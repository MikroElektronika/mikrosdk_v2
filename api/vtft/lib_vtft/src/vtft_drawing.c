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

#include "vtft_drawing.h"
#include <string.h>
#include "gl.h"
#include "gl_text.h"
#include "gl_shapes.h"
#include "conversions.h"
#include "generic_pointer.h"


// Local Function Definitions

// Set the brush for the given gradient style and colors.
static void _set_gradient_brush(vtft_t *instance,
                                            vtft_gradient_style gradient_style,
                                            vtft_bool_t transparent,
                                            gl_color_t start_color,
                                            gl_color_t end_color)
{
    vtft_bool_t swap_colors;

    if (transparent)
    {
        gl_set_brush_style(GL_BRUSH_STYLE_NONE);
        return;
    }

    swap_colors = 0;
    switch (gradient_style)
    {
        case VTFT_GRADIENT_NONE:
            gl_set_brush_style(GL_BRUSH_STYLE_FILL);
            break;

        case VTFT_GRADIENT_TOP_BOTTOM:
            gl_set_brush_style(GL_BRUSH_STYLE_GRADIENT_TOP_DOWN);
            break;

        case VTFT_GRADIENT_BOTTOM_TOP:
            gl_set_brush_style(GL_BRUSH_STYLE_GRADIENT_TOP_DOWN);
            swap_colors = 1;
            break;

        case VTFT_GRADIENT_LEFT_RIGHT:
            gl_set_brush_style(GL_BRUSH_STYLE_GRADIENT_LEFT_RIGHT);
            break;

        case VTFT_GRADIENT_RIGHT_LEFT:
            gl_set_brush_style(GL_BRUSH_STYLE_GRADIENT_LEFT_RIGHT);
            swap_colors = 1;
            break;
    }

    if (gradient_style == VTFT_GRADIENT_NONE)
    {
        gl_set_brush_color(start_color);
    }
    else
    {
        if (swap_colors == 0)
        {
            gl_set_brush_color_from(start_color);
            gl_set_brush_color_to(end_color);
        }
        else
        {
            gl_set_brush_color_from(end_color);
            gl_set_brush_color_to(start_color);
        }
    }
}

// Sets the brush for painting the given component,
// taking into account whether it is pressed or not.
static void _set_brush(vtft_t *instance, const vtft_colored_component * __generic_ptr colored)
{
    if ((vtft_active_component * __generic_ptr)colored == instance->pressed_component)
        _set_gradient_brush(instance,
            colored->press_gradient.gradient_style,
            colored->press_gradient.transparent,
            colored->press_gradient.press_start_color,
            colored->press_gradient.press_end_color
        );
    else
        _set_gradient_brush(instance,
            colored->press_gradient.gradient_style,
            colored->press_gradient.transparent,
            colored->press_gradient.start_color,
            colored->press_gradient.end_color
        );
}

// Sets the pen for painting the given component.
static void _set_pen(vtft_t *instance, const vtft_colored_component * __generic_ptr colored)
{
    const vtft_pen * __generic_ptr pen;

    pen = &(colored->pen);
    gl_set_pen(pen->color, pen->width);
}

// Sets both the brush and the pen for painting the given component.
static void _set_brush_and_pen(vtft_t *instance, const vtft_colored_component * __generic_ptr colored)
{
    _set_brush(instance, colored);
    _set_pen(instance, colored);
}

// Sets the font for painting the text of the given component.
static void _set_font(vtft_t *instance, const vtft_font * __generic_ptr font, vtft_bool_t vertical)
{
    gl_set_font(font->font_data);
    gl_set_pen(font->color, 1); // gl_set_brush?
    gl_set_font_background(false);
    if (vertical)
        gl_set_font_orientation(GL_FONT_VERTICAL_COLUMN);
    else
        gl_set_font_orientation(GL_FONT_HORIZONTAL);
}

