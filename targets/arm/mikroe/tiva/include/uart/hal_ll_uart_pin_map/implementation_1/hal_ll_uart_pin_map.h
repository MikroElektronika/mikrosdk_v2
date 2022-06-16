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
static const hal_ll_base_addr_t HAL_LL_UART0_BASE_ADDRESS = 0x4000C000;
#endif
#ifdef UART_MODULE_1
static const hal_ll_base_addr_t HAL_LL_UART1_BASE_ADDRESS = 0x4000D000;
#endif
#ifdef UART_MODULE_2
static const hal_ll_base_addr_t HAL_LL_UART2_BASE_ADDRESS = 0x4000E000;
#endif
#ifdef UART_MODULE_3
static const hal_ll_base_addr_t HAL_LL_UART3_BASE_ADDRESS = 0x4000F000;
#endif
#ifdef UART_MODULE_4
static const hal_ll_base_addr_t HAL_LL_UART4_BASE_ADDRESS = 0x40010000;
#endif
#ifdef UART_MODULE_5
static const hal_ll_base_addr_t HAL_LL_UART5_BASE_ADDRESS = 0x40011000;
#endif
#ifdef UART_MODULE_6
static const hal_ll_base_addr_t HAL_LL_UART6_BASE_ADDRESS = 0x40012000;
#endif
#ifdef UART_MODULE_7
static const hal_ll_base_addr_t HAL_LL_UART7_BASE_ADDRESS = 0x40013000;
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
    #ifdef UART0_TX_PA1_AF1
    {hal_ll_uart_module_num(UART_MODULE_0), PA1, HAL_LL_UART0_BASE_ADDRESS, 1},
    #endif
    #ifdef UART1_TX_PB1_AF1
    {hal_ll_uart_module_num(UART_MODULE_1), PB1, HAL_LL_UART1_BASE_ADDRESS, 1},
    #endif
    #ifdef UART1_TX_PC5_AF2
    {hal_ll_uart_module_num(UART_MODULE_1), PC5, HAL_LL_UART1_BASE_ADDRESS, 2},
    #endif
    #ifdef UART2_TX_PD7_AF1
    {hal_ll_uart_module_num(UART_MODULE_2), PD7, HAL_LL_UART2_BASE_ADDRESS, 1},
    #endif
    #ifdef UART2_TX_PG5_AF1
    {hal_ll_uart_module_num(UART_MODULE_2), PG5, HAL_LL_UART2_BASE_ADDRESS, 1},
    #endif
    #ifdef UART3_TX_PC7_AF1
    {hal_ll_uart_module_num(UART_MODULE_3), PC7, HAL_LL_UART3_BASE_ADDRESS, 1},
    #endif
    #ifdef UART4_TX_PC5_AF1
    {hal_ll_uart_module_num(UART_MODULE_4), PC5, HAL_LL_UART4_BASE_ADDRESS, 1},
    #endif
    #ifdef UART5_TX_PE5_AF1
    {hal_ll_uart_module_num(UART_MODULE_5), PE5, HAL_LL_UART5_BASE_ADDRESS, 1},
    #endif
    #ifdef UART6_TX_PD5_AF1
    {hal_ll_uart_module_num(UART_MODULE_6), PD5, HAL_LL_UART6_BASE_ADDRESS, 1},
    #endif
    #ifdef UART7_TX_PE1_AF1
    {hal_ll_uart_module_num(UART_MODULE_7), PE1, HAL_LL_UART7_BASE_ADDRESS, 1},
    #endif
    #ifdef UART4_TX_PJ1_AF1
    {hal_ll_uart_module_num(UART_MODULE_4), PJ1, HAL_LL_UART4_BASE_ADDRESS, 1},
    #endif
    #ifdef UART5_TX_PJ3_AF1
    {hal_ll_uart_module_num(UART_MODULE_5), PJ3, HAL_LL_UART5_BASE_ADDRESS, 1},
    #endif
    #ifdef UART6_TX_PJ5_AF1
    {hal_ll_uart_module_num(UART_MODULE_6), PJ5, HAL_LL_UART6_BASE_ADDRESS, 1},
    #endif
    #ifdef UART7_TX_PK5_AF1
    {hal_ll_uart_module_num(UART_MODULE_7), PK5, HAL_LL_UART7_BASE_ADDRESS, 1},
    #endif
    #ifdef UART1_TX_PQ5_AF1
    {hal_ll_uart_module_num(UART_MODULE_1), PQ5, HAL_LL_UART1_BASE_ADDRESS, 1},
    #endif
    #ifdef UART2_TX_PA7_AF1
    {hal_ll_uart_module_num(UART_MODULE_2), PA7, HAL_LL_UART2_BASE_ADDRESS, 1},
    #endif
    #ifdef UART2_TX_PD5_AF1
    {hal_ll_uart_module_num(UART_MODULE_2), PD5, HAL_LL_UART2_BASE_ADDRESS, 1},
    #endif
    #ifdef UART3_TX_PA5_AF1
    {hal_ll_uart_module_num(UART_MODULE_3), PA5, HAL_LL_UART3_BASE_ADDRESS, 1},
    #endif
    #ifdef UART3_TX_PJ1_AF1
    {hal_ll_uart_module_num(UART_MODULE_3), PJ1, HAL_LL_UART3_BASE_ADDRESS, 1},
    #endif
    #ifdef UART4_TX_PA3_AF1
    {hal_ll_uart_module_num(UART_MODULE_4), PA3, HAL_LL_UART4_BASE_ADDRESS, 1},
    #endif
    #ifdef UART4_TX_PK1_AF1
    {hal_ll_uart_module_num(UART_MODULE_4), PK1, HAL_LL_UART4_BASE_ADDRESS, 1},
    #endif
    #ifdef UART5_TX_PC7_AF1
    {hal_ll_uart_module_num(UART_MODULE_5), PC7, HAL_LL_UART5_BASE_ADDRESS, 1},
    #endif
    #ifdef UART6_TX_PP1_AF1
    {hal_ll_uart_module_num(UART_MODULE_6), PP1, HAL_LL_UART6_BASE_ADDRESS, 1},
    #endif
    #ifdef UART7_TX_PC5_AF1
    {hal_ll_uart_module_num(UART_MODULE_7), PC5, HAL_LL_UART7_BASE_ADDRESS, 1},
    #endif
    #ifdef UART1_TX_PR6_AF1
    {hal_ll_uart_module_num(UART_MODULE_1), PR6, HAL_LL_UART1_BASE_ADDRESS, 1},
    #endif
    #ifdef UART4_TX_PR0_AF1
    {hal_ll_uart_module_num(UART_MODULE_4), PR0, HAL_LL_UART4_BASE_ADDRESS, 1},
    #endif
    #ifdef UART5_TX_PH7_AF1
    {hal_ll_uart_module_num(UART_MODULE_5), PH7, HAL_LL_UART5_BASE_ADDRESS, 1},
    #endif
    #ifdef UART7_TX_PH7_AF2
    {hal_ll_uart_module_num(UART_MODULE_7), PH7, HAL_LL_UART7_BASE_ADDRESS, 2},
    #endif

    {HAL_LL_MODULE_ERROR, HAL_LL_PIN_NC, HAL_LL_MODULE_ERROR, HAL_LL_PIN_NC}
};

