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
 * @file tsc2003.h
 * @brief TSC2003 Resistive Touch Controller Driver.
 */

/**
 * @brief Command byte representation:
 *
 * -----------------------------------------
 * | C3 | C2 | C1 | C0 | PD1 | PD0 | M | X |
 * -----------------------------------------
 *
 * @b Where:
 *     @b Cx represents config bits;
 *     @b PDx represents power down mode;
 *     @b M represents ADC resolution;
 *     @b X is not important ( Don't care );
 */

#ifndef _TSC2003_H_
#define _TSC2003_H_

#ifdef __cplusplus
extern "C"{
#endif

#include "drv_digital_out.h"
#include "drv_i2c_master.h"
#include "drv_digital_in.h"
#include "drv_name.h"
#include "tp.h"

/**
 * @addtogroup middlewaregroup Middleware
 * @brief This section includes the mikroSDK API Reference for Middleware Layer.
 * @{
 */

/*!
 * @addtogroup tsc2003 TSC2003 Touch Controllers Driver
 * @brief TSC2003 Touch Controller Driver API Reference.
 * @{
 */

/**
 * @defgroup tsc2003_slave_addreses Defines possible TSC2003 slave addreses.
 * @details I2C device address options.
 * @note Address depends on @b A0 and @b A1 jumpers
 * on the back of the PCB.
 * @{
 */
#define TSC2003_I2C_SLAVE_ADDR_FIXED   (0x48)
#define TSC2003_I2C_SLAVE_ADDR_A0      (0x1)
#define TSC2003_I2C_SLAVE_ADDR_A1      (0x2)
#define TSC2003_I2C_SLAVE_ADDR_0       (TSC2003_I2C_SLAVE_ADDR_FIXED)
#define TSC2003_I2C_SLAVE_ADDR_1       (TSC2003_I2C_SLAVE_ADDR_FIXED | \
                                        TSC2003_I2C_SLAVE_ADDR_A0)
#define TSC2003_I2C_SLAVE_ADDR_2       (TSC2003_I2C_SLAVE_ADDR_FIXED | \
                                        TSC2003_I2C_SLAVE_ADDR_A1)
#define TSC2003_I2C_SLAVE_ADDR_3       (TSC2003_I2C_SLAVE_ADDR_FIXED | \
                                        TSC2003_I2C_SLAVE_ADDR_A0 | \
                                        TSC2003_I2C_SLAVE_ADDR_A1)
#define TSC2003_I2C_SLAVE_ADDR_DEFAULT (TSC2003_I2C_SLAVE_ADDR_3)
/** @} */ // tsc2003_slave_addreses

/**
 * @defgroup tsc2003_config_data Macro used to configure data byte.
 * @{
 */
#define configureData(c,pd,m) ((c<<4)|(pd<<2)|(m<<1))
/** @} */ // tsc2003_config_data

/**
 * @brief Map adequate control pins.
 */
#define TSC2003_MAP_PINS( cfg ) \
    cfg.i2c_cfg.scl = CTP_SCL; \
    cfg.i2c_cfg.sda = CTP_SDA; \
    cfg.int_pin     = CTP_INT

/**
 * @defgroup tsc2003_bits_cfg Config nibbles.
 * @details Higher nibble @b <7:4> used for operand values.
 *
 * |    CONFIG BITS    |
 * ---------------------
 * | C3 | C2 | C1 | C0 |
 *
 * @note
 *     Shifted to higher nibble in library.
 */
typedef enum {
    tsc2003_bits_cfg_measure_temp0, /**< Measure ambient temperature method 1. */
    tsc2003_bits_cfg_measure_vbat1, /**< Measure main battery voltage. */
    tsc2003_bits_cfg_measure_in1, /**< Measure auxiliary input 1. */
    tsc2003_bits_cfg_measure_temp1 = 0x4, /**< Measure ambient temperature method 2. */
    tsc2003_bits_cfg_measure_vbat2, /**< Measure secondary battery voltage. */
    tsc2003_bits_cfg_measure_in2, /**< Measure auxiliary input 2. */
    tsc2003_bits_cfg_measure_activate_drivers_x = 0x8, /**< Activate X- drivers. */
    tsc2003_bits_cfg_measure_activate_drivers_y, /**< Activate Y- drivers. */
    tsc2003_bits_cfg_measure_activate_drivers_x_y, /**< Activate X-,Y+ plate drivers. */
    tsc2003_bits_cfg_measure_position_x = 0xC, /**< measure X AD conversion. */
    tsc2003_bits_cfg_measure_position_y, /**< Measure Y AD conversion. */
    tsc2003_bits_cfg_measure_position_z1, /**< Measure Z1 AD conversion result. */
    tsc2003_bits_cfg_measure_position_z2 /**< measure Z2 AD conversion result. */
} tsc2003_bits_cfg;
/** @} */ // tsc2003_bits_cfg

