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

#ifdef __cplusplus
extern "C"
{
#endif

#include "hal_ll_gpio_port.h"

/**
 * @brief Configures a GPIO pin with specified name and direction.
 *
 * @details
 * Initializes the given GPIO pin structure with the base address and mask corresponding
 * to the pin name. Configures the pin as digital input, digital output, or analog input
 * based on the specified direction.
 *
 * @param[out] pin Pointer to the GPIO pin structure to be configured.
 * See @ref hal_ll_gpio_pin_t structure definition for more details.
 * @param[in] name The identifier of the pin to configure.
 * See @ref hal_ll_pin_name_t type for valid pin names.
 * @param[in] direction The direction mode to set for the pin (input, output, analog).
 * See @ref hal_ll_gpio_direction_t enumeration for possible directions.
 *
 * @return
 * - None.
 *
 * @note
 * - If the pin name is invalid or out of range, the pin base is set to NULL and mask to HAL_LL_PIN_NC.
 * - The function internally calls port-specific configuration functions.
 *
 * @pre
 * - The pin structure must be allocated before calling this function.
 *
 * @post
 * - The pin structure is initialized and the hardware pin is configured accordingly.
 *
 * @warning
 * - Passing an invalid pin name may result in uninitialized pin structure.
 *
 * @par Example Usage
 * @code{.c}
 *    // GPIO low level structure. *    hal_ll_gpio_pin_t pin; * *    // Initialize pin as output. *    hal_ll_gpio_configure_pin( &pin, GPIO_PB2, HAL_LL_GPIO_DIGITAL_OUTPUT );
 * @endcode
 *
 * @par Limitations
 * - Only supports pins defined within the PORT_COUNT range.
 *
 * @see hal_ll_gpio_pin_t
 * @see hal_ll_pin_name_t
 * @see hal_ll_gpio_direction_t
 *
 * @link https://github.com/MikroElektronika/mikrosdk_v2/blob/master/targets/pic_16bit/mikroe/dspic/include/gpio/hal_ll_gpio.h#L100 Link to header @endlink.
 * @link https://github.com/MikroElektronika/mikrosdk_v2/blob/master/targets/pic_16bit/mikroe/dspic/src/gpio/implementation_1/hal_ll_gpio.c#L50 Link to source @endlink.
 */
void hal_ll_gpio_configure_pin(hal_ll_gpio_pin_t *pin, hal_ll_pin_name_t name, hal_ll_gpio_direction_t direction);

/**
 * @brief Reads the input state of a GPIO pin.
 *
 * @details
 * Returns the current logical level present on the specified GPIO pin's input register.
 * The function reads the port input register and masks the bit corresponding to the pin.
 *
 * @param[in] pin Pointer to the GPIO pin structure to read from.
 * See @ref hal_ll_gpio_pin_t structure definition for more details.
 *
 * @return
 * - 1 if the pin input is high.
 * - 0 if the pin input is low or if the pin base is NULL.
 *
 * @note
 * - This function may be implemented as a macro depending on the FLATTEN_ME_LEVEL.
 *
 * @pre
 * - The pin must be configured as an input.
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
 * - Only supports pins with valid base addresses.
 *
 * @see hal_ll_gpio_pin_t
 *
 * @link https://github.com/MikroElektronika/mikrosdk_v2/blob/master/targets/pic_16bit/mikroe/dspic/include/gpio/hal_ll_gpio.h#L143 Link to header @endlink.
 * @link https://github.com/MikroElektronika/mikrosdk_v2/blob/master/targets/pic_16bit/mikroe/dspic/src/gpio/implementation_1/hal_ll_gpio.c Link to source @endlink.
 */
#if defined(FLATTEN_ME) && (FLATTEN_ME_LEVEL >= FLATTEN_ME_LEVEL_LOW)
#define hal_ll_gpio_read_pin_input( _handle ) ((((hal_ll_gpio_base_handle_t *)((hal_ll_gpio_pin_t *)_handle)->base) == 0) ? \
                                               (0) : (*( uint16_t * )((hal_ll_gpio_base_handle_t *)((hal_ll_gpio_pin_t *)_handle)->base)->port_reg_addr & ((hal_ll_gpio_pin_t *)_handle)->mask) ? \
                                               (1) : (0))
