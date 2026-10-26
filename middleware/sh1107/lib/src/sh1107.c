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
 * @file  sh1107.c
 * @brief SH1107 controller source file.
 */

#include "sh1107.h"
#include "sh1107_cmd.h"
#include "gl.h"
#include "drv_digital_out.h"
#include "drv_spi_master.h"
#include "delays.h"

/**
 * @remark No context for display controller driver, because in most cases only
 * one display on board. Performance concerns.
 */
static digital_out_t pin_rst;
static digital_out_t pin_cs;
static digital_out_t pin_dc;
static spi_master_t spi_master;

static uint16_t display_width;
static uint16_t display_height;

static uint16_t native_width;
static uint16_t native_height;

static uint8_t rotation_mode;
static uint8_t column_offset;

static gl_driver_t *current_gl_driver = NULL;

/** One bit per pixel, one byte holds 8 vertical pixels of one page. */
static uint8_t frame_buffer[SH1107_MAX_WIDTH * SH1107_MAX_HEIGHT / 8];

/** Window and cursor used while the Graphics Library streams pixels. */
static uint16_t frame_x1;
static uint16_t frame_y1;
static uint16_t frame_x2;
static uint16_t frame_y2;
static uint16_t frame_x;
static uint16_t frame_y;

#define DATA_SELECT() digital_out_high(&pin_dc);
#define COMMAND_SELECT() digital_out_low(&pin_dc)
#define CS_ACTIVE() digital_out_low(&pin_cs)
#define CS_DEACTIVE() digital_out_high(&pin_cs)

static void spi_send(uint8_t *data, uint32_t length)
{
    spi_master_write(&spi_master, data, length);
}

uint16_t sh1107_get_display_width()
{
    return display_width;
}

uint16_t sh1107_get_display_height()
{
    return display_height;
}

void sh1107_write_command(uint8_t command)
{
    COMMAND_SELECT();
    CS_ACTIVE();
    spi_send(&command, 1);
    CS_DEACTIVE();
}

void sh1107_write_param(uint8_t param)
{
    COMMAND_SELECT();
    CS_ACTIVE();
    spi_send(&param, 1);
    CS_DEACTIVE();
}

static void send_init_sequence(const uint8_t *seq)
{
    uint8_t count;

    while (*seq)
    {
        sh1107_write_command(*seq++);
        count = *seq++;
        while (count--)
        {
            sh1107_write_param(*seq++);
        }
    }
}

void sh1107_set_contrast(uint8_t contrast)
{
    sh1107_write_command(SH1107_CMD_CONTRAST);
    sh1107_write_param(contrast);
}

void sh1107_display_power(uint8_t state)
{
    sh1107_write_command(state ? SH1107_CMD_DISPLAY_ON : SH1107_CMD_DISPLAY_OFF);
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
}

void sh1107_rotate(uint8_t rotation)
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

void sh1107_draw_pixel(uint16_t x, uint16_t y, uint8_t on)
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
    index = (ny / 8) * SH1107_MAX_WIDTH + nx;
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

void sh1107_update(uint16_t x1, uint16_t y1, uint16_t x2, uint16_t y2)
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
        sh1107_write_command(SH1107_CMD_PAGE_ADDR | page);
        sh1107_write_command(SH1107_CMD_COL_LOW | (col & 0x0F));
        sh1107_write_command(SH1107_CMD_COL_HIGH | (col >> 4));

        DATA_SELECT();
        CS_ACTIVE();
        spi_send(&frame_buffer[page * SH1107_MAX_WIDTH + col_start], col_end - col_start + 1);
        CS_DEACTIVE();
    }
}

static uint8_t color_to_mono(gl_color_t color)
{
    uint16_t red = (color >> 11) & 0x1F;
    uint16_t green = (color >> 5) & 0x3F;
    uint16_t blue = color & 0x1F;

    return ((red * 2 + green + blue * 2) > 93) ? 1 : 0;
}

