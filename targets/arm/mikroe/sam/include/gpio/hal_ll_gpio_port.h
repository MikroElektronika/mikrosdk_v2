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
#include "hal_ll_gpio_struct_type.h"

#define RESET_PINS_OFFSET 32

/**
 * @brief Helper macros for GPIO HAL.
 *
 * @details
 * Defines utility macros used internally by the GPIO HAL for managing GPIO modules.
 */
#define GPIO_MODULE_STRUCT_END -1

/**
 * @brief Structure representing a GPIO module configuration.
 *
 * @details
 * This structure holds arrays for pins and their corresponding configurations
 * for a GPIO module. It is used to initialize or configure multiple pins at once.
 */
typedef struct
{
    uint32_t pins[13];   /**< Array of pin identifiers for the module */
    uint8_t configs[13]; /**< Array of configuration values corresponding to each pin */
} module_struct;

/**
 * @brief Handle and mask types for GPIO operations.
 *
 * @details
 * Defines the base handle type used to represent GPIO ports and pins.
 */
typedef handle_t hal_ll_gpio_base_t;

/**
 * @brief Enumeration for GPIO pin direction.
 *
 * @details
 * Specifies the direction mode of a GPIO pin, either digital input or digital output.
 */
typedef enum
{
    HAL_LL_GPIO_DIGITAL_INPUT = 0,  /**< Pin configured as digital input */
    HAL_LL_GPIO_DIGITAL_OUTPUT = 1  /**< Pin configured as digital output */
} hal_ll_gpio_direction_t;

/**
 * @brief Structure representing a GPIO pin or port.
 *
 * @details
 * This structure encapsulates a GPIO base handle and a mask representing
 * the specific pin(s) within the port.
 */
typedef struct hal_ll_gpio_t
{
    hal_ll_gpio_base_t base;   /**< Base handle for the GPIO port */
    hal_ll_gpio_mask_t mask;   /**< Mask representing the pin(s) */
};

/**
 * @brief Typedef for GPIO pin type.
 *
 * @details
 * Alias for the hal_ll_gpio_t structure representing a GPIO pin.
 */
typedef struct hal_ll_gpio_t hal_ll_gpio_pin_t;

/**
 * @brief Typedef for GPIO port type.
 *
 * @details
 * Alias for the hal_ll_gpio_t structure representing a GPIO port.
 */
typedef struct hal_ll_gpio_t hal_ll_gpio_port_t;

/**
 * @brief Get the index of the GPIO port from a pin name.
 *
 * @details
 * Calculates the port index by dividing the pin name by the port size.
 *
 * @param[in] name Pin name to extract the port index from.
 *
 * @return Port index as an unsigned 8-bit integer.
 *
 * @note
 * The port index corresponds to the position of the port in the internal port array.
 *
 * @pre
 * The pin name must be valid and correspond to a defined port.
 *
 * @post
 * Returns the port index for the given pin name.
 *
 * @warning
 * Passing an invalid pin name may result in undefined behavior.
 *
 * @par Example Usage
 * @code{.c}
 *    // Get port. *    hal_ll_gpio_port_index( GPIO_PB2 );
 * @endcode
 *
 * @par Limitations
 * - Only valid for pins defined within the supported ports.
 *
 * @see hal_ll_gpio_pin_index()
 * @see hal_ll_gpio_pin_mask()
 *
 * @link https://github.com/MikroElektronika/mikrosdk_v2/blob/master/targets/arm/mikroe/sam/include/gpio/hal_ll_gpio_port.h#L163 Link to header @endlink.
 * @link https://github.com/MikroElektronika/mikrosdk_v2/blob/master/targets/arm/mikroe/sam/src/gpio/implementations/implementation_1/hal_ll_gpio_port.c#L154 Link to source @endlink.
 */
uint8_t hal_ll_gpio_port_index( hal_ll_pin_name_t name );

