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
#include "hal_ll_cg.h"
#include "hal_ll_core_defines.h"
#include "hal_ll_uart_pin_map.h"

#include "hal_ll_core_defines.h"
#include "hal_ll_bit_control.h"

 /*!< @brief Local handle list */
static volatile hal_ll_uart_handle_register_t hal_ll_module_state[UART_MODULE_COUNT] = { (handle_t*)NULL, (handle_t*)NULL, false };

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

/*======================= BRD =============================*/
#define UART_BRD_BRN_POS            (0)
#define UART_BRD_BRN_MASK           (0X0000FFFF << UART_BRD_BRN_POS)
#define UART_BRD_BRK_POS            (16)
#define UART_BRD_BRK_MASK           (0X0000003F << UART_BRD_BRK_POS)
#define UART_BRD_KEN_BIT            (23)

/*======================= CR0 =============================*/
#define UART_CR0_SM_POS             (0)
#define UART_CR0_SM_MASK            (0X00000003 << UART_CR0_SM_POS)
#define UART_CR0_DATA_BITS_7        (0x00000000 << UART_CR0_SM_POS)
#define UART_CR0_DATA_BITS_8        (0x00000001 << UART_CR0_SM_POS)
#define UART_CR0_DATA_BITS_9        (0x00000002 << UART_CR0_SM_POS)
#define UART_CR0_STOP_BIT_POS       (4)
#define UART_CR0_PARITY_BIT         (3)
#define UART_CR0_PARITY_ENABLE_BIT  (2)

/*======================= SR =============================*/
#define UART_SR_SUE_POS        (31)
#define UART_SR_TXRUN_MASK     (0x00000001 << 15)

#define UART_SR_TLVL_POS  (8u)     // TLVL[11:8]
#define UART_SR_TLVL_MASK (0xFu << UART_SR_TLVL_POS)
#define UART_SR_RLVL_POS  (0u)     // RLVL[3:0]
#define UART_SR_RLVL_MASK (0xFu << UART_SR_RLVL_POS)

#define UART_SR_TXFF_MASK       (0X00000001 << 13)
#define UART_SR_RXFF_MASK       (0X00000001 << 5)
#define UART_SR_TXEND_MASK      (0X00000001 << 14)
#define UART_SR_RXEND_MASK      (0X00000001 << 6)

#define UART_SR_TXFF_BIT       (13)
#define UART_SR_RXFF_BIT       (5)

/*======================= TRANS =============================*/
#define UART_TRANS_TXE_BIT     (1)
#define UART_TRANS_RXE_BIT     (0)

/*======================= CR1 =============================*/
#define UART_CR1_INTTXFE_MASK    (0X00000001 << 7)
#define UART_CR1_INTRXFE_MASK    (0X00000001 << 5)
#define UART_CR1_INTTXWE_MASK    (0X00000001 << 6)
#define UART_CR1_INTRXWE_MASK    (0X00000001 << 4)

#define UART_CR1_INTTXFE_BIT     (7)
#define UART_CR1_INTTXWE_BIT     (6)
#define UART_CR1_INTRXFE_BIT     (5)
#define UART_CR1_INTRXWE_BIT     (4)

#define HAL_LL_UART_INTTXWE_POS  (6)
/*======================= SWRST =============================*/
#define UART_SWRST_MASK        (0X00000003 << 0)
#define UART_SWRST_MASK_10     (0x00000002)
#define UART_SWRST_MASK_01     (0x00000001)

/*======================= CLK =============================*/
#define UART_CLK_PRSEL_0       (0x00000000)

/*======================= CR1 =============================*/
#define UART_CR1_TIL_POS      (12)
#define UART_CR1_RIL_POS      (8)

#define UART_CR1_TIL_000_SHIFTED  (0x00000000 << UART_CR1_TIL_POS)
#define UART_CR1_TIL_001_SHIFTED  (0x00000001 << UART_CR1_TIL_POS)
#define UART_CR1_RIL_001_SHIFTED  (0x00000001 << UART_CR1_RIL_POS)
#define UART_CR1_RIL_010_SHIFTED  (0x00000002 << UART_CR1_RIL_POS)
#define UART_CR1_RIL_011_SHIFTED  (0x00000003 << UART_CR1_RIL_POS)
#define UART_CR1_RIL_000_SHIFTED  (0x00000000 << UART_CR1_RIL_POS)

#define UART_CR1_TIL_MASK          (0x00000007 << UART_CR1_TIL_POS)
#define UART_CR1_RIL_MASK          (0x00000007 << UART_CR1_RIL_POS)

#define UART_FIFOCLR_RFCLR_BIT     (1)
#define UART_FIFOCLR_TFCLR_BIT     (0)

#define UART_TX_FIFO_SIZE          (8u)

#define FIVE_CYCLES_OR_LESS        (0b111)

#define write_field_reg(reg, mask, value_shifted) do {  \
                                                       uint32_t _r = read_reg(reg); \
                                                       _r = ((_r & ~mask) | ((value_shifted) & (mask))); \
                                                       write_reg(reg,_r); \
                                                     } while(0)

/*!< @brief Macro used for interrupt status register flag check
 * Used in interrupt handlers.
 */
#define hal_ll_uart_get_status_flags(_handle,_flag) (((hal_ll_uart_base_handle_t *)_handle)->cr1 & _flag)

 /*!< @brief Macro used for module interrupt source check.
  * Used in interrupt handlers.
  */
#define hal_ll_uart_get_interrupt_source(_handle,_bit) (((hal_ll_uart_base_handle_t *)_handle)->sr & _bit)

