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
 * @file ft5xx6.h
 * @brief FT5xx6 Touch Controller Driver.
 */

#ifndef FT5XX6_H
#define FT5XX6_H

#include "drv_i2c_master.h"
#include "drv_digital_in.h"
#include "drv_name.h"
#include "tp.h"

/*!
 * @addtogroup middlewaregroup Middleware
 * @brief This section includes the mikroSDK API Reference for Middleware Layer.
 * @{
 */

/*!
 * @addtogroup ft5xx6 FT5xx6 Touch Controllers Driver
 * @brief FT5xx6 Touch Controller Driver API Reference.
 * @{
 */

/**
 * @defgroup ft5xx6_registers FT5xx6 Registers
 * @brief FT5xx6 Registers List.
 * @details FT5xx6 registers description with respective addresses.
 */

/**
 * @addtogroup ft5xx6_registers
 * @{
 */

/**
 * @brief FT5xx6 Device Mode Register.
 * @details Register address specified for device mode of FT5xx6 touch
 * controller.
 */
#define FT5XX6_REG_DEVICE_MODE          0x0

/**
 * @brief FT5xx6 Gesture ID Register.
 * @details Register address specified for gesture ID of FT5xx6 touch
 * controller.
 */
#define FT5XX6_REG_GEST_ID              0x1

/**
 * @brief FT5xx6 Status Register.
 * @details Register address specified for status of FT5xx6 touch controller.
 */
#define FT5XX6_REG_TD_STATUS            0x2

/**
 * @brief FT5xx6 Touch1 X-coord MSB Register.
 * @details Register address specified for touch1 x coordinate higher byte of
 * FT5xx6 touch controller.
 */
#define FT5XX6_REG_TOUCH1_XH            0x3

/**
 * @brief FT5xx6 Touch1 X-coord LSB Register.
 * @details Register address specified for touch1 x coordinate lower byte of
 * FT5xx6 touch controller.
 */
#define FT5XX6_REG_TOUCH1_XL            0x4

/**
 * @brief FT5xx6 Touch1 Y-coord MSB Register.
 * @details Register address specified for touch1 y coordinate higher byte of
 * FT5xx6 touch controller.
 */
#define FT5XX6_REG_TOUCH1_YH            0x5

/**
 * @brief FT5xx6 Touch1 Y-coord LSB Register.
 * @details Register address specified for touch1 y coordinate lower byte of
 * FT5xx6 touch controller.
 */
#define FT5XX6_REG_TOUCH1_YL            0x6

/**
 * @brief FT5xx6 Touch2 X-coord MSB Register.
 * @details Register address specified for touch2 x coordinate higher byte of
 * FT5xx6 touch controller.
 */
#define FT5XX6_REG_TOUCH2_XH            0x9

/**
 * @brief FT5xx6 Touch2 X-coord LSB Register.
 * @details Register address specified for touch2 x coordinate lower byte of
 * FT5xx6 touch controller.
 */
#define FT5XX6_REG_TOUCH2_XL            0xA

/**
 * @brief FT5xx6 Touch2 Y-coord MSB Register.
 * @details Register address specified for touch2 y coordinate higher byte of
 * FT5xx6 touch controller.
 */
#define FT5XX6_REG_TOUCH2_YH            0xB

/**
 * @brief FT5xx6 Touch2 Y-coord LSB Register.
 * @details Register address specified for touch2 y coordinate lower byte of
 * FT5xx6 touch controller.
 */
#define FT5XX6_REG_TOUCH2_YL            0xC

/**
 * @brief FT5xx6 Touch3 X-coord MSB Register.
 * @details Register address specified for touch3 x coordinate higher byte of
 * FT5xx6 touch controller.
 */
#define FT5XX6_REG_TOUCH3_XH            0xF

/**
 * @brief FT5xx6 Touch3 X-coord LSB Register.
 * @details Register address specified for touch3 x coordinate lower byte of
 * FT5xx6 touch controller.
 */
#define FT5XX6_REG_TOUCH3_XL            0x10

