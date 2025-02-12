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
** OF MERCHANTABILITY, EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED
** TO THE WARRANTIES FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT.
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

#include "hal_ll_gpio.h"
#include "hal_ll_core.h"
#include "hal_ll_uart.h"
#include "hal_ll_uart_pin_map.h"

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

/*!< @brief Helper macro for current Clock value (Hertz). */
#define _fosc (Get_Fosc_kHz()*1000)

/*!< @brief Helper macro for UART module sync time. */
#define hal_ll_uart_wait_for_sync(_hal_sync_val) while( _hal_sync_val-- ){asm nop;}

/*!< @brief Power module macros. */
#define HAL_LL_PRR_PRUSART0_BIT (1)
#define HAL_LL_PRR_PRUSART3_BIT (2)

/*!< @brief Helper macros for enabling/disabling transmitter/receiver hardware drivers. */
#define HAL_LL_UART_CREN_BIT (4)
#define HAL_LL_UART_TXEN_BIT (3)

/*!< @brief Macros defining USART Data bits values. */
#define HAL_LL_UART_DATA_BITS_9_USCRB_REGISTER_BIT (2)
#define HAL_LL_UART_DATA_BITS_MASK_USCRC_REGISTER (1)
#define HAL_LL_UART_DATA_BITS_5_MASK (3)
#define HAL_LL_UART_DATA_BITS_7_MASK (2)
#define HAL_LL_UART_DATA_BITS_8_MASK (3)

/*!< @brief Macros defining USART Parity bits values. */
#define HAL_LL_UART_PARITY_MASK (4)
#define HAL_LL_UART_PARITY_NONE_MASK (0)
#define HAL_LL_UART_PARITY_EVEN_MASK (2)
#define HAL_LL_UART_PARITY_ODD_MASK (3)

/*!< @brief Macros defining USART Stop bit values and mask. */
#define HAL_LL_UART_STOP_BIT (3)
#define HAL_LL_UART_STOP_BITS_TWO_MASK (0x08)

/*!< @brief Macro defining USART async mode clock divider. */
#define HAL_LL_UART_ASYNCHRONOUS_MODE_CLOCK_DIVIDER (16.0)
#define HAL_LL_UART_ASYNCHRONOUS_MODE_CLOCK_DIVIDER_U2Xn (8.0)

/*!< @brief Macro defining length of Baud Rate Low register. */
#define HAL_LL_UART_BAUD_RATE_REG_LOW_LENGTH (255)

/*!< @brief Helper macros for getting appropriate Baud rate prescaler value. */
#define HAL_LL_UART_CONTROL_AND_STATUS_REGISTER_SELECTED (0x80)
#define HAL_LL_UART_BAUD_RATE_REGISTER_SELECTED (0x3F)
#define HAL_LL_UART_THIRD_NIBBLE_MASK (0x0F00)
#define HAL_LL_UART_FLOOR_OR_CEILING_MASK (0.5)

/*!< @brief Helper macros for triggering UART interrupt. */
#define HAL_LL_UART_TRIGGER_INTERRUPT (0x0)
#define HAL_LL_UART_TXIF_BIT (6)
#define HAL_LL_UART_RXIF_BIT (7)

/*!< @brief Helper macro for retaining Control and Status Register bits. */
#define HAL_LL_UART_FIRST_NIBBLE_MASK (0xF)

/*!< @brief Helper macro for enabling double transmission speed mode. */
#define HAL_LL_UART_DOUBLE_SPEED (1)

/*!< @brief Macro used for calculating actual baud rate value and error value. */
#define HAL_LL_UART_ACCEPTABLE_ERROR (float)1.0
#define hal_ll_uart_get_baud_error( _baud_real,_baud ) ( (float)abs( _baud_real/_baud - 1 ) * 100 )

/*!< @brief Macro used for status register flag check.
 * Used in interrupt handlers.
 */
#define hal_ll_uart_get_status_flags(module_num) ( read_reg( hal_ll_uart_regs[ module_num ].uart_ucsra_reg_addr ))

/*!< @brief Macro used for module interrupt enabling.
 * Used in interrupt handlers.
 */
#if defined(UART_MODULE_0) && defined(UART_MODULE_1) && defined(UART_MODULE_2) && defined(UART_MODULE_3)
#define __HAL_LL_UART_ENABLE_IT(_num,_int) (_num==hal_ll_uart_module_num(UART_MODULE_0))?(set_reg_bit(HAL_LL_USART0_UCSR0B_REG_ADDRESS,_int)): \
                                           (_num==hal_ll_uart_module_num(UART_MODULE_1))?(set_reg_bit(HAL_LL_USART1_UCSR1B_REG_ADDRESS,_int)): \
                                           (_num==hal_ll_uart_module_num(UART_MODULE_2))?(set_reg_bit(HAL_LL_USART2_UCSR2B_REG_ADDRESS,_int)): \
                                           (set_reg_bit(HAL_LL_USART3_UCSR3B_REG_ADDRESS,_int))
#elif defined(UART_MODULE_0) && defined(UART_MODULE_1) && defined(UART_MODULE_2)
#define __HAL_LL_UART_ENABLE_IT(_num,_int) (_num==hal_ll_uart_module_num(UART_MODULE_0))?(set_reg_bit(HAL_LL_USART0_UCSR0B_REG_ADDRESS,_int)): \
                                           (_num==hal_ll_uart_module_num(UART_MODULE_1))?(set_reg_bit(HAL_LL_USART1_UCSR1B_REG_ADDRESS,_int)): \
                                           (set_reg_bit(HAL_LL_USART2_UCSR2B_REG_ADDRESS,_int))
#elif defined(UART_MODULE_0) && defined(UART_MODULE_1)
#define __HAL_LL_UART_ENABLE_IT(_num,_int) (_num==hal_ll_uart_module_num(UART_MODULE_0))?(set_reg_bit(HAL_LL_USART0_UCSR0B_REG_ADDRESS,_int)): \
                                           (set_reg_bit(HAL_LL_USART1_UCSR1B_REG_ADDRESS,_int))
#elif defined(UART_MODULE_1)
#define __HAL_LL_UART_ENABLE_IT(_num,_int) (set_reg_bit(HAL_LL_USART1_UCSR1B_REG_ADDRESS,_int))
#elif defined(UART_MODULE_0)
#define __HAL_LL_UART_ENABLE_IT(_num,_int) (set_reg_bit(HAL_LL_USART0_UCSR0B_REG_ADDRESS,_int))
#endif

/*!< @brief Macro used for module interrupt disabling.
 * Used in interrupt handlers.
 */
