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
#include "hal_ll_gpio.h"
#include "hal_ll_i2c_master.h"
#include "hal_ll_i2c_pin_map.h"
#include "hal_ll_mstpcr.h"
#include "delays.h"
#include "mcu.h" // TODO Esma

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

#define HAL_LL_I2C_AF_CONFIG 0xFF // TODO Esma

/*!< @brief Bit positions and masks */
#define HAL_LL_I2C_ICCR1_IICRST (6)
#define HAL_LL_I2C_ICCR1_ICE (7)
#define HAL_LL_I2C_ICCR2_BBSY (7)
#define HAL_LL_I2C_ICCR2_ST (1)
#define HAL_LL_I2C_ICCR2_SP (3)
#define HAL_LL_I2C_ICSR2_TDRE (7)
#define HAL_LL_I2C_ICSR2_NACKF (4)
#define HAL_LL_I2C_ICSR2_TEND (6)
#define HAL_LL_I2C_ICSR2_STOP (3)
#define HAL_LL_I2C_ICSR2_RDRF (5)
#define HAL_LL_I2C_ICMR3_WAIT (6)
#define HAL_LL_I2C_ICMR3_ACKBT (3)
#define HAL_LL_I2C_ICMR3_ACKWP (4)
#define HAL_LL_I2C_ICFER_SCLE (6)
#define HAL_LL_I2C_ICFER_NFE (5)

/*!< @brief Default I2C bit-rate if no speed is set */
#define HAL_LL_I2C_MASTER_SPEED_100K                (100000UL)
#define HAL_LL_I2C_MASTER_SPEED_400K                (400000UL)
#define HAL_LL_I2C_MASTER_SPEED_1M                  (1000000UL)
#define HAL_LL_I2C_MASTER_SPEED_3M2                 (3200000UL)

#define HAL_LL_I2C_DEFAULT_PASS_COUNT               (10000)

/*!< @brief I2C register structure */
typedef struct {
    hal_ll_base_addr_t iccr1; // IIC0.ICCR1 4005 3000h, IIC1.ICCR1 4005 3100h
    hal_ll_base_addr_t iccr2; // IIC0.ICCR2 4005 3001h, IIC1.ICCR2 4005 3101h
    hal_ll_base_addr_t icmr1; // IIC0.ICCR2 4005 3002h, IIC1.ICCR2 4005 3102h
    hal_ll_base_addr_t icmr2; // IIC0.ICCR2 4005 3003h, IIC1.ICCR2 4005 3103h
    hal_ll_base_addr_t icmr3; // IIC0.ICCR2 4005 3004h, IIC1.ICCR2 4005 3104h
    hal_ll_base_addr_t icfer; // IIC0.ICCR2 4005 3005h, IIC1.ICCR2 4005 3105h
    hal_ll_base_addr_t icser; // IIC0.ICCR2 4005 3006h, IIC1.ICCR2 4005 3106h
    hal_ll_base_addr_t icier; // IIC0.ICCR2 4005 3007h, IIC1.ICCR2 4005 3107h
    hal_ll_base_addr_t icsr1; // IIC0.ICCR2 4005 3008h, IIC1.ICCR2 4005 3108h
    hal_ll_base_addr_t icsr2; // IIC0.ICCR2 4005 3009h, IIC1.ICCR2 4005 3109h
    hal_ll_base_addr_t sarl[3]; // ?
    hal_ll_base_addr_t saru[3]; // ?
    hal_ll_base_addr_t icbrl; // IIC0.ICCR2 4005 3010h, IIC1.ICCR2 4005 3110h
    hal_ll_base_addr_t icbrh; // IIC0.ICCR2 4005 3011h, IIC1.ICCR2 4005 3111h
    hal_ll_base_addr_t icdrt; // IIC0.ICCR2 4005 3012h, IIC1.ICCR2 4005 3112h
    hal_ll_base_addr_t icdrr; // IIC0.ICCR2 4005 3013h, IIC1.ICCR2 4005 3113h
    // hal_ll_base_addr_t icdrs; // ?
    hal_ll_base_addr_t reserved[2];
    hal_ll_base_addr_t icwur; // IIC0.ICCR2 4005 3016h // ? , IIC1.ICCR2 4005 3109h
    hal_ll_base_addr_t icwur2; // IIC0.ICCR2 4005 3017h // ? , IIC1.ICCR2 4005 3109h
} hal_ll_i2c_base_handle_t;

