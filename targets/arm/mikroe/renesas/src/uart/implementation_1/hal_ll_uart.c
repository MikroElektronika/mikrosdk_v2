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

#include "hal_ll_sci.h"
#include "hal_ll_uart.h"
#include "hal_ll_gpio.h"
#include "hal_ll_core.h"
#include "hal_ll_mstpcr.h"
#include "hal_ll_core_defines.h"
#include "hal_ll_uart_pin_map.h"

/*!< @brief Local handle list */
static volatile hal_ll_uart_handle_register_t hal_ll_module_state[ UART_MODULE_COUNT ] = { (handle_t *)NULL, (handle_t *)NULL, false };

// ------------------------------------------------------------- PRIVATE MACROS
/*!< @brief Helper macro for getting hal_ll_module_state address. */
#define hal_ll_uart_get_module_state_address ((hal_ll_uart_handle_register_t *)*handle)
/*!< @brief Helper macro for getting module specific control register structure base address. */
#define hal_ll_uart_get_handle (hal_ll_uart_handle_register_t *)hal_ll_uart_get_module_state_address->hal_ll_uart_handle
/*!< @brief Helper macro for getting module specific control register structure. */
#define hal_ll_uart_get_base_struct(_handle) ((hal_ll_uart_base_handle_t *)_handle)
/*!< @brief Helper macro for getting module specific base address directly from HAL layer handle. */
#define hal_ll_uart_get_base_from_hal_handle ((hal_ll_uart_hw_specifics_map_t *)((hal_ll_uart_handle_register_t *)\
                                             (((hal_ll_uart_handle_register_t *)(handle))->hal_ll_uart_handle))->hal_ll_uart_handle)->base

/*!< @brief Macros used for calculating actual baud rate value and error value. */
#define hal_ll_uart_get_baud_rate(futa, brr) (futa / (brr * 2))

/*!< @brief Macros defining bit location. */
#define HAL_LL_UARTA_ASCTA_OVECTA   0
#define HAL_LL_UARTA_ASCTA_FECTA    1
#define HAL_LL_UARTA_ASCTA_PECTA    2

#define HAL_LL_UARTA_ASISA_OVEA     0
#define HAL_LL_UARTA_ASISA_FEA      1
#define HAL_LL_UARTA_ASISA_PEA      2
#define HAL_LL_UARTA_ASISA_TXSFA    4
#define HAL_LL_UARTA_ASISA_TXBFA    5

#define HAL_LL_UARTA_ASIMA0_ISRMA   0
#define HAL_LL_UARTA_ASIMA0_ISSMA   1
#define HAL_LL_UARTA_ASIMA0_RXEA    5
#define HAL_LL_UARTA_ASIMA0_TXEA    6
#define HAL_LL_UARTA_ASIMA0_EN      7

#define HAL_LL_UARTA_ASIMA1_DIR     1
#define HAL_LL_UARTA_ASIMA1_SL      2

/*!< @brief Macros defining register bit values. */
#define HAL_LL_UARTA_ASIMA1_CL_MASK         0x18
#define HAL_LL_UARTA_ASIMA1_CL_MASK_7BITS   0x10
#define HAL_LL_UARTA_ASIMA1_CL_MASK_8BITS   0x18
#define HAL_LL_UARTA_ASIMA1_PS_MASK         0x60
#define HAL_LL_UARTA_ASIMA1_PS_MASK_ODD     0x40
#define HAL_LL_UARTA_ASIMA1_PS_MASK_EVEN    0x60

/* @brief Macros used for interrupt handling. */
#define HAL_LL_SCI_ERI_INTERRUPT_PRIORITY   1
#define HAL_LL_SCI_RXI_INTERRUPT_PRIORITY   2
#define HAL_LL_SCI_TXI_INTERRUPT_PRIORITY   3
#define HAL_LL_SCI_ICU_IELSR_IR             16
#if (defined(R7FA2E3) || defined(R7FA2E1) || defined(R7FA2L1) || defined(R7FA2L2))
#define HAL_LL_SCI_MAXIMUM_INTERRUPTS_NUM   32
#else
#define HAL_LL_SCI_MAXIMUM_INTERRUPTS_NUM   30
#endif

/*!< @brief Structure used for linking interrupt event. */
typedef struct st_icu_ielsr_t {
    uint32_t ielsr[32];
} icu_ielsr_t;

icu_ielsr_t *icu_elsr_register = HAL_LL_ICU_IELSR_BASE_ADDRESS;

/**
 * @brief UART ISR vector table.
 *
 * An array of ISR function pointers for the enabled UART modules.
 * Each module contributes two entries to the table to accommodate
 * both transmit and receive.
 *
 * The table is placed in the `.application_vectors` section and marked
 * as `__used__` to ensure it's not optimized away by the linker.
 */
// For Cortex-M23 MCUs IELSR register values and capabilities are fixed.
// For more information see Table 12.7 in RA2E3 Hardware User Manual.
#if (defined(R7FA2E3) || defined(R7FA2E1) || defined(R7FA2L1))
const fsp_vector_t g_vector_table[HAL_LL_SCI_MAXIMUM_INTERRUPTS_NUM] __attribute__(( section( ".application_vectors" ))) __attribute__(( __used__ )) = {
    #ifdef SCI_MODULE_0
    SCI0_RXI_IRQHandler,   // IELSR0
    SCI0_TXI_IRQHandler,   // IELSR1
    ( void *)0,
    SCI0_ERI_IRQHandler,   // IELSR3
    #else
    ( void *)0,
    ( void *)0,
    ( void *)0,
    ( void *)0,
    #endif
    ( void *)0,
    ( void *)0,
    ( void *)0,
    ( void *)0,
    #ifdef SCI_MODULE_1
    SCI1_RXI_IRQHandler,   // IELSR8
    SCI1_TXI_IRQHandler,   // IELSR9
    ( void *)0,
    SCI1_ERI_IRQHandler,   // IELSR11
    #else
    ( void *)0,
    ( void *)0,
    ( void *)0,
    ( void *)0,
    #endif
    #ifdef SCI_MODULE_2
    SCI2_RXI_IRQHandler,   // IELSR12
    SCI2_TXI_IRQHandler,   // IELSR13
    ( void *)0,
    SCI2_ERI_IRQHandler,   // IELSR15
    #else
    ( void *)0,
    ( void *)0,
    ( void *)0,
    ( void *)0,
    #endif
    ( void *)0,
    ( void *)0,
    ( void *)0,
    ( void *)0,
    ( void *)0,
    ( void *)0,
    ( void *)0,
    ( void *)0,
    ( void *)0,
    ( void *)0,
    ( void *)0,
    ( void *)0,
    #ifdef SCI_MODULE_9
    SCI9_RXI_IRQHandler,   // IELSR28
    SCI9_TXI_IRQHandler,   // IELSR29
    ( void *)0,
    SCI9_ERI_IRQHandler    // IELSR31
    #else
    ( void *)0,
    ( void *)0,
    ( void *)0,
    ( void *)0
    #endif
};
#elif defined(R7FA2L2)
const fsp_vector_t g_vector_table[HAL_LL_SCI_MAXIMUM_INTERRUPTS_NUM] __attribute__(( section( ".application_vectors" ))) __attribute__(( __used__ )) = {
    SCI0_RXI_IRQHandler,        // IELSR0
    SCI0_TXI_IRQHandler,        // IELSR1
    ( void *)0,
    SCI0_ERI_IRQHandler,        // IELSR3
    ( void *)0,
    ( void *)0,
    ( void *)0,
    UARTA0_ERI_IRQHandler,   // IELSR7
    SCI1_RXI_IRQHandler,        // IELSR8
    SCI1_TXI_IRQHandler,        // IELSR9
    UARTA0_TXI_IRQHandler,    // IELSR10
    SCI1_ERI_IRQHandler,        // IELSR11
    SCI2_RXI_IRQHandler,        // IELSR12
    SCI2_TXI_IRQHandler,        // IELSR13
    ( void *)0,
    SCI2_ERI_IRQHandler,        // IELSR15
    UARTA0_RXI_IRQHandler,    // IELSR16
    UARTA1_TXI_IRQHandler,    // IELSR17
    UARTA1_RXI_IRQHandler,    // IELSR18
    ( void *)0,
    ( void *)0,
    ( void *)0,
    ( void *)0,
    UARTA1_ERI_IRQHandler,   // IELSR23
    ( void *)0,
    ( void *)0,
    ( void *)0,
    ( void *)0,
    SCI9_RXI_IRQHandler,        // IELSR28
    SCI9_TXI_IRQHandler,        // IELSR29
    ( void *)0,
    SCI9_ERI_IRQHandler         // IELSR31
};
#else
const fsp_vector_t g_vector_table[HAL_LL_SCI_MAXIMUM_INTERRUPTS_NUM] __attribute__(( section( ".application_vectors" ))) __attribute__(( __used__ )) = {
    #ifdef SCI_MODULE_0
    SCI0_TXI_IRQHandler,
    SCI0_RXI_IRQHandler,
    SCI0_ERI_IRQHandler,
    #else
    ( void *)0,
    ( void *)0,
    ( void *)0,
    #endif
    #ifdef SCI_MODULE_1
    SCI1_TXI_IRQHandler,
    SCI1_RXI_IRQHandler,
    SCI1_ERI_IRQHandler,
    #else
    ( void *)0,
    ( void *)0,
    ( void *)0,
    #endif
    #ifdef SCI_MODULE_2
    SCI2_TXI_IRQHandler,
    SCI2_RXI_IRQHandler,
    SCI2_ERI_IRQHandler,
    #else
    ( void *)0,
    ( void *)0,
    ( void *)0,
    #endif
    #ifdef SCI_MODULE_3
    SCI3_TXI_IRQHandler,
    SCI3_RXI_IRQHandler,
    SCI3_ERI_IRQHandler,
    #else
    ( void *)0,
    ( void *)0,
    ( void *)0,
    #endif
    #ifdef SCI_MODULE_4
    SCI4_TXI_IRQHandler,
    SCI4_RXI_IRQHandler,
    SCI4_ERI_IRQHandler,
    #else
    ( void *)0,
    ( void *)0,
    ( void *)0,
    #endif
    #ifdef SCI_MODULE_5
    SCI5_TXI_IRQHandler,
    SCI5_RXI_IRQHandler,
    SCI5_ERI_IRQHandler,
    #else
    ( void *)0,
    ( void *)0,
    ( void *)0,
    #endif
    #ifdef SCI_MODULE_6
    SCI6_TXI_IRQHandler,
    SCI6_RXI_IRQHandler,
    SCI6_ERI_IRQHandler,
    #else
    ( void *)0,
    ( void *)0,
    ( void *)0,
    #endif
    #ifdef SCI_MODULE_7
    SCI7_TXI_IRQHandler,
    SCI7_RXI_IRQHandler,
    SCI7_ERI_IRQHandler,
    #elif UART_MODULE_0
    UARTA0_TXI_IRQHandler,
    UARTA0_RXI_IRQHandler,
    UARTA0_ERI_IRQHandler,
    #else
    ( void *)0,
    ( void *)0,
    ( void *)0,
    #endif
    #ifdef SCI_MODULE_8
    SCI8_TXI_IRQHandler,
    SCI8_RXI_IRQHandler,
    SCI8_ERI_IRQHandler,
    #elif UART_MODULE_1
    UARTA1_TXI_IRQHandler,
    UARTA1_RXI_IRQHandler,
    UARTA1_ERI_IRQHandler,
    #else
    ( void *)0,
    ( void *)0,
    ( void *)0,
    #endif
    #ifdef SCI_MODULE_9
    SCI9_TXI_IRQHandler,
    SCI9_RXI_IRQHandler,
    SCI9_ERI_IRQHandler
    #else
    ( void *)0,
    ( void *)0,
    ( void *)0
    #endif
};
#endif

