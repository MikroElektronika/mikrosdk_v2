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

#include "hal_ll_pmc.h"
#include "hal_ll_uart.h"
#include "hal_ll_gpio.h"
#include "hal_ll_core.h"
#include "hal_ll_core_defines.h"
#include "hal_ll_uart_pin_map.h"

/*!< @brief Local handle list */
static volatile hal_ll_uart_handle_register_t hal_ll_module_state[UART_MODULE_COUNT + USART_MODULE_COUNT] = { (handle_t *)NULL, (handle_t *)NULL, false };

// ------------------------------------------------------------- PRIVATE MACROS

/*!< @brief Helper macro for getting module specific base address directly from HAL layer handle */
#define hal_ll_uart_get_base_from_hal_handle ((hal_ll_uart_hw_specifics_map_t *)((hal_ll_uart_handle_register_t *)\
                                             (((hal_ll_uart_handle_register_t *)(handle))->hal_ll_uart_handle))->hal_ll_uart_handle)->base

/*!< @brief Helper macro for getting module specific control register structure base address // first register address */
#define hal_ll_uart_get_handle (hal_ll_uart_handle_register_t *)hal_ll_uart_get_module_state_address->hal_ll_uart_handle

/*!< @brief Helper macro for getting module specific control register structure */
#define hal_ll_uart_get_base_struct(_handle) ((hal_ll_uart_base_handle_t *)_handle)

/*!< @brief Macros used for calculating actual baud rate value and error value */
#define HAL_LL_UART_ACCEPTABLE_ERROR (float)1.0
#define hal_ll_get_system_clock (Get_Fosc_kHz() * 1000)
#define hal_ll_uart_real_baud_rate(_div) (hal_ll_get_system_clock / (16 * _div))
#define hal_ll_baud_rate_register_divider(_baud) (hal_ll_get_system_clock / (16 * _baud))
#define hal_ll_uart_get_baud_error(_baud_real,_baud) (((float)(abs(_baud_real - _baud)) / _baud) * 100)

/*!< @brief Macros defining bit location */
#define HAL_LL_PID_UART0_BIT        7
#define HAL_LL_PID_UART1_BIT        8
#define HAL_LL_PID_UART2_BIT        12
#define HAL_LL_PID_UART3_BIT        13
#define HAL_LL_PID_UART4_BIT        14

#define HAL_LL_PID_USART0_BIT       13
#define HAL_LL_PID_USART1_BIT       14
#define HAL_LL_PID_USART2_BIT       15

#define HAL_LL_CR_RXEN_BIT          4
#define HAL_LL_CR_RXDIS_BIT         5
#define HAL_LL_CR_TXEN_BIT          6
#define HAL_LL_CR_TXDIS_BIT         7

#define HAL_LL_UART_IER_RXRDY_BIT   0
#define HAL_LL_UART_IER_TXRDY_BIT   1

#define HAL_LL_UART_IMR_RXRDY_FLAG 0x1
#define HAL_LL_UART_IMR_TXRDY_FLAG 0x2

#define HAL_LL_UART_SR_RXRDY_FLAG 0x1
#define HAL_LL_UART_SR_TXRDY_FLAG 0x2

/*!< @#brief Macros defining register masks */
#define HAL_LL_UART_MR_DATA_LENGTH_7_BIT_MASK       0x0080
#define HAL_LL_UART_MR_DATA_LENGTH_8_BIT_MASK       0x00C0
#define HAL_LL_UART_MR_PARITY_EVEN_MASK             0x0000
#define HAL_LL_UART_MR_PARITY_ODD_MASK              0x0200
#define HAL_LL_UART_MR_PARITY_NONE_MASK             0x0800
#define HAL_LL_UART_MR_STOP_BITS_ONE_MASK           0x0000
#define HAL_LL_UART_MR_STOP_BITS_ONE_AND_HALF_MASK  0x1000
#define HAL_LL_UART_MR_STOP_BITS_TWO_MASK           0x2000

#define HAL_LL_UART_CR_DISABLE_MASK                 0x00AC

/*!< @brief Helper macro for getting hal_ll_module_state address */
#define hal_ll_uart_get_module_state_address ((hal_ll_uart_handle_register_t *)*handle)

/*!< @brief Macro used for interrupt status register flag check
 * Used in interrupt handlers.
 */
#define hal_ll_uart_get_status_flags(_handle,_flag) (((hal_ll_uart_base_handle_t *)_handle)->imr & _flag)

/*!< @brief Macro used for module interrupt source check.
 * Used in interrupt handlers.
 */
 #define hal_ll_uart_get_interrupt_source(_handle,_bit) (((hal_ll_uart_base_handle_t *)_handle)->sr & _bit)

/*!< @brief UART HW register structure */
typedef struct
{
    hal_ll_base_addr_t cr;
    hal_ll_base_addr_t mr;
    hal_ll_base_addr_t ier;
    hal_ll_base_addr_t idr;
    hal_ll_base_addr_t imr;
    hal_ll_base_addr_t sr;
    hal_ll_base_addr_t rhr;
    hal_ll_base_addr_t thr;
    hal_ll_base_addr_t brgr;
    hal_ll_base_addr_t cmpr;
} hal_ll_uart_base_handle_t;