// Draws text that is aligned to one of the given edges.
static void _draw_aligned_text(vtft_t *instance,
    const vtft_text * __generic_ptr text,
    vtft_bool_t vertical_text,
    vtft_text_alignment text_align,
    vtft_coord_t left,
    vtft_coord_t top,
    vtft_ucoord_t width,
    vtft_ucoord_t height)
{
    gl_size_t text_size;

    _set_font(instance, &(text->font), vertical_text);

    text_size = gl_get_text_dimensions(text->caption);

    if (text_align == VTFT_TEXT_ALIGNMENT_LEFT)
        left += 4;
    else if (text_align == VTFT_TEXT_ALIGNMENT_RIGHT)
        left += width - text_size.width - 4;
    else
        left += (vtft_coord_t)(width - text_size.width) / 2;

    if (text_align == VTFT_TEXT_ALIGNMENT_TOP)
        top += 4;
    else if (text_align == VTFT_TEXT_ALIGNMENT_BOTTOM)
        top += height - text_size.height - 4;
    else
        top += (vtft_coord_t)(height - text_size.height) / 2;

    gl_draw_text(text->caption, left, top);
}

// Draws a text for a check box.
static void _draw_check_box_text(vtft_t *instance,
    const vtft_byte_t * __generic_ptr caption, vtft_coord_t left, vtft_coord_t top, vtft_ucoord_t height,  const vtft_font * __generic_ptr font)
{
    gl_size_t text_size;

    // set gl state
    _set_font(instance, font, 0);

    // perform actions
    text_size = gl_get_text_dimensions(caption);
    gl_draw_text(caption, left, top + (height - text_size.height) / 2);
}

// Updates the percentage text of the given progress bar.
static void _update_percentage(vtft_t *instance, vtft_progress_bar *progress_bar)
{
    vtft_ucoord_t local_position;
    gl_size_t text_size;
    char temp[10];

    if (progress_bar->show_position == 0)
        return;

    local_position = (uint32_t)(progress_bar->position - progress_bar->min_position)
        * 100 / (progress_bar->max_position - progress_bar->min_position);
    uint32_to_str(local_position, temp);
    l_trim(temp);
    strcpy(progress_bar->caption, temp);
    if (progress_bar->show_percent != 0)
        strcat(progress_bar->caption, "\%");

    // set gl state
    _set_font(instance, &(progress_bar->font), 0);

    // perform actions
    text_size = gl_get_text_dimensions(progress_bar->caption);
    gl_draw_text(
        progress_bar->caption,
        progress_bar->left + (progress_bar->width - text_size.width) / 2,
        progress_bar->top + (progress_bar->height - text_size.height) / 2
    );
}

// Global Function Definitions

// An empty drawing handle for components with an invalid type.
void _draw_none(vtft_t *instance, const vtft_component * __generic_ptr component)
{
    (void *)instance;
    (void * __generic_ptr)component;
}

// Draws the given box component.
void _draw_box(vtft_t *instance, const vtft_component * __generic_ptr component)
{
    const vtft_box * __generic_ptr box = (const vtft_box * __generic_ptr)component;

    // set gl state
    _set_brush_and_pen(instance, (vtft_colored_component * __generic_ptr)component);

    // perform actions
    gl_draw_rect(box->left, box->top, box->width, box->height);
}

// Draws the given rounded box component.
void _draw_rounded_box(vtft_t *instance, const vtft_component * __generic_ptr component)
{
    const vtft_rounded_box * __generic_ptr rbox = (const vtft_rounded_box * __generic_ptr)component;

    // set gl state
    _set_brush_and_pen(instance, (vtft_colored_component * __generic_ptr)component);

    // perform actions
    gl_draw_rect_rounded(rbox->left, rbox->top, rbox->width, rbox->height, rbox->corner_radius);
}

// Draws the given circle component.
void _draw_circle(vtft_t *instance, const vtft_component * __generic_ptr component)
{
    const vtft_circle * __generic_ptr circle = (const vtft_circle * __generic_ptr)component;

    // set gl state
    _set_brush_and_pen(instance, (vtft_colored_component * __generic_ptr)component);

    // perform actions
    gl_draw_circle((circle->left + circle->radius), (circle->top + circle->radius), circle->radius);
}

