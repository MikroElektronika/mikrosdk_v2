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
 * @brief Structure representing base addresses of GPIO port registers.
 *
 * @details
 * This structure holds the base addresses for the PORT, DDR (Data Direction Register),
 * and PIN registers of a GPIO port. These addresses are used to access and manipulate
 * the hardware registers corresponding to a specific GPIO port.
 */
typedef struct {
    hal_ll_base_addr_t port_reg_addr; /**< Base address of the PORT register */
    hal_ll_base_addr_t ddr_reg_addr;  /**< Base address of the DDR register */
    hal_ll_base_addr_t pin_reg_addr;  /**< Base address of the PIN register */
} hal_ll_gpio_base_handle_t;

/**
 *  Handle and mask types.
 */

/**
 * @brief Type definition for GPIO base handle.
 *
 * @details
 * This type represents a handle to a GPIO base, typically used to identify
 * a specific GPIO port or group of pins.
 */
typedef handle_t hal_ll_gpio_base_t;

/**
 * @brief Enumeration for GPIO pin direction.
 *
 * @details
 * This enumeration defines the possible directions for a GPIO pin,
 * indicating whether the pin is configured as an input or output.
 */
typedef enum {
    HAL_LL_GPIO_DIGITAL_INPUT = 0,  /**< Pin configured as digital input */
    HAL_LL_GPIO_DIGITAL_OUTPUT = 1  /**< Pin configured as digital output */
} hal_ll_gpio_direction_t;

/**
 * @brief Structure representing a GPIO pin or port.
 *
 * @details
 * This structure encapsulates a GPIO base handle and a mask representing
 * the specific pin(s) within the port. It is used to identify and manipulate
 * individual pins or groups of pins on a GPIO port.
 */
typedef struct hal_ll_gpio_t {
    hal_ll_gpio_base_t base; /**< Base handle for the GPIO port */
    hal_ll_gpio_mask_t mask; /**< Mask identifying specific pin(s) */
};

/**
 *  Pin and port data types.
 */

/**
 * @brief Type definition for a GPIO pin.
 *
 * @details
 * This type represents a GPIO pin, defined as a structure containing
 * a base handle and a mask.
 */
typedef struct hal_ll_gpio_t hal_ll_gpio_pin_t;

/**
 * @brief Type definition for a GPIO port.
 *
 * @details
 * This type represents a GPIO port, defined as a structure containing
 * a base handle and a mask.
 */
typedef struct hal_ll_gpio_t hal_ll_gpio_port_t;

/**
 * @brief Get the index of the port for a given pin name.
 *
 * @details
 * This function calculates the port index corresponding to the specified pin name.
 * The port index is used to identify the port within the microcontroller's GPIO ports.
 *
 * @param[in] name The pin name for which to get the port index.
 * See @ref hal_ll_pin_name_t for details.
 *
 * @return
 * The index of the port as an 8-bit unsigned integer.
 *
 * @note
 * The port index is derived by dividing the pin name value by the port size.
 *
 * @pre
 * The pin name must be valid and correspond to an existing pin.
 *
 * @post
 * None.
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
 * - Assumes pin names are sequentially ordered per port.
 *
 * @see hal_ll_gpio_port_pin_mask()
 * @see hal_ll_gpio_port_pin_index()
 *
 * @link https://github.com/MikroElektronika/mikrosdk_v2/blob/master/targets/avr_8bit/mikroe/avr/include/gpio/hal_ll_gpio_port.h#L167 Link to header @endlink.
 * @link https://github.com/MikroElektronika/mikrosdk_v2/blob/master/targets/avr_8bit/mikroe/avr/src/gpio/implementation_1/subimplementation_1/hal_ll_gpio_port.c#L200 Link to source @endlink.
 */
uint8_t hal_ll_gpio_port_index(hal_ll_pin_name_t name);

/**
 * @brief Get the pin mask for a given pin name within its port.
 *
 * @details
 * This function returns a bitmask representing the position of the specified pin
 * within its GPIO port. The mask can be used to manipulate or configure the pin
 * in the port's registers.
 *
 * @param[in] name The pin name for which to get the mask.
 * See @ref hal_ll_pin_name_t for details.
 *
 * @return
 * An 8-bit mask with a single bit set corresponding to the pin's position.
 *
 * @note
 * The mask is calculated by shifting 1 by the pin's index within the port.
 *
 * @pre
 * The pin name must be valid and correspond to an existing pin.
 *
 * @post
 * None.
 *
 * @warning
 * Using an invalid pin name may produce an incorrect mask.
 *
 * @par Example Usage
 * @code{.c}
 *     TODO: ADD EXAMPLE CODE FOR `uint8_t hal_ll_gpio_port_pin_mask(hal_ll_pin_name_t name)`
 * @endcode
 *
 * @par Limitations
 * - Assumes pins are indexed from 0 within each port.
 *
 * @see hal_ll_gpio_port_index()
 * @see hal_ll_gpio_port_pin_index()
 *
 * @link https://github.com/MikroElektronika/mikrosdk_v2/blob/master/targets/avr_8bit/mikroe/avr/include/gpio/hal_ll_gpio_port.h#L209 Link to header @endlink.
 * @link https://github.com/MikroElektronika/mikrosdk_v2/blob/master/targets/avr_8bit/mikroe/avr/src/gpio/implementation_1/subimplementation_1/hal_ll_gpio_port.c#L209 Link to source @endlink.
 */
