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
#include "hal_ll_rcc.h"
#include "hal_ll_gpio.h"
#include "hal_ll_i2c_master.h"
#include "hal_ll_i2c_pin_map.h"
#include "delays.h"

/*!< @brief Local handle list */
static volatile hal_ll_i2c_master_handle_register_t hal_ll_module_state[I2C_MODULE_COUNT] = { (handle_t *)NULL, (handle_t *)NULL, false };

// ------------------------------------------------------------- PRIVATE MACROS
/*!< @brief Helper macro for getting hal_ll_module_state address */
#define hal_ll_i2c_get_module_state_address ((hal_ll_i2c_master_handle_register_t *)*handle)
/*!< @brief Helper macro for getting module specific control register structure base address // first register address */
#define hal_ll_i2c_get_handle (hal_ll_i2c_master_handle_register_t *)hal_ll_i2c_get_module_state_address->hal_ll_i2c_master_handle
/*!< @brief Helper macro for getting module specific control register structure */
#define hal_ll_i2c_get_base_struct(_handle) ((hal_ll_i2c_base_handle_t *)_handle)
/*!< @brief Helper macro for getting module specific base address directly from HAL layer handle */
#define hal_ll_i2c_get_base_from_hal_handle ((hal_ll_i2c_hw_specifics_map_t *)((hal_ll_i2c_master_handle_register_t *)\
                                            (((hal_ll_i2c_master_handle_register_t *)(handle))->hal_ll_i2c_master_handle))->hal_ll_i2c_master_handle)->base

#define HAL_LL_I2C_SCL_PIN              0
#define HAL_LL_I2C_SDA_PIN              1
#define HAL_LL_I2C_MODULE_PIN_COUNT     2

#define HAL_LL_I2C_F_ICR_MASK           0x3FU

/*!< @brief Default I2C bit-rate if no speed is set */
#define HAL_LL_I2C_MASTER_SPEED_100K    100000UL
#define HAL_LL_I2C_MASTER_SPEED_400K    400000UL
#define HAL_LL_I2C_MASTER_SPEED_1M      1000000UL
#define HAL_LL_I2C_MASTER_SPEED_3M2     3200000UL

#define HAL_LL_I2C_DEFAULT_PASS_COUNT   10000

/*!< @brief Macros defining register bit location */
#define HAL_LL_I2C_C1_RSTA_BIT          2
#define HAL_LL_I2C_C1_TXAK_BIT          3
#define HAL_LL_I2C_C1_TX_BIT            4
#define HAL_LL_I2C_C1_IICIE_BIT         6
#define HAL_LL_I2C_C1_MST_BIT           5
#define HAL_LL_I2C_C1_IICEN_BIT         7
#define HAL_LL_I2C_S_RXAK_BIT           0
#define HAL_LL_I2C_S_IICIF_BIT          1
#define HAL_LL_I2C_S_SRW_BIT            2
#define HAL_LL_I2C_S_ARBL_BIT           4
#define HAL_LL_I2C_S_BUSY_BIT           5
#define HAL_LL_I2C_FLT_STARTF_BIT       4
#define HAL_LL_I2C_FLT_SSIE_BIT         5
#define HAL_LL_I2C_FLT_STOPF_BIT        6

#define HAL_LL_I2C0EN_BIT               6
#define HAL_LL_I2C1EN_BIT               7
#define HAL_LL_I2C2EN_BIT               6
#define HAL_LL_I2C3EN_BIT               7

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

#define HAL_LL_I2C_AF_CONFIG (GPIO_CFG_PULL_ENABLE | GPIO_CFG_PULL_UP | GPIO_CFG_TYPE_OD_ENABLED)

#define hal_ll_i2c_clear_status_reg(_temp) (_temp = hal_ll_hw_reg->s);

/*!< @brief I2C register structure */
typedef struct
{
    uint8_t a1;                 /**< I2C Address Register 1, offset: 0x0 */
    uint8_t f;                  /**< I2C Frequency Divider register, offset: 0x1 */
    uint8_t c1;                 /**< I2C Control Register 1, offset: 0x2 */
    uint8_t s;                  /**< I2C Status register, offset: 0x3 */
    uint8_t d;                  /**< I2C Data I/O register, offset: 0x4 */
    uint8_t c2;                 /**< I2C Control Register 2, offset: 0x5 */
    uint8_t flt;                /**< I2C Programmable Input Glitch Filter register, offset: 0x6 */
    uint8_t ra;                 /**< I2C Range Address register, offset: 0x7 */
    uint8_t smb;                /**< I2C SMBus Control and Status register, offset: 0x8 */
    uint8_t a2;                 /**< I2C Address Register 2, offset: 0x9 */
    uint8_t slth;               /**< I2C SCL Low Timeout Register High, offset: 0xA */
    uint8_t sltl;               /**< I2C SCL Low Timeout Register Low, offset: 0xB */
} hal_ll_i2c_base_handle_t;