// Draws the given ellipse component.
void _draw_ellipse(vtft_t *instance, const vtft_component * __generic_ptr component)
{
    const vtft_ellipse * __generic_ptr ellipse = (const vtft_ellipse * __generic_ptr)component;

    // set gl state
    _set_brush_and_pen(instance, (vtft_colored_component * __generic_ptr)component);

    // perform actions
    gl_draw_ellipse(ellipse->left + ellipse->width / 2, ellipse->top + ellipse->height / 2, ellipse->width / 2, ellipse->height / 2);
}

// Draws the given line component.
void _draw_line(vtft_t *instance, const vtft_component * __generic_ptr component)
{
    const vtft_pen * __generic_ptr pen = &(((const vtft_line * __generic_ptr)component)->pen);
    const vtft_line * __generic_ptr line = (const vtft_line * __generic_ptr)component;

    // set gl state
    gl_set_pen(pen->color, pen->width);

    // perform actions
    gl_draw_line(line->first_left, line->first_top, line->second_left, line->second_top);
}

// Draws the given label component.
void _draw_label(vtft_t *instance, const vtft_component * __generic_ptr component)
{
    const vtft_label * __generic_ptr label = (const vtft_label * __generic_ptr)component;

    // set gl state
    _set_font(instance, &(label->text.font), label->vertical_text);

    // perform actions
    gl_draw_text(label->text.caption, label->left, label->top);
}

// Draws the given button component.
void _draw_button(vtft_t *instance, const vtft_component *__generic_ptr component)
{
    const vtft_button * __generic_ptr button = (const vtft_button * __generic_ptr)component;

    _draw_box(instance, component);
    _draw_aligned_text(
        instance,
        &(button->text),
        button->vertical_text,
        button->text_align,
        button->left,
        button->top,
        button->width,
        button->height
    );
}

// Draws the given rounded button component.
void _draw_rounded_button(vtft_t *instance, const vtft_component * __generic_ptr component)
{
    const vtft_rounded_button * __generic_ptr rounded_button = (const vtft_rounded_button * __generic_ptr)component;

    _draw_rounded_box(instance, component);
    _draw_aligned_text(
        instance,
        &(rounded_button->text),
        rounded_button->vertical_text,
        rounded_button->text_align,
        rounded_button->left,
        rounded_button->top,
        rounded_button->width,
        rounded_button->height
    );
}

// Draws the given circle button component.
void _draw_circle_button(vtft_t *instance, const vtft_component * __generic_ptr component)
{
    const vtft_circle_button * __generic_ptr circle_button = (const vtft_circle_button * __generic_ptr)component;

    _draw_circle(instance, component);
    _draw_aligned_text(
        instance,
        &(circle_button->text),
        circle_button->vertical_text,
        circle_button->text_align,
        circle_button->left,
        circle_button->top,
        circle_button->radius << 1,
        circle_button->radius << 1
    );
}

// Draws the given image component.
void _draw_image(vtft_t *instance, const vtft_component * __generic_ptr component)
{
    const vtft_image * __generic_ptr image = (const vtft_image * __generic_ptr)component;
    gl_rectangle_t rect;

    rect.top_left.x = image->left;
    rect.top_left.y = image->top;
    rect.width      = image->width;
    rect.height     = image->height;

    gl_draw_image(&rect, 0, image->picture_data);
}

