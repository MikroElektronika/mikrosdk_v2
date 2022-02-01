/****************************************************************************
**
** Copyright (C) 2022 MikroElektronika d.o.o.
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
#define GPIO_AF_OFFSET 8
#define VALUE(pin, func) (pin | (func << GPIO_AF_OFFSET))

/**
 *  GPIO module struct defining pins and proprietary functions
 */
typedef struct
{
    hal_ll_base_addr_t pins[13];
    uint32_t configs[13];
} module_struct;

/**
 *  GPIO module registers access structure
 */
typedef struct
{
    hal_ll_base_addr_t gpiodata;
    hal_ll_base_addr_t gpiodir;
    hal_ll_base_addr_t gpiois;
    hal_ll_base_addr_t gpioibe;
    hal_ll_base_addr_t gpioiev;
    hal_ll_base_addr_t gpioim;
    hal_ll_base_addr_t gpioris;
    hal_ll_base_addr_t gpiomis;
    hal_ll_base_addr_t gpioicr;
    hal_ll_base_addr_t gpioafsel;
    hal_ll_base_addr_t gpio_reserved[55];
    hal_ll_base_addr_t gpiodr2r;
    hal_ll_base_addr_t gpiodr4r;
    hal_ll_base_addr_t gpiodr8r;
    hal_ll_base_addr_t gpioodr;
    hal_ll_base_addr_t gpiopur;
    hal_ll_base_addr_t gpiopdr;
    hal_ll_base_addr_t gpioslr;
    hal_ll_base_addr_t gpioden;
    hal_ll_base_addr_t gpiolock;
    hal_ll_base_addr_t gpiocr;
    hal_ll_base_addr_t gpioamsel;
    hal_ll_base_addr_t gpiopctl;
    hal_ll_base_addr_t gpioadcctl;
    hal_ll_base_addr_t gpiodmactl;
    hal_ll_base_addr_t gpiosi;
    hal_ll_base_addr_t gpiodr12r;
    hal_ll_base_addr_t gpiowakepen;
    hal_ll_base_addr_t gpiowakestat;
    hal_ll_base_addr_t gpiopp;
    hal_ll_base_addr_t gpiopc;
} hal_ll_gpio_base_handle_t;

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
  * @brief  Get pins port index within a list of available ports
  * @param  name - desired pin
  * @return uint8_t value from 0 to PORT_COUNT-1
  */
uint8_t hal_ll_gpio_port_index( hal_ll_pin_name_t name );

/**
  * @brief  Get pin mask of provided pin within proprietery port
  * @param  name - desired pin
  * @return uint32_t
  */
uint8_t hal_ll_gpio_pin_mask( hal_ll_pin_name_t name );

/**
  * @brief  Get base address of ports registers
  * @param  name - desired port
  * @return uint32_t address of first regsiter
  */
uint32_t hal_ll_gpio_port_base( hal_ll_port_name_t name );

/**
  * @brief  Set pin as analog input
  * @param  port - port base address acquired from hal_gpio_ll_port_base
  * @param  pin_mask - pin mask acquired from hal_gpio_ll_pin_mask
  * @return none
  */
void hal_ll_gpio_analog_input( uint32_t *port, uint8_t pin_mask );

/**
  * @brief  Set pin as digital input
  * @param  port - port base address acquired from hal_gpio_ll_port_base
  * @param  pin_mask - pin mask acquired from hal_gpio_ll_pin_mask
  * @return none
  */
void hal_ll_gpio_digital_input( uint32_t *port, uint8_t pin_mask );

/**
  * @brief  Set pin as digital output
  * @param  port - port base address acquired from hal_gpio_ll_port_base
  * @param  pin_mask - pin mask acquired from hal_gpio_ll_pin_mask
  * @return none
  */
void hal_ll_gpio_digital_output( uint32_t *port, uint8_t pin_mask );

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
