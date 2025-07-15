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
 * @file  ft800.c
 * @brief FT800 controller source file.
 */

#include "ft800.h"
#include "ft800_cmd.h"
#include "ft800_reg.h"
#include "ft800_const.h"
#include "ft800_struct.h"


void ft800_cmd( ft800_t *ctx, ft800_cfg_t *cfg, uint32_t command, uint16_t *cmdOffset )
{
    ft800_write_data( ctx, cfg, FT800_RAM_CMD + *cmdOffset, command, \
        FT800_DATA_LENGTH_BYTES_4 );
    *cmdOffset += FT800_COMMAND_OFFSET;
    ft800_write_data( ctx, cfg, FT800_REG_CMD_WRITE, *cmdOffset, \
        FT800_DATA_LENGTH_BYTES_2 );
}

void ft800_cmd_line(ft800_t *ctx, ft800_cfg_t *cfg, uint16_t *cmdOffset, uint16_t x1, \
    uint16_t y1, uint16_t x2, uint16_t y2, uint16_t color, uint8_t width)
{
    ft800_cmd( ctx, cfg, FT800_BEGIN( FT800_LINES ) , cmdOffset );
    ft800_cmd( ctx, cfg, FT800_LINE_WIDTH( width * FT800_POINT_SIZE_SCALE ), \
        cmdOffset );
    ft800_cmd( ctx, cfg, FT800_COLOR_RGB( ft800_rgb_convert( color, "red" ), \
        ft800_rgb_convert( color, "green" ), ft800_rgb_convert( color, \
        "blue" ) ), cmdOffset );
    ft800_cmd( ctx, cfg, FT800_VERTEX2F( x1 * FT800_POINT_SIZE_SCALE, \
        y1 * FT800_POINT_SIZE_SCALE ), cmdOffset );
    ft800_cmd( ctx, cfg, FT800_VERTEX2F( x2 * FT800_POINT_SIZE_SCALE, \
        y2 * FT800_POINT_SIZE_SCALE ), cmdOffset );
    ft800_cmd( ctx, cfg, FT800_END(), cmdOffset );
}

void ft800_cmd_text(ft800_t *ctx, ft800_cfg_t *cfg, uint16_t *cmdOffset, uint16_t x, \
    uint16_t y, uint16_t font, uint16_t options, char *s
) {
    ft800_cmd( ctx, cfg, FT800_CMD_TEXT, cmdOffset );
    ft800_cmd( ctx, cfg, ( y << FT800_OFFSET_COMMAND_PARAM_BYTES_2 ) | ( x & \
        FT800_COMMAND_MASK ), cmdOffset );
    ft800_cmd( ctx, cfg, ( options << FT800_OFFSET_COMMAND_PARAM_BYTES_2 ) | \
        ( font & FT800_COMMAND_MASK ), cmdOffset );

    while ( *s )
    {
        ft800_write_data( ctx, cfg, FT800_RAM_CMD + *cmdOffset, *s++, \
            FT800_DATA_LENGTH_BYTES_1 );
        ( *cmdOffset )++;
    }

    ft800_write_data( ctx, cfg, FT800_RAM_CMD + *cmdOffset, 0, \
        FT800_DATA_LENGTH_BYTES_1 );

    ( *cmdOffset )++;
    *cmdOffset = ( *cmdOffset + FT800_ALIGNMENT_ADDRESS ) & ~ \
        FT800_ALIGNMENT_ADDRESS;

    ft800_write_data( ctx, cfg, FT800_REG_CMD_WRITE, *cmdOffset, \
        FT800_DATA_LENGTH_BYTES_2 );
}

void ft800_cmd_number( ft800_t *ctx, ft800_cfg_t *cfg, uint16_t *cmdOffset, \
    uint16_t x, uint16_t y, uint16_t font, uint16_t options, int32_t num )
{
    ft800_cmd( ctx, cfg, FT800_CMD_NUMBER, cmdOffset );
    ft800_cmd( ctx, cfg, ( y << FT800_OFFSET_COMMAND_PARAM_BYTES_2 ) | ( x & \
        FT800_COMMAND_MASK ), cmdOffset );
    ft800_cmd( ctx, cfg, ( options << FT800_OFFSET_COMMAND_PARAM_BYTES_2 ) | \
        ( font & FT800_COMMAND_MASK ), cmdOffset );
    ft800_cmd( ctx, cfg, num, cmdOffset );

    ft800_write_data( ctx, cfg, FT800_RAM_CMD + *cmdOffset, 0, \
        FT800_DATA_LENGTH_BYTES_1 );

    ( *cmdOffset )++;
    *cmdOffset = ( *cmdOffset + FT800_ALIGNMENT_ADDRESS ) & ~ \
        FT800_ALIGNMENT_ADDRESS;

    ft800_write_data( ctx, cfg, FT800_REG_CMD_WRITE, *cmdOffset, \
        FT800_DATA_LENGTH_BYTES_2 );
}

