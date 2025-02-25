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

#include "hal_ll_pps.h"
#include "hal_ll_gpio.h"
#include "hal_ll_core.h"
#include "hal_ll_uart.h"
#include "hal_ll_uart_pin_map.h"
#include "assembly.h"

/*!< @brief Local handle list */
static volatile hal_ll_uart_handle_register_t hal_ll_module_state[UART_MODULE_COUNT] = { (handle_t *)NULL, (handle_t *)NULL, false };

// ------------------------------------------------------------- PRIVATE MACROS
/*!< @brief Helper macro for getting hal_ll_module_state address */
#define hal_ll_uart_get_module_state_address ((hal_ll_uart_handle_register_t *)*handle)
/*!< @brief Helper macro for getting module specific control register structure base address // first register address */
#define hal_ll_uart_get_handle (hal_ll_uart_handle_register_t *)hal_ll_uart_get_module_state_address->hal_ll_uart_handle
/*!< @brief Helper macro for getting module specific control register structure */
#define hal_ll_uart_get_base_struct(_handle) ((const hal_ll_uart_base_handle_t *)_handle)
/*!< @brief Helper macro for getting module specific base address directly from HAL layer handle */
#define hal_ll_uart_get_base_from_hal_handle ((hal_ll_uart_hw_specifics_map_t *)((hal_ll_uart_handle_register_t *)\
                                             (((hal_ll_uart_handle_register_t *)(handle))->hal_ll_uart_handle))->hal_ll_uart_handle)->base
/*!< @brief Helper macro for getting module specific base address structure directly from HAL layer handle */
#define hal_ll_uart_get_base_handle ((hal_ll_uart_hw_specifics_map_t *)((hal_ll_uart_get_handle)->hal_ll_uart_handle))->base

/*!< @brief Helper macro for UART module sync time */
#define hal_ll_uart_wait_for_sync(_hal_sync_val) while( _hal_sync_val-- ){assembly(nop);}

/*!< @brief Macros used for pin/port manipulation */
#define hal_ll_pin(port_name) (port_name & HAL_LL_NIBBLE_LOW_8BIT)
#define hal_ll_port(port_name) ((port_name & HAL_LL_NIBBLE_HIGH_8BIT) >> 4)

/*!< @brief Macros used for calculating actual baud rate value and error value */
#define HAL_LL_UART_ACCEPTABLE_ERROR (float)1.0
#define hal_ll_get_system_clock (Get_Fosc_kHz()*1000)
#define hal_ll_uart_get_baud(_clock,_baud,_div) (((_clock/(float)_baud)/_div)-1)
#define hal_ll_uart_get_real_baud(_clock,_baud,_div) (_clock/(_div*(_baud+1)))
#define hal_ll_uart_get_baud_error(_baud_real,_baud) (((float)(abs(_baud_real-_baud))/_baud)*100)
#define hal_ll_uart_get_baud_low_nibble(_clock,_baud,_div) ((_hal_uart_get_baud(_clock,_baud,_div) & HAL_LL_NIBBLE_LOW_16BIT))
#define hal_ll_uart_get_baud_high_nibble(_clock,_baud,_div) ((_hal_uart_get_baud(_clock,_baud,_div) & HAL_LL_NIBBLE_HIGH_16BIT)>>8)

/*!< @brief Macros used in hw init */
#define HAL_LL_UART_ON_BIT 7
#define HAL_LL_UART_BRGS_BIT 7
#define HAL_LL_UART_RXEN_BIT 4
#define HAL_LL_UART_TXEN_BIT 5

/*!< @brief Macro used during write/read */
#define HAL_LL_UART_TXMTIF_BIT 7
#define HAL_LL_UART_URXIF_BIT 0

/*!< @brief Stop bits */
#define HAL_LL_UART_STP_STOP_BITS_ONE_AND_A_HALF 4
#define HAL_LL_UART_STP_STOP_BITS_TWO_MASK 0x30

/*!< @brief Bit-mode */
#define HAL_LL_UART_MODE_7_BIT 0
#define HAL_LL_UART_MODE_9_BIT 2

/*!< @brief Parity */
#define HAL_LL_UART_PARITY_ODD_BIT 1
#define HAL_LL_UART_PARITY_EVEN_MASK 0x3

/*!< @brief Macro used for status registed flag check
 * Used in interrupt handlers.
 */
#define hal_ll_uart_get_status_flags(module_num) ( read_reg( hal_ll_uart_regs[ module_num ].uart_ivt_reg_addr ))

/*!< @brief Macro used for module interrupt enabling.
 * Used in interrupt handlers.
 */
#if defined(UART_MODULE_1) && defined(UART_MODULE_2) && \
    defined(UART_MODULE_3) && defined(UART_MODULE_4) && \
    defined(UART_MODULE_5)
#define __HAL_LL_UART_ENABLE_IT(_num,_int) (_num==hal_ll_uart_module_num(UART_MODULE_1))?(set_reg_bit(HAL_LL_PIE_MODULE_UART1_ADDRESS,_int)): \
                                           (_num==hal_ll_uart_module_num(UART_MODULE_2))?(set_reg_bit(HAL_LL_PIE_MODULE_UART2_ADDRESS,_int)): \
                                           (_num==hal_ll_uart_module_num(UART_MODULE_3))?(set_reg_bit(HAL_LL_PIE_MODULE_UART3_ADDRESS,_int)): \
                                           (_num==hal_ll_uart_module_num(UART_MODULE_4))?(set_reg_bit(HAL_LL_PIE_MODULE_UART4_ADDRESS,_int)): \
                                           (set_reg_bit(HAL_LL_PIE_MODULE_UART5_ADDRESS,_int))
#elif defined(UART_MODULE_1) && defined(UART_MODULE_2)
#define __HAL_LL_UART_ENABLE_IT(_num,_int) (_num==hal_ll_uart_module_num(UART_MODULE_1))?(set_reg_bit(HAL_LL_PIE_MODULE_UART1_ADDRESS,_int)): \
                                           (set_reg_bit(HAL_LL_PIE_MODULE_UART2_ADDRESS,_int))
#endif

/*!< @brief Macro used for module interrupt disabling.
 * Used in interrupt handlers.
 */
#if defined(UART_MODULE_1) && defined(UART_MODULE_2) && \
    defined(UART_MODULE_3) && defined(UART_MODULE_4) && \
    defined(UART_MODULE_5)
#define __HAL_LL_UART_DISABLE_IT(_num,_int) (_num==hal_ll_uart_module_num(UART_MODULE_1))?(clear_reg_bit(HAL_LL_PIE_MODULE_UART1_ADDRESS,_int)): \
                                            (_num==hal_ll_uart_module_num(UART_MODULE_2))?(clear_reg_bit(HAL_LL_PIE_MODULE_UART2_ADDRESS,_int)): \
                                            (_num==hal_ll_uart_module_num(UART_MODULE_3))?(clear_reg_bit(HAL_LL_PIE_MODULE_UART3_ADDRESS,_int)): \
                                            (_num==hal_ll_uart_module_num(UART_MODULE_4))?(clear_reg_bit(HAL_LL_PIE_MODULE_UART4_ADDRESS,_int)): \
                                            (clear_reg_bit(HAL_LL_PIE_MODULE_UART5_ADDRESS,_int))
#elif defined(UART_MODULE_1) && defined(UART_MODULE_2)
#define __HAL_LL_UART_DISABLE_IT(_num,_int) (_num==hal_ll_uart_module_num(UART_MODULE_1))?(clear_reg_bit(HAL_LL_PIE_MODULE_UART1_ADDRESS,_int)): \
                                            (clear_reg_bit(HAL_LL_PIE_MODULE_UART2_ADDRESS,_int))
#endif

/*!< @brief Macro used for module interrupt source check.
 * Used in interrupt handlers.
 */
#define __HAL_LL_UART_GET_IT_SOURCE(_num,_int) read_reg_bits(hal_ll_uart_ivt_map[_num].hal_ll_uart_ivt_pie_reg_addr,(1<<_int))

