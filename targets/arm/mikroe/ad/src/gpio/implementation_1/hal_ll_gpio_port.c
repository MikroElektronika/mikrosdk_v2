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
#include "hal_ll_pclkdis.h"

// MCR_GPIO4_CTRL packs 4 control bits per pin (do, oe, pe, in) instead of
// using separate set/clear registers like the other ports.
#define GPIO4_CTRL_PIN_FIELD_WIDTH 4U
#define GPIO4_CTRL_DO_OFFSET       0U
#define GPIO4_CTRL_OE_OFFSET       1U
#define GPIO4_CTRL_PE_OFFSET       2U
#define GPIO4_CTRL_IN_OFFSET       3U
#define GPIO4_CTRL_PIN_COUNT       2U

#define hal_ll_gpio_port_get_pin_index(__index) ( ( uint8_t )__index & 0xF )

#define hal_ll_gpio_port_get_port_index(__index) ( ( uint8_t )( __index & 0xF0 ) >> 4 )

/*!< @brief GPIO PORT array */
static const uint32_t hal_ll_gpio_port_base_arr[] =
{
    #ifdef GPIO_PORT_0
    GPIO_PORT0_BASE,
    #else
    0,
    #endif
    #ifdef GPIO_PORT_1
    GPIO_PORT1_BASE,
    #else
    0,
    #endif
    #ifdef GPIO_PORT_2
    GPIO_PORT2_BASE,
    #else
    0,
    #endif
    #ifdef GPIO_PORT_3
    GPIO_PORT3_BASE,
    #else
    0,
    #endif
    #ifdef GPIO_PORT_4
    GPIO_PORT4_BASE,
    #else
    0,
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

/**
  * @brief  Fetch the port address based on the provided port index.
  * @param  uint8_t - the index of the port
  * @return uint32_t - base address of the port
  */
static uint32_t hal_ll_gpio_get_base_addr( uint8_t port_index );

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

    while ( module->pins[ index ] != GPIO_MODULE_STRUCT_END )
    {
        hal_ll_gpio_config_pin_alternate_enable( module->pins[ index ], module->configs[ index ], state );

        index++;
    }
}

// ------------------------------------------------ STATIC FUNCTION DEFINITIONS

static uint8_t hal_ll_gpio_pin_index( hal_ll_pin_name_t name ) {
    return hal_ll_gpio_port_get_pin_index( name );
}

static uint8_t hal_ll_gpio_get_port_number(uint32_t base_addr)
{
    for (int i = 0; i < sizeof(hal_ll_gpio_port_base_arr) / sizeof(hal_ll_gpio_port_base_arr[0]); i++) {
        if (hal_ll_gpio_port_base_arr[i] == base_addr) {
            return i; // Port number.
        }
    }
    return 0xFF; // Not found.
}

static inline uint32_t hal_ll_gpio_get_base_addr( uint8_t port_index )
{
    if ( PORT_COUNT > port_index ) {
        return hal_ll_gpio_port_base_arr[port_index];
    }
    return 0;
}

