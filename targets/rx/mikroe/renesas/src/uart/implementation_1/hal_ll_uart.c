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

// TODO: replace with the project's actual PCLK accessor once available -- SCI is clocked from PCLK (or PCLKB, depending on the clock tree config).
#define HAL_LL_UART_SOURCE_CLOCK_HZ            (60000000UL)

// TODO: replace with the real MSTPCRB bit for the SCI channel wired up on this board -- not covered by the SCI chapter, needs the Low Power Consumption chapter (and a PRCR unlock around the write, same as was needed for MSTPCRA on the ADC driver).
#define HAL_LL_SCI_MSTPCRB_POS                 (25)

/*!< @brief SMR -- Serial Mode Register bit positions (non-smart-card mode). */
#define HAL_LL_SCI_UART_SMR_CKS_MASK                (0x03)
#define HAL_LL_SCI_UART_SMR_MP                      (2)
#define HAL_LL_SCI_UART_SMR_STOP                    (3)
#define HAL_LL_SCI_UART_SMR_PM                      (4)
#define HAL_LL_SCI_UART_SMR_PE                      (5)
#define HAL_LL_SCI_UART_SMR_CHR                     (6)
#define HAL_LL_SCI_UART_SMR_CM                      (7)

/*!< @brief SEMR -- Serial Extended Mode Register bit positions. */
#define HAL_LL_SCI_UART_SEMR_ABCSE                  (3)

/*!< @brief SCR -- Serial Control Register bit positions. */
#define HAL_LL_SCI_UART_SCR_CKE_MASK                (0x03)
#define HAL_LL_SCI_UART_SCR_TEIE                    (2)
#define HAL_LL_SCI_UART_SCR_MPIE                    (3)
#define HAL_LL_SCI_UART_SCR_RE                      (4)
#define HAL_LL_SCI_UART_SCR_TE                      (5)
#define HAL_LL_SCI_UART_SCR_RIE                     (6)
#define HAL_LL_SCI_UART_SCR_TIE                     (7)

/*!< @brief SSR -- Serial Status Register bit positions. */
#define HAL_LL_SCI_UART_SSR_MPBT                    (0)
#define HAL_LL_SCI_UART_SSR_MPB                     (1)
#define HAL_LL_SCI_UART_SSR_TEND                    (2)
#define HAL_LL_SCI_UART_SSR_PER                     (3)
#define HAL_LL_SCI_UART_SSR_FER                     (4)
#define HAL_LL_SCI_UART_SSR_ORER                    (5)
#define HAL_LL_SCI_UART_SSR_RDRF                    (6)
#define HAL_LL_SCI_UART_SSR_TDRE                    (7)

/*!< @brief SCMR -- Smart Card Mode Register bit positions. */
#define HAL_LL_SCI_UART_SCMR_SMIF                   (0)
#define HAL_LL_SCI_UART_SCMR_CHR1                   (4)

/*!< @brief Highest value that fits into the 8-bit BRR register. */
#define HAL_LL_SCI_UART_BRR_MAX_VALUE               (255)

