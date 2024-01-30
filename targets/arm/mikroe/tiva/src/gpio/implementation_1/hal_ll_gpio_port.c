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
 * @file  hal_ll_gpio_port.c
 * @brief GPIO HAL LOW LEVEL ported layer implementation.
 */

#include "hal_ll_gpio_port.h"
#include "hal_ll_rcc.h"

/*!< @brief Helper macro for extracting appropriate pin mask. */
#define HAL_LL_GPIO_PIN_MASK            0xFUL

/*!< @brief Helper macro for extracting appropriate port mask. */
#define HAL_LL_GPIO_PORT_MASK           0xFFUL

/*!< @brief Helper macro for extracting appropriate alternate function. */
#define HAL_LL_GPIO_AF_MASK             0xF00UL

/*!< @brief Helper macro for getting appropriate alternate function mask. */
#define HAL_LL_GPIO_AFSEL_MULTIPLIER    4

/*!< @brief Helper macro. */
#define HAL_LL_GPIO_GPIOCR_MASK         0xFFFFFF00

/*!< @brief Helper macro for hexadecimal number for unlocking the GPIOCR register. */
#define HAL_LL_GPIO_GPIOCR_UNLOCK_VALUE 0x4C4F434B

/*!< @brief Helper macro for checking against pins PE7 and PD7. */
#define HAL_LL_GPIO_PINMASK_PIN7        0x80UL

/*!< @brief Helper macro for checking against pins on PORTC[0:3]. */
#define HAL_LL_GPIO_PINMASK_PIN0_3      0xFUL

/*!< @brief Helper macro for checking against pins PF0. */
#define HAL_LL_GPIO_PINMASK_PIN0        0x01UL

/**
 *  Defines used in source
 */
#ifdef TM4C123
    #define GPIOA_BASE_ADDR     0x400043FCUL
    #define GPIOB_BASE_ADDR     0x400053FCUL
    #define GPIOC_BASE_ADDR     0x400063FCUL
    #define GPIOD_BASE_ADDR     0x400073FCUL
    #define GPIOE_BASE_ADDR     0x400243FCUL
    #define GPIOF_BASE_ADDR     0x400253FCUL
    #define GPIOG_BASE_ADDR     0x400263FCUL
    #define GPIOH_BASE_ADDR     0x400273FCUL
    #define GPIOJ_BASE_ADDR     0x4003D3FCUL
    #define GPIOK_BASE_ADDR     0x400613FCUL
#else
    #define GPIOA_BASE_ADDR     0x400583FCUL
    #define GPIOB_BASE_ADDR     0x400593FCUL
    #define GPIOC_BASE_ADDR     0x4005A3FCUL
    #define GPIOD_BASE_ADDR     0x4005B3FCUL
    #define GPIOE_BASE_ADDR     0x4005C3FCUL
    #define GPIOF_BASE_ADDR     0x4005D3FCUL
    #define GPIOG_BASE_ADDR     0x4005E3FCUL
    #define GPIOH_BASE_ADDR     0x4005F3FCUL
    #define GPIOJ_BASE_ADDR     0x400603FCUL
    #define GPIOK_BASE_ADDR     0x400613FCUL
    #define GPIOL_BASE_ADDR     0x400623FCUL
    #define GPIOM_BASE_ADDR     0x400633FCUL
    #define GPION_BASE_ADDR     0x400643FCUL
    #define GPIOP_BASE_ADDR     0x400653FCUL
    #define GPIOQ_BASE_ADDR     0x400663FCUL
    #define GPIOR_BASE_ADDR     0x400673FCUL
    #define GPIOS_BASE_ADDR     0x400683FCUL
    #define GPIOT_BASE_ADDR     0x400693FCUL
#endif

#define RCC_GPIOCLOCK        _SYSCTL_RCGCGPIO

#define hal_ll_gpio_port_get_pin_index(__index) ( __index & 0xF0 )?( ( uint8_t )__index % PORT_SIZE ): \
                                                ( ( uint8_t )__index % PORT_SIZE )

#define hal_ll_gpio_port_get_port_index(__index) ( __index & 0xF0 )?( ( uint8_t )__index / PORT_SIZE ): \
                                                 ( ( uint8_t )__index / PORT_SIZE )

#ifndef GPIOA_BASE_ADDR
    #define GPIOA_BASE_ADDR 0
#endif
#ifndef GPIOB_BASE_ADDR
    #define GPIOB_BASE_ADDR 1
