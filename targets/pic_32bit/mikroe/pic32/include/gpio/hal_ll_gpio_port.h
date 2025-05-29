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

typedef struct
{
    hal_ll_base_addr_t port_reg_addr;
    hal_ll_base_addr_t lat_reg_addr;
    hal_ll_base_addr_t tris_reg_addr;
} hal_ll_gpio_base_handle_t;

/**
 * @brief Type definition for GPIO base handle.
 *
 * @details
 * This type represents a handle to a GPIO base, used for identifying and
 * managing GPIO ports or pins.
 */
typedef handle_t hal_ll_gpio_base_t;

/**
 * @brief Enumeration for GPIO pin direction.
 *
 * @details
 * This enumeration defines the possible directions for a GPIO pin, either
 * digital input or digital output.
 */
typedef enum
{
    HAL_LL_GPIO_DIGITAL_INPUT = 0,
    HAL_LL_GPIO_DIGITAL_OUTPUT = 1
} hal_ll_gpio_direction_t;

/**
 * @brief Structure representing a GPIO pin or port.
 *
 * @details
 * This structure encapsulates a GPIO base handle and a mask representing
 * the specific pin(s) within the port. It is used to identify and manipulate
 * individual pins or groups of pins on a GPIO port.
 */
typedef struct hal_ll_gpio
{
    hal_ll_gpio_base_t base;
    hal_ll_gpio_mask_t mask;
} hal_ll_gpio_t;

/**
 * @brief Type definition for GPIO pin.
 *
 * @details
 * This type is an alias for hal_ll_gpio_t and represents a single GPIO pin.
 */
typedef hal_ll_gpio_t hal_ll_gpio_pin_t;

/**
 * @brief Type definition for GPIO port.
 *
 * @details
 * This type is an alias for hal_ll_gpio_t and represents a GPIO port.
 */
typedef hal_ll_gpio_t hal_ll_gpio_port_t;

/**
 * @brief Get the index of the GPIO port for a given pin name.
 *
 * @details
 * This function calculates and returns the index of the GPIO port to which
 * the specified pin belongs. The index is derived by dividing the pin name
 * by the port size.
 *
 * @param[in] name The pin name for which to get the port index.
 * See @ref hal_ll_pin_name_t for more details.
 *
 * @return
 * The index of the GPIO port as an 8-bit unsigned integer.
 *
 * @note
 * The port size is assumed to be a constant defining the number of pins per port.
 *
 * @pre
 * The pin name must be valid and correspond to an existing GPIO pin.
 *
 * @post
 * None.
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
 * - Assumes pin names are encoded such that division by PORT_SIZE yields port index.
 *
 * @see hal_ll_gpio_port_pin_mask()
 * @see hal_ll_gpio_port_base_map()
 *
 * @link https://github.com/MikroElektronika/mikrosdk_v2/blob/master/targets/pic_32bit/mikroe/pic32/include/gpio/hal_ll_gpio_port.h#L153 Link to header @endlink.
 * @link https://github.com/MikroElektronika/mikrosdk_v2/blob/master/targets/pic_32bit/mikroe/pic32/src/gpio/implementation_1/subimplementation_1/hal_ll_gpio_port.c#L154 Link to source @endlink.
 */
uint8_t hal_ll_gpio_port_index( hal_ll_pin_name_t name );

/**
 * @brief Get the pin mask for a given GPIO pin name.
 *
 * @details
 * This function returns a 32-bit mask with a single bit set corresponding to
 * the position of the specified pin within its port. The mask can be used to
 * manipulate or query the pin state in port registers.
 *
 * @param[in] name The pin name for which to get the mask.
 * See @ref hal_ll_pin_name_t for more details.
 *
 * @return
 * A 32-bit unsigned integer mask with the bit set for the specified pin.
 *
 * @note
 * The pin index within the port is calculated internally.
 *
 * @pre
 * The pin name must be valid and correspond to an existing GPIO pin.
 *
 * @post
 * None.
 *
 * @warning
 * Passing an invalid pin name may result in undefined behavior.
 *
 * @par Example Usage
 * @code{.c}
 *    // Get pin mask. *    hal_ll_gpio_port_pin_mask( GPIO_PB2 );
 * @endcode
 *
 * @par Limitations
 * - Assumes pin names are encoded such that pin index can be derived.
 *
 * @see hal_ll_gpio_port_index()
 * @see hal_ll_gpio_port_base_map()
 *
 * @link https://github.com/MikroElektronika/mikrosdk_v2/blob/master/targets/pic_32bit/mikroe/pic32/include/gpio/hal_ll_gpio_port.h#L195 Link to header @endlink.
 * @link https://github.com/MikroElektronika/mikrosdk_v2/blob/master/targets/pic_32bit/mikroe/pic32/src/gpio/implementation_1/subimplementation_1/hal_ll_gpio_port.c#L158 Link to source @endlink.
 */
