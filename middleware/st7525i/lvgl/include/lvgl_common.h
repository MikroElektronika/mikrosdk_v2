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
 * @file  lvgl_common.h
 * @brief Common LVGL interface APIs for all ST7525I displays.
 */

#ifdef __cplusplus
extern "C"{
#endif

#ifndef _LVGL_COMMON_H_
#define _LVGL_COMMON_H_

#include <stdint.h>
#include <stdbool.h>
#include "board.h"
#include "gl.h"
#include "st7525i.h"

/*!
 * @addtogroup middlewaregroup Middleware
 * @{
 */

/*!
 * @addtogroup st7525i_lvgl_common Common LVGL routines for ST7525I displays.
 * @brief Common LVGL routines for ST7525I displays.
 * @details The project must define the display pins and the display size
 *          before including this header (see the checks below).
 * @{
 */
// The project must define these before including this header.
// SCK, MISO and MOSI must belong to the same SPI module
#if !defined(TFT_RST_PIN) || !defined(TFT_CS_PIN) || !defined(TFT_DC_PIN) || \
    !defined(TFT_SCK_PIN) || !defined(TFT_MISO_PIN) || !defined(TFT_MOSI_PIN)
#error "Define the TFT pin macros (RST, CS, DC, SCK, MISO, MOSI) before including lvgl_common.h."
#endif

// Display size. Everything in LVGL scales from these two values.
#if !defined(_TFT_WIDTH_) || !defined(_TFT_HEIGHT_)
#error "Define _TFT_WIDTH_ and _TFT_HEIGHT_ before including lvgl_common.h."
#endif

// SPI clock speed in Hz. Can be overridden by the project.
#ifndef TFT_SPI_SPEED
#define TFT_SPI_SPEED 4000000
#endif

// Set to 1 so that white is light and black is dark (needed for this LCD). Can be overridden by the project.
#ifndef TFT_INVERT_COLORS
#define TFT_INVERT_COLORS 1
#endif

// Optional extra init commands (see st7525i_cfg_t). Can be overridden by the project.
#ifndef TFT_INIT_SEQ
#define TFT_INIT_SEQ NULL
#endif

// Display contrast (0x00 - 0xFF). Can be overridden by the project.
#ifndef TFT_CONTRAST
#define TFT_CONTRAST 0x80
#endif

/*!< Set display column to write data to. */
#define set_column() uint16_t start_column = act_x1; \
                     uint16_t end_column = act_x2;

/*!< Set display page to write data to. */
#define set_page() uint16_t start_page = act_y1; \
                   uint16_t end_page = act_y2;

/*!< Deselect display. In case of ST7525I send the changed area to the display (end of frame). */
#define display_deselect() (display_driver.end_frame_f())

/*!< ST7525I displays have no touch panel, so touch is never detected. */
#define check_touchpad() return false

/*!< Display driver handle. */
static gl_driver_t display_driver;

/*!< Display configuration. */
static st7525i_cfg_t display_cfg;

/**
 * @brief Initializes control pins, SPI and display to default state.
 * @return Nothing.
 */
static inline void display_configure(void)
{
    display_cfg.rst      = TFT_RST_PIN;
    display_cfg.cs       = TFT_CS_PIN;
    display_cfg.d_c      = TFT_DC_PIN;
    display_cfg.sck      = TFT_SCK_PIN;
    display_cfg.miso     = TFT_MISO_PIN;
    display_cfg.mosi     = TFT_MOSI_PIN;
    display_cfg.speed    = TFT_SPI_SPEED;
    display_cfg.width    = _TFT_WIDTH_;
    display_cfg.height   = _TFT_HEIGHT_;
    display_cfg.contrast = TFT_CONTRAST;
    display_cfg.invert   = TFT_INVERT_COLORS;
    display_cfg.init_seq = TFT_INIT_SEQ;

    st7525i_init(&display_cfg, &display_driver);
}

/**
 * @brief Prepares display for data about to be sent.
 * @param[in] start_column Column start offset.
 * @param[in] end_column Column end offset.
 * @param[in] start_page Page start offset.
 * @param[in] end_page Page end offset.
 * @return Nothing.
 */
static inline void frame_start(uint32_t start_column, uint32_t end_column,
                               uint32_t start_page, uint32_t end_page)
{
    gl_rectangle_t area;

    area.top_left.x = start_column;
    area.top_left.y = start_page;
    area.width      = end_column - start_column + 1;
    area.height     = end_page - start_page + 1;

    display_driver.begin_frame_f(&area);
}

/**
 * @brief Writes @ref length number of pixels from
 *        @ref array to the display.
 * @details Every pixel is converted to black or white by the driver (see st7525i.c).
 * @param[in] array Pixels in RGB565 format.
 * @param[in] length Number of pixels (not bytes).
 * @return Nothing.
 */
static inline void write_array_data(const uint16_t *array, uint32_t length)
{
    for (uint32_t i = 0; i < length; i++)
    {
        display_driver.frame_data_f(array[i]);
    }
}

/**
 * @brief Gets the touch coordinates.
 * @details ST7525I displays have no touch panel, so the coordinates are always zero.
 * @param[out] x Touch X coordinate.
 * @param[out] y Touch Y coordinate.
 * @return Nothing.
 */
static inline void get_touch_coordinates(int16_t *x, int16_t *y)
{
    (*x) = 0;
    (*y) = 0;
}

/*! @} */ // st7525i_lvgl_common
/*! @} */ // middlewaregroup

#ifdef __cplusplus
}
#endif

#endif // _LVGL_COMMON_H_
