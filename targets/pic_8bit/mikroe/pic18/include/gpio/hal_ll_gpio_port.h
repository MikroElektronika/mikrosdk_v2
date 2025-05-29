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
 * @brief Handle and mask types.
 *
 * @details
 * This typedef defines hal_ll_gpio_base_t as a handle type used for GPIO base identification.
 */
typedef handle_t hal_ll_gpio_base_t;

typedef enum
{
    HAL_LL_GPIO_DIGITAL_INPUT = 0,
    HAL_LL_GPIO_DIGITAL_OUTPUT = 1
} hal_ll_gpio_direction_t;

/**
 * @brief Structure representing a GPIO pin or port.
 *
 * @details
 * This structure contains a base handle and a mask to identify specific pins within a GPIO port.
 */
typedef struct hal_ll_gpio_t
{
    hal_ll_gpio_base_t base;
    hal_ll_gpio_mask_t mask;
};

/**
 * @brief Pin and port data types.
 *
 * @details
 * These typedefs define aliases for GPIO pin and port types based on hal_ll_gpio_t structure.
 */
typedef struct hal_ll_gpio_t hal_ll_gpio_pin_t;
typedef struct hal_ll_gpio_t hal_ll_gpio_port_t;

/**
 * @brief Get the index of the GPIO port for a given pin name.
 *
 * @details
 * This function returns the index of the GPIO port associated with the specified pin name.
 * The index corresponds to the position of the port in the internal port list.
 *
 * @param[in] name The pin name identifier.
 *
 * @return
 * The index of the GPIO port as an 8-bit unsigned integer.
 *
 * @note
 * The pin name must be valid and correspond to a known GPIO port.
 *
 * @pre
 * The GPIO system must be initialized.
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
 * - Only valid pin names are supported.
 *
 * @see hal_ll_gpio_port_pin_mask()
 * @see hal_ll_gpio_port_base_map()
 *
 * @link https://github.com/MikroElektronika/mikrosdk_v2/blob/master/targets/pic_8bit/mikroe/pic18/include/gpio/hal_ll_gpio_port.h#L134 Link to header @endlink.
 * @link https://github.com/MikroElektronika/mikrosdk_v2/blob/master/targets/pic_8bit/mikroe/pic18/src/gpio/implementation_1/subimplementation_1/hal_ll_gpio_port.c#L136 Link to source @endlink.
 */
uint8_t hal_ll_gpio_port_index( hal_ll_pin_name_t name );

/**
 * @brief Get the pin mask for a given pin name within its port.
 *
 * @details
 * This function returns a bitmask representing the position of the specified
 * pin within its GPIO port. The mask can be used to manipulate or query the
 * pin state in port registers.
 *
 * @param[in] name The pin name identifier.
 *
 * @return
 * An 8-bit mask with a single bit set corresponding to the pin position.
 *
 * @note
 * The pin name must be valid and correspond to a known GPIO port and pin.
 *
 * @pre
 * The GPIO system must be initialized.
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
 * - Only valid pin names are supported.
 *
 * @see hal_ll_gpio_port_index()
 * @see hal_ll_gpio_port_base_map()
 *
 * @link https://github.com/MikroElektronika/mikrosdk_v2/blob/master/targets/pic_8bit/mikroe/pic18/include/gpio/hal_ll_gpio_port.h#L175 Link to header @endlink.
 * @link https://github.com/MikroElektronika/mikrosdk_v2/blob/master/targets/pic_8bit/mikroe/pic18/src/gpio/implementation_1/subimplementation_1/hal_ll_gpio_port.c#L145 Link to source @endlink.
 */
uint8_t hal_ll_gpio_port_pin_mask( hal_ll_pin_name_t name );

