/****************************************************************************
**
** Copyright (C) 2020 MikroElektronika d.o.o.
** Contact: https://www.mikroe.com/contact
**
** This file is part of the mikroSDK package
**
** Commercial License Usage
**
** Licensees holding valid commercial NECTO compilers AI licenses may use this
** file in accordance with the commercial license agreement provided with the
** Software or, alternatively, in accordance with the terms contained in
** a written agreement between you and The mikroElektronika Company.
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

#include "gl_shapes.h"
#include "gl_utils.h"
#include <math.h>
#include <stdlib.h>
#include <stddef.h>
#include <stdbool.h>

extern gl_t instance;

/** *************************************************
 * @brief Draw part of circle like pizza slice.
 *
 * @detail This function should only be used for pieces
 * at hte same side of circle (I and II quadrant
 * OR III and IV quadrant). There is not any check
 * if angles are correct, so user is in obligation
 * to send arc with correct values.
 *
 * @param arc -> arc which will be painted
 * @param instance -> definition of all details about paint
 ***************************************************/
static void _draw_slice(gl_arc_t* arc, gl_rectangle_t* border_rect);

gl_color_t gl_gradient(gl_color_t from, gl_color_t to, float ratio)
{
    uint8_t r_from = GL_RED_OF(from);
    uint8_t r_to = GL_RED_OF(to);

    uint8_t g_from = GL_GREEN_OF(from);
    uint8_t g_to = GL_GREEN_OF(to);

    uint8_t b_from = GL_BLUE_OF(from);
    uint8_t b_to = GL_BLUE_OF(to);

    r_to = (float)r_from + (r_to - r_from) * ratio;
    g_to = (float)g_from + (g_to - g_from) * ratio;
    b_to = (float)b_from + (b_to - b_from) * ratio;

    return GL_RGB2COLOR(r_to, g_to, b_to);
}

static void _draw_horizontal_gradient_line(gl_rectangle_t *rect, gl_rectangle_t* border_rect)
{
    gl_color_t brush_color;
    gl_rectangle_t my_rect;

    my_rect.height = rect->height;
    my_rect.width = 1;
    my_rect.top_left.y = rect->top_left.y;
    my_rect.top_left.x = rect->top_left.x + rect->width;

    while (--my_rect.top_left.x >= rect->top_left.x)
    {
        brush_color = gl_gradient(instance.gradient_color.from, instance.gradient_color.to, (my_rect.top_left.x - border_rect->top_left.x) / (float) border_rect->width);
        instance.driver.fill_f(&my_rect, brush_color);
    }
}

static void _draw_vertical_gradient_line(gl_rectangle_t *rect, gl_rectangle_t* border_rect)
{
    gl_color_t brush_color;

    brush_color = gl_gradient(instance.gradient_color.from, instance.gradient_color.to, (rect->top_left.y - border_rect->top_left.y) / (float) border_rect->height);
    instance.driver.fill_f(rect, brush_color);
}

static void _draw_one_color_line(gl_rectangle_t *rect, gl_rectangle_t* unused)
{
    instance.driver.fill_f(rect, instance.brush.color);
}

inline static void _rect_gradient_crop(gl_rectangle_t* rect, gl_rectangle_t* gradient_border, bool no_crop)
{
    gl_rectangle_t tmp_rect;
    gl_color_t brush_color;
    gl_int_t limit;
    int16_t right_border = instance.crop_rect.right;
    int16_t bottom_border = instance.crop_rect.bottom;

    if (no_crop)
    {
        tmp_rect.top_left.x = rect->top_left.x;
        tmp_rect.top_left.y = rect->top_left.y;
        tmp_rect.width = rect->width;
        tmp_rect.height = rect->height;
    }
    else
    {
        if (instance.crop_rect.right == instance.crop_rect.left || instance.crop_rect.top == instance.crop_rect.bottom)
            return;

        if (rect->top_left.x >= right_border
        || rect->top_left.y >= bottom_border
        || rect->top_left.x + rect->width < instance.crop_rect.left
        || rect->top_left.y + rect->height < instance.crop_rect.top
        )
        return;

        if (rect->top_left.x >= instance.crop_rect.left)
            tmp_rect.top_left.x =  rect->top_left.x;
        else
            tmp_rect.top_left.x = instance.crop_rect.left;

        if (rect->top_left.y >= instance.crop_rect.top)
            tmp_rect.top_left.y = rect->top_left.y;
        else
            tmp_rect.top_left.y =instance.crop_rect.top;

        if (rect->top_left.x + rect->width <= right_border)
            tmp_rect.width = rect->top_left.x + rect->width - tmp_rect.top_left.x;
        else
            tmp_rect.width = right_border - tmp_rect.top_left.x;

        if (rect->top_left.y + rect->height <= bottom_border)
            tmp_rect.height = rect->top_left.y + rect->height - tmp_rect.top_left.y;
        else
            tmp_rect.height = bottom_border - tmp_rect.top_left.y;
    }

    if (instance.brush.style == GL_BRUSH_STYLE_GRADIENT_TOP_DOWN)
    {
        limit =  tmp_rect.top_left.y + tmp_rect.height;
        tmp_rect.height = 1;
        while (tmp_rect.top_left.y < limit)
        {
            brush_color = gl_gradient(instance.gradient_color.from,
                                    instance.gradient_color.to,
                                    (tmp_rect.top_left.y - gradient_border->top_left.y) / (float) gradient_border->height);
            instance.driver.fill_f(&tmp_rect, brush_color);
            tmp_rect.top_left.y++;
        }
    }
    else if(instance.brush.style == GL_BRUSH_STYLE_GRADIENT_LEFT_RIGHT)
    {
        limit =  tmp_rect.top_left.x + tmp_rect.width;
        tmp_rect.width = 1;
        while (tmp_rect.top_left.x < limit)
        {
            brush_color = gl_gradient(instance.gradient_color.from,
                                    instance.gradient_color.to,
                                    (tmp_rect.top_left.x - gradient_border->top_left.x) / (float) gradient_border->width);
            instance.driver.fill_f(&tmp_rect, brush_color);
            tmp_rect.top_left.x++;
        }
    }
}

/*********************************************************
 * For painting without crop use driver->fill_f function!
 ********************************************************/
// void static _rect_fill_crop(gl_rectangle_t* rect, gl_color_t color);
//#pragma ReentrancyCheck OFF _rect_fill_crop


void static _rect_fill_crop(gl_rectangle_t* rect, gl_color_t color)
{
    gl_rectangle_t tmp_rect;
    int16_t right_border = instance.crop_rect.right;
    int16_t bottom_border = instance.crop_rect.bottom;

    if (instance.crop_rect.left == instance.crop_rect.right || instance.crop_rect.top == instance.crop_rect.bottom)
        return;

    if (rect->top_left.x >= right_border
        || rect->top_left.y >= bottom_border
        || rect->top_left.x + (gl_int_t) rect->width < instance.crop_rect.left
        || rect->top_left.y + (gl_int_t) rect->height < instance.crop_rect.top
    )
        return;

    if (rect->top_left.x >= instance.crop_rect.left)
        tmp_rect.top_left.x =  rect->top_left.x;
    else
        tmp_rect.top_left.x = instance.crop_rect.left;

    if (rect->top_left.y >= instance.crop_rect.top)
        tmp_rect.top_left.y = rect->top_left.y;
    else
        tmp_rect.top_left.y =instance.crop_rect.top;

    if (rect->top_left.x + (gl_int_t) rect->width <= right_border)
        tmp_rect.width = rect->top_left.x + rect->width - tmp_rect.top_left.x;
    else
        tmp_rect.width = right_border - tmp_rect.top_left.x;

    if (rect->top_left.y + (gl_int_t) rect->height <= bottom_border)
        tmp_rect.height = rect->top_left.y + rect->height - tmp_rect.top_left.y;
    else
        tmp_rect.height = bottom_border - tmp_rect.top_left.y;


    instance.driver.fill_f(&tmp_rect, color);
}

void gl_draw_rect_of_global_gradient_object(gl_rectangle_t* rect, gl_rectangle_t* gradient_border)
{
    bool no_crop;
    gl_uint_t pen = instance.pen.inner_width + instance.pen.outer_width;

    if (!instance.driver.fill_f || rect == 0 || gradient_border == 0)
        return;

    no_crop = rect->top_left.x - pen >= 0
            && rect->top_left.y - pen >= 0
            && rect->top_left.x + rect->width + pen <= instance.driver.display_width
            && rect->top_left.y + rect->height + pen <= instance.driver.display_height;

    if (instance.brush.style == GL_BRUSH_STYLE_GRADIENT_TOP_DOWN)
        _rect_gradient_crop(rect, rect, no_crop);
    else if (instance.brush.style == GL_BRUSH_STYLE_GRADIENT_LEFT_RIGHT)
        _rect_gradient_crop(rect, gradient_border, no_crop);
    else
        _rect_fill_crop(rect, instance.brush.color);
}

static void _draw_diagonal_line_by_x(gl_point_t p, gl_point_t q, uint16_t len, gl_color_t color, bool no_crop)
{
    gl_rectangle_t rect;
    gl_int_t y2;
    double k;
    int16_t left_border = instance.crop_rect.left;
    int16_t right_border = instance.crop_rect.right;
    int16_t top_border = instance.crop_rect.top;
    int16_t bottom_border = instance.crop_rect.bottom;
    k = (q.x - p.x) / (double) (q.y - p.y);
    rect.width = 1;

    if (p.x < q.x)
    {
        rect.top_left.y = q.y;
        q.y = p.y;
        p.y = rect.top_left.y;

        rect.top_left.x = q.x;
        q.x = p.x;
        p.x = rect.top_left.x;
    }

    if (no_crop)
    {
        rect.height = len;
        rect.top_left.x = p.x;
        while (rect.top_left.x >= q.x)
        {
            rect.top_left.y = p.y + (rect.top_left.x - p.x) / k;
            instance.driver.fill_f(&rect, color);
            rect.top_left.x--;
        }
    }
    else
    {
        if (q.x >= right_border || p.x < left_border)
            return;
        if (p.x >= right_border)
            rect.top_left.x = right_border - 1;
        else
            rect.top_left.x = p.x;
        if (q.x < left_border)
            q.x = left_border;

        for (; rect.top_left.x >= q.x; rect.top_left.x--)
        {
            rect.top_left.y = floor(p.y + (rect.top_left.x - p.x) / k); //!<-- must use floor so that y is not ZERO double more times in case of crop at x=0
            y2 = rect.top_left.y + len;

            if (rect.top_left.y >= bottom_border || y2 <= top_border)
                continue;
            if (rect.top_left.y < top_border)
                rect.top_left.y = top_border;
            if (y2 > bottom_border)
                y2 = bottom_border;

            rect.height = y2 - rect.top_left.y;
            instance.driver.fill_f(&rect, color);
        }
    }
}


