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

extern uint16_t cmdOffset;

void ft800_cmd( ft800_t *ctx, uint32_t command ) {
    // Send FT800 controller command to the next available RAM memory region.
    ft800_write_32_bits( ctx, FT800_RAM_CMD + cmdOffset, command );

    // Increment command offset by 4 bytes.
    cmdOffset += FT800_COMMAND_OFFSET;
}

void ft800_cmd_line( ft800_t *ctx, uint16_t x1, \
    uint16_t y1, uint16_t x2, uint16_t y2, uint16_t color, uint8_t width ) {
    // Decode color channel values from requested color.
    uint8_t red = ft800_rgb_convert( color, FT800_RGB_RED );
    uint8_t green = ft800_rgb_convert( color, FT800_RGB_GREEN );
    uint8_t blue = ft800_rgb_convert( color, FT800_RGB_BLUE );

    // Begin generating the line symbol.
    ft800_cmd( ctx, FT800_BEGIN( FT800_LINES ));
    // Set the width of the line.
    ft800_cmd( ctx, FT800_LINE_WIDTH( width ));
    // Set the color of the line.
    ft800_cmd( ctx, FT800_COLOR_RGB( red, green, blue ));

    // Draw the begining and the end points of the line symbol.
    ft800_cmd( ctx, FT800_VERTEX2F( x1, y1 ));
    ft800_cmd( ctx, FT800_VERTEX2F( x2, y2 ));

    // Finish generating the line symbol.
    ft800_cmd( ctx, FT800_END() );
}

void ft800_cmd_text( ft800_t *ctx, uint16_t x, uint16_t y, uint16_t font, \
    uint16_t options, char *s ) {
    // Begin generating the text symbol.
    ft800_cmd( ctx, FT800_CMD_TEXT );
    // Set the start coordinates for the text symbol.
    ft800_cmd( ctx, FT800_CREATE_CMD( y, x ));
    // Set the font and options for the text symbol.
    ft800_cmd( ctx, FT800_CREATE_CMD( options, font ));

    // Draw each character of the text symbol.
    while ( *s )
    {
        ft800_write_8_bits( ctx, FT800_RAM_CMD + cmdOffset, *s++ );
        cmdOffset++;
    }

    // Write dummy bytes of data until the whole 4 byte command word is completed.
    while ( cmdOffset % FT800_COMMAND_OFFSET )
    {
        ft800_write_8_bits( ctx, FT800_RAM_CMD + cmdOffset, 0 );
        cmdOffset++;
    }
}

void ft800_cmd_number( ft800_t *ctx, uint16_t x, uint16_t y, uint16_t font, \
    uint16_t options, int32_t num ) {
    // Begin generating the number symbol.
    ft800_cmd( ctx, FT800_CMD_NUMBER );
    // Set the start coordinates for the number symbol.
    ft800_cmd( ctx, FT800_CREATE_CMD( y, x ));
    // Set the font and options for the number symbol.
    ft800_cmd( ctx, FT800_CREATE_CMD( options, font ));
    // Draw the number symbol.
    ft800_cmd( ctx, num );
}

void ft800_cmd_button( ft800_t *ctx, uint16_t x, uint16_t y, uint16_t w, \
    uint16_t h, uint16_t font, uint16_t options, const char *s ) {
    // Begin generating the button symbol.
    ft800_cmd( ctx, FT800_CMD_BUTTON );
    // Set the start coordinates for the button symbol.
    ft800_cmd( ctx, FT800_CREATE_CMD( y, x ));
    // Set the height and width for the button symbol.
    ft800_cmd( ctx, FT800_CREATE_CMD( h, w ));
    // Set the font and options for the button symbol.
    ft800_cmd( ctx, FT800_CREATE_CMD( options, font ));

    // Draw each character of the button symbol.
    while ( *s )
    {
        ft800_write_8_bits( ctx, FT800_RAM_CMD + cmdOffset, *s++ );
        cmdOffset++;
    }

    // Write dummy bytes of data until the whole 4 byte command word is completed.
    while ( cmdOffset % FT800_COMMAND_OFFSET )
    {
        ft800_write_8_bits( ctx, FT800_RAM_CMD + cmdOffset, 0 );
        cmdOffset++;
    }
}

