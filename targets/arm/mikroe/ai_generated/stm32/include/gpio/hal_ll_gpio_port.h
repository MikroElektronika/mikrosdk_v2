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
#include "hal_ll_gpio_struct_type.h"

#define RESET_PINS_OFFSET 16

/**
 * @brief Helper macros for GPIO HAL.
 *
 * @details
 * These macros assist in GPIO module operations such as marking the end of a module structure,
 * offsetting alternate function bits, and combining pin and function values.
 */
#define GPIO_MODULE_STRUCT_END -1
#define GPIO_AF_OFFSET 8
#define VALUE(pin, func) (pin | (func << GPIO_AF_OFFSET))

/**
 * @brief Structure representing a GPIO module configuration.
 *
 * @details
 * This structure holds arrays of pins and their corresponding configurations,
 * along with a GPIO remap value. It is used to initialize and configure GPIO modules.
 */
typedef struct
{
  uint32_t pins[13];
  uint32_t configs[13];
  uint32_t gpio_remap;
} module_struct;

/**
 * @brief Type definition for GPIO base handle.
 *
 * @details
 * This type represents a handle to a GPIO base, used for identifying GPIO ports.
 */
typedef handle_t hal_ll_gpio_base_t;

/**
 * @brief Enumeration for GPIO pin direction.
 *
 * @details
 * Defines the possible directions for a GPIO pin: digital input or digital output.
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
 * This structure contains a base handle and a mask used to identify and manipulate specific GPIO pins or ports.
 */
typedef struct hal_ll_gpio_t
{
    hal_ll_gpio_base_t base;
    hal_ll_gpio_mask_t mask;
} hal_ll_gpio_t;

/**
 * @brief Type definition for GPIO pin.
 *
 * @details
 * Represents a GPIO pin using the hal_ll_gpio_t structure.
 */
typedef struct hal_ll_gpio_t hal_ll_gpio_pin_t;

/**
 * @brief Type definition for GPIO port.
 *
 * @details
 * Represents a GPIO port using the hal_ll_gpio_t structure.
 */
typedef struct hal_ll_gpio_t hal_ll_gpio_port_t;

/**
 * @brief Get the index of the GPIO port from a pin name.
 *
 * @details
 * Calculates the port index by dividing the pin name by the port size.
 *
 * @param[in] name The GPIO pin name.
 * See @ref hal_ll_pin_name_t for details.
 *
 * @return The index of the GPIO port as an 8-bit unsigned integer.
 *
 * @note
 * - The port index corresponds to the position of the port in the GPIO port array.
 *
 * @pre
 * - The pin name must be valid and within the expected range.
 *
 * @post
 * - Returns the port index corresponding to the given pin name.
 *
 * @warning
 * - Passing an invalid pin name may result in undefined behavior.
 *
 * @par Example Usage
 * @code{.c}
 *    // Get port. *    hal_ll_gpio_port_index( GPIO_PB2 );
 * @endcode
 *
 * @par Limitations
 * - Assumes pin names are sequentially assigned per port.
 *
 * @see hal_ll_gpio_pin_index()
 * @see hal_ll_gpio_port_base()
 *
 * @link https://github.com/MikroElektronika/mikrosdk_v2/blob/master/targets/arm/mikroe/ai_generated/stm32/include/gpio/hal_ll_gpio_port.h#L167 Link to header @endlink.
 * @link https://github.com/MikroElektronika/mikrosdk_v2/blob/master/targets/arm/mikroe/ai_generated/stm32/src/gpio/implementations/doc_ds_86/hal_ll_gpio_port.c#L154 Link to source @endlink.
 */
uint8_t hal_ll_gpio_port_index( hal_ll_pin_name_t name );

/**
 * @brief Get the pin mask for a given GPIO pin name.
 *
 * @details
 * Computes a bitmask representing the specific pin within its port by shifting 1 by the pin index.
 *
 * @param[in] name The GPIO pin name.
 * See @ref hal_ll_pin_name_t for details.
 *
 * @return A 32-bit unsigned integer mask with a single bit set corresponding to the pin.
 *
 * @note
 * - Useful for setting, clearing, or toggling specific pins in a port register.
 *
 * @pre
 * - The pin name must be valid.
 *
 * @post
 * - Returns the bitmask for the specified pin.
 *
 * @warning
 * - Invalid pin names may produce incorrect masks.
 *
 * @par Example Usage
 * @code{.c}
 *    // Get pin mask. *    hal_ll_gpio_pin_mask( GPIO_PB2 );
 * @endcode
 *
 * @par Limitations
 * - Assumes pin index is less than 32.
 *
 * @see hal_ll_gpio_pin_index()
 *
 * @link https://github.com/MikroElektronika/mikrosdk_v2/blob/master/targets/arm/mikroe/ai_generated/stm32/include/gpio/hal_ll_gpio_port.h#L205 Link to header @endlink.
 * @link https://github.com/MikroElektronika/mikrosdk_v2/blob/master/targets/arm/mikroe/ai_generated/stm32/src/gpio/implementations/doc_ds_86/hal_ll_gpio_port.c#L159 Link to source @endlink.
 */
