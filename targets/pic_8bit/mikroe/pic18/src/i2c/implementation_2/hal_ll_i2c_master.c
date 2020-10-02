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
 * @file  hal_ll_i2c_master.c
 * @brief I2C master HAL LOW LEVEL layer implementation.
 */

#include "hal_ll_pps.h"
#include "hal_ll_gpio.h"
#include "hal_ll_odcon_map.h"
#include "hal_ll_i2c_master.h"
#include "hal_ll_i2c_pin_map.h"

/*!< @brief Local handle list */
static volatile hal_ll_i2c_master_handle_register_t hal_ll_module_state[I2C_MODULE_COUNT] = { (handle_t *)NULL, false };

// ------------------------------------------------------------- PRIVATE MACROS
/*!< @brief Helper macro for getting hal_ll_module_state address */
#define hal_ll_i2c_get_module_state_address ((hal_ll_i2c_master_handle_register_t *)*handle)
/*!< @brief Helper macro for getting module specific control register structure base address // first register address */
#define hal_ll_i2c_get_handle (hal_ll_i2c_master_handle_register_t *)hal_ll_i2c_get_module_state_address->hal_ll_i2c_master_handle
/*!< @brief Helper macro for getting module specific control register structure */
#define hal_ll_i2c_get_base_struct(_handle) ((const hal_ll_i2c_base_handle_t *)_handle)
/*!< @brief Helper macro for getting module specific base address directly from HAL layer handle */
#define hal_ll_i2c_get_base_from_hal_handle ((hal_ll_i2c_hw_specifics_map_t *)((hal_ll_i2c_master_handle_register_t *)\
                                            (((hal_ll_i2c_master_handle_register_t *)(handle))->hal_ll_i2c_master_handle))->hal_ll_i2c_master_handle)->base

/*!< @brief Macros used for pin/port manipulation */
#define pin_mask 0x0F
#define port_mask 0xF0
#define hal_ll_pin(port_name) (port_name & pin_mask)
#define hal_ll_port(port_name) ((port_name & port_mask) >> 4)

/*!< @brief Default I2C bit-rate if no speed is set */
#define HAL_LL_I2C_MASTER_SPEED_100K 100000UL

/*!< @brief Macros defining register addresses and masks */
#define HAL_LL_I2C_MASTER_MFINTOSC_CLK_SOURCE 0x3
#define HAL_LL_I2C_MASTER_CLEAR_CONDITION_BITS_MASK ((1U << HAL_LL_I2C_MASTER_PCIE_BIT) | \
                                                    (1U << HAL_LL_I2C_MASTER_RSCIE_BIT) | \
                                                    (1U << HAL_LL_I2C_MASTER_SCIE_BIT))
#define HAL_LL_I2C_MASTER_START_RESTART_BITS_MASK   ((1U << HAL_LL_I2C_MASTER_RSCIE_BIT) | \
                                                    (1U << HAL_LL_I2C_MASTER_SCIE_BIT))

/*!< @brief Macros defining register bit location */
#define HAL_LL_I2C1_MODULE_BIT 0
#define HAL_LL_I2C2_MODULE_BIT 1
#define HAL_LL_OSCEN_MFOEN_BIT 5
#define HAL_LL_OSCSTAT_MFOR_BIT 5
#define HAL_LL_I2C_MASTER_MODE_BIT 2
#define HAL_LL_I2C_MASTER_ACKCNT_BIT 7
#define HAL_LL_I2C_MASTER_PCIE_BIT 2
#define HAL_LL_I2C_MASTER_RSCIE_BIT 1
#define HAL_LL_I2C_MASTER_SCIE_BIT 0
#define HAL_LL_I2C_MASTER_MODULE_ENABLE_BIT 7
#define HAL_LL_I2C_MASTER_MDR_BIT 3
#define HAL_LL_I2C_MASTER_START_BIT 5
#define HAL_LL_I2C_MASTER_RSEN_BIT 6
#define HAL_LL_I2C_MASTER_TXBE_BIT 5
#define HAL_LL_I2C_MASTER_RXBF_BIT 0
#define HAL_LL_I2C_MASTER_STOP_FLAG_BIT 2
#define HAL_LL_I2C_MASTER_BFRE_BIT 7

/*!< @brief Default pass count value upon reset */
#define HAL_LL_I2C_DEFAULT_PASS_COUNT 10000

/*!< @brief Macros used for module pin checking */
#define HAL_LL_I2C_SCL_PIN 0
#define HAL_LL_I2C_SDA_PIN 1
#define HAL_LL_I2C_MODULE_PIN_COUNT 2

// -------------------------------------------------------------- PRIVATE TYPES
/*!< @brief I2C register structure */
typedef struct
{
    hal_ll_base_addr_t i2c_con0_reg_addr;
    hal_ll_base_addr_t i2c_con1_reg_addr;
    hal_ll_base_addr_t i2c_con2_reg_addr;
    hal_ll_base_addr_t i2c_clk_reg_addr;
    hal_ll_base_addr_t i2c_pie_reg_addr;
    hal_ll_base_addr_t i2c_pir_reg_addr;
    hal_ll_base_addr_t i2c_stat0_reg_addr;
    hal_ll_base_addr_t i2c_stat1_reg_addr;
    hal_ll_base_addr_t i2c_cnt_reg_addr;
    hal_ll_base_addr_t i2c_adb1_reg_addr;
    hal_ll_base_addr_t i2c_rxb_reg_addr;
    hal_ll_base_addr_t i2c_txb_reg_addr;
} hal_ll_i2c_base_handle_t;

/*!< @brief I2C hw specific structure */
typedef struct
{
    const hal_ll_i2c_base_handle_t *base;
    hal_ll_pin_name_t module_index;
    hal_ll_i2c_pins_t pins;
    uint32_t speed;
    uint8_t address;
    uint16_t timeout;
} hal_ll_i2c_hw_specifics_map_t;

/*!< @brief I2C hw specific error values */
typedef enum
{
    HAL_LL_I2C_MASTER_SUCCESS = 0,
    HAL_LL_I2C_MASTER_WRONG_PINS,
    HAL_LL_I2C_MASTER_MODULE_ERROR,

    HAL_LL_I2C_MASTER_ERROR = (-1)
} hal_ll_i2c_master_err_t;

