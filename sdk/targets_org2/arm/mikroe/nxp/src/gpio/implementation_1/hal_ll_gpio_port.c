/****************************************************************************
**
** Copyright (C) 2023 MikroElektronika d.o.o.
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
 * @file  hal_ll_gpio_port.c
 * @brief GPIO HAL LOW LEVEL ported layer implementation.
 */

#include "hal_ll_gpio_port.h"
#include "hal_ll_rcc.h"

/**
 *  Defines used in source
 */
#define NIBBLE_MASK_HIGH        0xFFFF0000UL
#define NIBBLE_MASK_LOW         0x0000FFFFUL

#define PORT_PCR_MUX_MASK       0x700UL
#define RCC_GPIOCLOCK           _SIM_SCGC5

#define GPIOA_BASE_ADDR         0x400FF000UL
#define GPIOB_BASE_ADDR         0x400FF040UL
#define GPIOC_BASE_ADDR         0x400FF080UL
#define GPIOD_BASE_ADDR         0x400FF0C0UL
#define GPIOE_BASE_ADDR         0x400FF100UL

#define PORTA_PCR_ADDR          0x40049000UL
#define PORTB_PCR_ADDR          0x4004A000UL
#define PORTC_PCR_ADDR          0x4004B000UL
#define PORTD_PCR_ADDR          0x4004C000UL
#define PORTE_PCR_ADDR          0x4004D000UL

#define GPIO_PCR_BASE_VALUE     0x40049000UL
#define GPIO_PCR_OFFSET_VALUE   0x1000UL

/*!< @brief GPIO PORT array */
static const uint32_t _hal_ll_gpio_port_base[ PORT_COUNT + 1 ] =
{
    #ifdef __PORT_A_CN
    GPIOA_BASE_ADDR,
    #endif
    #ifdef __PORT_B_CN
    GPIOB_BASE_ADDR,
    #endif
    #ifdef __PORT_C_CN
    GPIOC_BASE_ADDR,
    #endif
    #ifdef __PORT_D_CN
    GPIOD_BASE_ADDR,
    #endif
    #ifdef __PORT_E_CN
    GPIOE_BASE_ADDR,
    #endif

    HAL_LL_PORT_NC
};

/**
  * @brief  Enable gpio port clock
  * @param  port - port base address
  * @return none
  */
static void _hal_ll_gpio_clock_enable( uint32_t *port );

/**
  * @brief  Configure port pins
  * @param  port     - port base address
  *         pin_mask - desired pin
  *         config   - pin settings
  * @return none
  */
static void _hal_ll_gpio_config( uint32_t *port, uint32_t pin_mask, uint32_t config );

/**
  * @brief  Configure port pins alternate
  *         functions
  * @param  module_pin - desired pin
  *         config     - pin settings
  * @return none
  */
static void _hal_ll_gpio_config_pin_alternate_enable( uint32_t module_pin, uint32_t module_config, bool state );

static uint8_t hal_ll_gpio_pin_index( hal_ll_pin_name_t name )
{
    return ( uint8_t )name % PORT_SIZE;
}

uint8_t hal_ll_gpio_port_index( hal_ll_pin_name_t name )
{
    return ( uint8_t )name / PORT_SIZE;
}

uint32_t hal_ll_gpio_pin_mask( hal_ll_pin_name_t name )
{
    return ( 1UL << hal_ll_gpio_pin_index( name ) );
}

uint32_t hal_ll_gpio_port_base( hal_ll_port_name_t name )
{
    return _hal_ll_gpio_port_base[ name ];
}

void hal_ll_gpio_analog_input( uint32_t *port, uint32_t pin_mask )
{
    _hal_ll_gpio_config( port, pin_mask, GPIO_CFG_ANALOG_INPUT );
}

void hal_ll_gpio_digital_input( uint32_t *port, uint32_t pin_mask )
{
    _hal_ll_gpio_config( port, pin_mask, GPIO_CFG_DIGITAL_INPUT );
}

void hal_ll_gpio_digital_output( uint32_t *port, uint32_t pin_mask )
{
    _hal_ll_gpio_config( port, pin_mask, GPIO_CFG_DIGITAL_OUTPUT );
}

void hal_ll_gpio_module_struct_init( module_struct const *module, bool state )
{
    uint8_t index = 0;

    while ( module->pins[ index ] != GPIO_MODULE_STRUCT_END ) {
        _hal_ll_gpio_config_pin_alternate_enable( module->pins[ index ], module->configs[ index ], state );
        index++;
    }
}

