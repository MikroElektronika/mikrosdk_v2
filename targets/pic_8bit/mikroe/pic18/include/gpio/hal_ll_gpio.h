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
 * This function initializes the given GPIO pin structure by setting its base
 * address and mask according to the pin name. It configures the pin direction
 * as digital input, digital output, or analog input by calling the appropriate
 * port configuration functions.
 *
 * @param[out] pin Pointer to the GPIO pin structure to be configured.
 * See @ref hal_ll_gpio_pin_t structure definition for more details.
 * @param[in] name The pin name identifier used to determine port and pin mask.
 * See @ref hal_ll_pin_name_t type for valid pin names.
 * @param[in] direction The desired direction of the pin (input, output, analog).
 * See @ref hal_ll_gpio_direction_t enumeration for possible directions.
 *
 * @return
 * - None.
 *
 * @note
 * - If the pin name corresponds to an invalid port, the pin base is set to 0 and mask to HAL_LL_PIN_NC.
 * - The function assumes valid pin names and directions are provided.
 *
 * @pre
 * - The pin structure must be allocated before calling this function.
 *
 * @post
 * - The pin structure is initialized and the hardware pin is configured accordingly.
 *
 * @warning
 * - Passing invalid pin names may result in uninitialized pin structures.
 *
 * @par Example Usage
 * @code{.c}
 *     TODO: ADD EXAMPLE CODE FOR `void hal_ll_gpio_configure_pin(hal_ll_gpio_pin_t *pin, hal_ll_pin_name_t name, hal_ll_gpio_direction_t direction)`
 * @endcode
 *
 * @par Limitations
 * - Only supports digital input, digital output, and analog input directions.
 *
 * @see hal_ll_gpio_pin_t
 * @see hal_ll_pin_name_t
 * @see hal_ll_gpio_direction_t
 *
 * @link https://github.com/MikroElektronika/mikrosdk_v2/blob/master/targets/pic_8bit/mikroe/pic18/include/gpio/hal_ll_gpio.h#L101 Link to header @endlink.
 * @link https://github.com/MikroElektronika/mikrosdk_v2/blob/master/targets/pic_8bit/mikroe/pic18/src/gpio/implementation_1/hal_ll_gpio.c#L49 Link to source @endlink.
 */
void hal_ll_gpio_configure_pin(hal_ll_gpio_pin_t *pin, hal_ll_pin_name_t name, hal_ll_gpio_direction_t direction);

/**
 * @brief Reads the input state of a GPIO pin.
 *
 * @details
 * This function returns the current logical input level of the specified GPIO pin.
 * It reads the port input register and masks the bit corresponding to the pin.
 *
 * @param[in] pin Pointer to the GPIO pin structure to read from.
 * See @ref hal_ll_gpio_pin_t structure definition for more details.
 *
 * @return
 * - 1 if the pin input is high.
 * - 0 if the pin input is low or pin base is invalid.
 *
 * @note
 * - If the pin base is NULL or invalid, the function returns 0.
 *
 * @pre
 * - The pin must be configured as an input before calling this function.
 *
 * @post
 * - No side effects.
 *
 * @warning
 * - Reading from an uninitialized or invalid pin may return 0.
 *
 * @par Example Usage
 * @code{.c}
 *     TODO: ADD EXAMPLE CODE FOR `uint8_t hal_ll_gpio_read_pin_input(hal_ll_gpio_pin_t *pin)`
 * @endcode
 *
 * @par Limitations
 * - Only supports reading digital input state.
 *
 * @see hal_ll_gpio_pin_t
 * @see hal_ll_gpio_configure_pin()
 *
 * @link https://github.com/MikroElektronika/mikrosdk_v2/blob/master/targets/pic_8bit/mikroe/pic18/include/gpio/hal_ll_gpio.h#L145 Link to header @endlink.
 * @link https://github.com/MikroElektronika/mikrosdk_v2/blob/master/targets/pic_8bit/mikroe/pic18/src/gpio/implementation_1/hal_ll_gpio.c Link to source @endlink.
 */
