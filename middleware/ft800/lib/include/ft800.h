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

/**
 * @brief FT800 Gesture Items Limit Setting.
 * @details Gesture items limit for FT800 series controllers.
 */
#define FT800_GESTURE_ITEMS_MAX 7

/**
 * @brief FT800 Pin Mapping.
 * @details Utility macro for mapping FT800 series controllers.
 */
#define FT800_MAP_PINS( cfg ) \
    cfg.cs_pin=MIKROBUS_3_CS; \
    cfg.sck_pin=MIKROBUS_3_SCK; \
    cfg.miso_pin=MIKROBUS_3_MISO; \
    cfg.mosi_pin=MIKROBUS_3_MOSI; \
    cfg.pd_pin=MIKROBUS_3_RST;

/**
 * @brief FT800 Gesture Item Definition.
 * @details Gesture item definition for FT800 series controllers.
 */
typedef struct
{
    uint8_t key;    
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
    pin_name_t cs_pin;
    pin_name_t sck_pin;
    pin_name_t miso_pin;
    pin_name_t mosi_pin;
    pin_name_t pd_pin;
    pin_name_t in_pin;
    spi_master_config_t spi_master_cfg;
    uint16_t height;
    uint16_t width;
    const ft800_controller_t *controller;
} ft800_cfg_t;

/**
 * @brief FT800 Context Object.
 * @details Context object definition for FT800 series controllers.
 */
typedef struct
{
    spi_master_t spi_master;
    digital_in_t int_pin;
    digital_out_t cs_pin;
    digital_out_t pd_pin;
    tp_event_t press_det;     
    tp_touch_item_t touch;         
    tp_event_t gesture;       
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
    ft800_ucoord_t width;
    uint16_t color;
} ft800_pen;

/**
 * @brief FT800 Component Definition.
 * @details Drawning components for FT800 series controllers.
 */
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

/**
 * @brief FT800 Component Type Definition.
 * @details Drawning component type for FT800 series controllers.
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
    ft800_event press_event;
    ft800_event down_event;
    ft800_event up_event;
    ft800_event click_event;
} ft800_event_set;

/**
 * @brief FT800 Gradient Style Definition.
 * @details All possible gradient style types for FT800 series controllers.
 */
typedef enum
{
    FT800_GRADIENT_NONE,
    FT800_GRADIENT_TOP_BOTTOM,
    FT800_GRADIENT_BOTTOM_TOP,
    FT800_GRADIENT_LEFT_RIGHT,
    FT800_GRADIENT_RIGHT_LEFT
} ft800_gradient_style;

/**
 * @brief FT800 Press Gradient Definition.
 * @details Press gradient item definition for FT800 series controllers.
 */
typedef struct
{
    ft800_bool_t transparent;
    ft800_gradient_style gradient_style;
    uint16_t start_color;
    uint16_t end_color;
    uint16_t press_start_color;
    uint16_t press_end_color;
} ft800_press_gradient;

/**
 * @brief FT800 Gradient Definition.
 * @details Gradient item definition for FT800 series controllers.
 */
typedef struct
{
    ft800_bool_t transparent;
    ft800_gradient_style gradient_style;
    uint16_t start_color;
    uint16_t end_color;
} ft800_gradient;

/**
 * @brief FT800 Font Definition.
 * @details Font item definition for FT800 series controllers.
 */
typedef struct
{
    const ft800_byte_t *font_data;
    uint16_t color;
} ft800_font;

/**
 * @brief FT800 Text Definition.
 * @details Text item definition for FT800 series controllers.
 */
typedef struct
{
    ft800_byte_t * __generic_ptr caption;
    ft800_index_t max_length;
    ft800_font font;
} ft800_text;

/**
 * @brief FT800 Text Alignment Style Definition.
 * @details All possible alignment style types for FT800 series controllers.
 */
typedef enum
{
    FT800_TEXT_ALIGNMENT_LEFT,
    FT800_TEXT_ALIGNMENT_CENTER,
    FT800_TEXT_ALIGNMENT_RIGHT,
    FT800_TEXT_ALIGNMENT_TOP,
    FT800_TEXT_ALIGNMENT_MIDDLE,
    FT800_TEXT_ALIGNMENT_BOTTOM
} ft800_text_alignment;

/**
 * @brief FT800 Rounded Button Definition.
 * @details Rounded button item definition for FT800 series controllers.
 */
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

/**
 * @brief FT800 Circle Definition.
 * @details Circle item definition for FT800 series controllers.
 */
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
} ft800_circle;

/**
 * @brief FT800 Rounded Box Definition.
 * @details Rounded box item definition for FT800 series controllers.
 */
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
} ft800_rounded_box;

/**
 * @brief FT800 Ellipse Definition.
 * @details Ellipse item definition for FT800 series controllers.
 */
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
} ft800_ellipse;

/**
 * @brief FT800 Line Definition.
 * @details Line item definition for FT800 series controllers.
 */
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

} ft800_line;

/**
 * @brief FT800 Label Definition.
 * @details Label item definition for FT800 series controllers.
 */
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
} ft800_label;

/**
 * @brief FT800 Check Box Definition.
 * @details Check box item definition for FT800 series controllers.
 */
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
} ft800_check_box;

/**
 * @brief FT800 Radio Button Definition.
 * @details Rounded button item definition for FT800 series controllers.
 */
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
} ft800_radio_button;

/**
 * @brief FT800 Progress Bar Definition.
 * @details Progress bar item definition for FT800 series controllers.
 */
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

/**
 * @brief FT800 Image Definition.
 * @details Image item definition for FT800 series controllers.
 */
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
} ft800_image;

/**
 * @brief FT800 Configuration Object Setup Function.
 * @details This function initializes FT800 configuration structure to default
 * values.
 * @param[out] cfg : FT800 configuration object. See #ft800_cfg_t structure
 * definition for detailed explanation.
 * @param[in] controller : Controller selector from FT800 series
 * controllers. See #ft800_controller_t structure definition for detailed
 * explanation.
 * @return Nothing.
 * @note The all used pins will be set to unconnected state.
 *
 * @b Example
 * @code
 *    // FT800 configuration object.
 *    ft800_cfg_t ft800_cfg;
 *    // FT800 series touch controllers descriptor.
 *    const ft800_controller_t FT800_CONTROLLER =
 *    {
 *        {
 *            { 0x00, TP_EVENT_GEST_NONE },
 *            { 0x1C, TP_EVENT_GEST_LEFT },
 *            { 0x14, TP_EVENT_GEST_RIGHT },
 *            { 0x10, TP_EVENT_GEST_UP },
 *            { 0x18, TP_EVENT_GEST_DOWN },
 *            { 0x48, TP_EVENT_GEST_ZOOM_IN },
 *            { 0x49, TP_EVENT_GEST_ZOOM_OUT }
 *        }
 *    };
 *
 *    // FT800 configuration setup.
 *    ft800_cfg_setup( &ft800_cfg, &FT800_CONTROLLER );
 * @endcode
 */
void ft800_cfg_setup( ft800_cfg_t * cfg, const ft800_controller_t * controller );

/**
 * @brief FT800 Initialization Function.
 * @details This function initializes FT5xx6 context object to default values
 * and allows driver interface object to be linked with FT800 driver functions.
 * @param[out] ctx : FT5xx6 context object. See #ft800_t structure definition
 * for detailed explanation.
 * @param[in] cfg : FT800 configuration object. See #ft800_cfg_t structure
 * definition for detailed explanation.
 * @param[out] drv : TP driver interface object. See #tp_drv_t structure
 * definition for detailed explanation.
 * @return @li @c 0 - OK,
 *         @li @c 1 - SPI driver init error,
 *         @li @c 2 - Unsupported pin.
 * See #tp_err_t structure definition for detailed explanation.
 *
 * @b Example
 * @code
 *    // FT800 driver object.
 *    ft800_t ft800;
 *    // FT800 configuration object.
 *    ft800_cfg_t ft800_cfg;
 *    // FT800 series touch controllers descriptor.
 *    const ft800_controller_t FT800_CONTROLLER;
 *    // TP driver interface object.
 *    tp_drv_t tp_interface;
 *
 *    // FT800 configuration setup.
 *    ft800_cfg_setup( &ft800_cfg, &FT800_CONTROLLER );
 *    // FT800 controller pin mapping.
 *    FT800_MAP_PINS( ft800_cfg );
 *    // FT800 driver initialization.
 *    ft800_init( &ft800, &ft800_cfg, &tp_interface );
 * @endcode
 */
void ft800_init( ft800_t *ctx, ft800_cfg_t *cfg, tp_drv_t *drv );

/**
 * @brief FT800 Default Configuration Function.
 * @details This function puts the FT800 touch controller to normal operating
 * mode.
 * @param[in] ctx : FT800 context object. See #ft800_t structure definition
 * for detailed explanation.
 * @return Nothing.
 * @note It's necessary for this functon to be executed after Initialization
 * function for properly working of entire driver.
 *
 * @b Example
 * @code
 * 
 *    // FT800 driver default configuration.
 *    ft800_default_cfg( &ft800 );
 * @endcode
 */
void ft800_default_cfg( ft800_t * ctx );

