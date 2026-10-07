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
 * @file  st7789.c
 * @brief ST7789 controller source file.
 */
 
#include "st7789.h"
#include "st7789_cmd.h"
#include "gl.h"
 
#ifdef __GNUC__
#include <me_built_in.h>
#endif
#ifdef __MIKROC__
#include "built_in.h"
#endif
#include "drv_digital_out.h"
#include "drv_spi_master.h"
#include "delays.h"
 
/**
 * @remark No context for display controller driver, because in most cases only
 * one TFT display on board. Performance concerns.
 */
static digital_out_t pin_rst;
static digital_out_t pin_cs;
static digital_out_t pin_dc;
static spi_master_t spi_master;
 
static uint16_t display_width;
static uint16_t display_height;
 
static uint16_t native_width;
static uint16_t native_height;
 
static gl_driver_t *current_gl_driver = NULL;
static uint8_t cs_used;                                           
static digital_out_t pin_sck_soft;
static digital_out_t pin_mosi_soft;
static uint8_t soft_spi;
static uint16_t offset_x;
static uint16_t offset_y;

#define DATA_SELECT() digital_out_high(&pin_dc)
#define COMMAND_SELECT() digital_out_low(&pin_dc)
#define CS_ACTIVE() do { if (cs_used) { digital_out_low(&pin_cs); } } while (0)
#define CS_DEACTIVE() do { if (cs_used) { digital_out_high(&pin_cs); } } while (0)
#define ST7789_FILL_CHUNK 64   // Number of pixels sent with one SPI write.
#define ST7789_RAM_WIDTH 240 //Size of the controller memory, in pixels
#define ST7789_RAM_HEIGHT 320

static void spi_send(uint8_t *data, uint32_t length)
{
    if (!soft_spi)
    {
        spi_master_write(&spi_master, data, length);
        return;
    }

    while (length--)
    {
        uint8_t value = *data++;
        uint8_t bit;

        for (bit = 0; bit < 8; bit++)
        {
            if (value & 0x80)
            {
                digital_out_high(&pin_mosi_soft);
            }
            else
            {
                digital_out_low(&pin_mosi_soft);
            }

            digital_out_low(&pin_sck_soft);
            digital_out_high(&pin_sck_soft);
            value <<= 1;
        }
    }
}

uint16_t st7789_get_display_width()
{
    return display_width;
}
 
uint16_t st7789_get_display_height()
{
    return display_height;
}
 
void _st7789_begin_frame(gl_rectangle_t *rect)
{
    uint16_t start_column = rect->top_left.x + offset_x;
    uint16_t end_column = rect->top_left.x + rect->width - 1 + offset_x;
    uint16_t start_page = rect->top_left.y + offset_y;
    uint16_t end_page = rect->top_left.y + rect->height - 1 + offset_y;
 
    st7789_write_command(ST7789_CMD_CASET);
    st7789_write_param(Hi(start_column));
    st7789_write_param(Lo(start_column));
    st7789_write_param(Hi(end_column));
    st7789_write_param(Lo(end_column));
 
    st7789_write_command(ST7789_CMD_RASET);
    st7789_write_param(Hi(start_page));
    st7789_write_param(Lo(start_page));
    st7789_write_param(Hi(end_page));
    st7789_write_param(Lo(end_page));
 
    st7789_write_command(ST7789_CMD_RAMWR);
 
    CS_ACTIVE();
    DATA_SELECT();
}
 
void _st7789_end_frame()
{
    CS_DEACTIVE();
}
 
void _st7789_frame_data(gl_color_t color)
{
    uint8_t pixel[2];
 
    pixel[0] = Hi(color);   /* High byte first. */
    pixel[1] = Lo(color);   /* Low byte second. */
 
    spi_send(pixel, 2);
}
 
void _st7789_fill(gl_rectangle_t *rect, gl_color_t color)
{
    uint32_t length = (uint32_t)rect->width * (uint32_t)rect->height;
    uint8_t buffer[ST7789_FILL_CHUNK * 2];
    uint8_t high = Hi(color);
    uint8_t low = Lo(color);
    uint32_t chunk;
    uint32_t i;
 
    if (!length)
    {
        return;
    }
 
    // Fill the buffer with the color (only as many pixels as needed).
    chunk = (length < ST7789_FILL_CHUNK) ? length : ST7789_FILL_CHUNK;
 
    for (i = 0; i < chunk; i++)
    {
        buffer[i * 2] = high;
        buffer[i * 2 + 1] = low;
    }
 
    _st7789_begin_frame(rect);
 
    while (length >= ST7789_FILL_CHUNK)
    {
        spi_send(buffer, ST7789_FILL_CHUNK * 2);
        length -= ST7789_FILL_CHUNK;
    }
 
    if (length)
    {
        spi_send(buffer, length * 2);
    }
 
    _st7789_end_frame();
}

static void send_init_sequence(const uint8_t *sequence)
{
    while (*sequence)
    {
        uint8_t command = *sequence++;
        uint8_t count = *sequence++;

        st7789_write_command(command);

        while (count--)
        {
            st7789_write_param(*sequence++);
        }
    }
}
 
