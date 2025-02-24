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
 * @file  hal_ll_i2c_master.c
 * @brief I2C master HAL LOW LEVEL layer implementation.
 */

#include "hal_ll_pps.h"
#include "hal_ll_gpio.h"
#include "hal_ll_odcon_map.h"
#include "hal_ll_i2c_master.h"
#include "hal_ll_i2c_pin_map.h"
#include "delays.h"

/*!< @brief Local handle list */
static volatile hal_ll_i2c_master_handle_register_t hal_ll_module_state[I2C_MODULE_COUNT] = { ( handle_t * )NULL, ( handle_t * )NULL, false };

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

/*!< @brief Macro used for clock value checking */
#ifdef I2C_MODULE
#define hal_ll_i2c_check_speed(_speed) ((((Get_Fosc_kHz()*250UL/_speed)-(Get_Fosc_kHz()*250UL/1111111)))-1)
#else
#ifdef GB610
#define hal_ll_i2c_check_speed(_speed) (((Get_Fosc_kHz()*250UL/_speed))-2)
#else
#define hal_ll_i2c_check_speed(_speed) ((((Get_Fosc_kHz()*500UL/_speed)-(Get_Fosc_kHz()*500UL/1111111)))-1)
#endif
#endif
#define HAL_LL_I2C_MAX_SPEED_VALUE (0x1FFU)

/*!< @brief Default I2C bit-rate if no speed is set */
#define HAL_LL_I2C_MASTER_SPEED_100K (100000UL)
#define HAL_LL_I2C_MASTER_SPEED_400K (400000UL)

/*!< @brief Default pass count value upon reset */
#define HAL_LL_I2C_DEFAULT_PASS_COUNT (100000)

/*!< @brief Macros defining register addresses and masks */
#define HAL_LL_I2C_IDLE_MASK (0x1FU)

/*!< @brief Macros defining register bit location */
#define HAL_LL_I2CCON_SEN_BIT (0)
#define HAL_LL_I2CCON_RSEN_BIT (1)
#define HAL_LL_I2CCON_PEN_BIT (2)
#define HAL_LL_I2CCON_RCEN_BIT (3)
#define HAL_LL_I2CCON_ACKEN_BIT (4)
#define HAL_LL_I2CCON_ACKDT_BIT (5)
#define HAL_LL_I2CCON_DISSLW_BIT (9)
#define HAL_LL_I2CCON_I2CEN_BIT (15)
#define HAL_LL_I2CSTAT_TBF_BIT (0)
#define HAL_LL_I2CSTAT_TRSTAT_BIT (14)
#define HAL_LL_I2CSTAT_ACKSTAT_BIT (15)
#define HAL_LL_I2CSTAT_R_W_BIT (2)
#define HAL_LL_IFS0_MI2CIF_BIT (14)
#define HAL_LL_IFS1_MI2C1IF_BIT (1)
#define HAL_LL_IFS3_MI2C2IF_BIT (2)
#define HAL_LL_IFS4_MI2C2IF_BIT (7)

// -------------------------------------------------------------- PRIVATE TYPES
/*!< @brief I2C register structure */
typedef struct
{
    hal_ll_base_addr_t i2crcv_reg_addr;
    hal_ll_base_addr_t i2ctrn_reg_addr;
    hal_ll_base_addr_t i2cbrg_reg_addr;
    hal_ll_base_addr_t i2ccon_reg_addr;
    hal_ll_base_addr_t i2cstat_reg_addr;
    hal_ll_base_addr_t if_reg_addr;
} hal_ll_i2c_base_handle_t;

/*!< @brief I2C hw speed structure */
typedef struct
{
    uint32_t speed_value;
    uint8_t speed_write_reg_value;
} hal_ll_i2c_hw_speed_t;

/*!< @brief I2C hw specific structure */
typedef struct
{
    const hal_ll_i2c_base_handle_t *base;
    hal_ll_pin_name_t module_index;
    hal_ll_i2c_pins_t pins;
    hal_ll_i2c_hw_speed_t speed;
    uint8_t address;
    uint16_t timeout;
} hal_ll_i2c_hw_specifics_map_t;

/*!< @brief I2C hw specific module values */
typedef struct
{
    uint16_t pin_scl;
    uint16_t pin_sda;
} hal_ll_i2c_pin_id;

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
    HAL_LL_I2C_MASTER_TIMEOUT_WRITE,
    HAL_LL_I2C_MASTER_TIMEOUT_READ,
    HAL_LL_I2C_MASTER_ARBITRATION_LOST,
    HAL_LL_I2C_MASTER_TIMEOUT_WAIT_IDLE
} hal_ll_i2c_master_timeout_t;

