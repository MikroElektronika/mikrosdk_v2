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

#include "hal_ll_rcc.h"
#include "hal_ll_uart.h"
#include "hal_ll_gpio.h"
#include "hal_ll_core.h"
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

/*!< @brief Helper macro for UART module sync time */
#define hal_ll_uart_wait_for_sync(_hal_sync_val) while( _hal_sync_val-- ) assembly(nop)

/*!< @brief Macros used for calculating actual baud rate value and error value. */
#define HAL_LL_UART_ACCEPTABLE_ERROR (float)1.0
#define hal_ll_uart_get_baud(_clock,_baud,_div) (((_clock/(float)_baud)/_div))
#define hal_ll_uart_get_real_baud(_clock,_baud,_div) (_clock/(_div*(_baud)))
#define hal_ll_uart_get_baud_error(_baud_real,_baud) (((float)(abs(_baud_real-_baud))/_baud)*100)

/*!< @brief Macros defining bit location. */
#define HAL_LL_UART0EN                                  (0)
#define HAL_LL_UART1EN                                  (1)
#define HAL_LL_UART2EN                                  (2)
#define HAL_LL_UART3EN                                  (3)
#define HAL_LL_UART4EN                                  (4)
#define HAL_LL_UART5EN                                  (5)
#define HAL_LL_UART6EN                                  (6)
#define HAL_LL_UART7EN                                  (7)

#define HAL_LL_UART_CTL_UARTEN                          (0)
#define HAL_LL_UART_CTL_FEN                             (4)
#define HAL_LL_UART_CTL_TXE                             (8)
#define HAL_LL_UART_CTL_RXE                             (9)

#define HAL_LL_UART_IT_RXIM_BIT                         (4)
#define HAL_LL_UART_IT_TXIM_BIT                         (5)
#define HAL_LL_UART_IT_OER_BIT                          (10)

/*!< @brief Macros defining register bit values. */
#define HAL_LL_UART_LCRH_MASK                           (0xFFUL)
#define HAL_LL_UART_CTL_MASK                            (0xCFBFUL)

#define HAL_LL_UART_IT_FR_RXFE                          (0x10UL)
#define HAL_LL_UART_IT_FR_TXFF                          (0x20UL)

#define STOP_BITS_MASK                                  (0x8UL)
#define STOP_BITS_ONE                                   (0x0UL)
#define STOP_BITS_TWO                                   (STOP_BITS_MASK)

#define DATA_BITS_MASK                                  (0x60UL)
#define DATA_BIT_5                                      (0x0UL)
#define DATA_BIT_6                                      (0x20UL)
#define DATA_BIT_7                                      (0x40UL)
#define DATA_BIT_8                                      (DATA_BITS_MASK)

#define PARITY_STICK                                    (0x80UL)
#define PARITY_MASK                                     (0x6UL)
#define PARITY_NO                                       (0x0UL)
#define PARITY_EVEN                                     (PARITY_MASK)
#define PARITY_ODD                                      (0x2UL)

#define HAL_LL_UART_CTL_HSE_BIT                         (0x20UL)

#define HAL_LL_UART_ERRORS                              (0xF00U)
#define HAL_LL_UART_DATA                                (0xFFU)

/*!< @brief Macros used for interrupts. */
#define HAL_LL_UART_IT_CLEAR_MASK                       (0x360U)
#define HAL_LL_UART_IT_CR1_MASK                         (0x1F0UL)
#define HAL_LL_UART_IT_CR2_MASK                         (0x40UL)
#define HAL_LL_UART_IT_CR3_MASK                         (0x401UL)

#define HAL_LL_UART_CR1_REG_INDEX                       (1)
#define HAL_LL_UART_CR2_REG_INDEX                       (2)
#define HAL_LL_UART_CR3_REG_INDEX                       (3)

#define HAL_LL_UART_IT_PE                               (0x10000100UL)
#define HAL_LL_UART_IT_TXIM                             (1UL << HAL_LL_UART_IT_TXIM_BIT)
#define HAL_LL_UART_IT_TC                               (0x10000040UL)
#define HAL_LL_UART_IT_RXIM                             (1UL << HAL_LL_UART_IT_RXIM_BIT)
#define HAL_LL_UART_IT_IDLE                             (0x10000010UL)

#define HAL_LL_UART_IT_LBD                              (0x20000040UL)

#define HAL_LL_UART_IT_CTS                              (0x30000400UL)
#define HAL_LL_UART_IT_ERR                              (0x30000001UL)

#define HAL_LL_UART_STATUS_RXMIS_FLAG                   (HAL_LL_UART_IT_RXIM)
#define HAL_LL_UART_STATUS_TXMIS_FLAG                   (HAL_LL_UART_IT_TXIM)

/*!< @brief Macro used for status registed flag check.
 * Used in interrupt handlers.
 */
#define hal_ll_uart_get_status_flags(_handle,_flag) (((hal_ll_uart_base_handle_t *)_handle)->mis & _flag)

/*!< @brief Macro used for status registed flag clearing.
 * Used in interrupt handlers.
 */
#define hal_ll_uart_clear_status_flag(_handle,_flag) (set_reg_bit(&(((hal_ll_uart_base_handle_t *)_handle)->icr), _flag))

