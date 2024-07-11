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

#include "hal_ll_pps.h"
#include "hal_ll_gpio.h"
#include "hal_ll_core.h"
#include "hal_ll_uart.h"
#include "hal_ll_core_macros.h"
#include "hal_ll_uart_pin_map.h"
#include "assembly.h"

/*!< @brief Local handle list */
static volatile hal_ll_uart_handle_register_t hal_ll_module_state[UART_MODULE_COUNT] = { ( handle_t *)NULL, ( handle_t *)NULL, false };

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

/*!< @brief Macros used for calculating actual baud rate value and error value */
#define HAL_LL_UART_ACCEPTABLE_ERROR (float)1.0
#define hal_ll_get_system_clock (Get_Fosc_kHz()*1000)
#define hal_ll_get_system_clock_per_instruction (Get_Fosc_kHz()*1000/Get_Fosc_Per_Cyc())
#define hal_ll_uart_get_baud_prescaler_1(_baud) (_baud<<(4+Get_Fosc_Per_Cyc()/2))
#define hal_ll_uart_get_baud_prescaler_2(_prescaler_1) (hal_ll_get_system_clock%_prescaler_1)
#define hal_ll_uart_get_baud(_prescaler_1) (hal_ll_get_system_clock/_prescaler_1)
#define hal_ll_uart_get_real_baud(_clock,_baud,_div) (_clock/(_div*(_baud+1)))
#define hal_ll_uart_get_baud_error(_baud_real,_baud) (((float)(abs(_baud_real-_baud))/_baud))

/*!< @brief Macros defining register bits */
#define HAL_LL_UART_ENABLE_BIT                  0x000F
#define HAL_LL_RECEIVE_ENABLE_BIT               0x000C
#define HAL_LL_ALTERNATE_PINS_ENABLE_BIT        0x000A
#define HAL_LL_TRANSMIT_ENABLE_BIT              0x000A
#define HAL_LL_TRANSMIT_SHIFT_REGISTER_BIT      0x0008
#define HAL_LL_RECEIVE_BUF_OVERRUN_ERROR_BIT    0x0001
#define HAL_LL_RECIEVE_BUF_DATA_AVAILABLE_BIT   0x0000
#define HAL_LL_STOP_SELECTION_BIT               0x0000

#define HAL_LL_PARITY_BIT_MASK_9_NO_PARITY      0x0006
#define HAL_LL_PARITY_BIT_MASK_8_ODD_PARITY     0x0004
#define HAL_LL_PARITY_BIT_MASK_8_EVEN_PARITY    0x0002

#define HAL_LL_PARITY_ERROR_BIT                 0x0003
#define HAL_LL_FRAMING_ERROR_BIT                0x0002

// ------------------------------------------------------------------ TYPEDEFS
/*!< @brief UART HW register structure */
typedef struct
{
    hal_ll_base_addr_t uart_mode_reg_addr;
    hal_ll_base_addr_t uart_sta_reg_addr;
    hal_ll_base_addr_t uart_tx_reg_addr;
    hal_ll_base_addr_t uart_rx_reg_addr;
    hal_ll_base_addr_t uart_brg_reg_addr;
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
    const hal_ll_uart_base_handle_t *base;
    hal_ll_pin_name_t module_index;
    hal_ll_uart_pins_t pins;
    hal_ll_uart_baud_t baud_rate;
    hal_ll_uart_parity_t parity;
    hal_ll_uart_stop_bits_t stop_bit;
    hal_ll_uart_data_bits_t data_bit;
    bool alternate_pins;
    uint8_t hal_ll_pps_module_index;
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

    HAL_LL_UART_ERROR = ( -1 )
} hal_ll_uart_err_t;

/*!< @brief UART module state selection */
typedef enum
{
    HAL_LL_UART_DISABLE = 0,
    HAL_LL_UART_ENABLE
} hal_ll_uart_state_t;

