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

/**
 * @brief Touch Panel Private Macros.
 * @details Specified macros for internal usage.
 */
#define TP_PRESS_COORD_DEFAULT  0xFFFF
#define TP_RELEASE_NOT_DET      0
#define TP_RELEASE_DET          1

/**
 * @brief TP Get Rotated Coordinates Function.
 * @details This function allows user to get rotated coordinates of the
 * determined touch point from the touch item data.
 * @param[in] ctx : TP context object. See #tp_t structure definition for
 * detailed explanation.
 * @param[out] to : Touch item data where rotated coordinates be stored.
 * See tp_touch_coord_t structure definition for detailed explanation.
 * @param[in] from : Touch item data from which non-rotated coordinates be
 * calculated. See tp_touch_coord_t structure definition for detailed
 * explanation.
 * @return Nothing.
 * @note This function depends on the selected display (touch panel) placement
 * rotation.
 */
static void tp_get_rotated_coord( tp_t *ctx, tp_touch_coord_t *to, tp_touch_coord_t *from );

void tp_cfg_setup( tp_cfg_t *cfg ) {
    cfg->width = TFT_DISPLAY_WIDTH;
    cfg->height = TFT_DISPLAY_HEIGHT;
    cfg->start_pos = TP_ROTATE_0;
}

tp_err_t tp_init( tp_t *ctx, tp_cfg_t *cfg, tp_drv_t *drv, void *drv_ctx ) {
    ctx->tp_drv = drv;
    ctx->tp_drv_ctx = drv_ctx;

    ctx->press_callback_f = NULL;
    ctx->start_pos = cfg->start_pos;
    ctx->curr_pos = cfg->start_pos;
    ctx->rotate = TP_ROTATE_0;
    ctx->release = TP_RELEASE_DET;

    ctx->touch_prev.coord_x = TP_PRESS_COORD_DEFAULT;
    ctx->touch_prev.coord_y = TP_PRESS_COORD_DEFAULT;
    ctx->touch_prev.id = TP_TOUCH_ID_0;

    if ( cfg->width < cfg->height ) {
        ctx->width = 0;
        ctx->height = 0;
        ctx->coord_x_max = 0;
        ctx->coord_y_max = 0;

        return TP_ERR_SIZE;
    }

    ctx->width = cfg->width;
    ctx->height = cfg->height;
    ctx->coord_x_max = cfg->width;
    ctx->coord_y_max = cfg->height;

    return TP_OK;
}

void tp_press_callback_setup( tp_t *ctx, tp_press_callback_t cb ) {
    ctx->press_callback_f = cb;
}

void tp_rotate( tp_t *ctx, tp_rotate_t rotate ) {
    if ( rotate == ctx->rotate ) {
        return;
    }

    ctx->rotate = rotate;
    ctx->curr_pos = ctx->start_pos + ctx->rotate;

    if ( ctx->curr_pos > 3 ) {
        ctx->curr_pos -= 4;
    }

    if ( ctx->width > ctx->height ) {
        if ( ( TP_ROTATE_90 == rotate ) ||
             ( TP_ROTATE_270 == rotate ) ) {
            uint16_t tmp;

            tmp = ctx->width;
            ctx->width = ctx->height;
            ctx->height = tmp;
        }
    } else if ( ctx->width < ctx->height ) {
        if ( ( TP_ROTATE_0 == rotate ) ||
             ( TP_ROTATE_180 == rotate ) ) {
            uint16_t tmp;

            tmp = ctx->width;
            ctx->width = ctx->height;
            ctx->height = tmp;
        }
    }
}

tp_rotate_t tp_get_orientation( tp_t *ctx ) {
    return ctx->rotate;
}

void tp_get_size( tp_t *ctx, uint16_t *width, uint16_t *height ) {
    *width = ctx->width;
    *height = ctx->height;
}

tp_event_t tp_press_detect( tp_t *ctx ) {
    return ctx->tp_drv->tp_press_detect_f( ctx->tp_drv_ctx );
}