#if defined(FLATTEN_ME) && (FLATTEN_ME_LEVEL >= FLATTEN_ME_LEVEL_LOW)
#define hal_ll_gpio_read_pin_input( _handle ) ((((hal_ll_gpio_base_handle_t *)((hal_ll_gpio_pin_t *)_handle)->base) == 0) ? \
                                               (0) : (*( uint8_t *)((hal_ll_gpio_base_handle_t *)((hal_ll_gpio_pin_t *)_handle)->base)->port_reg_addr & ((hal_ll_gpio_pin_t *)_handle)->mask) ? \
                                               (1) : (0))
#else
uint8_t hal_ll_gpio_read_pin_input(hal_ll_gpio_pin_t *pin);
#endif

/**
 * @brief Reads the output latch state of a GPIO pin.
 *
 * @details
 * This function returns the current logical output level latched on the specified GPIO pin.
 * It reads the port latch register and masks the bit corresponding to the pin.
 *
 * @param[in] pin Pointer to the GPIO pin structure to read from.
 * See @ref hal_ll_gpio_pin_t structure definition for more details.
 *
 * @return
 * - 1 if the pin output latch is set high.
 * - 0 if the pin output latch is low or pin base is invalid.
 *
 * @note
 * - If the pin base is NULL or invalid, the function returns 0.
 *
 * @pre
 * - The pin must be configured as an output before calling this function.
 *
 * @post
 * - No side effects.
 *
 * @warning
 * - Reading from an uninitialized or invalid pin may return 0.
 *
 * @par Example Usage
 * @code{.c}
 *     TODO: ADD EXAMPLE CODE FOR `uint8_t hal_ll_gpio_read_pin_output(hal_ll_gpio_pin_t *pin)`
 * @endcode
 *
 * @par Limitations
 * - Only supports reading digital output latch state.
 *
 * @see hal_ll_gpio_pin_t
 * @see hal_ll_gpio_configure_pin()
 *
 * @link https://github.com/MikroElektronika/mikrosdk_v2/blob/master/targets/pic_8bit/mikroe/pic18/include/gpio/hal_ll_gpio.h#L193 Link to header @endlink.
 * @link https://github.com/MikroElektronika/mikrosdk_v2/blob/master/targets/pic_8bit/mikroe/pic18/src/gpio/implementation_1/hal_ll_gpio.c Link to source @endlink.
 */
#if defined(FLATTEN_ME) && (FLATTEN_ME_LEVEL >= FLATTEN_ME_LEVEL_LOW)
#define hal_ll_gpio_read_pin_output( _handle ) ((((hal_ll_gpio_base_handle_t *)((hal_ll_gpio_pin_t *)_handle)->base) == 0) ? \
                                                (0) : (*( uint8_t *)((hal_ll_gpio_base_handle_t *)((hal_ll_gpio_pin_t *)_handle)->base)->lat_reg_addr, ((hal_ll_gpio_pin_t *)_handle)->mask) ? \
                                                (1) : (0))
#else
uint8_t hal_ll_gpio_read_pin_output(hal_ll_gpio_pin_t *pin);
#endif