// ------------------------------------------------------------------ CONSTANTS
/*!< @brief UART modules register array */
static const hal_ll_uart_base_handle_t hal_ll_uart_regs[] =
{
    #ifdef UART_MODULE_1
    { HAL_LL_U1MODE_REG_ADDRESS, HAL_LL_U1STA_REG_ADDRESS, HAL_LL_U1TXREG_REG_ADDRESS, HAL_LL_U1RXREG_REG_ADDRESS, HAL_LL_U1BRG_REG_ADDRESS },
    #endif
    #ifdef UART_MODULE_2
    { HAL_LL_U2MODE_REG_ADDRESS, HAL_LL_U2STA_REG_ADDRESS, HAL_LL_U2TXREG_REG_ADDRESS, HAL_LL_U2RXREG_REG_ADDRESS, HAL_LL_U2BRG_REG_ADDRESS },
    #endif
    #ifdef UART_MODULE_3
    { HAL_LL_U3MODE_REG_ADDRESS, HAL_LL_U3STA_REG_ADDRESS, HAL_LL_U3TXREG_REG_ADDRESS, HAL_LL_U3RXREG_REG_ADDRESS, HAL_LL_U3BRG_REG_ADDRESS },
    #endif
    #ifdef UART_MODULE_4
    { HAL_LL_U4MODE_REG_ADDRESS, HAL_LL_U4STA_REG_ADDRESS, HAL_LL_U4TXREG_REG_ADDRESS, HAL_LL_U4RXREG_REG_ADDRESS, HAL_LL_U4BRG_REG_ADDRESS },
    #endif
    #ifdef UART_MODULE_5
    { HAL_LL_U5MODE_REG_ADDRESS, HAL_LL_U5STA_REG_ADDRESS, HAL_LL_U5TXREG_REG_ADDRESS, HAL_LL_U5RXREG_REG_ADDRESS, HAL_LL_U5BRG_REG_ADDRESS },
    #endif
    #ifdef UART_MODULE_6
    { HAL_LL_U6MODE_REG_ADDRESS, HAL_LL_U6STA_REG_ADDRESS, HAL_LL_U6TXREG_REG_ADDRESS, HAL_LL_U6RXREG_REG_ADDRESS, HAL_LL_U6BRG_REG_ADDRESS },
    #endif

    { HAL_LL_MODULE_ERROR, HAL_LL_MODULE_ERROR, HAL_LL_MODULE_ERROR, HAL_LL_MODULE_ERROR, HAL_LL_MODULE_ERROR }
};

// ------------------------------------------------------------------ VARIABLES
/*!< @brief Global handle variables used in functions */
static volatile hal_ll_uart_handle_register_t *low_level_handle;
static volatile hal_ll_uart_hw_specifics_map_t *hal_ll_uart_hw_specifics_map_local;

/*!< @brief Global interrupt handlers used in functions */
static hal_ll_uart_isr_t irq_handler;
static handle_t objects[UART_MODULE_COUNT] = { NULL };
uint8_t hal_ll_module_num;