/*!< @brief I2C end mode selection values */
typedef enum
{
    HAL_LL_I2C_MASTER_END_MODE_RESTART = 0,
    HAL_LL_I2C_MASTER_END_MODE_STOP,
    HAL_LL_I2C_MASTER_WRITE_THEN_READ
} hal_ll_i2c_master_end_mode_t;

/*!< @brief I2C timeout error values */
typedef enum
{
    HAL_LL_I2C_MASTER_TIMEOUT_START = 1300,
    HAL_LL_I2C_MASTER_TIMEOUT_STOP,
    HAL_LL_I2C_MASTER_TIMEOUT_WRITE,
    HAL_LL_I2C_MASTER_TIMEOUT_READ,
    HAL_LL_I2C_MASTER_ARBITRATION_LOST,
    HAL_LL_I2C_MASTER_TIMEOUT_INIT,
    HAL_LL_I2C_MASTER_TIMEOUT_WAIT_IDLE
} hal_ll_i2c_master_timeout_t;

/**
 * @brief Enum containing predefined module standard speed values.
 *
 * Enum values:
 * HAL_LL_I2C_MASTER_SPEED_STANDARD -- Speed set at 100K
 */
typedef enum
{
    /* TODO - Add support for additional bit-rate values
     * Only 100K is implemented at the moment.
     */
    HAL_LL_I2C_MASTER_SPEED_STANDARD = 0
} hal_ll_i2c_master_speed_t;

// ------------------------------------------------------------------ CONSTANTS
/*!< @brief I2C registers array */
static const hal_ll_i2c_base_handle_t hal_ll_i2c_hw_regs[ I2C_MODULE_COUNT + 1 ] =
{
    #ifdef I2C_MODULE
    { HAL_LL_I2C1CON0_ADDRESS, HAL_LL_I2C1CON1_ADDRESS, HAL_LL_I2C1CON2_ADDRESS, HAL_LL_I2C1CLK_ADDRESS, HAL_LL_I2C1PIE_ADDRESS, HAL_LL_I2C1PIR_ADDRESS, HAL_LL_I2C1STAT0_ADDRESS, HAL_LL_I2C1STAT1_ADDRESS, HAL_LL_I2C1CNT_ADDRESS, HAL_LL_I2C1ADB1_ADDRESS, HAL_LL_I2C1RXB_ADDRESS, HAL_LL_I2C1TXB_ADDRESS },
    #endif
    #ifdef I2C_MODULE_1
    { HAL_LL_I2C1CON0_ADDRESS, HAL_LL_I2C1CON1_ADDRESS, HAL_LL_I2C1CON2_ADDRESS, HAL_LL_I2C1CLK_ADDRESS, HAL_LL_I2C1PIE_ADDRESS, HAL_LL_I2C1PIR_ADDRESS, HAL_LL_I2C1STAT0_ADDRESS, HAL_LL_I2C1STAT1_ADDRESS, HAL_LL_I2C1CNT_ADDRESS, HAL_LL_I2C1ADB1_ADDRESS, HAL_LL_I2C1RXB_ADDRESS, HAL_LL_I2C1TXB_ADDRESS },
    #endif
    #ifdef I2C_MODULE_2
    { HAL_LL_I2C2CON0_ADDRESS, HAL_LL_I2C2CON1_ADDRESS, HAL_LL_I2C2CON2_ADDRESS, HAL_LL_I2C2CLK_ADDRESS, HAL_LL_I2C2PIE_ADDRESS, HAL_LL_I2C2PIR_ADDRESS, HAL_LL_I2C2STAT0_ADDRESS, HAL_LL_I2C2STAT1_ADDRESS, HAL_LL_I2C2CNT_ADDRESS, HAL_LL_I2C2ADB1_ADDRESS, HAL_LL_I2C2RXB_ADDRESS, HAL_LL_I2C2TXB_ADDRESS },
    #endif

    { HAL_LL_MODULE_ERROR, HAL_LL_MODULE_ERROR, HAL_LL_MODULE_ERROR, HAL_LL_MODULE_ERROR, HAL_LL_MODULE_ERROR, HAL_LL_MODULE_ERROR, HAL_LL_MODULE_ERROR, HAL_LL_MODULE_ERROR, HAL_LL_MODULE_ERROR, HAL_LL_MODULE_ERROR, HAL_LL_MODULE_ERROR, HAL_LL_MODULE_ERROR }
};

// ------------------------------------------------------------------ VARIABLES
/*!< @brief I2C hardware specific info */
static hal_ll_i2c_hw_specifics_map_t hal_ll_i2c_hw_specifics_map[ I2C_MODULE_COUNT + 1 ] =
{
    #ifdef I2C_MODULE
    {&hal_ll_i2c_hw_regs[hal_ll_i2c_module_num(I2C_MODULE)], hal_ll_i2c_module_num(I2C_MODULE), {HAL_LL_PIN_NC,0,HAL_LL_PIN_NC,0}, HAL_LL_I2C_MASTER_SPEED_100K, 0, HAL_LL_I2C_DEFAULT_PASS_COUNT},
    #endif
    #ifdef I2C_MODULE_1
    {&hal_ll_i2c_hw_regs[hal_ll_i2c_module_num(I2C_MODULE_1)], hal_ll_i2c_module_num(I2C_MODULE_1), {HAL_LL_PIN_NC,0,HAL_LL_PIN_NC,0}, HAL_LL_I2C_MASTER_SPEED_100K, 0, HAL_LL_I2C_DEFAULT_PASS_COUNT},
    #endif
    #ifdef I2C_MODULE_2
    {&hal_ll_i2c_hw_regs[hal_ll_i2c_module_num(I2C_MODULE_2)], hal_ll_i2c_module_num(I2C_MODULE_2), {HAL_LL_PIN_NC,0,HAL_LL_PIN_NC,0}, HAL_LL_I2C_MASTER_SPEED_100K, 0, HAL_LL_I2C_DEFAULT_PASS_COUNT},
    #endif

    {&hal_ll_i2c_hw_regs[I2C_MODULE_COUNT], HAL_LL_MODULE_ERROR, {HAL_LL_PIN_NC,0,HAL_LL_PIN_NC,0}, 0, 0, 0}
};

