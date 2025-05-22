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
** OF MERCHANTABILITY, EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED
** TO THE WARRANTIES FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT.
** IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM,
** DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT
** OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE
** OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
**
****************************************************************************/
/*!
 * @file  ft800.h
 * @brief FT800 Display Controller Driver.
 */

#ifndef FT800_H
#define FT800_H

#include <stdint.h>
#include "drv_spi_master.h"
#include "drv_digital_out.h"
#include "drv_digital_in.h"
#include "hal_gpio.h"
#include "gl.h"
#include "gl_text.h"
#include "generic_pointer.h"
#include "tp.h"

#define FT800_GESTURE_ITEMS_MAX        7

typedef struct
{
    uint8_t     key;    /**< Gesture key. */
    tp_event_t  value;  /**< Gesture event value. */

} ft800_gest_item_t;

/**
 * @brief FT5xx6 Gesture Items.
 * @details Gesture items for FT5xx6 series touch controllers.
 */
typedef struct
{
    ft800_gest_item_t  gest_items[ FT800_GESTURE_ITEMS_MAX ];

} ft800_controller_t;


typedef struct
{
    pin_name_t cs_pin;
    pin_name_t sck_pin;
    pin_name_t miso_pin;
    pin_name_t mosi_pin;
    pin_name_t pd_pin;
    pin_name_t in_pin;

    spi_master_config_t spi_master_cfg;
    
    uint16_t height;
    uint16_t width;
    const ft800_controller_t * controller;

} ft800_cfg_t;

typedef struct
{
    spi_master_t spi_master;

    digital_in_t int_pin;
    digital_out_t cs_pin;
    digital_out_t pd_pin;

    tp_event_t       press_det;     
    tp_touch_item_t  touch;         
    tp_event_t       gesture;       

} ft800_t;

/**
 * @brief FT800 Touch Controllers Descriptor.
 * @details Specified descriptor that describe events of the
 * gesture for each controller from FT800 series touch controllers.
 */
extern const ft800_controller_t FT800_CONTROLLER;

typedef uint8_t ft800_bool_t;
typedef uint8_t ft800_byte_t;
typedef int16_t ft800_index_t;
typedef int16_t  ft800_coord_t;
typedef uint16_t ft800_ucoord_t;

typedef struct
{
    ft800_ucoord_t width;
    uint16_t color;
}
ft800_pen;

// All possible component types.
typedef enum
{
    FT800_COMPONENT_NONE,
    FT800_COMPONENT_BOX,
    FT800_COMPONENT_ROUNDED_BOX,
    FT800_COMPONENT_CIRCLE,
    FT800_COMPONENT_ELLIPSE,
    FT800_COMPONENT_LINE,
    FT800_COMPONENT_LABEL,
    FT800_COMPONENT_BUTTON,
    FT800_COMPONENT_ROUNDED_BUTTON,
    FT800_COMPONENT_CIRCLE_BUTTON,
    FT800_COMPONENT_IMAGE,
    FT800_COMPONENT_CHECK_BOX,
    FT800_COMPONENT_RADIO_BUTTON,
    FT800_COMPONENT_PROGRESS_BAR,
    FT800_COMPONENT_COUNT
} ft800_component_type;

typedef ft800_component_type ft800_comp_type_t;

typedef void (*ft800_event)();

typedef struct
{
    ft800_event press_event;
    ft800_event down_event;
    ft800_event up_event;
    ft800_event click_event;
} ft800_event_set;

typedef enum
{
    FT800_GRADIENT_NONE,
    FT800_GRADIENT_TOP_BOTTOM,
    FT800_GRADIENT_BOTTOM_TOP,
    FT800_GRADIENT_LEFT_RIGHT,
    FT800_GRADIENT_RIGHT_LEFT
} ft800_gradient_style;

typedef struct
{
    ft800_bool_t transparent;
    ft800_gradient_style gradient_style;
    uint16_t start_color;
    uint16_t end_color;
    uint16_t press_start_color;
    uint16_t press_end_color;
} ft800_press_gradient;

