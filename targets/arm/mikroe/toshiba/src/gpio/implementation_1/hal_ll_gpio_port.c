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
#include "hal_ll_cg.h"

#define hal_ll_gpio_port_get_pin_index( __index ) ( (uint8_t) __index & 0xF )

#define hal_ll_gpio_port_get_port_index( __index ) ( (uint8_t) ( __index & 0xF0 ) >> 4 )

#ifdef GPIO_PORT_A
    #define GPIO_PORTA_BASE ( 0x400E0000UL )
#endif
#ifdef GPIO_PORT_B
    #define GPIO_PORTB_BASE ( 0x400E0100UL )
#endif
#ifdef GPIO_PORT_C
    #define GPIO_PORTC_BASE ( 0x400E0200UL )
#endif
#ifdef GPIO_PORT_D
    #define GPIO_PORTD_BASE ( 0x400E0300UL )
#endif
#ifdef GPIO_PORT_E
    #define GPIO_PORTE_BASE ( 0x400E0400UL )
#endif
#ifdef GPIO_PORT_F
    #define GPIO_PORTF_BASE ( 0x400E0500UL )
#endif
#ifdef GPIO_PORT_G
    #define GPIO_PORTG_BASE ( 0x400E0600UL )
#endif
#ifdef GPIO_PORT_H
    #define GPIO_PORTH_BASE ( 0x400E0700UL )
#endif
#ifdef GPIO_PORT_J
    #define GPIO_PORTJ_BASE ( 0x400E0800UL )
#endif
#ifdef GPIO_PORT_K
    #define GPIO_PORTK_BASE ( 0x400E0900UL )
#endif
#ifdef GPIO_PORT_L
    #define GPIO_PORTL_BASE ( 0x400E0A00UL )
#endif
#ifdef GPIO_PORT_M
    #define GPIO_PORTM_BASE ( 0x400E0B00UL )
#endif
#ifdef GPIO_PORT_N
    #define GPIO_PORTN_BASE ( 0x400E0C00UL )
#endif
#ifdef GPIO_PORT_U
    #define GPIO_PORTU_BASE ( 0x400E1000UL )
#endif
#ifdef GPIO_PORT_V
    #define GPIO_PORTV_BASE ( 0x400E1100UL )
#endif
/*!< @brief GPIO PORT array */
static const uint32_t hal_ll_gpio_port_base_arr[] = {
#ifdef GPIO_PORTA_BASE
    GPIO_PORTA_BASE,
#endif
#ifdef GPIO_PORTB_BASE
    GPIO_PORTB_BASE,
#endif
#ifdef GPIO_PORTC_BASE
    GPIO_PORTC_BASE,
#endif
#ifdef GPIO_PORTD_BASE
    GPIO_PORTD_BASE,
#endif
#ifdef GPIO_PORTE_BASE
    GPIO_PORTE_BASE,
#endif
#ifdef GPIO_PORTF_BASE
    GPIO_PORTF_BASE,
#endif
#ifdef GPIO_PORTG_BASE
    GPIO_PORTG_BASE,
#endif
#ifdef GPIO_PORTH_BASE
    GPIO_PORTH_BASE,
#endif
#ifdef GPIO_PORTJ_BASE
    GPIO_PORTJ_BASE,
#endif
#ifdef GPIO_PORTK_BASE
    GPIO_PORTK_BASE,
#endif
#ifdef GPIO_PORTL_BASE
    GPIO_PORTL_BASE,
#endif
#ifdef GPIO_PORTM_BASE
    GPIO_PORTM_BASE,
#endif
#ifdef GPIO_PORTN_BASE
    GPIO_PORTN_BASE,
#endif
#ifdef GPIO_PORTU_BASE
    GPIO_PORTU_BASE,
#endif
#ifdef GPIO_PORTV_BASE
    GPIO_PORTV_BASE
#endif
};

#define PROTECT_DISABLE 0xC1

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
  * @brief  Enable gpio port clock
  * @param  port - port base address
  * @return none
  */
static void hal_ll_gpio_clock_enable( uint32_t port );

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
    hal_ll_gpio_config( port, pin_mask, GPIO_CFG_DIGITAL_INPUT); // todo 
}

void hal_ll_gpio_digital_input( uint32_t *port, uint16_t pin_mask ) {
    hal_ll_gpio_config( port, pin_mask, GPIO_CFG_MODE_INPUT_PULLDOWN );
}

