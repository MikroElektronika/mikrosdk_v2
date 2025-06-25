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

void ft800_draw_button( ft800_t *ctx, ft800_cfg_t *cfg, uint16_t *cmdOffset, \
ft800_rounded_button *button )
{
    if ( button->active )
    {
        ft800_read_press_coordinates( ctx, cfg );

        uint16_t x_coordinate = ctx->touch.point[ 0 ].coord_x;
        uint16_t y_coordinate = ctx->touch.point[ 0 ].coord_y;

        gl_set_font( button->text.font.font_data );
        gl_size_t text_size = gl_get_text_dimensions( button->text.caption );

        uint8_t text_height = text_size.height;
        uint8_t text_width = text_size.width;

        if ( button->active )
        {
            if ( !button->press_gradient.transparent )
            {
                if ( ( ( x_coordinate <= ( button->left + button->width ) ) \
                && x_coordinate >= button->left ) && ( ( y_coordinate <= \
                ( button->top + button->height ) ) && \
                y_coordinate >= button->top ) )
                {
                    ft800_draw_gradient_rectangle( ctx, cfg, cmdOffset, button->left, \
                    button->top, button->width - button->pen.width, button->height \
                    - button->pen.width, FT800_BUTTON_RADIUS_SCALE * \
                    button->corner_radius, button->press_gradient.press_start_color, \
                    button->press_gradient.press_end_color, \
                    button->press_gradient.gradient_style );
                }
                else
                {
                    ft800_draw_gradient_rectangle( ctx, cfg, cmdOffset, button->left, \
                    button->top, button->width-button->pen.width, \
                    button->height-button->pen.width, FT800_BUTTON_RADIUS_SCALE * \
                    button->corner_radius, button->press_gradient.start_color, \
                    button->press_gradient.end_color, \
                    button->press_gradient.gradient_style );
                }
            }
            ft800_draw_edges_rectangle( ctx, cfg, cmdOffset, button->left, button->top, \
            button->width, button->height, button->corner_radius, \
            button->pen.color, button->pen.width );
            ft800_cmd( ctx, cfg, FT800_COLOR_RGB( ft800_rgb_convert( button->text.font.color,\
            "red" ), ft800_rgb_convert( button->text.font.color, "green" ), \
            ft800_rgb_convert( button->text.font.color, "blue" ) ), cmdOffset );
            if ( button->vertical_text )
            {
                ft800_draw_vertical_text( ctx, cfg, cmdOffset, button->left, \
                button->top, button->width, button->height, text_height, \
                text_width, button->pen.width, button->text_align, \
                button->text.caption );
            }
            else
            {
                ft800_draw_aligned_text( ctx, cfg, cmdOffset, button->left, \
                button->top, button->width, button->height, text_width, \
                button->text_align, button->pen.width, button->text.caption );
            }
        }
    }
}

void ft800_draw_circle( ft800_t *ctx, ft800_cfg_t *cfg, uint16_t *cmdOffset, \
     ft800_circle *circle )
{
    if ( circle->active )
    {
        ft800_read_press_coordinates( ctx, cfg );

        uint16_t x_coordinate = ctx->touch.point[ 0 ].coord_x;
        uint16_t y_coordinate = ctx->touch.point[ 0 ].coord_y;

        if ( !circle->press_gradient.transparent )
        {
            if ( ( ( x_coordinate <= ( circle->left + FT800_CIRCLE_RADIUS_SCALE * \
            circle->radius ) ) && x_coordinate >= ( circle->left ) ) && \
            ( ( y_coordinate <= ( circle->top + FT800_CIRCLE_RADIUS_SCALE * \
            circle->radius ) ) && y_coordinate >= circle->top ) )
            {
                ft800_draw_gradient_circle( ctx, cfg, cmdOffset, circle->left + \
                circle->radius, circle->top + circle->radius, \
                FT800_CIRCLE_RADIUS_SCALE * circle->radius, \
                circle->press_gradient.press_start_color, \
                circle->press_gradient.press_end_color, \
                circle->press_gradient.gradient_style );
            }
            else
            {
                ft800_draw_gradient_circle( ctx, cfg, cmdOffset, circle->left + \
                circle->radius, circle->top + circle->radius, \
                FT800_CIRCLE_RADIUS_SCALE * circle->radius, \
                circle->press_gradient.start_color, circle->press_gradient.end_color, \
                circle->press_gradient.gradient_style );
            }
        }

        ft800_draw_edges_circle( ctx, cfg, cmdOffset, circle->left + circle->radius, \
        circle->top + circle->radius, FT800_CIRCLE_RADIUS_SCALE * \
        circle->radius, circle->pen.color, circle->pen.width );
    }
}

void ft800_draw_label( ft800_t *ctx, ft800_cfg_t *cfg, uint16_t *cmdOffset, \
     ft800_label *label )
{
    if ( label->active )
    {
        gl_set_font( label->text.font.font_data );
        gl_size_t text_size = gl_get_text_dimensions( label->text.caption );

        uint16_t text_height = text_size.height;
        uint16_t text_width = text_size.width;

        ft800_cmd( ctx, cfg, FT800_COLOR_RGB( ft800_rgb_convert( label->text.font.color, \
        "red" ), ft800_rgb_convert( label->text.font.color, "green" ), \
        ft800_rgb_convert( label->text.font.color, "blue" ) ), cmdOffset );

        if ( label->vertical_text )
        {
            ft800_draw_vertical_text( ctx, cfg, cmdOffset, label->left, label->top, \
            label->width, 0, 0, text_width, 0, FT800_TEXT_ALIGNMENT_LEFT, \
            label->text.caption );
        }
        else
        {
            ft800_draw_aligned_text( ctx, cfg, cmdOffset, label->left, label->top, \
            label->width, label->height, text_height, FT800_TEXT_ALIGNMENT_LEFT, \
            0, label->text.caption );
        }
    }
}


void ft800_draw_line( ft800_t *ctx, ft800_cfg_t *cfg, uint16_t *cmdOffset, ft800_line \
     *line )
{
    ft800_cmd( ctx, cfg, FT800_BEGIN( FT800_LINES ) , cmdOffset );
    ft800_cmd( ctx, cfg, FT800_LINE_WIDTH( line->pen.width * FT800_POINT_SIZE_SCALE ), \
    cmdOffset);
    ft800_cmd( ctx, cfg, FT800_COLOR_RGB( ft800_rgb_convert( line->pen.color, "red" ), \
    ft800_rgb_convert( line->pen.color, "green" ), ft800_rgb_convert( line->pen.color, \
    "blue" ) ), cmdOffset );
    ft800_cmd( ctx, cfg, FT800_VERTEX2F( line->first_left * FT800_POINT_SIZE_SCALE, \
    line->first_top * FT800_POINT_SIZE_SCALE ), cmdOffset );
    ft800_cmd( ctx, cfg, FT800_VERTEX2F( line->second_left * FT800_POINT_SIZE_SCALE, \
    line->second_top * FT800_POINT_SIZE_SCALE ), cmdOffset );
    ft800_cmd( ctx, cfg, FT800_END(), cmdOffset );
}

void ft800_draw_box( ft800_t *ctx, ft800_cfg_t *cfg, uint16_t *cmdOffset, \
     ft800_rounded_box *box )
{
    ft800_read_press_coordinates( ctx, cfg );

    uint16_t x_coordinate = ctx->touch.point[ 0 ].coord_x;
    uint16_t y_coordinate = ctx->touch.point[ 0 ].coord_y;

    if ( box->active )
    {
        if ( !box->press_gradient.transparent )
        {
            if ( ( ( x_coordinate <= ( box->left + box->width ) ) && \
            x_coordinate >= box->left ) && ( ( y_coordinate <= ( box->top + \
            box->height ) ) && y_coordinate >= box->top ) )
            {
                ft800_draw_gradient_rectangle( ctx, cfg, cmdOffset, box->left, box->top,\
                 box->width - box->pen.width, box->height - box->pen.width, \
                 FT800_BOX_RADIUS_SCALE * box->corner_radius, \
                 box->press_gradient.press_start_color, \
                 box->press_gradient.press_end_color, \
                 box->press_gradient.gradient_style );
            }
            else
            {
                ft800_draw_gradient_rectangle( ctx, cfg, cmdOffset, box->left, \
                box->top, box->width - box->pen.width, box->height - \
                box->pen.width, FT800_BOX_RADIUS_SCALE * box->corner_radius, \
                box->press_gradient.start_color, box->press_gradient.end_color, \
                box->press_gradient.gradient_style );
            }
        }

        ft800_draw_edges_rectangle( ctx, cfg, cmdOffset, box->left, box->top, \
        box->width, box->height, box->corner_radius, box->pen.color, \
        box->pen.width );
    }
}


void ft800_draw_progress_bar( ft800_t *ctx, ft800_cfg_t *cfg, uint16_t *cmdOffset, \
     ft800_progress_bar *progress_bar )
{
    if ( !progress_bar->gradient.transparent )
    {
        ft800_draw_gradient_rectangle( ctx, cfg, cmdOffset, progress_bar->left + \
        FT800_PROGRESS_BAR_OFFSET_X_LEFT, progress_bar->top, ( uint16_t )( \
        ( ( float )progress_bar->position / FT800_PROGRESS_BAR_PERCENTAGE_SCALE  \
        ) * ( progress_bar->width -1* FT800_PROGRESS_BAR_OFFSET_X_RIGHT   ) ), \
        progress_bar->height, 0, progress_bar->gradient.end_color, \
        progress_bar->gradient.start_color, progress_bar->gradient.gradient_style );
    }
    else
    {
        ft800_draw_gradient_rectangle( ctx, cfg, cmdOffset, progress_bar->left, \
        progress_bar->top, progress_bar->width, progress_bar->height, \
        progress_bar->corner_radius, progress_bar->back_color, \
        progress_bar->back_color, progress_bar->gradient.gradient_style );
    }
    ft800_draw_edges_rectangle( ctx, cfg, cmdOffset, progress_bar->left, \
    progress_bar->top, progress_bar->width, progress_bar->height, \
    progress_bar->corner_radius, progress_bar->pen.color, progress_bar->pen.width );

    ft800_cmd( ctx, cfg, FT800_BEGIN( FT800_LINES ), cmdOffset );
    ft800_cmd( ctx, cfg, FT800_LINE_WIDTH( progress_bar->pen.width * \
    FT800_POINT_SIZE_SCALE ) , cmdOffset );
    ft800_cmd( ctx, cfg, FT800_VERTEX2F( ( ( progress_bar->left + \
    FT800_PROGRESS_BAR_OFFSET_X_LEFT ) * FT800_POINT_SIZE_SCALE ), \
    progress_bar->top * FT800_POINT_SIZE_SCALE ), cmdOffset );
    ft800_cmd( ctx, cfg, FT800_VERTEX2F( ( (progress_bar->left + \
    FT800_PROGRESS_BAR_OFFSET_X_LEFT ) * FT800_POINT_SIZE_SCALE), \
    ( progress_bar->top + progress_bar->height ) * FT800_POINT_SIZE_SCALE ), \
    cmdOffset );
    ft800_cmd( ctx, cfg, FT800_END(), cmdOffset );
    ft800_cmd( ctx, cfg, FT800_BEGIN( FT800_LINES ), cmdOffset );
    ft800_cmd( ctx, cfg, FT800_VERTEX2F( ( uint16_t )( ( ( float )progress_bar->position \
    / FT800_PROGRESS_BAR_PERCENTAGE_SCALE ) * ( progress_bar->width -1 * \
    FT800_PROGRESS_BAR_OFFSET_X_RIGHT ) + ( progress_bar->left + \
    FT800_PROGRESS_BAR_OFFSET_X_LEFT ) ) * FT800_POINT_SIZE_SCALE, \
    progress_bar->top * FT800_POINT_SIZE_SCALE ), cmdOffset );
    ft800_cmd( ctx, cfg, FT800_VERTEX2F( ( uint16_t )( ( \
    ( float )progress_bar->position / FT800_PROGRESS_BAR_PERCENTAGE_SCALE ) * \
    ( progress_bar->width -1 * FT800_PROGRESS_BAR_OFFSET_X_RIGHT ) + \
    ( progress_bar->left + FT800_PROGRESS_BAR_OFFSET_X_LEFT ) ) * \
    FT800_POINT_SIZE_SCALE, (progress_bar->top + progress_bar->height ) * \
    FT800_POINT_SIZE_SCALE ), cmdOffset );
    ft800_cmd( ctx, cfg, FT800_END(), cmdOffset );

    uint8_t font=(uint8_t)( ( FT800_PROGRESS_BAR_NUMBER_X_POSITION_SCALE_1 ) * \
    ( progress_bar->width -1 * FT800_PROGRESS_BAR_NUMBER_X_POSITION_SCALE_2 ) ) + \
    FT800_PROGRESS_BAR_OFFSET_X_LEFT;

    if ( progress_bar->show_position )
    {
        ft800_cmd( ctx, cfg, FT800_COLOR_RGB( ft800_rgb_convert( progress_bar->font.color, \
        "red" ), ft800_rgb_convert( progress_bar->font.color, "green" ), ft800_rgb_convert( \
        progress_bar->font.color, "blue" ) ), cmdOffset );
        ft800_cmd_number( ctx, cfg, cmdOffset, ( uint16_t )( progress_bar->left + \
        ( float )progress_bar->width / FT800_PROGRESS_BAR_NUMBER_HEIGHT_SCALE -1 \
        * FT800_PROGRESS_BAR_NUMBER_X_OFFSET ), ( uint16_t )( progress_bar->top + \
        ( float )progress_bar->height / FT800_PROGRESS_BAR_NUMBER_HEIGHT_SCALE -1 \
        * FT800_PROGRESS_BAR_NUMBER_Y_OFFSET  ), font, 0, progress_bar->position );
    }

}

