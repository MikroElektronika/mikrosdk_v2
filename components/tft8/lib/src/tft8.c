/****************************************************************************
**
** Copyright (C) 2022 MikroElektronika d.o.o.
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

#include "tft8.h"

#include "ssd1963_cmd.h"
#include "ssd1963.h"

static void _reset_ssd1963_controller_320x240_8bit();
static void _reset_ssd1963_controller_320x240();
static void _reset_ssd1963_controller_480x272();
static void _reset_ssd1963_controller_800x480();

/**
 * @brief RESISTIVE
 */

const tft8_board_t TFT_BOARD_3_RESISTIVE = {
    320, // display_width
    240, // display_height
    _reset_ssd1963_controller_320x240
};

const tft8_board_t TFT_BOARD_4_RESISTIVE = {
    480, // display_width
    272, // display_height
    _reset_ssd1963_controller_480x272
};

const tft8_board_t TFT_BOARD_5_RESISTIVE = {
    800, // display_width
    480, // display_height
    _reset_ssd1963_controller_800x480
};

const tft8_board_t TFT_BOARD_7_RESISTIVE = {
    800, // display_width
    480, // display_height
    _reset_ssd1963_controller_800x480
};

/**
 * @brief CAPACITIVE
 */

const tft8_board_t MIKROMEDIA_3_CAPACITIVE = {
    320, // display_width
    240, // display_height
    _reset_ssd1963_controller_320x240_8bit
};

const tft8_board_t TFT_BOARD_3_CAPACITIVE = {
    320, // display_width
    240, // display_height
    _reset_ssd1963_controller_320x240
};

const tft8_board_t TFT_BOARD_4_CAPACITIVE = {
    480, // display_width
    272, // display_height
    _reset_ssd1963_controller_480x272
};

const tft8_board_t TFT_BOARD_5_CAPACITIVE = {
    800, // display_width
    480, // display_height
    _reset_ssd1963_controller_800x480
};

const tft8_board_t TFT_BOARD_7_CAPACITIVE = {
    800, // display_width
    480, // display_height
    _reset_ssd1963_controller_800x480
};

static void _reset_ssd1963_controller_320x240_8bit()
{
    // CS_ACTIVE();
    ssd1963_write_command(SSD1963_CMD_SOFT_RESET);
    ssd1963_write_command(SSD1963_CMD_SOFT_RESET);
    ssd1963_write_command(SSD1963_CMD_SOFT_RESET);

    ssd1963_write_command(SSD1963_CMD_SET_PLL_MN);
    ssd1963_write_param(35);
    ssd1963_write_param(2);
    ssd1963_write_param(0x54);

    // START PLL
    ssd1963_write_command(SSD1963_CMD_SET_PLL);
    ssd1963_write_param(0x01);
    Delay_50us();
    Delay_50us();

    // LOCK PLL
    ssd1963_write_command(SSD1963_CMD_SET_PLL);
    ssd1963_write_param(0x03);

    ssd1963_write_command(SSD1963_CMD_SET_LCD_MODE);
    ssd1963_write_param(0x2C);
    ssd1963_write_param(0x20);
    ssd1963_write_param(0x01);
    ssd1963_write_param(0x3F);
    ssd1963_write_param(0x00);
    ssd1963_write_param(0xEF);
    ssd1963_write_param(0x00);

    ssd1963_write_command(SSD1963_CMD_SET_PIXEL_DATA_INTERFACE);
    ssd1963_write_param(0x00);

    // Command SSD1963_CMD_SET_PIXEL_FORMAT (0x3A) removed.
    ssd1963_write_command(0x3A);
    ssd1963_write_param(0x60);

    //SET PCLK freq=10MHz. Pixel clock frequency.
    ssd1963_write_command(SSD1963_CMD_SET_LSHIFT_FREQ);
    ssd1963_write_param(0x01);
    ssd1963_write_param(0x55);
    ssd1963_write_param(0x55);

    ssd1963_write_command(SSD1963_CMD_SET_HORI_PERIOD);
    ssd1963_write_param(0x01);
    ssd1963_write_param(0x98);
    ssd1963_write_param(0x00);
    ssd1963_write_param(0x44);
    ssd1963_write_param(0x28);
    ssd1963_write_param(0x00);
    ssd1963_write_param(0x00);
    ssd1963_write_param(0x00);

    ssd1963_write_command(SSD1963_CMD_SET_VERT_PERIOD);
    ssd1963_write_param(0x01);
    ssd1963_write_param(0x06);
    ssd1963_write_param(0x00);
    ssd1963_write_param(0x12);
    ssd1963_write_param(0x0A);
    ssd1963_write_param(0x00);
    ssd1963_write_param(0x00);

    // Rotation dependent.
    ssd1963_write_command(SSD1963_CMD_SET_ADDRESS_MODE);
    ssd1963_write_param(0xC0);

    ssd1963_write_command(SSD1963_CMD_SET_DISPLAY_ON);
}

