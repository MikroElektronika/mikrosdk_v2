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

#ifndef _HAL_LL_GPIO_H_
#define _HAL_LL_GPIO_H_

#include "hal_ll_gpio_port.h"

#ifdef __cplusplus
extern "C"{
#endif

/**
 * @brief Configures a GPIO pin with specified parameters.
 *
 * @details
 * Initializes the given GPIO pin structure with the base address and mask
 * corresponding to the pin name. Sets the pin direction as input or output.
 * This function prepares the pin for digital input or output operations.
 *
 * @param[in,out] pin Pointer to the GPIO pin structure to configure.
 * See @ref hal_ll_gpio_pin_t structure definition for more details.
 * @param[in] name The identifier of the pin to configure.
 * See @ref hal_ll_pin_name_t for valid pin names.
 * @param[in] direction Direction to set for the pin (input or output).
 * See @ref hal_ll_gpio_direction_t for possible directions.
 *
 * @return
 * - None.
 *
 * @note
 * - The pin structure is updated with base and mask values internally.
 * - Direction must be either HAL_LL_GPIO_DIGITAL_INPUT or HAL_LL_GPIO_DIGITAL_OUTPUT.
 *
 * @pre
 * - The pin name must be valid and supported by the hardware.
 *
 * @post
 * - The pin is configured and ready for digital I/O operations.
 *
 * @warning
 * - Calling this function with invalid parameters may lead to undefined behavior.
 *
 * @par Example Usage
 * @code{.c}
 *    // GPIO low level structure. *    hal_ll_gpio_pin_t pin; * *    // Initialize pin as output. *    hal_ll_gpio_configure_pin( &pin, GPIO_PB2, HAL_LL_GPIO_DIGITAL_OUTPUT );
 * @endcode
 *
 * @par Limitations
 * - Only supports digital input and output directions.
 *
 * @see hal_ll_gpio_pin_t
 * @see hal_ll_pin_name_t
 * @see hal_ll_gpio_direction_t
 *
 * @link https://github.com/MikroElektronika/mikrosdk_v2/blob/master/targets/arm/mikroe/tiva/include/gpio/hal_ll_gpio.h#L99 Link to header @endlink.
 * @link https://github.com/MikroElektronika/mikrosdk_v2/blob/master/targets/arm/mikroe/tiva/src/gpio/hal_ll_gpio.c#L49 Link to source @endlink.
 */
void hal_ll_gpio_configure_pin(hal_ll_gpio_pin_t *pin, hal_ll_pin_name_t name, hal_ll_gpio_direction_t direction);

/**
 * @brief Reads the input state of a GPIO pin.
 *
 * @details
 * Returns the current logical level present on the specified GPIO pin's input.
 * The function reads the pin's input data register and masks the relevant bit.
 *
 * @param[in] pin Pointer to the GPIO pin structure to read from.
 * See @ref hal_ll_gpio_pin_t structure definition for more details.
 *
 * @return
 * - 1 if the pin input is high.
 * - 0 if the pin input is low or invalid.
 *
 * @note
 * - This function may be implemented as a macro depending on compilation flags.
 * - Reading input state does not affect pin configuration.
 *
 * @pre
 * - The pin must be configured as input or capable of input reading.
 *
 * @post
 * - No side effects.
 *
 * @warning
 * - Reading from an uninitialized or invalid pin may return 0.
 *
 * @par Example Usage
 * @code{.c}
 *    // GPIO low level structure. *    hal_ll_gpio_pin_t pin; * *    // GPIO value holder. *    hal_port_size_t read_value; * *    // Read the input state of the pin. *    read_value = hal_ll_gpio_read_pin_input( &pin );
 * @endcode
 *
 * @par Limitations
 * - Only returns binary state (0 or 1).
 *
 * @see hal_ll_gpio_pin_t
 *
 * @link https://github.com/MikroElektronika/mikrosdk_v2/blob/master/targets/arm/mikroe/tiva/include/gpio/hal_ll_gpio.h#L143 Link to header @endlink.
 * @link https://github.com/MikroElektronika/mikrosdk_v2/blob/master/targets/arm/mikroe/tiva/src/gpio/hal_ll_gpio.c Link to source @endlink.
 */
#if defined(FLATTEN_ME) && (FLATTEN_ME_LEVEL >= FLATTEN_ME_LEVEL_LOW)
#define hal_ll_gpio_read_pin_input(_handle) ((((hal_ll_gpio_base_handle_t *)((hal_ll_gpio_pin_t *)_handle)->base) == 0) ? \
                                             (0) : (((hal_ll_gpio_base_handle_t *)((hal_ll_gpio_pin_t *)_handle)->base)->gpiodata & ((hal_ll_gpio_pin_t *)_handle)->mask) ? \
                                             (1) : (0))