/*!< @brief UART HW register structure. */
typedef struct {
    uint32_t dr;                        // Data register.
    uint32_t rsr_ecr;                   // Receive status/error clear register.
    uint32_t __unused1[4];
    uint32_t fr;                        // Flag register.
    uint32_t __unused2;
    uint32_t ilpr;                      // IrDA low power register.
    uint32_t ibrd;                      // Integer baud-rate register.
    uint32_t fbrd;                      // Fractional baud rate register.
    uint32_t lcrh;                      // Line control register.
    uint32_t ctl;                       // Control register.
    uint32_t ifls;                      // Interrupt FIFO level select register.
    uint32_t im;                        // Interrupt mask register.
    uint32_t ris;                       // Raw interrupt status register.
    uint32_t mis;                       // Masked interrupt status register.
    uint32_t icr;                       // Interrupt clear register.
    /* Register aren't used in this source.
     * Uncomment if needed. */
    /*
    uint32_t dmactl;                    // DMA control register.
    uint32_t __unused3[22];
    uint32_t nine_bitaddr;              // Nine bit self addres register.
    uint32_t nine_bitmask;              // Nine bit self adress mask register.
    */
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
    {HAL_LL_UART0_BASE_ADDRESS, hal_ll_uart_module_num( UART_MODULE_0 ), {HAL_LL_PIN_NC, 0, HAL_LL_PIN_NC, 0}, {115200, 0}, HAL_LL_UART_PARITY_DEFAULT, HAL_LL_UART_STOP_BITS_DEFAULT, HAL_LL_UART_DATA_BITS_DEFAULT},
    #endif
    #ifdef UART_MODULE_1
    {HAL_LL_UART1_BASE_ADDRESS, hal_ll_uart_module_num( UART_MODULE_1 ), {HAL_LL_PIN_NC, 0, HAL_LL_PIN_NC, 0}, {115200, 0}, HAL_LL_UART_PARITY_DEFAULT, HAL_LL_UART_STOP_BITS_DEFAULT, HAL_LL_UART_DATA_BITS_DEFAULT},
    #endif
    #ifdef UART_MODULE_2
    {HAL_LL_UART2_BASE_ADDRESS, hal_ll_uart_module_num( UART_MODULE_2 ), {HAL_LL_PIN_NC, 0, HAL_LL_PIN_NC, 0}, {115200, 0}, HAL_LL_UART_PARITY_DEFAULT, HAL_LL_UART_STOP_BITS_DEFAULT, HAL_LL_UART_DATA_BITS_DEFAULT},
    #endif
    #ifdef UART_MODULE_3
    {HAL_LL_UART3_BASE_ADDRESS, hal_ll_uart_module_num( UART_MODULE_3 ), {HAL_LL_PIN_NC, 0, HAL_LL_PIN_NC, 0}, {115200, 0}, HAL_LL_UART_PARITY_DEFAULT, HAL_LL_UART_STOP_BITS_DEFAULT, HAL_LL_UART_DATA_BITS_DEFAULT},
    #endif
    #ifdef UART_MODULE_4
    {HAL_LL_UART4_BASE_ADDRESS, hal_ll_uart_module_num( UART_MODULE_4 ), {HAL_LL_PIN_NC, 0, HAL_LL_PIN_NC, 0}, {115200, 0}, HAL_LL_UART_PARITY_DEFAULT, HAL_LL_UART_STOP_BITS_DEFAULT, HAL_LL_UART_DATA_BITS_DEFAULT},
    #endif
    #ifdef UART_MODULE_5
    {HAL_LL_UART5_BASE_ADDRESS, hal_ll_uart_module_num( UART_MODULE_5 ), {HAL_LL_PIN_NC, 0, HAL_LL_PIN_NC, 0}, {115200, 0}, HAL_LL_UART_PARITY_DEFAULT, HAL_LL_UART_STOP_BITS_DEFAULT, HAL_LL_UART_DATA_BITS_DEFAULT},
    #endif
    #ifdef UART_MODULE_6
    {HAL_LL_UART6_BASE_ADDRESS, hal_ll_uart_module_num( UART_MODULE_6 ), {HAL_LL_PIN_NC, 0, HAL_LL_PIN_NC, 0}, {115200, 0}, HAL_LL_UART_PARITY_DEFAULT, HAL_LL_UART_STOP_BITS_DEFAULT, HAL_LL_UART_DATA_BITS_DEFAULT},
    #endif
    #ifdef UART_MODULE_7
    {HAL_LL_UART7_BASE_ADDRESS, hal_ll_uart_module_num( UART_MODULE_7 ), {HAL_LL_PIN_NC, 0, HAL_LL_PIN_NC, 0}, {115200, 0}, HAL_LL_UART_PARITY_DEFAULT, HAL_LL_UART_STOP_BITS_DEFAULT, HAL_LL_UART_DATA_BITS_DEFAULT},
    #endif

    {HAL_LL_MODULE_ERROR, HAL_LL_MODULE_ERROR, {HAL_LL_PIN_NC, 0, HAL_LL_PIN_NC, 0}, {0, 0}, HAL_LL_MODULE_ERROR, HAL_LL_MODULE_ERROR, HAL_LL_MODULE_ERROR}
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
  * @brief  Get UART module clock speed.
  *
  * Returns adequate clock speed based on
  * UART module base address.
  *
  * @param[in]  module_index - UART module index number.
  *
  * @return uint8_t Module number.
  * Returns clock value.
  */
static uint32_t hal_ll_uart_get_clock_speed( hal_ll_pin_name_t module_index );

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
    hal_ll_uart_hw_specifics_map_local = hal_ll_get_specifics(hal_ll_uart_get_module_state_address);
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
    hal_ll_uart_hw_specifics_map_local = hal_ll_get_specifics(hal_ll_uart_get_module_state_address);

    low_level_handle->init_ll_state = false;

    hal_ll_uart_hw_specifics_map_local->baud_rate.baud = baud;

    hal_ll_uart_init(hal_ll_uart_hw_specifics_map_local);

    low_level_handle->init_ll_state = true;

    return hal_ll_uart_hw_specifics_map_local->baud_rate.real_baud;
}

hal_ll_err_t hal_ll_uart_set_parity( handle_t *handle, hal_ll_uart_parity_t parity ) {
    low_level_handle = hal_ll_uart_get_handle;
    hal_ll_uart_hw_specifics_map_local = hal_ll_get_specifics(hal_ll_uart_get_module_state_address);

    low_level_handle->init_ll_state = false;

    hal_ll_uart_hw_specifics_map_local->parity = parity;

    hal_ll_uart_init(hal_ll_uart_hw_specifics_map_local);

    low_level_handle->init_ll_state = true;

    return HAL_LL_UART_SUCCESS;
}

hal_ll_err_t hal_ll_uart_set_stop_bits( handle_t *handle, hal_ll_uart_stop_bits_t stop_bit ) {
    low_level_handle = hal_ll_uart_get_handle;
    hal_ll_uart_hw_specifics_map_local = hal_ll_get_specifics(hal_ll_uart_get_module_state_address);

    low_level_handle->init_ll_state = false;

    hal_ll_uart_hw_specifics_map_local->stop_bit = stop_bit;

    hal_ll_uart_init(hal_ll_uart_hw_specifics_map_local);

    low_level_handle->init_ll_state = true;

    return HAL_LL_UART_SUCCESS;
}

