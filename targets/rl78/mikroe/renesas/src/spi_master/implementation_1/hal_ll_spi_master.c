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
#include "hal_ll_per.h"
#include "hal_ll_pior_defines.h"
#include <stdbool.h>

/*!< @brief Local handle list */
static volatile hal_ll_spi_master_handle_register_t hal_ll_module_state[ SPI_MODULE_COUNT ] = { ( handle_t * )NULL, ( handle_t * )NULL, false };

// ------------------------------------------------------------- PRIVATE MACROS

/*!< @brief Helper macro for getting hal_ll_module_state address */
#define hal_ll_spi_master_get_module_state_address      ( ( hal_ll_spi_master_handle_register_t * )*handle )
/*!< @brief Helper macro for getting module specific control register structure base address */
#define hal_ll_spi_master_get_handle                    ( hal_ll_spi_master_handle_register_t *)hal_ll_spi_master_get_module_state_address->hal_ll_spi_master_handle
/*!< @brief Helper macro for getting module specific control register structure */
#define hal_ll_spi_master_get_base_struct( _handle )    ( ( volatile hal_ll_spi_master_base_handle_t * )_handle )
/*!< @brief Helper macro for getting module specific base address directly from HAL layer handle */
#define hal_ll_spi_master_get_base_from_hal_handle      ( ( hal_ll_spi_master_hw_specifics_map_t * )( ( hal_ll_spi_master_handle_register_t * )\
                                                        ( ( ( hal_ll_spi_master_handle_register_t * )( handle ) )->hal_ll_spi_master_handle ) )->hal_ll_spi_master_handle )->base

/*!< @brief Volatile register accessors, the bit control macros don't add volatile themselves. */
#define hal_ll_spi_master_reg8(_addr)           ( ( volatile uint8_t * )( _addr ) )
#define hal_ll_spi_master_reg16(_addr)          ( ( volatile uint16_t * )( _addr ) )

/*!< @brief CPU/peripheral clock (fCLK) feeding the SAU prescaler. */
#define HAL_LL_SPI_MASTER_FCLK_HZ               ( ( uint32_t )Get_Fosc_kHz() * 1000UL )

/*!< @brief Register addresses outside of the SAU unit block. */
#define HAL_LL_SPI_MASTER_PER0_ADDR             ( 0xF00F0UL )
#define HAL_LL_SPI_MASTER_PRR0_ADDR             ( 0xF00F1UL )

/*!< @brief Interrupt request flag registers holding the INTCSIp flags (R01UH1082 Figure 25-2). */
#define HAL_LL_SPI_MASTER_IF0H_ADDR             ( 0xFFFE1UL )
#define HAL_LL_SPI_MASTER_IF1L_ADDR             ( 0xFFFE2UL )
#define HAL_LL_SPI_MASTER_IF1H_ADDR             ( 0xFFFE3UL )

/*!< @brief SPIx is channel x%4 of SAU x/4 (CSI00 to CSI31). */
#define hal_ll_spi_master_unit(_index)          ( ( _index ) >> 2 )
#define hal_ll_spi_master_channel(_index)       ( ( _index ) & 3 )
/*!< @brief Channels 0/1 use CKm0, channels 2/3 use CKm1, same split as the UART driver. */
#define hal_ll_spi_master_cks(_index)           ( hal_ll_spi_master_channel( _index ) >> 1 )
/*!< @brief Channels of a unit sharing the prescaler of the given channel. */
#define hal_ll_spi_master_cks_channels(_index)  ( 3U << ( hal_ll_spi_master_cks( _index ) << 1 ) )
/*!< @brief PIOR10 routes SAU0, PIOR11 routes SAU1, two bits per channel. */
#define hal_ll_spi_master_pior_reg(_index)      ( 10 + hal_ll_spi_master_unit( _index ) )
#define hal_ll_spi_master_pior_shift(_index)    ( hal_ll_spi_master_channel( _index ) << 1 )
#define HAL_LL_SPI_MASTER_PIOR_WIDTH            ( 2 )

/*!< @brief SMRmn bits. */
#define HAL_LL_SPI_MASTER_SMR_CKS               ( 15 )
#define HAL_LL_SPI_MASTER_SMR_FIXED             ( 0x0020U ) // Bit 5 must be 1, MDmn2-0 = 000 (CSI, transfer end interrupt).
#define HAL_LL_SPI_MASTER_SMR_RESET             ( 0x0020U )