/**
 * @brief FT5xx6 Touch3 Y-coord MSB Register.
 * @details Register address specified for touch3 y coordinate higher byte of
 * FT5xx6 touch controller.
 */
#define FT5XX6_REG_TOUCH3_YH            0x11

/**
 * @brief FT5xx6 Touch3 Y-coord LSB Register.
 * @details Register address specified for touch3 y coordinate lower byte of
 * FT5xx6 touch controller.
 */
#define FT5XX6_REG_TOUCH3_YL            0x12

/**
 * @brief FT5xx6 Touch4 X-coord MSB Register.
 * @details Register address specified for touch4 x coordinate higher byte of
 * FT5xx6 touch controller.
 */
#define FT5XX6_REG_TOUCH4_XH            0x15

/**
 * @brief FT5xx6 Touch4 X-coord LSB Register.
 * @details Register address specified for touch4 x coordinate lower byte of
 * FT5xx6 touch controller.
 */
#define FT5XX6_REG_TOUCH4_XL            0x16

/**
 * @brief FT5xx6 Touch4 Y-coord MSB Register.
 * @details Register address specified for touch4 y coordinate higher byte of
 * FT5xx6 touch controller.
 */
#define FT5XX6_REG_TOUCH4_YH            0x17

/**
 * @brief FT5xx6 Touch4 Y-coord LSB Register.
 * @details Register address specified for touch4 y coordinate lower byte of
 * FT5xx6 touch controller.
 */
#define FT5XX6_REG_TOUCH4_YL            0x18

/**
 * @brief FT5xx6 Touch5 X-coord MSB Register.
 * @details Register address specified for touch5 x coordinate higher byte of
 * FT5xx6 touch controller.
 */
#define FT5XX6_REG_TOUCH5_XH            0x1B

/**
 * @brief FT5xx6 Touch5 X-coord LSB Register.
 * @details Register address specified for touch5 x coordinate lower byte of
 * FT5xx6 touch controller.
 */
#define FT5XX6_REG_TOUCH5_XL            0x1C

/**
 * @brief FT5xx6 Touch5 Y-coord MSB Register.
 * @details Register address specified for touch5 y coordinate higher byte of
 * FT5xx6 touch controller.
 */
#define FT5XX6_REG_TOUCH5_YH            0x1D

/**
 * @brief FT5xx6 Touch5 Y-coord LSB Register.
 * @details Register address specified for touch5 y coordinate lower byte of
 * FT5xx6 touch controller.
 */
#define FT5XX6_REG_TOUCH5_YL            0x1E

/**
 * @brief FT5xx6 Touch Detection Threshold Register.
 * @details Register address specified for touch detection threshold of FT5xx6
 * touch controller.
 */
#define FT5XX6_REG_TOUCH_DET_TH         0x80

/**
 * @brief FT5xx6 Touch Peak Detection Threshold Register.
 * @details Register address specified for touch peak detection threshold of
 * FT5xx6 touch controller.
 */
#define FT5XX6_REG_TOUCH_PEAK_DET_TH    0x81

/**
 * @brief FT5xx6 Touch Threshold Calibration Register.
 * @details Register address specified for touch threshold calibration of FT5xx6
 * touch controller.
 */
#define FT5XX6_REG_TOUCH_TH_CAL         0x82

/**
 * @brief FT5xx6 Touch Threshold Water Register.
 * @details Register address specified for touch threshold water of FT5xx6 touch
 * controller.
 */
#define FT5XX6_REG_TOUCH_TH_WATER       0x83

/**
 * @brief FT5xx6 Touch Threshold Temperature Compensation Register.
 * @details Register address specified for touch threshold temperature
 * compensation of FT5xx6 touch controller.
 */
#define FT5XX6_REG_TOUCH_TH_TEMP_COMP   0x84

/**
 * @brief FT5xx6 Power Control Register.
 * @details Register address specified for power control of FT5xx6 touch
 * controller.
 */
#define FT5XX6_REG_POWER_CTRL_MODE      0x86

/**
 * @brief FT5xx6 Timer Status Monitor Register.
 * @details Register address specified for timer status monitor of FT5xx6 touch
 * controller.
 */
