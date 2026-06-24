/****************************************************************************
**
** Copyright (C) ${COPYRIGHT_YEAR} MikroElektronika d.o.o.
** Contact: https://www.mikroe.com/contact
**
** This file is part of the mikroSDK package
**
** GNU Lesser General Public License Usage
** https://www.gnu.org/licenses/lgpl-3.0.html.
**
****************************************************************************/
/*!
 * @file  hal_ll_gpio_port.c
 * @brief GPIO HAL LOW LEVEL ported layer implementation for RA8D1 (R7FA8D1BHECBD).
 *
 * REGISTER LAYOUT (RA8D1 / R7FA8M1 branch in hal_ll_gpio_port.h):
 *
 *   PCNTRn offset within each R_PORTn block (stride = 0x20):
 *     +0x00  PCNTR1 : [31:16] PDR  (direction, 1=output)
 *                   : [15:0]  PODR (output data)
 *     +0x04  PCNTR2 : [31:16] EIDR (event input)
 *                   : [15:0]  PIDR (input data, read-only)
 *     +0x08  PCNTR3 : [31:16] PORR (output reset  — write 1 to clear PODR bit)
 *                   : [15:0]  POSR (output set    — write 1 to set   PODR bit)
 *     +0x0C  PCNTR4 : [31:16] EORR
 *                   : [15:0]  EOSR
 *
 *   PFS base:  0x40400800
 *     port_pfs->port[port_idx].pin[pin_idx].pmnpfs_b.pdr   = direction
 *     port_pfs->port[port_idx].pin[pin_idx].pmnpfs_b.asel  = analog select
 *     port_pfs->port[port_idx].pin[pin_idx].pmnpfs_b.pmr   = peripheral mode
 *     port_pfs->port[port_idx].pin[pin_idx].pmnpfs_b.psel  = peripheral select
 *
 *   PWPR (write-protect) at 0x40400D03:
 *     Clear B0WI (bit7) → set PFSWE (bit6) → write PFS → clear PFSWE → set B0WI
 *
 *   Pin name encoding (from hal_ll_pin_names.h):
 *     GPIO_Pxyz = (x << 4) | z   (e.g. GPIO_P507 = 0x57, port=5, pin=7)
 *     port_index = (name & 0xF0) >> 4
 *     pin_index  = (name & 0x0F)
 */

#include "hal_ll_gpio_port.h"

// -------------------------------------------------------------------------
// Encoding helpers — mirror the macros in hal_ll_gpio_port.c generic code
// -------------------------------------------------------------------------
#define hal_ll_gpio_port_get_pin_index(__index)  ( (uint8_t)( __index        & 0x0F ) )
#define hal_ll_gpio_port_get_port_index(__index) ( (uint8_t)( (__index & 0xF0) >> 4 ) )

// -------------------------------------------------------------------------
// Port base address table  (index = port number 0-9)
// GPIO_PORTn_BASE defined in mcu_definitions.h
// -------------------------------------------------------------------------
static const uint32_t hal_ll_gpio_port_base_arr[] =
{
    #ifdef GPIO_PORT_0
    GPIO_PORT0_BASE,
    #else
    0,
    #endif
    #ifdef GPIO_PORT_1
    GPIO_PORT1_BASE,
    #else
    0,
    #endif
    #ifdef GPIO_PORT_2
    GPIO_PORT2_BASE,
    #else
    0,
    #endif
    #ifdef GPIO_PORT_3
    GPIO_PORT3_BASE,
    #else
    0,
    #endif
    #ifdef GPIO_PORT_4
    GPIO_PORT4_BASE,
    #else
    0,
    #endif
    #ifdef GPIO_PORT_5
    GPIO_PORT5_BASE,
    #else
    0,
    #endif
    #ifdef GPIO_PORT_6
    GPIO_PORT6_BASE,
    #else
    0,
    #endif
    #ifdef GPIO_PORT_7
    GPIO_PORT7_BASE,
    #else
    0,
    #endif
    #ifdef GPIO_PORT_8
    GPIO_PORT8_BASE,
    #else
    0,
    #endif
    #ifdef GPIO_PORT_9
    GPIO_PORT9_BASE,
    #else
    0,
    #endif
    // RA8D1 has no PORT_A (10) or PORT_B (11)
    0,
    0
};

// -------------------------------------------------------------------------
// Private helpers
// -------------------------------------------------------------------------

/**
 * @brief  Unlock PFS registers for writing.
 *         Sequence: clear B0WI → set PFSWE
 */
static inline void hal_ll_gpio_pfs_unlock( void )
{
    PWPR_REGISTER_BASE &= ~0x80U;   // Clear B0WI  — allows PFSWE to be changed
    PWPR_REGISTER_BASE |=  0x40U;   // Set   PFSWE — allows PmnPFS to be written
}