/*!< @brief UART baud rate structure */
typedef struct
{
    uint32_t baud;
    uint32_t real_baud;
} hal_ll_uart_baud_t;

/*!< @brief UART hw specific structure */
typedef struct
{
    hal_ll_base_addr_t base;
    uint8_t module_index;
    hal_ll_uart_pins_t pins;
    hal_ll_uart_baud_t baud_rate;
    hal_ll_uart_parity_t parity;
    hal_ll_uart_stop_bits_t stop_bit;
    hal_ll_uart_data_bits_t data_bit;
} hal_ll_uart_hw_specifics_map_t;

/*!< @brief UART hw specific module values */
typedef struct
{
    hal_ll_pin_name_t pin_tx;
    hal_ll_pin_name_t pin_rx;
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

// ------------------------------------------------------------------ VARIABLES
/*!< @brief UART hardware specific info */
static hal_ll_uart_hw_specifics_map_t hal_ll_uart_hw_specifics_map[] =
{
    #ifdef USART_MODULE_0
    {HAL_LL_USART0_BASE_ADDRESS, hal_ll_usart_module_num(USART_MODULE_0), {HAL_LL_PIN_NC, 0, HAL_LL_PIN_NC, 0}, {115200, 0}, HAL_LL_UART_PARITY_DEFAULT, HAL_LL_UART_STOP_BITS_DEFAULT, HAL_LL_UART_DATA_BITS_DEFAULT},
    #endif
    #ifdef USART_MODULE_1
    {HAL_LL_USART1_BASE_ADDRESS, hal_ll_usart_module_num(USART_MODULE_1), {HAL_LL_PIN_NC, 0, HAL_LL_PIN_NC, 0}, {115200, 0}, HAL_LL_UART_PARITY_DEFAULT, HAL_LL_UART_STOP_BITS_DEFAULT, HAL_LL_UART_DATA_BITS_DEFAULT},
    #endif
    #ifdef USART_MODULE_2
    {HAL_LL_USART2_BASE_ADDRESS, hal_ll_usart_module_num(USART_MODULE_2), {HAL_LL_PIN_NC, 0, HAL_LL_PIN_NC, 0}, {115200, 0}, HAL_LL_UART_PARITY_DEFAULT, HAL_LL_UART_STOP_BITS_DEFAULT, HAL_LL_UART_DATA_BITS_DEFAULT},
    #endif
    #ifdef UART_MODULE_0
    {HAL_LL_UART0_BASE_ADDRESS, hal_ll_uart_module_num(UART_MODULE_0), {HAL_LL_PIN_NC, 0, HAL_LL_PIN_NC, 0}, {115200, 0}, HAL_LL_UART_PARITY_DEFAULT, HAL_LL_UART_STOP_BITS_DEFAULT, HAL_LL_UART_DATA_BITS_DEFAULT},
    #endif
    #ifdef UART_MODULE_1
    {HAL_LL_UART1_BASE_ADDRESS, hal_ll_uart_module_num(UART_MODULE_1), {HAL_LL_PIN_NC, 0, HAL_LL_PIN_NC, 0}, {115200, 0}, HAL_LL_UART_PARITY_DEFAULT, HAL_LL_UART_STOP_BITS_DEFAULT, HAL_LL_UART_DATA_BITS_DEFAULT},
    #endif
    #ifdef UART_MODULE_2
    {HAL_LL_UART2_BASE_ADDRESS, hal_ll_uart_module_num(UART_MODULE_2), {HAL_LL_PIN_NC, 0, HAL_LL_PIN_NC, 0}, {115200, 0}, HAL_LL_UART_PARITY_DEFAULT, HAL_LL_UART_STOP_BITS_DEFAULT, HAL_LL_UART_DATA_BITS_DEFAULT},
    #endif
    #ifdef UART_MODULE_3
    {HAL_LL_UART3_BASE_ADDRESS, hal_ll_uart_module_num(UART_MODULE_3), {HAL_LL_PIN_NC, 0, HAL_LL_PIN_NC, 0}, {115200, 0}, HAL_LL_UART_PARITY_DEFAULT, HAL_LL_UART_STOP_BITS_DEFAULT, HAL_LL_UART_DATA_BITS_DEFAULT},
    #endif
    #ifdef UART_MODULE_4
    {HAL_LL_UART4_BASE_ADDRESS, hal_ll_uart_module_num(UART_MODULE_4), {HAL_LL_PIN_NC, 0, HAL_LL_PIN_NC, 0}, {115200, 0}, HAL_LL_UART_PARITY_DEFAULT, HAL_LL_UART_STOP_BITS_DEFAULT, HAL_LL_UART_DATA_BITS_DEFAULT},
    #endif

    {HAL_LL_MODULE_ERROR, HAL_LL_MODULE_ERROR, {HAL_LL_PIN_NC, 0, HAL_LL_PIN_NC, 0}, {0, 0}, HAL_LL_MODULE_ERROR, HAL_LL_MODULE_ERROR, HAL_LL_MODULE_ERROR}
};

/*!< @brief Global handle variables used in functions */
static volatile hal_ll_uart_handle_register_t *low_level_handle;
static volatile hal_ll_uart_hw_specifics_map_t *hal_ll_uart_hw_specifics_map_local;

/*!< @brief Global interrupt handlers used in functions */
static hal_ll_uart_isr_t irq_handler;
static handle_t objects[UART_MODULE_COUNT + USART_MODULE_COUNT];

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
    hal_ll_uart_pin_id index_list[UART_MODULE_COUNT + USART_MODULE_COUNT] = {HAL_LL_PIN_NC,HAL_LL_PIN_NC};
    uint16_t pin_check_result;

    // Check if pins are valid
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
    hal_ll_uart_pin_id index_list[UART_MODULE_COUNT + USART_MODULE_COUNT] = {HAL_LL_PIN_NC,HAL_LL_PIN_NC};
    uint16_t pin_check_result;

    if ( (pin_check_result = hal_ll_uart_check_pins( hal_ll_uart_hw_specifics_map_local->pins.tx_pin.pin_name,
                                                     hal_ll_uart_hw_specifics_map_local->pins.rx_pin.pin_name, &index_list, (void *)0 ) ) == HAL_LL_PIN_NC ) {
        return HAL_LL_UART_WRONG_PINS;
    };

    hal_ll_uart_init( hal_ll_uart_hw_specifics_map_local );

    hal_ll_module_state[pin_check_result].hal_ll_uart_handle = (handle_t *)&hal_ll_uart_hw_specifics_map[pin_check_result].base;
    hal_ll_module_state[pin_check_result].init_ll_state = true;

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

    // Chips using implementation 1 do not support 7 bit data
    if( data_bit == HAL_LL_UART_DATA_BITS_7 ) {
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

void hal_ll_uart_register_irq_handler( handle_t *handle, hal_ll_uart_isr_t handler, handle_t obj ) {
    irq_handler = handler;
    objects[ hal_ll_uart_find_index( handle ) ] = obj;
}

void hal_ll_uart_irq_enable( handle_t *handle, hal_ll_uart_irq_t irq ) {
    low_level_handle = hal_ll_uart_get_handle;
    hal_ll_uart_hw_specifics_map_local = hal_ll_get_specifics(hal_ll_uart_get_module_state_address);

    hal_ll_uart_base_handle_t *hal_ll_hw_reg = ( hal_ll_uart_base_handle_t *)hal_ll_uart_hw_specifics_map_local->base;

    switch ( irq ) {
        case HAL_LL_UART_IRQ_RX:
            set_reg_bit( &hal_ll_hw_reg->ier, HAL_LL_UART_IER_RXRDY_BIT );
            break;

        case HAL_LL_UART_IRQ_TX:
            set_reg_bit( &hal_ll_hw_reg->ier, HAL_LL_UART_IER_TXRDY_BIT );
            break;

        default:
            break;
    }

    switch ( hal_ll_uart_hw_specifics_map_local->module_index )
    {
            #ifdef USART_MODULE_0
            case hal_ll_usart_module_num( USART_MODULE_0 ):
                hal_ll_core_enable_irq( USART0_NVIC );
                break;
            #endif

            #ifdef USART_MODULE_1
            case hal_ll_usart_module_num( USART_MODULE_1 ):
                hal_ll_core_enable_irq( USART1_NVIC );
                break;
            #endif

            #ifdef USART_MODULE_2
            case hal_ll_usart_module_num( USART_MODULE_2 ):
                hal_ll_core_enable_irq( USART2_NVIC );
                break;
            #endif

            #ifdef UART_MODULE_0
            case hal_ll_uart_module_num( UART_MODULE_0 ):
                hal_ll_core_enable_irq( UART0_NVIC );
                break;
            #endif

            #ifdef UART_MODULE_1
            case hal_ll_uart_module_num( UART_MODULE_1 ):
                hal_ll_core_enable_irq( UART1_NVIC );
                break;
            #endif

            #ifdef UART_MODULE_2
            case hal_ll_uart_module_num( UART_MODULE_2 ):
                hal_ll_core_enable_irq( UART2_NVIC );
                break;
            #endif

            #ifdef UART_MODULE_3
            case hal_ll_uart_module_num( UART_MODULE_3 ):
                hal_ll_core_enable_irq( UART3_NVIC );
                break;
            #endif

            #ifdef UART_MODULE_4
            case hal_ll_uart_module_num( UART_MODULE_4 ):
                hal_ll_core_enable_irq( UART4_NVIC );
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
            set_reg_bit( &hal_ll_hw_reg->idr, HAL_LL_UART_IER_RXRDY_BIT );
            break;

        case HAL_LL_UART_IRQ_TX:
            set_reg_bit( &hal_ll_hw_reg->idr, HAL_LL_UART_IER_TXRDY_BIT );
            break;

        default:
            break;
    }
    // Check if module interrupt flags are set or not
    if ( ( !hal_ll_uart_get_status_flags( hal_ll_uart_hw_specifics_map_local->base , HAL_LL_UART_IMR_RXRDY_FLAG ) ) &&
         ( !hal_ll_uart_get_status_flags( hal_ll_uart_hw_specifics_map_local->base , HAL_LL_UART_IMR_TXRDY_FLAG ) ) )
    {
        switch ( hal_ll_uart_hw_specifics_map_local->module_index )
        {
            #ifdef USART_MODULE_0
            case hal_ll_usart_module_num( USART_MODULE_0 ):
                hal_ll_core_disable_irq( USART0_NVIC );
                break;
            #endif

            #ifdef USART_MODULE_1
            case hal_ll_usart_module_num( USART_MODULE_1 ):
                hal_ll_core_disable_irq( USART1_NVIC );
                break;
            #endif

            #ifdef USART_MODULE_2
            case hal_ll_usart_module_num( USART_MODULE_2 ):
                hal_ll_core_disable_irq( USART2_NVIC );
                break;
            #endif

            #ifdef UART_MODULE_0
            case hal_ll_uart_module_num( UART_MODULE_0 ):
                hal_ll_core_disable_irq( UART0_NVIC );
                break;
            #endif

            #ifdef UART_MODULE_1
            case hal_ll_uart_module_num( UART_MODULE_1 ):
                hal_ll_core_disable_irq( UART1_NVIC );
                break;
            #endif

            #ifdef UART_MODULE_2
            case hal_ll_uart_module_num( UART_MODULE_2 ):
                hal_ll_core_disable_irq( UART2_NVIC );
                break;
            #endif

            #ifdef UART_MODULE_3
            case hal_ll_uart_module_num( UART_MODULE_3 ):
                hal_ll_core_disable_irq( UART3_NVIC );
                break;
            #endif

            #ifdef UART_MODULE_4
            case hal_ll_uart_module_num( UART_MODULE_4 ):
                hal_ll_core_disable_irq( UART4_NVIC );
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

    write_reg( &hal_ll_hw_reg->thr, wr_data );
}

void hal_ll_uart_write_polling( handle_t *handle, uint8_t wr_data) {
    hal_ll_uart_hw_specifics_map_local = hal_ll_get_specifics(hal_ll_uart_get_module_state_address);
    hal_ll_uart_base_handle_t *hal_ll_hw_reg = ( hal_ll_uart_base_handle_t *)hal_ll_uart_hw_specifics_map_local->base;

    while( !( read_reg( &hal_ll_hw_reg->sr ) & HAL_LL_UART_SR_TXRDY_FLAG ) ) {
        // Wait for space in the transmit buffer
    }

    write_reg( &hal_ll_hw_reg->thr, wr_data );
}

uint8_t hal_ll_uart_read( handle_t *handle ) {
    hal_ll_uart_hw_specifics_map_local = hal_ll_get_specifics(hal_ll_uart_get_module_state_address);
    hal_ll_uart_base_handle_t *hal_ll_hw_reg = ( hal_ll_uart_base_handle_t *)hal_ll_uart_hw_specifics_map_local->base;

    return ( read_reg( &hal_ll_hw_reg->rhr ) );
}

uint8_t hal_ll_uart_read_polling( handle_t *handle ) {
    hal_ll_uart_hw_specifics_map_local = hal_ll_get_specifics(hal_ll_uart_get_module_state_address);
    hal_ll_uart_base_handle_t *hal_ll_hw_reg = ( hal_ll_uart_base_handle_t *)hal_ll_uart_hw_specifics_map_local->base;

    while( !( read_reg( &hal_ll_hw_reg->sr ) & HAL_LL_UART_SR_RXRDY_FLAG ) ) {
        // Wait for data in the receive buffer
    }

    return ( read_reg( &hal_ll_hw_reg->rhr ) );
}

// ------------------------------------------------------------- DEFAULT EXCEPTION HANDLERS

#ifdef USART_MODULE_0
void USART0_Handler(void) {
    if( hal_ll_uart_get_status_flags( HAL_LL_USART0_BASE_ADDRESS , HAL_LL_UART_IMR_RXRDY_FLAG ) ) {
        if( ( hal_ll_uart_get_interrupt_source( HAL_LL_USART0_BASE_ADDRESS, HAL_LL_UART_SR_RXRDY_FLAG ) ) ) {
            irq_handler( objects[ hal_ll_usart_module_num( USART_MODULE_0 ) ], HAL_LL_UART_IRQ_RX );
        }
    }
    if( hal_ll_uart_get_status_flags( HAL_LL_USART0_BASE_ADDRESS , HAL_LL_UART_IMR_TXRDY_FLAG ) ) {
        if( ( hal_ll_uart_get_interrupt_source( HAL_LL_USART0_BASE_ADDRESS, HAL_LL_UART_SR_TXRDY_FLAG ) ) ) {
            irq_handler( objects[ hal_ll_usart_module_num( USART_MODULE_0 ) ], HAL_LL_UART_IRQ_TX );
        }
    }
}
#endif

#ifdef USART_MODULE_1
void USART1_Handler(void) {
    if( hal_ll_uart_get_status_flags( HAL_LL_USART1_BASE_ADDRESS , HAL_LL_UART_IMR_RXRDY_FLAG ) ) {
        if( ( hal_ll_uart_get_interrupt_source( HAL_LL_USART1_BASE_ADDRESS, HAL_LL_UART_SR_RXRDY_FLAG ) ) ) {
            irq_handler( objects[ hal_ll_usart_module_num( USART_MODULE_1 ) ], HAL_LL_UART_IRQ_RX );
        }
    }
    if( hal_ll_uart_get_status_flags( HAL_LL_USART1_BASE_ADDRESS , HAL_LL_UART_IMR_TXRDY_FLAG ) ) {
        if( ( hal_ll_uart_get_interrupt_source( HAL_LL_USART1_BASE_ADDRESS, HAL_LL_UART_SR_TXRDY_FLAG ) ) ) {
            irq_handler( objects[ hal_ll_usart_module_num( USART_MODULE_1 ) ], HAL_LL_UART_IRQ_TX );
        }
    }
}
#endif

#ifdef USART_MODULE_2
void USART2_Handler(void) {
    if( hal_ll_uart_get_status_flags( HAL_LL_USART2_BASE_ADDRESS , HAL_LL_UART_IMR_RXRDY_FLAG ) ) {
        if( ( hal_ll_uart_get_interrupt_source( HAL_LL_USART2_BASE_ADDRESS, HAL_LL_UART_SR_RXRDY_FLAG ) ) ) {
            irq_handler( objects[ hal_ll_usart_module_num( USART_MODULE_2 ) ], HAL_LL_UART_IRQ_RX );
        }
    }
    if( hal_ll_uart_get_status_flags( HAL_LL_USART2_BASE_ADDRESS , HAL_LL_UART_IMR_TXRDY_FLAG ) ) {
        if( ( hal_ll_uart_get_interrupt_source( HAL_LL_USART2_BASE_ADDRESS, HAL_LL_UART_SR_TXRDY_FLAG ) ) ) {
            irq_handler( objects[ hal_ll_usart_module_num( USART_MODULE_2 ) ], HAL_LL_UART_IRQ_TX );
        }
    }
}
#endif

#ifdef UART_MODULE_0
void UART0_Handler(void) {
    if( hal_ll_uart_get_status_flags( HAL_LL_UART0_BASE_ADDRESS , HAL_LL_UART_IMR_RXRDY_FLAG ) ) {
        if( ( hal_ll_uart_get_interrupt_source( HAL_LL_UART0_BASE_ADDRESS, HAL_LL_UART_SR_RXRDY_FLAG ) ) ) {
            irq_handler( objects[ hal_ll_uart_module_num( UART_MODULE_0 ) ], HAL_LL_UART_IRQ_RX );
        }
    }
    if( hal_ll_uart_get_status_flags( HAL_LL_UART0_BASE_ADDRESS , HAL_LL_UART_IMR_TXRDY_FLAG ) ) {
        if( ( hal_ll_uart_get_interrupt_source( HAL_LL_UART0_BASE_ADDRESS, HAL_LL_UART_SR_TXRDY_FLAG ) ) ) {
            irq_handler( objects[ hal_ll_uart_module_num( UART_MODULE_0 ) ], HAL_LL_UART_IRQ_TX );
        }
    }
}
#endif

#ifdef UART_MODULE_1
void UART1_Handler(void) {
    if( hal_ll_uart_get_status_flags( HAL_LL_UART1_BASE_ADDRESS , HAL_LL_UART_IMR_RXRDY_FLAG ) ) {
        if( ( hal_ll_uart_get_interrupt_source( HAL_LL_UART1_BASE_ADDRESS, HAL_LL_UART_SR_RXRDY_FLAG ) ) ) {
            irq_handler( objects[ hal_ll_uart_module_num( UART_MODULE_1 ) ], HAL_LL_UART_IRQ_RX );
        }
    }
    if( hal_ll_uart_get_status_flags( HAL_LL_UART1_BASE_ADDRESS , HAL_LL_UART_IMR_TXRDY_FLAG ) ) {
        if( ( hal_ll_uart_get_interrupt_source( HAL_LL_UART1_BASE_ADDRESS, HAL_LL_UART_SR_TXRDY_FLAG ) ) ) {
            irq_handler( objects[ hal_ll_uart_module_num( UART_MODULE_1 ) ], HAL_LL_UART_IRQ_TX );
        }
    }
}
#endif

#ifdef UART_MODULE_2
void UART2_Handler(void) {
    if( hal_ll_uart_get_status_flags( HAL_LL_UART2_BASE_ADDRESS , HAL_LL_UART_IMR_RXRDY_FLAG ) ) {
        if( ( hal_ll_uart_get_interrupt_source( HAL_LL_UART2_BASE_ADDRESS, HAL_LL_UART_SR_RXRDY_FLAG ) ) ) {
            irq_handler( objects[ hal_ll_uart_module_num( UART_MODULE_2 ) ], HAL_LL_UART_IRQ_RX );
        }
    }
    if( hal_ll_uart_get_status_flags( HAL_LL_UART2_BASE_ADDRESS , HAL_LL_UART_IMR_TXRDY_FLAG ) ) {
        if( ( hal_ll_uart_get_interrupt_source( HAL_LL_UART2_BASE_ADDRESS, HAL_LL_UART_SR_TXRDY_FLAG ) ) ) {
            irq_handler( objects[ hal_ll_uart_module_num( UART_MODULE_2 ) ], HAL_LL_UART_IRQ_TX );
        }
    }
}
#endif

#ifdef UART_MODULE_3
void UART3_Handler(void) {
    if( hal_ll_uart_get_status_flags( HAL_LL_UART3_BASE_ADDRESS , HAL_LL_UART_IMR_RXRDY_FLAG ) ) {
        if( ( hal_ll_uart_get_interrupt_source( HAL_LL_UART3_BASE_ADDRESS, HAL_LL_UART_SR_RXRDY_FLAG ) ) ) {
            irq_handler( objects[ hal_ll_uart_module_num( UART_MODULE_3 ) ], HAL_LL_UART_IRQ_RX );
        }
    }
    if( hal_ll_uart_get_status_flags( HAL_LL_UART3_BASE_ADDRESS , HAL_LL_UART_IMR_TXRDY_FLAG ) ) {
        if( ( hal_ll_uart_get_interrupt_source( HAL_LL_UART3_BASE_ADDRESS, HAL_LL_UART_SR_TXRDY_FLAG ) ) ) {
            irq_handler( objects[ hal_ll_uart_module_num( UART_MODULE_3 ) ], HAL_LL_UART_IRQ_TX );
        }
    }
}
#endif

#ifdef UART_MODULE_4
void UART4_Handler(void) {
    if( hal_ll_uart_get_status_flags( HAL_LL_UART4_BASE_ADDRESS , HAL_LL_UART_IMR_RXRDY_FLAG ) ) {
        if( ( hal_ll_uart_get_interrupt_source( HAL_LL_UART4_BASE_ADDRESS, HAL_LL_UART_SR_RXRDY_FLAG ) ) ) {
            irq_handler( objects[ hal_ll_uart_module_num( UART_MODULE_4 ) ], HAL_LL_UART_IRQ_RX );
        }
    }
    if( hal_ll_uart_get_status_flags( HAL_LL_UART4_BASE_ADDRESS , HAL_LL_UART_IMR_TXRDY_FLAG ) ) {
        if( ( hal_ll_uart_get_interrupt_source( HAL_LL_UART4_BASE_ADDRESS, HAL_LL_UART_SR_TXRDY_FLAG ) ) ) {
            irq_handler( objects[ hal_ll_uart_module_num( UART_MODULE_4 ) ], HAL_LL_UART_IRQ_TX );
        }
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

    if ( ( HAL_LL_PIN_NC == tx_pin ) || ( HAL_LL_PIN_NC == rx_pin ) ) {
        return HAL_LL_PIN_NC;
    }

    for ( tx_index = 0; tx_index < tx_map_size; tx_index++ )
    {
        if ( hal_ll_uart_tx_map[ tx_index ].pin == tx_pin )
        {
            for ( rx_index = 0; rx_index < rx_map_size; rx_index++ )
            {
                if ( hal_ll_uart_rx_map[ rx_index ].pin == rx_pin )
                {
                    if ( hal_ll_uart_tx_map[ tx_index ].base == hal_ll_uart_rx_map[ rx_index ].base ) {
                        // Get module number
                        hal_ll_module_id = hal_ll_uart_tx_map[ tx_index ].module_index;

                        // Map pin names
                        index_list[hal_ll_module_id].pin_tx = tx_index;
                        index_list[hal_ll_module_id].pin_rx = rx_index;

                        // Check if module is taken
                        if ( NULL == handle_map[ hal_ll_module_id ].hal_drv_uart_handle ) {
                            return hal_ll_module_id;
                        } else if ( ( UART_MODULE_COUNT + USART_MODULE_COUNT ) == ++index_counter ) {
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
    switch ( map->module_index )
    {
        #ifdef USART_MODULE_0
        case ( hal_ll_usart_module_num(USART_MODULE_0) ):
            (hal_ll_state == true)?(set_reg_bit( _PMC_PCER0, HAL_LL_PID_USART0_BIT )):(clear_reg_bit( _PMC_PCER0, HAL_LL_PID_USART0_BIT ));
            break;
        #endif

        #ifdef USART_MODULE_1
        case ( hal_ll_usart_module_num(USART_MODULE_1) ):
            (hal_ll_state == true)?(set_reg_bit( _PMC_PCER0, HAL_LL_PID_USART1_BIT )):(clear_reg_bit( _PMC_PCER0, HAL_LL_PID_USART1_BIT ));
            break;
        #endif

        #ifdef USART_MODULE_2
        case ( hal_ll_usart_module_num(USART_MODULE_2) ):
            (hal_ll_state == true)?(set_reg_bit( _PMC_PCER0, HAL_LL_PID_USART2_BIT )):(clear_reg_bit( _PMC_PCER0, HAL_LL_PID_USART2_BIT ));
            break;
        #endif

        #ifdef UART_MODULE_0
        case ( hal_ll_uart_module_num(UART_MODULE_0) ):
            (hal_ll_state == true)?(set_reg_bit( _PMC_PCER0, HAL_LL_PID_UART0_BIT )):(clear_reg_bit( _PMC_PCER0, HAL_LL_PID_UART0_BIT ));
            break;
        #endif

        #ifdef UART_MODULE_1
        case ( hal_ll_uart_module_num(UART_MODULE_1) ):
            (hal_ll_state == true)?(set_reg_bit( _PMC_PCER0, HAL_LL_PID_UART1_BIT )):(clear_reg_bit( _PMC_PCER0, HAL_LL_PID_UART1_BIT ));
            break;
        #endif

        #ifdef UART_MODULE_2
        case ( hal_ll_uart_module_num(UART_MODULE_2) ):
            (hal_ll_state == true)?(set_reg_bit( _PMC_PCER1, HAL_LL_PID_UART2_BIT )):(clear_reg_bit( _PMC_PCER1, HAL_LL_PID_UART2_BIT ));
            break;
        #endif

        #ifdef UART_MODULE_3
        case ( hal_ll_uart_module_num(UART_MODULE_3) ):
            (hal_ll_state == true)?(set_reg_bit( _PMC_PCER1, HAL_LL_PID_UART3_BIT )):(clear_reg_bit( _PMC_PCER1, HAL_LL_PID_UART3_BIT ));
            break;
        #endif

        #ifdef UART_MODULE_4
        case ( hal_ll_uart_module_num(UART_MODULE_4) ):
            (hal_ll_state == true)?(set_reg_bit( _PMC_PCER1, HAL_LL_PID_UART4_BIT )):(clear_reg_bit( _PMC_PCER1, HAL_LL_PID_UART4_BIT ));
            break;
        #endif

        default:
            break;
    }
}

static void hal_ll_uart_map_pins( uint8_t module_index, hal_ll_uart_pin_id *index_list ) {
    // Map new pins
    hal_ll_uart_hw_specifics_map[module_index].pins.tx_pin.pin_name = hal_ll_uart_tx_map[ index_list[module_index].pin_tx ].pin;
    hal_ll_uart_hw_specifics_map[module_index].pins.rx_pin.pin_name = hal_ll_uart_rx_map[ index_list[module_index].pin_rx ].pin;
    // TX and RX could have different alternate function settings, hence save both AF values
    hal_ll_uart_hw_specifics_map[module_index].pins.tx_pin.pin_af = hal_ll_uart_tx_map[ index_list[module_index].pin_tx ].af;
    hal_ll_uart_hw_specifics_map[module_index].pins.rx_pin.pin_af = hal_ll_uart_rx_map[ index_list[module_index].pin_rx ].af;
}

static void hal_ll_uart_alternate_functions_set_state( hal_ll_uart_hw_specifics_map_t *map, bool hal_ll_state ) {
    module_struct module;

    if ( ( map->pins.tx_pin.pin_name != HAL_LL_PIN_NC ) && map->pins.rx_pin.pin_name != HAL_LL_PIN_NC ) {
        module.pins[0] = map->pins.tx_pin.pin_name;
        module.pins[1] = map->pins.rx_pin.pin_name;
        module.pins[2] = GPIO_MODULE_STRUCT_END;

        module.configs[0] = map->pins.tx_pin.pin_af;
        module.configs[1] = map->pins.rx_pin.pin_af;
        module.configs[2] = GPIO_MODULE_STRUCT_END;

        hal_ll_gpio_module_struct_init( &module, hal_ll_state );
    }
}

static void hal_ll_uart_set_baud_bare_metal( hal_ll_uart_hw_specifics_map_t *map ) {
    hal_ll_uart_base_handle_t *hal_ll_hw_reg = hal_ll_uart_get_base_struct(map->base);
    uint16_t baud_rate_register_divider = hal_ll_baud_rate_register_divider( map->baud_rate.baud );
    uint32_t real_baud_rate = hal_ll_uart_real_baud_rate( baud_rate_register_divider );

    // If error greater than specified, cancel setting baud rate.
    if ( HAL_LL_UART_ACCEPTABLE_ERROR < hal_ll_uart_get_baud_error( real_baud_rate, map->baud_rate.baud )) {
        map->baud_rate.real_baud = hal_ll_uart_get_baud_error( real_baud_rate, map->baud_rate.baud );
    } else {
        map->baud_rate.real_baud = real_baud_rate;

        write_reg( &hal_ll_hw_reg->brgr, baud_rate_register_divider );
    }
}

static void hal_ll_uart_set_stop_bits_bare_metal( hal_ll_uart_hw_specifics_map_t *map ) {
    hal_ll_uart_base_handle_t *hal_ll_hw_reg = hal_ll_uart_get_base_struct(map->base);

    switch ( map->stop_bit )
    {
        case HAL_LL_UART_STOP_BITS_ONE:
            set_reg_bits( &hal_ll_hw_reg->mr, HAL_LL_UART_MR_STOP_BITS_ONE_MASK );
            break;
        case HAL_LL_UART_STOP_BITS_ONE_AND_A_HALF:
            set_reg_bits( &hal_ll_hw_reg->mr, HAL_LL_UART_MR_STOP_BITS_ONE_AND_HALF_MASK );
            break;
        case HAL_LL_UART_STOP_BITS_TWO:
            set_reg_bits( &hal_ll_hw_reg->mr, HAL_LL_UART_MR_STOP_BITS_TWO_MASK );
            break;

        default:
            break;
    }
}

static void hal_ll_uart_set_data_bits_bare_metal( hal_ll_uart_hw_specifics_map_t *map ) {
    hal_ll_uart_base_handle_t *hal_ll_hw_reg = hal_ll_uart_get_base_struct(map->base);

    switch ( map->data_bit )
    {
        case HAL_LL_UART_DATA_BITS_7:
            set_reg_bits( &hal_ll_hw_reg->mr, HAL_LL_UART_MR_DATA_LENGTH_7_BIT_MASK );
            break;

        case HAL_LL_UART_DATA_BITS_8:
            set_reg_bits( &hal_ll_hw_reg->mr, HAL_LL_UART_MR_DATA_LENGTH_8_BIT_MASK );
            break;

        default:
            break;
    }
}

static void hal_ll_uart_set_parity_bare_metal( hal_ll_uart_hw_specifics_map_t *map ) {
    hal_ll_uart_base_handle_t *hal_ll_hw_reg = hal_ll_uart_get_base_struct(map->base);

    switch ( map->parity )
    {
        case HAL_LL_UART_PARITY_NONE:
            set_reg_bits( &hal_ll_hw_reg->mr, HAL_LL_UART_MR_PARITY_NONE_MASK );
            break;
        case HAL_LL_UART_PARITY_EVEN:
            set_reg_bits( &hal_ll_hw_reg->mr, HAL_LL_UART_MR_PARITY_EVEN_MASK );
            break;
        case HAL_LL_UART_PARITY_ODD:
            set_reg_bits( &hal_ll_hw_reg->mr, HAL_LL_UART_MR_PARITY_ODD_MASK );
            break;

        default:
            break;
    }
}

static void hal_ll_uart_set_transmitter( hal_ll_uart_base_handle_t *hal_ll_hw_reg, hal_ll_uart_state_t pin_state ) {
    switch ( pin_state )
    {
        case HAL_LL_UART_DISABLE:
            set_reg_bit( &hal_ll_hw_reg->cr, HAL_LL_CR_TXDIS_BIT );
            break;

        case HAL_LL_UART_ENABLE:
            set_reg_bit( &hal_ll_hw_reg->cr, HAL_LL_CR_TXEN_BIT );
            break;

        default:
            break;
    }
}

static void hal_ll_uart_set_receiver( hal_ll_uart_base_handle_t *hal_ll_hw_reg, hal_ll_uart_state_t pin_state ) {
    switch ( pin_state )
    {
        case HAL_LL_UART_DISABLE:
            clear_reg_bit( &hal_ll_hw_reg->cr, HAL_LL_CR_RXDIS_BIT );
            break;

        case HAL_LL_UART_ENABLE:
            set_reg_bit( &hal_ll_hw_reg->cr, HAL_LL_CR_RXEN_BIT );
            break;

        default:
            break;
    }
}

static void hal_ll_uart_clear_regs( hal_ll_uart_base_handle_t *hal_ll_hw_reg ) {
    clear_reg( &hal_ll_hw_reg->cr );
    clear_reg( &hal_ll_hw_reg->mr );
    clear_reg( &hal_ll_hw_reg->ier );
    hal_ll_hw_reg->cr = HAL_LL_UART_CR_DISABLE_MASK;
}

static void hal_ll_uart_hw_init( hal_ll_uart_hw_specifics_map_t *map ) {
    hal_ll_uart_clear_regs( map->base );

    hal_ll_uart_set_data_bits_bare_metal( map );

    hal_ll_uart_set_parity_bare_metal( map );

    hal_ll_uart_set_stop_bits_bare_metal( map );

    hal_ll_uart_set_baud_bare_metal( map );

    hal_ll_uart_set_transmitter( map->base, HAL_LL_UART_ENABLE );

    hal_ll_uart_set_receiver( map->base, HAL_LL_UART_ENABLE );
}

static void hal_ll_uart_init( hal_ll_uart_hw_specifics_map_t *map ) {
    hal_ll_uart_set_clock( map, true );

    hal_ll_uart_alternate_functions_set_state( map, true );

    hal_ll_uart_hw_init( map );
}
// ------------------------------------------------------------------------- END
