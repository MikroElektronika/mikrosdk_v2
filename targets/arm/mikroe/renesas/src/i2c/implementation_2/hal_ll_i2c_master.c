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
 * @file  hal_ll_uart.c
 * @brief UART HAL LOW LEVEL layer implementation.
 */

#include <math.h>
#include "hal_ll_gpio.h"
#include "hal_ll_i2c_master.h"
#include "hal_ll_i2c_pin_map.h"
#include "hal_ll_mstpcr.h"
#include "delays.h"

#include "mcu.h"

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

#define HAL_LL_I2C_AF_CONFIG (GPIO_CFG_PORT_PULL_UP_ENABLE |\
                              GPIO_CFG_DIGITAL_OUTPUT |\
                              GPIO_CFG_NMOS_OPEN_DRAIN_ENABLE |\
                              GPIO_CFG_PERIPHERAL_PIN)

/*!< @brief Default I2C bit-rate if no speed is set */
#define HAL_LL_I2C_MASTER_SPEED_100K                (100000UL)
#define HAL_LL_I2C_MASTER_SPEED_400K                (400000UL)
#define HAL_LL_I2C_MASTER_SPEED_1M                  (1000000UL)
#define HAL_LL_I2C_MASTER_SPEED_3M2                 (3200000UL)

#define HAL_LL_I2C_DEFAULT_PASS_COUNT               (10000)

/*!< @brief Macros defining bit location. */
#define HAL_LL_SCI_SSR_TEND         2
#define HAL_LL_SCI_SCR_TEIE         2
#define HAL_LL_SCI_SEMR_BRME        2
#define HAL_LL_SCI_SEMR_ABCSE       3
#define HAL_LL_SCI_SMR_STOP         3
#define HAL_LL_SCI_SSR_PER          3
#define HAL_LL_SCI_SEMR_ABCS        4
#define HAL_LL_SCI_SCMR_CHR1        4
#define HAL_LL_SCI_SMR_PM           4
#define HAL_LL_SCI_SCR_RE           4
#define HAL_LL_SCI_SSR_FER          4
#define HAL_LL_SCI_SCR_TE           5
#define HAL_LL_SCI_SMR_PE           5
#define HAL_LL_SCI_SSR_ORER         5
#define HAL_LL_SCI_SMR_CHR          6
#define HAL_LL_SCI_SSR_RDRF         6
#define HAL_LL_SCI_SEMR_BGDM        6
#define HAL_LL_SCI_SCR_RIE          6
#define HAL_LL_SCI_SSR_TDRE         7
#define HAL_LL_SCI_SCR_TIE          7

#define HAL_LL_SCI_SCMR_SMIF        0
#define HAL_LL_SCI_SCMR_SINV        2
#define HAL_LL_SCI_SCMR_SDIR        3

#define HAL_LL_SCI_SPTR_RXDMON      0
#define HAL_LL_SCI_SPTR_SPB2DT      1
#define HAL_LL_SCI_SPTR_SPB2IO      2
#define HAL_LL_SCI_SPTR_RINV        4
#define HAL_LL_SCI_SPTR_TINV        5
#define HAL_LL_SCI_SPTR_ASEN        6
#define HAL_LL_SCI_SPTR_ATEN        7

#define HAL_LL_SCI_SIMR1_IICM       0
#define HAL_LL_SCI_SIMR1_IICDL_MASK         0xf8

#define HAL_LL_SCI_SIMR2_IICINTM    0
#define HAL_LL_SCI_SIMR2_IICCSC     1
#define HAL_LL_SCI_SIMR2_IICACKT    5

#define HAL_LL_SCI_SIMR3_IICSTAREQ  0
#define HAL_LL_SCI_SIMR3_IICSTIF    3

#define HAL_LL_SCI_SISR_IICACKR     0

#define HAL_LL_SCI_SIMR3_IICSDAS_MASK       0x30
#define HAL_LL_SCI_SIMR3_IICSCLS_MASK       0xC0
#define HAL_LL_SCI_SIMR3_START_MASK         0x51
#define HAL_LL_SCI_SIMR3_STOP_MASK          0x54

/*!< @brief Baud rate divisor information structure. */
static const uint16_t g_div_coefficient[] = {
    32U, 128U, 512U, 2048U
};

