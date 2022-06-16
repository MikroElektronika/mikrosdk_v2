/****************************************************************************
**
** Copyright (C) 2022 MikroElektronika d.o.o.
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
 * @file tsc2003.c
 * @brief TSC2003 Resistive Touch Controller Driver.
 */

#include "tsc2003.h"

#define TSC_PRESSURE_THRESHOLD_LOWER (1000)
#define TSC_PRESSURE_THRESHOLD_UPPER (6000)

/**
 * @brief: Macro used for adequate resolution setting.
 */
#define _resolution(_res) (tsc2003_bits_m_8bit == _res)?(1):(2)

/* ------------------------------------------------------- PUBLIC CONSTS ---------------------------------------------------*/

const tsc2003_calibration_data_t TSC2003_CALIBRATION_DATA_DEFAULT = {
    80, 3960, // Xmin, Xmax
    240, 3960 // Ymin, Ymax
};

/* --------------------------------------------- PRIVATE FUNCTIONS - DECLARATIONS -------------------------------------------*/

/**
 * @brief Maps value of @p x in [in_min, in_max] range to [0, out_max] range.
 * @param[in] x Raw conversion result from TSC2003 IC.
 * @param[in] in_min Calibrated minimum value.
 * @param[in] in_max Calibrated maximum value.
 * @param[in] out_max Screen actual resolution value. ( Example 240,320... )
 * @retval Returns actual coordinate value for read AD conversion from IC.
 */
static uint32_t _map( uint32_t x, uint32_t in_min, uint32_t in_max, uint32_t out_max );

/**
 * @brief Reads @p x_pos & @p y_pos coordinate values to 'touch point 0' ctx member if @b z is
 * between lower and upper press threshold levels.
 * @note TSC2003 should be configured first in order to read values.
 * Function doesn't relly on tsc2003_check_pressure for the sake of
 * using less pointers and better performance.
 * @param[out] ctx Initialized TSC2003 context structure. See @ref tsc2003_t for more
 * information about the context structure.
 * @param[in] x_pos X coordinate.
 * @param[in] y_pos Y coordinate.
 * @retval Nothing.
 */
static void tsc2003_update_ctx_coords( tsc2003_t * ctx, uint16_t x_pos, uint16_t y_pos );

/**
 * @brief Utility funciton used for calibration.
 * @details Uses tsc2003_check_pressure to get raw coordinates and if any of the cooords passes extreme values
 * updates ts_min/max_x/y. If @p callibration_points_uninitialized is true then initializes ts extremes with
 * read values.
 * @param[out] ctx Initialized TSC2003 context structure. See @ref tsc2003_t for more
 * information about the context structure.
 * @param[in] calibration_points_uninitialized Initial point or not.
 * @note @p calibration_points_uninitialized should be @b true only for the first point.
 * @retval Nothing.
 */
static void tsc2003_calibrate_point( tsc2003_t* ctx, bool calibration_points_uninitialized );

/**
 * @brief Default function for reading actual data.
 * @details Function reads X, Y, Z1, Z2 data and checks if
 * adequate pressure has been applied to the screen.
 * @param[out] ctx Initialized TSC2003 context structure. See @ref tsc2003_t for more
 * information about the context structure.
 * @param[out] x_pos Pointer to where X AD conversion result will be placed.
 * @param[out] y_pos Pointer to where Y AD conversion result will be placed.
 * @retval @b True(1) or @b False(0) based on pressure level.
 */
static bool tsc2003_check_pressure( tsc2003_t *ctx, uint16_t *x_pos, uint16_t *y_pos );

/* ----------------------------------------- PUBLIC TP INTERFACE FUNCTION IMPLEMENTATION ----------------------------------------------------*/

tp_err_t tsc2003_process( tsc2003_t * ctx ) {
    uint16_t x_pos = 0, y_pos = 0;
    /**
     * @brief Constant touch data.
     * @details Resistive display has only one touch
     * point, as opposed to capacitive ones.
     */
    ctx->touch.n_touches = 1;
    ctx->touch.point[0].id = TP_TOUCH_ID_0;

    if( DIGITAL_IN_SUCCESS == digital_in_read( &ctx->int_pin ) ) {
        /* If finger is on the screen. */
        if( tsc2003_check_pressure( ctx, &x_pos, &y_pos ) ) {
            /* If touch was previously detected then user is holding the pen down. */
            tsc2003_update_ctx_coords(ctx, x_pos, y_pos);
            ctx->press_det = TP_EVENT_PRESS_DET;
            ctx->pen_down = true;
            ctx->touch.point[0].event = TP_EVENT_PRESS_DOWN;
        } else {
            /* Touch_up. */
            if( ctx->pen_down ) {
                /**
                 * @note In the case of touch up:
                 * @b pen_down - means physical pen is no longer in touch position.
                 * @b press_det - means event is caught / @b press_up event.
                 * This scenario is the reason for separate tp event press detect &
                 * actual press detect.
                 */
                ctx->pen_down = false;
                ctx->press_det = TP_EVENT_PRESS_DET;
                ctx->touch.point[0].event = TP_EVENT_PRESS_UP;
            } else {
                /* Nothing. */
                ctx->press_det = TP_EVENT_PRESS_NOT_DET;
            }
        }
    } else {
        ctx->press_det = (ctx->pen_down) ? (TP_EVENT_PRESS_DET) : (TP_EVENT_PRESS_NOT_DET);
    }

    return TP_OK;
}