/*!< @brief SCRmn bits. */
#define HAL_LL_SPI_MASTER_SCR_TXE               ( 0x8000U )
#define HAL_LL_SPI_MASTER_SCR_RXE               ( 0x4000U )
#define HAL_LL_SPI_MASTER_SCR_DAP               ( 0x2000U )
#define HAL_LL_SPI_MASTER_SCR_CKP               ( 0x1000U )
#define HAL_LL_SPI_MASTER_SCR_FIXED             ( 0x0004U ) // Bit 2 must be 1.
#define HAL_LL_SPI_MASTER_SCR_DLS_8_BITS        ( 0x0003U )
#define HAL_LL_SPI_MASTER_SCR_RESET             ( 0x0087U )

/*!< @brief SSRmn/SIRmn bits. */
#define HAL_LL_SPI_MASTER_SSR_TSF               ( 6 )
#define HAL_LL_SPI_MASTER_SIR_OVCT              ( 0x0001U )

/*!< @brief SOm holds CKOmn in bits 11:8 and SOmn in bits 3:0. */
#define HAL_LL_SPI_MASTER_SO_CKO_SHIFT          ( 8 )

/*!< @brief SDRmn[15:9] transfer clock divider, fSCK = fMCK / (SDRmn[15:9] + 1) / 2. */
#define HAL_LL_SPI_MASTER_SDR_DIV_SHIFT         ( 9 )
#define HAL_LL_SPI_MASTER_SDR_DIV_MAX           ( 127 )
#define HAL_LL_SPI_MASTER_PRS_MAX               ( 15 )
#define HAL_LL_SPI_MASTER_PRS_MASK              ( 0x0FU )

/*!< @brief Only CSI00 may run at fCLK/2, the others are limited to fCLK/4. */
#define HAL_LL_SPI_MASTER_FULL_SPEED_INDEX      ( 0 )

// -------------------------------------------------------------- PRIVATE TYPES

/*!< @brief Default SPI Master bit-rate if no speed is set */
#define HAL_LL_SPI_MASTER_SPEED_100K 100000

/*!< @brief SPI Master hw specific error values. */
typedef enum {
    HAL_LL_SPI_MASTER_SUCCESS = 0,
    HAL_LL_SPI_MASTER_WRONG_PINS,
    HAL_LL_SPI_MASTER_MODULE_ERROR,

    HAL_LL_SPI_MASTER_ERROR = (-1)
} hal_ll_spi_master_err_t;

/*!< @brief SAU unit register block, SSRm0 (F0100H / F0140H) up to SSCm. */
typedef struct {
    uint16_t ssr[4];      /*!< 0x00 SSRmn - status. */
    uint16_t sir[4];      /*!< 0x08 SIRmn - error flag clear trigger. */
    uint16_t smr[4];      /*!< 0x10 SMRmn - mode. */
    uint16_t scr[4];      /*!< 0x18 SCRmn - communication format. */
    uint16_t se;          /*!< 0x20 SEm   - channel enable status. */
    uint16_t ss;          /*!< 0x22 SSm   - channel start trigger. */
    uint16_t st;          /*!< 0x24 STm   - channel stop trigger. */
    uint16_t sps;         /*!< 0x26 SPSm  - prescaler select. */
    uint16_t so;          /*!< 0x28 SOm   - serial output level. */
    uint16_t soe;         /*!< 0x2A SOEm  - serial output enable. */
    uint16_t reserved[4]; /*!< 0x2C */
    uint16_t sol;         /*!< 0x34 SOLm  - output level inversion. */
    uint16_t reserved1;   /*!< 0x36 */
    uint16_t ssc;         /*!< 0x38 SSCm  - SNOOZE control. */
} hal_ll_spi_master_base_handle_t;

/*!< @brief SPI Master hardware specific module values. */
typedef struct {
    uint8_t pin_miso;
    uint8_t pin_mosi;
    uint8_t pin_sck;
} hal_ll_spi_pin_id;

