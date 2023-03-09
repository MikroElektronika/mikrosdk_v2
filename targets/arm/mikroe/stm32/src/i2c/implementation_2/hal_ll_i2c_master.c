/****************************************************************************
**
** Copyright (C) 2023 MikroElektronika d.o.o.
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

#include "hal_ll_rcc.h"
#include "hal_ll_gpio.h"
#include "hal_ll_i2c_master.h"
#include "hal_ll_i2c_pin_map.h"

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

/*!< @brief Default I2C bit-rate if no speed is set */
#define HAL_LL_I2C_MASTER_SPEED_100K 100000UL
#define HAL_LL_I2C_MASTER_SPEED_400K 400000UL
#define HAL_LL_I2C_MASTER_SPEED_1M 1000000UL

/*!< @brief Default pass count value upon reset */
#define HAL_LL_I2C_DEFAULT_PASS_COUNT 0xFFFFU

/*!< @brief Macro used for timeout */
#define HAL_LL_I2C_LOOP_INDEX 10000U

/*!< @brief Macros defining register bit location */
#define HAL_LL_I2C1EN_BIT 21
#define HAL_LL_I2C2EN_BIT 22
#if defined(STM32F7xx)
    #define HAL_LL_I2C3EN_BIT 23
    #define HAL_LL_I2C4EN_BIT 24
    #define HAL_LL_I2C1SEL0_BIT 16
    #define HAL_LL_I2C1SEL1_BIT 17
    #define HAL_LL_I2C2SEL0_BIT 18
    #define HAL_LL_I2C2SEL1_BIT 19
    #define HAL_LL_I2C3SEL0_BIT 20
    #define HAL_LL_I2C3SEL1_BIT 21
    #define HAL_LL_I2C4SEL0_BIT 22
    #define HAL_LL_I2C4SEL1_BIT 23
    #define HAL_LL_I2C_100K 0x00303D5D
    #define HAL_LL_I2C_400K 0x0010061A
    #define HAL_LL_I2C_1M 0x00000107
#elif defined(STM32H7xx)
    #define HAL_LL_I2C3EN_BIT 23
    #define HAL_LL_I2C4EN_BIT 7
    #define HAL_LL_I2C123SRC0_BIT 12
    #define HAL_LL_I2C123SRC1_BIT 13
    #define HAL_LL_I2C4SRC0_BIT 8
    #define HAL_LL_I2C4SRC1_BIT 9
    #define HAL_LL_I2C_100K 0x10707DBC
    #define HAL_LL_I2C_400K 0x00602173
    #define HAL_LL_I2C_1M 0x00300B29
#elif defined(STM32L4xx)
    #define HAL_LL_I2C3EN_BIT 23
    #define HAL_LL_I2C4EN_BIT 1
    #define HAL_LL_I2C1SEL0_BIT 12
    #define HAL_LL_I2C1SEL1_BIT 13
    #define HAL_LL_I2C2SEL0_BIT 14
    #define HAL_LL_I2C2SEL1_BIT 15
    #define HAL_LL_I2C3SEL0_BIT 16
    #define HAL_LL_I2C3SEL1_BIT 17
    #define HAL_LL_I2C4SEL0_BIT 0
    #define HAL_LL_I2C4SEL1_BIT 1
    #define HAL_LL_I2C_100K 0x10909CEC
    #define HAL_LL_I2C_400K 0x00702991
    #define HAL_LL_I2C_1M 0x00300F33
#elif defined(STM32F3xx)
    #define HAL_LL_I2C3EN_BIT 30
    #define HAL_LL_I2C_100K 0x2000090E
    #define HAL_LL_I2C_400K 0x0000020B
    #define HAL_LL_I2C_1M 0x00000001
#elif defined(STM32F0xx)
    #define HAL_LL_I2C3EN_BIT 30
    #define HAL_LL_I2C_100K 0xb0420f13
    #define HAL_LL_I2C_400K 0x50330309
    #define HAL_LL_I2C_1M 0x50100301
#elif defined(STM32L0xx)
    #define HAL_LL_I2C3EN_BIT 30
    #define HAL_LL_I2C1SEL1_BIT 13
    #define HAL_LL_I2C1SEL0_BIT 12
    #define HAL_LL_I2C_100K 0x30420f13
    #define HAL_LL_I2C_400K 0x10320309
    #define HAL_LL_I2C_1M 0x00200204
#elif defined(STM32G0xx)
    #define HAL_LL_I2C_10K 0xE010A9FF
    #define HAL_LL_I2C_100K 0x10707DBC
    #define HAL_LL_I2C_400K 0x00602173
    #define HAL_LL_I2C_1M 0x00300B29
