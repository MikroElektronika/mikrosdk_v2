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
 * @brief SPI Master HAL LOW LEVEL layer implementation.
 */
#include "hal_ll_spi_master.h"
#include "hal_ll_spi_master_pin_map.h"
#include "hal_ll_gpio_port.h"
#include "hal_ll_rcc.h"

/*!< @brief Local handle list */
static volatile hal_ll_spi_master_handle_register_t hal_ll_module_state[ SPI_MODULE_COUNT ] = { ( handle_t * )NULL, ( handle_t * )NULL, false };

// ------------------------------------------------------------- PRIVATE MACROS

/*!< @brief Helper macro for getting hal_ll_module_state address */
#define hal_ll_spi_master_get_module_state_address      ( ( hal_ll_spi_master_handle_register_t * )*handle )
/*!< @brief Helper macro for getting module specific control register structure base address */
#define hal_ll_spi_master_get_handle                    ( hal_ll_spi_master_handle_register_t *)hal_ll_spi_master_get_module_state_address->hal_ll_spi_master_handle
/*!< @brief Helper macro for getting module specific control register structure */
#define hal_ll_spi_master_get_base_struct( _handle )    ( ( hal_ll_spi_master_base_handle_t * )_handle )
/*!< @brief Helper macro for getting module specific base address directly from HAL layer handle */
#define hal_ll_spi_master_get_base_from_hal_handle      ( ( hal_ll_spi_master_hw_specifics_map_t * )( ( hal_ll_spi_master_handle_register_t * )\
                                                        ( ( ( hal_ll_spi_master_handle_register_t * )( handle ) )->hal_ll_spi_master_handle ) )->hal_ll_spi_master_handle )->base

/*!< @brief SSI mode constants. */
#define HAL_LL_SPI_MASTER_CLK_POLARITY                  (6)
#define HAL_LL_SPI_MASTER_CLK_PHASE                     (7)

/*!< @brief SSI enable constants. */
#define HAL_LL_SPI_SSI_ENABLE                           (1)
#define HAL_LL_SPI0_ENABLE                              (0)
#define HAL_LL_SPI1_ENABLE                              (1)
#define HAL_LL_SPI2_ENABLE                              (2)
#define HAL_LL_SPI3_ENABLE                              (3)

/*!< @brief Status register bit check. */
#define HAL_LL_SPI1_FIFO_NOT_EMPTY                      (2)

/*!< @brief General constants. */
#define HAL_LL_SPI_CLK_POLARITY                         (1)
#define HAL_LL_SPI_CLK_PHASE                            (0)

/*!< @brief Default SPI Master bit-rate if no speed is set. */
#define HAL_LL_SPI_MASTER_SPEED_100K                    (100000)

/*!< @brief Maximum and minimum value for the clock speed. */
#define HAL_LL_SPI_MASTER_MAX_CLOCK_SPEED               (12000000)
#define HAL_LL_SPI_MASTER_MIN_CLOCK_SPEED               (2000000)

/*!< @brief Data transfer mode. */
#define HAL_LL_SPI_8_BIT                                (0x7)

/*!< @brief Alternate function config macros. */
#define HAL_LL_SPI_AF_CONFIG_SCK                        (GPIO_CFG_DIGITAL_OUTPUT | GPIO_CFG_ALT_FUNCTION)
#define HAL_LL_SPI_AF_CONFIG_MOSI                       (GPIO_CFG_DIGITAL_OUTPUT | GPIO_CFG_ALT_FUNCTION)
#define HAL_LL_SPI_AF_CONFIG_MISO                       (GPIO_CFG_DIGITAL_INPUT  | GPIO_CFG_ALT_FUNCTION)

/*!< @brief Helper macro for retrieving end-user's selected frequency. */
#define _fosc                                           (Get_Fosc_kHz()*1000)

// -------------------------------------------------------------- PRIVATE TYPES

/*!< @brief SPI Master hw specific error values. */
typedef enum {
    HAL_LL_SPI_MASTER_SUCCESS = 0,
    HAL_LL_SPI_MASTER_WRONG_PINS,
    HAL_LL_SPI_MASTER_MODULE_ERROR,

    HAL_LL_SPI_MASTER_ERROR = (-1)
} hal_ll_spi_master_err_t;

