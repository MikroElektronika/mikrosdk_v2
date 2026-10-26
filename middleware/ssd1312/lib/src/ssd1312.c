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
 * @file  ssd1312.c
 * @brief SSD1312 controller source file.
 */

#include "ssd1312.h"
#include "ssd1312_cmd.h"
#include "gl.h"
#include "drv_digital_out.h"
#include "drv_i2c_master.h"
#include "delays.h"

/**
 * @remark No context for display controller driver, because in most cases only
 * one display on board. Performance concerns.
 */

#define SSD1312_I2C_CHUNK 16

static digital_out_t pin_rst;
static i2c_master_t i2c_master;

static uint16_t display_width;
static uint16_t display_height;

static uint16_t native_width;
static uint16_t native_height;

static uint8_t rotation_mode;
static uint8_t column_offset;

static gl_driver_t *current_gl_driver = NULL;

/** One bit per pixel, one byte holds 8 vertical pixels of one page. */
static uint8_t frame_buffer[SSD1312_MAX_WIDTH * SSD1312_MAX_HEIGHT / 8];

/** Control byte followed by one page of display data. */
static uint8_t tx_buffer[SSD1312_I2C_CHUNK + 1];

/** Window and cursor used while the Graphics Library streams pixels. */
static uint16_t frame_x1;
static uint16_t frame_y1;
static uint16_t frame_x2;
static uint16_t frame_y2;
static uint16_t frame_x;
static uint16_t frame_y;

uint16_t ssd1312_get_display_width()
{
    return display_width;
}

uint16_t ssd1312_get_display_height()
{
    return display_height;
}

void ssd1312_write_command(uint8_t command)
{
    uint8_t buffer[2] = { SSD1312_CONTROL_COMMAND, command };

    i2c_master_write(&i2c_master, buffer, 2);
}

void ssd1312_write_param(uint8_t param)
{
    uint8_t buffer[2] = { SSD1312_CONTROL_COMMAND, param };

    i2c_master_write(&i2c_master, buffer, 2);
}

static void send_init_sequence(const uint8_t *seq)
{
    uint8_t count;

    while (*seq)
    {
        ssd1312_write_command(*seq++);
        count = *seq++;
        while (count--)
        {
            ssd1312_write_param(*seq++);
        }
    }
}

void ssd1312_set_contrast(uint8_t contrast)
{
    ssd1312_write_command(SSD1312_CMD_CONTRAST);
    ssd1312_write_param(contrast);
}

void ssd1312_display_power(uint8_t state)
{
    ssd1312_write_command(state ? SSD1312_CMD_DISPLAY_ON : SSD1312_CMD_DISPLAY_OFF);
}

static void map_xy(uint16_t x, uint16_t y, uint16_t *nx, uint16_t *ny)
{
    switch (rotation_mode)
    {
        case 1:
            *nx = native_width - 1 - y;
            *ny = x;
            break;
        case 2:
            *nx = native_width - 1 - x;
            *ny = native_height - 1 - y;
            break;
        case 3:
            *nx = y;
            *ny = native_height - 1 - x;
            break;
        default:
            *nx = x;
            *ny = y;
            break;
    }
    // The panel is mirrored horizontally, flip the column.
    *nx = native_width - 1 - *nx;
}

void ssd1312_rotate(uint8_t rotation)
{
    rotation_mode = rotation & 3;

    if (rotation_mode & 1)
    {
        display_width = native_height;
        display_height = native_width;
    }
    else
    {
        display_width = native_width;
        display_height = native_height;
    }

    if (current_gl_driver)
    {
        current_gl_driver->display_width = display_width;
        current_gl_driver->display_height = display_height;
    }
}

void ssd1312_draw_pixel(uint16_t x, uint16_t y, uint8_t on)
{
    uint16_t nx;
    uint16_t ny;
    uint16_t index;
    uint8_t mask;

    if (x >= display_width || y >= display_height)
    {
        return;
    }

    map_xy(x, y, &nx, &ny);
    index = (ny / 8) * SSD1312_MAX_WIDTH + nx;
    mask = 1 << (ny % 8);

    if (on)
    {
        frame_buffer[index] |= mask;
    }
    else
    {
        frame_buffer[index] &= ~mask;
    }
}

