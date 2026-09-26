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
#include "hal_ll_gpio.h"
#include "hal_ll_cg.h"
#include "hal_ll_gpio_constants.h"
#include "delays.h"

#define HAL_LL_EXP_PCA9538A_ADDR ( 0x73 )

#define hal_ll_gpio_port_get_pin_index( __index ) ( (uint8_t) __index & 0xF )

#define hal_ll_gpio_port_get_port_index( __index ) ( (uint8_t) ( __index & 0xF0 ) >> 4 )

#ifdef GPIO_PORT_A
    #define GPIO_PORTA_BASE ( 0x40080000UL )
#endif
#ifdef GPIO_PORT_B
    #define GPIO_PORTB_BASE ( 0x40080100UL )
#endif
#ifdef GPIO_PORT_C
    #define GPIO_PORTC_BASE ( 0x40080200UL )
#endif
#ifdef GPIO_PORT_D
    #define GPIO_PORTD_BASE ( 0x40080300UL )
#endif
#ifdef GPIO_PORT_E
    #define GPIO_PORTE_BASE ( 0x40080400UL )
#endif
#ifdef GPIO_PORT_F
    #define GPIO_PORTF_BASE ( 0x40080500UL )
#endif
#ifdef GPIO_PORT_G
    #define GPIO_PORTG_BASE ( 0x40080600UL )
#endif
#ifdef GPIO_PORT_H
    #define GPIO_PORTH_BASE ( 0x40080700UL )
#endif
#ifdef GPIO_PORT_J
    #define GPIO_PORTJ_BASE ( 0x40080800UL )
#endif
#ifdef GPIO_PORT_K
    #define GPIO_PORTK_BASE ( 0x40080900UL )
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
    #else
    0,
    #endif
    #ifdef GPIO_PORTB_BASE
    GPIO_PORTB_BASE,
    #else
    0,
    #endif
    #ifdef GPIO_PORTC_BASE
    GPIO_PORTC_BASE,
    #else
    0,
    #endif
    #ifdef GPIO_PORTD_BASE
    GPIO_PORTD_BASE,
    #else
    0,
    #endif
    #ifdef GPIO_PORTE_BASE
    GPIO_PORTE_BASE,
    #else
    0,
    #endif
    #ifdef GPIO_PORTF_BASE
    GPIO_PORTF_BASE,
    #else
    0,
    #endif
    #ifdef GPIO_PORTG_BASE
    GPIO_PORTG_BASE,
    #else
    0,
    #endif
    #ifdef GPIO_PORTH_BASE
    GPIO_PORTH_BASE,
    #else
    0,
    #endif
    #ifdef GPIO_PORTJ_BASE
    GPIO_PORTJ_BASE,
    #else
    0,
    #endif
    #ifdef GPIO_PORTK_BASE
    GPIO_PORTK_BASE,
    #else
    0,
    #endif
    #ifdef GPIO_PORTL_BASE
    GPIO_PORTL_BASE,
    #else
    0,
    #endif
    #ifdef GPIO_PORTM_BASE
    GPIO_PORTM_BASE,
    #else
    0,
    #endif
    #ifdef GPIO_PORTN_BASE
    GPIO_PORTN_BASE,
    #else
    0,
    #endif
    #ifdef GPIO_PORTU_BASE
    GPIO_PORTU_BASE,
    #else
    0,
    #endif
    #ifdef GPIO_PORTV_BASE
    GPIO_PORTV_BASE,
    #else
    0
    #endif
};

#define PROTECT_DISABLE ( 0xC1 )

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
    hal_ll_gpio_config( port, pin_mask, GPIO_CFG_MODE_ANALOG_INPUT );
}

void hal_ll_gpio_digital_input( uint32_t *port, uint16_t pin_mask ) {
    hal_ll_gpio_config( port, pin_mask, GPIO_CFG_IE | GPIO_CFG_PULL_UP );
}