/**
 * @brief Sets the output state of a GPIO pin.
 *
 * @details
 * This function sets or clears the output latch of the specified GPIO pin
 * according to the provided value. A non-zero value sets the pin high, zero clears it.
 *
 * @param[in,out] pin Pointer to the GPIO pin structure to modify.
 * See @ref hal_ll_gpio_pin_t structure definition for more details.
 * @param[in] value The output value to set: non-zero for high, zero for low.
 *
 * @return
 * - None.
 *
 * @note
 * - If the pin base is NULL or invalid, the function does nothing.
 *
 * @pre
 * - The pin must be configured as an output before calling this function.
 *
 * @post
 * - The pin output latch is updated to the specified value.
 *
 * @warning
 * - Writing to an uninitialized or invalid pin has no effect.
 *
 * @par Example Usage
 * @code{.c}
 *     TODO: ADD EXAMPLE CODE FOR `void hal_ll_gpio_write_pin_output(hal_ll_gpio_pin_t *pin, uint8_t value)`
 * @endcode
 *
 * @par Limitations
 * - Only supports digital output values.
 *
 * @see hal_ll_gpio_pin_t
 * @see hal_ll_gpio_configure_pin()
 *
 * @link https://github.com/MikroElektronika/mikrosdk_v2/blob/master/targets/pic_8bit/mikroe/pic18/include/gpio/hal_ll_gpio.h#L241 Link to header @endlink.
 * @link https://github.com/MikroElektronika/mikrosdk_v2/blob/master/targets/pic_8bit/mikroe/pic18/src/gpio/implementation_1/hal_ll_gpio.c Link to source @endlink.
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
 * @brief Toggles the output state of a GPIO pin.
 *
 * @details
 * This function reads the current output latch state of the specified GPIO pin
 * and writes the inverse value, effectively toggling the pin output.
 *
 * @param[in,out] pin Pointer to the GPIO pin structure to toggle.
 * See @ref hal_ll_gpio_pin_t structure definition for more details.
 *
 * @return
 * - None.
 *
 * @note
 * - If the pin base is NULL or invalid, the function does nothing.
 *
 * @pre
 * - The pin must be configured as an output before calling this function.
 *
 * @post
 * - The pin output latch is toggled.
 *
 * @warning
 * - Toggling an uninitialized or invalid pin has no effect.
 *
 * @par Example Usage
 * @code{.c}
 *     TODO: ADD EXAMPLE CODE FOR `void hal_ll_gpio_toggle_pin_output(hal_ll_gpio_pin_t *pin)`
 * @endcode
 *
 * @par Limitations
 * - Only supports digital output toggling.
 *
 * @see hal_ll_gpio_pin_t
 * @see hal_ll_gpio_write_pin_output()
 *
 * @link https://github.com/MikroElektronika/mikrosdk_v2/blob/master/targets/pic_8bit/mikroe/pic18/include/gpio/hal_ll_gpio.h#L290 Link to header @endlink.
 * @link https://github.com/MikroElektronika/mikrosdk_v2/blob/master/targets/pic_8bit/mikroe/pic18/src/gpio/implementation_1/hal_ll_gpio.c Link to source @endlink.
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
 * This function sets the output latch bit of the specified GPIO pin, driving the pin output high.
 *
 * @param[in,out] pin Pointer to the GPIO pin structure to modify.
 * See @ref hal_ll_gpio_pin_t structure definition for more details.
 *
 * @return
 * - None.
 *
 * @note
 * - If the pin base is NULL or invalid, the function does nothing.
 *
 * @pre
 * - The pin must be configured as an output before calling this function.
 *
 * @post
 * - The pin output latch is set high.
 *
 * @warning
 * - Setting an uninitialized or invalid pin has no effect.
 *
 * @par Example Usage
 * @code{.c}
 *     TODO: ADD EXAMPLE CODE FOR `void hal_ll_gpio_set_pin_output(hal_ll_gpio_pin_t *pin)`
 * @endcode
 *
 * @par Limitations
 * - Only supports setting digital output high.
 *
 * @see hal_ll_gpio_pin_t
 * @see hal_ll_gpio_clear_pin_output()
 *
 * @link https://github.com/MikroElektronika/mikrosdk_v2/blob/master/targets/pic_8bit/mikroe/pic18/include/gpio/hal_ll_gpio.h#L338 Link to header @endlink.
 * @link https://github.com/MikroElektronika/mikrosdk_v2/blob/master/targets/pic_8bit/mikroe/pic18/src/gpio/implementation_1/hal_ll_gpio.c Link to source @endlink.
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
 * This function clears the output latch bit of the specified GPIO pin, driving the pin output low.
 *
 * @param[in,out] pin Pointer to the GPIO pin structure to modify.
 * See @ref hal_ll_gpio_pin_t structure definition for more details.
 *
 * @return
 * - None.
 *
 * @note
 * - If the pin base is NULL or invalid, the function does nothing.
 *
 * @pre
 * - The pin must be configured as an output before calling this function.
 *
 * @post
 * - The pin output latch is cleared low.
 *
 * @warning
 * - Clearing an uninitialized or invalid pin has no effect.
 *
 * @par Example Usage
 * @code{.c}
 *     TODO: ADD EXAMPLE CODE FOR `void hal_ll_gpio_clear_pin_output(hal_ll_gpio_pin_t *pin)`
 * @endcode
 *
 * @par Limitations
 * - Only supports clearing digital output low.
 *
 * @see hal_ll_gpio_pin_t
 * @see hal_ll_gpio_set_pin_output()
 *
 * @link https://github.com/MikroElektronika/mikrosdk_v2/blob/master/targets/pic_8bit/mikroe/pic18/include/gpio/hal_ll_gpio.h#L384 Link to header @endlink.
 * @link https://github.com/MikroElektronika/mikrosdk_v2/blob/master/targets/pic_8bit/mikroe/pic18/src/gpio/implementation_1/hal_ll_gpio.c Link to source @endlink.
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
 * This function initializes the given GPIO port structure by setting its base
 * address and mask according to the port name. It configures the port pins
 * specified by the mask as digital input or output.
 *
 * @param[out] port Pointer to the GPIO port structure to be configured.
 * See @ref hal_ll_gpio_port_t structure definition for more details.
 * @param[in] name The port name identifier used to determine port base.
 * See @ref hal_ll_port_name_t type for valid port names.
 * @param[in] mask Bitmask specifying which pins of the port to configure.
 * See @ref hal_ll_gpio_mask_t type for mask details.
 * @param[in] direction The desired direction of the port pins (input or output).
 * See @ref hal_ll_gpio_direction_t enumeration for possible directions.
 *
 * @return
 * - None.
 *
 * @note
 * - If the port name is invalid, the port base is set to 0 and mask to HAL_LL_PIN_NC.
 * - Only digital input and output directions are supported for ports.
 *
 * @pre
 * - The port structure must be allocated before calling this function.
 *
 * @post
 * - The port structure is initialized and the hardware port pins are configured accordingly.
 *
 * @warning
 * - Passing invalid port names may result in uninitialized port structures.
 *
 * @par Example Usage
 * @code{.c}
 *     TODO: ADD EXAMPLE CODE FOR `void hal_ll_gpio_configure_port(hal_ll_gpio_port_t *port, hal_ll_port_name_t name, hal_ll_gpio_mask_t mask, hal_ll_gpio_direction_t direction)`
 * @endcode
 *
 * @par Limitations
 * - Analog input direction is not supported for ports.
 *
 * @see hal_ll_gpio_port_t
 * @see hal_ll_port_name_t
 * @see hal_ll_gpio_direction_t
 *
 * @link https://github.com/MikroElektronika/mikrosdk_v2/blob/master/targets/pic_8bit/mikroe/pic18/include/gpio/hal_ll_gpio.h#L438 Link to header @endlink.
 * @link https://github.com/MikroElektronika/mikrosdk_v2/blob/master/targets/pic_8bit/mikroe/pic18/src/gpio/implementation_1/hal_ll_gpio.c#L135 Link to source @endlink.
 */