/*!< @brief Global handle variables used in functions */
static volatile hal_ll_i2c_master_handle_register_t *low_level_handle;
static volatile hal_ll_i2c_hw_specifics_map_t *hal_ll_i2c_hw_specifics_map_local;

// ---------------------------------------------- PRIVATE FUNCTION DECLARATIONS
/**
  * @brief  Check if pins are adequate.
  *
  * Checks scl and sda pins the user has passed with pre-defined
  * pins in scl and sda maps. Take into consideration that module
  * index numbers have to be the same for both pins.
  *
  * @param[in]  scl - SCL pre-defined pin name.
  * @param[in]  sda - SDA pre-defined pin name.
  * @param[in]  *index_list - Array with SCL and SDA map index values
  *
  * @return hal_ll_pin_name_t Module index based on pins.
  *
  * Returns pre-defined module index from pin maps, if pins
  * are adequate.
  */
static hal_ll_pin_name_t hal_ll_i2c_master_check_pins( hal_ll_pin_name_t scl, hal_ll_pin_name_t sda, uint8_t *index_list );

/**
  * @brief  Get local hardware specific map.
  *
  * Checks handle value and returns address of adequate
  * hal_ll_i2c_hw_specifics_map array index.
  *
  * @param[in]  handle - Object specific context handler.
  *
  * @return hal_ll_i2c_hw_specifics_map_t Map address.
  *
  * Returns pre-defined map index address based on handle value,
  * if handle is adequate.
  */
static hal_ll_i2c_hw_specifics_map_t *hal_ll_get_specifics( handle_t handle );

/**
  * @brief  Get I2C busy bit value.
  *
  * Checks I2C busy bit value and returns true if device is in operation.
  * Else returns false.
  *
  * @param[in]  hal_ll_hw_reg - Object specific context handler.
  *
  * @return bool State of register busy bit.
  */
static bool hal_ll_i2c_master_is_idle( const hal_ll_i2c_base_handle_t *hal_ll_hw_reg );

/**
  * @brief  Get adequate I2C bit-rate value.
  *
  * Returns one of pre-defined bit-rate values,
  * or the closest bit-rate based on bit_rate
  * value passed to the function.
  *
  * @param[in]  bit_rate - I2C bit rate.
  *
  * @return uint32_t Adequate bit-rate value.
  *
  * Returns adequate value to be latter written into bare metal register address.
  * Take into consideration that this returns a predefined value.
  *
  * HAL_LL_I2C_MASTER_SPEED_100K -- 100Kbit/s
  */
static uint32_t hal_ll_i2c_get_speed( uint32_t bit_rate );

/**
  * @brief  Sets module power state.
  *
  * Enables/Disables I2C peripheral module on hardware level, based on beforehand
  * set configuration and module handler.
  *
  * @param[in]  map - Object specific context handler.
  * @param[in]  hal_ll_state - True(enable clock)/False(disable clock).
  *
  * @return None
  */
static void hal_ll_i2c_master_set_module_power( hal_ll_i2c_hw_specifics_map_t *map, bool hal_ll_state );

/**
 * @brief  Sets ODCONx state.
 *
 * Sets adequate ODCONx register state.
 * I2C pins open drain setting.
 *
 * @param[in]  map - Object specific context handler.
 *
 * @return  None.
 */
static void hal_ll_i2c_hw_odcon_set( map );

/**
 * @brief  Maps new-found module specific values.
 *
 * Maps pin names and alternate function values for
 * I2C SCL and SDA pins.
 *
 * @param[in]  module_index I2C HW module index -- 0,1,2...
 * @param[in]  *index_list  Array with SCL and SDA map index values
 *
 * @return  None
 */
static void hal_ll_i2c_master_map_pins( uint8_t module_index, uint8_t *index_list );

/**
  * @brief  Initialize I2C module on hardware level.
  *
  * Initializes I2C module on hardware level, based on beforehand
  * set configuration and module handler.
  *
  * @param[in]  map - Object specific context handler.
  *
  * @return hal_ll_err_t Module specific values.
  *
  * Returns one of pre-defined values.
  * Take into consideration that this is hardware specific.
  */
static hal_ll_err_t hal_ll_i2c_hw_init( hal_ll_i2c_hw_specifics_map_t *map );

/**
 * @brief  Set PPS state.
 *
 * Sets adequate RPINRx and RPORx register
 * values for adequate functionality.
 * Also, sets TRISx register bit appropriately.
 *
 * @param[in]  map - Object specific context handler.
 * @param[in]  hal_ll_state - init or deinit
 *
 * @return  hal_ll_pps_err_t PPS specific value.
 * HAL_LL_PPS_SUCCESS  -- OK
 * HAL_LL_PPS_DIRECTION_ERROR -- Direction not set
 * HAL_LL_PPS_PIN_ERROR -- Wrong pin
 * HAL_LL_PPS_MODULE_ERROR -- General error
 *
 * @note PIC specific.
 */
static hal_ll_pps_err_t hal_ll_pps_set_state( hal_ll_i2c_hw_specifics_map_t *map, bool hal_ll_state );

/**
  * @brief  Full I2C module initialization procedure.
  *
  * Initializes I2C module on hardware level, based on beforehand
  * set configuration and module handler. Sets adequate pin alternate functions.
  * Initializes module clock.
  *
  * @param[in]  map - Object specific context handler.
  *
  * @return hal_ll_err_t Module specific values.
  *
  * Returns one of pre-defined values.
  * Take into consideration that this is hardware specific.
  */
static hal_ll_err_t hal_ll_i2c_init( hal_ll_i2c_hw_specifics_map_t *map );

/**
  * @brief  Generates start signal on I2C bus.
  *
  * Generates a start signal on the I2C bus.
  *
  * @param[in]  map - Object specific context handler.
  *
  * @return hal_ll_err_t Module specific values.
  *
  * Returns one of pre-defined values.
  * Take into consideration that this is hardware specific.
  */
static hal_ll_err_t hal_ll_i2c_master_start( hal_ll_i2c_hw_specifics_map_t *map );

/**
  * @brief  Generates restart signal on I2C bus.
  *
  * Generates a restart signal on the I2C bus.
  *
  * @param[in]  map - Object specific context handler.
  *
  * @return hal_ll_err_t Module specific values.
  *
  * Returns one of pre-defined values.
  * Take into consideration that this is hardware specific.
  */
