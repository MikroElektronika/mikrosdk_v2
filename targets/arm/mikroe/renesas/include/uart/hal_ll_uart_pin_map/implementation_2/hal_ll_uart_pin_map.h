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

/*!< @brief UART pin structure. */
typedef struct {
    uint8_t module_index;
    hal_ll_pin_name_t pin;
    hal_ll_base_addr_t base;
    uint8_t af;
} hal_ll_uart_pin_map_t;

/*!< UART TX Pins. */
static const hal_ll_uart_pin_map_t hal_ll_uart_tx_map[] = {
    #ifdef SAU_UART0_TX_P101_AF3
    {hal_ll_uart_module_num( SAU_UART_MODULE_0 ), GPIO_P101, HAL_LL_SAU0_BASE_ADDR, 3},
    #endif
    #ifdef SAU_UART0_TX_P109_AF2
    {hal_ll_uart_module_num( SAU_UART_MODULE_0 ), GPIO_P109, HAL_LL_SAU0_BASE_ADDR, 2},
    #endif
    #ifdef SAU_UART0_TX_P501_AF2
    {hal_ll_uart_module_num( SAU_UART_MODULE_0 ), GPIO_P501, HAL_LL_SAU0_BASE_ADDR, 2},
    #endif
    #ifdef SAU_UART1_TX_P213_AF3
    {hal_ll_uart_module_num( SAU_UART_MODULE_1 ), GPIO_P213, HAL_LL_SAU0_BASE_ADDR, 3},
    #endif
    #ifdef SAU_UART1_TX_P300_AF3
    {hal_ll_uart_module_num( SAU_UART_MODULE_1 ), GPIO_P300, HAL_LL_SAU0_BASE_ADDR, 3},
    #endif
    #ifdef SAU_UART2_TX_P109_AF2
    {hal_ll_uart_module_num( SAU_UART_MODULE_2 ), GPIO_P109, HAL_LL_SAU1_BASE_ADDR, 2},
    #endif
    #ifdef SAU_UART2_TX_P402_AF1
    {hal_ll_uart_module_num( SAU_UART_MODULE_2 ), GPIO_P402, HAL_LL_SAU1_BASE_ADDR, 1},
    #endif
    #ifdef UART0_TX_P101_AF5
    {hal_ll_uart_module_num( UART_MODULE_0 ), GPIO_P101, HAL_LL_UARTA0_BASE_ADDR, 5},
    #endif
    #ifdef UART0_TX_P109_AF4
    {hal_ll_uart_module_num( UART_MODULE_0 ), GPIO_P109, HAL_LL_UARTA0_BASE_ADDR, 4},
    #endif
    #ifdef UART0_TX_P208_AF2
    {hal_ll_uart_module_num( UART_MODULE_0 ), GPIO_P208, HAL_LL_UARTA0_BASE_ADDR, 2},
    #endif
    #ifdef UART0_TX_P213_AF6
    {hal_ll_uart_module_num( UART_MODULE_0 ), GPIO_P213, HAL_LL_UARTA0_BASE_ADDR, 6},
    #endif
    #ifdef UART0_TX_P402_AF2
    {hal_ll_uart_module_num( UART_MODULE_0 ), GPIO_P402, HAL_LL_UARTA0_BASE_ADDR, 2},
    #endif
    #ifdef UART0_TX_P501_AF4
    {hal_ll_uart_module_num( UART_MODULE_0 ), GPIO_P501, HAL_LL_UARTA0_BASE_ADDR, 4},
    #endif
    #ifdef UART1_TX_P103_AF7
    {hal_ll_uart_module_num( UART_MODULE_1 ), GPIO_P103, HAL_LL_UARTA1_BASE_ADDR, 7},
    #endif
    #ifdef UART1_TX_P106_AF4
    {hal_ll_uart_module_num( UART_MODULE_1 ), GPIO_P106, HAL_LL_UARTA1_BASE_ADDR, 4},
    #endif
    #ifdef UART1_TX_P206_AF3
    {hal_ll_uart_module_num( UART_MODULE_1 ), GPIO_P206, HAL_LL_UARTA1_BASE_ADDR, 3},
    #endif
    #ifdef UART1_TX_P302_AF4
    {hal_ll_uart_module_num( UART_MODULE_1 ), GPIO_P302, HAL_LL_UARTA1_BASE_ADDR, 4},
    #endif
    #ifdef UART1_TX_P411_AF5
    {hal_ll_uart_module_num( UART_MODULE_1 ), GPIO_P411, HAL_LL_UARTA1_BASE_ADDR, 5},
    #endif

    {HAL_LL_MODULE_ERROR, HAL_LL_PIN_NC, HAL_LL_MODULE_ERROR, HAL_LL_PIN_NC}
};