// ------------------------------------------------------------------ TYPEDEFS
/*!< @brief UART HW register structure */
typedef struct
{
    hal_ll_base_addr_t uart_ucon0_reg_addr;
    hal_ll_base_addr_t uart_ucon1_reg_addr;
    hal_ll_base_addr_t uart_ucon2_reg_addr;
    hal_ll_base_addr_t uart_rxb_reg_addr;
    hal_ll_base_addr_t uart_txb_reg_addr;
    hal_ll_base_addr_t uart_fifo_reg_addr;
    hal_ll_base_addr_t uart_uerrir_reg_addr;
    hal_ll_base_addr_t uart_uerrie_reg_addr;
    hal_ll_base_addr_t uart_brgl_reg_addr;
    hal_ll_base_addr_t uart_brgh_reg_addr;
    hal_ll_base_addr_t uart_ivt_reg_addr;
} hal_ll_uart_base_handle_t;

/*!< @brief UART interrupt register structure */
typedef struct
{
    hal_ll_base_addr_t hal_ll_uart_ivt_pie_reg_addr;
    hal_ll_base_addr_t hal_ll_uart_ivt_pir_reg_addr;
} hal_ll_uart_handle_ivt_map_t;

/*!< @brief UART baud rate structure */
typedef struct
{
    uint32_t baud;
    uint32_t real_baud;
} hal_ll_uart_baud_t;

/*!< @brief UART hw specific structure */
typedef struct
{
    const hal_ll_uart_base_handle_t *base;
    hal_ll_pin_name_t module_index;
    hal_ll_uart_pins_t pins;
    hal_ll_uart_baud_t baud_rate;
    hal_ll_uart_parity_t parity;
    hal_ll_uart_stop_bits_t stop_bit;
    hal_ll_uart_data_bits_t data_bit;
} hal_ll_uart_hw_specifics_map_t;

/*!< @brief UART hw specific module values */
typedef struct
{
    uint16_t pin_tx;
    uint16_t pin_rx;
} hal_ll_uart_pin_id;

/*!< @brief UART hw specific error values */
typedef enum
{
    HAL_LL_UART_SUCCESS = 0,
    HAL_LL_UART_WRONG_PINS,
    HAL_LL_UART_MODULE_ERROR,

    HAL_LL_UART_ERROR = (-1)
} hal_ll_uart_err_t;

/*!< @brief UART module state selection */
typedef enum
{
    HAL_LL_UART_DISABLE = 0,
    HAL_LL_UART_ENABLE
} hal_ll_uart_state_t;

// ------------------------------------------------------------------ CONSTANTS
/*!< @brief UART modules register array */
static const hal_ll_uart_base_handle_t hal_ll_uart_regs[ UART_MODULE_COUNT + 1 ] =
{
    #ifdef UART_MODULE_1
    { HAL_LL_U1CON0_ADDRESS, HAL_LL_U1CON1_ADDRESS, HAL_LL_U1CON2_ADDRESS, HAL_LL_U1RXB_ADDRESS, HAL_LL_U1TXB_ADDRESS, HAL_LL_U1FIFO_ADDRESS, HAL_LL_U1ERRIR_ADDRESS, HAL_LL_U1ERRIE_ADDRESS, HAL_LL_U1BRGL_ADDRESS, HAL_LL_U1BRGH_ADDRESS, HAL_LL_PIR_MODULE_UART1_ADDRESS },
    #endif
    #ifdef UART_MODULE_2
    { HAL_LL_U2CON0_ADDRESS, HAL_LL_U2CON1_ADDRESS, HAL_LL_U2CON2_ADDRESS, HAL_LL_U2RXB_ADDRESS, HAL_LL_U2TXB_ADDRESS, HAL_LL_U2FIFO_ADDRESS, HAL_LL_U2ERRIR_ADDRESS, HAL_LL_U2ERRIE_ADDRESS, HAL_LL_U2BRGL_ADDRESS, HAL_LL_U2BRGH_ADDRESS, HAL_LL_PIR_MODULE_UART2_ADDRESS },
    #endif
    #ifdef UART_MODULE_3
    { HAL_LL_U3CON0_ADDRESS, HAL_LL_U3CON1_ADDRESS, HAL_LL_U3CON2_ADDRESS, HAL_LL_U3RXB_ADDRESS, HAL_LL_U3TXB_ADDRESS, HAL_LL_U3FIFO_ADDRESS, HAL_LL_U3ERRIR_ADDRESS, HAL_LL_U3ERRIE_ADDRESS, HAL_LL_U3BRGL_ADDRESS, HAL_LL_U3BRGH_ADDRESS, HAL_LL_PIR_MODULE_UART3_ADDRESS },
    #endif
    #ifdef UART_MODULE_4
    { HAL_LL_U4CON0_ADDRESS, HAL_LL_U4CON1_ADDRESS, HAL_LL_U4CON2_ADDRESS, HAL_LL_U4RXB_ADDRESS, HAL_LL_U4TXB_ADDRESS, HAL_LL_U4FIFO_ADDRESS, HAL_LL_U4ERRIR_ADDRESS, HAL_LL_U4ERRIE_ADDRESS, HAL_LL_U4BRGL_ADDRESS, HAL_LL_U4BRGH_ADDRESS, HAL_LL_PIR_MODULE_UART4_ADDRESS },
    #endif
    #ifdef UART_MODULE_5
    { HAL_LL_U5CON0_ADDRESS, HAL_LL_U5CON1_ADDRESS, HAL_LL_U5CON2_ADDRESS, HAL_LL_U5RXB_ADDRESS, HAL_LL_U5TXB_ADDRESS, HAL_LL_U5FIFO_ADDRESS, HAL_LL_U5ERRIR_ADDRESS, HAL_LL_U5ERRIE_ADDRESS, HAL_LL_U5BRGL_ADDRESS, HAL_LL_U5BRGH_ADDRESS, HAL_LL_PIR_MODULE_UART5_ADDRESS },
    #endif

    { HAL_LL_MODULE_ERROR, HAL_LL_MODULE_ERROR, HAL_LL_MODULE_ERROR, HAL_LL_MODULE_ERROR, HAL_LL_MODULE_ERROR, HAL_LL_MODULE_ERROR, HAL_LL_MODULE_ERROR, HAL_LL_MODULE_ERROR, HAL_LL_MODULE_ERROR, HAL_LL_MODULE_ERROR, HAL_LL_MODULE_ERROR }
};

/*!< @brief UART modules interrupt register array */
static const hal_ll_uart_handle_ivt_map_t hal_ll_uart_ivt_map[ UART_MODULE_COUNT + 1 ] =
{
    #ifdef UART_MODULE_1
    { HAL_LL_PIE_MODULE_UART1_ADDRESS, HAL_LL_PIR_MODULE_UART1_ADDRESS },
    #endif
    #ifdef UART_MODULE_2
    { HAL_LL_PIE_MODULE_UART2_ADDRESS, HAL_LL_PIR_MODULE_UART2_ADDRESS },
    #endif
    #ifdef UART_MODULE_3
    { HAL_LL_PIE_MODULE_UART3_ADDRESS, HAL_LL_PIR_MODULE_UART3_ADDRESS },
    #endif
    #ifdef UART_MODULE_4
    { HAL_LL_PIE_MODULE_UART4_ADDRESS, HAL_LL_PIR_MODULE_UART4_ADDRESS },
    #endif
    #ifdef UART_MODULE_5
    { HAL_LL_PIE_MODULE_UART5_ADDRESS, HAL_LL_PIR_MODULE_UART5_ADDRESS },
    #endif

    { HAL_LL_MODULE_ERROR, HAL_LL_MODULE_ERROR }
};

// ------------------------------------------------------------------ VARIABLES
/*!< @brief Global handle variables used in functions */
static volatile hal_ll_uart_handle_register_t *low_level_handle;
static volatile hal_ll_uart_hw_specifics_map_t *hal_ll_uart_hw_specifics_map_local;

/*!< @brief Global interrupt handlers used in functions */
static hal_ll_uart_isr_t irq_handler;
static handle_t objects[UART_MODULE_COUNT] = { NULL };

