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
 * @brief Configures a GPIO pin with specified name and direction.
 *
 * @details
 * This function initializes the given GPIO pin structure by setting its base port
 * and mask according to the pin name. It then configures the pin direction as input or output.
 *
 * @param[in,out] pin Pointer to the GPIO pin structure to configure.
 * See @ref hal_ll_gpio_pin_t structure definition for more details.
 * @param[in] name The identifier of the pin to configure.
 * See @ref hal_ll_pin_name_t type for valid pin names.
 * @param[in] direction The direction to set for the pin (input or output).
 * See @ref hal_ll_gpio_direction_t enumeration for possible directions.
 *
 * @return
 * - None.
 *
 * @note
 * - The pin structure must be valid and properly allocated before calling this function.
 * - The function sets the pin direction by calling internal functions for digital input or output.
 *
 * @pre
 * - The hardware GPIO port corresponding to the pin name must be available.
 *
 * @post
 * - The pin structure is initialized and the pin direction is configured.
 *
 * @warning
 * - Calling this function with invalid pin names or directions may lead to undefined behavior.
 *
 * @par Example Usage
 * @code{.c}
 *     TODO: ADD EXAMPLE CODE FOR `void hal_ll_gpio_configure_pin(hal_ll_gpio_pin_t *pin, hal_ll_pin_name_t name, hal_ll_gpio_direction_t direction)`
 * @endcode
 *
 * @par Limitations
 * - This function does not configure pin pull-up or pull-down resistors.
 *
 * @see hal_ll_gpio_pin_t
 * @see hal_ll_pin_name_t
 * @see hal_ll_gpio_direction_t
 *
 * @link https://github.com/MikroElektronika/mikrosdk_v2/blob/master/targets/arm/mikroe/sam/include/gpio/hal_ll_gpio.h#L98 Link to header @endlink.
 * @link https://github.com/MikroElektronika/mikrosdk_v2/blob/master/targets/arm/mikroe/sam/src/gpio/hal_ll_gpio.c#L49 Link to source @endlink.
 */
void hal_ll_gpio_configure_pin(hal_ll_gpio_pin_t *pin, hal_ll_pin_name_t name, hal_ll_gpio_direction_t direction);

/**
 * @brief Reads the input state of a GPIO pin.
 *
 * @details
 * This function returns the current logical input level of the specified GPIO pin.
 * It reads the pin status from the hardware port and masks it to obtain the pin value.
 *
 * @param[in] pin Pointer to the GPIO pin structure to read.
 * See @ref hal_ll_gpio_pin_t structure definition for more details.
 *
 * @return
 * - 1 if the pin input is high.
 * - 0 if the pin input is low or if the pin base is NULL.
 *
 * @note
 * - The pin must be configured as input to get valid readings.
 *
 * @pre
 * - The pin must be properly configured and initialized.
 *
 * @post
 * - No side effects.
 *
 * @warning
 * - Reading a pin configured as output may not reflect the actual pin state.
 *
 * @par Example Usage
 * @code{.c}
 *     TODO: ADD EXAMPLE CODE FOR `uint8_t hal_ll_gpio_read_pin_input(hal_ll_gpio_pin_t *pin)`
 * @endcode
 *
 * @par Limitations
 * - This function may return 0 if the pin base is not initialized.
 *
 * @see hal_ll_gpio_configure_pin()
 *
 * @link https://github.com/MikroElektronika/mikrosdk_v2/blob/master/targets/arm/mikroe/sam/include/gpio/hal_ll_gpio.h#L141 Link to header @endlink.
 * @link https://github.com/MikroElektronika/mikrosdk_v2/blob/master/targets/arm/mikroe/sam/src/gpio/hal_ll_gpio.c Link to source @endlink.
 */
