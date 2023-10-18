/****************************************************************************
**
** Copyright (C) 2023 MikroElektronika d.o.o.
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

#include "gl_text.h"
#include "gl_utils.h"
#include <stdlib.h>
#include <stdbool.h>

extern gl_t instance;

static gl_int_t _saturate(gl_int_t value, gl_int_t min, gl_int_t max)
{
    if (value < min)
        return min;
    return value > max ? max : value;
}

// static uint16_t _font_first_char(const uint8_t *font_data_array);
static uint16_t _font_first_char()
{
    return instance.font.data_array[2] /*| ((uint16_t)instance.font[3] << 8)*/;
}

static uint16_t _font_last_char()
{
    return instance.font.data_array[4] /*| ((uint16_t)instance.font[5] << 8)*/;
}

static uint16_t _font_height()
{
    return instance.font.data_array[6];
}

static uint8_t _font_width(uint16_t ch)
{
    const char *ch_table;
    ch_table = instance.font.data_array + 8 + (((uint32_t)ch - (uint32_t)_font_first_char()) << 2);
    return ch_table[0];
}

static char _font_width_max()
{
    return _font_width('W') + 1;
}

static uint32_t _font_offset(uint16_t ch)
{
    const char *ch_table;
    ch_table = instance.font.data_array + 8 + (((uint32_t)ch - (uint32_t)_font_first_char()) << 2);
    return (uint32_t)ch_table[1] | ((uint32_t)ch_table[2] << 8) | ((uint32_t)ch_table[3] << 16);
}

static void _draw_char_hor_crop(char ch, gl_int_t x, gl_int_t y)
{
    gl_rectangle_t _rect;
    bool no_skip;
    gl_int_t ch_width = _font_width(ch);
    gl_int_t ch_height = _font_height();
    gl_int_t x_offset = 0;
    gl_int_t y_offset = 0;
    uint8_t mask = 0;
    const uint8_t *ch_bitmap;

    if (!instance.font.data_array)
        return;

    _rect.width  = 1;
    _rect.height = 1;

    if (  ((x + ch_width) < instance.crop_rect.left) || (x > instance.crop_rect.right)
       || ((y + ch_height) < instance.crop_rect.top) || (y > instance.crop_rect.bottom))
        return;

    ch_bitmap = instance.font.data_array + _font_offset(ch);
    for (y_offset = 0; y_offset < ch_height; y_offset++)
    {
        mask = 0x01;
        _rect.top_left.y = y + y_offset;
        no_skip = (_rect.top_left.y > instance.crop_rect.top) && (_rect.top_left.y < instance.crop_rect.bottom);
        for (x_offset = 0; x_offset < ch_width;)
        {
            if (((x_offset + x) > instance.crop_rect.left) && ((x_offset + x) < instance.crop_rect.right) && no_skip)
            {
                if (mask & (*ch_bitmap))
                {
                    _rect.top_left.x = x + x_offset;
                    instance.driver.fill_f(&_rect, instance.pen.color);
                }
                else if (instance.font.background_on)
                {
                    _rect.top_left.x = x + x_offset;
                    instance.driver.fill_f(&_rect, instance.font.background_color);
                }
            }
            mask <<= 1;
            x_offset++;

            if (mask == 0)
            {
                ch_bitmap++;
                mask = 0x01;
            }
        }

        if (mask != 0x01)
            ch_bitmap++;
        y_offset++;
    }
}

static void _draw_char_ver_crop(char ch, gl_int_t x, gl_int_t y)
{
    gl_rectangle_t _rect;
    bool no_skip;
    uint8_t ch_width = _font_width(ch);
    uint8_t ch_height = _font_height();
    uint8_t x_offset = 0;
    uint8_t y_offset = 0;
    uint8_t mask = 0;
    const char *ch_bitmap;

    if (!instance.font.data_array)
        return;

    _rect.width  = 1;
    _rect.height = 1;

    if (  ((x + ch_width) < instance.crop_rect.left) || (x > instance.crop_rect.right)
       || ((y + ch_height) < instance.crop_rect.top) || (y > instance.crop_rect.bottom))
        return;

    ch_bitmap = instance.font.data_array +  _font_offset(ch);
    for (y_offset = 0; y_offset < ch_height;)
    {
        mask = 0x01;
        _rect.top_left.x = x + y_offset;
        no_skip = _rect.top_left.x > instance.crop_rect.left && _rect.top_left.x < instance.crop_rect.right;

        for (x_offset = 0; x_offset < ch_width;)
        {
            if (y - x_offset > instance.crop_rect.top && y - x_offset < instance.crop_rect.bottom && no_skip)
            {
                if (mask & *ch_bitmap)
                {
                    _rect.top_left.y = y - x_offset;
                    instance.driver.fill_f(&_rect, instance.pen.color);
                }
                else if (instance.font.background_on)
                {
                    _rect.top_left.y = y - x_offset;
                    instance.driver.fill_f(&_rect, instance.font.background_color);
                }
            }
            mask <<= 1;
            x_offset++;

            if (mask == 0)
            {
                ch_bitmap++;
                mask = 0x01;
            }
        }
        if(mask != 0x01)
            ch_bitmap++;
        y_offset++;
    }
}

