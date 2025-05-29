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
 * @file  drv_digital_out.h
 * @brief API for Digital output driver.
 */

#ifndef _DRV_DIGITAL_OUT_H_
#define _DRV_DIGITAL_OUT_H_

#ifdef __cplusplus
extern "C"{
#endif

#include "drv_name.h"
#include "hal_gpio.h"

/**
 * @brief Digital output error codes enumeration.
 *
 * @details
 * Defines possible return status codes for digital output operations.
 * DIGITAL_OUT_SUCCESS indicates successful operation,
 * DIGITAL_OUT_UNSUPPORTED_PIN indicates an invalid or unsupported pin was specified.
 */
typedef enum
{
    DIGITAL_OUT_SUCCESS = 0,    /*!< Success. */
    DIGITAL_OUT_UNSUPPORTED_PIN = (-1) /*!< Error. */
} digital_out_err_t;

/**
 * @brief Digital output pin descriptor structure.
 *
 * @details
 * This structure holds the configuration for a digital output pin,
 * including the base and mask information required for GPIO operations.
 */
typedef struct
{
    hal_gpio_pin_t pin; /*!< Structure defining pin base and mask. */
} digital_out_t;

/**
 * @addtogroup pergroup Microcontroller Peripherals
 * @{
 */

/**
 * @addtogroup drvgroup Driver Layer
 * @{
 */

/**
 * @addtogroup digoutgroup Digital Output Driver
 * @brief Digital Output Pin Driver API Reference.
 * @details This driver provids functions for configuring GPIO pin as digital output and setting logical value to it.
 * @{
 */

/**
 * @brief Initialize a digital output pin.
 *
 * @details
 * Configures the specified pin as a digital output.
 * The function sets up the pin direction and prepares it for output operations.
 *
 * @param[out] out Pointer to the digital_out_t structure to initialize.
 * See @ref digital_out_t structure definition for more details.
 * @param[in] name Pin name to be configured as digital output.
 * See @ref pin_name_t type for valid pin names.
 *
 * @return
 * - @ref DIGITAL_OUT_SUCCESS on successful initialization.
 * - @ref DIGITAL_OUT_UNSUPPORTED_PIN if the specified pin is not supported or invalid.
 *
 * @note
 * - The pin must be valid and not equal to HAL_PIN_NC.
 * - This function must be called before any other digital output operations on the pin.
 *
 * @pre
 * - The hardware GPIO subsystem must be initialized.
 *
 * @post
 * - The pin is configured as a digital output and ready for use.
 *
 * @warning
 * - Passing an invalid pin name will result in an error.
 *
 * @par Example Usage
 * @code{.c}
 *    // Digital output driver context structure. *    digital_out_t pin; * *    // Initializes digital output driver context structure and individual GPIO pin as digital output. *    if ( DIGITAL_OUT_SUCCESS == digital_out_init( &pin, GPIO_PB2 ) ) { *        // No error
 *    } else { *        // Handle the error
 *    }
 * @endcode
 *
 * @par Limitations
 * - Only pins supported by the underlying hardware can be initialized.
 *
 * @see digital_out_high()
 * @see digital_out_low()
 * @see digital_out_toggle()
 * @see digital_out_write()
 * @see digital_out_read()
 *
 * @link https://github.com/MikroElektronika/mikrosdk_v2/blob/master/drv/lib/include/drv_digital_out.h#L143 Link to header @endlink.
 * @link https://github.com/MikroElektronika/mikrosdk_v2/blob/master/drv/lib/src/lib_drv_digital_out/drv_digital_out.c#L46 Link to source @endlink.
 */
err_t digital_out_init( digital_out_t *out, pin_name_t name );

/**
 * @brief Set the digital output pin to a high logic level.
 *
 * @details
 * Drives the configured digital output pin to a logical high state.
 * This function sets the pin output voltage to the high level defined by the hardware.
 *
 * @param[in] out Pointer to the digital_out_t structure representing the pin.
 * See @ref digital_out_t structure definition for more details.
 *
 * @return
 * - @ref DIGITAL_OUT_SUCCESS on success.
 * - @ref DIGITAL_OUT_UNSUPPORTED_PIN if the pin is invalid or not configured.
 *
 * @note
 * - The pin must be initialized before calling this function.
 *
 * @pre
 * - digital_out_init() must have been called successfully.
 *
 * @post
 * - The pin output is set to high.
 *
 * @warning
 * - Calling this function on an uninitialized or unsupported pin may cause undefined behavior.
 *
 * @par Example Usage
 * @code{.c}
 *    // Digital output driver context structure. *    digital_out_t pin; * *    // Set pin to logical high state (1). *    if ( DIGITAL_OUT_SUCCESS == digital_out_high( &pin ) ) { *        // No error
 *    } else { *        // Handle the error
 *    }
 * @endcode
 *
 * @par Limitations
 * - This function may be implemented as a macro depending on configuration.
 *
 * @see digital_out_low()
 * @see digital_out_toggle()
 * @see digital_out_write()
 *
 * @link https://github.com/MikroElektronika/mikrosdk_v2/blob/master/drv/lib/include/drv_digital_out.h#L189 Link to header @endlink.
 * @link https://github.com/MikroElektronika/mikrosdk_v2/blob/master/drv/lib/src/lib_drv_digital_out/drv_digital_out.c#L58 Link to source @endlink.
 */
#if defined(FLATTEN_ME) && (FLATTEN_ME_LEVEL >= FLATTEN_ME_LEVEL_HIGH)
#define digital_out_high(_handle) hal_gpio_set_pin_output( (hal_gpio_pin_t *)_handle )
#else
err_t digital_out_high( digital_out_t *out );
#endif

/**
 * @brief Set the digital output pin to a low logic level.
 *
 * @details
 * Drives the configured digital output pin to a logical low state.
 * This function sets the pin output voltage to the low level defined by the hardware.
 *
 * @param[in] out Pointer to the digital_out_t structure representing the pin.
 * See @ref digital_out_t structure definition for more details.
 *
 * @return
 * - @ref DIGITAL_OUT_SUCCESS on success.
 * - @ref DIGITAL_OUT_UNSUPPORTED_PIN if the pin is invalid or not configured.
 *
 * @note
 * - The pin must be initialized before calling this function.
 *
 * @pre
 * - digital_out_init() must have been called successfully.
 *
 * @post
 * - The pin output is set to low.
 *
 * @warning
 * - Calling this function on an uninitialized or unsupported pin may cause undefined behavior.
 *
 * @par Example Usage
 * @code{.c}
 *    // Digital output driver context structure. *    digital_out_t pin; * *    // Set pin to logical low state (0). *    if ( DIGITAL_OUT_SUCCESS == digital_out_low( &pin ) ) { *        // No error
 *    } else { *        // Handle the error
 *    }
 * @endcode
 *
 * @par Limitations
 * - This function may be implemented as a macro depending on configuration.
 *
 * @see digital_out_high()
 * @see digital_out_toggle()
 * @see digital_out_write()
 *
 * @link https://github.com/MikroElektronika/mikrosdk_v2/blob/master/drv/lib/include/drv_digital_out.h#L236 Link to header @endlink.
 * @link https://github.com/MikroElektronika/mikrosdk_v2/blob/master/drv/lib/src/lib_drv_digital_out/drv_digital_out.c#L70 Link to source @endlink.
 */
#if defined(FLATTEN_ME) && (FLATTEN_ME_LEVEL >= FLATTEN_ME_LEVEL_HIGH)
#define digital_out_low(_handle) hal_gpio_clear_pin_output( (hal_gpio_pin_t *)_handle )
#else
err_t digital_out_low( digital_out_t *out );
#endif

/**
 * @brief Toggle the digital output pin state.
 *
 * @details
 * Changes the output state of the configured digital output pin to the opposite logic level.
 * If the pin is currently high, it will be set to low, and vice versa.
 *
 * @param[in] out Pointer to the digital_out_t structure representing the pin.
 * See @ref digital_out_t structure definition for more details.
 *
 * @return
 * - @ref DIGITAL_OUT_SUCCESS on success.
 * - @ref DIGITAL_OUT_UNSUPPORTED_PIN if the pin is invalid or not configured.
 *
 * @note
 * - The pin must be initialized before calling this function.
 *
 * @pre
 * - digital_out_init() must have been called successfully.
 *
 * @post
 * - The pin output state is toggled.
 *
 * @warning
 * - Calling this function on an uninitialized or unsupported pin may cause undefined behavior.
 *
 * @par Example Usage
 * @code{.c}
 *    // Digital output driver context structure. *    digital_out_t pin; * *    // Toggle pin state. *    if ( DIGITAL_OUT_SUCCESS == digital_out_toggle( &pin ) ) { *        // No error
 *    } else { *        // Handle the error
 *    }
 * @endcode
 *
 * @par Limitations
 * - This function may be implemented as a macro depending on configuration.
 *
 * @see digital_out_high()
 * @see digital_out_low()
 * @see digital_out_write()
 *
 * @link https://github.com/MikroElektronika/mikrosdk_v2/blob/master/drv/lib/include/drv_digital_out.h#L283 Link to header @endlink.
 * @link https://github.com/MikroElektronika/mikrosdk_v2/blob/master/drv/lib/src/lib_drv_digital_out/drv_digital_out.c#L82 Link to source @endlink.
 */
#if defined(FLATTEN_ME) && (FLATTEN_ME_LEVEL >= FLATTEN_ME_LEVEL_HIGH)
#define digital_out_toggle(_handle) hal_gpio_toggle_pin_output( (hal_gpio_pin_t *)_handle )
#else
err_t digital_out_toggle( digital_out_t *out );
#endif

/**
 * @brief Write a logical value to the digital output pin.
 *
 * @details
 * Sets the output state of the configured digital output pin to the specified logical value.
 * A non-zero value sets the pin high; zero sets it low.
 *
 * @param[in] out Pointer to the digital_out_t structure representing the pin.
 * See @ref digital_out_t structure definition for more details.
 * @param[in] value Logical value to write to the pin (0 or non-zero).
 *
 * @return
 * - @ref DIGITAL_OUT_SUCCESS on success.
 * - @ref DIGITAL_OUT_UNSUPPORTED_PIN if the pin is invalid or not configured.
 *
 * @note
 * - The pin must be initialized before calling this function.
 *
 * @pre
 * - digital_out_init() must have been called successfully.
 *
 * @post
 * - The pin output is set to the specified logical value.
 *
 * @warning
 * - Calling this function on an uninitialized or unsupported pin may cause undefined behavior.
 *
 * @par Example Usage
 * @code{.c}
 *    // Digital output driver context structure. *    digital_out_t pin; * *    // Value to be written. *    uint8_t write_value = 1; * *    // Write value to GPIO port. *    if ( DIGITAL_OUT_SUCCESS == digital_out_write( &pin, write_value ) ) { *        // No error
 *    } else { *        // Handle the error
 *    }
 * @endcode
 *
 * @par Limitations
 * - This function may be implemented as a macro depending on configuration.
 *
 * @see digital_out_high()
 * @see digital_out_low()
 * @see digital_out_toggle()
 *
 * @link https://github.com/MikroElektronika/mikrosdk_v2/blob/master/drv/lib/include/drv_digital_out.h#L331 Link to header @endlink.
 * @link https://github.com/MikroElektronika/mikrosdk_v2/blob/master/drv/lib/src/lib_drv_digital_out/drv_digital_out.c#L94 Link to source @endlink.
 */
#if defined(FLATTEN_ME) && (FLATTEN_ME_LEVEL >= FLATTEN_ME_LEVEL_HIGH)
#define digital_out_write(_handle,_value) hal_gpio_write_pin_output( (hal_gpio_pin_t *)_handle, _value )
#else
err_t digital_out_write( digital_out_t *out, uint8_t value );
#endif

/**
 * @brief Read the current logical state of the digital output pin.
 *
 * @details
 * Returns the current output state of the configured digital output pin.
 * The returned value is non-zero if the pin is high, or zero if the pin is low.
 *
 * @param[in] out Pointer to the digital_out_t structure representing the pin.
 * See @ref digital_out_t structure definition for more details.
 *
 * @return
 * - Non-zero value if the pin output is high.
 * - Zero if the pin output is low or if the pin is invalid.
 *
 * @note
 * - The pin must be initialized before calling this function.
 *
 * @pre
 * - digital_out_init() must have been called successfully.
 *
 * @post
 * - No change to the pin state.
 *
 * @warning
 * - Calling this function on an uninitialized or unsupported pin may return zero.
 *
 * @par Example Usage
 * @code{.c}
 *    // Digital output driver context structure. *    digital_out_t pin; * *    // GPIO value holder. *    uint8_t read_value; * *    // Read digital output value. *    read_value = digital_out_read( &pin );
 * @endcode
 *
 * @par Limitations
 * - This function may be implemented as a macro depending on configuration.
 *
 * @see digital_out_write()
 *
 * @link https://github.com/MikroElektronika/mikrosdk_v2/blob/master/drv/lib/include/drv_digital_out.h#L376 Link to header @endlink.
 * @link https://github.com/MikroElektronika/mikrosdk_v2/blob/master/drv/lib/src/lib_drv_digital_out/drv_digital_out.c#L106 Link to source @endlink.
 */
#if defined(FLATTEN_ME) && (FLATTEN_ME_LEVEL >= FLATTEN_ME_LEVEL_HIGH)
#define digital_out_read(_handle) hal_gpio_read_pin_output( (hal_gpio_pin_t *)_handle )
#else
uint8_t digital_out_read( digital_out_t *out );
#endif

/*! @} */ // digoutgroup
/*! @} */ // drvgroup
/*! @} */ // pergroup

#ifdef __cplusplus
}
#endif

#endif // _DRV_DIGITAL_OUT_H_
// ------------------------------------------------------------------------- END
