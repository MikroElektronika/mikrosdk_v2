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
 * This function initializes a GPIO pin structure with the base address and mask
 * corresponding to the specified pin name. It then configures the pin direction
 * as either digital input or digital output.
 *
 * @param[out] pin Pointer to the GPIO pin structure to be configured.
 * See @ref hal_ll_gpio_pin_t structure definition for more details.
 * @param[in] name The identifier of the pin to configure.
 * See @ref hal_ll_pin_name_t type for valid pin names.
 * @param[in] direction Direction to set for the pin (input or output).
 * See @ref hal_ll_gpio_direction_t enumeration for possible directions.
 *
 * @return
 * - None.
 *
 * @note
 * - The pin structure must be valid and allocated before calling this function.
 * - The function sets the pin base and mask internally based on the pin name.
 *
 * @pre
 * - The hardware GPIO port must be properly initialized.
 *
 * @post
 * - The pin is configured with the specified direction.
 *
 * @warning
 * - Passing an invalid pin name may result in undefined behavior.
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
 * @link https://github.com/MikroElektronika/mikrosdk_v2/blob/master/targets/arm/mikroe/nxp/include/gpio/hal_ll_gpio.h#L99 Link to header @endlink.
 * @link https://github.com/MikroElektronika/mikrosdk_v2/blob/master/targets/arm/mikroe/nxp/src/gpio/hal_ll_gpio.c#L49 Link to source @endlink.
 */
void hal_ll_gpio_configure_pin(hal_ll_gpio_pin_t *pin, hal_ll_pin_name_t name, hal_ll_gpio_direction_t direction);

/**
 * @brief Reads the input state of a GPIO pin.
 *
 * @details
 * This function returns the current logical level present on the specified GPIO pin's input register.
 * It reads the pin input data register and masks the relevant bit corresponding to the pin.
 *
 * @param[in] pin Pointer to the GPIO pin structure to read from.
 * See @ref hal_ll_gpio_pin_t structure definition for more details.
 *
 * @return
 * - 1 if the pin input is high.
 * - 0 if the pin input is low or if the pin base is NULL.
 *
 * @note
 * - The pin must be configured as input to get meaningful results.
 *
 * @pre
 * - The pin must be properly configured and initialized.
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
 * - Only returns binary logic level (0 or 1).
 *
 * @see hal_ll_gpio_configure_pin()
 *
 * @link https://github.com/MikroElektronika/mikrosdk_v2/blob/master/targets/arm/mikroe/nxp/include/gpio/hal_ll_gpio.h#L142 Link to header @endlink.
 * @link https://github.com/MikroElektronika/mikrosdk_v2/blob/master/targets/arm/mikroe/nxp/src/gpio/hal_ll_gpio.c Link to source @endlink.
 */
#if defined(FLATTEN_ME) && (FLATTEN_ME_LEVEL >= FLATTEN_ME_LEVEL_LOW)
#define hal_ll_gpio_read_pin_input(_handle) ((((hal_ll_gpio_base_handle_t *)((hal_ll_gpio_pin_t *)_handle)->base) == 0) ? \
                                             (0) : (((hal_ll_gpio_base_handle_t *)((hal_ll_gpio_pin_t *)_handle)->base)->pdir & ((hal_ll_gpio_pin_t *)_handle)->mask) ? \
                                             (1) : (0))
#else
uint8_t hal_ll_gpio_read_pin_input(hal_ll_gpio_pin_t *pin);
#endif

/**
 * @brief Reads the output state of a GPIO pin.
 *
 * @details
 * This function returns the current logical level set on the specified GPIO pin's output register.
 * It reads the pin output data register and masks the relevant bit corresponding to the pin.
 *
 * @param[in] pin Pointer to the GPIO pin structure to read from.
 * See @ref hal_ll_gpio_pin_t structure definition for more details.
 *
 * @return
 * - 1 if the pin output is set high.
 * - 0 if the pin output is set low or if the pin base is NULL.
 *
 * @note
 * - The pin must be configured as output to get meaningful results.
 *
 * @pre
 * - The pin must be properly configured and initialized.
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
 * - Only returns binary logic level (0 or 1).
 *
 * @see hal_ll_gpio_configure_pin()
 *
 * @link https://github.com/MikroElektronika/mikrosdk_v2/blob/master/targets/arm/mikroe/nxp/include/gpio/hal_ll_gpio.h#L189 Link to header @endlink.
 * @link https://github.com/MikroElektronika/mikrosdk_v2/blob/master/targets/arm/mikroe/nxp/src/gpio/hal_ll_gpio.c Link to source @endlink.
 */
