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
 * @file  ft800_reg.h
 * @brief FT800 Display Controller Structures.
 */

/*!
 * @addtogroup middlewaregroup Middleware
 * @{
 */

/*!
 * @addtogroup ft800 FT800 Display Controller Driver
 * @{
 */

/*!
 * @addtogroup ft800_registers FT800 Display Controller Structures
 * @brief FT800 Display Controller Structures List
 * @{
 */

#ifndef FT800_STRUCT_H
#define FT800_STRUCT_H

#include <stdint.h>
#include "drv_digital_out.h"
#include "generic_pointer.h"
#include "drv_digital_in.h"
#include "ft800_const.h"
#include "hal_gpio.h"
#include "gl_text.h"
#include "gl.h"
#include "tp.h"

/**
 * @brief FT800 Gesture Item Definition.
 * @details Gesture item definition for FT800 series controllers.
 */
typedef struct
{
    uint8_t    key;
    tp_event_t value;
} ft800_gest_item_t;

/**
 * @brief FT800 Controller Items.
 * @details Gesture items for FT800 series controllers.
 */
typedef struct
{
    ft800_gest_item_t gest_items[ FT800_GESTURE_ITEMS_MAX ];
} ft800_controller_t;

/**
 * @brief FT800 Configuration Object.
 * @details Configuration object definition for FT800 series controllers.
 */
typedef struct
{
    pin_name_t                cs_pin;        // Chip select pin for SPI communication.
    pin_name_t                sck_pin;       // Clock pin for SPI communication.
    pin_name_t                miso_pin;      // Master In Slave Out pin.
    pin_name_t                mosi_pin;      // Master Out Slave In pin.
    pin_name_t                pd_pin;        // Power-down control pin.
    pin_name_t                in_pin;        // Interrupt input pin from FT800.
    spi_master_config_t       spi_master_cfg;// SPI master configuration structure.
    uint16_t                  height;        // Screen height in pixels.
    uint16_t                  width;         // Screen width in pixels.
    const ft800_controller_t *controller;    // Pointer to the FT800 controller definition.
} ft800_cfg_t;

/**
 * @brief FT800 Context Object.
 * @details Context object definition for FT800 series controllers.
 */
typedef struct
{
    spi_master_t    spi_master;  // SPI master interface used for communication.
    digital_in_t    int_pin;     // Digital input pin for interrupt detection.
    digital_out_t   cs_pin;      // Digital output pin for chip select.
    digital_out_t   pd_pin;      // Digital output pin for power-down control.
    tp_event_t      press_det;   // Touch press detection event.
    tp_touch_item_t touch;       // Touch input information.
    tp_event_t      gesture;     // Gesture detection event.
} ft800_t;

/**
 * @brief FT800 Controllers Descriptor.
 * @details Specified descriptor that describe events of the
 * gesture for each controller from FT800 series controllers.
 */
extern const ft800_controller_t FT800_CONTROLLER;

/**
 * @brief FT800 Bool Type Definition.
 * @details Bool type for FT800 series controllers.
 */
typedef uint8_t ft800_bool_t;

/**
 * @brief FT800 Byte Type Definition.
 * @details Byte type for FT800 series controllers.
 */
typedef uint8_t ft800_byte_t;

/**
 * @brief FT800 Index Type Definition.
 * @details Index type for FT800 series controllers.
 */
typedef int16_t ft800_index_t;

/**
 * @brief FT800 COORD type definition.
 * @details Coordinate type for FT800 series controllers.
 */
typedef int16_t ft800_coord_t;

/**
 * @brief FT800 UCOORD Type Definition.
 * @details Unsigned coordinate type for FT800 series controllers.
 */
typedef uint16_t ft800_ucoord_t;

/**
 * @brief FT800 Pen Definition.
 * @details Pen item definition for FT800 series controllers.
 */
