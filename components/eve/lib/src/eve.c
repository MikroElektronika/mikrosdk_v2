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

#include "eve.h"

#include "ft800.h"
#include "ft800_reg.h"
#include "ft800_const.h"

static ft800_t display_ctx; /*!< Display Context Object. */
static uint16_t display_width;
static uint16_t display_height;

/**
 * @brief EVE
 */

const eve_display_t EVE_CLICK = {
    480, // display_width
    272  // display_height
};

void eve_init( eve_cfg_t *cfg, gl_driver_t *driver )
{
    ft800_cfg_t ft800_cfg;

    ft800_cfg_setup( &ft800_cfg, &FT800_CONTROLLER );
    ft800_cfg.cs_pin = cfg->eve_cs;
    ft800_cfg.sck_pin = cfg->eve_sck;
    ft800_cfg.mosi_pin = cfg->eve_sdi;
    ft800_cfg.miso_pin = cfg->eve_sdo;
    ft800_cfg.pd_pin = cfg->eve_pd;
    ft800_default_cfg( &ft800_cfg );

    ft800_cfg.width = cfg->board->display_width;
    ft800_cfg.height = cfg->board->display_height;
    display_width = ft800_cfg.width;
    display_height = ft800_cfg.height;

    ft800_display_init( &display_ctx, &ft800_cfg, driver );

    // Set backlight.
    eve_set_backlight( EVE_MAX_BACKLIGHT );
}

uint16_t eve_display_width()
{
    return display_width;
}

uint16_t eve_display_height()
{
    return display_height;
}

void eve_set_backlight( uint8_t intensity )
{
    // FT800 backlight duty cycle goes from 0 to 128.
    ft800_set_backlight( &display_ctx, ( uint8_t )( ( ( uint16_t )intensity + 1 ) >> 1 ) );
}

void eve_write_pixels( uint16_t x, uint16_t y, uint8_t *pixels, uint16_t length )
{
    ft800_write_ram_g( &display_ctx, FT800_FRAME_BUFFER_ADDRESS( x, y, display_width ),
                       pixels, ( uint32_t )length * FT800_FRAME_BUFFER_PIXEL_SIZE );
}
