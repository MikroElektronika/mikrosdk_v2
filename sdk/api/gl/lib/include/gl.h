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
 * \file gl.h
 *
 * \brief mikroSDK Graphic Library API.
 *
 * \details
 * It has the active state that can be changed by using this header's
 * function. Active state stores all information needed in drawing time
 * for concluding on wich of various ways the drawing should be performed.
 * The order of setting active state in most case is not important, but
 * there are some exceptions. For example it is the best to first set driver.
 * Also there are default values for the most of variables. But driver must be
 * set by user.
 *
 * The list of variables in active state :
 * gl_driver_t driver - determins specific display
 * required for any drawing on display, can be set by @ref gl_set_driver
 *
 * gl_border_t crop_rect - determins area on display in which object should be drawn
 * not required, set by default so that whole display is available for drawing,
 * can be set by @ref gl_set_crop_borders, and resets every time @ref gl_set_driver
 * is called
 *
 * gl_color_t pen_color - color of the pen
 * used for every shape, can be set by @ref gl_set_pen_color and
 * @ref gl_set_pen
 *
 * uint16_t inner_width - width of the pen that overlaps shape
 * used for every shape, can e set by @ref gl_set_pen_width, @ref gl_set_pen,
 * @ref gl_set_inner_pen
 *
 * uint16_t outer_width - width of the pen that does not overlap the shape
 * used for every shape, can e set by @ref gl_set_pen_width, @ref gl_set_pen,
 * @ref gl_set_outer_pen
 *
 * gl_color_t brush_color - color used for painting shapes in #GL_BRUSH_STYLE_FILL style
 * used for every shape, can be set by @ref gl_set_brush_color
 *
 * gl_brush_style_t style - determins how shapes are painted
 * used for every shape, can be set by @ref gl_set_brush_style
 *
 * gl_color_t gradient_start_color - color with which gradient starts
 * used for every shape when brush style is set to gradient, can be
 * set by @ref gl_set_brush_color_from
 *
 * gl_color_t gradient_end_color - color with which gradient ends
 * used for every shape when brush style is set to gradient, can be
 * set by @ref gl_set_brush_color_to
 *
 * gl_font_t font - font used for drawing text
 * required for any text drawing, can be set by @ref gl_set_font
 *
 * gl_font_orientation_t orientation - the orientation of the text
 * used for every text drawing, can be set y @ref gl_set_font_orientation
 *
 * bool background_on - indicates if background is enabled
 * required for every text drawing, can be set by @ref gl_set_font_background
 *
 * gl_color_t background_color - color for background of the character
 * used for every text drawing when background is enabled,
 * can be set by @ref gl_set_font_background_color
 *
 * Library example code :
 * @code
  #include "gl.h"
  #include "board.h"
  #include "tft8.h"

  static gl_driver_t driver;
  static tft8_cfg_t tft_cfg;

  // code
  TFT8_MAP_PINOUTS_16BIT(tft_cfg);
  tft_cfg.board = &TFT_BOARD_7_CAPACITIVE;
  tft8_init(&tft_cfg, &driver);

  gl_set_driver(&driver); //!<-- set driver before drawing and setting crop borders
  gl_clear(GL_CHARLESTON_GREEN);

  gl_set_crop_borders(-1, -1, 1050, 1000); //!<-- dont think about display dimension, make it wrong and let it be set according to display measures from driver.

  gl_set_brush_style(GL_BRUSH_STYLE_FILL); //!<-- set brush style before drawing
  gl_set_pen_width(0);  //!<-- set pen before drawing
  gl_draw_rect_rounded(105, 220, 80, 100, 40);

  gl_set_brush_color(GL_GREEN); //!<-- set brush color
  gl_draw_circle(145, 270, 30);
  gl_draw_rect_rounded(125, 295, 40, 100, 30);
  gl_draw_rect_rounded(120, 380, 100, 30, 30);
  gl_draw_rect(195, 405, 20, 75);

  gl_set_brush_style(GL_BRUSH_STYLE_GRADIENT_TOP_DOWN); //!<-- Gradient style requires specifying colors to start and end with
  gl_set_brush_color_from(GL_BROWN);
  gl_set_brush_color_to(GL_YELLOW);
  gl_set_pen(GL_GREEN, 6); //!<-- change pen
  gl_draw_line(140, 300, 210, 340);
  gl_draw_line(210, 340, 260, 350);
  gl_draw_line(140, 300, 210, 300);

  gl_set_pen(GL_BLACK, 2); //!<-- also change pen
                           //!<-- no need to set brush since point and line use only pen for drawing.
  gl_draw_point(140, 265);
  gl_draw_point(150, 265);
  gl_draw_line(138, 275, 147, 280);
  gl_draw_line(147, 280, 155, 275);
 * @endcode
 */