/*!< @brief I2C hw specific structure */
typedef struct {
    uint32_t base;
    hal_ll_pin_name_t module_index;
    hal_ll_i2c_pins_t pins;
    uint32_t speed;
    uint8_t address;
    uint16_t timeout;
} hal_ll_i2c_hw_specifics_map_t;

/*!< @brief I2C hw specific module values */
typedef struct {
    uint32_t pin_scl;
    uint32_t pin_sda;
} hal_ll_i2c_pin_id;

/*!< @brief I2C end mode selection values */
typedef enum {
    HAL_LL_I2C_MASTER_END_MODE_RESTART = 0,
    HAL_LL_I2C_MASTER_END_MODE_STOP,
    HAL_LL_I2C_MASTER_WRITE_THEN_READ
} hal_ll_i2c_master_end_mode_t;

/*!< @brief I2C hw specific error values */
typedef enum {
    HAL_LL_I2C_MASTER_SUCCESS = 0,
    HAL_LL_I2C_MASTER_WRONG_PINS,
    HAL_LL_I2C_MASTER_MODULE_ERROR,

    HAL_LL_I2C_MASTER_ERROR = (-1)
} hal_ll_i2c_master_err_t;

/*!< @brief I2C timeout error values */
typedef enum {
    HAL_LL_I2C_MASTER_TIMEOUT_START = 1300,
    HAL_LL_I2C_MASTER_TIMEOUT_STOP,
    HAL_LL_I2C_MASTER_TIMEOUT_WRITE,
    HAL_LL_I2C_MASTER_TIMEOUT_READ,
    HAL_LL_I2C_MASTER_ARBITRATION_LOST,
    HAL_LL_I2C_MASTER_TIMEOUT_INIT,
    HAL_LL_I2C_MASTER_TIMEOUT_WAIT_IDLE
} hal_ll_i2c_master_timeout_t;

/*!< @brief Enum containing predefined module standard speed values */
typedef enum {
    HAL_LL_I2C_MASTER_SPEED_STANDARD = 0,
    HAL_LL_I2C_MASTER_SPEED_FULL,
    HAL_LL_I2C_MASTER_SPEED_FAST
} hal_ll_i2c_master_speed_t;

