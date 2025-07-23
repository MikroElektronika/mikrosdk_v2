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

#ifdef GPIO_PORT_0
#define GPIO_PORT0_BASE  (0x40040000UL)
#endif
#ifdef GPIO_PORT_1
#define GPIO_PORT1_BASE  (0x40040020UL)
#endif
#ifdef GPIO_PORT_2
#define GPIO_PORT2_BASE  (0x40040040UL)
#endif
#ifdef GPIO_PORT_3
#define GPIO_PORT3_BASE  (0x40040060UL)
#endif
#ifdef GPIO_PORT_4
#define GPIO_PORT4_BASE  (0x40040080UL)
#endif
#ifdef GPIO_PORT_5
#define GPIO_PORT5_BASE  (0x400400A0UL)
#endif
#ifdef GPIO_PORT_6
#define GPIO_PORT6_BASE  (0x400400C0UL)
#endif
#ifdef GPIO_PORT_7
#define GPIO_PORT7_BASE  (0x400400E0UL)
#endif
#ifdef GPIO_PORT_8
#define GPIO_PORT8_BASE  (0x40040100UL)
#endif
#ifdef GPIO_PORT_9
#define GPIO_PORT9_BASE  (0x40040120UL)
#endif
#ifdef GPIO_PORT_PORT10
#define GPIO_PORT10_BASE (0x40040140UL)
#endif
#ifdef GPIO_PORT_PORT11
#define GPIO_PORT11_BASE (0x40040160UL)
#endif
#ifdef GPIO_PORT_PORT12
#define GPIO_PORT12_BASE (0x40040180UL)
#endif
#ifdef GPIO_PORT_PORT13
#define GPIO_PORT13_BASE (0x400401A0UL)
#endif
#ifdef GPIO_PORT_PORT14
#define GPIO_PORT14_BASE (0x400401C0UL)
#endif

#define PWPR_REGISTER_BASE (* ( volatile uint8_t * )0x40040D03UL)
#define PFS_REGISTER_ADDR (0x40040800UL)
#define PFS_PSEL_MASK (0x1F000000UL)