void ft800_cmd_button( ft800_t *ctx, ft800_cfg_t *cfg, uint16_t *cmdOffset, \
    uint16_t x, uint16_t y, uint16_t w, uint16_t h, uint16_t font, \
    uint16_t options, const char *s )
{
    ft800_cmd( ctx, cfg, FT800_CMD_BUTTON, cmdOffset );
    ft800_cmd( ctx, cfg, ( y << FT800_OFFSET_COMMAND_PARAM_BYTES_2 ) | ( x & \
        FT800_COMMAND_MASK ), cmdOffset );
    ft800_cmd( ctx, cfg, ( h << FT800_OFFSET_COMMAND_PARAM_BYTES_2 ) | ( w & \
        FT800_COMMAND_MASK ), cmdOffset );
    ft800_cmd( ctx, cfg, ( options << FT800_OFFSET_COMMAND_PARAM_BYTES_2 ) | \
        ( font & FT800_COMMAND_MASK ), cmdOffset );

    while ( *s )
    {
        ft800_write_data( ctx, cfg, FT800_RAM_CMD + *cmdOffset, *s++, \
            FT800_DATA_LENGTH_BYTES_1 );
        ( *cmdOffset )++;
    }

    ft800_write_data( ctx, cfg, FT800_RAM_CMD + *cmdOffset, 0, \
        FT800_DATA_LENGTH_BYTES_1 );

    ( *cmdOffset )++;
    *cmdOffset = ( *cmdOffset + FT800_ALIGNMENT_ADDRESS ) & ~ \
        FT800_ALIGNMENT_ADDRESS;

    ft800_write_data( ctx, cfg, FT800_REG_CMD_WRITE, *cmdOffset, \
        FT800_DATA_LENGTH_BYTES_2 );
}

void ft800_cmd_clock( ft800_t *ctx, ft800_cfg_t *cfg, uint16_t *cmdOffset, uint16_t x,\
    uint16_t y, uint16_t r, uint16_t options, uint16_t h, uint16_t m, \
    uint16_t sec, uint16_t ms )
{
    ft800_cmd( ctx, cfg, FT800_CMD_CLOCK, cmdOffset );
    ft800_cmd( ctx, cfg, ( y << FT800_OFFSET_COMMAND_PARAM_BYTES_2 ) | ( x & \
        FT800_COMMAND_MASK ), cmdOffset );
    ft800_cmd( ctx, cfg, ( options << FT800_OFFSET_COMMAND_PARAM_BYTES_2 ) | \
        ( r & FT800_COMMAND_MASK ), cmdOffset );
    ft800_cmd( ctx, cfg, ( m << FT800_OFFSET_COMMAND_PARAM_BYTES_2 ) | \
        ( h & FT800_COMMAND_MASK ), cmdOffset );
    ft800_cmd( ctx, cfg, ( ms << FT800_OFFSET_COMMAND_PARAM_BYTES_2 ) | \
        ( sec & FT800_COMMAND_MASK ), cmdOffset );

    ft800_write_data( ctx, cfg, FT800_RAM_CMD + *cmdOffset, 0, \
        FT800_DATA_LENGTH_BYTES_1 );

    ( *cmdOffset )++;
    *cmdOffset = ( *cmdOffset + FT800_ALIGNMENT_ADDRESS ) & ~ \
        FT800_ALIGNMENT_ADDRESS;

    ft800_write_data( ctx,cfg, FT800_REG_CMD_WRITE,*cmdOffset, \
        FT800_DATA_LENGTH_BYTES_4 );
}