static void _reset_ssd1963_controller_320x240()
{
    // CS_ACTIVE();
    ssd1963_write_command(SSD1963_CMD_SOFT_RESET);
    ssd1963_write_command(SSD1963_CMD_SOFT_RESET);
    ssd1963_write_command(SSD1963_CMD_SOFT_RESET);

    ssd1963_write_command(SSD1963_CMD_SET_PLL_MN);
    ssd1963_write_param(35);
    ssd1963_write_param(2);
    ssd1963_write_param(0x54);

    // START PLL
    ssd1963_write_command(SSD1963_CMD_SET_PLL);
    ssd1963_write_param(0x01);
    Delay_50us();
    Delay_50us();

    // LOCK PLL
    ssd1963_write_command(SSD1963_CMD_SET_PLL);
    ssd1963_write_param(0x03);

    ssd1963_write_command(SSD1963_CMD_SET_LCD_MODE);
    ssd1963_write_param(0x2C);
    ssd1963_write_param(0x20);
    ssd1963_write_param(0x01);
    ssd1963_write_param(0x3F);
    ssd1963_write_param(0x00);
    ssd1963_write_param(0xEF);
    ssd1963_write_param(0x00);

    ssd1963_write_command(SSD1963_CMD_SET_PIXEL_DATA_INTERFACE);
    #ifdef __16_bit_interface__
    ssd1963_write_param(0x03);
    #else
    ssd1963_write_param(0x00);
    #endif

    // Command SSD1963_CMD_SET_PIXEL_FORMAT (0x3A) removed.
    ssd1963_write_command(0x3A);
    ssd1963_write_param(0x60);

    //SET PCLK freq=10MHz. Pixel clock frequency.
    ssd1963_write_command(SSD1963_CMD_SET_LSHIFT_FREQ);
    ssd1963_write_param(0x01);
    ssd1963_write_param(0x55);
    ssd1963_write_param(0x55);

    ssd1963_write_command(SSD1963_CMD_SET_HORI_PERIOD);
    ssd1963_write_param(0x01);
    ssd1963_write_param(0x98);
    ssd1963_write_param(0x00);
    ssd1963_write_param(0x44);
    ssd1963_write_param(0x28);
    ssd1963_write_param(0x00);
    ssd1963_write_param(0x00);
    ssd1963_write_param(0x00);

    ssd1963_write_command(SSD1963_CMD_SET_VERT_PERIOD);
    ssd1963_write_param(0x01);
    ssd1963_write_param(0x06);
    ssd1963_write_param(0x00);
    ssd1963_write_param(0x12);
    ssd1963_write_param(0x0A);
    ssd1963_write_param(0x00);
    ssd1963_write_param(0x00);

    // Rotation dependent.
    ssd1963_write_command(SSD1963_CMD_SET_ADDRESS_MODE);
    ssd1963_write_param(0xC0);

    ssd1963_write_command(SSD1963_CMD_SET_DISPLAY_ON);
}