/*!< UART RX Pins. */
static const hal_ll_uart_pin_map_t hal_ll_uart_rx_map[] = {
    #ifdef SAU_UART0_RX_P100_AF3
    {hal_ll_uart_module_num( SAU_UART_MODULE_0 ), GPIO_P100, HAL_LL_SAU0_BASE_ADDR, 3},
    #endif
    #ifdef SAU_UART0_RX_P110_AF2
    {hal_ll_uart_module_num( SAU_UART_MODULE_0 ), GPIO_P110, HAL_LL_SAU0_BASE_ADDR, 2},
    #endif
    #ifdef SAU_UART0_RX_P502_AF2
    {hal_ll_uart_module_num( SAU_UART_MODULE_0 ), GPIO_P502, HAL_LL_SAU0_BASE_ADDR, 2},
    #endif
    #ifdef SAU_UART1_RX_P200_AF3
    {hal_ll_uart_module_num( SAU_UART_MODULE_1 ), GPIO_P200, HAL_LL_SAU0_BASE_ADDR, 3},
    #endif
    #ifdef SAU_UART1_RX_P212_AF3
    {hal_ll_uart_module_num( SAU_UART_MODULE_1 ), GPIO_P212, HAL_LL_SAU0_BASE_ADDR, 3},
    #endif
    #ifdef SAU_UART2_RX_P110_AF2
    {hal_ll_uart_module_num( SAU_UART_MODULE_2 ), GPIO_P110, HAL_LL_SAU1_BASE_ADDR, 2},
    #endif
    #ifdef SAU_UART2_RX_P403_AF1
    {hal_ll_uart_module_num( SAU_UART_MODULE_2 ), GPIO_P403, HAL_LL_SAU1_BASE_ADDR, 1},
    #endif
    #ifdef UART0_RX_P100_AF5
    {hal_ll_uart_module_num( UART_MODULE_0 ), GPIO_P100, HAL_LL_UARTA0_BASE_ADDR, 5},
    #endif
    #ifdef UART0_RX_P110_AF4
    {hal_ll_uart_module_num( UART_MODULE_0 ), GPIO_P110, HAL_LL_UARTA0_BASE_ADDR, 4},
    #endif
    #ifdef UART0_RX_P207_AF2
    {hal_ll_uart_module_num( UART_MODULE_0 ), GPIO_P207, HAL_LL_UARTA0_BASE_ADDR, 2},
    #endif
    #ifdef UART0_RX_P212_AF6
    {hal_ll_uart_module_num( UART_MODULE_0 ), GPIO_P212, HAL_LL_UARTA0_BASE_ADDR, 6},
    #endif
    #ifdef UART0_RX_P403_AF2
    {hal_ll_uart_module_num( UART_MODULE_0 ), GPIO_P403, HAL_LL_UARTA0_BASE_ADDR, 2},
    #endif
    #ifdef UART0_RX_P502_AF4
    {hal_ll_uart_module_num( UART_MODULE_0 ), GPIO_P502, HAL_LL_UARTA0_BASE_ADDR, 4},
    #endif
    #ifdef UART1_RX_P102_AF7
    {hal_ll_uart_module_num( UART_MODULE_1 ), GPIO_P102, HAL_LL_UARTA1_BASE_ADDR, 7},
    #endif
    #ifdef UART1_RX_P105_AF4
    {hal_ll_uart_module_num( UART_MODULE_1 ), GPIO_P105, HAL_LL_UARTA1_BASE_ADDR, 4},
    #endif
    #ifdef UART1_RX_P205_AF3
    {hal_ll_uart_module_num( UART_MODULE_1 ), GPIO_P205, HAL_LL_UARTA1_BASE_ADDR, 3},
    #endif
    #ifdef UART1_RX_P301_AF4
    {hal_ll_uart_module_num( UART_MODULE_1 ), GPIO_P301, HAL_LL_UARTA1_BASE_ADDR, 4},
    #endif
    #ifdef UART1_RX_P410_AF5
    {hal_ll_uart_module_num( UART_MODULE_1 ), GPIO_P410, HAL_LL_UARTA1_BASE_ADDR, 5},
    #endif

    {HAL_LL_MODULE_ERROR, HAL_LL_PIN_NC, HAL_LL_MODULE_ERROR, HAL_LL_PIN_NC}
};

#ifdef __cplusplus
}
#endif

#endif // _HAL_LL_UART_PIN_MAP_H_
// ------------------------------------------------------------------------- END
