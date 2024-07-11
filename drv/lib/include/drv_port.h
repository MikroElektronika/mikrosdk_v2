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
** OF MERCHANTABILITY, EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED
** TO THE WARRANTIES FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT.
** IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM,
** DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT
** OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE
** OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
**
****************************************************************************/
/*!
 * @file  drv_port.h
 * @brief API for GPIO port driver.
 */

#ifndef _DRV_PORT_H_
#define _DRV_PORT_H_

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
    PORT_SUCCESS = 0, /*!< Success. */
    PORT_ERROR = (-1) /*!< Error. */
} port_err_t;

/**
 * @details Predefined enum values for Port driver pin direction.
 */
typedef enum
{
    PIN_DIRECTION_DIGITAL_INPUT = 0,  /*!< Define as digital input. */
    PIN_DIRECTION_DIGITAL_OUTPUT = 1  /*!< Define as digital output. */
} pin_direction_t;

/**
 * @brief Port driver context structure, consisted of the following fields :
 * @details User needs to specify values herein.
 * @note The values are specified by #port_init.
 * See #hal_gpio_port_t and #port_name_t for more details.
 * @warning  The contents of the context structure are used by the module and
 * must not be altered. Reading or writing data directly from a control structure
 * by user should be avoided.
 */
typedef struct
{
    hal_gpio_port_t port; /*!< Structure containing port address and port name. */
    port_name_t name;     /*!< Port name. */
} port_t;

/*!
 * @addtogroup pergroup Microcontroller Peripherals
 * @{
 */

/*!
 * @addtogroup drvgroup Driver Layer
 * @{
 */

/*!
 * @addtogroup portgroup Port Driver
 * @brief GPIO Port Driver API Reference.
 * @details Driver for configuring GPIO ports as
 * digital output/input and
 * setting/reading logical value.
 * @{
 */

/**
 * @brief Initialize GPIO port.
 * @details Initializes port driver context structure and
 * masked GPIO pins as digital output or digital input.
 * @param[in,out] port Port driver context structure.
 * See #port_t structure definition for detailed explanation.
 * @param[in] name Port name.
 * See #port_name_t structure definition for detailed explanation.
 * @param[in] mask GPIO pin mask.
 * See #port_size_t structure definition for detailed explanation.
 * @param[in] direction GPIO pin direction.
 * See #pin_direction_t structure definition for detailed explanation.
 * @return The function can return one of the values defined in
 * the #port_err_t enum list.
 * @pre Make sure that \p port structure has been declared.
 * See #port_t structure definition for detailed explanation.
 * @warning The following example includes pin mapping.
 * Take into consideration that different hardware might not have the same pins.
 * Make sure to accommodate pin name based on your hardware specifics.
 *
 * @b Example
 * @code
 *   // Port driver context structure.
 *   static port_t port;
 *
 *   // Initialize PORT_B as output.
 *   if ( PORT_SUCCESS == port_init( &port, PORT_B, 0xFF, PIN_DIRECTION_DIGITAL_OUTPUT ) ) {
 *       // No error
 *   } else {
 *       // Handle the error
 *   }
 * @endcode
 */
err_t port_init( port_t *port, port_name_t name, port_size_t mask,
                 pin_direction_t direction
               );

/**
 * @brief Write to port.
 * @details Writes \p value to beforehand initialized port.
 * @param[in] port Port driver context structure.
 * See #port_t structure definition for detailed explanation.
 * @param[in] value Bit map to write on port.
 * See #port_size_t structure definition for detailed explanation.
 * @return The function can return one of the values defined in
 * the #port_err_t enum list.
 * @pre Make sure that \p port structure has been declared and
 * initialized beforehand.
 * See #port_t structure definition and #port_init for detailed explanation.
 *
 * @b Example
 * @code
 *   // Write value to defined port.
 *   if ( PORT_SUCCESS == port_write( &port, value ) ) {
 *       // No error
 *   } else {
 *       // Handle the error
 *   }
 * @endcode
 */
#if defined(FLATTEN_ME) && (FLATTEN_ME_LEVEL >= FLATTEN_ME_LEVEL_HIGH)
#define port_write(_handle,_value) hal_gpio_write_port_output( (hal_gpio_port_t *)_handle, _value )
#else
err_t port_write( port_t *port, port_size_t value );
#endif

/**
 * @brief Read from port.
 * @details Reads from beforehand initialized port.
 * @param[in] port Port driver context structure.
 * See #port_t structure definition for detailed explanation.
 * @return Value read from port input state.
 * @pre Make sure that \p port structure has been declared and
 * initialized beforehand.
 * See #port_t structure definition and #port_init for detailed explanation.
 *
 * @b Example
 * @code
 *   // Read value holder.
 *   static port_size_t read_value;
 *
 *   // Read port.
 *   read_value = port_read_input( &port );
 * @endcode
 */
#if defined(FLATTEN_ME) && (FLATTEN_ME_LEVEL >= FLATTEN_ME_LEVEL_HIGH)
#define port_read_input(_handle) hal_gpio_read_port_input( (hal_gpio_port_t *)_handle )
#else
port_size_t port_read_input( port_t *port );
#endif

/**
 * @brief Read from port.
 * @details Reads from beforehand initialized port.
 * @param[in] port Port driver context structure.
 * See #port_t structure definition for detailed explanation.
 * @return Value read from port output state.
 * @pre Make sure that \p port structure has been declared and
 * initialized beforehand.
 * See #port_t structure definition and #port_init for detailed explanation.
 *
 * @b Example
 * @code
 *   // Read value holder.
 *   static port_size_t read_value;
 *
 *   // Read port.
 *   read_value = port_read_output( &port );
 * @endcode
 */
#if defined(FLATTEN_ME) && (FLATTEN_ME_LEVEL >= FLATTEN_ME_LEVEL_HIGH)
#define port_read_output(_handle) hal_gpio_read_port_output( (hal_gpio_port_t *)_handle )
#else
port_size_t port_read_output( port_t *port );
#endif

/**
 * @brief Read from port.
 * @details Reads from beforehand initialized port.
 * @param[in] port Port driver context structure.
 * See #port_t structure definition for detailed explanation.
 * @return Value read from port output state.
 * @pre Make sure that \p port structure has been declared and
 * initialized beforehand.
 * See #port_t structure definition and #port_init for detailed explanation.
 *
 * @b Example
 * @code
 *   // Read value holder.
 *   static port_size_t read_value;
 *
 *   // Read port.
 *   read_value = port_read( &port );
 * @endcode
 */
#define port_read port_read_output

/*! @} */ // portgroup
/*! @} */ // drvgroup
/*! @} */ // pergroup

#ifdef __cplusplus
}
#endif

#endif // _DRV_PORT_H_
// ------------------------------------------------------------------------- END
