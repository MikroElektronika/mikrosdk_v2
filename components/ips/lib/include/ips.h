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
 * \brief The API for interfacing with IPS SPI display Click Boards.
 */
#ifndef _IPS_H_
#define _IPS_H_

#include "drv_digital_out.h"
#include "drv_spi_master.h"
#include "gl_types.h"

/*!
 * \addtogroup compgroup Components
 * \brief Libraries for extension boards.
 * @{
 */

/*!
 * \addtogroup ipsgroup IPS SPI Display
 * \brief IPS SPI Display  driver.
 *
 * Driver for configuring GPIO as digital input pin and getting logical value.
 * @{
 */

/*!
 * \brief Constant for setting minimum backlight.
 * \see ips_set_backlight
 */
#define IPS_MIN_BACKLIGHT (0x00)
#define TFT_MIN_BACKLIGHT IPS_MIN_BACKLIGHT
/*!
 * \brief Constant for setting maximum backlight.
 * \see ips_set_backlight
 */
#define IPS_MAX_BACKLIGHT (0xFF)
#define TFT_MAX_BACKLIGHT IPS_MAX_BACKLIGHT

#ifdef MIKROBUS_POSITION_IPSDISPLAY2
#define DISPLAY_SPI_MIKROBUS MIKROBUS_POSITION_IPSDISPLAY2
#endif

#ifndef DISPLAY_SPI_MIKROBUS
#define DISPLAY_SPI_MIKROBUS MIKROBUS_1
#endif

#define IPS_MAP_PINOUTS(ips_cfg) \
  ips_cfg.ips_bck = MIKROBUS( DISPLAY_SPI_MIKROBUS, MIKROBUS_AN ); \
  ips_cfg.ips_rst = MIKROBUS( DISPLAY_SPI_MIKROBUS, MIKROBUS_RST ); \
  ips_cfg.ips_cs = MIKROBUS( DISPLAY_SPI_MIKROBUS, MIKROBUS_CS ); \
  ips_cfg.ips_sck = MIKROBUS( DISPLAY_SPI_MIKROBUS, MIKROBUS_SCK ); \
  ips_cfg.ips_sdi = MIKROBUS( DISPLAY_SPI_MIKROBUS, MIKROBUS_MOSI ); \
  ips_cfg.ips_sdo = MIKROBUS( DISPLAY_SPI_MIKROBUS, MIKROBUS_MISO ); \
  ips_cfg.ips_dc = MIKROBUS( DISPLAY_SPI_MIKROBUS, MIKROBUS_INT )

/*!
 * \brief IPS SPI Display definition structure.
 */
typedef struct ips_display_s
{
    uint16_t display_width; /*!< Display width resolution in pixels. */
    uint16_t display_height; /*!< Display height resolution in pixels. */

    void (*reset_procedure)(void);
} ips_display_t;

/// Definition constant for IPS_DISPLAY_CLICK display Click Board.
extern const ips_display_t IPS_DISPLAY_1_CLICK;

/// Definition constant for IPS_DISPLAY_2_CLICK display Click Board.
extern const ips_display_t IPS_DISPLAY_2_CLICK;

/*!
 * \brief IPS SPI Display library configuration structure.
 */
typedef struct
{
    const ips_display_t *board; /*!< Board definition constant. */

    hal_pin_name_t ips_bck; /*!< BCK pin name. */
    hal_pin_name_t ips_rst; /*!< RST pin name. */
    hal_pin_name_t ips_cs; /*!< CS pin name. */
    hal_pin_name_t ips_sck; /*!< SCK pin name. */
    hal_pin_name_t ips_sdi; /*!< SDI pin name. */
    hal_pin_name_t ips_sdo; /*!< SDO pin name. */
    hal_pin_name_t ips_dc; /*!< D/C pin name. */
} ips_cfg_t;


#ifdef __cplusplus
extern "C"{
#endif

/*!
 * \brief Initializes IPS Click Board module driver with given
 * configuration.
 * \param driver TFT driver object structure used to store driver context data.
 * \param cfg Configuration structure.
 * \return Returns TFT driver instance handle.
 */
void ips_init(ips_cfg_t *cfg, gl_driver_t *driver);

/*!
 * \brief Returns displays width in pixels.
 */
uint16_t ips_display_width();

/*!
 * \brief Returns displays height in pixels.
 */
uint16_t ips_display_height();

/*!
 * \brief Sets display's backlight intensity.
 *
 * \param intensity Backlight intensity.
 *
 * \see ips_MIN_BACKLIGHT, ips_MAX_BACKLIGHT
 */
void ips_set_backlight(uint8_t intensity);

/*! @} */ // ipsgroup
/*! @} */ // compgroup

#ifdef __cplusplus
}
#endif
#endif // _IPS_H_
/*! @} */
