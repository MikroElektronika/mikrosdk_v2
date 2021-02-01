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
#define hal_ll_i2c_get_module_state_address (( hal_ll_i2c_master_handle_register_t *)*handle)
/*!< @brief Helper macro for getting module specific control register structure base address // first register address */
#define hal_ll_i2c_get_handle  (hal_ll_i2c_master_handle_register_t *)hal_ll_i2c_get_module_state_address->hal_ll_i2c_master_handle
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

/*!< @brief Macro used for clock value checking */
#define hal_ll_i2c_check_speed(_speed) (((Get_Fosc_kHz()*1000/_speed)/4)-1)
#define HAL_LL_I2C_MAX_SPEED_VALUE 0xFFU

/*!< @brief Default I2C bit-rate if no speed is set */
#define HAL_LL_I2C_MASTER_SPEED_100K 100000UL
#define HAL_LL_I2C_MASTER_SPEED_400K 400000UL

/*!< @brief Default pass count value upon reset */
#define HAL_LL_I2C_DEFAULT_PASS_COUNT 10000

/*!< @brief Macros defining register addresses and masks */
#define HAL_LL_SSPXCON1_SETUP 0x38U
#define HAL_LL_I2C_IDLE_MASK 0x1FU

/*!< @brief Macros defining register bit location */
#define HAL_LL_SSPSTAT_R_NOT_W_BIT 2
#define HAL_LL_SSPSTAT_CKE_BIT 6
#define HAL_LL_SSPSTAT_SMP_BIT 7
#define HAL_LL_SSPCON2_SEN_BIT 0
#define HAL_LL_SSPCON2_RSEN_BIT 1
#define HAL_LL_SSPCON2_PEN_BIT 2
#define HAL_LL_SSPCON2_RCEN_BIT 3
#define HAL_LL_SSPCON2_ACKEN_BIT 4
#define HAL_LL_SSPCON2_ACKDT_BIT 5
#define HAL_LL_SSPCON2_ACKSTAT_BIT 6

/*!< @brief Macros used for module pin checking */
#define HAL_LL_I2C_SCL_PIN 0
#define HAL_LL_I2C_SDA_PIN 1
#define HAL_LL_I2C_MODULE_PIN_COUNT 2

// -------------------------------------------------------------- PRIVATE TYPES
/*!< @brief I2C register structure */
typedef struct
{
    hal_ll_base_addr_t sspcon2_reg_addr;
    hal_ll_base_addr_t sspcon1_reg_addr;
    hal_ll_base_addr_t sspstat_reg_addr;
    hal_ll_base_addr_t sspadd_reg_addr;
    hal_ll_base_addr_t sspbuf_reg_addr;
    hal_ll_base_addr_t pir_reg_addr;
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
    { HAL_LL_SSP1CON2_ADDRESS, HAL_LL_SSP1CON1_ADDRESS, HAL_LL_SSP1STAT_ADDRESS, HAL_LL_SSP1ADD_ADDRESS, HAL_LL_SSP1BUF_ADDRESS, HAL_LL_PIR_MODULE_I2C1_ADDRESS },
    #endif

    #ifdef I2C_MODULE_1
    { HAL_LL_SSP1CON2_ADDRESS, HAL_LL_SSP1CON1_ADDRESS, HAL_LL_SSP1STAT_ADDRESS, HAL_LL_SSP1ADD_ADDRESS, HAL_LL_SSP1BUF_ADDRESS, HAL_LL_PIR_MODULE_I2C1_ADDRESS },
    #endif

    #ifdef I2C_MODULE_2
    { HAL_LL_SSP2CON2_ADDRESS, HAL_LL_SSP2CON1_ADDRESS, HAL_LL_SSP2STAT_ADDRESS, HAL_LL_SSP2ADD_ADDRESS, HAL_LL_SSP2BUF_ADDRESS, HAL_LL_PIR_MODULE_I2C2_ADDRESS },
    #endif

    { HAL_LL_MODULE_ERROR, HAL_LL_MODULE_ERROR, HAL_LL_MODULE_ERROR, HAL_LL_MODULE_ERROR, HAL_LL_MODULE_ERROR, HAL_LL_MODULE_ERROR }
};