#define FT5XX6_REG_MONITOR_STATUS_TMR   0x87

/**
 * @brief FT5xx6 Actual Period Monitor Register.
 * @details Register address specified for actual period monitor of FT5xx6 touch
 * controller.
 */
#define FT5XX6_REG_MONITOR_ACT_PERIOD   0x88

/**
 * @brief FT5xx6 Enter Idle Timer Register.
 * @details Register address specified for enter idle timer of FT5xx6 touch
 * controller.
 */
#define FT5XX6_REG_ENTER_IDLE_TIMER     0x89

/**
 * @brief FT5xx6 Auto Calibration Register.
 * @details Register address specified for auto calibration of FT5xx6 touch
 * controller.
 */
#define FT5XX6_REG_AUTO_CALIB_MODE      0xA0

/**
 * @brief FT5xx6 Version MSB Register.
 * @details Register address specified for version higher byte of FT5xx6 touch
 * controller.
 */
#define FT5XX6_REG_LIB_VERSION_H        0xA1

/**
 * @brief FT5xx6 Version LSB Register.
 * @details Register address specified for version lower byte of FT5xx6 touch
 * controller.
 */
#define FT5XX6_REG_LIB_VERSION_L        0xA2

/**
 * @brief FT5xx6 Chip Vendor ID Register.
 * @details Register address specified for chip vendor ID of FT5xx6 touch
 * controller.
 */
#define FT5XX6_REG_LIB_CHIP_VENDOR_ID   0xA3

/**
 * @brief FT5xx6 IVT To Host Status Register.
 * @details Register address specified for IVT to host status of FT5xx6 touch
 * controller.
 */
#define FT5XX6_REG_IVT_TO_HOST_STATUS   0xA4

/**
 * @brief FT5xx6 Power Consume Register.
 * @details Register address specified for power consume of FT5xx6 touch
 * controller.
 */
#define FT5XX6_REG_POWER_CONSUME_MODE   0xA5

/**
 * @brief FT5xx6 FW ID Register.
 * @details Register address specified for firmware ID of FT5xx6 touch
 * controller.
 */
#define FT5XX6_REG_FW_ID                0xA6

/**
 * @brief FT5xx6 Running State Register.
 * @details Register address specified for running state of FT5xx6 touch
 * controller.
 */
#define FT5XX6_REG_RUNNING_STATE        0xA7

/**
 * @brief FT5xx6 CTPM Vendor ID Register.
 * @details Register address specified for CTPM vendor ID of FT5xx6 touch
 * controller.
 */
#define FT5XX6_REG_CTPM_VENDOR_ID       0xA8

/**
 * @brief FT5xx6 Error ID Register.
 * @details Register address specified for error ID of FT5xx6 touch controller.
 */
#define FT5XX6_REG_ERROR_ID             0xA9

/**
 * @brief FT5xx6 Calibration Mode Configuration Register.
 * @details Register address specified for calibration mode configuration of
 * FT5xx6 touch controller.
 */
#define FT5XX6_REG_CONFIGURE_CAL_MODE   0xAA

/**
 * @brief FT5xx6 Big Area Threshold Register.
 * @details Register address specified for big area threshold of FT5xx6 touch
 * controller.
 */
#define FT5XX6_REG_BIG_AREA_TH          0xAE

/*! @} */ // ft5xx6_registers

/**
 * @defgroup ft5xx6_settings FT5xx6 Settings
 * @brief FT5xx6 Settings List.
 * @details FT5xx6 settings description with respective values.
 */

/**
 * @addtogroup ft5xx6_settings
 * @{
 */

/**
 * @brief FT5xx6 Interrupt Polling Mode Setting.
 * @details INT pin polling mode setting for FT5xx6 series touch controllers.
 */
#define FT5XX6_INT_MODE_POLLING         0

/**
 * @brief FT5xx6 Interrupt Trigger Mode Setting.
 * @details INT pin trigger mode setting for FT5xx6 series touch controllers.
 */