static void hal_ll_i2c_master_restart( const hal_ll_i2c_base_handle_t *hal_ll_hw_reg );

/**
  * @brief  Generates stop signal on I2C bus.
  *
  * Generates a stop signal on the I2C bus.
  *
  * @param[in]  map - Object specific context handler.
  *
  * @return hal_ll_err_t Module specific values.
  *
  * Returns one of pre-defined values.
  * Take into consideration that this is hardware specific.
  */
static void hal_ll_i2c_master_stop( const hal_ll_i2c_base_handle_t *hal_ll_hw_reg );

/**
  * @brief  Perform a read on the I2C bus.
  *
  * Initializes I2C module on hardware level, if not initialized beforehand
  * and continues to perform a read operation on the bus.
  *
  * @param[in]  map - Object specific context handler.
  * @param[in]  read_data_buf - Pointer to data buffer.
  * @param[in]  len_read_data - Number of data to be read.
  *
  * @return hal_ll_err_t Module specific values.
  *
  * Returns one of pre-defined values.
  * Take into consideration that this is hardware specific.
  */
static hal_ll_err_t hal_ll_i2c_master_read_bare_metal( hal_ll_i2c_hw_specifics_map_t *map, uint8_t *read_data_buf, size_t len_read_data, hal_ll_i2c_master_end_mode_t mode );

/**
  * @brief  Perform a write on the I2C bus.
  *
  * Initializes I2C module on hardware level, if not initialized beforehand
  * and continues to perform a write operation on the bus.
  *
  * @param[in]  map - Object specific context handler.
  * @param[in]  write_data_buf - Pointer to data buffer.
  * @param[in]  len_write_data - Number of data to be written.
  *
  * @return hal_ll_err_t Module specific values.
  *
  * Returns one of pre-defined values.
  * Take into consideration that this is hardware specific.
  */
static hal_ll_err_t hal_ll_i2c_master_write_bare_metal( hal_ll_i2c_hw_specifics_map_t *map, uint8_t *write_data_buf, size_t len_write_data, hal_ll_i2c_master_end_mode_t mode );

// ------------------------------------------------ PUBLIC FUNCTION DEFINITIONS
hal_ll_err_t hal_ll_i2c_master_register_handle( hal_ll_pin_name_t scl, hal_ll_pin_name_t sda, hal_ll_i2c_master_handle_register_t *handle_map, uint8_t *hal_module_id ) {
    uint8_t hal_ll_module_state_count = sizeof(hal_ll_module_state) / (sizeof(hal_ll_i2c_master_handle_register_t));
    uint8_t index_list[HAL_LL_I2C_MODULE_PIN_COUNT];
    uint8_t pin_check_result;

    if ( (pin_check_result = hal_ll_i2c_master_check_pins( scl, sda, &index_list )) == HAL_LL_PIN_NC ) {
        return HAL_LL_I2C_MASTER_WRONG_PINS;
    };

    if ( (hal_ll_i2c_hw_specifics_map[pin_check_result]->pins.pin_scl.pin_name != scl) ||
         (hal_ll_i2c_hw_specifics_map[pin_check_result]->pins.pin_sda.pin_name != sda) )
    {
        // Used only for chips which have I2C PPS pins
        #if HAL_LL_I2C_PPS_ENABLED == true
        if ( hal_ll_pps_set_state( &hal_ll_i2c_hw_specifics_map[ pin_check_result ], false ) != HAL_LL_I2C_MASTER_SUCCESS )
            return HAL_LL_I2C_MASTER_WRONG_PINS;
        #endif

        hal_ll_i2c_master_map_pins( pin_check_result, &index_list );

        // Used only for chips which have I2C PPS pins
        #if HAL_LL_I2C_PPS_ENABLED == true
        if ( hal_ll_pps_set_state( &hal_ll_i2c_hw_specifics_map[ pin_check_result ], true ) != HAL_LL_I2C_MASTER_SUCCESS )
            return HAL_LL_I2C_MASTER_WRONG_PINS;
        #endif

        handle_map[pin_check_result]->init_ll_state = false;
    }

    *hal_module_id = pin_check_result;

    hal_ll_module_state[pin_check_result]->hal_ll_i2c_master_handle = (handle_t *)&hal_ll_i2c_hw_specifics_map[pin_check_result]->base;

    handle_map[pin_check_result]->hal_ll_i2c_master_handle = (handle_t *)&hal_ll_module_state[pin_check_result]->hal_ll_i2c_master_handle;

    return HAL_LL_I2C_MASTER_SUCCESS;
}

hal_ll_err_t hal_ll_module_configure_i2c( handle_t *handle ) {
    hal_ll_i2c_hw_specifics_map_local = hal_ll_get_specifics(hal_ll_i2c_get_module_state_address);
    uint8_t index_list[HAL_LL_I2C_MODULE_PIN_COUNT];
    uint8_t pin_check_result;

    if ( (pin_check_result = hal_ll_i2c_master_check_pins( hal_ll_i2c_hw_specifics_map_local->pins.pin_scl.pin_name,
                                                           hal_ll_i2c_hw_specifics_map_local->pins.pin_sda.pin_name, &index_list ) ) == HAL_LL_PIN_NC )
    {
        return HAL_LL_I2C_MASTER_WRONG_PINS;
    };

    hal_ll_i2c_init( hal_ll_i2c_hw_specifics_map_local );

    hal_ll_module_state[pin_check_result]->hal_ll_i2c_master_handle = (handle_t *)&hal_ll_i2c_hw_specifics_map[pin_check_result]->base;
    hal_ll_module_state[pin_check_result]->init_ll_state = true;

    return HAL_LL_I2C_MASTER_SUCCESS;
}

hal_ll_err_t hal_ll_i2c_master_set_speed( handle_t *handle, uint32_t speed ) {
    low_level_handle = hal_ll_i2c_get_handle;
    hal_ll_i2c_hw_specifics_map_local = hal_ll_get_specifics(hal_ll_i2c_get_module_state_address);

    if( low_level_handle->hal_ll_i2c_master_handle == NULL ) {
        return HAL_LL_I2C_MASTER_MODULE_ERROR;
    }

    low_level_handle->init_ll_state = false;

    hal_ll_i2c_hw_specifics_map_local->speed = hal_ll_i2c_get_speed( speed );

    hal_ll_i2c_init( hal_ll_i2c_hw_specifics_map_local );

    low_level_handle->init_ll_state = true;

    return hal_ll_i2c_hw_specifics_map_local->speed;
}

