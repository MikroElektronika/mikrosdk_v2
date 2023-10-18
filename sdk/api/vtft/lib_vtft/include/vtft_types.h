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

/*!
 * \file
 */
#ifndef _VTFT_TYPES_H_
#define _VTFT_TYPES_H_

#include "gl_types.h"
#include "generic_pointer.h"
#include "tp.h"



/*! \addtogroup apigroup API
 *  @{
 */

/*! \addtogroup vtftgroup VTFT Library
 *  @{
 */

// Scalar types.
typedef uint8_t vtft_bool_t;
typedef uint8_t vtft_byte_t;
typedef int16_t vtft_index_t;
typedef gl_int_t  vtft_coord_t;
typedef gl_uint_t vtft_ucoord_t;

// All possible component types.
typedef enum
{
    VTFT_COMPONENT_NONE,
    VTFT_COMPONENT_BOX,
    VTFT_COMPONENT_ROUNDED_BOX,
    VTFT_COMPONENT_CIRCLE,
    VTFT_COMPONENT_ELLIPSE,
    VTFT_COMPONENT_LINE,
    VTFT_COMPONENT_LABEL,
    VTFT_COMPONENT_BUTTON,
    VTFT_COMPONENT_ROUNDED_BUTTON,
    VTFT_COMPONENT_CIRCLE_BUTTON,
    VTFT_COMPONENT_IMAGE,
    VTFT_COMPONENT_CHECK_BOX,
    VTFT_COMPONENT_RADIO_BUTTON,
    VTFT_COMPONENT_PROGRESS_BAR,
    VTFT_COMPONENT_COUNT
}
vtft_component_type;

typedef vtft_component_type vtft_comp_type_t;

// Events

typedef void (*vtft_event)();

typedef struct
{
    vtft_event press_event;
    vtft_event down_event;
    vtft_event up_event;
    vtft_event click_event;
}
vtft_event_set;

// Color, Pen, Gradient

typedef struct
{
    vtft_ucoord_t width;
    gl_color_t color;
}
vtft_pen;

typedef enum
{
    VTFT_GRADIENT_NONE,
    VTFT_GRADIENT_TOP_BOTTOM,
    VTFT_GRADIENT_BOTTOM_TOP,
    VTFT_GRADIENT_LEFT_RIGHT,
    VTFT_GRADIENT_RIGHT_LEFT
}
vtft_gradient_style;

typedef struct
{
    vtft_bool_t transparent;
    vtft_gradient_style gradient_style;
    gl_color_t start_color;
    gl_color_t end_color;
}
vtft_gradient;

typedef struct
{
    vtft_bool_t transparent;
    vtft_gradient_style gradient_style;
    gl_color_t start_color;
    gl_color_t end_color;
    gl_color_t press_start_color;
    gl_color_t press_end_color;
}
vtft_press_gradient;

// Text

typedef struct
{
    const vtft_byte_t *font_data;
    gl_color_t color;
}
vtft_font;

typedef struct
{
    vtft_byte_t * __generic_ptr caption;
    vtft_index_t max_length;
    vtft_font font;
}
vtft_text;

typedef struct
{
    const vtft_byte_t * caption; // nije generic jer je const text
    vtft_index_t max_length;
    vtft_font font;
}
vtft_c_text;

typedef enum
{
    VTFT_TEXT_ALIGNMENT_LEFT,
    VTFT_TEXT_ALIGNMENT_CENTER,
    VTFT_TEXT_ALIGNMENT_RIGHT,
    VTFT_TEXT_ALIGNMENT_TOP,
    VTFT_TEXT_ALIGNMENT_MIDDLE,
    VTFT_TEXT_ALIGNMENT_BOTTOM
}
vtft_text_alignment;

// Components

typedef struct
{
    vtft_comp_type_t type;
    vtft_index_t order;
    vtft_bool_t visible;
}
vtft_component;


typedef struct
{
    vtft_comp_type_t type;
    vtft_index_t order;
    vtft_bool_t visible;
    vtft_coord_t left;
    vtft_coord_t top;
}
vtft_positioned_component;