/*!< @brief UART HW register structure -- SCI register map, laid out in real address order (SMR at offset 0). */
typedef struct {
    uint8_t smr;
    uint8_t brr;
    uint8_t scr;
    uint8_t tdr;
    uint8_t ssr;
    uint8_t rdr;
    uint8_t scmr;
    uint8_t semr;
    uint8_t snfr;
    uint8_t simr1;
    uint8_t simr2;
    uint8_t simr3;
    uint8_t sisr;
    uint8_t spmr;
    uint8_t tdrh;
    uint8_t tdrl;
    uint8_t rdrh;
    uint8_t rdrl;
    uint8_t mddr;
    uint8_t dccr;
    uint8_t reserved0[6];
    uint8_t cdr;
    uint8_t reserved1;
    uint8_t sptr;
    uint8_t tmgr;
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
    hal_ll_pin_name_t tx_pin_af;
    hal_ll_pin_name_t rx_pin_af;
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
    #ifdef SCI_MODULE_6
    {HAL_LL_SCI6_BASE_ADDR, hal_ll_uart_module_num( SCI_MODULE_6 ), {HAL_LL_PIN_NC, HAL_LL_PIN_NC}, 0, 0, {115200, 0}, HAL_LL_UART_PARITY_DEFAULT, HAL_LL_UART_STOP_BITS_DEFAULT, HAL_LL_UART_DATA_BITS_DEFAULT, 10000},
    #endif

    {HAL_LL_MODULE_ERROR, HAL_LL_MODULE_ERROR, {HAL_LL_PIN_NC, HAL_LL_PIN_NC}, 0, 0, {0, 0}, HAL_LL_MODULE_ERROR, HAL_LL_MODULE_ERROR, HAL_LL_MODULE_ERROR, 10000 }
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
 * @brief  Initialize UART module.
 *
 * Enables UART module clock gate first.
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
 * the hardware level, following the SCI asynchronous-mode
 * init sequence from the reference manual.
 *
 * Procedure:
 * 1. Clears SCR/SMR (disables TE/RE, resets mode bits)
 * 2. Sets data bit value
 * 3. Sets parity value
 * 4. Sets stop bit value
 * 5. Sets baud rate value (CKS + BRR)
 * 6. Clears stale receive error flags
 * 7. Enables TE and RE
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

    if ( HAL_LL_PIN_NC == (pin_check_result = hal_ll_uart_check_pins( tx_pin, rx_pin, &index_list, handle_map )) ) {
        return HAL_LL_UART_WRONG_PINS;
    };

    if ( (hal_ll_uart_hw_specifics_map[pin_check_result].pins.tx_pin != tx_pin) ||
         (hal_ll_uart_hw_specifics_map[pin_check_result].pins.rx_pin != rx_pin) )
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

    // SCI does not support 5 or 6 bit data lengths -- only 7, 8 and 9.
    if ( ( HAL_LL_UART_DATA_BITS_7 > data_bit ) || ( HAL_LL_UART_DATA_BITS_9 < data_bit ) ) {
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

    if ( HAL_LL_MODULE_ERROR != hal_ll_uart_hw_specifics_map_local->base ) {
        hal_ll_uart_hw_specifics_map_local->timeout_polling_write = timeout;
    }
}

void hal_ll_uart_close( handle_t *handle ) {
    low_level_handle = hal_ll_uart_get_handle;
    hal_ll_uart_hw_specifics_map_local = hal_ll_get_specifics( hal_ll_uart_get_module_state_address );

    if ( NULL != low_level_handle->hal_ll_uart_handle ) {
        hal_ll_uart_base_handle_t *hal_ll_hw_reg = hal_ll_uart_get_base_struct( hal_ll_uart_hw_specifics_map_local->base );

        hal_ll_uart_set_clock( hal_ll_uart_hw_specifics_map_local, true );
        hal_ll_uart_alternate_functions_set_state( hal_ll_uart_hw_specifics_map_local, false );

        hal_ll_uart_irq_disable( handle, HAL_LL_UART_IRQ_RX );
        hal_ll_uart_irq_disable( handle, HAL_LL_UART_IRQ_TX );

        hal_ll_uart_clear_regs( hal_ll_hw_reg );

        hal_ll_uart_set_clock( hal_ll_uart_hw_specifics_map_local, false );

        hal_ll_uart_hw_specifics_map_local->pins.tx_pin = HAL_LL_PIN_NC;
        hal_ll_uart_hw_specifics_map_local->tx_pin_af = 0;
        hal_ll_uart_hw_specifics_map_local->pins.rx_pin = HAL_LL_PIN_NC;
        hal_ll_uart_hw_specifics_map_local->rx_pin_af = 0;

        hal_ll_uart_hw_specifics_map_local->baud_rate.baud = 115200UL;
        hal_ll_uart_hw_specifics_map_local->baud_rate.real_baud = 0;

        irq_handler = NULL;
        objects[ hal_ll_uart_find_index( handle ) ] = NULL;

        low_level_handle->hal_ll_uart_handle = NULL;
        low_level_handle->init_ll_state = false;
    }
}

void hal_ll_uart_register_irq_handler( handle_t *handle, hal_ll_uart_isr_t handler, handle_t obj ) {
    irq_handler = handler;
    hal_ll_uart_hw_specifics_map_local = hal_ll_get_specifics( hal_ll_uart_get_module_state_address );
    objects[ hal_ll_uart_find_index( handle ) ] = obj;

    // TODO: hook TXI/RXI/ERI up to the NVIC once interrupt-driven mode is implemented.
}

void hal_ll_uart_irq_enable( handle_t *handle, hal_ll_uart_irq_t irq ) {
    // TODO: enable SCI TXI/RXI interrupts (SCR.TIE/RIE) once interrupt-driven mode is implemented.
}

void hal_ll_uart_irq_disable( handle_t *handle, hal_ll_uart_irq_t irq ) {
    // TODO: disable SCI TXI/RXI interrupts (SCR.TIE/RIE) once interrupt-driven mode is implemented.
}

void hal_ll_uart_write( handle_t *handle, uint8_t wr_data ) {
    // TODO: interrupt-driven write path -- use hal_ll_uart_write_polling for now.
}

void hal_ll_uart_write_polling( handle_t *handle, uint8_t wr_data ) {
    hal_ll_uart_hw_specifics_map_local = hal_ll_get_specifics( hal_ll_uart_get_module_state_address );
    hal_ll_uart_base_handle_t *hal_ll_hw_reg = hal_ll_uart_get_base_struct( hal_ll_uart_hw_specifics_map_local->base );
    uint32_t time_counter = hal_ll_uart_hw_specifics_map_local->timeout_polling_write;

    // Wait until the TDR register is empty.
    while ( !check_reg_bit( &hal_ll_hw_reg->ssr, HAL_LL_SCI_UART_SSR_TDRE ) ) {
        if ( !time_counter-- ) {
            return;
        }
    }

    write_reg( &hal_ll_hw_reg->tdr, wr_data );

    // Wait until the character has actually been transmitted.
    time_counter = hal_ll_uart_hw_specifics_map_local->timeout_polling_write;
    while ( !check_reg_bit( &hal_ll_hw_reg->ssr, HAL_LL_SCI_UART_SSR_TEND ) ) {
        if ( !time_counter-- ) {
            return;
        }
    }
}

uint8_t hal_ll_uart_read( handle_t *handle ) {
    // TODO: interrupt-driven read path -- use hal_ll_uart_read_polling for now.
    return 0;
}

uint8_t hal_ll_uart_read_polling( handle_t *handle ) {
    hal_ll_uart_hw_specifics_map_local = hal_ll_get_specifics( hal_ll_uart_get_module_state_address );
    hal_ll_uart_base_handle_t *hal_ll_hw_reg = hal_ll_uart_get_base_struct( hal_ll_uart_hw_specifics_map_local->base );

    while ( !check_reg_bit( &hal_ll_hw_reg->ssr, HAL_LL_SCI_UART_SSR_RDRF ) ) {
        // An overrun error blocks further reception until cleared -- clear it and keep waiting.
        if ( check_reg_bit( &hal_ll_hw_reg->ssr, HAL_LL_SCI_UART_SSR_ORER ) ) {
            clear_reg_bit( &hal_ll_hw_reg->ssr, HAL_LL_SCI_UART_SSR_ORER );
        }
    }

    return read_reg( &hal_ll_hw_reg->rdr );
}

// ------------------------------------------------------------- DEFAULT EXCEPTION HANDLERS


// ----------------------------------------------- PRIVATE FUNCTION DEFINITIONS
static uint8_t hal_ll_uart_find_index( handle_t *handle ) {
    hal_ll_uart_hw_specifics_map_local = hal_ll_get_specifics( hal_ll_uart_get_module_state_address );

    if ( HAL_LL_MODULE_ERROR != hal_ll_uart_hw_specifics_map_local->base ) {
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
#define HAL_LL_ADC_PRCR_ADDR (0x000803FEUL)
#define HAL_LL_ADC_PRCR_LOCK_VAL (0xA500U)
#define HAL_LL_ADC_PRCR_UNLOCK_VAL (0xA502U)
static void hal_ll_uart_set_clock( hal_ll_uart_hw_specifics_map_t *map, bool hal_ll_state ) {
    // TODO: confirm the MSTPCRB bit for the SCI channel in use (not covered by the SCI chapter) and the PRCR unlock sequence around it.
    volatile uint16_t *prcr = ( uint16_t * )HAL_LL_ADC_PRCR_ADDR;
    write_reg( prcr, HAL_LL_ADC_PRCR_UNLOCK_VAL );


    ( hal_ll_state == true ) ? clear_reg_bit( _MSTPCRB, HAL_LL_SCI_MSTPCRB_POS ) : set_reg_bit( _MSTPCRB, HAL_LL_SCI_MSTPCRB_POS );

    write_reg( prcr, HAL_LL_ADC_PRCR_LOCK_VAL );
}

static void hal_ll_uart_map_pins( uint8_t module_index, hal_ll_uart_pin_id *index_list ) {
    // Map new pins.
    hal_ll_uart_hw_specifics_map[module_index].pins.tx_pin = hal_ll_uart_tx_map[index_list[module_index].pin_tx].pin;
    hal_ll_uart_hw_specifics_map[module_index].pins.rx_pin = hal_ll_uart_rx_map[index_list[module_index].pin_rx].pin;
    // TX and RX could have different alternate function settings, hence save both AF values.
    hal_ll_uart_hw_specifics_map[module_index].tx_pin_af = hal_ll_uart_tx_map[index_list[module_index].pin_tx].af;
    hal_ll_uart_hw_specifics_map[module_index].rx_pin_af = hal_ll_uart_rx_map[index_list[module_index].pin_rx].af;
}

static void hal_ll_uart_alternate_functions_set_state( hal_ll_uart_hw_specifics_map_t *map, bool hal_ll_state ) {
    module_struct module;

    if ( ( map->pins.rx_pin != HAL_LL_PIN_NC ) &&
         ( map->pins.tx_pin != HAL_LL_PIN_NC ) )
    {
        // This port's alternate-function config comes from module.configs[] (written straight to PmnPFS) --
        // not from AF bits packed into the pin value, so pass the pins plain and PSEL separately.
        module.pins[0] = map->pins.tx_pin;
        module.pins[1] = map->pins.rx_pin;
        module.pins[2] = GPIO_MODULE_STRUCT_END;

        module.configs[ 0 ] = 10;
        module.configs[ 1 ] = 10;
        module.configs[ 2 ] = GPIO_MODULE_STRUCT_END;

        hal_ll_gpio_module_struct_init( &module, hal_ll_state );
    }

}

static void hal_ll_uart_set_baud_bare_metal( hal_ll_uart_hw_specifics_map_t *map ) {
    hal_ll_uart_base_handle_t *hal_ll_hw_reg = hal_ll_uart_get_base_struct( map->base );
    uint32_t source_clock = HAL_LL_UART_SOURCE_CLOCK_HZ;
    uint32_t brr_value;
    uint8_t n;

    set_reg_bit( &hal_ll_hw_reg->semr, HAL_LL_SCI_UART_SEMR_ABCSE );

    for ( n = 0; n <= HAL_LL_SCI_UART_SMR_CKS_MASK; n++ ) {
        brr_value = ( source_clock / ( 6UL * ( 1UL << ( 2 * n ) ) * map->baud_rate.baud ) ) - 1;

        if ( HAL_LL_SCI_UART_BRR_MAX_VALUE >= brr_value ) {
            break;
        }
    }

    clear_reg_bits( &hal_ll_hw_reg->smr, HAL_LL_SCI_UART_SMR_CKS_MASK );
    set_reg_bits( &hal_ll_hw_reg->smr, n );

    write_reg( &hal_ll_hw_reg->brr, brr_value );

    map->baud_rate.real_baud = source_clock / ( 6UL * ( 1UL << ( 2 * n ) ) * ( brr_value + 1 ) );
}

static void hal_ll_uart_set_stop_bits_bare_metal( hal_ll_uart_hw_specifics_map_t *map ) {
    hal_ll_uart_base_handle_t *hal_ll_hw_reg = hal_ll_uart_get_base_struct( map->base );

    switch ( map->stop_bit ) {
        case HAL_LL_UART_STOP_BITS_TWO:
            set_reg_bit( &hal_ll_hw_reg->smr, HAL_LL_SCI_UART_SMR_STOP );
            break;
        case HAL_LL_UART_STOP_BITS_ONE:
        default:
            clear_reg_bit( &hal_ll_hw_reg->smr, HAL_LL_SCI_UART_SMR_STOP );
            break;
    }
}

static void hal_ll_uart_set_data_bits_bare_metal( hal_ll_uart_hw_specifics_map_t *map ) {
    hal_ll_uart_base_handle_t *hal_ll_hw_reg = hal_ll_uart_get_base_struct( map->base );

    // 8/7 bit selection needs SCMR.CHR1 = 1 (SCMR.CHR1/SMR.CHR combination);
    // 9 bit needs SCMR.CHR1 = 0 regardless of SMR.CHR.
    switch ( map->data_bit ) {
        case HAL_LL_UART_DATA_BITS_7:
            set_reg_bit( &hal_ll_hw_reg->scmr, HAL_LL_SCI_UART_SCMR_CHR1 );
            set_reg_bit( &hal_ll_hw_reg->smr, HAL_LL_SCI_UART_SMR_CHR );
            break;
        case HAL_LL_UART_DATA_BITS_9:
            clear_reg_bit( &hal_ll_hw_reg->scmr, HAL_LL_SCI_UART_SCMR_CHR1 );
            break;
        case HAL_LL_UART_DATA_BITS_8:
        default:
            set_reg_bit( &hal_ll_hw_reg->scmr, HAL_LL_SCI_UART_SCMR_CHR1 );
            clear_reg_bit( &hal_ll_hw_reg->smr, HAL_LL_SCI_UART_SMR_CHR );
            break;
    }
}

static void hal_ll_uart_set_parity_bare_metal( hal_ll_uart_hw_specifics_map_t *map ) {
    hal_ll_uart_base_handle_t *hal_ll_hw_reg = hal_ll_uart_get_base_struct( map->base );

    switch ( map->parity ) {
        case HAL_LL_UART_PARITY_EVEN:
            clear_reg_bit( &hal_ll_hw_reg->smr, HAL_LL_SCI_UART_SMR_PM );
            set_reg_bit( &hal_ll_hw_reg->smr, HAL_LL_SCI_UART_SMR_PE );
            break;
        case HAL_LL_UART_PARITY_ODD:
            set_reg_bit( &hal_ll_hw_reg->smr, HAL_LL_SCI_UART_SMR_PM );
            set_reg_bit( &hal_ll_hw_reg->smr, HAL_LL_SCI_UART_SMR_PE );
            break;
        case HAL_LL_UART_PARITY_NONE:
        default:
            clear_reg_bit( &hal_ll_hw_reg->smr, HAL_LL_SCI_UART_SMR_PE );
            break;
    }
}

static void hal_ll_uart_set_module( hal_ll_uart_base_handle_t *hal_ll_hw_reg, hal_ll_uart_state_t pin_state ) {
    switch ( pin_state ) {
        case HAL_LL_UART_ENABLE:
            set_reg_bit( &hal_ll_hw_reg->scr, HAL_LL_SCI_UART_SCR_TE );
            set_reg_bit( &hal_ll_hw_reg->scr, HAL_LL_SCI_UART_SCR_RE );
            break;
        case HAL_LL_UART_DISABLE:
        default:
            clear_reg_bit( &hal_ll_hw_reg->scr, HAL_LL_SCI_UART_SCR_TE );
            clear_reg_bit( &hal_ll_hw_reg->scr, HAL_LL_SCI_UART_SCR_RE );
            break;
    }
}

static void hal_ll_uart_clear_regs( hal_ll_uart_base_handle_t *hal_ll_hw_reg ) {
    clear_reg( &hal_ll_hw_reg->scr );
    clear_reg( &hal_ll_hw_reg->smr );
}

static void hal_ll_uart_hw_init( hal_ll_uart_hw_specifics_map_t *map ) {
    hal_ll_uart_base_handle_t *hal_ll_hw_reg = hal_ll_uart_get_base_struct( map->base );

    // SCR/SMR must be re-initialized (with TE = RE = 0) before any mode/format change.
    hal_ll_uart_clear_regs( hal_ll_hw_reg );

    hal_ll_uart_set_data_bits_bare_metal( map );

    hal_ll_uart_set_parity_bare_metal( map );

    hal_ll_uart_set_stop_bits_bare_metal( map );

    hal_ll_uart_set_baud_bare_metal( map );

    // Clear any receive error flags left over from a previous session -- ORER blocks further reception until cleared.
    clear_reg_bit( &hal_ll_hw_reg->ssr, HAL_LL_SCI_UART_SSR_ORER );
    clear_reg_bit( &hal_ll_hw_reg->ssr, HAL_LL_SCI_UART_SSR_FER );
    clear_reg_bit( &hal_ll_hw_reg->ssr, HAL_LL_SCI_UART_SSR_PER );

    hal_ll_uart_set_module( hal_ll_hw_reg, HAL_LL_UART_ENABLE );
}

static void hal_ll_uart_init( hal_ll_uart_hw_specifics_map_t *map ) {
    hal_ll_uart_set_clock( map, true );

    hal_ll_uart_alternate_functions_set_state( map, true );

    hal_ll_uart_hw_init( map );
}

// ------------------------------------------------------------------------- END
