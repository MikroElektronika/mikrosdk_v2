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
 * @file stmpe811.h
 * @brief STMPE811 Touch Controller Driver.
 */

#ifndef _STMPE811_H_
#define _STMPE811_H_

#ifdef __cplusplus
extern "C"{
#endif

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
 * @addtogroup stmpe811 STMPE811 Touch Controllers Driver
 * @brief STMPE811 Touch Controller Driver API Reference.
 * @{
 */

/**
 * @defgroup stmpe811_slave_addreses
 * @brief Defines for two possible STMPE811 slave addreses.
 * @{
 */
#define STMPE811_I2C_SLAVE_ADDR_0 (0x82 >> 1)
#define STMPE811_I2C_SLAVE_ADDR_1 (0x88 >> 1)
/** @} */ // stmpe811_slave_addreses

/**
 * @brief STMPE811 Pin Mapping.
 * @details Utility macro for mapping STMPE811 touch controllers.
 */
#define STMPE811_MAP_PINS( cfg ) \
    cfg.i2c_cfg.scl = CTP_SCL; \
    cfg.i2c_cfg.sda = CTP_SDA; \
    cfg.int_pin     = CTP_INT

/**
 * @brief Enumeration holding all STMPE811 register adresses.
 */
#define STMPE811_REG_ADDR_CHIP_ID        ((uint8_t)0x00) /**< 16 bit read only only register Device identification. Value after reset: 0x0811 */
#define STMPE811_REG_ADDR_ID_VER         ((uint8_t)0x02) /**< 8 bit read only register for revision number engineering sample final silicon, value : 0x03. */
#define STMPE811_REG_ADDR_SYS_CTRL1      ((uint8_t)0x03) /**< 8 bit read/write register for reset control. Value after reset 0x00*/
#define STMPE811_REG_ADDR_SYS_CTRL2      ((uint8_t)0x04) /**< 8 bit read/write register for clock control. Value after reset: 0x0F. */
#define STMPE811_REG_ADDR_SPI_CFG        ((uint8_t)0x08) /**< 8 bit read/write register for SPI interface configuration. Value after reset 0x01*/
#define STMPE811_REG_ADDR_INT_CTRL       ((uint8_t)0x09) /**< 8 bit read/write interrupt control register. */
#define STMPE811_REG_ADDR_INT_EN         ((uint8_t)0x0A) /**< 8 bit read/write interrupt enable register. */
#define STMPE811_REG_ADDR_INT_STA        ((uint8_t)0x0B) /**< 8 bit read only interrupt status register. */
#define STMPE811_REG_ADDR_GPIO_EN        ((uint8_t)0x0C) /**< 8 bit read/write GPIO interrupt enable register. */
#define STMPE811_REG_ADDR_GPIO_INT_STA   ((uint8_t)0x0D) /**< 8 bit read only GPIO interrupt status register. */
#define STMPE811_REG_ADDR_ADC_INT_EN     ((uint8_t)0x0E) /**< 8 bit read/write ADC interrupt enable register. */
#define STMPE811_REG_ADDR_ADC_INT_STA    ((uint8_t)0x0F) /**< 8 bit read only ADC interrupt status register. */
#define STMPE811_REG_ADDR_GPIO_SET_PIN   ((uint8_t)0x10) /**< 8 bit read/write GPIO set pin register. */
#define STMPE811_REG_ADDR_GPIO_CLR_PIN   ((uint8_t)0x11) /**< 8 bit read/write GPIO clear pin register. */
#define STMPE811_REG_ADDR_GPIO_MP_STA    ((uint8_t)0x12) /**< 8 bit read/write GPIO monitor pin state register. */
#define STMPE811_REG_ADDR_GPIO_DIR       ((uint8_t)0x13) /**< 8 bit read/write GPIO direction register. */
#define STMPE811_REG_ADDR_GPIO_ED        ((uint8_t)0x14) /**< 8 bit read/write GPIO edge detect register. */
#define STMPE811_REG_ADDR_GPIO_RE        ((uint8_t)0x15) /**< 8 bit read/write GPIO rising edge register. */
#define STMPE811_REG_ADDR_GPIO_FE        ((uint8_t)0x16) /**< 8 bit read/write GPIO falling edge register. */
#define STMPE811_REG_ADDR_GPIO_AF        ((uint8_t)0x17) /**< 8 bit read/write Alternate function register. */
#define STMPE811_REG_ADDR_ADC_CTRL1      ((uint8_t)0x20) /**< 8 bit read/write 0x1C ADC control register. */
#define STMPE811_REG_ADDR_ADC_CTRL2      ((uint8_t)0x21) /**< 8 bit read/write 0x01 ADC control register. */
#define STMPE811_REG_ADDR_ADC_CAPT       ((uint8_t)0x22) /**< 8 bit read/write xFF To initiate ADC data acquisition. */
#define STMPE811_REG_ADDR_ADC_DATA_CH0   ((uint8_t)0x30) /**< 16 bit read only register for ADC channel 0. */
#define STMPE811_REG_ADDR_ADC_DATA_CH1   ((uint8_t)0x32) /**< 16 bit read only register for ADC channel 1 STMPE811 registers STMPE811 20/66 Doc ID 14489 Rev 5. */
#define STMPE811_REG_ADDR_ADC_DATA_CH2   ((uint8_t)0x34) /**< 16 bit read only register for ADC channel 2. */
#define STMPE811_REG_ADDR_ADC_DATA_CH3   ((uint8_t)0x36) /**< 16 bit read only register for ADC channel 3. */
#define STMPE811_REG_ADDR_ADC_DATA_CH4   ((uint8_t)0x38) /**< 16 bit read only register for ADC channel 4. */
#define STMPE811_REG_ADDR_ADC_DATA_CH5   ((uint8_t)0x3A) /**< 16 bit read only register for ADC channel 5. */
#define STMPE811_REG_ADDR_ADC_DATA_CH6   ((uint8_t)0x3C) /**< 16 bit read only register for ADC channel 6. */
#define STMPE811_REG_ADDR_ADC_DATA_CH7   ((uint8_t)0x3E) /**< 16 bit read only register for ADC channel 7. */
#define STMPE811_REG_ADDR_TSC_CTRL       ((uint8_t)0x40) /**< 8 bit read/write 4-wire touchscreen controller setup. Value after reset: 0x90 */
#define STMPE811_REG_ADDR_TSC_CFG        ((uint8_t)0x41) /**< 8 bit read/write Touchscreen controller configuration. Value after reset: 0x00 */
#define STMPE811_REG_ADDR_WDW_TR_X       ((uint8_t)0x42) /**< 16 bit read/write Window setup for top right X. Value after reset: 0x0fff */
#define STMPE811_REG_ADDR_WDW_TR_Y       ((uint8_t)0x44) /**< 16 bit read/write Window setup for top right Y. Value after reset: 0x0fff */
#define STMPE811_REG_ADDR_WDW_BL_X       ((uint8_t)0x46) /**< 16 bit read/write Window setup for bottom left X. Value after reset: 0x0000 */
#define STMPE811_REG_ADDR_WDW_BL_Y       ((uint8_t)0x48) /**< 16 bit read/write Window setup for bottom left Y. Value after reset: 0x0000 */
#define STMPE811_REG_ADDR_FIFO_TH        ((uint8_t)0x4A) /**< 8 bit read/write FIFO level to generate interrupt. Value after reset: 0x00*/
#define STMPE811_REG_ADDR_FIFO_STA       ((uint8_t)0x4B) /**< 8 bit read/write Current status of FIFO. Value after reset: 0x20*/
#define STMPE811_REG_ADDR_FIFO_SIZE      ((uint8_t)0x4C) /**< 8 bit read only Current filled level of FIFO. */
#define STMPE811_REG_ADDR_TSC_DATA_X     ((uint8_t)0x4D) /**< 16 bit read only Data port for touchscreen controller data access. */
#define STMPE811_REG_ADDR_TSC_DATA_Y     ((uint8_t)0x4F) /**< 16 bit read only Data port for touchscreen controller data access. */
#define STMPE811_REG_ADDR_TSC_DATA_Z     ((uint8_t)0x51) /**< 8 bit read only Data port for touchscreen controller data access. */
#define STMPE811_REG_ADDR_TSC_DATA_XYZ   ((uint8_t)0x52) /**< 32 bit read only Data port for touchscreen controller data access. */
#define STMPE811_REG_ADDR_TSC_FRACTION_Z ((uint8_t)0x56) /**< 8 bit Touchscreen controller FRACTION_Z. Value after reset: 0x00 */
#define STMPE811_REG_ADDR_TSC_DATA       ((uint8_t)0x57) /**< 8 bit read only register. Data port for touchscreen controller data access. Value after reset: 0x00*/
#define STMPE811_REG_ADDR_TSC_I_DRIVE    ((uint8_t)0x58) /**< 8 bit read/write register. Touchscreen controller drive I. Value after reset: 0x00*/
#define STMPE811_REG_ADDR_TSC_SHIELD     ((uint8_t)0x59) /**< 8 bit read/write register. Touchscreen controller shield. Value after reset: 0x00 */
#define STMPE811_REG_ADDR_TEMP_CTRL      ((uint8_t)0x60) /**< 8 bit read/write register. Temperature sensor setup. Value after reset: 0x00 */
#define STMPE811_REG_ADDR_TEMP_DATA      ((uint8_t)0x61) /**< 8 bit read only register. Temperature data access port. Value after reset: 0x00 */
#define STMPE811_REG_ADDR_TEMP_TH        ((uint8_t)0x62) /**< 8 bit read/write register. Threshold for temperature controlled interrupt. Value after reset: 0x00#define */

/**
 * @defgroup FIFO_STA_register_bits FIFO_STA register bits
 * @details FIFO control and status bits for FIFO_CTRL register.
 * @{
 */
#define STMPE811_FIFO_STA_START          ((uint8_t)( 0 ))
#define STMPE811_FIFO_STA_RESET          ((uint8_t)( 1 ))
#define STMPE811_FIFO_TH_TRIG_BIT        ((uint8_t)( 1 << 4 ))
#define STMPE811_FIFO_EMPTY_BIT          ((uint8_t)( 1 << 5 ))
#define STMPE811_FIFO_FULL_BIT           ((uint8_t)( 1 << 6 ))
#define STMPE811_FIFO_OFLOW_BIT          ((uint8_t)( 1 << 7 ))
/** @} */ // FIFO_STA_register_bits

/**
 * @defgroup TSC_CTRL_register_bits
 * @details Touch screen controler control bits for TSC_CTRL register.
 * @{
 */
#define STMPE811_TSC_CTRL_ENABLE         ((uint8_t)( 1 ))
#define STMPE811_TSC_CTRL_OP_MOD_XYZ     ((uint8_t)( 0 ))
#define STMPE811_TSC_CTRL_OP_MOD_XY      ((uint8_t)( 1 << 1 ))
#define STMPE811_TSC_CTRL_OP_MOD_X       ((uint8_t)( 2 << 1 ))
#define STMPE811_TSC_CTRL_OP_MOD_Y       ((uint8_t)( 3 << 1 ))
#define STMPE811_TSC_CTRL_OP_MOD_Z       ((uint8_t)( 4 << 1 ))
#define STMPE811_TSC_CTRL_STA_BIT        ((uint8_t)( 1 << 7 ))
/** @} */ // TSC_CTRL_register_bits

/**
 * @defgroup INT_CTRL_register_bits
 * @details Interrupt Configuration bits for INT_CTRL register.
 * @{
 */
#define STMPE811_INT_CTRL_GLOBAL_INT_BIT    ((uint8_t)( 1 ))
#define STMPE811_INT_CTRL_INT_TYPE_BIT      ((uint8_t)( 1 << 1 ))
#define STMPE811_INT_CTRL_INT_POLARITY_BIT  ((uint8_t)( 1 << 2 ))
/** @} */ // INT_CTRL_register_bits

/**
 * @defgroup SYS_CTRL2_register_bits
 * @details Configuration bits for SYS_CTRL2 register
 * @{
 */
#define STMPE811_SYS_CTRL2_ADC_OFF_BIT    ((uint8_t)( 1 ))
#define STMPE811_SYS_CTRL2_TSC_OFF_BIT    ((uint8_t)( 1 << 1 ))
#define STMPE811_SYS_CTRL2_GPIO_OFF_BIT   ((uint8_t)( 1 << 2 ))
#define STMPE811_SYS_CTRL2_TS_OFF_BIT     ((uint8_t)( 1 << 3 ))
/** @} */ // SYS_CTRL2_register_bits

/**
 * @defgroup INTERUPT_bits
 * @details Bits same for int_sta and int_en regster
 * @{
 */
#define STMPE811_INT_GPIO       ((uint8_t)( 1 << 7 ))
#define STMPE811_INT_ADC        ((uint8_t)( 1 << 6 ))
#define STMPE811_INT_TEMP_SENS  ((uint8_t)( 1 << 5 ))
#define STMPE811_INT_FIFO_EMPTY ((uint8_t)( 1 << 4 ))
#define STMPE811_INT_FIFO_FULL  ((uint8_t)( 1 << 3 ))
#define STMPE811_INT_FIFO_OFLOW ((uint8_t)( 1 << 2 ))
#define STMPE811_INT_FIFO_TH    ((uint8_t)( 1 << 1 ))
#define STMPE811_INT_TOUCH_DET  ((uint8_t)( 1 ))
#define STMPE811_INT_ALL        ((uint8_t)( 0xff ))
/** @} */ // INTERUPT_bits

/**
 * @defgroup ADC_CTRL2_register_bits
 * @details ADC control bits for ADC_CTRL register.
 * @{
 */
#define STMPE811_ADC_CTRL2_ADC_FREQ_1_625_MHz   ((uint8_t)( 0 ))
#define STMPE811_ADC_CTRL2_ADC_FREQ_3_25_MHz    ((uint8_t)( 1 ))
#define STMPE811_ADC_CTRL2_ADC_FREQ_6_5_MHz     ((uint8_t)( 2 ))
#define STMPE811_ADC_CTRL2_ADC_FREQ_6_5_MHz_ALT ((uint8_t)( 3 ))
/** @} */ // ADC_CTRL2_bits

/**
 * @defgroup ADC_CTRL1_register_bits
 * @details ADC control bits for ADC_CTRL1 register.
 * @{
 */
#define STMPE811_ADC_CTRL1_SAMPLE_TIME_36        ((uint8_t)( 0 ))
#define STMPE811_ADC_CTRL1_SAMPLE_TIME_44        ((uint8_t)( 1 << 4 ))
#define STMPE811_ADC_CTRL1_SAMPLE_TIME_56        ((uint8_t)( 2 << 4 ))
#define STMPE811_ADC_CTRL1_SAMPLE_TIME_64        ((uint8_t)( 3 << 4 ))
#define STMPE811_ADC_CTRL1_SAMPLE_TIME_80        ((uint8_t)( 4 << 4 ))
#define STMPE811_ADC_CTRL1_SAMPLE_TIME_96        ((uint8_t)( 5 << 4 ))
#define STMPE811_ADC_CTRL1_SAMPLE_TIME_124       ((uint8_t)( 6 << 4 ))
#define STMPE811_ADC_CTRL1_MOD_12B               ((uint8_t)( 1 << 3 ))
#define STMPE811_ADC_CTRL1_REF_SEL_EXTERNAL      ((uint8_t)( 1 << 1 ))
#define STMPE811_ADC_CTRL1_REF_SEL_INTERNAL      ((uint8_t)( 0 ))
/** @} */ // ADC_CTRL1_bits

/**
 * @defgroup TSC_CFG_register_bits
 * @details Touch screen controler configuration bits for TSC_CFG register.
 * @{
 */
#define STMPE811_TSC_CFG_SETTLING_10us          ((uint8_t)( 0 ))
#define STMPE811_TSC_CFG_SETTLING_100us         ((uint8_t)( 1 ))
#define STMPE811_TSC_CFG_SETTLING_500us         ((uint8_t)( 2 ))
#define STMPE811_TSC_CFG_SETTLING_1ms           ((uint8_t)( 3 ))
#define STMPE811_TSC_CFG_SETTLING_5ms           ((uint8_t)( 4 ))
#define STMPE811_TSC_CFG_SETTLING_10ms          ((uint8_t)( 5 ))
#define STMPE811_TSC_CFG_SETTLING_50ms          ((uint8_t)( 6 ))
#define STMPE811_TSC_CFG_SETTLING_100ms         ((uint8_t)( 7 ))
#define STMPE811_TSC_CFG_TOUCH_DET_DELAY_10us   ((uint8_t)( 0 ))
#define STMPE811_TSC_CFG_TOUCH_DET_DELAY_100us  ((uint8_t)( 1 << 3 ))
#define STMPE811_TSC_CFG_TOUCH_DET_DELAY_500us  ((uint8_t)( 2 << 3 ))
#define STMPE811_TSC_CFG_TOUCH_DET_DELAY_1ms    ((uint8_t)( 3 << 3 ))
#define STMPE811_TSC_CFG_TOUCH_DET_DELAY_5ms    ((uint8_t)( 4 << 3 ))
#define STMPE811_TSC_CFG_TOUCH_DET_DELAY_10ms   ((uint8_t)( 5 << 3 ))
#define STMPE811_TSC_CFG_TOUCH_DET_DELAY_50ms   ((uint8_t)( 6 << 3 ))
#define STMPE811_TSC_CFG_TOUCH_DET_DELAY_100ms  ((uint8_t)( 7 << 3 ))
#define STMPE811_TSC_CFG_AVE_CTRL_1_SAMPLE      ((uint8_t)( 0 ))
#define STMPE811_TSC_CFG_AVE_CTRL_2_SAMPLES     ((uint8_t)( 1 << 6 ))
#define STMPE811_TSC_CFG_AVE_CTRL_4_SAMPLES     ((uint8_t)( 2 << 6 ))
#define STMPE811_TSC_CFG_AVE_CTRL_8_SAMPLES     ((uint8_t)( 3 << 6 ))
/** @} */ // TSC_CFG_register_bits

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
} stmpe811_calibration_data_t;

/**
 * @brief Default calibration data specific for MikroE resistive tft boards.
 * @details Data useful for skipping calibration when working with MikroE hardware.
 * Gives reasonable touch precision on any size resitive tft board.
 */
extern const stmpe811_calibration_data_t STMPE811_DEFAULT_CALIBRATION_DATA;

/**
 * @brief STMPE811 Configuration Object.
 * @details Configuration object definition for STMPE811 touch controller.
 */
typedef struct {
    pin_name_t int_pin; /**< Interrupt pin. */

    i2c_master_config_t i2c_cfg; /**< Configuration of communication module. */

    uint16_t width; /**< Touch panel width in pixels. */
    uint16_t height; /**< Touch panel height in pixels. */

    uint8_t addr_sel; /**< I2C slave address of STMPE811. */

    uint8_t press_threshold; /**< Press intensity needed to register touch event. */
} stmpe811_cfg_t;

/**
 * @brief STMPE811 Context Object.
 * @details Context object definition for STMPE811 touch controller.
 * This structure holds information about the current state of the controller.
 * @note Changing values inside this structure is not recomended as it can cause unwanted and incorrect
 * behaviour when used with @ref stmpe811_process function.
 */
typedef struct {
    i2c_master_t i2c; /**< Communication module object. */

    digital_in_t int_pin; /**< Interrupt pin object. */

    tp_event_t press_det; /**< Touch pressure event. */
    tp_touch_item_t touch; /**< Touch item. */
    tp_event_t gesture; /**< Gesture event. */

    bool pen_down; /**< Utility helper variable used for interpreting events. */

    uint16_t width; /**< Touch panel width in pixels. */
    uint16_t height; /**< Touch panel height in pixels. */

    uint8_t press_threshold; /**< Press intensity needed to register touch event. */

    /**< Calibration constants used for converting raw ADC touch data to actual pixel coordinates.*/
    stmpe811_calibration_data_t calibration_data;
} stmpe811_t;

/**
 * @brief STMPE811 configuration object setup function
 * @details This function initializes STMPE811 configuration structure to default values.
 * Interupt pin will be set to unconnected, screen dimenstion will be set to 0,
 * press threshold will be set to 0 and
 * @param[out] cfg STMPE811 configuration object.
 * @retval Nothing.
 */
void stmpe811_cfg_setup( stmpe811_cfg_t * cfg );

/**
 * @brief STMPE811 Initialization Function.
 * @details This function initializes STMPE811 context object using configuration values
 * from STMPE811 configuration object and allows touch panel driver interface object
 * to be linked with STMPE811 driver functions.
 * @note By default, STMPE811 stucture is initialized with calibration constants for
 * MikroE harware, in case of different hardware @ref stmpe811_set_calibration_data is available
 * for seting already determined calibration constants and @ref stmpe811_calibrate is available
 * for determinig new calibraiton constants.
 * @param[in] ctx Initialized STMPE811 context structure. See @ref stmpe811_t for more
 * information about the context structure.
 * @param[in] cfg STMPE811 configuration object. See @ref stmpe811_cfg_t structure
 * definition for detailed explanation.
 * @param[out] drv TP driver interface object. See @ref tp_drv_t structure
 * definition for detailed explanation.
 * @retval @li @c TP_OK OK,
 *         @li @c TP_ERR_INIT_DRV I2C driver init error,
 *         @li @c TP_ERR_UNSUPPORTED_PIN Unsupported pin.
 * See @ref tp_err_t structure definition for detailed explanation.
 */
tp_err_t stmpe811_init( stmpe811_t * ctx, stmpe811_cfg_t * cfg, tp_drv_t * drv );

/**
 * @brief STMPE811 Default Configuration Function.
 * @details Configures the device according to @link http://www.bdtic.com/download/ST/AN2807.pdf
 *      - turns off GPIO and temperature sensor
 *      - sets interrupt on touch detect and fifo threshold
 *      - sets single point reading mode
 *      - sets settling time to 500us, touch delay to 500us and 12 bit ADC mode
 *      - configures coordinate mode to X, Y and Z mode
 * @param[in] ctx Initialized STMPE811 context structure. See @ref stmpe811_t for more
 * information about the context structure.
 * @retval Nothing.
 */
void stmpe811_default_cfg( stmpe811_t* ctx );

/**
 * @brief Copies touch information from context object to touch item object
 * @details This function is necessary for interfacing with touch panel library as it's
 * address is stored in tp_drv_t driver structure during the STMPE811 context initialization.
 * @param[in] ctx Initialized STMPE811 context structure. See @ref stmpe811_t for more
 * information about the context structure.
 * @param[out] touch_item
 * @retval Nothing.
 */
void stmpe811_press_coordinates( stmpe811_t* ctx, tp_touch_item_t * touch_item );

/**
 * @brief Press detection function.
 * @details Retrives information about press detection from STMPE811.
 * @note This function is necessary for interfacing with touch panel library as it's
 * address is stored in tp_drv_t driver structure during the STMPE811 context initialization.
 * @param[in] ctx Initialized STMPE811 context structure. See @ref stmpe811_t for more
 * information about the context structure.
 * @retval @li @c TP_EVENT_PRESS_NOT_DET - Touch pressure is not detected.
 *         @li @c TP_EVENT_PRESS_DET - Touch pressure is detected.
 * See @ref tp_err_t structure definition for detailed explanation.
 */
tp_event_t stmpe811_press_detect( stmpe811_t* ctx );

/**
 * @brief Function processing events.
 * @details This function check if touch was detected and if it was reads
 * and stores touch information in context structure and checks if it's touch down, up or move.
 * @note This function is necessary for interfacing with touch panel library as it's
 * address is stored in tp_drv_t driver structure during the STMPE811 context initialization.
 * @note Function needs STMPE811 to be configured to trigger interupt on touch det since it relies on polling
 * the interrupt pin.
 * @param[in] ctx Initialized STMPE811 context structure. See @ref stmpe811_t for more
 * information about the context structure.
 * @retval Always returns TP_OK. see @ref tp_err_t for more details.
 */
tp_err_t stmpe811_process( stmpe811_t * ctx );

/**
 * @brief Read gesture information.
 * @details Since STMPE811 does not support gestures this function is purely for interfacing
 * with the tp library. Gesture returned from the function is always no gesture.
 * @param[in] ctx Initialized STMPE811 context structure. See @ref stmpe811_t for more
 * information about the context structure.
 * @note This function is necessary for interfacing with touch panel library as it's
 * address is stored in tp_drv_t driver structure during the STMPE811 context initialization.
 * @param[out] event Touch panel gesture data, always TP_EVENT_GEST_NONE. See @ref tp_event_t * definition
 * for detailed explanation.
 * @retval Nothing.
 */
void stmpe811_gesture( stmpe811_t* ctx, tp_event_t * event );

/**
 * @brief Reads a single byte from a register.
 * @details This function provides easy single byte read to a STMPE811 register since
 * most of the registers are only 1 byte in size.
 * @param[in] ctx Initialized STMPE811 context structure. See @ref stmpe811_t for more
 * information about the context structure.
 * @param[in] reg_addr Register address from which single byte will be read.
 * See @ref stmpe811_reg_addr_t for more information about register addresses.
 * @retval Register value.
 */
uint8_t stmpe811_generic_read_byte( stmpe811_t * ctx, uint8_t reg_addr );

/**
 * @brief Writes a single byte to a register.
 * @details This function provides easy single byte write to a STMPE811 register since
 * most of the registers are only 1 byte in size.
 * @param[in] ctx Initialized STMPE811 context structure. See @ref stmpe811_t for more
 * information about the context structure.
 * @param[in] reg_addr_addr Register address where single byte will be written.
 * See @ref stmpe811_reg_addr_t for more information about register addresses.
 * @param[in] value Value that will be written to register address.
 * @retval Nothing.
 */
void stmpe811_generic_write_byte( stmpe811_t * ctx, uint8_t reg_addr, uint8_t val );

/**
 * @brief Reads desired number of bytes from register to a buffer.
 * @details This function provides ability to read desired nubmer of bytes
 * from a STMPE811 register. Useful for the small amout of registers that are larger
 * than one byte in size, such as TSC_DATA_XYZ and windowing parameters registers.
 * @param[in] ctx Initialized STMPE811 context structure. See @ref stmpe811_t for more
 * information about the context structure.
 * @param[in] reg_addr Register address from where reading will start.
 * @param[out] buff Buffer where read data will be stored.
 * @param[in] len Length of data to be read.
 * @retval Nothing.
 */
void stmpe811_generic_read( stmpe811_t * ctx, uint8_t reg_addr, uint8_t * buff, uint8_t len );

/**
 * @brief Writes desired number of bytes from buffer to a register.
 * @details This function provides ability to read desired nubmer of bytes
 * to a STMPE811 register. Useful for the small amout of registers that are larger
 * than one byte in size, such as TSC_DATA_XYZ and windowing parameters registers.
 * @param[in] ctx Initialized STMPE811 context structure. See @ref stmpe811_t for more
 * information about the context structure.
 * @param[in] reg_addr Register address from where writing will start.
 * @param[in] buff Data that will be written to register address.
 * @param[in] len Length of data to be written.
 * @retval Nothing.
 */
void stmpe811_generic_write( stmpe811_t * ctx, uint8_t reg_addr, uint8_t * buff, uint8_t len );

/**
 * @brief Calibrates variables used for converting raw stmpe811 ADC values to pixel coordinates
 * @details Function nees the user to touch all four corners as close to the edges as possible
 * to find the extreme values. Function also supports holding a pen and moving it across the screen and
 * will use the most extreme coordinates found during that move as corner coordinates, so touching
 * a screen and draging a finger over the one of the four edges unitl touch is no longer detected
 * will give pretty good calibration data.
 * @param[in] ctx Initialized STMPE811 context structure. See @ref stmpe811_t for more
 * information about the context structure.
 * @retval Nothing.
 */
void stmpe811_calibrate( stmpe811_t* ctx );

/**
 * @brief Reads x & y coordinate values to x, y, z addresses.
 * @details Reads coordinate date and converts x and y to appropriate pixel coordinates then clears the
 * FIFO coordinate memory.
 * @param[in] ctx Initialized STMPE811 context structure. See @ref stmpe811_t for more
 * @note STMPE811 should be configured for x,y,z operation mode in order to read all values.
 * @param[out] x Pointer to memory where pixel x coordinate will be stored.
 * @param[out] y Pointer to memory where pixel y coordinate will be stored.
 * @param[out] z Pointer to memory where z value will be stored.
 * @retval Nothing.
 */
void stmpe811_read_xyz( stmpe811_t * ctx, uint16_t* x, uint16_t* y, uint16_t* z );

/**
 * @brief Utility funciton used for calibration.
 * @details reads raw adc values of x,y and z without mapping them to screen coordinates then clears
 * the FIFO coordinate memory.
 * @param[in] ctx Initialized STMPE811 context structure. See @ref stmpe811_t for more
 * @param[out] x Pointer to memory where raw x coordinate will be stored.
 * @param[out] y Pointer to memory where raw y coordinate will be stored.
 * @param[out] z Pointer to memory where z value will be stored.
 * @retval Nothing.
 */
void stmpe811_read_xyz_raw( stmpe811_t * ctx, uint16_t* x, uint16_t* y, uint16_t* z );

/**
 * @brief Utility funciton used for getting a copy of current calibration data.
 * @details Function copies data that's being e used for converting raw ADC values
 * to actual pixel coordinates.
 * @param[in] ctx Initialized STMPE811 context structure. See @ref stmpe811_t for more
 * @param[out] cdata Pointer to memory where calibration data will be stored.
 */
void stmpe811_get_calibration_data( stmpe811_t * ctx, stmpe811_calibration_data_t * cdata );

/**
 * @brief Utility funciton used for setting calibration data.
 * @details Function copies data stored in @p data. That information will be be used for
 * converting raw ADC values to actual pixel coordinates.
 * @param[in] ctx Initialized STMPE811 context structure. See @ref stmpe811_t for more
 * @param[out] cdata Pointer to memory from where new calibration will be copied and set.
 */
void stmpe811_set_calibration_data( stmpe811_t * ctx, const stmpe811_calibration_data_t * cdata );

/*! @} */ // middlewaregroup
/*! @} */ // stmpe811

#ifdef __cplusplus
}
#endif

#endif // _STMPE811_H_

// ------------------------------------------------------------------------ END