typedef struct
{
    ft800_bool_t transparent;
    ft800_gradient_style gradient_style;
    uint16_t start_color;
    uint16_t end_color;
} ft800_gradient;

typedef struct
{
    const ft800_byte_t *font_data;
    uint16_t color;
} ft800_font;

typedef struct
{
    ft800_byte_t * __generic_ptr caption;
    ft800_index_t max_length;
    ft800_font font;
} ft800_text;


typedef enum
{
    FT800_TEXT_ALIGNMENT_LEFT,
    FT800_TEXT_ALIGNMENT_CENTER,
    FT800_TEXT_ALIGNMENT_RIGHT,
    FT800_TEXT_ALIGNMENT_TOP,
    FT800_TEXT_ALIGNMENT_MIDDLE,
    FT800_TEXT_ALIGNMENT_BOTTOM
} ft800_text_alignment;

typedef struct
{
    ft800_comp_type_t type;
    ft800_index_t order;
    ft800_bool_t visible;
    ft800_coord_t left;
    ft800_coord_t top;
    ft800_bool_t active;
    ft800_event_set event_set;
    ft800_pen pen;
    ft800_press_gradient press_gradient;
    ft800_ucoord_t width;
    ft800_ucoord_t height;
    ft800_ucoord_t corner_radius;
    ft800_text text;
    ft800_text_alignment text_align;
    ft800_bool_t vertical_text;
} ft800_rounded_button;

typedef struct 
{
    ft800_comp_type_t type;
    ft800_index_t order;
    ft800_bool_t visible;
    ft800_coord_t left;
    ft800_coord_t top;
    ft800_bool_t active;
    ft800_event_set event_set;
    ft800_pen pen;
    ft800_press_gradient press_gradient;
    ft800_ucoord_t radius;
    
}ft800_circle;

typedef struct 
{
    ft800_comp_type_t type;
    ft800_index_t order;
    ft800_bool_t visible;
    ft800_coord_t left;
    ft800_coord_t top;
    ft800_bool_t active;
    ft800_event_set event_set;
    ft800_pen pen;
    ft800_press_gradient press_gradient;
    ft800_ucoord_t width;
    ft800_ucoord_t height;
    ft800_ucoord_t corner_radius;

}ft800_rounded_box;

typedef struct 
{
    ft800_comp_type_t type;
    ft800_index_t order;
    ft800_bool_t visible;
    ft800_coord_t left;
    ft800_coord_t top;
    ft800_bool_t active;
    ft800_event_set event_set;
    ft800_pen pen;
    ft800_press_gradient press_gradient;
    ft800_ucoord_t width;
    ft800_ucoord_t height;
    
}ft800_ellipse;

typedef struct 
{
    ft800_comp_type_t type;
    ft800_index_t order;
    ft800_bool_t visible;
    ft800_pen pen;
    ft800_coord_t first_left;
    ft800_coord_t first_top;
    ft800_coord_t second_left;
    ft800_coord_t second_top;

}ft800_line;

typedef struct 
{
    ft800_comp_type_t type;
    ft800_index_t order;
    ft800_bool_t visible;
    ft800_coord_t left;
    ft800_coord_t top;
    ft800_bool_t active;
    ft800_event_set event_set;
    ft800_ucoord_t width;
    ft800_ucoord_t height;
    ft800_text text;
    ft800_bool_t vertical_text;

}ft800_label;

typedef struct 
{
    ft800_comp_type_t type;
    ft800_index_t order;
    ft800_bool_t visible;
    ft800_coord_t left;
    ft800_coord_t top;
    ft800_bool_t active;
    ft800_event_set event_set;
    ft800_pen pen;
    ft800_press_gradient press_gradient;
    ft800_ucoord_t width;
    ft800_ucoord_t height;
    ft800_text text;
    ft800_text_alignment text_align;
    ft800_bool_t checked;
    ft800_ucoord_t corner_radius;

}ft800_check_box;

