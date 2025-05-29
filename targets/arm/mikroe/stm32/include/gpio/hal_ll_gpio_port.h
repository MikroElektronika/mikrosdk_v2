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

#define RESET_PINS_OFFSET 16

/**
 * @brief Helper macros for GPIO HAL.
 *
 * @details
 * These macros assist in GPIO module operations such as marking the end of a module structure,
 * defining alternate function offset, and combining pin and function values.
 */
#define GPIO_MODULE_STRUCT_END -1
#define GPIO_AF_OFFSET 8
#define VALUE(pin, func) (pin | (func << GPIO_AF_OFFSET))

/**
 * @brief Structure representing a GPIO module configuration.
 *
 * @details
 * This structure holds arrays of pins and their corresponding configurations,
 * along with a GPIO remap value used for alternate function remapping.
 */
typedef struct
{
  uint32_t pins[13];
  uint32_t configs[13];
  uint32_t gpio_remap;
} module_struct;

/**
 * @brief GPIO module registers access structure.
 *
 * @details
 * This structure defines the registers used to control GPIO ports.
 * The exact structure depends on the GPIO subset defined during compilation.
 */
#if defined(__hal_ll_gpio_subset_1__)

typedef struct
{
    uint32_t moder;
    uint32_t otyper;
    uint32_t ospeedr;
    uint32_t pupdr;
    uint32_t idr;
    uint32_t odr;
    uint32_t bsrr;
    uint32_t lckr;
    uint32_t afrl;
    uint32_t afrh;
} hal_ll_gpio_base_handle_t;

#elif defined(__hal_ll_gpio_subset_2__)

typedef struct
{
    uint32_t crl;
    uint32_t crh;
    uint32_t idr;
    uint32_t odr;
    uint32_t bsrr;
    uint32_t brr;
    uint32_t lckr;
} hal_ll_gpio_base_handle_t;

#endif

/**
 * @brief Type definition for GPIO base handle.
 *
 * @details
 * This type represents a handle to the base of a GPIO port.
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
};

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
 *
 * @return The index of the GPIO port.
 *
 * @note
 * - The port index is used to access port-specific registers or data.
 *
 * @pre
 * - The pin name must be valid and within the defined range.
 *
 * @post
 * - Returns the port index corresponding to the pin name.
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
 *
 * @link https://github.com/MikroElektronika/mikrosdk_v2/blob/master/targets/arm/mikroe/stm32/include/gpio/hal_ll_gpio_port.h#L202 Link to header @endlink.
 * @link https://github.com/MikroElektronika/mikrosdk_v2/blob/master/targets/arm/mikroe/stm32/src/gpio/implementation_2/hal_ll_gpio_port.c#L146 Link to source @endlink.
 */
uint8_t hal_ll_gpio_port_index( hal_ll_pin_name_t name );

/**
 * @brief Get the mask for a GPIO pin.
 *
 * @details
 * Returns a bitmask corresponding to the pin position within its port.
 *
 * @param[in] name The GPIO pin name.
 *
 * @return A 32-bit mask with a single bit set for the pin.
 *
 * @note
 * - The mask can be used to manipulate or read the pin state in port registers.
 *
 * @pre
 * - The pin name must be valid.
 *
 * @post
 * - Returns the bitmask for the specified pin.
 *
 * @warning
 * - Using an invalid pin name may cause incorrect mask calculation.
 *
 * @par Example Usage
 * @code{.c}
 *    // Get pin mask. *    hal_ll_gpio_pin_mask( GPIO_PB2 );
 * @endcode
 *
 * @par Limitations
 * - Assumes pin index fits within 32 bits.
 *
 * @see hal_ll_gpio_port_index()
 *
 * @link https://github.com/MikroElektronika/mikrosdk_v2/blob/master/targets/arm/mikroe/stm32/include/gpio/hal_ll_gpio_port.h#L239 Link to header @endlink.
 * @link https://github.com/MikroElektronika/mikrosdk_v2/blob/master/targets/arm/mikroe/stm32/src/gpio/implementation_2/hal_ll_gpio_port.c#L151 Link to source @endlink.
 */
uint32_t hal_ll_gpio_pin_mask( hal_ll_pin_name_t name );