#if defined(FLATTEN_ME) && (FLATTEN_ME_LEVEL >= FLATTEN_ME_LEVEL_LOW)
#define hal_ll_gpio_read_pin_input(_handle) ((((hal_ll_gpio_base_handle_t *)((hal_ll_gpio_pin_t *)_handle)->base) == 0) ? \
                                             (0) : (((hal_ll_gpio_base_handle_t *)((hal_ll_gpio_pin_t *)_handle)->base)->signal.pin_status & ((hal_ll_gpio_pin_t *)_handle)->mask) ? \
                                             (1) : (0))
#else
uint8_t hal_ll_gpio_read_pin_input(hal_ll_gpio_pin_t *pin);
#endif

/**
 * @brief Reads the output state of a GPIO pin.
 *
 * @details
 * This function returns the current logical output level of the specified GPIO pin.
 * It reads the pin status from the hardware port and masks it to obtain the pin output value.
 *
 * @param[in] pin Pointer to the GPIO pin structure to read.
 * See @ref hal_ll_gpio_pin_t structure definition for more details.
 *
 * @return
 * - 1 if the pin output is high.
 * - 0 if the pin output is low or if the pin base is NULL.
 *
 * @note
 * - The pin must be configured as output to get valid readings.
 *
 * @pre
 * - The pin must be properly configured and initialized.
 *
 * @post
 * - No side effects.
 *
 * @warning
 * - Reading a pin configured as input may not reflect the actual output state.
 *
 * @par Example Usage
 * @code{.c}
 *     TODO: ADD EXAMPLE CODE FOR `uint8_t hal_ll_gpio_read_pin_output(hal_ll_gpio_pin_t *pin)`
 * @endcode
 *
 * @par Limitations
 * - This function may return 0 if the pin base is not initialized.
 *
 * @see hal_ll_gpio_configure_pin()
 *
 * @link https://github.com/MikroElektronika/mikrosdk_v2/blob/master/targets/arm/mikroe/sam/include/gpio/hal_ll_gpio.h#L188 Link to header @endlink.
 * @link https://github.com/MikroElektronika/mikrosdk_v2/blob/master/targets/arm/mikroe/sam/src/gpio/hal_ll_gpio.c Link to source @endlink.
 */
#if defined(FLATTEN_ME) && (FLATTEN_ME_LEVEL >= FLATTEN_ME_LEVEL_LOW)
#define hal_ll_gpio_read_pin_output(_handle) ((((hal_ll_gpio_base_handle_t *)((hal_ll_gpio_pin_t *)_handle)->base) == 0) ? \
                                              (0) : (((hal_ll_gpio_base_handle_t *)((hal_ll_gpio_pin_t *)_handle)->base)->signal.pin_status & ((hal_ll_gpio_pin_t *)_handle)->mask) ? \
                                              (1) : (0))
#else
uint8_t hal_ll_gpio_read_pin_output(hal_ll_gpio_pin_t *pin);
#endif

/**
 * @brief Writes a logical output value to a GPIO pin.
 *
 * @details
 * This function sets the output state of the specified GPIO pin to high or low
 * depending on the provided value. It enables or disables the pin output accordingly.
 *
 * @param[in,out] pin Pointer to the GPIO pin structure to write.
 * See @ref hal_ll_gpio_pin_t structure definition for more details.
 * @param[in] value Logical value to write to the pin (non-zero for high, zero for low).
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
 * - The pin output state is updated to the specified value.
 *
 * @warning
 * - Writing to a pin configured as input may have no effect or cause undefined behavior.
 *
 * @par Example Usage
 * @code{.c}
 *     TODO: ADD EXAMPLE CODE FOR `void hal_ll_gpio_write_pin_output(hal_ll_gpio_pin_t *pin, uint8_t value)`
 * @endcode
 *
 * @par Limitations
 * - This function does not perform any validation on the value parameter.
 *
 * @see hal_ll_gpio_configure_pin()
 *
 * @link https://github.com/MikroElektronika/mikrosdk_v2/blob/master/targets/arm/mikroe/sam/include/gpio/hal_ll_gpio.h#L235 Link to header @endlink.
 * @link https://github.com/MikroElektronika/mikrosdk_v2/blob/master/targets/arm/mikroe/sam/src/gpio/hal_ll_gpio.c Link to source @endlink.
 */
