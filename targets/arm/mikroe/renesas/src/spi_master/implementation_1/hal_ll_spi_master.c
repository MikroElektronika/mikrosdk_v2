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
 * @file  hal_ll_spi_master.c
 * @brief SPI Master HAL LOW LEVEL layer implementation.
 */
#include "hal_ll_spi_master.h"
#include "hal_ll_spi_master_pin_map.h"
#include "hal_ll_gpio_port.h"
#include "hal_ll_mstpcr.h"
#include "mcu.h"

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

// -------------------------------------------------------------- PRIVATE TYPES

#define HAL_LL_SPI_SPSR_SPTEF (5)
#define HAL_LL_SPI_SPSR_SPRF (7)

#define HAL_LL_SPI_SPDCR_SPBYT (6)

#define HAL_LL_SPI_SPCR2_SCKASE (4)

#define HAL_LL_SPI_SPCMD0_SPNDEN_MASK (1UL << 13)
#define HAL_LL_SPI_SPCMD0_SLNDEN_MASK (1UL << 14)
#define HAL_LL_SPI_SPCMD0_SCKDEN_MASK (1UL << 15)
#define HAL_LL_SPI_SPCMD0_SPB_8BIT_MASK (7UL << 8)
#define HAL_LL_SPI_SPCMD0_BRDV_MASK (3UL << 2)
#define HAL_LL_SPI_SPCMD0_BRDV (2)
#define HAL_LL_SPI_SPCMD0_CPHA (0)
#define HAL_LL_SPI_SPCMD0_CPOL (1)

#define HAL_LL_SPI_SPCR_MSTR_MASK (1UL << 3)
#define HAL_LL_SPI_SPCR_SPE_MASK (1UL << 6)


/*!< @brief Default SPI Master bit-rate if no speed is set */
#define HAL_LL_SPI_MASTER_SPEED_100K 100000

/*!< @brief SPI Master hw specific error values. */
typedef enum {
    HAL_LL_SPI_MASTER_SUCCESS = 0,
    HAL_LL_SPI_MASTER_WRONG_PINS,
    HAL_LL_SPI_MASTER_MODULE_ERROR,

    HAL_LL_SPI_MASTER_ERROR = (-1)
} hal_ll_spi_master_err_t;

