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

/*!< @brief UART module base addresses */
#ifdef UART_MODULE_0
static const hal_ll_base_addr_t HAL_LL_UART0_BASE_ADDR = 0x40013800;
#endif
#ifdef UART_MODULE_1
static const hal_ll_base_addr_t HAL_LL_UART1_BASE_ADDR = 0x40004400;
#endif
#ifdef UART_MODULE_2
static const hal_ll_base_addr_t HAL_LL_UART2_BASE_ADDR = 0x40004800;
#endif
#ifdef UART_MODULE_3
static const hal_ll_base_addr_t HAL_LL_UART3_BASE_ADDR = 0x40004C00;
#endif
#ifdef UART_MODULE_4
static const hal_ll_base_addr_t HAL_LL_UART4_BASE_ADDR = 0x40005000;
#endif

/*!< @brief UART module alternate function values */
#define HAL_LL_UART_REMAP          (0x80000000)
#define HAL_LL_UART_NO_REMAP       (0x0)

#define HAL_LL_UART0_REMAP_FULL    (0x00000004)
#define HAL_LL_UART1_REMAP_FULL    (0x00000008)
#define HAL_LL_UART2_REMAP_PARTIAL (0x00000010)
#define HAL_LL_UART2_REMAP_FULL    (0x00000030)

/*!< @brief UART pin structure. */
typedef struct {
    uint8_t module_index;
    hal_ll_pin_name_t pin;
    hal_ll_base_addr_t base;
    uint32_t af;
} hal_ll_uart_pin_map_t;

/*!< UART TX Pins. */
static const hal_ll_uart_pin_map_t hal_ll_uart_tx_map[] = {
    #ifdef UART1_TX_PA2_REMAP_NONE
    {hal_ll_uart_module_num(UART_MODULE_1), PA2, HAL_LL_UART1_BASE_ADDR, HAL_LL_UART_NO_REMAP},
    #endif
    #ifdef UART0_TX_PA9_REMAP_NONE
    {hal_ll_uart_module_num(UART_MODULE_0), PA9, HAL_LL_UART0_BASE_ADDR, HAL_LL_UART_NO_REMAP},
    #endif
    #ifdef UART0_TX_PB6_REMAP_FULL
    {hal_ll_uart_module_num(UART_MODULE_0), PB6, HAL_LL_UART0_BASE_ADDR, HAL_LL_UART_REMAP | HAL_LL_UART0_REMAP_FULL},
    #endif
    #ifdef UART2_TX_PB10_REMAP_NONE
    {hal_ll_uart_module_num(UART_MODULE_2), PB10, HAL_LL_UART2_BASE_ADDR, HAL_LL_UART_NO_REMAP},
    #endif
    #ifdef UART2_TX_PC10_REMAP_PARTIAL
    {hal_ll_uart_module_num(UART_MODULE_2), PC10, HAL_LL_UART2_BASE_ADDR, HAL_LL_UART_REMAP | HAL_LL_UART2_REMAP_PARTIAL},
    #endif
    #ifdef UART3_TX_PC10_REMAP_NONE
    {hal_ll_uart_module_num(UART_MODULE_3), PC10, HAL_LL_UART3_BASE_ADDR, HAL_LL_UART_NO_REMAP},
    #endif
    #ifdef UART4_TX_PC12_REMAP_NONE
    {hal_ll_uart_module_num(UART_MODULE_4), PC12, HAL_LL_UART4_BASE_ADDR, HAL_LL_UART_NO_REMAP},
    #endif
    #ifdef UART2_TX_PD8_REMAP_FULL
    {hal_ll_uart_module_num(UART_MODULE_2), PD8, HAL_LL_UART2_BASE_ADDR, HAL_LL_UART_REMAP | HAL_LL_UART2_REMAP_FULL},
    #endif
    #ifdef UART1_TX_PD5_REMAP_FULL
    {hal_ll_uart_module_num(UART_MODULE_1), PD5, HAL_LL_UART1_BASE_ADDR, HAL_LL_UART_REMAP | HAL_LL_UART1_REMAP_FULL},
    #endif

    {HAL_LL_MODULE_ERROR, HAL_LL_PIN_NC, HAL_LL_MODULE_ERROR, HAL_LL_PIN_NC}
};

/*!< UART RX Pins. */
static const hal_ll_uart_pin_map_t hal_ll_uart_rx_map[] = {
    #ifdef UART1_RX_PA3_REMAP_NONE
    {hal_ll_uart_module_num(UART_MODULE_1), PA3, HAL_LL_UART1_BASE_ADDR, HAL_LL_UART_NO_REMAP},
    #endif
    #ifdef UART0_RX_PA10_REMAP_NONE
    {hal_ll_uart_module_num(UART_MODULE_0), PA10, HAL_LL_UART0_BASE_ADDR, HAL_LL_UART_NO_REMAP},
    #endif
    #ifdef UART0_RX_PB7_REMAP_FULL
    {hal_ll_uart_module_num(UART_MODULE_0), PB7, HAL_LL_UART0_BASE_ADDR, HAL_LL_UART_REMAP | HAL_LL_UART0_REMAP_FULL},
    #endif
    #ifdef UART2_RX_PB11_REMAP_NONE
    {hal_ll_uart_module_num(UART_MODULE_2), PB11, HAL_LL_UART2_BASE_ADDR, HAL_LL_UART_NO_REMAP},
    #endif
    #ifdef UART2_RX_PC11_REMAP_PARTIAL
    {hal_ll_uart_module_num(UART_MODULE_2), PC11, HAL_LL_UART2_BASE_ADDR, HAL_LL_UART_REMAP | HAL_LL_UART2_REMAP_PARTIAL},
    #endif
    #ifdef UART3_RX_PC11_REMAP_NONE
    {hal_ll_uart_module_num(UART_MODULE_3), PC11, HAL_LL_UART3_BASE_ADDR, HAL_LL_UART_NO_REMAP},
    #endif
    #ifdef UART4_RX_PD2_REMAP_NONE
    {hal_ll_uart_module_num(UART_MODULE_4), PD2, HAL_LL_UART4_BASE_ADDR, HAL_LL_UART_NO_REMAP},
    #endif
    #ifdef UART2_RX_PD9_REMAP_FULL
    {hal_ll_uart_module_num(UART_MODULE_2), PD9, HAL_LL_UART2_BASE_ADDR, HAL_LL_UART_REMAP | HAL_LL_UART2_REMAP_FULL},
    #endif
    #ifdef UART1_RX_PD6_REMAP_FULL
    {hal_ll_uart_module_num(UART_MODULE_1), PD6, HAL_LL_UART1_BASE_ADDR, HAL_LL_UART_REMAP | HAL_LL_UART1_REMAP_FULL},
    #endif

    {HAL_LL_MODULE_ERROR, HAL_LL_PIN_NC, HAL_LL_MODULE_ERROR, HAL_LL_PIN_NC}
};

#ifdef __cplusplus
}
#endif

#endif // _HAL_LL_UART_PIN_MAP_H_
// ------------------------------------------------------------------------- END
