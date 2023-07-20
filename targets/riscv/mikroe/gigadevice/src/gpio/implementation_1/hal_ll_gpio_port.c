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
#include "hal_ll_rcu.h"

/**
 *  Defines used in source
 */
#define GPIO_SWJ_CFG_PIN_MASK                      (0x18UL)
#define GPIO_AFIO_PCF0_SWJ_CFG_RESET               (0xF8FFFFFFUL)
#define GPIO_AFIO_PCF0_SWJ_CFG_NJRST_DISABLED      (0x01000000UL)
#define GPIO_AFIO_PCF0_SWJ_CFG_DISABLED            (0x04000000UL)

#if defined(GD32VF103)
    #define GPIOA_BASE_ADDR                        (0x40010800UL)
    #define GPIOB_BASE_ADDR                        (0x40010C00UL)
    #define GPIOC_BASE_ADDR                        (0x40011000UL)
    #define GPIOD_BASE_ADDR                        (0x40011400UL)
    #define GPIOE_BASE_ADDR                        (0x40011800UL)
    #define GPIO_AFIO_ADDR                         (0x40010000UL)
    #define RCU_GPIOCLOCK                          (RCU_APB2EN)
    #define HAL_GPIO_ALTERNATE_FUNCTION_ENABLE_BIT (0)
    /*!< If module is remapped. */
    #define HAL_LL_MODULE_REMAP                    (0x80000000UL)
#endif

#ifndef GPIOA_BASE_ADDR
    #define GPIOA_BASE_ADDR (0)
#endif
#ifndef GPIOB_BASE_ADDR
    #define GPIOB_BASE_ADDR (0)
#endif
#ifndef GPIOC_BASE_ADDR
    #define GPIOC_BASE_ADDR (0)
#endif
#ifndef GPIOD_BASE_ADDR
    #define GPIOD_BASE_ADDR (0)
#endif
#ifndef GPIOE_BASE_ADDR
    #define GPIOE_BASE_ADDR (0)
#endif

static void hal_ll_gpio_config( uint32_t *port, uint16_t pin_mask, uint32_t config );

/*!< @brief GPIO PORT array */
static const uint32_t _hal_ll_gpio_port_base [ 5 ] = {
    GPIOA_BASE_ADDR,
    GPIOB_BASE_ADDR,
    GPIOC_BASE_ADDR,
    GPIOD_BASE_ADDR,
    GPIOE_BASE_ADDR
};

/**
  * @brief  Enable gpio port clock
  * @param  port - port base address
  * @return none
  */
static void hal_ll_gpio_clock_enable( uint32_t port );

/**
  * @brief  Configure port pins
  * @param  *port    - pointer to gpio port
  *         pin_mask - desired pin
  *         config   - pin settings
  * @return none
  */
static void hal_ll_gpio_config( uint32_t *port, uint16_t pin_mask, uint32_t config );

/**
  * @brief  Configure port pins alternate
  *         functions
  * @param  module_pin    - desired pin
  *         module_config - pin settings
  * @return none
  */
static void _hal_ll_gpio_config_pin_alternate_enable( uint32_t module_pin, uint32_t module_config );

static uint8_t hal_ll_gpio_pin_index( hal_ll_pin_name_t name ) {
    return ( uint8_t )name % PORT_SIZE;
}

uint8_t hal_ll_gpio_port_index( hal_ll_pin_name_t name ) {
    return ( uint8_t )name / PORT_SIZE;
}

uint32_t hal_ll_gpio_pin_mask( hal_ll_pin_name_t name ) {
    return ( 1UL << hal_ll_gpio_pin_index( name ) );
}

uint32_t hal_ll_gpio_port_base( hal_ll_port_name_t name ) {
    return _hal_ll_gpio_port_base[ name ];
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

    // Get list of registers that are in relation with alternate functionality.
    hal_ll_gpio_afio_handle_t *afio_ptr = ( hal_ll_gpio_afio_handle_t *)GPIO_AFIO_ADDR;

    // Set appropriate functionality.
    if ( state ) {
        // Enable Alternate Functionality clock.
        set_reg_bit( RCU_APB2EN, HAL_GPIO_ALTERNATE_FUNCTION_ENABLE_BIT );

        // If alternate functionality mapping is needed...
        if ( module->gpio_remap & HAL_LL_MODULE_REMAP ) {
            afio_ptr->pcf0 |= (( afio_ptr->pcf0 & GPIO_AFIO_PCF0_SWJ_CFG_RESET ) |
                               ( module->gpio_remap & GPIO_AFIO_PCF0_MASK ));
        }
    } else {
        // Disable alternate functionality clock.
        clear_reg_bit( RCU_APB2EN, HAL_GPIO_ALTERNATE_FUNCTION_ENABLE_BIT );
    }

    // Finally, configure appropriate pin (or pins).
    while ( 0xFFFFFFFF != module->pins[ index ] )
    {
        _hal_ll_gpio_config_pin_alternate_enable( module->pins[ index ], module->configs[ index ] );

        index++;
    }
}