/*!< @brief I2C divider table structure */
typedef struct I2CDividerTableEntry {
    uint8_t icr;
    uint16_t scl_divider;
} hal_ll_i2c_divider_table_entry;

/*!< @brief I2C divider table */
const hal_ll_i2c_divider_table_entry divTable[] = {
    { 0x00, 20 },
    { 0x01, 22 },
    { 0x02, 24 },
    { 0x03, 26 },
    { 0x04, 28 },
    { 0x05, 30 },
    { 0x09, 32 },
    { 0x06, 34 },
    { 0x0a, 36 },
    { 0x07, 40 },
    { 0x0c, 44 },
    { 0x10, 48 },
    { 0x11, 56 },
    { 0x12, 64 },
    { 0x0f, 68 },
    { 0x13, 72 },
    { 0x14, 80 },
    { 0x15, 88 },
    { 0x19, 96 },
    { 0x16, 104 },
    { 0x1a, 112 },
    { 0x17, 128 },
    { 0x1c, 144 },
    { 0x1d, 160 },
    { 0x1e, 192 },
    { 0x22, 224 },
    { 0x1f, 240 },
    { 0x23, 256 },
    { 0x24, 288 },
    { 0x25, 320 },
    { 0x26, 384 },
    { 0x2a, 448 },
    { 0x27, 480 },
    { 0x2b, 512 },
    { 0x2c, 576 },
    { 0x2d, 640 },
    { 0x2e, 768 },
    { 0x32, 896 },
    { 0x2f, 960 },
    { 0x33, 1024 },
    { 0x34, 1152 },
    { 0x35, 1280 },
    { 0x36, 1536 },
    { 0x3a, 1792 },
    { 0x37, 1920 },
    { 0x3b, 2048 },
    { 0x3c, 2304 },
    { 0x3d, 2560 },
    { 0x3e, 3072 },
    { 0x3f, 3840 }
};

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