/*!< @brief I2C interrupt flags */
static const uint8_t hal_ll_i2c_sspif[ I2C_MODULE_COUNT + 1 ] =
{
    #ifdef I2C_MODULE
    HAL_LL_PIR_SSPIF_MODULE_1_BIT,
    #endif

    #ifdef I2C_MODULE_1
    HAL_LL_PIR_SSPIF_MODULE_1_BIT,
    #endif

    #ifdef I2C_MODULE_2
    HAL_LL_PIR_SSPIF_MODULE_2_BIT,
    #endif

    HAL_LL_PIN_NC
};

// ------------------------------------------------------------------ VARIABLES
/*!< @brief I2C hardware specific info */
static hal_ll_i2c_hw_specifics_map_t hal_ll_i2c_hw_specifics_map[ I2C_MODULE_COUNT + 1 ] =
{
    #ifdef I2C_MODULE
    {&hal_ll_i2c_hw_regs[hal_ll_i2c_module_num(I2C_MODULE)], hal_ll_i2c_module_num(I2C_MODULE), {HAL_LL_PIN_NC,0,HAL_LL_PIN_NC,0}, {HAL_LL_I2C_MASTER_SPEED_100K,0} , 0, HAL_LL_I2C_DEFAULT_PASS_COUNT},
    #endif

    #ifdef I2C_MODULE_1
    {&hal_ll_i2c_hw_regs[hal_ll_i2c_module_num(I2C_MODULE_1)], hal_ll_i2c_module_num(I2C_MODULE_1), {HAL_LL_PIN_NC,0,HAL_LL_PIN_NC,0}, {HAL_LL_I2C_MASTER_SPEED_100K,0} , 0, HAL_LL_I2C_DEFAULT_PASS_COUNT},
    #endif

    #ifdef I2C_MODULE_2
    {&hal_ll_i2c_hw_regs[hal_ll_i2c_module_num(I2C_MODULE_2)], hal_ll_i2c_module_num(I2C_MODULE_2), {HAL_LL_PIN_NC,0,HAL_LL_PIN_NC,0}, {HAL_LL_I2C_MASTER_SPEED_100K,0} , 0, HAL_LL_I2C_DEFAULT_PASS_COUNT},
    #endif

    {&hal_ll_i2c_hw_regs[I2C_MODULE_COUNT], HAL_LL_MODULE_ERROR, {HAL_LL_PIN_NC,0,HAL_LL_PIN_NC,0}, {0,0} , 0, 0}
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
  * HAL_LL_I2C_MASTER_SPEED_400K -- 400Kbit/s
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
static void hal_ll_i2c_hw_set_module_power( hal_ll_i2c_hw_specifics_map_t *map, bool hal_ll_state );

/**
  * @brief  Errata fix.
  *
  * The following function is a workaround for i2c module silicon bug
  * which exists in some MCU revisions.
  * 1. Configure SCL and SDA pins as outputs by clearing corresponding TRIS bits.
  * 2. Force SCL and SDA low by clearing corresponding LAT bits.
  * 3. While keeping LAT bits low, configure SCL and SDA as inputs by setting TRIS bits.
  *
  * @param[in]  map - Object specific context handler.
  *
  * @return None
  */
static void hal_ll_i2c_hw_errata_silicon_fix( hal_ll_i2c_hw_specifics_map_t *map );

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
static void hal_ll_i2c_hw_init( hal_ll_i2c_hw_specifics_map_t *map );

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
        // Clear previous module pps
        if ( hal_ll_pps_set_state( &hal_ll_i2c_hw_specifics_map[ pin_check_result ], false ) != HAL_LL_I2C_MASTER_SUCCESS )
            return HAL_LL_I2C_MASTER_WRONG_PINS;
        #endif

        // Map new pins
        hal_ll_i2c_master_map_pins( pin_check_result, &index_list );

        // Used only for chips which have I2C PPS pins
        #if HAL_LL_I2C_PPS_ENABLED == true
        // Set mapped pps
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

    hal_ll_i2c_hw_specifics_map_local->speed.speed_value = hal_ll_i2c_check_speed( hal_ll_i2c_get_speed( speed ) );

    if( hal_ll_i2c_hw_specifics_map_local->speed.speed_value > HAL_LL_I2C_MAX_SPEED_VALUE ) {
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
        hal_ll_i2c_hw_specifics_map_local->speed.speed_value = HAL_LL_I2C_MASTER_SPEED_100K;

        hal_ll_i2c_hw_set_module_power(hal_ll_i2c_hw_specifics_map_local, false);

        hal_ll_pps_set_state(hal_ll_i2c_hw_specifics_map_local, false);

        hal_ll_i2c_hw_specifics_map_local->pins->pin_scl.pin_name = HAL_LL_PIN_NC;
        hal_ll_i2c_hw_specifics_map_local->pins->pin_sda.pin_name = HAL_LL_PIN_NC;
        hal_ll_i2c_hw_specifics_map_local->pins->pin_scl.pin_pps = HAL_LL_PPS_FUNCTIONALITY_NONE;
        hal_ll_i2c_hw_specifics_map_local->pins->pin_sda.pin_pps = HAL_LL_PPS_FUNCTIONALITY_NONE;
    }
}