hal_ll_err_t hal_ll_uart_set_data_bits( handle_t *handle, hal_ll_uart_data_bits_t data_bit ) {
    low_level_handle = hal_ll_uart_get_handle;
    hal_ll_uart_hw_specifics_map_local = hal_ll_get_specifics(hal_ll_uart_get_module_state_address);

    // Chips using this implementation do not support 7 bit data.
    if ( ( data_bit < HAL_LL_UART_DATA_BITS_5 ) || ( data_bit > HAL_LL_UART_DATA_BITS_8 ) ) {
        return HAL_LL_UART_MODULE_ERROR;
    }

    low_level_handle->init_ll_state = false;

    hal_ll_uart_hw_specifics_map_local->data_bit = data_bit;

    hal_ll_uart_init(hal_ll_uart_hw_specifics_map_local);

    low_level_handle->init_ll_state = true;

    return HAL_LL_UART_SUCCESS;
}

void hal_ll_uart_close( handle_t *handle ) {
    low_level_handle = hal_ll_uart_get_handle;
    hal_ll_uart_hw_specifics_map_local = hal_ll_get_specifics(hal_ll_uart_get_module_state_address);

    if( low_level_handle->hal_ll_uart_handle != NULL ) {
        hal_ll_uart_set_clock(hal_ll_uart_hw_specifics_map_local, true);
        hal_ll_uart_alternate_functions_set_state( hal_ll_uart_hw_specifics_map_local, false );

        hal_ll_uart_irq_disable(handle, HAL_LL_UART_IRQ_RX);
        hal_ll_uart_irq_disable(handle, HAL_LL_UART_IRQ_TX);

        hal_ll_uart_clear_regs(hal_ll_uart_hw_specifics_map_local->base);
        hal_ll_uart_set_clock(hal_ll_uart_hw_specifics_map_local, false);

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
    objects[ hal_ll_uart_find_index( handle ) ] = obj;
}

void hal_ll_uart_irq_enable( handle_t *handle, hal_ll_uart_irq_t irq ) {
    low_level_handle = hal_ll_uart_get_handle;
    hal_ll_uart_hw_specifics_map_local = hal_ll_get_specifics(hal_ll_uart_get_module_state_address);

    hal_ll_uart_base_handle_t *hal_ll_hw_reg = ( hal_ll_uart_base_handle_t *)hal_ll_uart_hw_specifics_map_local->base;

    switch ( irq ) {
        case HAL_LL_UART_IRQ_RX:
            set_reg_bit( &hal_ll_hw_reg->im, HAL_LL_UART_IT_RXIM_BIT );
            break;
        case HAL_LL_UART_IRQ_TX:
            set_reg_bit( &hal_ll_hw_reg->im, HAL_LL_UART_IT_TXIM_BIT );
            break;

        default:
            break;
    }

    switch ( hal_ll_uart_hw_specifics_map_local->module_index ) {
        #if defined(UART_MODULE_0) && defined(UART0_NVIC)
        case hal_ll_uart_module_num( UART_MODULE_0 ):
            hal_ll_core_enable_irq( UART0_NVIC );
            break;
        #endif
        #if defined(UART_MODULE_1) && defined(UART1_NVIC)
        case hal_ll_uart_module_num( UART_MODULE_1 ):
            hal_ll_core_enable_irq( UART1_NVIC );
            break;
        #endif
        #if defined(UART_MODULE_2) && defined(UART2_NVIC)
        case hal_ll_uart_module_num( UART_MODULE_2 ):
            hal_ll_core_enable_irq( UART2_NVIC );
            break;
        #endif
        #if defined(UART_MODULE_3) && defined(UART3_NVIC)
        case hal_ll_uart_module_num( UART_MODULE_3 ):
            hal_ll_core_enable_irq( UART3_NVIC );
            break;
        #endif
        #if defined(UART_MODULE_4) && defined(UART4_NVIC)
        case hal_ll_uart_module_num( UART_MODULE_4 ):
            hal_ll_core_enable_irq( UART4_NVIC );
            break;
        #endif
        #if defined(UART_MODULE_5) && defined(UART5_NVIC)
        case hal_ll_uart_module_num( UART_MODULE_5 ):
            hal_ll_core_enable_irq( UART5_NVIC );
            break;
        #endif
        #if defined(UART_MODULE_6) && defined(UART6_NVIC)
        case hal_ll_uart_module_num( UART_MODULE_6 ):
            hal_ll_core_enable_irq( UART6_NVIC );
            break;
        #endif
        #if defined(UART_MODULE_7) && defined(UART7_NVIC)
        case hal_ll_uart_module_num( UART_MODULE_7 ):
            hal_ll_core_enable_irq( UART7_NVIC );
            break;
        #endif

        default:
            break;
    }
}

void hal_ll_uart_irq_disable( handle_t *handle, hal_ll_uart_irq_t irq ) {
    low_level_handle = hal_ll_uart_get_handle;
    hal_ll_uart_hw_specifics_map_local = hal_ll_get_specifics(hal_ll_uart_get_module_state_address);

    hal_ll_uart_base_handle_t *hal_ll_hw_reg = ( hal_ll_uart_base_handle_t *)hal_ll_uart_hw_specifics_map_local->base;

    switch ( irq ) {
        case HAL_LL_UART_IRQ_RX:
            clear_reg_bit( &hal_ll_hw_reg->im, HAL_LL_UART_IT_RXIM_BIT );
            break;
        case HAL_LL_UART_IRQ_TX:
            clear_reg_bit( &hal_ll_hw_reg->im, HAL_LL_UART_IT_TXIM_BIT );
            break;

        default:
            break;
    }

    /* Check if module interrupt flags are set or not.
     * ATTENTION This is a very important part in the code.
     * Interrupts should be disabled ONLY in case we have
     * both TX and RX interrupts disabled.
     */
    if ( ( !check_reg_bit( &hal_ll_hw_reg->im, HAL_LL_UART_IT_RXIM_BIT ) ) &&
         ( !check_reg_bit( &hal_ll_hw_reg->im, HAL_LL_UART_IT_TXIM_BIT ) ) )
    {
        switch ( hal_ll_uart_hw_specifics_map_local->module_index ) {
            #if defined(UART_MODULE_0) && defined(UART0_NVIC)
            case hal_ll_uart_module_num( UART_MODULE_0 ):
                hal_ll_core_disable_irq( UART0_NVIC );
                break;
            #endif
            #if defined(UART_MODULE_1) && defined(UART1_NVIC)
            case hal_ll_uart_module_num( UART_MODULE_1 ):
                hal_ll_core_disable_irq( UART1_NVIC );
                break;
            #endif
            #if defined(UART_MODULE_2) && defined(UART2_NVIC)
            case hal_ll_uart_module_num( UART_MODULE_2 ):
                hal_ll_core_disable_irq( UART2_NVIC );
                break;
            #endif
            #if defined(UART_MODULE_3) && defined(UART3_NVIC)
            case hal_ll_uart_module_num( UART_MODULE_3 ):
                hal_ll_core_disable_irq( UART3_NVIC );
                break;
            #endif
            #if defined(UART_MODULE_4) && defined(UART4_NVIC)
            case hal_ll_uart_module_num( UART_MODULE_4 ):
                hal_ll_core_disable_irq( UART4_NVIC );
                break;
            #endif
            #if defined(UART_MODULE_5) && defined(UART5_NVIC)
            case hal_ll_uart_module_num( UART_MODULE_5 ):
                hal_ll_core_disable_irq( UART5_NVIC );
                break;
            #endif
            #if defined(UART_MODULE_6) && defined(UART6_NVIC)
            case hal_ll_uart_module_num( UART_MODULE_6 ):
                hal_ll_core_disable_irq( UART6_NVIC );
                break;
            #endif
            #if defined(UART_MODULE_7) && defined(UART7_NVIC)
            case hal_ll_uart_module_num( UART_MODULE_7 ):
                hal_ll_core_disable_irq( UART7_NVIC );
                break;
            #endif

            default:
                break;
        }
    }
}

void hal_ll_uart_write( handle_t *handle, uint8_t wr_data) {
    hal_ll_uart_hw_specifics_map_local = hal_ll_get_specifics(hal_ll_uart_get_module_state_address);
    hal_ll_uart_base_handle_t *hal_ll_hw_reg = ( hal_ll_uart_base_handle_t *)hal_ll_uart_hw_specifics_map_local->base;

    hal_ll_hw_reg->dr = wr_data;
}

void hal_ll_uart_write_polling( handle_t *handle, uint8_t wr_data) {
    hal_ll_uart_hw_specifics_map_local = hal_ll_get_specifics(hal_ll_uart_get_module_state_address);
    hal_ll_uart_base_handle_t *hal_ll_hw_reg = ( hal_ll_uart_base_handle_t *)hal_ll_uart_hw_specifics_map_local->base;

    while ( hal_ll_hw_reg->fr & HAL_LL_UART_IT_FR_TXFF ) {
        // Wait for TXFF (Until the transmitter is not full)
    }

    hal_ll_hw_reg->dr = wr_data;
}

uint8_t hal_ll_uart_read( handle_t *handle ) {
    volatile uint16_t frame = 0;
    hal_ll_uart_hw_specifics_map_local = hal_ll_get_specifics(hal_ll_uart_get_module_state_address);
    hal_ll_uart_base_handle_t *hal_ll_hw_reg = ( hal_ll_uart_base_handle_t *)hal_ll_uart_hw_specifics_map_local->base;

    if ( check_reg_bit( &hal_ll_hw_reg->ris, HAL_LL_UART_IT_OER_BIT ) ) {
        set_reg_bit( &hal_ll_hw_reg->icr, HAL_LL_UART_IT_OER_BIT );
    }

    frame = hal_ll_hw_reg->dr;

    /**
     * TODO: Error flags are set by hardware in UARTDR[11:8].
     *       Error handling will be added in a future release.
     *
     * Code example:
     * // If error is present return 0, otherwise actual data.
     * return (frame & HAL_LL_UART_ERRORS) ? (0) : (frame);
     */
    return frame & HAL_LL_UART_DATA;
}

uint8_t hal_ll_uart_read_polling( handle_t *handle ) {
    volatile uint16_t frame = 0;
    hal_ll_uart_hw_specifics_map_local = hal_ll_get_specifics(hal_ll_uart_get_module_state_address);
    hal_ll_uart_base_handle_t *hal_ll_hw_reg = ( hal_ll_uart_base_handle_t *)hal_ll_uart_hw_specifics_map_local->base;

    if ( check_reg_bit( &hal_ll_hw_reg->ris, HAL_LL_UART_IT_OER_BIT ) ) {
        set_reg_bit( &hal_ll_hw_reg->icr, HAL_LL_UART_IT_OER_BIT );
    }

    while ( hal_ll_hw_reg->fr & HAL_LL_UART_IT_FR_RXFE ) {
        // Wait for RXFE (Until the receiver is not empty)
    }

    frame = hal_ll_hw_reg->dr;

    /**
     * TODO: Error flags are set by hardware in UARTDR[11:8].
     *       Error handling will be added in a future release.
     *
     * Code example:
     * // If error is present return 0, otherwise actual data.
     * return (frame & HAL_LL_UART_ERRORS) ? (0) : (frame);
     */
    return frame & HAL_LL_UART_DATA;
}

// ------------------------------------------------------------- DEFAULT EXCEPTION HANDLERS
#if defined(UART_MODULE_0) && defined(UART0_NVIC)
void MARK_AS_IRQ_HANDLER UART0_IRQHandler(void) MIKROC_IV(UART0_NVIC) {
    if ( hal_ll_uart_get_status_flags( HAL_LL_UART0_BASE_ADDRESS , HAL_LL_UART_STATUS_RXMIS_FLAG ) ) {
        hal_ll_uart_clear_status_flag( HAL_LL_UART0_BASE_ADDRESS, HAL_LL_UART_IT_RXIM_BIT );
        irq_handler( objects[ hal_ll_uart_module_num( UART_MODULE_0 ) ], HAL_LL_UART_IRQ_RX );
    }
    if ( hal_ll_uart_get_status_flags( HAL_LL_UART0_BASE_ADDRESS , HAL_LL_UART_STATUS_TXMIS_FLAG ) ) {
        hal_ll_uart_clear_status_flag( HAL_LL_UART0_BASE_ADDRESS, HAL_LL_UART_IT_TXIM_BIT );
        irq_handler( objects[ hal_ll_uart_module_num( UART_MODULE_0 ) ], HAL_LL_UART_IRQ_TX );
    }
}
#endif

#if defined(UART_MODULE_1) && defined(UART1_NVIC)
void MARK_AS_IRQ_HANDLER UART1_IRQHandler(void) MIKROC_IV(UART1_NVIC) {
    if ( hal_ll_uart_get_status_flags( HAL_LL_UART1_BASE_ADDRESS , HAL_LL_UART_STATUS_RXMIS_FLAG ) ) {
        hal_ll_uart_clear_status_flag( HAL_LL_UART1_BASE_ADDRESS, HAL_LL_UART_IT_RXIM_BIT );
        irq_handler( objects[ hal_ll_uart_module_num( UART_MODULE_1 ) ], HAL_LL_UART_IRQ_RX );
    }
    if ( hal_ll_uart_get_status_flags( HAL_LL_UART1_BASE_ADDRESS , HAL_LL_UART_STATUS_TXMIS_FLAG ) ) {
        hal_ll_uart_clear_status_flag( HAL_LL_UART1_BASE_ADDRESS, HAL_LL_UART_IT_TXIM_BIT );
        irq_handler( objects[ hal_ll_uart_module_num( UART_MODULE_1 ) ], HAL_LL_UART_IRQ_TX );
    }
}
#endif

#if defined(UART_MODULE_2) && defined(UART2_NVIC)
void MARK_AS_IRQ_HANDLER UART2_IRQHandler(void) MIKROC_IV(UART2_NVIC) {
    if ( hal_ll_uart_get_status_flags( HAL_LL_UART2_BASE_ADDRESS , HAL_LL_UART_STATUS_RXMIS_FLAG ) ) {
        hal_ll_uart_clear_status_flag( HAL_LL_UART2_BASE_ADDRESS, HAL_LL_UART_IT_RXIM_BIT );
        irq_handler( objects[ hal_ll_uart_module_num( UART_MODULE_2 ) ], HAL_LL_UART_IRQ_RX );
    }
    if ( hal_ll_uart_get_status_flags( HAL_LL_UART2_BASE_ADDRESS , HAL_LL_UART_STATUS_TXMIS_FLAG ) ) {
        hal_ll_uart_clear_status_flag( HAL_LL_UART2_BASE_ADDRESS, HAL_LL_UART_IT_TXIM_BIT );
        irq_handler( objects[ hal_ll_uart_module_num( UART_MODULE_2 ) ], HAL_LL_UART_IRQ_TX );
    }
}
#endif

#if defined(UART_MODULE_3) && defined(UART3_NVIC)
void MARK_AS_IRQ_HANDLER UART3_IRQHandler(void) MIKROC_IV(UART3_NVIC) {
    if ( hal_ll_uart_get_status_flags( HAL_LL_UART3_BASE_ADDRESS , HAL_LL_UART_STATUS_RXMIS_FLAG ) ) {
        hal_ll_uart_clear_status_flag( HAL_LL_UART3_BASE_ADDRESS, HAL_LL_UART_IT_RXIM_BIT );
        irq_handler( objects[ hal_ll_uart_module_num( UART_MODULE_3 ) ], HAL_LL_UART_IRQ_RX );
    }
    if ( hal_ll_uart_get_status_flags( HAL_LL_UART3_BASE_ADDRESS , HAL_LL_UART_STATUS_TXMIS_FLAG ) ) {
        hal_ll_uart_clear_status_flag( HAL_LL_UART3_BASE_ADDRESS, HAL_LL_UART_IT_TXIM_BIT );
        irq_handler( objects[ hal_ll_uart_module_num( UART_MODULE_3 ) ], HAL_LL_UART_IRQ_TX );
    }
}
#endif

#if defined(UART_MODULE_4) && defined(UART4_NVIC)
void MARK_AS_IRQ_HANDLER UART4_IRQHandler(void) MIKROC_IV(UART4_NVIC) {
    if ( hal_ll_uart_get_status_flags( HAL_LL_UART4_BASE_ADDRESS , HAL_LL_UART_STATUS_RXMIS_FLAG ) ) {
        hal_ll_uart_clear_status_flag( HAL_LL_UART4_BASE_ADDRESS, HAL_LL_UART_IT_RXIM_BIT );
        irq_handler( objects[ hal_ll_uart_module_num( UART_MODULE_4 ) ], HAL_LL_UART_IRQ_RX );
    }
    if ( hal_ll_uart_get_status_flags( HAL_LL_UART4_BASE_ADDRESS , HAL_LL_UART_STATUS_TXMIS_FLAG ) ) {
        hal_ll_uart_clear_status_flag( HAL_LL_UART4_BASE_ADDRESS, HAL_LL_UART_IT_TXIM_BIT );
        irq_handler( objects[ hal_ll_uart_module_num( UART_MODULE_4 ) ], HAL_LL_UART_IRQ_TX );
    }
}
#endif

#if defined(UART_MODULE_5) && defined(UART5_NVIC)
void MARK_AS_IRQ_HANDLER UART5_IRQHandler(void) MIKROC_IV(UART5_NVIC) {
    if ( hal_ll_uart_get_status_flags( HAL_LL_UART5_BASE_ADDRESS , HAL_LL_UART_STATUS_RXMIS_FLAG ) ) {
        hal_ll_uart_clear_status_flag( HAL_LL_UART5_BASE_ADDRESS, HAL_LL_UART_IT_RXIM_BIT );
        irq_handler( objects[ hal_ll_uart_module_num( UART_MODULE_5 ) ], HAL_LL_UART_IRQ_RX );
    }
    if ( hal_ll_uart_get_status_flags( HAL_LL_UART5_BASE_ADDRESS , HAL_LL_UART_STATUS_TXMIS_FLAG ) ) {
        hal_ll_uart_clear_status_flag( HAL_LL_UART5_BASE_ADDRESS, HAL_LL_UART_IT_TXIM_BIT );
        irq_handler( objects[ hal_ll_uart_module_num( UART_MODULE_5 )], HAL_LL_UART_IRQ_TX );
    }
}
#endif

#if defined(UART_MODULE_6) && defined(UART6_NVIC)
void MARK_AS_IRQ_HANDLER UART6_IRQHandler(void) MIKROC_IV(UART6_NVIC) {
    if ( hal_ll_uart_get_status_flags( HAL_LL_UART6_BASE_ADDRESS , HAL_LL_UART_STATUS_RXMIS_FLAG ) ) {
        hal_ll_uart_clear_status_flag( HAL_LL_UART6_BASE_ADDRESS, HAL_LL_UART_IT_RXIM_BIT );
        irq_handler( objects[ hal_ll_uart_module_num( UART_MODULE_6 ) ], HAL_LL_UART_IRQ_RX );
    }
    if ( hal_ll_uart_get_status_flags( HAL_LL_UART6_BASE_ADDRESS , HAL_LL_UART_STATUS_TXMIS_FLAG ) ) {
        hal_ll_uart_clear_status_flag( HAL_LL_UART6_BASE_ADDRESS, HAL_LL_UART_IT_TXIM_BIT );
        irq_handler( objects[ hal_ll_uart_module_num( UART_MODULE_6 ) ], HAL_LL_UART_IRQ_TX );
    }
}
#endif

#if defined(UART_MODULE_7) && defined(UART7_NVIC)
void MARK_AS_IRQ_HANDLER UART7_IRQHandler(void) MIKROC_IV(UART7_NVIC) {
    if ( hal_ll_uart_get_status_flags( HAL_LL_UART7_BASE_ADDRESS , HAL_LL_UART_STATUS_RXMIS_FLAG ) ) {
        hal_ll_uart_clear_status_flag( HAL_LL_UART7_BASE_ADDRESS, HAL_LL_UART_IT_RXIM_BIT );
        irq_handler( objects[ hal_ll_uart_module_num( UART_MODULE_7 ) ], HAL_LL_UART_IRQ_RX );
    }
    if ( hal_ll_uart_get_status_flags( HAL_LL_UART7_BASE_ADDRESS , HAL_LL_UART_STATUS_TXMIS_FLAG ) ) {
        hal_ll_uart_clear_status_flag( HAL_LL_UART7_BASE_ADDRESS, HAL_LL_UART_IT_TXIM_BIT );
        irq_handler( objects[ hal_ll_uart_module_num( UART_MODULE_7 ) ], HAL_LL_UART_IRQ_TX );
    }
}
#endif

// ----------------------------------------------- PRIVATE FUNCTION DEFINITIONS
static uint8_t hal_ll_uart_find_index( handle_t *handle ) {
    hal_ll_uart_hw_specifics_map_local = hal_ll_get_specifics(hal_ll_uart_get_module_state_address);

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

    if ( (HAL_LL_PIN_NC == tx_pin) || (HAL_LL_PIN_NC == rx_pin) ) {
        return HAL_LL_PIN_NC;
    }

    for ( tx_index = 0; tx_index < tx_map_size; tx_index++ ) {
        if ( hal_ll_uart_tx_map[ tx_index ].pin == tx_pin ) {
            for ( rx_index = 0; rx_index < rx_map_size; rx_index++ ) {
                if ( hal_ll_uart_rx_map[ rx_index ].pin == rx_pin ) {
                    if ( hal_ll_uart_tx_map[ tx_index ].base == hal_ll_uart_rx_map[ rx_index ].base ) {
                        // Get module number.
                        hal_ll_module_id = hal_ll_uart_tx_map[ tx_index ].module_index;

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
    uint8_t hal_ll_module_count = sizeof(hal_ll_module_state) / (sizeof(hal_ll_uart_handle_register_t));
    static uint8_t hal_ll_module_error = sizeof(hal_ll_module_state) / (sizeof(hal_ll_uart_handle_register_t));

    while( hal_ll_module_count-- ) {
        if (hal_ll_uart_get_base_from_hal_handle == hal_ll_uart_hw_specifics_map[hal_ll_module_count].base) {
            return &hal_ll_uart_hw_specifics_map[hal_ll_module_count];
        }
    }

    return &hal_ll_uart_hw_specifics_map[hal_ll_module_error];
}

static void hal_ll_uart_set_clock( hal_ll_uart_hw_specifics_map_t *map, bool hal_ll_state ) {
    switch ( map->module_index ) {
        #ifdef UART_MODULE_0
        case ( hal_ll_uart_module_num( UART_MODULE_0 )):
            ( hal_ll_state == true ) ? ( set_reg_bit( _SYSCTL_RCGCUART, HAL_LL_UART0EN ) ) : ( clear_reg_bit( _SYSCTL_RCGCUART, HAL_LL_UART0EN ) );
            break;
        #endif
        #ifdef UART_MODULE_1
        case ( hal_ll_uart_module_num( UART_MODULE_1 )):
            ( hal_ll_state == true ) ? ( set_reg_bit( _SYSCTL_RCGCUART, HAL_LL_UART1EN ) ) : ( clear_reg_bit( _SYSCTL_RCGCUART, HAL_LL_UART1EN ) );
            break;
        #endif
        #ifdef UART_MODULE_2
        case ( hal_ll_uart_module_num( UART_MODULE_2 )):
            ( hal_ll_state == true ) ? ( set_reg_bit( _SYSCTL_RCGCUART, HAL_LL_UART2EN ) ) : ( clear_reg_bit( _SYSCTL_RCGCUART, HAL_LL_UART2EN ) );
            break;
        #endif
        #ifdef UART_MODULE_3
        case ( hal_ll_uart_module_num( UART_MODULE_3 )):
            ( hal_ll_state == true ) ? ( set_reg_bit( _SYSCTL_RCGCUART, HAL_LL_UART3EN ) ) : ( clear_reg_bit( _SYSCTL_RCGCUART, HAL_LL_UART3EN ) );
            break;
        #endif
        #ifdef UART_MODULE_4
        case ( hal_ll_uart_module_num( UART_MODULE_4 )):
            ( hal_ll_state == true ) ? ( set_reg_bit( _SYSCTL_RCGCUART, HAL_LL_UART4EN ) ) : ( clear_reg_bit( _SYSCTL_RCGCUART, HAL_LL_UART4EN ) );
            break;
        #endif
        #ifdef UART_MODULE_5
        case ( hal_ll_uart_module_num( UART_MODULE_5 )):
            ( hal_ll_state == true ) ? ( set_reg_bit( _SYSCTL_RCGCUART, HAL_LL_UART5EN ) ) : ( clear_reg_bit( _SYSCTL_RCGCUART, HAL_LL_UART5EN ) );
            break;
        #endif
        #ifdef UART_MODULE_6
        case ( hal_ll_uart_module_num( UART_MODULE_6 )):
            ( hal_ll_state == true ) ? ( set_reg_bit( _SYSCTL_RCGCUART, HAL_LL_UART6EN ) ) : ( clear_reg_bit( _SYSCTL_RCGCUART, HAL_LL_UART6EN ) );
            break;
        #endif
        #ifdef UART_MODULE_7
        case ( hal_ll_uart_module_num( UART_MODULE_7 )):
            ( hal_ll_state == true ) ? ( set_reg_bit( _SYSCTL_RCGCUART, HAL_LL_UART7EN ) ) : ( clear_reg_bit( _SYSCTL_RCGCUART, HAL_LL_UART7EN ) );
            break;
        #endif

        default:
            break;
    }
}

static void hal_ll_uart_map_pins( uint8_t module_index, hal_ll_uart_pin_id *index_list ) {
    // Map new pins.
    hal_ll_uart_hw_specifics_map[module_index].pins.tx_pin.pin_name = hal_ll_uart_tx_map[ index_list[module_index].pin_tx ].pin;
    hal_ll_uart_hw_specifics_map[module_index].pins.rx_pin.pin_name = hal_ll_uart_rx_map[ index_list[module_index].pin_rx ].pin;
    // TX and RX could have different alternate function settings, hence save both AF values.
    hal_ll_uart_hw_specifics_map[module_index].pins.tx_pin.pin_af = hal_ll_uart_tx_map[ index_list[module_index].pin_tx ].af;
    hal_ll_uart_hw_specifics_map[module_index].pins.rx_pin.pin_af = hal_ll_uart_rx_map[ index_list[module_index].pin_rx ].af;
}

static void hal_ll_uart_alternate_functions_set_state( hal_ll_uart_hw_specifics_map_t *map, bool hal_ll_state ) {
    module_struct module;
    uint32_t uart_config = 0;

    if ( (map->pins.rx_pin.pin_name != HAL_LL_PIN_NC) &&
         (map->pins.tx_pin.pin_name != HAL_LL_PIN_NC) )
    {
        if( hal_ll_state != false ) {
            uart_config |= GPIO_CFG_ALT_FUNCTION | GPIO_CFG_DIGITAL_ENABLE | GPIO_CFG_DRIVE_8mA;
        }

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
    uint32_t reg = 0;
    uint32_t integer_divider = 0;
    uint32_t fractional_divider = 0;
    uint8_t clk_div;
    hal_ll_uart_base_handle_t *hal_ll_hw_reg = hal_ll_uart_get_base_struct(map->base);

    if (hal_ll_hw_reg->ctl & HAL_LL_UART_CTL_HSE_BIT) {
        clk_div = 8;
    } else {
        clk_div = 16;
    }

    double hal_ll_baud_value = ( ( double )( hal_ll_uart_get_clock_speed( map->module_index ) ) /
                                 ( double )( clk_div * ( map->baud_rate.baud ) ) );
    uint32_t hal_ll_baud_value_int = ( uint32_t )hal_ll_baud_value;
    uint32_t hal_ll_baud_value_fract = ( uint32_t )( ( ( hal_ll_baud_value - ( double ) hal_ll_baud_value_int ) * ( double )64 ) + ( double )0.5 );
    uint32_t hal_ll_baud_real_value = ( uint32_t )( ( double )( hal_ll_uart_get_clock_speed( map->module_index ) ) /
                                      ( double )( clk_div * ( ( double )hal_ll_baud_value_int + ( hal_ll_baud_value_fract/
                                      ( double )64 ) ) ) + ( double )0.5);

    // If error greater than specified, cancel setting baud rate.
    if( (hal_ll_uart_get_baud_error(hal_ll_baud_real_value,map->baud_rate.baud)) > HAL_LL_UART_ACCEPTABLE_ERROR ) {
        map->baud_rate.real_baud = hal_ll_uart_get_baud_error(hal_ll_baud_real_value,map->baud_rate.baud);
    } else {
        map->baud_rate.real_baud = hal_ll_baud_real_value;
        hal_ll_hw_reg->ibrd = hal_ll_baud_value_int;
        hal_ll_hw_reg->fbrd = hal_ll_baud_value_fract;
    }
}

static uint32_t hal_ll_uart_get_clock_speed( hal_ll_pin_name_t module_index ) {
    return Get_Fosc_kHz() * 1000;
}

static void hal_ll_uart_set_stop_bits_bare_metal( hal_ll_uart_hw_specifics_map_t *map ) {
    hal_ll_uart_base_handle_t *hal_ll_hw_reg = hal_ll_uart_get_base_struct(map->base);

    switch ( map->stop_bit ) {
        case HAL_LL_UART_STOP_BITS_ONE:
            hal_ll_hw_reg->lcrh &= ~STOP_BITS_MASK;
            break;
        case HAL_LL_UART_STOP_BITS_TWO:
            hal_ll_hw_reg->lcrh |= STOP_BITS_TWO;
            break;

        default:
            break;
    }
}

static void hal_ll_uart_set_data_bits_bare_metal( hal_ll_uart_hw_specifics_map_t *map ) {
    hal_ll_uart_base_handle_t *hal_ll_hw_reg = hal_ll_uart_get_base_struct(map->base);

    switch ( map->data_bit ) {
        case HAL_LL_UART_DATA_BITS_5:
            hal_ll_hw_reg->lcrh &= ~DATA_BITS_MASK;
            break;
        case HAL_LL_UART_DATA_BITS_6:
            hal_ll_hw_reg->lcrh &= ~DATA_BITS_MASK;
            hal_ll_hw_reg->lcrh |= DATA_BIT_6;
            break;
        case HAL_LL_UART_DATA_BITS_7:
            hal_ll_hw_reg->lcrh &= ~DATA_BITS_MASK;
            hal_ll_hw_reg->lcrh |= DATA_BIT_7;
            break;
        case HAL_LL_UART_DATA_BITS_8:
            hal_ll_hw_reg->lcrh |= DATA_BIT_8;
            break;

        default:
            break;
    }
}

static void hal_ll_uart_set_parity_bare_metal( hal_ll_uart_hw_specifics_map_t *map ) {
    hal_ll_uart_base_handle_t *hal_ll_hw_reg = hal_ll_uart_get_base_struct(map->base);

    switch ( map->parity ) {
        case HAL_LL_UART_PARITY_NONE:
            hal_ll_hw_reg->lcrh &= ~(PARITY_MASK | PARITY_STICK);
            break;
        case HAL_LL_UART_PARITY_EVEN:
            hal_ll_hw_reg->lcrh |= (PARITY_EVEN | PARITY_STICK);
            break;
        case HAL_LL_UART_PARITY_ODD:
            hal_ll_hw_reg->lcrh &= ~PARITY_MASK;
            hal_ll_hw_reg->lcrh |= (PARITY_ODD | PARITY_STICK);
            break;

        default:
            break;
    }
}

static void hal_ll_uart_set_module( hal_ll_uart_base_handle_t *hal_ll_hw_reg, hal_ll_uart_state_t pin_state ) {
    switch ( pin_state ) {
        case HAL_LL_UART_DISABLE:
            clear_reg_bit( &( hal_ll_hw_reg->ctl ), HAL_LL_UART_CTL_UARTEN );
            break;
        case HAL_LL_UART_ENABLE:
            set_reg_bit( &( hal_ll_hw_reg->ctl ), HAL_LL_UART_CTL_UARTEN );
            break;

        default:
            break;
    }
}

static void hal_ll_uart_set_transmitter( hal_ll_uart_base_handle_t *hal_ll_hw_reg, hal_ll_uart_state_t pin_state ) {
    switch ( pin_state ) {
        case HAL_LL_UART_DISABLE:
            clear_reg_bit( &( hal_ll_hw_reg->ctl ), HAL_LL_UART_CTL_TXE );
            break;
        case HAL_LL_UART_ENABLE:
            set_reg_bit( &( hal_ll_hw_reg->ctl ), HAL_LL_UART_CTL_TXE );
            break;

        default:
            break;
    }
}

static void hal_ll_uart_set_receiver( hal_ll_uart_base_handle_t *hal_ll_hw_reg, hal_ll_uart_state_t pin_state ) {
    switch ( pin_state ) {
        case HAL_LL_UART_DISABLE:
            clear_reg_bit( &( hal_ll_hw_reg->ctl ), HAL_LL_UART_CTL_RXE );
            break;
        case HAL_LL_UART_ENABLE:
            set_reg_bit( &( hal_ll_hw_reg->ctl ), HAL_LL_UART_CTL_RXE );
            break;

        default:
            break;
    }
}

static void hal_ll_uart_clear_regs( hal_ll_uart_base_handle_t *hal_ll_hw_reg ) {
    clear_reg_bit( &( hal_ll_hw_reg->ctl ), HAL_LL_UART_CTL_UARTEN );
    clear_reg_bit( &( hal_ll_hw_reg->lcrh ), HAL_LL_UART_CTL_FEN );
    hal_ll_hw_reg->lcrh &= ~HAL_LL_UART_LCRH_MASK;
    hal_ll_hw_reg->ctl &= ~HAL_LL_UART_CTL_MASK;
}

static void hal_ll_uart_hw_init( hal_ll_uart_hw_specifics_map_t *map ) {
    hal_ll_uart_clear_regs( map->base );

    hal_ll_uart_set_baud_bare_metal( map );

    /* In order for UART Transmit interrupt to
     * be triggered, initial dummy data write is
     * required. Writing to the register here is
     * harmless as we disable TX/RX pins and the
     * whole UART module in `hal_ll_uart_clear_regs`
     * function. For more information on this issue,
     * please have a look at the following link.
     *
     * <https://e2e.ti.com/support/microcontrollers/arm-based-microcontrollers-group/
     *  arm-based-microcontrollers/f/arm-based-microcontrollers-forum/603001/
     *  tm4c129encpdt-uart-transmit-interrupt-not-being-triggered>
     */
    ((hal_ll_uart_base_handle_t *)(map->base))->dr = 0;

    hal_ll_uart_set_data_bits_bare_metal( map );

    hal_ll_uart_set_parity_bare_metal( map );

    hal_ll_uart_set_stop_bits_bare_metal( map );

    hal_ll_uart_set_transmitter( map->base, HAL_LL_UART_ENABLE );

    hal_ll_uart_set_receiver( map->base, HAL_LL_UART_ENABLE );

    hal_ll_uart_set_module( map->base, HAL_LL_UART_ENABLE );
}

static void hal_ll_uart_init( hal_ll_uart_hw_specifics_map_t *map ) {
    /*!< @brief Static, because clock doesn't change during runtime */
    uint32_t hal_ll_clock_value = Get_Fosc_kHz() * 2;

    hal_ll_uart_alternate_functions_set_state( map, true );

    hal_ll_uart_set_clock( map, true );

    /* There must be a delay of 3 system clocks after the UART module
     * clock is enabled before any UART module registers are accessed.
     * See datasheet page 1327 for more information.
     * <https://www.ti.com/lit/gpn/tm4c129xnczad>
     */
    assembly( nop );
    assembly( nop );
    assembly( nop );

    hal_ll_uart_hw_init( map );

    hal_ll_uart_wait_for_sync(hal_ll_clock_value);
}

// ------------------------------------------------------------------------- END