/**
 * @brief Write Data Function.
 * @details This function allows user to write any 8-bit, 16-bit 24-bit or 32-bit data to the 
 * selected register of the 800 series controllers.
 * @param[in] ctx : FT800 context object. See #ft800_t structure definition
 * for detailed explanation.
 * @param[in] cfg : FT800 configuration object. See #ft800_cfg_t structure
 * definition for detailed explanation.
 * @param[in] addres : Register address where data be written.
 * @param[in] value : Data to be written.
 * @param[in] length : Size of data sent.
 * @return Nothing.
 *
 * @b Example
 * @code
 *    // FT800 driver object.
 *    ft800_t ctx;
 *    // FT800 configuration object.
 *    ft800_cfg_t cfg;
 * 
 *    // FT800 driver set in active configuration.
 *    write_data( ctx, cfg, FT800_CMD_ADDRES, FT800_ACTIVE, 24 );
 * @endcode
 */
void write_data( ft800_t *ctx, ft800_cfg_t *cfg, uint32_t addres, uint32_t value, uint8_t length );

/**
 * @brief Read Data Function.
 * @details This function allows user to read any desired register of the FT800
 * series controllers.
 * @param[in] ctx : FT800 context object. See #ft800_t structure definition
 * for detailed explanation.
 * @param[in] cfg : FT800 configuration object. See #ft800_cfg_t structure
 * definition for detailed explanation.
 * @param[in] addres : Register address which from data be read.
 * @param[in] length : Size of readed data.
 * @return 32-bit read data.
 *
 * @b Example
 * @code
 *    // FT800 driver object.
 *    ft800_t ctx;
 *    // FT800 configuration object.
 *    ft800_cfg_t cfg;
 *    // Read value.
 *    uint8_t read_data;
 *
 *    // Reading activity status of FT800 controller.
 *    read_data = read_data( &ctx, &cfg, FT800_REG_ID , 8 );
 * @endcode
 */
uint32_t read_data( ft800_t *ctx, ft800_cfg_t *cfg, uint32_t addres, uint8_t length );

/**
 * @brief FT800 Configuration Function.
 * @details This function configure FT800 registers to active operating
 * mode.
 * @param[in] ctx : FT800 context object. See #ft800_t structure definition
 * for detailed explanation.
 * @param[in] cfg : FT800 configuration object. See #ft800_cfg_t structure
 * definition for detailed explanation.
 * @return Nothing.
 *
 * @b Example
 * @code
 *
 *    // FT800 driver object.
 *    ft800_t ctx;
 *    // FT800 configuration object.
 *    ft800_cfg_t cfg;
 * 
 *    // FT800 driver active configuration.
 *    ft800_cfg(ctx,cfg);
 * @endcode
 */
void ft800_cfg( ft800_t *ctx, ft800_cfg_t *cfg );

/**
 * @brief FT800 Gesture Check Function.
 * @details This function allows user to get the information about the gesture
 * ( slide direction ).
 * @param[in] ctx : FT800 context object. See #ft800_t structure definition
 * for detailed explanation.
 * @param[out] event : Touch panel gesture data. See #tp_event_t structure
 * definition for detailed explanation.
 * @return Nothing.
 * @note #ft800_process function must be called to update all events.
 *
 * @b Example
 * @code
 *    // FT800 driver object.
 *    ft800_t ft800;
 *    // Gesture event.
 *    tp_event_t event;
 *
 *    // Checking slide direction event of pressed touch.
 *    ft800_gesture( &ft800, &event );
 * @endcode
 */
void ft800_gesture( ft800_t *ctx, tp_event_t *event );

/**
 * @brief FT800 Touch Pressure Detect Function.
 * @details This function allows the touch pressure detection.
 * @param[in] ctx : FT800 context object. See #ft800_t structure definition
 * for detailed explanation.
 * @return @li @c 3 - Touch pressure is not detected,
 *         @li @c 4 - Touch pressure is detected.
 * See #tp_event_t structure definition for detailed explanation.
 * @note #ft800_process function must be called to update all events.
 *
 * @b Example
 * @code
 *    // FT800 driver object.
 *    ft800_t ft800;
 *    // Touch pressure event.
 *    tp_event_t event;
 *
 *    // Checking touch pressure event.
 *    event = ft800_press_detect( &ft800 );
 * @endcode
 */
tp_event_t ft800_press_detect( ft800_t *ctx );

/**
 * @brief FT800 Pressure Coordinates Check Function.
 * @details This function allows user to get the information about the number
 * of pressed touch points, coordinates and touch event for each pressed touch
 * point.
 * @param[in] ctx : FT800 context object. See #ft800_t structure definition
 * for detailed explanation.
 * @param[out] touch_item : Touch item data. See #tp_touch_item_t structure
 * definition for detailed explanation.
 * @return Nothing.
 * @note #ft800_process function must be called to update all events.
 *
 * @b Example
 * @code
 *    // FT800 driver object.
 *    ft800_t ft5xx6;
 *    // Touch pressure item.
 *    tp_touch_item_t tp_item;
 *
 *    // To get all necessary data information about pressed touch.
 *    ft800_press_coordinates( &ft800, &tp_item );
 * @endcode
 */
void ft800_press_coordinates( ft800_t *ctx, tp_touch_item_t *touch_item );

/**
 * @brief Initialization Touch Screen.
 * @details This function allows user to set registers of FT800 controller to
 * active state and enable recognition of press on screen. 
 * @param[in] ctx : FT800 context object. See #ft800_t structure definition
 * for detailed explanation.
 * @param[in] cfg : FT800 configuration object. See #ft800_cfg_t structure
 * definition for detailed explanation.
 * @param[in] run_calibration : Enable a calibration routine for FT800 controller.
 * @return Nothing.
 *
 * @b Example
 * @code
 *    // FT800 driver object.
 *    ft800_t ctx;
 *    // FT800 configuration object.
 *    ft800_cfg_t cfg;
 *
 *    // To set touch engine registers at active state and run calibration routine.
 *    init_touch_screen( &ctx, &cfg, true );
 * @endcode
 */
void init_touch_screen( ft800_t *ctx, ft800_cfg_t *cfg, bool run_calibration );

/**
 * @brief FT800 Process Function.
 * @details This function detects a touch pressure, and if any touch pressure
 * was detected, then collects all information about the pressed touch and
 * slide direction ( gesture ).
 * @param[in] ctx : FT800 context object. See #ft5xx6_t structure definition
 * for detailed explanation.
 * @return @li @c 0 - OK,
 *         @li @c 5 - Number of pressed touches is out of range.
 * See #tp_err_t structure definition for detailed explanation.
 * @note To update all possible events, just need to call this function before
 * the any other function for checking events is called.
 *
 * @b Example
 * @code
 *    // FT800 driver object.
 *    ft800_t ft800;
 *    // TP error code.
 *    tp_err_t error;
 *
 *    // Processing all data and events of the target touch controller.
 *    error = ft800_process( &ft800 );
 * @endcode
 */
 tp_err_t ft800_process( ft800_t *ctx, ft800_cfg_t *cfg );

 /*I can't find description */
 static tp_err_t ft800_read_press_coordinates( ft800_t *ctx, ft800_cfg_t *cfg );

 /**
 * @brief FT800 Waiting Coprocessor Function.
 * @details This function block executin code untill value in FT800_REG_CMD_WRITE
 * and FT800_REG_CMD_READ are equal.
 * @param[in] ctx : FT800 context object. See #ft800_t structure definition
 * for detailed explanation.
 * @param[in] cfg : FT800 configuration object. See #ft800_cfg_t structure
 * definition for detailed explanation.
 * @return Nothing.
 *
 * @b Example
 * @code
 *    // FT800 driver object.
 *    ft800_t ctx;
 *    // FT800 configuration object.
 *    ft800_cfg_t cfg;
 *    // FT800 display list commands offset.
 *    uint16_t cmdOffset;
 * 
 *    // Waiting for co-processor to handle FT800_REG_CMD_WRITE and FT800_REG_CMD_READ
 *    // after finishing display list.
 *    end_display_list( &ctx, &cfg, &cmdOffset ); 
 *    wait_coprocessor( &ctx, &cfg );
 * @endcode
 */
void wait_coprocessor( ft800_t *ctx, ft800_cfg_t *cfg );

 /**
 * @brief Write into RAM G Function.
 * @details This function writes a image data from generated array into RAM G memory.  
 * @param[in] ctx : FT800 context object. See #ft800_t structure definition
 * for detailed explanation.
 * @param[in] cfg : FT800 configuration object. See #ft800_cfg_t structure
 * definition for detailed explanation.
 * @param[in] cmdOffset : Display list command offset.
 * @param[in] addr : Address in FT800_RAM_G memory from where starts uploading datas of image.
 * @param[in] data : Image data from generated array.
 * @param[in] length : Lenght of data which is enrolled in FT800_RAM_G.
 * @return Nothing.
 *
 * @b Example
 * @code
 *    // FT800 driver object.
 *    ft800_t ctx;
 *    // FT800 configuration object.
 *    ft800_cfg_t cfg;
 *    // FT800 display list commands offset.
 *    uint16_t cmdOffset;
 *    // First adress in FT800_RAM_G memory.
 *    uint32_t addr = 0x0000;
 *    // Images data array.
 *    uint8_t array[ ]=....
 *    // Size of array.
 *    uint32_t size=sizeof(array)
 * 
 *    // Writing image data into FT800_RAM_G memory.
 *    write_ram_g( &ctx, &cfg, &cmdOffset, addr, array, size );
 * @endcode
 */
