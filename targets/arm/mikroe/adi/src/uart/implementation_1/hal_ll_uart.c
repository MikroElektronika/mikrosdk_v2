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
#include "hal_ll_pclkdis.h"
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

#define HAL_LL_UART_CTRL_PARITY_SELECT      (5)
#define HAL_LL_UART_CTRL_STOP_BITS          (12)
#define HAL_LL_UART_CTRL_DATA_BITS_MASK     (0xC00UL)
#define HAL_LL_UART_CTRL_DATA_6_BITS        (10)
#define HAL_LL_UART_CTRL_DATA_7_BITS        (11)
#define HAL_LL_UART_CTRL_RX_FLUSH           (9)
#define HAL_LL_UART_CTRL_TX_FLUSH           (8)
#define HAL_LL_UART_CTRL_BCLKEN             (15)
#define HAL_LL_UART_CTRL_BCLKRDY            (19)
#define HAL_LL_UART_CTRL_UCAGM              (20)

#define HAL_LL_UART_STATUS_RX_EM            (4)
#define HAL_LL_UART_STATUS_TX_FULL          (7)

#define HAL_LL_UART_INT_RX_THD              (4)
#define HAL_LL_UART_INT_TX_HE               (6)
#define HAL_LL_UART_INT_RX_THD_FLAG         (1UL << HAL_LL_UART_INT_RX_THD)
#define HAL_LL_UART_INT_TX_HE_FLAG          (1UL << HAL_LL_UART_INT_TX_HE)
#define HAL_LL_UART_INT_SUPPORTED_MASK      (HAL_LL_UART_INT_RX_THD_FLAG | HAL_LL_UART_INT_TX_HE_FLAG)

#define HAL_LL_UART_CTRL_RX_THD_MASK        (0xFUL)
#define HAL_LL_UART_CTRL_RX_THD_BYTE        (0x1UL)

/* ARMv7-M NVIC Interrupt Set-Pending Register base address. */
#define HAL_LL_UART_NVIC_ISPR_BASE          (0xE000E200UL)

#define HAL_LL_UART_IBRO_FREQ_HZ            (7372800UL)

/* Macros used for setting UART baurate. */
#define HAL_LL_UART_OSR_4X                  (5UL)
#define HAL_LL_UART_CLOCK_FREQ_HZ           (((uint32_t)FOSC_KHZ_VALUE * 1000UL) / 2UL)

/*!< @brief UART HW register structure. */
typedef struct {
    uint32_t ctrl;
    uint32_t status;
    uint32_t int_en;
    uint32_t int_fl;
    uint32_t clkdiv;
    uint32_t osr;
    uint32_t txpeek;
    uint32_t pnr;
    uint32_t fifo;
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
    {HAL_LL_UART0_BASE_ADDR, hal_ll_uart_module_num( UART_MODULE_0 ), {HAL_LL_PIN_NC, 0, HAL_LL_PIN_NC, 0}, {115200, 0}, HAL_LL_UART_PARITY_DEFAULT, HAL_LL_UART_STOP_BITS_DEFAULT, HAL_LL_UART_DATA_BITS_DEFAULT, 10000},
    #endif
    #ifdef UART_MODULE_1
    {HAL_LL_UART1_BASE_ADDR, hal_ll_uart_module_num( UART_MODULE_1 ), {HAL_LL_PIN_NC, 0, HAL_LL_PIN_NC, 0}, {115200, 0}, HAL_LL_UART_PARITY_DEFAULT, HAL_LL_UART_STOP_BITS_DEFAULT, HAL_LL_UART_DATA_BITS_DEFAULT, 10000},
    #endif
    #ifdef UART_MODULE_2
    {HAL_LL_UART2_BASE_ADDR, hal_ll_uart_module_num( UART_MODULE_2 ), {HAL_LL_PIN_NC, 0, HAL_LL_PIN_NC, 0}, {115200, 0}, HAL_LL_UART_PARITY_DEFAULT, HAL_LL_UART_STOP_BITS_DEFAULT, HAL_LL_UART_DATA_BITS_DEFAULT, 10000},
    #endif
    #ifdef UART_MODULE_3
    {HAL_LL_UART3_BASE_ADDR, hal_ll_uart_module_num( UART_MODULE_3 ), {HAL_LL_PIN_NC, 0, HAL_LL_PIN_NC, 0}, {115200, 0}, HAL_LL_UART_PARITY_DEFAULT, HAL_LL_UART_STOP_BITS_DEFAULT, HAL_LL_UART_DATA_BITS_DEFAULT, 10000},
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

/**
 * @brief Set a UART interrupt pending in the ARM NVIC.
 *
 * Used to kick-start interrupt-driven TX because MAX32690 TX_HE is an
 * edge/event interrupt and an empty FIFO does not generate the first event.
 *
 * @param[in] irq_num NVIC interrupt number.
 *
 * @return void None.
 */
static void hal_ll_uart_set_pending_irq( uint8_t irq_num );

/**
 * @brief Common UART interrupt service routine.
 *
 * Drains RX FIFO and fills TX FIFO through the registered mikroSDK callback.
 * The upper HAL callback consumes/produces one byte per invocation, therefore
 * the callback is invoked repeatedly while the corresponding FIFO can be
 * serviced.
 *
 * @param[in] base UART peripheral base address.
 * @param[in] module_index UART module index.
 *
 * @return void None.
 */
static void hal_ll_uart_process_irq( hal_ll_base_addr_t base, uint8_t module_index );

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

}

