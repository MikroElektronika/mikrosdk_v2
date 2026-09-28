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
#include <stdbool.h>

/*!< @brief Local handle list */
static volatile hal_ll_spi_master_handle_register_t hal_ll_module_state[ SPI_MODULE_COUNT ] = { ( handle_t * )NULL, ( handle_t * )NULL, false };

// ------------------------------------------------------------- PRIVATE MACROS

/*!< @brief Helper macro for getting hal_ll_module_state address */
#define hal_ll_spi_master_get_module_state_address      ( ( hal_ll_spi_master_handle_register_t * )*handle )
/*!< @brief Helper macro for getting module specific control register structure base address */
#define hal_ll_spi_master_get_handle                    ( hal_ll_spi_master_handle_register_t *)hal_ll_spi_master_get_module_state_address->hal_ll_spi_master_handle
/*!< @brief Helper macro for getting module specific control register structure */
#define hal_ll_spi_master_get_base_struct( _handle )    ( ( hal_ll_spi_master_base_handle_t * )_handle )
/*!< @brief Helper macro for getting RSPIA specific control register structure */
#define hal_ll_spi_master_get_rspia_base_struct( _handle ) ( ( hal_ll_spi_master_rspia_base_handle_t * )_handle )
/*!< @brief Helper macro for getting module specific base address directly from HAL layer handle */
#define hal_ll_spi_master_get_base_from_hal_handle      ( ( hal_ll_spi_master_hw_specifics_map_t * )( ( hal_ll_spi_master_handle_register_t * )\
                                                        ( ( ( hal_ll_spi_master_handle_register_t * )( handle ) )->hal_ll_spi_master_handle ) )->hal_ll_spi_master_handle )->base

// -------------------------------------------------------------- PRIVATE TYPES

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

#define HAL_LL_SPI_SPSR_SPTEF (5)
#define HAL_LL_SPI_SPSR_SPRF (7)

#define HAL_LL_RSPIA_SPCR_SPE_MASK (1UL << 0)
#define HAL_LL_RSPIA_SPCR_MRCKS_MASK (1UL << 7)
#define HAL_LL_RSPIA_SPCR_SCKASE_MASK (1UL << 12)
#define HAL_LL_RSPIA_SPCR_MSTR_MASK (1UL << 30)
#define HAL_LL_RSPIA_SPCR_SYNDIS_MASK (1UL << 31)

#define HAL_LL_RSPIA_SPCMD0_SPB_8BIT_MASK (7UL << 16)

#define HAL_LL_RSPIA_SPFCLR_FCLR_MASK (1UL << 0)

#define HAL_LL_RSPIA_SPSR_ERR_FLAGS_MASK ( ( 1U << 7 ) | ( 1U << 8 ) | ( 1U << 10 ) | ( 1U << 11 ) )

#define HAL_LL_RSPIA_SPTFSR_FREE_MASK (7U)
#define HAL_LL_RSPIA_SPRFSR_FILL_MASK (7U)

/*!< @brief RSPI and RSPIA are clocked from PCLKA. */
// TODO: replace with the actual PCLKA value once a clock accessor is available.
#define HAL_LL_SPI_MCU_CLOCK_HZ ( 120000000UL )

#define HAL_LL_SPI_PRCR_ADDR ( 0x000803FEUL )
#define HAL_LL_SPI_PRCR_UNLOCK_VAL ( 0xA502U )
#define HAL_LL_SPI_PRCR_LOCK_VAL ( 0xA500U )

// TODO: confirm MSTPB17 (RSPI0) against the Low Power Consumption chapter.
#define HAL_LL_SPI_RSPI0_MSTPCRB_POS ( 17 )
#define HAL_LL_SPI_RSPIA0_MSTPCRD_POS ( 26 )

/*!< @brief Default SPI Master bit-rate if no speed is set */
#define HAL_LL_SPI_MASTER_SPEED_100K 100000

/*!< @brief SPI Master hw specific error values. */
typedef enum {
    HAL_LL_SPI_MASTER_SUCCESS = 0,
    HAL_LL_SPI_MASTER_WRONG_PINS,
    HAL_LL_SPI_MASTER_MODULE_ERROR,

    HAL_LL_SPI_MASTER_ERROR = (-1)
} hal_ll_spi_master_err_t;

/*!< @brief RSPI register structure. */
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

