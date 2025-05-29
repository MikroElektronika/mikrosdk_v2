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
 * This function initializes a GPIO pin by setting its base address, mask, and direction.
 * It configures the pin as either digital input or digital output based on the direction parameter.
 *
 * @param[out] pin Pointer to the GPIO pin structure to be configured.
 * See @ref hal_ll_gpio_pin_t structure definition for more details.
 * @param[in] name The pin name identifier used to determine port and pin mask.
 * See @ref hal_ll_pin_name_t type for valid pin names.
 * @param[in] direction The direction to configure the pin for (input or output).
 * See @ref hal_ll_gpio_direction_t enumeration for possible directions.
 *
 * @return
 * - None.
 *
 * @note
 * - The function assumes the pin name is valid and corresponds to a valid GPIO port.
 * - The pin structure is updated with base address and mask for further operations.
 *
 * @pre
 * - The GPIO port base must be accessible.
 *
 * @post
 * - The pin is configured as digital input or output.
 *
 * @warning
 * - Calling this function with invalid pin names may cause undefined behavior.
 *
 * @par Example Usage
 * @code{.c}
 *    // GPIO low level structure. *    hal_ll_gpio_pin_t pin; * *    // Initialize pin as output. *    hal_ll_gpio_configure_pin( &pin, GPIO_PB2, HAL_LL_GPIO_DIGITAL_OUTPUT );
 * @endcode
 *
 * @par Limitations
 * - Does not configure alternate functions or pull-up/down resistors.
 *
 * @see hal_ll_gpio_pin_t
 * @see hal_ll_pin_name_t
 * @see hal_ll_gpio_direction_t
 *
 * @link https://github.com/MikroElektronika/mikrosdk_v2/blob/master/targets/arm/mikroe/stm32/include/gpio/hal_ll_gpio.h#L98 Link to header @endlink.
 * @link https://github.com/MikroElektronika/mikrosdk_v2/blob/master/targets/arm/mikroe/stm32/src/gpio/hal_ll_gpio.c#L49 Link to source @endlink.
 */
void hal_ll_gpio_configure_pin(hal_ll_gpio_pin_t *pin, hal_ll_pin_name_t name, hal_ll_gpio_direction_t direction);

/**
 * @brief Reads the input state of a GPIO pin.
 *
 * @details
 * This function reads the current logical level present on the specified GPIO pin's input data register.
 * It returns 1 if the pin input is high, or 0 if it is low.
 *
 * @param[in] pin Pointer to the GPIO pin structure to read from.
 * See @ref hal_ll_gpio_pin_t structure definition for more details.
 *
 * @return
 * - 1 if the pin input is high.
 * - 0 if the pin input is low or if the pin base is NULL.
 *
 * @note
 * - The function reads the input data register (IDR) of the GPIO port.
 * - If the pin base is NULL, the function returns 0.
 *
 * @pre
 * - The pin must be configured as input or capable of reading input state.
 *
 * @post
 * - No side effects.
 *
 * @warning
 * - Reading from an uninitialized pin may yield undefined results.
 *
 * @par Example Usage
 * @code{.c}
 *    // GPIO low level structure. *    hal_ll_gpio_pin_t pin; * *    // GPIO value holder. *    hal_port_size_t read_value; * *    // Read the input state of the pin. *    read_value = hal_ll_gpio_read_pin_input( &pin );
 * @endcode
 *
 * @par Limitations
 * - Does not debounce or filter input signals.
 *
 * @see hal_ll_gpio_pin_t
 *
 * @link https://github.com/MikroElektronika/mikrosdk_v2/blob/master/targets/arm/mikroe/stm32/include/gpio/hal_ll_gpio.h#L142 Link to header @endlink.
 * @link https://github.com/MikroElektronika/mikrosdk_v2/blob/master/targets/arm/mikroe/stm32/src/gpio/hal_ll_gpio.c Link to source @endlink.
 */
#if defined(FLATTEN_ME) && (FLATTEN_ME_LEVEL >= FLATTEN_ME_LEVEL_LOW)
#define hal_ll_gpio_read_pin_input(_handle) ((((hal_ll_gpio_base_handle_t *)((hal_ll_gpio_pin_t *)_handle)->base) == 0) ? \
                                             (0) : (((hal_ll_gpio_base_handle_t *)((hal_ll_gpio_pin_t *)_handle)->base)->idr & ((hal_ll_gpio_pin_t *)_handle)->mask) ? \
                                             (1) : (0))