void write_ram_g( ft800_t *ctx, ft800_cfg_t *cfg, uint16_t *cmdOffset, uint32_t addr, const uint8_t *data, uint32_t length );

 /**
 * @brief Send Command Function.
 * @details This function sends command to FT800 co-processor.  
 * @param[in] ctx : FT800 context object. See #ft800_t structure definition
 * for detailed explanation.
 * @param[in] cfg : FT800 configuration object. See #ft800_cfg_t structure
 * definition for detailed explanation.
 * @param[in] command : Command which is being sent to FT800 co-processor.
 * @param[in] cmdOffset : Display list command offset.
 * @return Nothing.
 *
 * @b Example
 * @code
 *    // FT800 driver object.
 *    ft800_t ctx;
 *    // FT800 configuration object.
 *    ft800_cfg_t cfg;
 *    // FT800 display list commands offset.
 *    uint16_t cmdOffset;
 *
 *    // Command which starts touch calibration routine.
 *    cmd( &ctx, &cfg, FT800_CMD_CALIBRATE, &cmdOffset );
 * @endcode
 */
void cmd( ft800_t *ctx, ft800_cfg_t *cfg, uint32_t command, uint16_t *cmdOffset );

 /**
 * @brief Send Command Text Function.
 * @details This function sends command to FT800 co-processor for drawing text.
 * @param[in] ctx : FT800 context object. See #ft800_t structure definition
 * for detailed explanation.
 * @param[in] cfg : FT800 configuration object. See #ft800_cfg_t structure
 * definition for detailed explanation.
 * @param[in] cmdOffset : Display list command offset.
 * @param[in] x : X coordinate from which to start drawing the text.
 * @param[in] y : Y coordinate from which to start drawing the text.
 * @param[in] font : Seting one of avilable in-built fonts.
 * @param[in] option : Additional options for text centering.
 * @param[in] s : Text to be drawned.
 * @return Nothing.
 *
 * @b Example
 * @code
 *    // FT800 driver object.
 *    ft800_t ctx;
 *    // FT800 configuration object.
 *    ft800_cfg_t cfg;
 *    // FT800 display list commands offset.
 *    uint16_t cmdOffset;
 *
 *    // Command which draws text FT800 at position ( 50, 50 ) with font 31.
 *    start_display_list( &ctx, &cfg, &cmdOffset );
 * 
 *    cmd_text( ctx, cfg, cmdOffset, 50, 50, 31, 0, "FT800" );
 * 
 *    end_display_list( &ctx, &cfg, &cmdOffset );
 * @endcode
 */
void cmd_text( ft800_t *ctx, ft800_cfg_t *cfg, uint16_t *cmdOffset, uint16_t x, uint16_t y, uint16_t font, uint16_t options, const char *s );

/**
 * @brief Send Command Number Function.
 * @details This function sends command to FT800 co-processor for drawing number.
 * @param[in] ctx : FT800 context object. See #ft800_t structure definition
 * for detailed explanation.
 * @param[in] cfg : FT800 configuration object. See #ft800_cfg_t structure
 * definition for detailed explanation.
 * @param[in] cmdOffset : Display list command offset.
 * @param[in] x : X coordinate from which to start drawing the number.
 * @param[in] y : Y coordinate from which to start drawing the number.
 * @param[in] font : Seting one of avilable in-built fonts.
 * @param[in] option : Additional options for number centering.
 * @param[in] num : Number to be drawned.
 * @return Nothing.
 *
 * @b Example
 * @code
 *    // FT800 driver object.
 *    ft800_t ctx;
 *    // FT800 configuration object.
 *    ft800_cfg_t cfg;
 *    // FT800 display list commands offset.
 *    uint16_t cmdOffset;
 *
 *    // Command which draws number 800 at position (50,50) with font 31.
 *    start_display_list( &ctx, &cfg, &cmdOffset );
 * 
 *    cmd_number( &ctx, &cfg, &cmdOffset, 50, 50, 31, 0, "800" );
 * 
 *    end_display_list( &ctx, &cfg, &cmdOffset );
 * @endcode
 */
void cmd_number( ft800_t *ctx, ft800_cfg_t *cfg, uint16_t *cmdOffset, uint16_t x, uint16_t y, uint16_t font, uint16_t options, int32_t num );

/**
 * @brief Send Command Button Function.
 * @details This function sends command to FT800 co-processor for drawing in-built button widget. 
 * @param[in] ctx : FT800 context object. See #ft800_t structure definition
 * for detailed explanation.
 * @param[in] cfg : FT800 configuration object. See #ft800_cfg_t structure
 * definition for detailed explanation.
 * @param[in] cmdOffset : Display list command offset.
 * @param[in] x : X coordinate from which to start drawing the button.
 * @param[in] y : Y coordinate from which to start drawing the button.
 * @param[in] w : Width of button.
 * @param[in] h : Height of button.
 * @param[in] font : Seting one of avilable in-built fonts for text drawned on button.
 * @param[in] option : If it's 0 button is displayed as a 3D, else if it's 256 button is 
 * displayed as a 2D.
 * @param[in] s : Text on button to be drawned.
 * @return Nothing.
 *
 * @b Example
 * @code
 *    // FT800 driver object.
 *    ft800_t ctx;
 *    // FT800 configuration object.
 *    ft800_cfg_t cfg;
 *    // FT800 display list commands offset.
 *    uint16_t cmdOffset;
 *
 *    // Command which draws 3D button at position ( 50, 50 ) with width 100 and height
 *    // 50 on which it is drawn "Press" with font 31.
 *    start_display_list( &ctx, &cfg, &cmdOffset );
 * 
 *    cmd_button( &ctx, &cfg, &cmdOffset, 50, 50, 100, 50, 26, 0, "Press" );
 * 
 *    end_display_list( &ctx, &cfg, &cmdOffset );
 * @endcode
 */
void cmd_button( ft800_t *ctx, ft800_cfg_t *cfg, uint16_t *cmdOffset, uint16_t x, uint16_t y, uint16_t w, uint16_t h, uint16_t font, uint16_t options, const char *s );

/**
 * @brief Send Command Clock Function.
 * @details This function sends command to FT800 co-processor for drawing in-built clock widget. 
 * @param[in] ctx : FT800 context object. See #ft800_t structure definition
 * for detailed explanation.
 * @param[in] cfg : FT800 configuration object. See #ft800_cfg_t structure
 * definition for detailed explanation.
 * @param[in] cmdOffset : Display list command offset.
 * @param[in] x : X coordinate of center of clock.
 * @param[in] y : Y coordinate of center of clock.
 * @param[in] r : Radius of clock.
 * @param[in] option : Options for drawning flat clock instead of 3D or remove certain tick.
 * @param[in] h : Position of hour tick.
 * @param[in] m : Position of minutes tick.
 * @param[in] sec : Position of seconds tick.
 * @param[in] ms : Value of miliseconds.
 * @return Nothing.
 *
 * @b Example
 * @code
 *    // FT800 driver object.
 *    ft800_t ctx;
 *    // FT800 configuration object.
 *    ft800_cfg_t cfg;
 *    // FT800 display list commands offset.
 *    uint16_t cmdOffset;
 *
 *    // Command which draws 3D clock with position of center at ( 50, 50 ) with radius 100 which 
 *    // shows 12 hour and 15 minutes.
 *    start_display_list( &ctx, &cfg, &cmdOffset );
 * 
 *    cmd_clock( &ctx, &cfg, &cmdOffset, 50, 50, 100, 0, 12, 15, 0, 0 );
 * 
 *    end_display_list( &ctx, &cfg, &cmdOffset );
 * @endcode
 */
void cmd_clock( ft800_t *ctx, ft800_cfg_t *cfg, uint16_t *cmdOffset, uint16_t x, uint16_t y, uint16_t r, uint16_t options, uint16_t h, uint16_t m, uint16_t sec, uint16_t ms );

/**
 * @brief Send Command Gauge Function.
 * @details This function sends command to FT800 co-processor for drawing in-built clock widget. 
 * @param[in] ctx : FT800 context object. See #ft800_t structure definition
 * for detailed explanation.
 * @param[in] cfg : FT800 configuration object. See #ft800_cfg_t structure
 * definition for detailed explanation.
 * @param[in] cmdOffset : Display list command offset.
 * @param[in] x : X coordinate of center of clock.
 * @param[in] y : Y coordinate of center of clock.
 * @param[in] r : Radius of clock.
 * @param[in] option : Options for drawning flat gauge instead of 3D or remove certain tick.
 * @param[in] major : Number of major subdivisions on the dial.
 * @param[in] minor : Number of minor subdivisions on the dial.
 * @param[in] val : Gauge indicated value, between 0 and range, inclusive.
 * @param[in] range : Maximum value of gauge.
 * @return Nothing.
 *
 * @b Example
 * @code
 *    // FT800 driver object.
 *    ft800_t ctx;
 *    // FT800 configuration object.
 *    ft800_cfg_t cfg;
 *    // FT800 display list commands offset.
 *    uint16_t cmdOffset;
 *
 *    // Command which draws 3D gauge with position of center at ( 50, 50 ) with radius 100 
 *    // which shows value 30 form maximum 100.
 *    start_display_list( &ctx, &cfg, &cmdOffset );
 * 
 *    cmd_gauge( &ctx, &cfg, &cmdOffset, 50, 50, 100, 0, 5, 4, 30, 100 );
 * 
 *    end_display_list( &ctx, &cfg, &cmdOffset );
 * @endcode
 */