#ifndef _GL_H_
#define _GL_H_

#include "gl_types.h"
#include "generic_pointer.h"
#include "gl_colors.h"
#include "gl_text.h"
#include "gl_shapes.h"
#include "gl_image.h"

/** \addtogroup apigroup API
 *  \brief API
 *  @{
 */

/**
 * \addtogroup glgroup Graphic Library
 * \brief Graphic Library
 *  @{
 */

#ifdef __cplusplus
extern "C"{
#endif

/**
 * @brief Sets the driver to the active state and enables
 * drawing on whole display.
 *
 * @details The given driver should contain information
 * about display's width and height and, the most important,
 * pointer to funciton for drawing one rectangle into the display.
 *
 * @param[in] driver the driver that will be set as active.  See @ref gl_driver_t definition for detailed explanation.
 *
 * Example :
 * @code
    gl_driver_t driver;
    ...
    /// Initialize driver.
    TFT8_MAP_PINOUTS_16BIT(tft_cfg);
    tft_cfg.board = &TFT_BOARD_7_CAPACITIVE;
    tft8_init(&tft_cfg, &driver);

    // Set driver.
    gl_set_driver(&driver);
 * @endcode
 */
void gl_set_driver(gl_driver_t *driver);

/**
 * @brief Paint hole display with @p color.
 * If driver is not set then function do nothing.
 *
 * @details Borders set by user using @ref gl_set_crop_borders will be ignored.
 *
 * @param[in] color The color that is used for painting.  See @ref gl_color_t definition for detailed explanation.
 *
 * Example :
 * @code
    gl_driver_t driver;
    ...
    /// Initialize driver.
    TFT8_MAP_PINOUTS_16BIT(tft_cfg);
    tft_cfg.board = &TFT_BOARD_7_CAPACITIVE;
    tft8_init(&tft_cfg, &driver);

    // Set driver.
    gl_set_driver(&driver);

    // Clear display
    gl_clear(GL_WHITE);
 * @endcode
 */
void gl_clear(gl_color_t color);

/**
 * @brief Initialize borders for drawing on display.
 *
 * @details Calculates intersection of display's borders and
 * rectangle determined by @p left, @p top, @p bottom and @p right
 * and change borders of active state to calculated ones.
 * It affects every future drawing by cropping
 * every part of the text or object which cross the set borders.
 * If rectangle between @p left, @p top, @p bottom and @p right
 * coordinates is completely out of display or @p left is greater
 * then @p right or @p top is greater then @p bottom, then state will be
 * same as if function was called with 0, 0, display_height, display_width,
 * and whole display is available for future drawing.
 * Every border is given by its coordinate. Left and right is given by x-axis
 * and top and bottom by y-axis.  See @ref gl_coord_t definition for detailed explanation.
 *
 * @param[in] left Left border.
 * @param[in] top Top border.
 * @param[in] bottom Bottom border.
 * @param[in] right Right border.
 *
 * @returns If the driver is not set returns false, otherwise returns true.
 *
 * @pre The driver must be set first since only after that
 * the dimension (borders) of display is known.
 *
 * Example :
 * @code
   gl_driver_t driver;
    ...
    /// Initialize driver.
    TFT8_MAP_PINOUTS_16BIT(tft_cfg);
    tft_cfg.board = &TFT_BOARD_7_CAPACITIVE;
    tft8_init(&tft_cfg, &driver);

    // Set driver.
    gl_set_driver(&driver);
    gl_set_pen_width(0); // Turn off pen.

    ...

    // Specify area on display for drawing.
    gl_set_crop_borders(-1, -1, -1, -1); // Set hole display enabled becouse the area is invalid
    gl_draw_lrect(50,50, 50, 50);         // Hole rect is visible

    ...

    // Specify area on display for drawing
    gl_set_crop_borders(-5,-3, 75, 75); // Set borders for drawing on y=75 and x = 75 at right and bottom, while top and right borders are corrected to zeros.
    gl_draw_rect(50, 50, 50,50);          // Part of rect is cropped, and display has only rect between 50,50,75, 75

    ...

    // Specify area on display for drawing
    gl_set_crop_borders(250,250, 300, 300); // Set borders for drawing between coordinates y=250 and y=300, x=250 and x=300
    gl_draw_rect(50, 50, 50,50);                 // Since rectangle does not apears in previously specified area, hole rect is not visble.
 * @endcode
 */
bool gl_set_crop_borders(gl_coord_t left, gl_coord_t top, gl_coord_t bottom, gl_coord_t right);

/**
 * @brief Initialize the active font to @p font.
 * Active font is used for every text drawing.
 *
 * @param[in] font The font generated by NectoStudio.
 *
 * Example :
 * @code
   extern const uint8_t* my_font;  //!<-- The font is generated by NectoStudio so extern is needed.
   gl_set_font(my_font);              //!<-- Initialize font.

   ...

   gl_draw_text('Hello World', 50, 50);                       //!<-- Draw text with 'my_font' style.

   gl_size_t size;
   size = gl_get_text_dimensions("Hello World");         //!<-- Get size of text, to calculate where to draw other shape.
   gl_draw_rect(50 + size.width , 50, 20, size.height);  //!<-- Draw rectangle next to text.
 * @endcode
 */
void gl_set_font(const uint8_t *font);

/**
 * @brief Sets the active font orientation to @p orientation.
 *
 * @details
 * Active font orientation determins direction of string and
 * characters inside string whenever text is drawn.
 * By default font orientation is horizontal.
 *
 * @param[in] orientation the font orientation.  See @ref gl_set_font_orientation definition for detailed explanation.
 *
 * Example :
 * @code
   extern const uint8_t* my_font;  //!<-- The font is generated by NectoStudio.
   gl_set_font(my_font);              //!<-- Set font.

   ...

   gl_set_font_orientation(GL_FONT_HORIZONTAL);              //!<-- Set horizontal orientation
   gl_draw_text('Horizontal text', 50, 50);                             //!<-- Draw text horizontaly

   gl_set_font_orientation(GL_FONT_VERTICAL);                   //!<-- Set vertical text with vertikal characters
   gl_draw_text('Vertical text rotated to right', 50, 50);            //!<-- Draw text on new way

   gl_set_font_orientation(GL_FONT_VERTICAL_COLUMN);      //!<-- Set vertical text with horizontal characters
   gl_draw_text('Vertical text', 50, 50);                                 //!<-- Draw text
 * @endcode
 */
void gl_set_font_orientation(gl_font_orientation_t orientation);

/**
 * @brief Sets the active pen width to @p width and its color to @p color.
 * This affects every future drawing of shape by displaying pen
 * so that one half of pen's width cover shape, and the rest of @p width
 * is drew on the outside of shape.
 *
 * @param[in] color the color of the pen.  See @ref gl_color_t definition for detailed explanation.
 * @param[in] width the width of the pen.
 *
 * @details If the shape is less then inner part of pen, the rest
 * of inner pen will just be ignored, it wont afect outer pen to change.
 *
 * Example :
 * @code
   gl_set_pen(GL_RED, 10);

    ...

    gl_draw_circle(50, 50 20);         //!<-- Draw circle with red pen 10 pixels width.
    gl_draw_rect(100, 50, 20, 30);  //!<-- Draw rectangle with red pen 10 pixels width.

    ...

    gl_set_pen(GL_YELLOW, 5);

    gl_draw_circle(50, 50 20);         //!<-- Draw circle with yellow pen 5 pixels width.
    gl_draw_rect(100, 50, 20, 30);  //!<-- Draw rectangle with yellow pen 5 pixels width.
 * @endcode
 */
void gl_set_pen(gl_color_t color, uint16_t width);

/**
 * @brief Sets the active pen's color to @p color.
 *
 * @details
 * This affects every future drawing of shape by
 * painting pen in given @p color if pen width is not zero.
 *
 * @param[in] color The color of the pen.  See @ref gl_color_t definition for detailed explanation.
 *
 * Example :
 * @code
   gl_set_pen(GL_RED, 10);       // Set both pen color and width.
   gl_draw_rect(10, 50, 10, 10); // Draw rectangle with red pen 10 pixels width.

   ...

   gl_set_pen_color(GL_GREEN);  // Change only pen color.
   gl_draw_rect(50, 50, 50, 50);  // Draw with green pen 10 pixels width.
 * @endcode
 */
void gl_set_pen_color(gl_color_t color);

/**
 * @brief Sets the active pen width to @p width.
 * This affects every future drawing of shape by displaying pen
 * so that one half of pen's width cover shape, and the rest of pen
 * is drew on the outside of shape.
 *
 * @param[in] width the width of the pen.
 *
 * @details If the shape is less then inner part of pen, the rest
 * of inner pen will just be ignored, it wont afect outer pen to change.
 *
 * Example :
 * @code
   gl_set_pen(GL_RED, 10);         // Set both pen color and width.
   gl_draw_rect(10, 50, 10, 10);   // Draw rectangle with red pen 10 pixels width.

   ...

   gl_set_pen_width(5);              // Change only pen width.
   gl_draw_rect(50, 50, 50, 50);   // Draw with red pen 5 pixels width.
 * @endcode
 */
void gl_set_pen_width(uint16_t width);

/**
 * @brief Sets width of inner part of active pen to @p width_inside_object.
 * The old width of the pen drew on the outside of shape stays the same, ie.
 * only width of inner part of shape is changed to given value.
 * This affects every drawing of shape in the future.
 *
 * @param[in] width_inside_object the width of inner pen, ie. part of pen that
 * overlaps shape.
 *
 * @details If the shape is less then inner part of pen, the rest
 * of inner pen will just be ignored, it wont afect outer pen to change.
 *
 * Example :
 * @code
   gl_set_brush_color(GL_RED);                          // Set brush color.
   gl_set_brush_style(GL_BRUSH_STYLE_FILL);     // Set brush style to paint all shape with one color.
   gl_set_pen_color(GL_GREEN);                         // Set pen color.
   ...

   gl_set_pen_width(20);          // Set pen width 20 pixels. Automatic 10 pixels will be out of  shape, and 10 in that shape.
   gl_draw_circle(50, 50, 35);    // Draw circle with ring.
                                          // Circle has radius r = 25 pixels, and ring is between r = 25pixels and r = 45pixels.
   ...

   gl_set_outer_pen(0);          // Set outer pen.
   gl_set_inner_pen(20);          // Set inner pen.
   gl_draw_circle(50, 100, 35);  // Draw circle with ring.
                                         // Circle has radius r = 15 pixels, and ring is between r = 15 pixels and r = 35 pixels.

   ...

   gl_set_outer_pen(20);          // Set outer pen.
   gl_set_inner_pen(0);             // Set inner pen.
   gl_draw_circle(50, 100, 35);   // Draw circle with ring.
                                          // Circle has radius r = 35 pixels, and ring is between r = 35 pixels and r = 55 pixels.
 * @endcode
 */
void gl_set_inner_pen(uint16_t width_inside_object);

/**
 * @brief Returns the inner width of active pen.
 *
 * @return the active pen's inner width, ie. part of pen that
 * overlaps shape.
 *
 * Example :
 * @code
   // First way:
   gl_set_pen_width(20);                   // Set pen width 20 pixels. Automatic 10 pixels will be out of  shape, and 10 in that shape.
   uint16_t size = gl_get_inner_pen();  // Get inner pen.
   gl_draw_rect(50, 50, 50, 50);         // Draw rectangle.
   gl_draw_text("Hello world!", 50 + size, 50 + size); // Draw text inside rectangle but not over the pen.

   // Second way:
   gl_set_outer_pen(20);
   gl_set_inner_pen(0);
   gl_draw_rect(60, 60, 40, 40);
   gl_draw_text("Hello world!", 60, 60);
 * @endcode
 */
uint16_t gl_get_inner_pen();

/**
 * @brief Sets width of outer part of active pen to @p width_outside_object.
 * The old width of the pen drew on the inside of shape stays the same, ie.
 * only width of outer part of shape is changed to given value.
 * This affects every drawing of shape in the future.
 *
 * @param[in] width_outside_object the width of outer pen, ie. part of pen that
 * doesn't overlap shape.
 *
 * @details If the shape is less then inner part of pen, the rest
 * of inner pen will just be ignored, it won't affect outer pen to change.
 *
 * Example :
 * @code

 * @endcode
 */
void gl_set_outer_pen(uint16_t width_outside_object);

/**
 * @brief Returns the outer width of active pen.
 *
 * @return the width of outer pen, ie. part of pen that
 * doesn't overlap shape.
 */
uint16_t gl_get_outer_pen();

/**
 * @brief Sets active brush style to @p style.
 *
 * @details
 * This affects every drawing in the future.
 * By setting brush style its determined how
 * shapes will be collored.
 *
 * @param[in] style a style for painting shapes.  See @ref gl_brush_style_t definition for detailed explanation.
 */
void gl_set_brush_style(gl_brush_style_t style);

/**
 * @brief Sets active brush color to @p color.
 *
 * @details
 * This affects every drawing in the future
 * when brush style if #GL_BRUSH_STYLE_FILL.
 *
 * @param[in] color the color for painting non gradient style.  See @ref gl_color_t definition for detailed explanation.
 */
void gl_set_brush_color(gl_color_t color);

/**
 * @brief Sets the active start color to @p color.
 *
 * @details
 * The active start color is used whenever a drawing
 * of shape with some of gradient style is performed.
 *
 * @param[in] color determins the color from which the gradient starts.  See @ref gl_color_t definition for detailed explanation.
 */
void gl_set_brush_color_from(gl_color_t color);

/**
 * @brief Sets the active end color to @p color.
 *
 * @details
 * The active end color is used whenever  drawing
 * of shape with some of gradient style is performed.
 *
 * @param[in] color determins the color with which the gradient ends. See @ref gl_color_t definition for detailed explanation.
 */
void gl_set_brush_color_to(gl_color_t color);

/**
 * @brief Sets the active background color for texts to @p background.
 *
 * @details
 * This will affect drawing text only if background is enabled.
 * To enable drawing use @ref gl_set_font_background.
 *
 * @param[in] background the color of the background of character. See @ref gl_color_t definition for detailed explanation.
 */
void gl_set_font_background_color(gl_color_t background);

/**
 * @brief Sets active indicator for text backround to @p enable.
 *
 * @param[in] enable the indicator for determining if background behind
 * character should be painted.
 *
 * @sa @ref gl_set_font_background_color
 */
void gl_set_font_background(bool enable);

/**
 * @brief Returns the width of the display.
 *
 * @return If the driver is not set returns zero, otherwise
 * returns the width of the active display indicated by driver.
 *
 * @pre The driver must be set first since only after that
 * the dimension of display is known.
 */
uint16_t gl_get_screen_width();

/**
 * @brief Returns the height of the display.
 *
 * @return If the driver is not set returns zero, otherwise
 * returns the height of the active display indicated by driver.
 *
 * @pre The driver must be set first since only after that
 * the dimension of display is known.
 */
uint16_t gl_get_screen_height();

#ifdef __cplusplus
} // extern "C"
#endif

/*! @} */ // glgroup
/*! @} */ // apigroup

#endif // _GL_H_
// ------------------------------------------------------------------------- END
