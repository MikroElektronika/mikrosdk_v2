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

#define hal_ll_gpio_port_get_pin_index(__index) ( ( uint8_t )__index & 0xF )

#define hal_ll_gpio_port_get_port_index(__index) ( ( uint8_t )( __index & 0xF0 ) >> 4 )

#define GPIO_ALT_FUNC_MASK (0xFF00)

/* P/PM offsets, anchored at GPIO_PORTx_BASE (that port's P register addr). */
#define HAL_LL_GPIO_P_OFFSET       ( 0x00UL )
#define HAL_LL_GPIO_PM_OFFSET      ( 0x20UL )

/* PU/PIM/POM/PDIDIS offsets, anchored at GPIO_PORTx_CFG_BASE (PU register
 * addr, see hal_ll_gpio_port_cfg_base()). */
#define HAL_LL_GPIO_PU_OFFSET      ( 0x000UL )
#define HAL_LL_GPIO_PIM_OFFSET     ( 0x010UL )
#define HAL_LL_GPIO_POM_OFFSET     ( 0x020UL )
#define HAL_LL_GPIO_PDIDIS_OFFSET  ( 0x280UL )

/* PMCAxx only exists for ports 1, 2 and 4 (R01UH1082 4.3.7); every other
 * port has no analog/digital mux, so GPIO_CFG_ANALOG_INPUT is simply not
 * valid there and this returns 0. */
#define HAL_LL_PMCA1_BASE ( 0xF0061UL )
#define HAL_LL_PMCA2_BASE ( 0xF0062UL )
#define HAL_LL_PMCA4_BASE ( 0xF0064UL )

static inline hal_ll_base_addr_t hal_ll_gpio_analog_ctrl_base( uint8_t port_index ) {
    switch ( port_index ) {
        case 1:  return HAL_LL_PMCA1_BASE;
        case 2:  return HAL_LL_PMCA2_BASE;
        case 4:  return HAL_LL_PMCA4_BASE;
        default: return 0;
    }
}

/* Peripheral I/O redirection registers (PIOR0..PIOR13), R01UH1082 4.3.10. */
#define HAL_LL_PIOR_BASE ( 0xF04E0UL )

static inline void hal_ll_pior_set_field( uint8_t pior_index, uint8_t shift, uint8_t width, uint8_t value ) {
    hal_ll_base_addr_t reg  = HAL_LL_PIOR_BASE + pior_index;
    uint8_t            mask = ( uint8_t ) ( ( ( 1U << width ) - 1U ) << shift );

    clear_reg_bits( ( uint8_t * ) reg, mask );
    set_reg_bits( ( uint8_t * ) reg, ( uint8_t ) ( ( value << shift ) & mask ) );
}

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
    #ifdef GPIO_PORT_5
    GPIO_PORT5_BASE,
    #else
    0,
    #endif
    #ifdef GPIO_PORT_6
    GPIO_PORT6_BASE,
    #else
    0,
    #endif
    #ifdef GPIO_PORT_7
    GPIO_PORT7_BASE,
    #else
    0,
    #endif
    #ifdef GPIO_PORT_8
    GPIO_PORT8_BASE,
    #else
    0,
    #endif
    #ifdef GPIO_PORT_9
    GPIO_PORT9_BASE,
    #else
    0,
    #endif
    #ifdef GPIO_PORT_10
    GPIO_PORT10_BASE,
    #else
    0,
    #endif
    #ifdef GPIO_PORT_11
    GPIO_PORT11_BASE,
    #else
    0,
    #endif
    #ifdef GPIO_PORT_12
    GPIO_PORT12_BASE,
    #else
    0,
    #endif
    #ifdef GPIO_PORT_13
    GPIO_PORT13_BASE,
    #else
    0,
    #endif
    #ifdef GPIO_PORT_14
    GPIO_PORT14_BASE,
    #else
    0,
    #endif
};