typedef struct
{
    vtft_comp_type_t type;
    vtft_index_t order;
    vtft_bool_t visible;
    vtft_coord_t left;
    vtft_coord_t top;
    vtft_bool_t active;
    vtft_event_set event_set;
}
vtft_active_component;

typedef struct
{
    vtft_comp_type_t type;
    vtft_index_t order;
    vtft_bool_t visible;
    vtft_coord_t left;
    vtft_coord_t top;
    vtft_bool_t active;
    vtft_event_set event_set;
    vtft_pen pen;
    vtft_press_gradient press_gradient;
}
vtft_colored_component;

// Basic Components

typedef struct
{
    vtft_comp_type_t type;
    vtft_index_t order;
    vtft_bool_t visible;
    vtft_coord_t left;
    vtft_coord_t top;
    vtft_bool_t active;
    vtft_event_set event_set;
    vtft_pen pen;
    vtft_press_gradient press_gradient;
    vtft_ucoord_t width;
    vtft_ucoord_t height;
}
vtft_box;

typedef struct
{
    vtft_comp_type_t type;
    vtft_index_t order;
    vtft_bool_t visible;
    vtft_coord_t left;
    vtft_coord_t top;
    vtft_bool_t active;
    vtft_event_set event_set;
    vtft_pen pen;
    vtft_press_gradient press_gradient;
    vtft_ucoord_t width;
    vtft_ucoord_t height;
    vtft_ucoord_t corner_radius;
}
vtft_rounded_box;

typedef struct
{
    vtft_comp_type_t type;
    vtft_index_t order;
    vtft_bool_t visible;
    vtft_coord_t left;
    vtft_coord_t top;
    vtft_bool_t active;
    vtft_event_set event_set;
    vtft_pen pen;
    vtft_press_gradient press_gradient;
    vtft_ucoord_t radius;
}
vtft_circle;

typedef struct
{
    vtft_comp_type_t type;
    vtft_index_t order;
    vtft_bool_t visible;
    vtft_coord_t left;
    vtft_coord_t top;
    vtft_bool_t active;
    vtft_event_set event_set;
    vtft_pen pen;
    vtft_press_gradient press_gradient;
    vtft_ucoord_t width;
    vtft_ucoord_t height;
}
vtft_ellipse;

typedef struct
{
    vtft_comp_type_t type;
    vtft_index_t order;
    vtft_bool_t visible;
    vtft_pen pen;
    vtft_coord_t first_left;
    vtft_coord_t first_top;
    vtft_coord_t second_left;
    vtft_coord_t second_top;
}
vtft_line;

// Common Components

typedef struct
{
    vtft_comp_type_t type;
    vtft_index_t order;
    vtft_bool_t visible;
    vtft_coord_t left;
    vtft_coord_t top;
    vtft_bool_t active;
    vtft_event_set event_set;
    vtft_ucoord_t width;
    vtft_ucoord_t height;
    vtft_text text;
    vtft_bool_t vertical_text;
}
vtft_label;

typedef struct
{
    vtft_comp_type_t type;
    vtft_index_t order;
    vtft_bool_t visible;
    vtft_coord_t left;
    vtft_coord_t top;
    vtft_bool_t active;
    vtft_event_set event_set;
    vtft_pen pen;
    vtft_press_gradient press_gradient;
    vtft_ucoord_t width;
    vtft_ucoord_t height;
    vtft_text text;
    vtft_text_alignment text_align;
    vtft_bool_t vertical_text;
}
vtft_button;

typedef struct
{
    vtft_comp_type_t type;
    vtft_index_t order;
    vtft_bool_t visible;
    vtft_coord_t left;
    vtft_coord_t top;
    vtft_bool_t active;
    vtft_event_set event_set;
    vtft_pen pen;
    vtft_press_gradient press_gradient;
    vtft_ucoord_t width;
    vtft_ucoord_t height;
    vtft_ucoord_t corner_radius;
    vtft_text text;
    vtft_text_alignment text_align;
    vtft_bool_t vertical_text;
}
vtft_rounded_button;

typedef struct
{
    vtft_comp_type_t type;
    vtft_index_t order;
    vtft_bool_t visible;
    vtft_coord_t left;
    vtft_coord_t top;
    vtft_bool_t active;
    vtft_event_set event_set;
    vtft_pen pen;
    vtft_press_gradient press_gradient;
    vtft_ucoord_t radius;
    vtft_text text;
    vtft_text_alignment text_align;
    vtft_bool_t vertical_text;
}
vtft_circle_button;