// ----------------------------------------------- PRIVATE FUNCTION DEFINITIONS
static hal_ll_err_t hal_ll_i2c_master_read_bare_metal( hal_ll_i2c_hw_specifics_map_t *map, uint8_t *read_data_buf, size_t len_read_data, hal_ll_i2c_master_end_mode_t mode ) {
    const hal_ll_i2c_base_handle_t *hal_ll_hw_reg = hal_ll_i2c_get_base_struct(map->base);
    size_t transfer_counter = NULL;
    uint16_t time_counter = map->timeout;
    uint8_t status = NULL;

    if( mode != HAL_LL_I2C_MASTER_WRITE_THEN_READ ) {
        status = hal_ll_i2c_master_start( map );
        if( status != HAL_LL_I2C_MASTER_SUCCESS ) {
            return status;
        }
    }

    clear_reg_bit( hal_ll_hw_reg->pir_reg_addr , hal_ll_i2c_sspif[ map->module_index ] );
    write_reg( hal_ll_hw_reg->sspbuf_reg_addr, ( ( map->address << 1 ) | 1 ) );

    status = hal_ll_i2c_master_check_write( map );
    if( status != HAL_LL_I2C_MASTER_SUCCESS ) {
        return status;
    }

    for ( transfer_counter = 0; transfer_counter < len_read_data; transfer_counter++ ) {

        clear_reg_bit( hal_ll_hw_reg->pir_reg_addr, hal_ll_i2c_sspif[ map->module_index ] );
        set_reg_bit( hal_ll_hw_reg->sspcon2_reg_addr, HAL_LL_SSPCON2_RCEN_BIT );

        // Wait for interrupt flag.
        while ( !check_reg_bit( hal_ll_hw_reg->pir_reg_addr, hal_ll_i2c_sspif[ map->module_index ] ) ) {
            if ( map->timeout ) {
                if ( !time_counter-- )
                    return HAL_LL_I2C_MASTER_TIMEOUT_READ;
            }
        }

        read_data_buf[transfer_counter] = read_reg( hal_ll_hw_reg->sspbuf_reg_addr );

        if ( transfer_counter < ( len_read_data - 1 ) ) {
            clear_reg_bit( hal_ll_hw_reg->sspcon2_reg_addr, HAL_LL_SSPCON2_ACKDT_BIT );
        } else {
            set_reg_bit( hal_ll_hw_reg->sspcon2_reg_addr, HAL_LL_SSPCON2_ACKDT_BIT );
        }

        clear_reg_bit( hal_ll_hw_reg->pir_reg_addr, hal_ll_i2c_sspif[ map->module_index ] );
        set_reg_bit( hal_ll_hw_reg->sspcon2_reg_addr, HAL_LL_SSPCON2_ACKEN_BIT );

        time_counter = map->timeout;
        while ( !check_reg_bit( hal_ll_hw_reg->pir_reg_addr, hal_ll_i2c_sspif[ map->module_index ] ) ) {
            if ( map->timeout ) {
                if ( !time_counter-- )
                    return HAL_LL_I2C_MASTER_TIMEOUT_READ;
            }
        }
    }

    set_reg_bit( hal_ll_hw_reg->sspcon2_reg_addr , HAL_LL_SSPCON2_PEN_BIT );

    return HAL_LL_I2C_MASTER_SUCCESS;
}

