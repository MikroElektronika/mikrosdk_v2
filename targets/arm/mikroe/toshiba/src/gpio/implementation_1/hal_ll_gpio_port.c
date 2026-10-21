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
#include "hal_ll_cg.h"
#include "hal_ll_gpio_constants.h"

#define hal_ll_gpio_port_get_pin_index( __index ) ( (uint8_t) ( ( __index ) & 0xF ) )

#define hal_ll_gpio_port_get_port_index( __index ) ( (uint8_t) ( ( __index ) >> 4 ) )

#define PROTECT_DISABLE ( 0xC1 )

#if defined(TMPM4L)
    #define GPIO_ALTERNATE_FUNCTION_LAST GPIO_ALTERNATE_FUNCTION_8
#elif defined(TMPM3H)
    // TMPM3H ports have only [PxFR1] to [PxFR6]
    #define GPIO_ALTERNATE_FUNCTION_LAST GPIO_ALTERNATE_FUNCTION_6
#else
    #define GPIO_ALTERNATE_FUNCTION_LAST GPIO_ALTERNATE_FUNCTION_7
#endif

/*!< @brief Port clock supply bit is the port number in this register (CG-M3H(1) Table 1.11, TMPM4L/TMPM4K CG). */
#if defined(TMPM4K)
    #define GPIO_PORT_CLOCK_REG_ADDR HAL_LL_CG_BASE_FSYSMENA_ADDR
#else
    #define GPIO_PORT_CLOCK_REG_ADDR HAL_LL_CG_BASE_FSYSENA_ADDR
#endif

#ifdef TMPM3H
    // TMPM3H port W clock is [CGFSYSENB]<IPENB27> instead of [CGFSYSENA]<IPENA18>
    #define GPIO_PORT_W_INDEX          (18)
    #define GPIO_PORT_W_CLOCK_BIT      (27)
#endif

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
    return HAL_LL_GPIO_PORT_BASE + ( (uint32_t) name * GPIO_PORT_REG_STRIDE );
}

void hal_ll_gpio_analog_input( uint32_t *port, uint16_t pin_mask ) {
    hal_ll_gpio_config( port, pin_mask, GPIO_CFG_MODE_ANALOG_INPUT );
}

void hal_ll_gpio_digital_input( uint32_t *port, uint16_t pin_mask ) {
    hal_ll_gpio_config( port, pin_mask, GPIO_CFG_IE | GPIO_CFG_PULL_DOWN );
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
    return (uint8_t) ( ( base_addr - HAL_LL_GPIO_PORT_BASE ) / GPIO_PORT_REG_STRIDE );
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
    port_name = hal_ll_gpio_port_index( pin_name );
    port_ptr  = (hal_ll_gpio_base_handle_t *) hal_ll_gpio_port_base( port_name );

    uint32_t *fr_registers[] = { &port_ptr->fr1, &port_ptr->fr2, &port_ptr->fr3, &port_ptr->fr4,
                                 &port_ptr->fr5, &port_ptr->fr6, &port_ptr->fr7,
                                 #ifdef TMPM4L
                                 &port_ptr->fr8
                                 #endif
                               };

    uint32_t mask = (uint32_t) ( 1 << pin_index );

    hal_ll_gpio_config( (uint32_t*)&port_ptr, mask, module_config );

    //Clear all FR registers for this pin
    for ( int i = 0; i < GPIO_ALTERNATE_FUNCTION_LAST; i++ ) {
        clear_reg_bit( fr_registers[i], pin_index );
    }

    alt_offset = ( ( module_pin & ~GPIO_PIN_NAME_MASK ) >> GPIO_AF_OFFSET );

    if ( state && ( alt_offset >= GPIO_ALTERNATE_FUNCTION_1 && alt_offset <= GPIO_ALTERNATE_FUNCTION_LAST ) ) {
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

            #ifdef TMPM4L
            case GPIO_ALTERNATE_FUNCTION_8:
                port_ptr->fr8 |= mask;
                break;
            #endif

            default:
                break;
        }
    }
}

static void hal_ll_gpio_clock_enable( uint32_t port ) {
    uint32_t *clock_addr   = (uint32_t *) GPIO_PORT_CLOCK_REG_ADDR;
    uint32_t *protect_addr = (uint32_t *) HAL_LL_CG_BASE_PROTECT_ADDR;
    uint8_t   port_index   = hal_ll_gpio_get_port_number( port );

    set_reg_bits( protect_addr, PROTECT_DISABLE );

    #ifdef TMPM3H
    if ( GPIO_PORT_W_INDEX == port_index ) {
        set_reg_bit( (uint32_t *) HAL_LL_CG_BASE_FSYSENB_ADDR, GPIO_PORT_W_CLOCK_BIT );
        return;
    }
    #endif

    set_reg_bit( clock_addr, port_index );
}

// ------------------------------------------------------------------------- END
