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


/*!< @brief Macro used for status registed flag check.
 * Used in interrupt handlers.
 */
#define hal_ll_uart_get_status_flags(_handle,_flag) (((hal_ll_uart_base_handle_t *)_handle)->mis & _flag)

/*!< @brief Macro used for status registed flag clearing.
 * Used in interrupt handlers.
 */
#define hal_ll_uart_clear_status_flag(_handle,_flag) (set_reg_bit(&(((hal_ll_uart_base_handle_t *)_handle)->icr), _flag))

/*!< @brief Macro used for picking the divisors for the source clock.
 * if is_base_16 == true:
 *     Skip this calculation for divisors that are not achievable with 16 base clk cycles per bit.
 * if is_base_16 == false:
 *     Skip this calculation for divisors that are only achievable without 16 base clk cycles per bit.
 */
#define hal_ll_sci_brr_assert_divisors(is_base_16, i)   \
                                    (is_base_16  ^ (g_async_baud[i].abcs | g_async_baud[i].abcse))

/*!< @brief Macro used for calculating BRR register value.
 * BRR = (PCLKA / (div_coefficient * baud)) - 1
 */
#define hal_ll_sci_brr_calculate(baud, pclka, i) (pclka / (g_div_coefficient[i] * baud))

/*!< @brief Macro used for calculating the baud rate error.
 * error[%] = {(PCLKA / (baud * div_coefficient * (BRR + 1)) - 1} x 100
 * Promoting to 64 bits for calculation, but the final value can never be more than 32 bits, as
 * described below, so this cast is safe.
 *    1. Larger frequencies yield larger bit errors (absolute value). As the frequency grows,
 *       the current_error approaches -100000, so:
 *       0 >= current_error >= -100000
 *    2. current_error is between -100000 and 0. This entire range fits in an int32_t type, so the cast
 *       to (int32_t) is safe.
 */
#define hal_ll_sci_brr_get_error(brr, pclka, baud, i) \
    (int32_t)(((((int64_t)pclka) * HAL_LL_SCI_BRR_ERROR_REFERENCE) / \
    (g_div_coefficient[i] * baud * (brr + 1))) - HAL_LL_SCI_BRR_ERROR_REFERENCE)

/*!< @brief Macro used for getting the real baudrate.
 * baud = PCLKA / ((BRR + 1) * div_coefficient)
 */
#define hal_ll_sci_get_baud_rate(pclka, brr, i) (pclka / ((brr + 1) * g_div_coefficient[i]))

/*!< @brief Macros defining bit location. */
#define HAL_LL_SCI_SEMR_BRME    2
#define HAL_LL_SCI_SEMR_ABCSE   3
#define HAL_LL_SCI_SMR_STOP     3
#define HAL_LL_SCI_SEMR_ABCS    4
#define HAL_LL_SCI_SCMR_CHR1    4
#define HAL_LL_SCI_SMR_PM       4
#define HAL_LL_SCI_SCR_RE       4
#define HAL_LL_SCI_SCR_TE       5
#define HAL_LL_SCI_SMR_PE       5
#define HAL_LL_SCI_SMR_CHR      6
#define HAL_LL_SCI_SSR_RDRF     6
#define HAL_LL_SCI_SEMR_BGDM    6
#define HAL_LL_SCI_SSR_TDRE     7

/*!< @brief Macros defining register bit values. */
#define HAL_LL_SCI_CLOCK_EXTERNAL   0x3
#define HAL_LL_SCI_SEMR_CONFIGURE(bgdm, abcs, abcse) \
                                    (bgdm << HAL_LL_SCI_SEMR_BGDM) | \
                                    (abcs << HAL_LL_SCI_SEMR_ABCS) | \
                                    (abcse << HAL_LL_SCI_SEMR_ABCSE)

/*!< @brief Macros used for baudrate calculations. */
#define HAL_LL_SCI_NUM_DIVISORS         13
#define HAL_LL_SCI_BRR_MAX              256
#define HAL_LL_SCI_BRR_ERROR_ACCEPTABLE 1000UL
#define HAL_LL_SCI_BRR_ERROR_REFERENCE  100000UL

/*!< @brief Structures used for baudrate calculations. */
typedef struct st_baud_setting_const_t
{
    uint8_t bgdm;   /**< BGDM value to get divisor */
    uint8_t abcs;   /**< ABCS value to get divisor */
    uint8_t abcse;  /**< ABCSE value to get divisor */
    uint8_t cks;    /**< CKS  value to get divisor (CKS = N) */
} baud_setting_const_t;