void ft800_cmd_gauge( ft800_t *ctx, ft800_cfg_t *cfg, uint16_t *cmdOffset, uint16_t x,\
    uint16_t y, uint16_t r, uint16_t options, uint16_t major, uint16_t minor, \
    uint16_t val, uint16_t range )
{
    ft800_cmd( ctx, cfg, FT800_CMD_GAUGE, cmdOffset );
    ft800_cmd( ctx, cfg, ( y << FT800_OFFSET_COMMAND_PARAM_BYTES_2 ) | ( x & \
        FT800_COMMAND_MASK ), cmdOffset );
    ft800_cmd( ctx, cfg, ( options << FT800_OFFSET_COMMAND_PARAM_BYTES_2 ) | \
        ( r & FT800_COMMAND_MASK ), cmdOffset );
    ft800_cmd( ctx, cfg, ( minor << FT800_OFFSET_COMMAND_PARAM_BYTES_2 ) | \
        ( major & FT800_COMMAND_MASK ), cmdOffset );
    ft800_cmd( ctx, cfg, ( range << FT800_OFFSET_COMMAND_PARAM_BYTES_2 ) | \
        ( val & FT800_COMMAND_MASK ), cmdOffset );

    ft800_write_data( ctx, cfg, FT800_RAM_CMD + *cmdOffset, 0, \
        FT800_DATA_LENGTH_BYTES_1 );

    ( *cmdOffset )++;
    *cmdOffset = ( *cmdOffset + FT800_ALIGNMENT_ADDRESS ) & ~ \
        FT800_ALIGNMENT_ADDRESS;

    ft800_write_data( ctx, cfg, FT800_REG_CMD_WRITE, *cmdOffset, \
        FT800_DATA_LENGTH_BYTES_4 );
}

void ft800_cmd_gradient( ft800_t *ctx, ft800_cfg_t *cfg, uint16_t *cmdOffset, \
    uint16_t x0, uint16_t y0, uint16_t x1, uint16_t y1, uint8_t r1, uint8_t g1, \
    uint8_t b1, uint8_t r2, uint8_t g2, uint8_t b2 )
{
    ft800_cmd( ctx, cfg, FT800_CMD_GRADIENT, cmdOffset );
    ft800_cmd( ctx, cfg, ( x0 << FT800_OFFSET_COMMAND_PARAM_BYTES_2 ) | y0, cmdOffset );
    ft800_cmd( ctx, cfg, FT800_COLOR_RGB( r1, g1, b1 ), cmdOffset );
    ft800_cmd( ctx, cfg, ( x1 << FT800_OFFSET_COMMAND_PARAM_BYTES_2 ) | y1, cmdOffset );
    ft800_cmd( ctx, cfg, FT800_COLOR_RGB( r2, g2, b2 ), cmdOffset );

    ft800_write_data( ctx,cfg, FT800_RAM_CMD + *cmdOffset, 0, \
        FT800_DATA_LENGTH_BYTES_1 );

    ( *cmdOffset )++;
    *cmdOffset = ( *cmdOffset + FT800_ALIGNMENT_ADDRESS ) & ~ FT800_ALIGNMENT_ADDRESS;

    ft800_write_data( ctx, cfg, FT800_REG_CMD_WRITE, *cmdOffset, \
        FT800_DATA_LENGTH_BYTES_2 );
}

void ft800_cmd_keys( ft800_t *ctx, ft800_cfg_t *cfg, uint16_t* cmdOffset, uint16_t x, \
    uint16_t y, uint16_t w, uint16_t h, uint16_t font, uint16_t options, \
    const char *s )
{
    ft800_cmd( ctx, cfg, FT800_CMD_KEYS, cmdOffset );
    ft800_cmd( ctx, cfg, ( y << FT800_OFFSET_COMMAND_PARAM_BYTES_2 ) | ( x & \
        FT800_COMMAND_MASK ), cmdOffset );
    ft800_cmd( ctx, cfg, ( h << FT800_OFFSET_COMMAND_PARAM_BYTES_2 ) | ( w & \
        FT800_COMMAND_MASK ), cmdOffset );
    ft800_cmd( ctx, cfg, ( options << FT800_OFFSET_COMMAND_PARAM_BYTES_2 ) | \
        ( font & FT800_COMMAND_MASK ), cmdOffset );

    while ( *s )
    {
        ft800_write_data( ctx, cfg, FT800_RAM_CMD + *cmdOffset, *s++, \
            FT800_DATA_LENGTH_BYTES_1 );
        ( *cmdOffset )++;
    }

    ft800_write_data( ctx, cfg, FT800_RAM_CMD + *cmdOffset, 0, \
        FT800_DATA_LENGTH_BYTES_1 );

    ( *cmdOffset )++;
    *cmdOffset = ( *cmdOffset + FT800_ALIGNMENT_ADDRESS ) & ~ \
        FT800_ALIGNMENT_ADDRESS;

    ft800_write_data( ctx, cfg, FT800_REG_CMD_WRITE, *cmdOffset, \
        FT800_DATA_LENGTH_BYTES_2 );
}

