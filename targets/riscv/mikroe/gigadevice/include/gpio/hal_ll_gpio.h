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
 * @param[in,out] pin Pointer to the GPIO pin structure to be configured.
 * See @ref hal_ll_gpio_pin_t structure definition for more details.
 * @param[in] name The pin name identifier to configure.
 * See @ref hal_ll_pin_name_t type for valid pin names.
 * @param[in] direction The direction to set for the pin (input or output).
 * See @ref hal_ll_gpio_direction_t enumeration for possible directions.
 *
 * @return
 * - None.
 *
 * @note
 * - The function assumes the pin name is valid and corresponds to a supported GPIO pin.
 * - The pin structure is updated with the base address and mask for the pin.
 *
 * @pre
 * - The pin structure must be allocated and valid.
 *
 * @post
 * - The pin is configured with the specified direction.
 *
 * @warning
 * - Calling this function with an invalid pin name may result in undefined behavior.
 *
 * @par Example Usage
 * @code{.c}
 *    // GPIO low level structure. *    hal_ll_gpio_pin_t pin; * *    // Initialize pin as output. *    hal_ll_gpio_configure_pin( &pin, GPIO_PB2, HAL_LL_GPIO_DIGITAL_OUTPUT );
 * @endcode
 *
 * @par Limitations
 * - Does not configure pin pull-up or pull-down resistors.
 *
 * @see hal_ll_gpio_pin_t
 * @see hal_ll_pin_name_t
 * @see hal_ll_gpio_direction_t
 *
 * @link https://github.com/MikroElektronika/mikrosdk_v2/blob/master/targets/riscv/mikroe/gigadevice/include/gpio/hal_ll_gpio.h#L99 Link to header @endlink.
 * @link https://github.com/MikroElektronika/mikrosdk_v2/blob/master/targets/riscv/mikroe/gigadevice/src/gpio/hal_ll_gpio.c#L49 Link to source @endlink.
 */
void hal_ll_gpio_configure_pin(hal_ll_gpio_pin_t *pin, hal_ll_pin_name_t name, hal_ll_gpio_direction_t direction);

/**
 * @brief Reads the input state of a GPIO pin.
 *
 * @details
 * This function returns the current logical input level of the specified GPIO pin.
 * It reads the input status register and masks the bit corresponding to the pin.
 *
 * @param[in] pin Pointer to the GPIO pin structure to read from.
 * See @ref hal_ll_gpio_pin_t structure definition for more details.
 *
 * @return
 * - 0x01 if the pin input is high.
 * - 0x00 if the pin input is low or invalid.
 *
 * @note
 * - The function may be implemented as a macro depending on compilation flags.
 * - Reading the input reflects the actual voltage level on the pin.
 *
 * @pre
 * - The pin must be configured as input or capable of input reading.
 *
 * @post
 * - No side effects.
 *
 * @warning
 * - Reading from an uninitialized or invalid pin structure may cause undefined behavior.
 *
 * @par Example Usage
 * @code{.c}
 *    // GPIO low level structure. *    hal_ll_gpio_pin_t pin; * *    // GPIO value holder. *    hal_port_size_t read_value; * *    // Read the input state of the pin. *    read_value = hal_ll_gpio_read_pin_input( &pin );
 * @endcode
 *
 * @par Limitations
 * - None.
 *
 * @see hal_ll_gpio_pin_t
 *
 * @link https://github.com/MikroElektronika/mikrosdk_v2/blob/master/targets/riscv/mikroe/gigadevice/include/gpio/hal_ll_gpio.h#L143 Link to header @endlink.
 * @link https://github.com/MikroElektronika/mikrosdk_v2/blob/master/targets/riscv/mikroe/gigadevice/src/gpio/hal_ll_gpio.c Link to source @endlink.
 */
#if defined(FLATTEN_ME) && (FLATTEN_ME_LEVEL >= FLATTEN_ME_LEVEL_LOW)
#define hal_ll_gpio_read_pin_input(_handle) ((((hal_ll_gpio_base_handle_t *)((hal_ll_gpio_pin_t *)_handle)->base) != NULL) ? \
                                             (((hal_ll_gpio_base_handle_t *)((hal_ll_gpio_pin_t *)_handle)->base)->istat & ((hal_ll_gpio_pin_t *)_handle)->mask) : \
                                             (0))