typedef struct
{
    ft800_ucoord_t width;                // Pen width.
    uint16_t       color;                // Pen color.
} ft800_pen;

/**
 * @brief FT800 Component Definition.
 * @details Drawing components for FT800 series controllers.
 */
typedef enum
{
    FT800_COMPONENT_NONE,                // No component defined.
    FT800_COMPONENT_BOX,                 // Rectangular box.
    FT800_COMPONENT_ROUNDED_BOX,         // Rectangular box with rounded corners.
    FT800_COMPONENT_CIRCLE,              // Circular shape.
    FT800_COMPONENT_ELLIPSE,             // Elliptical shape.
    FT800_COMPONENT_LINE,                // Straight line.
    FT800_COMPONENT_LABEL,               // Static text label.
    FT800_COMPONENT_BUTTON,              // Rectangular button.
    FT800_COMPONENT_ROUNDED_BUTTON,      // Rectangular Button with rounded corners.
    FT800_COMPONENT_CIRCLE_BUTTON,       // Circular button.
    FT800_COMPONENT_IMAGE,               // Image or bitmap display.
    FT800_COMPONENT_CHECK_BOX,           // Check box with selectable state.
    FT800_COMPONENT_RADIO_BUTTON,        // Radio button with selectable state.
    FT800_COMPONENT_PROGRESS_BAR,        // Progress bar with showing a value.
    FT800_COMPONENT_COUNT                // Total number of defined component types.
} ft800_component_type;

/**
 * @brief FT800 Component Type Definition.
 * @details Drawing component type for FT800 series controllers.
 */
typedef ft800_component_type ft800_comp_type_t;

/**
 * @brief FT800 Event Function Definition.
 * @details Event function for FT800 series controllers.
 */
typedef void ( * ft800_event )();

/**
 * @brief FT800 Component Definition.
 * @details All possible component types for FT800 series controllers.
 */
typedef struct
{
    ft800_event press_event;              // Triggered when a component is pressed.
    ft800_event down_event;               // Triggered when touch begins.
    ft800_event up_event;                 // Triggered when touch ends.
    ft800_event click_event;              // Triggered on click.
} ft800_event_set;

/**
 * @brief FT800 Gradient Style Definition.
 * @details All possible gradient style types for FT800 series controllers.
 */
typedef enum
{
    FT800_GRADIENT_NONE,                  // No gradient applied.
    FT800_GRADIENT_TOP_BOTTOM,            // Gradient from top to bottom.
    FT800_GRADIENT_BOTTOM_TOP,            // Gradient from bottom to top.
    FT800_GRADIENT_LEFT_RIGHT,            // Gradient from left to right.
    FT800_GRADIENT_RIGHT_LEFT             // Gradient from right to left.
} ft800_gradient_style;

/**
 * @brief FT800 Press Gradient Definition.
 * @details Press gradient item definition for FT800 series controllers.
 */
typedef struct
{
    ft800_bool_t         transparent;     // Whether the gradient is transparent.
    ft800_gradient_style gradient_style;  // Direction of the gradient.
    uint16_t             start_color;     // Gradient start color in idle state.
    uint16_t             end_color;       // Gradient end color in idle state.
    uint16_t             press_start_color;// Start color when pressed.
    uint16_t             press_end_color; // End color when pressed.
} ft800_press_gradient;

/**
 * @brief FT800 Gradient Definition.
 * @details Gradient item definition for FT800 series controllers.
 */
typedef struct
{
    ft800_bool_t         transparent;   // Enables / disables transparency.
    ft800_gradient_style gradient_style;// Gradient direction.
    uint16_t             start_color;   // Starting gradient color.
    uint16_t             end_color;     // Ending gradient color.
} ft800_gradient;

/**
 * @brief FT800 Font Definition.
 * @details Font item definition for FT800 series controllers.
 */
typedef struct
{
    const ft800_byte_t *font_data;      // Pointer to font data.
    uint16_t            color;          // Font color.
} ft800_font;

