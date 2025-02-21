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

/*!< @brief Helper macro for setting appropriate I2C maximum rise time in Fm/Sm mode */
#define hal_ll_set_frequency(freqrange,speed) (speed<=100000)?(freqrange + 1):(((freqrange*300U)/1000U)+1U)
/*!< @brief Macro used for clearing status reg bits */
#define hal_ll_i2c_clear_status_reg(_temp) (_temp = hal_ll_hw_reg->sr1); \
                                            assembly(nop); \
                                            _temp |= hal_ll_hw_reg->sr2 << 16;

/*!< @brief Helper macros used for speed calculation */
#define hal_ll_i2c_get_pclk1 ((uint16_t)(rcc_clocks.pclk1 / 1000000))
#define HAL_LL_I2C_CCR_MINIMUM_ALLOWED_VALUE (0x04)

/*!< @brief Default I2C bit-rate if no speed is set */
#define HAL_LL_I2C_MASTER_SPEED_100K 100000UL
#define HAL_LL_I2C_MASTER_SPEED_400K 400000UL
#define HAL_LL_I2C_MASTER_SPEED_1M 1000000UL
#define HAL_LL_I2C_MASTER_SPEED_3M2 3200000UL

/*!< @brief Default pass count value upon reset */
#define HAL_LL_I2C_DEFAULT_PASS_COUNT 10000

/*!< @brief Macros defining register bit location */
#define HAL_LL_I2C_CCR_DUTY_BIT 14
#define HAL_LL_I2C_CCR_F_S_BIT 15
#define HAL_LL_I2C_CR1_PE_BIT 0
#define HAL_LL_I2C1EN_BIT 21
#define HAL_LL_I2C2EN_BIT 22
#define HAL_LL_I2C3EN_BIT 23
#define HAL_LL_I2C_CR1_SWRST_BIT 15
#define HAL_LL_I2C_CR1_ACK_BIT 10
#define HAL_LL_I2C_CR1_POS_BIT 11
#define HAL_LL_I2C_SR1_ADDR_BIT 1
#define HAL_LL_I2C_SR1_BTF_BIT 2
#define HAL_LL_I2C_CR1_START_BIT 8
#define HAL_LL_I2C_CR1_STOP_BIT 9
#define HAL_LL_I2C_SR1_ARLO_BIT 9
#define HAL_LL_I2C_SR2_BUSY_BIT 1

/*!< @brief Macros defining register specific bit masks */
#define HAL_LL_I2C_CR2_FREQ_MASK (0x3FU)

/*!< @brief Macro used for setting pin alternate functions */
#define HAL_LL_I2C_AF_CONFIG (GPIO_CFG_MODE_ALT_FUNCTION | GPIO_CFG_SPEED_HIGH | GPIO_CFG_OTYPE_OD)

/*!< @brief I2C event macros */
#define HAL_LL_I2C_EVENT_MASTER_MODE_SELECT ((uint32_t)0x00030001)  /* BUSY, MSL and SB flag */
#define HAL_LL_I2C_EVENT_MASTER_TRANSMITTER_MODE_SELECTED ((uint32_t)0x00070082)  /* BUSY, MSL, ADDR, TXE and TRA flags */
#define HAL_LL_I2C_EVENT_MASTER_RECEIVER_MODE_SELECTED ((uint32_t)0x00030002)  /* BUSY, MSL and ADDR flags */
#define HAL_LL_I2C_EVENT_MASTER_MODE_ADDRESS10 ((uint32_t)0x00030008)  /* BUSY, MSL and ADD10 flags */
#define HAL_LL_I2C_EVENT_MASTER_BYTE_RECEIVED ((uint32_t)0x00030040)  /* BUSY, MSL and RXNE flags */
#define HAL_LL_I2C_EVENT_MASTER_BYTE_TRANSMITTING ((uint32_t)0x00070080)  /* TRA, BUSY, MSL, TXE flags */
#define HAL_LL_I2C_EVENT_MASTER_BYTE_TRANSMITTED ((uint32_t)0x00070084)  /* TRA, BUSY, MSL, TXE and BTF flags */