static void disable_swj_cfg( hal_ll_gpio_afio_handle_t *afio_ptr ) {
    /* First back to reset state. */
    afio_ptr->pcf0 &= GPIO_AFIO_PCF0_SWJ_CFG_RESET;
    /* Then disable the jtag functionality. */
    afio_ptr->pcf0 |= GPIO_AFIO_PCF0_SWJ_CFG_DISABLED;
}

/**
  * @brief  Enable gpio port clock
  * @param  port - port base address
  * @return none
  */
static void hal_ll_gpio_clock_enable( uint32_t port ) {
    uint8_t pos = 0;

    switch ( port )
    {
        #ifdef __PORT_A_CN
        case GPIOA_BASE_ADDR:
            pos = 2;
            break;
        #endif
        #ifdef __PORT_B_CN
        case GPIOB_BASE_ADDR:
            pos = 3;
            break;
        #endif
        #ifdef __PORT_C_CN
        case GPIOC_BASE_ADDR:
            pos = 4;
            break;
        #endif
        #ifdef __PORT_D_CN
        case GPIOD_BASE_ADDR:
            pos = 5;
            break;
        #endif
        #ifdef __PORT_E_CN
        case GPIOE_BASE_ADDR:
            pos = 6;
            break;
        #endif
    }

    *(uint32_t *)RCU_GPIOCLOCK |= 1UL << pos;
}

/**
  * @brief  Configure single port pins
  * @param  port     - port base address
  *         pin_mask - desired pin
  *         config   - pin settings
  * @return none
  */