#else
uint8_t hal_ll_gpio_read_pin_input(hal_ll_gpio_pin_t *pin);
#endif

/**
 * @brief Reads the output latch state of a GPIO pin.
 *
 * @details
 * Returns the current logical level set on the specified GPIO pin's output latch register.
 * The function reads the port latch register and masks the bit corresponding to the pin.
 *
 * @param[in] pin Pointer to the GPIO pin structure to read from.
 * See @ref hal_ll_gpio_pin_t structure definition for more details.
 *
 * @return
 * - 1 if the pin output latch is set high.
 * - 0 if the pin output latch is low or if the pin base is NULL.
 *
 * @note
 * - This function may be implemented as a macro depending on the FLATTEN_ME_LEVEL.
 *
 * @pre
 * - The pin must be configured as an output.
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
 * - Only supports pins with valid base addresses.
 *
 * @see hal_ll_gpio_pin_t
 *
 * @link https://github.com/MikroElektronika/mikrosdk_v2/blob/master/targets/pic_16bit/mikroe/dspic/include/gpio/hal_ll_gpio.h#L190 Link to header @endlink.
 * @link https://github.com/MikroElektronika/mikrosdk_v2/blob/master/targets/pic_16bit/mikroe/dspic/src/gpio/implementation_1/hal_ll_gpio.c Link to source @endlink.
 */
#if defined(FLATTEN_ME) && (FLATTEN_ME_LEVEL >= FLATTEN_ME_LEVEL_LOW)
#define hal_ll_gpio_read_pin_output( _handle ) ((((hal_ll_gpio_base_handle_t *)((hal_ll_gpio_pin_t *)_handle)->base) == 0) ? \
                                                (0) : (*( uint16_t * )((hal_ll_gpio_base_handle_t *)((hal_ll_gpio_pin_t *)_handle)->base)->lat_reg_addr & ((hal_ll_gpio_pin_t *)_handle)->mask) ? \
                                                (1) : (0))
#else
uint8_t hal_ll_gpio_read_pin_output(hal_ll_gpio_pin_t *pin);
#endif

/**
 * @brief Writes a logical value to the output latch of a GPIO pin.
 *
 * @details
 * Sets or clears the output latch bit corresponding to the specified GPIO pin,
 * effectively driving the pin high or low if configured as an output.
 *
 * @param[in,out] pin Pointer to the GPIO pin structure to write to.
 * See @ref hal_ll_gpio_pin_t structure definition for more details.
 * @param[in] value Logical value to write to the pin output latch (0 or non-zero).
 *
 * @return
 * - None.
 *
 * @note
 * - This function may be implemented as a macro depending on the FLATTEN_ME_LEVEL.
 *
 * @pre
 * - The pin must be configured as an output.
 *
 * @post
 * - The pin output latch is updated to the specified value.
 *
 * @warning
 * - Writing to a pin not configured as output may have no effect or undefined behavior.
 *
 * @par Example Usage
 * @code{.c}
 *    // GPIO low level structure. *    hal_ll_gpio_pin_t pin; * *    // Set pin logic state to high (1). *    hal_ll_gpio_write_pin_output( &pin, 1 );
 * @endcode
 *
 * @par Limitations
 * - Only supports pins with valid base addresses.
 *
 * @see hal_ll_gpio_pin_t
 *
 * @link https://github.com/MikroElektronika/mikrosdk_v2/blob/master/targets/pic_16bit/mikroe/dspic/include/gpio/hal_ll_gpio.h#L237 Link to header @endlink.
 * @link https://github.com/MikroElektronika/mikrosdk_v2/blob/master/targets/pic_16bit/mikroe/dspic/src/gpio/implementation_1/hal_ll_gpio.c Link to source @endlink.
 */
#if defined(FLATTEN_ME) && (FLATTEN_ME_LEVEL >= FLATTEN_ME_LEVEL_LOW)
#define hal_ll_gpio_write_pin_output( _handle, _value ) ((((hal_ll_gpio_base_handle_t *)((hal_ll_gpio_pin_t *)_handle)->base) != NULL) ? \
                                                            ((_value > 0) ? \
                                                             (set_reg_bits(((hal_ll_gpio_base_handle_t *)((hal_ll_gpio_pin_t *)_handle)->base)->lat_reg_addr, (uint32_t)((hal_ll_gpio_pin_t *)_handle)->mask)) : \
                                                             (clear_reg_bits(((hal_ll_gpio_base_handle_t *)((hal_ll_gpio_pin_t *)_handle)->base)->lat_reg_addr, (uint32_t)((hal_ll_gpio_pin_t *)_handle)->mask))) : \
                                                         (0))
