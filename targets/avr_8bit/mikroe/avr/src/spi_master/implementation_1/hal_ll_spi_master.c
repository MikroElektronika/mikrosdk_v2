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
#include "hal_ll_spi_master_pin_map.h"

/*!< @brief Local handle list */
static volatile hal_ll_spi_master_handle_register_t hal_ll_module_state[SPI_MODULE_COUNT] = {(handle_t *)NULL, (handle_t *)NULL, false};

// ------------------------------------------------------------- PRIVATE MACROS
/*!< @brief Helper macro for getting hal_ll_module_state address */
#define hal_ll_spi_master_get_module_state_address ((hal_ll_spi_master_handle_register_t *)*handle)
/*!< @brief Helper macro for getting module specific control register structure base address // first register address */
#define hal_ll_spi_master_get_handle (hal_ll_spi_master_handle_register_t *)hal_ll_spi_master_get_module_state_address->hal_ll_spi_master_handle
/*!< @brief Helper macro for getting module specific control register structure */
#define hal_ll_spi_master_get_base_struct(_handle) ((const hal_ll_spi_master_base_handle_t *)_handle)
/*!< @brief Helper macro for getting module specific base address directly from HAL layer handle */
#define hal_ll_spi_master_get_base_from_hal_handle ((hal_ll_spi_master_hw_specifics_map_t *)((hal_ll_spi_master_handle_register_t *)\
                                                   (((hal_ll_spi_master_handle_register_t *)(handle))->hal_ll_spi_master_handle))->hal_ll_spi_master_handle)->base

/*!< @brief Helper macros for baud rate dividers. */
#define HAL_LL_SPI_MASTER_CLK_BAUD_RATE_DIVIDER_2 (2)
#define HAL_LL_SPI_MASTER_CLK_BAUD_RATE_DIVIDER_4 (4)
#define HAL_LL_SPI_MASTER_CLK_BAUD_RATE_DIVIDER_8 (8)
#define HAL_LL_SPI_MASTER_CLK_BAUD_RATE_DIVIDER_16 (16)
#define HAL_LL_SPI_MASTER_CLK_BAUD_RATE_DIVIDER_32 (32)
#define HAL_LL_SPI_MASTER_CLK_BAUD_RATE_DIVIDER_64 (64)
#define HAL_LL_SPI_MASTER_CLK_BAUD_RATE_DIVIDER_128 (128)

/*!< @brief Helper macro for clock polarity. */
#define HAL_LL_SPI_MASTER_CLK_POLARITY (3)

/*!< @brief Helper macro for clock phase. */
#define HAL_LL_SPI_MASTER_CLK_PHASE (2)

/*!< @brief Helper macro for configuring SPI module as a master. */
#define HAL_LL_SPI_MASTER_MODE (4)

/*!< @brief Helper macro for enabling SPI module. */
#define HAL_LL_SPI_MODULE_ENABLE (6)

/*!< @brief Helper macro for serial transfer complete. */
#define HAL_LL_SPI_MASTER_TRANSFER_COMPLETE_FLAG_BIT (7)

/*!< @brief Helper macros for baud rate selection. */
#define HAL_LL_SPI_MASTER_CLK_BAUD_RATE_BIT_0 (0)
#define HAL_LL_SPI_MASTER_CLK_BAUD_RATE_BIT_1 (1)
#define HAL_LL_SPI_MASTER_CLK_BAUD_RATE_BIT_2 (7)

/*!< @brief Helper macros for powering up/down SPI module. */
#define HAL_LL_PRR0_PRSPI0_BIT (2)
#define HAL_LL_PRR1_PRSPI1_BIT (1)
#define HAL_LL_PRR_SPI_BIT (3)

/*!< @brief Helper macro for retrieving MCU clock in Hz. */
#define _fosc (Get_Fosc_kHz()*1000)

/*!< @brief Default SPI Master bit-rate if no speed is set. */
#define HAL_LL_SPI_MASTER_SPEED_100K (100000)

/*!< @brief Helper macro for masking SPI0 PRR0 module for MCUs which utilize SPI PRR module only. */
#ifdef HAL_LL_PRR_REG_ADDRESS
#define HAL_LL_PRR0_REG_ADDRESS HAL_LL_PRR_REG_ADDRESS
#endif

// -------------------------------------------------------------- PRIVATE TYPES
/*!< @brief SPI register structure. */
typedef struct {
    hal_ll_base_addr_t spi_spcr_reg_addr; // SPI Control register.
    hal_ll_base_addr_t spi_spsr_reg_addr; // SPI Status register.
    hal_ll_base_addr_t spi_spdr_reg_addr; // SPI Data register.
} hal_ll_spi_master_base_handle_t;

/*!< @brief SPI Master hardware specific structure */
typedef struct {
    const hal_ll_spi_master_base_handle_t *base;
    uint8_t module_index;
    hal_ll_spi_master_pins_t pins;
    uint8_t  dummy_data;
    uint32_t speed;
    uint32_t hw_actual_speed;
    hal_ll_spi_master_mode_t mode;
} hal_ll_spi_master_hw_specifics_map_t;

/*!< @brief SPI Master hw specific error values */
typedef enum {
    HAL_LL_SPI_MASTER_SUCCESS = 0,
    HAL_LL_SPI_MASTER_WRONG_PINS,
    HAL_LL_SPI_MASTER_MODULE_ERROR,

    HAL_LL_SPI_MASTER_ERROR = (-1)
} hal_ll_spi_master_err_t;

