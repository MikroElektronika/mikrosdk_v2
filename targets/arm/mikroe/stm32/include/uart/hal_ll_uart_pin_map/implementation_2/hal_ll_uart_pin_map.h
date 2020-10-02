/****************************************************************************
**
** Copyright (C) 2020 MikroElektronika d.o.o.
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

/*!< @brief Helper macro for getting adequate module index number */
#define hal_ll_uart_module_num(_module_num) (_module_num - 1)

/*!< @brief Macro defining `weak` attribute */
#define __weak __attribute__((weak))

/*!< @brief UART module base addresses */
#ifdef UART_MODULE_1
#if defined(STM32F7xx) || defined(STM32H7xx)
static const hal_ll_base_addr_t HAL_LL_UART1_BASE_ADDRESS = 0x40011000;
#elif defined(STM32F3xx) || defined(STM32L4xx) || defined(STM32G0xx) || \
      defined(STM32L0xx) || defined(STM32F0xx)
static const hal_ll_base_addr_t HAL_LL_UART1_BASE_ADDRESS = 0x40013800;
#endif
#endif
#ifdef UART_MODULE_2
static const hal_ll_base_addr_t HAL_LL_UART2_BASE_ADDRESS = 0x40004400;
#endif
#ifdef UART_MODULE_3
static const hal_ll_base_addr_t HAL_LL_UART3_BASE_ADDRESS = 0x40004800;
#endif
#ifdef UART_MODULE_4
static const hal_ll_base_addr_t HAL_LL_UART4_BASE_ADDRESS = 0x40004C00;
#endif
#ifdef UART_MODULE_5
static const hal_ll_base_addr_t HAL_LL_UART5_BASE_ADDRESS = 0x40005000;
#endif
#ifdef UART_MODULE_6
static const hal_ll_base_addr_t HAL_LL_UART6_BASE_ADDRESS = 0x40011400;
#endif
#ifdef UART_MODULE_7
#if defined(STM32F7xx) || defined(STM32H7xx)
static const hal_ll_base_addr_t HAL_LL_UART7_BASE_ADDRESS = 0x40007800;
#elif defined(STM32F0xx)
static const hal_ll_base_addr_t HAL_LL_UART7_BASE_ADDRESS = 0x40011800;
#endif
#endif
#ifdef UART_MODULE_8
#if defined(STM32F7xx) || defined(STM32H7xx)
static const hal_ll_base_addr_t HAL_LL_UART8_BASE_ADDRESS = 0x40007C00;
#elif defined(STM32F0xx)
static const hal_ll_base_addr_t HAL_LL_UART8_BASE_ADDRESS = 0x40011C00;
#endif
#endif

/*!< @brief UART module alternate function values */
#ifdef UART_MODULE_1
static const uint8_t HAL_LL_UART1_GPIO_AF0 = 0;
static const uint8_t HAL_LL_UART1_GPIO_AF1 = 1;
static const uint8_t HAL_LL_UART1_GPIO_AF4 = 4;
static const uint8_t HAL_LL_UART1_GPIO_AF7 = 7;
#endif
#ifdef UART_MODULE_2
static const uint8_t HAL_LL_UART2_GPIO_AF0 = 0;
static const uint8_t HAL_LL_UART2_GPIO_AF1 = 1;
static const uint8_t HAL_LL_UART2_GPIO_AF3 = 3;
static const uint8_t HAL_LL_UART2_GPIO_AF4 = 4;
static const uint8_t HAL_LL_UART2_GPIO_AF7 = 7;
#endif
#ifdef UART_MODULE_3
static const uint8_t HAL_LL_UART3_GPIO_AF0 = 0;
static const uint8_t HAL_LL_UART3_GPIO_AF1 = 1;
static const uint8_t HAL_LL_UART3_GPIO_AF4 = 4;
static const uint8_t HAL_LL_UART3_GPIO_AF7 = 7;
#endif
#ifdef UART_MODULE_4
static const uint8_t HAL_LL_UART4_GPIO_AF0 = 0;
static const uint8_t HAL_LL_UART4_GPIO_AF1 = 1;
static const uint8_t HAL_LL_UART4_GPIO_AF4 = 4;
static const uint8_t HAL_LL_UART4_GPIO_AF5 = 5;
static const uint8_t HAL_LL_UART4_GPIO_AF6 = 6;
static const uint8_t HAL_LL_UART4_GPIO_AF8 = 8;
#endif
#ifdef UART_MODULE_5
static const uint8_t HAL_LL_UART5_GPIO_AF1 = 1;
static const uint8_t HAL_LL_UART5_GPIO_AF2 = 2;
static const uint8_t HAL_LL_UART5_GPIO_AF4 = 4;
static const uint8_t HAL_LL_UART5_GPIO_AF5 = 5;
static const uint8_t HAL_LL_UART5_GPIO_AF6 = 6;
static const uint8_t HAL_LL_UART5_GPIO_AF7 = 7;
static const uint8_t HAL_LL_UART5_GPIO_AF8 = 8;
static const uint8_t HAL_LL_UART5_GPIO_AF14 = 14;
#endif
#ifdef UART_MODULE_6
static const uint8_t HAL_LL_UART6_GPIO_AF1 = 1;
static const uint8_t HAL_LL_UART6_GPIO_AF2 = 2;
static const uint8_t HAL_LL_UART6_GPIO_AF5 = 5;
static const uint8_t HAL_LL_UART6_GPIO_AF7 = 7;
static const uint8_t HAL_LL_UART6_GPIO_AF8 = 8;
#endif
#ifdef UART_MODULE_7
static const uint8_t HAL_LL_UART7_GPIO_AF1 = 1;
static const uint8_t HAL_LL_UART7_GPIO_AF7 = 7;
static const uint8_t HAL_LL_UART7_GPIO_AF8 = 8;
static const uint8_t HAL_LL_UART7_GPIO_AF11 = 11;
static const uint8_t HAL_LL_UART7_GPIO_AF12 = 12;
#endif
#ifdef UART_MODULE_8
static const uint8_t HAL_LL_UART8_GPIO_AF0 = 0;
static const uint8_t HAL_LL_UART8_GPIO_AF1 = 1;
static const uint8_t HAL_LL_UART8_GPIO_AF2 = 2;
static const uint8_t HAL_LL_UART8_GPIO_AF8 = 8;
#endif

/*!< @brief Pin structure */
typedef struct
{
    uint8_t module_index;
    hal_ll_pin_name_t pin;
    hal_ll_base_addr_t base;
    uint8_t af;
} hal_ll_uart_pin_map_t;

