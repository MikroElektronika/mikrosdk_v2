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

#define PORT_MASK_16BIT 0xFFFF
#define PORT_PIN_MASK 0x000F

/**
 * @brief GPIO port register addresses handle structure.
 *
 * @details
 * This structure holds the base addresses for the port registers:
 * port register, latch register, and tristate register.
 * It is used internally to access and manipulate GPIO port registers.
 */
typedef struct {
    hal_ll_base_addr_t port_reg_addr; /**< Base address of the port register */
    hal_ll_base_addr_t lat_reg_addr;  /**< Base address of the latch register */
    hal_ll_base_addr_t tris_reg_addr; /**< Base address of the tristate register */
} hal_ll_gpio_base_handle_t;

/**
 * @brief GPIO base handle type.
 *
 * @details
 * This type represents a generic handle to a GPIO base,
 * typically used to identify a specific GPIO port or pin.
 */
typedef handle_t hal_ll_gpio_base_t;

/**
 * @brief GPIO pin direction enumeration.
 *
 * @details
 * This enumeration defines the possible directions for a GPIO pin:
 * digital input or digital output.
 */
typedef enum {
    HAL_LL_GPIO_DIGITAL_INPUT = 0,  /**< Pin configured as digital input */
    HAL_LL_GPIO_DIGITAL_OUTPUT = 1  /**< Pin configured as digital output */
} hal_ll_gpio_direction_t;

/**
 * @brief GPIO pin or port structure.
 *
 * @details
 * This structure represents a GPIO pin or port,
 * containing a base handle and a mask to identify specific pins.
 */
typedef struct hal_ll_gpio_t {
    hal_ll_gpio_base_t base; /**< Base handle for the GPIO */
    hal_ll_gpio_mask_t mask; /**< Mask identifying the pin(s) */
} hal_ll_gpio_t;

/**
 * @brief GPIO pin type.
 *
 * @details
 * Alias for hal_ll_gpio_t representing a GPIO pin.
 */
typedef struct hal_ll_gpio_t hal_ll_gpio_pin_t;

/**
 * @brief GPIO port type.
 *
 * @details
 * Alias for hal_ll_gpio_t representing a GPIO port.
 */
typedef struct hal_ll_gpio_t hal_ll_gpio_port_t;

/**
 * @brief Placeholder function named affichage.
 *
 * @details
 * This function's purpose is not specified in the current context.
 * It returns a 16-bit unsigned integer value.
 *
 * @return uint16_t A 16-bit unsigned integer value.
 *
 * @note This function may be used for display or debugging purposes.
 *
 * @pre None.
 *
 * @post None.
 *
 * @warning Usage and behavior are undefined without further context.
 *
 * @par Example Usage
 * @code{.c}
 *     TODO: ADD EXAMPLE CODE FOR `affichage`
 * @endcode
 *
 * @par Limitations
 * - Function behavior is not documented.
 *
 * @see None.
 *
 * @link https://github.com/MikroElektronika/mikrosdk_v2/blob/master/targets/pic_16bit/mikroe/dspic/include/gpio/hal_ll_gpio_port.h#L150 Link to header @endlink.
 * @link https://github.com/MikroElektronika/mikrosdk_v2/blob/master/targets/pic_16bit/mikroe/dspic/src/gpio/implementation_1/subimplementation_1/hal_ll_gpio_port.c Link to source @endlink.
 */
uint16_t affichage();

/**
 * @brief Get port index from pin name.
 *
 * @details
 * Calculates the index of the port to which the specified pin belongs.
 * The index is based on the pin name and the port size.
 *
 * @param[in] name Pin name to get the port index for.
 *
 * @return uint8_t Port index value from 0 to PORT_COUNT-1.
 *
 * @note This function assumes that pin names are organized sequentially per port.
 *
 * @pre The pin name must be valid and correspond to an existing pin.
 *
 * @post None.
 *
 * @warning None.
 *
 * @par Example Usage
 * @code{.c}
 *    // Get port. *    hal_ll_gpio_port_index( GPIO_PB2 );
 * @endcode
 *
 * @par Limitations
 * - Only valid for pins within defined ports.
 *
 * @see hal_ll_gpio_port_pin_mask()
 * @see hal_ll_gpio_port_pin_index()
 *
 * @link https://github.com/MikroElektronika/mikrosdk_v2/blob/master/targets/pic_16bit/mikroe/dspic/include/gpio/hal_ll_gpio_port.h#L185 Link to header @endlink.
 * @link https://github.com/MikroElektronika/mikrosdk_v2/blob/master/targets/pic_16bit/mikroe/dspic/src/gpio/implementation_1/subimplementation_1/hal_ll_gpio_port.c#L176 Link to source @endlink.
 */
uint8_t hal_ll_gpio_port_index(hal_ll_pin_name_t name);

