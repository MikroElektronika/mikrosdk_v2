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

#include "ips.h"

#include "st7789_cmd.h"
#include "st7789.h"
#include "delays.h"

static st7789_t display_ctx; /*!< Display Context Object. */
static void _reset_st7789_ips_display_2_click_240x240();

/**
 * @brief IPS
 */

const ips_display_t IPS_DISPLAY_2_CLICK = {
    240, // display_width
    240, // display_height
    _reset_st7789_ips_display_2_click_240x240
};

static void _reset_st7789_ips_display_2_click_240x240()
{
    st7789_reset();

    st7789_write_command( ST7789_CMD_MADCTL );
    st7789_write_param( 0x00 );

    // 16 bit pixel format
    st7789_write_command( ST7789_CMD_COLMOD );
    st7789_write_param( 0x05 );

    // According to ST7789V2 this should not be needed as its default from RST
   st7789_write_command( ST7789_CMD_PORCTRL );
   st7789_write_param( 0x0C );
   st7789_write_param( 0x0C );
   st7789_write_param( 0x00 );
   st7789_write_param( 0x33 );
   st7789_write_param( 0x33 );

   st7789_write_command( ST7789_CMD_GCTRL );
   st7789_write_param( 0x35 );

   st7789_write_command( ST7789_CMD_VCOMS );
   st7789_write_param( 0x19 );

   st7789_write_command( ST7789_CMD_LCMCTRL );
   st7789_write_param( 0x2C );

   st7789_write_command( ST7789_CMD_VDVVRHEN );
   st7789_write_param( 0x01 );

   st7789_write_command( ST7789_CMD_VRHS );
   st7789_write_param( 0x19 );

   st7789_write_command( ST7789_CMD_VDVSET ); 
   st7789_write_param( 0x20 );

    // Frame Rate Control in Normal Mode at 60Hz
   st7789_write_command( ST7789_CMD_FRCTR2 );
   st7789_write_param( 0x0F );

   st7789_write_command( ST7789_CMD_PWCTRL1 );
   st7789_write_param( 0xA4 );
   st7789_write_param( 0xA1 );

   st7789_write_command( ST7789_CMD_PVGAMCTRL );
   st7789_write_param( 0xD0 );
   st7789_write_param( 0x08 );
   st7789_write_param( 0x0E );
   st7789_write_param( 0x09 );
   st7789_write_param( 0x09 );
   st7789_write_param( 0x05 );
   st7789_write_param( 0x31 );
   st7789_write_param( 0x33 );
   st7789_write_param( 0x48 );
   st7789_write_param( 0x17 );
   st7789_write_param( 0x14 );
   st7789_write_param( 0x15 );
   st7789_write_param( 0x31 );
   st7789_write_param( 0x34 );

   // Negative Voltage Gamma Control
   st7789_write_command( ST7789_CMD_NVGAMCTRL ); 
   st7789_write_param( 0xD0 );
   st7789_write_param( 0x08 );
   st7789_write_param( 0x0E );
   st7789_write_param( 0x09 );
   st7789_write_param( 0x09 );
   st7789_write_param( 0x15 );
   st7789_write_param( 0x31 );
   st7789_write_param( 0x33 );
   st7789_write_param( 0x48 );
   st7789_write_param( 0x17 );
   st7789_write_param( 0x14 );
   st7789_write_param( 0x15 );
   st7789_write_param( 0x31 );
   st7789_write_param( 0x34 );

   // Turn on display inversion
   st7789_write_command( ST7789_CMD_INVON );

   // Exit sleep mode
   st7789_write_command( ST7789_CMD_SLPOUT );
   Delay_100ms();
   Delay_10ms();
   Delay_10ms();

   st7789_write_command( ST7789_CMD_DISPON ); //
}

void ips_init(ips_cfg_t *cfg, gl_driver_t *driver)
{
    st7789_cfg_t st7789_cfg;
    st7789_cfg.bck = cfg->ips_bck;
    st7789_cfg.rst = cfg->ips_rst;
    st7789_cfg.cs = cfg->ips_cs;
    st7789_cfg.sck = cfg->ips_sck;
    st7789_cfg.sdi = cfg->ips_sdi;
    st7789_cfg.sdo = cfg->ips_sdo;
    st7789_cfg.rs = cfg->ips_dc;

    st7789_cfg.width  = cfg->board->display_width;
    st7789_cfg.height = cfg->board->display_height;

    st7789_init( &display_ctx, &st7789_cfg, &driver );
    cfg->board->reset_procedure();

    // Set backlight.
    ips_set_backlight(0xFF);
}

uint16_t ips_display_width()
{
    return st7789_get_display_width();
}

uint16_t ips_display_height()
{
    return st7789_get_display_height();
}

void ips_set_backlight(uint8_t intensity)
{
    st7789_set_backlight( intensity );
}