/*!< @brief UART hardware specific info */
static hal_ll_uart_hw_specifics_map_t hal_ll_uart_hw_specifics_map[] =
{
    #ifdef UART_MODULE_1
    { &hal_ll_uart_regs[hal_ll_uart_module_num( UART_MODULE_1 )], hal_ll_uart_module_num( UART_MODULE_1 ), { HAL_LL_PIN_NC, HAL_LL_PIN_NC }, { 115200, 0 }, 0, UART_MODULE_1 },
    #endif
    #ifdef UART_MODULE_2
    { &hal_ll_uart_regs[hal_ll_uart_module_num( UART_MODULE_2 )], hal_ll_uart_module_num( UART_MODULE_2 ), { HAL_LL_PIN_NC, HAL_LL_PIN_NC }, { 115200, 0 }, 0, UART_MODULE_2 },
    #endif
    #ifdef UART_MODULE_3
    { &hal_ll_uart_regs[hal_ll_uart_module_num( UART_MODULE_3 )], hal_ll_uart_module_num( UART_MODULE_3), { HAL_LL_PIN_NC, HAL_LL_PIN_NC }, { 115200, 0 }, 0, UART_MODULE_3 },
    #endif
    #ifdef UART_MODULE_4
    { &hal_ll_uart_regs[hal_ll_uart_module_num( UART_MODULE_4 )], hal_ll_uart_module_num( UART_MODULE_4 ), { HAL_LL_PIN_NC, HAL_LL_PIN_NC }, { 115200, 0 }, 0, UART_MODULE_4 },
    #endif
    #ifdef UART_MODULE_5
    { &hal_ll_uart_regs[hal_ll_uart_module_num( UART_MODULE_5 )], hal_ll_uart_module_num( UART_MODULE_5 ), { HAL_LL_PIN_NC, HAL_LL_PIN_NC }, { 115200, 0 }, 0, UART_MODULE_5 },
    #endif
    #ifdef UART_MODULE_6
    { &hal_ll_uart_regs[hal_ll_uart_module_num( UART_MODULE_6 )], hal_ll_uart_module_num( UART_MODULE_6 ), { HAL_LL_PIN_NC, HAL_LL_PIN_NC }, { 115200, 0 }, 0, UART_MODULE_6 },
    #endif

    { HAL_LL_MODULE_ERROR, HAL_LL_MODULE_ERROR, { HAL_LL_PIN_NC, HAL_LL_PIN_NC }, { 0, 0 }, 0, 0 }
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
static hal_ll_uart_hw_specifics_map_t *hal_ll_get_specifics( handle_t handle );

/**
  * @brief  Sets pin state.
  *
  * The following function sets TRIS and
  * ANSEL/ADCON/ANCON values for adequate pins.
  *
  * @param[in]  map - Object specific context handler.
  *
  * @return None
  */
static void hal_ll_uart_hw_ansel_set( hal_ll_uart_hw_specifics_map_t *map );

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
static void hal_ll_uart_clear_regs( const hal_ll_uart_base_handle_t *reg_addresses );

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
static void hal_ll_uart_set_module( const hal_ll_uart_base_handle_t *reg_addresses, hal_ll_uart_state_t pin_state );

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
static void hal_ll_uart_set_transmitter( const hal_ll_uart_base_handle_t *reg_addresses, hal_ll_uart_state_t pin_state );

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
static void hal_ll_uart_set_receiver( const hal_ll_uart_base_handle_t *reg_addresses, hal_ll_uart_state_t pin_state );

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

    if ( ( hal_ll_uart_hw_specifics_map[pin_check_result].pins.tx_pin != tx_pin ) ||
         ( hal_ll_uart_hw_specifics_map[pin_check_result].pins.rx_pin != rx_pin ) )
    {
        // Used only for chips which have UART PPS pins
        #if HAL_LL_UART_PPS_ENABLED == true
        if ( hal_ll_pps_set_state( &hal_ll_uart_hw_specifics_map[ pin_check_result ], false ) != HAL_LL_UART_SUCCESS )
            return HAL_LL_UART_WRONG_PINS;
        #endif

        hal_ll_uart_map_pins( pin_check_result, &index_list );

        // Used only for chips which have UART PPS pins
        #if HAL_LL_UART_PPS_ENABLED == true
        if ( hal_ll_pps_set_state( &hal_ll_uart_hw_specifics_map[ pin_check_result ], true ) != HAL_LL_UART_SUCCESS )
            return HAL_LL_UART_WRONG_PINS;
        #endif

        handle_map[pin_check_result].init_ll_state = false;
    }

    *hal_module_id = pin_check_result;

    hal_ll_module_state[pin_check_result].hal_ll_uart_handle = ( handle_t *)&hal_ll_uart_hw_specifics_map[pin_check_result].base;

    handle_map[pin_check_result].hal_ll_uart_handle = ( handle_t *)&hal_ll_module_state[pin_check_result].hal_ll_uart_handle;

    hal_ll_module_num = pin_check_result;

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

    hal_ll_uart_hw_specifics_map_local = hal_ll_get_specifics( hal_ll_uart_get_module_state_address );

    low_level_handle->init_ll_state = false;

    hal_ll_uart_hw_specifics_map_local->baud_rate.baud = baud;

    hal_ll_uart_init( hal_ll_uart_hw_specifics_map_local );

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
    hal_ll_uart_hw_specifics_map_local = hal_ll_get_specifics( hal_ll_uart_get_module_state_address );

    if( low_level_handle->hal_ll_uart_handle != NULL ) {
        hal_ll_uart_irq_disable( handle, HAL_LL_UART_IRQ_RX );
        hal_ll_uart_irq_disable( handle, HAL_LL_UART_IRQ_TX );

        hal_ll_uart_clear_regs( hal_ll_uart_hw_specifics_map_local->base );

        hal_ll_uart_hw_specifics_map_local->pins.tx_pin = HAL_LL_PIN_NC;
        hal_ll_uart_hw_specifics_map_local->pins.rx_pin = HAL_LL_PIN_NC;

        hal_ll_uart_hw_specifics_map_local->baud_rate.baud = 115200UL;
        hal_ll_uart_hw_specifics_map_local->baud_rate.real_baud = 0;

        irq_handler = NULL;
        objects[hal_ll_uart_find_index( handle )] = NULL;

        low_level_handle->hal_ll_uart_handle = NULL;
        low_level_handle->hal_drv_uart_handle = NULL;

        low_level_handle->init_ll_state = false;
    }
}

void hal_ll_uart_register_irq_handler( handle_t *handle, hal_ll_uart_isr_t handler, handle_t obj ) {
    irq_handler = handler;
    objects[hal_ll_uart_find_index( handle )] = obj;
}