// ------------------------------------------------------------------ CONSTANTS
// SPI Master module registers array.
static const hal_ll_spi_master_base_handle_t hal_ll_spi_master_registers[ SPI_MODULE_COUNT + 1 ] = {
    #ifdef SPI_MODULE_0
    { HAL_LL_SPI0_CTRL_REG_ADDRESS, HAL_LL_SPI0_STATUS_REG_ADDRESS, HAL_LL_SPI0_DATA_REG_ADDRESS },
    #endif

    #ifdef SPI_MODULE_1
    { HAL_LL_SPI1_CTRL_REG_ADDRESS, HAL_LL_SPI1_STATUS_REG_ADDRESS, HAL_LL_SPI1_DATA_REG_ADDRESS },
    #endif

    #ifdef SPI_MODULE_2
    #if defined (__hal_ll_spi_master_subset_atxmega__)
    { HAL_LL_SPI2_CTRL_REG_ADDRESS, HAL_LL_SPI2_STATUS_REG_ADDRESS, HAL_LL_SPI2_DATA_REG_ADDRESS },
    #endif
    #endif

    #ifdef SPI_MODULE_3
    #if defined (__hal_ll_spi_master_subset_atxmega__)
    { HAL_LL_SPI3_CTRL_REG_ADDRESS, HAL_LL_SPI3_STATUS_REG_ADDRESS, HAL_LL_SPI3_DATA_REG_ADDRESS },
    #endif
    #endif

    { HAL_LL_MODULE_ERROR, HAL_LL_MODULE_ERROR, HAL_LL_MODULE_ERROR }
};

// ------------------------------------------------------------------ VARIABLES
/*!< @brief SPI Master hardware specific info */
static hal_ll_spi_master_hw_specifics_map_t hal_ll_spi_master_hw_specifics_map[ SPI_MODULE_COUNT + 1 ] = {
    #ifdef SPI_MODULE_0
    { &hal_ll_spi_master_registers[hal_ll_spi_master_module_num(SPI_MODULE_0)], hal_ll_spi_master_module_num(SPI_MODULE_0),
    { HAL_LL_PIN_NC, HAL_LL_PIN_NC, HAL_LL_PIN_NC, HAL_LL_PIN_NC }, 0, HAL_LL_SPI_MASTER_SPEED_100K, 0, HAL_LL_SPI_MASTER_MODE_DEFAULT },
    #endif

    #ifdef SPI_MODULE_1
    { &hal_ll_spi_master_registers[hal_ll_spi_master_module_num(SPI_MODULE_1)], hal_ll_spi_master_module_num(SPI_MODULE_1),
    { HAL_LL_PIN_NC, HAL_LL_PIN_NC, HAL_LL_PIN_NC, HAL_LL_PIN_NC }, 0, HAL_LL_SPI_MASTER_SPEED_100K, 0, HAL_LL_SPI_MASTER_MODE_DEFAULT },
    #endif

    #ifdef SPI_MODULE_2
    #if defined (__hal_ll_spi_master_subset_atxmega__)
    { &hal_ll_spi_master_registers[hal_ll_spi_master_module_num(SPI_MODULE_2)], hal_ll_spi_master_module_num(SPI_MODULE_2),
    { HAL_LL_PIN_NC, HAL_LL_PIN_NC, HAL_LL_PIN_NC, HAL_LL_PIN_NC }, 0, HAL_LL_SPI_MASTER_SPEED_100K, 0, HAL_LL_SPI_MASTER_MODE_DEFAULT },
    #endif
    #endif

    #ifdef SPI_MODULE_3
    #if defined (__hal_ll_spi_master_subset_atxmega__)
    { &hal_ll_spi_master_registers[hal_ll_spi_master_module_num(SPI_MODULE_3)], hal_ll_spi_master_module_num(SPI_MODULE_3),
    { HAL_LL_PIN_NC, HAL_LL_PIN_NC, HAL_LL_PIN_NC, HAL_LL_PIN_NC }, 0, HAL_LL_SPI_MASTER_SPEED_100K, 0, HAL_LL_SPI_MASTER_MODE_DEFAULT },
    #endif
    #endif

    { &hal_ll_spi_master_registers[SPI_MODULE_COUNT], HAL_LL_MODULE_ERROR,
    { HAL_LL_PIN_NC, HAL_LL_PIN_NC, HAL_LL_PIN_NC, HAL_LL_PIN_NC }, NULL, NULL, NULL }
};

/*!< @brief Global handle variables used in functions */
static volatile hal_ll_spi_master_handle_register_t *low_level_handle;
static volatile hal_ll_spi_master_hw_specifics_map_t *hal_ll_spi_master_hw_specifics_map_local;

// ---------------------------------------------- PRIVATE FUNCTION DECLARATIONS

/**
  * @brief Check if pins are adequate.
  *
  * Checks SCK, MISO and MOSI pins the user has passed with pre-defined
  * pins in SCK, MISO and MOSI maps. Take into consideration that module
  * index numbers have to be the same for both pins.
  *
  * @param[in] sck - SCK pre-defined pin name.
  * @param[in] miso - MISO pre-defined pin name.
  * @param[in] mosi - MOSI pre-defined pin name.
  * @param[in] *index_list - Index list.
  * @return hal_ll_pin_name_t Module index based on pins.
  *
  * Returns pre-defined module index from pin maps, if pins
  * are adequate.
  */