/**
 * @brief FT800 Text Definition.
 * @details Text item definition for FT800 series controllers.
 */
typedef struct
{
    ft800_byte_t *__generic_ptr caption;// Pointer to the text string.
    ft800_index_t max_length;           // Maximum length of the text.
    ft800_font    font;                 // Font configuration.
} ft800_text;

/**
 * @brief FT800 Text Alignment Style Definition.
 * @details All possible alignment style types for FT800 series controllers.
 */
typedef enum
{
    FT800_TEXT_ALIGNMENT_LEFT,          // Align text to the left edge.
    FT800_TEXT_ALIGNMENT_CENTER,        // Align text to the horizontal center.
    FT800_TEXT_ALIGNMENT_RIGHT,         // Align text to the right edge.
    FT800_TEXT_ALIGNMENT_TOP,           // Align text to the top edge.
    FT800_TEXT_ALIGNMENT_MIDDLE,        // Align text to the vertical center.
    FT800_TEXT_ALIGNMENT_BOTTOM         // Align text to the bottom edge.
} ft800_text_alignment;

/**
 * @brief FT800 Screen Definition.
 * @details Screen item definition for FT800 series controllers.
 */
typedef struct
{
    ft800_coord_t     width;            // Width of the screen in pixels.
    ft800_coord_t     height;           // Height of the screen in pixels.
    uint16_t          color;            // Background color of the screen.
    ft800_event_set   press_event;      // Events triggered on press interaction anywhere on the screen.
    ft800_event_set   down_event;       // Events triggered when touch is held down on the screen.
    ft800_event_set   up_event;         // Events triggered when touch is released from the screen.
    ft800_comp_type_t *__generic_ptr * __generic_ptr components;    // Double pointer to an array of component pointers.
    ft800_index_t      component_count; // Number of UI components currently active on the screen.
} ft800_screen;

/**
 * @brief FT800 Rounded Button Definition.
 * @details Rounded button item definition for FT800 series controllers.
 */
typedef struct
{
    ft800_comp_type_t    type;          // Component type identifier.
    ft800_index_t        order;         // Drawing/rendering order.
    ft800_bool_t         visible;       // Visibility status.
    ft800_coord_t        left;          // X coordinates of the top-left corner.
    ft800_coord_t        top;           // Y coordinates of the top-left corner.
    ft800_bool_t         active;        // Whether the button is interactable.
    ft800_event_set      event_set;     // Associated events.
    ft800_pen            pen;           // Outline styling.
    ft800_press_gradient press_gradient;// Pressed-state styling.
    ft800_ucoord_t       width;         // Width of button.
    ft800_ucoord_t       height;        // Height of button.
    ft800_ucoord_t       corner_radius; // Radius of button corners.
    ft800_text           text;          // Button label text.
    ft800_text_alignment text_align;    // Alignment of the text inside the button.
    ft800_bool_t         vertical_text; // Whether the text is drawn vertically.
} ft800_rounded_button;

/**
 * @brief FT800 Circle Definition.
 * @details Circle item definition for FT800 series controllers.
 */
typedef struct
{
    ft800_comp_type_t    type;          // Component type identifier.
    ft800_index_t        order;         // Drawing / rendering order.
    ft800_bool_t         visible;       // Visibility status.
    ft800_coord_t        left;          // X coordinates of the top-left corner.
    ft800_coord_t        top;           // Y coordinates of the top-left corner.
    ft800_bool_t         active;        // Whether the circle is interactable.
    ft800_event_set      event_set;     // Associated events.
    ft800_pen            pen;           // Outline styling.
    ft800_press_gradient press_gradient;// Pressed-state styling.
    ft800_ucoord_t       radius;        // Radius of the circle.
} ft800_circle;

/**
 * @brief FT800 Rounded Box Definition.
 * @details Rounded box item definition for FT800 series controllers.
 */
