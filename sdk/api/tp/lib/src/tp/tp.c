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
 * @file tp.c
 * @brief Touch Panel API Library.
 */

#include "tp.h"
#include <stddef.h>

/**
 * @brief Touch Panel Private Macros.
 * @details Specified macros for internal usage.
 */
#define TP_GESTURE_ITEMS        4
#define TP_PRESS_COORD_DEFAULT  0xFFFF
#define TP_RELEASE_NOT_DET      0
#define TP_RELEASE_DET          1

/**
 * @brief Touch Panel Gesture Item Definition.
 * @details Touch Panel gesture item definition depending on the panel
 * orientation.
 */
typedef struct
{
    tp_event_t  gest_rot0;      /**< Gesture event rotated by 0 degrees. */
    tp_event_t  gest_rot90;     /**< Gesture event rotated by 90 degrees. */
    tp_event_t  gest_rot180;    /**< Gesture event rotated by 180 degrees. */
    tp_event_t  gest_rot270;    /**< Gesture event rotated by 270 degrees. */

} tp_gest_item_t;

/**
 * @brief Touch Panel Gesture Items.
 * @details Touch Panel gesture items with determined maximal number of items.
 */
typedef struct
{
    tp_gest_item_t  gest_items[ TP_GESTURE_ITEMS ];

} tp_gest_id_t;

/**
 * @brief Touch Panel Gesture ID Definition.
 * @details Touch Panel gesture ID (event) definition depending on the panel
 * orientation.
 */
static const tp_gest_id_t TP_GESTURE_ID =
{
    {
        { TP_EVENT_GEST_LEFT,  TP_EVENT_GEST_DOWN,  TP_EVENT_GEST_RIGHT, TP_EVENT_GEST_UP },
        { TP_EVENT_GEST_RIGHT, TP_EVENT_GEST_UP,    TP_EVENT_GEST_LEFT,  TP_EVENT_GEST_DOWN },
        { TP_EVENT_GEST_UP,    TP_EVENT_GEST_LEFT,  TP_EVENT_GEST_DOWN,  TP_EVENT_GEST_RIGHT },
        { TP_EVENT_GEST_DOWN,  TP_EVENT_GEST_RIGHT, TP_EVENT_GEST_UP,    TP_EVENT_GEST_LEFT }
    }
};

/**
 * @brief TP Get Rotated Coordinates Function.
 * @details This function allows user to get a rotated coordinates of the
 * determined touch point from the touch item data.
 * @param[in] ctx : TP context object. See #tp_t structure definition for
 * detailed explanation.
 * @param[out] to : Touch item data where rotated coordinates be stored.
 * See #tp_touch_item_t structure definition for detailed explanation.
 * @param[in] from : Touch item data from which non-rotated coordinates be
 * calculated. See #tp_touch_item_t structure definition for detailed
 * explanation.
 * @param[in] index : Index of the determined touch point.
 * @return Nothing.
 * @note This function depends of the selected display (touch panel) placement
 * rotation.
 */
static void
tp_get_rotated_coord( tp_t * ctx, tp_touch_item_t * to, tp_touch_item_t * from,
                      uint8_t index );

void
tp_cfg_setup( tp_cfg_t * cfg )
{
    cfg->width     = TFT_DISPLAY_WIDTH;
    cfg->height    = TFT_DISPLAY_HEIGHT;
    cfg->start_pos = TP_ROTATE_0;
}

tp_err_t
tp_init( tp_t * ctx, tp_cfg_t * cfg, tp_drv_t * drv, void * drv_ctx )
{
    uint8_t idx;

    ctx->tp_drv     = drv;
    ctx->tp_drv_ctx = drv_ctx;

    ctx->press_callback_f     = NULL;
    ctx->gesture_callback_f   = NULL;
    ctx->start_pos            = cfg->start_pos;
    ctx->curr_pos             = cfg->start_pos;
    ctx->rotate               = TP_ROTATE_0;
    ctx->release              = TP_RELEASE_DET;
    ctx->touch_prev.n_touches = 0;

    for ( idx = 0; idx < TP_N_TOUCHES_MAX; idx++ )
    {
        ctx->touch_prev.point[ idx ].coord_x = TP_PRESS_COORD_DEFAULT;
        ctx->touch_prev.point[ idx ].coord_y = TP_PRESS_COORD_DEFAULT;
        ctx->touch_prev.point[ idx ].event   = TP_EVENT_PRESS_NOT_DET;
        ctx->touch_prev.point[ idx ].id      = TP_TOUCH_ID_5;
    }
    ctx->gesture_prev = TP_EVENT_GEST_NONE;

    if ( cfg->width < cfg->height )
    {
        ctx->width       = 0;
        ctx->height      = 0;
        ctx->coord_x_max = 0;
        ctx->coord_y_max = 0;

        return TP_ERR_SIZE;
    }

    ctx->width       = cfg->width;
    ctx->height      = cfg->height;
    ctx->coord_x_max = cfg->width;
    ctx->coord_y_max = cfg->height;

    return TP_OK;
}