/*!< @brief SPI Master hardware specific structure. */
typedef struct {
    hal_ll_base_addr_t base;          /*!< SDRmn (SIOp), identifies the module. */
    hal_ll_base_addr_t sau_base;      /*!< SAU unit register block. */
    hal_ll_base_addr_t if_reg;        /*!< Interrupt request flag register holding CSIIFp. */
    uint8_t if_bit;                   /*!< CSIIFp bit position. */
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
    { HAL_LL_SPI0_BASE_ADDR, HAL_LL_SAU0_BASE_ADDR, HAL_LL_SPI_MASTER_IF0H_ADDR, 5, hal_ll_spi_master_module_num(SPI_MODULE_0),
     { HAL_LL_PIN_NC, 0, HAL_LL_PIN_NC, 0, HAL_LL_PIN_NC, 0 }, 0,
      HAL_LL_SPI_MASTER_SPEED_100K, 0, HAL_LL_SPI_MASTER_MODE_DEFAULT },
    #endif
    #ifdef SPI_MODULE_1
    { HAL_LL_SPI1_BASE_ADDR, HAL_LL_SAU0_BASE_ADDR, HAL_LL_SPI_MASTER_IF1L_ADDR, 4, hal_ll_spi_master_module_num(SPI_MODULE_1),
     { HAL_LL_PIN_NC, 0, HAL_LL_PIN_NC, 0, HAL_LL_PIN_NC, 0 }, 0,
      HAL_LL_SPI_MASTER_SPEED_100K, 0, HAL_LL_SPI_MASTER_MODE_DEFAULT },
    #endif
    #ifdef SPI_MODULE_2
    { HAL_LL_SPI2_BASE_ADDR, HAL_LL_SAU0_BASE_ADDR, HAL_LL_SPI_MASTER_IF1L_ADDR, 0, hal_ll_spi_master_module_num(SPI_MODULE_2),
     { HAL_LL_PIN_NC, 0, HAL_LL_PIN_NC, 0, HAL_LL_PIN_NC, 0 }, 0,
      HAL_LL_SPI_MASTER_SPEED_100K, 0, HAL_LL_SPI_MASTER_MODE_DEFAULT },
    #endif
    #ifdef SPI_MODULE_3
    { HAL_LL_SPI3_BASE_ADDR, HAL_LL_SAU0_BASE_ADDR, HAL_LL_SPI_MASTER_IF1L_ADDR, 1, hal_ll_spi_master_module_num(SPI_MODULE_3),
     { HAL_LL_PIN_NC, 0, HAL_LL_PIN_NC, 0, HAL_LL_PIN_NC, 0 }, 0,
      HAL_LL_SPI_MASTER_SPEED_100K, 0, HAL_LL_SPI_MASTER_MODE_DEFAULT },
    #endif
    #ifdef SPI_MODULE_4
    { HAL_LL_SPI4_BASE_ADDR, HAL_LL_SAU1_BASE_ADDR, HAL_LL_SPI_MASTER_IF0H_ADDR, 0, hal_ll_spi_master_module_num(SPI_MODULE_4),
     { HAL_LL_PIN_NC, 0, HAL_LL_PIN_NC, 0, HAL_LL_PIN_NC, 0 }, 0,
      HAL_LL_SPI_MASTER_SPEED_100K, 0, HAL_LL_SPI_MASTER_MODE_DEFAULT },
    #endif
    #ifdef SPI_MODULE_5
    { HAL_LL_SPI5_BASE_ADDR, HAL_LL_SAU1_BASE_ADDR, HAL_LL_SPI_MASTER_IF0H_ADDR, 1, hal_ll_spi_master_module_num(SPI_MODULE_5),
     { HAL_LL_PIN_NC, 0, HAL_LL_PIN_NC, 0, HAL_LL_PIN_NC, 0 }, 0,
      HAL_LL_SPI_MASTER_SPEED_100K, 0, HAL_LL_SPI_MASTER_MODE_DEFAULT },
    #endif
    #ifdef SPI_MODULE_6
    { HAL_LL_SPI6_BASE_ADDR, HAL_LL_SAU1_BASE_ADDR, HAL_LL_SPI_MASTER_IF1H_ADDR, 4, hal_ll_spi_master_module_num(SPI_MODULE_6),
     { HAL_LL_PIN_NC, 0, HAL_LL_PIN_NC, 0, HAL_LL_PIN_NC, 0 }, 0,
      HAL_LL_SPI_MASTER_SPEED_100K, 0, HAL_LL_SPI_MASTER_MODE_DEFAULT },
    #endif
    #ifdef SPI_MODULE_7
    { HAL_LL_SPI7_BASE_ADDR, HAL_LL_SAU1_BASE_ADDR, HAL_LL_SPI_MASTER_IF1H_ADDR, 5, hal_ll_spi_master_module_num(SPI_MODULE_7),
     { HAL_LL_PIN_NC, 0, HAL_LL_PIN_NC, 0, HAL_LL_PIN_NC, 0 }, 0,
      HAL_LL_SPI_MASTER_SPEED_100K, 0, HAL_LL_SPI_MASTER_MODE_DEFAULT },
    #endif

    { HAL_LL_MODULE_ERROR, HAL_LL_MODULE_ERROR, HAL_LL_MODULE_ERROR, 0, HAL_LL_MODULE_ERROR,
     { HAL_LL_PIN_NC, 0, HAL_LL_PIN_NC, 0, HAL_LL_PIN_NC, 0 }, 0, 0, 0, 0 }
};