void hal_ll_i2c_master_set_timeout( handle_t *handle, uint16_t timeout ) {
    low_level_handle = hal_ll_i2c_get_handle;
    hal_ll_i2c_hw_specifics_map_local = hal_ll_get_specifics(hal_ll_i2c_get_module_state_address);

    if( low_level_handle->hal_ll_i2c_master_handle != NULL ) {
        hal_ll_i2c_hw_specifics_map_local->timeout = timeout;
    }
}

void hal_ll_i2c_master_set_slave_address( handle_t *handle, uint8_t addr ) {
    low_level_handle = hal_ll_i2c_get_handle;
    hal_ll_i2c_hw_specifics_map_local = hal_ll_get_specifics(hal_ll_i2c_get_module_state_address);

    if( low_level_handle->hal_ll_i2c_master_handle != NULL ) {
        hal_ll_i2c_hw_specifics_map_local->address = addr;
    }
}

hal_ll_err_t hal_ll_i2c_master_read( handle_t *handle, uint8_t *read_data_buf, size_t len_read_data ) {
    low_level_handle = hal_ll_i2c_get_handle;
    hal_ll_i2c_hw_specifics_map_local = hal_ll_get_specifics(hal_ll_i2c_get_module_state_address);

    if( low_level_handle->hal_ll_i2c_master_handle == NULL ) {
        return HAL_LL_I2C_MASTER_MODULE_ERROR;
    }

    return hal_ll_i2c_master_read_bare_metal( hal_ll_i2c_hw_specifics_map_local, read_data_buf, len_read_data, HAL_LL_I2C_MASTER_END_MODE_STOP );
}

hal_ll_err_t hal_ll_i2c_master_write( handle_t *handle, uint8_t *write_data_buf, size_t len_write_data ) {
    low_level_handle = hal_ll_i2c_get_handle;
    hal_ll_i2c_hw_specifics_map_local = hal_ll_get_specifics(hal_ll_i2c_get_module_state_address);

    if( low_level_handle->hal_ll_i2c_master_handle == NULL ) {
        return HAL_LL_I2C_MASTER_MODULE_ERROR;
    }

    return hal_ll_i2c_master_write_bare_metal( hal_ll_i2c_hw_specifics_map_local, write_data_buf, len_write_data, HAL_LL_I2C_MASTER_END_MODE_STOP );
}

hal_ll_err_t hal_ll_i2c_master_write_then_read( handle_t *handle, uint8_t *write_data_buf, size_t len_write_data, uint8_t *read_data_buf, size_t len_read_data ) {
    low_level_handle = hal_ll_i2c_get_handle;
    hal_ll_i2c_hw_specifics_map_local = hal_ll_get_specifics(hal_ll_i2c_get_module_state_address);

    if( low_level_handle->hal_ll_i2c_master_handle == NULL ) {
        return HAL_LL_I2C_MASTER_MODULE_ERROR;
    }

    if( hal_ll_i2c_master_write_bare_metal( hal_ll_i2c_hw_specifics_map_local, write_data_buf, len_write_data, HAL_LL_I2C_MASTER_WRITE_THEN_READ ) != HAL_LL_I2C_MASTER_SUCCESS ) {
        return HAL_LL_I2C_MASTER_TIMEOUT_WRITE;
    }

    if( hal_ll_i2c_master_read_bare_metal( hal_ll_i2c_hw_specifics_map_local, read_data_buf, len_read_data, HAL_LL_I2C_MASTER_WRITE_THEN_READ ) != HAL_LL_I2C_MASTER_SUCCESS ) {
        return HAL_LL_I2C_MASTER_TIMEOUT_READ;
    }

    return HAL_LL_I2C_MASTER_SUCCESS;
}

void hal_ll_i2c_master_close( handle_t *handle ) {
    low_level_handle = hal_ll_i2c_get_handle;
    hal_ll_i2c_hw_specifics_map_local = hal_ll_get_specifics(hal_ll_i2c_get_module_state_address);

    if( low_level_handle->hal_ll_i2c_master_handle != NULL ) {
        // Used only for chips which have I2C PPS pins
        #if HAL_LL_I2C_PPS_ENABLED == true
        hal_ll_pps_set_state(hal_ll_i2c_hw_specifics_map_local, false);
        #endif

        low_level_handle->hal_ll_i2c_master_handle = NULL;
        low_level_handle->init_ll_state = false;

        hal_ll_i2c_hw_specifics_map_local->address = 0;
        hal_ll_i2c_hw_specifics_map_local->timeout = HAL_LL_I2C_DEFAULT_PASS_COUNT;
        hal_ll_i2c_hw_specifics_map_local->speed = HAL_LL_I2C_MASTER_SPEED_100K;

        hal_ll_i2c_master_set_module_power(hal_ll_i2c_hw_specifics_map_local, false);

        hal_ll_pps_set_state(hal_ll_i2c_hw_specifics_map_local, false);

        hal_ll_i2c_hw_specifics_map_local->pins->pin_scl.pin_name = HAL_LL_PIN_NC;
        hal_ll_i2c_hw_specifics_map_local->pins->pin_sda.pin_name = HAL_LL_PIN_NC;
        hal_ll_i2c_hw_specifics_map_local->pins->pin_scl.pin_pps = 0;
        hal_ll_i2c_hw_specifics_map_local->pins->pin_sda.pin_pps = 0;
    }
}