/**
 * @brief Get the base address map for a given GPIO port.
 *
 * @details
 * This function returns the base address of the GPIO port registers
 * corresponding to the specified port name. The returned address points
 * to the structure containing port, latch, and tristate register addresses.
 *
 * @param[in] name The GPIO port name identifier.
 *
 * @return
 * The base address of the GPIO port register map as a 16-bit unsigned integer.
 *
 * @note
 * The port name must be valid and correspond to a known GPIO port.
 *
 * @pre
 * The GPIO system must be initialized.
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
 * - Only valid port names are supported.
 *
 * @see hal_ll_gpio_port_index()
 * @see hal_ll_gpio_port_pin_mask()
 *
 * @link https://github.com/MikroElektronika/mikrosdk_v2/blob/master/targets/pic_8bit/mikroe/pic18/include/gpio/hal_ll_gpio_port.h#L216 Link to header @endlink.
 * @link https://github.com/MikroElektronika/mikrosdk_v2/blob/master/targets/pic_8bit/mikroe/pic18/src/gpio/implementation_1/subimplementation_1/hal_ll_gpio_port.c#L154 Link to source @endlink.
 */
uint16_t hal_ll_gpio_port_base_map( hal_ll_port_name_t name );

/**
 * @brief Configure specified pins of a GPIO port as analog inputs.
 *
 * @details
 * This function configures the pins specified by the pin mask on the given
 * port to operate as analog inputs. It modifies the port registers to set
 * the pins to analog mode.
 *
 * @param[in,out] port Pointer to the base address of the GPIO port registers.
 * See @ref hal_ll_gpio_base_handle_t for details.
 * @param[in] pin_mask Bitmask specifying which pins to configure as analog inputs.
 * See @ref hal_ll_gpio_mask_t for details.
 *
 * @return
 * None.
 *
 * @note
 * This function affects only the pins specified by the pin mask.
 *
 * @pre
 * The port pointer must be valid and point to a GPIO port register base.
 *
 * @post
 * The specified pins are configured as analog inputs.
 *
 * @warning
 * Configuring pins as analog inputs may disable digital input/output functionality.
 *
 * @par Example Usage
 * @code{.c}
 *    // Set pin 0 (mask 0x01) of PORTB as analog input. *    hal_ll_gpio_port_analog_input( hal_ll_gpio_port_base( PORTB ), 0x01 );
 * @endcode
 *
 * @par Limitations
 * - Only pins supporting analog input can be configured.
 *
 * @see hal_ll_gpio_port_digital_input()
 * @see hal_ll_gpio_port_digital_output()
 *
 * @link https://github.com/MikroElektronika/mikrosdk_v2/blob/master/targets/pic_8bit/mikroe/pic18/include/gpio/hal_ll_gpio_port.h#L260 Link to header @endlink.
 * @link https://github.com/MikroElektronika/mikrosdk_v2/blob/master/targets/pic_8bit/mikroe/pic18/src/gpio/implementation_1/subimplementation_1/hal_ll_gpio_port.c#L164 Link to source @endlink.
 */
void hal_ll_gpio_port_analog_input( uint16_t *port, uint8_t pin_mask );

/**
 * @brief Configure specified pins of a GPIO port as digital inputs.
 *
 * @details
 * This function configures the pins specified by the pin mask on the given
 * port to operate as digital inputs. It modifies the port registers to set
 * the pins to digital input mode.
 *
 * @param[in,out] port Pointer to the base address of the GPIO port registers.
 * See @ref hal_ll_gpio_base_handle_t for details.
 * @param[in] pin_mask Bitmask specifying which pins to configure as digital inputs.
 * See @ref hal_ll_gpio_mask_t for details.
 *
 * @return
 * None.
 *
 * @note
 * This function affects only the pins specified by the pin mask.
 *
 * @pre
 * The port pointer must be valid and point to a GPIO port register base.
 *
 * @post
 * The specified pins are configured as digital inputs.
 *
 * @warning
 * Configuring pins as digital inputs disables output functionality on those pins.
 *
 * @par Example Usage
 * @code{.c}
 *    // Set pin 0 (mask 0x01) of PORTB as digital input. *    hal_ll_gpio_port_digital_input( hal_ll_gpio_port_base( PORTB ), 0x01 );
 * @endcode
 *
 * @par Limitations
 * - Only pins supporting digital input can be configured.
 *
 * @see hal_ll_gpio_port_analog_input()
 * @see hal_ll_gpio_port_digital_output()
 *
 * @link https://github.com/MikroElektronika/mikrosdk_v2/blob/master/targets/pic_8bit/mikroe/pic18/include/gpio/hal_ll_gpio_port.h#L304 Link to header @endlink.
 * @link https://github.com/MikroElektronika/mikrosdk_v2/blob/master/targets/pic_8bit/mikroe/pic18/src/gpio/implementation_1/subimplementation_1/hal_ll_gpio_port.c#L174 Link to source @endlink.
 */
