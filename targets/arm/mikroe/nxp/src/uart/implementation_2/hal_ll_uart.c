/****************************************************************************
**
** Copyright (C) 2022 MikroElektronika d.o.o.
** Contact: https://www.mikroe.com/contact
**
** This file is part of the mikroSDK package
**
** Commercial License Usage
**
** Licensees holding valid commercial NECTO compilers AI licenses may use this
** file in accordance with the commercial license agreement provided with the
** Software or, alternatively, in accordance with the terms contained in
** a written agreement between you and The mikroElektronika Company.
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

#include "hal_ll_rcc.h"
#include "hal_ll_uart.h"
#include "hal_ll_gpio.h"
#include "hal_ll_core.h"
#include "hal_ll_core_defines.h"
#include "hal_ll_uart_pin_map.h"

/*!< @brief Local handle list */
static volatile hal_ll_uart_handle_register_t hal_ll_module_state[UART_MODULE_COUNT] = { (handle_t *)NULL, (handle_t *)NULL, false };

// ------------------------------------------------------------- PRIVATE MACROS
/*!< @brief Helper macro for getting hal_ll_module_state address */
#define hal_ll_uart_get_module_state_address ((hal_ll_uart_handle_register_t *)*handle)
/*!< @brief Helper macro for getting module specific control register structure base address // first register address */
#define hal_ll_uart_get_handle (hal_ll_uart_handle_register_t *)hal_ll_uart_get_module_state_address->hal_ll_uart_handle
/*!< @brief Helper macro for getting module specific control register structure */
#define hal_ll_uart_get_base_struct(_handle) ((hal_ll_uart_base_handle_t *)_handle)
/*!< @brief Helper macro for getting module specific base address directly from HAL layer handle */
#define hal_ll_uart_get_base_from_hal_handle ((hal_ll_uart_hw_specifics_map_t *)((hal_ll_uart_handle_register_t *)\
                                             (((hal_ll_uart_handle_register_t *)(handle))->hal_ll_uart_handle))->hal_ll_uart_handle)->base

#define hal_ll_uart_get_status_flags(_handle,_flag) (((hal_ll_uart_base_handle_t *)_handle)->stat & _flag)
#define hal_ll_uart_clear_status_flag(_handle,_flag) (clear_reg_bit( &(((hal_ll_uart_base_handle_t *)_handle)->stat), ( _flag & HAL_LL_UART_IT_CLEAR_MASK ) ) )

// Baud rate
#define HAL_LL_UART_ACCEPTABLE_ERROR (float)1.0
#define hal_ll_uart_get_baud(_clock,_baud,_div) (((_clock/(float)_baud)/_div)-1)
#define hal_ll_uart_get_real_baud(_clock,_baud,_div) (_clock/(_div*(_baud+1)))
#define hal_ll_uart_get_baud_error(_baud_real,_baud) (((float)(abs(_baud_real-_baud))/_baud)*100)

#define HAL_LL_UART_AF_CONFIG GPIO_CFG_MODE_ALT_FUNCTION

#define HAL_LL_UART_STAT_RDRF_FLAG     ( 1U << 21 )
#define HAL_LL_UART_STAT_TDRE_FLAG     ( 1U << 23 )

#define HAL_LL_UART_MODULE_PIN_COUNT   2
#define HAL_LL_UART_TX_PIN             0
#define HAL_LL_UART_RX_PIN             1

#define HAL_LL_UART_CTRL_TE            19
#define HAL_LL_UART_CTRL_RE            18

// Bits
#define STOP_BITS_ONE                  0x0U
#define STOP_BITS_TWO                  ( 1U << 13 )

#define DATA_BIT_8                     0x0U
#define DATA_BIT_9                     0x10U

#define PARITY_DISABLED                0x0U
#define PARITY_ENABLED                 0x2U
#define PARITY_EVEN                    0x0U
#define PARITY_ODD                     0x1U

#define HAL_LL_BAUD_BOTHEDGE           ( 1U << 17)

// Clear masks
#define HAL_LL_UART_CTRL_MASK          0x0FF00000UL

// Interrupts
#define HAL_LL_UART_IT_MASK            0xFFFFUL
#define HAL_LL_UART_IT_CLEAR_MASK      0x0000UL

#define HAL_LL_UART_IT_RIE             21
#define HAL_LL_UART_IT_TIE             23

#define HAL_LL_UART_IT_RIE_MASK        0x00200000
#define HAL_LL_UART_IT_TIE_MASK        0x00800000

#define HAL_LL_UART0_CLK_EN            4
#define HAL_LL_UART1_CLK_EN            5
#define HAL_LL_UART2_CLK_EN            6
#define HAL_LL_UART3_CLK_EN            7
#define HAL_LL_UART4_CLK_EN            22