void hal_ll_gpio_digital_output( uint32_t *port, uint16_t pin_mask ) {
    hal_ll_gpio_config( port, pin_mask, GPIO_CFG_MODE_OUTPUT_PP );
}

void hal_ll_gpio_module_struct_init( module_struct const *module, bool state ) {
    int32_t index = 0;

    while ( module->pins[ index ] != GPIO_MODULE_STRUCT_END ) {
        hal_ll_gpio_config_pin_alternate_enable( module->pins[ index ], module->configs[ index ], state );

        index++;
    }
}

// ------------------------------------------------ STATIC FUNCTION DEFINITIONS

static uint8_t hal_ll_gpio_pin_index( hal_ll_pin_name_t name ) {
    return hal_ll_gpio_port_get_pin_index( name );
}

static uint32_t hal_ll_gpio_get_port_number( uint32_t base_addr ) {
    for ( int i = 0; i < sizeof( hal_ll_gpio_port_base_arr ) / sizeof( hal_ll_gpio_port_base_arr[0] ); i++ ) {
        if ( hal_ll_gpio_port_base_arr[i] == base_addr ) {
            return i; // Port number.
        }
    }
    return -1; // Not found.
}

static void hal_ll_gpio_config( uint32_t *port, uint16_t pin_mask, uint32_t config ) {
    hal_ll_gpio_base_handle_t *gpio_ptr = (hal_ll_gpio_base_handle_t *) *port;

    hal_ll_gpio_clock_enable( *port );

    switch ( config ) {
        case GPIO_CFG_MODE_OUTPUT_PP:
            // Configure as output
            gpio_ptr->cr |= pin_mask;    // Enable Output
            gpio_ptr->ie &= ~pin_mask;   // Disable Input
            gpio_ptr->od &= ~pin_mask;   // Disable open drain
            gpio_ptr->pup &= ~pin_mask;  // Disable pull-up
            gpio_ptr->pdn &= ~pin_mask;  // Disable pull-down
            break;

        case GPIO_CFG_DIGITAL_INPUT:
            // Configure as input
            gpio_ptr->cr &= ~pin_mask;   // Disable Output
            gpio_ptr->ie |= pin_mask;    // Enable Input
            gpio_ptr->od &= ~pin_mask;   // Disable open drain
            gpio_ptr->pup &= ~pin_mask;  // Disable pull-up
            gpio_ptr->pdn &= ~pin_mask;  // Disable pull-down
            break;

        case GPIO_CFG_ANALOG_INPUT:
            // Configure as analog
            gpio_ptr->cr &= ~pin_mask;   // Disable Output
            gpio_ptr->ie &= ~pin_mask;   // Disable Input
            gpio_ptr->od &= ~pin_mask;   // Disable open drain
            gpio_ptr->pup &= ~pin_mask;  // Disable pull-up
            gpio_ptr->pdn &= ~pin_mask;  // Disable pull-down
            break;

        case GPIO_CFG_MODE_INPUT_PULLUP:
            // Configure as input with pull-up
            gpio_ptr->cr &= ~pin_mask;   // Disable Output
            gpio_ptr->ie |= pin_mask;    // Enable Input
            gpio_ptr->od &= ~pin_mask;   // Disable open drain
            gpio_ptr->pup |= pin_mask;   // Enable pull-up
            gpio_ptr->pdn &= ~pin_mask;  // Disable pull-down
            break;

        case GPIO_CFG_MODE_INPUT_PULLDOWN:
            // Configure as input with pull-down
            gpio_ptr->cr &= ~pin_mask;   // Disable Output
            gpio_ptr->ie |= pin_mask;    // Enable Input
            gpio_ptr->od &= ~pin_mask;   // Disable open drain
            gpio_ptr->pup &= ~pin_mask;  // Disable pull-up
            gpio_ptr->pdn |= pin_mask;   // Enable pull-down
            break;

        case GPIO_CFG_MODE_OUTPUT_OD:
            // Configure as output open
            gpio_ptr->cr |= pin_mask;    // Enable Output
            gpio_ptr->ie &= ~pin_mask;   // Disable Input
            gpio_ptr->od |= pin_mask;    // Enable open drain
            gpio_ptr->pup &= ~pin_mask;  // Disable pull-up
            gpio_ptr->pdn &= ~pin_mask;  // Disable pull-down
            break;

        default:
            // Do nothing
            break;
    }
}