#else
void hal_ll_gpio_write_pin_output(hal_ll_gpio_pin_t *pin, uint8_t value);
#endif

/**
 * @brief Toggles the output latch state of a GPIO pin.
 *
 * @details
 * Reads the current output latch state of the specified GPIO pin and writes the inverse value,
 * effectively toggling the pin output if configured as an output.
 *
 * @param[in,out] pin Pointer to the GPIO pin structure to toggle.
 * See @ref hal_ll_gpio_pin_t structure definition for more details.
 *
 * @return
 * - None.
 *
 * @note
 * - This function may be implemented as a macro depending on the FLATTEN_ME_LEVEL.
 *
 * @pre
 * - The pin must be configured as an output.
 *
 * @post
 * - The pin output latch is toggled.
 *
 * @warning
 * - Toggling a pin not configured as output may have no effect or undefined behavior.
 *
 * @par Example Usage
 * @code{.c}
 *    // GPIO low level structure. *    hal_ll_gpio_pin_t pin; * *    // Toggle pin logic state. *    hal_ll_gpio_toggle_pin_output( &pin );
 * @endcode
 *
 * @par Limitations
 * - Only supports pins with valid base addresses.
 *
 * @see hal_ll_gpio_pin_t
 *
 * @link https://github.com/MikroElektronika/mikrosdk_v2/blob/master/targets/pic_16bit/mikroe/dspic/include/gpio/hal_ll_gpio.h#L285 Link to header @endlink.
 * @link https://github.com/MikroElektronika/mikrosdk_v2/blob/master/targets/pic_16bit/mikroe/dspic/src/gpio/implementation_1/hal_ll_gpio.c Link to source @endlink.
 */
#if defined(FLATTEN_ME) && (FLATTEN_ME_LEVEL >= FLATTEN_ME_LEVEL_LOW)
#define hal_ll_gpio_toggle_pin_output(_handle) ((((hal_ll_gpio_base_handle_t *)((hal_ll_gpio_pin_t *)_handle)->base) != NULL) ? \
                                                    (((read_reg(((hal_ll_gpio_base_handle_t *)((hal_ll_gpio_pin_t *)_handle)->base)->lat_reg_addr) & ((hal_ll_gpio_pin_t *)_handle)->mask)) ? \
                                                     (clear_reg_bits(((hal_ll_gpio_base_handle_t *)((hal_ll_gpio_pin_t *)_handle)->base)->lat_reg_addr, (uint32_t)((hal_ll_gpio_pin_t *)_handle)->mask)) : \
                                                     (set_reg_bits(((hal_ll_gpio_base_handle_t *)((hal_ll_gpio_pin_t *)_handle)->base)->lat_reg_addr, (uint32_t)((hal_ll_gpio_pin_t *)_handle)->mask))) : \
                                                (0))
#else
void hal_ll_gpio_toggle_pin_output(hal_ll_gpio_pin_t *pin);
#endif

/**
 * @brief Sets the output latch of a GPIO pin to high.
 *
 * @details
 * Sets the output latch bit corresponding to the specified GPIO pin,
 * driving the pin output high if configured as an output.
 *
 * @param[in,out] pin Pointer to the GPIO pin structure to set.
 * See @ref hal_ll_gpio_pin_t structure definition for more details.
 *
 * @return
 * - None.
 *
 * @note
 * - This function may be implemented as a macro depending on the FLATTEN_ME_LEVEL.
 *
 * @pre
 * - The pin must be configured as an output.
 *
 * @post
 * - The pin output latch is set to high.
 *
 * @warning
 * - Setting a pin not configured as output may have no effect or undefined behavior.
 *
 * @par Example Usage
 * @code{.c}
 *    // GPIO low level structure. *    hal_ll_gpio_pin_t pin; * *    // Set pin logical state to high. *    hal_ll_gpio_set_pin_output( &pin );
 * @endcode
 *
 * @par Limitations
 * - Only supports pins with valid base addresses.
 *
 * @see hal_ll_gpio_pin_t
 *
 * @link https://github.com/MikroElektronika/mikrosdk_v2/blob/master/targets/pic_16bit/mikroe/dspic/include/gpio/hal_ll_gpio.h#L333 Link to header @endlink.
 * @link https://github.com/MikroElektronika/mikrosdk_v2/blob/master/targets/pic_16bit/mikroe/dspic/src/gpio/implementation_1/hal_ll_gpio.c Link to source @endlink.
 */