typedef struct
{
    ft800_comp_type_t    type;          // Component type identifier.
    ft800_index_t        order;         // Drawing / rendering order.
    ft800_bool_t         visible;       // Visibility status.
    ft800_coord_t        left;          // X coordinates of the top-left corner.
    ft800_coord_t        top;           // Y coordinates of the top-left corner.
    ft800_bool_t         active;        // Whether the box is interactable.
    ft800_event_set      event_set;     // Associated events.
    ft800_pen            pen;           // Outline styling.
    ft800_press_gradient press_gradient;// Pressed-state styling.
    ft800_ucoord_t       width;         // Width of box.
    ft800_ucoord_t       height;        // Height of box.
    ft800_ucoord_t       corner_radius; // Radius of box corners.
} ft800_rounded_box;

/**
 * @brief FT800 Ellipse Definition.
 * @details Ellipse item definition for FT800 series controllers.
 */
typedef struct
{
    ft800_comp_type_t    type;          // Component type identifier.
    ft800_index_t        order;         // Drawing / rendering order.
    ft800_bool_t         visible;       // Visibility status.
    ft800_coord_t        left;          // X coordinates of the top-left corner.
    ft800_coord_t        top;           // Y coordinates of the top-left corner.
    ft800_bool_t         active;        // Whether the ellipse is interactable.
    ft800_event_set      event_set;     // Associated events.
    ft800_pen            pen;           // Outline styling.
    ft800_press_gradient press_gradient;// Pressed-state styling.
    ft800_ucoord_t       width;         // Width of ellipse.
    ft800_ucoord_t       height;        // Height of ellipse.
} ft800_ellipse;

/**
 * @brief FT800 Line Definition.
 * @details Line item definition for FT800 series controllers.
 */
typedef struct
{
    ft800_comp_type_t type;             // Component type identifier.
    ft800_index_t     order;            // Drawing / rendering order.
    ft800_bool_t      visible;          // Visibility status.
    ft800_pen         pen;              // Outline styling.
    ft800_coord_t     first_left;       // Starting X point coordinate.
    ft800_coord_t     first_top;        // Starting Y point coordinate.
    ft800_coord_t     second_left;      // Starting X point coordinate.
    ft800_coord_t     second_top;       // Starting Y point coordinate.

} ft800_line;

/**
 * @brief FT800 Label Definition.
 * @details Label item definition for FT800 series controllers.
 */
typedef struct
{
    ft800_comp_type_t type;             // Component type identifier.
    ft800_index_t     order;            // Drawing / rendering order.
    ft800_bool_t      visible;          // Visibility status.
    ft800_coord_t     left;             // X coordinates of the top-left corner.
    ft800_coord_t     top;              // Y coordinates of the top-left corner.
    ft800_bool_t      active;           // Whether the label is interactable.
    ft800_event_set   event_set;        // Associated events.
    ft800_ucoord_t    width;            // Width of label.
    ft800_ucoord_t    height;           // Height of label.
    ft800_text        text;             // Label text.
    ft800_bool_t      vertical_text;    // Whether the text is drawn vertically.
} ft800_label;

/**
 * @brief FT800 Check Box Definition.
 * @details Check box item definition for FT800 series controllers.
 */
typedef struct
{
    ft800_comp_type_t    type;          // Component type identifier.
    ft800_index_t        order;         // Drawing / rendering order.
    ft800_bool_t         visible;       // Visibility status.
    ft800_coord_t        left;          // X coordinates of the top-left corner.
    ft800_coord_t        top;           // Y coordinates of the top-left corner.
    ft800_bool_t         active;        // Whether the Check box is interactable.
    ft800_event_set      event_set;     // Associated events.
    ft800_pen            pen;           // Outline styling.
    ft800_press_gradient press_gradient;// Pressed-state styling.
    ft800_ucoord_t       width;         // Width of Check box.
    ft800_ucoord_t       height;        // Height of Check box.
    ft800_text           text;          // Check box label text.
    ft800_text_alignment text_align;    // Alignment of the text outside the Check box.
    ft800_bool_t         checked;       // Check sing is drawed or not
    ft800_ucoord_t       corner_radius; // Radius of Check box corners.
} ft800_check_box;

