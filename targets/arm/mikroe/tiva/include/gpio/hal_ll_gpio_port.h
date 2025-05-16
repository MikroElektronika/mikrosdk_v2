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

/**
 * @brief Helper macros for GPIO HAL operations.
 *
 * @details
 * These macros assist in GPIO module structure management,
 * alternate function offset calculation, and pin/function value encoding.
 */
#define GPIO_MODULE_STRUCT_END (-1)
#define GPIO_AF_OFFSET 8
#define VALUE(pin, func) (pin | (func << GPIO_AF_OFFSET))

/**
 * @brief Structure representing a GPIO module configuration.
 *
 * @details
 * This structure holds arrays of pin base addresses and their corresponding configurations.
 * It is used to initialize or configure multiple GPIO pins within a module.
 */
typedef struct
{
    hal_ll_base_addr_t pins[13];   /**< Array of pin base addresses */
    uint32_t configs[13];          /**< Array of pin configuration values */
} module_struct;

/**
 * @brief Structure representing the base registers of a GPIO port.
 *
 * @details
 * This structure contains pointers to all relevant GPIO registers for a single port,
 * including data, direction, interrupt, alternate function, drive strength, and other control registers.
 * It is used for low-level GPIO port manipulation.
 */
typedef struct
{
    hal_ll_base_addr_t gpiodata;       /**< GPIO data register */
    hal_ll_base_addr_t gpiodir;        /**< GPIO direction register */
    hal_ll_base_addr_t gpiois;         /**< GPIO interrupt sense register */
    hal_ll_base_addr_t gpioibe;        /**< GPIO interrupt both edges register */
    hal_ll_base_addr_t gpioiev;        /**< GPIO interrupt event register */
    hal_ll_base_addr_t gpioim;         /**< GPIO interrupt mask register */
    hal_ll_base_addr_t gpioris;        /**< GPIO raw interrupt status register */
    hal_ll_base_addr_t gpiomis;        /**< GPIO masked interrupt status register */
    hal_ll_base_addr_t gpioicr;        /**< GPIO interrupt clear register */
    hal_ll_base_addr_t gpioafsel;      /**< GPIO alternate function select register */
    hal_ll_base_addr_t gpio_reserved[55]; /**< Reserved space for alignment */
    hal_ll_base_addr_t gpiodr2r;       /**< GPIO 2-mA drive select register */
    hal_ll_base_addr_t gpiodr4r;       /**< GPIO 4-mA drive select register */
    hal_ll_base_addr_t gpiodr8r;       /**< GPIO 8-mA drive select register */
    hal_ll_base_addr_t gpioodr;        /**< GPIO open drain select register */
    hal_ll_base_addr_t gpiopur;        /**< GPIO pull-up select register */
    hal_ll_base_addr_t gpiopdr;        /**< GPIO pull-down select register */
    hal_ll_base_addr_t gpioslr;        /**< GPIO slew rate control select register */
    hal_ll_base_addr_t gpioden;        /**< GPIO digital enable register */
    hal_ll_base_addr_t gpiolock;       /**< GPIO lock register */
    hal_ll_base_addr_t gpiocr;         /**< GPIO commit register */
    hal_ll_base_addr_t gpioamsel;      /**< GPIO analog mode select register */
    hal_ll_base_addr_t gpiopctl;       /**< GPIO port control register */
    hal_ll_base_addr_t gpioadcctl;     /**< GPIO ADC control register */
    hal_ll_base_addr_t gpiodmactl;     /**< GPIO DMA control register */
    hal_ll_base_addr_t gpiosi;         /**< GPIO select interrupt register */
    hal_ll_base_addr_t gpiodr12r;      /**< GPIO 12-mA drive select register */
    hal_ll_base_addr_t gpiowakepen;    /**< GPIO wake pin enable register */
    hal_ll_base_addr_t gpiowakestat;   /**< GPIO wake status register */
    hal_ll_base_addr_t gpiopp;         /**< GPIO peripheral properties register */
    hal_ll_base_addr_t gpiopc;         /**< GPIO peripheral configuration register */
} hal_ll_gpio_base_handle_t;

