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
 * @file tp.h
 * @brief Touch Panel API Library.
 *
 * Supported drivers (version 2.0.0):
 * - FT5XX6 Driver.
 */

#ifndef _TP_H_
#define _TP_H_

#include <stdint.h>
#include <stddef.h>

/**
 * @brief Touch Panel Touch Limit.
 * @details Maximal number of possible pressed touches.
 */
#define TP_N_TOUCHES_MAX  5

/**
 * @brief Touch Panel Error Code Definition.
 * @details Specified error codes defined for Touch Panel library.
 */
typedef enum
{
    TP_OK,                  /**< Successful. */
    TP_ERR_INIT_DRV,        /**< Driver initialization error. */
    TP_ERR_UNSUPPORTED_PIN, /**< Unsupported pin error. */
    TP_ERR_SIZE,            /**< Touch panel size error. */
    TP_ERR_PRESS_COORD,     /**< Pressed coordinates error. */
    TP_ERR_N_TOUCHES,       /**< Number of touches error. */
    TP_ERR_N_DATA           /**< Number of data error. */

} tp_err_t;

/**
 * @brief Touch Panel Event Code Definition.
 * @details Specified events defined for Touch Panel library.
 */
typedef enum
{
    TP_EVENT_PRESS_DOWN,    /**< Touch pressed down event. */
    TP_EVENT_PRESS_UP,      /**< Touch released event. */
    TP_EVENT_PRESS_MOVE,    /**< Touch moved event. */
    TP_EVENT_PRESS_NOT_DET, /**< Touch not detected event. */
    TP_EVENT_PRESS_DET,     /**< Touch detected event. */
    TP_EVENT_GEST_NONE,     /**< Touch not slided event. */
    TP_EVENT_GEST_LEFT,     /**< Touch slided left event. */
    TP_EVENT_GEST_RIGHT,    /**< Touch slided right event. */
    TP_EVENT_GEST_UP,       /**< Touch slided up event. */
    TP_EVENT_GEST_DOWN,     /**< Touch slided down event. */
    TP_EVENT_GEST_ZOOM_IN,  /**< Touch zoom in event. */
    TP_EVENT_GEST_ZOOM_OUT  /**< Touch zoom out event. */

} tp_event_t;

/**
 * @brief Touch Point ID Definition.
 * @details Specified id of touch points defined for Touch Panel library.
 */
typedef enum
{
    TP_TOUCH_ID_0,  /**< Touch ID 0. */
    TP_TOUCH_ID_1,  /**< Touch ID 1. */
    TP_TOUCH_ID_2,  /**< Touch ID 2. */
    TP_TOUCH_ID_3,  /**< Touch ID 3. */
    TP_TOUCH_ID_4,  /**< Touch ID 4. */
    TP_TOUCH_ID_5   /**< Touch ID 5. */

} tp_touch_id_t;

/**
 * @brief Touch Panel Placement (Orientation) Definition.
 * @details Possible orientations defined for Touch Panel library.
 */
typedef enum
{
    TP_ROTATE_0,    /**< TP rotation 0 degrees. */
    TP_ROTATE_90,   /**< TP rotation 90 degrees. */
    TP_ROTATE_180,  /**< TP rotation 180 degrees. */
    TP_ROTATE_270   /**< TP rotation 270 degrees. */

} tp_rotate_t;

/**
 * @brief Touch Point Coordinates Data Type.
 * @details Data type of coordinates of touch point defined for Touch Panel
 * library.
 */
typedef uint16_t tp_coord_t;

/**
 * @brief Touch Point Object Definition.
 * @details Touch point object defined for Touch Panel library.
 */
typedef struct
{
    tp_coord_t     coord_x; /**< Touch coordinate x. */
    tp_coord_t     coord_y; /**< Touch coordinate y. */
    tp_event_t     event;   /**< Touch event. */
    tp_touch_id_t  id;      /**< Touch ID. */

} tp_touch_coord_t;

/**
 * @brief Touch Item Definition.
 * @details Touch items defined for Touch Panel library with determined maximal
 * number of items.
 */
typedef struct
{
    tp_touch_coord_t  point[ TP_N_TOUCHES_MAX ];    /**< Touch point objects. */
    uint8_t           n_touches;                    /**< Number of detected touches. */

} tp_touch_item_t;

/**
 * @brief Touch Panel Driver Interface Definition.
 * @details Driver interface defined for touch pressure detection.
 */
typedef tp_event_t ( * tp_press_det_t )( void * );

/**
 * @brief Touch Panel Driver Interface Definition.
 * @details Driver interface defined for touch item.
 */
typedef void ( * tp_press_coord_t )( void *, tp_touch_item_t * );

