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

/*!< @brief Helper macro for getting adequate module index number */
#define hal_ll_uart_module_num(_module_num) (_module_num - 1)
#define hal_ll_usart_module_num(_module_num) hal_ll_uart_module_num(_module_num)
#define hal_ll_lpuart_module_num(_module_num) hal_ll_uart_module_num(_module_num)

/*!< @brief Pin structure */
typedef struct
{
    uint8_t module_index;
    hal_ll_pin_name_t pin;
    hal_ll_base_addr_t base;
    uint32_t af;
} hal_ll_uart_pin_map_t;

#ifdef UART_MODULE_1
#define USART_MODULE_1 UART_MODULE_1
#define UART1_BASE_ADDRESS (0x40013800UL)
#define UART1_BASE_ADDR UART1_BASE_ADDRESS
#define USART1_BASE_ADDR UART1_BASE_ADDRESS
#define USART1_BASE_ADDRESS UART1_BASE_ADDRESS
#define HAL_LL_UART1_BASE_ADDR UART1_BASE_ADDRESS
#define HAL_LL_USART1_BASE_ADDR UART1_BASE_ADDRESS
#define HAL_LL_UART1_BASE_ADDRESS UART1_BASE_ADDRESS
#define HAL_LL_USART1_BASE_ADDRESS UART1_BASE_ADDRESS
#endif
#ifdef UART_MODULE_2
#define USART_MODULE_2 UART_MODULE_2
#define UART2_BASE_ADDRESS (0x40004400UL)
#define UART2_BASE_ADDR UART2_BASE_ADDRESS
#define USART2_BASE_ADDR UART2_BASE_ADDRESS
#define USART2_BASE_ADDRESS UART2_BASE_ADDRESS
#define HAL_LL_UART2_BASE_ADDR UART2_BASE_ADDRESS
#define HAL_LL_USART2_BASE_ADDR UART2_BASE_ADDRESS
#define HAL_LL_UART2_BASE_ADDRESS UART2_BASE_ADDRESS
#define HAL_LL_USART2_BASE_ADDRESS UART2_BASE_ADDRESS
#endif
#ifdef UART_MODULE_3
#define USART_MODULE_3 UART_MODULE_3
#define UART3_BASE_ADDRESS (0x40004800UL)
#define UART3_BASE_ADDR UART3_BASE_ADDRESS
#define USART3_BASE_ADDR UART3_BASE_ADDRESS
#define USART3_BASE_ADDRESS UART3_BASE_ADDRESS
#define HAL_LL_UART3_BASE_ADDR UART3_BASE_ADDRESS
#define HAL_LL_USART3_BASE_ADDR UART3_BASE_ADDRESS
#define HAL_LL_UART3_BASE_ADDRESS UART3_BASE_ADDRESS
#define HAL_LL_USART3_BASE_ADDRESS UART3_BASE_ADDRESS
#endif
#ifdef UART_MODULE_4
#define USART_MODULE_4 UART_MODULE_4
#define UART4_BASE_ADDRESS (0x40004C00UL)
#define UART4_BASE_ADDR UART4_BASE_ADDRESS
#define USART4_BASE_ADDR UART4_BASE_ADDRESS
#define USART4_BASE_ADDRESS UART4_BASE_ADDRESS
#define HAL_LL_UART4_BASE_ADDR UART4_BASE_ADDRESS
#define HAL_LL_USART4_BASE_ADDR UART4_BASE_ADDRESS
#define HAL_LL_UART4_BASE_ADDRESS UART4_BASE_ADDRESS
#define HAL_LL_USART4_BASE_ADDRESS UART4_BASE_ADDRESS
#endif
#ifdef UART_MODULE_5
#define USART_MODULE_5 UART_MODULE_5
#define UART5_BASE_ADDRESS (0x40005000UL)
#define UART5_BASE_ADDR UART5_BASE_ADDRESS
#define USART5_BASE_ADDR UART5_BASE_ADDRESS
#define USART5_BASE_ADDRESS UART5_BASE_ADDRESS
#define HAL_LL_UART5_BASE_ADDR UART5_BASE_ADDRESS
#define HAL_LL_USART5_BASE_ADDR UART5_BASE_ADDRESS
#define HAL_LL_UART5_BASE_ADDRESS UART5_BASE_ADDRESS
#define HAL_LL_USART5_BASE_ADDRESS UART5_BASE_ADDRESS
#endif
#ifdef UART_MODULE_6
#define USART_MODULE_6 UART_MODULE_6
#define UART6_BASE_ADDRESS (0x40013C00UL)
#define UART6_BASE_ADDR UART6_BASE_ADDRESS
#define USART6_BASE_ADDR UART6_BASE_ADDRESS
#define USART6_BASE_ADDRESS UART6_BASE_ADDRESS
#define HAL_LL_UART6_BASE_ADDR UART6_BASE_ADDRESS
#define HAL_LL_USART6_BASE_ADDR UART6_BASE_ADDRESS
#define HAL_LL_UART6_BASE_ADDRESS UART6_BASE_ADDRESS
#define HAL_LL_USART6_BASE_ADDRESS UART6_BASE_ADDRESS
#endif