/**
 * @brief Type definition for GPIO base handle.
 *
 * @details
 * This type represents a handle to a GPIO base, used for low-level GPIO operations.
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
    HAL_LL_GPIO_DIGITAL_INPUT = 0,   /**< Pin configured as digital input */
    HAL_LL_GPIO_DIGITAL_OUTPUT = 1   /**< Pin configured as digital output */
} hal_ll_gpio_direction_t;

/**
 * @brief Structure representing a GPIO pin or port.
 *
 * @details
 * This structure contains a base handle and a mask representing the pin or port.
 * It is used to identify and manipulate specific GPIO pins or ports.
 */
typedef struct hal_ll_gpio_t
{
    hal_ll_gpio_base_t base;      /**< Base handle for GPIO */
    hal_ll_gpio_mask_t mask;      /**< Mask identifying the pin(s) */
} hal_ll_gpio_t;

/**
 * @brief Type definition for GPIO pin.
 *
 * @details
 * Alias for hal_ll_gpio_t representing a GPIO pin.
 */
typedef struct hal_ll_gpio_t hal_ll_gpio_pin_t;

/**
 * @brief Type definition for GPIO port.
 *
 * @details
 * Alias for hal_ll_gpio_t representing a GPIO port.
 */
typedef struct hal_ll_gpio_t hal_ll_gpio_port_t;

/**
 * @brief Get the port index from a pin name.
 *
 * @details
 * Calculates the port index based on the given pin name.
 *
 * @param[in] name Pin name to extract the port index from.
 *
 * @return Port index as an unsigned 8-bit integer.
 *
 * @note
 * The port index corresponds to the position of the port in the GPIO port array.
 *
 * @pre
 * The pin name must be valid and correspond to a known port.
 *
 * @post
 * Returns the port index for the specified pin.
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
 * - Only supports pin names defined in the platform.
 *
 * @see hal_ll_gpio_pin_mask()
 * @see hal_ll_gpio_port_base()
 *
 * @link https://github.com/MikroElektronika/mikrosdk_v2/blob/master/targets/arm/mikroe/tiva/include/gpio/hal_ll_gpio_port.h#L206 Link to header @endlink.
 * @link https://github.com/MikroElektronika/mikrosdk_v2/blob/master/targets/arm/mikroe/tiva/src/gpio/implementation_1/hal_ll_gpio_port.c#L259 Link to source @endlink.
 */
uint8_t hal_ll_gpio_port_index( hal_ll_pin_name_t name );

/**
 * @brief Get the pin mask from a pin name.
 *
 * @details
 * Returns a bitmask representing the pin position within its port.
 *
 * @param[in] name Pin name to extract the mask from.
 *
 * @return Pin mask as an unsigned 8-bit integer.
 *
 * @note
 * The mask has a single bit set corresponding to the pin's position.
 *
 * @pre
 * The pin name must be valid.
 *
 * @post
 * Returns the mask for the specified pin.
 *
 * @warning
 * Invalid pin names may cause incorrect mask values.
 *
 * @par Example Usage
 * @code{.c}
 *     TODO: ADD EXAMPLE CODE FOR `uint8_t hal_ll_gpio_pin_mask(hal_ll_pin_name_t name)`
 * @endcode
 *
 * @par Limitations
 * - Only supports pin names defined in the platform.
 *
 * @see hal_ll_gpio_port_index()
 * @see hal_ll_gpio_port_base()
 *
 * @link https://github.com/MikroElektronika/mikrosdk_v2/blob/master/targets/arm/mikroe/tiva/include/gpio/hal_ll_gpio_port.h#L244 Link to header @endlink.
 * @link https://github.com/MikroElektronika/mikrosdk_v2/blob/master/targets/arm/mikroe/tiva/src/gpio/implementation_1/hal_ll_gpio_port.c#L263 Link to source @endlink.
 */