// ----------------------------------------------- PRIVATE FUNCTION DEFINITIONS
static hal_ll_err_t hal_ll_i2c_master_read_bare_metal( hal_ll_i2c_hw_specifics_map_t *map, uint8_t *read_data_buf, size_t len_read_data, hal_ll_i2c_master_end_mode_t mode ) {
    const hal_ll_i2c_base_handle_t *hal_ll_hw_reg = hal_ll_i2c_get_base_struct(map->base);
    size_t transfer_counter = NULL;
    uint8_t status = NULL;
    uint16_t time_counter = map->timeout;

    if( !check_reg_bit( hal_ll_hw_reg->i2c_con0_reg_addr, HAL_LL_I2C_MASTER_MDR_BIT ) ) {
        while ( !hal_ll_i2c_master_is_idle( map->base ) ) {
            if ( map->timeout ) {
                if ( !time_counter-- )
                    return HAL_LL_I2C_MASTER_TIMEOUT_WRITE;
                }
        }
    }

    write_reg( hal_ll_hw_reg->i2c_cnt_reg_addr, len_read_data );
    write_reg( hal_ll_hw_reg->i2c_adb1_reg_addr, ( map->address << 1 ) + 1 );
    status = hal_ll_i2c_master_start( map );
    if ( status != HAL_LL_I2C_MASTER_SUCCESS ) {
        return status;
    }

    time_counter = map->timeout;
    while ( !( hal_ll_hw_reg->i2c_pir_reg_addr, HAL_LL_I2C_MASTER_START_RESTART_BITS_MASK ) ) {
        if ( map->timeout ) {
            if ( !time_counter-- )
                return HAL_LL_I2C_MASTER_TIMEOUT_WRITE;
            }
    }

    clear_reg_bits( hal_ll_hw_reg->i2c_pir_reg_addr, HAL_LL_I2C_MASTER_START_RESTART_BITS_MASK );
    if( mode == HAL_LL_I2C_MASTER_WRITE_THEN_READ ) {
        hal_ll_i2c_master_restart( map->base );
    } else {
        status = hal_ll_i2c_master_start( map );
        if ( status != HAL_LL_I2C_MASTER_SUCCESS ) {
            return status;
        }
    }

    for( transfer_counter = 0; transfer_counter < len_read_data; transfer_counter++) {
        time_counter = map->timeout;
        while ( !check_reg_bit( hal_ll_hw_reg->i2c_stat1_reg_addr, HAL_LL_I2C_MASTER_RXBF_BIT ) ) {
            if ( map->timeout ) {
                if ( !time_counter-- )
                    return HAL_LL_I2C_MASTER_TIMEOUT_WRITE;
            }
        }
        read_data_buf[ transfer_counter ] = read_reg(hal_ll_hw_reg->i2c_rxb_reg_addr);
    }

    hal_ll_i2c_master_stop( map->base );

    time_counter = map->timeout;
    clear_reg_bit( hal_ll_hw_reg->i2c_pir_reg_addr, HAL_LL_I2C_MASTER_STOP_FLAG_BIT );
    while ( !( check_reg_bit( hal_ll_hw_reg->i2c_pir_reg_addr, HAL_LL_I2C_MASTER_STOP_FLAG_BIT ) ) ) {
        if ( map->timeout ) {
            if ( !time_counter-- )
                return HAL_LL_I2C_MASTER_TIMEOUT_WRITE;
        }
    }

    return HAL_LL_I2C_MASTER_SUCCESS;
}

static hal_ll_err_t hal_ll_i2c_master_write_bare_metal( hal_ll_i2c_hw_specifics_map_t *map, uint8_t *write_data_buf, size_t len_write_data, hal_ll_i2c_master_end_mode_t mode ) {
    const hal_ll_i2c_base_handle_t *hal_ll_hw_reg = hal_ll_i2c_get_base_struct(map->base);
    uint16_t time_counter = map->timeout;
    uint8_t status = NULL;
    size_t transfer_counter = NULL;

    if( !check_reg_bit( hal_ll_hw_reg->i2c_con0_reg_addr, HAL_LL_I2C_MASTER_MDR_BIT ) ) {
        while ( !hal_ll_i2c_master_is_idle( map->base ) ) {
            if ( map->timeout ) {
                if ( !time_counter-- )
                    return HAL_LL_I2C_MASTER_TIMEOUT_WRITE;
                }
        }
    }

    write_reg( hal_ll_hw_reg->i2c_cnt_reg_addr, len_write_data );
    write_reg( hal_ll_hw_reg->i2c_adb1_reg_addr, ( map->address << 1 ) );
    status = hal_ll_i2c_master_start( map );
    if ( status != HAL_LL_I2C_MASTER_SUCCESS ) {
        return status;
    }

    clear_reg_bits( hal_ll_hw_reg->i2c_pir_reg_addr, HAL_LL_I2C_MASTER_START_RESTART_BITS_MASK );

    if ( mode == HAL_LL_I2C_MASTER_WRITE_THEN_READ ) {
        hal_ll_i2c_master_restart( map->base );
    } else {
        hal_ll_i2c_master_stop( map->base );
    }

    for( transfer_counter = 0; transfer_counter < len_write_data; transfer_counter++){
        write_reg( hal_ll_hw_reg->i2c_txb_reg_addr, write_data_buf[ transfer_counter ] );

        time_counter = map->timeout;
        while ( !check_reg_bit( hal_ll_hw_reg->i2c_stat1_reg_addr, HAL_LL_I2C_MASTER_TXBE_BIT ) ) {
            if ( map->timeout ) {
                if ( !time_counter-- )
                    return HAL_LL_I2C_MASTER_TIMEOUT_WRITE;
                }
        }
    }

    time_counter = map->timeout;
    if ( mode != HAL_LL_I2C_MASTER_WRITE_THEN_READ ) {
        while ( !( check_reg_bit( hal_ll_hw_reg->i2c_pir_reg_addr, HAL_LL_I2C_MASTER_STOP_FLAG_BIT ) ) ) {
            if ( map->timeout ) {
                if ( !time_counter-- )
                    return HAL_LL_I2C_MASTER_TIMEOUT_WRITE;
                }
        }
        clear_reg_bit( hal_ll_hw_reg->i2c_pir_reg_addr, HAL_LL_I2C_MASTER_STOP_FLAG_BIT );
    } else {
        while ( !check_reg_bit( hal_ll_hw_reg->i2c_con0_reg_addr, HAL_LL_I2C_MASTER_MDR_BIT ) ) {
            if ( map->timeout ) {
                if ( !time_counter-- )
                    return HAL_LL_I2C_MASTER_TIMEOUT_WRITE;
            }
        }
    }

    return HAL_LL_I2C_MASTER_SUCCESS;
}