/**
 * @brief  Lock PFS registers after writing.
 *         Sequence: clear PFSWE → set B0WI
 */
static inline void hal_ll_gpio_pfs_lock( void )
{
    PWPR_REGISTER_BASE &= ~0x40U;   // Clear PFSWE — disables PmnPFS writes
    PWPR_REGISTER_BASE |=  0x80U;   // Set   B0WI  — locks PFSWE
}

/**
 * @brief  Reverse-lookup port index from a base address.
 */
static uint8_t hal_ll_gpio_get_port_number( uint32_t base_addr )
{
    uint8_t i;
    for ( i = 0; i < (uint8_t)(sizeof(hal_ll_gpio_port_base_arr) /
                                sizeof(hal_ll_gpio_port_base_arr[0])); i++ )
    {
        if ( hal_ll_gpio_port_base_arr[i] == base_addr )
            return i;
    }
    return 0xFFU; // Not found
}

/**
 * @brief  Return port base address for a given port index.
 */
static inline uint32_t hal_ll_gpio_get_base_addr( uint8_t port_index )
{
    if ( port_index < PORT_COUNT )
        return hal_ll_gpio_port_base_arr[ port_index ];
    return 0UL;
}

/**
 * @brief  Return pin index (0-15) from pin name.
 */
static inline uint8_t hal_ll_gpio_pin_index( hal_ll_pin_name_t name )
{
    return hal_ll_gpio_port_get_pin_index( name );
}

// -------------------------------------------------------------------------
// Core configuration function
// -------------------------------------------------------------------------

/**
 * @brief  Configure a single pin or a full port via PFS and PDR.
 *
 * @param  port      Pointer to the port base address (value, not register).
 *                   For a single pin *port is the R_PORTn base address.
 * @param  pin_mask  Bit mask for the target pin(s).
 *                   Pass 0xFFFF to configure all 16 pins of the port at once
 *                   using the PDR register (direction only, no PFS access).
 * @param  config    Combination of GPIO_CFG_* flags from mcu_definitions.h.
 */
static void hal_ll_gpio_config( uint32_t *port, uint16_t pin_mask, uint32_t config )
{
    hal_ll_gpio_pfs_t        *port_pfs_ptr = PFS_REGISTER_ADDR;
    hal_ll_gpio_base_handle_t *port_ptr    = (hal_ll_gpio_base_handle_t *)(*port);

    // -----------------------------------------------------------------
    // Fast path: whole-port direction change via PDR (no PFS needed).
    // This is used by hal_ll_gpio_configure_port when mask == 0xFFFF.
    // -----------------------------------------------------------------
    if ( pin_mask == 0xFFFFU )
    {
        if ( config & GPIO_CFG_DIGITAL_OUTPUT )
            port_ptr->pdr = 0xFFFFU;
        else
            port_ptr->pdr = 0x0000U;
        return;
    }

    // -----------------------------------------------------------------
    // Single-pin path via PFS
    // -----------------------------------------------------------------
    uint32_t pin_index  = (uint32_t)__builtin_ctz( pin_mask );   // 0-15
    uint8_t  port_index = hal_ll_gpio_get_port_number( *port );

    if ( port_index == 0xFFU )
        return;   // Invalid port address — bail out safely

    hal_ll_gpio_pfs_unlock();

    // Step 1: clear peripheral mode — pin must be GPIO before reconfiguring
    port_pfs_ptr->port[ port_index ].pin[ pin_index ].pmnpfs_b.pmr  = 0U;
    // Step 2: clear peripheral select
    port_pfs_ptr->port[ port_index ].pin[ pin_index ].pmnpfs_b.psel = 0U;

    // Step 3: direction / analog / digital
    if ( config & GPIO_CFG_ANALOG_INPUT )
    {
        port_pfs_ptr->port[ port_index ].pin[ pin_index ].pmnpfs_b.pdr  = 0U;
        port_pfs_ptr->port[ port_index ].pin[ pin_index ].pmnpfs_b.asel = 1U;
    }
    else if ( config & GPIO_CFG_DIGITAL_OUTPUT )
    {
        port_pfs_ptr->port[ port_index ].pin[ pin_index ].pmnpfs_b.asel = 0U;
        port_pfs_ptr->port[ port_index ].pin[ pin_index ].pmnpfs_b.pdr  = 1U;
    }
    else    // GPIO_CFG_DIGITAL_INPUT
    {
        port_pfs_ptr->port[ port_index ].pin[ pin_index ].pmnpfs_b.asel = 0U;
        port_pfs_ptr->port[ port_index ].pin[ pin_index ].pmnpfs_b.pdr  = 0U;
    }

    // Step 4: optional features
    if ( config & GPIO_CFG_PORT_PULL_UP_ENABLE )
        port_pfs_ptr->port[ port_index ].pin[ pin_index ].pmnpfs_b.pcr   = 1U;

    if ( config & GPIO_CFG_NMOS_OPEN_DRAIN_ENABLE )
        port_pfs_ptr->port[ port_index ].pin[ pin_index ].pmnpfs_b.ncodr = 1U;

    if ( config & GPIO_CFG_PORT_MIDDLE_DRIVE )
        port_pfs_ptr->port[ port_index ].pin[ pin_index ].pmnpfs_b.dscr  = 1U;

    if ( config & GPIO_CFG_EVENT_RISING_EDGE )
        port_pfs_ptr->port[ port_index ].pin[ pin_index ].pmnpfs_b.eofr  = 1U;

    if ( config & GPIO_CFG_EVENT_FALLING_EDGE )
        port_pfs_ptr->port[ port_index ].pin[ pin_index ].pmnpfs_b.eofr  = 2U;

    if ( config & GPIO_CFG_EVENT_BOTH_EDGES )
        port_pfs_ptr->port[ port_index ].pin[ pin_index ].pmnpfs_b.eofr  = 3U;

    if ( config & GPIO_CFG_IRQ_ENABLE )
        port_pfs_ptr->port[ port_index ].pin[ pin_index ].pmnpfs_b.isel  = 1U;

    // Step 5: re-enable peripheral mode ONLY if caller asked for it
    if ( config & GPIO_CFG_PERIPHERAL_PIN )
        port_pfs_ptr->port[ port_index ].pin[ pin_index ].pmnpfs_b.pmr   = 1U;

    hal_ll_gpio_pfs_lock();
}