void ssd1312_update(uint16_t x1, uint16_t y1, uint16_t x2, uint16_t y2)
{
    uint16_t ax;
    uint16_t ay;
    uint16_t bx;
    uint16_t by;
    uint16_t col_start;
    uint16_t col_end;
    uint16_t page_start;
    uint16_t page_end;
    uint16_t page;
    uint16_t col;
    uint16_t length;
    uint16_t i;
    uint16_t total;
    uint16_t sent;

    if (x1 >= display_width || y1 >= display_height)
    {
        return;
    }

    if (x2 >= display_width)
    {
        x2 = display_width - 1;
    }
    if (y2 >= display_height)
    {
        y2 = display_height - 1;
    }

    map_xy(x1, y1, &ax, &ay);
    map_xy(x2, y2, &bx, &by);

    col_start = (ax < bx) ? ax : bx;
    col_end = (ax < bx) ? bx : ax;
    page_start = ((ay < by) ? ay : by) / 8;
    page_end = ((ay < by) ? by : ay) / 8;

    for (page = page_start; page <= page_end; page++)
    {
        col = col_start + column_offset;
        ssd1312_write_command(SSD1312_CMD_PAGE_ADDR | page);
        ssd1312_write_command(SSD1312_CMD_COL_LOW | (col & 0x0F));
        ssd1312_write_command(SSD1312_CMD_COL_HIGH | (col >> 4));

        total = col_end - col_start + 1;
        sent = 0;

        while (sent < total)
        {
            length = total - sent;
            if (length > SSD1312_I2C_CHUNK)
            {
                length = SSD1312_I2C_CHUNK;
            }

            tx_buffer[0] = SSD1312_CONTROL_DATA;
            for (i = 0; i < length; i++)
            {
                tx_buffer[i + 1] = frame_buffer[page * SSD1312_MAX_WIDTH + col_start + sent + i];
            }
            i2c_master_write(&i2c_master,tx_buffer, length + 1);
            sent += length;
        }
    }
}

static uint8_t color_to_mono(gl_color_t color)
{
    uint16_t red = (color >> 11) & 0x1F;
    uint16_t green = (color >> 5) & 0x3F;
    uint16_t blue = color & 0x1F;

    return ((red * 2 + green + blue * 2) > 93) ? 1 : 0;
}

void _ssd1312_begin_frame(gl_rectangle_t *rect)
{
    frame_x1 = rect->top_left.x;
    frame_y1 = rect->top_left.y;
    frame_x2 = frame_x1 + rect->width - 1;
    frame_y2 = frame_y1 + rect->height - 1;

    frame_x = frame_x1;
    frame_y = frame_y1;
}

void _ssd1312_frame_data(gl_color_t color)
{
    ssd1312_draw_pixel(frame_x, frame_y, color_to_mono(color));

    if (frame_x >= frame_x2)
    {
        frame_x = frame_x1;
        frame_y++;
    }
    else
    {
        frame_x++;
    }
}

void _ssd1312_end_frame()
{
    ssd1312_update(frame_x1, frame_y1, frame_x2, frame_y2);
}

void _ssd1312_fill(gl_rectangle_t *rect, gl_color_t color)
{
    uint16_t x_end = rect->top_left.x + rect->width - 1;
    uint16_t y_end = rect->top_left.y + rect->height - 1;
    uint8_t on = color_to_mono(color);
    uint16_t x;
    uint16_t y;

    if (!rect->width || !rect->height)
    {
        return;
    }

    for (y = rect->top_left.y; y <= y_end; y++)
    {
        for (x = rect->top_left.x; x <= x_end; x++)
        {
            ssd1312_draw_pixel(x, y, on);
        }
    }

    ssd1312_update(rect->top_left.x, rect->top_left.y, x_end, y_end);
}