#define __HAL_LL_UART_ENABLE_IT(__HANDLE__, __INTERRUPT__) (__HANDLE__->ctrl |= (__INTERRUPT__ & HAL_LL_UART_IT_MASK))
#define __HAL_LL_UART_DISABLE_IT(__HANDLE__, __INTERRUPT__) (__HANDLE__->ctrl &= ~(__INTERRUPT__ & HAL_LL_UART_IT_MASK))
#define __HAL_LL_UART_GET_IT_SOURCE(__HANDLE__, __INTERRUPT__) (((hal_ll_uart_base_handle_t* )__HANDLE__)->ctrl & __INTERRUPT__)


typedef struct
{
    uint32_t baud;
    uint32_t stat;
    uint32_t ctrl;
    uint32_t datareg;
    uint32_t match;
    uint32_t modir;
    uint32_t fifo;
    uint32_t water;
} hal_ll_uart_base_handle_t;

typedef struct
{
    uint32_t baud;
    uint32_t real_baud;
} hal_ll_uart_baud_t;

typedef struct
{
    hal_ll_base_addr_t base;
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

typedef enum
{
    HAL_LL_UART_SUCCESS = 0,
    HAL_LL_UART_WRONG_PINS,
    HAL_LL_UART_MODULE_ERROR,

    HAL_LL_UART_ERROR = (-1)
} hal_ll_uart_err_t;

typedef enum
{
    HAL_LL_UART_DISABLE = 0,
    HAL_LL_UART_ENABLE
} hal_ll_uart_state_t;

static hal_ll_uart_hw_specifics_map_t hal_ll_uart_hw_specifics_map[UART_MODULE_COUNT + 1] =
{
    #ifdef UART_MODULE_0
    {HAL_LL_UART0_BASE, hal_ll_uart_module_num(UART_MODULE_0), {HAL_LL_PIN_NC, 0, HAL_LL_PIN_NC, 0}, {115200, 0} , HAL_LL_UART_PARITY_DEFAULT, HAL_LL_UART_STOP_BITS_DEFAULT, HAL_LL_UART_DATA_BITS_DEFAULT},
    #endif
    #ifdef UART_MODULE_1
    {HAL_LL_UART1_BASE, hal_ll_uart_module_num(UART_MODULE_1), {HAL_LL_PIN_NC, 0, HAL_LL_PIN_NC, 0}, {115200, 0}, HAL_LL_UART_PARITY_DEFAULT, HAL_LL_UART_STOP_BITS_DEFAULT, HAL_LL_UART_DATA_BITS_DEFAULT},
    #endif
    #ifdef UART_MODULE_2
    {HAL_LL_UART2_BASE, hal_ll_uart_module_num(UART_MODULE_2), {HAL_LL_PIN_NC, 0, HAL_LL_PIN_NC, 0}, {115200, 0}, HAL_LL_UART_PARITY_DEFAULT, HAL_LL_UART_STOP_BITS_DEFAULT, HAL_LL_UART_DATA_BITS_DEFAULT},
    #endif
    #ifdef UART_MODULE_3
    {HAL_LL_UART3_BASE, hal_ll_uart_module_num(UART_MODULE_3), {HAL_LL_PIN_NC, 0, HAL_LL_PIN_NC, 0}, {115200, 0}, HAL_LL_UART_PARITY_DEFAULT, HAL_LL_UART_STOP_BITS_DEFAULT, HAL_LL_UART_DATA_BITS_DEFAULT},
    #endif
    #ifdef UART_MODULE_4
    {HAL_LL_UART4_BASE, hal_ll_uart_module_num(UART_MODULE_4), {HAL_LL_PIN_NC, 0, HAL_LL_PIN_NC, 0}, {115200, 0}, HAL_LL_UART_PARITY_DEFAULT, HAL_LL_UART_STOP_BITS_DEFAULT, HAL_LL_UART_DATA_BITS_DEFAULT},
    #endif

    {HAL_LL_MODULE_ERROR, HAL_LL_MODULE_ERROR, {HAL_LL_PIN_NC, 0, HAL_LL_PIN_NC, 0}, {0, 0}, HAL_LL_MODULE_ERROR, HAL_LL_MODULE_ERROR, HAL_LL_MODULE_ERROR}
};

/*!< @brief Global interrupt handlers used in functions */
static hal_ll_uart_isr_t irq_handler;
static handle_t objects[UART_MODULE_COUNT];

// ------------------------------------------------------------------ VARIABLES
/*!< @brief UART hardware specific info */

/*!< @brief Global handle variables used in functions */
static volatile hal_ll_uart_handle_register_t *low_level_handle;
static volatile hal_ll_uart_hw_specifics_map_t *hal_ll_uart_hw_specifics_map_local;

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
 * @brief  Maps new-found module specific values.
 *
 * Maps pin names and alternate function values for
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
  * @param[in]  hal_ll_state - True(enable clock)/False(disable clock).
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
  * @brief  Get UART module clocking.
  *
  * Returns adequate clock frequency based on
  * UART module base address.
  *
  * @param[in]  map - Object specific context handler.
  *
  * @return uint8_t Module number.
  * Returns clock value.
  */
static uint8_t hal_ll_uart_get_clock( hal_ll_uart_hw_specifics_map_t *map );

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

    hal_ll_uart_pin_id index_list[UART_MODULE_COUNT] = {HAL_LL_PIN_NC,HAL_LL_PIN_NC};
    uint16_t pin_check_result;

   // Check if pins are valid
    if ( HAL_LL_PIN_NC == ( pin_check_result = hal_ll_uart_check_pins( tx_pin, rx_pin, &index_list, handle_map )) ) {
        return HAL_LL_UART_WRONG_PINS;
    };

    if ( ( hal_ll_uart_hw_specifics_map[pin_check_result]->pins.tx_pin.pin_name != tx_pin ) ||
         ( hal_ll_uart_hw_specifics_map[pin_check_result]->pins.rx_pin.pin_name != rx_pin ) )
    {
        hal_ll_uart_alternate_functions_set_state( &hal_ll_uart_hw_specifics_map[pin_check_result], false );
        hal_ll_uart_map_pins( pin_check_result, &index_list );
        hal_ll_uart_alternate_functions_set_state( &hal_ll_uart_hw_specifics_map[pin_check_result], true );
        handle_map[pin_check_result]->init_ll_state = false;
    }

    *hal_module_id = pin_check_result;
    hal_ll_module_state[pin_check_result]->hal_ll_uart_handle = (handle_t *) &hal_ll_uart_hw_specifics_map[pin_check_result]->base;
    handle_map[pin_check_result]->hal_ll_uart_handle = (handle_t *) &hal_ll_module_state[pin_check_result]->hal_ll_uart_handle;

    return HAL_LL_UART_SUCCESS;
}