static void _draw_char_hor(char ch, gl_int_t x, gl_int_t y)
{
    gl_rectangle_t _rect;
    gl_int_t ch_width = _font_width(ch);
    gl_int_t ch_height = _font_height();
    uint32_t offset = _font_offset(ch);
    gl_int_t x_offset = 0;
    gl_int_t y_offset = 0;
    uint8_t mask = 0;
    const uint8_t *ch_bitmap;

    if (!instance.font.data_array)
        return;

    _rect.width  = 1;
    _rect.height = 1;

    // Clip

    ch_bitmap = instance.font.data_array + offset;
    for (y_offset = 0; y_offset < ch_height;)
    {
        mask = 0x01;
        _rect.top_left.y = y + y_offset;
        for (x_offset = 0; x_offset < ch_width;)
        {
            if (mask & (*ch_bitmap))
            {
                _rect.top_left.x = x + x_offset;
                instance.driver.fill_f(&_rect, instance.pen.color);
            }
            else if (instance.font.background_on)
            {
                _rect.top_left.x = x + x_offset;
                instance.driver.fill_f(&_rect, instance.font.background_color);
            }

            mask <<= 1;
            x_offset++;

            if (mask == 0)
            {
                ch_bitmap++;
                mask = 0x01;
            }
        }

        if(mask != 0x01)
            ch_bitmap++;
        y_offset++;
    }
}

static void _draw_char_ver(char ch, gl_int_t x, gl_int_t y)
{
    gl_rectangle_t _rect;
    gl_int_t ch_width = _font_width(ch);
    gl_int_t ch_height = _font_height();
    uint32_t offset = _font_offset(ch);
    gl_int_t x_offset = 0;
    gl_int_t y_offset = 0;
    uint8_t mask = 0;
    const uint8_t *ch_bitmap;

    if (!instance.font.data_array)
        return;

    _rect.width  = 1;
    _rect.height = 1;

    ch_height = abs(_saturate(x + ch_height, 0, instance.driver.display_width) - x);
    ch_width = abs(_saturate(y - ch_width, 0, instance.driver.display_height) - y);

    ch_bitmap = instance.font.data_array + offset;
    for (y_offset = 0; y_offset < ch_height;)
    {
        mask = 0x01;
        _rect.top_left.x = x + y_offset;
        for (x_offset = 0; x_offset < ch_width;)
        {
            if (mask & *ch_bitmap)
            {
                _rect.top_left.y = y - x_offset;
                instance.driver.fill_f(&_rect, instance.pen.color);
            }
            else if (instance.font.background_on)
            {
                _rect.top_left.y = y - x_offset;
                instance.driver.fill_f(&_rect, instance.font.background_color);
            }

            mask <<= 1;
            x_offset++;

            if (mask == 0)
            {
                ch_bitmap++;
                mask = 0x01;
            }
        }
        ch_bitmap++;
        y_offset++;
    }
}

void gl_draw_char(char ch, gl_coord_t x, gl_coord_t y)
{
    if (!instance.driver.fill_f || !instance.font.data_array)
        return;

    if (instance.font.orientation == GL_FONT_HORIZONTAL || GL_FONT_VERTICAL_COLUMN)
        _draw_char_hor_crop(ch, x, y);
    else
        _draw_char_ver_crop(ch, x, y);
}