// NOTE: ovde je visak ovaj color argument
static void _draw_diagonal_line_by_y(gl_point_t p, gl_point_t q, uint16_t len, bool no_crop)
{
    gl_rectangle_t rect;
    gl_int_t x2;
    double k;
    int16_t left_border = instance.crop_rect.left;
    int16_t right_border = instance.crop_rect.right;
    int16_t top_border = instance.crop_rect.top;
    int16_t bottom_border = instance.crop_rect.bottom;
    k = (q.x - p.x) / (double) (q.y - p.y);
    rect.height = 1;

    if (p.y < q.y)
    {
        rect.top_left.y = q.y;
        q.y = p.y;
        p.y = rect.top_left.y;

        rect.top_left.x = q.x;
        q.x = p.x;
        p.x = rect.top_left.x;
    }

    if (no_crop)
    {
        rect.width = len;
        rect.top_left.y = p.y;
        while (rect.top_left.y >= q.y)
        {
            rect.top_left.x = p.x + (rect.top_left.y - p.y) * k;
            instance.driver.fill_f(&rect, instance.pen.color);
            rect.top_left.y--;
        }
    }
    else
    {
        if (q.y >= bottom_border || p.y < top_border)
            return;
        if (p.y >= bottom_border)
            rect.top_left.y = bottom_border - 1;
        else
            rect.top_left.y = p.y;
        if (q.y < top_border)
            q.y = top_border;

        for (;rect.top_left.y >= q.y; rect.top_left.y--)
        {
            rect.top_left.x = floor(p.x + (rect.top_left.y - p.y) * k); //!<-- must use floor so that x is not ZERO double more times then it should be in case of crop at y=0
            x2 = rect.top_left.x + len;
            if (x2 <= left_border || rect.top_left.x >= right_border)
                continue;
            if (rect.top_left.x < left_border)
                rect.top_left.x = left_border;
            if (x2 > right_border)
                x2 = right_border;

            rect.width = x2 - rect.top_left.x;
            instance.driver.fill_f(&rect, instance.pen.color);
        }
    }
}

static void _draw_triangle_crop(gl_point_t a, gl_point_t b, gl_point_t c, gl_color_t color)
{
    gl_rectangle_t rect;
    double k1, k2;       //!<-- y=kx+n
    gl_int_t tmp;
    int16_t left_border = instance.crop_rect.left;
    int16_t right_border = instance.crop_rect.right;
    int16_t top_border = instance.crop_rect.top;
    int16_t bottom_border = instance.crop_rect.bottom;

    /*****************************************
     * sort points by y-coordinate
     * so A become most down, and c most up
     *****************************************/
    if (a.y < b.y)
    {
        tmp = b.y;
        b.y = a.y;
        a.y = tmp;

        tmp = b.x;
        b.x = a.x;
        a.x = tmp;
    }
    if (a.y < c.y)
    {
        tmp = a.y;
        a.y = c.y;
        c.y = tmp;

        tmp = a.x;
        a.x = c.x;
        c.x = tmp;
    }
    if (b.y < c.y)
    {
        tmp = b.y;
        b.y = c.y;
        c.y = tmp;

        tmp = b.x;
        b.x = c.x;
        c.x = tmp;
    }
    if (a.y == b.y && a.x > b.x)
    {
        tmp = b.x;
        b.x = a.x;
        a.x = tmp;
    }

    /******************************
     * Calculate coefficients.
     ******************************/
    if (b.x > c.x)
    {
        k1 = (c.x - a.x) / (double) (c.y - a.y);
        k2 = (b.x - a.x) / (double) (b.y - a.y); // FIXME: Ivan: pogledati asemblerski kod pri prvom izracunavanju ovog izraza u projektu 'BuildFailedIfLabels...' na ARMu (3/-3 = 3.77E+008)
    }
    else
    {
        k1 = (b.x - a.x) / (double) (b.y - a.y);
        k2 = (c.x - a.x) / (double) (c.y - a.y);
    }

    if (a.y < top_border || c.y >= bottom_border || max(max(a.x,b.x),c.x) < left_border || min(min(a.x,b.x),c.x) >= right_border)        //!<-- crop check
        return;

    /********************************
     * Painting!
     *******************************/
    rect.height = 1;
    rect.top_left.y = a.y;

    rect.top_left.y = min(rect.top_left.y, bottom_border-1);
    for (;rect.top_left.y >= b.y && rect.top_left.y >= top_border; rect.top_left.y--) //NOTE: da li je nula dozvoljena za crtanje?!
    {
        rect.top_left.x = a.x + (rect.top_left.y - a.y) * k1;
        if (rect.top_left.x < left_border)
            rect.top_left.x = left_border;
        if (rect.top_left.x >= right_border)
            continue;
        tmp = a.x + (rect.top_left.y - a.y) * k2;
        if (tmp >= right_border)
            tmp = right_border - 1;
        if (tmp <= left_border)
            continue;
        rect.width = tmp - rect.top_left.x + 1;
        instance.driver.fill_f(&rect, color);
    }

    if (a.y == b.y) //!<-- if they are same, the AB line is not painted
        rect.top_left.y++;

    if (b.x > c.x)
    {
        k2 = (b.x - c.x) / (double) (b.y - c.y);

        rect.top_left.y = min(rect.top_left.y,bottom_border - 1);
        for (;rect.top_left.y >= c.y && rect.top_left.y >= top_border; rect.top_left.y--)
        {
            rect.top_left.x = a.x + (rect.top_left.y - a.y) * k1;
            if (rect.top_left.x < left_border)
                rect.top_left.x = left_border;
            if (rect.top_left.x >= right_border)
                continue;
            tmp = b.x + (rect.top_left.y - b.y) * k2;
            if (tmp >= right_border)
                tmp = right_border - 1;
            if (tmp <= left_border)
                continue;
            rect.width = tmp - rect.top_left.x+1;
            instance.driver.fill_f(&rect, color);
        }
    }
    else
    {
        k1 = (b.x - c.x) / (double) (b.y - c.y);

        for (;rect.top_left.y >= c.y && rect.top_left.y >= top_border; rect.top_left.y--)
        {
            rect.top_left.x = b.x + (rect.top_left.y - b.y) * k1;
            tmp = a.x + (rect.top_left.y - a.y) * k2;
            if (tmp < rect.top_left.x)
            {
                rect.top_left.x = tmp;
                tmp = b.x + (rect.top_left.y - b.y) * k1;
            }
            if (rect.top_left.x < left_border)
                rect.top_left.x = left_border;
            if (rect.top_left.x >= right_border)
                continue;
            if (tmp >= right_border)
                tmp = right_border-1;
            if (tmp <= left_border)
                continue;
            rect.width = tmp - rect.top_left.x+1;
            instance.driver.fill_f(&rect, color);
        }
    }
}

static void _draw_triangle_fill(gl_point_t a, gl_point_t b, gl_point_t c, gl_color_t color)
{
    gl_rectangle_t rect;
    double k1, k2;                   //!<-- y=kx+n
    gl_int_t tmp;

    /*****************************************
     * Sort points by y-coordinate
     * so A become most down, and c most up
     *****************************************/
    if (a.y < b.y)
    {
        tmp = b.y;
        b.y = a.y;
        a.y = tmp;

        tmp = b.x;
        b.x = a.x;
        a.x = tmp;
    }
    if (a.y < c.y)
    {
        tmp = a.y;
        a.y = c.y;
        c.y = tmp;

        tmp = a.x;
        a.x = c.x;
        c.x = tmp;
    }
    if (b.y < c.y)
    {
        tmp = b.y;
        b.y = c.y;
        c.y = tmp;

        tmp = b.x;
        b.x = c.x;
        c.x = tmp;
    }
    if (a.y == b.y && a.x > b.x)
    {
        tmp = b.x;
        b.x = a.x;
        a.x = tmp;
    }

    /******************************
     * Calculate coefficients.
     ******************************/
    if (b.x > c.x)
    {
        k1 = (c.x - a.x) / (double) (c.y - a.y);
        k2 = (b.x - a.x) / (double) (b.y - a.y);
    }
    else
    {
        k1 = (b.x - a.x) / (double) (b.y - a.y);
        k2 = (c.x - a.x) / (double) (c.y - a.y);
    }

    /******************************
     * Check if there is triangle
     * or line.
     ******************************/
    if (k1 - k2 < 0.000001 && k1 - k2 > -0.000001)
        return;

    /********************************
     * Painting!
     *******************************/
    rect.height = 1;
    rect.top_left.y = a.y;
    while (rect.top_left.y >= b.y)
    {
        rect.top_left.x = a.x + (rect.top_left.y - a.y) * k1;
        rect.width = a.x + (rect.top_left.y - a.y) * k2 - rect.top_left.x + 1;
        instance.driver.fill_f(&rect, color);
        rect.top_left.y--;
    }

    if (a.y == b.y)     //!<-- if they are same, the AB line is not painted
        rect.top_left.y++;

    if (b.x > c.x)
    {
        k2 = (b.x - c.x) / (double) (b.y - c.y);

        while (rect.top_left.y >= c.y)
        {
            rect.top_left.x = a.x + (rect.top_left.y - a.y) * k1;
            rect.width = b.x + (rect.top_left.y - b.y) * k2 - rect.top_left.x;
            instance.driver.fill_f(&rect, color);
            rect.top_left.y--;
        }
    }
    else
    {
        k1 = (b.x - c.x) / (double) (b.y - c.y);

        while (rect.top_left.y >= c.y)
        {
            rect.top_left.x = b.x + (rect.top_left.y - b.y) * k1;
            tmp = a.x + (rect.top_left.y - a.y) * k2;
            if (tmp < rect.top_left.x)
            {
                rect.width = rect.top_left.x - tmp;
                rect.top_left.x = tmp;
            }
            else
                rect.width = tmp - rect.top_left.x;
            instance.driver.fill_f(&rect, color);
            rect.top_left.y--;
        }
    }
}

