/****************************************************************************
**
** Copyright (C) ${COPYRIGHT_YEAR} MikroElektronika d.o.o.
** Contact: https://www.mikroe.com/contact
**
** This file is part of the mikroSDK package
**
** Commercial License Usage
**
** Licensees holding valid commercial NECTO compilers AI licenses may use this
** file in accordance with the commercial license agreement provided with the
** Software or, alternatively, in accordance with the terms contained in
** a written agreement between you and The MikroElektronika Company.
** For licensing terms and conditions see
** https://www.mikroe.com/legal/software-license-agreement.
** For further information use the contact form at
** https://www.mikroe.com/contact.
**
**
** GNU Lesser General Public License Usage
**
** Alternatively, this file may be used for
** non-commercial projects under the terms of the GNU Lesser
** General Public License version 3 as published by the Free Software
** Foundation: https://www.gnu.org/licenses/lgpl-3.0.html.
**
** The above copyright notice and this permission notice shall be
** included in all copies or substantial portions of the Software.
**
** THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND,
** EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES
** OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT.
** IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM,
** DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT
** OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE
** OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
**
****************************************************************************/
/*!
 * @file  hal_ll_gpio_port.c
 * @brief GPIO HAL LOW LEVEL ported layer implementation.
 */

#include "hal_ll_gpio_port.h"

#define hal_ll_gpio_port_get_pin_index(__index) ( ( uint8_t )__index & 0xF )

#define hal_ll_gpio_port_get_port_index(__index) ( ( uint8_t )( __index & 0xF0 ) >> 4 )

#define GPIO_ALT_FUNC_MASK (0xFF00)

/* P/PM offsets, anchored at GPIO_PORTx_BASE (that port's P register addr). */
#define HAL_LL_GPIO_P_OFFSET       ( 0x00UL )
#define HAL_LL_GPIO_PM_OFFSET      ( 0x20UL )

/* Per-port register banks, one byte per port index (R01UH1082 4.3). */
#define HAL_LL_GPIO_PDIDIS_BASE    ( 0xF02B0UL )

/* PMCAxx only exists for ports 1, 2 and 4 (R01UH1082 4.3.7). Unimplemented
 * bits must be kept at their reset value (1), hence the masks. */
#define HAL_LL_PMCA1_BASE ( 0xF0061UL )
#define HAL_LL_PMCA2_BASE ( 0xF0062UL )
#define HAL_LL_PMCA4_BASE ( 0xF0064UL )
#define HAL_LL_PMCA1_MASK ( 0x1FU )
#define HAL_LL_PMCA2_MASK ( 0xFFU )
#define HAL_LL_PMCA4_MASK ( 0x3CU )

/* LCD port function registers (R01UH1082 4.3.16). PFSEG0 bits 0-3 are
 * PFCOM0-3 (P90-P93), PFSEGz lives in PFSEG(1 + z / 8) bit (z % 8). Most of
 * these reset to 1, i.e. the pin is an LCD output with digital I/O disabled. */
#define HAL_LL_PFSEG0_BASE         ( 0xF0290UL )
#define HAL_LL_PFSEG1_BASE         ( 0xF0291UL )

/* LCD input switch control register (R01UH1082 4.3.17). Resets to 0, i.e.
 * P85-P87 and P125-P127 are LCD pins with digital input disabled. */
#define HAL_LL_ISCLCD_ADDR         ( 0xF0298UL )
#define HAL_LL_ISCLCD_ISCCAP       ( 0x01U )
#define HAL_LL_ISCLCD_ISCVL1       ( 0x02U )
#define HAL_LL_ISCLCD_ISCVL2       ( 0x04U )
#define HAL_LL_ISCLCD_ISCVL3       ( 0x08U )
#define HAL_LL_ISCLCD_ISCVL4       ( 0x10U )

/* Port 13 has no PM register (P130 output only, P137 input only). */
#define HAL_LL_GPIO_PORT_13_INDEX  ( 13 )

#define HAL_LL_GPIO_PORT_INDEX_MAX ( sizeof( hal_ll_gpio_port_base_arr ) / sizeof( hal_ll_gpio_port_base_arr[ 0 ] ) )