void gl_draw_text(const char * __generic_ptr text, gl_coord_t x, gl_coord_t y)
{
    gl_int_t x_pos = x;
    gl_int_t y_pos = y;
    gl_int_t end_pos;
    char font_height;

    if (!instance.driver.fill_f || !instance.font.data_array)
        return;

    font_height = _font_height();

    if (instance.font.orientation == GL_FONT_HORIZONTAL)
    {
        // eliminate from display by y coordinate
        if (y > instance.crop_rect.bottom || y + font_height < instance.crop_rect.top)
            return ;

        // if it's cut by y top/bottom line
        if ((y < instance.crop_rect.top) || ((y + font_height) > instance.crop_rect.bottom))
        {
            while(*text)
            {
                _draw_char_hor_crop(*text, x_pos, y_pos);
                x_pos += _font_width(*text);
                text++;
            }

            return;
        }

        // eliminate all chars with x coordinate less then 0
        end_pos = x_pos;
        if (end_pos < instance.crop_rect.left)
        {
            while (*text)
            {
                end_pos += _font_width(*text);
                if (end_pos > instance.crop_rect.left)
                    break;
                text++;
            }

            if (!*text)
                return;

            _draw_char_hor_crop(*text, end_pos - _font_width(*text), y_pos);
            text++;
            x_pos = end_pos;
        }

        // draw between left and right x display line
        end_pos += _font_width(*text);
        while (*text && end_pos < instance.crop_rect.right)
        {
            _draw_char_hor(*text, x_pos, y_pos);
            x_pos = end_pos;
            text++;
            end_pos += _font_width(*text);
        }

        // if there is one char on right x display line, draw it
         if (*text && x_pos < instance.crop_rect.right)
            _draw_char_hor_crop(*text, x_pos, y_pos);

         return;
    }

    if (instance.font.orientation == GL_FONT_VERTICAL_COLUMN)
    {
        // eliminate from display by y coordinate
        if (x > instance.crop_rect.right || x + _font_width_max() < instance.crop_rect.left)
            return ;

        // if it's cut by x left/right display line
        if (x < instance.crop_rect.left || x + _font_width_max() > instance.crop_rect.right)
        {
            while (*text)
            {
                _draw_char_hor_crop(*text, x_pos, y_pos);
                y_pos += font_height;
                text++;
            }

            return;
        }

        // eliminate all chars with y coordinate less then 0
        end_pos = y_pos;
        if (end_pos < instance.crop_rect.top)
        {
            while (*text)
            {
                end_pos  += font_height;
                if (end_pos > instance.crop_rect.top)
                    break;
                text++;
            }

            if (!*text)
                return;

            _draw_char_hor_crop(*text, x_pos,  end_pos - font_height);
            text++;
            y_pos = end_pos;
        }

        // draw between top and bottom display line
        end_pos += font_height;
        while (*text && end_pos < instance.crop_rect.bottom)
        {
            _draw_char_hor(*text, x_pos, y_pos);
            y_pos = end_pos;
            text++;
            end_pos += font_height;
        }

        // if there is one char on bottom display line, draw it
        if (*text && y_pos < instance.crop_rect.bottom)
            _draw_char_hor_crop(*text, x_pos, y_pos);

        return;
    }

    if (instance.font.orientation == GL_FONT_VERTICAL)
    {
        // eliminate from display by y coordinate
        if (x > instance.crop_rect.right || x + font_height < instance.crop_rect.left)
            return ;

        // if it's cut by x left/right display line
         if (x < instance.crop_rect.left || x + font_height > instance.crop_rect.right)
        {
            while (*text)
            {
                _draw_char_ver_crop(*text, x_pos, y_pos);
                y_pos -= _font_width(*text);
                text++;
            }

            return;
        }

         // eliminate all chars with y coordinate greater then display_height
         end_pos = y_pos;
         if (end_pos > instance.crop_rect.bottom)
         {
            while (*text)
            {
                end_pos  -= _font_width(*text);
                if (end_pos < instance.crop_rect.bottom)
                    break;
                text++;
            }

            if (!*text)
                return;

            _draw_char_ver_crop(*text, x_pos, end_pos + _font_width(*text));
            text++;
            y_pos = end_pos;
         }

        // draw between top and bottom display line
        end_pos  -= _font_width(*text);
        while (*text && end_pos > instance.crop_rect.top)
        {
            _draw_char_ver(*text, x_pos, y_pos);
            y_pos = end_pos;
            text++;
            end_pos -= _font_width(*text);
        }

        // if there is one char on top display line, draw it
        if (*text && y_pos > instance.crop_rect.top)
            _draw_char_ver_crop(*text, x_pos, y_pos);
    }
}

gl_size_t gl_get_text_dimensions(const char * __generic_ptr text)
{
    gl_size_t result;
    gl_uint_t maks = 0;
    gl_uint_t containter = 0;

    gl_font_orientation_t orientation = instance.font.orientation;
    gl_int_t text_length = 0;

    if (!text || !instance.font.data_array)
    {
        result.height = 0;
        result.width = 0;
        return result;
    }

    if (orientation != GL_FONT_VERTICAL_COLUMN)
    {
        while (*text)
            containter += _font_width(*text++);

        if (orientation == GL_FONT_HORIZONTAL)
        {
            result.width = containter;
            result.height = _font_height();
        }
        else
        {
            result.width = _font_height();
            result.height = containter;
        }
    }
    else
    {
        while (text[text_length])
            if (maks < (containter = _font_width(text[text_length++])))
                maks = containter;

        result.width = maks;
        result.height = _font_height() * text_length;
    }

    return result;
}