typedef struct 
{
    ft800_comp_type_t type;
    ft800_index_t order;
    ft800_bool_t visible;
    ft800_coord_t left;
    ft800_coord_t top;
    ft800_bool_t active;
    ft800_event_set event_set;
    ft800_pen pen;
    ft800_press_gradient press_gradient;
    ft800_ucoord_t width;
    ft800_ucoord_t height;
    ft800_text text;
    ft800_text_alignment text_align;
    ft800_bool_t checked;
    gl_color_t back_color;

}ft800_radio_button;

typedef struct
{
    ft800_comp_type_t type;
    ft800_index_t order;
    ft800_bool_t visible;
    ft800_coord_t left;
    ft800_coord_t top;
    ft800_ucoord_t width;
    ft800_ucoord_t height;
    ft800_ucoord_t corner_radius;
    ft800_byte_t *caption;
    ft800_font font;
    ft800_pen pen;
    ft800_gradient gradient;
    uint16_t back_color;
    uint32_t position;
    uint32_t prev_pos;
    uint32_t min_position;
    uint32_t max_position;
    ft800_bool_t smooth;
    ft800_bool_t show_percent;
    ft800_bool_t show_position;

} ft800_progress_bar;

typedef struct
{
    ft800_comp_type_t type;
    ft800_index_t order;
    ft800_bool_t visible;
    ft800_coord_t left;
    ft800_coord_t top;
    ft800_bool_t active;
    ft800_event_set event_set;
    ft800_ucoord_t width;
    ft800_ucoord_t height;
    const ft800_byte_t *picture_data;
    uint32_t ratio;

    ft800_ucoord_t corner_radius;    
}ft800_image;



/**
 * @brief FT800 Pin Mapping.
 * @details Utility macro for mapping FT5xx6 series touch controllers.
 */
#define FT800_MAP_PINS( cfg ) \
    cfg.cs_pin=MIKROBUS_3_CS; \
    cfg.sck_pin=MIKROBUS_3_SCK; \
    cfg.miso_pin=MIKROBUS_3_MISO; \
    cfg.mosi_pin=MIKROBUS_3_MOSI; \
    cfg.pd_pin=MIKROBUS_3_RST;