static void _draw_slice_crop(gl_arc_t* arc, gl_rectangle_t* border_rect)
{
    gl_rectangle_t rect;
    gl_rectangle_t rect_ring;
    gl_color_t paint_color;
    double storage;
    short step;
    gl_int_t x_left;
    gl_int_t y_left;
    gl_int_t x_right;
    gl_int_t y_right;
    gl_int_t radius_out;
    gl_int_t x_ring_left;
    gl_int_t y_ring_left;
    gl_int_t x_ring_right;
    gl_int_t y_ring_right;
    gl_int_t buffer_right_x;
    gl_int_t y_extremum_ring_out;
    gl_int_t y_extremum_ring_in;
    gl_int_t y_extremum_triangle;
    int32_t circle_equation_part;
    double tg_angle_start;
    double tg_angle_end;
    double coefficient_left;    //<-- (x_left-x0)/(y_left-y0)
    double coefficient_right;   //<-- (x_right-x0)/(y_right-y0)
    int16_t left_border = instance.crop_rect.left;
    int16_t right_border = instance.crop_rect.right;
    int16_t top_border = instance.crop_rect.top;
    int16_t bottom_border = instance.crop_rect.bottom;
    gl_uint_t pen = instance.pen.inner_width + instance.pen.outer_width;

    // check if there is anything to draw
    if (arc->radius == 0 && pen == 0)
        return;

    // calculate fundamental variables
    radius_out = (gl_int_t) arc->radius + pen;

    storage = 3.14159265358 / 180; //!<-- radians in degree
    tg_angle_start = tan(arc->start_angle * storage);
    tg_angle_end = tan(arc->end_angle * storage);

    // finding pint A
    storage = sqrt(1.0 + tg_angle_start * tg_angle_start);
    x_ring_left = arc->radius / storage;
    y_ring_left = arc->radius / storage * tg_angle_start;

    storage = radius_out / storage; //!<-- must store with double precision to use with y again!
    x_left = (gl_int_t) storage;
    y_left = storage * tg_angle_start;

    // rotate if needed
    if (90 < arc->start_angle && arc->start_angle<= 270)
    {
        x_left *= -1;
        y_left *= -1;
        y_ring_left *= -1;
        x_ring_left *= -1;
    }

    // do the translation from (0,0) center
    x_left += arc->center.x;
    y_left += arc->center.y;
    y_ring_left += arc->center.y;
    x_ring_left += arc->center.x;

    // finding point B
    storage = sqrt(1.0 + tg_angle_end * tg_angle_end);
    x_ring_right = arc->radius / storage;
    y_ring_right = arc->radius / storage * tg_angle_end;

    storage = radius_out / storage; //!<-- must store with double precision to use with y again!
    x_right = (int) storage;
    y_right = storage * tg_angle_end;

    // rotate if needed
    if (90 < arc->end_angle && arc->end_angle<= 270)
    {
        x_right *= -1;
        y_right *= -1;
        y_ring_right *= -1;
        x_ring_right *= -1;
    }

    // do the translation from (0,0) center
    x_right += arc->center.x;
    y_right += arc->center.y;
    y_ring_right += arc->center.y;
    x_ring_right += arc->center.x;

    // check which one is realy left
    if (x_left > x_right)
    {
        storage = x_left;
        x_left = x_right;
        x_right = storage;

        storage = y_left;
        y_left = y_right;
        y_right = storage;

        storage = x_ring_left;
        x_ring_left = x_ring_right;
        x_ring_right = storage;

        storage = y_ring_left;
        y_ring_left = y_ring_right;
        y_ring_right = storage;
    }

    coefficient_left = (x_left - arc->center.x) / (double) (y_left - arc->center.y);
    coefficient_right = (x_right - arc->center.x) / (double) (y_right - arc->center.y);

    if (arc->end_angle > 180)
    {
        // negative circle part
        if (x_left <= arc->center.x && arc->center.x <= x_right)
        {
            y_extremum_ring_out = arc->center.y - radius_out;
            y_extremum_ring_in = arc->center.y - (gl_int_t)arc->radius;
        }
        else
        {
            y_extremum_ring_out = y_left < y_right ? y_left : y_right;
            y_extremum_ring_in = y_ring_left < y_ring_right ? y_ring_left : y_ring_right;
        }

        y_extremum_triangle = y_ring_left > y_ring_right ? y_ring_left : y_ring_right;

        step = -1;
    }
    else
    {
        // positive circle part
        if (x_left <= arc->center.x && arc->center.x <= x_right)
        {
            y_extremum_ring_out = arc->center.y + radius_out;
            y_extremum_ring_in = arc->center.y + arc->radius;
        }
        else
        {
            y_extremum_ring_out = y_left > y_right ? y_left : y_right;
            y_extremum_ring_in = y_ring_left > y_ring_right ? y_ring_left : y_ring_right;
        }

        y_extremum_triangle = y_ring_left < y_ring_right ? y_ring_left : y_ring_right;
        step = 1;
    }
    if (pen == 0 || arc->radius == 0)
        y_extremum_ring_in = y_extremum_triangle;

    rect.height = 1;

    // draw tringle part between OA and OB lines
    if ( (instance.brush.style != GL_BRUSH_STYLE_NONE || arc->radius == 0)
        && !(arc->center.y < top_border && y_extremum_triangle < top_border)
        && !(arc->center.y > bottom_border && y_extremum_triangle > bottom_border))
    {
        if (arc->radius == 0)
            paint_color = instance.pen.color;
        else
            paint_color = instance.brush.color;

        rect.top_left.y = arc->center.y;

        if (arc->radius == 0 || instance.brush.style == GL_BRUSH_STYLE_FILL)
        {
            gl_int_t tmp;
            for (; rect.top_left.y != y_extremum_triangle; rect.top_left.y += step)
            {
                if (rect.top_left.y < top_border || rect.top_left.y >= bottom_border)
                    continue;

                rect.top_left.x = arc->center.x + (rect.top_left.y - arc->center.y) * coefficient_left;
                if (rect.top_left.x >= right_border)
                    continue;
                if (rect.top_left.x < left_border)
                    rect.top_left.x = left_border;

                tmp = arc->center.x + (rect.top_left.y - arc->center.y) * coefficient_right;
                if (tmp < left_border)
                    continue;
                if (tmp >= right_border)
                    tmp = right_border;

                rect.width = tmp - rect.top_left.x;
                instance.driver.fill_f(&rect, paint_color);
            }
        }
        else if (instance.brush.style == GL_BRUSH_STYLE_GRADIENT_TOP_DOWN)
        {
            gl_int_t tmp;
            for (; rect.top_left.y != y_extremum_triangle; rect.top_left.y += step)
            {
                if (rect.top_left.y < top_border || rect.top_left.y >= bottom_border)
                    continue;

                rect.top_left.x = arc->center.x + (rect.top_left.y - arc->center.y) * coefficient_left;
                if (rect.top_left.x >= right_border)
                    continue;
                if (rect.top_left.x < left_border)
                    rect.top_left.x = left_border;

                tmp = arc->center.x + (rect.top_left.y - arc->center.y) * coefficient_right;
                if (tmp < left_border)
                    continue;
                if (tmp >= right_border)
                    tmp = right_border;

                rect.width = tmp - rect.top_left.x;
                paint_color = gl_gradient(instance.gradient_color.from, instance.gradient_color.to, (rect.top_left.y - border_rect->top_left.y) / (float) border_rect->height);
                instance.driver.fill_f(&rect, paint_color);
            }

            paint_color = gl_gradient(instance.gradient_color.from, instance.gradient_color.to, (rect.top_left.y - border_rect->top_left.y) / (float) border_rect->height);
        }
        else
        {
            gl_int_t tmp;
            rect.width = 1;
            for (; rect.top_left.y != y_extremum_triangle; rect.top_left.y += step)
            {
                if (rect.top_left.y < top_border || rect.top_left.y >= bottom_border)
                    continue;

                rect.top_left.x = arc->center.x + (rect.top_left.y - arc->center.y) * coefficient_left;
                if (rect.top_left.x >= right_border)
                    continue;
                if (rect.top_left.x < left_border)
                    rect.top_left.x = left_border;

                tmp = arc->center.x + (rect.top_left.y - arc->center.y) * coefficient_right;
                if (tmp < left_border)
                    continue;
                if (tmp >= right_border)
                    tmp = right_border;

                while (rect.top_left.x  < tmp)
                {
                    paint_color = gl_gradient(instance.gradient_color.from, instance.gradient_color.to, (rect.top_left.x - border_rect->top_left.x) / (float) border_rect->width);
                    instance.driver.fill_f(&rect, paint_color);

                    rect.top_left.x++;
                }
            }

            paint_color = gl_gradient(instance.gradient_color.from, instance.gradient_color.to, (rect.top_left.y - border_rect->top_left.y) / (float) border_rect->height);
        }

        if (y_extremum_triangle == y_ring_left)
            rect.top_left.x = x_ring_left;
        else
            rect.top_left.x = arc->center.x + (rect.top_left.y - arc->center.y) * coefficient_left;

        if (rect.top_left.x < left_border)
            rect.top_left.x = left_border;

        if (y_extremum_triangle == y_ring_right)
            buffer_right_x = x_ring_right;
        else
            buffer_right_x = arc->center.x + (rect.top_left.y - arc->center.y) * coefficient_right;

        if (buffer_right_x >= right_border)
            buffer_right_x = right_border - 1;

        if (rect.top_left.y >= top_border
        && rect.top_left.y < bottom_border
        && rect.top_left.x < right_border
        && buffer_right_x > left_border) //NOTE: testirati ovo, promenjen znak
        {
            rect.width = buffer_right_x - rect.top_left.x;
            instance.driver.fill_f(&rect, paint_color);
        }
    }

    // AREA II
    rect_ring.top_left.y = rect.top_left.y = y_extremum_triangle;
    rect_ring.height = 1;
    paint_color = instance.brush.color;

    for (; rect.top_left.y != y_extremum_ring_in; rect_ring.top_left.y = rect.top_left.y += step)
    {
        if (rect.top_left.y < top_border || rect.top_left.y >= bottom_border)
            continue;

        // find most left X
        if (abs(arc->center.y - rect.top_left.y) < abs(arc->center.y - y_left))
            rect_ring.top_left.x = rect.top_left.x = arc->center.x + (rect.top_left.y - arc->center.y) * coefficient_left;
        else
        {
            circle_equation_part = radius_out*(int32_t)radius_out - (rect.top_left.y - arc->center.y)*(int32_t)(rect.top_left.y - arc->center.y);
            while ((x_left - arc->center.x)*(int32_t)(x_left - arc->center.x) > circle_equation_part)
                x_left++;

            rect.top_left.x = x_left;
        }
        if (rect.top_left.x >= right_border)
            continue;
        if (rect.top_left.x < left_border)
            rect.top_left.x = left_border;

        // find most right x
        if (abs(arc->center.y - rect.top_left.y) < abs(arc->center.y - y_right))
            storage = arc->center.x + (rect.top_left.y - arc->center.y) * coefficient_right;
        else
        {
            circle_equation_part = radius_out*(int32_t)radius_out - (rect.top_left.y - arc->center.y)*(int32_t)(rect.top_left.y - arc->center.y);
            while ((x_right - arc->center.x)*(int32_t)(x_right - arc->center.x) > circle_equation_part)
                x_right--;

            storage = x_right;
        }
        if (storage < left_border)
            continue;

        // find where is inner left border of pen (if at this y coordinate even exists left pen)
        if (abs(arc->center.y - y_ring_left) <= abs(arc->center.y - rect.top_left.y))
        {
            circle_equation_part = arc->radius*((int32_t)arc->radius) - (rect.top_left.y - arc->center.y)*(int32_t)(rect.top_left.y - arc->center.y);
            while ((x_ring_left - arc->center.x)*(int32_t)(x_ring_left - arc->center.x) > circle_equation_part)
                x_ring_left++;

            // prepare parameter for slice part
            rect_ring.top_left.x = x_ring_left;
            if (rect_ring.top_left.x < left_border)
                rect_ring.top_left.x = left_border;

            if (x_ring_left >= left_border)
            {
                if (x_ring_left > right_border)
                    x_ring_left = right_border;

                // draw pen (frame of slice)
                if (x_ring_left > rect.top_left.x)
                {
                    rect.width = x_ring_left - rect.top_left.x;
                    instance.driver.fill_f(&rect, instance.pen.color);
                }
            }
        }

        // find where is inner right border of pen (if at this y coordinate even exists right pen)
        if (abs(arc->center.y - y_ring_right) <= abs(arc->center.y - rect.top_left.y))
        {
            circle_equation_part = arc->radius*((int32_t)arc->radius) - (rect.top_left.y - arc->center.y)*(int32_t)(rect.top_left.y - arc->center.y);
            while ((x_ring_right - arc->center.x)*(int32_t)(x_ring_right - arc->center.x) > circle_equation_part)
                x_ring_right--;

            rect.top_left.x = x_ring_right;
            if (rect.top_left.x < right_border)
            {
                if (rect.top_left.x < left_border)
                    rect.top_left.x = left_border;

                // draw pen (frame of slice)
                if (storage > right_border)
                    storage = right_border;

                if (storage > rect.top_left.x)
                {
                    rect.width = storage - rect.top_left.x ;
                    instance.driver.fill_f(&rect, instance.pen.color);
                }
            }

            // prepare parameter for slice part
            storage = x_ring_right;
        }
        if (storage < left_border)
            continue;
        if (storage > right_border)
            storage = right_border;
        if (rect_ring.top_left.x >= right_border)
            continue;
        if (rect_ring.top_left.x < left_border)
            rect_ring.top_left.x = left_border;

        // if slice is not transparent then paint it
        if (instance.brush.style != GL_BRUSH_STYLE_NONE)
        {
            // find color for gradient brush style
            if (instance.brush.style == GL_BRUSH_STYLE_GRADIENT_LEFT_RIGHT)
            {
                rect_ring.width = 1;

                while (rect_ring.top_left.x  < storage)
                {
                    paint_color = gl_gradient(instance.gradient_color.from, instance.gradient_color.to, (rect_ring.top_left.x - border_rect->top_left.x) / (float) border_rect->width);
                    instance.driver.fill_f(&rect_ring, paint_color);

                    rect_ring.top_left.x++;
                }
            }
            else
            {
                if (instance.brush.style == GL_BRUSH_STYLE_GRADIENT_TOP_DOWN)
                    paint_color =  gl_gradient(instance.gradient_color.from, instance.gradient_color.to, (rect.top_left.y - border_rect->top_left.y) / (float) border_rect->height);

                rect_ring.width = storage - rect_ring.top_left.x;
                instance.driver.fill_f(&rect_ring, paint_color);
            }
        }
    }

    // draw part which contains only one color at end of arc
    if (pen)
        paint_color = instance.pen.color;
    else
        paint_color = instance.brush.color;

    if ((y_extremum_ring_out < top_border && y_extremum_ring_in < top_border)
    || (y_extremum_ring_out >= bottom_border && y_extremum_ring_in >= bottom_border))
        return;

    for (rect.top_left.y = y_extremum_ring_in; rect.top_left.y != y_extremum_ring_out; rect.top_left.y += step)
    {
        if (rect.top_left.y < top_border || rect.top_left.y >= bottom_border)
            continue;

        // find left part
        if (abs(arc->center.y - rect.top_left.y) < abs(arc->center.y - y_left))
            rect.top_left.x = arc->center.x + (rect.top_left.y - arc->center.y) * coefficient_left;
        else
        {
            circle_equation_part = radius_out*(int32_t)radius_out - (rect.top_left.y - arc->center.y)*(int32_t)(rect.top_left.y - arc->center.y);
            while ((x_left - arc->center.x)*(int32_t)(x_left - arc->center.x) > circle_equation_part)
                x_left++;

            rect.top_left.x = x_left;
        }
        if (rect.top_left.x >= right_border)
            continue;
        if (rect.top_left.x < left_border)
            rect.top_left.x = left_border;

        // find right part
        if (abs(arc->center.y - rect.top_left.y) < abs(arc->center.y - y_right))
           buffer_right_x = arc->center.x + (rect.top_left.y - arc->center.y) * coefficient_right;
        else
        {
            circle_equation_part = radius_out*(int32_t)radius_out - (rect.top_left.y - arc->center.y)*(int32_t)(rect.top_left.y - arc->center.y);
            while ((x_right - arc->center.x)*(int32_t)(x_right - arc->center.x) > circle_equation_part)
                x_right--;

            if (x_right < 0)
                x_right = 0;

            buffer_right_x = x_right;
        }
        if (buffer_right_x < left_border)
            continue;
        if (buffer_right_x > right_border)
            buffer_right_x = right_border;

        rect.width = buffer_right_x - rect.top_left.x;
        if (pen != 0 || instance.brush.style == GL_BRUSH_STYLE_FILL)
        {
            instance.driver.fill_f(&rect, paint_color);
        }
        else
        {
            if (instance.brush.style == GL_BRUSH_STYLE_GRADIENT_LEFT_RIGHT)
            {
                gl_int_t storage2;
                storage2 = rect.width + rect.top_left.x;
                rect.width = 1;
                while (rect.top_left.x < storage2)
                {
                    paint_color = gl_gradient(instance.gradient_color.from, instance.gradient_color.to, (rect.top_left.x - border_rect->top_left.x) / (float) border_rect->width);
                    instance.driver.fill_f(&rect, paint_color);

                    rect.top_left.x++;
                }
            }
            else
            {
                paint_color = gl_gradient(instance.gradient_color.from, instance.gradient_color.to, (rect.top_left.y - border_rect->top_left.y) / (float) border_rect->height);
                instance.driver.fill_f(&rect, paint_color);
            }
        }
    }
}

