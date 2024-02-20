/****************************************************************************
**
** Copyright (C) 2024 MikroElektronika d.o.o.
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

/*!< UART module base addresses. */
#ifdef UART_MODULE_0
#ifdef MK8xLPUART
static const hal_ll_base_addr_t HAL_LL_UART0_BASE = 0x400C4000;
#else
static const hal_ll_base_addr_t HAL_LL_UART0_BASE = 0x4006A000;
#endif
#endif

#ifdef UART_MODULE_1
#ifdef MK8xLPUART
static const hal_ll_base_addr_t HAL_LL_UART1_BASE = 0x400C5000;
#else
static const hal_ll_base_addr_t HAL_LL_UART1_BASE = 0x4006B000;
#endif
#endif

#ifdef UART_MODULE_2
#ifdef MK8xLPUART
static const hal_ll_base_addr_t HAL_LL_UART2_BASE = 0x400C6000;
#else
static const hal_ll_base_addr_t HAL_LL_UART2_BASE = 0x4006C000;
#endif
#endif

#ifdef UART_MODULE_3
#ifdef MK8xLPUART
static const hal_ll_base_addr_t HAL_LL_UART3_BASE = 0x400C7000;
#else
static const hal_ll_base_addr_t HAL_LL_UART3_BASE = 0x4006D000;
#endif
#endif

#ifdef UART_MODULE_4
#ifdef MK8xLPUART
static const hal_ll_base_addr_t HAL_LL_UART4_BASE = 0x400D6000;
#else
static const hal_ll_base_addr_t HAL_LL_UART4_BASE = 0x400EA000;
#endif
#endif

#ifdef UART_MODULE_5
static const hal_ll_base_addr_t HAL_LL_UART5_BASE = 0x400EB000;
#endif

/*!< @brief UART pin structure. */
typedef struct {
    uint8_t module_index;
    hal_ll_pin_name_t pin;
    hal_ll_base_addr_t base;
    uint8_t af;
} hal_ll_uart_pin_map_t;

/*!< UART TX Pins. */
static const hal_ll_uart_pin_map_t hal_ll_uart_tx_map[] = {
    #ifdef UART0_TX_PA2_AF2
    {hal_ll_uart_module_num(UART_MODULE_0), PA2, HAL_LL_UART0_BASE, 2},
    #endif
    #ifdef UART1_TX_PC4_AF3
    {hal_ll_uart_module_num(UART_MODULE_1), PC4, HAL_LL_UART1_BASE, 3},
    #endif
    #ifdef UART0_TX_PD7_AF3
    {hal_ll_uart_module_num(UART_MODULE_0), PD7, HAL_LL_UART0_BASE, 3},
    #endif
    #ifdef UART0_TX_PB17_AF3
    {hal_ll_uart_module_num(UART_MODULE_0), PB17, HAL_LL_UART0_BASE, 3},
    #endif
    #ifdef UART2_TX_PD3_AF3
    {hal_ll_uart_module_num(UART_MODULE_2), PD3, HAL_LL_UART2_BASE, 3},
    #endif
    #ifdef UART1_TX_PE0_AF3
    {hal_ll_uart_module_num(UART_MODULE_1), PE0, HAL_LL_UART1_BASE, 3},
    #endif
    #ifdef UART0_TX_PA14_AF3
    {hal_ll_uart_module_num(UART_MODULE_0), PA14, HAL_LL_UART0_BASE, 3},
    #endif
    #ifdef UART3_TX_PE4_AF3
    {hal_ll_uart_module_num(UART_MODULE_3), PE4, HAL_LL_UART3_BASE, 3},
    #endif
    #ifdef UART3_TX_PB11_AF3
    {hal_ll_uart_module_num(UART_MODULE_3), PB11, HAL_LL_UART3_BASE, 3},
    #endif
    #ifdef UART3_TX_PC17_AF3
    {hal_ll_uart_module_num(UART_MODULE_3), PC17, HAL_LL_UART3_BASE, 3},
    #endif
    #ifdef UART4_TX_PE24_AF3
    {hal_ll_uart_module_num(UART_MODULE_4), PE24, HAL_LL_UART4_BASE, 3},
    #endif
    #ifdef UART4_TX_PC15_AF3
    {hal_ll_uart_module_num(UART_MODULE_4), PC15, HAL_LL_UART4_BASE, 3},
    #endif
    #ifdef UART5_TX_PE8_AF3
    {hal_ll_uart_module_num(UART_MODULE_5), PE8, HAL_LL_UART5_BASE, 3},
    #endif
    #ifdef UART5_TX_PD9_AF3
    {hal_ll_uart_module_num(UART_MODULE_5), PD9, HAL_LL_UART5_BASE, 3},
    #endif
    #ifdef UART2_TX_PE16_AF3
    {hal_ll_uart_module_num(UART_MODULE_2), PE16, HAL_LL_UART2_BASE, 3},
    #endif
    #ifdef UART4_TX_PA20_AF3
    {hal_ll_uart_module_num(UART_MODULE_4), PA20, HAL_LL_UART4_BASE, 3},
    #endif
    #ifdef UART2_TX_PE12_AF3
    {hal_ll_uart_module_num(UART_MODULE_2), PE12, HAL_LL_UART2_BASE, 3},
    #endif
    #ifdef UART1_TX_PE16_AF3
    {hal_ll_uart_module_num(UART_MODULE_1), PE16, HAL_LL_UART1_BASE, 3},
    #endif
    #ifdef UART0_TX_PE20_AF4
    {hal_ll_uart_module_num(UART_MODULE_0), PE20, HAL_LL_UART0_BASE, 4},
    #endif
    #ifdef UART0_TX_PB1_AF7
    {hal_ll_uart_module_num(UART_MODULE_0), PB1, HAL_LL_UART0_BASE, 7},
    #endif
    #ifdef UART0_TX_PC7_AF5
    {hal_ll_uart_module_num(UART_MODULE_0), PC7, HAL_LL_UART0_BASE, 5},
    #endif
    #ifdef UART4_TX_PE24_AF8
    {hal_ll_uart_module_num(UART_MODULE_4), PE24, HAL_LL_UART4_BASE, 8},
    #endif
    #ifdef UART4_TX_PC15_AF9
    {hal_ll_uart_module_num(UART_MODULE_4), PC15, HAL_LL_UART4_BASE, 9},
    #endif

    {HAL_LL_MODULE_ERROR, HAL_LL_PIN_NC, HAL_LL_MODULE_ERROR, HAL_LL_PIN_NC}
};

