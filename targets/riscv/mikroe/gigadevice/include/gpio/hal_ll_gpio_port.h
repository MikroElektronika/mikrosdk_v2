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
/**
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

#define RESET_PINS_OFFSET 16

/**
 * @brief Helper macros for GPIO HAL.
 *
 * @details
 * These macros assist in GPIO operations such as marking the end of a module structure,
 * defining alternate function offset, and combining pin and function values.
 */
#define GPIO_MODULE_STRUCT_END -1
#define GPIO_AF_OFFSET 8
#define VALUE(pin, func) (pin | (func << GPIO_AF_OFFSET))

/**
 * @brief Structure representing a GPIO module configuration.
 *
 * @details
 * This structure holds arrays of pins and their corresponding configurations,
 * along with a GPIO remap value indicating alternate function remapping.
 */
typedef struct
{
  uint32_t pins[13];
  uint32_t configs[13];
  uint32_t gpio_remap;
} module_struct;

/**
 * @brief Structure representing the base registers of a GPIO port.
 *
 * @details
 * This structure maps the hardware registers of a GPIO port including control,
 * input status, output control, bit operate, bit clear, and lock registers.
 */
typedef struct
{
    uint32_t ctl0;    /**< Port control register 0. Address offset 0x00. */
    uint32_t ctl1;    /**< Port control register 1. Address offset 0x04. */
    uint32_t istat;   /**< Port input status register. Address offset 0x08. */
    uint32_t octl;    /**< Port output control register. Address offset 0x0C. */
    uint32_t bop;     /**< Port bit operate register. Address offset 0x10. */
    uint32_t bc;      /**< Port bit clear register. Address offset 0x14. */
    uint32_t lock;    /**< Port configuration lock register. Address offset 0x18. */
} hal_ll_gpio_base_handle_t;

/**
 * @brief Structure representing the alternate function I/O registers.
 *
 * @details
 * This structure maps the registers related to event control, alternate function
 * configuration, external interrupt source selection, and unused reserved space.
 */
typedef struct
{
    uint32_t ec;        /**< Event control register. Address offset 0x00. */
    uint32_t pcf0;      /**< Alternate function I/O port configuration register 0. Address offset 0x04. */
    uint32_t extiss0;   /**< External interrupt sources selection register 0. Address offset 0x08. */
    uint32_t extiss1;   /**< External interrupt sources selection register 1. Address offset 0x0C. */
    uint32_t extiss2;   /**< External interrupt sources selection register 2. Address offset 0x10. */
    uint32_t extiss3;   /**< External interrupt sources selection register 3. Address offset 0x14. */
    uint32_t __unused1; /**< Unused. Address offset 0x18. */
    uint32_t pcf1;      /**< Alternate function I/O port configuration register 1. Address offset 0x1C. */
} hal_ll_gpio_afio_handle_t;

/**
 * @brief Typedef for GPIO base handle.
 *
 * @details
 * This type represents a generic handle to a GPIO base, used for GPIO operations.
 */
typedef handle_t hal_ll_gpio_base_t;

/**
 * @brief Enumeration for GPIO pin direction.
 *
 * @details
 * Defines the possible directions for a GPIO pin: digital input or digital output.
 */
typedef enum
{
    HAL_LL_GPIO_DIGITAL_INPUT = 0,  /**< Pin configured as digital input. */
    HAL_LL_GPIO_DIGITAL_OUTPUT = 1  /**< Pin configured as digital output. */
} hal_ll_gpio_direction_t;

/**
 * @brief Structure representing a GPIO pin or port.
 *
 * @details
 * This structure contains a base handle and a mask representing the pin or port.
 */
typedef struct hal_ll_gpio_t
{
    hal_ll_gpio_base_t base;  /**< Base handle for GPIO port. */
    hal_ll_gpio_mask_t mask;  /**< Mask representing the pin(s). */
} hal_ll_gpio_t;