/*!< @brief Pins of a port that have a PFSEGz bit, PFSEGz = seg_offset + pin. */
typedef struct {
    uint8_t pin_mask;
    uint8_t seg_offset;
} hal_ll_gpio_seg_map_t;

/*!< @brief PFSEG mapping per port index (R01UH1082 2.1.6, 4.3.16). */
static const hal_ll_gpio_seg_map_t hal_ll_gpio_seg_map[] =
{
    { 0xFF, 43 }, /* P00-P07 -> SEG43-SEG50 */
    { 0xFF, 35 }, /* P10-P17 -> SEG35-SEG42 */
    { 0xFC, 27 }, /* P22-P27 -> SEG29-SEG34 */
    { 0x3F, 20 }, /* P30-P35 -> SEG20-SEG25 */
    { 0xC0, 20 }, /* P46-P47 -> SEG26-SEG27 */
    { 0xFF,  4 }, /* P50-P57 -> SEG4-SEG11 */
    { 0x00,  0 },
    { 0xFF, 12 }, /* P70-P77 -> SEG12-SEG19 */
    { 0x00,  0 },
    { 0xF0,  0 }, /* P94-P97 -> SEG0-SEG3 (P90-P93 use PFCOM0-3) */
    { 0x00,  0 },
    { 0x00,  0 },
    { 0x00,  0 },
    { 0x01, 28 }, /* P130 -> SEG28 */
    { 0x3E, 50 }  /* P141-P145 -> SEG51-SEG55 */
};

static inline hal_ll_base_addr_t hal_ll_gpio_analog_ctrl_base( uint8_t port_index, uint8_t *implemented ) {
    switch ( port_index ) {
        case 1:  *implemented = HAL_LL_PMCA1_MASK; return HAL_LL_PMCA1_BASE;
        case 2:  *implemented = HAL_LL_PMCA2_MASK; return HAL_LL_PMCA2_BASE;
        case 4:  *implemented = HAL_LL_PMCA4_MASK; return HAL_LL_PMCA4_BASE;
        default: *implemented = 0; return 0;
    }
}

/*!< @brief GPIO PORT array */
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
    #ifdef GPIO_PORT_10
    GPIO_PORT10_BASE,
    #else
    0,
    #endif
    #ifdef GPIO_PORT_11
    GPIO_PORT11_BASE,
    #else
    0,
    #endif
    #ifdef GPIO_PORT_12
    GPIO_PORT12_BASE,
    #else
    0,
    #endif
    #ifdef GPIO_PORT_13
    GPIO_PORT13_BASE,
    #else
    0,
    #endif
    #ifdef GPIO_PORT_14
    GPIO_PORT14_BASE,
    #else
    0,
    #endif
};

// ---------------------------------------------- PRIVATE FUNCTION DECLARATIONS

/**
  * @brief  Configure port pins
  * @param  port     - port base address
  *         pin_mask - desired pin
  *         config   - pin settings
  * @return none
  */
static void hal_ll_gpio_config( uint32_t *port, uint16_t pin_mask, uint32_t config );

/**
  * @brief  Configure port pins alternate
  *         functions
  * @param  module_pin - desired pin
  *         config     - pin settings
  * @return none
  */
static void hal_ll_gpio_config_pin_alternate_enable( uint32_t module_pin, uint32_t module_config, bool state );

/**
  * @brief  Retrieve the index of the
  *         provided pin
  * @param  hal_ll_pin_name_t - pin
  * @return uint8_t - the index of the pin
  */
static uint8_t hal_ll_gpio_pin_index( hal_ll_pin_name_t name );

/**
  * @brief  Enable or disable the digital buffers of pins shared with LCD functions.
  * @details PFSEGx/PFCOMy reset to 1 and ISCLCD to 0, leaving most pins in
  *          "digital input invalid" state (R01UH1082 Table 4-5, 4.3.16, 4.3.17).
  * @param  port_index - port index
  *         mask       - pins within the port
  *         digital    - true for digital I/O, false to restore the reset
  *                      state (required for analog input)
  * @return none
  */
static void hal_ll_gpio_set_digital_mode( uint8_t port_index, uint8_t mask, bool digital );

// ------------------------------------------------ PUBLIC FUNCTION DEFINITIONS

uint8_t hal_ll_gpio_port_index( hal_ll_pin_name_t name ) {
    uint16_t ret;
    ret = hal_ll_gpio_port_get_port_index( name );
    return ret;
}