#else
uint8_t hal_ll_gpio_read_pin_input(hal_ll_gpio_pin_t *pin);
#endif

/**
 * @brief Reads the output state of a GPIO pin.
 *
 * @details
 * This function reads the current logical level set on the specified GPIO pin's output data register.
 * It returns 1 if the pin output is high, or 0 if it is low.
 *
 * @param[in] pin Pointer to the GPIO pin structure to read from.
 * See @ref hal_ll_gpio_pin_t structure definition for more details.
 *
 * @return
 * - 1 if the pin output is high.
 * - 0 if the pin output is low or if the pin base is NULL.
 *
 * @note
 * - The function reads the output data register (ODR) of the GPIO port.
 * - If the pin base is NULL, the function returns 0.
 *
 * @pre
 * - The pin must be configured as output or capable of reading output state.
 *
 * @post
 * - No side effects.
 *
 * @warning
 * - Reading from an uninitialized pin may yield undefined results.
 *
 * @par Example Usage
 * @code{.c}
 *    // GPIO low level structure. *    hal_ll_gpio_pin_t pin; * *    // GPIO value holder. *    hal_port_size_t read_value; * *    // Read the output state of the pin. *    read_value = hal_ll_gpio_read_pin_output( &pin );
 * @endcode
 *
 * @par Limitations
 * - Does not reflect actual pin voltage if hardware overrides output.
 *
 * @see hal_ll_gpio_pin_t
 *
 * @link https://github.com/MikroElektronika/mikrosdk_v2/blob/master/targets/arm/mikroe/stm32/include/gpio/hal_ll_gpio.h#L190 Link to header @endlink.
 * @link https://github.com/MikroElektronika/mikrosdk_v2/blob/master/targets/arm/mikroe/stm32/src/gpio/hal_ll_gpio.c Link to source @endlink.
 */
#if defined(FLATTEN_ME) && (FLATTEN_ME_LEVEL >= FLATTEN_ME_LEVEL_LOW)
#define hal_ll_gpio_read_pin_output(_handle) ((((hal_ll_gpio_base_handle_t *)((hal_ll_gpio_pin_t *)_handle)->base) == 0) ? \
                                              (0) : (((hal_ll_gpio_base_handle_t *)((hal_ll_gpio_pin_t *)_handle)->base)->odr & ((hal_ll_gpio_pin_t *)_handle)->mask) ? \
                                              (1) : (0))
#else
uint8_t hal_ll_gpio_read_pin_output(hal_ll_gpio_pin_t *pin);
#endif

/**
 * @brief Writes a logical value to a GPIO pin output.
 *
 * @details
 * This function sets or clears the output state of the specified GPIO pin by writing to the port's bit set/reset register.
 * A non-zero value sets the pin output high; zero clears it low.
 *
 * @param[in,out] pin Pointer to the GPIO pin structure to write to.
 * See @ref hal_ll_gpio_pin_t structure definition for more details.
 * @param[in] value Logical value to write to the pin output (0 or non-zero).
 *
 * @return
 * - None.
 *
 * @note
 * - The function uses the bit set/reset register (BSRR) for atomic pin state changes.
 * - If the pin base is NULL, no operation is performed.
 *
 * @pre
 * - The pin must be configured as output.
 *
 * @post
 * - The pin output state is updated accordingly.
 *
 * @warning
 * - Writing to an input-configured pin may have no effect or cause undefined behavior.
 *
 * @par Example Usage
 * @code{.c}
 *    // GPIO low level structure. *    hal_ll_gpio_pin_t pin; * *    // Set pin logic state to high (1). *    hal_ll_gpio_write_pin_output( &pin, 1 );
 * @endcode
 *
 * @par Limitations
 * - Does not support analog or alternate function pins.
 *
 * @see hal_ll_gpio_pin_t
 *
 * @link https://github.com/MikroElektronika/mikrosdk_v2/blob/master/targets/arm/mikroe/stm32/include/gpio/hal_ll_gpio.h#L238 Link to header @endlink.
 * @link https://github.com/MikroElektronika/mikrosdk_v2/blob/master/targets/arm/mikroe/stm32/src/gpio/hal_ll_gpio.c Link to source @endlink.
 */
