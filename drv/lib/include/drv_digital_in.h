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
 * @file  drv_digital_in.h
 * @brief API for Digital input driver.
 */

#ifndef _DRV_DIGITAL_IN_H_
#define _DRV_DIGITAL_IN_H_

#ifdef __cplusplus
extern "C"{
#endif

#include "drv_name.h"
#include "hal_gpio.h"

/**
 * @brief Digital input driver error codes.
 *
 * @details
 * This enumeration defines the possible error codes returned by digital input driver functions.
 * DIGITAL_IN_SUCCESS indicates successful operation,
 * while DIGITAL_IN_UNSUPPORTED_PIN indicates an invalid or unsupported pin was specified.
 */
typedef enum
{
    DIGITAL_IN_SUCCESS = 0,    /*!< Success. */
    DIGITAL_IN_UNSUPPORTED_PIN = (-1) /*!< Error. */
} digital_in_err_t;

/**
 * @brief Digital input pin descriptor structure.
 *
 * @details
 * This structure holds the configuration information for a digital input pin,
 * including the base and mask of the GPIO pin used for digital input operations.
 */
typedef struct
{
    hal_gpio_pin_t pin; /*!< Structure defining pin base and mask. */
} digital_in_t;

/**
 * @addtogroup pergroup Microcontroller Peripherals
 * @{
 */

/**
 * @addtogroup drvgroup Driver Layer
 * @{
 */

/**
 * @addtogroup digingroup Digital Input Driver
 * @brief Digital Input Pin Driver API Reference.
 * @details This driver provids functions for configuring GPIO pin as digital input and reading logical value from it.
 * @{
 */

/**
 * @brief Initialize a digital input pin.
 *
 * @details
 * Configures the specified GPIO pin as a digital input.
 * The function initializes the digital_in_t structure with the pin configuration.
 * If the specified pin is not connected (HAL_PIN_NC), the function returns an error.
 *
 * @param[out] in Pointer to the digital_in_t structure to be initialized.
 * See @ref digital_in_t structure definition for more details.
 * @param[in] name The pin name to be configured as digital input.
 * See @ref pin_name_t for valid pin names.
 *
 * @return
 * - @ref DIGITAL_IN_SUCCESS on successful initialization.
 * - @ref DIGITAL_IN_UNSUPPORTED_PIN if the specified pin is not supported or invalid.
 *
 * @note
 * - The pin must be a valid GPIO pin capable of digital input.
 * - The function does not enable any internal pull-up or pull-down resistors.
 *
 * @pre
 * - The hardware GPIO module must be properly initialized.
 *
 * @post
 * - The digital_in_t structure is configured for the specified pin.
 *
 * @warning
 * - Passing HAL_PIN_NC as the pin name will result in an error.
 *
 * @par Example Usage
 * @code{.c}
 *     TODO: ADD EXAMPLE CODE FOR `digital_in_init(digital_in_t * in, pin_name_t name)`
 * @endcode
 *
 * @par Limitations
 * - Does not configure pin pull-up or pull-down resistors.
 *
 * @see digital_in_read()
 *
 * @link https://github.com/MikroElektronika/mikrosdk_v2/blob/master/drv/lib/include/drv_digital_in.h#L140 Link to header @endlink.
 * @link https://github.com/MikroElektronika/mikrosdk_v2/blob/master/drv/lib/src/lib_drv_digital_in/drv_digital_in.c#L46 Link to source @endlink.
 */
err_t digital_in_init( digital_in_t *in, pin_name_t name );

/**
 * @brief Read the logical state of a digital input pin.
 *
 * @details
 * Reads the current logical level of the configured digital input pin.
 * Returns 1 if the pin is at a high logic level, or 0 if it is low.
 * If the pin is not configured or invalid, returns 0.
 *
 * @param[in] in Pointer to the digital_in_t structure representing the digital input pin.
 * See @ref digital_in_t structure definition for more details.
 *
 * @return
 * - 1 if the digital input pin is at a high logic level.
 * - 0 if the digital input pin is at a low logic level or if the pin is invalid.
 *
 * @note
 * - The pin must be initialized with digital_in_init() before calling this function.
 * - This function may be implemented as a macro depending on compilation flags.
 *
 * @pre
 * - The digital input pin must be initialized and configured.
 *
 * @post
 * - The logical state of the pin is returned.
 *
 * @warning
 * - Reading from an uninitialized or unsupported pin may return 0.
 *
 * @par Example Usage
 * @code{.c}
 *     TODO: ADD EXAMPLE CODE FOR `digital_in_read(digital_in_t * in)`
 * @endcode
 *
 * @par Limitations
 * - None.
 *
 * @see digital_in_init()
 *
 * @link https://github.com/MikroElektronika/mikrosdk_v2/blob/master/drv/lib/include/drv_digital_in.h#L186 Link to header @endlink.
 * @link https://github.com/MikroElektronika/mikrosdk_v2/blob/master/drv/lib/src/lib_drv_digital_in/drv_digital_in.c#L58 Link to source @endlink.
 */
#if defined(FLATTEN_ME) && (FLATTEN_ME_LEVEL >= FLATTEN_ME_LEVEL_HIGH)
#define digital_in_read(_handle) hal_gpio_read_pin_input( (hal_gpio_pin_t *)_handle )
#else
uint8_t digital_in_read( digital_in_t *in );
#endif

/*! @} */ // digingroup
/*! @} */ // drvgroup
/*! @} */ // pergroup

#ifdef __cplusplus
}
#endif

#endif // _DRV_DIGITAL_IN_H_
// ------------------------------------------------------------------------- END