// -------------------------------------------------------------- PRIVATE TYPES
/*!< @brief I2C register structure */
typedef struct
{
    hal_ll_base_addr_t cr1;
    hal_ll_base_addr_t cr2;
    hal_ll_base_addr_t oar1;
    hal_ll_base_addr_t oar2;
    hal_ll_base_addr_t dr;
    hal_ll_base_addr_t sr1;
    hal_ll_base_addr_t sr2;
    hal_ll_base_addr_t ccr;
    hal_ll_base_addr_t trise;
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
    #ifdef I2C_MODULE_1
    {HAL_LL_I2C1_BASE_ADDR, hal_ll_i2c_module_num(I2C_MODULE_1), {HAL_LL_PIN_NC, 0, HAL_LL_PIN_NC, 0}, HAL_LL_I2C_MASTER_SPEED_100K , 0, HAL_LL_I2C_DEFAULT_PASS_COUNT},
    #endif
    #ifdef I2C_MODULE_2
    {HAL_LL_I2C2_BASE_ADDR, hal_ll_i2c_module_num(I2C_MODULE_2), {HAL_LL_PIN_NC, 0, HAL_LL_PIN_NC, 0}, HAL_LL_I2C_MASTER_SPEED_100K , 0, HAL_LL_I2C_DEFAULT_PASS_COUNT},
    #endif
    #ifdef I2C_MODULE_3
    {HAL_LL_I2C3_BASE_ADDR, hal_ll_i2c_module_num(I2C_MODULE_3), {HAL_LL_PIN_NC, 0, HAL_LL_PIN_NC, 0}, HAL_LL_I2C_MASTER_SPEED_100K , 0, HAL_LL_I2C_DEFAULT_PASS_COUNT},
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
static uint8_t hal_ll_i2c_master_wait_for_idle( hal_ll_i2c_hw_specifics_map_t *map );

/**
  * @brief  Get value of status register.
  * @param[in]  hal_ll_hw_reg - I2C module base address.
  * @return uint32_t Status register value.
  */
static uint32_t hal_ll_i2c_master_get_status( hal_ll_i2c_base_handle_t *hal_ll_hw_reg );

/**
  * @brief  Check for current event on I2C bus.
  * @param[in]  hal_ll_hw_reg - I2C module base address.
  * @param[in]  event - Predefined event.
  * @return uint8_t Event status.
  */
static uint8_t hal_ll_i2c_master_check_event( hal_ll_i2c_base_handle_t *hal_ll_hw_reg, uint32_t event );

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
static uint16_t hal_ll_i2c_calculate_speed( uint32_t clock_value, uint32_t speed );

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

    hal_ll_i2c_pin_id index_list[I2C_MODULE_COUNT] = {HAL_LL_PIN_NC,HAL_LL_PIN_NC};
    uint16_t pin_check_result;

    // Check if pins are valid
    if ( (pin_check_result = hal_ll_i2c_master_check_pins( scl, sda, &index_list, handle_map )) == HAL_LL_PIN_NC ) {
        return HAL_LL_I2C_MASTER_WRONG_PINS;
    };

    if ( (hal_ll_i2c_hw_specifics_map[pin_check_result].pins.pin_scl.pin_name != scl) ||
         (hal_ll_i2c_hw_specifics_map[pin_check_result].pins.pin_sda.pin_name != sda) )
    {
        hal_ll_i2c_master_alternate_functions_set_state( &hal_ll_i2c_hw_specifics_map[ pin_check_result ], false );

        hal_ll_i2c_master_map_pins( pin_check_result, &index_list );

        hal_ll_i2c_master_alternate_functions_set_state( &hal_ll_i2c_hw_specifics_map[ pin_check_result ], true );

        handle_map[pin_check_result].init_ll_state = false;
    }

    *hal_module_id = pin_check_result;

    hal_ll_module_state[pin_check_result].hal_ll_i2c_master_handle = (handle_t *)&hal_ll_i2c_hw_specifics_map[pin_check_result].base;

    handle_map[pin_check_result].hal_ll_i2c_master_handle = (handle_t *)&hal_ll_module_state[pin_check_result].hal_ll_i2c_master_handle;

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
    hal_ll_i2c_hw_specifics_map_local = hal_ll_get_specifics(hal_ll_i2c_get_module_state_address);

    low_level_handle->init_ll_state = false;

    hal_ll_i2c_hw_specifics_map_local->speed = hal_ll_i2c_get_speed( speed );

    hal_ll_i2c_init( hal_ll_i2c_hw_specifics_map_local );

    low_level_handle->init_ll_state = true;

    return hal_ll_i2c_hw_specifics_map_local->speed;
}