// ------------------------------------------------------------------ VARIABLES
static hal_ll_i2c_hw_specifics_map_t hal_ll_i2c_hw_specifics_map[ I2C_MODULE_COUNT + 1 ] = {
    #ifdef I2C_MODULE_0
    {0x40053000UL, hal_ll_i2c_module_num( I2C_MODULE_0 ), {HAL_LL_PIN_NC, 0, HAL_LL_PIN_NC, 0}, HAL_LL_I2C_MASTER_SPEED_100K , 0, HAL_LL_I2C_DEFAULT_PASS_COUNT},
    #endif
    #ifdef I2C_MODULE_1
    {0x40053100UL, hal_ll_i2c_module_num( I2C_MODULE_1 ), {HAL_LL_PIN_NC, 0, HAL_LL_PIN_NC, 0}, HAL_LL_I2C_MASTER_SPEED_100K , 0, HAL_LL_I2C_DEFAULT_PASS_COUNT},
    #endif
    #ifdef I2C_MODULE_2
    {HAL_LL_I2C2_BASE_ADDR, hal_ll_i2c_module_num( I2C_MODULE_2 ), {HAL_LL_PIN_NC, 0, HAL_LL_PIN_NC, 0}, HAL_LL_I2C_MASTER_SPEED_100K , 0, HAL_LL_I2C_DEFAULT_PASS_COUNT},
    #endif
    #ifdef I2C_MODULE_3
    {HAL_LL_I2C3_BASE_ADDR, hal_ll_i2c_module_num( I2C_MODULE_3 ), {HAL_LL_PIN_NC, 0, HAL_LL_PIN_NC, 0}, HAL_LL_I2C_MASTER_SPEED_100K , 0, HAL_LL_I2C_DEFAULT_PASS_COUNT},
    #endif
    #ifdef I2C_MODULE_4
    {HAL_LL_I2C4_BASE_ADDR, hal_ll_i2c_module_num( I2C_MODULE_4 ), {HAL_LL_PIN_NC, 0, HAL_LL_PIN_NC, 0}, HAL_LL_I2C_MASTER_SPEED_100K , 0, HAL_LL_I2C_DEFAULT_PASS_COUNT},
    #endif
    #ifdef I2C_MODULE_5
    {HAL_LL_I2C5_BASE_ADDR, hal_ll_i2c_module_num( I2C_MODULE_5 ), {HAL_LL_PIN_NC, 0, HAL_LL_PIN_NC, 0}, HAL_LL_I2C_MASTER_SPEED_100K , 0, HAL_LL_I2C_DEFAULT_PASS_COUNT},
    #endif
    #ifdef I2C_MODULE_6
    {HAL_LL_I2C6_BASE_ADDR, hal_ll_i2c_module_num( I2C_MODULE_6 ), {HAL_LL_PIN_NC, 0, HAL_LL_PIN_NC, 0}, HAL_LL_I2C_MASTER_SPEED_100K , 0, HAL_LL_I2C_DEFAULT_PASS_COUNT},
    #endif
    #ifdef I2C_MODULE_7
    {HAL_LL_I2C7_BASE_ADDR, hal_ll_i2c_module_num( I2C_MODULE_7 ), {HAL_LL_PIN_NC, 0, HAL_LL_PIN_NC, 0}, HAL_LL_I2C_MASTER_SPEED_100K , 0, HAL_LL_I2C_DEFAULT_PASS_COUNT},
    #endif
    #ifdef I2C_MODULE_8
    {HAL_LL_I2C8_BASE_ADDR, hal_ll_i2c_module_num( I2C_MODULE_8 ), {HAL_LL_PIN_NC, 0, HAL_LL_PIN_NC, 0}, HAL_LL_I2C_MASTER_SPEED_100K , 0, HAL_LL_I2C_DEFAULT_PASS_COUNT},
    #endif
    #ifdef I2C_MODULE_9
    {HAL_LL_I2C9_BASE_ADDR, hal_ll_i2c_module_num( I2C_MODULE_9 ), {HAL_LL_PIN_NC, 0, HAL_LL_PIN_NC, 0}, HAL_LL_I2C_MASTER_SPEED_100K , 0, HAL_LL_I2C_DEFAULT_PASS_COUNT},
    #endif

    {HAL_LL_MODULE_ERROR, HAL_LL_MODULE_ERROR, {HAL_LL_PIN_NC, 0, HAL_LL_PIN_NC, 0}, 0, 0, 0}
};

/*!< @brief Global handle variables used in functions */
static volatile hal_ll_i2c_master_handle_register_t *low_level_handle;
static volatile hal_ll_i2c_hw_specifics_map_t *hal_ll_i2c_hw_specifics_map_local;

// ---------------------------------------------- PRIVATE FUNCTION DECLARATIONS

/**
  * @brief  Initialize I2C module on hardware level.
  *
  * Initializes I2C module on hardware level, based on beforehand
  * set configuration and module handler.
  *
  * @param[in]  *map - Object specific context handler.
  * @return None
  *
  * Returns one of pre-defined values.
  * Take into consideration that this is hardware specific.
  */
