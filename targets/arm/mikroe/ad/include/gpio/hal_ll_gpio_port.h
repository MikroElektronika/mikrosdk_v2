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
 * @file  hal_ll_gpio.h
 * @brief This file contains all the functions prototypes for the GPIO library.
 */

#ifndef _HAL_LL_GPIO_PORT_H_
#define _HAL_LL_GPIO_PORT_H_

#ifdef __cplusplus
extern "C"{
#endif

#include "hal_ll_target.h"
#include "hal_ll_gpio_constants.h"

/**
 *  Helper macros for GPIO HAL
 */
#define GPIO_MODULE_STRUCT_END (-1)
#define GPIO_PIN_NAME_MASK (0xFFUL)
#define GPIO_ALT_FUNC_MASK (0xFF00UL)
#define GPIO_AF_OFFSET 8
#define VALUE(pin, func) (pin | (func << 8))

/**
 *  Config macros for GPIO HAL
 */
#define GPIO_CFG_OUT                        (0x01)   // Control Register (direction) flag
#define GPIO_CFG_OD                         (0x02)   // Open Drain flag
#define GPIO_CFG_PULL_UP                    (0x04)   // Pull-up flag
#define GPIO_CFG_PULL_DOWN                  (0x08)   // Pull-down flag
#define GPIO_CFG_IE                         (0x10)   // Input Enable flag

/**
 *  Port 4 has no dedicated set/clear register bank like the other ports;
 *  MCR_GPIO4_CTRL instead packs 4 control bits (do, oe, pe, in) per pin
 *  into a single register.
 */
#define GPIO4_CTRL_PIN_FIELD_WIDTH 4U
#define GPIO4_CTRL_DO_OFFSET       0U
#define GPIO4_CTRL_OE_OFFSET       1U
#define GPIO4_CTRL_PE_OFFSET       2U
#define GPIO4_CTRL_IN_OFFSET       3U
#define GPIO4_CTRL_PIN_COUNT       2U

/**
 *  GPIO module struct defining pins and proprietary functions
 */
typedef struct
{
    uint32_t en0;
    uint32_t en0_set;
    uint32_t en0_clr;
    uint32_t outen;
    uint32_t outen_set;
    uint32_t outen_clr;
    uint32_t out;
    uint32_t out_set;
    uint32_t out_clr;
    uint32_t in;
    uint32_t intmode;
    uint32_t intpol;
    uint32_t inen;
    uint32_t inten;
    uint32_t inten_set;
    uint32_t inten_clr;
    uint32_t intfl;
    uint32_t _reserved0;
    uint32_t intfl_clr;
    uint32_t wken;
    uint32_t wken_set;
    uint32_t wken_clr;
    uint32_t _reserved1;
    uint32_t dualedge;
    uint32_t padctrl0;
    uint32_t padctrl1;
    uint32_t en1;
    uint32_t en1_set;
    uint32_t en1_clr;
    uint32_t en2;
    uint32_t en2_set;
    uint32_t en2_clr;
    uint32_t _reserved2[10];
    uint32_t hysen;
    uint32_t srsel;
    uint32_t ds0;
    uint32_t ds1;
    uint32_t ps;
    uint32_t _reserved3;
    uint32_t vssel;
} hal_ll_gpio_base_handle_t;

/**
 *  GPIO module struct defining pins and proprietary functions
 */
typedef struct
{
    uint32_t pins[13];
    uint32_t configs[13];
    uint32_t gpio_remap;
} module_struct;

/**
 *  Handle and mask types.
 */
typedef handle_t hal_ll_gpio_base_t;

/**
 *  Enum used for pin direction selection.
 */
typedef enum
{
    HAL_LL_GPIO_DIGITAL_INPUT = 0,
    HAL_LL_GPIO_DIGITAL_OUTPUT = 1
} hal_ll_gpio_direction_t;

/**
 *  Enum used for pin direction selection.
 */
typedef struct hal_ll_gpio_t
{
    hal_ll_gpio_base_t base;
    hal_ll_gpio_mask_t mask;
};

/**
 *  Pin and port data types.
 */
typedef struct hal_ll_gpio_t hal_ll_gpio_pin_t;
typedef struct hal_ll_gpio_t hal_ll_gpio_port_t;

/**
 *  Helpers for addressing bits inside Port 4's packed MCR_GPIO4_CTRL register.
 */
static inline uint8_t hal_ll_gpio_port4_pin_index( uint16_t pin_mask ) {
    return ( uint8_t ) __builtin_ctz( pin_mask );
}

static inline uint8_t hal_ll_gpio_port4_read_bit( hal_ll_gpio_base_t base, uint8_t pin_index, uint8_t bit_offset ) {
    volatile uint32_t *ctrl = ( volatile uint32_t * ) base;
    uint32_t reg_bit = 1UL << ( pin_index * GPIO4_CTRL_PIN_FIELD_WIDTH + bit_offset );
    return ( *ctrl & reg_bit ) ? 1 : 0;
}

static inline void hal_ll_gpio_port4_write_bit( hal_ll_gpio_base_t base, uint8_t pin_index, uint8_t bit_offset, bool state ) {
    volatile uint32_t *ctrl = ( volatile uint32_t * ) base;
    uint32_t reg_bit = 1UL << ( pin_index * GPIO4_CTRL_PIN_FIELD_WIDTH + bit_offset );
    if ( state ) {
        *ctrl |= reg_bit;
    } else {
        *ctrl &= ~reg_bit;
    }
}

/*!< @brief Read/write every pin covered by @p mask in one call - used for
 *          the port-wide functions, since Port 4's bits aren't laid out
 *          as one contiguous register field like the other ports. */
static inline hal_ll_port_size_t hal_ll_gpio_port4_read_port( hal_ll_gpio_base_t base, hal_ll_gpio_mask_t mask, uint8_t bit_offset ) {
    hal_ll_port_size_t value = 0;
    for ( uint8_t i = 0; i < GPIO4_CTRL_PIN_COUNT; i++ ) {
        if ( ( mask & ( 1UL << i ) ) && hal_ll_gpio_port4_read_bit( base, i, bit_offset ) ) {
            value |= ( 1UL << i );
        }
    }
    return value;
}

static inline void hal_ll_gpio_port4_write_port( hal_ll_gpio_base_t base, hal_ll_gpio_mask_t mask, uint8_t bit_offset, hal_ll_port_size_t value ) {
    for ( uint8_t i = 0; i < GPIO4_CTRL_PIN_COUNT; i++ ) {
        if ( mask & ( 1UL << i ) ) {
            hal_ll_gpio_port4_write_bit( base, i, bit_offset, ( value & ( 1UL << i ) ) ? true : false );
        }
    }
}

/**
  * @brief  Get pins port index within a list of available ports
  * @param  name - desired pin
  * @return uint8_t value from 0 to PORT_COUNT-1
  */
uint8_t hal_ll_gpio_port_index( hal_ll_pin_name_t name );

/**
  * @brief  Get pin mask of provided pin within proprietary port
  * @param  name - desired pin
  * @return uint32_t
  */
uint16_t hal_ll_gpio_pin_mask( hal_ll_pin_name_t name );

/**
  * @brief  Get base address of ports registers
  * @param  name - desired port
  * @return uint32_t address of first register
  */
uint32_t hal_ll_gpio_port_base( hal_ll_port_name_t name );

/**
  * @brief  Set pin as analog input
  * @param  port - port base address acquired from hal_gpio_ll_port_base
  * @param  pin_mask - pin mask acquired from hal_gpio_ll_pin_mask
  * @param  port_name - port name acquired from hal_gpio_ll_port_index
  * @return none
  */
void hal_ll_gpio_analog_input( uint32_t *port, uint16_t pin_mask, hal_ll_port_name_t port_name );

/**
  * @brief  Set pin as digital input
  * @param  port - port base address acquired from hal_gpio_ll_port_base
  * @param  pin_mask - pin mask acquired from hal_gpio_ll_pin_mask
  * @param  port_name - port name acquired from hal_gpio_ll_port_index
  * @return none
  */
void hal_ll_gpio_digital_input( uint32_t *port, uint16_t pin_mask, hal_ll_port_name_t port_name );

/**
  * @brief  Set pin as digital output
  * @param  port - port base address acquired from hal_gpio_ll_port_base
  * @param  pin_mask - pin mask acquired from hal_gpio_ll_pin_mask
  * @param  port_name - port name acquired from hal_gpio_ll_port_index
  * @return none
  */
void hal_ll_gpio_digital_output( uint32_t *port, uint16_t pin_mask, hal_ll_port_name_t port_name );

/**
  * @brief  Initialize structure of pins associated to specific peripheral
  * @param  module - desired module pins structure
  * @return none
  */
void hal_ll_gpio_module_struct_init( module_struct const *module, bool state );

#ifdef __cplusplus
}
#endif

#endif // _HAL_LL_GPIO_PORT_H_
// ------------------------------------------------------------------------- END
