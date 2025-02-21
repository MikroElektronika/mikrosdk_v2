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

#include "hal_ll_pps.h"
#include "hal_ll_gpio.h"
#include "hal_ll_core.h"
#include "hal_ll_uart.h"
#include "hal_ll_uart_pin_map.h"
#include "assembly.h"
#include "delays.h"

/*!< @brief Local handle list */
static volatile hal_ll_uart_handle_register_t hal_ll_module_state[UART_MODULE_COUNT] = { (handle_t *)NULL, (handle_t *)NULL, false };

// ------------------------------------------------------------- PRIVATE MACROS
/*!< @brief Macro used for module interrupt disabling.
 * Used in interrupt handlers.
 */
#if defined(UART_MODULE_1) && defined(UART_MODULE_2) && \
    defined(UART_MODULE_3) && defined(UART_MODULE_4) && \
    defined(UART_MODULE_5) && defined(UART_MODULE_6)
#define __HAL_LL_UART_DISABLE_IT_RX(_num,_int) (_num==hal_ll_uart_module_num(UART_MODULE_1))?(clear_reg_bit(HAL_LL_UART_1_IEC_RX_ADDRESS,_int)): \
                                               (_num==hal_ll_uart_module_num(UART_MODULE_2))?(clear_reg_bit(HAL_LL_UART_2_IEC_RX_ADDRESS,_int)): \
                                               (_num==hal_ll_uart_module_num(UART_MODULE_3))?(clear_reg_bit(HAL_LL_UART_3_IEC_RX_ADDRESS,_int)): \
                                               (_num==hal_ll_uart_module_num(UART_MODULE_4))?(clear_reg_bit(HAL_LL_UART_4_IEC_RX_ADDRESS,_int)): \
                                               (_num==hal_ll_uart_module_num(UART_MODULE_5))?(clear_reg_bit(HAL_LL_UART_5_IEC_RX_ADDRESS,_int)): \
                                               (clear_reg_bit(HAL_LL_UART_6_IEC_RX_ADDRESS,_int))
#elif defined(UART_MODULE_1) && defined(UART_MODULE_2) && \
      defined(UART_MODULE_3) && defined(UART_MODULE_4) && \
      defined(UART_MODULE_5)
#define __HAL_LL_UART_DISABLE_IT_RX(_num,_int) (_num==hal_ll_uart_module_num(UART_MODULE_1))?(clear_reg_bit(HAL_LL_UART_1_IEC_RX_ADDRESS,_int)): \
                                               (_num==hal_ll_uart_module_num(UART_MODULE_2))?(clear_reg_bit(HAL_LL_UART_2_IEC_RX_ADDRESS,_int)): \
                                               (_num==hal_ll_uart_module_num(UART_MODULE_3))?(clear_reg_bit(HAL_LL_UART_3_IEC_RX_ADDRESS,_int)): \
                                               (_num==hal_ll_uart_module_num(UART_MODULE_4))?(clear_reg_bit(HAL_LL_UART_4_IEC_RX_ADDRESS,_int)): \
                                               (clear_reg_bit(HAL_LL_UART_5_IEC_RX_ADDRESS,_int))
#elif defined(UART_MODULE_1) && defined(UART_MODULE_2) && \
      defined(UART_MODULE_3) && defined(UART_MODULE_4)
#define __HAL_LL_UART_DISABLE_IT_RX(_num,_int) (_num==hal_ll_uart_module_num(UART_MODULE_1))?(clear_reg_bit(HAL_LL_UART_1_IEC_RX_ADDRESS,_int)): \
                                               (_num==hal_ll_uart_module_num(UART_MODULE_2))?(clear_reg_bit(HAL_LL_UART_2_IEC_RX_ADDRESS,_int)): \
                                               (_num==hal_ll_uart_module_num(UART_MODULE_3))?(clear_reg_bit(HAL_LL_UART_3_IEC_RX_ADDRESS,_int)): \
                                               (clear_reg_bit(HAL_LL_UART_4_IEC_RX_ADDRESS,_int))
#elif defined(UART_MODULE_1) && defined(UART_MODULE_2)
#define __HAL_LL_UART_DISABLE_IT_RX(_num,_int) (_num==hal_ll_uart_module_num(UART_MODULE_1))?(clear_reg_bit(HAL_LL_UART_1_IEC_RX_ADDRESS,_int)): \
                                               (clear_reg_bit(HAL_LL_UART_2_IEC_RX_ADDRESS,_int))
#else
#   error “Modules not defined adequately. Check `mcu_definitions` file and low level UART implementation.”
#endif

#if defined(UART_MODULE_1) && defined(UART_MODULE_2) && \
    defined(UART_MODULE_3) && defined(UART_MODULE_4) && \
    defined(UART_MODULE_5) && defined(UART_MODULE_6)
#define __HAL_LL_UART_DISABLE_IT_TX(_num,_int) (_num==hal_ll_uart_module_num(UART_MODULE_1))?(clear_reg_bit(HAL_LL_UART_1_IEC_TX_ADDRESS,_int)): \
                                               (_num==hal_ll_uart_module_num(UART_MODULE_2))?(clear_reg_bit(HAL_LL_UART_2_IEC_TX_ADDRESS,_int)): \
                                               (_num==hal_ll_uart_module_num(UART_MODULE_3))?(clear_reg_bit(HAL_LL_UART_3_IEC_TX_ADDRESS,_int)): \
                                               (_num==hal_ll_uart_module_num(UART_MODULE_4))?(clear_reg_bit(HAL_LL_UART_4_IEC_TX_ADDRESS,_int)): \
                                               (_num==hal_ll_uart_module_num(UART_MODULE_5))?(clear_reg_bit(HAL_LL_UART_5_IEC_TX_ADDRESS,_int)): \
                                               (clear_reg_bit(HAL_LL_UART_6_IEC_TX_ADDRESS,_int))
#elif defined(UART_MODULE_1) && defined(UART_MODULE_2) && \
      defined(UART_MODULE_3) && defined(UART_MODULE_4) && \
      defined(UART_MODULE_5)
#define __HAL_LL_UART_DISABLE_IT_TX(_num,_int) (_num==hal_ll_uart_module_num(UART_MODULE_1))?(clear_reg_bit(HAL_LL_UART_1_IEC_TX_ADDRESS,_int)): \
                                               (_num==hal_ll_uart_module_num(UART_MODULE_2))?(clear_reg_bit(HAL_LL_UART_2_IEC_TX_ADDRESS,_int)): \
                                               (_num==hal_ll_uart_module_num(UART_MODULE_3))?(clear_reg_bit(HAL_LL_UART_3_IEC_TX_ADDRESS,_int)): \
                                               (_num==hal_ll_uart_module_num(UART_MODULE_4))?(clear_reg_bit(HAL_LL_UART_4_IEC_TX_ADDRESS,_int)): \
                                               (clear_reg_bit(HAL_LL_UART_5_IEC_TX_ADDRESS,_int))
#elif defined(UART_MODULE_1) && defined(UART_MODULE_2) && \
      defined(UART_MODULE_3) && defined(UART_MODULE_4)
#define __HAL_LL_UART_DISABLE_IT_TX(_num,_int) (_num==hal_ll_uart_module_num(UART_MODULE_1))?(clear_reg_bit(HAL_LL_UART_1_IEC_TX_ADDRESS,_int)): \
                                               (_num==hal_ll_uart_module_num(UART_MODULE_2))?(clear_reg_bit(HAL_LL_UART_2_IEC_TX_ADDRESS,_int)): \
                                               (_num==hal_ll_uart_module_num(UART_MODULE_3))?(clear_reg_bit(HAL_LL_UART_3_IEC_TX_ADDRESS,_int)): \
                                               (clear_reg_bit(HAL_LL_UART_4_IEC_TX_ADDRESS,_int))
#elif defined(UART_MODULE_1) && defined(UART_MODULE_2)
#define __HAL_LL_UART_DISABLE_IT_TX(_num,_int) (_num==hal_ll_uart_module_num(UART_MODULE_1))?(clear_reg_bit(HAL_LL_UART_1_IEC_TX_ADDRESS,_int)): \
                                               (clear_reg_bit(HAL_LL_UART_2_IEC_TX_ADDRESS,_int))
#else
#   error “Modules not defined adequately. Check `mcu_definitions` file and low level UART implementation.”
#endif
/*!< @brief Macro used for module interrupt enabling.
 * Used in interrupt handlers.
 */
#if defined(UART_MODULE_1) && defined(UART_MODULE_2) && \
    defined(UART_MODULE_3) && defined(UART_MODULE_4) && \
    defined(UART_MODULE_5) && defined(UART_MODULE_6)