static void _reset_ssd1963_controller_480x272()
{
    // Software reset.
    ssd1963_write_command(SSD1963_CMD_SOFT_RESET);
    ssd1963_write_command(SSD1963_CMD_SOFT_RESET);
    ssd1963_write_command(SSD1963_CMD_SOFT_RESET);

    // PLL.
    ssd1963_write_command(SSD1963_CMD_SET_PLL_MN);
    ssd1963_write_param(35);
    ssd1963_write_param(2);
    ssd1963_write_param(0x54);

    // START PLL.
    ssd1963_write_command(SSD1963_CMD_SET_PLL);
    ssd1963_write_param(0x01);
    Delay_50us();
    Delay_50us();

    // LOCK PLL.
    ssd1963_write_command(SSD1963_CMD_SET_PLL);
    ssd1963_write_param(0x03);

    ssd1963_write_command(SSD1963_CMD_SET_LCD_MODE);
    ssd1963_write_param(0x28);
    ssd1963_write_param(0x20);

    ssd1963_write_param(0x01);  // SET horizontal size=480-1 HightByte
    ssd1963_write_param(0xDF);  // SET horizontal size=480-1 LowByte
    ssd1963_write_param(0x01);  // SET vertical size=272-1 HightByte
    ssd1963_write_param(0x0F);  // SET vertical size=272-1 LowByte
    ssd1963_write_param(0x00);  // SET even/odd line RGB seq.=RGB

    ssd1963_write_command(SSD1963_CMD_SET_PIXEL_DATA_INTERFACE);
    #ifdef __16_bit_interface__
    ssd1963_write_param(0x03);
    #else
    ssd1963_write_param(0x00);
    #endif

    // Command SSD1963_CMD_SET_PIXEL_FORMAT (0x3A) removed.
    ssd1963_write_command(0x3A);
    ssd1963_write_param(0x60);

    // SET PCLK freq=10MHz. Pixel clock frequency.
    #ifdef __resistive__
    // Configuration for resistive
    ssd1963_write_command(SSD1963_CMD_SET_LSHIFT_FREQ ); //SET PCLK freq=10MHz  ; pixel clock frequency
    ssd1963_write_param(0x01);
    ssd1963_write_param(0x45);
    ssd1963_write_param(0x47);

    ssd1963_write_command(SSD1963_CMD_SET_HORI_PERIOD);     //SET HBP,
    ssd1963_write_param(0x02); //SET HSYNC Tatol 525
    ssd1963_write_param(0x0d);
    ssd1963_write_param(0x00); //SET HBP 43
    ssd1963_write_param(0x2b);
    ssd1963_write_param(0x28); //SET VBP 41=40+1
    ssd1963_write_param(0x00); //SET Hsync pulse start position
    ssd1963_write_param(0x00);
    ssd1963_write_param(0x00); //SET Hsync pulse subpixel start position

    ssd1963_write_command(SSD1963_CMD_SET_VERT_PERIOD);     //SET VBP,
    ssd1963_write_param(0x01); //SET Vsync total 286=285+1
    ssd1963_write_param(0x1d);
    ssd1963_write_param(0x00); //SET VBP=12
    ssd1963_write_param(0x0c);
    ssd1963_write_param(0x09); //SET Vsync pulse 10=9+1
    ssd1963_write_param(0x00); //SET Vsync pulse start position
    ssd1963_write_param(0x00);
    #else
    // Configuration for capacitive.
    ssd1963_write_command(SSD1963_CMD_SET_LSHIFT_FREQ);
    ssd1963_write_param(0x04);
    ssd1963_write_param(0x3A);
    ssd1963_write_param(0xB6);

    ssd1963_write_command(SSD1963_CMD_SET_HORI_PERIOD);
    ssd1963_write_param(0x04);
    ssd1963_write_param(0x20);
    ssd1963_write_param(0x00);
    ssd1963_write_param(0x30);
    ssd1963_write_param(0x30);
    ssd1963_write_param(0x00);
    ssd1963_write_param(0x00);
    ssd1963_write_param(0x00);

    ssd1963_write_command(SSD1963_CMD_SET_VERT_PERIOD);
    ssd1963_write_param(0x02);
    ssd1963_write_param(0x0D);
    ssd1963_write_param(0x00);
    ssd1963_write_param(0x16);
    ssd1963_write_param(0x04);
    ssd1963_write_param(0x00);
    ssd1963_write_param(0x00);
    #endif

    // Rotation dependent.
    ssd1963_write_command(SSD1963_CMD_SET_ADDRESS_MODE);
    ssd1963_write_param(0xC0);

    ssd1963_write_command(SSD1963_CMD_SET_DISPLAY_ON);
}