void
tp_press_callback_setup( tp_t * ctx, tp_press_callback_t cb )
{
    ctx->press_callback_f = cb;
}

void
tp_gesture_callback_setup( tp_t * ctx, tp_gesture_callback_t cb )
{
    ctx->gesture_callback_f = cb;
}

void
tp_rotate( tp_t * ctx, tp_rotate_t rotate )
{
    if ( ctx->rotate == rotate )
    {
        return;
    }

    ctx->rotate = rotate;
    ctx->curr_pos = ctx->start_pos + ctx->rotate;

    if ( ctx->curr_pos > 3 )
    {
        ctx->curr_pos -= 4;
    }

    if ( ctx->width > ctx->height )
    {
        if ( ( rotate == TP_ROTATE_90 ) ||
             ( rotate == TP_ROTATE_270 ) )
        {
            uint16_t tmp;

            tmp         = ctx->width;
            ctx->width  = ctx->height;
            ctx->height = tmp;
        }
    }
    else if ( ctx->width < ctx->height )
    {
        if ( ( rotate == TP_ROTATE_0 ) ||
             ( rotate == TP_ROTATE_180 ) )
        {
            uint16_t tmp;

            tmp         = ctx->width;
            ctx->width  = ctx->height;
            ctx->height = tmp;
        }
    }
}

tp_rotate_t
tp_get_orientation( tp_t * ctx )
{
    return ctx->rotate;
}

void
tp_get_size( tp_t * ctx, uint16_t * width, uint16_t * height )
{
    *width  = ctx->width;
    *height = ctx->height;
}

tp_event_t
tp_press_detect( tp_t * ctx )
{
    return ctx->tp_drv->tp_press_detect_f( ctx->tp_drv_ctx );
}

