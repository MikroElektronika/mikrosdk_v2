/****************************************************************************
**
** Copyright (C) 2026 MikroElektronika d.o.o.
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
 * @file  lvgl_common.h
 * @brief Common LVGL TFT interface APIs for all SSD1963 displays.
 */

#ifdef __cplusplus
extern "C"
{
#endif

#ifndef _LVGL_COMMON_H_
#define _LVGL_COMMON_H_

#include "board.h"
#include "st7789_cmd.h"
#include "drv_digital_out.h"
#include "drv_digital_in.h"
#include "drv_spi_master.h"
#include "touch_controller.h"

#ifdef __GNUC__
#include <me_built_in.h>
#endif

#ifdef MikroCCoreVersion
#if MikroCCoreVersion >= 1
#include "delays.h"
#endif
#endif

#ifndef DISPLAY_SPI_MIKROBUS
#define DISPLAY_SPI_MIKROBUS MIKROBUS_1
#endif

/*!
 * \addtogroup compgroup Components
 * \brief Libraries for extension boards.
 * @{
 */

/*!
 * \addtogroup tftgroupCommon Common TFT Board routines.
 * \brief Common TFT Board routines.
 * @{
 */

/*!< Set display column to write data to. */
#define set_column() \
   uint16_t start_column = act_x1; \
   uint16_t end_column = act_x2;

/*!< Set display page to write data to. */
#define set_page() \
   uint16_t start_page = act_y1; \
   uint16_t end_page = act_y2;

/*!< Set SPI dummy write data. */
#define SPI_DUMMY          0x00

/*!< Set CS pin high. */
#define CS_HIGH            ( digital_out_high( &pin_cs ) )
/*!< Set CS pin low. */
#define CS_LOW             ( digital_out_low( &pin_cs ) )
/*!< Set RST pin high. */
#define RST_HIGH           ( digital_out_high( &pin_rst ) )
/*!< Set WR pin low. */
#define RST_LOW            ( digital_out_low( &pin_rst ) )
/*!< Set DC pin high. RS on mikroBUS*/
#define DC_HIGH            ( digital_out_high( &pin_dc ) )
/*!< Set DC pin low. RS on mikroBUS*/
#define DC_LOW             ( digital_out_low( &pin_dc ) )
/*!< Deselect display. In case of SSD1963 set CS pin high. */
#define display_deselect() CS_HIGH
/*!< Check if touch was detected. */
#define check_touchpad() return (tp.touch.n_touches > 0)

/*!< SPI handler. */
static spi_master_t disp_spi;
/*!< CS pin handle. */
static digital_out_t pin_cs;
/*!< RST pin handle. */
static digital_out_t pin_rst;
/*!< DC pin handle. */
static digital_out_t pin_dc;
/*!< BCK pin handle. */
static digital_out_t pin_bck;

/*!< Display driver handle. */
static gl_driver_t display_driver;

/*!< Touch panel handle. */
static tp_drv_t tp_interface;
static tp_t tp;

/**
 * @brief Writes @ref command to TFT board.
 * @param[in] command Command to be written.
 * @return Nothing.
 */
static inline void write_command( uint8_t command )
{
   CS_LOW;
   DC_LOW;
   spi_master_write( &disp_spi, &command, 1 );
   CS_HIGH;
}

/**
 * @brief Writes @ref param to TFT board.
 * @param[in] param Parameter to be written.
 * @return Nothing.
 */
static inline void write_param( uint8_t param )
{
   CS_LOW;
   DC_HIGH;
   spi_master_write( &disp_spi, &param, 1 );
   CS_HIGH;
}

/**
 * @brief Writes @ref length number of data from
 *        @ref array to TFT board.
 * @param[in] array Pointer to data array.
 * @param[in] length Number of bytes to write.
 * @return Nothing.
 */
static inline void write_array_data( uint16_t *array, uint16_t length )
{
   /* LVGL v9 gives pixels as a byte pointer. For SPI treat it as uint8_t */
   uint8_t *data = (uint8_t *)array;

   /*Write px data*/
   CS_LOW;
   spi_master_write( &disp_spi, data, length * 2 );
   CS_HIGH;
}

/**
 * @brief Initializes control and data pins as well as
 *        display to default state.
 * @return Nothing.
 */
static inline void display_configure( void )
{
   spi_master_config_t spi_cfg;

   // Initialize communication pins.
   spi_master_configure_default( &spi_cfg );

   spi_cfg.sck = MIKROBUS( DISPLAY_SPI_MIKROBUS, MIKROBUS_SCK );
   spi_cfg.miso = MIKROBUS( DISPLAY_SPI_MIKROBUS, MIKROBUS_MISO );
   spi_cfg.mosi = MIKROBUS( DISPLAY_SPI_MIKROBUS, MIKROBUS_MOSI );

   spi_master_open( &disp_spi, &spi_cfg );
   spi_master_set_default_write_data( &disp_spi, SPI_DUMMY );
   spi_master_set_mode( &disp_spi, SPI_MASTER_MODE_0 );
   spi_master_set_speed( &disp_spi, 5000000 );

   // Initialize control pins.
   digital_out_init( &pin_cs, MIKROBUS( DISPLAY_SPI_MIKROBUS, MIKROBUS_CS ) );
   digital_out_init( &pin_rst, MIKROBUS( DISPLAY_SPI_MIKROBUS, MIKROBUS_RST ) );
   digital_out_init( &pin_dc, MIKROBUS( DISPLAY_SPI_MIKROBUS, MIKROBUS_INT ) );
   digital_out_init( &pin_bck, MIKROBUS( DISPLAY_SPI_MIKROBUS, MIKROBUS_AN ) );
   digital_out_high( &pin_bck );
   CS_HIGH;

   // Initialize touch controller.
   touch_controller_init(&display_driver, TFT_MAX_BACKLIGHT);
}

/**
 * @brief Prepares display for data about to be sent.
 * @param[in] start_column Column start offset.
 * @param[in] end_column Column end offset.
 * @param[in] start_page Page start offset.
 * @param[in] end_page Page end offset.
 * @return Nothing.
 */
static inline void frame_start( uint32_t start_column, uint32_t end_column,
                                uint32_t start_page, uint32_t end_page )
{
   write_command( ST7789_CMD_CASET );
   write_param( Hi( start_column ) );
   write_param( Lo( start_column ) );
   write_param( Hi( end_column ) );
   write_param( Lo( end_column ) );

   write_command( ST7789_CMD_RASET );
   write_param( Hi( start_page ) );
   write_param( Lo( start_page ) );
   write_param( Hi( end_page ) );
   write_param( Lo( end_page ) );

   write_command( ST7789_CMD_RAMWR );

   CS_LOW;
   DC_HIGH;
}

/**
 * @brief Returns last touch coordinates.
 * @param[in] x X axis value.
 * @param[in] y Y axis value.
 * @return Nothing.
 */
static inline void get_touch_coordinates( int16_t *x, int16_t *y )
{
   tp_touch_item_t touch_item;

   tp_press_coordinates( &tp, &touch_item );

   ( *x ) = touch_item.point[0].coord_x;
   ( *y ) = touch_item.point[0].coord_y;
}

/*! @} */ // tftgroupCommon
/*! @} */ // compgroup

#ifdef __cplusplus
}
#endif

#endif    // _LVGL_COMMON_H_
// ------------------------------------------------------------------------- END
