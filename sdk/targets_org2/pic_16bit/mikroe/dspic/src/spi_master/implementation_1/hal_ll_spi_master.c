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
 * @file  hal_ll_spi_master.c
 * @brief SPI master HAL LOW LEVEL layer implementation.
 */

#include "hal_ll_spi_master.h"
#include "hal_ll_gpio_port.h"
#include "hal_ll_pps.h"
#include "hal_ll_spi_master_pin_map.h"
#include "hal_ll_slrcon_map.h"

/*!< @brief Local handle list */
static volatile hal_ll_spi_master_handle_register_t hal_ll_module_state[SPI_MODULE_COUNT] = { ( handle_t *)NULL, ( handle_t *)NULL, false } ;

// ------------------------------------------------------------- PRIVATE MACROS
/*!< @brief Helper macro for getting hal_ll_module_state address */
#define hal_ll_spi_master_get_module_state_address (hal_ll_spi_master_handle_register_t *)((hal_ll_spi_master_handle_register_t *)*handle)
//#define hal_ll_spi_master_get_module_state_address              ((hal_ll_spi_master_handle_register_t *)*handle)
/*!< @brief Helper macro for getting module specific control register structure base address // first register address */
#define hal_ll_spi_master_get_handle                            (hal_ll_spi_master_handle_register_t *)hal_ll_spi_master_get_module_state_address->hal_ll_spi_master_handle
/*!< @brief Helper macro for getting module specific control register structure */
#define hal_ll_spi_master_get_base_struct(_handle)              ((const hal_ll_spi_master_base_handle_t *)_handle)
/*!< @brief Helper macro for getting module specific base address directly from HAL layer handle */
#define hal_ll_spi_master_get_base_from_hal_handle              ((hal_ll_spi_master_hw_specifics_map_t *)((hal_ll_spi_master_handle_register_t *)\
                                                                (((hal_ll_spi_master_handle_register_t *)(handle))->hal_ll_spi_master_handle))->hal_ll_spi_master_handle)->base
/*!< @brief Helper macro for getting appropriate baud rate generator register value */
#define hal_ll_spi_get_brg_value(_baud_value)                   ((_fcy/(2*_baud_value))-1)

/*!< @brief Default SPI Master bit-rate if no speed is set */
#ifndef HAL_LL_SPI1BRGL_REG_ADDRESS
#define HAL_LL_SPI_MASTER_SPEED_MAX         _fcy
#else
#define HAL_LL_SPI_MASTER_SPEED_MAX         _fcy/4
#endif
#define HAL_LL_SPI_MASTER_SPEED_MIN         _fcy/16374
#define HAL_LL_SPI_MASTER_SPEED_100K        (100000)

/*!< @brief Macros defining MCU clock and SPI Master baud rate properties */
#define _fosc (Get_Fosc_kHz()*1000)
#ifdef dsPIC30F
#define _fcy (_fosc/4)
#else
#define _fcy (_fosc/2)
#endif
#define HAL_LL_SPI_MASTER_SPEED_RESOLUTION_MASK_MAX     (31)
#define HAL_LL_SPI_MASTER_SPEED_COUNT_FOR_SORTING_ARRAY (20)
#define HAL_LL_SPI_MASTER_SPEED_COUNT_REAL_ARRAY        (14)
#define HAL_LL_QUARTER_VALUE                            (5)
#define HAL_LL_MAX_SPEED_MEMBER                         (0)

/*!< @brief Macros defining register addresses and masks */
#define HAL_LL_RECEIVE_BUFFER_FULL_BIT      0x0000
#define HAL_LL_TRANSMIT_BUFFER_FULL_BIT     0x0001
#define HAL_LL_MASTER_MODE_ENABLE_BIT       0x0005
#define HAL_LL_RECEIVE_OVERFLOW_FLAG_BIT    0x0006
#define HAL_LL_CLOCK_POLARITY_SETUP_BIT     0x0006
#define HAL_LL_CLOCK_EDGE_SETUP_BIT         0x0008
#define HAL_LL_SPI_ENABLE_BIT               0x000F

#define HAL_LL_PRESCALER_BIT_MASK_PRIM_1    0x0003
#define HAL_LL_PRESCALER_BIT_MASK_PRIM_4    0x0002
#define HAL_LL_PRESCALER_BIT_MASK_PRIM_16   0x0001

#define HAL_LL_PRESCALER_BIT_MASK_SEC_1     0x001C
#define HAL_LL_PRESCALER_BIT_MASK_SEC_2     0x0018
#define HAL_LL_PRESCALER_BIT_MASK_SEC_3     0x0014
#define HAL_LL_PRESCALER_BIT_MASK_SEC_4     0x0010
#define HAL_LL_PRESCALER_BIT_MASK_SEC_5     0x000C
#define HAL_LL_PRESCALER_BIT_MASK_SEC_6     0x0008
#define HAL_LL_PRESCALER_BIT_MASK_SEC_7     0x0004


// -------------------------------------------------------------- PRIVATE TYPES
/*!< @brief SPI register structure. */
typedef struct {
    hal_ll_base_addr_t stat;
    hal_ll_base_addr_t con;
    hal_ll_base_addr_t buf;
    #ifdef HAL_LL_SPI1BRGL_REG_ADDRESS
    hal_ll_base_addr_t brg;
    #endif
} hal_ll_spi_master_base_handle_t;

/*!< @brief Prescale handle structure. */
typedef struct {
    uint32_t speed;
    uint8_t mask;
} hal_ll_prescale_handle_t;

/*!< @brief SPI Master hardware specific structure. */
typedef struct {
    const hal_ll_spi_master_base_handle_t *base;
    uint8_t module_index;
    hal_ll_spi_master_pins_t pins;
    uint8_t  dummy_data;
    uint32_t speed;
    uint32_t hw_actual_speed;
    hal_ll_spi_master_mode_t mode;
    uint8_t hal_ll_pps_module_index;
} hal_ll_spi_master_hw_specifics_map_t;