/*!< @brief UART HW register structure. */
typedef struct {
    uint8_t txba;        /* Transmit Buffer Register             */
    uint8_t rxba;        /* Receive Buffer Register              */
    uint8_t asima0;      /* Operation Mode Setting Register 0    */
    uint8_t asima1;      /* Operation Mode Setting Register 1    */
    uint8_t brgca;       /* Baud Rate Generator Control Register */
    uint8_t asisa;       /* Status Register                      */
    uint8_t ascta;       /* Status Clear Trigger Register        */
} hal_ll_uart_base_handle_t;

/*!< @brief UART baud rate structure. */
typedef struct {
    uint32_t baud;
    uint32_t real_baud;
} hal_ll_uart_baud_t;

/*!< @brief UART hw specific structure. */
typedef struct {
    hal_ll_base_addr_t base;
    hal_ll_pin_name_t module_index;
    hal_ll_uart_pins_t pins;
    hal_ll_uart_baud_t baud_rate;
    hal_ll_uart_parity_t parity;
    hal_ll_uart_stop_bits_t stop_bit;
    hal_ll_uart_data_bits_t data_bit;
    uint32_t timeout_polling_write;
    bool is_sci_module;
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
    #ifdef SCI_MODULE_0
    {HAL_LL_SCI0_BASE_ADDR, hal_ll_uart_module_num( SCI_MODULE_0 ), {HAL_LL_PIN_NC, 0, HAL_LL_PIN_NC, 0}, {115200, 0}, HAL_LL_UART_PARITY_DEFAULT, HAL_LL_UART_STOP_BITS_DEFAULT, HAL_LL_UART_DATA_BITS_DEFAULT, 10000, 1},
    #endif
    #ifdef SCI_MODULE_1
    {HAL_LL_SCI1_BASE_ADDR, hal_ll_uart_module_num( SCI_MODULE_1 ), {HAL_LL_PIN_NC, 0, HAL_LL_PIN_NC, 0}, {115200, 0}, HAL_LL_UART_PARITY_DEFAULT, HAL_LL_UART_STOP_BITS_DEFAULT, HAL_LL_UART_DATA_BITS_DEFAULT, 10000, 1},
    #endif
    #ifdef SCI_MODULE_2
    {HAL_LL_SCI2_BASE_ADDR, hal_ll_uart_module_num( SCI_MODULE_2 ), {HAL_LL_PIN_NC, 0, HAL_LL_PIN_NC, 0}, {115200, 0}, HAL_LL_UART_PARITY_DEFAULT, HAL_LL_UART_STOP_BITS_DEFAULT, HAL_LL_UART_DATA_BITS_DEFAULT, 10000, 1},
    #endif
    #ifdef SCI_MODULE_3
    {HAL_LL_SCI3_BASE_ADDR, hal_ll_uart_module_num( SCI_MODULE_3 ), {HAL_LL_PIN_NC, 0, HAL_LL_PIN_NC, 0}, {115200, 0}, HAL_LL_UART_PARITY_DEFAULT, HAL_LL_UART_STOP_BITS_DEFAULT, HAL_LL_UART_DATA_BITS_DEFAULT, 10000, 1},
    #endif
    #ifdef SCI_MODULE_4
    {HAL_LL_SCI4_BASE_ADDR, hal_ll_uart_module_num( SCI_MODULE_4 ), {HAL_LL_PIN_NC, 0, HAL_LL_PIN_NC, 0}, {115200, 0}, HAL_LL_UART_PARITY_DEFAULT, HAL_LL_UART_STOP_BITS_DEFAULT, HAL_LL_UART_DATA_BITS_DEFAULT, 10000, 1},
    #endif
    #ifdef SCI_MODULE_5
    {HAL_LL_SCI5_BASE_ADDR, hal_ll_uart_module_num( SCI_MODULE_5 ), {HAL_LL_PIN_NC, 0, HAL_LL_PIN_NC, 0}, {115200, 0}, HAL_LL_UART_PARITY_DEFAULT, HAL_LL_UART_STOP_BITS_DEFAULT, HAL_LL_UART_DATA_BITS_DEFAULT, 10000, 1},
    #endif
    #ifdef SCI_MODULE_6
    {HAL_LL_SCI6_BASE_ADDR, hal_ll_uart_module_num( SCI_MODULE_6 ), {HAL_LL_PIN_NC, 0, HAL_LL_PIN_NC, 0}, {115200, 0}, HAL_LL_UART_PARITY_DEFAULT, HAL_LL_UART_STOP_BITS_DEFAULT, HAL_LL_UART_DATA_BITS_DEFAULT, 10000, 1},
    #endif
    #ifdef SCI_MODULE_7
    {HAL_LL_SCI7_BASE_ADDR, hal_ll_uart_module_num( SCI_MODULE_7 ), {HAL_LL_PIN_NC, 0, HAL_LL_PIN_NC, 0}, {115200, 0}, HAL_LL_UART_PARITY_DEFAULT, HAL_LL_UART_STOP_BITS_DEFAULT, HAL_LL_UART_DATA_BITS_DEFAULT, 10000, 1},
    #endif
    #ifdef SCI_MODULE_8
    {HAL_LL_SCI8_BASE_ADDR, hal_ll_uart_module_num( SCI_MODULE_8 ), {HAL_LL_PIN_NC, 0, HAL_LL_PIN_NC, 0}, {115200, 0}, HAL_LL_UART_PARITY_DEFAULT, HAL_LL_UART_STOP_BITS_DEFAULT, HAL_LL_UART_DATA_BITS_DEFAULT, 10000, 1},
    #endif
    #ifdef SCI_MODULE_9
    {HAL_LL_SCI9_BASE_ADDR, hal_ll_uart_module_num( SCI_MODULE_9 ), {HAL_LL_PIN_NC, 0, HAL_LL_PIN_NC, 0}, {115200, 0}, HAL_LL_UART_PARITY_DEFAULT, HAL_LL_UART_STOP_BITS_DEFAULT, HAL_LL_UART_DATA_BITS_DEFAULT, 10000, 1},
    #endif
    #ifdef UART_MODULE_0
    {HAL_LL_UARTA0_BASE_ADDR, hal_ll_uart_module_num( UART_MODULE_0 ), {HAL_LL_PIN_NC, 0, HAL_LL_PIN_NC, 0}, {115200, 0}, HAL_LL_UART_PARITY_DEFAULT, HAL_LL_UART_STOP_BITS_DEFAULT, HAL_LL_UART_DATA_BITS_DEFAULT, 10000, 0},
    #endif
    #ifdef UART_MODULE_1
    {HAL_LL_UARTA1_BASE_ADDR, hal_ll_uart_module_num( UART_MODULE_1 ), {HAL_LL_PIN_NC, 0, HAL_LL_PIN_NC, 0}, {115200, 0}, HAL_LL_UART_PARITY_DEFAULT, HAL_LL_UART_STOP_BITS_DEFAULT, HAL_LL_UART_DATA_BITS_DEFAULT, 10000, 0},
    #endif

    {HAL_LL_MODULE_ERROR, HAL_LL_MODULE_ERROR, {HAL_LL_PIN_NC, 0, HAL_LL_PIN_NC, 0}, {0, 0}, HAL_LL_MODULE_ERROR, HAL_LL_MODULE_ERROR, HAL_LL_MODULE_ERROR, 10000 }
};
/*!< @brief UART hardware specific info. */

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
  * index numbers have to be the same for both pins.
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
 * Maps pin names and alternate function values for
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
  * Sets adequate value for alternate function settings.
  * This function must be called if UART is to work.
  * Based on value of hal_ll_state, alternate functions can be
  * set or cleared.
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
  * Initializes UART module clock on hardware level, based on beforehand
  * set configuration and module handler.
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
static void hal_ll_uart_clear_regs( hal_ll_uart_base_handle_t *hal_ll_hw_reg );

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
static void hal_ll_uart_set_module( hal_ll_uart_base_handle_t *hal_ll_hw_reg, hal_ll_uart_state_t pin_state );

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
static void hal_ll_uart_set_transmitter( hal_ll_uart_base_handle_t *hal_ll_hw_reg, hal_ll_uart_state_t pin_state );

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
static void hal_ll_uart_set_receiver( hal_ll_uart_base_handle_t *hal_ll_hw_reg, hal_ll_uart_state_t pin_state );

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
 * 2. Sets data bit value
 * 3. Sets parity value
 * 4. Sets stop bit value
 * 5. Sets baud rate value
 * 6. Enables transmit pin
 * 7. Enables receive pin
 * 8. Enables clock gate for specific module
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
    if ( (pin_check_result = hal_ll_uart_check_pins( tx_pin, rx_pin, &index_list, handle_map )) == HAL_LL_PIN_NC ) {
        return HAL_LL_UART_WRONG_PINS;
    };

    if ( (hal_ll_uart_hw_specifics_map[pin_check_result].pins.tx_pin.pin_name != tx_pin) ||
         (hal_ll_uart_hw_specifics_map[pin_check_result].pins.rx_pin.pin_name != rx_pin) )
    {
        hal_ll_uart_alternate_functions_set_state( &hal_ll_uart_hw_specifics_map[ pin_check_result ], false );

        hal_ll_uart_map_pins( pin_check_result, &index_list );

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

    low_level_handle->init_ll_state = false;

    hal_ll_uart_hw_specifics_map_local->stop_bit = stop_bit;

    hal_ll_uart_init( hal_ll_uart_hw_specifics_map_local );

    low_level_handle->init_ll_state = true;

    return HAL_LL_UART_SUCCESS;
}