/*!< @brief SPI register structure. */
typedef struct {
    uint32_t cr0;           // QSSI module Control 0 Register.
    uint32_t cr1;           // QSSI module Control 1 Register.
    uint32_t dr;            // QSSI module Data read Register.
    uint32_t ssisr;         // QSSI module Status Register.
    uint32_t cpsdvsr;       // QSSI module Clock prescale divisor Register.
    uint32_t ssiim;         // QSSI module Interrupt Mask Register.
    uint32_t ssiris;        // QSSI module Raw Interrupt Status Register.
    uint32_t ssimis;        // QSSI module Masked Interrupt Status Register.
    uint32_t ssiicr;        // QSSI module Interrupt Clear Register.
    uint32_t ssidmactl;     // QSSI module DMA control Register.
    /* Commented out for memory optimization;
     * Uncomment if needed.
     */
    // uint32_t __unused1[998];// Reserved memory space.
    // uint32_t ssipp;         // QSSI module Peripheral properties Register.
    // uint32_t __unused2;     // Reserved memory space.
    // uint32_t ssicc;         // QSSI module Clock configuration Register.
    // uint32_t __unused3[6];  // Reserved memory space.
    // uint32_t ssipid4;       // QSSI module Peripheral ID 4.
    // uint32_t ssipid5;       // QSSI module Peripheral ID 5.
    // uint32_t ssipid6;       // QSSI module peripheral ID 6.
    // uint32_t ssipid7;       // QSSI module peripheral ID 7.
    // uint32_t ssipid0;       // QSSI module peripheral ID 0.
    // uint32_t ssipid1;       // QSSI module peripheral ID 1.
    // uint32_t ssipid2;       // QSSI module peripheral ID 2.
    // uint32_t ssipid3;       // QSSI module peripheral ID 3.
    // uint32_t ssipcd0;       // QSSI module prime cell ID 0.
    // uint32_t ssipcd1;       // QSSI prime cell ID 1.
    // uint32_t ssipcd2;       // QSSI prime cell ID 2.
    // uint32_t ssipcd3;       // QSSI prime cell ID 3.
} hal_ll_spi_master_base_handle_t;

/*!< @brief SPI Master hardware specific module values. */
typedef struct {
    uint8_t pin_miso;
    uint8_t pin_mosi;
    uint8_t pin_sck;
} hal_ll_spi_pin_id;

/*!< @brief SPI Master hardware specific structure. */
typedef struct {
    hal_ll_base_addr_t base;
    uint8_t module_index;
    hal_ll_spi_master_pins_t pins;
    uint8_t dummy_data;
    uint32_t speed;
    uint32_t hw_actual_speed;
    hal_ll_spi_master_mode_t mode;
} hal_ll_spi_master_hw_specifics_map_t;

// ------------------------------------------------------------------ VARIABLES

/*!< @brief Global handle variables used in functions. */
static volatile hal_ll_spi_master_handle_register_t *low_level_handle;
static volatile hal_ll_spi_master_hw_specifics_map_t *hal_ll_spi_master_hw_specifics_map_local;

/*!< @brief SPI Master hardware specific info. */
static hal_ll_spi_master_hw_specifics_map_t hal_ll_spi_master_hw_specifics_map[ SPI_MODULE_COUNT + 1 ] = {
    #ifdef SPI_MODULE_0
    { HAL_LL_SPI0_MASTER_BASE_ADDR, hal_ll_spi_master_module_num(SPI_MODULE_0), { HAL_LL_PIN_NC, 0, HAL_LL_PIN_NC, 0, HAL_LL_PIN_NC, 0 }, 0, HAL_LL_SPI_MASTER_SPEED_100K, 0, HAL_LL_SPI_MASTER_MODE_DEFAULT },
    #endif
    #ifdef SPI_MODULE_1
    { HAL_LL_SPI1_MASTER_BASE_ADDR, hal_ll_spi_master_module_num(SPI_MODULE_1), { HAL_LL_PIN_NC, 0, HAL_LL_PIN_NC, 0, HAL_LL_PIN_NC, 0 }, 0, HAL_LL_SPI_MASTER_SPEED_100K, 0, HAL_LL_SPI_MASTER_MODE_DEFAULT },
    #endif
    #ifdef SPI_MODULE_2
    { HAL_LL_SPI2_MASTER_BASE_ADDR, hal_ll_spi_master_module_num(SPI_MODULE_2), { HAL_LL_PIN_NC, 0, HAL_LL_PIN_NC, 0, HAL_LL_PIN_NC, 0 }, 0, HAL_LL_SPI_MASTER_SPEED_100K, 0, HAL_LL_SPI_MASTER_MODE_DEFAULT },
    #endif
    #ifdef SPI_MODULE_3
    { HAL_LL_SPI3_MASTER_BASE_ADDR, hal_ll_spi_master_module_num(SPI_MODULE_3), { HAL_LL_PIN_NC, 0, HAL_LL_PIN_NC, 0, HAL_LL_PIN_NC, 0 }, 0, HAL_LL_SPI_MASTER_SPEED_100K, 0, HAL_LL_SPI_MASTER_MODE_DEFAULT },
    #endif

    { HAL_LL_MODULE_ERROR, HAL_LL_MODULE_ERROR, { HAL_LL_PIN_NC, 0, HAL_LL_PIN_NC, 0, HAL_LL_PIN_NC, 0 }, 0, 0, 0, 0 }
};

// ---------------------------------------------- PRIVATE FUNCTION DECLARATIONS
/**
  * @brief  Check if pins are adequate.
  *
  * Checks SCK, MISO and MOSI pins the user has passed with pre-defined
  * pins in SCK, MISO and MOSI maps. Take into consideration that module
  * index numbers have to be the same for both pins.
  *
  * @param[in]  sck  - SCK pre-defined pin name.
  * @param[in]  miso - MISO pre-defined pin name.
  * @param[in]  mosi - MOSI pre-defined pin name.
  * @param[in]  *index_list - Index list address.
  * @param[out] *handle_map - Pointer to local handle list.
  * @return hal_ll_pin_name_t Module index based on pins.
  *
  * Returns pre-defined module index from pin maps, if pins
  * are adequate.
  */
