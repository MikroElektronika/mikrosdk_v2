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
 * \file
 *
 * \brief The API for interfacing with FT800 based EVE Click Board.
 */
#ifndef _EVE_H_
#define _EVE_H_

#include "drv_digital_out.h"
#include "drv_spi_master.h"
#include "gl_types.h"

#include "eve_mikrobus.h"

/*!
 * \addtogroup compgroup Components
 * \brief Libraries for extension boards.
 * @{
 */

/*!
 * \addtogroup evegroup EVE Display
 * \brief FT800 based EVE Click display driver.
 * @{
 */

/*!
 * \brief Constant for setting minimum backlight.
 * \see eve_set_backlight
 */
#define EVE_MIN_BACKLIGHT ( 0x00 )
#define TFT_MIN_BACKLIGHT EVE_MIN_BACKLIGHT
/*!
 * \brief Constant for setting maximum backlight.
 * \see eve_set_backlight
 */
#define EVE_MAX_BACKLIGHT ( 0xFF )
#define TFT_MAX_BACKLIGHT EVE_MAX_BACKLIGHT

#ifndef DISPLAY_SPI_MIKROBUS
#define DISPLAY_SPI_MIKROBUS MIKROBUS_1
#endif

#define EVE_MAP_PINOUTS( eve_cfg )                                     \
    eve_cfg.eve_cs = MIKROBUS( DISPLAY_SPI_MIKROBUS, MIKROBUS_CS );    \
    eve_cfg.eve_sck = MIKROBUS( DISPLAY_SPI_MIKROBUS, MIKROBUS_SCK );  \
    eve_cfg.eve_sdi = MIKROBUS( DISPLAY_SPI_MIKROBUS, MIKROBUS_MOSI ); \
    eve_cfg.eve_sdo = MIKROBUS( DISPLAY_SPI_MIKROBUS, MIKROBUS_MISO ); \
    eve_cfg.eve_pd = MIKROBUS( DISPLAY_SPI_MIKROBUS, MIKROBUS_RST )

/*!
 * \brief EVE Display definition structure.
 */
typedef struct eve_display_s
{
    uint16_t display_width;  /*!< Display width resolution in pixels. */
    uint16_t display_height; /*!< Display height resolution in pixels. */
} eve_display_t;

/// Definition constant for EVE_CLICK display Click Board.
extern const eve_display_t EVE_CLICK;

/*!
 * \brief EVE Display library configuration structure.
 */
typedef struct
{
    const eve_display_t *board; /*!< Board definition constant. */

    hal_pin_name_t eve_cs;      /*!< CS pin name. */
    hal_pin_name_t eve_sck;     /*!< SCK pin name. */
    hal_pin_name_t eve_sdi;     /*!< SDI pin name. */
    hal_pin_name_t eve_sdo;     /*!< SDO pin name. */
    hal_pin_name_t eve_pd;      /*!< PD (power down) pin name. */
} eve_cfg_t;

#ifdef __cplusplus
extern "C"
{
#endif

/*!
 * \brief Initializes EVE Click Board module driver with given
 * configuration.
 * \param cfg Configuration structure.
 * \param driver TFT driver object structure used to store driver context data.
 */
void eve_init( eve_cfg_t *cfg, gl_driver_t *driver );

/*!
 * \brief Returns displays width in pixels.
 */
uint16_t eve_display_width();

/*!
 * \brief Returns displays height in pixels.
 */
uint16_t eve_display_height();

/*!
 * \brief Sets display's backlight intensity.
 *
 * \param intensity Backlight intensity.
 *
 * \see EVE_MIN_BACKLIGHT, EVE_MAX_BACKLIGHT
 */
void eve_set_backlight( uint8_t intensity );

/*!
 * \brief Writes RGB565 pixels to one display row.
 *
 * \param x Column of the first pixel.
 * \param y Row of the pixels.
 * \param pixels Little endian RGB565 pixel data.
 * \param length Number of pixels to write.
 */
void eve_write_pixels( uint16_t x, uint16_t y, uint8_t *pixels, uint16_t length );

/*! @} */ // evegroup
/*! @} */ // compgroup

#ifdef __cplusplus
}
#endif
#endif    // _EVE_H_
/*! @} */