/**
 * @brief Get pin mask for a given pin name.
 *
 * @details
 * Returns a bit mask corresponding to the pin's position within its port.
 * The mask can be used to manipulate or identify the pin within port registers.
 *
 * @param[in] name Pin name to get the mask for.
 *
 * @return uint16_t Bit mask representing the pin position.
 *
 * @note The mask is a single bit set at the pin's index within the port.
 *
 * @pre The pin name must be valid.
 *
 * @post None.
 *
 * @warning None.
 *
 * @par Example Usage
 * @code{.c}
 *    // Get pin mask. *    hal_ll_gpio_port_pin_mask( GPIO_PB2 );
 * @endcode
 *
 * @par Limitations
 * - Only valid for pins within defined ports.
 *
 * @see hal_ll_gpio_port_index()
 * @see hal_ll_gpio_port_base_map()
 *
 * @link https://github.com/MikroElektronika/mikrosdk_v2/blob/master/targets/pic_16bit/mikroe/dspic/include/gpio/hal_ll_gpio_port.h#L220 Link to header @endlink.
 * @link https://github.com/MikroElektronika/mikrosdk_v2/blob/master/targets/pic_16bit/mikroe/dspic/src/gpio/implementation_1/subimplementation_1/hal_ll_gpio_port.c#L185 Link to source @endlink.
 */
uint16_t hal_ll_gpio_port_pin_mask(hal_ll_pin_name_t name);

/**
 * @brief Get base map address of a GPIO port.
 *
 * @details
 * Returns the base address of the port register offsets for the specified port.
 * This address can be used to access port registers for configuration and control.
 *
 * @param[in] name Port name to get the base map for.
 *
 * @return uint16_t Address of the first register of the port.
 *
 * @note The returned address corresponds to internal port register mappings.
 *
 * @pre The port name must be valid.
 *
 * @post None.
 *
 * @warning None.
 *
 * @par Example Usage
 * @code{.c}
 *    // Get the base address map of a GPIO port. *    hal_ll_gpio_port_base_map( PORTB );
 * @endcode
 *
 * @par Limitations
 * - Only valid for ports defined in the hardware.
 *
 * @see hal_ll_gpio_port_pin_mask()
 * @see hal_ll_gpio_port_index()
 *
 * @link https://github.com/MikroElektronika/mikrosdk_v2/blob/master/targets/pic_16bit/mikroe/dspic/include/gpio/hal_ll_gpio_port.h#L255 Link to header @endlink.
 * @link https://github.com/MikroElektronika/mikrosdk_v2/blob/master/targets/pic_16bit/mikroe/dspic/src/gpio/implementation_1/subimplementation_1/hal_ll_gpio_port.c#L194 Link to source @endlink.
 */
uint16_t hal_ll_gpio_port_base_map(hal_ll_port_name_t name);

/**
 * @brief Configure port pins as analog input.
 *
 * @details
 * Sets the specified pins of the given port to analog input mode.
 * This disables digital input buffers and enables analog functionality.
 *
 * @param[in] port Pointer to the port base address.
 * @param[in] pin_mask Bit mask specifying which pins to configure.
 *
 * @return void
 *
 * @note This function affects only the pins specified by the pin_mask.
 *
 * @pre The port pointer must be valid and point to a valid port register.
 *
 * @post The specified pins are configured as analog inputs.
 *
 * @warning Ensure that the pins support analog input functionality.
 *
 * @par Example Usage
 * @code{.c}
 *    // Set pin 0 (mask 0x01) of PORTB as analog input. *    hal_ll_gpio_port_analog_input( hal_ll_gpio_port_base( PORTB ), 0x01 );
 * @endcode
 *
 * @par Limitations
 * - Pins not supporting analog input will not be affected.
 *
 * @see hal_ll_gpio_port_digital_input()
 * @see hal_ll_gpio_port_digital_output()
 *
 * @link https://github.com/MikroElektronika/mikrosdk_v2/blob/master/targets/pic_16bit/mikroe/dspic/include/gpio/hal_ll_gpio_port.h#L291 Link to header @endlink.
 * @link https://github.com/MikroElektronika/mikrosdk_v2/blob/master/targets/pic_16bit/mikroe/dspic/src/gpio/implementation_1/subimplementation_1/hal_ll_gpio_port.c#L204 Link to source @endlink.
 */
void hal_ll_gpio_port_analog_input(uint16_t *port, uint16_t pin_mask);