void hal_ll_i2c_master_set_timeout( handle_t *handle, uint16_t timeout ) {
    hal_ll_i2c_hw_specifics_map_local = hal_ll_get_specifics(hal_ll_i2c_get_module_state_address);

    if( hal_ll_i2c_hw_specifics_map_local->base != HAL_LL_MODULE_ERROR ) {
        hal_ll_i2c_hw_specifics_map_local->timeout = timeout;
    }
}

void hal_ll_i2c_master_set_slave_address( handle_t *handle, uint8_t addr ) {
    hal_ll_i2c_hw_specifics_map_local = hal_ll_get_specifics(hal_ll_i2c_get_module_state_address);

    if( hal_ll_i2c_hw_specifics_map_local->base != HAL_LL_MODULE_ERROR ) {
        hal_ll_i2c_hw_specifics_map_local->address = addr;
    }
}

hal_ll_err_t hal_ll_i2c_master_read( handle_t *handle, uint8_t *read_data_buf, size_t len_read_data ) {
    low_level_handle = hal_ll_i2c_get_handle;
    hal_ll_i2c_hw_specifics_map_local = hal_ll_get_specifics(hal_ll_i2c_get_module_state_address);

    return hal_ll_i2c_master_read_bare_metal( hal_ll_i2c_hw_specifics_map_local, read_data_buf, len_read_data, HAL_LL_I2C_MASTER_END_MODE_STOP );
}

hal_ll_err_t hal_ll_i2c_master_write( handle_t *handle, uint8_t *write_data_buf, size_t len_write_data ) {
    low_level_handle = hal_ll_i2c_get_handle;
    hal_ll_i2c_hw_specifics_map_local = hal_ll_get_specifics(hal_ll_i2c_get_module_state_address);

    return hal_ll_i2c_master_write_bare_metal( hal_ll_i2c_hw_specifics_map_local, write_data_buf, len_write_data, HAL_LL_I2C_MASTER_END_MODE_STOP );
}