hal_ll_err_t hal_ll_module_configure_uart( handle_t *handle ) {
    hal_ll_uart_hw_specifics_map_local = hal_ll_get_specifics( hal_ll_uart_get_module_state_address );
    hal_ll_uart_pin_id index_list[HAL_LL_UART_MODULE_PIN_COUNT] = {HAL_LL_PIN_NC,HAL_LL_PIN_NC};
    uint16_t pin_check_result;

    if ( HAL_LL_PIN_NC == ( pin_check_result = hal_ll_uart_check_pins( hal_ll_uart_hw_specifics_map_local->pins.tx_pin.pin_name,
                                                                       hal_ll_uart_hw_specifics_map_local->pins.rx_pin.pin_name,
                                                                       &index_list, (void *)0 ) )) {
        return HAL_LL_UART_WRONG_PINS;
    };

    hal_ll_uart_init( hal_ll_uart_hw_specifics_map_local );

    hal_ll_module_state[pin_check_result]->hal_ll_uart_handle = (handle_t *) &hal_ll_uart_hw_specifics_map[pin_check_result]->base;
    hal_ll_module_state[pin_check_result]->init_ll_state = true;

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

    if( NULL == low_level_handle->hal_ll_uart_handle ) {
        return HAL_LL_UART_MODULE_ERROR;
    }

    low_level_handle->init_ll_state = false;
    hal_ll_uart_hw_specifics_map_local->parity = parity;
    hal_ll_uart_init( hal_ll_uart_hw_specifics_map_local );
    low_level_handle->init_ll_state = true;

    return HAL_LL_UART_SUCCESS;
}