/*!< @brief I2C register structure */
typedef struct {
    uint8_t smr;        // Serial Mode Register.
    uint8_t brr;        // Bit Rate Register.
    uint8_t scr;        // Serial Control Register.
    uint8_t tdr;        // Transmit Data Register.
    uint8_t ssr;        // Serial Status Register.
    uint8_t rdr;        // Receive Data Register.
    uint8_t scmr;       // Smart Card Mode Register.
    uint8_t semr;       // Serial Extended Mode Register.
    uint8_t snfr;       // Noise Filter Setting Register.
    uint8_t simr1;      // I2C Mode Register 1.
    uint8_t simr2;      // I2C Mode Register 2.
    uint8_t simr3;      // I2C Mode Register 3.
    uint8_t sisr;       // I2C Status Register
    uint8_t spmr;       // SPI Mode Register
    uint16_t tdrhl;     // Transmit 9-bit Data Register.
    uint16_t rdrhl;     // Receive 9-bit Data Register.
    uint8_t mddr;       // Modulation Duty Register.
    uint8_t dccr;       // Data Compare Match Control Register.
    uint16_t fcr;       // FIFO Control Register.
    uint16_t fdr;       // FIFO Data Count Register.
    uint16_t lsr;       // Line Status Register.
    uint16_t cdr;       // Compare Match Data Register.
    uint8_t sptr;       // Serial Port Register.

} hal_ll_i2c_base_handle_t;

/*!< @brief I2C hw specific structure */
typedef struct {
    hal_ll_base_addr_t base;
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
    {HAL_LL_UART0_BASE_ADDRESS, hal_ll_i2c_module_num( I2C_MODULE_0 ),
     {HAL_LL_PIN_NC, 0, HAL_LL_PIN_NC, 10000},
     HAL_LL_I2C_MASTER_SPEED_100K , 0, HAL_LL_I2C_DEFAULT_PASS_COUNT},
    #endif
    #ifdef I2C_MODULE_1
    {HAL_LL_UART1_BASE_ADDRESS, hal_ll_i2c_module_num( I2C_MODULE_1 ),
     {HAL_LL_PIN_NC, 0, HAL_LL_PIN_NC, 10000},
     HAL_LL_I2C_MASTER_SPEED_100K , 0, HAL_LL_I2C_DEFAULT_PASS_COUNT},
    #endif
    #ifdef I2C_MODULE_2
    {HAL_LL_UART2_BASE_ADDRESS, hal_ll_i2c_module_num( I2C_MODULE_2 ),
    {HAL_LL_PIN_NC, 0, HAL_LL_PIN_NC, 10000},
    HAL_LL_I2C_MASTER_SPEED_100K , 0, HAL_LL_I2C_DEFAULT_PASS_COUNT},
    #endif
    #ifdef I2C_MODULE_3
    {HAL_LL_UART3_BASE_ADDRESS, hal_ll_i2c_module_num( I2C_MODULE_3 ),
    {HAL_LL_PIN_NC, 0, HAL_LL_PIN_NC, 10000},
    HAL_LL_I2C_MASTER_SPEED_100K , 0, HAL_LL_I2C_DEFAULT_PASS_COUNT},
    #endif
    #ifdef I2C_MODULE_4
    {HAL_LL_UART4_BASE_ADDRESS, hal_ll_i2c_module_num( I2C_MODULE_4 ),
    {HAL_LL_PIN_NC, 0, HAL_LL_PIN_NC, 10000},
    HAL_LL_I2C_MASTER_SPEED_100K , 0, HAL_LL_I2C_DEFAULT_PASS_COUNT},
    #endif
    #ifdef I2C_MODULE_5
    {HAL_LL_UART5_BASE_ADDRESS, hal_ll_i2c_module_num( I2C_MODULE_5 ),
    {HAL_LL_PIN_NC, 0, HAL_LL_PIN_NC, 10000},
    HAL_LL_I2C_MASTER_SPEED_100K , 0, HAL_LL_I2C_DEFAULT_PASS_COUNT},
    #endif
    #ifdef I2C_MODULE_6
    {HAL_LL_UART6_BASE_ADDRESS, hal_ll_i2c_module_num( I2C_MODULE_6 ),
    {HAL_LL_PIN_NC, 0, HAL_LL_PIN_NC, 10000},
    HAL_LL_I2C_MASTER_SPEED_100K , 0, HAL_LL_I2C_DEFAULT_PASS_COUNT},
    #endif
    #ifdef I2C_MODULE_7
    {HAL_LL_UART7_BASE_ADDRESS, hal_ll_i2c_module_num( I2C_MODULE_7 ),
    {HAL_LL_PIN_NC, 0, HAL_LL_PIN_NC, 10000},
    HAL_LL_I2C_MASTER_SPEED_100K , 0, HAL_LL_I2C_DEFAULT_PASS_COUNT},
    #endif
    #ifdef I2C_MODULE_8
    {HAL_LL_UART8_BASE_ADDRESS, hal_ll_i2c_module_num( I2C_MODULE_8 ),
    {HAL_LL_PIN_NC, 0, HAL_LL_PIN_NC, 10000},
    HAL_LL_I2C_MASTER_SPEED_100K , 0, HAL_LL_I2C_DEFAULT_PASS_COUNT},
    #endif
    #ifdef I2C_MODULE_9
    {HAL_LL_UART9_BASE_ADDRESS, hal_ll_i2c_module_num( I2C_MODULE_9 ),
    {HAL_LL_PIN_NC, 0, HAL_LL_PIN_NC, 10000},
    HAL_LL_I2C_MASTER_SPEED_100K , 0, HAL_LL_I2C_DEFAULT_PASS_COUNT},
    #endif

    {HAL_LL_MODULE_ERROR, HAL_LL_MODULE_ERROR,
     {HAL_LL_PIN_NC, 0, HAL_LL_PIN_NC, 0}, 0, 0, 0}
};