#if defined(UART_MODULE_0) && defined(UART_MODULE_1) && defined(UART_MODULE_2) && defined(UART_MODULE_3)
#define __HAL_LL_UART_DISABLE_IT(_num,_int) (_num==hal_ll_uart_module_num(UART_MODULE_0))?(clear_reg_bit(HAL_LL_USART0_UCSR0B_REG_ADDRESS,_int)): \
                                           (_num==hal_ll_uart_module_num(UART_MODULE_1))?(clear_reg_bit(HAL_LL_USART1_UCSR1B_REG_ADDRESS,_int)): \
                                           (_num==hal_ll_uart_module_num(UART_MODULE_2))?(clear_reg_bit(HAL_LL_USART2_UCSR2B_REG_ADDRESS,_int)): \
                                           (clear_reg_bit(HAL_LL_USART3_UCSR3B_REG_ADDRESS,_int))
#elif defined(UART_MODULE_0) && defined(UART_MODULE_1) && defined(UART_MODULE_2)
#define __HAL_LL_UART_DISABLE_IT(_num,_int) (_num==hal_ll_uart_module_num(UART_MODULE_0))?(clear_reg_bit(HAL_LL_USART0_UCSR0B_REG_ADDRESS,_int)): \
                                           (_num==hal_ll_uart_module_num(UART_MODULE_1))?(clear_reg_bit(HAL_LL_USART1_UCSR1B_REG_ADDRESS,_int)): \
                                           (clear_reg_bit(HAL_LL_USART2_UCSR2B_REG_ADDRESS,_int))
#elif defined(UART_MODULE_0) && defined(UART_MODULE_1)
#define __HAL_LL_UART_DISABLE_IT(_num,_int) (_num==hal_ll_uart_module_num(UART_MODULE_0))?(clear_reg_bit(HAL_LL_USART0_UCSR0B_REG_ADDRESS,_int)): \
                                           (clear_reg_bit(HAL_LL_USART1_UCSR1B_REG_ADDRESS,_int))
#elif defined(UART_MODULE_1)
#define __HAL_LL_UART_DISABLE_IT(_num,_int) (clear_reg_bit(HAL_LL_USART1_UCSR1B_REG_ADDRESS,_int))
#elif defined(UART_MODULE_0)
#define __HAL_LL_UART_DISABLE_IT(_num,_int) (clear_reg_bit(HAL_LL_USART0_UCSR0B_REG_ADDRESS,_int))
#endif

/*!< @brief Macro used for module interrupt source check.
 * Used in interrupt handlers.
 */
#define __HAL_LL_UART_GET_IT_SOURCE(_num,_int) read_reg_bits(hal_ll_uart_regs[_num].uart_ucsrb_reg_addr,(1<<_int))

// ------------------------------------------------------------------ TYPEDEFS
/*!< @brief UART HW register structure */
typedef struct {
    hal_ll_base_addr_t uart_udr_reg_addr; // USART I/O Data register.
    hal_ll_base_addr_t uart_ucsra_reg_addr; // USART Control and Status register A.
    hal_ll_base_addr_t uart_ucsrb_reg_addr; // USART Control and Status register B.
    hal_ll_base_addr_t uart_ucsrc_reg_addr; // USART Control and Status register C.
    hal_ll_base_addr_t uart_ubrrh_reg_addr; // USART Baud Rate High register.
    hal_ll_base_addr_t uart_ubrrl_reg_addr; // USART Baud Rate Low register.
} hal_ll_uart_base_handle_t;

/*!< @brief UART baud rate structure */
typedef struct {
    uint32_t baud;
    uint32_t real_baud;
} hal_ll_uart_baud_t;

/*!< @brief UART hw specific structure */
typedef struct {
    const hal_ll_uart_base_handle_t *base;
    hal_ll_pin_name_t module_index;
    hal_ll_uart_pins_t pins;
    hal_ll_uart_baud_t baud_rate;
    hal_ll_uart_parity_t parity;
    hal_ll_uart_stop_bits_t stop_bit;
    hal_ll_uart_data_bits_t data_bit;
} hal_ll_uart_hw_specifics_map_t;

/*!< @brief UART hw specific module values */
typedef struct {
    hal_ll_pin_name_t pin_tx;
    hal_ll_pin_name_t pin_rx;
} hal_ll_uart_pin_id;

/*!< @brief UART hw specific error values */
typedef enum {
    HAL_LL_UART_SUCCESS = 0,
    HAL_LL_UART_WRONG_PINS,
    HAL_LL_UART_MODULE_ERROR,

    HAL_LL_UART_ERROR = (-1)
} hal_ll_uart_err_t;

/*!< @brief UART module state selection */
typedef enum {
    HAL_LL_UART_DISABLE = 0,
    HAL_LL_UART_ENABLE
} hal_ll_uart_state_t;

// ------------------------------------------------------------------ CONSTANTS
/*!< @brief UART modules register array */
static const hal_ll_uart_base_handle_t hal_ll_uart_regs[ UART_MODULE_COUNT + 1 ] = {
    #ifdef UART_MODULE_0
    { HAL_LL_USART0_UDR0_REG_ADDRESS, HAL_LL_USART0_UCSR0A_REG_ADDRESS, HAL_LL_USART0_UCSR0B_REG_ADDRESS,
      HAL_LL_USART0_UCSR0C_REG_ADDRESS, HAL_LL_USART0_UBRR0H_REG_ADDRESS, HAL_LL_USART0_UBRR0L_REG_ADDRESS },
    #endif
    #ifdef UART_MODULE_1
    { HAL_LL_USART1_UDR1_REG_ADDRESS, HAL_LL_USART1_UCSR1A_REG_ADDRESS, HAL_LL_USART1_UCSR1B_REG_ADDRESS,
      HAL_LL_USART1_UCSR1C_REG_ADDRESS, HAL_LL_USART1_UBRR1H_REG_ADDRESS, HAL_LL_USART1_UBRR1L_REG_ADDRESS },
    #endif
    #ifdef UART_MODULE_2
    { HAL_LL_USART2_UDR2_REG_ADDRESS, HAL_LL_USART2_UCSR2A_REG_ADDRESS, HAL_LL_USART2_UCSR2B_REG_ADDRESS,
      HAL_LL_USART2_UCSR2C_REG_ADDRESS, HAL_LL_USART2_UBRR2H_REG_ADDRESS, HAL_LL_USART2_UBRR2L_REG_ADDRESS },
    #endif
    #ifdef UART_MODULE_3
    { HAL_LL_USART3_UDR3_REG_ADDRESS, HAL_LL_USART3_UCSR3A_REG_ADDRESS, HAL_LL_USART3_UCSR3B_REG_ADDRESS,
      HAL_LL_USART3_UCSR3C_REG_ADDRESS, HAL_LL_USART3_UBRR3H_REG_ADDRESS, HAL_LL_USART3_UBRR3L_REG_ADDRESS },
    #endif

    { HAL_LL_MODULE_ERROR, HAL_LL_MODULE_ERROR, HAL_LL_MODULE_ERROR,
      HAL_LL_MODULE_ERROR, HAL_LL_MODULE_ERROR, HAL_LL_MODULE_ERROR }
};

// ------------------------------------------------------------------ VARIABLES
/*!< @brief Global handle variables used in functions */
static volatile hal_ll_uart_handle_register_t *low_level_handle;
static volatile hal_ll_uart_hw_specifics_map_t *hal_ll_uart_hw_specifics_map_local;

