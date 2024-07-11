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
 * @file  ssd1963.c
 * @brief SSD1963 controller source file.
 */

#include "ssd1963.h"
#include "ssd1963_cmd.h"

#ifdef __GNUC__
#include <me_built_in.h>
#endif
#ifdef __MIKROC__
#include "built_in.h"
#endif
#include "drv_digital_out.h"
#include "drv_port.h"
#include "delays.h"

/**
 * @remark No context for display controller driver, because in most cases only
 * one TFT display on board. Performance concerns.
 */
static digital_out_t pin_rst;
static digital_out_t pin_cs;
static digital_out_t pin_dc;
static digital_out_t pin_wr;
static digital_out_t pin_rd;

static port_t data_channel_0;
static port_t data_channel_1;

static uint16_t display_width;
static uint16_t display_height;

static uint8_t port_shift_8bit = 0;
static uint8_t port_shift_16bit_low = 0;
static uint8_t port_shift_16bit_high = 0;

#define DATA_PORT_NIBBLE_HIGH 0xFF00

#define DATA_SELECT() digital_out_high(&pin_dc);
#define COMMAND_SELECT() digital_out_low(&pin_dc);

#define WRITE_STROBE() \
    digital_out_low(&pin_wr); \
    digital_out_high(&pin_wr)

#define CS_ACTIVE() digital_out_low(&pin_cs)
#define CS_DEACTIVE() digital_out_high(&pin_cs)


uint16_t ssd1963_get_display_width()
{
    return display_width;
}

uint16_t ssd1963_get_display_height()
{
    return display_height;
}


/**
 * @brief This function supports only one rotation. Should be implemented for
 * rest.
 */
void _ssd1963_begin_frame(gl_rectangle_t *rect)
{
    /// Orientation dependent.
    uint16_t start_column = (display_width - 1) - (rect->top_left.x + rect->width - 1);
    uint16_t end_column =  (display_width - 1) - rect->top_left.x;
    uint16_t start_page = (display_height - 1) - (rect->top_left.y + rect->height - 1);
    uint16_t end_page = (display_height - 1) - rect->top_left.y;

    // CS_ACTIVE();

    ssd1963_write_command(SSD1963_CMD_SET_COLUMN_ADDRESS);
    ssd1963_write_param(Hi(start_column));
    ssd1963_write_param(Lo(start_column));
    ssd1963_write_param(Hi(end_column));
    ssd1963_write_param(Lo(end_column));

    ssd1963_write_command(SSD1963_CMD_SET_PAGE_ADDRESS);
    ssd1963_write_param(Hi(start_page));
    ssd1963_write_param(Lo(start_page));
    ssd1963_write_param(Hi(end_page));
    ssd1963_write_param(Lo(end_page));

    ssd1963_write_command(SSD1963_CMD_WRITE_MEMORY_START);

    CS_ACTIVE();
    DATA_SELECT();
}

void _ssd1963_end_frame()
{
    CS_DEACTIVE();
}

// TODO Fix color, see datasheet 3cycles
void _fill_8bit_host_interface(gl_rectangle_t *rect, gl_color_t color)
{
    uint32_t length = (uint32_t)rect->width * (uint32_t)rect->height;
    uint32_t value1 = ((color & 0xF800) >> 8) & 0x00FF;
    uint32_t value2 = ((color & 0x07E0 ) >> 3) & 0x00FF;
    uint32_t value3 = ((color & 0x001F ) << 3) & 0x00FF;

    if (!length)
        return;

    _ssd1963_begin_frame(rect);

    while(length--)
    {
        port_write(&data_channel_0, value1<<port_shift_8bit);
        WRITE_STROBE();

        port_write(&data_channel_0, value2<<port_shift_8bit);
        WRITE_STROBE();

        port_write(&data_channel_0, value3<<port_shift_8bit);
        WRITE_STROBE();
    }

    _ssd1963_end_frame();
}

/**
 * @brief Optimized function for sending color fill data with 16-bit host
 * interface when all 16-bits are routed from single port.
 */
void _fill_16bit_host_interface_single_channel(gl_rectangle_t *rect, gl_color_t color)
{
    uint32_t length = (uint32_t)rect->width * (uint32_t)rect->height;

    if (!length)
        return;

    _ssd1963_begin_frame(rect);

    port_write(&data_channel_0, color<<port_shift_16bit_low);
    while(length--)
    {
        WRITE_STROBE();
    }

    _ssd1963_end_frame();
}