void _sh1107_begin_frame(gl_rectangle_t *rect)
{
    frame_x1 = rect->top_left.x;
    frame_y1 = rect->top_left.y;
    frame_x2 = frame_x1 + rect->width - 1;
    frame_y2 = frame_y1 + rect->height - 1;

    frame_x = frame_x1;
    frame_y = frame_y1;
}

void _sh1107_frame_data(gl_color_t color)
{
    sh1107_draw_pixel(frame_x, frame_y, color_to_mono(color));

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

void _sh1107_end_frame()
{
    sh1107_update(frame_x1, frame_y1, frame_x2, frame_y2);
}

void _sh1107_fill(gl_rectangle_t *rect, gl_color_t color)
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
            sh1107_draw_pixel(x, y, on);
        }
    }

    sh1107_update(rect->top_left.x, rect->top_left.y, x_end, y_end);
}

void sh1107_init(sh1107_cfg_t *cfg, gl_driver_t * __generic_ptr driver)
{
    spi_master_config_t spi_cfg;
    uint16_t i;

    digital_out_init(&pin_cs, cfg->cs);
    digital_out_high(&pin_cs);

    digital_out_init(&pin_dc, cfg->d_c);
    digital_out_init(&pin_rst, cfg->rst);

    digital_out_high(&pin_dc);
    digital_out_low(&pin_rst);

    spi_master_configure_default(&spi_cfg);
    spi_cfg.sck = cfg->sck;
    spi_cfg.miso = cfg->miso;
    spi_cfg.mosi = cfg->mosi;
    spi_cfg.speed = cfg->speed;

    if (SPI_MASTER_ERROR == spi_master_open(&spi_master, &spi_cfg))
    {
        return;
    }

    spi_master_set_speed(&spi_master, cfg->speed);

    driver->fill_f = _sh1107_fill;
    driver->begin_frame_f = _sh1107_begin_frame;
    driver->end_frame_f = _sh1107_end_frame;
    driver->frame_data_f = _sh1107_frame_data;

    current_gl_driver = driver;

    native_width = (cfg->width > SH1107_MAX_WIDTH) ? SH1107_MAX_WIDTH : cfg->width;
    native_height = (cfg->height > SH1107_MAX_HEIGHT) ? SH1107_MAX_HEIGHT : cfg->height;
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

    Delay_ms(SH1107_DELAY_RESET_MS);
    digital_out_high(&pin_rst);
    Delay_ms(SH1107_DELAY_RESET_MS);

    sh1107_write_command(SH1107_CMD_DISPLAY_OFF);
    sh1107_write_command(SH1107_CMD_MEM_MODE_PAGE);

    sh1107_write_command(SH1107_CMD_CLOCK_DIV);
    sh1107_write_param(0x80);

    sh1107_write_command(SH1107_CMD_MULTIPLEX);
    sh1107_write_param(native_height - 1);

    sh1107_write_command(SH1107_CMD_DISPLAY_OFFSET);
    sh1107_write_param(cfg->display_offset);

    sh1107_write_command(SH1107_CMD_START_LINE);
    sh1107_write_param(0x00);

    sh1107_write_command(SH1107_CMD_DCDC_CONTROL);
    sh1107_write_param(SH1107_DCDC_ON);

    sh1107_write_command(SH1107_CMD_SEG_REMAP_OFF);
    sh1107_write_command(SH1107_CMD_COM_SCAN_NORMAL);

    sh1107_write_command(SH1107_CMD_PRECHARGE);
    sh1107_write_param(0x22);

    sh1107_write_command(SH1107_CMD_VCOM_DESELECT);
    sh1107_write_param(0x35);

    sh1107_set_contrast(cfg->contrast);

    sh1107_write_command(SH1107_CMD_ENTIRE_OFF);
    sh1107_write_command(cfg->invert ? SH1107_CMD_REVERSE : SH1107_CMD_NORMAL);

    if (cfg->init_seq)
    {
        send_init_sequence(cfg->init_seq);
    }

    sh1107_update(0, 0, display_width - 1, display_height - 1);

    sh1107_display_power(1);
    Delay_ms(SH1107_DELAY_DISPLAY_ON_MS);
}