/**
 * @defgroup tsc2003_bits_pd Power down values.
 * @details Bits @b <3:2> used for values.
 *
 * |     POWER DOWN    |
 * ---------------------
 * |   PD1   |   PD2   |
 *
 * @note
 *     Shifted to adequate position in library.
 */
typedef enum {
    tsc2003_bits_pd_power_down_between_conversion, /**< Power-Down Between Conversions. */
    tsc2003_bits_pd_int_ref_off_adc_on, /**< Internal reference OFF, ADC ON. */
    tsc2003_bits_pd_int_ref_on_adc_off, /**< Internal reference ON, ADC OFF. */
    tsc2003_bits_pd_int_ref_on_adc_on /**< Internal reference ON, ADC ON. */
} tsc2003_bits_pd;
/** @} */ // tsc2003_bits_pd

/**
 * @defgroup tsc2003_bits_m Mode bit values.
 * @details Bit <1> used for value.
 *
 * | MODE |
 * --------
 * |  M   |
 *
 * @note
 *     Shifted to adequate position in library.
 */
typedef enum {
    tsc2003_bits_m_12bit, /**< 12-bit AD conversion mode. */
    tsc2003_bits_m_8bit /**< 8-bit AD conversion mode. */
} tsc2003_bits_m;
/** @} */ // tsc2003_bits_m

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
} tsc2003_calibration_data_t;

/**
 * @brief Press intensity needed to register touch event.
 */
typedef struct {
    uint16_t tsc2003_pressure_threshold_lower; /**< Lower threshold level. Typically 1000. */
    uint16_t tsc2003_pressure_threshold_upper; /**< Upper threshold level. Typically 6000. */
} tsc2003_pressure_threshold_t;

/**
 * @brief Default calibration data specific for MikroE resistive tft boards.
 * @details Data useful for skipping calibration when working with MikroE hardware.
 * Gives reasonable touch precision on any size resitive tft board.
 */
extern const tsc2003_calibration_data_t TSC2003_CALIBRATION_DATA_DEFAULT;

/**
 * @brief TSC2003 Configuration Object.
 * @details Configuration object definition for TSC2003 touch controller.
 */
typedef struct {
    pin_name_t int_pin; /**< Interrupt pin. */

    i2c_master_config_t i2c_cfg; /**< Configuration of communication module. */

    uint16_t width; /**< Touch panel width in pixels. */
    uint16_t height; /**< Touch panel height in pixels. */

    uint8_t addr_sel; /**< I2C slave address of TSC2003. */

    tsc2003_bits_m resolution; /**< AD conversion resolution. */
    tsc2003_bits_pd power_down; /**< Power down state between AD conversions. */

    /**< Press intensity needed to register touch event. */
    tsc2003_pressure_threshold_t pressure_threshold_level;
} tsc2003_cfg_t;

/**
 * @brief TSC2003 Context Object.
 * @details Context object definition for TSC2003 touch controller.
 * This structure holds information about the current state of the controller.
 * @warning Changing values inside this structure is not recomended as it can cause unwanted and incorrect
 * behaviour when used with @ref tsc2003_process function.
 */
typedef struct {
    digital_in_t int_pin; /**< Interrupt pin object. */

    i2c_master_t i2c; /**< Communication module object. */

    uint16_t width; /**< Touch panel width in pixels. */
    uint16_t height; /**< Touch panel height in pixels. */

    tp_event_t press_det; /**< Touch pressure event. */
    tp_touch_item_t touch; /**< Touch item. */
    tp_event_t gesture; /**< Gesture event. */

    bool pen_down; /**< Utility helper variable used for interpreting events. */

    tsc2003_bits_m resolution; /**< AD conversion resolution. */
    tsc2003_bits_pd power_down; /**< Power down state between AD conversions. */

    /**< Press intensity needed to register touch event. */
    tsc2003_pressure_threshold_t pressure_threshold_level;

    /**< Calibration constants used for converting raw ADC touch data to actual pixel coordinates.*/
    tsc2003_calibration_data_t calibration_data;
} tsc2003_t;