/*!< @brief SPI register structure. */
typedef struct {
    uint8_t spcr;
    uint8_t sslp;
    uint8_t sppcr;
    uint8_t spsr;
    union {
        uint32_t spdr;
        uint16_t spdr_ha;
        uint8_t spdr_by;
    };
    uint8_t spscr;
    uint8_t spssr;
    uint8_t spbr;
    uint8_t spdcr;
    uint8_t spckd;
    uint8_t sslnd;
    uint8_t spnd;
    uint8_t spcr2;
    uint16_t spcmd0;
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
    { HAL_LL_SPI0_MASTER_BASE_ADDR, hal_ll_spi_master_module_num(SPI_MODULE_0),
     { HAL_LL_PIN_NC, 0, HAL_LL_PIN_NC, 0, HAL_LL_PIN_NC, 0 }, 0,
      HAL_LL_SPI_MASTER_SPEED_100K, 0, HAL_LL_SPI_MASTER_MODE_DEFAULT },
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
static hal_ll_pin_name_t hal_ll_spi_master_check_pins( hal_ll_pin_name_t sck_pin,
                                                       hal_ll_pin_name_t miso_pin,
                                                       hal_ll_pin_name_t mosi_pin,
                                                       hal_ll_spi_pin_id *index_list,
                                                       hal_ll_spi_master_handle_register_t *handle_map );

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
static void hal_ll_spi_master_module_enable( hal_ll_spi_master_hw_specifics_map_t *map, bool hal_ll_state );

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
static hal_ll_spi_master_hw_specifics_map_t *hal_ll_get_specifics( handle_t handle );

// TODO
static void hal_ll_spi_master_set_bit_rate( hal_ll_spi_master_hw_specifics_map_t *map );

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
static void hal_ll_spi_master_init( hal_ll_spi_master_hw_specifics_map_t *map );

/**
  * @brief  Initialize hardware SPI module.
  *
  * @param[in]  *map - Object specific context handler.
  * @return None
  *
  * Returns one of pre-defined error values.
  * Take into consideration that this is hardware specific.
  */
static void hal_ll_spi_master_hw_init( hal_ll_spi_master_hw_specifics_map_t *map );

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
static void hal_ll_spi_master_write_bare_metal( hal_ll_spi_master_base_handle_t *hal_ll_hw_reg,
                                                uint8_t *read_data,
                                                size_t write_data_size );

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
static void hal_ll_spi_master_read_bare_metal( hal_ll_spi_master_base_handle_t *hal_ll_hw_reg,
                                               uint8_t *read_data_buffer,
                                               size_t read_data_length,
                                               uint8_t dummy_data );

/**
  * @brief  Perform a simultaneous write and read on the SPI Master bus.
  *
  * Function performs a full-duplex SPI transfer. Each written byte results in
  * a received byte which is optionally stored in the read buffer.
  * If the write buffer is NULL, the configured dummy byte will be transmitted.
  * If the read buffer is NULL, the received data will be discarded.
  *
  * @param[in]  *map - Object specific context handler.
  * @param[in]  *write_data_buffer - Pointer to write data buffer.
  *                                  If NULL, dummy data will be used.
  * @param[out] *read_data_buffer - Pointer to read data buffer.
  *                                 If NULL, received data will be discarded.
  * @param[in]  data_length - Number of bytes to be transferred.
  *
  * @note TX FIFO is flushed and re-enabled on each byte transfer to ensure proper behavior.
  *       This implementation uses polling and is blocking.
  */
static void hal_ll_spi_master_transfer_bare_metal( hal_ll_spi_master_base_handle_t *hal_ll_hw_reg,
                                                   uint8_t *write_data_buffer,
                                                   uint8_t *read_data_buffer,
                                                   size_t data_length );
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
static void hal_ll_spi_master_alternate_functions_set_state( hal_ll_spi_master_hw_specifics_map_t *map,
                                                             bool hal_ll_state );

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
static void hal_ll_spi_master_map_pins( uint8_t module_index, hal_ll_spi_pin_id *index_list );

// ------------------------------------------------ PUBLIC FUNCTION DEFINITIONS
hal_ll_err_t hal_ll_spi_master_register_handle( hal_ll_pin_name_t sck, hal_ll_pin_name_t miso, hal_ll_pin_name_t mosi,
                                                hal_ll_spi_master_handle_register_t *handle_map,
                                                uint8_t *hal_module_id ) {
    hal_ll_spi_pin_id index_list[ SPI_MODULE_COUNT ] = { HAL_LL_PIN_NC,HAL_LL_PIN_NC,HAL_LL_PIN_NC };
    uint16_t pin_check_result;

    // Check user-defined pins.
    if ( ( pin_check_result = hal_ll_spi_master_check_pins( sck, miso, mosi, &index_list, handle_map ) ) == HAL_LL_PIN_NC ) {
        return HAL_LL_SPI_MASTER_WRONG_PINS;
    };

    // If user has come with the same SPI hardware module, and with the same pair of the pins, the pin mapping procedure
    // will not have to take a place; otherwise, clear af-s, map new pins, set af-s, and set init state to false.
    if ( ( hal_ll_spi_master_hw_specifics_map[ pin_check_result ].pins.sck.pin_name != sck   ) ||
         ( hal_ll_spi_master_hw_specifics_map[ pin_check_result ].pins.miso.pin_name != miso ) ||
         ( hal_ll_spi_master_hw_specifics_map[ pin_check_result ].pins.mosi.pin_name != mosi ) ) {

        hal_ll_spi_master_alternate_functions_set_state( &hal_ll_spi_master_hw_specifics_map[ pin_check_result ], false );

        hal_ll_spi_master_map_pins( pin_check_result, &index_list );

        hal_ll_spi_master_alternate_functions_set_state( &hal_ll_spi_master_hw_specifics_map[ pin_check_result ], true );

        handle_map[ pin_check_result ].init_ll_state = false;
    }

    // Return id of the SPI module that is going to be used.
    *hal_module_id = pin_check_result;

    // Insert current module into hal_ll_module_state map.
    hal_ll_module_state[ pin_check_result ].hal_ll_spi_master_handle =
                                            ( handle_t * )&hal_ll_spi_master_hw_specifics_map[ pin_check_result ].base;

    // Return the same info about module one level up ( into the HAL level ).
    handle_map[ pin_check_result ].hal_ll_spi_master_handle =
                                   ( handle_t* )&hal_ll_module_state[ pin_check_result ].hal_ll_spi_master_handle;

    return HAL_LL_SPI_MASTER_SUCCESS;
}

hal_ll_err_t hal_ll_module_configure_spi( handle_t *handle ) {
    hal_ll_spi_master_hw_specifics_map_local = hal_ll_get_specifics( hal_ll_spi_master_get_module_state_address );
    hal_ll_spi_master_handle_register_t *hal_handle = (hal_ll_spi_master_handle_register_t *)*handle;
    uint8_t pin_check_result = hal_ll_spi_master_hw_specifics_map_local->module_index;

    hal_ll_spi_master_init( hal_ll_spi_master_hw_specifics_map_local );

    hal_ll_module_state[ pin_check_result ].hal_ll_spi_master_handle =
                                            ( handle_t * )&hal_ll_spi_master_hw_specifics_map[pin_check_result].base;
    hal_ll_module_state[ pin_check_result ].init_ll_state = true;
    hal_handle->init_ll_state = true;

    return HAL_LL_SPI_MASTER_SUCCESS;
}

void hal_ll_spi_master_set_default_write_data( handle_t *handle, uint8_t dummy_data ) {
    // Get appropriate hw specifics map.
    hal_ll_spi_master_hw_specifics_map_local = hal_ll_get_specifics( hal_ll_spi_master_get_module_state_address );

    if( hal_ll_spi_master_hw_specifics_map_local->base != HAL_LL_MODULE_ERROR ) {
        hal_ll_spi_master_hw_specifics_map_local->dummy_data = dummy_data;
    }
}

hal_ll_err_t hal_ll_spi_master_write( handle_t *handle, uint8_t *write_data_buffer, size_t length_data ) {
    // Get low level HAL handle.
    low_level_handle = hal_ll_spi_master_get_handle;

    // Get appropriate hw specifics map.
    hal_ll_spi_master_hw_specifics_map_local = hal_ll_get_specifics( hal_ll_spi_master_get_module_state_address );

    hal_ll_spi_master_write_bare_metal( hal_ll_spi_master_hw_specifics_map_local->base,
                                        write_data_buffer,
                                        length_data );

    return HAL_LL_SPI_MASTER_SUCCESS;
}

hal_ll_err_t hal_ll_spi_master_read( handle_t *handle, uint8_t *read_data_buffer, size_t length_data ) {
    // Get low level HAL handle.
    low_level_handle = hal_ll_spi_master_get_handle;

    // Get appropriate hw specifics map.
    hal_ll_spi_master_hw_specifics_map_local = hal_ll_get_specifics( hal_ll_spi_master_get_module_state_address );

    hal_ll_spi_master_read_bare_metal( hal_ll_spi_master_hw_specifics_map_local->base,
                                       read_data_buffer, length_data,
                                       hal_ll_spi_master_hw_specifics_map_local->dummy_data );

    return HAL_LL_SPI_MASTER_SUCCESS;
}

hal_ll_err_t hal_ll_spi_master_write_then_read( handle_t *handle,
                                                uint8_t *write_data_buffer,
                                                size_t length_write_data,
                                                uint8_t *read_data_buffer,
                                                size_t length_read_data ) {
    // Get low level HAL handle.
    low_level_handle = hal_ll_spi_master_get_handle;

    // Get appropriate hw specifics map.
    hal_ll_spi_master_hw_specifics_map_local = hal_ll_get_specifics( hal_ll_spi_master_get_module_state_address );

    hal_ll_spi_master_write_bare_metal( hal_ll_spi_master_hw_specifics_map_local->base,
                                        write_data_buffer,
                                        length_write_data );

    hal_ll_spi_master_read_bare_metal( hal_ll_spi_master_hw_specifics_map_local->base,
                                       read_data_buffer,
                                       length_read_data,
                                       hal_ll_spi_master_hw_specifics_map_local->dummy_data );

    return HAL_LL_SPI_MASTER_SUCCESS;
}

hal_ll_err_t hal_ll_spi_master_transfer(handle_t *handle,
                                        uint8_t *write_data_buffer,
                                        uint8_t *read_data_buffer,
                                        size_t data_length) {
    low_level_handle = hal_ll_spi_master_get_handle;
    hal_ll_spi_master_hw_specifics_map_local = hal_ll_get_specifics(hal_ll_spi_master_get_module_state_address);

    if (NULL == low_level_handle->hal_ll_spi_master_handle) {
        return HAL_LL_SPI_MASTER_MODULE_ERROR;
    }

    hal_ll_spi_master_transfer_bare_metal( hal_ll_spi_master_hw_specifics_map_local->base,
                                           write_data_buffer, read_data_buffer, data_length );

    if (!hal_ll_spi_master_hw_specifics_map_local || !data_length) {
        return HAL_LL_SPI_MASTER_MODULE_ERROR;
    }

    return HAL_LL_SPI_MASTER_SUCCESS;
}

uint32_t hal_ll_spi_master_set_speed( handle_t *handle, uint32_t speed ) {
    // Get low level HAL handle.
    low_level_handle = hal_ll_spi_master_get_handle;

    // Get appropriate hw specifics map.
    hal_ll_spi_master_hw_specifics_map_local =
            hal_ll_get_specifics( hal_ll_spi_master_get_module_state_address );

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
    hal_ll_spi_master_hw_specifics_map_local =
            hal_ll_get_specifics( hal_ll_spi_master_get_module_state_address );

    low_level_handle->init_ll_state = false;

    // Insert user-defined mode into local map.
    hal_ll_spi_master_hw_specifics_map_local->mode = mode;

    // Init once again, but with updated SPI Master mode value.
    hal_ll_spi_master_init( hal_ll_spi_master_hw_specifics_map_local );

    low_level_handle->init_ll_state = true;

    return HAL_LL_SPI_MASTER_SUCCESS;
}

void hal_ll_spi_master_close( handle_t* handle ) {
    low_level_handle = hal_ll_spi_master_get_handle;
    hal_ll_spi_master_hw_specifics_map_local =
            hal_ll_get_specifics( hal_ll_spi_master_get_module_state_address );

    if( low_level_handle->hal_ll_spi_master_handle != NULL ) {
        low_level_handle->hal_ll_spi_master_handle  = NULL;
        low_level_handle->hal_drv_spi_master_handle = NULL;

        low_level_handle->init_ll_state = false;

        hal_ll_spi_master_hw_specifics_map_local->mode = HAL_LL_SPI_MASTER_MODE_DEFAULT;
        hal_ll_spi_master_hw_specifics_map_local->speed = HAL_LL_SPI_MASTER_SPEED_100K;
        hal_ll_spi_master_hw_specifics_map_local->dummy_data = 0;
        hal_ll_spi_master_hw_specifics_map_local->hw_actual_speed = 0;

        hal_ll_spi_master_module_enable( hal_ll_spi_master_hw_specifics_map_local, true );
        hal_ll_spi_master_alternate_functions_set_state( hal_ll_spi_master_hw_specifics_map_local, false );
        hal_ll_spi_master_module_enable( hal_ll_spi_master_hw_specifics_map_local, false );

        hal_ll_spi_master_hw_specifics_map_local->pins.sck.pin_name = HAL_LL_PIN_NC;
        hal_ll_spi_master_hw_specifics_map_local->pins.miso.pin_name = HAL_LL_PIN_NC;
        hal_ll_spi_master_hw_specifics_map_local->pins.mosi.pin_name = HAL_LL_PIN_NC;
        hal_ll_spi_master_hw_specifics_map_local->pins.sck.pin_af = 0;
        hal_ll_spi_master_hw_specifics_map_local->pins.miso.pin_af = 0;
        hal_ll_spi_master_hw_specifics_map_local->pins.mosi.pin_af = 0;
    }
}

// ----------------------------------------------- PRIVATE FUNCTION DEFINITIONS
static void hal_ll_spi_master_write_bare_metal( hal_ll_spi_master_base_handle_t *hal_ll_hw_reg,
                                                uint8_t *write_data_buffer, size_t write_data_length ) {
    while ( 0 < write_data_length-- ) {
        // Wait until transmit buffer is empty
        while ( !check_reg_bit( &hal_ll_hw_reg->spsr, HAL_LL_SPI_SPSR_SPTEF ));

        // Send byte from write buffer
        write_reg( &hal_ll_hw_reg->spdr_by, ( uint8_t )( *write_data_buffer++ ) );

        // Wait until receive is complete
        while ( !check_reg_bit( &hal_ll_hw_reg->spsr, HAL_LL_SPI_SPSR_SPRF ));

        // Dummy read
        volatile uint8_t temp = read_reg( &hal_ll_hw_reg->spdr_by );
    }
}

static void hal_ll_spi_master_read_bare_metal( hal_ll_spi_master_base_handle_t *hal_ll_hw_reg,
                                               uint8_t *read_data_buffer, size_t read_data_length,
                                               uint8_t dummy_data ) {
    while ( 0 < read_data_length-- ) {
        // Wait until transmit buffer is empty
        while ( !check_reg_bit( &hal_ll_hw_reg->spsr, HAL_LL_SPI_SPSR_SPTEF ));

        // Send dummy data
        write_reg( &hal_ll_hw_reg->spdr_by, (uint8_t)(dummy_data));

        // Wait until receive is complete
        while ( !check_reg_bit( &hal_ll_hw_reg->spsr, HAL_LL_SPI_SPSR_SPRF ));

        // Read received byte and store if read buffer is provided
        *read_data_buffer++ = (uint8_t)read_reg( &hal_ll_hw_reg->spdr_by );
    }
}

static void hal_ll_spi_master_transfer_bare_metal( hal_ll_spi_master_base_handle_t *hal_ll_hw_reg,
                                                   uint8_t *write_data_buffer,
                                                   uint8_t *read_data_buffer,
                                                   size_t data_length ) {
    while ( 0 < data_length-- ) {
        // Wait until transmit buffer is empty
        while ( !check_reg_bit( &hal_ll_hw_reg->spsr, HAL_LL_SPI_SPSR_SPTEF ));

        // Send byte from write buffer or dummy if NULL
        uint8_t tx_data = ( write_data_buffer ) ? *write_data_buffer++ : 0xFF;
        write_reg( &hal_ll_hw_reg->spdr_by, tx_data );

        // Wait until receive is complete
        while ( !check_reg_bit( &hal_ll_hw_reg->spsr, HAL_LL_SPI_SPSR_SPRF ));

        // Read received byte and store if read buffer is provided
        uint8_t rx_data = (uint8_t)read_reg( &hal_ll_hw_reg->spdr_by );
        if ( read_data_buffer ) {
            *read_data_buffer++ = rx_data;
        }
    }
}

static hal_ll_pin_name_t hal_ll_spi_master_check_pins( hal_ll_pin_name_t sck_pin,
                                                       hal_ll_pin_name_t miso_pin,
                                                       hal_ll_pin_name_t mosi_pin,
                                                       hal_ll_spi_pin_id *index_list,
                                                       hal_ll_spi_master_handle_register_t *handle_map ) {
    static const uint16_t sck_map_size  =
                    ( sizeof( hal_ll_spi_master_sck_map ) ) / ( sizeof( hal_ll_spi_master_pin_map_t ) );
    static const uint16_t miso_map_size =
                    ( sizeof( hal_ll_spi_master_miso_map ) ) / ( sizeof( hal_ll_spi_master_pin_map_t ) );
    static const uint16_t mosi_map_size =
                    ( sizeof( hal_ll_spi_master_mosi_map ) ) / ( sizeof( hal_ll_spi_master_pin_map_t ) );
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
        if (hal_ll_spi_master_sck_map[ sck_index ].pin == sck_pin ) {
            for ( miso_index = 0; miso_index < miso_map_size; miso_index++ ) {
                if (hal_ll_spi_master_miso_map[ miso_index ].pin == miso_pin ) {
                    if (hal_ll_spi_master_sck_map[ sck_index ].module_index ==
                                hal_ll_spi_master_miso_map[ miso_index ].module_index ) {
                        for ( mosi_index = 0; mosi_index < mosi_map_size; mosi_index++ ) {
                            if (hal_ll_spi_master_mosi_map[mosi_index ].pin ==  mosi_pin ) {
                                if (hal_ll_spi_master_sck_map[sck_index].module_index ==
                                             hal_ll_spi_master_mosi_map[ mosi_index ].module_index ) {
                                    // Get module number
                                    hal_ll_module_id =hal_ll_spi_master_sck_map[ sck_index ].module_index;

                                    // Map pin names
                                    index_list[ hal_ll_module_id ].pin_sck = sck_index;
                                    index_list[ hal_ll_module_id ].pin_miso = miso_index;
                                    index_list[ hal_ll_module_id ].pin_mosi = mosi_index;

                                    // Check if module is taken
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
}

static hal_ll_spi_master_hw_specifics_map_t *hal_ll_get_specifics( handle_t handle ) {
    uint8_t hal_ll_module_count = sizeof( hal_ll_module_state ) / ( sizeof( hal_ll_spi_master_handle_register_t ) );

    static uint8_t hal_ll_module_error = sizeof( hal_ll_module_state ) / ( sizeof( hal_ll_spi_master_handle_register_t ) );

    while ( hal_ll_module_count-- ) {
        if ( hal_ll_spi_master_get_base_from_hal_handle ==
             hal_ll_spi_master_hw_specifics_map[ hal_ll_module_count ].base ) {
            return &hal_ll_spi_master_hw_specifics_map[ hal_ll_module_count ];
        }
    }

    // If NOK, return pointer to the last row of this map ( point to null pointer ).
    return &hal_ll_spi_master_hw_specifics_map[hal_ll_module_error];
}

static void hal_ll_spi_master_map_pins( uint8_t module_index, hal_ll_spi_pin_id *index_list ) {
    // if every single pin is OK, insert them into this new map, and use this map in all low level functions.
    hal_ll_spi_master_hw_specifics_map[ module_index ].pins.sck.pin_name  =
                                    hal_ll_spi_master_sck_map[ index_list[ module_index ].pin_sck ].pin;
    hal_ll_spi_master_hw_specifics_map[ module_index ].pins.miso.pin_name =
                                    hal_ll_spi_master_miso_map[ index_list[ module_index ].pin_miso ].pin;
    hal_ll_spi_master_hw_specifics_map[ module_index ].pins.mosi.pin_name =
                                    hal_ll_spi_master_mosi_map[ index_list[ module_index ].pin_mosi ].pin;

    // SCK, MISO and MOSI pins could have different alternate function settings, hence save all the AF-s.
    hal_ll_spi_master_hw_specifics_map[ module_index ].pins.sck.pin_af   =
                                    hal_ll_spi_master_sck_map[ index_list[ module_index ].pin_sck ].af;
    hal_ll_spi_master_hw_specifics_map[ module_index ].pins.miso.pin_af  =
                                    hal_ll_spi_master_miso_map[ index_list[ module_index ].pin_miso ].af;
    hal_ll_spi_master_hw_specifics_map[ module_index ].pins.mosi.pin_af  =
                                    hal_ll_spi_master_mosi_map[ index_list[ module_index ].pin_mosi ].af;
}

static void hal_ll_spi_master_alternate_functions_set_state( hal_ll_spi_master_hw_specifics_map_t *map,
                                                             bool hal_ll_state ) {
    module_struct module;

    if((map->pins.sck.pin_name != HAL_LL_PIN_NC) &&
       (map->pins.miso.pin_name != HAL_LL_PIN_NC) &&
       (map->pins.miso.pin_name != HAL_LL_PIN_NC)) {

        module.pins[0] = VALUE(map->pins.sck.pin_name, map->pins.sck.pin_af);
        module.pins[1] = VALUE(map->pins.miso.pin_name, map->pins.miso.pin_af);
        module.pins[2] = VALUE(map->pins.mosi.pin_name, map->pins.mosi.pin_af);
        module.pins[3] = GPIO_MODULE_STRUCT_END;

        module.configs[0] = GPIO_CFG_PORT_PULL_UP_ENABLE | GPIO_CFG_DIGITAL_OUTPUT | GPIO_CFG_PERIPHERAL_PIN;
        module.configs[1] = GPIO_CFG_DIGITAL_INPUT | GPIO_CFG_PERIPHERAL_PIN;
        module.configs[2] = GPIO_CFG_PORT_PULL_UP_ENABLE | GPIO_CFG_DIGITAL_OUTPUT | GPIO_CFG_PERIPHERAL_PIN;
        module.configs[3] = GPIO_MODULE_STRUCT_END;

        module.gpio_remap = map->pins.sck.pin_af;

        hal_ll_gpio_module_struct_init(&module, hal_ll_state);
    }
}

static void hal_ll_spi_master_module_enable( hal_ll_spi_master_hw_specifics_map_t *map, bool hal_ll_state ) {
    if ( true == hal_ll_state ) {
        switch ( map->module_index ) {
            #ifdef SPI_MODULE_0
            case hal_ll_spi_master_module_num(SPI_MODULE_0):
                clear_reg_bit( _MSTPCRB, MSTPCRB_MSTPB19_POS );
                break;
            #endif
            #ifdef SPI_MODULE_1
            case hal_ll_spi_master_module_num(SPI_MODULE_1):
                clear_reg_bit( _MSTPCRB, MSTPCRB_MSTPB18_POS );
                break;
            #endif

            default:
                break;
        }
    } else {
        switch ( map->module_index ) {
            #ifdef SPI_MODULE_0
            case hal_ll_spi_master_module_num(SPI_MODULE_0):
                set_reg_bit( _MSTPCRB, MSTPCRB_MSTPB19_POS );
                break;
            #endif
            #ifdef SPI_MODULE_1
            case hal_ll_spi_master_module_num(SPI_MODULE_1):
                set_reg_bit( _MSTPCRB, MSTPCRB_MSTPB18_POS );
                break;
            #endif

            default:
                break;
        }
    }
}

static void hal_ll_spi_master_set_bit_rate( hal_ll_spi_master_hw_specifics_map_t *map ) {
    hal_ll_spi_master_base_handle_t *hal_ll_hw_reg = (hal_ll_spi_master_base_handle_t *)map->base;
    static const int mul_table[] = { 2, 4, 8, 16 };
    uint8_t spbr, mul;

    system_clocks_t system_clocks;
    SYSTEM_GetClocksFrequency( &system_clocks );

    uint8_t brdv = ( read_reg( &hal_ll_hw_reg->spcmd0 ) & HAL_LL_SPI_SPCMD0_BRDV_MASK ) >> HAL_LL_SPI_SPCMD0_BRDV;

    mul = mul_table[brdv];

    spbr = system_clocks.pclka / ( map->speed * mul ) - 1;

    write_reg( &hal_ll_hw_reg->spbr, spbr );

    // TODO: Add support for highest and lowest possible bit rates, as well as deviation calculation.
}

static void hal_ll_spi_master_hw_init( hal_ll_spi_master_hw_specifics_map_t *map ) {
    hal_ll_spi_master_base_handle_t *hal_ll_hw_reg = (hal_ll_spi_master_base_handle_t *)map->base;

    // Disable loopback mode; set MOSI output value.
    clear_reg( &hal_ll_hw_reg->sppcr );

    // Set the desired bit rate.
    hal_ll_spi_master_set_bit_rate( map );

    // Byte access is used for SPDR.
    set_reg_bit( &hal_ll_hw_reg->spdcr, HAL_LL_SPI_SPDCR_SPBYT );

    clear_reg( &hal_ll_hw_reg->spckd ); // 1RSPCK delay
    clear_reg( &hal_ll_hw_reg->sslnd ); // 1RSPCK delay
    clear_reg( &hal_ll_hw_reg->spnd ); // 1RSPCK + 2PCLKA delay

    // Enable RSPCK auto-stop function.
    set_reg_bit( &hal_ll_hw_reg->spcr2, HAL_LL_SPI_SPCR2_SCKASE );

    // Use delays as defined in SPND, SSLND and SPCKD.
    write_reg( &hal_ll_hw_reg->spcmd0, HAL_LL_SPI_SPCMD0_SPNDEN_MASK |
                                       HAL_LL_SPI_SPCMD0_SLNDEN_MASK |
                                       HAL_LL_SPI_SPCMD0_SCKDEN_MASK );

    // 8 bit data length.
    write_reg( &hal_ll_hw_reg->spcmd0, HAL_LL_SPI_SPCMD0_SPB_8BIT_MASK );

    // Choose whether idle state for the clock is high level (1) or low level (0).
    if (HAL_LL_SPI_MASTER_MODE_1 >= map->mode ) {
        clear_reg_bit( &hal_ll_hw_reg->spcmd0, HAL_LL_SPI_SPCMD0_CPOL );
    } else {
        set_reg_bit(&( hal_ll_hw_reg->spcmd0), HAL_LL_SPI_SPCMD0_CPOL );
    }

    // Choose whether transmit occurs on the transition from ACTIVE to IDLE (1), or vice versa (0).
    if ( HAL_LL_SPI_MASTER_MODE_0 == map->mode || HAL_LL_SPI_MASTER_MODE_2 == map->mode ) {
        clear_reg_bit( &hal_ll_hw_reg->spcmd0, HAL_LL_SPI_SPCMD0_CPHA );
    } else {
        set_reg_bit( &hal_ll_hw_reg->spcmd0, HAL_LL_SPI_SPCMD0_CPHA );
    }

    // Enable SPI; Master mode
    write_reg( &hal_ll_hw_reg->spcr, HAL_LL_SPI_SPCR_MSTR_MASK | HAL_LL_SPI_SPCR_SPE_MASK );

    volatile uint8_t temp = read_reg( &hal_ll_hw_reg->spcr );
}

static void hal_ll_spi_master_init( hal_ll_spi_master_hw_specifics_map_t *map ) {

    hal_ll_spi_master_module_enable( map, true );

    hal_ll_spi_master_alternate_functions_set_state( map, true );

    hal_ll_spi_master_hw_init( map );
}

// ------------------------------------------------------------------------- END
