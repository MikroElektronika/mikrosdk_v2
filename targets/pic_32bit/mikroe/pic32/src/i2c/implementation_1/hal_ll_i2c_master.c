/****************************************************************************
**
** Copyright (C) 2021 MikroElektronika d.o.o.
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
 * @file  hal_ll_i2c_master.c
 * @brief I2C master HAL LOW LEVEL layer implementation.
 */

#include "hal_ll_gpio.h"
#include "hal_ll_i2c_master.h"
#include "hal_ll_i2c_pin_map.h"

/*!< @brief Local handle list */
static volatile hal_ll_i2c_master_handle_register_t hal_ll_module_state[ I2C_MODULE_COUNT ] = { ( handle_t * )NULL, ( handle_t * )NULL, false };

// ------------------------------------------------------------- PRIVATE MACROS

/*!< @brief Helper macro for getting hal_ll_module_state address */
#define hal_ll_i2c_get_module_state_address     (( hal_ll_i2c_master_handle_register_t * )*handle )
/*!< @brief Helper macro for getting module specific control register structure base address // first register address */
#define hal_ll_i2c_get_handle                   ( hal_ll_i2c_master_handle_register_t * )hal_ll_i2c_get_module_state_address->hal_ll_i2c_master_handle
/*!< @brief Helper macro for getting module specific control register structure */
#define hal_ll_i2c_get_base_struct( _handle )   (( hal_ll_i2c_base_handle_t * )_handle )
/*!< @brief Helper macro for getting module specific base address directly from HAL layer handle */
#define hal_ll_i2c_get_base_from_hal_handle     (( hal_ll_i2c_hw_specifics_map_t * )(( low_level_handle->hal_ll_i2c_master_handle )))->base

/*!< @brief Macro used for clock value checking */
#define HAL_LL_I2C_PB2DIV_MASK                  0x007F
#define PB_Clock_Divisor                        (((*( uint32_t * )HAL_LL_PB2DIV_ADDRESS ) &HAL_LL_I2C_PB2DIV_MASK ) + 1 )
#define PB_Clock_Value_Mx(_value)               (_value==0)?(1): \
                                                (_value==1)?(2): \
                                                (_value==2)?(4): \
                                                (8)

/*!< @brief Default I2C bit-rate if no speed is set */
#define HAL_LL_I2C_MASTER_SPEED_100K            100000UL
#define HAL_LL_I2C_MASTER_SPEED_400K            400000UL

/*!< @brief Default pass count value upon reset */
#define HAL_LL_I2C_DEFAULT_PASS_COUNT           10000

/*!< @brief Macros defining register addresses and masks */
#define HAL_LL_I2CXSTAT_MASK                    0x0U
#define HAL_LL_I2C_IDLE_MASK                    0x1FU

/*!< @brief Macros defining register bit location */
#define HAL_LL_I2CCON_SEN_BIT                   0
#define HAL_LL_I2CCON_RSEN_BIT                  1
#define HAL_LL_I2CCON_PEN_BIT                   2
#define HAL_LL_I2CCON_RCEN_BIT                  3
#define HAL_LL_I2CCON_ACKEN_BIT                 4
#define HAL_LL_I2CCON_ACKDT_BIT                 5
#define HAL_LL_I2CCON_DISSLW_BIT                9
#define HAL_LL_I2CCON_ON_BIT                    15

#define HAL_LL_I2CSTAT_TBF_BIT                  0
#define HAL_LL_I2CSTAT_I2COV_BIT                6
#define HAL_LL_I2CSTAT_IWCOL_BIT                7
#define HAL_LL_I2CSTAT_BCL_BIT                  10
#define HAL_LL_I2CSTAT_TRSTAT_BIT               14
#define HAL_LL_I2CSTAT_ACKSTAT_BIT              15

// -------------------------------------------------------------- PRIVATE TYPES
/*!< @brief I2C register structure */
typedef struct
{
    hal_ll_base_addr_t i2ccon_reg_addr;
    hal_ll_base_addr_t __unused_1[ 3 ];
    hal_ll_base_addr_t i2cstat_reg_addr;
    hal_ll_base_addr_t __unused_2[ 3 ];
    hal_ll_base_addr_t i2cadd_reg_addr;
    hal_ll_base_addr_t __unused_3[ 3 ];
    hal_ll_base_addr_t i2cmsk_reg_addr;
    hal_ll_base_addr_t __unused_4[ 3 ];
    hal_ll_base_addr_t i2cbrg_reg_addr;
    hal_ll_base_addr_t __unused_5[ 3 ];
    hal_ll_base_addr_t i2ctrn_reg_addr;
    hal_ll_base_addr_t __unused_6[ 3 ];
    hal_ll_base_addr_t i2crcv_reg_addr;
} hal_ll_i2c_base_handle_t;