uint16_t hal_ll_gpio_pin_mask( hal_ll_pin_name_t name ) {
    uint16_t ret;
    ret = ( 1UL << hal_ll_gpio_pin_index( name ) );
    return ret;
}

uint32_t hal_ll_gpio_port_base( hal_ll_port_name_t name ) {
    if ( HAL_LL_GPIO_PORT_INDEX_MAX > name ) {
        return hal_ll_gpio_port_base_arr[ name ];
    }

    return 0;
}

void hal_ll_gpio_analog_input( uint32_t *port, uint16_t pin_mask ) {
    hal_ll_gpio_config( port, pin_mask, GPIO_CFG_ANALOG_INPUT );
}

void hal_ll_gpio_digital_input( uint32_t *port, uint16_t pin_mask ) {
    hal_ll_gpio_config( port, pin_mask, GPIO_CFG_DIGITAL_INPUT );
}

void hal_ll_gpio_digital_output( uint32_t *port, uint16_t pin_mask ) {
    hal_ll_gpio_config( port, pin_mask, GPIO_CFG_DIGITAL_OUTPUT );
}

void hal_ll_gpio_module_struct_init( module_struct const *module, bool state ) {
    int32_t index = 0;

    while ( module->pins[ index ] != GPIO_MODULE_STRUCT_END )
    {
        hal_ll_gpio_config_pin_alternate_enable( module->pins[ index ], module->configs[ index ], state );

        index++;
    }
}

// ------------------------------------------------ STATIC FUNCTION DEFINITIONS

static uint8_t hal_ll_gpio_pin_index( hal_ll_pin_name_t name ) {
    return hal_ll_gpio_port_get_pin_index( name );
}

static uint8_t hal_ll_gpio_get_port_number(uint32_t base_addr)
{
    for (int i = 0; i < sizeof(hal_ll_gpio_port_base_arr) / sizeof(hal_ll_gpio_port_base_arr[0]); i++) {
        if (hal_ll_gpio_port_base_arr[i] == base_addr) {
            return i; // Port number.
        }
    }
    return 0xFF; // Not found.
}

static void hal_ll_gpio_set_digital_mode( uint8_t port_index, uint8_t mask, bool digital ) {
    uint8_t pin;
    uint8_t seg;
    uint8_t iscl = 0;
    hal_ll_base_addr_t reg;

    // P90-P93 -> PFCOM0-PFCOM3.
    if ( 9 == port_index ) {
        if ( !digital ) {
            set_reg_bits( ( uint8_t * ) HAL_LL_PFSEG0_BASE, mask & 0x0F );
        } else {
            clear_reg_bits( ( uint8_t * ) HAL_LL_PFSEG0_BASE, mask & 0x0F );
        }
    }

    if ( ( sizeof( hal_ll_gpio_seg_map ) / sizeof( hal_ll_gpio_seg_map[ 0 ] ) ) > port_index ) {
        for ( pin = 0; pin < 8; pin++ ) {
            if ( !( mask & hal_ll_gpio_seg_map[ port_index ].pin_mask & ( 1U << pin ) ) ) {
                continue;
            }

            seg = hal_ll_gpio_seg_map[ port_index ].seg_offset + pin;
            reg = HAL_LL_PFSEG1_BASE + ( seg >> 3 );

            if ( !digital ) {
                set_reg_bit( ( uint8_t * ) reg, seg & 0x07 );
            } else {
                clear_reg_bit( ( uint8_t * ) reg, seg & 0x07 );
            }
        }
    }

    // VL1-VL4, CAPL, CAPH pins: ISCLCD bit = 1 enables the digital input buffer.
    if ( 8 == port_index ) {
        if ( mask & 0x20 ) iscl |= HAL_LL_ISCLCD_ISCVL4;
        if ( mask & 0x40 ) iscl |= HAL_LL_ISCLCD_ISCVL2;
        if ( mask & 0x80 ) iscl |= HAL_LL_ISCLCD_ISCVL1;
    } else if ( 12 == port_index ) {
        if ( mask & 0x20 ) iscl |= HAL_LL_ISCLCD_ISCVL3;
        if ( mask & 0xC0 ) iscl |= HAL_LL_ISCLCD_ISCCAP;
    }

    if ( iscl ) {
        if ( !digital ) {
            clear_reg_bits( ( uint8_t * ) HAL_LL_ISCLCD_ADDR, iscl );
        } else {
            set_reg_bits( ( uint8_t * ) HAL_LL_ISCLCD_ADDR, iscl );
        }
    }
}