#endif
#define HAL_LL_I2C_PE_BIT 0
#define HAL_LL_I2C_CR2_STOP_BIT 14
#define HAL_LL_I2C_CR2_START_BIT 13
#define HAL_LL_I2C_ISR_STOPF_BIT 5
#define HAL_LL_I2C_ISR_BUSY_BIT 15
#define HAL_LL_I2C_ARLO_BIT 9
#define HAL_LL_I2C_RXNE_BIT 2
#define HAL_LL_I2C_TXIS_BIT 1
#define HAL_LL_I2C_TXE_BIT 0

/*!< @brief Macros defining register bit masks */
#define HAL_LL_I2C_CR1_RXTX_INT 0x6
#define HAL_LL_I2C_CR2_STOP 0x4000UL
#define HAL_LL_I2C_CR2_START 0x2000U
#define HAL_LL_I2C_CR2_SADD 0x3FFU
#define HAL_LL_I2C_CR2_NBYTES 0xFF0000UL
#define HAL_LL_I2C_CR2_RD_WRN 0x400U
#define HAL_LL_I2C_CR2_RELOAD 0x1000000UL
#define HAL_LL_I2C_CR2_AUTOEND 0x2000000UL
#define HAL_LL_I2C_FILTERS_OFF 0xFFFFE0FFUL
#define HAL_LL_I2C_SADD_MASK 0x3FFUL
#define HAL_LL_I2C_HEAD10R_MASK 0x1000UL
#define HAL_LL_I2C_NBYTES_MASK 0xFF0000UL
#define HAL_LL_I2C_RELOAD_MASK 0x1000000UL
#define HAL_LL_I2C_RD_WRN_MASK 0x400UL

/*!< @brief Macros used for module pin checking */
#define HAL_LL_I2C_SCL_PIN 0
#define HAL_LL_I2C_SDA_PIN 1
#define HAL_LL_I2C_MODULE_PIN_COUNT 2

/*!< @brief Macro used for setting pin alternate functions */
#define HAL_LL_I2C_AF_CONFIG (GPIO_CFG_MODE_ALT_FUNCTION | GPIO_CFG_SPEED_HIGH | GPIO_CFG_OTYPE_OD)