// Draws the given check box.
void _draw_check_box(vtft_t *instance, const vtft_component * __generic_ptr component)
{
    const vtft_coord_t font_margin = 5;
    vtft_coord_t left;
    vtft_coord_t top;
    vtft_ucoord_t width;
    vtft_ucoord_t height;
    vtft_ucoord_t corner_radius;
    vtft_coord_t text_left;
    const vtft_check_box * __generic_ptr check_box = (const vtft_check_box * __generic_ptr)component;
    // set gl state
    _set_brush_and_pen(instance, (const vtft_colored_component * __generic_ptr)component);

    // Get the dimensions.
    top = check_box->top;
    width = check_box->width;
    height = check_box->height;
    corner_radius = check_box->corner_radius;
    left = check_box->left;
    if (check_box->text_align == VTFT_TEXT_ALIGNMENT_LEFT)
    {
        text_left = left;
        left += width - height;
    }
    else
    {
        text_left = left + height + font_margin + (check_box->pen.width / 2);
    }

    // Draw the rectangle.
    // perform actions
    if (corner_radius > 0)
        gl_draw_rect_rounded(left, top, height, height - 1, corner_radius);
    else
        gl_draw_rect(left, top, height, height - 1);

    // Draw the checkmark, if the component is checked.
    if (check_box->checked != 0)
    {
        vtft_coord_t line_width = (float)height / (4 * 1.4142135623);
        // set gl state
        gl_set_pen(check_box->pen.color, line_width);
        // perform actions
        gl_draw_line(
            left + 3.f * height / 16.f,
            top + 9.f * height / 16.f,
            left + 7.f * height / 16.f,
            top + 13.f * height / 16.f
        );
        gl_draw_line(
            left + 5.f * height / 16.f,
            top + 13.f * height / 16.f,
            left + 13.f * height / 16.f,
            top + 5.f * height / 16.f
        );
    }

    // Draw the text.
    _draw_check_box_text(instance, check_box->text.caption,
        text_left, top, height, &(check_box->text.font));
}

// Draws the given radio button.
void _draw_radio_button(vtft_t *instance, vtft_component *component)
{
    vtft_coord_t left;
    vtft_coord_t top;
    vtft_ucoord_t width;
    vtft_ucoord_t height;
    vtft_ucoord_t radius;
    vtft_ucoord_t circle_offset;
    vtft_coord_t text_left;
    vtft_radio_button *radio_button = (vtft_radio_button * )component;

    // Get the dimensions.
    top = radio_button->top;
    width = radio_button->width;
    height = radio_button->height;
    radius = height / 2;
    circle_offset = height / 5;
    left = radio_button->left;
    if (radio_button->text_align == VTFT_TEXT_ALIGNMENT_LEFT)
    {
        text_left = left + 3;
        left += width - height;
    }
    else
    {
        text_left = left + height + 3;
    }

    // Draw the outer circle.
    // set gl state
    _set_gradient_brush(instance, VTFT_GRADIENT_NONE,
        radio_button->press_gradient.transparent,
        radio_button->back_color, radio_button->back_color);
    _set_pen(instance, (vtft_colored_component *)component);
    // perform actions
    gl_draw_circle(left + radius, top + radius, radius);

    // Draw the inner circle.
    if (radio_button->checked != 0)
    {
        // set gl state
        _set_brush(instance, (vtft_colored_component *)component);
        // perform actions
        gl_draw_circle(left + radius, top + radius, radius - circle_offset);
    }

    // Draw the text.
    _draw_check_box_text(instance, radio_button->text.caption,
        text_left, top, height, &(radio_button->text.font));
}