/**
 * @brief Typedef for GPIO pin.
 *
 * @details
 * Represents a GPIO pin using the hal_ll_gpio_t structure.
 */
typedef struct hal_ll_gpio_t hal_ll_gpio_pin_t;

/**
 * @brief Typedef for GPIO port.
 *
 * @details
 * Represents a GPIO port using the hal_ll_gpio_t structure.
 */
typedef struct hal_ll_gpio_t hal_ll_gpio_port_t;

/**
 * @brief Get the index of the GPIO port from a pin name.
 *
 * @details
 * Calculates the port index by dividing the pin name by the port size.
 *
 * @param[in] name Pin name to get the port index for.
 *
 * @return Port index as an unsigned 8-bit integer.
 *
 * @note
 * The port index corresponds to the position of the port in the internal port base array.
 *
 * @pre
 * The pin name must be valid and within the supported range.
 *
 * @post
 * Returns the port index corresponding to the pin.
 *
 * @warning
 * Passing an invalid pin name may result in undefined behavior.
 *
 * @par Example Usage
 * @code{.c}
 *     TODO: ADD EXAMPLE CODE FOR `uint8_t hal_ll_gpio_port_index(hal_ll_pin_name_t name)`
 * @endcode
 *
 * @par Limitations
 * - Only valid pin names supported.
 *
 * @see hal_ll_gpio_pin_mask()
 * @see hal_ll_gpio_port_base()
 *
 * @link https://github.com/MikroElektronika/mikrosdk_v2/blob/master/targets/riscv/mikroe/gigadevice/include/gpio/hal_ll_gpio_port.h#L202 Link to header @endlink.
 * @link https://github.com/MikroElektronika/mikrosdk_v2/blob/master/targets/riscv/mikroe/gigadevice/src/gpio/implementation_1/hal_ll_gpio_port.c#L124 Link to source @endlink.
 */
uint8_t hal_ll_gpio_port_index( hal_ll_pin_name_t name );

/**
 * @brief Get the pin mask for a given pin name.
 *
 * @details
 * Returns a bitmask with a single bit set corresponding to the pin index within the port.
 *
 * @param[in] name Pin name to get the mask for.
 *
 * @return 32-bit mask with the bit set for the pin.
 *
 * @note
 * The mask can be used to manipulate or configure the specific pin within a port.
 *
 * @pre
 * The pin name must be valid.
 *
 * @post
 * Returns the mask representing the pin position.
 *
 * @warning
 * Invalid pin names may cause incorrect mask values.
 *
 * @par Example Usage
 * @code{.c}
 *     TODO: ADD EXAMPLE CODE FOR `uint32_t hal_ll_gpio_pin_mask(hal_ll_pin_name_t name)`
 * @endcode
 *
 * @par Limitations
 * - Only supports pins within the defined port size.
 *
 * @see hal_ll_gpio_port_index()
 * @see hal_ll_gpio_port_base()
 *
 * @link https://github.com/MikroElektronika/mikrosdk_v2/blob/master/targets/riscv/mikroe/gigadevice/include/gpio/hal_ll_gpio_port.h#L240 Link to header @endlink.
 * @link https://github.com/MikroElektronika/mikrosdk_v2/blob/master/targets/riscv/mikroe/gigadevice/src/gpio/implementation_1/hal_ll_gpio_port.c#L128 Link to source @endlink.
 */
uint32_t hal_ll_gpio_pin_mask( hal_ll_pin_name_t name );