#if defined(FLATTEN_ME) && (FLATTEN_ME_LEVEL >= FLATTEN_ME_LEVEL_LOW)
#define hal_ll_gpio_write_pin_output(_handle,_value) ((((hal_ll_gpio_base_handle_t *)((hal_ll_gpio_pin_t *)_handle)->base) != NULL) ? \
                                                          ((_value > 0) ? \
                                                           (((hal_ll_gpio_base_handle_t *)((hal_ll_gpio_pin_t *)_handle)->base)->signal.enable = ((hal_ll_gpio_pin_t *)_handle)->mask) : \
                                                           (((hal_ll_gpio_base_handle_t *)((hal_ll_gpio_pin_t *)_handle)->base)->signal.disable = ((hal_ll_gpio_pin_t *)_handle)->mask)) : \
                                                      (0))
#else
void hal_ll_gpio_write_pin_output(hal_ll_gpio_pin_t *pin, uint8_t value);
#endif

/**
 * @brief Toggles the output state of a GPIO pin.
 *
 * @details
 * This function inverts the current output state of the specified GPIO pin.
 * If the pin output is high, it will be set to low, and vice versa.
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
 * - Toggling a pin configured as input may have no effect or cause undefined behavior.
 *
 * @par Example Usage
 * @code{.c}
 *     TODO: ADD EXAMPLE CODE FOR `void hal_ll_gpio_toggle_pin_output(hal_ll_gpio_pin_t *pin)`
 * @endcode
 *
 * @par Limitations
 * - This function reads the pin output state before toggling, which may cause a slight delay.
 *
 * @see hal_ll_gpio_write_pin_output()
 * @see hal_ll_gpio_read_pin_output()
 *
 * @link https://github.com/MikroElektronika/mikrosdk_v2/blob/master/targets/arm/mikroe/sam/include/gpio/hal_ll_gpio.h#L284 Link to header @endlink.
 * @link https://github.com/MikroElektronika/mikrosdk_v2/blob/master/targets/arm/mikroe/sam/src/gpio/hal_ll_gpio.c Link to source @endlink.
 */
#if defined(FLATTEN_ME) && (FLATTEN_ME_LEVEL >= FLATTEN_ME_LEVEL_LOW)
#define hal_ll_gpio_toggle_pin_output(_handle) ((((hal_ll_gpio_base_handle_t *)((hal_ll_gpio_pin_t *)_handle)->base) != NULL) ? \
                                                    ((((((hal_ll_gpio_base_handle_t *)((hal_ll_gpio_pin_t *)_handle)->base)->signal.pin_status & ((hal_ll_gpio_pin_t *)_handle)->mask))) ? \
                                                     (((hal_ll_gpio_base_handle_t *)((hal_ll_gpio_pin_t *)_handle)->base)->signal.disable = ((hal_ll_gpio_pin_t *)_handle)->mask) : \
                                                     (((hal_ll_gpio_base_handle_t *)((hal_ll_gpio_pin_t *)_handle)->base)->signal.enable = ((hal_ll_gpio_pin_t *)_handle)->mask)) : \
                                                (0))
#else
void hal_ll_gpio_toggle_pin_output(hal_ll_gpio_pin_t *pin);
#endif

/**
 * @brief Sets the output state of a GPIO pin to high.
 *
 * @details
 * This function sets the specified GPIO pin output to a logical high level.
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
 * - The pin output state is set to high.
 *
 * @warning
 * - Setting a pin configured as input may have no effect or cause undefined behavior.
 *
 * @par Example Usage
 * @code{.c}
 *     TODO: ADD EXAMPLE CODE FOR `void hal_ll_gpio_set_pin_output(hal_ll_gpio_pin_t *pin)`
 * @endcode
 *
 * @par Limitations
 * - This function does not check the current state before setting.
 *
 * @see hal_ll_gpio_clear_pin_output()
 *
 * @link https://github.com/MikroElektronika/mikrosdk_v2/blob/master/targets/arm/mikroe/sam/include/gpio/hal_ll_gpio.h#L331 Link to header @endlink.
 * @link https://github.com/MikroElektronika/mikrosdk_v2/blob/master/targets/arm/mikroe/sam/src/gpio/hal_ll_gpio.c Link to source @endlink.
 */