/*!< @brief Global handle variables used in functions */
static volatile hal_ll_i2c_master_handle_register_t *low_level_handle;
static volatile hal_ll_i2c_hw_specifics_map_t *hal_ll_i2c_hw_specifics_map_local;

// ---------------------------------------------- PRIVATE FUNCTION DECLARATIONS
/**
  * @brief  Enable or disable the I2C hardware module.
  *
  * Controls the clock and power state of the specified I2C hardware module
  * by enabling or disabling it, depending on the provided state parameter.
  *
  * @param[in]  *map        - Object specific context handler.
  * @param[in]  hal_ll_state - Desired state of the module (true to enable, false to disable).
  * @return None
  */
static void hal_ll_i2c_master_module_enable( hal_ll_i2c_hw_specifics_map_t *map, bool hal_ll_state );

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
  * @brief  Set I2C speed registers based on clock and bit rate.
  *
  * Sets ICMR1, ICBRL, and ICBRH values based on the PCLKB clock
  * and desired I2C speed (100kHz, 400kHz, or 1MHz).
  *
  * @param[in]  *map - I2C hardware context.
  *
  * @note Supports only 24MHz and 32MHz PCLKB.
  */
static void hal_ll_i2c_calculate_speed( hal_ll_i2c_hw_specifics_map_t *map );

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
                                                       size_t len_read_data,
                                                       hal_ll_i2c_master_end_mode_t mode );

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
                                                        size_t len_write_data,
                                                        hal_ll_i2c_master_end_mode_t mode );

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
        hal_ll_i2c_master_module_enable( hal_ll_i2c_hw_specifics_map_local, false );

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

    if( HAL_LL_I2C_MASTER_TIMEOUT_WAIT_IDLE == hal_ll_i2c_master_wait_for_idle( map )) {
        return HAL_LL_I2C_MASTER_TIMEOUT_WAIT_IDLE;
    }

    time_counter = map->timeout;
    while( !check_reg_bit( &hal_ll_hw_reg->ssr, HAL_LL_SCI_SSR_TEND )) {
        if( map->timeout ) {
            if( !time_counter-- )
                return HAL_LL_I2C_MASTER_TIMEOUT_WRITE;
        }
    }

    clear_reg_bit( &hal_ll_hw_reg->scr, HAL_LL_SCI_SCR_RIE );

    write_reg( &hal_ll_hw_reg->simr3, HAL_LL_SCI_SIMR3_START_MASK );

    while( !check_reg_bit( &hal_ll_hw_reg->simr3, HAL_LL_SCI_SIMR3_IICSTIF )) {
        if( map->timeout ) {
            if( !time_counter-- )
                return HAL_LL_I2C_MASTER_TIMEOUT_WRITE;
        }
    }

    clear_reg_bit( &hal_ll_hw_reg->simr3, HAL_LL_SCI_SIMR3_IICSTIF );
    clear_reg_bits( &hal_ll_hw_reg->simr3, HAL_LL_SCI_SIMR3_IICSDAS_MASK | HAL_LL_SCI_SIMR3_IICSCLS_MASK );

    write_reg( &hal_ll_hw_reg->tdr, map->address << 1 );

    // time_counter = map->timeout;
    // while( !check_reg_bit( &hal_ll_hw_reg->ssr, HAL_LL_SCI_SSR_TDRE )) {
    //     if( map->timeout ) {
    //         if( !time_counter-- )
    //             return HAL_LL_I2C_MASTER_TIMEOUT_WRITE;
    //     }
    // }

    time_counter = map->timeout;
    while( !check_reg_bit( &hal_ll_hw_reg->ssr, HAL_LL_SCI_SSR_TEND )) {
        if( map->timeout ) {
            if( !time_counter-- )
                return HAL_LL_I2C_MASTER_TIMEOUT_WRITE;
        }
    }

    if ( !check_reg_bit( &hal_ll_hw_reg->sisr, HAL_LL_SCI_SISR_IICACKR ) ) {
        for( uint8_t i = 0; i < len_write_data; i++ ) {
            write_reg( &hal_ll_hw_reg->tdr, write_data_buf[i] );

            // time_counter = map->timeout;
            // while( !check_reg_bit( &hal_ll_hw_reg->ssr, HAL_LL_SCI_SSR_TDRE )) {
            //     if( map->timeout ) {
            //         if( !time_counter-- )
            //             return HAL_LL_I2C_MASTER_TIMEOUT_WRITE;
            //     }
            // }

            time_counter = map->timeout;
            while( !check_reg_bit( &hal_ll_hw_reg->ssr, HAL_LL_SCI_SSR_TEND )) {
                if( map->timeout ) {
                    if( !time_counter-- )
                        return HAL_LL_I2C_MASTER_TIMEOUT_WRITE;
                }
            }
        }
    }

    write_reg( &hal_ll_hw_reg->simr3, HAL_LL_SCI_SIMR3_STOP_MASK );

    while( !check_reg_bit( &hal_ll_hw_reg->simr3, HAL_LL_SCI_SIMR3_IICSTIF )) {
        if( map->timeout ) {
            if( !time_counter-- )
                return HAL_LL_I2C_MASTER_TIMEOUT_WRITE;
        }
    }

    set_reg_bit( &hal_ll_hw_reg->simr3, HAL_LL_SCI_SIMR3_IICSTIF );
    clear_reg_bits( &hal_ll_hw_reg->simr3, HAL_LL_SCI_SIMR3_IICSDAS_MASK | HAL_LL_SCI_SIMR3_IICSCLS_MASK );

    return HAL_LL_I2C_MASTER_SUCCESS;
}