uint32_t hal_ll_gpio_port_pin_mask( hal_ll_pin_name_t name );

/**
 * @brief Get the base address mapping for a given GPIO port name.
 *
 * @details
 * This function returns the base address of the GPIO port structure associated
 * with the specified port name. This base address is used to access the port's
 * registers for configuration and data operations.
 *
 * @param[in] name The GPIO port name.
 * See @ref hal_ll_port_name_t for more details.
 *
 * @return
 * The base address of the GPIO port as a 32-bit unsigned integer.
 *
 * @note
 * The returned address points to a hal_ll_gpio_base_handle_t structure.
 *
 * @pre
 * The port name must be valid and correspond to an existing GPIO port.
 *
 * @post
 * None.
 *
 * @warning
 * Passing an invalid port name may result in undefined behavior.
 *
 * @par Example Usage
 * @code{.c}
 *    // Get the base address map of a GPIO port. *    hal_ll_gpio_port_base_map( PORTB );
 * @endcode
 *
 * @par Limitations
 * - Assumes port names are valid and mapped in the internal port address array.
 *
 * @see hal_ll_gpio_port_index()
 * @see hal_ll_gpio_port_pin_mask()
 *
 * @link https://github.com/MikroElektronika/mikrosdk_v2/blob/master/targets/pic_32bit/mikroe/pic32/include/gpio/hal_ll_gpio_port.h#L237 Link to header @endlink.
 * @link https://github.com/MikroElektronika/mikrosdk_v2/blob/master/targets/pic_32bit/mikroe/pic32/src/gpio/implementation_1/subimplementation_1/hal_ll_gpio_port.c#L162 Link to source @endlink.
 */
uint32_t hal_ll_gpio_port_base_map( hal_ll_port_name_t name );

/**
 * @brief Configure specified pins on a port as analog inputs.
 *
 * @details
 * This function configures the pins specified by the pin mask on the given port
 * to operate as analog inputs. It sets the appropriate registers to enable
 * analog functionality on those pins.
 *
 * @param[in,out] port Pointer to the base address of the GPIO port registers.
 * See @ref hal_ll_gpio_base_handle_t for more details.
 * @param[in] pin_mask Bitmask specifying which pins to configure as analog inputs.
 * See @ref hal_ll_gpio_mask_t for more details.
 *
 * @return
 * None.
 *
 * @note
 * This function affects only the pins specified in the pin_mask.
 *
 * @pre
 * The port pointer must be valid and point to a GPIO port register structure.
 *
 * @post
 * The specified pins are configured as analog inputs.
 *
 * @warning
 * Configuring pins as analog inputs may disable their digital functionality.
 *
 * @par Example Usage
 * @code{.c}
 *    // Set pin 0 (mask 0x01) of PORTB as analog input. *    hal_ll_gpio_port_analog_input( hal_ll_gpio_port_base( PORTB ), 0x01 );
 * @endcode
 *
 * @par Limitations
 * - Only pins supporting analog input can be configured successfully.
 *
 * @see hal_ll_gpio_port_digital_input()
 * @see hal_ll_gpio_port_digital_output()
 *
 * @link https://github.com/MikroElektronika/mikrosdk_v2/blob/master/targets/pic_32bit/mikroe/pic32/include/gpio/hal_ll_gpio_port.h#L281 Link to header @endlink.
 * @link https://github.com/MikroElektronika/mikrosdk_v2/blob/master/targets/pic_32bit/mikroe/pic32/src/gpio/implementation_1/subimplementation_1/hal_ll_gpio_port.c#L166 Link to source @endlink.
 */
void hal_ll_gpio_port_analog_input( uint32_t *port, uint16_t pin_mask );

/**
 * @brief Configure specified pins on a port as digital inputs.
 *
 * @details
 * This function configures the pins specified by the pin mask on the given port
 * to operate as digital inputs. It sets the appropriate registers to enable
 * digital input functionality on those pins.
 *
 * @param[in,out] port Pointer to the base address of the GPIO port registers.
 * See @ref hal_ll_gpio_base_handle_t for more details.
 * @param[in] pin_mask Bitmask specifying which pins to configure as digital inputs.
 * See @ref hal_ll_gpio_mask_t for more details.
 *
 * @return
 * None.
 *
 * @note
 * This function affects only the pins specified in the pin_mask.
 *
 * @pre
 * The port pointer must be valid and point to a GPIO port register structure.
 *
 * @post
 * The specified pins are configured as digital inputs.
 *
 * @warning
 * Configuring pins as digital inputs may disable their analog functionality.
 *
 * @par Example Usage
 * @code{.c}
 *    // Set pin 0 (mask 0x01) of PORTB as digital input. *    hal_ll_gpio_port_digital_input( hal_ll_gpio_port_base( PORTB ), 0x01 );
 * @endcode
 *
 * @par Limitations
 * - Only pins supporting digital input can be configured successfully.
 *
 * @see hal_ll_gpio_port_analog_input()
 * @see hal_ll_gpio_port_digital_output()
 *
 * @link https://github.com/MikroElektronika/mikrosdk_v2/blob/master/targets/pic_32bit/mikroe/pic32/include/gpio/hal_ll_gpio_port.h#L325 Link to header @endlink.
 * @link https://github.com/MikroElektronika/mikrosdk_v2/blob/master/targets/pic_32bit/mikroe/pic32/src/gpio/implementation_1/subimplementation_1/hal_ll_gpio_port.c#L170 Link to source @endlink.
 */