#else
uint8_t hal_ll_gpio_read_pin_input(hal_ll_gpio_pin_t *pin);
#endif

/**
 * @brief Reads the output state of a GPIO pin.
 *
 * @details
 * This function returns the current logical output level of the specified GPIO pin.
 * It reads the output control register and masks the bit corresponding to the pin.
 *
 * @param[in] pin Pointer to the GPIO pin structure to read from.
 * See @ref hal_ll_gpio_pin_t structure definition for more details.
 *
 * @return
 * - 0x01 if the pin output is set high.
 * - 0x00 if the pin output is set low or invalid.
 *
 * @note
 * - The function may be implemented as a macro depending on compilation flags.
 * - Reading the output reflects the last output value set on the pin.
 *
 * @pre
 * - The pin must be configured as output or capable of output reading.
 *
 * @post
 * - No side effects.
 *
 * @warning
 * - Reading from an uninitialized or invalid pin structure may cause undefined behavior.
 *
 * @par Example Usage
 * @code{.c}
 *    // GPIO low level structure. *    hal_ll_gpio_pin_t pin; * *    // GPIO value holder. *    hal_port_size_t read_value; * *    // Read the output state of the pin. *    read_value = hal_ll_gpio_read_pin_output( &pin );
 * @endcode
 *
 * @par Limitations
 * - None.
 *
 * @see hal_ll_gpio_pin_t
 *
 * @link https://github.com/MikroElektronika/mikrosdk_v2/blob/master/targets/riscv/mikroe/gigadevice/include/gpio/hal_ll_gpio.h#L191 Link to header @endlink.
 * @link https://github.com/MikroElektronika/mikrosdk_v2/blob/master/targets/riscv/mikroe/gigadevice/src/gpio/hal_ll_gpio.c Link to source @endlink.
 */
#if defined(FLATTEN_ME) && (FLATTEN_ME_LEVEL >= FLATTEN_ME_LEVEL_LOW)
#define hal_ll_gpio_read_pin_output(_handle) ((((hal_ll_gpio_base_handle_t *)((hal_ll_gpio_pin_t *)_handle)->base) != NULL) ? \
                                              (((hal_ll_gpio_base_handle_t *)((hal_ll_gpio_pin_t *)_handle)->base)->octl & ((hal_ll_gpio_pin_t *)_handle)->mask) : \
                                              (0))
#else
uint8_t hal_ll_gpio_read_pin_output(hal_ll_gpio_pin_t *pin);
#endif

/**
 * @brief Sets the output state of a GPIO pin.
 *
 * @details
 * This function sets the output level of the specified GPIO pin to high or low.
 * It writes to the bit operation register to set or reset the pin output.
 *
 * @param[in,out] pin Pointer to the GPIO pin structure to write to.
 * See @ref hal_ll_gpio_pin_t structure definition for more details.
 * @param[in] value The output value to set (non-zero for high, zero for low).
 *
 * @return
 * - None.
 *
 * @note
 * - The function may be implemented as a macro depending on compilation flags.
 * - Writing to the pin affects the output driver state.
 *
 * @pre
 * - The pin must be configured as output.
 *
 * @post
 * - The pin output is set to the specified value.
 *
 * @warning
 * - Writing to an input-configured pin may have no effect or undefined behavior.
 *
 * @par Example Usage
 * @code{.c}
 *    // GPIO low level structure. *    hal_ll_gpio_pin_t pin; * *    // Set pin logic state to high (1). *    hal_ll_gpio_write_pin_output( &pin, 1 );
 * @endcode
 *
 * @par Limitations
 * - None.
 *
 * @see hal_ll_gpio_pin_t
 *
 * @link https://github.com/MikroElektronika/mikrosdk_v2/blob/master/targets/riscv/mikroe/gigadevice/include/gpio/hal_ll_gpio.h#L239 Link to header @endlink.
 * @link https://github.com/MikroElektronika/mikrosdk_v2/blob/master/targets/riscv/mikroe/gigadevice/src/gpio/hal_ll_gpio.c Link to source @endlink.
 */