#else
uint8_t hal_ll_gpio_read_pin_input(hal_ll_gpio_pin_t *pin);
#endif

/**
 * @brief Reads the output state of a GPIO pin.
 *
 * @details
 * Returns the current logical level driven on the specified GPIO pin's output.
 * The function reads the pin's output data register and masks the relevant bit.
 *
 * @param[in] pin Pointer to the GPIO pin structure to read from.
 * See @ref hal_ll_gpio_pin_t structure definition for more details.
 *
 * @return
 * - 1 if the pin output is high.
 * - 0 if the pin output is low or invalid.
 *
 * @note
 * - This function may be implemented as a macro depending on compilation flags.
 * - Reading output state does not affect pin configuration.
 *
 * @pre
 * - The pin must be configured as output or capable of output reading.
 *
 * @post
 * - No side effects.
 *
 * @warning
 * - Reading from an uninitialized or invalid pin may return 0.
 *
 * @par Example Usage
 * @code{.c}
 *    // GPIO low level structure. *    hal_ll_gpio_pin_t pin; * *    // GPIO value holder. *    hal_port_size_t read_value; * *    // Read the output state of the pin. *    read_value = hal_ll_gpio_read_pin_output( &pin );
 * @endcode
 *
 * @par Limitations
 * - Only returns binary state (0 or 1).
 *
 * @see hal_ll_gpio_pin_t
 *
 * @link https://github.com/MikroElektronika/mikrosdk_v2/blob/master/targets/arm/mikroe/tiva/include/gpio/hal_ll_gpio.h#L191 Link to header @endlink.
 * @link https://github.com/MikroElektronika/mikrosdk_v2/blob/master/targets/arm/mikroe/tiva/src/gpio/hal_ll_gpio.c Link to source @endlink.
 */
#if defined(FLATTEN_ME) && (FLATTEN_ME_LEVEL >= FLATTEN_ME_LEVEL_LOW)
#define hal_ll_gpio_read_pin_output(_handle) ((((hal_ll_gpio_base_handle_t *)((hal_ll_gpio_pin_t *)_handle)->base) == 0) ? \
                                              (0) : (((hal_ll_gpio_base_handle_t *)((hal_ll_gpio_pin_t *)_handle)->base)->gpiodata & ((hal_ll_gpio_pin_t *)_handle)->mask) ? \
                                              (1) : (0))
#else
uint8_t hal_ll_gpio_read_pin_output(hal_ll_gpio_pin_t *pin);
#endif

/**
 * @brief Writes a logical value to a GPIO pin output.
 *
 * @details
 * Sets or clears the output state of the specified GPIO pin according to the
 * provided value. A non-zero value sets the pin high; zero clears it low.
 *
 * @param[in,out] pin Pointer to the GPIO pin structure to write to.
 * See @ref hal_ll_gpio_pin_t structure definition for more details.
 * @param[in] value Logical value to write to the pin output (0 or non-zero).
 *
 * @return
 * - None.
 *
 * @note
 * - This function may be implemented as a macro depending on compilation flags.
 * - Writing affects only the pin's output data register bit.
 *
 * @pre
 * - The pin must be configured as output.
 *
 * @post
 * - The pin output state is updated accordingly.
 *
 * @warning
 * - Writing to a pin configured as input may have no effect or undefined behavior.
 *
 * @par Example Usage
 * @code{.c}
 *    // GPIO low level structure. *    hal_ll_gpio_pin_t pin; * *    // Set pin logic state to high (1). *    hal_ll_gpio_write_pin_output( &pin, 1 );
 * @endcode
 *
 * @par Limitations
 * - Only supports binary output values.
 *
 * @see hal_ll_gpio_pin_t
 *
 * @link https://github.com/MikroElektronika/mikrosdk_v2/blob/master/targets/arm/mikroe/tiva/include/gpio/hal_ll_gpio.h#L239 Link to header @endlink.
 * @link https://github.com/MikroElektronika/mikrosdk_v2/blob/master/targets/arm/mikroe/tiva/src/gpio/hal_ll_gpio.c Link to source @endlink.
 */
