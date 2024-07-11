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
 * \file
 *
 * \brief The API for interfacing with EasyTFT RESISTIVE display Board.
 */
#ifndef _TFT7_H_
#define _TFT7_H_

#include "drv_port.h"
#include "gl_types.h"
#include "board.h"
#include "gl.h"

/*!
 * \addtogroup compgroup Components
 * \brief Libraries for extension boards.
 * @{
 */

/*!
 * \addtogroup tft7group EasyTFT Board Capacitive
 * \brief EasyTFT Board Capacitive driver.
 * @{
 */

/*!
 * \brief Mapping for backlight control.
 */
#define TFT7_MIN_BACKLIGHT (0)
#define TFT7_BACKLIGHT_10  (0.1)
#define TFT7_BACKLIGHT_20  (0.2)
#define TFT7_BACKLIGHT_30  (0.3)
#define TFT7_BACKLIGHT_40  (0.4)
#define TFT7_BACKLIGHT_50  (0.5)
#define TFT7_BACKLIGHT_60  (0.6)
#define TFT7_BACKLIGHT_70  (0.7)
#define TFT7_BACKLIGHT_80  (0.8)
#define TFT7_BACKLIGHT_90  (0.9)
#define TFT7_MAX_BACKLIGHT (1)

#define TFT_MIN_BACKLIGHT TFT7_MIN_BACKLIGHT
#define TFT_MAX_BACKLIGHT TFT7_MAX_BACKLIGHT

/*!
 * \brief Mapping control pins.
 */
#define TFT7_MAP_CTRL_BITS( tft_cfg ) \
  tft_cfg.tft_rst = TFT_RST;\
  tft_cfg.tft_cs  = TFT_CS; \
  tft_cfg.tft_rs  = TFT_RS; \
  tft_cfg.tft_wr  = TFT_WR; \
  tft_cfg.tft_rd  = TFT_RD; \

#define TFT_MAP_CTRL_BITS TFT7_MAP_CTRL_BITS

/*!
 * \brief Mapping configuration structure to 8 bit host interface defined with
 * board.
 */
#define TFT7_MAP_CTRL_8BIT( tft_cfg ) \
  TFT7_MAP_CTRL_BITS( tft_cfg ); \
  tft_cfg.data_channel_0 = TFT_8BIT_DATA_PORT_CH0; \
  tft_cfg.data_channel_0_mask = TFT_8BIT_DATA_PORT_CH0_MASK; \
  tft_cfg.host_interface = TFT7_HOST_INTERFACE_8BIT;

#define TFT_MAP_CTRL_8BIT TFT7_MAP_CTRL_8BIT

/*!
 * \brief Mapping configuration structure to 16 bit host interface defined with
 * board.
 */
#define TFT7_MAP_CTRL_16BIT( tft_cfg ) \
  TFT7_MAP_CTRL_BITS( tft_cfg ); \
  tft_cfg.data_channel_0 = TFT_16BIT_DATA_PORT_CH0; \
  tft_cfg.data_channel_0_mask = TFT_16BIT_DATA_PORT_CH0_MASK; \
  tft_cfg.data_channel_1 = TFT_16BIT_DATA_PORT_CH1; \
  tft_cfg.data_channel_1_mask = TFT_16BIT_DATA_PORT_CH1_MASK; \
  tft_cfg.host_interface = TFT7_HOST_INTERFACE_16BIT;

#define TFT_MAP_CTRL_16BIT TFT7_MAP_CTRL_16BIT

/*!
 * \brief Host interface configuration enumeration.
 */
typedef enum
{
    TFT7_HOST_INTERFACE_8BIT = 0,
    TFT7_HOST_INTERFACE_16BIT
} tft7_host_interface_t;

/*!
 * \brief Mapping structure for display orientation.
 */
 typedef enum
{
    TFT_MODE_LANDSCAPE_UP = 0,
    TFT_MODE_PORTRAIT_LEFT,
    TFT_MODE_LANDSCAPE_DOWN,
    TFT_MODE_PORTRAIT_RIGHT
} tft7_orientation_t;

/*!
 * \brief EasyTFT Board definition structure.
 */
typedef struct tft7_board_s
{
    uint16_t display_width; /*!< Display width resolution in pixels. */
    uint16_t display_height; /*!< Display height resolution in pixels. */

    void ( *reset_procedure )( tft7_orientation_t orientation );
} tft7_board_t;

// Definition constant for EasyTFT board.
extern const tft7_board_t TFT_BOARD_EASY;

/*!
 * \brief EasyTFT Board library configuration structure.
 */
typedef struct
{
    const tft7_board_t *board; /*!< Board definition constant. */

    hal_pin_name_t tft_rst; /*!< RST pin name. */
    hal_pin_name_t tft_cs;  /*!< CS pin name. */
    hal_pin_name_t tft_rs;  /*!< D/C pin name. */
    hal_pin_name_t tft_rd;  /*!< RD pin name. */
    hal_pin_name_t tft_wr;  /*!< WR pin name. */
    hal_pin_name_t tft_pwm; /*!< PWM pin name. */

    hal_port_name_t data_channel_0; /*!< Port name for data channel 0. */
    uint32_t data_channel_0_mask;   /*!< Port mask for data channel 0. */

    hal_port_name_t data_channel_1; /*!< Port name for data channel 1. */
    uint32_t data_channel_1_mask;   /*!< Port mask for data channel 1. */

    tft7_host_interface_t host_interface; /*!< Host interface configuration. */

    const tft7_orientation_t *orientation;
} tft7_cfg_t;

#ifdef __cplusplus
extern "C"{
#endif

/*!
 * \brief Initializes TFT extension board module driver with given
 * configuration.
 * \param cfg Configuration structure.
 * \param driver TFT driver object structure used to store driver context data.
 * \return Returns TFT driver instance handle.
 */
void tft7_init( tft7_cfg_t *cfg, gl_driver_t *driver );

/*!
 * \brief Returns displays width in pixels.
 */
uint16_t tft7_display_width();

/*!
 * \brief Returns displays height in pixels.
 */
uint16_t tft7_display_height();

/*!
 * \brief Sets the active display orientation to @p orientation.
 * \param cfg Configuration structure.
 * \param driver TFT driver object structure used to store driver context data.
 * \param orientation Display orientation that will be set as active.
 * @return Nothing.
 */
void tft7_set_display_orientation( tft7_cfg_t *cfg, gl_driver_t *driver, tft7_orientation_t orientation );

/*!
 * \brief Sets the active display backlight to @p intensity.
 * \param intensity Display backlight intensity that will be set as active.
 * @return Nothing.
 */
void tft7_set_backlight( float intensity );

// TODO Implement set gamma.
// TODO Implement display on/off.

/*! @} */ // tft7group
/*! @} */ // compgroup

#ifdef __cplusplus
}
#endif
#endif // _TFT7_H_
/*! @} */
