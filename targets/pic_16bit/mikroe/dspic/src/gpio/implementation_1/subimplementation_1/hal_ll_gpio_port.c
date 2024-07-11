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
** OF MERCHANTABILITY, EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED
** TO THE WARRANTIES FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT.
** IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM,
** DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT
** OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE
** OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
**
****************************************************************************/
/*!
 * @file hal_ll_port_gpio.c
 * @brief Low level HAL GPIO ported source file.
 */

#include "hal_ll_gpio_port.h"
#include "hal_ll_analog_in_map.h"

// ------------------------------------------------------------- PRIVATE MACROS

// -------------------------------------------------------------- PRIVATE TYPES

/**
 *  Defines used in source
 */

/*!< @brief GPIO PORT null-pointer constants (for non-existant ports) */
#ifndef __PORT_A_CN
    #define PORTA_REG_ADDRESS NULL
    #define LATA_REG_ADDRESS NULL
    #define TRISA_REG_ADDRESS NULL
#endif
#ifndef __PORT_B_CN
    #define PORTB_REG_ADDRESS NULL
    #define LATB_REG_ADDRESS NULL
    #define TRISB_REG_ADDRESS NULL
#endif
#ifndef __PORT_C_CN
    #define PORTC_REG_ADDRESS NULL
    #define LATC_REG_ADDRESS NULL
    #define TRISC_REG_ADDRESS NULL
#endif
#ifndef __PORT_D_CN
    #define PORTD_REG_ADDRESS NULL
    #define LATD_REG_ADDRESS NULL
    #define TRISD_REG_ADDRESS NULL
#endif
#ifndef __PORT_E_CN
    #define PORTE_REG_ADDRESS NULL
    #define LATE_REG_ADDRESS NULL
    #define TRISE_REG_ADDRESS NULL
#endif
#ifndef __PORT_F_CN
    #define PORTF_REG_ADDRESS NULL
    #define LATF_REG_ADDRESS NULL
    #define TRISF_REG_ADDRESS NULL
#endif
#ifndef __PORT_G_CN
    #define PORTG_REG_ADDRESS NULL
    #define LATG_REG_ADDRESS NULL
    #define TRISG_REG_ADDRESS NULL
#endif
#ifndef __PORT_H_CN
    #define PORTH_REG_ADDRESS NULL
    #define LATH_REG_ADDRESS NULL
    #define TRISH_REG_ADDRESS NULL
#endif
#ifndef __PORT_J_CN
    #define PORTJ_REG_ADDRESS NULL
    #define LATJ_REG_ADDRESS NULL
    #define TRISJ_REG_ADDRESS NULL
#endif
#ifndef __PORT_K_CN
    #define PORTK_REG_ADDRESS NULL
    #define LATK_REG_ADDRESS NULL
    #define TRISK_REG_ADDRESS NULL
#endif

/*!< @brief GPIO PORT array */
static hal_ll_gpio_base_handle_t _hal_ll_gpio_port_addresses[ ] = {
    { PORTA_REG_ADDRESS, LATA_REG_ADDRESS, TRISA_REG_ADDRESS },
    { PORTB_REG_ADDRESS, LATB_REG_ADDRESS, TRISB_REG_ADDRESS },
    { PORTC_REG_ADDRESS, LATC_REG_ADDRESS, TRISC_REG_ADDRESS },
    { PORTD_REG_ADDRESS, LATD_REG_ADDRESS, TRISD_REG_ADDRESS },
    { PORTE_REG_ADDRESS, LATE_REG_ADDRESS, TRISE_REG_ADDRESS },
    { PORTF_REG_ADDRESS, LATF_REG_ADDRESS, TRISF_REG_ADDRESS },
    { PORTG_REG_ADDRESS, LATG_REG_ADDRESS, TRISG_REG_ADDRESS },
    { PORTH_REG_ADDRESS, LATH_REG_ADDRESS, TRISH_REG_ADDRESS },
    { PORTJ_REG_ADDRESS, LATJ_REG_ADDRESS, TRISJ_REG_ADDRESS },
    { PORTK_REG_ADDRESS, LATK_REG_ADDRESS, TRISK_REG_ADDRESS },

    { HAL_LL_PORT_NC, HAL_LL_PORT_NC, HAL_LL_PORT_NC }
};

/**
  * @brief  Configure pin that has analog function
  *
  * @param[in] pin - desired pin
  * @param[in] is_digital - pin configuration( true = digital, false = analog )
  * @param[in] map - analog pin configuration structure
  * @return none
  */
static void hal_ll_gpio_port_configure_analog_pin( hal_ll_pin_name_t pin, bool is_digital, hal_ll_pin_channel_list_t *map );