static hal_ll_pin_name_t _hal_ll_spi_master_check_pins( hal_ll_pin_name_t sck_pin, hal_ll_pin_name_t miso_pin, hal_ll_pin_name_t mosi_pin, hal_ll_spi_pin_id *index_list, hal_ll_spi_master_handle_register_t *handle_map );

/**
  * @brief  Enable clock for SPI module on hardware level.
  *
  * Initializes SPI module clock on hardware level, based on beforehand
  * set configuration and module handler.
  *
  * @param[in]  *map - Object specific context handler.
  * @param[in]  hal_ll_state - True(enable clock)/False(disable clock).
  * @return None
  */
static void _hal_ll_spi_master_set_clock( hal_ll_spi_master_hw_specifics_map_t *map, bool hal_ll_state );

/**
  * @brief  Get local hardware specific map.
  *
  * Checks handle value and returns address of adequate
  * hal_ll_spi_master_hw_specifics_map array index.
  *
  * @param[in]  handle - Object specific context handler.
  * @return hal_ll_spi_master_hw_specifics_map_t Map address.
  *
  * Returns pre-defined map index address based on handle value,
  * if handle is adequate.
  */
static hal_ll_spi_master_hw_specifics_map_t *_hal_ll_get_specifics( handle_t handle );

/**
  * @brief  Full SPI Master module initialization procedure.
  *
  * Initializes SPI Master module on hardware level, based on beforehand
  * set configuration and module handler. Sets adequate pin alternate functions.
  * Initializes module clock.
  *
  * @param[in]  *map - Object specific context handler.
  * @return hal_ll_err_t Module specific values.
  *
  * Returns one of pre-defined values.
  * Take into consideration that this is hardware specific.
  */
static void _hal_ll_spi_master_init( hal_ll_spi_master_hw_specifics_map_t *map );

/**
  * @brief  Initialize hardware SPI module.
  *
  * @param[in]  *map - Object specific context handler.
  * @return None
  *
  * Returns one of pre-defined error values.
  * Take into consideration that this is hardware specific.
  */
static void _hal_ll_spi_master_hw_init( hal_ll_spi_master_hw_specifics_map_t *map );

/**
 * @brief Transfer function used in read and write bare metal.
 *
 * Performs a dummy read/write, and then the real transfer for
 * read and write.
 *
 * @param[in] *hal_ll_hw_register - Registers defined
 * in the program.
 * @param[in] data_buffer - Data which is going to be tranfered.
 * @return - None
 */
uint8_t _hal_ll_spi_master_transfer( hal_ll_spi_master_base_handle_t *hal_ll_hw_reg, uint8_t data_buffer );

/**
  * @brief  Perform a write on the SPI Master bus.
  *
  * Initializes SPI Master module on hardware level, if not initialized beforehand
  * and continues to perform a write operation on the bus.
  *
  * @param[in]  map - Object specific context handler.
  * @param[in]  *write_data_buffer - Pointer to data buffer.
  * @param[in]  write_data_length - Number of data to be written.
  * @return hal_ll_err_t Module specific error values.
  *
  * Returns one of pre-defined error values.
  * Take into consideration that this is hardware specific.
  */
static void _hal_ll_spi_master_write_bare_metal( hal_ll_spi_master_base_handle_t *hal_ll_hw_reg, uint8_t *read_data, size_t write_data_size );

/**
  * @brief  Perform a read on the SPI Master bus.
  *
  * Initializes SPI Master module on hardware level, if not initialized beforehand
  * and continues to perform a read operation on the bus.
  *
  * @param[in]  *map - Object specific context handler.
  * @param[in]  *read_data_buffer - Pointer to data buffer.
  * @param[in]  read_data_length - Number of data to be read.
  * @param[in]  dummy_data - Data required for read procedure.
  * @return hal_ll_err_t Module specific error values.
  */
static void _hal_ll_spi_master_read_bare_metal( hal_ll_spi_master_base_handle_t *hal_ll_hw_reg, uint8_t *read_data_buffer, size_t read_data_length, uint8_t dummy_data );

/**
  * @brief  Sets SPI Master pin alternate function state.
  *
  * Sets adequate value for alternate function settings.
  * This function must be called if SPI is to work.
  * Based on value of hal_ll_state, alternate functions can be
  * set or cleared.
  *
  * @param[in]  *map - Object specific context handler.
  * @param[in]  hal_ll_state - Init/De-init
  */
static void _hal_ll_spi_master_alternate_functions_set_state( hal_ll_spi_master_hw_specifics_map_t *map, bool hal_ll_state );

/**
  * @brief  Enables or disables SPI module 0 clock.
  * @param  hal_ll_state - True(enable clock)/False(disable clock).
  * @return none
  */
static inline void _hal_ll_spi_master0_set_clock ( bool hal_ll_state );

/**
  * @brief  Enables or disables SPI module 1 clock.
  * @param  hal_ll_state - True(enable clock)/False(disable clock).
  * @return none
  */