void ft800_draw_check_box( ft800_t *ctx, ft800_cfg_t *cfg, uint16_t *cmdOffset, \
     ft800_check_box *check_box )
{
    if ( check_box->active )
    {
        ft800_read_press_coordinates( ctx, cfg );

        uint16_t x_coordinate = ctx->touch.point[ 0 ].coord_x;
        uint16_t y_coordinate = ctx->touch.point[ 0 ].coord_y;

        gl_set_font( check_box->text.font.font_data );
        gl_size_t text_size = gl_get_text_dimensions( check_box->text.caption );

        uint8_t text_height = text_size.height;
        uint8_t text_width = text_size.width;

        if ( FT800_TEXT_ALIGNMENT_RIGHT == check_box->text_align )
        {
            if ( !check_box->press_gradient.transparent )
            {
                if ( ( ( x_coordinate <= ( check_box->left + check_box->width \
                ) ) && x_coordinate >= check_box->left ) && ( ( y_coordinate <= \
                ( check_box->top + check_box->height ) ) && y_coordinate >= \
                check_box->top ) )
                {
                    ft800_draw_gradient_rectangle( ctx, cfg, cmdOffset, check_box->left \
                    + check_box->pen.width, check_box->top + check_box->pen.width, \
                    check_box->height -1 * FT800_CHECK_BOX_PEN_OFFSET_SCALE * \
                    check_box->pen.width, check_box->height -1 * \
                    FT800_CHECK_BOX_PEN_OFFSET_SCALE * check_box->pen.width, \
                    FT800_CHECK_BOX_PEN_OFFSET_SCALE * check_box->corner_radius, \
                    check_box->press_gradient.press_start_color, \
                    check_box->press_gradient.press_end_color, \
                    check_box->press_gradient.gradient_style );
                }
                else
                {
                    ft800_draw_gradient_rectangle( ctx, cfg, cmdOffset, \
                    check_box->left + check_box->pen.width, \
                    check_box->top + check_box->pen.width, check_box->height -1 \
                    * FT800_CHECK_BOX_PEN_OFFSET_SCALE * check_box->pen.width, \
                    check_box->height -1 * FT800_CHECK_BOX_PEN_OFFSET_SCALE * \
                    check_box->pen.width, FT800_CHECK_BOX_PEN_OFFSET_SCALE * \
                    check_box->corner_radius, \
                    check_box->press_gradient.start_color, \
                    check_box->press_gradient.end_color, \
                    check_box->press_gradient.gradient_style );
                }
            }

            ft800_draw_edges_rectangle( ctx, cfg, cmdOffset, check_box->left, \
                check_box->top, check_box->height, check_box->height, \
                check_box->corner_radius, check_box->pen.color, \
                check_box->pen.width );

            ft800_cmd( ctx, cfg, FT800_COLOR_RGB( \
            ft800_rgb_convert( check_box->text.font.color, "red" ), \
            ft800_rgb_convert( check_box->text.font.color, "green" ), \
            ft800_rgb_convert( check_box->text.font.color, "blue" ) ), cmdOffset );
            ft800_draw_aligned_text( ctx, cfg, cmdOffset, check_box->left + \
            check_box->height, check_box->top, check_box->width, \
            check_box->height, text_height, FT800_TEXT_ALIGNMENT_LEFT, \
            check_box->pen.width, check_box->text.caption );
            ft800_cmd( ctx, cfg, FT800_COLOR_RGB( \
            ft800_rgb_convert( check_box->pen.color, "red" ), \
            ft800_rgb_convert( check_box->pen.color, "green" ), \
            ft800_rgb_convert( check_box->pen.color, "blue" ) ), cmdOffset );
            ft800_cmd( ctx, cfg, FT800_LINE_WIDTH( ( uint16_t )( check_box->height \
            / FT800_CHECK_BOX_SIGN_SCALE_1 ) * FT800_POINT_SIZE_SCALE ), \
            cmdOffset );
            ft800_cmd( ctx, cfg, FT800_BEGIN( FT800_LINES ), cmdOffset );
            ft800_cmd( ctx, cfg, FT800_VERTEX2F( ( uint16_t )( check_box->left + \
            ( check_box->height / FT800_CHECK_BOX_SIGN_SCALE_1 ) ) * \
            FT800_POINT_SIZE_SCALE,( uint16_t )( check_box->top + \
            FT800_CHECK_BOX_SIGN_SCALE_3 * check_box->height ) * \
            FT800_POINT_SIZE_SCALE ), cmdOffset );
            ft800_cmd( ctx, cfg, FT800_VERTEX2F( ( uint16_t )( check_box->left + \
            FT800_CHECK_BOX_SIGN_SCALE_2 * check_box->height + \
            check_box->pen.width ) * FT800_POINT_SIZE_SCALE, ( uint16_t )( \
            check_box->top + check_box->height - ( check_box->height / \
            FT800_CHECK_BOX_SIGN_SCALE_1 ) ) * FT800_POINT_SIZE_SCALE ), \
            cmdOffset );
            ft800_cmd( ctx, cfg, FT800_END(), cmdOffset );
            ft800_cmd( ctx, cfg, FT800_BEGIN( FT800_LINES ), cmdOffset );
            ft800_cmd( ctx, cfg, FT800_VERTEX2F( ( uint16_t )( check_box->left + \
            FT800_CHECK_BOX_SIGN_SCALE_2 * check_box->height + \
            check_box->pen.width ) * FT800_POINT_SIZE_SCALE, ( uint16_t )( \
            check_box->top + check_box->height - ( check_box->height / \
            FT800_CHECK_BOX_SIGN_SCALE_1 ) ) * FT800_POINT_SIZE_SCALE ), \
            cmdOffset );
            ft800_cmd( ctx, cfg, FT800_VERTEX2F( ( uint16_t )( check_box->left + \
            check_box->height - ( check_box->height / \
            FT800_CHECK_BOX_SIGN_SCALE_1 ) ) * FT800_POINT_SIZE_SCALE, \
            ( uint16_t )( check_box->top + ( check_box->height / \
            FT800_CHECK_BOX_SIGN_SCALE_1 ) ) * FT800_POINT_SIZE_SCALE ), \
            cmdOffset );
            ft800_cmd( ctx, cfg, FT800_END(), cmdOffset );
        }
        else if ( check_box->text_align == FT800_TEXT_ALIGNMENT_LEFT )
        {
            if ( !check_box->press_gradient.transparent )
            {
                if ( ( ( x_coordinate <= ( check_box->left + check_box->width ) \
                ) && x_coordinate >= check_box->left ) && ( ( y_coordinate <= \
                ( check_box->top + check_box->height ) ) && y_coordinate >= \
                check_box->top ) )
                {
                    ft800_draw_gradient_rectangle( ctx, cfg, cmdOffset, \
                    FT800_CHECK_BOX_SIGN_SCALE_3 * text_width  + check_box->left \
                    + check_box->pen.width, check_box->top + check_box->pen.width, \
                    check_box->height -1 * FT800_CHECK_BOX_PEN_OFFSET_SCALE * \
                    check_box->pen.width, check_box->height -1 * \
                    FT800_CHECK_BOX_PEN_OFFSET_SCALE * check_box->pen.width, \
                    FT800_CHECK_BOX_CORNER_RADIUS_SCALE * \
                    check_box->corner_radius, \
                    check_box->press_gradient.press_start_color, \
                    check_box->press_gradient.press_end_color, \
                    check_box->press_gradient.gradient_style );
                }
                else
                {
                    ft800_draw_gradient_rectangle( ctx, cfg, cmdOffset, \
                    FT800_CHECK_BOX_SIGN_SCALE_3 * text_width  + check_box->left \
                     + check_box->pen.width, check_box->top + check_box->pen.width, \
                     check_box->height -1 * FT800_CHECK_BOX_PEN_OFFSET_SCALE * \
                     check_box->pen.width, check_box->height -1 * \
                     FT800_CHECK_BOX_PEN_OFFSET_SCALE * check_box->pen.width, \
                    FT800_CHECK_BOX_CORNER_RADIUS_SCALE * check_box->corner_radius, \
                    check_box->press_gradient.start_color, \
                    check_box->press_gradient.end_color, \
                    check_box->press_gradient.gradient_style );
                }
            }

            ft800_draw_edges_rectangle( ctx, cfg, cmdOffset, \
            FT800_CHECK_BOX_SIGN_SCALE_3 * text_width + check_box->left, \
            check_box->top, check_box->height, check_box->height, \
            check_box->corner_radius, check_box->pen.color, check_box->pen.width );

            ft800_cmd( ctx, cfg, FT800_COLOR_RGB( \
            ft800_rgb_convert( check_box->text.font.color, "red" ), \
            ft800_rgb_convert( check_box->text.font.color, "green" ), \
            ft800_rgb_convert( check_box->text.font.color, "blue" ) ), cmdOffset );
            ft800_draw_aligned_text( ctx, cfg, cmdOffset, check_box->left, \
            check_box->top, check_box->width, check_box->height, \
            text_height, FT800_TEXT_ALIGNMENT_LEFT, check_box->pen.width, \
            check_box->text.caption );
            ft800_cmd( ctx, cfg, FT800_COLOR_RGB( \
            ft800_rgb_convert( check_box->pen.color, "red" ), \
            ft800_rgb_convert( check_box->pen.color, "green" ), \
            ft800_rgb_convert( check_box->pen.color, "blue" ) ), cmdOffset );
            ft800_cmd( ctx, cfg, FT800_LINE_WIDTH( ( uint16_t )( check_box->height / \
            FT800_CHECK_BOX_SIGN_SCALE_1 ) * FT800_POINT_SIZE_SCALE ) , \
            cmdOffset );
            ft800_cmd( ctx, cfg, FT800_BEGIN( FT800_LINES ), cmdOffset );
            ft800_cmd( ctx, cfg, FT800_VERTEX2F( ( uint16_t )( \
            FT800_CHECK_BOX_SIGN_SCALE_3 * text_width + check_box->left + \
            ( check_box->height /FT800_CHECK_BOX_SIGN_SCALE_1 ) ) * \
            FT800_POINT_SIZE_SCALE, ( uint16_t )( check_box->top + \
            FT800_CHECK_BOX_SIGN_SCALE_3 * check_box->height ) * \
            FT800_POINT_SIZE_SCALE ), cmdOffset );
            ft800_cmd( ctx, cfg, FT800_VERTEX2F( ( uint16_t )( \
            FT800_CHECK_BOX_SIGN_SCALE_3 * text_width + check_box->left + \
            FT800_CHECK_BOX_SIGN_SCALE_2 * check_box->height + \
            check_box->pen.width ) * FT800_POINT_SIZE_SCALE,( uint16_t )( \
            check_box->top + check_box->height - ( check_box->height / \
            FT800_CHECK_BOX_SIGN_SCALE_1 ) ) * FT800_POINT_SIZE_SCALE ), \
            cmdOffset );
            ft800_cmd( ctx, cfg, FT800_END(), cmdOffset );
            ft800_cmd( ctx, cfg, FT800_BEGIN( FT800_LINES ), cmdOffset );
            ft800_cmd( ctx, cfg, FT800_VERTEX2F( ( uint16_t )( \
            FT800_CHECK_BOX_SIGN_SCALE_3 * text_width + check_box->left + \
            FT800_CHECK_BOX_SIGN_SCALE_2 * check_box->height + \
            check_box->pen.width ) *FT800_POINT_SIZE_SCALE, ( uint16_t )( \
            check_box->top + check_box->height - ( check_box->height / \
            FT800_CHECK_BOX_SIGN_SCALE_1 ) ) * FT800_POINT_SIZE_SCALE ), \
            cmdOffset );
            ft800_cmd( ctx, cfg, FT800_VERTEX2F( ( uint16_t )( \
            FT800_CHECK_BOX_SIGN_SCALE_3 * text_width + check_box->left + \
            check_box->height - ( check_box->height / \
            FT800_CHECK_BOX_SIGN_SCALE_1) ) * FT800_POINT_SIZE_SCALE,\
            ( uint16_t )( check_box->top + ( check_box->height / \
            FT800_CHECK_BOX_SIGN_SCALE_1 ) ) * FT800_POINT_SIZE_SCALE ), \
            cmdOffset );
            ft800_cmd( ctx, cfg, FT800_END(), cmdOffset );
        }
    }
}