/**
 * @note @b TSC2003 hardware does not support gestures.
 */
void tsc2003_gesture( tsc2003_t* ctx, tp_event_t * event ) {
    *event = TP_EVENT_GEST_NONE;
}

tp_event_t tsc2003_press_detect( tsc2003_t* ctx ) {
    return ctx->press_det;
}

void tsc2003_press_coordinates( tsc2003_t* ctx, tp_touch_item_t * touch_item ) {
    touch_item->n_touches = 1;
    touch_item->point[0] = ctx->touch.point[0];
}

// -------------------------------------------------  PUBLIC FUNCTIONS - IMPLEMENTATION  -----------------------------------------------------*/

tp_err_t tsc2003_init( tsc2003_t* ctx, tsc2003_cfg_t * cfg , tp_drv_t * drv ) {
    /* Function with void pointer argument fix. */
    //  TODO -- fix this part of the code.
    tp_event_t ( * tmp_ptr1 )( tsc2003_t * );
    void       ( * tmp_ptr2 )( tsc2003_t *, tp_touch_item_t * );
    void       ( * tmp_ptr3 )( tsc2003_t *, tp_event_t * );
    tp_err_t   ( * tmp_ptr4 )( tsc2003_t * );

    if( I2C_MASTER_ERROR == i2c_master_open( &ctx->i2c, &cfg->i2c_cfg ) ) {
        return TP_ERR_INIT_DRV;
    }

    i2c_master_set_slave_address( &ctx->i2c, cfg->addr_sel );
    i2c_master_set_speed( &ctx->i2c, I2C_MASTER_SPEED_STANDARD );
    i2c_master_set_timeout( &ctx->i2c, 0 );

    if( DIGITAL_IN_UNSUPPORTED_PIN == digital_in_init( &ctx->int_pin, cfg->int_pin ) ) {
        return TP_ERR_UNSUPPORTED_PIN;
    }

    drv->tp_process_f           = &tsc2003_process;
    drv->tp_press_detect_f      = &tsc2003_press_detect;
    drv->tp_press_coordinates_f = &tsc2003_press_coordinates;
    drv->tp_gesture_f           = &tsc2003_gesture;

    ctx->width  = cfg->width;
    ctx->height = cfg->height;

    ctx->pressure_threshold_level.tsc2003_pressure_threshold_lower =
        cfg->pressure_threshold_level.tsc2003_pressure_threshold_lower;
    ctx->pressure_threshold_level.tsc2003_pressure_threshold_upper =
        cfg->pressure_threshold_level.tsc2003_pressure_threshold_upper;
    ctx->press_det = TP_EVENT_PRESS_NOT_DET;

    ctx->pen_down = false;

    tsc2003_set_calibration_data( ctx, &TSC2003_CALIBRATION_DATA_DEFAULT );

    return TP_OK;

    //  TODO -- fix this part of the code.
    tmp_ptr1( NULL );
    tmp_ptr2( NULL, NULL );
    tmp_ptr3( NULL, NULL );
    tmp_ptr4( NULL );
}

void tsc2003_cfg_setup( tsc2003_cfg_t * cfg ) {
    i2c_master_configure_default( &cfg->i2c_cfg );

    cfg->int_pin  = HAL_PIN_NC;
    cfg->addr_sel = TSC2003_I2C_SLAVE_ADDR_DEFAULT;
    cfg->resolution = tsc2003_bits_m_12bit;
    cfg->power_down = tsc2003_bits_pd_power_down_between_conversion;

    cfg->height = TFT_DISPLAY_HEIGHT;
    cfg->width = TFT_DISPLAY_WIDTH;

    cfg->pressure_threshold_level.tsc2003_pressure_threshold_lower = TSC_PRESSURE_THRESHOLD_LOWER;
    cfg->pressure_threshold_level.tsc2003_pressure_threshold_upper = TSC_PRESSURE_THRESHOLD_UPPER;
}

void tsc2003_default_cfg( tsc2003_t* ctx ) {
    tsc2003_write_cmd( ctx, 0 );
}

void tsc2003_write_cmd( tsc2003_t * ctx, uint8_t reg_addr ) {
    uint8_t cmdByte = configureData(reg_addr,ctx->power_down,ctx->resolution);

    i2c_master_write( &ctx->i2c, &cmdByte, 1 );
}

void tsc2003_calibrate( tsc2003_t* ctx ) {
    tsc2003_calibrate_point( ctx, true );
    tsc2003_calibrate_point( ctx, false );
    tsc2003_calibrate_point( ctx, false );
    tsc2003_calibrate_point( ctx, false );
}

