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

#include "hal_ll_pmc.h"
#include "hal_ll_gpio.h"
#include "hal_ll_i2c_master.h"
#include "hal_ll_i2c_pin_map.h"

/*!< @brief Local handle list */
static volatile hal_ll_i2c_master_handle_register_t hal_ll_module_state[I2C_MODULE_COUNT] = { (handle_t *)NULL, (handle_t *)NULL, false };

// ------------------------------------------------------------- PRIVATE MACROS
/*!< @brief Macros used for calculating speed value and configuring the clock register */
#define hal_ll_get_system_clock (Get_Fosc_kHz() * 1000)
#define hal_ll_i2c_get_divider(temp_div,speed) (hal_ll_get_system_clock / (2 * temp_div * speed)) - 3U
/*!< @brief Helper macro for getting hal_ll_module_state address */
#define hal_ll_i2c_get_module_state_address ((hal_ll_i2c_master_handle_register_t *)*handle)
/*!< @brief Helper macro for getting module specific control register structure base address // first register address */
#define hal_ll_i2c_get_handle (hal_ll_i2c_master_handle_register_t *)hal_ll_i2c_get_module_state_address->hal_ll_i2c_master_handle
/*!< @brief Helper macro for getting module specific control register structure */
#define hal_ll_i2c_get_base_struct(_handle) ((hal_ll_i2c_base_handle_t *)_handle)
/*!< @brief Helper macro for getting module specific base address directly from HAL layer handle */
#define hal_ll_i2c_get_base_from_hal_handle ((hal_ll_i2c_hw_specifics_map_t *)((hal_ll_i2c_master_handle_register_t *)\
                                            (((hal_ll_i2c_master_handle_register_t *)(handle))->hal_ll_i2c_master_handle))->hal_ll_i2c_master_handle)->base

/*!< @brief Default I2C bit-rate if no speed is set */
#define HAL_LL_I2C_MASTER_SPEED_100K                100000UL
#define HAL_LL_I2C_MASTER_LOW_DIVIDER_SPEED_LIMIT   384000UL
#define HAL_LL_I2C_MASTER_SPEED_400K                400000UL

/*!< @brief Default pass count value upon reset */
#define HAL_LL_I2C_DEFAULT_PASS_COUNT 0xFFFFU

/*!< @brief Macro used for timeout */
#define HAL_LL_I2C_LOOP_INDEX 10000U

/*!< @brief Macros defining register bit location */
#define HAL_LL_TWIHS_SR_TXCOMP_BIT      0
#define HAL_LL_TWIHS_SR_RXRDY_BIT       1
#define HAL_LL_TWIHS_SR_TXRDY_BIT       2
#define HAL_LL_TWIHS_SR_ARBLST_BIT      9

#define HAL_LL_TWIHS_CR_START_BIT       0
#define HAL_LL_TWIHS_CR_STOP_BIT        1
#define HAL_LL_TWIHS_CR_MSEN_BIT        2
#define HAL_LL_TWIHS_CR_SVDIS_BIT       5
#define HAL_LL_TWIHS_CR_SWRST_BIT       7

#define HAL_LL_TWIHS_MMR_MREAD_BIT      12
#define HAL_LL_TWIHS_MMR_DADR_START_BIT 16

#define HAL_LL_PID_TWIHS2_BIT           9
#define HAL_LL_PID_TWIHS0_BIT           19
#define HAL_LL_PID_TWIHS1_BIT           20

/*!< @brief Macros for speed calculation */
#define HAL_LL_TWIHS_CWGR_CLKDIV_MAX    7

// -------------------------------------------------------------- PRIVATE TYPES
/*!< @brief I2C register structure */
typedef struct
{
    hal_ll_base_addr_t cr;
    hal_ll_base_addr_t mmr;
    hal_ll_base_addr_t smr;
    hal_ll_base_addr_t iadr;
    hal_ll_base_addr_t cwgr;
    hal_ll_base_addr_t _unused[3];
    hal_ll_base_addr_t sr;
    hal_ll_base_addr_t ier;
    hal_ll_base_addr_t idr;
    hal_ll_base_addr_t imr;
    hal_ll_base_addr_t rhr;
    hal_ll_base_addr_t thr;
    hal_ll_base_addr_t smbtr;
} hal_ll_i2c_base_handle_t;

