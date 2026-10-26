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

#include "hal_ll_uart.h"
#include "hal_ll_gpio.h"
#include "hal_ll_core.h"
#include "hal_ll_per.h"
#include "hal_ll_core_defines.h"
#include "hal_ll_uart_pin_map.h"
#include "hal_ll_pior_defines.h"

/*!< @brief Local handle list */
static volatile hal_ll_uart_handle_register_t hal_ll_module_state[ UART_MODULE_COUNT ] = { (handle_t *)NULL, (handle_t *)NULL, false };

// ------------------------------------------------------------- PRIVATE MACROS
/*!< @brief Helper macro for getting hal_ll_module_state address. */
#define hal_ll_uart_get_module_state_address ((hal_ll_uart_handle_register_t *)*handle)
/*!< @brief Helper macro for getting module specific control register structure base address. */
#define hal_ll_uart_get_handle (hal_ll_uart_handle_register_t *)hal_ll_uart_get_module_state_address->hal_ll_uart_handle
/*!< @brief Helper macro for getting module specific control register structure. */
#define hal_ll_uart_get_base_struct(_handle) ((volatile hal_ll_uart_base_handle_t *)_handle)
/*!< @brief Helper macro for getting module specific base address directly from HAL layer handle. */
#define hal_ll_uart_get_base_from_hal_handle ((hal_ll_uart_hw_specifics_map_t *)((hal_ll_uart_handle_register_t *)\
                                             (((hal_ll_uart_handle_register_t *)(handle))->hal_ll_uart_handle))->hal_ll_uart_handle)->base

/*!< @brief Volatile register accessors, the bit control macros don't add volatile themselves. */
#define hal_ll_uart_reg8(_addr)         ( ( volatile uint8_t * )( _addr ) )
#define hal_ll_uart_reg16(_addr)        ( ( volatile uint16_t * )( _addr ) )

/*!< @brief CPU/peripheral clock (fCLK) feeding the SAU prescaler. */
#ifndef HAL_LL_UART_FCLK_HZ
#define HAL_LL_UART_FCLK_HZ             ( ( uint32_t )Get_Fosc_kHz() * 1000UL )
#endif

/*!< @brief Register addresses outside of the SAU unit block. */
#define HAL_LL_UART_PER0_ADDR           ( 0xF00F0UL )
#define HAL_LL_UART_PRR0_ADDR           ( 0xF00F1UL )
#define HAL_LL_UART_NFEN0_ADDR          ( 0xF0070UL )

/*!< @brief Receive data registers, SDRm1/SDRm3 (RXDq). */
#define HAL_LL_UART0_RX_DATA_ADDR       ( 0xFFF12UL ) // SDR01
#define HAL_LL_UART1_RX_DATA_ADDR       ( 0xFFF46UL ) // SDR03
#define HAL_LL_UART2_RX_DATA_ADDR       ( 0xFFF4AUL ) // SDR11
#define HAL_LL_UART3_RX_DATA_ADDR       ( 0xFFF16UL ) // SDR13

/*!< @brief UARTq uses channels 2*(q%2) (TX) and 2*(q%2)+1 (RX) of SAU q/2. */
#define hal_ll_uart_unit(_index)        ( ( _index ) >> 1 )
#define hal_ll_uart_tx_channel(_index)  ( ( ( _index ) & 1 ) << 1 )
#define hal_ll_uart_rx_channel(_index)  ( hal_ll_uart_tx_channel( _index ) + 1 )
/*!< @brief Each UART owns one SPSm prescaler (CKm0 for UART0/2, CKm1 for UART1/3). */
#define hal_ll_uart_cks(_index)         ( ( _index ) & 1 )
/*!< @brief PIOR10 routes SAU0, PIOR11 routes SAU1; UART0/2 use bits 1:0, UART1/3 bits 5:4. */
#define hal_ll_uart_pior_reg(_index)    ( 10 + hal_ll_uart_unit( _index ) )
#define hal_ll_uart_pior_shift(_index)  ( ( ( _index ) & 1 ) << 2 )
#define HAL_LL_UART_PIOR_WIDTH          ( 2 )
/*!< @brief NFEN0 SNFENq0 bit for RxDq. */
#define hal_ll_uart_nfen_bit(_index)    ( ( _index ) << 1 )

/*!< @brief SMRmn bits. */
#define HAL_LL_UART_SMR_CKS             ( 15 )
#define HAL_LL_UART_SMR_STS             ( 0x0100U )
#define HAL_LL_UART_SMR_FIXED           ( 0x0020U ) // Bit 5 must be 1.
#define HAL_LL_UART_SMR_MD_UART         ( 0x0002U )
#define HAL_LL_UART_SMR_RESET           ( 0x0020U )

/*!< @brief SCRmn bits. */
#define HAL_LL_UART_SCR_TXE             ( 0x8000U )
#define HAL_LL_UART_SCR_RXE             ( 0x4000U )
#define HAL_LL_UART_SCR_PTC_SHIFT       ( 8 )
#define HAL_LL_UART_SCR_DIR_LSB         ( 0x0080U )
#define HAL_LL_UART_SCR_SLC_SHIFT       ( 4 )
#define HAL_LL_UART_SCR_FIXED           ( 0x0004U ) // Bit 2 must be 1.
#define HAL_LL_UART_SCR_RESET           ( 0x0087U )

#define HAL_LL_UART_PTC_NONE            ( 0 )
#define HAL_LL_UART_PTC_EVEN            ( 2 )
#define HAL_LL_UART_PTC_ODD             ( 3 )
#define HAL_LL_UART_SLC_1_BIT           ( 1 )
#define HAL_LL_UART_SLC_2_BITS          ( 2 )
#define HAL_LL_UART_DLS_9_BITS          ( 1 )
#define HAL_LL_UART_DLS_7_BITS          ( 2 )
#define HAL_LL_UART_DLS_8_BITS          ( 3 )