static hal_ll_pin_name_t hal_ll_spi_master_check_pins( hal_ll_pin_name_t sck, hal_ll_pin_name_t miso,
                                                       hal_ll_pin_name_t mosi, hal_ll_spi_master_pins_t *index_list,
                                                       hal_ll_spi_master_handle_register_t *handle_map );

/**
  * @brief Get local hardware specific map.
  *
  * Checks handle value and returns address of adequate
  * hal_ll_spi_master_hw_specifics_map array index.
  *
  * @param[in] handle - Object specific context handler.
  * @return hal_ll_spi_master_hw_specifics_map_t Map address.
  *
  * Returns pre-defined map index address based on handle value,
  * if handle is adequate.
  */
static hal_ll_spi_master_hw_specifics_map_t *hal_ll_get_specifics( handle_t handle );

/**
  * @brief Enable clock for SPI module on hardware level.
  *
  * Initializes SPI module clock on hardware level, based on beforehand
  * set configuration and module handler.
  *
  * @param[in] *map - Object specific context handler.
  * @param[in] hal_ll_state - True(enable clock)/False(disable clock).
  * @return None
  */
static void hal_ll_spi_master_set_clock( hal_ll_spi_master_hw_specifics_map_t *map, bool hal_ll_state );

/**
  * @brief Full SPI Master module initialization procedure.
  *
  * Initializes SPI Master module on hardware level, based on beforehand
  * set configuration and module handler. Sets adequate pin alternate functions.
  * Initializes module clock.
  *
  * @param[in] *map - Object specific context handler.
  * @return hal_ll_err_t Module specific values.
  *
  * Returns one of pre-defined values.
  * Take into consideration that this is hardware specific.
  */
static void hal_ll_spi_master_init( hal_ll_spi_master_hw_specifics_map_t *map );

/**
 * @brief Maps new-found module specific values.
 *
 * Maps pin names and alternate function values for
 * SPI SCK, MISO and MOSI pins.
 *
 * @param[in]  module_index SPI HW module index -- 0,1,2...
 * @param[in]  *index_list  Array with SCK, MISO and MOSI map index values
 *
 * @return None
 */
static void hal_ll_spi_master_map_pins( uint8_t module_index, hal_ll_spi_master_pins_t *index_list );

/**
  * @brief Perform a read on the SPI Master bus.
  *
  * Initializes SPI Master module on hardware level, if not initialized beforehand
  * and continues to perform a read operation on the bus.
  *
  * @param[in] *map - Object specific context handler.
  * @param[in] *read_data_buffer - Pointer to data buffer.
  * @param[in] read_data_length - Number of data to be read.
  * @param[in] dummy_data - Data required for read procedure.
  * @return hal_ll_err_t Module specific error values.
  *
  * Returns one of pre-defined error values.
  * Take into consideration that this is hardware specific.
  */
static void hal_ll_spi_master_read_bare_metal( hal_ll_spi_master_hw_specifics_map_t *map, uint8_t *read_data_buffer,
                                               size_t read_data_length, uint8_t dummy_data );

/**
  * @brief Perform a write on the SPI Master bus.
  *
  * Initializes SPI Master module on hardware level, if not initialized beforehand
  * and continues to perform a write operation on the bus.
  *
  * @param[in] *map - Object specific context handler.
  * @param[in] *write_data_buffer - Pointer to data buffer.
  * @param[in] write_data_length - Number of data to be written.
  * @return hal_ll_err_t Module specific error values.
  *
  * Returns one of pre-defined error values.
  * Take into consideration that this is hardware specific.
  */
static void hal_ll_spi_master_write_bare_metal( hal_ll_spi_master_hw_specifics_map_t *map, uint8_t * __generic_ptr write_data_buffer,
                                                size_t write_data_length );

/**
  * @brief Perform a transfer on the SPI Master bus.
  *
  * Initializes SPI Master module on hardware level, if not initialized beforehand
  * and continues to perform a write operation on the bus.
  *
  * @param[in] *map - Object specific context handler.
  * @param[in] data_buffer - User-specific data, or dummy data.
  * @return data Read data.
  *
  * Returns one of pre-defined error values.
  * Take into consideration that this is hardware specific.
  */
static uint8_t hal_ll_spi_master_transfer_bare_metal( hal_ll_spi_master_hw_specifics_map_t *map, uint8_t data_buffer );

/**
 * @brief Set GPIO state.
 *
 * Sets adequate TRISx register
 * values for adequate functionality.
 *
 * @param *map - Object specific context handler.
 * @param hal_ll_state - init or deinit
 *
 * @return none.
 *
 * @note AVR specific.
 */
static void hal_ll_spi_master_configure_pins( hal_ll_spi_master_hw_specifics_map_t *map, bool hal_ll_state );

/**
 * @brief Set SPI baud rate.
 *
 * Calculate Baud Rate value.
 *
 * @param[in] *map - Object specific context handler.
 *
 * @return none.
 *
 * @note AVR specific.
 */
static void hal_ll_spi_master_set_baud_rate(hal_ll_spi_master_hw_specifics_map_t *map);

