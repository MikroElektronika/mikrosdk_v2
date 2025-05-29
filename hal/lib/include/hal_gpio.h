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
 * @file  hal_gpio.h
 * @brief This file contains all the functions prototypes for the GPIO library.
 */

#ifndef _HAL_GPIO_H_
#define _HAL_GPIO_H_

#ifdef __cplusplus
extern "C"{
#endif

#include "hal_target.h"
#include "hal_ll_gpio.h"

/**
 * @brief GPIO pin direction enumeration.
 *
 * @details
 * Defines the direction modes for a GPIO pin, specifying whether the pin
 * is configured as a digital input or digital output.
 */
typedef enum
{
    HAL_GPIO_DIGITAL_INPUT = 0, /*!< GPIO as digital input. */
    HAL_GPIO_DIGITAL_OUTPUT = 1 /*!< GPIO as digital output. */
} hal_gpio_direction_t;

/**
 * @brief GPIO base handle type.
 *
 * @details
 * Represents the base handle type used internally for GPIO operations.
 */
typedef handle_t hal_gpio_base_t; /*!< Handle type. */

/**
 * @brief GPIO mask type.
 *
 * @details
 * Represents the mask type used for GPIO port bit masking operations.
 */
typedef hal_ll_gpio_mask_t hal_gpio_mask_t; /*!< Mask type. */

/**
 * @brief GPIO pin or port structure.
 *
 * @details
 * This structure represents a GPIO pin or port, containing the base address
 * of the port and a bit mask indicating the specific pin(s) within the port.
 */
typedef struct hal_gpio
{
    hal_gpio_base_t base; /*!< Port base address. */
    hal_gpio_mask_t mask; /*!< Port bit mask. */
} hal_gpio_t;

/**
 * @brief GPIO pin type.
 *
 * @details
 * Forward declaration typedef for a GPIO pin, equivalent to hal_gpio_t.
 */
typedef hal_gpio_t hal_gpio_pin_t;  /*!< Forward declaration of the gpio pin typedef. */

/**
 * @brief GPIO port type.
 *
 * @details
 * Forward declaration typedef for a GPIO port, equivalent to hal_gpio_t.
 */
typedef hal_gpio_t hal_gpio_port_t; /*!< Forward declaration of the gpio port typedef. */

/**
 * @addtogroup pergroup Microcontroller Peripherals
 * @{
 */

/**
 * @addtogroup halgroup Hardware Abstraction Layer
 * @{
 */

/**
 * @addtogroup halgpiogroup GPIO HAL
 * @brief GPIO Hardware Abstraction Layer API Reference.
 * @details API for configuring and manipulating GPIO HAL module.
 * @{
 */

/**
 * @brief Configures a GPIO pin with the specified name and direction.
 *
 * @details
 * Initializes and configures the given GPIO pin structure with the specified
 * pin name and direction (input or output). This function sets up the pin
 * for subsequent read/write operations.
 *
 * @param[in,out] pin Pointer to the GPIO pin structure to configure.
 * See @ref hal_gpio_pin_t structure definition for more details.
 * @param[in] name The pin name identifier to configure.
 * See @ref hal_pin_name_t for valid pin names.
 * @param[in] direction The direction to set for the pin (input or output).
 * See @ref hal_gpio_direction_t for possible values.
 *
 * @return
 * - None.
 *
 * @note
 * - The pin must be properly initialized before use.
 * - The direction setting affects the electrical behavior of the pin.
 *
 * @pre
 * - The hardware must support the specified pin.
 *
 * @post
 * - The pin is configured and ready for I/O operations.
 *
 * @warning
 * - Configuring a pin incorrectly may cause hardware conflicts.
 *
 * @par Example Usage
 * @code{.c}
 *    // GPIO HAL pin context structure. *    hal_gpio_pin_t pin; * *    // Configure pin as digital output. *    hal_gpio_configure_pin( &pin, GPIO_PB2, HAL_GPIO_DIGITAL_OUTPUT );
 * @endcode
 *
 * @par Limitations
 * - Pin configuration is limited to digital input/output modes.
 *
 * @see hal_gpio_direction_t
 * @see hal_gpio_pin_t
 *
 * @link https://github.com/MikroElektronika/mikrosdk_v2/blob/master/hal/lib/include/hal_gpio.h#L174 Link to header @endlink.
 * @link https://github.com/MikroElektronika/mikrosdk_v2/blob/master/hal/lib/src/lib_hal_gpio/hal_gpio.c#L46 Link to source @endlink.
 */
void hal_gpio_configure_pin( hal_gpio_pin_t *pin, hal_pin_name_t name, hal_gpio_direction_t direction );

/**
 * @brief Reads the input state of a GPIO pin.
 *
 * @details
 * Returns the current logical input level of the specified GPIO pin.
 * The function reads the actual voltage level present on the pin.
 *
 * @param[in] pin Pointer to the GPIO pin structure to read.
 * See @ref hal_gpio_pin_t structure definition for more details.
 *
 * @return
 * - 0 if the pin input is low.
 * - Non-zero if the pin input is high.
 *
 * @note
 * - The pin must be configured as an input for valid readings.
 *
 * @pre
 * - The pin must be configured and initialized.
 *
 * @post
 * - No side effects.
 *
 * @warning
 * - Reading from an unconfigured pin may yield undefined results.
 *
 * @par Example Usage
 * @code{.c}
 *    // GPIO HAL pin context structure. *    hal_gpio_pin_t pin; * *    // GPIO value holder. *    uint8_t read_value; * *    // Read pin state. *    read_value = hal_gpio_read_pin_input( &pin );
 * @endcode
 *
 * @par Limitations
 * - Only digital input state is read; analog states are not supported.
 *
 * @see hal_gpio_configure_pin()
 * @see hal_gpio_pin_t
 *
 * @link https://github.com/MikroElektronika/mikrosdk_v2/blob/master/hal/lib/include/hal_gpio.h#L219 Link to header @endlink.
 * @link https://github.com/MikroElektronika/mikrosdk_v2/blob/master/hal/lib/src/lib_hal_gpio/hal_gpio.c#L53 Link to source @endlink.
 */
#if defined(FLATTEN_ME) && (FLATTEN_ME_LEVEL >= FLATTEN_ME_LEVEL_MID)
#define hal_gpio_read_pin_input(_handle) hal_ll_gpio_read_pin_input( (hal_ll_gpio_pin_t *)_handle )
#else
uint8_t hal_gpio_read_pin_input( hal_gpio_pin_t *pin );
#endif

/**
 * @brief Reads the output state of a GPIO pin.
 *
 * @details
 * Returns the current logical output level set on the specified GPIO pin.
 * This reflects the last value written to the pin output register.
 *
 * @param[in] pin Pointer to the GPIO pin structure to read.
 * See @ref hal_gpio_pin_t structure definition for more details.
 *
 * @return
 * - 0 if the pin output is low.
 * - Non-zero if the pin output is high.
 *
 * @note
 * - The pin must be configured as an output for valid readings.
 *
 * @pre
 * - The pin must be configured and initialized.
 *
 * @post
 * - No side effects.
 *
 * @warning
 * - Reading output state does not guarantee the actual pin voltage level.
 *
 * @par Example Usage
 * @code{.c}
 *    // GPIO HAL pin context structure. *    hal_gpio_pin_t pin; * *    // GPIO value holder. *    uint8_t read_value; * *    // Read pin state. *    read_value = hal_gpio_read_pin_output( &pin );
 * @endcode
 *
 * @par Limitations
 * - Only digital output state is read; actual pin state may differ due to hardware.
 *
 * @see hal_gpio_configure_pin()
 * @see hal_gpio_pin_t
 *
 * @link https://github.com/MikroElektronika/mikrosdk_v2/blob/master/hal/lib/include/hal_gpio.h#L265 Link to header @endlink.
 * @link https://github.com/MikroElektronika/mikrosdk_v2/blob/master/hal/lib/src/lib_hal_gpio/hal_gpio.c#L60 Link to source @endlink.
 */
#if defined(FLATTEN_ME) && (FLATTEN_ME_LEVEL >= FLATTEN_ME_LEVEL_MID)
#define hal_gpio_read_pin_output(_handle) hal_ll_gpio_read_pin_output( (hal_ll_gpio_pin_t *)_handle )
#else
uint8_t hal_gpio_read_pin_output( hal_gpio_pin_t *pin );
#endif

/**
 * @brief Writes a logical output value to a GPIO pin.
 *
 * @details
 * Sets the output level of the specified GPIO pin to the given value.
 * The pin must be configured as an output for this operation to take effect.
 *
 * @param[in,out] pin Pointer to the GPIO pin structure to write.
 * See @ref hal_gpio_pin_t structure definition for more details.
 * @param[in] value The logical value to write to the pin output.
 * - 0 sets the pin output low.
 * - Non-zero sets the pin output high.
 *
 * @return
 * - None.
 *
 * @note
 * - Writing to a pin configured as input may have no effect.
 *
 * @pre
 * - The pin must be configured as an output.
 *
 * @post
 * - The pin output register is updated with the specified value.
 *
 * @warning
 * - Writing invalid values may cause undefined behavior.
 *
 * @par Example Usage
 * @code{.c}
 *    // GPIO HAL pin context structure. *    hal_gpio_pin_t pin; * *    // Set pin logic state to high (1). *    hal_gpio_write_pin_output( &pin, 1 );
 * @endcode
 *
 * @par Limitations
 * - Only digital output values are supported.
 *
 * @see hal_gpio_configure_pin()
 * @see hal_gpio_pin_t
 *
 * @link https://github.com/MikroElektronika/mikrosdk_v2/blob/master/hal/lib/include/hal_gpio.h#L313 Link to header @endlink.
 * @link https://github.com/MikroElektronika/mikrosdk_v2/blob/master/hal/lib/src/lib_hal_gpio/hal_gpio.c#L67 Link to source @endlink.
 */
#if defined(FLATTEN_ME) && (FLATTEN_ME_LEVEL >= FLATTEN_ME_LEVEL_MID)
#define hal_gpio_write_pin_output(_handle,_value) hal_ll_gpio_write_pin_output( (hal_ll_gpio_pin_t *)_handle, _value )
#else
void hal_gpio_write_pin_output( hal_gpio_pin_t *pin, uint8_t value );
#endif

/**
 * @brief Toggles the output state of a GPIO pin.
 *
 * @details
 * Inverts the current output state of the specified GPIO pin.
 * If the pin output is high, it will be set low, and vice versa.
 *
 * @param[in,out] pin Pointer to the GPIO pin structure to toggle.
 * See @ref hal_gpio_pin_t structure definition for more details.
 *
 * @return
 * - None.
 *
 * @note
 * - The pin must be configured as an output.
 *
 * @pre
 * - The pin must be initialized and configured as output.
 *
 * @post
 * - The pin output state is inverted.
 *
 * @warning
 * - Toggling an input pin may have no effect.
 *
 * @par Example Usage
 * @code{.c}
 *    // GPIO HAL pin context structure. *    hal_gpio_pin_t pin; * *    // Toggle pin logic state. *    hal_gpio_toggle_pin_output( &pin );
 * @endcode
 *
 * @par Limitations
 * - Only digital output pins can be toggled.
 *
 * @see hal_gpio_configure_pin()
 * @see hal_gpio_pin_t
 *
 * @link https://github.com/MikroElektronika/mikrosdk_v2/blob/master/hal/lib/include/hal_gpio.h#L358 Link to header @endlink.
 * @link https://github.com/MikroElektronika/mikrosdk_v2/blob/master/hal/lib/src/lib_hal_gpio/hal_gpio.c#L74 Link to source @endlink.
 */
#if defined(FLATTEN_ME) && (FLATTEN_ME_LEVEL >= FLATTEN_ME_LEVEL_MID)
#define hal_gpio_toggle_pin_output(_handle) hal_ll_gpio_toggle_pin_output( (hal_ll_gpio_pin_t *)_handle )
#else
void hal_gpio_toggle_pin_output( hal_gpio_pin_t *pin );
#endif

/**
 * @brief Sets the output state of a GPIO pin to high.
 *
 * @details
 * Drives the specified GPIO pin output to a logical high level.
 * The pin must be configured as an output for this operation.
 *
 * @param[in,out] pin Pointer to the GPIO pin structure to set.
 * See @ref hal_gpio_pin_t structure definition for more details.
 *
 * @return
 * - None.
 *
 * @note
 * - This function sets the pin output without affecting other pins.
 *
 * @pre
 * - The pin must be configured as an output.
 *
 * @post
 * - The pin output is set to high.
 *
 * @warning
 * - Setting an input pin may have no effect.
 *
 * @par Example Usage
 * @code{.c}
 *    // GPIO HAL pin context structure. *    hal_gpio_pin_t pin; * *    // Set pin logic state high (1). *    hal_gpio_set_pin_output( &pin );
 * @endcode
 *
 * @par Limitations
 * - Only digital output pins can be set.
 *
 * @see hal_gpio_configure_pin()
 * @see hal_gpio_pin_t
 *
 * @link https://github.com/MikroElektronika/mikrosdk_v2/blob/master/hal/lib/include/hal_gpio.h#L403 Link to header @endlink.
 * @link https://github.com/MikroElektronika/mikrosdk_v2/blob/master/hal/lib/src/lib_hal_gpio/hal_gpio.c#L81 Link to source @endlink.
 */
#if defined(FLATTEN_ME) && (FLATTEN_ME_LEVEL >= FLATTEN_ME_LEVEL_MID)
#define hal_gpio_set_pin_output(_handle) hal_ll_gpio_set_pin_output( (hal_ll_gpio_pin_t *)_handle )
#else
void hal_gpio_set_pin_output( hal_gpio_pin_t *pin );
#endif

/**
 * @brief Clears the output state of a GPIO pin to low.
 *
 * @details
 * Drives the specified GPIO pin output to a logical low level.
 * The pin must be configured as an output for this operation.
 *
 * @param[in,out] pin Pointer to the GPIO pin structure to clear.
 * See @ref hal_gpio_pin_t structure definition for more details.
 *
 * @return
 * - None.
 *
 * @note
 * - This function clears the pin output without affecting other pins.
 *
 * @pre
 * - The pin must be configured as an output.
 *
 * @post
 * - The pin output is set to low.
 *
 * @warning
 * - Clearing an input pin may have no effect.
 *
 * @par Example Usage
 * @code{.c}
 *    // GPIO HAL pin context structure. *    hal_gpio_pin_t pin; * *    // Set pin logic state low (0). *    hal_gpio_clear_pin_output( &pin );
 * @endcode
 *
 * @par Limitations
 * - Only digital output pins can be cleared.
 *
 * @see hal_gpio_configure_pin()
 * @see hal_gpio_pin_t
 *
 * @link https://github.com/MikroElektronika/mikrosdk_v2/blob/master/hal/lib/include/hal_gpio.h#L448 Link to header @endlink.
 * @link https://github.com/MikroElektronika/mikrosdk_v2/blob/master/hal/lib/src/lib_hal_gpio/hal_gpio.c#L88 Link to source @endlink.
 */
#if defined(FLATTEN_ME) && (FLATTEN_ME_LEVEL >= FLATTEN_ME_LEVEL_MID)
#define hal_gpio_clear_pin_output(_handle) hal_ll_gpio_clear_pin_output( (hal_ll_gpio_pin_t *)_handle )
#else
void hal_gpio_clear_pin_output( hal_gpio_pin_t *pin );
#endif

/**
 * @brief Configures a GPIO port with the specified name, mask, and direction.
 *
 * @details
 * Initializes and configures the given GPIO port structure with the specified
 * port name, bit mask, and direction (input or output). The mask specifies
 * which pins within the port are affected.
 *
 * @param[in,out] port Pointer to the GPIO port structure to configure.
 * See @ref hal_gpio_port_t structure definition for more details.
 * @param[in] name The port name identifier to configure.
 * See @ref hal_port_name_t for valid port names.
 * @param[in] mask Bit mask specifying which pins in the port to configure.
 * See @ref hal_gpio_mask_t for mask details.
 * @param[in] direction The direction to set for the selected pins.
 * See @ref hal_gpio_direction_t for possible values.
 *
 * @return
 * - None.
 *
 * @note
 * - Only pins specified by the mask are configured.
 *
 * @pre
 * - The hardware must support the specified port and pins.
 *
 * @post
 * - The port pins specified by the mask are configured and ready for I/O.
 *
 * @warning
 * - Incorrect mask or port name may cause hardware conflicts.
 *
 * @par Example Usage
 * @code{.c}
 *    // GPIO HAL port context structure. *    hal_gpio_port_t port; * *    // Configure port as digital output. *    hal_gpio_configure_port( &port, PORTB, 0xFF, HAL_GPIO_DIGITAL_OUTPUT );
 * @endcode
 *
 * @par Limitations
 * - Port configuration is limited to digital input/output modes.
 *
 * @see hal_gpio_direction_t
 * @see hal_gpio_port_t
 *
 * @link https://github.com/MikroElektronika/mikrosdk_v2/blob/master/hal/lib/include/hal_gpio.h#L497 Link to header @endlink.
 * @link https://github.com/MikroElektronika/mikrosdk_v2/blob/master/hal/lib/src/lib_hal_gpio/hal_gpio.c#L94 Link to source @endlink.
 */
void hal_gpio_configure_port( hal_gpio_port_t *port, hal_port_name_t name, hal_gpio_mask_t mask, hal_gpio_direction_t direction );

/**
 * @brief Reads the input state of a GPIO port.
 *
 * @details
 * Returns the current logical input levels of all pins in the specified GPIO port.
 * The returned value is a bitmask representing the state of each pin.
 *
 * @param[in] port Pointer to the GPIO port structure to read.
 * See @ref hal_gpio_port_t structure definition for more details.
 *
 * @return
 * - Bitmask representing the input states of the port pins.
 *
 * @note
 * - The port pins must be configured as inputs for valid readings.
 *
 * @pre
 * - The port must be configured and initialized.
 *
 * @post
 * - No side effects.
 *
 * @warning
 * - Reading from unconfigured ports may yield undefined results.
 *
 * @par Example Usage
 * @code{.c}
 *    // GPIO HAL port context structure. *    hal_gpio_port_t port; * *    // GPIO value holder. *    hal_port_size_t read_value; * *    // Read port state. *    read_value = hal_gpio_read_port_input( &port );
 * @endcode
 *
 * @par Limitations
 * - Only digital input states are read; analog states are not supported.
 *
 * @see hal_gpio_configure_port()
 * @see hal_gpio_port_t
 *
 * @link https://github.com/MikroElektronika/mikrosdk_v2/blob/master/hal/lib/include/hal_gpio.h#L541 Link to header @endlink.
 * @link https://github.com/MikroElektronika/mikrosdk_v2/blob/master/hal/lib/src/lib_hal_gpio/hal_gpio.c#L101 Link to source @endlink.
 */
#if defined(FLATTEN_ME) && (FLATTEN_ME_LEVEL >= FLATTEN_ME_LEVEL_MID)
#define hal_gpio_read_port_input(_handle) hal_ll_gpio_read_port_input( (hal_ll_gpio_port_t *)_handle )
#else
hal_port_size_t hal_gpio_read_port_input( hal_gpio_port_t *port );
#endif

/**
 * @brief Reads the output state of a GPIO port.
 *
 * @details
 * Returns the current logical output levels set on all pins in the specified GPIO port.
 * The returned value is a bitmask representing the output state of each pin.
 *
 * @param[in] port Pointer to the GPIO port structure to read.
 * See @ref hal_gpio_port_t structure definition for more details.
 *
 * @return
 * - Bitmask representing the output states of the port pins.
 *
 * @note
 * - The port pins must be configured as outputs for valid readings.
 *
 * @pre
 * - The port must be configured and initialized.
 *
 * @post
 * - No side effects.
 *
 * @warning
 * - Reading output state does not guarantee the actual pin voltage levels.
 *
 * @par Example Usage
 * @code{.c}
 *    // GPIO HAL port context structure. *    hal_gpio_port_t port; * *    // GPIO value holder. *    hal_port_size_t read_value; * *    // Read port state. *    read_value = hal_gpio_read_port_output( &port );
 * @endcode
 *
 * @par Limitations
 * - Only digital output states are read; actual pin states may differ due to hardware.
 *
 * @see hal_gpio_configure_port()
 * @see hal_gpio_port_t
 *
 * @link https://github.com/MikroElektronika/mikrosdk_v2/blob/master/hal/lib/include/hal_gpio.h#L586 Link to header @endlink.
 * @link https://github.com/MikroElektronika/mikrosdk_v2/blob/master/hal/lib/src/lib_hal_gpio/hal_gpio.c#L108 Link to source @endlink.
 */
#if defined(FLATTEN_ME) && (FLATTEN_ME_LEVEL >= FLATTEN_ME_LEVEL_MID)
#define hal_gpio_read_port_output(_handle) hal_ll_gpio_read_port_output( (hal_ll_gpio_port_t *)_handle )
#else
hal_port_size_t hal_gpio_read_port_output( hal_gpio_port_t *port );
#endif

/**
 * @brief Writes a logical output value to a GPIO port.
 *
 * @details
 * Sets the output levels of the specified GPIO port pins according to the given bitmask value.
 * Only pins configured as outputs will be affected.
 *
 * @param[in,out] port Pointer to the GPIO port structure to write.
 * See @ref hal_gpio_port_t structure definition for more details.
 * @param[in] value Bitmask representing the output values to set on the port pins.
 *
 * @return
 * - None.
 *
 * @note
 * - Writing to pins configured as inputs may have no effect.
 *
 * @pre
 * - The port must be configured as output.
 *
 * @post
 * - The port output registers are updated with the specified values.
 *
 * @warning
 * - Writing invalid values may cause undefined behavior.
 *
 * @par Example Usage
 * @code{.c}
 *    // GPIO HAL port context structure. *    hal_gpio_port_t port; * *    // Set port logic state to 0xAA. *    hal_gpio_write_port_output( &port, 0xAA );
 * @endcode
 *
 * @par Limitations
 * - Only digital output values are supported.
 *
 * @see hal_gpio_configure_port()
 * @see hal_gpio_port_t
 *
 * @link https://github.com/MikroElektronika/mikrosdk_v2/blob/master/hal/lib/include/hal_gpio.h#L632 Link to header @endlink.
 * @link https://github.com/MikroElektronika/mikrosdk_v2/blob/master/hal/lib/src/lib_hal_gpio/hal_gpio.c#L115 Link to source @endlink.
 */
#if defined(FLATTEN_ME) && (FLATTEN_ME_LEVEL >= FLATTEN_ME_LEVEL_MID)
#define hal_gpio_write_port_output(_handle,_value) hal_ll_gpio_write_port_output( (hal_ll_gpio_port_t *)_handle, _value )
#else
void hal_gpio_write_port_output( hal_gpio_port_t *port, hal_port_size_t value );
#endif

/**
 * @brief Fetches the pin number within a port from a pin name.
 *
 * @details
 * Calculates the pin number within its port by computing the modulo of the pin name
 * with the port size. This helps in identifying the specific pin index in the port.
 *
 * @param[in] pin_name The full pin name identifier.
 * See @ref hal_pin_name_t for valid pin names.
 *
 * @return
 * The pin number within the port as a hal_pin_name_t value.
 *
 * @note
 * - This function assumes pin names are encoded such that modulo with PORT_SIZE yields pin index.
 *
 * @pre
 * - The pin_name must be a valid pin identifier.
 *
 * @post
 * - Returns the pin index within the port.
 *
 * @warning
 * - Using invalid pin names may result in incorrect pin numbers.
 *
 * @par Example Usage
 * @code{.c}
 *    pin_name_t fetch_pin = hal_gpio_fetch_pin( GPIO_PB2 );
 * @endcode
 *
 * @par Limitations
 * - Only valid for pin names encoded with port and pin information.
 *
 * @see hal_pin_name_t
 *
 * @link https://github.com/MikroElektronika/mikrosdk_v2/blob/master/hal/lib/include/hal_gpio.h#L673 Link to header @endlink.
 * @link https://github.com/MikroElektronika/mikrosdk_v2/blob/master/hal/lib/src/lib_hal_gpio/hal_gpio.c Link to source @endlink.
 */
static inline hal_pin_name_t hal_gpio_fetch_pin(hal_pin_name_t pin_name) {
    return (hal_pin_name_t)((uint8_t)pin_name % PORT_SIZE);
}

/**
 * @brief Fetches the port number from a given pin name.
 *
 * @details
 * Determines the port number associated with the given pin name.
 * For 8-bit PIC microcontrollers, extracts the higher nibble of the pin name.
 * For other platforms, calculates the port by dividing the pin name by PORT_SIZE.
 *
 * @param[in] pin_name The full pin name identifier.
 * See @ref hal_pin_name_t for valid pin names.
 *
 * @return
 * The corresponding port number as a hal_port_name_t value.
 *
 * @note
 * - The method of extraction depends on the target platform.
 *
 * @pre
 * - The pin_name must be a valid pin identifier.
 *
 * @post
 * - Returns the port number associated with the pin.
 *
 * @warning
 * - Using invalid pin names may result in incorrect port numbers.
 *
 * @par Example Usage
 * @code{.c}
 *    port_name_t fetch_port = hal_gpio_fetch_port( GPIO_PB2 );
 * @endcode
 *
 * @par Limitations
 * - Platform-specific behavior; ensure correct platform macros are defined.
 *
 * @see hal_pin_name_t
 * @see hal_port_name_t
 *
 * @link https://github.com/MikroElektronika/mikrosdk_v2/blob/master/hal/lib/include/hal_gpio.h#L717 Link to header @endlink.
 * @link https://github.com/MikroElektronika/mikrosdk_v2/blob/master/hal/lib/src/lib_hal_gpio/hal_gpio.c Link to source @endlink.
 */
static inline hal_port_name_t hal_gpio_fetch_port(hal_pin_name_t pin_name) {
    #if defined(__XC8__) || defined(__MIKROC_AI_FOR_PIC__)
    return (hal_port_name_t)((((uint8_t)pin_name & 0xF0) >> 4));
    #else
    return (hal_port_name_t)((uint8_t)pin_name / PORT_SIZE);
    #endif
}

/*! @} */ // halgpiogroup
/*! @} */ // halgroup
/*! @} */ // pergroup

#ifdef __cplusplus
}
#endif

#endif // _HAL_GPIO_H_
// ------------------------------------------------------------------------- END