// -------------------------------------------------------------- PRIVATE TYPES
/*!< @brief I2C register structure */
typedef struct
{
    hal_ll_base_addr_t cr1;
    hal_ll_base_addr_t cr2;
    hal_ll_base_addr_t oar1;
    hal_ll_base_addr_t oar2;
    hal_ll_base_addr_t timingr;
    hal_ll_base_addr_t timoutr;
    hal_ll_base_addr_t isr;
    hal_ll_base_addr_t icr;
    hal_ll_base_addr_t pecr;
    hal_ll_base_addr_t rxdr;
    hal_ll_base_addr_t txdr;
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
    #ifdef I2C_MODULE_1
    {HAL_LL_I2C1_BASE_ADDR, hal_ll_i2c_module_num(I2C_MODULE_1), {HAL_LL_PIN_NC, 0, HAL_LL_PIN_NC, 0}, HAL_LL_I2C_MASTER_SPEED_100K , 0, HAL_LL_I2C_DEFAULT_PASS_COUNT},
    #endif
    #ifdef I2C_MODULE_2
    {HAL_LL_I2C2_BASE_ADDR, hal_ll_i2c_module_num(I2C_MODULE_2), {HAL_LL_PIN_NC, 0, HAL_LL_PIN_NC, 0}, HAL_LL_I2C_MASTER_SPEED_100K , 0, HAL_LL_I2C_DEFAULT_PASS_COUNT},
    #endif
    #ifdef I2C_MODULE_3
    {HAL_LL_I2C3_BASE_ADDR, hal_ll_i2c_module_num(I2C_MODULE_3), {HAL_LL_PIN_NC, 0, HAL_LL_PIN_NC, 0}, HAL_LL_I2C_MASTER_SPEED_100K , 0, HAL_LL_I2C_DEFAULT_PASS_COUNT},
    #endif
    #ifdef I2C_MODULE_4
    {HAL_LL_I2C4_BASE_ADDR, hal_ll_i2c_module_num(I2C_MODULE_4), {HAL_LL_PIN_NC, 0, HAL_LL_PIN_NC, 0}, HAL_LL_I2C_MASTER_SPEED_100K , 0, HAL_LL_I2C_DEFAULT_PASS_COUNT},
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
  * @brief  Enable clock for I2C1 module on hardware level.
  *
  * Initializes I2C1 module clock on hardware level, based on beforehand
  * set configuration and module handler.
  *
  * @param[in]  hal_ll_state - True/False -- Init/De-init
  *
  * @return None
  */
static inline void hal_ll_i2c1_set_clock( bool hal_ll_state );

/**
  * @brief  Enable clock for I2C2 module on hardware level.
  *
  * Initializes I2C2 module clock on hardware level, based on beforehand
  * set configuration and module handler.
  *
  * @param[in]  hal_ll_state - True/False -- Init/De-init
  *
  * @return None
  */
static inline void hal_ll_i2c2_set_clock( bool hal_ll_state );

/**
  * @brief  Enable clock for I2C3 module on hardware level.
  *
  * Initializes I2C3 module clock on hardware level, based on beforehand
  * set configuration and module handler.
  *
  * @param[in]  hal_ll_state - True/False -- Init/De-init
  *
  * @return None
  */
static inline void hal_ll_i2c3_set_clock( bool hal_ll_state );

/**
  * @brief  Enable clock for I2C4 module on hardware level.
  *
  * Initializes I2C4 module clock on hardware level, based on beforehand
  * set configuration and module handler.
  *
  * @param[in]  hal_ll_state - True/False -- Init/De-init
  *
  * @return None
  */
static inline void hal_ll_i2c4_set_clock( bool hal_ll_state );

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
  * @param[in]  config - I2C config bits.
  * @return void None.
  */
static void hal_ll_i2c_master_configure_transfer( hal_ll_i2c_base_handle_t *hal_ll_hw_reg, uint32_t config );

/**
  * @brief  Reset value of I2C CR2 register.
  *
  * @param[in]  hal_ll_hw_reg  - I2C module base address.
  * @returnl none
  */
static void hal_ll_i2c_master_reset_cr2( hal_ll_i2c_base_handle_t *hal_ll_hw_reg );

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

    hal_ll_i2c_pin_id index_list[I2C_MODULE_COUNT] = {HAL_LL_PIN_NC,HAL_LL_PIN_NC};
    uint16_t pin_check_result;

    // Check if pins are valid
    if ( (pin_check_result = hal_ll_i2c_master_check_pins( scl, sda, &index_list, handle_map )) == HAL_LL_PIN_NC ) {
        return HAL_LL_I2C_MASTER_WRONG_PINS;
    };

    if ( (hal_ll_i2c_hw_specifics_map[pin_check_result]->pins.pin_scl.pin_name != scl) ||
         (hal_ll_i2c_hw_specifics_map[pin_check_result]->pins.pin_sda.pin_name != sda) )
    {
        hal_ll_i2c_master_alternate_functions_set_state( &hal_ll_i2c_hw_specifics_map[ pin_check_result ], false );

        hal_ll_i2c_master_map_pins( pin_check_result, &index_list );

        hal_ll_i2c_master_alternate_functions_set_state( &hal_ll_i2c_hw_specifics_map[ pin_check_result ], true );

        handle_map[pin_check_result]->init_ll_state = false;
    }

    *hal_module_id = pin_check_result;

    hal_ll_module_state[pin_check_result].hal_ll_i2c_master_handle = (handle_t *)&hal_ll_i2c_hw_specifics_map[pin_check_result].base;

    handle_map[pin_check_result]->hal_ll_i2c_master_handle = (handle_t *)&hal_ll_module_state[pin_check_result].hal_ll_i2c_master_handle;

    return HAL_LL_I2C_MASTER_SUCCESS;
}

hal_ll_err_t hal_ll_module_configure_i2c( handle_t *handle ) {
    hal_ll_i2c_hw_specifics_map_local = hal_ll_get_specifics(hal_ll_i2c_get_module_state_address);
    hal_ll_i2c_pin_id index_list[I2C_MODULE_COUNT] = {HAL_LL_PIN_NC,HAL_LL_PIN_NC};
    uint16_t pin_check_result;

    if ( (pin_check_result = hal_ll_i2c_master_check_pins( hal_ll_i2c_hw_specifics_map_local->pins.pin_scl.pin_name,
                                                           hal_ll_i2c_hw_specifics_map_local->pins.pin_scl.pin_name, &index_list, (void *)0 ) ) == HAL_LL_PIN_NC )
    {
        return HAL_LL_I2C_MASTER_WRONG_PINS;
    };

    hal_ll_i2c_init( hal_ll_i2c_hw_specifics_map_local );

    hal_ll_module_state[pin_check_result].hal_ll_i2c_master_handle = (handle_t *)&hal_ll_i2c_hw_specifics_map[pin_check_result].base;
    hal_ll_module_state[pin_check_result].init_ll_state = true;

    return HAL_LL_I2C_MASTER_SUCCESS;
}

