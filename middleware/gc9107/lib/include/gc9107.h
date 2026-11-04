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
 * @file  gc9107.h
 * @brief GC9107 Display Controller Driver.
 */

#ifndef GC9107_H
#define GC9107_H

#include "drv_digital_out.h"
#include "drv_spi_master.h"

/**
 * @brief GC9107 Configuration Object.
 */
typedef struct
{
    hal_pin_name_t bck; /*!< Backlight pin. */
    hal_pin_name_t rst; /*!< Reset pin. */
    hal_pin_name_t cs;  /*!< Chip Select pin. */
    hal_pin_name_t sck; /*!< SPI Clock pin. */
    hal_pin_name_t sdi; /*!< SPI Data IN pin. */
    hal_pin_name_t sdo; /*!< SPI Data Out pin. */
    hal_pin_name_t rs;  /*!< Data/Command select pin. */

    uint16_t width;     /*!< Display width. */
    uint16_t height;    /*!< Display height. */
} gc9107_cfg_t;

/**
 * @brief GC9107 Context Object.
 * @details Context object definition for GC9107 display controller.
 *          This structure holds information about the current state of the
 *          controller.
 */
typedef struct
{
    spi_master_t spi; /**< Communication module object. */

    uint16_t width;   /**< Display width in pixels. */
    uint16_t height;  /**< Display height in pixels. */
} gc9107_t;

/*!
 * @addtogroup middlewaregroup Middleware
 * @{
 */

/*!
 * @addtogroup GC9107 Display Controller Driver
 * @brief GC9107 Display Controller Driver API reference.
 * @details API for configuring and manipulating GC9107 Display Controller driver.
 * @{
 */

/**
 * @brief GC9107 Display Controller initialization.
 * @details This function opens the SPI, initializes the control pins and stores
 *          the display size.
 * @param[out] ctx : GC9107 context object. See #gc9107_t structure definition
 *                   for detailed explanation.
 * @param[in] cfg : GC9107 configuration object. See #gc9107_cfg_t structure
 *                  definition for detailed explanation.
 * @return Nothing.
 */
void gc9107_init( gc9107_t *ctx, gc9107_cfg_t *cfg );

/**
 * @brief Send command to GC9107 Display Controller.
 * @details This function sends command to GC9107 Display Controller.
 * @param[in] command : command to be sent. See @ref gc9107_commands for command
 *                      list.
 * @return Nothing.
 */
void gc9107_write_command( uint8_t command );

/**
 * @brief Send data to GC9107 Display Controller.
 * @details This function sends data to GC9107 Display Controller.
 * @param[in] param : data to be sent.
 * @return Nothing.
 */
void gc9107_write_param( uint8_t param );

/**
 * @brief Get SPI handle used by GC9107 driver.
 * @details This function returns the SPI handle opened by @ref gc9107_init, so other
 * code talking to the same display can reuse it instead of opening SPI again.
 * @return Pointer to the SPI handle.
 */
spi_master_t *gc9107_get_spi( void );

/**
 * @brief Get display width.
 * @details This function returns the width of the GC9107 controller based display.
 * @return Display width.
 */
uint16_t gc9107_get_display_width();

/**
 * @brief Get display height.
 * @details This function returns the height of the GC9107 controller based display.
 * @return Display height.
 */
uint16_t gc9107_get_display_height();

/**
 * @brief Reset device.
 * @details This function resets the GC9107 driver.
 * @return Nothing.
 */
void gc9107_reset();

/**
 * @brief Configure display.
 * @details This function sends the GC9107 initialization command sequence and
 *          turns the display on.
 * @return Nothing.
 */
void gc9107_configure();

/*!
 * @brief Sets display's backlight intensity.
 * @param[in] intensity Backlight intensity.
 * @note PWM control not implemented.
 * @retval Nothing
 */
void gc9107_set_backlight( uint8_t intensity );

/*! @} */ // GC9107
/*! @} */ // middlewaregroup

#endif // GC9107_H