/*!< @brief SSRmn bits. */
#define HAL_LL_UART_SSR_TSF             ( 6 )
#define HAL_LL_UART_SSR_BFF             ( 5 )
#define HAL_LL_UART_SSR_ERR_MASK        ( 0x0007U ) // FEF, PEF, OVF; SIRmn uses the same positions.

/*!< @brief SDRmn[15:9] transfer clock divider, UART allows 2..127. */
#define HAL_LL_UART_SDR_DIV_SHIFT       ( 9 )
#define HAL_LL_UART_SDR_DIV_MIN         ( 2 )
#define HAL_LL_UART_SDR_DIV_MAX         ( 127 )
#define HAL_LL_UART_PRS_MAX             ( 15 )

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
} hal_ll_uart_base_handle_t;

/*!< @brief UART baud rate structure. */
typedef struct {
    uint32_t baud;
    uint32_t real_baud;
} hal_ll_uart_baud_t;

/*!< @brief UART hw specific structure. */
typedef struct {
    hal_ll_base_addr_t base;          /*!< TX data register (SDRm0/SDRm2), identifies the module. */
    hal_ll_base_addr_t rx_data;       /*!< RX data register (SDRm1/SDRm3). */
    hal_ll_base_addr_t sau_base;      /*!< SAU unit register block. */
    hal_ll_pin_name_t module_index;
    hal_ll_uart_pins_t pins;
    uint8_t pior_value;
    hal_ll_uart_baud_t baud_rate;
    hal_ll_uart_parity_t parity;
    hal_ll_uart_stop_bits_t stop_bit;
    hal_ll_uart_data_bits_t data_bit;
    uint32_t timeout_polling_write;
} hal_ll_uart_hw_specifics_map_t;

/*!< @brief UART hw specific error values. */
typedef enum {
    HAL_LL_UART_SUCCESS = 0,
    HAL_LL_UART_WRONG_PINS,
    HAL_LL_UART_MODULE_ERROR,

    HAL_LL_UART_ERROR = (-1)
} hal_ll_uart_err_t;

/*!< @brief UART hw specific module values. */
typedef struct {
    uint16_t pin_tx;
    uint16_t pin_rx;
} hal_ll_uart_pin_id;

/*!< @brief UART module state selection. */
typedef enum {
    HAL_LL_UART_DISABLE = 0,
    HAL_LL_UART_ENABLE
} hal_ll_uart_state_t;

// ------------------------------------------------------------------ VARIABLES
/*!< @brief UART hardware specific info. */
static hal_ll_uart_hw_specifics_map_t hal_ll_uart_hw_specifics_map[ UART_MODULE_COUNT + 1 ] = {
    #ifdef UART_MODULE_0
    {HAL_LL_UART0_BASE_ADDR, HAL_LL_UART0_RX_DATA_ADDR, HAL_LL_SAU0_BASE_ADDR, hal_ll_uart_module_num( UART_MODULE_0 ),
     {HAL_LL_PIN_NC, HAL_LL_PIN_NC}, 0, {115200, 0}, HAL_LL_UART_PARITY_DEFAULT, HAL_LL_UART_STOP_BITS_DEFAULT, HAL_LL_UART_DATA_BITS_DEFAULT, 10000},
    #endif
    #ifdef UART_MODULE_1
    {HAL_LL_UART1_BASE_ADDR, HAL_LL_UART1_RX_DATA_ADDR, HAL_LL_SAU0_BASE_ADDR, hal_ll_uart_module_num( UART_MODULE_1 ),
     {HAL_LL_PIN_NC, HAL_LL_PIN_NC}, 0, {115200, 0}, HAL_LL_UART_PARITY_DEFAULT, HAL_LL_UART_STOP_BITS_DEFAULT, HAL_LL_UART_DATA_BITS_DEFAULT, 10000},
    #endif
    #ifdef UART_MODULE_2
    {HAL_LL_UART2_BASE_ADDR, HAL_LL_UART2_RX_DATA_ADDR, HAL_LL_SAU1_BASE_ADDR, hal_ll_uart_module_num( UART_MODULE_2 ),
     {HAL_LL_PIN_NC, HAL_LL_PIN_NC}, 0, {115200, 0}, HAL_LL_UART_PARITY_DEFAULT, HAL_LL_UART_STOP_BITS_DEFAULT, HAL_LL_UART_DATA_BITS_DEFAULT, 10000},
    #endif
    #ifdef UART_MODULE_3
    {HAL_LL_UART3_BASE_ADDR, HAL_LL_UART3_RX_DATA_ADDR, HAL_LL_SAU1_BASE_ADDR, hal_ll_uart_module_num( UART_MODULE_3 ),
     {HAL_LL_PIN_NC, HAL_LL_PIN_NC}, 0, {115200, 0}, HAL_LL_UART_PARITY_DEFAULT, HAL_LL_UART_STOP_BITS_DEFAULT, HAL_LL_UART_DATA_BITS_DEFAULT, 10000},
    #endif

    {HAL_LL_MODULE_ERROR, HAL_LL_MODULE_ERROR, HAL_LL_MODULE_ERROR, HAL_LL_MODULE_ERROR,
     {HAL_LL_PIN_NC, HAL_LL_PIN_NC}, 0, {0, 0}, HAL_LL_MODULE_ERROR, HAL_LL_MODULE_ERROR, HAL_LL_MODULE_ERROR, 10000}
};

/*!< @brief Global handle variables used in functions. */
static volatile hal_ll_uart_handle_register_t *low_level_handle;
static volatile hal_ll_uart_hw_specifics_map_t *hal_ll_uart_hw_specifics_map_local;

/*!< @brief Global interrupt handlers used in functions. */
static hal_ll_uart_isr_t irq_handler;
static handle_t objects[UART_MODULE_COUNT];