#if defined(FLATTEN_ME) && (FLATTEN_ME_LEVEL >= FLATTEN_ME_LEVEL_LOW)
#define hal_ll_gpio_write_pin_output(_handle,_value) ((((hal_ll_gpio_base_handle_t *)((hal_ll_gpio_pin_t *)_handle)->base) != NULL) ? \
                                                          ((_value > 0) ? \
                                                           (((hal_ll_gpio_base_handle_t *)((hal_ll_gpio_pin_t *)_handle)->base)->bop = ((hal_ll_gpio_pin_t *)_handle)->mask) : \
                                                           (((hal_ll_gpio_base_handle_t *)((hal_ll_gpio_pin_t *)_handle)->base)->bop = ((uint32_t)((hal_ll_gpio_pin_t *)_handle)->mask << RESET_PINS_OFFSET))) : \
                                                      (0))
#else
void hal_ll_gpio_write_pin_output(hal_ll_gpio_pin_t *pin, uint8_t value);
#endif

/**
 * @brief Toggles the output state of a GPIO pin.
 *
 * @details
 * This function toggles the current output state of the specified GPIO pin.
 * If the pin output is high, it sets it low; if low, it sets it high.
 *
 * @param[in,out] pin Pointer to the GPIO pin structure to toggle.
 * See @ref hal_ll_gpio_pin_t structure definition for more details.
 *
 * @return
 * - None.
 *
 * @note
 * - The function may be implemented as a macro depending on compilation flags.
 * - Toggling is performed by reading the current output and writing the inverse.
 *
 * @pre
 * - The pin must be configured as output.
 *
 * @post
 * - The pin output state is inverted.
 *
 * @warning
 * - Toggling an input-configured pin may have no effect or undefined behavior.
 *
 * @par Example Usage
 * @code{.c}
 *    // GPIO low level structure. *    hal_ll_gpio_pin_t pin; * *    // Toggle pin logic state. *    hal_ll_gpio_toggle_pin_output( &pin );
 * @endcode
 *
 * @par Limitations
 * - None.
 *
 * @see hal_ll_gpio_pin_t
 * @see hal_ll_gpio_read_pin_output()
 * @see hal_ll_gpio_write_pin_output()
 *
 * @link https://github.com/MikroElektronika/mikrosdk_v2/blob/master/targets/riscv/mikroe/gigadevice/include/gpio/hal_ll_gpio.h#L290 Link to header @endlink.
 * @link https://github.com/MikroElektronika/mikrosdk_v2/blob/master/targets/riscv/mikroe/gigadevice/src/gpio/hal_ll_gpio.c Link to source @endlink.
 */
#if defined(FLATTEN_ME) && (FLATTEN_ME_LEVEL >= FLATTEN_ME_LEVEL_LOW)
#define hal_ll_gpio_toggle_pin_output(_handle) ((((hal_ll_gpio_base_handle_t *)((hal_ll_gpio_pin_t *)_handle)->base) != NULL) ? \
                                                    ((((((hal_ll_gpio_base_handle_t *)((hal_ll_gpio_pin_t *)_handle)->base)->octl & ((hal_ll_gpio_pin_t *)_handle)->mask))) ? \
                                                     (((hal_ll_gpio_base_handle_t *)((hal_ll_gpio_pin_t *)_handle)->base)->bop = ((uint32_t)((hal_ll_gpio_pin_t *)_handle)->mask << RESET_PINS_OFFSET)) : \
                                                     (((hal_ll_gpio_base_handle_t *)((hal_ll_gpio_pin_t *)_handle)->base)->bop = ((hal_ll_gpio_pin_t *)_handle)->mask)) : \
                                                (0))
#else
void hal_ll_gpio_toggle_pin_output(hal_ll_gpio_pin_t *pin);
#endif

