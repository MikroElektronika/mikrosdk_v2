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
#include "hal_ll_cg.h"

/*!< @brief Local handle list */
static volatile hal_ll_spi_master_handle_register_t hal_ll_module_state[ SPI_MODULE_COUNT ] = { { ( handle_t * )NULL, ( handle_t * )NULL, false }, { ( handle_t * )NULL, ( handle_t * )NULL, false } };

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


/*!< @brief Default SPI Master bit-rate if no speed is set */
#define HAL_LL_SPI_MASTER_SPEED_100K 100000

/*!< @brief Maximum value for baud rate register (8-bit register) */
#define HAL_LL_SPI_MASTER_BR_REG_MAX_VALUE 255

/*!< @brief Default CR1 configuration: Master mode, SPI mode, Full duplex, CS1 select, FC=5 */
#define HAL_LL_SPI_CR1_DEFAULT_CONFIG 0x00001D05

/*!< @brief Default FMTR0 configuration: MSB first, 8-bit frame, CS1 negative logic, Mode 0 timing */
#define HAL_LL_SPI_FMTR0_DEFAULT_CONFIG 0x88000411

#define HAL_LL_CG_SPI0_BIT 19
#define HAL_LL_CG_SPI1_BIT 20

#define HAL_LL_SPI_CR_ENABLE_BIT 0

// SPI GPIO configuration macros
#define GPIO_CFG_SPI_SCK  ( GPIO_CFG_PORT_DIRECTION_OUTPUT  )

#define GPIO_CFG_SPI_MISO ( GPIO_CFG_MODE_DIGITAL_INPUT | GPIO_CFG_PULL_UP )

#define GPIO_CFG_SPI_MOSI ( GPIO_CFG_PORT_DIRECTION_OUTPUT  )

// CR0 register masks
#define CR0_TSPIE_MASK   0x01
#define CR0_SWRST10_MASK 0x80  // 0x80 - bit 7 for reset step 1
#define CR0_SWRST01_MASK 0x40  // 0x40 - bit 6 for reset step 2

// CR1 register masks
#define CR1_TSPIMS_MASK 0x2000
#define CR1_MSTR_MASK   0x1000
#define CR1_TMMD_MASK   0x0C00
#define CR1_CSSEL_MASK  0x0300
#define CR1_FC_MASK     0x00FF
#define CR1_TRGEN_MASK  0x8000
#define CR1_TRXE_MASK   0x4000

// SECTCR0 register masks
#define SECTCR0_SECT_MASK 0x01

// SR register masks
#define SR_TSPISUE_MASK 0x80000000
#define SR_RLVL_MASK    0x0F
#define SR_TFEMP_MASK   0x00100000
#define SR_RXEND_MASK   0x00000040
#define SR_RFFLL_MASK   0x00000010
#define SR_TXEND_MASK   0x00400000
#define SR_TLVL_MASK    0x000F0000

// FMTR0 register masks
#define FMTR0_DIR_MASK    0x80000000
#define FMTR0_CS0POL_MASK 0x00010000
#define FMTR0_CKPOL_MASK  0x00004000
#define FMTR0_CKPHA_MASK  0x00008000

// CR2 register masks
#define CR0_TIDLE_POS  22
#define CR0_TIDLE_MASK 0x00C00000

#define TSPI_MAX_SPEED    25000000UL

// Helper macros for frame count and TIDLE settings
#define TSPI_CR1_FC_MSK       0xFF
#define TSPI_CR1_FC( val )    ( ( (uint32_t) ( val ) << 0 ) & TSPI_CR1_FC_MSK )
#define TSPI_CR2_TIDLE( val ) ( ( (uint32_t) ( val ) << CR0_TIDLE_POS ) & CR0_TIDLE_MASK )

/*!< @brief SPI Master hw specific error values. */
typedef enum {
    HAL_LL_SPI_MASTER_SUCCESS = 0,
    HAL_LL_SPI_MASTER_WRONG_PINS,
    HAL_LL_SPI_MASTER_MODULE_ERROR,

    HAL_LL_SPI_MASTER_ERROR = ( -1 )
} hal_ll_spi_master_err_t;