static void hal_ll_gpio_config( uint32_t *port, uint16_t pin_mask, uint32_t config ) {
    hal_ll_base_addr_t port_addr = ( hal_ll_base_addr_t ) port;
    uint8_t mask = ( uint8_t ) pin_mask;
    uint8_t port_index;
    uint8_t analog_implemented;
    hal_ll_base_addr_t analog_reg;
    hal_ll_base_addr_t pdidis_reg;

    if ( NULL == port ) {
        return;
    }

    port_index = hal_ll_gpio_get_port_number( ( uint32_t ) port_addr );
    if ( HAL_LL_GPIO_PORT_INDEX_MAX <= port_index ) {
        return;
    }

    analog_reg = hal_ll_gpio_analog_ctrl_base( port_index, &analog_implemented );
    pdidis_reg = HAL_LL_GPIO_PDIDIS_BASE + port_index;

    switch ( config ) {
        case GPIO_CFG_DIGITAL_INPUT:
            if ( 0 != analog_reg ) {
                clear_reg_bits( ( uint8_t * ) analog_reg, mask & analog_implemented );
            }
            hal_ll_gpio_set_digital_mode( port_index, mask, true );
            if ( HAL_LL_GPIO_PORT_13_INDEX != port_index ) {
                set_reg_bits( ( uint8_t * ) ( port_addr + HAL_LL_GPIO_PM_OFFSET ), mask );
            }
            clear_reg_bits( ( uint8_t * ) pdidis_reg, mask );
            break;

        case GPIO_CFG_DIGITAL_OUTPUT:
            if ( 0 != analog_reg ) {
                clear_reg_bits( ( uint8_t * ) analog_reg, mask & analog_implemented );
            }
            hal_ll_gpio_set_digital_mode( port_index, mask, true );
            /* Output latch has no defined reset value we can rely on across
             * every pin - force it low here so "configured as output"
             * always starts from a known, deterministic level instead of
             * whatever P happened to already contain. */
            clear_reg_bits( ( uint8_t * ) ( port_addr + HAL_LL_GPIO_P_OFFSET ), mask );
            if ( HAL_LL_GPIO_PORT_13_INDEX != port_index ) {
                clear_reg_bits( ( uint8_t * ) ( port_addr + HAL_LL_GPIO_PM_OFFSET ), mask );
            }
            clear_reg_bits( ( uint8_t * ) pdidis_reg, mask );
            break;

        case GPIO_CFG_ANALOG_INPUT:
            /* Only P10-P14, P20-P27 and P42-P45 have an analog function
             * (PMCAxx). Analog requires PMCAmn = 1, PFSEGz = 1 (where the pin
             * has one) and PMmn = 1 (R01UH1082 Table 4-5). */
            if ( 0 == analog_reg ) {
                break;
            }
            mask &= analog_implemented;
            set_reg_bits( ( uint8_t * ) ( port_addr + HAL_LL_GPIO_PM_OFFSET ), mask );
            set_reg_bits( ( uint8_t * ) analog_reg, mask );
            hal_ll_gpio_set_digital_mode( port_index, mask, false );
            break;

        default:
            break;
    }
}

static void hal_ll_gpio_config_pin_alternate_enable( uint32_t module_pin, uint32_t module_config, bool state ) {
    uint8_t pin_index;
    hal_ll_pin_name_t pin_name;
    hal_ll_port_name_t port_name;
    hal_ll_base_addr_t port_addr;

    pin_name = ( hal_ll_pin_name_t ) module_pin;
    pin_index = hal_ll_gpio_pin_index( pin_name );
    port_name = hal_ll_gpio_port_index( pin_name );

    port_addr = ( hal_ll_base_addr_t ) hal_ll_gpio_port_base( port_name );

    if ( false == state ) {
        return;
    }

    hal_ll_gpio_config( ( uint32_t * ) port_addr, ( uint16_t ) ( 1 << pin_index ), module_config );
}

// ------------------------------------------------------------------------- END