// ---------------------------------------------- PRIVATE FUNCTION DECLARATIONS
/**
  * @brief  Check if pins are adequate.
  *
  * Checks tx and rx pins the user has passed with pre-defined
  * pins in tx and rx maps. Take into consideration that module
  * index numbers and PIOR values have to be the same for both pins,
  * since one PIOR field routes both TxDq and RxDq.
  *
  * @param[in]  tx_pin - TX pre-defined pin name.
  * @param[in]  rx_pin - RX pre-defined pin name.
  * @param[in]  *index_list - Array containing map index numbers.
  * @return hal_ll_pin_name_t Module index based on pins.
  *
  * Returns pre-defined module index from pin maps, if pins
  * are adequate.
  */
static hal_ll_pin_name_t hal_ll_uart_check_pins( hal_ll_pin_name_t tx_pin, hal_ll_pin_name_t rx_pin, hal_ll_uart_pin_id *index_list, hal_ll_uart_handle_register_t *handle_map );

/**
 * @brief  Maps new-found module specific values.
 *
 * Maps pin names and PIOR value for
 * TX and RX pins.
 *
 * @param[in]  module_index UART HW module index -- 0,1,2...
 * @param[in]  *index_list  Array with TX and RX map index values
 *                          and module number
 *
 * @return  None
 */
static void hal_ll_uart_map_pins( uint8_t module_index, hal_ll_uart_pin_id *index_list );

/**
  * @brief  Sets UART pin alternate function state.
  *
  * Routes TxDq/RxDq through PIOR10/PIOR11 and configures
  * pin directions. TX output latch is left high, since
  * the pin outputs the latch ANDed with the serial output.
  *
  * @param[in]  map - Object specific context handler.
  * @param[in]  hal_ll_state - Init/De-init
  *
  * @return void None.
  */
static void hal_ll_uart_alternate_functions_set_state( hal_ll_uart_hw_specifics_map_t *map, bool hal_ll_state );

/**
  * @brief  Get local hardware specific map.
  *
  * Checks handle value and returns address of adequate
  * hal_ll_uart_hw_specifics_map array index.
  *
  * @param[in]  handle - Object specific context handler.
  * @return hal_ll_uart_hw_specifics_map_t Map address.
  *
  * Returns pre-defined map index address based on handle value,
  * if handle is adequate.
  */
static hal_ll_uart_hw_specifics_map_t *hal_ll_get_specifics( handle_t handle );

/**
  * @brief  Enable clock for UART module on hardware level.
  *
  * Releases the SAU unit from reset and supplies its clock.
  * On disable, the unit clock is only stopped if no other
  * channel of the unit is still running.
  *
  * @param[in]  map - Object specific context handler.
  * @param[in]  hal_ll_stat - True(enable clock)/False(disable clock).
  *
  * @return void None.
  */
static void hal_ll_uart_set_clock( hal_ll_uart_hw_specifics_map_t *map, bool hal_ll_state );

/**
  * @brief  Finds UART module index.
  *
  * Finds UART index(module number) based on
  * handle value.
  *
  * @param[in]  handle - Object specific context handler.
  *
  * @return uint8_t Module number.
  * Returns values from 0 to 3.
  */
static uint8_t hal_ll_uart_find_index( handle_t *handle );

/**
  * @brief  Clears UART registers.
  *
  * Stops both UART channels and returns their
  * configuration registers to reset values.
  *
  * @param[in]  map - Object specific context handler.
  *
  * @return void None.
  */
static void hal_ll_uart_clear_regs( hal_ll_uart_hw_specifics_map_t *map );

/**
 * @brief  Calculates prescaler and divider for desired baud rate.
 *
 * Picks the lowest SPSm prescaler for which SDRmn[15:9]
 * fits, which gives the finest divider resolution.
 * Stores the achieved baud rate in the map.
 *
 * @param[in]  map - Object specific context handler.
 * @param[out] prs - SPSm prescaler value (fMCK = fCLK / 2^prs).
 *
 * @return uint16_t SDRmn[15:9] value, 0 if baud rate can't be reached.
 */
static uint16_t hal_ll_uart_set_baud_bare_metal( hal_ll_uart_hw_specifics_map_t *map, uint8_t *prs );

/**
 * @brief  Gets stop bit setting.
 *
 * @param[in]  map - Object specific context handler.
 *
 * @return uint16_t SLCmn field value for the TX channel.
 */
static uint16_t hal_ll_uart_set_stop_bits_bare_metal( hal_ll_uart_hw_specifics_map_t *map );

/**
 * @brief  Gets data bit setting.
 *
 * @param[in]  map - Object specific context handler.
 *
 * @return uint16_t DLSmn field value.
 */
static uint16_t hal_ll_uart_set_data_bits_bare_metal( hal_ll_uart_hw_specifics_map_t *map );

/**
 * @brief  Gets parity setting.
 *
 * @param[in]  map - Object specific context handler.
 *
 * @return uint16_t PTCmn field value.
 */
static uint16_t hal_ll_uart_set_parity_bare_metal( hal_ll_uart_hw_specifics_map_t *map );

/**
 * @brief  Starts or stops both UART channels.
 *
 * @param[in]  map - Object specific context handler.
 * @param[in]  pin_state - Enable/disable.
 *
 * @return void None.
 */
static void hal_ll_uart_set_module( hal_ll_uart_hw_specifics_map_t *map, hal_ll_uart_state_t pin_state );

/**
 * @brief  Initialize UART module.
 *
 * Enables SAU unit clock first.
 * Sets pin alternate function state.
 * Initializes specific UART module.
 *
 * @param[in]  map - Object specific context handler.
 *
 * @return void None.
 */
static void hal_ll_uart_init( hal_ll_uart_hw_specifics_map_t *map );

