/****************************************************************************
**
** Copyright (C) 2024 MikroElektronika d.o.o.
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
 * @file tp_mikroe.c
 * @brief MIKROE Resistive Touch Controller Driver.
 */

#include "tp_mikroe.h"

static digital_out_t pin_rst;
static digital_out_t pin_cs;
static digital_out_t pin_rs;
static digital_out_t pin_wr;
static digital_out_t pin_rd;

static digital_out_t pin_up;
static digital_out_t pin_right;

#if defined TP_MIKROE_TRANSISTOR_LOGIC
static digital_in_t pin_left;
static digital_in_t pin_down;
#else
static digital_out_t pin_left;
static digital_out_t pin_down;

static digital_in_t in_pin_up;
static digital_in_t in_pin_right;
static digital_in_t in_pin_left;
static digital_in_t in_pin_down;
#endif

extern uint16_t display_width;
extern uint16_t display_height;

const tp_mikroe_calibration_data_t TP_MIKROE_CALIBRATION_DATA_DEFAULT = {
    TP_MIKROE_CALIBRATION_XMIN, TP_MIKROE_CALIBRATION_XMAX,
    TP_MIKROE_CALIBRATION_YMIN, TP_MIKROE_CALIBRATION_YMAX
};

/**
 * @brief Function for calculating coordinates.
 * @details This function calculates the coordinates of pressed touch point/points.
 * @param[in] ctx Initialized TP_MIKROE context structure. See @ref tp_mikroe_t for more
 * information about the context structure.
 * @param[in] *x_coord_int - x value.
 * @param[in] *y_coord_int - y value.
 * @retval Nothing.
 */
static void tp_mikroe_calc_coord( tp_mikroe_t *ctx, int *x_coord_int, int *y_coord_int );

/**
 * @brief Configures pins.
 * @details Sets adequate pins as input or output.
 * @param[in] None.
 * @retval Nothing.
 */
static void tp_mikroe_driver_x_on();

/**
 * @brief Configures pins.
 * @details Sets adequate pins as input or output.
 * @param[in] None.
 * @retval Nothing.
 */
static void tp_mikroe_driver_y_on();

/**
 * @brief Configures pins.
 * @details Sets adequate pins as input or output.
 * @param[in] None.
 * @retval Nothing.
 */
static void tp_mikroe_driver_z_on();

/**
 * @brief TP_MIKROE ADC pin configuration function.
 * @details Sets ADC pins to appropriate values.
 * @param[in] None.
 * @retval Nothing.
 */
static void tp_mikroe_adc_init_pins();

void tp_mikroe_default_cfg_adc ( tp_mikroe_t *ctx ) {
    tp_mikroe_adc_init_pins();
}

tp_err_t tp_mikroe_init_tp ( tp_mikroe_t *ctx, tp_mikroe_cfg_t *cfg, tp_drv_t *drv ) {
    analog_in_open( &ctx->analog_in_x, &cfg->analog_in_cfg_read_x );
    analog_in_open( &ctx->analog_in_y, &cfg->analog_in_cfg_read_y );

    tp_mikroe_set_calibration_data( ctx, &TP_MIKROE_CALIBRATION_DATA_DEFAULT );

    ctx->pressure_threshold_level.tp_mikroe_pressure_threshold_lower =
        cfg->pressure_threshold_level.tp_mikroe_pressure_threshold_lower;
    ctx->pressure_threshold_level.tp_mikroe_pressure_threshold_upper =
        cfg->pressure_threshold_level.tp_mikroe_pressure_threshold_upper;

    tp_event_t ( * tmp_ptr1 )( tp_mikroe_t * );
    void ( * tmp_ptr2 )( tp_mikroe_t *, tp_touch_coord_t * );
    void ( * tmp_ptr3 )( tp_mikroe_t *, tp_event_t * );
    tp_err_t ( * tmp_ptr4 )( tp_mikroe_t * );

    drv->tp_process_f = &tp_mikroe_process;
    drv->tp_press_detect_f = &tp_mikroe_press_detect;
    drv->tp_press_coordinates_f = &tp_mikroe_press_coordinates;

    ctx->width = cfg->width;
    ctx->height = cfg->height;

    ctx->press_det = TP_EVENT_PRESS_NOT_DET;

    ctx->pen_down = false;

    return TP_OK;

    tmp_ptr1( NULL );
    tmp_ptr2( NULL, NULL );
    tmp_ptr3( NULL, NULL );
    tmp_ptr4( NULL );
}