#if defined(FLATTEN_ME) && (FLATTEN_ME_LEVEL >= FLATTEN_ME_LEVEL_LOW)
#define hal_ll_gpio_set_pin_output( _handle ) ((((hal_ll_gpio_base_handle_t *)((hal_ll_gpio_pin_t *)_handle)->base) != NULL) ? \
                                               (set_reg_bits(((hal_ll_gpio_base_handle_t *)((hal_ll_gpio_pin_t *)_handle)->base)->lat_reg_addr, ((hal_ll_gpio_pin_t *)_handle)->mask)) : \
                                               (0))
#else
void hal_ll_gpio_set_pin_output(hal_ll_gpio_pin_t *pin);
#endif

/**
 * @brief Clears the output latch of a GPIO pin to low.
 *
 * @details
 * Clears the output latch bit corresponding to the specified GPIO pin,
 * driving the pin output low if configured as an output.
 *
 * @param[in,out] pin Pointer to the GPIO pin structure to clear.
 * See @ref hal_ll_gpio_pin_t structure definition for more details.
 *
 * @return
 * - None.
 *
 * @note
 * - This function may be implemented as a macro depending on the FLATTEN_ME_LEVEL.
 *
 * @pre
 * - The pin must be configured as an output.
 *
 * @post
 * - The pin output latch is cleared to low.
 *
 * @warning
 * - Clearing a pin not configured as output may have no effect or undefined behavior.
 *
 * @par Example Usage
 * @code{.c}
 *    // GPIO low level structure. *    hal_ll_gpio_pin_t pin; * *    // Set pin logical state to low. *    hal_ll_gpio_clear_pin_output( &pin );
 * @endcode
 *
 * @par Limitations
 * - Only supports pins with valid base addresses.
 *
 * @see hal_ll_gpio_pin_t
 *
 * @link https://github.com/MikroElektronika/mikrosdk_v2/blob/master/targets/pic_16bit/mikroe/dspic/include/gpio/hal_ll_gpio.h#L379 Link to header @endlink.
 * @link https://github.com/MikroElektronika/mikrosdk_v2/blob/master/targets/pic_16bit/mikroe/dspic/src/gpio/implementation_1/hal_ll_gpio.c Link to source @endlink.
 */
#if defined(FLATTEN_ME) && (FLATTEN_ME_LEVEL >= FLATTEN_ME_LEVEL_LOW)
#define hal_ll_gpio_clear_pin_output( _handle ) ((((hal_ll_gpio_base_handle_t *)((hal_ll_gpio_pin_t *)_handle)->base) != NULL) ? \
                                                 (clear_reg_bits(((hal_ll_gpio_base_handle_t *)((hal_ll_gpio_pin_t *)_handle)->base)->lat_reg_addr, ((hal_ll_gpio_pin_t *)_handle)->mask)) : \
                                                 (0))
#else
void hal_ll_gpio_clear_pin_output(hal_ll_gpio_pin_t *pin);
#endif