static void hal_ll_i2c_hw_init( hal_ll_i2c_hw_specifics_map_t *map );

// TODO Esma
static void hal_ll_i2c_calculate_speed( hal_ll_i2c_hw_specifics_map_t *map, uint32_t clock_value );

/**
  * @brief  Full I2C module initialization procedure.
  *
  * Initializes I2C module on hardware level, based on beforehand
  * set configuration and module handler. Sets adequate pin alternate functions.
  * Initializes module clock.
  *
  * @param[in]  *map - Object specific context handler.
  * @return None
  *
  * Returns one of pre-defined values.
  * Take into consideration that this is hardware specific.
  */
static void hal_ll_i2c_init( hal_ll_i2c_hw_specifics_map_t *map );

/**
  * @brief  Sets I2C pin alternate function state.
  *
  * Sets adequate value for alternate function settings.
  * This function must be called if I2C is to work.
  * Based on value of hal_ll_state, alternate functions can be
  * set or cleared.
  *
  * @param[in]  *map - Object specific context handler.
  * @param[in]  hal_ll_state - Init/De-init
  *
  * @return  None
  */
static void hal_ll_i2c_master_alternate_functions_set_state( hal_ll_i2c_hw_specifics_map_t *map,
                                                             bool hal_ll_state );

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
static hal_ll_pin_name_t hal_ll_i2c_master_check_pins( hal_ll_pin_name_t scl,
                                                       hal_ll_pin_name_t sda,
                                                       hal_ll_i2c_pin_id *index_list,
                                                       hal_ll_i2c_master_handle_register_t *handle_map );

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
  * @brief  Waits until device is free to operate.
  *
  * Polls I2C busy bit value and waits until device has finished any
  * on-going operation.
  *
  * @param[in]  *map - Object specific context handler.
  * @return hal_ll_err_t Module specific values.
  */
static hal_ll_err_t hal_ll_i2c_master_wait_for_idle( hal_ll_i2c_hw_specifics_map_t *map ) ;

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
  * @brief  Perform a read on the I2C bus.
  *
  * Initializes I2C module on hardware level, if not initialized beforehand
  * and continues to perform a read operation on the bus.
  *
  * @param[in]  *map - Object specific context handler.
  * @param[in]  *readDatabuf - Pointer to data buffer.
  * @param[in]  lenReadData - Number of data to be read.
  * @return hal_ll_err_t Module specific values.
  *
  * Returns one of pre-defined values.
  * Take into consideration that this is hardware specific.
  */
static hal_ll_err_t hal_ll_i2c_master_read_bare_metal( hal_ll_i2c_hw_specifics_map_t *map,
                                                       uint8_t *read_data_buf,
                                                       size_t len_read_data, hal_ll_i2c_master_end_mode_t mode );

/**
  * @brief  Perform a write on the I2C bus.
  *
  * Initializes I2C module on hardware level, if not initialized beforehand
  * and continues to perform a write operation on the bus.
  *
  * @param[in]  *map - Object specific context handler.
  * @param[in]  *writeDatabuf - Pointer to data buffer.
  * @param[in]  lenWriteData - Number of data to be written.
  * @return hal_ll_err_t Module specific values.
  *
  * Returns one of pre-defined values.
  * Take into consideration that this is hardware specific.
  */
static hal_ll_err_t hal_ll_i2c_master_write_bare_metal( hal_ll_i2c_hw_specifics_map_t *map,
                                                        uint8_t *write_data_buf,
                                                        size_t len_write_data, hal_ll_i2c_master_end_mode_t mode );