#if defined(FLATTEN_ME) && (FLATTEN_ME_LEVEL >= FLATTEN_ME_LEVEL_LOW)
#define hal_ll_gpio_write_pin_output(_handle,_value) ((((hal_ll_gpio_base_handle_t *)((hal_ll_gpio_pin_t *)_handle)->base) != NULL) ? \
                                                          ((_value > 0) ? \
                                                           (((hal_ll_gpio_base_handle_t *)((hal_ll_gpio_pin_t *)_handle)->base)->gpiodata |= ((hal_ll_gpio_pin_t *)_handle)->mask) : \
                                                           (((hal_ll_gpio_base_handle_t *)((hal_ll_gpio_pin_t *)_handle)->base)->gpiodata &= ~((hal_ll_gpio_pin_t *)_handle)->mask)) : \
                                                      (0))
#else
void hal_ll_gpio_write_pin_output(hal_ll_gpio_pin_t *pin, uint8_t value);
#endif

/**
 * @brief Toggles the output state of a GPIO pin.
 *
 * @details
 * Reads the current output state of the specified GPIO pin and inverts it,
 * setting the pin output to the opposite logical level.
 *
 * @param[in,out] pin Pointer to the GPIO pin structure to toggle.
 * See @ref hal_ll_gpio_pin_t structure definition for more details.
 *
 * @return
 * - None.
 *
 * @note
 * - This function may be implemented as a macro depending on compilation flags.
 * - Toggling affects only the pin's output data register bit.
 *
 * @pre
 * - The pin must be configured as output.
 *
 * @post
 * - The pin output state is inverted.
 *
 * @warning
 * - Toggling a pin configured as input may have no effect or undefined behavior.
 *
 * @par Example Usage
 * @code{.c}
 *    // GPIO low level structure. *    hal_ll_gpio_pin_t pin; * *    // Toggle pin logic state. *    hal_ll_gpio_toggle_pin_output( &pin );
 * @endcode
 *
 * @par Limitations
 * - Only supports binary output values.
 *
 * @see hal_ll_gpio_pin_t
 * @see hal_ll_gpio_write_pin_output()
 * @see hal_ll_gpio_read_pin_output()
 *
 * @link https://github.com/MikroElektronika/mikrosdk_v2/blob/master/targets/arm/mikroe/tiva/include/gpio/hal_ll_gpio.h#L290 Link to header @endlink.
 * @link https://github.com/MikroElektronika/mikrosdk_v2/blob/master/targets/arm/mikroe/tiva/src/gpio/hal_ll_gpio.c Link to source @endlink.
 */
#if defined(FLATTEN_ME) && (FLATTEN_ME_LEVEL >= FLATTEN_ME_LEVEL_LOW)
#define hal_ll_gpio_toggle_pin_output(_handle) ((((hal_ll_gpio_base_handle_t *)((hal_ll_gpio_pin_t *)_handle)->base) != NULL) ? \
                                                    ((((((hal_ll_gpio_base_handle_t *)((hal_ll_gpio_pin_t *)_handle)->base)->gpiodata & ((hal_ll_gpio_pin_t *)_handle)->mask))) ? \
                                                     (((hal_ll_gpio_base_handle_t *)((hal_ll_gpio_pin_t *)_handle)->base)->gpiodata &= ~((hal_ll_gpio_pin_t *)_handle)->mask) : \
                                                     (((hal_ll_gpio_base_handle_t *)((hal_ll_gpio_pin_t *)_handle)->base)->gpiodata |= ((hal_ll_gpio_pin_t *)_handle)->mask)) : \
                                                (0))
#else
void hal_ll_gpio_toggle_pin_output(hal_ll_gpio_pin_t *pin);
#endif