void st7789_init(st7789_cfg_t *cfg, gl_driver_t * __generic_ptr driver)
{
    spi_master_config_t spi_cfg;
 
    cs_used = (HAL_PIN_NC != cfg->cs);

    if (cs_used)
    {
        digital_out_init(&pin_cs, cfg->cs);
        digital_out_high(&pin_cs);
    }
    digital_out_init(&pin_dc, cfg->d_c);
    digital_out_init(&pin_rst, cfg->rst);

    soft_spi = cfg->soft_spi;

    if (soft_spi)
    {
        digital_out_init(&pin_sck_soft, cfg->sck);
        digital_out_init(&pin_mosi_soft, cfg->mosi);
        digital_out_high(&pin_sck_soft);
    }
 
    digital_out_high(&pin_dc);
    digital_out_low(&pin_rst);
 
    if (!soft_spi)
    {
        spi_master_configure_default(&spi_cfg);
        spi_cfg.sck = cfg->sck;
        spi_cfg.miso = cfg->miso;
        spi_cfg.mosi = cfg->mosi;
        spi_cfg.speed = cfg->speed;
        spi_cfg.mode = (spi_master_mode_t)cfg->spi_mode;

        if (SPI_MASTER_ERROR == spi_master_open(&spi_master, &spi_cfg))
        {
            return;
        }

        spi_master_set_speed(&spi_master, cfg->speed);
    }
 
    driver->fill_f = _st7789_fill;
    driver->begin_frame_f = _st7789_begin_frame;
    driver->end_frame_f = _st7789_end_frame;
    driver->frame_data_f = _st7789_frame_data;
 
    current_gl_driver = driver;
 
    display_width = cfg->width;
    driver->display_width = cfg->width;
    display_height = cfg->height;
    driver->display_height = cfg->height;
 
    native_width = cfg->width;
    native_height = cfg->height;
 
    Delay_100ms();
    digital_out_high(&pin_rst);
    Delay_100ms();
    Delay_100ms();
 
    st7789_write_command(ST7789_CMD_SWRESET);
    Delay_ms(ST7789_DELAY_SWRESET_MS);
    
    if (cfg->init_seq)
    {
        send_init_sequence(cfg->init_seq);
    }
 
    st7789_write_command(ST7789_CMD_SLPOUT);
    Delay_ms(ST7789_DELAY_SLPOUT_MS);
 
    st7789_write_command(ST7789_CMD_COLMOD);
    st7789_write_param(ST7789_COLMOD_16BIT);
 
    if (cfg->invert)
    {
        st7789_write_command(ST7789_CMD_INVON);
    }
 
    st7789_write_command(ST7789_CMD_DISPON);
}
 
void st7789_write_command(uint8_t command)
{
    CS_ACTIVE();
    COMMAND_SELECT();
 
    spi_send(&command, 1);
 
    CS_DEACTIVE();
}
 
void st7789_write_param(uint8_t param)
{
    CS_ACTIVE();
    DATA_SELECT();
 
    spi_send(&param, 1);
 
    CS_DEACTIVE();
}
 
void st7789_write_pixels(const uint8_t *data, uint32_t length)
{
    spi_send((uint8_t *)data, length);
}
 
void st7789_rotate(uint8_t rotation)
{
    uint8_t madctl;
    uint8_t landscape;
    uint16_t column_offset;
    uint16_t row_offset;
 
    switch (rotation)
    {
        case 1:  madctl = ST7789_MADCTL_MX | ST7789_MADCTL_MV; landscape = 1; break;   // 90 degrees.
        case 2:  madctl = ST7789_MADCTL_MY | ST7789_MADCTL_MX; landscape = 0; break;   // 180 degrees.
        case 3:  madctl = ST7789_MADCTL_MY | ST7789_MADCTL_MV; landscape = 1; break;   // 270 degrees.
        default: madctl = 0x00; landscape = 0; break;                                  // 0 degrees.
    }
 
    st7789_write_command(ST7789_CMD_MADCTL);
    st7789_write_param(madctl);
    // A panel smaller than the controller memory sits at the end of the memory
    // when the order of that axis is reversed, so the window has to be shifted.
    column_offset = (madctl & ST7789_MADCTL_MX) ? (ST7789_RAM_WIDTH - native_width) : 0;
    row_offset = (madctl & ST7789_MADCTL_MY) ? (ST7789_RAM_HEIGHT - native_height) : 0;
    if(madctl & ST7789_MADCTL_MV)
    {
        offset_x = row_offset;
        offset_y = column_offset;
    }
    else
    {
        offset_x = column_offset;
        offset_y = row_offset;
    }
 
    display_width  = landscape ? native_height : native_width;
    display_height = landscape ? native_width : native_height;
 
    if (current_gl_driver)
    {
        current_gl_driver->display_width  = display_width;
        current_gl_driver->display_height = display_height;
 
        // Graphic library keeps its own copy of the driver, so update it.
        gl_set_driver(current_gl_driver);
    }
}
 
void st7789_display_power(uint8_t state)
{
    if (state)
    {
        st7789_write_command(ST7789_CMD_DISPON);
    }
    else
    {
        st7789_write_command(ST7789_CMD_DISPOFF);
    }
}