static hal_ll_err_t hal_ll_i2c_master_start( hal_ll_i2c_hw_specifics_map_t *map ) {
    const hal_ll_i2c_base_handle_t *hal_ll_hw_reg = hal_ll_i2c_get_base_struct(map->base);
    uint16_t time_counter = map->timeout;

    set_reg_bit( hal_ll_hw_reg->i2c_con0_reg_addr, HAL_LL_I2C_MASTER_START_BIT );

    while (!read_reg_bits( hal_ll_hw_reg->i2c_pir_reg_addr, HAL_LL_I2C_MASTER_START_RESTART_BITS_MASK)) {
        if ( map->timeout ) {
            if ( !time_counter-- )
                return HAL_LL_I2C_MASTER_TIMEOUT_WRITE;
        }
    }

    return HAL_LL_I2C_MASTER_SUCCESS;
}

static void hal_ll_i2c_master_restart( const hal_ll_i2c_base_handle_t *hal_ll_hw_reg ) {
    set_reg_bit( hal_ll_hw_reg->i2c_con0_reg_addr, HAL_LL_I2C_MASTER_RSEN_BIT );
}

static void hal_ll_i2c_master_stop( const hal_ll_i2c_base_handle_t *hal_ll_hw_reg ) {
    clear_reg_bit( hal_ll_hw_reg->i2c_con0_reg_addr, HAL_LL_I2C_MASTER_RSEN_BIT );
}

static bool hal_ll_i2c_master_is_idle( const hal_ll_i2c_base_handle_t *hal_ll_hw_reg ) {
    return check_reg_bit( hal_ll_hw_reg->i2c_stat0_reg_addr, HAL_LL_I2C_MASTER_BFRE_BIT );
}

static hal_ll_pin_name_t hal_ll_i2c_master_check_pins( hal_ll_pin_name_t scl, hal_ll_pin_name_t sda, uint8_t *index_list ) {
    static uint16_t scl_map_size = ( sizeof( hal_ll_i2c_scl_map ) / sizeof( hal_ll_i2c_pin_map_t ) );
    static uint16_t sda_map_size = ( sizeof( hal_ll_i2c_sda_map ) / sizeof( hal_ll_i2c_pin_map_t ) );
    uint8_t scl_index;
    uint8_t sda_index;

    for ( scl_index = 0; scl_index < scl_map_size; scl_index++ ) {
        if ( hal_ll_i2c_scl_map[ scl_index ]->pin == scl ) {
            for ( sda_index = 0; sda_index < sda_map_size; sda_index++ ) {
                if ( hal_ll_i2c_sda_map[ sda_index ]->pin == sda ) {
                    if ( hal_ll_i2c_scl_map[ scl_index ]->module_index == hal_ll_i2c_sda_map[ sda_index ]->module_index ) {
                        // Map pin names
                        index_list[HAL_LL_I2C_SCL_PIN] = scl_index;
                        index_list[HAL_LL_I2C_SDA_PIN] = sda_index;
                        return hal_ll_i2c_scl_map[ scl_index ]->module_index;
                    }
                }
            }
        }
    }

    return  HAL_LL_PIN_NC;
}

static hal_ll_i2c_hw_specifics_map_t *hal_ll_get_specifics( handle_t handle ) {
    uint8_t hal_ll_module_count = sizeof(hal_ll_module_state) / (sizeof(hal_ll_i2c_master_handle_register_t));
    static uint8_t hal_ll_module_error = hal_ll_module_count;

    while( hal_ll_module_count-- ) {
        if (hal_ll_i2c_get_base_from_hal_handle == hal_ll_i2c_hw_specifics_map[hal_ll_module_count]->base) {
            return &hal_ll_i2c_hw_specifics_map[hal_ll_module_count];
        }
    }

    return &hal_ll_i2c_hw_specifics_map[hal_ll_module_error];
}

static void hal_ll_i2c_master_map_pins( uint8_t module_index, uint8_t *index_list ) {
    // Map new pins
    hal_ll_i2c_hw_specifics_map[module_index]->pins.pin_scl.pin_name = hal_ll_i2c_scl_map[ index_list[HAL_LL_I2C_SCL_PIN] ]->pin;
    hal_ll_i2c_hw_specifics_map[module_index]->pins.pin_sda.pin_name = hal_ll_i2c_sda_map[ index_list[HAL_LL_I2C_SDA_PIN] ]->pin;
}

static hal_ll_pps_err_t hal_ll_pps_set_state( hal_ll_i2c_hw_specifics_map_t *map, bool hal_ll_state ) {
    hal_ll_pps_err_t hal_ll_status = HAL_LL_PPS_SUCCESS;

    if( (map->pins.pin_scl.pin_name != HAL_LL_PIN_NC) && (map->pins.pin_sda.pin_name != HAL_LL_PIN_NC) ) {
        // Check status manually if needed
        hal_ll_status = hal_ll_pps_map( hal_ll_port( map->pins->pin_scl.pin_name ), hal_ll_pin( map->pins->pin_scl.pin_name ),
                                        HAL_LL_GPIO_DIGITAL_OUTPUT, HAL_LL_PPS_FUNCTIONALITY_I2C_SCL, map->module_index, hal_ll_state );

        if ( hal_ll_status != HAL_LL_PPS_SUCCESS )
            return hal_ll_status;

        hal_ll_status = hal_ll_pps_map( hal_ll_port( map->pins->pin_scl.pin_name ), hal_ll_pin( map->pins->pin_scl.pin_name ),
                                        HAL_LL_GPIO_DIGITAL_INPUT, HAL_LL_PPS_FUNCTIONALITY_I2C_SCL, map->module_index, hal_ll_state );

        if ( hal_ll_status != HAL_LL_PPS_SUCCESS )
            return hal_ll_status;

        // Check status manually if needed
        hal_ll_status = hal_ll_pps_map( hal_ll_port( map->pins->pin_sda.pin_name ), hal_ll_pin( map->pins->pin_sda.pin_name ),
                                        HAL_LL_GPIO_DIGITAL_INPUT, HAL_LL_PPS_FUNCTIONALITY_I2C_SDA, map->module_index, hal_ll_state );

        if ( hal_ll_status != HAL_LL_PPS_SUCCESS )
            return hal_ll_status;

        hal_ll_status = hal_ll_pps_map( hal_ll_port( map->pins->pin_sda.pin_name ), hal_ll_pin( map->pins->pin_sda.pin_name ),
                                        HAL_LL_GPIO_DIGITAL_OUTPUT, HAL_LL_PPS_FUNCTIONALITY_I2C_SDA, map->module_index, hal_ll_state );

        return hal_ll_status;
    } else {
        return HAL_LL_PPS_SUCCESS;
    }
}