/**
 * @brief TSC2003 configuration object setup function
 * @details This function initializes TSC2003 configuration structure to default values.
 * Interupt pin will be set to unconnected, screen dimenstion will be set to 0,
 * press threshold will be set to default defined values.
 * @param[out] cfg TSC2003 configuration object.
 * @retval Nothing.
 */
void tsc2003_cfg_setup( tsc2003_cfg_t * cfg );

/**
 * @brief TSC2003 Initialization Function.
 * @details  This function initializes TSC2003 context object using configuration values
 * from TSC2003 configuration object and allows touch panel driver interface object
 * to be linked with TSC2003 driver functions.
 * @note By default, TSC2003 stucture is initialized with calibration constants for
 * MikroE harware, in case of different hardware @ref tsc2003_set_calibration_data is available
 * for seting already determined calibration constants and @ref tsc2003_calibrate is available
 * for determinig new calibraiton constants.
 * @param[in] ctx Initialized TSC2003 context structure. See @ref tsc2003_t for more
 * information about the context structure.
 * @param[in] cfg TSC2003 configuration object. See @ref tsc2003_cfg_t structure
 * definition for detailed explanation.
 * @param[out] drv TP driver interface object. See @ref tp_drv_t structure
 * definition for detailed explanation.
 * @retval @li @c TP_OK OK,
 *         @li @c TP_ERR_INIT_DRV I2C driver init error,
 *         @li @c TP_ERR_UNSUPPORTED_PIN Unsupported pin.
 * See @ref tp_err_t structure definition for detailed explanation.
 */
tp_err_t tsc2003_init( tsc2003_t * ctx, tsc2003_cfg_t * cfg, tp_drv_t * drv );

/**
 * @brief TSC2003 Default Configuration Function.
 * @details Configures the device by powering the module down initially.
 * @param[in] ctx Initialized TSC2003 context structure. See @ref tsc2003_t for more
 * information about the context structure.
 * @retval Nothing.
 */
void tsc2003_default_cfg( tsc2003_t* ctx );

/**
 * @brief Copies touch information from context object to touch item object
 * @details This function is necessary for interfacing with touch panel library as it's
 * address is stored in tp_drv_t driver structure during the TSC2003 context initialization.
 * @param[in] ctx Initialized TSC2003 context structure. See @ref tsc2003_t for more
 * information about the context structure.
 * @param[out] touch_item
 * @return Nothing.
 */
void tsc2003_press_coordinates( tsc2003_t* ctx, tp_touch_item_t * touch_item );

/**
 * @brief Press detection function.
 * @details Retrives information about press detection from TSC2003.
 * @note This function is necessary for interfacing with touch panel library as its
 * address is stored in tp_drv_t driver structure during the TSC2003 context initialization.
 * @param[in] ctx Initialized TSC2003 context structure. See @ref tsc2003_t for more
 * information about the context structure.
 * @retval @li @c TP_EVENT_PRESS_NOT_DET - Touch pressure is not detected.
 *         @li @c TP_EVENT_PRESS_DET - Touch pressure is detected.
 * See @ref tp_err_t structure definition for detailed explanation.
 */
tp_event_t tsc2003_press_detect( tsc2003_t* ctx );

/**
 * @brief Function processing events.
 * @details This function checks if touch was detected and if it was, reads
 * and stores touch information in context structure and checks if it's touch down or up.
 * @note This function is necessary for interfacing with touch panel library as its
 * address is stored in tp_drv_t driver structure during the TSC2003 context initialization.
 * @param[in] ctx Initialized TSC2003 context structure. See @ref tsc2003_t for more
 * information about the context structure.
 * @retval Always returns @b TP_OK. see @ref tp_err_t for more details.
 */
tp_err_t tsc2003_process( tsc2003_t * ctx );

/**
 * @brief Read gesture information.
 * @details Since TSC2003 does not support gestures this function is purely for interfacing
 * with the tp library. Gesture returned from the function is always no gesture.
 * @param[in] ctx Initialized TSC2003 context structure. See @ref tsc2003_t for more
 * information about the context structure.
 * @note This function is necessary for interfacing with touch panel library as it's
 * address is stored in tp_drv_t driver structure during the TSC2003 context initialization.
 * @param[out] event Touch panel gesture data, always TP_EVENT_GEST_NONE. See @ref tp_event_t * definition
 * for detailed explanation.
 * @retval Nothing.
 */
void tsc2003_gesture( tsc2003_t* ctx, tp_event_t * event );