void ssd1312_init(ssd1312_cfg_t *cfg, gl_driver_t * __generic_ptr driver)
{
    i2c_master_config_t i2c_cfg;
    uint16_t i;

    if (cfg->rst != HAL_PIN_NC)
    {
        digital_out_init(&pin_rst, cfg->rst);
        digital_out_low(&pin_rst);
    }

    i2c_master_configure_default(&i2c_cfg);
    i2c_cfg.scl = cfg->scl;
    i2c_cfg.sda = cfg->sda;

    if (I2C_MASTER_ERROR == i2c_master_open(&i2c_master, &i2c_cfg))
    {
        return;
    }

    i2c_master_set_slave_address(&i2c_master, cfg->address);
    i2c_master_set_speed(&i2c_master, cfg->speed);

    driver->fill_f = _ssd1312_fill;
    driver->begin_frame_f = _ssd1312_begin_frame;
    driver->end_frame_f = _ssd1312_end_frame;
    driver->frame_data_f = _ssd1312_frame_data;

    current_gl_driver = driver;

    native_width = (cfg->width > SSD1312_MAX_WIDTH) ? SSD1312_MAX_WIDTH : cfg->width;
    native_height = (cfg->height > SSD1312_MAX_HEIGHT) ? SSD1312_MAX_HEIGHT : cfg->height;
    display_width = native_width;
    driver->display_width = display_width;
    display_height = native_height;
    driver->display_height = display_height;

    column_offset = cfg->col_offset;
    rotation_mode = 0;

    for (i = 0; i < sizeof(frame_buffer); i++)
    {
        frame_buffer[i] = 0;
    }

    Delay_ms(SSD1312_DELAY_RESET_MS);
    if (cfg->rst != HAL_PIN_NC)
    {
        digital_out_high(&pin_rst);
        Delay_ms(SSD1312_DELAY_RESET_MS);
    }

    ssd1312_write_command(SSD1312_CMD_DISPLAY_OFF);
    ssd1312_write_command(SSD1312_CMD_MEM_MODE);
    ssd1312_write_param(SSD1312_MEM_MODE_PAGE);

    ssd1312_write_command(SSD1312_CMD_CLOCK_DIV);
    ssd1312_write_param(0x80);

    ssd1312_write_command(SSD1312_CMD_MULTIPLEX);
    ssd1312_write_param(0x3F);

    ssd1312_write_command(SSD1312_CMD_DISPLAY_OFFSET);
    ssd1312_write_param(cfg->display_offset);

    ssd1312_write_command(SSD1312_CMD_START_LINE);

    ssd1312_write_command(SSD1312_CMD_CHARGE_PUMP);
    ssd1312_write_param(SSD1312_CHARGE_PUMP_OFF);

    ssd1312_write_command(SSD1312_CMD_SEG_PINS);
    ssd1312_write_param(SSD1312_SEG_PINS_ALTERNATIVE);

    ssd1312_write_command(SSD1312_CMD_SEG_REMAP_OFF);
    ssd1312_write_command(SSD1312_CMD_COM_SCAN_REVERSE);

    ssd1312_write_command(SSD1312_CMD_PRECHARGE);
    ssd1312_write_param(0x22);

    ssd1312_write_command(SSD1312_CMD_VCOM_DESELECT);
    ssd1312_write_param(0x20);

    ssd1312_set_contrast(cfg->contrast);

    ssd1312_write_command(SSD1312_CMD_ENTIRE_OFF);
    ssd1312_write_command(cfg->invert ? SSD1312_CMD_REVERSE : SSD1312_CMD_NORMAL);

    if (cfg->init_seq)
    {
        send_init_sequence(cfg->init_seq);
    }

    ssd1312_update(0, 0, display_width - 1, display_height - 1);

    ssd1312_display_power(1);
    Delay_ms(SSD1312_DELAY_DISPLAY_ON_MS);
}