static hal_ll_err_t hal_ll_i2c_master_write_bare_metal( hal_ll_i2c_hw_specifics_map_t *map, uint8_t *write_data_buf, size_t len_write_data, hal_ll_i2c_master_end_mode_t mode ) {
    const hal_ll_i2c_base_handle_t *hal_ll_hw_reg = hal_ll_i2c_get_base_struct(map->base);
    size_t transfer_counter = NULL;
    uint8_t status = NULL;

    status = hal_ll_i2c_master_start( map );
    if( status != HAL_LL_I2C_MASTER_SUCCESS ) {
        return status;
    }

    clear_reg_bit( hal_ll_hw_reg->pir_reg_addr , hal_ll_i2c_sspif[ map->module_index ]);
    write_reg( hal_ll_hw_reg->sspbuf_reg_addr, ( map->address << 1 ) );

    status = hal_ll_i2c_master_check_write( map );
    if( status != HAL_LL_I2C_MASTER_SUCCESS ) {
        return status;
    }

    for ( transfer_counter = 0; transfer_counter < len_write_data; transfer_counter++ )
    {
        write_reg( hal_ll_hw_reg->sspbuf_reg_addr, write_data_buf[ transfer_counter ] );

        status = hal_ll_i2c_master_check_write( map );
        if( status != HAL_LL_I2C_MASTER_SUCCESS ) {
            return status;
        }
    }

    if ( ( mode == HAL_LL_I2C_MASTER_END_MODE_RESTART ) || ( mode == HAL_LL_I2C_MASTER_WRITE_THEN_READ ) ) {
        status = hal_ll_i2c_master_restart( map );
        if( status != HAL_LL_I2C_MASTER_SUCCESS ) {
            return status;
        }
    } else if ( mode == HAL_LL_I2C_MASTER_END_MODE_STOP ) {
        set_reg_bit( hal_ll_hw_reg->sspcon2_reg_addr , HAL_LL_SSPCON2_PEN_BIT );
    }

    if ( !check_reg_bit( hal_ll_hw_reg->sspcon2_reg_addr, HAL_LL_SSPCON2_ACKSTAT_BIT ) ) {
        return HAL_LL_I2C_MASTER_SUCCESS;
    } else {
        return HAL_LL_I2C_MASTER_ERROR;
    }
}