tp_err_t tp_mikroe_process ( tp_mikroe_t *ctx ) {
    uint16_t x_pos = 0, y_pos = 0;

    ctx->touch.id = TP_TOUCH_ID_0;
    ctx->touch.event = TP_EVENT_PRESS_NOT_DET;
    ctx->press_det = TP_EVENT_PRESS_NOT_DET;

    if ( tp_mikroe_pressure_level_detect( ctx ) ) {
        if ( !ctx->pen_down ) {
            if ( tp_mikroe_check_pressure( ctx, &x_pos, &y_pos ) ) {
                tp_mikroe_update_ctx_coords( ctx, x_pos, y_pos );
                ctx->press_det = TP_EVENT_PRESS_DET;
                ctx->touch.event = TP_EVENT_PRESS_DOWN;
                ctx->pen_down = true;
            } else {
                ctx->press_det = TP_EVENT_PRESS_DET;
                ctx->touch.event = TP_EVENT_PRESS_UP;
                ctx->pen_down = false;
            }
        }
    } else {
        ctx->pen_down = false;
        ctx->touch.event = TP_EVENT_PRESS_NOT_DET;
        ctx->press_det = TP_EVENT_PRESS_NOT_DET;
    }
    return TP_OK;
}

void tp_mikroe_gesture ( tp_mikroe_t *ctx, tp_event_t *event ) {
    /**
     * @brief MikroE Touch panel implementation
     * does not support gestures.
     */
    *event = 0;
}

tp_event_t tp_mikroe_press_detect ( tp_mikroe_t *ctx ) {
    return ctx->press_det;
}

void tp_mikroe_press_coordinates ( tp_mikroe_t *ctx, tp_touch_coord_t *touch_item ) {
    *touch_item = ctx->touch;
    touch_item->event = ctx->touch.event;
}

void tp_mikroe_calibrate ( tp_t *tp_instance ) {
    SET_PEN();

    DRAW_ARROW_TOP_LEFT();
    tp_mikroe_calibrate_point( tp_instance->tp_drv_ctx, true );

    DRAW_ARROW_BOTTOM_RIGHT();
    tp_mikroe_calibrate_point( tp_instance->tp_drv_ctx, false );

    DRAW_ARROW_TOP_RIGHT();
    tp_mikroe_calibrate_point( tp_instance->tp_drv_ctx, false );

    DRAW_ARROW_BOTTOM_LEFT();
    tp_mikroe_calibrate_point( tp_instance->tp_drv_ctx, false );

    gl_clear( GL_BLACK );
}

void tp_mikroe_get_calibration_data ( tp_mikroe_t *ctx, tp_mikroe_calibration_data_t *cdata ) {
    memcpy( ( void * )cdata, ( void * )&ctx->calibration_data, sizeof( tp_mikroe_calibration_data_t ) );
}

void tp_mikroe_set_calibration_data ( tp_mikroe_t *ctx, const tp_mikroe_calibration_data_t *cdata ) {
    memcpy( ( void * )&ctx->calibration_data, ( const void * )cdata, sizeof( tp_mikroe_calibration_data_t ) );
}

void tp_mikroe_set_pressure_threshold_level ( tp_mikroe_cfg_t *cfg, tp_mikroe_pressure_threshold_t pressure ) {
    cfg->pressure_threshold_level.tp_mikroe_pressure_threshold_lower = pressure.tp_mikroe_pressure_threshold_lower;
}