/**
 * @brief  Initialize UART module on the hardware level.
 *
 * Performs UART module initialization on
 * the hardware level (R01UH1082 Figure 19-77 and 19-85).
 *
 * Procedure:
 * 1. Stops both channels
 * 2. Sets prescaler and baud rate divider
 * 3. Sets mode, data bits, parity and stop bits
 * 4. Enables RX noise filter
 * 5. Sets TX idle level and enables serial output
 * 6. Starts both channels
 *
 * @param[in]  map - Object specific context handler.
 *
 * @return void None.
 */
static void hal_ll_uart_hw_init( hal_ll_uart_hw_specifics_map_t *map );

// ------------------------------------------------ PUBLIC FUNCTION DEFINITIONS
hal_ll_err_t hal_ll_uart_register_handle( hal_ll_pin_name_t tx_pin, hal_ll_pin_name_t rx_pin, hal_ll_uart_handle_register_t *handle_map, uint8_t *hal_module_id ) {
    hal_ll_uart_pin_id index_list[UART_MODULE_COUNT] = {HAL_LL_PIN_NC,HAL_LL_PIN_NC};
    uint16_t pin_check_result;

    // Check if pins are valid.
    if ( (pin_check_result = hal_ll_uart_check_pins( tx_pin, rx_pin, index_list, handle_map )) == HAL_LL_PIN_NC ) {
        return HAL_LL_UART_WRONG_PINS;
    };

    if ( (hal_ll_uart_hw_specifics_map[pin_check_result].pins.tx_pin != tx_pin) ||
         (hal_ll_uart_hw_specifics_map[pin_check_result].pins.rx_pin != rx_pin) )
    {
        hal_ll_uart_alternate_functions_set_state( &hal_ll_uart_hw_specifics_map[ pin_check_result ], false );

        hal_ll_uart_map_pins( pin_check_result, index_list );

        hal_ll_uart_alternate_functions_set_state( &hal_ll_uart_hw_specifics_map[ pin_check_result ], true );

        handle_map[pin_check_result].init_ll_state = false;
    }

    *hal_module_id = pin_check_result;

    hal_ll_module_state[pin_check_result].hal_ll_uart_handle = (handle_t *)&hal_ll_uart_hw_specifics_map[pin_check_result].base;

    handle_map[pin_check_result].hal_ll_uart_handle = (handle_t *)&hal_ll_module_state[pin_check_result].hal_ll_uart_handle;

    return HAL_LL_UART_SUCCESS;
}

hal_ll_err_t hal_ll_module_configure_uart( handle_t *handle ) {
    hal_ll_uart_hw_specifics_map_local = hal_ll_get_specifics( hal_ll_uart_get_module_state_address );
    hal_ll_uart_handle_register_t *hal_handle = ( hal_ll_uart_handle_register_t * )*handle;
    uint8_t pin_check_result = hal_ll_uart_hw_specifics_map_local->module_index;

    hal_ll_uart_init( hal_ll_uart_hw_specifics_map_local );

    hal_ll_module_state[pin_check_result].hal_ll_uart_handle = ( handle_t * )&hal_ll_uart_hw_specifics_map[pin_check_result].base;
    hal_ll_module_state[pin_check_result].init_ll_state = true;
    hal_handle->init_ll_state = true;

    return HAL_LL_UART_SUCCESS;
}

hal_ll_err_t hal_ll_uart_set_baud( handle_t *handle, uint32_t baud ) {
    low_level_handle = hal_ll_uart_get_handle;
    hal_ll_uart_hw_specifics_map_local = hal_ll_get_specifics( hal_ll_uart_get_module_state_address );

    low_level_handle->init_ll_state = false;

    hal_ll_uart_hw_specifics_map_local->baud_rate.baud = baud;

    hal_ll_uart_init( hal_ll_uart_hw_specifics_map_local );

    low_level_handle->init_ll_state = true;

    return hal_ll_uart_hw_specifics_map_local->baud_rate.real_baud;
}

hal_ll_err_t hal_ll_uart_set_parity( handle_t *handle, hal_ll_uart_parity_t parity ) {
    low_level_handle = hal_ll_uart_get_handle;
    hal_ll_uart_hw_specifics_map_local = hal_ll_get_specifics( hal_ll_uart_get_module_state_address );

    low_level_handle->init_ll_state = false;

    hal_ll_uart_hw_specifics_map_local->parity = parity;

    hal_ll_uart_init( hal_ll_uart_hw_specifics_map_local );

    low_level_handle->init_ll_state = true;

    return HAL_LL_UART_SUCCESS;
}

hal_ll_err_t hal_ll_uart_set_stop_bits( handle_t *handle, hal_ll_uart_stop_bits_t stop_bit ) {
    low_level_handle = hal_ll_uart_get_handle;
    hal_ll_uart_hw_specifics_map_local = hal_ll_get_specifics( hal_ll_uart_get_module_state_address );

    // SAU UART only supports 1 or 2 stop bits.
    if ( ( HAL_LL_UART_STOP_BITS_ONE != stop_bit ) && ( HAL_LL_UART_STOP_BITS_TWO != stop_bit ) ) {
        return HAL_LL_UART_MODULE_ERROR;
    }

    low_level_handle->init_ll_state = false;

    hal_ll_uart_hw_specifics_map_local->stop_bit = stop_bit;

    hal_ll_uart_init( hal_ll_uart_hw_specifics_map_local );

    low_level_handle->init_ll_state = true;

    return HAL_LL_UART_SUCCESS;
}