uint32_t check;

static hal_ll_err_t hal_ll_i2c_master_read_bare_metal( hal_ll_i2c_hw_specifics_map_t *map,
                                                       uint8_t *read_data_buf,
                                                       size_t len_read_data,
                                                       hal_ll_i2c_master_end_mode_t mode ) {
    hal_ll_i2c_base_handle_t *hal_ll_hw_reg = hal_ll_i2c_get_base_struct( map->base );
    uint16_t time_counter = map->timeout;
    uint8_t dummy_byte = 0xFF;
    uint8_t dummy_read = 0;

    // len_read_data++;

    if( HAL_LL_I2C_MASTER_TIMEOUT_WAIT_IDLE == hal_ll_i2c_master_wait_for_idle( map )) {
        return HAL_LL_I2C_MASTER_TIMEOUT_WAIT_IDLE;
    }

    clear_reg_bit( &hal_ll_hw_reg->scr, HAL_LL_SCI_SCR_RIE );

    write_reg( &hal_ll_hw_reg->simr3, HAL_LL_SCI_SIMR3_START_MASK );

    while( !check_reg_bit( &hal_ll_hw_reg->simr3, HAL_LL_SCI_SIMR3_IICSTIF )) {
        if( map->timeout ) {
            if( !time_counter-- )
                return HAL_LL_I2C_MASTER_TIMEOUT_READ;
        }
    }

    clear_reg_bit( &hal_ll_hw_reg->simr3, HAL_LL_SCI_SIMR3_IICSTIF );
    clear_reg_bits( &hal_ll_hw_reg->simr3, HAL_LL_SCI_SIMR3_IICSDAS_MASK | HAL_LL_SCI_SIMR3_IICSCLS_MASK );

    write_reg( &hal_ll_hw_reg->tdr, ( map->address << 1 ) | 1 );

    time_counter = map->timeout;
    while( !check_reg_bit( &hal_ll_hw_reg->ssr, HAL_LL_SCI_SSR_TDRE )) {
        if( map->timeout ) {
            if( !time_counter-- )
                return HAL_LL_I2C_MASTER_TIMEOUT_READ;
        }
    }

    if ( !check_reg_bit( &hal_ll_hw_reg->sisr, HAL_LL_SCI_SISR_IICACKR ) ) {
        clear_reg_bit( &hal_ll_hw_reg->simr2, HAL_LL_SCI_SIMR2_IICACKT );
        set_reg_bit( &hal_ll_hw_reg->scr, HAL_LL_SCI_SCR_RIE );


        for( uint8_t i = 0; i < len_read_data - 1; i++ ) {
            time_counter = map->timeout;
            while( check_reg_bit( &hal_ll_hw_reg->ssr, HAL_LL_SCI_SSR_RDRF )) {
                if( map->timeout ) {
                    if( !time_counter-- )
                        return HAL_LL_I2C_MASTER_TIMEOUT_READ;
                }
            }

            write_reg( &hal_ll_hw_reg->tdr, dummy_byte );
            // clear_reg_bit( &hal_ll_hw_reg->ssr, HAL_LL_SCI_SSR_RDRF );

            check = R_SCI0->FTDRHL;

            // set_reg_bit( &hal_ll_hw_reg->ssr, HAL_LL_SCI_SSR_RDRF );

            // check = R_SCI0->SSR;

            // check = read_reg( &hal_ll_hw_reg->tdr );

            time_counter = map->timeout;
            while( !check_reg_bit( &hal_ll_hw_reg->ssr, HAL_LL_SCI_SSR_TDRE )) {
                if( map->timeout ) {
                    if( !time_counter-- )
                        return HAL_LL_I2C_MASTER_TIMEOUT_READ;
                }
            }
            // check = read_reg( &hal_ll_hw_reg->tdr );

            check = R_SCI0->FTDRHL;

            time_counter = map->timeout;
            while( !check_reg_bit( &hal_ll_hw_reg->ssr, HAL_LL_SCI_SSR_RDRF )) {
                if( map->timeout ) {
                    if( !time_counter-- )
                        return HAL_LL_I2C_MASTER_TIMEOUT_READ;
                }
            }

            read_data_buf[i] = read_reg( &hal_ll_hw_reg->rdr );
        }

        set_reg_bit( &hal_ll_hw_reg->simr2, HAL_LL_SCI_SIMR2_IICACKT );

        time_counter = map->timeout;
            while( check_reg_bit( &hal_ll_hw_reg->ssr, HAL_LL_SCI_SSR_RDRF )) {
                if( map->timeout ) {
                    if( !time_counter-- )
                        return HAL_LL_I2C_MASTER_TIMEOUT_READ;
                }
            }

        write_reg( &hal_ll_hw_reg->tdr, dummy_byte );

        time_counter = map->timeout;
        while( !check_reg_bit( &hal_ll_hw_reg->ssr, HAL_LL_SCI_SSR_RDRF )) {
            if( map->timeout ) {
                if( !time_counter-- )
                    return HAL_LL_I2C_MASTER_TIMEOUT_READ;
            }
        }

        read_data_buf[len_read_data - 1] = read_reg( &hal_ll_hw_reg->rdr );

        uint8_t a = read_data_buf[len_read_data - 1];

        time_counter = map->timeout;
        while( !check_reg_bit( &hal_ll_hw_reg->ssr, HAL_LL_SCI_SSR_TDRE )) {
            if( map->timeout ) {
                if( !time_counter-- )
                    return HAL_LL_I2C_MASTER_TIMEOUT_READ;
            }
        }
    }

    clear_reg_bit( &hal_ll_hw_reg->simr3, HAL_LL_SCI_SIMR3_IICSTIF );
    clear_reg_bits( &hal_ll_hw_reg->simr3, HAL_LL_SCI_SIMR3_IICSDAS_MASK | HAL_LL_SCI_SIMR3_IICSCLS_MASK );


    write_reg( &hal_ll_hw_reg->simr3, HAL_LL_SCI_SIMR3_STOP_MASK );

    while( !check_reg_bit( &hal_ll_hw_reg->simr3, HAL_LL_SCI_SIMR3_IICSTIF )) {
        if( map->timeout ) {
            if( !time_counter-- )
                return HAL_LL_I2C_MASTER_TIMEOUT_READ;
        }
    }

    clear_reg_bit( &hal_ll_hw_reg->simr3, HAL_LL_SCI_SIMR3_IICSTIF );
    clear_reg_bits( &hal_ll_hw_reg->simr3, HAL_LL_SCI_SIMR3_IICSDAS_MASK | HAL_LL_SCI_SIMR3_IICSCLS_MASK );

    // write_reg( &hal_ll_hw_reg->simr3, HAL_LL_SCI_SIMR3_STOP_MASK );

    // while( !check_reg_bit( &hal_ll_hw_reg->simr3, HAL_LL_SCI_SIMR3_IICSTIF )) {
    //     if( map->timeout ) {
    //         if( !time_counter-- )
    //             return HAL_LL_I2C_MASTER_TIMEOUT_READ;
    //     }
    // }

    // clear_reg_bit( &hal_ll_hw_reg->simr3, HAL_LL_SCI_SIMR3_IICSTIF );
    // clear_reg_bits( &hal_ll_hw_reg->simr3, HAL_LL_SCI_SIMR3_IICSDAS_MASK | HAL_LL_SCI_SIMR3_IICSCLS_MASK );

    return HAL_LL_I2C_MASTER_SUCCESS;
}