#if defined(FLATTEN_ME) && (FLATTEN_ME_LEVEL >= FLATTEN_ME_LEVEL_LOW)
#define hal_ll_gpio_write_pin_output(_handle,_value) ((((hal_ll_gpio_base_handle_t *)((hal_ll_gpio_pin_t *)_handle)->base) != NULL) ? \
                                                          ((_value > 0) ? \
                                                           (((hal_ll_gpio_base_handle_t *)((hal_ll_gpio_pin_t *)_handle)->base)->bsrr = ((hal_ll_gpio_pin_t *)_handle)->mask) : \
                                                           (((hal_ll_gpio_base_handle_t *)((hal_ll_gpio_pin_t *)_handle)->base)->bsrr = ((uint32_t)((hal_ll_gpio_pin_t *)_handle)->mask << RESET_PINS_OFFSET))) : \
                                                      (0))
#else
void hal_ll_gpio_write_pin_output(hal_ll_gpio_pin_t *pin, uint8_t value);
#endif

/**
 * @brief Toggles the output state of a GPIO pin.
 *
 * @details
 * This function inverts the current output state of the specified GPIO pin.
 * If the pin output is high, it will be set low; if low, it will be set high.
 *
 * @param[in,out] pin Pointer to the GPIO pin structure to toggle.
 * See @ref hal_ll_gpio_pin_t structure definition for more details.
 *
 * @return
 * - None.
 *
 * @note
 * - The function reads the current output state and writes the opposite state.
 * - If the pin base is NULL, no operation is performed.
 *
 * @pre
 * - The pin must be configured as output.
 *
 * @post
 * - The pin output state is toggled.
 *
 * @warning
 * - Toggling an input-configured pin may have no effect or cause undefined behavior.
 *
 * @par Example Usage
 * @code{.c}
 *    // GPIO low level structure. *    hal_ll_gpio_pin_t pin; * *    // Toggle pin logic state. *    hal_ll_gpio_toggle_pin_output( &pin );
 * @endcode
 *
 * @par Limitations
 * - Does not support atomic toggle on hardware without BSRR register.
 *
 * @see hal_ll_gpio_pin_t
 *
 * @link https://github.com/MikroElektronika/mikrosdk_v2/blob/master/targets/arm/mikroe/stm32/include/gpio/hal_ll_gpio.h#L287 Link to header @endlink.
 * @link https://github.com/MikroElektronika/mikrosdk_v2/blob/master/targets/arm/mikroe/stm32/src/gpio/hal_ll_gpio.c Link to source @endlink.
 */
#if defined(FLATTEN_ME) && (FLATTEN_ME_LEVEL >= FLATTEN_ME_LEVEL_LOW)
#define hal_ll_gpio_toggle_pin_output(_handle) ((((hal_ll_gpio_base_handle_t *)((hal_ll_gpio_pin_t *)_handle)->base) != NULL) ? \
                                                    ((((((hal_ll_gpio_base_handle_t *)((hal_ll_gpio_pin_t *)_handle)->base)->odr & ((hal_ll_gpio_pin_t *)_handle)->mask))) ? \
                                                     (((hal_ll_gpio_base_handle_t *)((hal_ll_gpio_pin_t *)_handle)->base)->bsrr = ((uint32_t)((hal_ll_gpio_pin_t *)_handle)->mask << RESET_PINS_OFFSET)) : \
                                                     (((hal_ll_gpio_base_handle_t *)((hal_ll_gpio_pin_t *)_handle)->base)->bsrr = ((hal_ll_gpio_pin_t *)_handle)->mask)) : \
                                                (0))
#else
void hal_ll_gpio_toggle_pin_output(hal_ll_gpio_pin_t *pin);
#endif

/**
 * @brief Sets the output state of a GPIO pin to high.
 *
 * @details
 * This function sets the specified GPIO pin output to a logical high level by writing to the port's bit set/reset register.
 *
 * @param[in,out] pin Pointer to the GPIO pin structure to set.
 * See @ref hal_ll_gpio_pin_t structure definition for more details.
 *
 * @return
 * - None.
 *
 * @note
 * - The function uses the bit set/reset register (BSRR) for atomic pin set operation.
 * - If the pin base is NULL, no operation is performed.
 *
 * @pre
 * - The pin must be configured as output.
 *
 * @post
 * - The pin output is set to high.
 *
 * @warning
 * - Setting an input-configured pin may have no effect or cause undefined behavior.
 *
 * @par Example Usage
 * @code{.c}
 *    // GPIO low level structure. *    hal_ll_gpio_pin_t pin; * *    // Set pin logical state to high. *    hal_ll_gpio_set_pin_output( &pin );
 * @endcode
 *
 * @par Limitations
 * - Does not support analog or alternate function pins.
 *
 * @see hal_ll_gpio_pin_t
 *
 * @link https://github.com/MikroElektronika/mikrosdk_v2/blob/master/targets/arm/mikroe/stm32/include/gpio/hal_ll_gpio.h#L335 Link to header @endlink.
 * @link https://github.com/MikroElektronika/mikrosdk_v2/blob/master/targets/arm/mikroe/stm32/src/gpio/hal_ll_gpio.c Link to source @endlink.
 */