void ft800_cmd_clock( ft800_t *ctx, uint16_t x, uint16_t y, uint16_t r, \
    uint16_t options, uint16_t h, uint16_t m, uint16_t sec, uint16_t ms ) {
    // Begin generating the clock symbol.
    ft800_cmd( ctx, FT800_CMD_CLOCK );
    // Set the start coordinates for the clock symbol.
    ft800_cmd( ctx, FT800_CREATE_CMD( y, x ));
    // Set the radius and options for the clock symbol.
    ft800_cmd( ctx, FT800_CREATE_CMD( options, r ));
    // Set minutes and hours for the clock symbol.
    ft800_cmd( ctx, FT800_CREATE_CMD( m, h ));
    // Set milliseconds and seconds for the clock symbol.
    ft800_cmd( ctx, FT800_CREATE_CMD( ms, sec ));
}

void ft800_cmd_gauge( ft800_t *ctx, uint16_t x, uint16_t y, uint16_t r, \
    uint16_t options, uint16_t major, uint16_t minor, uint16_t val, uint16_t range ) {
    // Begin generating the gauge symbol.
    ft800_cmd( ctx, FT800_CMD_GAUGE );
    // Set the start coordinates for the gauge symbol.
    ft800_cmd( ctx, FT800_CREATE_CMD( y, x ));
    // Set the radius and options for the gauge symbol.
    ft800_cmd( ctx, FT800_CREATE_CMD( options, r ));
    // Set the number of major and minor subdivisions for the gauge symbol.
    ft800_cmd( ctx, FT800_CREATE_CMD( minor, major ));
    // Set the indicated and maximum value for the gauge symbol.
    ft800_cmd( ctx, FT800_CREATE_CMD( range, val ));
}

void ft800_cmd_gradient( ft800_t *ctx, uint16_t x0, uint16_t y0, uint16_t x1, \
    uint16_t y1, uint8_t r1, uint8_t g1, uint8_t b1, uint8_t r2, uint8_t g2, uint8_t b2 ) {
    // Begin generating the gradient.
    ft800_cmd( ctx, FT800_CMD_GRADIENT );
    // Set the start coordinates for the gradient.
    ft800_cmd( ctx, FT800_CREATE_CMD( x0, y0 ));
    // Set the start color for the gradient.
    ft800_cmd( ctx, FT800_COLOR_RGB( r1, g1, b1 ));
    // Set the end coordinates for the gradient.
    ft800_cmd( ctx, FT800_CREATE_CMD( x1, y1 ));
    // Set the end color for the gradient.
    ft800_cmd( ctx, FT800_COLOR_RGB( r2, g2, b2 ));
}

void ft800_cmd_keys( ft800_t *ctx, uint16_t x, uint16_t y, uint16_t w, \
    uint16_t h, uint16_t font, uint16_t options, const char *s ) {
    // Begin generating the key symbols.
    ft800_cmd( ctx, FT800_CMD_KEYS );
    // Set the start coordinates for the key symbols.
    ft800_cmd( ctx, FT800_CREATE_CMD( y, x ));
    // Set the height and width for the key symbols.
    ft800_cmd( ctx, FT800_CREATE_CMD( h, w ));
    // Set the font and options for the key symbols.
    ft800_cmd( ctx, FT800_CREATE_CMD( options, font ));

    // Draw each key of the key symbols.
    while ( *s )
    {
        ft800_write_8_bits( ctx, FT800_RAM_CMD + cmdOffset, *s++ );
        cmdOffset++;
    }

    // Write dummy bytes of data until the whole 4 byte command word is completed.
    while ( cmdOffset % FT800_COMMAND_OFFSET )
    {
        ft800_write_8_bits( ctx, FT800_RAM_CMD + cmdOffset, 0 );
        cmdOffset++;
    }
}

void ft800_cmd_progress( ft800_t *ctx, uint16_t x, uint16_t y, uint16_t w, \
    uint16_t h, uint16_t options, uint16_t val, uint16_t range ) {
    // Begin generating the progress bar symbol.
    ft800_cmd( ctx, FT800_CMD_PROGRESS );
    // Set the start coordinates for the progress bar symbol.
    ft800_cmd( ctx, FT800_CREATE_CMD( y, x ));
    // Set the height and width for the progress bar symbol.
    ft800_cmd( ctx, FT800_CREATE_CMD( h, w ));
    // Set the position and options for the progress bar symbol.
    ft800_cmd( ctx, FT800_CREATE_CMD( val, options ));
    // Set the maximum range of the progress bar symbol.
    ft800_cmd( ctx, FT800_CREATE_CMD( range, 0 ));
}

