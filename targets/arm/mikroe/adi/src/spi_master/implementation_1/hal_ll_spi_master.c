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
 * @brief SPI Master HAL LOW LEVEL layer implementation for MAX32690.
 *
 */

#include "hal_ll_spi_master.h"
#include "hal_ll_spi_master_pin_map.h"
#include "hal_ll_gpio_port.h"
#include "hal_ll_pclkdis.h"
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
/*!< @brief Helper macro for getting module specific base address directly from HAL layer handle */
#define hal_ll_spi_master_get_base_from_hal_handle      ( ( hal_ll_spi_master_hw_specifics_map_t * )( ( hal_ll_spi_master_handle_register_t * )\
                                                        ( ( ( hal_ll_spi_master_handle_register_t * )( handle ) )->hal_ll_spi_master_handle ) )->hal_ll_spi_master_handle )->base

// -------------------------------------------------------------- PRIVATE TYPES

// SPIn_CTRL0 bit positions
#define HAL_LL_SPI_MASTER_CTRL0_SS_ACTIVE_POS      (16)
#define HAL_LL_SPI_MASTER_CTRL0_START              (5)
#define HAL_LL_SPI_MASTER_CTRL0_MST_MODE           (1)
#define HAL_LL_SPI_MASTER_CTRL0_EN                 (0)

// SPIn_CTRL2 bit positions
#define HAL_LL_SPI_MASTER_CTRL2_NUMBITS_POS        (8)

// SPIn_CLKCTRL bit positions
#define HAL_LL_SPI_MASTER_CLKCTRL_CLKDIV_POS       (16)
#define HAL_LL_SPI_MASTER_CLKCTRL_HI_POS           (8)
#define HAL_LL_SPI_MASTER_CLKCTRL_LO_POS           (0)

// SPIn_DMA bit positions
#define HAL_LL_SPI_MASTER_DMA_TX_FIFO_EN           (6)
#define HAL_LL_SPI_MASTER_DMA_TX_FLUSH             (7)
#define HAL_LL_SPI_MASTER_DMA_TX_LVL_POS           (8)
#define HAL_LL_SPI_MASTER_DMA_RX_FIFO_EN           (22)
#define HAL_LL_SPI_MASTER_DMA_RX_FLUSH             (23)
#define HAL_LL_SPI_MASTER_DMA_RX_LVL_POS           (24)
#define HAL_LL_SPI_MASTER_CTRL2_CLKPOL   (1)
#define HAL_LL_SPI_MASTER_CTRL2_CLKPHA   (0)

// SPIn_INTFL bit positions
#define HAL_LL_SPI_MASTER_INTFL_MST_DONE           (11)

// SPIn_STAT bit positions
#define HAL_LL_SPI_MASTER_STAT_BUSY                (0)

#define HAL_LL_SPI_MASTER_FIFO_DEPTH               (32)
#define HAL_LL_SPI_MASTER_FIFO8_MAX                (0xFFU)

/*!< @brief Default SPI Master bit-rate if no speed is set */
#define HAL_LL_SPI_MASTER_SPEED_100K 100000

/*!< @brief Approximate PCLK, empirically derived from a scope measurement
 *   -- replace with a real clock-tree query if this port has one. */
#define HAL_LL_SPI_MASTER_PCLK_HZ_APPROX  (32000000UL)

/*!< @brief SPI Master hw specific error values. */
typedef enum {
    HAL_LL_SPI_MASTER_SUCCESS = 0,
    HAL_LL_SPI_MASTER_WRONG_PINS,
    HAL_LL_SPI_MASTER_MODULE_ERROR,

    HAL_LL_SPI_MASTER_ERROR = (-1)
} hal_ll_spi_master_err_t;