/**
 * @brief Sets the output state of a GPIO pin to high.
 *
 * @details
 * This function sets the output of the specified GPIO pin to a high logic level.
 * It writes to the bit operation register to set the pin.
 *
 * @param[in,out] pin Pointer to the GPIO pin structure to set.
 * See @ref hal_ll_gpio_pin_t structure definition for more details.
 *
 * @return
 * - None.
 *
 * @note
 * - The function may be implemented as a macro depending on compilation flags.
 *
 * @pre
 * - The pin must be configured as output.
 *
 * @post
 * - The pin output is set high.
 *
 * @warning
 * - Setting an input-configured pin may have no effect or undefined behavior.
 *
 * @par Example Usage
 * @code{.c}
 *    // GPIO low level structure. *    hal_ll_gpio_pin_t pin; * *    // Set pin logical state to high. *    hal_ll_gpio_set_pin_output( &pin );
 * @endcode
 *
 * @par Limitations
 * - None.
 *
 * @see hal_ll_gpio_pin_t
 *
 * @link https://github.com/MikroElektronika/mikrosdk_v2/blob/master/targets/riscv/mikroe/gigadevice/include/gpio/hal_ll_gpio.h#L338 Link to header @endlink.
 * @link https://github.com/MikroElektronika/mikrosdk_v2/blob/master/targets/riscv/mikroe/gigadevice/src/gpio/hal_ll_gpio.c Link to source @endlink.
 */
#if defined(FLATTEN_ME) && (FLATTEN_ME_LEVEL >= FLATTEN_ME_LEVEL_LOW)
#define hal_ll_gpio_set_pin_output(_handle) ((((hal_ll_gpio_base_handle_t *)((hal_ll_gpio_pin_t *)_handle)->base) != NULL) ? \
                                             (((hal_ll_gpio_base_handle_t *)((hal_ll_gpio_pin_t *)_handle)->base)->bop = ((hal_ll_gpio_pin_t *)_handle)->mask) : \
                                             (0))
#else
void hal_ll_gpio_set_pin_output(hal_ll_gpio_pin_t *pin);
#endif

/**
 * @brief Clears the output state of a GPIO pin to low.
 *
 * @details
 * This function sets the output of the specified GPIO pin to a low logic level.
 * It writes to the bit clear register to reset the pin.
 *
 * @param[in,out] pin Pointer to the GPIO pin structure to clear.
 * See @ref hal_ll_gpio_pin_t structure definition for more details.
 *
 * @return
 * - None.
 *
 * @note
 * - The function may be implemented as a macro depending on compilation flags.
 *
 * @pre
 * - The pin must be configured as output.
 *
 * @post
 * - The pin output is set low.
 *
 * @warning
 * - Clearing an input-configured pin may have no effect or undefined behavior.
 *
 * @par Example Usage
 * @code{.c}
 *    // GPIO low level structure. *    hal_ll_gpio_pin_t pin; * *    // Set pin logical state to low. *    hal_ll_gpio_clear_pin_output( &pin );
 * @endcode
 *
 * @par Limitations
 * - None.
 *
 * @see hal_ll_gpio_pin_t
 *
 * @link https://github.com/MikroElektronika/mikrosdk_v2/blob/master/targets/riscv/mikroe/gigadevice/include/gpio/hal_ll_gpio.h#L384 Link to header @endlink.
 * @link https://github.com/MikroElektronika/mikrosdk_v2/blob/master/targets/riscv/mikroe/gigadevice/src/gpio/hal_ll_gpio.c Link to source @endlink.
 */
#if defined(FLATTEN_ME) && (FLATTEN_ME_LEVEL >= FLATTEN_ME_LEVEL_LOW)
#define hal_ll_gpio_clear_pin_output(_handle) ((((hal_ll_gpio_base_handle_t *)((hal_ll_gpio_pin_t *)_handle)->base) != NULL) ? \
                                               (((hal_ll_gpio_base_handle_t *)((hal_ll_gpio_pin_t *)_handle)->base)->bc = (uint32_t)((hal_ll_gpio_pin_t *)_handle)->mask) : \
                                               (0))
#else
void hal_ll_gpio_clear_pin_output(hal_ll_gpio_pin_t *pin);
#endif