#endif
#ifndef GPIOC_BASE_ADDR
    #define GPIOC_BASE_ADDR 2
#endif
#ifndef GPIOD_BASE_ADDR
    #define GPIOD_BASE_ADDR 3
#endif
#ifndef GPIOE_BASE_ADDR
    #define GPIOE_BASE_ADDR 4
#endif
#ifndef GPIOF_BASE_ADDR
    #define GPIOF_BASE_ADDR 5
#endif
#ifndef GPIOG_BASE_ADDR
    #define GPIOG_BASE_ADDR 6
#endif
#ifndef GPIOH_BASE_ADDR
    #define GPIOH_BASE_ADDR 7
#endif
#ifndef GPIOJ_BASE_ADDR
    #define GPIOJ_BASE_ADDR 8
#endif
#ifndef GPIOK_BASE_ADDR
    #define GPIOK_BASE_ADDR 9
#endif
#ifndef GPIOL_BASE_ADDR
    #define GPIOL_BASE_ADDR 10
#endif
#ifndef GPIOM_BASE_ADDR
    #define GPIOM_BASE_ADDR 11
#endif
#ifndef GPION_BASE_ADDR
    #define GPION_BASE_ADDR 12
#endif
#ifndef GPIOP_BASE_ADDR
    #define GPIOP_BASE_ADDR 13
#endif
#ifndef GPIOQ_BASE_ADDR
    #define GPIOQ_BASE_ADDR 14
#endif
#ifndef GPIOR_BASE_ADDR
    #define GPIOR_BASE_ADDR 15
#endif
#ifndef GPIOS_BASE_ADDR
    #define GPIOS_BASE_ADDR 16
#endif
#ifndef GPIOT_BASE_ADDR
    #define GPIOT_BASE_ADDR 17
#endif

