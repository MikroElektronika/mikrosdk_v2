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


void cmd( ft800_t *ctx, ft800_cfg_t *cfg, uint32_t command, uint16_t *cmdOffset )
{
    ft800_write_data( ctx, cfg, FT800_RAM_CMD + *cmdOffset, command, \
    FT800_DATA_LENGTH_BYTES_4 );
    *cmdOffset += FT800_COMMAND_OFFSET;
    ft800_write_data( ctx, cfg, FT800_REG_CMD_WRITE, *cmdOffset, \
    FT800_DATA_LENGTH_BYTES_2 );
}

void cmd_text(
    ft800_t *ctx, ft800_cfg_t *cfg, uint16_t *cmdOffset, uint16_t x, \
    uint16_t y, uint16_t font, uint16_t options, const char *s
) {
    cmd( ctx, cfg, FT800_CMD_TEXT, cmdOffset );
    cmd( ctx, cfg, ( y << FT800_OFFSET_COMMAND_PARAM_BYTES_2 ) | ( x & \
    FT800_COMMAND_MASK ), cmdOffset );
    cmd( ctx, cfg, ( options << FT800_OFFSET_COMMAND_PARAM_BYTES_2 ) | \
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
    *cmdOffset = ( *cmdOffset + FT800_ALIGMENT_ADDRESS ) & ~ \
    FT800_ALIGMENT_ADDRESS;

    ft800_write_data( ctx, cfg, FT800_REG_CMD_WRITE, *cmdOffset, \
    FT800_DATA_LENGTH_BYTES_2 );
}

void cmd_number( ft800_t *ctx, ft800_cfg_t *cfg, uint16_t *cmdOffset, \
     uint16_t x, uint16_t y, uint16_t font, uint16_t options, int32_t num )
{
    cmd( ctx, cfg, FT800_CMD_NUMBER, cmdOffset );
    cmd( ctx, cfg, ( y << FT800_OFFSET_COMMAND_PARAM_BYTES_2 ) | ( x & \
    FT800_COMMAND_MASK ), cmdOffset );
    cmd( ctx, cfg, ( options << FT800_OFFSET_COMMAND_PARAM_BYTES_2 ) | \
    ( font & FT800_COMMAND_MASK ), cmdOffset );
    cmd( ctx, cfg, num, cmdOffset );

    ft800_write_data( ctx, cfg, FT800_RAM_CMD + *cmdOffset, 0, \
    FT800_DATA_LENGTH_BYTES_1 );

    ( *cmdOffset )++;
    *cmdOffset = ( *cmdOffset + FT800_ALIGMENT_ADDRESS ) & ~ \
    FT800_ALIGMENT_ADDRESS;

    ft800_write_data( ctx, cfg, FT800_REG_CMD_WRITE, *cmdOffset, \
    FT800_DATA_LENGTH_BYTES_2 );
}

void cmd_button( ft800_t *ctx, ft800_cfg_t *cfg, uint16_t *cmdOffset, \
     uint16_t x, uint16_t y, uint16_t w, uint16_t h, uint16_t font, \
     uint16_t options, const char *s )
{
    cmd( ctx, cfg, FT800_CMD_BUTTON, cmdOffset );
    cmd( ctx, cfg, ( y << FT800_OFFSET_COMMAND_PARAM_BYTES_2 ) | ( x & \
    FT800_COMMAND_MASK ), cmdOffset );
    cmd( ctx, cfg, ( h << FT800_OFFSET_COMMAND_PARAM_BYTES_2 ) | ( w & \
    FT800_COMMAND_MASK ), cmdOffset );
    cmd( ctx, cfg, ( options << FT800_OFFSET_COMMAND_PARAM_BYTES_2 ) | \
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
    *cmdOffset = ( *cmdOffset + FT800_ALIGMENT_ADDRESS ) & ~ \
    FT800_ALIGMENT_ADDRESS;

    ft800_write_data( ctx, cfg, FT800_REG_CMD_WRITE, *cmdOffset, \
    FT800_DATA_LENGTH_BYTES_2 );
}

void cmd_clock( ft800_t *ctx, ft800_cfg_t *cfg, uint16_t *cmdOffset, uint16_t x,\
     uint16_t y, uint16_t r, uint16_t options, uint16_t h, uint16_t m, \
     uint16_t sec, uint16_t ms )
{
    cmd( ctx, cfg, FT800_CMD_CLOCK, cmdOffset );
    cmd( ctx, cfg, ( y << FT800_OFFSET_COMMAND_PARAM_BYTES_2 ) | ( x & \
    FT800_COMMAND_MASK ), cmdOffset );
    cmd( ctx, cfg, ( options << FT800_OFFSET_COMMAND_PARAM_BYTES_2 ) | \
    ( r & FT800_COMMAND_MASK ), cmdOffset );
    cmd( ctx, cfg, ( m << FT800_OFFSET_COMMAND_PARAM_BYTES_2 ) | \
    ( h & FT800_COMMAND_MASK ), cmdOffset );
    cmd( ctx, cfg, ( ms << FT800_OFFSET_COMMAND_PARAM_BYTES_2 ) | \
    ( sec & FT800_COMMAND_MASK ), cmdOffset );

    ft800_write_data( ctx, cfg, FT800_RAM_CMD + *cmdOffset, 0, \
    FT800_DATA_LENGTH_BYTES_1 );

    ( *cmdOffset )++;
    *cmdOffset = ( *cmdOffset + FT800_ALIGMENT_ADDRESS ) & ~ \
    FT800_ALIGMENT_ADDRESS;

    ft800_write_data( ctx,cfg, FT800_REG_CMD_WRITE,*cmdOffset, \
    FT800_DATA_LENGTH_BYTES_4 );
}

void cmd_gauge( ft800_t *ctx, ft800_cfg_t *cfg, uint16_t *cmdOffset, uint16_t x,\
     uint16_t y, uint16_t r, uint16_t options, uint16_t major, uint16_t minor, \
     uint16_t val, uint16_t range )
{
    cmd( ctx, cfg, FT800_CMD_GAUGE, cmdOffset );
    cmd( ctx, cfg, ( y << FT800_OFFSET_COMMAND_PARAM_BYTES_2 ) | ( x & \
    FT800_COMMAND_MASK ), cmdOffset );
    cmd( ctx, cfg, ( options << FT800_OFFSET_COMMAND_PARAM_BYTES_2 ) | \
    ( r & FT800_COMMAND_MASK ), cmdOffset );
    cmd( ctx, cfg, ( minor << FT800_OFFSET_COMMAND_PARAM_BYTES_2 ) | \
    ( major & FT800_COMMAND_MASK ), cmdOffset );
    cmd( ctx, cfg, ( range << FT800_OFFSET_COMMAND_PARAM_BYTES_2 ) | \
    ( val & FT800_COMMAND_MASK ), cmdOffset );

    ft800_write_data( ctx, cfg, FT800_RAM_CMD + *cmdOffset, 0, \
    FT800_DATA_LENGTH_BYTES_1 );

    ( *cmdOffset )++;
    *cmdOffset = ( *cmdOffset + FT800_ALIGMENT_ADDRESS ) & ~ \
    FT800_ALIGMENT_ADDRESS;

    ft800_write_data( ctx, cfg, FT800_REG_CMD_WRITE, *cmdOffset, \
    FT800_DATA_LENGTH_BYTES_4 );
}

void cmd_gradient( ft800_t *ctx, ft800_cfg_t *cfg, uint16_t *cmdOffset, \
     uint16_t x0, uint16_t y0, uint16_t x1, uint16_t y1, uint8_t r1, uint8_t g1, \
     uint8_t b1, uint8_t r2, uint8_t g2, uint8_t b2 )
{
    cmd( ctx, cfg, FT800_CMD_GRADIENT, cmdOffset );
    cmd( ctx, cfg, ( x0 << FT800_OFFSET_COMMAND_PARAM_BYTES_2 ) | y0, cmdOffset );
    cmd( ctx, cfg, FT800_COLOR_RGB( r1, g1, b1 ), cmdOffset );
    cmd( ctx, cfg, ( x1 << FT800_OFFSET_COMMAND_PARAM_BYTES_2 ) | y1, cmdOffset );
    cmd( ctx, cfg, FT800_COLOR_RGB( r2, g2, b2 ), cmdOffset );

    ft800_write_data( ctx,cfg, FT800_RAM_CMD + *cmdOffset, 0, \
    FT800_DATA_LENGTH_BYTES_1 );

    ( *cmdOffset )++;
    *cmdOffset = ( *cmdOffset + FT800_ALIGMENT_ADDRESS ) & ~ FT800_ALIGMENT_ADDRESS;

    ft800_write_data( ctx, cfg, FT800_REG_CMD_WRITE, *cmdOffset, \
    FT800_DATA_LENGTH_BYTES_2 );
}

void cmd_keys( ft800_t *ctx, ft800_cfg_t *cfg, uint16_t* cmdOffset, uint16_t x, \
     uint16_t y, uint16_t w, uint16_t h, uint16_t font, uint16_t options, \
     const char *s )
{
    cmd( ctx, cfg, FT800_CMD_KEYS, cmdOffset );
    cmd( ctx, cfg, ( y << FT800_OFFSET_COMMAND_PARAM_BYTES_2 ) | ( x & \
    FT800_COMMAND_MASK ), cmdOffset );
    cmd( ctx, cfg, ( h << FT800_OFFSET_COMMAND_PARAM_BYTES_2 ) | ( w & \
    FT800_COMMAND_MASK ), cmdOffset );
    cmd( ctx, cfg, ( options << FT800_OFFSET_COMMAND_PARAM_BYTES_2 ) | \
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
    *cmdOffset = ( *cmdOffset + FT800_ALIGMENT_ADDRESS ) & ~ \
    FT800_ALIGMENT_ADDRESS;

    ft800_write_data( ctx, cfg, FT800_REG_CMD_WRITE, *cmdOffset, \
    FT800_DATA_LENGTH_BYTES_2 );
}

void cmd_progress( ft800_t *ctx, ft800_cfg_t *cfg, uint16_t *cmdOffset, \
     uint16_t x, uint16_t y, uint16_t w, uint16_t h, uint16_t options, \
     uint16_t val, uint16_t range )
{
    cmd( ctx, cfg, FT800_CMD_PROGRESS, cmdOffset );
    cmd( ctx, cfg, ( y << FT800_OFFSET_COMMAND_PARAM_BYTES_2 ) | \
    ( x & FT800_COMMAND_MASK ), cmdOffset );
    cmd( ctx, cfg, ( h << FT800_OFFSET_COMMAND_PARAM_BYTES_2 ) | \
    ( w & FT800_COMMAND_MASK ), cmdOffset );
    cmd( ctx, cfg, ( val << FT800_OFFSET_COMMAND_PARAM_BYTES_2 ) | \
    ( options & FT800_COMMAND_MASK ), cmdOffset );
    cmd( ctx, cfg, range, cmdOffset );

    ft800_write_data( ctx, cfg, FT800_RAM_CMD + *cmdOffset, 0, \
    FT800_DATA_LENGTH_BYTES_1 );

    ( *cmdOffset )++;
    *cmdOffset = ( *cmdOffset + FT800_ALIGMENT_ADDRESS ) & ~ \
    FT800_ALIGMENT_ADDRESS;

    ft800_write_data( ctx, cfg, FT800_REG_CMD_WRITE, *cmdOffset, \
    FT800_DATA_LENGTH_BYTES_2 );
}

void cmd_slider( ft800_t *ctx, ft800_cfg_t *cfg, uint16_t *cmdOffset, \
     uint16_t x, uint16_t y, uint16_t w, uint16_t h, uint16_t options, \
     uint16_t val, uint16_t range )
{
    cmd( ctx, cfg, FT800_CMD_SLIDER, cmdOffset );
    cmd( ctx, cfg, ( y << FT800_OFFSET_COMMAND_PARAM_BYTES_2 ) | \
    ( x & FT800_COMMAND_MASK ), cmdOffset );
    cmd( ctx, cfg, ( h << FT800_OFFSET_COMMAND_PARAM_BYTES_2 ) | \
    ( w & FT800_COMMAND_MASK ), cmdOffset );
    cmd( ctx, cfg, ( val << FT800_OFFSET_COMMAND_PARAM_BYTES_2 ) | \
    ( options & FT800_COMMAND_MASK ), cmdOffset );
    cmd( ctx, cfg, range, cmdOffset );

    ft800_write_data( ctx, cfg, FT800_RAM_CMD + *cmdOffset, 0, \
    FT800_DATA_LENGTH_BYTES_1 );

    ( *cmdOffset )++;
    *cmdOffset = ( *cmdOffset + FT800_ALIGMENT_ADDRESS ) & ~ \
    FT800_ALIGMENT_ADDRESS;

    ft800_write_data( ctx, cfg, FT800_REG_CMD_WRITE, *cmdOffset, \
    FT800_DATA_LENGTH_BYTES_2 );
}

void cmd_scrollbar( ft800_t *ctx, ft800_cfg_t *cfg, uint16_t *cmdOffset, \
     uint16_t x, uint16_t y, uint16_t w, uint16_t h, uint16_t options, \
     uint16_t val, uint16_t size, uint16_t range )
{
    cmd( ctx, cfg, FT800_CMD_SCROLLBAR, cmdOffset );
    cmd( ctx, cfg, ( y << FT800_OFFSET_COMMAND_PARAM_BYTES_2 ) | \
    ( x & FT800_COMMAND_MASK ), cmdOffset );
    cmd( ctx, cfg, ( h << FT800_OFFSET_COMMAND_PARAM_BYTES_2 ) | \
    ( w & FT800_COMMAND_MASK ), cmdOffset );
    cmd( ctx, cfg, ( val << FT800_OFFSET_COMMAND_PARAM_BYTES_2 ) | \
    ( options & FT800_COMMAND_MASK ), cmdOffset );
    cmd( ctx, cfg, ( range << FT800_OFFSET_COMMAND_PARAM_BYTES_2 ) | \
    ( size & FT800_COMMAND_MASK ), cmdOffset );

    ft800_write_data( ctx, cfg, FT800_RAM_CMD + *cmdOffset, 0, \
    FT800_DATA_LENGTH_BYTES_1 );

    ( *cmdOffset )++;
    *cmdOffset = ( *cmdOffset + FT800_ALIGMENT_ADDRESS ) & ~ \
    FT800_ALIGMENT_ADDRESS;

    ft800_write_data( ctx, cfg, FT800_REG_CMD_WRITE, *cmdOffset, \
    FT800_DATA_LENGTH_BYTES_4 );
}

void cmd_dial( ft800_t *ctx, ft800_cfg_t *cfg, uint16_t *cmdOffset, uint16_t x, \
     uint16_t y, uint16_t r, uint16_t options, uint16_t val )
{
    cmd( ctx, cfg, FT800_CMD_DIAL, cmdOffset );
    cmd( ctx, cfg, ( y << FT800_OFFSET_COMMAND_PARAM_BYTES_2 ) | \
    ( x & FT800_COMMAND_MASK ), cmdOffset );
    cmd( ctx, cfg, ( options << FT800_OFFSET_COMMAND_PARAM_BYTES_2 ) | \
    ( r & FT800_COMMAND_MASK ), cmdOffset );
    cmd( ctx, cfg, val, cmdOffset );

    ft800_write_data( ctx, cfg, FT800_RAM_CMD + *cmdOffset, 0, \
    FT800_DATA_LENGTH_BYTES_1 );

    ( *cmdOffset )++;
    *cmdOffset = ( *cmdOffset + FT800_ALIGMENT_ADDRESS ) & ~ FT800_ALIGMENT_ADDRESS;

    ft800_write_data( ctx, cfg, FT800_REG_CMD_WRITE, *cmdOffset, \
    FT800_DATA_LENGTH_BYTES_2 );
}

void cmd_toggle( ft800_t *ctx, ft800_cfg_t *cfg, uint16_t *cmdOffset, \
     uint16_t x, uint16_t y, uint16_t w, uint16_t font, uint16_t options, \
     uint16_t state, const char *s )
{
    cmd( ctx, cfg, FT800_CMD_TOGGLE, cmdOffset );
    cmd( ctx, cfg, ( y << FT800_OFFSET_COMMAND_PARAM_BYTES_2 ) | \
    ( x & FT800_COMMAND_MASK ), cmdOffset );
    cmd( ctx, cfg, ( font << FT800_OFFSET_COMMAND_PARAM_BYTES_2 ) | \
    ( w & FT800_COMMAND_MASK ), cmdOffset );
    cmd( ctx, cfg, ( state << FT800_OFFSET_COMMAND_PARAM_BYTES_2 ) | \
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
    *cmdOffset = ( *cmdOffset + FT800_ALIGMENT_ADDRESS ) & ~ \
    FT800_ALIGMENT_ADDRESS;

    ft800_write_data( ctx, cfg, FT800_REG_CMD_WRITE, *cmdOffset, \
    FT800_DATA_LENGTH_BYTES_2 );
}

void cmd_track( ft800_t *ctx, ft800_cfg_t *cfg, uint16_t *cmdOffset, uint16_t x,\
     uint16_t y, uint16_t w, uint16_t h, uint16_t tag )
{
    cmd( ctx, cfg, FT800_CMD_TRACK, cmdOffset );
    cmd( ctx, cfg, ( y << FT800_OFFSET_COMMAND_PARAM_BYTES_2 ) | \
    ( x & FT800_COMMAND_MASK ), cmdOffset );
    cmd( ctx, cfg, ( h << FT800_OFFSET_COMMAND_PARAM_BYTES_2 ) | \
    ( w & FT800_COMMAND_MASK ), cmdOffset );
    cmd( ctx, cfg, tag, cmdOffset );
}

// ------------------------------------------------------------------------- END