// Draws the given progress bar.
void _draw_progress_bar(vtft_t *instance, vtft_component *component)
{
    vtft_progress_bar *progress_bar;
    vtft_gradient *gradient;
    vtft_pen *pen;
    vtft_ucoord_t position;
    uint32_t inner_part;
    gl_coord_t middle;
    uint16_t screen_width, screen_height;
    gl_coord_t top, left, width, height;

    // Get information.
    progress_bar = (vtft_progress_bar *)component;
    gradient = &(progress_bar->gradient);
    pen = &(progress_bar->pen);

    // Set parametars
    gl_set_pen_width(pen->width);
    inner_part = gl_get_inner_pen();
    left = progress_bar->left + inner_part;
    top = progress_bar->top + inner_part;
    width = progress_bar->width - 2 * inner_part;
    height = progress_bar->height - 2 * inner_part;

    // Set pen
    gl_set_pen_color(pen->color);
    gl_set_inner_pen(0);
    gl_set_outer_pen(pen->width);

    // Set locals
    screen_width = gl_get_screen_width();
    screen_height = gl_get_screen_height();

    // Calculate the position of the middle line between filled and empty part
    if (progress_bar->position < progress_bar->max_position)
        position = progress_bar->position;
    else
        position = progress_bar->max_position;

    if (position < progress_bar->min_position)
        position = progress_bar->min_position;

    position = 100 * ((uint32_t) position - progress_bar->min_position) / (progress_bar->max_position - progress_bar->min_position);
    middle = left + (uint32_t)position * width / 100;

    // Draw filled part with pen
    gl_set_crop_borders(0,
                        0,
                        screen_height,
                        middle);

    _set_gradient_brush(instance,
        gradient->gradient_style,
        gradient->transparent,
        gradient->start_color,
        gradient->end_color);

    if (progress_bar->corner_radius == 0)
        gl_draw_rect(left, top, width, height);
    else
        gl_draw_rect_rounded(left, top, width, height, progress_bar->corner_radius);

    // Draw background with pen
    gl_set_crop_borders(middle,
                        0,
                        screen_height,
                        screen_width);

    _set_gradient_brush(instance,
        VTFT_GRADIENT_NONE,
        gradient->transparent,
        progress_bar->back_color,
        progress_bar->back_color);

    if (progress_bar->corner_radius == 0)
        gl_draw_rect(left, top, width, height);
    else
        gl_draw_rect_rounded(left, top, width, height, progress_bar->corner_radius);

    gl_set_crop_borders(0,0, screen_height, screen_width);

    // Draw stripes for non smooth option
     if (progress_bar->smooth == 0)
    {
        vtft_ucoord_t move_offset = 10 + 3;
        vtft_coord_t temp_pos = left + move_offset;
        gl_set_pen_width(0);

        while (temp_pos < middle)
        {
            if (progress_bar->corner_radius != 0)
            {
                gl_set_crop_borders(temp_pos - 3,
                                    0,
                                    screen_height,
                                    temp_pos);

                gl_draw_rect_rounded(left, top, width, height, progress_bar->corner_radius);
            }
            else
                gl_draw_rect(temp_pos - 3,
                            top,
                            3,
                            height);

            temp_pos += move_offset;
        }
        if (temp_pos - middle < 3)
        {
            if (progress_bar->corner_radius != 0)
            {
                gl_set_crop_borders(temp_pos - 3,
                                    0,
                                    screen_height,
                                    middle - temp_pos);

                gl_draw_rect_rounded(left, top, width, height, progress_bar->corner_radius);
            }
            else
                gl_draw_rect(temp_pos - 3,
                         top,
                         middle - temp_pos + 3,
                         height);
        }

        if (progress_bar->corner_radius != 0)
            gl_set_crop_borders(0,0, screen_height, screen_width);
    }

    // Draw the percentage text.
    _update_percentage(instance, progress_bar);
    progress_bar->prev_pos = progress_bar->position;
}