#if defined(FLATTEN_ME) && (FLATTEN_ME_LEVEL >= FLATTEN_ME_LEVEL_LOW)
#define hal_ll_gpio_read_pin_output(_handle) ((((hal_ll_gpio_base_handle_t *)((hal_ll_gpio_pin_t *)_handle)->base) == 0) ? \
                                              (0) : (((hal_ll_gpio_base_handle_t *)((hal_ll_gpio_pin_t *)_handle)->base)->pdor & ((hal_ll_gpio_pin_t *)_handle)->mask) ? \
                                              (1) : (0))
#else
uint8_t hal_ll_gpio_read_pin_output(hal_ll_gpio_pin_t *pin);
#endif

/**
 * @brief Writes a logical value to a GPIO pin output.
 *
 * @details
 * This function sets or clears the output state of the specified GPIO pin.
 * If the value is non-zero, the pin output is set high; otherwise, it is set low.
 *
 * @param[in,out] pin Pointer to the GPIO pin structure to write to.
 * See @ref hal_ll_gpio_pin_t structure definition for more details.
 * @param[in] value Logical value to write to the pin output (0 or non-zero).
 *
 * @return
 * - None.
 *
 * @note
 * - The pin must be configured as output before calling this function.
 *
 * @pre
 * - The pin must be properly configured and initialized.
 *
 * @post
 * - The pin output state is updated accordingly.
 *
 * @warning
 * - Writing to an input-configured pin may have no effect.
 *
 * @par Example Usage
 * @code{.c}
 *    // GPIO low level structure. *    hal_ll_gpio_pin_t pin; * *    // Set pin logic state to high (1). *    hal_ll_gpio_write_pin_output( &pin, 1 );
 * @endcode
 *
 * @par Limitations
 * - Only supports binary output values.
 *
 * @see hal_ll_gpio_configure_pin()
 *
 * @link https://github.com/MikroElektronika/mikrosdk_v2/blob/master/targets/arm/mikroe/nxp/include/gpio/hal_ll_gpio.h#L236 Link to header @endlink.
 * @link https://github.com/MikroElektronika/mikrosdk_v2/blob/master/targets/arm/mikroe/nxp/src/gpio/hal_ll_gpio.c Link to source @endlink.
 */
#if defined(FLATTEN_ME) && (FLATTEN_ME_LEVEL >= FLATTEN_ME_LEVEL_LOW)
#define hal_ll_gpio_write_pin_output(_handle,_value) ((((hal_ll_gpio_base_handle_t *)((hal_ll_gpio_pin_t *)_handle)->base) != NULL) ? \
                                                          ((_value > 0) ? \
                                                           (((hal_ll_gpio_base_handle_t *)((hal_ll_gpio_pin_t *)_handle)->base)->psor = ((hal_ll_gpio_pin_t *)_handle)->mask) : \
                                                           (((hal_ll_gpio_base_handle_t *)((hal_ll_gpio_pin_t *)_handle)->base)->pcor = ((hal_ll_gpio_pin_t *)_handle)->mask)) : \
                                                      (0))
#else
void hal_ll_gpio_write_pin_output(hal_ll_gpio_pin_t *pin, uint8_t value);
#endif

/**
 * @brief Toggles the output state of a GPIO pin.
 *
 * @details
 * This function inverts the current output state of the specified GPIO pin.
 * If the pin output is high, it will be set low, and vice versa.
 *
 * @param[in,out] pin Pointer to the GPIO pin structure to toggle.
 * See @ref hal_ll_gpio_pin_t structure definition for more details.
 *
 * @return
 * - None.
 *
 * @note
 * - The pin must be configured as output before calling this function.
 *
 * @pre
 * - The pin must be properly configured and initialized.
 *
 * @post
 * - The pin output state is toggled.
 *
 * @warning
 * - Toggling an input-configured pin may have no effect.
 *
 * @par Example Usage
 * @code{.c}
 *    // GPIO low level structure. *    hal_ll_gpio_pin_t pin; * *    // Toggle pin logic state. *    hal_ll_gpio_toggle_pin_output( &pin );
 * @endcode
 *
 * @par Limitations
 * - Only supports toggling binary output states.
 *
 * @see hal_ll_gpio_configure_pin()
 *
 * @link https://github.com/MikroElektronika/mikrosdk_v2/blob/master/targets/arm/mikroe/nxp/include/gpio/hal_ll_gpio.h#L284 Link to header @endlink.
 * @link https://github.com/MikroElektronika/mikrosdk_v2/blob/master/targets/arm/mikroe/nxp/src/gpio/hal_ll_gpio.c Link to source @endlink.
 */