/**
 * @brief Touch Panel Driver Interface Definition.
 * @details Driver interface defined for gesture event.
 */
typedef void ( * tp_gesture_t )( void *, tp_event_t * );

/**
 * @brief Touch Panel Driver Interface Definition.
 * @details Driver interface defined for process function.
 */
typedef tp_err_t ( * tp_process_t )( void * );

/**
 * @brief Touch Panel Touch Callback Function.
 * @details Touch point callback function defined for Touch Panel library.
 */
typedef void ( * tp_press_callback_t )( tp_event_t, tp_coord_t, tp_coord_t,
                                        tp_touch_id_t );

/**
 * @brief Touch Panel Gesture Callback Function.
 * @details Gesture callback function defined for Touch Panel library.
 */
typedef void ( * tp_gesture_callback_t )( tp_event_t );

/**
 * @brief Touch Panel Driver Interface Items.
 * @details Driver interface items defined for Touch Panel library.
 */
typedef struct
{
    tp_press_det_t    tp_press_detect_f;        /**< Driver press detect function pointer. */
    tp_press_coord_t  tp_press_coordinates_f;   /**< Driver get point function pointer. */
    tp_gesture_t      tp_gesture_f;             /**< Driver gesture function pointer. */
    tp_process_t      tp_process_f;             /**< Driver process function pointer. */

} tp_drv_t;

/**
 * @brief Touch Panel Size And Placement Configuration Object.
 * @details Specified configuration defined for Touch Panel library.
 */
typedef struct
{
    uint16_t     width;         /**< Panel width. */
    uint16_t     height;        /**< Panel height. */
    tp_rotate_t  start_pos;     /**< Panel start position. */

} tp_cfg_t;

/**
 * @brief Touch Panel Context Object.
 * @details Specified context object defined for Touch Panel library.
 */
typedef struct
{
    // Touch panel interface.

    tp_drv_t *       tp_drv;                    /**< Driver (interface) pointer. */
    void *           tp_drv_ctx;                /**< Driver context pointer. */

    tp_press_callback_t   press_callback_f;     /**< Callback function handler. */
    tp_gesture_callback_t gesture_callback_f;   /**< Callback function handler. */

    // Touch panel size and orientation.

    uint16_t         width;                     /**< Panel width. */
    uint16_t         height;                    /**< Panel height. */
    uint16_t         coord_x_max;               /**< Panel maximal x coordinate. */
    uint16_t         coord_y_max;               /**< Panel maximal y coordinate. */
    tp_rotate_t      start_pos;                 /**< Panel start position. */
    uint8_t          curr_pos;                  /**< Panel current position. */
    tp_rotate_t      rotate;                    /**< Panel rotation. */

    // Touch panel current and previous data.

    tp_touch_item_t  touch;                     /**< Touch point item. */
    tp_event_t       gesture;                   /**< Gesture event. */

    tp_touch_item_t  touch_prev;                /**< Touch point previous data. */
    tp_event_t       gesture_prev;              /**< Gesture previous event. */
    tp_touch_item_t  touch_prev_mirr;           /**< Touch point mirrored data. */

    uint8_t          release;                   /**< Touch release detector. */

} tp_t;

/*!
 * \addtogroup middlewaregroup
 * @{
 */

/*!
 * @addtogroup tpgroup Touch Panel Library
 * @brief Touch Panel library API reference.
 * @details API for configuring and manipulating Touch Panel library.
 * @{
 */