/*!< @brief UART TX pins */
__weak static const hal_ll_uart_pin_map_t hal_ll_uart_tx_map[] =
{
    //------------ BEGIN TX
    #ifdef UART_MODULE_1
    #ifdef UART1_TX_PA2_AF1
    {hal_ll_uart_module_num(UART_MODULE_1), PA2, HAL_LL_UART1_BASE_ADDRESS, HAL_LL_UART1_GPIO_AF1},
    #endif
    #ifdef UART1_TX_PA9_AF1
    {hal_ll_uart_module_num(UART_MODULE_1), PA9, HAL_LL_UART1_BASE_ADDRESS, HAL_LL_UART1_GPIO_AF1},
    #endif
    #ifdef UART1_TX_PA9_AF4
    {hal_ll_uart_module_num(UART_MODULE_1), PA9, HAL_LL_UART1_BASE_ADDRESS, HAL_LL_UART1_GPIO_AF4},
    #endif
    #ifdef UART1_TX_PA9_AF7
    {hal_ll_uart_module_num(UART_MODULE_1), PA9, HAL_LL_UART1_BASE_ADDRESS, HAL_LL_UART1_GPIO_AF7},
    #endif
    #ifdef UART1_TX_PA14_AF1
    {hal_ll_uart_module_num(UART_MODULE_1), PA14, HAL_LL_UART1_BASE_ADDRESS, HAL_LL_UART1_GPIO_AF1},
    #endif
    #ifdef UART1_TX_PB6_AF0
    {hal_ll_uart_module_num(UART_MODULE_1), PB6, HAL_LL_UART1_BASE_ADDRESS, HAL_LL_UART1_GPIO_AF0},
    #endif
    #ifdef UART1_TX_PB6_AF1
    {hal_ll_uart_module_num(UART_MODULE_1), PB6, HAL_LL_UART1_BASE_ADDRESS, HAL_LL_UART1_GPIO_AF1},
    #endif
    #ifdef UART1_TX_PB6_AF4
    {hal_ll_uart_module_num(UART_MODULE_1), PB6, HAL_LL_UART1_BASE_ADDRESS, HAL_LL_UART1_GPIO_AF4},
    #endif
    #ifdef UART1_TX_PB6_AF7
    {hal_ll_uart_module_num(UART_MODULE_1), PB6, HAL_LL_UART1_BASE_ADDRESS, HAL_LL_UART1_GPIO_AF7},
    #endif
    #ifdef UART1_TX_PB14_AF4
    {hal_ll_uart_module_num(UART_MODULE_1), PB14, HAL_LL_UART1_BASE_ADDRESS, HAL_LL_UART1_GPIO_AF4},
    #endif
    #ifdef UART1_TX_PC4_AF1
    {hal_ll_uart_module_num(UART_MODULE_1), PC4, HAL_LL_UART1_BASE_ADDRESS, HAL_LL_UART1_GPIO_AF1},
    #endif
    #ifdef UART1_TX_PC4_AF7
    {hal_ll_uart_module_num(UART_MODULE_1), PC4, HAL_LL_UART1_BASE_ADDRESS, HAL_LL_UART1_GPIO_AF7},
    #endif
    #ifdef UART1_TX_PE0_AF7
    {hal_ll_uart_module_num(UART_MODULE_1), PE0, HAL_LL_UART1_BASE_ADDRESS, HAL_LL_UART1_GPIO_AF7},
    #endif
    #ifdef UART1_TX_PG9_AF7
    {hal_ll_uart_module_num(UART_MODULE_1), PG9, HAL_LL_UART1_BASE_ADDRESS, HAL_LL_UART1_GPIO_AF7},
    #endif
    #endif

    #ifdef UART_MODULE_2
    #ifdef UART2_TX_PA2_AF1
    {hal_ll_uart_module_num(UART_MODULE_2), PA2, HAL_LL_UART2_BASE_ADDRESS, HAL_LL_UART2_GPIO_AF1},
    #endif
    #ifdef UART2_TX_PA2_AF4
    {hal_ll_uart_module_num(UART_MODULE_2), PA2, HAL_LL_UART2_BASE_ADDRESS, HAL_LL_UART2_GPIO_AF4},
    #endif
    #ifdef UART2_TX_PA9_AF4
    {hal_ll_uart_module_num(UART_MODULE_2), PA9, HAL_LL_UART2_BASE_ADDRESS, HAL_LL_UART2_GPIO_AF4},
    #endif
    #ifdef UART2_TX_PA2_AF7
    {hal_ll_uart_module_num(UART_MODULE_2), PA2, HAL_LL_UART2_BASE_ADDRESS, HAL_LL_UART2_GPIO_AF7},
    #endif
    #ifdef UART2_TX_PA14_AF1
    {hal_ll_uart_module_num(UART_MODULE_2), PA14, HAL_LL_UART2_BASE_ADDRESS, HAL_LL_UART2_GPIO_AF1},
    #endif
    #ifdef UART2_TX_PA14_AF4
    {hal_ll_uart_module_num(UART_MODULE_2), PA14, HAL_LL_UART2_BASE_ADDRESS, HAL_LL_UART2_GPIO_AF4},
    #endif
    #ifdef UART2_TX_PA14_AF7
    {hal_ll_uart_module_num(UART_MODULE_2), PA14, HAL_LL_UART2_BASE_ADDRESS, HAL_LL_UART2_GPIO_AF7},
    #endif
    #ifdef UART2_TX_PB3_AF7
    {hal_ll_uart_module_num(UART_MODULE_2), PB3, HAL_LL_UART2_BASE_ADDRESS, HAL_LL_UART2_GPIO_AF7},
    #endif
    #ifdef UART2_TX_PB6_AF0
    {hal_ll_uart_module_num(UART_MODULE_2), PB6, HAL_LL_UART2_BASE_ADDRESS, HAL_LL_UART2_GPIO_AF0},
    #endif
    #ifdef UART2_TX_PB8_AF0
    {hal_ll_uart_module_num(UART_MODULE_2), PB8, HAL_LL_UART2_BASE_ADDRESS, HAL_LL_UART2_GPIO_AF0},
    #endif
    #ifdef UART2_TX_PD5_AF0
    {hal_ll_uart_module_num(UART_MODULE_2), PD5, HAL_LL_UART2_BASE_ADDRESS, HAL_LL_UART2_GPIO_AF0},
    #endif
    #ifdef UART2_TX_PD5_AF1
    {hal_ll_uart_module_num(UART_MODULE_2), PD5, HAL_LL_UART2_BASE_ADDRESS, HAL_LL_UART2_GPIO_AF1},
    #endif
    #ifdef UART2_TX_PD5_AF4
    {hal_ll_uart_module_num(UART_MODULE_2), PD5, HAL_LL_UART2_BASE_ADDRESS, HAL_LL_UART2_GPIO_AF4},
    #endif
    #ifdef UART2_TX_PD5_AF7
    {hal_ll_uart_module_num(UART_MODULE_2), PD5, HAL_LL_UART2_BASE_ADDRESS, HAL_LL_UART2_GPIO_AF7},
    #endif
    #endif

    #ifdef UART_MODULE_3
    #ifdef UART3_TX_PA5_AF4
    {hal_ll_uart_module_num(UART_MODULE_3), PA5, HAL_LL_UART3_BASE_ADDRESS, HAL_LL_UART3_GPIO_AF4},
    #endif
    #ifdef UART3_TX_PB2_AF4
    {hal_ll_uart_module_num(UART_MODULE_3), PB2, HAL_LL_UART3_BASE_ADDRESS, HAL_LL_UART3_GPIO_AF4},
    #endif
    #ifdef UART3_TX_PB8_AF4
    {hal_ll_uart_module_num(UART_MODULE_3), PB8, HAL_LL_UART3_BASE_ADDRESS, HAL_LL_UART3_GPIO_AF4},
    #endif
    #ifdef UART3_TX_PB8_AF7
    {hal_ll_uart_module_num(UART_MODULE_3), PB8, HAL_LL_UART3_BASE_ADDRESS, HAL_LL_UART3_GPIO_AF7},
    #endif
    #ifdef UART3_TX_PB9_AF7
    {hal_ll_uart_module_num(UART_MODULE_3), PB9, HAL_LL_UART3_BASE_ADDRESS, HAL_LL_UART3_GPIO_AF7},
    #endif
    #ifdef UART3_TX_PB10_AF4
    {hal_ll_uart_module_num(UART_MODULE_3), PB10, HAL_LL_UART3_BASE_ADDRESS, HAL_LL_UART3_GPIO_AF4},
    #endif
    #ifdef UART3_TX_PB10_AF7
    {hal_ll_uart_module_num(UART_MODULE_3), PB10, HAL_LL_UART3_BASE_ADDRESS, HAL_LL_UART3_GPIO_AF7},
    #endif
    #ifdef UART3_TX_PC4_AF0
    {hal_ll_uart_module_num(UART_MODULE_3), PC4, HAL_LL_UART3_BASE_ADDRESS, HAL_LL_UART1_GPIO_AF0},
    #endif
    #ifdef UART3_TX_PC4_AF1
    {hal_ll_uart_module_num(UART_MODULE_3), PC4, HAL_LL_UART3_BASE_ADDRESS, HAL_LL_UART3_GPIO_AF1},
    #endif
    #ifdef UART3_TX_PC4_AF4
    {hal_ll_uart_module_num(UART_MODULE_3), PC4, HAL_LL_UART3_BASE_ADDRESS, HAL_LL_UART1_GPIO_AF4},
    #endif
    #ifdef UART3_TX_PC4_AF7
    {hal_ll_uart_module_num(UART_MODULE_3), PC4, HAL_LL_UART3_BASE_ADDRESS, HAL_LL_UART1_GPIO_AF7},
    #endif
    #ifdef UART3_TX_PC10_AF0
    {hal_ll_uart_module_num(UART_MODULE_3), PC10, HAL_LL_UART3_BASE_ADDRESS, HAL_LL_UART3_GPIO_AF0},
    #endif
    #ifdef UART3_TX_PC10_AF1
    {hal_ll_uart_module_num(UART_MODULE_3), PC10, HAL_LL_UART3_BASE_ADDRESS, HAL_LL_UART3_GPIO_AF1},
    #endif
    #ifdef UART3_TX_PC10_AF4
    {hal_ll_uart_module_num(UART_MODULE_3), PC10, HAL_LL_UART3_BASE_ADDRESS, HAL_LL_UART3_GPIO_AF4},
    #endif
    #ifdef UART3_TX_PC10_AF7
    {hal_ll_uart_module_num(UART_MODULE_3), PC10, HAL_LL_UART3_BASE_ADDRESS, HAL_LL_UART3_GPIO_AF7},
    #endif
    #ifdef UART3_TX_PD8_AF0
    {hal_ll_uart_module_num(UART_MODULE_3), PD8, HAL_LL_UART3_BASE_ADDRESS, HAL_LL_UART3_GPIO_AF0},
    #endif
    #ifdef UART3_TX_PD8_AF4
    {hal_ll_uart_module_num(UART_MODULE_3), PD8, HAL_LL_UART3_BASE_ADDRESS, HAL_LL_UART3_GPIO_AF4},
    #endif
    #ifdef UART3_TX_PD8_AF7
    {hal_ll_uart_module_num(UART_MODULE_3), PD8, HAL_LL_UART3_BASE_ADDRESS, HAL_LL_UART3_GPIO_AF7},
    #endif
    #endif

    #ifdef UART_MODULE_4
    #ifdef UART4_TX_PA0_AF4
    {hal_ll_uart_module_num(UART_MODULE_4), PA0, HAL_LL_UART4_BASE_ADDRESS, HAL_LL_UART4_GPIO_AF4},
    #endif
    #ifdef UART4_TX_PA0_AF6
    {hal_ll_uart_module_num(UART_MODULE_4), PA0, HAL_LL_UART4_BASE_ADDRESS, HAL_LL_UART4_GPIO_AF6},
    #endif
    #ifdef UART4_TX_PA0_AF8
    {hal_ll_uart_module_num(UART_MODULE_4), PA0, HAL_LL_UART4_BASE_ADDRESS, HAL_LL_UART4_GPIO_AF8},
    #endif
    #ifdef UART4_TX_PA12_AF6
    {hal_ll_uart_module_num(UART_MODULE_4), PA12, HAL_LL_UART4_BASE_ADDRESS, HAL_LL_UART4_GPIO_AF6},
    #endif
    #ifdef UART4_TX_PB9_AF8
    {hal_ll_uart_module_num(UART_MODULE_4), PB9, HAL_LL_UART4_BASE_ADDRESS, HAL_LL_UART4_GPIO_AF8},
    #endif
    #ifdef UART4_TX_PC10_AF0
    {hal_ll_uart_module_num(UART_MODULE_4), PC10, HAL_LL_UART4_BASE_ADDRESS, HAL_LL_UART4_GPIO_AF0},
    #endif
    #ifdef UART4_TX_PC10_AF1
    {hal_ll_uart_module_num(UART_MODULE_4), PC10, HAL_LL_UART4_BASE_ADDRESS, HAL_LL_UART4_GPIO_AF1},
    #endif
    #ifdef UART4_TX_PC10_AF5
    {hal_ll_uart_module_num(UART_MODULE_4), PC10, HAL_LL_UART4_BASE_ADDRESS, HAL_LL_UART4_GPIO_AF5},
    #endif
    #ifdef UART4_TX_PC10_AF6
    {hal_ll_uart_module_num(UART_MODULE_4), PC10, HAL_LL_UART4_BASE_ADDRESS, HAL_LL_UART4_GPIO_AF6},
    #endif
    #ifdef UART4_TX_PC10_AF8
    {hal_ll_uart_module_num(UART_MODULE_4), PC10, HAL_LL_UART4_BASE_ADDRESS, HAL_LL_UART4_GPIO_AF8},
    #endif
    #ifdef UART4_TX_PD1_AF8
    {hal_ll_uart_module_num(UART_MODULE_4), PD1, HAL_LL_UART4_BASE_ADDRESS, HAL_LL_UART4_GPIO_AF8},
    #endif
    #ifdef UART4_TX_PE8_AF1
    {hal_ll_uart_module_num(UART_MODULE_4), PE8, HAL_LL_UART4_BASE_ADDRESS, HAL_LL_UART4_GPIO_AF1},
    #endif
    #ifdef UART4_TX_PE8_AF4
    {hal_ll_uart_module_num(UART_MODULE_4), PE8, HAL_LL_UART4_BASE_ADDRESS, HAL_LL_UART4_GPIO_AF4},
    #endif
    #ifdef UART4_TX_PE8_AF6
    {hal_ll_uart_module_num(UART_MODULE_4), PE8, HAL_LL_UART4_BASE_ADDRESS, HAL_LL_UART4_GPIO_AF6},
    #endif
    #ifdef UART4_TX_PH13_AF8
    {hal_ll_uart_module_num(UART_MODULE_4), PH13, HAL_LL_UART4_BASE_ADDRESS, HAL_LL_UART4_GPIO_AF8},
    #endif
    #endif

    #ifdef UART_MODULE_5
    #ifdef UART5_TX_PB3_AF4
    {hal_ll_uart_module_num(UART_MODULE_5), PB3, HAL_LL_UART5_BASE_ADDRESS, HAL_LL_UART5_GPIO_AF4},
    #endif
    #ifdef UART5_TX_PB3_AF6
    {hal_ll_uart_module_num(UART_MODULE_5), PB3, HAL_LL_UART5_BASE_ADDRESS, HAL_LL_UART5_GPIO_AF6},
    #endif
    #ifdef UART5_TX_PB6_AF1
    {hal_ll_uart_module_num(UART_MODULE_5), PB6, HAL_LL_UART5_BASE_ADDRESS, HAL_LL_UART5_GPIO_AF1},
    #endif
    #ifdef UART5_TX_PB6_AF14
    {hal_ll_uart_module_num(UART_MODULE_5), PB6, HAL_LL_UART5_BASE_ADDRESS, HAL_LL_UART5_GPIO_AF14},
    #endif
    #ifdef UART5_TX_PB9_AF7
    {hal_ll_uart_module_num(UART_MODULE_5), PB9, HAL_LL_UART5_BASE_ADDRESS, HAL_LL_UART5_GPIO_AF7},
    #endif
    #ifdef UART5_TX_PB13_AF8
    {hal_ll_uart_module_num(UART_MODULE_5), PB13, HAL_LL_UART5_BASE_ADDRESS, HAL_LL_UART5_GPIO_AF8},
    #endif
    #ifdef UART5_TX_PB13_AF14
    {hal_ll_uart_module_num(UART_MODULE_5), PB13, HAL_LL_UART5_BASE_ADDRESS, HAL_LL_UART5_GPIO_AF14},
    #endif
    #ifdef UART5_TX_PC12_AF2
    {hal_ll_uart_module_num(UART_MODULE_5), PC12, HAL_LL_UART5_BASE_ADDRESS, HAL_LL_UART5_GPIO_AF2},
    #endif
    #ifdef UART5_TX_PC12_AF4
    {hal_ll_uart_module_num(UART_MODULE_5), PC12, HAL_LL_UART5_BASE_ADDRESS, HAL_LL_UART5_GPIO_AF4},
    #endif
    #ifdef UART5_TX_PC12_AF5
    {hal_ll_uart_module_num(UART_MODULE_5), PC12, HAL_LL_UART5_BASE_ADDRESS, HAL_LL_UART5_GPIO_AF5},
    #endif
    #ifdef UART5_TX_PC12_AF8
    {hal_ll_uart_module_num(UART_MODULE_5), PC12, HAL_LL_UART5_BASE_ADDRESS, HAL_LL_UART5_GPIO_AF8},
    #endif
    #ifdef UART5_TX_PE10_AF1
    {hal_ll_uart_module_num(UART_MODULE_5), PE10, HAL_LL_UART5_BASE_ADDRESS, HAL_LL_UART5_GPIO_AF1},
    #endif
    #ifdef UART5_TX_PE10_AF4
    {hal_ll_uart_module_num(UART_MODULE_5), PE10, HAL_LL_UART5_BASE_ADDRESS, HAL_LL_UART5_GPIO_AF4},
    #endif
    #ifdef UART5_TX_PE10_AF6
    {hal_ll_uart_module_num(UART_MODULE_5), PE10, HAL_LL_UART5_BASE_ADDRESS, HAL_LL_UART5_GPIO_AF6},
    #endif
    #endif

    #ifdef UART_MODULE_6
    #ifdef UART6_TX_PA4_AF5
    {hal_ll_uart_module_num(UART_MODULE_6), PA4, HAL_LL_UART6_BASE_ADDRESS, HAL_LL_UART6_GPIO_AF5},
    #endif
    #ifdef UART6_TX_PC0_AF2
    {hal_ll_uart_module_num(UART_MODULE_6), PC0, HAL_LL_UART6_BASE_ADDRESS, HAL_LL_UART6_GPIO_AF2},
    #endif
    #ifdef UART6_TX_PC0_AF5
    {hal_ll_uart_module_num(UART_MODULE_6), PC0, HAL_LL_UART6_BASE_ADDRESS, HAL_LL_UART6_GPIO_AF5},
    #endif
    #ifdef UART6_TX_PC6_AF7
    {hal_ll_uart_module_num(UART_MODULE_6), PC6, HAL_LL_UART6_BASE_ADDRESS, HAL_LL_UART6_GPIO_AF7},
    #endif
    #ifdef UART6_TX_PC6_AF8
    {hal_ll_uart_module_num(UART_MODULE_6), PC6, HAL_LL_UART6_BASE_ADDRESS, HAL_LL_UART6_GPIO_AF8},
    #endif
    #ifdef UART6_TX_PF9_AF1
    {hal_ll_uart_module_num(UART_MODULE_6), PF9, HAL_LL_UART6_BASE_ADDRESS, HAL_LL_UART6_GPIO_AF1},
    #endif
    #ifdef UART6_TX_PF9_AF5
    {hal_ll_uart_module_num(UART_MODULE_6), PF9, HAL_LL_UART6_BASE_ADDRESS, HAL_LL_UART6_GPIO_AF5},
    #endif
    #ifdef UART6_TX_PG14_AF7
    {hal_ll_uart_module_num(UART_MODULE_6), PG14, HAL_LL_UART6_BASE_ADDRESS, HAL_LL_UART6_GPIO_AF7},
    #endif
    #ifdef UART6_TX_PG14_AF8
    {hal_ll_uart_module_num(UART_MODULE_6), PG14, HAL_LL_UART6_BASE_ADDRESS, HAL_LL_UART6_GPIO_AF8},
    #endif
    #endif

    #ifdef UART_MODULE_7
    #ifdef UART7_TX_PA15_AF12
    {hal_ll_uart_module_num(UART_MODULE_7), PA15, HAL_LL_UART7_BASE_ADDRESS, HAL_LL_UART7_GPIO_AF12},
    #endif
    #ifdef UART7_TX_PA15_AF11
    {hal_ll_uart_module_num(UART_MODULE_7), PA15, HAL_LL_UART7_BASE_ADDRESS, HAL_LL_UART7_GPIO_AF11},
    #endif
    #ifdef UART7_TX_PB4_AF12
    {hal_ll_uart_module_num(UART_MODULE_7), PB4, HAL_LL_UART7_BASE_ADDRESS, HAL_LL_UART7_GPIO_AF12},
    #endif
    #ifdef UART7_TX_PB4_AF11
    {hal_ll_uart_module_num(UART_MODULE_7), PB4, HAL_LL_UART7_BASE_ADDRESS, HAL_LL_UART7_GPIO_AF11},
    #endif
    #ifdef UART7_TX_PC0_AF1
    {hal_ll_uart_module_num(UART_MODULE_7), PC0, HAL_LL_UART7_BASE_ADDRESS, HAL_LL_UART7_GPIO_AF1},
    #endif
    #ifdef UART7_TX_PC6_AF1
    {hal_ll_uart_module_num(UART_MODULE_7), PC6, HAL_LL_UART7_BASE_ADDRESS, HAL_LL_UART7_GPIO_AF1},
    #endif
    #ifdef UART7_TX_PE8_AF8
    {hal_ll_uart_module_num(UART_MODULE_7), PE8, HAL_LL_UART7_BASE_ADDRESS, HAL_LL_UART7_GPIO_AF8},
    #endif
    #ifdef UART7_TX_PE8_AF7
    {hal_ll_uart_module_num(UART_MODULE_7), PE8, HAL_LL_UART7_BASE_ADDRESS, HAL_LL_UART7_GPIO_AF7},
    #endif
    #ifdef UART7_TX_PF2_AF1
    {hal_ll_uart_module_num(UART_MODULE_7), PF2, HAL_LL_UART7_BASE_ADDRESS, HAL_LL_UART7_GPIO_AF1},
    #endif
    #ifdef UART7_TX_PF7_AF8
    {hal_ll_uart_module_num(UART_MODULE_7), PF7, HAL_LL_UART7_BASE_ADDRESS, HAL_LL_UART7_GPIO_AF8},
    #endif
    #ifdef UART7_TX_PF7_AF7
    {hal_ll_uart_module_num(UART_MODULE_7), PF7, HAL_LL_UART7_BASE_ADDRESS, HAL_LL_UART7_GPIO_AF7},
    #endif
    #endif

    #ifdef UART_MODULE_8
    #ifdef UART8_TX_PC2_AF2
    {hal_ll_uart_module_num(UART_MODULE_8), PC2, HAL_LL_UART8_BASE_ADDRESS, HAL_LL_UART8_GPIO_AF2},
    #endif
    #ifdef UART8_TX_PC8_AF1
    {hal_ll_uart_module_num(UART_MODULE_8), PC8, HAL_LL_UART8_BASE_ADDRESS, HAL_LL_UART8_GPIO_AF1},
    #endif
    #ifdef UART8_TX_PC8_AF2
    {hal_ll_uart_module_num(UART_MODULE_8), PC8, HAL_LL_UART8_BASE_ADDRESS, HAL_LL_UART8_GPIO_AF2},
    #endif
    #ifdef UART8_TX_PD13_AF0
    {hal_ll_uart_module_num(UART_MODULE_8), PD13, HAL_LL_UART8_BASE_ADDRESS, HAL_LL_UART8_GPIO_AF0},
    #endif
    #ifdef UART8_TX_PD13_AF2
    {hal_ll_uart_module_num(UART_MODULE_8), PD13, HAL_LL_UART8_BASE_ADDRESS, HAL_LL_UART8_GPIO_AF2},
    #endif
    #ifdef UART8_TX_PE1_AF8
    {hal_ll_uart_module_num(UART_MODULE_8), PE1, HAL_LL_UART8_BASE_ADDRESS, HAL_LL_UART8_GPIO_AF8},
    #endif
    #ifdef UART8_TX_PJ8_AF8
    {hal_ll_uart_module_num(UART_MODULE_8), PJ8, HAL_LL_UART8_BASE_ADDRESS, HAL_LL_UART8_GPIO_AF8},
    #endif
    #endif

    {HAL_LL_MODULE_ERROR, HAL_LL_PIN_NC, HAL_LL_MODULE_ERROR, HAL_LL_PIN_NC}
    //------------ END TX
};