/*!< @brief I2C hw specific structure */
typedef struct
{
    hal_ll_base_addr_t base;
    hal_ll_pin_name_t module_index;
    hal_ll_i2c_pins_t pins;
    uint32_t speed;
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

    HAL_LL_I2C_MASTER_ERROR = ( -1 )
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
    HAL_LL_I2C_MASTER_TIMEOUT_REPEATED_START,
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
 * HAL_LL_I2C_MASTER_SPEED_FULL -- Speed set at 400K
 */
typedef enum
{
    HAL_LL_I2C_MASTER_SPEED_STANDARD = 0,
    HAL_LL_I2C_MASTER_SPEED_FULL
} hal_ll_i2c_master_speed_t;

// ------------------------------------------------------------------ CONSTANTS

// ------------------------------------------------------------------ VARIABLES

/*!< @brief I2C hardware specific info */
static hal_ll_i2c_hw_specifics_map_t hal_ll_i2c_hw_specifics_map[ I2C_MODULE_COUNT + 1 ] =
{
    #ifdef I2C_MODULE
    { HAL_LL_I2C1CON_ADDRESS, hal_ll_i2c_module_num( I2C_MODULE ), { HAL_LL_PIN_NC,HAL_LL_PIN_NC }, HAL_LL_I2C_MASTER_SPEED_100K , 0, HAL_LL_I2C_DEFAULT_PASS_COUNT },
    #endif
    #ifdef I2C_MODULE_1
    { HAL_LL_I2C1CON_ADDRESS, hal_ll_i2c_module_num( I2C_MODULE_1 ), { HAL_LL_PIN_NC,HAL_LL_PIN_NC }, HAL_LL_I2C_MASTER_SPEED_100K , 0, HAL_LL_I2C_DEFAULT_PASS_COUNT },
    #endif
    #ifdef I2C_MODULE_2
    { HAL_LL_I2C2CON_ADDRESS, hal_ll_i2c_module_num( I2C_MODULE_2 ), { HAL_LL_PIN_NC,HAL_LL_PIN_NC }, HAL_LL_I2C_MASTER_SPEED_100K , 0, HAL_LL_I2C_DEFAULT_PASS_COUNT },
    #endif
    #ifdef I2C_MODULE_3
    { HAL_LL_I2C3CON_ADDRESS, hal_ll_i2c_module_num( I2C_MODULE_3 ), { HAL_LL_PIN_NC,HAL_LL_PIN_NC }, HAL_LL_I2C_MASTER_SPEED_100K , 0, HAL_LL_I2C_DEFAULT_PASS_COUNT },
    #endif
    #ifdef I2C_MODULE_4
    { HAL_LL_I2C4CON_ADDRESS, hal_ll_i2c_module_num( I2C_MODULE_4 ), { HAL_LL_PIN_NC,HAL_LL_PIN_NC }, HAL_LL_I2C_MASTER_SPEED_100K , 0, HAL_LL_I2C_DEFAULT_PASS_COUNT },
    #endif
    #ifdef I2C_MODULE_5
    { HAL_LL_I2C5CON_ADDRESS, hal_ll_i2c_module_num( I2C_MODULE_5 ), { HAL_LL_PIN_NC,HAL_LL_PIN_NC }, HAL_LL_I2C_MASTER_SPEED_100K , 0, HAL_LL_I2C_DEFAULT_PASS_COUNT },
    #endif

    { HAL_LL_MODULE_ERROR, HAL_LL_MODULE_ERROR, { HAL_LL_PIN_NC, HAL_LL_PIN_NC }, 0 , 0, 0 }
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
static bool hal_ll_i2c_master_is_idle( hal_ll_i2c_base_handle_t *hal_ll_hw_reg );

/**
  * @brief  Wait to get I2C busy bit value.
  *
  * Wait to checks I2C busy bit value and returns true if device is in operation.
  * Else returns false.
  *
  * @param[in]  map - Object specific context handler.
  * @param[in]  errorCode - Error code.
  *
  * @return hal_ll_err_t.
  */
static hal_ll_err_t hal_ll_i2c_master_wait_for_idle( hal_ll_i2c_hw_specifics_map_t *map, uint8_t errorCode );

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
  * @brief  Configuration of pins.
  *
  * Sets mode of SCL and SDA pins ( Input/Output) in I2C.
  *
  * @param[in]  map - Object specific context handler.
  *
  * @return None
  */
static void hal_ll_i2c_master_set_pins( hal_ll_i2c_hw_specifics_map_t *map );

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
static void hal_ll_i2c_hw_set_module_power( hal_ll_i2c_hw_specifics_map_t *map, bool hal_ll_state );

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
  * @brief  Full I2C module initialization procedure.
  *
  * Initializes I2C module on hardware level, based on beforehand
  * set configuration and module handler. Sets adequate pin alternate functions.
  * Initializes module clock.
  *
  * @param[in]  map - Object specific context handler.
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
static hal_ll_err_t hal_ll_i2c_master_stop( hal_ll_i2c_hw_specifics_map_t *map );


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

    hal_ll_i2c_pin_id index_list[I2C_MODULE_COUNT] = {HAL_LL_PIN_NC,HAL_LL_PIN_NC};
    uint16_t pin_check_result;

    if ( HAL_LL_PIN_NC == ( pin_check_result = hal_ll_i2c_master_check_pins( scl, sda, &index_list, handle_map ))  ) {
        return HAL_LL_I2C_MASTER_WRONG_PINS;
    };

    if ( ( hal_ll_i2c_hw_specifics_map[ pin_check_result ].pins.pin_scl != scl ) ||
         ( hal_ll_i2c_hw_specifics_map[ pin_check_result ].pins.pin_sda != sda ) ){
        // Map new pins
        hal_ll_i2c_master_map_pins( pin_check_result, &index_list );
        handle_map[ pin_check_result ]->init_ll_state = false;
    }

    *hal_module_id = pin_check_result;

    hal_ll_module_state[ pin_check_result ].hal_ll_i2c_master_handle = ( handle_t * )&hal_ll_i2c_hw_specifics_map[ pin_check_result ].base;

    handle_map[pin_check_result]->hal_ll_i2c_master_handle = ( handle_t * )&hal_ll_module_state[ pin_check_result ].hal_ll_i2c_master_handle;

    return HAL_LL_I2C_MASTER_SUCCESS;
}

hal_ll_err_t hal_ll_module_configure_i2c( handle_t *handle ) {
    hal_ll_i2c_hw_specifics_map_local = hal_ll_get_specifics ( hal_ll_i2c_get_module_state_address );
    hal_ll_i2c_pin_id index_list [ I2C_MODULE_COUNT ] = {HAL_LL_PIN_NC,HAL_LL_PIN_NC};
    uint16_t pin_check_result;

    if ( HAL_LL_PIN_NC == ( pin_check_result = hal_ll_i2c_master_check_pins( hal_ll_i2c_hw_specifics_map_local->pins.pin_scl,
                                                                             hal_ll_i2c_hw_specifics_map_local->pins.pin_sda, &index_list, (void *)0 ) ) ){
        return HAL_LL_I2C_MASTER_WRONG_PINS;
    };

    hal_ll_i2c_init( hal_ll_i2c_hw_specifics_map_local );

    hal_ll_module_state[ pin_check_result ].hal_ll_i2c_master_handle = (handle_t *)&hal_ll_i2c_hw_specifics_map[ pin_check_result ].base;
    hal_ll_module_state[ pin_check_result ].init_ll_state = true;

    return HAL_LL_I2C_MASTER_SUCCESS;
}

hal_ll_err_t hal_ll_i2c_master_set_speed( handle_t *handle, uint32_t speed ) {
    low_level_handle = hal_ll_i2c_get_handle;
    hal_ll_i2c_hw_specifics_map_local = hal_ll_get_specifics( hal_ll_i2c_get_module_state_address );

    low_level_handle->init_ll_state = false;

    hal_ll_i2c_hw_specifics_map_local->speed = hal_ll_i2c_get_speed( speed );

    hal_ll_i2c_init( hal_ll_i2c_hw_specifics_map_local );

    low_level_handle->init_ll_state = true;

    return hal_ll_i2c_hw_specifics_map_local->speed;
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

    if( HAL_LL_I2C_MASTER_SUCCESS !=  hal_ll_i2c_master_write_bare_metal( hal_ll_i2c_hw_specifics_map_local, write_data_buf, len_write_data, HAL_LL_I2C_MASTER_WRITE_THEN_READ ) ) {
        return HAL_LL_I2C_MASTER_TIMEOUT_WRITE;
    }

    if( HAL_LL_I2C_MASTER_SUCCESS  !=  hal_ll_i2c_master_read_bare_metal( hal_ll_i2c_hw_specifics_map_local, read_data_buf, len_read_data, HAL_LL_I2C_MASTER_WRITE_THEN_READ ) ) {
        return HAL_LL_I2C_MASTER_TIMEOUT_READ;
    }

    return HAL_LL_I2C_MASTER_SUCCESS;
}

void hal_ll_i2c_master_close( handle_t *handle ) {
    low_level_handle = hal_ll_i2c_get_handle;
    hal_ll_i2c_hw_specifics_map_local = hal_ll_get_specifics( hal_ll_i2c_get_module_state_address );

    if( NULL != low_level_handle->hal_ll_i2c_master_handle ) {

        low_level_handle->hal_ll_i2c_master_handle = NULL;
        low_level_handle->hal_drv_i2c_master_handle = NULL;
        low_level_handle->init_ll_state = false;

        hal_ll_i2c_hw_specifics_map_local->address = 0;
        hal_ll_i2c_hw_specifics_map_local->timeout = HAL_LL_I2C_DEFAULT_PASS_COUNT;
        hal_ll_i2c_hw_specifics_map_local->speed = HAL_LL_I2C_MASTER_SPEED_100K;

        #ifdef HAL_LL_PERIPHERAL_MODULE_DISABLE
        hal_ll_i2c_hw_set_module_power( hal_ll_i2c_hw_specifics_map_local, false );
        #endif

        hal_ll_i2c_hw_specifics_map_local->pins.pin_scl = HAL_LL_PIN_NC;
        hal_ll_i2c_hw_specifics_map_local->pins.pin_sda = HAL_LL_PIN_NC;
    }
}

// ----------------------------------------------- PRIVATE FUNCTION DEFINITIONS

static hal_ll_err_t hal_ll_i2c_master_write_bare_metal( hal_ll_i2c_hw_specifics_map_t *map, uint8_t *write_data_buf, size_t len_write_data, hal_ll_i2c_master_end_mode_t mode ) {
    hal_ll_i2c_base_handle_t *hal_ll_hw_reg = hal_ll_i2c_get_base_struct( map->base );
    size_t transfer_counter = NULL;
    uint8_t status = NULL;
    uint16_t time_counter = map->timeout;

    status = hal_ll_i2c_master_start( map );
    if( HAL_LL_I2C_MASTER_SUCCESS != status ) {
        return status;
    }

    hal_ll_hw_reg->i2ctrn_reg_addr =  map->address << 1 ;

    status = hal_ll_i2c_master_check_write( map );
    hal_ll_i2c_master_wait_for_idle ( map, HAL_LL_I2C_MASTER_TIMEOUT_WRITE );

    if( HAL_LL_I2C_MASTER_SUCCESS != status ) {
        return status;
    }

    for ( transfer_counter = 0; transfer_counter < len_write_data; transfer_counter++ ){
        hal_ll_hw_reg->i2ctrn_reg_addr = write_data_buf[ transfer_counter ];

        status = hal_ll_i2c_master_check_write( map );
        hal_ll_i2c_master_wait_for_idle ( map, HAL_LL_I2C_MASTER_TIMEOUT_WRITE );
        if( HAL_LL_I2C_MASTER_SUCCESS != status ) {
            return status;
        }
    }

    if ( HAL_LL_I2C_MASTER_END_MODE_STOP == mode ){
        hal_ll_i2c_master_stop ( map );
    } else if ( HAL_LL_I2C_MASTER_WRITE_THEN_READ == mode ){
        hal_ll_i2c_master_restart ( map );
    }

    if ( check_reg_bit( &hal_ll_hw_reg->i2cstat_reg_addr,  HAL_LL_I2CSTAT_IWCOL_BIT )){
        return HAL_LL_I2C_MASTER_ERROR;
    } else {
        while ( check_reg_bit( &hal_ll_hw_reg->i2cstat_reg_addr, HAL_LL_I2CSTAT_TBF_BIT )){
            if ( map->timeout ){
                if ( !time_counter-- )
                    return HAL_LL_I2C_MASTER_TIMEOUT_WRITE;
            }
        }
        hal_ll_i2c_master_wait_for_idle ( map, HAL_LL_I2C_MASTER_TIMEOUT_WRITE );

        if ( check_reg_bit( &hal_ll_hw_reg->i2cstat_reg_addr, HAL_LL_I2CSTAT_ACKSTAT_BIT ))
            return HAL_LL_I2C_MASTER_ERROR;
        else
            return HAL_LL_I2C_MASTER_SUCCESS;
    }
}

static hal_ll_err_t hal_ll_i2c_master_read_bare_metal( hal_ll_i2c_hw_specifics_map_t *map, uint8_t *read_data_buf, size_t len_read_data, hal_ll_i2c_master_end_mode_t mode ){
    hal_ll_i2c_base_handle_t *hal_ll_hw_reg = hal_ll_i2c_get_base_struct( map->base );
    size_t transfer_counter = NULL;
    uint8_t status = NULL;
    uint16_t time_counter = map->timeout;

    if( HAL_LL_I2C_MASTER_WRITE_THEN_READ != mode ) {
        status = hal_ll_i2c_master_start( map );
        if( HAL_LL_I2C_MASTER_SUCCESS != status ) {
            return status;
        }
    }

    hal_ll_hw_reg->i2ctrn_reg_addr = (( map->address << 1 ) | 0x01 );

    status = hal_ll_i2c_master_check_write( map );
    hal_ll_i2c_master_wait_for_idle ( map, HAL_LL_I2C_MASTER_TIMEOUT_WRITE );

    for( transfer_counter = 0; transfer_counter < len_read_data ; transfer_counter++ ){

        set_reg_bit( &hal_ll_hw_reg->i2ccon_reg_addr, HAL_LL_I2CCON_RCEN_BIT );

        while ( check_reg_bit( &hal_ll_hw_reg->i2ccon_reg_addr, HAL_LL_I2CCON_RCEN_BIT )){
            if ( map->timeout ){
                if ( !time_counter-- )
                    return HAL_LL_I2C_MASTER_TIMEOUT_READ;
            }
        }

        clear_reg_bit( &hal_ll_hw_reg->i2cstat_reg_addr, HAL_LL_I2CSTAT_I2COV_BIT );

        read_data_buf[ transfer_counter ] = read_reg( &hal_ll_hw_reg->i2crcv_reg_addr );

        if ( transfer_counter < ( len_read_data - 1) ){
            clear_reg_bit ( &hal_ll_hw_reg->i2ccon_reg_addr , HAL_LL_I2CCON_ACKDT_BIT );
        } else {
            set_reg_bit ( &hal_ll_hw_reg->i2ccon_reg_addr , HAL_LL_I2CCON_ACKDT_BIT );
        }

        set_reg_bit( &hal_ll_hw_reg->i2ccon_reg_addr, HAL_LL_I2CCON_ACKEN_BIT );

        time_counter = map->timeout;
        while ( check_reg_bit( &hal_ll_hw_reg->i2ccon_reg_addr, HAL_LL_I2CCON_ACKEN_BIT ) ){
            if ( map->timeout ){
                if ( !time_counter-- )
                    return HAL_LL_I2C_MASTER_TIMEOUT_READ;
            }
        }
    }
    hal_ll_i2c_master_stop ( map );

    return HAL_LL_I2C_MASTER_SUCCESS;
}

static hal_ll_err_t hal_ll_i2c_master_check_write( hal_ll_i2c_hw_specifics_map_t *map ) {
    hal_ll_i2c_base_handle_t *hal_ll_hw_reg = hal_ll_i2c_get_base_struct( map->base );
    uint16_t time_counter = map->timeout;

    while ( check_reg_bit( &hal_ll_hw_reg->i2cstat_reg_addr, HAL_LL_I2CSTAT_TBF_BIT ) ) {
        if ( map->timeout ) {
            if ( !time_counter-- )
                return HAL_LL_I2C_MASTER_TIMEOUT_WRITE;
        }
    }

    return HAL_LL_I2C_MASTER_SUCCESS;
}

static hal_ll_err_t hal_ll_i2c_master_start( hal_ll_i2c_hw_specifics_map_t *map ) {
    hal_ll_i2c_base_handle_t *hal_ll_hw_reg = hal_ll_i2c_get_base_struct( map->base );
    uint16_t time_counter = map->timeout;

    hal_ll_i2c_master_wait_for_idle ( map, HAL_LL_I2C_MASTER_TIMEOUT_START );

    set_reg_bit ( &hal_ll_hw_reg->i2ccon_reg_addr, HAL_LL_I2CCON_SEN_BIT );

    if ( check_reg_bit( &hal_ll_hw_reg->i2cstat_reg_addr, HAL_LL_I2CSTAT_BCL_BIT ))
        return HAL_LL_I2C_MASTER_ERROR;

    time_counter = map->timeout;

    while ( check_reg_bit( &hal_ll_hw_reg->i2ccon_reg_addr , HAL_LL_I2CCON_SEN_BIT ) ){
        if ( map->timeout ) {
            if ( !time_counter-- )
                return HAL_LL_I2C_MASTER_TIMEOUT_START;
        }
    }

    return HAL_LL_I2C_MASTER_SUCCESS;
}

static hal_ll_err_t hal_ll_i2c_master_stop( hal_ll_i2c_hw_specifics_map_t *map ) {
    hal_ll_i2c_base_handle_t *hal_ll_hw_reg = hal_ll_i2c_get_base_struct( map->base  );
    uint16_t time_counter = map->timeout;

    hal_ll_i2c_master_wait_for_idle ( map, HAL_LL_I2C_MASTER_TIMEOUT_STOP );

    set_reg_bit ( &hal_ll_hw_reg->i2ccon_reg_addr, HAL_LL_I2CCON_PEN_BIT );

    time_counter = map->timeout;

    while ( check_reg_bit( &hal_ll_hw_reg->i2ccon_reg_addr , HAL_LL_I2CCON_PEN_BIT ) ){
        if ( map->timeout ) {
            if ( !time_counter-- )
                return HAL_LL_I2C_MASTER_TIMEOUT_STOP;
        }
    }

   return HAL_LL_I2C_MASTER_SUCCESS;
}

static hal_ll_err_t hal_ll_i2c_master_restart( hal_ll_i2c_hw_specifics_map_t *map ){
    hal_ll_i2c_base_handle_t *hal_ll_hw_reg = hal_ll_i2c_get_base_struct( map->base );

    uint16_t time_counter = map->timeout;

    hal_ll_i2c_master_wait_for_idle ( map, HAL_LL_I2C_MASTER_TIMEOUT_REPEATED_START );

    set_reg_bit ( &hal_ll_hw_reg->i2ccon_reg_addr, HAL_LL_I2CCON_RSEN_BIT );

    if ( check_reg_bit( &hal_ll_hw_reg->i2cstat_reg_addr , HAL_LL_I2CSTAT_BCL_BIT ) || check_reg_bit( &hal_ll_hw_reg->i2cstat_reg_addr , HAL_LL_I2CSTAT_IWCOL_BIT ) ){
        return HAL_LL_I2C_MASTER_ERROR;
    }

    while ( check_reg_bit( &hal_ll_hw_reg->i2ccon_reg_addr , HAL_LL_I2CCON_RSEN_BIT ) ){
        if ( map->timeout ) {
            if ( !time_counter-- )
                return HAL_LL_I2C_MASTER_TIMEOUT_REPEATED_START;
        }
    }
}

static hal_ll_err_t hal_ll_i2c_master_wait_for_idle( hal_ll_i2c_hw_specifics_map_t *map, uint8_t errorCode ){
    hal_ll_i2c_base_handle_t *hal_ll_hw_reg = hal_ll_i2c_get_base_struct( map->base );
    uint16_t time_counter = map->timeout;

    while ( !hal_ll_i2c_master_is_idle( hal_ll_hw_reg ) ){
        if ( map->timeout ){
            if ( !time_counter-- )
                return errorCode;
        }
    }
}

static bool hal_ll_i2c_master_is_idle( hal_ll_i2c_base_handle_t *hal_ll_hw_reg ) {
    return !( ( read_reg( &hal_ll_hw_reg->i2ccon_reg_addr ) & HAL_LL_I2C_IDLE_MASK ) || check_reg_bit( &hal_ll_hw_reg->i2cstat_reg_addr, HAL_LL_I2CSTAT_TRSTAT_BIT ) );
}

static hal_ll_i2c_hw_specifics_map_t *hal_ll_get_specifics( handle_t handle ) {
    uint8_t hal_ll_module_count = sizeof( hal_ll_module_state ) / ( sizeof( hal_ll_i2c_master_handle_register_t ) );
    static uint8_t hal_ll_module_error = hal_ll_module_count;

    while( hal_ll_module_count-- ) {
         if ( hal_ll_i2c_get_base_from_hal_handle == hal_ll_i2c_hw_specifics_map[ hal_ll_module_count ].base ) {
            return &hal_ll_i2c_hw_specifics_map[ hal_ll_module_count ];
        }
    }

    return &hal_ll_i2c_hw_specifics_map[ hal_ll_module_error ];
}

static hal_ll_pin_name_t hal_ll_i2c_master_check_pins( hal_ll_pin_name_t scl, hal_ll_pin_name_t sda, hal_ll_i2c_pin_id *index_list, hal_ll_i2c_master_handle_register_t *handle_map ) {
    static const uint16_t scl_map_size = ( sizeof( hal_ll_i2c_scl_map ) / sizeof( hal_ll_i2c_pin_map_t ) );
    static const uint16_t sda_map_size = ( sizeof( hal_ll_i2c_sda_map ) / sizeof( hal_ll_i2c_pin_map_t ) );
    uint8_t hal_ll_module_id = 0;
    uint8_t index_counter = 0;
    uint16_t scl_index;
    uint16_t sda_index;

    for ( scl_index = 0; scl_index < scl_map_size; scl_index++ ) {
        if ( hal_ll_i2c_scl_map[ scl_index ].pin == scl ) {
            for ( sda_index = 0; sda_index < sda_map_size; sda_index++ ) {
                if ( hal_ll_i2c_sda_map[ sda_index ].pin == sda ) {
                    if ( hal_ll_i2c_scl_map[ scl_index ].module_index == hal_ll_i2c_sda_map[ sda_index ].module_index ) {
                        // Get module number
                        hal_ll_module_id = hal_ll_i2c_scl_map[ scl_index ].module_index;
                        // Map pin names
                        index_list[hal_ll_module_id]->pin_scl = scl_index;
                        index_list[hal_ll_module_id]->pin_sda = sda_index;

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

static void hal_ll_i2c_hw_set_module_power( hal_ll_i2c_hw_specifics_map_t *map, bool hal_ll_state ) {
    switch ( map->module_index )
    {
        #ifdef HAL_LL_PMD5_ADDRESS
            #ifdef I2C_MODULE
            case( hal_ll_i2c_module_num( I2C_MODULE ) ):
                ( hal_ll_state )?( clear_reg_bit( HAL_LL_PMD5_ADDRESS, HAL_LL_I2C1MD_ENABLE_BIT ) ):( set_reg_bit( HAL_LL_PMD5_ADDRESS, HAL_LL_I2C1MD_ENABLE_BIT ) );
                break;
            #endif

            #ifdef I2C_MODULE_1
            case( hal_ll_i2c_module_num( I2C_MODULE_1 ) ):
                ( hal_ll_state )?( clear_reg_bit( HAL_LL_PMD5_ADDRESS, HAL_LL_I2C1MD_ENABLE_BIT ) ):( set_reg_bit( HAL_LL_PMD5_ADDRESS, HAL_LL_I2C1MD_ENABLE_BIT ) );
                break;
            #endif

            #ifdef I2C_MODULE_2
            case( hal_ll_i2c_module_num( I2C_MODULE_2 ) ):
                ( hal_ll_state )?( clear_reg_bit( HAL_LL_PMD5_ADDRESS, HAL_LL_I2C2MD_ENABLE_BIT ) ):( set_reg_bit( HAL_LL_PMD5_ADDRESS, HAL_LL_I2C2MD_ENABLE_BIT ) );
                break;
            #endif

            #ifdef I2C_MODULE_3
            case( hal_ll_i2c_module_num( I2C_MODULE_3 ) ):
                ( hal_ll_state )?( clear_reg_bit( HAL_LL_PMD5_ADDRESS, HAL_LL_I2C3MD_ENABLE_BIT ) ):( set_reg_bit( HAL_LL_PMD5_ADDRESS, HAL_LL_I2C3MD_ENABLE_BIT ) );
                break;
            #endif

            #ifdef I2C_MODULE_4
            case( hal_ll_i2c_module_num( I2C_MODULE_4 ) ):
                ( hal_ll_state )?( clear_reg_bit( HAL_LL_PMD5_ADDRESS, HAL_LL_I2C4MD_ENABLE_BIT ) ):( set_reg_bit( HAL_LL_PMD5_ADDRESS, HAL_LL_I2C4MD_ENABLE_BIT ) );
                break;
            #endif

            #ifdef I2C_MODULE_5
            case( hal_ll_i2c_module_num( I2C_MODULE_5 ) ):
                ( hal_ll_state )?( clear_reg_bit( HAL_LL_PMD5_ADDRESS, HAL_LL_I2C5MD_ENABLE_BIT ) ):( set_reg_bit( HAL_LL_PMD5_ADDRESS, HAL_LL_I2C5MD_ENABLE_BIT ) );
                break;
            #endif
        #endif

            default:
                break;
    }
}

static uint32_t hal_ll_i2c_get_speed( uint32_t bit_rate ) {
    if ( bit_rate <= HAL_LL_I2C_MASTER_SPEED_FULL ) {
        if ( bit_rate <= HAL_LL_I2C_MASTER_SPEED_STANDARD ) {
            return HAL_LL_I2C_MASTER_SPEED_100K;
        } else if ( bit_rate <= HAL_LL_I2C_MASTER_SPEED_FULL ) {
            return HAL_LL_I2C_MASTER_SPEED_400K;
        } else {
            return HAL_LL_I2C_MASTER_SPEED_400K;
        }
    } else {
        if ( bit_rate <= HAL_LL_I2C_MASTER_SPEED_100K ) {
            return HAL_LL_I2C_MASTER_SPEED_100K;
        } else if ( bit_rate <= HAL_LL_I2C_MASTER_SPEED_400K ) {
            return HAL_LL_I2C_MASTER_SPEED_400K;
        } else {
            return HAL_LL_I2C_MASTER_SPEED_400K;
        }
    }
    return HAL_LL_I2C_MASTER_SPEED_100K;
}

static void hal_ll_i2c_master_set_pins( hal_ll_i2c_hw_specifics_map_t *map ){
    hal_ll_gpio_pin_t pin_name;

    hal_ll_gpio_configure_pin ( &pin_name, map->pins.pin_scl, HAL_LL_GPIO_DIGITAL_OUTPUT );
    hal_ll_gpio_configure_pin ( &pin_name, map->pins.pin_sda, HAL_LL_GPIO_DIGITAL_INPUT );
}

static void hal_ll_i2c_master_map_pins( uint8_t module_index, hal_ll_i2c_pin_id *index_list ) {
    // Map new pins
    hal_ll_i2c_hw_specifics_map[module_index]->pins.pin_scl = hal_ll_i2c_scl_map[ index_list[module_index]->pin_scl ].pin;
    hal_ll_i2c_hw_specifics_map[module_index]->pins.pin_sda = hal_ll_i2c_sda_map[ index_list[module_index]->pin_sda ].pin;
}

static void hal_ll_i2c_init( hal_ll_i2c_hw_specifics_map_t *map) {
    hal_ll_i2c_base_handle_t *hal_ll_hw_reg = hal_ll_i2c_get_base_struct( map->base );
    hal_ll_hw_reg->i2ccon_reg_addr = 0;

    #ifdef HAL_LL_PERIPHERAL_MODULE_DISABLE
    hal_ll_i2c_hw_set_module_power ( map, true );
    #endif

    set_reg_bit( &hal_ll_hw_reg->i2ccon_reg_addr, HAL_LL_I2CCON_ON_BIT );

    if ( map->speed <= HAL_LL_I2C_MASTER_SPEED_100K ){
        set_reg_bit( &hal_ll_hw_reg->i2ccon_reg_addr, HAL_LL_I2CCON_DISSLW_BIT );
    } else {
        clear_reg_bit( &hal_ll_hw_reg->i2ccon_reg_addr, HAL_LL_I2CCON_DISSLW_BIT );
    }

    #ifdef PIC32MXxx
    uint8_t __tmp = (*( uint32_t * )HAL_LL_OSCCON_ADDRESS >> 19) & 0x3;
    __tmp = PB_Clock_Value_Mx(__tmp);
    write_reg( &hal_ll_hw_reg->i2cbrg_reg_addr,(((Get_Fosc_kHz()*1000/__tmp)/( map->speed*2 )) - 2) );
    #elif defined(PIC32MZxx)
    write_reg( &hal_ll_hw_reg->i2cbrg_reg_addr,((( Get_Fosc_kHz()*1000/PB_Clock_Divisor )/( map->speed*2 )) - 2));
    #endif

    write_reg( &hal_ll_hw_reg->i2cstat_reg_addr, HAL_LL_I2CXSTAT_MASK );
}

// ------------------------------------------------------------------------- END