/**
 * @brief Sets the output state of a GPIO pin to high.
 *
 * @details
 * Sets the output data register bit corresponding to the specified GPIO pin,
 * driving the pin output to a logical high level.
 *
 * @param[in,out] pin Pointer to the GPIO pin structure to set.
 * See @ref hal_ll_gpio_pin_t structure definition for more details.
 *
 * @return
 * - None.
 *
 * @note
 * - This function may be implemented as a macro depending on compilation flags.
 * - Setting the pin does not affect other pins.
 *
 * @pre
 * - The pin must be configured as output.
 *
 * @post
 * - The pin output is set to high.
 *
 * @warning
 * - Setting a pin configured as input may have no effect or undefined behavior.
 *
 * @par Example Usage
 * @code{.c}
 *    // GPIO low level structure. *    hal_ll_gpio_pin_t pin; * *    // Set pin logical state to high. *    hal_ll_gpio_set_pin_output( &pin );
 * @endcode
 *
 * @par Limitations
 * - Only supports binary output values.
 *
 * @see hal_ll_gpio_pin_t
 *
 * @link https://github.com/MikroElektronika/mikrosdk_v2/blob/master/targets/arm/mikroe/tiva/include/gpio/hal_ll_gpio.h#L339 Link to header @endlink.
 * @link https://github.com/MikroElektronika/mikrosdk_v2/blob/master/targets/arm/mikroe/tiva/src/gpio/hal_ll_gpio.c Link to source @endlink.
 */
#if defined(FLATTEN_ME) && (FLATTEN_ME_LEVEL >= FLATTEN_ME_LEVEL_LOW)
#define hal_ll_gpio_set_pin_output(_handle) ((((hal_ll_gpio_base_handle_t *)((hal_ll_gpio_pin_t *)_handle)->base) != NULL) ? \
                                             (((hal_ll_gpio_base_handle_t *)((hal_ll_gpio_pin_t *)_handle)->base)->gpiodata |= ((hal_ll_gpio_pin_t *)_handle)->mask) : \
                                             (0))
#else
void hal_ll_gpio_set_pin_output(hal_ll_gpio_pin_t *pin);
#endif

/**
 * @brief Clears the output state of a GPIO pin to low.
 *
 * @details
 * Clears the output data register bit corresponding to the specified GPIO pin,
 * driving the pin output to a logical low level.
 *
 * @param[in,out] pin Pointer to the GPIO pin structure to clear.
 * See @ref hal_ll_gpio_pin_t structure definition for more details.
 *
 * @return
 * - None.
 *
 * @note
 * - This function may be implemented as a macro depending on compilation flags.
 * - Clearing the pin does not affect other pins.
 *
 * @pre
 * - The pin must be configured as output.
 *
 * @post
 * - The pin output is set to low.
 *
 * @warning
 * - Clearing a pin configured as input may have no effect or undefined behavior.
 *
 * @par Example Usage
 * @code{.c}
 *    // GPIO low level structure. *    hal_ll_gpio_pin_t pin; * *    // Set pin logical state to low. *    hal_ll_gpio_clear_pin_output( &pin );
 * @endcode
 *
 * @par Limitations
 * - Only supports binary output values.
 *
 * @see hal_ll_gpio_pin_t
 *
 * @link https://github.com/MikroElektronika/mikrosdk_v2/blob/master/targets/arm/mikroe/tiva/include/gpio/hal_ll_gpio.h#L386 Link to header @endlink.
 * @link https://github.com/MikroElektronika/mikrosdk_v2/blob/master/targets/arm/mikroe/tiva/src/gpio/hal_ll_gpio.c Link to source @endlink.
 */
#if defined(FLATTEN_ME) && (FLATTEN_ME_LEVEL >= FLATTEN_ME_LEVEL_LOW)
#define hal_ll_gpio_clear_pin_output(_handle) ((((hal_ll_gpio_base_handle_t *)((hal_ll_gpio_pin_t *)_handle)->base) != NULL) ? \
                                               (((hal_ll_gpio_base_handle_t *)((hal_ll_gpio_pin_t *)_handle)->base)->gpiodata &= ~((hal_ll_gpio_pin_t *)_handle)->mask) : \
                                               (0))
#else
void hal_ll_gpio_clear_pin_output(hal_ll_gpio_pin_t *pin);
#endif