void cmd_gauge( ft800_t *ctx, ft800_cfg_t *cfg, uint16_t *cmdOffset, uint16_t x, uint16_t y, uint16_t r, uint16_t options, uint16_t major, uint16_t minor, uint16_t val, uint16_t range );

/**
 * @brief Send Command Gradient Function.
 * @details This function sends command to FT800 co-processor for drawing gradient color in rectangle.
 * @param[in] ctx : FT800 context object. See #ft800_t structure definition
 * for detailed explanation.
 * @param[in] cfg : FT800 configuration object. See #ft800_cfg_t structure
 * definition for detailed explanation.
 * @param[in] cmdOffset : Display list command offset.
 * @param[in] x0 : X coordinate from which to start drawing the gradient rectangle.
 * @param[in] y0 : Y coordinate from which to start drawing the gradient rectangle.
 * @param[in] x1 : X coordinate to which it is drawn.
 * @param[in] y1 : Y coordinate to which it is drawn.
 * @param[in] r1 : Value of starting red color component.
 * @param[in] g1 : Value of starting green color component.
 * @param[in] b1 : Value of starting blue color component.
 * @param[in] r2 : Value of ending red color component.
 * @param[in] g2 : Value of ending green color component.
 * @param[in] b2 : Value of ending blue color component.
 * @return Nothing.
 * @note To prevent color bleed, use in combination with FT800_SCISSOR_XY and FT800_SCISSOR_SIZE.
 *
 * @b Example
 * @code
 *    // FT800 driver object.
 *    ft800_t ctx;
 *    // FT800 configuration object.
 *    ft800_cfg_t cfg;
 *    // FT800 display list commands offset.
 *    uint16_t cmdOffset;
 *
 *    // Command which draws red-blue gradient rectangle with width 100 and height 100
 *    // from position ( 50, 50 ). 
 *    start_display_list( &ctx, &cfg, &cmdOffset );
 *      
 *    cmd( &ctx, &cfg, FT800_SCISSOR_XY( 50, 50 ), cmdOffset );
 *    cmd( &ctx, &cfg, FT800_SCISSOR_SIZE( 100, 100 ), cmdOffset );
 *    cmd_gradient( &ctx, &cfg, cmdOffset, 50, 50, 100, 100, 255, 0, 0, 0, 0, 255 );
 * 
 *    end_display_list( &ctx, &cfg, &cmdOffset );
 * @endcode
 */
void cmd_gradient( ft800_t *ctx, ft800_cfg_t *cfg, uint16_t *cmdOffset, uint16_t x0, uint16_t y0, uint16_t x1, uint16_t y1, uint8_t r1, uint8_t g1, uint8_t b1, uint8_t r2, uint8_t g2, uint8_t b2 );

/**
 * @brief Send Command Keys Function.
 * @details This function sends command to FT800 co-processor for drawing in-built keys widget.
 * @param[in] ctx : FT800 context object. See #ft800_t structure definition
 * for detailed explanation.
 * @param[in] cfg : FT800 configuration object. See #ft800_cfg_t structure
 * definition for detailed explanation.
 * @param[in] cmdOffset : Display list command offset.
 * @param[in] x : X coordinate from which to start drawing the keys.
 * @param[in] y : Y coordinate from which to start drawing the keys.
 * @param[in] w : Width of one key.
 * @param[in] h : Height of one key.
 * @param[in] font : Seting one of avilable in-built fonts for text drawned on button.
 * @param[in] option : If it's 0 key is displayed as a 3D, else if it's 256 key is 
 * displayed as a 2D.
 * @param[in] s : Text where each letter represents the letter on each key, respectively.
 * @return Nothing.
 *
 * @b Example
 * @code
 *    // FT800 driver object.
 *    ft800_t ctx;
 *    // FT800 configuration object.
 *    ft800_cfg_t cfg;
 *    // FT800 display list commands offset.
 *    uint16_t cmdOffset;
 *
 *    // Command which draws 3 3D key at position from ( 50, 50 ) with width 50 and height
 *    // 50 on which it is drawn one number each starting from 1 with font 20.
 *    start_display_list( &ctx, &cfg, &cmdOffset );
 * 
 *    cmd_keys( &ctx, &cfg, cmdOffset, 50, 50, 50, 50, 20, 0, "123" );
 * 
 *    end_display_list( &ctx, &cfg, &cmdOffset );
 * @endcode
 */
void cmd_keys(ft800_t *ctx, ft800_cfg_t *cfg,uint16_t* cmdOffset,uint16_t x,uint16_t y,uint16_t w,uint16_t h,uint16_t font,uint16_t options,const char *s );

/**
 * @brief Send Command Progress Function.
 * @details This function sends command to FT800 co-processor for drawing in-built progress bar widget.
 * @param[in] ctx : FT800 context object. See #ft800_t structure definition
 * for detailed explanation.
 * @param[in] cfg : FT800 configuration object. See #ft800_cfg_t structure
 * definition for detailed explanation.
 * @param[in] cmdOffset : Display list command offset.
 * @param[in] x : X coordinate from which to start drawing the progress bar.
 * @param[in] y : Y coordinate from which to start drawing the progress bar.
 * @param[in] w : Width of progress bar.
 * @param[in] h : Height of progress bar.
 * @param[in] option : If it's 0 progress bar is displayed as a 3D, else if it's 256 
 * progress bar is displayed as a 2D.
 * @param[in] val : Current value of progress bar.
 * @param[in] range : Maximum value of progress bar.
 * @return Nothing.
 *
 * @b Example
 * @code
 *    // FT800 driver object.
 *    ft800_t ctx;
 *    // FT800 configuration object.
 *    ft800_cfg_t cfg;
 *    // FT800 display list commands offset.
 *    uint16_t cmdOffset;
 *
 *    // Command which draws 3 3D progress bar at position from ( 50, 50 ) with width 150 and height
 *    // 10 with position 75 of maximum 100
 *    start_display_list( &ctx, &cfg, &cmdOffset );
 *    
 *    cmd_progress( &ctx, &cfg, &cmdOffset, 50, 50, 150, 10, 0, 75, 100 );
 * 
 *    end_display_list( &ctx, &cfg, &cmdOffset );
 * @endcode
 */
void cmd_progress( ft800_t *ctx, ft800_cfg_t *cfg, uint16_t *cmdOffset, uint16_t x, uint16_t y, uint16_t w, uint16_t h, uint16_t options, uint16_t val, uint16_t range );

/**
 * @brief Send Command Slider Function.
 * @details This function sends command to FT800 co-processor for drawing in-built slider widget.
 * @param[in] ctx : FT800 context object. See #ft800_t structure definition
 * for detailed explanation.
 * @param[in] cfg : FT800 configuration object. See #ft800_cfg_t structure
 * definition for detailed explanation.
 * @param[in] cmdOffset : Display list command offset.
 * @param[in] x : X coordinate from which to start drawing the slider.
 * @param[in] y : Y coordinate from which to start drawing the slider.
 * @param[in] w : Width of slider.
 * @param[in] h : Height of slider.
 * @param[in] option : If it's 0 progress bar is displayed as a 3D, else if it's 256 
 * progress bar is displayed as a 2D.
 * @param[in] val : Current value of slider.
 * @param[in] range : Maximum value of slider.
 * @return Nothing.
 *
 * @b Example
 * @code
 *    // FT800 driver object.
 *    ft800_t ctx;
 *    // FT800 configuration object.
 *    ft800_cfg_t cfg;
 *    // FT800 display list commands offset.
 *    uint16_t cmdOffset;
 *
 *    // Command which draws 3 3D slider at position from ( 50, 50 ) with width 150 and height
 *    // 10 with position 50 of maximum 100.
 *    start_display_list( &ctx, &cfg, &cmdOffset );
 * 
 *    slider_draw( &ctx, &cfg, &cmdOffset, 50, 50, 150, 10, 50, 100 );
 * 
 *    end_display_list( &ctx, &cfg, &cmdOffset );
 * @endcode
 */
void cmd_slider( ft800_t *ctx, ft800_cfg_t *cfg, uint16_t *cmdOffset, uint16_t x, uint16_t y, uint16_t w, uint16_t h, uint16_t options, uint16_t val, uint16_t range );

/**
 * @brief Send Command Scrollbar Function.
 * @details This function sends command to FT800 co-processor for drawing in-built scrollbar widget.
 * @param[in] ctx : FT800 context object. See #ft800_t structure definition
 * for detailed explanation.
 * @param[in] cfg : FT800 configuration object. See #ft800_cfg_t structure
 * definition for detailed explanation.
 * @param[in] cmdOffset : Display list command offset.
 * @param[in] x : X coordinate from which to start drawing the scrollbar.
 * @param[in] y : Y coordinate from which to start drawing the scrollbar.
 * @param[in] w : Width of scrollbar.
 * @param[in] h : Height of scrollbar.
 * @param[in] option : If it's 0 scrollbar is displayed as a 3D, else if it's 256 
 * scrollbar is displayed as a 2D.
 * @param[in] val : Current value of scrollbar.
 * @param[in] size : Size of bar.
 * @param[in] range : Maximum value of scrollbar.
 * @return Nothing.
 *
 * @b Example
 * @code
 *    // FT800 driver object.
 *    ft800_t ctx;
 *    // FT800 configuration object.
 *    ft800_cfg_t cfg;
 *    // FT800 display list commands offset.
 *    uint16_t cmdOffset;
 *
 *    // Command which draws 3 3D scrollbar at position from ( 20, 50 ) with width 120 and height
 *    // 8 and size of bar 40 with position 10 of maximum 100.
 *    start_display_list( &ctx, &cfg, &cmdOffset );
 * 
 *    cmd_scrollbar( &ctx, &cfg, cmdOffset, 20, 50, 120, 8, 0, 10, 40, 100 );
 * 
 *    end_display_list( &ctx, &cfg, &cmdOffset );
 * @endcode
 */