uint8_t hal_ll_gpio_port_pin_mask(hal_ll_pin_name_t name);

/**
 * @brief Get the base address map of a GPIO port.
 *
 * @details
 * This function returns the base address of the register map for the specified GPIO port.
 * The returned address points to the structure containing the PORT, DDR, and PIN register addresses.
 *
 * @param[in] name The port name for which to get the base map.
 * See @ref hal_ll_port_name_t for details.
 *
 * @return
 * The base address of the port's register map as a 16-bit unsigned integer.
 *
 * @note
 * The returned address can be cast to a pointer to hal_ll_gpio_base_handle_t for register access.
 *
 * @pre
 * The port name must be valid and correspond to an existing port.
 *
 * @post
 * None.
 *
 * @warning
 * Using an invalid port name may result in a null or invalid address.
 *
 * @par Example Usage
 * @code{.c}
 *     TODO: ADD EXAMPLE CODE FOR `uint16_t hal_ll_gpio_port_base_map(hal_ll_port_name_t name)`
 * @endcode
 *
 * @par Limitations
 * - Only valid for ports defined in the hardware abstraction layer.
 *
 * @see hal_ll_gpio_base_handle_t
 *
 * @link https://github.com/MikroElektronika/mikrosdk_v2/blob/master/targets/avr_8bit/mikroe/avr/include/gpio/hal_ll_gpio_port.h#L249 Link to header @endlink.
 * @link https://github.com/MikroElektronika/mikrosdk_v2/blob/master/targets/avr_8bit/mikroe/avr/src/gpio/implementation_1/subimplementation_1/hal_ll_gpio_port.c#L218 Link to source @endlink.
 */
uint16_t hal_ll_gpio_port_base_map(hal_ll_port_name_t name);

/**
 * @brief Configure a GPIO pin as an analog input.
 *
 * @details
 * This function configures the specified pin on the given port as an analog input.
 * It disables the digital input buffer and pull-up resistors to allow analog signals.
 *
 * @param[in,out] port Pointer to the base address of the GPIO port registers.
 * See @ref hal_ll_gpio_base_handle_t for details.
 * @param[in] pin_mask Bitmask representing the pin(s) to configure.
 * See @ref hal_ll_gpio_mask_t for details.
 *
 * @return
 * None.
 *
 * @note
 * This function internally calls hal_ll_gpio_port_config() with the analog input configuration.
 *
 * @pre
 * The port pointer must be valid and point to a valid GPIO port register set.
 *
 * @post
 * The specified pin(s) will be configured as analog inputs.
 *
 * @warning
 * Configuring a pin as analog input disables its digital input functionality.
 *
 * @par Example Usage
 * @code{.c}
 *     TODO: ADD EXAMPLE CODE FOR `void hal_ll_gpio_port_analog_input(uint16_t *port, uint8_t pin_mask)`
 * @endcode
 *
 * @par Limitations
 * - Only applicable to pins that support analog input functionality.
 *
 * @see hal_ll_gpio_port_config()
 *
 * @link https://github.com/MikroElektronika/mikrosdk_v2/blob/master/targets/avr_8bit/mikroe/avr/include/gpio/hal_ll_gpio_port.h#L291 Link to header @endlink.
 * @link https://github.com/MikroElektronika/mikrosdk_v2/blob/master/targets/avr_8bit/mikroe/avr/src/gpio/implementation_1/subimplementation_1/hal_ll_gpio_port.c#L228 Link to source @endlink.
 */
void hal_ll_gpio_port_analog_input(uint16_t *port, uint8_t pin_mask);