// -------------------------------------------------------------------------
// Alternate function (peripheral pin) helper
// -------------------------------------------------------------------------

static void hal_ll_gpio_config_pin_alternate_enable( uint32_t module_pin,
                                                      uint32_t module_config,
                                                      bool     state )
{
    hal_ll_gpio_pfs_t  *port_ptr  = PFS_REGISTER_ADDR;
    hal_ll_pin_name_t   pin_name  = (hal_ll_pin_name_t)( module_pin & GPIO_PIN_NAME_MASK );
    uint8_t             pin_index = hal_ll_gpio_pin_index( pin_name );
    hal_ll_port_name_t  port_name = hal_ll_gpio_port_index( module_pin & 0xFFU );
    uint32_t            port_base = hal_ll_gpio_get_base_addr( port_name );

    // First set the pin to GPIO mode with the requested config
    hal_ll_gpio_config( (uint32_t *)&port_base,
                        hal_ll_gpio_pin_mask( pin_name ),
                        module_config );

    hal_ll_gpio_pfs_unlock();

    if ( state )
    {
        // Write peripheral select, then switch to peripheral mode
        port_ptr->port[ port_name ].pin[ pin_index ].pmnpfs_b.psel =
            (uint32_t)( ( module_pin & 0xFF00UL ) >> 8 );
        port_ptr->port[ port_name ].pin[ pin_index ].pmnpfs_b.pmr  = 1U;
    }
    else
    {
        port_ptr->port[ port_name ].pin[ pin_index ].pmnpfs_b.pmr  = 0U;
        port_ptr->port[ port_name ].pin[ pin_index ].pmnpfs_b.psel = 0U;
    }

    hal_ll_gpio_pfs_lock();
}

// -------------------------------------------------------------------------
// Public API implementation
// -------------------------------------------------------------------------

uint8_t hal_ll_gpio_port_index( hal_ll_pin_name_t name )
{
    return hal_ll_gpio_port_get_port_index( name );
}

uint16_t hal_ll_gpio_pin_mask( hal_ll_pin_name_t name )
{
    return (uint16_t)( 1UL << hal_ll_gpio_port_get_pin_index( name ) );
}

uint32_t hal_ll_gpio_port_base( hal_ll_port_name_t name )
{
    return hal_ll_gpio_port_base_arr[ name ];
}

void hal_ll_gpio_analog_input( uint32_t *port, uint16_t pin_mask )
{
    hal_ll_gpio_config( port, pin_mask, GPIO_CFG_ANALOG_INPUT );
}

void hal_ll_gpio_digital_input( uint32_t *port, uint16_t pin_mask )
{
    hal_ll_gpio_config( port, pin_mask, GPIO_CFG_DIGITAL_INPUT );
}

void hal_ll_gpio_digital_output( uint32_t *port, uint16_t pin_mask )
{
    hal_ll_gpio_config( port, pin_mask, GPIO_CFG_DIGITAL_OUTPUT );
}

void hal_ll_gpio_module_struct_init( module_struct const *module, bool state )
{
    int32_t index = 0;
    while ( module->pins[ index ] != (uint32_t)GPIO_MODULE_STRUCT_END )
    {
        hal_ll_gpio_config_pin_alternate_enable( module->pins[ index ],
                                                  module->configs[ index ],
                                                  state );
        index++;
    }
}

// ------------------------------------------------------------------------- END