void ft800_draw_radio_button( ft800_t *ctx, ft800_cfg_t *cfg, uint16_t *cmdOffset, \
     ft800_radio_button *radio_button )
{
    if ( radio_button->active )
    {
        ft800_read_press_coordinates( ctx, cfg );

        uint16_t x_coordinate = ctx->touch.point[ 0 ].coord_x;
        uint16_t y_coordinate = ctx->touch.point[ 0 ].coord_y;

        gl_set_font( radio_button->text.font.font_data );
        gl_size_t text_size = gl_get_text_dimensions( radio_button->text.caption );

        uint8_t text_height = text_size.height;
        uint8_t text_width = text_size.width;

        if ( FT800_TEXT_ALIGNMENT_RIGHT == radio_button->text_align )
        {
            if ( !radio_button->press_gradient.transparent )
            {
                if ( ( ( x_coordinate <= ( radio_button->left + \
                radio_button->width ) ) && ( x_coordinate >= radio_button->left \
                ) ) && ( ( y_coordinate <= ( radio_button->top + \
                radio_button->height ) ) && ( y_coordinate >= radio_button->top ) ) )
                {
                    ft800_draw_gradient_circle( ctx, cfg, cmdOffset, ( uint16_t )( \
                    radio_button->left + ( float )radio_button->height / \
                    FT800_RADIO_BUTTON_CENTER_SCALE_L ), ( uint16_t )( \
                    radio_button->top + ( float )radio_button->height / \
                    FT800_RADIO_BUTTON_CENTER_SCALE_L  ), radio_button->height / \
                    FT800_RADIO_BUTTON_HEIGHT_SCALE_L , \
                    radio_button->press_gradient.press_end_color, \
                    radio_button->press_gradient.press_start_color, \
                    radio_button->press_gradient.gradient_style );
                }
                else
                {
                    ft800_draw_gradient_circle( ctx, cfg, cmdOffset, ( uint16_t )( \
                    radio_button->left + ( float )radio_button->height / \
                    FT800_RADIO_BUTTON_CENTER_SCALE_L  ), ( uint16_t )( \
                    radio_button->top + ( float )radio_button->height / \
                    FT800_RADIO_BUTTON_CENTER_SCALE_L ), radio_button->height / \
                    FT800_RADIO_BUTTON_HEIGHT_SCALE_L , \
                    radio_button->press_gradient.end_color, \
                    radio_button->press_gradient.start_color, \
                    radio_button->press_gradient.gradient_style );
                }
            }

            ft800_draw_edges_circle( ctx, cfg, cmdOffset, ( uint16_t )( \
            radio_button->left + ( float )radio_button->height / \
            FT800_RADIO_BUTTON_CENTER_SCALE_L  ), ( uint16_t )( \
            radio_button->top + ( float )radio_button->height / \
            FT800_RADIO_BUTTON_CENTER_SCALE_L ), radio_button->height, \
            radio_button->pen.color, radio_button->pen.width );
            ft800_draw_edges_circle( ctx, cfg, cmdOffset, ( uint16_t )( \
            radio_button->left + ( float )radio_button->height / \
            FT800_RADIO_BUTTON_CENTER_SCALE_L  ), ( uint16_t )( \
            radio_button->top + ( float )radio_button->height / \
            FT800_RADIO_BUTTON_CENTER_SCALE_L ), radio_button->height / \
            FT800_RADIO_BUTTON_HEIGHT_SCALE_L, radio_button->pen.color, \
            radio_button->pen.width );

            ft800_cmd( ctx, cfg, FT800_COLOR_RGB( ft800_rgb_convert( \
            radio_button->text.font.color, "red" ), ft800_rgb_convert( \
            radio_button->text.font.color, "green" ), ft800_rgb_convert( \
            radio_button->text.font.color, "blue" ) ), cmdOffset );

            ft800_draw_aligned_text( ctx, cfg, cmdOffset, radio_button->left + \
            radio_button->height + radio_button->pen.width * \
            FT800_RADIO_BUTTON_PEN_OFFSET_SCALE, radio_button->top, \
            radio_button->width, radio_button->height, text_height, \
            FT800_TEXT_ALIGNMENT_LEFT, radio_button->pen.width, \
            radio_button->text.caption );
        }
        else if ( FT800_TEXT_ALIGNMENT_LEFT == radio_button->text_align )
        {
            if ( !radio_button->press_gradient.transparent )
            {
                if ( ( ( x_coordinate <= ( radio_button->left + \
                radio_button->width ) ) && ( x_coordinate >= \
                radio_button->left ) ) && ( ( y_coordinate <= ( \
                radio_button->top + radio_button->height ) ) && ( y_coordinate \
                >= radio_button->top ) ) )
                {
                    ft800_draw_gradient_circle( ctx, cfg, cmdOffset, ( uint16_t )( \
                    FT800_RADIO_BUTTON_CENTER_SCALE_R * text_width + \
                    radio_button->left + ( float )radio_button->height / \
                    FT800_RADIO_BUTTON_HEIGHT_SCALE_R ), ( uint16_t )( \
                    radio_button->top + ( float )radio_button->height / \
                    FT800_RADIO_BUTTON_HEIGHT_SCALE_R ), radio_button->height / \
                    FT800_RADIO_BUTTON_HEIGHT_SCALE_R, \
                    radio_button->press_gradient.press_end_color, \
                    radio_button->press_gradient.press_start_color, \
                    radio_button->press_gradient.gradient_style );
                }
                else
                {
                    ft800_draw_gradient_circle( ctx, cfg, cmdOffset, ( uint16_t )( \
                    FT800_RADIO_BUTTON_CENTER_SCALE_R * text_width + \
                    radio_button->left + ( float )radio_button->height / \
                    FT800_RADIO_BUTTON_HEIGHT_SCALE_R ), ( uint16_t )( \
                    radio_button->top + ( float )radio_button->height / \
                    FT800_RADIO_BUTTON_HEIGHT_SCALE_R ), radio_button->height / \
                    FT800_RADIO_BUTTON_HEIGHT_SCALE_R, \
                    radio_button->press_gradient.end_color, \
                    radio_button->press_gradient.start_color, \
                    radio_button->press_gradient.gradient_style );
                }
            }

            ft800_draw_edges_circle( ctx, cfg, cmdOffset, ( uint16_t )( \
            FT800_RADIO_BUTTON_CENTER_SCALE_R * text_width + radio_button->left \
            + ( float )radio_button->height / FT800_RADIO_BUTTON_HEIGHT_SCALE_R ), \
            ( uint16_t )( radio_button->top + ( float )radio_button->height / \
            FT800_RADIO_BUTTON_HEIGHT_SCALE_R ), radio_button->height, \
            radio_button->pen.color, radio_button->pen.width );
            ft800_draw_edges_circle( ctx, cfg, cmdOffset, ( uint16_t )( \
            FT800_RADIO_BUTTON_CENTER_SCALE_R * text_width + radio_button->left \
            + ( float )radio_button->height / FT800_RADIO_BUTTON_HEIGHT_SCALE_R ), \
             ( uint16_t )( radio_button->top + ( float )radio_button->height / \
             FT800_RADIO_BUTTON_HEIGHT_SCALE_R ), radio_button->height / \
             FT800_RADIO_BUTTON_HEIGHT_SCALE_R, radio_button->pen.color, \
             radio_button->pen.width );

            ft800_cmd( ctx, cfg, FT800_COLOR_RGB( \
            ft800_rgb_convert( radio_button->text.font.color, "red" ), \
            ft800_rgb_convert( radio_button->text.font.color, "green" ), \
            ft800_rgb_convert( radio_button->text.font.color, "blue" ) ), cmdOffset );

            ft800_draw_aligned_text( ctx, cfg, cmdOffset, radio_button->left, \
            radio_button->top, radio_button->width, radio_button->height, \
            text_height, FT800_TEXT_ALIGNMENT_LEFT, radio_button->pen.width, \
            radio_button->text.caption );
        }
    }
}