/*!< @brief UART hardware specific info */
static hal_ll_uart_hw_specifics_map_t hal_ll_uart_hw_specifics_map[ UART_MODULE_COUNT + 1 ] =
{
    #ifdef UART_MODULE_1
    {&hal_ll_uart_regs[hal_ll_uart_module_num(UART_MODULE_1)], hal_ll_uart_module_num(UART_MODULE_1), { HAL_LL_PIN_NC, HAL_LL_UART1_UTXIF_BIT, HAL_LL_PIN_NC, HAL_LL_UART1_URXIF_BIT }, {115200, 0}, HAL_LL_UART_PARITY_DEFAULT, HAL_LL_UART_STOP_BITS_DEFAULT, HAL_LL_UART_DATA_BITS_DEFAULT },
    #endif
    #ifdef UART_MODULE_2
    {&hal_ll_uart_regs[hal_ll_uart_module_num(UART_MODULE_2)], hal_ll_uart_module_num(UART_MODULE_2), { HAL_LL_PIN_NC, HAL_LL_UART2_UTXIF_BIT, HAL_LL_PIN_NC, HAL_LL_UART2_URXIF_BIT }, {115200, 0}, HAL_LL_UART_PARITY_DEFAULT, HAL_LL_UART_STOP_BITS_DEFAULT, HAL_LL_UART_DATA_BITS_DEFAULT },
    #endif
    #ifdef UART_MODULE_3
    {&hal_ll_uart_regs[hal_ll_uart_module_num(UART_MODULE_3)], hal_ll_uart_module_num(UART_MODULE_3), { HAL_LL_PIN_NC, HAL_LL_UART3_UTXIF_BIT, HAL_LL_PIN_NC, HAL_LL_UART3_URXIF_BIT }, {115200, 0}, HAL_LL_UART_PARITY_DEFAULT, HAL_LL_UART_STOP_BITS_DEFAULT, HAL_LL_UART_DATA_BITS_DEFAULT },
    #endif
    #ifdef UART_MODULE_4
    {&hal_ll_uart_regs[hal_ll_uart_module_num(UART_MODULE_4)], hal_ll_uart_module_num(UART_MODULE_4), { HAL_LL_PIN_NC, HAL_LL_UART4_UTXIF_BIT, HAL_LL_PIN_NC, HAL_LL_UART4_URXIF_BIT }, {115200, 0}, HAL_LL_UART_PARITY_DEFAULT, HAL_LL_UART_STOP_BITS_DEFAULT, HAL_LL_UART_DATA_BITS_DEFAULT },
    #endif
    #ifdef UART_MODULE_5
    {&hal_ll_uart_regs[hal_ll_uart_module_num(UART_MODULE_5)], hal_ll_uart_module_num(UART_MODULE_5), { HAL_LL_PIN_NC, HAL_LL_UART5_UTXIF_BIT, HAL_LL_PIN_NC, HAL_LL_UART5_URXIF_BIT }, {115200, 0}, HAL_LL_UART_PARITY_DEFAULT, HAL_LL_UART_STOP_BITS_DEFAULT, HAL_LL_UART_DATA_BITS_DEFAULT },
    #endif

    {&hal_ll_uart_regs[UART_MODULE_COUNT], HAL_LL_MODULE_ERROR, { HAL_LL_PIN_NC, 0, HAL_LL_PIN_NC, 0 }, {0, 0}, HAL_LL_UART_PARITY_DEFAULT, HAL_LL_UART_STOP_BITS_DEFAULT, HAL_LL_UART_DATA_BITS_DEFAULT }
};

// ---------------------------------------------- PRIVATE FUNCTION DECLARATIONS
/**
  * @brief  Check if pins are adequate.
  *
  * Checks tx and rx pins the user has passed with pre-defined
  * pins in tx and rx maps. Take into consideration that module
  * index numbers have to be the same for both pins.
  *
  * @param[in]  tx_pin - TX pre-defined pin name.
  * @param[in]  rx_pin - RX pre-defined pin name.
  * @return hal_ll_pin_name_t Module index based on pins.
  *
  * Returns pre-defined module index from pin maps, if pins
  * are adequate.
  */
static hal_ll_pin_name_t hal_ll_uart_check_pins( hal_ll_pin_name_t tx_pin, hal_ll_pin_name_t rx_pin, hal_ll_uart_pin_id *index_list, hal_ll_uart_handle_register_t *handle_map );

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
static hal_ll_uart_hw_specifics_map_t *hal_ll_uart_get_specifics( handle_t handle );

/**
 * @brief  Sets desired stop bits.
 *
 * Initializes module on hardware level
 * with specified stop bit value.
 *
 * @param[in]  map - Object specific context handler.
 *
 * @return void None.
 */
static void hal_ll_uart_set_stop_bits_bare_metal( hal_ll_uart_hw_specifics_map_t *map );

/**
 * @brief  Sets desired data bits.
 *
 * Initializes module on hardware level
 * with specified data bit bit value.
 *
 * @param[in]  map - Object specific context handler.
 *
 * @return void None.
 */
static void hal_ll_uart_set_data_bits_bare_metal( hal_ll_uart_hw_specifics_map_t *map );

/**
 * @brief  Sets desired parity.
 *
 * Initializes module on hardware level
 * with specified parity value.
 *
 * @param[in]  map - Object specific context handler.
 *
 * @return void None.
 */
static void hal_ll_uart_set_parity_bare_metal( hal_ll_uart_hw_specifics_map_t *map );

/**
  * @brief  Enable clock for UART module on hardware level.
  *
  * Initializes UART module clock on hardware level, based on beforehand
  * set configuration and module handler.
  *
  * @param[in]  map - Object specific context handler.
  * @param[in]  hal_ll_stat - True(enable clock)/False(disable clock).
  *
  * @return void None.
  */
static void hal_ll_uart_set_module_power( hal_ll_uart_hw_specifics_map_t *map, bool hal_ll_state );

/**
  * @brief  Sets pin state.
  *
  * The following function sets TRIS and ANSEL values
  * for adequate pins.
  *
  * @param[in]  map - Object specific context handler.
  *
  * @return None
  */
static void hal_ll_i2c_hw_ansel_set( hal_ll_uart_hw_specifics_map_t *map );

/**
 * @brief  Maps new-found module specific values.
 *
 * Maps pin names and PPS values for
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
 * @brief  Set PPS state.
 *
 * Sets adequate RPINRx and RPORx register
 * values for adequate functionality.
 * Also, sets TRISx register bit appropriately.
 *
 * @param[in]  map - Object specific context handler.
 * @param[in]  hal_ll_state - init or deinit
 *
 * @return  hal_ll_pps_err_t PPS specific value.
 * HAL_LL_PPS_SUCCESS  -- OK
 * HAL_LL_PPS_DIRECTION_ERROR -- Direction not set
 * HAL_LL_PPS_PIN_ERROR -- Wrong pin
 * HAL_LL_PPS_MODULE_ERROR -- General error
 *
 * @note PIC specific.
 */
static hal_ll_pps_err_t hal_ll_pps_set_state( hal_ll_uart_hw_specifics_map_t *map, bool hal_ll_state );

/**
  * @brief  Finds UART module index.
  *
  * Finds UART index(module number) based on
  * handle value.
  *
  * @param[in]  handle - Object specific context handler.
  *
  * @return uint8_t Module number.
  * Returns values from 0 to 9.
  */
static uint8_t hal_ll_uart_find_index( handle_t *handle );

/**
  * @brief  Clears UART registers.
  *
  * Clears UART module configuration
  * registers, effectively disabling the module itself.
  * Take into consideration that any IRQ bits
  * are not cleared.
  *
  * @param[in]  hal_ll_hw_reg - UART HW register structure.
  *
  * @return void None.
  */
static void hal_ll_uart_clear_regs( const hal_ll_uart_base_handle_t *hal_ll_hw_reg );

