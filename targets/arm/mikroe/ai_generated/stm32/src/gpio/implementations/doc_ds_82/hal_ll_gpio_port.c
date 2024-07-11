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
 * @file  hal_ll_gpio_port.c
 * @brief GPIO HAL LOW LEVEL ported layer implementation.
 */

#include "hal_ll_gpio_port.h"
#include "hal_ll_rcc.h"

/**
 *  Defines used in source
 */
#define GPIOA_BASE_ADDR 0x48000000
#define GPIOB_BASE_ADDR 0x48000400
#define GPIOC_BASE_ADDR 0x48000800
#define GPIOD_BASE_ADDR 0x48000C00
#define GPIOE_BASE_ADDR 0x48001000
#define GPIOF_BASE_ADDR 0x48001400
#define GPIOG_BASE_ADDR 0x48001800

#define RCC_GPIOCLOCK   _RCC_AHB2ENR

#ifndef GPIOA_BASE_ADDR
    #define GPIOA_BASE_ADDR 0
#endif

#ifndef GPIOB_BASE_ADDR
    #define GPIOB_BASE_ADDR 0
#endif

#ifndef GPIOC_BASE_ADDR
    #define GPIOC_BASE_ADDR 0
#endif

#ifndef GPIOD_BASE_ADDR
    #define GPIOD_BASE_ADDR 0
#endif

#ifndef GPIOE_BASE_ADDR
    #define GPIOE_BASE_ADDR 0
#endif

#ifndef GPIOF_BASE_ADDR
    #define GPIOF_BASE_ADDR 0
#endif

#ifndef GPIOG_BASE_ADDR
    #define GPIOG_BASE_ADDR 0
#endif

static void hal_ll_gpio_config( uint32_t *port, uint16_t pin_mask, uint32_t config );

/*!< @brief GPIO PORT array */
static const uint32_t _hal_ll_gpio_port_base [ 7 ] =
{
    GPIOA_BASE_ADDR,
    GPIOB_BASE_ADDR,
    GPIOC_BASE_ADDR,
    GPIOD_BASE_ADDR,
    GPIOE_BASE_ADDR,
    GPIOF_BASE_ADDR,
    GPIOG_BASE_ADDR
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
static void _hal_ll_gpio_config( uint32_t *port, uint16_t pin_mask, uint32_t config );

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
    return ( ( uint32_t )0x01 << hal_ll_gpio_pin_index( name ) );
}

uint32_t hal_ll_gpio_port_base( hal_ll_port_name_t name )
{
    return _hal_ll_gpio_port_base[ name ];
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

    while ( module->pins[ index ] != GPIO_MODULE_STRUCT_END )
    {
        _hal_ll_gpio_config_pin_alternate_enable( module->pins[ index ], module->configs[ index ], state );

        index++;
    }
}

/**
  * @brief  Enable gpio port clock
  * @param  port - port base address
  * @return none
  */
static void hal_ll_gpio_clock_enable( uint32_t *port )
{
    uint32_t pos = 0;

    switch ( ( uint32_t )port & 0xFFFFFC00 )
    {
        #ifdef __PORT_A_CN
        case GPIOA_BASE_ADDR: pos = 0x01;   break;
        #endif
        #ifdef __PORT_B_CN
        case GPIOB_BASE_ADDR: pos = 0x02;   break;
        #endif
        #ifdef __PORT_C_CN
        case GPIOC_BASE_ADDR: pos = 0x04;   break;
        #endif
        #ifdef __PORT_D_CN
        case GPIOD_BASE_ADDR: pos = 0x08;   break;
        #endif
        #ifdef __PORT_E_CN
        case GPIOE_BASE_ADDR: pos = 0x10;   break;
        #endif
        #ifdef __PORT_F_CN
        case GPIOF_BASE_ADDR: pos = 0x20;   break;
        #endif
        #ifdef __PORT_G_CN
        case GPIOG_BASE_ADDR: pos = 0x40;   break;
        #endif
    }

    *(uint32_t *)RCC_GPIOCLOCK |= pos;
}

/**
  * @brief  Configure single port pins
  * @param  port     - port base address
  *         pin_mask - desired pin
  *         config   - pin settings
  * @return none
  */