/**
 * @brief Enum containing predefined module standard speed values.
 *
 * Enum values:
 * HAL_LL_I2C_MASTER_SPEED_STANDARD -- Speed set at 100K
 * HAL_LL_I2C_MASTER_SPEED_FULL -- Speed set at 400K
 */
typedef enum
{
    HAL_LL_I2C_MASTER_SPEED_STANDARD = 0,
    HAL_LL_I2C_MASTER_SPEED_FULL
} hal_ll_i2c_master_speed_t;

// ------------------------------------------------------------------ CONSTANTS
/*!< @brief I2C registers array */
static const hal_ll_i2c_base_handle_t hal_ll_i2c_hw_regs[ I2C_MODULE_COUNT + 1 ] =
{
    #ifdef I2C_MODULE
    #ifdef HAL_LL_I2CRCV_REG_ADDRESS
    { HAL_LL_I2CRCV_REG_ADDRESS, HAL_LL_I2CTRN_REG_ADDRESS, HAL_LL_I2CBRG_REG_ADDRESS, HAL_LL_I2CCON_REG_ADDRESS, HAL_LL_I2CSTAT_REG_ADDRESS, HAL_LL_IFS0_REG_ADDRESS },
    #endif
    #endif

    #ifdef I2C_MODULE_1
    #ifdef HAL_LL_I2C1RCV_REG_ADDRESS
    { HAL_LL_I2C1RCV_REG_ADDRESS, HAL_LL_I2C1TRN_REG_ADDRESS, HAL_LL_I2C1BRG_REG_ADDRESS, HAL_LL_I2C1CON_REG_ADDRESS, HAL_LL_I2C1STAT_REG_ADDRESS, HAL_LL_IFS1_REG_ADDRESS },
    #endif
    #endif

    #ifdef I2C_MODULE_2
    #ifdef HAL_LL_I2C2RCV_REG_ADDRESS
    { HAL_LL_I2C2RCV_REG_ADDRESS, HAL_LL_I2C2TRN_REG_ADDRESS, HAL_LL_I2C2BRG_REG_ADDRESS, HAL_LL_I2C2CON_REG_ADDRESS, HAL_LL_I2C2STAT_REG_ADDRESS, HAL_LL_IFS3_REG_ADDRESS },
    #endif
    #endif

    #ifdef I2C_MODULE_3
    #ifdef HAL_LL_I2C3RCV_REG_ADDRESS
    { HAL_LL_I2C3RCV_REG_ADDRESS, HAL_LL_I2C3TRN_REG_ADDRESS, HAL_LL_I2C3BRG_REG_ADDRESS, HAL_LL_I2C3CON_REG_ADDRESS, HAL_LL_I2C3STAT_REG_ADDRESS, HAL_LL_IFS4_REG_ADDRESS },
    #endif
    #endif

    { HAL_LL_MODULE_ERROR, HAL_LL_MODULE_ERROR, HAL_LL_MODULE_ERROR, HAL_LL_MODULE_ERROR, HAL_LL_MODULE_ERROR, HAL_LL_MODULE_ERROR }
};

/*!< @brief I2C interrupt flags */
static const uint8_t hal_ll_i2c_if[ I2C_MODULE_COUNT + 1 ] =
{
    #ifdef I2C_MODULE
    HAL_LL_IFS0_MI2CIF_BIT,
    #endif

    #ifdef I2C_MODULE_1
    HAL_LL_IFS1_MI2C1IF_BIT,
    #endif

    #ifdef I2C_MODULE_2
    HAL_LL_IFS3_MI2C2IF_BIT,
    #endif

    #ifdef I2C_MODULE_3
    HAL_LL_IFS4_MI2C2IF_BIT,
    #endif

    HAL_LL_PIN_NC
};

