/****************************************************************************
**
** Copyright (C) 2023 MikroElektronika d.o.o.
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

/*!< @brief Macros defining control register values */
#define HAL_LL_UART_CTRLB_RXEN_BIT        (4)
#define HAL_LL_UART_CTRLB_TXEN_BIT        (3)
#define HAL_LL_UART_CTRLA_RXCINTLVL_SHIFT (4)
#define HAL_LL_UART_CTRLA_TXCINTLVL_SHIFT (2)

/*!< @brief Macros defining interrupt level values. */
#define HAL_LL_UART_INTERRUPT_LEVEL_OFF   (0x0)
#define HAL_LL_UART_INTERRUPT_LEVEL_LO    (0x1)
#define HAL_LL_UART_INTERRUPT_LEVEL_MED   (0x2)
#define HAL_LL_UART_INTERRUPT_LEVEL_HI    (0x3)

/*!< @brief Macros defining USART baud rate values. */
#define HAL_LL_UART_BAUD_RATE_MUL         (16)
#define HAL_LL_UART_BAUD_RATE_MUL_CLK2X   (8)
#define HAL_LL_UART_CTRLB_CLK2X_BIT       (2)

/*!< @brief Macros defining USART Stop bits values. */
#define HAL_LL_UART_SBMODE_SHIFT          (3)
#define HAL_LL_UART_SBMODE_ONE            (0)
#define HAL_LL_UART_SBMODE_TWO            (1)

/*!< @brief Macros defining USART Parity bits values. */
#define HAL_LL_UART_PMODE_SHIFT           (4)
#define HAL_LL_UART_PARITY_NONE           (0)
#define HAL_LL_UART_PARITY_EVEN           (2)
#define HAL_LL_UART_PARITY_ODD            (3)

/*!< @brief Macros defining USART Data bits values. */
#define HAL_LL_UART_CHSIZE_5BIT           (0)
#define HAL_LL_UART_CHSIZE_6BIT           (1)
#define HAL_LL_UART_CHSIZE_7BIT           (2)
#define HAL_LL_UART_CHSIZE_8BIT           (3)
#define HAL_LL_UART_CHSIZE_9BIT           (7)

/*!< @brief Helper macros for triggering UART interrupt. */
#define ASCII_START_OF_TEXT               (2)
#define HAL_LL_UART_TRIGGER_INTERRUPT     (ASCII_START_OF_TEXT)
#define HAL_LL_UART_STATUS_RXCIF_BIT      (7)
#define HAL_LL_UART_STATUS_TXCIF_BIT      (6)
#define HAL_LL_UART_STATUS_DREIF_BIT      (5)

/*!< @brief Helper macros for enabling interrupts. */
#define HAL_LL_PMIC_CTRL_HILVLEN          (0x4)
#define HAL_LL_PMIC_CTRL_MEDLVLEN         (0x2)
#define HAL_LL_PMIC_CTRL_LOLVLEN          (0x1)

/*!< @brief Macro defining USART0 remap bit position. */
#define HAL_LL_USART0_REMAP_BIT           (4)

/*!< @brief Macro defining Power reduction register values. */
#define HAL_LL_PRPn_USART0_MODULE_ENABLE  (4)
#define HAL_LL_PRPn_USART1_MODULE_ENABLE  (5)

/*!< @brief Macro used for calculating actual baud rate value and error value. */
#define HAL_LL_UART_ACCEPTABLE_ERROR (float)1.0
#define hal_ll_uart_get_baud_error( _baud_real,_baud ) ( (float)abs( _baud_real/_baud - 1 ) * 100 )

/*!< @brief Macros used for status register flag check */
#define hal_ll_uart_get_status_flags( module_num ) ( read_reg( hal_ll_uart_regs[ module_num ].status ))

/*!< @brief Macros used for enabling and disabling interrupts */
#define __HAL_LL_UART_ENABLE_IT( _num,_int ) ( set_reg_bits( hal_ll_uart_regs[_num].ctrla, ( HAL_LL_UART_INTERRUPT_LEVEL_HI<<_int )))
#define __HAL_LL_UART_DISABLE_IT( _num,_int ) ( clear_reg_bits( hal_ll_uart_regs[_num].ctrla, ( HAL_LL_UART_INTERRUPT_LEVEL_HI<<_int )))

/*!< @brief Local handle list */
static volatile hal_ll_uart_handle_register_t hal_ll_module_state[UART_MODULE_COUNT] = { (handle_t *)NULL, (handle_t *)NULL, false };

// ------------------------------------------------------------- PRIVATE MACROS
/*!< @brief Helper macro for getting hal_ll_module_state address */
#define hal_ll_uart_get_module_state_address (( hal_ll_uart_handle_register_t *)*handle )
/*!< @brief Helper macro for getting module specific control register structure base address // first register address */
#define hal_ll_uart_get_handle ( hal_ll_uart_handle_register_t * )hal_ll_uart_get_module_state_address->hal_ll_uart_handle
/*!< @brief Helper macro for getting module specific control register structure */
#define hal_ll_uart_get_base_struct(_handle) (( const hal_ll_uart_base_handle_t * )_handle )
/*!< @brief Helper macro for getting module specific base address directly from HAL layer handle */
#define hal_ll_uart_get_base_from_hal_handle (( hal_ll_uart_hw_specifics_map_t * )(( hal_ll_uart_handle_register_t * )\
                                             ((( hal_ll_uart_handle_register_t * )(handle))->hal_ll_uart_handle ))->hal_ll_uart_handle )->base
/*!< @brief Helper macro for getting module specific base address structure directly from HAL layer handle */
#define hal_ll_uart_get_base_handle (( hal_ll_uart_hw_specifics_map_t * )(( hal_ll_uart_get_handle )->hal_ll_uart_handle ))->base