#define FT5XX6_INT_MODE_TRIGGER         1

/**
 * @brief FT5xx6 Slave Address Setting.
 * @details Slave address setting for FT5xx6 series touch controllers.
 */
#define FT5XX6_I2C_ADDR                 0x38

/**
 * @brief FT5xx6 Data Transfer Limits Setting.
 * @details Data transfer limits for FT5xx6 series touch controllers.
 */
#define FT5XX6_N_DATA_TRANSFER_MIN      1
#define FT5XX6_N_DATA_TRANSFER_MAX      256

/**
 * @brief FT5xx6 Gesture Items Limit Setting.
 * @details Gesture items limit for FT5xx6 series touch controllers.
 */
#define FT5XX6_GESTURE_ITEMS_MAX        7

/**
 * @brief FT5xx6 Touch Pressure Event.
 * @details Touch pressure event for FT5xx6 series touch controllers.
 */
#define FT5XX6_EVENT_PRESS_DET          0x80

/**
 * @defgroup ft5xx6_masks FT5xx6 Masks
 * @brief FT5xx6 Masks List.
 * @details FT5xx6 masks description with respective values.
 */

/**
 * @addtogroup ft5xx6_masks
 * @{
 */

/**
 * @brief FT5xx6 Touch Coordinates Mask.
 * @details Touch pressure coordinates mask for FT5xx6 series touch controllers.
 */
#define FT5XX6_MASK_PRESS_COORD         0xFFF

/**
 * @brief FT5xx6 Touch Event Mask.
 * @details Touch pressure event mask for FT5xx6 series touch controllers.
 */
#define FT5XX6_MASK_PRESS_EVENT         0xC0

/**
 * @brief FT5xx6 Touch Detection Mask.
 * @details Touch pressure detection mask for FT5xx6 series touch controllers.
 */
#define FT5XX6_MASK_PRESS_DET           0xC0

/**
 * @brief FT5xx6 TP Number Mask.
 * @details Touch point number mask for FT5xx6 series touch controllers.
 */
#define FT5XX6_MASK_TP_NUM              0xF

/*! @} */ // ft5xx6_masks

/**
 * @defgroup ft5xx6_offsets FT5xx6 Offsets
 * @brief FT5xx6 Offsets List.
 * @details FT5xx6 offsets description with respective values.
 */

/**
 * @addtogroup ft5xx6_offsets
 * @{
 */

/**
 * @brief FT5xx6 Touch Event Offset.
 * @details Touch event offset for FT5xx6 series touch controllers.
 */
#define FT5XX6_OFFSET_PRESS_EVENT       6

/**
 * @brief FT5xx6 Touch ID Offset.
 * @details Touch ID offset for FT5xx6 series touch controllers.
 */
#define FT5XX6_OFFSET_PRESS_ID          4

/**
 * @brief FT5xx6 Device Mode Offset.
 * @details Device mode offset for FT5xx6 series touch controllers.
 */
#define FT5XX6_OFFSET_DEV_MODE          4

/**
 * @brief FT5xx6 Touch Reading Offset.
 * @details Reading of touches offset for FT5xx6 series touch controllers.
 */
#define FT5XX6_OFFSET_TOUCH_READING     6

/*! @} */ // ft5xx6_offsets

/**
 * @brief FT5xx6 Pin Mapping.
 * @details Utility macro for mapping FT5xx6 series touch controllers.
 */
#define FT5XX6_MAP_PINS( cfg ) \
    cfg.i2c_cfg.scl = CTP_SCL; \
    cfg.i2c_cfg.sda = CTP_SDA; \
    cfg.int_pin     = CTP_INT

/*! @} */ // ft5xx6_settings
/*! @} */ // ft5xx6
/*! @} */ // middlewaregroup

/**
 * @brief FT5xx6 Device Mode Settings.
 * @details Device mode definition for FT5xx6 series touch controllers.
 */
typedef enum
{
    FT5XX6_DEV_MODE_NORMAL,     /**< Normal mode. */
    FT5XX6_DEV_MODE_SYS_INFO,   /**< System info mode. */
    FT5XX6_DEV_MODE_TEST = 4    /**< Device test mode. */

} ft5xx6_dev_mode_t;