/**
 * @brief  Sets desired baud rate on hardware level.
 *
 * Initializes module with specified baud rate value.
 * Take into consideration that if the difference
 * between desired baud rate and actual baud
 * rate the hw was initialized to is greater than
 * 1%, baud rate shall not be set.
 * If this occurs, return value shall be
 * the error percentage.
 *
 * @param[in]  map - Object specific context handler.
 *
 * @return void None.
 */
static void hal_ll_uart_set_baud_bare_metal( hal_ll_uart_hw_specifics_map_t *map );

/**
 * @brief  Sets module clock value.
 *
 * Enables/disables specific UART module
 * clock gate.
 *
 * @param[in]  hal_ll_hw_reg - UART HW register structure.
 * @param[in]  pin_state - true(enable clock) / false(disable clock)
 *
 * @return void None.
 */
static void hal_ll_uart_set_module( const hal_ll_uart_base_handle_t *hal_ll_hw_reg, hal_ll_uart_state_t pin_state );

/**
 * @brief  Sets module TX line state.
 *
 * Enables/disables specific UART module
 * TX pin state
 *
 * @param[in]  hal_ll_hw_reg - UART HW register structure.
 * @param[in]  pin_state - true(enable transmitter pin) / false(disable transmitter pin)
 *
 * @return void None.
 */
static void hal_ll_uart_set_transmitter( const hal_ll_uart_base_handle_t *hal_ll_hw_reg, hal_ll_uart_state_t pin_state );

/**
 * @brief  Sets module RX line state.
 *
 * Enables/disables specific UART module
 * RX pin state
 *
 * @param[in]  hal_ll_hw_reg - UART HW register structure.
 * @param[in]  pin_state - true(enable receive pin) / false(disable receive pin)
 *
 * @return void None.
 */
static void hal_ll_uart_set_receiver( const hal_ll_uart_base_handle_t *hal_ll_hw_reg, hal_ll_uart_state_t pin_state );

/**
 * @brief  Initialize UART module.
 *
 * Enables UART module clogk gate first.
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
 * the hardware level.
 *
 * Procedure:
 * 1. Clears control registers
 * 2. Sets baud rate value
 * 3. Enables transmit pin
 * 4. Enables receive pin
 * 5. Enables power for specific module
 *
 * @param[in]  map - Object specific context handler.
 *
 * @return void None.
 */
static void hal_ll_uart_hw_init( hal_ll_uart_hw_specifics_map_t *map );

// ------------------------------------------------ PUBLIC FUNCTION DEFINITIONS
hal_ll_err_t hal_ll_uart_register_handle( hal_ll_pin_name_t tx_pin, hal_ll_pin_name_t rx_pin, hal_ll_uart_handle_register_t *handle_map, uint8_t *hal_module_id ) {

    hal_ll_uart_pin_id index_list[UART_MODULE_COUNT] = {HAL_LL_PIN_NC,HAL_LL_PIN_NC};
    uint8_t pin_check_result;

    // Check if pins are valid
    if ( (pin_check_result = hal_ll_uart_check_pins( tx_pin, rx_pin, index_list, handle_map )) == HAL_LL_PIN_NC ) {
        return HAL_LL_UART_WRONG_PINS;
    }

    if ( (hal_ll_uart_hw_specifics_map[pin_check_result].pins.tx_pin.pin_name != tx_pin) ||
         (hal_ll_uart_hw_specifics_map[pin_check_result].pins.rx_pin.pin_name != rx_pin) )
    {
        // Used only for chips which have UART PPS pins
        #if HAL_LL_UART_PPS_ENABLED == true
        if ( hal_ll_pps_set_state( &hal_ll_uart_hw_specifics_map[ pin_check_result ], false ) != HAL_LL_UART_SUCCESS )
            return HAL_LL_UART_WRONG_PINS;
        #endif

        hal_ll_uart_map_pins( pin_check_result, index_list );

        // Used only for chips which have UART PPS pins
        #if HAL_LL_UART_PPS_ENABLED == true
        if ( hal_ll_pps_set_state( &hal_ll_uart_hw_specifics_map[ pin_check_result ], true ) != HAL_LL_UART_SUCCESS )
            return HAL_LL_UART_WRONG_PINS;
        #endif

        handle_map[pin_check_result].init_ll_state = false;
    }

    *hal_module_id = pin_check_result;

    hal_ll_module_state[pin_check_result].hal_ll_uart_handle = (handle_t *)&hal_ll_uart_hw_specifics_map[pin_check_result].base;

    handle_map[pin_check_result].hal_ll_uart_handle = (handle_t *)&hal_ll_module_state[pin_check_result].hal_ll_uart_handle;

    return HAL_LL_UART_SUCCESS;
}

hal_ll_err_t hal_ll_module_configure_uart( handle_t *handle ) {
    hal_ll_uart_hw_specifics_map_local = hal_ll_uart_get_specifics( hal_ll_uart_get_module_state_address );
    hal_ll_uart_handle_register_t *hal_handle = (hal_ll_uart_handle_register_t *)*handle;
    uint8_t pin_check_result = hal_ll_uart_hw_specifics_map_local->module_index;

    hal_ll_uart_init( hal_ll_uart_hw_specifics_map_local );

    hal_ll_module_state[pin_check_result].hal_ll_uart_handle = (handle_t *)&hal_ll_uart_hw_specifics_map[pin_check_result].base;
    hal_ll_module_state[pin_check_result].init_ll_state = true;
    hal_handle->init_ll_state = true;

    return HAL_LL_UART_SUCCESS;
}

hal_ll_err_t hal_ll_uart_set_baud( handle_t *handle, uint32_t baud ) {
    low_level_handle = hal_ll_uart_get_handle;
    hal_ll_uart_hw_specifics_map_local = hal_ll_uart_get_specifics( hal_ll_uart_get_module_state_address );

    low_level_handle->init_ll_state = false;

    hal_ll_uart_hw_specifics_map_local->baud_rate.baud = baud;

    hal_ll_uart_init(hal_ll_uart_hw_specifics_map_local);

    low_level_handle->init_ll_state = true;

    return hal_ll_uart_hw_specifics_map_local->baud_rate.real_baud;
}

hal_ll_err_t hal_ll_uart_set_parity( handle_t *handle, hal_ll_uart_parity_t parity ) {
    low_level_handle = hal_ll_uart_get_handle;
    hal_ll_uart_hw_specifics_map_local = hal_ll_uart_get_specifics( hal_ll_uart_get_module_state_address );

    low_level_handle->init_ll_state = false;

    hal_ll_uart_hw_specifics_map_local->parity = parity;

    hal_ll_uart_init(hal_ll_uart_hw_specifics_map_local);

    low_level_handle->init_ll_state = true;

    return HAL_LL_UART_SUCCESS;
}

hal_ll_err_t hal_ll_uart_set_stop_bits( handle_t *handle, hal_ll_uart_stop_bits_t stop_bit ) {
    low_level_handle = hal_ll_uart_get_handle;
    hal_ll_uart_hw_specifics_map_local = hal_ll_uart_get_specifics( hal_ll_uart_get_module_state_address );

    low_level_handle->init_ll_state = false;

    hal_ll_uart_hw_specifics_map_local->stop_bit = stop_bit;

    hal_ll_uart_init(hal_ll_uart_hw_specifics_map_local);

    low_level_handle->init_ll_state = true;

    return HAL_LL_UART_SUCCESS;
}

hal_ll_err_t hal_ll_uart_set_data_bits( handle_t *handle, hal_ll_uart_data_bits_t data_bit ) {
    low_level_handle = hal_ll_uart_get_handle;
    hal_ll_uart_hw_specifics_map_local = hal_ll_uart_get_specifics( hal_ll_uart_get_module_state_address );

    low_level_handle->init_ll_state = false;

    hal_ll_uart_hw_specifics_map_local->data_bit = data_bit;

    hal_ll_uart_init(hal_ll_uart_hw_specifics_map_local);

    low_level_handle->init_ll_state = true;

    return HAL_LL_UART_SUCCESS;
}