/*!< @brief UART TX pins */
static const hal_ll_uart_pin_map_t hal_ll_uart_tx_map[] =
{
    #ifdef USART1_TX_PA9_AF1
    {hal_ll_usart_module_num(USART_MODULE_1), PA9, USART1_BASE_ADDRESS, 1},
    #endif
    #ifdef USART1_TX_PB6_AF0
    {hal_ll_usart_module_num(USART_MODULE_1), PB6, USART1_BASE_ADDRESS, 0},
    #endif
    #ifdef USART1_TX_PC4_AF1
    {hal_ll_usart_module_num(USART_MODULE_1), PC4, USART1_BASE_ADDRESS, 1},
    #endif
    #ifdef USART2_TX_PA14_AF1
    {hal_ll_usart_module_num(USART_MODULE_2), PA14, USART2_BASE_ADDRESS, 1},
    #endif
    #ifdef USART2_TX_PA2_AF1
    {hal_ll_usart_module_num(USART_MODULE_2), PA2, USART2_BASE_ADDRESS, 1},
    #endif
    #ifdef USART2_TX_PD5_AF0
    {hal_ll_usart_module_num(USART_MODULE_2), PD5, USART2_BASE_ADDRESS, 0},
    #endif
    #ifdef USART3_TX_PA5_AF4
    {hal_ll_usart_module_num(USART_MODULE_3), PA5, USART3_BASE_ADDRESS, 4},
    #endif
    #ifdef USART3_TX_PB10_AF4
    {hal_ll_usart_module_num(USART_MODULE_3), PB10, USART3_BASE_ADDRESS, 4},
    #endif
    #ifdef USART3_TX_PB2_AF4
    {hal_ll_usart_module_num(USART_MODULE_3), PB2, USART3_BASE_ADDRESS, 4},
    #endif
    #ifdef USART3_TX_PB8_AF4
    {hal_ll_usart_module_num(USART_MODULE_3), PB8, USART3_BASE_ADDRESS, 4},
    #endif
    #ifdef USART3_TX_PC10_AF0
    {hal_ll_usart_module_num(USART_MODULE_3), PC10, USART3_BASE_ADDRESS, 0},
    #endif
    #ifdef USART3_TX_PC4_AF0
    {hal_ll_usart_module_num(USART_MODULE_3), PC4, USART3_BASE_ADDRESS, 0},
    #endif
    #ifdef USART3_TX_PD8_AF0
    {hal_ll_usart_module_num(USART_MODULE_3), PD8, USART3_BASE_ADDRESS, 0},
    #endif
    #ifdef USART4_TX_PA0_AF4
    {hal_ll_usart_module_num(USART_MODULE_4), PA0, USART4_BASE_ADDRESS, 4},
    #endif
    #ifdef USART4_TX_PC10_AF1
    {hal_ll_usart_module_num(USART_MODULE_4), PC10, USART4_BASE_ADDRESS, 1},
    #endif
    #ifdef USART4_TX_PE8_AF0
    {hal_ll_usart_module_num(USART_MODULE_4), PE8, USART4_BASE_ADDRESS, 0},
    #endif
    #ifdef USART5_TX_PB0_AF8
    {hal_ll_usart_module_num(USART_MODULE_5), PB0, USART5_BASE_ADDRESS, 8},
    #endif
    #ifdef USART5_TX_PB3_AF3
    {hal_ll_usart_module_num(USART_MODULE_5), PB3, USART5_BASE_ADDRESS, 3},
    #endif
    #ifdef USART5_TX_PC12_AF3
    {hal_ll_usart_module_num(USART_MODULE_5), PC12, USART5_BASE_ADDRESS, 3},
    #endif
    #ifdef USART5_TX_PD3_AF3
    {hal_ll_usart_module_num(USART_MODULE_5), PD3, USART5_BASE_ADDRESS, 3},
    #endif
    #ifdef USART5_TX_PE10_AF3
    {hal_ll_usart_module_num(USART_MODULE_5), PE10, USART5_BASE_ADDRESS, 3},
    #endif
    #ifdef USART6_TX_PA4_AF3
    {hal_ll_usart_module_num(USART_MODULE_6), PA4, USART6_BASE_ADDRESS, 3},
    #endif
    #ifdef USART6_TX_PB8_AF8
    {hal_ll_usart_module_num(USART_MODULE_6), PB8, USART6_BASE_ADDRESS, 8},
    #endif
    #ifdef USART6_TX_PC0_AF4
    {hal_ll_usart_module_num(USART_MODULE_6), PC0, USART6_BASE_ADDRESS, 4},
    #endif
    #ifdef USART6_TX_PF9_AF3
    {hal_ll_usart_module_num(USART_MODULE_6), PF9, USART6_BASE_ADDRESS, 3},
    #endif
    {HAL_LL_MODULE_ERROR, HAL_LL_PIN_NC, HAL_LL_MODULE_ERROR, HAL_LL_PIN_NC}
    //------------ END TX
};