/*!< @brief Baud rate bit divisor information structure. */
static const baud_setting_const_t g_async_baud[ HAL_LL_SCI_NUM_DIVISORS ] =
{
    {0U, 0U, 1U, 0U},                  /* BGDM, ABCS, ABCSE, n */
    {1U, 1U, 0U, 0U},
    {1U, 0U, 0U, 0U},
    {0U, 0U, 1U, 1U},
    {0U, 0U, 0U, 0U},
    {1U, 0U, 0U, 1U},
    {0U, 0U, 1U, 2U},
    {0U, 0U, 0U, 1U},
    {1U, 0U, 0U, 2U},
    {0U, 0U, 1U, 3U},
    {0U, 0U, 0U, 2U},
    {1U, 0U, 0U, 3U},
    {0U, 0U, 0U, 3U}
};

/*!< @brief Baud rate divisor information structure. */
static const uint16_t g_div_coefficient[ HAL_LL_SCI_NUM_DIVISORS ] =
{
    6U, 8U, 16U, 24U, 32U, 64U, 96U, 128U, 256U, 384U, 512U, 1024U, 2048U,
};

/*!< @brief UART HW register structure. */
typedef struct {
    uint8_t smr;    // Serial Mode Register.
    uint8_t brr;    // Bit Rate Register.
    uint8_t scr;    // Serial Control Register.
    uint8_t tdr;    // Transmit Data Register.
    uint8_t ssr;    // Serial Status Register.
    uint8_t rdr;    // Receive Data Register.
    uint8_t scmr;   // Smart Card Mode Register.
    uint8_t semr;   // Serial Extended Mode Register.
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
    {HAL_LL_UART0_BASE_ADDRESS, hal_ll_uart_module_num( UART_MODULE_0 ), {HAL_LL_PIN_NC, 0, HAL_LL_PIN_NC, 0}, {9600, 0}, HAL_LL_UART_PARITY_DEFAULT, HAL_LL_UART_STOP_BITS_DEFAULT, HAL_LL_UART_DATA_BITS_DEFAULT},
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
    #ifdef UART_MODULE_8
    {HAL_LL_UART8_BASE_ADDRESS, hal_ll_uart_module_num( UART_MODULE_8 ), {HAL_LL_PIN_NC, 0, HAL_LL_PIN_NC, 0}, {115200, 0}, HAL_LL_UART_PARITY_DEFAULT, HAL_LL_UART_STOP_BITS_DEFAULT, HAL_LL_UART_DATA_BITS_DEFAULT},
    #endif
    #ifdef UART_MODULE_9
    {HAL_LL_UART9_BASE_ADDRESS, hal_ll_uart_module_num( UART_MODULE_9 ), {HAL_LL_PIN_NC, 0, HAL_LL_PIN_NC, 0}, {115200, 0}, HAL_LL_UART_PARITY_DEFAULT, HAL_LL_UART_STOP_BITS_DEFAULT, HAL_LL_UART_DATA_BITS_DEFAULT},
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
  * Returns adequate clock speed for UART module.
  *
  * @return uint32_t UART source clock speed in Hz.
  */
static uint32_t hal_ll_uart_get_clock_speed( void );

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

void hal_ll_uart_close( handle_t *handle ) {
    low_level_handle = hal_ll_uart_get_handle;
    hal_ll_uart_hw_specifics_map_local = hal_ll_get_specifics( hal_ll_uart_get_module_state_address );

    if( low_level_handle->hal_ll_uart_handle != NULL ) {
        hal_ll_uart_set_clock( hal_ll_uart_hw_specifics_map_local, true );
        hal_ll_uart_alternate_functions_set_state( hal_ll_uart_hw_specifics_map_local, false );

        hal_ll_uart_irq_disable( handle, HAL_LL_UART_IRQ_RX );
        hal_ll_uart_irq_disable( handle, HAL_LL_UART_IRQ_TX );

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
    objects[ hal_ll_uart_find_index( handle ) ] = obj;
}

void hal_ll_uart_irq_enable( handle_t *handle, hal_ll_uart_irq_t irq ) {
    low_level_handle = hal_ll_uart_get_handle;
    hal_ll_uart_hw_specifics_map_local = hal_ll_get_specifics( hal_ll_uart_get_module_state_address );

    hal_ll_uart_base_handle_t *hal_ll_hw_reg = ( hal_ll_uart_base_handle_t *)hal_ll_uart_hw_specifics_map_local->base;

    switch ( irq ) {
        case HAL_LL_UART_IRQ_RX:
            // TODO
            break;
        case HAL_LL_UART_IRQ_TX:
            // TODO
            break;

        default:
            break;
    }

    switch ( hal_ll_uart_hw_specifics_map_local->module_index ) {
        #if defined( UART_MODULE_0 ) && defined( UART0_NVIC )
        case hal_ll_uart_module_num( UART_MODULE_0 ):
            hal_ll_core_enable_irq( UART0_NVIC );
            break;
        #endif
        #if defined( UART_MODULE_1 ) && defined( UART1_NVIC )
        case hal_ll_uart_module_num( UART_MODULE_1 ):
            hal_ll_core_enable_irq( UART1_NVIC );
            break;
        #endif
        #if defined( UART_MODULE_2 ) && defined( UART2_NVIC )
        case hal_ll_uart_module_num( UART_MODULE_2 ):
            hal_ll_core_enable_irq( UART2_NVIC );
            break;
        #endif
        #if defined( UART_MODULE_3 ) && defined( UART3_NVIC )
        case hal_ll_uart_module_num( UART_MODULE_3 ):
            hal_ll_core_enable_irq( UART3_NVIC );
            break;
        #endif
        #if defined( UART_MODULE_4 ) && defined( UART4_NVIC )
        case hal_ll_uart_module_num( UART_MODULE_4 ):
            hal_ll_core_enable_irq( UART4_NVIC );
            break;
        #endif
        #if defined( UART_MODULE_5 ) && defined( UART5_NVIC )
        case hal_ll_uart_module_num( UART_MODULE_5 ):
            hal_ll_core_enable_irq( UART5_NVIC );
            break;
        #endif
        #if defined( UART_MODULE_6 ) && defined( UART6_NVIC )
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
    hal_ll_uart_hw_specifics_map_local = hal_ll_get_specifics( hal_ll_uart_get_module_state_address );

    hal_ll_uart_base_handle_t *hal_ll_hw_reg = ( hal_ll_uart_base_handle_t *)hal_ll_uart_hw_specifics_map_local->base;

    switch ( irq ) {
        case HAL_LL_UART_IRQ_RX:
            // TODO
            break;
        case HAL_LL_UART_IRQ_TX:
            // TODO
            break;

        default:
            break;
    }

    /* Check if module interrupt flags are set or not.
     * ATTENTION This is a very important part in the code.
     * Interrupts should be disabled ONLY in case we have
     * both TX and RX interrupts disabled.
     */
    if (
        //  ( !check_reg_bit( &hal_ll_hw_reg->im, HAL_LL_UART_IT_RXIM_BIT ) ) &&
        //  ( !check_reg_bit( &hal_ll_hw_reg->im, HAL_LL_UART_IT_TXIM_BIT ) )
        1 // TODO
        )
    {
        switch ( hal_ll_uart_hw_specifics_map_local->module_index ) {
            #if defined( UART_MODULE_0 ) && defined( UART0_NVIC )
            case hal_ll_uart_module_num( UART_MODULE_0 ):
                hal_ll_core_disable_irq( UART0_NVIC );
                break;
            #endif
            #if defined( UART_MODULE_1 ) && defined( UART1_NVIC )
            case hal_ll_uart_module_num( UART_MODULE_1 ):
                hal_ll_core_disable_irq( UART1_NVIC );
                break;
            #endif
            #if defined( UART_MODULE_2 ) && defined( UART2_NVIC )
            case hal_ll_uart_module_num( UART_MODULE_2 ):
                hal_ll_core_disable_irq( UART2_NVIC );
                break;
            #endif
            #if defined( UART_MODULE_3 ) && defined( UART3_NVIC )
            case hal_ll_uart_module_num( UART_MODULE_3 ):
                hal_ll_core_disable_irq( UART3_NVIC );
                break;
            #endif
            #if defined( UART_MODULE_4 ) && defined( UART4_NVIC )
            case hal_ll_uart_module_num( UART_MODULE_4 ):
                hal_ll_core_disable_irq( UART4_NVIC );
                break;
            #endif
            #if defined( UART_MODULE_5 ) && defined( UART5_NVIC )
            case hal_ll_uart_module_num( UART_MODULE_5 ):
                hal_ll_core_disable_irq( UART5_NVIC );
                break;
            #endif
            #if defined( UART_MODULE_6 ) && defined( UART6_NVIC )
            case hal_ll_uart_module_num( UART_MODULE_6 ):
                hal_ll_core_disable_irq( UART6_NVIC );
                break;
            #endif
            #if defined( UART_MODULE_7 ) && defined( UART7_NVIC )
            case hal_ll_uart_module_num( UART_MODULE_7 ):
                hal_ll_core_disable_irq( UART7_NVIC );
                break;
            #endif

            default:
                break;
        }
    }
}

void hal_ll_uart_write( handle_t *handle, uint8_t wr_data ) {
    hal_ll_uart_hw_specifics_map_local = hal_ll_get_specifics( hal_ll_uart_get_module_state_address );
    hal_ll_uart_base_handle_t *hal_ll_hw_reg = ( hal_ll_uart_base_handle_t *)hal_ll_uart_hw_specifics_map_local->base;

    hal_ll_hw_reg->tdr = wr_data;
}

void hal_ll_uart_write_polling( handle_t *handle, uint8_t wr_data ) {
    hal_ll_uart_hw_specifics_map_local = hal_ll_get_specifics( hal_ll_uart_get_module_state_address );
    hal_ll_uart_base_handle_t *hal_ll_hw_reg = ( hal_ll_uart_base_handle_t * )hal_ll_uart_hw_specifics_map_local->base;

    // Wait until transmit data register is empty.
    while ( !( check_reg_bit( &hal_ll_hw_reg->ssr, HAL_LL_SCI_SSR_TDRE )));
    hal_ll_hw_reg->tdr = wr_data;
}

uint8_t hal_ll_uart_read( handle_t *handle ) {
    hal_ll_uart_hw_specifics_map_local = hal_ll_get_specifics( hal_ll_uart_get_module_state_address );
    hal_ll_uart_base_handle_t *hal_ll_hw_reg = ( hal_ll_uart_base_handle_t * )hal_ll_uart_hw_specifics_map_local->base;

    return hal_ll_hw_reg->rdr;
}

uint8_t hal_ll_uart_read_polling( handle_t *handle ) {
    hal_ll_uart_hw_specifics_map_local = hal_ll_get_specifics( hal_ll_uart_get_module_state_address );
    hal_ll_uart_base_handle_t *hal_ll_hw_reg = ( hal_ll_uart_base_handle_t *)hal_ll_uart_hw_specifics_map_local->base;

    // Wait until there is data in the receive data register.
    while ( !( check_reg_bit( &hal_ll_hw_reg->ssr, HAL_LL_SCI_SSR_RDRF )));

    return hal_ll_hw_reg->rdr;
}

// ------------------------------------------------------------- DEFAULT EXCEPTION HANDLERS
#if defined( UART_MODULE_0 ) && defined( UART0_NVIC )
void MARK_AS_IRQ_HANDLER UART0_IRQHandler( void ) MIKROC_IV( UART0_NVIC ) {
    if ( hal_ll_uart_get_status_flags( HAL_LL_UART0_BASE_ADDRESS , HAL_LL_UART_STATUS_RXMIS_FLAG )) {
        hal_ll_uart_clear_status_flag( HAL_LL_UART0_BASE_ADDRESS, HAL_LL_UART_IT_RXIM_BIT );
        irq_handler( objects[ hal_ll_uart_module_num( UART_MODULE_0 ) ], HAL_LL_UART_IRQ_RX );
    }
    if ( hal_ll_uart_get_status_flags( HAL_LL_UART0_BASE_ADDRESS , HAL_LL_UART_STATUS_TXMIS_FLAG )) {
        hal_ll_uart_clear_status_flag( HAL_LL_UART0_BASE_ADDRESS, HAL_LL_UART_IT_TXIM_BIT );
        irq_handler( objects[ hal_ll_uart_module_num( UART_MODULE_0 ) ], HAL_LL_UART_IRQ_TX );
    }
}
#endif

#if defined( UART_MODULE_1 ) && defined( UART1_NVIC )
void MARK_AS_IRQ_HANDLER UART1_IRQHandler( void ) MIKROC_IV( UART1_NVIC ) {
    if ( hal_ll_uart_get_status_flags( HAL_LL_UART1_BASE_ADDRESS , HAL_LL_UART_STATUS_RXMIS_FLAG )) {
        hal_ll_uart_clear_status_flag( HAL_LL_UART1_BASE_ADDRESS, HAL_LL_UART_IT_RXIM_BIT );
        irq_handler( objects[ hal_ll_uart_module_num( UART_MODULE_1 ) ], HAL_LL_UART_IRQ_RX );
    }
    if ( hal_ll_uart_get_status_flags( HAL_LL_UART1_BASE_ADDRESS , HAL_LL_UART_STATUS_TXMIS_FLAG )) {
        hal_ll_uart_clear_status_flag( HAL_LL_UART1_BASE_ADDRESS, HAL_LL_UART_IT_TXIM_BIT );
        irq_handler( objects[ hal_ll_uart_module_num( UART_MODULE_1 ) ], HAL_LL_UART_IRQ_TX );
    }
}
#endif

#if defined( UART_MODULE_2 ) && defined( UART2_NVIC )
void MARK_AS_IRQ_HANDLER UART2_IRQHandler( void ) MIKROC_IV( UART2_NVIC ) {
    if ( hal_ll_uart_get_status_flags( HAL_LL_UART2_BASE_ADDRESS , HAL_LL_UART_STATUS_RXMIS_FLAG )) {
        hal_ll_uart_clear_status_flag( HAL_LL_UART2_BASE_ADDRESS, HAL_LL_UART_IT_RXIM_BIT );
        irq_handler( objects[ hal_ll_uart_module_num( UART_MODULE_2 ) ], HAL_LL_UART_IRQ_RX );
    }
    if ( hal_ll_uart_get_status_flags( HAL_LL_UART2_BASE_ADDRESS , HAL_LL_UART_STATUS_TXMIS_FLAG )) {
        hal_ll_uart_clear_status_flag( HAL_LL_UART2_BASE_ADDRESS, HAL_LL_UART_IT_TXIM_BIT );
        irq_handler( objects[ hal_ll_uart_module_num( UART_MODULE_2 ) ], HAL_LL_UART_IRQ_TX );
    }
}
#endif

#if defined( UART_MODULE_3 ) && defined( UART3_NVIC )
void MARK_AS_IRQ_HANDLER UART3_IRQHandler( void ) MIKROC_IV( UART3_NVIC ) {
    if ( hal_ll_uart_get_status_flags( HAL_LL_UART3_BASE_ADDRESS , HAL_LL_UART_STATUS_RXMIS_FLAG )) {
        hal_ll_uart_clear_status_flag( HAL_LL_UART3_BASE_ADDRESS, HAL_LL_UART_IT_RXIM_BIT );
        irq_handler( objects[ hal_ll_uart_module_num( UART_MODULE_3 ) ], HAL_LL_UART_IRQ_RX );
    }
    if ( hal_ll_uart_get_status_flags( HAL_LL_UART3_BASE_ADDRESS , HAL_LL_UART_STATUS_TXMIS_FLAG )) {
        hal_ll_uart_clear_status_flag( HAL_LL_UART3_BASE_ADDRESS, HAL_LL_UART_IT_TXIM_BIT );
        irq_handler( objects[ hal_ll_uart_module_num( UART_MODULE_3 ) ], HAL_LL_UART_IRQ_TX );
    }
}
#endif

#if defined( UART_MODULE_4 ) && defined( UART4_NVIC )
void MARK_AS_IRQ_HANDLER UART4_IRQHandler( void ) MIKROC_IV( UART4_NVIC ) {
    if ( hal_ll_uart_get_status_flags( HAL_LL_UART4_BASE_ADDRESS , HAL_LL_UART_STATUS_RXMIS_FLAG )) {
        hal_ll_uart_clear_status_flag( HAL_LL_UART4_BASE_ADDRESS, HAL_LL_UART_IT_RXIM_BIT );
        irq_handler( objects[ hal_ll_uart_module_num( UART_MODULE_4 ) ], HAL_LL_UART_IRQ_RX );
    }
    if ( hal_ll_uart_get_status_flags( HAL_LL_UART4_BASE_ADDRESS , HAL_LL_UART_STATUS_TXMIS_FLAG )) {
        hal_ll_uart_clear_status_flag( HAL_LL_UART4_BASE_ADDRESS, HAL_LL_UART_IT_TXIM_BIT );
        irq_handler( objects[ hal_ll_uart_module_num( UART_MODULE_4 ) ], HAL_LL_UART_IRQ_TX );
    }
}
#endif

#if defined( UART_MODULE_5 ) && defined( UART5_NVIC )
void MARK_AS_IRQ_HANDLER UART5_IRQHandler( void ) MIKROC_IV( UART5_NVIC ) {
    if ( hal_ll_uart_get_status_flags( HAL_LL_UART5_BASE_ADDRESS , HAL_LL_UART_STATUS_RXMIS_FLAG )) {
        hal_ll_uart_clear_status_flag( HAL_LL_UART5_BASE_ADDRESS, HAL_LL_UART_IT_RXIM_BIT );
        irq_handler( objects[ hal_ll_uart_module_num( UART_MODULE_5 ) ], HAL_LL_UART_IRQ_RX );
    }
    if ( hal_ll_uart_get_status_flags( HAL_LL_UART5_BASE_ADDRESS , HAL_LL_UART_STATUS_TXMIS_FLAG )) {
        hal_ll_uart_clear_status_flag( HAL_LL_UART5_BASE_ADDRESS, HAL_LL_UART_IT_TXIM_BIT );
        irq_handler( objects[ hal_ll_uart_module_num( UART_MODULE_5 )], HAL_LL_UART_IRQ_TX );
    }
}
#endif

#if defined( UART_MODULE_6 ) && defined( UART6_NVIC )
void MARK_AS_IRQ_HANDLER UART6_IRQHandler( void ) MIKROC_IV( UART6_NVIC ) {
    if ( hal_ll_uart_get_status_flags( HAL_LL_UART6_BASE_ADDRESS , HAL_LL_UART_STATUS_RXMIS_FLAG )) {
        hal_ll_uart_clear_status_flag( HAL_LL_UART6_BASE_ADDRESS, HAL_LL_UART_IT_RXIM_BIT );
        irq_handler( objects[ hal_ll_uart_module_num( UART_MODULE_6 ) ], HAL_LL_UART_IRQ_RX );
    }
    if ( hal_ll_uart_get_status_flags( HAL_LL_UART6_BASE_ADDRESS , HAL_LL_UART_STATUS_TXMIS_FLAG )) {
        hal_ll_uart_clear_status_flag( HAL_LL_UART6_BASE_ADDRESS, HAL_LL_UART_IT_TXIM_BIT );
        irq_handler( objects[ hal_ll_uart_module_num( UART_MODULE_6 ) ], HAL_LL_UART_IRQ_TX );
    }
}
#endif

#if defined( UART_MODULE_7 ) && defined( UART7_NVIC )
void MARK_AS_IRQ_HANDLER UART7_IRQHandler( void ) MIKROC_IV( UART7_NVIC ) {
    if ( hal_ll_uart_get_status_flags( HAL_LL_UART7_BASE_ADDRESS , HAL_LL_UART_STATUS_RXMIS_FLAG )) {
        hal_ll_uart_clear_status_flag( HAL_LL_UART7_BASE_ADDRESS, HAL_LL_UART_IT_RXIM_BIT );
        irq_handler( objects[ hal_ll_uart_module_num( UART_MODULE_7 ) ], HAL_LL_UART_IRQ_RX );
    }
    if ( hal_ll_uart_get_status_flags( HAL_LL_UART7_BASE_ADDRESS , HAL_LL_UART_STATUS_TXMIS_FLAG )) {
        hal_ll_uart_clear_status_flag( HAL_LL_UART7_BASE_ADDRESS, HAL_LL_UART_IT_TXIM_BIT );
        irq_handler( objects[ hal_ll_uart_module_num( UART_MODULE_7 ) ], HAL_LL_UART_IRQ_TX );
    }
}
#endif

#if defined( UART_MODULE_8 ) && defined( UART8_NVIC )
void MARK_AS_IRQ_HANDLER UART8_IRQHandler( void ) MIKROC_IV( UART8_NVIC ) {
    if ( hal_ll_uart_get_status_flags( HAL_LL_UART8_BASE_ADDRESS , HAL_LL_UART_STATUS_RXMIS_FLAG )) {
        hal_ll_uart_clear_status_flag( HAL_LL_UART8_BASE_ADDRESS, HAL_LL_UART_IT_RXIM_BIT );
        irq_handler( objects[ hal_ll_uart_module_num( UART_MODULE_8 ) ], HAL_LL_UART_IRQ_RX );
    }
    if ( hal_ll_uart_get_status_flags( HAL_LL_UART8_BASE_ADDRESS , HAL_LL_UART_STATUS_TXMIS_FLAG )) {
        hal_ll_uart_clear_status_flag( HAL_LL_UART8_BASE_ADDRESS, HAL_LL_UART_IT_TXIM_BIT );
        irq_handler( objects[ hal_ll_uart_module_num( UART_MODULE_8 ) ], HAL_LL_UART_IRQ_TX );
    }
}
#endif

#if defined( UART_MODULE_9 ) && defined( UART9_NVIC )
void MARK_AS_IRQ_HANDLER UART9_IRQHandler( void ) MIKROC_IV( UART9_NVIC ) {
    if ( hal_ll_uart_get_status_flags( HAL_LL_UART9_BASE_ADDRESS , HAL_LL_UART_STATUS_RXMIS_FLAG )) {
        hal_ll_uart_clear_status_flag( HAL_LL_UART9_BASE_ADDRESS, HAL_LL_UART_IT_RXIM_BIT );
        irq_handler( objects[ hal_ll_uart_module_num( UART_MODULE_9 ) ], HAL_LL_UART_IRQ_RX );
    }
    if ( hal_ll_uart_get_status_flags( HAL_LL_UART9_BASE_ADDRESS , HAL_LL_UART_STATUS_TXMIS_FLAG )) {
        hal_ll_uart_clear_status_flag( HAL_LL_UART9_BASE_ADDRESS, HAL_LL_UART_IT_TXIM_BIT );
        irq_handler( objects[ hal_ll_uart_module_num( UART_MODULE_9 ) ], HAL_LL_UART_IRQ_TX );
    }
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
    switch ( map->module_index ) {
        #ifdef UART_MODULE_0
        case ( hal_ll_uart_module_num( UART_MODULE_0 )):
            ( hal_ll_state == false ) ? ( set_reg_bit( _MSTPCRB, MSTPCRB_MSTPB31_POS )) : ( clear_reg_bit( _MSTPCRB, MSTPCRB_MSTPB31_POS ));
            break;
        #endif
        #ifdef UART_MODULE_1
        case ( hal_ll_uart_module_num( UART_MODULE_1 )):
            ( hal_ll_state == false ) ? ( set_reg_bit( _MSTPCRB, MSTPCRB_MSTPB30_POS )) : ( clear_reg_bit( _MSTPCRB, MSTPCRB_MSTPB30_POS ));
            break;
        #endif
        #ifdef UART_MODULE_2
        case ( hal_ll_uart_module_num( UART_MODULE_2 )):
            ( hal_ll_state == false ) ? ( set_reg_bit( _MSTPCRB, MSTPCRB_MSTPB29_POS )) : ( clear_reg_bit( _MSTPCRB, MSTPCRB_MSTPB29_POS ));
            break;
        #endif
        #ifdef UART_MODULE_3
        case ( hal_ll_uart_module_num( UART_MODULE_3 )):
            ( hal_ll_state == false ) ? ( set_reg_bit( _MSTPCRB, MSTPCRB_MSTPB28_POS )) : ( clear_reg_bit( _MSTPCRB, MSTPCRB_MSTPB28_POS ));
            break;
        #endif
        #ifdef UART_MODULE_4
        case ( hal_ll_uart_module_num( UART_MODULE_4 )):
            ( hal_ll_state == false ) ? ( set_reg_bit( _MSTPCRB, MSTPCRB_MSTPB27_POS )) : ( clear_reg_bit( _MSTPCRB, MSTPCRB_MSTPB27_POS ));
            break;
        #endif
        #ifdef UART_MODULE_5
        case ( hal_ll_uart_module_num( UART_MODULE_5 )):
            ( hal_ll_state == false ) ? ( set_reg_bit( _MSTPCRB, MSTPCRB_MSTPB26_POS )) : ( clear_reg_bit( _MSTPCRB, MSTPCRB_MSTPB26_POS ));
            break;
        #endif
        #ifdef UART_MODULE_6
        case ( hal_ll_uart_module_num( UART_MODULE_6 )):
            ( hal_ll_state == false ) ? ( set_reg_bit( _MSTPCRB, MSTPCRB_MSTPB25_POS )) : ( clear_reg_bit( _MSTPCRB, MSTPCRB_MSTPB25_POS ));
            break;
        #endif
        #ifdef UART_MODULE_7
        case ( hal_ll_uart_module_num( UART_MODULE_7 )):
            ( hal_ll_state == false ) ? ( set_reg_bit( _MSTPCRB, MSTPCRB_MSTPB24_POS )) : ( clear_reg_bit( _MSTPCRB, MSTPCRB_MSTPB24_POS ));
            break;
        #endif
        #ifdef UART_MODULE_8
        case ( hal_ll_uart_module_num( UART_MODULE_8 )):
            ( hal_ll_state == false ) ? ( set_reg_bit( _MSTPCRB, MSTPCRB_MSTPB23_POS )) : ( clear_reg_bit( _MSTPCRB, MSTPCRB_MSTPB23_POS ));
            break;
        #endif
        #ifdef UART_MODULE_9
        case ( hal_ll_uart_module_num( UART_MODULE_9 )):
            ( hal_ll_state == false ) ? ( set_reg_bit( _MSTPCRB, MSTPCRB_MSTPB22_POS )) : ( clear_reg_bit( _MSTPCRB, MSTPCRB_MSTPB22_POS ));
            break;
        #endif

        default:
            break;
    }
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

    /* Find the best BRR (bit rate register) value.
     *  In table g_async_baud, divisor values are stored for BGDM, ABCS, ABCSE and N values. Each set of divisors
     *  is tried, and the settings with the lowest bit rate error are stored. The formula to calculate BRR is as
     *  follows and it must be 255 or less:
     *  BRR = (PCLKA / (div_coefficient * baud)) - 1
     */
    uint32_t error = HAL_LL_SCI_BRR_ERROR_REFERENCE;
    uint32_t temp_brr, divisor = 0U;
    uint8_t abcse, abcs, bgdm, brr, cks;
    int32_t err_divisor, current_error;
    uint32_t source_clock = hal_ll_uart_get_clock_speed( );

    for ( uint8_t select_16_base_clk_cycles = 0U;
          (( 1 >= select_16_base_clk_cycles ) && ( HAL_LL_SCI_BRR_ERROR_ACCEPTABLE < error ));
          select_16_base_clk_cycles++ )
    {
        for ( uint8_t i = 0U; HAL_LL_SCI_NUM_DIVISORS > i ; i++ )
        {
            if ( hal_ll_sci_brr_assert_divisors( select_16_base_clk_cycles, i ))
            {
                continue;
            }

            temp_brr = hal_ll_sci_brr_calculate( map->baud_rate.baud, source_clock, i );

            if (( HAL_LL_SCI_BRR_MAX ) >= temp_brr )
            {
                while ( temp_brr-- > 0U )
                {
                    current_error = hal_ll_sci_brr_get_error( temp_brr, source_clock, map->baud_rate.baud, i );

                    /* Take the absolute value of the bit rate error. */
                    if ( current_error < 0 )
                    {
                        current_error = -current_error;
                    }

                    /* If the absolute value of the bit rate error is less than the previous lowest absolute value of
                     *  bit rate error, then store these settings as the best value.
                     */
                    if ( current_error < error )
                    {
                        bgdm  = g_async_baud[i].bgdm;
                        abcs  = g_async_baud[i].abcs;
                        abcse = g_async_baud[i].abcse;
                        cks = g_async_baud[i].cks;
                        brr = ( uint8_t ) temp_brr;
                        error = current_error;
                        map->baud_rate.real_baud = hal_ll_sci_get_baud_rate( source_clock, brr ,i );
                    }
                }
            }
        }
    }

    set_reg_bits( &hal_ll_hw_reg->semr, HAL_LL_SCI_SEMR_CONFIGURE( bgdm, abcs, abcse ));
    set_reg_bits( &hal_ll_hw_reg->smr, cks );
    write_reg( &hal_ll_hw_reg->brr, brr );
}

static uint32_t hal_ll_uart_get_clock_speed( void ) {
    system_clocks_t system_clocks;

    SYSTEM_GetClocksFrequency( &system_clocks );
    return system_clocks.pclka;
}

static void hal_ll_uart_set_stop_bits_bare_metal( hal_ll_uart_hw_specifics_map_t *map ) {
    hal_ll_uart_base_handle_t *hal_ll_hw_reg = hal_ll_uart_get_base_struct( map->base );

    switch ( map->stop_bit ) {
        case HAL_LL_UART_STOP_BITS_ONE:
            clear_reg_bit( &hal_ll_hw_reg->smr, HAL_LL_SCI_SMR_STOP );
            break;
        case HAL_LL_UART_STOP_BITS_TWO:
            set_reg_bit( &hal_ll_hw_reg->smr, HAL_LL_SCI_SMR_STOP );
            break;

        default:
            break;
    }
}

static void hal_ll_uart_set_data_bits_bare_metal( hal_ll_uart_hw_specifics_map_t *map ) {
    hal_ll_uart_base_handle_t *hal_ll_hw_reg = hal_ll_uart_get_base_struct( map->base );

    switch ( map->data_bit )
    {
        case HAL_LL_UART_DATA_BITS_7:
            set_reg_bit( &hal_ll_hw_reg->scmr, HAL_LL_SCI_SCMR_CHR1 );
            set_reg_bit( &hal_ll_hw_reg->smr, HAL_LL_SCI_SMR_CHR );
            break;
        case HAL_LL_UART_DATA_BITS_8:
            set_reg_bit( &hal_ll_hw_reg->scmr, HAL_LL_SCI_SCMR_CHR1 );
            clear_reg_bit( &hal_ll_hw_reg->smr, HAL_LL_SCI_SMR_CHR );
            break;
        case HAL_LL_UART_DATA_BITS_9:
            clear_reg_bit( &hal_ll_hw_reg->scmr, HAL_LL_SCI_SCMR_CHR1 );
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
            clear_reg_bit( &hal_ll_hw_reg->smr, HAL_LL_SCI_SMR_PE );
            break;
        case HAL_LL_UART_PARITY_EVEN:
            set_reg_bit( &hal_ll_hw_reg->smr, HAL_LL_SCI_SMR_PE );
            break;
        case HAL_LL_UART_PARITY_ODD:
            set_reg_bit( &hal_ll_hw_reg->smr, HAL_LL_SCI_SMR_PE );
            set_reg_bit( &hal_ll_hw_reg->smr, HAL_LL_SCI_SMR_PM );
            break;

        default:
            break;
    }
}

static void hal_ll_uart_set_module( hal_ll_uart_base_handle_t *hal_ll_hw_reg, hal_ll_uart_state_t pin_state ) {
    switch ( pin_state )
    {
        /* SCI module doesn't have any specific bitfield for enabling it, but
         * we disable UART work by switching source clock to external as this implementation
         * doesn't support the use of external clock for SCI module.
         */
        case HAL_LL_UART_DISABLE:
            set_reg_bits( &hal_ll_hw_reg->scr, HAL_LL_SCI_CLOCK_EXTERNAL );
            break;

        case HAL_LL_UART_ENABLE:
            clear_reg_bits( &hal_ll_hw_reg->scr, HAL_LL_SCI_CLOCK_EXTERNAL );
            break;

        default:
            break;
    }
}

static void hal_ll_uart_set_transmitter( hal_ll_uart_base_handle_t *hal_ll_hw_reg, hal_ll_uart_state_t pin_state ) {
    switch ( pin_state )
    {
        case HAL_LL_UART_DISABLE:
            clear_reg_bit( &hal_ll_hw_reg->scr, HAL_LL_SCI_SCR_TE );
            break;

        case HAL_LL_UART_ENABLE:
            set_reg_bit( &hal_ll_hw_reg->scr, HAL_LL_SCI_SCR_TE );
            break;

        default:
            break;
    }
}

static void hal_ll_uart_set_receiver( hal_ll_uart_base_handle_t *hal_ll_hw_reg, hal_ll_uart_state_t pin_state ) {
    switch ( pin_state )
    {
        case HAL_LL_UART_DISABLE:
            clear_reg_bit( &hal_ll_hw_reg->scr, HAL_LL_SCI_SCR_RE );
            break;

        case HAL_LL_UART_ENABLE:
            set_reg_bit( &hal_ll_hw_reg->scr, HAL_LL_SCI_SCR_RE );
            break;

        default:
            break;
    }
}

static void hal_ll_uart_clear_regs( hal_ll_uart_base_handle_t *hal_ll_hw_reg ) {
    clear_reg( &hal_ll_hw_reg->scr );
    while ( read_reg( &hal_ll_hw_reg->scr ));
    clear_reg( &hal_ll_hw_reg->smr );
    clear_reg( &hal_ll_hw_reg->ssr );
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

    hal_ll_uart_hw_init( map );
}

// ------------------------------------------------------------------------- END
