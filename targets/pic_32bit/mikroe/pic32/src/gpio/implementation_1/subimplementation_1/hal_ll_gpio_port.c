/****************************************************************************
**
** Copyright (C) 2024 MikroElektronika d.o.o.
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
** OF MERCHANTABILITY, EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED
** TO THE WARRANTIES FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT.
** IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM,
** DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT
** OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE
** OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
**
****************************************************************************/
/*!
 * @file hal_ll_gpio_port.c
 * @brief Low level HAL GPIO ported source file.
 */

#include "hal_ll_gpio_port.h"
#include "hal_ll_analog_in_map.h"

// ------------------------------------------------------------- PRIVATE MACROS

/**< @brief Utility macro for geting pin name based on port and bit for that pin on that port. */
#define HAL_LL_GET_PIN(port_name, pin_index) ( ( hal_ll_pin_name_t ) ( ( port_name << 0x04 ) + pin_index ) )

// -------------------------------------------------------------- PRIVATE TYPES

/**
 *  Defines used in source
 */
#ifndef PORTA_BASE_ADDRESS
    #define PORTA_BASE_ADDRESS NULL
    #define LATA_BASE_ADDRESS NULL
    #define TRISA_BASE_ADDRESS NULL
#endif
#ifndef PORTB_BASE_ADDRESS
    #define PORTB_BASE_ADDRESS NULL
    #define LATB_BASE_ADDRESS NULL
    #define TRISB_BASE_ADDRESS NULL
#endif
#ifndef PORTC_BASE_ADDRESS
    #define PORTC_BASE_ADDRESS NULL
    #define LATC_BASE_ADDRESS NULL
    #define TRISC_BASE_ADDRESS NULL
#endif
#ifndef PORTD_BASE_ADDRESS
    #define PORTD_BASE_ADDRESS NULL
    #define LATD_BASE_ADDRESS NULL
    #define TRISD_BASE_ADDRESS NULL
#endif
#ifndef PORTE_BASE_ADDRESS
    #define PORTE_BASE_ADDRESS NULL
    #define LATE_BASE_ADDRESS NULL
    #define TRISE_BASE_ADDRESS NULL
#endif
#ifndef PORTF_BASE_ADDRESS
    #define PORTF_BASE_ADDRESS NULL
    #define LATF_BASE_ADDRESS NULL
    #define TRISF_BASE_ADDRESS NULL
#endif
#ifndef PORTG_BASE_ADDRESS
    #define PORTG_BASE_ADDRESS NULL
    #define LATG_BASE_ADDRESS NULL
    #define TRISG_BASE_ADDRESS NULL
#endif
#ifndef PORTH_BASE_ADDRESS
    #define PORTH_BASE_ADDRESS NULL
    #define LATH_BASE_ADDRESS NULL
    #define TRISH_BASE_ADDRESS NULL
#endif
#ifndef PORTJ_BASE_ADDRESS
    #define PORTJ_BASE_ADDRESS NULL
    #define LATJ_BASE_ADDRESS NULL
    #define TRISJ_BASE_ADDRESS NULL
#endif
#ifndef PORTK_BASE_ADDRESS
    #define PORTK_BASE_ADDRESS NULL
    #define LATK_BASE_ADDRESS NULL
    #define TRISK_BASE_ADDRESS NULL
#endif

/*!< @brief GPIO PORT array */
static hal_ll_gpio_base_handle_t _hal_ll_gpio_port_addresses[ 10 ] =
{
    { PORTA_BASE_ADDRESS, LATA_BASE_ADDRESS, TRISA_BASE_ADDRESS },
    { PORTB_BASE_ADDRESS, LATB_BASE_ADDRESS, TRISB_BASE_ADDRESS },
    { PORTC_BASE_ADDRESS, LATC_BASE_ADDRESS, TRISC_BASE_ADDRESS },
    { PORTD_BASE_ADDRESS, LATD_BASE_ADDRESS, TRISD_BASE_ADDRESS },
    { PORTE_BASE_ADDRESS, LATE_BASE_ADDRESS, TRISE_BASE_ADDRESS },
    { PORTF_BASE_ADDRESS, LATF_BASE_ADDRESS, TRISF_BASE_ADDRESS },
    { PORTG_BASE_ADDRESS, LATG_BASE_ADDRESS, TRISG_BASE_ADDRESS },
    { PORTH_BASE_ADDRESS, LATH_BASE_ADDRESS, TRISH_BASE_ADDRESS },
    { PORTJ_BASE_ADDRESS, LATJ_BASE_ADDRESS, TRISJ_BASE_ADDRESS },
    { PORTK_BASE_ADDRESS, LATK_BASE_ADDRESS, TRISK_BASE_ADDRESS }
};

// ----------------------------------------------- PRIVATE FUNCTION DECLARATIONS

/**
  * @brief  Configure pin that has analog function.
  *
  * @param[in] pin - Desired pin.
  * @param[in] is_digital - Pin configuration( true = digital, false = analog ).
  * @return none
  */
static void hal_ll_gpio_port_configure_analog_pin( hal_ll_pin_name_t pin, bool is_digital );

/**
  * @brief  Configure port pins.
  *
  * @param[in]  port - Port base address.
  * @param[in]  pin - Desired single pin.
  * @param[in]  config - Pin settings.
  * @return     none
  */
static void hal_ll_gpio_port_config( uint32_t *port, hal_ll_pin_name_t pin, uint32_t config );