bool tp_mikroe_check_pressure ( tp_mikroe_t *ctx, uint16_t *x_pos, uint16_t *y_pos ) {
    unsigned int result = 0;

    tp_mikroe_driver_x_on();

    Delay_1ms();

    analog_in_read ( &ctx->analog_in_y, &result );
    if ( ctx->pressure_threshold_level.tp_mikroe_pressure_threshold_lower > result ) {
        return false;
    }

    *y_pos = result;

    tp_mikroe_driver_y_on();

    Delay_1ms();

    analog_in_read ( &ctx->analog_in_x, &result );
    if ( ctx->pressure_threshold_level.tp_mikroe_pressure_threshold_lower > result ) {
        return false;
    }

    *x_pos = result;

    tp_mikroe_driver_z_on();

    return true;
}

void tp_mikroe_update_ctx_coords ( tp_mikroe_t *ctx, uint16_t x_pos, uint16_t y_pos ) {
    int x_coord_int = 0, y_coord_int = 0;

    x_coord_int = x_pos - ctx->calibration_data.min_x;
    y_coord_int = y_pos - ctx->calibration_data.min_y;

    tp_mikroe_calc_coord( ctx, &x_coord_int, &y_coord_int );

    ctx->touch.coord_x = x_coord_int;
    ctx->touch.coord_y = y_coord_int;
}

void tp_mikroe_calibrate_point ( tp_mikroe_t *ctx, bool calibration_points_uninitialized ) {
    uint16_t x = 0, y = 0;

    while( !tp_mikroe_pressure_level_detect ( ctx ) );

    while( !tp_mikroe_check_pressure ( ctx, &x, &y ) );

    if ( calibration_points_uninitialized ) {
        ctx->calibration_data.min_x = x;
        ctx->calibration_data.max_x = x;
        ctx->calibration_data.min_y = y;
        ctx->calibration_data.max_y = y;
    } else {
        if ( x < ctx->calibration_data.min_x )
            ctx->calibration_data.min_x = x;
        if ( x > ctx->calibration_data.max_x )
            ctx->calibration_data.max_x = x;
        if ( y < ctx->calibration_data.min_y )
            ctx->calibration_data.min_y = y;
        if ( y > ctx->calibration_data.max_y )
            ctx->calibration_data.max_y = y;
    }
}

void tp_mikroe_set_threshold ( tp_mikroe_t *ctx, uint16_t threshold_upper, uint16_t threshold_lower ) {
    ctx->pressure_threshold_level.tp_mikroe_pressure_threshold_upper = threshold_upper;
    ctx->pressure_threshold_level.tp_mikroe_pressure_threshold_lower = threshold_lower;
}

void tp_mikroe_cfg_setup ( tp_mikroe_cfg_t *cfg ) {
    cfg->width = display_width;
    cfg->height = display_height;

    TP_MIKROE_ADC_CONFIG( cfg );

    cfg->pressure_threshold_level.tp_mikroe_pressure_threshold_lower = TP_MIKROE_PRESSURE_THRESHOLD_LOWER;
    cfg->pressure_threshold_level.tp_mikroe_pressure_threshold_upper = TP_MIKROE_PRESSURE_THRESHOLD_UPPER;
}

char tp_mikroe_pressure_level_detect ( tp_mikroe_t *ctx ) {
    int adc_rd = 0;
    char result = 0;

    tp_mikroe_driver_z_on();

    Delay_10ms();

    analog_in_read ( &ctx->analog_in_y, &adc_rd );

    #if defined TP_MIKROE_TRANSISTOR_LOGIC
    result = ( ctx->pressure_threshold_level.tp_mikroe_pressure_threshold_upper < adc_rd );
    #else
    result = ( ctx->pressure_threshold_level.tp_mikroe_pressure_threshold_upper > adc_rd );
    #endif

    return result;
}