/*!< @brief SPI Master hw specific error values. */
typedef enum {
    HAL_LL_SPI_MASTER_SUCCESS = 0,
    HAL_LL_SPI_MASTER_WRONG_PINS,
    HAL_LL_SPI_MASTER_MODULE_ERROR,

    HAL_LL_SPI_MASTER_ERROR = ( -1 )
} hal_ll_spi_master_err_t;

// ------------------------------------------------------------------ CONSTANTS
// SPI Master module registers array.


static const hal_ll_spi_master_base_handle_t hal_ll_spi_master_registers[] = {
    #ifdef SPI_MODULE_1
    #ifdef HAL_LL_SPI1BRGL_REG_ADDRESS
    { HAL_LL_SPI1STATL_REG_ADDRESS, HAL_LL_SPI1_CONTROL_REG_ADDRESS, HAL_LL_SPI1BUFL_REG_ADDRESS, HAL_LL_SPI1BRGL_REG_ADDRESS },
    #else
    { HAL_LL_SPI1STAT_REG_ADDRESS, HAL_LL_SPI1_CONTROL_REG_ADDRESS, HAL_LL_SPI1BUF_REG_ADDRESS },
    #endif
    #endif
    #ifdef SPI_MODULE_2
    #ifdef HAL_LL_SPI1BRGL_REG_ADDRESS
    { HAL_LL_SPI2STATL_REG_ADDRESS, HAL_LL_SPI2_CONTROL_REG_ADDRESS, HAL_LL_SPI2BUFL_REG_ADDRESS, HAL_LL_SPI2BRGL_REG_ADDRESS },
    #else
    { HAL_LL_SPI2STAT_REG_ADDRESS, HAL_LL_SPI2_CONTROL_REG_ADDRESS, HAL_LL_SPI2BUF_REG_ADDRESS },
    #endif
    #endif
    #ifdef SPI_MODULE_3
    #ifdef HAL_LL_SPI1BRGL_REG_ADDRESS
    { HAL_LL_SPI3STATL_REG_ADDRESS, HAL_LL_SPI3_CONTROL_REG_ADDRESS, HAL_LL_SPI3BUFL_REG_ADDRESS, HAL_LL_SPI3BRGL_REG_ADDRESS },
    #else
    { HAL_LL_SPI3STAT_REG_ADDRESS, HAL_LL_SPI3_CONTROL_REG_ADDRESS, HAL_LL_SPI3BUF_REG_ADDRESS },
    #endif
    #endif
    #ifdef SPI_MODULE_4
    #ifdef HAL_LL_SPI1BRGL_REG_ADDRESS
    { HAL_LL_SPI4STATL_REG_ADDRESS, HAL_LL_SPI4_CONTROL_REG_ADDRESS, HAL_LL_SPI4BUFL_REG_ADDRESS, HAL_LL_SPI4BRGL_REG_ADDRESS },
    #else
    { HAL_LL_SPI4STAT_REG_ADDRESS, HAL_LL_SPI4_CONTROL_REG_ADDRESS, HAL_LL_SPI4BUF_REG_ADDRESS },
    #endif
    #endif

    { HAL_LL_MODULE_ERROR, HAL_LL_MODULE_ERROR, HAL_LL_MODULE_ERROR }
};

// ------------------------------------------------------------------ VARIABLES
/*!< @brief SPI Master hardware specific info */
static hal_ll_spi_master_hw_specifics_map_t hal_ll_spi_master_hw_specifics_map[] = {
    #ifdef SPI_MODULE_1
    { &hal_ll_spi_master_registers[ SPI_MODULE_1 - 1 ], SPI_MODULE_1, {HAL_LL_PIN_NC, HAL_LL_PIN_NC, HAL_LL_PIN_NC}, 0, HAL_LL_SPI_MASTER_SPEED_100K, 0, HAL_LL_SPI_MASTER_MODE_DEFAULT, SPI_MODULE_1 },
    #endif
    #ifdef SPI_MODULE_2
    { &hal_ll_spi_master_registers[ SPI_MODULE_2 - 1 ], SPI_MODULE_2, {HAL_LL_PIN_NC, HAL_LL_PIN_NC, HAL_LL_PIN_NC}, 0, HAL_LL_SPI_MASTER_SPEED_100K, 0, HAL_LL_SPI_MASTER_MODE_DEFAULT, SPI_MODULE_2 },
    #endif
    #ifdef SPI_MODULE_3
    { &hal_ll_spi_master_registers[ SPI_MODULE_3 - 1 ], SPI_MODULE_3, {HAL_LL_PIN_NC, HAL_LL_PIN_NC, HAL_LL_PIN_NC}, 0, HAL_LL_SPI_MASTER_SPEED_100K, 0, HAL_LL_SPI_MASTER_MODE_DEFAULT, SPI_MODULE_3 },
    #endif
    #ifdef SPI_MODULE_4
    { &hal_ll_spi_master_registers[ SPI_MODULE_4 - 1 ], SPI_MODULE_4, {HAL_LL_PIN_NC, HAL_LL_PIN_NC, HAL_LL_PIN_NC}, 0, HAL_LL_SPI_MASTER_SPEED_100K, 0, HAL_LL_SPI_MASTER_MODE_DEFAULT, SPI_MODULE_4 },
    #endif

    { &hal_ll_spi_master_registers[SPI_MODULE_COUNT], HAL_LL_MODULE_ERROR, {HAL_LL_PIN_NC, HAL_LL_PIN_NC, HAL_LL_PIN_NC}, NULL, NULL, NULL, NULL, 0 }
};

/*!< @brief Global handle variables used in functions */
static volatile hal_ll_spi_master_handle_register_t *low_level_handle;
static volatile hal_ll_spi_master_hw_specifics_map_t *hal_ll_spi_master_hw_specifics_map_local;
static hal_ll_prescale_handle_t hal_ll_spi_master_speed_array[HAL_LL_SPI_MASTER_SPEED_COUNT_REAL_ARRAY];
static uint8_t hal_ll_spi_master_speeds_number;