void hal_ll_uart_irq_enable( handle_t *handle, hal_ll_uart_irq_t irq ) {
    low_level_handle = hal_ll_uart_get_handle;
    hal_ll_uart_hw_specifics_map_local = hal_ll_get_specifics( hal_ll_uart_get_module_state_address );
    hal_ll_uart_base_handle_t *hal_ll_hw_reg = ( hal_ll_uart_base_handle_t * )hal_ll_uart_hw_specifics_map_local->base;
    bool kick_tx = false;

    switch ( irq ) {
        case HAL_LL_UART_IRQ_RX:
            /*
             * mikroSDK UART interrupt mode is byte-oriented and needs an IRQ
             * for the first received byte.
             */
            clear_reg_bits( &hal_ll_hw_reg->ctrl, HAL_LL_UART_CTRL_RX_THD_MASK );
            set_reg_bits( &hal_ll_hw_reg->ctrl, HAL_LL_UART_CTRL_RX_THD_BYTE );

            /* INT_FL is W1C. Clear a stale event before enabling it. */
            write_reg( &hal_ll_hw_reg->int_fl, HAL_LL_UART_INT_RX_THD_FLAG );
            set_reg_bit( &hal_ll_hw_reg->int_en, HAL_LL_UART_INT_RX_THD );
            break;

        case HAL_LL_UART_IRQ_TX:
            /* INT_FL is W1C. Clear a stale event before enabling it. */
            write_reg( &hal_ll_hw_reg->int_fl, HAL_LL_UART_INT_TX_HE_FLAG );
            set_reg_bit( &hal_ll_hw_reg->int_en, HAL_LL_UART_INT_TX_HE );

            /*
             * TX_HE is generated only when TX FIFO crosses from more than
             * half-full to half-empty. Kick the NVIC once so the first bytes
             * can be loaded into an initially empty FIFO.
             *
             * MAX32690 silicon has an erratum stating that TX_HE is not
             * reliable. As a workaround in this implementation PENDING
             * state for UART TX interrupt is set before enabling global
             * interrupts.
             */
            kick_tx = true;
            break;

        default:
            return;
    }

    switch ( hal_ll_uart_hw_specifics_map_local->module_index ) {
        #ifdef UART_MODULE_0
        case hal_ll_uart_module_num( UART_MODULE_0 ):
            hal_ll_core_enable_irq( UART0_NVIC );
            if ( kick_tx ) {
                /* Set pending interrupt state manually for UART0_TX
                 * for the first TX byte to be written via interrupt.
                 */
                hal_ll_uart_set_pending_irq( UART0_NVIC );
            }
            break;
        #endif

        #ifdef UART_MODULE_1
        case hal_ll_uart_module_num( UART_MODULE_1 ):
            hal_ll_core_enable_irq( UART1_NVIC );
            if ( kick_tx ) {
                /* Set pending interrupt state manually for UART1_TX
                 * for the first TX byte to be written via interrupt.
                 */
                hal_ll_uart_set_pending_irq( UART1_NVIC );
            }
            break;
        #endif

        #ifdef UART_MODULE_2
        case hal_ll_uart_module_num( UART_MODULE_2 ):
            hal_ll_core_enable_irq( UART2_NVIC );
            if ( kick_tx ) {
                /* Set pending interrupt state manually for UART2_TX
                 * for the first TX byte to be written via interrupt.
                 */
                hal_ll_uart_set_pending_irq( UART2_NVIC );
            }
            break;
        #endif

        #ifdef UART_MODULE_3
        case hal_ll_uart_module_num( UART_MODULE_3 ):
            hal_ll_core_enable_irq( UART3_NVIC );
            if ( kick_tx ) {
                /* Set pending interrupt state manually for UART3_TX
                 * for the first TX byte to be written via interrupt.
                 */
                hal_ll_uart_set_pending_irq( UART3_NVIC );
            }
            break;
        #endif

        default:
            break;
    }
}

