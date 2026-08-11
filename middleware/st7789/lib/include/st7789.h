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
/*!
 * @file  st7789.h
 * @brief ST7789 Display Controller Driver.
 */

#ifndef ST7789_H
#define ST7789_H

#include "drv_spi_master.h"
#include "tp.h"

/**
 * @brief Map adequate control pins.
 * @note This function is a placeholder, current screens based on this driver do not have
 * touch screen drivers yet.
 */
#define TP_ST7789_MAP_PINS( cfg ) \
   do                             \
   {                              \
   } while ( 0 )

/**
 * @brief ST7789 Touch Configuration Object.
 * @details Configuration object definition for TP ST7789 touch controller.
 */
typedef struct
{
   uint16_t width;  /**< Touch panel width in pixels. */
   uint16_t height; /**< Touch panel height in pixels. */
} tp_st7789_cfg_t;

/**
 * @brief TP ST7789 Context Object.
 * @details Context object definition for ST7789 touch controller.
 *          This structure holds information about the current state of the
 *          controller.
 */
typedef struct
{
   uint16_t width;  /**< Touch panel width in pixels. */
   uint16_t height; /**< Touch panel height in pixels. */
} tp_st7789_t;

/**
 * @brief ST7789 Configuration Object.
 * @details Configuration object definition for ST7789 display controller.
 */
typedef struct
{
   hal_pin_name_t bck; /*!< Backlight pin. */
   hal_pin_name_t rst; /*!< Reset pin. */
   hal_pin_name_t cs;  /*!< Chip Select pin. */
   hal_pin_name_t sck; /*!< SPI Clock pin. */
   hal_pin_name_t sdi; /*!< SPI Data IN pin. */
   hal_pin_name_t sdo; /*!< SPI Data Out pin. */
   hal_pin_name_t rs;  /*!< Data/Command select pin */

   uint16_t width;     /*!< Display width. */
   uint16_t height;    /*!< Display height. */
} st7789_cfg_t;

/**
 * @brief ST7789 Context Object.
 * @details Context object definition for ST7789 touch controller.
 *          This structure holds information about the current state of the
 *          controller.
 */
typedef struct
{
   spi_master_t spi; /**< Communication module object. */

   uint16_t width;   /**< Touch panel width in pixels. */
   uint16_t height;  /**< Touch panel height in pixels. */

   bool pen_down;    /**< Utility helper variable used for interpreting events. */
} st7789_t;

/*!
 * @addtogroup middlewaregroup Middleware
 * @{
 */

/*!
 * @addtogroup ST7789 Display Controller Driver
 * @brief ST7789 Display Controller Driver API reference.
 * @details API for configuring and manipulating ST7789 Display Controller driver.
 * @{
 */

/**
 * @brief ST7789 Display Controller initialization.
 * @details This function initializes ST7789 Display Controller context object to
 *          default values and allows driver interface object to be linked with
 *          ST7789 Display Controller driver functions.
 * @param[out] ctx : ST7789 context object. See #st7789_t structure definition
 *                   for detailed explanation.
 * @param[in] cfg : ST7789 configuration object. See #st7789_cfg_t structure
 *                  definition for detailed explanation.
 * @param[out] drv : TP driver interface object. See #tp_drv_t structure
 *                   definition for detailed explanation (uninmplemented).
 * @return Nothing.
 */
void st7789_init( st7789_t *ctx, st7789_cfg_t *cfg, tp_drv_t *drv );

/**
 * @brief Send command to ST7789 Display Controller.
 * @details This function sends command to ST7789 Display Controller.
 * @param[in] command : command to be sent. See @ref st7789_commands for command
 *                      list.
 * @return Nothing.
 */
void st7789_write_command( uint8_t command );

/**
 * @brief Send data to ST7789 Display Controller.
 * @details This function sends data to ST7789 Display Controller.
 * @param[in] param : data to be sent.
 * @return Nothing.
 */
void st7789_write_param( uint8_t param );

/**
 * @brief Get display width.
 * @details This function returns the width of the ST7789 controller based display.
 * @return Display width.
 */
uint16_t st7789_get_display_width();

/**
 * @brief Get display height.
 * @details This function returns the height of the ST7789 controller based display.
 * @return Display height.
 */
uint16_t st7789_get_display_height();

/**
 * @brief Reset device.
 * @details This function resets the ST7789 driver.
 * @return Nothing.
 */
void st7789_reset();

/*!
 * @brief Sets display's backlight intensity.
 * @param[in] intensity Backlight intensity.
 * @note PWM control not implemented.
 * @retval Nothing
 */
void st7789_set_backlight( uint8_t intensity );

/**
 * @brief TP ST7789 Initialization Function.
 * @details  This function initializes TP ST7789 context object using configuration values
 * from TP ST7789 configuration object.
 * @note This function is a placeholder, current screens based on this driver do not have
 * touch screen drivers yet.
 * @param[in] ctx Initialized TP ST7789 context structure.
 * @param[in] cfg TP ST7789 configuration object.
 * @param[out] drv TP driver interface object. See @ref tp_drv_t structure
 * definition for detailed explanation.
 * @retval @li @c TP_OK OK,
 * See @ref tp_err_t structure definition for detailed explanation.
 */
tp_err_t tp_st7789_init( tp_st7789_t *ctx, tp_st7789_cfg_t *cfg, tp_drv_t *drv );

/**
 * @brief TP ST7789 configuration object setup function.
 * @details This function initializes TP ST7789 configuration structure to default values.
 * @note This function is a placeholder, current screens based on this driver do not have
 * touch screen drivers yet.
 * @param[out] cfg TP ST7789 configuration object.
 * @retval Nothing.
 */
void tp_st7789_cfg_setup( tp_st7789_cfg_t *cfg );

/**
 * @brief TP ST7789 Default Configuration Function.
 * @details Configures the device to default configuration.
 * @note This function is a placeholder, current screens based on this driver do not have
 * touch screen drivers yet.
 * @param[in] ctx Initialized TP ST7789 context structure.
 * @retval Nothing.
 */
void tp_st7789_default_cfg( tp_st7789_t *ctx );

/*! @} */ // st7789
/*! @} */ // mwgroup

#endif // ST7789_H
// ------------------------------------------------------------------------- END