// ---------------------------------------------- PRIVATE FUNCTION DECLARATIONS

/**
  * @brief  Check if pins are adequate.
  *
  * Checks SCK, MISO and MOSI pins the user has passed with pre-defined
  * pins in SCK, MISO and MOSI maps. Take into consideration that module
  * index numbers have to be the same for both pins.
  *
  * @param[in]  sck - SCK pre-defined pin name.
  * @param[in]  miso - MISO pre-defined pin name.
  * @param[in]  mosi - MOSI pre-defined pin name.
  * @param[in]  *index_list - Index list.
  * @param[in]  *handle_map - Handle register map.
  * @return hal_ll_pin_name_t Module index based on pins.
  *
  * Returns pre-defined module index from pin maps, if pins
  * are adequate.
  */
static hal_ll_pin_name_t hal_ll_spi_master_check_pins( hal_ll_pin_name_t sck, hal_ll_pin_name_t miso, hal_ll_pin_name_t mosi, hal_ll_spi_master_pins_t *index_list, hal_ll_spi_master_handle_register_t *handle_map );

/**
  * @brief  Get local hardware specific map.
  *
  * Checks handle value and returns address of adequate
  * hal_ll_spi_master_hw_specifics_map array index.
  *
  * @param[in]  handle - Object specific context handler.
  *
  * @return hal_ll_spi_master_hw_specifics_map_t Map address.
  *
  * Returns pre-defined map index address based on handle value,
  * if handle is adequate.
  */
static hal_ll_spi_master_hw_specifics_map_t *hal_ll_get_specifics( handle_t handle );

/**
  * @brief  Full SPI Master module initialization procedure.
  *
  * Initializes SPI Master module on hardware level, based on beforehand
  * set configuration and module handler. Sets adequate pin alternate functions.
  * Initializes module clock.
  *
  * @param[in]  *map - Object specific context handler.
  *
  * @return  None.
  */
static void hal_ll_spi_master_init( hal_ll_spi_master_hw_specifics_map_t *map );

/**
 * @brief  Sets ODCONx state.
 *
 * Sets adequate ODCONx register state.
 * SPI pins open drain setting.
 *
 * @param[in]  map - Object specific context handler.
 *
 * @return  None.
 */
static void hal_ll_spi_hw_odcon_set( map );

/**
 * @brief  Maps new-found module specific values.
 *
 * Maps pin names and alternate function values for
 * SPI SCK, MISO and MOSI pins.
 *
 * @param[in]  module_index SPI HW module index -- 0,1,2...
 * @param[in]  *index_list  Array with SCK, MISO and MOSI map index values
 *
 * @return  None
 */
static void hal_ll_spi_master_map_pins( uint8_t module_index, hal_ll_spi_master_pins_t *index_list );

/**
  * @brief  Perform a read on the SPI Master bus.
  *
  * Initializes SPI Master module on hardware level, if not initialized beforehand
  * and continues to perform a read operation on the bus.
  *
  * @param[in]  map - Object specific context handler.
  * @param[in]  *read_data_buffer - Pointer to data buffer.
  * @param[in]  read_data_length - Number of data to be read.
  * @param[in]  dummy_data - Data required for read procedure.
  *
  * @return  None.
  */
static void hal_ll_spi_master_read_bare_metal( hal_ll_spi_master_hw_specifics_map_t *map, uint8_t *read_data_buffer, size_t read_data_length, uint8_t dummy_data );

/**
  * @brief  Perform a write on the SPI Master bus.
  *
  * Initializes SPI Master module on hardware level, if not initialized beforehand
  * and continues to perform a write operation on the bus.
  *
  * @param[in]  map - Object specific context handler.
  * @param[in]  *write_data_buffer - Pointer to data buffer.
  * @param[in]  write_data_length - Number of data to be written.
  *
  * @return  None.
  */
static void hal_ll_spi_master_write_bare_metal( hal_ll_spi_master_hw_specifics_map_t *map, uint8_t *write_data_buffer, size_t write_data_length );

/**
  * @brief  Perform a transfer on the SPI Master bus.
  *
  * Initializes SPI Master module on hardware level, if not initialized beforehand
  * and continues to perform a write operation on the bus.
  *
  * @param[in]  map - Object specific context handler.
  * @param[in]  data_buffer - User-specific data, or dummy data.
  *
  * @return uint8_t Read data.
  *
  * Returns data from the buff register.
  */
static uint8_t hal_ll_spi_master_transfer_bare_metal( hal_ll_spi_master_hw_specifics_map_t *map, uint8_t data_buffer );

/**
  * @brief  Get an available speed for SPI.
  *
  * Finds the closet speed to the user's that spi module can set up.
  *
  * @param[in] user_speed - the speed that user wants to set up.
  *
  * @return uint8_t Mask for the prescalers bits.
  *
  * Returns data from the buff register.
  */
static uint8_t hal_ll_get_available_speed_mask( uint32_t user_speed );

/**
 * @brief  Set GPIO state.
 *
 * Sets adequate TRISx register
 * values for adequate functionality.
 *
 * @param map - Object specific context handler.
 * @param hal_ll_state - init or deinit
 *
 * @return  none.
 *
 * @note PIC specific.
 */
static void hal_ll_spi_master_configure_pins( hal_ll_spi_master_hw_specifics_map_t *map, bool hal_ll_state );

/**
 * @brief  Get all possible speed values for MCU.
 *
 * Counts all speed values according to the clock setup.
 *
 * @return  none.
 */
static void hal_ll_spi_master_fill_speed_array();

/**
 * @brief Set PPS state.
 *
 * Sets adequate RPORx or RPIRx register
 * values for adequate functionality.
 * Also, sets TRISx register bit appropriately.
 *
 * @param map - Object specific context handler.
 * @param hal_ll_state - init or deinit
 *
 * @return  hal_ll_pps_err_t PPS specific value.
 * HAL_LL_PPS_SUCCESS  -- OK
 * HAL_LL_PPS_DIRECTION_ERROR -- Direction not set
 * HAL_LL_PPS_PIN_ERROR -- Wrong pin
 * HAL_LL_PPS_MODULE_ERROR -- General error
 *
 * @note PIC specific.
 */