/*!< @brief RSPIA register structure. */
typedef struct {
    union {
        uint32_t spdr;
        uint16_t spdr_ha;
        uint8_t spdr_by;
    };
    uint8_t spckd;
    uint8_t sslnd;
    uint8_t spnd;
    uint8_t reserved0;
    uint32_t spcr;
    uint8_t sprmcr;
    uint8_t spdrcsr;
    uint8_t sppcr;
    uint8_t reserved1;
    uint8_t sslp;
    uint8_t spbr;
    uint8_t reserved2;
    uint8_t spscr;
    uint32_t spcmd0;
    uint8_t reserved3[ 0x28 ];
    uint16_t spdcr;
    uint16_t reserved4;
    uint16_t spfcr;
    uint8_t reserved5[ 11 ];
    uint8_t spssr;
    uint16_t spsr;
    uint8_t reserved6[ 4 ];
    uint8_t sptfsr;
    uint8_t reserved7[ 3 ];
    uint8_t sprfsr;
    uint8_t reserved8[ 13 ];
    uint16_t spsclr;
    uint8_t spfclr;
} hal_ll_spi_master_rspia_base_handle_t;

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
    bool is_rspia_module;
    uint32_t sck_pin_af;
    uint32_t miso_pin_af;
    uint32_t mosi_pin_af;
} hal_ll_spi_master_hw_specifics_map_t;

// ------------------------------------------------------------------ VARIABLES

/*!< @brief Global handle variables used in functions. */
static volatile hal_ll_spi_master_handle_register_t *low_level_handle;
static volatile hal_ll_spi_master_hw_specifics_map_t *hal_ll_spi_master_hw_specifics_map_local;