void hal_ll_gpio_configure_port(hal_ll_gpio_port_t *port, hal_ll_port_name_t name, hal_ll_gpio_mask_t mask, hal_ll_gpio_direction_t direction);

/**
 * @brief Reads the input state of a GPIO port.
 *
 * @details
 * This function returns the current logical input levels of the specified GPIO port pins
 * as a bitmask. It reads the port input register and masks the bits according to the port mask.
 *
 * @param[in] port Pointer to the GPIO port structure to read from.
 * See @ref hal_ll_gpio_port_t structure definition for more details.
 *
 * @return
 * - Bitmask representing the input states of the port pins specified by the mask.
 * - 0 if the port base is invalid.
 *
 * @note
 * - If the port base is NULL or invalid, the function returns 0.
 *
 * @pre
 * - The port must be configured as input before calling this function.
 *
 * @post
 * - No side effects.
 *
 * @warning
 * - Reading from an uninitialized or invalid port may return 0.
 *
 * @par Example Usage
 * @code{.c}
 *     TODO: ADD EXAMPLE CODE FOR `hal_ll_port_size_t hal_ll_gpio_read_port_input(hal_ll_gpio_port_t *port)`
 * @endcode
 *
 * @par Limitations
 * - Only supports reading digital input states.
 *
 * @see hal_ll_gpio_port_t
 * @see hal_ll_gpio_configure_port()
 *
 * @link https://github.com/MikroElektronika/mikrosdk_v2/blob/master/targets/pic_8bit/mikroe/pic18/include/gpio/hal_ll_gpio.h#L482 Link to header @endlink.
 * @link https://github.com/MikroElektronika/mikrosdk_v2/blob/master/targets/pic_8bit/mikroe/pic18/src/gpio/implementation_1/hal_ll_gpio.c Link to source @endlink.
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
 * This function returns the current logical output latch levels of the specified GPIO port pins
 * as a bitmask. It reads the port latch register and masks the bits according to the port mask.
 *
 * @param[in] port Pointer to the GPIO port structure to read from.
 * See @ref hal_ll_gpio_port_t structure definition for more details.
 *
 * @return
 * - Bitmask representing the output latch states of the port pins specified by the mask.
 * - 0 if the port base is invalid.
 *
 * @note
 * - If the port base is NULL or invalid, the function returns 0.
 *
 * @pre
 * - The port must be configured as output before calling this function.
 *
 * @post
 * - No side effects.
 *
 * @warning
 * - Reading from an uninitialized or invalid port may return 0.
 *
 * @par Example Usage
 * @code{.c}
 *     TODO: ADD EXAMPLE CODE FOR `hal_ll_port_size_t hal_ll_gpio_read_port_output(hal_ll_gpio_port_t *port)`
 * @endcode
 *
 * @par Limitations
 * - Only supports reading digital output latch states.
 *
 * @see hal_ll_gpio_port_t
 * @see hal_ll_gpio_configure_port()
 *
 * @link https://github.com/MikroElektronika/mikrosdk_v2/blob/master/targets/pic_8bit/mikroe/pic18/include/gpio/hal_ll_gpio.h#L530 Link to header @endlink.
 * @link https://github.com/MikroElektronika/mikrosdk_v2/blob/master/targets/pic_8bit/mikroe/pic18/src/gpio/implementation_1/hal_ll_gpio.c Link to source @endlink.
 */