// ---------------------------------------------- PRIVATE FUNCTION DECLARATIONS
/**
  * @brief  Check if pins are adequate.
  *
  * Checks SCK, MISO and MOSI pins the user has passed with pre-defined
  * pins in SCK, MISO and MOSI maps. Take into consideration that module
  * index numbers and PIOR values have to be the same for all pins,
  * since one PIOR field routes SCKp, SIp and SOp.
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
  * Releases the SAU unit from reset and supplies its clock.
  * The clock is only stopped if no other channel of the
  * unit is running, since UART/CSI/IIC channels share it.
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
  * @brief  Calculate SPI Master bit rate.
  *
  * Calculates the SPSm prescaler and the SDRmn[15:9] divider giving
  * the highest bit rate not above the requested speed.
  * fSCK = fCLK / 2^prs / (SDRmn[15:9] + 1) / 2.
  * If another channel sharing the prescaler is running, its
  * prescaler is kept and only the divider is calculated.
  *
  * @param[in]  *map Object-specific context handler.
  * @param[out] *prs Prescaler value for SPSm.
  * @return uint16_t SDRmn[15:9] divider value.
  */
static uint16_t hal_ll_spi_master_set_bit_rate( hal_ll_spi_master_hw_specifics_map_t *map, uint8_t *prs );

/**
  * @brief  Full SPI Master module initialization procedure.
  *
  * Initializes SPI Master module on hardware level, based on beforehand
  * set configuration and module handler. Sets adequate pin alternate functions.
  * Initializes module clock.
  *
  * @param[in]  *map - Object specific context handler.
  * @return None
  */
static void hal_ll_spi_master_init( hal_ll_spi_master_hw_specifics_map_t *map );

/**
  * @brief  Initialize hardware SPI module.
  *
  * Master transmission/reception procedure
  * (R01UH1082 Figure 19-42 and 19-43).
  *
  * @param[in]  *map - Object specific context handler.
  * @return None
  */
static void hal_ll_spi_master_hw_init( hal_ll_spi_master_hw_specifics_map_t *map );

/**
  * @brief  Stop SPI channel and restore its registers.
  *
  * @param[in]  *map - Object specific context handler.
  * @return None
  */
static void hal_ll_spi_master_clear_regs( hal_ll_spi_master_hw_specifics_map_t *map );

/**
  * @brief  Transfer a single byte.
  *
  * Writes SIOp and polls the transfer end interrupt
  * request flag (CSIIFp), then reads received data.
  *
  * @param[in]  *map - Object specific context handler.
  * @param[in]  data - Byte to be sent.
  * @return uint8_t Received byte.
  */
static uint8_t hal_ll_spi_master_transfer_byte( hal_ll_spi_master_hw_specifics_map_t *map, uint8_t data );

/**
  * @brief  Perform a write on the SPI Master bus.
  *
  * Received data is discarded.
  *
  * @param[in]  *map - Object specific context handler.
  * @param[in]  *write_data_buffer - Pointer to data buffer.
  * @param[in]  write_data_length - Number of data to be written.
  * @return None.
  */
static void hal_ll_spi_master_write_bare_metal( hal_ll_spi_master_hw_specifics_map_t *map,
                                                uint8_t *write_data_buffer,
                                                size_t write_data_length );

/**
  * @brief  Perform a read on the SPI Master bus.
  *
  * Dummy data is sent for each byte read.
  *
  * @param[in]  *map - Object specific context handler.
  * @param[in]  *read_data_buffer - Pointer to data buffer.
  * @param[in]  read_data_length - Number of data to be read.
  * @param[in]  dummy_data - Data required for read procedure.
  * @return None.
  */