void hal_ll_gpio_port_digital_input( uint32_t *port, uint16_t pin_mask );

/**
 * @brief Configure specified pins on a port as digital inputs or outputs.
 *
 * @details
 * This function configures the pins specified by the mask in the given GPIO port
 * structure as either digital inputs or digital outputs based on the is_input flag.
 * It also manages the analog/digital configuration for pins that support analog input.
 *
 * @param[in,out] port Pointer to the GPIO port structure to configure.
 * See @ref hal_ll_gpio_port_t for more details.
 * @param[in] name The name/index of the port to configure.
 * See @ref hal_ll_port_name_t for more details.
 * @param[in] is_input Boolean flag indicating direction:
 * - true: configure pins as digital inputs.
 * - false: configure pins as digital outputs.
 *
 * @return
 * None.
 *
 * @note
 * This function clears the latch bits for the pins before configuring direction.
 * It also sets the analog/digital configuration bits appropriately.
 *
 * @pre
 * The port pointer must be valid and initialized.
 *
 * @post
 * The specified pins are configured as digital inputs or outputs.
 *
 * @warning
 * Pins configured as digital inputs will have their analog functionality disabled.
 *
 * @par Example Usage
 * @code{.c}
 *    hal_ll_gpio_port_t *port; *    // Set port PORTB as output. *    hal_ll_gpio_port_digital_configure_port( port, PORTB, false );
 * @endcode
 *
 * @par Limitations
 * - Only pins supporting digital I/O can be configured successfully.
 *
 * @see hal_ll_gpio_port_analog_input()
 * @see hal_ll_gpio_port_digital_input()
 * @see hal_ll_gpio_port_digital_output()
 *
 * @link https://github.com/MikroElektronika/mikrosdk_v2/blob/master/targets/pic_32bit/mikroe/pic32/include/gpio/hal_ll_gpio_port.h#L374 Link to header @endlink.
 * @link https://github.com/MikroElektronika/mikrosdk_v2/blob/master/targets/pic_32bit/mikroe/pic32/src/gpio/implementation_1/subimplementation_1/hal_ll_gpio_port.c#L174 Link to source @endlink.
 */
void hal_ll_gpio_port_digital_configure_port( hal_ll_gpio_port_t *port, uint8_t name, bool is_input );

/**
 * @brief Configure specified pins on a port as digital outputs.
 *
 * @details
 * This function configures the pins specified by the pin mask on the given port
 * to operate as digital outputs. It sets the appropriate registers to enable
 * digital output functionality on those pins.
 *
 * @param[in,out] port Pointer to the base address of the GPIO port registers.
 * See @ref hal_ll_gpio_base_handle_t for more details.
 * @param[in] pin Bitmask specifying which pins to configure as digital outputs.
 * See @ref hal_ll_gpio_mask_t for more details.
 *
 * @return
 * None.
 *
 * @note
 * This function clears the latch bits for the pins before configuring direction.
 *
 * @pre
 * The port pointer must be valid and point to a GPIO port register structure.
 *
 * @post
 * The specified pins are configured as digital outputs.
 *
 * @warning
 * Configuring pins as digital outputs may disable their analog functionality.
 *
 * @par Example Usage
 * @code{.c}
 *    // Set pin 0 (mask 0x01) of PORTB as digital output. *    hal_ll_gpio_port_digital_output( hal_ll_gpio_port_base( PORTB ), 0x01 );
 * @endcode
 *
 * @par Limitations
 * - Only pins supporting digital output can be configured successfully.
 *
 * @see hal_ll_gpio_port_analog_input()
 * @see hal_ll_gpio_port_digital_input()
 *
 * @link https://github.com/MikroElektronika/mikrosdk_v2/blob/master/targets/pic_32bit/mikroe/pic32/include/gpio/hal_ll_gpio_port.h#L418 Link to header @endlink.
 * @link https://github.com/MikroElektronika/mikrosdk_v2/blob/master/targets/pic_32bit/mikroe/pic32/src/gpio/implementation_1/subimplementation_1/hal_ll_gpio_port.c#L206 Link to source @endlink.
 */
void hal_ll_gpio_port_digital_output( uint32_t *port, uint16_t pin );

#ifdef __cplusplus
}
#endif

#endif // _HAL_LL_GPIO_PORT_H_
// ------------------------------------------------------------------------- END