/**
 * @brief Get the base address of a GPIO port.
 *
 * @details
 * Returns the base memory address of the specified GPIO port.
 *
 * @param[in] name Port name to get the base address for.
 *
 * @return 32-bit base address of the GPIO port.
 *
 * @note
 * The base address is used for direct register access to the port.
 *
 * @pre
 * The port name must be valid and supported by the hardware.
 *
 * @post
 * Returns the base address of the port.
 *
 * @warning
 * Using an invalid port name may result in undefined behavior.
 *
 * @par Example Usage
 * @code{.c}
 *     TODO: ADD EXAMPLE CODE FOR `uint32_t hal_ll_gpio_port_base(hal_ll_port_name_t name)`
 * @endcode
 *
 * @par Limitations
 * - Only ports defined in the internal port base array are supported.
 *
 * @see hal_ll_gpio_port_index()
 * @see hal_ll_gpio_pin_mask()
 *
 * @link https://github.com/MikroElektronika/mikrosdk_v2/blob/master/targets/riscv/mikroe/gigadevice/include/gpio/hal_ll_gpio_port.h#L278 Link to header @endlink.
 * @link https://github.com/MikroElektronika/mikrosdk_v2/blob/master/targets/riscv/mikroe/gigadevice/src/gpio/implementation_1/hal_ll_gpio_port.c#L132 Link to source @endlink.
 */
uint32_t hal_ll_gpio_port_base( hal_ll_port_name_t name );

/**
 * @brief Configure specified pins on a port as analog inputs.
 *
 * @details
 * Sets the given pins on the specified port to analog input mode by configuring
 * the port registers accordingly.
 *
 * @param[in,out] port Pointer to the GPIO port base address.
 * @param[in] pin_mask Bitmask representing the pins to configure as analog input.
 *
 * @return void
 *
 * @note
 * This function directly modifies the port control registers to set pins to analog mode.
 *
 * @pre
 * The port pointer must be valid and point to a GPIO port.
 * The pin_mask must specify valid pins within the port.
 *
 * @post
 * The specified pins are configured as analog inputs.
 *
 * @warning
 * Configuring pins incorrectly may affect other functionalities on the port.
 *
 * @par Example Usage
 * @code{.c}
 *     TODO: ADD EXAMPLE CODE FOR `void hal_ll_gpio_analog_input(uint32_t *port, uint16_t pin_mask)`
 * @endcode
 *
 * @par Limitations
 * - Only pins supported by the hardware can be configured.
 *
 * @see hal_ll_gpio_digital_input()
 * @see hal_ll_gpio_digital_output()
 *
 * @link https://github.com/MikroElektronika/mikrosdk_v2/blob/master/targets/riscv/mikroe/gigadevice/include/gpio/hal_ll_gpio_port.h#L319 Link to header @endlink.
 * @link https://github.com/MikroElektronika/mikrosdk_v2/blob/master/targets/riscv/mikroe/gigadevice/src/gpio/implementation_1/hal_ll_gpio_port.c#L136 Link to source @endlink.
 */
void hal_ll_gpio_analog_input( uint32_t *port, uint16_t pin_mask );

/**
 * @brief Configure specified pins on a port as digital inputs.
 *
 * @details
 * Sets the given pins on the specified port to digital input mode by configuring
 * the port registers accordingly.
 *
 * @param[in,out] port Pointer to the GPIO port base address.
 * @param[in] pin_mask Bitmask representing the pins to configure as digital input.
 *
 * @return void
 *
 * @note
 * This function directly modifies the port control registers to set pins to digital input mode.
 *
 * @pre
 * The port pointer must be valid and point to a GPIO port.
 * The pin_mask must specify valid pins within the port.
 *
 * @post
 * The specified pins are configured as digital inputs.
 *
 * @warning
 * Configuring pins incorrectly may affect other functionalities on the port.
 *
 * @par Example Usage
 * @code{.c}
 *     TODO: ADD EXAMPLE CODE FOR `void hal_ll_gpio_digital_input(uint32_t *port, uint16_t pin_mask)`
 * @endcode
 *
 * @par Limitations
 * - Only pins supported by the hardware can be configured.
 *
 * @see hal_ll_gpio_analog_input()
 * @see hal_ll_gpio_digital_output()
 *
 * @link https://github.com/MikroElektronika/mikrosdk_v2/blob/master/targets/riscv/mikroe/gigadevice/include/gpio/hal_ll_gpio_port.h#L360 Link to header @endlink.
 * @link https://github.com/MikroElektronika/mikrosdk_v2/blob/master/targets/riscv/mikroe/gigadevice/src/gpio/implementation_1/hal_ll_gpio_port.c#L140 Link to source @endlink.
 */