void cmd_scrollbar( ft800_t *ctx, ft800_cfg_t *cfg, uint16_t *cmdOffset, uint16_t x, uint16_t y, uint16_t w, uint16_t h, uint16_t options, uint16_t val, uint16_t size, uint16_t range );

/**
 * @brief Send Command Dial Function.
 * @details This function sends command to FT800 co-processor for drawning in-built dial widget.
 * @param[in] ctx : FT800 context object. See #ft800_t structure definition
 * for detailed explanation.
 * @param[in] cfg : FT800 configuration object. See #ft800_cfg_t structure
 * definition for detailed explanation.
 * @param[in] cmdOffset : Display list command offset.
 * @param[in] x : X coordinate of center of dial .
 * @param[in] y : Y coordinate of center of dial.
 * @param[in] r : Radius of dial.
 * @param[in] option : Options for drawning flat dial instead of 3D.
 * @param[in] val : Position of dial pointer in range between 0 and 65535.
 * @return Nothing.
 *
 * @b Example
 * @code
 *    // FT800 driver object.
 *    ft800_t ctx;
 *    // FT800 configuration object.
 *    ft800_cfg_t cfg;
 *    // FT800 display list commands offset.
 *    uint16_t cmdOffset;
 *
 *    // Command which draw 3D dial with position of center at ( 100, 100 ) with radius 50 with 
 *    position of pointer stright up.
 *    start_display_list( &ctx, &cfg, &cmdOffset );
 * 
 *    cmd_dial( &ctx, &cfg, &cmdOffset, 100, 100, 50, 0, 0x8000 );
 * 
 *    end_display_list( &ctx, &cfg, &cmdOffset );
 * @endcode
 */
void cmd_dial( ft800_t *ctx, ft800_cfg_t *cfg, uint16_t *cmdOffset, uint16_t x, uint16_t y, uint16_t r, uint16_t options, uint16_t val );

/**
 * @brief Command Toggle.
 * @details This function send command to FT800 co-processor for drawning in-built toggle widget.
 * @param[in] ctx : FT800 context object. See #ft800_t structure definition
 * for detailed explanation.
 * @param[in] cfg : FT800 configuration object. See #ft800_cfg_t structure
 * definition for detailed explanation.
 * @param[in] cmdOffset : Display list command offset.
 * @param[in] x : X coordinate from which to start drawing the toggle.
 * @param[in] y : Y coordinate from which to start drawing the toggle.
 * @param[in] w : Width of toggle.
 * @param[in] font : Seting one of avilable in-built fonts for text drawned on toggle.
 * @param[in] option : If it's 0 toggle is displayed as a 3D, else if it's 256 togle is 
 * displayed as a 2D.
 * @param[in] state : The position the toggle is currently in.
 * @param[in] s : Text which mark state of toggle.
 * @return Nothing.
 *
 * @b Example
 * @code
 *    // FT800 driver object.
 *    ft800_t ctx;
 *    // FT800 configuration object.
 *    ft800_cfg_t cfg;
 *    // FT800 display list commands offset.
 *    uint16_t cmdOffset;
 *
 *    // Command which draw 3D toggle at position ( 60, 20 ) with width 33 in state 0 ( no ).
 *    start_display_list( &ctx, &cfg, &cmdOffset );
 * 
 *    cmd_toggle( &ctx, &cfg, &cmdOffset, 60, 20, 33, 27, 0, 0, “no” “ \xff” “yes” );
 * 
 *    end_display_list( &ctx, &cfg, &cmdOffset );
 * @endcode
 */
void cmd_toggle( ft800_t *ctx, ft800_cfg_t *cfg, uint16_t *cmdOffset, uint16_t x, uint16_t y, uint16_t w, uint16_t font, uint16_t options, uint16_t state, const char *s );

/**
 * @brief Command Track.
 * @details This function send command to FT800 co-processor to start tracking movement of press
 * applied at drawned object after this function.
 * @param[in] ctx : FT800 context object. See #ft800_t structure definition
 * for detailed explanation.
 * @param[in] cfg : FT800 configuration object. See #ft800_cfg_t structure
 * definition for detailed explanation.
 * @param[in] cmdOffset : Display list command offset.
 * @param[in] x : X coordinate from which to start tracking press and movement.
 * @param[in] y : Y coordinate from which to start tracking press and movement.
 * @param[in] w : Width of area on which press and movement are tracked(for linear object;
 * for rotary object is constant 1).
 * @param[in] h : Height of area on which press and movement are tracked(for linear object;
 * for rotary object is constant 1).
 * @param[in] tag : Tag of the object that being tracked.
 * @return Nothing.
 *
 * @b Example
 * @code
 *    // FT800 driver object.
 *    ft800_t ctx;
 *    // FT800 configuration object.
 *    ft800_cfg_t cfg;
 *    // FT800 display list commands offset.
 *    uint16_t cmdOffset;
 *    // Value read from register.
 *    uint32_t tracker;
 * 
 *    // Command for tracking movement of dial and moving his pointer.
 *    cmd( &ctx, &cfg, FT800_TAG_MASK( 1 ), &cmdOffset );
 *    cmd( &ctx, &cfg, FT800_TAG( 1 ), &cmdOffset );
 *    dial_draw( &ctx, &cfg, cmdOffset, 90, 180, 50, angle );
 *    cmd( &ctx, &cfg, FT800_TAG_MASK( 0 ), &cmdOffset );
 *
 *    track( &ctx, &cfg, &cmdOffset, 90, 180, 1, 1, 1 );
 *    tracker = read_data( &ctx, &cfg, FT800_REG_TRACKER, 32 ); 
 *    if ( ( tracker & 0xFF ) == 1){ 
 *      angle = tracker >> 16; 
 *    }
 * @endcode
 */
void cmd_track( ft800_t *ctx, ft800_cfg_t *cfg, uint16_t *cmdOffset, uint16_t x, uint16_t y, uint16_t w, uint16_t h, uint16_t tag );

/**
 * @brief Start Display List.
 * @details This function start new display list displayed on FT800 screen.
 * @param[in] ctx : FT800 context object. See #ft800_t structure definition
 * for detailed explanation.
 * @param[in] cfg : FT800 configuration object. See #ft800_cfg_t structure
 * definition for detailed explanation.
 * @param[in] cmdOffset : Display list command offset.
 * @return Nothing.
 *
 * @b Example
 * @code
 *    // FT800 driver object.
 *    ft800_t ctx;
 *    // FT800 configuration object.
 *    ft800_cfg_t cfg;
 *    // FT800 display list commands offset.
 *    uint16_t cmdOffset;
 *
 *    // Command starting new display list
 *    start_display_list( &ctx, &cfg, &cmdOffset );
 * @endcode
 */
void start_display_list( ft800_t *ctx, ft800_cfg_t *cfg, uint16_t *cmdOffset );

/**
 * @brief End Display List.
 * @details This function finish display list displayed on FT800 screen.
 * @param[in] ctx : FT800 context object. See #ft800_t structure definition
 * for detailed explanation.
 * @param[in] cfg : FT800 configuration object. See #ft800_cfg_t structure
 * definition for detailed explanation.
 * @param[in] cmdOffset : Display list command offset.
 * @return Nothing.
 *
 * @b Example
 * @code
 *    // FT800 driver object.
 *    ft800_t ctx;
 *    // FT800 configuration object.
 *    ft800_cfg_t cfg;
 *    // FT800 display list commands offset.
 *    uint16_t cmdOffset;
 *
 *    // Command starting new display list.
 *    end_display_list( &ctx, &cfg, &cmdOffset );
 * @endcode
 */
void end_display_list(ft800_t *ctx, ft800_cfg_t *cfg, uint16_t *cmdOffset );

/**
 * @brief Draw Button.
 * @details This function draw button drawned in NECTO Designer.
 * @param[in] ctx : FT800 context object. See #ft800_t structure definition
 * for detailed explanation.
 * @param[in] cfg : FT800 configuration object. See #ft800_cfg_t structure
 * definition for detailed explanation.
 * @param[in] cmdOffset : Display list command offset.
 * @param[in] button : Structure which contains all necessary parameters from NECTO Designer 
 * for drawing button.
 * @return Nothing.
 *
 * @b Example
 * @code
 *    // FT800 driver object.
 *    ft800_t ctx;
 *    // FT800 configuration object.
 *    ft800_cfg_t cfg;
 *    // FT800 display list commands offset.
 *    uint16_t cmdOffset;
 *
 *    // These functions are drawing button drawned in NECTO Designer and show on screen of FT800.
 *    start_display_list( &ctx, &cfg, &cmdOffset );   
 *   
 *    draw_button( &ctx, &cfg, &cmdOffset, main_screen.RoundedButton_0 );
 * 
 *    end_display_list( &ctx, &cfg, &cmdOffset );
 * @endcode
 */
void draw_button( ft800_t *ctx, ft800_cfg_t *cfg, uint16_t *cmdOffset, ft800_rounded_button *button );