#if defined(FLATTEN_ME) && (FLATTEN_ME_LEVEL >= FLATTEN_ME_LEVEL_LOW)
#define hal_ll_gpio_set_pin_output(_handle) ((((hal_ll_gpio_base_handle_t *)((hal_ll_gpio_pin_t *)_handle)->base) != NULL) ? \
                                             (((hal_ll_gpio_base_handle_t *)((hal_ll_gpio_pin_t *)_handle)->base)->bsrr = ((hal_ll_gpio_pin_t *)_handle)->mask) : \
                                             (0))
#else
void hal_ll_gpio_set_pin_output(hal_ll_gpio_pin_t *pin);
#endif

/**
 * @brief Clears the output state of a GPIO pin to low.
 *
 * @details
 * This function sets the specified GPIO pin output to a logical low level by writing to the port's bit set/reset register.
 *
 * @param[in,out] pin Pointer to the GPIO pin structure to clear.
 * See @ref hal_ll_gpio_pin_t structure definition for more details.
 *
 * @return
 * - None.
 *
 * @note
 * - The function uses the bit set/reset register (BSRR) for atomic pin clear operation.
 * - If the pin base is NULL, no operation is performed.
 *
 * @pre
 * - The pin must be configured as output.
 *
 * @post
 * - The pin output is set to low.
 *
 * @warning
 * - Clearing an input-configured pin may have no effect or cause undefined behavior.
 *
 * @par Example Usage
 * @code{.c}
 *    // GPIO low level structure. *    hal_ll_gpio_pin_t pin; * *    // Set pin logical state to low. *    hal_ll_gpio_clear_pin_output( &pin );
 * @endcode
 *
 * @par Limitations
 * - Does not support analog or alternate function pins.
 *
 * @see hal_ll_gpio_pin_t
 *
 * @link https://github.com/MikroElektronika/mikrosdk_v2/blob/master/targets/arm/mikroe/stm32/include/gpio/hal_ll_gpio.h#L381 Link to header @endlink.
 * @link https://github.com/MikroElektronika/mikrosdk_v2/blob/master/targets/arm/mikroe/stm32/src/gpio/hal_ll_gpio.c Link to source @endlink.
 */
#if defined(FLATTEN_ME) && (FLATTEN_ME_LEVEL >= FLATTEN_ME_LEVEL_LOW)
#define hal_ll_gpio_clear_pin_output(_handle) ((((hal_ll_gpio_base_handle_t *)((hal_ll_gpio_pin_t *)_handle)->base) != NULL) ? \
                                               (((hal_ll_gpio_base_handle_t *)((hal_ll_gpio_pin_t *)_handle)->base)->bsrr = ((uint32_t)((hal_ll_gpio_pin_t *)_handle)->mask << RESET_PINS_OFFSET)) : \
                                               (0))
#else
void hal_ll_gpio_clear_pin_output(hal_ll_gpio_pin_t *pin);
#endif