// ------------------------------------------------------------------ VARIABLES
/*!< @brief I2C hardware specific info */
static hal_ll_i2c_hw_specifics_map_t hal_ll_i2c_hw_specifics_map[ I2C_MODULE_COUNT + 1 ] =
{
    #ifdef I2C_MODULE
    { &hal_ll_i2c_hw_regs[hal_ll_i2c_module_num( I2C_MODULE )], hal_ll_i2c_module_num( I2C_MODULE ), { HAL_LL_PIN_NC, 0, HAL_LL_PIN_NC, 0 }, { HAL_LL_I2C_MASTER_SPEED_100K, 0 }, 0, HAL_LL_I2C_DEFAULT_PASS_COUNT },
    #endif

    #ifdef I2C_MODULE_1
    { &hal_ll_i2c_hw_regs[hal_ll_i2c_module_num( I2C_MODULE_1 )], hal_ll_i2c_module_num( I2C_MODULE_1 ), { HAL_LL_PIN_NC, 0, HAL_LL_PIN_NC, 0 }, { HAL_LL_I2C_MASTER_SPEED_100K, 0 }, 0, HAL_LL_I2C_DEFAULT_PASS_COUNT },
    #endif

    #ifdef I2C_MODULE_2
    { &hal_ll_i2c_hw_regs[hal_ll_i2c_module_num( I2C_MODULE_2 )], hal_ll_i2c_module_num( I2C_MODULE_2 ), { HAL_LL_PIN_NC, 0, HAL_LL_PIN_NC, 0 }, { HAL_LL_I2C_MASTER_SPEED_100K, 0 }, 0, HAL_LL_I2C_DEFAULT_PASS_COUNT },
    #endif

    #ifdef I2C_MODULE_3
    { &hal_ll_i2c_hw_regs[hal_ll_i2c_module_num( I2C_MODULE_3 )], hal_ll_i2c_module_num( I2C_MODULE_3 ), { HAL_LL_PIN_NC, 0, HAL_LL_PIN_NC, 0 }, { HAL_LL_I2C_MASTER_SPEED_100K, 0 }, 0, HAL_LL_I2C_DEFAULT_PASS_COUNT },
    #endif

    { &hal_ll_i2c_hw_regs[I2C_MODULE_COUNT], HAL_LL_MODULE_ERROR, { HAL_LL_PIN_NC, 0, HAL_LL_PIN_NC, 0 }, { 0, 0 }, 0, 0 }
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
  *                           and module number
  * @param[in]  *handle_map - I2C master low level handle
  *
  * @return hal_ll_pin_name_t Module index based on pins.
  *
  * Returns pre-defined module index from pin maps, if pins
  * are adequate.
  */
static hal_ll_pin_name_t hal_ll_i2c_master_check_pins( hal_ll_pin_name_t scl, hal_ll_pin_name_t sda, hal_ll_i2c_pin_id *index_list, hal_ll_i2c_master_handle_register_t *handle_map );

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
  * HAL_LL_I2C_MASTER_SPEED_400K -- 400Kbit/s
  */
static uint32_t hal_ll_i2c_get_speed( uint32_t bit_rate );

/**
 * @brief  Maps new-found module specific values.
 *
 * Maps pin names and alternate function values for
 * I2C SCL and SDA pins.
 *
 * @param[in]  module_index I2C HW module index -- 0,1,2...
 * @param[in]  *index_list  Array with SCL and SDA map index values
 *                          and module number
 *
 * @return  None
 */
static void hal_ll_i2c_master_map_pins( uint8_t module_index, hal_ll_i2c_pin_id *index_list );

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
static void hal_ll_i2c_hw_init( hal_ll_i2c_hw_specifics_map_t *map );

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
static void hal_ll_i2c_init( hal_ll_i2c_hw_specifics_map_t *map );

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
static hal_ll_err_t hal_ll_i2c_master_restart( hal_ll_i2c_hw_specifics_map_t *map );

/**
  * @brief  Checks bus for on-going write.
  *
  * @param[in]  map - Object specific context handler.
  *
  * @return uint32_t Adequate bit-rate value.
  *
  * Returns one of pre-defined values.
  * Take into consideration that this is hardware specific.
  */
static hal_ll_err_t hal_ll_i2c_master_check_write( hal_ll_i2c_hw_specifics_map_t *map );

/**
  * @brief  Perform a read on the I2C bus.
  *
  * Initializes I2C module on hardware level, if not initialized beforehand
  * and continues to perform a read operation on the bus.
  *
  * @param[in]  map - Object specific context handler.
  * @param[in]  read_data_buf - Pointer to data buffer.
  * @param[in]  len_read_data - Number of data to be read.
  * @param[in]  mode - I2C end mode.
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
  * @param[in]  mode - I2C end mode.
  *
  * @return hal_ll_err_t Module specific values.
  *
  * Returns one of pre-defined values.
  * Take into consideration that this is hardware specific.
  */
static hal_ll_err_t hal_ll_i2c_master_write_bare_metal( hal_ll_i2c_hw_specifics_map_t *map, uint8_t *write_data_buf, size_t len_write_data, hal_ll_i2c_master_end_mode_t mode );

// ------------------------------------------------ PUBLIC FUNCTION DEFINITIONS
hal_ll_err_t hal_ll_i2c_master_register_handle( hal_ll_pin_name_t scl, hal_ll_pin_name_t sda, hal_ll_i2c_master_handle_register_t *handle_map, uint8_t *hal_module_id ) {
    hal_ll_i2c_pin_id index_list[I2C_MODULE_COUNT] = { HAL_LL_PIN_NC, HAL_LL_PIN_NC };
    uint8_t pin_check_result;

    if ( HAL_LL_PIN_NC == ( pin_check_result = hal_ll_i2c_master_check_pins( scl, sda, &index_list, handle_map ) ) ) {
        return HAL_LL_I2C_MASTER_WRONG_PINS;
    };

    if ( ( hal_ll_i2c_hw_specifics_map[pin_check_result].pins.pin_scl.pin_name != scl ) ||
         ( hal_ll_i2c_hw_specifics_map[pin_check_result].pins.pin_sda.pin_name != sda ) ) {

        hal_ll_i2c_master_map_pins( pin_check_result, &index_list );
        handle_map[pin_check_result].init_ll_state = false;
    }

    *hal_module_id = pin_check_result;

    hal_ll_module_state[pin_check_result].hal_ll_i2c_master_handle = ( handle_t * )&hal_ll_i2c_hw_specifics_map[pin_check_result].base;

    handle_map[pin_check_result].hal_ll_i2c_master_handle = ( handle_t * )&hal_ll_module_state[pin_check_result].hal_ll_i2c_master_handle;

    return HAL_LL_I2C_MASTER_SUCCESS;
}

hal_ll_err_t hal_ll_module_configure_i2c( handle_t *handle ) {
    hal_ll_i2c_hw_specifics_map_local = hal_ll_get_specifics(hal_ll_i2c_get_module_state_address);
    hal_ll_i2c_master_handle_register_t *hal_handle = (hal_ll_i2c_master_handle_register_t *)*handle;
    uint8_t pin_check_result = hal_ll_i2c_hw_specifics_map_local->module_index;

    hal_ll_i2c_init( hal_ll_i2c_hw_specifics_map_local );

    hal_ll_module_state[pin_check_result].hal_ll_i2c_master_handle = (handle_t *)&hal_ll_i2c_hw_specifics_map[pin_check_result].base;
    hal_ll_module_state[pin_check_result].init_ll_state = true;
    hal_handle->init_ll_state = true;

    return HAL_LL_I2C_MASTER_SUCCESS;
}

hal_ll_err_t hal_ll_i2c_master_set_speed( handle_t *handle, uint32_t speed ) {
    low_level_handle = hal_ll_i2c_get_handle;
    hal_ll_i2c_hw_specifics_map_local = hal_ll_get_specifics( hal_ll_i2c_get_module_state_address );

    low_level_handle->init_ll_state = false;

    hal_ll_i2c_hw_specifics_map_local->speed.speed_value = hal_ll_i2c_check_speed( hal_ll_i2c_get_speed( speed ) );
    if ( HAL_LL_I2C_MAX_SPEED_VALUE < hal_ll_i2c_hw_specifics_map_local->speed.speed_value ) {
        return HAL_LL_I2C_MASTER_MODULE_ERROR;
    }

    hal_ll_i2c_hw_specifics_map_local->speed.speed_write_reg_value = hal_ll_i2c_hw_specifics_map_local->speed.speed_value;
    hal_ll_i2c_hw_specifics_map_local->speed.speed_value = hal_ll_i2c_get_speed( speed );

    hal_ll_i2c_init( hal_ll_i2c_hw_specifics_map_local );

    low_level_handle->init_ll_state = true;

    return hal_ll_i2c_hw_specifics_map_local->speed.speed_value;
}

void hal_ll_i2c_master_set_timeout( handle_t *handle, uint16_t timeout ) {
    low_level_handle = hal_ll_i2c_get_handle;
    hal_ll_i2c_hw_specifics_map_local = hal_ll_get_specifics( hal_ll_i2c_get_module_state_address );

    hal_ll_i2c_hw_specifics_map_local->timeout = timeout;
}

void hal_ll_i2c_master_set_slave_address( handle_t *handle, uint8_t addr ) {
    low_level_handle = hal_ll_i2c_get_handle;
    hal_ll_i2c_hw_specifics_map_local = hal_ll_get_specifics( hal_ll_i2c_get_module_state_address );

    hal_ll_i2c_hw_specifics_map_local->address = addr;
}

hal_ll_err_t hal_ll_i2c_master_read( handle_t *handle, uint8_t *read_data_buf, size_t len_read_data ) {
    low_level_handle = hal_ll_i2c_get_handle;
    hal_ll_i2c_hw_specifics_map_local = hal_ll_get_specifics( hal_ll_i2c_get_module_state_address );

    return hal_ll_i2c_master_read_bare_metal( hal_ll_i2c_hw_specifics_map_local, read_data_buf, len_read_data, HAL_LL_I2C_MASTER_END_MODE_STOP );
}

hal_ll_err_t hal_ll_i2c_master_write( handle_t *handle, uint8_t *write_data_buf, size_t len_write_data ) {
    low_level_handle = hal_ll_i2c_get_handle;
    hal_ll_i2c_hw_specifics_map_local = hal_ll_get_specifics( hal_ll_i2c_get_module_state_address );

    return hal_ll_i2c_master_write_bare_metal( hal_ll_i2c_hw_specifics_map_local, write_data_buf, len_write_data, HAL_LL_I2C_MASTER_END_MODE_STOP );
}

hal_ll_err_t hal_ll_i2c_master_write_then_read( handle_t *handle, uint8_t *write_data_buf, size_t len_write_data, uint8_t *read_data_buf, size_t len_read_data ) {
    low_level_handle = hal_ll_i2c_get_handle;
    hal_ll_i2c_hw_specifics_map_local = hal_ll_get_specifics( hal_ll_i2c_get_module_state_address );

    if ( HAL_LL_I2C_MASTER_SUCCESS != hal_ll_i2c_master_write_bare_metal( hal_ll_i2c_hw_specifics_map_local, write_data_buf, len_write_data, HAL_LL_I2C_MASTER_WRITE_THEN_READ ) ) {
        return HAL_LL_I2C_MASTER_TIMEOUT_WRITE;
    }

    /**
     * @note Wait for drivers to set-up
     * correctly.
     **/
    #ifdef __TFT_RESISTIVE_TSC2003__
    Delay_22us();
    #endif

    if ( HAL_LL_I2C_MASTER_SUCCESS != hal_ll_i2c_master_read_bare_metal( hal_ll_i2c_hw_specifics_map_local, read_data_buf, len_read_data, HAL_LL_I2C_MASTER_WRITE_THEN_READ ) ) {
        return HAL_LL_I2C_MASTER_TIMEOUT_READ;
    }

    return HAL_LL_I2C_MASTER_SUCCESS;
}

void hal_ll_i2c_master_close( handle_t *handle ) {
    low_level_handle = hal_ll_i2c_get_handle;
    hal_ll_i2c_hw_specifics_map_local = hal_ll_get_specifics( hal_ll_i2c_get_module_state_address );

    if ( NULL != low_level_handle->hal_ll_i2c_master_handle ) {
        low_level_handle->hal_ll_i2c_master_handle = NULL;
        low_level_handle->hal_drv_i2c_master_handle = NULL;
        low_level_handle->init_ll_state = false;

        hal_ll_i2c_hw_specifics_map_local->address = 0;
        hal_ll_i2c_hw_specifics_map_local->timeout = HAL_LL_I2C_DEFAULT_PASS_COUNT;
        hal_ll_i2c_hw_specifics_map_local->speed.speed_value = HAL_LL_I2C_MASTER_SPEED_100K;

        hal_ll_i2c_hw_specifics_map_local->pins.pin_scl.pin_name = HAL_LL_PIN_NC;
        hal_ll_i2c_hw_specifics_map_local->pins.pin_sda.pin_name = HAL_LL_PIN_NC;
    }
}

// ----------------------------------------------- PRIVATE FUNCTION DEFINITIONS
static hal_ll_err_t hal_ll_i2c_master_read_bare_metal( hal_ll_i2c_hw_specifics_map_t *map, uint8_t *read_data_buf, size_t len_read_data, hal_ll_i2c_master_end_mode_t mode ) {
    const hal_ll_i2c_base_handle_t *hal_ll_hw_reg = hal_ll_i2c_get_base_struct( map->base );
    size_t transfer_counter = 0;
    uint16_t time_counter = map->timeout;
    uint8_t status = HAL_LL_I2C_MASTER_SUCCESS;

    if ( HAL_LL_I2C_MASTER_WRITE_THEN_READ != mode ) {
        status = hal_ll_i2c_master_start( map );
        if ( HAL_LL_I2C_MASTER_SUCCESS != status ) {
            return status;
        }
    }

    clear_reg_bit( hal_ll_hw_reg->if_reg_addr, hal_ll_i2c_if[map->module_index] );
    write_reg( hal_ll_hw_reg->i2ctrn_reg_addr, ( ( map->address << 1 ) | 1 ) );

    status = hal_ll_i2c_master_check_write( map );
    if ( HAL_LL_I2C_MASTER_SUCCESS != status ) {
        return status;
    }

    for ( transfer_counter = 0; transfer_counter < len_read_data; transfer_counter++ ) {
        clear_reg_bit( hal_ll_hw_reg->if_reg_addr, hal_ll_i2c_if[map->module_index] );
        set_reg_bit( hal_ll_hw_reg->i2ccon_reg_addr, HAL_LL_I2CCON_RCEN_BIT );

        while ( !check_reg_bit( hal_ll_hw_reg->if_reg_addr, hal_ll_i2c_if[map->module_index] ) ) {
            if ( map->timeout ) {
                if ( !time_counter-- )
                    return HAL_LL_I2C_MASTER_TIMEOUT_READ;
            }
        }

        read_data_buf[transfer_counter] = read_reg( hal_ll_hw_reg->i2crcv_reg_addr );

        if ( transfer_counter < ( len_read_data - 1 ) ) {
            clear_reg_bit( hal_ll_hw_reg->i2ccon_reg_addr, HAL_LL_I2CCON_ACKDT_BIT );
        } else {
            set_reg_bit( hal_ll_hw_reg->i2ccon_reg_addr, HAL_LL_I2CCON_ACKDT_BIT );
        }

        clear_reg_bit( hal_ll_hw_reg->if_reg_addr, hal_ll_i2c_if[map->module_index] );
        set_reg_bit( hal_ll_hw_reg->i2ccon_reg_addr, HAL_LL_I2CCON_ACKEN_BIT );

        time_counter = map->timeout;
        while ( !check_reg_bit( hal_ll_hw_reg->if_reg_addr, hal_ll_i2c_if[map->module_index] ) ) {
            if ( map->timeout ) {
                if ( !time_counter-- )
                    return HAL_LL_I2C_MASTER_TIMEOUT_READ;
            }
        }
    }

    set_reg_bit( hal_ll_hw_reg->i2ccon_reg_addr, HAL_LL_I2CCON_PEN_BIT );

    return HAL_LL_I2C_MASTER_SUCCESS;
}

static hal_ll_err_t hal_ll_i2c_master_write_bare_metal( hal_ll_i2c_hw_specifics_map_t *map, uint8_t *write_data_buf, size_t len_write_data, hal_ll_i2c_master_end_mode_t mode ) {
    const hal_ll_i2c_base_handle_t *hal_ll_hw_reg = hal_ll_i2c_get_base_struct( map->base );
    size_t transfer_counter = 0;
    uint8_t status = HAL_LL_I2C_MASTER_SUCCESS;

    status = hal_ll_i2c_master_start( map );
    if ( HAL_LL_I2C_MASTER_SUCCESS != status ) {
        return status;
    }

    clear_reg_bit( hal_ll_hw_reg->if_reg_addr, hal_ll_i2c_if[map->module_index] );
    write_reg( hal_ll_hw_reg->i2ctrn_reg_addr, ( map->address << 1 ) );
    status = hal_ll_i2c_master_check_write( map );
    if ( status != HAL_LL_I2C_MASTER_SUCCESS ) {
        return status;
    }

    for ( transfer_counter = 0; transfer_counter < len_write_data; transfer_counter++ ) {
        write_reg( hal_ll_hw_reg->i2ctrn_reg_addr, write_data_buf[transfer_counter] );
        status = hal_ll_i2c_master_check_write( map );
        if( status != HAL_LL_I2C_MASTER_SUCCESS ) {
            return status;
        }
    }

    if ( ( HAL_LL_I2C_MASTER_END_MODE_RESTART == mode ) || ( HAL_LL_I2C_MASTER_WRITE_THEN_READ == mode ) ) {
        /**
         * @note When R/W = 0, the input sample acquisition period starts
         * on the falling edge of SCL once the C0 bit of the command
         * byte has been latched, and ends when a Stop or
         * repeated Start condition has been issued.
         **/
        #ifdef __TFT_RESISTIVE_TSC2003__
        Delay_1ms();
        #endif

        status = hal_ll_i2c_master_restart( map );
        if ( HAL_LL_I2C_MASTER_SUCCESS != status ) {
            return status;
        }
    } else if ( HAL_LL_I2C_MASTER_END_MODE_STOP == mode ) {
        set_reg_bit( hal_ll_hw_reg->i2ccon_reg_addr, HAL_LL_I2CCON_PEN_BIT );
    }

    if ( !check_reg_bit( hal_ll_hw_reg->i2cstat_reg_addr, HAL_LL_I2CSTAT_ACKSTAT_BIT ) ) {
        return HAL_LL_I2C_MASTER_SUCCESS;
    } else {
        return HAL_LL_I2C_MASTER_ERROR;
    }
}

static hal_ll_err_t hal_ll_i2c_master_start( hal_ll_i2c_hw_specifics_map_t *map ) {
    const hal_ll_i2c_base_handle_t *hal_ll_hw_reg = hal_ll_i2c_get_base_struct( map->base );
    uint16_t time_counter = map->timeout;

    while ( !hal_ll_i2c_master_is_idle( hal_ll_hw_reg ) ) {
        if ( map->timeout ) {
            if ( !time_counter-- )
                return HAL_LL_I2C_MASTER_TIMEOUT_START;
        }
    }

    set_reg_bit( hal_ll_hw_reg->i2ccon_reg_addr, HAL_LL_I2CCON_SEN_BIT );

    time_counter = map->timeout;
    while ( check_reg_bit( hal_ll_hw_reg->i2ccon_reg_addr, HAL_LL_I2CCON_SEN_BIT ) ) {
        if ( map->timeout ) {
            if ( !time_counter-- )
                return HAL_LL_I2C_MASTER_TIMEOUT_START;
        }
    }

    return HAL_LL_I2C_MASTER_SUCCESS;
}

static hal_ll_err_t hal_ll_i2c_master_restart( hal_ll_i2c_hw_specifics_map_t *map ) {
    const hal_ll_i2c_base_handle_t *hal_ll_hw_reg = hal_ll_i2c_get_base_struct( map->base );
    uint16_t time_counter = map->timeout;

    set_reg_bit( hal_ll_hw_reg->i2ccon_reg_addr, HAL_LL_I2CCON_RSEN_BIT );
    while ( check_reg_bit( hal_ll_hw_reg->i2ccon_reg_addr, HAL_LL_I2CCON_RSEN_BIT ) ) {
        if ( map->timeout ) {
            if ( !time_counter-- )
                return HAL_LL_I2C_MASTER_TIMEOUT_START;
        }
    }

    return HAL_LL_I2C_MASTER_SUCCESS;
}

static bool hal_ll_i2c_master_is_idle( const hal_ll_i2c_base_handle_t *hal_ll_hw_reg ) {
    if ( !check_reg_bit( hal_ll_hw_reg->i2cstat_reg_addr, HAL_LL_I2CSTAT_TRSTAT_BIT ) ) {
        if ( !( read_reg( hal_ll_hw_reg->i2ccon_reg_addr ) & HAL_LL_I2C_IDLE_MASK ) ) {
            return HAL_LL_I2C_MASTER_TIMEOUT_WAIT_IDLE;
        }
    }

    return HAL_LL_I2C_MASTER_SUCCESS;
}

static hal_ll_err_t hal_ll_i2c_master_check_write( hal_ll_i2c_hw_specifics_map_t *map ) {
    const hal_ll_i2c_base_handle_t *hal_ll_hw_reg = hal_ll_i2c_get_base_struct( map->base );
    uint16_t time_counter = map->timeout;

    while ( check_reg_bit( hal_ll_hw_reg->i2cstat_reg_addr, HAL_LL_I2CSTAT_TRSTAT_BIT ) ) {
        if ( map->timeout ) {
            if ( !time_counter-- )
                return HAL_LL_I2C_MASTER_TIMEOUT_WRITE;
        }
    }

    time_counter = map->timeout;
    while ( !check_reg_bit( hal_ll_hw_reg->if_reg_addr, hal_ll_i2c_if[map->module_index] ) ) {
        if ( map->timeout ) {
            if ( !time_counter-- )
                return HAL_LL_I2C_MASTER_TIMEOUT_WRITE;
        }
    }

    return HAL_LL_I2C_MASTER_SUCCESS;
}

static hal_ll_pin_name_t hal_ll_i2c_master_check_pins( hal_ll_pin_name_t scl, hal_ll_pin_name_t sda, hal_ll_i2c_pin_id *index_list, hal_ll_i2c_master_handle_register_t *handle_map ) {
    static const uint16_t scl_map_size = ( sizeof( hal_ll_i2c_scl_map ) / sizeof( hal_ll_i2c_pin_map_t ) );
    static const uint16_t sda_map_size = ( sizeof( hal_ll_i2c_sda_map ) / sizeof( hal_ll_i2c_pin_map_t ) );
    uint8_t hal_ll_module_id = 0;
    uint8_t index_counter = 0;
    uint16_t scl_index;
    uint16_t sda_index;

    if ( ( HAL_LL_PIN_NC == scl ) || ( HAL_LL_PIN_NC == sda ) ) {
        return HAL_LL_PIN_NC;
    }

    for ( scl_index = 0; scl_index < scl_map_size; scl_index++ ) {
        if ( hal_ll_i2c_scl_map[scl_index].pin == scl ) {
            for ( sda_index = 0; sda_index < sda_map_size; sda_index++ ) {
                if ( hal_ll_i2c_sda_map[sda_index].pin == sda ) {
                    if ( hal_ll_i2c_scl_map[scl_index].module_index == hal_ll_i2c_sda_map[sda_index].module_index ) {
                        // Get module number
                        hal_ll_module_id = hal_ll_i2c_scl_map[scl_index].module_index;
                        // Map pin names
                        index_list[hal_ll_module_id].pin_scl = scl_index;
                        index_list[hal_ll_module_id].pin_sda = sda_index;

                        // Check if module is taken
                        if ( NULL == handle_map[hal_ll_module_id].hal_drv_i2c_master_handle ) {
                            return hal_ll_module_id;
                        } else if ( I2C_MODULE_COUNT == ++index_counter ) {
                            return --index_counter;
                        }
                    }
                }
            }
        }
    }

    if ( index_counter ) {
        return hal_ll_module_id;
    } else {
        return HAL_LL_PIN_NC;
    }
}

static hal_ll_i2c_hw_specifics_map_t *hal_ll_get_specifics( handle_t handle ) {
    uint8_t hal_ll_module_count = sizeof( hal_ll_module_state ) / ( sizeof( hal_ll_i2c_master_handle_register_t ) );
    static uint8_t hal_ll_module_error = sizeof( hal_ll_module_state ) / ( sizeof( hal_ll_i2c_master_handle_register_t ) );

    while( hal_ll_module_count-- ) {
        if ( hal_ll_i2c_get_base_from_hal_handle == hal_ll_i2c_hw_specifics_map[hal_ll_module_count].base ) {
            return &hal_ll_i2c_hw_specifics_map[hal_ll_module_count];
        }
    }

    return &hal_ll_i2c_hw_specifics_map[hal_ll_module_error];
}

static void hal_ll_i2c_master_map_pins( uint8_t module_index, hal_ll_i2c_pin_id *index_list ) {
    // Map new pins
    hal_ll_i2c_hw_specifics_map[module_index].pins.pin_scl.pin_name = hal_ll_i2c_scl_map[index_list[module_index].pin_scl].pin;
    hal_ll_i2c_hw_specifics_map[module_index].pins.pin_sda.pin_name = hal_ll_i2c_sda_map[index_list[module_index].pin_sda].pin;
}

static uint32_t hal_ll_i2c_get_speed( uint32_t bit_rate ) {
    if ( HAL_LL_I2C_MASTER_SPEED_FULL >= bit_rate ) {
        if ( HAL_LL_I2C_MASTER_SPEED_STANDARD >= bit_rate ) {
            return HAL_LL_I2C_MASTER_SPEED_100K;
        } else if ( HAL_LL_I2C_MASTER_SPEED_FULL >= bit_rate ) {
            return HAL_LL_I2C_MASTER_SPEED_400K;
        } else {
            return HAL_LL_I2C_MASTER_SPEED_400K;
        }
    } else {
        if ( HAL_LL_I2C_MASTER_SPEED_100K >= bit_rate ) {
            return HAL_LL_I2C_MASTER_SPEED_100K;
        } else if ( HAL_LL_I2C_MASTER_SPEED_400K >= bit_rate ) {
            return HAL_LL_I2C_MASTER_SPEED_400K;
        } else {
            return HAL_LL_I2C_MASTER_SPEED_400K;
        }
    }

    return HAL_LL_I2C_MASTER_SPEED_100K;
}

static void hal_ll_i2c_hw_init( hal_ll_i2c_hw_specifics_map_t *map ) {
    const hal_ll_i2c_base_handle_t *hal_ll_hw_reg = hal_ll_i2c_get_base_struct( map->base );

    write_reg( hal_ll_hw_reg->i2cbrg_reg_addr, map->speed.speed_write_reg_value );
    set_reg_bit( hal_ll_hw_reg->i2ccon_reg_addr, HAL_LL_I2CCON_I2CEN_BIT );

    clear_reg( hal_ll_hw_reg->i2cstat_reg_addr );
    while ( !hal_ll_i2c_master_is_idle( hal_ll_hw_reg ) );
}

static void hal_ll_i2c_init( hal_ll_i2c_hw_specifics_map_t *map ) {
    hal_ll_i2c_hw_init( map );
}

// ------------------------------------------------------------------------- END