/*!< @brief GPIO config-bank array (PU/PIM/POM/PDIDIS anchor per port) */
static const uint32_t hal_ll_gpio_port_cfg_base_arr[] =
{
    #ifdef GPIO_PORT_0
    GPIO_PORT0_CFG_BASE,
    #else
    0,
    #endif
    #ifdef GPIO_PORT_1
    GPIO_PORT1_CFG_BASE,
    #else
    0,
    #endif
    #ifdef GPIO_PORT_2
    GPIO_PORT2_CFG_BASE,
    #else
    0,
    #endif
    #ifdef GPIO_PORT_3
    GPIO_PORT3_CFG_BASE,
    #else
    0,
    #endif
    #ifdef GPIO_PORT_4
    GPIO_PORT4_CFG_BASE,
    #else
    0,
    #endif
    #ifdef GPIO_PORT_5
    GPIO_PORT5_CFG_BASE,
    #else
    0,
    #endif
    #ifdef GPIO_PORT_6
    GPIO_PORT6_CFG_BASE,
    #else
    0,
    #endif
    #ifdef GPIO_PORT_7
    GPIO_PORT7_CFG_BASE,
    #else
    0,
    #endif
    #ifdef GPIO_PORT_8
    GPIO_PORT8_CFG_BASE,
    #else
    0,
    #endif
    #ifdef GPIO_PORT_9
    GPIO_PORT9_CFG_BASE,
    #else
    0,
    #endif
    #ifdef GPIO_PORT_10
    GPIO_PORT10_CFG_BASE,
    #else
    0,
    #endif
    #ifdef GPIO_PORT_11
    GPIO_PORT11_CFG_BASE,
    #else
    0,
    #endif
    #ifdef GPIO_PORT_12
    GPIO_PORT12_CFG_BASE,
    #else
    0,
    #endif
    #ifdef GPIO_PORT_13
    GPIO_PORT13_CFG_BASE,
    #else
    0,
    #endif
    #ifdef GPIO_PORT_14
    GPIO_PORT14_CFG_BASE,
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

/**
  * @brief  Fetch this port's config-bank base address
  *         (anchors PU/PIM/POM/PDIDIS, see the HAL_LL_GPIO_P*_OFFSET macros).
  * @param  hal_ll_port_name_t - port
  * @return uint32_t - config-bank base address of the port
  */
static uint32_t hal_ll_gpio_port_cfg_base( hal_ll_port_name_t name );

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

static uint32_t hal_ll_gpio_port_cfg_base( hal_ll_port_name_t name ) {
    return hal_ll_gpio_port_cfg_base_arr[ name ];
}

static void hal_ll_gpio_config( uint32_t *port, uint16_t pin_mask, uint32_t config ) {
    hal_ll_base_addr_t port_addr = ( hal_ll_base_addr_t ) port;
    uint8_t mask = ( uint8_t ) pin_mask;
    uint8_t port_index;
    hal_ll_base_addr_t analog_reg;
    hal_ll_base_addr_t cfg_addr;

    if ( NULL == port ) {
        return;
    }

    port_index = hal_ll_gpio_get_port_number( ( uint32_t ) port_addr );
    analog_reg = hal_ll_gpio_analog_ctrl_base( port_index );

    cfg_addr = ( PORT_COUNT > port_index ) ? hal_ll_gpio_port_cfg_base_arr[ port_index ] : 0;

    switch ( config ) {
        case GPIO_CFG_DIGITAL_INPUT:
            if ( 0 != analog_reg ) {
                clear_reg_bits( ( uint8_t * ) analog_reg, mask );
            }
            set_reg_bits( ( uint8_t * ) ( port_addr + HAL_LL_GPIO_PM_OFFSET ), mask );
            if ( 0 != cfg_addr ) {
                clear_reg_bits( ( uint8_t * ) ( cfg_addr + HAL_LL_GPIO_PDIDIS_OFFSET ), mask );
            }
            break;

        case GPIO_CFG_DIGITAL_OUTPUT:
            if ( 0 != analog_reg ) {
                clear_reg_bits( ( uint8_t * ) analog_reg, mask );
            }
            clear_reg_bits( ( uint8_t * ) ( port_addr + HAL_LL_GPIO_PM_OFFSET ), mask );
            if ( 0 != cfg_addr ) {
                clear_reg_bits( ( uint8_t * ) ( cfg_addr + HAL_LL_GPIO_PDIDIS_OFFSET ), mask );
            }
            break;

        case GPIO_CFG_ANALOG_INPUT:
            /* Ports without a PMCAxx register (i.e. not port 1, 2, or 4) have no
             * analog mux at all -- GPIO_CFG_ANALOG_INPUT is not valid there. */
            if ( 0 != analog_reg ) {
                set_reg_bits( ( uint8_t * ) analog_reg, mask );
            }
            set_reg_bits( ( uint8_t * ) ( port_addr + HAL_LL_GPIO_PM_OFFSET ), mask );
            if ( 0 != cfg_addr ) {
                clear_reg_bits( ( uint8_t * ) ( cfg_addr + HAL_LL_GPIO_PDIDIS_OFFSET ), mask );
            }
            break;

        default:
            break;
    }
}

static void hal_ll_gpio_config_pin_alternate_enable( uint32_t module_pin, uint32_t module_config, bool state ) {
    uint8_t pin_index;
    hal_ll_pin_name_t pin_name;
    hal_ll_port_name_t port_name;
    hal_ll_base_addr_t port_addr;

    pin_name = ( hal_ll_pin_name_t ) module_pin;
    pin_index = hal_ll_gpio_pin_index( pin_name );
    port_name = hal_ll_gpio_port_index( pin_name );

    port_addr = ( hal_ll_base_addr_t ) hal_ll_gpio_port_base( port_name );

    if ( false == state ) {
        return;
    }

    hal_ll_gpio_config( ( uint32_t * ) port_addr, ( uint16_t ) ( 1 << pin_index ), module_config );
}

// ------------------------------------------------------------------------- END
