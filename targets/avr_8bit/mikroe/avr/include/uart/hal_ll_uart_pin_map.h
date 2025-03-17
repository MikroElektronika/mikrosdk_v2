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
/*

  This file is part of mikroSDK.

  Copyright (c) ${COPYRIGHT_YEAR}, MikroElektronika - www.mikroe.com

  All rights reserved.

-------------------------------------------------------------------------- */
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

/*!< @brief Macro defining `weak` attribute */
#define __weak __attribute__((weak))

/*!< @brief Pin structure */
typedef struct {
    hal_ll_pin_name_t pin;
    uint8_t module_index;
    bool alternate;
} hal_ll_uart_pin_map_t;

/*!< @brief UART TX pins */
static const hal_ll_uart_pin_map_t hal_ll_uart_tx_map[] = {
    //------------ BEGIN TX
    #ifdef USART0_TXD_PE1
    {GPIO_PE1, hal_ll_uart_module_num(UART_MODULE_0), false},
    #endif
    #ifdef USART1_TXD_PD3
    {GPIO_PD3, hal_ll_uart_module_num(UART_MODULE_1), false},
    #endif
    #ifdef USART2_TXD_PH1
    {GPIO_PH1, hal_ll_uart_module_num(UART_MODULE_2), false},
    #endif
    #ifdef USART3_TXD_PJ1
    {GPIO_PJ1, hal_ll_uart_module_num(UART_MODULE_3), false},
    #endif
    #ifdef USART0_TXD_PD1
    {GPIO_PD1, hal_ll_uart_module_num(UART_MODULE_0), false},
    #endif
    #ifdef USART_TXD_PD1
    {GPIO_PD1, hal_ll_uart_module_num(UART_MODULE_0), false},
    #endif
    #ifdef USART2_TXD_PE3
    {GPIO_PE3, hal_ll_uart_module_num(UART_MODULE_2), false},
    #endif
    #ifdef USART1_TXD_PB3
    {GPIO_PB3, hal_ll_uart_module_num(UART_MODULE_1), false},
    #endif
    #ifdef USARTC0_TXD_PC3
    {GPIO_PC3, hal_ll_uart_module_num(UART_MODULE_C0), false},
    #endif
    #ifdef USARTC0_TXD_PC7_ALT
    {GPIO_PC7, hal_ll_uart_module_num(UART_MODULE_C0), true},
    #endif
    #ifdef USARTC1_TXD_PC7
    {GPIO_PC7, hal_ll_uart_module_num(UART_MODULE_C1), false},
    #endif
    #ifdef USARTD0_TXD_PD3
    {GPIO_PD3, hal_ll_uart_module_num(UART_MODULE_D0), false},
    #endif
    #ifdef USARTD1_TXD_PD7
    {GPIO_PD7, hal_ll_uart_module_num(UART_MODULE_D1), false},
    #endif
    #ifdef USARTE0_TXD_PE3
    {GPIO_PE3, hal_ll_uart_module_num(UART_MODULE_E0), false},
    #endif
    #ifdef USARTE1_TXD_PE7
    {GPIO_PE7, hal_ll_uart_module_num(UART_MODULE_E1), false},
    #endif
    #ifdef USARTF0_TXD_PF3
    {GPIO_PF3, hal_ll_uart_module_num(UART_MODULE_F0), false},
    #endif
    #ifdef USARTF1_TXD_PF7
    {GPIO_PF7, hal_ll_uart_module_num(UART_MODULE_F1), false},
    #endif
    #ifdef USARTD0_TXD_PD7_ALT
    {GPIO_PD7, hal_ll_uart_module_num(UART_MODULE_D0), true},
    #endif
    #ifdef USARTE0_TXD_PE7_ALT
    {GPIO_PE7, hal_ll_uart_module_num(UART_MODULE_E0), true},
    #endif
    #ifdef USARTF0_TXD_PF7_ALT
    {GPIO_PF7, hal_ll_uart_module_num(UART_MODULE_F0), true},
    #endif

    { HAL_LL_PIN_NC, HAL_LL_MODULE_ERROR, HAL_LL_PIN_NC }
    //------------ END TX
};