void hal_ll_uart_irq_enable( handle_t *handle, hal_ll_uart_irq_t irq ) {
    hal_ll_uart_hw_specifics_map_local = hal_ll_get_specifics( hal_ll_uart_get_module_state_address );
    hal_ll_module_num = hal_ll_uart_hw_specifics_map_local->module_index;

    switch ( irq )
    {
        case HAL_LL_UART_IRQ_RX:
            hal_ll_core_enable_irq( HAL_LL_UART_IRQ_RX );
            break;
        case HAL_LL_UART_IRQ_TX:
            hal_ll_core_enable_irq( HAL_LL_UART_IRQ_TX );
            break;

        default:
            break;
    }
}
void hal_ll_uart_irq_disable( handle_t *handle, hal_ll_uart_irq_t irq ) {
    hal_ll_uart_hw_specifics_map_local = hal_ll_get_specifics( hal_ll_uart_get_module_state_address );
    hal_ll_module_num = hal_ll_uart_hw_specifics_map_local->module_index;

    switch ( irq )
    {
        case HAL_LL_UART_IRQ_RX:
            hal_ll_core_disable_irq( HAL_LL_UART_IRQ_RX );
            break;

        case HAL_LL_UART_IRQ_TX:
            hal_ll_core_disable_irq( HAL_LL_UART_IRQ_TX );
            break;

        default:
            break;
    }
}

void hal_ll_uart_write( handle_t *handle, uint8_t wr_data ) {
    const hal_ll_uart_base_handle_t *reg_addresses = hal_ll_uart_get_base_handle;

    while ( !check_reg_bit( reg_addresses->uart_sta_reg_addr, HAL_LL_TRANSMIT_SHIFT_REGISTER_BIT ) );

    write_reg( reg_addresses->uart_tx_reg_addr, wr_data );
}

uint8_t hal_ll_uart_read( handle_t *handle ) {
    const hal_ll_uart_base_handle_t *reg_addresses = hal_ll_uart_get_base_handle;
    uint8_t rd_data;

    rd_data = read_reg( reg_addresses->uart_rx_reg_addr );

    /**
     * We are checking if there are any characters left in the
     * receive buffer before we clear the overrun flag if it is present.
     */
    if ( !check_reg_bit( reg_addresses->uart_sta_reg_addr, HAL_LL_RECIEVE_BUF_DATA_AVAILABLE_BIT ) ) {
        if ( check_reg_bit( reg_addresses->uart_sta_reg_addr, HAL_LL_RECEIVE_BUF_OVERRUN_ERROR_BIT ) )
            clear_reg_bit( reg_addresses->uart_sta_reg_addr, HAL_LL_RECEIVE_BUF_OVERRUN_ERROR_BIT );
    }

    /**
     * Returning 0 if any error ocurred, otherwise
     * returning the read data.
     */
    if ( check_reg_bit( reg_addresses->uart_sta_reg_addr, HAL_LL_FRAMING_ERROR_BIT ) || check_reg_bit( reg_addresses->uart_sta_reg_addr, HAL_LL_PARITY_ERROR_BIT ) )
        return 0;

    return rd_data;
}

// ------------------------------------------------------------- DEFAULT EXCEPTION HANDLERS
/*!< @brief Link handler from HAL layer */
void hal_uart_irq_handler( handle_t obj, hal_ll_uart_irq_t event );

// Interrupt Routine Service for UART_1
#ifdef UART_MODULE_1
void MARK_AS_IRQ_HANDLER _U1RXInterrupt(void) MIKROC_IV(USART1_RX_IVT_ADDRESS) {
    if ( check_reg_bit(UART1_INTERRUPT_CONTROL_REG_IFS_RX, UART1_INTERRUPT_CONTROL_BIT_RX) ) {
        clear_reg_bit(UART1_INTERRUPT_CONTROL_REG_IFS_RX, UART1_INTERRUPT_CONTROL_BIT_RX);
        irq_handler( objects[hal_ll_uart_module_num( UART_MODULE_1 )], HAL_LL_UART_IRQ_RX );
    }
}

void MARK_AS_IRQ_HANDLER _U1TXInterrupt(void) MIKROC_IV(USART1_TX_IVT_ADDRESS) {
    if ( check_reg_bit(UART1_INTERRUPT_CONTROL_REG_IFS_TX, UART1_INTERRUPT_CONTROL_BIT_TX) ) {
        clear_reg_bit(UART1_INTERRUPT_CONTROL_REG_IFS_TX, UART1_INTERRUPT_CONTROL_BIT_TX);
        irq_handler( objects[hal_ll_uart_module_num( UART_MODULE_1 )], HAL_LL_UART_IRQ_TX );
    }
}
#endif
// EOF Interrupt Routine Service for UART_1