static inline void _hal_ll_spi_master1_set_clock ( bool hal_ll_state );

/**
  * @brief  Enables or disables SPI module 2 clock.
  * @param  hal_ll_state - True(enable clock)/False(disable clock).
  * @return none
  */
static inline void _hal_ll_spi_master2_set_clock ( bool hal_ll_state );

/**
  * @brief  Enables or disables SPI module 3 clock.
  * @param  hal_ll_state - True(enable clock)/False(disable clock).
  * @return none
  */
static inline void _hal_ll_spi_master3_set_clock ( bool hal_ll_state );

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
static void _hal_ll_spi_master_map_pins( uint8_t module_index, hal_ll_spi_pin_id *index_list );

/**
 * @brief  Configures SPI mode.
 *
 * Sets adequate Clock Polarity and Clock Phase settings
 * based on @mode parameter.
 *
 * @param[in] *hal_ll_hw_register - Registers defined
 * in the program.
 * @param[in]  mode - User-defined SPI mode property.
 *
 * @return  None
 */
static void _hal_ll_spi_master_mode_selection( hal_ll_spi_master_base_handle_t *hal_ll_hw_reg,  hal_ll_spi_master_mode_t mode );

// ------------------------------------------------ PUBLIC FUNCTION DEFINITIONS
hal_ll_err_t hal_ll_spi_master_register_handle( hal_ll_pin_name_t sck, hal_ll_pin_name_t miso, hal_ll_pin_name_t mosi, hal_ll_spi_master_handle_register_t *handle_map, uint8_t *hal_module_id ) {
    hal_ll_spi_pin_id index_list[ SPI_MODULE_COUNT ] = { HAL_LL_PIN_NC,HAL_LL_PIN_NC,HAL_LL_PIN_NC };
    uint16_t pin_check_result;

    // Check user-defined pins.
    if ( ( pin_check_result = _hal_ll_spi_master_check_pins( sck, miso, mosi, &index_list, handle_map ) ) == HAL_LL_PIN_NC ) {
        return HAL_LL_SPI_MASTER_WRONG_PINS;
    };

    // If user has come with the same SPI hardware module, and with the same pair of the pins, the pin mapping procedure
    // will not have to take a place; otherwise, clear af-s, map new pins, set af-s, and set init state to false.
    if ( ( hal_ll_spi_master_hw_specifics_map[ pin_check_result ].pins.sck.pin_name != sck   ) ||
         ( hal_ll_spi_master_hw_specifics_map[ pin_check_result ].pins.miso.pin_name != miso ) ||
         ( hal_ll_spi_master_hw_specifics_map[ pin_check_result ].pins.mosi.pin_name != mosi ) ) {

        _hal_ll_spi_master_alternate_functions_set_state( &hal_ll_spi_master_hw_specifics_map[ pin_check_result ], false );

        _hal_ll_spi_master_map_pins( pin_check_result, &index_list );

        _hal_ll_spi_master_alternate_functions_set_state( &hal_ll_spi_master_hw_specifics_map[ pin_check_result ], true );

        handle_map[ pin_check_result ].init_ll_state = false;
    }

    // Return id of the SPI module that is going to be used.
    *hal_module_id = pin_check_result;

    // Insert current module into hal_ll_module_state map.
    hal_ll_module_state[ pin_check_result ].hal_ll_spi_master_handle = ( handle_t * )&hal_ll_spi_master_hw_specifics_map[ pin_check_result ].base;

    // Return the same info about module one level up ( into the HAL level ).
    handle_map[ pin_check_result ].hal_ll_spi_master_handle = ( handle_t* )&hal_ll_module_state[ pin_check_result ].hal_ll_spi_master_handle;

    return HAL_LL_SPI_MASTER_SUCCESS;
}

hal_ll_err_t hal_ll_module_configure_spi( handle_t *handle ) {
    hal_ll_spi_master_hw_specifics_map_local = _hal_ll_get_specifics( hal_ll_spi_master_get_module_state_address );
    hal_ll_spi_master_handle_register_t *hal_handle = (hal_ll_spi_master_handle_register_t *)*handle;
    uint8_t pin_check_result = hal_ll_spi_master_hw_specifics_map_local->module_index;

    _hal_ll_spi_master_init( hal_ll_spi_master_hw_specifics_map_local );

    hal_ll_module_state[ pin_check_result ].hal_ll_spi_master_handle = ( handle_t * )&hal_ll_spi_master_hw_specifics_map[pin_check_result].base;
    hal_ll_module_state[ pin_check_result ].init_ll_state = true;
    hal_handle->init_ll_state = true;

    return HAL_LL_SPI_MASTER_SUCCESS;
}

void hal_ll_spi_master_set_default_write_data( handle_t *handle, uint8_t dummy_data ) {
    // Get appropriate hw specifics map.
    hal_ll_spi_master_hw_specifics_map_local = _hal_ll_get_specifics( hal_ll_spi_master_get_module_state_address );

    if( hal_ll_spi_master_hw_specifics_map_local->base != HAL_LL_MODULE_ERROR ) {
        hal_ll_spi_master_hw_specifics_map_local->dummy_data = dummy_data;
    }
}