/*!< @brief GPIO PORT array */
static const uint32_t _hal_ll_gpio_port_base[] =
{
    #ifdef TM4C123
    GPIOA_BASE_ADDR,
    GPIOB_BASE_ADDR,
    GPIOC_BASE_ADDR,
    GPIOD_BASE_ADDR,
    GPIOE_BASE_ADDR,
    GPIOF_BASE_ADDR,
    GPIOG_BASE_ADDR,
    GPIOH_BASE_ADDR,
    GPIOJ_BASE_ADDR,
    GPIOK_BASE_ADDR
    #else
    GPIOA_BASE_ADDR,
    GPIOB_BASE_ADDR,
    GPIOC_BASE_ADDR,
    GPIOD_BASE_ADDR,
    GPIOE_BASE_ADDR,
    GPIOF_BASE_ADDR,
    GPIOG_BASE_ADDR,
    GPIOH_BASE_ADDR,
    GPIOJ_BASE_ADDR,
    GPIOK_BASE_ADDR,
    GPIOL_BASE_ADDR,
    GPIOM_BASE_ADDR,
    GPION_BASE_ADDR,
    GPIOP_BASE_ADDR,
    GPIOQ_BASE_ADDR,
    GPIOR_BASE_ADDR,
    GPIOS_BASE_ADDR,
    GPIOT_BASE_ADDR
    #endif
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
static void _hal_ll_gpio_config( uint32_t *port, uint8_t pin_mask, uint32_t config );

/**
  * @brief  Configure port pins alternate
  *         functions
  * @param  module_pin - desired pin
  *         config     - pin settings
  * @return none
  */
static void _hal_ll_gpio_config_pin_alternate_enable( uint32_t module_pin, uint32_t module_config, bool state );

/**
 * @brief Enables write access to pins
 *        that were originally locked.
 * @param[in] *gpio_ptr - Register list for one GPIO module.
 * @param[in] port  - Port base address.
 * @param[in] pin   - Pin mask.
 *
 * @return none
 */
static void hal_ll_gpio_unlock_pin( hal_ll_gpio_base_handle_t *gpio_ptr, uint32_t port, uint8_t pin_mask );

/**
 * @brief Unlock access to generic GPIO registers
 *        (GPIOAFSEL, GPIOPUR, GPIOPDR and GPIODEN)
 *        for pin which is locked on POR -> power-on reset.
 * @param[in] *gpio_ptr - Register list for one GPIO module.
 * @param[in] pin_mask  - GPIO pin mask.
 *
 * @return none
 */
static void hal_ll_gpio_commit_pin( hal_ll_gpio_base_handle_t *gpio_ptr, uint8_t pin_mask );

static uint8_t hal_ll_gpio_pin_index( hal_ll_pin_name_t name ) {
    return hal_ll_gpio_port_get_pin_index( name );
}

uint8_t hal_ll_gpio_port_index( hal_ll_pin_name_t name ) {
    return hal_ll_gpio_port_get_port_index( name );
}

uint8_t hal_ll_gpio_pin_mask( hal_ll_pin_name_t name ) {
    return ( 1UL << hal_ll_gpio_pin_index( name ) );
}

uint32_t hal_ll_gpio_port_base( hal_ll_port_name_t name ) {
    return _hal_ll_gpio_port_base[ name ];
}

void hal_ll_gpio_analog_input( uint32_t *port, uint8_t pin_mask ) {
    _hal_ll_gpio_config( port, pin_mask, GPIO_CFG_ANALOG_INPUT );
}

void hal_ll_gpio_digital_input( uint32_t *port, uint8_t pin_mask ) {
    _hal_ll_gpio_config( port, pin_mask, GPIO_CFG_DIGITAL_INPUT );
}

void hal_ll_gpio_digital_output( uint32_t *port, uint8_t pin_mask ) {
    _hal_ll_gpio_config( port, pin_mask, GPIO_CFG_DIGITAL_OUTPUT );
}

void hal_ll_gpio_module_struct_init( module_struct const *module, bool state ) {
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
static void hal_ll_gpio_clock_enable( uint32_t port ) {
    uint8_t shift_value;

    switch ( port ) {
        case GPIOA_BASE_ADDR:
            shift_value = 0;
            break;
        case GPIOB_BASE_ADDR:
            shift_value = 1;
            break;
        case GPIOC_BASE_ADDR:
            shift_value = 2;
            break;
        case GPIOD_BASE_ADDR:
            shift_value = 3;
            break;
        case GPIOE_BASE_ADDR:
            shift_value = 4;
            break;
        case GPIOF_BASE_ADDR:
            shift_value = 5;
            break;
        case GPIOG_BASE_ADDR:
            shift_value = 6;
            break;
        case GPIOH_BASE_ADDR:
            shift_value = 7;
            break;
        case GPIOJ_BASE_ADDR:
            shift_value = 8;
            break;
        case GPIOK_BASE_ADDR:
            shift_value = 9;
            break;
        case GPIOL_BASE_ADDR:
            shift_value = 10;
            break;
        case GPIOM_BASE_ADDR:
            shift_value = 11;
            break;
        case GPION_BASE_ADDR:
            shift_value = 12;
            break;
        case GPIOP_BASE_ADDR:
            shift_value = 13;
            break;
        case GPIOQ_BASE_ADDR:
            shift_value = 14;
            break;
        case GPIOR_BASE_ADDR:
            shift_value = 15;
            break;
        case GPIOS_BASE_ADDR:
            shift_value = 16;
            break;
        case GPIOT_BASE_ADDR:
            shift_value = 17;
            break;

        default:
            return;
    }

    *RCC_GPIOCLOCK |= 1UL << shift_value;
}

static void hal_ll_gpio_commit_pin( hal_ll_gpio_base_handle_t *gpio_ptr, uint8_t pin_mask ) {
    // Unlock GPIOCR register.
    gpio_ptr->gpiolock = HAL_LL_GPIO_GPIOCR_UNLOCK_VALUE;

    // Unlock access to generic GPIO registers (GPIOAFSEL, GPIOPUR, GPIOPDR and GPIODEN)
    // for pin which is locked on POR -> power-on reset.
    gpio_ptr->gpiocr = pin_mask;
}

static void hal_ll_gpio_unlock_pin( hal_ll_gpio_base_handle_t *gpio_ptr, uint32_t port, uint8_t pin_mask ) {
    switch ( port ) {
        // JTAG/SWD pins are based on PORTC.
        case GPIOC_BASE_ADDR:
            if ( pin_mask == ( pin_mask & HAL_LL_GPIO_PINMASK_PIN0_3 ) ) {
                hal_ll_gpio_commit_pin( gpio_ptr, pin_mask );
            }
            break;
        // Non-maskable interrupt pin is based on both PORTD and PORTE.
        case GPIOD_BASE_ADDR:
        case GPIOE_BASE_ADDR:
            if ( pin_mask == HAL_LL_GPIO_PINMASK_PIN7 ) {
                hal_ll_gpio_commit_pin( gpio_ptr, pin_mask );
            }
            break;
        case GPIOF_BASE_ADDR:
            if ( pin_mask == HAL_LL_GPIO_PINMASK_PIN0 ) {
                hal_ll_gpio_commit_pin( gpio_ptr, pin_mask );
            }
            break;

        default:
            return;
    }
}

/**
  * @brief  Configure single port pins
  * @param  port     - port base address
  *         pin_mask - desired pin
  *         config   - pin settings
  * @return none
  */
static void _hal_ll_gpio_config( uint32_t *port, uint8_t pin_mask, uint32_t config ) {
    uint8_t  i;
    uint32_t tmp_code;

    hal_ll_gpio_base_handle_t *gpio_ptr = ( hal_ll_gpio_base_handle_t * )( *port );

    hal_ll_gpio_clock_enable( *port );

    hal_ll_gpio_unlock_pin( gpio_ptr, *port, pin_mask );

    if ( config & GPIO_CFG_MODE_OUTPUT ) {
        gpio_ptr->gpiodir |= pin_mask;
    } else {
        // Else, digital input.
        gpio_ptr->gpiodir &= ~pin_mask;
    }

    if ( config & GPIO_CFG_PULL_UP ) {
        gpio_ptr->gpiopur |= pin_mask;
    } else {
        gpio_ptr->gpiopur &= ~pin_mask;
    }

    if( config & GPIO_CFG_PULL_DOWN ) {
        gpio_ptr->gpiopdr |= pin_mask;
    } else {
        gpio_ptr->gpiopdr &= ~pin_mask;
    }

    if ( config & GPIO_CFG_OPEN_DRAIN ) {
        gpio_ptr->gpioodr |= pin_mask;
    } else {
        gpio_ptr->gpioodr &= ~pin_mask;
    }

    if ( config & GPIO_CFG_DRIVE_2mA) {
        gpio_ptr->gpiodr2r |= pin_mask;
    } else {
        gpio_ptr->gpiodr2r &= ~pin_mask;
    }

    if ( config & GPIO_CFG_DRIVE_4mA ) {
        gpio_ptr->gpiodr4r |= pin_mask;
    } else {
        gpio_ptr->gpiodr4r &= ~pin_mask;
    }

    if ( config & GPIO_CFG_DRIVE_8mA) {
        gpio_ptr->gpiodr8r |= pin_mask;
    } else {
        gpio_ptr->gpiodr8r &= ~pin_mask;
    }

    if( ( 1 == ( config & GPIO_CFG_DRIVE_6mA ) ) ||
        ( 1 == ( config & GPIO_CFG_DRIVE_10mA ) ) ||
        ( 1 == ( config & GPIO_CFG_DRIVE_12mA ) ) )
    {
        tmp_code = 0;
        for ( i = 0; i < 8; i++ ) {
            if( ( pin_mask >> i ) & 1 ) {
                tmp_code |= 0x3UL << ( i * 2 );
            }
        }

        gpio_ptr->gpiopc &= ~tmp_code;
        gpio_ptr->gpiodr8r &= ~pin_mask;
        gpio_ptr->gpiodr4r &= ~pin_mask;
        gpio_ptr->gpiodr12r &= ~pin_mask;
    }

    tmp_code = 0;

    if ( config & GPIO_CFG_DRIVE_6mA ) {
        for( i = 0; i < 8; i++ ) {
            if( ( pin_mask >> i ) & 1 ) {
                tmp_code |= 0x1UL << ( i * 2 );
            }
        }

        gpio_ptr->gpiopc |= tmp_code;
        gpio_ptr->gpiodr8r |= pin_mask;
    }

    tmp_code = 0;

    if( config & GPIO_CFG_DRIVE_10mA ) {
        for( i = 0; i < 8; i++ ) {
            if( ( pin_mask >> i ) & 1 ) {
                tmp_code |= 0x3UL << ( i * 2 );
            }
        }

        gpio_ptr->gpiopc |= tmp_code;
        gpio_ptr->gpiodr8r |= pin_mask;
        gpio_ptr->gpiodr12r |= pin_mask;
    }

    tmp_code = 0;

    if( config & GPIO_CFG_DRIVE_12mA ) {
        for( i = 0; i < 8; i++ ) {
            if( ( pin_mask >> i ) & 1 ) {
                tmp_code |= 0x3UL << ( i * 2 );
            }
        }

        gpio_ptr->gpiopc |= tmp_code;
        gpio_ptr->gpiodr8r |= pin_mask;
        gpio_ptr->gpiodr4r |= pin_mask;
        gpio_ptr->gpiodr12r |= pin_mask;
    }

    if ( config & GPIO_CFG_SLEW_RATE ) {
        if ( config & GPIO_CFG_DRIVE_8mA ) {
            gpio_ptr->gpioslr |= pin_mask;
        } else {
            return;
        }
    } else {
        gpio_ptr->gpioslr &= ~pin_mask;
    }

    if ( config & GPIO_CFG_DIGITAL_ENABLE ) {
        gpio_ptr->gpioden |= pin_mask;
    } else {
        gpio_ptr->gpioden &= ~pin_mask;
    }

    if ( config & GPIO_CFG_ISOLATION_DISABLE ) {
        if( ( GPIOE_BASE_ADDR != *port ) & ( GPIOD_BASE_ADDR != *port ) & ( GPIOB_BASE_ADDR != *port ) &
            ( GPIOK_BASE_ADDR != *port ) & ( GPIOP_BASE_ADDR != *port ) )
        {
            return;
        } else {
            gpio_ptr->gpioamsel |= pin_mask;
        }
    } else {
        if( ( GPIOE_BASE_ADDR == *port ) | ( GPIOD_BASE_ADDR == *port ) | ( GPIOB_BASE_ADDR == *port ) |
            ( GPIOK_BASE_ADDR == *port ) | ( GPIOP_BASE_ADDR == *port ) )
        {
            gpio_ptr->gpioamsel &= ~pin_mask;
        }
    }

    if ( config & GPIO_CFG_ADC_SRC_TRIGGER ) {
        gpio_ptr->gpioadcctl |= pin_mask;
    } else {
        gpio_ptr->gpioadcctl &= ~pin_mask;
    }

    if ( config & GPIO_CFG_ALT_FUNCTION )
        gpio_ptr->gpioafsel |= pin_mask;
    else
        gpio_ptr->gpioafsel &= ~pin_mask;
}

/**
  * @brief  Configure port pins alternate
  *         functions
  * @param  module_pin - desired pin
  *         config     - pin settings
  * @return none
  */
static void _hal_ll_gpio_config_pin_alternate_enable( uint32_t module_pin, uint32_t module_config, bool state ) {
    // Pin, port & alternate function mask declaration & initialization.
    uint8_t pin_mask_raw = 0;
    uint8_t pin_mask     = 0;
    uint8_t port_mask    = 0;
    uint32_t af_mask     = 0;
    uint32_t *port       = 0;

    // Extract appropriate info from "module_pin" variable.
    pin_mask_raw = ( ( module_pin & HAL_LL_GPIO_PIN_MASK ) % PORT_SIZE );
    pin_mask     = ( 0x1UL << pin_mask_raw );
    port_mask    = ( module_pin & HAL_LL_GPIO_PORT_MASK ) / PORT_SIZE;
    af_mask      = ( ( ( module_pin & HAL_LL_GPIO_AF_MASK ) >> 8 ) << ( pin_mask_raw * HAL_LL_GPIO_AFSEL_MULTIPLIER ) );

    // Get appropriate GPIO module.
    port = (uint32_t *)_hal_ll_gpio_port_base[port_mask];

    // Configure basic GPIO settings.
    _hal_ll_gpio_config( &port, pin_mask, module_config );

    // Get appropriate register list.
    hal_ll_gpio_base_handle_t *gpio_ptr = ( hal_ll_gpio_base_handle_t * )( port );

    /*
    * NOTE: On TM4C123 microcontrollers, the GPIO_PCTL register
    * retains a non-zero value after reset. Therefore, clearing specific bits
    * corresponding to the currently selected pin in the register before
    * assigning new values is necessary for proper initialization.
    */
    gpio_ptr->gpiopctl &= ~( HAL_LL_GPIO_PIN_MASK << ( module_pin * HAL_LL_GPIO_AFSEL_MULTIPLIER ));

    if ( state ) {
        // Set appropriate bit in AFSEL register.
        gpio_ptr->gpioafsel |= ( 0x1UL << pin_mask );

        // Set appropriate bit in GPIOPCTL register.
        gpio_ptr->gpiopctl |= af_mask;
    } else {
        // Clear appropriate bit in AFSEL register.
        gpio_ptr->gpioafsel &= ~( 0x1UL << pin_mask );

        // Clear appropriate bit in GPIOPCTL register.
        gpio_ptr->gpiopctl &= ~( af_mask );
    }
}

// ------------------------------------------------------------------------- END
