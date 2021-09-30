/****************************************************************************
**
** Copyright (C) 2021 MikroElektronika d.o.o.
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
    hal_ll_base_addr_t pdor;     /**< Port Data Output Register, offset: 0x0 */
    hal_ll_base_addr_t psor;     /**< Port Set Output Register, offset: 0x4 */
    hal_ll_base_addr_t pcor;     /**< Port Clear Output Register, offset: 0x8 */
    hal_ll_base_addr_t ptor;     /**< Port Toggle Output Register, offset: 0xC */
    hal_ll_base_addr_t pdir;     /**< Port Data Input Register, offset: 0x10 */
    hal_ll_base_addr_t pddr;     /**< Port Data Direction Register, offset: 0x14 */
} hal_ll_gpio_base_handle_t;

typedef struct
{
    hal_ll_base_addr_t pcr0;
    hal_ll_base_addr_t pcr1;
    hal_ll_base_addr_t pcr2;
    hal_ll_base_addr_t pcr3;
    hal_ll_base_addr_t pcr4;
    hal_ll_base_addr_t pcr5;
    hal_ll_base_addr_t pcr6;
    hal_ll_base_addr_t pcr7;
    hal_ll_base_addr_t pcr8;
    hal_ll_base_addr_t pcr9;
    hal_ll_base_addr_t pcr10;
    hal_ll_base_addr_t pcr11;
    hal_ll_base_addr_t pcr12;
    hal_ll_base_addr_t pcr13;
    hal_ll_base_addr_t pcr14;
    hal_ll_base_addr_t pcr15;
    hal_ll_base_addr_t pcr16;
    hal_ll_base_addr_t pcr17;
    hal_ll_base_addr_t pcr18;
    hal_ll_base_addr_t pcr19;
    hal_ll_base_addr_t pcr20;
    hal_ll_base_addr_t pcr21;
    hal_ll_base_addr_t pcr22;
    hal_ll_base_addr_t pcr23;
    hal_ll_base_addr_t pcr24;
    hal_ll_base_addr_t pcr25;
    hal_ll_base_addr_t pcr26;
    hal_ll_base_addr_t pcr27;
    hal_ll_base_addr_t pcr28;
    hal_ll_base_addr_t pcr29;
    hal_ll_base_addr_t pcr30;
    hal_ll_base_addr_t pcr31;
} hal_ll_gpio_pcr_base_handle_t;

typedef struct
{
    hal_ll_base_addr_t pcr_index_of[32];
} hal_ll_gpio_pcr_base_array_t;

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
uint32_t hal_ll_gpio_pin_mask( hal_ll_pin_name_t name );

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
void hal_ll_gpio_analog_input( uint32_t *port, uint32_t pin_mask );

/**
  * @brief  Set pin as digital input
  * @param  port - port base address acquired from hal_gpio_ll_port_base
  * @param  pin_mask - pin mask acquired from hal_gpio_ll_pin_mask
  * @return none
  */
void hal_ll_gpio_digital_input( uint32_t *port, uint32_t pin_mask );

/**
  * @brief  Set pin as digital output
  * @param  port - port base address acquired from hal_gpio_ll_port_base
  * @param  pin_mask - pin mask acquired from hal_gpio_ll_pin_mask
  * @return none
  */
void hal_ll_gpio_digital_output( uint32_t *port, uint32_t pin_mask );

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