static hal_ll_pps_err_t _hal_ll_pps_set_state( hal_ll_spi_master_hw_specifics_map_t *map, bool hal_ll_state );

/**
 * @brief Finds appropriate prescaler mask for SPI speed.
 *
 * Depending on the users requested speed searches
 * for the closest available SPI speed
 * and returns the corresponding prescaler mask.
 *
 * @param map - Object specific context handler.
 *
 * @return uint8_t prescaler mask for SPI control register.
 */
static uint8_t hal_ll_spi_master_set_speed_prescaler( hal_ll_spi_master_hw_specifics_map_t *map );

/**
 * @brief Finds appropriate value for baud rate generator.
 *
 * Depending on the users requested speed calculates
 * the value that should be written to the baud rate register.
 *
 * @param map - Object specific context handler.
 *
 * @return uint16_t value for SPI baud rate register.
 */
static uint16_t hal_ll_spi_master_set_baud_rate( hal_ll_spi_master_hw_specifics_map_t *map );

// ------------------------------------------------ PUBLIC FUNCTION DEFINITIONS
hal_ll_err_t hal_ll_spi_master_register_handle( hal_ll_pin_name_t sck, hal_ll_pin_name_t miso, hal_ll_pin_name_t mosi, hal_ll_spi_master_handle_register_t *handle_map, uint8_t *hal_module_id ) {
    hal_ll_spi_master_pins_t index_list[SPI_MODULE_COUNT] = { HAL_LL_PIN_NC, HAL_LL_PIN_NC, HAL_LL_PIN_NC };
    uint8_t pin_check_result;

    // Check user-defined pins.
    if ( ( pin_check_result = hal_ll_spi_master_check_pins( sck, miso, mosi, &index_list, handle_map ) ) == HAL_LL_PIN_NC ) {
        return HAL_LL_SPI_MASTER_WRONG_PINS;
    }

    // If user has come with the same SPI hardware module, and with the same pair of the pins, the pin mapping procedure
    // will not take a place; otherwise, clear af-s, map new pins, set af-s, and set init state to false.
    if ( ( hal_ll_spi_master_hw_specifics_map[pin_check_result].pins.sck != sck ) ||
        ( hal_ll_spi_master_hw_specifics_map[pin_check_result].pins.miso != miso ) ||
        ( hal_ll_spi_master_hw_specifics_map[pin_check_result].pins.mosi != mosi ) ) {

        #if HAL_LL_SPI_PPS_ENABLED == true
        // Clear previous module pps
        _hal_ll_pps_set_state( &hal_ll_spi_master_hw_specifics_map[ pin_check_result ], false );
        #endif

        // Map new pps.
        hal_ll_spi_master_map_pins( pin_check_result, &index_list );

        #if HAL_LL_SPI_PPS_ENABLED == true
        // Set mapped pps
        _hal_ll_pps_set_state( &hal_ll_spi_master_hw_specifics_map[ pin_check_result ], true );
        #endif

        handle_map[pin_check_result]->init_ll_state = false;
    }

    // Return id of the SPI module that is going to be used.
    *hal_module_id = pin_check_result;

    // Insert current module into hal_ll_module_state map.
    hal_ll_module_state[pin_check_result].hal_ll_spi_master_handle = ( handle_t *)&hal_ll_spi_master_hw_specifics_map[pin_check_result].base;

    // Return the same info about module one level up ( into the HAL level ).
    handle_map[pin_check_result]->hal_ll_spi_master_handle = ( handle_t *)&hal_ll_module_state[pin_check_result].hal_ll_spi_master_handle;

    #ifndef HAL_LL_SPI1BRGL_REG_ADDRESS
    // Get all possible speed values for spi module.
    hal_ll_spi_master_fill_speed_array();
    #endif

    return HAL_LL_SPI_MASTER_SUCCESS;
}

hal_ll_err_t hal_ll_module_configure_spi( handle_t *handle ) {

    hal_ll_spi_master_pins_t index_list[SPI_MODULE_COUNT] = { HAL_LL_PIN_NC, HAL_LL_PIN_NC, HAL_LL_PIN_NC };
    hal_ll_spi_master_hw_specifics_map_local = hal_ll_get_specifics( hal_ll_spi_master_get_module_state_address );
    uint8_t pin_check_result;

    pin_check_result =  hal_ll_spi_master_check_pins(hal_ll_spi_master_hw_specifics_map_local->pins.sck,
                                                     hal_ll_spi_master_hw_specifics_map_local->pins.miso,
                                                     hal_ll_spi_master_hw_specifics_map_local->pins.mosi,
                                                     &index_list, ( void *)0 );

    hal_ll_spi_master_init( hal_ll_spi_master_hw_specifics_map_local );

    hal_ll_module_state[pin_check_result].hal_ll_spi_master_handle = (handle_t *)&hal_ll_spi_master_hw_specifics_map[pin_check_result].base;
    hal_ll_module_state[pin_check_result].init_ll_state = true;

    return HAL_LL_SPI_MASTER_SUCCESS;
}

void hal_ll_spi_master_set_default_write_data( handle_t *handle, uint8_t dummy_data ) {

    hal_ll_spi_master_hw_specifics_map_local = hal_ll_get_specifics( hal_ll_spi_master_get_module_state_address );

    hal_ll_spi_master_hw_specifics_map_local->dummy_data = dummy_data;

}

hal_ll_err_t hal_ll_spi_master_write( handle_t *handle, uint8_t *write_data_buffer, size_t length_data ) {

    hal_ll_spi_master_hw_specifics_map_local = hal_ll_get_specifics( hal_ll_spi_master_get_module_state_address );

    hal_ll_spi_master_write_bare_metal( hal_ll_spi_master_hw_specifics_map_local, write_data_buffer, length_data );

    return HAL_LL_SPI_MASTER_SUCCESS;
}