/*!< @brief Enum containing predefined module standard speed values */
typedef enum
{
    HAL_LL_I2C_MASTER_SPEED_STANDARD = 0,
    HAL_LL_I2C_MASTER_SPEED_FULL,
    HAL_LL_I2C_MASTER_SPEED_FAST
} hal_ll_i2c_master_speed_t;
// ------------------------------------------------------------------ VARIABLES
static hal_ll_i2c_hw_specifics_map_t hal_ll_i2c_hw_specifics_map[I2C_MODULE_COUNT + 1] =
{
    #ifdef I2C_MODULE_0
    {HAL_LL_I2C0_BASE, hal_ll_i2c_module_num(I2C_MODULE_0), {HAL_LL_PIN_NC, 0, HAL_LL_PIN_NC, 0} , HAL_LL_I2C_MASTER_SPEED_100K , 0, HAL_LL_I2C_DEFAULT_PASS_COUNT},
    #endif
    #ifdef I2C_MODULE_1
    {HAL_LL_I2C1_BASE, hal_ll_i2c_module_num(I2C_MODULE_1), {HAL_LL_PIN_NC, 0, HAL_LL_PIN_NC, 0} , HAL_LL_I2C_MASTER_SPEED_100K , 0, HAL_LL_I2C_DEFAULT_PASS_COUNT},
    #endif
    #ifdef I2C_MODULE_2
    {HAL_LL_I2C2_BASE, hal_ll_i2c_module_num(I2C_MODULE_2), {HAL_LL_PIN_NC, 0, HAL_LL_PIN_NC, 0} , HAL_LL_I2C_MASTER_SPEED_100K , 0, HAL_LL_I2C_DEFAULT_PASS_COUNT},
    #endif
    #ifdef I2C_MODULE_3
    {HAL_LL_I2C3_BASE, hal_ll_i2c_module_num(I2C_MODULE_3), {HAL_LL_PIN_NC, 0, HAL_LL_PIN_NC, 0} , HAL_LL_I2C_MASTER_SPEED_100K , 0, HAL_LL_I2C_DEFAULT_PASS_COUNT},
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
  * @brief  Get I2C busy bit value.
  *
  * Checks I2C busy bit value and returns true if device is in operation.
  * Else returns false.
  *
  * @param[in]  hal_ll_hw_reg - Object specific context handler.
  * @return bool State of register busy bit.
  */
static bool hal_ll_i2c_master_is_idle( hal_ll_i2c_base_handle_t *hal_ll_hw_reg );

/**
  * @brief  Waits until device is free to operate.
  *
  * Polls I2C busy bit value and waits until device has finished any
  * on-going operation.
  *
  * @param[in]  map - Object specific context handler.
  * @return bool Free/Busy.
  */
static hal_ll_err_t hal_ll_i2c_master_wait_for_idle( hal_ll_i2c_hw_specifics_map_t *map );

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
static uint32_t hal_ll_i2c_get_speed( uint32_t bit_rate );

/**
  * @brief  Calculate I2C speed value.
  *
  * Calculates adequate value to be written in HW register
  * in order to set appropriate speed.
  *
  * @param[in]  clock_value - MCU clock value.
  * @param[in]  speed - I2C module desired bit-rate.
  * @return uint16_t Adequate value.
  *
  * Returns adequate value to be written into bare metal register address.
  * Take into consideration that this is hardware specific.
  */
static void hal_ll_i2c_calculate_speed( uint32_t clock_value, hal_ll_i2c_hw_specifics_map_t *map );

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
  * @return hal_ll_err_t Module specific values.
  *
  * Returns one of pre-defined values.
  * Take into consideration that this is hardware specific.
  */
static void hal_ll_i2c_hw_init( hal_ll_i2c_hw_specifics_map_t *map );

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
static void hal_ll_i2c_init( hal_ll_i2c_hw_specifics_map_t *map );

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
  * @brief  Writes one byte in data register.
  *
  * Writes one byte in data register.
  *
  * @param[in]  map - Object specific context handler.
  * @param[in]  dataByte - One byte of data.
  * @return hal_ll_err_t Module specific values.
  *
  * Returns the value of RXAK bit.
  * Take into consideration that this is hardware specific.
  */
static uint8_t hal_ll_i2c_master_write_byte( hal_ll_i2c_hw_specifics_map_t *map, uint8_t dataByte );

/**
  * @brief  Reads one byte from data register.
  *
  * Reads one byte from data register.
  *
  * @param[in]  map - Object specific context handler.
  * @return uint8_t Module specific values.
  *
  * Returns the value of data register.
  * Take into consideration that this is hardware specific.
  */
static uint8_t hal_ll_i2c_master_read_byte( hal_ll_i2c_hw_specifics_map_t *map );

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
    if ( ( pin_check_result = hal_ll_i2c_master_check_pins( scl, sda, &index_list, handle_map )) == HAL_LL_PIN_NC ) {
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

    hal_ll_module_state[ pin_check_result ].hal_ll_i2c_master_handle = ( handle_t * )&hal_ll_i2c_hw_specifics_map[ pin_check_result ].base;
    handle_map[ pin_check_result ].hal_ll_i2c_master_handle = ( handle_t * )&hal_ll_module_state[ pin_check_result ].hal_ll_i2c_master_handle;

    return HAL_LL_I2C_MASTER_SUCCESS;
}

hal_ll_err_t hal_ll_module_configure_i2c( handle_t *handle ) {
    hal_ll_i2c_hw_specifics_map_local = hal_ll_get_specifics( hal_ll_i2c_get_module_state_address );
    hal_ll_i2c_master_handle_register_t *hal_handle = (hal_ll_i2c_master_handle_register_t *)*handle;
    uint8_t pin_check_result = hal_ll_i2c_hw_specifics_map_local->module_index;

    hal_ll_i2c_init( hal_ll_i2c_hw_specifics_map_local );

    hal_ll_module_state[ pin_check_result ].hal_ll_i2c_master_handle = ( handle_t * )&hal_ll_i2c_hw_specifics_map[ pin_check_result ].base;
    hal_ll_module_state[ pin_check_result ].init_ll_state = true;
    hal_handle->init_ll_state = true;

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
    hal_ll_i2c_hw_specifics_map_local = hal_ll_get_specifics(hal_ll_i2c_get_module_state_address);

    if( HAL_LL_MODULE_ERROR != hal_ll_i2c_hw_specifics_map_local->base ) {
        hal_ll_i2c_hw_specifics_map_local->timeout = timeout;
    }
}

void hal_ll_i2c_master_set_slave_address( handle_t *handle, uint8_t addr ) {
    hal_ll_i2c_hw_specifics_map_local = hal_ll_get_specifics(hal_ll_i2c_get_module_state_address);

    if( HAL_LL_MODULE_ERROR != hal_ll_i2c_hw_specifics_map_local->base ) {
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

    if( NULL != hal_ll_i2c_master_write_bare_metal( hal_ll_i2c_hw_specifics_map_local, write_data_buf, len_write_data, HAL_LL_I2C_MASTER_WRITE_THEN_READ ) ) {
        return HAL_LL_I2C_MASTER_TIMEOUT_WRITE;
    }

    /**
     * @note Wait for drivers to set-up
     * correctly.
     **/
    #ifdef __TFT_RESISTIVE_TSC2003__
    Delay_22us();
    #endif

    if( NULL != hal_ll_i2c_master_read_bare_metal( hal_ll_i2c_hw_specifics_map_local, read_data_buf, len_read_data, HAL_LL_I2C_MASTER_WRITE_THEN_READ ) ) {
        return HAL_LL_I2C_MASTER_TIMEOUT_READ;
    }

    return HAL_LL_I2C_MASTER_SUCCESS;
}

void hal_ll_i2c_master_close( handle_t *handle ) {
    low_level_handle = hal_ll_i2c_get_handle;
    hal_ll_i2c_hw_specifics_map_local = hal_ll_get_specifics(hal_ll_i2c_get_module_state_address);

    if( NULL != low_level_handle->hal_ll_i2c_master_handle ) {
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
static uint8_t hal_ll_i2c_master_write_byte( hal_ll_i2c_hw_specifics_map_t *map, uint8_t dataByte ) {
    hal_ll_i2c_base_handle_t *hal_ll_hw_reg = hal_ll_i2c_get_base_struct( map->base );
    uint16_t time_counter = map->timeout;

    set_reg_bit( &( hal_ll_hw_reg->c1 ), HAL_LL_I2C_C1_TX_BIT );

    hal_ll_hw_reg->d = dataByte;

    while ( !check_reg_bit( &( hal_ll_hw_reg->s ), HAL_LL_I2C_S_IICIF_BIT ) ) {
        if ( map->timeout ) {
            if( !time_counter-- )
                return HAL_LL_I2C_MASTER_TIMEOUT_WRITE;
        }
    }

    set_reg_bit( &( hal_ll_hw_reg->s ), HAL_LL_I2C_S_IICIF_BIT );

    return ( check_reg_bit( &( hal_ll_hw_reg->s ), HAL_LL_I2C_S_RXAK_BIT ));
}

static uint8_t hal_ll_i2c_master_read_byte( hal_ll_i2c_hw_specifics_map_t *map ) {
    hal_ll_i2c_base_handle_t *hal_ll_hw_reg = hal_ll_i2c_get_base_struct( map->base );
    uint8_t dataByte;
    uint16_t time_counter = map->timeout;

    dataByte = hal_ll_hw_reg->d;

    while ( !check_reg_bit( &( hal_ll_hw_reg->s ), HAL_LL_I2C_S_IICIF_BIT ) ) {
        if ( map->timeout ) {
            if( !time_counter-- )
                return HAL_LL_I2C_MASTER_TIMEOUT_READ;
        }
    }

    set_reg_bit( &( hal_ll_hw_reg->s ), HAL_LL_I2C_S_IICIF_BIT );

    return dataByte;
}

static hal_ll_err_t hal_ll_i2c_master_stop( hal_ll_i2c_hw_specifics_map_t *map ) {
    hal_ll_i2c_base_handle_t *hal_ll_hw_reg = hal_ll_i2c_get_base_struct( map->base );
    uint16_t time_counter = map->timeout;
    hal_ll_err_t status;

    clear_reg_bit( &( hal_ll_hw_reg->c1 ), HAL_LL_I2C_C1_MST_BIT );
    clear_reg_bit( &( hal_ll_hw_reg->c1 ), HAL_LL_I2C_C1_TX_BIT );

    status = hal_ll_i2c_master_wait_for_idle( map );
    if( HAL_LL_I2C_MASTER_SUCCESS != status )
        return status;

    #if defined I2C_MASTER_CHIP_SELECT
    while ( !check_reg_bit( &( hal_ll_hw_reg->s ), HAL_LL_I2C_S_IICIF_BIT ) ) {
        if ( map->timeout ) {
            if( !time_counter-- )
                return HAL_LL_I2C_MASTER_TIMEOUT_STOP;
        }
    }
    if( check_reg_bit( &( hal_ll_hw_reg->flt ), HAL_LL_I2C_FLT_STOPF_BIT ) )
        set_reg_bit( &( hal_ll_hw_reg->flt ), HAL_LL_I2C_FLT_STOPF_BIT );
    #endif
    set_reg_bit( &( hal_ll_hw_reg->s ), HAL_LL_I2C_S_IICIF_BIT );
    #if defined I2C_MASTER_CHIP_SELECT
    time_counter = map->timeout;
    while ( check_reg_bit( &( hal_ll_hw_reg->s ), HAL_LL_I2C_S_IICIF_BIT )) {
        if ( map->timeout ) {
            if( !time_counter-- )
                return HAL_LL_I2C_MASTER_TIMEOUT_STOP;
        }
    }
    #endif
    return HAL_LL_I2C_MASTER_SUCCESS;
}

static hal_ll_err_t hal_ll_i2c_master_read_bare_metal( hal_ll_i2c_hw_specifics_map_t *map, uint8_t *read_data_buf, size_t len_read_data, hal_ll_i2c_master_end_mode_t mode ) {
    hal_ll_i2c_base_handle_t *hal_ll_hw_reg = hal_ll_i2c_get_base_struct( map->base );
    size_t i = 0;
    hal_ll_err_t status = HAL_LL_I2C_MASTER_SUCCESS;

    if ( HAL_LL_I2C_MASTER_WRITE_THEN_READ != mode ) {
        if ( HAL_LL_I2C_MASTER_SUCCESS != hal_ll_i2c_master_start( map ) )
            return HAL_LL_I2C_MASTER_TIMEOUT_START;
    }

    if ( HAL_LL_I2C_MASTER_TIMEOUT_WRITE != ( status = hal_ll_i2c_master_write_byte( map, ( map->address << 1 ) | 1 ))) {
        if ( status ) {
            if ( HAL_LL_I2C_MASTER_SUCCESS != hal_ll_i2c_master_stop( map ) )
                return HAL_LL_I2C_MASTER_TIMEOUT_STOP;
        }
    } else {
        return HAL_LL_I2C_MASTER_TIMEOUT_WRITE;
    }

    clear_reg_bit( &( hal_ll_hw_reg->c1 ), HAL_LL_I2C_C1_TX_BIT );

    if ( 1 == len_read_data )
        set_reg_bit( &( hal_ll_hw_reg->c1 ), HAL_LL_I2C_C1_TXAK_BIT );
    else
        clear_reg_bit( &( hal_ll_hw_reg->c1 ), HAL_LL_I2C_C1_TXAK_BIT );

    if ( HAL_LL_I2C_MASTER_TIMEOUT_READ == hal_ll_i2c_master_read_byte( map ))
        return HAL_LL_I2C_MASTER_TIMEOUT_READ;

    for( i = len_read_data-1; i >= 0; i-- ) {
        switch (i) {
            case 0x0:
                if ( HAL_LL_I2C_MASTER_SUCCESS != hal_ll_i2c_master_stop( map ) )
                    return HAL_LL_I2C_MASTER_TIMEOUT_STOP;
                break;
            case 0x1:
                set_reg_bit( &( hal_ll_hw_reg->c1 ), HAL_LL_I2C_C1_TXAK_BIT );
                break;
            default :
                clear_reg_bit( &( hal_ll_hw_reg->c1 ), HAL_LL_I2C_C1_TXAK_BIT );
                break;
        }
        if ( 0 == i ) {
            *read_data_buf++ = hal_ll_hw_reg->d;
            break;
        } else {
            status = hal_ll_i2c_master_read_byte( map );
            if ( HAL_LL_I2C_MASTER_TIMEOUT_READ != status )
                *read_data_buf++ = ( uint8_t ) status;
            else
                return status;
        }
    }

    return HAL_LL_I2C_MASTER_SUCCESS;
}

static hal_ll_err_t hal_ll_i2c_master_write_bare_metal( hal_ll_i2c_hw_specifics_map_t *map, uint8_t *write_data_buf, size_t len_write_data, hal_ll_i2c_master_end_mode_t mode ) {
    hal_ll_i2c_base_handle_t *hal_ll_hw_reg = hal_ll_i2c_get_base_struct( map->base );
    size_t i;
    uint16_t time_counter = map->timeout;
    hal_ll_err_t status = HAL_LL_I2C_MASTER_SUCCESS;

    status = hal_ll_i2c_master_start( map );
    if ( HAL_LL_I2C_MASTER_SUCCESS != status )
        return status;

    if ( HAL_LL_I2C_MASTER_TIMEOUT_WRITE != ( status = hal_ll_i2c_master_write_byte( map, map->address << 1 ))) {
        if ( status ) {
            if( HAL_LL_I2C_MASTER_SUCCESS != hal_ll_i2c_master_stop( map ))
                return HAL_LL_I2C_MASTER_TIMEOUT_STOP;
            else
                return HAL_LL_I2C_MASTER_SUCCESS;
        }
    } else {
        return HAL_LL_I2C_MASTER_TIMEOUT_WRITE;
    }

    for( i = 0; i < len_write_data; i++ ) {
        if ( HAL_LL_I2C_MASTER_TIMEOUT_WRITE != ( status = hal_ll_i2c_master_write_byte( map, write_data_buf[i] ))) {
            if ( status ) {
                if ( HAL_LL_I2C_MASTER_SUCCESS == hal_ll_i2c_master_stop( map ))
                    return HAL_LL_I2C_MASTER_SUCCESS;
                else
                    return HAL_LL_I2C_MASTER_TIMEOUT_STOP;
            }
        } else {
            return HAL_LL_I2C_MASTER_TIMEOUT_WRITE;
        }
    }

    if ( HAL_LL_I2C_MASTER_END_MODE_STOP == mode ) {
        #if defined I2C_MASTER_CHIP_SELECT
        while ( check_reg_bit( &( hal_ll_hw_reg->s ), HAL_LL_I2C_S_IICIF_BIT ) ) {
            if ( map->timeout ) {
                if ( !time_counter-- )
                    return HAL_LL_I2C_MASTER_TIMEOUT_WRITE;
            }
        }
        #endif
        clear_reg_bit( &( hal_ll_hw_reg->c1 ), HAL_LL_I2C_C1_MST_BIT );

        #if defined I2C_MASTER_CHIP_SELECT
        time_counter = map->timeout;
        while ( !check_reg_bit( &( hal_ll_hw_reg->s ), HAL_LL_I2C_S_IICIF_BIT )) {
            if ( map->timeout ) {
                if ( !time_counter-- )
                    return HAL_LL_I2C_MASTER_TIMEOUT_WRITE;
            }
        }
        if ( check_reg_bit( &( hal_ll_hw_reg->flt ), HAL_LL_I2C_FLT_STARTF_BIT ))
                set_reg_bit( &( hal_ll_hw_reg->flt ), HAL_LL_I2C_FLT_STARTF_BIT );
        if ( check_reg_bit( &( hal_ll_hw_reg->flt ), HAL_LL_I2C_FLT_STOPF_BIT ))
                set_reg_bit( &( hal_ll_hw_reg->flt ), HAL_LL_I2C_FLT_STOPF_BIT );
        #endif

        set_reg_bit( &( hal_ll_hw_reg->s ), HAL_LL_I2C_S_IICIF_BIT );
    }
    else {
        /**
         * @note When R/W = 0, the input sample acquisition period starts
         * on the falling edge of SCL once the C0 bit of the command
         * byte has been latched, and ends when a Stop or
         * repeated Start condition has been issued.
         **/
        #ifdef __TFT_RESISTIVE_TSC2003__
        Delay_1ms();
        #endif
        set_reg_bit( &( hal_ll_hw_reg->c1 ), HAL_LL_I2C_C1_RSTA_BIT );
        #if defined I2C_MASTER_CHIP_SELECT
        time_counter = map->timeout;
        while ( !( check_reg_bit( &( hal_ll_hw_reg->s ), HAL_LL_I2C_S_IICIF_BIT ))) {
            if ( map->timeout ) {
                if ( !time_counter-- )
                    return HAL_LL_I2C_MASTER_TIMEOUT_WRITE;
            }
        }

        if( check_reg_bit( &( hal_ll_hw_reg->flt ), HAL_LL_I2C_FLT_STARTF_BIT ))
            set_reg_bit( &( hal_ll_hw_reg->flt ), HAL_LL_I2C_FLT_STARTF_BIT );
        #endif
        set_reg_bit( &( hal_ll_hw_reg->s ), HAL_LL_I2C_S_IICIF_BIT );
    }
    #if defined I2C_MASTER_CHIP_SELECT
    time_counter = map->timeout;
    while ( check_reg_bit( &( hal_ll_hw_reg->s ), HAL_LL_I2C_S_IICIF_BIT ) ) {
        if ( map->timeout ) {
            if ( !time_counter-- )
                return HAL_LL_I2C_MASTER_TIMEOUT_WRITE;
        }
    }
    #endif
    return HAL_LL_I2C_MASTER_SUCCESS;
}

static hal_ll_err_t hal_ll_i2c_master_start( hal_ll_i2c_hw_specifics_map_t *map ) {
    hal_ll_i2c_base_handle_t *hal_ll_hw_reg = hal_ll_i2c_get_base_struct( map->base );
    uint16_t time_counter = map->timeout;
    hal_ll_err_t status = HAL_LL_I2C_MASTER_SUCCESS;

    status = hal_ll_i2c_master_wait_for_idle( map );
    if ( HAL_LL_I2C_MASTER_SUCCESS != status ){
        return HAL_LL_I2C_MASTER_TIMEOUT_START;
    }

    set_reg_bit( &( hal_ll_hw_reg->c1 ), HAL_LL_I2C_C1_MST_BIT );

    if ( check_reg_bit( &( hal_ll_hw_reg->s ), HAL_LL_I2C_S_ARBL_BIT ) ){
            #if defined I2C_MASTER_CHIP_SELECT_MK64
            clear_reg_bit( &( hal_ll_hw_reg->c1), HAL_LL_I2C_C1_MST_BIT );
            #endif
            set_reg_bit( &( hal_ll_hw_reg->s ), HAL_LL_I2C_S_ARBL_BIT );
            #if defined I2C_MASTER_CHIP_SELECT
            if( check_reg_bit( &( hal_ll_hw_reg->flt ), HAL_LL_I2C_FLT_STARTF_BIT ))
               set_reg_bit( &( hal_ll_hw_reg->flt ), HAL_LL_I2C_FLT_STARTF_BIT );
            #endif
            set_reg_bit( &( hal_ll_hw_reg->s ), HAL_LL_I2C_S_IICIF_BIT );
        return HAL_LL_I2C_MASTER_ARBITRATION_LOST;
    }
    #if defined I2C_MASTER_CHIP_SELECT
    while ( !check_reg_bit( &( hal_ll_hw_reg->s ), HAL_LL_I2C_S_IICIF_BIT ) ) {
        if ( map->timeout ) {
            if ( !time_counter-- )
                return HAL_LL_I2C_MASTER_TIMEOUT_START;
        }
    }
    if( check_reg_bit( &( hal_ll_hw_reg->flt ), HAL_LL_I2C_FLT_STARTF_BIT ))
                set_reg_bit( &( hal_ll_hw_reg->flt ), HAL_LL_I2C_FLT_STARTF_BIT );
    #endif
    set_reg_bit( &( hal_ll_hw_reg->s ), HAL_LL_I2C_S_IICIF_BIT );
    #if defined I2C_MASTER_CHIP_SELECT
    time_counter = map->timeout;
    while ( check_reg_bit( &( hal_ll_hw_reg->s ), HAL_LL_I2C_S_IICIF_BIT ) ) {
        if ( map->timeout ) {
            if ( !time_counter-- )
                return HAL_LL_I2C_MASTER_TIMEOUT_START;
        }
    }
    #endif

    return HAL_LL_I2C_MASTER_SUCCESS;
}

static hal_ll_err_t hal_ll_i2c_master_wait_for_idle( hal_ll_i2c_hw_specifics_map_t *map ) {
    uint16_t time_counter = map->timeout;

    while ( !hal_ll_i2c_master_is_idle( map->base ) ) {
        if ( map->timeout ) {
            if ( !time_counter-- )
                return HAL_LL_I2C_MASTER_TIMEOUT_WAIT_IDLE;
        }
    }

    return HAL_LL_I2C_MASTER_SUCCESS;
}

static bool hal_ll_i2c_master_is_idle( hal_ll_i2c_base_handle_t *hal_ll_hw_reg ) {
    return !( check_reg_bit( &( hal_ll_hw_reg->s ), HAL_LL_I2C_S_BUSY_BIT ) );
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
                        // Get module number
                        hal_ll_module_id = hal_ll_i2c_scl_map[ scl_index ].module_index;
                        // Map pin names
                        index_list[hal_ll_module_id].pin_scl = scl_index;
                        index_list[hal_ll_module_id].pin_sda = sda_index;

                        // Check if module is taken
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
    uint8_t hal_ll_module_count = sizeof( hal_ll_module_state ) / (sizeof( hal_ll_i2c_master_handle_register_t ));
    static uint8_t hal_ll_module_error = sizeof(hal_ll_module_state) / (sizeof( hal_ll_i2c_master_handle_register_t));

    while( hal_ll_module_count-- ) {
        if ( hal_ll_i2c_get_base_from_hal_handle == hal_ll_i2c_hw_specifics_map[ hal_ll_module_count ].base ) {
            return &hal_ll_i2c_hw_specifics_map[ hal_ll_module_count ];
        }
    }

    return &hal_ll_i2c_hw_specifics_map[ hal_ll_module_error ];
}

static void hal_ll_i2c_master_map_pins( uint8_t module_index, hal_ll_i2c_pin_id *index_list ) {
    // Map new pins
    hal_ll_i2c_hw_specifics_map[module_index].pins.pin_scl.pin_name = hal_ll_i2c_scl_map[ index_list[module_index].pin_scl ].pin;
    hal_ll_i2c_hw_specifics_map[module_index].pins.pin_sda.pin_name = hal_ll_i2c_sda_map[ index_list[module_index].pin_sda ].pin;
    // SCL and SDA could have different alternate function settings, hence save both AF values
    hal_ll_i2c_hw_specifics_map[module_index].pins.pin_scl.pin_af = hal_ll_i2c_scl_map[ index_list[module_index].pin_scl ].af;
    hal_ll_i2c_hw_specifics_map[module_index].pins.pin_sda.pin_af = hal_ll_i2c_sda_map[ index_list[module_index].pin_sda ].af;
}

static void hal_ll_i2c_master_alternate_functions_set_state( hal_ll_i2c_hw_specifics_map_t *map, bool hal_ll_state ) {
    module_struct module;

    if( ( HAL_LL_PIN_NC != map->pins.pin_scl.pin_name ) && ( HAL_LL_PIN_NC != map->pins.pin_sda.pin_name ) ) {
        module.pins[0] = VALUE( map->pins.pin_scl.pin_name, map->pins.pin_scl.pin_af );
        module.pins[1] = VALUE( map->pins.pin_sda.pin_name, map->pins.pin_sda.pin_af );
        module.pins[2] = GPIO_MODULE_STRUCT_END;

        module.configs[0] = HAL_LL_I2C_AF_CONFIG;
        module.configs[1] = HAL_LL_I2C_AF_CONFIG;
        module.configs[2] = GPIO_MODULE_STRUCT_END;

        hal_ll_gpio_module_struct_init( &module, hal_ll_state );
    }
}

static uint32_t hal_ll_i2c_get_speed( uint32_t bit_rate ) {
    if ( bit_rate <= HAL_LL_I2C_MASTER_SPEED_FAST ) {
        if ( bit_rate <= HAL_LL_I2C_MASTER_SPEED_STANDARD ) {
            return HAL_LL_I2C_MASTER_SPEED_100K;
        } else if ( bit_rate <= HAL_LL_I2C_MASTER_SPEED_FULL ) {
            return HAL_LL_I2C_MASTER_SPEED_400K;
        } else if ( bit_rate <= HAL_LL_I2C_MASTER_SPEED_FAST ) {
            return HAL_LL_I2C_MASTER_SPEED_1M;
        } else {
            return HAL_LL_I2C_MASTER_SPEED_100K;
        }
    } else {
        if ( bit_rate <= HAL_LL_I2C_MASTER_SPEED_100K ) {
            return HAL_LL_I2C_MASTER_SPEED_100K;
        } else if ( bit_rate <= HAL_LL_I2C_MASTER_SPEED_400K ) {
            return HAL_LL_I2C_MASTER_SPEED_400K;
        } else if ( bit_rate <= HAL_LL_I2C_MASTER_SPEED_1M ) {
            return HAL_LL_I2C_MASTER_SPEED_1M;
        } else {
            return HAL_LL_I2C_MASTER_SPEED_1M;
        }
    }
}

static void hal_ll_i2c_master_set_clock( hal_ll_i2c_hw_specifics_map_t *map, bool hal_ll_state ) {
    switch ( map->module_index )
    {
        #if defined(I2C_MODULE_0)
        case ( hal_ll_i2c_module_num( I2C_MODULE_0 ) ):
            if( hal_ll_state ) {
                set_reg_bit( _SIM_SCGC4, HAL_LL_I2C0EN_BIT );
            } else {
                clear_reg_bit( _SIM_SCGC4, HAL_LL_I2C0EN_BIT );
            }
            break;
        #endif
        #if defined(I2C_MODULE_1)
        case ( hal_ll_i2c_module_num( I2C_MODULE_1 ) ):
            if( hal_ll_state ) {
                set_reg_bit( _SIM_SCGC4, HAL_LL_I2C1EN_BIT );
            } else {
                clear_reg_bit( _SIM_SCGC4, HAL_LL_I2C1EN_BIT );
            }
            break;
        #endif
        #if defined(I2C_MODULE_2)
        case ( hal_ll_i2c_module_num( I2C_MODULE_2 ) ):
            if( hal_ll_state ) {
                set_reg_bit( _SIM_SCGC1, HAL_LL_I2C2EN_BIT );
            } else {
                clear_reg_bit( _SIM_SCGC1, HAL_LL_I2C2EN_BIT );
            }
            break;
        #endif
        #if defined(I2C_MODULE_3)
        case ( hal_ll_i2c_module_num( I2C_MODULE_3 ) ):
            if( hal_ll_state ) {
                set_reg_bit( _SIM_SCGC1, HAL_LL_I2C3EN_BIT );
            } else {
                clear_reg_bit( _SIM_SCGC1, HAL_LL_I2C3EN_BIT );
            }
            break;
        #endif

        default:
            break;
    }
}

static void hal_ll_i2c_calculate_speed( uint32_t clock_value, hal_ll_i2c_hw_specifics_map_t *map ) {
    uint32_t multiplier, currentRate, freq;
    uint32_t absError, bestError;
    uint32_t bestIcr;
    uint8_t i, mult, bestMult;

    SIM_ClocksTypeDef rcc_clocks;
    SIM_GetClocksFrequency( &rcc_clocks );

    hal_ll_i2c_base_handle_t *hal_ll_hw_reg = hal_ll_i2c_get_base_struct( map->base );

    #ifdef HAL_LL_RCC_CLOCK_OUTPUT
    #ifdef __MKV4X_RCC__
    freq = rcc_clocks.flash_frequency;
    #elif defined(__MKV5X_RCC__)
    freq = rcc_clocks.bus_flash_frequency;
    #endif
    #else
    freq = rcc_clocks.busclock_frequency;
    #endif

    bestError = 0xFFFFFFFF;
    bestMult = 0;
    bestIcr = 0;

    for ( mult = 0; ( mult <= 2 ) && ( 0 != bestError ); mult++ ) {
        multiplier = 1 << mult;

        for ( i = 0; i < 50; i++ ) {
            currentRate = freq / ( multiplier * divTable[i].scl_divider );
            absError = clock_value>currentRate ? clock_value-currentRate : currentRate-clock_value;

            if ( absError < bestError ) {
                bestMult = mult;
                bestIcr = divTable[i].icr;
                bestError = absError;

                if ( 0 == absError ) break;
            }
        }
    }

    hal_ll_hw_reg->f = ( bestMult << 6 ) | bestIcr;
}

static void hal_ll_i2c_hw_init( hal_ll_i2c_hw_specifics_map_t *map ) {
    hal_ll_i2c_base_handle_t *hal_ll_hw_reg = hal_ll_i2c_get_base_struct( map->base );

    clear_reg_bit( &( hal_ll_hw_reg->c1 ), HAL_LL_I2C_C1_IICEN_BIT );

    hal_ll_i2c_calculate_speed( map->speed, map );

    hal_ll_hw_reg->c1 = 0;

    set_reg_bit( &( hal_ll_hw_reg->c1 ), HAL_LL_I2C_C1_IICEN_BIT );
    set_reg_bit( &( hal_ll_hw_reg->c1 ), HAL_LL_I2C_C1_IICIE_BIT );
    #if defined I2C_MASTER_CHIP_SELECT
    set_reg_bit( &( hal_ll_hw_reg->flt ), HAL_LL_I2C_FLT_SSIE_BIT );
    #endif
}

static void hal_ll_i2c_init( hal_ll_i2c_hw_specifics_map_t *map ) {
    hal_ll_i2c_master_set_clock( map, true );

    hal_ll_i2c_hw_init( map );
}
// ------------------------------------------------------------------------- END