/**
 * @brief Get the base address of a GPIO port.
 *
 * @details
 * Returns the base memory address of the specified GPIO port.
 *
 * @param[in] name The GPIO port name.
 *
 * @return The base address of the GPIO port.
 *
 * @note
 * - The base address is used for direct register access.
 *
 * @pre
 * - The port name must be valid.
 *
 * @post
 * - Returns the base address corresponding to the port name.
 *
 * @warning
 * - Using an invalid port name may return zero or invalid address.
 *
 * @par Example Usage
 * @code{.c}
 *    // Get port base address. *    hal_ll_gpio_port_base( PORTB );
 * @endcode
 *
 * @par Limitations
 * - Only supports ports defined in the _hal_ll_gpio_port_base array.
 *
 * @see hal_ll_gpio_port_index()
 *
 * @link https://github.com/MikroElektronika/mikrosdk_v2/blob/master/targets/arm/mikroe/stm32/include/gpio/hal_ll_gpio_port.h#L276 Link to header @endlink.
 * @link https://github.com/MikroElektronika/mikrosdk_v2/blob/master/targets/arm/mikroe/stm32/src/gpio/implementation_2/hal_ll_gpio_port.c#L156 Link to source @endlink.
 */
uint32_t hal_ll_gpio_port_base( hal_ll_port_name_t name );

/**
 * @brief Configure GPIO pins as analog input.
 *
 * @details
 * Sets the specified pins on the given port to analog input mode.
 *
 * @param[in,out] port Pointer to the base address of the GPIO port.
 * See @ref hal_ll_gpio_base_handle_t for port structure details.
 * @param[in] pin_mask Bitmask specifying which pins to configure.
 *
 * @return void
 *
 * @note
 * - This function configures pins for analog input, disabling digital input/output.
 *
 * @pre
 * - The port pointer must be valid.
 * - The pin_mask must specify valid pins within the port.
 *
 * @post
 * - The specified pins are configured as analog inputs.
 *
 * @warning
 * - Configuring pins incorrectly may affect other peripheral functions.
 *
 * @par Example Usage
 * @code{.c}
 *    // Set pin 0 (mask 0x01) of PORTB as analog input. *    hal_ll_gpio_analog_input( hal_ll_gpio_port_base( PORTB ), 0x01 );
 * @endcode
 *
 * @par Limitations
 * - Only applicable to pins supporting analog input.
 *
 * @see hal_ll_gpio_digital_input()
 * @see hal_ll_gpio_digital_output()
 *
 * @link https://github.com/MikroElektronika/mikrosdk_v2/blob/master/targets/arm/mikroe/stm32/include/gpio/hal_ll_gpio_port.h#L317 Link to header @endlink.
 * @link https://github.com/MikroElektronika/mikrosdk_v2/blob/master/targets/arm/mikroe/stm32/src/gpio/implementation_2/hal_ll_gpio_port.c#L161 Link to source @endlink.
 */
void hal_ll_gpio_analog_input( uint32_t *port, uint16_t pin_mask );

/**
 * @brief Configure GPIO pins as digital input.
 *
 * @details
 * Sets the specified pins on the given port to digital input mode.
 *
 * @param[in,out] port Pointer to the base address of the GPIO port.
 * See @ref hal_ll_gpio_base_handle_t for port structure details.
 * @param[in] pin_mask Bitmask specifying which pins to configure.
 *
 * @return void
 *
 * @note
 * - This function configures pins for digital input, disabling output mode.
 *
 * @pre
 * - The port pointer must be valid.
 * - The pin_mask must specify valid pins within the port.
 *
 * @post
 * - The specified pins are configured as digital inputs.
 *
 * @warning
 * - Configuring pins incorrectly may affect other peripheral functions.
 *
 * @par Example Usage
 * @code{.c}
 *    // Set pin 0 (mask 0x01) of PORTB as digital input. *    hal_ll_gpio_digital_input( hal_ll_gpio_port_base( PORTB ), 0x01 );
 * @endcode
 *
 * @par Limitations
 * - Only applicable to pins supporting digital input.
 *
 * @see hal_ll_gpio_analog_input()
 * @see hal_ll_gpio_digital_output()
 *
 * @link https://github.com/MikroElektronika/mikrosdk_v2/blob/master/targets/arm/mikroe/stm32/include/gpio/hal_ll_gpio_port.h#L358 Link to header @endlink.
 * @link https://github.com/MikroElektronika/mikrosdk_v2/blob/master/targets/arm/mikroe/stm32/src/gpio/implementation_2/hal_ll_gpio_port.c#L166 Link to source @endlink.
 */