hal_ll_err_t hal_ll_spi_master_read( handle_t *handle, uint8_t *read_data_buffer, size_t length_data ) {

    hal_ll_spi_master_hw_specifics_map_local = hal_ll_get_specifics( hal_ll_spi_master_get_module_state_address );

    hal_ll_spi_master_read_bare_metal( hal_ll_spi_master_hw_specifics_map_local, read_data_buffer, length_data, hal_ll_spi_master_hw_specifics_map_local->dummy_data );

    return HAL_LL_SPI_MASTER_SUCCESS;
}

hal_ll_err_t hal_ll_spi_master_write_then_read( handle_t *handle, uint8_t *write_data_buffer, size_t length_write_data, uint8_t *read_data_buffer, size_t length_read_data ) {

    hal_ll_spi_master_hw_specifics_map_local = hal_ll_get_specifics( hal_ll_spi_master_get_module_state_address );

    hal_ll_spi_master_write_bare_metal( hal_ll_spi_master_hw_specifics_map_local, write_data_buffer, length_write_data );

    hal_ll_spi_master_read_bare_metal( hal_ll_spi_master_hw_specifics_map_local, read_data_buffer, length_read_data, hal_ll_spi_master_hw_specifics_map_local->dummy_data );

    return HAL_LL_SPI_MASTER_SUCCESS;
}

uint32_t hal_ll_spi_master_set_speed( handle_t *handle, uint32_t speed ) {
    // Get low level HAL handle.
    low_level_handle = hal_ll_spi_master_get_handle;

    // Get appropriate hw specifics map.
    hal_ll_spi_master_hw_specifics_map_local = hal_ll_get_specifics( hal_ll_spi_master_get_module_state_address );

    low_level_handle->init_ll_state = false;

    // Insert user-defined baud rate into local map.
    hal_ll_spi_master_hw_specifics_map_local->speed = speed;

    // Init once again, but with updated SPI Master baud rate value.
    hal_ll_spi_master_init( hal_ll_spi_master_hw_specifics_map_local );

    low_level_handle->init_ll_state = true;

    // Return value of the SPI Master baud rate value.
    return hal_ll_spi_master_hw_specifics_map_local->hw_actual_speed;
}

hal_ll_err_t hal_ll_spi_master_set_mode( handle_t *handle, hal_ll_spi_master_mode_t mode ) {
    // Get low level HAL handle.
    low_level_handle = hal_ll_spi_master_get_handle;

    // Get appropriate hw specifics map.
    hal_ll_spi_master_hw_specifics_map_local = hal_ll_get_specifics( hal_ll_spi_master_get_module_state_address );

    low_level_handle->init_ll_state = false;

    // Insert user-defined baud rate into local map.
    hal_ll_spi_master_hw_specifics_map_local->mode = mode;

    // Init once again, but with updated SPI Master mode value.
    hal_ll_spi_master_init( hal_ll_spi_master_hw_specifics_map_local );

    low_level_handle->init_ll_state = true;

    // Return value of the SPI Master mode that is going to be used.
    return HAL_LL_SPI_MASTER_SUCCESS;
}

void hal_ll_spi_master_close( handle_t* handle ) {
    // Get low level HAL handle.
    low_level_handle = hal_ll_spi_master_get_handle;

    // Get appropriate hw specifics map.
    hal_ll_spi_master_hw_specifics_map_local = hal_ll_get_specifics( hal_ll_spi_master_get_module_state_address );

    if ( low_level_handle->hal_ll_spi_master_handle != NULL ) {
        low_level_handle->hal_ll_spi_master_handle  = NULL;
        low_level_handle->hal_drv_spi_master_handle  = NULL;
        low_level_handle->init_ll_state = false;

        hal_ll_spi_master_hw_specifics_map_local->mode = HAL_LL_SPI_MASTER_MODE_DEFAULT;
        hal_ll_spi_master_hw_specifics_map_local->speed = HAL_LL_SPI_MASTER_SPEED_100K;
        hal_ll_spi_master_hw_specifics_map_local->dummy_data = 0;
        hal_ll_spi_master_hw_specifics_map_local->hw_actual_speed = 0;

        hal_ll_spi_master_configure_pins( hal_ll_spi_master_hw_specifics_map_local, false );

        hal_ll_spi_master_hw_specifics_map_local->pins.sck = HAL_LL_PIN_NC;
        hal_ll_spi_master_hw_specifics_map_local->pins.miso = HAL_LL_PIN_NC;
        hal_ll_spi_master_hw_specifics_map_local->pins.mosi = HAL_LL_PIN_NC;
    }
}

// ----------------------------------------------- PRIVATE FUNCTION DEFINITIONS
static uint8_t hal_ll_spi_master_transfer_bare_metal( hal_ll_spi_master_hw_specifics_map_t *map, uint8_t data_buffer ) {
    hal_ll_spi_master_base_handle_t *reg_addresses = hal_ll_spi_master_get_base_struct( map->base );

    // Delete overflow information.
    clear_reg_bit( reg_addresses->stat, HAL_LL_RECEIVE_OVERFLOW_FLAG_BIT );

    // Wait for transmition to start.
    while ( check_reg_bit( reg_addresses->stat, HAL_LL_TRANSMIT_BUFFER_FULL_BIT ) );

    // Write transmitted data to buffer.
    *( ( volatile uint8_t * )( reg_addresses->buf ) ) = data_buffer;

    // Wait for receiving to complete.
    while ( !check_reg_bit( reg_addresses->stat, HAL_LL_RECEIVE_BUFFER_FULL_BIT ) );

    return *( ( volatile uint8_t * )reg_addresses->buf );
}

static void hal_ll_spi_master_write_bare_metal( hal_ll_spi_master_hw_specifics_map_t *map, uint8_t *write_data_buffer, size_t write_data_length ) {
    size_t transfer_counter = 0;

    // Write the first data to be transmitted into the SPI_DR register.
    for ( transfer_counter = 0; transfer_counter < write_data_length; transfer_counter++ ) {
        // If we are good to go (if the tx buffer value has been shifted to the shift register), write the data.
        hal_ll_spi_master_transfer_bare_metal( map, write_data_buffer[transfer_counter] );
    }
}