void _fill_16bit_host_interface(gl_rectangle_t *rect, gl_color_t color)
{
    uint32_t length = (uint32_t)rect->width * (uint32_t)rect->height;

    if (!length)
        return;

    _ssd1963_begin_frame(rect);

    port_write(&data_channel_0, Lo(color)<<port_shift_16bit_low);
    port_write(&data_channel_1, Hi(color)<<port_shift_16bit_high);
    while(length--)
    {
        WRITE_STROBE();
    }

    _ssd1963_end_frame();
}

// TODO Fix color, see datasheet 3cycles
void _frame_data_8bit_host_interface(gl_color_t color)
{
    port_write(&data_channel_0, ((color & 0xF800) >> 8)<<port_shift_8bit);
    WRITE_STROBE();

    port_write(&data_channel_0, ((color & 0x07E0 ) >> 3)<<port_shift_8bit);
    WRITE_STROBE();

    port_write(&data_channel_0, ((color & 0x001F ) << 3)<<port_shift_8bit);
    WRITE_STROBE();
}

// TODO Fix color, see datasheet 3cycles
void _frame_data_16bit_host_interface_single_channel(gl_color_t color)
{
    port_write(&data_channel_0, color<<port_shift_16bit_low);
    WRITE_STROBE();
}

void _frame_data_16bit_host_interface(gl_color_t color)
{
    port_write(&data_channel_0, Lo(color)<<port_shift_16bit_low);
    port_write(&data_channel_1, Hi(color)<<port_shift_16bit_high);
    WRITE_STROBE();
}

void ssd1963_init(ssd1963_cfg_t *cfg, gl_driver_t * __generic_ptr driver)
{
    digital_out_init(&pin_cs, cfg->cs);
    digital_out_init(&pin_dc, cfg->d_c);
    digital_out_init(&pin_wr, cfg->wr);
    digital_out_init(&pin_rd, cfg->rd);
    digital_out_init(&pin_rst, cfg->rst);

    digital_out_high(&pin_cs);
    digital_out_high(&pin_dc);
    digital_out_high(&pin_wr);
    digital_out_high(&pin_rd);
    digital_out_low(&pin_rst);

    port_init(&data_channel_0, cfg->data_channel_0, cfg->data_channel_0_mask, GPIO_DIGITAL_OUTPUT);
    port_write(&data_channel_0, 0x0000);

    if (cfg->host_interface == SSD1963_HOST_INTERFACE_8BIT)
    {
        driver->fill_f = _fill_8bit_host_interface;
        driver->frame_data_f = _frame_data_8bit_host_interface;

        port_shift_8bit = 0;
        if (cfg->data_channel_0_mask == DATA_PORT_NIBBLE_HIGH) {
            port_shift_8bit = 8;
        }
    }

    if (cfg->host_interface == SSD1963_HOST_INTERFACE_16BIT)
    {
        if (cfg->data_channel_1 == HAL_PORT_NC)
        {
            driver->fill_f = _fill_16bit_host_interface_single_channel;
            driver->frame_data_f = _frame_data_16bit_host_interface_single_channel;

            port_shift_16bit_low = 0;
            if(cfg->data_channel_0_mask == DATA_PORT_NIBBLE_HIGH) {
                port_shift_16bit_low = 8;
            }
        }
        else
        {
            port_init(&data_channel_1, cfg->data_channel_1, cfg->data_channel_1_mask, GPIO_DIGITAL_OUTPUT);
            port_write(&data_channel_1, 0x0000);

            driver->fill_f = _fill_16bit_host_interface;
            driver->frame_data_f = _frame_data_16bit_host_interface;

            port_shift_16bit_low = 0;
            port_shift_16bit_high = 0;
            if(cfg->data_channel_0_mask == DATA_PORT_NIBBLE_HIGH) {
                port_shift_16bit_low = 8;
            }
            if(cfg->data_channel_1_mask == DATA_PORT_NIBBLE_HIGH) {
                port_shift_16bit_high = 8;
            }
        }
    }

    driver->begin_frame_f = _ssd1963_begin_frame;
    driver->end_frame_f = _ssd1963_end_frame;

    display_width = cfg->width;
    driver->display_width = cfg->width;
    display_height = cfg->height;
    driver->display_height = cfg->height;

    Delay_100ms();
    digital_out_high(&pin_rst);
    Delay_100ms();
    Delay_100ms();
}

void ssd1963_write_command(uint8_t command)
{
    CS_ACTIVE();
    COMMAND_SELECT();

    port_write(&data_channel_0, command<<port_shift_8bit);
    WRITE_STROBE();
    CS_DEACTIVE();
}

void ssd1963_write_param(uint8_t param)
{
    CS_ACTIVE();
    DATA_SELECT();

    port_write(&data_channel_0, param<<port_shift_8bit);
    WRITE_STROBE();
    CS_DEACTIVE();
}

// ------------------------------------------------------------------------- END