/**
 * @brief Draw Circle.
 * @details This function draw circle drawned in NECTO Designer.
 * @param[in] ctx : FT800 context object. See #ft800_t structure definition
 * for detailed explanation.
 * @param[in] cfg : FT800 configuration object. See #ft800_cfg_t structure
 * definition for detailed explanation.
 * @param[in] cmdOffset : Display list command offset.
 * @param[in] circle : Structure which contains all necessary parameters from NECTO Designer 
 * for drawing circle.
 * @return Nothing.
 *
 * @b Example
 * @code
 *    // FT800 driver object.
 *    ft800_t ctx;
 *    // FT800 configuration object.
 *    ft800_cfg_t cfg;
 *    // FT800 display list commands offset.
 *    uint16_t cmdOffset;
 *
 *    // These functions are drawing circle drawned in NECTO Designer and show on screen of FT800.
 *    start_display_list( &ctx, &cfg, &cmdOffset );
 *   
 *    draw_circle( &ctx, &cfg, &cmdOffset, main_screen.Circle_0 );
 * 
 *    end_display_list( &ctx, &cfg, &cmdOffset );
 * @endcode
 */
void draw_circle( ft800_t *ctx, ft800_cfg_t *cfg, uint16_t *cmdOffset, ft800_circle *circle );

/**
 * @brief Draw Label.
 * @details This function draw text label drawned in NECTO Designer.
 * @param[in] ctx : FT800 context object. See #ft800_t structure definition
 * for detailed explanation.
 * @param[in] cfg : FT800 configuration object. See #ft800_cfg_t structure
 * definition for detailed explanation.
 * @param[in] cmdOffset : Display list command offset.
 * @param[in] label : Structure which contains all necessary parameters from NECTO Designer 
 * for drawing text label.
 * @return Nothing.
 *
 * @b Example
 * @code
 *    // FT800 driver object.
 *    ft800_t ctx;
 *    // FT800 configuration object.
 *    ft800_cfg_t cfg;
 *    // FT800 display list commands offset
 *    uint16_t cmdOffset;
 *
 *    // These functions are drawing text label drawned in NECTO Designer and show on screen of FT800.
 *    start_display_list( &ctx, &cfg, &cmdOffset );
 *   
 *    draw_label( &ctx, &cfg, &cmdOffset, main_screen.Label_0 );
 * 
 *    end_display_list( &ctx, &cfg, &cmdOffset );
 * @endcode
 */
void draw_label( ft800_t *ctx, ft800_cfg_t *cfg, uint16_t *cmdOffset, ft800_label *label );

/**
 * @brief Draw Line.
 * @details This function draw line drawned in NECTO Designer.
 * @param[in] ctx : FT800 context object. See #ft800_t structure definition
 * for detailed explanation.
 * @param[in] cfg : FT800 configuration object. See #ft800_cfg_t structure
 * definition for detailed explanation.
 * @param[in] cmdOffset : Display list command offset.
 * @param[in] line : Structure which contains all necessary parameters from NECTO Designer 
 * for drawing line.
 * @return Nothing.
 *
 * @b Example
 * @code
 *    // FT800 driver object.
 *    ft800_t ctx;
 *    // FT800 configuration object.
 *    ft800_cfg_t cfg;
 *    // FT800 display list commands offset.
 *    uint16_t cmdOffset;
 *
 *    // These functions are drawing line drawned in NECTO Designer and show on screen of FT800.
 *    start_display_list( &ctx, &cfg, &cmdOffset );
 *   
 *    draw_line( &ctx, &cfg, &cmdOffset, main_screen.Line_0 );
 * 
 *    end_display_list( &ctx, &cfg, &cmdOffset );
 * @endcode
 */
void draw_line( ft800_t *ctx, ft800_cfg_t *cfg, uint16_t *cmdOffset, ft800_line *line );

/**
 * @brief Draw Box.
 * @details This function draw box drawned in NECTO Designer.
 * @param[in] ctx : FT800 context object. See #ft800_t structure definition
 * for detailed explanation.
 * @param[in] cfg : FT800 configuration object. See #ft800_cfg_t structure
 * definition for detailed explanation.
 * @param[in] cmdOffset : Display list command offset.
 * @param[in] box : Structure which contains all necessary parameters from NECTO Designer 
 * for drawing box.
 * @return Nothing.
 *
 * @b Example
 * @code
 *    // FT800 driver object.
 *    ft800_t ctx;
 *    // FT800 configuration object.
 *    ft800_cfg_t cfg;
 *    // FT800 display list commands offset.
 *    uint16_t cmdOffset;
 *
 *    // These functions are drawing box drawned in NECTO Designer and show on screen of FT800.
 *    start_display_list( &ctx, &cfg, &cmdOffset );
 *   
 *    draw_box( &ctx, &cfg, &cmdOffset, main_screen.RoundedBox_0 );
 * 
 *    end_display_list( &ctx, &cfg, &cmdOffset );
 * @endcode
 */
void draw_box( ft800_t *ctx, ft800_cfg_t *cfg, uint16_t *cmdOffset, ft800_rounded_box *box );

/**
 * @brief Draw Progress Bar Function.
 * @details This function draws progress bar from NECTO Designer window.
 * @param[in] ctx : FT800 context object. See #ft800_t structure definition
 * for detailed explanation.
 * @param[in] cfg : FT800 configuration object. See #ft800_cfg_t structure
 * definition for detailed explanation.
 * @param[in] cmdOffset : Display list command offset.
 * @param[in] progress_bar : Structure which contains all necessary parameters from NECTO Designer 
 * for drawing progress bar.
 * @return Nothing.
 *
 * @b Example
 * @code
 *    // FT800 driver object.
 *    ft800_t ctx;
 *    // FT800 configuration object.
 *    ft800_cfg_t cfg;
 *    // FT800 display list commands offset.
 *    uint16_t cmdOffset;
 *
 *    // These functions are drawing progress bar drawned in NECTO Designer and show on screen of FT800.
 *    start_display_list( &ctx, &cfg, &cmdOffset );
 *   
 *    draw_progress_bar( &ctx, &cfg, &cmdOffset, main_screen.ProgressBar_0 );
 * 
 *    end_display_list( &ctx, &cfg, &cmdOffset );
 * @endcode
 */
void draw_progress_bar( ft800_t *ctx, ft800_cfg_t *cfg, uint16_t *cmdOffset, ft800_progress_bar *progress_bar );

/**
 * @brief Draw Check Box Function.
 * @details This function draws check box from NECTO Designer window.
 * @param[in] ctx : FT800 context object. See #ft800_t structure definition
 * for detailed explanation.
 * @param[in] cfg : FT800 configuration object. See #ft800_cfg_t structure
 * definition for detailed explanation.
 * @param[in] cmdOffset : Display list command offset.
 * @param[in] check_box : Structure which contains all necessary parameters from NECTO Designer 
 * for drawing check box.
 * @return Nothing.
 *
 * @b Example
 * @code
 *    // FT800 driver object.
 *    ft800_t ctx;
 *    // FT800 configuration object.
 *    ft800_cfg_t cfg;
 *    // FT800 display list commands offset.
 *    uint16_t cmdOffset;
 *
 *    // These functions are drawing check box drawned in NECTO Designer and show on screen of FT800.
 *    start_display_list( &ctx, &cfg, &cmdOffset );
 *   
 *    draw_check_box( &ctx, &cfg, &cmdOffset, main_screen.CheckBox_0 );
 * 
 *    end_display_list(&ctx, &cfg, &cmdOffset );
 * @endcode
 */
void draw_check_box( ft800_t *ctx, ft800_cfg_t *cfg, uint16_t *cmdOffset, ft800_check_box *check_box );

/**
 * @brief Draw Radio Button.
 * @details This function draw radio button drawned in NECTO Designer.
 * @param[in] ctx : FT800 context object. See #ft800_t structure definition
 * for detailed explanation.
 * @param[in] cfg : FT800 configuration object. See #ft800_cfg_t structure
 * definition for detailed explanation.
 * @param[in] cmdOffset : Display list command offset.
 * @param[in] radio_button: Structure which contains all necessary parameters from NECTO Designer 
 * for drawing check box.
 * @return Nothing.
 *
 * @b Example
 * @code
 *    // FT800 driver object.
 *    ft800_t ctx;
 *    // FT800 configuration object.
 *    ft800_cfg_t cfg;
 *    // FT800 display list commands offset.
 *    uint16_t cmdOffset;
 *
 *    // These functions are drawing radio button drawned in NECTO Designer and show on screen of FT800.
 *    start_display_list( &ctx, &cfg, &cmdOffset );
 *   
 *    draw_radio_button( &ctx, &cfg, &cmdOffset, main_screen.RadioButton_0 );
 * 
 *    end_display_list( &ctx, &cfg, &cmdOffset );
 * @endcode
 */
void draw_radio_button( ft800_t *ctx, ft800_cfg_t *cfg, uint16_t *cmdOffset, ft800_radio_button *radio_button );