hal_ll_err_t hal_ll_uart_set_stop_bits( handle_t *handle, hal_ll_uart_stop_bits_t stop_bit ) {
    low_level_handle = hal_ll_uart_get_handle;
    hal_ll_uart_hw_specifics_map_local = hal_ll_get_specifics( hal_ll_uart_get_module_state_address );

    if( NULL == low_level_handle->hal_ll_uart_handle ) {
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

    if( NULL == low_level_handle->hal_ll_uart_handle ) {
        return HAL_LL_UART_MODULE_ERROR;
    }

    if( HAL_LL_UART_DATA_BITS_7 == data_bit ) {
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
        objects[hal_ll_uart_find_index( handle )] = NULL;

        low_level_handle->hal_ll_uart_handle = NULL;
        low_level_handle->hal_drv_uart_handle = NULL;

        low_level_handle->init_ll_state = false;
    }
}

void hal_ll_uart_register_irq_handler( handle_t *handle, hal_ll_uart_isr_t handler, handle_t obj ){
    irq_handler = handler;
    objects[hal_ll_uart_find_index( handle )] = obj;
}

void hal_ll_uart_irq_enable( handle_t *handle, hal_ll_uart_irq_t irq ) {
    low_level_handle = hal_ll_uart_get_handle;
    hal_ll_uart_hw_specifics_map_local = hal_ll_get_specifics( hal_ll_uart_get_module_state_address );

    hal_ll_uart_base_handle_t *hal_ll_hw_reg = ( hal_ll_uart_base_handle_t *)hal_ll_uart_hw_specifics_map_local->base;

    switch ( irq ) {
        case HAL_LL_UART_IRQ_RX:
            __HAL_LL_UART_ENABLE_IT ( hal_ll_hw_reg, HAL_LL_UART_IT_RIE_MASK );
            break;
        case HAL_LL_UART_IRQ_TX:
            __HAL_LL_UART_ENABLE_IT ( hal_ll_hw_reg, HAL_LL_UART_IT_TIE_MASK );
            break;

        default:
            break;
    }

    switch ( hal_ll_uart_hw_specifics_map_local->module_index ) {
        #if defined(UART_MODULE_0) && defined(UART0_NVIC)
        case hal_ll_uart_module_num(UART_MODULE_0):
            hal_ll_core_enable_irq( UART0_NVIC );
            break;
        #endif
        #if defined(UART_MODULE_1) && defined(UART1_NVIC)
        case hal_ll_uart_module_num(UART_MODULE_1):
            hal_ll_core_enable_irq( UART1_NVIC );
            break;
        #endif
        #if defined(UART_MODULE_2) && defined(UART2_NVIC)
        case hal_ll_uart_module_num(UART_MODULE_2):
            hal_ll_core_enable_irq( UART2_NVIC );
            break;
        #endif
        #if defined(UART_MODULE_3) && defined(UART3_NVIC)
        case hal_ll_uart_module_num(UART_MODULE_3):
            hal_ll_core_enable_irq( UART3_NVIC );
            break;
        #endif
        #if defined(UART_MODULE_4) && defined(UART4_NVIC)
        case hal_ll_uart_module_num(UART_MODULE_4):
            hal_ll_core_enable_irq( UART4_NVIC );
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
            __HAL_LL_UART_DISABLE_IT ( hal_ll_hw_reg, HAL_LL_UART_IT_RIE_MASK );
            break;
        case HAL_LL_UART_IRQ_TX:
            __HAL_LL_UART_DISABLE_IT ( hal_ll_hw_reg, HAL_LL_UART_IT_TIE_MASK );
            break;

        default:
            break;
    }

    // Check if module interrupt flags are set or not
    if ( ( !check_reg_bit( &hal_ll_hw_reg->ctrl, HAL_LL_UART_IT_RIE ) ) &&
         ( !check_reg_bit( &hal_ll_hw_reg->ctrl, HAL_LL_UART_IT_TIE ) ) )
    {
        switch ( hal_ll_uart_hw_specifics_map_local->module_index ) {
             #if defined(UART_MODULE_0) && defined(UART0_NVIC)
            case hal_ll_uart_module_num(UART_MODULE_0):
                hal_ll_core_disable_irq( UART0_NVIC );
                break;
            #endif
            #if defined(UART_MODULE_1) && defined(UART1_NVIC)
            case hal_ll_uart_module_num(UART_MODULE_1):
                hal_ll_core_disable_irq( UART1_NVIC );
                break;
            #endif
            #if defined(UART_MODULE_2) && defined(UART2_NVIC)
            case hal_ll_uart_module_num(UART_MODULE_2):
                hal_ll_core_disable_irq( UART2_NVIC );
                break;
            #endif
            #if defined(UART_MODULE_3) && defined(UART3_NVIC)
            case hal_ll_uart_module_num(UART_MODULE_3):
                hal_ll_core_disable_irq( UART3_NVIC );
                break;
            #endif
            #if defined(UART_MODULE_4) && defined(UART4_NVIC)
            case hal_ll_uart_module_num(UART_MODULE_4):
                hal_ll_core_disable_irq( UART4_NVIC );
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

    hal_ll_hw_reg->datareg = wr_data;
}

uint8_t hal_ll_uart_read( handle_t *handle ) {
    hal_ll_uart_hw_specifics_map_local = hal_ll_get_specifics( hal_ll_uart_get_module_state_address );
    hal_ll_uart_base_handle_t *hal_ll_hw_reg = ( hal_ll_uart_base_handle_t *)hal_ll_uart_hw_specifics_map_local->base;

    return ( hal_ll_hw_reg->datareg );
}

// ------------------------------------------------------------- DEFAULT EXCEPTION HANDLERS
#if defined(UART_MODULE_0) && defined(UART0_NVIC)
__weak void UART0_IRQHandler(void) MIKROC_IV(UART0_NVIC) {
    if( hal_ll_uart_get_status_flags( HAL_LL_UART0_BASE, HAL_LL_UART_STAT_RDRF_FLAG ) ) {
        if( ( __HAL_LL_UART_GET_IT_SOURCE( HAL_LL_UART0_BASE, HAL_LL_UART_IT_RIE_MASK ) ) != 0 ) {
            hal_ll_uart_clear_status_flag( HAL_LL_UART0_BASE, HAL_LL_UART_STAT_RDRF_FLAG );
            irq_handler( objects[ hal_ll_uart_module_num( UART_MODULE_0 ) ], HAL_LL_UART_IRQ_RX );
        }
    }
    if( hal_ll_uart_get_status_flags( HAL_LL_UART0_BASE, HAL_LL_UART_STAT_TDRE_FLAG ) ) {
        if( ( __HAL_LL_UART_GET_IT_SOURCE( HAL_LL_UART0_BASE, HAL_LL_UART_IT_TIE_MASK ) ) != 0 ) {
            hal_ll_uart_clear_status_flag( HAL_LL_UART0_BASE, HAL_LL_UART_STAT_TDRE_FLAG );
            irq_handler( objects[ hal_ll_uart_module_num( UART_MODULE_0 ) ], HAL_LL_UART_IRQ_TX );
        }
    }
}
#endif

#if defined(UART_MODULE_1) && defined(UART1_NVIC)
__weak void UART1_IRQHandler(void) MIKROC_IV(UART1_NVIC) {
    if( hal_ll_uart_get_status_flags( HAL_LL_UART1_BASE, HAL_LL_UART_STAT_RDRF_FLAG ) ) {
        if( ( __HAL_LL_UART_GET_IT_SOURCE( HAL_LL_UART1_BASE, HAL_LL_UART_IT_RIE_MASK ) ) != 0 ) {
            hal_ll_uart_clear_status_flag( HAL_LL_UART1_BASE, HAL_LL_UART_STAT_RDRF_FLAG );
            irq_handler( objects[ hal_ll_uart_module_num( UART_MODULE_1 ) ], HAL_LL_UART_IRQ_RX );
        }
    }
    if( hal_ll_uart_get_status_flags( HAL_LL_UART1_BASE, HAL_LL_UART_STAT_TDRE_FLAG ) ) {
        if( ( __HAL_LL_UART_GET_IT_SOURCE( HAL_LL_UART1_BASE, HAL_LL_UART_IT_TIE_MASK ) ) != 0 ) {
            hal_ll_uart_clear_status_flag( HAL_LL_UART1_BASE, HAL_LL_UART_STAT_TDRE_FLAG );
            irq_handler( objects[ hal_ll_uart_module_num( UART_MODULE_1 ) ], HAL_LL_UART_IRQ_TX );
        }
    }
}
#endif

#if defined(UART_MODULE_2) && defined(UART2_NVIC)
__weak void UART2_IRQHandler(void) MIKROC_IV(UART2_NVIC) {
    if( hal_ll_uart_get_status_flags( HAL_LL_UART2_BASE, HAL_LL_UART_STAT_RDRF_FLAG ) ) {
        if( ( __HAL_LL_UART_GET_IT_SOURCE( HAL_LL_UART2_BASE, HAL_LL_UART_IT_RIE_MASK ) ) != 0 ) {
            hal_ll_uart_clear_status_flag( HAL_LL_UART2_BASE, HAL_LL_UART_STAT_RDRF_FLAG );
            irq_handler( objects[ hal_ll_uart_module_num( UART_MODULE_2 ) ], HAL_LL_UART_IRQ_RX );
        }
    }
    if( hal_ll_uart_get_status_flags( HAL_LL_UART2_BASE, HAL_LL_UART_STAT_TDRE_FLAG ) ) {
        if( ( __HAL_LL_UART_GET_IT_SOURCE( HAL_LL_UART2_BASE, HAL_LL_UART_IT_TIE_MASK ) ) != 0 ) {
            hal_ll_uart_clear_status_flag( HAL_LL_UART2_BASE, HAL_LL_UART_STAT_TDRE_FLAG );
            irq_handler( objects[ hal_ll_uart_module_num( UART_MODULE_2 ) ], HAL_LL_UART_IRQ_TX );
        }
    }
}
#endif

#if defined(UART_MODULE_3) && defined(UART3_NVIC)
__weak void UART3_IRQHandler(void) MIKROC_IV(UART3_NVIC) {
    if( hal_ll_uart_get_status_flags( HAL_LL_UART3_BASE, HAL_LL_UART_STAT_RDRF_FLAG ) ) {
        if( ( __HAL_LL_UART_GET_IT_SOURCE( HAL_LL_UART3_BASE, HAL_LL_UART_IT_RIE_MASK ) ) != 0 ) {
            hal_ll_uart_clear_status_flag( HAL_LL_UART3_BASE, HAL_LL_UART_STAT_RDRF_FLAG );
            irq_handler( objects[ hal_ll_uart_module_num( UART_MODULE_3 ) ], HAL_LL_UART_IRQ_RX );
        }
    }
    if( hal_ll_uart_get_status_flags( HAL_LL_UART3_BASE, HAL_LL_UART_STAT_TDRE_FLAG ) ) {
        if( ( __HAL_LL_UART_GET_IT_SOURCE( HAL_LL_UART3_BASE, HAL_LL_UART_IT_TIE_MASK ) ) != 0 ) {
            hal_ll_uart_clear_status_flag( HAL_LL_UART3_BASE, HAL_LL_UART_STAT_TDRE_FLAG );
            irq_handler( objects[ hal_ll_uart_module_num( UART_MODULE_3 ) ], HAL_LL_UART_IRQ_TX );
        }
    }
}
#endif

#if defined(UART_MODULE_4) && defined(UART4_NVIC)
__weak void UART4_IRQHandler(void) MIKROC_IV(UART4_NVIC) {
    if( hal_ll_uart_get_status_flags( HAL_LL_UART4_BASE, HAL_LL_UART_STAT_RDRF_FLAG ) ) {
        if( ( __HAL_LL_UART_GET_IT_SOURCE( HAL_LL_UART4_BASE, HAL_LL_UART_IT_RIE_MASK ) ) != 0 ) {
            hal_ll_uart_clear_status_flag( HAL_LL_UART4_BASE, HAL_LL_UART_STAT_RDRF_FLAG );
            irq_handler( objects[ hal_ll_uart_module_num( UART_MODULE_4 ) ], HAL_LL_UART_IRQ_RX );
        }
    }
    if( hal_ll_uart_get_status_flags( HAL_LL_UART4_BASE, HAL_LL_UART_STAT_TDRE_FLAG ) ) {
        if( ( __HAL_LL_UART_GET_IT_SOURCE( HAL_LL_UART4_BASE, HAL_LL_UART_IT_TIE_MASK ) ) != 0 ) {
            hal_ll_uart_clear_status_flag( HAL_LL_UART4_BASE, HAL_LL_UART_STAT_TDRE_FLAG );
            irq_handler( objects[ hal_ll_uart_module_num( UART_MODULE_4 ) ], HAL_LL_UART_IRQ_TX );
        }
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

static hal_ll_uart_hw_specifics_map_t *hal_ll_get_specifics( handle_t handle ) {
    uint8_t hal_ll_module_count = sizeof( hal_ll_module_state ) / ( sizeof( hal_ll_uart_handle_register_t ) );
    static uint8_t hal_ll_module_error = hal_ll_module_count;

    while( hal_ll_module_count-- ) {
        if ( hal_ll_uart_get_base_from_hal_handle == hal_ll_uart_hw_specifics_map[hal_ll_module_count]->base ) {
            return &hal_ll_uart_hw_specifics_map[hal_ll_module_count];
        }
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
                        index_list[hal_ll_module_id]->pin_tx = tx_index;
                        index_list[hal_ll_module_id]->pin_rx = rx_index;

                        // Check if module is taken
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

static void hal_ll_uart_set_clock( hal_ll_uart_hw_specifics_map_t *map, bool hal_ll_state ) {
    switch ( map->module_index ) {
        #ifdef UART_MODULE_0
        case ( hal_ll_uart_module_num( UART_MODULE_0 ) ):
            (hal_ll_state == true)?(set_reg_bit( _SIM_SCGC2, HAL_LL_UART0_CLK_EN )):(clear_reg_bit( _SIM_SCGC2, HAL_LL_UART0_CLK_EN ));
            break;
        #endif
        #ifdef UART_MODULE_1
        case ( hal_ll_uart_module_num( UART_MODULE_1 ) ):
            (hal_ll_state == true)?(set_reg_bit( _SIM_SCGC2, HAL_LL_UART1_CLK_EN )):(clear_reg_bit( _SIM_SCGC2, HAL_LL_UART1_CLK_EN ));
            break;
        #endif
        #ifdef UART_MODULE_2
        case ( hal_ll_uart_module_num( UART_MODULE_2 ) ):
            (hal_ll_state == true)?(set_reg_bit( _SIM_SCGC2, HAL_LL_UART2_CLK_EN )):(clear_reg_bit( _SIM_SCGC2, HAL_LL_UART2_CLK_EN ));
            break;
        #endif
        #ifdef UART_MODULE_3
        case ( hal_ll_uart_module_num( UART_MODULE_3 ) ):
            (hal_ll_state == true)?(set_reg_bit( _SIM_SCGC2, HAL_LL_UART3_CLK_EN )):(clear_reg_bit( _SIM_SCGC2, HAL_LL_UART3_CLK_EN ));
            break;
        #endif
        #ifdef UART_MODULE_4
        case ( hal_ll_uart_module_num( UART_MODULE_4 ) ):
            (hal_ll_state == true)?(set_reg_bit( _SIM_SCGC2, HAL_LL_UART4_CLK_EN )):(clear_reg_bit( _SIM_SCGC2, HAL_LL_UART4_CLK_EN ));
            break;
        #endif

        default:
            break;
    }
}

static void hal_ll_uart_map_pins( uint8_t module_index, hal_ll_uart_pin_id *index_list ) {
    // Map new pins
    hal_ll_uart_hw_specifics_map[module_index]->pins.tx_pin.pin_name = hal_ll_uart_tx_map[ index_list[module_index]->pin_tx ].pin;
    hal_ll_uart_hw_specifics_map[module_index]->pins.rx_pin.pin_name = hal_ll_uart_rx_map[ index_list[module_index]->pin_rx ].pin;
    // TX and RX could have different alternate function settings, hence save both AF values
    hal_ll_uart_hw_specifics_map[module_index]->pins.tx_pin.pin_af = hal_ll_uart_tx_map[ index_list[module_index]->pin_tx ].af;
    hal_ll_uart_hw_specifics_map[module_index]->pins.rx_pin.pin_af = hal_ll_uart_rx_map[ index_list[module_index]->pin_rx ].af;
}

static void hal_ll_uart_clear_regs( hal_ll_uart_base_handle_t *hal_ll_hw_reg ) {
    hal_ll_hw_reg->ctrl &= HAL_LL_UART_CTRL_MASK;
}

static void hal_ll_uart_set_data_bits_bare_metal( hal_ll_uart_hw_specifics_map_t *map ) {
    hal_ll_uart_base_handle_t *hal_ll_hw_reg = hal_ll_uart_get_base_struct( map->base );

    switch ( map->data_bit ) {
        case HAL_LL_UART_DATA_BITS_8:
            hal_ll_hw_reg->ctrl |= DATA_BIT_8;
            break;
        case HAL_LL_UART_DATA_BITS_9:
            hal_ll_hw_reg->ctrl |= DATA_BIT_9;
            break;

        default:
            break;
    }
}

static void hal_ll_uart_set_parity_bare_metal( hal_ll_uart_hw_specifics_map_t *map ) {
    hal_ll_uart_base_handle_t *hal_ll_hw_reg = hal_ll_uart_get_base_struct( map->base );

    switch ( map->parity ) {
        case HAL_LL_UART_PARITY_NONE:
            hal_ll_hw_reg->ctrl |= PARITY_DISABLED;
            break;
        case HAL_LL_UART_PARITY_EVEN:
            hal_ll_hw_reg->ctrl |= PARITY_ENABLED | PARITY_EVEN;
            break;
        case HAL_LL_UART_PARITY_ODD:
            hal_ll_hw_reg->ctrl |= PARITY_ENABLED | PARITY_ODD;
            break;

        default:
            break;
    }
}

static void hal_ll_uart_set_stop_bits_bare_metal( hal_ll_uart_hw_specifics_map_t *map ) {
    hal_ll_uart_base_handle_t *hal_ll_hw_reg = hal_ll_uart_get_base_struct( map->base );

    switch ( map->stop_bit ) {
        case HAL_LL_UART_STOP_BITS_ONE:
            hal_ll_hw_reg->baud &= ~STOP_BITS_TWO;
            break;
        case HAL_LL_UART_STOP_BITS_TWO:
            hal_ll_hw_reg->baud |= STOP_BITS_TWO;
            break;

        default:
            break;
    }
}

static void hal_ll_uart_alternate_functions_set_state( hal_ll_uart_hw_specifics_map_t *map, bool hal_ll_state ) {
    module_struct module;

    if ( ( map->pins.tx_pin.pin_name != HAL_LL_PIN_NC ) && map->pins.rx_pin.pin_name != HAL_LL_PIN_NC ) {
        module.pins[0] = VALUE( map->pins.tx_pin.pin_name, map->pins.tx_pin.pin_af );
        module.pins[1] = VALUE( map->pins.rx_pin.pin_name, map->pins.rx_pin.pin_af );
        module.pins[2] = GPIO_MODULE_STRUCT_END;

        module.configs[0] = HAL_LL_UART_AF_CONFIG;
        module.configs[1] = HAL_LL_UART_AF_CONFIG;
        module.configs[2] = GPIO_MODULE_STRUCT_END;

        hal_ll_gpio_module_struct_init( &module, hal_ll_state );
    }
}

static uint32_t hal_ll_uart_get_clock( hal_ll_uart_hw_specifics_map_t *map ) {
    SIM_ClocksTypeDef sim_clocks;

    SIM_GetClocksFrequency( &sim_clocks );

    return sim_clocks.system_frequency;
}

static void hal_ll_uart_set_baud_bare_metal( hal_ll_uart_hw_specifics_map_t *map ) {
    uint16_t sbr, sbrTemp, i;
    uint32_t osr, tempDiff, calculatedBaud, baudDiff;
    uint32_t module_clock = hal_ll_uart_get_clock( map );
    uint32_t hal_ll_baud_value = hal_ll_uart_get_baud( module_clock, map->baud_rate.baud, 4 );
    uint32_t hal_ll_baud_real_value = hal_ll_uart_get_real_baud( module_clock, hal_ll_baud_value, 4 );
    hal_ll_uart_base_handle_t *hal_ll_hw_reg = hal_ll_uart_get_base_struct( map->base );

    osr = 4;
    sbr = (module_clock/(map->baud_rate.baud * osr));
    /*set sbr to 1 if the module_clock can not satisfy the desired baud rate*/
    if(sbr == 0) {
        sbr = 1;
    }
    calculatedBaud = (module_clock / (osr * sbr));

    if (calculatedBaud > map->baud_rate.baud) {
        baudDiff = calculatedBaud - map->baud_rate.baud;
    }
    else {
        baudDiff = map->baud_rate.baud - calculatedBaud;
    }
    for (i = 5; i <= 32; i++) {
        /* calculate the temporary sbr value   */
        sbrTemp = (module_clock/(map->baud_rate.baud * i));
       /*set sbrTemp to 1 if the module_clock can not satisfy the desired baud rate*/
        if(sbrTemp == 0) {
            sbrTemp = 1;
        }
        /* calculate the baud rate based on the temporary osr and sbr values */
        calculatedBaud = (module_clock / (i * sbrTemp));

        if (calculatedBaud > map->baud_rate.baud) {
            tempDiff = calculatedBaud - map->baud_rate.baud;
        }
        else {
            tempDiff = map->baud_rate.baud - calculatedBaud;
        }

        if (tempDiff <= baudDiff) {
            baudDiff = tempDiff;
            osr = i;  /* update and store the best osr value calculated */
            sbr = sbrTemp;  /* update store the best sbr value calculated */
        }
    }

    /* Check to see if actual baud rate is within 3% of desired baud rate
     * based on the best calculate osr value */
    if( ( hal_ll_uart_get_baud_error( hal_ll_baud_real_value, map->baud_rate.baud )) > HAL_LL_UART_ACCEPTABLE_ERROR ) {
        map->baud_rate.real_baud = hal_ll_uart_get_baud_error( hal_ll_baud_real_value, map->baud_rate.baud );
    } else {
            if ((osr > 3) && (osr < 8)) {
                hal_ll_hw_reg->baud |= HAL_LL_BAUD_BOTHEDGE;
            }

            hal_ll_hw_reg->baud &= ~(0x1FUL << 24);
            hal_ll_hw_reg->baud |= ((uint32_t)(osr - 1)) << 24;

            hal_ll_hw_reg->baud &= ~0x1FFFUL;
            hal_ll_hw_reg->baud |= sbr;
    }
}

static void hal_ll_uart_set_transmitter( hal_ll_uart_base_handle_t *hal_ll_hw_reg, hal_ll_uart_state_t pin_state ){
    switch ( pin_state ) {
        case HAL_LL_UART_DISABLE:
            clear_reg_bit( &( hal_ll_hw_reg->ctrl ), HAL_LL_UART_CTRL_TE );
            break;
        case HAL_LL_UART_ENABLE:
            set_reg_bit( &( hal_ll_hw_reg->ctrl ), HAL_LL_UART_CTRL_TE );
            break;

        default:
            break;
    }
}

static void hal_ll_uart_set_receiver( hal_ll_uart_base_handle_t *hal_ll_hw_reg, hal_ll_uart_state_t pin_state ){
    switch ( pin_state ) {
        case HAL_LL_UART_DISABLE:
            clear_reg_bit( &( hal_ll_hw_reg->ctrl ), HAL_LL_UART_CTRL_RE );
            break;
        case HAL_LL_UART_ENABLE:
            set_reg_bit( &( hal_ll_hw_reg->ctrl ), HAL_LL_UART_CTRL_RE );
            break;

        default:
            break;
    }
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