/**
 * @brief Configure port pins as digital input or output.
 *
 * @details
 * Configures the entire port represented by the hal_ll_gpio_port_t structure
 * as either digital input or digital output based on the is_input flag.
 * Also configures analog pins accordingly.
 *
 * @param[in,out] port Pointer to the hal_ll_gpio_port_t structure representing the port.
 * @param[in] name Port index or identifier.
 * @param[in] is_input Boolean flag indicating input (true) or output (false) configuration.
 *
 * @return void
 *
 * @note This function updates the tristate register to set pin directions.
 * It also configures analog pins to digital mode if applicable.
 *
 * @pre The port structure must be properly initialized.
 *
 * @post The port pins are configured as digital input or output.
 *
 * @warning Changing pin directions may affect connected peripherals.
 *
 * @par Example Usage
 * @code{.c}
 *    hal_ll_gpio_port_t *port; *    // Set port PORTB as output. *    hal_ll_gpio_port_digital_configure_port( port, PORTB, false );
 * @endcode
 *
 * @par Limitations
 * - Only pins defined in the analog input register list are configured for analog settings.
 *
 * @see hal_ll_gpio_port_analog_input()
 * @see hal_ll_gpio_port_digital_input()
 * @see hal_ll_gpio_port_digital_output()
 *
 * @link https://github.com/MikroElektronika/mikrosdk_v2/blob/master/targets/pic_16bit/mikroe/dspic/include/gpio/hal_ll_gpio_port.h#L331 Link to header @endlink.
 * @link https://github.com/MikroElektronika/mikrosdk_v2/blob/master/targets/pic_16bit/mikroe/dspic/src/gpio/implementation_1/subimplementation_1/hal_ll_gpio_port.c#L218 Link to source @endlink.
 */
void hal_ll_gpio_port_digital_configure_port(hal_ll_gpio_port_t *port, uint8_t name, bool is_input);

/**
 * @brief Configure port pins as digital input.
 *
 * @details
 * Sets the specified pins of the given port to digital input mode.
 * This enables digital input buffers and disables output drivers.
 *
 * @param[in] port Pointer to the port base address.
 * @param[in] pin_mask Bit mask specifying which pins to configure.
 *
 * @return void
 *
 * @note This function affects only the pins specified by the pin_mask.
 *
 * @pre The port pointer must be valid and point to a valid port register.
 *
 * @post The specified pins are configured as digital inputs.
 *
 * @warning Ensure that the pins are not used as outputs before calling this function.
 *
 * @par Example Usage
 * @code{.c}
 *    // Set pin 0 (mask 0x01) of PORTB as digital input. *    hal_ll_gpio_port_digital_input( hal_ll_gpio_port_base( PORTB ), 0x01 );
 * @endcode
 *
 * @par Limitations
 * - Pins configured as analog inputs will be overridden to digital input.
 *
 * @see hal_ll_gpio_port_analog_input()
 * @see hal_ll_gpio_port_digital_output()
 *
 * @link https://github.com/MikroElektronika/mikrosdk_v2/blob/master/targets/pic_16bit/mikroe/dspic/include/gpio/hal_ll_gpio_port.h#L367 Link to header @endlink.
 * @link https://github.com/MikroElektronika/mikrosdk_v2/blob/master/targets/pic_16bit/mikroe/dspic/src/gpio/implementation_1/subimplementation_1/hal_ll_gpio_port.c#L214 Link to source @endlink.
 */
void hal_ll_gpio_port_digital_input(uint16_t *port, uint16_t pin_mask);

/**
 * @brief Configure port pins as digital output.
 *
 * @details
 * Sets the specified pin of the given port to digital output mode.
 * This enables output drivers and disables digital input buffers.
 *
 * @param[in] port Pointer to the port base address.
 * @param[in] pin Pin mask specifying which pin to configure.
 *
 * @return void
 *
 * @note This function affects only the specified pin.
 *
 * @pre The port pointer must be valid and point to a valid port register.
 *
 * @post The specified pin is configured as digital output.
 *
 * @warning Ensure that the pin is not used as input before calling this function.
 *
 * @par Example Usage
 * @code{.c}
 *    // Set pin 0 (mask 0x01) of PORTB as digital output. *    hal_ll_gpio_port_digital_output( hal_ll_gpio_port_base( PORTB ), 0x01 );
 * @endcode
 *
 * @par Limitations
 * - Only one pin can be configured at a time.
 *
 * @see hal_ll_gpio_port_digital_input()
 * @see hal_ll_gpio_port_analog_input()
 *
 * @link https://github.com/MikroElektronika/mikrosdk_v2/blob/master/targets/pic_16bit/mikroe/dspic/include/gpio/hal_ll_gpio_port.h#L403 Link to header @endlink.
 * @link https://github.com/MikroElektronika/mikrosdk_v2/blob/master/targets/pic_16bit/mikroe/dspic/src/gpio/implementation_1/subimplementation_1/hal_ll_gpio_port.c#L244 Link to source @endlink.
 */
void hal_ll_gpio_port_digital_output(uint16_t *port, uint8_t pin);

#ifdef __cplusplus
}
#endif

#endif // _HAL_LL_GPIO_PORT_H_
// ------------------------------------------------------------------------- END