#define __HAL_LL_UART_ENABLE_IT_RX(_num,_int)  (_num==hal_ll_uart_module_num(UART_MODULE_1))?(set_reg_bit(HAL_LL_UART_1_IEC_RX_ADDRESS,_int)): \
                                               (_num==hal_ll_uart_module_num(UART_MODULE_2))?(set_reg_bit(HAL_LL_UART_2_IEC_RX_ADDRESS,_int)): \
                                               (_num==hal_ll_uart_module_num(UART_MODULE_3))?(set_reg_bit(HAL_LL_UART_3_IEC_RX_ADDRESS,_int)): \
                                               (_num==hal_ll_uart_module_num(UART_MODULE_4))?(set_reg_bit(HAL_LL_UART_4_IEC_RX_ADDRESS,_int)): \
                                               (_num==hal_ll_uart_module_num(UART_MODULE_5))?(set_reg_bit(HAL_LL_UART_5_IEC_RX_ADDRESS,_int)): \
                                               (set_reg_bit(HAL_LL_UART_6_IEC_RX_ADDRESS,_int))
#elif defined(UART_MODULE_1) && defined(UART_MODULE_2) && \
      defined(UART_MODULE_3) && defined(UART_MODULE_4) && \
      defined(UART_MODULE_5)
#define __HAL_LL_UART_ENABLE_IT_RX(_num,_int)  (_num==hal_ll_uart_module_num(UART_MODULE_1))?(set_reg_bit(HAL_LL_UART_1_IEC_RX_ADDRESS,_int)): \
                                               (_num==hal_ll_uart_module_num(UART_MODULE_2))?(set_reg_bit(HAL_LL_UART_2_IEC_RX_ADDRESS,_int)): \
                                               (_num==hal_ll_uart_module_num(UART_MODULE_3))?(set_reg_bit(HAL_LL_UART_3_IEC_RX_ADDRESS,_int)): \
                                               (_num==hal_ll_uart_module_num(UART_MODULE_4))?(set_reg_bit(HAL_LL_UART_4_IEC_RX_ADDRESS,_int)): \
                                               (set_reg_bit(HAL_LL_UART_5_IEC_RX_ADDRESS,_int))
#elif defined(UART_MODULE_1) && defined(UART_MODULE_2) && \
      defined(UART_MODULE_3) && defined(UART_MODULE_4)
#define __HAL_LL_UART_ENABLE_IT_RX(_num,_int)  (_num==hal_ll_uart_module_num(UART_MODULE_1))?(set_reg_bit(HAL_LL_UART_1_IEC_RX_ADDRESS,_int)): \
                                               (_num==hal_ll_uart_module_num(UART_MODULE_2))?(set_reg_bit(HAL_LL_UART_2_IEC_RX_ADDRESS,_int)): \
                                               (_num==hal_ll_uart_module_num(UART_MODULE_3))?(set_reg_bit(HAL_LL_UART_3_IEC_RX_ADDRESS,_int)): \
                                               (set_reg_bit(HAL_LL_UART_4_IEC_RX_ADDRESS,_int))
#elif defined(UART_MODULE_1) && defined(UART_MODULE_2)
#define __HAL_LL_UART_ENABLE_IT_RX(_num,_int)  (_num==hal_ll_uart_module_num(UART_MODULE_1))?(set_reg_bit(HAL_LL_UART_1_IEC_RX_ADDRESS,_int)): \
                                               (set_reg_bit(HAL_LL_UART_2_IEC_RX_ADDRESS,_int))
#else
#   error “Modules not defined adequately. Check `mcu_definitions` file and low level UART implementation.”
#endif

#if defined(UART_MODULE_1) && defined(UART_MODULE_2) && \
    defined(UART_MODULE_3) && defined(UART_MODULE_4) && \
    defined(UART_MODULE_5) && defined(UART_MODULE_6)
#define __HAL_LL_UART_ENABLE_IT_TX(_num,_int)  (_num==hal_ll_uart_module_num(UART_MODULE_1))?(set_reg_bit(HAL_LL_UART_1_IEC_TX_ADDRESS,_int)): \
                                               (_num==hal_ll_uart_module_num(UART_MODULE_2))?(set_reg_bit(HAL_LL_UART_2_IEC_TX_ADDRESS,_int)): \
                                               (_num==hal_ll_uart_module_num(UART_MODULE_3))?(set_reg_bit(HAL_LL_UART_3_IEC_TX_ADDRESS,_int)): \
                                               (_num==hal_ll_uart_module_num(UART_MODULE_4))?(set_reg_bit(HAL_LL_UART_4_IEC_TX_ADDRESS,_int)): \
                                               (_num==hal_ll_uart_module_num(UART_MODULE_5))?(set_reg_bit(HAL_LL_UART_5_IEC_TX_ADDRESS,_int)): \
                                               (set_reg_bit(HAL_LL_UART_6_IEC_TX_ADDRESS,_int))
#elif defined(UART_MODULE_1) && defined(UART_MODULE_2) && \
      defined(UART_MODULE_3) && defined(UART_MODULE_4) && \
      defined(UART_MODULE_5)
#define __HAL_LL_UART_ENABLE_IT_TX(_num,_int)  (_num==hal_ll_uart_module_num(UART_MODULE_1))?(set_reg_bit(HAL_LL_UART_1_IEC_TX_ADDRESS,_int)): \
                                               (_num==hal_ll_uart_module_num(UART_MODULE_2))?(set_reg_bit(HAL_LL_UART_2_IEC_TX_ADDRESS,_int)): \
                                               (_num==hal_ll_uart_module_num(UART_MODULE_3))?(set_reg_bit(HAL_LL_UART_3_IEC_TX_ADDRESS,_int)): \
                                               (_num==hal_ll_uart_module_num(UART_MODULE_4))?(set_reg_bit(HAL_LL_UART_4_IEC_TX_ADDRESS,_int)): \
                                               (set_reg_bit(HAL_LL_UART_5_IEC_TX_ADDRESS,_int))
#elif defined(UART_MODULE_1) && defined(UART_MODULE_2) && \
      defined(UART_MODULE_3) && defined(UART_MODULE_4)
#define __HAL_LL_UART_ENABLE_IT_TX(_num,_int)  (_num==hal_ll_uart_module_num(UART_MODULE_1))?(set_reg_bit(HAL_LL_UART_1_IEC_TX_ADDRESS,_int)): \
                                               (_num==hal_ll_uart_module_num(UART_MODULE_2))?(set_reg_bit(HAL_LL_UART_2_IEC_TX_ADDRESS,_int)): \
                                               (_num==hal_ll_uart_module_num(UART_MODULE_3))?(set_reg_bit(HAL_LL_UART_3_IEC_TX_ADDRESS,_int)): \
                                               (set_reg_bit(HAL_LL_UART_4_IEC_TX_ADDRESS,_int))
#elif defined(UART_MODULE_1) && defined(UART_MODULE_2)
#define __HAL_LL_UART_ENABLE_IT_TX(_num,_int)  (_num==hal_ll_uart_module_num(UART_MODULE_1))?(set_reg_bit(HAL_LL_UART_1_IEC_TX_ADDRESS,_int)): \
                                               (set_reg_bit(HAL_LL_UART_2_IEC_TX_ADDRESS,_int))
#else
#   error “Modules not defined adequately. Check `mcu_definitions` file and low level UART implementation.”
#endif

#ifdef PIC32MXxx
#ifdef interrupt_case_1
#define __interrupt_handle_rx(__address,__flag,__module) clear_reg_bit( __address, __flag ); \
                                                         irq_handler( objects[hal_ll_uart_module_num(__module)], HAL_LL_UART_IRQ_RX )
#define __interrupt_handle_tx(__address,__flag,__module) clear_reg_bit( __address, __flag ); \
                                                         irq_handler( objects[hal_ll_uart_module_num(__module)], HAL_LL_UART_IRQ_TX )
#elif defined(interrupt_case_2)
#define __interrupt_handle_rx(__address,__flag,__module) irq_handler( objects[hal_ll_uart_module_num(__module)], HAL_LL_UART_IRQ_RX ); \
                                                         clear_reg_bit( __address, __flag )
#define __interrupt_handle_tx(__address,__flag,__module) irq_handler( objects[hal_ll_uart_module_num(__module)], HAL_LL_UART_IRQ_TX ); \
                                                         clear_reg_bit( __address, __flag )
#else
#   error Interrupt routines not defined adequately. Check `CMakeLists.txt` file and low level UART implementation.”
#endif
#endif

/*!< @brief Helper macro for getting hal_ll_module_state address */
#define hal_ll_uart_get_module_state_address ((hal_ll_uart_handle_register_t *)handle)
/*!< @brief Helper macro for getting module specific control register structure base address // first register address */
#define hal_ll_uart_get_handle (hal_ll_uart_handle_register_t *)hal_ll_uart_get_module_state_address->hal_ll_uart_handle
/*!< @brief Helper macro for getting module specific base address directly from HAL layer handle */
#define hal_ll_uart_get_base_from_hal_handle ((hal_ll_uart_hw_specifics_map_t *)((hal_ll_uart_hw_specifics_map_t *)((hal_ll_uart_hw_specifics_map_t *)\
                                             ((hal_ll_uart_handle_register_t *)handle)->hal_ll_uart_handle)->base)->base)->base