static hal_ll_err_t hal_ll_i2c_master_start( hal_ll_i2c_hw_specifics_map_t *map ) {
    const hal_ll_i2c_base_handle_t *hal_ll_hw_reg = hal_ll_i2c_get_base_struct(map->base);
    uint16_t time_counter = map->timeout;

    while( !hal_ll_i2c_master_is_idle( hal_ll_hw_reg ) ) {
        if ( map->timeout ) {
            if ( !time_counter-- )
                return HAL_LL_I2C_MASTER_TIMEOUT_START;
        }
    }

    set_reg_bit( hal_ll_hw_reg->sspcon2_reg_addr, HAL_LL_SSPCON2_SEN_BIT );

    time_counter = map->timeout;
    while ( check_reg_bit( hal_ll_hw_reg->sspcon2_reg_addr , HAL_LL_SSPCON2_SEN_BIT ) )
    {
        if ( map->timeout ) {
            if ( !time_counter-- )
                return HAL_LL_I2C_MASTER_TIMEOUT_START;
        }
    }

    return HAL_LL_I2C_MASTER_SUCCESS;
}

static hal_ll_err_t hal_ll_i2c_master_restart( hal_ll_i2c_hw_specifics_map_t *map ) {
    const hal_ll_i2c_base_handle_t *hal_ll_hw_reg = hal_ll_i2c_get_base_struct(map->base);
    uint16_t time_counter = map->timeout;

    // Restart Condition Enable.
    set_reg_bit( hal_ll_hw_reg->sspcon2_reg_addr, HAL_LL_SSPCON2_RSEN_BIT );
    while ( check_reg_bit( hal_ll_hw_reg->sspcon2_reg_addr , HAL_LL_SSPCON2_RSEN_BIT ) )
    {
        if ( map->timeout ) {
            if ( !time_counter-- )
                return HAL_LL_I2C_MASTER_TIMEOUT_START;
        }
    }

    return HAL_LL_I2C_MASTER_SUCCESS;
}

static bool hal_ll_i2c_master_is_idle( const hal_ll_i2c_base_handle_t *hal_ll_hw_reg ) {
    if ( !check_reg_bit( hal_ll_hw_reg->sspstat_reg_addr, HAL_LL_SSPSTAT_R_NOT_W_BIT ) ) {
        if ( !( read_reg( hal_ll_hw_reg->sspcon2_reg_addr ) & HAL_LL_I2C_IDLE_MASK ) ) {
            return HAL_LL_I2C_MASTER_TIMEOUT_WAIT_IDLE;
        }
    }

    return HAL_LL_I2C_MASTER_SUCCESS;
}

static hal_ll_err_t hal_ll_i2c_master_check_write( hal_ll_i2c_hw_specifics_map_t *map ) {
    const hal_ll_i2c_base_handle_t *hal_ll_hw_reg = hal_ll_i2c_get_base_struct(map->base);
    uint16_t time_counter = map->timeout;

    while ( check_reg_bit( hal_ll_hw_reg->sspstat_reg_addr , HAL_LL_SSPSTAT_R_NOT_W_BIT ) ) {
        if ( map->timeout ) {
            if ( !time_counter-- )
                return HAL_LL_I2C_MASTER_TIMEOUT_WRITE;
        }
    }

    time_counter = map->timeout;
    while ( !check_reg_bit( hal_ll_hw_reg->pir_reg_addr, hal_ll_i2c_sspif[ map->module_index ] ) ) {
        if ( map->timeout ) {
            if ( !time_counter-- )
                return HAL_LL_I2C_MASTER_TIMEOUT_WRITE;
        }
    }

    return HAL_LL_I2C_MASTER_SUCCESS;
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
        #ifdef __hal_ll_pps_i2c_in_out__
        hal_ll_status = hal_ll_pps_map( hal_ll_port( map->pins->pin_scl.pin_name ), hal_ll_pin( map->pins->pin_scl.pin_name ),
                                        HAL_LL_GPIO_DIGITAL_INPUT, HAL_LL_PPS_FUNCTIONALITY_I2C_SCL, map->module_index, hal_ll_state );
        
        if ( hal_ll_status != HAL_LL_PPS_SUCCESS )
            return hal_ll_status; 
        #endif
        // Check status manually if needed
        hal_ll_status = hal_ll_pps_map( hal_ll_port( map->pins->pin_sda.pin_name ), hal_ll_pin( map->pins->pin_sda.pin_name ),
                                        HAL_LL_GPIO_DIGITAL_INPUT, HAL_LL_PPS_FUNCTIONALITY_I2C_SDA, map->module_index, hal_ll_state );
        #ifdef __hal_ll_pps_i2c_in_out__
        if ( hal_ll_status != HAL_LL_PPS_SUCCESS )
            return hal_ll_status;

        hal_ll_status = hal_ll_pps_map( hal_ll_port( map->pins->pin_sda.pin_name ), hal_ll_pin( map->pins->pin_sda.pin_name ),
                                        HAL_LL_GPIO_DIGITAL_OUTPUT, HAL_LL_PPS_FUNCTIONALITY_I2C_SDA, map->module_index, hal_ll_state );
        #endif
        return hal_ll_status;
    } else {
        return HAL_LL_PPS_SUCCESS;
    }
}

