/****************************************************************************
**
** Copyright (C) 2020 MikroElektronika d.o.o.
** Contact: https://www.mikroe.com/contact
**
** This file is part of the mikroSDK package
**
** Commercial License Usage
**
** Licensees holding valid commercial NECTO compilers AI licenses may use this
** file in accordance with the commercial license agreement provided with the
** Software or, alternatively, in accordance with the terms contained in
** a written agreement between you and The mikroElektronika Company.
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
 * @file ft5xx6.c
 * @brief FT5xx6 Touch Controller Driver.
 */

#include "ft5xx6.h"
#include "drv_digital_out.h"
#include "drv_digital_in.h"

/**
 * @brief FT5xx6 Events Definition.
 * @details Events code definition depending on the family of touch controller.
 */
const ft5xx6_controller_t FT5X06_CONTROLLER =
{
    {
        { 0x00, TP_EVENT_GEST_NONE },
        { 0x10, TP_EVENT_GEST_LEFT },
        { 0x18, TP_EVENT_GEST_RIGHT },
        { 0x1C, TP_EVENT_GEST_UP },
        { 0x14, TP_EVENT_GEST_DOWN },
        { 0x48, TP_EVENT_GEST_ZOOM_IN },
        { 0x49, TP_EVENT_GEST_ZOOM_OUT }
    }
};

const ft5xx6_controller_t FT5X16_CONTROLLER =
{
    {
        { 0x00, TP_EVENT_GEST_NONE },
        { 0x10, TP_EVENT_GEST_LEFT },
        { 0x18, TP_EVENT_GEST_RIGHT },
        { 0x1C, TP_EVENT_GEST_UP },
        { 0x14, TP_EVENT_GEST_DOWN },
        { 0x48, TP_EVENT_GEST_ZOOM_IN },
        { 0x49, TP_EVENT_GEST_ZOOM_OUT }
    }
};

const ft5xx6_controller_t FT5X26_CONTROLLER =
{
    {
        { 0x00, TP_EVENT_GEST_NONE },
        { 0x1C, TP_EVENT_GEST_LEFT },
        { 0x14, TP_EVENT_GEST_RIGHT },
        { 0x10, TP_EVENT_GEST_UP },
        { 0x18, TP_EVENT_GEST_DOWN },
        { 0x48, TP_EVENT_GEST_ZOOM_IN },
        { 0x49, TP_EVENT_GEST_ZOOM_OUT }
    }
};

const ft5xx6_controller_t FT5X46_CONTROLLER =
{
    {
        { 0x00, TP_EVENT_GEST_NONE },
        { 0x1C, TP_EVENT_GEST_LEFT },
        { 0x14, TP_EVENT_GEST_RIGHT },
        { 0x10, TP_EVENT_GEST_UP },
        { 0x18, TP_EVENT_GEST_DOWN },
        { 0x48, TP_EVENT_GEST_ZOOM_IN },
        { 0x49, TP_EVENT_GEST_ZOOM_OUT }
    }
};

/**
 * @brief FT5xx6 Pressure Coordinates Read Function.
 * @details This function reads the coordinates of pressed touch point/points.
 * @param[out] ctx : FT5xx6 context object. See #ft5xx6_t structure definition
 * for detailed explanation.
 * @return @li @c 0 - OK,
 *         @li @c 5 - Number of pressed touches is out of range.
 * See #tp_err_t structure definition for detailed explanation.
 */
static tp_err_t
ft5xx6_read_press_coordinates( ft5xx6_t * ctx );

/**
 * @brief FT5xx6 Gesture Read Function.
 * @details This function reads the gesture ID and allows user to see the slide
 * direction.
 * @param[out] ctx : FT5xx6 context object. See #ft5xx6_t structure definition
 * for detailed explanation.
 * @return Nothing.
 */
static void
ft5xx6_read_gesture( ft5xx6_t * ctx );

void
ft5xx6_cfg_setup( ft5xx6_cfg_t * cfg, const ft5xx6_controller_t * controller )
{
    i2c_master_configure_default( &cfg->i2c_cfg );

    cfg->int_pin    = HAL_PIN_NC;
    cfg->controller = controller;
}