static void _draw_slice(gl_arc_t* arc, gl_rectangle_t* border_rect)
{
    gl_rectangle_t rect;
    gl_rectangle_t rect_ring;

    gl_color_t paint_color;
    double storage;
    short step;

    /********************************
     *        __
     *     _--  --_
     *    A \    / B(x_right, y_right)
     *       \  /
     *        \/
     *      O(x,y)
     *
     * A(x_left, y_left)
     * O = arc->center
     * ******************************/

    gl_int_t x_left;
    gl_int_t y_left;
    gl_int_t x_right;
    gl_int_t y_right;

    gl_int_t radius_out;

    gl_int_t x_ring_left;
    gl_int_t y_ring_left;
    gl_int_t x_ring_right;
    gl_int_t y_ring_right;

    gl_int_t y_extremum_ring_out;
    gl_int_t y_extremum_ring_in;
    gl_int_t y_extremum_triangle;

    /**************************************************
     * Saving time variables. Calculate as less as can!
     *
     * 1) Find x using formula for circle. When calculating
     * x coordinate for ARC part, NOT x element OA line,
     * then use circle_equation_part calculated once
     * per interation.
     *
     * cicrcle formula : (x-x0)^2+(y-y0)^2=r^2
     * circle_equation_part = r^2-(y-y0)^2
     *
     * algorithm: while x is out of circle, change x;
     *
     * example:
     * while ( (x-x0)^2 > circle_equation_part )
     *     x++;
     **************************************************/
    gl_int_t circle_equation_part;

    /**************************************************
     * Saving time variables. Calculate as less as can!
     *
     * 2) To find points of intersections arc and lines
     * FROM center of arc with given angles, use formula:
     *
     * x = radius / sqrt(1 + tg^2(angle_alpha))
     * y =  x * tg(angle_alpha)
     *
     * note: don't forget to calculate angle in radian!
     **************************************************/
    double tg_angle_start;
    double tg_angle_end;

    /**************************************************
     * Saving time variables. Calculate as less as can!
     *
     * 3) For finding x of OA and OB lines use formula
     * for line between two dots. Once calculated
     * coefficient, use every time!
     *
     * line formula: x = x0 + (y_temp-y0)*((x_a-x0)/(y_a-y0))
     * coefficient = (x - x0)/(y - y0)
     **************************************************/
    double coefficient_left;    //<-- (x_left-x0)/(y_left-y0)
    double coefficient_right;   //<-- (x_right-x0)/(y_right-y0)

    gl_uint_t pen = instance.pen.inner_width + instance.pen.outer_width;

    // check if there is anything to draw
    if (arc->radius == 0 && pen == 0)
        return;


    /**************************************************
     * Border rectangle
     *
     * Border_rectange is used for calculating color
     * when paint in top-down OR LEFT-R gradient. Normaly
     * this value should be argument of function in case
     * that slice is part of some bigger shape.
     * ***********************************************/
    if (border_rect == NULL && (instance.brush.style == GL_BRUSH_STYLE_GRADIENT_LEFT_RIGHT ||
                               instance.brush.style == GL_BRUSH_STYLE_GRADIENT_TOP_DOWN))
        return;

    // calculate fundamental variables
    radius_out = (gl_int_t) arc->radius + pen;

    storage = 3.14159265358 / 180; //!<-- radians in degree
    tg_angle_start = tan(arc->start_angle * storage);
    tg_angle_end = tan(arc->end_angle * storage);

    // finding pint A
    storage = sqrt(1.0 + tg_angle_start * tg_angle_start);
    x_ring_left = arc->radius / storage;
    y_ring_left = arc->radius / storage * tg_angle_start;

    storage = radius_out / storage; //!<-- must store with double precision to use with y again!
    x_left = (int) storage;
    y_left = storage * tg_angle_start;

    // rotate if needed
    if (90 < arc->start_angle && arc->start_angle<= 270)
    {
        x_left *= -1;
        y_left *= -1;
        y_ring_left *= -1;
        x_ring_left *= -1;
    }

    // do the translation from (0,0) center
    x_left += arc->center.x;
    y_left += arc->center.y;
    y_ring_left += arc->center.y;
    x_ring_left += arc->center.x;

    // finding point B
    storage = sqrt(1.0 + tg_angle_end * tg_angle_end);
    x_ring_right = arc->radius / storage;
    y_ring_right = arc->radius / storage * tg_angle_end;

    storage = radius_out / storage; //!<-- must store with double precision to use with y again!
    x_right = (int) storage;
    y_right = storage * tg_angle_end;

    // rotate if needed
    if (90 < arc->end_angle && arc->end_angle<= 270)
    {
        x_right *= -1;
        y_right *= -1;
        y_ring_right *= -1;
        x_ring_right *= -1;
    }

    // do the translation from (0,0) center
    x_right += arc->center.x;
    y_right += arc->center.y;
    y_ring_right += arc->center.y;
    x_ring_right += arc->center.x;

    // check which one if realy left
    if (x_left > x_right)
    {
        storage = x_left;
        x_left = x_right;
        x_right = storage;

        storage = y_left;
        y_left = y_right;
        y_right = storage;

        storage = x_ring_left;
        x_ring_left = x_ring_right;
        x_ring_right = storage;

        storage = y_ring_left;
        y_ring_left = y_ring_right;
        y_ring_right = storage;
    }

    coefficient_left = (x_left - arc->center.x) / (double) (y_left - arc->center.y);
    coefficient_right = (x_right - arc->center.x) / (double) (y_right - arc->center.y);

    /*************************************************
     * Extremums.
     *
     * The idea for drawing is to split it into 3 areas.
     * In first area only brush color will be painted.
     * And that will be performed FROM center of the
     * arc TO the point "radius of circle" far away from
     * center AND with less y coordinate. That point
     * should be on OA or OB line.
     * The other one of that two points, is  next
     * "extremum_ring_in" and that is the limit of second
     * area for painting. This is the only complicated
     * area for painting, so it is separated with
     * purpose to make every easy part, stay easy, and
     * that way make function go faster, not having
     * too mush if statements where it is not needed.
     * Third area is area of only ring (in this case it's pen)
     * and it has to be drown from extremum_ring_in to the
     * extremum_ring_out. This is where the job is simple only
     * painting shapes with one color, if any (in case there
     * is no ring this will not even run)
     *
     * Find extremums to know all borders
     * for drawing. Also conclude should you
     * draw from top to bottom or opposite.
     *
     * y_xtremum = most far from center y
     * y_ring_up = greater y coordinate form ring arc
     * y_ting_low = lower y coordinate from ring arc
     *
     * Determin if y will be incremented or decremented:
     * step = -1 || step = +1
     *
     * note: if x or y ansics is in slice then it will
     * be extremum_ring's:
     * y_extremum_ring_out = center.y + radius + pen_width
     * y_extremum_ring_in = center.y + radius
     **************************************************/
    if (arc->end_angle > 180)
    {
        // negative circle part
        if (x_left <= arc->center.x && arc->center.x <= x_right)
        {
            y_extremum_ring_out = arc->center.y - radius_out;
            y_extremum_ring_in = arc->center.y - (gl_int_t) arc->radius;
        }
        else
        {
            y_extremum_ring_out = y_left < y_right ? y_left : y_right;
            y_extremum_ring_in = y_ring_left < y_ring_right ? y_ring_left : y_ring_right;
        }

        y_extremum_triangle = y_ring_left > y_ring_right ? y_ring_left : y_ring_right;

        step = -1;
    }
    else
    {
        // positive circle part
        if (x_left <= arc->center.x && arc->center.x <= x_right)
        {
            y_extremum_ring_out = arc->center.y + radius_out;
            y_extremum_ring_in = arc->center.y + arc->radius;
        }
        else
        {
            y_extremum_ring_out = y_left > y_right ? y_left : y_right;
            y_extremum_ring_in = y_ring_left > y_ring_right ? y_ring_left : y_ring_right;
        }

        y_extremum_triangle = y_ring_left < y_ring_right ? y_ring_left : y_ring_right;
        step = 1;
    }
    if (pen == 0 || arc->radius == 0)
        y_extremum_ring_in = y_extremum_triangle;

    rect.height = 1;

    // draw tringle part between OA and OB lines
    if (instance.brush.style != GL_BRUSH_STYLE_NONE || arc->radius == 0)
    {
        if (arc->radius == 0)
            paint_color = instance.pen.color;
        else
            paint_color = instance.brush.color;

        rect.top_left.y = arc->center.y;

        if (arc->radius == 0 || instance.brush.style == GL_BRUSH_STYLE_FILL)
        {
            while (rect.top_left.y != y_extremum_triangle)
            {
                rect.top_left.x = arc->center.x + (rect.top_left.y - arc->center.y) * coefficient_left;
                rect.width = arc->center.x + (rect.top_left.y - arc->center.y) * coefficient_right - rect.top_left.x;

                instance.driver.fill_f(&rect, paint_color);

                rect.top_left.y += step;
            }
        }
        else if (instance.brush.style == GL_BRUSH_STYLE_GRADIENT_TOP_DOWN)
        {
            while (rect.top_left.y != y_extremum_triangle)
            {
                rect.top_left.x = arc->center.x + (rect.top_left.y - arc->center.y) * coefficient_left;
                rect.width = arc->center.x + (rect.top_left.y - arc->center.y) * coefficient_right - rect.top_left.x;

                paint_color = gl_gradient(instance.gradient_color.from, instance.gradient_color.to, (rect.top_left.y - border_rect->top_left.y) / (float) border_rect->height);
                instance.driver.fill_f(&rect, paint_color);

                rect.top_left.y += step;
            }

            paint_color = gl_gradient(instance.gradient_color.from, instance.gradient_color.to, (rect.top_left.y - border_rect->top_left.y) / (float) border_rect->height);
        }
        else
        {
            rect.width = 1;
            while (rect.top_left.y != y_extremum_triangle)
            {
                rect.top_left.x = arc->center.x + (rect.top_left.y - arc->center.y) * coefficient_left;
                storage = arc->center.x + (rect.top_left.y - arc->center.y) * coefficient_right;

                while (rect.top_left.x  < storage)
                {
                    paint_color = gl_gradient(instance.gradient_color.from, instance.gradient_color.to, (rect.top_left.x - border_rect->top_left.x) / (float) border_rect->width);
                    instance.driver.fill_f(&rect, paint_color);

                    rect.top_left.x++;
                }
                rect.top_left.y += step;
            }

            paint_color = gl_gradient(instance.gradient_color.from, instance.gradient_color.to, (rect.top_left.y - border_rect->top_left.y) / (float) border_rect->height);
        }

        /*****************************************************
         * Case when rect.top.y is equal to y_extremum rect
         * is speacial case. If there is no ring (pen) then
         * there we would not get right x coordinate using our
         * formula (because formula is made for line between
         * two dots, if we calculate for end or start dot,
         * we get wrong value). So we want to use already
         * calculated value of x (which we stored at x_left
         * and x_right).
         * Since this is only ONE special case, it is out of
         * while loop, so the loop stay as fast as possible.
         *****************************************************/
        if (y_extremum_triangle == y_ring_left)
            rect.top_left.x = x_ring_left;
        else
            rect.top_left.x = arc->center.x + (rect.top_left.y - arc->center.y) * coefficient_left;

        if (y_extremum_triangle == y_ring_right)
            rect.width = x_ring_right - rect.top_left.x;
        else
            rect.width = arc->center.x + (rect.top_left.y - arc->center.y) * coefficient_right - rect.top_left.x;

        instance.driver.fill_f(&rect, paint_color);
    }

    /**********************************************
     * AREA II
     *
     * Draw part of arc wich has ring inner border
     * to calculate more. The idea is to save time
     * so that function get in this loop only if
     * there is 'area II' - area with pizza slice
     * part and rect. Otherwise, never check and
     * calculate so much parameters.
     * The initialization of extremums handles if
     * function should or should not get in this loop.
     **********************************************/
    rect_ring.top_left.y = rect.top_left.y = y_extremum_triangle;
    rect_ring.height = 1;

    while (rect.top_left.y != y_extremum_ring_in)
    {
        // find most left X
        if (abs(arc->center.y - rect.top_left.y) < abs(arc->center.y - y_left))
            rect_ring.top_left.x = rect.top_left.x = arc->center.x + (rect.top_left.y - arc->center.y) * coefficient_left;
        else
        {
            circle_equation_part = radius_out*radius_out - (rect.top_left.y - arc->center.y)*(rect.top_left.y - arc->center.y);
            while ((x_left - arc->center.x)*(x_left - arc->center.x) > circle_equation_part)
                x_left++;

            rect.top_left.x = x_left;
        }

        // find most right x
        if (abs(arc->center.y - rect.top_left.y) < abs(arc->center.y - y_right))
            storage = arc->center.x + (rect.top_left.y - arc->center.y) * coefficient_right;
        else
        {
            circle_equation_part = radius_out*radius_out - (rect.top_left.y - arc->center.y)*(rect.top_left.y - arc->center.y);
            while ((x_right - arc->center.x)*(x_right - arc->center.x) > circle_equation_part)
                x_right--;

            storage = x_right;
        }

        // find where is inner left border of pen (if at this y coordinate even exists left pen)
        if (abs(arc->center.y - y_ring_left) <= abs(arc->center.y - rect.top_left.y))
        {
            circle_equation_part = arc->radius*((gl_int_t)arc->radius) - (rect.top_left.y - arc->center.y)*(rect.top_left.y - arc->center.y);
            while ((x_ring_left - arc->center.x)*(x_ring_left - arc->center.x) > circle_equation_part)
                x_ring_left++;

            // draw pen (frame of slice)
            rect.width = x_ring_left - rect.top_left.x > 0 ? x_ring_left - rect.top_left.x : 0;
            instance.driver.fill_f(&rect, instance.pen.color);

            // prepare parameter for slice part
            rect_ring.top_left.x = x_ring_left;
        }

        // find where is inner right border of pen (if at this y coordinate even exists right pen)
        if (abs(arc->center.y - y_ring_right) <= abs(arc->center.y - rect.top_left.y))
        {
            circle_equation_part = arc->radius*((gl_int_t) arc->radius) - (rect.top_left.y - arc->center.y)*(rect.top_left.y - arc->center.y);
           while ((x_ring_right - arc->center.x)*(x_ring_right - arc->center.x) > circle_equation_part)
                x_ring_right--;

            // draw pen (frame of slice)
            rect.top_left.x = x_ring_right;
            rect.width = storage - x_ring_right ;//> 0 ? storage - x_ring_right : 0;
            instance.driver.fill_f(&rect, instance.pen.color);

            // prepare parameter for slice part
            storage = x_ring_right;
        }

        // if slice is not transparent then paint it
        if (instance.brush.style != GL_BRUSH_STYLE_NONE)
        {
            // find color for gradient brush style
            if (instance.brush.style == GL_BRUSH_STYLE_GRADIENT_LEFT_RIGHT)
            {
                rect_ring.width = 1;

                while (rect_ring.top_left.x  < storage)
                {
                    paint_color = gl_gradient(instance.gradient_color.from, instance.gradient_color.to, (rect_ring.top_left.x - border_rect->top_left.x) / (float) border_rect->width);
                    instance.driver.fill_f(&rect_ring, paint_color);

                    rect_ring.top_left.x++;
                }
            }
            else
            {
                if (instance.brush.style == GL_BRUSH_STYLE_GRADIENT_TOP_DOWN)
                    paint_color =  gl_gradient(instance.gradient_color.from, instance.gradient_color.to, (rect.top_left.y - border_rect->top_left.y) / (float) border_rect->height);

                rect_ring.width = storage - rect_ring.top_left.x;
                instance.driver.fill_f(&rect_ring, paint_color);
            }
        }

        rect_ring.top_left.y = rect.top_left.y += step;
    }

    // draw part which contains only one color at end of arc
    if (pen)
        paint_color = instance.pen.color;
    else
        paint_color = instance.brush.color;

    // if some preview part was skipped, set y coordinate //!- maybe not needed :/
    rect.top_left.y = y_extremum_ring_in;

    while (rect.top_left.y != y_extremum_ring_out)
    {
        // find left part
        if (abs(arc->center.y - rect.top_left.y) < abs(arc->center.y - y_left))
            rect.top_left.x = arc->center.x + (rect.top_left.y - arc->center.y) * coefficient_left;
        else
        {
            circle_equation_part = radius_out*radius_out - (rect.top_left.y - arc->center.y)*(rect.top_left.y - arc->center.y);
            while ((x_left - arc->center.x)*(x_left - arc->center.x) > circle_equation_part)
                x_left++;

            rect.top_left.x = x_left;
        }

        // find right part
        if (abs(arc->center.y - rect.top_left.y) < abs(arc->center.y - y_right))
            rect.width = arc->center.x + (rect.top_left.y - arc->center.y) * coefficient_right - rect.top_left.x;
        else
        {
            circle_equation_part = radius_out*radius_out - (rect.top_left.y - arc->center.y)*(rect.top_left.y - arc->center.y);
            while ((x_right - arc->center.x)*(x_right - arc->center.x) > circle_equation_part)
                x_right--;

            rect.width = x_right - rect.top_left.x;
        }

        // TODO: consider separating this in 2 functions so that
        // this is not calculated if its not necesarry
        if (pen != 0 || instance.brush.style == GL_BRUSH_STYLE_FILL)
        {
            instance.driver.fill_f(&rect, paint_color);
        }
        else
        {
            if (instance.brush.style == GL_BRUSH_STYLE_GRADIENT_TOP_DOWN)
            {
                paint_color = gl_gradient(instance.gradient_color.from, instance.gradient_color.to, (rect.top_left.y - border_rect->top_left.y) / (float) border_rect->height);
                instance.driver.fill_f(&rect, paint_color);
            }
            else
            {
                storage = rect.width + rect.top_left.x;
                rect.width = 1;
                while (rect.top_left.x < storage)
                {
                    paint_color = gl_gradient(instance.gradient_color.from, instance.gradient_color.to, (rect.top_left.x - border_rect->top_left.x) / (float) border_rect->width);
                    instance.driver.fill_f(&rect, paint_color);

                    rect.top_left.x++;
                }
            }
        }

        rect.top_left.y += step;
    }

    //TODO: dovrsi poslednju liniju
    // circle_equation_part = radius_out*radius_out - (rect.top_left.y - arc->center.y)*(rect.top_left.y - arc->center.y);
    // while ((x_left - arc->center.x)*(x_left - arc->center.x) > circle_equation_part)
    //     x_left++;

    // while ((x_right - arc->center.x)*(x_right - arc->center.x) > circle_equation_part)
    //     x_right--;

    // rect.top_left.x = x_left;
    // rect.width = x_right - rect.top_left.x;

    // if (!instance.pen_width)
    //         paint_color = _gradient(instance.brush_gradient_from, instance.brush_gradient_to, (rect.top_left.y - border_rect->top_left.y) / (float) border_rect->height);

    // instance.driver.fill_f(&rect, paint_color);

}

