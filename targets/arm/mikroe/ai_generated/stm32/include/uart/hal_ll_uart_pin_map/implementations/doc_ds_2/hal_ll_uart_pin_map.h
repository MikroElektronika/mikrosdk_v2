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

/*!< @brief UART TX pins */
static const hal_ll_uart_pin_map_t hal_ll_uart_tx_map[] =
{
    #ifdef USART1_TX_PA0_AF4
    {hal_ll_usart_module_num(USART_MODULE_1), PA0, USART1_BASE_ADDRESS, 4},
    #endif
    #ifdef USART1_TX_PB6_AF0
    {hal_ll_usart_module_num(USART_MODULE_1), PB6, USART1_BASE_ADDRESS, 0},
    #endif
    #ifdef USART1_TX_PC14_AF0
    {hal_ll_usart_module_num(USART_MODULE_1), PC14, USART1_BASE_ADDRESS, 0},
    #endif
    #ifdef USART2_TX_PA14_AF1
    {hal_ll_usart_module_num(USART_MODULE_2), PA14, USART2_BASE_ADDRESS, 1},
    #endif
    #ifdef USART2_TX_PA2_AF1
    {hal_ll_usart_module_num(USART_MODULE_2), PA2, USART2_BASE_ADDRESS, 1},
    #endif
    #ifdef USART2_TX_PA4_AF1
    {hal_ll_usart_module_num(USART_MODULE_2), PA4, USART2_BASE_ADDRESS, 1},
    #endif
    #ifdef USART2_TX_PA8_AF1
    {hal_ll_usart_module_num(USART_MODULE_2), PA8, USART2_BASE_ADDRESS, 1},
    #endif
    #ifdef USART1_TX_PA9_AF1
    {hal_ll_usart_module_num(USART_MODULE_1), PA9, USART1_BASE_ADDRESS, 1},
    #endif
    {HAL_LL_MODULE_ERROR, HAL_LL_PIN_NC, HAL_LL_MODULE_ERROR, HAL_LL_PIN_NC}
    //------------ END TX
};

/*!< @brief UART RX pins */
static const hal_ll_uart_pin_map_t hal_ll_uart_rx_map[] =
{
    #ifdef USART1_RX_PA1_AF4
    {hal_ll_usart_module_num(USART_MODULE_1), PA1, USART1_BASE_ADDRESS, 4},
    #endif
    #ifdef USART1_RX_PA8_AF14
    {hal_ll_usart_module_num(USART_MODULE_1), PA8, USART1_BASE_ADDRESS, 14},
    #endif
    #ifdef USART1_RX_PB7_AF0
    {hal_ll_usart_module_num(USART_MODULE_1), PB7, USART1_BASE_ADDRESS, 0},
    #endif
    #ifdef USART2_RX_PA13_AF4
    {hal_ll_usart_module_num(USART_MODULE_2), PA13, USART2_BASE_ADDRESS, 4},
    #endif
    #ifdef USART2_RX_PA14_AF9
    {hal_ll_usart_module_num(USART_MODULE_2), PA14, USART2_BASE_ADDRESS, 9},
    #endif
    #ifdef USART2_RX_PA15_AF1
    {hal_ll_usart_module_num(USART_MODULE_2), PA15, USART2_BASE_ADDRESS, 1},
    #endif
    #ifdef USART2_RX_PA3_AF1
    {hal_ll_usart_module_num(USART_MODULE_2), PA3, USART2_BASE_ADDRESS, 1},
    #endif
    #ifdef USART2_RX_PA5_AF1
    {hal_ll_usart_module_num(USART_MODULE_2), PA5, USART2_BASE_ADDRESS, 1},
    #endif
    #ifdef USART1_RX_PA10_AF1
    {hal_ll_usart_module_num(USART_MODULE_1), PA10, USART1_BASE_ADDRESS, 1},
    #endif
    #ifdef USART1_RX_PB2_AF0
    {hal_ll_usart_module_num(USART_MODULE_1), PB2, USART1_BASE_ADDRESS, 0},
    #endif
    {HAL_LL_MODULE_ERROR, HAL_LL_PIN_NC, HAL_LL_MODULE_ERROR, HAL_LL_PIN_NC}
    //------------ END RX
};

#ifdef __cplusplus
}
#endif

#endif // _HAL_LL_UART_PIN_MAP_H_
// ------------------------------------------------------------------------- END
