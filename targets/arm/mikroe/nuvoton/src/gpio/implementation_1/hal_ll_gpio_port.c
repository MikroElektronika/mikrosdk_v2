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
#include "hal_ll_mstpcr.h"

#define hal_ll_gpio_port_get_pin_index(__index) ( ( uint8_t )__index & 0xF )

#define hal_ll_gpio_port_get_port_index(__index) ( ( uint8_t )( __index & 0xF0 ) >> 4 )

#ifdef GPIO_PORT_A
#define GPIO_PORTA_BASE  (0x40004000UL)
#endif
#ifdef GPIO_PORT_B
#define GPIO_PORTB_BASE  (0x40004040UL)
#endif
#ifdef GPIO_PORT_C
#define GPIO_PORTC_BASE  (0x40004080UL)
#endif
#ifdef GPIO_PORT_D
#define GPIO_PORTD_BASE  (0x400040C0UL)
#endif
#ifdef GPIO_PORT_E
#define GPIO_PORTE_BASE  (0x40004100UL)
#endif
#ifdef GPIO_PORT_F
#define GPIO_PORTF_BASE  (0x40004140UL)
#endif
#ifdef GPIO_PORT_G
#define GPIO_PORTG_BASE  (0x40004180UL)
#endif
#ifdef GPIO_PORT_H
#define GPIO_PORTH_BASE  (0x400041C0UL)
#endif

#define CLKEN_OFSET     (24)

/*!< @brief GPIO PORT array */
static const uint32_t hal_ll_gpio_port_base_arr[PORT_COUNT] =
{
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
    GPIO_PORTG_BASE,
    #endif
    #ifdef GPIO_PORTG_BASE
    GPIO_PORTG_BASE,
    #endif
    #ifdef GPIO_PORTH_BASE
    GPIO_PORTH_BASE,
    #endif
};

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

void hal_ll_gpio_analog_input( hal_ll_pin_name_t name ) {
    uint8_t pin_offset;
    uint8_t mfp_offset;
    uint32_t* mfp_p = NULL;

    mfp_offset = name / 8;
    pin_offset = name % 8;

    mfp_p = GPIO_MFP_P + mfp_offset;

    clear_reg_bits( mfp_p, GPIO_MFP_RESET << pin_offset );
    set_reg_bits( mfp_p, GPIO_MFP_ANALOG_INPUT << ( pin_offset * GPIO_MFP_PIN_WITH ) );
}

void hal_ll_gpio_digital_input( uint32_t *port, uint16_t pin_mask ) {
    hal_ll_gpio_config( port, pin_mask, GPIO_MODE_INPUT );
}

void hal_ll_gpio_digital_output( uint32_t *port, uint16_t pin_mask ) {
    hal_ll_gpio_config( port, pin_mask, GPIO_MODE_OUTPUT );
}

void hal_ll_gpio_module_struct_init( module_struct const *module, bool state ) {
    int32_t index = 0;

    while ( module->pins[ index ] != GPIO_MODULE_STRUCT_END ) {
        hal_ll_gpio_config_pin_alternate_enable( module->pins[ index ], module->configs[ index ], state );

        index++;
    }
}

static void hal_ll_gpio_clock_enable( hal_ll_port_name_t port_index ) {
    set_reg_bit( CLK_AHBCLK, ( CLKEN_OFSET + port_index ) );
}


// ------------------------------------------------ STATIC FUNCTION DEFINITIONS

static uint8_t hal_ll_gpio_pin_index( hal_ll_pin_name_t name ) {
    return hal_ll_gpio_port_get_pin_index( name );
}

static uint32_t hal_ll_gpio_get_port_number(uint32_t base_addr)
{
    for ( int i = 0; i < sizeof(hal_ll_gpio_port_base_arr) / sizeof(hal_ll_gpio_port_base_arr[0]); i++ ) {
        if ( hal_ll_gpio_port_base_arr[i] == base_addr ) {
            return i;
        }
    }
    return -1;
}