uint32_t hal_ll_gpio_pin_mask( hal_ll_pin_name_t name );

/**
 * @brief Get the base address of a GPIO port.
 *
 * @details
 * Returns the base memory address of the specified GPIO port.
 *
 * @param[in] name The GPIO port name.
 * See @ref hal_ll_port_name_t for details.
 *
 * @return The base address of the GPIO port as a 32-bit unsigned integer.
 *
 * @note
 * - The base address is used for direct register access to the port.
 *
 * @pre
 * - The port name must be valid.
 *
 * @post
 * - Returns the base address corresponding to the port.
 *
 * @warning
 * - Invalid port names may return zero or invalid addresses.
 *
 * @par Example Usage
 * @code{.c}
 *    // Get port base address. *    hal_ll_gpio_port_base( PORTB );
 * @endcode
 *
 * @par Limitations
 * - Only supports ports defined in the GPIO port base array.
 *
 * @see hal_ll_gpio_port_index()
 *
 * @link https://github.com/MikroElektronika/mikrosdk_v2/blob/master/targets/arm/mikroe/ai_generated/stm32/include/gpio/hal_ll_gpio_port.h#L243 Link to header @endlink.
 * @link https://github.com/MikroElektronika/mikrosdk_v2/blob/master/targets/arm/mikroe/ai_generated/stm32/src/gpio/implementations/doc_ds_86/hal_ll_gpio_port.c#L164 Link to source @endlink.
 */
uint32_t hal_ll_gpio_port_base( hal_ll_port_name_t name );

/**
 * @brief Configure specified pins of a GPIO port as analog inputs.
 *
 * @details
 * Sets the configuration of the pins specified by pin_mask on the given port to analog input mode.
 *
 * @param[in,out] port Pointer to the base address of the GPIO port.
 * See @ref hal_ll_gpio_base_t for details.
 * @param[in] pin_mask Bitmask specifying which pins to configure.
 * See @ref hal_ll_gpio_mask_t for details.
 *
 * @return None.
 *
 * @note
 * - This function modifies the port registers to set pins to analog mode.
 *
 * @pre
 * - The port pointer must be valid.
 * - The pin_mask must specify valid pins within the port.
 *
 * @post
 * - The specified pins are configured as analog inputs.
 *
 * @warning
 * - Configuring pins incorrectly may affect other functionalities.
 *
 * @par Example Usage
 * @code{.c}
 *    // Set pin 0 (mask 0x01) of PORTB as analog input. *    hal_ll_gpio_analog_input( hal_ll_gpio_port_base( PORTB ), 0x01 );
 * @endcode
 *
 * @par Limitations
 * - Only supports pins available on the specified port.
 *
 * @see hal_ll_gpio_digital_input()
 * @see hal_ll_gpio_digital_output()
 *
 * @link https://github.com/MikroElektronika/mikrosdk_v2/blob/master/targets/arm/mikroe/ai_generated/stm32/include/gpio/hal_ll_gpio_port.h#L285 Link to header @endlink.
 * @link https://github.com/MikroElektronika/mikrosdk_v2/blob/master/targets/arm/mikroe/ai_generated/stm32/src/gpio/implementations/doc_ds_86/hal_ll_gpio_port.c#L169 Link to source @endlink.
 */
void hal_ll_gpio_analog_input( uint32_t *port, uint16_t pin_mask );

/**
 * @brief Configure specified pins of a GPIO port as digital inputs.
 *
 * @details
 * Sets the configuration of the pins specified by pin_mask on the given port to digital input mode.
 *
 * @param[in,out] port Pointer to the base address of the GPIO port.
 * See @ref hal_ll_gpio_base_t for details.
 * @param[in] pin_mask Bitmask specifying which pins to configure.
 * See @ref hal_ll_gpio_mask_t for details.
 *
 * @return None.
 *
 * @note
 * - This function modifies the port registers to set pins to digital input mode.
 *
 * @pre
 * - The port pointer must be valid.
 * - The pin_mask must specify valid pins within the port.
 *
 * @post
 * - The specified pins are configured as digital inputs.
 *
 * @warning
 * - Configuring pins incorrectly may affect other functionalities.
 *
 * @par Example Usage
 * @code{.c}
 *    // Set pin 0 (mask 0x01) of PORTB as digital input. *    hal_ll_gpio_digital_input( hal_ll_gpio_port_base( PORTB ), 0x01 );
 * @endcode
 *
 * @par Limitations
 * - Only supports pins available on the specified port.
 *
 * @see hal_ll_gpio_analog_input()
 * @see hal_ll_gpio_digital_output()
 *
 * @link https://github.com/MikroElektronika/mikrosdk_v2/blob/master/targets/arm/mikroe/ai_generated/stm32/include/gpio/hal_ll_gpio_port.h#L327 Link to header @endlink.
 * @link https://github.com/MikroElektronika/mikrosdk_v2/blob/master/targets/arm/mikroe/ai_generated/stm32/src/gpio/implementations/doc_ds_86/hal_ll_gpio_port.c#L174 Link to source @endlink.
 */