/*!< @brief SPI register structure. */
typedef struct {
    uint32_t cr0;
    uint32_t cr1;
    uint32_t cr2;
    uint32_t cr3;
    uint32_t br;
    uint32_t fmtr0;
    uint32_t fmtr1;
    uint32_t sectcr0;
    uint32_t sectcr1;
    uint32_t _unused0[55];
    uint32_t dr;
    uint32_t _unused1[63];
    uint32_t sr;
    uint32_t err;
} hal_ll_spi_master_base_handle_t;

/*!< @brief SPI Master hardware specific module values. */
typedef struct {
    uint8_t pin_miso;
    uint8_t pin_mosi;
    uint8_t pin_sck;
} hal_ll_spi_pin_id;

/*!< @brief SPI Master hardware specific structure. */
typedef struct {
    hal_ll_base_addr_t       base;
    uint8_t                  module_index;
    hal_ll_spi_master_pins_t pins;
    uint8_t                  dummy_data;
    uint32_t                 speed;
    uint32_t                 hw_actual_speed;
    hal_ll_spi_master_mode_t mode;
} hal_ll_spi_master_hw_specifics_map_t;

// ------------------------------------------------------------------ VARIABLES

/*!< @brief Global handle variables used in functions. */
static volatile hal_ll_spi_master_handle_register_t *low_level_handle;
static hal_ll_spi_master_hw_specifics_map_t         *hal_ll_spi_master_hw_specifics_map_local;