hal_ll_err_t hal_ll_uart_set_data_bits( handle_t *handle, hal_ll_uart_data_bits_t data_bit ) {
    low_level_handle = hal_ll_uart_get_handle;
    hal_ll_uart_hw_specifics_map_local = hal_ll_get_specifics( hal_ll_uart_get_module_state_address );

    // Chips using this implementation do not support 7 bit data.
    if ( ( data_bit < HAL_LL_UART_DATA_BITS_7 ) || ( data_bit > HAL_LL_UART_DATA_BITS_9 ) ) {
        return HAL_LL_UART_MODULE_ERROR;
    }

    low_level_handle->init_ll_state = false;

    hal_ll_uart_hw_specifics_map_local->data_bit = data_bit;

    hal_ll_uart_init( hal_ll_uart_hw_specifics_map_local );

    low_level_handle->init_ll_state = true;

    return HAL_LL_UART_SUCCESS;
}

void hal_ll_uart_set_polling_write_timeout( handle_t *handle, uint32_t timeout ) {
    hal_ll_uart_hw_specifics_map_local = hal_ll_get_specifics(hal_ll_uart_get_module_state_address);

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

        if ( hal_ll_uart_hw_specifics_map_local->is_sci_module )
            hal_ll_sci_uart_clear_regs( hal_ll_uart_hw_specifics_map_local );
        else
            hal_ll_uart_clear_regs( hal_ll_uart_hw_specifics_map_local->base );
        hal_ll_uart_set_clock( hal_ll_uart_hw_specifics_map_local, false );

        hal_ll_uart_hw_specifics_map_local->pins.tx_pin.pin_name = HAL_LL_PIN_NC;
        hal_ll_uart_hw_specifics_map_local->pins.tx_pin.pin_af = 0;
        hal_ll_uart_hw_specifics_map_local->pins.rx_pin.pin_name = HAL_LL_PIN_NC;
        hal_ll_uart_hw_specifics_map_local->pins.rx_pin.pin_af = 0;

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

    /*
     * As Renesas MCUs don't have fixed IVT table for peripherals, we need
     * to assign UART interrupts to the corresponding NVIC channels manually.
     * Memory mapping is achieved by defining interrupts service routince in
     * .application_vectors memory region with the help of g_vector_table.
     */
    switch ( hal_ll_uart_hw_specifics_map_local->module_index ) {
        #ifdef SCI_MODULE_0
        case hal_ll_uart_module_num( SCI_MODULE_0 ):
            icu_elsr_register->ielsr[ SCI0_TXI_NVIC ] = SCI0_TXI_EVENT;
            hal_ll_core_enable_irq( SCI0_TXI_NVIC );
            icu_elsr_register->ielsr[ SCI0_RXI_NVIC ] = SCI0_RXI_EVENT;
            hal_ll_core_enable_irq( SCI0_RXI_NVIC );
            icu_elsr_register->ielsr[ SCI0_ERI_NVIC ] = SCI0_ERI_EVENT;
            hal_ll_core_enable_irq( SCI0_ERI_NVIC );

            // Set the interrupt priority to handle all received data properly.
            hal_ll_core_set_priority_irq( SCI0_ERI_NVIC, HAL_LL_SCI_ERI_INTERRUPT_PRIORITY );
            hal_ll_core_set_priority_irq( SCI0_RXI_NVIC, HAL_LL_SCI_RXI_INTERRUPT_PRIORITY );
            hal_ll_core_set_priority_irq( SCI0_TXI_NVIC, HAL_LL_SCI_TXI_INTERRUPT_PRIORITY );
            break;
        #endif
        #ifdef SCI_MODULE_1
        case hal_ll_uart_module_num( SCI_MODULE_1 ):
            icu_elsr_register->ielsr[ SCI1_TXI_NVIC ] = SCI1_TXI_EVENT;
            hal_ll_core_enable_irq( SCI1_TXI_NVIC );
            icu_elsr_register->ielsr[ SCI1_RXI_NVIC ] = SCI1_RXI_EVENT;
            hal_ll_core_enable_irq( SCI1_RXI_NVIC );
            icu_elsr_register->ielsr[ SCI1_ERI_NVIC ] = SCI1_ERI_EVENT;
            hal_ll_core_enable_irq( SCI1_ERI_NVIC );

            // Set the interrupt priority to handle all received data properly.
            hal_ll_core_set_priority_irq( SCI1_ERI_NVIC, HAL_LL_SCI_ERI_INTERRUPT_PRIORITY );
            hal_ll_core_set_priority_irq( SCI1_RXI_NVIC, HAL_LL_SCI_RXI_INTERRUPT_PRIORITY );
            hal_ll_core_set_priority_irq( SCI1_TXI_NVIC, HAL_LL_SCI_TXI_INTERRUPT_PRIORITY );
            break;
        #endif
        #ifdef SCI_MODULE_2
        case hal_ll_uart_module_num( SCI_MODULE_2 ):
            icu_elsr_register->ielsr[ SCI2_TXI_NVIC ] = SCI2_TXI_EVENT;
            hal_ll_core_enable_irq( SCI2_TXI_NVIC );
            icu_elsr_register->ielsr[ SCI2_RXI_NVIC ] = SCI2_RXI_EVENT;
            hal_ll_core_enable_irq( SCI2_RXI_NVIC );
            icu_elsr_register->ielsr[ SCI2_ERI_NVIC ] = SCI2_ERI_EVENT;
            hal_ll_core_enable_irq( SCI2_ERI_NVIC );

            // Set the interrupt priority to handle all received data properly.
            hal_ll_core_set_priority_irq( SCI2_ERI_NVIC, HAL_LL_SCI_ERI_INTERRUPT_PRIORITY );
            hal_ll_core_set_priority_irq( SCI2_RXI_NVIC, HAL_LL_SCI_RXI_INTERRUPT_PRIORITY );
            hal_ll_core_set_priority_irq( SCI2_TXI_NVIC, HAL_LL_SCI_TXI_INTERRUPT_PRIORITY );
            break;
        #endif
        #ifdef SCI_MODULE_3
        case hal_ll_uart_module_num( SCI_MODULE_3 ):
            icu_elsr_register->ielsr[ SCI3_TXI_NVIC ] = SCI3_TXI_EVENT;
            hal_ll_core_enable_irq( SCI3_TXI_NVIC );
            icu_elsr_register->ielsr[ SCI3_RXI_NVIC ] = SCI3_RXI_EVENT;
            hal_ll_core_enable_irq( SCI3_RXI_NVIC );
            icu_elsr_register->ielsr[ SCI3_ERI_NVIC ] = SCI3_ERI_EVENT;
            hal_ll_core_enable_irq( SCI3_ERI_NVIC );

            // Set the interrupt priority to handle all received data properly.
            hal_ll_core_set_priority_irq( SCI3_ERI_NVIC, HAL_LL_SCI_ERI_INTERRUPT_PRIORITY );
            hal_ll_core_set_priority_irq( SCI3_RXI_NVIC, HAL_LL_SCI_RXI_INTERRUPT_PRIORITY );
            hal_ll_core_set_priority_irq( SCI3_TXI_NVIC, HAL_LL_SCI_TXI_INTERRUPT_PRIORITY );
            break;
        #endif
        #ifdef SCI_MODULE_4
        case hal_ll_uart_module_num( SCI_MODULE_4 ):
            icu_elsr_register->ielsr[ SCI4_TXI_NVIC ] = SCI4_TXI_EVENT;
            hal_ll_core_enable_irq( SCI4_TXI_NVIC );
            icu_elsr_register->ielsr[ SCI4_RXI_NVIC ] = SCI4_RXI_EVENT;
            hal_ll_core_enable_irq( SCI4_RXI_NVIC );
            icu_elsr_register->ielsr[ SCI4_ERI_NVIC ] = SCI4_ERI_EVENT;
            hal_ll_core_enable_irq( SCI4_ERI_NVIC );

            // Set the interrupt priority to handle all received data properly.
            hal_ll_core_set_priority_irq( SCI4_ERI_NVIC, HAL_LL_SCI_ERI_INTERRUPT_PRIORITY );
            hal_ll_core_set_priority_irq( SCI4_RXI_NVIC, HAL_LL_SCI_RXI_INTERRUPT_PRIORITY );
            hal_ll_core_set_priority_irq( SCI4_TXI_NVIC, HAL_LL_SCI_TXI_INTERRUPT_PRIORITY );
            break;
        #endif
        #ifdef SCI_MODULE_5
        case hal_ll_uart_module_num( SCI_MODULE_5 ):
            icu_elsr_register->ielsr[ SCI5_TXI_NVIC ] = SCI5_TXI_EVENT;
            hal_ll_core_enable_irq( SCI5_TXI_NVIC );
            icu_elsr_register->ielsr[ SCI5_RXI_NVIC ] = SCI5_RXI_EVENT;
            hal_ll_core_enable_irq( SCI5_RXI_NVIC );
            icu_elsr_register->ielsr[ SCI5_ERI_NVIC ] = SCI5_ERI_EVENT;
            hal_ll_core_enable_irq( SCI5_ERI_NVIC );

            // Set the interrupt priority to handle all received data properly.
            hal_ll_core_set_priority_irq( SCI5_ERI_NVIC, HAL_LL_SCI_ERI_INTERRUPT_PRIORITY );
            hal_ll_core_set_priority_irq( SCI5_RXI_NVIC, HAL_LL_SCI_RXI_INTERRUPT_PRIORITY );
            hal_ll_core_set_priority_irq( SCI5_TXI_NVIC, HAL_LL_SCI_TXI_INTERRUPT_PRIORITY );
            break;
        #endif
        #ifdef SCI_MODULE_6
        case hal_ll_uart_module_num( SCI_MODULE_6 ):
            icu_elsr_register->ielsr[ SCI6_TXI_NVIC ] = SCI6_TXI_EVENT;
            hal_ll_core_enable_irq( SCI6_TXI_NVIC );
            icu_elsr_register->ielsr[ SCI6_RXI_NVIC ] = SCI6_RXI_EVENT;
            hal_ll_core_enable_irq( SCI6_RXI_NVIC );
            icu_elsr_register->ielsr[ SCI6_ERI_NVIC ] = SCI6_ERI_EVENT;
            hal_ll_core_enable_irq( SCI6_ERI_NVIC );

            // Set the interrupt priority to handle all received data properly.
            hal_ll_core_set_priority_irq( SCI6_ERI_NVIC, HAL_LL_SCI_ERI_INTERRUPT_PRIORITY );
            hal_ll_core_set_priority_irq( SCI6_RXI_NVIC, HAL_LL_SCI_RXI_INTERRUPT_PRIORITY );
            hal_ll_core_set_priority_irq( SCI6_TXI_NVIC, HAL_LL_SCI_TXI_INTERRUPT_PRIORITY );
            break;
        #endif
        #ifdef SCI_MODULE_7
        case hal_ll_uart_module_num( SCI_MODULE_7 ):
            icu_elsr_register->ielsr[ SCI7_TXI_NVIC ] = SCI7_TXI_EVENT;
            hal_ll_core_enable_irq( SCI7_TXI_NVIC );
            icu_elsr_register->ielsr[ SCI7_RXI_NVIC ] = SCI7_RXI_EVENT;
            hal_ll_core_enable_irq( SCI7_RXI_NVIC );
            icu_elsr_register->ielsr[ SCI7_ERI_NVIC ] = SCI7_ERI_EVENT;
            hal_ll_core_enable_irq( SCI7_ERI_NVIC );

            // Set the interrupt priority to handle all received data properly.
            hal_ll_core_set_priority_irq( SCI7_ERI_NVIC, HAL_LL_SCI_ERI_INTERRUPT_PRIORITY );
            hal_ll_core_set_priority_irq( SCI7_RXI_NVIC, HAL_LL_SCI_RXI_INTERRUPT_PRIORITY );
            hal_ll_core_set_priority_irq( SCI7_TXI_NVIC, HAL_LL_SCI_TXI_INTERRUPT_PRIORITY );
            break;
        #endif
        #ifdef SCI_MODULE_8
        case hal_ll_uart_module_num( SCI_MODULE_8 ):
            icu_elsr_register->ielsr[ SCI8_TXI_NVIC ] = SCI8_TXI_EVENT;
            hal_ll_core_enable_irq( SCI8_TXI_NVIC );
            icu_elsr_register->ielsr[ SCI8_RXI_NVIC ] = SCI8_RXI_EVENT;
            hal_ll_core_enable_irq( SCI8_RXI_NVIC );
            icu_elsr_register->ielsr[ SCI8_ERI_NVIC ] = SCI8_ERI_EVENT;
            hal_ll_core_enable_irq( SCI8_ERI_NVIC );

            // Set the interrupt priority to handle all received data properly.
            hal_ll_core_set_priority_irq( SCI8_ERI_NVIC, HAL_LL_SCI_ERI_INTERRUPT_PRIORITY );
            hal_ll_core_set_priority_irq( SCI8_RXI_NVIC, HAL_LL_SCI_RXI_INTERRUPT_PRIORITY );
            hal_ll_core_set_priority_irq( SCI8_TXI_NVIC, HAL_LL_SCI_TXI_INTERRUPT_PRIORITY );
            break;
        #endif
        #ifdef SCI_MODULE_9
        case hal_ll_uart_module_num( SCI_MODULE_9 ):
            icu_elsr_register->ielsr[ SCI9_TXI_NVIC ] = SCI9_TXI_EVENT;
            hal_ll_core_enable_irq( SCI9_TXI_NVIC );
            icu_elsr_register->ielsr[ SCI9_RXI_NVIC ] = SCI9_RXI_EVENT;
            hal_ll_core_enable_irq( SCI9_RXI_NVIC );
            icu_elsr_register->ielsr[ SCI9_ERI_NVIC ] = SCI9_ERI_EVENT;
            hal_ll_core_enable_irq( SCI9_ERI_NVIC );

            // Set the interrupt priority to handle all received data properly.
            hal_ll_core_set_priority_irq( SCI9_ERI_NVIC, HAL_LL_SCI_ERI_INTERRUPT_PRIORITY );
            hal_ll_core_set_priority_irq( SCI9_RXI_NVIC, HAL_LL_SCI_RXI_INTERRUPT_PRIORITY );
            hal_ll_core_set_priority_irq( SCI9_TXI_NVIC, HAL_LL_SCI_TXI_INTERRUPT_PRIORITY );
            break;
        #endif
        #ifdef UART_MODULE_0
        case hal_ll_uart_module_num( UART_MODULE_0 ):
            icu_elsr_register->ielsr[ UARTA0_TXI_NVIC ] = UARTA0_TXI_EVENT;
            hal_ll_core_enable_irq( UARTA0_TXI_NVIC );
            icu_elsr_register->ielsr[ UARTA0_RXI_NVIC ] = UARTA0_RXI_EVENT;
            hal_ll_core_enable_irq( UARTA0_RXI_NVIC );
            icu_elsr_register->ielsr[ UARTA0_ERI_NVIC ] = UARTA0_ERI_EVENT;
            hal_ll_core_enable_irq( UARTA0_ERI_NVIC );

            // Set the interrupt priority to handle all received data properly.
            hal_ll_core_set_priority_irq( UARTA0_ERI_NVIC, HAL_LL_SCI_ERI_INTERRUPT_PRIORITY );
            hal_ll_core_set_priority_irq( UARTA0_RXI_NVIC, HAL_LL_SCI_RXI_INTERRUPT_PRIORITY );
            hal_ll_core_set_priority_irq( UARTA0_TXI_NVIC, HAL_LL_SCI_TXI_INTERRUPT_PRIORITY );
            break;
        #endif
        #ifdef UART_MODULE_1
        case hal_ll_uart_module_num( UART_MODULE_1 ):
            icu_elsr_register->ielsr[ UARTA1_TXI_NVIC ] = UARTA1_TXI_EVENT;
            hal_ll_core_enable_irq( UARTA1_TXI_NVIC );
            icu_elsr_register->ielsr[ UARTA1_RXI_NVIC ] = UARTA1_RXI_EVENT;
            hal_ll_core_enable_irq( UARTA1_RXI_NVIC );
            icu_elsr_register->ielsr[ UARTA1_ERI_NVIC ] = UARTA1_ERI_EVENT;
            hal_ll_core_enable_irq( UARTA1_ERI_NVIC );

            // Set the interrupt priority to handle all received data properly.
            hal_ll_core_set_priority_irq( UARTA1_ERI_NVIC, HAL_LL_SCI_ERI_INTERRUPT_PRIORITY );
            hal_ll_core_set_priority_irq( UARTA1_RXI_NVIC, HAL_LL_SCI_RXI_INTERRUPT_PRIORITY );
            hal_ll_core_set_priority_irq( UARTA1_TXI_NVIC, HAL_LL_SCI_TXI_INTERRUPT_PRIORITY );
            break;
        #endif

        default:
            break;
    }
}