void ft800_draw_ellipse( ft800_t *ctx, ft800_cfg_t *cfg, uint16_t *cmdOffset,ft800_ellipse *ellipse )
{
    if ( ellipse->active )
    {
        ft800_read_press_coordinates( ctx, cfg );

        uint16_t x_coordinate = ctx->touch.point[ 0 ].coord_x;
        uint16_t y_coordinate = ctx->touch.point[ 0 ].coord_y;

        if ( !ellipse->press_gradient.transparent )
        {
            if ( ( ( x_coordinate <= ( ellipse->left + ellipse->width ) ) && \
            x_coordinate >= ellipse->left ) && ( ( y_coordinate <= ( ellipse->top \
                + ellipse->height ) ) && y_coordinate >= ellipse->top ) )
            {
                ft800_draw_gradient_ellipse( ctx, cfg, cmdOffset, ( uint16_t )( \
                    ellipse->left + ( float )ellipse->width / \
                    FT800_ELLIPSE_WIDTH_SCALE ), ( uint16_t )( ellipse->top + \
                        ( float )ellipse->height / FT800_ELLIPSE_HEIGHT_SCALE ), \
                        ellipse->width, ellipse->height, \
                        ellipse->press_gradient.press_end_color, \
                        ellipse->press_gradient.press_start_color, \
                        ellipse->press_gradient.gradient_style );
            }
            else
            {
                ft800_draw_gradient_ellipse( ctx, cfg, cmdOffset, ( uint16_t )( \
                ellipse->left + ( float )ellipse->width / \
                FT800_ELLIPSE_WIDTH_SCALE ), ( uint16_t )(ellipse->top+( \
                float )ellipse->height / FT800_ELLIPSE_HEIGHT_SCALE ), \
                ellipse->width, ellipse->height, ellipse->press_gradient.end_color, \
                ellipse->press_gradient.start_color, \
                ellipse->press_gradient.gradient_style );
            }
        }

        ft800_draw_edges_ellipse( ctx, cfg, cmdOffset, ( uint16_t )( ellipse->left + \
        ( float )ellipse->width / FT800_ELLIPSE_WIDTH_SCALE ), ( uint16_t )( \
        ellipse->top + ( float )ellipse->height / FT800_ELLIPSE_HEIGHT_SCALE ), \
        ellipse->width, ellipse->height, ellipse->pen.color, ellipse->pen.width );
    }
}

void ft800_draw_image( ft800_t *ctx, ft800_cfg_t *cfg, uint16_t *cmdOffset, \
     ft800_image *image )
{
    uint32_t addr_in_ramg = 0x000000;
    uint32_t image_size_bytes = image->width * image->height * \
    FT800_IMAGE_SIZE_CONST_1 + FT800_IMAGE_SIZE_CONST_2;

    if ( !(!ctx || !cfg || !image->picture_data || image_size_bytes) )
    {
        return;
    }

    uint32_t padding = addr_in_ramg % FT800_IMAGE_PADDING_ALIGMENT;

    if ( padding > 0 )
    {
        uint8_t pad[ FT800_IMAGE_PADDING_SIZE ] = { 0 };
        uint32_t pad_len = FT800_IMAGE_PADDING_ALIGMENT - padding;

        ft800_write_ram_g( ctx, cfg, cmdOffset, addr_in_ramg, pad, pad_len );

        addr_in_ramg += pad_len;
    }

    ft800_write_ram_g( ctx, cfg, cmdOffset, addr_in_ramg, image->picture_data, \
    image_size_bytes );

    ft800_cmd( ctx, cfg, FT800_BITMAP_HANDLE( 0 ), cmdOffset );
    ft800_cmd( ctx, cfg, FT800_BITMAP_SOURCE( addr_in_ramg ), cmdOffset );
    ft800_cmd( ctx, cfg, FT800_BITMAP_LAYOUT( FT800_IMAGE_BITMAP_LAYOUT_FORMAT, \
    image->width * FT800_IMAGE_SIZE_CONST_1, image->height ), cmdOffset );
    ft800_cmd( ctx, cfg, FT800_BITMAP_SIZE( 0, 0, 0, image->width, image->height ), \
    cmdOffset );
    ft800_cmd( ctx, cfg, FT800_BEGIN( FT800_BITMAPS ), cmdOffset );
    ft800_cmd( ctx, cfg, FT800_VERTEX2F( image->left * FT800_POINT_SIZE_SCALE, \
    image->top * FT800_POINT_SIZE_SCALE ), cmdOffset );
    ft800_cmd( ctx, cfg, FT800_END(), cmdOffset );
}

uint8_t ft800_rgb_convert( uint16_t color, char *name )
{
    uint8_t red;
    uint8_t green;
    uint8_t blue;

    if ( !strcmp( name, "red" ) )
    {
        red = ( uint8_t )( ( ( color >> FT800_OFFSET_RGB_COLOR_RED ) & \
        FT800_SELECT_LSB_BITS_5 ) * FT800_RGB_RED_SCALE );
        return red;
    }
    if ( !strcmp( name, "green" ) )
    {
        green = ( uint8_t )( ( ( color >> FT800_OFFSET_RGB_COLOR_GREEN  ) & \
        FT800_SELECT_LSB_BITS_6 ) * FT800_RGB_GREEN_SCALE );
        return green;
    }
    if( !strcmp( name, "blue" ) )
    {
        blue = ( uint8_t )( ( color & FT800_SELECT_LSB_BITS_5 ) * \
        FT800_RGB_BLUE_SCALE );
        return blue;
    }
}

void ft800_set_screen_background( ft800_t *ctx, ft800_cfg_t *cfg, \
     uint16_t *cmdOffset, ft800_screen *screen )
{
    ft800_cmd( ctx, cfg, FT800_CLEAR_COLOR_RGB( ft800_rgb_convert( screen->color, "red" ), \
    ft800_rgb_convert( screen->color, "green" ), \
    ft800_rgb_convert( screen->color, "blue" ) ), cmdOffset );
    ft800_cmd( ctx, cfg, FT800_CLEAR( FT800_CLR_BUFF_MASK, FT800_CLR_BUFF_MASK, \
    FT800_CLR_BUFF_MASK ), cmdOffset );
}

void ft800_execute_drawing_process( ft800_t *ctx, ft800_cfg_t *cfg, \
     uint16_t *cmdOffset, uint16_t x_s, uint16_t y_s, uint16_t x_e, \
     uint16_t y_e, uint16_t r_color, uint16_t g_color, uint16_t b_color )
{
    ft800_cmd( ctx, cfg, FT800_COLOR_RGB( r_color, g_color, b_color ), cmdOffset );
    ft800_cmd( ctx, cfg, FT800_BEGIN( FT800_RECTS ), cmdOffset );
    ft800_cmd( ctx, cfg, FT800_VERTEX2F( x_s * FT800_POINT_SIZE_SCALE, y_s * \
    FT800_POINT_SIZE_SCALE ), cmdOffset );
    ft800_cmd( ctx, cfg, FT800_VERTEX2F( x_e * FT800_POINT_SIZE_SCALE, y_e * \
    FT800_POINT_SIZE_SCALE ), cmdOffset );
    ft800_cmd( ctx, cfg, FT800_END(), cmdOffset );
}

void ft800_draw_edges_circle( ft800_t *ctx, ft800_cfg_t *cfg, uint16_t *cmdOffset, \
     uint16_t cx, uint16_t cy, uint16_t width, uint16_t pen_color, uint16_t pen_width )
{
    float a = width / FT800_CIRCLE_EDGES_WIDTH_SCALE;

    ft800_cmd( ctx, cfg, FT800_COLOR_RGB( ft800_rgb_convert( pen_color, "red" ), \
    ft800_rgb_convert( pen_color, "green" ), ft800_rgb_convert( pen_color, "blue" ) ), \
    cmdOffset );
    ft800_cmd( ctx, cfg, FT800_LINE_WIDTH( pen_width * FT800_POINT_SIZE_SCALE ), \
    cmdOffset );
    ft800_cmd( ctx, cfg, FT800_BEGIN( FT800_LINE_STRIP ), cmdOffset );

    uint16_t segments = FT800_CIRCLE_EDGES_SEGMENTS;

    for ( uint16_t i = 0; i <= segments; i++ )
    {
        float theta = ( FT800_CIRCLE_EDGES_THETA_SCALE * i ) / segments;
        float x = cx + a * cos( theta );
        float y = cy + a * sin( theta );

        ft800_cmd( ctx, cfg, FT800_VERTEX2F( ( uint16_t )( x * \
        FT800_POINT_SIZE_SCALE ), ( uint16_t )( y * FT800_POINT_SIZE_SCALE ) ), cmdOffset );
    }

    ft800_cmd( ctx, cfg, FT800_END(), cmdOffset );
}