#if defined(FLATTEN_ME) && (FLATTEN_ME_LEVEL >= FLATTEN_ME_LEVEL_LOW)
#define hal_ll_gpio_set_pin_output(_handle) ((((hal_ll_gpio_base_handle_t *)((hal_ll_gpio_pin_t *)_handle)->base) != NULL) ? \
                                             (((hal_ll_gpio_base_handle_t *)((hal_ll_gpio_pin_t *)_handle)->base)->signal.enable = ((hal_ll_gpio_pin_t *)_handle)->mask) : \
                                             (0))
#else
void hal_ll_gpio_set_pin_output(hal_ll_gpio_pin_t *pin);
#endif

/**
 * @brief Clears the output state of a GPIO pin to low.
 *
 * @details
 * This function sets the specified GPIO pin output to a logical low level.
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
 * - The pin output state is set to low.
 *
 * @warning
 * - Clearing a pin configured as input may have no effect or cause undefined behavior.
 *
 * @par Example Usage
 * @code{.c}
 *     TODO: ADD EXAMPLE CODE FOR `void hal_ll_gpio_clear_pin_output(hal_ll_gpio_pin_t *pin)`
 * @endcode
 *
 * @par Limitations
 * - This function does not check the current state before clearing.
 *
 * @see hal_ll_gpio_set_pin_output()
 *
 * @link https://github.com/MikroElektronika/mikrosdk_v2/blob/master/targets/arm/mikroe/sam/include/gpio/hal_ll_gpio.h#L376 Link to header @endlink.
 * @link https://github.com/MikroElektronika/mikrosdk_v2/blob/master/targets/arm/mikroe/sam/src/gpio/hal_ll_gpio.c Link to source @endlink.
 */
#if defined(FLATTEN_ME) && (FLATTEN_ME_LEVEL >= FLATTEN_ME_LEVEL_LOW)
#define hal_ll_gpio_clear_pin_output(_handle) ((((hal_ll_gpio_base_handle_t *)((hal_ll_gpio_pin_t *)_handle)->base) != NULL) ? \
                                               (((hal_ll_gpio_base_handle_t *)((hal_ll_gpio_pin_t *)_handle)->base)->signal.disable = ((hal_ll_gpio_pin_t *)_handle)->mask) : \
                                               (0))
#else
void hal_ll_gpio_clear_pin_output(hal_ll_gpio_pin_t *pin);
#endif

/**
 * @brief Configures a GPIO port with specified name, mask, and direction.
 *
 * @details
 * This function initializes the given GPIO port structure by setting its base port
 * and mask. It then configures the port pins specified by the mask as input or output.
 *
 * @param[in,out] port Pointer to the GPIO port structure to configure.
 * See @ref hal_ll_gpio_port_t structure definition for more details.
 * @param[in] name The identifier of the port to configure.
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
 * - Only pins specified in the mask are configured.
 *
 * @pre
 * - The hardware GPIO port corresponding to the port name must be available.
 *
 * @post
 * - The port structure is initialized and the specified pins are configured.
 *
 * @warning
 * - Configuring pins not available on the hardware port may cause undefined behavior.
 *
 * @par Example Usage
 * @code{.c}
 *     TODO: ADD EXAMPLE CODE FOR `void hal_ll_gpio_configure_port(hal_ll_gpio_port_t *port, hal_ll_port_name_t name, hal_ll_gpio_mask_t mask, hal_ll_gpio_direction_t direction)`
 * @endcode
 *
 * @par Limitations
 * - This function does not configure pull-up or pull-down resistors.
 *
 * @see hal_ll_gpio_port_t
 * @see hal_ll_port_name_t
 * @see hal_ll_gpio_mask_t
 * @see hal_ll_gpio_direction_t
 *
 * @link https://github.com/MikroElektronika/mikrosdk_v2/blob/master/targets/arm/mikroe/sam/include/gpio/hal_ll_gpio.h#L429 Link to header @endlink.
 * @link https://github.com/MikroElektronika/mikrosdk_v2/blob/master/targets/arm/mikroe/sam/src/gpio/hal_ll_gpio.c#L137 Link to source @endlink.
 */