/*--------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------*/
void ft800_default_cfg(ft800_t * ctx);
void ft800_cfg(ft800_t *ctx,ft800_cfg_t *cfg);
//void ft800_cfg(ft800_t *ctx,ft800_cfg_t *cfg);
void ft800_cfg_setup( ft800_cfg_t * cfg, const ft800_controller_t * controller );
void ft800_init( ft800_t * ctx, ft800_cfg_t * cfg, tp_drv_t * drv );
/*--------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------*/
void init_touch_screen(ft800_t *ctx, ft800_cfg_t *cfg,bool run_calibration);
void ft800_gesture( ft800_t* ctx, tp_event_t * event );
tp_event_t ft800_press_detect( ft800_t* ctx );
void ft800_press_coordinates( ft800_t* ctx, tp_touch_item_t * touch_item );
static tp_err_t ft800_read_press_coordinates( ft800_t *ctx, ft800_cfg_t *cfg );
tp_err_t ft800_process( ft800_t * ctx , ft800_cfg_t *cfg);
/*--------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------*/
void write_data(ft800_t *ctx,ft800_cfg_t *cfg, uint32_t addres,uint32_t value,uint8_t length );
uint32_t read_data(ft800_t *ctx,ft800_cfg_t *cfg,uint32_t addres,uint8_t length);
/*--------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------*/
void cmd(ft800_t *ctx,ft800_cfg_t *cfg,uint32_t command,uint16_t*cmdOffset);
void cmd_text(ft800_t *ctx,ft800_cfg_t *cfg,uint16_t* cmdOffset, int16_t x, int16_t y, int16_t font, uint16_t options, const char* s);
void wait_coprocessor(ft800_t *ctx,ft800_cfg_t *cfg);
/*--------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------*/
uint8_t rgb_convert(int16_t color,char *name);
/*--------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------*/
void start_display_list(ft800_t *ctx, ft800_cfg_t *cfg,uint16_t *cmdOffset);
void end_display_list(ft800_t *ctx, ft800_cfg_t *cfg,uint16_t *cmdOffset);
/*--------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------*/
void draw_box(ft800_t *ctx, ft800_cfg_t *cfg,uint16_t *cmdOffset,ft800_rounded_box *box);
void draw_button(ft800_t *ctx,ft800_cfg_t *cfg, uint16_t *cmdOffset, ft800_rounded_button *button);
void draw_edges_circle(ft800_t *ctx, ft800_cfg_t *cfg, uint16_t *cmdOffset,uint16_t cx, uint16_t cy,uint16_t width,uint16_t pen_color, uint16_t pen_width);
void draw_label(ft800_t *ctx,ft800_cfg_t *cfg,uint16_t *cmdOffset,ft800_label *label);
void draw_line(ft800_t *ctx,ft800_cfg_t *cfg,uint16_t *cmdOffset,ft800_line *line);
void draw_progress_bar(ft800_t *ctx,ft800_cfg_t *cfg,uint16_t *cmdOffset,ft800_progress_bar *progress_bar);
void draw_check_box(ft800_t *ctx, ft800_cfg_t *cfg,uint16_t *cmdOffset,ft800_check_box *check_box);
void cmd_number(ft800_t *ctx,ft800_cfg_t *cfg,uint16_t* cmdOffset,uint16_t left,uint16_t top,uint16_t font,uint16_t options,int32_t num);
void draw_radio_button(ft800_t *ctx, ft800_cfg_t *cfg,uint16_t *cmdOffset,ft800_radio_button *radio_button);
void draw_gradient_circle(ft800_t *ctx, ft800_cfg_t *cfg,uint16_t *cmdOffset,uint16_t cx, uint16_t cy, uint16_t width, uint16_t s_color,uint16_t e_color,uint8_t type);
void draw_edges_ellipse(ft800_t *ctx, ft800_cfg_t *cfg, uint16_t *cmdOffset,uint16_t cx, uint16_t cy,uint16_t width, uint16_t height,uint16_t pen_color, uint16_t pen_width);
void draw_gradient(ft800_t *ctx,ft800_cfg_t *cfg,uint16_t *cmdOffset,uint16_t s_color,uint16_t e_color,char *object,uint16_t left,uint16_t top,uint16_t width,uint16_t height,uint16_t pp,uint16_t type);
void draw_gradient_ellipse(ft800_t *ctx, ft800_cfg_t *cfg,uint16_t *cmdOffset,uint16_t x, uint16_t y, uint16_t width, uint16_t height,uint16_t s_color,uint16_t e_color,uint8_t variant);
void draw_edges_rectangle(ft800_t *ctx, ft800_cfg_t *cfg, uint16_t *cmdOffset,uint16_t x1, uint16_t y1, uint16_t width, uint16_t height,uint16_t radius, uint16_t color, uint8_t pen_width);
void draw_gradient_rectangle(ft800_t *ctx, ft800_cfg_t *cfg, uint16_t *cmdOffset,uint16_t x1, uint16_t y1, uint16_t width, uint16_t height,uint16_t radius, uint16_t s_color, uint16_t e_color,uint8_t variant);
void draw_ellipse(ft800_t *ctx, ft800_cfg_t *cfg, uint16_t *cmdOffset,ft800_ellipse *ellipse);
void draw_circle(ft800_t *ctx, ft800_cfg_t *cfg,uint16_t *cmdOffset,ft800_circle *circle);
void draw_image_image(ft800_t *ctx,ft800_cfg_t *cfg,uint16_t *cmdOffset,ft800_image *image);
/*--------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------*/
void draw_aligned_text(ft800_t *ctx, ft800_cfg_t *cfg, uint16_t *cmdOffset,uint16_t x, uint16_t y, uint16_t width, uint16_t height,uint16_t text_height,ft800_text_alignment alignment,uint8_t pen, char *text);
void draw_vertical_text(ft800_t *ctx, ft800_cfg_t *cfg, uint16_t* cmdOffset, uint16_t x ,uint16_t y,uint16_t width,uint16_t height,uint16_t text_width,uint16_t pen,ft800_text_alignment alignment,char *text);
/*--------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------*/

#endif // FT800_H
// ------------------------------------------------------------------------- END