/**
 * @brief Configures a GPIO port with specified name, mask, and direction.
 *
 * @details
 * Initializes the given GPIO port structure with the base address and mask corresponding
 * to the port name. Configures the port pins specified by the mask as digital input or output.
 *
 * @param[out] port Pointer to the GPIO port structure to be configured.
 * See @ref hal_ll_gpio_port_t structure definition for more details.
 * @param[in] name The identifier of the port to configure.
 * See @ref hal_ll_port_name_t type for valid port names.
 * @param[in] mask Bitmask specifying which pins of the port to configure.
 * See @ref hal_ll_gpio_mask_t type for mask details.
 * @param[in] direction The direction mode to set for the port pins (input or output).
 * See @ref hal_ll_gpio_direction_t enumeration for possible directions.
 *
 * @return
 * - None.
 *
 * @note
 * - If the port name is invalid or out of range, the port base is set to NULL and mask to HAL_LL_PIN_NC.
 * - The function internally calls port-specific configuration functions.
 *
 * @pre
 * - The port structure must be allocated before calling this function.
 *
 * @post
 * - The port structure is initialized and the hardware port pins are configured accordingly.
 *
 * @warning
 * - Passing an invalid port name may result in uninitialized port structure.
 *
 * @par Example Usage
 * @code{.c}
 *    // GPIO low level structure. *    hal_ll_gpio_port_t port; * *    // Initialize port as output. *    hal_ll_gpio_configure_port( &port, PORTB, 0xFF, HAL_LL_GPIO_DIGITAL_OUTPUT );
 * @endcode
 *
 * @par Limitations
 * - Only supports ports defined within the PORT_COUNT range.
 *
 * @see hal_ll_gpio_port_t
 * @see hal_ll_port_name_t
 * @see hal_ll_gpio_mask_t
 * @see hal_ll_gpio_direction_t
 *
 * @link https://github.com/MikroElektronika/mikrosdk_v2/blob/master/targets/pic_16bit/mikroe/dspic/include/gpio/hal_ll_gpio.h#L433 Link to header @endlink.
 * @link https://github.com/MikroElektronika/mikrosdk_v2/blob/master/targets/pic_16bit/mikroe/dspic/src/gpio/implementation_1/hal_ll_gpio.c#L137 Link to source @endlink.
 */
void hal_ll_gpio_configure_port(hal_ll_gpio_port_t *port, hal_ll_port_name_t name, hal_ll_gpio_mask_t mask, hal_ll_gpio_direction_t direction);

/**
 * @brief Reads the input state of a GPIO port.
 *
 * @details
 * Returns the current logical levels present on the specified GPIO port's input register,
 * masked by the port's configured mask.
 *
 * @param[in] port Pointer to the GPIO port structure to read from.
 * See @ref hal_ll_gpio_port_t structure definition for more details.
 *
 * @return
 * - The masked input state of the port pins.
 * - 0 if the port base is NULL.
 *
 * @note
 * - This function may be implemented as a macro depending on the FLATTEN_ME_LEVEL.
 *
 * @pre
 * - The port must be configured as input.
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
 * - Only supports ports with valid base addresses.
 *
 * @see hal_ll_gpio_port_t
 *
 * @link https://github.com/MikroElektronika/mikrosdk_v2/blob/master/targets/pic_16bit/mikroe/dspic/include/gpio/hal_ll_gpio.h#L476 Link to header @endlink.
 * @link https://github.com/MikroElektronika/mikrosdk_v2/blob/master/targets/pic_16bit/mikroe/dspic/src/gpio/implementation_1/hal_ll_gpio.c Link to source @endlink.
 */
#if defined(FLATTEN_ME) && (FLATTEN_ME_LEVEL >= FLATTEN_ME_LEVEL_LOW)
#define hal_ll_gpio_read_port_input( _handle ) ((((hal_ll_gpio_base_handle_t *)((hal_ll_gpio_port_t *)_handle)->base) != NULL) ? \
                                                (read_reg_bits(((hal_ll_gpio_base_handle_t *)((hal_ll_gpio_port_t *)_handle)->base)->port_reg_addr, ((hal_ll_gpio_port_t *)_handle)->mask)) : \
                                                (0))
#else
hal_ll_port_size_t hal_ll_gpio_read_port_input(hal_ll_gpio_port_t *port);
#endif