// ------------------------------------------------------------------ TYPEDEFS
/*!< @brief UART HW register structure */
typedef struct {
    hal_ll_base_addr_t dat;
    hal_ll_base_addr_t status;
    hal_ll_base_addr_t ctrla;
    hal_ll_base_addr_t ctrlb;
    hal_ll_base_addr_t ctrlc;
    hal_ll_base_addr_t baudctrla;
    hal_ll_base_addr_t baudctrlb;
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
    bool alternate;
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
    #ifdef UART_MODULE_C0
    { HAL_LL_USARTC0_DATA_REG_ADDRESS, HAL_LL_USARTC0_STATUS_REG_ADDRESS, HAL_LL_USARTC0_CTRLA_REG_ADDRESS, HAL_LL_USARTC0_CTRLB_REG_ADDRESS,
      HAL_LL_USARTC0_CTRLC_REG_ADDRESS, HAL_LL_USARTC0_BAUDCTRLA_REG_ADDRESS, HAL_LL_USARTC0_BAUDCTRLB_REG_ADDRESS },
    #endif
    #ifdef UART_MODULE_C1
    { HAL_LL_USARTC1_DATA_REG_ADDRESS, HAL_LL_USARTC1_STATUS_REG_ADDRESS, HAL_LL_USARTC1_CTRLA_REG_ADDRESS, HAL_LL_USARTC1_CTRLB_REG_ADDRESS,
      HAL_LL_USARTC1_CTRLC_REG_ADDRESS, HAL_LL_USARTC1_BAUDCTRLA_REG_ADDRESS, HAL_LL_USARTC1_BAUDCTRLB_REG_ADDRESS },
    #endif
    #ifdef UART_MODULE_D0
    { HAL_LL_USARTD0_DATA_REG_ADDRESS, HAL_LL_USARTD0_STATUS_REG_ADDRESS, HAL_LL_USARTD0_CTRLA_REG_ADDRESS, HAL_LL_USARTD0_CTRLB_REG_ADDRESS,
      HAL_LL_USARTD0_CTRLC_REG_ADDRESS, HAL_LL_USARTD0_BAUDCTRLA_REG_ADDRESS, HAL_LL_USARTD0_BAUDCTRLB_REG_ADDRESS },
    #endif
    #ifdef UART_MODULE_D1
    { HAL_LL_USARTD1_DATA_REG_ADDRESS, HAL_LL_USARTD1_STATUS_REG_ADDRESS, HAL_LL_USARTD1_CTRLA_REG_ADDRESS, HAL_LL_USARTD1_CTRLB_REG_ADDRESS,
      HAL_LL_USARTD1_CTRLC_REG_ADDRESS, HAL_LL_USARTD1_BAUDCTRLA_REG_ADDRESS, HAL_LL_USARTD1_BAUDCTRLB_REG_ADDRESS },
    #endif
    #ifdef UART_MODULE_E0
    { HAL_LL_USARTE0_DATA_REG_ADDRESS, HAL_LL_USARTE0_STATUS_REG_ADDRESS, HAL_LL_USARTE0_CTRLA_REG_ADDRESS, HAL_LL_USARTE0_CTRLB_REG_ADDRESS,
      HAL_LL_USARTE0_CTRLC_REG_ADDRESS, HAL_LL_USARTE0_BAUDCTRLA_REG_ADDRESS, HAL_LL_USARTE0_BAUDCTRLB_REG_ADDRESS },
    #endif
    #ifdef UART_MODULE_E1
    { HAL_LL_USARTE1_DATA_REG_ADDRESS, HAL_LL_USARTE1_STATUS_REG_ADDRESS, HAL_LL_USARTE1_CTRLA_REG_ADDRESS, HAL_LL_USARTE1_CTRLB_REG_ADDRESS,
      HAL_LL_USARTE1_CTRLC_REG_ADDRESS, HAL_LL_USARTE1_BAUDCTRLA_REG_ADDRESS, HAL_LL_USARTE1_BAUDCTRLB_REG_ADDRESS },
    #endif
    #ifdef UART_MODULE_F0
    { HAL_LL_USARTF0_DATA_REG_ADDRESS, HAL_LL_USARTF0_STATUS_REG_ADDRESS, HAL_LL_USARTF0_CTRLA_REG_ADDRESS, HAL_LL_USARTF0_CTRLB_REG_ADDRESS,
      HAL_LL_USARTF0_CTRLC_REG_ADDRESS, HAL_LL_USARTF0_BAUDCTRLA_REG_ADDRESS, HAL_LL_USARTF0_BAUDCTRLB_REG_ADDRESS },
    #endif
    #ifdef UART_MODULE_F1
    { HAL_LL_USARTF1_DATA_REG_ADDRESS, HAL_LL_USARTF1_STATUS_REG_ADDRESS, HAL_LL_USARTF1_CTRLA_REG_ADDRESS, HAL_LL_USARTF1_CTRLB_REG_ADDRESS,
      HAL_LL_USARTF1_CTRLC_REG_ADDRESS, HAL_LL_USARTF1_BAUDCTRLA_REG_ADDRESS, HAL_LL_USARTF1_BAUDCTRLB_REG_ADDRESS },
    #endif

    { HAL_LL_MODULE_ERROR, HAL_LL_MODULE_ERROR, HAL_LL_MODULE_ERROR, HAL_LL_MODULE_ERROR, HAL_LL_MODULE_ERROR, HAL_LL_MODULE_ERROR, HAL_LL_MODULE_ERROR }
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
    #ifdef UART_MODULE_C0
    { &hal_ll_uart_regs[hal_ll_uart_module_num( UART_MODULE_C0 )], hal_ll_uart_module_num( UART_MODULE_C0 ),
      { HAL_LL_PIN_NC, HAL_LL_UART_STATUS_TXCIF_BIT, HAL_LL_PIN_NC, HAL_LL_UART_STATUS_RXCIF_BIT },
      {115200, 0}, HAL_LL_UART_PARITY_DEFAULT, HAL_LL_UART_STOP_BITS_DEFAULT, HAL_LL_UART_DATA_BITS_DEFAULT, false },
    #endif
    #ifdef UART_MODULE_C1
    { &hal_ll_uart_regs[hal_ll_uart_module_num( UART_MODULE_C1 )], hal_ll_uart_module_num( UART_MODULE_C1 ),
      { HAL_LL_PIN_NC, HAL_LL_UART_STATUS_TXCIF_BIT, HAL_LL_PIN_NC, HAL_LL_UART_STATUS_RXCIF_BIT },
      {115200, 0}, HAL_LL_UART_PARITY_DEFAULT, HAL_LL_UART_STOP_BITS_DEFAULT, HAL_LL_UART_DATA_BITS_DEFAULT, false },
    #endif
    #ifdef UART_MODULE_D0
    { &hal_ll_uart_regs[hal_ll_uart_module_num( UART_MODULE_D0 )], hal_ll_uart_module_num( UART_MODULE_D0 ),
      { HAL_LL_PIN_NC, HAL_LL_UART_STATUS_TXCIF_BIT, HAL_LL_PIN_NC, HAL_LL_UART_STATUS_RXCIF_BIT },
      {115200, 0}, HAL_LL_UART_PARITY_DEFAULT, HAL_LL_UART_STOP_BITS_DEFAULT, HAL_LL_UART_DATA_BITS_DEFAULT, false },
    #endif
    #ifdef UART_MODULE_D1
    { &hal_ll_uart_regs[hal_ll_uart_module_num( UART_MODULE_D1 )], hal_ll_uart_module_num( UART_MODULE_D1 ),
      { HAL_LL_PIN_NC, HAL_LL_UART_STATUS_TXCIF_BIT, HAL_LL_PIN_NC, HAL_LL_UART_STATUS_RXCIF_BIT },
      {115200, 0}, HAL_LL_UART_PARITY_DEFAULT, HAL_LL_UART_STOP_BITS_DEFAULT, HAL_LL_UART_DATA_BITS_DEFAULT, false },
    #endif
    #ifdef UART_MODULE_E0
    { &hal_ll_uart_regs[hal_ll_uart_module_num( UART_MODULE_E0 )], hal_ll_uart_module_num( UART_MODULE_E0 ),
      { HAL_LL_PIN_NC, HAL_LL_UART_STATUS_TXCIF_BIT, HAL_LL_PIN_NC, HAL_LL_UART_STATUS_RXCIF_BIT },
      {115200, 0}, HAL_LL_UART_PARITY_DEFAULT, HAL_LL_UART_STOP_BITS_DEFAULT, HAL_LL_UART_DATA_BITS_DEFAULT, false },
    #endif
    #ifdef UART_MODULE_E1
    { &hal_ll_uart_regs[hal_ll_uart_module_num( UART_MODULE_E1 )], hal_ll_uart_module_num( UART_MODULE_E1 ),
      { HAL_LL_PIN_NC, HAL_LL_UART_STATUS_TXCIF_BIT, HAL_LL_PIN_NC, HAL_LL_UART_STATUS_RXCIF_BIT },
      {115200, 0}, HAL_LL_UART_PARITY_DEFAULT, HAL_LL_UART_STOP_BITS_DEFAULT, HAL_LL_UART_DATA_BITS_DEFAULT, false },
    #endif
    #ifdef UART_MODULE_F0
    { &hal_ll_uart_regs[hal_ll_uart_module_num( UART_MODULE_F0 )], hal_ll_uart_module_num( UART_MODULE_F0 ),
      { HAL_LL_PIN_NC, HAL_LL_UART_STATUS_TXCIF_BIT, HAL_LL_PIN_NC, HAL_LL_UART_STATUS_RXCIF_BIT },
      {115200, 0}, HAL_LL_UART_PARITY_DEFAULT, HAL_LL_UART_STOP_BITS_DEFAULT, HAL_LL_UART_DATA_BITS_DEFAULT, false },
    #endif
    #ifdef UART_MODULE_F1
    { &hal_ll_uart_regs[hal_ll_uart_module_num( UART_MODULE_F1 )], hal_ll_uart_module_num( UART_MODULE_F1 ),
      { HAL_LL_PIN_NC, HAL_LL_UART_STATUS_TXCIF_BIT, HAL_LL_PIN_NC, HAL_LL_UART_STATUS_RXCIF_BIT },
      {115200, 0}, HAL_LL_UART_PARITY_DEFAULT, HAL_LL_UART_STOP_BITS_DEFAULT, HAL_LL_UART_DATA_BITS_DEFAULT, false },
    #endif

    { &hal_ll_uart_regs[hal_ll_uart_module_num( UART_MODULE_COUNT)], HAL_LL_MODULE_ERROR,
      { HAL_LL_PIN_NC, 0, HAL_LL_PIN_NC, 0 },
      {0, 0}, HAL_LL_MODULE_ERROR, HAL_LL_MODULE_ERROR, HAL_LL_MODULE_ERROR, false }
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
  * @param[in]  *index_list - Array containing pin map index numbers.
  * @param[in]  *handle_map - Map containing UART HAL low level and Driver handles.
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
static hal_ll_uart_hw_specifics_map_t *hal_ll_get_specifics( handle_t handle );

/**
  * @brief Enable or disable clock for UART module on hardware level.
  *
  * Initializes UART module clock on hardware level, based on beforehand
  * set configuration and module handler.
  *
  * @param[in] module_num - Number of UART module.
  * @param[in] hal_ll_stat - True(enable clock)/False(disable clock).
  *
  * @return void None.
  */
static void hal_ll_uart_power_reduction_enable( uint8_t module_num, bool hal_ll_state );

/**
 * @brief  Maps new-found module specific values.
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
    hal_ll_uart_pin_id index_list[UART_MODULE_COUNT] = { HAL_LL_PIN_NC, HAL_LL_PIN_NC };
    uint8_t pin_check_result;

    // Check if pins are valid
    if ( HAL_LL_PIN_NC == ( pin_check_result = hal_ll_uart_check_pins( tx_pin, rx_pin, &index_list, handle_map ) ) ) {
        return HAL_LL_UART_WRONG_PINS;
    }

    if ( ( hal_ll_uart_hw_specifics_map[pin_check_result].pins.tx_pin.pin_name != tx_pin ) ||
         ( hal_ll_uart_hw_specifics_map[pin_check_result].pins.rx_pin.pin_name != rx_pin ) ) {
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
    // @note: AVR microcontrollers do not utilize
    // half stop bit and one and a half bit.
    //------------------------------------------------
    if (( HAL_LL_UART_STOP_BITS_HALF == stop_bit ) || ( HAL_LL_UART_STOP_BITS_ONE_AND_A_HALF == stop_bit )) {
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
        hal_ll_uart_power_reduction_enable( hal_ll_uart_hw_specifics_map_local->module_index, false );
        #endif

        hal_ll_uart_alternate_functions_set_state( hal_ll_uart_hw_specifics_map_local, false );

        hal_ll_uart_irq_disable( handle, HAL_LL_UART_IRQ_RX );
        hal_ll_uart_irq_disable( handle, HAL_LL_UART_IRQ_TX );

        hal_ll_uart_clear_regs( hal_ll_uart_hw_specifics_map_local->base );

        // Power-down appropriate UART module via Power Reduction Register (if available).
        #if HAL_LL_POWER_REDUCTION
        hal_ll_uart_power_reduction_enable( hal_ll_uart_hw_specifics_map_local->module_index, true );
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
    hal_ll_uart_hw_specifics_map_local = hal_ll_get_specifics( hal_ll_uart_get_module_state_address );

    switch ( irq ) {
        case HAL_LL_UART_IRQ_RX:
            __HAL_LL_UART_ENABLE_IT( hal_ll_uart_hw_specifics_map_local->module_index, HAL_LL_UART_CTRLA_RXCINTLVL_SHIFT );
            break;

        case HAL_LL_UART_IRQ_TX:
            __HAL_LL_UART_ENABLE_IT( hal_ll_uart_hw_specifics_map_local->module_index, HAL_LL_UART_CTRLA_TXCINTLVL_SHIFT );
            break;

        default:
            break;
    }

}

void hal_ll_uart_irq_disable( handle_t *handle, hal_ll_uart_irq_t irq ) {
    hal_ll_uart_hw_specifics_map_local = hal_ll_get_specifics( hal_ll_uart_get_module_state_address );

    switch ( irq ) {
        case HAL_LL_UART_IRQ_RX:
            __HAL_LL_UART_DISABLE_IT( hal_ll_uart_hw_specifics_map_local->module_index, HAL_LL_UART_CTRLA_RXCINTLVL_SHIFT );
            break;

        case HAL_LL_UART_IRQ_TX:
            __HAL_LL_UART_DISABLE_IT( hal_ll_uart_hw_specifics_map_local->module_index, HAL_LL_UART_CTRLA_TXCINTLVL_SHIFT );
            break;

        default:
            break;
    }
}

void hal_ll_uart_write( handle_t *handle, uint8_t wr_data ) {
    const hal_ll_uart_base_handle_t *hal_ll_hw_reg = hal_ll_uart_get_base_handle;
    write_reg( hal_ll_hw_reg->dat, wr_data );
}

uint8_t hal_ll_uart_read( handle_t *handle ) {
    const hal_ll_uart_base_handle_t *hal_ll_hw_reg = hal_ll_uart_get_base_handle;
    return read_reg( hal_ll_hw_reg->dat );
}

// ------------------------------------------------------------- DEFAULT EXCEPTION HANDLERS
/*!< @brief Link handler from HAL layer */
void hal_uart_irq_handler( handle_t obj, hal_ll_uart_irq_t event );

#if defined ( UART_MODULE_C0 )
void UART0_RX_IRQHandler( void ) MIKROC_IV( UARTC0_RX_INTERRUPT_ADDRESS_VECTOR ) {
    irq_handler( objects[ hal_ll_uart_module_num( UART_MODULE_C0 ) ], HAL_LL_UART_IRQ_RX );
}

void UART0_TX_IRQHandler( void ) MIKROC_IV( UARTC0_TX_INTERRUPT_ADDRESS_VECTOR ) {
    if( hal_ll_uart_get_status_flags( hal_ll_uart_module_num( UART_MODULE_C0 )) & ( 1 <<  HAL_LL_UART_STATUS_DREIF_BIT )) {
        irq_handler( objects[ hal_ll_uart_module_num( UART_MODULE_C0 ) ], HAL_LL_UART_IRQ_TX );
        write_reg( hal_ll_uart_regs[ hal_ll_uart_module_num( UART_MODULE_C0 ) ].status, HAL_LL_UART_STATUS_TXCIF_BIT );
    }
}
#endif

#if defined ( UART_MODULE_C1 )
void UART1_RX_IRQHandler( void ) MIKROC_IV( UARTC1_RX_INTERRUPT_ADDRESS_VECTOR ) {
    irq_handler( objects[ hal_ll_uart_module_num( UART_MODULE_C1 ) ], HAL_LL_UART_IRQ_RX );
}

void UART1_TX_IRQHandler( void ) MIKROC_IV( UARTC1_TX_INTERRUPT_ADDRESS_VECTOR ) {
    if( hal_ll_uart_get_status_flags( hal_ll_uart_module_num( UART_MODULE_C1 )) & ( 1 <<  HAL_LL_UART_STATUS_DREIF_BIT )) {
        irq_handler( objects[ hal_ll_uart_module_num( UART_MODULE_C1 ) ], HAL_LL_UART_IRQ_TX );
        write_reg( hal_ll_uart_regs[ hal_ll_uart_module_num( UART_MODULE_C1 ) ].status, HAL_LL_UART_STATUS_TXCIF_BIT );
    }
}
#endif

#if defined ( UART_MODULE_D0 )
void UART2_RX_IRQHandler( void ) MIKROC_IV( UARTD0_RX_INTERRUPT_ADDRESS_VECTOR ) {
    irq_handler( objects[ hal_ll_uart_module_num( UART_MODULE_D0 ) ], HAL_LL_UART_IRQ_RX );
}

void UART2_TX_IRQHandler( void ) MIKROC_IV( UARTD0_TX_INTERRUPT_ADDRESS_VECTOR ) {
    if( hal_ll_uart_get_status_flags( hal_ll_uart_module_num( UART_MODULE_D0 )) & ( 1 <<  HAL_LL_UART_STATUS_DREIF_BIT )) {
        irq_handler( objects[ hal_ll_uart_module_num( UART_MODULE_D0 ) ], HAL_LL_UART_IRQ_TX );
        write_reg( hal_ll_uart_regs[ hal_ll_uart_module_num( UART_MODULE_D0 ) ].status, HAL_LL_UART_STATUS_TXCIF_BIT );
    }
}
#endif

#if defined ( UART_MODULE_D1 )
void UART3_RX_IRQHandler( void ) MIKROC_IV( UARTD1_RX_INTERRUPT_ADDRESS_VECTOR ) {
    irq_handler( objects[ hal_ll_uart_module_num( UART_MODULE_D1 ) ], HAL_LL_UART_IRQ_RX );
}

void UART3_TX_IRQHandler( void ) MIKROC_IV( UARTD1_TX_INTERRUPT_ADDRESS_VECTOR ) {
    if( hal_ll_uart_get_status_flags( hal_ll_uart_module_num( UART_MODULE_D1 )) & ( 1 <<  HAL_LL_UART_STATUS_DREIF_BIT )) {
        irq_handler( objects[ hal_ll_uart_module_num( UART_MODULE_D1 ) ], HAL_LL_UART_IRQ_TX );
        write_reg( hal_ll_uart_regs[ hal_ll_uart_module_num( UART_MODULE_D1 ) ].status, HAL_LL_UART_STATUS_TXCIF_BIT );
    }
}
#endif

#if defined ( UART_MODULE_E0 )
void UART4_RX_IRQHandler( void ) MIKROC_IV( UARTE0_RX_INTERRUPT_ADDRESS_VECTOR ) {
    irq_handler( objects[ hal_ll_uart_module_num( UART_MODULE_E0 ) ], HAL_LL_UART_IRQ_RX );
}

void UART4_TX_IRQHandler( void ) MIKROC_IV( UARTE0_TX_INTERRUPT_ADDRESS_VECTOR ) {
    if( hal_ll_uart_get_status_flags( hal_ll_uart_module_num( UART_MODULE_E0 )) & ( 1 <<  HAL_LL_UART_STATUS_DREIF_BIT )) {
        irq_handler( objects[ hal_ll_uart_module_num( UART_MODULE_E0 ) ], HAL_LL_UART_IRQ_TX );
        write_reg( hal_ll_uart_regs[ hal_ll_uart_module_num( UART_MODULE_E0 ) ].status, HAL_LL_UART_STATUS_TXCIF_BIT );
    }
}
#endif

#if defined ( UART_MODULE_E1 )
void UART5_RX_IRQHandler( void ) MIKROC_IV( UARTE1_RX_INTERRUPT_ADDRESS_VECTOR ) {
    irq_handler( objects[ hal_ll_uart_module_num( UART_MODULE_E1 ) ], HAL_LL_UART_IRQ_RX );
}

void UART5_TX_IRQHandler( void ) MIKROC_IV( UARTE1_TX_INTERRUPT_ADDRESS_VECTOR ) {
    if( hal_ll_uart_get_status_flags( hal_ll_uart_module_num( UART_MODULE_E1 )) & ( 1 <<  HAL_LL_UART_STATUS_DREIF_BIT )) {
        irq_handler( objects[ hal_ll_uart_module_num( UART_MODULE_E1 ) ], HAL_LL_UART_IRQ_TX );
        write_reg( hal_ll_uart_regs[ hal_ll_uart_module_num( UART_MODULE_E1 ) ].status, HAL_LL_UART_STATUS_TXCIF_BIT );
    }
}
#endif

#if defined ( UART_MODULE_F0 )
void UART6_RX_IRQHandler( void ) MIKROC_IV( UARTF0_RX_INTERRUPT_ADDRESS_VECTOR ) {
    irq_handler( objects[ hal_ll_uart_module_num( UART_MODULE_F0 ) ], HAL_LL_UART_IRQ_RX );
}

void UART6_TX_IRQHandler( void ) MIKROC_IV( UARTF0_TX_INTERRUPT_ADDRESS_VECTOR ) {
    if( hal_ll_uart_get_status_flags( hal_ll_uart_module_num( UART_MODULE_F0 )) & ( 1 <<  HAL_LL_UART_STATUS_DREIF_BIT )) {
        irq_handler( objects[ hal_ll_uart_module_num( UART_MODULE_F0 ) ], HAL_LL_UART_IRQ_TX );
        write_reg( hal_ll_uart_regs[ hal_ll_uart_module_num( UART_MODULE_F0 ) ].status, HAL_LL_UART_STATUS_TXCIF_BIT );
    }
}
#endif

#if defined ( UART_MODULE_F1 )
void UART7_RX_IRQHandler( void ) MIKROC_IV( UARTF1_RX_INTERRUPT_ADDRESS_VECTOR ) {
    irq_handler( objects[ hal_ll_uart_module_num( UART_MODULE_F1 ) ], HAL_LL_UART_IRQ_RX );
}

void UART7_TX_IRQHandler( void ) MIKROC_IV( UARTF1_TX_INTERRUPT_ADDRESS_VECTOR ) {
    if( hal_ll_uart_get_status_flags( hal_ll_uart_module_num( UART_MODULE_F1 )) & ( 1 <<  HAL_LL_UART_STATUS_DREIF_BIT )) {
        irq_handler( objects[ hal_ll_uart_module_num( UART_MODULE_F1 ) ], HAL_LL_UART_IRQ_TX );
        write_reg( hal_ll_uart_regs[ hal_ll_uart_module_num( UART_MODULE_F1 ) ].status, HAL_LL_UART_STATUS_TXCIF_BIT );
    }
}
#endif

// ----------------------------------------------- PRIVATE FUNCTION DEFINITIONS
static uint8_t hal_ll_uart_find_index( handle_t *handle ) {
    hal_ll_uart_hw_specifics_map_local = hal_ll_get_specifics( hal_ll_uart_get_module_state_address );

    if( HAL_LL_MODULE_ERROR != hal_ll_uart_hw_specifics_map_local->base->dat ) {
        return hal_ll_uart_hw_specifics_map_local->module_index;
    } else {
        return NULL;
    }
}

static hal_ll_pin_name_t hal_ll_uart_check_pins( hal_ll_pin_name_t tx_pin, hal_ll_pin_name_t rx_pin, hal_ll_uart_pin_id *index_list, hal_ll_uart_handle_register_t *handle_map ) {
    static const uint8_t tx_map_size = ( sizeof( hal_ll_uart_tx_map ) / sizeof( hal_ll_uart_pin_map_t ) );
    static const uint8_t rx_map_size = ( sizeof( hal_ll_uart_rx_map ) / sizeof( hal_ll_uart_pin_map_t ) );
    uint8_t hal_ll_module_id = 0;
    uint8_t index_counter = 0;
    uint8_t tx_index;
    uint8_t rx_index;

    if ( ( HAL_LL_PIN_NC == tx_pin) || ( HAL_LL_PIN_NC == rx_pin) ) {
        return HAL_LL_PIN_NC;
    }

    for ( tx_index = 0; tx_index < tx_map_size; tx_index++ ) {
        if ( hal_ll_uart_tx_map[ tx_index ].pin == tx_pin ) {
            for ( rx_index = 0; rx_index < rx_map_size; rx_index++ ) {
                if ( hal_ll_uart_rx_map[ rx_index ].pin == rx_pin ) {
                    if ( hal_ll_uart_tx_map[ tx_index ].module_index == hal_ll_uart_rx_map[ rx_index ].module_index ) {
                        if ( hal_ll_uart_tx_map[ tx_index ].alternate == hal_ll_uart_rx_map[ rx_index ].alternate ) {
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
    }

    if ( index_counter ) {
        return hal_ll_module_id;
    } else {
        return HAL_LL_PIN_NC;
    }
}

static hal_ll_uart_hw_specifics_map_t *hal_ll_get_specifics( handle_t handle ) {
    uint8_t hal_ll_module_count = sizeof( hal_ll_module_state ) / ( sizeof( hal_ll_uart_handle_register_t ));
    static uint8_t hal_ll_module_error = hal_ll_module_count;

    while( hal_ll_module_count-- ) {
        if ( hal_ll_uart_get_base_from_hal_handle == hal_ll_uart_hw_specifics_map[ hal_ll_module_count ].base) {
            return &hal_ll_uart_hw_specifics_map[ hal_ll_module_count ];
        }
    }

    return &hal_ll_uart_hw_specifics_map[hal_ll_module_error];
}

static void hal_ll_uart_map_pins( uint8_t module_index, hal_ll_uart_pin_id *index_list ) {
    hal_ll_uart_hw_specifics_map[ module_index ].pins.tx_pin.pin_name = hal_ll_uart_tx_map[ index_list[ module_index ]->pin_tx ].pin;
    hal_ll_uart_hw_specifics_map[ module_index ].pins.rx_pin.pin_name = hal_ll_uart_rx_map[ index_list[ module_index ]->pin_rx ].pin;
    hal_ll_uart_hw_specifics_map[ module_index ].alternate = hal_ll_uart_rx_map[ index_list[ module_index ]->pin_rx ].alternate;
}

static void hal_ll_uart_alternate_functions_set_state( hal_ll_uart_hw_specifics_map_t *map, bool hal_ll_state ) {
    hal_ll_gpio_pin_t local_pin;
    if (( HAL_LL_PIN_NC != map->pins.tx_pin.pin_name ) && ( HAL_LL_PIN_NC != map->pins.rx_pin.pin_name )) {
        if ( hal_ll_state) {
            hal_ll_gpio_configure_pin( &local_pin, map->pins.tx_pin.pin_name, HAL_LL_GPIO_DIGITAL_OUTPUT );
            hal_ll_gpio_configure_pin( &local_pin, map->pins.rx_pin.pin_name, HAL_LL_GPIO_DIGITAL_INPUT );
        } else {
            hal_ll_gpio_configure_pin( &local_pin, map->pins.tx_pin.pin_name, HAL_LL_GPIO_DIGITAL_INPUT );
            hal_ll_gpio_configure_pin( &local_pin, map->pins.rx_pin.pin_name, HAL_LL_GPIO_DIGITAL_INPUT );
        }
    }
    #if ( HAL_LL_MODULE_REMAP == true )
    if( true == map->alternate ) {
        #ifdef UART_MODULE_C0
        if( hal_ll_uart_module_num( UART_MODULE_C0 ) == map->module_index ) {
            set_reg_bit( PORTC_REMAP_REG_ADDRESS, HAL_LL_USART0_REMAP_BIT );
        }
        #endif
        #ifdef UART_MODULE_D0
        if( hal_ll_uart_module_num( UART_MODULE_D0 ) == map->module_index ) {
            set_reg_bit( PORTD_REMAP_REG_ADDRESS, HAL_LL_USART0_REMAP_BIT );
        }
        #endif
        #ifdef UART_MODULE_E0
        if( hal_ll_uart_module_num( UART_MODULE_E0 ) == map->module_index ) {
            set_reg_bit( PORTE_REMAP_REG_ADDRESS, HAL_LL_USART0_REMAP_BIT );
        }
        #endif
        #ifdef UART_MODULE_F0
        if( hal_ll_uart_module_num( UART_MODULE_F0 ) == map->module_index ) {
            set_reg_bit( PORTF_REMAP_REG_ADDRESS, HAL_LL_USART0_REMAP_BIT );
        }
        #endif
    }
    #endif
}

static void hal_ll_uart_set_baud_bare_metal( hal_ll_uart_hw_specifics_map_t *map ) {
    const hal_ll_uart_base_handle_t *hal_ll_hw_reg = hal_ll_uart_get_base_struct( map->base );
    static uint32_t peripheral_clock = Get_Fosc_kHz()*1000;
    volatile int8_t bscale, i, baud_mul;
    volatile int16_t bsel;
    volatile float real_baud, baud_rate_error;

    baud_mul = ( check_reg_bit( hal_ll_hw_reg->ctrlb, HAL_LL_UART_CTRLB_CLK2X_BIT )) ? HAL_LL_UART_BAUD_RATE_MUL_CLK2X : HAL_LL_UART_BAUD_RATE_MUL;

    for( i = -7; i < 8; i++) {
        if( i < 0 ) {
            bsel =  ( pow( 2, i * (-1) ) * (( (float)peripheral_clock / ( map->baud_rate.baud * baud_mul )) - 1 ));
            real_baud = (float)peripheral_clock / ( baud_mul*( pow( 2, i ) * bsel + 1 ));
        } else {
            bsel = pow( 2, i * (-1) ) * ( (float)peripheral_clock / ( map->baud_rate.baud * baud_mul )) - 1;
            real_baud = peripheral_clock / (float)( pow( 2, i ) * baud_mul * ( bsel + 1 ));
        }
        if (( 4095 < bsel ) || ( 0 > bsel ) || ( 0 == bsel ) && ( 0 != i )) continue;
        baud_rate_error = hal_ll_uart_get_baud_error( real_baud, map->baud_rate.baud );
        if( (float)1.0 > baud_rate_error ) break;
    }

    if( baud_rate_error > HAL_LL_UART_ACCEPTABLE_ERROR ) {
        map->baud_rate.real_baud = (uint32_t)baud_rate_error;
    } else {
        map->baud_rate.real_baud = real_baud;
        bscale = i;
        write_reg( hal_ll_hw_reg->baudctrla, bsel );
        write_reg( hal_ll_hw_reg->baudctrlb, ( bsel >> 8 ) | ( bscale << 4 ));
    }
}

static void hal_ll_uart_set_data_bits_bare_metal( hal_ll_uart_hw_specifics_map_t *map ) {
    const hal_ll_uart_base_handle_t *hal_ll_hw_reg = hal_ll_uart_get_base_struct( map->base );

    switch( map->data_bit ) {
        // NOTE: HAL_LL_UART_DATA_BITS_5 and HAL_LL_UART_DATA_BITS_6 are not defined
        /*
        case HAL_LL_UART_DATA_BITS_5:
            set_reg_bits( hal_ll_hw_reg->ctrlc, HAL_LL_UART_CHSIZE_5BIT );
            break;
        case HAL_LL_UART_DATA_BITS_6:
            set_reg_bits( hal_ll_hw_reg->ctrlc, HAL_LL_UART_CHSIZE_6BIT );
            break;
        */
        case HAL_LL_UART_DATA_BITS_7:
            set_reg_bits( hal_ll_hw_reg->ctrlc, HAL_LL_UART_CHSIZE_7BIT );
            break;
        case HAL_LL_UART_DATA_BITS_8:
            set_reg_bits( hal_ll_hw_reg->ctrlc, HAL_LL_UART_CHSIZE_8BIT );
            break;
        case HAL_LL_UART_DATA_BITS_9:
            set_reg_bits( hal_ll_hw_reg->ctrlc, HAL_LL_UART_CHSIZE_9BIT );
            break;

        default:
            break;
    }
}

static void hal_ll_uart_set_stop_bits_bare_metal( hal_ll_uart_hw_specifics_map_t *map ) {
    const hal_ll_uart_base_handle_t *hal_ll_hw_reg = hal_ll_uart_get_base_struct( map->base );

    switch( map->stop_bit ) {
        case HAL_LL_UART_STOP_BITS_ONE:
            set_reg_bits( hal_ll_hw_reg->ctrlc, HAL_LL_UART_SBMODE_ONE << HAL_LL_UART_SBMODE_SHIFT );
            break;
        case HAL_LL_UART_STOP_BITS_TWO:
            set_reg_bits( hal_ll_hw_reg->ctrlc, HAL_LL_UART_SBMODE_TWO << HAL_LL_UART_SBMODE_SHIFT );
            break;

        default:
            break;
    }
}

static void hal_ll_uart_set_parity_bare_metal( hal_ll_uart_hw_specifics_map_t *map ) {
    const hal_ll_uart_base_handle_t *hal_ll_hw_reg = hal_ll_uart_get_base_struct( map->base );

    switch( map->parity ) {
        case HAL_LL_UART_PARITY_NONE:
            clear_reg_bits( hal_ll_hw_reg->ctrlc, HAL_LL_UART_PARITY_NONE << HAL_LL_UART_PMODE_SHIFT );
            break;
        case HAL_LL_UART_PARITY_EVEN:
            set_reg_bits( hal_ll_hw_reg->ctrlc, HAL_LL_UART_PARITY_EVEN << HAL_LL_UART_PMODE_SHIFT );
            break;
        case HAL_LL_UART_PARITY_ODD:
            set_reg_bits( hal_ll_hw_reg->ctrlc, HAL_LL_UART_PARITY_ODD << HAL_LL_UART_PMODE_SHIFT );
            break;

        default:
            break;
    }
}

static void hal_ll_uart_set_transmitter( const hal_ll_uart_base_handle_t *hal_ll_hw_reg, hal_ll_uart_state_t pin_state ) {
    switch ( pin_state )
    {
        case HAL_LL_UART_DISABLE:
            clear_reg_bit( hal_ll_hw_reg->ctrlb, HAL_LL_UART_CTRLB_TXEN_BIT );
            break;

        case HAL_LL_UART_ENABLE:
            set_reg_bit( hal_ll_hw_reg->ctrlb, HAL_LL_UART_CTRLB_TXEN_BIT );
            break;

        default:
            break;
    }
}

static void hal_ll_uart_set_receiver( const hal_ll_uart_base_handle_t *hal_ll_hw_reg, hal_ll_uart_state_t pin_state ) {
    switch ( pin_state )
    {
        case HAL_LL_UART_DISABLE:
            clear_reg_bit( hal_ll_hw_reg->ctrlb, HAL_LL_UART_CTRLB_RXEN_BIT );
            break;

        case HAL_LL_UART_ENABLE:
            set_reg_bit( hal_ll_hw_reg->ctrlb, HAL_LL_UART_CTRLB_RXEN_BIT );
            break;

        default:
            break;
    }
}

static void hal_ll_uart_power_reduction_enable( uint8_t module_num, bool hal_ll_state ) {

    switch ( module_num ) {
        #ifdef UART_MODULE_C0
        case hal_ll_uart_module_num(UART_MODULE_C0):
            if( true == hal_ll_state ) {
                set_reg_bit( HAL_LL_PRPC_REG_ADDRESS, HAL_LL_PRPn_USART0_MODULE_ENABLE );
            } else {
                clear_reg_bit( HAL_LL_PRPC_REG_ADDRESS, HAL_LL_PRPn_USART0_MODULE_ENABLE );
            }
            break;
        #endif
        #ifdef UART_MODULE_C1
        case hal_ll_uart_module_num(UART_MODULE_C1):
            if( true == hal_ll_state ) {
                set_reg_bit( HAL_LL_PRPC_REG_ADDRESS, HAL_LL_PRPn_USART1_MODULE_ENABLE );
            } else {
                clear_reg_bit( HAL_LL_PRPC_REG_ADDRESS, HAL_LL_PRPn_USART1_MODULE_ENABLE );
            }
            break;
        #endif
        #ifdef UART_MODULE_D0
        case hal_ll_uart_module_num(UART_MODULE_D0):
            if( true == hal_ll_state ) {
                set_reg_bit( HAL_LL_PRPD_REG_ADDRESS, HAL_LL_PRPn_USART0_MODULE_ENABLE );
            } else {
                clear_reg_bit( HAL_LL_PRPD_REG_ADDRESS, HAL_LL_PRPn_USART0_MODULE_ENABLE );
            }
            break;
        #endif
        #ifdef UART_MODULE_D1
        case hal_ll_uart_module_num(UART_MODULE_D1):
            if( true == hal_ll_state ) {
                set_reg_bit( HAL_LL_PRPD_REG_ADDRESS, HAL_LL_PRPn_USART1_MODULE_ENABLE );
            } else {
                clear_reg_bit( HAL_LL_PRPD_REG_ADDRESS, HAL_LL_PRPn_USART1_MODULE_ENABLE );
            }
            break;
        #endif
        #ifdef UART_MODULE_E0
        case hal_ll_uart_module_num(UART_MODULE_E0):
            if( true == hal_ll_state ) {
                set_reg_bit( HAL_LL_PRPE_REG_ADDRESS, HAL_LL_PRPn_USART0_MODULE_ENABLE );
            } else {
                clear_reg_bit( HAL_LL_PRPE_REG_ADDRESS, HAL_LL_PRPn_USART0_MODULE_ENABLE );
            }
            break;
        #endif
        #ifdef UART_MODULE_E1
        case hal_ll_uart_module_num(UART_MODULE_E1):
            if( true == hal_ll_state ) {
                set_reg_bit( HAL_LL_PRPE_REG_ADDRESS, HAL_LL_PRPn_USART1_MODULE_ENABLE );
            } else {
                clear_reg_bit( HAL_LL_PRPE_REG_ADDRESS, HAL_LL_PRPn_USART1_MODULE_ENABLE );
            }
            break;
        #endif
        #ifdef UART_MODULE_F0
        case hal_ll_uart_module_num(UART_MODULE_F0):
            if( true == hal_ll_state ) {
                set_reg_bit( HAL_LL_PRPF_REG_ADDRESS, HAL_LL_PRPn_USART0_MODULE_ENABLE );
            } else {
                clear_reg_bit( HAL_LL_PRPF_REG_ADDRESS, HAL_LL_PRPn_USART0_MODULE_ENABLE );
            }
            break;
        #endif
        #ifdef UART_MODULE_F1
        case hal_ll_uart_module_num(UART_MODULE_F1):
            if( true == hal_ll_state ) {
                set_reg_bit( HAL_LL_PRPF_REG_ADDRESS, HAL_LL_PRPn_USART1_MODULE_ENABLE );
            } else {
                clear_reg_bit( HAL_LL_PRPF_REG_ADDRESS, HAL_LL_PRPn_USART1_MODULE_ENABLE );
            }
            break;
        #endif
    }
}

static void hal_ll_uart_clear_regs( const hal_ll_uart_base_handle_t *hal_ll_hw_reg ) {
    clear_reg( hal_ll_hw_reg->ctrla );
    clear_reg( hal_ll_hw_reg->ctrlc );
}

static void hal_ll_uart_hw_init( hal_ll_uart_hw_specifics_map_t *map ) {
    const hal_ll_uart_base_handle_t *hal_ll_hw_reg = hal_ll_uart_get_base_struct( map->base );

    hal_ll_uart_clear_regs( map->base );

    // Power-down appropriate UART module via Power Reduction Register (if available).
    #if HAL_LL_POWER_REDUCTION
    hal_ll_uart_power_reduction_enable( map->module_index, false );
    #endif

    hal_ll_uart_set_baud_bare_metal( map );

    hal_ll_uart_set_parity_bare_metal( map );

    hal_ll_uart_set_data_bits_bare_metal( map );

    hal_ll_uart_set_stop_bits_bare_metal( map );

    write_reg( HAL_LL_PMIC_CTRL_REG_ADDRESS, HAL_LL_PMIC_CTRL_HILVLEN | HAL_LL_PMIC_CTRL_MEDLVLEN | HAL_LL_PMIC_CTRL_LOLVLEN );

    hal_ll_uart_set_transmitter( map->base, HAL_LL_UART_ENABLE );

    hal_ll_uart_set_receiver( map->base, HAL_LL_UART_ENABLE );

    /*
     * In order for UART Transmit interrupt to be triggered, initial dummy data write is required.
     * According to documentation:
     * "Data transfer is initiated by writing to the DATA register.
     *  This is the case for both sending and receiving data, since the transmitter controls the transfer clock."
     */
    write_reg( hal_ll_hw_reg->dat, HAL_LL_UART_TRIGGER_INTERRUPT );
}

static void hal_ll_uart_init( hal_ll_uart_hw_specifics_map_t *map ) {
    hal_ll_uart_hw_init( map );
}

// ------------------------------------------------------------------------- END