// Interrupt Routine Service for UART_2
#ifdef UART_MODULE_2
void MARK_AS_IRQ_HANDLER _U2RXInterrupt(void) MIKROC_IV(USART2_RX_IVT_ADDRESS) {
    if ( check_reg_bit(UART2_INTERRUPT_CONTROL_REG_IFS_RX, UART2_INTERRUPT_CONTROL_BIT_RX) ) {
        clear_reg_bit(UART2_INTERRUPT_CONTROL_REG_IFS_RX, UART2_INTERRUPT_CONTROL_BIT_RX);
        irq_handler( objects[hal_ll_uart_module_num( UART_MODULE_2 )], HAL_LL_UART_IRQ_RX );
    }
}

void MARK_AS_IRQ_HANDLER _U2TXInterrupt(void) MIKROC_IV(USART2_TX_IVT_ADDRESS) {
    if ( check_reg_bit(UART2_INTERRUPT_CONTROL_REG_IFS_TX, UART2_INTERRUPT_CONTROL_BIT_TX) ) {
        clear_reg_bit(UART2_INTERRUPT_CONTROL_REG_IFS_TX, UART2_INTERRUPT_CONTROL_BIT_TX);
        irq_handler( objects[hal_ll_uart_module_num( UART_MODULE_2 )], HAL_LL_UART_IRQ_TX );
    }
}
#endif
// EOF Interrupt Routine Service for UART_2

// Interrupt Routine Service for UART_3
#ifdef UART_MODULE_3
void  MARK_AS_IRQ_HANDLER _U3RXInterrupt(void) MIKROC_IV(USART3_RX_IVT_ADDRESS) {
    if ( check_reg_bit(UART3_INTERRUPT_CONTROL_REG_IFS_RX, UART3_INTERRUPT_CONTROL_BIT_RX) ) {
        clear_reg_bit(UART3_INTERRUPT_CONTROL_REG_IFS_RX, UART3_INTERRUPT_CONTROL_BIT_RX);
        irq_handler( objects[hal_ll_uart_module_num( UART_MODULE_3 )], HAL_LL_UART_IRQ_RX );
    }
}

void  MARK_AS_IRQ_HANDLER _U3TXInterrupt(void) MIKROC_IV(USART3_TX_IVT_ADDRESS) {
    if ( check_reg_bit(UART3_INTERRUPT_CONTROL_REG_IFS_TX, UART3_INTERRUPT_CONTROL_BIT_TX) ) {
        clear_reg_bit(UART3_INTERRUPT_CONTROL_REG_IFS_TX, UART3_INTERRUPT_CONTROL_BIT_TX);
        irq_handler( objects[hal_ll_uart_module_num( UART_MODULE_3 )], HAL_LL_UART_IRQ_TX );
    }
}
#endif
// EOF Interrupt Routine Service for UART_3

// Interrupt Routine Service for UART_4
#ifdef UART_MODULE_4
void  MARK_AS_IRQ_HANDLER _U4RXInterrupt(void) MIKROC_IV(USART4_RX_IVT_ADDRESS) {
    if ( check_reg_bit(UART4_INTERRUPT_CONTROL_REG_IFS_RX, UART4_INTERRUPT_CONTROL_BIT_RX) ) {
        clear_reg_bit(UART4_INTERRUPT_CONTROL_REG_IFS_RX, UART4_INTERRUPT_CONTROL_BIT_RX);
        irq_handler( objects[hal_ll_uart_module_num( UART_MODULE_4 )], HAL_LL_UART_IRQ_RX );
    }
}

void  MARK_AS_IRQ_HANDLER _U4TXInterrupt(void) MIKROC_IV(USART4_TX_IVT_ADDRESS) {
    if ( check_reg_bit(UART4_INTERRUPT_CONTROL_REG_IFS_TX, UART4_INTERRUPT_CONTROL_BIT_TX) ) {
        clear_reg_bit(UART4_INTERRUPT_CONTROL_REG_IFS_TX, UART4_INTERRUPT_CONTROL_BIT_TX);
        irq_handler( objects[hal_ll_uart_module_num( UART_MODULE_4 )], HAL_LL_UART_IRQ_TX );
    }
}
#endif
// EOF Interrupt Routine Service for UART_4

// Interrupt Routine Service for UART_5
#ifdef UART_MODULE_5
void  MARK_AS_IRQ_HANDLER _U5RXInterrupt(void) MIKROC_IV(USART5_RX_IVT_ADDRESS) {
    if ( check_reg_bit(UART5_INTERRUPT_CONTROL_REG_IFS_RX, UART5_INTERRUPT_CONTROL_BIT_RX) ) {
        clear_reg_bit(UART5_INTERRUPT_CONTROL_REG_IFS_RX, UART5_INTERRUPT_CONTROL_BIT_RX);
        irq_handler( objects[hal_ll_uart_module_num( UART_MODULE_5 )], HAL_LL_UART_IRQ_RX );
    }
}