// ------------------------------------------------ PUBLIC FUNCTION DEFINITIONS
hal_ll_err_t hal_ll_i2c_master_register_handle( hal_ll_pin_name_t scl,
                                                hal_ll_pin_name_t sda,
                                                hal_ll_i2c_master_handle_register_t *handle_map,
                                                uint8_t *hal_module_id ) {
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

    hal_ll_module_state[pin_check_result].hal_ll_i2c_master_handle =
            (handle_t *)&hal_ll_i2c_hw_specifics_map[pin_check_result].base;

    handle_map[pin_check_result].hal_ll_i2c_master_handle =
            (handle_t *)&hal_ll_module_state[pin_check_result].hal_ll_i2c_master_handle;

    return HAL_LL_I2C_MASTER_SUCCESS;
}

hal_ll_err_t hal_ll_module_configure_i2c( handle_t *handle ) {
    hal_ll_i2c_hw_specifics_map_local = hal_ll_get_specifics( hal_ll_i2c_get_module_state_address );
    hal_ll_i2c_master_handle_register_t *hal_handle = (hal_ll_i2c_master_handle_register_t *)*handle;
    uint8_t pin_check_result = hal_ll_i2c_hw_specifics_map_local->module_index;

    hal_ll_i2c_init( hal_ll_i2c_hw_specifics_map_local );

    hal_ll_module_state[ pin_check_result ].hal_ll_i2c_master_handle =
            ( handle_t * )&hal_ll_i2c_hw_specifics_map[ pin_check_result ].base;

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

    return hal_ll_i2c_master_read_bare_metal( hal_ll_i2c_hw_specifics_map_local,
                                              read_data_buf,
                                              len_read_data,
                                              HAL_LL_I2C_MASTER_END_MODE_STOP );
}

hal_ll_err_t hal_ll_i2c_master_write( handle_t *handle, uint8_t *write_data_buf, size_t len_write_data ) {
    low_level_handle = hal_ll_i2c_get_handle;
    hal_ll_i2c_hw_specifics_map_local = hal_ll_get_specifics( hal_ll_i2c_get_module_state_address );

    return hal_ll_i2c_master_write_bare_metal( hal_ll_i2c_hw_specifics_map_local,
                                               write_data_buf,
                                               len_write_data,
                                               HAL_LL_I2C_MASTER_END_MODE_STOP );
}