void _update_progress_bar(vtft_t *instance, vtft_progress_bar *progress_bar)
{
    vtft_gradient *gradient;
    vtft_pen *pen;
    vtft_ucoord_t position, tmp;
    uint32_t inner_part;
    gl_coord_t middle, prev_middle;
    uint16_t screen_width, screen_height;
    gl_coord_t top, left, width, height;

    if (progress_bar->visible == 0)
        return;

    // Correct position if needed
    if (progress_bar->position < progress_bar->max_position)
        position = progress_bar->position;
    else
        position = progress_bar->max_position;

    if (position < progress_bar->min_position)
        position = progress_bar->min_position;

    // If nothing's changed return
    if (progress_bar->prev_pos == position)
        return;

    // If component is transparent just draw again
    if (progress_bar->gradient.transparent)
    {
        _draw_progress_bar(instance, (vtft_component *)progress_bar);
        return;
    }

    // Get information.
    gradient = &(progress_bar->gradient);
    pen = &(progress_bar->pen);

    // Set parametars
    gl_set_pen_width(pen->width);
    inner_part = gl_get_inner_pen();
    left = progress_bar->left + inner_part;
    top = progress_bar->top + inner_part;
    width = progress_bar->width - 2 * inner_part;
    height = progress_bar->height - 2 * inner_part;

    // Set pen
    gl_set_pen_width(0);

    // TODO: Store current settings, not default one
    // Set locals
    screen_width = gl_get_screen_width();
    screen_height = gl_get_screen_height();

    // Calculate coordinates of middle and preview middle
    tmp = 100 * ((uint32_t) position - progress_bar->min_position)
        / (progress_bar->max_position - progress_bar->min_position);
    middle = left + (uint32_t)tmp * width / 100;

    tmp = 100 * ((uint32_t) progress_bar->prev_pos - progress_bar->min_position)
        / (progress_bar->max_position - progress_bar->min_position);
    prev_middle = left + (uint32_t)tmp * width / 100;

    if (prev_middle != middle)
    {
        // Draw part between preview and current position

        if (prev_middle < middle)
        {
            // The percentage has been increased
            gl_set_crop_borders(prev_middle, 0, screen_height, middle);

            _set_gradient_brush(instance,
                gradient->gradient_style,
                gradient->transparent,
                gradient->start_color,
                gradient->end_color);
        }
        else /*if (prev_middle > middle)*/
        {
            // The percentage is lower so paint with background over filled part
            gl_set_crop_borders(middle, 0, screen_height, prev_middle);

            _set_gradient_brush(instance,
                VTFT_GRADIENT_NONE,
                gradient->transparent,
                progress_bar->back_color,
                progress_bar->back_color);
        }

        if (progress_bar->corner_radius == 0)
            gl_draw_rect(left, top, width, height);
        else
            gl_draw_rect_rounded(left, top, width, height, progress_bar->corner_radius);
    }

    // Delete old text
    gl_coord_t text_start = 0, text_end, text_top;
    gl_size_t text_size;
    if (progress_bar->show_position)
    {
        // Set gl state
        _set_font(instance, &(progress_bar->font), 0);

        // perform action
        text_size = gl_get_text_dimensions(progress_bar->caption);
        if (text_size.width >  progress_bar->width)
            text_size.width =  progress_bar->width;

        // find position of text
        text_start = progress_bar->left + (progress_bar->width - text_size.width) / 2;
        text_end = text_start + text_size.width;

        text_top = progress_bar->top + (progress_bar->height - text_size.height) / 2;

        gl_coord_t lower = middle < prev_middle ? middle : prev_middle;
        gl_coord_t greater = middle > prev_middle ? middle : prev_middle;

        // Paint filled part
        if (text_start < lower && text_end > greater)
        {
            // In this case we draw left and right of already updated area

            // TODO: When drawing text with gradient implements, delete else branch and allways draw only text

            if (gradient->gradient_style == VTFT_GRADIENT_NONE)
            {
                // If there is not gradient draw exactly the same text with background color
                gl_set_crop_borders(text_start, 0, screen_height, middle);

                // set gl state
                gl_set_pen(gradient->start_color, 1);

                // perform actions
                gl_draw_text(progress_bar->caption, text_start, text_top);
            }
            else
            {
                // Otherwise paint hole rectangle where text is
                gl_coord_t left1 = text_start;
                gl_coord_t top1 = text_top;
                gl_coord_t right1 = lower;
                gl_coord_t bottom1 = top1 + text_size.height;

                gl_set_crop_borders(left1, top1, bottom1, right1);

                _set_gradient_brush(instance,
                    gradient->gradient_style,
                    gradient->transparent,
                    gradient->start_color,
                    gradient->end_color);

                if (progress_bar->corner_radius == 0)
                    gl_draw_rect(left, top, width, height);
                else
                    gl_draw_rect_rounded(left, top, width, height, progress_bar->corner_radius);
            }

            /// Paint background, since it can not be gradiental, overdraw with text
            gl_set_crop_borders(greater, 0, screen_height, text_end);
            gl_set_pen(progress_bar->back_color, 1);
            gl_draw_text(progress_bar->caption, text_start, text_top);
        }
        else if (!(text_start > lower && text_end < greater))
        {
            // In this case there is only one part for overpainting
            gl_coord_t top1 = text_top;
            gl_coord_t bottom1 = top1 + text_size.height;

            gl_coord_t left1, right1;
            if (lower <= text_start)
            {
                left1 = text_start;
                if (text_start < greater)
                    left1 = greater;

                right1 = text_end;

                gl_set_crop_borders(left1, top1, bottom1, right1);
                gl_set_pen(progress_bar->back_color, 1);
                gl_draw_text(progress_bar->caption, text_start, text_top);
            }
            else
            {
                left1 = text_start;
                gl_coord_t width1 = text_end < greater ? text_end : greater;
                width1 -= left1;

                _set_gradient_brush(instance,
                    gradient->gradient_style,
                    gradient->transparent,
                    gradient->start_color,
                    gradient->end_color);

                gl_set_crop_borders(left1, top1, bottom1, left1 + width1);
                if (gradient->gradient_style == VTFT_GRADIENT_NONE)
                {
                    gl_set_pen(gradient->start_color, 1);
                    gl_draw_text(progress_bar->caption, text_start, text_top);
                }
                else
                {
                    // Otherwise paint hole rectangle where text is
                    if (progress_bar->corner_radius == 0)
                        gl_draw_rect(left, top, width, height);
                    else
                        gl_draw_rect_rounded(left, top, width, height, progress_bar->corner_radius);
                }
            }
        }
    }

    gl_set_crop_borders(0,0, screen_height, screen_width);

    // Draw stripes for non smooth option
     if (progress_bar->smooth == 0 && (prev_middle < middle || text_start < middle))
    {
        vtft_ucoord_t move_offset = 10 + 3;
        vtft_coord_t temp_pos;
        _set_gradient_brush(instance,
                VTFT_GRADIENT_NONE,
                gradient->transparent,
                progress_bar->back_color,
                progress_bar->back_color);
        gl_set_pen_width(0);

        gl_coord_t top1, height1;
        for (temp_pos = left + move_offset; temp_pos < middle; temp_pos += move_offset)
        {
            if (temp_pos < prev_middle)
                if (temp_pos < text_start)
                    continue;
                else
                {
                    top1 = text_top;
                    height1 = text_size.height;
                }
            else
            {
                top1 = top;
                height1 = height;
            }

            if (progress_bar->corner_radius != 0)
            {
                gl_set_crop_borders(temp_pos - 3, top1, height1 + top1, temp_pos);
                gl_draw_rect_rounded(left, top, width, height, progress_bar->corner_radius);
            }
            else
                gl_draw_rect(temp_pos - 3, top1, 3, height1);
        }

        if (temp_pos - middle < 3)
        {
            // draw last empty part
            if (progress_bar->corner_radius != 0)
            {
                gl_set_crop_borders(temp_pos - 3, 0, screen_height, middle);
                gl_draw_rect_rounded(left, top, width, height, progress_bar->corner_radius);
            }
            else
                gl_draw_rect(temp_pos - 3, top, 3 - (temp_pos - middle), height);
        }

        if (progress_bar->corner_radius != 0)
            gl_set_crop_borders(0,0, screen_height, screen_width);
    }

    // Draw the percentage text.
    _update_percentage(instance, progress_bar);
    progress_bar->prev_pos = progress_bar->position;
    gl_set_crop_borders(0, 0, screen_height, screen_width);
}