/**
 * @brief Configure a GPIO port's pins as digital input or output.
 *
 * @details
 * This function configures the direction of pins on a GPIO port as either digital input or output.
 * It modifies the data direction register (DDR) bits corresponding to the pins specified in the mask.
 *
 * @param[in,out] port Pointer to a hal_ll_gpio_port_t structure representing the port and pins.
 * See @ref hal_ll_gpio_port_t for details.
 * @param[in] name The port index or identifier.
 * See @ref uint8_t for details.
 * @param[in] is_input Boolean flag indicating direction:
 * - true: configure pins as input.
 * - false: configure pins as output.
 *
 * @return
 * None.
 *
 * @note
 * This function directly manipulates the DDR register bits for the specified pins.
 *
 * @pre
 * The port structure must be properly initialized with valid base and mask values.
 *
 * @post
 * The pins specified in the mask will be configured as input or output accordingly.
 *
 * @warning
 * Changing pin direction may affect connected peripherals or circuits.
 *
 * @par Example Usage
 * @code{.c}
 *     TODO: ADD EXAMPLE CODE FOR `void hal_ll_gpio_port_digital_configure_port(hal_ll_gpio_port_t *port, uint8_t name, bool is_input)`
 * @endcode
 *
 * @par Limitations
 * - Assumes the port base points to valid hardware registers.
 *
 * @see hal_ll_gpio_port_digital_input()
 * @see hal_ll_gpio_port_digital_output()
 *
 * @link https://github.com/MikroElektronika/mikrosdk_v2/blob/master/targets/avr_8bit/mikroe/avr/include/gpio/hal_ll_gpio_port.h#L337 Link to header @endlink.
 * @link https://github.com/MikroElektronika/mikrosdk_v2/blob/master/targets/avr_8bit/mikroe/avr/src/gpio/implementation_1/subimplementation_1/hal_ll_gpio_port.c#L242 Link to source @endlink.
 */
void hal_ll_gpio_port_digital_configure_port(hal_ll_gpio_port_t *port, uint8_t name, bool is_input);

/**
 * @brief Configure a GPIO pin as a digital input.
 *
 * @details
 * This function configures the specified pin on the given port as a digital input.
 * It sets the data direction register accordingly to enable input mode.
 *
 * @param[in,out] port Pointer to the base address of the GPIO port registers.
 * See @ref hal_ll_gpio_base_handle_t for details.
 * @param[in] pin_mask Bitmask representing the pin(s) to configure.
 * See @ref hal_ll_gpio_mask_t for details.
 *
 * @return
 * None.
 *
 * @note
 * This function internally calls hal_ll_gpio_port_config() with the digital input configuration.
 *
 * @pre
 * The port pointer must be valid and point to a valid GPIO port register set.
 *
 * @post
 * The specified pin(s) will be configured as digital inputs.
 *
 * @warning
 * Pull-up resistors are not enabled by this function; they must be configured separately if needed.
 *
 * @par Example Usage
 * @code{.c}
 *     TODO: ADD EXAMPLE CODE FOR `void hal_ll_gpio_port_digital_input(uint16_t *port, uint8_t pin_mask)`
 * @endcode
 *
 * @par Limitations
 * - Does not configure pull-up or pull-down resistors.
 *
 * @see hal_ll_gpio_port_config()
 *
 * @link https://github.com/MikroElektronika/mikrosdk_v2/blob/master/targets/avr_8bit/mikroe/avr/include/gpio/hal_ll_gpio_port.h#L379 Link to header @endlink.
 * @link https://github.com/MikroElektronika/mikrosdk_v2/blob/master/targets/avr_8bit/mikroe/avr/src/gpio/implementation_1/subimplementation_1/hal_ll_gpio_port.c#L238 Link to source @endlink.
 */
void hal_ll_gpio_port_digital_input(uint16_t *port, uint8_t pin_mask);

/**
 * @brief Configure a GPIO pin as a digital output.
 *
 * @details
 * This function configures the specified pin on the given port as a digital output.
 * It sets the data direction register accordingly to enable output mode.
 *
 * @param[in,out] port Pointer to the base address of the GPIO port registers.
 * See @ref hal_ll_gpio_base_handle_t for details.
 * @param[in] pin_mask Bitmask representing the pin(s) to configure.
 * See @ref hal_ll_gpio_mask_t for details.
 *
 * @return
 * None.
 *
 * @note
 * This function internally calls hal_ll_gpio_port_config() with the digital output configuration.
 *
 * @pre
 * The port pointer must be valid and point to a valid GPIO port register set.
 *
 * @post
 * The specified pin(s) will be configured as digital outputs.
 *
 * @warning
 * Output pins should be driven carefully to avoid conflicts on the bus.
 *
 * @par Example Usage
 * @code{.c}
 *     TODO: ADD EXAMPLE CODE FOR `void hal_ll_gpio_port_digital_output(uint16_t *port, uint8_t pin)`
 * @endcode
 *
 * @par Limitations
 * - Does not set the output value; only configures direction.
 *
 * @see hal_ll_gpio_port_config()
 *
 * @link https://github.com/MikroElektronika/mikrosdk_v2/blob/master/targets/avr_8bit/mikroe/avr/include/gpio/hal_ll_gpio_port.h#L421 Link to header @endlink.
 * @link https://github.com/MikroElektronika/mikrosdk_v2/blob/master/targets/avr_8bit/mikroe/avr/src/gpio/implementation_1/subimplementation_1/hal_ll_gpio_port.c#L259 Link to source @endlink.
 */
void hal_ll_gpio_port_digital_output(uint16_t *port, uint8_t pin);

#endif // _HAL_LL_GPIO_PORT_H_
// ------------------------------------------------------------------------- END