tp_err_t
ft5xx6_init( ft5xx6_t * ctx, ft5xx6_cfg_t * cfg, tp_drv_t * drv )
{
//     digital_out_t scl_pin;
//     digital_in_t sda_pin;

    // ** Linking problem for functions with different types of arguments.
    tp_event_t ( * tmp_ptr1 )( ft5xx6_t * );
    void ( * tmp_ptr2 )( ft5xx6_t *, tp_touch_item_t * );
    void ( * tmp_ptr3 )( ft5xx6_t *, tp_event_t * );
    tp_err_t ( * tmp_ptr4 )( ft5xx6_t * );

    /*digital_out_init( &scl_pin, cfg->i2c_cfg.scl );
    digital_in_init( &sda_pin, cfg->i2c_cfg.sda );
    digital_out_high( &scl_pin );

    while ( 0 == digital_in_read( &sda_pin ) )
    {
        digital_out_low( &scl_pin );
        Delay_10us( );
        digital_out_high( &scl_pin );
        Delay_10us( );
    }*/

    if ( i2c_master_open( &ctx->i2c, &cfg->i2c_cfg ) == I2C_MASTER_ERROR )
    {
        return TP_ERR_INIT_DRV;
    }

    i2c_master_set_slave_address( &ctx->i2c, FT5XX6_I2C_ADDR );
    i2c_master_set_speed( &ctx->i2c, I2C_MASTER_SPEED_STANDARD );
    i2c_master_set_timeout( &ctx->i2c, 0 );

    if ( digital_in_init( &ctx->int_pin, cfg->int_pin ) == DIGITAL_IN_UNSUPPORTED_PIN )
    {
        return TP_ERR_UNSUPPORTED_PIN;
    }

    ctx->controller = cfg->controller;

    drv->tp_press_detect_f      = ft5xx6_press_detect;
    drv->tp_press_coordinates_f = ft5xx6_press_coordinates;
    drv->tp_gesture_f           = ft5xx6_gesture;
    drv->tp_process_f           = ft5xx6_process;

    return TP_OK;

    // **
    tmp_ptr1( NULL );
    tmp_ptr2( NULL, NULL );
    tmp_ptr3( NULL, NULL );
    tmp_ptr4( NULL );
}

void
ft5xx6_default_cfg( ft5xx6_t * ctx )
{
    ft5xx6_run_mode_setup( ctx, FT5XX6_RUN_MODE_CFG );
    ft5xx6_dev_mode_setup( ctx, FT5XX6_DEV_MODE_NORMAL );
    ft5xx6_generic_write( ctx, FT5XX6_REG_IVT_TO_HOST_STATUS, FT5XX6_INT_MODE_POLLING );
    ft5xx6_run_mode_setup( ctx, FT5XX6_RUN_MODE_WORK );
}

void
ft5xx6_generic_write( ft5xx6_t * ctx, uint8_t reg_addr, uint8_t data_in )
{
    uint8_t tmp_data[ 2 ];

    tmp_data[ 0 ] = reg_addr;
    tmp_data[ 1 ] = data_in;

    i2c_master_write( &ctx->i2c, tmp_data, 2 );
}

uint8_t
ft5xx6_generic_read_single( ft5xx6_t * ctx, uint8_t reg_addr )
{
    uint8_t tmp_data;

    tmp_data = reg_addr;

    i2c_master_write_then_read( &ctx->i2c, &tmp_data, 1, &tmp_data, 1 );

    return tmp_data;
}

tp_err_t
ft5xx6_generic_read_multiple( ft5xx6_t * ctx, uint8_t reg_addr,
                              uint8_t * data_out, uint16_t n_bytes )
{
    uint8_t tmp_data;

    if ( ( n_bytes < FT5XX6_N_DATA_TRANSFER_MIN ) ||
         ( n_bytes > FT5XX6_N_DATA_TRANSFER_MAX ) )
    {
        return TP_ERR_N_DATA;
    }

    tmp_data = reg_addr;

    i2c_master_write_then_read( &ctx->i2c, &tmp_data, 1, data_out, n_bytes );

    return TP_OK;
}