void gl_draw_rect(gl_coord_t top_left_x, gl_coord_t top_left_y, gl_uint_t width, gl_uint_t height)
{
    gl_rectangle_t tmp_rect;
    bool no_crop;
    // in order to save time for cast in signed, we will store this values as int variables
    gl_int_t pen = instance.pen.inner_width + instance.pen.outer_width;
    gl_int_t inner_offset =  instance.pen.inner_width;
    gl_int_t outer_offset = instance.pen.outer_width;

    if (!instance.driver.fill_f)
        return;

    // determin if there is part of object out of area for drawing "crop rect"
    // left side
    no_crop = top_left_x - outer_offset >= instance.crop_rect.left;
    // top
    no_crop = no_crop && top_left_y - outer_offset >= instance.crop_rect.top;
    // right
    no_crop = no_crop && top_left_x + width + outer_offset < instance.crop_rect.right;
    // bottom
    no_crop = no_crop && top_left_y + height + outer_offset < instance.crop_rect.bottom;

    if (!no_crop)
    {
        if (top_left_x - outer_offset >= instance.crop_rect.right
        || top_left_y - outer_offset >= instance.crop_rect.bottom
        || top_left_x + width + outer_offset < instance.crop_rect.left
        || top_left_y + height + outer_offset < instance.crop_rect.top
        )
        return;
    }

    if (inner_offset * 2 >= width || inner_offset * 2 >= height)
    {
        tmp_rect.top_left.x = top_left_x - outer_offset;
        tmp_rect.top_left.y = top_left_y - outer_offset;
        tmp_rect.width  = 2 * outer_offset + width;
        tmp_rect.height = 2 * outer_offset + height;

        if (no_crop)
            instance.driver.fill_f(&tmp_rect, instance.pen.color);
        else
            _rect_fill_crop(&tmp_rect, instance.pen.color);

        return;
    }

    // Draw frame with pen.
    if (pen)
    {
        // Up and down sides
        tmp_rect.top_left.x = top_left_x - outer_offset;
        tmp_rect.top_left.y = top_left_y - outer_offset;
        tmp_rect.width  = width + 2 * outer_offset;
        tmp_rect.height = pen;
        if (no_crop)
        {
            instance.driver.fill_f(&tmp_rect, instance.pen.color);                // videti u listeru
            tmp_rect.top_left.y = top_left_y - (inner_offset - 1) + (height - 1); // NOTE: Ivan: da li ce optimizator umeti da ukloni ove jedinice? Tj. da li da je sklonim, ovde stoji zbog citljivosti algoritma.
            instance.driver.fill_f(&tmp_rect, instance.pen.color);
        }
        else
        {
            _rect_fill_crop(&tmp_rect, instance.pen.color);
            tmp_rect.top_left.y = top_left_y - (inner_offset - 1) + (height - 1);
            _rect_fill_crop(&tmp_rect, instance.pen.color);
        }

        // Left and right sides
        tmp_rect.top_left.x = top_left_x - outer_offset;
        tmp_rect.top_left.y = top_left_y + inner_offset; //!<-- we want that first line also to be part of inner pen
        tmp_rect.width  = pen;
        tmp_rect.height = height - 2 * inner_offset;
        if (no_crop)
        {
            instance.driver.fill_f(&tmp_rect, instance.pen.color);
            tmp_rect.top_left.x = top_left_x + (width - 1) - (inner_offset - 1);
            instance.driver.fill_f(&tmp_rect, instance.pen.color);
        }
        else
        {
            _rect_fill_crop(&tmp_rect, instance.pen.color);
            tmp_rect.top_left.x = top_left_x + (width - 1) - (inner_offset - 1);
            _rect_fill_crop(&tmp_rect, instance.pen.color);
        }
    }

    if (instance.brush.style != GL_BRUSH_STYLE_NONE)
    {
        tmp_rect.top_left.x = top_left_x + inner_offset;
        tmp_rect.top_left.y = top_left_y + inner_offset;
        tmp_rect.width  = width - 2 * inner_offset;
        tmp_rect.height = height - 2 * inner_offset;

        if (instance.brush.style == GL_BRUSH_STYLE_FILL)
        {
            if (no_crop)
                instance.driver.fill_f(&tmp_rect, instance.brush.color);
            else
                _rect_fill_crop(&tmp_rect, instance.brush.color);
        }
        else if (instance.brush.style == GL_BRUSH_STYLE_GRADIENT_TOP_DOWN)
            _rect_gradient_crop(&tmp_rect, &tmp_rect, no_crop);
        else
            _rect_gradient_crop(&tmp_rect, &tmp_rect, no_crop);
    }
}