tp_err_t
tp_press_coordinates( tp_t * ctx, tp_touch_item_t * touch_item )
{
    uint8_t idx;
    uint8_t state = 0;
    tp_err_t status = TP_OK;

    ctx->tp_drv->tp_press_coordinates_f( ctx->tp_drv_ctx, &ctx->touch );

    for ( idx = 0; idx < ctx->touch.n_touches; idx++ )
    {
        if ( ctx->touch.point[ idx ].event == TP_EVENT_PRESS_UP )
        {
            state = 1;
        }
    }

    if ( ( ctx->touch_prev.n_touches > ctx->touch.n_touches ) || ( state == 1 ) )
    {
        for ( idx = 0; idx < ctx->touch_prev.n_touches; idx++ )
        {
            tp_get_rotated_coord( ctx, &ctx->touch_prev_mirr, &ctx->touch_prev, idx );

            ctx->touch_prev_mirr.point[ idx ].id = ctx->touch_prev.point[ idx ].id;
        }

        for ( idx = 0; idx < ctx->touch.n_touches; idx++ )
        {
            ctx->touch_prev.point[ idx ].coord_x = ctx->touch_prev.point[ idx + 1 ].coord_x;
            ctx->touch_prev.point[ idx ].coord_y = ctx->touch_prev.point[ idx + 1 ].coord_y;
            ctx->touch_prev.point[ idx ].id      = ctx->touch_prev.point[ idx + 1 ].id;
            ctx->touch_prev.point[ idx ].event   = TP_EVENT_PRESS_MOVE;
        }

        for ( idx = ctx->touch_prev.n_touches; idx > ctx->touch.n_touches; idx-- )
        {
            ctx->touch_prev.point[ idx - 1 ].coord_x = TP_PRESS_COORD_DEFAULT;
            ctx->touch_prev.point[ idx - 1 ].coord_y = TP_PRESS_COORD_DEFAULT;
            ctx->touch_prev.point[ idx - 1 ].event   = TP_EVENT_PRESS_NOT_DET;
            ctx->touch_prev.point[ idx - 1 ].id      = TP_TOUCH_ID_5;
        }
    }

    for ( idx = 0; idx < ctx->touch.n_touches; idx++ )
    {
        if ( ( ctx->touch.point[ idx ].coord_x <= ctx->coord_x_max ) &&
             ( ctx->touch.point[ idx ].coord_y <= ctx->coord_y_max ) )
        {
            tp_get_rotated_coord( ctx, touch_item, &ctx->touch, idx );

            if ( ( ctx->touch.point[ idx ].coord_x != ctx->touch_prev.point[ idx ].coord_x ) ||
                 ( ctx->touch.point[ idx ].coord_y != ctx->touch_prev.point[ idx ].coord_y ) )
            {
                if ( ctx->touch.point[ idx ].event == ctx->touch_prev.point[ idx ].event )
                {
                    touch_item->point[ idx ].event = TP_EVENT_PRESS_NOT_DET;
                }
                else
                {
                    touch_item->point[ idx ].event     = ctx->touch.point[ idx ].event;
                    touch_item->point[ idx ].id        = ctx->touch.point[ idx ].id;
                    ctx->touch_prev.point[ idx ].event = ctx->touch.point[ idx ].event;
                }

                ctx->touch_prev.point[ idx ].coord_x = ctx->touch.point[ idx ].coord_x;
                ctx->touch_prev.point[ idx ].coord_y = ctx->touch.point[ idx ].coord_y;
                ctx->touch_prev.point[ idx ].id      = ctx->touch.point[ idx ].id;
            }
            else
            {
                touch_item->point[ idx ].event = TP_EVENT_PRESS_NOT_DET;

                if ( ctx->touch_prev.point[ idx ].event == TP_EVENT_PRESS_MOVE )
                {
                    ctx->touch_prev.point[ idx ].event = TP_EVENT_PRESS_NOT_DET;
                }
            }
        }
        else
        {
            touch_item->point[ idx ].event     = TP_EVENT_PRESS_NOT_DET;
            ctx->touch_prev.point[ idx ].event = TP_EVENT_PRESS_NOT_DET;

            status = TP_ERR_PRESS_COORD;
        }
    }

    touch_item->n_touches = ctx->touch.n_touches;

    return status;
}

void
tp_gesture( tp_t * ctx, tp_event_t * event )
{
    uint8_t idx;

    ctx->tp_drv->tp_gesture_f( ctx->tp_drv_ctx, &ctx->gesture );

    if ( ( ctx->gesture == TP_EVENT_GEST_NONE ) ||
         ( ctx->gesture == TP_EVENT_GEST_ZOOM_IN ) ||
         ( ctx->gesture == TP_EVENT_GEST_ZOOM_OUT ) )
    {
        if ( ctx->gesture != ctx->gesture_prev )
        {
            *event = ctx->gesture;
        }
        else
        {
            *event = TP_EVENT_GEST_NONE;
        }

        ctx->gesture_prev = ctx->gesture;

        return;
    }

    for ( idx = 0; idx < TP_GESTURE_ITEMS; idx++ )
    {
        if ( ctx->gesture == TP_GESTURE_ID.gest_items[ idx ].gest_rot0 )
        {
            if ( ctx->gesture == ctx->gesture_prev )
            {
                *event = TP_EVENT_GEST_NONE;

                return;
            }

            switch ( ctx->curr_pos )
            {
                case TP_ROTATE_0 :
                {
                    *event = TP_GESTURE_ID.gest_items[ idx ].gest_rot0;
                break;
                }
                case TP_ROTATE_90 :
                {
                    *event = TP_GESTURE_ID.gest_items[ idx ].gest_rot90;
                break;
                }
                case TP_ROTATE_180 :
                {
                    *event = TP_GESTURE_ID.gest_items[ idx ].gest_rot180;
                break;
                }
                default :
                {
                    *event = TP_GESTURE_ID.gest_items[ idx ].gest_rot270;
                break;
                }
            }

            ctx->gesture_prev = ctx->gesture;

            return;
        }
    }
}