void hal_ll_gpio_digital_output( uint32_t *port, uint16_t pin_mask ) {
    hal_ll_gpio_config( port, pin_mask, GPIO_CFG_PORT_DIRECTION_OUTPUT );
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

static uint8_t hal_ll_gpio_get_port_number( uint32_t base_addr ) {
    for ( int i = 0; i < sizeof( hal_ll_gpio_port_base_arr ) / sizeof( hal_ll_gpio_port_base_arr[0] ); i++ ) {
        if ( hal_ll_gpio_port_base_arr[i] == base_addr ) {
            return i; // Port number.
        }
    }
    return 0xFF; // Not found.
}

static void hal_ll_gpio_config( uint32_t *port, uint16_t pin_mask, uint32_t config ) {
    hal_ll_gpio_base_handle_t *gpio_ptr = (hal_ll_gpio_base_handle_t *) *port;

    hal_ll_gpio_clock_enable( *port );

    // Check if using new flag-based configuration
    if ( config & (GPIO_CFG_CR | GPIO_CFG_OD |
                   GPIO_CFG_PULL_UP | GPIO_CFG_PULL_DOWN |
                   GPIO_CFG_IE | GPIO_OUTPUT_HIGH) ) {

        // New flag-based configuration
        if ( config & GPIO_OUTPUT_HIGH ) {
            gpio_ptr->data |= pin_mask;    // set output as high
        } else {
            gpio_ptr->data &= ~pin_mask;   // set output as low
        }
        // Configure Control Register (CR) - Direction
        if ( config & GPIO_CFG_CR ) {
            gpio_ptr->cr |= pin_mask;    // Enable Output
        } else {
            gpio_ptr->cr &= ~pin_mask;   // Disable Output (Input mode)
        }

        // Configure Input Enable (IE)
        if ( config & GPIO_CFG_IE ) {
            gpio_ptr->ie |= pin_mask;    // Enable Input
        } else {
            gpio_ptr->ie &= ~pin_mask;   // Disable Input
        }

        // Configure Open Drain (OD)
        if ( config & GPIO_CFG_OD ) {
            gpio_ptr->od |= pin_mask;    // Enable Open Drain
        } else {
            gpio_ptr->od &= ~pin_mask;   // Disable Open Drain (Push-Pull)
        }

        // Configure Pull-up (PUP)
        if ( config & GPIO_CFG_PULL_UP ) {
            gpio_ptr->pup |= pin_mask;   // Enable Pull-up
        } else {
            gpio_ptr->pup &= ~pin_mask;  // Disable Pull-up
        }

        // Configure Pull-down (PDN)
        if ( config & GPIO_CFG_PULL_DOWN ) {
            gpio_ptr->pdn |= pin_mask;   // Enable Pull-down
        } else {
            gpio_ptr->pdn &= ~pin_mask;  // Disable Pull-down
        }

        return; // Exit early for flag-based configuration

    } else if ( config == GPIO_CFG_MODE_ANALOG_INPUT ) {
        gpio_ptr->ie &= ~pin_mask;
        gpio_ptr->cr &= ~pin_mask;
        gpio_ptr->pdn &= ~pin_mask;
        gpio_ptr->pup &= ~pin_mask;
        gpio_ptr->od &= ~pin_mask;
    }
}

static void hal_ll_gpio_config_pin_alternate_enable( uint32_t module_pin, uint32_t module_config, bool state ) {
    uint8_t                              pin_index;
    hal_ll_pin_name_t                    pin_name;
    hal_ll_port_name_t                   port_name;
    hal_ll_gpio_base_handle_t           *port_ptr;
    hal_ll_gpio_alternate_function_t     alt_offset;

    pin_name  = module_pin & GPIO_PIN_NAME_MASK;
    pin_index = hal_ll_gpio_pin_index( pin_name );
    port_name = hal_ll_gpio_port_index( module_pin & 0xFF );
    port_ptr  = (hal_ll_gpio_base_handle_t *) hal_ll_gpio_port_base( port_name );

    uint32_t *fr_registers[] = { &port_ptr->fr1, &port_ptr->fr2, &port_ptr->fr3, &port_ptr->fr4,
                                 &port_ptr->fr5, &port_ptr->fr6, &port_ptr->fr7 };

    uint32_t mask = (uint32_t) ( 1 << pin_index );

    hal_ll_gpio_config( (uint32_t*)&port_ptr, mask, module_config );

    //Clear all FR registers for this pin
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
    uint32_t *sysma_addr = (uint32_t *) HAL_LL_CG_BASE_FSYSENA_ADDR;
    uint32_t *protect_addr = (uint32_t *) HAL_LL_CG_BASE_PROTECT_ADDR;

    port_index = hal_ll_gpio_get_port_number( port );

    *protect_addr = PROTECT_DISABLE;

    switch ( port_index ) {
        case GPIO_PORT_INDEX_0:
            set_reg_bit( sysma_addr, FSYSMENA_PORTA );
            break;

        case GPIO_PORT_INDEX_1:
            set_reg_bit( sysma_addr, FSYSMENA_PORTB );
            break;

        case GPIO_PORT_INDEX_2:
            set_reg_bit( sysma_addr, FSYSMENA_PORTC );
            break;

        case GPIO_PORT_INDEX_3:
            set_reg_bit( sysma_addr, FSYSMENA_PORTD );
            break;

        case GPIO_PORT_INDEX_4:
            set_reg_bit( sysma_addr, FSYSMENA_PORTE );
            break;

        case GPIO_PORT_INDEX_5:
            set_reg_bit( sysma_addr, FSYSMENA_PORTF );
            break;

        case GPIO_PORT_INDEX_6:
            set_reg_bit( sysma_addr, FSYSMENA_PORTG );
            break;

        case GPIO_PORT_INDEX_7:
            set_reg_bit( sysma_addr, FSYSMENA_PORTH );
            break;
        case GPIO_PORT_INDEX_8:
            set_reg_bit( sysma_addr, FSYSMENA_PORTJ );
            break;

        case GPIO_PORT_INDEX_9:
            set_reg_bit( sysma_addr, FSYSMENA_PORTK );
            break;

        case GPIO_PORT_INDEX_10:
            set_reg_bit( sysma_addr, FSYSMENA_PORTL );
            break;

        case GPIO_PORT_INDEX_11:
            set_reg_bit( sysma_addr, FSYSMENA_PORTM );
            break;
        case GPIO_PORT_INDEX_12:
            set_reg_bit( sysma_addr, FSYSMENA_PORTN );
            break;

        case GPIO_PORT_INDEX_13:
            set_reg_bit( sysma_addr, FSYSMENA_PORTU );
            break;

        case GPIO_PORT_INDEX_14:
            set_reg_bit( sysma_addr, FSYSMENA_PORTV );
            break;

        default:
            // Do nothing
            break;
    }
}

#define HAL_LL_EXP_I2C_SCL_PIN   GPIO_PA5
#define HAL_LL_EXP_I2C_SDA_PIN   GPIO_PA6 

#define HAL_LL_EXP_REG_INPUT_PORT   0x00
#define HAL_LL_EXP_REG_OUTPUT_PORT  0x01
#define HAL_LL_EXP_REG_CONFIG       0x03

#define HAL_LL_EXP_BIT_DELAY_MS     2

static uint8_t hal_ll_exp_ready         = 0;
static uint8_t hal_ll_exp_config_shadow = 0xFF; 
static uint8_t hal_ll_exp_output_shadow = 0x00;

static hal_ll_gpio_pin_t hal_ll_exp_scl_pin;
static hal_ll_gpio_pin_t hal_ll_exp_sda_pin;

static void hal_ll_exp_scl_high( void ) {
    hal_ll_gpio_configure_pin( &hal_ll_exp_scl_pin, HAL_LL_EXP_I2C_SCL_PIN, HAL_LL_GPIO_DIGITAL_INPUT ); // released
}
static void hal_ll_exp_scl_low( void ) {
    hal_ll_gpio_configure_pin( &hal_ll_exp_scl_pin, HAL_LL_EXP_I2C_SCL_PIN, HAL_LL_GPIO_DIGITAL_OUTPUT );
    hal_ll_gpio_write_pin_output( &hal_ll_exp_scl_pin, 0 );
}
static void hal_ll_exp_sda_high( void ) {
    hal_ll_gpio_configure_pin( &hal_ll_exp_sda_pin, HAL_LL_EXP_I2C_SDA_PIN, HAL_LL_GPIO_DIGITAL_INPUT ); // released
}
static void hal_ll_exp_sda_low( void ) {
    hal_ll_gpio_configure_pin( &hal_ll_exp_sda_pin, HAL_LL_EXP_I2C_SDA_PIN, HAL_LL_GPIO_DIGITAL_OUTPUT );
    hal_ll_gpio_write_pin_output( &hal_ll_exp_sda_pin, 0 );
}
static uint8_t hal_ll_exp_sda_read( void ) {
    hal_ll_gpio_configure_pin( &hal_ll_exp_sda_pin, HAL_LL_EXP_I2C_SDA_PIN, HAL_LL_GPIO_DIGITAL_INPUT );
    return hal_ll_gpio_read_pin_input( &hal_ll_exp_sda_pin );
}

static void hal_ll_exp_i2c_start( void ) {
    hal_ll_exp_sda_high(); hal_ll_exp_scl_high(); Delay_ms( HAL_LL_EXP_BIT_DELAY_MS );
    hal_ll_exp_sda_low();  Delay_ms( HAL_LL_EXP_BIT_DELAY_MS );
    hal_ll_exp_scl_low();  Delay_ms( HAL_LL_EXP_BIT_DELAY_MS );
}

static void hal_ll_exp_i2c_stop( void ) {
    hal_ll_exp_sda_low();  Delay_ms( HAL_LL_EXP_BIT_DELAY_MS );
    hal_ll_exp_scl_high(); Delay_ms( HAL_LL_EXP_BIT_DELAY_MS );
    hal_ll_exp_sda_high(); Delay_ms( HAL_LL_EXP_BIT_DELAY_MS );
}

static uint8_t hal_ll_exp_i2c_write_byte( uint8_t data ) {
    uint8_t ack;

    for ( int8_t i = 7; i >= 0; i-- ) {
        if ( data & ( 1 << i ) ) { hal_ll_exp_sda_high(); } else { hal_ll_exp_sda_low(); }
        Delay_ms( HAL_LL_EXP_BIT_DELAY_MS );
        hal_ll_exp_scl_high(); Delay_ms( HAL_LL_EXP_BIT_DELAY_MS );
        hal_ll_exp_scl_low();  Delay_ms( HAL_LL_EXP_BIT_DELAY_MS );
    }

    hal_ll_exp_sda_high(); Delay_ms( HAL_LL_EXP_BIT_DELAY_MS );
    hal_ll_exp_scl_high(); Delay_ms( HAL_LL_EXP_BIT_DELAY_MS );
    ack = ( hal_ll_exp_sda_read() == 0 );
    hal_ll_exp_scl_low();  Delay_ms( HAL_LL_EXP_BIT_DELAY_MS );

    return ack;
}

static uint8_t hal_ll_exp_i2c_read_byte( uint8_t send_ack ) {
    uint8_t data = 0;

    hal_ll_exp_sda_high();

    for ( int8_t i = 7; i >= 0; i-- ) {
        hal_ll_exp_scl_high(); Delay_ms( HAL_LL_EXP_BIT_DELAY_MS );
        if ( hal_ll_exp_sda_read() ) { data |= ( 1 << i ); }
        hal_ll_exp_scl_low(); Delay_ms( HAL_LL_EXP_BIT_DELAY_MS );
    }

    if ( send_ack ) { hal_ll_exp_sda_low(); } else { hal_ll_exp_sda_high(); }
    Delay_ms( HAL_LL_EXP_BIT_DELAY_MS );
    hal_ll_exp_scl_high(); Delay_ms( HAL_LL_EXP_BIT_DELAY_MS );
    hal_ll_exp_scl_low();  Delay_ms( HAL_LL_EXP_BIT_DELAY_MS );
    hal_ll_exp_sda_high();

    return data;
}

static uint8_t hal_ll_exp_pca_write_reg( uint8_t reg, uint8_t value ) {
    uint8_t ok = 1;
    hal_ll_exp_i2c_start();
    ok &= hal_ll_exp_i2c_write_byte( ( HAL_LL_EXP_PCA9538A_ADDR << 1 ) | 0 );
    ok &= hal_ll_exp_i2c_write_byte( reg );
    ok &= hal_ll_exp_i2c_write_byte( value );
    hal_ll_exp_i2c_stop();
    return ok;
}

static uint8_t hal_ll_exp_pca_read_reg( uint8_t reg ) {
    uint8_t value;
    hal_ll_exp_i2c_start();
    hal_ll_exp_i2c_write_byte( ( HAL_LL_EXP_PCA9538A_ADDR << 1 ) | 0 );
    hal_ll_exp_i2c_write_byte( reg );
    hal_ll_exp_i2c_start();
    hal_ll_exp_i2c_write_byte( ( HAL_LL_EXP_PCA9538A_ADDR << 1 ) | 1 );
    value = hal_ll_exp_i2c_read_byte( 0 );
    hal_ll_exp_i2c_stop();
    return value;
}

static void hal_ll_exp_lazy_init( void ) {
    if ( hal_ll_exp_ready ) {
        return;
    }

    hal_ll_exp_sda_high();
    hal_ll_exp_scl_high();
    Delay_ms( 10 );
    hal_ll_exp_ready = 1;
}


uint8_t hal_ll_gpio_expander_pin_check( hal_ll_pin_name_t name ) {
    return ( hal_ll_gpio_port_get_port_index( name ) == HAL_LL_GPIO_EXPANDER_PORT_INDEX ) ? 1 : 0;
}

void hal_ll_gpio_expander_configure_pin( uint8_t bit, hal_ll_gpio_direction_t direction ) {
    hal_ll_exp_lazy_init();

    if ( HAL_LL_GPIO_DIGITAL_INPUT == direction ) {
        hal_ll_exp_config_shadow |= ( 1 << bit );
    } else {
        hal_ll_exp_config_shadow &= ~( 1 << bit );
    }

    hal_ll_exp_pca_write_reg( HAL_LL_EXP_REG_CONFIG, hal_ll_exp_config_shadow );

    if ( HAL_LL_GPIO_DIGITAL_OUTPUT == direction ) {
        hal_ll_exp_pca_write_reg( HAL_LL_EXP_REG_OUTPUT_PORT, hal_ll_exp_output_shadow );
    }
}

uint8_t hal_ll_gpio_expander_read_pin( uint8_t bit ) {
    if ( 0 == ( hal_ll_exp_config_shadow & ( 1 << bit ) ) ) {
        return ( hal_ll_exp_output_shadow & ( 1 << bit ) ) ? 0x01 : 0x00;
    }

    uint8_t input_val = hal_ll_exp_pca_read_reg( HAL_LL_EXP_REG_INPUT_PORT );
    return ( input_val & ( 1 << bit ) ) ? 0x01 : 0x00;
}

void hal_ll_gpio_expander_write_pin( uint8_t bit, uint8_t value ) {
    if ( value ) {
        hal_ll_exp_output_shadow |= ( 1 << bit );
    } else {
        hal_ll_exp_output_shadow &= ~( 1 << bit );
    }
    hal_ll_exp_pca_write_reg( HAL_LL_EXP_REG_OUTPUT_PORT, hal_ll_exp_output_shadow );
}

// ------------------------------------------------------------------------- END