// ------------------------------------------------ PUBLIC FUNCTION DEFINITIONS
hal_ll_err_t hal_ll_spi_master_register_handle(hal_ll_pin_name_t sck, hal_ll_pin_name_t miso, hal_ll_pin_name_t mosi,
                                               hal_ll_spi_master_handle_register_t *handle_map, uint8_t *hal_module_id ) {
    hal_ll_spi_master_pins_t index_list[ SPI_MODULE_COUNT ] = { HAL_LL_PIN_NC, HAL_LL_PIN_NC, HAL_LL_PIN_NC, HAL_LL_PIN_NC };
    uint8_t pin_check_result;

    // Check user-defined pins.
    if ( HAL_LL_PIN_NC == ( pin_check_result = hal_ll_spi_master_check_pins(sck, miso, mosi, &index_list, handle_map ) ) ) {
        return HAL_LL_SPI_MASTER_WRONG_PINS;
    }

    // If user has come with the same SPI hardware module, and with the same pair of the pins, the pin mapping procedure
    // will not take a place; otherwise, clear af-s, map new pins, set af-s, and set init state to false.
    if ( ( hal_ll_spi_master_hw_specifics_map[ pin_check_result ].pins.sck != sck ) ||
        ( hal_ll_spi_master_hw_specifics_map[ pin_check_result ].pins.miso != miso ) ||
        ( hal_ll_spi_master_hw_specifics_map[ pin_check_result ].pins.mosi != mosi ) ) {

        // Map new pps.
        hal_ll_spi_master_map_pins( pin_check_result, &index_list );

        handle_map[ pin_check_result ]->init_ll_state = false;
    }

    // Return id of the SPI module that is going to be used.
    *hal_module_id = pin_check_result;

    // Insert current module into hal_ll_module_state map.
    hal_ll_module_state[ pin_check_result ].hal_ll_spi_master_handle = (handle_t *)&hal_ll_spi_master_hw_specifics_map[ pin_check_result ].base;

    // Return the same info about module one level up (into the HAL level).
    handle_map[ pin_check_result ]->hal_ll_spi_master_handle = (handle_t *)&hal_ll_module_state[ pin_check_result ].hal_ll_spi_master_handle;

    return HAL_LL_SPI_MASTER_SUCCESS;
}

hal_ll_err_t hal_ll_module_configure_spi( handle_t *handle ) {
    hal_ll_spi_master_hw_specifics_map_local = hal_ll_get_specifics(hal_ll_spi_master_get_module_state_address);
    hal_ll_spi_master_handle_register_t *hal_handle = (hal_ll_spi_master_handle_register_t *)*handle;
    uint8_t pin_check_result = hal_ll_spi_master_hw_specifics_map_local->module_index;

    hal_ll_spi_master_init( hal_ll_spi_master_hw_specifics_map_local );

    hal_ll_module_state[ pin_check_result ].hal_ll_spi_master_handle = (handle_t *)&hal_ll_spi_master_hw_specifics_map[ pin_check_result ].base;
    hal_ll_module_state[ pin_check_result ].init_ll_state = true;
    hal_handle->init_ll_state = true;

    return HAL_LL_SPI_MASTER_SUCCESS;
}

void hal_ll_spi_master_set_default_write_data( handle_t *handle, uint8_t dummy_data ) {
    low_level_handle = hal_ll_spi_master_get_handle;
    // Get appropriate hw specifics map.
    hal_ll_spi_master_hw_specifics_map_local = hal_ll_get_specifics(hal_ll_spi_master_get_module_state_address);

    hal_ll_spi_master_hw_specifics_map_local->dummy_data = dummy_data;
}

hal_ll_err_t hal_ll_spi_master_write( handle_t *handle, uint8_t * __generic_ptr write_data_buffer, size_t length_data ) {
    // Get low level HAL handle.
    low_level_handle = hal_ll_spi_master_get_handle;

    // Get appropriate hw specifics map.
    hal_ll_spi_master_hw_specifics_map_local = hal_ll_get_specifics(hal_ll_spi_master_get_module_state_address);

    hal_ll_spi_master_write_bare_metal( hal_ll_spi_master_hw_specifics_map_local, write_data_buffer, length_data );

    return HAL_LL_SPI_MASTER_SUCCESS;
}

hal_ll_err_t hal_ll_spi_master_read( handle_t *handle, uint8_t *read_data_buffer, size_t length_data ) {
    // Get low level HAL handle.
    low_level_handle = hal_ll_spi_master_get_handle;

    // Get appropriate hw specifics map.
    hal_ll_spi_master_hw_specifics_map_local = hal_ll_get_specifics(hal_ll_spi_master_get_module_state_address);

    hal_ll_spi_master_read_bare_metal( hal_ll_spi_master_hw_specifics_map_local, read_data_buffer, length_data,
                                       hal_ll_spi_master_hw_specifics_map_local->dummy_data );

    return HAL_LL_SPI_MASTER_SUCCESS;
}

hal_ll_err_t hal_ll_spi_master_write_then_read( handle_t *handle, uint8_t *write_data_buffer, size_t length_write_data,
                                                uint8_t *read_data_buffer, size_t length_read_data ) {
    // Get low level HAL handle.
    low_level_handle = hal_ll_spi_master_get_handle;

    // Get appropriate hw specifics map.
    hal_ll_spi_master_hw_specifics_map_local = hal_ll_get_specifics(hal_ll_spi_master_get_module_state_address);

    hal_ll_spi_master_write_bare_metal( hal_ll_spi_master_hw_specifics_map_local, write_data_buffer, length_write_data );

    hal_ll_spi_master_read_bare_metal( hal_ll_spi_master_hw_specifics_map_local, read_data_buffer, length_read_data,
                                       hal_ll_spi_master_hw_specifics_map_local->dummy_data );

    return HAL_LL_SPI_MASTER_SUCCESS;
}