hal_ll_err_t hal_ll_uart_set_data_bits( handle_t *handle, hal_ll_uart_data_bits_t data_bit ) {
    low_level_handle = hal_ll_uart_get_handle;
    hal_ll_uart_hw_specifics_map_local = hal_ll_get_specifics( hal_ll_uart_get_module_state_address );

    // SAU UART supports 7, 8 and 9 bit data, 9 bit only on UART0 and UART2.
    if ( ( data_bit < HAL_LL_UART_DATA_BITS_7 ) || ( data_bit > HAL_LL_UART_DATA_BITS_9 ) ) {
        return HAL_LL_UART_MODULE_ERROR;
    }

    if ( ( HAL_LL_UART_DATA_BITS_9 == data_bit ) && ( hal_ll_uart_hw_specifics_map_local->module_index & 1 ) ) {
        return HAL_LL_UART_MODULE_ERROR;
    }

    low_level_handle->init_ll_state = false;

    hal_ll_uart_hw_specifics_map_local->data_bit = data_bit;

    hal_ll_uart_init( hal_ll_uart_hw_specifics_map_local );

    low_level_handle->init_ll_state = true;

    return HAL_LL_UART_SUCCESS;
}

void hal_ll_uart_set_polling_write_timeout( handle_t *handle, uint32_t timeout ) {
    hal_ll_uart_hw_specifics_map_local = hal_ll_get_specifics( hal_ll_uart_get_module_state_address );

    if( hal_ll_uart_hw_specifics_map_local->base != HAL_LL_MODULE_ERROR ) {
        hal_ll_uart_hw_specifics_map_local->timeout_polling_write = timeout;
    }
}

void hal_ll_uart_close( handle_t *handle ) {
    low_level_handle = hal_ll_uart_get_handle;
    hal_ll_uart_hw_specifics_map_local = hal_ll_get_specifics( hal_ll_uart_get_module_state_address );

    if( low_level_handle->hal_ll_uart_handle != NULL ) {
        hal_ll_uart_set_clock( hal_ll_uart_hw_specifics_map_local, true );
        hal_ll_uart_alternate_functions_set_state( hal_ll_uart_hw_specifics_map_local, false );

        hal_ll_uart_irq_disable( handle, HAL_LL_UART_IRQ_RX );
        hal_ll_uart_irq_disable( handle, HAL_LL_UART_IRQ_TX );

        hal_ll_uart_clear_regs( hal_ll_uart_hw_specifics_map_local );
        hal_ll_uart_set_clock( hal_ll_uart_hw_specifics_map_local, false );

        hal_ll_uart_hw_specifics_map_local->pins.tx_pin = HAL_LL_PIN_NC;
        hal_ll_uart_hw_specifics_map_local->pins.rx_pin = HAL_LL_PIN_NC;
        hal_ll_uart_hw_specifics_map_local->pior_value = 0;

        hal_ll_uart_hw_specifics_map_local->baud_rate.baud = 115200UL;
        hal_ll_uart_hw_specifics_map_local->baud_rate.real_baud = 0;

        irq_handler = NULL;
        objects[ hal_ll_uart_find_index( handle ) ] = NULL;

        low_level_handle->hal_ll_uart_handle = NULL;
        low_level_handle->hal_drv_uart_handle = NULL;

        low_level_handle->init_ll_state = false;
    }
}

void hal_ll_uart_register_irq_handler( handle_t *handle, hal_ll_uart_isr_t handler, handle_t obj ){
    irq_handler = handler;
    hal_ll_uart_hw_specifics_map_local = hal_ll_get_specifics( hal_ll_uart_get_module_state_address );
    objects[ hal_ll_uart_find_index( handle ) ] = obj;
}

// Interrupts (INTSTq/INTSRq) are not implemented yet, only polling mode is supported.
void hal_ll_uart_irq_enable( handle_t *handle, hal_ll_uart_irq_t irq ) {
    low_level_handle = hal_ll_uart_get_handle;
    hal_ll_uart_hw_specifics_map_local = hal_ll_get_specifics( hal_ll_uart_get_module_state_address );
}

void hal_ll_uart_irq_disable( handle_t *handle, hal_ll_uart_irq_t irq ) {
    low_level_handle = hal_ll_uart_get_handle;
    hal_ll_uart_hw_specifics_map_local = hal_ll_get_specifics( hal_ll_uart_get_module_state_address );
}

void hal_ll_uart_write( handle_t *handle, uint8_t wr_data ) {
    hal_ll_uart_hw_specifics_map_local = hal_ll_get_specifics( hal_ll_uart_get_module_state_address );

    // While the channel runs, only SDRmn[8:0] is written.
    write_reg( hal_ll_uart_reg16( hal_ll_uart_hw_specifics_map_local->base ), wr_data );
}

void hal_ll_uart_write_polling( handle_t *handle, uint8_t wr_data ) {
    hal_ll_uart_hw_specifics_map_local = hal_ll_get_specifics( hal_ll_uart_get_module_state_address );
    volatile hal_ll_uart_base_handle_t *hal_ll_hw_reg = hal_ll_uart_get_base_struct( hal_ll_uart_hw_specifics_map_local->sau_base );
    uint8_t tx_channel = hal_ll_uart_tx_channel( hal_ll_uart_hw_specifics_map_local->module_index );
    uint32_t time_counter = hal_ll_uart_hw_specifics_map_local->timeout_polling_write;

    // Writing SDRmn while BFFmn = 1 overwrites the pending byte, wait for the buffer to drain.
    while ( check_reg_bit( &hal_ll_hw_reg->ssr[ tx_channel ], HAL_LL_UART_SSR_BFF ) ) {
        // Timeout check.
        if( !time_counter-- ) {
            return;
        }
    }

    write_reg( hal_ll_uart_reg16( hal_ll_uart_hw_specifics_map_local->base ), wr_data );
}

uint8_t hal_ll_uart_read( handle_t *handle ) {
    hal_ll_uart_hw_specifics_map_local = hal_ll_get_specifics( hal_ll_uart_get_module_state_address );
    uint8_t rd_data;

    rd_data = ( uint8_t )read_reg( hal_ll_uart_reg16( hal_ll_uart_hw_specifics_map_local->rx_data ) );

    return rd_data;
}