void  MARK_AS_IRQ_HANDLER _U5TXInterrupt(void) MIKROC_IV(USART5_TX_IVT_ADDRESS) {
    if ( check_reg_bit(UART5_INTERRUPT_CONTROL_REG_IFS_TX, UART5_INTERRUPT_CONTROL_BIT_TX) ) {
        clear_reg_bit(UART5_INTERRUPT_CONTROL_REG_IFS_TX, UART5_INTERRUPT_CONTROL_BIT_TX);
        irq_handler( objects[hal_ll_uart_module_num( UART_MODULE_5 )], HAL_LL_UART_IRQ_TX );
    }
}
#endif
// EOF Interrupt Routine Service for UART_5

// Interrupt Routine Service for UART_6
#ifdef UART_MODULE_6
void  MARK_AS_IRQ_HANDLER _U6RXInterrupt(void) MIKROC_IV(USART6_RX_IVT_ADDRESS) {
    if ( check_reg_bit(UART6_INTERRUPT_CONTROL_REG_IFS_RX, UART6_INTERRUPT_CONTROL_BIT_RX) ) {
        clear_reg_bit(UART6_INTERRUPT_CONTROL_REG_IFS_RX, UART6_INTERRUPT_CONTROL_BIT_RX);
        irq_handler( objects[hal_ll_uart_module_num( UART_MODULE_6 )], HAL_LL_UART_IRQ_RX );
    }
}

void  MARK_AS_IRQ_HANDLER _U6TXInterrupt(void) MIKROC_IV(USART6_TX_IVT_ADDRESS) {
    if ( check_reg_bit(UART6_INTERRUPT_CONTROL_REG_IFS_TX, UART6_INTERRUPT_CONTROL_BIT_TX) ) {
        clear_reg_bit(UART6_INTERRUPT_CONTROL_REG_IFS_TX, UART6_INTERRUPT_CONTROL_BIT_TX);
        irq_handler( objects[hal_ll_uart_module_num( UART_MODULE_6 )], HAL_LL_UART_IRQ_TX );
    }
}
#endif
// EOF Interrupt Routine Service for UART_6

