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
 * @file gl_types.h
 * @brief Declaration of types for Graphic Library.
 */


#ifndef _GL_TYPES_H_
#define _GL_TYPES_H_

#include "gl_colors.h"
#include <stdbool.h>

#ifdef __cplusplus
extern "C"{
#endif

/**
 * @details Enum containing styles for brush that are supported in the drawing functions. It should be used for controlling the look of shapes that uses brush in drawing.
 */
typedef enum
{
    GL_BRUSH_STYLE_NONE = 0,                      /**< Brush area will not be painted.*/
    GL_BRUSH_STYLE_FILL,                              /**< Brush area will be painted with one color set by @ref gl_set_brush_color .*/
    GL_BRUSH_STYLE_GRADIENT_TOP_DOWN,   /**< Brush area will be painted gradientally from top to bottom, with colors set by @ref gl_set_brush_color_from for top part, and @ref gl_set_brush_color_to for bottom part.*/
    GL_BRUSH_STYLE_GRADIENT_LEFT_RIGHT   /**< Brush area will be painted gradientally from left to right, with colors set by @ref gl_set_brush_color_from for left part, and @ref gl_set_brush_color_to for right part.*/
    // GL_BRUSH_STYLE_IMAGE_PATTERN         //TODO: Implement in drawing function.
    // GL_BRUSH_STYLE_GRADIENT_LINEAR       //TODO: Implement in drawing function.
} gl_brush_style_t;


/**
 * @details Enum containing predefined signs for image format. This format is supported in NectoStudio's resource generator.
 */
typedef enum
{
    GL_IMAGE_FORMAT_BITMAP_1BPP  = 0x01,    /**< Image in bitmap format with 1 bpp. */
    GL_IMAGE_FORMAT_BITMAP_4BPP = 0x04,     /**< Image in bitmap format with 4 bpp. */
    GL_IMAGE_FORMAT_BITMAP_8BPP  = 0x08,    /**< Image in bitmap format with 8 bpp. */
    GL_IMAGE_FORMAT_BITMAP_16BPP = 0x10,   /**< Image in bitmap format with 16 bpp. */
    GL_IMAGE_FORMAT_JPEG = 0x20                  /**< Image in jpeg format. */
} gl_image_format_t;

/**
 * @details Enum containing options for orientation of the text. It should be used for controlling orientation of the text or single character when drawing.
 */
typedef enum
{
    GL_FONT_HORIZONTAL = 0,    /**< Text is horizontal. */
    GL_FONT_VERTICAL,               /**< Text is vertical but characters in text are horizontal. */
    GL_FONT_VERTICAL_COLUMN   /**< Both text and characters in it are vertical. */
} gl_font_orientation_t;

typedef int16_t  gl_int_t;    /**< 16-bit integer is used for gl_int_t */
typedef uint16_t gl_uint_t;  /**< 16-bit unsigned integer is used for gl_uint_t */
typedef int32_t  gl_long_int_t;    /**< 32-bit integer is used for gl_long_int_t */
typedef uint32_t gl_long_uint_t;  /**< 32-bit unsigned integer is used for gl_long_uint_t */

typedef uint16_t gl_angle_t; /**< The angle for the arc. Value should be positive. Value between 0 and 360 is expected, but if it happens to be bigger, it will be calculated like:
* @code
* void f (gl_angle_t value) {
* gl_angle_t angle = value % 360
* }
* @endcode */

typedef int16_t gl_coord_t; /**< The coordinates on display are linked to its pixels. To target area 50 pixels away from top and 70 pixels away from left display's edge use coordinates: @f$ x = 70 @f$ and @f$ y = 50 @f$ .*/

/**
 * @brief The context structure for storing coordinates of the point.
 * @details User shall define the values stored within.
 */
typedef struct
{
    gl_int_t x;   /**< X coordinate. */
    gl_int_t y;   /**< Y coordinate. */
} gl_point_t;

/**
 * @brief The context structure for storing width and height in number of pixels on the screen.
 * @details User shall define the values stored within.
 */
typedef struct
{
    gl_uint_t width;    /**< Width. */
    gl_uint_t height;   /**< Height. */
} gl_size_t;

/**
 * @brief The context structure for storing rectangle by its top left point and width and height (in pixels).
 * @details User shall define the values stored within.
 */
typedef struct
{
    gl_point_t  top_left;  /**< Top left point of the rectangle.  See @ref gl_point_t definition for detailed explanation.*/
    uint16_t  width;    /**< Width. */
    uint16_t height;    /**< Height. */
} gl_rectangle_t;


typedef void (*gl_fill_t)(gl_rectangle_t *rect, gl_color_t color);  /**< Function used for drawing on display. Should be defined in driver. */
typedef void (*gl_begin_frame_t)(gl_rectangle_t *rect); /**< Function used for drawing on display. Should be defined in driver. */
typedef void (*gl_frame_data_t)(gl_color_t color); /**< Function used for drawing on display. Should be defined in driver. */
typedef void (*gl_end_frame_t)(); /**< Function used for drawing on display. Should be defined in driver. */

/**
 * @brief The context structure for storing driver configuration.
 * @details User shall define the values stored within. And driver configuration could be found in lower level of mikroSDK.
 */
typedef struct
{
    uint16_t  display_width;             /**< Width of the display. */
    uint16_t display_height;             /**< Height of the display. */

    gl_fill_t         fill_f;                       /**< Send color data to frame transfer and do the drawing. */
    gl_begin_frame_t  begin_frame_f;  /**< Begin frame transfer. */
    gl_frame_data_t   frame_data_f;   /**< Send color data to frame transfer. */
    gl_end_frame_t    end_frame_f;    /**< Finish frame transfer. */
} gl_driver_t;

#ifdef __cplusplus
} // extern "C"
#endif

#endif // _GL_TYPES_H_
// ------------------------------------------------------------------------- END