void hal_ll_uart_irq_disable( handle_t *handle, hal_ll_uart_irq_t irq ) {
    low_level_handle = hal_ll_uart_get_handle;
    hal_ll_uart_hw_specifics_map_local = hal_ll_get_specifics( hal_ll_uart_get_module_state_address );
    hal_ll_uart_base_handle_t *hal_ll_hw_reg = ( hal_ll_uart_base_handle_t * )hal_ll_uart_hw_specifics_map_local->base;

    switch ( irq ) {
        case HAL_LL_UART_IRQ_RX:
            clear_reg_bit( &hal_ll_hw_reg->int_en, HAL_LL_UART_INT_RX_THD );
            write_reg( &hal_ll_hw_reg->int_fl, HAL_LL_UART_INT_RX_THD_FLAG );
            break;

        case HAL_LL_UART_IRQ_TX:
            clear_reg_bit( &hal_ll_hw_reg->int_en, HAL_LL_UART_INT_TX_HE );
            write_reg( &hal_ll_hw_reg->int_fl, HAL_LL_UART_INT_TX_HE_FLAG );
            break;

        default:
            return;
    }

    /* Disable the shared UART NVIC line only when neither HAL IRQ is enabled. */
    if ( !( read_reg( &hal_ll_hw_reg->int_en ) & HAL_LL_UART_INT_SUPPORTED_MASK ) ) {
        switch ( hal_ll_uart_hw_specifics_map_local->module_index ) {
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

            default:
                break;
        }
    }
}

void hal_ll_uart_write( handle_t *handle, uint8_t wr_data ) {
    hal_ll_uart_hw_specifics_map_local = hal_ll_get_specifics( hal_ll_uart_get_module_state_address );
    hal_ll_uart_base_handle_t *hal_ll_hw_reg = ( hal_ll_uart_base_handle_t * )hal_ll_uart_hw_specifics_map_local->base;

    /* Non-polling path: IRQ service guarantees that TX FIFO has free space. */
    write_reg( &hal_ll_hw_reg->fifo, wr_data );
}

void hal_ll_uart_write_polling( handle_t *handle, uint8_t wr_data ) {
    hal_ll_uart_hw_specifics_map_local = hal_ll_get_specifics( hal_ll_uart_get_module_state_address );
    hal_ll_uart_base_handle_t *hal_ll_hw_reg = ( hal_ll_uart_base_handle_t * )hal_ll_uart_hw_specifics_map_local->base;

    // Wait while TX FIFO is full.
    while ( check_reg_bit( &hal_ll_hw_reg->status, HAL_LL_UART_STATUS_TX_FULL ) );

    // Write loads the byte into the TX FIFO.
    write_reg( &hal_ll_hw_reg->fifo, wr_data );
}

uint8_t hal_ll_uart_read( handle_t *handle ) {
    hal_ll_uart_hw_specifics_map_local = hal_ll_get_specifics( hal_ll_uart_get_module_state_address );
    hal_ll_uart_base_handle_t *hal_ll_hw_reg = ( hal_ll_uart_base_handle_t * )hal_ll_uart_hw_specifics_map_local->base;

    return ( uint8_t )read_reg( &hal_ll_hw_reg->fifo );
}

uint8_t hal_ll_uart_read_polling( handle_t *handle ) {
    hal_ll_uart_hw_specifics_map_local = hal_ll_get_specifics( hal_ll_uart_get_module_state_address );
    hal_ll_uart_base_handle_t *hal_ll_hw_reg = ( hal_ll_uart_base_handle_t * )hal_ll_uart_hw_specifics_map_local->base;

    // Wait while RX FIFO is empty.
    while ( check_reg_bit( &hal_ll_hw_reg->status, HAL_LL_UART_STATUS_RX_EM ) );

    // Read pops the next byte from the RX FIFO.
    return read_reg( &hal_ll_hw_reg->fifo );
}