/**
 * @brief Configures a GPIO port with specified parameters.
 *
 * @details
 * This function initializes a GPIO port structure with the base address and mask
 * corresponding to the specified port name. It then configures the port pins
 * specified by the mask as either digital input or digital output.
 *
 * @param[in,out] port Pointer to the GPIO port structure to be configured.
 * See @ref hal_ll_gpio_port_t structure definition for more details.
 * @param[in] name The port name identifier to configure.
 * See @ref hal_ll_port_name_t type for valid port names.
 * @param[in] mask Bitmask specifying which pins of the port to configure.
 * See @ref hal_ll_gpio_mask_t type for mask details.
 * @param[in] direction The direction to set for the port pins (input or output).
 * See @ref hal_ll_gpio_direction_t enumeration for possible directions.
 *
 * @return
 * - None.
 *
 * @note
 * - The function assumes the port name is valid and corresponds to a supported GPIO port.
 * - Only pins specified in the mask are configured.
 *
 * @pre
 * - The port structure must be allocated and valid.
 *
 * @post
 * - The port pins specified by the mask are configured with the specified direction.
 *
 * @warning
 * - Calling this function with an invalid port name or mask may result in undefined behavior.
 *
 * @par Example Usage
 * @code{.c}
 *    // GPIO low level structure. *    hal_ll_gpio_port_t port; * *    // Initialize port as output. *    hal_ll_gpio_configure_port( &port, PORTB, 0xFF, HAL_LL_GPIO_DIGITAL_OUTPUT );
 * @endcode
 *
 * @par Limitations
 * - Does not configure pin pull-up or pull-down resistors.
 *
 * @see hal_ll_gpio_port_t
 * @see hal_ll_port_name_t
 * @see hal_ll_gpio_mask_t
 * @see hal_ll_gpio_direction_t
 *
 * @link https://github.com/MikroElektronika/mikrosdk_v2/blob/master/targets/riscv/mikroe/gigadevice/include/gpio/hal_ll_gpio.h#L439 Link to header @endlink.
 * @link https://github.com/MikroElektronika/mikrosdk_v2/blob/master/targets/riscv/mikroe/gigadevice/src/gpio/hal_ll_gpio.c#L124 Link to source @endlink.
 */
void hal_ll_gpio_configure_port(hal_ll_gpio_port_t *port, hal_ll_port_name_t name, hal_ll_gpio_mask_t mask, hal_ll_gpio_direction_t direction);

/**
 * @brief Reads the input state of a GPIO port.
 *
 * @details
 * This function returns the current logical input levels of the specified GPIO port pins
 * as masked by the port's mask. It reads the input status register and applies the mask.
 *
 * @param[in] port Pointer to the GPIO port structure to read from.
 * See @ref hal_ll_gpio_port_t structure definition for more details.
 *
 * @return
 * - Bitmask representing the input states of the port pins specified by the mask.
 * - Zero if the port base is invalid.
 *
 * @note
 * - The function may be implemented as a macro depending on compilation flags.
 * - Reading the input reflects the actual voltage levels on the port pins.
 *
 * @pre
 * - The port must be configured as input or capable of input reading.
 *
 * @post
 * - No side effects.
 *
 * @warning
 * - Reading from an uninitialized or invalid port structure may cause undefined behavior.
 *
 * @par Example Usage
 * @code{.c}
 *    // GPIO low level structure. *    hal_ll_gpio_port_t port; * *    // GPIO value holder. *    hal_port_size_t read_value; * *    // Read the input state of the port. *    read_value = hal_ll_gpio_read_port_input( &port );
 * @endcode
 *
 * @par Limitations
 * - None.
 *
 * @see hal_ll_gpio_port_t
 *
 * @link https://github.com/MikroElektronika/mikrosdk_v2/blob/master/targets/riscv/mikroe/gigadevice/include/gpio/hal_ll_gpio.h#L483 Link to header @endlink.
 * @link https://github.com/MikroElektronika/mikrosdk_v2/blob/master/targets/riscv/mikroe/gigadevice/src/gpio/hal_ll_gpio.c Link to source @endlink.
 */
#if defined(FLATTEN_ME) && (FLATTEN_ME_LEVEL >= FLATTEN_ME_LEVEL_LOW)
#define hal_ll_gpio_read_port_input(_handle) ((((hal_ll_gpio_base_handle_t *)((hal_ll_gpio_port_t *)_handle)->base) != NULL) ? \
                                              ((hal_ll_port_size_t)((hal_ll_gpio_base_handle_t *)((hal_ll_gpio_port_t *)_handle)->base)->istat & ((hal_ll_gpio_port_t *)_handle)->mask) : \
                                              (0))
#else
hal_ll_port_size_t hal_ll_gpio_read_port_input(hal_ll_gpio_port_t *port);
#endif