uint32_t hal_ll_spi_master_set_speed( handle_t *handle, uint32_t speed ) {
    // Get low level HAL handle.
    low_level_handle = hal_ll_spi_master_get_handle;

    // Get appropriate hw specifics map.
    hal_ll_spi_master_hw_specifics_map_local = hal_ll_get_specifics(hal_ll_spi_master_get_module_state_address);

    low_level_handle->init_ll_state = false;

    // Insert user-defined baud rate into local map.
    hal_ll_spi_master_hw_specifics_map_local->speed = speed;

    // Init once again, but with updated SPI Master baud rate value.
    hal_ll_spi_master_init(hal_ll_spi_master_hw_specifics_map_local);

    low_level_handle->init_ll_state = true;

    // Return value of the SPI Master baud rate value.
    return hal_ll_spi_master_hw_specifics_map_local->hw_actual_speed;
}

hal_ll_err_t hal_ll_spi_master_set_mode( handle_t *handle, hal_ll_spi_master_mode_t mode ) {
    // Get low level HAL handle.
    low_level_handle = hal_ll_spi_master_get_handle;

    // Get appropriate hw specifics map.
    hal_ll_spi_master_hw_specifics_map_local = hal_ll_get_specifics(hal_ll_spi_master_get_module_state_address);

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
    hal_ll_spi_master_hw_specifics_map_local = hal_ll_get_specifics(hal_ll_spi_master_get_module_state_address);

    if( NULL != low_level_handle->hal_ll_spi_master_handle ) {
        low_level_handle->hal_ll_spi_master_handle  = NULL;
        low_level_handle->hal_drv_spi_master_handle  = NULL;
        low_level_handle->init_ll_state = false;

        hal_ll_spi_master_hw_specifics_map_local->mode = HAL_LL_SPI_MASTER_MODE_DEFAULT;
        hal_ll_spi_master_hw_specifics_map_local->speed = HAL_LL_SPI_MASTER_SPEED_100K;
        hal_ll_spi_master_hw_specifics_map_local->dummy_data = 0;
        hal_ll_spi_master_hw_specifics_map_local->hw_actual_speed = 0;

        hal_ll_spi_master_set_clock( hal_ll_spi_master_hw_specifics_map_local, true );
        hal_ll_spi_master_configure_pins( hal_ll_spi_master_hw_specifics_map_local, false );
        hal_ll_spi_master_set_clock( hal_ll_spi_master_hw_specifics_map_local, false );

        hal_ll_spi_master_hw_specifics_map_local->pins.sck = HAL_LL_PIN_NC;
        hal_ll_spi_master_hw_specifics_map_local->pins.miso = HAL_LL_PIN_NC;
        hal_ll_spi_master_hw_specifics_map_local->pins.mosi = HAL_LL_PIN_NC;
    }
}

// ----------------------------------------------- PRIVATE FUNCTION DEFINITIONS
static uint8_t hal_ll_spi_master_transfer_bare_metal( hal_ll_spi_master_hw_specifics_map_t *map, uint8_t data_buffer ) {
    const hal_ll_spi_master_base_handle_t *hal_ll_hw_reg = hal_ll_spi_master_get_base_struct( map->base );

    // Write user-defined data ( 'hal_ll_spi_master_read_bare_metal' procedure will send dummy data ).
    write_reg( hal_ll_hw_reg->spi_spdr_reg_addr, data_buffer );

    // Wait until transmission of byte is completed.
    while ( !check_reg_bit( hal_ll_hw_reg->spi_spsr_reg_addr, HAL_LL_SPI_MASTER_TRANSFER_COMPLETE_FLAG_BIT ) );

    // Return read data.
    return read_reg( hal_ll_hw_reg->spi_spdr_reg_addr );
}

static void hal_ll_spi_master_write_bare_metal( hal_ll_spi_master_hw_specifics_map_t *map, uint8_t * __generic_ptr write_data_buffer,
                                                size_t write_data_length ) {
    size_t transfer_counter = 0;
    const hal_ll_spi_master_base_handle_t *hal_ll_hw_reg = hal_ll_spi_master_get_base_struct( map->base );

    // Write the first data to be transmitted into the SPI_DR register.
    for( transfer_counter = 0; transfer_counter < write_data_length; transfer_counter++ ) {
        // If we are good to go ( if the tx buffer value has been shifted to the shift register ), write the data.
        hal_ll_spi_master_transfer_bare_metal( map, write_data_buffer[ transfer_counter ] );
    }
}

static void hal_ll_spi_master_read_bare_metal( hal_ll_spi_master_hw_specifics_map_t *map, uint8_t *read_data_buffer,
                                               size_t read_data_length, uint8_t dummy_data ) {
    const hal_ll_spi_master_base_handle_t *hal_ll_hw_reg = hal_ll_spi_master_get_base_struct( map->base );
    volatile size_t transfer_counter = 0;

    // Read the first data to be transmitted into the SPI_DR register.
    for( transfer_counter = 0; transfer_counter < read_data_length; transfer_counter++ ) {
        // If we are good to go (if the value from shift register has been shifted to the rx register), read the data.
        read_data_buffer[ transfer_counter ] = hal_ll_spi_master_transfer_bare_metal( map, dummy_data );
    }
}