static void _reset_ssd1963_controller_800x480()
{
    // CS_ACTIVE();
    ssd1963_write_command(SSD1963_CMD_SOFT_RESET);
    ssd1963_write_command(SSD1963_CMD_SOFT_RESET);
    ssd1963_write_command(SSD1963_CMD_SOFT_RESET);

    ssd1963_write_command(SSD1963_CMD_SET_PLL_MN);
    ssd1963_write_param(35);
    ssd1963_write_param(2);
    ssd1963_write_param(0x54);

    // START PLL
    ssd1963_write_command(SSD1963_CMD_SET_PLL);
    ssd1963_write_param(0x01);
    Delay_50us();
    Delay_50us();

    // LOCK PLL
    ssd1963_write_command(SSD1963_CMD_SET_PLL);
    ssd1963_write_param(0x03);

    ssd1963_write_command(SSD1963_CMD_SET_LCD_MODE);
    ssd1963_write_param(0x28);
    ssd1963_write_param(0x20);
    ssd1963_write_param(0x03);
    ssd1963_write_param(0x1F);
    ssd1963_write_param(0x01);
    ssd1963_write_param(0xDF);
    ssd1963_write_param(0x00);

    ssd1963_write_command(SSD1963_CMD_SET_PIXEL_DATA_INTERFACE);
    #ifdef __16_bit_interface__
    ssd1963_write_param(0x03);
    #else
    ssd1963_write_param(0x00);
    #endif

    // Command SSD1963_CMD_SET_PIXEL_FORMAT (0x3A) removed.
    ssd1963_write_command(0x3A);
    ssd1963_write_param(0x60);

    //SET PCLK freq=10MHz. Pixel clock frequency.
    ssd1963_write_command(SSD1963_CMD_SET_LSHIFT_FREQ);
    ssd1963_write_param(0x04);
    ssd1963_write_param(0x3A);
    ssd1963_write_param(0x60);

    ssd1963_write_command(SSD1963_CMD_SET_HORI_PERIOD);
    ssd1963_write_param(0x04);
    ssd1963_write_param(0x20);
    ssd1963_write_param(0x00);
    ssd1963_write_param(0x30);
    ssd1963_write_param(0x30);
    ssd1963_write_param(0x00);
    ssd1963_write_param(0x00);
    ssd1963_write_param(0x00);

    ssd1963_write_command(SSD1963_CMD_SET_VERT_PERIOD);
    ssd1963_write_param(0x02);
    ssd1963_write_param(0x0D);
    ssd1963_write_param(0x00);
    ssd1963_write_param(0x16);
    ssd1963_write_param(0x04);
    ssd1963_write_param(0x00);
    ssd1963_write_param(0x00);

    // Rotation dependent.
    ssd1963_write_command(SSD1963_CMD_SET_ADDRESS_MODE);
    ssd1963_write_param(0xC0);

    ssd1963_write_command(SSD1963_CMD_SET_DISPLAY_ON);
}

void tft8_init(tft8_cfg_t *cfg, gl_driver_t *driver)
{
    ssd1963_cfg_t ssd1963_cfg;
    ssd1963_cfg.rst = cfg->tft_rst;
    ssd1963_cfg.cs = cfg->tft_cs;
    ssd1963_cfg.d_c = cfg->tft_d_c;
    ssd1963_cfg.rd = cfg->tft_rd;
    ssd1963_cfg.wr = cfg->tft_wr;

    ssd1963_cfg.data_channel_0 = cfg->data_channel_0;
    ssd1963_cfg.data_channel_0_mask = cfg->data_channel_0_mask;

    ssd1963_cfg.data_channel_1 = cfg->data_channel_1;
    ssd1963_cfg.data_channel_1_mask = cfg->data_channel_1_mask;

    ssd1963_cfg.host_interface = cfg->host_interface;

    ssd1963_cfg.width  = cfg->board->display_width;
    ssd1963_cfg.height = cfg->board->display_height;

    ssd1963_init(&ssd1963_cfg, driver);
    cfg->board->reset_procedure();

    // Set backlight.
    tft8_set_backlight(0xFF);
}

uint8_t tft8_is_supported_interface(tft8_host_interface_t interface)
{
    switch(interface)
    {
    case TFT8_HOST_INTERFACE_8BIT:
    case TFT8_HOST_INTERFACE_16BIT:
        return 0xFF;
    default:
        return 0x00;
    }
    return 0x00;
}

uint16_t tft8_display_width()
{
    return ssd1963_get_display_width();
}

uint16_t tft8_display_height()
{
    return ssd1963_get_display_height();
}

void tft8_set_backlight(uint8_t intenisty)
{
    ssd1963_write_command(SSD1963_CMD_SET_DISPLAY_OFF);
    ssd1963_write_command(SSD1963_CMD_SET_PWM_CONF);
    ssd1963_write_param(0x06);
    ssd1963_write_param(intenisty);
    ssd1963_write_param(0x01);
    ssd1963_write_param(0xFF);
    ssd1963_write_param(0x00);
    ssd1963_write_param(0x01);
    ssd1963_write_command(SSD1963_CMD_SET_DISPLAY_ON);
}