void hal_ll_uart_close( handle_t *handle ) {
    low_level_handle = hal_ll_uart_get_handle;
    hal_ll_uart_hw_specifics_map_local = hal_ll_uart_get_specifics( hal_ll_uart_get_module_state_address );

    if( low_level_handle->hal_ll_uart_handle != NULL ) {
        hal_ll_uart_set_module_power(hal_ll_uart_hw_specifics_map_local, true);

        // Used only for chips which have I2C PPS pins
        #if HAL_LL_UART_PPS_ENABLED == true
        hal_ll_pps_set_state(hal_ll_uart_hw_specifics_map_local, false);
        #endif

        hal_ll_uart_irq_disable(handle, HAL_LL_UART_IRQ_RX);
        hal_ll_uart_irq_disable(handle, HAL_LL_UART_IRQ_TX);

        hal_ll_uart_clear_regs(hal_ll_uart_hw_specifics_map_local->base);
        hal_ll_uart_set_module_power(hal_ll_uart_hw_specifics_map_local, false);

        hal_ll_uart_hw_specifics_map_local->pins.tx_pin.pin_name = HAL_LL_PIN_NC;
        hal_ll_uart_hw_specifics_map_local->pins.rx_pin.pin_name = HAL_LL_PIN_NC;

        hal_ll_uart_hw_specifics_map_local->baud_rate.baud = 115200UL;
        hal_ll_uart_hw_specifics_map_local->baud_rate.real_baud = 0;

        irq_handler = NULL;
        objects[ hal_ll_uart_find_index( handle ) ] = 0;

        low_level_handle->hal_ll_uart_handle = NULL;
        low_level_handle->hal_drv_uart_handle = NULL;

        low_level_handle->init_ll_state = false;
    }
}

void hal_ll_uart_register_irq_handler( handle_t *handle, hal_ll_uart_isr_t handler, handle_t obj ) {
    irq_handler = handler;
    objects[ hal_ll_uart_find_index( handle ) ] = obj;
}

void hal_ll_uart_irq_enable( handle_t *handle, hal_ll_uart_irq_t irq ) {
    hal_ll_uart_hw_specifics_map_local = hal_ll_uart_get_specifics( hal_ll_uart_get_module_state_address );

    switch ( irq )
    {
        case HAL_LL_UART_IRQ_RX:
            __HAL_LL_UART_ENABLE_IT( hal_ll_uart_hw_specifics_map_local->module_index,
                                     hal_ll_uart_hw_specifics_map_local->pins.rx_pin.pir_num );
            break;

        case HAL_LL_UART_IRQ_TX:
            __HAL_LL_UART_ENABLE_IT( hal_ll_uart_hw_specifics_map_local->module_index,
                                     hal_ll_uart_hw_specifics_map_local->pins.tx_pin.pir_num );
            break;

        default:
            break;
    }

    switch ( hal_ll_uart_hw_specifics_map_local->module_index )
    {
        #ifdef UART_MODULE_1
        case hal_ll_uart_module_num(UART_MODULE_1):
            hal_ll_core_enable_irq( HAL_LL_IRQ_U1RXIE_BIT );
            break;
        #endif
        #ifdef UART_MODULE_2
        case hal_ll_uart_module_num(UART_MODULE_2):
            hal_ll_core_enable_irq( HAL_LL_IRQ_U2RXIE_BIT );
            break;
        #endif
        #ifdef UART_MODULE_3
        case hal_ll_uart_module_num(UART_MODULE_3):
            hal_ll_core_enable_irq( HAL_LL_IRQ_U3RXIE_BIT );
            break;
        #endif
        #ifdef UART_MODULE_4
        case hal_ll_uart_module_num(UART_MODULE_4):
            hal_ll_core_enable_irq( HAL_LL_IRQ_U4RXIE_BIT );
            break;
        #endif
        #ifdef UART_MODULE_5
        case hal_ll_uart_module_num(UART_MODULE_5):
            hal_ll_core_enable_irq( HAL_LL_IRQ_U5RXIE_BIT );
            break;
        #endif

        default:
            break;
    }
}

void hal_ll_uart_irq_disable( handle_t *handle, hal_ll_uart_irq_t irq ) {
    hal_ll_uart_hw_specifics_map_local = hal_ll_uart_get_specifics( hal_ll_uart_get_module_state_address );

    switch ( irq )
    {
        case HAL_LL_UART_IRQ_RX:
            __HAL_LL_UART_DISABLE_IT( hal_ll_uart_hw_specifics_map_local->module_index,
                                      hal_ll_uart_hw_specifics_map_local->pins.rx_pin.pir_num );
            break;

        case HAL_LL_UART_IRQ_TX:
            __HAL_LL_UART_DISABLE_IT( hal_ll_uart_hw_specifics_map_local->module_index,
                                      hal_ll_uart_hw_specifics_map_local->pins.tx_pin.pir_num );
            break;

        default:
            break;
    }

    // Check if module interrupt flags are set or not
    if ( ( !check_reg_bit( hal_ll_uart_ivt_map[ hal_ll_uart_hw_specifics_map_local->module_index ].hal_ll_uart_ivt_pir_reg_addr,
                           hal_ll_uart_hw_specifics_map_local->pins.rx_pin.pir_num ) ) &&
         ( !check_reg_bit( hal_ll_uart_ivt_map[ hal_ll_uart_hw_specifics_map_local->module_index ].hal_ll_uart_ivt_pir_reg_addr,
                           hal_ll_uart_hw_specifics_map_local->pins.tx_pin.pir_num ) ) )
    {
        switch ( hal_ll_uart_hw_specifics_map_local->module_index )
        {
            #ifdef UART_MODULE_1
            case hal_ll_uart_module_num(UART_MODULE_1):
                hal_ll_core_disable_irq( HAL_LL_IRQ_U1RXIE_BIT );
                break;
            #endif
            #ifdef UART_MODULE_2
            case hal_ll_uart_module_num(UART_MODULE_2):
                hal_ll_core_disable_irq( HAL_LL_IRQ_U2RXIE_BIT );
                break;
            #endif
            #ifdef UART_MODULE_3
            case hal_ll_uart_module_num(UART_MODULE_3):
                hal_ll_core_disable_irq( HAL_LL_IRQ_U3RXIE_BIT );
                break;
            #endif
            #ifdef UART_MODULE_4
            case hal_ll_uart_module_num(UART_MODULE_4):
                hal_ll_core_disable_irq( HAL_LL_IRQ_U4RXIE_BIT );
                break;
            #endif
            #ifdef UART_MODULE_5
            case hal_ll_uart_module_num(UART_MODULE_5):
                hal_ll_core_disable_irq( HAL_LL_IRQ_U5RXIE_BIT );
                break;
            #endif

            default:
                break;
        }
    }
}

void hal_ll_uart_write( handle_t *handle, uint8_t wr_data) {
    const hal_ll_uart_base_handle_t *hal_ll_hw_reg = hal_ll_uart_hw_specifics_map_local->base;

    while( !check_reg_bit( hal_ll_hw_reg->uart_uerrir_reg_addr, HAL_LL_UART_TXMTIF_BIT ) );

    write_reg( hal_ll_hw_reg->uart_txb_reg_addr, wr_data );
}

void hal_ll_uart_write_polling( handle_t *handle, uint8_t wr_data) {
    const hal_ll_uart_base_handle_t *hal_ll_hw_reg = hal_ll_uart_hw_specifics_map_local->base;

    while( !check_reg_bit( hal_ll_hw_reg->uart_uerrir_reg_addr, HAL_LL_UART_TXMTIF_BIT ) );

    write_reg( hal_ll_hw_reg->uart_txb_reg_addr, wr_data );
}

uint8_t hal_ll_uart_read( handle_t *handle ) {
    const hal_ll_uart_base_handle_t *hal_ll_hw_reg = hal_ll_uart_hw_specifics_map_local->base;

    return read_reg( hal_ll_hw_reg->uart_rxb_reg_addr );
}