/**
 * @brief Reads the output state of a GPIO port.
 *
 * @details
 * This function returns the current logical output levels of the specified GPIO port pins
 * as masked by the port's mask. It reads the output control register and applies the mask.
 *
 * @param[in] port Pointer to the GPIO port structure to read from.
 * See @ref hal_ll_gpio_port_t structure definition for more details.
 *
 * @return
 * - Bitmask representing the output states of the port pins specified by the mask.
 * - Zero if the port base is invalid.
 *
 * @note
 * - The function may be implemented as a macro depending on compilation flags.
 * - Reading the output reflects the last output values set on the port pins.
 *
 * @pre
 * - The port must be configured as output or capable of output reading.
 *
 * @post
 * - No side effects.
 *
 * @warning
 * - Reading from an uninitialized or invalid port structure may cause undefined behavior.
 *
 * @par Example Usage
 * @code{.c}
 *    // GPIO low level structure. *    hal_ll_gpio_port_t port; * *    // GPIO value holder. *    hal_port_size_t read_value; * *    // Read the output state of the port. *    read_value = hal_ll_gpio_read_port_output( &port );
 * @endcode
 *
 * @par Limitations
 * - None.
 *
 * @see hal_ll_gpio_port_t
 *
 * @link https://github.com/MikroElektronika/mikrosdk_v2/blob/master/targets/riscv/mikroe/gigadevice/include/gpio/hal_ll_gpio.h#L531 Link to header @endlink.
 * @link https://github.com/MikroElektronika/mikrosdk_v2/blob/master/targets/riscv/mikroe/gigadevice/src/gpio/hal_ll_gpio.c Link to source @endlink.
 */
#if defined(FLATTEN_ME) && (FLATTEN_ME_LEVEL >= FLATTEN_ME_LEVEL_LOW)
#define hal_ll_gpio_read_port_output(_handle) ((((hal_ll_gpio_base_handle_t *)((hal_ll_gpio_port_t *)_handle)->base) != NULL) ? \
                                               ((hal_ll_port_size_t)(((hal_ll_gpio_base_handle_t *)((hal_ll_gpio_port_t *)_handle)->base)->octl) & (((hal_ll_gpio_port_t *)_handle)->mask)) : \
                                               (0))
#else
hal_ll_port_size_t hal_ll_gpio_read_port_output(hal_ll_gpio_port_t *port);
#endif

/**
 * @brief Sets the output state of a GPIO port.
 *
 * @details
 * This function sets the output levels of the specified GPIO port pins as specified by the value.
 * It writes to the bit operation register to set or reset pins according to the value and mask.
 *
 * @param[in,out] port Pointer to the GPIO port structure to write to.
 * See @ref hal_ll_gpio_port_t structure definition for more details.
 * @param[in] value Bitmask representing the output values to set on the port pins.
 *
 * @return
 * - None.
 *
 * @note
 * - The function may be implemented as a macro depending on compilation flags.
 * - Only pins specified in the port mask are affected.
 *
 * @pre
 * - The port must be configured as output.
 *
 * @post
 * - The port pins output states are updated according to the value.
 *
 * @warning
 * - Writing to an input-configured port may have no effect or undefined behavior.
 *
 * @par Example Usage
 * @code{.c}
 *    // GPIO low level structure. *    hal_ll_gpio_port_t port; * *    // Set port logic state to 0xAA. *    hal_ll_gpio_write_port_output( &port, 0xAA );
 * @endcode
 *
 * @par Limitations
 * - None.
 *
 * @see hal_ll_gpio_port_t
 *
 * @link https://github.com/MikroElektronika/mikrosdk_v2/blob/master/targets/riscv/mikroe/gigadevice/include/gpio/hal_ll_gpio.h#L579 Link to header @endlink.
 * @link https://github.com/MikroElektronika/mikrosdk_v2/blob/master/targets/riscv/mikroe/gigadevice/src/gpio/hal_ll_gpio.c Link to source @endlink.
 */
#if defined(FLATTEN_ME) && (FLATTEN_ME_LEVEL >= FLATTEN_ME_LEVEL_LOW)
#define hal_ll_gpio_write_port_output(_handle,_value) ((((hal_ll_gpio_base_handle_t *)((hal_ll_gpio_port_t *)_handle)->base) != NULL) ? \
                                                          (((hal_ll_gpio_base_handle_t *)((hal_ll_gpio_port_t *)_handle)->base)->bop = \
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