/**
 * @brief FT5xx6 Run Mode Settings.
 * @details Run mode definition for FT5xx6 series touch controllers.
 */
typedef enum
{
    FT5XX6_RUN_MODE_CFG,        /**< Config mode. */
    FT5XX6_RUN_MODE_WORK,       /**< Working mode. */
    FT5XX6_RUN_MODE_CAL,        /**< Calibration mode. */
    FT5XX6_RUN_MODE_FACT,       /**< Factory mode. */
    FT5XX6_RUN_MODE_AUTO_CAL    /**< Auto calibration mode. */

} ft5xx6_run_mode_t;

/**
 * @brief FT5xx6 Gesture Item Definition.
 * @details Gesture item definition for FT5xx6 series touch controllers.
 */
typedef struct
{
    uint8_t     key;    /**< Gesture key. */
    tp_event_t  value;  /**< Gesture event value. */

} ft5xx6_gest_item_t;

/**
 * @brief FT5xx6 Gesture Items.
 * @details Gesture items for FT5xx6 series touch controllers.
 */
typedef struct
{
    ft5xx6_gest_item_t  gest_items[ FT5XX6_GESTURE_ITEMS_MAX ];

} ft5xx6_controller_t;

/**
 * @brief FT5xx6 Configuration Object.
 * @details Configuration object definition for FT5xx6 series touch controllers.
 */
typedef struct
{
    pin_name_t           int_pin;   /**< Interrupt pin. */

    i2c_master_config_t  i2c_cfg;   /**< Configuration of communication module. */

    const ft5xx6_controller_t * controller; /**< Touch controller descriptor. */

} ft5xx6_cfg_t;

/**
 * @brief FT5xx6 Context Object.
 * @details Context object definition for FT5xx6 series touch controllers.
 */
typedef struct
{
    i2c_master_t     i2c;           /**< Communication module object. */

    digital_in_t     int_pin;       /**< Interrupt pin object. */

    const ft5xx6_controller_t * controller; /**< Touch controller descriptor. */

    tp_event_t       press_det;     /**< Touch pressure event. */
    tp_touch_item_t  touch;         /**< Touch item. */
    tp_event_t       gesture;       /**< Gesture event. */

} ft5xx6_t;

/**
 * @brief FT5x06 Touch Controllers Descriptor.
 * @details Specified descriptor that describe events of the
 * gesture for each controller from FT5x06 series touch controllers.
 */
extern const ft5xx6_controller_t FT5X06_CONTROLLER;

/**
 * @brief FT5x16 Touch Controllers Descriptor.
 * @details Specified descriptor that describe events of the
 * gesture for each controller from FT5x16 series touch controllers.
 */
extern const ft5xx6_controller_t FT5X16_CONTROLLER;

/**
 * @brief FT5x26 Touch Controllers Descriptor.
 * @details Specified descriptor that describe events of the
 * gesture for each controller from FT5x26 series touch controllers.
 */
extern const ft5xx6_controller_t FT5X26_CONTROLLER;

/**
 * @brief FT5x46 Touch Controllers Descriptor.
 * @details Specified descriptor that describe events of the
 * gesture for each controller from FT5x46 series touch controllers.
 */
extern const ft5xx6_controller_t FT5X46_CONTROLLER;

/*!
 * @addtogroup middlewaregroup Middleware
 * @brief This section includes the mikroSDK API Reference for Middleware Layer.
 * @{
 */

/*!
 * @addtogroup ft5xx6 FT5xx6 Touch Controllers Driver
 * @brief API for configuring and manipulating FT5xx6 Touch Controller driver.
 * @{
 */