typedef struct
{
    vtft_comp_type_t type;
    vtft_index_t order;
    vtft_bool_t visible;
    vtft_coord_t left;
    vtft_coord_t top;
    vtft_bool_t active;
    vtft_event_set event_set;
    vtft_ucoord_t width;
    vtft_ucoord_t height;
    const vtft_byte_t *picture_data;
    uint32_t ratio;
}
vtft_image;

typedef struct
{
    vtft_comp_type_t type;
    vtft_index_t order;
    vtft_bool_t visible;
    vtft_coord_t left;
    vtft_coord_t top;
    vtft_bool_t active;
    vtft_event_set event_set;
    vtft_pen pen;
    vtft_press_gradient press_gradient;
    vtft_ucoord_t width;
    vtft_ucoord_t height;
    vtft_text text;
    vtft_text_alignment text_align;
    vtft_bool_t checked;
}
vtft_abstract_check_box;

typedef struct
{
    vtft_comp_type_t type;
    vtft_index_t order;
    vtft_bool_t visible;
    vtft_coord_t left;
    vtft_coord_t top;
    vtft_bool_t active;
    vtft_event_set event_set;
    vtft_pen pen;
    vtft_press_gradient press_gradient;
    vtft_ucoord_t width;
    vtft_ucoord_t height;
    vtft_text text;
    vtft_text_alignment text_align;
    vtft_bool_t checked;
    vtft_ucoord_t corner_radius;
}
vtft_check_box;

typedef struct
{
    vtft_comp_type_t type;
    vtft_index_t order;
    vtft_bool_t visible;
    vtft_coord_t left;
    vtft_coord_t top;
    vtft_bool_t active;
    vtft_event_set event_set;
    vtft_pen pen;
    vtft_press_gradient press_gradient;
    vtft_ucoord_t width;
    vtft_ucoord_t height;
    vtft_text text;
    vtft_text_alignment text_align;
    vtft_bool_t checked;
    gl_color_t back_color;
}
vtft_radio_button;

typedef struct
{
    vtft_comp_type_t type;
    vtft_index_t order;
    vtft_bool_t visible;
    vtft_coord_t left;
    vtft_coord_t top;
    vtft_ucoord_t width;
    vtft_ucoord_t height;
    vtft_ucoord_t corner_radius;
    vtft_byte_t *caption;
    vtft_font font;
    vtft_pen pen;
    vtft_gradient gradient;
    gl_color_t back_color;
    uint32_t position;
    uint32_t prev_pos;
    uint32_t min_position;
    uint32_t max_position;
    vtft_bool_t smooth;
    vtft_bool_t show_percent;
    vtft_bool_t show_position;
}
vtft_progress_bar;

// Screen

typedef struct
{
    vtft_ucoord_t width;
    vtft_ucoord_t height;
    gl_color_t color;

    vtft_event press_event;
    vtft_event down_event;
    vtft_event up_event;

    vtft_component *__generic_ptr * __generic_ptr components;
    vtft_index_t component_count;
}
vtft_screen;

// Drawing Functions
// The function signature for drawing a component.
typedef void (*vtft_draw_handle)(struct vtft_s *instance, vtft_component * __generic_ptr component);

// VTFT Instance

typedef struct vtft_s
{
    // The TP instance.
    tp_t * tp_instance;

    // The draw handles for all the various components.
    vtft_draw_handle draw_handles[VTFT_COMPONENT_COUNT];

    // The currently displayed screen.
    vtft_screen *current_screen;

    // Pen down indicator.
    vtft_bool_t pen_down;
    // Indicates that the screen has been changed while the screen was pressed.
    vtft_bool_t screen_changed;

    // The component currently under the cursor.
    vtft_active_component * __generic_ptr current_active_component;

    // The currently pressed component.
    vtft_active_component * __generic_ptr pressed_component;
}
vtft_t;

/*! @} */ // vtftgroup
/*! @} */ // apigroup

#endif // _VTFT_TYPES_H_
// ------------------------------------------------------------------------- END