uint8_t hal_ll_gpio_pin_mask( hal_ll_pin_name_t name );

/**
 * @brief Get the base address of a GPIO port.
 *
 * @details
 * Returns the base address of the specified GPIO port.
 *
 * @param[in] name Port name to get the base address for.
 *
 * @return Base address of the GPIO port as a 32-bit unsigned integer.
 *
 * @note
 * The base address is used for direct register access.
 *
 * @pre
 * The port name must be valid.
 *
 * @post
 * Returns the base address of the specified port.
 *
 * @warning
 * Invalid port names may cause incorrect base addresses.
 *
 * @par Example Usage
 * @code{.c}
 *     TODO: ADD EXAMPLE CODE FOR `uint32_t hal_ll_gpio_port_base(hal_ll_port_name_t name)`
 * @endcode
 *
 * @par Limitations
 * - Only supports port names defined in the platform.
 *
 * @see hal_ll_gpio_port_index()
 * @see hal_ll_gpio_pin_mask()
 *
 * @link https://github.com/MikroElektronika/mikrosdk_v2/blob/master/targets/arm/mikroe/tiva/include/gpio/hal_ll_gpio_port.h#L282 Link to header @endlink.
 * @link https://github.com/MikroElektronika/mikrosdk_v2/blob/master/targets/arm/mikroe/tiva/src/gpio/implementation_1/hal_ll_gpio_port.c#L267 Link to source @endlink.
 */
uint32_t hal_ll_gpio_port_base( hal_ll_port_name_t name );

/**
 * @brief Configure GPIO pins as analog inputs.
 *
 * @details
 * Sets the specified pins on the given port to analog input mode.
 *
 * @param[in,out] port Pointer to the port base address.
 * @param[in] pin_mask Bitmask specifying which pins to configure.
 *
 * @return void
 *
 * @note
 * This function configures pins for analog input functionality,
 * disabling digital input/output features.
 *
 * @pre
 * The port pointer must be valid and point to a GPIO port.
 *
 * @post
 * The specified pins are configured as analog inputs.
 *
 * @warning
 * Using pins configured as analog inputs for digital I/O may cause undefined behavior.
 *
 * @par Example Usage
 * @code{.c}
 *     TODO: ADD EXAMPLE CODE FOR `void hal_ll_gpio_analog_input(uint32_t *port, uint8_t pin_mask)`
 * @endcode
 *
 * @par Limitations
 * - Only pins supporting analog input can be configured.
 *
 * @see hal_ll_gpio_digital_input()
 * @see hal_ll_gpio_digital_output()
 *
 * @link https://github.com/MikroElektronika/mikrosdk_v2/blob/master/targets/arm/mikroe/tiva/include/gpio/hal_ll_gpio_port.h#L322 Link to header @endlink.
 * @link https://github.com/MikroElektronika/mikrosdk_v2/blob/master/targets/arm/mikroe/tiva/src/gpio/implementation_1/hal_ll_gpio_port.c#L271 Link to source @endlink.
 */
void hal_ll_gpio_analog_input( uint32_t *port, uint8_t pin_mask );

/**
 * @brief Configure GPIO pins as digital inputs.
 *
 * @details
 * Sets the specified pins on the given port to digital input mode.
 *
 * @param[in,out] port Pointer to the port base address.
 * @param[in] pin_mask Bitmask specifying which pins to configure.
 *
 * @return void
 *
 * @note
 * This function disables output functionality and enables digital input on the pins.
 *
 * @pre
 * The port pointer must be valid and point to a GPIO port.
 *
 * @post
 * The specified pins are configured as digital inputs.
 *
 * @warning
 * Pins configured as digital inputs should not be driven externally as outputs.
 *
 * @par Example Usage
 * @code{.c}
 *     TODO: ADD EXAMPLE CODE FOR `void hal_ll_gpio_digital_input(uint32_t *port, uint8_t pin_mask)`
 * @endcode
 *
 * @par Limitations
 * - Only pins supporting digital input can be configured.
 *
 * @see hal_ll_gpio_analog_input()
 * @see hal_ll_gpio_digital_output()
 *
 * @link https://github.com/MikroElektronika/mikrosdk_v2/blob/master/targets/arm/mikroe/tiva/include/gpio/hal_ll_gpio_port.h#L361 Link to header @endlink.
 * @link https://github.com/MikroElektronika/mikrosdk_v2/blob/master/targets/arm/mikroe/tiva/src/gpio/implementation_1/hal_ll_gpio_port.c#L275 Link to source @endlink.
 */
