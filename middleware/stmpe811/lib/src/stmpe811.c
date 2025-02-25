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
 * @file stmpe811.c
 * @brief STMPE811 Resistive Touch Controller Driver.
 */

#include "stmpe811.h"
#include "delays.h"

/* ------------------------------------------------------- PUBLIC CONSTS ---------------------------------------------------*/

const stmpe811_calibration_data_t STMPE811_DEFAULT_CALIBRATION_DATA = {
    80, 3960,
    240, 3960
};

/* ------------------------------------------------------- PRIVATE CONSTS ---------------------------------------------------*/

/**
 * @brief Necessary configuration sequence.
 */
static const uint8_t init_sequence[] = {
    STMPE811_REG_ADDR_SYS_CTRL2,      STMPE811_SYS_CTRL2_GPIO_OFF_BIT | STMPE811_SYS_CTRL2_TS_OFF_BIT, // 0x0c,
    STMPE811_REG_ADDR_INT_EN,         STMPE811_INT_FIFO_TH | STMPE811_INT_TOUCH_DET, // 0x03
    STMPE811_REG_ADDR_ADC_CTRL1,      STMPE811_ADC_CTRL1_SAMPLE_TIME_80 | STMPE811_ADC_CTRL1_REF_SEL_EXTERNAL | STMPE811_ADC_CTRL1_MOD_12B, // 0x49,
    STMPE811_REG_ADDR_ADC_CTRL2,      STMPE811_ADC_CTRL2_ADC_FREQ_3_25_MHz, //0x01
    STMPE811_REG_ADDR_GPIO_AF,        0x00,
    STMPE811_REG_ADDR_TSC_CFG,        STMPE811_TSC_CFG_SETTLING_500us | STMPE811_TSC_CFG_TOUCH_DET_DELAY_500us | STMPE811_TSC_CFG_AVE_CTRL_4_SAMPLES, // 0x9a,
    STMPE811_REG_ADDR_FIFO_TH,        1, // 0x01 single point
    STMPE811_REG_ADDR_FIFO_STA,       STMPE811_FIFO_STA_RESET, // 0x01,
    STMPE811_REG_ADDR_FIFO_STA,       STMPE811_FIFO_STA_START, // 0x00,
    STMPE811_REG_ADDR_TSC_FRACTION_Z, 0x7,
    STMPE811_REG_ADDR_TSC_I_DRIVE,    0x01, // enable i drive
    STMPE811_REG_ADDR_TSC_CTRL,       STMPE811_TSC_CTRL_ENABLE, // enable touch screen - 0x01
    STMPE811_REG_ADDR_INT_STA,        STMPE811_INT_ALL, // clear all interupts - 0xff
    STMPE811_REG_ADDR_INT_CTRL,       STMPE811_INT_CTRL_GLOBAL_INT_BIT, // enable interupts - 0x01,
    0,0 // sequence termiator
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
 * @brief Reads x & y coordinate values to 'touch point 0' ctx member if z is over press threshold
 * @note STMPE811 should be configured for x,y,z operation mode in order to read values.
 * Function doesn't relly on @li @ref stmpe811_read_xyz for the sake of
 * using less pointers and better performance.
 * @param[out] ctx Initialized STMPE811 context structure. See @ref stmpe811_t for more
 * information about the context structure.
 * @retval Returns true if coords have been updated.
 */
static bool _stmpe811_update_ctx_coords( stmpe811_t * ctx );

/**
 * @brief Utility funciton used for calibration.
 * @details Reads raw adc values of x and y without mapping them to screen coords.
 * Doesn't care about z saving a little more time than using public stmpe_read_xyz_raw function
 * Because it's used only for calibration having to dereferencing pointer arguments seem alright
 * since it wont be used very often.
 * @param[in] ctx Initialized STMPE811 context structure. See @ref stmpe811_t for more
 * information about the context structure.
 * @param[out] x Pointer to where X AD conversion result will be placed.
 * @param[out] y Pointer to where Y AD conversion result will be placed.
 * @retval Nothing.
 */
static void _stmpe811_read_xy_raw( stmpe811_t * ctx, uint16_t* x, uint16_t* y );

/**
 * @brief Utility funciton used for calibration.
 * @details Uses _stmpe_read_xy_raw to get raw coordinates and if any of the cooords passes extreme values
 * updates ts_min/max_x/y. If @p callibration_points_uninitialized is true then initializes ts extremes with
 * read values.
 * @param[out] ctx Initialized STMPE811 context structure. See @ref stmpe811_t for more
 * information about the context structure.
 * @param[in] calibration_points_uninitialized Initial point or not.
 * @note @p calibration_points_uninitialized should be @b true only for the first point.
 * @retval Nothing.
 */
static void _stmpe811_calibrate_point( stmpe811_t* ctx, bool calibration_points_uninitialized );

/**
 * @brief Clear fifo coordinate memory
 * @details Writes reset then start to fifo control register
 * @param[in] ctx Initialized STMPE811 context structure. See @ref stmpe811_t for more
 * information about the context structure.
 * @retval Nothing.
 */
static void _stmpe811_clear_fifo( stmpe811_t* ctx );

/* ----------------------------------------- PUBLIC TP INTERFACE FUNCTION IMPLEMENTATION ----------------------------------------------------*/

tp_err_t stmpe811_process( stmpe811_t * ctx ) {
    /**
     * @brief Constant touch data.
     * @details Resistive display has only one touch
     * point, as opposed to capacitive ones.
     */
    ctx->touch.n_touches = 0;
    ctx->touch.point[0].id = TP_TOUCH_ID_0;

    if( DIGITAL_IN_SUCCESS == digital_in_read( &ctx->int_pin ) ) {
        /* Clear all interupts. */
        stmpe811_generic_write_byte( ctx,STMPE811_REG_ADDR_INT_STA, 0xff );
        uint8_t touch_det = ( 0x80 & stmpe811_generic_read_byte( ctx, STMPE811_REG_ADDR_TSC_CTRL ) );
        uint8_t fifo_size = stmpe811_generic_read_byte( ctx, STMPE811_REG_ADDR_FIFO_SIZE );

        ctx->touch.n_touches = 1;
        /* If finger is on the screen. */
        if( touch_det ) {
            /* If touch was previously detected then user is holding the pen down. */
            if( ctx->pen_down ) {
                ctx->press_det = TP_EVENT_PRESS_DET;
                ctx->touch.point[0].event = TP_EVENT_PRESS_MOVE;
                /**
                 * @note Update coords only if stmpe811 has new coords ready, dont update coords that
                 * are already stored inside ctx.
                 * This works well with TP library and uses old coordinates util new ones are ready.
                 */
                if( fifo_size ) {
                    _stmpe811_update_ctx_coords(ctx);
                }
            } else if( fifo_size ) {
                /**
                 * @note If pen is not down and new coords are ready, then its a pen down event.
                 * Check for coords & threshold.
                 */
                if( _stmpe811_update_ctx_coords(ctx) ) {
                    ctx->press_det = TP_EVENT_PRESS_DET;
                    ctx->pen_down = true;
                    ctx->touch.point[0].event = TP_EVENT_PRESS_DOWN;
                }
            }
        } else {
            /* Touch_up. */
            if( ctx->pen_down ) {
                /**
                 * @note In the case of touch up:
                 *   @b pen_down - means physical pen is no longer in touch.
                 *   @b press_det - means event is caught, press_up event.
                 *
                 * This scenario is the reason for separate tp event press detect &
                 * actual press det.
                 */
                ctx->pen_down = false;
                ctx->press_det = TP_EVENT_PRESS_DET;
                ctx->touch.point[0].event = TP_EVENT_PRESS_UP;
                _stmpe811_clear_fifo( ctx );
            } else {
                /* Nothing. */
                _stmpe811_clear_fifo( ctx );
                ctx->press_det = TP_EVENT_PRESS_NOT_DET;
            }
        }
    } else {
        ctx->press_det = (ctx->pen_down) ?  (TP_EVENT_PRESS_DET) : (TP_EVENT_PRESS_NOT_DET);
        ctx->touch.n_touches = 0;
    }

    return TP_OK;
}

/**
 * @note @b STMPE811 hardware does not support gestures.
 */
void stmpe811_gesture( stmpe811_t* ctx, tp_event_t * event ) {
    *event = TP_EVENT_GEST_NONE;
}

tp_event_t stmpe811_press_detect( stmpe811_t* ctx ) {
    return ctx->press_det;
}

void stmpe811_press_coordinates( stmpe811_t* ctx, tp_touch_item_t * touch_item ) {
    touch_item->n_touches = ctx->touch.n_touches;
    touch_item->point[0] = ctx->touch.point[0];
}

// -------------------------------------------------  PUBLIC FUNCTIONS - IMPLEMENTATION  -----------------------------------------------------*/

tp_err_t stmpe811_init ( stmpe811_t* ctx, stmpe811_cfg_t * cfg , tp_drv_t * drv ) {
    // Function with void pointer argument fix.
    //  TODO -- fix this part of the code.
    tp_event_t ( * tmp_ptr1 )( stmpe811_t * );
    void       ( * tmp_ptr2 )( stmpe811_t *, tp_touch_item_t * );
    void       ( * tmp_ptr3 )( stmpe811_t *, tp_event_t * );
    tp_err_t   ( * tmp_ptr4 )( stmpe811_t * );

    if( I2C_MASTER_ERROR == i2c_master_open( &ctx->i2c, &cfg->i2c_cfg ) ) {
        return TP_ERR_INIT_DRV;
    }

    i2c_master_set_slave_address( &ctx->i2c, cfg->addr_sel );
    i2c_master_set_speed( &ctx->i2c, I2C_MASTER_SPEED_STANDARD );
    i2c_master_set_timeout( &ctx->i2c, 0 );

    if( DIGITAL_IN_UNSUPPORTED_PIN == digital_in_init( &ctx->int_pin, cfg->int_pin ) ) {
        return TP_ERR_UNSUPPORTED_PIN;
    }

    drv->tp_process_f           = &stmpe811_process;
    drv->tp_press_detect_f      = &stmpe811_press_detect;
    drv->tp_press_coordinates_f = &stmpe811_press_coordinates;
    drv->tp_gesture_f           = &stmpe811_gesture;

    ctx->width  = cfg->width;
    ctx->height = cfg->height;
    ctx->press_threshold = cfg->press_threshold;
    ctx->press_det = TP_EVENT_PRESS_NOT_DET;
    ctx->pen_down = false;

    stmpe811_set_calibration_data( ctx, &STMPE811_DEFAULT_CALIBRATION_DATA );

    return TP_OK;

    //  TODO -- fix this part of the code.
    tmp_ptr1( NULL );
    tmp_ptr2( NULL, NULL );
    tmp_ptr3( NULL, NULL );
    tmp_ptr4( NULL );
}

void stmpe811_cfg_setup( stmpe811_cfg_t * cfg ) {
    i2c_master_configure_default( &cfg->i2c_cfg );

    cfg->int_pin  = HAL_PIN_NC;
    cfg->addr_sel = STMPE811_I2C_SLAVE_ADDR_1;

    cfg->height = TFT_DISPLAY_HEIGHT;
    cfg->width = TFT_DISPLAY_WIDTH;

    cfg->press_threshold = 0;
}

void stmpe811_default_cfg( stmpe811_t* ctx ) {
    for( uint8_t i  = 0; init_sequence[i] != 0; i += 2 ) {
        stmpe811_generic_write_byte ( ctx, init_sequence[i], init_sequence[i+1] );
        Delay_5ms();
    }
}

void stmpe811_generic_write_byte( stmpe811_t * ctx, uint8_t reg_addr, uint8_t byte ) {
    uint8_t tmp_data[2];
    tmp_data[0] = reg_addr;
    tmp_data[1] = byte;
    i2c_master_write( &ctx->i2c, tmp_data, 2 );
}

uint8_t stmpe811_generic_read_byte( stmpe811_t * ctx, uint8_t reg_addr ) {
    uint8_t read_buf;
    i2c_master_write_then_read( &ctx->i2c, &reg_addr, 1, &read_buf, 1 );
    return read_buf;
}

void stmpe811_generic_write( stmpe811_t * ctx, uint8_t reg, uint8_t * buff, uint8_t len ) {
    /* No need for more than 3 bytes since largest write register is 2 bytes + one for register. */
    uint8_t tmp_data[3];
    /* Start buffer with reg addr. */
    tmp_data[0] = reg;

    /* Copy data to formated buffer with offset. */
    for( uint8_t i = 1; i <= len; i++ ) {
        tmp_data[i] = buff[i-1];
    }

    i2c_master_write( &ctx->i2c, tmp_data, len+1 );
}

void stmpe811_generic_read( stmpe811_t * ctx, uint8_t reg, uint8_t * buff, uint8_t len ) {
    i2c_master_write_then_read( &ctx->i2c, &reg, 1, buff, len );
}

void stmpe811_calibrate( stmpe811_t* ctx ) {
    _stmpe811_calibrate_point( ctx, true );
    _stmpe811_calibrate_point( ctx, false );
    _stmpe811_calibrate_point( ctx, false );
    _stmpe811_calibrate_point( ctx, false );
}

void stmpe811_read_xyz_raw( stmpe811_t * ctx, uint16_t* x, uint16_t* y, uint16_t* z ) {
    uint8_t values[5];
    int16_t val;

    stmpe811_generic_read( ctx, STMPE811_REG_ADDR_TSC_DATA_X, values, 5 );

    /* Pack values. */
    *x = (uint16_t)values[1] + ((uint16_t)values[0] << 8);
    *y = (uint16_t)values[3] + ((uint16_t)values[2] << 8);
    *z = values[4];

    /* Get actual display pixel coordinates. */
    *x = _map( *x, ctx->calibration_data.min_x, ctx->calibration_data.max_x, ctx->width );
    *y = _map( *y, ctx->calibration_data.min_y, ctx->calibration_data.max_y, ctx->height );

    /* Clear fifo. */
    stmpe811_generic_write_byte( ctx, STMPE811_REG_ADDR_FIFO_STA, STMPE811_FIFO_STA_RESET);
    stmpe811_generic_write_byte( ctx, STMPE811_REG_ADDR_FIFO_STA, STMPE811_FIFO_STA_START);
}

void stmpe811_read_xyz( stmpe811_t * ctx, uint16_t* x, uint16_t* y, uint16_t* z ) {
    stmpe811_read_xyz_raw ( ctx, x, y, z );
    /* Get actual display pixel coordinates. */
    *x = _map( *x, ctx->calibration_data.min_x, ctx->calibration_data.max_x, ctx->width );
    *y = _map( *y, ctx->calibration_data.min_y, ctx->calibration_data.max_y, ctx->height );
}

void stmpe811_get_calibration_data( stmpe811_t * ctx, stmpe811_calibration_data_t * cdata ) {
    memcpy( (void*)cdata, (void*)&ctx->calibration_data, sizeof(stmpe811_calibration_data_t) );
}

void stmpe811_set_calibration_data( stmpe811_t * ctx, const stmpe811_calibration_data_t * cdata ) {
    memcpy( (void *)&ctx->calibration_data, (const void*)cdata, sizeof(stmpe811_calibration_data_t) );
}

/* --------------------------------------------- PRIVATE FUNCTIONS - IMPLEMENTATIONS ----------------------------------------*/

static uint32_t _map( uint32_t x, uint32_t in_min, uint32_t in_max, uint32_t out_max ) {
    x -= in_min;
    return (x * out_max) / (in_max - in_min);
}

static bool _stmpe811_update_ctx_coords( stmpe811_t * ctx ) {
    uint8_t values[5];
    int16_t val;

    stmpe811_generic_read( ctx, STMPE811_REG_ADDR_TSC_DATA_X, values, 5 );

    /* Pack values. */
    uint16_t x = (uint16_t)values[1] + ((uint16_t)values[0] << 8);
    uint16_t y = (uint16_t)values[3] + ((uint16_t)values[2] << 8);
    uint8_t z = values[4];

    /* Get actual display pixel coordinates. */
    x = _map( x, ctx->calibration_data.min_x, ctx->calibration_data.max_x, ctx->width );
    y = _map( y, ctx->calibration_data.min_y, ctx->calibration_data.max_y, ctx->height );

    /* Write coords. */
    if( z > ctx->press_threshold ) {
        ctx->touch.point[0].coord_x = x;
        ctx->touch.point[0].coord_y = y;
    }

    /* Clear fifo. */
    stmpe811_generic_write_byte( ctx, STMPE811_REG_ADDR_FIFO_STA, STMPE811_FIFO_STA_RESET );
    stmpe811_generic_write_byte( ctx, STMPE811_REG_ADDR_FIFO_STA, STMPE811_FIFO_STA_START );

    return (z > ctx->press_threshold) ? true : false;
}

static void _stmpe811_read_xy_raw( stmpe811_t * ctx, uint16_t* x, uint16_t* y ) {
    uint8_t values[5];
    int16_t val;

    stmpe811_generic_read( ctx, STMPE811_REG_ADDR_TSC_DATA_X, values, 5 );

    /* Pack coords and write them to output unsigned integers. */
    *x = (uint16_t)values[1] + ((uint16_t)values[0] << 8);
    *y = (uint16_t)values[3] + ((uint16_t)values[2] << 8);
    uint8_t z = values[4];

    /* Clear fifo. */
    stmpe811_generic_write_byte( ctx, STMPE811_REG_ADDR_FIFO_STA, STMPE811_FIFO_STA_RESET );
    stmpe811_generic_write_byte( ctx, STMPE811_REG_ADDR_FIFO_STA, STMPE811_FIFO_STA_START );
}

static void _stmpe811_calibrate_point( stmpe811_t* ctx, bool calibration_points_uninitialized ) {
    uint16_t x, y;
    /* Clear any previous touch data. */
    _stmpe811_clear_fifo( ctx );

    /* Block until touch detected. */
    while( ! ( STMPE811_TSC_CTRL_STA_BIT & stmpe811_generic_read_byte( ctx, STMPE811_REG_ADDR_TSC_CTRL ) ) );

    /**
     * @note Read while touch down.
     * This allows draging to be processed and maybe find better ts min & max values.
     */
    while( ( STMPE811_TSC_CTRL_STA_BIT & stmpe811_generic_read_byte( ctx, STMPE811_REG_ADDR_TSC_CTRL) ) ) {
        /* Wait until coords. */
        if( 0 == stmpe811_generic_read_byte( ctx, STMPE811_REG_ADDR_FIFO_SIZE ) )
            continue;

        _stmpe811_read_xy_raw( ctx, &x, &y );
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
}

static void _stmpe811_clear_fifo( stmpe811_t* ctx ) {
    stmpe811_generic_write_byte( ctx, STMPE811_REG_ADDR_FIFO_STA, STMPE811_FIFO_STA_RESET );
    stmpe811_generic_write_byte( ctx, STMPE811_REG_ADDR_FIFO_STA, STMPE811_FIFO_STA_START );
}

// ------------------------------------------------------------------------ END