void ft800_cmd_progress( ft800_t *ctx, ft800_cfg_t *cfg, uint16_t *cmdOffset, \
    uint16_t x, uint16_t y, uint16_t w, uint16_t h, uint16_t options, \
    uint16_t val, uint16_t range )
{
    ft800_cmd( ctx, cfg, FT800_CMD_PROGRESS, cmdOffset );
    ft800_cmd( ctx, cfg, ( y << FT800_OFFSET_COMMAND_PARAM_BYTES_2 ) | \
        ( x & FT800_COMMAND_MASK ), cmdOffset );
    ft800_cmd( ctx, cfg, ( h << FT800_OFFSET_COMMAND_PARAM_BYTES_2 ) | \
        ( w & FT800_COMMAND_MASK ), cmdOffset );
    ft800_cmd( ctx, cfg, ( val << FT800_OFFSET_COMMAND_PARAM_BYTES_2 ) | \
        ( options & FT800_COMMAND_MASK ), cmdOffset );
    ft800_cmd( ctx, cfg, range, cmdOffset );

    ft800_write_data( ctx, cfg, FT800_RAM_CMD + *cmdOffset, 0, \
        FT800_DATA_LENGTH_BYTES_1 );

    ( *cmdOffset )++;
    *cmdOffset = ( *cmdOffset + FT800_ALIGNMENT_ADDRESS ) & ~ \
        FT800_ALIGNMENT_ADDRESS;

    ft800_write_data( ctx, cfg, FT800_REG_CMD_WRITE, *cmdOffset, \
        FT800_DATA_LENGTH_BYTES_2 );
}

void ft800_cmd_slider( ft800_t *ctx, ft800_cfg_t *cfg, uint16_t *cmdOffset, \
    uint16_t x, uint16_t y, uint16_t w, uint16_t h, uint16_t options, \
    uint16_t val, uint16_t range )
{
    ft800_cmd( ctx, cfg, FT800_CMD_SLIDER, cmdOffset );
    ft800_cmd( ctx, cfg, ( y << FT800_OFFSET_COMMAND_PARAM_BYTES_2 ) | \
        ( x & FT800_COMMAND_MASK ), cmdOffset );
    ft800_cmd( ctx, cfg, ( h << FT800_OFFSET_COMMAND_PARAM_BYTES_2 ) | \
        ( w & FT800_COMMAND_MASK ), cmdOffset );
    ft800_cmd( ctx, cfg, ( val << FT800_OFFSET_COMMAND_PARAM_BYTES_2 ) | \
        ( options & FT800_COMMAND_MASK ), cmdOffset );
    ft800_cmd( ctx, cfg, range, cmdOffset );

    ft800_write_data( ctx, cfg, FT800_RAM_CMD + *cmdOffset, 0, \
        FT800_DATA_LENGTH_BYTES_1 );

    ( *cmdOffset )++;
    *cmdOffset = ( *cmdOffset + FT800_ALIGNMENT_ADDRESS ) & ~ \
        FT800_ALIGNMENT_ADDRESS;

    ft800_write_data( ctx, cfg, FT800_REG_CMD_WRITE, *cmdOffset, \
        FT800_DATA_LENGTH_BYTES_2 );
}

void ft800_cmd_scrollbar( ft800_t *ctx, ft800_cfg_t *cfg, uint16_t *cmdOffset, \
    uint16_t x, uint16_t y, uint16_t w, uint16_t h, uint16_t options, \
    uint16_t val, uint16_t size, uint16_t range )
{
    ft800_cmd( ctx, cfg, FT800_CMD_SCROLLBAR, cmdOffset );
    ft800_cmd( ctx, cfg, ( y << FT800_OFFSET_COMMAND_PARAM_BYTES_2 ) | \
        ( x & FT800_COMMAND_MASK ), cmdOffset );
    ft800_cmd( ctx, cfg, ( h << FT800_OFFSET_COMMAND_PARAM_BYTES_2 ) | \
        ( w & FT800_COMMAND_MASK ), cmdOffset );
    ft800_cmd( ctx, cfg, ( val << FT800_OFFSET_COMMAND_PARAM_BYTES_2 ) | \
        ( options & FT800_COMMAND_MASK ), cmdOffset );
    ft800_cmd( ctx, cfg, ( range << FT800_OFFSET_COMMAND_PARAM_BYTES_2 ) | \
        ( size & FT800_COMMAND_MASK ), cmdOffset );

    ft800_write_data( ctx, cfg, FT800_RAM_CMD + *cmdOffset, 0, \
        FT800_DATA_LENGTH_BYTES_1 );

    ( *cmdOffset )++;
    *cmdOffset = ( *cmdOffset + FT800_ALIGNMENT_ADDRESS ) & ~ \
        FT800_ALIGNMENT_ADDRESS;

    ft800_write_data( ctx, cfg, FT800_REG_CMD_WRITE, *cmdOffset, \
        FT800_DATA_LENGTH_BYTES_4 );
}