/*!< @brief Global interrupt handlers used in functions */
static hal_ll_uart_isr_t irq_handler;
static handle_t objects[UART_MODULE_COUNT] = { NULL };

/*!< @brief UART hardware specific info */
static hal_ll_uart_hw_specifics_map_t hal_ll_uart_hw_specifics_map[ UART_MODULE_COUNT + 1 ] = {
    #ifdef UART_MODULE_0
    { &hal_ll_uart_regs[ hal_ll_uart_module_num(UART_MODULE_0) ], hal_ll_uart_module_num(UART_MODULE_0),
    { HAL_LL_PIN_NC, HAL_LL_UART_TXIF_BIT, HAL_LL_PIN_NC, HAL_LL_UART_RXIF_BIT },
    { 115200, 0 }, HAL_LL_UART_PARITY_DEFAULT, HAL_LL_UART_STOP_BITS_DEFAULT, HAL_LL_UART_DATA_BITS_DEFAULT },
    #endif
    #ifdef UART_MODULE_1
    { &hal_ll_uart_regs[ hal_ll_uart_module_num(UART_MODULE_1) ], hal_ll_uart_module_num(UART_MODULE_1),
    { HAL_LL_PIN_NC, HAL_LL_UART_TXIF_BIT, HAL_LL_PIN_NC, HAL_LL_UART_RXIF_BIT },
    { 115200, 0 }, HAL_LL_UART_PARITY_DEFAULT, HAL_LL_UART_STOP_BITS_DEFAULT, HAL_LL_UART_DATA_BITS_DEFAULT },
    #endif
    #ifdef UART_MODULE_2
    { &hal_ll_uart_regs[ hal_ll_uart_module_num(UART_MODULE_2) ], hal_ll_uart_module_num(UART_MODULE_2),
    { HAL_LL_PIN_NC, HAL_LL_UART_TXIF_BIT, HAL_LL_PIN_NC, HAL_LL_UART_RXIF_BIT },
    { 115200, 0 }, HAL_LL_UART_PARITY_DEFAULT, HAL_LL_UART_STOP_BITS_DEFAULT, HAL_LL_UART_DATA_BITS_DEFAULT },
    #endif
    #ifdef UART_MODULE_3
    { &hal_ll_uart_regs[ hal_ll_uart_module_num(UART_MODULE_3) ], hal_ll_uart_module_num(UART_MODULE_3),
    { HAL_LL_PIN_NC, HAL_LL_UART_TXIF_BIT, HAL_LL_PIN_NC, HAL_LL_UART_RXIF_BIT },
    { 115200, 0 }, HAL_LL_UART_PARITY_DEFAULT, HAL_LL_UART_STOP_BITS_DEFAULT, HAL_LL_UART_DATA_BITS_DEFAULT },
    #endif

    { &hal_ll_uart_regs[ hal_ll_uart_module_num(UART_MODULE_COUNT) ], HAL_LL_MODULE_ERROR,
    { HAL_LL_PIN_NC, 0, HAL_LL_PIN_NC, 0 }, { 0, 0 }, HAL_LL_MODULE_ERROR, HAL_LL_MODULE_ERROR, HAL_LL_MODULE_ERROR }
};

// ---------------------------------------------- PRIVATE FUNCTION DECLARATIONS
/**
  * @brief Check if pins are adequate.
  *
  * Checks tx and rx pins the user has passed with pre-defined
  * pins in tx and rx maps. Take into consideration that module
  * index numbers have to be the same for both pins.
  *
  * @param[in] tx_pin - TX pre-defined pin name.
  * @param[in] rx_pin - RX pre-defined pin name.
  * @param[in] *index_list - Array containing pin map index numbers.
  * @param[in] *handle_map - Map containing UART HAL low level and Driver handles.
  * @return hal_ll_pin_name_t Module index based on pins.
  *
  * Returns pre-defined module index from pin maps, if pins
  * are adequate.
  */
static hal_ll_pin_name_t hal_ll_uart_check_pins( hal_ll_pin_name_t tx_pin, hal_ll_pin_name_t rx_pin,
                                                 hal_ll_uart_pin_id *index_list, hal_ll_uart_handle_register_t *handle_map );

/**
  * @brief Get local hardware specific map.
  *
  * Checks handle value and returns address of adequate
  * hal_ll_uart_hw_specifics_map array index.
  *
  * @param[in] handle - Object specific context handler.
  * @return hal_ll_uart_hw_specifics_map_t Map address.
  *
  * Returns pre-defined map index address based on handle value,
  * if handle is adequate.
  */
static hal_ll_uart_hw_specifics_map_t *hal_ll_get_specifics( handle_t handle );

/**
  * @brief Enable clock for UART module on hardware level.
  *
  * Initializes UART module clock on hardware level, based on beforehand
  * set configuration and module handler.
  *
  * @param[in] *map - Object specific context handler.
  * @param[in] hal_ll_stat - True(enable clock)/False(disable clock).
  *
  * @return void None.
  */
static void hal_ll_uart_set_module_power( hal_ll_uart_hw_specifics_map_t *map, bool hal_ll_state );

/**
 * @brief Maps new-found module specific values.
 *
 * Maps pin names and PPS values for
 * TX and RX pins.
 *
 * @param[in]  module_index UART HW module index -- 0,1,2...
 * @param[in]  *index_list  Array with TX and RX map index values
 *
 * @return  None
 */
static void hal_ll_uart_map_pins( uint8_t module_index, hal_ll_uart_pin_id *index_list );

/**
  * @brief Sets UART pin alternate function state.
  *
  * Sets adequate value for alternate function settings.
  * This function must be called if UART is to work.
  * Based on value of hal_ll_state, alternate functions can be
  * set or cleared.
  *
  * @param[in] *map - Object specific context handler.
  * @param[in] hal_ll_state - Init/De-init
  *
  * @return void None.
  */
static void hal_ll_uart_alternate_functions_set_state( hal_ll_uart_hw_specifics_map_t *map, bool hal_ll_state );

/**
  * @brief Finds UART module index.
  *
  * Finds UART index(module number) based on
  * handle value.
  *
  * @param[in] *handle - Object specific context handler.
  *
  * @return uint8_t Module number.
  * Returns values from 0 to 9.
  */
static uint8_t hal_ll_uart_find_index( handle_t *handle );

/**
  * @brief Clears UART registers.
  *
  * Clears UART module configuration
  * registers, effectively disabling the module itself.
  * Take into consideration that any IRQ bits
  * are not cleared.
  *
  * @param[in] *hal_ll_hw_reg - UART HW register structure.
  *
  * @return void None.
  */
static void hal_ll_uart_clear_regs( const hal_ll_uart_base_handle_t *hal_ll_hw_reg );

