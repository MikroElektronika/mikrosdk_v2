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
 * @file tp_mikroe.h
 * @brief TP_MIKROE Touch Controller Driver.
 */

#ifndef _TP_MIKROE_H_
#define _TP_MIKROE_H_

#ifdef __cplusplus
extern "C"{
#endif

#include "drv_analog_in.h"
#include "drv_digital_out.h"
#include "drv_digital_in.h"
#include "tp.h"
#include "gl.h"
#include "board.h"

/**
 * @addtogroup middlewaregroup Middleware
 * @brief This section includes the mikroSDK API Reference for Middleware Layer.
 * @{
 */

/*!
 * @addtogroup tp_mikroe TP_MIKROE Touch Controllers Driver
 * @brief TP_MIKROE Touch Controller Driver API Reference.
 * @{
 */

/**
 * @brief Defines value for vref.
 */
#define VREF_VALUE 3.3f

#ifndef TP_MIKROE_CALIBRATION_XMIN
#define TP_MIKROE_CALIBRATION_XMIN 0
#endif
#ifndef TP_MIKROE_CALIBRATION_XMAX
#define TP_MIKROE_CALIBRATION_XMAX 0
#endif

#ifndef TP_MIKROE_CALIBRATION_YMIN
#define TP_MIKROE_CALIBRATION_YMIN 0
#endif
#ifndef TP_MIKROE_CALIBRATION_YMAX
#define TP_MIKROE_CALIBRATION_YMAX 0
#endif

#ifndef TP_MIKROE_PRESSURE_THRESHOLD_LOWER
#define TP_MIKROE_PRESSURE_THRESHOLD_LOWER 0
#endif
#ifndef TP_MIKROE_PRESSURE_THRESHOLD_UPPER
#define TP_MIKROE_PRESSURE_THRESHOLD_UPPER 0
#endif

/**
 * @brief Mapping for ADC config structure.
 */
#define TP_MIKROE_MAP_PINS( tp_mikroe_cfg ) \
    tp_mikroe_cfg.left = TP_MIKROE_XL;\
    tp_mikroe_cfg.right = TP_MIKROE_XR;\
    tp_mikroe_cfg.up = TP_MIKROE_YU;\
    tp_mikroe_cfg.down = TP_MIKROE_YD;

/**
 * @brief Calibration data structure.
 * @details Used for converting raw coordinate to actual pixel cordinate.
 */
typedef struct {
    /**< Minimum raw x coordinate value. */
    uint16_t min_x;
    /**< Maximum raw x coordinate value. */
    uint16_t max_x;
    /**< Minimum raw y coordinate value. */
    uint16_t min_y;
    /**< Maximum raw y coordinate value. */
    uint16_t max_y;
} tp_mikroe_calibration_data_t;

/**
 * @brief Pressure threshold data structure.
 * @details Press intensity needed to register touch event.
 */
typedef struct {
    uint16_t tp_mikroe_pressure_threshold_lower; /**< Lower threshold level.*/
    uint16_t tp_mikroe_pressure_threshold_upper; /**< Upper threshold level.*/
} tp_mikroe_pressure_threshold_t;

/**
 * @brief TP_MIKROE Configuration Object.
 * @details Configuration object definition for TP_MIKROE touch controller.
 */
typedef struct {
    pin_name_t left;  /*!< TP XL Pin. */
    pin_name_t right; /*!< TP XR Pin. */
    pin_name_t up;    /*!< TP YU Pin. */
    pin_name_t down;  /*!< TP YD Pin. */

    analog_in_config_t analog_in_cfg_read_x; /*!< ADC configuration structure. */
    analog_in_config_t analog_in_cfg_read_y; /*!< ADC configuration structure. */

    /**< Press intensity needed to register touch event. */
    tp_mikroe_pressure_threshold_t pressure_threshold_level;

    uint16_t width;  /*!< Display width. */
    uint16_t height; /*!< Display height. */
} tp_mikroe_cfg_t;

#define TP_MIKROE_ADC_CONFIG( cfg ) \
    cfg->analog_in_cfg_read_x.resolution = ANALOG_IN_RESOLUTION_CMAKE; \
    cfg->analog_in_cfg_read_y.resolution = ANALOG_IN_RESOLUTION_CMAKE; \
    cfg->analog_in_cfg_read_x.input_pin = TP_READ_X_CMAKE; \
    cfg->analog_in_cfg_read_y.input_pin = TP_READ_Y_CMAKE; \
    cfg->analog_in_cfg_read_x.vref_input = ANALOG_IN_VREF_CMAKE; \
    cfg->analog_in_cfg_read_y.vref_input = ANALOG_IN_VREF_CMAKE; \
    cfg->analog_in_cfg_read_x.vref_value = VREF_VALUE; \
    cfg->analog_in_cfg_read_y.vref_value = VREF_VALUE;

/**
 * @brief TP_MIKROE Context Object.
 * @details Context object definition for TP_MIKROE touch controller.
 */
typedef struct {
    pin_name_t left;  /*!< TP XL Pin. */
    pin_name_t right; /*!< TP XR Pin. */
    pin_name_t up;    /*!< TP YU Pin. */
    pin_name_t down;  /*!< TP YD Pin. */

    analog_in_t analog_in_x; /*!< ADC context structure. */
    analog_in_t analog_in_y; /*!< ADC context structure. */

    tp_event_t press_det;   /**< Touch pressure event. */
    tp_touch_coord_t touch; /**< Touch item. */
    tp_event_t gesture;     /**< Gesture event. */
    tp_rotate_t rotate;     /**< Panel rotation. */

    bool pen_down; /**< Utility helper variable used for interpreting events. */

    /**< Press intensity needed to register touch event. */
    tp_mikroe_pressure_threshold_t pressure_threshold_level;

    /**< Calibration constants used for converting raw ADC touch data to actual pixel coordinates.*/
    tp_mikroe_calibration_data_t calibration_data;

    uint16_t width;  /**< Touch panel width in pixels. */
    uint16_t height; /**< Touch panel height in pixels. */
} tp_mikroe_t;

/**
 * @brief Macros used to draw arrows during tp_mikroe_calibration.
 */
#define SET_PEN() \
    gl_set_pen( GL_WHITE, 4 );

#define DRAW_ARROW_TOP_LEFT() \
    gl_clear( GL_BLACK ); \
    gl_draw_line( 0, 0, 10, 0 ); \
    gl_draw_line( 0, 0, 0, 10 ); \
    gl_draw_line( 0, 0, 15, 15 );

#define DRAW_ARROW_TOP_RIGHT() \
    gl_clear( GL_BLACK ); \
    gl_draw_line( 320, 0, 320, 10 ); \
    gl_draw_line( 320, 0, 310, 0 ); \
    gl_draw_line( 320, 0, 305, 15 );

#define DRAW_ARROW_BOTTOM_LEFT() \
    gl_clear( GL_BLACK ); \
    gl_draw_line( 0, 240, 0, 230 ); \
    gl_draw_line( 0, 240, 10, 240 ); \
    gl_draw_line( 0, 240, 15, 225 );

#define DRAW_ARROW_BOTTOM_RIGHT() \
    gl_clear( GL_BLACK ); \
    gl_draw_line( 320, 240, 320, 230 ); \
    gl_draw_line( 320, 240, 310, 240 ); \
    gl_draw_line( 320, 240, 305, 225 );

/**
 * @brief Function processing events.
 * @details This function checks if touch was detected and if it was, reads
 * and stores touch information in context structure and checks if it's touch down or up.
 * @note This function is necessary for interfacing with touch panel library as its
 * address is stored in tp_drv_t driver structure during the TP_MIKROE context initialization.
 * @param[in] ctx Initialized TP_MIKROE context structure. See @ref tp_mikroe_t for more
 * information about the context structure.
 * @retval Always returns @b TP_OK. see @ref tp_err_t for more details.
 */
tp_err_t tp_mikroe_process( tp_mikroe_t *ctx );

/**
 * @brief Read gesture information.
 * @details Since TP_MIKROE does not support gestures this function is purely for interfacing
 * with the tp library. Gesture returned from the function is always no gesture.
 * @param[in] ctx Initialized TP_MIKROE context structure. See @ref tp_mikroe_t for more
 * information about the context structure.
 * @note This function is necessary for interfacing with touch panel library as it's
 * address is stored in tp_drv_t driver structure during the TP_MIKROE context initialization.
 * @param[in] event Touch panel gesture data, always TP_EVENT_GEST_NONE. See @ref tp_event_t * definition
 * for detailed explanation.
 * @retval Nothing.
 */
void tp_mikroe_gesture ( tp_mikroe_t *ctx, tp_event_t *event );

/**
 * @brief Press detection function.
 * @details Retrieves information about press detection from TP_MIKROE.
 * @note This function is necessary for interfacing with touch panel library as its
 * address is stored in tp_drv_t driver structure during the TP_MIKROE context initialization.
 * @param[in] ctx Initialized TP_MIKROE context structure. See @ref tp_mikroe_t for more
 * information about the context structure.
 * @retval @li @c TP_EVENT_PRESS_NOT_DET - Touch pressure is not detected.
 *         @li @c TP_EVENT_PRESS_DET - Touch pressure is detected.
 * See @ref tp_err_t structure definition for detailed explanation.
 */
tp_event_t tp_mikroe_press_detect ( tp_mikroe_t *ctx );

/**
 * @brief Copies touch information from context object to touch item object
 * @details This function is necessary for interfacing with touch panel library as it's
 * address is stored in tp_drv_t driver structure during the TP_MIKROE context initialization.
 * @param[in] tp_instance TP instance. See #tp_t structure definition for detailed explanation.
 * @param[in] touch_item
 * @return Nothing.
 */
void tp_mikroe_press_coordinates ( tp_mikroe_t *ctx, tp_touch_coord_t *touch_item );

/**
 * @brief Calibrates variables used for converting raw TP_MIKROE ADC values to pixel coordinates
 * @details Function needs the user to touch all four corners as close to the edges as possible
 * to find the extreme values.
 * @param[in] *tp_instance TP instance. See @ref tp_mikroe_t for more information about the context structure.
 * @retval Nothing.
 */
void tp_mikroe_calibrate( tp_t *tp_instance );

/**
 * @brief Utility function used for getting a copy of current calibration data.
 * @details Function copies data that's being used for converting raw ADC values
 * to actual pixel coordinates.
 * @param[in] ctx Initialized TP_MIKROE context structure. See @ref tp_mikroe_t for more
 * @param[in] cdata Pointer to memory where calibration data will be stored.
 * @retval Nothing.
 */
void tp_mikroe_get_calibration_data ( tp_mikroe_t *ctx, tp_mikroe_calibration_data_t *cdata );

/**
 * @brief Utility function used for setting calibration data.
 * @details Function copies data stored in @p cdata. That information will be  be used for
 * converting raw ADC values to actual pixel coordinates.
 * @param[in] ctx Initialized TP_MIKROE context structure. See @ref tp_mikroe_t for more
 * information about the context structure.
 * @param[in] cdata Pointer to memory from where new calibration will be copied and set.
 * @retval Nothing.
 */
void tp_mikroe_set_calibration_data ( tp_mikroe_t *ctx, const tp_mikroe_calibration_data_t *cdata );

/**
 * @brief Utility function used for setting threshold levels.
 * @details Function copies data stored in @p pressure. That information will be  be used for
 * checking if adequate pressure has been applied to the screen.
 * @param[in] cfg Initialized TP_MIKROE context structure. See @ref tp_mikroe_t for more
 * information about the context structure.
 * @param[in] pressure Structure with desired threshold levels set.
 * See @ref tp_mikroe_pressure_threshold_t for more information about the structure.
 * @retval Nothing.
 */
void tp_mikroe_set_pressure_threshold_level ( tp_mikroe_cfg_t *cfg, tp_mikroe_pressure_threshold_t pressure );

/**
 * @brief Function for reading raw ADC data.
 * @details Function reads X, Y data and checks if
 * adequate pressure has been applied to the screen.
 * @param[in] ctx Initialized TP_MIKROE context structure. See @ref tp_mikroe_t for more
 * information about the context structure.
 * @param[in] x_pos Pointer to where X AD conversion result will be placed.
 * @param[in] y_pos Pointer to where Y AD conversion result will be placed.
 * @retval @b True(1) or @b False(0) based on pressure level.
 */
bool tp_mikroe_check_pressure ( tp_mikroe_t *ctx, uint16_t *x_pos, uint16_t *y_pos );

/**
 * @brief Utility function used for setting threshold levels.
 * @param[in] cfx Initialized TP_MIKROE context structure. See @ref tp_mikroe_t for more
 * information about the context structure.
 * @param[in] threshold_upper Desired upper threshold level.
 * @param[in] threshold_lower Desired lower threshold level.
 * @retval Nothing.
 */
void tp_mikroe_set_threshold ( tp_mikroe_t *ctx, uint16_t threshold_upper, uint16_t threshold_lower );

/**
 * @brief Converts @p x_pos & @p y_pos raw ADC values to coordinate values and stores them
 *in 'touch point 0' ctx member.
 * @param[in] ctx Initialized TP_MIKROE context structure. See @ref tp_mikroe_t for more
 * information about the context structure.
 * @param[in] x_pos X coordinate ADC value.
 * @param[in] y_pos Y coordinate ADC value.
 * @retval Nothing.
 */
void tp_mikroe_update_ctx_coords( tp_mikroe_t *ctx, uint16_t x_pos, uint16_t y_pos );

/**
 * @brief Utility function used for calibration.
 * @details Uses tp_mikroe_check_pressure to get raw coordinates and if any of the coordinates passes extreme value
 * updates min_x/max_x/min_y/max_y. If @p callibration_points_uninitialized is true then initializes ts extremes with
 * read values.
 * @param[in] ctx Initialized TP_MIKROE context structure. See @ref tp_mikroe_t for more
 * information about the context structure.
 * @param[in] calibration_points_uninitialized Initial point or not.
 * @note @p calibration_points_uninitialized should be @b true only for the first point.
 * @retval Nothing.
 */
void tp_mikroe_calibrate_point ( tp_mikroe_t *ctx, bool calibration_points_uninitialized );

/**
 * @brief Function used for checking pressure levels.
 * @details Function reads raw ADC value and checks if it's between lower and upper pressure threshold.
 * @param[in] ctx Initialized TP_MIKROE context structure. See @ref tp_mikroe_t for more
 * @retval True if press is detected, False if not.
 */
char tp_mikroe_pressure_level_detect ( tp_mikroe_t *ctx );

 /**
 * @brief TP_MIKROE Configuration setup Function.
 * @details Sets ADC configuration structure to appropriate values.
 * @param[in] cfg TP_MIKROE configuration object.
 * See #tp_mikroe_cfg_t structure definition for detailed explanation.
 * @retval Nothing.
 */
void tp_mikroe_cfg_setup( tp_mikroe_cfg_t *cfg );

/**
 * @brief TP_MIKROE Touch Panel initialization.
 * This function initializes TP_MIKROE context object using configuration values
 * from TP_MIKROE configuration object and allows touch panel driver interface object
 * to be linked with TP_MIKROE driver functions.
 * @note By default, TP_MIKROE structure is initialized with calibration constants for
 * MikroE hardware, in case of different hardware @ref tp_mikroe_set_calibration_data is available
 * for seting already determined calibration constants and @ref tp_mikroe_calibrate is available
 * for determining new calibration constants.
 * @param[in] ctx Initialized TP_MIKROE context structure. See @ref tp_mikroe_t for more
 * information about the context structure.
 * @param[in] cfg TP_MIKROE configuration object. See @ref tp_mikroe_cfg_t structure
 * definition for detailed explanation.
 * @param[in] drv TP driver interface object. See @ref tp_drv_t structure
 * definition for detailed explanation.
 * @retval @li @c TP_OK OK,
 * See @ref tp_err_t structure definition for detailed explanation.
 */
tp_err_t tp_mikroe_init_tp( tp_mikroe_t *ctx, tp_mikroe_cfg_t *cfg , tp_drv_t *drv );

 /**
 * @brief TP_MIKROE ADC pin configuration function.
 * @details Sets ADC pins to appropriate values.
 * @param[in] ctx TP_MIKROE context object.
 * See #tp_mikroe_t structure definition for detailed explanation.
 * @retval Nothing.
 */
void tp_mikroe_default_cfg_adc( tp_mikroe_t *ctx );

/*! @} */ // tp_mikroe
/*! @} */ // mwgroup

#ifdef __cplusplus
}
#endif

#endif // _TP_MIKROE_H_

// ------------------------------------------------------------------------ END