/**
 * @brief Configures a GPIO port with specified parameters.
 *
 * @details
 * Initializes the given GPIO port structure with the base address and mask
 * corresponding to the port name and mask. Sets the port direction as input or output.
 * This function prepares the port for digital input or output operations on multiple pins.
 *
 * @param[in,out] port Pointer to the GPIO port structure to configure.
 * See @ref hal_ll_gpio_port_t structure definition for more details.
 * @param[in] name The identifier of the port to configure.
 * See @ref hal_ll_port_name_t for valid port names.
 * @param[in] mask Bitmask specifying which pins in the port to configure.
 * See @ref hal_ll_gpio_mask_t for mask details.
 * @param[in] direction Direction to set for the port pins (input or output).
 * See @ref hal_ll_gpio_direction_t for possible directions.
 *
 * @return
 * - None.
 *
 * @note
 * - The port structure is updated with base and mask values internally.
 * - Direction must be either HAL_LL_GPIO_DIGITAL_INPUT or HAL_LL_GPIO_DIGITAL_OUTPUT.
 *
 * @pre
 * - The port name and mask must be valid and supported by the hardware.
 *
 * @post
 * - The port pins specified by mask are configured and ready for digital I/O operations.
 *
 * @warning
 * - Calling this function with invalid parameters may lead to undefined behavior.
 *
 * @par Example Usage
 * @code{.c}
 *    // GPIO low level structure. *    hal_ll_gpio_port_t port; * *    // Initialize port as output. *    hal_ll_gpio_configure_port( &port, PORTB, 0xFF, HAL_LL_GPIO_DIGITAL_OUTPUT );
 * @endcode
 *
 * @par Limitations
 * - Only supports digital input and output directions.
 *
 * @see hal_ll_gpio_port_t
 * @see hal_ll_port_name_t
 * @see hal_ll_gpio_mask_t
 * @see hal_ll_gpio_direction_t
 *
 * @link https://github.com/MikroElektronika/mikrosdk_v2/blob/master/targets/arm/mikroe/tiva/include/gpio/hal_ll_gpio.h#L441 Link to header @endlink.
 * @link https://github.com/MikroElektronika/mikrosdk_v2/blob/master/targets/arm/mikroe/tiva/src/gpio/hal_ll_gpio.c#L126 Link to source @endlink.
 */
void hal_ll_gpio_configure_port(hal_ll_gpio_port_t *port, hal_ll_port_name_t name, hal_ll_gpio_mask_t mask, hal_ll_gpio_direction_t direction);

/**
 * @brief Reads the input state of a GPIO port.
 *
 * @details
 * Returns the current logical levels present on the specified GPIO port's input pins,
 * masked by the port's mask. The function reads the port's input data register.
 *
 * @param[in] port Pointer to the GPIO port structure to read from.
 * See @ref hal_ll_gpio_port_t structure definition for more details.
 *
 * @return
 * - Bitmask representing the input states of the masked pins.
 * - 0 if the port base is invalid.
 *
 * @note
 * - This function may be implemented as a macro depending on compilation flags.
 * - Reading input state does not affect port configuration.
 *
 * @pre
 * - The port must be configured as input or capable of input reading.
 *
 * @post
 * - No side effects.
 *
 * @warning
 * - Reading from an uninitialized or invalid port may return 0.
 *
 * @par Example Usage
 * @code{.c}
 *    // GPIO low level structure. *    hal_ll_gpio_port_t port; * *    // GPIO value holder. *    hal_port_size_t read_value; * *    // Read the input state of the port. *    read_value = hal_ll_gpio_read_port_input( &port );
 * @endcode
 *
 * @par Limitations
 * - Only returns masked input states.
 *
 * @see hal_ll_gpio_port_t
 *
 * @link https://github.com/MikroElektronika/mikrosdk_v2/blob/master/targets/arm/mikroe/tiva/include/gpio/hal_ll_gpio.h#L485 Link to header @endlink.
 * @link https://github.com/MikroElektronika/mikrosdk_v2/blob/master/targets/arm/mikroe/tiva/src/gpio/hal_ll_gpio.c Link to source @endlink.
 */
#if defined(FLATTEN_ME) && (FLATTEN_ME_LEVEL >= FLATTEN_ME_LEVEL_LOW)
#define hal_ll_gpio_read_port_input(_handle) ((((hal_ll_gpio_base_handle_t *)((hal_ll_gpio_port_t *)_handle)->base) != NULL) ? \
                                              ((hal_ll_port_size_t)(((hal_ll_gpio_base_handle_t *)((hal_ll_gpio_port_t *)_handle)->base)->gpiodata) & (((hal_ll_gpio_port_t *)_handle)->mask)) : \
                                              (0))
#else
hal_ll_port_size_t hal_ll_gpio_read_port_input(hal_ll_gpio_port_t *port);
#endif