#if defined(FLATTEN_ME) && (FLATTEN_ME_LEVEL >= FLATTEN_ME_LEVEL_LOW)
#define hal_ll_gpio_toggle_pin_output(_handle) ((((hal_ll_gpio_base_handle_t *)((hal_ll_gpio_pin_t *)_handle)->base) != NULL) ? \
                                                (((hal_ll_gpio_base_handle_t *)((hal_ll_gpio_pin_t *)_handle)->base)->ptor = ((hal_ll_gpio_pin_t *)_handle)->mask) : \
                                                (0))
#else
void hal_ll_gpio_toggle_pin_output(hal_ll_gpio_pin_t *pin);
#endif

/**
 * @brief Sets the output state of a GPIO pin to high.
 *
 * @details
 * This function sets the output register bit corresponding to the specified GPIO pin,
 * driving the pin output to a logical high level.
 *
 * @param[in,out] pin Pointer to the GPIO pin structure to set.
 * See @ref hal_ll_gpio_pin_t structure definition for more details.
 *
 * @return
 * - None.
 *
 * @note
 * - The pin must be configured as output before calling this function.
 *
 * @pre
 * - The pin must be properly configured and initialized.
 *
 * @post
 * - The pin output is set to high.
 *
 * @warning
 * - Setting an input-configured pin may have no effect.
 *
 * @par Example Usage
 * @code{.c}
 *    // GPIO low level structure. *    hal_ll_gpio_pin_t pin; * *    // Set pin logical state to high. *    hal_ll_gpio_set_pin_output( &pin );
 * @endcode
 *
 * @par Limitations
 * - Only supports setting binary output states.
 *
 * @see hal_ll_gpio_configure_pin()
 *
 * @link https://github.com/MikroElektronika/mikrosdk_v2/blob/master/targets/arm/mikroe/nxp/include/gpio/hal_ll_gpio.h#L330 Link to header @endlink.
 * @link https://github.com/MikroElektronika/mikrosdk_v2/blob/master/targets/arm/mikroe/nxp/src/gpio/hal_ll_gpio.c Link to source @endlink.
 */
#if defined(FLATTEN_ME) && (FLATTEN_ME_LEVEL >= FLATTEN_ME_LEVEL_LOW)
#define hal_ll_gpio_set_pin_output(_handle) ((((hal_ll_gpio_base_handle_t *)((hal_ll_gpio_pin_t *)_handle)->base) != NULL) ? \
                                             (((hal_ll_gpio_base_handle_t *)((hal_ll_gpio_pin_t *)_handle)->base)->psor = ((hal_ll_gpio_pin_t *)_handle)->mask) : \
                                             (0))
#else
void hal_ll_gpio_set_pin_output(hal_ll_gpio_pin_t *pin);
#endif

/**
 * @brief Clears the output state of a GPIO pin to low.
 *
 * @details
 * This function clears the output register bit corresponding to the specified GPIO pin,
 * driving the pin output to a logical low level.
 *
 * @param[in,out] pin Pointer to the GPIO pin structure to clear.
 * See @ref hal_ll_gpio_pin_t structure definition for more details.
 *
 * @return
 * - None.
 *
 * @note
 * - The pin must be configured as output before calling this function.
 *
 * @pre
 * - The pin must be properly configured and initialized.
 *
 * @post
 * - The pin output is set to low.
 *
 * @warning
 * - Clearing an input-configured pin may have no effect.
 *
 * @par Example Usage
 * @code{.c}
 *    // GPIO low level structure. *    hal_ll_gpio_pin_t pin; * *    // Set pin logical state to low. *    hal_ll_gpio_clear_pin_output( &pin );
 * @endcode
 *
 * @par Limitations
 * - Only supports clearing binary output states.
 *
 * @see hal_ll_gpio_configure_pin()
 *
 * @link https://github.com/MikroElektronika/mikrosdk_v2/blob/master/targets/arm/mikroe/nxp/include/gpio/hal_ll_gpio.h#L376 Link to header @endlink.
 * @link https://github.com/MikroElektronika/mikrosdk_v2/blob/master/targets/arm/mikroe/nxp/src/gpio/hal_ll_gpio.c Link to source @endlink.
 */
