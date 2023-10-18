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

#include "gl.h"
#include "gl_utils.h"
#include <string.h>

gl_t instance =
{
    // driver
    {0, 0, 0, 0, 0, 0},

    // crop_border
    0, 0, 0, 0,

    // pen
    GL_RED, 0, 1,

    // brush
    GL_YELLOW, GL_BRUSH_STYLE_FILL,

    // gradient
    GL_WHITE, GL_BLACK,

    // font
    {0, GL_FONT_HORIZONTAL, GL_WHITE, false}
};

void gl_set_driver(gl_driver_t *driver)
{
    memcpy(&instance.driver, driver, sizeof(gl_driver_t));

    instance.crop_rect.top = 0;
    instance.crop_rect.left = 0;
    instance.crop_rect.right  = instance.driver.display_width;
    instance.crop_rect.bottom = instance.driver.display_height;
}

void gl_clear(gl_color_t color)
{
    gl_rectangle_t _rect;

    if (!instance.driver.fill_f)
        return;

    _rect.top_left.x = 0;
    _rect.top_left.y = 0;
    _rect.width  = instance.driver.display_width;
    _rect.height = instance.driver.display_height;

    instance.driver.fill_f(&_rect, color);
}

bool gl_set_crop_borders(gl_coord_t left, gl_coord_t top, gl_coord_t bottom, gl_coord_t right)
{
    // If driver is not initialized just return
    if (!instance.driver.fill_f)
        return false;

    // If area is out of screen then set crop rect to screen's dimension
    if (top >= instance.driver.display_height
        || left >= instance.driver.display_width
        || right < 0
        || bottom < 0
        || bottom < top
        || right < left
    )
    {
        instance.crop_rect.top = 0;
        instance.crop_rect.left = 0;
        instance.crop_rect.right = instance.driver.display_width;
        instance.crop_rect.bottom = instance.driver.display_height;
        return true;
    }

    // If area is out of screen in some part, crop that
    if (left < 0)
        instance.crop_rect.left = 0;
    else
        instance.crop_rect.left = left;

    if (top < 0)
        instance.crop_rect.top = 0;
    else
        instance.crop_rect.top = top;

    if (right > instance.driver.display_width)
        instance.crop_rect.right = instance.driver.display_width;
    else
        instance.crop_rect.right = right;

    if (bottom > instance.driver.display_height)
        instance.crop_rect.bottom = instance.driver.display_height;
    else
        instance.crop_rect.bottom = bottom;

    return true;
}

void gl_set_font(const uint8_t *font)
{
    instance.font.data_array = font;
}

void gl_set_font_orientation(gl_font_orientation_t orientation)
{
    instance.font.orientation = orientation;
}


void gl_set_pen(gl_color_t color, uint16_t width)
{
    instance.pen.inner_width = width >> 1;
    instance.pen.outer_width = width - instance.pen.inner_width;

    instance.pen.color = color;
}

void gl_set_pen_width(uint16_t width)
{
    instance.pen.inner_width = width >> 1;
    instance.pen.outer_width = width - instance.pen.inner_width;
}

void gl_set_inner_pen(uint16_t width_inside_object)
{
    instance.pen.inner_width = width_inside_object;
}

void gl_set_outer_pen(uint16_t width_outside_object)
{
    instance.pen.outer_width = width_outside_object;
}

uint16_t gl_get_inner_pen()
{
    return instance.pen.inner_width;
}

uint16_t gl_get_outer_pen()
{
    return instance.pen.outer_width;
}

void gl_set_pen_color(gl_color_t color)
{
    instance.pen.color = color;
}

void gl_set_brush_style(gl_brush_style_t style)
{
    instance.brush.style = style;
}

void gl_set_brush_color(gl_color_t color)
{
    instance.brush.color = color;
}

void gl_set_brush_color_from(gl_color_t color)
{
    instance.gradient_color.from = color;
}

void gl_set_brush_color_to(gl_color_t color)
{
    instance.gradient_color.to = color;
}

void gl_set_font_background_color(gl_color_t background)
{
    instance.font.background_color = background;
}

void gl_set_font_background(bool enable)
{
    instance.font.background_on = enable;
}

uint16_t gl_get_screen_width()
{
    if (instance.driver.fill_f)
        return instance.driver.display_width;

    return 0;
}

uint16_t gl_get_screen_height()
{
    if (instance.driver.fill_f)
        return instance.driver.display_height;

    return 0;
}