hal_ll_err_t hal_ll_i2c_master_write_then_read( handle_t *handle,
                                                uint8_t *write_data_buf,
                                                size_t len_write_data,
                                                uint8_t *read_data_buf,
                                                size_t len_read_data ) {
    low_level_handle = hal_ll_i2c_get_handle;
    hal_ll_i2c_hw_specifics_map_local = hal_ll_get_specifics( hal_ll_i2c_get_module_state_address );

    if( NULL != hal_ll_i2c_master_write_bare_metal( hal_ll_i2c_hw_specifics_map_local,
                                                    write_data_buf,
                                                    len_write_data,
                                                    HAL_LL_I2C_MASTER_WRITE_THEN_READ ) ) {
        return HAL_LL_I2C_MASTER_TIMEOUT_WRITE;
    }

    /**
     * @note Wait for drivers to set-up
     * correctly.
     **/
    #ifdef __TFT_RESISTIVE_TSC2003__
    Delay_22us();
    #endif

    if( NULL != hal_ll_i2c_master_read_bare_metal( hal_ll_i2c_hw_specifics_map_local,
                                                   read_data_buf,
                                                   len_read_data,
                                                   HAL_LL_I2C_MASTER_WRITE_THEN_READ ) ) {
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

        hal_ll_i2c_master_alternate_functions_set_state( hal_ll_i2c_hw_specifics_map_local, false );

        hal_ll_i2c_hw_specifics_map_local->pins.pin_scl.pin_name = HAL_LL_PIN_NC;
        hal_ll_i2c_hw_specifics_map_local->pins.pin_sda.pin_name = HAL_LL_PIN_NC;
        hal_ll_i2c_hw_specifics_map_local->pins.pin_scl.pin_af = 0;
        hal_ll_i2c_hw_specifics_map_local->pins.pin_sda.pin_af = 0;
    }
}
// ----------------------------------------------- PRIVATE FUNCTION DEFINITIONS
static hal_ll_err_t hal_ll_i2c_master_write_bare_metal( hal_ll_i2c_hw_specifics_map_t *map,
                                                        uint8_t *write_data_buf,
                                                        size_t len_write_data,
                                                        hal_ll_i2c_master_end_mode_t mode ) {
    hal_ll_i2c_base_handle_t *hal_ll_hw_reg = hal_ll_i2c_get_base_struct( map->base );
    uint16_t time_counter = map->timeout;

    hal_ll_i2c_master_wait_for_idle( map );

    set_reg_bit( &hal_ll_hw_reg->iccr2, HAL_LL_I2C_ICCR2_ST );

    while( !check_reg_bit( &hal_ll_hw_reg->icsr2, HAL_LL_I2C_ICSR2_TDRE ));

    write_reg( &hal_ll_hw_reg->icdrt, map->address << 1 );

    while( !check_reg_bit( &hal_ll_hw_reg->icsr2, HAL_LL_I2C_ICSR2_TDRE ));

    if( check_reg_bit( &hal_ll_hw_reg->icsr2, HAL_LL_I2C_ICSR2_NACKF ))
        set_reg_bit( &hal_ll_hw_reg->iccr2, HAL_LL_I2C_ICCR2_SP );

    for( uint8_t i = 0; i < len_write_data; i++ ) {
        while( !check_reg_bit( &hal_ll_hw_reg->icsr2, HAL_LL_I2C_ICSR2_TDRE ));
        write_reg( &hal_ll_hw_reg->icdrt, write_data_buf[i] );
    }

    while( !check_reg_bit( &hal_ll_hw_reg->icsr2, HAL_LL_I2C_ICSR2_TEND ));

    clear_reg_bit( &hal_ll_hw_reg->icsr2, HAL_LL_I2C_ICSR2_STOP );
    set_reg_bit( &hal_ll_hw_reg->iccr2, HAL_LL_I2C_ICCR2_SP );

    while( !check_reg_bit( &hal_ll_hw_reg->icsr2, HAL_LL_I2C_ICSR2_STOP ));

    set_reg_bit( &hal_ll_hw_reg->icsr2, HAL_LL_I2C_ICSR2_NACKF );
    clear_reg_bit( &hal_ll_hw_reg->icsr2, HAL_LL_I2C_ICSR2_STOP );

    return HAL_LL_I2C_MASTER_SUCCESS; // TODO ESMA: add timeout and returning errors
}