hal_ll_err_t hal_ll_i2c_master_set_speed( handle_t *handle, uint32_t speed ) {
    low_level_handle = hal_ll_i2c_get_handle;
    hal_ll_i2c_hw_specifics_map_local = hal_ll_get_specifics(hal_ll_i2c_get_module_state_address);

    low_level_handle->init_ll_state = false;

    hal_ll_i2c_hw_specifics_map_local->speed = speed;

    if ( hal_ll_i2c_init( hal_ll_i2c_hw_specifics_map_local ) != HAL_LL_I2C_MASTER_SUCCESS ) {
        return HAL_LL_I2C_MASTER_TIMEOUT_INIT;
    }

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
    size_t transfer_counter = NULL;
    uint8_t status = NULL;

    /**
     * @note When R/W = 0, the input sample acquisition period starts
     * on the falling edge of SCL once the C0 bit of the command
     * byte has been latched, and ends when a Stop or
     * repeated Start condition has been issued.
     **/
    #ifdef __TFT_RESISTIVE_TSC2003__
    Delay_1ms();
    #endif

    hal_ll_i2c_master_configure_transfer ( map->base,
                                         ( map->address << 1 & HAL_LL_I2C_CR2_SADD ) |
                                         ( len_read_data << 16 & HAL_LL_I2C_CR2_NBYTES ) |
                                         HAL_LL_I2C_CR2_RD_WRN |
                                         HAL_LL_I2C_CR2_START
                                         );

    for ( transfer_counter; transfer_counter < len_read_data; transfer_counter++ ) {
        while ( !( check_reg_bit( &( hal_ll_hw_reg->isr ), HAL_LL_I2C_RXNE_BIT ) ) ) {
            if ( map->timeout ) {
                if ( !time_counter-- )
                    return HAL_LL_I2C_MASTER_TIMEOUT_READ;
            }
        }
        read_data_buf[ transfer_counter ] = hal_ll_hw_reg->rxdr;
    }

    if ( ( mode == HAL_LL_I2C_MASTER_END_MODE_STOP ) || ( mode == HAL_LL_I2C_MASTER_WRITE_THEN_READ ) ) {
        status = hal_ll_i2c_master_stop( map );
    } else {
        status = hal_ll_i2c_master_start( map );
    }

    if( status != HAL_LL_I2C_MASTER_SUCCESS ) {
        return status;
    }

    hal_ll_i2c_master_reset_cr2( hal_ll_hw_reg );

    return HAL_LL_I2C_MASTER_SUCCESS;
}

static hal_ll_err_t hal_ll_i2c_master_write_bare_metal( hal_ll_i2c_hw_specifics_map_t *map, uint8_t *write_data_buf, size_t len_write_data, hal_ll_i2c_master_end_mode_t mode ) {
    hal_ll_i2c_base_handle_t *hal_ll_hw_reg = hal_ll_i2c_get_base_struct(map->base);
    uint16_t time_counter = map->timeout;
    size_t transfer_counter = NULL;
    uint8_t status = NULL;

    hal_ll_i2c_master_configure_transfer ( map->base,
                                         ( map->address << 1 & HAL_LL_I2C_CR2_SADD ) |
                                         ( len_write_data << 16 & HAL_LL_I2C_CR2_NBYTES ) |
                                         !HAL_LL_I2C_CR2_RD_WRN |
                                         HAL_LL_I2C_CR2_START
                                         );

    for ( transfer_counter; transfer_counter < len_write_data; transfer_counter++ )
    {
        while ( !( check_reg_bit( &( hal_ll_hw_reg->isr ), HAL_LL_I2C_TXIS_BIT ) ) ) {
            if ( map->timeout ) {
                if ( !time_counter-- )
                    return HAL_LL_I2C_MASTER_TIMEOUT_WRITE;
            }
        }
        hal_ll_hw_reg->txdr = write_data_buf[ transfer_counter ];
    }

    time_counter = map->timeout;
    while ( !( check_reg_bit( &( hal_ll_hw_reg->isr ), HAL_LL_I2C_TXE_BIT ) ) ) {
        if ( map->timeout ) {
            if ( !time_counter-- )
                return HAL_LL_I2C_MASTER_TIMEOUT_WRITE;
        }
    }

    if ( mode == HAL_LL_I2C_MASTER_END_MODE_STOP )
    {
        hal_ll_i2c_master_stop( map );
    }

    hal_ll_i2c_master_reset_cr2( hal_ll_hw_reg );

    return HAL_LL_I2C_MASTER_SUCCESS;
}