/*!< UART RX Pins. */
static const hal_ll_uart_pin_map_t hal_ll_uart_rx_map[] = {
    #ifdef UART0_RX_PA1_AF2
    {hal_ll_uart_module_num(UART_MODULE_0), PA1, HAL_LL_UART0_BASE, 2},
    #endif
    #ifdef UART1_RX_PC3_AF3
    {hal_ll_uart_module_num(UART_MODULE_1), PC3, HAL_LL_UART1_BASE, 3},
    #endif
    #ifdef UART0_RX_PD6_AF3
    {hal_ll_uart_module_num(UART_MODULE_0), PD6, HAL_LL_UART0_BASE, 3},
    #endif
    #ifdef UART0_RX_PB16_AF3
    {hal_ll_uart_module_num(UART_MODULE_0), PB16, HAL_LL_UART0_BASE, 3},
    #endif
    #ifdef UART2_RX_PD2_AF3
    {hal_ll_uart_module_num(UART_MODULE_2), PD2, HAL_LL_UART2_BASE, 3},
    #endif
    #ifdef UART1_RX_PE1_AF3
    {hal_ll_uart_module_num(UART_MODULE_1), PE1, HAL_LL_UART1_BASE, 3},
    #endif
    #ifdef UART0_RX_PA15_AF3
    {hal_ll_uart_module_num(UART_MODULE_0), PA15, HAL_LL_UART0_BASE, 3},
    #endif
    #ifdef UART3_RX_PE5_AF3
    {hal_ll_uart_module_num(UART_MODULE_3), PE5, HAL_LL_UART3_BASE, 3},
    #endif
    #ifdef UART3_RX_PB10_AF3
    {hal_ll_uart_module_num(UART_MODULE_3), PB10, HAL_LL_UART3_BASE, 3},
    #endif
    #ifdef UART3_RX_PC16_AF3
    {hal_ll_uart_module_num(UART_MODULE_3), PC16, HAL_LL_UART3_BASE, 3},
    #endif
    #ifdef UART4_RX_PE25_AF3
    {hal_ll_uart_module_num(UART_MODULE_4), PE25, HAL_LL_UART4_BASE, 3},
    #endif
    #ifdef UART4_RX_PC14_AF3
    {hal_ll_uart_module_num(UART_MODULE_4), PC14, HAL_LL_UART4_BASE, 3},
    #endif
    #ifdef UART5_RX_PE9_AF3
    {hal_ll_uart_module_num(UART_MODULE_5), PE9, HAL_LL_UART5_BASE, 3},
    #endif
    #ifdef UART5_RX_PD8_AF3
    {hal_ll_uart_module_num(UART_MODULE_5), PD8, HAL_LL_UART5_BASE, 3},
    #endif
    #ifdef UART2_RX_PE17_AF3
    {hal_ll_uart_module_num(UART_MODULE_2), PE17, HAL_LL_UART2_BASE, 3},
    #endif
    #ifdef UART4_RX_PA21_AF3
    {hal_ll_uart_module_num(UART_MODULE_4), PA21, HAL_LL_UART4_BASE, 3},
    #endif
    #ifdef UART2_RX_PE13_AF3
    {hal_ll_uart_module_num(UART_MODULE_2), PE13, HAL_LL_UART2_BASE, 3},
    #endif
    #ifdef UART1_RX_PE17_AF3
    {hal_ll_uart_module_num(UART_MODULE_1), PE17, HAL_LL_UART1_BASE, 3},
    #endif
    #ifdef UART0_RX_PE21_AF4
    {hal_ll_uart_module_num(UART_MODULE_0), PE21, HAL_LL_UART0_BASE, 4},
    #endif
    #ifdef UART0_RX_PB0_AF7
    {hal_ll_uart_module_num(UART_MODULE_0), PB0, HAL_LL_UART0_BASE, 7},
    #endif
    #ifdef UART0_RX_PC6_AF5
    {hal_ll_uart_module_num(UART_MODULE_0), PC6, HAL_LL_UART0_BASE, 5},
    #endif
    #ifdef UART4_RX_PE25_AF8
    {hal_ll_uart_module_num(UART_MODULE_4), PE25, HAL_LL_UART4_BASE, 8},
    #endif
    #ifdef UART4_RX_PC14_AF9
    {hal_ll_uart_module_num(UART_MODULE_4), PC14, HAL_LL_UART4_BASE, 9},
    #endif

    {HAL_LL_MODULE_ERROR, HAL_LL_PIN_NC, HAL_LL_MODULE_ERROR, HAL_LL_PIN_NC}
};

#ifdef __cplusplus
}
#endif

#endif // _HAL_LL_UART_PIN_MAP_H_
// ------------------------------------------------------------------------- END