static hal_ll_err_t hal_ll_i2c_master_read_bare_metal( hal_ll_i2c_hw_specifics_map_t *map,
                                                       uint8_t *read_data_buf,
                                                       size_t len_read_data,
                                                       hal_ll_i2c_master_end_mode_t mode ) {
    hal_ll_i2c_base_handle_t *hal_ll_hw_reg = hal_ll_i2c_get_base_struct( map->base );
    uint16_t time_counter = map->timeout;
    uint8_t dummy_read;

    hal_ll_i2c_master_wait_for_idle( map );

    set_reg_bit( &hal_ll_hw_reg->iccr2, HAL_LL_I2C_ICCR2_ST );

    while( !check_reg_bit( &hal_ll_hw_reg->icsr2, HAL_LL_I2C_ICSR2_TDRE ));

    write_reg( &hal_ll_hw_reg->icdrt, ( map->address << 1 ) | 1 );

    while( !check_reg_bit( &hal_ll_hw_reg->icsr2, HAL_LL_I2C_ICSR2_RDRF ));

    if( check_reg_bit( &hal_ll_hw_reg->icsr2, HAL_LL_I2C_ICSR2_NACKF )) {
        // Error
        clear_reg_bit( &hal_ll_hw_reg->icsr2, HAL_LL_I2C_ICSR2_STOP );
        set_reg_bit( &hal_ll_hw_reg->iccr2, HAL_LL_I2C_ICCR2_SP );
        dummy_read = read_reg( &hal_ll_hw_reg->icdrr );
    } else {
        set_reg_bit( &hal_ll_hw_reg->icmr3, HAL_LL_I2C_ICMR3_WAIT );
        if( 1 != len_read_data ) {
            for( uint8_t i = 0; i < len_read_data - 2; i++ ) {
                read_data_buf[i] = read_reg( &hal_ll_hw_reg->icdrr );
                while( !check_reg_bit( &hal_ll_hw_reg->icsr2, HAL_LL_I2C_ICSR2_RDRF ));
            }
        }

        set_reg_bit( &hal_ll_hw_reg->icmr3, HAL_LL_I2C_ICMR3_ACKWP );
        set_reg_bit( &hal_ll_hw_reg->icmr3, HAL_LL_I2C_ICMR3_ACKBT );
        clear_reg_bit( &hal_ll_hw_reg->icmr3, HAL_LL_I2C_ICMR3_ACKWP );

        read_data_buf[len_read_data - 2] = read_reg( &hal_ll_hw_reg->icdrr );

        while( !check_reg_bit( &hal_ll_hw_reg->icsr2, HAL_LL_I2C_ICSR2_RDRF ));

        clear_reg_bit( &hal_ll_hw_reg->icsr2, HAL_LL_I2C_ICSR2_STOP );
        set_reg_bit( &hal_ll_hw_reg->iccr2, HAL_LL_I2C_ICCR2_SP );

        read_data_buf[len_read_data - 1] = read_reg( &hal_ll_hw_reg->icdrr );
        clear_reg_bit( &hal_ll_hw_reg->icmr3, HAL_LL_I2C_ICMR3_WAIT );
    }

    while( !check_reg_bit( &hal_ll_hw_reg->icsr2, HAL_LL_I2C_ICSR2_STOP ));

    clear_reg_bit( &hal_ll_hw_reg->icsr2, HAL_LL_I2C_ICSR2_NACKF );
    clear_reg_bit( &hal_ll_hw_reg->icsr2, HAL_LL_I2C_ICSR2_STOP );

    return HAL_LL_I2C_MASTER_SUCCESS;
}

static void hal_ll_i2c_master_alternate_functions_set_state( hal_ll_i2c_hw_specifics_map_t *map, bool hal_ll_state ) {
    module_struct module;

    if( (map->pins.pin_scl.pin_name != HAL_LL_PIN_NC) && (map->pins.pin_sda.pin_name != HAL_LL_PIN_NC) ) {
        module.pins[0] = VALUE( map->pins.pin_scl.pin_name, map->pins.pin_scl.pin_af );
        module.pins[1] = VALUE( map->pins.pin_sda.pin_name, map->pins.pin_sda.pin_af );
        module.pins[2] = GPIO_MODULE_STRUCT_END;

        module.configs[0] = HAL_LL_I2C_AF_CONFIG; // TODO
        module.configs[1] = HAL_LL_I2C_AF_CONFIG; // TODO
        module.configs[2] = GPIO_MODULE_STRUCT_END;

        hal_ll_gpio_module_struct_init( &module, hal_ll_state );
    }
}

