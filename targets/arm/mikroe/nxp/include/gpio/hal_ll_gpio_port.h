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

/**
 * @brief Helper macros for GPIO HAL operations.
 *
 * @details
 * These macros assist in GPIO module structure handling and alternate function
 * configuration by defining constants and bit manipulation helpers.
 */
#define GPIO_MODULE_STRUCT_END (-1)
#define GPIO_AF_OFFSET 8
#define VALUE(pin, func) (pin | (func << GPIO_AF_OFFSET))

/**
 * @brief Structure representing a GPIO module configuration.
 *
 * @details
 * This structure holds arrays of pin base addresses and their corresponding
 * configuration values for up to 13 pins. It is used to initialize or configure
 * GPIO modules collectively.
 */
typedef struct
{
    hal_ll_base_addr_t pins[13];
    uint32_t configs[13];
} module_struct;

/**
 * @brief Structure representing the base registers of a GPIO port.
 *
 * @details
 * This structure contains base addresses for key GPIO port registers including
 * data output, set output, clear output, toggle output, data input, and data
 * direction registers. It is used to access and manipulate GPIO port registers.
 */
typedef struct
{
    hal_ll_base_addr_t pdor;     /**< Port Data Output Register, offset: 0x0 */
    hal_ll_base_addr_t psor;     /**< Port Set Output Register, offset: 0x4 */
    hal_ll_base_addr_t pcor;     /**< Port Clear Output Register, offset: 0x8 */
    hal_ll_base_addr_t ptor;     /**< Port Toggle Output Register, offset: 0xC */
    hal_ll_base_addr_t pdir;     /**< Port Data Input Register, offset: 0x10 */
    hal_ll_base_addr_t pddr;     /**< Port Data Direction Register, offset: 0x14 */
} hal_ll_gpio_base_handle_t;

/**
 * @brief Structure representing the base addresses of GPIO port control registers.
 *
 * @details
 * This structure contains base addresses for port control registers (PCR) for
 * pins 0 through 31. It is used to configure pin multiplexing and other pin
 * control features at the port level.
 */
typedef struct
{
    hal_ll_base_addr_t pcr0;
    hal_ll_base_addr_t pcr1;
    hal_ll_base_addr_t pcr2;
    hal_ll_base_addr_t pcr3;
    hal_ll_base_addr_t pcr4;
    hal_ll_base_addr_t pcr5;
    hal_ll_base_addr_t pcr6;
    hal_ll_base_addr_t pcr7;
    hal_ll_base_addr_t pcr8;
    hal_ll_base_addr_t pcr9;
    hal_ll_base_addr_t pcr10;
    hal_ll_base_addr_t pcr11;
    hal_ll_base_addr_t pcr12;
    hal_ll_base_addr_t pcr13;
    hal_ll_base_addr_t pcr14;
    hal_ll_base_addr_t pcr15;
    hal_ll_base_addr_t pcr16;
    hal_ll_base_addr_t pcr17;
    hal_ll_base_addr_t pcr18;
    hal_ll_base_addr_t pcr19;
    hal_ll_base_addr_t pcr20;
    hal_ll_base_addr_t pcr21;
    hal_ll_base_addr_t pcr22;
    hal_ll_base_addr_t pcr23;
    hal_ll_base_addr_t pcr24;
    hal_ll_base_addr_t pcr25;
    hal_ll_base_addr_t pcr26;
    hal_ll_base_addr_t pcr27;
    hal_ll_base_addr_t pcr28;
    hal_ll_base_addr_t pcr29;
    hal_ll_base_addr_t pcr30;
    hal_ll_base_addr_t pcr31;
} hal_ll_gpio_pcr_base_handle_t;

/**
 * @brief Structure representing an array of port control register base addresses.
 *
 * @details
 * This structure holds an array of base addresses for port control registers
 * indexed by pin number, facilitating access to individual pin control registers.
 */
typedef struct
{
    hal_ll_base_addr_t pcr_index_of[32];
} hal_ll_gpio_pcr_base_array_t;

/**
 * @brief GPIO handle type definition.
 *
 * @details
 * Defines a generic handle type for GPIO operations, used to reference GPIO ports
 * or pins in the HAL layer.
 */
typedef handle_t hal_ll_gpio_base_t;

/**
 * @brief Enumeration for GPIO pin direction.
 *
 * @details
 * Defines possible directions for a GPIO pin: digital input or digital output.
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
 * This structure encapsulates a GPIO base handle and a mask representing the
 * specific pin(s) within the port. It is used to identify and manipulate GPIO pins or ports.
 */
typedef struct hal_ll_gpio_t
{
    hal_ll_gpio_base_t base;
    hal_ll_gpio_mask_t mask;
};

/**
 * @brief Alias for GPIO pin type.
 *
 * @details
 * Defines hal_ll_gpio_pin_t as an alias for hal_ll_gpio_t structure, representing
 * a GPIO pin.
 */
typedef struct hal_ll_gpio_t hal_ll_gpio_pin_t;