static hal_ll_pin_name_t hal_ll_spi_master_check_pins( hal_ll_pin_name_t sck_pin, hal_ll_pin_name_t miso_pin,
                                                       hal_ll_pin_name_t mosi_pin, hal_ll_spi_master_pins_t *index_list,
                                                       hal_ll_spi_master_handle_register_t *handle_map ) {
    static const uint8_t sck_map_size  = ( sizeof( _spi_sck_map ) ) / ( sizeof( hal_ll_spi_master_pin_map_t ) );
    static const uint8_t miso_map_size = ( sizeof( _spi_miso_map ) ) / ( sizeof( hal_ll_spi_master_pin_map_t ) );
    static const uint8_t mosi_map_size = ( sizeof( _spi_mosi_map ) ) / ( sizeof( hal_ll_spi_master_pin_map_t ) );
    uint8_t hal_ll_module_id = 0;
    uint8_t index_counter = 0;
    uint8_t miso_index;
    uint8_t mosi_index;
    uint8_t sck_index;

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
                            if ( _spi_mosi_map[mosi_index ].pin ==  mosi_pin ) {
                                if ( _spi_sck_map[sck_index].module_index ==_spi_mosi_map[mosi_index].module_index ) {
                                    // Get module number
                                    hal_ll_module_id = _spi_sck_map[ sck_index ].module_index;

                                    // Map pin names
                                    index_list[ hal_ll_module_id ]->sck = sck_index;
                                    index_list[ hal_ll_module_id ]->miso = miso_index;
                                    index_list[ hal_ll_module_id ]->mosi = mosi_index;
                                    index_list[ hal_ll_module_id ]->ss = sck_index;

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
    hal_ll_spi_master_hw_specifics_map[ module_index ].pins.sck  = _spi_sck_map[ index_list[ module_index ]->sck ].pin;
    hal_ll_spi_master_hw_specifics_map[ module_index ].pins.miso = _spi_miso_map[ index_list[ module_index ]->miso ].pin;
    hal_ll_spi_master_hw_specifics_map[ module_index ].pins.mosi = _spi_mosi_map[ index_list[ module_index ]->mosi ].pin;
    #if defined (__hal_ll_spi_master_subset_atmega__)
    hal_ll_spi_master_hw_specifics_map[ module_index ].pins.ss = _spi_ss_map[ index_list[ module_index ]->ss ].pin;
    #endif
}

static hal_ll_spi_master_hw_specifics_map_t *hal_ll_get_specifics( handle_t handle ) {
    uint8_t hal_ll_module_count = sizeof( hal_ll_module_state ) / ( sizeof( hal_ll_spi_master_handle_register_t ) );

    static uint8_t hal_ll_module_error = hal_ll_module_count;

    while ( hal_ll_module_count-- ) {
        if ( hal_ll_spi_master_get_base_from_hal_handle == hal_ll_spi_master_hw_specifics_map[ hal_ll_module_count ].base ) {
            return &hal_ll_spi_master_hw_specifics_map[ hal_ll_module_count ];
        }
    }

    // If NOK, return pointer to the last row of this map ( point to null pointer ).
    return &hal_ll_spi_master_hw_specifics_map[ hal_ll_module_error ];
}

static void hal_ll_spi_master_configure_pins( hal_ll_spi_master_hw_specifics_map_t *map, bool hal_ll_state ) {
    hal_ll_gpio_pin_t local_pin;

    if ( ( HAL_LL_PIN_NC != map->pins.sck ) && ( HAL_LL_PIN_NC != map->pins.miso ) && ( HAL_LL_PIN_NC != map->pins.mosi ) ) {
        if ( hal_ll_state ) {
            hal_ll_gpio_configure_pin( &local_pin, map->pins.sck, HAL_LL_GPIO_DIGITAL_OUTPUT );
            hal_ll_gpio_configure_pin( &local_pin, map->pins.miso, HAL_LL_GPIO_DIGITAL_INPUT );
            hal_ll_gpio_configure_pin( &local_pin, map->pins.mosi, HAL_LL_GPIO_DIGITAL_OUTPUT );
            #if defined (__hal_ll_spi_master_subset_atmega__)
            hal_ll_gpio_configure_pin( &local_pin, map->pins.ss, HAL_LL_GPIO_DIGITAL_OUTPUT );
            #endif
        } else {
            hal_ll_gpio_configure_pin( &local_pin, map->pins.sck, HAL_LL_GPIO_DIGITAL_INPUT );
            hal_ll_gpio_configure_pin( &local_pin, map->pins.miso, HAL_LL_GPIO_DIGITAL_INPUT );
            hal_ll_gpio_configure_pin( &local_pin, map->pins.mosi, HAL_LL_GPIO_DIGITAL_INPUT );
            #if defined (__hal_ll_spi_master_subset_atmega__)
            hal_ll_gpio_configure_pin( &local_pin, map->pins.ss, HAL_LL_GPIO_DIGITAL_INPUT );
            #endif
        }
    }
}

static void hal_ll_spi_master_set_clock( hal_ll_spi_master_hw_specifics_map_t *map, bool hal_ll_state ) {
    switch ( map->module_index ) {
        #ifdef SPI_MODULE_0
        #if defined (__hal_ll_spi_master_subset_atmega__)
        #ifdef HAL_LL_PRR0_REG_ADDRESS
        case hal_ll_spi_master_module_num( SPI_MODULE_0 ):
            ( true == hal_ll_state )?(clear_reg_bit( HAL_LL_PRR0_REG_ADDRESS, HAL_LL_PRR0_PRSPI0_BIT )):
            (set_reg_bit( HAL_LL_PRR0_REG_ADDRESS, HAL_LL_PRR0_PRSPI0_BIT ));
            break;
        #endif
        #elif defined (__hal_ll_spi_master_subset_atxmega__)
        #ifdef HAL_LL_PRPC_REG_ADDRESS
        case hal_ll_spi_master_module_num( SPI_MODULE_0 ):
            ( true == hal_ll_state )?(clear_reg_bit( HAL_LL_PRPC_REG_ADDRESS, HAL_LL_PRR_SPI_BIT )):(set_reg_bit( HAL_LL_PRPC_REG_ADDRESS, HAL_LL_PRR_SPI_BIT ));
            break;
        #endif
        #endif
        #endif

        #ifdef SPI_MODULE_1
        #if defined (__hal_ll_spi_master_subset_atmega__)
        #ifdef HAL_LL_PRR2_REG_ADDRESS
        case hal_ll_spi_master_module_num( SPI_MODULE_1 ):
            ( true == hal_ll_state )?(clear_reg_bit( HAL_LL_PRR2_REG_ADDRESS, HAL_LL_PRR1_PRSPI1_BIT )):
            (set_reg_bit( HAL_LL_PRR2_REG_ADDRESS, HAL_LL_PRR1_PRSPI1_BIT ));
            break;
        #endif
        #elif defined (__hal_ll_spi_master_subset_atxmega__)
        #ifdef HAL_LL_PRPD_REG_ADDRESS
        case hal_ll_spi_master_module_num( SPI_MODULE_1 ):
            ( true == hal_ll_state )?(clear_reg_bit( HAL_LL_PRPD_REG_ADDRESS, HAL_LL_PRR_SPI_BIT )):(set_reg_bit( HAL_LL_PRPD_REG_ADDRESS, HAL_LL_PRR_SPI_BIT ));
            break;
        #endif
        #endif
        #endif

        #ifdef SPI_MODULE_2
        #ifdef HAL_LL_PRPE_REG_ADDRESS
        #if defined (__hal_ll_spi_master_subset_atxmega__)
        case hal_ll_spi_master_module_num( SPI_MODULE_2 ):
            ( true == hal_ll_state )?(clear_reg_bit( HAL_LL_PRPE_REG_ADDRESS, HAL_LL_PRR_SPI_BIT )):(set_reg_bit( HAL_LL_PRPE_REG_ADDRESS, HAL_LL_PRR_SPI_BIT ));
            break;
        #endif
        #endif
        #endif

        #ifdef SPI_MODULE_3
        #if defined (__hal_ll_spi_master_subset_atxmega__)
        #ifdef HAL_LL_PRPF_REG_ADDRESS
        case hal_ll_spi_master_module_num( SPI_MODULE_3 ):
            ( true == hal_ll_state )?(clear_reg_bit( HAL_LL_PRPF_REG_ADDRESS, HAL_LL_PRR_SPI_BIT )):(set_reg_bit( HAL_LL_PRPF_REG_ADDRESS, HAL_LL_PRR_SPI_BIT ));
            break;
        #endif
        #endif
        #endif

        default:
            break;
    }
}

static void hal_ll_spi_master_set_baud_rate( hal_ll_spi_master_hw_specifics_map_t *map ) {
    // Get hardware register list for user-defined SPI pins.
    const hal_ll_spi_master_base_handle_t *hal_ll_hw_reg = hal_ll_spi_master_get_base_struct( map->base );

    bool prescaler_bit_0 = 0;
    bool prescaler_bit_1 = 0;
    bool prescaler_bit_2 = 0;

    // Calculate SPI speed via prescaler values that are eligible.
    ( ( _fosc / HAL_LL_SPI_MASTER_CLK_BAUD_RATE_DIVIDER_2 ) <= map->speed )?( prescaler_bit_0 = true, prescaler_bit_1 = false, prescaler_bit_2 = false ):
    ( ( ( _fosc / HAL_LL_SPI_MASTER_CLK_BAUD_RATE_DIVIDER_4 ) <= map->speed )?( prescaler_bit_0 = false, prescaler_bit_1 = false, prescaler_bit_2 = false ):
    ( ( ( _fosc / HAL_LL_SPI_MASTER_CLK_BAUD_RATE_DIVIDER_8 ) <= map->speed )?( prescaler_bit_0 = true, prescaler_bit_1 = true, prescaler_bit_2 = false ):
    ( ( ( _fosc / HAL_LL_SPI_MASTER_CLK_BAUD_RATE_DIVIDER_16 ) <= map->speed )?( prescaler_bit_0 = false, prescaler_bit_1 = true, prescaler_bit_2 = false ):
    ( ( ( _fosc / HAL_LL_SPI_MASTER_CLK_BAUD_RATE_DIVIDER_32 ) <= map->speed )?( prescaler_bit_0 = true, prescaler_bit_1 = false, prescaler_bit_2 = true ):
    ( ( ( _fosc / HAL_LL_SPI_MASTER_CLK_BAUD_RATE_DIVIDER_64 ) <= map->speed )?( prescaler_bit_0 = false, prescaler_bit_1 = false, prescaler_bit_2 = true ):
    ( ( ( _fosc / HAL_LL_SPI_MASTER_CLK_BAUD_RATE_DIVIDER_128 ) <= map->speed )?( prescaler_bit_0 = false, prescaler_bit_1 = true, prescaler_bit_2 = true ):
    ( prescaler_bit_0 = false, prescaler_bit_1 = true, prescaler_bit_2 = true ) ) ) ) ) ) );

    // Configure SPI prescaler bit 0 (SPI2X bit) appropriately.
    #if defined (__hal_ll_spi_master_subset_atmega__)
    ( prescaler_bit_0 )?( set_reg_bit( hal_ll_hw_reg->spi_spsr_reg_addr, HAL_LL_SPI_MASTER_CLK_BAUD_RATE_BIT_0 ) ):
    ( clear_reg_bit( hal_ll_hw_reg->spi_spsr_reg_addr, HAL_LL_SPI_MASTER_CLK_BAUD_RATE_BIT_0 ) );
    #elif defined (__hal_ll_spi_master_subset_atxmega__)
    ( prescaler_bit_0 )?( set_reg_bit( hal_ll_hw_reg->spi_spcr_reg_addr, HAL_LL_SPI_MASTER_CLK_BAUD_RATE_BIT_2 ) ):
    ( clear_reg_bit( hal_ll_hw_reg->spi_spsr_reg_addr, HAL_LL_SPI_MASTER_CLK_BAUD_RATE_BIT_0 ) );
    #endif

    // Configure SPI prescaler bit 1 (SPR0 bit) appropriately.
    ( prescaler_bit_1 )?( set_reg_bit( hal_ll_hw_reg->spi_spcr_reg_addr, HAL_LL_SPI_MASTER_CLK_BAUD_RATE_BIT_0 ) ):
    ( clear_reg_bit( hal_ll_hw_reg->spi_spcr_reg_addr, HAL_LL_SPI_MASTER_CLK_BAUD_RATE_BIT_0 ) );

    // Configure SPI prescaler bit 2 (SPR1 bit) appropriately.
    ( prescaler_bit_2 )?( set_reg_bit( hal_ll_hw_reg->spi_spcr_reg_addr, HAL_LL_SPI_MASTER_CLK_BAUD_RATE_BIT_1 ) ):
    ( clear_reg_bit( hal_ll_hw_reg->spi_spcr_reg_addr, HAL_LL_SPI_MASTER_CLK_BAUD_RATE_BIT_1 ) );
}

static void hal_ll_spi_master_hw_init( hal_ll_spi_master_hw_specifics_map_t *map ) {
    // Get hardware register list for user-defined SPI pins.
    const hal_ll_spi_master_base_handle_t *hal_ll_hw_reg = hal_ll_spi_master_get_base_struct( map->base );

    /* Clear SPI Control register:
     * - disable SPI interrupt;
     * - disable SPI module;
     * - set MSB to be transmitted first;
     * - set SPI Slave mode;
     * - set SPI mode 0;
     * - set SPI baud rate to be fosc/4.
    */
    clear_reg( hal_ll_hw_reg->spi_spcr_reg_addr );

    // Set SPI master mode.
    set_reg_bit( hal_ll_hw_reg->spi_spcr_reg_addr, HAL_LL_SPI_MASTER_MODE );

    /* Set Clock Polarity.
     * Choose whether idle state for the clock is high level (1) or low level (0).
     */
    if ( HAL_LL_SPI_MASTER_MODE_1 >= map->mode ) {
        clear_reg_bit( hal_ll_hw_reg->spi_spcr_reg_addr, HAL_LL_SPI_MASTER_CLK_POLARITY );
    } else {
        set_reg_bit( hal_ll_hw_reg->spi_spcr_reg_addr, HAL_LL_SPI_MASTER_CLK_POLARITY );
    }

    /* Set Clock Phase.
     * Choose whether transmit occurs on the transition from ACTIVE to IDLE ( 1 ), or vice versa ( 0 ).
     */
    if ( HAL_LL_SPI_MASTER_MODE_0 == map->mode || HAL_LL_SPI_MASTER_MODE_2 == map->mode ) {
        clear_reg_bit( hal_ll_hw_reg->spi_spcr_reg_addr, HAL_LL_SPI_MASTER_CLK_PHASE );
    } else {
        set_reg_bit( hal_ll_hw_reg->spi_spcr_reg_addr, HAL_LL_SPI_MASTER_CLK_PHASE );
    }

    // Configure SPI speed.
    hal_ll_spi_master_set_baud_rate( map );

    // Enable SPI module.
    set_reg_bit( hal_ll_hw_reg->spi_spcr_reg_addr, HAL_LL_SPI_MODULE_ENABLE );
}

static void hal_ll_spi_master_init( hal_ll_spi_master_hw_specifics_map_t *map ) {
    // Enable specific clock module.
    hal_ll_spi_master_set_clock ( map, true );

    // Configure pins which are going to be used for SPI communication.
    hal_ll_spi_master_configure_pins( map, true );

    // Finally, write user-defined settings into hardware registers.
    hal_ll_spi_master_hw_init( map );
}
// ------------------------------------------------------------------------- END