void
ft5xx6_dev_mode_setup( ft5xx6_t * ctx, ft5xx6_dev_mode_t mode )
{
    ft5xx6_generic_write( ctx, FT5XX6_REG_DEVICE_MODE, mode << FT5XX6_OFFSET_DEV_MODE );
}

void
ft5xx6_run_mode_setup( ft5xx6_t * ctx, ft5xx6_run_mode_t mode )
{
    ft5xx6_generic_write( ctx, FT5XX6_REG_RUNNING_STATE, mode );
}

tp_event_t
ft5xx6_press_detect( ft5xx6_t * ctx )
{
    return ctx->press_det;
}

void
ft5xx6_press_coordinates( ft5xx6_t * ctx, tp_touch_item_t * touch_item )
{
    touch_item->n_touches = ctx->touch.n_touches;

    for ( uint8_t idx = 0; idx < ctx->touch.n_touches; idx++ )
    {
        touch_item->point[ idx ].coord_x = ctx->touch.point[ idx ].coord_x;
        touch_item->point[ idx ].coord_y = ctx->touch.point[ idx ].coord_y;

        touch_item->point[ idx ].event = ctx->touch.point[ idx ].event;
        touch_item->point[ idx ].id    = ctx->touch.point[ idx ].id;
    }
}

void
ft5xx6_gesture( ft5xx6_t * ctx, tp_event_t * event )
{
    *event = ctx->gesture;
}

tp_err_t
ft5xx6_process( ft5xx6_t * ctx )
{
    tp_err_t status;

    status = ft5xx6_read_press_coordinates( ctx );

    if ( ( status == TP_OK ) && ( ctx->press_det == TP_EVENT_PRESS_DET ) )
    {
        ft5xx6_read_gesture( ctx );
    }

    return status;
}

static tp_err_t
ft5xx6_read_press_coordinates( ft5xx6_t * ctx )
{
    if ( !digital_in_read( &ctx->int_pin ) )
    {
        ctx->touch.n_touches = ft5xx6_generic_read_single( ctx, FT5XX6_REG_TD_STATUS );

        if ( ctx->touch.n_touches > TP_N_TOUCHES_MAX )
        {
            return TP_ERR_N_TOUCHES;
        }
        else
        {
            uint8_t read_data[ 4 ];
            uint8_t touch_addr = FT5XX6_REG_TOUCH1_XH;

            for ( uint8_t idx = 0; idx < ctx->touch.n_touches; idx++ )
            {
                ft5xx6_generic_read_multiple( ctx, touch_addr, read_data, 4 );

                ctx->touch.point[ idx ].coord_x = read_data[ 0 ];
                ctx->touch.point[ idx ].coord_x <<= 8;
                ctx->touch.point[ idx ].coord_x |= read_data[ 1 ];
                ctx->touch.point[ idx ].coord_x &= FT5XX6_MASK_PRESS_COORD;

                ctx->touch.point[ idx ].coord_y = read_data[ 2 ];
                ctx->touch.point[ idx ].coord_y <<= 8;
                ctx->touch.point[ idx ].coord_y |= read_data[ 3 ];
                ctx->touch.point[ idx ].coord_y &= FT5XX6_MASK_PRESS_COORD;

                ctx->touch.point[ idx ].event = read_data[ 0 ] >> FT5XX6_OFFSET_PRESS_EVENT;
                ctx->touch.point[ idx ].id    = read_data[ 2 ] >> FT5XX6_OFFSET_PRESS_ID;

                touch_addr += FT5XX6_OFFSET_TOUCH_READING;
            }

            ctx->press_det = TP_EVENT_PRESS_DET;
        }
    }
    else
    {
        ctx->press_det = TP_EVENT_PRESS_NOT_DET;
    }

    return TP_OK;
}

static void
ft5xx6_read_gesture( ft5xx6_t * ctx )
{
    uint8_t read_data;

    read_data = ft5xx6_generic_read_single( ctx, FT5XX6_REG_GEST_ID );

    for ( uint8_t idx = 0; idx < FT5XX6_GESTURE_ITEMS_MAX; idx++ )
    {
        if ( read_data == ctx->controller->gest_items[ idx ].key )
        {
            ctx->gesture = ctx->controller->gest_items[ idx ].value;

            return;
        }
    }
}

// ------------------------------------------------------------------------ END