static void tp_mikroe_calc_coord ( tp_mikroe_t *ctx, int *x_coord_int, int *y_coord_int ) {
    int tmp = 0;
    int x_coord_int_local = *x_coord_int;
    int y_coord_int_local = *y_coord_int;

    if ( TP_MIKROE_ROTATE_CASE_0 == ctx->rotate ) {
        tmp = y_coord_int_local;
        y_coord_int_local = ( ( ( long )x_coord_int_local * ctx->height ) / ( ctx->calibration_data.max_x - ctx->calibration_data.min_x ) );
        x_coord_int_local = ( ( ( long )tmp * ctx->width ) / ( ctx->calibration_data.max_y - ctx->calibration_data.min_y ) );
        y_coord_int_local = ctx->height - y_coord_int_local;
        x_coord_int_local = ctx->width - x_coord_int_local;
    } else if ( TP_MIKROE_ROTATE_CASE_1 == ctx->rotate ) {
        x_coord_int_local = ( ( ( long )x_coord_int_local * ctx->width ) / ( ctx->calibration_data.max_x - ctx->calibration_data.min_x ) );
        y_coord_int_local = ctx->height - ( ( ( long )y_coord_int_local * ctx->height ) / ( ctx->calibration_data.max_y - ctx->calibration_data.min_y ) );
    } else if ( TP_MIKROE_ROTATE_CASE_2 == ctx->rotate ) {
        tmp = y_coord_int_local;
        y_coord_int_local = ( ( ( long )x_coord_int_local * ctx->height ) / ( ctx->calibration_data.max_x - ctx->calibration_data.min_x ) );
        x_coord_int_local = ( ( ( long )tmp * ctx->width ) / ( ctx->calibration_data.max_y - ctx->calibration_data.min_y ) );
    } else if ( TP_MIKROE_ROTATE_CASE_3 == ctx->rotate ) {
        x_coord_int_local = ctx->width - ( ( ( long )x_coord_int_local * ctx->width ) / ( ctx->calibration_data.max_x - ctx->calibration_data.min_x ) );
        y_coord_int_local = ( ( ( long )y_coord_int_local * ctx->height ) / ( ctx->calibration_data.max_y - ctx->calibration_data.min_y ) );
    }

    *x_coord_int = x_coord_int_local;
    *y_coord_int = y_coord_int_local;
}

#ifdef TP_MIKROE_TRANSISTOR_LOGIC
static void tp_mikroe_driver_x_on() {
    digital_out_low( &pin_right );
    digital_out_high( &pin_up );
}

static void tp_mikroe_driver_y_on() {
    digital_out_high( &pin_right );
    digital_out_low( &pin_up );
}

static void tp_mikroe_driver_z_on() {
    digital_out_low( &pin_up );
    digital_out_low( &pin_right );
}

static void tp_mikroe_adc_init_pins() {
    digital_out_init( &pin_up, TP_MIKROE_YU );
    digital_out_init( &pin_right, TP_MIKROE_XR );
    digital_in_init( &pin_left, TP_MIKROE_YD );
    digital_in_init( &pin_down, TP_MIKROE_XL );
}
#else
static void tp_mikroe_driver_x_on() {
    digital_in_init( &in_pin_up, TP_MIKROE_YU );
    digital_in_init( &in_pin_down, TP_MIKROE_YD );
    digital_out_init( &pin_left, TP_MIKROE_XL );
    digital_out_init( &pin_right, TP_MIKROE_XR );
    digital_out_low( &pin_right );
    digital_out_high( &pin_left );
}

static void tp_mikroe_driver_y_on() {
    digital_in_init( &in_pin_left, TP_MIKROE_XL );
    digital_in_init( &in_pin_right, TP_MIKROE_XR );
    digital_out_init( &pin_up, TP_MIKROE_YU );
    digital_out_init( &pin_down, TP_MIKROE_YD );
    digital_out_low( &pin_down );
    digital_out_high( &pin_up );
}

static void tp_mikroe_driver_z_on() {
    digital_in_init( &in_pin_up, TP_MIKROE_YU );
    digital_out_init( &pin_right, TP_MIKROE_XR );
    digital_in_init( &in_pin_left, TP_MIKROE_XL );
    digital_in_init( &in_pin_down, TP_MIKROE_YD );
    digital_out_low( &pin_right );
}

static void tp_mikroe_adc_init_pins() {
    tp_mikroe_driver_z_on();
}
#endif

// ------------------------------------------------------------------------ END