static void hal_ll_i2c_master_configure_transfer( hal_ll_i2c_base_handle_t *hal_ll_hw_reg, uint32_t config ) {
    uint32_t reg = 0;

    // Clear last set slave address
    hal_ll_hw_reg->cr2 &= ~HAL_LL_I2C_CR2_SADD;

    reg = hal_ll_hw_reg->cr2;
    reg &= ~( uint32_t )(
                        ( HAL_LL_I2C_CR2_SADD ) |
                        ( HAL_LL_I2C_CR2_NBYTES ) |
                        ( HAL_LL_I2C_CR2_RELOAD ) |
                        ( HAL_LL_I2C_CR2_AUTOEND ) |
                        ( HAL_LL_I2C_CR2_RD_WRN ) |
                        ( HAL_LL_I2C_CR2_START ) |
                        ( HAL_LL_I2C_CR2_STOP )
                        );

    reg |= config;
    hal_ll_hw_reg->cr2 = reg;
}

static void hal_ll_i2c_master_reset_cr2( hal_ll_i2c_base_handle_t *hal_ll_hw_reg ) {
    hal_ll_hw_reg->cr2 &= ~( uint32_t )
                                    (
                                        HAL_LL_I2C_SADD_MASK |
                                        HAL_LL_I2C_HEAD10R_MASK |
                                        HAL_LL_I2C_NBYTES_MASK |
                                        HAL_LL_I2C_RELOAD_MASK |
                                        HAL_LL_I2C_RD_WRN_MASK
                                    );
}

static hal_ll_err_t hal_ll_i2c_master_start( hal_ll_i2c_hw_specifics_map_t *map ) {
    hal_ll_i2c_base_handle_t *hal_ll_hw_reg = hal_ll_i2c_get_base_struct(map->base);
    uint16_t loop_index = HAL_LL_I2C_LOOP_INDEX;

    set_reg_bit( &(hal_ll_hw_reg->cr2), HAL_LL_I2C_CR2_START_BIT );

    if ( check_reg_bit( &( hal_ll_hw_reg->isr ), HAL_LL_I2C_ARLO_BIT ) )
        return HAL_LL_I2C_MASTER_ARBITRATION_LOST;

    while ( loop_index-- )
        asm nop;

    return HAL_LL_I2C_MASTER_SUCCESS;
}

static hal_ll_err_t hal_ll_i2c_master_stop( hal_ll_i2c_hw_specifics_map_t *map ) {
    hal_ll_i2c_base_handle_t *hal_ll_hw_reg = ( hal_ll_i2c_base_handle_t* )map->base;
    uint16_t time_counter = map->timeout;
    uint32_t loop_index = HAL_LL_I2C_LOOP_INDEX;

    set_reg_bit( &(hal_ll_hw_reg->cr2), HAL_LL_I2C_CR2_STOP_BIT );

    while ( !( hal_ll_hw_reg->isr & HAL_LL_I2C_ISR_STOPF_BIT ) ) {
        if ( map->timeout ) {
            if ( !time_counter-- )
                return HAL_LL_I2C_MASTER_TIMEOUT_STOP;
        }
    }

    if ( map->timeout < HAL_LL_I2C_LOOP_INDEX ) {
        while ( loop_index-- )
            asm nop;
    }

    hal_ll_hw_reg->isr &= ~HAL_LL_I2C_ISR_STOPF_BIT;

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
                        // Get module number
                        hal_ll_module_id = hal_ll_i2c_scl_map[ scl_index ].module_index;
                        // Map pin names
                        index_list[hal_ll_module_id]->pin_scl = scl_index;
                        index_list[hal_ll_module_id]->pin_sda = sda_index;

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
    static uint8_t hal_ll_module_error = hal_ll_module_count;

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
            hal_ll_i2c1_set_clock( hal_ll_state );
            break;
        #endif
        #if defined(I2C_MODULE_2)
        case ( hal_ll_i2c_module_num(I2C_MODULE_2) ):
            hal_ll_i2c2_set_clock( hal_ll_state );
            break;
        #endif
        #if defined(I2C_MODULE_3)
        case ( hal_ll_i2c_module_num(I2C_MODULE_3) ):
            hal_ll_i2c3_set_clock( hal_ll_state );
            break;
        #endif
        #if defined(I2C_MODULE_4)
        case ( hal_ll_i2c_module_num(I2C_MODULE_4) ):
            hal_ll_i2c4_set_clock( hal_ll_state );
            break;
        #endif

        default:
            break;
    }
}