static void hal_ll_gpio_config( uint32_t *port, uint16_t pin_mask, uint32_t config )
{
    uint32_t pin_pos       = 0;
    uint32_t pos           = 0;
    uint32_t current_pin   = 0;

    uint32_t mode          = 0;
    uint32_t speed         = 0;
    uint32_t otype         = 0;
    uint32_t pull          = 0;

    hal_ll_gpio_base_handle_t *port_ptr;

    port_ptr = ( hal_ll_gpio_base_handle_t *)port;

    hal_ll_gpio_clock_enable( port );

    if ( pin_mask == GPIO_PIN_MASK_LOW )
    {
        port_ptr->moder &= HAL_LL_NIBBLE_HIGH_32BIT;

        if ( config == GPIO_CFG_DIGITAL_OUTPUT )
        {
            port_ptr->moder |= 0x00005555;
            port_ptr->otyper &= 0xFFFFFF00;
            port_ptr->ospeedr |= HAL_LL_NIBBLE_LOW_32BIT;
            return;
        }
        if ( config == GPIO_CFG_DIGITAL_INPUT )
        {
            port_ptr->moder &= HAL_LL_NIBBLE_HIGH_32BIT;
            return;
        }
    }
    else if ( pin_mask == GPIO_PIN_MASK_HIGH )
    {
        port_ptr->moder &= HAL_LL_NIBBLE_LOW_32BIT;

        if ( config == GPIO_CFG_DIGITAL_OUTPUT )
        {
            port_ptr->moder |= 0x55550000;
            port_ptr->otyper &= 0xFFFF00FF;
            port_ptr->ospeedr |= HAL_LL_NIBBLE_HIGH_32BIT;
            return;
        }
        if ( config == GPIO_CFG_DIGITAL_INPUT )
        {
            port_ptr->moder &= HAL_LL_NIBBLE_LOW_32BIT;
            return;
        }
    }

    if ( pin_mask == GPIO_PIN_MASK_ALL )
    {
        if ( config == GPIO_CFG_DIGITAL_OUTPUT )
        {
            port_ptr->moder = 0x55555555;
            port_ptr->otyper = 0;
            port_ptr->ospeedr = HAL_LL_NIBBLE_HIGH_32BIT;
            return;
        }
        if ( config == GPIO_CFG_DIGITAL_INPUT )
        {
            port_ptr->moder = 0;
            return;
        }
    }

    if ( config & GPIO_CFG_MODE_ANALOG )
        mode = 3;
    else if ( config & GPIO_CFG_MODE_ALT_FUNCTION )
        mode = 2;
    else if ( config & GPIO_CFG_MODE_OUTPUT )
        mode = 1;
    else
        mode = 0;

    if ( config & ( GPIO_CFG_SPEED_VERY_HIGH ) )
        speed = 3;

    if ( config & ( GPIO_CFG_SPEED_HIGH ) )
        speed = 2;

    if ( config & ( GPIO_CFG_SPEED_MEDIUM ) )
        speed = 1;

    if ( config & ( GPIO_CFG_SPEED_LOW ) )
        speed = 0;

    if ( config & GPIO_CFG_OTYPE_OD )
        otype = 1;
    else
        otype = 0;

    if ( config & GPIO_CFG_PULL_DOWN )
        pull = 2;
    else if ( config & GPIO_CFG_PULL_UP )
        pull = 1;
    else
        pull = 0;

    for ( pin_pos = 0x00; pin_pos < 0x10; pin_pos++ )
    {
        pos = ( ( uint32_t ) 0x01 ) << pin_pos;
        current_pin = pin_mask & pos;

        if ( current_pin == pos )
        {
            port_ptr->moder &= ~( ( uint32_t )0x03 << ( pin_pos * 2 ) );
            port_ptr->moder |= ( ( ( uint32_t )mode ) << ( pin_pos * 2 ) );

            if ( config & ( GPIO_CFG_MODE_OUTPUT | GPIO_CFG_MODE_ALT_FUNCTION ) )
            {
                port_ptr->ospeedr &= ~( ( uint32_t )0x03 << ( pin_pos * 2 ) );
                port_ptr->ospeedr |= ( ( uint32_t )( speed ) << ( pin_pos * 2 ) );

                port_ptr->otyper &= ~( ( uint32_t )0x01 << ( ( uint16_t )pin_pos  ) ) ;
                port_ptr->otyper |= ( uint16_t )( ( ( uint16_t )otype ) << ( ( uint16_t )pin_pos  ) );
            }

            port_ptr->pupdr &= ~( ( uint32_t )0x03 << ( ( uint16_t )pin_pos * 2 ) );
            port_ptr->pupdr |= ( ( ( uint32_t )pull ) << ( pin_pos * 2 ) );

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
    hal_ll_pin_name_t pin_name;
    uint16_t pin_index;
    uint32_t alternate_function;
    hal_ll_gpio_base_handle_t *port_ptr;

    pin_name  = module_pin & GPIO_PIN_NAME_MASK;

    alternate_function = ( module_pin >> GPIO_AF_OFFSET ) & GPIO_AF_MASK;

    port_ptr = ( hal_ll_gpio_base_handle_t *)hal_ll_gpio_port_base( hal_ll_gpio_port_index ( pin_name ) );

    hal_ll_gpio_clock_enable( ( uint32_t *)port_ptr );

    pin_index = hal_ll_gpio_pin_index( pin_name );
    if ( pin_index > 7 )
    {
        pin_index -= 8;
        if ( state ) {
            port_ptr->afrh &= ~( ( uint32_t )( GPIO_AF_MASK ) << ( pin_index * 4 ) );
            port_ptr->afrh |= ( ( uint32_t )( alternate_function ) << ( pin_index * 4 ) );
        } else {
            port_ptr->afrh &= ~( ( uint32_t )( alternate_function ) << ( pin_index * 4 ) );
        }
    }
    else
    {
        if ( state ) {
            port_ptr->afrl &= ~( ( uint32_t )( GPIO_AF_MASK ) << ( pin_index * 4 ) );
            port_ptr->afrl |= ( ( uint32_t )( alternate_function ) << ( pin_index * 4 ) );
        } else {
            port_ptr->afrl &= ~( ( uint32_t )( alternate_function ) << ( pin_index * 4 ) );
        }
    }

    hal_ll_gpio_config( ( uint32_t*)port_ptr, hal_ll_gpio_pin_mask( pin_name ), module_config );
}
// ------------------------------------------------------------------------- END