/*!< @brief SPI Master hardware specific info. */
static hal_ll_spi_master_hw_specifics_map_t hal_ll_spi_master_hw_specifics_map[SPI_MODULE_COUNT + 1] = {
    #ifdef SPI_MODULE_0
    { HAL_LL_SPI0_MASTER_BASE_ADDR, hal_ll_spi_master_module_num( SPI_MODULE_0 ),
      { HAL_LL_PIN_NC, 0, HAL_LL_PIN_NC, 0, HAL_LL_PIN_NC, 0 },
      0, HAL_LL_SPI_MASTER_SPEED_100K, 0, HAL_LL_SPI_MASTER_MODE_DEFAULT },
    #endif
    #ifdef SPI_MODULE_1
    { HAL_LL_SPI1_MASTER_BASE_ADDR, hal_ll_spi_master_module_num( SPI_MODULE_1 ),
      { HAL_LL_PIN_NC, 0, HAL_LL_PIN_NC, 0, HAL_LL_PIN_NC, 0 },
      0, HAL_LL_SPI_MASTER_SPEED_100K, 0, HAL_LL_SPI_MASTER_MODE_DEFAULT },
    #endif
    { HAL_LL_MODULE_ERROR, HAL_LL_PIN_NC,
      { HAL_LL_PIN_NC, 0, HAL_LL_PIN_NC, 0, HAL_LL_PIN_NC, 0 },
      0, 0, 0, HAL_LL_SPI_MASTER_MODE_DEFAULT }
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

/**
  * @brief  Set SPI Master bit rate.
  *
  * Calculates and sets the SPI bit rate by configuring the SPBR register,
  * based on the system clock, desired speed, and BRDV setting.
  *
  * @param[in]  *map Object-specific context handler.
  * @return None
  *
  */
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

// ----------------------------------------------- PRIVATE FUNCTION DEFINITIONS

// ------------------------------------------------ PUBLIC FUNCTION DEFINITIONS
hal_ll_err_t hal_ll_spi_master_register_handle( hal_ll_pin_name_t sck, hal_ll_pin_name_t miso, hal_ll_pin_name_t mosi,
                                                hal_ll_spi_master_handle_register_t *handle_map,
                                                uint8_t *hal_module_id ) {
    hal_ll_spi_pin_id index_list[SPI_MODULE_COUNT] = { HAL_LL_PIN_NC, HAL_LL_PIN_NC, HAL_LL_PIN_NC };
    uint16_t pin_check_result;

    // Check user-defined pins.
    if ( ( pin_check_result = hal_ll_spi_master_check_pins( sck, miso, mosi, index_list, handle_map ) ) == HAL_LL_PIN_NC ) {
        return HAL_LL_SPI_MASTER_WRONG_PINS;
    };

    // If user has come with the same SPI hardware module, and with the same pair of the pins, the pin mapping procedure
    // will not have to take a place; otherwise, clear af-s, map new pins, set af-s, and set init state to false.
    if ( ( hal_ll_spi_master_hw_specifics_map[ pin_check_result ].pins.sck.pin_name != sck   ) ||
         ( hal_ll_spi_master_hw_specifics_map[ pin_check_result ].pins.miso.pin_name != miso ) ||
         ( hal_ll_spi_master_hw_specifics_map[ pin_check_result ].pins.mosi.pin_name != mosi ) ) {

        hal_ll_spi_master_alternate_functions_set_state( &hal_ll_spi_master_hw_specifics_map[ pin_check_result ], false );

        hal_ll_spi_master_map_pins( pin_check_result, index_list );

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

    if ( hal_ll_spi_master_hw_specifics_map_local->base != HAL_LL_MODULE_ERROR ) {
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
    hal_ll_spi_master_hw_specifics_map_local = hal_ll_get_specifics( hal_ll_spi_master_get_module_state_address );

    if ( NULL == low_level_handle->hal_ll_spi_master_handle ) {
        return HAL_LL_SPI_MASTER_MODULE_ERROR;
    }

    hal_ll_spi_master_transfer_bare_metal( hal_ll_spi_master_hw_specifics_map_local->base,
                                           write_data_buffer, read_data_buffer, data_length );

    if ( !hal_ll_spi_master_hw_specifics_map_local || !data_length ) {
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
    if ( !write_data_buffer || !write_data_length ) {
        return;
    }

    // will be used for disposing of unwanted dr values
    static uint8_t clear_reg = 0;

    // flush rx fifo
    while ( read_reg_bits( &hal_ll_hw_reg->sr, SR_RLVL_MASK ) ) {
        clear_reg = hal_ll_hw_reg->dr;
    }
    
    // set frame count
    uint32_t reg = hal_ll_hw_reg->cr1 & ~TSPI_CR1_FC_MSK;
    reg |= TSPI_CR1_FC( write_data_length );
    hal_ll_hw_reg->cr1 = reg;
    
    /* 
        * since frame lenght is 8bits => TX FIFO has 8 stages ( RM 3.6.1.1 table 3.6)
        * if write_data_length > 8, fully prefill the Tx FIFO and start the transfer
        * before writing new data, make sure to clear recieved data to pervent RX FIFO getting blocked
    */
    if ( write_data_length > 8 ) {
        for ( size_t i = 0; i < 8; i++ ) {
            hal_ll_hw_reg->dr = write_data_buffer[i];
        }
        
        // start communication
        set_reg_bits( &hal_ll_hw_reg->cr1, CR1_TRXE_MASK );

        for ( size_t i = 8; i < write_data_length; i++ ) {
            // shift by 16 since SR<TLVL[3:0]> are bits 19:16 and wait untill there is a space in TX FIFO
            // CR2<TIL[3:0]> max value is 7 
            while ( ( ( read_reg_bits( &hal_ll_hw_reg->sr, SR_TLVL_MASK ) ) >> 16 ) > 6 ) {
            }

            if (read_reg_bits( &hal_ll_hw_reg->sr, SR_RLVL_MASK )) {
                clear_reg = hal_ll_hw_reg->dr;
            }            
            hal_ll_hw_reg->dr = write_data_buffer[i];
        }
    }
    // just prefill the TX FIFO with all the data from write_data_buffer and start transfer
    else {
        for ( size_t i = 0; i < write_data_length; i++ ) {
            hal_ll_hw_reg->dr = write_data_buffer[i];
        }
        
        // start communication
        set_reg_bits( &hal_ll_hw_reg->cr1, CR1_TRXE_MASK );
    }
   
    // wait until TX FIFO becomes empty
    while ( ( read_reg_bits( &hal_ll_hw_reg->sr, SR_TFEMP_MASK ) ) == 0 );
    
    //stop communication
    clear_reg_bits( &hal_ll_hw_reg->cr1, CR1_TRXE_MASK );
    
    // wait until modification is enabled again
    while ( read_reg_bits( &hal_ll_hw_reg->sr, SR_TSPISUE_MASK ) );
}

static void hal_ll_spi_master_read_bare_metal( hal_ll_spi_master_base_handle_t *hal_ll_hw_reg,
                                               uint8_t *read_data_buffer, size_t read_data_length,
                                               uint8_t dummy_data ) {

    // will be used for disposing of unwanted dr values                                            
    static uint8_t clear_reg = 0;

    if ( !read_data_buffer || !read_data_length ) {
        return;
    }
   
    // flush rx fifo
    while (read_reg_bits( &hal_ll_hw_reg->sr, SR_RLVL_MASK )) {
        clear_reg = hal_ll_hw_reg->dr;
    }
    
    // since its a fullduplex, data must also be sent(dummy data) and therefore frame conunt must be set
    uint32_t reg = hal_ll_hw_reg->cr1 & ~TSPI_CR1_FC_MSK;
    reg |= TSPI_CR1_FC( read_data_length );
    hal_ll_hw_reg->cr1 = reg;
    
    // prefill TX FIFO with dummy data, max 8 bytes
    for ( size_t i = 0; i < read_data_length && i < 8; i++ ) {
        hal_ll_hw_reg->dr = dummy_data;
    }
    
    // start communication
    set_reg_bits( &hal_ll_hw_reg->cr1, CR1_TRXE_MASK );

    for ( size_t i = 0; i < read_data_length; i++ ) {

        // wait until there is data in RX FIFO and read it
        while ( ( read_reg_bits( &hal_ll_hw_reg->sr, SR_RLVL_MASK ) ) == 0 );
        read_data_buffer[i] = hal_ll_hw_reg->dr;

        // check if there is still data to be read 
        if ( i + 8 < read_data_length ) {
            hal_ll_hw_reg->dr = dummy_data;
        }
    }
    
    //stop communication
    clear_reg_bits( &hal_ll_hw_reg->cr1, CR1_TRXE_MASK );
   
    // wait until modification is enabled again
    while ( read_reg_bits( &hal_ll_hw_reg->sr, SR_TSPISUE_MASK ) );
}

static void hal_ll_spi_master_transfer_bare_metal( hal_ll_spi_master_base_handle_t *hal_ll_hw_reg,
                                                   uint8_t *write_data_buffer,
                                                   uint8_t *read_data_buffer,
                                                   size_t data_length ) {

    // will be used for disposing of unwanted dr values
    static uint8_t clear_reg = 0;
    
    if ( !data_length ) {
        return;
    }
   
    // flush rx fifo
    while ( read_reg_bits( &hal_ll_hw_reg->sr, SR_RLVL_MASK ) ) {
        clear_reg = hal_ll_hw_reg->dr;
    }
    
    // set frame count
    uint32_t reg = hal_ll_hw_reg->cr1 & ~TSPI_CR1_FC_MSK;
    reg |= TSPI_CR1_FC( data_length );
    hal_ll_hw_reg->cr1 = reg;
   
    // calculate how many bytes TX FIFO will be prefilled with
    size_t initial_fill = ( data_length < 8 ) ? data_length : 8;
    
    // prefill TX FIFO with data from write_data_buffer or with 0x00 if write_data_buffer is NULL
    for ( size_t i = 0; i < initial_fill; i++ ) {
        uint8_t data      = write_data_buffer ? write_data_buffer[i] : 0;
        hal_ll_hw_reg->dr = data;
    }

    size_t tx_count = initial_fill;
    size_t rx_count = 0;   
    
    // start communication
    set_reg_bits( &hal_ll_hw_reg->cr1, CR1_TRXE_MASK );

    // continue transfer until all data is received  
    while ( rx_count < data_length ) {

        // wait until data is recieved in RX FIFO and read it
        while ( ( read_reg_bits( &hal_ll_hw_reg->sr, SR_RLVL_MASK ) ) == 0 );

        uint8_t received = hal_ll_hw_reg->dr;
        if ( read_data_buffer ) {
            read_data_buffer[rx_count] = received;
        }
        rx_count++;
        
        // check if there is more data to be transfered and if there is an empty space in TX FIFO
        if ( tx_count < data_length && ( ( read_reg_bits( &hal_ll_hw_reg->sr, SR_TLVL_MASK ) ) >> 16 ) <= 6 ) {
            uint8_t data      = write_data_buffer ? write_data_buffer[tx_count] : 0;
            hal_ll_hw_reg->dr = data;
            tx_count++;
        }
    }
   
    // wait until TX FIFO becomes empty
    while ( ( read_reg_bits( &hal_ll_hw_reg->sr, SR_TFEMP_MASK ) ) == 0 ); 
    
    
    //stop communication
    clear_reg_bits( &hal_ll_hw_reg->cr1, CR1_TRXE_MASK );
    
    // wait until modification is enabled again
    while ( read_reg_bits( &hal_ll_hw_reg->sr, SR_TSPISUE_MASK ) ); 
    
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

    if ( ( map->pins.sck.pin_name != HAL_LL_PIN_NC ) && ( map->pins.miso.pin_name != HAL_LL_PIN_NC )
         && ( map->pins.mosi.pin_name != HAL_LL_PIN_NC ) ) {
        module.pins[0] = VALUE( map->pins.sck.pin_name, map->pins.sck.pin_af );
        module.pins[1] = VALUE( map->pins.miso.pin_name, map->pins.miso.pin_af );
        module.pins[2] = VALUE( map->pins.mosi.pin_name, map->pins.mosi.pin_af );
        module.pins[3] = GPIO_MODULE_STRUCT_END;

        module.configs[0] = GPIO_CFG_SPI_SCK;
        module.configs[1] = GPIO_CFG_SPI_MISO;
        module.configs[2] = GPIO_CFG_SPI_MOSI;
        module.configs[3] = GPIO_MODULE_STRUCT_END;

        module.gpio_remap = map->pins.sck.pin_af;

        hal_ll_gpio_module_struct_init( &module, hal_ll_state );
    }
}

static void hal_ll_spi_master_module_enable( hal_ll_spi_master_hw_specifics_map_t *map, bool hal_ll_state ) {
    hal_ll_spi_master_base_handle_t *hal_ll_hw_reg = (hal_ll_spi_master_base_handle_t *) map->base;
    hal_ll_cg_base_handle_t         *hal_ll_cg_reg = (hal_ll_cg_base_handle_t *) HAL_LL_CG_BASE_ADDR;

    if ( hal_ll_state ) {
        // Enable SPI module clock and operation
        switch ( map->module_index ) {
            #ifdef SPI_MODULE_0
            case hal_ll_spi_master_module_num( SPI_MODULE_0 ):
                #ifdef HAL_LL_CG_SPI0_BIT
                set_reg_bit( &hal_ll_cg_reg->fsysmena, HAL_LL_CG_SPI0_BIT );  // Enable clock for SPI0 module
                #endif
                break;
            #endif
            #ifdef SPI_MODULE_1
            case hal_ll_spi_master_module_num( SPI_MODULE_1 ):
                #ifdef HAL_LL_CG_SPI1_BIT
                set_reg_bit( &hal_ll_cg_reg->fsysmena, HAL_LL_CG_SPI1_BIT );  // Enable clock for SPI1 module
                #endif
                break;
            #endif

            default:
                break;
        }
    } else {
        // Disable SPI module
        switch ( map->module_index ) {
            #ifdef SPI_MODULE_0
            case hal_ll_spi_master_module_num( SPI_MODULE_0 ):
                #ifdef HAL_LL_CG_SPI0_BIT
                clear_reg_bit( &hal_ll_cg_reg->fsysmena, HAL_LL_CG_SPI0_BIT );  // Disable clock for SPI0 module
                #endif
                break;
            #endif
            #ifdef SPI_MODULE_1
            case hal_ll_spi_master_module_num( SPI_MODULE_1 ):
                #ifdef HAL_LL_CG_SPI1_BIT
                clear_reg_bit( &hal_ll_cg_reg->fsysmena, HAL_LL_CG_SPI1_BIT );  // Disable clock for SPI1 module
                #endif
                break;
            #endif

            default:
                break;
        }
    }
}

static void hal_ll_spi_master_set_bit_rate( hal_ll_spi_master_hw_specifics_map_t *map ) {
    hal_ll_spi_master_base_handle_t *hal_ll_hw_reg = (hal_ll_spi_master_base_handle_t *)map->base;

    // Calculate baud rate setting based on desired speed
    // BR register formula: SPI_CLK = fsys / (2 * (BR + 1))
    CG_ClocksTypeDef cg;
    CG_GetClocksFrequency(&cg);

    uint32_t f_phi_t0 = cg.CG_FT0M_Frequency; 
    uint32_t desired = map->speed ? map->speed : HAL_LL_SPI_MASTER_SPEED_100K;

    // "When setting conditions, the transfer clock cannot exceed 25 MHz" -> RM page 23
    if (desired > TSPI_MAX_SPEED) desired = TSPI_MAX_SPEED; 

    uint32_t best_brck = 0, best_brs = 0;
    uint32_t best_err = 0xFFFFFFFFu;
    
    // prescaler x (BRCK): 1,2,4,...,512  and divisor N (BRS): 1..16
    const uint16_t brck_div_tbl[10] = {1,2,4,8,16,32,64,128,256,512}; 
    for (uint32_t i = 0; i < 10; i++) {
        uint32_t x = brck_div_tbl[i];
        for (uint32_t N = 1; N <= 16; N++) {
            uint32_t f = f_phi_t0 / (2u * x * N);
            uint32_t err = (f > desired) ? (f - desired) : (desired - f);
            if (err < best_err) {
                best_err = err;
                best_brck = i;          
                best_brs  = (N == 16) ? 0 : N; // TSPIxBR<BRS[3:0]> : 0000 = 16 RM page 65
            }
        }
    }

    // wait until modification is enabled again
    while (hal_ll_hw_reg->sr & SR_TSPISUE_MASK);

    // create a bit field with calculate values 
    uint32_t br = ((best_brck & 0xFu) << 4) | (best_brs & 0xFu);
    hal_ll_hw_reg->br = br;                                      
     
    
    // update the speed
    uint32_t x = brck_div_tbl[best_brck];
    uint32_t N = (best_brs == 0) ? 16u : best_brs;
    map->hw_actual_speed = f_phi_t0 / (2u * x * N);



}


uint8_t SW_RESET_FLAG = 0;

static void hal_ll_spi_master_hw_init( hal_ll_spi_master_hw_specifics_map_t *map ) {
    hal_ll_spi_master_base_handle_t *hal_ll_hw_reg = (hal_ll_spi_master_base_handle_t *) map->base;
    hal_ll_cg_base_handle_t         *hal_ll_cg_reg = (hal_ll_cg_base_handle_t *) HAL_LL_CG_BASE_ADDR;

    // Ensure clock is enabled for the specific module
    switch ( map->module_index ) {
        #ifdef SPI_MODULE_0
        case hal_ll_spi_master_module_num( SPI_MODULE_0 ):
            if ( !( hal_ll_cg_reg->fsysmena & ( 1UL << HAL_LL_CG_SPI0_BIT ) ) ) {
                set_reg_bit( &hal_ll_cg_reg->fsysmena, HAL_LL_CG_SPI0_BIT );
            }
            break;
        #endif
        #ifdef SPI_MODULE_1
        case hal_ll_spi_master_module_num( SPI_MODULE_1 ):
            if ( !( hal_ll_cg_reg->fsysmena & ( 1UL << HAL_LL_CG_SPI1_BIT ) ) ) {
                set_reg_bit( &hal_ll_cg_reg->fsysmena, HAL_LL_CG_SPI1_BIT );
            }
            break;
        #endif
        default:
            break;
    }

    // RM page 61 - Set CR0<TSPIE> = 1 (operation) then perform initialization and communications
    set_reg_bits( &hal_ll_hw_reg->cr0, CR0_TSPIE_MASK );

   
    // in case modification is not enbaled,enable it by doing a SW reset
    if ( read_reg_bits( &hal_ll_hw_reg->sr, SR_TSPISUE_MASK ) ) {
        set_reg_bits( &hal_ll_hw_reg->cr0, CR0_SWRST10_MASK );
        set_reg_bits( &hal_ll_hw_reg->cr0, CR0_SWRST01_MASK );
    }    
    
    // wait until modification is enabled 
    while ( read_reg_bits( &hal_ll_hw_reg->sr, SR_TSPISUE_MASK ) );
   
    // choose frame mode
    clear_reg_bits( &hal_ll_hw_reg->sectcr0, SECTCR0_SECT_MASK );

    // Configure CR1: MASTER, SPI MODE, FULL DUPLEX, BURST FRAME transfer
    // Breaking down the bits:
    // - MSTR = 1 (Master mode)
    // - TSPIMS = 1 (SPI mode)
    // - TMMD = 01 (Full duplex)
    // - CSSEL = 01 (CS1)
    // - FC will be set dynamically during transfers
    hal_ll_hw_reg->cr1 = HAL_LL_SPI_CR1_DEFAULT_CONFIG;
    
    // set output value function control when TSPIxTXD idles to be low
    uint32_t reg = hal_ll_hw_reg->cr2 & ~CR0_TIDLE_MASK;
    reg |= TSPI_CR2_TIDLE( 2 );
    hal_ll_hw_reg->cr2 = reg;

    hal_ll_spi_master_set_bit_rate( map );

    // Configure FMTR0 register for SPI mode
    // hal_ll_hw_reg->FMTR0 = 0x88000411;
    // This sets:
    // - MSB first (DIR = 1)
    // - Frame length = 8 bits
    // - CS1 negative logic
    // - Data sampled on first edge (CKPHA = 0)
    // - SCK at LOW LEVEL when idle (CKPOL = 0)
    uint32_t fmtr0_val = HAL_LL_SPI_FMTR0_DEFAULT_CONFIG;

    // Adjust clock polarity and phase based on SPI mode
    switch ( map->mode ) {
        case HAL_LL_SPI_MASTER_MODE_0:
            // CPOL = 0, CPHA = 0 (already set in base value)
            break;
        case HAL_LL_SPI_MASTER_MODE_1:
            // CPOL = 0, CPHA = 1
            fmtr0_val |= FMTR0_CKPHA_MASK;
            break;
        case HAL_LL_SPI_MASTER_MODE_2:
            // CPOL = 1, CPHA = 0
            fmtr0_val |= FMTR0_CKPOL_MASK;
            break;
        case HAL_LL_SPI_MASTER_MODE_3:
            // CPOL = 1, CPHA = 1
            fmtr0_val |= ( FMTR0_CKPOL_MASK | FMTR0_CKPHA_MASK );
            break;
        default:
            // Default to mode 0
            break;
    }

    hal_ll_hw_reg->fmtr0 = fmtr0_val;
}


static void hal_ll_spi_master_init( hal_ll_spi_master_hw_specifics_map_t *map ) {
    hal_ll_spi_master_module_enable( map, true );

    hal_ll_spi_master_alternate_functions_set_state( map, true );

    hal_ll_spi_master_hw_init( map );
}

// ------------------------------------------------------------------------- END