/*!< @brief UART HW register structure. */
typedef struct {
    volatile uint32_t swrst;     /* UART Software Reset Register                 */
    volatile uint32_t cr0;       /* UART Control Register 0                      */
    volatile uint32_t cr1;       /* UART Control Register 1                      */
    volatile uint32_t clk;       /* UART Clock Control Register                  */
    volatile uint32_t brd;       /* UART Baud Rate Register                      */
    volatile uint32_t trans;     /* UART Transfer Enable Register                */
    volatile uint32_t dr;        /* UART Data Register                           */
    volatile uint32_t sr;        /* UART Status Register                         */
    volatile uint32_t fifoclr;   /* UART FIFO Clear Register                     */
    volatile uint32_t err;
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
static hal_ll_uart_hw_specifics_map_t hal_ll_uart_hw_specifics_map[UART_MODULE_COUNT + 1] = {
    #ifdef UART_MODULE_0
    {HAL_LL_UART0_BASE_ADDRESS, hal_ll_uart_module_num( UART_MODULE_0 ), {HAL_LL_PIN_NC, 0, HAL_LL_PIN_NC, 0},
            {115200, 0}, HAL_LL_UART_PARITY_DEFAULT, HAL_LL_UART_STOP_BITS_DEFAULT, HAL_LL_UART_DATA_BITS_DEFAULT},
    #endif
    #ifdef UART_MODULE_1
    {HAL_LL_UART1_BASE_ADDRESS, hal_ll_uart_module_num( UART_MODULE_1 ), {HAL_LL_PIN_NC, 0, HAL_LL_PIN_NC, 0},
            {115200, 0}, HAL_LL_UART_PARITY_DEFAULT, HAL_LL_UART_STOP_BITS_DEFAULT, HAL_LL_UART_DATA_BITS_DEFAULT},
    #endif
    #ifdef UART_MODULE_2
    {HAL_LL_UART2_BASE_ADDRESS, hal_ll_uart_module_num( UART_MODULE_2 ), {HAL_LL_PIN_NC, 0, HAL_LL_PIN_NC, 0},
            {115200, 0}, HAL_LL_UART_PARITY_DEFAULT, HAL_LL_UART_STOP_BITS_DEFAULT, HAL_LL_UART_DATA_BITS_DEFAULT},
    #endif
    #ifdef UART_MODULE_3
    {HAL_LL_UART3_BASE_ADDRESS, hal_ll_uart_module_num( UART_MODULE_3 ), {HAL_LL_PIN_NC, 0, HAL_LL_PIN_NC, 0},
            {115200, 0}, HAL_LL_UART_PARITY_DEFAULT, HAL_LL_UART_STOP_BITS_DEFAULT, HAL_LL_UART_DATA_BITS_DEFAULT},
    #endif

    {HAL_LL_MODULE_ERROR, HAL_LL_MODULE_ERROR, {HAL_LL_PIN_NC, 0, HAL_LL_PIN_NC, 0}, {0, 0},
            HAL_LL_MODULE_ERROR, HAL_LL_MODULE_ERROR, HAL_LL_MODULE_ERROR}
};

/*!< @brief Global handle variables used in functions. */
static volatile hal_ll_uart_handle_register_t* low_level_handle;
static volatile hal_ll_uart_hw_specifics_map_t* hal_ll_uart_hw_specifics_map_local;

/*!< @brief Global interrupt handlers used in functions. */
static hal_ll_uart_isr_t irq_handler;
static handle_t objects[UART_MODULE_COUNT];

#define UART_CR0_NF_POS   12u
#define UART_CR0_NF_MASK  ( 0x7u << UART_CR0_NF_POS )
#define UART_CR0_NF(val)  (((uint32_t)(val) & 0x7u) << UART_CR0_NF_POS)

static inline void hal_ll_uart_set_rx_noise_filter(hal_ll_uart_base_handle_t *hal_ll_hw_reg, uint8_t nf_sel)
{
    uint32_t cr0 = hal_ll_hw_reg->cr0;
    cr0 &= ~UART_CR0_NF_MASK;
    cr0 |= UART_CR0_NF(nf_sel);
    hal_ll_hw_reg->cr0 = cr0;
}

// Array with flag for each module that indicates whether the ISR kick has been done.
static volatile uint8_t s_tx_kick[UART_MODULE_COUNT] = {0};

// Array with flag for each module to make sure NVIC Interrupt Set-Pending Register
// is set only at the beginning of a transmission.
static volatile uint8_t nvic_pending[UART_MODULE_COUNT] = {0};

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
static hal_ll_pin_name_t hal_ll_uart_check_pins( hal_ll_pin_name_t tx_pin,
                                                 hal_ll_pin_name_t rx_pin,
                                                 hal_ll_uart_pin_id* index_list,
                                                 hal_ll_uart_handle_register_t* handle_map );

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
static void hal_ll_uart_map_pins( uint8_t module_index, hal_ll_uart_pin_id* index_list );

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
static void hal_ll_uart_alternate_functions_set_state( hal_ll_uart_hw_specifics_map_t* map, bool hal_ll_state );

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
static hal_ll_uart_hw_specifics_map_t* hal_ll_get_specifics( handle_t handle );

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
static void hal_ll_uart_set_clock( hal_ll_uart_hw_specifics_map_t* map, bool hal_ll_state );

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
static uint8_t hal_ll_uart_find_index( handle_t* handle );

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
static void hal_ll_uart_clear_regs( hal_ll_uart_base_handle_t* hal_ll_hw_reg );

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
static void hal_ll_uart_set_stop_bits_bare_metal( hal_ll_uart_hw_specifics_map_t* map );

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
static void hal_ll_uart_set_data_bits_bare_metal( hal_ll_uart_hw_specifics_map_t* map );

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
static void hal_ll_uart_set_parity_bare_metal( hal_ll_uart_hw_specifics_map_t* map );

/**
 * @brief  Sets module clock value.
 *
 * Enables/disables specific UART module
 * clock gate.
 *
 * @param[in]  hal_ll_hw_reg - UART HW register structure.
 * @param[in]  pin_state - true(enable `) / false(disable clock)
 *
 * @return void None.
 */
static void hal_ll_uart_set_module( hal_ll_uart_base_handle_t* hal_ll_hw_reg, hal_ll_uart_state_t pin_state );

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
static void hal_ll_uart_set_transmitter( hal_ll_uart_base_handle_t* hal_ll_hw_reg, hal_ll_uart_state_t pin_state );

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
static void hal_ll_uart_set_receiver( hal_ll_uart_base_handle_t* hal_ll_hw_reg, hal_ll_uart_state_t pin_state );

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
static void hal_ll_uart_init( hal_ll_uart_hw_specifics_map_t* map );

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
static void hal_ll_uart_hw_init( hal_ll_uart_hw_specifics_map_t* map );

// ------------------------------------------------ PUBLIC FUNCTION DEFINITIONS
hal_ll_err_t hal_ll_uart_register_handle( hal_ll_pin_name_t tx_pin,
                                          hal_ll_pin_name_t rx_pin,
                                          hal_ll_uart_handle_register_t* handle_map,
                                          uint8_t* hal_module_id ) {
    hal_ll_uart_pin_id index_list[UART_MODULE_COUNT] = { HAL_LL_PIN_NC,HAL_LL_PIN_NC };
    uint16_t pin_check_result;

    // Check if pins are valid.
    if ( ( pin_check_result = hal_ll_uart_check_pins( tx_pin, rx_pin, &index_list, handle_map ) ) == HAL_LL_PIN_NC ) {
        return HAL_LL_UART_WRONG_PINS;
    };

    if ( ( hal_ll_uart_hw_specifics_map[pin_check_result].pins.tx_pin.pin_name != tx_pin ) ||
         ( hal_ll_uart_hw_specifics_map[pin_check_result].pins.rx_pin.pin_name != rx_pin ) )
    {
        hal_ll_uart_alternate_functions_set_state( &hal_ll_uart_hw_specifics_map[pin_check_result], false );

        hal_ll_uart_map_pins( pin_check_result, &index_list );

        hal_ll_uart_alternate_functions_set_state( &hal_ll_uart_hw_specifics_map[pin_check_result], true );

        handle_map[pin_check_result].init_ll_state = false;
    }

    *hal_module_id = pin_check_result;

    hal_ll_module_state[pin_check_result].hal_ll_uart_handle =
                       ( handle_t* )&hal_ll_uart_hw_specifics_map[pin_check_result].base;

    handle_map[pin_check_result].hal_ll_uart_handle =
              ( handle_t* )&hal_ll_module_state[pin_check_result].hal_ll_uart_handle;

    return HAL_LL_UART_SUCCESS;
}

hal_ll_err_t hal_ll_module_configure_uart( handle_t* handle ) {
    hal_ll_uart_hw_specifics_map_local = hal_ll_get_specifics( hal_ll_uart_get_module_state_address );
    hal_ll_uart_handle_register_t* hal_handle = ( hal_ll_uart_handle_register_t* )*handle;
    uint8_t pin_check_result = hal_ll_uart_hw_specifics_map_local->module_index;

    hal_ll_uart_init( hal_ll_uart_hw_specifics_map_local );

    hal_ll_module_state[pin_check_result].hal_ll_uart_handle =
                                        ( handle_t* )&hal_ll_uart_hw_specifics_map[pin_check_result].base;
    hal_ll_module_state[pin_check_result].init_ll_state = true;
    hal_handle->init_ll_state = true;

    return HAL_LL_UART_SUCCESS;
}

hal_ll_err_t hal_ll_uart_set_baud( handle_t* handle, uint32_t baud ) {
    low_level_handle = hal_ll_uart_get_handle;
    hal_ll_uart_hw_specifics_map_local = hal_ll_get_specifics( hal_ll_uart_get_module_state_address );

    low_level_handle->init_ll_state = false;

    hal_ll_uart_hw_specifics_map_local->baud_rate.baud = baud;

    hal_ll_uart_init( hal_ll_uart_hw_specifics_map_local );

    low_level_handle->init_ll_state = true;

    return hal_ll_uart_hw_specifics_map_local->baud_rate.real_baud;
}

hal_ll_err_t hal_ll_uart_set_parity( handle_t* handle, hal_ll_uart_parity_t parity ) {
    low_level_handle = hal_ll_uart_get_handle;
    hal_ll_uart_hw_specifics_map_local = hal_ll_get_specifics( hal_ll_uart_get_module_state_address );

    low_level_handle->init_ll_state = false;

    hal_ll_uart_hw_specifics_map_local->parity = parity;

    hal_ll_uart_init( hal_ll_uart_hw_specifics_map_local );

    low_level_handle->init_ll_state = true;

    return HAL_LL_UART_SUCCESS;
}

hal_ll_err_t hal_ll_uart_set_stop_bits( handle_t* handle, hal_ll_uart_stop_bits_t stop_bit ) {
    low_level_handle = hal_ll_uart_get_handle;
    hal_ll_uart_hw_specifics_map_local = hal_ll_get_specifics( hal_ll_uart_get_module_state_address );

    low_level_handle->init_ll_state = false;

    hal_ll_uart_hw_specifics_map_local->stop_bit = stop_bit;

    hal_ll_uart_init( hal_ll_uart_hw_specifics_map_local );

    low_level_handle->init_ll_state = true;

    return HAL_LL_UART_SUCCESS;
}

hal_ll_err_t hal_ll_uart_set_data_bits( handle_t* handle, hal_ll_uart_data_bits_t data_bit ) {
    low_level_handle = hal_ll_uart_get_handle;
    hal_ll_uart_hw_specifics_map_local = hal_ll_get_specifics( hal_ll_uart_get_module_state_address );

    if ( ( HAL_LL_UART_DATA_BITS_7 > data_bit ) || ( HAL_LL_UART_DATA_BITS_9 < data_bit ) ) {
        return HAL_LL_UART_MODULE_ERROR;
    }

    low_level_handle->init_ll_state = false;

    hal_ll_uart_hw_specifics_map_local->data_bit = data_bit;

    hal_ll_uart_init( hal_ll_uart_hw_specifics_map_local );

    low_level_handle->init_ll_state = true;

    return HAL_LL_UART_SUCCESS;
}

void hal_ll_uart_close( handle_t* handle ) {
    low_level_handle = hal_ll_uart_get_handle;
    hal_ll_uart_hw_specifics_map_local = hal_ll_get_specifics( hal_ll_uart_get_module_state_address );

    if ( low_level_handle->hal_ll_uart_handle != NULL ) {
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
        objects[hal_ll_uart_find_index( handle )] = NULL;

        low_level_handle->hal_ll_uart_handle = NULL;
        low_level_handle->hal_drv_uart_handle = NULL;

        low_level_handle->init_ll_state = false;
    }
}

void hal_ll_uart_register_irq_handler( handle_t* handle, hal_ll_uart_isr_t handler, handle_t obj ) {
    irq_handler = handler;
    hal_ll_uart_hw_specifics_map_local = hal_ll_get_specifics( hal_ll_uart_get_module_state_address );
    objects[hal_ll_uart_find_index( handle )] = obj;
}

void hal_ll_uart_irq_enable( handle_t* handle, hal_ll_uart_irq_t irq ) {
    low_level_handle = hal_ll_uart_get_handle;
    hal_ll_uart_hw_specifics_map_local = hal_ll_get_specifics( hal_ll_uart_get_module_state_address );

    hal_ll_uart_base_handle_t* hal_ll_hw_reg =
        ( hal_ll_uart_base_handle_t* )hal_ll_uart_hw_specifics_map_local->base;

    // SR_SUE must be set to 0 before modifying CR1 -> done in hw_init.
    switch ( irq ) {
        case HAL_LL_UART_IRQ_RX:
            set_reg_bit( &hal_ll_hw_reg->cr1, UART_CR1_INTRXWE_BIT );

            switch ( hal_ll_uart_hw_specifics_map_local->module_index ) {
                #ifdef UART_MODULE_0
                case hal_ll_uart_module_num( UART_MODULE_0 ):
                    hal_ll_core_enable_irq( UART0_RX_NVIC );
                    break;
                #endif
                #ifdef UART_MODULE_1
                case hal_ll_uart_module_num( UART_MODULE_1 ):
                    hal_ll_core_enable_irq( UART1_RX_NVIC );
                    break;
                #endif
                #ifdef UART_MODULE_2
                case hal_ll_uart_module_num( UART_MODULE_2 ):
                    hal_ll_core_enable_irq( UART2_RX_NVIC );
                    break;
                #endif
                #ifdef UART_MODULE_3
                case hal_ll_uart_module_num( UART_MODULE_3 ):
                    hal_ll_core_enable_irq( UART3_RX_NVIC );
                    break;
                #endif
                default:
                    break;
            }
            break;

        case HAL_LL_UART_IRQ_TX:
            set_reg_bit( &hal_ll_hw_reg->cr1, UART_CR1_INTTXWE_BIT );

            switch ( hal_ll_uart_hw_specifics_map_local->module_index ) {
                #ifdef UART_MODULE_0
                case hal_ll_uart_module_num( UART_MODULE_0 ):
                    hal_ll_core_enable_irq( UART0_TX_NVIC );
                    break;
                #endif
                #ifdef UART_MODULE_1
                case hal_ll_uart_module_num( UART_MODULE_1 ):
                    hal_ll_core_enable_irq( UART1_TX_NVIC );
                    break;
                #endif
                #ifdef UART_MODULE_2
                case hal_ll_uart_module_num( UART_MODULE_2 ):
                    hal_ll_core_enable_irq( UART2_TX_NVIC );
                    break;
                #endif
                #ifdef UART_MODULE_3
                case hal_ll_uart_module_num( UART_MODULE_3 ):
                    hal_ll_core_enable_irq( UART3_TX_NVIC );
                    break;
                #endif
                default:
                    break;
            }

            /*
             * INTTXWE is an edge-triggered interrupt which is set when one frame is transmitted (its stop bit detected)
             * therefore a kick is needed for the first ISR to be called.
             * This is done by setting the right bit in NVIC Interrupt Set-Pending Register.
             *
             * It is important to ensure this pending is done only at the beginning of one transmission session.
             * This is checked by verifying that:
             *   - no data is currently being transferred (SR<TRXUN> = 0)
             *   - TX FIFO is empty (SR<TLVL> = 0000)
             *
             * The s_tx_kick flag indicates that the kick has been done,
             * and is reset in irq_disable(), which is called after the last byte is sent (ring buffer empty).
             */
            if ( ( ( read_reg(&hal_ll_hw_reg->sr) & UART_SR_TXRUN_MASK ) == 0u ) &&
                 ( ( ( read_reg(&hal_ll_hw_reg->sr) & UART_SR_TLVL_MASK ) >> UART_SR_TLVL_POS ) == 0u ) &&
                 !s_tx_kick[ hal_ll_uart_hw_specifics_map_local->module_index ] ) {

                switch ( hal_ll_uart_hw_specifics_map_local->module_index ) {
                    #ifdef UART_MODULE_0
                    case hal_ll_uart_module_num( UART_MODULE_0 ):
                        hal_ll_core_port_nvic_set_pending_irq( UART0_TX_NVIC );
                        break;
                    #endif
                    #ifdef UART_MODULE_1
                    case hal_ll_uart_module_num( UART_MODULE_1 ):
                        hal_ll_core_port_nvic_set_pending_irq( UART1_TX_NVIC );
                        break;
                    #endif
                    #ifdef UART_MODULE_2
                    case hal_ll_uart_module_num( UART_MODULE_2 ):
                        hal_ll_core_port_nvic_set_pending_irq( UART2_TX_NVIC );
                        break;
                    #endif
                    #ifdef UART_MODULE_3
                    case hal_ll_uart_module_num( UART_MODULE_3 ):
                        hal_ll_core_port_nvic_set_pending_irq( UART3_TX_NVIC );
                        break;
                    #endif
                    default:
                        break;
                }

                s_tx_kick[ hal_ll_uart_hw_specifics_map_local->module_index ] = 1;
            }
            break;

        default:
            break;
    }
}

void hal_ll_uart_irq_disable( handle_t* handle, hal_ll_uart_irq_t irq ) {
    low_level_handle = hal_ll_uart_get_handle;
    hal_ll_uart_hw_specifics_map_local = hal_ll_get_specifics( hal_ll_uart_get_module_state_address );

    hal_ll_uart_base_handle_t* hal_ll_hw_reg =
        ( hal_ll_uart_base_handle_t* )hal_ll_uart_hw_specifics_map_local->base;

    switch ( irq ) {
        case HAL_LL_UART_IRQ_RX:
            clear_reg_bit( &hal_ll_hw_reg->cr1, UART_CR1_INTRXWE_BIT );

            switch ( hal_ll_uart_hw_specifics_map_local->module_index ) {
                #ifdef UART_MODULE_0
                case hal_ll_uart_module_num( UART_MODULE_0 ):
                    hal_ll_core_disable_irq( UART0_RX_NVIC );
                    break;
                #endif
                #ifdef UART_MODULE_1
                case hal_ll_uart_module_num( UART_MODULE_1 ):
                    hal_ll_core_disable_irq( UART1_RX_NVIC );
                    break;
                #endif
                #ifdef UART_MODULE_2
                case hal_ll_uart_module_num( UART_MODULE_2 ):
                    hal_ll_core_disable_irq( UART2_RX_NVIC );
                    break;
                #endif
                #ifdef UART_MODULE_3
                case hal_ll_uart_module_num( UART_MODULE_3 ):
                    hal_ll_core_disable_irq( UART3_RX_NVIC );
                    break;
                #endif
                default:
                    break;
            }
            break;

        case HAL_LL_UART_IRQ_TX:
            clear_reg_bit( &hal_ll_hw_reg->cr1, UART_CR1_INTTXWE_BIT );

            switch ( hal_ll_uart_hw_specifics_map_local->module_index ) {
                #ifdef UART_MODULE_0
                case hal_ll_uart_module_num( UART_MODULE_0 ):
                    hal_ll_core_disable_irq( UART0_TX_NVIC );
                    break;
                #endif
                #ifdef UART_MODULE_1
                case hal_ll_uart_module_num( UART_MODULE_1 ):
                    hal_ll_core_disable_irq( UART1_TX_NVIC );
                    break;
                #endif
                #ifdef UART_MODULE_2
                case hal_ll_uart_module_num( UART_MODULE_2 ):
                    hal_ll_core_disable_irq( UART2_TX_NVIC );
                    break;
                #endif
                #ifdef UART_MODULE_3
                case hal_ll_uart_module_num( UART_MODULE_3 ):
                    hal_ll_core_disable_irq( UART3_TX_NVIC );
                    break;
                #endif
                default:
                    break;
            }

            // HAL calls irq_disable() after the last byte is sent (ring buffer empty)
            // => set flag for new TX kick
            s_tx_kick[ hal_ll_uart_hw_specifics_map_local->module_index ] = 0;
            nvic_pending[ hal_ll_uart_hw_specifics_map_local->module_index ] = 0;
            break;

        default:
            break;
    }
}

void hal_ll_uart_write( handle_t* handle, uint8_t wr_data ) {
    hal_ll_uart_hw_specifics_map_local = hal_ll_get_specifics( hal_ll_uart_get_module_state_address );
    hal_ll_uart_base_handle_t* hal_ll_hw_reg =
                ( hal_ll_uart_base_handle_t* )hal_ll_uart_hw_specifics_map_local->base;

    hal_ll_hw_reg->dr = wr_data;
}

void hal_ll_uart_write_polling( handle_t* handle, uint8_t wr_data ) {
    hal_ll_uart_hw_specifics_map_local = hal_ll_get_specifics( hal_ll_uart_get_module_state_address );
    hal_ll_uart_base_handle_t* hal_ll_hw_reg =
                ( hal_ll_uart_base_handle_t* )hal_ll_uart_hw_specifics_map_local->base;

    /*
     * [UARTxSR]<TLVL> (Transmit FIFO data storage level) indicates the number of bytes
     * currently stored in the TX FIFO. The FIFO can hold up to 8 bytes.
     *
     * Wait until there is space for at least one more byte before writing new data.
     */
    while ( UART_TX_FIFO_SIZE <= ( ( read_reg( &hal_ll_hw_reg->sr ) & UART_SR_TLVL_MASK ) >> UART_SR_TLVL_POS ) ) {
        // Wait
    }

    hal_ll_hw_reg->dr = wr_data;
}

uint8_t hal_ll_uart_read( handle_t* handle ) {
    hal_ll_uart_hw_specifics_map_local = hal_ll_get_specifics( hal_ll_uart_get_module_state_address );
    hal_ll_uart_base_handle_t* hal_ll_hw_reg =
                ( hal_ll_uart_base_handle_t* )hal_ll_uart_hw_specifics_map_local->base;

    return hal_ll_hw_reg->dr;
}

uint8_t hal_ll_uart_read_polling( handle_t* handle ) {
    hal_ll_uart_hw_specifics_map_local = hal_ll_get_specifics( hal_ll_uart_get_module_state_address );
    hal_ll_uart_base_handle_t* hal_ll_hw_reg =
                ( hal_ll_uart_base_handle_t* )hal_ll_uart_hw_specifics_map_local->base;

    // Check if a data has been received to RX FIFO, if yes read it, if not then wait
    while ( !( ( read_reg( &hal_ll_hw_reg->sr ) & UART_SR_RLVL_MASK ) >> UART_SR_RLVL_POS ) ) {}

    return hal_ll_hw_reg->dr;
}

// ------------------------------------------------------------- DEFAULT EXCEPTION HANDLERS

#ifdef UART_MODULE_0
void INTSC0RX_Handler( void ) {
    hal_ll_uart_base_handle_t* hal_ll_hw_reg = ( hal_ll_uart_base_handle_t* )HAL_LL_UART0_BASE_ADDRESS;
    if ( hal_ll_uart_get_status_flags( HAL_LL_UART0_BASE_ADDRESS, UART_CR1_INTRXWE_MASK ) ) {
        if ( ( hal_ll_uart_get_interrupt_source( HAL_LL_UART0_BASE_ADDRESS, UART_SR_RXEND_MASK ) )) {
            write_reg( &hal_ll_hw_reg->sr, UART_SR_RXEND_MASK ); /* W1C */
            irq_handler( objects[hal_ll_uart_module_num( UART_MODULE_0 )], HAL_LL_UART_IRQ_RX );
        }
    }
}

void INTSC0TX_Handler( void ) {
    hal_ll_uart_base_handle_t* hal_ll_hw_reg = ( hal_ll_uart_base_handle_t* )HAL_LL_UART0_BASE_ADDRESS;
    if ( hal_ll_uart_get_status_flags( HAL_LL_UART0_BASE_ADDRESS, UART_CR1_INTTXWE_MASK ) ) {
        if( nvic_pending[hal_ll_uart_module_num( UART_MODULE_0 )] == 0 ){
            irq_handler( objects[hal_ll_uart_module_num( UART_MODULE_0 )], HAL_LL_UART_IRQ_TX );
            nvic_pending[hal_ll_uart_module_num( UART_MODULE_0 )] = 1;
        } else {
            if ( ( hal_ll_uart_get_interrupt_source( HAL_LL_UART0_BASE_ADDRESS, UART_SR_TXEND_MASK ) )) {
                write_reg( &hal_ll_hw_reg->sr, UART_SR_TXEND_MASK ); /* W1C */
                irq_handler( objects[hal_ll_uart_module_num( UART_MODULE_0 )], HAL_LL_UART_IRQ_TX );
            }
        }
    }
}
#endif

#ifdef UART_MODULE_1
void INTSC1RX_Handler( void ) {
    hal_ll_uart_base_handle_t* hal_ll_hw_reg = ( hal_ll_uart_base_handle_t* )HAL_LL_UART1_BASE_ADDRESS;
    if ( hal_ll_uart_get_status_flags( HAL_LL_UART1_BASE_ADDRESS, UART_CR1_INTRXWE_MASK ) ) {
        if ( ( hal_ll_uart_get_interrupt_source( HAL_LL_UART1_BASE_ADDRESS, UART_SR_RXEND_MASK ) )) {
            write_reg( &hal_ll_hw_reg->sr, UART_SR_RXEND_MASK ); /* W1C */
            irq_handler( objects[hal_ll_uart_module_num( UART_MODULE_1 )], HAL_LL_UART_IRQ_RX );
        }
    }
}

void INTSC1TX_Handler( void ) {
    hal_ll_uart_base_handle_t* hal_ll_hw_reg = ( hal_ll_uart_base_handle_t* )HAL_LL_UART1_BASE_ADDRESS;
    if ( hal_ll_uart_get_status_flags( HAL_LL_UART1_BASE_ADDRESS, UART_CR1_INTTXWE_MASK ) ) {
        if( nvic_pending[hal_ll_uart_module_num( UART_MODULE_1 )] == 0 ){
            irq_handler( objects[hal_ll_uart_module_num( UART_MODULE_1 )], HAL_LL_UART_IRQ_TX );
            nvic_pending[hal_ll_uart_module_num( UART_MODULE_1 )] = 1;
        } else {
            if ( ( hal_ll_uart_get_interrupt_source( HAL_LL_UART1_BASE_ADDRESS, UART_SR_TXEND_MASK ) )) {
                write_reg( &hal_ll_hw_reg->sr, UART_SR_TXEND_MASK ); /* W1C */
                irq_handler( objects[hal_ll_uart_module_num( UART_MODULE_1 )], HAL_LL_UART_IRQ_TX );
            }
        }
    }
}
#endif

#ifdef UART_MODULE_2
void INTSC2RX_Handler( void ) {
    hal_ll_uart_base_handle_t* hal_ll_hw_reg = ( hal_ll_uart_base_handle_t* )HAL_LL_UART2_BASE_ADDRESS;
    if ( hal_ll_uart_get_status_flags( HAL_LL_UART2_BASE_ADDRESS, UART_CR1_INTRXWE_MASK ) ) {
        if ( ( hal_ll_uart_get_interrupt_source( HAL_LL_UART2_BASE_ADDRESS, UART_SR_RXEND_MASK ) )) {
            write_reg( &hal_ll_hw_reg->sr, UART_SR_RXEND_MASK ); /* W1C */
            irq_handler( objects[hal_ll_uart_module_num( UART_MODULE_2 )], HAL_LL_UART_IRQ_RX );
        }
    }
}

void INTSC2TX_Handler( void ) {
    hal_ll_uart_base_handle_t* hal_ll_hw_reg = ( hal_ll_uart_base_handle_t* )HAL_LL_UART2_BASE_ADDRESS;
    if ( hal_ll_uart_get_status_flags( HAL_LL_UART2_BASE_ADDRESS, UART_CR1_INTTXWE_MASK ) ) {
        if( nvic_pending[hal_ll_uart_module_num( UART_MODULE_2 )] == 0 ){
            irq_handler( objects[hal_ll_uart_module_num( UART_MODULE_2 )], HAL_LL_UART_IRQ_TX );
            nvic_pending[hal_ll_uart_module_num( UART_MODULE_2 )] = 1;
        } else {
            if ( ( hal_ll_uart_get_interrupt_source( HAL_LL_UART2_BASE_ADDRESS, UART_SR_TXEND_MASK ) )) {
                write_reg( &hal_ll_hw_reg->sr, UART_SR_TXEND_MASK ); /* W1C */
                irq_handler( objects[hal_ll_uart_module_num( UART_MODULE_2 )], HAL_LL_UART_IRQ_TX );
            }
        }
    }
}
#endif

#ifdef UART_MODULE_3
void INTSC3RX_Handler( void ) {
    hal_ll_uart_base_handle_t* hal_ll_hw_reg = ( hal_ll_uart_base_handle_t* )HAL_LL_UART3_BASE_ADDRESS;
    if ( hal_ll_uart_get_status_flags( HAL_LL_UART3_BASE_ADDRESS, UART_CR1_INTRXWE_MASK ) ) {
        if ( ( hal_ll_uart_get_interrupt_source( HAL_LL_UART3_BASE_ADDRESS, UART_SR_RXEND_MASK ) )) {
            write_reg( &hal_ll_hw_reg->sr, UART_SR_RXEND_MASK ); /* W1C */
            irq_handler( objects[hal_ll_uart_module_num( UART_MODULE_3 )], HAL_LL_UART_IRQ_RX );
        }
    }
}

void INTSC3TX_Handler( void ) {
    hal_ll_uart_base_handle_t* hal_ll_hw_reg = ( hal_ll_uart_base_handle_t* )HAL_LL_UART3_BASE_ADDRESS;
    if ( hal_ll_uart_get_status_flags( HAL_LL_UART3_BASE_ADDRESS, UART_CR1_INTTXWE_MASK ) ) {
        if( nvic_pending[hal_ll_uart_module_num( UART_MODULE_3 )] == 0 ){
            irq_handler( objects[hal_ll_uart_module_num( UART_MODULE_3 )], HAL_LL_UART_IRQ_TX );
            nvic_pending[hal_ll_uart_module_num( UART_MODULE_3 )] = 1;
        } else {
            if ( ( hal_ll_uart_get_interrupt_source( HAL_LL_UART3_BASE_ADDRESS, UART_SR_TXEND_MASK ) )) {
                write_reg( &hal_ll_hw_reg->sr, UART_SR_TXEND_MASK ); /* WIC */
                irq_handler( objects[hal_ll_uart_module_num( UART_MODULE_3 )], HAL_LL_UART_IRQ_TX );
            }
        }
    }
}
#endif

// ----------------------------------------------- PRIVATE FUNCTION DEFINITIONS
static uint8_t hal_ll_uart_find_index( handle_t* handle ) {
    hal_ll_uart_hw_specifics_map_local = hal_ll_get_specifics( hal_ll_uart_get_module_state_address );

    if ( HAL_LL_MODULE_ERROR != hal_ll_uart_hw_specifics_map_local->base ) {
        return hal_ll_uart_hw_specifics_map_local->module_index;
    } else {
        return NULL;
    }
}

static hal_ll_pin_name_t hal_ll_uart_check_pins( hal_ll_pin_name_t tx_pin,
                                                 hal_ll_pin_name_t rx_pin,
                                                 hal_ll_uart_pin_id* index_list,
                                                 hal_ll_uart_handle_register_t* handle_map ) {
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
                    if ( hal_ll_uart_tx_map[tx_index].base == hal_ll_uart_rx_map[rx_index].base ) {
                        // Get module number.
                        hal_ll_module_id = hal_ll_uart_tx_map[tx_index].module_index;

                        // Map pin names.
                        index_list[hal_ll_module_id].pin_tx = tx_index;
                        index_list[hal_ll_module_id].pin_rx = rx_index;

                        // Check if module is taken.
                        if ( NULL == handle_map[hal_ll_module_id].hal_drv_uart_handle ) {
                            return hal_ll_module_id;
                        }
                        else if ( UART_MODULE_COUNT == ++index_counter ) {
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

static hal_ll_uart_hw_specifics_map_t* hal_ll_get_specifics( handle_t handle ) {
    uint8_t hal_ll_module_count = sizeof( hal_ll_module_state ) / ( sizeof( hal_ll_uart_handle_register_t ) );
    static uint8_t hal_ll_module_error = sizeof( hal_ll_module_state ) / ( sizeof( hal_ll_uart_handle_register_t ) );

    while ( hal_ll_module_count-- ) {
        if ( hal_ll_uart_get_base_from_hal_handle == hal_ll_uart_hw_specifics_map[hal_ll_module_count].base ) {
            return &hal_ll_uart_hw_specifics_map[hal_ll_module_count];
        }
    }

    return &hal_ll_uart_hw_specifics_map[hal_ll_module_error];
}

static void hal_ll_uart_set_clock( hal_ll_uart_hw_specifics_map_t* map, bool hal_ll_state ) {

    uint32_t* sysma_addr = ( uint32_t* )HAL_LL_CG_BASE_FSYSMENA_ADDR;
    uint32_t* protect_addr = ( uint32_t* )HAL_LL_CG_BASE_PROTECT_ADDR;

    // Writing 0xC1 in CGPROTECT<PROTECT[7:0]> makes CG registers write-enabled
    set_reg_bits( protect_addr, 0xC1 );

    switch ( map->module_index )
    {
        #ifdef UART_MODULE_0
        case ( hal_ll_uart_module_num( UART_MODULE_0 ) ):
            ( hal_ll_state == true ) ? ( set_reg_bit( sysma_addr, CGFSYSMENA_IPMENA_UART0_BIT ) ) :
                                       ( clear_reg_bit( sysma_addr, CGFSYSMENA_IPMENA_UART0_BIT ) );
            break;
        #endif

        #ifdef UART_MODULE_1
        case ( hal_ll_uart_module_num( UART_MODULE_1 ) ):
            ( hal_ll_state == true ) ? ( set_reg_bit( sysma_addr, CGFSYSMENA_IPMENA_UART1_BIT ) ) :
                                       ( clear_reg_bit( sysma_addr, CGFSYSMENA_IPMENA_UART1_BIT ) );
            break;
        #endif

        #ifdef UART_MODULE_2
        case ( hal_ll_uart_module_num( UART_MODULE_2 ) ):
            ( hal_ll_state == true ) ? ( set_reg_bit( sysma_addr, CGFSYSMENA_IPMENA_UART2_BIT ) ) :
                                       ( clear_reg_bit( sysma_addr, CGFSYSMENA_IPMENA_UART2_BIT ) );
            break;
        #endif

        #ifdef UART_MODULE_3
        case ( hal_ll_uart_module_num( UART_MODULE_3 ) ):
            ( hal_ll_state == true ) ? ( set_reg_bit( sysma_addr, CGFSYSMENA_IPMENA_UART3_BIT ) ) :
                                       ( clear_reg_bit( sysma_addr, CGFSYSMENA_IPMENA_UART3_BIT ) );
            break;
        #endif

        default:
            break;
    }
}

static void hal_ll_uart_map_pins( uint8_t module_index, hal_ll_uart_pin_id* index_list ) {
    // Map new pins.
    hal_ll_uart_hw_specifics_map[module_index].pins.tx_pin.pin_name =
                                               hal_ll_uart_tx_map[index_list[module_index].pin_tx].pin;
    hal_ll_uart_hw_specifics_map[module_index].pins.rx_pin.pin_name =
                                               hal_ll_uart_rx_map[index_list[module_index].pin_rx].pin;
    // TX and RX could have different alternate function settings, hence save both AF values.
    hal_ll_uart_hw_specifics_map[module_index].pins.tx_pin.pin_af =
                                               hal_ll_uart_tx_map[index_list[module_index].pin_tx].af;
    hal_ll_uart_hw_specifics_map[module_index].pins.rx_pin.pin_af =
                                               hal_ll_uart_rx_map[index_list[module_index].pin_rx].af;
}

static void hal_ll_uart_alternate_functions_set_state( hal_ll_uart_hw_specifics_map_t* map,
                                                       bool hal_ll_state ) {
    module_struct module;
    uint32_t uart_config = 0;

    if ( ( map->pins.rx_pin.pin_name != HAL_LL_PIN_NC ) &&
        ( map->pins.tx_pin.pin_name != HAL_LL_PIN_NC ) )
    {
        module.pins[0] = VALUE( map->pins.tx_pin.pin_name, map->pins.tx_pin.pin_af );
        module.pins[1] = VALUE( map->pins.rx_pin.pin_name, map->pins.rx_pin.pin_af );
        module.pins[2] = GPIO_MODULE_STRUCT_END;

        module.configs[0] = GPIO_CFG_CR | GPIO_OUTPUT_HIGH;
        module.configs[1] = GPIO_CFG_MODE_DIGITAL_INPUT | GPIO_CFG_PULL_UP;
        module.configs[2] = GPIO_MODULE_STRUCT_END;

        hal_ll_gpio_module_struct_init( &module, hal_ll_state );
    }
}

static void hal_ll_uart_set_baud_bare_metal( hal_ll_uart_hw_specifics_map_t* map ) {
    hal_ll_uart_base_handle_t* hal_ll_hw_reg = hal_ll_uart_get_base_struct( map->base );

    /*
     * f_baud = ( f_tranfer_clock / ( N + ( 64 - k )/64 ) ) / 16 -> RM page 12 3.2
     * N = BRD<BRN> (integer divisor)
     * K = BRD<BRK> (fractional fine-tuning)
     * BRD<KEN> must be enabled for fraction tuning
     */

    // Fetch uart tranfer clock and the baud rate user wants to set
    uint32_t fclk = hal_ll_uart_get_clock_speed();
    uint32_t baud = map->baud_rate.baud;

    // Calculate ideal div = N + ( 64 - k )/64 ) with the baud user wants to set
    double div = ( double )fclk / ( 16.0 * ( double )baud );

    /*
     * example : f_tranfer_clock = 40MHz and  baud = 9600 => div = 260.4166...
     * now separte divisor into the whole part and the decimal remainder
     * N = 260, frac = 0.4166
     */
    uint32_t N = ( uint32_t )div;
    double frac = div - ( double )N;

    // ( 64 - k )/64 ) = frac => k = 64 - 64*frac = (1 - frac) * 64
    uint32_t K = ( uint32_t )lround( ( 1.0 - frac ) * 64.0 );

    /*
     * if K = 64 means that div should be equal to N, as if there is no fraction
     * instead of div = N + 0  => K = 64 , BRK is 6bits long(0...63)
     * div = (N - 1) + (64 - 0)/64 => (K = 0)
     */
    if ( K == 64 ) {
        if ( N > 0 ) N -= 1;
        K = 0;
    }

    write_field_reg( &hal_ll_hw_reg->brd, UART_BRD_BRN_MASK, ( N << UART_BRD_BRN_POS ) );
    write_field_reg( &hal_ll_hw_reg->brd, UART_BRD_BRK_MASK, ( K << UART_BRD_BRK_POS ) );
    set_reg_bit( &hal_ll_hw_reg->brd, UART_BRD_KEN_BIT );  // enable fractions

    // map the real baud rate
    map->baud_rate.real_baud = ( uint32_t )( ( double )fclk /
                                             ( 16.0 * ( ( double )N + ( double )( 64 - K )/64.0 ) ) );
}

static uint32_t hal_ll_uart_get_clock_speed( void ) {

    /*
     * UART transfer clock comes from 'prescaled' FT0 which is a middle-speed system clock (fsysm)
     * max fsysm = 80MHz -> RM page 18 - 1.2.6. System Clock
     */
    CG_ClocksTypeDef cg;
    CG_GetClocksFrequency( &cg );

    return cg.CG_FT0M_Frequency;
}

static void hal_ll_uart_set_stop_bits_bare_metal( hal_ll_uart_hw_specifics_map_t* map ) {
    hal_ll_uart_base_handle_t* hal_ll_hw_reg = hal_ll_uart_get_base_struct( map->base );

    // SR_SUE must be set to 0 before this reg CR0 can be modified - > done in uart_hw_init
    switch ( map->stop_bit )
    {
        case HAL_LL_UART_STOP_BITS_ONE:
            clear_reg_bit( &hal_ll_hw_reg->cr0, UART_CR0_STOP_BIT_POS );
            break;
        case HAL_LL_UART_STOP_BITS_TWO:
            set_reg_bit( &hal_ll_hw_reg->cr0, UART_CR0_STOP_BIT_POS );
            break;

        default:
            break;
    }
}

static void hal_ll_uart_set_data_bits_bare_metal( hal_ll_uart_hw_specifics_map_t* map ) {
    hal_ll_uart_base_handle_t* hal_ll_hw_reg = hal_ll_uart_get_base_struct( map->base );

    /// SR_SUE must be set to 0 before this reg CR0 can be modified - > done in uart_hw_init
    switch ( map->data_bit )
    {
        case HAL_LL_UART_DATA_BITS_7:
            write_field_reg( &hal_ll_hw_reg->cr0, UART_CR0_SM_MASK, UART_CR0_DATA_BITS_7 );
            break;

        case HAL_LL_UART_DATA_BITS_8:
            write_field_reg( &hal_ll_hw_reg->cr0, UART_CR0_SM_MASK, UART_CR0_DATA_BITS_8 );
            break;

        case HAL_LL_UART_DATA_BITS_9:
            write_field_reg( &hal_ll_hw_reg->cr0, UART_CR0_SM_MASK, UART_CR0_DATA_BITS_9 );
            break;

        default:
            break;
    }
}

static void hal_ll_uart_set_parity_bare_metal( hal_ll_uart_hw_specifics_map_t* map ) {
    hal_ll_uart_base_handle_t* hal_ll_hw_reg = hal_ll_uart_get_base_struct( map->base );

    // SR_SUE must be set to 0 before this reg CR0 can be modified - > done in uart_hw_init
    switch ( map->parity )
    {
        case HAL_LL_UART_PARITY_NONE:
            clear_reg_bit( &hal_ll_hw_reg->cr0, UART_CR0_PARITY_ENABLE_BIT );
            break;
        case HAL_LL_UART_PARITY_EVEN:
            set_reg_bit( &hal_ll_hw_reg->cr0, UART_CR0_PARITY_ENABLE_BIT );
            set_reg_bit( &hal_ll_hw_reg->cr0, UART_CR0_PARITY_BIT );
            break;
        case HAL_LL_UART_PARITY_ODD:
            set_reg_bit( &hal_ll_hw_reg->cr0, UART_CR0_PARITY_ENABLE_BIT );
            clear_reg_bit( &hal_ll_hw_reg->cr0, UART_CR0_PARITY_BIT );
            break;

        default:
            break;
    }
}

static void hal_ll_uart_set_module( hal_ll_uart_base_handle_t* hal_ll_hw_reg,
                                    hal_ll_uart_state_t pin_state ) {

    // UART transfer clock FTx = fsysm
    hal_ll_hw_reg->clk = UART_CLK_PRSEL_0;
}

static void hal_ll_uart_set_transmitter( hal_ll_uart_base_handle_t* hal_ll_hw_reg,
                                         hal_ll_uart_state_t pin_state ) {

    switch ( pin_state )
    {
        case HAL_LL_UART_DISABLE:
            clear_reg_bit( &hal_ll_hw_reg->trans, UART_TRANS_TXE_BIT );
            break;

        case HAL_LL_UART_ENABLE:
            set_reg_bit( &hal_ll_hw_reg->trans, UART_TRANS_TXE_BIT );
            break;

        default:
            break;
    }
}

static void hal_ll_uart_set_receiver( hal_ll_uart_base_handle_t* hal_ll_hw_reg,
                                      hal_ll_uart_state_t pin_state ) {

    switch ( pin_state )
    {
        case HAL_LL_UART_DISABLE:
            clear_reg_bit( &hal_ll_hw_reg->trans, UART_TRANS_RXE_BIT );
            break;

        case HAL_LL_UART_ENABLE:
            set_reg_bit( &hal_ll_hw_reg->trans, UART_TRANS_RXE_BIT );
            break;

        default:
            break;
    }
}

static void hal_ll_uart_clear_regs( hal_ll_uart_base_handle_t* hal_ll_hw_reg ) {
    // Initialize FIFO pointers
    write_reg( &hal_ll_hw_reg->fifoclr, ( 1u<<UART_FIFOCLR_TFCLR_BIT ) | ( 1u<<UART_FIFOCLR_RFCLR_BIT ) );
    // Disable Transmission and Reception
    clear_reg( &hal_ll_hw_reg->trans );
}

static void hal_ll_uart_hw_init( hal_ll_uart_hw_specifics_map_t* map ) {

    hal_ll_uart_base_handle_t* hal_ll_hw_reg = hal_ll_uart_get_base_struct( map->base );

    /*
     * The sequence of the write of "10" and the next write of "01" generates the software reset. => <SUE> is "0"
     * only now can certain registers be updated
     * this also clears TRANS<TXE> and TRANS<RXE> and initialises FIFO pointers
     */
    write_field_reg( &hal_ll_hw_reg->swrst, UART_SWRST_MASK, UART_SWRST_MASK_10 );
    write_field_reg( &hal_ll_hw_reg->swrst, UART_SWRST_MASK, UART_SWRST_MASK_01 );

    hal_ll_uart_clear_regs( map->base );

    hal_ll_uart_set_module( map->base, HAL_LL_UART_ENABLE );

    hal_ll_uart_set_baud_bare_metal( map );
    hal_ll_uart_set_data_bits_bare_metal( map );
    hal_ll_uart_set_parity_bare_metal( map );
    hal_ll_uart_set_stop_bits_bare_metal( map );

    // At lower baud rates it's easier for RXD to mistake noise for a false START bit
    hal_ll_uart_set_rx_noise_filter( hal_ll_hw_reg, FIVE_CYCLES_OR_LESS );

    hal_ll_uart_set_transmitter( map->base, HAL_LL_UART_ENABLE );

    hal_ll_uart_set_receiver( map->base, HAL_LL_UART_ENABLE );
}

static void hal_ll_uart_init( hal_ll_uart_hw_specifics_map_t* map ) {
    hal_ll_uart_set_clock( map, true );

    hal_ll_uart_alternate_functions_set_state( map, true );

    hal_ll_uart_hw_init( map );
}

// ------------------------------------------------------------------------- END
