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
 * @param[in,out] port Port driver context strucutre.
 * See #port_t structure definition for detailed explanation.
 * @param[in] name Port name.
 * See #port_name_t structure definition for detailed explanation.
 * @param[in] mask GPIO pin mask.
 * See #port_size_t structure definition for detailed explanation.
 * @param[in] direction GPIO pin direction.
 * See #pin_direction_t structure definition for detailed explanation.
 * @return Nothing.
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
 *   port_init( &port, PORT_B, mask, PIN_DIRECTION_DIGITAL_OUTPUT );
 * @endcode
 */
void port_init( port_t *port, port_name_t name, port_size_t mask,
                pin_direction_t direction
              );

/**
 * @brief Write to port.
 * @details Writes \p value to beforehand initialized port.
 * @param[in] port Port driver context strucutre.
 * See #port_t structure definition for detailed explanation.
 * @param[in] value Bit map to write on port.
 * See #port_size_t structure definition for detailed explanation.
 * @return Nothing.
 * @pre Make sure that \p port structure has been declared and
 * initialized beforehand.
 * See #port_t structure definition and #port_init for detailed explanation.
 *
 * @b Example
 * @code
 *   // Write value to defined port.
 *   port_write( &port, value );
 * @endcode
 */
void port_write( port_t *port, port_size_t value );

/**
 * @brief Read from port.
 * @details Reads from beforehand initialized port.
 * @param[in] port Port driver context strucutre.
 * See #port_t structure definition for detailed explanation.
 * @return Value read from port.
 * @pre Make sure that \p port structure has been declared and
 * initialized beforehand.
 * See #port_t structure definition and #port_init for detailed explanation.
 *
 * @b Example
 * @code
 *   // Read value holder.
 *   static port_size_t read_value;
 *
 *   // Read port and toggle value.
 *   read_value = port_read( &port );
 * @endcode
 */
port_size_t port_read( port_t *port );

/*! @} */ // portgroup
/*! @} */ // drvgroup
/*! @} */ // pergroup

#ifdef __cplusplus
}
#endif

#endif // _DRV_PORT_H_
// ------------------------------------------------------------------------- END