static void hal_ll_i2c_master_map_pins( uint8_t module_index, hal_ll_i2c_pin_id *index_list ) {
    // Map new pins
    hal_ll_i2c_hw_specifics_map[module_index]->pins.pin_scl.pin_name = hal_ll_i2c_scl_map[ index_list[module_index]->pin_scl ].pin;
    hal_ll_i2c_hw_specifics_map[module_index]->pins.pin_sda.pin_name = hal_ll_i2c_sda_map[ index_list[module_index]->pin_sda ].pin;
    // SCL and SDA could have different alternate function settings, hence save both AF values
    hal_ll_i2c_hw_specifics_map[module_index]->pins.pin_scl.pin_af = hal_ll_i2c_scl_map[ index_list[module_index]->pin_scl ].af;
    hal_ll_i2c_hw_specifics_map[module_index]->pins.pin_sda.pin_af = hal_ll_i2c_sda_map[ index_list[module_index]->pin_sda ].af;
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

        hal_ll_gpio_module_struct_init( &module, hal_ll_state );
    }
}

static uint32_t hal_ll_i2c_get_speed( hal_ll_i2c_hw_specifics_map_t *map ) {
    if ( map->speed <= HAL_LL_I2C_MASTER_SPEED_FAST ) {
        if ( map->speed <= HAL_LL_I2C_MASTER_SPEED_STANDARD ) {
            map->speed = HAL_LL_I2C_MASTER_SPEED_100K;
            return HAL_LL_I2C_100K;
        } else if ( map->speed <= HAL_LL_I2C_MASTER_SPEED_FULL ) {
            map->speed = HAL_LL_I2C_MASTER_SPEED_400K;
            return HAL_LL_I2C_400K;
        } else if ( map->speed <= HAL_LL_I2C_MASTER_SPEED_FAST ) {
            map->speed = HAL_LL_I2C_MASTER_SPEED_1M;
            return HAL_LL_I2C_1M;
        } else {
            map->speed = HAL_LL_I2C_MASTER_SPEED_100K;
            return HAL_LL_I2C_100K;
        }
    } else {
        if ( map->speed <= HAL_LL_I2C_MASTER_SPEED_100K ) {
            map->speed = HAL_LL_I2C_MASTER_SPEED_100K;
            return HAL_LL_I2C_100K;
        } else if ( map->speed <= HAL_LL_I2C_MASTER_SPEED_400K ) {
            map->speed = HAL_LL_I2C_MASTER_SPEED_400K;
            return HAL_LL_I2C_400K;
        } else if ( map->speed <= HAL_LL_I2C_MASTER_SPEED_1M ) {
            map->speed = HAL_LL_I2C_MASTER_SPEED_1M;
            return HAL_LL_I2C_1M;
        } else {
            map->speed = HAL_LL_I2C_MASTER_SPEED_1M;
            return HAL_LL_I2C_1M;
        }
    }
}

static inline void hal_ll_i2c1_set_clock( bool hal_ll_state ) {
    if ( hal_ll_state ) {
        #if defined(STM32F7xx)
        set_reg_bit( _RCC_APB1ENR, HAL_LL_I2C1EN_BIT );
        set_reg_bit( _RCC_DCKCFGR2, HAL_LL_I2C1SEL1_BIT );
        #elif defined(STM32H7xx)
        set_reg_bit( _RCC_APB1LENR, HAL_LL_I2C1EN_BIT );
        set_reg_bit( _RCC_D2CCIP2R, HAL_LL_I2C123SRC1_BIT );
        #elif defined(STM32L4xx)
        set_reg_bit( _RCC_APB1ENR1, HAL_LL_I2C1EN_BIT );
        set_reg_bit( _RCC_CCIPR, HAL_LL_I2C1SEL1_BIT );
        #elif defined(STM32F3xx)
        set_reg_bit( _RCC_APB1ENR, HAL_LL_I2C1EN_BIT );
        #elif defined(STM32F0xx)
        set_reg_bit( _RCC_APB1ENR, HAL_LL_I2C1EN_BIT );
        #elif defined(STM32L0xx)
        set_reg_bit( _RCC_CCIPR, HAL_LL_I2C1SEL0_BIT );
        clear_reg_bit( _RCC_CCIPR, HAL_LL_I2C1SEL1_BIT );
        set_reg_bit( _RCC_APB1ENR, HAL_LL_I2C1EN_BIT );
        #elif defined(STM32G0xx)
        set_reg_bit( _RCC_APB1ENR, HAL_LL_I2C1EN_BIT );
        #endif
    } else {
        #if defined(STM32F7xx)
        clear_reg_bit( _RCC_APB1ENR, HAL_LL_I2C1EN_BIT );
        clear_reg_bit( _RCC_DCKCFGR2, HAL_LL_I2C1SEL1_BIT );
        #elif defined(STM32H7xx)
        clear_reg_bit( _RCC_APB1LENR, HAL_LL_I2C1EN_BIT );
        clear_reg_bit( _RCC_D2CCIP2R, HAL_LL_I2C123SRC1_BIT );
        #elif defined(STM32L4xx)
        clear_reg_bit( _RCC_APB1ENR1, HAL_LL_I2C1EN_BIT );
        clear_reg_bit( _RCC_CCIPR, HAL_LL_I2C1SEL1_BIT );
        #elif defined(STM32F3xx)
        clear_reg_bit( _RCC_APB1ENR, HAL_LL_I2C1EN_BIT );
        #elif defined(STM32F0xx)
        clear_reg_bit( _RCC_APB1ENR, HAL_LL_I2C1EN_BIT );
        #elif defined(STM32L0xx)
        clear_reg_bit( _RCC_CCIPR, HAL_LL_I2C1SEL0_BIT );
        clear_reg_bit( _RCC_CCIPR, HAL_LL_I2C1SEL1_BIT );
        clear_reg_bit( _RCC_APB1ENR, HAL_LL_I2C1EN_BIT );
        #elif defined(STM32G0xx)
        clear_reg_bit( _RCC_APB1ENR, HAL_LL_I2C1EN_BIT );
        #endif
    }
}