uint8_t hal_ll_uart_read_polling( handle_t *handle ) {
    const hal_ll_uart_base_handle_t *hal_ll_hw_reg = hal_ll_uart_hw_specifics_map_local->base;

    while( !check_reg_bit( hal_ll_uart_regs[ hal_ll_uart_hw_specifics_map_local->module_index ].uart_ivt_reg_addr,
                           HAL_LL_UART_URXIF_BIT ) )
    {
        // Wait for data in the receive buffer
    }

    return read_reg( hal_ll_hw_reg->uart_rxb_reg_addr );
}

// ------------------------------------------------------------- DEFAULT EXCEPTION HANDLERS
/*!< @brief Link handler from HAL layer */
void hal_uart_irq_handler(handle_t obj, hal_ll_uart_irq_t event);

/*!< @brief Link IRQ Handler to HAL layer `hal_uart_irq_handler` function */
#pragma funcall UART_IRQHandler hal_uart_irq_handler

#pragma optimize none
__weak void MARK_AS_IRQ_HANDLER UART_IRQHandler(void) MIKROC_IV(HAL_LL_INTERRUPT_PRIORITY) {
    #ifdef UART_MODULE_1
    if( hal_ll_uart_get_status_flags( hal_ll_uart_module_num(UART_MODULE_1) ) & ( 1 << HAL_LL_UART1_URXIF_BIT ) )
    {
        if( ( __HAL_LL_UART_GET_IT_SOURCE( hal_ll_uart_module_num(UART_MODULE_1), HAL_LL_UART1_URXIF_BIT ) ) != 0 )
        {
            irq_handler( objects[ hal_ll_uart_module_num(UART_MODULE_1) ], HAL_LL_UART_IRQ_RX );
        }
    }
    if( ( hal_ll_uart_get_status_flags( hal_ll_uart_module_num(UART_MODULE_1) ) & ( 1 << HAL_LL_UART1_UTXIF_BIT ) ) )
    {
        if( ( __HAL_LL_UART_GET_IT_SOURCE( hal_ll_uart_module_num(UART_MODULE_1), HAL_LL_UART1_UTXIF_BIT ) ) != 0 )
        {
            irq_handler( objects[ hal_ll_uart_module_num(UART_MODULE_1) ], HAL_LL_UART_IRQ_TX );
        }
    }
    #endif
    #ifdef UART_MODULE_2
    if( hal_ll_uart_get_status_flags( hal_ll_uart_module_num(UART_MODULE_2) ) & ( 1 << HAL_LL_UART2_URXIF_BIT ) )
    {
        if( ( __HAL_LL_UART_GET_IT_SOURCE( hal_ll_uart_module_num(UART_MODULE_2), HAL_LL_UART2_URXIF_BIT ) ) != 0 )
        {
            irq_handler( objects[ hal_ll_uart_module_num(UART_MODULE_2) ], HAL_LL_UART_IRQ_RX );
        }
    }
    if( hal_ll_uart_get_status_flags( hal_ll_uart_module_num(UART_MODULE_2) ) & ( 1 << HAL_LL_UART2_UTXIF_BIT ) )
    {
        if( ( __HAL_LL_UART_GET_IT_SOURCE( hal_ll_uart_module_num(UART_MODULE_2), HAL_LL_UART2_UTXIF_BIT ) ) != 0 )
        {
            irq_handler( objects[ hal_ll_uart_module_num(UART_MODULE_2) ], HAL_LL_UART_IRQ_TX );
        }
    }
    #endif
     #ifdef UART_MODULE_3
    if( hal_ll_uart_get_status_flags( hal_ll_uart_module_num(UART_MODULE_3) ) & ( 1 << HAL_LL_UART3_URXIF_BIT ) )
    {
        if( ( __HAL_LL_UART_GET_IT_SOURCE( hal_ll_uart_module_num(UART_MODULE_3), HAL_LL_UART3_URXIF_BIT ) ) != 0 )
        {
            irq_handler( objects[ hal_ll_uart_module_num(UART_MODULE_3) ], HAL_LL_UART_IRQ_RX );
        }
    }
    if( hal_ll_uart_get_status_flags( hal_ll_uart_module_num(UART_MODULE_3) ) & ( 1 << HAL_LL_UART3_UTXIF_BIT ) )
    {
        if( ( __HAL_LL_UART_GET_IT_SOURCE( hal_ll_uart_module_num(UART_MODULE_3), HAL_LL_UART3_UTXIF_BIT ) ) != 0 )
        {
            irq_handler( objects[ hal_ll_uart_module_num(UART_MODULE_3) ], HAL_LL_UART_IRQ_TX );
        }
    }
    #endif
    #ifdef UART_MODULE_4
    if( hal_ll_uart_get_status_flags( hal_ll_uart_module_num(UART_MODULE_4) ) & ( 1 << HAL_LL_UART4_URXIF_BIT ) )
    {
        if( ( __HAL_LL_UART_GET_IT_SOURCE( hal_ll_uart_module_num(UART_MODULE_4), HAL_LL_UART4_URXIF_BIT ) ) != 0 )
        {
            irq_handler( objects[ hal_ll_uart_module_num(UART_MODULE_4) ], HAL_LL_UART_IRQ_RX );
        }
    }
    if( hal_ll_uart_get_status_flags( hal_ll_uart_module_num(UART_MODULE_4) ) & ( 1 << HAL_LL_UART4_UTXIF_BIT ) )
    {
        if( ( __HAL_LL_UART_GET_IT_SOURCE( hal_ll_uart_module_num(UART_MODULE_4), HAL_LL_UART4_UTXIF_BIT ) ) != 0 )
        {
            irq_handler( objects[ hal_ll_uart_module_num(UART_MODULE_4) ], HAL_LL_UART_IRQ_TX );
        }
    }
    #endif
    #ifdef UART_MODULE_5
    if( hal_ll_uart_get_status_flags( hal_ll_uart_module_num(UART_MODULE_5) ) & ( 1 << HAL_LL_UART5_URXIF_BIT ) )
    {
        if( ( __HAL_LL_UART_GET_IT_SOURCE( hal_ll_uart_module_num(UART_MODULE_5), HAL_LL_UART5_URXIF_BIT ) ) != 0 )
        {
            irq_handler( objects[ hal_ll_uart_module_num(UART_MODULE_5) ], HAL_LL_UART_IRQ_RX );
        }
    }
    if( hal_ll_uart_get_status_flags( hal_ll_uart_module_num(UART_MODULE_5) ) & ( 1 << HAL_LL_UART5_UTXIF_BIT ) )
    {
        if( ( __HAL_LL_UART_GET_IT_SOURCE( hal_ll_uart_module_num(UART_MODULE_5), HAL_LL_UART5_UTXIF_BIT ) ) != 0 )
        {
            irq_handler( objects[ hal_ll_uart_module_num(UART_MODULE_5) ], HAL_LL_UART_IRQ_TX );
        }
    }
    #endif
}
#pragma optimize default