/**
 * @brief Sets desired baud rate on hardware level.
 *
 * Initializes module with specified baud rate value.
 * Take into consideration that if the difference
 * between desired baud rate and actual baud
 * rate the hw was initialized to is greater than
 * 1%, baud rate shall not be set.
 * If this occurs, return value shall be
 * the error percentage.
 *
 * @param[in] *map - Object specific context handler.
 *
 * @return void None.
 */
static void hal_ll_uart_set_baud_bare_metal( hal_ll_uart_hw_specifics_map_t *map );

/**
 * @brief Sets desired data bits.
 *
 * Initializes module on hardware level
 * with specified data bit bit value.
 *
 * @param[in] *map - Object specific context handler.
 *
 * @return void None.
 */
static void hal_ll_uart_set_data_bits_bare_metal( hal_ll_uart_hw_specifics_map_t *map );

/**
 * @brief Sets desired parity.
 *
 * Initializes module on hardware level
 * with specified parity value.
 *
 * @param[in] *map - Object specific context handler.
 *
 * @return void None.
 */
static void hal_ll_uart_set_parity_bare_metal( hal_ll_uart_hw_specifics_map_t *map );

/**
 * @brief Sets desired stop bits.
 *
 * Initializes module on hardware level
 * with specified stop bit value.
 *
 * @param[in] *map - Object specific context handler.
 *
 * @return void None.
 */
static void hal_ll_uart_set_stop_bits_bare_metal( hal_ll_uart_hw_specifics_map_t *map );

/**
 * @brief Sets module TX line state.
 *
 * Enables/disables specific UART module
 * TX pin state
 *
 * @param[in] *hal_ll_hw_reg - UART HW register structure.
 * @param[in] pin_state - true(enable transmitter pin) / false(disable transmitter pin)
 *
 * @return void None.
 */
static void hal_ll_uart_set_transmitter( hal_ll_uart_base_handle_t *hal_ll_hw_reg, hal_ll_uart_state_t pin_state );

/**
 * @brief Sets module RX line state.
 *
 * Enables/disables specific UART module
 * RX pin state
 *
 * @param[in] *hal_ll_hw_reg - UART HW register structure.
 * @param[in] pin_state - true(enable receive pin) / false(disable receive pin)
 *
 * @return void None.
 */
static void hal_ll_uart_set_receiver( hal_ll_uart_base_handle_t *hal_ll_hw_reg, hal_ll_uart_state_t pin_state );

/**
 * @brief Initialize UART module.
 *
 * Enables UART module clogk gate first.
 * Sets pin alternate function state.
 * Initializes specific UART module.
 *
 * @param[in] *map - Object specific context handler.
 *
 * @return void None.
 */
static void hal_ll_uart_init( hal_ll_uart_hw_specifics_map_t *map );

/**
 * @brief Initialize UART module on the hardware level.
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
 * @param[in] *map - Object specific context handler.
 *
 * @return void None.
 */
static void hal_ll_uart_hw_init( hal_ll_uart_hw_specifics_map_t *map );
// ------------------------------------------------ PUBLIC FUNCTION DEFINITIONS
hal_ll_err_t hal_ll_uart_register_handle( hal_ll_pin_name_t tx_pin, hal_ll_pin_name_t rx_pin,
                                          hal_ll_uart_handle_register_t *handle_map, uint8_t *hal_module_id ) {
    hal_ll_uart_pin_id index_list[UART_MODULE_COUNT] = { HAL_LL_PIN_NC, HAL_LL_PIN_NC };
    uint8_t pin_check_result;

    // Check if pins are valid
    if ( HAL_LL_PIN_NC == ( pin_check_result = hal_ll_uart_check_pins( tx_pin, rx_pin, &index_list, handle_map ) ) ) {
        return HAL_LL_UART_WRONG_PINS;
    }

    if ( (hal_ll_uart_hw_specifics_map[pin_check_result].pins.tx_pin.pin_name != tx_pin) ||
         (hal_ll_uart_hw_specifics_map[pin_check_result].pins.rx_pin.pin_name != rx_pin) ) {
            hal_ll_uart_alternate_functions_set_state( &hal_ll_uart_hw_specifics_map[ pin_check_result ], false );

            hal_ll_uart_map_pins( pin_check_result, &index_list );

            hal_ll_uart_alternate_functions_set_state( &hal_ll_uart_hw_specifics_map[ pin_check_result ], true );

            handle_map[pin_check_result]->init_ll_state = false;
    }

    *hal_module_id = pin_check_result;

    hal_ll_module_state[pin_check_result].hal_ll_uart_handle = (handle_t *)&hal_ll_uart_hw_specifics_map[pin_check_result].base;

    handle_map[pin_check_result]->hal_ll_uart_handle = (handle_t *)&hal_ll_module_state[pin_check_result].hal_ll_uart_handle;

    return HAL_LL_UART_SUCCESS;
}