static void hal_ll_gpio_config( uint32_t *port, uint16_t pin_mask, uint32_t config ) {
    uint32_t pin_pos        = 0;
    uint32_t pos            = 0;
    uint32_t current_pin    = 0;

    uint32_t pin_index = ( pin_mask == 0xFFFF ) ? 0xFFFF : __builtin_ctz( pin_mask );
    hal_ll_port_name_t port_index;
    port_index = hal_ll_gpio_get_port_number( *port );
    hal_ll_gpio_base_handle_t *port_ptr = ( hal_ll_gpio_base_handle_t * ) *port;

    hal_ll_gpio_clock_enable( port_index );

    if ( pin_mask == GPIO_PIN_MASK_LOW ) {
        port_ptr->mode &= ~HAL_LL_NIBBLE_LOW_32BIT;

        if ( config == GPIO_MODE_OUTPUT ) {
            port_ptr->mode |=  GPIO_PORT_LOW_MODE_OUTPUT;
            return;
        }
        if ( config == GPIO_MODE_INPUT ) {
            port_ptr->mode &= ~HAL_LL_NIBBLE_LOW_32BIT;
            port_ptr->pusel = ( port_ptr->pusel & ~HAL_LL_NIBBLE_LOW_32BIT ) | GPIO_PORT_LOW_PUSEL_PULL_DOWN;
            return;
        }
    }

    if ( pin_mask == GPIO_PIN_MASK_HIGH ) {
        port_ptr->mode &= ~HAL_LL_NIBBLE_HIGH_32BIT;

        if ( config == GPIO_MODE_OUTPUT ) {
            port_ptr->mode |= GPIO_PORT_HIGH_MODE_OUTPUT;
            return;
        }
        if ( config == GPIO_MODE_INPUT ) {
            port_ptr->mode &= ~HAL_LL_NIBBLE_HIGH_32BIT;
            port_ptr->pusel = ( port_ptr->pusel & ~HAL_LL_NIBBLE_HIGH_32BIT ) | GPIO_PORT_HIGH_PUSEL_PULL_DOWN;
            return;
        }
    }

    if ( pin_mask == GPIO_PIN_MASK_ALL ) {
        if ( config == GPIO_MODE_OUTPUT ) {
            port_ptr->mode |= GPIO_PORT_ALL_MODE_OUTPUT;
            return;
        }
        if ( config == GPIO_MODE_INPUT ) {
            port_ptr->mode |= HAL_LL_CLEAR;
            port_ptr->pusel = GPIO_PORT_ALL_PUSEL_PULL_DOWN;
            return;
        }
    }

    for ( pin_pos = 0; pin_pos < 16; pin_pos++ ) {
        pos = ( ( uint32_t )0x01 ) << pin_pos;
        current_pin = ( pin_mask ) & pos;

        if ( current_pin == pos ) {
            port_ptr->mode &= ~( GPIO_MODER_MODER0 << ( pin_pos * GPIO_MODE_PIN_WIDTH ) );

            if ( config == GPIO_MODE_OUTPUT ) {
                port_ptr->mode |= ( GPIO_MODE_OUTPUT << ( pin_pos * GPIO_MODE_PIN_WIDTH ) );
            }
            if ( config == GPIO_MODE_INPUT ) {
                port_ptr->mode |= ( GPIO_MODE_INPUT << ( pin_pos * GPIO_MODE_PIN_WIDTH ) );
                port_ptr->pusel = ( port_ptr->pusel & ~( GPIO_PUSEL_DISABLE3 << ( pin_pos * GPIO_MODE_PIN_WIDTH ) ) ) | ( GPIO_PUSEL_PULL_DOWN << ( pin_pos * GPIO_MODE_PIN_WIDTH ) );
            }
        }
    }

}

static void hal_ll_gpio_config_pin_alternate_enable( uint32_t module_pin, uint32_t module_config, bool state ) {
    uint8_t pin_index;
    hal_ll_pin_name_t pin_name;
    hal_ll_port_name_t port_name;
    uint8_t mfp_offset;
    uint8_t mfp_pin_offset;
    uint32_t* mfp_p = NULL;

    pin_name = module_pin & GPIO_PIN_NAME_MASK;

    pin_index = hal_ll_gpio_pin_index( pin_name );

    port_name = hal_ll_gpio_port_index( module_pin & 0xFF );

    mfp_offset = pin_name / 8;
    mfp_pin_offset = pin_name % 8;

    mfp_p = GPIO_MFP_P + mfp_offset;

    clear_reg_bits( mfp_p, GPIO_MFP_RESET << mfp_pin_offset );
    set_reg_bits( mfp_p, module_config << ( mfp_pin_offset * GPIO_MFP_PIN_WITH ) );
}

// ------------------------------------------------------------------------- END