// ----------------------------------------------- PRIVATE FUNCTION DEFINITIONS
static uint8_t hal_ll_uart_find_index( handle_t *handle ) {
    hal_ll_uart_hw_specifics_map_local = hal_ll_uart_get_specifics( hal_ll_uart_get_module_state_address );

    if( hal_ll_uart_hw_specifics_map_local->base->uart_ucon0_reg_addr != HAL_LL_MODULE_ERROR ) {
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

    if ( (HAL_LL_PIN_NC == tx_pin) || (HAL_LL_PIN_NC == rx_pin) ) {
        return HAL_LL_PIN_NC;
    }

    for ( tx_index = 0; tx_index < tx_map_size; tx_index++ ) {
        if ( hal_ll_uart_tx_map[ tx_index ].pin == tx_pin ) {
            for ( rx_index = 0; rx_index < rx_map_size; rx_index++ ) {
                if ( hal_ll_uart_rx_map[ rx_index ].pin == rx_pin ) {
                    if ( hal_ll_uart_tx_map[ tx_index ].module_index == hal_ll_uart_rx_map[ rx_index ].module_index ) {
                        // Get module number
                        hal_ll_module_id = hal_ll_uart_tx_map[ tx_index ].module_index;

                        // Map pin names
                        index_list[hal_ll_module_id].pin_tx = tx_index;
                        index_list[hal_ll_module_id].pin_rx = rx_index;

                        // Check if module is taken
                        if ( NULL == handle_map[hal_ll_module_id].hal_drv_uart_handle ) {
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

static hal_ll_uart_hw_specifics_map_t *hal_ll_uart_get_specifics( handle_t handle ) {
    uint8_t hal_ll_module_count = sizeof(hal_ll_module_state) / (sizeof(hal_ll_uart_handle_register_t));
    static uint8_t hal_ll_module_error = sizeof(hal_ll_module_state) / (sizeof(hal_ll_uart_handle_register_t));

    #ifdef __XC8__
    #define REGISTER_HANDLE hal_ll_uart_handle
    #define REGISTER_HANDLE_TYPE hal_ll_uart_handle_register_t
    memory_width tmp_addr = 0;
    #if !(FSR_APPROACH)
    // On 8-bit PIC microcontrollers, pointers are often only 8 bits wide by default,
    // meaning they can only access addresses within a single memory page.
    // Circumvent this issue by concatenating the address to one 16-bit wide variable.
    memory_width *tmp_ptr, tmp_values[NUMBER_OF_BYTES] = {0};
    REGISTER_HANDLE_TYPE *handle_register = (REGISTER_HANDLE_TYPE *)handle;
    memory_width current_addr = &handle_register->REGISTER_HANDLE;

    for (uint8_t i = 0; i < NUMBER_OF_BYTES; i++) {
        current_addr += i;
        tmp_values[i] = read_reg(current_addr);
    }

    current_addr = 0;
    for (uint8_t i=0; i<NUMBER_OF_BYTES; i++) {
        current_addr = current_addr | (tmp_values[i] << (8*i));
    }
    #else
    /**
     * @brief Alternate approach with indirect register access.
     */
    memory_width *tmp_ptr, current_addr = 0;
    REGISTER_HANDLE_TYPE *handle_register = (REGISTER_HANDLE_TYPE *)handle;
    FSR0 = &handle_register->hal_ll_tim_handle;
    for (uint8_t i=0; i<NUMBER_OF_BYTES; i++) {
        current_addr = current_addr | (read_reg(FSR0++) << (8*i));
    }
    #endif
    tmp_ptr = current_addr;
    current_addr = *tmp_ptr;
    #endif

    while( hal_ll_module_count-- ) {
        #ifdef __XC8__
        tmp_addr = &hal_ll_uart_hw_specifics_map[hal_ll_module_count];
        if (current_addr == tmp_addr) {
            return &hal_ll_uart_hw_specifics_map[hal_ll_module_count];
        }
        #else
        if (hal_ll_uart_get_base_from_hal_handle == hal_ll_uart_hw_specifics_map[hal_ll_module_count].base) {
            return &hal_ll_uart_hw_specifics_map[hal_ll_module_count];
        }
        #endif
    }

    return &hal_ll_uart_hw_specifics_map[hal_ll_module_error];
}

static void hal_ll_uart_map_pins( uint8_t module_index, hal_ll_uart_pin_id *index_list ) {
    // Map new pins
    hal_ll_uart_hw_specifics_map[module_index].pins.tx_pin.pin_name = hal_ll_uart_tx_map[ index_list[module_index].pin_tx ].pin;
    hal_ll_uart_hw_specifics_map[module_index].pins.rx_pin.pin_name = hal_ll_uart_rx_map[ index_list[module_index].pin_rx ].pin;
}

static hal_ll_pps_err_t hal_ll_pps_set_state( hal_ll_uart_hw_specifics_map_t *map, bool hal_ll_state ) {
    hal_ll_pps_err_t hal_ll_status = HAL_LL_PPS_SUCCESS;

    if ( (map->pins.tx_pin.pin_name != HAL_LL_PIN_NC) && (map->pins.rx_pin.pin_name != HAL_LL_PIN_NC) ) {
        // Check status manually if needed
        hal_ll_status = hal_ll_pps_map( hal_ll_port( map->pins.tx_pin.pin_name ), hal_ll_pin( map->pins.tx_pin.pin_name ),
                                        HAL_LL_GPIO_DIGITAL_OUTPUT, HAL_LL_PPS_FUNCTIONALITY_UART, map->module_index, hal_ll_state );

        if ( hal_ll_status != HAL_LL_UART_SUCCESS )
            return hal_ll_status;

        // Check status manually if needed
        hal_ll_status = hal_ll_pps_map( hal_ll_port( map->pins.rx_pin.pin_name ), hal_ll_pin( map->pins.rx_pin.pin_name ),
                                        HAL_LL_GPIO_DIGITAL_INPUT, HAL_LL_PPS_FUNCTIONALITY_UART, map->module_index, hal_ll_state );

        return hal_ll_status;
    } else {
        return HAL_LL_UART_SUCCESS;
    }
}

static void hal_ll_uart_set_module_power( hal_ll_uart_hw_specifics_map_t *map, bool hal_ll_state ) {
    switch ( map->module_index )
    {
        #ifdef UART_MODULE_1
        #ifdef HAL_LL_PMD_UART1_ADDRESS
        case hal_ll_uart_module_num(UART_MODULE_1):
            ( hal_ll_state == true )?(clear_reg_bit( HAL_LL_PMD_UART1_ADDRESS, HAL_LL_UART1_MODULE_BIT )):(set_reg_bit( HAL_LL_PMD_UART1_ADDRESS, HAL_LL_UART1_MODULE_BIT ));
            break;
        #endif
        #endif
        #ifdef UART_MODULE_2
        #ifdef HAL_LL_PMD_UART2_ADDRESS
        case hal_ll_uart_module_num(UART_MODULE_2):
            ( hal_ll_state == true )?(clear_reg_bit( HAL_LL_PMD_UART2_ADDRESS, HAL_LL_UART2_MODULE_BIT )):(set_reg_bit( HAL_LL_PMD_UART2_ADDRESS, HAL_LL_UART2_MODULE_BIT ));
            break;
        #endif
        #endif
        #ifdef UART_MODULE_3
        #ifdef HAL_LL_PMD_UART3_ADDRESS
        case hal_ll_uart_module_num(UART_MODULE_3):
            ( hal_ll_state == true )?(clear_reg_bit( HAL_LL_PMD_UART3_ADDRESS, HAL_LL_UART3_MODULE_BIT )):(set_reg_bit( HAL_LL_PMD_UART3_ADDRESS, HAL_LL_UART3_MODULE_BIT ));
            break;
        #endif
        #endif
        #ifdef UART_MODULE_4
        #ifdef HAL_LL_PMD_UART4_ADDRESS
        case hal_ll_uart_module_num(UART_MODULE_4):
            ( hal_ll_state == true )?(clear_reg_bit( HAL_LL_PMD_UART4_ADDRESS, HAL_LL_UART4_MODULE_BIT )):(set_reg_bit( HAL_LL_PMD_UART4_ADDRESS, HAL_LL_UART4_MODULE_BIT ));
            break;
        #endif
        #endif
        #ifdef UART_MODULE_5
        #ifdef HAL_LL_PMD_UART5_ADDRESS
        case hal_ll_uart_module_num(UART_MODULE_5):
            ( hal_ll_state == true )?(clear_reg_bit( HAL_LL_PMD_UART5_ADDRESS, HAL_LL_UART5_MODULE_BIT )):(set_reg_bit( HAL_LL_PMD_UART5_ADDRESS, HAL_LL_UART5_MODULE_BIT ));
            break;
        #endif
        #endif

        default:
            break;
    }
}

static void hal_ll_uart_set_baud_bare_metal( hal_ll_uart_hw_specifics_map_t *map ) {
    const hal_ll_uart_base_handle_t *hal_ll_hw_reg = hal_ll_uart_get_base_struct(map->base);
    uint32_t hal_ll_baud_value = hal_ll_uart_get_baud(hal_ll_get_system_clock,map->baud_rate.baud,4);
    uint32_t hal_ll_baud_real_value = hal_ll_uart_get_real_baud(hal_ll_get_system_clock,hal_ll_baud_value,4);

    // If error greater than specified, cancel setting baud rate
    if( (float)hal_ll_uart_get_baud_error(hal_ll_baud_real_value,map->baud_rate.baud) > HAL_LL_UART_ACCEPTABLE_ERROR ) {
        map->baud_rate.real_baud = hal_ll_uart_get_baud_error(hal_ll_baud_real_value,map->baud_rate.baud);
    } else {
        map->baud_rate.real_baud = hal_ll_baud_real_value;

        set_reg_bit( hal_ll_hw_reg->uart_ucon0_reg_addr, HAL_LL_UART_BRGS_BIT );

        write_reg( hal_ll_hw_reg->uart_brgl_reg_addr, hal_ll_baud_value & HAL_LL_NIBBLE_LOW_16BIT );

        write_reg( hal_ll_hw_reg->uart_brgh_reg_addr, hal_ll_baud_value >> 8 );
    }
}

static void hal_ll_uart_set_stop_bits_bare_metal( hal_ll_uart_hw_specifics_map_t *map ) {
    const hal_ll_uart_base_handle_t *hal_ll_hw_reg = hal_ll_uart_get_base_struct(map->base);

    switch ( map->stop_bit )
    {
        case HAL_LL_UART_STOP_BITS_ONE:
            // ONE STOP BIT BY DEFAULT AFTER RESET
            break;
        case HAL_LL_UART_STOP_BITS_ONE_AND_A_HALF:
            set_reg_bit( hal_ll_hw_reg->uart_ucon2_reg_addr, HAL_LL_UART_STP_STOP_BITS_ONE_AND_A_HALF );
            break;
        case HAL_LL_UART_STOP_BITS_TWO:
            write_reg( hal_ll_hw_reg->uart_ucon2_reg_addr, HAL_LL_UART_STP_STOP_BITS_TWO_MASK );
            break;

        default:
            break;
    }
}

static void hal_ll_uart_set_data_bits_bare_metal( hal_ll_uart_hw_specifics_map_t *map ) {
    const hal_ll_uart_base_handle_t *hal_ll_hw_reg = hal_ll_uart_get_base_struct(map->base);

    switch ( map->data_bit )
    {
        case HAL_LL_UART_DATA_BITS_7:
            set_reg_bit( hal_ll_hw_reg->uart_ucon0_reg_addr, HAL_LL_UART_MODE_7_BIT );
            break;
        case HAL_LL_UART_DATA_BITS_8:
            // 8-BIT MODE BY DEFAULT AFTER RESET
            break;
        case HAL_LL_UART_DATA_BITS_9:
            set_reg_bit( hal_ll_hw_reg->uart_ucon0_reg_addr, HAL_LL_UART_MODE_9_BIT );
            break;

        default:
            break;
    }
}

static void hal_ll_uart_set_parity_bare_metal( hal_ll_uart_hw_specifics_map_t *map ) {
    const hal_ll_uart_base_handle_t *hal_ll_hw_reg = hal_ll_uart_get_base_struct(map->base);

    switch ( map->parity )
    {
        case HAL_LL_UART_PARITY_NONE:
            // NO PARITY BY DEFAULT AFTER RESET
            break;
        case HAL_LL_UART_PARITY_EVEN:
            write_reg( hal_ll_hw_reg->uart_ucon0_reg_addr, HAL_LL_UART_PARITY_EVEN_MASK );
            break;
        case HAL_LL_UART_PARITY_ODD:
            set_reg_bit( hal_ll_hw_reg->uart_ucon0_reg_addr, HAL_LL_UART_PARITY_ODD_BIT );
            break;

        default:
            break;
    }
}

static void hal_ll_uart_set_module( const hal_ll_uart_base_handle_t *hal_ll_hw_reg, hal_ll_uart_state_t pin_state ) {
    switch ( pin_state )
    {
        case HAL_LL_UART_DISABLE:
            clear_reg_bit( hal_ll_hw_reg->uart_ucon1_reg_addr, HAL_LL_UART_ON_BIT );
            break;

        case HAL_LL_UART_ENABLE:
            set_reg_bit( hal_ll_hw_reg->uart_ucon1_reg_addr, HAL_LL_UART_ON_BIT );
            break;

        default:
            break;
    }

}

static void hal_ll_uart_set_transmitter( const hal_ll_uart_base_handle_t *hal_ll_hw_reg, hal_ll_uart_state_t pin_state ) {
    switch ( pin_state )
    {
        case HAL_LL_UART_DISABLE:
            clear_reg_bit( hal_ll_hw_reg->uart_ucon0_reg_addr, HAL_LL_UART_TXEN_BIT );
            break;

        case HAL_LL_UART_ENABLE:
            set_reg_bit( hal_ll_hw_reg->uart_ucon0_reg_addr, HAL_LL_UART_TXEN_BIT );
            break;

        default:
            break;
    }
}

static void hal_ll_uart_set_receiver( const hal_ll_uart_base_handle_t *hal_ll_hw_reg, hal_ll_uart_state_t pin_state ) {
    switch ( pin_state )
    {
        case HAL_LL_UART_DISABLE:
            clear_reg_bit( hal_ll_hw_reg->uart_ucon0_reg_addr, HAL_LL_UART_RXEN_BIT );
            break;

        case HAL_LL_UART_ENABLE:
            set_reg_bit( hal_ll_hw_reg->uart_ucon0_reg_addr, HAL_LL_UART_RXEN_BIT );
            break;

        default:
            break;
    }
}

static void hal_ll_uart_clear_regs( const hal_ll_uart_base_handle_t *hal_ll_hw_reg ) {
    clear_reg( hal_ll_hw_reg->uart_ucon0_reg_addr );
    clear_reg( hal_ll_hw_reg->uart_ucon1_reg_addr );
    clear_reg( hal_ll_hw_reg->uart_ucon2_reg_addr );
}

static void hal_ll_i2c_hw_ansel_set( hal_ll_uart_hw_specifics_map_t *map ) {
    const hal_ll_uart_base_handle_t *hal_ll_hw_reg = hal_ll_uart_get_base_struct(map->base);
    hal_ll_gpio_pin_t local_pin;

    /*
     * Configures TX and RX pins as output/input by clearing/setting
     * corresponding TRIS bits.
     */
    hal_ll_gpio_configure_pin(&local_pin, map->pins.tx_pin.pin_name, HAL_LL_GPIO_DIGITAL_OUTPUT);
    hal_ll_gpio_configure_pin(&local_pin, map->pins.rx_pin.pin_name, HAL_LL_GPIO_DIGITAL_INPUT);
}

static void hal_ll_uart_hw_init( hal_ll_uart_hw_specifics_map_t *map ) {
    hal_ll_uart_clear_regs( map->base );

    hal_ll_uart_set_data_bits_bare_metal( map );

    hal_ll_uart_set_parity_bare_metal( map );

    hal_ll_uart_set_stop_bits_bare_metal( map );

    hal_ll_uart_set_baud_bare_metal( map );

    hal_ll_uart_set_transmitter( map->base, HAL_LL_UART_ENABLE );

    hal_ll_uart_set_receiver( map->base, HAL_LL_UART_ENABLE );

    hal_ll_uart_set_module( map->base, HAL_LL_UART_ENABLE );
}

static void hal_ll_uart_init( hal_ll_uart_hw_specifics_map_t *map ) {
    /*!< @brief Static, because clock doesn't change during runtime */
    static uint32_t hal_ll_clock_value;

    hal_ll_clock_value = Get_Fosc_kHz();

    hal_ll_uart_set_module_power( map, true );

    hal_ll_i2c_hw_ansel_set( map );

    hal_ll_uart_hw_init( map );

    hal_ll_uart_wait_for_sync(hal_ll_clock_value);
}

/*!< @brief Turn reentrancy check off for functions used in interrupt routines */
#pragma ReentrancyCheck OFF hal_ll_uart_get_specifics, hal_ll_uart_irq_disable, hal_ll_core_disable_irq
// ------------------------------------------------------------------------- END
