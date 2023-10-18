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

/**
 * @file gl_shapes.h
 * @brief API for different shape drawing. All function provided here requires setting parameters before call. It can be done by functions from gl.h header.
 */
#ifndef _GL_SHAPES_H_
#define _GL_SHAPES_H_

#include "gl_types.h"

/** @addtogroup apigroup API
 *  @brief API
 *  @{
 */

/**
 * @addtogroup glgroup Graphic Library
 * @brief Graphic Library
 *  @{
 */

#ifdef __cplusplus
extern "C"{
#endif

/**
 * @brief Draws rectangle to displey driver with top left corner positioned at @p top_left_x and @p top_left_y coordinates using pen and brush previously set.
 *
 * @details Coordinates are represented by special type @ref gl_coord_t.
 * Look of the shape can be cusomized using different pen and brush. To see how they can be set, visit gl.h .
 *
 * @param[in] top_left_x X coordinate of rectangle's top and left corner.
 * @param[in] top_left_y Y coordinate of rectangle's top and left corner.
 * @param[in] width Width of rectangle.
 * @param[in] height Height of rectangle.
 *
 * @pre Before calling this function, be sure to initialize driver using @ref gl_set_driver.
 *
 * @sa @ref gl_draw_rect_rounded, @ref gl_set_pen, @ref gl_set_brush_color, @ref gl_set_brush_style
 */
void gl_draw_rect(gl_coord_t top_left_x, gl_coord_t top_left_y, gl_uint_t width, gl_uint_t height);

/**
 * @brief Draw rounded rectangle to diplsay driver using previously set pen and brush.
 *
 * @details Coordinates are represented by special type @ref gl_coord_t.
 *Look of the shape can be cusomized using different pen and brush. To see how they can be set, visit gl.h .
 *
 * @param[in] top_left_x X coordinate of rectangle's top and left corner.
 * @param[in] top_left_y Y coordinate of rectangle's top and left corner.
 * @param[in] width  Width of rectangle.
 * @param[in] height Height of rectangle.
 * @param[in] radius Radius of rounded corners.
 *
 * @pre Before calling this function, be sure to initialize driver using @ref gl_set_driver.
 *
 * @sa @ref gl_draw_rect, @ref gl_set_pen, @ref gl_set_brush_color, @ref gl_set_brush_style, @ref gl_set_brush_color_from, @ref gl_set_brush_color_to.
 */
void gl_draw_rect_rounded(gl_coord_t top_left_x, gl_coord_t top_left_y, gl_uint_t width, gl_uint_t height, gl_uint_t radius);


/**
 * @brief Draw point to display driver using previously set pen.
 *
 * @details Coordinates are represented by special type @ref gl_coord_t.
 * Look of the shape can be cusomized using different pen. To see how they can be set, visit gl.h .
 *
 * @param[in] x X coordinate of point.
 * @param[in] y Y coordinate of point.
 *
 * @pre Before calling this function, be sure to initialize driver using @ref gl_set_driver.
 *
 * @sa @ref gl_draw_line, @ref gl_set_pen_width, @ref gl_set_pen_color.
 */
void gl_draw_point(gl_coord_t x, gl_coord_t y);

/**
 * @brief Draw line AB to display driver using previously set pen.
 *
 * @details Coordinates are represented by special type @ref gl_coord_t.
 *Look of the shape can be cusomized using different pen. To see how they can be set, visit gl.h .
 *
 * @param[in] x1 X coordinate of point A.
 * @param[in] y1 Y coordinate of point A.
 * @param[in] x2 X coordinate of point B.
 * @param[in] y2 Y coordinate of point B.
 *
 * @pre Before calling this function, be sure to initialize driver using @ref gl_set_driver.
 *
 * @sa @ref gl_draw_line, @ref gl_set_pen_width, @ref gl_set_pen_color.
 */
void gl_draw_line(gl_coord_t x1, gl_coord_t y1, gl_coord_t x2, gl_coord_t y2);

/**
 * @brief Draw circleto display driver using previously set pen and brush.
 *
 * @details Coordinates are represented by special type @ref gl_coord_t.
 * Look of the shape can be cusomized using different pen and brush. To see how they can be set, visit gl.h .
 *
 * @param[in] x0 X coordinate of center.
 * @param[in] y0 Y coordinate of center.
 * @param[in] radius Circle radius.
 *
 * @pre Before calling this function, be sure to initialize driver using @ref gl_set_driver.
 *
 * @sa @ref gl_draw_ellipse, @ref gl_draw_arc, @ref gl_set_pen, @ref gl_set_brush_style, @ref gl_set_brush_color, @ref gl_set_brush_color_from, @ref gl_set_brush_color_to.
 */
void gl_draw_circle(gl_coord_t x0, gl_coord_t y0, gl_uint_t radius);

/**
 * @brief Draw ellipse to the display driver using previously set pen and brush.
 *
 * @details Coordinates are represented by special type @ref gl_coord_t.
 * Look of the shape can be cusomized using different pen and brush. To see how they can be set, visit gl.h .
 *
 * @param[in] x0 X coordinate of the center.
 * @param[in] y0 Y coordinate of the center.
 * @param[in] half_a Semi-length on the X axis.
 * @param[in] half_b Semi-length on the Y axis.
 *
 * @pre Before calling this function, be sure to initialize the driver using @ref gl_set_driver.
 *
 * @sa @ref gl_draw_circle, @ref gl_draw_arc, @ref gl_set_pen, @ref gl_set_brush_style, @ref gl_set_brush_color, @ref gl_set_brush_color_from, @ref gl_set_brush_color_to.
 */
void gl_draw_ellipse(gl_coord_t x0, gl_coord_t y0, gl_uint_t half_a, gl_uint_t half_b);

/**
 * \brief Draw arc with center in given @p x and @p y coordinates and @p radius size.
 * The start (end) of the arc is determined by @p start (@p end) angle made with x axis.
 *
 * @details Coordinates are represented by special type @ref gl_coord_t.
 * Look of the shape can be cusomized using different pen and brush. To see how they can be set, visit gl.h .
 *
 * @param[in] x X coordinate of center.
 * @param[in] y y coordinate of center.
 * @param[in] radius radius of arc.
 * @param[in] start the angle made with x axis which determins where arc stars.
 * @param[in] end the angle made withh x axis which determins where do arc ends.
 *
 * @pre Before calling this function, be sure to initialize driver using @ref gl_set_driver.
 *
 * @sa @ref gl_draw_circle, @ref gl_set_pen, @ref gl_set_brush_style, @ref gl_set_brush_color, @ref gl_set_brush_color_from, @ref gl_set_brush_color_to.
 */
void gl_draw_arc(gl_coord_t x, gl_coord_t y, gl_uint_t radius, gl_angle_t start, gl_angle_t end);

#ifdef __cplusplus
} // extern "C"
#endif

/** @} */ // glgroup
/** @} */ // apigroup

#endif // _GL_SHAPES_H_
// ------------------------------------------------------------------------- END