void hal_ll_gpio_configure_port(hal_ll_gpio_port_t *port, hal_ll_port_name_t name, hal_ll_gpio_mask_t mask, hal_ll_gpio_direction_t direction);

/**
 * @brief Reads the input state of a GPIO port.
 *
 * @details
 * This function returns the current logical input levels of the specified GPIO port pins
 * as a bitmask. Only pins specified in the port mask are considered.
 *
 * @param[in] port Pointer to the GPIO port structure to read.
 * See @ref hal_ll_gpio_port_t structure definition for more details.
 *
 * @return
 * - Bitmask representing the input states of the port pins.
 * - Zero if the port base is NULL.
 *
 * @note
 * - The port pins must be configured as input to get valid readings.
 *
 * @pre
 * - The port must be properly configured and initialized.
 *
 * @post
 * - No side effects.
 *
 * @warning
 * - Reading pins configured as output may not reflect actual pin states.
 *
 * @par Example Usage
 * @code{.c}
 *     TODO: ADD EXAMPLE CODE FOR `hal_ll_port_size_t hal_ll_gpio_read_port_input(hal_ll_gpio_port_t *port)`
 * @endcode
 *
 * @par Limitations
 * - This function may return zero if the port base is not initialized.
 *
 * @see hal_ll_gpio_configure_port()
 *
 * @link https://github.com/MikroElektronika/mikrosdk_v2/blob/master/targets/arm/mikroe/sam/include/gpio/hal_ll_gpio.h#L472 Link to header @endlink.
 * @link https://github.com/MikroElektronika/mikrosdk_v2/blob/master/targets/arm/mikroe/sam/src/gpio/hal_ll_gpio.c Link to source @endlink.
 */
#if defined(FLATTEN_ME) && (FLATTEN_ME_LEVEL >= FLATTEN_ME_LEVEL_LOW)
#define hal_ll_gpio_read_port_input(_handle) ((((hal_ll_gpio_base_handle_t *)((hal_ll_gpio_port_t *)_handle)->base) != NULL) ? \
                                              ((hal_ll_port_size_t)((hal_ll_gpio_base_handle_t *)((hal_ll_gpio_port_t *)_handle)->base)->signal.pin_status & ((hal_ll_gpio_port_t *)_handle)->mask) : \
                                              (0))
#else
hal_ll_port_size_t hal_ll_gpio_read_port_input(hal_ll_gpio_port_t *port);
#endif

/**
 * @brief Reads the output state of a GPIO port.
 *
 * @details
 * This function returns the current logical output levels of the specified GPIO port pins
 * as a bitmask. Only pins specified in the port mask are considered.
 *
 * @param[in] port Pointer to the GPIO port structure to read.
 * See @ref hal_ll_gpio_port_t structure definition for more details.
 *
 * @return
 * - Bitmask representing the output states of the port pins.
 * - Zero if the port base is NULL.
 *
 * @note
 * - The port pins must be configured as output to get valid readings.
 *
 * @pre
 * - The port must be properly configured and initialized.
 *
 * @post
 * - No side effects.
 *
 * @warning
 * - Reading pins configured as input may not reflect actual output states.
 *
 * @par Example Usage
 * @code{.c}
 *     TODO: ADD EXAMPLE CODE FOR `hal_ll_port_size_t hal_ll_gpio_read_port_output(hal_ll_gpio_port_t *port)`
 * @endcode
 *
 * @par Limitations
 * - This function may return zero if the port base is not initialized.
 *
 * @see hal_ll_gpio_configure_port()
 *
 * @link https://github.com/MikroElektronika/mikrosdk_v2/blob/master/targets/arm/mikroe/sam/include/gpio/hal_ll_gpio.h#L519 Link to header @endlink.
 * @link https://github.com/MikroElektronika/mikrosdk_v2/blob/master/targets/arm/mikroe/sam/src/gpio/hal_ll_gpio.c Link to source @endlink.
 */