static void hal_ll_i2c_master_map_pins( uint8_t module_index, hal_ll_i2c_pin_id *index_list ) {
    // Map new pins
    hal_ll_i2c_hw_specifics_map[module_index].pins.pin_scl.pin_name =
                        hal_ll_i2c_scl_map[ index_list[module_index].pin_scl ].pin;
    hal_ll_i2c_hw_specifics_map[module_index].pins.pin_sda.pin_name =
                        hal_ll_i2c_sda_map[ index_list[module_index].pin_sda ].pin;
    // SCL and SDA could have different alternate function settings,
    // hence save both AF values
    hal_ll_i2c_hw_specifics_map[module_index].pins.pin_scl.pin_af =
                        hal_ll_i2c_scl_map[ index_list[module_index].pin_scl ].af;
    hal_ll_i2c_hw_specifics_map[module_index].pins.pin_sda.pin_af =
                        hal_ll_i2c_sda_map[ index_list[module_index].pin_sda ].af;
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

static hal_ll_pin_name_t hal_ll_i2c_master_check_pins( hal_ll_pin_name_t scl,
                                                       hal_ll_pin_name_t sda,
                                                       hal_ll_i2c_pin_id *index_list,
                                                       hal_ll_i2c_master_handle_register_t *handle_map ) {
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

static hal_ll_err_t hal_ll_i2c_master_wait_for_idle( hal_ll_i2c_hw_specifics_map_t *map ) {
    hal_ll_i2c_base_handle_t *hal_ll_hw_reg = hal_ll_i2c_get_base_struct( map->base );

    while( check_reg_bit( &hal_ll_hw_reg->iccr2, HAL_LL_I2C_ICCR2_BBSY ));

    return 0;
}

static void hal_ll_i2c_calculate_speed( hal_ll_i2c_hw_specifics_map_t *map, uint32_t clock_value ) {
    hal_ll_i2c_base_handle_t *hal_ll_hw_reg = hal_ll_i2c_get_base_struct( map->base );
    // 32MHz on PCLKB, 100kbps I2C

    write_reg( &hal_ll_hw_reg->icmr1, 0x3 << 4 );
    set_reg_bit( &hal_ll_hw_reg->icfer, HAL_LL_I2C_ICFER_SCLE );
    set_reg_bit( &hal_ll_hw_reg->icfer, HAL_LL_I2C_ICFER_NFE );
    write_reg( &hal_ll_hw_reg->icbrl, 0xF2 );
    write_reg( &hal_ll_hw_reg->icbrh, 0xF0 );
}

static void hal_ll_i2c_hw_init( hal_ll_i2c_hw_specifics_map_t *map ) {
    hal_ll_i2c_base_handle_t *hal_ll_hw_reg = hal_ll_i2c_get_base_struct( map->base );

    // I2C initialization
    // Set the ICCR1.ICE bit set to 0 to set the SCLn and SDAn pins to the inactive state.
    clear_reg_bit( &hal_ll_hw_reg->iccr1, HAL_LL_I2C_ICCR1_ICE );
    // Set the ICCR1.IICRST bit to 1 to initiate IIC reset
    set_reg_bit( &hal_ll_hw_reg->iccr1, HAL_LL_I2C_ICCR1_IICRST );
    // Set the ICCR1.ICE bit to 1 to initiate internal reset.
    set_reg_bit( &hal_ll_hw_reg->iccr1, HAL_LL_I2C_ICCR1_ICE );

    clear_reg( &hal_ll_hw_reg->icser );
}

static void hal_ll_i2c_init( hal_ll_i2c_hw_specifics_map_t *map ) {
    hal_ll_i2c_base_handle_t *hal_ll_hw_reg = hal_ll_i2c_get_base_struct( map->base );
    uint32_t clock_value; // TODO Esma get source clock value

    // Enable IIC peripheral
    if( hal_ll_i2c_module_num( I2C_MODULE_0 ) == map->module_index )
        clear_reg_bit( _MSTPCRB, MSTPCRB_MSTPB9_POS );
    else if( hal_ll_i2c_module_num( I2C_MODULE_1 ) == map->module_index )
        clear_reg_bit( _MSTPCRB, MSTPCRB_MSTPB8_POS );

    hal_ll_i2c_hw_init( map );

    hal_ll_i2c_calculate_speed( map, clock_value );

    // When the required register settings are complete,
    // set the ICCR1.IICRST bit to 0 to release the IIC reset.
    clear_reg_bit( &hal_ll_hw_reg->iccr1, HAL_LL_I2C_ICCR1_IICRST );

    return;
}

// ------------------------------------------------------------------------- END
