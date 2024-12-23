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
#define hal_ll_usart_module_num(_module_num) (_module_num)
#define hal_ll_uart_module_num(_module_num) (_module_num + USART_MODULE_COUNT)

/*!< @brief Pin structure */
typedef struct
{
    uint8_t module_index;
    hal_ll_pin_name_t pin;
    hal_ll_base_addr_t base;
    uint8_t af;
} hal_ll_uart_pin_map_t;

#ifdef USART_MODULE_0
#define HAL_LL_USART0_BASE_ADDRESS 0x40024000UL
#endif
#ifdef USART_MODULE_1
#define HAL_LL_USART1_BASE_ADDRESS 0x40028000UL
#endif
#ifdef USART_MODULE_2
#define HAL_LL_USART2_BASE_ADDRESS 0x4002C000UL
#endif
#ifdef UART_MODULE_0
#define HAL_LL_UART0_BASE_ADDRESS 0x400E0800UL
#endif
#ifdef UART_MODULE_1
#define HAL_LL_UART1_BASE_ADDRESS 0x400E0A00UL
#endif
#ifdef UART_MODULE_2
#define HAL_LL_UART2_BASE_ADDRESS 0x400E1A00UL
#endif
#ifdef UART_MODULE_3
#define HAL_LL_UART3_BASE_ADDRESS 0x400E1C00UL
#endif
#ifdef UART_MODULE_4
#define HAL_LL_UART4_BASE_ADDRESS 0x400E1E00UL
#endif

/*!< @brief UART TX pins */
static const hal_ll_uart_pin_map_t hal_ll_uart_tx_map[] =
{
    #ifdef USART0_TX_PB1_AFC
    {hal_ll_usart_module_num(USART_MODULE_0), GPIO_PB1, HAL_LL_USART0_BASE_ADDRESS, 2},
    #endif
    #ifdef USART1_TX_PB4_AFD
    {hal_ll_usart_module_num(USART_MODULE_1), GPIO_PB4, HAL_LL_USART1_BASE_ADDRESS, 3},
    #endif
    #ifdef USART2_TX_PD16_AFB
    {hal_ll_usart_module_num(USART_MODULE_2), GPIO_PD16, HAL_LL_USART2_BASE_ADDRESS, 1},
    #endif
    #ifdef UART0_TX_PA10_AFA
    {hal_ll_uart_module_num(UART_MODULE_0), GPIO_PA10, HAL_LL_UART0_BASE_ADDRESS, 0},
    #endif
    #ifdef UART1_TX_PA4_AFC
    {hal_ll_uart_module_num(UART_MODULE_1), GPIO_PA4, HAL_LL_UART1_BASE_ADDRESS, 2},
    #endif
    #ifdef UART1_TX_PA6_AFC
    {hal_ll_uart_module_num(UART_MODULE_1), GPIO_PA6, HAL_LL_UART1_BASE_ADDRESS, 2},
    #endif
    #ifdef UART1_TX_PD26_AFD
    {hal_ll_uart_module_num(UART_MODULE_1), GPIO_PD26, HAL_LL_UART1_BASE_ADDRESS, 3},
    #endif
    #ifdef UART2_TX_PD26_AFC
    {hal_ll_uart_module_num(UART_MODULE_2), GPIO_PD26, HAL_LL_UART2_BASE_ADDRESS, 2},
    #endif
    #ifdef UART3_TX_PD30_AFA
    {hal_ll_uart_module_num(UART_MODULE_3), GPIO_PD30, HAL_LL_UART3_BASE_ADDRESS, 0},
    #endif
    #ifdef UART3_TX_PD31_AFB
    {hal_ll_uart_module_num(UART_MODULE_3), GPIO_PD31, HAL_LL_UART3_BASE_ADDRESS, 1},
    #endif
    #ifdef UART4_TX_PD3_AFC
    {hal_ll_uart_module_num(UART_MODULE_4), GPIO_PD3, HAL_LL_UART4_BASE_ADDRESS, 2},
    #endif
    #ifdef UART4_TX_PD19_AFC
    {hal_ll_uart_module_num(UART_MODULE_4), GPIO_PD19, HAL_LL_UART4_BASE_ADDRESS, 2},
    #endif

    {HAL_LL_MODULE_ERROR, HAL_LL_PIN_NC, HAL_LL_MODULE_ERROR, HAL_LL_PIN_NC}
};

/*!< @brief UART RX pins */
static const hal_ll_uart_pin_map_t hal_ll_uart_rx_map[] =
{
    #ifdef USART0_RX_PB0_AFC
    {hal_ll_usart_module_num(USART_MODULE_0), GPIO_PB0, HAL_LL_USART0_BASE_ADDRESS, 2},
    #endif
    #ifdef USART1_RX_PA21_AFA
    {hal_ll_usart_module_num(USART_MODULE_1), GPIO_PA21, HAL_LL_USART1_BASE_ADDRESS, 0},
    #endif
    #ifdef USART2_RX_PD15_AFB
    {hal_ll_usart_module_num(USART_MODULE_2), GPIO_PD15, HAL_LL_USART2_BASE_ADDRESS, 1},
    #endif
    #ifdef UART0_RX_PA9_AFA
    {hal_ll_uart_module_num(UART_MODULE_0), GPIO_PA9, HAL_LL_UART0_BASE_ADDRESS, 0},
    #endif
    #ifdef UART1_RX_PA5_AFC
    {hal_ll_uart_module_num(UART_MODULE_1), GPIO_PA5, HAL_LL_UART1_BASE_ADDRESS, 2},
    #endif
    #ifdef UART2_RX_PD25_AFC
    {hal_ll_uart_module_num(UART_MODULE_2), GPIO_PD25, HAL_LL_UART2_BASE_ADDRESS, 2},
    #endif
    #ifdef UART3_RX_PD28_AFA
    {hal_ll_uart_module_num(UART_MODULE_3), GPIO_PD28, HAL_LL_UART3_BASE_ADDRESS, 0},
    #endif
    #ifdef UART4_RX_PD18_AFC
    {hal_ll_uart_module_num(UART_MODULE_4), GPIO_PD18, HAL_LL_UART4_BASE_ADDRESS, 2},
    #endif

    {HAL_LL_MODULE_ERROR, HAL_LL_PIN_NC, HAL_LL_MODULE_ERROR, HAL_LL_PIN_NC}
};

#ifdef __cplusplus
}
#endif

#endif // _HAL_LL_UART_PIN_MAP_H_
// ------------------------------------------------------------------------- END