static inline void hal_ll_i2c2_set_clock( bool hal_ll_state ) {
    if ( hal_ll_state ) {
        #if defined(STM32F7xx)
        set_reg_bit( _RCC_APB1ENR, HAL_LL_I2C2EN_BIT );
        set_reg_bit( _RCC_DCKCFGR2, HAL_LL_I2C2SEL1_BIT );
        #elif defined(STM32H7xx)
        set_reg_bit( _RCC_APB1LENR, HAL_LL_I2C2EN_BIT );
        set_reg_bit( _RCC_D2CCIP2R, HAL_LL_I2C123SRC1_BIT );
        #elif defined(STM32L4xx)
        set_reg_bit( _RCC_APB1ENR1, HAL_LL_I2C2EN_BIT );
        set_reg_bit( _RCC_CCIPR, HAL_LL_I2C2SEL1_BIT );
        #elif defined(STM32F3xx)
        set_reg_bit( _RCC_APB1ENR, HAL_LL_I2C2EN_BIT );
        #elif defined(STM32F0xx)
        set_reg_bit( _RCC_APB1ENR, HAL_LL_I2C2EN_BIT );
        #elif defined(STM32L0xx)
        set_reg_bit( _RCC_APB1ENR, HAL_LL_I2C2EN_BIT );
        #elif defined(STM32G0xx)
        set_reg_bit( _RCC_APB1ENR, HAL_LL_I2C2EN_BIT );
        #endif
    } else {
        #if defined(STM32F7xx)
        clear_reg_bit( _RCC_APB1ENR, HAL_LL_I2C2EN_BIT );
        clear_reg_bit( _RCC_DCKCFGR2, HAL_LL_I2C2SEL1_BIT );
        #elif defined(STM32H7xx)
        clear_reg_bit( _RCC_APB1LENR, HAL_LL_I2C2EN_BIT );
        clear_reg_bit( _RCC_D2CCIP2R, HAL_LL_I2C123SRC1_BIT );
        #elif defined(STM32L4xx)
        clear_reg_bit( _RCC_APB1ENR1, HAL_LL_I2C2EN_BIT );
        clear_reg_bit( _RCC_CCIPR, HAL_LL_I2C2SEL1_BIT );
        #elif defined(STM32F3xx)
        clear_reg_bit( _RCC_APB1ENR, HAL_LL_I2C2EN_BIT );
        #elif defined(STM32F0xx)
        clear_reg_bit( _RCC_APB1ENR, HAL_LL_I2C2EN_BIT );
        #elif defined(STM32L0xx)
        clear_reg_bit( _RCC_APB1ENR, HAL_LL_I2C2EN_BIT );
        #elif defined(STM32G0xx)
        clear_reg_bit( _RCC_APB1ENR, HAL_LL_I2C2EN_BIT );
        #endif
    }
}