/*!< @brief SPI register structure. */
typedef struct {
    uint32_t fifo32;
    uint32_t ctrl0;
    uint32_t ctrl1;
    uint32_t ctrl2;
    uint32_t sstime;
    uint32_t clkctrl;
    uint32_t rsvd0;
    uint32_t dma;
    uint32_t intfl;
    uint32_t inten;
    uint32_t wkfl;
    uint32_t wken;
    uint32_t stat;
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

/*!< @brief SPI Master hardware specific info.
 *
 * Only the one confirmed pin combination is populated (SPI0, AF2 on
 * P2.29/28/27). Add further #ifdef SPI_MODULE_x blocks the same way as
 * more pin options get verified.
 */
static hal_ll_spi_master_hw_specifics_map_t hal_ll_spi_master_hw_specifics_map[ SPI_MODULE_COUNT + 1 ] = {
    #ifdef SPI_MODULE_0
    { HAL_LL_SPI0_BASE_ADDR, hal_ll_spi_master_module_num(SPI_MODULE_0),
     { HAL_LL_PIN_NC, 0, HAL_LL_PIN_NC, 0, HAL_LL_PIN_NC, 0 }, 0xFF,
      HAL_LL_SPI_MASTER_SPEED_100K, 0, HAL_LL_SPI_MASTER_MODE_DEFAULT },
    #endif

    { HAL_LL_MODULE_ERROR, HAL_LL_MODULE_ERROR, { HAL_LL_PIN_NC, 0, HAL_LL_PIN_NC, 0, HAL_LL_PIN_NC, 0 }, 0, 0, 0, 0 }
};

// Pin maps (sck/mosi/miso, with module_index and af per entry) come from
// hal_ll_spi_master_pin_map.h, already #included above -- don't redefine
// them here.

// ---------------------------------------------- PRIVATE FUNCTION DECLARATIONS
/**
  * @brief  Check if pins are adequate.
  * @param[in]  sck_pin, miso_pin, mosi_pin - user-supplied pin names.
  * @param[in]  *index_list - Index list address.
  * @param[out] *handle_map - Pointer to local handle list.
  * @return hal_ll_pin_name_t Module index based on pins.
  */
static hal_ll_pin_name_t hal_ll_spi_master_check_pins( hal_ll_pin_name_t sck_pin,
                                                       hal_ll_pin_name_t miso_pin,
                                                       hal_ll_pin_name_t mosi_pin,
                                                       hal_ll_spi_pin_id *index_list,
                                                       hal_ll_spi_master_handle_register_t *handle_map );

/**
  * @brief  Enable/disable the SPI0 peripheral clock.
  * @param[in]  *map - Object specific context handler.
  * @param[in]  hal_ll_state - True(enable clock)/False(disable clock).
  */
static void hal_ll_spi_master_module_enable( hal_ll_spi_master_hw_specifics_map_t *map, bool hal_ll_state );

/**
  * @brief  Get local hardware specific map.
  * @param[in]  handle - Object specific context handler.
  * @return hal_ll_spi_master_hw_specifics_map_t Map address.
  */
static hal_ll_spi_master_hw_specifics_map_t *hal_ll_get_specifics( handle_t handle );

/**
  * @brief  Set SPI Master bit rate.
  *
  * SCK = PCLK / (2^clkdiv * (hi + lo)), hi == lo for 50% duty. hi/lo
  * must stay nonzero whenever clkdiv is nonzero -- confirmed on
  * hardware that leaving them 0 with clkdiv != 0 means SCK is never
  * generated and the peripheral hangs indefinitely on MST_DONE.
  *
  * @param[in]  *map Object-specific context handler.
  */
static void hal_ll_spi_master_set_bit_rate( hal_ll_spi_master_hw_specifics_map_t *map );

/**
  * @brief  Full SPI Master module initialization procedure.
  * @param[in]  *map - Object specific context handler.
  */
static void hal_ll_spi_master_init( hal_ll_spi_master_hw_specifics_map_t *map );

/**
  * @brief  Initialize hardware SPI module (CTRL2 mode/width, bit rate,
  *         controller mode enable).
  * @param[in]  *map - Object specific context handler.
  */
static void hal_ll_spi_master_hw_init( hal_ll_spi_master_hw_specifics_map_t *map );

/**
  * @brief  Perform a write on the SPI Master bus.
  *
  * Thin wrapper over hal_ll_spi_master_transfer_bare_metal(). Four-wire
  * mode requires both FIFOs running regardless of direction (confirmed
  * on hardware -- see file header note), so there is no cheaper
  * write-only path at this register level; read_data_buffer is passed
  * as NULL so received bytes are simply discarded.
  */
static void hal_ll_spi_master_write_bare_metal( hal_ll_spi_master_base_handle_t *hal_ll_hw_reg,
                                                uint8_t *write_data_buffer,
                                                size_t write_data_length );

/**
  * @brief  Perform a read on the SPI Master bus.
  *
  * Thin wrapper over hal_ll_spi_master_transfer_bare_metal(); dummy_data
  * is passed through as the TX filler byte sent while write_data_buffer
  * is NULL.
  */
static void hal_ll_spi_master_read_bare_metal( hal_ll_spi_master_base_handle_t *hal_ll_hw_reg,
                                               uint8_t *read_data_buffer,
                                               size_t read_data_length,
                                               uint8_t dummy_data );

/**
  * @brief  Perform a simultaneous write and read on the SPI Master bus.
  *
  * Confirmed working on hardware. Both TX and RX FIFOs are always
  * enabled and drained regardless of which buffer is NULL -- four-wire
  * mode on this peripheral is inherently full-duplex; disabling either
  * FIFO stalls MST_DONE forever. NULL write_data_buffer sends
  * filler_byte; NULL read_data_buffer discards received bytes.
  */
static void hal_ll_spi_master_transfer_bare_metal( hal_ll_spi_master_base_handle_t *hal_ll_hw_reg,
                                                   uint8_t *write_data_buffer,
                                                   uint8_t *read_data_buffer,
                                                   size_t data_length,
                                                   uint8_t filler_byte );

/**
  * @brief  Sets SPI Master pin alternate function state (SCK/MOSI/MISO
  *         only -- CS is not part of this peripheral's pin config, see
  *         file header note).
  * @param[in]  *map - Object specific context handler.
  * @param[in]  hal_ll_state - Init/De-init
  */
static void hal_ll_spi_master_alternate_functions_set_state( hal_ll_spi_master_hw_specifics_map_t *map,
                                                             bool hal_ll_state );

/**
 * @brief  Maps new-found module specific values.
 * @param[in]  module_index SPI HW module index.
 * @param[in]  *index_list  Array with SCK, MISO and MOSI map index values.
 */
static void hal_ll_spi_master_map_pins( uint8_t module_index, hal_ll_spi_pin_id *index_list );

// ------------------------------------------------ PUBLIC FUNCTION DEFINITIONS
hal_ll_err_t hal_ll_spi_master_register_handle( hal_ll_pin_name_t sck, hal_ll_pin_name_t miso, hal_ll_pin_name_t mosi,
                                                hal_ll_spi_master_handle_register_t *handle_map,
                                                uint8_t *hal_module_id ) {
    hal_ll_spi_pin_id index_list[ SPI_MODULE_COUNT ] = { HAL_LL_PIN_NC,HAL_LL_PIN_NC,HAL_LL_PIN_NC };
    uint16_t pin_check_result;

    if ( ( pin_check_result = hal_ll_spi_master_check_pins( sck, miso, mosi, &index_list, handle_map ) ) == HAL_LL_PIN_NC ) {
        return HAL_LL_SPI_MASTER_WRONG_PINS;
    };

    if ( ( hal_ll_spi_master_hw_specifics_map[ pin_check_result ].pins.sck.pin_name != sck   ) ||
         ( hal_ll_spi_master_hw_specifics_map[ pin_check_result ].pins.miso.pin_name != miso ) ||
         ( hal_ll_spi_master_hw_specifics_map[ pin_check_result ].pins.mosi.pin_name != mosi ) ) {

        hal_ll_spi_master_alternate_functions_set_state( &hal_ll_spi_master_hw_specifics_map[ pin_check_result ], false );

        hal_ll_spi_master_map_pins( pin_check_result, &index_list );

        hal_ll_spi_master_alternate_functions_set_state( &hal_ll_spi_master_hw_specifics_map[ pin_check_result ], true );

        handle_map[ pin_check_result ].init_ll_state = false;
    }

    *hal_module_id = pin_check_result;

    hal_ll_module_state[ pin_check_result ].hal_ll_spi_master_handle =
                                            ( handle_t * )&hal_ll_spi_master_hw_specifics_map[ pin_check_result ].base;

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
    hal_ll_spi_master_hw_specifics_map_local = hal_ll_get_specifics( hal_ll_spi_master_get_module_state_address );

    if( hal_ll_spi_master_hw_specifics_map_local->base != HAL_LL_MODULE_ERROR ) {
        hal_ll_spi_master_hw_specifics_map_local->dummy_data = dummy_data;
    }
}

hal_ll_err_t hal_ll_spi_master_write( handle_t *handle, uint8_t *write_data_buffer, size_t length_data ) {
    low_level_handle = hal_ll_spi_master_get_handle;
    hal_ll_spi_master_hw_specifics_map_local = hal_ll_get_specifics( hal_ll_spi_master_get_module_state_address );

    hal_ll_spi_master_write_bare_metal( hal_ll_spi_master_hw_specifics_map_local->base,
                                        write_data_buffer,
                                        length_data );

    return HAL_LL_SPI_MASTER_SUCCESS;
}

hal_ll_err_t hal_ll_spi_master_read( handle_t *handle, uint8_t *read_data_buffer, size_t length_data ) {
    low_level_handle = hal_ll_spi_master_get_handle;
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
    low_level_handle = hal_ll_spi_master_get_handle;
    hal_ll_spi_master_hw_specifics_map_local = hal_ll_get_specifics( hal_ll_spi_master_get_module_state_address );

    hal_ll_spi_master_write_bare_metal( hal_ll_spi_master_hw_specifics_map_local->base,
                                        write_data_buffer,
                                        length_write_data );
    hal_ll_spi_master_read_bare_metal( hal_ll_spi_master_hw_specifics_map_local->base,
                                    read_data_buffer, length_read_data,
                                    hal_ll_spi_master_hw_specifics_map_local->dummy_data );

    return HAL_LL_SPI_MASTER_SUCCESS;
}

hal_ll_err_t hal_ll_spi_master_transfer( handle_t *handle,
                                         uint8_t *write_data_buffer,
                                         uint8_t *read_data_buffer,
                                         size_t data_length ) {
    low_level_handle = hal_ll_spi_master_get_handle;
    hal_ll_spi_master_hw_specifics_map_local = hal_ll_get_specifics( hal_ll_spi_master_get_module_state_address );

    if ( NULL == low_level_handle->hal_ll_spi_master_handle ) {
        return HAL_LL_SPI_MASTER_MODULE_ERROR;
    }

    if ( !hal_ll_spi_master_hw_specifics_map_local || !data_length ) {
        return HAL_LL_SPI_MASTER_MODULE_ERROR;
    }

    hal_ll_spi_master_transfer_bare_metal( hal_ll_spi_master_hw_specifics_map_local->base,
                                           write_data_buffer, read_data_buffer, data_length,
                                           hal_ll_spi_master_hw_specifics_map_local->dummy_data );

    return HAL_LL_SPI_MASTER_SUCCESS;
}

uint32_t hal_ll_spi_master_set_speed( handle_t *handle, uint32_t speed ) {
    low_level_handle = hal_ll_spi_master_get_handle;
    hal_ll_spi_master_hw_specifics_map_local =
            hal_ll_get_specifics( hal_ll_spi_master_get_module_state_address );

    low_level_handle->init_ll_state = false;

    hal_ll_spi_master_hw_specifics_map_local->speed = speed;

    hal_ll_spi_master_init( hal_ll_spi_master_hw_specifics_map_local );

    low_level_handle->init_ll_state = true;

    return hal_ll_spi_master_hw_specifics_map_local->hw_actual_speed;
}

hal_ll_err_t hal_ll_spi_master_set_mode( handle_t *handle, hal_ll_spi_master_mode_t mode ) {
    low_level_handle = hal_ll_spi_master_get_handle;
    hal_ll_spi_master_hw_specifics_map_local =
            hal_ll_get_specifics( hal_ll_spi_master_get_module_state_address );

    low_level_handle->init_ll_state = false;

    hal_ll_spi_master_hw_specifics_map_local->mode = mode;

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
        hal_ll_spi_master_hw_specifics_map_local->dummy_data = HAL_LL_SPI_MASTER_FIFO8_MAX;
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
                                                uint8_t *write_data_buffer,
                                                size_t write_data_length ) {
    hal_ll_spi_master_transfer_bare_metal( hal_ll_hw_reg, write_data_buffer, NULL, write_data_length, HAL_LL_SPI_MASTER_FIFO8_MAX );
}

static void hal_ll_spi_master_read_bare_metal( hal_ll_spi_master_base_handle_t *hal_ll_hw_reg,
                                               uint8_t *read_data_buffer,
                                               size_t read_data_length,
                                               uint8_t dummy_data ) {
    hal_ll_spi_master_transfer_bare_metal( hal_ll_hw_reg, NULL, read_data_buffer, read_data_length, dummy_data );
}

static uint32_t hal_ll_spi_master_check_spi_tx_level( hal_ll_spi_master_base_handle_t *hal_ll_hw_reg ) {
    return ( read_reg( &hal_ll_hw_reg->dma ) >> HAL_LL_SPI_MASTER_DMA_TX_LVL_POS ) & 0x3FUL;
}

static uint32_t hal_ll_spi_master_check_spi_rx_level( hal_ll_spi_master_base_handle_t *hal_ll_hw_reg ) {
    return ( read_reg( &hal_ll_hw_reg->dma ) >> HAL_LL_SPI_MASTER_DMA_RX_LVL_POS ) & 0x3FUL;
}

static void hal_ll_spi_master_transfer_bare_metal( hal_ll_spi_master_base_handle_t *hal_ll_hw_reg,
                                                   uint8_t *write_data_buffer,
                                                   uint8_t *read_data_buffer,
                                                   size_t data_length,
                                                   uint8_t filler_byte ) {
    uint16_t tx_cnt = 0, rx_cnt = 0;

    if ( data_length == 0 ) {
        return;
    }

    while( check_reg_bit( &hal_ll_hw_reg->stat, HAL_LL_SPI_MASTER_STAT_BUSY ) );

    // Flush stale FIFO contents (must be done with FIFOs disabled).
    clear_reg_bits( &hal_ll_hw_reg->dma, ( 1 << HAL_LL_SPI_MASTER_DMA_TX_FIFO_EN ) |
                                         ( 1 << HAL_LL_SPI_MASTER_DMA_RX_FIFO_EN ) );
    set_reg_bits( &hal_ll_hw_reg->dma, ( 1 << HAL_LL_SPI_MASTER_DMA_TX_FLUSH ) |
                                       ( 1 << HAL_LL_SPI_MASTER_DMA_RX_FLUSH ) );

    // Four-wire mode: tx_num_char governs both directions.
    write_reg( &hal_ll_hw_reg->ctrl1, ( ( uint32_t )data_length << 16 ) | ( ( uint32_t )data_length ) );

    // Both FIFOs always enabled.
    set_reg_bits( &hal_ll_hw_reg->dma, ( 1 << HAL_LL_SPI_MASTER_DMA_TX_FIFO_EN ) |
                                       ( 1 << HAL_LL_SPI_MASTER_DMA_RX_FIFO_EN ) );
    set_reg_bit( &hal_ll_hw_reg->intfl, HAL_LL_SPI_MASTER_INTFL_MST_DONE );   // clear stale flag (W1C)

    // Pre-fill the TX FIFO before starting.
    while ( ( tx_cnt < data_length ) && ( hal_ll_spi_master_check_spi_tx_level( hal_ll_hw_reg ) < HAL_LL_SPI_MASTER_FIFO_DEPTH ) ) {
        *( volatile uint8_t * )&hal_ll_hw_reg->fifo32 = ( write_data_buffer != 0 ) ? write_data_buffer[tx_cnt] :
                                                                                     filler_byte;
        tx_cnt++;
    }

    set_reg_bit( &hal_ll_hw_reg->ctrl0, HAL_LL_SPI_MASTER_CTRL0_START );

    while ( ( tx_cnt < data_length ) || ( rx_cnt < data_length ) ) {
        if ( ( tx_cnt < data_length ) && ( hal_ll_spi_master_check_spi_tx_level( hal_ll_hw_reg ) < HAL_LL_SPI_MASTER_FIFO_DEPTH ) ) {
            *( volatile uint8_t * )&hal_ll_hw_reg->fifo32 = ( write_data_buffer != 0 ) ? write_data_buffer[tx_cnt] :
                                                                                         filler_byte;
            tx_cnt++;
        }
        if ( ( rx_cnt < data_length ) && ( hal_ll_spi_master_check_spi_rx_level( hal_ll_hw_reg ) > 0 ) ) {
            uint8_t byte = *( volatile uint8_t * )&hal_ll_hw_reg->fifo32;
            if ( read_data_buffer != 0 ) {
                read_data_buffer[rx_cnt] = byte;
            }
            rx_cnt++;
        }
    }

    while( !check_reg_bit( &hal_ll_hw_reg->intfl, HAL_LL_SPI_MASTER_INTFL_MST_DONE ) );
    set_reg_bit( &hal_ll_hw_reg->intfl, HAL_LL_SPI_MASTER_INTFL_MST_DONE );

    clear_reg_bits( &hal_ll_hw_reg->dma, ( 1 << HAL_LL_SPI_MASTER_DMA_TX_FIFO_EN ) |
                                         ( 1 << HAL_LL_SPI_MASTER_DMA_RX_FIFO_EN ) );
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

    for ( sck_index = 0; sck_index < sck_map_size; sck_index++ ) {
        if ( hal_ll_spi_master_sck_map[ sck_index ].pin == sck_pin ) {
            for ( miso_index = 0; miso_index < miso_map_size; miso_index++ ) {
                if ( hal_ll_spi_master_miso_map[ miso_index ].pin == miso_pin ) {
                    if ( hal_ll_spi_master_sck_map[ sck_index ].module_index ==
                                hal_ll_spi_master_miso_map[ miso_index ].module_index ) {
                        for ( mosi_index = 0; mosi_index < mosi_map_size; mosi_index++ ) {
                            if ( hal_ll_spi_master_mosi_map[mosi_index ].pin ==  mosi_pin ) {
                                if ( hal_ll_spi_master_sck_map[sck_index].module_index ==
                                             hal_ll_spi_master_mosi_map[ mosi_index ].module_index ) {
                                    hal_ll_module_id = hal_ll_spi_master_sck_map[ sck_index ].module_index;

                                    for ( uint8_t map_member = 0; map_member < SPI_MODULE_COUNT + 1; map_member++  ) {
                                        if ( hal_ll_spi_master_hw_specifics_map[map_member].module_index ==  hal_ll_module_id ) {
                                            hal_ll_module_id = map_member;
                                            break;
                                        }
                                    }

                                    index_list[ hal_ll_module_id ].pin_sck = sck_index;
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

    return &hal_ll_spi_master_hw_specifics_map[hal_ll_module_error];
}

static void hal_ll_spi_master_map_pins( uint8_t module_index, hal_ll_spi_pin_id *index_list ) {
    hal_ll_spi_master_hw_specifics_map[ module_index ].pins.sck.pin_name  =
                                    hal_ll_spi_master_sck_map[ index_list[ module_index ].pin_sck ].pin;
    hal_ll_spi_master_hw_specifics_map[ module_index ].pins.miso.pin_name =
                                    hal_ll_spi_master_miso_map[ index_list[ module_index ].pin_miso ].pin;
    hal_ll_spi_master_hw_specifics_map[ module_index ].pins.mosi.pin_name =
                                    hal_ll_spi_master_mosi_map[ index_list[ module_index ].pin_mosi ].pin;

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

    if ( ( map->pins.sck.pin_name  != HAL_LL_PIN_NC ) &&
         ( map->pins.miso.pin_name != HAL_LL_PIN_NC ) &&
         ( map->pins.mosi.pin_name != HAL_LL_PIN_NC ) ) {

        module.pins[0] = VALUE( map->pins.sck.pin_name,  map->pins.sck.pin_af );
        module.pins[1] = VALUE( map->pins.miso.pin_name, map->pins.miso.pin_af );
        module.pins[2] = VALUE( map->pins.mosi.pin_name, map->pins.mosi.pin_af );
        module.pins[3] = GPIO_MODULE_STRUCT_END;

        module.configs[0] = GPIO_CFG_DIGITAL_OUTPUT | GPIO_CFG_PERIPHERAL_PIN;   // SCK
        module.configs[1] = GPIO_CFG_DIGITAL_INPUT  | GPIO_CFG_PERIPHERAL_PIN;   // MISO
        module.configs[2] = GPIO_CFG_DIGITAL_OUTPUT | GPIO_CFG_PERIPHERAL_PIN;   // MOSI
        module.configs[3] = GPIO_MODULE_STRUCT_END;

        module.gpio_remap = map->pins.sck.pin_af;

        hal_ll_gpio_module_struct_init( &module, hal_ll_state );
    }
}

static void hal_ll_spi_master_module_enable( hal_ll_spi_master_hw_specifics_map_t *map, bool hal_ll_state ) {
    switch ( map->module_index ) {
        #ifdef SPI_MODULE_0
        case hal_ll_spi_master_module_num(SPI_MODULE_0):
            if ( true == hal_ll_state ) {
                clear_reg_bit( _GCR_PCLKDIS0_, GCR_PCLKDIS0_6 );
            } else {
                clear_reg_bit( _GCR_PCLKDIS0_, GCR_PCLKDIS0_6 );
            }
            break;
        #endif
        #ifdef SPI_MODULE_1
        case hal_ll_spi_master_module_num(SPI_MODULE_1):
            if ( true == hal_ll_state ) {
                clear_reg_bit( _GCR_PCLKDIS0_, GCR_PCLKDIS0_7 );
            } else {
                clear_reg_bit( _GCR_PCLKDIS0_, GCR_PCLKDIS0_7 );
            }
            break;
        #endif
        #ifdef SPI_MODULE_2
        case hal_ll_spi_master_module_num(SPI_MODULE_2):
            if ( true == hal_ll_state ) {
                clear_reg_bit( _GCR_PCLKDIS0_, GCR_PCLKDIS0_8 );
            } else {
                clear_reg_bit( _GCR_PCLKDIS0_, GCR_PCLKDIS0_8 );
            }
            break;
        #endif
        #ifdef SPI_MODULE_3
        case hal_ll_spi_master_module_num(SPI_MODULE_3):
            if ( true == hal_ll_state ) {
                clear_reg_bit( _GCR_PCLKDIS1_, GCR_PCLKDIS0_16 );
            } else {
                clear_reg_bit( _GCR_PCLKDIS1_, GCR_PCLKDIS0_16 );
            }
            break;
        #endif
        #ifdef SPI_MODULE_4
        case hal_ll_spi_master_module_num(SPI_MODULE_4):
            if ( true == hal_ll_state ) {
                clear_reg_bit( _GCR_PCLKDIS1_, GCR_PCLKDIS0_17 );
            } else {
                clear_reg_bit( _GCR_PCLKDIS1_, GCR_PCLKDIS0_17 );
            }
            break;
        #endif

        default:
            break;
    }
}

static void hal_ll_spi_master_set_bit_rate( hal_ll_spi_master_hw_specifics_map_t *map ) {
    hal_ll_spi_master_base_handle_t *hal_ll_hw_reg = (hal_ll_spi_master_base_handle_t *)map->base;
    uint32_t divisor;
    uint8_t scale;
    uint8_t half;

    if ( 0 == map->speed ) {
        map->speed = HAL_LL_SPI_MASTER_SPEED_100K;
    }

    divisor = HAL_LL_SPI_MASTER_PCLK_HZ_APPROX / map->speed;
    if ( 0 == divisor ) {
        divisor = 1;
    }

    // SCK = PCLK / (2^scale * (hi + lo)); keep hi == lo for 50% duty.
    // hi/lo must stay nonzero whenever scale is nonzero (see file header
    // note) -- start scale at 0 and only grow it while half-period would
    // otherwise overflow the 15-cycle hi/lo field.
    scale = 0;
    while ( ( scale < 8 ) && ( ( divisor >> ( scale + 1 ) ) > 30 ) ) {
        scale++;
    }

    half = (uint8_t)( divisor >> ( scale + 1 ) );
    if ( half < 1 ) {
        half = 1;
    }
    if ( half > 15 ) {
        half = 15;
    }

    write_reg( &hal_ll_hw_reg->clkctrl, ( (uint32_t)scale << HAL_LL_SPI_MASTER_CLKCTRL_CLKDIV_POS ) |
                                        ( (uint32_t)half  << HAL_LL_SPI_MASTER_CLKCTRL_HI_POS )     |
                                        ( (uint32_t)half  << HAL_LL_SPI_MASTER_CLKCTRL_LO_POS ) );

    map->hw_actual_speed = HAL_LL_SPI_MASTER_PCLK_HZ_APPROX / ( ( 1UL << scale ) * ( 2UL * half ) );
}

static void hal_ll_spi_master_hw_init( hal_ll_spi_master_hw_specifics_map_t *map ) {
    hal_ll_spi_master_base_handle_t *hal_ll_hw_reg = (hal_ll_spi_master_base_handle_t *)map->base;

    // Disable before reconfiguring.
    clear_reg_bit( &hal_ll_hw_reg->ctrl0, HAL_LL_SPI_MASTER_CTRL0_EN );

    // Set mode.
    // if ( HAL_LL_SPI_MASTER_MODE_1 >= map->mode ) {
    //     clear_reg_bit( &hal_ll_hw_reg->ctrl2, HAL_LL_SPI_MASTER_CTRL2_CLKPOL );
    // } else {
    //     set_reg_bit( &hal_ll_hw_reg->ctrl2, HAL_LL_SPI_MASTER_CTRL2_CLKPOL );
    // }
    // if ( HAL_LL_SPI_MASTER_MODE_0 == map->mode || HAL_LL_SPI_MASTER_MODE_2 == map->mode ) {
    //     clear_reg_bit( &hal_ll_hw_reg->ctrl2, HAL_LL_SPI_MASTER_CTRL2_CLKPHA );
    // } else {
    //     set_reg_bit( &hal_ll_hw_reg->ctrl2, HAL_LL_SPI_MASTER_CTRL2_CLKPHA );
    // }
    // Four-wire full duplex, 8 bits per character.
    // TODO: honor map->mode (CPOL/CPHA) once modes other than 0 are
    // exercised on this port -- fixed to mode 0 for now.
    write_reg( &hal_ll_hw_reg->ctrl2, ( 8UL << HAL_LL_SPI_MASTER_CTRL2_NUMBITS_POS ) );

    hal_ll_spi_master_set_bit_rate( map );

    set_reg_bit( &hal_ll_hw_reg->ctrl0, HAL_LL_SPI_MASTER_CTRL0_MST_MODE );
    set_reg_bit( &hal_ll_hw_reg->ctrl0, HAL_LL_SPI_MASTER_CTRL0_EN );
}

static void hal_ll_spi_master_init( hal_ll_spi_master_hw_specifics_map_t *map ) {
    hal_ll_spi_master_module_enable( map, true );

    hal_ll_spi_master_alternate_functions_set_state( map, true );

    hal_ll_spi_master_hw_init( map );
}

// ------------------------------------------------------------------------- END