void ft800_draw_gradient_circle( ft800_t *ctx, ft800_cfg_t *cfg, uint16_t *cmdOffset, \
     uint16_t cx, uint16_t cy, uint16_t width, uint16_t s_color, uint16_t e_color, \
     ft800_gradient_style gradient )
{
    uint8_t red, green, blue;
    uint16_t radius = ( uint16_t )( ( float )width / \
    FT800_CIRCLE_GRADIENT_WIDTH_SCALE ), steps = radius * \
    FT800_CIRCLE_GRADIENT_RADIUS_SCALE;
    int16_t x1, x2, y1, y2, y_top, y_bottom, i;
    float dx, dy, x_offset, y_offset, normalized_x, normalized_y, sqrt_val, t;

    if ( FT800_GRADIENT_BOTTOM_TOP == gradient )
    {
        for ( i = 0; i <= steps; i++ )
        {
            t = ( float )i / steps;
            red = ft800_rgb_convert( e_color, "red" ) + t * ( \
            ft800_rgb_convert( s_color, "red" ) - ft800_rgb_convert( e_color, "red" ) );
            green = ft800_rgb_convert( e_color, "green" ) + t * ( \
            ft800_rgb_convert( s_color, "green" ) - ft800_rgb_convert( e_color, "green" ) );
            blue = ft800_rgb_convert( e_color, "blue" ) + t * ( \
            ft800_rgb_convert( s_color, "blue" ) - ft800_rgb_convert( e_color, "blue" ) );
            y_offset = - radius + ( FT800_CIRCLE_GRADIENT_RADIUS_SCALE * \
            radius * t );
            y1 = cy + ( int16_t )( y_offset );
            y2 = y1 + FT800_CIRCLE_GRADIENT_OFFSET_Y;
            normalized_y = y_offset / radius;
            if ( -1 * FT800_CIRCLE_GRADIENT_NORMAL_VALUE > normalized_y )
                normalized_y = -1 * FT800_CIRCLE_GRADIENT_NORMAL_VALUE;

            if ( FT800_CIRCLE_GRADIENT_NORMAL_VALUE < normalized_y )
                normalized_y = FT800_CIRCLE_GRADIENT_NORMAL_VALUE;

            sqrt_val = FT800_CIRCLE_GRADIENT_NORMAL_VALUE  - ( normalized_y * \
            normalized_y );

            if ( sqrt_val < 0.0 )
                sqrt_val = 0.0;

            dx = radius * sqrt( sqrt_val );
            x1 = cx - ( int16_t )( dx );
            x2 = cx + ( int16_t )( dx );
            if ( x2 > x1 )
                ft800_execute_drawing_process( ctx, cfg, cmdOffset, x1, y1, x2, y2, \
                red, green, blue );
        }
    }
    else if ( FT800_GRADIENT_TOP_BOTTOM == gradient )
    {
        for ( i = 0; i <= steps; i++ )
        {
            t = ( float )i / steps;
            red = ft800_rgb_convert( s_color, "red" ) + t * ( \
            ft800_rgb_convert( e_color, "red" ) - ft800_rgb_convert( s_color, "red" ) );
            green = ft800_rgb_convert( s_color, "green" ) + t * ( \
            ft800_rgb_convert( e_color, "green" ) - ft800_rgb_convert( s_color, "green" ) );
            blue = ft800_rgb_convert( s_color, "blue" ) + t * ( \
            ft800_rgb_convert( e_color, "blue" ) - ft800_rgb_convert( s_color, "blue" ) );
            y_offset = - radius + ( FT800_CIRCLE_GRADIENT_RADIUS_SCALE * \
            radius * t );
            y1 = cy + ( int16_t )( y_offset );
            y2 = y1 + FT800_CIRCLE_GRADIENT_OFFSET_Y;
            normalized_y = y_offset / radius;

            if ( -1 * FT800_CIRCLE_GRADIENT_NORMAL_VALUE > normalized_y )
                normalized_y = -1 * FT800_CIRCLE_GRADIENT_NORMAL_VALUE;

            if ( FT800_CIRCLE_GRADIENT_NORMAL_VALUE < normalized_y )
                normalized_y = FT800_CIRCLE_GRADIENT_NORMAL_VALUE;

            sqrt_val = FT800_CIRCLE_GRADIENT_NORMAL_VALUE - ( normalized_y * \
            normalized_y );

            if ( sqrt_val < 0.0 )
                sqrt_val = 0.0;

            dx = radius * sqrt( sqrt_val );
            x1 = cx - ( int16_t )( dx );
            x2 = cx + ( int16_t )( dx );
            if ( x2 > x1 )
                ft800_execute_drawing_process( ctx, cfg, cmdOffset, x1, y1, x2, y2, \
                red, green, blue );
        }
    }
    else if ( FT800_GRADIENT_RIGHT_LEFT == gradient )
    {
        for ( i = 0; i <= steps; i++ )
        {
            t = ( float )i / steps;
            red = ft800_rgb_convert( e_color,"red" ) + t * ( \
            ft800_rgb_convert( s_color, "red" ) - ft800_rgb_convert( e_color, "red" ) );
            green = ft800_rgb_convert( e_color,"green" ) + t * ( \
            ft800_rgb_convert( s_color, "green" ) - ft800_rgb_convert( e_color, "green" ) );
            blue = ft800_rgb_convert( e_color,"blue" ) + t * ( \
            ft800_rgb_convert( s_color, "blue" ) - ft800_rgb_convert( e_color, "blue" ) );

            x_offset = - radius + ( FT800_CIRCLE_GRADIENT_RADIUS_SCALE * \
            radius * t );
            x1 = cx + ( int16_t )( x_offset );
            x2 = x1 + FT800_CIRCLE_GRADIENT_OFFSET_X;
            normalized_x = x_offset / radius;

            if ( -1 * FT800_CIRCLE_GRADIENT_NORMAL_VALUE > normalized_x )
                normalized_x = -1 * FT800_CIRCLE_GRADIENT_NORMAL_VALUE;

            if ( FT800_CIRCLE_GRADIENT_NORMAL_VALUE < normalized_x )
                normalized_x = FT800_CIRCLE_GRADIENT_NORMAL_VALUE;

            sqrt_val = FT800_CIRCLE_GRADIENT_NORMAL_VALUE - ( normalized_x * \
            normalized_x );

            if ( sqrt_val < 0.0 )
                sqrt_val = 0.0;

            dy = radius * sqrt( sqrt_val );
            y_top = cy - ( int16_t )( dy );
            y_bottom = cy + ( int16_t )( dy );
            if ( y_bottom > y_top )
                ft800_execute_drawing_process( ctx, cfg, cmdOffset, x1, y_top, x2, \
                y_bottom, red, green, blue );
        }
    }
    else if( FT800_GRADIENT_LEFT_RIGHT == gradient )
    {
        for ( i = 0; i <= steps; i++ ) {
            t = ( float )i / steps;
            red = ft800_rgb_convert( s_color, "red" ) + t * ( \
            ft800_rgb_convert( e_color, "red" ) - ft800_rgb_convert( s_color, "red" ) );
            green = ft800_rgb_convert( s_color, "green" ) + t * ( \
            ft800_rgb_convert( e_color, "green" ) - ft800_rgb_convert( s_color, "green" ) );
            blue = ft800_rgb_convert( s_color , "blue" ) + t * ( \
            ft800_rgb_convert( e_color, "blue" ) - ft800_rgb_convert( s_color, "blue" ) );

            x_offset = -1 * radius + ( FT800_CIRCLE_GRADIENT_RADIUS_SCALE * \
            radius * t );
            x1 = cx + ( int16_t )( x_offset );
            x2 = x1 + FT800_CIRCLE_GRADIENT_OFFSET_X;
            normalized_x = x_offset / radius;

            if ( -1 * FT800_CIRCLE_GRADIENT_NORMAL_VALUE > normalized_x )
                normalized_x = -1 * FT800_CIRCLE_GRADIENT_NORMAL_VALUE;

            if ( FT800_CIRCLE_GRADIENT_NORMAL_VALUE < normalized_x )
                normalized_x = FT800_CIRCLE_GRADIENT_NORMAL_VALUE;

            sqrt_val = FT800_CIRCLE_GRADIENT_NORMAL_VALUE - ( normalized_x * \
            normalized_x );

            if ( sqrt_val < 0.0 )
                sqrt_val = 0.0;

            dy = radius * sqrt( sqrt_val );
            y_top = cy - ( int16_t )( dy );
            y_bottom = cy + ( int16_t )( dy );
            if ( y_bottom > y_top )
                ft800_execute_drawing_process( ctx, cfg, cmdOffset, x1, y_top, x2, \
                y_bottom, red, green, blue );
        }
    }
    else if ( FT800_GRADIENT_NONE == gradient )
    {
        uint8_t red = ft800_rgb_convert( s_color, "red" );
        uint8_t green = ft800_rgb_convert( s_color, "green" );
        uint8_t blue = ft800_rgb_convert( s_color, "blue" );

        ft800_cmd( ctx, cfg, FT800_COLOR_RGB( red, green, blue ), cmdOffset );
        ft800_cmd( ctx, cfg, FT800_BEGIN( FT800_POINTS ), cmdOffset );
        ft800_cmd( ctx, cfg, FT800_POINT_SIZE( ( uint16_t )( ( float )width / \
        FT800_CIRCLE_GRADIENT_WIDTH_SCALE ) * FT800_POINT_SIZE_SCALE ), cmdOffset );
        ft800_cmd( ctx, cfg, FT800_VERTEX2F(cx * FT800_POINT_SIZE_SCALE, cy * \
        FT800_POINT_SIZE_SCALE ), cmdOffset );
        ft800_cmd( ctx, cfg, FT800_END(), cmdOffset );
    }
}

void ft800_draw_edges_ellipse(ft800_t *ctx, ft800_cfg_t *cfg, uint16_t *cmdOffset, \
     uint16_t cx, uint16_t cy,uint16_t width, uint16_t height, \
     uint16_t pen_color, uint16_t pen_width)
{
    float a = width / FT800_ELLIPSE_EDGES_WIDTH_SCALE;
    float b = height / FT800_ELLIPSE_EDGES_HEIGHT_SCALE;

    ft800_cmd( ctx, cfg, FT800_COLOR_RGB( ft800_rgb_convert( pen_color, "red" ), \
    ft800_rgb_convert( pen_color, "green" ), ft800_rgb_convert( pen_color, "blue" ) ), \
    cmdOffset );
    ft800_cmd( ctx, cfg, FT800_LINE_WIDTH( pen_width * FT800_POINT_SIZE_SCALE ), \
    cmdOffset );
    ft800_cmd( ctx, cfg, FT800_BEGIN( FT800_LINE_STRIP ), cmdOffset );

    uint16_t segments = FT800_ELLIPSE_EDGES_SEGMENTS;

    for ( uint16_t i = 0; i <= segments; i++ )
    {
        float theta = ( FT800_ELLIPSE_EDGES_THETA_SCALE * i ) / segments;
        float x = cx + a * cos( theta );
        float y = cy + b * sin( theta );

        ft800_cmd( ctx, cfg, FT800_VERTEX2F( ( uint16_t )( x * FT800_POINT_SIZE_SCALE ), \
         ( uint16_t )( y * FT800_POINT_SIZE_SCALE ) ), cmdOffset );
    }

    ft800_cmd( ctx, cfg, FT800_END(), cmdOffset );
}