/**
  * @brief  Enable gpio port clock
  * @param  port - port base address
  * @return none
  */
static void hal_ll_gpio_clock_enable( uint32_t port, uint32_t* port_pcr_base_addr )
{
    uint32_t pos = 0;

    switch ( port )
    {
        case GPIOA_BASE_ADDR:
            pos = 9;
            *port_pcr_base_addr = PORTA_PCR_ADDR;
            break;
        case GPIOB_BASE_ADDR:
            pos = 10;
            *port_pcr_base_addr = PORTB_PCR_ADDR;
            break;
        case GPIOC_BASE_ADDR:
            pos = 11;
            *port_pcr_base_addr = PORTC_PCR_ADDR;
            break;
        case GPIOD_BASE_ADDR:
            pos = 12;
            *port_pcr_base_addr = PORTD_PCR_ADDR;
            break;
        case GPIOE_BASE_ADDR:
            pos = 13;
            *port_pcr_base_addr = PORTE_PCR_ADDR;
            break;

        default:
            return;
    }

    *RCC_GPIOCLOCK |= ( 1UL << pos );
}

/**
  * @brief  Configure single port pins
  * @param  port     - port base address
  *         pin_mask - desired pin
  *         config   - pin settings
  * @return none
  */
static void _hal_ll_gpio_config( uint32_t *port, uint32_t pin_mask, uint32_t config )
{
    uint8_t  pin_num     = 0;
    uint32_t pin_pos     = 0;
    uint32_t current_pin = 0;
    uint32_t port_base   = 0;

    hal_ll_gpio_pcr_base_array_t *port_pcr_array;
    hal_ll_gpio_base_handle_t *gpio_ptr = ( hal_ll_gpio_base_handle_t* )( *port );

    hal_ll_gpio_clock_enable( *port, &port_base );

    port_pcr_array = ( hal_ll_gpio_pcr_base_handle_t* )port_base;

    for ( pin_num = 0; pin_num < 32; pin_num++ ) {
        pin_pos = 1UL << pin_num;
        current_pin = pin_mask & pin_pos;

        // Check if current pin position matches loop number
        if ( current_pin == pin_pos ) {
            // Set analog by default
            port_pcr_array->pcr_index_of[ pin_num ] &= NIBBLE_MASK_HIGH;
            port_pcr_array->pcr_index_of[ pin_num ] |= ( config & NIBBLE_MASK_LOW );

            // Check if it is a digital signal or alternate function
            if ( ( config & GPIO_CFG_MODE_ANALOG ) != GPIO_CFG_MODE_ANALOG ) {
                // Set gpio direction input
                if ( config & GPIO_CFG_MODE_INPUT ) {
                    port_pcr_array->pcr_index_of[ pin_num ] |= GPIO_CFG_PULL_ENABLE;
                    gpio_ptr->pddr &= ~current_pin;
                } else {
                    gpio_ptr->pddr |= current_pin;
                }
            }
        }
    }
}

/**
  * @brief  Configure port pins alternate
  *         functions
  * @param  module_pin - desired pin
  *         config     - pin settings
  * @return none
  */
static void _hal_ll_gpio_config_pin_alternate_enable( uint32_t module_pin, uint32_t module_config, bool state )
{
    uint8_t pin_index;
    hal_ll_pin_name_t pin_name;
    hal_ll_port_name_t port_name;
    hal_ll_gpio_base_handle_t *port_ptr;
    hal_ll_gpio_pcr_base_array_t *port_pcr_array;

    pin_name = module_pin & GPIO_PIN_NAME_MASK;

    pin_index = hal_ll_gpio_pin_index( pin_name );

    port_name = hal_ll_gpio_port_index( module_pin & 0xFF );

    port_ptr = ( hal_ll_gpio_base_handle_t* )hal_ll_gpio_port_base( port_name );

    port_pcr_array = ( hal_ll_gpio_pcr_base_handle_t* )( GPIO_PCR_BASE_VALUE + port_name * GPIO_PCR_OFFSET_VALUE );

    _hal_ll_gpio_config( (uint32_t *)&port_ptr, hal_ll_gpio_pin_mask( pin_index ), module_config );

    if ( true == state ) {
        port_pcr_array->pcr_index_of[ pin_index ] |= module_pin & PORT_PCR_MUX_MASK;
    } else {
        port_pcr_array->pcr_index_of[ pin_index ] &= ~( module_pin & PORT_PCR_MUX_MASK );
    }
}
// ------------------------------------------------------------------------- END