/**
  * @brief  Configure port pins
  * @param[in] name - port base address
  * @param[in] pin_mask - desired pin
  * @param[in] config - pin settings
  * @return none
  */
static void hal_ll_gpio_port_config( uint16_t *name, uint16_t pin_mask, uint16_t config );

/**
  * @brief  Set pin as analog input
  * @param[in] pin - pin index
  * @param[in] bit_mask - bit mask
  * @param[in] map - analog pin configuration structure
  * @note clear desired bits of ANSx or ANSELx registers
  * @return none
  */
static void hal_ll_gpio_set_ans( uint8_t pin, hal_ll_pin_channel_list_t *map, uint16_t bit_mask );

/**
  * @brief  Set pin as analog input
  * @param[in] pin - pin index
  * @param[in] bit_mask - bit mask
  * @param[in] map - analog pin configuration structure
  * @note set desired bits of ADPCFG or ADxPCFGx registers
  * @return none
  */
static void hal_ll_gpio_set_adpcfg( uint8_t pin, hal_ll_pin_channel_list_t *map, uint16_t bit_mask );

/**
  * @brief  Get pin index within a port
  * @param[in] name - desired pin
  * @return uint8_t value from 0 to PORT_SIZE-1
  */
static uint8_t hal_ll_gpio_port_pin_index( hal_ll_pin_name_t name ) {
    return ( uint16_t ) name % PORT_SIZE;
}

/**
  * @brief  Get pins port index within a list of available ports
  * @param[in] name - desired pin
  * @return uint8_t value from 0 to PORT_COUNT-1
  */
uint8_t hal_ll_gpio_port_index( hal_ll_pin_name_t name ) {
    return ( uint16_t ) name / PORT_SIZE;
}

/**
  * @brief  Get pin mask of provided pin within proprietery port
  * @param[in] name - desired pin
  * @return uint16_t
  */
uint16_t hal_ll_gpio_port_pin_mask( hal_ll_pin_name_t name ) {
    return ( 0x1UL << hal_ll_gpio_port_pin_index ( name ) );
}

/**
  * @brief  Get map address of port register offsets
  * @param[in] name - desired port
  * @return uint16_t address of first register
  */
uint16_t hal_ll_gpio_port_base_map( hal_ll_port_name_t name ) {
     return ( uint16_t ) &_hal_ll_gpio_port_addresses [ name ];
}

/**
  * @brief  Set pin as analog input
  * @param[in] port - port base address acquired from hal_gpio_ll_port_base
  * @param[in] pin_mask - pin mask acquired from hal_gpio_ll_pin_mask
  * @return none
  */
void hal_ll_gpio_port_analog_input( uint16_t *port, uint16_t pin_mask ) {
    hal_ll_gpio_port_config( port, pin_mask, GPIO_CFG_ANALOG_INPUT );
}

/**
  * @brief  Set pin as digital input
  * @param[in] port - port base address acquired from hal_gpio_ll_port_base
  * @param[in] pin_mask - pin mask acquired from hal_gpio_ll_pin_mask
  * @return none
  */
void hal_ll_gpio_port_digital_input( uint16_t *port, uint16_t pin_mask ) {
     hal_ll_gpio_port_config( port, pin_mask, GPIO_CFG_DIGITAL_INPUT );
}

void hal_ll_gpio_port_digital_configure_port( hal_ll_gpio_port_t *port, uint8_t name, bool is_input ) {
    static const uint8_t adc_map_size = ( sizeof( hal_ll_analog_in_register_list ) / sizeof( hal_ll_pin_channel_list_t ) );
    uint8_t pin_index;
    uint8_t pin;

    hal_ll_gpio_base_handle_t *port_ptr = ( hal_ll_gpio_base_handle_t * )port->base;

    if ( is_input ) {
        *( uint16_t * )port_ptr->tris_reg_addr |= port->mask;
    } else {
        *( uint16_t * )port_ptr->tris_reg_addr &= ~( port->mask );
    }

    for ( pin_index = 0; pin_index < adc_map_size; pin_index++ ) {
        if ( hal_ll_gpio_port_index( hal_ll_analog_in_register_list[pin_index].pin ) == name ) {
            hal_ll_gpio_port_configure_analog_pin( hal_ll_analog_in_register_list[pin_index].pin, true, &hal_ll_analog_in_register_list[pin_index] );
        }
    }
}

/**
  * @brief  Set pin as digital output
  * @param[in] port - port base address acquired from hal_gpio_ll_port_base
  * @param[in] pin_mask - pin mask acquired from hal_gpio_ll_pin_mask
  * @return none
  */
void hal_ll_gpio_port_digital_output( uint16_t *port, uint8_t pin ) {
    hal_ll_gpio_port_config( port, pin, GPIO_CFG_DIGITAL_OUTPUT );
}