void hal_ll_gpio_port_digital_input( uint16_t *port, uint8_t pin_mask );

/**
 * @brief Configure a GPIO port's pins as digital inputs or outputs.
 *
 * @details
 * This function configures the pins specified in the port structure as either
 * digital inputs or outputs based on the is_input flag. It updates the tristate
 * register accordingly and handles analog pin configuration as needed.
 *
 * @param[in,out] port Pointer to the GPIO port structure containing base and mask.
 * See @ref hal_ll_gpio_port_t for details.
 * @param[in] name The port name identifier.
 * See @ref hal_ll_port_name_t for details.
 * @param[in] is_input Boolean flag indicating direction:
 * - true: configure pins as digital inputs.
 * - false: configure pins as digital outputs.
 *
 * @return
 * None.
 *
 * @note
 * This function also manages analog pin configuration for pins with analog functions.
 *
 * @pre
 * The port pointer must be valid and initialized.
 *
 * @post
 * The specified pins are configured as digital inputs or outputs.
 *
 * @warning
 * Incorrect usage may lead to improper pin configuration or conflicts with analog functions.
 *
 * @par Example Usage
 * @code{.c}
 *    hal_ll_gpio_port_t *port; *    // Set port PORTB as output. *    hal_ll_gpio_port_digital_configure_port( port, PORTB, false );
 * @endcode
 *
 * @par Limitations
 * - Only pins supporting digital input/output can be configured.
 *
 * @see hal_ll_gpio_port_digital_input()
 * @see hal_ll_gpio_port_digital_output()
 *
 * @link https://github.com/MikroElektronika/mikrosdk_v2/blob/master/targets/pic_8bit/mikroe/pic18/include/gpio/hal_ll_gpio_port.h#L351 Link to header @endlink.
 * @link https://github.com/MikroElektronika/mikrosdk_v2/blob/master/targets/pic_8bit/mikroe/pic18/src/gpio/implementation_1/subimplementation_1/hal_ll_gpio_port.c#L178 Link to source @endlink.
 */
void hal_ll_gpio_port_digital_configure_port( hal_ll_gpio_port_t *port, uint8_t name, bool is_input );

/**
 * @brief Configure specified pins of a GPIO port as digital outputs.
 *
 * @details
 * This function configures the pins specified by the pin mask on the given
 * port to operate as digital outputs. It modifies the port registers to set
 * the pins to digital output mode.
 *
 * @param[in,out] port Pointer to the base address of the GPIO port registers.
 * See @ref hal_ll_gpio_base_handle_t for details.
 * @param[in] pin_mask Bitmask specifying which pins to configure as digital outputs.
 * See @ref hal_ll_gpio_mask_t for details.
 *
 * @return
 * None.
 *
 * @note
 * This function affects only the pins specified by the pin mask.
 *
 * @pre
 * The port pointer must be valid and point to a GPIO port register base.
 *
 * @post
 * The specified pins are configured as digital outputs.
 *
 * @warning
 * Configuring pins as digital outputs disables input functionality on those pins.
 *
 * @par Example Usage
 * @code{.c}
 *    // Set pin 0 (mask 0x01) of PORTB as digital output. *    hal_ll_gpio_port_digital_output( hal_ll_gpio_port_base( PORTB ), 0x01 );
 * @endcode
 *
 * @par Limitations
 * - Only pins supporting digital output can be configured.
 *
 * @see hal_ll_gpio_port_digital_input()
 * @see hal_ll_gpio_port_analog_input()
 *
 * @link https://github.com/MikroElektronika/mikrosdk_v2/blob/master/targets/pic_8bit/mikroe/pic18/include/gpio/hal_ll_gpio_port.h#L395 Link to header @endlink.
 * @link https://github.com/MikroElektronika/mikrosdk_v2/blob/master/targets/pic_8bit/mikroe/pic18/src/gpio/implementation_1/subimplementation_1/hal_ll_gpio_port.c#L237 Link to source @endlink.
 */
void hal_ll_gpio_port_digital_output( uint16_t *port, uint8_t pin );

#endif // _HAL_LL_GPIO_PORT_H_
// ------------------------------------------------------------------------- END