// ----------------------------------------------- PRIVATE FUNCTION DEFINITIONS
static uint8_t hal_ll_uart_find_index( handle_t *handle ) {
    hal_ll_uart_hw_specifics_map_local = hal_ll_get_specifics( hal_ll_uart_get_module_state_address );

    if( hal_ll_uart_hw_specifics_map_local->base->uart_sta_reg_addr != HAL_LL_MODULE_ERROR ) {
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

    for ( tx_index = 0; tx_index < tx_map_size; tx_index++ ) {
        if ( hal_ll_uart_tx_map[tx_index].pin == tx_pin ) {
            for ( rx_index = 0; rx_index < rx_map_size; rx_index++ ) {
                if ( hal_ll_uart_rx_map[rx_index].pin == rx_pin ) {
                    if ( hal_ll_uart_tx_map[tx_index].module_index == hal_ll_uart_rx_map[rx_index].module_index ) {
                        // Get module number
                        hal_ll_module_id = hal_ll_uart_tx_map[tx_index].module_index;

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

static hal_ll_uart_hw_specifics_map_t *hal_ll_get_specifics( handle_t handle ) {
    uint8_t hal_ll_module_count = sizeof( hal_ll_module_state ) / (sizeof( hal_ll_uart_handle_register_t ) );
    static uint8_t hal_ll_module_error = sizeof( hal_ll_module_state ) / (sizeof( hal_ll_uart_handle_register_t ) );

    while( hal_ll_module_count-- ) {
        if ( hal_ll_uart_get_base_from_hal_handle == hal_ll_uart_hw_specifics_map[hal_ll_module_count].base ) {
            return &hal_ll_uart_hw_specifics_map[hal_ll_module_count];
        }
    }

    return &hal_ll_uart_hw_specifics_map[hal_ll_module_error];
}

static void hal_ll_uart_map_pins( uint8_t module_index, hal_ll_uart_pin_id *index_list ) {
    // Map new pins
    hal_ll_uart_hw_specifics_map[module_index].pins.tx_pin = hal_ll_uart_tx_map[index_list[module_index].pin_tx].pin;
    hal_ll_uart_hw_specifics_map[module_index].pins.rx_pin = hal_ll_uart_rx_map[index_list[module_index].pin_rx].pin;
    hal_ll_uart_hw_specifics_map[module_index].hal_ll_pps_module_index = hal_ll_uart_rx_map[index_list[module_index].pin_rx].module_index;
    // Get information about alternativity of the pins
    hal_ll_uart_hw_specifics_map[module_index].alternate_pins = hal_ll_uart_tx_map[index_list[module_index].pin_tx].alternate_pins;
}

static void hal_ll_uart_set_baud_bare_metal( hal_ll_uart_hw_specifics_map_t *map ) {
    static uint8_t div_value = 16;
    const hal_ll_uart_base_handle_t *reg_addresses = hal_ll_uart_hw_specifics_map_local->base;
    uint32_t baud_prescaler_1 = hal_ll_uart_get_baud_prescaler_1( map->baud_rate.baud );
    uint32_t baud_prescaler_2 = hal_ll_uart_get_baud_prescaler_2( baud_prescaler_1 );
    uint32_t hal_ll_baud_value = hal_ll_uart_get_baud( baud_prescaler_1 );
    uint32_t hal_ll_baud_rate;

    // Additional check to reduce the error
    if ( baud_prescaler_2 > ( baud_prescaler_1 >> 1 ) )
        hal_ll_baud_value++;

    hal_ll_baud_rate = hal_ll_uart_get_real_baud( hal_ll_get_system_clock_per_instruction, --hal_ll_baud_value, div_value );

    // If error greater than specified, cancel setting baud rate
    if( HAL_LL_UART_ACCEPTABLE_ERROR < (float)hal_ll_uart_get_baud_error( hal_ll_baud_rate, map->baud_rate.baud ) ) {
        map->baud_rate.real_baud = hal_ll_uart_get_baud_error( hal_ll_baud_rate, map->baud_rate.baud );
    } else {
        map->baud_rate.real_baud = hal_ll_baud_rate;

        write_reg( reg_addresses->uart_brg_reg_addr, hal_ll_baud_value );
    }
}

static void hal_ll_uart_set_module( const hal_ll_uart_base_handle_t *reg_addresses, hal_ll_uart_state_t pin_state ) {
    // If pins are alternative then configure the module in appropriate way
    if ( hal_ll_uart_hw_specifics_map_local->alternate_pins )
        set_reg_bit( reg_addresses->uart_mode_reg_addr, HAL_LL_ALTERNATE_PINS_ENABLE_BIT );

    switch ( pin_state )
    {
        case HAL_LL_UART_DISABLE:
            clear_reg_bit( reg_addresses->uart_mode_reg_addr, HAL_LL_UART_ENABLE_BIT );
            break;

        case HAL_LL_UART_ENABLE:
            set_reg_bit( reg_addresses->uart_mode_reg_addr, HAL_LL_UART_ENABLE_BIT );
            break;
        default:
            break;
    }
}

static void hal_ll_uart_set_parity_bare_metal( hal_ll_uart_hw_specifics_map_t *map ) {
    const hal_ll_uart_base_handle_t *reg_addresses = hal_ll_uart_get_base_struct( map->base );

    switch ( map->parity )
    {
        case HAL_LL_UART_PARITY_NONE:
            clear_reg_bits( reg_addresses->uart_mode_reg_addr, HAL_LL_PARITY_BIT_MASK_9_NO_PARITY );
            break;

        case HAL_LL_UART_PARITY_EVEN:
            set_reg_bits( reg_addresses->uart_mode_reg_addr, HAL_LL_PARITY_BIT_MASK_8_EVEN_PARITY );
            break;

        case HAL_LL_UART_PARITY_ODD:
            set_reg_bits( reg_addresses->uart_mode_reg_addr, HAL_LL_PARITY_BIT_MASK_8_ODD_PARITY );
            break;

        default:
            break;
    }
}

static void hal_ll_uart_set_stop_bits_bare_metal( hal_ll_uart_hw_specifics_map_t *map ) {
    const hal_ll_uart_base_handle_t *reg_addresses = hal_ll_uart_get_base_struct( map->base );

    switch ( map->stop_bit )
    {
        case HAL_LL_UART_STOP_BITS_ONE:
            clear_reg_bit( reg_addresses->uart_mode_reg_addr, HAL_LL_STOP_SELECTION_BIT );
            break;

        case HAL_LL_UART_STOP_BITS_TWO:
            set_reg_bit( reg_addresses->uart_mode_reg_addr, HAL_LL_STOP_SELECTION_BIT );
            break;

        default:
            break;
    }
}

static void hal_ll_uart_set_data_bits_bare_metal( hal_ll_uart_hw_specifics_map_t *map ) {
    const hal_ll_uart_base_handle_t *reg_addresses = hal_ll_uart_get_base_struct( map->base );

    switch ( map->data_bit )
    {
        case HAL_LL_UART_DATA_BITS_9:
            set_reg_bits( reg_addresses->uart_mode_reg_addr, HAL_LL_PARITY_BIT_MASK_9_NO_PARITY );
            break;

        default:
            break;
    }
}

static void hal_ll_uart_set_transmitter( const hal_ll_uart_base_handle_t *reg_addresses, hal_ll_uart_state_t pin_state ) {
    switch ( pin_state )
    {
        case HAL_LL_UART_DISABLE:
            clear_reg_bit( reg_addresses->uart_mode_reg_addr, HAL_LL_TRANSMIT_ENABLE_BIT );
            break;

        case HAL_LL_UART_ENABLE:
            set_reg_bit( reg_addresses->uart_sta_reg_addr, HAL_LL_TRANSMIT_ENABLE_BIT );
            break;

        default:
            break;
    }
}

static void hal_ll_uart_set_receiver( const hal_ll_uart_base_handle_t *reg_addresses, hal_ll_uart_state_t pin_state ) {
    /**
     * @brief Enable receiving.
     *
     * For some MCUs this bit is not implemented,
     * but some MCUs need this bit to be set in order
     * to receive the data.
     */
    set_reg_bit( reg_addresses->uart_sta_reg_addr, HAL_LL_RECEIVE_ENABLE_BIT );
}

static void hal_ll_uart_clear_regs( const hal_ll_uart_base_handle_t *reg_addresses ) {
    clear_reg( reg_addresses->uart_mode_reg_addr );
    clear_reg( reg_addresses->uart_sta_reg_addr );
    clear_reg( reg_addresses->uart_brg_reg_addr );
}

static void hal_ll_uart_hw_ansel_set( hal_ll_uart_hw_specifics_map_t *map ) {
    hal_ll_gpio_pin_t local_pin;

    /*
     * Configures TX and RX pins as output/input by clearing/setting
     * corresponding TRIS bits.
     */
    hal_ll_gpio_configure_pin( &local_pin, map->pins.rx_pin, HAL_LL_GPIO_DIGITAL_INPUT );
    hal_ll_gpio_configure_pin( &local_pin, map->pins.tx_pin, HAL_LL_GPIO_DIGITAL_OUTPUT );
}

static hal_ll_pps_err_t hal_ll_pps_set_state( hal_ll_uart_hw_specifics_map_t *map, bool hal_ll_state ) {
    hal_ll_pps_err_t hal_ll_status = HAL_LL_PPS_SUCCESS;

    if ( HAL_LL_PIN_NC != map->pins.tx_pin ) {
        hal_ll_status = hal_ll_pps_map( ( map->pins.tx_pin & HAL_LL_NIBBLE_HIGH_8BIT ) >> 4, map->pins.tx_pin & HAL_LL_NIBBLE_LOW_8BIT, HAL_LL_GPIO_DIGITAL_OUTPUT,
                                                HAL_LL_PPS_FUNCTIONALITY_UART, map->hal_ll_pps_module_index, hal_ll_state );

        if ( hal_ll_status != HAL_LL_UART_SUCCESS )
            return hal_ll_status;

        // Check status manually if needed
        hal_ll_status = hal_ll_pps_map( ( map->pins.rx_pin & HAL_LL_NIBBLE_HIGH_8BIT ) >> 4, map->pins.rx_pin & HAL_LL_NIBBLE_LOW_8BIT,
                                        HAL_LL_GPIO_DIGITAL_INPUT, HAL_LL_PPS_FUNCTIONALITY_UART, map->hal_ll_pps_module_index, hal_ll_state );

        return hal_ll_status;
    } else {
        return HAL_LL_UART_SUCCESS;
    }
}

static void hal_ll_uart_hw_init( hal_ll_uart_hw_specifics_map_t *map ) {
    hal_ll_uart_clear_regs( map->base );

    hal_ll_uart_set_baud_bare_metal( map );

    hal_ll_uart_set_module( map->base, HAL_LL_UART_ENABLE );

    hal_ll_uart_set_parity_bare_metal( map );

    hal_ll_uart_set_stop_bits_bare_metal( map );

    hal_ll_uart_set_data_bits_bare_metal( map );

    hal_ll_uart_set_receiver( map->base, HAL_LL_UART_ENABLE );

    hal_ll_uart_set_transmitter( map->base, HAL_LL_UART_ENABLE );
}

static void hal_ll_uart_init( hal_ll_uart_hw_specifics_map_t *map ) {
    static uint32_t hal_ll_clock_value;

    hal_ll_clock_value = Get_Fosc_kHz();

    hal_ll_uart_hw_ansel_set( map );

    #if HAL_LL_UART_PPS_ENABLED == true
    // Set pps functions for mapped pins
    hal_ll_pps_set_state( map, true );
    #endif

    hal_ll_uart_hw_init( map );

    hal_ll_uart_wait_for_sync( hal_ll_clock_value );
}

// ------------------------------------------------------------------------- END