/**
 * @brief Get the mask for a specific GPIO pin.
 *
 * @details
 * Returns a bitmask with a single bit set corresponding to the pin index within its port.
 *
 * @param[in] name Pin name to get the mask for.
 *
 * @return Bitmask representing the pin position within the port.
 *
 * @note
 * The mask can be used to manipulate or configure the specific pin within the port registers.
 *
 * @pre
 * The pin name must be valid and correspond to a defined pin within a port.
 *
 * @post
 * Returns the bitmask for the specified pin.
 *
 * @warning
 * Using an invalid pin name may cause incorrect mask calculation.
 *
 * @par Example Usage
 * @code{.c}
 *    // Get pin mask. *    hal_ll_gpio_pin_mask( GPIO_PB2 );
 * @endcode
 *
 * @par Limitations
 * - Only valid for pins defined within the supported ports.
 *
 * @see hal_ll_gpio_port_index()
 * @see hal_ll_gpio_pin_index()
 *
 * @link https://github.com/MikroElektronika/mikrosdk_v2/blob/master/targets/arm/mikroe/sam/include/gpio/hal_ll_gpio_port.h#L201 Link to header @endlink.
 * @link https://github.com/MikroElektronika/mikrosdk_v2/blob/master/targets/arm/mikroe/sam/src/gpio/implementations/implementation_1/hal_ll_gpio_port.c Link to source @endlink.
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
 * @return Base address of the GPIO port.
 *
 * @note
 * The base address is used for direct register access to the port.
 *
 * @pre
 * The port name must be valid and correspond to a supported port.
 *
 * @post
 * Returns the base address for the specified port.
 *
 * @warning
 * Using an invalid port name may result in undefined behavior.
 *
 * @par Example Usage
 * @code{.c}
 *    // Get port base address. *    hal_ll_gpio_port_base( PORTB );
 * @endcode
 *
 * @par Limitations
 * - Only valid for ports defined in the target device.
 *
 * @see hal_ll_gpio_port_index()
 *
 * @link https://github.com/MikroElektronika/mikrosdk_v2/blob/master/targets/arm/mikroe/sam/include/gpio/hal_ll_gpio_port.h#L238 Link to header @endlink.
 * @link https://github.com/MikroElektronika/mikrosdk_v2/blob/master/targets/arm/mikroe/sam/src/gpio/implementations/implementation_1/hal_ll_gpio_port.c Link to source @endlink.
 */
uint32_t hal_ll_gpio_port_base( hal_ll_port_name_t name );

/**
 * @brief Configure GPIO pins as analog input.
 *
 * @details
 * Sets the specified pins on the given port to analog input mode.
 *
 * @param[in,out] port Pointer to the GPIO port base handle.
 * See @ref hal_ll_gpio_base_t for details.
 * @param[in] pin_mask Bitmask representing the pins to configure.
 * See @ref hal_ll_gpio_mask_t for details.
 *
 * @return None.
 *
 * @note
 * This function disables digital input/output functionality on the specified pins.
 *
 * @pre
 * The port handle must be valid and initialized.
 *
 * @post
 * The specified pins are configured as analog inputs.
 *
 * @warning
 * Pins configured as analog inputs cannot be used for digital I/O until reconfigured.
 *
 * @par Example Usage
 * @code{.c}
 *    // Set pin 0 (mask 0x01) of PORTB as analog input. *    hal_ll_gpio_analog_input( hal_ll_gpio_port_base( PORTB ), 0x01 );
 * @endcode
 *
 * @par Limitations
 * - Only pins supporting analog input can be configured.
 *
 * @see hal_ll_gpio_digital_input()
 * @see hal_ll_gpio_digital_output()
 *
 * @link https://github.com/MikroElektronika/mikrosdk_v2/blob/master/targets/arm/mikroe/sam/include/gpio/hal_ll_gpio_port.h#L279 Link to header @endlink.
 * @link https://github.com/MikroElektronika/mikrosdk_v2/blob/master/targets/arm/mikroe/sam/src/gpio/implementations/implementation_1/hal_ll_gpio_port.c#L169 Link to source @endlink.
 */
void hal_ll_gpio_analog_input( hal_ll_gpio_base_t *port, hal_ll_gpio_mask_t pin_mask );

/**
 * @brief Configure GPIO pins as digital input.
 *
 * @details
 * Sets the specified pins on the given port to digital input mode with filtering enabled.
 *
 * @param[in,out] port Pointer to the GPIO port base handle.
 * See @ref hal_ll_gpio_base_t for details.
 * @param[in] pin_mask Bitmask representing the pins to configure.
 * See @ref hal_ll_gpio_mask_t for details.
 *
 * @return None.
 *
 * @note
 * Enables input filtering to reduce noise on the input pins.
 *
 * @pre
 * The port handle must be valid and initialized.
 *
 * @post
 * The specified pins are configured as digital inputs.
 *
 * @warning
 * Pins configured as digital inputs cannot drive output signals.
 *
 * @par Example Usage
 * @code{.c}
 *    // Set pin 0 (mask 0x01) of PORTB as digital input. *    hal_ll_gpio_digital_input( hal_ll_gpio_port_base( PORTB ), 0x01 );
 * @endcode
 *
 * @par Limitations
 * - Only pins supporting digital input can be configured.
 *
 * @see hal_ll_gpio_analog_input()
 * @see hal_ll_gpio_digital_output()
 *
 * @link https://github.com/MikroElektronika/mikrosdk_v2/blob/master/targets/arm/mikroe/sam/include/gpio/hal_ll_gpio_port.h#L320 Link to header @endlink.
 * @link https://github.com/MikroElektronika/mikrosdk_v2/blob/master/targets/arm/mikroe/sam/src/gpio/implementations/implementation_1/hal_ll_gpio_port.c#L174 Link to source @endlink.
 */