void hal_ll_uart_irq_enable( handle_t *handle, hal_ll_uart_irq_t irq ) {
    low_level_handle = hal_ll_uart_get_handle;
    hal_ll_uart_hw_specifics_map_local = hal_ll_get_specifics( hal_ll_uart_get_module_state_address );

    if ( hal_ll_uart_hw_specifics_map_local->is_sci_module ) {
        hal_ll_sci_uart_irq_enable( hal_ll_uart_hw_specifics_map_local, irq );
    } else {
        hal_ll_uart_base_handle_t *hal_ll_hw_reg = ( hal_ll_uart_base_handle_t *)hal_ll_uart_hw_specifics_map_local->base;

        switch ( irq ) {
            case HAL_LL_UART_IRQ_RX:
                set_reg_bit( &hal_ll_hw_reg->asima0, HAL_LL_UARTA_ASIMA0_RXEA );
                break;
            case HAL_LL_UART_IRQ_TX:
                set_reg_bit( &hal_ll_hw_reg->asima0, HAL_LL_UARTA_ASIMA0_TXEA );
                break;

            default:
                break;
        }


        // To trigger the TX interrupt RA MCUs require data to be written into transmit buffer both for UARTA.
        if ( HAL_LL_UART_IRQ_TX == irq )
            irq_handler( objects[ hal_ll_uart_hw_specifics_map_local->module_index ], HAL_LL_UART_IRQ_TX );
    }
}