/*!< @brief GPIO PORT array */
static const uint32_t hal_ll_gpio_port_base_arr[] =
{
    #ifdef GPIO_PORT0_BASE
    GPIO_PORT0_BASE,
    #endif
    #ifdef GPIO_PORT1_BASE
    GPIO_PORT1_BASE,
    #endif
    #ifdef GPIO_PORT2_BASE
    GPIO_PORT2_BASE,
    #endif
    #ifdef GPIO_PORT3_BASE
    GPIO_PORT3_BASE,
    #endif
    #ifdef GPIO_PORT4_BASE
    GPIO_PORT4_BASE,
    #endif
    #ifdef GPIO_PORT5_BASE
    GPIO_PORT5_BASE,
    #endif
    #ifdef GPIO_PORT6_BASE
    GPIO_PORT6_BASE,
    #endif
    #ifdef GPIO_PORT7_BASE
    GPIO_PORT7_BASE,
    #endif
    #ifdef GPIO_PORT8_BASE
    GPIO_PORT8_BASE,
    #endif
    #ifdef GPIO_PORT9_BASE
    GPIO_PORT9_BASE,
    #endif
    #ifdef GPIO_PORT10_BASE
    GPIO_PORT10_BASE,
    #endif
    #ifdef GPIO_PORT11_BASE
    GPIO_PORT11_BASE,
    #endif
    #ifdef GPIO_PORT12_BASE
    GPIO_PORT12_BASE,
    #endif
    #ifdef GPIO_PORT13_BASE
    GPIO_PORT13_BASE,
    #endif
    #ifdef GPIO_PORT14_BASE
    GPIO_PORT14_BASE
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
    return hal_ll_gpio_port_base_arr[ name ];
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

static uint32_t hal_ll_gpio_get_port_number(uint32_t base_addr)
{
    for (int i = 0; i < sizeof(hal_ll_gpio_port_base_arr) / sizeof(hal_ll_gpio_port_base_arr[0]); i++) {
        if (hal_ll_gpio_port_base_arr[i] == base_addr) {
            return i; // port number
        }
    }
    return -1; // not found
}

static void hal_ll_gpio_config( uint32_t *port, uint16_t pin_mask, uint32_t config ) {
    uint32_t pin_index = ( pin_mask == 0xFFFF ) ? 0xFFFF : __builtin_ctz(pin_mask); // TODO Esma
    hal_ll_port_name_t port_index;
    port_index = hal_ll_gpio_get_port_number( *port );
    hal_ll_gpio_pfs_t *port_pfs_ptr = PFS_REGISTER_ADDR;
    hal_ll_gpio_base_handle_t *port_ptr = (hal_ll_gpio_base_handle_t *) *port;

    // Clear the B0WI bit in the PWPR register. This enables writing to the PFSWE bit in the PWPR register.
    PWPR_REGISTER_BASE &= ~0x80; // Clear B0WI bit
    // Set 1 to the PFSWE bit in the PWPR register. This enables writing to the PmnPFS register.
    PWPR_REGISTER_BASE |= 0x40; // Set PFSWE bit

    if ( pin_mask == 0xFFFF ) {
        if ( config & GPIO_CFG_DIGITAL_OUTPUT )
            port_ptr->pdr = pin_mask;
        else
            port_ptr->pdr = 0;
    } else {
        // Clear the Port Mode Control bit in the PMR for the target pin to select the general I/O port.
        port_pfs_ptr->port[port_index].pin[pin_index].pmnpfs_b.pmr = 0;
        // Specify the input/output function for the pin through the PSEL[4:0] bit settings in the PmnPFS register.
        port_pfs_ptr->port[port_index].pin[pin_index].pmnpfs_b.psel = 0;

        if( config & GPIO_CFG_ANALOG_INPUT ) {
            port_pfs_ptr->port[port_index].pin[pin_index].pmnpfs_b.pmr = 0;
            port_pfs_ptr->port[port_index].pin[pin_index].pmnpfs_b.pdr = 0;
            port_pfs_ptr->port[port_index].pin[pin_index].pmnpfs_b.asel = 1;
        } else if ( config & GPIO_CFG_DIGITAL_OUTPUT ) {
            port_pfs_ptr->port[port_index].pin[pin_index].pmnpfs_b.pdr = 1;
            port_pfs_ptr->port[port_index].pin[pin_index].pmnpfs_b.asel = 0;
        } else if ( config & GPIO_CFG_DIGITAL_INPUT ) {
            port_pfs_ptr->port[port_index].pin[pin_index].pmnpfs_b.pdr = 0;
            port_pfs_ptr->port[port_index].pin[pin_index].pmnpfs_b.asel = 0;
        }

        if( config & GPIO_CFG_PORT_PULL_UP_ENABLE )
            port_pfs_ptr->port[port_index].pin[pin_index].pmnpfs_b.pcr = 1;

        if( config & GPIO_CFG_NMOS_OPEN_DRAIN_ENABLE )
            port_pfs_ptr->port[port_index].pin[pin_index].pmnpfs_b.ncodr = 1;

        if( config & GPIO_CFG_PORT_MIDDLE_DRIVE )
            port_pfs_ptr->port[port_index].pin[pin_index].pmnpfs_b.dscr = 1;

        if( config & GPIO_CFG_EVENT_RISING_EDGE )
            port_pfs_ptr->port[port_index].pin[pin_index].pmnpfs_b.eofr = 1;

        if( config & GPIO_CFG_EVENT_FALLING_EDGE )
            port_pfs_ptr->port[port_index].pin[pin_index].pmnpfs_b.eofr = 2;

        if( config & GPIO_CFG_EVENT_BOTH_EDGES )
            port_pfs_ptr->port[port_index].pin[pin_index].pmnpfs_b.eofr = 3;

        if( config & GPIO_CFG_IRQ_ENABLE )
            port_pfs_ptr->port[port_index].pin[pin_index].pmnpfs_b.isel = 1;

        if( config & GPIO_CFG_PERIPHERAL_PIN )
            port_pfs_ptr->port[port_index].pin[pin_index].pmnpfs_b.pmr = 1;

        // Clear the PFSWE bit in the PWPR register. This disables writing to the PmnPFS register.
        PWPR_REGISTER_BASE &= ~0x40; // Set PFSWE bit
        // Set 1 to the B0WI bit in the PWPR register. This disables writing to the PFSWE bit in the PWPR register
        PWPR_REGISTER_BASE |= 0x80; // Set B0WI bit
    }
}

static void hal_ll_gpio_config_pin_alternate_enable( uint32_t module_pin, uint32_t module_config, bool state ) {
    uint8_t pin_index;
    hal_ll_pin_name_t pin_name;
    hal_ll_port_name_t port_name;
    hal_ll_gpio_pfs_t *port_ptr = PFS_REGISTER_ADDR;

    pin_name = module_pin & GPIO_PIN_NAME_MASK;

    pin_index = hal_ll_gpio_pin_index( pin_name );

    port_name = hal_ll_gpio_port_index( module_pin & 0xFF );

    hal_ll_gpio_config( (uint32_t *)&port_ptr, hal_ll_gpio_pin_mask( pin_index ), module_config );

    // Clear the B0WI bit in the PWPR register. This enables writing to the PFSWE bit in the PWPR register.
    PWPR_REGISTER_BASE &= ~0x80; // Clear B0WI bit
    // Set 1 to the PFSWE bit in the PWPR register. This enables writing to the PmnPFS register.
    PWPR_REGISTER_BASE |= 0x40; // Set PFSWE bit

    if ( true == state ) {
        port_ptr->port[port_name].pin[pin_index].pmnpfs_b.psel = (( module_pin & 0xFF00 ) >> 8 );
        port_ptr->port[port_name].pin[pin_index].pmnpfs_b.pmr = 1; // Peripheral mode
    } else {
        port_ptr->port[port_name].pin[pin_index].pmnpfs_b.psel &= 0;
    }

    // Clear the PFSWE bit in the PWPR register. This disables writing to the PmnPFS register.
    PWPR_REGISTER_BASE &= ~0x40; // Set PFSWE bit
    // Set 1 to the B0WI bit in the PWPR register. This disables writing to the PFSWE bit in the PWPR register
    PWPR_REGISTER_BASE |= 0x80; // Set B0WI bit
}

// ------------------------------------------------------------------------- END