/*!< @brief Helper macro for getting module specific base address directly from HAL layer interrupt routine handle */
#define hal_ll_uart_get_wr_rd_handle (hal_ll_uart_base_handle_t *)(((hal_ll_uart_hw_specifics_map_t *)((hal_ll_uart_handle_register_t *) \
                                     ((hal_ll_uart_handle_register_t*)*handle)->hal_ll_uart_handle)->hal_ll_uart_handle)->base)

/*!< @brief Helper macro for UART module sync time */
#define hal_ll_uart_wait_for_sync(_hal_sync_val) while( _hal_sync_val-- ){assembly(nop);}

/*!< @brief Helper macro for UART module init time */
#ifdef PIC32MXxx
#define hal_ll_uart_init_stabilize() Delay_10ms();Delay_10ms();Delay_10ms();Delay_10ms();Delay_10ms();
#elif defined(PIC32MZxx)
#define hal_ll_uart_init_stabilize() Delay_10ms();Delay_10ms();Delay_10ms();
#else
#   error Chip not supported. Check `CMakeLists.txt` file and low level UART implementation.”
#endif

/*!< @brief Macros used for pin/port manipulation */
#define pin_mask 0x0F
#define port_mask 0xF0
#define hal_ll_pin(port_name) (port_name & pin_mask)
#define hal_ll_port(port_name) ((port_name & port_mask) >> 4)

/*!< @brief Macros used for calculating actual baud rate value and error value */
#define HAL_LL_UART_ACCEPTABLE_ERROR (float)1.0
#define hal_ll_get_system_clock (Get_Fosc_kHz()*1000)
#define hal_ll_uart_get_baud(_clock,_baud,_div) (((_clock/(float)_baud)/_div)-1)
#define hal_ll_uart_get_real_baud(_clock,_baud,_div) (_clock/(_div*(_baud+1)))
#define hal_ll_uart_get_baud_error(_baud_real,_baud) (((float)(abs(_baud_real-_baud))/_baud)*100)
#define hal_ll_uart_get_baud_low_nibble(_clock,_baud,_div) ((_hal_uart_get_baud(_clock,_baud,_div) & HAL_LL_NIBBLE_LOW_16BIT))
#define hal_ll_uart_get_baud_high_nibble(_clock,_baud,_div) ((_hal_uart_get_baud(_clock,_baud,_div) & HAL_LL_NIBBLE_HIGH_16BIT)>>8)

/*!< @brief Helper mask macros */
#define HAL_LL_OSCCON_MASK (0x180000UL)
#define HAL_LL_DATA_BITS_9_MASK 0x6

/*!< @brief Power module macros */
#define HAL_LL_UART_MODULE_ON_BIT 0x0FU
#define HAL_LL_UART_RXEN_BIT 0x0CU
#define HAL_LL_UART_TXEN_BIT 10

/*!< @brief Macros defining baud bit locations */
#define HAL_LL_UART_TRMT_BIT 8
#define HAL_LL_UART_OERR_BIT 1
#define HAL_LL_UART_BRGH_BIT 3
#define HAL_LL_UART_URXDA_BIT 0
#define HAL_LL_UART_PDSEL_BIT1 1
#define HAL_LL_UART_PDSEL_BIT2 2
#define HAL_LL_STSEL_BIT 0

// ------------------------------------------------------------------ TYPEDEFS

/*!< @brief UART HW register structure */
typedef struct {
    hal_ll_base_addr_t uart_mode_reg_addr;
    hal_ll_base_addr_t __unused_1[3];
    hal_ll_base_addr_t uart_sta_reg_addr;
    hal_ll_base_addr_t __unused_2[3];
    hal_ll_base_addr_t uart_tx_reg_addr;
    hal_ll_base_addr_t __unused_3[3];
    hal_ll_base_addr_t uart_rx_reg_addr;
    hal_ll_base_addr_t __unused_4[3];
    hal_ll_base_addr_t uart_brg_reg_addr;
} hal_ll_uart_base_handle_t;

/*!< @brief UART baud rate structure */
typedef struct {
    uint32_t baud;
    uint32_t real_baud;
} hal_ll_uart_baud_t;

/*!< @brief UART hw specific structure */
typedef struct {
    hal_ll_base_addr_t base;
    hal_ll_pin_name_t module_index;
    hal_ll_uart_pins_t pins;
    hal_ll_uart_baud_t baud_rate;
    hal_ll_uart_parity_t parity;
    hal_ll_uart_data_bits_t data_bits;
    hal_ll_uart_stop_bits_t stop_bits;
    uint8_t iec_rx_bit;
    uint8_t iec_tx_bit;
} hal_ll_uart_hw_specifics_map_t;