/**
 * @brief FT800 Radio Button Definition.
 * @details Rounded button item definition for FT800 series controllers.
 */
typedef struct
{
    ft800_comp_type_t    type;          // Component type identifier.
    ft800_index_t        order;         // Drawing / rendering order.
    ft800_bool_t         visible;       // Visibility status.
    ft800_coord_t        left;          // X coordinates of the top-left corner.
    ft800_coord_t        top;           // Y coordinates of the top-left corner.
    ft800_bool_t         active;        // Whether the Radio button is interactable.
    ft800_event_set      event_set;     // Associated events.
    ft800_pen            pen;           // Outline styling.
    ft800_press_gradient press_gradient;// Pressed-state styling.
    ft800_ucoord_t       width;         // Width of Radio button.
    ft800_ucoord_t       height;        // Height of Radio button.
    ft800_text           text;          // Radio button label text.
    ft800_text_alignment text_align;    // Alignment of the text outside the Radio button.
    ft800_bool_t         checked;       // Check whether the inner circle is drawn
    gl_color_t           back_color;    // Background color of the Radio button.
} ft800_radio_button;

/**
 * @brief FT800 Progress Bar Definition.
 * @details Progress bar item definition for FT800 series controllers.
 */
typedef struct
{
    ft800_comp_type_t type;             // Component type identifier.
    ft800_index_t     order;            // Drawing / rendering order.
    ft800_bool_t      visible;          // Visibility status.
    ft800_coord_t     left;             // X coordinates of the top-left corner.
    ft800_coord_t     top;              // Y coordinates of the top-left corner.
    ft800_ucoord_t    width;            // Width of Progress bar.
    ft800_ucoord_t    height;           // Height of Progress bar.
    ft800_ucoord_t    corner_radius;    // Radius of Progress bar corners.
    ft800_byte_t     *caption;          // Label with progress percentage
    ft800_font        font;             // Font for the label.
    ft800_pen         pen;              // Outline styling.
    ft800_gradient    gradient;         // Fill gradient styling.
    uint16_t          back_color;       // Background color.
    uint32_t          position;         // Current progress value.
    uint32_t          prev_pos;         // Previous progress value.
    uint32_t          min_position;     // Minimum value.
    uint32_t          max_position;     // Maximum value.
    ft800_bool_t      smooth;           // Enables smooth animation.
    ft800_bool_t      show_percent;     // Displays percentage sign.
    ft800_bool_t      show_position;    // Displays numeric progress value.
} ft800_progress_bar;

/**
 * @brief FT800 Image Definition.
 * @details Image item definition for FT800 series controllers.
 */
typedef struct
{
    ft800_comp_type_t   type;           // Component type identifier.
    ft800_index_t       order;          // Drawing / rendering order.
    ft800_bool_t        visible;        // Visibility status.
    ft800_coord_t       left;           // X coordinates of the top-left corner.
    ft800_coord_t       top;            // Y coordinates of the top-left corner.
    ft800_bool_t        active;         // Whether the Image is interactable.
    ft800_event_set     event_set;      // Associated events.
    ft800_ucoord_t      width;          // Width of Image.
    ft800_ucoord_t      height;         // Height of Image.
    const ft800_byte_t *picture_data;   // Pointer to raw image data.
    uint32_t            ratio;          // Image scale or aspect ratio.
    ft800_ucoord_t      corner_radius;  // Radius of Image corners.
} ft800_image;

  /*! @} */ // ft800_structures
 /*! @} */ // ft800
/*! @} */ // mwgroup

#endif
// ------------------------------------------------------------------------- END