/**
  * @brief  Configure single port pins
  * @param[in] port - port base address
  * @param[in] pin - desired pin
  * @param[in] config - pin settings
  * @return none
  */
static void hal_ll_gpio_port_config( uint16_t *port, uint16_t pin, uint16_t config ) {
    hal_ll_port_name_t mask = hal_ll_gpio_port_pin_mask( pin & PORT_PIN_MASK );
    hal_ll_gpio_base_handle_t *port_ptr = ( hal_ll_gpio_base_handle_t * )port;

    if ( GPIO_CFG_DIGITAL_OUTPUT == config ) {
        *( uint16_t * )port_ptr->tris_reg_addr &= ~mask;
        hal_ll_gpio_port_configure_analog_pin( pin, true, NULL );
        return;
    } else if ( GPIO_CFG_DIGITAL_INPUT == config ) {
        *( uint16_t * )port_ptr->tris_reg_addr |= mask;
        hal_ll_gpio_port_configure_analog_pin( pin, true, NULL );
        return;
    } else {
        *( uint16_t * )port_ptr->tris_reg_addr |= mask;
        hal_ll_gpio_port_configure_analog_pin( pin, false, NULL );
        return;
    }
}

static void hal_ll_gpio_port_configure_analog_pin( hal_ll_pin_name_t pin, bool is_digital, hal_ll_pin_channel_list_t *map ) {
    uint8_t pin_index = 0;
    static const uint8_t adc_map_size = ( sizeof( hal_ll_analog_in_register_list ) / sizeof( hal_ll_pin_channel_list_t ) );
    volatile uint16_t reg_value;
    uint16_t bit_value;

    if ( map ) {
        if ( map->analog_write_value ) {
            bit_value = 1 << map->analog_in_register_bit;
            if ( is_digital ) {
                bit_value = ~bit_value;
                hal_ll_gpio_set_ans( pin_index, map, bit_value );
            } else {
                hal_ll_gpio_set_adpcfg( pin_index, map, bit_value );
            }
        } else {
            bit_value = ~( 1 << map->analog_in_register_bit );
            if ( is_digital ) {
                bit_value = ~bit_value;
                hal_ll_gpio_set_adpcfg( pin_index, map, bit_value );
            } else {
                hal_ll_gpio_set_adpcfg( pin_index, map, bit_value );
            }
        }
    } else {
        for ( pin_index = 0; pin_index < adc_map_size; pin_index++ ) {
            if ( hal_ll_analog_in_register_list[pin_index].pin == pin ) {
                if ( hal_ll_analog_in_register_list[pin_index].analog_write_value ) {
                    bit_value = 1 << hal_ll_analog_in_register_list[ pin_index ].analog_in_register_bit;
                    if ( is_digital ) {
                        hal_ll_gpio_set_ans( pin_index, &hal_ll_analog_in_register_list[pin_index], ~bit_value );
                    } else {
                        hal_ll_gpio_set_adpcfg( pin_index, &hal_ll_analog_in_register_list[pin_index], bit_value );
                    }
                } else {
                    bit_value = ~( 1 << hal_ll_analog_in_register_list[ pin_index ].analog_in_register_bit );
                    if ( is_digital ) {
                        hal_ll_gpio_set_adpcfg( pin_index, &hal_ll_analog_in_register_list[pin_index], ~bit_value );
                    } else {
                        hal_ll_gpio_set_ans( pin_index, &hal_ll_analog_in_register_list[pin_index], bit_value );
                    }
                }
            }
        }
    }
}

static void hal_ll_gpio_set_ans( uint8_t pin, hal_ll_pin_channel_list_t *map, uint16_t bit_mask ) {
    volatile uint16_t reg_value;

    reg_value = read_reg( map->analog_in_register_addresses.address[0] );
    write_reg( map->analog_in_register_addresses.address[0], reg_value & bit_mask );
    if ( NULL != map->analog_in_register_addresses.address[1] ) {
        reg_value = read_reg( map->analog_in_register_addresses.address[1] );
        write_reg( map->analog_in_register_addresses.address[1], reg_value & bit_mask );
    }
}

static void hal_ll_gpio_set_adpcfg( uint8_t pin, hal_ll_pin_channel_list_t *map, uint16_t bit_mask ) {
    volatile uint16_t reg_value;

    reg_value = read_reg( map->analog_in_register_addresses.address[0] & ~bit_mask );
    write_reg( map->analog_in_register_addresses.address[0], reg_value | bit_mask );
    if ( NULL != map->analog_in_register_addresses.address[1] ) {
        reg_value = read_reg( map->analog_in_register_addresses.address[1] & ~bit_mask );
        write_reg( map->analog_in_register_addresses.address[1], reg_value | bit_mask );
    }
}
// ------------------------------------------------------------------------- END