/*!< @brief I2C hw specific structure */
typedef struct
{
    hal_ll_base_addr_t base;
    uint8_t module_index;
    hal_ll_i2c_pins_t pins;
    uint32_t speed;
    uint8_t address;
    uint16_t timeout;
} hal_ll_i2c_hw_specifics_map_t;

/*!< @brief I2C hw specific module values */
typedef struct
{
    hal_ll_pin_name_t pin_scl;
    hal_ll_pin_name_t pin_sda;
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
    HAL_LL_I2C_MASTER_TIMEOUT_STOP,
    HAL_LL_I2C_MASTER_TIMEOUT_WRITE,
    HAL_LL_I2C_MASTER_TIMEOUT_READ,
    HAL_LL_I2C_MASTER_ARBITRATION_LOST,
    HAL_LL_I2C_MASTER_TIMEOUT_INIT
} hal_ll_i2c_master_timeout_t;

/**
 * @brief Enum containing predefined module standard speed values.
 *
 * Enum values:
 * HAL_LL_I2C_MASTER_SPEED_STANDARD -- Speed set at 100K
 * HAL_LL_I2C_MASTER_SPEED_FULL -- Speed set at 400K
 * HAL_LL_I2C_MASTER_SPEED_FAST -- Speed set at 1M
 */
typedef enum
{
    HAL_LL_I2C_MASTER_SPEED_STANDARD = 0,
    HAL_LL_I2C_MASTER_SPEED_FULL,
    HAL_LL_I2C_MASTER_SPEED_FAST
} hal_ll_i2c_master_speed_t;