static void hal_ll_spi_master_read_bare_metal( hal_ll_spi_master_hw_specifics_map_t *map,
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
  * @note This implementation uses polling and is blocking.
  */
static void hal_ll_spi_master_transfer_bare_metal( hal_ll_spi_master_hw_specifics_map_t *map,
                                                   uint8_t *write_data_buffer,
                                                   uint8_t *read_data_buffer,
                                                   size_t data_length );
/**
  * @brief  Sets SPI Master pin alternate function state.
  *
  * Routes SCKp/SIp/SOp through PIOR10/PIOR11 and configures
  * pin directions. SCK and MOSI output latches are left high,
  * since the pins output the latch ANDed with the serial output.
  *
  * @param[in]  *map - Object specific context handler.
  * @param[in]  hal_ll_state - Init/De-init
  */
static void hal_ll_spi_master_alternate_functions_set_state( hal_ll_spi_master_hw_specifics_map_t *map,
                                                             bool hal_ll_state );

/**
 * @brief  Maps new-found module specific values.
 *
 * Maps pin names and PIOR values for
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

    if( hal_ll_spi_master_hw_specifics_map_local->base != HAL_LL_MODULE_ERROR ) {
        hal_ll_spi_master_hw_specifics_map_local->dummy_data = dummy_data;
    }
}

hal_ll_err_t hal_ll_spi_master_write( handle_t *handle, uint8_t *write_data_buffer, size_t length_data ) {
    // Get low level HAL handle.
    low_level_handle = hal_ll_spi_master_get_handle;

    // Get appropriate hw specifics map.
    hal_ll_spi_master_hw_specifics_map_local = hal_ll_get_specifics( hal_ll_spi_master_get_module_state_address );

    hal_ll_spi_master_write_bare_metal( hal_ll_spi_master_hw_specifics_map_local,
                                        write_data_buffer,
                                        length_data );

    return HAL_LL_SPI_MASTER_SUCCESS;
}

hal_ll_err_t hal_ll_spi_master_read( handle_t *handle, uint8_t *read_data_buffer, size_t length_data ) {
    // Get low level HAL handle.
    low_level_handle = hal_ll_spi_master_get_handle;

    // Get appropriate hw specifics map.
    hal_ll_spi_master_hw_specifics_map_local = hal_ll_get_specifics( hal_ll_spi_master_get_module_state_address );

    hal_ll_spi_master_read_bare_metal( hal_ll_spi_master_hw_specifics_map_local,
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

    hal_ll_spi_master_write_bare_metal( hal_ll_spi_master_hw_specifics_map_local,
                                        write_data_buffer,
                                        length_write_data );
    hal_ll_spi_master_read_bare_metal( hal_ll_spi_master_hw_specifics_map_local,
                                       read_data_buffer, length_read_data,
                                       hal_ll_spi_master_hw_specifics_map_local->dummy_data );

    return HAL_LL_SPI_MASTER_SUCCESS;
}

hal_ll_err_t hal_ll_spi_master_transfer(handle_t *handle,
                                        uint8_t *write_data_buffer,
                                        uint8_t *read_data_buffer,
                                        size_t data_length) {
    low_level_handle = hal_ll_spi_master_get_handle;
    hal_ll_spi_master_hw_specifics_map_local = hal_ll_get_specifics(hal_ll_spi_master_get_module_state_address);

    if ( ( NULL == low_level_handle->hal_ll_spi_master_handle ) ||
         ( HAL_LL_MODULE_ERROR == hal_ll_spi_master_hw_specifics_map_local->base ) || !data_length ) {
        return HAL_LL_SPI_MASTER_MODULE_ERROR;
    }

    hal_ll_spi_master_transfer_bare_metal( hal_ll_spi_master_hw_specifics_map_local,
                                           write_data_buffer, read_data_buffer, data_length );

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
        hal_ll_spi_master_clear_regs( hal_ll_spi_master_hw_specifics_map_local );
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
static uint8_t hal_ll_spi_master_transfer_byte( hal_ll_spi_master_hw_specifics_map_t *map, uint8_t data ) {
    volatile uint8_t *if_reg = hal_ll_spi_master_reg8( map->if_reg );

    // CSIIFp is set on transfer end even while masked (MKxx = 1 after reset).
    clear_reg_bit( if_reg, map->if_bit );

    // While the channel runs, only SDRmn[7:0] (SIOp) is written.
    write_reg( hal_ll_spi_master_reg8( map->base ), data );

    while ( !check_reg_bit( if_reg, map->if_bit ) );

    clear_reg_bit( if_reg, map->if_bit );

    return read_reg( hal_ll_spi_master_reg8( map->base ) );
}

static void hal_ll_spi_master_write_bare_metal( hal_ll_spi_master_hw_specifics_map_t *map,
                                                uint8_t *write_data_buffer, size_t write_data_length ) {
    for ( size_t i = 0; i < write_data_length; i++ ) {
        hal_ll_spi_master_transfer_byte( map, write_data_buffer[ i ] );
    }
}

static void hal_ll_spi_master_read_bare_metal( hal_ll_spi_master_hw_specifics_map_t *map,
                                               uint8_t *read_data_buffer, size_t read_data_length,
                                               uint8_t dummy_data ) {
    for ( size_t i = 0; i < read_data_length; i++ ) {
        read_data_buffer[ i ] = hal_ll_spi_master_transfer_byte( map, dummy_data );
    }
}

static void hal_ll_spi_master_transfer_bare_metal( hal_ll_spi_master_hw_specifics_map_t *map,
                                                   uint8_t *write_data_buffer,
                                                   uint8_t *read_data_buffer,
                                                   size_t data_length ) {
    uint8_t read_data;

    for ( size_t i = 0; i < data_length; i++ ) {
        read_data = hal_ll_spi_master_transfer_byte( map, write_data_buffer ? write_data_buffer[ i ] : map->dummy_data );

        if ( read_data_buffer ) {
            read_data_buffer[ i ] = read_data;
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
                // One PIOR field routes all three pins, so they must share it.
                if ( ( hal_ll_spi_master_miso_map[ miso_index ].pin == miso_pin ) &&
                     ( hal_ll_spi_master_sck_map[ sck_index ].module_index == hal_ll_spi_master_miso_map[ miso_index ].module_index ) &&
                     ( hal_ll_spi_master_sck_map[ sck_index ].af == hal_ll_spi_master_miso_map[ miso_index ].af ) ) {
                    for ( mosi_index = 0; mosi_index < mosi_map_size; mosi_index++ ) {
                        if ( ( hal_ll_spi_master_mosi_map[ mosi_index ].pin == mosi_pin ) &&
                             ( hal_ll_spi_master_sck_map[ sck_index ].module_index == hal_ll_spi_master_mosi_map[ mosi_index ].module_index ) &&
                             ( hal_ll_spi_master_sck_map[ sck_index ].af == hal_ll_spi_master_mosi_map[ mosi_index ].af ) ) {
                            // Get module number
                            hal_ll_module_id = hal_ll_spi_master_sck_map[ sck_index ].module_index;

                            // Map module number to map index
                            for ( uint8_t map_member = 0; map_member < SPI_MODULE_COUNT + 1; map_member++  ) {
                                if ( hal_ll_spi_master_hw_specifics_map[map_member].module_index ==  hal_ll_module_id ) {
                                    hal_ll_module_id = map_member;
                                    break;
                                }
                            }

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

    // SCK, MISO and MOSI share the PIOR value, checked in hal_ll_spi_master_check_pins.
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
    hal_ll_pin_name_t sck_pin = map->pins.sck.pin_name;
    hal_ll_pin_name_t mosi_pin = map->pins.mosi.pin_name;

    if( ( map->pins.sck.pin_name != HAL_LL_PIN_NC ) &&
        ( map->pins.miso.pin_name != HAL_LL_PIN_NC ) &&
        ( map->pins.mosi.pin_name != HAL_LL_PIN_NC ) ) {

        if ( hal_ll_state ) {
            hal_ll_pior_set_field( hal_ll_spi_master_pior_reg( map->module_index ),
                                   hal_ll_spi_master_pior_shift( map->module_index ),
                                   HAL_LL_SPI_MASTER_PIOR_WIDTH, map->pins.sck.pin_af );
        }

        module.pins[0] = map->pins.sck.pin_name;
        module.pins[1] = map->pins.miso.pin_name;
        module.pins[2] = map->pins.mosi.pin_name;
        module.pins[3] = GPIO_MODULE_STRUCT_END;

        module.configs[0] = GPIO_CFG_DIGITAL_OUTPUT;
        module.configs[1] = GPIO_CFG_DIGITAL_INPUT;
        module.configs[2] = GPIO_CFG_DIGITAL_OUTPUT;
        module.configs[3] = GPIO_MODULE_STRUCT_END;

        hal_ll_gpio_module_struct_init( &module, hal_ll_state );

        if ( hal_ll_state ) {
            // SCKp and SOp are the port latch ANDed with the serial output, so the latches must be high.
            set_reg_bits( hal_ll_spi_master_reg8( hal_ll_gpio_port_base( hal_ll_gpio_port_index( sck_pin ) ) ),
                          ( uint8_t )hal_ll_gpio_pin_mask( sck_pin ) );
            set_reg_bits( hal_ll_spi_master_reg8( hal_ll_gpio_port_base( hal_ll_gpio_port_index( mosi_pin ) ) ),
                          ( uint8_t )hal_ll_gpio_pin_mask( mosi_pin ) );
        }
    }
}

static void hal_ll_spi_master_module_enable( hal_ll_spi_master_hw_specifics_map_t *map, bool hal_ll_state ) {
    volatile hal_ll_spi_master_base_handle_t *hal_ll_hw_reg = hal_ll_spi_master_get_base_struct( map->sau_base );
    uint8_t per0_bit = PER0_SAU0EN_POS + hal_ll_spi_master_unit( map->module_index );

    if ( hal_ll_state ) {
        // SAUmRES shares the PER0 bit position in PRR0.
        clear_reg_bit( hal_ll_spi_master_reg8( HAL_LL_SPI_MASTER_PRR0_ADDR ), per0_bit );
        set_reg_bit( hal_ll_spi_master_reg8( HAL_LL_SPI_MASTER_PER0_ADDR ), per0_bit );
    } else if ( !read_reg( &hal_ll_hw_reg->se ) ) {
        // The other UART/CSI/IIC channels of this unit share the clock, keep it while any of them run.
        clear_reg_bit( hal_ll_spi_master_reg8( HAL_LL_SPI_MASTER_PER0_ADDR ), per0_bit );
    }
}

static uint16_t hal_ll_spi_master_set_bit_rate( hal_ll_spi_master_hw_specifics_map_t *map, uint8_t *prs ) {
    volatile hal_ll_spi_master_base_handle_t *hal_ll_hw_reg = hal_ll_spi_master_get_base_struct( map->sau_base );
    uint8_t channel = hal_ll_spi_master_channel( map->module_index );
    uint8_t cks_shift = hal_ll_spi_master_cks( map->module_index ) << 2;
    uint32_t speed = map->speed ? map->speed : 1;
    bool prs_locked;
    uint32_t fmck = HAL_LL_SPI_MASTER_FCLK_HZ;
    uint32_t div = 1;
    uint8_t div_min;

    // SPSm must not change while the other channel on the same prescaler runs, use its setting then.
    prs_locked = ( read_reg( &hal_ll_hw_reg->se ) & hal_ll_spi_master_cks_channels( map->module_index ) & ~( 1U << channel ) );
    *prs = prs_locked ? ( ( read_reg( &hal_ll_hw_reg->sps ) >> cks_shift ) & HAL_LL_SPI_MASTER_PRS_MASK ) : 0;

    // The lowest prescaler that fits keeps the most resolution.
    for ( ; *prs <= HAL_LL_SPI_MASTER_PRS_MAX; ( *prs )++ ) {
        fmck = HAL_LL_SPI_MASTER_FCLK_HZ >> *prs;
        // Round the divider up, so the actual speed is never above the requested one.
        div = ( fmck + ( 2 * speed ) - 1 ) / ( 2 * speed );
        // Master transfer clock is limited to fCLK/4, except CSI00 (fCLK/2).
        div_min = ( ( 0 == *prs ) && ( HAL_LL_SPI_MASTER_FULL_SPEED_INDEX != map->module_index ) ) ? 2 : 1;
        if ( div < div_min ) {
            div = div_min;
        }

        if ( ( ( div - 1 ) <= HAL_LL_SPI_MASTER_SDR_DIV_MAX ) || prs_locked ) {
            break;
        }
    }

    // Requested speed is below the slowest setting, use the slowest one.
    if ( *prs > HAL_LL_SPI_MASTER_PRS_MAX ) {
        *prs = HAL_LL_SPI_MASTER_PRS_MAX;
        fmck = HAL_LL_SPI_MASTER_FCLK_HZ >> *prs;
    }
    if ( ( div - 1 ) > HAL_LL_SPI_MASTER_SDR_DIV_MAX ) {
        div = HAL_LL_SPI_MASTER_SDR_DIV_MAX + 1;
    }

    map->hw_actual_speed = fmck / ( 2 * div );

    return ( uint16_t )( div - 1 );
}

static void hal_ll_spi_master_clear_regs( hal_ll_spi_master_hw_specifics_map_t *map ) {
    volatile hal_ll_spi_master_base_handle_t *hal_ll_hw_reg = hal_ll_spi_master_get_base_struct( map->sau_base );
    uint8_t channel = hal_ll_spi_master_channel( map->module_index );

    // STm is a trigger register, other channels are unaffected by zero bits.
    write_reg( &hal_ll_hw_reg->st, ( 1U << channel ) );
    clear_reg_bit( &hal_ll_hw_reg->soe, channel );

    write_reg( &hal_ll_hw_reg->smr[ channel ], HAL_LL_SPI_MASTER_SMR_RESET );
    write_reg( &hal_ll_hw_reg->scr[ channel ], HAL_LL_SPI_MASTER_SCR_RESET );
    write_reg( hal_ll_spi_master_reg16( map->base ), 0 );
    write_reg( &hal_ll_hw_reg->sir[ channel ], HAL_LL_SPI_MASTER_SIR_OVCT );
    clear_reg_bit( hal_ll_spi_master_reg8( map->if_reg ), map->if_bit );
}

static void hal_ll_spi_master_hw_init( hal_ll_spi_master_hw_specifics_map_t *map ) {
    volatile hal_ll_spi_master_base_handle_t *hal_ll_hw_reg = hal_ll_spi_master_get_base_struct( map->sau_base );
    uint8_t channel = hal_ll_spi_master_channel( map->module_index );
    uint8_t cks = hal_ll_spi_master_cks( map->module_index );
    // CPOL = 1 means non-reversed clock (CKPmn = 0), CPHA = 0 means data half a clock early (DAPmn = 1).
    bool cpol = ( map->mode >> 1 ) & 1;
    bool cpha = map->mode & 1;
    uint16_t format;
    uint16_t sdr;
    uint8_t prs;

    // SPSm, SMRmn, SCRmn and SDRmn[15:9] may only be written while SEmn = 0.
    hal_ll_spi_master_clear_regs( map );

    sdr = hal_ll_spi_master_set_bit_rate( map, &prs );

    // Only this channel's own CKm0/CKm1 nibble, left alone if a sibling channel already set it.
    if ( ( ( read_reg( &hal_ll_hw_reg->sps ) >> ( cks << 2 ) ) & HAL_LL_SPI_MASTER_PRS_MASK ) != prs ) {
        clear_reg_bits( &hal_ll_hw_reg->sps, ( uint16_t )( HAL_LL_SPI_MASTER_PRS_MASK << ( cks << 2 ) ) );
        set_reg_bits( &hal_ll_hw_reg->sps, ( uint16_t )( prs << ( cks << 2 ) ) );
    }

    write_reg( &hal_ll_hw_reg->smr[ channel ], ( cks << HAL_LL_SPI_MASTER_SMR_CKS ) | HAL_LL_SPI_MASTER_SMR_FIXED );

    // Transmission/reception, MSB first, 8-bit data, no stop bit (R01UH1082 Figure 19-42).
    format = HAL_LL_SPI_MASTER_SCR_TXE | HAL_LL_SPI_MASTER_SCR_RXE |
             HAL_LL_SPI_MASTER_SCR_FIXED | HAL_LL_SPI_MASTER_SCR_DLS_8_BITS;
    if ( !cpol ) {
        format |= HAL_LL_SPI_MASTER_SCR_CKP;
    }
    if ( !cpha ) {
        format |= HAL_LL_SPI_MASTER_SCR_DAP;
    }
    write_reg( &hal_ll_hw_reg->scr[ channel ], format );

    // 16-bit write while stopped, an 8-bit write would clear SDRmn[15:9].
    write_reg( hal_ll_spi_master_reg16( map->base ), sdr << HAL_LL_SPI_MASTER_SDR_DIV_SHIFT );

    // Clock idles at the CPOL level, data line idles high.
    if ( cpol ) {
        set_reg_bit( &hal_ll_hw_reg->so, channel + HAL_LL_SPI_MASTER_SO_CKO_SHIFT );
    } else {
        clear_reg_bit( &hal_ll_hw_reg->so, channel + HAL_LL_SPI_MASTER_SO_CKO_SHIFT );
    }
    set_reg_bit( &hal_ll_hw_reg->so, channel );
    clear_reg_bit( &hal_ll_hw_reg->sol, channel );
    set_reg_bit( &hal_ll_hw_reg->soe, channel );

    write_reg( &hal_ll_hw_reg->ss, ( 1U << channel ) );
}

static void hal_ll_spi_master_init( hal_ll_spi_master_hw_specifics_map_t *map ) {

    hal_ll_spi_master_module_enable( map, true );

    hal_ll_spi_master_alternate_functions_set_state( map, true );

    hal_ll_spi_master_hw_init( map );
}

// ------------------------------------------------------------------------- END
