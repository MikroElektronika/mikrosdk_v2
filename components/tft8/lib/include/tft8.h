/****************************************************************************
**
** Copyright (C) 2021 MikroElektronika d.o.o.
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
 * \brief The API for interfacing with TFT BOARD CAPCAITIVE display boards.
 */
#ifndef TFT8_H
#define TFT8_H

#include "drv_digital_out.h"
#include "drv_port.h"
#include "gl_types.h"

/*!
 * \addtogroup compgroup Components
 * \brief Libraries for extension boards.
 * @{
 */

/*!
 * \addtogroup tft8group TFT Board Capacitive
 * \brief TFT Board Capacitive  driver.
 *
 * Driver for configuring GPIO as digital input pin and getting logical value.
 * @{
 */


/*!
 * \brief Constant for setting minimum backlight.
 * \see tft8_set_backlight
 */
#define TFT8_MIN_BACKLIGHT (0x00)
/*!
 * \brief Constant for setting maximum backlight.
 * \see tft8_set_backlight
 */
#define TFT8_MAX_BACKLIGHT (0xFF)

/*!
 * \brief Mapping controll pins.
 */
#define TFT8_MAP_CTRL_BITS(tft_cfg) \
  tft_cfg.tft_rst = TFT_RST; \
  tft_cfg.tft_cs  = TFT_CS;  \
  tft_cfg.tft_d_c = TFT_D_C; \
  tft_cfg.tft_wr  = TFT_WR;  \
  tft_cfg.tft_rd  = TFT_RD;  \

/*!
 * \brief Mapping configuration strucutre to 8 bit host interface defined with
 * board.
 */
#define TFT8_MAP_PINOUTS_8BIT(tft_cfg) \
  TFT8_MAP_CTRL_BITS(tft_cfg) \
  tft_cfg.data_channel_0 = TFT_8BIT_DATA_PORT_CH0; \
  tft_cfg.data_channel_0_mask = TFT_8BIT_DATA_PORT_CH0_MASK; \
  tft_cfg.host_interface = TFT8_HOST_INTERFACE_8BIT;

/*!
 * \brief Mapping configuration strucutre to 16 bit host interface defined with board.
 */
#define TFT8_MAP_PINOUTS_16BIT(tft_cfg) \
  TFT8_MAP_CTRL_BITS(tft_cfg) \
  tft_cfg.data_channel_0 = TFT_16BIT_DATA_PORT_CH0; \
  tft_cfg.data_channel_0_mask = TFT_16BIT_DATA_PORT_CH0_MASK; \
  tft_cfg.data_channel_1 = TFT_16BIT_DATA_PORT_CH1; \
  tft_cfg.data_channel_1_mask = TFT_16BIT_DATA_PORT_CH1_MASK; \
  tft_cfg.host_interface = TFT8_HOST_INTERFACE_16BIT;

/*!
 * \brief Host interface configuration enumeration.
 */
typedef enum
{
    TFT8_HOST_INTERFACE_8BIT = 0,
    TFT8_HOST_INTERFACE_16BIT,
    TFT8_HOST_INTERFACE_CUSTOM
} tft8_host_interface_t;

/*!
 * \brief TFT Board Capacitive definition structure.
 */
typedef struct tft8_board_s
{
    uint16_t display_width; /*!< Display width resolution in pixels. */
    uint16_t display_height; /*!< Display height resolution in pixels. */

    void (*reset_procedure)(void);
} tft8_board_t;

/// Definition constant for TFT BOARD 3 CAPACITIVE display board.
extern const tft8_board_t TFT_BOARD_3_CAPACITIVE;
/// Definition constant for TFT BOARD 4 CAPACITIVE display board.
extern const tft8_board_t TFT_BOARD_4_CAPACITIVE;
/// Definition constant for TFT BOARD 5 CAPACITIVE display board.
extern const tft8_board_t TFT_BOARD_5_CAPACITIVE;
/// Definition constant for TFT BOARD 7 CAPACITIVE display board.
extern const tft8_board_t TFT_BOARD_7_CAPACITIVE;
/// Definition constant for MIKROMEDIA 3 CAPACITIVE display board.
extern const tft8_board_t MIKROMEDIA_3_CAPACITIVE;


/*!
 * \brief TFT Board Capacitive library configuration structure.
 */
typedef struct
{
    const tft8_board_t *board; /*!< Board definition constant. */

    hal_pin_name_t tft_rst; /*!< RST pin name. */
    hal_pin_name_t tft_cs; /*!< CS pin name. */
    hal_pin_name_t tft_d_c; /*!< D/C pin name. */
    hal_pin_name_t tft_rd; /*!< RD pin name. */
    hal_pin_name_t tft_wr; /*!< WR pin name. */

    hal_port_name_t data_channel_0; /*!< Port name for data channel 0. */
    uint32_t data_channel_0_mask;  /*!< Port mask for data channel 0. */

    hal_port_name_t data_channel_1; /*!< Port name for data channel 1. */
    uint32_t data_channel_1_mask;  /*!< Port mask for data channel 1. */

    tft8_host_interface_t host_interface; /*!< Host interface configuration. */
} tft8_cfg_t;


#ifdef __cplusplus
extern "C"{
#endif

/*!
 * \brief Initializes TFT extension board module driver with given
 * configuration.
 * \param driver TFT driver object structure used to store driver context data.
 * \param cfg Configuration structure.
 * \return Returns TFT driver instance handle.
 */
void tft8_init(tft8_cfg_t *cfg, gl_driver_t *driver);

/*!
 * \brief Returns positive value if TFT8 board supports \p interface, otherwise
 * returns 0.
 *
 * \param interface Host interface.
 */
uint8_t tft8_is_supported_interface(tft8_host_interface_t interface);

/*!
 * \brief Returns displays width in pixels.
 */
uint16_t tft8_display_width();

/*!
 * \brief Returns displays height in pixels.
 */
uint16_t tft8_display_height();

/*!
 * \brief Sets display's backlight intenisty.
 *
 * \param intenisty Backlight intenisty.
 *
 * \see TFT8_MIN_BACKLIGHT, TFT8_MAX_BACKLIGHT
 */
void tft8_set_backlight(uint8_t intenisty);

// TODO Implement set gamma.
// TODO Implement display on/off.

/*! @} */ // tft8group
/*! @} */ // compgroup

#ifdef __cplusplus
}
#endif
#endif // TFT8_H
/*! @} */