/**
 * @brief Draw Ellipse.
 * @details This function draw ellipse drawned in NECTO Designer.
 * @param[in] ctx : FT800 context object. See #ft800_t structure definition
 * for detailed explanation.
 * @param[in] cfg : FT800 configuration object. See #ft800_cfg_t structure
 * definition for detailed explanation.
 * @param[in] cmdOffset : Display list command offset.
 * @param[in] ellipse: Structure which contains all necessary parameters from NECTO Designer 
 * for drawing ellipse.
 * @return Nothing.
 *
 * @b Example
 * @code
 *    // FT800 driver object.
 *    ft800_t ctx;
 *    // FT800 configuration object.
 *    ft800_cfg_t cfg;
 *    // FT800 display list commands offset.
 *    uint16_t cmdOffset;
 *
 *    // These functions are drawing ellipse drawned in NECTO Designer and show on screen of FT800.
 *    start_display_list( &ctx, &cfg, &cmdOffset );
 *   
 *    draw_ellipse( &ctx, &cfg ,&cmdOffset, main_screen.Ellipse_0 );
 * 
 *    end_display_list( &ctx, &cfg, &cmdOffset );
 * @endcode
 */
void draw_ellipse( ft800_t *ctx, ft800_cfg_t *cfg, uint16_t *cmdOffset, ft800_ellipse *ellipse );

/**
 * @brief Draw Image Function.
 * @details This function draws image uploaded in NECTO Designer window.
 * @param[in] ctx : FT800 context object. See #ft800_t structure definition
 * for detailed explanation.
 * @param[in] cfg : FT800 configuration object. See #ft800_cfg_t structure
 * definition for detailed explanation.
 * @param[in] cmdOffset : Display list command offset.
 * @param[in] image: Structure which contains all necessary parameters from NECTO Designer 
 * for drawing image.
 * @return Nothing.
 *
 * @b Example
 * @code
 *    // FT800 driver object.
 *    ft800_t ctx;
 *    // FT800 configuration object.
 *    ft800_cfg_t cfg;
 *    // FT800 display list commands offset.
 *    uint16_t cmdOffset;
 *
 *    // These functions are drawing image uploaded in NECTO Designer and show on screen of FT800.
 *    start_display_list( &ctx, &cfg, &cmdOffset );
 *   
 *    draw_ellipse( &ctx, &cfg, &cmdOffset, main_screen.Ellipse_0 );
 * 
 *    end_display_list( &ctx, &cfg, &cmdOffset );
 * @endcode
 */
void draw_image_image( ft800_t *ctx, ft800_cfg_t *cfg, uint16_t *cmdOffset, ft800_image *image );

/**
 * @brief RGB Converter
 * @details This function convert hex number which represent RGB565 color data into 0 - 255 
 * value for specific color.
 * @param[in] color : Hex number which represent RGB565 data of color.
 * @param[in] name: The name of the color ( red, green or blue ) extracted from the hex value.
 * @return Value in range 0 - 255.
 *
 * @b Example
 * @code
 *
 *    // Value of color in RGB565 format.
 *    uint16_t color=0x8BD0
 * 
 *    // Variable for red color.
 *    uint8_t r_color;
 *
 *    // This function gets value of red component from RGB565 color.
 *    r_color = rgb_convert( color, "red" );
 * @endcode
 */
uint8_t rgb_convert( uint16_t color, char *name );

/**
 * @brief Draw Circle's Edges Function.
 * @details This function draws edges of circle, without  interior filling.
 * @param[in] ctx : FT800 context object. See #ft800_t structure definition
 * for detailed explanation.
 * @param[in] cfg : FT800 configuration object. See #ft800_cfg_t structure
 * definition for detailed explanation.
 * @param[in] cmdOffset : Display list command offset.
 * @param[in] cx: X coordinate of center of circle.
 * @param[in] cy: Y coordinate of center of circle.
 * @param[in] width: Diameter of circle.
 * @param[in] pen_color: The color in which the edges will be drawn.
 * @param[in] pen_width: Width of edges.
 * @return Nothing.
 *
 * @b Example
 * @code
 *    // FT800 driver object.
 *    ft800_t ctx;
 *    // FT800 configuration object.
 *    ft800_cfg_t cfg;
 *    // FT800 display list commands offset.
 *    uint16_t cmdOffset;
 *    // Value of color.
 *    uint16_t pen_color=0xFFFF;
 *
 *    // These functions are drawing white edges of circle with width of it 5 and with 
 *    // position of center at ( 100, 100 ) and with diameter of 100 and show on screen of FT800.
 *    start_display_list( &ctx, &cfg, &cmdOffset );
 *   
 *    draw_edges_circle( &ctx, &cfg, &cmdOffset, 100, 100, 100, pen_color, 5 );
 * 
 *    end_display_list( &ctx, &cfg, &cmdOffset );
 * @endcode
 */
void draw_edges_circle( ft800_t *ctx, ft800_cfg_t *cfg, uint16_t *cmdOffset, uint16_t cx, uint16_t cy, uint16_t width, uint16_t pen_color, uint16_t pen_width );

/**
 * @brief Draw Circle Gradient Function.
 * @details This function draws circle filled with specifics colors with gradient transition.
 * @param[in] ctx : FT800 context object. See #ft800_t structure definition
 * for detailed explanation.
 * @param[in] cfg : FT800 configuration object. See #ft800_cfg_t structure
 * definition for detailed explanation.
 * @param[in] cmdOffset : Display list command offset.
 * @param[in] cx: X coordinate of center of circle.
 * @param[in] cy: Y coordinate of center of circle.
 * @param[in] diameter: Diameter of circle.
 * @param[in] s_color: The starting color with which the circle will be filled.
 * @param[in] e_color: The final color with which the circle will be filled.
 * @param[in] variant: Type of gradient transition.
 * @return Nothing.
 *
 * @b Example
 * @code
 *    // FT800 driver object.
 *    ft800_t ctx;
 *    // FT800 configuration object.
 *    ft800_cfg_t cfg;
 *    // FT800 display list commands offset.
 *    uint16_t cmdOffset;
 *    // Value of starting color. 
 *    uint16_t pen_color=0xF800;
 *    // Value of ending color. 
 *    uint16_t pen_color=0x001F;
 *
 *    // These functions fill a circular area with two colors that flow in a 
 *    // gradient with position of center at ( 50, 50 ) and width 100 and plot them on the FT800 display.
 *    start_display_list( &ctx, &cfg, &cmdOffset );
 *   
 *    draw_gradient_circle( &ctx, &cfg, &cmdOffset, 50, 50, 100, s_color, e_color, FT800_GRADIENT_TOP_BOTTOM );
 * 
 *    end_display_list( &ctx, &cfg, &cmdOffset );
 * @endcode
 */
void draw_gradient_circle( ft800_t *ctx, ft800_cfg_t *cfg, uint16_t *cmdOffset, uint16_t cx, uint16_t cy, uint16_t diameter, uint16_t s_color, uint16_t e_color, uint8_t type );

/**
 * @brief Draw Ellipse's Edges Function.
 * @details This function draws edges of ellipse, without  interior filling.
 * @param[in] ctx : FT800 context object. See #ft800_t structure definition
 * for detailed explanation.
 * @param[in] cfg : FT800 configuration object. See #ft800_cfg_t structure
 * definition for detailed explanation.
 * @param[in] cmdOffset : Display list command offset.
 * @param[in] cx: X coordinate of center of ellipse.
 * @param[in] cy: Y coordinate of center of ellipse.
 * @param[in] width: Width of ellipse.
 * @param[in] height: Height of ellipse.
 * @param[in] pen_color: The color in which the edges will be drawn.
 * @param[in] pen_width: Width of edges.
 * @return Nothing.
 *
 * @b Example
 * @code
 *    // FT800 driver object.
 *    ft800_t ctx;
 *    // FT800 configuration object.
 *    ft800_cfg_t cfg;
 *    // FT800 display list commands offset.
 *    uint16_t cmdOffset;
 *    // Value of color.
 *    uint16_t pen_color=0xFFFF;
 *
 *    // These functions are drawing white edges of ellipse with width of it 5 and with 
 *    // position of center at ( 100, 100 ) and with width of 100 and height of 50 and 
 *    // show on screen of FT800.
 *    start_display_list( &ctx, &cfg, &cmdOffset );
 *   
 *    draw_edges_ellipse( &ctx, &cfg, &cmdOffset, 100, 100, 100, 50, pen_color, 5 );
 * 
 *    end_display_list( &ctx, &cfg, &cmdOffset );
 * @endcode
 */
void draw_edges_ellipse( ft800_t *ctx, ft800_cfg_t *cfg, uint16_t *cmdOffset, uint16_t cx, uint16_t cy, uint16_t width, uint16_t height, uint16_t pen_color, uint16_t pen_width );

/**
 * @brief Draw Ellipse Gradient Function.
 * @details This function draws elliptical area filled in specifics colors with gradient transition.
 * @param[in] ctx : FT800 context object. See #ft800_t structure definition
 * for detailed explanation.
 * @param[in] cfg : FT800 configuration object. See #ft800_cfg_t structure
 * definition for detailed explanation.
 * @param[in] cmdOffset : Display list command offset.
 * @param[in] x: X coordinate of center of ellipse.
 * @param[in] y: Y coordinate of center of ellipse.
 * @param[in] width: Width of ellipse.
 * @param[in] width: Height of ellipse.
 * @param[in] s_color: The starting color with which the ellipse will be filled.
 * @param[in] e_color: The final color with which the ellipse will be filled.
 * @param[in] variant: Type of gradient transition.
 * @return Nothing.
 *
 * @b Example
 * @code
 *    // FT800 driver object.
 *    ft800_t ctx;
 *    // FT800 configuration object.
 *    ft800_cfg_t cfg;
 *    // FT800 display list commands offset.
 *    uint16_t cmdOffset;
 *    // Value of starting color. 
 *    uint16_t pen_color=0xF800;
 *    // Value of ending color. 
 *    uint16_t pen_color=0x001F;
 *
 *    // These functions fill a elliptical area with two colors that flow in a 
 *    // gradient with position of center at ( 50, 50 ) and width 100 and height 50 and 
 *    // plot them on the FT800 display.
 *    start_display_list( &ctx, &cfg, &cmdOffset );
 *   
 *    draw_gradient_circle( &ctx, &cfg, &cmdOffset, 50, 50, 100, s_color, e_color, FT800_GRADIENT_TOP_BOTTOM );
 * 
 *    end_display_list( &ctx, &cfg, &cmdOffset );
 * @endcode
 */