#if defined(FLATTEN_ME) && (FLATTEN_ME_LEVEL >= FLATTEN_ME_LEVEL_LOW)
#define hal_ll_gpio_clear_pin_output(_handle) ((((hal_ll_gpio_base_handle_t *)((hal_ll_gpio_pin_t *)_handle)->base) != NULL) ? \
                                               (((hal_ll_gpio_base_handle_t *)((hal_ll_gpio_pin_t *)_handle)->base)->pcor = ((uint32_t)((hal_ll_gpio_pin_t *)_handle)->mask)) : \
                                               (0))
#else
void hal_ll_gpio_clear_pin_output(hal_ll_gpio_pin_t *pin);
#endif

/**
 * @brief Configures a GPIO port with specified parameters.
 *
 * @details
 * This function initializes a GPIO port structure with the base address and mask
 * corresponding to the specified port name and mask. It then configures the port direction
 * as either digital input or digital output for the masked pins.
 *
 * @param[out] port Pointer to the GPIO port structure to be configured.
 * See @ref hal_ll_gpio_port_t structure definition for more details.
 * @param[in] name The identifier of the port to configure.
 * See @ref hal_ll_port_name_t type for valid port names.
 * @param[in] mask Bitmask specifying which pins in the port to configure.
 * See @ref hal_ll_gpio_mask_t type for mask details.
 * @param[in] direction Direction to set for the port pins (input or output).
 * See @ref hal_ll_gpio_direction_t enumeration for possible directions.
 *
 * @return
 * - None.
 *
 * @note
 * - The port structure must be valid and allocated before calling this function.
 * - Only pins specified in the mask are configured.
 *
 * @pre
 * - The hardware GPIO port must be properly initialized.
 *
 * @post
 * - The port pins specified by the mask are configured with the specified direction.
 *
 * @warning
 * - Passing an invalid port name or mask may result in undefined behavior.
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
 * @link https://github.com/MikroElektronika/mikrosdk_v2/blob/master/targets/arm/mikroe/nxp/include/gpio/hal_ll_gpio.h#L431 Link to header @endlink.
 * @link https://github.com/MikroElektronika/mikrosdk_v2/blob/master/targets/arm/mikroe/nxp/src/gpio/hal_ll_gpio.c#L134 Link to source @endlink.
 */
void hal_ll_gpio_configure_port(hal_ll_gpio_port_t *port, hal_ll_port_name_t name, hal_ll_gpio_mask_t mask, hal_ll_gpio_direction_t direction);

/**
 * @brief Reads the input state of a GPIO port.
 *
 * @details
 * This function returns the current logical levels present on the specified GPIO port's input register,
 * masked by the port's mask to only include relevant pins.
 *
 * @param[in] port Pointer to the GPIO port structure to read from.
 * See @ref hal_ll_gpio_port_t structure definition for more details.
 *
 * @return
 * - Bitmask representing the input states of the masked pins.
 * - 0 if the port base is NULL.
 *
 * @note
 * - The port pins must be configured as input to get meaningful results.
 *
 * @pre
 * - The port must be properly configured and initialized.
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
 * - Only returns binary logic levels for masked pins.
 *
 * @see hal_ll_gpio_configure_port()
 *
 * @link https://github.com/MikroElektronika/mikrosdk_v2/blob/master/targets/arm/mikroe/nxp/include/gpio/hal_ll_gpio.h#L474 Link to header @endlink.
 * @link https://github.com/MikroElektronika/mikrosdk_v2/blob/master/targets/arm/mikroe/nxp/src/gpio/hal_ll_gpio.c Link to source @endlink.
 */
#if defined(FLATTEN_ME) && (FLATTEN_ME_LEVEL >= FLATTEN_ME_LEVEL_LOW)
#define hal_ll_gpio_read_port_input(_handle) ((((hal_ll_gpio_base_handle_t *)((hal_ll_gpio_port_t *)_handle)->base) != NULL) ? \
                                              ((hal_ll_port_size_t)((hal_ll_gpio_base_handle_t *)((hal_ll_gpio_port_t *)_handle)->base)->pdir & ((hal_ll_gpio_port_t *)_handle)->mask) : \
                                              (0))
#else
hal_ll_port_size_t hal_ll_gpio_read_port_input(hal_ll_gpio_port_t *port);
#endif