/**
 * @brief Configures a GPIO port with specified parameters.
 *
 * @details
 * This function initializes a GPIO port by setting its base address, mask, and direction.
 * It configures the port pins specified by the mask as either digital input or digital output.
 *
 * @param[out] port Pointer to the GPIO port structure to be configured.
 * See @ref hal_ll_gpio_port_t structure definition for more details.
 * @param[in] name The port name identifier used to determine port base.
 * See @ref hal_ll_port_name_t type for valid port names.
 * @param[in] mask Bitmask specifying which pins of the port to configure.
 * See @ref hal_ll_gpio_mask_t type for mask details.
 * @param[in] direction The direction to configure the port pins for (input or output).
 * See @ref hal_ll_gpio_direction_t enumeration for possible directions.
 *
 * @return
 * - None.
 *
 * @note
 * - The function assumes the port name is valid and corresponds to a valid GPIO port.
 * - The port structure is updated with base address and mask for further operations.
 *
 * @pre
 * - The GPIO port base must be accessible.
 *
 * @post
 * - The specified pins of the port are configured as digital input or output.
 *
 * @warning
 * - Calling this function with invalid port names or masks may cause undefined behavior.
 *
 * @par Example Usage
 * @code{.c}
 *    // GPIO low level structure. *    hal_ll_gpio_port_t port; * *    // Initialize port as output. *    hal_ll_gpio_configure_port( &port, PORTB, 0xFF, HAL_LL_GPIO_DIGITAL_OUTPUT );
 * @endcode
 *
 * @par Limitations
 * - Does not configure alternate functions or pull-up/down resistors.
 *
 * @see hal_ll_gpio_port_t
 * @see hal_ll_port_name_t
 * @see hal_ll_gpio_mask_t
 * @see hal_ll_gpio_direction_t
 *
 * @link https://github.com/MikroElektronika/mikrosdk_v2/blob/master/targets/arm/mikroe/stm32/include/gpio/hal_ll_gpio.h#L435 Link to header @endlink.
 * @link https://github.com/MikroElektronika/mikrosdk_v2/blob/master/targets/arm/mikroe/stm32/src/gpio/hal_ll_gpio.c#L133 Link to source @endlink.
 */
void hal_ll_gpio_configure_port(hal_ll_gpio_port_t *port, hal_ll_port_name_t name, hal_ll_gpio_mask_t mask, hal_ll_gpio_direction_t direction);

/**
 * @brief Reads the input state of a GPIO port.
 *
 * @details
 * This function reads the current logical levels present on the specified GPIO port's input data register,
 * masked by the port's configured mask. It returns the masked input values.
 *
 * @param[in] port Pointer to the GPIO port structure to read from.
 * See @ref hal_ll_gpio_port_t structure definition for more details.
 *
 * @return
 * - Masked input values of the port pins as @ref hal_ll_port_size_t.
 * - Returns 0 if the port base is NULL.
 *
 * @note
 * - The function reads the input data register (IDR) of the GPIO port.
 * - Only pins specified by the mask are returned.
 *
 * @pre
 * - The port must be configured as input or capable of reading input state.
 *
 * @post
 * - No side effects.
 *
 * @warning
 * - Reading from an uninitialized port may yield undefined results.
 *
 * @par Example Usage
 * @code{.c}
 *    // GPIO low level structure. *    hal_ll_gpio_port_t port; * *    // GPIO value holder. *    hal_port_size_t read_value; * *    // Read the input state of the port. *    read_value = hal_ll_gpio_read_port_input( &port );
 * @endcode
 *
 * @par Limitations
 * - Does not debounce or filter input signals.
 *
 * @see hal_ll_gpio_port_t
 *
 * @link https://github.com/MikroElektronika/mikrosdk_v2/blob/master/targets/arm/mikroe/stm32/include/gpio/hal_ll_gpio.h#L479 Link to header @endlink.
 * @link https://github.com/MikroElektronika/mikrosdk_v2/blob/master/targets/arm/mikroe/stm32/src/gpio/hal_ll_gpio.c Link to source @endlink.
 */
#if defined(FLATTEN_ME) && (FLATTEN_ME_LEVEL >= FLATTEN_ME_LEVEL_LOW)
#define hal_ll_gpio_read_port_input(_handle) ((((hal_ll_gpio_base_handle_t *)((hal_ll_gpio_port_t *)_handle)->base) != NULL) ? \
                                              ((hal_ll_port_size_t)((hal_ll_gpio_base_handle_t *)((hal_ll_gpio_port_t *)_handle)->base)->idr & ((hal_ll_gpio_port_t *)_handle)->mask) : \
                                              (0))
#else
hal_ll_port_size_t hal_ll_gpio_read_port_input(hal_ll_gpio_port_t *port);
#endif