hal_ll_err_t hal_ll_spi_master_write( handle_t *handle, uint8_t *write_data_buffer, size_t length_data ) {
    // Get low level HAL handle.
    low_level_handle = hal_ll_spi_master_get_handle;

    // Get appropriate hw specifics map.
    hal_ll_spi_master_hw_specifics_map_local = _hal_ll_get_specifics( hal_ll_spi_master_get_module_state_address );

    _hal_ll_spi_master_write_bare_metal( hal_ll_spi_master_hw_specifics_map_local->base, write_data_buffer, length_data );

    return HAL_LL_SPI_MASTER_SUCCESS;
}

hal_ll_err_t hal_ll_spi_master_read( handle_t *handle, uint8_t *read_data_buffer, size_t length_data ) {
    // Get low level HAL handle.
    low_level_handle = hal_ll_spi_master_get_handle;

    // Get appropriate hw specifics map.
    hal_ll_spi_master_hw_specifics_map_local = _hal_ll_get_specifics( hal_ll_spi_master_get_module_state_address );

    _hal_ll_spi_master_read_bare_metal( hal_ll_spi_master_hw_specifics_map_local->base, read_data_buffer, length_data, hal_ll_spi_master_hw_specifics_map_local->dummy_data );
    return HAL_LL_SPI_MASTER_SUCCESS;
}

hal_ll_err_t hal_ll_spi_master_write_then_read( handle_t *handle, uint8_t *write_data_buffer, size_t length_write_data, uint8_t *read_data_buffer, size_t length_read_data ) {
    // Get low level HAL handle.
    low_level_handle = hal_ll_spi_master_get_handle;

    // Get appropriate hw specifics map.
    hal_ll_spi_master_hw_specifics_map_local = _hal_ll_get_specifics( hal_ll_spi_master_get_module_state_address );

    _hal_ll_spi_master_write_bare_metal( hal_ll_spi_master_hw_specifics_map_local->base, write_data_buffer, length_write_data );

    _hal_ll_spi_master_read_bare_metal( hal_ll_spi_master_hw_specifics_map_local->base, read_data_buffer, length_read_data, hal_ll_spi_master_hw_specifics_map_local->dummy_data );

    return HAL_LL_SPI_MASTER_SUCCESS;
}

uint32_t hal_ll_spi_master_set_speed( handle_t *handle, uint32_t speed ) {
    // Get low level HAL handle.
    low_level_handle = hal_ll_spi_master_get_handle;

    // Get appropriate hw specifics map.
    hal_ll_spi_master_hw_specifics_map_local = _hal_ll_get_specifics( hal_ll_spi_master_get_module_state_address );

    low_level_handle->init_ll_state = false;

    // Insert user-defined baud rate into local map.
    hal_ll_spi_master_hw_specifics_map_local->speed = speed;

    // Init once again, but with updated SPI Master baud rate value.
    _hal_ll_spi_master_init( hal_ll_spi_master_hw_specifics_map_local );

    low_level_handle->init_ll_state = true;

    // Return value of the SPI Master baud rate value.
    return hal_ll_spi_master_hw_specifics_map_local->hw_actual_speed;
}

hal_ll_err_t hal_ll_spi_master_set_mode( handle_t *handle, hal_ll_spi_master_mode_t mode ) {
     // Get low level HAL handle.
    low_level_handle = hal_ll_spi_master_get_handle;

    // Get appropriate hw specifics map.
    hal_ll_spi_master_hw_specifics_map_local = _hal_ll_get_specifics( hal_ll_spi_master_get_module_state_address );

    low_level_handle->init_ll_state = false;

    // Insert user-defined mode into local map.
    hal_ll_spi_master_hw_specifics_map_local->mode = mode;

    // Init once again, but with updated SPI Master mode value.
    _hal_ll_spi_master_init( hal_ll_spi_master_hw_specifics_map_local );

    low_level_handle->init_ll_state = true;

    return HAL_LL_SPI_MASTER_SUCCESS;
}

void hal_ll_spi_master_close( handle_t* handle ) {
    low_level_handle = hal_ll_spi_master_get_handle;
    hal_ll_spi_master_hw_specifics_map_local = _hal_ll_get_specifics( hal_ll_spi_master_get_module_state_address );

    if( low_level_handle->hal_ll_spi_master_handle != NULL ) {
        low_level_handle->hal_ll_spi_master_handle  = NULL;
        low_level_handle->hal_drv_spi_master_handle = NULL;

        low_level_handle->init_ll_state = false;

        hal_ll_spi_master_hw_specifics_map_local->mode = HAL_LL_SPI_MASTER_MODE_DEFAULT;
        hal_ll_spi_master_hw_specifics_map_local->speed = HAL_LL_SPI_MASTER_SPEED_100K;
        hal_ll_spi_master_hw_specifics_map_local->dummy_data = 0;
        hal_ll_spi_master_hw_specifics_map_local->hw_actual_speed = 0;

        _hal_ll_spi_master_set_clock( hal_ll_spi_master_hw_specifics_map_local, true );
        _hal_ll_spi_master_alternate_functions_set_state( hal_ll_spi_master_hw_specifics_map_local, false );
        _hal_ll_spi_master_set_clock( hal_ll_spi_master_hw_specifics_map_local, false );

        hal_ll_spi_master_hw_specifics_map_local->pins.sck.pin_name = HAL_LL_PIN_NC;
        hal_ll_spi_master_hw_specifics_map_local->pins.miso.pin_name = HAL_LL_PIN_NC;
        hal_ll_spi_master_hw_specifics_map_local->pins.mosi.pin_name = HAL_LL_PIN_NC;
        hal_ll_spi_master_hw_specifics_map_local->pins.sck.pin_af = 0;
        hal_ll_spi_master_hw_specifics_map_local->pins.miso.pin_af = 0;
        hal_ll_spi_master_hw_specifics_map_local->pins.mosi.pin_af = 0;
    }
}