/**
 * @brief Reads the output state of a GPIO port.
 *
 * @details
 * This function returns the current logical levels set on the specified GPIO port's output register,
 * masked by the port's mask to only include relevant pins.
 *
 * @param[in] port Pointer to the GPIO port structure to read from.
 * See @ref hal_ll_gpio_port_t structure definition for more details.
 *
 * @return
 * - Bitmask representing the output states of the masked pins.
 * - 0 if the port base is NULL.
 *
 * @note
 * - The port pins must be configured as output to get meaningful results.
 *
 * @pre
 * - The port must be properly configured and initialized.
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
 * - Only returns binary logic levels for masked pins.
 *
 * @see hal_ll_gpio_configure_port()
 *
 * @link https://github.com/MikroElektronika/mikrosdk_v2/blob/master/targets/arm/mikroe/nxp/include/gpio/hal_ll_gpio.h#L521 Link to header @endlink.
 * @link https://github.com/MikroElektronika/mikrosdk_v2/blob/master/targets/arm/mikroe/nxp/src/gpio/hal_ll_gpio.c Link to source @endlink.
 */
#if defined(FLATTEN_ME) && (FLATTEN_ME_LEVEL >= FLATTEN_ME_LEVEL_LOW)
#define hal_ll_gpio_read_port_output(_handle) ((((hal_ll_gpio_base_handle_t *)((hal_ll_gpio_port_t *)_handle)->base) != NULL) ? \
                                               ((hal_ll_port_size_t)(((hal_ll_gpio_base_handle_t *)((hal_ll_gpio_port_t *)_handle)->base)->pdor) & (((hal_ll_gpio_port_t *)_handle)->mask)) : \
                                               (0))
#else
hal_ll_port_size_t hal_ll_gpio_read_port_output(hal_ll_gpio_port_t *port);
#endif

/**
 * @brief Writes a logical value to a GPIO port output.
 *
 * @details
 * This function sets the output register bits corresponding to the specified GPIO port's masked pins.
 * It updates only the pins specified by the mask, preserving other pins' states.
 *
 * @param[in,out] port Pointer to the GPIO port structure to write to.
 * See @ref hal_ll_gpio_port_t structure definition for more details.
 * @param[in] value Bitmask representing the logical values to write to the port pins.
 *
 * @return
 * - None.
 *
 * @note
 * - The port pins must be configured as output before calling this function.
 *
 * @pre
 * - The port must be properly configured and initialized.
 *
 * @post
 * - The port output states are updated accordingly.
 *
 * @warning
 * - Writing to input-configured pins may have no effect.
 *
 * @par Example Usage
 * @code{.c}
 *    // GPIO low level structure. *    hal_ll_gpio_port_t port; * *    // Set port logic state to 0xAA. *    hal_ll_gpio_write_port_output( &port, 0xAA );
 * @endcode
 *
 * @par Limitations
 * - Only supports binary output values.
 *
 * @see hal_ll_gpio_configure_port()
 *
 * @link https://github.com/MikroElektronika/mikrosdk_v2/blob/master/targets/arm/mikroe/nxp/include/gpio/hal_ll_gpio.h#L568 Link to header @endlink.
 * @link https://github.com/MikroElektronika/mikrosdk_v2/blob/master/targets/arm/mikroe/nxp/src/gpio/hal_ll_gpio.c Link to source @endlink.
 */
#if defined(FLATTEN_ME) && (FLATTEN_ME_LEVEL >= FLATTEN_ME_LEVEL_LOW)
#define hal_ll_gpio_write_port_output(_handle,_value) ((((hal_ll_gpio_base_handle_t *)((hal_ll_gpio_port_t *)_handle)->base) != NULL) ? \
                                                          (((hal_ll_gpio_base_handle_t *)((hal_ll_gpio_port_t *)_handle)->base)->pdor = \
                                                           (((hal_ll_gpio_base_handle_t *)((hal_ll_gpio_port_t *)_handle)->base)->pdor & ~((hal_ll_gpio_port_t *)_handle)->mask) | \
                                                           ((uint32_t)((hal_ll_port_size_t)_value & ((hal_ll_gpio_port_t *)_handle)->mask))) : \
                                                       (0))
#else
void hal_ll_gpio_write_port_output(hal_ll_gpio_port_t *port, hal_ll_port_size_t value);
#endif

#ifdef __cplusplus
}
#endif

#endif // _HAL_LL_GPIO_H_
// ------------------------------------------------------------------------- END