void ft800_draw_gradient_ellipse( ft800_t *ctx, ft800_cfg_t *cfg, uint16_t *cmdOffset, \
     uint16_t cx, uint16_t cy, uint16_t width, uint16_t height, uint16_t s_color, \
     uint16_t e_color, ft800_gradient_style gradient )
{
    uint8_t red, green, blue, a = width / FT800_ELLIPSE_GRADIENT_WIDTH_SCALE, \
    b = height / FT800_ELLIPSE_GRADIENT_HEIGHT_SCALE, steps = \
    FT800_ELLIPSE_GRADIENT_SEGMENTS, i;
    float t1, t2, x1_offset, x2_offset, y1_offset, y2_offset, normalized_x1, \
    normalized_x2, normalized_y1, normalized_y2, dx1, dx2, dy1, dy2;

    if ( FT800_GRADIENT_TOP_BOTTOM == gradient )
    {
        for ( i = 0; i < steps; i++ )
        {
            t1 = ( float )i / steps;
            t2 = ( float )( i + FT800_ELLIPSE_GRADIENT_INTPOL_OFFSET ) / steps;

            red = ft800_rgb_convert( e_color, "red" ) + t1 * ( \
            ft800_rgb_convert( s_color, "red" ) - ft800_rgb_convert( e_color, "red" ) );
            green = ft800_rgb_convert( e_color, "green" ) + t1 * ( \
            ft800_rgb_convert( s_color, "green" ) - ft800_rgb_convert( e_color, "green" ) );
            blue = ft800_rgb_convert( e_color, "blue" ) + t1 * ( \
            ft800_rgb_convert( s_color, "blue" ) - ft800_rgb_convert( e_color, "blue" ) );

            y1_offset = ( FT800_ELLIPSE_GRADIENT_WIDTH_SCALE * b ) * ( t1 - 0.5 );
            y2_offset = ( FT800_ELLIPSE_GRADIENT_WIDTH_SCALE * b ) * ( t2 - 0.5 );

            normalized_y1 = y1_offset / b;
            normalized_y2 = y2_offset / b;

            if ( -1 * FT800_ELLIPSE_GRADIENT_NORMAL_VALUE > normalized_y1 )
                normalized_y1 = -1 * FT800_ELLIPSE_GRADIENT_NORMAL_VALUE;

            if ( FT800_ELLIPSE_GRADIENT_NORMAL_VALUE < normalized_y1 )
                normalized_y1 = FT800_ELLIPSE_GRADIENT_NORMAL_VALUE;

            if ( -1 * FT800_ELLIPSE_GRADIENT_NORMAL_VALUE > normalized_y2 )
                normalized_y2 = -1 * FT800_ELLIPSE_GRADIENT_NORMAL_VALUE;

            if ( FT800_ELLIPSE_GRADIENT_NORMAL_VALUE < normalized_y2 )
                normalized_y2 = FT800_ELLIPSE_GRADIENT_NORMAL_VALUE;


            dx1 = a * sqrt( FT800_ELLIPSE_GRADIENT_NORMAL_VALUE - normalized_y1 \
            * normalized_y1 );
            dx2 = a * sqrt( FT800_ELLIPSE_GRADIENT_NORMAL_VALUE - normalized_y2 \
            * normalized_y2 );

            int16_t x_left1 = cx - ( int16_t )( dx1 );
            int16_t x_right1 = cx + ( int16_t )( dx1 );
            int16_t x_left2 = cx - ( int16_t )( dx2 );
            int16_t x_right2 = cx + ( int16_t )( dx2 );
            int16_t y1 = cy + ( int16_t )( y1_offset );
            int16_t y2 = cy + ( int16_t )( y2_offset );

            if ( x_right1 > x_left1 && y2 != y1 )
                ft800_execute_drawing_process( ctx, cfg, cmdOffset, x_left1, y1, \
                x_right1, y2, red, green, blue );
        }
    }
    else if ( FT800_GRADIENT_BOTTOM_TOP == gradient )
    {
        for ( i = 0; i < steps; i++ )
        {
            t1 = ( float )i / steps;
            t2 = ( float )( i + FT800_ELLIPSE_GRADIENT_INTPOL_OFFSET ) / steps;

            red = ft800_rgb_convert( s_color, "red" ) + t1 * ( \
            ft800_rgb_convert( e_color, "red" ) - ft800_rgb_convert( s_color, "red" ) );
            green = ft800_rgb_convert( s_color, "green" ) + t1 * ( \
            ft800_rgb_convert( e_color, "green" ) - ft800_rgb_convert( s_color, "green" ) );
            blue = ft800_rgb_convert( s_color, "blue" ) + t1 * ( \
            ft800_rgb_convert( e_color, "blue" ) - ft800_rgb_convert( s_color, "blue" ) );

            y1_offset = ( FT800_ELLIPSE_GRADIENT_WIDTH_SCALE * b ) * ( t1 -1 * \
            FT800_ELLIPSE_GRADIENT_INTPOL_OFFSET_Y );
            y2_offset = ( FT800_ELLIPSE_GRADIENT_WIDTH_SCALE * b ) * ( t2 -1 * \
            FT800_ELLIPSE_GRADIENT_INTPOL_OFFSET_Y );
            normalized_y1 = y1_offset / b;
            normalized_y2 = y2_offset / b;

            if ( -1 * FT800_ELLIPSE_GRADIENT_NORMAL_VALUE > normalized_y1 )
                normalized_y1 = -1 * FT800_ELLIPSE_GRADIENT_NORMAL_VALUE;

            if ( FT800_ELLIPSE_GRADIENT_NORMAL_VALUE < normalized_y1 )
                normalized_y1 = FT800_ELLIPSE_GRADIENT_NORMAL_VALUE;

            if ( -1 * FT800_ELLIPSE_GRADIENT_NORMAL_VALUE > normalized_y2 )
                normalized_y2 = -1 * FT800_ELLIPSE_GRADIENT_NORMAL_VALUE;

            if ( FT800_ELLIPSE_GRADIENT_NORMAL_VALUE < normalized_y2 )
                normalized_y2 = FT800_ELLIPSE_GRADIENT_NORMAL_VALUE;


            dx1 = a * sqrt( FT800_ELLIPSE_GRADIENT_NORMAL_VALUE - normalized_y1 \
            * normalized_y1 );
            dx2 = a * sqrt( FT800_ELLIPSE_GRADIENT_NORMAL_VALUE - normalized_y2 \
            * normalized_y2 );

            int16_t x_left1 = cx - ( int16_t )( dx1 );
            int16_t x_right1 = cx + ( int16_t )( dx1 );
            int16_t x_left2 = cx - ( int16_t )( dx2 );
            int16_t x_right2 = cx + ( int16_t )( dx2 );
            int16_t y1 = cy + ( int16_t )( y1_offset );
            int16_t y2 = cy + ( int16_t )( y2_offset );

            if ( x_right1 > x_left1 && y2 != y1 )
                ft800_execute_drawing_process( ctx, cfg, cmdOffset, x_left1, y1, \
                x_right1, y2, red, green, blue );
        }
    }
    else if( FT800_GRADIENT_LEFT_RIGHT == gradient )
    {
        for ( i = 0; i < steps; i++ )
        {
            t1 = ( float )i / steps;
            t2 = ( float )( i + FT800_ELLIPSE_GRADIENT_INTPOL_OFFSET ) / steps;

            red = ft800_rgb_convert( e_color, "red" ) + t1 * ( \
            ft800_rgb_convert( s_color, "red" ) - ft800_rgb_convert( e_color, "red" ) );
            green = ft800_rgb_convert( e_color, "green" ) + t1 * ( \
            ft800_rgb_convert( s_color, "green" ) - ft800_rgb_convert( e_color, "green" ) );
            blue = ft800_rgb_convert( e_color, "blue" ) + t1 * ( \
            ft800_rgb_convert( s_color, "blue" ) - ft800_rgb_convert( e_color, "blue" ) );

            x1_offset = ( FT800_ELLIPSE_GRADIENT_HEIGHT_SCALE * a ) * ( t1 -1 * \
            FT800_ELLIPSE_GRADIENT_INTPOL_OFFSET_Y );
            x2_offset = ( FT800_ELLIPSE_GRADIENT_HEIGHT_SCALE * a ) * ( t2 -1 * \
            FT800_ELLIPSE_GRADIENT_INTPOL_OFFSET_Y );
            normalized_x1 = x1_offset / a;
            normalized_x2 = x2_offset / a;

            if ( -1 * FT800_ELLIPSE_GRADIENT_NORMAL_VALUE > normalized_x1 )
                normalized_x1 = -1 * FT800_ELLIPSE_GRADIENT_NORMAL_VALUE;

            if ( FT800_ELLIPSE_GRADIENT_NORMAL_VALUE < normalized_x1 )
                normalized_x1 = FT800_ELLIPSE_GRADIENT_NORMAL_VALUE;

            if ( -1 * FT800_ELLIPSE_GRADIENT_NORMAL_VALUE > normalized_x2 )
                normalized_x2 = FT800_ELLIPSE_GRADIENT_NORMAL_VALUE;

            if ( FT800_ELLIPSE_GRADIENT_NORMAL_VALUE < normalized_x2 )
                normalized_x2 = FT800_ELLIPSE_GRADIENT_NORMAL_VALUE;

            dy1 = b * sqrt( FT800_ELLIPSE_GRADIENT_NORMAL_VALUE - normalized_x1 \
            * normalized_x1 );
            dy2 = b * sqrt( FT800_ELLIPSE_GRADIENT_NORMAL_VALUE - normalized_x2 \
            * normalized_x2 );

            int16_t y_top1 = cy - ( int16_t )( dy1 );
            int16_t y_bottom1 = cy + ( int16_t )( dy1 );
            int16_t y_top2 = cy - ( int16_t )( dy2 );
            int16_t y_bottom2 = cy + ( int16_t )( dy2 );
            int16_t x1 = cx + ( int16_t )( x1_offset );
            int16_t x2 = cx + ( int16_t )( x2_offset );

            if ( y_bottom1 > y_top1 && x2 != x1 )
                ft800_execute_drawing_process( ctx, cfg, cmdOffset, x1, y_top1, x2, \
                y_bottom1, red, green, blue );
        }
    }
    else if( FT800_GRADIENT_RIGHT_LEFT == gradient )
    {
        for ( i = 0; i < steps; i++ )
        {
            t1 = ( float )i / steps;
            t2 = ( float )( i + FT800_ELLIPSE_GRADIENT_INTPOL_OFFSET ) / steps;

            red = ft800_rgb_convert( s_color, "red" ) + t1 * ( \
            ft800_rgb_convert( e_color, "red" ) - ft800_rgb_convert( s_color, "red" ) );
            green = ft800_rgb_convert( s_color, "green" ) + t1 * ( \
            ft800_rgb_convert( e_color, "green" ) - ft800_rgb_convert( s_color, "green" ) );
            blue = ft800_rgb_convert( s_color, "blue" ) + t1 * ( \
            ft800_rgb_convert( e_color, "blue" ) - ft800_rgb_convert( s_color, "blue" ) );

            x1_offset = ( FT800_ELLIPSE_GRADIENT_HEIGHT_SCALE * a ) * ( t1 -1 * \
            FT800_ELLIPSE_GRADIENT_INTPOL_OFFSET_Y );
            x2_offset = ( FT800_ELLIPSE_GRADIENT_HEIGHT_SCALE * a ) * ( t2 -1 * \
            FT800_ELLIPSE_GRADIENT_INTPOL_OFFSET_Y );
            normalized_x1 = x1_offset / a;
            normalized_x2 = x2_offset / a;

            if ( -1 * FT800_ELLIPSE_GRADIENT_NORMAL_VALUE > normalized_x1 )
                normalized_x1 = -1 * FT800_ELLIPSE_GRADIENT_NORMAL_VALUE;

            if ( FT800_ELLIPSE_GRADIENT_NORMAL_VALUE < normalized_x1 )
                normalized_x1 = FT800_ELLIPSE_GRADIENT_NORMAL_VALUE;

            if ( -1 * FT800_ELLIPSE_GRADIENT_NORMAL_VALUE > normalized_x2 )
                normalized_x2 = FT800_ELLIPSE_GRADIENT_NORMAL_VALUE;

            if ( FT800_ELLIPSE_GRADIENT_NORMAL_VALUE < normalized_x2 )
                normalized_x2 = FT800_ELLIPSE_GRADIENT_NORMAL_VALUE;

            dy1 = b * sqrt( FT800_ELLIPSE_GRADIENT_NORMAL_VALUE - normalized_x1 \
            * normalized_x1 );
            dy2 = b * sqrt( FT800_ELLIPSE_GRADIENT_NORMAL_VALUE - normalized_x2 \
            * normalized_x2 );

            int16_t y_top1 = cy - ( int16_t )( dy1 );
            int16_t y_bottom1 = cy + ( int16_t )( dy1 );
            int16_t y_top2 = cy - ( int16_t )( dy2 );
            int16_t y_bottom2 = cy + ( int16_t )( dy2 );
            int16_t x1 = cx + ( int16_t )( x1_offset );
            int16_t x2 = cx + ( int16_t )( x2_offset );

            if ( y_bottom1 > y_top1 && x2 != x1 )
                ft800_execute_drawing_process( ctx, cfg, cmdOffset, x1, y_top1, x2, \
                y_bottom1, red, green, blue );
        }
    }
    else if( FT800_GRADIENT_NONE == gradient )
    {
        for ( i = 0; i < steps; i++ )
        {
            t1 = ( float )i / steps;
            t2 = ( float )( i + FT800_ELLIPSE_GRADIENT_INTPOL_OFFSET ) / steps;

            red = ft800_rgb_convert( e_color, "red" );
            green = ft800_rgb_convert( e_color, "green" );
            blue = ft800_rgb_convert( e_color, "blue" );

            y1_offset = ( FT800_ELLIPSE_GRADIENT_WIDTH_SCALE * b ) * ( t1 -1 * \
            FT800_ELLIPSE_GRADIENT_INTPOL_OFFSET_Y );
            y2_offset = ( FT800_ELLIPSE_GRADIENT_WIDTH_SCALE * b ) * ( t2 -1 * \
            FT800_ELLIPSE_GRADIENT_INTPOL_OFFSET_Y );
            normalized_y1 = y1_offset / b;
            normalized_y2 = y2_offset / b;

            if ( -1 * FT800_ELLIPSE_GRADIENT_NORMAL_VALUE > normalized_y1 )
                normalized_y1 = -1 * FT800_ELLIPSE_GRADIENT_NORMAL_VALUE;

            if ( FT800_ELLIPSE_GRADIENT_NORMAL_VALUE < normalized_y1 )
                normalized_y1 = FT800_ELLIPSE_GRADIENT_NORMAL_VALUE;

            if ( -1 * FT800_ELLIPSE_GRADIENT_NORMAL_VALUE > normalized_y2 )
                normalized_y2 = -1 * FT800_ELLIPSE_GRADIENT_NORMAL_VALUE;

            if ( FT800_ELLIPSE_GRADIENT_NORMAL_VALUE < normalized_y2 )
                normalized_y2 = FT800_ELLIPSE_GRADIENT_NORMAL_VALUE;

            dx1 = a * sqrt( FT800_ELLIPSE_GRADIENT_NORMAL_VALUE - normalized_y1 \
            * normalized_y1 );
            dx2 = a * sqrt( FT800_ELLIPSE_GRADIENT_NORMAL_VALUE - normalized_y2 \
            * normalized_y2 );

            int16_t x_left1 = cx - ( int16_t )( dx1 );
            int16_t x_right1 = cx + ( int16_t )( dx1 );
            int16_t x_left2 = cx - ( int16_t )( dx2 );
            int16_t x_right2 = cx + ( int16_t )( dx2 );
            int16_t y1 = cy + ( int16_t )( y1_offset );
            int16_t y2 = cy + ( int16_t )( y2_offset );

            if ( x_right1 > x_left1 && y2 != y1 )
                ft800_execute_drawing_process( ctx, cfg, cmdOffset, x_left1, y1, \
                x_right1, y2, red, green, blue );
        }
    }
}