/*!< @brief UART RX pins */
static const hal_ll_uart_pin_map_t hal_ll_uart_rx_map[] =
{
    #ifdef USART1_RX_PA10_AF1
    {hal_ll_usart_module_num(USART_MODULE_1), PA10, USART1_BASE_ADDRESS, 1},
    #endif
    #ifdef USART1_RX_PB7_AF0
    {hal_ll_usart_module_num(USART_MODULE_1), PB7, USART1_BASE_ADDRESS, 0},
    #endif
    #ifdef USART1_RX_PC5_AF1
    {hal_ll_usart_module_num(USART_MODULE_1), PC5, USART1_BASE_ADDRESS, 1},
    #endif
    #ifdef USART2_RX_PA15_AF1
    {hal_ll_usart_module_num(USART_MODULE_2), PA15, USART2_BASE_ADDRESS, 1},
    #endif
    #ifdef USART2_RX_PA3_AF1
    {hal_ll_usart_module_num(USART_MODULE_2), PA3, USART2_BASE_ADDRESS, 1},
    #endif
    #ifdef USART2_RX_PD6_AF0
    {hal_ll_usart_module_num(USART_MODULE_2), PD6, USART2_BASE_ADDRESS, 0},
    #endif
    #ifdef USART3_RX_PB0_AF4
    {hal_ll_usart_module_num(USART_MODULE_3), PB0, USART3_BASE_ADDRESS, 4},
    #endif
    #ifdef USART3_RX_PB11_AF4
    {hal_ll_usart_module_num(USART_MODULE_3), PB11, USART3_BASE_ADDRESS, 4},
    #endif
    #ifdef USART3_RX_PB9_AF4
    {hal_ll_usart_module_num(USART_MODULE_3), PB9, USART3_BASE_ADDRESS, 4},
    #endif
    #ifdef USART3_RX_PC11_AF0
    {hal_ll_usart_module_num(USART_MODULE_3), PC11, USART3_BASE_ADDRESS, 0},
    #endif
    #ifdef USART3_RX_PC5_AF0
    {hal_ll_usart_module_num(USART_MODULE_3), PC5, USART3_BASE_ADDRESS, 0},
    #endif
    #ifdef USART3_RX_PD9_AF0
    {hal_ll_usart_module_num(USART_MODULE_3), PD9, USART3_BASE_ADDRESS, 0},
    #endif
    #ifdef USART4_RX_PA1_AF4
    {hal_ll_usart_module_num(USART_MODULE_4), PA1, USART4_BASE_ADDRESS, 4},
    #endif
    #ifdef USART4_RX_PC11_AF1
    {hal_ll_usart_module_num(USART_MODULE_4), PC11, USART4_BASE_ADDRESS, 1},
    #endif
    #ifdef USART4_RX_PE9_AF0
    {hal_ll_usart_module_num(USART_MODULE_4), PE9, USART4_BASE_ADDRESS, 0},
    #endif
    #ifdef USART5_RX_PB1_AF8
    {hal_ll_usart_module_num(USART_MODULE_5), PB1, USART5_BASE_ADDRESS, 8},
    #endif
    #ifdef USART5_RX_PB4_AF3
    {hal_ll_usart_module_num(USART_MODULE_5), PB4, USART5_BASE_ADDRESS, 3},
    #endif
    #ifdef USART5_RX_PD2_AF3
    {hal_ll_usart_module_num(USART_MODULE_5), PD2, USART5_BASE_ADDRESS, 3},
    #endif
    #ifdef USART6_RX_PA5_AF3
    {hal_ll_usart_module_num(USART_MODULE_6), PA5, USART6_BASE_ADDRESS, 3},
    #endif
    #ifdef USART6_RX_PB9_AF8
    {hal_ll_usart_module_num(USART_MODULE_6), PB9, USART6_BASE_ADDRESS, 8},
    #endif
    #ifdef USART6_RX_PC1_AF4
    {hal_ll_usart_module_num(USART_MODULE_6), PC1, USART6_BASE_ADDRESS, 4},
    #endif
    #ifdef USART5_RX_PE11_AF3
    {hal_ll_usart_module_num(USART_MODULE_5), PE11, USART5_BASE_ADDRESS, 3},
    #endif
    #ifdef USART6_RX_PF10_AF3
    {hal_ll_usart_module_num(USART_MODULE_6), PF10, USART6_BASE_ADDRESS, 3},
    #endif
    {HAL_LL_MODULE_ERROR, HAL_LL_PIN_NC, HAL_LL_MODULE_ERROR, HAL_LL_PIN_NC}
    //------------ END RX
};

#ifdef __cplusplus
}
#endif

#endif // _HAL_LL_UART_PIN_MAP_H_
// ------------------------------------------------------------------------- END