/**
  * @brief  Get pin index within a port.
  *
  * @param  name - Desired pin.
  * @return uint8_t value from 0 to PORT_SIZE-1.
  */
static uint16_t hal_ll_gpio_port_pin_index( hal_ll_pin_name_t name );

// ------------------------------------------------ PUBLIC FUNCTION DEFFINITIONS

uint8_t hal_ll_gpio_port_index( hal_ll_pin_name_t name ) {
    return ( uint8_t ) name / PORT_SIZE;
}

uint32_t hal_ll_gpio_port_pin_mask( hal_ll_pin_name_t name ) {
    return ( ( uint32_t ) 0x01 << hal_ll_gpio_port_pin_index( name ) );
}

uint32_t hal_ll_gpio_port_base_map( hal_ll_port_name_t name ) {
    return ( uint32_t ) &_hal_ll_gpio_port_addresses[ name ];
}

void hal_ll_gpio_port_analog_input( uint32_t *port, uint16_t pin_mask ) {
    hal_ll_gpio_port_config( port, pin_mask, GPIO_CFG_ANALOG_INPUT );
}

void hal_ll_gpio_port_digital_input( uint32_t *port, uint16_t pin_mask ) {
    hal_ll_gpio_port_config( port, pin_mask, GPIO_CFG_DIGITAL_INPUT );
}

void hal_ll_gpio_port_digital_configure_port( hal_ll_gpio_port_t *port, uint8_t port_name, bool is_input ) {
    static uint8_t adc_map_size;
    uint8_t count;
    uint8_t pin_index;

    hal_ll_gpio_base_handle_t *port_ptr = ( hal_ll_gpio_base_handle_t * ) port->base;
    clear_reg_bits( port_ptr->lat_reg_addr, port->mask );

    if ( is_input ) {
        set_reg_bits( port_ptr->tris_reg_addr, port->mask );
    } else {
        clear_reg_bits( port_ptr->tris_reg_addr, port->mask );
    }

    // Enable ad1pcfg flag for digital input.
    adc_map_size =  ( sizeof( hal_ll_analog_in_register_list ) / sizeof( hal_ll_pin_channel_list_t ) );

    for ( count=0; count < PORT_SIZE; count++ ) {
        if ( port->mask >> count ) {
            for ( pin_index = 0; pin_index < adc_map_size; pin_index++ ) {
                if ( hal_ll_analog_in_register_list[pin_index]->pin == HAL_LL_GET_PIN(port_name, count) ) {
                    // MX: set ad1pcfg bit flag to 1 making desired pin digital.
                    // MZ: clear ANSELx bit making desired pin digital.
                    MARK_AS_DIGITAL( hal_ll_analog_in_register_list[ pin_index ].analog_in_register_addr ,
                                     hal_ll_analog_in_register_list[ pin_index ].analog_in_register_bit );
                    break;
                }
            }
        }
    }
}

void hal_ll_gpio_port_digital_output( uint32_t *port, uint16_t pin ) {
    hal_ll_gpio_port_config( port, pin, GPIO_CFG_DIGITAL_OUTPUT );
}

// ------------------------------------------------ PRIVATE FUNCTION DEFINITIONS

static uint16_t hal_ll_gpio_port_pin_index( hal_ll_pin_name_t name ) {
    return ( uint16_t ) name % PORT_SIZE;
}

static void hal_ll_gpio_port_config( uint32_t *port, hal_ll_pin_name_t pin, uint32_t config ) {
    hal_ll_gpio_mask_t mask= hal_ll_gpio_port_pin_mask( pin );

    hal_ll_gpio_base_handle_t *port_ptr = ( hal_ll_gpio_base_handle_t * ) port;

    clear_reg_bits( port_ptr->lat_reg_addr, mask );

    if ( GPIO_CFG_DIGITAL_OUTPUT == config ) {
        clear_reg_bits( port_ptr->tris_reg_addr, mask );
        hal_ll_gpio_port_configure_analog_pin( pin, true );
        return;
    }
    if ( GPIO_CFG_DIGITAL_INPUT == config ) {
        set_reg_bits(port_ptr->tris_reg_addr, mask);
        hal_ll_gpio_port_configure_analog_pin(pin, true);
        return;
    }
    if ( GPIO_CFG_ANALOG_INPUT == config)  {
        set_reg_bits(port_ptr->tris_reg_addr, mask);
        hal_ll_gpio_port_configure_analog_pin(pin, false);
        return;
    }
}

static void hal_ll_gpio_port_configure_analog_pin( hal_ll_pin_name_t pin, bool is_digital )
{
    static uint8_t adc_map_size;
    static uint8_t pin_index = 0;

    adc_map_size = ( sizeof( hal_ll_analog_in_register_list ) / sizeof( hal_ll_pin_channel_list_t ) );

    //NOTE: no need to set TRISx to input since caller function takes care of that.
    for ( pin_index = 0; pin_index < adc_map_size; pin_index++ ) {
        if ( hal_ll_analog_in_register_list[pin_index].pin == pin ) {
            if ( is_digital ) {
                MARK_AS_DIGITAL( hal_ll_analog_in_register_list[ pin_index ].analog_in_register_addr,
                                 hal_ll_analog_in_register_list[ pin_index ].analog_in_register_bit );
                break;
            } else {
                MARK_AS_ANALOG( hal_ll_analog_in_register_list[ pin_index ].analog_in_register_addr,
                                hal_ll_analog_in_register_list[ pin_index ].analog_in_register_bit );
                break;
            }
        }
    }
}
// ------------------------------------------------------------------------- END