void ft800_cmd_slider( ft800_t *ctx, uint16_t x, uint16_t y, uint16_t w, \
    uint16_t h, uint16_t options, uint16_t val, uint16_t range ) {
    // Begin generating the slider symbol.
    ft800_cmd( ctx, FT800_CMD_SLIDER );
    // Set the start coordinates for the slider symbol.
    ft800_cmd( ctx, FT800_CREATE_CMD( y, x ));
    // Set the height and width for the slider symbol.
    ft800_cmd( ctx, FT800_CREATE_CMD( h, w ));
    // Set the position and options for the slider symbol.
    ft800_cmd( ctx, FT800_CREATE_CMD( val, options ));
    // Set the maximum range for the slider symbol.
    ft800_cmd( ctx, FT800_CREATE_CMD( range, 0 ));
}

void ft800_cmd_scrollbar( ft800_t *ctx, uint16_t x, uint16_t y, uint16_t w, \
    uint16_t h, uint16_t options, uint16_t val, uint16_t size, uint16_t range ) {
    // Begin generating the scrollbar symbol.
    ft800_cmd( ctx, FT800_CMD_SCROLLBAR );
    // Set the start coordinates for the scrollbar symbol.
    ft800_cmd( ctx, FT800_CREATE_CMD( y, x ));
    // Set the height and width for the scrollbar symbol.
    ft800_cmd( ctx, FT800_CREATE_CMD( h, w ));
    // Set the position and options for the scrollbar symbol.
    ft800_cmd( ctx, FT800_CREATE_CMD( val, options ));
    // Set the maximum range and size for the scrollbar symbol.
    ft800_cmd( ctx, FT800_CREATE_CMD( range, size ));
}

void ft800_cmd_dial( ft800_t *ctx, uint16_t x, uint16_t y, uint16_t r,
    uint16_t options, uint16_t val ) {
    // Begin generating the dial symbol.
    ft800_cmd( ctx, FT800_CMD_DIAL );
    // Set the start coordinates for the dial symbol.
    ft800_cmd( ctx, FT800_CREATE_CMD( y, x ));
    // Set the radius and options for the dial symbol.
    ft800_cmd( ctx, FT800_CREATE_CMD( options, r ));
    // Set the position for the dial symbol.
    ft800_cmd( ctx, FT800_CREATE_CMD( val, 0 ));
}

void ft800_cmd_toggle( ft800_t *ctx, uint16_t x, uint16_t y, uint16_t w, \
    uint16_t font, uint16_t options, uint16_t state, const char *s ) {
    ft800_cmd( ctx, FT800_CMD_TOGGLE );
    ft800_cmd( ctx, ( y << FT800_OFFSET_COMMAND_PARAM_BYTES_2 ) | \
        ( x & FT800_COMMAND_MASK ));
    ft800_cmd( ctx, ( font << FT800_OFFSET_COMMAND_PARAM_BYTES_2 ) | \
        ( w & FT800_COMMAND_MASK ));
    ft800_cmd( ctx, ( state << FT800_OFFSET_COMMAND_PARAM_BYTES_2 ) | \
        ( options & FT800_COMMAND_MASK ));

    while ( *s )
    {
        ft800_write_8_bits( ctx, FT800_RAM_CMD + cmdOffset, *s++ );
        cmdOffset++;
    }

    ft800_write_8_bits( ctx, FT800_RAM_CMD + cmdOffset, 0 );

    cmdOffset++;
    cmdOffset = ( cmdOffset + FT800_ALIGNMENT_ADDRESS ) & ~FT800_ALIGNMENT_ADDRESS;

    ft800_write_16_bits( ctx, FT800_REG_CMD_WRITE, cmdOffset );
}

void ft800_cmd_track( ft800_t *ctx, uint16_t x, uint16_t y, uint16_t w, uint16_t h, uint16_t tag ) {
    ft800_cmd( ctx, FT800_CMD_TRACK );
    ft800_cmd( ctx, ( y << FT800_OFFSET_COMMAND_PARAM_BYTES_2 ) | ( x & FT800_COMMAND_MASK ));
    ft800_cmd( ctx, ( h << FT800_OFFSET_COMMAND_PARAM_BYTES_2 ) | ( w & FT800_COMMAND_MASK ));
    ft800_cmd( ctx, tag );
}

// ------------------------------------------------------------------------- END