/*!< @brief UART RX pins */
__weak static const hal_ll_uart_pin_map_t hal_ll_uart_rx_map[] =
{
    //------------ BEGIN RX
    #ifdef UART_MODULE_1
    #ifdef UART1_RX_PA3_AF1
    {hal_ll_uart_module_num(UART_MODULE_1), PA3, HAL_LL_UART1_BASE_ADDRESS, HAL_LL_UART1_GPIO_AF1},
    #endif
    #ifdef UART1_RX_PA10_AF0
    {hal_ll_uart_module_num(UART_MODULE_1), PA10, HAL_LL_UART1_BASE_ADDRESS, HAL_LL_UART1_GPIO_AF0},
    #endif
    #ifdef UART1_RX_PA10_AF1
    {hal_ll_uart_module_num(UART_MODULE_1), PA10, HAL_LL_UART1_BASE_ADDRESS, HAL_LL_UART1_GPIO_AF1},
    #endif
    #ifdef UART1_RX_PA10_AF4
    {hal_ll_uart_module_num(UART_MODULE_1), PA10, HAL_LL_UART1_BASE_ADDRESS, HAL_LL_UART1_GPIO_AF4},
    #endif
    #ifdef UART1_RX_PA10_AF7
    {hal_ll_uart_module_num(UART_MODULE_1), PA10, HAL_LL_UART1_BASE_ADDRESS, HAL_LL_UART1_GPIO_AF7},
    #endif
    #ifdef UART1_RX_PA15_AF1
    {hal_ll_uart_module_num(UART_MODULE_1), PA15, HAL_LL_UART1_BASE_ADDRESS, HAL_LL_UART1_GPIO_AF1},
    #endif
    #ifdef UART1_RX_PA15_AF7
    {hal_ll_uart_module_num(UART_MODULE_1), PA15, HAL_LL_UART1_BASE_ADDRESS, HAL_LL_UART1_GPIO_AF7},
    #endif
    #ifdef UART1_RX_PB7_AF0
    {hal_ll_uart_module_num(UART_MODULE_1), PB7, HAL_LL_UART1_BASE_ADDRESS, HAL_LL_UART1_GPIO_AF0},
    #endif
    #ifdef UART1_RX_PB7_AF1
    {hal_ll_uart_module_num(UART_MODULE_1), PB7, HAL_LL_UART1_BASE_ADDRESS, HAL_LL_UART1_GPIO_AF1},
    #endif
    #ifdef UART1_RX_PB7_AF4
    {hal_ll_uart_module_num(UART_MODULE_1), PB7, HAL_LL_UART1_BASE_ADDRESS, HAL_LL_UART1_GPIO_AF4},
    #endif
    #ifdef UART1_RX_PB7_AF7
    {hal_ll_uart_module_num(UART_MODULE_1), PB7, HAL_LL_UART1_BASE_ADDRESS, HAL_LL_UART1_GPIO_AF7},
    #endif
    #ifdef UART1_RX_PB15_AF4
    {hal_ll_uart_module_num(UART_MODULE_1), PB15, HAL_LL_UART1_BASE_ADDRESS, HAL_LL_UART1_GPIO_AF4},
    #endif
    #ifdef UART1_RX_PC5_AF1
    {hal_ll_uart_module_num(UART_MODULE_1), PC5, HAL_LL_UART1_BASE_ADDRESS, HAL_LL_UART1_GPIO_AF1},
    #endif
    #ifdef UART1_RX_PC5_AF7
    {hal_ll_uart_module_num(UART_MODULE_1), PC5, HAL_LL_UART1_BASE_ADDRESS, HAL_LL_UART1_GPIO_AF7},
    #endif
    #ifdef UART1_RX_PE1_AF7
    {hal_ll_uart_module_num(UART_MODULE_1), PE1, HAL_LL_UART1_BASE_ADDRESS, HAL_LL_UART1_GPIO_AF7},
    #endif
    #ifdef UART1_RX_PG10_AF7
    {hal_ll_uart_module_num(UART_MODULE_1), PG10, HAL_LL_UART1_BASE_ADDRESS, HAL_LL_UART1_GPIO_AF7},
    #endif
    #endif

    #ifdef UART_MODULE_2
    #ifdef UART2_RX_PA0_AF0
    {hal_ll_uart_module_num(UART_MODULE_2), PA0, HAL_LL_UART2_BASE_ADDRESS, HAL_LL_UART2_GPIO_AF0},
    #endif
    #ifdef UART2_RX_PA3_AF1
    {hal_ll_uart_module_num(UART_MODULE_2), PA3, HAL_LL_UART2_BASE_ADDRESS, HAL_LL_UART2_GPIO_AF1},
    #endif
    #ifdef UART2_RX_PA3_AF3
    {hal_ll_uart_module_num(UART_MODULE_2), PA3, HAL_LL_UART2_BASE_ADDRESS, HAL_LL_UART2_GPIO_AF3},
    #endif
    #ifdef UART2_RX_PA3_AF4
    {hal_ll_uart_module_num(UART_MODULE_2), PA3, HAL_LL_UART2_BASE_ADDRESS, HAL_LL_UART2_GPIO_AF4},
    #endif
    #ifdef UART2_RX_PA10_AF0
    {hal_ll_uart_module_num(UART_MODULE_2), PA10, HAL_LL_UART2_BASE_ADDRESS, HAL_LL_UART2_GPIO_AF0},
    #endif
    #ifdef UART2_RX_PA10_AF4
    {hal_ll_uart_module_num(UART_MODULE_2), PA10, HAL_LL_UART2_BASE_ADDRESS, HAL_LL_UART2_GPIO_AF4},
    #endif
    #ifdef UART2_RX_PA3_AF7
    {hal_ll_uart_module_num(UART_MODULE_2), PA3, HAL_LL_UART2_BASE_ADDRESS, HAL_LL_UART2_GPIO_AF7},
    #endif
    #ifdef UART2_RX_PA15_AF1
    {hal_ll_uart_module_num(UART_MODULE_2), PA15, HAL_LL_UART2_BASE_ADDRESS, HAL_LL_UART2_GPIO_AF1},
    #endif
    #ifdef UART2_RX_PA15_AF3
    {hal_ll_uart_module_num(UART_MODULE_2), PA15, HAL_LL_UART2_BASE_ADDRESS, HAL_LL_UART2_GPIO_AF3},
    #endif
    #ifdef UART2_RX_PA15_AF4
    {hal_ll_uart_module_num(UART_MODULE_2), PA15, HAL_LL_UART2_BASE_ADDRESS, HAL_LL_UART2_GPIO_AF4},
    #endif
    #ifdef UART2_RX_PA15_AF7
    {hal_ll_uart_module_num(UART_MODULE_2), PA15, HAL_LL_UART2_BASE_ADDRESS, HAL_LL_UART2_GPIO_AF7},
    #endif
    #ifdef UART2_RX_PB4_AF7
    {hal_ll_uart_module_num(UART_MODULE_2), PB4, HAL_LL_UART2_BASE_ADDRESS, HAL_LL_UART2_GPIO_AF7},
    #endif
    #ifdef UART2_RX_PB7_AF0
    {hal_ll_uart_module_num(UART_MODULE_2), PB7, HAL_LL_UART2_BASE_ADDRESS, HAL_LL_UART2_GPIO_AF0},
    #endif
    #ifdef UART2_RX_PD6_AF0
    {hal_ll_uart_module_num(UART_MODULE_2), PD6, HAL_LL_UART2_BASE_ADDRESS, HAL_LL_UART2_GPIO_AF0},
    #endif
    #ifdef UART2_RX_PD6_AF1
    {hal_ll_uart_module_num(UART_MODULE_2), PD6, HAL_LL_UART2_BASE_ADDRESS, HAL_LL_UART2_GPIO_AF1},
    #endif
    #ifdef UART2_RX_PD6_AF3
    {hal_ll_uart_module_num(UART_MODULE_2), PD6, HAL_LL_UART2_BASE_ADDRESS, HAL_LL_UART2_GPIO_AF3},
    #endif
    #ifdef UART2_RX_PD6_AF4
    {hal_ll_uart_module_num(UART_MODULE_2), PD6, HAL_LL_UART2_BASE_ADDRESS, HAL_LL_UART2_GPIO_AF4},
    #endif
    #ifdef UART2_RX_PD6_AF7
    {hal_ll_uart_module_num(UART_MODULE_2), PD6, HAL_LL_UART2_BASE_ADDRESS, HAL_LL_UART2_GPIO_AF7},
    #endif
    #endif

    #ifdef UART_MODULE_3
    #ifdef UART3_RX_PB0_AF4
    {hal_ll_uart_module_num(UART_MODULE_3), PB0, HAL_LL_UART3_BASE_ADDRESS, HAL_LL_UART3_GPIO_AF4},
    #endif
    #ifdef UART3_RX_PB2_AF4
    {hal_ll_uart_module_num(UART_MODULE_3), PB2, HAL_LL_UART3_BASE_ADDRESS, HAL_LL_UART3_GPIO_AF4},
    #endif
    #ifdef UART3_RX_PB8_AF7
    {hal_ll_uart_module_num(UART_MODULE_3), PB8, HAL_LL_UART3_BASE_ADDRESS, HAL_LL_UART3_GPIO_AF7},
    #endif
    #ifdef UART3_RX_PB9_AF4
    {hal_ll_uart_module_num(UART_MODULE_3), PB9, HAL_LL_UART3_BASE_ADDRESS, HAL_LL_UART3_GPIO_AF4},
    #endif
    #ifdef UART3_RX_PB9_AF7
    {hal_ll_uart_module_num(UART_MODULE_3), PB9, HAL_LL_UART3_BASE_ADDRESS, HAL_LL_UART3_GPIO_AF7},
    #endif
    #ifdef UART3_RX_PB11_AF4
    {hal_ll_uart_module_num(UART_MODULE_3), PB11, HAL_LL_UART3_BASE_ADDRESS, HAL_LL_UART3_GPIO_AF4},
    #endif
    #ifdef UART3_RX_PB11_AF7
    {hal_ll_uart_module_num(UART_MODULE_3), PB11, HAL_LL_UART3_BASE_ADDRESS, HAL_LL_UART3_GPIO_AF7},
    #endif
    #ifdef UART3_RX_PC5_AF0
    {hal_ll_uart_module_num(UART_MODULE_3), PC5, HAL_LL_UART3_BASE_ADDRESS, HAL_LL_UART1_GPIO_AF0},
    #endif
    #ifdef UART3_RX_PC5_AF1
    {hal_ll_uart_module_num(UART_MODULE_3), PC5, HAL_LL_UART3_BASE_ADDRESS, HAL_LL_UART3_GPIO_AF1},
    #endif
    #ifdef UART3_RX_PC5_AF4
    {hal_ll_uart_module_num(UART_MODULE_3), PC5, HAL_LL_UART3_BASE_ADDRESS, HAL_LL_UART1_GPIO_AF4},
    #endif
    #ifdef UART3_RX_PC5_AF7
    {hal_ll_uart_module_num(UART_MODULE_3), PC5, HAL_LL_UART3_BASE_ADDRESS, HAL_LL_UART1_GPIO_AF7},
    #endif
    #ifdef UART3_RX_PC11_AF0
    {hal_ll_uart_module_num(UART_MODULE_3), PC11, HAL_LL_UART3_BASE_ADDRESS, HAL_LL_UART3_GPIO_AF0},
    #endif
    #ifdef UART3_RX_PC11_AF1
    {hal_ll_uart_module_num(UART_MODULE_3), PC11, HAL_LL_UART3_BASE_ADDRESS, HAL_LL_UART3_GPIO_AF1},
    #endif
    #ifdef UART3_RX_PC11_AF4
    {hal_ll_uart_module_num(UART_MODULE_3), PC11, HAL_LL_UART3_BASE_ADDRESS, HAL_LL_UART3_GPIO_AF4},
    #endif
    #ifdef UART3_RX_PC11_AF7
    {hal_ll_uart_module_num(UART_MODULE_3), PC11, HAL_LL_UART3_BASE_ADDRESS, HAL_LL_UART3_GPIO_AF7},
    #endif
    #ifdef UART3_RX_PD9_AF0
    {hal_ll_uart_module_num(UART_MODULE_3), PD9, HAL_LL_UART3_BASE_ADDRESS, HAL_LL_UART3_GPIO_AF0},
    #endif
    #ifdef UART3_RX_PD9_AF4
    {hal_ll_uart_module_num(UART_MODULE_3), PD9, HAL_LL_UART3_BASE_ADDRESS, HAL_LL_UART3_GPIO_AF4},
    #endif
    #ifdef UART3_RX_PD9_AF7
    {hal_ll_uart_module_num(UART_MODULE_3), PD9, HAL_LL_UART3_BASE_ADDRESS, HAL_LL_UART3_GPIO_AF7},
    #endif
    #ifdef UART3_RX_PE15_AF7
    {hal_ll_uart_module_num(UART_MODULE_3), PE15, HAL_LL_UART3_BASE_ADDRESS, HAL_LL_UART3_GPIO_AF7},
    #endif
    #endif

    #ifdef UART_MODULE_4
    #ifdef UART4_RX_PA1_AF4
    {hal_ll_uart_module_num(UART_MODULE_4), PA1, HAL_LL_UART4_BASE_ADDRESS, HAL_LL_UART4_GPIO_AF4},
    #endif
    #ifdef UART4_RX_PA1_AF6
    {hal_ll_uart_module_num(UART_MODULE_4), PA1, HAL_LL_UART4_BASE_ADDRESS, HAL_LL_UART4_GPIO_AF6},
    #endif
    #ifdef UART4_RX_PA1_AF8
    {hal_ll_uart_module_num(UART_MODULE_4), PA1, HAL_LL_UART4_BASE_ADDRESS, HAL_LL_UART4_GPIO_AF8},
    #endif
    #ifdef UART4_RX_PA11_AF6
    {hal_ll_uart_module_num(UART_MODULE_4), PA11, HAL_LL_UART4_BASE_ADDRESS, HAL_LL_UART4_GPIO_AF6},
    #endif
    #ifdef UART4_RX_PB8_AF8
    {hal_ll_uart_module_num(UART_MODULE_4), PB8, HAL_LL_UART4_BASE_ADDRESS, HAL_LL_UART4_GPIO_AF8},
    #endif
    #ifdef UART4_RX_PC11_AF0
    {hal_ll_uart_module_num(UART_MODULE_4), PC11, HAL_LL_UART4_BASE_ADDRESS, HAL_LL_UART4_GPIO_AF0},
    #endif
    #ifdef UART4_RX_PC11_AF1
    {hal_ll_uart_module_num(UART_MODULE_4), PC11, HAL_LL_UART4_BASE_ADDRESS, HAL_LL_UART4_GPIO_AF1},
    #endif
    #ifdef UART4_RX_PC11_AF8
    {hal_ll_uart_module_num(UART_MODULE_4), PC11, HAL_LL_UART4_BASE_ADDRESS, HAL_LL_UART4_GPIO_AF8},
    #endif
    #ifdef UART4_RX_PC11_AF5
    {hal_ll_uart_module_num(UART_MODULE_4), PC11, HAL_LL_UART4_BASE_ADDRESS, HAL_LL_UART4_GPIO_AF5},
    #endif
    #ifdef UART4_RX_PC11_AF6
    {hal_ll_uart_module_num(UART_MODULE_4), PC11, HAL_LL_UART4_BASE_ADDRESS, HAL_LL_UART4_GPIO_AF6},
    #endif
    #ifdef UART4_RX_PD0_AF8
    {hal_ll_uart_module_num(UART_MODULE_4), PD0, HAL_LL_UART4_BASE_ADDRESS, HAL_LL_UART4_GPIO_AF8},
    #endif
    #ifdef UART4_RX_PE9_AF1
    {hal_ll_uart_module_num(UART_MODULE_4), PE9, HAL_LL_UART4_BASE_ADDRESS, HAL_LL_UART4_GPIO_AF1},
    #endif
    #ifdef UART4_RX_PE9_AF4
    {hal_ll_uart_module_num(UART_MODULE_4), PE9, HAL_LL_UART4_BASE_ADDRESS, HAL_LL_UART4_GPIO_AF4},
    #endif
    #ifdef UART4_RX_PE9_AF6
    {hal_ll_uart_module_num(UART_MODULE_4), PE9, HAL_LL_UART4_BASE_ADDRESS, HAL_LL_UART4_GPIO_AF6},
    #endif
    #ifdef UART4_RX_PI9_AF8
    {hal_ll_uart_module_num(UART_MODULE_4), PI9, HAL_LL_UART4_BASE_ADDRESS, HAL_LL_UART4_GPIO_AF8},
    #endif
    #ifdef UART4_RX_PH14_AF8
    {hal_ll_uart_module_num(UART_MODULE_4), PH14, HAL_LL_UART4_BASE_ADDRESS, HAL_LL_UART4_GPIO_AF8},
    #endif
    #endif

    #ifdef UART_MODULE_5
    #ifdef UART5_RX_PB4_AF4
    {hal_ll_uart_module_num(UART_MODULE_5), PB4, HAL_LL_UART5_BASE_ADDRESS, HAL_LL_UART5_GPIO_AF4},
    #endif
    #ifdef UART5_RX_PB4_AF6
    {hal_ll_uart_module_num(UART_MODULE_5), PB4, HAL_LL_UART5_BASE_ADDRESS, HAL_LL_UART5_GPIO_AF6},
    #endif
    #ifdef UART5_RX_PB5_AF1
    {hal_ll_uart_module_num(UART_MODULE_5), PB5, HAL_LL_UART5_BASE_ADDRESS, HAL_LL_UART5_GPIO_AF1},
    #endif
    #ifdef UART5_RX_PB5_AF14
    {hal_ll_uart_module_num(UART_MODULE_5), PB5, HAL_LL_UART5_BASE_ADDRESS, HAL_LL_UART5_GPIO_AF14},
    #endif
    #ifdef UART5_RX_PB8_AF7
    {hal_ll_uart_module_num(UART_MODULE_5), PB8, HAL_LL_UART5_BASE_ADDRESS, HAL_LL_UART5_GPIO_AF7},
    #endif
    #ifdef UART5_RX_PB12_AF8
    {hal_ll_uart_module_num(UART_MODULE_5), PB12, HAL_LL_UART5_BASE_ADDRESS, HAL_LL_UART5_GPIO_AF8},
    #endif
    #ifdef UART5_RX_PB12_AF14
    {hal_ll_uart_module_num(UART_MODULE_5), PB12, HAL_LL_UART5_BASE_ADDRESS, HAL_LL_UART5_GPIO_AF14},
    #endif
    #ifdef UART5_RX_PD2_AF2
    {hal_ll_uart_module_num(UART_MODULE_5), PD2, HAL_LL_UART5_BASE_ADDRESS, HAL_LL_UART5_GPIO_AF2},
    #endif
    #ifdef UART5_RX_PD2_AF4
    {hal_ll_uart_module_num(UART_MODULE_5), PD2, HAL_LL_UART5_BASE_ADDRESS, HAL_LL_UART5_GPIO_AF4},
    #endif
    #ifdef UART5_RX_PD2_AF5
    {hal_ll_uart_module_num(UART_MODULE_5), PD2, HAL_LL_UART5_BASE_ADDRESS, HAL_LL_UART5_GPIO_AF5},
    #endif
    #ifdef UART5_RX_PD2_AF6
    {hal_ll_uart_module_num(UART_MODULE_5), PD2, HAL_LL_UART5_BASE_ADDRESS, HAL_LL_UART5_GPIO_AF6},
    #endif
    #ifdef UART5_RX_PD2_AF8
    {hal_ll_uart_module_num(UART_MODULE_5), PD2, HAL_LL_UART5_BASE_ADDRESS, HAL_LL_UART5_GPIO_AF8},
    #endif
    #ifdef UART5_RX_PE11_AF1
    {hal_ll_uart_module_num(UART_MODULE_5), PE11, HAL_LL_UART5_BASE_ADDRESS, HAL_LL_UART5_GPIO_AF1},
    #endif
    #ifdef UART5_RX_PE11_AF4
    {hal_ll_uart_module_num(UART_MODULE_5), PE11, HAL_LL_UART5_BASE_ADDRESS, HAL_LL_UART5_GPIO_AF4},
    #endif
    #ifdef UART5_RX_PE11_AF6
    {hal_ll_uart_module_num(UART_MODULE_5), PE11, HAL_LL_UART5_BASE_ADDRESS, HAL_LL_UART5_GPIO_AF6},
    #endif
    #endif

    #ifdef UART_MODULE_6
    #ifdef UART6_RX_PA5_AF5
    {hal_ll_uart_module_num(UART_MODULE_6), PA5, HAL_LL_UART6_BASE_ADDRESS, HAL_LL_UART6_GPIO_AF5},
    #endif
    #ifdef UART6_RX_PC1_AF2
    {hal_ll_uart_module_num(UART_MODULE_6), PC1, HAL_LL_UART6_BASE_ADDRESS, HAL_LL_UART6_GPIO_AF2},
    #endif
    #ifdef UART6_RX_PC1_AF5
    {hal_ll_uart_module_num(UART_MODULE_6), PC1, HAL_LL_UART6_BASE_ADDRESS, HAL_LL_UART6_GPIO_AF5},
    #endif
    #ifdef UART6_RX_PC7_AF7
    {hal_ll_uart_module_num(UART_MODULE_6), PC7, HAL_LL_UART6_BASE_ADDRESS, HAL_LL_UART6_GPIO_AF7},
    #endif
    #ifdef UART6_RX_PC7_AF8
    {hal_ll_uart_module_num(UART_MODULE_6), PC7, HAL_LL_UART6_BASE_ADDRESS, HAL_LL_UART6_GPIO_AF8},
    #endif
    #ifdef UART6_RX_PF10_AF1
    {hal_ll_uart_module_num(UART_MODULE_6), PF10, HAL_LL_UART6_BASE_ADDRESS, HAL_LL_UART6_GPIO_AF1},
    #endif
    #ifdef UART6_RX_PF10_AF5
    {hal_ll_uart_module_num(UART_MODULE_6), PF10, HAL_LL_UART6_BASE_ADDRESS, HAL_LL_UART6_GPIO_AF5},
    #endif
    #ifdef UART6_RX_PG9_AF7
    {hal_ll_uart_module_num(UART_MODULE_6), PG9, HAL_LL_UART6_BASE_ADDRESS, HAL_LL_UART6_GPIO_AF7},
    #endif
    #ifdef UART6_RX_PG9_AF8
    {hal_ll_uart_module_num(UART_MODULE_6), PG9, HAL_LL_UART6_BASE_ADDRESS, HAL_LL_UART6_GPIO_AF8},
    #endif
    #endif

    #ifdef UART_MODULE_7
    #ifdef UART7_RX_PA8_AF12
    {hal_ll_uart_module_num(UART_MODULE_7), PA8, HAL_LL_UART7_BASE_ADDRESS, HAL_LL_UART7_GPIO_AF12},
    #endif
    #ifdef UART7_RX_PA8_AF11
    {hal_ll_uart_module_num(UART_MODULE_7), PA8, HAL_LL_UART7_BASE_ADDRESS, HAL_LL_UART7_GPIO_AF11},
    #endif
    #ifdef UART7_RX_PB3_AF12
    {hal_ll_uart_module_num(UART_MODULE_7), PB3, HAL_LL_UART7_BASE_ADDRESS, HAL_LL_UART7_GPIO_AF12},
    #endif
    #ifdef UART7_RX_PB3_AF11
    {hal_ll_uart_module_num(UART_MODULE_7), PB3, HAL_LL_UART7_BASE_ADDRESS, HAL_LL_UART7_GPIO_AF11},
    #endif
    #ifdef UART7_RX_PC1_AF1
    {hal_ll_uart_module_num(UART_MODULE_7), PC1, HAL_LL_UART7_BASE_ADDRESS, HAL_LL_UART7_GPIO_AF1},
    #endif
    #ifdef UART7_RX_PC7_AF1
    {hal_ll_uart_module_num(UART_MODULE_7), PC7, HAL_LL_UART7_BASE_ADDRESS, HAL_LL_UART7_GPIO_AF1},
    #endif
    #ifdef UART7_RX_PE7_AF8
    {hal_ll_uart_module_num(UART_MODULE_7), PE7, HAL_LL_UART7_BASE_ADDRESS, HAL_LL_UART7_GPIO_AF8},
    #endif
    #ifdef UART7_RX_PE7_AF7
    {hal_ll_uart_module_num(UART_MODULE_7), PE7, HAL_LL_UART7_BASE_ADDRESS, HAL_LL_UART7_GPIO_AF7},
    #endif
    #ifdef UART7_RX_PF3_AF1
    {hal_ll_uart_module_num(UART_MODULE_7), PF3, HAL_LL_UART7_BASE_ADDRESS, HAL_LL_UART7_GPIO_AF1},
    #endif
    #ifdef UART7_RX_PF6_AF8
    {hal_ll_uart_module_num(UART_MODULE_7), PF6, HAL_LL_UART7_BASE_ADDRESS, HAL_LL_UART7_GPIO_AF8},
    #endif
    #ifdef UART7_RX_PF6_AF7
    {hal_ll_uart_module_num(UART_MODULE_7), PF6, HAL_LL_UART7_BASE_ADDRESS, HAL_LL_UART7_GPIO_AF7},
    #endif
    #endif

    #ifdef UART_MODULE_8
    #ifdef UART8_RX_PC3_AF2
    {hal_ll_uart_module_num(UART_MODULE_8), PC3, HAL_LL_UART8_BASE_ADDRESS, HAL_LL_UART8_GPIO_AF2},
    #endif
    #ifdef UART8_RX_PC9_AF1
    {hal_ll_uart_module_num(UART_MODULE_8), PC9, HAL_LL_UART8_BASE_ADDRESS, HAL_LL_UART8_GPIO_AF1},
    #endif
    #ifdef UART8_RX_PC9_AF2
    {hal_ll_uart_module_num(UART_MODULE_8), PC9, HAL_LL_UART8_BASE_ADDRESS, HAL_LL_UART8_GPIO_AF2},
    #endif
    #ifdef UART8_RX_PD14_AF0
    {hal_ll_uart_module_num(UART_MODULE_8), PD14, HAL_LL_UART8_BASE_ADDRESS, HAL_LL_UART8_GPIO_AF0},
    #endif
    #ifdef UART8_RX_PD14_AF2
    {hal_ll_uart_module_num(UART_MODULE_8), PD14, HAL_LL_UART8_BASE_ADDRESS, HAL_LL_UART8_GPIO_AF2},
    #endif
    #ifdef UART8_RX_PE0_AF8
    {hal_ll_uart_module_num(UART_MODULE_8), PE0, HAL_LL_UART8_BASE_ADDRESS, HAL_LL_UART8_GPIO_AF8},
    #endif
    #ifdef UART8_RX_PJ9_AF8
    {hal_ll_uart_module_num(UART_MODULE_8), PJ9, HAL_LL_UART8_BASE_ADDRESS, HAL_LL_UART8_GPIO_AF8},
    #endif
    #endif

    {HAL_LL_MODULE_ERROR, HAL_LL_PIN_NC, HAL_LL_MODULE_ERROR, HAL_LL_PIN_NC}
    //------------ END RX
};

#ifdef __cplusplus
}
#endif

#endif // _HAL_LL_UART_PIN_MAP_H_
// ------------------------------------------------------------------------- END