static inline void hal_ll_i2c3_set_clock( bool hal_ll_state ) {
    if ( hal_ll_state ) {
        #if defined(STM32F7xx)
        set_reg_bit( _RCC_APB1ENR, HAL_LL_I2C3EN_BIT );
        set_reg_bit( _RCC_DCKCFGR2, HAL_LL_I2C3SEL1_BIT );
        #elif defined(STM32H7xx)
        set_reg_bit( _RCC_APB1LENR, HAL_LL_I2C3EN_BIT );
        set_reg_bit( _RCC_D2CCIP2R, HAL_LL_I2C123SRC1_BIT );
        #elif defined(STM32L4xx)
        set_reg_bit( _RCC_APB1ENR1, HAL_LL_I2C3EN_BIT );
        set_reg_bit( _RCC_CCIPR, HAL_LL_I2C3SEL1_BIT );
        #elif defined(STM32F3xx)
        set_reg_bit( _RCC_APB1ENR, HAL_LL_I2C3EN_BIT );
        #elif defined(STM32L0xx)
        set_reg_bit( _RCC_APB1ENR, HAL_LL_I2C3EN_BIT );
        #endif
    } else {
        #if defined(STM32F7xx)
        clear_reg_bit( _RCC_APB1ENR, HAL_LL_I2C3EN_BIT );
        clear_reg_bit( _RCC_DCKCFGR2, HAL_LL_I2C3SEL1_BIT );
        #elif defined(STM32H7xx)
        clear_reg_bit( _RCC_APB1LENR, HAL_LL_I2C3EN_BIT );
        clear_reg_bit( _RCC_D2CCIP2R, HAL_LL_I2C123SRC1_BIT );
        #elif defined(STM32L4xx)
        clear_reg_bit( _RCC_APB1ENR1, HAL_LL_I2C3EN_BIT );
        clear_reg_bit( _RCC_CCIPR, HAL_LL_I2C3SEL1_BIT );
        #elif defined(STM32F3xx)
        clear_reg_bit( _RCC_APB1ENR, HAL_LL_I2C3EN_BIT );
        #elif defined(STM32L0xx)
        clear_reg_bit( _RCC_APB1ENR, HAL_LL_I2C3EN_BIT );
        #endif
    }
}

static inline void hal_ll_i2c4_set_clock( bool hal_ll_state ) {
    if ( hal_ll_state ) {
        #if defined(STM32F7xx)
        set_reg_bit( _RCC_APB1ENR, HAL_LL_I2C4EN_BIT );
        set_reg_bit( _RCC_DCKCFGR2, HAL_LL_I2C4SEL1_BIT );
        #elif defined(STM32H7xx)
        set_reg_bit( _RCC_APB4ENR, HAL_LL_I2C4EN_BIT );
        set_reg_bit( _RCC_D3CCIPR, HAL_LL_I2C4SRC1_BIT );
        #elif defined(STM32L4xx)
        set_reg_bit( _RCC_APB1ENR2, HAL_LL_I2C4EN_BIT );
        set_reg_bit( _RCC_CCIPR2, HAL_LL_I2C4SEL1_BIT );
        #endif
    } else {
        #if defined(STM32F7xx)
        clear_reg_bit( _RCC_APB1ENR, HAL_LL_I2C4EN_BIT );
        clear_reg_bit( _RCC_DCKCFGR2, HAL_LL_I2C4SEL1_BIT );
        #elif defined(STM32H7xx)
        clear_reg_bit( _RCC_APB4ENR, HAL_LL_I2C4EN_BIT );
        clear_reg_bit( _RCC_D3CCIPR, HAL_LL_I2C4SRC1_BIT );
        #elif defined(STM32L4xx)
        clear_reg_bit( _RCC_APB1ENR2, HAL_LL_I2C4EN_BIT );
        clear_reg_bit( _RCC_CCIPR2, HAL_LL_I2C4SEL1_BIT );
        #endif
    }
}

static hal_ll_err_t hal_ll_i2c_hw_init( hal_ll_i2c_hw_specifics_map_t *map ) {
    hal_ll_i2c_base_handle_t *hal_ll_hw_reg = hal_ll_i2c_get_base_struct(map->base);
    uint16_t time_counter = map->timeout;

    clear_reg_bit( &( hal_ll_hw_reg->cr1 ), HAL_LL_I2C_PE_BIT );
    while ( check_reg_bit( &( hal_ll_hw_reg->cr1 ), HAL_LL_I2C_PE_BIT ) ) {
        if ( map->timeout ) {
            if ( !time_counter-- )
                return HAL_LL_I2C_MASTER_TIMEOUT_INIT;
        }
    }

    hal_ll_hw_reg->cr1 &= HAL_LL_I2C_FILTERS_OFF;

    hal_ll_hw_reg->timingr = hal_ll_i2c_get_speed( map );

    hal_ll_hw_reg->cr1 |= HAL_LL_I2C_CR1_RXTX_INT;

    set_reg_bit( &( hal_ll_hw_reg->cr1 ), HAL_LL_I2C_PE_BIT );

    return HAL_LL_I2C_MASTER_SUCCESS;
}

static hal_ll_err_t hal_ll_i2c_init( hal_ll_i2c_hw_specifics_map_t *map ) {
    hal_ll_i2c_master_set_clock( map, true );

    return hal_ll_i2c_hw_init( map );
}
// ------------------------------------------------------------------------- END