/**
 * @brief Reads the output state of a GPIO port.
 *
 * @details
 * Returns the current logical levels driven on the specified GPIO port's output pins,
 * masked by the port's mask. The function reads the port's output data register.
 *
 * @param[in] port Pointer to the GPIO port structure to read from.
 * See @ref hal_ll_gpio_port_t structure definition for more details.
 *
 * @return
 * - Bitmask representing the output states of the masked pins.
 * - 0 if the port base is invalid.
 *
 * @note
 * - This function may be implemented as a macro depending on compilation flags.
 * - Reading output state does not affect port configuration.
 *
 * @pre
 * - The port must be configured as output or capable of output reading.
 *
 * @post
 * - No side effects.
 *
 * @warning
 * - Reading from an uninitialized or invalid port may return 0.
 *
 * @par Example Usage
 * @code{.c}
 *    // GPIO low level structure. *    hal_ll_gpio_port_t port; * *    // GPIO value holder. *    hal_port_size_t read_value; * *    // Read the output state of the port. *    read_value = hal_ll_gpio_read_port_output( &port );
 * @endcode
 *
 * @par Limitations
 * - Only returns masked output states.
 *
 * @see hal_ll_gpio_port_t
 *
 * @link https://github.com/MikroElektronika/mikrosdk_v2/blob/master/targets/arm/mikroe/tiva/include/gpio/hal_ll_gpio.h#L533 Link to header @endlink.
 * @link https://github.com/MikroElektronika/mikrosdk_v2/blob/master/targets/arm/mikroe/tiva/src/gpio/hal_ll_gpio.c Link to source @endlink.
 */
#if defined(FLATTEN_ME) && (FLATTEN_ME_LEVEL >= FLATTEN_ME_LEVEL_LOW)
#define hal_ll_gpio_read_port_output(_handle) ((((hal_ll_gpio_base_handle_t *)((hal_ll_gpio_port_t *)_handle)->base) != NULL) ? \
                                               ((hal_ll_port_size_t)(((hal_ll_gpio_base_handle_t *)((hal_ll_gpio_port_t *)_handle)->base)->gpiodata) & (((hal_ll_gpio_port_t *)_handle)->mask)) : \
                                               (0))
#else
hal_ll_port_size_t hal_ll_gpio_read_port_output(hal_ll_gpio_port_t *port);
#endif

/**
 * @brief Writes a logical value to a GPIO port output.
 *
 * @details
 * Sets the output data register bits corresponding to the specified GPIO port's
 * masked pins according to the provided value. Only bits within the mask are affected.
 *
 * @param[in,out] port Pointer to the GPIO port structure to write to.
 * See @ref hal_ll_gpio_port_t structure definition for more details.
 * @param[in] value Bitmask representing the logical values to write to the port pins.
 *
 * @return
 * - None.
 *
 * @note
 * - This function may be implemented as a macro depending on compilation flags.
 * - Writing affects only the masked pins of the port.
 *
 * @pre
 * - The port must be configured as output.
 *
 * @post
 * - The port output states are updated accordingly.
 *
 * @warning
 * - Writing to a port configured as input may have no effect or undefined behavior.
 *
 * @par Example Usage
 * @code{.c}
 *    // GPIO low level structure. *    hal_ll_gpio_port_t port; * *    // Set port logic state to 0xAA. *    hal_ll_gpio_write_port_output( &port, 0xAA );
 * @endcode
 *
 * @par Limitations
 * - Only supports binary output values per pin.
 *
 * @see hal_ll_gpio_port_t
 *
 * @link https://github.com/MikroElektronika/mikrosdk_v2/blob/master/targets/arm/mikroe/tiva/include/gpio/hal_ll_gpio.h#L581 Link to header @endlink.
 * @link https://github.com/MikroElektronika/mikrosdk_v2/blob/master/targets/arm/mikroe/tiva/src/gpio/hal_ll_gpio.c Link to source @endlink.
 */
#if defined(FLATTEN_ME) && (FLATTEN_ME_LEVEL >= FLATTEN_ME_LEVEL_LOW)
#define hal_ll_gpio_write_port_output(_handle,_value) ((((hal_ll_gpio_base_handle_t *)((hal_ll_gpio_port_t *)_handle)->base) != NULL) ? \
                                                          (((hal_ll_gpio_base_handle_t *)((hal_ll_gpio_port_t *)_handle)->base)->gpiodata = \
                                                           ((hal_ll_gpio_port_t *)_handle)->mask & (hal_ll_port_size_t)_value) : \
                                                       (0))
#else
void hal_ll_gpio_write_port_output(hal_ll_gpio_port_t *port, hal_ll_port_size_t value);
#endif

#ifdef __cplusplus
}
#endif

#endif // _HAL_LL_GPIO_H_
// ------------------------------------------------------------------------- END