tp_err_t
tp_process( tp_t * ctx )
{
    tp_err_t status;
    tp_touch_item_t touch_item;

    status = ctx->tp_drv->tp_process_f( ctx->tp_drv_ctx );

    if ( status != TP_OK )
    {
        return status;
    }

    if ( TP_EVENT_PRESS_DET == tp_press_detect( ctx ) )
    {
        uint8_t idx;

        status = tp_press_coordinates( ctx, &touch_item );

        for ( idx = 0; idx < touch_item.n_touches; idx++ )
        {
            if ( ( touch_item.point[ idx ].event != TP_EVENT_PRESS_NOT_DET ) &&
                 ( touch_item.point[ idx ].event != TP_EVENT_PRESS_UP ) )
            {
                if ( ctx->press_callback_f != NULL )
                {
                    ctx->press_callback_f( touch_item.point[ idx ].event,
                                           touch_item.point[ idx ].coord_x,
                                           touch_item.point[ idx ].coord_y,
                                           touch_item.point[ idx ].id );
                }
            }
        }

        if ( ctx->touch_prev.n_touches > touch_item.n_touches )
        {
            uint8_t idx2;
            uint8_t state;

            for ( idx = 0; idx < ctx->touch_prev.n_touches; idx++ )
            {
                state = 0;

                for ( idx2 = 0; idx2 < touch_item.n_touches; idx2++ )
                {
                    if ( ctx->touch_prev_mirr.point[ idx ].id == ctx->touch_prev.point[ idx2 ].id )
                    {
                        state = 1;
                    }
                }

                if ( ( ctx->press_callback_f != NULL ) && ( state == 0 ) )
                {
                    ctx->press_callback_f( TP_EVENT_PRESS_UP,
                                           ctx->touch_prev_mirr.point[ idx ].coord_x,
                                           ctx->touch_prev_mirr.point[ idx ].coord_y,
                                           ctx->touch_prev_mirr.point[ idx ].id );
                }
            }
        }

        ctx->touch_prev.n_touches = touch_item.n_touches;

        if ( status == TP_OK )
        {
            tp_event_t event;

            tp_gesture( ctx, &event );

            if ( event != TP_EVENT_GEST_NONE )
            {
                if ( ctx->gesture_callback_f != NULL )
                {
                    ctx->gesture_callback_f( event );
                }
            }
        }

        ctx->release = TP_RELEASE_NOT_DET;
    }
    else if ( !ctx->release )
    {
        uint8_t idx;

        for ( idx = 0; idx < ctx->touch_prev.n_touches; idx++ )
        {
            if ( ctx->press_callback_f != NULL )
            {
                ctx->press_callback_f( TP_EVENT_PRESS_UP,
                                       touch_item.point[ idx ].coord_x,
                                       touch_item.point[ idx ].coord_y,
                                       touch_item.point[ idx ].id );
            }
        }

        for ( idx = 0; idx < ctx->touch_prev.n_touches; idx++ )
        {
            ctx->touch_prev.point[ idx ].coord_x = TP_PRESS_COORD_DEFAULT;
            ctx->touch_prev.point[ idx ].coord_y = TP_PRESS_COORD_DEFAULT;
            ctx->touch_prev.point[ idx ].event   = TP_EVENT_PRESS_NOT_DET;
            ctx->touch_prev.point[ idx ].id      = TP_TOUCH_ID_5;
        }

        ctx->gesture_prev         = TP_EVENT_GEST_NONE;
        ctx->release              = TP_RELEASE_DET;
        ctx->touch_prev.n_touches = 0;
    }

    return status;
}

static void
tp_get_rotated_coord( tp_t * ctx, tp_touch_item_t * to, tp_touch_item_t * from,
                      uint8_t index )
{
    switch ( ctx->curr_pos )
    {
        case TP_ROTATE_0 :
        {
            to->point[ index ].coord_x = from->point[ index ].coord_x;
            to->point[ index ].coord_y = from->point[ index ].coord_y;
        break;
        }
        case TP_ROTATE_90 :
        {
            to->point[ index ].coord_x = from->point[ index ].coord_y;
            to->point[ index ].coord_y = ctx->coord_x_max -
                                         from->point[ index ].coord_x;
        break;
        }
        case TP_ROTATE_180 :
        {
            to->point[ index ].coord_x = ctx->coord_x_max -
                                         from->point[ index ].coord_x;
            to->point[ index ].coord_y = ctx->coord_y_max -
                                         from->point[ index ].coord_y;
        break;
        }
        default :
        {
            to->point[ index ].coord_x = ctx->coord_y_max -
                                         from->point[ index ].coord_y;
            to->point[ index ].coord_y = from->point[ index ].coord_x;
        break;
        }
    }
}

// ------------------------------------------------------------------------ END