// ----------------------------------------------- PRIVATE FUNCTION DEFINITIONS

static hal_ll_pin_name_t _hal_ll_spi_master_check_pins( hal_ll_pin_name_t sck_pin, hal_ll_pin_name_t miso_pin, hal_ll_pin_name_t mosi_pin, hal_ll_spi_pin_id *index_list, hal_ll_spi_master_handle_register_t *handle_map ) {
    static uint16_t sck_map_size  = ( sizeof( _spi_sck_map ) )  / ( sizeof( hal_ll_spi_master_pin_map_t ) );
    static uint16_t miso_map_size = ( sizeof( _spi_miso_map ) ) / ( sizeof( hal_ll_spi_master_pin_map_t ) );
    static uint16_t mosi_map_size = ( sizeof( _spi_mosi_map ) ) / ( sizeof( hal_ll_spi_master_pin_map_t ) );

    uint8_t hal_ll_module_id = 0;
    uint8_t index_counter = 0;
    uint16_t miso_index;
    uint16_t mosi_index;
    uint16_t sck_index;

    if ( (HAL_LL_PIN_NC == sck_pin) || (HAL_LL_PIN_NC == miso_pin) || (HAL_LL_PIN_NC == mosi_pin) ) {
        return HAL_LL_PIN_NC;
    }

    // Check pins from the specific pin maps with the user defined pins.
    for( sck_index = 0; sck_index < sck_map_size; sck_index++ ) {
        if( _spi_sck_map[ sck_index ].pin == sck_pin ) {
            for( miso_index = 0; miso_index < miso_map_size; miso_index++ ) {
                if( _spi_miso_map[ miso_index ].pin == miso_pin ) {
                    if( _spi_sck_map[ sck_index ].module_index == _spi_miso_map[ miso_index ].module_index ) {
                        for( mosi_index = 0; mosi_index < mosi_map_size; mosi_index++ ) {
                            if( _spi_mosi_map[ mosi_index ].pin == mosi_pin ) {
                                if( _spi_sck_map[ sck_index ].module_index == _spi_mosi_map[ mosi_index ].module_index ) {
                                    hal_ll_module_id = _spi_sck_map[ sck_index ].module_index;

                                    index_list[ hal_ll_module_id ].pin_sck  = sck_index;
                                    index_list[ hal_ll_module_id ].pin_miso = miso_index;
                                    index_list[ hal_ll_module_id ].pin_mosi = mosi_index;

                                    if ( NULL == handle_map[hal_ll_module_id].hal_drv_spi_master_handle ) {
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

    return HAL_LL_SPI_MASTER_SUCCESS;
}

static hal_ll_spi_master_hw_specifics_map_t *_hal_ll_get_specifics( handle_t handle ) {
    uint8_t hal_ll_module_count = sizeof( hal_ll_module_state ) / ( sizeof( hal_ll_spi_master_handle_register_t ) );
    static uint8_t hal_ll_module_error = sizeof( hal_ll_module_state ) / ( sizeof( hal_ll_spi_master_handle_register_t ) );

    while ( hal_ll_module_count-- ) {
        if ( hal_ll_spi_master_get_base_from_hal_handle == hal_ll_spi_master_hw_specifics_map[ hal_ll_module_count ].base ) {
            return &hal_ll_spi_master_hw_specifics_map[ hal_ll_module_count ];
        }
    }

    // If NOK, return pointer to the last row of this map ( point to null pointer ).
    return &hal_ll_spi_master_hw_specifics_map[ hal_ll_module_error ];
}

static void _hal_ll_spi_master_map_pins( uint8_t module_index, hal_ll_spi_pin_id *index_list ) {
    // If every single pin is OK, insert them into this new map, and use this map in all low level functions.
    hal_ll_spi_master_hw_specifics_map[ module_index ].pins.sck.pin_name = _spi_sck_map[ index_list[ module_index ].pin_sck ].pin;
    hal_ll_spi_master_hw_specifics_map[ module_index ].pins.miso.pin_name = _spi_miso_map[ index_list[ module_index ].pin_miso ].pin;
    hal_ll_spi_master_hw_specifics_map[ module_index ].pins.mosi.pin_name = _spi_mosi_map[ index_list[ module_index ].pin_mosi ].pin;

    //SCK, MISO and MOSI pin could have different alternate function settings, hence save all of the AF-s.
    hal_ll_spi_master_hw_specifics_map[ module_index ].pins.sck.pin_af = _spi_sck_map[ index_list[ module_index ].pin_sck ].af;
    hal_ll_spi_master_hw_specifics_map[ module_index ].pins.miso.pin_af = _spi_miso_map[ index_list[ module_index ].pin_miso ].af;
    hal_ll_spi_master_hw_specifics_map[ module_index ].pins.mosi.pin_af = _spi_mosi_map[ index_list[ module_index ].pin_mosi ].af;
}

static void _hal_ll_spi_master_alternate_functions_set_state( hal_ll_spi_master_hw_specifics_map_t *map, bool hal_ll_state ) {
    module_struct module;

    if ( ( map->pins.sck.pin_name != HAL_LL_PIN_NC ) && ( map->pins.miso.pin_name != HAL_LL_PIN_NC ) && ( map->pins.mosi.pin_name != HAL_LL_PIN_NC ) ) {
        module.pins[ 0 ] = VALUE( map->pins.sck.pin_name, map->pins.sck.pin_af );
        module.pins[ 1 ] = VALUE( map->pins.mosi.pin_name, map->pins.mosi.pin_af );
        module.pins[ 2 ] = VALUE( map->pins.miso.pin_name, map->pins.miso.pin_af );
        module.pins[ 3 ] = GPIO_MODULE_STRUCT_END;

        module.configs[ 0 ] = HAL_LL_SPI_AF_CONFIG_SCK;
        module.configs[ 1 ] = HAL_LL_SPI_AF_CONFIG_MOSI;
        module.configs[ 2 ] = HAL_LL_SPI_AF_CONFIG_MISO;
        module.configs[ 3 ] = GPIO_MODULE_STRUCT_END;

        hal_ll_gpio_module_struct_init( &module, hal_ll_state );
    }
}

static void _hal_ll_spi_master_set_clock( hal_ll_spi_master_hw_specifics_map_t *map, bool hal_ll_state ) {
    switch( map->module_index ) {
        #if defined ( SPI_MODULE_0 )
        case ( hal_ll_spi_master_module_num( SPI_MODULE_0 ) ):
            _hal_ll_spi_master0_set_clock( hal_ll_state );
            break;
        #endif
        #if defined ( SPI_MODULE_1 )
        case ( hal_ll_spi_master_module_num( SPI_MODULE_1 ) ):
            _hal_ll_spi_master1_set_clock( hal_ll_state );
            break;
        #endif
        #if defined ( SPI_MODULE_2 )
        case ( hal_ll_spi_master_module_num( SPI_MODULE_2 ) ):
            _hal_ll_spi_master2_set_clock( hal_ll_state );
            break;
        #endif
        #if defined ( SPI_MODULE_3 )
        case ( hal_ll_spi_master_module_num( SPI_MODULE_3 ) ):
            _hal_ll_spi_master3_set_clock( hal_ll_state );
            break;
        #endif

        default:
            break;
    }
}

static inline void _hal_ll_spi_master0_set_clock ( bool hal_ll_state ) {
    // Check hal_ll_state, and set the bit for the clock
    hal_ll_state ? set_reg_bit( _SYSCTL_RCGCSSI, HAL_LL_SPI0_ENABLE ) : clear_reg_bit( _SYSCTL_RCGCSSI, HAL_LL_SPI0_ENABLE );
}

static inline void _hal_ll_spi_master1_set_clock( bool hal_ll_state ) {
    // Check hal_ll_state, and set the bit for the clock
    hal_ll_state ? set_reg_bit( _SYSCTL_RCGCSSI, HAL_LL_SPI1_ENABLE ) : clear_reg_bit( _SYSCTL_RCGCSSI, HAL_LL_SPI1_ENABLE );
}

static inline void _hal_ll_spi_master2_set_clock( bool hal_ll_state ) {
    // Check hal_ll_state, and set the bit for the clock
    hal_ll_state ? set_reg_bit( _SYSCTL_RCGCSSI, HAL_LL_SPI2_ENABLE ) : clear_reg_bit( _SYSCTL_RCGCSSI, HAL_LL_SPI2_ENABLE );
}

static inline void _hal_ll_spi_master3_set_clock( bool hal_ll_state ) {
    // Check hal_ll_state, and set the bit for the clock
    hal_ll_state ? set_reg_bit( _SYSCTL_RCGCSSI, HAL_LL_SPI3_ENABLE ) : clear_reg_bit( _SYSCTL_RCGCSSI, HAL_LL_SPI3_ENABLE );
}

uint8_t _hal_ll_spi_master_transfer( hal_ll_spi_master_base_handle_t *hal_ll_hw_reg, uint8_t data_buffer ) {
    // Perform a dummy transfer.
    volatile uint8_t temp = hal_ll_hw_reg->dr;

    hal_ll_hw_reg->dr = data_buffer;

    // Wait for the transfer to finish.
    while( !( check_reg_bit ( &( hal_ll_hw_reg->ssisr ), HAL_LL_SPI1_FIFO_NOT_EMPTY ) ) );

    return hal_ll_hw_reg->dr;
}

static void _hal_ll_spi_master_write_bare_metal( hal_ll_spi_master_base_handle_t *hal_ll_hw_reg, uint8_t *write_data_buffer, size_t write_data_length ) {
    size_t transfer_counter = 0;

    for ( transfer_counter = 0; transfer_counter < write_data_length; transfer_counter++ ) {
        _hal_ll_spi_master_transfer( hal_ll_hw_reg, write_data_buffer[ transfer_counter ] );
    }
}

static void _hal_ll_spi_master_read_bare_metal( hal_ll_spi_master_base_handle_t *hal_ll_hw_reg, uint8_t *read_data_buffer, size_t read_data_length, uint8_t dummy_data ) {
    size_t transfer_counter = 0;

    for( transfer_counter = 0; transfer_counter < read_data_length; transfer_counter++ ) {
        read_data_buffer[ transfer_counter ] = _hal_ll_spi_master_transfer( hal_ll_hw_reg, dummy_data );
    }
}

static void _hal_ll_spi_master_mode_selection( hal_ll_spi_master_base_handle_t *hal_ll_hw_reg,  hal_ll_spi_master_mode_t mode ) {
    // Clock Polarity configuration.
    if ( mode <= HAL_LL_SPI_MASTER_MODE_1 ) {
        // Idle state for the SPI clock is low level (0).
        clear_reg_bit( &(hal_ll_hw_reg->cr0), HAL_LL_SPI_MASTER_CLK_POLARITY );
    } else {
        // Idle state for the SPI clock is high level (1).
        set_reg_bit( &(hal_ll_hw_reg->cr0), HAL_LL_SPI_MASTER_CLK_POLARITY );
    }

    // Clock Phase configuration.
    if ( mode == HAL_LL_SPI_MASTER_MODE_0 || mode == HAL_LL_SPI_MASTER_MODE_2 ) {
        // Data is captured on the 1st clock edge transition.
        clear_reg_bit( &(hal_ll_hw_reg->cr0), HAL_LL_SPI_MASTER_CLK_PHASE );
    } else {
        // Data is captured on the 2nd clock edge transition.
        set_reg_bit( &(hal_ll_hw_reg->cr0), HAL_LL_SPI_MASTER_CLK_PHASE );
    }
}

static void _hal_ll_spi_master_hw_init( hal_ll_spi_master_hw_specifics_map_t *map ) {
    uint32_t bitrate;
    uint32_t scaler = 0;
    uint32_t prescaler = 0;
    uint32_t min_diff = 0xFFFFFFFF;
    uint16_t scaler_counter, prescaler_value;
    bool appropriate_baud_rate_found = false;

    hal_ll_spi_master_base_handle_t *hal_ll_hw_reg = ( hal_ll_spi_master_base_handle_t* ) map->base;

    // Set 8bit transfer mode.
    hal_ll_hw_reg->cr0 = HAL_LL_SPI_8_BIT;

    // SPI Mode selection process.
    _hal_ll_spi_master_mode_selection( map->base, map->mode );

    //Check if the user clock values are OK.
    if( map->speed > HAL_LL_SPI_MASTER_MAX_CLOCK_SPEED ) {
        map->speed = HAL_LL_SPI_MASTER_MAX_CLOCK_SPEED;
    }

    if( map->speed < HAL_LL_SPI_MASTER_MIN_CLOCK_SPEED ) {
        map->speed = HAL_LL_SPI_MASTER_MIN_CLOCK_SPEED;
    }

    for ( scaler_counter = 2; scaler_counter < 255; scaler_counter += 2 ) {
        for ( prescaler_value = 0; prescaler_value < 256; prescaler_value++ ) {
            bitrate = _fosc / ( scaler_counter * ( 1 + prescaler_value ) );
            if ( map->speed >= bitrate ) {
                uint32_t diff  = map->speed - bitrate;
                if ( min_diff > diff ) {
                    min_diff = diff;
                    prescaler = prescaler_value;
                    scaler = scaler_counter;
                    appropriate_baud_rate_found = true;
                    break;
                }
            }
        }

        if( appropriate_baud_rate_found ) {
            break;
        }
    }
    // Saving scale and prescale values.
    hal_ll_hw_reg->cr0 |= ( prescaler << 8 );
    hal_ll_hw_reg->cpsdvsr = scaler;

    // Enable the SSI module.
    set_reg_bit( &( hal_ll_hw_reg->cr1 ), HAL_LL_SPI_SSI_ENABLE );

    // Memorize final hardware SPI speed.
    hal_ll_spi_master_hw_specifics_map->hw_actual_speed = bitrate;
}

static void _hal_ll_spi_master_init( hal_ll_spi_master_hw_specifics_map_t *map ) {
    //Enable specific clock module.
    _hal_ll_spi_master_set_clock( map, true );

    //Enable specific alternate functions.
    _hal_ll_spi_master_alternate_functions_set_state( map, true );

    //Finally, write user-defined settings into hardware registers.
    _hal_ll_spi_master_hw_init( map );
}

// ------------------------------------------------------------------------- END