uint8_t hal_ll_uart_read_polling( handle_t *handle ) {
    hal_ll_uart_hw_specifics_map_local = hal_ll_get_specifics( hal_ll_uart_get_module_state_address );
    volatile hal_ll_uart_base_handle_t *hal_ll_hw_reg = hal_ll_uart_get_base_struct( hal_ll_uart_hw_specifics_map_local->sau_base );
    uint8_t rx_channel = hal_ll_uart_rx_channel( hal_ll_uart_hw_specifics_map_local->module_index );
    uint8_t read_data;
    uint16_t errors;

    // BFFmn is set on reception and on a reception error.
    while ( !check_reg_bit( &hal_ll_hw_reg->ssr[ rx_channel ], HAL_LL_UART_SSR_BFF ) );

    // Read SDRmn first so the next frame can't overrun while the error is handled (Table 19-7).
    read_data = ( uint8_t )read_reg( hal_ll_uart_reg16( hal_ll_uart_hw_specifics_map_local->rx_data ) );

    errors = read_reg_bits( &hal_ll_hw_reg->ssr[ rx_channel ], HAL_LL_UART_SSR_ERR_MASK );
    if ( errors ) {
        write_reg( &hal_ll_hw_reg->sir[ rx_channel ], errors );
    }

    return read_data;
}

// ------------------------------------------------------------- DEFAULT EXCEPTION HANDLERS


// ----------------------------------------------- PRIVATE FUNCTION DEFINITIONS
static uint8_t hal_ll_uart_find_index( handle_t *handle ) {
    hal_ll_uart_hw_specifics_map_local = hal_ll_get_specifics( hal_ll_uart_get_module_state_address );

    if( hal_ll_uart_hw_specifics_map_local->base != HAL_LL_MODULE_ERROR ) {
        return hal_ll_uart_hw_specifics_map_local->module_index;
    } else {
        return NULL;
    }
}