/**
 * @brief Reads the output state of a GPIO port.
 *
 * @details
 * This function reads the current logical levels set on the specified GPIO port's output data register,
 * masked by the port's configured mask. It returns the masked output values.
 *
 * @param[in] port Pointer to the GPIO port structure to read from.
 * See @ref hal_ll_gpio_port_t structure definition for more details.
 *
 * @return
 * - Masked output values of the port pins as @ref hal_ll_port_size_t.
 * - Returns 0 if the port base is NULL.
 *
 * @note
 * - The function reads the output data register (ODR) of the GPIO port.
 * - Only pins specified by the mask are returned.
 *
 * @pre
 * - The port must be configured as output or capable of reading output state.
 *
 * @post
 * - No side effects.
 *
 * @warning
 * - Reading from an uninitialized port may yield undefined results.
 *
 * @par Example Usage
 * @code{.c}
 *    // GPIO low level structure. *    hal_ll_gpio_port_t port; * *    // GPIO value holder. *    hal_port_size_t read_value; * *    // Read the output state of the port. *    read_value = hal_ll_gpio_read_port_output( &port );
 * @endcode
 *
 * @par Limitations
 * - Does not reflect actual pin voltage if hardware overrides output.
 *
 * @see hal_ll_gpio_port_t
 *
 * @link https://github.com/MikroElektronika/mikrosdk_v2/blob/master/targets/arm/mikroe/stm32/include/gpio/hal_ll_gpio.h#L527 Link to header @endlink.
 * @link https://github.com/MikroElektronika/mikrosdk_v2/blob/master/targets/arm/mikroe/stm32/src/gpio/hal_ll_gpio.c Link to source @endlink.
 */
#if defined(FLATTEN_ME) && (FLATTEN_ME_LEVEL >= FLATTEN_ME_LEVEL_LOW)
#define hal_ll_gpio_read_port_output(_handle) ((((hal_ll_gpio_base_handle_t *)((hal_ll_gpio_port_t *)_handle)->base) != NULL) ? \
                                               ((hal_ll_port_size_t)(((hal_ll_gpio_base_handle_t *)((hal_ll_gpio_port_t *)_handle)->base)->odr) & (((hal_ll_gpio_port_t *)_handle)->mask)) : \
                                               (0))
#else
hal_ll_port_size_t hal_ll_gpio_read_port_output(hal_ll_gpio_port_t *port);
#endif

/**
 * @brief Writes logical values to a GPIO port output.
 *
 * @details
 * This function sets or clears the output state of the specified GPIO port pins by writing to the port's bit set/reset register.
 * The value parameter specifies which pins to set high or low, masked by the port's configured mask.
 *
 * @param[in,out] port Pointer to the GPIO port structure to write to.
 * See @ref hal_ll_gpio_port_t structure definition for more details.
 * @param[in] value Logical values to write to the port pins as @ref hal_ll_port_size_t.
 *
 * @return
 * - None.
 *
 * @note
 * - The function uses the bit set/reset register (BSRR) for atomic port pin state changes.
 * - If the port base is NULL, no operation is performed.
 *
 * @pre
 * - The port must be configured as output.
 *
 * @post
 * - The port pins output states are updated accordingly.
 *
 * @warning
 * - Writing to an input-configured port may have no effect or cause undefined behavior.
 *
 * @par Example Usage
 * @code{.c}
 *    // GPIO low level structure. *    hal_ll_gpio_port_t port; * *    // Set port logic state to 0xAA. *    hal_ll_gpio_write_port_output( &port, 0xAA );
 * @endcode
 *
 * @par Limitations
 * - Does not support analog or alternate function pins.
 *
 * @see hal_ll_gpio_port_t
 *
 * @link https://github.com/MikroElektronika/mikrosdk_v2/blob/master/targets/arm/mikroe/stm32/include/gpio/hal_ll_gpio.h#L575 Link to header @endlink.
 * @link https://github.com/MikroElektronika/mikrosdk_v2/blob/master/targets/arm/mikroe/stm32/src/gpio/hal_ll_gpio.c Link to source @endlink.
 */
#if defined(FLATTEN_ME) && (FLATTEN_ME_LEVEL >= FLATTEN_ME_LEVEL_LOW)
#define hal_ll_gpio_write_port_output(_handle,_value) ((((hal_ll_gpio_base_handle_t *)((hal_ll_gpio_port_t *)_handle)->base) != NULL) ? \
                                                          (((hal_ll_gpio_base_handle_t *)((hal_ll_gpio_port_t *)_handle)->base)->bsrr = \
                                                           ((hal_ll_port_size_t)_value & ((hal_ll_gpio_port_t *)_handle)->mask) | \
                                                           ((uint32_t)(~(hal_ll_port_size_t)_value & ((hal_ll_gpio_port_t *)_handle)->mask) << RESET_PINS_OFFSET)) : \
                                                       (0))
#else
void hal_ll_gpio_write_port_output(hal_ll_gpio_port_t *port, hal_ll_port_size_t value);
#endif

#ifdef __cplusplus
}
#endif

#endif // _HAL_LL_GPIO_H_
// ------------------------------------------------------------------------- END