hal_ll_err_t hal_ll_i2c_master_write_then_read( handle_t *handle, uint8_t *write_data_buf, size_t len_write_data, uint8_t *read_data_buf, size_t len_read_data ) {
    low_level_handle = hal_ll_i2c_get_handle;
    hal_ll_i2c_hw_specifics_map_local = hal_ll_get_specifics(hal_ll_i2c_get_module_state_address);

    if( hal_ll_i2c_master_write_bare_metal( hal_ll_i2c_hw_specifics_map_local, write_data_buf, len_write_data, HAL_LL_I2C_MASTER_WRITE_THEN_READ ) != NULL ) {
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
    hal_ll_i2c_hw_specifics_map_local = hal_ll_get_specifics(hal_ll_i2c_get_module_state_address);

    if( low_level_handle->hal_ll_i2c_master_handle != NULL ) {
        low_level_handle->hal_ll_i2c_master_handle = NULL;
        low_level_handle->hal_drv_i2c_master_handle = NULL;

        low_level_handle->init_ll_state = false;

        hal_ll_i2c_hw_specifics_map_local->address = 0;
        hal_ll_i2c_hw_specifics_map_local->timeout = HAL_LL_I2C_DEFAULT_PASS_COUNT;
        hal_ll_i2c_hw_specifics_map_local->speed = HAL_LL_I2C_MASTER_SPEED_100K;

        hal_ll_i2c_master_set_clock(hal_ll_i2c_hw_specifics_map_local, true);
        hal_ll_i2c_master_alternate_functions_set_state( hal_ll_i2c_hw_specifics_map_local, false );
        hal_ll_i2c_master_set_clock(hal_ll_i2c_hw_specifics_map_local, false);

        hal_ll_i2c_hw_specifics_map_local->pins.pin_scl.pin_name = HAL_LL_PIN_NC;
        hal_ll_i2c_hw_specifics_map_local->pins.pin_sda.pin_name = HAL_LL_PIN_NC;
        hal_ll_i2c_hw_specifics_map_local->pins.pin_scl.pin_af = 0;
        hal_ll_i2c_hw_specifics_map_local->pins.pin_sda.pin_af = 0;
    }
}

// ----------------------------------------------- PRIVATE FUNCTION DEFINITIONS
static hal_ll_err_t hal_ll_i2c_master_read_bare_metal( hal_ll_i2c_hw_specifics_map_t *map, uint8_t *read_data_buf, size_t len_read_data, hal_ll_i2c_master_end_mode_t mode ) {
    hal_ll_i2c_base_handle_t *hal_ll_hw_reg = hal_ll_i2c_get_base_struct(map->base);
    uint16_t time_counter = map->timeout;
    size_t transfer_counter = 0;
    volatile uint32_t status_reg_clear;
    uint8_t status = HAL_LL_I2C_MASTER_SUCCESS;

    if( mode != HAL_LL_I2C_MASTER_WRITE_THEN_READ ) {
        status = hal_ll_i2c_master_start( map );
        if( status != HAL_LL_I2C_MASTER_SUCCESS ) {
            return status;
        }
    }

    if ( len_read_data <= 2 ) {
        // If 2 bytes are read
        ( len_read_data == 1 ) ? ( NULL ) : ( set_reg_bit( &( hal_ll_hw_reg->cr1 ), HAL_LL_I2C_CR1_ACK_BIT),
                                            set_reg_bit( &( hal_ll_hw_reg->cr1 ), HAL_LL_I2C_CR1_POS_BIT ) );

        hal_ll_hw_reg->dr = ( map->address << 1 ) | 1;

        while ( !( check_reg_bit( &(hal_ll_hw_reg->sr1), HAL_LL_I2C_SR1_ADDR_BIT ) ) ) {
            if ( map->timeout ) {
                if ( !time_counter-- )
                    return HAL_LL_I2C_MASTER_TIMEOUT_READ;
            }
        }

        clear_reg_bit( &( hal_ll_hw_reg->cr1 ), HAL_LL_I2C_CR1_ACK_BIT);

        hal_ll_i2c_clear_status_reg(status_reg_clear); // Check status reg value for combined SR1 and SR2 status

        time_counter = map->timeout;
        while( ( len_read_data == 1 ) ? ( !hal_ll_i2c_master_check_event( map->base, HAL_LL_I2C_EVENT_MASTER_BYTE_RECEIVED ) ) :
                                      ( !(check_reg_bit( &( hal_ll_hw_reg->sr1 ), HAL_LL_I2C_SR1_BTF_BIT ) ) ) )
        {
             if ( map->timeout ) {
                if ( !time_counter-- )
                    return HAL_LL_I2C_MASTER_TIMEOUT_READ;
            }
        }

        if( ( mode == HAL_LL_I2C_MASTER_END_MODE_STOP ) || ( mode == HAL_LL_I2C_MASTER_WRITE_THEN_READ ) ) {
            set_reg_bit( &( hal_ll_hw_reg->cr1 ), HAL_LL_I2C_CR1_STOP_BIT );
        } else {
            set_reg_bit( &( hal_ll_hw_reg->cr1 ), HAL_LL_I2C_CR1_START_BIT );

            time_counter = map->timeout;
            while ( !hal_ll_i2c_master_check_event( map->base, HAL_LL_I2C_EVENT_MASTER_MODE_SELECT ) ) {
                if ( map->timeout ) {
                    if ( !time_counter-- )
                        return HAL_LL_I2C_MASTER_TIMEOUT_READ;
                }
            }
        }

        ( len_read_data == 1 ) ? ( read_data_buf[ transfer_counter ] = hal_ll_hw_reg->dr ) :
                                 ( read_data_buf[ transfer_counter++ ] = hal_ll_hw_reg->dr, read_data_buf[ transfer_counter++ ] = hal_ll_hw_reg->dr );

        ( len_read_data == 1 ) ? ( NULL ) : ( clear_reg_bit( &(hal_ll_hw_reg->cr1), HAL_LL_I2C_CR1_POS_BIT ) );
    } else {
        set_reg_bit( &( hal_ll_hw_reg->cr1 ), HAL_LL_I2C_CR1_ACK_BIT );
        hal_ll_hw_reg->dr = ( map->address << 1 ) | 1;

        time_counter = map->timeout;
        while ( !hal_ll_i2c_master_check_event( map->base, HAL_LL_I2C_EVENT_MASTER_RECEIVER_MODE_SELECTED ) ) {
            if ( map->timeout ) {
                if ( !time_counter-- )
                    return HAL_LL_I2C_MASTER_TIMEOUT_READ;
            }
        }

        transfer_counter = 0;
        while ( transfer_counter < len_read_data - 3 ) {
            time_counter = map->timeout;
            while ( !hal_ll_i2c_master_check_event( map->base, HAL_LL_I2C_EVENT_MASTER_BYTE_RECEIVED ) ) {
                if ( map->timeout ) {
                    if ( !time_counter-- )
                        return HAL_LL_I2C_MASTER_TIMEOUT_READ;
                }
            }
            read_data_buf[ transfer_counter++ ] = hal_ll_hw_reg->dr;
        }

        time_counter = map->timeout;
        while ( !check_reg_bit( &( hal_ll_hw_reg->sr1 ), HAL_LL_I2C_SR1_BTF_BIT ) ) {
            if ( map->timeout ) {
                if ( !time_counter-- )
                    return HAL_LL_I2C_MASTER_TIMEOUT_READ;
            }
        }

        clear_reg_bit( &( hal_ll_hw_reg->cr1 ), HAL_LL_I2C_CR1_ACK_BIT );
        read_data_buf[ transfer_counter++ ] = hal_ll_hw_reg->dr;

        time_counter = map->timeout;
        while ( !check_reg_bit( &( hal_ll_hw_reg->sr1 ), HAL_LL_I2C_SR1_BTF_BIT ) ) {
            if ( map->timeout ) {
                if ( !time_counter-- )
                    return HAL_LL_I2C_MASTER_TIMEOUT_READ;
            }
        }

        if( ( mode == HAL_LL_I2C_MASTER_END_MODE_STOP ) || ( mode == HAL_LL_I2C_MASTER_WRITE_THEN_READ ) ) {
            set_reg_bit( &( hal_ll_hw_reg->cr1 ), HAL_LL_I2C_CR1_STOP_BIT );
        } else {
            set_reg_bit( &( hal_ll_hw_reg->cr1 ), HAL_LL_I2C_CR1_START_BIT );

            time_counter = map->timeout;
            while ( !hal_ll_i2c_master_check_event( map->base, HAL_LL_I2C_EVENT_MASTER_MODE_SELECT ) ) {
                if ( map->timeout ) {
                    if ( !time_counter-- )
                        return HAL_LL_I2C_MASTER_TIMEOUT_READ;
                }
            }
        }

        read_data_buf[ transfer_counter++ ] = hal_ll_hw_reg->dr;
        read_data_buf[ transfer_counter++ ] = hal_ll_hw_reg->dr;
    }

    return HAL_LL_I2C_MASTER_SUCCESS;
}

static hal_ll_err_t hal_ll_i2c_master_write_bare_metal( hal_ll_i2c_hw_specifics_map_t *map, uint8_t *write_data_buf, size_t len_write_data, hal_ll_i2c_master_end_mode_t mode ) {
    hal_ll_i2c_base_handle_t *hal_ll_hw_reg = hal_ll_i2c_get_base_struct(map->base);
    uint16_t time_counter = map->timeout;
    size_t transfer_counter = 0;
    uint8_t status = HAL_LL_I2C_MASTER_SUCCESS;

    status = hal_ll_i2c_master_start( map );
    if( status != HAL_LL_I2C_MASTER_SUCCESS ) {
        return status;
    }

    hal_ll_hw_reg->dr = ( map->address << 1 );

    while ( !hal_ll_i2c_master_check_event( map->base, HAL_LL_I2C_EVENT_MASTER_TRANSMITTER_MODE_SELECTED ) ) {
        if ( map->timeout ) {
            if ( !time_counter-- )
                return HAL_LL_I2C_MASTER_TIMEOUT_WRITE;
        }
    }

    for ( transfer_counter = 0; transfer_counter < len_write_data - 1; transfer_counter++ ) {
        hal_ll_hw_reg->dr = write_data_buf[ transfer_counter ];

        time_counter = map->timeout;
        while ( !hal_ll_i2c_master_check_event( map->base, HAL_LL_I2C_EVENT_MASTER_BYTE_TRANSMITTING ) ) {
            if ( map->timeout ) {
                if ( !time_counter-- )
                    return HAL_LL_I2C_MASTER_TIMEOUT_WRITE;
            }
        }
    }

    hal_ll_hw_reg->dr = write_data_buf[ transfer_counter ];

    time_counter = map->timeout;
    while ( !hal_ll_i2c_master_check_event( map->base, HAL_LL_I2C_EVENT_MASTER_BYTE_TRANSMITTED ) ) {
        if ( map->timeout ) {
            if ( !time_counter-- )
                return HAL_LL_I2C_MASTER_TIMEOUT_WRITE;
        }
    }

    if( mode == HAL_LL_I2C_MASTER_END_MODE_STOP ) {
        set_reg_bit( &( hal_ll_hw_reg->cr1 ), HAL_LL_I2C_CR1_STOP_BIT );
    } else {
        /**
         * @note When R/W = 0, the input sample acquisition period starts
         * on the falling edge of SCL once the C0 bit of the command
         * byte has been latched, and ends when a Stop or
         * repeated Start condition has been issued.
         **/
        #ifdef __TFT_RESISTIVE_TSC2003__
        Delay_1ms();
        #endif
        set_reg_bit( &( hal_ll_hw_reg->cr1 ), HAL_LL_I2C_CR1_START_BIT );

        time_counter = map->timeout;
        while ( !hal_ll_i2c_master_check_event( map->base, HAL_LL_I2C_EVENT_MASTER_MODE_SELECT ) ) {
            if ( map->timeout ) {
                if ( !time_counter-- )
                    return HAL_LL_I2C_MASTER_TIMEOUT_WRITE;
            }
        }
    }

    return HAL_LL_I2C_MASTER_SUCCESS;
}

static hal_ll_err_t hal_ll_i2c_master_start( hal_ll_i2c_hw_specifics_map_t *map ) {
    hal_ll_i2c_base_handle_t *hal_ll_hw_reg = hal_ll_i2c_get_base_struct(map->base);
    uint16_t time_counter = map->timeout;
    uint8_t result = HAL_LL_I2C_MASTER_SUCCESS;

    result = hal_ll_i2c_master_wait_for_idle( map );
    if ( result != HAL_LL_I2C_MASTER_SUCCESS )
        return HAL_LL_I2C_MASTER_TIMEOUT_START;

    set_reg_bit( &( hal_ll_hw_reg->cr1 ), HAL_LL_I2C_CR1_START_BIT );

    if ( check_reg_bit( &( hal_ll_hw_reg->sr1 ), HAL_LL_I2C_SR1_ARLO_BIT ) )
        return HAL_LL_I2C_MASTER_ARBITRATION_LOST;

    while ( !hal_ll_i2c_master_check_event( map->base, HAL_LL_I2C_EVENT_MASTER_MODE_SELECT ) ) {
        if ( map->timeout ) {
            if ( !time_counter-- )
                return HAL_LL_I2C_MASTER_TIMEOUT_START;
        }
    }

    return HAL_LL_I2C_MASTER_SUCCESS;
}

static uint8_t hal_ll_i2c_master_wait_for_idle( hal_ll_i2c_hw_specifics_map_t *map ) {
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
    return !( check_reg_bit( &( hal_ll_hw_reg->sr2 ), HAL_LL_I2C_SR2_BUSY_BIT ) );
}

static uint32_t hal_ll_i2c_master_get_status( hal_ll_i2c_base_handle_t *hal_ll_hw_reg ) {
    return ( uint32_t )hal_ll_hw_reg->sr1 | ( ( ( uint32_t )hal_ll_hw_reg->sr2 ) << 16 );
}

static uint8_t hal_ll_i2c_master_check_event( hal_ll_i2c_base_handle_t *hal_ll_hw_reg, uint32_t event ) {
    return ( hal_ll_i2c_master_get_status( hal_ll_hw_reg ) & event ) == event;
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
    uint8_t hal_ll_module_count = sizeof(hal_ll_module_state) / (sizeof(hal_ll_i2c_master_handle_register_t));
    static uint8_t hal_ll_module_error = sizeof(hal_ll_module_state) / (sizeof(hal_ll_i2c_master_handle_register_t));

    while( hal_ll_module_count-- ) {
        if (hal_ll_i2c_get_base_from_hal_handle == hal_ll_i2c_hw_specifics_map[hal_ll_module_count].base) {
            return &hal_ll_i2c_hw_specifics_map[hal_ll_module_count];
        }
    }

    return &hal_ll_i2c_hw_specifics_map[hal_ll_module_error];
}

static void hal_ll_i2c_master_set_clock( hal_ll_i2c_hw_specifics_map_t *map, bool hal_ll_state ) {
    switch ( map->module_index )
    {
        #if defined(I2C_MODULE_1)
        case ( hal_ll_i2c_module_num(I2C_MODULE_1) ):
            if( hal_ll_state ) {
                set_reg_bit( _RCC_APB1ENR, HAL_LL_I2C1EN_BIT );
            } else {
                clear_reg_bit( _RCC_APB1ENR, HAL_LL_I2C1EN_BIT );
            }
            break;
        #endif
        #if defined(I2C_MODULE_2)
        case ( hal_ll_i2c_module_num(I2C_MODULE_2) ):
            if( hal_ll_state ) {
                set_reg_bit( _RCC_APB1ENR, HAL_LL_I2C2EN_BIT );
            } else {
                clear_reg_bit( _RCC_APB1ENR, HAL_LL_I2C2EN_BIT );
            }
            break;
        #endif
        #if defined(I2C_MODULE_3)
        case ( hal_ll_i2c_module_num(I2C_MODULE_3) ):
            if( hal_ll_state ) {
                set_reg_bit( _RCC_APB1ENR, HAL_LL_I2C3EN_BIT );
            } else {
                clear_reg_bit( _RCC_APB1ENR, HAL_LL_I2C3EN_BIT );
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
    // SCL and SDA could have different alternate function settings, hence save both AF values
    hal_ll_i2c_hw_specifics_map[module_index].pins.pin_scl.pin_af = hal_ll_i2c_scl_map[ index_list[module_index].pin_scl ].af;
    hal_ll_i2c_hw_specifics_map[module_index].pins.pin_sda.pin_af = hal_ll_i2c_sda_map[ index_list[module_index].pin_sda ].af;
}

static void hal_ll_i2c_master_alternate_functions_set_state( hal_ll_i2c_hw_specifics_map_t *map, bool hal_ll_state ) {
    module_struct module;

    if( (map->pins.pin_scl.pin_name != HAL_LL_PIN_NC) && (map->pins.pin_sda.pin_name != HAL_LL_PIN_NC) ) {
        module.pins[0] = VALUE( map->pins.pin_scl.pin_name, map->pins.pin_scl.pin_af );
        module.pins[1] = VALUE( map->pins.pin_sda.pin_name, map->pins.pin_sda.pin_af );
        module.pins[2] = GPIO_MODULE_STRUCT_END;

        module.configs[0] = HAL_LL_I2C_AF_CONFIG;
        module.configs[1] = HAL_LL_I2C_AF_CONFIG;
        module.configs[2] = GPIO_MODULE_STRUCT_END;

        /* STM32F1xx specific */
        module.gpio_remap = map->pins.pin_scl.pin_af;

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

static uint16_t hal_ll_i2c_calculate_speed( uint32_t clock_value, uint32_t speed ) {
    uint16_t tmp_one = 0;
    uint16_t tmp_two = 0;

    if ( speed <= HAL_LL_I2C_MASTER_SPEED_100K )
    {
        tmp_one = ( uint16_t )( clock_value / ( speed << 1 ) );
        if ( tmp_one < HAL_LL_I2C_CCR_MINIMUM_ALLOWED_VALUE )
            return HAL_LL_I2C_CCR_MINIMUM_ALLOWED_VALUE;

        return tmp_one;
    } else {
        tmp_one = ( uint16_t )( clock_value / ( speed * 3 ) );
        tmp_two = ( uint16_t )( clock_value / ( speed * 25 ) );

        tmp_one = tmp_one * ( speed * 3 );
        tmp_two = tmp_two * ( speed * 25 );

        if ( ( clock_value - tmp_one ) < ( clock_value - tmp_two ) )
        {
            tmp_one = ( uint16_t )( clock_value / ( speed * 3 ) );
        } else {
            tmp_one = ( uint16_t )( clock_value / ( speed * 25 ) );
            tmp_one |= 1U << HAL_LL_I2C_CCR_DUTY_BIT;
        }

        if ( ( tmp_one & 0xFFF ) == 0 )
            tmp_one |= 1;

        return (( uint16_t )( tmp_one | ( 1U << HAL_LL_I2C_CCR_F_S_BIT )));
    }

    return HAL_LL_I2C_MASTER_SUCCESS;
}

static void hal_ll_i2c_hw_init( hal_ll_i2c_hw_specifics_map_t *map ) {
    hal_ll_i2c_base_handle_t *hal_ll_hw_reg = hal_ll_i2c_get_base_struct(map->base);
    uint16_t frequency_range;
    rcc_clocks_t rcc_clocks;

    #ifdef __STM32F101_103_ERRATA__
    set_reg_bit( &( hal_ll_hw_reg->cr1 ), HAL_LL_I2C_CR1_SWRST_BIT );
    #endif

    RCC_GetClocksFrequency( &rcc_clocks );

    #ifdef __STM32F101_103_ERRATA__
    clear_reg_bit( &( hal_ll_hw_reg->cr1 ), HAL_LL_I2C_CR1_SWRST_BIT );
    #endif

    frequency_range = hal_ll_i2c_get_pclk1;

    hal_ll_hw_reg->cr2 &= ~HAL_LL_I2C_CR2_FREQ_MASK;

    hal_ll_hw_reg->cr2 = frequency_range;

    clear_reg_bit( &( hal_ll_hw_reg->cr1 ), HAL_LL_I2C_CR1_PE_BIT );

    hal_ll_hw_reg->trise = hal_ll_set_frequency( frequency_range, map->speed );

    hal_ll_hw_reg->ccr = hal_ll_i2c_calculate_speed( rcc_clocks.pclk1, map->speed );

    hal_ll_hw_reg->cr1 = 0;

    set_reg_bit( &( hal_ll_hw_reg->cr1 ), HAL_LL_I2C_CR1_PE_BIT );
}

static void hal_ll_i2c_init( hal_ll_i2c_hw_specifics_map_t *map ) {
    hal_ll_i2c_master_set_clock( map, true );

    hal_ll_i2c_hw_init( map );
}
// ------------------------------------------------------------------------- END
