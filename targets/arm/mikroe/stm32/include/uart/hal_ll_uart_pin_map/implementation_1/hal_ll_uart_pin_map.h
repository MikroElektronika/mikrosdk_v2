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

/*!< @brief Helper macro for getting adequate module index number */
#define hal_ll_uart_module_num(_module_num) (_module_num - 1)

/*!< @brief Macro defining `weak` attribute */
#define __weak __attribute__((weak))

/*!< @brief Macros used for STM32F1xx chip remap */
#define HAL_LL_UART_REMAP_ENABLE 0x08000000UL
#define HAL_LL_UART_REMAP_DISABLE 0

/*!< @brief UART module base addresses */
#ifdef UART_MODULE_1
#if defined(STM32F4xx) || defined(STM32F2xx)
static const hal_ll_base_addr_t HAL_LL_UART1_BASE_ADDRESS = 0x40011000;
#elif defined(STM32F1xx) || defined(STM32L1xx)
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
static const hal_ll_base_addr_t HAL_LL_UART7_BASE_ADDRESS = 0x40007800;
#endif
#ifdef UART_MODULE_8
static const hal_ll_base_addr_t HAL_LL_UART8_BASE_ADDRESS = 0x40007C00;
#endif
#ifdef UART_MODULE_9
static const hal_ll_base_addr_t HAL_LL_UART9_BASE_ADDRESS = 0x40011800;
#endif
#ifdef UART_MODULE_10
static const hal_ll_base_addr_t HAL_LL_UART10_BASE_ADDRESS = 0x40011C00;
#endif

/*!< @brief UART module alternate function values */
#ifdef UART_MODULE_1
static const uint8_t HAL_LL_UART1_GPIO_AF7 = 7;
static const uint8_t HAL_LL_UART1_GPIO_AF = 4;
#endif
#ifdef UART_MODULE_2
static const uint8_t HAL_LL_UART2_GPIO_AF7 = 7;
static const uint8_t HAL_LL_UART2_GPIO_AF = 8;
#endif
#ifdef UART_MODULE_3
static const uint8_t HAL_LL_UART3_GPIO_AF7 = 7;
static const uint32_t HAL_LL_UART3_GPIO_AF_1 = 0x10;
static const uint32_t HAL_LL_UART3_GPIO_AF_2 = 0x30;
#endif
#ifdef UART_MODULE_4
static const uint8_t HAL_LL_UART4_GPIO_AF8 = 8;
static const uint8_t HAL_LL_UART4_GPIO_AF11 = 11;
static const uint8_t HAL_LL_UART4_GPIO_AF = 0;
#endif
#ifdef UART_MODULE_5
static const uint8_t HAL_LL_UART5_GPIO_AF8 = 8;
static const uint8_t HAL_LL_UART5_GPIO_AF11 = 11;
static const uint8_t HAL_LL_UART5_GPIO_AF = 0;
#endif
#ifdef UART_MODULE_6
static const uint8_t HAL_LL_UART6_GPIO_AF8 = 8;
#endif
#ifdef UART_MODULE_7
static const uint8_t HAL_LL_UART7_GPIO_AF8 = 8;
#endif
#ifdef UART_MODULE_8
static const uint8_t HAL_LL_UART8_GPIO_AF8 = 8;
#endif
#ifdef UART_MODULE_9
static const uint8_t HAL_LL_UART9_GPIO_AF11 = 11;
#endif
#ifdef UART_MODULE_10
static const uint8_t HAL_LL_UART10_GPIO_AF11 = 11;
#endif

/*!< @brief Pin structure */
typedef struct
{
    uint8_t module_index;
    hal_ll_pin_name_t pin;
    hal_ll_base_addr_t base;
    uint32_t af;
} hal_ll_uart_pin_map_t;