void hal_ll_uart_irq_disable( handle_t *handle, hal_ll_uart_irq_t irq ) {
    low_level_handle = hal_ll_uart_get_handle;
    hal_ll_uart_hw_specifics_map_local = hal_ll_get_specifics( hal_ll_uart_get_module_state_address );

    if ( hal_ll_uart_hw_specifics_map_local->is_sci_module ) {
        hal_ll_sci_uart_irq_disable( hal_ll_uart_hw_specifics_map_local, irq );
    } else {
        hal_ll_uart_base_handle_t *hal_ll_hw_reg = ( hal_ll_uart_base_handle_t *)hal_ll_uart_hw_specifics_map_local->base;

        switch ( irq ) {
            case HAL_LL_UART_IRQ_RX:
                clear_reg_bit( &hal_ll_hw_reg->asima0, HAL_LL_UARTA_ASIMA0_RXEA );
                break;
            case HAL_LL_UART_IRQ_TX:
                // Wait for the last transmission to finish.
                while( check_reg_bit(  &hal_ll_hw_reg->asisa, HAL_LL_UARTA_ASISA_TXSFA ));
                clear_reg_bit( &hal_ll_hw_reg->asima0, HAL_LL_UARTA_ASIMA0_TXEA );
                break;

            default:
                break;
        }
    }
}

void hal_ll_uart_write( handle_t *handle, uint8_t wr_data ) {
    hal_ll_uart_hw_specifics_map_local = hal_ll_get_specifics( hal_ll_uart_get_module_state_address );

    if ( hal_ll_uart_hw_specifics_map_local->is_sci_module ) {
        hal_ll_sci_uart_write( hal_ll_uart_hw_specifics_map_local, wr_data );
    } else {
        hal_ll_uart_base_handle_t *hal_ll_hw_reg = ( hal_ll_uart_base_handle_t *)hal_ll_uart_hw_specifics_map_local->base;

        hal_ll_hw_reg->txba = wr_data;

        /* On lower baud rates UARTA module needs more time to process data,
        * so we need to wait for TX buffer to be empty to avoid overrunning data that is being transmitted.
        */
        if ( 19200 >= hal_ll_uart_hw_specifics_map_local->baud_rate.baud ) {
            while( check_reg_bit(  &hal_ll_hw_reg->asisa, HAL_LL_UARTA_ASISA_TXBFA ));
            while( check_reg_bit(  &hal_ll_hw_reg->asisa, HAL_LL_UARTA_ASISA_TXSFA ));
        }
    }
}

void hal_ll_uart_write_polling( handle_t *handle, uint8_t wr_data ) {
    hal_ll_uart_hw_specifics_map_local = hal_ll_get_specifics( hal_ll_uart_get_module_state_address );

    if ( hal_ll_uart_hw_specifics_map_local->is_sci_module ) {
        hal_ll_sci_uart_write_polling( hal_ll_uart_hw_specifics_map_local, wr_data );
    } else {
        hal_ll_uart_base_handle_t *hal_ll_hw_reg = ( hal_ll_uart_base_handle_t * )hal_ll_uart_hw_specifics_map_local->base;
        uint32_t time_counter = hal_ll_uart_hw_specifics_map_local->timeout_polling_write;

        // Wait until transmit data buffer is empty.
        while ( check_reg_bit( &hal_ll_hw_reg->asisa, HAL_LL_UARTA_ASISA_TXBFA )) {
            // Timeout check.
            if( !time_counter-- ) {
                return;
            }
        }

        hal_ll_hw_reg->txba = wr_data;

        // Wait until transmission is over.
        time_counter = hal_ll_uart_hw_specifics_map_local->timeout_polling_write;
        while ( check_reg_bit( &hal_ll_hw_reg->asisa, HAL_LL_UARTA_ASISA_TXSFA )) {
            // Timeout check.
            if( !time_counter-- ) {
                return;
            }
        }
    }
}