tp_err_t tp_press_coordinates( tp_t *ctx, tp_touch_coord_t *touch_item )
{
    uint8_t state = 0;
    tp_err_t status = TP_OK;

    ctx->tp_drv->tp_press_coordinates_f( ctx->tp_drv_ctx, &ctx->touch );

    if ( TP_EVENT_PRESS_UP == ctx->touch.event ) {
        state = 1;
    }

    if ( state ) {
        tp_get_rotated_coord( ctx, &ctx->touch_prev_mirr, &ctx->touch_prev );
        ctx->touch_prev_mirr.id = ctx->touch_prev.id;

        ctx->touch_prev.coord_x = ctx->touch_prev.coord_x;
        ctx->touch_prev.coord_y = ctx->touch_prev.coord_y;
        ctx->touch_prev.id = ctx->touch_prev.id;
        ctx->touch_prev.event = TP_EVENT_PRESS_MOVE;
    }

    if ( ( ctx->touch.coord_x <= ctx->coord_x_max ) &&
         ( ctx->touch.coord_y <= ctx->coord_y_max ) ) {
        tp_get_rotated_coord( ctx, touch_item, &ctx->touch );

        if ( ( ctx->touch.coord_x != ctx->touch_prev.coord_x ) ||
                ( ctx->touch.coord_y != ctx->touch_prev.coord_y ) ) {
            touch_item->event = ctx->touch.event;
            touch_item->id = ctx->touch.id;
            ctx->touch_prev.event = ctx->touch.event;

            ctx->touch_prev.coord_x = ctx->touch.coord_x;
            ctx->touch_prev.coord_y = ctx->touch.coord_y;
            ctx->touch_prev.id = ctx->touch.id;
        } else {
            touch_item->event = TP_EVENT_PRESS_NOT_DET;

            if ( ctx->touch_prev.event == TP_EVENT_PRESS_MOVE )
            {
                ctx->touch_prev.event = TP_EVENT_PRESS_NOT_DET;
            }
        }
    } else {
        touch_item->event = TP_EVENT_PRESS_NOT_DET;
        ctx->touch_prev.event = TP_EVENT_PRESS_NOT_DET;

        status = TP_ERR_PRESS_COORD;
    }

    return status;
}

tp_err_t tp_process( tp_t *ctx ) {
    tp_err_t status;
    tp_touch_coord_t touch_item;

    status = ctx->tp_drv->tp_process_f( ctx->tp_drv_ctx );

    if ( TP_OK != status ) {
        return status;
    }

    if ( TP_EVENT_PRESS_DET == tp_press_detect( ctx ) ) {
        status = tp_press_coordinates( ctx, &touch_item );

        if ( ( TP_EVENT_PRESS_NOT_DET != touch_item.event ) &&
             (  TP_EVENT_PRESS_UP != touch_item.event ) ) {
            if ( NULL != ctx->press_callback_f ) {
                ctx->press_callback_f( touch_item.event,
                                       touch_item.coord_x,
                                       touch_item.coord_y,
                                       touch_item.id );
            }
        }

        ctx->release = TP_RELEASE_NOT_DET;
    } else if ( !ctx->release ) {
        if ( NULL != ctx->press_callback_f ) {
            ctx->press_callback_f( TP_EVENT_PRESS_UP,
                                   touch_item.coord_x,
                                   touch_item.coord_y,
                                   touch_item.id );
        }

        ctx->touch_prev.coord_x = TP_PRESS_COORD_DEFAULT;
        ctx->touch_prev.coord_y = TP_PRESS_COORD_DEFAULT;
        ctx->touch_prev.id = TP_TOUCH_ID_0;

        ctx->release = TP_RELEASE_DET;
    }

    return status;
}

static void tp_get_rotated_coord( tp_t *ctx, tp_touch_coord_t *to, tp_touch_coord_t *from )
{
    switch ( ctx->curr_pos ) {
        case TP_ROTATE_0 :
            to->coord_x = from->coord_x;
            to->coord_y = from->coord_y;
            break;
        case TP_ROTATE_90 :
            to->coord_x = from->coord_y;
            to->coord_y = ctx->coord_x_max - from->coord_x;
            break;
        case TP_ROTATE_180 :
            to->coord_x = ctx->coord_x_max - from->coord_x;
            to->coord_y = ctx->coord_y_max - from->coord_y;
            break;

        default :
            to->coord_x = ctx->coord_y_max - from->coord_y;
            to->coord_y = from->coord_x;
            break;
    }
}

// ------------------------------------------------------------------------ END