#if defined(FLATTEN_ME) && (FLATTEN_ME_LEVEL >= FLATTEN_ME_LEVEL_LOW)
#define hal_ll_gpio_read_port_output( _handle ) ((((hal_ll_gpio_base_handle_t *)((hal_ll_gpio_port_t *)_handle)->base) != NULL) ? \
                                                 (read_reg_bits(((hal_ll_gpio_base_handle_t *)((hal_ll_gpio_port_t *)_handle)->base)->lat_reg_addr, ((hal_ll_gpio_port_t *)_handle)->mask)) : \
                                                 (0))
#else
hal_ll_port_size_t hal_ll_gpio_read_port_output(hal_ll_gpio_port_t *port);
#endif

/**
 * @brief Writes output values to a GPIO port.
 *
 * @details
 * This function writes the specified bitmask value to the output latch of the GPIO port,
 * affecting only the pins specified by the port mask. It preserves the state of other pins.
 *
 * @param[in,out] port Pointer to the GPIO port structure to modify.
 * See @ref hal_ll_gpio_port_t structure definition for more details.
 * @param[in] value Bitmask representing the output values to set on the port pins.
 *
 * @return
 * - None.
 *
 * @note
 * - If the port base is NULL or invalid, the function does nothing.
 *
 * @pre
 * - The port must be configured as output before calling this function.
 *
 * @post
 * - The port output latch is updated with the specified values on masked pins.
 *
 * @warning
 * - Writing to an uninitialized or invalid port has no effect.
 *
 * @par Example Usage
 * @code{.c}
 *     TODO: ADD EXAMPLE CODE FOR `void hal_ll_gpio_write_port_output(hal_ll_gpio_port_t *port, hal_ll_port_size_t value)`
 * @endcode
 *
 * @par Limitations
 * - Only supports digital output values.
 *
 * @see hal_ll_gpio_port_t
 * @see hal_ll_gpio_configure_port()
 *
 * @link https://github.com/MikroElektronika/mikrosdk_v2/blob/master/targets/pic_8bit/mikroe/pic18/include/gpio/hal_ll_gpio.h#L578 Link to header @endlink.
 * @link https://github.com/MikroElektronika/mikrosdk_v2/blob/master/targets/pic_8bit/mikroe/pic18/src/gpio/implementation_1/hal_ll_gpio.c Link to source @endlink.
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