#ifdef __cplusplus
extern "C"{
#endif

/**
 * @brief Touch Panel Configuration Function.
 * @details Configures Touch Panel configuration structure to default
 * initialization values.
 * @param[out] cfg : Touch Panel configuration object. See #tp_cfg_t structure
 * definition for detailed explanation.
 * @return Nothing.
 * @note Take into consideration that this is just structure variable initial
 * values setting. Values need to be redefined by user.
 *
 * @b Example
 * @code
 *    // TP configuration object declaration.
 *    tp_cfg_t tp_cfg;
 *
 *    // TP configuration object setup to initial values.
 *    tp_cfg_setup( &tp_cfg );
 * @endcode
 */
void
tp_cfg_setup( tp_cfg_t * cfg );

/**
 * @brief Touch Panel Initialization Function.
 * @details This function initializes Touch Panel context object to default
 * initialization values and executes a linking procedure between Touch Panel
 * API and touch controller driver.
 * @param[out] ctx : Touch Panel context object. See #tp_t structure definition
 * for detailed explanation.
 * @param[in] cfg : Touch Panel configuration object. See #tp_cfg_t structure
 * definition for detailed explanation.
 * @param[in] drv : Touch Panel driver interface object. See #tp_drv_t structure
 * definition for detailed explanation.
 * @param[in] drv_ctx : Touch Panel driver context object. See #ft5xx6_t
 * structure definition for detailed explanation.
 * @return @li @c 0 - OK,
 *         @li @c 3 - Size error.
 * See #tp_err_t structure definition for detailed explanation.
 *
 * @b Example
 * @code
 *    // TP API object.
 *    tp_t tp;
 *    // TP configuration object.
 *    tp_cfg_t tp_cfg;
 *    // TP driver interface object.
 *    tp_drv_t tp_interface;
 *    // FT5xx6 touch controller driver object.
 *    ft5xx6_t ft5xx6;
 *    // FT5xx6 configuration object.
 *    ft5xx6_cfg_t ft5xx6_cfg;
 *    // FT5x26 series touch controllers descriptor.
 *    const ft5xx6_controller_t FT5X26_CONTROLLER;
 *
 *    // FT5xx6 driver setup.
 *    ft5xx6_cfg_setup( &ft5xx6_cfg, &FT5X26_CONTROLLER );
 *    // FT5xx6 driver pin mapping.
 *    FT5XX6_MAP_PINS( ft5xx6_cfg );
 *    // FT5xx6 driver initialization.
 *    ft5xx6_init( &ft5xx6, &ft5xx6_cfg, &tp_interface );
 *    // FT5xx6 driver default configuration.
 *    ft5xx6_default_cfg( &ft5xx6 );
 *
 *    // TP API setup.
 *    tp_cfg_setup( &tp_cfg );
 *    tp_cfg.width  = 800;
 *    tp_cfg.height = 480;
 *    tp_cfg.start_pos = TP_ROTATE_180;
 *    // TP API initialization.
 *    tp_init( &tp, &tp_cfg, &tp_interface, &ft5xx6 );
 * @endcode
 */
tp_err_t
tp_init( tp_t * ctx, tp_cfg_t * cfg, tp_drv_t * drv, void * drv_ctx );

/**
 * @brief Touch Panel Callback Setup Function.
 * @details This function sets callback handler for touch pressure detection.
 * @param[out] ctx : Touch Panel context object. See #tp_t structure definition
 * for detailed explanation.
 * @param[in] cb : Callback function (handler).
 * See #tp_press_callback_t structure definition for detailed explanation.
 * @return Nothing.
 * @note If callback handler is not set, it will be ignored in the code.
 *
 * @b Example
 * @code
 *    // TP API object.
 *    tp_t tp;
 *
 *    // Callback handler function declaration.
 *    void touch_callback( tp_event_t event, tp_coord_t x, tp_coord_t y,
 *                         tp_touch_id_t id );
 *
 *    // Callback handler setting.
 *    tp_press_callback_setup( &tp, touch_callback );
 * @endcode
 */
void
tp_press_callback_setup( tp_t * ctx, tp_press_callback_t cb );

/**
 * @brief Touch Panel Callback Setup Function.
 * @details This function sets callback handler for gesture event.
 * @param[out] ctx : Touch Panel context object. See #tp_t structure definition
 * for detailed explanation.
 * @param[in] cb : Callback function (handler).
 * See #tp_gesture_callback_t structure definition for detailed explanation.
 * @return Nothing.
 * @note If callback handler is not set, it will be ignored in the code.
 *
 * @b Example
 * @code
 *    // TP API object.
 *    tp_t tp;
 *
 *    // Callback handler function declaration.
 *    void gesture_callback( tp_event_t event );
 *
 *    // Callback handler setting.
 *    tp_gesture_callback_setup( &tp, gesture_callback );
 * @endcode
 */
void
tp_gesture_callback_setup( tp_t * ctx, tp_gesture_callback_t cb );

/**
 * @brief Touch Panel Rotate Function.
 * @details This function sets the Touch Panel orientation.
 * @param[out] ctx : Touch Panel context object. See #tp_t structure definition
 * for detailed explanation.
 * @param[in] rotate : Selects the orientation angle. See #tp_rotate_t for valid
 * values.
 * @return Nothing.
 *
 * @b Example
 * @code
 *    // TP API object.
 *    tp_t tp;
 *
 *    // TP rotation setting.
 *    tp_rotate( &tp, TP_ROTATE_0 );
 * @endcode
 */
void
tp_rotate( tp_t * ctx, tp_rotate_t rotate );

/**
 * @brief Touch Panel Orientation Check Function.
 * @details This function checks the Touch Panel orientation state.
 * @param[in] ctx : Touch Panel context object. See #tp_t structure definition
 * for detailed explanation.
 * @return Touch Panel orientation value. See #tp_rotate_t structure definition
 * for detailed explanation.
 *
 * @b Example
 * @code
 *    // TP API object.
 *    tp_t tp;
 *    // TP placement state.
 *    tp_rotate_t state;
 *
 *    // TP placement checking.
 *    state = tp_get_orientation( &tp );
 * @endcode
 */
tp_rotate_t
tp_get_orientation( tp_t * ctx );

/**
 * @brief Touch Panel Size Check Function.
 * @details This function checks the Touch Panel size.
 * @param[in] ctx : Touch Panel context object. See #tp_t structure definition
 * for detailed explanation.
 * @param[out] width : Touch Panel width size.
 * @param[out] height : Touch Panel height size.
 * @return Nothing.
 *
 * @b Example
 * @code
 *    // TP API object.
 *    tp_t tp;
 *    // TP size data.
 *    uint16_t tp_width, tp_height;
 *
 *    // TP size checking.
 *    tp_get_size( &tp, &tp_width, &tp_height );
 * @endcode
 */
void
tp_get_size( tp_t * ctx, uint16_t * width, uint16_t * height );

/**
 * @brief Touch Panel Pressure Detector Function.
 * @details This function checks the touch pressure detection.
 * @param[in] ctx : Touch Panel context object. See #tp_t structure definition
 * for detailed explanation.
 * @return Touch Panel pressure event:
 *          @li @c 3 - Touch is not detected,
 *          @li @c 4 - Touch is detected.
 * See #tp_event_t structure definition for detailed explanation.
 * @note #tp_process function must be called to update all events.
 *
 * @b Example
 * @code
 *    // TP API object.
 *    tp_t tp;
 *    // Touch detection event.
 *    tp_event_t event;
 *
 *    // Touch detection checking.
 *    event = tp_press_detect( &tp );
 * @endcode
 */
tp_event_t
tp_press_detect( tp_t * ctx );

/**
 * @brief Touch Panel Pressure Coordinates Check Function.
 * @details This function allows user to get the information about the number
 * of pressed touch points, coordinates and touch event for each pressed touch
 * point.
 * @param[in] ctx : Touch Panel context object. See #tp_t structure definition
 * for detailed explanation.
 * @param[out] touch_item : Touch item data. See #tp_touch_item_t structure
 * definition for detailed explanation.
 * @return @li @c 0 - OK,
 *         @li @c 4 - Touch coordinates are out of range.
 * See #tp_err_t structure definition for detailed explanation.
 * @note #tp_process function must be called to update all events.
 *
 * @b Example
 * @code
 *    // TP API object.
 *    tp_t tp;
 *    // TP error code.
 *    tp_err_t error;
 *    // Touch pressure item data.
 *    tp_touch_item_t tp_item;
 *
 *    // Touch pressure item getting.
 *    error = tp_press_coordinates( &tp, &tp_item );
 * @endcode
 */
tp_err_t
tp_press_coordinates( tp_t * ctx, tp_touch_item_t * touch_item );

/**
 * @brief Touch Panel Gesture Check Function.
 * @details This function allows user to get the information about the gesture
 * (slide direction).
 * @param[in] ctx : Touch Panel context object. See #tp_t structure definition
 * for detailed explanation.
 * @param[out] event : Touch Panel gesture event. See #tp_event_t structure
 * definition for detailed explanation.
 * @return Nothing.
 * @note #tp_process function must be called to update all events.
 *
 * @b Example
 * @code
 *    // TP API object.
 *    tp_t tp;
 *    // TP gesture event.
 *    tp_event_t event;
 *
 *    // TP gesture event checking.
 *    tp_gesture( &tp, &event );
 * @endcode
 */
void
tp_gesture( tp_t * ctx, tp_event_t * event );

/**
 * @brief Touch Panel Process Function.
 * @details This function detects a touch pressure, and if any touch pressure
 * was detected, then collects all data information and events about the pressed
 * touch and slide direction (gesture), and calls a callback handlers, if they
 * are set.
 * @param[in] ctx : Touch Panel context object. See #tp_t structure definition
 * for detailed explanation.
 * @return @li @c 0 - OK,
 *         @li @c 4 - Touch coordinates are out of range,
 *         @li @c 5 - Number of pressed touches is out of range.
 * See #tp_err_t structure definition for detailed explanation.
 * @note To get all possible events, just need to call this function, but
 * callback handlers must be set first. This function is not blocking function.
 *
 * @b Example
 * @code
 *    // TP API object.
 *    tp_t tp;
 *    // TP error code.
 *    tp_err_t error;
 *
 *    // TP events and data processing.
 *    error = tp_process( &tp );
 * @endcode
 */
tp_err_t
tp_process( tp_t * ctx );

#ifdef __cplusplus
}
#endif
#endif // _TP_H_

/*! @} */ // tpgroup
/*! @} */ // apigroup

// ------------------------------------------------------------------------ END