static void hal_ll_gpio_config( uint32_t *port, uint16_t pin_mask, uint32_t config ) {
    uint32_t pin_index = ( pin_mask == 0xFFFF ) ? 0xFFFF : __builtin_ctz(pin_mask);
    hal_ll_gpio_base_handle_t *gpio_ptr = (hal_ll_gpio_base_handle_t *) *port;
    hal_ll_port_name_t port_index;

    if ( GPIO_PORT0_BASE == *port ) {
        clear_reg_bit( _GCR_PCLKDIS0_, GCR_PCLKDIS0_0 );
    } else if ( GPIO_PORT1_BASE == *port ) {
        clear_reg_bit( _GCR_PCLKDIS0_, GCR_PCLKDIS0_1 );
    } else if ( GPIO_PORT2_BASE == *port ) {
        clear_reg_bit( _GCR_PCLKDIS0_, GCR_PCLKDIS0_2 );
    }

    if ( config & GPIO_ALT_FUNC_MASK ) {
        // 0: Alternate function selected
        gpio_ptr->en0_clr |= pin_mask;
    } else {
        // 1: I/O mode selected
        gpio_ptr->en0_set |= pin_mask;
    }

    if ( GPIO_PORT4_BASE == *port ) {
        volatile uint32_t *gpio4_ctrl = ( volatile uint32_t * ) *port;
        uint8_t bit_offset;

        if ( GPIO4_CTRL_PIN_COUNT <= pin_index ) {
            return;
        }

        bit_offset = pin_index * GPIO4_CTRL_PIN_FIELD_WIDTH;

        // Output Enable (oe) - bit 1 of the pin field: 1 = output mode, 0 = input mode
        if ( config & GPIO_CFG_OUT ) {
            *gpio4_ctrl |= ( 1UL << ( bit_offset + GPIO4_CTRL_OE_OFFSET ) );
        } else {
            *gpio4_ctrl &= ~( 1UL << ( bit_offset + GPIO4_CTRL_OE_OFFSET ) );
        }

        // Pull Enable (pe) - bit 2 of the pin field, active-low: 0 = enabled, 1 = disabled
        if ( config & ( GPIO_CFG_PULL_UP | GPIO_CFG_PULL_DOWN ) ) {
            *gpio4_ctrl &= ~( 1UL << ( bit_offset + GPIO4_CTRL_PE_OFFSET ) );

            // Pull direction (do) - bit 0 of the pin field, shared with output
            // data. Only meaningful here while oe = 0 (input mode).
            if ( config & GPIO_CFG_PULL_UP ) {
                *gpio4_ctrl |= ( 1UL << ( bit_offset + GPIO4_CTRL_DO_OFFSET ) );
            } else {
                *gpio4_ctrl &= ~( 1UL << ( bit_offset + GPIO4_CTRL_DO_OFFSET ) );
            }
        } else {
            *gpio4_ctrl |= ( 1UL << ( bit_offset + GPIO4_CTRL_PE_OFFSET ) );
        }

        return;
    } else if ( config & ( GPIO_CFG_OUT | GPIO_CFG_OD | GPIO_CFG_PULL_UP |
                           GPIO_CFG_PULL_DOWN | GPIO_CFG_IE ) ) {

        // Configure Control Register (CR) - Direction
        if ( config & GPIO_CFG_OUT ) {
            gpio_ptr->outen_set |= pin_mask;   // Enable Output
            gpio_ptr->out_set |= pin_mask;     // Set value to low (default)
        } else {
            gpio_ptr->outen_clr |= pin_mask;   // Disable Output (Input mode)
        }

        // Configure Input Enable (IE)
        if ( config & GPIO_CFG_IE ) {
            gpio_ptr->inen |= pin_mask;   // Enable Input
        } else {
            gpio_ptr->inen |= pin_mask;   // Disable Input
        }

        // TODO: Open-drain?
        // // Configure Open Drain (OD)
        // if ( config & GPIO_CFG_OD ) {
        //     gpio_ptr->od |= pin_mask;    // Enable Open Drain
        // } else {
        //     gpio_ptr->od &= ~pin_mask;   // Disable Open Drain (Push-Pull)
        // }

        // TODO : Pull-up and Pull-down?
        // // Configure Pull-up (PUP)
        // if ( config & GPIO_CFG_PULL_UP ) {
        //     gpio_ptr->pup |= pin_mask;   // Enable Pull-up
        // } else {
        //     gpio_ptr->pup &= ~pin_mask;  // Disable Pull-up
        // }

        // // Configure Pull-down (PDN)
        // if ( config & GPIO_CFG_PULL_DOWN ) {
        //     gpio_ptr->pdn |= pin_mask;   // Enable Pull-down
        // } else {
        //     gpio_ptr->pdn &= ~pin_mask;  // Disable Pull-down
        // }

        return; // Exit early for flag-based configuration
    }
}

static void hal_ll_gpio_config_pin_alternate_enable( uint32_t module_pin, uint32_t module_config, bool state ) {
    uint8_t pin_index;
    hal_ll_pin_name_t pin_name;
    hal_ll_port_name_t port_name;
    hal_ll_gpio_base_handle_t *port_ptr;
    uint32_t *port;
    uint8_t alternate_function;

    pin_index = hal_ll_gpio_pin_index( pin_name );
    uint32_t mask = (uint32_t) ( 1 << pin_index );

    hal_ll_gpio_config( (uint32_t*)&port_ptr, mask, module_config );

    alternate_function = ( ( module_pin & GPIO_ALT_FUNC_MASK ) >> GPIO_AF_OFFSET );

    if ( state && ( alternate_function >= 1 && alternate_function <= 3 ) ) {
        switch ( alternate_function ) {
            case 1:
                port_ptr->en1_clr |= mask;
                port_ptr->en2_clr |= mask;
                break;

            case 2:
                port_ptr->en1_set |= mask;
                port_ptr->en2_clr |= mask;
                break;

            case 3:
                port_ptr->en1_clr |= mask;
                port_ptr->en2_set |= mask;
                break;

            default:
                break;
        }
    }
}

// ------------------------------------------------------------------------- END