static void hal_ll_i2c_master_set_module_power( hal_ll_i2c_hw_specifics_map_t *map, bool hal_ll_state ) {
    switch ( map->module_index )
    {
        #ifdef I2C_MODULE
        #ifdef HAL_LL_PMD_I2C_ADDRESS
        case ( hal_ll_i2c_module_num(I2C_MODULE) ):
            ( hal_ll_state )?( clear_reg_bit( HAL_LL_PMD_I2C_ADDRESS, HAL_LL_SSP_MODULE_BIT ) ):( set_reg_bit( HAL_LL_PMD_I2C_ADDRESS, HAL_LL_SSP_MODULE_BIT ) );
            break;
        #endif
        #endif
        #ifdef I2C_MODULE_1
        #ifdef HAL_LL_PMD_I2C1_ADDRESS
        case ( hal_ll_i2c_module_num(I2C_MODULE_1) ):
            ( hal_ll_state )?( clear_reg_bit( HAL_LL_PMD_I2C1_ADDRESS, HAL_LL_SSP1_MODULE_BIT ) ):( set_reg_bit( HAL_LL_PMD_I2C1_ADDRESS, HAL_LL_SSP1_MODULE_BIT ) );
            break;
        #endif
        #endif
        #ifdef I2C_MODULE_2
        #ifdef HAL_LL_PMD_I2C2_ADDRESS
        case ( hal_ll_i2c_module_num(I2C_MODULE_2) ):
            ( hal_ll_state )?( clear_reg_bit( HAL_LL_PMD_I2C2_ADDRESS, HAL_LL_SSP2_MODULE_BIT ) ):( set_reg_bit( HAL_LL_PMD_I2C2_ADDRESS, HAL_LL_SSP2_MODULE_BIT ) );
            break;
        #endif
        #endif

        default:
            break;
    }
}

static uint32_t hal_ll_i2c_get_speed( uint32_t bit_rate ) {
    /* TODO - Add support for additional bit-rate values
     * Only 100K is implemented at the moment.
     */
    if ( bit_rate <= HAL_LL_I2C_MASTER_SPEED_100K ) {
        if ( bit_rate <= HAL_LL_I2C_MASTER_SPEED_STANDARD ) {
            return HAL_LL_I2C_MASTER_SPEED_100K;
        }
    } else {
        if ( bit_rate <= HAL_LL_I2C_MASTER_SPEED_100K ) {
            return HAL_LL_I2C_MASTER_SPEED_100K;
        }
    }

    return HAL_LL_I2C_MASTER_SPEED_100K;
}

static void hal_ll_i2c_hw_ansel_set( hal_ll_i2c_hw_specifics_map_t *map ) {
    hal_ll_gpio_pin_t local_pin;

    hal_ll_gpio_configure_pin(&local_pin, map->pins->pin_scl.pin_name, HAL_LL_GPIO_DIGITAL_OUTPUT);
    hal_ll_gpio_configure_pin(&local_pin, map->pins->pin_sda.pin_name, HAL_LL_GPIO_DIGITAL_OUTPUT);
}

static void hal_ll_i2c_hw_odcon_set( hal_ll_i2c_hw_specifics_map_t *map ) {
    static uint8_t odcon_map_size = sizeof(odconx_map) / sizeof(hal_ll_odconx_t);
    uint8_t list_index;

    for( list_index = 0; list_index < odcon_map_size; list_index++ ) {
        if ( odconx_map[list_index]->is_odconx_numeric == HAL_LL_HW_MODULES_DEFAULT ) {
            if ( (odconx_map[list_index]->pin == map->pins.pin_scl.pin_name) ||
                 (odconx_map[list_index]->pin == map->pins.pin_sda.pin_name) )
            {
                set_reg_bit( odconx_map[list_index]->odcon_address, odconx_map[list_index]->odcon_address_bit );
            }
        }
    }
}

static hal_ll_err_t hal_ll_i2c_hw_init( hal_ll_i2c_hw_specifics_map_t *map ) {
    const hal_ll_i2c_base_handle_t *hal_ll_hw_reg = hal_ll_i2c_get_base_struct(map->base);
    uint16_t time_counter = map->timeout;

    set_reg_bit( HAL_LL_OSCEN_ADDRESS, HAL_LL_OSCEN_MFOEN_BIT );
    while ( !check_reg_bit( HAL_LL_OSCSTAT_ADDRESS, HAL_LL_OSCSTAT_MFOR_BIT ) ) {
        if ( map->timeout ) {
            if ( !time_counter-- )
                return HAL_LL_I2C_MASTER_TIMEOUT_INIT;
        }
    }

    set_reg_bit( hal_ll_hw_reg->i2c_con0_reg_addr, HAL_LL_I2C_MASTER_MODE_BIT );                  // MODE, master mode 7-bit address
    set_reg_bit( hal_ll_hw_reg->i2c_con1_reg_addr, HAL_LL_I2C_MASTER_ACKCNT_BIT );                // ACKCNT

    clear_reg( hal_ll_hw_reg->i2c_con2_reg_addr );                                                // reset CON2, FME=0 => FSCL = FCLK/5 (100kHz)

    write_reg( hal_ll_hw_reg->i2c_clk_reg_addr, HAL_LL_I2C_MASTER_MFINTOSC_CLK_SOURCE );          // Fclk = MFINTOSC (500 kHz)
    write_reg( hal_ll_hw_reg->i2c_pie_reg_addr, HAL_LL_I2C_MASTER_CLEAR_CONDITION_BITS_MASK );    // Enable : Stop, Restart and Start Interrupt Flags

    set_reg_bit( hal_ll_hw_reg->i2c_con0_reg_addr, HAL_LL_I2C_MASTER_MODULE_ENABLE_BIT );         // Enable module

    return HAL_LL_I2C_MASTER_SUCCESS;
}

static hal_ll_err_t hal_ll_i2c_init( hal_ll_i2c_hw_specifics_map_t *map ) {
    hal_ll_i2c_master_set_module_power( map, true );

    hal_ll_i2c_hw_ansel_set( map );

    hal_ll_i2c_hw_odcon_set( map );

    return hal_ll_i2c_hw_init( map );
}
// ------------------------------------------------------------------------- END