void gl_draw_point(gl_coord_t x, gl_coord_t y)
{
    gl_rectangle_t _rect;
    gl_uint_t pen = instance.pen.inner_width + instance.pen.outer_width;
    gl_int_t outer_offset = instance.pen.outer_width;

    if (!instance.driver.fill_f)
        return;

    _rect.top_left.x = x - outer_offset;
    _rect.top_left.y = y - outer_offset;
    _rect.width  = pen;
    _rect.height = pen;

    _rect_fill_crop(&_rect, instance.pen.color);
}

/*************************************************************************
 * Draw a line between T1(x0,y0) and T2(x1, y1) with outer frame width
 * outter_offset based on pen_width.
 *
 * Algorithm:
 * 1.) If T1 has greater x value then switch its value's with T2.
 * 2.) If line is paralel to x-axis or y-axis then just draw it normally.
 *     And return.
 * 3.) Otherwise, find equation of T1T2 line
 * 4.) Find T'2 which is in T1T2 line, d pixels far away from T2.
 *     Using formulas:
 *        d^2 = (x2-x)^2 + (y2-y)^2     -> d=outer_offset
 *        y-y2 = (y1-y2)/(x1-x2)(x-x2)  -> k=(y1-y2)/(x1-x2)
 *        y-y2 = k*(x-x2)               -> n=y1-k*x1
 *     We get T'2(x,y):
 *        x = d / sqrt(1 + k^2)
 *        y = k*x + n
 * 5.) Find x and y distances for given angle
 * 6.) Find all vertices of rectangle ABCD!
 *
 *     xa = x1 - dx - dy
 *     ya = y1 - dy + dx
 *     xb = x2 + dx - dy
 *     yb = y2 + dy + dx
 *     xc = x2 + dx + dy
 *     yc = y2 + dy - dx
 *     xd = x1 - dx + dy
 *     yd = y1 - dy - dx
 *
 *     t2_prim = (x2 + dx, y2 + dy)
 *     t1_prim = (x1 - dx, y1 - dy)
 * 7.) Check if line is visible, and return if not, otherwise set no_crop parameter
 * 8.) If pen width is lower then 3 then draw only line
 * 9.) Otherwise draw line using two triangle ABC and ADC!
 *************************************************************************/
void gl_draw_line(gl_coord_t x1, gl_coord_t y1, gl_coord_t x2, gl_coord_t y2)
{
    gl_rectangle_t rect;
    gl_int_t outter_offset = instance.pen.outer_width;
    gl_uint_t pen = instance.pen.inner_width + instance.pen.outer_width;
    bool no_crop = true;

    /*********************************************
     * T1(x0,y0) T2(x1, y1)
     *
     * y=kx+n  -> j-na prave kroz ove dve tacke
     * k = (y1 - y0) / (x1 - x0)
     * n = y0 - k * x0
     *********************************************/
    double k_T1T2;
    double n_T1T2;
    double dx;
    double dy;

    gl_point_t t2_prim;
    gl_point_t a;
    gl_point_t b;
    gl_point_t c;
    gl_point_t d;

    if (!instance.driver.fill_f)
        return;

    if (pen == 0)
        return;

    // algorithm step 1
    if (x1 > x2)
    {
        k_T1T2 = x2;
        x2 = x1;
        x1 = k_T1T2;

        k_T1T2 = y2;
        y2 = y1;
        y1 = k_T1T2;
    }

    // algorithm step 2
    if (x1 == x2)
    {
        // set y1 be smaller
        if (y1 > y2)
        {
            k_T1T2 = y2;
            y2 = y1;
            y1 = k_T1T2;
        }

        rect.top_left.x = x1 - outter_offset;
        rect.top_left.y = y1;
        rect.height = (y2 - y1);
        rect.width  = pen;
        _rect_fill_crop(&rect, instance.pen.color);
        return;
    }

    // algorithm step 2
    if (y1 == y2)
    {
        rect.top_left.x = x1;
        rect.top_left.y = y1 - outter_offset;
        rect.width  = (x2 - x1);
        rect.height = pen;
        _rect_fill_crop(&rect, instance.pen.color);
        return;
    }

    outter_offset = pen / 2.0;
    if (outter_offset < 0)
        outter_offset = 0;

    // algorithm step 3
    k_T1T2 = (y2 - y1) / (double) (x2 - x1);
    n_T1T2 = y1 - x1 * k_T1T2;

    // algorithm step 4
    t2_prim.x = x2 + outter_offset / (double) sqrt(1 + k_T1T2*k_T1T2);
    t2_prim.y = k_T1T2 * (x2 + outter_offset / (double) sqrt(1 + k_T1T2*k_T1T2)) + n_T1T2;

    // algorithm step 5
    dx = x2 + outter_offset / (double) sqrt(1 + k_T1T2*k_T1T2) - x2; // t2_prim.x - x2
    dy = k_T1T2 * (x2 + outter_offset / (double) sqrt(1 + k_T1T2*k_T1T2)) + n_T1T2 - y2; // t2_prim.y - y2

    // algorithm step 6
    a.x = x1 - dy;
    a.y = y1 + dx;
    b.x = x2 - dy;
    b.y = y2 + dx;
    c.x = x2 + dy;
    c.y = y2 - dx;
    d.x = x1 + dy;
    d.y = y1 - dx;

    // algorithm step 7
    if ((a.x >= instance.crop_rect.right
        && d.x >= instance.crop_rect.right) ||
        (d.y >= instance.crop_rect.bottom
        && c.y >= instance.crop_rect.bottom) ||
        (c.x < instance.crop_rect.left
        && b.x < instance.crop_rect.left) ||
        (a.y < instance.crop_rect.top
        && b.y < instance.crop_rect.top)
    )
        return; // line is out of area

    no_crop = a.x >= instance.crop_rect.left
              && d.x >= instance.crop_rect.left;
    no_crop = no_crop && d.y >= instance.crop_rect.top
              && c.y >= instance.crop_rect.top;
    no_crop = no_crop && c.x < instance.crop_rect.right
              && b.x < instance.crop_rect.right;
    no_crop = no_crop && a.y < instance.crop_rect.bottom
              && b.y < instance.crop_rect.bottom;

    //algorithm step 7
    if (pen < 3)
    {
        if (abs(x2 - x1) > abs(y2 - y1))
            _draw_diagonal_line_by_x(d.x < a.x ? d : a, d.x < a.x ? c : b, pen, instance.pen.color, no_crop);
        else
            _draw_diagonal_line_by_y(d, c, pen, no_crop);
        return;
    }

    // algorithm step 9
    if (no_crop)
    {
        _draw_triangle_fill(a, b, c, instance.pen.color);
        _draw_triangle_fill(a, c, d, instance.pen.color);
    }
    else
    {
        _draw_triangle_crop(a, b, c, instance.pen.color);
        _draw_triangle_crop(a, c, d, instance.pen.color);
    }
}

gl_int_t _find_circle_line_width(gl_int_t x, gl_int_t y, gl_int_t r_in, gl_int_t r_out)
{
    gl_int_t w = 0;
    gl_int_t y_2 = y * y;
    gl_int_t r_2 = x * x + y_2;

    r_in *= r_in;
    r_out *= r_out;

    while((r_2 >= r_in) && (x > 0))
    {
        x--;
        w++;
        r_2 = x * x + y_2;
    }

    return w;
}