static void hal_ll_i2c_hw_set_module_power( hal_ll_i2c_hw_specifics_map_t *map, bool hal_ll_state ) {
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

static void hal_ll_i2c_hw_errata_silicon_fix( hal_ll_i2c_hw_specifics_map_t *map ) {
    hal_ll_gpio_pin_t local_pin;

    /*
     * The following code section is a workaround for i2c module silicon bug
     * which exists in some MCU revisions.
     * 1. Configure SCL and SDA pins as outputs by clearing corresponding TRIS bits.
     * 2. Force SCL and SDA low by clearing corresponding LAT bits.
     * 3. While keeping LAT bits low, configure SCL and SDA as inputs by setting TRIS bits.
     */
    hal_ll_gpio_configure_pin(&local_pin, map->pins->pin_scl.pin_name, HAL_LL_GPIO_DIGITAL_OUTPUT);
    hal_ll_gpio_clear_pin_output(&local_pin);
    hal_ll_gpio_configure_pin(&local_pin, map->pins->pin_scl.pin_name, HAL_LL_GPIO_DIGITAL_INPUT);

    hal_ll_gpio_configure_pin(&local_pin, map->pins->pin_sda.pin_name, HAL_LL_GPIO_DIGITAL_OUTPUT);
    hal_ll_gpio_clear_pin_output(&local_pin);
    hal_ll_gpio_configure_pin(&local_pin, map->pins->pin_sda.pin_name, HAL_LL_GPIO_DIGITAL_INPUT);
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

static void hal_ll_i2c_hw_init( hal_ll_i2c_hw_specifics_map_t *map ) {
    const hal_ll_i2c_base_handle_t *hal_ll_hw_reg = hal_ll_i2c_get_base_struct(map->base);

    // Set I2C Speed(baud rate).
    write_reg( hal_ll_hw_reg->sspadd_reg_addr, map->speed.speed_write_reg_value );

    // Slew rate control enabled for High-Speed mode (400 kHz).
    if ( map->speed.speed_value >= HAL_LL_I2C_MASTER_SPEED_400K ) {
        clear_reg_bit( hal_ll_hw_reg->sspstat_reg_addr, HAL_LL_SSPSTAT_SMP_BIT );
    }

    // Disable SMBus specific inputs.
    clear_reg_bit( hal_ll_hw_reg->sspstat_reg_addr, HAL_LL_SSPSTAT_CKE_BIT );

    // I2C Master mode: Clock = FOSC/(4 * (SSPxADD + 1)).
    write_reg( hal_ll_hw_reg->sspcon1_reg_addr, HAL_LL_SSPXCON1_SETUP );
}

static void hal_ll_i2c_init( hal_ll_i2c_hw_specifics_map_t *map ) {
    hal_ll_i2c_hw_set_module_power( map, true );

    hal_ll_i2c_hw_errata_silicon_fix( map );

    hal_ll_i2c_hw_odcon_set( map );

    hal_ll_i2c_hw_init( map );
}
// ------------------------------------------------------------------------- END