/*!< @brief UART hw specific module values */
typedef struct {
    uint16_t pin_tx;
    uint16_t pin_rx;
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


// ------------------------------------------------------------------ VARIABLES
/*!< @brief Global handle variables used in functions */
static volatile hal_ll_uart_handle_register_t *low_level_handle;
static volatile hal_ll_uart_hw_specifics_map_t *hal_ll_uart_hw_specifics_map_local;

/*!< @brief Global interrupt handlers used in functions */
static hal_ll_uart_isr_t irq_handler;
static handle_t objects[UART_MODULE_COUNT] = { NULL };

/*!< @brief UART hardware specific info*/
static hal_ll_uart_hw_specifics_map_t hal_ll_uart_hw_specifics_map[UART_MODULE_COUNT + 1] = {
    #ifdef UART_MODULE_1
    { HAL_LL_U1MODE_ADDRESS, hal_ll_uart_module_num(UART_MODULE_1), {HAL_LL_PIN_NC, HAL_LL_PIN_NC}, {115200, 0}, HAL_LL_UART_PARITY_DEFAULT, HAL_LL_UART_DATA_BITS_DEFAULT, HAL_LL_UART_STOP_BITS_DEFAULT, HAL_LL_UART_1_RX_FLAG, HAL_LL_UART_1_TX_FLAG },
    #endif
    #ifdef UART_MODULE_2
    { HAL_LL_U2MODE_ADDRESS, hal_ll_uart_module_num(UART_MODULE_2), {HAL_LL_PIN_NC, HAL_LL_PIN_NC}, {115200, 0}, HAL_LL_UART_PARITY_DEFAULT, HAL_LL_UART_DATA_BITS_DEFAULT, HAL_LL_UART_STOP_BITS_DEFAULT, HAL_LL_UART_2_RX_FLAG, HAL_LL_UART_2_TX_FLAG },
    #endif
    #ifdef UART_MODULE_3
    { HAL_LL_U3MODE_ADDRESS, hal_ll_uart_module_num(UART_MODULE_3), {HAL_LL_PIN_NC, HAL_LL_PIN_NC}, {115200, 0}, HAL_LL_UART_PARITY_DEFAULT, HAL_LL_UART_DATA_BITS_DEFAULT, HAL_LL_UART_STOP_BITS_DEFAULT, HAL_LL_UART_3_RX_FLAG, HAL_LL_UART_3_TX_FLAG },
    #endif
    #ifdef UART_MODULE_4
    { HAL_LL_U4MODE_ADDRESS, hal_ll_uart_module_num(UART_MODULE_4), {HAL_LL_PIN_NC, HAL_LL_PIN_NC}, {115200, 0}, HAL_LL_UART_PARITY_DEFAULT, HAL_LL_UART_DATA_BITS_DEFAULT, HAL_LL_UART_STOP_BITS_DEFAULT, HAL_LL_UART_4_RX_FLAG, HAL_LL_UART_4_TX_FLAG },
    #endif
    #ifdef UART_MODULE_5
    { HAL_LL_U5MODE_ADDRESS, hal_ll_uart_module_num(UART_MODULE_5), {HAL_LL_PIN_NC, HAL_LL_PIN_NC}, {115200, 0}, HAL_LL_UART_PARITY_DEFAULT, HAL_LL_UART_DATA_BITS_DEFAULT, HAL_LL_UART_STOP_BITS_DEFAULT, HAL_LL_UART_5_RX_FLAG, HAL_LL_UART_5_TX_FLAG },
    #endif
    #ifdef UART_MODULE_6
    { HAL_LL_U6MODE_ADDRESS, hal_ll_uart_module_num(UART_MODULE_6), {HAL_LL_PIN_NC, HAL_LL_PIN_NC}, {115200, 0}, HAL_LL_UART_PARITY_DEFAULT, HAL_LL_UART_DATA_BITS_DEFAULT, HAL_LL_UART_STOP_BITS_DEFAULT, HAL_LL_UART_6_RX_FLAG, HAL_LL_UART_6_TX_FLAG },
    #endif

    { HAL_LL_MODULE_ERROR, 0xFF, {HAL_LL_PIN_NC, HAL_LL_PIN_NC}, {0, 0}, HAL_LL_UART_PARITY_DEFAULT, HAL_LL_UART_DATA_BITS_DEFAULT, HAL_LL_UART_STOP_BITS_DEFAULT, 0xFF, 0xFF }
};

// ---------------------------------------------- PRIVATE FUNCTION DECLARATIONS
/**
 * @brief  Sets desired parity.
 *
 * Initializes module with specified parity value.
 *
 * @param[in] map - Object specific context handler.
 *
 * @return Re-init module state. If neccessary.
 */
static hal_ll_err_t hal_ll_uart_set_data_bits_and_parity( hal_ll_uart_hw_specifics_map_t *map );

/**
  * @brief  Check if pins are adequate.
  *
  * Checks tx and rx pins the user has passed with pre-defined
  * pins in tx and rx maps. Take into consideration that module
  * index numbers have to be the same for both pins.
  *
  * @param[in]  tx_pin - TX pre-defined pin name.
  * @param[in]  rx_pin - RX pre-defined pin name.
  * @param[out] *index_list - Module list.
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
static void hal_ll_uart_set_module_power( hal_ll_uart_hw_specifics_map_t *map, bool hal_ll_state );

/**
 * @brief  Maps new-found module specific values.
 *
 * Maps pin names and PPS values for
 * TX and RX pins.
 *
 * @param[in]  module_index UART HW module index -- 0,1,2...
 * @param[in]  &index_list  Array with TX and RX map index values
 *
 * @return  None
 */
static void hal_ll_uart_map_pins( uint8_t module_index, hal_ll_uart_pin_id *index_list );

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
static void hal_ll_uart_set_module( hal_ll_uart_base_handle_t *hal_ll_hw_reg, hal_ll_uart_state_t pin_state );

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

/**
 * @brief  Sets interrupt priority levels.
 *
 * Performs interrupt priority level setting.
 *
 * @param[in]  module_num - Module number ( 1, 2... ).
 * @Note Values can be from 1 to 7.
 *
 * @return void None.
 */
static void hal_ll_core_set_interrupt_priority( uint8_t module_num );

// ------------------------------------------------ PUBLIC FUNCTION DEFINITIONS

hal_ll_err_t hal_ll_uart_register_handle( hal_ll_pin_name_t tx_pin, hal_ll_pin_name_t rx_pin, hal_ll_uart_handle_register_t *handle_map, uint8_t *hal_module_id ) {

    hal_ll_uart_pin_id index_list[UART_MODULE_COUNT] = {HAL_LL_PIN_NC,HAL_LL_PIN_NC};
    uint16_t pin_check_result;

    // Check if pins are valid
    if ( HAL_LL_PIN_NC == (pin_check_result = hal_ll_uart_check_pins( tx_pin, rx_pin, &index_list, handle_map )) ) {
        return HAL_LL_UART_WRONG_PINS;
    };

    if ( (hal_ll_uart_hw_specifics_map[pin_check_result].pins.tx_pin != tx_pin) ||
         (hal_ll_uart_hw_specifics_map[pin_check_result].pins.rx_pin != rx_pin) ) {
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

        hal_ll_core_set_interrupt_priority( pin_check_result );
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

hal_ll_err_t hal_ll_uart_set_data_bits( handle_t *handle, hal_ll_uart_data_bits_t data_bit ) {
    low_level_handle = hal_ll_uart_get_handle;
    hal_ll_uart_hw_specifics_map_local = hal_ll_get_specifics(hal_ll_uart_get_module_state_address);

    low_level_handle->init_ll_state = false;

    hal_ll_uart_hw_specifics_map_local->data_bits = data_bit;

    hal_ll_uart_init(hal_ll_uart_hw_specifics_map_local);

    low_level_handle->init_ll_state = true;

    return HAL_LL_UART_SUCCESS;
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

    hal_ll_uart_hw_specifics_map_local->stop_bits = stop_bit;

    hal_ll_uart_init(hal_ll_uart_hw_specifics_map_local);

    low_level_handle->init_ll_state = true;

    return HAL_LL_UART_SUCCESS;
}

void hal_ll_uart_close( handle_t *handle ) {
    low_level_handle = hal_ll_uart_get_handle;
    hal_ll_uart_hw_specifics_map_local = hal_ll_get_specifics(hal_ll_uart_get_module_state_address);

    if( NULL != low_level_handle->hal_ll_uart_handle ) {
        #ifdef HAL_LL_PERIPHERAL_MODULE_DISABLE
        hal_ll_uart_set_module_power(hal_ll_uart_hw_specifics_map_local, true);
        #endif

        // Used only for chips which have UART PPS pins
        #if HAL_LL_UART_PPS_ENABLED == true
        hal_ll_pps_set_state(hal_ll_uart_hw_specifics_map_local, false);
        #endif

        hal_ll_uart_irq_disable(handle, HAL_LL_UART_IRQ_RX);
        hal_ll_uart_irq_disable(handle, HAL_LL_UART_IRQ_TX);

        hal_ll_uart_clear_regs(hal_ll_uart_hw_specifics_map_local->base);

        #ifdef HAL_LL_PERIPHERAL_MODULE_DISABLE
        hal_ll_uart_set_module_power(hal_ll_uart_hw_specifics_map_local, false);
        #endif

        hal_ll_uart_hw_specifics_map_local->pins.tx_pin = HAL_LL_PIN_NC;
        hal_ll_uart_hw_specifics_map_local->pins.rx_pin = HAL_LL_PIN_NC;

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
            __HAL_LL_UART_ENABLE_IT_RX( hal_ll_uart_hw_specifics_map_local->module_index, hal_ll_uart_hw_specifics_map_local->iec_rx_bit );
            break;
        case HAL_LL_UART_IRQ_TX:
            __HAL_LL_UART_ENABLE_IT_TX( hal_ll_uart_hw_specifics_map_local->module_index, hal_ll_uart_hw_specifics_map_local->iec_tx_bit );
            break;

        default:
            break;
    }
}

void hal_ll_uart_irq_disable( handle_t *handle, hal_ll_uart_irq_t irq ) {
    hal_ll_uart_hw_specifics_map_local = hal_ll_get_specifics(hal_ll_uart_get_module_state_address);

    switch ( irq ) {
        case HAL_LL_UART_IRQ_RX:
            __HAL_LL_UART_DISABLE_IT_RX( hal_ll_uart_hw_specifics_map_local->module_index, hal_ll_uart_hw_specifics_map_local->iec_rx_bit );
            break;
        case HAL_LL_UART_IRQ_TX:
            __HAL_LL_UART_DISABLE_IT_TX( hal_ll_uart_hw_specifics_map_local->module_index, hal_ll_uart_hw_specifics_map_local->iec_tx_bit );
            break;

        default:
            break;
    }
}

void hal_ll_uart_write( handle_t *handle, uint8_t wr_data ) {
    hal_ll_uart_base_handle_t *hal_ll_hw_reg = hal_ll_uart_get_wr_rd_handle;

    while ( !check_reg_bit(&hal_ll_hw_reg->uart_sta_reg_addr, HAL_LL_UART_TRMT_BIT) );

    write_reg( &hal_ll_hw_reg->uart_tx_reg_addr, wr_data );
}

uint8_t hal_ll_uart_read( handle_t *handle ) {
    hal_ll_uart_base_handle_t *hal_ll_hw_reg = hal_ll_uart_get_wr_rd_handle;

    if ( check_reg_bit(&hal_ll_hw_reg->uart_sta_reg_addr, HAL_LL_UART_OERR_BIT) ) {
        clear_reg_bit(&hal_ll_hw_reg->uart_sta_reg_addr, HAL_LL_UART_OERR_BIT);
    }

    return read_reg( &hal_ll_hw_reg->uart_rx_reg_addr );
}

// ------------------------------------------------------------- DEFAULT EXCEPTION HANDLERS

/*!< @brief Link handler from HAL layer*/
void hal_uart_irq_handler(handle_t obj, hal_ll_uart_irq_t event);

/*!< @brief Link IRQ Handler to HAL layer `hal_uart_irq_handler` function*/
#pragma funcall UART_IRQHandler hal_uart_irq_handler

#ifdef PIC32MXxx
#ifdef UART_MODULE_1
__weak void MARK_AS_IRQ_HANDLER(HAL_LL_IVT_UART_1) UART1_IRQHandler( void ) MIKROC_IV( HAL_LL_IVT_UART_1 ) {
    if( check_reg_bit( HAL_LL_UART_1_IFS_RX_ADDRESS, HAL_LL_UART_1_RX_FLAG ) &&
        check_reg_bit( HAL_LL_UART_1_IEC_RX_ADDRESS, HAL_LL_UART_1_RX_FLAG ) ) {
        __interrupt_handle_rx( HAL_LL_UART_1_IFS_RX_ADDRESS, HAL_LL_UART_1_RX_FLAG, UART_MODULE_1 );
    }
    if( check_reg_bit( HAL_LL_UART_1_IFS_TX_ADDRESS, HAL_LL_UART_1_TX_FLAG ) &&
        check_reg_bit( HAL_LL_UART_1_IEC_TX_ADDRESS, HAL_LL_UART_1_TX_FLAG ) ) {
        __interrupt_handle_tx( HAL_LL_UART_1_IFS_TX_ADDRESS, HAL_LL_UART_1_TX_FLAG, UART_MODULE_1 );
    }
}
#endif

#ifdef UART_MODULE_2
__weak void  MARK_AS_IRQ_HANDLER(HAL_LL_IVT_UART_2) UART2_IRQHandler( void ) MIKROC_IV( HAL_LL_IVT_UART_2 ) {
    if( check_reg_bit( HAL_LL_UART_2_IFS_RX_ADDRESS, HAL_LL_UART_2_RX_FLAG ) &&
        check_reg_bit( HAL_LL_UART_2_IEC_RX_ADDRESS, HAL_LL_UART_2_RX_FLAG ) ) {
        __interrupt_handle_rx( HAL_LL_UART_2_IFS_RX_ADDRESS, HAL_LL_UART_2_RX_FLAG, UART_MODULE_2 );
    }
    if( check_reg_bit( HAL_LL_UART_2_IFS_TX_ADDRESS, HAL_LL_UART_2_TX_FLAG ) &&
        check_reg_bit( HAL_LL_UART_2_IEC_TX_ADDRESS, HAL_LL_UART_2_TX_FLAG ) ) {
        __interrupt_handle_tx( HAL_LL_UART_2_IFS_TX_ADDRESS, HAL_LL_UART_2_TX_FLAG, UART_MODULE_2 );
    }
}
#endif

#ifdef UART_MODULE_3
__weak void MARK_AS_IRQ_HANDLER(HAL_LL_IVT_UART_3) UART3_IRQHandler( void ) MIKROC_IV( HAL_LL_IVT_UART_3 ) {
    if( check_reg_bit( HAL_LL_UART_3_IFS_RX_ADDRESS, HAL_LL_UART_3_RX_FLAG ) &&
        check_reg_bit( HAL_LL_UART_3_IEC_RX_ADDRESS, HAL_LL_UART_3_RX_FLAG ) ) {
        __interrupt_handle_rx( HAL_LL_UART_3_IFS_RX_ADDRESS, HAL_LL_UART_3_RX_FLAG, UART_MODULE_3 );
    }
    if( check_reg_bit( HAL_LL_UART_3_IFS_TX_ADDRESS, HAL_LL_UART_3_TX_FLAG ) &&
        check_reg_bit( HAL_LL_UART_3_IEC_TX_ADDRESS, HAL_LL_UART_3_TX_FLAG ) ) {
        __interrupt_handle_tx( HAL_LL_UART_3_IFS_TX_ADDRESS, HAL_LL_UART_3_TX_FLAG, UART_MODULE_3 );
    }
}
#endif

#ifdef UART_MODULE_4
__weak void MARK_AS_IRQ_HANDLER(HAL_LL_IVT_UART_4) UART4_IRQHandler( void ) MIKROC_IV( HAL_LL_IVT_UART_4 ) {
    if( check_reg_bit( HAL_LL_UART_4_IFS_RX_ADDRESS, HAL_LL_UART_4_RX_FLAG ) &&
        check_reg_bit( HAL_LL_UART_4_IEC_RX_ADDRESS, HAL_LL_UART_4_RX_FLAG ) ) {
        __interrupt_handle_rx( HAL_LL_UART_4_IFS_RX_ADDRESS, HAL_LL_UART_4_RX_FLAG, UART_MODULE_4 );
    }
    if( check_reg_bit( HAL_LL_UART_4_IFS_TX_ADDRESS, HAL_LL_UART_4_TX_FLAG ) &&
        check_reg_bit( HAL_LL_UART_4_IEC_TX_ADDRESS, HAL_LL_UART_4_TX_FLAG ) ) {
        __interrupt_handle_tx( HAL_LL_UART_4_IFS_TX_ADDRESS, HAL_LL_UART_4_TX_FLAG, UART_MODULE_4 );
    }
}
#endif

#ifdef UART_MODULE_5
__weak void MARK_AS_IRQ_HANDLER(HAL_LL_IVT_UART_5) UART5_IRQHandler( void ) MIKROC_IV( HAL_LL_IVT_UART_5 ) {
    if( check_reg_bit( HAL_LL_UART_5_IFS_RX_ADDRESS, HAL_LL_UART_5_RX_FLAG ) &&
        check_reg_bit( HAL_LL_UART_5_IEC_RX_ADDRESS, HAL_LL_UART_5_RX_FLAG ) ) {
        __interrupt_handle_rx( HAL_LL_UART_5_IFS_RX_ADDRESS, HAL_LL_UART_5_RX_FLAG, UART_MODULE_5 );
    }
    if( check_reg_bit( HAL_LL_UART_5_IFS_TX_ADDRESS, HAL_LL_UART_5_TX_FLAG ) &&
        check_reg_bit( HAL_LL_UART_5_IEC_TX_ADDRESS, HAL_LL_UART_5_TX_FLAG ) ) {
        __interrupt_handle_tx( HAL_LL_UART_5_IFS_TX_ADDRESS, HAL_LL_UART_5_TX_FLAG, UART_MODULE_5 );
    }
}
#endif

#ifdef UART_MODULE_6
__weak void MARK_AS_IRQ_HANDLER(HAL_LL_IVT_UART_6) UART6_IRQHandler( void ) MIKROC_IV( HAL_LL_IVT_UART_6 ) {
    if( check_reg_bit( HAL_LL_UART_6_IFS_RX_ADDRESS, HAL_LL_UART_6_RX_FLAG ) &&
        check_reg_bit( HAL_LL_UART_6_IEC_RX_ADDRESS, HAL_LL_UART_6_RX_FLAG ) ) {
        __interrupt_handle_rx( HAL_LL_UART_6_IFS_RX_ADDRESS, HAL_LL_UART_6_RX_FLAG, UART_MODULE_6 );
    }
    if( check_reg_bit( HAL_LL_UART_6_IFS_TX_ADDRESS, HAL_LL_UART_6_TX_FLAG ) &&
        check_reg_bit( HAL_LL_UART_6_IEC_TX_ADDRESS, HAL_LL_UART_6_TX_FLAG ) ) {
        __interrupt_handle_tx( HAL_LL_UART_6_IFS_TX_ADDRESS, HAL_LL_UART_6_TX_FLAG, UART_MODULE_6 );
    }
}
#endif
#else
#ifdef UART_MODULE_1
__weak void MARK_AS_IRQ_HANDLER(HAL_LL_IVT_UART_1_RX) UART1_IRQHandler_RX( void ) MIKROC_IV( HAL_LL_IVT_UART_1_RX ) {
    if( check_reg_bit( HAL_LL_UART_1_IFS_RX_ADDRESS, HAL_LL_UART_1_RX_FLAG ) &&
        check_reg_bit( HAL_LL_UART_1_IEC_RX_ADDRESS, HAL_LL_UART_1_RX_FLAG ) ) {
        irq_handler( objects[hal_ll_uart_module_num(UART_MODULE_1)], HAL_LL_UART_IRQ_RX );
        clear_reg_bit( HAL_LL_UART_1_IFS_RX_ADDRESS, HAL_LL_UART_1_RX_FLAG );
    }
}

__weak void MARK_AS_IRQ_HANDLER(HAL_LL_IVT_UART_1_TX) UART1_IRQHandler_TX( void ) MIKROC_IV( HAL_LL_IVT_UART_1_TX ) {
    if( check_reg_bit( HAL_LL_UART_1_IFS_TX_ADDRESS, HAL_LL_UART_1_TX_FLAG ) &&
        check_reg_bit( HAL_LL_UART_1_IEC_TX_ADDRESS, HAL_LL_UART_1_TX_FLAG ) ) {
        irq_handler( objects[hal_ll_uart_module_num(UART_MODULE_1)], HAL_LL_UART_IRQ_TX );
        clear_reg_bit( HAL_LL_UART_1_IFS_TX_ADDRESS, HAL_LL_UART_1_TX_FLAG );
    }
}
#endif

#ifdef UART_MODULE_2
__weak void MARK_AS_IRQ_HANDLER(HAL_LL_IVT_UART_2_RX) UART2_IRQHandler_RX( void ) MIKROC_IV( HAL_LL_IVT_UART_2_RX ) {
    if( check_reg_bit( HAL_LL_UART_2_IFS_RX_ADDRESS, HAL_LL_UART_2_RX_FLAG ) &&
        check_reg_bit( HAL_LL_UART_2_IEC_RX_ADDRESS, HAL_LL_UART_2_RX_FLAG ) ) {
        irq_handler( objects[hal_ll_uart_module_num(UART_MODULE_2)], HAL_LL_UART_IRQ_RX );
        clear_reg_bit( HAL_LL_UART_2_IFS_RX_ADDRESS, HAL_LL_UART_2_RX_FLAG );
    }
}

__weak void MARK_AS_IRQ_HANDLER(HAL_LL_IVT_UART_2_TX) UART2_IRQHandler_TX( void ) MIKROC_IV( HAL_LL_IVT_UART_2_TX ) {
    if( check_reg_bit( HAL_LL_UART_2_IFS_TX_ADDRESS, HAL_LL_UART_2_TX_FLAG ) &&
        check_reg_bit( HAL_LL_UART_2_IEC_TX_ADDRESS, HAL_LL_UART_2_TX_FLAG ) ) {
        irq_handler( objects[hal_ll_uart_module_num(UART_MODULE_2)], HAL_LL_UART_IRQ_TX );
        clear_reg_bit( HAL_LL_UART_2_IFS_TX_ADDRESS, HAL_LL_UART_2_TX_FLAG );
    }
}
#endif

#ifdef UART_MODULE_3
__weak void MARK_AS_IRQ_HANDLER(HAL_LL_IVT_UART_3_RX) UART3_IRQHandler_RX( void ) MIKROC_IV( HAL_LL_IVT_UART_3_RX ) {
    if( check_reg_bit( HAL_LL_UART_3_IFS_RX_ADDRESS, HAL_LL_UART_3_RX_FLAG ) &&
        check_reg_bit( HAL_LL_UART_3_IEC_RX_ADDRESS, HAL_LL_UART_3_RX_FLAG ) ) {
        irq_handler( objects[hal_ll_uart_module_num(UART_MODULE_3)], HAL_LL_UART_IRQ_RX );
        clear_reg_bit( HAL_LL_UART_3_IFS_RX_ADDRESS, HAL_LL_UART_3_RX_FLAG );
    }
}

__weak void MARK_AS_IRQ_HANDLER(HAL_LL_IVT_UART_3_TX) UART3_IRQHandler_TX( void ) MIKROC_IV( HAL_LL_IVT_UART_3_TX ) {
    if( check_reg_bit( HAL_LL_UART_3_IFS_TX_ADDRESS, HAL_LL_UART_3_TX_FLAG ) &&
        check_reg_bit( HAL_LL_UART_3_IEC_TX_ADDRESS, HAL_LL_UART_3_TX_FLAG ) ) {
        irq_handler( objects[hal_ll_uart_module_num(UART_MODULE_3)], HAL_LL_UART_IRQ_TX );
        clear_reg_bit( HAL_LL_UART_3_IFS_TX_ADDRESS, HAL_LL_UART_3_TX_FLAG );
    }
}
#endif

#ifdef UART_MODULE_4
__weak void MARK_AS_IRQ_HANDLER(HAL_LL_IVT_UART_4_RX) UART4_IRQHandler_RX( void ) MIKROC_IV( HAL_LL_IVT_UART_4_RX ) {
    if( check_reg_bit( HAL_LL_UART_4_IFS_RX_ADDRESS, HAL_LL_UART_4_RX_FLAG ) &&
        check_reg_bit( HAL_LL_UART_4_IEC_RX_ADDRESS, HAL_LL_UART_4_RX_FLAG ) ) {
        irq_handler( objects[hal_ll_uart_module_num(UART_MODULE_4)], HAL_LL_UART_IRQ_RX );
        clear_reg_bit( HAL_LL_UART_4_IFS_RX_ADDRESS, HAL_LL_UART_4_RX_FLAG );
    }
}

__weak void MARK_AS_IRQ_HANDLER(HAL_LL_IVT_UART_4_TX) UART4_IRQHandler_TX( void ) MIKROC_IV( HAL_LL_IVT_UART_4_TX ) {
    if( check_reg_bit( HAL_LL_UART_4_IFS_TX_ADDRESS, HAL_LL_UART_4_TX_FLAG ) &&
        check_reg_bit( HAL_LL_UART_4_IEC_TX_ADDRESS, HAL_LL_UART_4_TX_FLAG ) ) {
        irq_handler( objects[hal_ll_uart_module_num(UART_MODULE_4)], HAL_LL_UART_IRQ_TX );
        clear_reg_bit( HAL_LL_UART_4_IFS_TX_ADDRESS, HAL_LL_UART_4_TX_FLAG );
    }
}
#endif

#ifdef UART_MODULE_5
__weak void MARK_AS_IRQ_HANDLER(HAL_LL_IVT_UART_5_RX) UART5_IRQHandler_RX( void ) MIKROC_IV( HAL_LL_IVT_UART_5_RX ) {
    if( check_reg_bit( HAL_LL_UART_5_IFS_RX_ADDRESS, HAL_LL_UART_5_RX_FLAG ) &&
        check_reg_bit( HAL_LL_UART_5_IEC_RX_ADDRESS, HAL_LL_UART_5_RX_FLAG ) ) {
        irq_handler( objects[hal_ll_uart_module_num(UART_MODULE_5)], HAL_LL_UART_IRQ_RX );
        clear_reg_bit( HAL_LL_UART_5_IFS_RX_ADDRESS, HAL_LL_UART_5_RX_FLAG );
    }
}

__weak void MARK_AS_IRQ_HANDLER(HAL_LL_IVT_UART_5_TX) UART5_IRQHandler_TX( void ) MIKROC_IV( HAL_LL_IVT_UART_5_TX ) {
    if( check_reg_bit( HAL_LL_UART_5_IFS_TX_ADDRESS, HAL_LL_UART_5_TX_FLAG ) &&
        check_reg_bit( HAL_LL_UART_5_IEC_TX_ADDRESS, HAL_LL_UART_5_TX_FLAG ) ) {
        irq_handler( objects[hal_ll_uart_module_num(UART_MODULE_5)], HAL_LL_UART_IRQ_TX );
        clear_reg_bit( HAL_LL_UART_5_IFS_TX_ADDRESS, HAL_LL_UART_5_TX_FLAG );
    }
}
#endif

#ifdef UART_MODULE_6
__weak void MARK_AS_IRQ_HANDLER(HAL_LL_IVT_UART_6_RX) UART6_IRQHandler_RX( void ) MIKROC_IV( HAL_LL_IVT_UART_6_RX ) {
    if( check_reg_bit( HAL_LL_UART_6_IFS_RX_ADDRESS, HAL_LL_UART_6_RX_FLAG ) &&
        check_reg_bit( HAL_LL_UART_6_IEC_RX_ADDRESS, HAL_LL_UART_6_RX_FLAG ) ) {
        irq_handler( objects[hal_ll_uart_module_num(UART_MODULE_6)], HAL_LL_UART_IRQ_RX );
        clear_reg_bit( HAL_LL_UART_6_IFS_RX_ADDRESS, HAL_LL_UART_6_RX_FLAG );
    }
}

__weak void MARK_AS_IRQ_HANDLER(HAL_LL_IVT_UART_6_TX) UART6_IRQHandler_TX( void ) MIKROC_IV( HAL_LL_IVT_UART_6_TX ) {
    if( check_reg_bit( HAL_LL_UART_6_IFS_TX_ADDRESS, HAL_LL_UART_6_TX_FLAG ) &&
        check_reg_bit( HAL_LL_UART_6_IEC_TX_ADDRESS, HAL_LL_UART_6_TX_FLAG ) ) {
        irq_handler( objects[hal_ll_uart_module_num(UART_MODULE_6)], HAL_LL_UART_IRQ_TX );
        clear_reg_bit( HAL_LL_UART_6_IFS_TX_ADDRESS, HAL_LL_UART_6_TX_FLAG );
    }
}
#endif
#endif

// ----------------------------------------------- PRIVATE FUNCTION DEFINITIONS

static uint8_t hal_ll_uart_find_index( handle_t *handle ) {
    hal_ll_uart_hw_specifics_map_local = hal_ll_get_specifics(hal_ll_uart_get_module_state_address);

    if( HAL_LL_MODULE_ERROR != hal_ll_uart_hw_specifics_map_local->base ) {
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
                    if ( hal_ll_uart_tx_map[ tx_index ].module_index == hal_ll_uart_rx_map[ rx_index ].module_index ) {
                        // Get module number
                        hal_ll_module_id = hal_ll_uart_tx_map[ tx_index ].module_index;

                        // Map pin names
                        index_list[ hal_ll_module_id ].pin_tx = tx_index;
                        index_list[ hal_ll_module_id ].pin_rx = rx_index;

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
    uint8_t hal_ll_module_count = sizeof(hal_ll_module_state) / (sizeof(hal_ll_uart_handle_register_t));
    static uint8_t hal_ll_module_error = sizeof(hal_ll_module_state) / (sizeof(hal_ll_uart_handle_register_t));

    while( hal_ll_module_count-- ) {
        if (hal_ll_uart_get_base_from_hal_handle == hal_ll_uart_hw_specifics_map[hal_ll_module_count].base) {
            return &hal_ll_uart_hw_specifics_map[hal_ll_module_count];
        }
    }

    return &hal_ll_uart_hw_specifics_map[hal_ll_module_error];
}

static void hal_ll_uart_map_pins( uint8_t module_index, hal_ll_uart_pin_id *index_list ) {
    // Map new pins
    hal_ll_uart_hw_specifics_map[module_index].pins.tx_pin = hal_ll_uart_tx_map[index_list[module_index].pin_tx].pin;
    hal_ll_uart_hw_specifics_map[module_index].pins.rx_pin = hal_ll_uart_rx_map[index_list[module_index].pin_rx].pin;
}

static void hal_ll_core_set_interrupt_priority( uint8_t module_num ) {
    uint8_t irq_num = 0;
    #ifdef PIC32MZxx
    uint8_t irq_num_2 = 0;
    #endif

    switch ( module_num ) {
        #ifdef PIC32MXxx
        #ifdef HAL_LL_IVT_UART_1
        case hal_ll_uart_module_num(UART_MODULE_1):
            irq_num = HAL_LL_IVT_UART_1;
            break;
        #endif
        #ifdef HAL_LL_IVT_UART_2
        case hal_ll_uart_module_num(UART_MODULE_2):
            irq_num = HAL_LL_IVT_UART_2;
            break;
        #endif
        #ifdef HAL_LL_IVT_UART_3
        case hal_ll_uart_module_num(UART_MODULE_3):
            irq_num = HAL_LL_IVT_UART_3;
            break;
        #endif
        #ifdef HAL_LL_IVT_UART_4
        case hal_ll_uart_module_num(UART_MODULE_4):
            irq_num = HAL_LL_IVT_UART_4;
            break;
        #endif
        #ifdef HAL_LL_IVT_UART_5
        case hal_ll_uart_module_num(UART_MODULE_5):
            irq_num = HAL_LL_IVT_UART_5;
            break;
        #endif
        #ifdef HAL_LL_IVT_UART_6
        case hal_ll_uart_module_num(UART_MODULE_6):
            irq_num = HAL_LL_IVT_UART_6;
            break;
        #endif
        #elif defined(PIC32MZxx)
        #ifdef UART_MODULE_1
        case hal_ll_uart_module_num(UART_MODULE_1):
            irq_num   = HAL_LL_IVT_UART_1_RX;
            irq_num_2 = HAL_LL_IVT_UART_1_TX;
            break;
        #endif
        #ifdef UART_MODULE_2
        case hal_ll_uart_module_num(UART_MODULE_2):
            irq_num   = HAL_LL_IVT_UART_2_RX;
            irq_num_2 = HAL_LL_IVT_UART_2_TX;
            break;
        #endif
        #ifdef UART_MODULE_3
        case hal_ll_uart_module_num(UART_MODULE_3):
            irq_num   = HAL_LL_IVT_UART_3_RX;
            irq_num_2 = HAL_LL_IVT_UART_3_TX;
            break;
        #endif
        #ifdef UART_MODULE_4
        case hal_ll_uart_module_num(UART_MODULE_4):
            irq_num   = HAL_LL_IVT_UART_4_RX;
            irq_num_2 = HAL_LL_IVT_UART_4_TX;
            break;
        #endif
        #ifdef UART_MODULE_5
        case hal_ll_uart_module_num(UART_MODULE_5):
            irq_num   = HAL_LL_IVT_UART_5_RX;
            irq_num_2 = HAL_LL_IVT_UART_5_TX;
            break;
        #endif
        #ifdef UART_MODULE_6
        case hal_ll_uart_module_num(UART_MODULE_6):
            irq_num   = HAL_LL_IVT_UART_6_RX;
            irq_num_2 = HAL_LL_IVT_UART_6_TX;
            break;
        #endif
        #endif

        default:
            break;
    }

    #ifdef PIC32MXxx
    hal_ll_core_set_priority_irq( irq_num, HAL_LL_IRQ_PRIORITY_LEVEL_7 );
    #elif defined(PIC32MZxx)
    // PIC32MZ chips have separate interrupt vectors
    hal_ll_core_set_priority_irq( irq_num,   HAL_LL_IRQ_PRIORITY_LEVEL_7 );
    hal_ll_core_set_priority_irq( irq_num_2, HAL_LL_IRQ_PRIORITY_LEVEL_7 );
    #endif
}

static void hal_ll_uart_set_module_power( hal_ll_uart_hw_specifics_map_t *map, bool hal_ll_state ) {
    switch ( map->module_index ) {
        #ifdef HAL_LL_PMD5_ADDRESS
            #ifdef UART_MODULE_1
            case hal_ll_uart_module_num(UART_MODULE_1):
                ( hal_ll_state == true )?(clear_reg_bit( HAL_LL_PMD5_ADDRESS, HAL_LL_U1MD_ENABLE_BIT )):(set_reg_bit( HAL_LL_PMD5_ADDRESS, HAL_LL_U1MD_ENABLE_BIT ));
                break;
            #endif
            #ifdef UART_MODULE_2
            case hal_ll_uart_module_num(UART_MODULE_2):
                ( hal_ll_state == true )?(clear_reg_bit( HAL_LL_PMD5_ADDRESS, HAL_LL_U2MD_ENABLE_BIT )):(set_reg_bit( HAL_LL_PMD5_ADDRESS, HAL_LL_U2MD_ENABLE_BIT ));
                break;
            #endif
            #ifdef UART_MODULE_3
            case hal_ll_uart_module_num(UART_MODULE_3):
                ( hal_ll_state == true )?(clear_reg_bit( HAL_LL_PMD5_ADDRESS, HAL_LL_U3MD_ENABLE_BIT )):(set_reg_bit( HAL_LL_PMD5_ADDRESS, HAL_LL_U3MD_ENABLE_BIT ));
                break;
            #endif
            #ifdef UART_MODULE_4
            case hal_ll_uart_module_num(UART_MODULE_4):
                ( hal_ll_state == true )?(clear_reg_bit( HAL_LL_PMD5_ADDRESS, HAL_LL_U4MD_ENABLE_BIT )):(set_reg_bit( HAL_LL_PMD5_ADDRESS, HAL_LL_U4MD_ENABLE_BIT ));
                break;
            #endif
            #ifdef UART_MODULE_5
            case hal_ll_uart_module_num(UART_MODULE_5):
                ( hal_ll_state == true )?(clear_reg_bit( HAL_LL_PMD5_ADDRESS, HAL_LL_U5MD_ENABLE_BIT )):(set_reg_bit( HAL_LL_PMD5_ADDRESS, HAL_LL_U5MD_ENABLE_BIT ));
                break;
            #endif
        #endif

            default:
                break;
    }
}

static hal_ll_pps_err_t hal_ll_pps_set_state( hal_ll_uart_hw_specifics_map_t *map, bool hal_ll_state ) {
    hal_ll_pps_err_t hal_ll_status = HAL_LL_PPS_SUCCESS;

    if ( (map->pins.tx_pin != HAL_LL_PIN_NC) && (map->pins.rx_pin != HAL_LL_PIN_NC) ) {
        // Check status manually if needed
        hal_ll_status = hal_ll_pps_map( hal_ll_port( map->pins.tx_pin ), hal_ll_pin( map->pins.tx_pin ),
                                        HAL_LL_GPIO_DIGITAL_OUTPUT, HAL_LL_PPS_FUNCTIONALITY_UART, map->module_index, hal_ll_state );

        if ( hal_ll_status != HAL_LL_UART_SUCCESS )
            return hal_ll_status;

        // Check status manually if needed
        hal_ll_status = hal_ll_pps_map( hal_ll_port( map->pins.rx_pin ), hal_ll_pin( map->pins.rx_pin ),
                                        HAL_LL_GPIO_DIGITAL_INPUT, HAL_LL_PPS_FUNCTIONALITY_UART, map->module_index, hal_ll_state );

        return hal_ll_status;
    } else {
        return HAL_LL_UART_SUCCESS;
    }
}

static void hal_ll_uart_set_baud_bare_metal( hal_ll_uart_hw_specifics_map_t *map ) {
    static uint8_t div_value = 4;
    uint32_t tmp_baud_1 = 0;
    uint32_t tmp_baud_2 = 0;
    uint32_t tmp_baud = hal_ll_get_system_clock;
    #ifdef PIC32MXxx
    tmp_baud >>= (read_reg_bits( HAL_LL_OSCCON_ADDRESS, HAL_LL_OSCCON_MASK ) >> 19);
    #elif defined(PIC32MZxx)
    uint32_t divisor = (read_reg(HAL_LL_PB2DIV_ADDRESS) & 0x007F) + 1;
    tmp_baud /= divisor;
    #endif

    hal_ll_uart_base_handle_t *hal_ll_hw_reg = (hal_ll_uart_base_handle_t *)map->base;

    uint32_t hal_ll_baud_value = hal_ll_uart_get_baud( hal_ll_get_system_clock,map->baud_rate.baud,div_value );
    uint32_t hal_ll_baud_real_value = hal_ll_uart_get_real_baud( hal_ll_get_system_clock,hal_ll_baud_value,div_value );

    // If error greater than specified, cancel setting baud rate
    if( (float)hal_ll_uart_get_baud_error( hal_ll_baud_real_value,map->baud_rate.baud ) > HAL_LL_UART_ACCEPTABLE_ERROR ) {
        map->baud_rate.real_baud = hal_ll_uart_get_baud_error( hal_ll_baud_real_value,map->baud_rate.baud );
    } else {
        map->baud_rate.real_baud = hal_ll_baud_real_value;

        set_reg_bit( &hal_ll_hw_reg->uart_mode_reg_addr, HAL_LL_UART_BRGH_BIT ); // High speed mode.

        tmp_baud_1 = map->baud_rate.baud * 4;

        tmp_baud_2 = tmp_baud % tmp_baud_1;
        tmp_baud /= tmp_baud_1;

        if( tmp_baud_2 > (tmp_baud_1>>1) ) {
            tmp_baud++;
        }

        hal_ll_hw_reg->uart_brg_reg_addr = --tmp_baud;
    }
}

static void hal_ll_uart_set_stop_bits_bare_metal( hal_ll_uart_hw_specifics_map_t *map ) {
    hal_ll_uart_base_handle_t *hal_ll_hw_reg = (hal_ll_uart_base_handle_t *)map->base;

    switch ( map->stop_bits ) {
        case HAL_LL_UART_STOP_BITS_ONE:
            clear_reg_bit( &hal_ll_hw_reg->uart_mode_reg_addr, HAL_LL_STSEL_BIT );
            break;
        case HAL_LL_UART_STOP_BITS_TWO:
            set_reg_bit( &hal_ll_hw_reg->uart_mode_reg_addr, HAL_LL_STSEL_BIT );
            break;

        default:
            break;
    }
}

static hal_ll_err_t hal_ll_uart_set_data_bits_and_parity( hal_ll_uart_hw_specifics_map_t *map ){
    hal_ll_uart_base_handle_t *hal_ll_hw_reg = (hal_ll_uart_base_handle_t *)map->base;

    if( HAL_LL_UART_DATA_BITS_9 == map->data_bits ) {
        set_reg_bits( &hal_ll_hw_reg->uart_mode_reg_addr, HAL_LL_DATA_BITS_9_MASK );
    } else if( HAL_LL_UART_DATA_BITS_8 == map->data_bits ) {
        switch( map->parity ) {
            case ( HAL_LL_UART_PARITY_NONE ):
                clear_reg_bits( &hal_ll_hw_reg->uart_mode_reg_addr, HAL_LL_DATA_BITS_9_MASK );
                break;
            case ( HAL_LL_UART_PARITY_EVEN ):
                set_reg_bit( &hal_ll_hw_reg->uart_mode_reg_addr, HAL_LL_UART_PDSEL_BIT1 );
                clear_reg_bit( &hal_ll_hw_reg->uart_mode_reg_addr, HAL_LL_UART_PDSEL_BIT2 );
                break;
            case ( HAL_LL_UART_PARITY_ODD ):
                set_reg_bit( &hal_ll_hw_reg->uart_mode_reg_addr, HAL_LL_UART_PDSEL_BIT2 );
                clear_reg_bit( &hal_ll_hw_reg->uart_mode_reg_addr, HAL_LL_UART_PDSEL_BIT1 );
                break;

            default:
                break;
        }
    }

    return HAL_LL_UART_SUCCESS;
}

static void hal_ll_uart_set_module( hal_ll_uart_base_handle_t *hal_ll_hw_reg, hal_ll_uart_state_t pin_state ) {
    switch ( pin_state ) {
        case HAL_LL_UART_DISABLE:
            clear_reg_bit( &hal_ll_hw_reg->uart_mode_reg_addr, HAL_LL_UART_MODULE_ON_BIT );
            break;
        case HAL_LL_UART_ENABLE:
            set_reg_bit( &hal_ll_hw_reg->uart_mode_reg_addr, HAL_LL_UART_MODULE_ON_BIT );
            break;

        default:
            break;
    }
}

static void hal_ll_uart_set_transmitter( hal_ll_uart_base_handle_t *hal_ll_hw_reg, hal_ll_uart_state_t pin_state ) {
    switch ( pin_state ) {
        case HAL_LL_UART_DISABLE:
            clear_reg_bit( &hal_ll_hw_reg->uart_sta_reg_addr, HAL_LL_UART_TXEN_BIT );
            break;
        case HAL_LL_UART_ENABLE:
            set_reg_bit( &hal_ll_hw_reg->uart_sta_reg_addr, HAL_LL_UART_TXEN_BIT );
            break;

        default:
            break;
    }
}

static void hal_ll_uart_set_receiver( hal_ll_uart_base_handle_t *hal_ll_hw_reg, hal_ll_uart_state_t pin_state ) {
    switch ( pin_state ) {
        case HAL_LL_UART_DISABLE:
            clear_reg_bit( &hal_ll_hw_reg->uart_sta_reg_addr, HAL_LL_UART_RXEN_BIT );
            break;
        case HAL_LL_UART_ENABLE:
            set_reg_bit( &hal_ll_hw_reg->uart_sta_reg_addr, HAL_LL_UART_RXEN_BIT );
            break;

        default:
            break;
    }
}

static void hal_ll_uart_clear_regs( hal_ll_uart_base_handle_t *hal_ll_hw_reg ) {
    clear_reg( &hal_ll_hw_reg->uart_mode_reg_addr );
    clear_reg( &hal_ll_hw_reg->uart_sta_reg_addr );
    clear_reg( &hal_ll_hw_reg->uart_tx_reg_addr );
    clear_reg( &hal_ll_hw_reg->uart_rx_reg_addr );
}

static void hal_ll_uart_hw_ansel_set( hal_ll_uart_hw_specifics_map_t *map ) {
    hal_ll_gpio_pin_t local_pin;

    /*
     * Configures TX and RX pins as output/input by clearing/setting
     * corresponding TRIS bits.
     */
    hal_ll_gpio_configure_pin(&local_pin, map->pins.tx_pin, HAL_LL_GPIO_DIGITAL_OUTPUT);
    hal_ll_gpio_configure_pin(&local_pin, map->pins.rx_pin, HAL_LL_GPIO_DIGITAL_INPUT);
}

static void hal_ll_uart_hw_init( hal_ll_uart_hw_specifics_map_t *map ) {
    hal_ll_uart_clear_regs( map->base );

    hal_ll_uart_set_baud_bare_metal( map );

    hal_ll_uart_set_data_bits_and_parity( map );

    hal_ll_uart_set_stop_bits_bare_metal( map );

    hal_ll_uart_set_transmitter( map->base, HAL_LL_UART_ENABLE );

    hal_ll_uart_set_receiver( map->base, HAL_LL_UART_ENABLE );

    hal_ll_uart_set_module( map->base, HAL_LL_UART_ENABLE );

    /*
     * Wait time defined per PIC32 family.
     * After initializing module, it takes
     * some time for it to be synchronised
     * adequately. Without it, start bit won't
     * be sent and initial data will be lost.
     */
    hal_ll_uart_init_stabilize();
}

static void hal_ll_uart_init( hal_ll_uart_hw_specifics_map_t *map ) {
    /*!< @brief Static, because clock doesn't change during runtime */
    static uint32_t hal_ll_clock_value;
    hal_ll_clock_value = Get_Fosc_kHz();

    #ifdef HAL_LL_PERIPHERAL_MODULE_DISABLE
    hal_ll_uart_set_module_power( map, true );
    #endif

    hal_ll_uart_hw_ansel_set( map );

    #if HAL_LL_UART_PPS_ENABLED == true
    hal_ll_pps_set_state( map, true );
    #endif

    hal_ll_uart_hw_init( map );

    hal_ll_uart_wait_for_sync(hal_ll_clock_value);
}

// ------------------------------------------------------------------------- END
