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
 * @file  lvgl_common.h
 * @brief Common LVGL TFT interface APIs for all SSD1963 displays.
 */

#ifdef __cplusplus
extern "C"{
#endif

#ifndef _LVGL_COMMON_H_
#define _LVGL_COMMON_H_

#include "board.h"
#include "drv_port.h"
#include "ssd1963_cmd.h"
#include "drv_digital_out.h"
#include "touch_controller.h"

#ifndef LCD_TFT_CH0_8BIT_MASK
#define LCD_TFT_CH0_8BIT_MASK LCD_TFT_8BIT_CH0_MASK
#endif

#ifdef __GNUC__
#include <me_built_in.h>
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
#define set_column() uint16_t start_column = (_TFT_WIDTH_ - 1) - (act_x1 + act_w - 1); \
                     uint16_t end_column = (_TFT_WIDTH_ - 1) - act_x1;

/*!< Set display page to write data to. */
#define set_page() uint16_t start_page = (_TFT_HEIGHT_ - 1) - act_y2; \
                   uint16_t end_page = (_TFT_HEIGHT_ - 1) - act_y1;

/*!< Set CS pin high. */
#define CS_HIGH (digital_out_high(&pin_cs))
/*!< Set CS pin low. */
#define CS_LOW  (digital_out_low(&pin_cs))
/*!< Set WR pin high. */
#define WR_HIGH (digital_out_high(&pin_wr))
/*!< Set WR pin low. */
#define WR_LOW  (digital_out_low(&pin_wr))
/*!< Set DC pin high. */
#define DC_HIGH (digital_out_high(&pin_dc))
/*!< Set DC pin low. */
#define DC_LOW  (digital_out_low(&pin_dc))
/*!< Deselect display. In case of SSD1963 set CS pin high. */
#define display_deselect() CS_HIGH

/*!< Check if touch was detected. */
#define check_touchpad() return (tp.touch.n_touches > 0)

/*!< CS pin handle. */
static digital_out_t pin_cs;
/*!< WR pin handle. */
static digital_out_t pin_wr;
/*!< DC pin handle. */
static digital_out_t pin_dc;

/*!< Data port handle. */
static port_t port_high;
static port_t port_low;

/*!< Display driver handle. */
static gl_driver_t display_driver;

/*!< Touch panel handle. */
static tp_drv_t tp_interface;
static tp_t tp;

/*!< Initial value for 16-bit port check. */
static volatile bool port_16bit_single = false;
static volatile bool port_16bit_dual = false;

/*!< Initial value for data shifting. Some MCUs
     have data pins routed on upper 8 pins.
     E.G. data pins 0-7 are on PORTD pins 8-15,
     so we need to shift the data. */
static volatile uint8_t shift_data_port_low = 0;
static volatile uint8_t shift_data_port_high = 0;

/**
 * @brief Writes @ref command to TFT board.
 * @param[in] command Command to be written.
 * @return Nothing.
 */
static inline void write_command(uint8_t command)
{
    CS_LOW;
    DC_LOW;
    port_write(&port_low, command << shift_data_port_low);
    WR_LOW;
    WR_HIGH;
    CS_HIGH;
}

/**
 * @brief Writes @ref param to TFT board.
 * @param[in] param Parameter to be written.
 * @return Nothing.
 */
static inline void write_param(uint8_t param)
{
    CS_LOW;
    DC_HIGH;
    port_write(&port_low, param << shift_data_port_low);
    WR_LOW;
    WR_HIGH;
    CS_HIGH;
}

/**
 * @brief Routine to write data on 8-bit TFT ports.
 * @details Most efficient way to spread all data across 8-bit
 *          data port.
 * @param[in] fill_data 16-bit Data to spread across 8 pins.
 * @return Nothing.
 */
static inline void data_8bit_write(uint16_t fill_data)
{
    volatile uint32_t value1 = ((fill_data & 0xF800) >> 8) & 0x00FF;
    volatile uint32_t value2 = ((fill_data & 0x07E0 ) >> 3) & 0x00FF;
    volatile uint32_t value3 = ((fill_data & 0x001F ) << 3) & 0x00FF;

    port_write(&port_low, (uint16_t)(value1 << shift_data_port_low));
    WR_LOW;
    WR_HIGH;
    port_write(&port_low, (uint16_t)(value2 << shift_data_port_low));
    WR_LOW;
    WR_HIGH;
    port_write(&port_low, (uint16_t)(value3 << shift_data_port_low));
}

/**
 * @brief Writes @ref length number of data from
 *        @ref array to TFT board.
 * @param[in] array Pointer to data array.
 * @param[in] length Number of bytes to write.
 * @return Nothing.
 */
static inline void write_array_data(uint16_t *array, uint16_t length)
{
    uint32_t i;

    for (i = 0; i < length; i++)
    {
        if (port_16bit_single) {
            port_write(&port_low, *array);
        } else if (port_16bit_dual) {
            port_write(&port_low, ((uint16_t)(*array & 0xFF)) << shift_data_port_low);
            port_write(&port_high, ((uint16_t)(*array & 0xFF00) >> 8) << shift_data_port_high);
        } else {
            data_8bit_write(*array);
        }

        WR_LOW;
        WR_HIGH;

        array++;
    }
}

/**
 * @brief Initializes control and data pins as well as
 *        display to default state.
 * @return Nothing.
 */
static inline void display_configure(void)
{
    // Reset values to false.
    port_16bit_single = false;
    port_16bit_dual = false;
    shift_data_port_low = 0;
    shift_data_port_high = 0;

    // Initialize control pins.
    digital_out_init(&pin_cs, TFT_CS);
    digital_out_init(&pin_dc, TFT_D_C);
    digital_out_init(&pin_wr, TFT_WR);

    // Initialize data port.
    if (HAL_PORT_NC != LCD_TFT_16BIT_CH1) {
        port_16bit_dual = true;
        port_init(&port_low, TFT_16BIT_DATA_PORT_CH0, LCD_TFT_16BIT_CH0_MASK, PIN_DIRECTION_DIGITAL_OUTPUT);
        port_init(&port_high, TFT_16BIT_DATA_PORT_CH1, LCD_TFT_16BIT_CH1_MASK, PIN_DIRECTION_DIGITAL_OUTPUT);
        if (0xFF00 == LCD_TFT_16BIT_CH0) {
            shift_data_port_low = 8;
        }
        if (0xFF00 == LCD_TFT_16BIT_CH1) {
            shift_data_port_high = 8;
        }
    } else if (HAL_PORT_NC != LCD_TFT_16BIT_CH0) {
        port_init(&port_low, LCD_TFT_16BIT_CH0, LCD_TFT_16BIT_CH0_MASK, PIN_DIRECTION_DIGITAL_OUTPUT);
        if (0xFFFF == LCD_TFT_16BIT_CH0_MASK) {
            port_16bit_single = true;
        }
        if (0xFF00 == LCD_TFT_CH0_8BIT_MASK) {
            shift_data_port_low = 8;
        }
    } else if (HAL_PORT_NC != LCD_TFT_8BIT_CH0) {
        port_init(&port_low, LCD_TFT_8BIT_CH0, LCD_TFT_CH0_8BIT_MASK, PIN_DIRECTION_DIGITAL_OUTPUT);
        if (0xFFFF == LCD_TFT_CH0_8BIT_MASK) {
            port_16bit_single = true;
        }
        if (0xFF00 == LCD_TFT_CH0_8BIT_MASK) {
            shift_data_port_low = 8;
        }
    }

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
static inline void frame_start(uint32_t start_column, uint32_t end_column,
                               uint32_t start_page, uint32_t end_page)
{
    write_command(SSD1963_CMD_SET_COLUMN_ADDRESS);
    write_param(Hi(start_column));
    write_param(Lo(start_column));
    write_param(Hi(end_column));
    write_param(Lo(end_column));

    write_command(SSD1963_CMD_SET_PAGE_ADDRESS);
    write_param(Hi(start_page));
    write_param(Lo(start_page));
    write_param(Hi(end_page));
    write_param(Lo(end_page));

    write_command(SSD1963_CMD_WRITE_MEMORY_START);

    CS_LOW;
    DC_HIGH;
}

/**
 * @brief Returns last touch coordinates.
 * @param[in] x X axis value.
 * @param[in] y Y axis value.
 * @return Nothing.
 */
static inline void get_touch_coordinates(int16_t *x, int16_t *y)
{
    tp_touch_item_t touch_item;

    tp_press_coordinates(&tp, &touch_item);

    (*x) = touch_item.point[0].coord_x;
    (*y) = touch_item.point[0].coord_y;
}

/*! @} */ // tftgroupCommon
/*! @} */ // compgroup

#ifdef __cplusplus
}
#endif

#endif // _LVGL_COMMON_H_
// ------------------------------------------------------------------------- END