uint8_t hal_ll_uart_read( handle_t *handle ) {
    hal_ll_uart_hw_specifics_map_local = hal_ll_get_specifics( hal_ll_uart_get_module_state_address );
    uint8_t rd_data;

    if ( hal_ll_uart_hw_specifics_map_local->is_sci_module ) {
        return hal_ll_sci_uart_read( hal_ll_uart_hw_specifics_map_local );
    } else {
        hal_ll_uart_base_handle_t *hal_ll_hw_reg = ( hal_ll_uart_base_handle_t * )hal_ll_uart_hw_specifics_map_local->base;

        rd_data = hal_ll_hw_reg->rxba;
    }

    return rd_data;
}

uint8_t hal_ll_uart_read_polling( handle_t *handle ) {
    hal_ll_uart_hw_specifics_map_local = hal_ll_get_specifics( hal_ll_uart_get_module_state_address );
    uint8_t read_data = 0xFF;

    if ( hal_ll_uart_hw_specifics_map_local->is_sci_module ) {
        return hal_ll_sci_uart_read_polling( hal_ll_uart_hw_specifics_map_local );
    } else {
        hal_ll_uart_base_handle_t *hal_ll_hw_reg = ( hal_ll_uart_base_handle_t *)hal_ll_uart_hw_specifics_map_local->base;

        /* In polling mode, UARTA has no flag to confirm that the received byte was read.
        * Therefore, wait until the receive data register changes from the buffer reset
        * value before reading the next byte.
        *
        * At higher baud rates, data may be lost because the missing RDRF flag makes it
        * harder to detect new data before an overrun occurs. Once an overrun error
        * happens, subsequent received data may also be lost.
        *
        * For polling mode, the recommended baud rate is 9600.
        */
        while ( 0xFF == read_data )
            read_data = hal_ll_hw_reg->rxba;

        /* In polling mode, UARTA does not refresh the receive buffer automatically.
        * After reading each received byte, reset the buffer by briefly disabling and
        * re-enabling the UARTA module.
        */
        clear_reg_bit( &hal_ll_hw_reg->asima0, HAL_LL_UARTA_ASIMA0_EN );
        set_reg_bit( &hal_ll_hw_reg->asima0, HAL_LL_UARTA_ASIMA0_EN );

        return read_data;
    }
}

// ------------------------------------------------------------- DEFAULT EXCEPTION HANDLERS
#if defined( SCI_MODULE_0 )
void SCI0_TXI_IRQHandler( void ) {
    irq_handler( objects[ hal_ll_uart_module_num( SCI_MODULE_0 ) ], HAL_LL_UART_IRQ_TX );
    clear_reg_bit( &icu_elsr_register->ielsr[ SCI0_TXI_NVIC ], HAL_LL_SCI_ICU_IELSR_IR );
}

void SCI0_RXI_IRQHandler( void ) {
    irq_handler( objects[ hal_ll_uart_module_num( SCI_MODULE_0 ) ], HAL_LL_UART_IRQ_RX );
    clear_reg_bit( &icu_elsr_register->ielsr[ SCI0_RXI_NVIC ], HAL_LL_SCI_ICU_IELSR_IR );
}

void SCI0_ERI_IRQHandler( void ) {
    irq_handler( objects[ hal_ll_uart_module_num( SCI_MODULE_0 ) ], HAL_LL_UART_IRQ_RX );
    clear_reg_bit( &icu_elsr_register->ielsr[ SCI0_ERI_NVIC ], HAL_LL_SCI_ICU_IELSR_IR );
}
#endif

#if defined( SCI_MODULE_1 )
void SCI1_TXI_IRQHandler( void ) {
    irq_handler( objects[ hal_ll_uart_module_num( SCI_MODULE_1 ) ], HAL_LL_UART_IRQ_TX );
    clear_reg_bit( &icu_elsr_register->ielsr[ SCI1_TXI_NVIC ], HAL_LL_SCI_ICU_IELSR_IR );
}

void SCI1_RXI_IRQHandler( void ) {
    irq_handler( objects[ hal_ll_uart_module_num( SCI_MODULE_1 ) ], HAL_LL_UART_IRQ_RX );
    clear_reg_bit( &icu_elsr_register->ielsr[ SCI1_RXI_NVIC ], HAL_LL_SCI_ICU_IELSR_IR );
}

void SCI1_ERI_IRQHandler( void ) {
    irq_handler( objects[ hal_ll_uart_module_num( SCI_MODULE_1 ) ], HAL_LL_UART_IRQ_RX );
    clear_reg_bit( &icu_elsr_register->ielsr[ SCI1_ERI_NVIC ], HAL_LL_SCI_ICU_IELSR_IR );
}
#endif

#if defined( SCI_MODULE_2 )
void SCI2_TXI_IRQHandler( void ) {
    irq_handler( objects[ hal_ll_uart_module_num( SCI_MODULE_2 ) ], HAL_LL_UART_IRQ_TX );
    clear_reg_bit( &icu_elsr_register->ielsr[ SCI2_TXI_NVIC ], HAL_LL_SCI_ICU_IELSR_IR );
}

void SCI2_RXI_IRQHandler( void ) {
    irq_handler( objects[ hal_ll_uart_module_num( SCI_MODULE_2 ) ], HAL_LL_UART_IRQ_RX );
    clear_reg_bit( &icu_elsr_register->ielsr[ SCI2_RXI_NVIC ], HAL_LL_SCI_ICU_IELSR_IR );
}

void SCI2_ERI_IRQHandler( void ) {
    irq_handler( objects[ hal_ll_uart_module_num( SCI_MODULE_2 ) ], HAL_LL_UART_IRQ_RX );
    clear_reg_bit( &icu_elsr_register->ielsr[ SCI2_ERI_NVIC ], HAL_LL_SCI_ICU_IELSR_IR );
}
#endif

#if defined( SCI_MODULE_3 )
void SCI3_TXI_IRQHandler( void ) {
    irq_handler( objects[ hal_ll_uart_module_num( SCI_MODULE_3 ) ], HAL_LL_UART_IRQ_TX );
    clear_reg_bit( &icu_elsr_register->ielsr[ SCI3_TXI_NVIC ], HAL_LL_SCI_ICU_IELSR_IR );
}

void SCI3_RXI_IRQHandler( void ) {
    irq_handler( objects[ hal_ll_uart_module_num( SCI_MODULE_3 ) ], HAL_LL_UART_IRQ_RX );
    clear_reg_bit( &icu_elsr_register->ielsr[ SCI3_RXI_NVIC ], HAL_LL_SCI_ICU_IELSR_IR );
}

void SCI3_ERI_IRQHandler( void ) {
    irq_handler( objects[ hal_ll_uart_module_num( SCI_MODULE_3 ) ], HAL_LL_UART_IRQ_RX );
    clear_reg_bit( &icu_elsr_register->ielsr[ SCI3_ERI_NVIC ], HAL_LL_SCI_ICU_IELSR_IR );
}
#endif

#if defined( SCI_MODULE_4 )
void SCI4_TXI_IRQHandler( void ) {
    irq_handler( objects[ hal_ll_uart_module_num( SCI_MODULE_4 ) ], HAL_LL_UART_IRQ_TX );
    clear_reg_bit( &icu_elsr_register->ielsr[ SCI4_TXI_NVIC ], HAL_LL_SCI_ICU_IELSR_IR );
}

void SCI4_RXI_IRQHandler( void ) {
    irq_handler( objects[ hal_ll_uart_module_num( SCI_MODULE_4 ) ], HAL_LL_UART_IRQ_RX );
    clear_reg_bit( &icu_elsr_register->ielsr[ SCI4_RXI_NVIC ], HAL_LL_SCI_ICU_IELSR_IR );
}

void SCI4_ERI_IRQHandler( void ) {
    irq_handler( objects[ hal_ll_uart_module_num( SCI_MODULE_4 ) ], HAL_LL_UART_IRQ_RX );
    clear_reg_bit( &icu_elsr_register->ielsr[ SCI4_ERI_NVIC ], HAL_LL_SCI_ICU_IELSR_IR );
}
#endif

#if defined( SCI_MODULE_5 )
void SCI5_TXI_IRQHandler( void ) {
    irq_handler( objects[ hal_ll_uart_module_num( SCI_MODULE_5 ) ], HAL_LL_UART_IRQ_TX );
    clear_reg_bit( &icu_elsr_register->ielsr[ SCI5_TXI_NVIC ], HAL_LL_SCI_ICU_IELSR_IR );
}