void hal_ll_gpio_digital_input( uint32_t *port, uint16_t pin_mask );

/**
 * @brief Configure GPIO pins as digital output.
 *
 * @details
 * Sets the specified pins on the given port to digital output mode.
 *
 * @param[in,out] port Pointer to the base address of the GPIO port.
 * See @ref hal_ll_gpio_base_handle_t for port structure details.
 * @param[in] pin_mask Bitmask specifying which pins to configure.
 *
 * @return void
 *
 * @note
 * - This function configures pins for digital output, disabling input mode.
 *
 * @pre
 * - The port pointer must be valid.
 * - The pin_mask must specify valid pins within the port.
 *
 * @post
 * - The specified pins are configured as digital outputs.
 *
 * @warning
 * - Configuring pins incorrectly may affect other peripheral functions.
 *
 * @par Example Usage
 * @code{.c}
 *    // Set pin 0 (mask 0x01) of PORTB as digital output. *    hal_ll_gpio_digital_output( hal_ll_gpio_port_base( PORTB ), 0x01 );
 * @endcode
 *
 * @par Limitations
 * - Only applicable to pins supporting digital output.
 *
 * @see hal_ll_gpio_analog_input()
 * @see hal_ll_gpio_digital_input()
 *
 * @link https://github.com/MikroElektronika/mikrosdk_v2/blob/master/targets/arm/mikroe/stm32/include/gpio/hal_ll_gpio_port.h#L399 Link to header @endlink.
 * @link https://github.com/MikroElektronika/mikrosdk_v2/blob/master/targets/arm/mikroe/stm32/src/gpio/implementation_2/hal_ll_gpio_port.c#L171 Link to source @endlink.
 */
void hal_ll_gpio_digital_output( uint32_t *port, uint16_t pin_mask );

/**
 * @brief Initialize GPIO module structure and configure alternate functions.
 *
 * @details
 * This function initializes the GPIO module structure by enabling or disabling
 * the alternate function remapping and configuring the pins and their settings
 * as specified in the module structure.
 *
 * @param[in] module Pointer to the module_struct containing pins, configs, and remap info.
 * See @ref module_struct for structure details.
 * @param[in] state Boolean value to enable (true) or disable (false) the module configuration.
 *
 * @return void
 *
 * @note
 * - This function handles both AFIO_MAPR and AFIO_MAPR2 remapping registers.
 * - It iterates through the pins array until GPIO_MODULE_STRUCT_END is encountered.
 *
 * @pre
 * - The module pointer must be valid and properly initialized.
 *
 * @post
 * - The GPIO module pins are configured according to the provided module_struct.
 *
 * @warning
 * - Incorrect configuration may lead to unexpected pin behavior.
 *
 * @par Example Usage
 * @code{.c}
 *    module_struct module; *    bool hal_ll_state; *    hal_ll_gpio_module_struct_init( &module, hal_ll_state );
 * @endcode
 *
 * @par Limitations
 * - Only supports modules with up to 13 pins as defined.
 *
 * @see module_struct
 *
 * @link https://github.com/MikroElektronika/mikrosdk_v2/blob/master/targets/arm/mikroe/stm32/include/gpio/hal_ll_gpio_port.h#L441 Link to header @endlink.
 * @link https://github.com/MikroElektronika/mikrosdk_v2/blob/master/targets/arm/mikroe/stm32/src/gpio/implementation_2/hal_ll_gpio_port.c#L176 Link to source @endlink.
 */
void hal_ll_gpio_module_struct_init( module_struct const *module, bool state );

#ifdef __cplusplus
}
#endif

#endif // _HAL_LL_GPIO_PORT_H_
// ------------------------------------------------------------------------- END