/**
 * @brief Alias for GPIO port type.
 *
 * @details
 * Defines hal_ll_gpio_port_t as an alias for hal_ll_gpio_t structure, representing
 * a GPIO port.
 */
typedef struct hal_ll_gpio_t hal_ll_gpio_port_t;

/**
 * @brief Get the index of the GPIO port from a pin name.
 *
 * @details
 * Calculates the port index by dividing the pin name by the port size constant.
 * This function helps in identifying the port number associated with a given pin.
 *
 * @param[in] name The GPIO pin name.
 * See @ref hal_ll_pin_name_t for details.
 *
 * @return The index of the GPIO port as an 8-bit unsigned integer.
 *
 * @note
 * - The port index is zero-based.
 *
 * @pre
 * - The pin name must be valid and within the supported range.
 *
 * @post
 * - Returns the port index corresponding to the pin.
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
 * - Only valid for pins defined within the supported port range.
 *
 * @see hal_ll_gpio_pin_index()
 * @see hal_ll_gpio_port_base()
 *
 * @link https://github.com/MikroElektronika/mikrosdk_v2/blob/master/targets/arm/mikroe/nxp/include/gpio/hal_ll_gpio_port.h#L243 Link to header @endlink.
 * @link https://github.com/MikroElektronika/mikrosdk_v2/blob/master/targets/arm/mikroe/nxp/src/gpio/implementation_1/hal_ll_gpio_port.c#L123 Link to source @endlink.
 */
uint8_t hal_ll_gpio_port_index( hal_ll_pin_name_t name );

/**
 * @brief Get the mask for a GPIO pin.
 *
 * @details
 * Computes a bitmask corresponding to the pin position within its port by
 * shifting 1 by the pin index. This mask is used for bitwise operations on GPIO ports.
 *
 * @param[in] name The GPIO pin name.
 * See @ref hal_ll_pin_name_t for details.
 *
 * @return A 32-bit unsigned integer mask with a single bit set for the pin.
 *
 * @note
 * - The mask corresponds to the pin's bit position within the port register.
 *
 * @pre
 * - The pin name must be valid.
 *
 * @post
 * - Returns the bitmask for the specified pin.
 *
 * @warning
 * - Using an invalid pin name may produce incorrect masks.
 *
 * @par Example Usage
 * @code{.c}
 *    // Get pin mask. *    hal_ll_gpio_pin_mask( GPIO_PB2 );
 * @endcode
 *
 * @par Limitations
 * - Only supports pins within the defined port size.
 *
 * @see hal_ll_gpio_pin_index()
 * @see hal_ll_gpio_port_index()
 *
 * @link https://github.com/MikroElektronika/mikrosdk_v2/blob/master/targets/arm/mikroe/nxp/include/gpio/hal_ll_gpio_port.h#L283 Link to header @endlink.
 * @link https://github.com/MikroElektronika/mikrosdk_v2/blob/master/targets/arm/mikroe/nxp/src/gpio/implementation_1/hal_ll_gpio_port.c#L128 Link to source @endlink.
 */
uint32_t hal_ll_gpio_pin_mask( hal_ll_pin_name_t name );

/**
 * @brief Get the base address of a GPIO port.
 *
 * @details
 * Returns the base memory address of the specified GPIO port, which is used
 * to access the port's registers.
 *
 * @param[in] name The GPIO port name.
 * See @ref hal_ll_port_name_t for details.
 *
 * @return The base address of the GPIO port as a 32-bit unsigned integer.
 *
 * @note
 * - The returned address corresponds to the hardware register base for the port.
 *
 * @pre
 * - The port name must be valid and supported by the hardware.
 *
 * @post
 * - Returns the base address for the specified port.
 *
 * @warning
 * - Using an invalid port name may result in undefined behavior.
 *
 * @par Example Usage
 * @code{.c}
 *    // Get port base address. *    hal_ll_gpio_port_base( PORTB );
 * @endcode
 *
 * @par Limitations
 * - Only ports defined in the platform are supported.
 *
 * @see hal_ll_gpio_port_index()
 * @see hal_ll_gpio_pin_mask()
 *
 * @link https://github.com/MikroElektronika/mikrosdk_v2/blob/master/targets/arm/mikroe/nxp/include/gpio/hal_ll_gpio_port.h#L323 Link to header @endlink.
 * @link https://github.com/MikroElektronika/mikrosdk_v2/blob/master/targets/arm/mikroe/nxp/src/gpio/implementation_1/hal_ll_gpio_port.c#L133 Link to source @endlink.
 */
uint32_t hal_ll_gpio_port_base( hal_ll_port_name_t name );