void SCI5_RXI_IRQHandler( void ) {
    irq_handler( objects[ hal_ll_uart_module_num( SCI_MODULE_5 ) ], HAL_LL_UART_IRQ_RX );
    clear_reg_bit( &icu_elsr_register->ielsr[ SCI5_RXI_NVIC ], HAL_LL_SCI_ICU_IELSR_IR );
}

void SCI5_ERI_IRQHandler( void ) {
    irq_handler( objects[ hal_ll_uart_module_num( SCI_MODULE_5 ) ], HAL_LL_UART_IRQ_RX );
    clear_reg_bit( &icu_elsr_register->ielsr[ SCI5_ERI_NVIC ], HAL_LL_SCI_ICU_IELSR_IR );
}
#endif

#if defined( SCI_MODULE_6 )
void SCI6_TXI_IRQHandler( void ) {
    irq_handler( objects[ hal_ll_uart_module_num( SCI_MODULE_6 ) ], HAL_LL_UART_IRQ_TX );
    clear_reg_bit( &icu_elsr_register->ielsr[ SCI6_TXI_NVIC ], HAL_LL_SCI_ICU_IELSR_IR );
}

void SCI6_RXI_IRQHandler( void ) {
    irq_handler( objects[ hal_ll_uart_module_num( SCI_MODULE_6 ) ], HAL_LL_UART_IRQ_RX );
    clear_reg_bit( &icu_elsr_register->ielsr[ SCI6_RXI_NVIC ], HAL_LL_SCI_ICU_IELSR_IR );
}

void SCI6_ERI_IRQHandler( void ) {
    irq_handler( objects[ hal_ll_uart_module_num( SCI_MODULE_6 ) ], HAL_LL_UART_IRQ_RX );
    clear_reg_bit( &icu_elsr_register->ielsr[ SCI6_ERI_NVIC ], HAL_LL_SCI_ICU_IELSR_IR );
}
#endif

#if defined( SCI_MODULE_7 )
void SCI7_TXI_IRQHandler( void ) {
    irq_handler( objects[ hal_ll_uart_module_num( SCI_MODULE_7 ) ], HAL_LL_UART_IRQ_TX );
    clear_reg_bit( &icu_elsr_register->ielsr[ SCI7_TXI_NVIC ], HAL_LL_SCI_ICU_IELSR_IR );
}

void SCI7_RXI_IRQHandler( void ) {
    irq_handler( objects[ hal_ll_uart_module_num( SCI_MODULE_7 ) ], HAL_LL_UART_IRQ_RX );
    clear_reg_bit( &icu_elsr_register->ielsr[ SCI7_RXI_NVIC ], HAL_LL_SCI_ICU_IELSR_IR );
}

void SCI7_ERI_IRQHandler( void ) {
    irq_handler( objects[ hal_ll_uart_module_num( SCI_MODULE_7 ) ], HAL_LL_UART_IRQ_RX );
    clear_reg_bit( &icu_elsr_register->ielsr[ SCI7_ERI_NVIC ], HAL_LL_SCI_ICU_IELSR_IR );
}
#endif

#if defined( SCI_MODULE_8 )
void SCI8_TXI_IRQHandler( void ) {
    irq_handler( objects[ hal_ll_uart_module_num( SCI_MODULE_8 ) ], HAL_LL_UART_IRQ_TX );
    clear_reg_bit( &icu_elsr_register->ielsr[ SCI8_TXI_NVIC ], HAL_LL_SCI_ICU_IELSR_IR );
}

void SCI8_RXI_IRQHandler( void ) {
    irq_handler( objects[ hal_ll_uart_module_num( SCI_MODULE_8 ) ], HAL_LL_UART_IRQ_RX );
    clear_reg_bit( &icu_elsr_register->ielsr[ SCI8_RXI_NVIC ], HAL_LL_SCI_ICU_IELSR_IR );
}

void SCI8_ERI_IRQHandler( void ) {
    irq_handler( objects[ hal_ll_uart_module_num( SCI_MODULE_8 ) ], HAL_LL_UART_IRQ_RX );
    clear_reg_bit( &icu_elsr_register->ielsr[ SCI8_ERI_NVIC ], HAL_LL_SCI_ICU_IELSR_IR );
}
#endif

#if defined( SCI_MODULE_9 )
void SCI9_TXI_IRQHandler( void ) {
    irq_handler( objects[ hal_ll_uart_module_num( SCI_MODULE_9 ) ], HAL_LL_UART_IRQ_TX );
    clear_reg_bit( &icu_elsr_register->ielsr[ SCI9_TXI_NVIC ], HAL_LL_SCI_ICU_IELSR_IR );
}

void SCI9_RXI_IRQHandler( void ) {
    irq_handler( objects[ hal_ll_uart_module_num( SCI_MODULE_9 ) ], HAL_LL_UART_IRQ_RX );
    clear_reg_bit( &icu_elsr_register->ielsr[ SCI9_RXI_NVIC ], HAL_LL_SCI_ICU_IELSR_IR );
}

void SCI9_ERI_IRQHandler( void ) {
    irq_handler( objects[ hal_ll_uart_module_num( SCI_MODULE_9 ) ], HAL_LL_UART_IRQ_RX );
    clear_reg_bit( &icu_elsr_register->ielsr[ SCI9_ERI_NVIC ], HAL_LL_SCI_ICU_IELSR_IR );
}
#endif

#if defined( UART_MODULE_0 )
void UARTA0_TXI_IRQHandler( void ) {
    irq_handler( objects[ hal_ll_uart_module_num( UART_MODULE_0 ) ], HAL_LL_UART_IRQ_TX );
}

void UARTA0_RXI_IRQHandler( void ) {
    irq_handler( objects[ hal_ll_uart_module_num( UART_MODULE_0 ) ], HAL_LL_UART_IRQ_RX );
}

void UARTA0_ERI_IRQHandler( void ) {
    hal_ll_uart_base_handle_t *hal_ll_hw_reg = ( hal_ll_uart_base_handle_t *)HAL_LL_UARTA0_BASE_ADDR;

    /*
     * If irq_handler is called by ERI (Error Receive Interrupt)
     * we need to handle overrun error as reception stops when overrun error
     * is detected.
     */
    if ( check_reg_bit( &hal_ll_hw_reg->asisa, HAL_LL_UARTA_ASISA_OVEA ))
        set_reg_bit( &hal_ll_hw_reg->ascta, HAL_LL_UARTA_ASCTA_OVECTA );
    /*
     * If irq_handler is called by the framing error we need
     * to clear the error flag to disable the ERI interrupt.
     */
    if ( check_reg_bit( &hal_ll_hw_reg->asisa, HAL_LL_UARTA_ASISA_FEA ))
        set_reg_bit( &hal_ll_hw_reg->ascta, HAL_LL_UARTA_ASCTA_FECTA );

    /*
     * If irq_handler is called by the parity error we need
     * to clear the error flag to disable the ERI interrupt.
     */
    if ( check_reg_bit( &hal_ll_hw_reg->asisa, HAL_LL_UARTA_ASISA_PEA ))
        set_reg_bit( &hal_ll_hw_reg->ascta, HAL_LL_UARTA_ASCTA_PECTA );
}
#endif

#if defined( UART_MODULE_1 )
void UARTA1_TXI_IRQHandler( void ) {
    irq_handler( objects[ hal_ll_uart_module_num( UART_MODULE_1 ) ], HAL_LL_UART_IRQ_TX );
}

void UARTA1_RXI_IRQHandler( void ) {
    irq_handler( objects[ hal_ll_uart_module_num( UART_MODULE_1 ) ], HAL_LL_UART_IRQ_RX );
}

void UARTA1_ERI_IRQHandler( void ) {
    hal_ll_uart_base_handle_t *hal_ll_hw_reg = ( hal_ll_uart_base_handle_t *)HAL_LL_UARTA1_BASE_ADDR;

    /*
     * If irq_handler is called by ERI (Error Receive Interrupt)
     * we need to handle overrun error as reception stops when overrun error
     * is detected.
     */
    if ( check_reg_bit( &hal_ll_hw_reg->asisa, HAL_LL_UARTA_ASISA_OVEA ))
        set_reg_bit( &hal_ll_hw_reg->ascta, HAL_LL_UARTA_ASCTA_OVECTA );
    /*
     * If irq_handler is called by the framing error we need
     * to clear the error flag to disable the ERI interrupt.
     */
    if ( check_reg_bit( &hal_ll_hw_reg->asisa, HAL_LL_UARTA_ASISA_FEA ))
        set_reg_bit( &hal_ll_hw_reg->ascta, HAL_LL_UARTA_ASCTA_FECTA );

    /*
     * If irq_handler is called by the parity error we need
     * to clear the error flag to disable the ERI interrupt.
     */
    if ( check_reg_bit( &hal_ll_hw_reg->asisa, HAL_LL_UARTA_ASISA_PEA ))
        set_reg_bit( &hal_ll_hw_reg->ascta, HAL_LL_UARTA_ASCTA_PECTA );
}
#endif

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
                    if ( hal_ll_uart_tx_map[ tx_index ].base == hal_ll_uart_rx_map[ rx_index ].base ) {
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
    if ( map->is_sci_module )
        hal_ll_sci_module_enable( map->module_index, hal_ll_state );
    else
        ( hal_ll_state == false ) ? ( set_reg_bit( _MSTPCRB, MSTPCRB_MSTPB15_POS )) : ( clear_reg_bit( _MSTPCRB, MSTPCRB_MSTPB15_POS ));
}