void hal_ll_gpio_digital_input( hal_ll_gpio_base_t *port, hal_ll_gpio_mask_t pin_mask );

/**
 * @brief Configure GPIO pins as digital output.
 *
 * @details
 * Sets the specified pins on the given port to digital output mode and enables pull-up resistors.
 *
 * @param[in,out] port Pointer to the GPIO port base handle.
 * See @ref hal_ll_gpio_base_t for details.
 * @param[in] pin_mask Bitmask representing the pins to configure.
 * See @ref hal_ll_gpio_mask_t for details.
 *
 * @return None.
 *
 * @note
 * Enables output driver and pull-up resistors on the specified pins.
 *
 * @pre
 * The port handle must be valid and initialized.
 *
 * @post
 * The specified pins are configured as digital outputs.
 *
 * @warning
 * Pins configured as digital outputs will drive signals and should not be connected to conflicting outputs.
 *
 * @par Example Usage
 * @code{.c}
 *    // Set pin 0 (mask 0x01) of PORTB as digital output. *    hal_ll_gpio_digital_output( hal_ll_gpio_port_base( PORTB ), 0x01 );
 * @endcode
 *
 * @par Limitations
 * - Only pins supporting digital output can be configured.
 *
 * @see hal_ll_gpio_analog_input()
 * @see hal_ll_gpio_digital_input()
 *
 * @link https://github.com/MikroElektronika/mikrosdk_v2/blob/master/targets/arm/mikroe/sam/include/gpio/hal_ll_gpio_port.h#L361 Link to header @endlink.
 * @link https://github.com/MikroElektronika/mikrosdk_v2/blob/master/targets/arm/mikroe/sam/src/gpio/implementations/implementation_1/hal_ll_gpio_port.c#L179 Link to source @endlink.
 */
void hal_ll_gpio_digital_output( hal_ll_gpio_base_t *port, hal_ll_gpio_mask_t pin_mask );

/**
 * @brief Initialize GPIO module pins with specified state.
 *
 * @details
 * Iterates through the pins and configurations in the provided module_struct and
 * enables or disables alternate functions for each pin based on the state parameter.
 *
 * @param[in] module Pointer to the module_struct containing pins and their configurations.
 * See @ref module_struct for details.
 * @param[in] state Boolean value indicating whether to enable (true) or disable (false) the alternate functions.
 *
 * @return None.
 *
 * @note
 * This function is used to initialize or deinitialize multiple pins belonging to a GPIO module.
 *
 * @pre
 * The module_struct must be properly initialized with valid pins and configurations.
 *
 * @post
 * The alternate function state of the specified pins is set according to the state parameter.
 *
 * @warning
 * Passing an invalid module_struct or incorrect state may cause undefined behavior.
 *
 * @par Example Usage
 * @code{.c}
 *    module_struct module; *    bool hal_ll_state; *    hal_ll_gpio_module_struct_init( &module, hal_ll_state );
 * @endcode
 *
 * @par Limitations
 * - Only pins and configurations supported by the hardware should be used.
 *
 * @see hal_ll_gpio_config_pin_alternate_enable()
 *
 * @link https://github.com/MikroElektronika/mikrosdk_v2/blob/master/targets/arm/mikroe/sam/include/gpio/hal_ll_gpio_port.h#L401 Link to header @endlink.
 * @link https://github.com/MikroElektronika/mikrosdk_v2/blob/master/targets/arm/mikroe/sam/src/gpio/implementations/implementation_1/hal_ll_gpio_port.c#L184 Link to source @endlink.
 */
void hal_ll_gpio_module_struct_init( module_struct const *module, bool state );

#ifdef __cplusplus
}
#endif

#endif // _HAL_LL_GPIO_PORT_H_
// ------------------------------------------------------------------------- END
