/****************************************************************************
**
** Copyright (C) 2020 MikroElektronika d.o.o.
** Contact: https://www.mikroe.com/contact
**
** This file is part of the mikroSDK package
**
** Commercial License Usage
**
** Licensees holding valid commercial NECTO compilers AI licenses may use this
** file in accordance with the commercial license agreement provided with the
** Software or, alternatively, in accordance with the terms contained in
** a written agreement between you and The mikroElektronika Company.
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

#if defined(STM32F03x) || defined(STM32F04x) || defined(STM32F05x) || \
    defined(STM32F07x) || defined(STM32F09x)
    #define GPIOA_BASE_ADDR 0x48000000
    #define GPIOB_BASE_ADDR 0x48000400
    #define GPIOC_BASE_ADDR 0x48000800
    #define GPIOD_BASE_ADDR 0x48000C00
    #define GPIOE_BASE_ADDR 0x48001000
    #define GPIOF_BASE_ADDR 0x48001400
    #define RCC_GPIOCLOCK   _RCC_AHBENR
#endif

#if defined(STM32G0xx)
    #define GPIOA_BASE_ADDR 0x50000000
    #define GPIOB_BASE_ADDR 0x50000400
    #define GPIOC_BASE_ADDR 0x50000800
    #define GPIOD_BASE_ADDR 0x50000C00
    #define GPIOF_BASE_ADDR 0x50001400
    #define RCC_GPIOCLOCK   _RCC_IOPENR
#endif

#if defined(STM32L01x) || defined(STM32L02x) || defined(STM32L03x) || \
    defined(STM32L04x) || defined(STM32L05x) || defined(STM32L06x) || \
    defined(STM32L07x) || defined(STM32L08x)
    #define GPIOA_BASE_ADDR 0x50000000
    #define GPIOB_BASE_ADDR 0x50000400
    #define GPIOC_BASE_ADDR 0x50000800
    #define GPIOD_BASE_ADDR 0x50000C00
    #define GPIOE_BASE_ADDR 0x50001000
    #define GPIOH_BASE_ADDR 0x50001C00
    #define RCC_GPIOCLOCK   _RCC_IOPENR
#endif

#if defined(STM32F2xx)
    #define GPIOA_BASE_ADDR 0x40020000
    #define GPIOB_BASE_ADDR 0x40020400
    #define GPIOC_BASE_ADDR 0x40020800
    #define GPIOD_BASE_ADDR 0x40020C00
    #define GPIOE_BASE_ADDR 0x40021000
    #define GPIOF_BASE_ADDR 0x40021400
    #define GPIOG_BASE_ADDR 0x40021800
    #define GPIOH_BASE_ADDR 0x40021C00
    #define GPIOI_BASE_ADDR 0x40022000
    #define RCC_GPIOCLOCK _RCC_AHB1ENR
#endif

#if defined(STM32L1xx)
    #define GPIOA_BASE_ADDR 0x40020000
    #define GPIOB_BASE_ADDR 0x40020400
    #define GPIOC_BASE_ADDR 0x40020800
    #define GPIOD_BASE_ADDR 0x40020C00
    #define GPIOE_BASE_ADDR 0x40021000
    #define GPIOF_BASE_ADDR 0x40021800
    #define GPIOG_BASE_ADDR 0x40021C00
    #define GPIOH_BASE_ADDR 0x40021400
    #define RCC_GPIOCLOCK _RCC_AHBENR
#endif

#if defined(STM32F3xx)
    #define GPIOA_BASE_ADDR 0x48000000
    #define GPIOB_BASE_ADDR 0x48000400
    #define GPIOC_BASE_ADDR 0x48000800
    #define GPIOD_BASE_ADDR 0x48000C00
    #define GPIOE_BASE_ADDR 0x48001000
    #define GPIOF_BASE_ADDR 0x48001400
    #define GPIOG_BASE_ADDR 0x48001800
    #define GPIOH_BASE_ADDR 0x48001C00
    #define RCC_GPIOCLOCK _RCC_AHBENR
#endif

#if defined(STM32F4xx)
    #define GPIOA_BASE_ADDR 0x40020000
    #define GPIOB_BASE_ADDR 0x40020400
    #define GPIOC_BASE_ADDR 0x40020800
    #define GPIOD_BASE_ADDR 0x40020C00
    #define GPIOE_BASE_ADDR 0x40021000
    #define GPIOF_BASE_ADDR 0x40021400
    #define GPIOG_BASE_ADDR 0x40021800
    #define GPIOH_BASE_ADDR 0x40021C00
    #define GPIOI_BASE_ADDR 0x40022000
    #define GPIOJ_BASE_ADDR 0x40022400
    #define GPIOK_BASE_ADDR 0x40022800
    #define RCC_GPIOCLOCK _RCC_AHB1ENR
#endif

#if defined(STM32L4xx)
    #define GPIOA_BASE_ADDR 0x48000000
    #define GPIOB_BASE_ADDR 0x48000400
    #define GPIOC_BASE_ADDR 0x48000800
    #define GPIOD_BASE_ADDR 0x48000C00
    #define GPIOE_BASE_ADDR 0x48001000
    #define GPIOF_BASE_ADDR 0x48001400
    #define GPIOG_BASE_ADDR 0x48001800
    #define GPIOH_BASE_ADDR 0x48001C00
    #define GPIOI_BASE_ADDR 0x48002000
    #define RCC_GPIOCLOCK _RCC_AHB2ENR
#endif

#if defined(STM32F7xx)
    #define GPIOA_BASE_ADDR 0x40020000
    #define GPIOB_BASE_ADDR 0x40020400
    #define GPIOC_BASE_ADDR 0x40020800
    #define GPIOD_BASE_ADDR 0x40020C00
    #define GPIOE_BASE_ADDR 0x40021000
    #define GPIOF_BASE_ADDR 0x40021400
    #define GPIOG_BASE_ADDR 0x40021800
    #define GPIOH_BASE_ADDR 0x40021C00
    #define GPIOI_BASE_ADDR 0x40022000
    #define GPIOJ_BASE_ADDR 0x40022400
    #define GPIOK_BASE_ADDR 0x40022800
    #define RCC_GPIOCLOCK _RCC_AHB1ENR
#endif

#if defined(STM32H7xx)
    #define GPIOA_BASE_ADDR 0x58020000
    #define GPIOB_BASE_ADDR 0x58020400
    #define GPIOC_BASE_ADDR 0x58020800
    #define GPIOD_BASE_ADDR 0x58020C00
    #define GPIOE_BASE_ADDR 0x58021000
    #define GPIOF_BASE_ADDR 0x58021400
    #define GPIOG_BASE_ADDR 0x58021800
    #define GPIOH_BASE_ADDR 0x58021C00
    #define GPIOI_BASE_ADDR 0x58022000
    #define GPIOJ_BASE_ADDR 0x58022400
    #define GPIOK_BASE_ADDR 0x58022800
    #define RCC_GPIOCLOCK _RCC_AHB4ENR
#endif

#ifndef GPIOA_BASE_ADDR
    #define GPIOA_BASE_ADDR NULL
#endif
#ifndef GPIOB_BASE_ADDR
    #define GPIOB_BASE_ADDR NULL
#endif
#ifndef GPIOC_BASE_ADDR
    #define GPIOC_BASE_ADDR NULL
#endif
#ifndef GPIOD_BASE_ADDR
    #define GPIOD_BASE_ADDR NULL
#endif
#ifndef GPIOE_BASE_ADDR
    #define GPIOE_BASE_ADDR NULL
#endif
#ifndef GPIOF_BASE_ADDR
    #define GPIOF_BASE_ADDR NULL
#endif
#ifndef GPIOG_BASE_ADDR
    #define GPIOG_BASE_ADDR NULL
#endif
#ifndef GPIOH_BASE_ADDR
    #define GPIOH_BASE_ADDR NULL
#endif
#ifndef GPIOI_BASE_ADDR
    #define GPIOI_BASE_ADDR NULL
#endif
#ifndef GPIOJ_BASE_ADDR
    #define GPIOJ_BASE_ADDR NULL
#endif
#ifndef GPIOK_BASE_ADDR
    #define GPIOK_BASE_ADDR NULL
#endif

static void hal_ll_gpio_config( uint32_t *port, uint16_t pin_mask, uint32_t config );

/*!< @brief GPIO PORT array */
static const uint32_t _hal_ll_gpio_port_base [ 11 ] =
{
    GPIOA_BASE_ADDR,
    GPIOB_BASE_ADDR,
    GPIOC_BASE_ADDR,
    GPIOD_BASE_ADDR,
    GPIOE_BASE_ADDR,
    GPIOF_BASE_ADDR,
    GPIOG_BASE_ADDR,
    GPIOH_BASE_ADDR,
    GPIOI_BASE_ADDR,
    GPIOJ_BASE_ADDR,
    GPIOK_BASE_ADDR
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
    case GPIOA_BASE_ADDR: pos = 0x1;   break;
    #endif
    #ifdef __PORT_B_CN
    case GPIOB_BASE_ADDR: pos = 0x2;   break;
    #endif
    #ifdef __PORT_C_CN
    case GPIOC_BASE_ADDR: pos = 0x4;   break;
    #endif
    #ifdef __PORT_D_CN
    case GPIOD_BASE_ADDR: pos = 0x8;   break;
    #endif
    #ifdef __PORT_E_CN
    case GPIOE_BASE_ADDR: pos = 0x10;  break;
    #endif
    #ifdef __PORT_F_CN
    case GPIOF_BASE_ADDR: pos = 0x20;  break;
    #endif
    #ifdef __PORT_G_CN
    case GPIOG_BASE_ADDR: pos = 0x40;  break;
    #endif
    #ifdef __PORT_H_CN
    case GPIOH_BASE_ADDR: pos = 0x80;  break;
    #endif
    #ifdef __PORT_I_CN
    case GPIOI_BASE_ADDR: pos = 0x100; break;
    #endif
    #ifdef __PORT_J_CN
    case GPIOJ_BASE_ADDR: pos = 0x200; break;
    #endif
    #ifdef __PORT_K_CN
    case GPIOK_BASE_ADDR: pos = 0x400; break;
    #endif
  }

  #if defined(STM32F3xx) || defined(STM32F0xx)
  *(uint32_t *)RCC_GPIOCLOCK |= ( uint32_t )pos << GPIO_AHB_SHIFT;
  #else
  *(uint32_t *)RCC_GPIOCLOCK |= pos;
  #endif
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
        port_ptr->moder &= 0xFFFF0000;
        if ( config == GPIO_CFG_DIGITAL_OUTPUT )
        {
            port_ptr->moder     |= 0x00005555;
            port_ptr->otyper    &= 0xFFFFFF00;
            port_ptr->ospeedr   |= 0x0000FFFF;
            return;
        }
        if ( config == GPIO_CFG_DIGITAL_INPUT )
        {
            port_ptr->moder     &= 0xFFFF0000;
            return;
        }
    }
    else if ( pin_mask == GPIO_PIN_MASK_HIGH )
    {
        port_ptr->moder &= 0x0000FFFF;
        if ( config == GPIO_CFG_DIGITAL_OUTPUT )
        {
            port_ptr->moder     |= 0x55550000;
            port_ptr->otyper    &= 0xFFFF00FF;
            port_ptr->ospeedr   |= 0xFFFF0000;
            return;
        }
        if ( config == GPIO_CFG_DIGITAL_INPUT )
        {
            port_ptr->moder     &= 0x0000FFFF;
            return;
        }
    }

    if ( pin_mask == GPIO_PIN_MASK_ALL )
    {
        if ( config == GPIO_CFG_DIGITAL_OUTPUT )
        {
            port_ptr->moder     = 0x55555555;
            port_ptr->otyper    = 0;
            port_ptr->ospeedr   = 0xFFFF0000;
            return;
        }
        if ( config == GPIO_CFG_DIGITAL_INPUT )
        {
            port_ptr->moder     = 0;
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

#if defined(STM32F411xx) || defined(STM32F412xx) || defined(STM32F413xx) || \
    defined(STM32F423xx) || defined(STM32F446xx) || defined(STM32F3xx)
    if ( config & ( GPIO_CFG_SPEED_HIGH | GPIO_CFG_SPEED_MAX ) )
        speed = 3;
#elif defined(STM32F4xx) || defined(STM32L4xx) || defined(STM32F7xx) || \
    defined(STM32H7xx)  || defined(STM32F2xx) || defined(STM32L1xx) || \
    defined(STM32F0xx)  || defined(STM32G0xx) || defined(STM32L0xx)
    if ( config & ( GPIO_CFG_SPEED_VERY_HIGH | GPIO_CFG_SPEED_MAX ) )
        speed = 3;
#endif
#if defined(STM32F4xx) || defined(STM32L4xx) || defined(STM32F7xx) || \
      defined(STM32H7xx)  || defined(STM32F2xx) || defined(STM32L1xx) || \
      defined(STM32F0xx)  || defined(STM32G0xx) || defined(STM32L0xx)
    else if ( config & GPIO_CFG_SPEED_HIGH )
        speed = 2;
#elif defined(STM32F411xx) || defined(STM32F412xx) || defined(STM32F413xx) || \
    defined(STM32F423xx) || defined(STM32F446xx)
    else if ( config & GPIO_CFG_SPEED_FAST )
        speed = 2;
#endif
    else if ( config & GPIO_CFG_SPEED_MEDIUM )
        speed = 1;
    else if ( config & GPIO_CFG_SPEED_LOW )
        speed = 0;
    else
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
        pos = ( ( uint32_t )0x01 ) << pin_pos;
        current_pin = ( pin_mask ) & pos;

        if ( current_pin == pos )
        {
            port_ptr->moder &= ~( GPIO_MODER_MODER0 << ( pin_pos * 2 ) );
            port_ptr->moder |= ( ( ( uint32_t )mode ) << ( pin_pos * 2 ) );

            if ( config & ( GPIO_CFG_MODE_OUTPUT | GPIO_CFG_MODE_ALT_FUNCTION ) )
            {
                port_ptr->ospeedr &= ~( GPIO_OSPEEDER_OSPEEDR0 << ( pin_pos * 2 ) );
                port_ptr->ospeedr |= ( ( uint32_t )( speed ) << ( pin_pos * 2 ) );

                port_ptr->otyper &= ~( GPIO_OTYPER_OT_0 << ( ( uint16_t )pin_pos ) ) ;
                port_ptr->otyper |= ( uint16_t )( ( ( uint16_t )otype ) << ( ( uint16_t )pin_pos ) );
            }

            port_ptr->pupdr &= ~( GPIO_PUPDR_PUPDR0 << ( ( uint16_t )pin_pos * 2 ) );
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