#if defined(FLATTEN_ME) && (FLATTEN_ME_LEVEL >= FLATTEN_ME_LEVEL_LOW)
#define hal_ll_gpio_read_port_output(_handle) ((((hal_ll_gpio_base_handle_t *)((hal_ll_gpio_port_t *)_handle)->base) != NULL) ? \
                                               ((hal_ll_port_size_t)(((hal_ll_gpio_base_handle_t *)((hal_ll_gpio_port_t *)_handle)->base)->signal.pin_status) & (((hal_ll_gpio_port_t *)_handle)->mask)) : \
                                               (0))
#else
hal_ll_port_size_t hal_ll_gpio_read_port_output(hal_ll_gpio_port_t *port);
#endif

/**
 * @brief Writes a logical output value to a GPIO port.
 *
 * @details
 * This function sets the output state of the specified GPIO port pins to the given value.
 * Only pins specified in the port mask are affected. Pins corresponding to bits set in the value
 * are set high, and pins corresponding to bits cleared in the value are set low.
 *
 * @param[in,out] port Pointer to the GPIO port structure to write.
 * See @ref hal_ll_gpio_port_t structure definition for more details.
 * @param[in] value Bitmask representing the output values to write to the port pins.
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
 * - The port output states are updated to the specified values.
 *
 * @warning
 * - Writing to pins configured as input may have no effect or cause undefined behavior.
 *
 * @par Example Usage
 * @code{.c}
 *     TODO: ADD EXAMPLE CODE FOR `void hal_ll_gpio_write_port_output(hal_ll_gpio_port_t *port, hal_ll_port_size_t value)`
 * @endcode
 *
 * @par Limitations
 * - This function does not perform validation on the value parameter.
 *
 * @see hal_ll_gpio_configure_port()
 *
 * @link https://github.com/MikroElektronika/mikrosdk_v2/blob/master/targets/arm/mikroe/sam/include/gpio/hal_ll_gpio.h#L567 Link to header @endlink.
 * @link https://github.com/MikroElektronika/mikrosdk_v2/blob/master/targets/arm/mikroe/sam/src/gpio/hal_ll_gpio.c Link to source @endlink.
 */
#if defined(FLATTEN_ME) && (FLATTEN_ME_LEVEL >= FLATTEN_ME_LEVEL_LOW)
#define hal_ll_gpio_write_port_output(_handle,_value) ((((hal_ll_gpio_base_handle_t *)((hal_ll_gpio_port_t *)_handle)->base) != NULL) ? \
                                                          (((hal_ll_gpio_base_handle_t *)((hal_ll_gpio_port_t *)_handle)->base)->signal.enable = \
                                                           ((hal_ll_port_size_t)_value & ((hal_ll_gpio_port_t *)_handle)->mask), \
                                                           ((hal_ll_gpio_base_handle_t *)((hal_ll_gpio_port_t *)_handle)->base)->signal.disable = \
                                                           (~(hal_ll_port_size_t)_value & ((hal_ll_gpio_port_t *)_handle)->mask)) : \
                                                       (0))
#else
void hal_ll_gpio_write_port_output(hal_ll_gpio_port_t *port, hal_ll_port_size_t value);
#endif

#ifdef __cplusplus
}
#endif

#endif // _HAL_LL_GPIO_H_
// ------------------------------------------------------------------------- END
