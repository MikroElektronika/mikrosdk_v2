/****************************************************************************
**
** Copyright (C) 2022 MikroElektronika d.o.o.
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
** OF MERCHANTABILITY, EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED
** TO THE WARRANTIES FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT.
** IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM,
** DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT
** OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE
** OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
**
****************************************************************************/
/*!
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
 * @details Return values.
 */
typedef enum
{
    DIGITAL_IN_SUCCESS = 0,    /*!< Success. */
    DIGITAL_IN_UNSUPPORTED_PIN = (-1) /*!< Error. */
} digital_in_err_t;

/**
 * @brief Digital input driver context structure, consisted of the following fields :
 * @details The context structure for storing driver internal state.
 * @note The values are specified by #digital_in_init.
 * See #hal_gpio_pin_t for more details.
 * @warning  The contents of the context structure are used by the module and
 * must not be altered. Reading or writing data directly from a control structure
 * by user should be avoided.
 */
typedef struct
{
    hal_gpio_pin_t pin; /*!< Structure defining pin base and mask. */
} digital_in_t;

/*!
 * @addtogroup pergroup Microcontroller Peripherals
 * @{
 */

/*!
 * @addtogroup drvgroup Driver Layer
 * @{
 */

/*!
 * @addtogroup digingroup Digital Input Driver
 * @brief Digital Input Pin Driver API Reference.
 * @details This driver provids functions for configuring GPIO pin as digital input and reading logical value from it.
 * @{
 */

/**
 * @brief Initialize GPIO pin.
 * @details Initializes digital input driver context structure
 * and individual GPIO pin as digital input.
 * @param[in,out] in Digital input driver context structure.
 * See #digital_in_t structure definition for detailed explanation.
 * @param[in] name The name of the GPIO pin.
 * See #pin_name_t structure definition for detailed explanation.
 * @return The function can return one of the values defined in
 * the #digital_out_err_t enum list.
 * @pre Make sure that \p in structure has been declared.
 * See #digital_in_err_t structure definition for detailed explanation.
 * @warning The following example includes pin mapping.
 * Take into consideration that different hardware might not have the same pins.
 * Make sure to accommodate pin name based on your hardware specifics.
 *
 * @b Example
 * @code
 *   // Digital input driver context structure.
 *   static digital_in_t input_pin;
 *
 *   // Initializes digital input driver context structure and individual GPIO pin as digital input.
 *   digital_in_init( &input_pin, PB2 );
 * @endcode
 */
err_t digital_in_init( digital_in_t *in, pin_name_t name );

/**
 * @brief Read GPIO pin.
 * @details Reads the current input value of the individual GPIO pin.
 * @param[in] in Digital input driver context structure.
 * See #digital_in_t structure definition for detailed explanation.
 * @return Function returns pin logical state (1 or 0).
 * @pre Make sure that \p in structure has been declared and
 * initialized beforehand.
 * See #digital_in_t structure definition and #digital_in_init for detailed explanation.
 * @note Return value depends on signal being input to current pin.
 *
 * @b Example
 * @code
 *   // GPIO value holder.
 *   uint8_t value;
 *
 *   // Read digital input value.
 *   value = digital_in_read( &input_pin );
 * @endcode
 */
uint8_t digital_in_read( digital_in_t *in );

/*! @} */ // digingroup
/*! @} */ // drvgroup
/*! @} */ // pergroup

#ifdef __cplusplus
}
#endif

#endif // _DRV_DIGITAL_IN_H_
// ------------------------------------------------------------------------- END