#ifdef __cplusplus
extern "C"{
#endif

/**
 * @brief FT5xx6 Configuration Object Setup Function.
 * @details This function initializes FT5xx6 configuration structure to default
 * values.
 * @param[out] cfg : FT5xx6 configuration object. See #ft5xx6_cfg_t structure
 * definition for detailed explanation.
 * @param[in] controller : Touch controller selector from FT5xx6 series touch
 * controllers. See #ft5xx6_controller_t structure definition for detailed
 * explanation.
 * @return Nothing.
 * @note The all used pins will be set to unconnected state.
 *
 * @b Example
 * @code
 *    // FT5xx6 configuration object.
 *    ft5xx6_cfg_t ft5xx6_cfg;
 *    // FT5x26 series touch controllers descriptor.
 *    const ft5xx6_controller_t FT5X26_CONTROLLER =
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
 *    // FT5xx6 configuration setup.
 *    ft5xx6_cfg_setup( &ft5xx6_cfg, &FT5X26_CONTROLLER );
 * @endcode
 */
void
ft5xx6_cfg_setup( ft5xx6_cfg_t * cfg, const ft5xx6_controller_t * controller );

/**
 * @brief FT5xx6 Initialization Function.
 * @details This function initializes FT5xx6 context object to default values
 * and allows driver interface object to be linked with FT5xx6 driver functions.
 * @param[out] ctx : FT5xx6 context object. See #ft5xx6_t structure definition
 * for detailed explanation.
 * @param[in] cfg : FT5xx6 configuration object. See #ft5xx6_cfg_t structure
 * definition for detailed explanation.
 * @param[out] drv : TP driver interface object. See #tp_drv_t structure
 * definition for detailed explanation.
 * @return @li @c 0 - OK,
 *         @li @c 1 - I2C driver init error,
 *         @li @c 2 - Unsupported pin.
 * See #tp_err_t structure definition for detailed explanation.
 *
 * @b Example
 * @code
 *    // FT5xx6 driver object.
 *    ft5xx6_t ft5xx6;
 *    // FT5xx6 configuration object.
 *    ft5xx6_cfg_t ft5xx6_cfg;
 *    // FT5x26 series touch controllers descriptor.
 *    const ft5xx6_controller_t FT5X26_CONTROLLER;
 *    // TP driver interface object.
 *    tp_drv_t tp_interface;
 *
 *    // FT5xx6 configuration setup.
 *    ft5xx6_cfg_setup( &ft5xx6_cfg, &FT5X26_CONTROLLER );
 *    // FT5xx6 controller pin mapping.
 *    FT5XX6_MAP_PINS( ft5xx6_cfg );
 *    // FT5xx6 driver initialization.
 *    ft5xx6_init( &ft5xx6, &ft5xx6_cfg, &tp_interface );
 * @endcode
 */
tp_err_t
ft5xx6_init( ft5xx6_t * ctx, ft5xx6_cfg_t * cfg, tp_drv_t * drv );

/**
 * @brief FT5xx6 Default Configuration Function.
 * @details This function puts the FT5xx6 touch controller to normal operating
 * mode.
 * @param[in] ctx : FT5xx6 context object. See #ft5xx6_t structure definition
 * for detailed explanation.
 * @return Nothing.
 * @note It's necessary for this functon to be executed after Initialization
 * function for properly working of entire driver.
 *
 * @b Example
 * @code
 *    // FT5xx6 driver object.
 *    ft5xx6_t ft5xx6;
 *
 *    // FT5xx6 driver default configuration.
 *    ft5xx6_default_cfg( &ft5xx6 );
 * @endcode
 */
void
ft5xx6_default_cfg( ft5xx6_t * ctx );

/**
 * @brief FT5xx6 Generic Write Function.
 * @details This function allows user to write any 8-bit data to the selected
 * register of the FT5xx6 series touch controllers.
 * @param[in] ctx : FT5xx6 context object. See #ft5xx6_t structure definition
 * for detailed explanation.
 * @param[in] reg_addr : Register address where data be written.
 * @param[in] data_in : Data to be written.
 * @return Nothing.
 *
 * @b Example
 * @code
 *    // FT5xx6 driver object.
 *    ft5xx6_t ft5xx6;
 *
 *    // Setting FT5xx6 controller to configuration mode.
 *    ft5xx6_generic_write( &ft5xx6, FT5XX6_REG_RUNNING_STATE,
 *                          FT5XX6_RUN_MODE_CFG );
 * @endcode
 */
void
ft5xx6_generic_write( ft5xx6_t * ctx, uint8_t reg_addr, uint8_t data_in );

/**
 * @brief FT5xx6 Generic Single Read Function.
 * @details This function allows user to read any desired register of the FT5xx6
 * series touch controllers.
 * @param[in] ctx : FT5xx6 context object. See #ft5xx6_t structure definition
 * for detailed explanation.
 * @param[in] reg_addr : Register address which from data be read.
 * @return 8-bit read data.
 *
 * @b Example
 * @code
 *    // FT5xx6 driver object.
 *    ft5xx6_t ft5xx6;
 *    // Read value.
 *    uint8_t read_data;
 *
 *    // Reading status of FT5xx6 controller to get number of pressed touches.
 *    read_data = ft5xx6_generic_read_single( &ft5xx6, FT5XX6_REG_TD_STATUS );
 * @endcode
 */
uint8_t
ft5xx6_generic_read_single( ft5xx6_t * ctx, uint8_t reg_addr );

/**
 * @brief FT5xx6 Generic Multiple Read Function.
 * @details This function allows user to read the desired number of data bytes,
 * starting from the selected register address.
 * @param[in] ctx : FT5xx6 context object. See #ft5xx6_t structure definition
 * for detailed explanation.
 * @param[in] reg_addr : Register address which from the data reading will be
 * started.
 * @param[out] data_out : Memory where read data will be stored.
 * @param[in] n_bytes : Number of data bytes to be read.
 * @return @li @c 0 - OK,
 *         @li @c 6 - Number of transfered bytes is out of range.
 * See #tp_err_t structure definition for detailed explanation.
 *
 * @b Example
 * @code
 *    // FT5xx6 driver object.
 *    ft5xx6_t ft5xx6;
 *    // Read value.
 *    uint8_t read_data[ 2 ];
 *    // TP error code.
 *    tp_err_t error;
 *
 *    // Reading two data bytes to get x coordinate value of touch1.
 *    error = ft5xx6_generic_read_multiple( &ft5xx6, FT5XX6_REG_TOUCH1_XH,
 *                                          read_data, 2 );
 * @endcode
 */
tp_err_t
ft5xx6_generic_read_multiple( ft5xx6_t * ctx, uint8_t reg_addr,
                              uint8_t * data_out, uint16_t n_bytes );

/**
 * @brief FT5xx6 Device Mode Setup Function.
 * @details This function puts the FT5xx6 series touch controllers to the
 * selected device mode.
 * @param[in] ctx : FT5xx6 context object. See #ft5xx6_t structure definition
 * for detailed explanation.
 * @param[in] mode : device mode of operation. See #ft5xx6_dev_mode_t for valid
 * values.
 * @return Nothing.
 *
 * @b Example
 * @code
 *    // FT5xx6 driver object.
 *    ft5xx6_t ft5xx6;
 *
 *    // Setting device normal operating mode of FT5xx6 series touch controllers.
 *    ft5xx6_dev_mode_setup( &ft5xx6, FT5XX6_DEV_MODE_NORMAL );
 * @endcode
 */
void
ft5xx6_dev_mode_setup( ft5xx6_t * ctx, ft5xx6_dev_mode_t mode );

/**
 * @brief FT5xx6 Run Mode Setup Function.
 * @details This function puts the FT5xx6 series touch controllers to the
 * selected run mode.
 * @param[in] ctx : FT5xx6 context object. See #ft5xx6_t structure definition
 * for detailed explanation.
 * @param[in] mode : run mode of operation. See #ft5xx6_run_mode_t for valid
 * values.
 * @return Nothing.
 *
 * @b Example
 * @code
 *    // FT5xx6 driver object.
 *    ft5xx6_t ft5xx6;
 *
 *    // Setting run working mode of FT5xx6 series touch controllers.
 *    ft5xx6_run_mode_setup( &ft5xx6, FT5XX6_RUN_MODE_WORK );
 * @endcode
 */
void
ft5xx6_run_mode_setup( ft5xx6_t * ctx, ft5xx6_run_mode_t mode );

/**
 * @brief FT5xx6 Touch Pressure Detect Function.
 * @details This function allows the touch pressure detection.
 * @param[in] ctx : FT5xx6 context object. See #ft5xx6_t structure definition
 * for detailed explanation.
 * @return @li @c 3 - Touch pressure is not detected,
 *         @li @c 4 - Touch pressure is detected.
 * See #tp_event_t structure definition for detailed explanation.
 * @note #ft5xx6_process function must be called to update all events.
 *
 * @b Example
 * @code
 *    // FT5xx6 driver object.
 *    ft5xx6_t ft5xx6;
 *    // Touch pressure event.
 *    tp_event_t event;
 *
 *    // Checking touch pressure event.
 *    event = ft5xx6_press_detect( &ft5xx6 );
 * @endcode
 */
tp_event_t
ft5xx6_press_detect( ft5xx6_t * ctx );

/**
 * @brief FT5xx6 Pressure Coordinates Check Function.
 * @details This function allows user to get the informations about the number
 * of pressed touch points, coordinates and touch event for each pressed touch
 * point.
 * @param[in] ctx : FT5xx6 context object. See #ft5xx6_t structure definition
 * for detailed explanation.
 * @param[out] touch_item : Touch item data. See #tp_touch_item_t structure
 * definition for detailed explanation.
 * @return Nothing.
 * @note #ft5xx6_process function must be called to update all events.
 *
 * @b Example
 * @code
 *    // FT5xx6 driver object.
 *    ft5xx6_t ft5xx6;
 *    // Touch pressure item.
 *    tp_touch_item_t tp_item;
 *
 *    // To get all necessary data information about pressed touch.
 *    ft5xx6_press_coordinates( &ft5xx6, &tp_item );
 * @endcode
 */
void
ft5xx6_press_coordinates( ft5xx6_t * ctx, tp_touch_item_t * touch_item );

/**
 * @brief FT5xx6 Gesture Check Function.
 * @details This function allows user to get the informations about the gesture
 * (slide direction).
 * @param[in] ctx : FT5xx6 context object. See #ft5xx6_t structure definition
 * for detailed explanation.
 * @param[out] event : Touch panel gesture data. See #tp_event_t structure
 * definition for detailed explanation.
 * @return Nothing.
 * @note #ft5xx6_process function must be called to update all events.
 *
 * @b Example
 * @code
 *    // FT5xx6 driver object.
 *    ft5xx6_t ft5xx6;
 *    // Gesture event.
 *    tp_event_t event;
 *
 *    // Checking slide direction event of pressed touch.
 *    ft5xx6_gesture( &ft5xx6, &event );
 * @endcode
 */
void
ft5xx6_gesture( ft5xx6_t * ctx, tp_event_t * event );

/**
 * @brief FT5xx6 Process Function.
 * @details This function detects a touch pressure, and if any touch pressure
 * was detected, then collects all informations about the pressed touch and
 * slide direction (gesture).
 * @param[in] ctx : FT5xx6 context object. See #ft5xx6_t structure definition
 * for detailed explanation.
 * @return @li @c 0 - OK,
 *         @li @c 5 - Number of pressed touches is out of range.
 * See #tp_err_t structure definition for detailed explanation.
 * @note To update all possible events, just need to call this function before
 * the any other function for checking events is called.
 *
 * @b Example
 * @code
 *    // FT5xx6 driver object.
 *    ft5xx6_t ft5xx6;
 *    // TP error code.
 *    tp_err_t error;
 *
 *    // Processing all data and events of the target touch controller.
 *    error = ft5xx6_process( &ft5xx6 );
 * @endcode
 */
tp_err_t
ft5xx6_process( ft5xx6_t * ctx );

#ifdef __cplusplus
}
#endif
#endif // FT5XX6_H

/*! @} */ // ft5xx6
/*! @} */ // middlewaregroup

// ------------------------------------------------------------------------ END
