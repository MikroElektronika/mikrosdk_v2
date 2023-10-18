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

#if defined(STM32F1xx)
#define GPIOA_BASE_ADDR ( uint32_t )0x40010800
#define GPIOB_BASE_ADDR ( uint32_t )0x40010C00
#define GPIOC_BASE_ADDR ( uint32_t )0x40011000
#define GPIOD_BASE_ADDR ( uint32_t )0x40011400
#define GPIOE_BASE_ADDR ( uint32_t )0x40011800
#define GPIOF_BASE_ADDR ( uint32_t )0x40011C00
#define GPIOG_BASE_ADDR ( uint32_t )0x40012000

#define RCC_GPIOCLOCK _RCC_APB2ENR
#define HAL_GPIO_ALTERNATE_FUNCTION_ENABLE  0
#endif

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
#ifndef GPIOH_BASE_ADDR
    #define GPIOH_BASE_ADDR 0
#endif
#ifndef GPIOI_BASE_ADDR
    #define GPIOI_BASE_ADDR 0
#endif
#ifndef GPIOJ_BASE_ADDR
    #define GPIOJ_BASE_ADDR 0
#endif
#ifndef GPIOK_BASE_ADDR
    #define GPIOK_BASE_ADDR 0
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

uint8_t hal_ll_gpio_pin_index( hal_ll_pin_name_t name )
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
    volatile uint32_t gpio_remap;

    ( state == true ) ? ( set_reg_bit( _RCC_APB2ENR, HAL_GPIO_ALTERNATE_FUNCTION_ENABLE ) ) :
                              ( clear_reg_bit( _RCC_APB2ENR, HAL_GPIO_ALTERNATE_FUNCTION_ENABLE ) );

    // If alternate function is in AFIO_MAPR2
    if ( module->gpio_remap & GPIO_AFIO_REG_SELECT )
    {
        ( state == true ) ? (*(uint32_t *)_AFIO_MAPR2 |= module->gpio_remap & GPIO_AFIO_MAPR2_MASK) :
                            (*(uint32_t *)_AFIO_MAPR2 &= ~(module->gpio_remap & GPIO_AFIO_MAPR2_MASK));
    } else  // If alternate function is in AFIO_MAPR
    {
        /**
         * @brief Predefined compiler macro.
         * @note MikroC compiler uses HW_DEBUG. GCC uses NDEBUG( not debug ).
         * @note Using NDEBUG because it's the only macro whose behavior is
         * standardized across compilers and implementations.
         */
        #ifdef __GNUC__
            #define HW_DEBUG !NDEBUG
        #endif
        #if HW_DEBUG
        gpio_remap = module->gpio_remap & GPIO_AFIO_MAPR_MASK & 
                     GPIO_AFIO_MAPR_NO_SWJ_MASK | GPIO_AFIO_MAPR_SWJDP_ENABLED_MASK;
        #else
        gpio_remap = module->gpio_remap & GPIO_AFIO_MAPR_MASK;
        #endif

        ( state == true ) ? (*(uint32_t *)_AFIO_MAPR |= ( *(uint32_t *)_AFIO_MAPR & ~GPIO_AFIO_MAPR_SWJ ) | gpio_remap ) :
                            (*(uint32_t *)_AFIO_MAPR &= ~(( *(uint32_t *)_AFIO_MAPR & ~GPIO_AFIO_MAPR_SWJ ) | gpio_remap ));
    }

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

  switch ( ( uint32_t ) port & 0xFFFFFC00 )
  {
    #ifdef __PORT_A_CN
    case GPIOA_BASE_ADDR: pos = 0x4;   break;
    #endif
    #ifdef __PORT_B_CN
    case GPIOB_BASE_ADDR: pos = 0x8;   break;
    #endif
    #ifdef __PORT_C_CN
    case GPIOC_BASE_ADDR: pos = 0x10;   break;
    #endif
    #ifdef __PORT_D_CN
    case GPIOD_BASE_ADDR: pos = 0x20;   break;
    #endif
    #ifdef __PORT_E_CN
    case GPIOE_BASE_ADDR: pos = 0x40;  break;
    #endif
    #ifdef __PORT_F_CN
    case GPIOF_BASE_ADDR: pos = 0x80;  break;
    #endif
    #ifdef __PORT_G_CN
    case GPIOG_BASE_ADDR: pos = 0x100;  break;
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

    uint32_t *port_ptr_tmp = 0;
    uint32_t tmpreg        = 0;

    uint32_t tmp_pinmask   = 0;

    hal_ll_gpio_base_handle_t *port_ptr;
    port_ptr = ( hal_ll_gpio_base_handle_t *)port;

    hal_ll_gpio_clock_enable( port );

    if ( pin_mask == GPIO_PIN_MASK_LOW )
    {
        if ( config == GPIO_CFG_DIGITAL_OUTPUT )
        {
            port_ptr->crl = GPIO_SET_ALL_OUTPUT;
            return;
        }
        if ( config == GPIO_CFG_DIGITAL_INPUT )
        {
            port_ptr->crl = GPIO_SET_ALL_INPUT;
            return;
        }
    }
    else if ( pin_mask == GPIO_PIN_MASK_HIGH )
    {
        if ( config == GPIO_CFG_DIGITAL_OUTPUT )
        {
            port_ptr->crh = GPIO_SET_ALL_OUTPUT;
            return;
        }
        if ( config == GPIO_CFG_DIGITAL_INPUT )
        {
            port_ptr->crh = GPIO_SET_ALL_INPUT;
            return;
        }
    }

    if ( pin_mask == GPIO_PIN_MASK_ALL )
    {
        if ( config == GPIO_CFG_DIGITAL_OUTPUT )
        {
            port_ptr->crl = GPIO_SET_ALL_OUTPUT;
            port_ptr->crh = GPIO_SET_ALL_OUTPUT;
            return;
        }
        if ( config == GPIO_CFG_DIGITAL_INPUT )
        {
            port_ptr->crl = GPIO_SET_ALL_INPUT;
            port_ptr->crh = GPIO_SET_ALL_INPUT;
            return;
        }
    }

    if ( config & ( GPIO_CFG_MODE_ANALOG ) )
        mode = 0;
    else if ( config & GPIO_CFG_MODE_INPUT )
    {
        if ( config & ( GPIO_CFG_PULL_DOWN | GPIO_CFG_PULL_UP ) )
            mode = 0x8;
        else
            mode = 0x4;
    }
    else if ( config & GPIO_CFG_MODE_OUTPUT )
    {
        if ( config & GPIO_CFG_OTYPE_OD )
            mode = 0x4;
        else
            mode = 0;
    }
    else if ( config & GPIO_CFG_MODE_ALT_FUNCTION )
    {
        if ( config & GPIO_CFG_OTYPE_OD )
            mode = 0xC;
        else
            mode = 0x8;
    }

    if ( config & ( GPIO_CFG_SPEED_MAX | GPIO_CFG_SPEED_50MHZ ) )
        speed = 3;
    else if ( config & GPIO_CFG_SPEED_2MHZ )
        speed = 2;
    else if ( config & GPIO_CFG_SPEED_10MHZ )
        speed = 1;

    if ( config & ( GPIO_CFG_MODE_OUTPUT | GPIO_CFG_MODE_ALT_FUNCTION ) )
    {
        /* Output mode */
        mode |= (uint32_t)speed;
    }

  if ( ( pin_mask & 0xFF ) != 0 )
  {
    tmpreg = port_ptr->crl;      // CRL register

    for ( pin_pos = 0x00; pin_pos < 0x08; pin_pos++ )
    {
      pos = ( ( uint32_t ) 0x01 ) << pin_pos;
      /* Get the port pins position */
      current_pin = pin_mask & pos;

      if ( current_pin == pos )
      {
        pos = pin_pos << 2;
        /* Clear the corresponding low control register bits */
        tmp_pinmask = ( ( uint32_t ) 0x0F ) << pos;
        tmpreg &= ~tmp_pinmask;

        /* Write the mode configuration in the corresponding bits */
        tmpreg |= mode << pos;

        /* Reset the corresponding ODR bit */
        if ( ( config & ( GPIO_CFG_MODE_INPUT | GPIO_CFG_PULL_DOWN ) ) == ( GPIO_CFG_MODE_INPUT | GPIO_CFG_PULL_DOWN ) )
        {
          port_ptr->brr = ( ( ( uint32_t ) 0x01 ) << pin_pos );  // write to BRR register
        }
        /* Set the corresponding ODR bit */
        if ( ( config & ( GPIO_CFG_MODE_INPUT | GPIO_CFG_PULL_UP ) ) == ( GPIO_CFG_MODE_INPUT | GPIO_CFG_PULL_UP ) )
        {
          port_ptr->bsrr = ( ( uint32_t ) 0x01 ) << pin_pos;
        }
      }
    }
    port_ptr->crl = tmpreg;          // write to CRL register

  }

/*---------------------------- GPIO CRH Configuration ------------------------*/
  /* Configure the eight high port pins */
  if ( pin_mask > HAL_LL_NIBBLE_LOW_16BIT )
  {
    tmpreg = port_ptr->crh;//GPIOx->CRH;
    for ( pin_pos = 0x00; pin_pos < 0x08; pin_pos++ )
    {
      pos = ( ( uint32_t ) 0x01) << (pin_pos + 0x08);
      /* Get the port pins position */
      current_pin = pin_mask & pos;
      if ( current_pin == pos )
      {
        pos = pin_pos << 2;
        /* Clear the corresponding high control register bits */
        tmp_pinmask = ( ( uint32_t ) 0x0F ) << pos;
        tmpreg &= ~tmp_pinmask;

        /* Write the mode configuration in the corresponding bits */
        tmpreg |= mode << pos;

        /* Reset the corresponding ODR bit */
        if ( ( config & ( GPIO_CFG_MODE_INPUT | GPIO_CFG_PULL_DOWN ) ) == ( GPIO_CFG_MODE_INPUT | GPIO_CFG_PULL_DOWN ) )
        {
          port_ptr->brr = ( ( uint32_t ) 0x01 ) << ( pin_pos + 0x08 );
        }
        /* Set the corresponding ODR bit */
        if ( ( config & ( GPIO_CFG_MODE_INPUT | GPIO_CFG_PULL_UP ) ) == ( GPIO_CFG_MODE_INPUT | GPIO_CFG_PULL_UP ) )
        {
          port_ptr->bsrr = ( ( uint32_t ) 0x01 ) << ( pin_pos + 0x08 );
        }
      }
    }
    port_ptr->crh = tmpreg;
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
    uint16_t pin_index;
    hal_ll_pin_name_t pin_name;
    hal_ll_gpio_base_handle_t *port_ptr;

    pin_name  = module_pin & GPIO_PIN_NAME_MASK;

    pin_index = hal_ll_gpio_pin_index( pin_name );

    port_ptr = ( hal_ll_gpio_base_handle_t *)hal_ll_gpio_port_base( hal_ll_gpio_port_index ( pin_name ) );

    if ( state ) {
        hal_ll_gpio_config( ( uint32_t*)port_ptr, hal_ll_gpio_pin_mask( pin_name ), module_config );
    } else {
        hal_ll_gpio_clock_enable( ( uint32_t * )port_ptr );

        if ( pin_index > 7 ) {
            pin_index -= 8;
            port_ptr->crh |= ( GPIO_CFG_MODE_OUTPUT << ( pin_index * 4 ) ); // STM32F1 pin reset state
        } else {
            port_ptr->crl |= ( GPIO_CFG_MODE_OUTPUT << ( pin_index * 4 ) ); // STM32F1 pin reset state
        }

        module_config &= ~GPIO_CFG_MODE_ALT_FUNCTION;
        hal_ll_gpio_config( ( uint32_t*)port_ptr, hal_ll_gpio_pin_mask( pin_name ), module_config );
    }
}
// ------------------------------------------------------------------------- END
