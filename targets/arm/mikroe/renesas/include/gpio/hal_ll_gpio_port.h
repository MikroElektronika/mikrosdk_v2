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
#define GPIO_AF_OFFSET 8
#define VALUE(pin, func) (pin | (func << GPIO_AF_OFFSET))

/**
 *  GPIO module struct defining pins and proprietary functions
 */
typedef struct
{
    union {
        uint32_t pcntr1;
        struct {
            uint16_t podr;
            uint16_t pdr;
        };
    };
    union {
        uint32_t pcntr2;
        struct {
            uint16_t eidr; // PORT1-4 only
            uint16_t pidr;
        };
    };
    union {
        uint32_t pcntr3;
        struct {
            uint16_t porr;
            uint16_t posr;
        };
    };
    union {
        uint32_t pcntr4; // PORT1-4 only
        struct {
            uint16_t eorr; // PORT1-4 only
            uint16_t eosr; // PORT1-4 only
        };
    };
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
 * @brief Pin Function Select Register (PmnPFS) structure.
 *
 * Represents the configuration settings for a single pin using the
 * Port Function Select (PFS) register. This includes direction, mode,
 * drive strength, and peripheral selection.
 */
typedef struct
{
    union
    {
        volatile uint32_t pmnpfs;

        struct
        {
            volatile uint32_t podr  : 1; /**< Output data. */
            volatile uint32_t pidr  : 1; /**< Input data. */
            volatile uint32_t pdr   : 1; /**< Direction (0: input, 1: output). */
            uint32_t                : 1; /**< Reserved. */
            volatile uint32_t pcr   : 1; /**< Pull-up control (0: disabled, 1: enabled). */
            uint32_t                : 1; /**< Reserved. */
            volatile uint32_t ncodr : 1; /**< N-ch open-drain control (0: CMOS, 1: NMOS open-drain). */
            uint32_t                : 3; /**< Reserved. */
            volatile uint32_t dscr  : 2; /**< Drive capacity control. */
            volatile uint32_t eofr  : 2; /**< Event on falling/rising edge. */
            volatile uint32_t isel  : 1; /**< IRQ input select (0: disabled, 1: enabled). */
            volatile uint32_t asel  : 1; /**< Analog select (0: digital, 1: analog). */
            volatile uint32_t pmr   : 1; /**< Peripheral mode select (0: GPIO, 1: peripheral). */
            uint32_t                : 7; /**< Reserved. */
            volatile uint32_t psel  : 5; /**< Peripheral function select. */
            uint32_t                : 3; /**< Reserved. */
        } pmnpfs_b;
    };
} hal_ll_gpio_pfs_pin_t;

/**
 * @brief Port-level PFS register map.
 *
 * Represents the PFS register set for all 16 pins of a given port.
 */
typedef struct
{
    volatile hal_ll_gpio_pfs_pin_t pin[16]; /**< PFS configuration for pins 0 to 15. */
} hal_ll_gpio_pfs_port_t;

/**
 * @brief Entire PFS register map for all ports.
 *
 * Represents all available ports in the microcontroller that support
 * Port Function Select configuration.
 */
typedef struct
{
    volatile hal_ll_gpio_pfs_port_t port[10]; /**< Port array supporting PFS. */
} hal_ll_gpio_pfs_t;

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
uint16_t hal_ll_gpio_pin_mask( hal_ll_pin_name_t name );

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
void hal_ll_gpio_analog_input( uint32_t *port, uint16_t pin_mask );

/**
  * @brief  Set pin as digital input
  * @param  port - port base address acquired from hal_gpio_ll_port_base
  * @param  pin_mask - pin mask acquired from hal_gpio_ll_pin_mask
  * @return none
  */
void hal_ll_gpio_digital_input( uint32_t *port, uint16_t pin_mask );

/**
  * @brief  Set pin as digital output
  * @param  port - port base address acquired from hal_gpio_ll_port_base
  * @param  pin_mask - pin mask acquired from hal_gpio_ll_pin_mask
  * @return none
  */
void hal_ll_gpio_digital_output( uint32_t *port, uint16_t pin_mask );

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