static hal_ll_pin_name_t hal_ll_uart_check_pins( hal_ll_pin_name_t tx_pin, hal_ll_pin_name_t rx_pin, hal_ll_uart_pin_id *index_list, hal_ll_uart_handle_register_t *handle_map ) {
    static const uint16_t tx_map_size = ( sizeof( hal_ll_uart_tx_map ) / sizeof( hal_ll_uart_pin_map_t ) );
    static const uint16_t rx_map_size = ( sizeof( hal_ll_uart_rx_map ) / sizeof( hal_ll_uart_pin_map_t ) );
    uint8_t hal_ll_module_id = 0;
    uint8_t index_counter = 0;
    uint16_t tx_index;
    uint16_t rx_index;

    if (( HAL_LL_PIN_NC == tx_pin ) || ( HAL_LL_PIN_NC == rx_pin )) {
        return HAL_LL_PIN_NC;
    }

    for ( tx_index = 0; tx_index < tx_map_size; tx_index++ ) {
        if ( hal_ll_uart_tx_map[ tx_index ].pin == tx_pin ) {
            for ( rx_index = 0; rx_index < rx_map_size; rx_index++ ) {
                if ( hal_ll_uart_rx_map[ rx_index ].pin == rx_pin ) {
                    // One PIOR field routes both directions, so the pair must share it.
                    if ( ( hal_ll_uart_tx_map[ tx_index ].base == hal_ll_uart_rx_map[ rx_index ].base ) &&
                         ( hal_ll_uart_tx_map[ tx_index ].af == hal_ll_uart_rx_map[ rx_index ].af ) ) {
                        // Get module number.
                        hal_ll_module_id = hal_ll_uart_tx_map[ tx_index ].module_index;

                        // Map module number to map index
                        for ( uint8_t map_member = 0; map_member < UART_MODULE_COUNT + 1; map_member++  ) {
                            if ( hal_ll_uart_hw_specifics_map[map_member].module_index ==  hal_ll_module_id ) {
                                hal_ll_module_id = map_member;
                                break;
                            }
                        }

                        // Map pin names.
                        index_list[hal_ll_module_id].pin_tx = tx_index;
                        index_list[hal_ll_module_id].pin_rx = rx_index;

                        // Check if module is taken.
                        if ( NULL == handle_map[ hal_ll_module_id ].hal_drv_uart_handle ) {
                            return hal_ll_module_id;
                        } else if ( UART_MODULE_COUNT == ++index_counter ) {
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

static hal_ll_uart_hw_specifics_map_t *hal_ll_get_specifics( handle_t handle ) {
    uint8_t hal_ll_module_count = sizeof( hal_ll_module_state ) / ( sizeof( hal_ll_uart_handle_register_t ));
    static uint8_t hal_ll_module_error = sizeof( hal_ll_module_state ) / ( sizeof( hal_ll_uart_handle_register_t ));

    while( hal_ll_module_count-- ) {
        if ( hal_ll_uart_get_base_from_hal_handle == hal_ll_uart_hw_specifics_map[hal_ll_module_count].base ) {
            return &hal_ll_uart_hw_specifics_map[hal_ll_module_count];
        }
    }

    return &hal_ll_uart_hw_specifics_map[hal_ll_module_error];
}

static void hal_ll_uart_set_clock( hal_ll_uart_hw_specifics_map_t *map, bool hal_ll_state ) {
    volatile hal_ll_uart_base_handle_t *hal_ll_hw_reg = hal_ll_uart_get_base_struct( map->sau_base );
    uint8_t per0_bit = PER0_SAU0EN_POS + hal_ll_uart_unit( map->module_index );

    if ( hal_ll_state ) {
        // SAUmRES shares the PER0 bit position in PRR0.
        clear_reg_bit( hal_ll_uart_reg8( HAL_LL_UART_PRR0_ADDR ), per0_bit );
        set_reg_bit( hal_ll_uart_reg8( HAL_LL_UART_PER0_ADDR ), per0_bit );
    } else if ( !read_reg( &hal_ll_hw_reg->se ) ) {
        // The other UART/CSI/IIC channels of this unit share the clock, keep it while any of them run.
        clear_reg_bit( hal_ll_uart_reg8( HAL_LL_UART_PER0_ADDR ), per0_bit );
    }
}

static void hal_ll_uart_map_pins( uint8_t module_index, hal_ll_uart_pin_id *index_list ) {
    // Map new pins.
    hal_ll_uart_hw_specifics_map[module_index].pins.tx_pin = hal_ll_uart_tx_map[index_list[module_index].pin_tx].pin;
    hal_ll_uart_hw_specifics_map[module_index].pins.rx_pin = hal_ll_uart_rx_map[index_list[module_index].pin_rx].pin;
    // TX and RX share the PIOR value, checked in hal_ll_uart_check_pins.
    hal_ll_uart_hw_specifics_map[module_index].pior_value = hal_ll_uart_tx_map[index_list[module_index].pin_tx].af;
}

static void hal_ll_uart_alternate_functions_set_state( hal_ll_uart_hw_specifics_map_t *map, bool hal_ll_state ) {
    module_struct module;
    hal_ll_pin_name_t tx_pin = map->pins.tx_pin;

    if (( map->pins.rx_pin != HAL_LL_PIN_NC ) &&
        ( map->pins.tx_pin != HAL_LL_PIN_NC ))
    {
        if ( hal_ll_state ) {
            // Written directly, hal_ll_pior_map() can match a PIOR13 (UARTA) row for the same pin and module index.
            hal_ll_pior_set_field( hal_ll_uart_pior_reg( map->module_index ),
                                   hal_ll_uart_pior_shift( map->module_index ),
                                   HAL_LL_UART_PIOR_WIDTH, map->pior_value );
        }

        module.pins[0] = map->pins.tx_pin;
        module.pins[1] = map->pins.rx_pin;
        module.pins[2] = GPIO_MODULE_STRUCT_END;

        module.configs[0] = GPIO_CFG_DIGITAL_OUTPUT;
        module.configs[1] = GPIO_CFG_DIGITAL_INPUT;
        module.configs[2] = GPIO_MODULE_STRUCT_END;

        hal_ll_gpio_module_struct_init( &module, hal_ll_state );

        if ( hal_ll_state ) {
            // TxDq is the port latch ANDed with the serial output, so the latch must idle high.
            set_reg_bits( hal_ll_uart_reg8( hal_ll_gpio_port_base( hal_ll_gpio_port_index( tx_pin ) ) ),
                          ( uint8_t )hal_ll_gpio_pin_mask( tx_pin ) );
        }
    }
}

static uint16_t hal_ll_uart_set_baud_bare_metal( hal_ll_uart_hw_specifics_map_t *map, uint8_t *prs ) {
    uint32_t baud = map->baud_rate.baud;
    uint32_t fmck;
    uint32_t div;

    map->baud_rate.real_baud = 0;

    if ( !baud ) {
        return 0;
    }

    // Baud = fMCK / (SDRmn[15:9] + 1) / 2, the lowest prescaler that fits keeps the most resolution.
    for ( *prs = 0; *prs <= HAL_LL_UART_PRS_MAX; ( *prs )++ ) {
        fmck = HAL_LL_UART_FCLK_HZ >> *prs;
        div = ( fmck + baud ) / ( 2 * baud ); // Rounded fMCK / (2 * baud).

        if ( ( div - 1 ) <= HAL_LL_UART_SDR_DIV_MAX ) {
            break;
        }
    }

    if ( ( *prs > HAL_LL_UART_PRS_MAX ) || ( div < ( HAL_LL_UART_SDR_DIV_MIN + 1 ) ) ) {
        return 0;
    }

    map->baud_rate.real_baud = fmck / ( 2 * div );

    return ( uint16_t )( div - 1 );
}

static uint16_t hal_ll_uart_set_stop_bits_bare_metal( hal_ll_uart_hw_specifics_map_t *map ) {
    if ( HAL_LL_UART_STOP_BITS_TWO == map->stop_bit ) {
        return HAL_LL_UART_SLC_2_BITS;
    }

    return HAL_LL_UART_SLC_1_BIT;
}

static uint16_t hal_ll_uart_set_data_bits_bare_metal( hal_ll_uart_hw_specifics_map_t *map ) {
    switch ( map->data_bit ) {
        case HAL_LL_UART_DATA_BITS_7:
            return HAL_LL_UART_DLS_7_BITS;
        case HAL_LL_UART_DATA_BITS_9:
            return HAL_LL_UART_DLS_9_BITS;
        default:
            return HAL_LL_UART_DLS_8_BITS;
    }
}

static uint16_t hal_ll_uart_set_parity_bare_metal( hal_ll_uart_hw_specifics_map_t *map ) {
    switch ( map->parity ) {
        case HAL_LL_UART_PARITY_EVEN:
            return HAL_LL_UART_PTC_EVEN;
        case HAL_LL_UART_PARITY_ODD:
            return HAL_LL_UART_PTC_ODD;
        default:
            return HAL_LL_UART_PTC_NONE;
    }
}

static void hal_ll_uart_set_module( hal_ll_uart_hw_specifics_map_t *map, hal_ll_uart_state_t pin_state ) {
    volatile hal_ll_uart_base_handle_t *hal_ll_hw_reg = hal_ll_uart_get_base_struct( map->sau_base );
    uint16_t channels = ( 1U << hal_ll_uart_tx_channel( map->module_index ) ) |
                        ( 1U << hal_ll_uart_rx_channel( map->module_index ) );

    // SSm/STm are trigger registers, other channels are unaffected by zero bits.
    if ( HAL_LL_UART_ENABLE == pin_state ) {
        write_reg( &hal_ll_hw_reg->ss, channels );
    } else {
        write_reg( &hal_ll_hw_reg->st, channels );
    }
}

static void hal_ll_uart_clear_regs( hal_ll_uart_hw_specifics_map_t *map ) {
    volatile hal_ll_uart_base_handle_t *hal_ll_hw_reg = hal_ll_uart_get_base_struct( map->sau_base );
    uint8_t tx_channel = hal_ll_uart_tx_channel( map->module_index );
    uint8_t rx_channel = hal_ll_uart_rx_channel( map->module_index );

    hal_ll_uart_set_module( map, HAL_LL_UART_DISABLE );

    clear_reg_bit( &hal_ll_hw_reg->soe, tx_channel );
    clear_reg_bit( &hal_ll_hw_reg->sol, tx_channel );
    clear_reg_bit( hal_ll_uart_reg8( HAL_LL_UART_NFEN0_ADDR ), hal_ll_uart_nfen_bit( map->module_index ) );

    write_reg( &hal_ll_hw_reg->smr[ tx_channel ], HAL_LL_UART_SMR_RESET );
    write_reg( &hal_ll_hw_reg->smr[ rx_channel ], HAL_LL_UART_SMR_RESET );
    write_reg( &hal_ll_hw_reg->scr[ tx_channel ], HAL_LL_UART_SCR_RESET );
    write_reg( &hal_ll_hw_reg->scr[ rx_channel ], HAL_LL_UART_SCR_RESET );
    write_reg( hal_ll_uart_reg16( map->base ), 0 );
    write_reg( hal_ll_uart_reg16( map->rx_data ), 0 );
    write_reg( &hal_ll_hw_reg->sir[ rx_channel ], HAL_LL_UART_SSR_ERR_MASK );
}

static void hal_ll_uart_hw_init( hal_ll_uart_hw_specifics_map_t *map ) {
    volatile hal_ll_uart_base_handle_t *hal_ll_hw_reg = hal_ll_uart_get_base_struct( map->sau_base );
    uint8_t tx_channel = hal_ll_uart_tx_channel( map->module_index );
    uint8_t rx_channel = hal_ll_uart_rx_channel( map->module_index );
    uint8_t cks = hal_ll_uart_cks( map->module_index );
    uint16_t format;
    uint16_t sdr;
    uint8_t prs;

    // SPSm, SMRmn, SCRmn, SOLm and SDRmn[15:9] may only be written while SEmn = 0.
    hal_ll_uart_set_module( map, HAL_LL_UART_DISABLE );
    clear_reg_bit( &hal_ll_hw_reg->soe, tx_channel );

    sdr = hal_ll_uart_set_baud_bare_metal( map, &prs );
    if ( !sdr ) {
        return;
    }

    // Only this UART's own CKm0/CKm1 nibble.
    clear_reg_bits( &hal_ll_hw_reg->sps, ( uint16_t )( 0x0FU << ( cks << 2 ) ) );
    set_reg_bits( &hal_ll_hw_reg->sps, ( uint16_t )( prs << ( cks << 2 ) ) );

    // The RX channel's SMR must be set too, with the TX channel in UART transmission mode.
    write_reg( &hal_ll_hw_reg->smr[ tx_channel ], ( cks << HAL_LL_UART_SMR_CKS ) | HAL_LL_UART_SMR_FIXED | HAL_LL_UART_SMR_MD_UART );
    write_reg( &hal_ll_hw_reg->smr[ rx_channel ], ( cks << HAL_LL_UART_SMR_CKS ) | HAL_LL_UART_SMR_STS |
                                                  HAL_LL_UART_SMR_FIXED | HAL_LL_UART_SMR_MD_UART );

    // LSB first, error interrupt masked (EOCmn = 0) for polling.
    format = ( hal_ll_uart_set_parity_bare_metal( map ) << HAL_LL_UART_SCR_PTC_SHIFT ) |
             HAL_LL_UART_SCR_DIR_LSB | HAL_LL_UART_SCR_FIXED |
             hal_ll_uart_set_data_bits_bare_metal( map );
    write_reg( &hal_ll_hw_reg->scr[ tx_channel ], HAL_LL_UART_SCR_TXE | format |
               ( hal_ll_uart_set_stop_bits_bare_metal( map ) << HAL_LL_UART_SCR_SLC_SHIFT ) );
    // Reception always checks a single stop bit.
    write_reg( &hal_ll_hw_reg->scr[ rx_channel ], HAL_LL_UART_SCR_RXE | format |
               ( HAL_LL_UART_SLC_1_BIT << HAL_LL_UART_SCR_SLC_SHIFT ) );

    // 16-bit writes while stopped, an 8-bit write would clear SDRmn[15:9].
    write_reg( hal_ll_uart_reg16( map->base ), sdr << HAL_LL_UART_SDR_DIV_SHIFT );
    write_reg( hal_ll_uart_reg16( map->rx_data ), sdr << HAL_LL_UART_SDR_DIV_SHIFT );

    set_reg_bit( hal_ll_uart_reg8( HAL_LL_UART_NFEN0_ADDR ), hal_ll_uart_nfen_bit( map->module_index ) );

    // Non-inverted output, idle high before output is handed to the SAU.
    clear_reg_bit( &hal_ll_hw_reg->sol, tx_channel );
    set_reg_bit( &hal_ll_hw_reg->so, tx_channel );
    set_reg_bit( &hal_ll_hw_reg->soe, tx_channel );

    write_reg( &hal_ll_hw_reg->sir[ rx_channel ], HAL_LL_UART_SSR_ERR_MASK );

    // At least 4 fMCK cycles between RXEmn = 1 and SSmn = 1.
    for ( volatile uint32_t wait = ( 4UL << prs ); wait; wait-- );

    hal_ll_uart_set_module( map, HAL_LL_UART_ENABLE );
}

static void hal_ll_uart_init( hal_ll_uart_hw_specifics_map_t *map ) {
    hal_ll_uart_set_clock( map, true );

    hal_ll_uart_alternate_functions_set_state( map, true );

    hal_ll_uart_hw_init( map );
}

// ------------------------------------------------------------------------- END