static void hal_ll_spi_master_read_bare_metal( hal_ll_spi_master_hw_specifics_map_t *map, uint8_t *read_data_buffer, size_t read_data_length, uint8_t dummy_data ) {
    size_t transfer_counter = 0;

    // Read the first data to be transmitted into the SPI_DR register.
    for( transfer_counter = 0; transfer_counter < read_data_length; transfer_counter++ ) {
        // If we are good to go (if the value from shift register has been shifted to the rx register), read the data.
        read_data_buffer[transfer_counter] = hal_ll_spi_master_transfer_bare_metal( map, dummy_data );
    }
}

static hal_ll_pin_name_t hal_ll_spi_master_check_pins( hal_ll_pin_name_t sck_pin, hal_ll_pin_name_t miso_pin, hal_ll_pin_name_t mosi_pin, hal_ll_spi_master_pins_t *index_list, hal_ll_spi_master_handle_register_t *handle_map ) {

    static const uint16_t sck_map_size  = ( sizeof( _spi_sck_map ) ) / ( sizeof( hal_ll_spi_master_pin_map_t ) );
    static const uint16_t miso_map_size = ( sizeof( _spi_miso_map ) ) / ( sizeof( hal_ll_spi_master_pin_map_t ) );
    static const uint16_t mosi_map_size = ( sizeof( _spi_mosi_map ) ) / ( sizeof( hal_ll_spi_master_pin_map_t ) );
    uint8_t hal_ll_module_id = 0;
    uint8_t index_counter = 0;
    uint16_t miso_index;
    uint16_t mosi_index;
    uint16_t sck_index;

    if ( ( HAL_LL_PIN_NC == sck_pin ) || ( HAL_LL_PIN_NC == miso_pin ) || ( HAL_LL_PIN_NC == mosi_pin ) ) {
        return HAL_LL_PIN_NC;
    }

    // Check pins from the specific pin maps with the user defined pins.
    for ( sck_index = 0; sck_index < sck_map_size; sck_index++ ) {
        if ( _spi_sck_map[sck_index].pin == sck_pin ) {
            for ( miso_index = 0; miso_index < miso_map_size; miso_index++ ) {
                if ( _spi_miso_map[miso_index].pin == miso_pin ) {
                    if ( _spi_sck_map[sck_index].module_index ==_spi_miso_map[miso_index].module_index ) {
                        for ( mosi_index = 0; mosi_index < mosi_map_size; mosi_index++ ) {
                            if ( _spi_mosi_map[mosi_index].pin ==  mosi_pin ) {
                                if ( _spi_sck_map[sck_index].module_index ==_spi_mosi_map[mosi_index].module_index ) {
                                    // Get module number
                                    hal_ll_module_id = _spi_sck_map[ sck_index ].module_index;

                                    // Map pin names
                                    index_list[hal_ll_module_id]->sck = sck_index;
                                    index_list[hal_ll_module_id]->miso = miso_index;
                                    index_list[hal_ll_module_id]->mosi = mosi_index;

                                    // Check if module is taken
                                    if ( NULL == handle_map[hal_ll_module_id]->hal_drv_spi_master_handle ) {
                                        return hal_ll_module_id;
                                    } else if ( SPI_MODULE_COUNT == ++index_counter ) {
                                        return --index_counter;
                                    }
                                }
                            }
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

static void hal_ll_spi_master_map_pins( uint8_t module_index, hal_ll_spi_master_pins_t *index_list ) {

    hal_ll_spi_master_hw_specifics_map[module_index].pins.sck  = _spi_sck_map[index_list[module_index]->sck].pin;
    hal_ll_spi_master_hw_specifics_map[module_index].pins.miso = _spi_miso_map[index_list[module_index]->miso].pin;
    hal_ll_spi_master_hw_specifics_map[module_index].pins.mosi = _spi_mosi_map[index_list[module_index]->mosi].pin;
    hal_ll_spi_master_hw_specifics_map[module_index].hal_ll_pps_module_index = _spi_mosi_map[index_list[module_index]->mosi].module_index;
}

static hal_ll_spi_master_hw_specifics_map_t *hal_ll_get_specifics(handle_t handle) {
    uint8_t hal_ll_module_count = sizeof( hal_ll_module_state ) / ( sizeof( hal_ll_spi_master_handle_register_t ) );

    static uint8_t hal_ll_module_error = hal_ll_module_count;

    while ( hal_ll_module_count-- ) {
        if ( hal_ll_spi_master_get_base_from_hal_handle == hal_ll_spi_master_hw_specifics_map[hal_ll_module_count].base ) {
            return &hal_ll_spi_master_hw_specifics_map[hal_ll_module_count];
        }
    }

    // If NOK, return pointer to the last row of this map ( point to null pointer ).
    return &hal_ll_spi_master_hw_specifics_map[hal_ll_module_error];
}

static void hal_ll_spi_master_configure_pins( hal_ll_spi_master_hw_specifics_map_t *map, bool hal_ll_state ) {
    hal_ll_gpio_pin_t pin;

    if (hal_ll_state) {
        hal_ll_gpio_configure_pin( &pin, map->pins.miso, HAL_LL_GPIO_DIGITAL_INPUT );
        hal_ll_gpio_configure_pin( &pin, map->pins.mosi, HAL_LL_GPIO_DIGITAL_OUTPUT );
        hal_ll_gpio_configure_pin( &pin, map->pins.sck, HAL_LL_GPIO_DIGITAL_OUTPUT );
    } else {
        hal_ll_gpio_configure_pin( &pin, map->pins.miso, HAL_LL_GPIO_DIGITAL_INPUT );
        hal_ll_gpio_configure_pin( &pin, map->pins.mosi, HAL_LL_GPIO_DIGITAL_INPUT );
        hal_ll_gpio_configure_pin( &pin, map->pins.sck, HAL_LL_GPIO_DIGITAL_INPUT );
    }
}

static void hal_ll_spi_master_fill_speed_array() {
    uint8_t elem, sorting_elem = 0, primary_prescaler = 1;
    uint8_t mask = HAL_LL_SPI_MASTER_SPEED_RESOLUTION_MASK_MAX;
    hal_ll_prescale_handle_t sorting_buffer[HAL_LL_SPI_MASTER_SPEED_COUNT_FOR_SORTING_ARRAY];

    // Fill the array with all possible speed values.
    for ( elem = 1; elem < HAL_LL_SPI_MASTER_SPEED_COUNT_FOR_SORTING_ARRAY + 1; elem++ ) {
        if ( ( elem % HAL_LL_QUARTER_VALUE ) == 1 ) {
            // For the first values of each quarter use _fcy to count prescaled speed.
            sorting_buffer[elem - 1].speed = HAL_LL_SPI_MASTER_SPEED_MAX / primary_prescaler;
            sorting_buffer[elem - 1].mask = mask;
            mask -= 4;
        } else if ( elem % HAL_LL_QUARTER_VALUE ){
            // For other values use the first value of the "quarter".
            sorting_buffer[elem - 1].speed = sorting_buffer[elem - ( elem % HAL_LL_QUARTER_VALUE )].speed / ( 2 + 2 * ( elem % HAL_LL_QUARTER_VALUE - 2 ) );
            sorting_buffer[elem - 1].mask = mask;
            mask -= 8;
        }
        else {
            // If we reached the end of the "quarter" then change the mask in a different way
            sorting_buffer[elem - 1].speed = sorting_buffer[elem - HAL_LL_QUARTER_VALUE ].speed / ( 2 + 2 * ( HAL_LL_QUARTER_VALUE - 2 ) );
            sorting_buffer[elem - 1].mask = mask;
            mask = HAL_LL_SPI_MASTER_SPEED_RESOLUTION_MASK_MAX - elem / HAL_LL_QUARTER_VALUE;
            primary_prescaler *= 4;
        }
    }

    for ( elem = 0; elem < HAL_LL_SPI_MASTER_SPEED_COUNT_FOR_SORTING_ARRAY; elem++ ) {
        if ( ( ( elem >= HAL_LL_QUARTER_VALUE ) && ( !( elem % HAL_LL_QUARTER_VALUE ) || !( elem % HAL_LL_QUARTER_VALUE - 1 ) ) ) ||
                ( elem == 0 ) )
            continue;
        #ifdef dsPIC30F
        if ( elem == 1 )
            continue;
        #endif
        hal_ll_spi_master_speed_array[sorting_elem].speed = sorting_buffer[elem].speed;
        hal_ll_spi_master_speed_array[sorting_elem].mask = sorting_buffer[elem].mask;
        sorting_elem++;
    }
    hal_ll_spi_master_speeds_number = sorting_elem - 1;
}

static uint8_t hal_ll_get_available_speed_mask( uint32_t user_speed ) {
    uint8_t elem;

    for ( elem = 0; elem < HAL_LL_SPI_MASTER_SPEED_MAX + 1; elem++ ) {
        if ( ( hal_ll_spi_master_speed_array[elem].speed >= user_speed ) && ( hal_ll_spi_master_speed_array[elem + 1].speed <= user_speed ) ) {
            break;
        }
    }

    if ( hal_ll_spi_master_speed_array[elem].speed - user_speed < user_speed - hal_ll_spi_master_speed_array[elem + 1].speed )
        return ( hal_ll_spi_master_speed_array[elem].mask );
    else
        return ( hal_ll_spi_master_speed_array[elem + 1].mask );
}

static uint8_t hal_ll_spi_master_set_speed_prescaler( hal_ll_spi_master_hw_specifics_map_t *map ) {
    // Prescaler value (starting from 0 -> highest SPI speed, up to 255 -> lowest SPI speed).
    uint8_t prescaler_mask = 0;

    // Minimum bandwidth.
    static const uint32_t speed_minimum = hal_ll_spi_master_speed_array[hal_ll_spi_master_speeds_number].speed;

    // Maximum bandwidth.
    static const uint32_t speed_maximum = hal_ll_spi_master_speed_array[HAL_LL_MAX_SPEED_MEMBER].speed;

    // If user-defined SPI speed is less then or equal to eligible hardware frequency, set SPI speed to be the minimal possible.
    if ( map->speed <= speed_minimum ) {

        return hal_ll_spi_master_speed_array[hal_ll_spi_master_speeds_number].mask;

    // If user-defined SPI speed is greater then or equal to eligible hardware frequency, set SPI speed to be the maximal possible.
    } else if ( map->speed >= speed_maximum ) {

        return hal_ll_spi_master_speed_array[HAL_LL_MAX_SPEED_MEMBER].mask;

    // If user-defined SPI speed is in between, find as closest SPI speed prescaler as possible.
    } else {
        prescaler_mask = hal_ll_get_available_speed_mask( map->speed );

        return prescaler_mask;
    }
}

static uint16_t hal_ll_spi_master_set_baud_rate( hal_ll_spi_master_hw_specifics_map_t *map ) {
    if ( HAL_LL_SPI_MASTER_SPEED_MAX < map->speed )
        return ( hal_ll_spi_get_brg_value( HAL_LL_SPI_MASTER_SPEED_MAX ) );
    else if ( HAL_LL_SPI_MASTER_SPEED_MIN > map->speed )
        return ( hal_ll_spi_get_brg_value( HAL_LL_SPI_MASTER_SPEED_MIN ) );
    return ( hal_ll_spi_get_brg_value( map->speed ) );
}

static void hal_ll_spi_master_hw_init( hal_ll_spi_master_hw_specifics_map_t *map ) {
    hal_ll_spi_master_base_handle_t *reg_addresses = hal_ll_spi_master_get_base_struct( map->base );
	#ifndef HAL_LL_SPI1BRGL_REG_ADDRESS
    uint8_t prescaler_mask = hal_ll_spi_master_set_speed_prescaler( map );
    #else
    uint16_t brg_reg_value = hal_ll_spi_master_set_baud_rate( map );
    clear_reg( reg_addresses->brg );
	#endif

    // Make sure registers are clear.
    clear_reg( reg_addresses->stat );
    clear_reg( reg_addresses->con );
	clear_reg( reg_addresses->buf );

    // Enable bus master mode.
    set_reg_bit( reg_addresses->con, HAL_LL_MASTER_MODE_ENABLE_BIT );

    // Setup clock polarity and edge ( mode setup ).
    switch ( map->mode )
    {
        case HAL_LL_SPI_MASTER_MODE_0:
            clear_reg_bit( reg_addresses->con, HAL_LL_CLOCK_POLARITY_SETUP_BIT );
            set_reg_bit( reg_addresses->con, HAL_LL_CLOCK_EDGE_SETUP_BIT );
            break;
        case HAL_LL_SPI_MASTER_MODE_1:
            clear_reg_bit( reg_addresses->con, HAL_LL_CLOCK_POLARITY_SETUP_BIT );
            clear_reg_bit( reg_addresses->con, HAL_LL_CLOCK_EDGE_SETUP_BIT );
            break;
        case HAL_LL_SPI_MASTER_MODE_2:
            set_reg_bit( reg_addresses->con, HAL_LL_CLOCK_POLARITY_SETUP_BIT );
            set_reg_bit( reg_addresses->con, HAL_LL_CLOCK_EDGE_SETUP_BIT );
            break;
        case HAL_LL_SPI_MASTER_MODE_3:
            set_reg_bit( reg_addresses->con, HAL_LL_CLOCK_POLARITY_SETUP_BIT );
            clear_reg_bit( reg_addresses->con, HAL_LL_CLOCK_EDGE_SETUP_BIT );
            break;

        default:
            break;
    }

    // Delete overflow information.
    clear_reg_bit( reg_addresses->stat, HAL_LL_RECEIVE_OVERFLOW_FLAG_BIT );

    #ifndef HAL_LL_SPI1BRGL_REG_ADDRESS
    // Set up primary and secondary prescalers depending on user speed preference.
    set_reg_bits( reg_addresses->con, prescaler_mask );
    // Enable SPI module.
    set_reg_bit( reg_addresses->stat, HAL_LL_SPI_ENABLE_BIT );
    #else
    // Set baudrate generator divider bits
    write_reg( reg_addresses->brg, brg_reg_value );
    // Enable SPI module.
    set_reg_bit( reg_addresses->con, HAL_LL_SPI_ENABLE_BIT );
	#endif
}

static hal_ll_pps_err_t _hal_ll_pps_set_state(hal_ll_spi_master_hw_specifics_map_t *map, bool hal_ll_state) {
    hal_ll_pps_err_t hal_ll_status = HAL_LL_PPS_SUCCESS;

    if( (map->pins.sck != HAL_LL_PIN_NC) && (map->pins.miso != HAL_LL_PIN_NC) && (map->pins.mosi != HAL_LL_PIN_NC) ) {

        hal_ll_status = hal_ll_pps_map((map->pins.sck & HAL_LL_NIBBLE_HIGH_8BIT) >> 4, map->pins.sck & HAL_LL_NIBBLE_LOW_8BIT, HAL_LL_GPIO_DIGITAL_OUTPUT,
                                                HAL_LL_PPS_FUNCTIONALITY_SPI_SCK, map->hal_ll_pps_module_index, hal_ll_state);

        if (hal_ll_status != HAL_LL_PPS_SUCCESS) {
            return hal_ll_status;
        }

        #ifdef __hal_ll_pps_spi_in_out__
        hal_ll_status = hal_ll_pps_map((map->pins.sck & HAL_LL_NIBBLE_HIGH_8BIT) >> 4, map->pins.sck & HAL_LL_NIBBLE_LOW_8BIT, HAL_LL_GPIO_DIGITAL_INPUT,
                                                HAL_LL_PPS_FUNCTIONALITY_SPI_SCK, map->hal_ll_pps_module_index, hal_ll_state);

        if (hal_ll_status != HAL_LL_PPS_SUCCESS) {
            return hal_ll_status;
        }
        #endif

        hal_ll_status = hal_ll_pps_map((map->pins.miso & HAL_LL_NIBBLE_HIGH_8BIT) >> 4, map->pins.miso & HAL_LL_NIBBLE_LOW_8BIT, HAL_LL_GPIO_DIGITAL_INPUT,
                                                HAL_LL_PPS_FUNCTIONALITY_SPI_MISO, map->hal_ll_pps_module_index, hal_ll_state);

        if (hal_ll_status != HAL_LL_PPS_SUCCESS) {
            return hal_ll_status;
        }

        hal_ll_status = hal_ll_pps_map((map->pins.mosi & HAL_LL_NIBBLE_HIGH_8BIT) >> 4, map->pins.mosi & HAL_LL_NIBBLE_LOW_8BIT, HAL_LL_GPIO_DIGITAL_OUTPUT,
                                                HAL_LL_PPS_FUNCTIONALITY_SPI_MOSI, map->hal_ll_pps_module_index, hal_ll_state);

        if (hal_ll_status != HAL_LL_PPS_SUCCESS) {
            return hal_ll_status;
        }
    } else {
        return HAL_LL_PPS_SUCCESS;
    }
}

static void hal_ll_spi_master_init( hal_ll_spi_master_hw_specifics_map_t *map ) {
    // Configure pins which are going to be used for SPI communication.
    hal_ll_spi_master_configure_pins( map, true );

    // Used only for chips which have SPI PPS pins
    #if HAL_LL_SPI_PPS_ENABLED == true
    // Set pps functions for mapped pins
    _hal_ll_pps_set_state( map, true );
    #endif

    // Finally, write user-defined settings into hardware registers.
    hal_ll_spi_master_hw_init( map );
}
// ------------------------------------------------------------------------- END