void hal_ll_gpio_digital_input( uint32_t *port, uint16_t pin_mask );

/**
 * @brief Configure specified pins on a port as digital outputs.
 *
 * @details
 * Sets the given pins on the specified port to digital output mode by configuring
 * the port registers accordingly.
 *
 * @param[in,out] port Pointer to the GPIO port base address.
 * @param[in] pin_mask Bitmask representing the pins to configure as digital output.
 *
 * @return void
 *
 * @note
 * This function directly modifies the port control registers to set pins to digital output mode.
 *
 * @pre
 * The port pointer must be valid and point to a GPIO port.
 * The pin_mask must specify valid pins within the port.
 *
 * @post
 * The specified pins are configured as digital outputs.
 *
 * @warning
 * Configuring pins incorrectly may affect other functionalities on the port.
 *
 * @par Example Usage
 * @code{.c}
 *     TODO: ADD EXAMPLE CODE FOR `void hal_ll_gpio_digital_output(uint32_t *port, uint16_t pin_mask)`
 * @endcode
 *
 * @par Limitations
 * - Only pins supported by the hardware can be configured.
 *
 * @see hal_ll_gpio_analog_input()
 * @see hal_ll_gpio_digital_input()
 *
 * @link https://github.com/MikroElektronika/mikrosdk_v2/blob/master/targets/riscv/mikroe/gigadevice/include/gpio/hal_ll_gpio_port.h#L401 Link to header @endlink.
 * @link https://github.com/MikroElektronika/mikrosdk_v2/blob/master/targets/riscv/mikroe/gigadevice/src/gpio/implementation_1/hal_ll_gpio_port.c#L144 Link to source @endlink.
 */
void hal_ll_gpio_digital_output( uint32_t *port, uint16_t pin_mask );

/**
 * @brief Initialize GPIO module structure and configure alternate functions.
 *
 * @details
 * This function initializes the GPIO module structure by enabling or disabling
 * the alternate function clock and configuring the alternate function pins
 * according to the provided module structure.
 *
 * @param[in] module Pointer to the module_struct containing pins, configs, and remap info.
 * @param[in] state Boolean flag to enable (true) or disable (false) the alternate function clock.
 *
 * @return void
 *
 * @note
 * This function assumes the module structure is properly populated with valid pins and configurations.
 *
 * @pre
 * The module pointer must be valid and point to a properly initialized module_struct.
 *
 * @post
 * The alternate function clock is enabled or disabled, and pins are configured accordingly.
 *
 * @warning
 * Improper configuration may lead to incorrect pin behavior or conflicts.
 *
 * @par Example Usage
 * @code{.c}
 *     TODO: ADD EXAMPLE CODE FOR `void hal_ll_gpio_module_struct_init(module_struct const *module, bool state)`
 * @endcode
 *
 * @par Limitations
 * - Only pins and configurations supported by the hardware are valid.
 *
 * @see module_struct
 *
 * @link https://github.com/MikroElektronika/mikrosdk_v2/blob/master/targets/riscv/mikroe/gigadevice/include/gpio/hal_ll_gpio_port.h#L441 Link to header @endlink.
 * @link https://github.com/MikroElektronika/mikrosdk_v2/blob/master/targets/riscv/mikroe/gigadevice/src/gpio/implementation_1/hal_ll_gpio_port.c#L148 Link to source @endlink.
 */
void hal_ll_gpio_module_struct_init( module_struct const *module, bool state );

#ifdef __cplusplus
}
#endif

#endif // _HAL_LL_GPIO_PORT_H_
// ------------------------------------------------------------------------- END