static void hal_ll_i2c_master_alternate_functions_set_state( hal_ll_i2c_hw_specifics_map_t *map,
                                                             bool hal_ll_state ) {
    module_struct module;

    if( (map->pins.pin_scl.pin_name != HAL_LL_PIN_NC) && (map->pins.pin_sda.pin_name != HAL_LL_PIN_NC) ) {
        module.pins[0] = VALUE( map->pins.pin_scl.pin_name, map->pins.pin_scl.pin_af );
        module.pins[1] = VALUE( map->pins.pin_sda.pin_name, map->pins.pin_sda.pin_af );
        module.pins[2] = GPIO_MODULE_STRUCT_END;

        module.configs[0] = GPIO_CFG_NMOS_OPEN_DRAIN_ENABLE;
        module.configs[1] = GPIO_CFG_NMOS_OPEN_DRAIN_ENABLE;
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
    uint8_t hal_ll_module_count = sizeof( hal_ll_module_state ) /
                                        (sizeof( hal_ll_i2c_master_handle_register_t ));
    static uint8_t hal_ll_module_error = sizeof(hal_ll_module_state) /
                                        (sizeof( hal_ll_i2c_master_handle_register_t));

    while( hal_ll_module_count-- ) {
        if ( hal_ll_i2c_get_base_from_hal_handle ==
                 hal_ll_i2c_hw_specifics_map[ hal_ll_module_count ].base ) {
            return &hal_ll_i2c_hw_specifics_map[ hal_ll_module_count ];
        }
    }

    return &hal_ll_i2c_hw_specifics_map[ hal_ll_module_error ];
}

static hal_ll_pin_name_t hal_ll_i2c_master_check_pins( hal_ll_pin_name_t scl,
                                                       hal_ll_pin_name_t sda,
                                                       hal_ll_i2c_pin_id *index_list,
                                                       hal_ll_i2c_master_handle_register_t *handle_map ) {
    static const uint16_t scl_map_size =
            ( sizeof( hal_ll_i2c_scl_map ) / sizeof( hal_ll_i2c_pin_map_t ) );
    static const uint16_t sda_map_size =
            ( sizeof( hal_ll_i2c_sda_map ) / sizeof( hal_ll_i2c_pin_map_t ) );
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
                    if ( hal_ll_i2c_scl_map[ scl_index ].module_index ==
                                hal_ll_i2c_sda_map[ sda_index ].module_index ) {
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
    uint16_t time_counter = map->timeout;

    // while( check_reg_bit( &hal_ll_hw_reg->iccr2, HAL_LL_I2C_ICCR2_BBSY )) {
    //     if( map->timeout ) {
    //         if( !time_counter-- ) {
    //             return HAL_LL_I2C_MASTER_TIMEOUT_WAIT_IDLE;
    //         }
    //     }
    // }

    bool sda_high = ( check_reg_bit( &hal_ll_hw_reg->sptr, HAL_LL_SCI_SPTR_RXDMON ) == 1);
    bool scl_high = ( check_reg_bit( &hal_ll_hw_reg->sptr, HAL_LL_SCI_SPTR_SPB2DT ) == 1);
    // bool tx_idle  = (SCI0->SSR_b.TDRE == 1) &&
    //                 (SCI0->SSR_b.TEND == 1);
    // bool iic_done = (SCI0->SIMR3_b.IICSTIF == 1);

    // return sda_high && tx_idle && iic_done;

    return ( sda_high && scl_high ) ? HAL_LL_I2C_MASTER_SUCCESS : 1;
}

static void hal_ll_i2c_calculate_speed( hal_ll_i2c_hw_specifics_map_t *map ) {
    hal_ll_i2c_base_handle_t *hal_ll_hw_reg = hal_ll_i2c_get_base_struct( map->base );

    uint8_t best_n = -1;
    uint8_t best_N = 0;
    double best_error = 100.0;

    system_clocks_t system_clocks;
    SYSTEM_GetClocksFrequency( &system_clocks );

    uint32_t i2c_source_clock = system_clocks.pclkb;

    for ( uint8_t i = 0; i < 4; i++ ) {
        double raw_N = ( i2c_source_clock / ( g_div_coefficient[i] * map->speed ) ) - 1;

        uint8_t candidates_N [5];
        uint8_t candidates_count;

        uint8_t raw_N_floor = (uint8_t) floor( raw_N );
        uint8_t raw_N_ceil  = (uint8_t) ceil( raw_N );
        uint8_t raw_N_round = (uint8_t) floor( raw_N + 0.5 );

        candidates_N[candidates_count++] = raw_N_floor;

        if ( raw_N_ceil != raw_N_floor )
            candidates_N[candidates_count++] = raw_N_ceil;

        if ( raw_N_round != raw_N_floor && raw_N_round != raw_N_ceil )
            candidates_N[candidates_count++] = raw_N_round;

        candidates_N[candidates_count++] = raw_N_floor > 1 ? raw_N_floor - 1 : 1;
        candidates_N[candidates_count++] = raw_N_floor + 1;

        for ( uint8_t j = 0; j < candidates_count; j++ ) {
            uint8_t candidate_N = candidates_N[j];

            if ( candidate_N < 0 || candidate_N > 255 )
                continue;

            double real_bps = i2c_source_clock / ( g_div_coefficient[i] * ( (double)candidate_N + 1.0 ) );
            double error = ( real_bps - map->speed ) / map->speed * 100.0;

            if ( fabs( error ) < fabs( best_error ) ) {
                best_n = i;
                best_N = candidate_N;
                best_error = error;
            }
        }
    }

    clear_reg_bits( &hal_ll_hw_reg->smr, 0x3 );
    write_reg( &hal_ll_hw_reg->brr, best_N );
    clear_reg_bit( &hal_ll_hw_reg->semr, 2 );
}

static void hal_ll_i2c_hw_init( hal_ll_i2c_hw_specifics_map_t *map ) {
    hal_ll_i2c_base_handle_t *hal_ll_hw_reg = hal_ll_i2c_get_base_struct( map->base );

    // I2C initialization
    // Set the SIMR3.IICSDAS and SIMR3.IICSCLS bits set to 11b to drive the SCLn and SDAn pins to high-impedance state.
    set_reg_bits( &hal_ll_hw_reg->simr3, HAL_LL_SCI_SIMR3_IICSDAS_MASK );
    set_reg_bits( &hal_ll_hw_reg->simr3, HAL_LL_SCI_SIMR3_IICSCLS_MASK );

    clear_reg( &hal_ll_hw_reg->smr );

    // // Set the format for transmission
    clear_reg_bit( &hal_ll_hw_reg->scmr, HAL_LL_SCI_SCMR_SMIF );
    clear_reg_bit( &hal_ll_hw_reg->scmr, HAL_LL_SCI_SCMR_SINV );
    set_reg_bit( &hal_ll_hw_reg->scmr, HAL_LL_SCI_SCMR_SDIR );

    // // Set the initial value for SPTR
    clear_reg_bit( &hal_ll_hw_reg->sptr, HAL_LL_SCI_SPTR_RINV );
    clear_reg_bit( &hal_ll_hw_reg->sptr, HAL_LL_SCI_SPTR_TINV );
    clear_reg_bit( &hal_ll_hw_reg->sptr, HAL_LL_SCI_SPTR_SPB2IO );
    clear_reg_bit( &hal_ll_hw_reg->sptr, HAL_LL_SCI_SPTR_ASEN );
    clear_reg_bit( &hal_ll_hw_reg->sptr, HAL_LL_SCI_SPTR_ATEN );

    hal_ll_i2c_calculate_speed( map );

    clear_reg_bit( &hal_ll_hw_reg->semr, 5 );
    set_reg_bit( &hal_ll_hw_reg->snfr, 0 );


    set_reg_bit( &hal_ll_hw_reg->simr1, HAL_LL_SCI_SIMR1_IICM );
    set_reg_bit( &hal_ll_hw_reg->simr1, 3 );
    // clear_reg_bits( &hal_ll_hw_reg->simr1, HAL_LL_SCI_SIMR1_IICDL_MASK );

    set_reg_bit( &hal_ll_hw_reg->simr2, HAL_LL_SCI_SIMR2_IICINTM );
    set_reg_bit( &hal_ll_hw_reg->simr2, HAL_LL_SCI_SIMR2_IICCSC );
    set_reg_bit( &hal_ll_hw_reg->simr2, HAL_LL_SCI_SIMR2_IICACKT );

    clear_reg( &hal_ll_hw_reg->spmr );

    set_reg_bit( &hal_ll_hw_reg->scr, HAL_LL_SCI_SCR_TE );
    // set_reg_bit( &hal_ll_hw_reg->scr, HAL_LL_SCI_SCR_RE );

    set_reg_bit( &hal_ll_hw_reg->scr, HAL_LL_SCI_SCR_TIE );
    clear_reg_bit( &hal_ll_hw_reg->scr, HAL_LL_SCI_SCR_RIE );
    set_reg_bit( &hal_ll_hw_reg->scr, HAL_LL_SCI_SCR_TEIE );
}

static void hal_ll_i2c_master_module_enable( hal_ll_i2c_hw_specifics_map_t *map, bool hal_ll_state ) {
        switch ( map->module_index ) {
        #ifdef I2C_MODULE_0
        case ( hal_ll_i2c_module_num( I2C_MODULE_0 )):
            ( hal_ll_state == false ) ? ( set_reg_bit( _MSTPCRB, MSTPCRB_MSTPB31_POS )) : ( clear_reg_bit( _MSTPCRB, MSTPCRB_MSTPB31_POS ));
            break;
        #endif
        #ifdef I2C_MODULE_1
        case ( hal_ll_i2c_module_num( I2C_MODULE_1 )):
            ( hal_ll_state == false ) ? ( set_reg_bit( _MSTPCRB, MSTPCRB_MSTPB30_POS )) : ( clear_reg_bit( _MSTPCRB, MSTPCRB_MSTPB30_POS ));
            break;
        #endif
        #ifdef I2C_MODULE_2
        case ( hal_ll_i2c_module_num( I2C_MODULE_2 )):
            ( hal_ll_state == false ) ? ( set_reg_bit( _MSTPCRB, MSTPCRB_MSTPB29_POS )) : ( clear_reg_bit( _MSTPCRB, MSTPCRB_MSTPB29_POS ));
            break;
        #endif
        #ifdef I2C_MODULE_3
        case ( hal_ll_i2c_module_num( I2C_MODULE_3 )):
            ( hal_ll_state == false ) ? ( set_reg_bit( _MSTPCRB, MSTPCRB_MSTPB28_POS )) : ( clear_reg_bit( _MSTPCRB, MSTPCRB_MSTPB28_POS ));
            break;
        #endif
        #ifdef I2C_MODULE_4
        case ( hal_ll_i2c_module_num( I2C_MODULE_4 )):
            ( hal_ll_state == false ) ? ( set_reg_bit( _MSTPCRB, MSTPCRB_MSTPB27_POS )) : ( clear_reg_bit( _MSTPCRB, MSTPCRB_MSTPB27_POS ));
            break;
        #endif
        #ifdef I2C_MODULE_5
        case ( hal_ll_i2c_module_num( I2C_MODULE_5 )):
            ( hal_ll_state == false ) ? ( set_reg_bit( _MSTPCRB, MSTPCRB_MSTPB26_POS )) : ( clear_reg_bit( _MSTPCRB, MSTPCRB_MSTPB26_POS ));
            break;
        #endif
        #ifdef I2C_MODULE_6
        case ( hal_ll_i2c_module_num( I2C_MODULE_6 )):
            ( hal_ll_state == false ) ? ( set_reg_bit( _MSTPCRB, MSTPCRB_MSTPB25_POS )) : ( clear_reg_bit( _MSTPCRB, MSTPCRB_MSTPB25_POS ));
            break;
        #endif
        #ifdef I2C_MODULE_7
        case ( hal_ll_i2c_module_num( I2C_MODULE_7 )):
            ( hal_ll_state == false ) ? ( set_reg_bit( _MSTPCRB, MSTPCRB_MSTPB24_POS )) : ( clear_reg_bit( _MSTPCRB, MSTPCRB_MSTPB24_POS ));
            break;
        #endif
        #ifdef I2C_MODULE_8
        case ( hal_ll_i2c_module_num( I2C_MODULE_8 )):
            ( hal_ll_state == false ) ? ( set_reg_bit( _MSTPCRB, MSTPCRB_MSTPB23_POS )) : ( clear_reg_bit( _MSTPCRB, MSTPCRB_MSTPB23_POS ));
            break;
        #endif
        #ifdef I2C_MODULE_9
        case ( hal_ll_i2c_module_num( I2C_MODULE_9 )):
            ( hal_ll_state == false ) ? ( set_reg_bit( _MSTPCRB, MSTPCRB_MSTPB22_POS )) : ( clear_reg_bit( _MSTPCRB, MSTPCRB_MSTPB22_POS ));
            break;
        #endif

        default:
            break;
    }
}

static void hal_ll_i2c_init( hal_ll_i2c_hw_specifics_map_t *map ) {
    hal_ll_i2c_base_handle_t *hal_ll_hw_reg = hal_ll_i2c_get_base_struct( map->base );

    // Enable IIC peripheral
    hal_ll_i2c_master_module_enable( map, true );

    clear_reg_bit( &hal_ll_hw_reg->scr, HAL_LL_SCI_SCR_RE );
    clear_reg_bit( &hal_ll_hw_reg->scr, HAL_LL_SCI_SCR_TE );
    clear_reg_bit( &hal_ll_hw_reg->scr, HAL_LL_SCI_SCR_TIE );
    clear_reg_bit( &hal_ll_hw_reg->scr, HAL_LL_SCI_SCR_RIE );
    clear_reg_bit( &hal_ll_hw_reg->scr, HAL_LL_SCI_SCR_TEIE );
    R_SCI0->SMR_b.CKS = 0;

    hal_ll_i2c_master_alternate_functions_set_state( map, true );

    hal_ll_i2c_hw_init( map );

}

// ------------------------------------------------------------------------- END