void ft800_cmd_dial( ft800_t *ctx, ft800_cfg_t *cfg, uint16_t *cmdOffset, uint16_t x, \
    uint16_t y, uint16_t r, uint16_t options, uint16_t val )
{
    ft800_cmd( ctx, cfg, FT800_CMD_DIAL, cmdOffset );
    ft800_cmd( ctx, cfg, ( y << FT800_OFFSET_COMMAND_PARAM_BYTES_2 ) | \
        ( x & FT800_COMMAND_MASK ), cmdOffset );
    ft800_cmd( ctx, cfg, ( options << FT800_OFFSET_COMMAND_PARAM_BYTES_2 ) | \
        ( r & FT800_COMMAND_MASK ), cmdOffset );
    ft800_cmd( ctx, cfg, val, cmdOffset );

    ft800_write_data( ctx, cfg, FT800_RAM_CMD + *cmdOffset, 0, \
        FT800_DATA_LENGTH_BYTES_1 );

    ( *cmdOffset )++;
    *cmdOffset = ( *cmdOffset + FT800_ALIGNMENT_ADDRESS ) & ~ FT800_ALIGNMENT_ADDRESS;

    ft800_write_data( ctx, cfg, FT800_REG_CMD_WRITE, *cmdOffset, \
        FT800_DATA_LENGTH_BYTES_2 );
}

void ft800_cmd_toggle( ft800_t *ctx, ft800_cfg_t *cfg, uint16_t *cmdOffset, \
    uint16_t x, uint16_t y, uint16_t w, uint16_t font, uint16_t options, \
    uint16_t state, const char *s )
{
    ft800_cmd( ctx, cfg, FT800_CMD_TOGGLE, cmdOffset );
    ft800_cmd( ctx, cfg, ( y << FT800_OFFSET_COMMAND_PARAM_BYTES_2 ) | \
        ( x & FT800_COMMAND_MASK ), cmdOffset );
    ft800_cmd( ctx, cfg, ( font << FT800_OFFSET_COMMAND_PARAM_BYTES_2 ) | \
        ( w & FT800_COMMAND_MASK ), cmdOffset );
    ft800_cmd( ctx, cfg, ( state << FT800_OFFSET_COMMAND_PARAM_BYTES_2 ) | \
        ( options & FT800_COMMAND_MASK ), cmdOffset );

    while ( *s )
    {
        ft800_write_data( ctx, cfg, FT800_RAM_CMD + *cmdOffset, *s++, \
            FT800_DATA_LENGTH_BYTES_1 );
        ( *cmdOffset )++;
    }

    ft800_write_data( ctx, cfg, FT800_RAM_CMD + *cmdOffset, 0, \
        FT800_DATA_LENGTH_BYTES_1 );

    ( *cmdOffset )++;
    *cmdOffset = ( *cmdOffset + FT800_ALIGNMENT_ADDRESS ) & ~ \
        FT800_ALIGNMENT_ADDRESS;

    ft800_write_data( ctx, cfg, FT800_REG_CMD_WRITE, *cmdOffset, \
        FT800_DATA_LENGTH_BYTES_2 );
}

void ft800_cmd_track( ft800_t *ctx, ft800_cfg_t *cfg, uint16_t *cmdOffset, uint16_t x,\
    uint16_t y, uint16_t w, uint16_t h, uint16_t tag )
{
    ft800_cmd( ctx, cfg, FT800_CMD_TRACK, cmdOffset );
    ft800_cmd( ctx, cfg, ( y << FT800_OFFSET_COMMAND_PARAM_BYTES_2 ) | \
        ( x & FT800_COMMAND_MASK ), cmdOffset );
    ft800_cmd( ctx, cfg, ( h << FT800_OFFSET_COMMAND_PARAM_BYTES_2 ) | \
        ( w & FT800_COMMAND_MASK ), cmdOffset );
    ft800_cmd( ctx, cfg, tag, cmdOffset );
}

// ------------------------------------------------------------------------- END