// ------------------------------------------------------------- DEFAULT EXCEPTION HANDLERS
#if defined( UART_MODULE_0 )
void UART0_IRQHandler( void ) {
    hal_ll_uart_process_irq( HAL_LL_UART0_BASE_ADDR, hal_ll_uart_module_num( UART_MODULE_0 ) );
}
#endif

#if defined( UART_MODULE_1 )
void UART1_IRQHandler( void ) {
    hal_ll_uart_process_irq( HAL_LL_UART1_BASE_ADDR, hal_ll_uart_module_num( UART_MODULE_1 ) );
}
#endif

#if defined( UART_MODULE_2 )
void UART2_IRQHandler( void ) {
    hal_ll_uart_process_irq( HAL_LL_UART2_BASE_ADDR, hal_ll_uart_module_num( UART_MODULE_2 ) );
}
#endif

#if defined( UART_MODULE_3 )
void UART3_IRQHandler( void ) {
    hal_ll_uart_process_irq( HAL_LL_UART3_BASE_ADDR, hal_ll_uart_module_num( UART_MODULE_3 ) );
}
#endif

// ----------------------------------------------- PRIVATE FUNCTION DEFINITIONS
static void hal_ll_uart_set_pending_irq( uint8_t irq_num )
{
    volatile uint32_t *nvic_ispr = ( volatile uint32_t * )HAL_LL_UART_NVIC_ISPR_BASE;

    uint32_t nvic_irq = hal_ll_core_irq( irq_num );

    nvic_ispr[ nvic_irq >> 5 ] = ( 1UL << ( nvic_irq & HAL_LL_CORE_IRQ_MASK ) );

    while ( !( nvic_ispr[ nvic_irq >> 5 ]  & 1UL << ( nvic_irq & HAL_LL_CORE_IRQ_MASK )));
}

static void hal_ll_uart_process_irq( hal_ll_base_addr_t base, uint8_t module_index ) {
    hal_ll_uart_base_handle_t *hal_ll_hw_reg = hal_ll_uart_get_base_struct( base );
    uint32_t enabled_interrupts = read_reg( &hal_ll_hw_reg->int_en );
    uint32_t interrupt_flags = read_reg( &hal_ll_hw_reg->int_fl );

    /*
     * RX threshold flag is an event flag and must be cleared by writing 1.
     * Drain all currently available bytes because the upper HAL callback reads
     * exactly one byte per invocation.
     */
    if ( ( enabled_interrupts & HAL_LL_UART_INT_RX_THD_FLAG ) &&
         ( interrupt_flags & HAL_LL_UART_INT_RX_THD_FLAG ) ) {
        write_reg( &hal_ll_hw_reg->int_fl, HAL_LL_UART_INT_RX_THD_FLAG );

        if ( irq_handler ) {
            while ( !check_reg_bit( &hal_ll_hw_reg->status, HAL_LL_UART_STATUS_RX_EM ) &&
                    ( read_reg( &hal_ll_hw_reg->int_en ) & HAL_LL_UART_INT_RX_THD_FLAG ) ) {
                irq_handler( objects[ module_index ], HAL_LL_UART_IRQ_RX );
            }
        }
    }

    /*
     * TX_HE is an event rather than a TX-ready level. The first invocation can
     * be software-pended by hal_ll_uart_irq_enable(); later invocations are
     * generated by the hardware half-empty event. Fill all currently available
     * FIFO space because the upper HAL callback writes one byte per invocation.
     */
    if ( enabled_interrupts & HAL_LL_UART_INT_TX_HE_FLAG ) {
        if ( interrupt_flags & HAL_LL_UART_INT_TX_HE_FLAG ) {
            write_reg( &hal_ll_hw_reg->int_fl, HAL_LL_UART_INT_TX_HE_FLAG );
        }

        if ( irq_handler ) {
            while ( !check_reg_bit( &hal_ll_hw_reg->status, HAL_LL_UART_STATUS_TX_FULL ) &&
                    ( read_reg( &hal_ll_hw_reg->int_en ) & HAL_LL_UART_INT_TX_HE_FLAG ) ) {
                irq_handler( objects[ module_index ], HAL_LL_UART_IRQ_TX );
            }
        }
    }
}

static uint8_t hal_ll_uart_find_index( handle_t *handle ) {
    hal_ll_uart_hw_specifics_map_local = hal_ll_get_specifics( hal_ll_uart_get_module_state_address );

    if( hal_ll_uart_hw_specifics_map_local->base != HAL_LL_MODULE_ERROR ) {
        return hal_ll_uart_hw_specifics_map_local->module_index;
    } else {
        return NULL;
    }
}