static void hal_ll_uart_map_pins( uint8_t module_index, hal_ll_uart_pin_id *index_list ) {
    // Map new pins.
    hal_ll_uart_hw_specifics_map[module_index].pins.tx_pin.pin_name = hal_ll_uart_tx_map[index_list[module_index].pin_tx].pin;
    hal_ll_uart_hw_specifics_map[module_index].pins.rx_pin.pin_name = hal_ll_uart_rx_map[index_list[module_index].pin_rx].pin;
    // TX and RX could have different alternate function settings, hence save both AF values.
    hal_ll_uart_hw_specifics_map[module_index].pins.tx_pin.pin_af = hal_ll_uart_tx_map[index_list[module_index].pin_tx].af;
    hal_ll_uart_hw_specifics_map[module_index].pins.rx_pin.pin_af = hal_ll_uart_rx_map[index_list[module_index].pin_rx].af;
}

static void hal_ll_uart_alternate_functions_set_state( hal_ll_uart_hw_specifics_map_t *map, bool hal_ll_state ) {
    module_struct module;
    uint32_t uart_config = 0;

    if (( map->pins.rx_pin.pin_name != HAL_LL_PIN_NC ) &&
        ( map->pins.tx_pin.pin_name != HAL_LL_PIN_NC ))
    {
        module.pins[0] = VALUE( map->pins.tx_pin.pin_name, map->pins.tx_pin.pin_af );
        module.pins[1] = VALUE( map->pins.rx_pin.pin_name, map->pins.rx_pin.pin_af );
        module.pins[2] = GPIO_MODULE_STRUCT_END;

        module.configs[ 0 ] = uart_config;
        module.configs[ 1 ] = uart_config;
        module.configs[ 2 ] = GPIO_MODULE_STRUCT_END;

        hal_ll_gpio_module_struct_init( &module, hal_ll_state );
    }
}

static void hal_ll_uart_set_baud_bare_metal( hal_ll_uart_hw_specifics_map_t *map ) {
    hal_ll_uart_base_handle_t *hal_ll_hw_reg = hal_ll_uart_get_base_struct( map->base );
    system_clocks_t system_clocks;
    uint32_t source_clock;
    uint8_t brgca_value;

    SYSTEM_GetClocksFrequency( &system_clocks );

    switch ( map->module_index ) {
        #ifdef UART_MODULE_0
        case ( hal_ll_uart_module_num( UART_MODULE_0 )):
            source_clock = system_clocks.uarta0;
            break;
        #endif
        #ifdef UART_MODULE_1
        case ( hal_ll_uart_module_num( UART_MODULE_1 )):
            source_clock = system_clocks.uarta1;
            break;
        #endif

        default:
            break;
    }

    /* Find the best BRGCA value.
     *  BRGCA = (Futa / (2 * baud)) and [ 2 <= BRGCA <= 255 ]
     */
    brgca_value = source_clock / ( 2 * map->baud_rate.baud );
    map->baud_rate.real_baud = hal_ll_uart_get_baud_rate( source_clock, brgca_value );
    write_reg(  &hal_ll_hw_reg->brgca, brgca_value );
}

static void hal_ll_uart_set_stop_bits_bare_metal( hal_ll_uart_hw_specifics_map_t *map ) {
    hal_ll_uart_base_handle_t *hal_ll_hw_reg = hal_ll_uart_get_base_struct( map->base );

    switch ( map->stop_bit ) {
        case HAL_LL_UART_STOP_BITS_ONE:
            clear_reg_bit( &hal_ll_hw_reg->asima1, HAL_LL_UARTA_ASIMA1_SL );
            break;
        case HAL_LL_UART_STOP_BITS_TWO:
            set_reg_bit( &hal_ll_hw_reg->asima1, HAL_LL_UARTA_ASIMA1_SL );
            break;

        default:
            break;
    }
}

static void hal_ll_uart_set_data_bits_bare_metal( hal_ll_uart_hw_specifics_map_t *map ) {
    hal_ll_uart_base_handle_t *hal_ll_hw_reg = hal_ll_uart_get_base_struct( map->base );

    switch ( map->data_bit )
    {
        case HAL_LL_UART_DATA_BITS_5:
            clear_reg_bits( &hal_ll_hw_reg->asima1, HAL_LL_UARTA_ASIMA1_CL_MASK );
            break;
        case HAL_LL_UART_DATA_BITS_7:
            set_reg_bits( &hal_ll_hw_reg->asima1, HAL_LL_UARTA_ASIMA1_CL_MASK_7BITS );
            break;
        case HAL_LL_UART_DATA_BITS_8:
            set_reg_bits( &hal_ll_hw_reg->asima1, HAL_LL_UARTA_ASIMA1_CL_MASK_8BITS );
            break;

        default:
            break;
    }
}

static void hal_ll_uart_set_parity_bare_metal( hal_ll_uart_hw_specifics_map_t *map ) {
    hal_ll_uart_base_handle_t *hal_ll_hw_reg = hal_ll_uart_get_base_struct( map->base );

    switch ( map->parity )
    {
        case HAL_LL_UART_PARITY_NONE:
            clear_reg_bits( &hal_ll_hw_reg->asima1, HAL_LL_UARTA_ASIMA1_PS_MASK );
            break;
        case HAL_LL_UART_PARITY_EVEN:
            set_reg_bits( &hal_ll_hw_reg->asima1, HAL_LL_UARTA_ASIMA1_PS_MASK_EVEN );
            break;
        case HAL_LL_UART_PARITY_ODD:
            set_reg_bits( &hal_ll_hw_reg->asima1, HAL_LL_UARTA_ASIMA1_PS_MASK_ODD );
            break;

        default:
            break;
    }
}

static void hal_ll_uart_set_module( hal_ll_uart_base_handle_t *hal_ll_hw_reg, hal_ll_uart_state_t pin_state ) {
    switch ( pin_state )
    {
        case HAL_LL_UART_DISABLE:
            clear_reg_bit( &hal_ll_hw_reg->asima0, HAL_LL_UARTA_ASIMA0_EN );
            break;

        case HAL_LL_UART_ENABLE:
            set_reg_bit( &hal_ll_hw_reg->asima0, HAL_LL_UARTA_ASIMA0_EN );
            break;

        default:
            break;
    }
}

static void hal_ll_uart_set_transmitter( hal_ll_uart_base_handle_t *hal_ll_hw_reg, hal_ll_uart_state_t pin_state ) {
    switch ( pin_state )
    {
        case HAL_LL_UART_DISABLE:
            clear_reg_bit( &hal_ll_hw_reg->asima0, HAL_LL_UARTA_ASIMA0_TXEA );
            break;

        case HAL_LL_UART_ENABLE:
            set_reg_bit( &hal_ll_hw_reg->asima0, HAL_LL_UARTA_ASIMA0_TXEA );
            break;

        default:
            break;
    }
}

static void hal_ll_uart_set_receiver( hal_ll_uart_base_handle_t *hal_ll_hw_reg, hal_ll_uart_state_t pin_state ) {
    switch ( pin_state )
    {
        case HAL_LL_UART_DISABLE:
            clear_reg_bit( &hal_ll_hw_reg->asima0, HAL_LL_UARTA_ASIMA0_RXEA );
            break;

        case HAL_LL_UART_ENABLE:
            set_reg_bit( &hal_ll_hw_reg->asima0, HAL_LL_UARTA_ASIMA0_RXEA );
            break;

        default:
            break;
    }
}

static void hal_ll_uart_clear_regs( hal_ll_uart_base_handle_t *hal_ll_hw_reg ) {
    clear_reg( &hal_ll_hw_reg->asima0 );
    clear_reg( &hal_ll_hw_reg->asima1 );
    clear_reg( &hal_ll_hw_reg->asisa );
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
    hal_ll_uart_set_clock( map, true );

    hal_ll_uart_alternate_functions_set_state( map, true );

    if ( map->is_sci_module )
        hal_ll_sci_uart_hw_init( map );
    else
        hal_ll_uart_hw_init( map );
}

// ------------------------------------------------------------------------- END