void ft800_draw_edges_rectangle( ft800_t *ctx, ft800_cfg_t *cfg, uint16_t *cmdOffset, \
     uint16_t x1, uint16_t y1, uint16_t width, uint16_t height, uint16_t radius, \
     uint16_t color, uint8_t pen_width )
{
    uint8_t red = ft800_rgb_convert( color, "red" );
    uint8_t green = ft800_rgb_convert( color, "green" );
    uint8_t blue = ft800_rgb_convert( color, "blue" );
    uint16_t x2 = x1 + width, y2 = y1 + height;
    uint8_t i, segments = FT800_RECTANGLE_EDGES_SEGMENT;
    float theta;

    radius = radius * FT800_RECTANGLE_EDGES_RADIUS_SCALE;

    if ( ( width / FT800_RECTANGLE_EDGES_WIDTH_SCALE) < radius )
        radius = width / FT800_RECTANGLE_EDGES_WIDTH_SCALE;

    if ( ( height / FT800_RECTANGLE_EDGES_HEIGHT_SCALE) < radius )
        radius = ( height / FT800_RECTANGLE_EDGES_HEIGHT_SCALE);

    ft800_cmd( ctx, cfg, FT800_COLOR_RGB( red, green, blue ), cmdOffset );
    ft800_cmd( ctx, cfg, FT800_LINE_WIDTH( pen_width * FT800_POINT_SIZE_SCALE ), \
    cmdOffset );
    ft800_cmd( ctx, cfg, FT800_BEGIN( FT800_LINES ), cmdOffset );
    ft800_cmd( ctx, cfg, FT800_VERTEX2F( ( x1 + radius ) * FT800_POINT_SIZE_SCALE, y1 \
    * FT800_POINT_SIZE_SCALE ), cmdOffset );
    ft800_cmd( ctx, cfg, FT800_VERTEX2F( ( x2 - radius ) * FT800_POINT_SIZE_SCALE, y1 \
    * FT800_POINT_SIZE_SCALE ), cmdOffset );
    ft800_cmd( ctx, cfg, FT800_VERTEX2F( ( x1 + radius ) * FT800_POINT_SIZE_SCALE, y2 \
    * FT800_POINT_SIZE_SCALE ), cmdOffset );
    ft800_cmd( ctx, cfg, FT800_VERTEX2F( ( x2 - radius ) * FT800_POINT_SIZE_SCALE, y2 \
    * FT800_POINT_SIZE_SCALE ), cmdOffset );
    ft800_cmd( ctx, cfg, FT800_VERTEX2F( x1 * FT800_POINT_SIZE_SCALE, ( y1 + radius ) \
    * FT800_POINT_SIZE_SCALE ), cmdOffset );
    ft800_cmd( ctx, cfg, FT800_VERTEX2F( x1 * FT800_POINT_SIZE_SCALE, ( y2 - radius ) \
    * FT800_POINT_SIZE_SCALE ), cmdOffset );
    ft800_cmd( ctx, cfg, FT800_VERTEX2F( x2 * FT800_POINT_SIZE_SCALE, ( y1 + radius ) \
    * FT800_POINT_SIZE_SCALE ), cmdOffset );
    ft800_cmd( ctx, cfg, FT800_VERTEX2F( x2 * FT800_POINT_SIZE_SCALE, ( y2 - radius ) \
    * FT800_POINT_SIZE_SCALE ), cmdOffset );
    ft800_cmd( ctx, cfg, FT800_END(), cmdOffset );
    ft800_cmd( ctx, cfg, FT800_BEGIN( FT800_LINE_STRIP ), cmdOffset );

    for ( i = 0; i <= segments; i++ )
    {
        theta = FT800_RECTANGLE_EDGES_THETA_SCALE * ( i / ( float )segments );

        uint16_t x = ( uint16_t )( x1 + radius - radius * cos( theta ) );
        uint16_t y = ( uint16_t )( y1 + radius - radius * sin( theta ) );

        ft800_cmd( ctx, cfg, FT800_VERTEX2F( x * FT800_POINT_SIZE_SCALE, y * \
            FT800_POINT_SIZE_SCALE ), cmdOffset );
    }

    ft800_cmd( ctx, cfg, FT800_END(), cmdOffset );
    ft800_cmd( ctx, cfg, FT800_BEGIN( FT800_LINE_STRIP ), cmdOffset );

    for ( i = 0; i <= segments; i++ )
    {
        theta = FT800_RECTANGLE_EDGES_THETA_SCALE * ( i / ( float )segments );

        uint16_t x = ( uint16_t )( x2 - radius + radius * sin( theta ) );
        uint16_t y = ( uint16_t )( y1 + radius - radius * cos( theta ) );

        ft800_cmd( ctx, cfg, FT800_VERTEX2F( x * FT800_POINT_SIZE_SCALE, y * \
            FT800_POINT_SIZE_SCALE ), cmdOffset );
    }

    ft800_cmd( ctx, cfg, FT800_END(), cmdOffset );
    ft800_cmd( ctx, cfg, FT800_BEGIN( FT800_LINE_STRIP ), cmdOffset );

    for ( i = 0; i <= segments; i++ )
    {
        theta = FT800_RECTANGLE_EDGES_THETA_SCALE * ( i / ( float )segments );

        uint16_t x = ( uint16_t )(x2 - radius + radius * cos( theta ) );
        uint16_t y = ( uint16_t )(y2 - radius + radius * sin( theta ) );

        ft800_cmd( ctx, cfg, FT800_VERTEX2F( x * FT800_POINT_SIZE_SCALE, y * \
            FT800_POINT_SIZE_SCALE ), cmdOffset );
    }

    ft800_cmd( ctx, cfg, FT800_END(), cmdOffset );
    ft800_cmd( ctx, cfg, FT800_BEGIN( FT800_LINE_STRIP ), cmdOffset );

    for ( i = 0; i <= segments; i++ )
    {
        theta = FT800_RECTANGLE_EDGES_THETA_SCALE * ( i / ( float )segments );

        uint16_t x = ( uint16_t )(x1 + radius - radius * sin( theta ) );
        uint16_t y = ( uint16_t )(y2 - radius + radius * cos( theta ) );

        ft800_cmd( ctx, cfg, FT800_VERTEX2F( x * FT800_POINT_SIZE_SCALE, y * \
            FT800_POINT_SIZE_SCALE ), cmdOffset );
    }

    ft800_cmd( ctx, cfg, FT800_END(), cmdOffset );
}