void draw_gradient_ellipse( ft800_t *ctx, ft800_cfg_t *cfg, uint16_t *cmdOffset, uint16_t cx, uint16_t cy, uint16_t width, uint16_t height, uint16_t s_color, uint16_t e_color, uint8_t variant );

/**
 * @brief Draw Rectangle Edges Function.
 * @details This function draws edges of rectangle, without  interior filling.
 * @param[in] ctx : FT800 context object. See #ft800_t structure definition
 * for detailed explanation.
 * @param[in] cfg : FT800 configuration object. See #ft800_cfg_t structure
 * definition for detailed explanation.
 * @param[in] cmdOffset : Display list command offset.
 * @param[in] cx: X coordinate from which to start drawing the edges of rectangle.
 * @param[in] cy: Y coordinate from which to start drawing the edges of rectangle.
 * @param[in] width: Width of edges of rectangle.
 * @param[in] width: Height of edges of rectangle.
 * @param[in] radius: Radius of corners of edges of rectangle.
 * @param[in] color: The color in which the edges will be drawn.
 * @param[in] pen_width: Width of edges.
 * @return Nothing.
 *
 * @b Example
 * @code
 *    // FT800 driver object.
 *    ft800_t ctx;
 *    // FT800 configuration object.
 *    ft800_cfg_t cfg;
 *    // FT800 display list commands offset.
 *    uint16_t cmdOffset;
 *    // Value of color.
 *    uint16_t pen_color=0xFFFF;
 *
 *    // These functions are drawing white edges of rectangle with width of it 5 
 *    // and from position ( 50, 50 ) with width of 100 and height of 100, with radius of corners 10
 *    // and plot them on the FT800 display.
 *    start_display_list( &ctx, &cfg, &cmdOffset );
 *   
 *    draw_edges_rectangle( &ctx, &cfg, &cmdOffset, 50, 50, 100, 100,10, color, 5 );
 * 
 *    end_display_list( &ctx, &cfg, &cmdOffset );
 * @endcode
 */
void draw_edges_rectangle( ft800_t *ctx, ft800_cfg_t *cfg, uint16_t *cmdOffset, uint16_t x, uint16_t y, uint16_t width, uint16_t height,uint16_t radius, uint16_t color, uint8_t pen_width );

/**
 * @brief Draw Rectangle Gradient Function.
 * @details This function draws rectangular area filled in specifics colors with gradient transition.
 * @param[in] ctx : FT800 context object. See #ft800_t structure definition
 * for detailed explanation.
 * @param[in] cfg : FT800 configuration object. See #ft800_cfg_t structure
 * definition for detailed explanation.
 * @param[in] cmdOffset : Display list command offset.
 * @param[in] x1: X coordinate from which to start drawing the filled rectangle.
 * @param[in] y1: Y coordinate from which to start drawing the filled rectangle.
 * @param[in] width: Width of rectangular area.
 * @param[in] height: Height of rectangular area.
 * @param[in] radius: Radius of corners of edges of rectangular area.
 * @param[in] s_color: The starting color with which the rectangle will be filled.
 * @param[in] e_color: The final color with which the rectangle will be filled.
 * @param[in] variant: Type of gradient transition.
 * @return Nothing.
 *
 * @b Example
 * @code
 *    // FT800 driver object.
 *    ft800_t ctx;
 *    // FT800 configuration object.
 *    ft800_cfg_t cfg;
 *    // FT800 display list commands offset.
 *    uint16_t cmdOffset;
 *    // Value of color.
 *    uint16_t pen_color=0xFFFF;
 *
 *    // These functions fill rectangular area with two colors that flow in a 
 *    // gradient and from position ( 50, 50 ) with width of 100 and height of 100, 
 *    // with radius of corners 10 and plot them on the FT800 display.
 *    start_display_list( &ctx, &cfg, &cmdOffset );
 *   
 *    draw_gradient_rectangle( &ctx, &cfg, &cmdOffset, 50, 50, 100, 100, 10, s_color, e_color, FT800_GRADIENT_TOP_BOTTOM );
 * 
 *    end_display_list( &ctx, &cfg, &cmdOffset );
 * @endcode
 */
void draw_gradient_rectangle( ft800_t *ctx, ft800_cfg_t *cfg, uint16_t *cmdOffset,uint16_t x1, uint16_t y1, uint16_t width, uint16_t height, uint16_t radius, uint16_t s_color, uint16_t e_color, uint8_t variant );

/**
 * @brief Draw Aligned Text Function.
 * @details This function draws text with the possibility of alignment.
 * @param[in] ctx : FT800 context object. See #ft800_t structure definition
 * for detailed explanation.
 * @param[in] cfg : FT800 configuration object. See #ft800_cfg_t structure
 * definition for detailed explanation.
 * @param[in] cmdOffset : Display list command offset.
 * @param[in] x: X coordinate from which start drawing the text.
 * @param[in] y: Y coordinate from which start drawing the text.
 * @param[in] width: Width of object which the text is aligned.
 * @param[in] height: Height of object which the text is aligned.
 * @param[in] text_height: Height of text.
 * @param[in] aligment: Type of aligment.
 * @param[in] pen: Width of edges od object which the text is aligned.
 * @param[in] text: Text being drawn.
 * @return Nothing.
 *
 * @b Example
 * @code
 *    // FT800 driver object.
 *    ft800_t ctx;
 *    // FT800 configuration object.
 *    ft800_cfg_t cfg;
 *    // FT800 display list commands offset.
 *    uint16_t cmdOffset;
 *    // Value of color. 
 *    uint16_t pen_color=0xFFFF;
 *
 *    // These functions will draw edges of rectangle and text "FT800" inside of them, 
 *    // aligned to center of rectangle and plot them on the FT800 display.
 *    start_display_list( &ctx, &cfg, &cmdOffset );
 *   
 *    draw_edges_rectangle( &ctx, &cfg, &cmdOffset, 50, 50, 100, 50,10, color, 5 );
 *    draw_aligned_text( &ctx, &cfg, &cmdOffset, 50, 50, 100, 50, 80, FT800_TEXT_ALIGNMENT_CENTER, 5, "FT800" );
 * 
 *    end_display_list( &ctx, &cfg, &cmdOffset );
 * @endcode
 */
void draw_aligned_text( ft800_t *ctx, ft800_cfg_t *cfg, uint16_t *cmdOffset, uint16_t x, uint16_t y, uint16_t width, uint16_t height, uint16_t text_height, ft800_text_alignment alignment, uint8_t pen, char *text );

/**
 * @brief Draw Aligned Text Function.
 * @details This function draws vertical text with the possibility of alignment.
 * @param[in] ctx : FT800 context object. See #ft800_t structure definition
 * for detailed explanation.
 * @param[in] cfg : FT800 configuration object. See #ft800_cfg_t structure
 * definition for detailed explanation.
 * @param[in] cmdOffset : Display list command offset.
 * @param[in] x: X coordinate from which start drawing the text.
 * @param[in] y: Y coordinate from which start drawing the text.
 * @param[in] width: Width of object which the text is aligned.
 * @param[in] height: Height of object which the text is aligned.
 * @param[in] text_height: Height of text.
 * @param[in] aligment: Type of aligment.
 * @param[in] pen: Width of edges od object which the text is aligned.
 * @param[in] text: Text being drawn.
 * @return Nothing.
 *
 * @b Example
 * @code
 *    // FT800 driver object.
 *    ft800_t ctx;
 *    // FT800 configuration object.
 *    ft800_cfg_t cfg;
 *    // FT800 display list commands offset.
 *    uint16_t cmdOffset;
 *    // Value of color.
 *    uint16_t pen_color=0xFFFF;
 *
 *    // These functions will draw edges of rectangle and vertical text "FT800" inside of them, 
 *    // aligned to center of rectangle and plot them on the FT800 display.
 *    start_display_list( &ctx, &cfg, &cmdOffset );
 *   
 *    draw_edges_rectangle( &ctx, &cfg, &cmdOffset, 50, 50, 100, 50,10, color, 5 );
 *    draw_vertical_text( &ctx, &cfg, &cmdOffset, 50, 50, 100, 50, 80, FT800_TEXT_ALIGNMENT_CENTER, 5, "FT800" );
 * 
 *    end_display_list( &ctx, &cfg, &cmdOffset );
 * @endcode
 */
void draw_vertical_text( ft800_t *ctx, ft800_cfg_t *cfg, uint16_t *cmdOffset, uint16_t x , uint16_t y, uint16_t width, uint16_t height, uint16_t text_width, uint16_t pen, ft800_text_alignment alignment, char *text );

#endif // FT800_H
// ------------------------------------------------------------------------- END