static hal_ll_pin_name_t hal_ll_uart_check_pins( hal_ll_pin_name_t tx_pin,
                                                 hal_ll_pin_name_t rx_pin,
                                                 hal_ll_uart_pin_id *index_list,
                                                 hal_ll_uart_handle_register_t *handle_map ) {
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
    switch ( map->module_index ) {
        #ifdef UART_MODULE_0
        case ( hal_ll_uart_module_num( UART_MODULE_0 ) ):
            (hal_ll_state == true) ? (clear_reg_bit( _GCR_PCLKDIS0_, GCR_PCLKDIS0_9 )):
                                     (set_reg_bit( _GCR_PCLKDIS0_, GCR_PCLKDIS0_9 ));
            break;
        #endif
        #ifdef UART_MODULE_1
        case ( hal_ll_uart_module_num( UART_MODULE_1 ) ):
            (hal_ll_state == true) ? (clear_reg_bit( _GCR_PCLKDIS0_, GCR_PCLKDIS0_10 )):
                                     (set_reg_bit( _GCR_PCLKDIS0_, GCR_PCLKDIS0_10 ));
            break;
        #endif
        #ifdef UART_MODULE_2
        case ( hal_ll_uart_module_num( UART_MODULE_2 ) ):
            (hal_ll_state == true) ? (clear_reg_bit( _GCR_PCLKDIS1_, GCR_PCLKDIS1_1 )):
                                     (set_reg_bit( _GCR_PCLKDIS1_, GCR_PCLKDIS1_1 ));
            break;
        #endif
        #ifdef UART_MODULE_3
        case ( hal_ll_uart_module_num( UART_MODULE_3 ) ):
            (hal_ll_state == true) ? (clear_reg_bit( _LPGCR_PCLKDIS_, LPGCR_PCLKDIS_4 )):
                                     (set_reg_bit( _LPGCR_PCLKDIS_, LPGCR_PCLKDIS_4 ));
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

    if (( map->pins.rx_pin.pin_name != HAL_LL_PIN_NC ) &&
        ( map->pins.tx_pin.pin_name != HAL_LL_PIN_NC ))
    {
        module.pins[0] = VALUE( map->pins.tx_pin.pin_name, map->pins.tx_pin.pin_af );
        module.pins[1] = VALUE( map->pins.rx_pin.pin_name, map->pins.rx_pin.pin_af );
        module.pins[2] = GPIO_MODULE_STRUCT_END;

        module.configs[ 0 ] = GPIO_CFG_DIGITAL_OUTPUT | GPIO_CFG_PERIPHERAL_PIN; // TX
        module.configs[ 1 ] = GPIO_CFG_DIGITAL_INPUT  | GPIO_CFG_PERIPHERAL_PIN; // RX
        module.configs[ 2 ] = GPIO_MODULE_STRUCT_END;

        hal_ll_gpio_module_struct_init( &module, hal_ll_state );
    }
}

static void hal_ll_uart_set_baud_bare_metal( hal_ll_uart_hw_specifics_map_t *map ) {
    hal_ll_uart_base_handle_t *hal_ll_hw_reg = hal_ll_uart_get_base_struct( map->base );
    uint32_t clkdiv;
    system_clocks_t system_clocks;
    uint32_t uart_clk_hz;
    uint32_t baud;

    baud = map->baud_rate.baud;

    clear_reg_bit( &hal_ll_hw_reg->ctrl, HAL_LL_UART_CTRL_BCLKEN );
    if ( hal_ll_uart_module_num( UART_MODULE_3 ) == map->module_index )
    {
        uart_clk_hz = HAL_LL_UART_IBRO_FREQ_HZ;

        //  OSR = 5 -> 4x oversampling with FDM disabled.
        write_reg( &hal_ll_hw_reg->osr, HAL_LL_UART_OSR_4X );
    } else {
        uart_clk_hz = HAL_LL_UART_CLOCK_FREQ_HZ;
    }

    clkdiv = uart_clk_hz / baud;
    if ( ( ( uart_clk_hz % baud ) > ( baud / 2 ) ) || ( clkdiv == 0 ) ) {
        clkdiv++;
    }

    write_reg( &hal_ll_hw_reg->clkdiv, clkdiv );

    set_reg_bit( &hal_ll_hw_reg->ctrl, HAL_LL_UART_CTRL_UCAGM );

    set_reg_bit( &hal_ll_hw_reg->ctrl, HAL_LL_UART_CTRL_BCLKEN );
    while( !check_reg_bit( &hal_ll_hw_reg->ctrl, HAL_LL_UART_CTRL_BCLKRDY ) );
}

static void hal_ll_uart_set_stop_bits_bare_metal( hal_ll_uart_hw_specifics_map_t *map ) {
    hal_ll_uart_base_handle_t *hal_ll_hw_reg = hal_ll_uart_get_base_struct( map->base );

    switch ( map->stop_bit ) {
        case HAL_LL_UART_STOP_BITS_ONE:
            clear_reg_bit( &hal_ll_hw_reg->ctrl, HAL_LL_UART_CTRL_STOP_BITS );
            break;
        case HAL_LL_UART_STOP_BITS_TWO:
            set_reg_bit( &hal_ll_hw_reg->ctrl, HAL_LL_UART_CTRL_STOP_BITS );
            break;

        default:
            break;
    }
}

static void hal_ll_uart_set_data_bits_bare_metal( hal_ll_uart_hw_specifics_map_t *map ) {
    hal_ll_uart_base_handle_t *hal_ll_hw_reg = hal_ll_uart_get_base_struct( map->base );

    clear_reg_bits( &hal_ll_hw_reg->ctrl, HAL_LL_UART_CTRL_DATA_BITS_MASK);

    switch ( map->data_bit )
    {
        case HAL_LL_UART_DATA_BITS_5:
            clear_reg_bits( &hal_ll_hw_reg->ctrl, HAL_LL_UART_CTRL_DATA_BITS_MASK );
            break;
        case HAL_LL_UART_DATA_BITS_6:
            set_reg_bit( &hal_ll_hw_reg->ctrl, HAL_LL_UART_CTRL_DATA_6_BITS );
            break;
        case HAL_LL_UART_DATA_BITS_7:
            set_reg_bit( &hal_ll_hw_reg->ctrl, HAL_LL_UART_CTRL_DATA_7_BITS );
            break;
        case HAL_LL_UART_DATA_BITS_8:
            set_reg_bits( &hal_ll_hw_reg->ctrl, HAL_LL_UART_CTRL_DATA_BITS_MASK );
            break;

        default:
            break;
    }
}

static void hal_ll_uart_set_parity_bare_metal( hal_ll_uart_hw_specifics_map_t *map ) {
    hal_ll_uart_base_handle_t *hal_ll_hw_reg = hal_ll_uart_get_base_struct( map->base );

    switch ( map->parity )
    {
        case HAL_LL_UART_PARITY_EVEN:
            clear_reg_bit( &hal_ll_hw_reg->ctrl, HAL_LL_UART_CTRL_PARITY_SELECT );
            break;
        case HAL_LL_UART_PARITY_ODD:
            set_reg_bit( &hal_ll_hw_reg->ctrl, HAL_LL_UART_CTRL_PARITY_SELECT );
            break;

        default:
            break;
    }
}

static void hal_ll_uart_clear_regs( hal_ll_uart_base_handle_t *hal_ll_hw_reg ) {
    clear_reg_bit( &hal_ll_hw_reg->ctrl, HAL_LL_UART_CTRL_BCLKEN );

    // Flush FIFOs.
    set_reg_bit( &hal_ll_hw_reg->ctrl, HAL_LL_UART_CTRL_RX_FLUSH );
    set_reg_bit( &hal_ll_hw_reg->ctrl, HAL_LL_UART_CTRL_TX_FLUSH );
}

static void hal_ll_uart_hw_init( hal_ll_uart_hw_specifics_map_t *map ) {
    hal_ll_uart_base_handle_t *hal_ll_hw_reg = hal_ll_uart_get_base_struct( map->base );

    hal_ll_uart_clear_regs( hal_ll_hw_reg );

    hal_ll_uart_set_baud_bare_metal( map );

    hal_ll_uart_set_data_bits_bare_metal( map );

    hal_ll_uart_set_parity_bare_metal( map );

    hal_ll_uart_set_stop_bits_bare_metal( map );
}

static void hal_ll_uart_init( hal_ll_uart_hw_specifics_map_t *map ) {
    hal_ll_uart_base_handle_t *hal_ll_hw_reg = hal_ll_uart_get_base_struct( map->base );

    hal_ll_uart_set_clock( map, true );

    hal_ll_uart_alternate_functions_set_state( map, true );

    hal_ll_uart_hw_init( map );
}

// ------------------------------------------------------------------------- END