void ft800_draw_gradient_rectangle( ft800_t *ctx, ft800_cfg_t *cfg, uint16_t \
     *cmdOffset, uint16_t x1, uint16_t y1, uint16_t width, uint16_t height, \
      uint16_t radius, uint16_t s_color, uint16_t e_color, \
      ft800_gradient_style gradient )
{
    uint8_t red, green, blue;
    uint16_t x2 = x1 + width, y2 = y1 + height, i, y_start, y_end, shrink, \
    x_left, x_right, x, x_end, y_top, y_bottom, steps;
    float dy, dx, t;

    if ( ( width / FT800_RECTANGLE_GRADIENT_WIDTH_SCALE ) < radius )
        radius = width / FT800_RECTANGLE_GRADIENT_WIDTH_SCALE;

    if ( ( height / FT800_RECTANGLE_GRADIENT_HEIGHT_SCALE ) < radius )
        radius = height / FT800_RECTANGLE_GRADIENT_HEIGHT_SCALE;

    if( ( FT800_GRADIENT_TOP_BOTTOM == gradient) || ( FT800_GRADIENT_BOTTOM_TOP \
        == gradient ) )
        steps = height;

    else
        steps = width;

    if ( FT800_GRADIENT_BOTTOM_TOP == gradient )
    {
        for ( i = 0; i <= steps; i++ )
        {
            t = ( float )i / steps;

            red = ft800_rgb_convert( e_color, "red" ) + t * ( \
            ft800_rgb_convert( s_color, "red" ) - ft800_rgb_convert( e_color, "red" ) );
            green = ft800_rgb_convert( e_color, "green" ) + t * ( \
            ft800_rgb_convert( s_color, "green" ) - ft800_rgb_convert( e_color, "green" ) );
            blue = ft800_rgb_convert( e_color, "blue" ) + t * ( \
            ft800_rgb_convert( s_color, "blue" ) - ft800_rgb_convert( e_color, "blue" ) );

            y_start = y1 + i;
            y_end = y_start + FT800_RECTANGLE_GRADIENT_OFFSET_Y;
            shrink = 0;

            if ( y_start < y1 + radius )
            {
                dy = ( float )( radius - ( y_start - y1 ) );
                shrink = radius - ( uint16_t )( sqrt( radius * radius - \
                dy * dy ) );
            }
            else if ( y_start > y2 - radius )
            {
                dy = ( float )( y_start - ( y2 - radius ) );
                shrink = radius - ( uint16_t )( sqrt( radius * radius - \
                dy * dy ) );
            }

            x_left = x1 + shrink;
            x_right = x2 - shrink;

            if ( x_right > x_left )
                ft800_execute_drawing_process( ctx, cfg, cmdOffset, x_left, y_start, \
                x_right, y_end, red, green, blue );
        }
    }
    else if ( FT800_GRADIENT_TOP_BOTTOM == gradient )
    {
        for ( i = 0; i <= steps; i++ )
        {
            t = ( float )i / steps;

            red = ft800_rgb_convert( s_color, "red" ) + t * ( \
            ft800_rgb_convert( e_color, "red" ) - ft800_rgb_convert( s_color, "red" ) );
            green = ft800_rgb_convert( s_color, "green" ) + t * ( \
            ft800_rgb_convert( e_color, "green" ) - ft800_rgb_convert( s_color, "green" ) );
            blue = ft800_rgb_convert( s_color, "blue" ) + t * ( \
            ft800_rgb_convert( e_color, "blue" ) - ft800_rgb_convert( s_color, "blue" ) );

            y_start = y1 + i;
            y_end = y_start + FT800_RECTANGLE_GRADIENT_OFFSET_Y;
            shrink = 0;

            if ( y_start < y1 + radius )
            {
                dy = ( float )( radius - ( y_start - y1 ) );
                shrink = radius - ( uint16_t )( sqrt( radius * radius - \
                dy * dy ) );
            }
            else if ( y_start > y2 - radius )
            {
                dy = ( float )( y_start - ( y2 - radius ) );
                shrink = radius - ( uint16_t )( sqrt( radius * radius - \
                dy * dy ) );
            }

            x_left = x1 + shrink;
            x_right = x2 - shrink;

            if ( x_right > x_left )
                ft800_execute_drawing_process( ctx, cfg, cmdOffset, x_left, y_start, \
                x_right, y_end, red, green, blue );
        }
    }
    else if ( FT800_GRADIENT_RIGHT_LEFT == gradient )
    {
        for ( i = 0; i <= steps; i++ )
        {
            t = ( float )i / steps;

            red = ft800_rgb_convert( e_color, "red" ) + t * ( \
            ft800_rgb_convert( s_color, "red" ) - ft800_rgb_convert( e_color, "red" ) );
            green = ft800_rgb_convert( e_color, "green" ) + t * ( \
            ft800_rgb_convert( s_color, "green" ) - ft800_rgb_convert( e_color, "green" ) );
            blue = ft800_rgb_convert( e_color, "blue" ) + t * ( \
            ft800_rgb_convert( s_color, "blue" ) - ft800_rgb_convert( e_color, "blue" ) );

            x = x1 + i;
            x_end = x + FT800_RECTANGLE_GRADIENT_OFFSET_X;
            shrink = 0;
            if ( x < x1 + radius )
            {
                dx = ( float )( radius - ( x - x1 ) );
                shrink = radius - ( uint16_t )( sqrt( radius * radius - dx * dx ) );
            }
            else if ( x > x2 - radius )
            {
                dx = ( float ) (x - ( x2 - radius ) );
                shrink = radius - ( uint16_t )( sqrt( radius * radius - dx * dx ) );
            }

            uint16_t y_top = y1 + shrink;
            uint16_t y_bottom = y2 - shrink;

            if ( y_bottom > y_top )
                ft800_execute_drawing_process( ctx, cfg, cmdOffset, x, y_top, x_end, \
                y_bottom, red, green, blue );
        }
    }

    else if ( FT800_GRADIENT_LEFT_RIGHT == gradient )
    {
        for ( i = 0; i <= steps; i++ )
        {
            t = ( float )i / steps;

            red = ft800_rgb_convert( s_color, "red" ) + t * ( \
            ft800_rgb_convert( e_color, "red" ) - ft800_rgb_convert( s_color, "red" ) );
            green = ft800_rgb_convert( s_color, "green" ) + t * ( \
            ft800_rgb_convert( e_color, "green" ) - ft800_rgb_convert( s_color, "green" ) );
            blue = ft800_rgb_convert( s_color, "blue" ) + t * ( \
            ft800_rgb_convert( e_color, "blue" ) - ft800_rgb_convert( s_color, "blue" ) );

            x = x1 + i;
            x_end = x + FT800_RECTANGLE_GRADIENT_OFFSET_X;
            shrink = 0;

            if ( x < x1 + radius )
            {
                dx = ( float )( radius - ( x - x1 ) );
                shrink = radius - ( uint16_t )( sqrt( radius * radius - dx * dx ) );
            }
            else if ( x > x2 - radius )
            {
                dx = ( float )( x - ( x2 - radius ) );
                shrink = radius - ( uint16_t )( sqrt( radius * radius - dx * dx ) );
            }

            y_top = y1 + shrink;
            y_bottom = y2 - shrink;

            if ( y_bottom > y_top )
                ft800_execute_drawing_process( ctx, cfg, cmdOffset, x, y_top, x_end, \
                y_bottom, red, green, blue );
        }
    }
    else if( FT800_GRADIENT_NONE == gradient )
    {
        for ( i = 0; i <= steps; i++ )
        {
            t = ( float )i / steps;

            red = ft800_rgb_convert( s_color, "red" );
            green = ft800_rgb_convert( s_color, "green" );
            blue = ft800_rgb_convert( s_color, "blue" );

            x = x1 + i;
            x_end = x + FT800_RECTANGLE_GRADIENT_OFFSET_X;
            shrink = 0;

            if ( x < x1 + radius )
            {
                dx = ( float )( radius - ( x - x1 ) );
                shrink = radius - ( uint16_t )( sqrt( radius * radius - dx * dx ) );
            }
            else if ( x > x2 - radius )
            {
                dx = ( float )( x - ( x2 - radius ) );
                shrink = radius - ( uint16_t )( sqrt( radius * radius - dx * dx ) );
            }

            y_top = y1 + shrink;
            y_bottom = y2 - shrink;

            if ( y_bottom > y_top )
                ft800_execute_drawing_process( ctx, cfg, cmdOffset, x, y_top, x_end, \
                y_bottom, red, green, blue );
        }
    }
}

void ft800_draw_aligned_text( ft800_t *ctx, ft800_cfg_t *cfg, uint16_t *cmdOffset, \
     uint16_t x, uint16_t y, uint16_t width, uint16_t height, \
     uint16_t text_height, ft800_text_alignment alignment, uint8_t pen, char *text)
{

    uint8_t font_size;
    uint8_t middle;
    uint8_t letter_width;
    text_height = text_height / strlen( text );

    if ( FT800_TEXT_SIZE_16 >= text_height )
    {
        font_size = FT800_TEXT_FONT_SIZE_26;
        middle = FT800_TEXT_HEIGHT_MIDDLE_26;
        letter_width = FT800_LETTER_WIDTH_26;
    }
    else if ( FT800_TEXT_SIZE_32 >= text_height )
    {
        font_size = FT800_TEXT_FONT_SIZE_27;
        middle = FT800_TEXT_HEIGHT_MIDDLE_27;
        letter_width = FT800_LETTER_WIDTH_27;
    }
    else if ( FT800_TEXT_SIZE_48 >= text_height )
    {
        font_size = FT800_TEXT_FONT_SIZE_28;
        middle = FT800_TEXT_HEIGHT_MIDDLE_28;
        letter_width = FT800_LETTER_WIDTH_28;
    }
    else if ( FT800_TEXT_SIZE_64 >= text_height )
    {
        font_size = FT800_TEXT_FONT_SIZE_29;
        middle = FT800_TEXT_HEIGHT_MIDDLE_29;
        letter_width = FT800_LETTER_WIDTH_29;
    }
    else if ( FT800_TEXT_SIZE_80 >= text_height )
    {
        font_size = FT800_TEXT_FONT_SIZE_30;
        middle = FT800_TEXT_HEIGHT_MIDDLE_30;
        letter_width = FT800_LETTER_WIDTH_30;
    }
    else
    {
        font_size = FT800_TEXT_FONT_SIZE_31;
        middle = FT800_TEXT_HEIGHT_MIDDLE_31;
        letter_width = FT800_LETTER_WIDTH_31;
    }

    uint16_t text_width = letter_width * strlen(text);
    uint16_t center_y = y + height / FT800_TEXT_SCALE_Y - middle;
    uint16_t x_text = x;
    uint16_t y_text = center_y;

    switch ( alignment )
    {
        case FT800_TEXT_ALIGNMENT_LEFT:
            x_text = x + pen;
            break;

        case FT800_TEXT_ALIGNMENT_RIGHT:
            x_text = x + width - text_width;
            break;

        case FT800_TEXT_ALIGNMENT_CENTER:
            x_text = x + ( width - text_width ) / FT800_TEXT_SCALE_X;
            break;

        case FT800_TEXT_ALIGNMENT_TOP:
            x_text = x + ( width - text_width ) / FT800_TEXT_SCALE_X;
            y_text = y + pen;
            break;

        case FT800_TEXT_ALIGNMENT_BOTTOM:
            x_text = x + ( width - text_width ) / FT800_TEXT_SCALE_X;
            y_text = y + height -1 * FT800_TEXT_SCALE_Y * middle -1 * \
            FT800_TEXT_SCALE_Y * pen;
            break;

        default:
            break;
    }

    ft800_cmd_text( ctx, cfg, cmdOffset, x_text, y_text, font_size, 0, text );
}

void ft800_draw_vertical_text( ft800_t *ctx, ft800_cfg_t *cfg, uint16_t *cmdOffset, \
     uint16_t x, uint16_t y, uint16_t width, uint16_t height, uint16_t text_height, \
     uint16_t text_width, uint16_t pen, ft800_text_alignment alignment, char *text )
{

    size_t len = strlen( text );
    uint16_t letter_height = text_width / len;
    uint16_t font_size;
    uint16_t char_height;

    if ( FT800_TEXT_SIZE_16 >= letter_height )
    {
        font_size = FT800_TEXT_FONT_SIZE_26;
        char_height = FT800_CHAR_HEIGHT_26;
        text_height=( uint16_t )( ( float )text_height * \
        FT800_TEXT_HEIGHT_SCALE_16 );
    }
    else if ( FT800_TEXT_SIZE_32 >= letter_height )
    {
        font_size = FT800_TEXT_FONT_SIZE_27;
        char_height = FT800_CHAR_HEIGHT_27;
        text_height=( uint16_t )( ( float )text_height * \
        FT800_TEXT_HEIGHT_SCALE_32 );

    }
    else if ( FT800_TEXT_SIZE_48 >= letter_height )
    {
        font_size = FT800_TEXT_FONT_SIZE_28;
        char_height = FT800_CHAR_HEIGHT_28;
        text_height=( uint16_t )( ( float )text_height * \
        FT800_TEXT_HEIGHT_SCALE_48 );
    }
    else if ( FT800_TEXT_SIZE_64 >= letter_height )
    {
        font_size = FT800_TEXT_FONT_SIZE_29;
        char_height = FT800_CHAR_HEIGHT_29;
        text_height=( uint16_t )( ( float )text_height * \
        FT800_TEXT_HEIGHT_SCALE_64 );
    }
    else if ( FT800_TEXT_SIZE_80 >= letter_height )
    {
        font_size = FT800_TEXT_FONT_SIZE_30;
        char_height = FT800_CHAR_HEIGHT_30;
        text_height=( uint16_t )( ( float )text_height * \
        FT800_TEXT_HEIGHT_SCALE_80 );
    }
    else if ( FT800_TEXT_SIZE_80 < letter_height )
    {
        font_size = FT800_TEXT_FONT_SIZE_31;
        char_height = FT800_CHAR_HEIGHT_31;
        text_height=( uint16_t )( ( float )text_height * \
        FT800_TEXT_HEIGHT_SCALE_80 );
    }

    uint16_t x_text;
    uint16_t y_text = y + ( height - text_height ) / FT800_TEXT_SCALE_Y;

    switch ( alignment )
    {
        case FT800_TEXT_ALIGNMENT_LEFT:
            x_text = x + pen;
            break;
        case FT800_TEXT_ALIGNMENT_CENTER:
            x_text = x + ( width - char_height ) / FT800_TEXT_SCALE_X;
            break;
        case FT800_TEXT_ALIGNMENT_RIGHT:
            x_text = x + width - char_height;
            break;
        default:
            x_text = x;
            break;
    }

    char ch[ 2 ];
    ch[ 1 ] = '\0';

    for ( size_t i = 0; i < len; i++ )
    {
        ch[ 0 ] = text[ i ];
        ft800_cmd_text( ctx, cfg, cmdOffset, x_text, y_text, font_size, 0, ch );
        y_text += char_height;
    }
}

// ------------------------------------------------------------------------- END