void tsc2003_generic_read( tsc2003_t * ctx, uint8_t reg_addr, uint8_t *data_buff, uint8_t len ) {
    data_buff[0] = 0;
    data_buff[1] = 0;

    i2c_master_write_then_read( &ctx->i2c, &reg_addr, 1, data_buff, len );
}

void tsc2003_get_calibration_data( tsc2003_t * ctx, tsc2003_calibration_data_t * cdata ) {
    memcpy( (void*)cdata, (void*)&ctx->calibration_data, sizeof(tsc2003_calibration_data_t) );
}

void tsc2003_set_calibration_data( tsc2003_t * ctx, const tsc2003_calibration_data_t * cdata ) {
    memcpy( (void *)&ctx->calibration_data, (const void*)cdata, sizeof(tsc2003_calibration_data_t) );
}

void tsc2003_set_pressure_threshold_level( tsc2003_cfg_t * cfg, tsc2003_pressure_threshold_t pressure ) {
    cfg->pressure_threshold_level.tsc2003_pressure_threshold_lower = pressure.tsc2003_pressure_threshold_lower;
    cfg->pressure_threshold_level.tsc2003_pressure_threshold_upper = pressure.tsc2003_pressure_threshold_upper;
}

/* --------------------------------------------- PRIVATE FUNCTIONS - IMPLEMENTATIONS ----------------------------------------*/

static bool tsc2003_check_pressure( tsc2003_t *ctx, uint16_t *x_pos, uint16_t *y_pos ) {
    uint16_t z1_data, z2_data = 0;
    uint8_t data_buff[2] = { 0, 0 };
    uint32_t pressure_check;

    tsc2003_generic_read( ctx, configureData(tsc2003_bits_cfg_measure_position_x,
                                             ctx->power_down, ctx->resolution),
                                             data_buff,
                                             _resolution(ctx->resolution));
    *x_pos = ((uint16_t)data_buff[0] << 4) + ((uint16_t)data_buff[1] >> 4);

    tsc2003_generic_read( ctx, configureData(tsc2003_bits_cfg_measure_position_y,
                                             ctx->power_down, ctx->resolution),
                                             data_buff,
                                             _resolution(ctx->resolution));
    *y_pos = ((uint16_t)data_buff[0] << 4) + ((uint16_t)data_buff[1] >> 4);

    tsc2003_generic_read( ctx, configureData(tsc2003_bits_cfg_measure_position_z1,
                                             ctx->power_down, ctx->resolution),
                                             data_buff,
                                             _resolution(ctx->resolution));
    z1_data = ((uint16_t)data_buff[0] << 4) + ((uint16_t)data_buff[1] >> 4);

    tsc2003_generic_read( ctx, configureData(tsc2003_bits_cfg_measure_position_z2,
                                             ctx->power_down, ctx->resolution),
                                             data_buff,
                                             _resolution(ctx->resolution));

    z2_data = ((uint16_t)data_buff[0] << 4) + ((uint16_t)data_buff[1] >> 4);
    pressure_check = (((uint32_t)z2_data * (*x_pos)) / z1_data) - (*x_pos);

    if( (pressure_check > ctx->pressure_threshold_level.tsc2003_pressure_threshold_upper) ||
         (pressure_check < ctx->pressure_threshold_level.tsc2003_pressure_threshold_lower) )
    {
        return false;
    } else {
        return true;
    }
}

static uint32_t _map( uint32_t x, uint32_t in_min, uint32_t in_max, uint32_t out_max ) {
    x -= in_min;
    return (x * out_max) / (in_max - in_min);
}

static void tsc2003_update_ctx_coords( tsc2003_t * ctx, uint16_t x_pos, uint16_t y_pos ) {
    /* Get actual display pixel coordinates. */
    ctx->touch.point[0].coord_x =  _map( x_pos, ctx->calibration_data.min_x, ctx->calibration_data.max_x, ctx->width );
    ctx->touch.point[0].coord_y =  _map( y_pos, ctx->calibration_data.min_y, ctx->calibration_data.max_y, ctx->height );
}

static void tsc2003_calibrate_point( tsc2003_t* ctx, bool calibration_points_uninitialized ) {
    uint16_t x, y;

    /* Block until touch detected (INT pin low). */
    while( !tsc2003_press_detect(ctx) );

    /* Keep reading data untill pressure is adequate. */
    while( !tsc2003_check_pressure( ctx, &x, &y ) );

    /* Map values after reading points. */
    if( calibration_points_uninitialized ) {
        ctx->calibration_data.min_x = x;
        ctx->calibration_data.max_x = x;
        ctx->calibration_data.min_y = y;
        ctx->calibration_data.max_y = y;
    } else {
        if( x < ctx->calibration_data.min_x )
            ctx->calibration_data.min_x = x;
        if( x > ctx->calibration_data.max_x )
            ctx->calibration_data.max_x = x;
        if( y < ctx->calibration_data.min_y )
            ctx->calibration_data.min_y = y;
        if( y > ctx->calibration_data.max_y )
            ctx->calibration_data.max_y = y;
    }
}

// ------------------------------------------------------------------------ END