/*!< @brief UART TX pins */
__weak static const hal_ll_uart_pin_map_t hal_ll_uart_tx_map[] =
{
    //------------ BEGIN TX
    #ifdef UART_MODULE_1
    #ifdef UART1_TX_PA9_AF7
    {hal_ll_uart_module_num(UART_MODULE_1), PA9, HAL_LL_UART1_BASE_ADDRESS, HAL_LL_UART1_GPIO_AF7},
    #endif
    #ifdef UART1_TX_PA9
    {hal_ll_uart_module_num(UART_MODULE_1), PA9, HAL_LL_UART1_BASE_ADDRESS, HAL_LL_UART_REMAP_DISABLE},
    #endif
    #ifdef UART1_TX_PA15_AF7
    {hal_ll_uart_module_num(UART_MODULE_1), PA15, HAL_LL_UART1_BASE_ADDRESS, HAL_LL_UART1_GPIO_AF7},
    #endif
    #ifdef UART1_TX_PB6_AF7
    {hal_ll_uart_module_num(UART_MODULE_1), PB6, HAL_LL_UART1_BASE_ADDRESS, HAL_LL_UART1_GPIO_AF7},
    #endif
    #ifdef UART1_TX_PB6_REMAP
    {hal_ll_uart_module_num(UART_MODULE_1), PB6, HAL_LL_UART1_BASE_ADDRESS, ( HAL_LL_UART1_GPIO_AF | HAL_LL_UART_REMAP_ENABLE )},
    #endif
    #endif

    #ifdef UART_MODULE_2
    #ifdef UART2_TX_PA2_AF7
    {hal_ll_uart_module_num(UART_MODULE_2), PA2, HAL_LL_UART2_BASE_ADDRESS, HAL_LL_UART2_GPIO_AF7},
    #endif
    #ifdef UART2_TX_PA2
    {hal_ll_uart_module_num(UART_MODULE_2), PA2, HAL_LL_UART2_BASE_ADDRESS, HAL_LL_UART_REMAP_DISABLE},
    #endif
    #ifdef UART2_TX_PD5_AF7
    {hal_ll_uart_module_num(UART_MODULE_2), PD5, HAL_LL_UART2_BASE_ADDRESS, HAL_LL_UART2_GPIO_AF7},
    #endif
    #ifdef UART2_TX_PD5_REMAP
    {hal_ll_uart_module_num(UART_MODULE_2), PD5, HAL_LL_UART2_BASE_ADDRESS, ( HAL_LL_UART2_GPIO_AF | HAL_LL_UART_REMAP_ENABLE )},
    #endif
    #endif

    #ifdef UART_MODULE_3
    #ifdef UART3_TX_PB10_AF7
    {hal_ll_uart_module_num(UART_MODULE_3), PB10, HAL_LL_UART3_BASE_ADDRESS, HAL_LL_UART3_GPIO_AF7},
    #endif
    #ifdef UART3_TX_PB10
    {hal_ll_uart_module_num(UART_MODULE_3), PB10, HAL_LL_UART3_BASE_ADDRESS, HAL_LL_UART_REMAP_DISABLE},
    #endif
    #ifdef UART3_TX_PC10_AF7
    {hal_ll_uart_module_num(UART_MODULE_3), PC10, HAL_LL_UART3_BASE_ADDRESS, HAL_LL_UART3_GPIO_AF7},
    #endif
    #ifdef UART3_TX_PC10_REMAP
    {hal_ll_uart_module_num(UART_MODULE_3), PC10, HAL_LL_UART3_BASE_ADDRESS, ( HAL_LL_UART3_GPIO_AF_1 | HAL_LL_UART_REMAP_ENABLE )},
    #endif
    #ifdef UART3_TX_PD8_AF7
    {hal_ll_uart_module_num(UART_MODULE_3), PD8, HAL_LL_UART3_BASE_ADDRESS, HAL_LL_UART3_GPIO_AF7},
    #endif
    #ifdef UART3_TX_PD8_REMAP
    {hal_ll_uart_module_num(UART_MODULE_3), PD8, HAL_LL_UART3_BASE_ADDRESS, ( HAL_LL_UART3_GPIO_AF_2 | HAL_LL_UART_REMAP_ENABLE )},
    #endif
    #endif

    #ifdef UART_MODULE_4
    #ifdef UART4_TX_PA0_AF8
    {hal_ll_uart_module_num(UART_MODULE_4), PA0, HAL_LL_UART4_BASE_ADDRESS, HAL_LL_UART4_GPIO_AF8},
    #endif
    #ifdef UART4_TX_PA12_AF11
    {hal_ll_uart_module_num(UART_MODULE_4), PA12, HAL_LL_UART4_BASE_ADDRESS, HAL_LL_UART4_GPIO_AF11},
    #endif
    #ifdef UART4_TX_PC10_AF8
    {hal_ll_uart_module_num(UART_MODULE_4), PC10, HAL_LL_UART4_BASE_ADDRESS, HAL_LL_UART4_GPIO_AF8},
    #endif
    #ifdef UART4_TX_PC10
    {hal_ll_uart_module_num(UART_MODULE_4), PC10, HAL_LL_UART4_BASE_ADDRESS, HAL_LL_UART4_GPIO_AF},
    #endif
    #ifdef UART4_TX_PD1_AF11
    {hal_ll_uart_module_num(UART_MODULE_4), PD1, HAL_LL_UART4_BASE_ADDRESS, HAL_LL_UART4_GPIO_AF11},
    #endif
    #ifdef UART4_TX_PD10_AF8
    {hal_ll_uart_module_num(UART_MODULE_4), PD10, HAL_LL_UART4_BASE_ADDRESS, HAL_LL_UART4_GPIO_AF8},
    #endif
    #endif

    #ifdef UART_MODULE_5
    #ifdef UART5_TX_PB6_AF11
    {hal_ll_uart_module_num(UART_MODULE_5), PB6, HAL_LL_UART5_BASE_ADDRESS, HAL_LL_UART5_GPIO_AF11},
    #endif
    #ifdef UART5_TX_PB9_AF11
    {hal_ll_uart_module_num(UART_MODULE_5), PB9, HAL_LL_UART5_BASE_ADDRESS, HAL_LL_UART5_GPIO_AF11},
    #endif
    #ifdef UART5_TX_PB13_AF11
    {hal_ll_uart_module_num(UART_MODULE_5), PB13, HAL_LL_UART5_BASE_ADDRESS, HAL_LL_UART5_GPIO_AF11},
    #endif
    #ifdef UART5_TX_PC12_AF8
    {hal_ll_uart_module_num(UART_MODULE_5), PC12, HAL_LL_UART5_BASE_ADDRESS, HAL_LL_UART5_GPIO_AF8},
    #endif
    #ifdef UART5_TX_PC12
    {hal_ll_uart_module_num(UART_MODULE_5), PC12, HAL_LL_UART5_BASE_ADDRESS, HAL_LL_UART5_GPIO_AF},
    #endif
    #ifdef UART5_TX_PE8_AF8
    {hal_ll_uart_module_num(UART_MODULE_5), PE8, HAL_LL_UART5_BASE_ADDRESS, HAL_LL_UART5_GPIO_AF8},
    #endif
    #endif

    #ifdef UART_MODULE_6
    #ifdef UART6_TX_PA11_AF8
    {hal_ll_uart_module_num(UART_MODULE_6), PA11, HAL_LL_UART6_BASE_ADDRESS, HAL_LL_UART6_GPIO_AF8},
    #endif
    #ifdef UART6_TX_PC6_AF8
    {hal_ll_uart_module_num(UART_MODULE_6), PC6, HAL_LL_UART6_BASE_ADDRESS, HAL_LL_UART6_GPIO_AF8},
    #endif
    #ifdef UART6_TX_PG14_AF8
    {hal_ll_uart_module_num(UART_MODULE_6), PG14, HAL_LL_UART6_BASE_ADDRESS, HAL_LL_UART6_GPIO_AF8},
    #endif
    #endif

    #ifdef UART_MODULE_7
    #ifdef UART7_TX_PA15_AF8
    {hal_ll_uart_module_num(UART_MODULE_7), PA15, HAL_LL_UART7_BASE_ADDRESS, HAL_LL_UART7_GPIO_AF8},
    #endif
    #ifdef UART7_TX_PB4_AF8
    {hal_ll_uart_module_num(UART_MODULE_7), PB4, HAL_LL_UART7_BASE_ADDRESS, HAL_LL_UART7_GPIO_AF8},
    #endif
    #ifdef UART7_TX_PE8_AF8
    {hal_ll_uart_module_num(UART_MODULE_7), PE8, HAL_LL_UART7_BASE_ADDRESS, HAL_LL_UART7_GPIO_AF8},
    #endif
    #ifdef UART7_TX_PF7_AF8
    {hal_ll_uart_module_num(UART_MODULE_7), PF7, HAL_LL_UART7_BASE_ADDRESS, HAL_LL_UART7_GPIO_AF8},
    #endif
    #endif

    #ifdef UART_MODULE_8
    #ifdef UART8_TX_PE1_AF8
    {hal_ll_uart_module_num(UART_MODULE_8), PE1, HAL_LL_UART8_BASE_ADDRESS, HAL_LL_UART8_GPIO_AF8},
    #endif
    #ifdef UART8_TX_PF9_AF8
    {hal_ll_uart_module_num(UART_MODULE_8), PF9, HAL_LL_UART8_BASE_ADDRESS, HAL_LL_UART8_GPIO_AF8},
    #endif
    #endif

    #ifdef UART_MODULE_9
    #ifdef UART9_TX_PD15_AF11
    {hal_ll_uart_module_num(UART_MODULE_9), PD15, HAL_LL_UART9_BASE_ADDRESS, HAL_LL_UART9_GPIO_AF11},
    #endif
    #ifdef UART9_TX_PG1_AF11
    {hal_ll_uart_module_num(UART_MODULE_9), PG1, HAL_LL_UART9_BASE_ADDRESS, HAL_LL_UART9_GPIO_AF11},
    #endif
    #endif

    #ifdef UART_MODULE_10
    #ifdef UART10_TX_PE3_AF11
    {hal_ll_uart_module_num(UART_MODULE_10), PE3, HAL_LL_UART10_BASE_ADDRESS, HAL_LL_UART10_GPIO_AF11},
    #endif
    #ifdef UART10_TX_PG12_AF11
    {hal_ll_uart_module_num(UART_MODULE_10), PG12, HAL_LL_UART10_BASE_ADDRESS, HAL_LL_UART10_GPIO_AF11},
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
    #ifdef UART1_RX_PA10_AF7
    {hal_ll_uart_module_num(UART_MODULE_1), PA10, HAL_LL_UART1_BASE_ADDRESS, HAL_LL_UART1_GPIO_AF7},
    #endif
    #ifdef UART1_RX_PA10
    {hal_ll_uart_module_num(UART_MODULE_1), PA10, HAL_LL_UART1_BASE_ADDRESS, HAL_LL_UART_REMAP_DISABLE},
    #endif
    #ifdef UART1_RX_PB3_AF7
    {hal_ll_uart_module_num(UART_MODULE_1), PB3, HAL_LL_UART1_BASE_ADDRESS, HAL_LL_UART1_GPIO_AF7},
    #endif
    #ifdef UART1_RX_PB7_AF7
    {hal_ll_uart_module_num(UART_MODULE_1), PB7, HAL_LL_UART1_BASE_ADDRESS, HAL_LL_UART1_GPIO_AF7},
    #endif
    #ifdef UART1_RX_PB7_REMAP
    {hal_ll_uart_module_num(UART_MODULE_1), PB7, HAL_LL_UART1_BASE_ADDRESS, ( HAL_LL_UART1_GPIO_AF | HAL_LL_UART_REMAP_ENABLE )},
    #endif
    #endif

    #ifdef UART_MODULE_2
    #ifdef UART2_RX_PA3_AF7
    {hal_ll_uart_module_num(UART_MODULE_2), PA3, HAL_LL_UART2_BASE_ADDRESS, HAL_LL_UART2_GPIO_AF7},
    #endif
    #ifdef UART2_RX_PA3
    {hal_ll_uart_module_num(UART_MODULE_2), PA3, HAL_LL_UART2_BASE_ADDRESS, HAL_LL_UART_REMAP_DISABLE},
    #endif
    #ifdef UART2_RX_PD6_AF7
    {hal_ll_uart_module_num(UART_MODULE_2), PD6, HAL_LL_UART2_BASE_ADDRESS, HAL_LL_UART2_GPIO_AF7},
    #endif
    #ifdef UART2_RX_PD6_REMAP
    {hal_ll_uart_module_num(UART_MODULE_2), PD6, HAL_LL_UART2_BASE_ADDRESS, ( HAL_LL_UART2_GPIO_AF | HAL_LL_UART_REMAP_ENABLE )},
    #endif
    #endif

    #ifdef UART_MODULE_3
    #ifdef UART3_RX_PB11_AF7
    {hal_ll_uart_module_num(UART_MODULE_3), PB11, HAL_LL_UART3_BASE_ADDRESS, HAL_LL_UART3_GPIO_AF7},
    #endif
    #ifdef UART3_RX_PB11
    {hal_ll_uart_module_num(UART_MODULE_3), PB11, HAL_LL_UART3_BASE_ADDRESS, HAL_LL_UART_REMAP_DISABLE},
    #endif
    #ifdef UART3_RX_PC5_AF7
    {hal_ll_uart_module_num(UART_MODULE_3), PC5, HAL_LL_UART3_BASE_ADDRESS, HAL_LL_UART3_GPIO_AF7},
    #endif
    #ifdef UART3_RX_PC11_AF7
    {hal_ll_uart_module_num(UART_MODULE_3), PC11, HAL_LL_UART3_BASE_ADDRESS, HAL_LL_UART3_GPIO_AF7},
    #endif
    #ifdef UART3_RX_PC11_REMAP
    {hal_ll_uart_module_num(UART_MODULE_3), PC11, HAL_LL_UART3_BASE_ADDRESS, ( HAL_LL_UART3_GPIO_AF_1 | HAL_LL_UART_REMAP_ENABLE )},
    #endif
    #ifdef UART3_RX_PD9_AF7
    {hal_ll_uart_module_num(UART_MODULE_3), PD9, HAL_LL_UART3_BASE_ADDRESS, HAL_LL_UART3_GPIO_AF7},
    #endif
    #ifdef UART3_RX_PD9_REMAP
    {hal_ll_uart_module_num(UART_MODULE_3), PD9, HAL_LL_UART3_BASE_ADDRESS, ( HAL_LL_UART3_GPIO_AF_2 | HAL_LL_UART_REMAP_ENABLE )},
    #endif
    #endif

    #ifdef UART_MODULE_4
    #ifdef UART4_RX_PA1_AF8
    {hal_ll_uart_module_num(UART_MODULE_4), PA1, HAL_LL_UART4_BASE_ADDRESS, HAL_LL_UART4_GPIO_AF8},
    #endif
    #ifdef UART4_RX_PA11_AF11
    {hal_ll_uart_module_num(UART_MODULE_4), PA11, HAL_LL_UART4_BASE_ADDRESS, HAL_LL_UART4_GPIO_AF11},
    #endif
    #ifdef UART4_RX_PC11_AF8
    {hal_ll_uart_module_num(UART_MODULE_4), PC11, HAL_LL_UART4_BASE_ADDRESS, HAL_LL_UART4_GPIO_AF8},
    #endif
    #ifdef UART4_RX_PC11
    {hal_ll_uart_module_num(UART_MODULE_4), PC11, HAL_LL_UART4_BASE_ADDRESS, HAL_LL_UART4_GPIO_AF},
    #endif
    #ifdef UART4_RX_PD0_AF11
    {hal_ll_uart_module_num(UART_MODULE_4), PD0, HAL_LL_UART4_BASE_ADDRESS, HAL_LL_UART4_GPIO_AF11},
    #endif
    #endif

    #ifdef UART_MODULE_5
    #ifdef UART5_RX_PB5_AF11
    {hal_ll_uart_module_num(UART_MODULE_5), PB5, HAL_LL_UART5_BASE_ADDRESS, HAL_LL_UART5_GPIO_AF11},
    #endif
    #ifdef UART5_RX_PB8_AF11
    {hal_ll_uart_module_num(UART_MODULE_5), PB8, HAL_LL_UART5_BASE_ADDRESS, HAL_LL_UART5_GPIO_AF11},
    #endif
    #ifdef UART5_RX_PB12_AF11
    {hal_ll_uart_module_num(UART_MODULE_5), PB12, HAL_LL_UART5_BASE_ADDRESS, HAL_LL_UART5_GPIO_AF11},
    #endif
    #ifdef UART5_RX_PD2_AF8
    {hal_ll_uart_module_num(UART_MODULE_5), PD2, HAL_LL_UART5_BASE_ADDRESS, HAL_LL_UART5_GPIO_AF8},
    #endif
    #ifdef UART5_RX_PD2
    {hal_ll_uart_module_num(UART_MODULE_5), PD2, HAL_LL_UART5_BASE_ADDRESS, HAL_LL_UART5_GPIO_AF},
    #endif
    #ifdef UART5_RX_PE7_AF8
    {hal_ll_uart_module_num(UART_MODULE_5), PE7, HAL_LL_UART5_BASE_ADDRESS, HAL_LL_UART5_GPIO_AF8},
    #endif
    #endif

    #ifdef UART_MODULE_6
    #ifdef UART6_RX_PA12_AF8
    {hal_ll_uart_module_num(UART_MODULE_6), PA12, HAL_LL_UART6_BASE_ADDRESS, HAL_LL_UART6_GPIO_AF8},
    #endif
    #ifdef UART6_RX_PC7_AF8
    {hal_ll_uart_module_num(UART_MODULE_6), PC7, HAL_LL_UART6_BASE_ADDRESS, HAL_LL_UART6_GPIO_AF8},
    #endif
    #ifdef UART6_RX_PG9_AF8
    {hal_ll_uart_module_num(UART_MODULE_6), PG9, HAL_LL_UART6_BASE_ADDRESS, HAL_LL_UART6_GPIO_AF8},
    #endif
    #endif

    #ifdef UART_MODULE_7
    #ifdef UART7_RX_PA8_AF8
    {hal_ll_uart_module_num(UART_MODULE_7), PA8, HAL_LL_UART7_BASE_ADDRESS, HAL_LL_UART7_GPIO_AF8},
    #endif
    #ifdef UART7_RX_PB3_AF8
    {hal_ll_uart_module_num(UART_MODULE_7), PB3, HAL_LL_UART7_BASE_ADDRESS, HAL_LL_UART7_GPIO_AF8},
    #endif
    #ifdef UART7_RX_PE7_AF8
    {hal_ll_uart_module_num(UART_MODULE_7), PE7, HAL_LL_UART7_BASE_ADDRESS, HAL_LL_UART7_GPIO_AF8},
    #endif
    #ifdef UART7_RX_PF6_AF8
    {hal_ll_uart_module_num(UART_MODULE_7), PF6, HAL_LL_UART7_BASE_ADDRESS, HAL_LL_UART7_GPIO_AF8},
    #endif
    #endif

    #ifdef UART_MODULE_8
    #ifdef UART8_RX_PE0_AF8
    {hal_ll_uart_module_num(UART_MODULE_8), PE0, HAL_LL_UART8_BASE_ADDRESS, HAL_LL_UART8_GPIO_AF8},
    #endif
    #ifdef UART8_RX_PF8_AF8
    {hal_ll_uart_module_num(UART_MODULE_8), PF8, HAL_LL_UART8_BASE_ADDRESS, HAL_LL_UART8_GPIO_AF8},
    #endif
    #endif

    #ifdef UART_MODULE_9
    #ifdef UART9_RX_PD14_AF11
    {hal_ll_uart_module_num(UART_MODULE_9), PD14, HAL_LL_UART9_BASE_ADDRESS, HAL_LL_UART9_GPIO_AF11},
    #endif
    #ifdef UART9_RX_PG0_AF11
    {hal_ll_uart_module_num(UART_MODULE_9), PG0, HAL_LL_UART9_BASE_ADDRESS, HAL_LL_UART9_GPIO_AF11},
    #endif
    #endif

    #ifdef UART_MODULE_10
    #ifdef UART10_RX_PE2_AF11
    {hal_ll_uart_module_num(UART_MODULE_10), PE2, HAL_LL_UART10_BASE_ADDRESS, HAL_LL_UART10_GPIO_AF11},
    #endif
    #ifdef UART10_RX_PG11_AF11
    {hal_ll_uart_module_num(UART_MODULE_10), PG11, HAL_LL_UART10_BASE_ADDRESS, HAL_LL_UART10_GPIO_AF11},
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