void gl_draw_circle(gl_coord_t x0, gl_coord_t y0, gl_uint_t radius)
{
    gl_int_t inner_offset = instance.pen.inner_width;
    gl_int_t outer_offset = instance.pen.outer_width;

    gl_int_t r_in = radius - inner_offset;
    gl_int_t r_out = radius + outer_offset;
    gl_int_t r_out_2 = r_out * r_out;

    gl_rectangle_t _rect;
    gl_int_t y_2 = 0;
    gl_int_t w = 0;

    _rect.height = 1;

    if (!instance.driver.fill_f)
        return;

    if ((x0 - (gl_int_t) radius - outer_offset >= instance.crop_rect.right)
        || (x0 + (gl_int_t) radius + outer_offset < instance.crop_rect.left)
        || (y0 - (gl_int_t) radius - outer_offset >= instance.crop_rect.bottom)
        || (y0 + (gl_int_t) radius + outer_offset < instance.crop_rect.top))
        return;

    // TODO: Uradi optimizaciju citavog iscrtavanja.
//     if (x0 - r_out < instance.crop_rect.left
//      || x0 + r_out >= instance.crop_rect.right
//      || y0 - r_out < instance.crop_rect.top
//      || y0 + r_out >= instance.crop_rect.bottom)
     {
         gl_arc_t arc;
         arc.radius = r_in;
         arc.center.x = x0;
         arc.center.y = y0;

         _rect.width = _rect.height = 2*r_in;
         _rect.top_left.x = x0 - r_in;
         _rect.top_left.y = y0 - r_in;

         arc.start_angle = 0;
         arc.end_angle = 180;
         _draw_slice_crop(&arc, &_rect);

         arc.start_angle = 180;
         arc.end_angle = 360;
         _draw_slice_crop(&arc, &_rect);
         return;
     }

//     y = 0;
//     x  = r_out;
//     while (y < r_out)
//     {
//         while(((x * x) + y_2) >= r_out_2)
//         {
//             x--;
//         }
//
//         w = _find_circle_line_width(x, y, r_in , r_out);
//         _rect.width  = w;
//
//         _rect.top_left.x = x0 - x;
//         _rect.top_left.y = y0 - y;
//         instance.driver.fill_f(&_rect, instance.pen.color);
//
//         _rect.top_left.y = y0 + y;
//         instance.driver.fill_f(&_rect, instance.pen.color);
//
//         _rect.top_left.x = x0 + x - _rect.width;
//         _rect.top_left.y = y0 - y;
//         instance.driver.fill_f(&_rect, instance.pen.color);
//
//         _rect.top_left.y = y0 + y;
//         instance.driver.fill_f(&_rect, instance.pen.color);
//
//         if (instance.brush.style == GL_BRUSH_STYLE_FILL)
//         {
//             _rect.top_left.x = x0 - x + w;
//             _rect.top_left.y = y0 - y;
//             _rect.width  = 2* x - 2*w;
//             instance.driver.fill_f(&_rect, instance.brush.color);
//
//             _rect.top_left.y = y0 + y;
//             instance.driver.fill_f(&_rect, instance.brush.color);
//         }
//
//         if (instance.brush.style == GL_BRUSH_STYLE_GRADIENT_TOP_DOWN)
//         {
//             _rect.top_left.x = x0 - x + w;
//             _rect.top_left.y = y0 - y;
//             _rect.width  = 2* x - 2*w;
//             instance.driver.fill_f(&_rect, gl_gradient(instance.gradient_color.from, instance.gradient_color.to, 0.5f - ((float)y / r_in * 0.5f)));
//
//             _rect.top_left.y = y0 + y;
//             instance.driver.fill_f(&_rect, gl_gradient(instance.gradient_color.from, instance.gradient_color.to, 0.5f + ((float)y / r_in * 0.5f)));
//         }
//
//         if ((instance.brush.style == GL_BRUSH_STYLE_GRADIENT_LEFT_RIGHT) && (y <= r_in))
//         {
//             _rect.top_left.x = x0 - y;
//             _rect.top_left.y = y0 - x + w;
//             _rect.height = 2* x - 2*w + 1;
//             _rect.width  = 1;
//             instance.driver.fill_f(&_rect, gl_gradient(instance.gradient_color.from, instance.gradient_color.to, 0.5f - ((float)y / r_in * 0.5f)));
//
//             _rect.top_left.x = x0 + y;
//             instance.driver.fill_f(&_rect, gl_gradient(instance.gradient_color.from, instance.gradient_color.to, 0.5f + ((float)y / r_in * 0.5f)));
//
//             _rect.height = 1;
//         }
//
//         y++;
//         y_2 = y * y;
//     }
}

void gl_draw_arc(gl_coord_t x, gl_coord_t y, gl_uint_t radius, gl_angle_t start_angle, gl_angle_t end_angle)
{
    gl_arc_t arc_tmp;
    gl_rectangle_t border_rect;

    int16_t left_border = instance.crop_rect.left;
    int16_t right_border = instance.crop_rect.right;
    int16_t top_border = instance.crop_rect.top;
    int16_t bottom_border = instance.crop_rect.bottom;

    gl_int_t inner_width = instance.pen.inner_width;
    gl_int_t outer_width = instance.pen.outer_width;

    // if arc should be crop, see if it has even one visible part, if not, don't call function for drawing
    bool no_crop_up = true;
    bool no_crop_down = true;
    bool draw_up = true;
    bool draw_down = true;

    if (!instance.driver.fill_f)
        return;

    // crtanje preko slice f-je iziskuje ranije handlovanje
    // inner_offset-a pen-a
    if (inner_width  > radius)
        arc_tmp.radius = 0;
    else
        arc_tmp.radius = radius - inner_width;

    /***************************************************
     * Gradient
     *
     * If there is gradient brush, then for calculating
     * gradient color in exact place, we need border_rect.
     * If this function gets that rectangle already filled
     * with value for height != 0, then we do not change it.
     * Otherwise, we want the gradient to be calculated like
     * there is circle and slice is only shown part.
     ***************************************************/
    border_rect.width = border_rect.height = radius<<1;
    border_rect.top_left.x = (arc_tmp.center.x = x) - arc_tmp.radius;
    border_rect.top_left.y = (arc_tmp.center.y = y) - arc_tmp.radius;

    if (y + (gl_int_t) radius + outer_width < top_border //!<-- here must be used parameter radius, because inner_width can be greater then radius and therefor we can not calculate this value like new_radius + inner_width + outer_width
        || y - (gl_int_t) radius - outer_width >= bottom_border
        || x + (gl_int_t) radius + outer_width < left_border
        || x - (gl_int_t) radius - outer_width >= right_border)
        return;

    if (y < top_border)
        draw_down = no_crop_down = no_crop_up = false;
    else if (y >= bottom_border)
        draw_up = no_crop_down = no_crop_up = false;

    if (y - radius - outer_width < top_border)
        no_crop_down = false;
    else if (y + radius + outer_width >= top_border)
        no_crop_up = false;

    if (x + (gl_int_t) radius + outer_width >= right_border ||
        x - (gl_int_t) radius - outer_width < left_border)
        no_crop_down = no_crop_up = false;

    // zahteva se ceo krug
    if (end_angle == start_angle)
    {
        if (no_crop_down && no_crop_up)
            gl_draw_circle(x, y, radius);
        else
        {
            arc_tmp.start_angle = 0;
            arc_tmp.end_angle = 180;
            if (no_crop_up)
                _draw_slice(&arc_tmp, &border_rect);
            else if (draw_up)
                _draw_slice_crop(&arc_tmp, &border_rect);

            arc_tmp.start_angle = 180;
            arc_tmp.end_angle = 360;
            if (no_crop_down)
                _draw_slice(&arc_tmp, &border_rect);
            else if (draw_down)
                _draw_slice_crop(&arc_tmp, &border_rect);
        }
        return;
    }

    // neregularno stanje
    arc_tmp.start_angle = start_angle % 360;
    arc_tmp.end_angle = end_angle % 360;

    // iscrtavamo odvojeno gornju i donju polovinu kruga
    if (arc_tmp.start_angle < 180)
    {
        if (arc_tmp.end_angle < arc_tmp.start_angle)
        {
            // crtamo: start-180, 180-360, 0-end
            arc_tmp.end_angle = 180;
            if (no_crop_up)
                _draw_slice(&arc_tmp, &border_rect);
            else if (draw_up)
                _draw_slice_crop(&arc_tmp, &border_rect);

            arc_tmp.start_angle = 180;
            arc_tmp.end_angle = 360; //TODO: razmisli o nuli ovde
            if (no_crop_down)
                _draw_slice(&arc_tmp, &border_rect);
            else if (draw_down)
                _draw_slice_crop(&arc_tmp, &border_rect);

            arc_tmp.start_angle = 0;
            arc_tmp.end_angle = end_angle % 360;
            if (no_crop_up)
                _draw_slice(&arc_tmp, &border_rect);
            else if (draw_up)
                _draw_slice_crop(&arc_tmp, &border_rect);

            return;
        }

        if (arc_tmp.end_angle <= 180)
        {
            // crtamo: start-end
            if (no_crop_up)
                _draw_slice(&arc_tmp, &border_rect);
            else if (draw_up)
                _draw_slice_crop(&arc_tmp, &border_rect);

            return;
        }

        // crtamo: start-180, 180-end
        arc_tmp.end_angle = 180;
        if (no_crop_up)
            _draw_slice(&arc_tmp, &border_rect);
        else if (draw_up)
            _draw_slice_crop(&arc_tmp, &border_rect);

        arc_tmp.start_angle = 180;
        arc_tmp.end_angle = end_angle % 360;
        if (no_crop_down)
            _draw_slice(&arc_tmp, &border_rect);
        else if (draw_down)
            _draw_slice_crop(&arc_tmp, &border_rect);

        return;
    }

    // inace je arc_tmp.start_angle >= 180
    if (arc_tmp.end_angle > arc_tmp.start_angle)
    {
        // crtamo: start-end
        if (no_crop_down)
            _draw_slice(&arc_tmp, &border_rect);
        else if (draw_down)
            _draw_slice_crop(&arc_tmp, &border_rect);

        return;
    }

    if (arc_tmp.end_angle > 180)
    {
        // crtamo start-360, 0-180, 180-end
        arc_tmp.end_angle = 360;
        if (no_crop_down)
            _draw_slice(&arc_tmp, &border_rect);
        else if (draw_down)
            _draw_slice_crop(&arc_tmp, &border_rect);

        arc_tmp.start_angle = 0;
        arc_tmp.end_angle = 180; //TODO: razmisli o nuli ovde
        if (no_crop_up)
            _draw_slice(&arc_tmp, &border_rect);
        else if (draw_up)
            _draw_slice_crop(&arc_tmp, &border_rect);

        arc_tmp.start_angle = 180;
        arc_tmp.end_angle = end_angle % 360;
        if (no_crop_down)
            _draw_slice(&arc_tmp, &border_rect);
        else if (draw_down)
            _draw_slice_crop(&arc_tmp, &border_rect);

        return;
    }

    // inace je end <= 180
    // u tom slucaju crtamo start-360, 0-end
    arc_tmp.end_angle = 360;
    if (no_crop_down)
        _draw_slice(&arc_tmp, &border_rect);
    else if (draw_down)
        _draw_slice_crop(&arc_tmp, &border_rect);

    arc_tmp.start_angle = 0;
    arc_tmp.end_angle = end_angle % 360;
    if (no_crop_up)
        _draw_slice(&arc_tmp, &border_rect);
    else if (draw_up)
        _draw_slice_crop(&arc_tmp, &border_rect);
}