/*!< UART RX Pins. */
static const hal_ll_uart_pin_map_t hal_ll_uart_rx_map[] = {
    #ifdef UART0_RX_PA0_AF1
    {hal_ll_uart_module_num(UART_MODULE_0), PA0, HAL_LL_UART0_BASE_ADDRESS, 1},
    #endif
    #ifdef UART1_RX_PB0_AF1
    {hal_ll_uart_module_num(UART_MODULE_1), PB0, HAL_LL_UART1_BASE_ADDRESS, 1},
    #endif
    #ifdef UART1_RX_PC4_AF2
    {hal_ll_uart_module_num(UART_MODULE_1), PC4, HAL_LL_UART1_BASE_ADDRESS, 2},
    #endif
    #ifdef UART2_RX_PD6_AF1
    {hal_ll_uart_module_num(UART_MODULE_2), PD6, HAL_LL_UART2_BASE_ADDRESS, 1},
    #endif
    #ifdef UART2_RX_PG4_AF1
    {hal_ll_uart_module_num(UART_MODULE_2), PG4, HAL_LL_UART2_BASE_ADDRESS, 1},
    #endif
    #ifdef UART3_RX_PC6_AF1
    {hal_ll_uart_module_num(UART_MODULE_3), PC6, HAL_LL_UART3_BASE_ADDRESS, 1},
    #endif
    #ifdef UART4_RX_PC4_AF1
    {hal_ll_uart_module_num(UART_MODULE_4), PC4, HAL_LL_UART4_BASE_ADDRESS, 1},
    #endif
    #ifdef UART5_RX_PE4_AF1
    {hal_ll_uart_module_num(UART_MODULE_5), PE4, HAL_LL_UART5_BASE_ADDRESS, 1},
    #endif
    #ifdef UART6_RX_PD4_AF1
    {hal_ll_uart_module_num(UART_MODULE_6), PD4, HAL_LL_UART6_BASE_ADDRESS, 1},
    #endif
    #ifdef UART7_RX_PE0_AF1
    {hal_ll_uart_module_num(UART_MODULE_7), PE0, HAL_LL_UART7_BASE_ADDRESS, 1},
    #endif
    #ifdef UART4_RX_PJ0_AF1
    {hal_ll_uart_module_num(UART_MODULE_4), PJ0, HAL_LL_UART4_BASE_ADDRESS, 1},
    #endif
    #ifdef UART5_RX_PJ2_AF1
    {hal_ll_uart_module_num(UART_MODULE_5), PJ2, HAL_LL_UART5_BASE_ADDRESS, 1},
    #endif
    #ifdef UART6_RX_PJ4_AF1
    {hal_ll_uart_module_num(UART_MODULE_6), PJ4, HAL_LL_UART6_BASE_ADDRESS, 1},
    #endif
    #ifdef UART7_RX_PK4_AF1
    {hal_ll_uart_module_num(UART_MODULE_7), PK4, HAL_LL_UART7_BASE_ADDRESS, 1},
    #endif
    #ifdef UART1_RX_PQ4_AF1
    {hal_ll_uart_module_num(UART_MODULE_1), PQ4, HAL_LL_UART1_BASE_ADDRESS, 1},
    #endif
    #ifdef UART2_RX_PA6_AF1
    {hal_ll_uart_module_num(UART_MODULE_2), PA6, HAL_LL_UART2_BASE_ADDRESS, 1},
    #endif
    #ifdef UART2_RX_PD4_AF1
    {hal_ll_uart_module_num(UART_MODULE_2), PD4, HAL_LL_UART2_BASE_ADDRESS, 1},
    #endif
    #ifdef UART3_RX_PA4_AF1
    {hal_ll_uart_module_num(UART_MODULE_3), PA4, HAL_LL_UART3_BASE_ADDRESS, 1},
    #endif
    #ifdef UART3_RX_PJ0_AF1
    {hal_ll_uart_module_num(UART_MODULE_3), PJ0, HAL_LL_UART3_BASE_ADDRESS, 1},
    #endif
    #ifdef UART4_RX_PA2_AF1
    {hal_ll_uart_module_num(UART_MODULE_4), PA2, HAL_LL_UART4_BASE_ADDRESS, 1},
    #endif
    #ifdef UART4_RX_PK0_AF1
    {hal_ll_uart_module_num(UART_MODULE_4), PK0, HAL_LL_UART4_BASE_ADDRESS, 1},
    #endif
    #ifdef UART5_RX_PC6_AF1
    {hal_ll_uart_module_num(UART_MODULE_5), PC6, HAL_LL_UART5_BASE_ADDRESS, 1},
    #endif
    #ifdef UART6_RX_PP0_AF1
    {hal_ll_uart_module_num(UART_MODULE_6), PP0, HAL_LL_UART6_BASE_ADDRESS, 1},
    #endif
    #ifdef UART7_RX_PC4_AF1
    {hal_ll_uart_module_num(UART_MODULE_7), PC4, HAL_LL_UART7_BASE_ADDRESS, 1},
    #endif
    #ifdef UART1_RX_PR5_AF1
    {hal_ll_uart_module_num(UART_MODULE_1), PR5, HAL_LL_UART1_BASE_ADDRESS, 1},
    #endif
    #ifdef UART4_RX_PR1_AF1
    {hal_ll_uart_module_num(UART_MODULE_4), PR1, HAL_LL_UART4_BASE_ADDRESS, 1},
    #endif
    #ifdef UART5_RX_PH6_AF1
    {hal_ll_uart_module_num(UART_MODULE_5), PH6, HAL_LL_UART5_BASE_ADDRESS, 1},
    #endif
    #ifdef UART7_RX_PH6_AF2
    {hal_ll_uart_module_num(UART_MODULE_7), PH6, HAL_LL_UART7_BASE_ADDRESS, 2},
    #endif

    {HAL_LL_MODULE_ERROR, HAL_LL_PIN_NC, HAL_LL_MODULE_ERROR, HAL_LL_PIN_NC}
};

#ifdef __cplusplus
}
#endif

#endif // _HAL_LL_UART_PIN_MAP_H_
// ------------------------------------------------------------------------- END