/*!< @brief SPI Master hardware specific info. */
static hal_ll_spi_master_hw_specifics_map_t hal_ll_spi_master_hw_specifics_map[ SPI_MODULE_COUNT + 1 ] = {
    #ifdef SPI_MODULE_0
    { HAL_LL_SPI0_MASTER_BASE_ADDR, hal_ll_spi_master_module_num(SPI_MODULE_0),
     { HAL_LL_PIN_NC, HAL_LL_PIN_NC, HAL_LL_PIN_NC }, 0,
      HAL_LL_SPI_MASTER_SPEED_100K, 0, HAL_LL_SPI_MASTER_MODE_DEFAULT, 0, 0, 0, 0},
    #endif
    #ifdef SPI_MODULE_1
    { HAL_LL_SPI1_MASTER_BASE_ADDR, hal_ll_spi_master_module_num(SPI_MODULE_1),
     { HAL_LL_PIN_NC, HAL_LL_PIN_NC, HAL_LL_PIN_NC }, 0,
      HAL_LL_SPI_MASTER_SPEED_100K, 0, HAL_LL_SPI_MASTER_MODE_DEFAULT, 1, 0, 0, 0},
    #endif

    { HAL_LL_MODULE_ERROR, HAL_LL_MODULE_ERROR, { HAL_LL_PIN_NC, HAL_LL_PIN_NC, HAL_LL_PIN_NC }, 0, 0, 0, 0, 0, 0, 0, 0 }
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
  * @return None.
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
  * @return None.
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
  * @brief  Get SPCMD0 bits common to RSPI and RSPIA.
  *
  * Delay enables, CPOL and CPHA, based on the configured SPI mode.
  *
  * @param[in]  *map - Object specific context handler.
  * @return SPCMD0 bit mask.
  */
static uint32_t hal_ll_spi_master_get_spcmd0_common( hal_ll_spi_master_hw_specifics_map_t *map );

/**
  * @brief  Initialize hardware RSPIA module.
  *
  * @param[in]  *map - Object specific context handler.
  * @return None
  */
static void hal_ll_spi_master_rspia_hw_init( hal_ll_spi_master_hw_specifics_map_t *map );

/**
  * @brief  RSPIA variants of the write, read and transfer bare metal functions.
  *
  * Same behavior as their RSPI counterparts above.
  */
static void hal_ll_spi_master_rspia_write_bare_metal( hal_ll_spi_master_rspia_base_handle_t *hal_ll_hw_reg,
                                                      uint8_t *write_data_buffer,
                                                      size_t write_data_length );

static void hal_ll_spi_master_rspia_read_bare_metal( hal_ll_spi_master_rspia_base_handle_t *hal_ll_hw_reg,
                                                     uint8_t *read_data_buffer,
                                                     size_t read_data_length,
                                                     uint8_t dummy_data );

static void hal_ll_spi_master_rspia_transfer_bare_metal( hal_ll_spi_master_rspia_base_handle_t *hal_ll_hw_reg,
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
    hal_ll_spi_pin_id index_list[ SPI_MODULE_COUNT ] = { HAL_LL_PIN_NC, HAL_LL_PIN_NC, HAL_LL_PIN_NC };
    uint16_t pin_check_result;

    // Check user-defined pins.
    pin_check_result = hal_ll_spi_master_check_pins( sck, miso, mosi, index_list, handle_map );

    if ( HAL_LL_PIN_NC == pin_check_result ) {
        return HAL_LL_SPI_MASTER_WRONG_PINS;
    }

    // Same module and same pins do not need remapping; otherwise clear af-s, map new pins, set af-s and reset init state.
    if ( ( hal_ll_spi_master_hw_specifics_map[ pin_check_result ].pins.sck != sck ) ||
         ( hal_ll_spi_master_hw_specifics_map[ pin_check_result ].pins.miso != miso ) ||
         ( hal_ll_spi_master_hw_specifics_map[ pin_check_result ].pins.mosi != mosi ) ) {

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
                                   ( handle_t * )&hal_ll_module_state[ pin_check_result ].hal_ll_spi_master_handle;

    return HAL_LL_SPI_MASTER_SUCCESS;
}

hal_ll_err_t hal_ll_module_configure_spi( handle_t *handle ) {
    hal_ll_spi_master_hw_specifics_map_local = hal_ll_get_specifics( hal_ll_spi_master_get_module_state_address );
    hal_ll_spi_master_handle_register_t *hal_handle = ( hal_ll_spi_master_handle_register_t * )*handle;
    uint8_t pin_check_result = hal_ll_spi_master_hw_specifics_map_local->module_index;

    hal_ll_spi_master_init( hal_ll_spi_master_hw_specifics_map_local );

    hal_ll_module_state[ pin_check_result ].hal_ll_spi_master_handle =
                                            ( handle_t * )&hal_ll_spi_master_hw_specifics_map[ pin_check_result ].base;
    hal_ll_module_state[ pin_check_result ].init_ll_state = true;
    hal_handle->init_ll_state = true;

    return HAL_LL_SPI_MASTER_SUCCESS;
}

void hal_ll_spi_master_set_default_write_data( handle_t *handle, uint8_t dummy_data ) {
    // Get appropriate hw specifics map.
    hal_ll_spi_master_hw_specifics_map_local = hal_ll_get_specifics( hal_ll_spi_master_get_module_state_address );

    if ( HAL_LL_MODULE_ERROR != hal_ll_spi_master_hw_specifics_map_local->base ) {
        hal_ll_spi_master_hw_specifics_map_local->dummy_data = dummy_data;
    }
}

hal_ll_err_t hal_ll_spi_master_write( handle_t *handle, uint8_t *write_data_buffer, size_t length_data ) {
    // Get low level HAL handle.
    low_level_handle = hal_ll_spi_master_get_handle;

    // Get appropriate hw specifics map.
    hal_ll_spi_master_hw_specifics_map_local = hal_ll_get_specifics( hal_ll_spi_master_get_module_state_address );

    if ( true == hal_ll_spi_master_hw_specifics_map_local->is_rspia_module ) {
        hal_ll_spi_master_rspia_write_bare_metal( hal_ll_spi_master_get_rspia_base_struct( hal_ll_spi_master_hw_specifics_map_local->base ),
                                                  write_data_buffer, length_data );
    } else {
        hal_ll_spi_master_write_bare_metal( hal_ll_spi_master_get_base_struct( hal_ll_spi_master_hw_specifics_map_local->base ),
                                            write_data_buffer, length_data );
    }

    return HAL_LL_SPI_MASTER_SUCCESS;
}

hal_ll_err_t hal_ll_spi_master_read( handle_t *handle, uint8_t *read_data_buffer, size_t length_data ) {
    // Get low level HAL handle.
    low_level_handle = hal_ll_spi_master_get_handle;

    // Get appropriate hw specifics map.
    hal_ll_spi_master_hw_specifics_map_local = hal_ll_get_specifics( hal_ll_spi_master_get_module_state_address );

    if ( true == hal_ll_spi_master_hw_specifics_map_local->is_rspia_module ) {
        hal_ll_spi_master_rspia_read_bare_metal( hal_ll_spi_master_get_rspia_base_struct( hal_ll_spi_master_hw_specifics_map_local->base ),
                                                 read_data_buffer, length_data,
                                                 hal_ll_spi_master_hw_specifics_map_local->dummy_data );
    } else {
        hal_ll_spi_master_read_bare_metal( hal_ll_spi_master_get_base_struct( hal_ll_spi_master_hw_specifics_map_local->base ),
                                           read_data_buffer, length_data,
                                           hal_ll_spi_master_hw_specifics_map_local->dummy_data );
    }

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

    if ( true == hal_ll_spi_master_hw_specifics_map_local->is_rspia_module ) {
        hal_ll_spi_master_rspia_write_bare_metal( hal_ll_spi_master_get_rspia_base_struct( hal_ll_spi_master_hw_specifics_map_local->base ),
                                                  write_data_buffer, length_write_data );
        hal_ll_spi_master_rspia_read_bare_metal( hal_ll_spi_master_get_rspia_base_struct( hal_ll_spi_master_hw_specifics_map_local->base ),
                                                 read_data_buffer, length_read_data,
                                                 hal_ll_spi_master_hw_specifics_map_local->dummy_data );
    } else {
        hal_ll_spi_master_write_bare_metal( hal_ll_spi_master_get_base_struct( hal_ll_spi_master_hw_specifics_map_local->base ),
                                            write_data_buffer, length_write_data );
        hal_ll_spi_master_read_bare_metal( hal_ll_spi_master_get_base_struct( hal_ll_spi_master_hw_specifics_map_local->base ),
                                           read_data_buffer, length_read_data,
                                           hal_ll_spi_master_hw_specifics_map_local->dummy_data );
    }

    return HAL_LL_SPI_MASTER_SUCCESS;
}

hal_ll_err_t hal_ll_spi_master_transfer(handle_t *handle,
                                        uint8_t *write_data_buffer,
                                        uint8_t *read_data_buffer,
                                        size_t data_length) {
    low_level_handle = hal_ll_spi_master_get_handle;
    hal_ll_spi_master_hw_specifics_map_local = hal_ll_get_specifics( hal_ll_spi_master_get_module_state_address );

    if ( ( NULL == low_level_handle->hal_ll_spi_master_handle ) || ( 0 == data_length ) ) {
        return HAL_LL_SPI_MASTER_MODULE_ERROR;
    }

    if ( true == hal_ll_spi_master_hw_specifics_map_local->is_rspia_module ) {
        hal_ll_spi_master_rspia_transfer_bare_metal( hal_ll_spi_master_get_rspia_base_struct( hal_ll_spi_master_hw_specifics_map_local->base ),
                                                     write_data_buffer, read_data_buffer, data_length );
    } else {
        hal_ll_spi_master_transfer_bare_metal( hal_ll_spi_master_get_base_struct( hal_ll_spi_master_hw_specifics_map_local->base ),
                                               write_data_buffer, read_data_buffer, data_length );
    }

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

    // Insert user-defined mode into local map.
    hal_ll_spi_master_hw_specifics_map_local->mode = mode;

    // Init once again, but with updated SPI Master mode value.
    hal_ll_spi_master_init( hal_ll_spi_master_hw_specifics_map_local );

    low_level_handle->init_ll_state = true;

    return HAL_LL_SPI_MASTER_SUCCESS;
}

void hal_ll_spi_master_close( handle_t* handle ) {
    low_level_handle = hal_ll_spi_master_get_handle;
    hal_ll_spi_master_hw_specifics_map_local = hal_ll_get_specifics( hal_ll_spi_master_get_module_state_address );

    if ( NULL != low_level_handle->hal_ll_spi_master_handle ) {
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

        hal_ll_spi_master_hw_specifics_map_local->pins.sck = HAL_LL_PIN_NC;
        hal_ll_spi_master_hw_specifics_map_local->pins.miso = HAL_LL_PIN_NC;
        hal_ll_spi_master_hw_specifics_map_local->pins.mosi = HAL_LL_PIN_NC;
        hal_ll_spi_master_hw_specifics_map_local->sck_pin_af = 0;
        hal_ll_spi_master_hw_specifics_map_local->miso_pin_af = 0;
        hal_ll_spi_master_hw_specifics_map_local->mosi_pin_af = 0;
    }
}

// ----------------------------------------------- PRIVATE FUNCTION DEFINITIONS
static void hal_ll_spi_master_write_bare_metal( hal_ll_spi_master_base_handle_t *hal_ll_hw_reg,
                                                uint8_t *write_data_buffer, size_t write_data_length ) {
    while ( 0 < write_data_length-- ) {
        while ( !check_reg_bit( &hal_ll_hw_reg->spsr, HAL_LL_SPI_SPSR_SPTEF ) );

        write_reg( &hal_ll_hw_reg->spdr_by, ( uint8_t )( *write_data_buffer++ ) );

        while ( !check_reg_bit( &hal_ll_hw_reg->spsr, HAL_LL_SPI_SPSR_SPRF ) );

        // Dummy read to free the receive buffer.
        volatile uint8_t temp = read_reg( &hal_ll_hw_reg->spdr_by );
        ( void )temp;
    }
}

static void hal_ll_spi_master_read_bare_metal( hal_ll_spi_master_base_handle_t *hal_ll_hw_reg,
                                               uint8_t *read_data_buffer, size_t read_data_length,
                                               uint8_t dummy_data ) {
    while ( 0 < read_data_length-- ) {
        while ( !check_reg_bit( &hal_ll_hw_reg->spsr, HAL_LL_SPI_SPSR_SPTEF ) );

        write_reg( &hal_ll_hw_reg->spdr_by, ( uint8_t )dummy_data );

        while ( !check_reg_bit( &hal_ll_hw_reg->spsr, HAL_LL_SPI_SPSR_SPRF ) );

        *read_data_buffer++ = ( uint8_t )read_reg( &hal_ll_hw_reg->spdr_by );
    }
}

static void hal_ll_spi_master_transfer_bare_metal( hal_ll_spi_master_base_handle_t *hal_ll_hw_reg,
                                                   uint8_t *write_data_buffer,
                                                   uint8_t *read_data_buffer,
                                                   size_t data_length ) {
    while ( 0 < data_length-- ) {
        while ( !check_reg_bit( &hal_ll_hw_reg->spsr, HAL_LL_SPI_SPSR_SPTEF ) );

        // Send byte from write buffer, or 0xFF if there is none.
        uint8_t tx_data = ( write_data_buffer ) ? *write_data_buffer++ : 0xFF;
        write_reg( &hal_ll_hw_reg->spdr_by, tx_data );

        while ( !check_reg_bit( &hal_ll_hw_reg->spsr, HAL_LL_SPI_SPSR_SPRF ) );

        uint8_t rx_data = ( uint8_t )read_reg( &hal_ll_hw_reg->spdr_by );

        if ( read_data_buffer ) {
            *read_data_buffer++ = rx_data;
        }
    }
}

static void hal_ll_spi_master_rspia_write_bare_metal( hal_ll_spi_master_rspia_base_handle_t *hal_ll_hw_reg,
                                                      uint8_t *write_data_buffer, size_t write_data_length ) {
    // Fill/empty level registers are polled instead of the SPTEF/SPRF flags.
    while ( 0 < write_data_length-- ) {
        while ( 0 == ( read_reg( &hal_ll_hw_reg->sptfsr ) & HAL_LL_RSPIA_SPTFSR_FREE_MASK ) );

        write_reg( &hal_ll_hw_reg->spdr_by, ( uint8_t )( *write_data_buffer++ ) );

        while ( 0 == ( read_reg( &hal_ll_hw_reg->sprfsr ) & HAL_LL_RSPIA_SPRFSR_FILL_MASK ) );

        // Dummy read to free the receive FIFO.
        volatile uint32_t temp = read_reg( &hal_ll_hw_reg->spdr );
        ( void )temp;
    }
}

static void hal_ll_spi_master_rspia_read_bare_metal( hal_ll_spi_master_rspia_base_handle_t *hal_ll_hw_reg,
                                                     uint8_t *read_data_buffer, size_t read_data_length,
                                                     uint8_t dummy_data ) {
    while ( 0 < read_data_length-- ) {
        while ( 0 == ( read_reg( &hal_ll_hw_reg->sptfsr ) & HAL_LL_RSPIA_SPTFSR_FREE_MASK ) );

        write_reg( &hal_ll_hw_reg->spdr_by, ( uint8_t )dummy_data );

        while ( 0 == ( read_reg( &hal_ll_hw_reg->sprfsr ) & HAL_LL_RSPIA_SPRFSR_FILL_MASK ) );

        *read_data_buffer++ = ( uint8_t )read_reg( &hal_ll_hw_reg->spdr );
    }
}

static void hal_ll_spi_master_rspia_transfer_bare_metal( hal_ll_spi_master_rspia_base_handle_t *hal_ll_hw_reg,
                                                         uint8_t *write_data_buffer,
                                                         uint8_t *read_data_buffer,
                                                         size_t data_length ) {
    while ( 0 < data_length-- ) {
        while ( 0 == ( read_reg( &hal_ll_hw_reg->sptfsr ) & HAL_LL_RSPIA_SPTFSR_FREE_MASK ) );

        // Send byte from write buffer, or 0xFF if there is none.
        uint8_t tx_data = ( write_data_buffer ) ? *write_data_buffer++ : 0xFF;
        write_reg( &hal_ll_hw_reg->spdr_by, tx_data );

        while ( 0 == ( read_reg( &hal_ll_hw_reg->sprfsr ) & HAL_LL_RSPIA_SPRFSR_FILL_MASK ) );

        uint8_t rx_data = ( uint8_t )read_reg( &hal_ll_hw_reg->spdr );

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
        if ( hal_ll_spi_master_sck_map[ sck_index ].pin == sck_pin ) {
            for ( miso_index = 0; miso_index < miso_map_size; miso_index++ ) {
                if ( hal_ll_spi_master_miso_map[ miso_index ].pin == miso_pin ) {
                    if ( hal_ll_spi_master_sck_map[ sck_index ].module_index ==
                                hal_ll_spi_master_miso_map[ miso_index ].module_index ) {
                        for ( mosi_index = 0; mosi_index < mosi_map_size; mosi_index++ ) {
                            if ( hal_ll_spi_master_mosi_map[ mosi_index ].pin == mosi_pin ) {
                                if ( hal_ll_spi_master_sck_map[ sck_index ].module_index ==
                                             hal_ll_spi_master_mosi_map[ mosi_index ].module_index ) {
                                    // Get module number
                                    hal_ll_module_id = hal_ll_spi_master_sck_map[ sck_index ].module_index;

                                    // Map module number to map index
                                    for ( uint8_t map_member = 0; map_member < SPI_MODULE_COUNT + 1; map_member++ ) {
                                        if ( hal_ll_spi_master_hw_specifics_map[ map_member ].module_index == hal_ll_module_id ) {
                                            hal_ll_module_id = map_member;
                                            break;
                                        }
                                    }

                                    // Map pin names
                                    index_list[ hal_ll_module_id ].pin_sck = sck_index;
                                    index_list[ hal_ll_module_id ].pin_miso = miso_index;
                                    index_list[ hal_ll_module_id ].pin_mosi = mosi_index;

                                    // Check if module is taken
                                    if ( NULL == handle_map[ hal_ll_module_id ].hal_drv_spi_master_handle ) {
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
    return &hal_ll_spi_master_hw_specifics_map[ hal_ll_module_error ];
}

static void hal_ll_spi_master_map_pins( uint8_t module_index, hal_ll_spi_pin_id *index_list ) {
    hal_ll_spi_master_hw_specifics_map[ module_index ].pins.sck  =
                                    hal_ll_spi_master_sck_map[ index_list[ module_index ].pin_sck ].pin;
    hal_ll_spi_master_hw_specifics_map[ module_index ].pins.miso =
                                    hal_ll_spi_master_miso_map[ index_list[ module_index ].pin_miso ].pin;
    hal_ll_spi_master_hw_specifics_map[ module_index ].pins.mosi =
                                    hal_ll_spi_master_mosi_map[ index_list[ module_index ].pin_mosi ].pin;

    // SCK, MISO and MOSI pins could have different alternate function settings, hence save all the AF-s.
    hal_ll_spi_master_hw_specifics_map[ module_index ].sck_pin_af   =
                                    hal_ll_spi_master_sck_map[ index_list[ module_index ].pin_sck ].af;
    hal_ll_spi_master_hw_specifics_map[ module_index ].miso_pin_af  =
                                    hal_ll_spi_master_miso_map[ index_list[ module_index ].pin_miso ].af;
    hal_ll_spi_master_hw_specifics_map[ module_index ].mosi_pin_af  =
                                    hal_ll_spi_master_mosi_map[ index_list[ module_index ].pin_mosi ].af;
}

static void hal_ll_spi_master_alternate_functions_set_state( hal_ll_spi_master_hw_specifics_map_t *map,
                                                             bool hal_ll_state ) {
    module_struct module;

    if ( ( HAL_LL_PIN_NC != map->pins.sck ) &&
         ( HAL_LL_PIN_NC != map->pins.miso ) &&
         ( HAL_LL_PIN_NC != map->pins.mosi ) ) {

        // Pins are passed plain; the PSEL value goes through module.configs[].
        module.pins[ 0 ] = map->pins.sck;
        module.pins[ 1 ] = map->pins.miso;
        module.pins[ 2 ] = map->pins.mosi;
        module.pins[ 3 ] = GPIO_MODULE_STRUCT_END;

        module.configs[ 0 ] = map->sck_pin_af;
        module.configs[ 1 ] = map->miso_pin_af;
        module.configs[ 2 ] = map->mosi_pin_af;
        module.configs[ 3 ] = GPIO_MODULE_STRUCT_END;

        hal_ll_gpio_module_struct_init( &module, hal_ll_state );
    }
}

static void hal_ll_spi_master_module_enable( hal_ll_spi_master_hw_specifics_map_t *map, bool hal_ll_state ) {
    volatile uint16_t *prcr = ( volatile uint16_t * )HAL_LL_SPI_PRCR_ADDR;

    write_reg( prcr, HAL_LL_SPI_PRCR_UNLOCK_VAL );

    if ( true == map->is_rspia_module ) {
        if ( true == hal_ll_state ) {
            clear_reg_bit( _MSTPCRD, HAL_LL_SPI_RSPIA0_MSTPCRD_POS );
        } else {
            set_reg_bit( _MSTPCRD, HAL_LL_SPI_RSPIA0_MSTPCRD_POS );
        }
    } else {
        if ( true == hal_ll_state ) {
            clear_reg_bit( _MSTPCRB, HAL_LL_SPI_RSPI0_MSTPCRB_POS );
        } else {
            set_reg_bit( _MSTPCRB, HAL_LL_SPI_RSPI0_MSTPCRB_POS );
        }
    }

    write_reg( prcr, HAL_LL_SPI_PRCR_LOCK_VAL );
}

static void hal_ll_spi_master_set_bit_rate( hal_ll_spi_master_hw_specifics_map_t *map ) {
    uint32_t step;
    uint32_t divisor = 0;
    uint8_t brdv;

    // Bit rate = PCLKA / ( 2 * ( SPBR + 1 ) * 2^BRDV ); pick the smallest BRDV whose SPBR fits, rounding the rate down.
    for ( brdv = 0; brdv < 4; brdv++ ) {
        step = ( 2UL << brdv ) * map->speed;
        divisor = ( HAL_LL_SPI_MCU_CLOCK_HZ + step - 1 ) / step;

        if ( 256 >= divisor ) {
            break;
        }
    }

    if ( 4 == brdv ) {
        brdv = 3;
        divisor = 256;
    }

    map->hw_actual_speed = HAL_LL_SPI_MCU_CLOCK_HZ / ( ( 2UL << brdv ) * divisor );

    if ( true == map->is_rspia_module ) {
        hal_ll_spi_master_rspia_base_handle_t *hal_ll_hw_reg = hal_ll_spi_master_get_rspia_base_struct( map->base );

        write_reg( &hal_ll_hw_reg->spbr, ( uint8_t )( divisor - 1 ) );
        clear_reg_bits( &hal_ll_hw_reg->spcmd0, HAL_LL_SPI_SPCMD0_BRDV_MASK );
        set_reg_bits( &hal_ll_hw_reg->spcmd0, ( uint32_t )brdv << HAL_LL_SPI_SPCMD0_BRDV );
    } else {
        hal_ll_spi_master_base_handle_t *hal_ll_hw_reg = hal_ll_spi_master_get_base_struct( map->base );

        write_reg( &hal_ll_hw_reg->spbr, ( uint8_t )( divisor - 1 ) );
        clear_reg_bits( &hal_ll_hw_reg->spcmd0, HAL_LL_SPI_SPCMD0_BRDV_MASK );
        set_reg_bits( &hal_ll_hw_reg->spcmd0, ( uint16_t )( brdv << HAL_LL_SPI_SPCMD0_BRDV ) );
    }
}

static uint32_t hal_ll_spi_master_get_spcmd0_common( hal_ll_spi_master_hw_specifics_map_t *map ) {
    uint32_t spcmd0 = HAL_LL_SPI_SPCMD0_SPNDEN_MASK |
                      HAL_LL_SPI_SPCMD0_SLNDEN_MASK |
                      HAL_LL_SPI_SPCMD0_SCKDEN_MASK;

    // Idle state of the clock: high (CPOL = 1) for modes 2 and 3.
    if ( HAL_LL_SPI_MASTER_MODE_1 < map->mode ) {
        spcmd0 |= ( 1UL << HAL_LL_SPI_SPCMD0_CPOL );
    }

    // Data varies on the odd edge (CPHA = 1) for modes 1 and 3.
    if ( ( HAL_LL_SPI_MASTER_MODE_0 != map->mode ) && ( HAL_LL_SPI_MASTER_MODE_2 != map->mode ) ) {
        spcmd0 |= ( 1UL << HAL_LL_SPI_SPCMD0_CPHA );
    }

    return spcmd0;
}

static void hal_ll_spi_master_hw_init( hal_ll_spi_master_hw_specifics_map_t *map ) {
    hal_ll_spi_master_base_handle_t *hal_ll_hw_reg = hal_ll_spi_master_get_base_struct( map->base );

    // Configuration can only be changed while the module is disabled.
    clear_reg( &hal_ll_hw_reg->spcr );

    // Disable loopback mode; set MOSI output value.
    clear_reg( &hal_ll_hw_reg->sppcr );

    // Byte access is used for SPDR.
    write_reg( &hal_ll_hw_reg->spdcr, ( uint8_t )( 1UL << HAL_LL_SPI_SPDCR_SPBYT ) );

    clear_reg( &hal_ll_hw_reg->spckd );
    clear_reg( &hal_ll_hw_reg->sslnd );
    clear_reg( &hal_ll_hw_reg->spnd );

    // Enable RSPCK auto-stop function.
    write_reg( &hal_ll_hw_reg->spcr2, ( uint8_t )( 1UL << HAL_LL_SPI_SPCR2_SCKASE ) );

    // Use delays as defined in SPND, SSLND and SPCKD; 8 bit data length; clock polarity and phase.
    write_reg( &hal_ll_hw_reg->spcmd0, ( uint16_t )( hal_ll_spi_master_get_spcmd0_common( map ) |
                                                     HAL_LL_SPI_SPCMD0_SPB_8BIT_MASK ) );

    // Set the desired bit rate.
    hal_ll_spi_master_set_bit_rate( map );

    // Enable SPI; Master mode
    write_reg( &hal_ll_hw_reg->spcr, ( uint8_t )( HAL_LL_SPI_SPCR_MSTR_MASK | HAL_LL_SPI_SPCR_SPE_MASK ) );
}

static void hal_ll_spi_master_rspia_hw_init( hal_ll_spi_master_hw_specifics_map_t *map ) {
    hal_ll_spi_master_rspia_base_handle_t *hal_ll_hw_reg = hal_ll_spi_master_get_rspia_base_struct( map->base );
    uint32_t spcr_value = HAL_LL_RSPIA_SPCR_MRCKS_MASK | HAL_LL_RSPIA_SPCR_SYNDIS_MASK | HAL_LL_RSPIA_SPCR_SCKASE_MASK;
    volatile uint32_t temp;

    // SYNDIS has to be set first, with the module disabled.
    write_reg( &hal_ll_hw_reg->spcr, HAL_LL_RSPIA_SPCR_SYNDIS_MASK );

    clear_reg( &hal_ll_hw_reg->sppcr );
    clear_reg( &hal_ll_hw_reg->spdcr );
    clear_reg( &hal_ll_hw_reg->spfcr );
    clear_reg( &hal_ll_hw_reg->spscr );
    clear_reg( &hal_ll_hw_reg->spckd );
    clear_reg( &hal_ll_hw_reg->sslnd );
    clear_reg( &hal_ll_hw_reg->spnd );

    // Use delays as defined in SPND, SSLND and SPCKD; 8 bit data length; clock polarity and phase.
    write_reg( &hal_ll_hw_reg->spcmd0, hal_ll_spi_master_get_spcmd0_common( map ) |
                                       HAL_LL_RSPIA_SPCMD0_SPB_8BIT_MASK );

    // Set the desired bit rate.
    hal_ll_spi_master_set_bit_rate( map );

    write_reg( &hal_ll_hw_reg->spcr, spcr_value );

    // MSTR is set in a separate write, at least 1 PCLKA after the other SPCR bits.
    temp = read_reg( &hal_ll_hw_reg->spcr );
    write_reg( &hal_ll_hw_reg->spcr, spcr_value | HAL_LL_RSPIA_SPCR_MSTR_MASK );
    temp = read_reg( &hal_ll_hw_reg->spcr );
    ( void )temp;

    // Clear error flags and FIFO, then enable the module.
    write_reg( &hal_ll_hw_reg->spsclr, ( uint16_t )( read_reg( &hal_ll_hw_reg->spsr ) & HAL_LL_RSPIA_SPSR_ERR_FLAGS_MASK ) );
    write_reg( &hal_ll_hw_reg->spfclr, ( uint8_t )HAL_LL_RSPIA_SPFCLR_FCLR_MASK );

    write_reg( &hal_ll_hw_reg->spcr, spcr_value | HAL_LL_RSPIA_SPCR_MSTR_MASK | HAL_LL_RSPIA_SPCR_SPE_MASK );
}

static void hal_ll_spi_master_init( hal_ll_spi_master_hw_specifics_map_t *map ) {
    hal_ll_spi_master_module_enable( map, true );

    hal_ll_spi_master_alternate_functions_set_state( map, true );

    if ( true == map->is_rspia_module ) {
        hal_ll_spi_master_rspia_hw_init( map );
    } else {
        hal_ll_spi_master_hw_init( map );
    }
}

// ------------------------------------------------------------------------- END