#pragma funcall  _draw_rects_quarters _draw_one_color_line, _draw_horizontal_gradient_line, _draw_vertical_gradient_line
static void _draw_rects_quarters(gl_point_t t1, gl_point_t t2, gl_int_t radius, gl_rectangle_t* gradient_border)
{
    void (*fill_f_brush)(gl_rectangle_t*, gl_rectangle_t*);
    gl_rectangle_t rect;
    gl_rectangle_t rect_ring;

    gl_int_t radius1;
    gl_int_t radius2;

    bool no_pen;            // ako je pen.width = 0
    bool has_brush;         // ako je brush_style != none
    bool no_more_brush;     // ako je za crtanje ostao samo pen ili je brush_style = none

    gl_int_t x_right_up;
    gl_int_t x_ring;

    gl_int_t y_temp = 0;
    gl_int_t y_max;
    gl_int_t y_inner_max;

    gl_int_t circle_equation_part; //<-- r^2-(y-y0)^2
    gl_uint_t pen = instance.pen.inner_width + instance.pen.outer_width;

    radius2 = radius;
    radius1 = radius2 + pen;

    // set function for brush color style
    if (instance.brush.style == GL_BRUSH_STYLE_FILL)
        fill_f_brush = &_draw_one_color_line;
    else if (instance.brush.style == GL_BRUSH_STYLE_GRADIENT_LEFT_RIGHT)
        fill_f_brush = &_draw_horizontal_gradient_line;
    else if (instance.brush.style == GL_BRUSH_STYLE_GRADIENT_TOP_DOWN)
        fill_f_brush = &_draw_vertical_gradient_line;

    rect.height = 1;
    rect.top_left.y = t2.y;
    rect.top_left.x = t2.x;
    rect.width = radius2;
    x_right_up = t2.x + radius1;

    rect_ring.height = 1;
    rect_ring.top_left.y = t2.y;
    rect_ring.top_left.x = t2.x + radius2;
    rect_ring.width = radius1 - radius2;
    x_ring = t2.x + radius2;

    y_max = t2.y + radius1;
    y_inner_max = t2.y + radius2;
    no_more_brush = radius2 <= 0;
    no_pen = radius1 == radius2;
    has_brush = instance.brush.style != GL_BRUSH_STYLE_NONE;
    if (!has_brush && no_pen)
        return;

    while (rect.top_left.y < y_max)
    {
        if (no_pen)
        {
            rect.top_left.x = t2.x;
            (*fill_f_brush)(&rect, gradient_border);

            rect.top_left.y = t1.y - y_temp;
            (*fill_f_brush)(&rect, gradient_border);

            rect.top_left.x = t1.x - rect.width;
            (*fill_f_brush)(&rect, gradient_border);

            rect.top_left.y = t2.y + y_temp;
            (*fill_f_brush)(&rect, gradient_border);
        }
        else if (no_more_brush)
        {
            rect.top_left.x = t2.x;
            instance.driver.fill_f(&rect, instance.pen.color);

            rect.top_left.y = t1.y - y_temp;
            instance.driver.fill_f(&rect, instance.pen.color);

            rect.top_left.x = t1.x - rect.width;
            instance.driver.fill_f(&rect, instance.pen.color);

            rect.top_left.y = t2.y + y_temp;
            instance.driver.fill_f(&rect, instance.pen.color);
        }
        else
        {
            rect.top_left.x = t2.x;
            rect_ring.top_left.x = x_ring;
            if (has_brush)
                (*fill_f_brush)(&rect, gradient_border);
            instance.driver.fill_f(&rect_ring, instance.pen.color);

            rect_ring.top_left.y = rect.top_left.y = t1.y - y_temp;
            if (has_brush)
                (*fill_f_brush)(&rect, gradient_border);
            instance.driver.fill_f(&rect_ring, instance.pen.color);

            rect.top_left.x = t1.x - rect.width;
            rect_ring.top_left.x = t1.x - rect_ring.width - rect.width;
            if (has_brush)
                (*fill_f_brush)(&rect, gradient_border);
            instance.driver.fill_f(&rect_ring, instance.pen.color);

            rect_ring.top_left.y = rect.top_left.y = t2.y + y_temp;
            if (has_brush)
                (*fill_f_brush)(&rect, gradient_border);
            instance.driver.fill_f(&rect_ring, instance.pen.color);
        }

        ++y_temp;
        ++rect.top_left.y;

        // find new x
        circle_equation_part = radius1*radius1 - (rect.top_left.y - t2.y)*(rect.top_left.y - t2.y);
        while ((x_right_up - t2.x)*(x_right_up-t2.x) > circle_equation_part)
            x_right_up -= 1;

        // here check the ring values
        if (!no_more_brush)
        {
            rect_ring.top_left.y = rect.top_left.y;
            circle_equation_part = radius2*radius2 - (rect_ring.top_left.y - t2.y)*(rect_ring.top_left.y - t2.y);
            while ((x_ring - t2.x)*(x_ring - t2.x) > circle_equation_part)
                x_ring -= 1;

            rect.width = x_ring - t2.x;
            rect_ring.width = x_right_up - x_ring;

            if (y_inner_max < rect.top_left.y)
            {
                no_more_brush = true;
                rect.width = x_right_up - t2.x;
            }
        }
        else
            rect.width = x_right_up - t2.x;
    }
}

static void _draw_rect_rounded_non_standard( gl_rectangle_t *rect, gl_int_t radius)
{
    gl_rectangle_t rect_tmp;

    //    ------------------------------
    //   |   .(x1,y1)        .(x2,y1)        |
    //   |   .(x1,y2)        .(x2,y2)        |
    //    ------------------------------
    gl_point_t t1;       //!<-- t1(x1,y1)
    gl_point_t t2;       //!<-- t2(x2,y2)

    bool no_crop;
    gl_int_t pen = instance.pen.inner_width + instance.pen.outer_width;

    /*********************
     * Check of validity
     *********************/
    if (instance.brush.style == GL_BRUSH_STYLE_NONE && pen == 0)
        return;

    if (2*radius > rect->width || 2*radius > rect->height)
    {
        if (rect->width < rect->height)
            radius = rect->width >> 1;
        else
            radius = rect->height >> 1;
    }

    t1.x = rect->top_left.x + radius;                 //TODO: proveri da li je brze racunanje, ili prenosenje pokazivaca!
    t2.x = rect->top_left.x + rect->width - radius;
    t1.y = rect->top_left.y + radius - 1;
    t2.y = rect->top_left.y + rect->height - radius;

    no_crop = t1.x - radius - pen >= instance.crop_rect.left
            && t1.y - radius - pen >= instance.crop_rect.top
            && t2.x + radius + pen <= instance.crop_rect.right
            && t2.y + radius + pen <= instance.crop_rect.bottom;

    if (no_crop)
        _draw_rects_quarters(t1, t2, radius, rect);
    else
    {
        gl_arc_t arc;
        arc.radius = radius;

        arc.center = t1;
        arc.start_angle = 180;
        arc.end_angle = 270;
        _draw_slice_crop(&arc, rect);

        arc.center.y = t2.y;
        arc.start_angle = 90;
        arc.end_angle = 180;
        _draw_slice_crop(&arc, rect);

        arc.center.x = t2.x;
        arc.start_angle = 0;
        arc.end_angle = 90;
        _draw_slice_crop(&arc, rect);

        arc.center.y = t1.y;
        arc.start_angle = 270;
        arc.end_angle = 360;
        _draw_slice_crop(&arc, rect);
    }

    if (instance.brush.style == GL_BRUSH_STYLE_FILL)
    {
        // draw inside object
        rect_tmp.height = rect->height;
        rect_tmp.width = rect->width - 2*radius;
        rect_tmp.top_left.y = rect->top_left.y;
        rect_tmp.top_left.x = t1.x;
        if (no_crop)
            instance.driver.fill_f(&rect_tmp, instance.brush.color);
        else
            _rect_fill_crop(&rect_tmp, instance.brush.color);

        rect_tmp.height = rect->height - 2*radius;
        rect_tmp.width = radius;
        rect_tmp.top_left.y = t1.y+1;
        rect_tmp.top_left.x = rect->top_left.x;
        if (no_crop)
            instance.driver.fill_f(&rect_tmp, instance.brush.color);
        else
            _rect_fill_crop(&rect_tmp, instance.brush.color);

        rect_tmp.top_left.x = t2.x;
        if (no_crop)
            instance.driver.fill_f(&rect_tmp, instance.brush.color);
        else
            _rect_fill_crop(&rect_tmp, instance.brush.color);
    }
    else if (instance.brush.style == GL_BRUSH_STYLE_GRADIENT_LEFT_RIGHT)
    {
        // draw inside object
        rect_tmp.height = rect->height - 2*radius;
        rect_tmp.width = radius;
        rect_tmp.top_left.y = t1.y+1;
        rect_tmp.top_left.x = rect->top_left.x;
        _rect_gradient_crop(&rect_tmp, rect, no_crop);

        rect_tmp.top_left.x = t2.x;
        _rect_gradient_crop(&rect_tmp, rect, no_crop);

        rect_tmp.height = rect->height;
        rect_tmp.width = rect->width - 2*radius;
        rect_tmp.top_left.y = rect->top_left.y;
        rect_tmp.top_left.x = t1.x;
        _rect_gradient_crop(&rect_tmp, rect, no_crop);
    }
    else if (instance.brush.style == GL_BRUSH_STYLE_GRADIENT_TOP_DOWN)
    {
        // draw inside object
        rect_tmp.height = radius;
        rect_tmp.width = rect->width - 2*radius;
        rect_tmp.top_left.y = rect->top_left.y;
        rect_tmp.top_left.x = t1.x;
        _rect_gradient_crop(&rect_tmp, rect, no_crop);

        rect_tmp.top_left.y = t2.y;
        _rect_gradient_crop(&rect_tmp, rect, no_crop);

        rect_tmp.height = rect->height - 2*radius;
        rect_tmp.width = rect->width;
        rect_tmp.top_left.y = t1.y+1;
        rect_tmp.top_left.x = rect->top_left.x;
        _rect_gradient_crop(&rect_tmp, rect, no_crop);
    }

    /************
     * Draw pen
     ************/
    if (pen > 0)
    {
        // up
        rect_tmp.height = pen;
        rect_tmp.width = rect->width - 2 * radius;
        rect_tmp.top_left.x = t1.x;
        rect_tmp.top_left.y = rect->top_left.y - pen;
        if (no_crop)
            instance.driver.fill_f(&rect_tmp, instance.pen.color);
        else
            _rect_fill_crop(&rect_tmp, instance.pen.color);

        // down
        rect_tmp.top_left.y = rect->top_left.y + rect->height;
        if (no_crop)
            instance.driver.fill_f(&rect_tmp, instance.pen.color);
        else
            _rect_fill_crop(&rect_tmp, instance.pen.color);

        // left & right
        rect_tmp.height = rect->height - 2*radius + 2;
        rect_tmp.width = pen;
        rect_tmp.top_left.x = rect->top_left.x - pen;
        rect_tmp.top_left.y = t1.y;
        if (no_crop)
        {
            instance.driver.fill_f(&rect_tmp, instance.pen.color);
            rect_tmp.top_left.x = rect->top_left.x + rect->width;
            instance.driver.fill_f(&rect_tmp, instance.pen.color);
        }
        else
        {
            _rect_fill_crop(&rect_tmp, instance.pen.color);
            rect_tmp.top_left.x = rect->top_left.x + rect->width;
            _rect_fill_crop(&rect_tmp, instance.pen.color);
        }
    }
}


void gl_draw_rect_rounded(gl_coord_t x, gl_coord_t y, gl_uint_t width, gl_uint_t height, gl_uint_t radius)
{
    gl_int_t inner_offset = instance.pen.inner_width;

    gl_color_t original_color;
    gl_brush_style_t original_brush_style;

    if (!instance.driver.fill_f)
        return;

    if (inner_offset<<1 < height && inner_offset<<1 <width)
    {
        gl_rectangle_t rect;

        // pripremi vrednosti
        rect.height = height - (inner_offset << 1);
        rect.width = width - (inner_offset << 1);
        rect.top_left.x = x + inner_offset;
        rect.top_left.y = y + inner_offset;

        // iscrtaj
        _draw_rect_rounded_non_standard(&rect, radius);
    }
    else
    {
        gl_rectangle_t rect;
        rect.height = height;
        rect.width = width;
        rect.top_left.x = x;
        rect.top_left.y = y;

        // pripremi vrednosti
        original_color = instance.brush.color;
        original_brush_style = instance.brush.style;

        instance.brush.color = instance.pen.color;
        instance.brush.style = GL_BRUSH_STYLE_FILL;
        instance.pen.inner_width = 0;

        // odradi posao
        _draw_rect_rounded_non_standard(&rect, radius);

        // vrati prosledjene vrednosti
        instance.brush.color = original_color;
        instance.brush.style =  original_brush_style;
        instance.pen.inner_width = inner_offset;
    }
}