/**
 * @brief Writes a generic command to the IC.
 * @details This function provides easy write access to the TSC2003 IC.
 * @param[in] ctx Initialized TSC2003 context structure. See @ref tsc2003_t for more
 * information about the context structure.
 * @param[in] reg_addr Register address with adequate configuration.
 * @note Register address is defined as follows:
 * -----------------------------------------
 * | C3 | C2 | C1 | C0 | PD1 | PD0 | M | X |
 * -----------------------------------------
 *   @b Where:
 *     @b Cx represents config bits; - see @ref tsc2003_bits_cfg
 *     @b PDx represents power down mode; - see @ref tsc2003_bits_pd
 *     @b M represents ADC resolution; - see @ref tsc2003_bits_m
 *     @b X is not important ( Don't care );
 *   The formatted address will be:
 *     @b ((Cx<<4) | @b (PDx<<2) | @b (M<<1))
 * @retval Nothing.
 */
void tsc2003_write_cmd( tsc2003_t * ctx, uint8_t reg_addr );

/**
 * @brief Reads a number of bytes from a register.
 * @details This function provides easy read from a TSC2003 register.
 * @param[in] ctx Initialized TSC2003 context structure. See @ref tsc2003_t for more
 * information about the context structure.
 * @param[in] reg_addr Register address from which single byte will be read.
 * @note Register address is defined as follows:
 * -----------------------------------------
 * | C3 | C2 | C1 | C0 | PD1 | PD0 | M | X |
 * -----------------------------------------
 *   @b Where:
 *     @b Cx represents config bits; - see @ref tsc2003_bits_cfg
 *     @b PDx represents power down mode; - see @ref tsc2003_bits_pd
 *     @b M represents ADC resolution; - see @ref tsc2003_bits_m
 *     @b X is not important ( Don't care );
 *   The formatted address will be:
 *     @b ((Cx<<4) | @b (PDx<<2) | @b (M<<1))
 * @param[out] data_buff Buffer for returning read data from IC.
 * @param[in] len Number of data to read from the IC.
 * @retval Nothing.
 */
void tsc2003_generic_read( tsc2003_t * ctx, uint8_t reg_addr, uint8_t *data_buff, uint8_t len );

/**
 * @brief Calibrates variables used for converting raw TSC2003 ADC values to pixel coordinates
 * @details Function nees the user to touch all four corners as close to the edges as possible
 * to find the extreme values. Function also supports holding a pen and moving it across the screen and
 * will use the most extreme coordinates found during that move as corner coordinates, so touching
 * a screen and draging a finger over the one of the four edges unitl touch is no longer detected
 * will give pretty good calibration data.
 * @param[in] ctx Initialized TSC2003 context structure. See @ref tsc2003_t for more
 * information about the context structure.
 * @retval Nothing.
 */
void tsc2003_calibrate( tsc2003_t* ctx );

/**
 * @brief Utility funciton used for getting a copy of current calibration data.
 * @details Function copies data that's being e used for converting raw ADC values
 * to actual pixel coordinates.
 * @param[in] ctx Initialized TSC2003 context structure. See @ref tsc2003_t for more
 * @param[out] cdata Pointer to memory where calibration data will be stored.
 * @retval Nothing.
 */
void tsc2003_get_calibration_data( tsc2003_t * ctx, tsc2003_calibration_data_t * cdata );

/**
 * @brief Utility funciton used for setting calibration data.
 * @details Function copies data stored in @p cdata. That information will be  be used for
 * converting raw ADC values to actual pixel coordinates.
 * @param[in] ctx Initialized TSC2003 context structure. See @ref tsc2003_t for more
 * information about the context structure.
 * @param[out] cdata Pointer to memory from where new calibration will be copied and set.
 * @retval Nothing.
 */
void tsc2003_set_calibration_data( tsc2003_t * ctx, const tsc2003_calibration_data_t * cdata );

/**
 * @brief Utility funciton used for setting threshold levels.
 * @details Function copies data stored in @p pressure. That information will be  be used for
 * checking if adquate pressure has been applied to the screen.
 * @param[out] cfg Initialized TSC2003 context structure. See @ref tsc2003_t for more
 * @param[in] pressure Structure with desired threshold levels set.
 * See @ref tsc2003_pressure_threshold_t for more information about the structure.
 * @retval Nothing.
 */
void tsc2003_set_pressure_threshold_level( tsc2003_cfg_t * cfg, tsc2003_pressure_threshold_t pressure );

/*! @} */ // middlewaregroup
/*! @} */ // tsc2003

#ifdef __cplusplus
}
#endif

#endif // _TSC2003_H_

// ------------------------------------------------------------------------ END