/*!< @brief UART RX pins */
static const hal_ll_uart_pin_map_t hal_ll_uart_rx_map[] = {
    //------------ BEGIN RX
    #ifdef USART0_RXD_PE0
    {GPIO_PE0, hal_ll_uart_module_num(UART_MODULE_0), false},
    #endif
    #ifdef USART1_RXD_PD2
    {GPIO_PD2, hal_ll_uart_module_num(UART_MODULE_1), false},
    #endif
    #ifdef USART2_RXD_PH0
    {GPIO_PH0, hal_ll_uart_module_num(UART_MODULE_2), false},
    #endif
    #ifdef USART3_RXD_PJ0
    {GPIO_PJ0, hal_ll_uart_module_num(UART_MODULE_3), false},
    #endif
    #ifdef USART0_RXD_PD0
    {GPIO_PD0, hal_ll_uart_module_num(UART_MODULE_0), false},
    #endif
    #ifdef USART_RXD_PD0
    {GPIO_PD0, hal_ll_uart_module_num(UART_MODULE_0), false},
    #endif
    #ifdef USART2_RXD_PE2
    {GPIO_PE2, hal_ll_uart_module_num(UART_MODULE_2), false},
    #endif
    #ifdef USART1_RXD_PB4
    {GPIO_PB4, hal_ll_uart_module_num(UART_MODULE_1), false},
    #endif
    #ifdef USARTC0_RXD_PC2
    {GPIO_PC2, hal_ll_uart_module_num(UART_MODULE_C0), false},
    #endif
    #ifdef USARTC0_RXD_PC6_ALT
    {GPIO_PC6, hal_ll_uart_module_num(UART_MODULE_C0), true},
    #endif
    #ifdef USARTC1_RXD_PC6
    {GPIO_PC6, hal_ll_uart_module_num(UART_MODULE_C1), false},
    #endif
    #ifdef USARTD0_RXD_PD2
    {GPIO_PD2, hal_ll_uart_module_num(UART_MODULE_D0), false},
    #endif
    #ifdef USARTD1_RXD_PD6
    {GPIO_PD6, hal_ll_uart_module_num(UART_MODULE_D1), false},
    #endif
    #ifdef USARTE0_RXD_PE2
    {GPIO_PE2, hal_ll_uart_module_num(UART_MODULE_E0), false},
    #endif
    #ifdef USARTE1_RXD_PE6
    {GPIO_PE6, hal_ll_uart_module_num(UART_MODULE_E1), false},
    #endif
    #ifdef USARTF0_RXD_PF2
    {GPIO_PF2, hal_ll_uart_module_num(UART_MODULE_F0), false},
    #endif
    #ifdef USARTF1_RXD_PF6
    {GPIO_PF6, hal_ll_uart_module_num(UART_MODULE_F1), false},
    #endif
    #ifdef USARTD0_RXD_PD6_ALT
    {GPIO_PD6, hal_ll_uart_module_num(UART_MODULE_D0), true},
    #endif
    #ifdef USARTE0_RXD_PE6_ALT
    {GPIO_PE6, hal_ll_uart_module_num(UART_MODULE_E0), true},
    #endif
    #ifdef USARTF0_RXD_PF6_ALT
    {GPIO_PF6, hal_ll_uart_module_num(UART_MODULE_F0), true},
    #endif

    { HAL_LL_PIN_NC, HAL_LL_MODULE_ERROR, HAL_LL_PIN_NC }
    //------------ END RX
};

#ifdef __cplusplus
}
#endif

#endif // _HAL_LL_UART_PIN_MAP_H_
// ---------------------------------------------------------------------- END