// ------------------------------------------------------------------ VARIABLES
/*!< @brief I2C hardware specific info */
static hal_ll_i2c_hw_specifics_map_t hal_ll_i2c_hw_specifics_map[] =
{
    #ifdef I2C_MODULE_0
    {HAL_LL_I2C0_BASE_ADDRESS, hal_ll_i2c_module_num(I2C_MODULE_0), {HAL_LL_PIN_NC, 0, HAL_LL_PIN_NC, 0}, HAL_LL_I2C_MASTER_SPEED_100K , 0, HAL_LL_I2C_DEFAULT_PASS_COUNT},
    #endif
    #ifdef I2C_MODULE_1
    {HAL_LL_I2C1_BASE_ADDRESS, hal_ll_i2c_module_num(I2C_MODULE_1), {HAL_LL_PIN_NC, 0, HAL_LL_PIN_NC, 0}, HAL_LL_I2C_MASTER_SPEED_100K , 0, HAL_LL_I2C_DEFAULT_PASS_COUNT},
    #endif
    #ifdef I2C_MODULE_2
    {HAL_LL_I2C2_BASE_ADDRESS, hal_ll_i2c_module_num(I2C_MODULE_2), {HAL_LL_PIN_NC, 0, HAL_LL_PIN_NC, 0}, HAL_LL_I2C_MASTER_SPEED_100K , 0, HAL_LL_I2C_DEFAULT_PASS_COUNT},
    #endif

    {HAL_LL_MODULE_ERROR, HAL_LL_MODULE_ERROR, {HAL_LL_PIN_NC, 0, HAL_LL_PIN_NC, 0}, 0, 0, 0}
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
  * @param[in]  *index_list - Index list address
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
  * @return hal_ll_i2c_hw_specifics_map_t Map address.
  *
  * Returns pre-defined map index address based on handle value,
  * if handle is adequate.
  */
static hal_ll_i2c_hw_specifics_map_t *hal_ll_get_specifics( handle_t handle );

/**
  * @brief  Get adequate I2C bit-rate value.
  *
  * Returns one of pre-defined bit-rate values,
  * or the closest bit-rate based on bit_rate
  * value passed to the function.
  *
  * @param[in]  bit_rate - I2C bit rate.
  * @return uint32_t Adequate bit-rate value.
  *
  * Returns adequate value to be latter written into bare metal register address.
  * Take into consideration that this returns a predefined value.
  *
  * HAL_LL_I2C_MASTER_SPEED_100K -- 100Kbit/s
  * HAL_LL_I2C_MASTER_SPEED_400K -- 400Kbit/s
  * HAL_LL_I2C_MASTER_SPEED_1M -- 1Mbit/s
  * HAL_LL_I2C_MASTER_SPEED_3M2 -- 3.2Mbit/s
  */
static uint32_t hal_ll_i2c_get_speed( hal_ll_i2c_hw_specifics_map_t *map );

/**
  * @brief  Enable clock for I2C module on hardware level.
  *
  * Initializes I2C module clock on hardware level, based on beforehand
  * set configuration and module handler.
  *
  * @param[in]  map - Object specific context handler.
  * @param[in]  hal_ll_stat - True(enable clock)/False(disable clock).
  *
  * @return None
  */
static void hal_ll_i2c_master_set_clock( hal_ll_i2c_hw_specifics_map_t *map, bool hal_ll_state );

/**
  * @brief  Initialize I2C module on hardware level.
  *
  * Initializes I2C module on hardware level, based on beforehand
  * set configuration and module handler.
  *
  * @param[in]  map - Object specific context handler.
  * @return hal_ll_err_t Module specific return values.
  *
  * Returns one of pre-defined values.
  * Take into consideration that this is hardware specific.
  */
static hal_ll_err_t hal_ll_i2c_hw_init( hal_ll_i2c_hw_specifics_map_t *map );

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
  * @brief  Sets I2C pin alternate function state.
  *
  * Sets adequate value for alternate function settings.
  * This function must be called if I2C is to work.
  * Based on value of hal_ll_state, alternate functions can be
  * set or cleared.
  *
  * @param[in]  map - Object specific context handler.
  * @param[in]  hal_ll_state - Init/De-init
  *
  * @return  None
  */
static void hal_ll_i2c_master_alternate_functions_set_state( hal_ll_i2c_hw_specifics_map_t *map, bool hal_ll_state );

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
static hal_ll_err_t hal_ll_i2c_init( hal_ll_i2c_hw_specifics_map_t *map );

/**
  * @brief  Configure I2C module for data transfer.
  *
  * @param[in]  hal_ll_hw_reg  - I2C module base address.
  * @param[in]  slave_address - client address.
  * @param[in]  read - defines either it is read operation or write.
  * @return void None.
  */
static void hal_ll_i2c_master_configure_transfer( hal_ll_i2c_base_handle_t *hal_ll_hw_reg, uint8_t slave_address, bool read );

/**
  * @brief  Generates start signal on I2C bus.
  *
  * Generates a start signal on the I2C bus.
  *
  * @param[in]  map - Object specific context handler.
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
  * @return hal_ll_err_t Module specific values.
  *
  * Returns one of pre-defined values.
  * Take into consideration that this is hardware specific.
  */
static hal_ll_err_t hal_ll_i2c_master_stop( hal_ll_i2c_hw_specifics_map_t *map );

/**
  * @brief  Perform a read on the I2C bus.
  *
  * Initializes I2C module on hardware level, if not initialized beforehand
  * and continues to perform a read operation on the bus.
  *
  * @param[in]  map - Object specific context handler.
  * @param[in]  readDatabuf - Pointer to data buffer.
  * @param[in]  lenReadData - Number of data to be read.
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
  * @param[in]  writeDatabuf - Pointer to data buffer.
  * @param[in]  lenWriteData - Number of data to be written.
  * @return hal_ll_err_t Module specific values.
  *
  * Returns one of pre-defined values.
  * Take into consideration that this is hardware specific.
  */
static hal_ll_err_t hal_ll_i2c_master_write_bare_metal( hal_ll_i2c_hw_specifics_map_t *map, uint8_t *write_data_buf, size_t len_write_data, hal_ll_i2c_master_end_mode_t mode );

// ------------------------------------------------ PUBLIC FUNCTION DEFINITIONS
hal_ll_err_t hal_ll_i2c_master_register_handle( hal_ll_pin_name_t scl, hal_ll_pin_name_t sda, hal_ll_i2c_master_handle_register_t *handle_map, uint8_t *hal_module_id ) {

    hal_ll_i2c_pin_id index_list[ I2C_MODULE_COUNT ] = { HAL_LL_PIN_NC, HAL_LL_PIN_NC };
    uint16_t pin_check_result;

    // Check if pins are valid
    if ( ( pin_check_result = hal_ll_i2c_master_check_pins( scl, sda, &index_list, handle_map ) ) == HAL_LL_PIN_NC ) {
        return HAL_LL_I2C_MASTER_WRONG_PINS;
    };

    if ( ( hal_ll_i2c_hw_specifics_map[ pin_check_result ].pins.pin_scl.pin_name != scl ) ||
         ( hal_ll_i2c_hw_specifics_map[ pin_check_result ].pins.pin_sda.pin_name != sda ) )
    {
        hal_ll_i2c_master_alternate_functions_set_state( &hal_ll_i2c_hw_specifics_map[ pin_check_result ], false );

        hal_ll_i2c_master_map_pins( pin_check_result, &index_list );

        hal_ll_i2c_master_alternate_functions_set_state( &hal_ll_i2c_hw_specifics_map[ pin_check_result ], true );

        handle_map[ pin_check_result ].init_ll_state = false;
    }

    *hal_module_id = pin_check_result;

    hal_ll_module_state[ pin_check_result ].hal_ll_i2c_master_handle = ( handle_t *)&hal_ll_i2c_hw_specifics_map[ pin_check_result ].base;

    handle_map[ pin_check_result ].hal_ll_i2c_master_handle = ( handle_t *)&hal_ll_module_state[ pin_check_result ].hal_ll_i2c_master_handle;

    return HAL_LL_I2C_MASTER_SUCCESS;
}

hal_ll_err_t hal_ll_module_configure_i2c( handle_t *handle ) {
    hal_ll_i2c_hw_specifics_map_local = hal_ll_get_specifics( hal_ll_i2c_get_module_state_address );
    hal_ll_i2c_master_handle_register_t *hal_handle = ( hal_ll_i2c_master_handle_register_t *)*handle;
    uint8_t pin_check_result = hal_ll_i2c_hw_specifics_map_local->module_index;

    hal_ll_i2c_init( hal_ll_i2c_hw_specifics_map_local );

    hal_ll_module_state[ pin_check_result ].hal_ll_i2c_master_handle = ( handle_t *)&hal_ll_i2c_hw_specifics_map[pin_check_result].base;
    hal_ll_module_state[ pin_check_result ].init_ll_state = true;
    hal_handle->init_ll_state = true;

    return HAL_LL_I2C_MASTER_SUCCESS;
}

hal_ll_err_t hal_ll_i2c_master_set_speed( handle_t *handle, uint32_t speed ) {
    low_level_handle = hal_ll_i2c_get_handle;
    hal_ll_i2c_hw_specifics_map_local = hal_ll_get_specifics( hal_ll_i2c_get_module_state_address );

    low_level_handle->init_ll_state = false;

    hal_ll_i2c_hw_specifics_map_local->speed = speed;

    if ( hal_ll_i2c_init( hal_ll_i2c_hw_specifics_map_local ) != HAL_LL_I2C_MASTER_SUCCESS ) {
        return HAL_LL_I2C_MASTER_TIMEOUT_INIT;
    }

    low_level_handle->init_ll_state = true;

    return hal_ll_i2c_hw_specifics_map_local->speed;
}

void hal_ll_i2c_master_set_timeout( handle_t *handle, uint16_t timeout ) {
    hal_ll_i2c_hw_specifics_map_local = hal_ll_get_specifics( hal_ll_i2c_get_module_state_address );

    if( hal_ll_i2c_hw_specifics_map_local->base != HAL_LL_MODULE_ERROR ) {
        hal_ll_i2c_hw_specifics_map_local->timeout = timeout;
    }
}

void hal_ll_i2c_master_set_slave_address( handle_t *handle, uint8_t addr ) {
    hal_ll_i2c_hw_specifics_map_local = hal_ll_get_specifics( hal_ll_i2c_get_module_state_address );

    if( hal_ll_i2c_hw_specifics_map_local->base != HAL_LL_MODULE_ERROR ) {
        hal_ll_i2c_hw_specifics_map_local->address = addr;
    }
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

    if ( hal_ll_i2c_master_write_bare_metal( hal_ll_i2c_hw_specifics_map_local, write_data_buf, len_write_data, HAL_LL_I2C_MASTER_WRITE_THEN_READ ) != NULL ) {
        return HAL_LL_I2C_MASTER_TIMEOUT_WRITE;
    }

    /**
     * @note Wait for drivers to set-up
     * correctly.
     **/
    #ifdef __TFT_RESISTIVE_TSC2003__
    Delay_22us();
    #endif

    if( hal_ll_i2c_master_read_bare_metal( hal_ll_i2c_hw_specifics_map_local, read_data_buf, len_read_data, HAL_LL_I2C_MASTER_WRITE_THEN_READ ) != NULL ) {
        return HAL_LL_I2C_MASTER_TIMEOUT_READ;
    }

    return HAL_LL_I2C_MASTER_SUCCESS;
}

void hal_ll_i2c_master_close( handle_t *handle ) {
    low_level_handle = hal_ll_i2c_get_handle;
    hal_ll_i2c_hw_specifics_map_local = hal_ll_get_specifics( hal_ll_i2c_get_module_state_address );

    if( low_level_handle->hal_ll_i2c_master_handle != NULL ) {
        low_level_handle->hal_ll_i2c_master_handle = NULL;
        low_level_handle->hal_drv_i2c_master_handle = NULL;

        low_level_handle->init_ll_state = false;

        hal_ll_i2c_hw_specifics_map_local->address = 0;
        hal_ll_i2c_hw_specifics_map_local->timeout = HAL_LL_I2C_DEFAULT_PASS_COUNT;
        hal_ll_i2c_hw_specifics_map_local->speed = HAL_LL_I2C_MASTER_SPEED_100K;

        hal_ll_i2c_master_set_clock( hal_ll_i2c_hw_specifics_map_local, true );
        hal_ll_i2c_master_alternate_functions_set_state( hal_ll_i2c_hw_specifics_map_local, false );
        hal_ll_i2c_master_set_clock( hal_ll_i2c_hw_specifics_map_local, false );

        hal_ll_i2c_hw_specifics_map_local->pins.pin_scl.pin_name = HAL_LL_PIN_NC;
        hal_ll_i2c_hw_specifics_map_local->pins.pin_sda.pin_name = HAL_LL_PIN_NC;
        hal_ll_i2c_hw_specifics_map_local->pins.pin_scl.pin_af = 0;
        hal_ll_i2c_hw_specifics_map_local->pins.pin_sda.pin_af = 0;
    }
}

// ----------------------------------------------- PRIVATE FUNCTION DEFINITIONS
static hal_ll_err_t hal_ll_i2c_master_read_bare_metal( hal_ll_i2c_hw_specifics_map_t *map, uint8_t *read_data_buf, size_t len_read_data, hal_ll_i2c_master_end_mode_t mode ) {
    hal_ll_i2c_base_handle_t *hal_ll_hw_reg = hal_ll_i2c_get_base_struct( map->base );
    uint16_t time_counter = map->timeout;
    size_t transfer_counter = NULL;
    uint8_t status = NULL;
    uint8_t dummy_data;

    #ifdef __TFT_RESISTIVE_TSC2003__
    Delay_1ms();
    #endif

    hal_ll_i2c_master_configure_transfer( hal_ll_hw_reg, map->address, true );

    status = hal_ll_i2c_master_start( map );

    for ( transfer_counter; transfer_counter < len_read_data - 1; transfer_counter++ ) {
        while ( !( check_reg_bit( &hal_ll_hw_reg->sr, HAL_LL_TWIHS_SR_RXRDY_BIT ) ) ) {
            if ( map->timeout ) {
                if ( !time_counter-- )
                    return HAL_LL_I2C_MASTER_TIMEOUT_READ;
            }
        }
        read_data_buf[ transfer_counter ] = read_reg( &hal_ll_hw_reg->rhr );
    }

    if ( ( mode == HAL_LL_I2C_MASTER_END_MODE_STOP ) || ( mode == HAL_LL_I2C_MASTER_WRITE_THEN_READ ) ) {
        status = hal_ll_i2c_master_stop( map );

        // For ATSAM MCUs last data byte should be read after stop bit has beed sent to end the receiving.
        while ( !( check_reg_bit( &hal_ll_hw_reg->sr, HAL_LL_TWIHS_SR_RXRDY_BIT ) ) ) {
            if ( map->timeout ) {
                if ( !time_counter-- )
                    return HAL_LL_I2C_MASTER_TIMEOUT_READ;
            }
        }
        read_data_buf[ transfer_counter ] = read_reg( &hal_ll_hw_reg->rhr );

        while ( !( check_reg_bit( &hal_ll_hw_reg->sr, HAL_LL_TWIHS_SR_TXCOMP_BIT ) ) ) {
            if ( map->timeout ) {
                if ( !time_counter-- )
                    return HAL_LL_I2C_MASTER_TIMEOUT_STOP;
            }
        }
    }

    /*
     * Clear the receive register because ATSAM MCUs with TWIHS
     * registers keep strething the clock line till TXCOMP flag
     * is not set that causes the garbage readings although
     * receiving is finished.
     */
    dummy_data = read_reg( &hal_ll_hw_reg->rhr );

    if( status != HAL_LL_I2C_MASTER_SUCCESS ) {
        return status;
    }

    return HAL_LL_I2C_MASTER_SUCCESS;
}

static hal_ll_err_t hal_ll_i2c_master_write_bare_metal( hal_ll_i2c_hw_specifics_map_t *map, uint8_t *write_data_buf, size_t len_write_data, hal_ll_i2c_master_end_mode_t mode ) {
    hal_ll_i2c_base_handle_t *hal_ll_hw_reg = hal_ll_i2c_get_base_struct( map->base );
    uint16_t time_counter = map->timeout;
    size_t transfer_counter = NULL;
    uint8_t status = NULL;

    hal_ll_i2c_master_configure_transfer( hal_ll_hw_reg, map->address, false );

    for ( transfer_counter; transfer_counter < len_write_data; transfer_counter++ )
    {
        while ( !( check_reg_bit( &hal_ll_hw_reg->sr, HAL_LL_TWIHS_SR_TXRDY_BIT ) ) ) {
            if ( map->timeout ) {
                if ( !time_counter-- )
                    return HAL_LL_I2C_MASTER_TIMEOUT_WRITE;
            }
        }
        write_reg( &hal_ll_hw_reg->thr, write_data_buf[ transfer_counter ] );
    }

    time_counter = map->timeout;
    while ( !( check_reg_bit( &hal_ll_hw_reg->sr, HAL_LL_TWIHS_SR_TXRDY_BIT ) ) ) {
        if ( map->timeout ) {
            if ( !time_counter-- )
                return HAL_LL_I2C_MASTER_TIMEOUT_WRITE;
        }
    }

    if ( ( mode == HAL_LL_I2C_MASTER_END_MODE_STOP ) || ( mode == HAL_LL_I2C_MASTER_WRITE_THEN_READ ) )
    {
        hal_ll_i2c_master_stop( map );

        while ( !( check_reg_bit( &hal_ll_hw_reg->sr, HAL_LL_TWIHS_SR_TXCOMP_BIT ) ) ) {
            if ( map->timeout ) {
                if ( !time_counter-- )
                    return HAL_LL_I2C_MASTER_TIMEOUT_STOP;
            }
        }
    }

    return HAL_LL_I2C_MASTER_SUCCESS;
}

static void hal_ll_i2c_master_configure_transfer( hal_ll_i2c_base_handle_t *hal_ll_hw_reg, uint8_t slave_address, bool read ) {

    write_reg( &hal_ll_hw_reg->mmr, ( slave_address << HAL_LL_TWIHS_MMR_DADR_START_BIT ) );

    if ( read )
        set_reg_bit( &hal_ll_hw_reg->mmr, HAL_LL_TWIHS_MMR_MREAD_BIT );
}

static hal_ll_err_t hal_ll_i2c_master_start( hal_ll_i2c_hw_specifics_map_t *map ) {
    hal_ll_i2c_base_handle_t *hal_ll_hw_reg = hal_ll_i2c_get_base_struct( map->base );
    uint16_t loop_index = HAL_LL_I2C_LOOP_INDEX;

    set_reg_bit( &hal_ll_hw_reg->cr, HAL_LL_TWIHS_CR_START_BIT );

    if ( check_reg_bit( &hal_ll_hw_reg->sr, HAL_LL_TWIHS_SR_ARBLST_BIT ) )
        return HAL_LL_I2C_MASTER_ARBITRATION_LOST;

    while ( loop_index-- )
        assembly( nop );

    return HAL_LL_I2C_MASTER_SUCCESS;
}

static hal_ll_err_t hal_ll_i2c_master_stop( hal_ll_i2c_hw_specifics_map_t *map ) {
    hal_ll_i2c_base_handle_t *hal_ll_hw_reg = hal_ll_i2c_get_base_struct( map->base );
    uint16_t time_counter = map->timeout;
    uint32_t loop_index = HAL_LL_I2C_LOOP_INDEX;

    set_reg_bit( &hal_ll_hw_reg->cr, HAL_LL_TWIHS_CR_STOP_BIT );

    while ( loop_index-- )
        assembly(nop);

    return HAL_LL_I2C_MASTER_SUCCESS;
}

static hal_ll_pin_name_t hal_ll_i2c_master_check_pins( hal_ll_pin_name_t scl, hal_ll_pin_name_t sda, hal_ll_i2c_pin_id *index_list, hal_ll_i2c_master_handle_register_t *handle_map ) {
    static const uint16_t scl_map_size = ( sizeof( hal_ll_i2c_scl_map ) / sizeof( hal_ll_i2c_pin_map_t ) );
    static const uint16_t sda_map_size = ( sizeof( hal_ll_i2c_sda_map ) / sizeof( hal_ll_i2c_pin_map_t ) );
    uint8_t hal_ll_module_id = 0;
    uint8_t index_counter = 0;
    uint16_t scl_index;
    uint16_t sda_index;

    if ( (HAL_LL_PIN_NC == scl) || (HAL_LL_PIN_NC == sda) ) {
        return HAL_LL_PIN_NC;
    }

    for ( scl_index = 0; scl_index < scl_map_size; scl_index++ ) {
        if ( hal_ll_i2c_scl_map[ scl_index ].pin == scl ) {
            for ( sda_index = 0; sda_index < sda_map_size; sda_index++ ) {
                if ( hal_ll_i2c_sda_map[ sda_index ].pin == sda ) {
                    if ( hal_ll_i2c_scl_map[ scl_index ].module_index == hal_ll_i2c_sda_map[ sda_index ].module_index ) {
                        // Get module number.
                        hal_ll_module_id = hal_ll_i2c_scl_map[ scl_index ].module_index;
                        // Map pin names.
                        index_list[hal_ll_module_id].pin_scl = scl_index;
                        index_list[hal_ll_module_id].pin_sda = sda_index;

                        // Check if module is taken.
                        if ( NULL == handle_map[ hal_ll_module_id ].hal_drv_i2c_master_handle ) {
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
    static uint8_t hal_ll_module_error = sizeof( hal_ll_module_state ) / ( sizeof( hal_ll_i2c_master_handle_register_t ));

    while( hal_ll_module_count-- ) {
        if (hal_ll_i2c_get_base_from_hal_handle == hal_ll_i2c_hw_specifics_map[ hal_ll_module_count ].base) {
            return &hal_ll_i2c_hw_specifics_map[ hal_ll_module_count ];
        }
    }

    return &hal_ll_i2c_hw_specifics_map[ hal_ll_module_error ];
}

static void hal_ll_i2c_master_set_clock( hal_ll_i2c_hw_specifics_map_t *map, bool hal_ll_state ) {
    switch ( map->module_index )
    {
        #ifdef I2C_MODULE_0
        case ( hal_ll_i2c_module_num( I2C_MODULE_0 ) ):
            if ( hal_ll_state ) {
                set_reg_bit( _PMC_PCER0, HAL_LL_PID_TWIHS0_BIT );
            } else {
                set_reg_bit( _PMC_PCDR0, HAL_LL_PID_TWIHS0_BIT );
            }
            break;
        #endif
        #ifdef I2C_MODULE_1
        case ( hal_ll_i2c_module_num( I2C_MODULE_1 ) ):
            if ( hal_ll_state ) {
                set_reg_bit( _PMC_PCER0, HAL_LL_PID_TWIHS1_BIT );
            } else {
                set_reg_bit( _PMC_PCDR0, HAL_LL_PID_TWIHS1_BIT );
            }
            break;
        #endif
        #ifdef I2C_MODULE_2
        case ( hal_ll_i2c_module_num( I2C_MODULE_2 ) ):
            if ( hal_ll_state ) {
                set_reg_bit( _PMC_PCER1, HAL_LL_PID_TWIHS2_BIT );
            } else {
                set_reg_bit( _PMC_PCDR1, HAL_LL_PID_TWIHS2_BIT );
            }
            break;
        #endif

        default:
            break;
    }
}

static void hal_ll_i2c_master_map_pins( uint8_t module_index, hal_ll_i2c_pin_id *index_list ) {
    // Map new pins
    hal_ll_i2c_hw_specifics_map[module_index].pins.pin_scl.pin_name = hal_ll_i2c_scl_map[ index_list[module_index].pin_scl ].pin;
    hal_ll_i2c_hw_specifics_map[module_index].pins.pin_sda.pin_name = hal_ll_i2c_sda_map[ index_list[module_index].pin_sda ].pin;
    // SCL and SDA could have different alternate function settings, hence save both AF values.
    hal_ll_i2c_hw_specifics_map[module_index].pins.pin_scl.pin_af = hal_ll_i2c_scl_map[ index_list[module_index].pin_scl ].af;
    hal_ll_i2c_hw_specifics_map[module_index].pins.pin_sda.pin_af = hal_ll_i2c_sda_map[ index_list[module_index].pin_sda ].af;
}

static void hal_ll_i2c_master_alternate_functions_set_state( hal_ll_i2c_hw_specifics_map_t *map, bool hal_ll_state ) {
    module_struct module;

    if( (map->pins.pin_scl.pin_name != HAL_LL_PIN_NC) && (map->pins.pin_sda.pin_name != HAL_LL_PIN_NC) ) {
        module.pins[0] = map->pins.pin_scl.pin_name;
        module.pins[1] = map->pins.pin_sda.pin_name;
        module.pins[2] = GPIO_MODULE_STRUCT_END;

        module.configs[0] = map->pins.pin_scl.pin_af;
        module.configs[1] = map->pins.pin_sda.pin_af;
        module.configs[2] = GPIO_MODULE_STRUCT_END;

        hal_ll_gpio_module_struct_init( &module, hal_ll_state );
    }
}

static uint32_t hal_ll_i2c_get_speed( hal_ll_i2c_hw_specifics_map_t *map ) {
    hal_ll_i2c_base_handle_t *hal_ll_hw_reg = hal_ll_i2c_get_base_struct( map->base );
	uint8_t ckdiv = 0;
	uint8_t temp_div;
    uint32_t i2c_speed, twihs_cwgr;

	// High-Speed can be only used in slave mode, 400k is the max speed allowed for master.
    switch ( map->speed ) {
        case HAL_LL_I2C_MASTER_SPEED_STANDARD:
            i2c_speed = HAL_LL_I2C_MASTER_SPEED_100K;
            break;
        case HAL_LL_I2C_MASTER_SPEED_FULL:
            i2c_speed = HAL_LL_I2C_MASTER_LOW_DIVIDER_SPEED_LIMIT;
            break;

        default:
            return HAL_LL_I2C_MASTER_ERROR;
    }

    /* Formula for calculating baud value involves two unknowns. Fix one unknown and calculate the other.
       Fix the CKDIV value and see if CLDIV (or CHDIV) fits into the 8-bit register. */

    /* Calculate CLDIV with CKDIV set to 0 */
    while ( ckdiv <= HAL_LL_TWIHS_CWGR_CLKDIV_MAX ) {
        temp_div = 1;
        for ( uint8_t i = 1; i <= ckdiv; i++)
            temp_div *= 2;
        twihs_cwgr = hal_ll_i2c_get_divider( temp_div, i2c_speed );
        if ( twihs_cwgr <= HAL_LL_NIBBLE_LOW_16BIT )
            break;
        ckdiv++;
    }

    if ( twihs_cwgr > HAL_LL_NIBBLE_LOW_16BIT )
        /* Could not generate CLDIV and CKDIV register values for the requested baud rate */
        return HAL_LL_I2C_MASTER_ERROR;
    else
        write_reg( &hal_ll_hw_reg->cwgr, ( twihs_cwgr << 8 ) | twihs_cwgr | ckdiv << 16 );

	return HAL_LL_I2C_MASTER_SUCCESS;
}

static hal_ll_err_t hal_ll_i2c_hw_init( hal_ll_i2c_hw_specifics_map_t *map ) {
    hal_ll_i2c_base_handle_t *hal_ll_hw_reg = hal_ll_i2c_get_base_struct( map->base );
    uint16_t time_counter = map->timeout;
    int8_t status = HAL_LL_I2C_MASTER_SUCCESS;

    // Reset TWIHS control register.
    set_reg_bit( &hal_ll_hw_reg->cr, HAL_LL_TWIHS_CR_SWRST_BIT );

    // Get the actual speed and set the dividers for clock.
    status = hal_ll_i2c_get_speed( map );

    // Make sure I2C is not in Slave Mode.
    set_reg_bit( &hal_ll_hw_reg->cr, HAL_LL_TWIHS_CR_SVDIS_BIT );

    // Enable I2C in Master Mode.
    set_reg_bit( &hal_ll_hw_reg->cr, HAL_LL_TWIHS_CR_MSEN_BIT );

    return status;
}

static hal_ll_err_t hal_ll_i2c_init( hal_ll_i2c_hw_specifics_map_t *map ) {
    hal_ll_i2c_master_set_clock( map, true );

    return hal_ll_i2c_hw_init( map );
}
// ------------------------------------------------------------------------- END