static void hal_ll_gpio_config( uint32_t *port, uint16_t pin_mask, uint32_t config ) {
    int8_t pin_cnt = 8;
    bool lock_state = false;
    hal_ll_pin_name_t pin_id = 0;

    /* GPIO handler. */
    hal_ll_gpio_base_handle_t *port_ptr = ( hal_ll_gpio_base_handle_t *)port;

    /* AFIO handler. */
    hal_ll_gpio_afio_handle_t *afio_ptr = ( hal_ll_gpio_afio_handle_t *)GPIO_AFIO_ADDR;

    /* Enable clock before continuing. */
    hal_ll_gpio_clock_enable( (uint32_t)port );

    if ( port_ptr->lock & GPIO_LOCK_KEY_BIT_MASK ) {
        lock_state = true;
    }

    /* Pins Px8-Px15. */
    while( --pin_cnt >= 0 ) {
        pin_id = 1UL << (pin_cnt + 8);

        /* If pin is locked, skip setting. */
        if ( (!lock_state) || (lock_state && !(port_ptr->lock & pin_id)) ) {
            if ( pin_id & pin_mask ) {
                /* Set to default analog functionality by default. */
                port_ptr->ctl1 &= ~(0xFUL << (pin_cnt * 4));

                /* Then check if there is need to set the pin as digital I/O. */
                if ( GPIO_CFG_DIGITAL_OUTPUT == config ) {
                    port_ptr->ctl1 |= ( GPIO_CFG_DIGITAL_OUTPUT << ( pin_cnt * 4 ) );
                } else if ( GPIO_CFG_DIGITAL_INPUT == config ) {
                    port_ptr->ctl1 |= ( GPIO_CFG_DIGITAL_INPUT << ( pin_cnt * 4 ) );
                    /* Else, check if there is need to set custom pin settings. */
                } else {
                    if ( GPIO_CTL_CFG_OUTPUT_AFIO_PP == ( GPIO_MASK_BITS_CTL & config ) ) {
                        port_ptr->ctl1 |= ( ( GPIO_CTL_CFG_OUTPUT_AFIO_PP ) << ( pin_cnt * 4 ) );
                    } else if ( GPIO_CTL_CFG_OUTPUT_AFIO_OD == ( GPIO_MASK_BITS_CTL & config ) ) {
                        port_ptr->ctl1 |= ( ( GPIO_CTL_CFG_OUTPUT_AFIO_OD ) << ( pin_cnt * 4 ) );
                    }
                    if ( GPIO_CTL_MODE_OUTPUT_SPEED_M2 == ( GPIO_MASK_BITS_MD & config ) ) {
                        port_ptr->ctl1 |= ( ( GPIO_CTL_MODE_OUTPUT_SPEED_M2 ) << ( pin_cnt * 4 ) );
                    } else if ( GPIO_CTL_MODE_OUTPUT_SPEED_M10 == ( GPIO_MASK_BITS_MD & config ) ) {
                        port_ptr->ctl1 |= ( ( GPIO_CTL_MODE_OUTPUT_SPEED_M10 ) << ( pin_cnt * 4 ) );
                    } else if ( GPIO_CTL_MODE_OUTPUT_SPEED_M50 == ( GPIO_MASK_BITS_MD & config ) ) {
                        port_ptr->ctl1 |= ( ( GPIO_CTL_MODE_OUTPUT_SPEED_M50 ) << ( pin_cnt * 4 ) );
                    }
                }
            }
        }
    }

    /* Pins Px0-Px7. */
    pin_cnt = 8;
    while( --pin_cnt >= 0 ) {
        pin_id = 1UL << pin_cnt;

        /* If pin is locked, skip setting. */
        if ( (!lock_state) || (lock_state && !(port_ptr->lock & pin_id)) ) {
            if ( pin_id & pin_mask ) {
                /* Set to default analog functionality by default. */
                port_ptr->ctl0 &= ~(0xFUL << (pin_cnt * 4));

                /* Then check if there is need to set the pin as digital I/O. */
                if ( GPIO_CFG_DIGITAL_OUTPUT == config ) {
                    port_ptr->ctl0 |= ( GPIO_CFG_DIGITAL_OUTPUT << ( pin_cnt * 4 ) );
                } else if ( GPIO_CFG_DIGITAL_INPUT == config ) {
                    port_ptr->ctl0 |= ( GPIO_CFG_DIGITAL_INPUT << ( pin_cnt * 4 ) );
                    /* Else, check if there is need to set custom pin settings. */
                } else {
                    if ( GPIO_CTL_CFG_OUTPUT_AFIO_PP == ( GPIO_MASK_BITS_CTL & config ) ) {
                        port_ptr->ctl0 |= ( ( GPIO_CTL_CFG_OUTPUT_AFIO_PP ) << ( pin_cnt * 4 ) );
                    } else if ( GPIO_CTL_CFG_OUTPUT_AFIO_OD == ( GPIO_MASK_BITS_CTL & config ) ) {
                        port_ptr->ctl0 |= ( ( GPIO_CTL_CFG_OUTPUT_AFIO_OD ) << ( pin_cnt * 4 ) );
                    }
                    if ( GPIO_CTL_MODE_OUTPUT_SPEED_M2 == ( GPIO_MASK_BITS_MD & config ) ) {
                        port_ptr->ctl0 |= ( ( GPIO_CTL_MODE_OUTPUT_SPEED_M2 ) << ( pin_cnt * 4 ) );
                    } else if ( GPIO_CTL_MODE_OUTPUT_SPEED_M10 == ( GPIO_MASK_BITS_MD & config ) ) {
                        port_ptr->ctl0 |= ( ( GPIO_CTL_MODE_OUTPUT_SPEED_M10 ) << ( pin_cnt * 4 ) );
                    } else if ( GPIO_CTL_MODE_OUTPUT_SPEED_M50 == ( GPIO_MASK_BITS_MD & config ) ) {
                        port_ptr->ctl0 |= ( ( GPIO_CTL_MODE_OUTPUT_SPEED_M50 ) << ( pin_cnt * 4 ) );
                    }
                }
            }
        }
    }

    /* If pins PB3 and PB4 are being used, disable the JTAG functionality. */
    if ( (GPIOB_BASE_ADDR == (uint32_t)&port_ptr->ctl0) &&
         (pin_mask & GPIO_SWJ_CFG_PIN_MASK) )
    {
        disable_swj_cfg( afio_ptr );
    }
}

/**
  * @brief  Configure port pins alternate
  *         functions
  * @param  module_pin - desired pin
  *         config     - pin settings
  * @return none
  */
static void _hal_ll_gpio_config_pin_alternate_enable( uint32_t module_pin, uint32_t module_config ) {
    hal_ll_pin_name_t pin_name;
    hal_ll_gpio_base_handle_t *port_ptr;

    // Get pin name.
    pin_name  = module_pin & GPIO_PIN_NAME_MASK;

    // Get appropriate PORT.
    port_ptr = ( hal_ll_gpio_base_handle_t *)hal_ll_gpio_port_base( hal_ll_gpio_port_index ( pin_name ) );

    // Finally, configure pin.
    hal_ll_gpio_config( ( uint32_t*)port_ptr, hal_ll_gpio_pin_mask( pin_name ), module_config );
}
// ------------------------------------------------------------------------- END