void hal_ll_gpio_digital_input( uint32_t *port, uint8_t pin_mask );

/**
 * @brief Configure GPIO pins as digital outputs.
 *
 * @details
 * Sets the specified pins on the given port to digital output mode.
 *
 * @param[in,out] port Pointer to the port base address.
 * @param[in] pin_mask Bitmask specifying which pins to configure.
 *
 * @return void
 *
 * @note
 * This function enables output functionality on the pins.
 *
 * @pre
 * The port pointer must be valid and point to a GPIO port.
 *
 * @post
 * The specified pins are configured as digital outputs.
 *
 * @warning
 * Driving pins configured as outputs without proper load may damage hardware.
 *
 * @par Example Usage
 * @code{.c}
 *     TODO: ADD EXAMPLE CODE FOR `void hal_ll_gpio_digital_output(uint32_t *port, uint8_t pin_mask)`
 * @endcode
 *
 * @par Limitations
 * - Only pins supporting digital output can be configured.
 *
 * @see hal_ll_gpio_analog_input()
 * @see hal_ll_gpio_digital_input()
 *
 * @link https://github.com/MikroElektronika/mikrosdk_v2/blob/master/targets/arm/mikroe/tiva/include/gpio/hal_ll_gpio_port.h#L400 Link to header @endlink.
 * @link https://github.com/MikroElektronika/mikrosdk_v2/blob/master/targets/arm/mikroe/tiva/src/gpio/implementation_1/hal_ll_gpio_port.c#L279 Link to source @endlink.
 */
void hal_ll_gpio_digital_output( uint32_t *port, uint8_t pin_mask );

/**
 * @brief Initialize GPIO module structure with alternate function settings.
 *
 * @details
 * Iterates through the provided module structure and enables or disables
 * alternate function configurations for each pin based on the state parameter.
 *
 * @param[in] module Pointer to the module_struct containing pins and configurations.
 * @param[in] state Boolean state to enable (true) or disable (false) alternate functions.
 *
 * @return void
 *
 * @note
 * The module structure must be terminated with GPIO_MODULE_STRUCT_END in the pins array.
 *
 * @pre
 * The module pointer must be valid and properly initialized.
 *
 * @post
 * Alternate function settings are applied to all pins in the module structure.
 *
 * @warning
 * Incorrect configurations may lead to undefined pin behavior.
 *
 * @par Example Usage
 * @code{.c}
 *     TODO: ADD EXAMPLE CODE FOR `void hal_ll_gpio_module_struct_init(module_struct const *module, bool state)`
 * @endcode
 *
 * @par Limitations
 * - Only pins listed in the module structure are affected.
 *
 * @see module_struct
 * @see _hal_ll_gpio_config_pin_alternate_enable()
 *
 * @link https://github.com/MikroElektronika/mikrosdk_v2/blob/master/targets/arm/mikroe/tiva/include/gpio/hal_ll_gpio_port.h#L440 Link to header @endlink.
 * @link https://github.com/MikroElektronika/mikrosdk_v2/blob/master/targets/arm/mikroe/tiva/src/gpio/implementation_1/hal_ll_gpio_port.c#L283 Link to source @endlink.
 */
void hal_ll_gpio_module_struct_init( module_struct const *module, bool state );

#ifdef __cplusplus
}
#endif

#endif // _HAL_LL_GPIO_PORT_H_
// ------------------------------------------------------------------------- END