/**
 * @brief Reads the output latch state of a GPIO port.
 *
 * @details
 * Returns the current logical levels set on the specified GPIO port's output latch register,
 * masked by the port's configured mask.
 *
 * @param[in] port Pointer to the GPIO port structure to read from.
 * See @ref hal_ll_gpio_port_t structure definition for more details.
 *
 * @return
 * - The masked output latch state of the port pins.
 * - 0 if the port base is NULL.
 *
 * @note
 * - This function may be implemented as a macro depending on the FLATTEN_ME_LEVEL.
 *
 * @pre
 * - The port must be configured as output.
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
 * - Only supports ports with valid base addresses.
 *
 * @see hal_ll_gpio_port_t
 *
 * @link https://github.com/MikroElektronika/mikrosdk_v2/blob/master/targets/pic_16bit/mikroe/dspic/include/gpio/hal_ll_gpio.h#L523 Link to header @endlink.
 * @link https://github.com/MikroElektronika/mikrosdk_v2/blob/master/targets/pic_16bit/mikroe/dspic/src/gpio/implementation_1/hal_ll_gpio.c Link to source @endlink.
 */
#if defined(FLATTEN_ME) && (FLATTEN_ME_LEVEL >= FLATTEN_ME_LEVEL_LOW)
#define hal_ll_gpio_read_port_output( _handle ) ((((hal_ll_gpio_base_handle_t *)((hal_ll_gpio_port_t *)_handle)->base) != NULL) ? \
                                                 (read_reg_bits(((hal_ll_gpio_base_handle_t *)((hal_ll_gpio_port_t *)_handle)->base)->lat_reg_addr, ((hal_ll_gpio_port_t *)_handle)->mask)) : \
                                                 (0))
#else
hal_ll_port_size_t hal_ll_gpio_read_port_output(hal_ll_gpio_port_t *port);
#endif

/**
 * @brief Writes a logical value to the output latch of a GPIO port.
 *
 * @details
 * Updates the output latch register of the specified GPIO port with the given value,
 * affecting only the pins specified by the port's mask.
 *
 * @param[in,out] port Pointer to the GPIO port structure to write to.
 * See @ref hal_ll_gpio_port_t structure definition for more details.
 * @param[in] value The value to write to the port output latch.
 * See @ref hal_ll_port_size_t type for value details.
 *
 * @return
 * - None.
 *
 * @note
 * - This function may be implemented as a macro depending on the FLATTEN_ME_LEVEL.
 * - The function preserves bits outside the port mask.
 *
 * @pre
 * - The port must be configured as output.
 *
 * @post
 * - The port output latch is updated with the specified value.
 *
 * @warning
 * - Writing to a port not configured as output may have no effect or undefined behavior.
 *
 * @par Example Usage
 * @code{.c}
 *    // GPIO low level structure. *    hal_ll_gpio_port_t port; * *    // Set port logic state to 0xAA. *    hal_ll_gpio_write_port_output( &port, 0xAA );
 * @endcode
 *
 * @par Limitations
 * - Only supports ports with valid base addresses.
 *
 * @see hal_ll_gpio_port_t
 * @see hal_ll_port_size_t
 *
 * @link https://github.com/MikroElektronika/mikrosdk_v2/blob/master/targets/pic_16bit/mikroe/dspic/include/gpio/hal_ll_gpio.h#L573 Link to header @endlink.
 * @link https://github.com/MikroElektronika/mikrosdk_v2/blob/master/targets/pic_16bit/mikroe/dspic/src/gpio/implementation_1/hal_ll_gpio.c Link to source @endlink.
 */
#if defined(FLATTEN_ME) && (FLATTEN_ME_LEVEL >= FLATTEN_ME_LEVEL_LOW)
#define hal_ll_gpio_write_port_output(_handle,_value) ((((hal_ll_gpio_base_handle_t *)((hal_ll_gpio_port_t *)_handle)->base) != NULL) ? \
                                                          (write_reg(((hal_ll_gpio_base_handle_t *)((hal_ll_gpio_port_t *)_handle)->base)->lat_reg_addr, \
                                                           ((read_reg_bits(((hal_ll_gpio_base_handle_t *)((hal_ll_gpio_port_t *)_handle)->base)->lat_reg_addr, ((hal_ll_gpio_port_t *)_handle)->mask) & \
                                                           ~(((hal_ll_gpio_port_t *)_handle)->mask)) | (((hal_ll_gpio_port_t *)_handle)->mask & _value)))) : \
                                                       (0))

#else
void hal_ll_gpio_write_port_output(hal_ll_gpio_port_t *port, hal_ll_port_size_t value);
#endif

#ifdef __cplusplus
}
#endif

#endif // _HAL_LL_GPIO_H_
// ------------------------------------------------------------------------- END
