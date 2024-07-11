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

/*!< @brief UART TX pins */
static const hal_ll_uart_pin_map_t hal_ll_uart_tx_map[] =
{
    #ifdef UART4_TX_PC10_AF5
    {hal_ll_uart_module_num(UART_MODULE_4), PC10, UART4_BASE_ADDRESS, 5},
    #endif
    #ifdef UART5_TX_PC12_AF5
    {hal_ll_uart_module_num(UART_MODULE_5), PC12, UART5_BASE_ADDRESS, 5},
    #endif
    #ifdef USART1_TX_PA9_AF7
    {hal_ll_usart_module_num(USART_MODULE_1), PA9, USART1_BASE_ADDRESS, 7},
    #endif
    #ifdef USART1_TX_PB6_AF7
    {hal_ll_usart_module_num(USART_MODULE_1), PB6, USART1_BASE_ADDRESS, 7},
    #endif
    #ifdef USART1_TX_PC4_AF7
    {hal_ll_usart_module_num(USART_MODULE_1), PC4, USART1_BASE_ADDRESS, 7},
    #endif
    #ifdef USART1_TX_PE0_AF7
    {hal_ll_usart_module_num(USART_MODULE_1), PE0, USART1_BASE_ADDRESS, 7},
    #endif
    #ifdef USART1_TX_PG9_AF7
    {hal_ll_usart_module_num(USART_MODULE_1), PG9, USART1_BASE_ADDRESS, 7},
    #endif
    #ifdef USART2_TX_PA14_AF7
    {hal_ll_usart_module_num(USART_MODULE_2), PA14, USART2_BASE_ADDRESS, 7},
    #endif
    #ifdef USART2_TX_PA2_AF7
    {hal_ll_usart_module_num(USART_MODULE_2), PA2, USART2_BASE_ADDRESS, 7},
    #endif
    #ifdef USART2_TX_PB3_AF7
    {hal_ll_usart_module_num(USART_MODULE_2), PB3, USART2_BASE_ADDRESS, 7},
    #endif
    #ifdef USART2_TX_PD5_AF7
    {hal_ll_usart_module_num(USART_MODULE_2), PD5, USART2_BASE_ADDRESS, 7},
    #endif
    #ifdef USART3_TX_PB10_AF7
    {hal_ll_usart_module_num(USART_MODULE_3), PB10, USART3_BASE_ADDRESS, 7},
    #endif
    #ifdef USART3_TX_PB9_AF7
    {hal_ll_usart_module_num(USART_MODULE_3), PB9, USART3_BASE_ADDRESS, 7},
    #endif
    #ifdef USART3_TX_PC10_AF7
    {hal_ll_usart_module_num(USART_MODULE_3), PC10, USART3_BASE_ADDRESS, 7},
    #endif
    #ifdef USART3_TX_PD8_AF7
    {hal_ll_usart_module_num(USART_MODULE_3), PD8, USART3_BASE_ADDRESS, 7},
    #endif
    {HAL_LL_MODULE_ERROR, HAL_LL_PIN_NC, HAL_LL_MODULE_ERROR, HAL_LL_PIN_NC}
    //------------ END TX
};

/*!< @brief UART RX pins */
static const hal_ll_uart_pin_map_t hal_ll_uart_rx_map[] =
{
    #ifdef UART4_RX_PC11_AF5
    {hal_ll_uart_module_num(UART_MODULE_4), PC11, UART4_BASE_ADDRESS, 5},
    #endif
    #ifdef UART5_RX_PD2_AF5
    {hal_ll_uart_module_num(UART_MODULE_5), PD2, UART5_BASE_ADDRESS, 5},
    #endif
    #ifdef USART1_RX_PA10_AF7
    {hal_ll_usart_module_num(USART_MODULE_1), PA10, USART1_BASE_ADDRESS, 7},
    #endif
    #ifdef USART1_RX_PB7_AF7
    {hal_ll_usart_module_num(USART_MODULE_1), PB7, USART1_BASE_ADDRESS, 7},
    #endif
    #ifdef USART1_RX_PC5_AF7
    {hal_ll_usart_module_num(USART_MODULE_1), PC5, USART1_BASE_ADDRESS, 7},
    #endif
    #ifdef USART1_RX_PE1_AF7
    {hal_ll_usart_module_num(USART_MODULE_1), PE1, USART1_BASE_ADDRESS, 7},
    #endif
    #ifdef USART2_RX_PA15_AF7
    {hal_ll_usart_module_num(USART_MODULE_2), PA15, USART2_BASE_ADDRESS, 7},
    #endif
    #ifdef USART2_RX_PA3_AF7
    {hal_ll_usart_module_num(USART_MODULE_2), PA3, USART2_BASE_ADDRESS, 7},
    #endif
    #ifdef USART2_RX_PB4_AF7
    {hal_ll_usart_module_num(USART_MODULE_2), PB4, USART2_BASE_ADDRESS, 7},
    #endif
    #ifdef USART2_RX_PD6_AF7
    {hal_ll_usart_module_num(USART_MODULE_2), PD6, USART2_BASE_ADDRESS, 7},
    #endif
    #ifdef USART3_RX_PB11_AF7
    {hal_ll_usart_module_num(USART_MODULE_3), PB11, USART3_BASE_ADDRESS, 7},
    #endif
    #ifdef USART3_RX_PB8_AF7
    {hal_ll_usart_module_num(USART_MODULE_3), PB8, USART3_BASE_ADDRESS, 7},
    #endif
    #ifdef USART3_RX_PC11_AF7
    {hal_ll_usart_module_num(USART_MODULE_3), PC11, USART3_BASE_ADDRESS, 7},
    #endif
    #ifdef USART3_RX_PD9_AF7
    {hal_ll_usart_module_num(USART_MODULE_3), PD9, USART3_BASE_ADDRESS, 7},
    #endif
    #ifdef USART3_RX_PE15_AF7
    {hal_ll_usart_module_num(USART_MODULE_3), PE15, USART3_BASE_ADDRESS, 7},
    #endif
    {HAL_LL_MODULE_ERROR, HAL_LL_PIN_NC, HAL_LL_MODULE_ERROR, HAL_LL_PIN_NC}
    //------------ END RX
};

#ifdef __cplusplus
}
#endif

#endif // _HAL_LL_UART_PIN_MAP_H_
// ------------------------------------------------------------------------- END