static void hal_ll_gpio_config_pin_alternate_enable( uint32_t module_pin, uint32_t module_config, bool state ) {
    uint8_t                              pin_index;
    hal_ll_pin_name_t                    pin_name;
    hal_ll_port_name_t                   port_name;
    hal_ll_gpio_base_handle_t           *port_ptr;
    uint32_t                            *fr_register;
    hal_ll_gpio_alternate_function_t     alt_offset;

    uint32_t *fr_registers[] = { &port_ptr->fr1, &port_ptr->fr2, &port_ptr->fr3, &port_ptr->fr4,
                                 &port_ptr->fr5, &port_ptr->fr6, &port_ptr->fr7 };

    pin_name  = module_pin & GPIO_PIN_NAME_MASK;
    pin_index = hal_ll_gpio_pin_index( pin_name );
    port_name = hal_ll_gpio_port_index( module_pin & 0xFF );
    port_ptr  = (hal_ll_gpio_base_handle_t *) hal_ll_gpio_port_base( port_name );

    uint32_t mask = (uint32_t) ( 1 << pin_index );

    hal_ll_gpio_clock_enable( port_ptr );

    // Clear all FR registers for this pin
    for ( int i = 0; i < GPIO_ALTERNATE_FUNCTION_7; i++ ) {
        clear_reg_bit( fr_registers[i], pin_index );
    }

    alt_offset = ( ( module_pin & ~GPIO_PIN_NAME_MASK ) >> GPIO_AF_OFFSET );

    if ( state && ( alt_offset >= GPIO_ALTERNATE_FUNCTION_1 && alt_offset <= GPIO_ALTERNATE_FUNCTION_7 ) ) {
        switch ( alt_offset ) {
            case GPIO_ALTERNATE_FUNCTION_1:
                port_ptr->fr1 |= mask;
                break;

            case GPIO_ALTERNATE_FUNCTION_2:
                port_ptr->fr2 |= mask;
                break;

            case GPIO_ALTERNATE_FUNCTION_3:
                port_ptr->fr3 |= mask;
                break;

            case GPIO_ALTERNATE_FUNCTION_4:
                port_ptr->fr4 |= mask;
                break;

            case GPIO_ALTERNATE_FUNCTION_5:
                port_ptr->fr5 |= mask;
                break;

            case GPIO_ALTERNATE_FUNCTION_6:
                port_ptr->fr6 |= mask;
                break;

            case GPIO_ALTERNATE_FUNCTION_7:
                port_ptr->fr7 |= mask;
                break;
        }
    }
}

static void hal_ll_gpio_clock_enable( uint32_t port ) {
    uint32_t  port_index;
    uint32_t *sysma_addr   = (uint32_t *) HAL_LL_CG_BASE_FSYSMENA_ADDR;
    uint32_t *protect_addr = (uint32_t *) HAL_LL_CG_BASE_PROTECT_ADDR;

    set_reg_bits( protect_addr, PROTECT_DISABLE );

    port_index = hal_ll_gpio_get_port_number( port );

    switch ( port_index ) {
        case 0:
            set_reg_bit( sysma_addr, FSYSMENA_PORTA );
            break;

        case 1:
            set_reg_bit( sysma_addr, FSYSMENA_PORTB );
            break;

        case 2:
            set_reg_bit( sysma_addr, FSYSMENA_PORTC );
            break;

        case 3:
            set_reg_bit( sysma_addr, FSYSMENA_PORTD );
            break;

        case 4:
            set_reg_bit( sysma_addr, FSYSMENA_PORTE );
            break;

        case 5:
            set_reg_bit( sysma_addr, FSYSMENA_PORTF );
            break;

        case 6:
            set_reg_bit( sysma_addr, FSYSMENA_PORTG );
            break;

        case 7:
            set_reg_bit( sysma_addr, FSYSMENA_PORTH );
            break;
        case 8:
            set_reg_bit( sysma_addr, FSYSMENA_PORTJ );
            break;

        case 9:
            set_reg_bit( sysma_addr, FSYSMENA_PORTK );
            break;

        case 10:
            set_reg_bit( sysma_addr, FSYSMENA_PORTL );
            break;

        case 11:
            set_reg_bit( sysma_addr, FSYSMENA_PORTM );
            break;
        case 12:
            set_reg_bit( sysma_addr, FSYSMENA_PORTN );
            break;

        case 13:
            set_reg_bit( sysma_addr, FSYSMENA_PORTU );
            break;

        case 14:
            set_reg_bit( sysma_addr, FSYSMENA_PORTV );
            break;

        default:
            // Do nothing
            break;
    }
}

// ------------------------------------------------------------------------- END