hal_ll_err_t hal_ll_module_configure_uart( handle_t *handle ) {
    hal_ll_uart_hw_specifics_map_local = hal_ll_get_specifics( hal_ll_uart_get_module_state_address );
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

    //------------------------------------------------
    /// @note: AVR microcontrollers do not utilize
    // half stop bit and one and a half bit.
    //------------------------------------------------
    if ( ( HAL_LL_UART_STOP_BITS_HALF == stop_bit ) || ( HAL_LL_UART_STOP_BITS_ONE_AND_A_HALF == stop_bit ) ) {
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

    low_level_handle->init_ll_state = false;

    hal_ll_uart_hw_specifics_map_local->data_bit = data_bit;

    hal_ll_uart_init( hal_ll_uart_hw_specifics_map_local );

    low_level_handle->init_ll_state = true;

    return HAL_LL_UART_SUCCESS;
}

void hal_ll_uart_close( handle_t *handle ) {
    low_level_handle = hal_ll_uart_get_handle;
    hal_ll_uart_hw_specifics_map_local = hal_ll_get_specifics( hal_ll_uart_get_module_state_address );

    if( NULL != low_level_handle->hal_ll_uart_handle ) {
        #if HAL_LL_POWER_REDUCTION
        hal_ll_uart_set_module_power( hal_ll_uart_hw_specifics_map_local, true );
        #endif

        hal_ll_uart_alternate_functions_set_state( hal_ll_uart_hw_specifics_map_local, false );

        hal_ll_uart_irq_disable( handle, HAL_LL_UART_IRQ_RX );
        hal_ll_uart_irq_disable( handle, HAL_LL_UART_IRQ_TX );

        hal_ll_uart_clear_regs( hal_ll_uart_hw_specifics_map_local->base );

        // Power-down appropriate UART module via Power Reduction Register (if available).
        #if HAL_LL_POWER_REDUCTION
        hal_ll_uart_set_module_power( hal_ll_uart_hw_specifics_map_local, false );
        #endif

        hal_ll_uart_hw_specifics_map_local->pins.tx_pin.pin_name = HAL_LL_PIN_NC;
        hal_ll_uart_hw_specifics_map_local->pins.rx_pin.pin_name = HAL_LL_PIN_NC;

        hal_ll_uart_hw_specifics_map_local->baud_rate.baud = 115200UL;
        hal_ll_uart_hw_specifics_map_local->baud_rate.real_baud = 0;

        irq_handler = NULL;
        objects[ hal_ll_uart_find_index( handle ) ] = NULL;

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
    hal_ll_uart_hw_specifics_map_local = hal_ll_get_specifics(hal_ll_uart_get_module_state_address);

    switch ( irq ) {
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
}

void hal_ll_uart_irq_disable( handle_t *handle, hal_ll_uart_irq_t irq ) {
    hal_ll_uart_hw_specifics_map_local = hal_ll_get_specifics(hal_ll_uart_get_module_state_address);

    switch ( irq ) {
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

    if ( ( check_reg_bit( hal_ll_uart_regs[ hal_ll_uart_hw_specifics_map_local->module_index ].uart_ucsra_reg_addr, HAL_LL_UART_TXIF_BIT ) ) &&
         ( check_reg_bit( hal_ll_uart_regs[ hal_ll_uart_hw_specifics_map_local->module_index ].uart_ucsra_reg_addr, HAL_LL_UART_RXIF_BIT ) ) ) {
        switch ( hal_ll_uart_hw_specifics_map_local->module_index ) {
            #ifdef UART_MODULE_0
            case hal_ll_uart_module_num(UART_MODULE_0):
                hal_ll_core_disable_irq( HAL_LL_USART0_RX_IVT_ADDRESS );
                break;
            #endif
            #ifdef UART_MODULE_1
            case hal_ll_uart_module_num(UART_MODULE_1):
                hal_ll_core_disable_irq( HAL_LL_USART1_RX_IVT_ADDRESS );
                break;
            #endif
            #ifdef UART_MODULE_2
            case hal_ll_uart_module_num(UART_MODULE_2):
                hal_ll_core_disable_irq( HAL_LL_USART2_RX_IVT_ADDRESS );
                break;
            #endif
            #ifdef UART_MODULE_3
            case hal_ll_uart_module_num(UART_MODULE_3):
                hal_ll_core_disable_irq( HAL_LL_USART3_RX_IVT_ADDRESS );
                break;
            #endif

            default:
                break;
        }
    }
}

void hal_ll_uart_write( handle_t *handle, uint8_t wr_data ) {
    const hal_ll_uart_base_handle_t *hal_ll_hw_reg = hal_ll_uart_get_base_handle;
    write_reg( hal_ll_hw_reg->uart_udr_reg_addr, wr_data );
}

void hal_ll_uart_write_polling( handle_t *handle, uint8_t wr_data ) {
    // TODO
}

uint8_t hal_ll_uart_read( handle_t *handle ) {
    const hal_ll_uart_base_handle_t *hal_ll_hw_reg = hal_ll_uart_get_base_handle;
    return ( read_reg( hal_ll_hw_reg->uart_udr_reg_addr ));
}

uint8_t hal_ll_uart_read_polling( handle_t *handle ) {
    return 1; // TODO
}
// ------------------------------------------------------------- DEFAULT EXCEPTION HANDLERS
/*!< @brief Link handler from HAL layer */
void hal_uart_irq_handler(handle_t obj, hal_ll_uart_irq_t event);

/*!< @brief Instruct the linker which functions can be called indirectly from the "hal_uart_irq_handler" function. */
#pragma funcall UART_RX_IRQHandler, UART_TX_IRQHandler, UART1_RX_IRQHandler, UART1_TX_IRQHandler, \
                UART2_RX_IRQHandler, UART2_TX_IRQHandler, UART3_RX_IRQHandler, UART3_TX_IRQHandler hal_uart_irq_handler

#if defined (UART_MODULE_0)
void UART_RX_IRQHandler(void) MIKROC_IV(UART0_RX_INTERRUPT_ADDRESS_VECTOR) {
    if( hal_ll_uart_get_status_flags( hal_ll_uart_module_num(UART_MODULE_0) ) & ( 1 << HAL_LL_UART_RXIF_BIT ) ) {
        if( 0 != ( __HAL_LL_UART_GET_IT_SOURCE( hal_ll_uart_module_num(UART_MODULE_0), HAL_LL_UART_RXIF_BIT ) ) ) {
            irq_handler( objects[ hal_ll_uart_module_num(UART_MODULE_0) ], HAL_LL_UART_IRQ_RX );
        }
    }
}

void UART_TX_IRQHandler(void) MIKROC_IV(UART0_TX_INTERRUPT_ADDRESS_VECTOR) {
    if( 0 != ( __HAL_LL_UART_GET_IT_SOURCE( hal_ll_uart_module_num(UART_MODULE_0), HAL_LL_UART_TXIF_BIT ) ) ) {
        irq_handler( objects[ hal_ll_uart_module_num(UART_MODULE_0) ], HAL_LL_UART_IRQ_TX );
    }
}
#endif

#if defined (UART_MODULE_1)
void UART1_RX_IRQHandler(void) MIKROC_IV(UART1_RX_INTERRUPT_ADDRESS_VECTOR) {
    if( hal_ll_uart_get_status_flags( hal_ll_uart_module_num(UART_MODULE_1) ) & ( 1 << HAL_LL_UART_RXIF_BIT ) ) {
        if( 0 != ( __HAL_LL_UART_GET_IT_SOURCE( hal_ll_uart_module_num(UART_MODULE_1), HAL_LL_UART_RXIF_BIT ) ) ) {
            irq_handler( objects[ hal_ll_uart_module_num(UART_MODULE_1) ], HAL_LL_UART_IRQ_RX );
        }
    }
}

void UART1_TX_IRQHandler(void) MIKROC_IV(UART1_TX_INTERRUPT_ADDRESS_VECTOR) {
    if( 0 != ( __HAL_LL_UART_GET_IT_SOURCE( hal_ll_uart_module_num(UART_MODULE_1), HAL_LL_UART_TXIF_BIT ) ) ) {
        irq_handler( objects[ hal_ll_uart_module_num(UART_MODULE_1) ], HAL_LL_UART_IRQ_TX );
    }
}
#endif

#if defined (UART_MODULE_2)
void UART2_RX_IRQHandler(void) MIKROC_IV(UART2_RX_INTERRUPT_ADDRESS_VECTOR) {
    if( hal_ll_uart_get_status_flags( hal_ll_uart_module_num(UART_MODULE_2) ) & ( 1 << HAL_LL_UART_RXIF_BIT ) ) {
        if( 0 != ( __HAL_LL_UART_GET_IT_SOURCE( hal_ll_uart_module_num(UART_MODULE_2), HAL_LL_UART_RXIF_BIT ) ) ) {
            irq_handler( objects[ hal_ll_uart_module_num(UART_MODULE_2) ], HAL_LL_UART_IRQ_RX );
        }
    }
}

void UART2_TX_IRQHandler(void) MIKROC_IV(UART2_TX_INTERRUPT_ADDRESS_VECTOR) {
    if( 0 != ( __HAL_LL_UART_GET_IT_SOURCE( hal_ll_uart_module_num(UART_MODULE_2), HAL_LL_UART_TXIF_BIT ) ) ) {
        irq_handler( objects[ hal_ll_uart_module_num(UART_MODULE_2) ], HAL_LL_UART_IRQ_TX );
    }
}
#endif

#if defined (UART_MODULE_3)
void UART3_RX_IRQHandler(void) MIKROC_IV(UART3_RX_INTERRUPT_ADDRESS_VECTOR) {
    if( hal_ll_uart_get_status_flags( hal_ll_uart_module_num(UART_MODULE_3) ) & ( 1 << HAL_LL_UART_RXIF_BIT ) ) {
        if( 0 != ( __HAL_LL_UART_GET_IT_SOURCE( hal_ll_uart_module_num(UART_MODULE_3), HAL_LL_UART_RXIF_BIT ) ) ) {
            irq_handler( objects[ hal_ll_uart_module_num(UART_MODULE_3) ], HAL_LL_UART_IRQ_RX );
        }
    }
}

void UART3_TX_IRQHandler(void) MIKROC_IV(UART3_TX_INTERRUPT_ADDRESS_VECTOR) {
    if( 0 != ( __HAL_LL_UART_GET_IT_SOURCE( hal_ll_uart_module_num(UART_MODULE_3), HAL_LL_UART_TXIF_BIT ) ) ) {
        irq_handler( objects[ hal_ll_uart_module_num(UART_MODULE_3) ], HAL_LL_UART_IRQ_TX );
    }
}
#endif

// ----------------------------------------------- PRIVATE FUNCTION DEFINITIONS
static uint8_t hal_ll_uart_find_index( handle_t *handle ) {
    hal_ll_uart_hw_specifics_map_local = hal_ll_get_specifics(hal_ll_uart_get_module_state_address);

    if( hal_ll_uart_hw_specifics_map_local->base->uart_udr_reg_addr != HAL_LL_MODULE_ERROR ) {
        return hal_ll_uart_hw_specifics_map_local->module_index;
    } else {
        return NULL;
    }
}

static hal_ll_pin_name_t hal_ll_uart_check_pins( hal_ll_pin_name_t tx_pin, hal_ll_pin_name_t rx_pin,
                                                 hal_ll_uart_pin_id *index_list, hal_ll_uart_handle_register_t *handle_map ) {
    static const uint8_t tx_map_size = ( sizeof( hal_ll_uart_tx_map ) / sizeof( hal_ll_uart_pin_map_t ) );
    static const uint8_t rx_map_size = ( sizeof( hal_ll_uart_rx_map ) / sizeof( hal_ll_uart_pin_map_t ) );
    uint8_t hal_ll_module_id = 0;
    uint8_t index_counter = 0;
    uint8_t tx_index;
    uint8_t rx_index;

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
                        index_list[hal_ll_module_id]->pin_tx = tx_index;
                        index_list[hal_ll_module_id]->pin_rx = rx_index;

                        // Check if module is taken
                        if ( NULL == handle_map[hal_ll_module_id]->hal_drv_uart_handle ) {
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
    static uint8_t hal_ll_module_error = hal_ll_module_count;

    while( hal_ll_module_count-- ) {
        if (hal_ll_uart_get_base_from_hal_handle == hal_ll_uart_hw_specifics_map[hal_ll_module_count].base) {
            return &hal_ll_uart_hw_specifics_map[hal_ll_module_count];
        }
    }

    return &hal_ll_uart_hw_specifics_map[hal_ll_module_error];
}

static void hal_ll_uart_map_pins( uint8_t module_index, hal_ll_uart_pin_id *index_list ) {
    // Map new pins.
    hal_ll_uart_hw_specifics_map[module_index].pins.tx_pin.pin_name = hal_ll_uart_tx_map[ index_list[module_index]->pin_tx ].pin;
    hal_ll_uart_hw_specifics_map[module_index].pins.rx_pin.pin_name = hal_ll_uart_rx_map[ index_list[module_index]->pin_rx ].pin;
}

static void hal_ll_uart_alternate_functions_set_state( hal_ll_uart_hw_specifics_map_t *map, bool hal_ll_state ) {
    hal_ll_gpio_pin_t local_pin;
    if ( ( HAL_LL_PIN_NC != map->pins.tx_pin.pin_name ) && ( HAL_LL_PIN_NC != map->pins.rx_pin.pin_name ) ) {
        if (hal_ll_state) {
            hal_ll_gpio_configure_pin( &local_pin, map->pins.tx_pin.pin_name, HAL_LL_GPIO_DIGITAL_OUTPUT );
            hal_ll_gpio_configure_pin( &local_pin, map->pins.rx_pin.pin_name, HAL_LL_GPIO_DIGITAL_INPUT );
        } else {
            hal_ll_gpio_configure_pin( &local_pin, map->pins.tx_pin.pin_name, HAL_LL_GPIO_DIGITAL_INPUT );
            hal_ll_gpio_configure_pin( &local_pin, map->pins.rx_pin.pin_name, HAL_LL_GPIO_DIGITAL_INPUT );
        }
    }
}

static void hal_ll_uart_set_module_power( hal_ll_uart_hw_specifics_map_t *map, bool hal_ll_state ) {
    switch ( map->module_index ) {
        #ifdef UART_MODULE_0
        #ifdef HAL_LL_PRR0_REG_ADDRESS
        case hal_ll_uart_module_num(UART_MODULE_0):
            ( hal_ll_state == true )?(clear_reg_bit( HAL_LL_PRR0_REG_ADDRESS, HAL_LL_PRR_PRUSART0_BIT )):(set_reg_bit( HAL_LL_PRR0_REG_ADDRESS, HAL_LL_PRR_PRUSART0_BIT ));
            break;
        #endif
        #endif
        #ifdef UART_MODULE_3
        #ifdef HAL_LL_PRR1_REG_ADDRESS
        case hal_ll_uart_module_num(UART_MODULE_3):
            ( hal_ll_state == true )?(clear_reg_bit( HAL_LL_PRR1_REG_ADDRESS, HAL_LL_PRR_PRUSART3_BIT )):(set_reg_bit( HAL_LL_PRR1_REG_ADDRESS, HAL_LL_PRR_PRUSART3_BIT ));
            break;
        #endif
        #endif

        default:
            break;
    }
}

static void hal_ll_uart_set_baud_bare_metal(hal_ll_uart_hw_specifics_map_t *map) {
    const hal_ll_uart_base_handle_t *hal_ll_hw_reg = hal_ll_uart_get_base_struct(map->base);

    float baud_rate_prescaler_remainder = 0.0;
    uint16_t baud_rate_prescaler_int = 0;
    float baud_rate_prescaler_raw = 0.0;
    float baud_rate_calculated = 0.0;
    float abs_res = 0.0;
    float err = 0.0;

    float divider = HAL_LL_UART_ASYNCHRONOUS_MODE_CLOCK_DIVIDER;

    // Calculate baud rate prescaler value.
    baud_rate_prescaler_raw = ( _fosc / ( divider * map->baud_rate.baud ) ) - 1.0;

    // Get the integer part of the baud rate prescaler.
    baud_rate_prescaler_int = baud_rate_prescaler_raw;

    // Get the remainder part of the baud rate prescaler.
    baud_rate_prescaler_remainder = baud_rate_prescaler_raw - (float)baud_rate_prescaler_int;

    // Apply "floor" or "ceiling" logic.
    if ( HAL_LL_UART_FLOOR_OR_CEILING_MASK < baud_rate_prescaler_remainder ) {
        ++baud_rate_prescaler_int;
    }

    baud_rate_calculated = ( _fosc / ( divider * ( baud_rate_prescaler_int + 1 )));

    abs_res = (( baud_rate_calculated / map->baud_rate.baud ) - 1.0 );
    abs_res = ( abs_res < 0 ) ? abs_res * (-1.0) : abs_res;
    err = (float)( abs_res * 100 );

    if( err > (float)2.5 ) {
        divider = HAL_LL_UART_ASYNCHRONOUS_MODE_CLOCK_DIVIDER_U2Xn;

        // Set U2Xn bit to double transfer rate.
        set_reg_bit( hal_ll_hw_reg->uart_ucsra_reg_addr, HAL_LL_UART_DOUBLE_SPEED );

        // Calculate baud rate prescaler value.
        baud_rate_prescaler_raw = ( _fosc / ( divider * map->baud_rate.baud ) ) - 1.0;

        // Get the integer part of the baud rate prescaler.
        baud_rate_prescaler_int = baud_rate_prescaler_raw;

        // Get the remainder part of the baud rate prescaler.
        baud_rate_prescaler_remainder = baud_rate_prescaler_raw - (float)baud_rate_prescaler_int;

        // Apply "floor" or "ceiling" logic.
        if ( HAL_LL_UART_FLOOR_OR_CEILING_MASK < baud_rate_prescaler_remainder ) {
            ++baud_rate_prescaler_int;
        }
    }

    // Memorize actual baud rate.
    map->baud_rate.real_baud = ( _fosc / ( divider * ( baud_rate_prescaler_int + 1 ) ) );
    if( hal_ll_uart_get_baud_error( map->baud_rate.real_baud, map->baud_rate.baud ) ) {
        // Change to error baud if error greater than 1%.
        map->baud_rate.real_baud = hal_ll_uart_get_baud_error( map->baud_rate.real_baud, map->baud_rate.baud );
    } else {
        // If prescaler value is greater than 255, populate HIGH register in first place.
        if ( HAL_LL_UART_BAUD_RATE_REG_LOW_LENGTH < baud_rate_prescaler_int ) {
            #ifdef REGISTERS_WITH_SHARED_IO_LOCATION
            write_reg( hal_ll_hw_reg->uart_ubrrh_reg_addr, ( ( ( baud_rate_prescaler_int & HAL_LL_UART_THIRD_NIBBLE_MASK ) >> 8 ) &
            HAL_LL_UART_BAUD_RATE_REGISTER_SELECTED ) );
            #else
            write_reg( hal_ll_hw_reg->uart_ubrrh_reg_addr, ( ( baud_rate_prescaler_int & HAL_LL_UART_THIRD_NIBBLE_MASK ) >> 8 ) );
            #endif
        }

        // Populate LOW register with lower eight bits of baud rate value.
        write_reg( hal_ll_hw_reg->uart_ubrrl_reg_addr, (uint8_t)baud_rate_prescaler_int );
    }
}

static void hal_ll_uart_set_stop_bits_bare_metal( hal_ll_uart_hw_specifics_map_t *map ) {
    const hal_ll_uart_base_handle_t *hal_ll_hw_reg = hal_ll_uart_get_base_struct(map->base);

    switch ( map->stop_bit ) {
        case HAL_LL_UART_STOP_BITS_ONE:
            clear_reg_bit( hal_ll_hw_reg->uart_ucsrc_reg_addr, HAL_LL_UART_STOP_BIT );
            break;
        case HAL_LL_UART_STOP_BITS_TWO:
            #ifdef REGISTERS_WITH_SHARED_IO_LOCATION
            *(uint8_t *)hal_ll_hw_reg->uart_ucsrc_reg_addr &= ( HAL_LL_UART_CONTROL_AND_STATUS_REGISTER_SELECTED |
            HAL_LL_UART_STOP_BITS_TWO_MASK );
            #else
            set_reg_bit( hal_ll_hw_reg->uart_ucsrc_reg_addr, HAL_LL_UART_STOP_BIT );
            #endif
            break;

        default:
            /**
             * @note: AVR microcontrollers do not utilize
             * half stop bit and one and a half stop bit.
             */
            break;
    }
}

static void hal_ll_uart_set_data_bits_bare_metal( hal_ll_uart_hw_specifics_map_t *map ) {
    const hal_ll_uart_base_handle_t *hal_ll_hw_reg = hal_ll_uart_get_base_struct(map->base);

    switch ( map->data_bit ) {
        case HAL_LL_UART_DATA_BITS_7:
            #ifdef REGISTERS_WITH_SHARED_IO_LOCATION
            write_reg( hal_ll_hw_reg->uart_ucsrc_reg_addr, HAL_LL_UART_CONTROL_AND_STATUS_REGISTER_SELECTED |
            ( HAL_LL_UART_DATA_BITS_7_MASK << HAL_LL_UART_DATA_BITS_MASK_USCRC_REGISTER ) );
            #else
            set_reg_bit( hal_ll_hw_reg->uart_ucsrc_reg_addr, HAL_LL_UART_DATA_BITS_7_MASK << HAL_LL_UART_DATA_BITS_MASK_USCRC_REGISTER );
            clear_reg_bit( hal_ll_hw_reg->uart_ucsrb_reg_addr, HAL_LL_UART_DATA_BITS_9_USCRB_REGISTER_BIT );
            #endif
            break;
        case HAL_LL_UART_DATA_BITS_8:
            #ifdef REGISTERS_WITH_SHARED_IO_LOCATION
            write_reg( hal_ll_hw_reg->uart_ucsrc_reg_addr, HAL_LL_UART_CONTROL_AND_STATUS_REGISTER_SELECTED |
            ( HAL_LL_UART_DATA_BITS_8_MASK << HAL_LL_UART_DATA_BITS_MASK_USCRC_REGISTER ) );
            #else
            set_reg_bits( hal_ll_hw_reg->uart_ucsrc_reg_addr, HAL_LL_UART_DATA_BITS_8_MASK << HAL_LL_UART_DATA_BITS_MASK_USCRC_REGISTER );
            clear_reg_bit( hal_ll_hw_reg->uart_ucsrb_reg_addr, HAL_LL_UART_DATA_BITS_9_USCRB_REGISTER_BIT );
            #endif
            break;
        case HAL_LL_UART_DATA_BITS_9:
            #ifdef REGISTERS_WITH_SHARED_IO_LOCATION
            write_reg( hal_ll_hw_reg->uart_ucsrc_reg_addr, HAL_LL_UART_CONTROL_AND_STATUS_REGISTER_SELECTED |
            ( HAL_LL_UART_DATA_BITS_8_MASK << HAL_LL_UART_DATA_BITS_MASK_USCRC_REGISTER ) );
            #else
            set_reg_bits( hal_ll_hw_reg->uart_ucsrc_reg_addr, HAL_LL_UART_DATA_BITS_8_MASK << HAL_LL_UART_DATA_BITS_MASK_USCRC_REGISTER );
            #endif
            set_reg_bit( hal_ll_hw_reg->uart_ucsrb_reg_addr, HAL_LL_UART_DATA_BITS_9_USCRB_REGISTER_BIT );
            break;

        default:
            break;
    }
}

static void hal_ll_uart_set_parity_bare_metal( hal_ll_uart_hw_specifics_map_t *map ) {
const hal_ll_uart_base_handle_t *hal_ll_hw_reg = hal_ll_uart_get_base_struct( map->base );

    switch( map->parity ) {
        case HAL_LL_UART_PARITY_NONE:
            #ifdef REGISTERS_WITH_SHARED_IO_LOCATION
            *(uint8_t *)hal_ll_hw_reg->uart_ucsrc_reg_addr &= HAL_LL_UART_CONTROL_AND_STATUS_REGISTER_SELECTED |
            HAL_LL_UART_FIRST_NIBBLE_MASK;
            #else
            clear_reg_bits( hal_ll_hw_reg->uart_ucsrc_reg_addr, HAL_LL_UART_PARITY_NONE_MASK << HAL_LL_UART_PARITY_MASK );
            #endif
            break;
        case HAL_LL_UART_PARITY_EVEN:
            #ifdef REGISTERS_WITH_SHARED_IO_LOCATION
            set_reg_bits( hal_ll_hw_reg->uart_ucsrc_reg_addr, HAL_LL_UART_CONTROL_AND_STATUS_REGISTER_SELECTED |
            ( HAL_LL_UART_PARITY_ODD_MASK << HAL_LL_UART_PARITY_MASK ) );
            #else
            set_reg_bits( hal_ll_hw_reg->uart_ucsrc_reg_addr, HAL_LL_UART_PARITY_EVEN_MASK << HAL_LL_UART_PARITY_MASK );
            #endif
            break;
        case HAL_LL_UART_PARITY_ODD:
            #ifdef REGISTERS_WITH_SHARED_IO_LOCATION
            set_reg_bits( hal_ll_hw_reg->uart_ucsrc_reg_addr, HAL_LL_UART_CONTROL_AND_STATUS_REGISTER_SELECTED |
            ( HAL_LL_UART_PARITY_ODD_MASK << HAL_LL_UART_PARITY_MASK ) );
            #else
            set_reg_bits( hal_ll_hw_reg->uart_ucsrc_reg_addr, HAL_LL_UART_PARITY_ODD_MASK << HAL_LL_UART_PARITY_MASK );
            #endif
            break;

        default:
            break;
    }
}

static void hal_ll_uart_set_transmitter( const hal_ll_uart_base_handle_t *hal_ll_hw_reg, hal_ll_uart_state_t pin_state ) {
    switch ( pin_state ) {
        case HAL_LL_UART_DISABLE:
            clear_reg_bit( hal_ll_hw_reg->uart_ucsrb_reg_addr, HAL_LL_UART_TXEN_BIT );
            break;

        case HAL_LL_UART_ENABLE:
            set_reg_bit( hal_ll_hw_reg->uart_ucsrb_reg_addr, HAL_LL_UART_TXEN_BIT );
            break;

        default:
            break;
    }
}

static void hal_ll_uart_set_receiver( const hal_ll_uart_base_handle_t *hal_ll_hw_reg, hal_ll_uart_state_t pin_state ) {
    switch ( pin_state ) {
        case HAL_LL_UART_DISABLE:
            clear_reg_bit( hal_ll_hw_reg->uart_ucsrb_reg_addr, HAL_LL_UART_CREN_BIT );
            break;

        case HAL_LL_UART_ENABLE:
            set_reg_bit( hal_ll_hw_reg->uart_ucsrb_reg_addr, HAL_LL_UART_CREN_BIT );
            break;

        default:
            break;
    }
}

static void hal_ll_uart_clear_regs( const hal_ll_uart_base_handle_t *hal_ll_hw_reg ) {
    clear_reg( hal_ll_hw_reg->uart_ucsrc_reg_addr );
    #ifdef REGISTERS_WITH_SHARED_IO_LOCATION
    write_reg( hal_ll_hw_reg->uart_ucsrc_reg_addr, HAL_LL_UART_CONTROL_AND_STATUS_REGISTER_SELECTED );
    #endif
}

static void hal_ll_uart_hw_init( hal_ll_uart_hw_specifics_map_t *map ) {
    const hal_ll_uart_base_handle_t *hal_ll_hw_reg = hal_ll_uart_get_base_struct( map->base );

    // Clear USART Control and Status register C.
    hal_ll_uart_clear_regs( map->base );

    // Set USART data bits.
    hal_ll_uart_set_data_bits_bare_metal( map );

    // Set USART parity bits.
    hal_ll_uart_set_parity_bare_metal( map );

    // Set USART stop bits.
    hal_ll_uart_set_stop_bits_bare_metal( map );

    // Set USART Baud rate.
    hal_ll_uart_set_baud_bare_metal( map );

    /* In order for UART Transmit interrupt to
     * be triggered, initial dummy data write is
     * required. Writing to the register here is
     * harmless as we have disabled TX/RX pins and the
     * whole UART module in `hal_ll_uart_clear_regs`
     * function.
     */
    write_reg( hal_ll_hw_reg->uart_udr_reg_addr, HAL_LL_UART_TRIGGER_INTERRUPT );

    // Enable Transmitter driver.
    hal_ll_uart_set_transmitter( map->base, HAL_LL_UART_ENABLE );

    // Enable Receiver driver.
    hal_ll_uart_set_receiver( map->base, HAL_LL_UART_ENABLE );
}

static void hal_ll_uart_init( hal_ll_uart_hw_specifics_map_t *map ) {
    /*!< @brief Static, because clock doesn't change during runtime. */
    static const uint32_t hal_ll_clock_value = Get_Fosc_kHz();

    // Power-up appropriate UART module via Power Reduction Register (if available).
    #if HAL_LL_POWER_REDUCTION == true
    hal_ll_uart_set_module_power( map, true );
    #endif

    // Finally, write user-defined settings into hardware registers.
    hal_ll_uart_hw_init( map );

    // Give it some time to stabilize.
    hal_ll_uart_wait_for_sync( hal_ll_clock_value );
}

// ------------------------------------------------------------------------- END