void hal_ll_gpio_digital_input( uint32_t *port, uint16_t pin_mask );

/**
 * @brief Configure specified pins of a GPIO port as digital outputs.
 *
 * @details
 * Sets the configuration of the pins specified by pin_mask on the given port to digital output mode.
 *
 * @param[in,out] port Pointer to the base address of the GPIO port.
 * See @ref hal_ll_gpio_base_t for details.
 * @param[in] pin_mask Bitmask specifying which pins to configure.
 * See @ref hal_ll_gpio_mask_t for details.
 *
 * @return None.
 *
 * @note
 * - This function modifies the port registers to set pins to digital output mode.
 *
 * @pre
 * - The port pointer must be valid.
 * - The pin_mask must specify valid pins within the port.
 *
 * @post
 * - The specified pins are configured as digital outputs.
 *
 * @warning
 * - Configuring pins incorrectly may affect other functionalities.
 *
 * @par Example Usage
 * @code{.c}
 *    // Set pin 0 (mask 0x01) of PORTB as digital output. *    hal_ll_gpio_digital_output( hal_ll_gpio_port_base( PORTB ), 0x01 );
 * @endcode
 *
 * @par Limitations
 * - Only supports pins available on the specified port.
 *
 * @see hal_ll_gpio_analog_input()
 * @see hal_ll_gpio_digital_input()
 *
 * @link https://github.com/MikroElektronika/mikrosdk_v2/blob/master/targets/arm/mikroe/ai_generated/stm32/include/gpio/hal_ll_gpio_port.h#L369 Link to header @endlink.
 * @link https://github.com/MikroElektronika/mikrosdk_v2/blob/master/targets/arm/mikroe/ai_generated/stm32/src/gpio/implementations/doc_ds_86/hal_ll_gpio_port.c#L179 Link to source @endlink.
 */
void hal_ll_gpio_digital_output( uint32_t *port, uint16_t pin_mask );

/**
 * @brief Initialize GPIO module structure and configure pins.
 *
 * @details
 * Iterates through the pins and configurations in the provided module structure,
 * enabling or disabling alternate functions for each pin based on the state parameter.
 *
 * @param[in] module Pointer to a constant module_struct containing pins and configurations.
 * See @ref module_struct for details.
 * @param[in] state Boolean value indicating whether to enable (true) or disable (false) the alternate functions.
 *
 * @return None.
 *
 * @note
 * - The function stops processing when it encounters GPIO_MODULE_STRUCT_END in the pins array.
 *
 * @pre
 * - The module pointer must be valid and properly initialized.
 *
 * @post
 * - The pins in the module are configured according to the specified state.
 *
 * @warning
 * - Passing an invalid module structure may cause undefined behavior.
 *
 * @par Example Usage
 * @code{.c}
 *    module_struct module; *    bool hal_ll_state; *    hal_ll_gpio_module_struct_init( &module, hal_ll_state );
 * @endcode
 *
 * @par Limitations
 * - Assumes the pins array is terminated with GPIO_MODULE_STRUCT_END.
 *
 * @see hal_ll_gpio_config()
 * @see _hal_ll_gpio_config_pin_alternate_enable()
 *
 * @link https://github.com/MikroElektronika/mikrosdk_v2/blob/master/targets/arm/mikroe/ai_generated/stm32/include/gpio/hal_ll_gpio_port.h#L410 Link to header @endlink.
 * @link https://github.com/MikroElektronika/mikrosdk_v2/blob/master/targets/arm/mikroe/ai_generated/stm32/src/gpio/implementations/doc_ds_86/hal_ll_gpio_port.c#L184 Link to source @endlink.
 */
void hal_ll_gpio_module_struct_init( module_struct const *module, bool state );

#ifdef __cplusplus
}
#endif

#endif // _HAL_LL_GPIO_PORT_H_
// ------------------------------------------------------------------------- END
