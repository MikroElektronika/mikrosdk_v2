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
 * @file  hal_ll_uart_pin_map.h
 * @brief UART HAL LOW LEVEL PIN MAPS.
 */

#ifndef _HAL_LL_UART_PIN_MAP_H_
#define _HAL_LL_UART_PIN_MAP_H_

#ifdef __cplusplus
extern "C"{
#endif

#include "hal_ll_pin_names.h"

/*!< @brief Macro defining `weak` attribute */
#define __weak __attribute__((weak))
/*!< @brief Helper macro for getting adequate module index number */
#define hal_ll_uart_module_num(_module_num) (_module_num - 1)

/*!< @brief UART module base addresses */
#ifdef UART_MODULE_0
static const hal_ll_base_addr_t HAL_LL_UART0_BASE_ADDRESS = 0x40070000UL;
#endif
#ifdef UART_MODULE_1
static const hal_ll_base_addr_t HAL_LL_UART1_BASE_ADDRESS = 0x40071000UL;
#endif
#ifdef UART_MODULE_2
static const hal_ll_base_addr_t HAL_LL_UART2_BASE_ADDRESS = 0x40072000UL;
#endif
#ifdef UART_MODULE_3
static const hal_ll_base_addr_t HAL_LL_UART3_BASE_ADDRESS = 0x40073000UL;
#endif
#ifdef UART_MODULE_4
static const hal_ll_base_addr_t HAL_LL_UART4_BASE_ADDRESS = 0x40074000UL;
#endif
#ifdef UART_MODULE_5
static const hal_ll_base_addr_t HAL_LL_UART5_BASE_ADDRESS = 0x40075000UL;
#endif

/*!< UART AF NUMBERS */

#define HAL_LL_UART_GPIO_AF2        2
#define HAL_LL_UART_GPIO_AF3        3
#define HAL_LL_UART_GPIO_AF4        4
#define HAL_LL_UART_GPIO_AF5        5
#define HAL_LL_UART_GPIO_AF6        6
#define HAL_LL_UART_GPIO_AF7        7
#define HAL_LL_UART_GPIO_AF8        8
#define HAL_LL_UART_GPIO_AF9        9
#define HAL_LL_UART_GPIO_AF10       10
#define HAL_LL_UART_GPIO_AF11       11
#define HAL_LL_UART_GPIO_AF12       12

/*!< @brief UART pin structure. */
typedef struct {
    uint8_t module_index;
    hal_ll_pin_name_t pin;
    hal_ll_base_addr_t base;
    uint8_t af;
} hal_ll_uart_pin_map_t;

/*!< UART TX Pins. */
static const hal_ll_uart_pin_map_t hal_ll_uart_tx_map[] = {

    #ifdef UART_MODULE_0
    #ifdef UART0_TX_PA14_AF3
    {UART_MODULE_0, GPIO_PA14, HAL_LL_UART0_BASE_ADDRESS, HAL_LL_UART_GPIO_AF3},
    #endif
    #ifdef UART0_TX_PC12_AF3
    {UART_MODULE_0, GPIO_PC12, HAL_LL_UART0_BASE_ADDRESS, HAL_LL_UART_GPIO_AF3},
    #endif
    #ifdef UART0_TX_PF3_AF3
    {UART_MODULE_0, GPIO_PF3, HAL_LL_UART0_BASE_ADDRESS, HAL_LL_UART_GPIO_AF3},
    #endif
    #ifdef UART0_TX_PF0_AF4
    {UART_MODULE_0, GPIO_PF0, HAL_LL_UART0_BASE_ADDRESS, HAL_LL_UART_GPIO_AF4},
    #endif
    #ifdef UART0_TX_PB9_AF5
    {UART_MODULE_0, GPIO_PB9, HAL_LL_UART0_BASE_ADDRESS, HAL_LL_UART_GPIO_AF5},
    #endif
    #ifdef UART0_TX_PB13_AF6
    {UART_MODULE_0, GPIO_PB13, HAL_LL_UART0_BASE_ADDRESS, HAL_LL_UART_GPIO_AF6},
    #endif
    #ifdef UART0_TX_PA1_AF7
    {UART_MODULE_0, GPIO_PA1, HAL_LL_UART0_BASE_ADDRESS, HAL_LL_UART_GPIO_AF7},
    #endif
    #ifdef UART0_TX_PA7_AF7
    {UART_MODULE_0, GPIO_PA7, HAL_LL_UART0_BASE_ADDRESS, HAL_LL_UART_GPIO_AF7},
    #endif
    #ifdef UART0_TX_PH10_AF8
    {UART_MODULE_0, GPIO_PH10, HAL_LL_UART0_BASE_ADDRESS, HAL_LL_UART_GPIO_AF8},
    #endif
    #ifdef UART0_TX_PD3_AF9
    {UART_MODULE_0, GPIO_PD3, HAL_LL_UART0_BASE_ADDRESS, HAL_LL_UART_GPIO_AF9},
    #endif
    #ifdef UART0_TX_PA5_AF11
    {UART_MODULE_0, GPIO_PA5, HAL_LL_UART0_BASE_ADDRESS, HAL_LL_UART_GPIO_AF11},
    #endif
    #endif

    #ifdef UART_MODULE_1
    #ifdef UART1_TX_PF0_AF2
    {UART_MODULE_1, GPIO_PF0, HAL_LL_UART1_BASE_ADDRESS, HAL_LL_UART_GPIO_AF2},
    #endif
    #ifdef UART1_TX_PD7_AF3
    {UART_MODULE_1, GPIO_PD7, HAL_LL_UART1_BASE_ADDRESS, HAL_LL_UART_GPIO_AF3},
    #endif
    #ifdef UART1_TX_PD11_AF3
    {UART_MODULE_1, GPIO_PD11, HAL_LL_UART1_BASE_ADDRESS, HAL_LL_UART_GPIO_AF3},
    #endif
    #ifdef UART1_TX_PB3_AF6
    {UART_MODULE_1, GPIO_PB3, HAL_LL_UART1_BASE_ADDRESS, HAL_LL_UART_GPIO_AF6},
    #endif
    #ifdef UART1_TX_PB7_AF6
    {UART_MODULE_1, GPIO_PB7, HAL_LL_UART1_BASE_ADDRESS, HAL_LL_UART_GPIO_AF6},
    #endif
    #ifdef UART1_TX_PA9_AF7
    {UART_MODULE_1, GPIO_PA9, HAL_LL_UART1_BASE_ADDRESS, HAL_LL_UART_GPIO_AF7},
    #endif
    #ifdef UART1_TX_PA3_AF8
    {UART_MODULE_1, GPIO_PA3, HAL_LL_UART1_BASE_ADDRESS, HAL_LL_UART_GPIO_AF8},
    #endif
    #ifdef UART1_TX_PE13_AF8
    {UART_MODULE_1, GPIO_PE13, HAL_LL_UART1_BASE_ADDRESS, HAL_LL_UART_GPIO_AF8},
    #endif
    #ifdef UART1_TX_PH8_AF10
    {UART_MODULE_1, GPIO_PH8, HAL_LL_UART1_BASE_ADDRESS, HAL_LL_UART_GPIO_AF10},
    #endif
    #endif

    #ifdef UART_MODULE_2
    #ifdef UART2_TX_PF4_AF2
    {UART_MODULE_2, GPIO_PF4, HAL_LL_UART2_BASE_ADDRESS, HAL_LL_UART_GPIO_AF2},
    #endif
    #ifdef UART2_TX_PE14_AF3
    {UART_MODULE_2, GPIO_PE14, HAL_LL_UART2_BASE_ADDRESS, HAL_LL_UART_GPIO_AF3},
    #endif
    #ifdef UART2_TX_PB1_AF7
    {UART_MODULE_2, GPIO_PB1, HAL_LL_UART2_BASE_ADDRESS, HAL_LL_UART_GPIO_AF7},
    #endif
    #ifdef UART2_TX_PC13_AF7
    {UART_MODULE_2, GPIO_PC13, HAL_LL_UART2_BASE_ADDRESS, HAL_LL_UART_GPIO_AF7},
    #endif
    #ifdef UART2_TX_PE8_AF7
    {UART_MODULE_2, GPIO_PE8, HAL_LL_UART2_BASE_ADDRESS, HAL_LL_UART_GPIO_AF7},
    #endif
    #ifdef UART2_TX_PC1_AF8
    {UART_MODULE_2, GPIO_PC1, HAL_LL_UART2_BASE_ADDRESS, HAL_LL_UART_GPIO_AF8},
    #endif
    #ifdef UART2_TX_PC5_AF8
    {UART_MODULE_2, GPIO_PC5, HAL_LL_UART2_BASE_ADDRESS, HAL_LL_UART_GPIO_AF8},
    #endif
    #ifdef UART2_TX_PB5_AF12
    {UART_MODULE_2, GPIO_PB5, HAL_LL_UART2_BASE_ADDRESS, HAL_LL_UART_GPIO_AF12},
    #endif
    #endif

    #ifdef UART_MODULE_3
    #ifdef UART3_TX_PD1_AF5
    {UART_MODULE_3, GPIO_PD1, HAL_LL_UART3_BASE_ADDRESS, HAL_LL_UART_GPIO_AF5},
    #endif
    #ifdef UART3_TX_PB15_AF7
    {UART_MODULE_3, GPIO_PB15, HAL_LL_UART3_BASE_ADDRESS, HAL_LL_UART_GPIO_AF7},
    #endif
    #ifdef UART3_TX_PC10_AF7
    {UART_MODULE_3, GPIO_PC10, HAL_LL_UART3_BASE_ADDRESS, HAL_LL_UART_GPIO_AF7},
    #endif
    #ifdef UART3_TX_PE1_AF7
    {UART_MODULE_3, GPIO_PE1, HAL_LL_UART3_BASE_ADDRESS, HAL_LL_UART_GPIO_AF7},
    #endif
    #ifdef UART3_TX_PE10_AF7
    {UART_MODULE_3, GPIO_PE10, HAL_LL_UART3_BASE_ADDRESS, HAL_LL_UART_GPIO_AF7},
    #endif
    #ifdef UART3_TX_PC3_AF11
    {UART_MODULE_3, GPIO_PC3, HAL_LL_UART3_BASE_ADDRESS, HAL_LL_UART_GPIO_AF11},
    #endif
    #endif

    #ifdef UART_MODULE_4
    #ifdef UART4_TX_PA12_AF3
    {UART_MODULE_4, GPIO_PA12, HAL_LL_UART4_BASE_ADDRESS, HAL_LL_UART_GPIO_AF3},
    #endif
    #ifdef UART4_TX_PC7_AF5
    {UART_MODULE_4, GPIO_PC7, HAL_LL_UART4_BASE_ADDRESS, HAL_LL_UART_GPIO_AF5},
    #endif
    #ifdef UART4_TX_PB11_AF6
    {UART_MODULE_4, GPIO_PB11, HAL_LL_UART4_BASE_ADDRESS, HAL_LL_UART_GPIO_AF6},
    #endif
    #ifdef UART4_TX_PF7_AF6
    {UART_MODULE_4, GPIO_PF7, HAL_LL_UART4_BASE_ADDRESS, HAL_LL_UART_GPIO_AF6},
    #endif
    #ifdef UART4_TX_PA3_AF7
    {UART_MODULE_4, GPIO_PA3, HAL_LL_UART4_BASE_ADDRESS, HAL_LL_UART_GPIO_AF7},
    #endif
    #ifdef UART4_TX_PH10_AF7
    {UART_MODULE_4, GPIO_PH10, HAL_LL_UART4_BASE_ADDRESS, HAL_LL_UART_GPIO_AF7},
    #endif
    #ifdef UART4_TX_PC5_AF11
    {UART_MODULE_4, GPIO_PC5, HAL_LL_UART4_BASE_ADDRESS, HAL_LL_UART_GPIO_AF11},
    #endif
    #endif

    #ifdef UART_MODULE_5
    #ifdef UART5_TX_PF11_AF6
    {UART_MODULE_5, GPIO_PF11, HAL_LL_UART5_BASE_ADDRESS, HAL_LL_UART_GPIO_AF6},
    #endif
    #ifdef UART5_TX_PB5_AF7
    {UART_MODULE_5, GPIO_PB5, HAL_LL_UART5_BASE_ADDRESS, HAL_LL_UART_GPIO_AF7},
    #endif
    #ifdef UART5_TX_PA5_AF8
    {UART_MODULE_5, GPIO_PA5, HAL_LL_UART5_BASE_ADDRESS, HAL_LL_UART_GPIO_AF8},
    #endif
    #ifdef UART5_TX_PE7_AF8
    {UART_MODULE_5, GPIO_PE7, HAL_LL_UART5_BASE_ADDRESS, HAL_LL_UART_GPIO_AF8},
    #endif
    #endif

    {HAL_LL_MODULE_ERROR, HAL_LL_PIN_NC, HAL_LL_MODULE_ERROR, HAL_LL_PIN_NC}
};

/*!< UART RX Pins. */
static const hal_ll_uart_pin_map_t hal_ll_uart_rx_map[] = {
    
    #ifdef UART_MODULE_0
    #ifdef UART0_RX_PA15_AF3
    {UART_MODULE_0, GPIO_PA15, HAL_LL_UART0_BASE_ADDRESS, HAL_LL_UART_GPIO_AF3},
    #endif
    #ifdef UART0_RX_PC11_AF3
    {UART_MODULE_0, GPIO_PC11, HAL_LL_UART0_BASE_ADDRESS, HAL_LL_UART_GPIO_AF3},
    #endif
    #ifdef UART0_RX_PF2_AF3
    {UART_MODULE_0, GPIO_PF2, HAL_LL_UART0_BASE_ADDRESS, HAL_LL_UART_GPIO_AF3},
    #endif
    #ifdef UART0_RX_PF1_AF4
    {UART_MODULE_0, GPIO_PF1, HAL_LL_UART0_BASE_ADDRESS, HAL_LL_UART_GPIO_AF4},
    #endif
    #ifdef UART0_RX_PB8_AF5
    {UART_MODULE_0, GPIO_PB8, HAL_LL_UART0_BASE_ADDRESS, HAL_LL_UART_GPIO_AF5},
    #endif
    #ifdef UART0_RX_PB12_AF6
    {UART_MODULE_0, GPIO_PB12, HAL_LL_UART0_BASE_ADDRESS, HAL_LL_UART_GPIO_AF6},
    #endif
    #ifdef UART0_RX_PA0_AF7
    {UART_MODULE_0, GPIO_PA0, HAL_LL_UART0_BASE_ADDRESS, HAL_LL_UART_GPIO_AF7},
    #endif
    #ifdef UART0_RX_PA6_AF7
    {UART_MODULE_0, GPIO_PA6, HAL_LL_UART0_BASE_ADDRESS, HAL_LL_UART_GPIO_AF7},
    #endif
    #ifdef UART0_RX_PH11_AF8
    {UART_MODULE_0, GPIO_PH11, HAL_LL_UART0_BASE_ADDRESS, HAL_LL_UART_GPIO_AF8},
    #endif
    #ifdef UART0_RX_PD2_AF9
    {UART_MODULE_0, GPIO_PD2, HAL_LL_UART0_BASE_ADDRESS, HAL_LL_UART_GPIO_AF9},
    #endif
    #ifdef UART0_RX_PA4_AF11
    {UART_MODULE_0, GPIO_PA4, HAL_LL_UART0_BASE_ADDRESS, HAL_LL_UART_GPIO_AF11},
    #endif
    #endif

    #ifdef UART_MODULE_1
    #ifdef UART1_RX_PF1_AF2
    {UART_MODULE_1, GPIO_PF1, HAL_LL_UART1_BASE_ADDRESS, HAL_LL_UART_GPIO_AF2},
    #endif
    #ifdef UART1_RX_PD6_AF3
    {UART_MODULE_1, GPIO_PD6, HAL_LL_UART1_BASE_ADDRESS, HAL_LL_UART_GPIO_AF3},
    #endif
    #ifdef UART1_RX_PD10_AF3
    {UART_MODULE_1, GPIO_PD10, HAL_LL_UART1_BASE_ADDRESS, HAL_LL_UART_GPIO_AF3},
    #endif
    #ifdef UART1_RX_PB2_AF6
    {UART_MODULE_1, GPIO_PB2, HAL_LL_UART1_BASE_ADDRESS, HAL_LL_UART_GPIO_AF6},
    #endif
    #ifdef UART1_RX_PB6_AF6
    {UART_MODULE_1, GPIO_PB6, HAL_LL_UART1_BASE_ADDRESS, HAL_LL_UART_GPIO_AF6},
    #endif
    #ifdef UART1_RX_PA8_AF7
    {UART_MODULE_1, GPIO_PA8, HAL_LL_UART1_BASE_ADDRESS, HAL_LL_UART_GPIO_AF7},
    #endif
    #ifdef UART1_RX_PA2_AF8
    {UART_MODULE_1, GPIO_PA2, HAL_LL_UART1_BASE_ADDRESS, HAL_LL_UART_GPIO_AF8},
    #endif
    #ifdef UART1_RX_PC8_AF8
    {UART_MODULE_1, GPIO_PC8, HAL_LL_UART1_BASE_ADDRESS, HAL_LL_UART_GPIO_AF8},
    #endif
    #ifdef UART1_RX_PH9_AF10
    {UART_MODULE_1, GPIO_PH9, HAL_LL_UART1_BASE_ADDRESS, HAL_LL_UART_GPIO_AF10},
    #endif
    #endif

    #ifdef UART_MODULE_2
    #ifdef UART2_RX_PF5_AF2
    {UART_MODULE_2, GPIO_PF5, HAL_LL_UART2_BASE_ADDRESS, HAL_LL_UART_GPIO_AF2},
    #endif
    #ifdef UART2_RX_PE15_AF3
    {UART_MODULE_2, GPIO_PE15, HAL_LL_UART2_BASE_ADDRESS, HAL_LL_UART_GPIO_AF3},
    #endif
    #ifdef UART2_RX_PB0_AF7
    {UART_MODULE_2, GPIO_PB0, HAL_LL_UART2_BASE_ADDRESS, HAL_LL_UART_GPIO_AF7},
    #endif
    #ifdef UART2_RX_PD12_AF7
    {UART_MODULE_2, GPIO_PD12, HAL_LL_UART2_BASE_ADDRESS, HAL_LL_UART_GPIO_AF7},
    #endif
    #ifdef UART2_RX_PE9_AF7
    {UART_MODULE_2, GPIO_PE9, HAL_LL_UART2_BASE_ADDRESS, HAL_LL_UART_GPIO_AF7},
    #endif
    #ifdef UART2_RX_PC0_AF8
    {UART_MODULE_2, GPIO_PC0, HAL_LL_UART2_BASE_ADDRESS, HAL_LL_UART_GPIO_AF8},
    #endif
    #ifdef UART2_RX_PC4_AF8
    {UART_MODULE_2, GPIO_PC4, HAL_LL_UART2_BASE_ADDRESS, HAL_LL_UART_GPIO_AF8},
    #endif
    #ifdef UART2_RX_PB4_AF12
    {UART_MODULE_2, GPIO_PB4, HAL_LL_UART2_BASE_ADDRESS, HAL_LL_UART_GPIO_AF12},
    #endif
    #endif

    #ifdef UART_MODULE_3
    #ifdef UART3_RX_PD0_AF5
    {UART_MODULE_3, GPIO_PD0, HAL_LL_UART3_BASE_ADDRESS, HAL_LL_UART_GPIO_AF5},
    #endif
    #ifdef UART3_RX_PB14_AF7
    {UART_MODULE_3, GPIO_PB14, HAL_LL_UART3_BASE_ADDRESS, HAL_LL_UART_GPIO_AF7},
    #endif
    #ifdef UART3_RX_PC9_AF7
    {UART_MODULE_3, GPIO_PC9, HAL_LL_UART3_BASE_ADDRESS, HAL_LL_UART_GPIO_AF7},
    #endif
    #ifdef UART3_RX_PE0_AF7
    {UART_MODULE_3, GPIO_PE0, HAL_LL_UART3_BASE_ADDRESS, HAL_LL_UART_GPIO_AF7},
    #endif
    #ifdef UART3_RX_PE11_AF7
    {UART_MODULE_3, GPIO_PE11, HAL_LL_UART3_BASE_ADDRESS, HAL_LL_UART_GPIO_AF7},
    #endif
    #ifdef UART3_RX_PC2_AF11
    {UART_MODULE_3, GPIO_PC2, HAL_LL_UART3_BASE_ADDRESS, HAL_LL_UART_GPIO_AF11},
    #endif
    #endif

    #ifdef UART_MODULE_4
    #ifdef UART4_RX_PA13_AF3
    {UART_MODULE_4, GPIO_PA13, HAL_LL_UART4_BASE_ADDRESS, HAL_LL_UART_GPIO_AF3},
    #endif
    #ifdef UART4_RX_PC6_AF5
    {UART_MODULE_4, GPIO_PC6, HAL_LL_UART4_BASE_ADDRESS, HAL_LL_UART_GPIO_AF5},
    #endif
    #ifdef UART4_RX_PB10_AF6
    {UART_MODULE_4, GPIO_PB10, HAL_LL_UART4_BASE_ADDRESS, HAL_LL_UART_GPIO_AF6},
    #endif
    #ifdef UART4_RX_PF6_AF6
    {UART_MODULE_4, GPIO_PF6, HAL_LL_UART4_BASE_ADDRESS, HAL_LL_UART_GPIO_AF6},
    #endif
    #ifdef UART4_RX_PA2_AF7
    {UART_MODULE_4, GPIO_PA2, HAL_LL_UART4_BASE_ADDRESS, HAL_LL_UART_GPIO_AF7},
    #endif
    #ifdef UART4_RX_PH11_AF7
    {UART_MODULE_4, GPIO_PH11, HAL_LL_UART4_BASE_ADDRESS, HAL_LL_UART_GPIO_AF7},
    #endif
    #ifdef UART4_RX_PC4_AF11
    {UART_MODULE_4, GPIO_PC4, HAL_LL_UART4_BASE_ADDRESS, HAL_LL_UART_GPIO_AF11},
    #endif
    #endif

    #ifdef UART_MODULE_5
    #ifdef UART5_RX_PF10_AF6
    {UART_MODULE_5, GPIO_PF10, HAL_LL_UART5_BASE_ADDRESS, HAL_LL_UART_GPIO_AF6},
    #endif
    #ifdef UART5_RX_PB4_AF7
    {UART_MODULE_5, GPIO_PB4, HAL_LL_UART5_BASE_ADDRESS, HAL_LL_UART_GPIO_AF7},
    #endif
    #ifdef UART5_RX_PA4_AF8
    {UART_MODULE_5, GPIO_PA4, HAL_LL_UART5_BASE_ADDRESS, HAL_LL_UART_GPIO_AF8},
    #endif
    #ifdef UART5_RX_PE6_AF8
    {UART_MODULE_5, GPIO_PE6, HAL_LL_UART5_BASE_ADDRESS, HAL_LL_UART_GPIO_AF8},
    #endif
    #endif

    {HAL_LL_MODULE_ERROR, HAL_LL_PIN_NC, HAL_LL_MODULE_ERROR, HAL_LL_PIN_NC}
};

#ifdef __cplusplus
}
#endif

#endif // _HAL_LL_UART_PIN_MAP_H_
// ------------------------------------------------------------------------- END