/**
 * @brief Configure GPIO pins as analog inputs.
 *
 * @details
 * Sets the specified pins on the given port to operate as analog inputs by
 * applying the appropriate configuration settings.
 *
 * @param[in,out] port Pointer to the base address of the GPIO port to configure.
 * See @ref uint32_t for details.
 * @param[in] pin_mask Bitmask representing the pins to configure as analog inputs.
 * See @ref uint32_t for details.
 *
 * @return None.
 *
 * @note
 * - This function modifies the port configuration registers to enable analog mode.
 *
 * @pre
 * - The port pointer must be valid and point to a GPIO port base address.
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
 * - Only pins supporting analog input mode can be configured.
 *
 * @see hal_ll_gpio_digital_input()
 * @see hal_ll_gpio_digital_output()
 *
 * @link https://github.com/MikroElektronika/mikrosdk_v2/blob/master/targets/arm/mikroe/nxp/include/gpio/hal_ll_gpio_port.h#L366 Link to header @endlink.
 * @link https://github.com/MikroElektronika/mikrosdk_v2/blob/master/targets/arm/mikroe/nxp/src/gpio/implementation_1/hal_ll_gpio_port.c#L138 Link to source @endlink.
 */
void hal_ll_gpio_analog_input( uint32_t *port, uint32_t pin_mask );

/**
 * @brief Configure GPIO pins as digital inputs.
 *
 * @details
 * Sets the specified pins on the given port to operate as digital inputs by
 * applying the appropriate configuration settings.
 *
 * @param[in,out] port Pointer to the base address of the GPIO port to configure.
 * See @ref uint32_t for details.
 * @param[in] pin_mask Bitmask representing the pins to configure as digital inputs.
 * See @ref uint32_t for details.
 *
 * @return None.
 *
 * @note
 * - This function modifies the port configuration registers to enable digital input mode.
 *
 * @pre
 * - The port pointer must be valid and point to a GPIO port base address.
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
 * - Only pins supporting digital input mode can be configured.
 *
 * @see hal_ll_gpio_analog_input()
 * @see hal_ll_gpio_digital_output()
 *
 * @link https://github.com/MikroElektronika/mikrosdk_v2/blob/master/targets/arm/mikroe/nxp/include/gpio/hal_ll_gpio_port.h#L409 Link to header @endlink.
 * @link https://github.com/MikroElektronika/mikrosdk_v2/blob/master/targets/arm/mikroe/nxp/src/gpio/implementation_1/hal_ll_gpio_port.c#L143 Link to source @endlink.
 */
void hal_ll_gpio_digital_input( uint32_t *port, uint32_t pin_mask );

/**
 * @brief Configure GPIO pins as digital outputs.
 *
 * @details
 * Sets the specified pins on the given port to operate as digital outputs by
 * applying the appropriate configuration settings.
 *
 * @param[in,out] port Pointer to the base address of the GPIO port to configure.
 * See @ref uint32_t for details.
 * @param[in] pin_mask Bitmask representing the pins to configure as digital outputs.
 * See @ref uint32_t for details.
 *
 * @return None.
 *
 * @note
 * - This function modifies the port configuration registers to enable digital output mode.
 *
 * @pre
 * - The port pointer must be valid and point to a GPIO port base address.
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
 * - Only pins supporting digital output mode can be configured.
 *
 * @see hal_ll_gpio_analog_input()
 * @see hal_ll_gpio_digital_input()
 *
 * @link https://github.com/MikroElektronika/mikrosdk_v2/blob/master/targets/arm/mikroe/nxp/include/gpio/hal_ll_gpio_port.h#L452 Link to header @endlink.
 * @link https://github.com/MikroElektronika/mikrosdk_v2/blob/master/targets/arm/mikroe/nxp/src/gpio/implementation_1/hal_ll_gpio_port.c#L148 Link to source @endlink.
 */
void hal_ll_gpio_digital_output( uint32_t *port, uint32_t pin_mask );

/**
 * @brief Initialize GPIO module structure pins with alternate function configuration.
 *
 * @details
 * Iterates through the pins and configurations in the provided module structure,
 * enabling or disabling alternate function settings for each pin based on the
 * specified state.
 *
 * @param[in] module Pointer to the module_struct containing pins and their configurations.
 * See @ref module_struct for details.
 * @param[in] state Boolean value indicating whether to enable (true) or disable (false)
 * the alternate function configuration.
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
 * - Alternate function configurations are applied to all pins in the module structure.
 *
 * @warning
 * - Incorrect configurations may lead to undefined pin behavior.
 *
 * @par Example Usage
 * @code{.c}
 *    module_struct module; *    bool hal_ll_state; *    hal_ll_gpio_module_struct_init( &module, hal_ll_state );
 * @endcode
 *
 * @par Limitations
 * - Only supports up to 13 pins as defined in the module_struct.
 *
 * @see hal_ll_gpio_analog_input()
 * @see hal_ll_gpio_digital_input()
 * @see hal_ll_gpio_digital_output()
 *
 * @link https://github.com/MikroElektronika/mikrosdk_v2/blob/master/targets/arm/mikroe/nxp/include/gpio/hal_ll_gpio_port.h#L496 Link to header @endlink.
 * @link https://github.com/MikroElektronika/mikrosdk_v2/blob/master/targets/arm/mikroe/nxp/src/gpio/implementation_1/hal_ll_gpio_port.c#L153 Link to source @endlink.
 */
void hal_ll_gpio_module_struct_init( module_struct const *module, bool state );

#ifdef __cplusplus
}
#endif

#endif // _HAL_LL_GPIO_PORT_H_
// ------------------------------------------------------------------------- END
