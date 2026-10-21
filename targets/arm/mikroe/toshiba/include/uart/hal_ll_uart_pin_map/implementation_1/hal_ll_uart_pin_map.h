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
#include "mcu_reg_addresses.h"

/*!< @brief Macro defining `weak` attribute */
#define __weak __attribute__((weak))
/*!< @brief Helper macro for getting adequate module index number */
#define hal_ll_uart_module_num(_module_num) (_module_num - 1)

/**
 * Alternate Function Values.
 */
typedef enum
{
    HAL_LL_ALTERNATE_FUNCTION_1 = 1,
    HAL_LL_ALTERNATE_FUNCTION_2,
    HAL_LL_ALTERNATE_FUNCTION_3,
    HAL_LL_ALTERNATE_FUNCTION_4,
    HAL_LL_ALTERNATE_FUNCTION_5,
    HAL_LL_ALTERNATE_FUNCTION_6,
    HAL_LL_ALTERNATE_FUNCTION_7,
    HAL_LL_ALTERNATE_FUNCTION_8
} hal_ll_alternate_function_t;


/*!< @brief UART pin structure. */
typedef struct {
    uint8_t module_index;
    hal_ll_pin_name_t pin;
    hal_ll_base_addr_t base;
    hal_ll_alternate_function_t af;
} hal_ll_uart_pin_map_t;

/*!< UART TX Pins. */
static const hal_ll_uart_pin_map_t hal_ll_uart_tx_map[] = {
    #ifdef UART0_TX_PC0_AF1
    {hal_ll_uart_module_num( UART_MODULE_0 ), GPIO_PC0, HAL_LL_UART0_BASE_ADDRESS, HAL_LL_ALTERNATE_FUNCTION_1},
    #endif
    #ifdef UART0_TX_PC1_AF2
    {hal_ll_uart_module_num( UART_MODULE_0 ), GPIO_PC1, HAL_LL_UART0_BASE_ADDRESS, HAL_LL_ALTERNATE_FUNCTION_2},
    #endif
    #ifdef UART0_TX_PD2_AF2
    {hal_ll_uart_module_num( UART_MODULE_0 ), GPIO_PD2, HAL_LL_UART0_BASE_ADDRESS, HAL_LL_ALTERNATE_FUNCTION_2},
    #endif
    #ifdef UART0_TX_PD3_AF1
    {hal_ll_uart_module_num( UART_MODULE_0 ), GPIO_PD3, HAL_LL_UART0_BASE_ADDRESS, HAL_LL_ALTERNATE_FUNCTION_1},
    #endif
    #ifdef UART0_TX_PN0_AF1
    {hal_ll_uart_module_num( UART_MODULE_0 ), GPIO_PN0, HAL_LL_UART0_BASE_ADDRESS, HAL_LL_ALTERNATE_FUNCTION_1},
    #endif
    #ifdef UART0_TX_PN1_AF2
    {hal_ll_uart_module_num( UART_MODULE_0 ), GPIO_PN1, HAL_LL_UART0_BASE_ADDRESS, HAL_LL_ALTERNATE_FUNCTION_2},
    #endif
    #ifdef UART1_TX_PA3_AF1
    {hal_ll_uart_module_num( UART_MODULE_1 ), GPIO_PA3, HAL_LL_UART1_BASE_ADDRESS, HAL_LL_ALTERNATE_FUNCTION_1},
    #endif
    #ifdef UART1_TX_PA4_AF2
    {hal_ll_uart_module_num( UART_MODULE_1 ), GPIO_PA4, HAL_LL_UART1_BASE_ADDRESS, HAL_LL_ALTERNATE_FUNCTION_2},
    #endif
    #ifdef UART1_TX_PA5_AF1
    {hal_ll_uart_module_num( UART_MODULE_1 ), GPIO_PA5, HAL_LL_UART1_BASE_ADDRESS, HAL_LL_ALTERNATE_FUNCTION_1},
    #endif
    #ifdef UART1_TX_PA6_AF2
    {hal_ll_uart_module_num( UART_MODULE_1 ), GPIO_PA6, HAL_LL_UART1_BASE_ADDRESS, HAL_LL_ALTERNATE_FUNCTION_2},
    #endif
    #ifdef UART1_TX_PC4_AF1
    {hal_ll_uart_module_num( UART_MODULE_1 ), GPIO_PC4, HAL_LL_UART1_BASE_ADDRESS, HAL_LL_ALTERNATE_FUNCTION_1},
    #endif
    #ifdef UART1_TX_PC5_AF2
    {hal_ll_uart_module_num( UART_MODULE_1 ), GPIO_PC5, HAL_LL_UART1_BASE_ADDRESS, HAL_LL_ALTERNATE_FUNCTION_2},
    #endif
    #ifdef UART1_TX_PU5_AF1
    {hal_ll_uart_module_num( UART_MODULE_1 ), GPIO_PU5, HAL_LL_UART1_BASE_ADDRESS, HAL_LL_ALTERNATE_FUNCTION_1},
    #endif
    #ifdef UART1_TX_PU6_AF2
    {hal_ll_uart_module_num( UART_MODULE_1 ), GPIO_PU6, HAL_LL_UART1_BASE_ADDRESS, HAL_LL_ALTERNATE_FUNCTION_2},
    #endif
    #ifdef UART2_TX_PA1_AF1
    {hal_ll_uart_module_num( UART_MODULE_2 ), GPIO_PA1, HAL_LL_UART2_BASE_ADDRESS, HAL_LL_ALTERNATE_FUNCTION_1},
    #endif
    #ifdef UART2_TX_PA2_AF2
    {hal_ll_uart_module_num( UART_MODULE_2 ), GPIO_PA2, HAL_LL_UART2_BASE_ADDRESS, HAL_LL_ALTERNATE_FUNCTION_2},
    #endif
    #ifdef UART2_TX_PC2_AF1
    {hal_ll_uart_module_num( UART_MODULE_2 ), GPIO_PC2, HAL_LL_UART2_BASE_ADDRESS, HAL_LL_ALTERNATE_FUNCTION_1},
    #endif
    #ifdef UART2_TX_PC3_AF2
    {hal_ll_uart_module_num( UART_MODULE_2 ), GPIO_PC3, HAL_LL_UART2_BASE_ADDRESS, HAL_LL_ALTERNATE_FUNCTION_2},
    #endif
    #ifdef UART2_TX_PF0_AF1
    {hal_ll_uart_module_num( UART_MODULE_2 ), GPIO_PF0, HAL_LL_UART2_BASE_ADDRESS, HAL_LL_ALTERNATE_FUNCTION_1},
    #endif
    #ifdef UART2_TX_PF1_AF2
    {hal_ll_uart_module_num( UART_MODULE_2 ), GPIO_PF1, HAL_LL_UART2_BASE_ADDRESS, HAL_LL_ALTERNATE_FUNCTION_2},
    #endif
    #ifdef UART2_TX_PU0_AF1
    {hal_ll_uart_module_num( UART_MODULE_2 ), GPIO_PU0, HAL_LL_UART2_BASE_ADDRESS, HAL_LL_ALTERNATE_FUNCTION_1},
    #endif
    #ifdef UART2_TX_PU1_AF2
    {hal_ll_uart_module_num( UART_MODULE_2 ), GPIO_PU1, HAL_LL_UART2_BASE_ADDRESS, HAL_LL_ALTERNATE_FUNCTION_2},
    #endif
    #ifdef UART3_TX_PC0_AF1
    {hal_ll_uart_module_num( UART_MODULE_3 ), GPIO_PC0, HAL_LL_UART3_BASE_ADDRESS, HAL_LL_ALTERNATE_FUNCTION_1},
    #endif
    #ifdef UART3_TX_PC1_AF2
    {hal_ll_uart_module_num( UART_MODULE_3 ), GPIO_PC1, HAL_LL_UART3_BASE_ADDRESS, HAL_LL_ALTERNATE_FUNCTION_2},
    #endif
    #ifdef UART3_TX_PD4_AF2
    {hal_ll_uart_module_num( UART_MODULE_3 ), GPIO_PD4, HAL_LL_UART3_BASE_ADDRESS, HAL_LL_ALTERNATE_FUNCTION_2},
    #endif
    #ifdef UART3_TX_PD5_AF1
    {hal_ll_uart_module_num( UART_MODULE_3 ), GPIO_PD5, HAL_LL_UART3_BASE_ADDRESS, HAL_LL_ALTERNATE_FUNCTION_1},
    #endif
    #ifdef UART3_TX_PF3_AF1
    {hal_ll_uart_module_num( UART_MODULE_3 ), GPIO_PF3, HAL_LL_UART3_BASE_ADDRESS, HAL_LL_ALTERNATE_FUNCTION_1},
    #endif
    #ifdef UART3_TX_PF4_AF2
    {hal_ll_uart_module_num( UART_MODULE_3 ), GPIO_PF4, HAL_LL_UART3_BASE_ADDRESS, HAL_LL_ALTERNATE_FUNCTION_2},
    #endif
    #ifdef UART3_TX_PF6_AF1
    {hal_ll_uart_module_num( UART_MODULE_3 ), GPIO_PF6, HAL_LL_UART3_BASE_ADDRESS, HAL_LL_ALTERNATE_FUNCTION_1},
    #endif
    #ifdef UART3_TX_PF7_AF2
    {hal_ll_uart_module_num( UART_MODULE_3 ), GPIO_PF7, HAL_LL_UART3_BASE_ADDRESS, HAL_LL_ALTERNATE_FUNCTION_2},
    #endif
    #ifdef UART4_TX_PA7_AF1
    {hal_ll_uart_module_num( UART_MODULE_4 ), GPIO_PA7, HAL_LL_UART4_BASE_ADDRESS, HAL_LL_ALTERNATE_FUNCTION_1},
    #endif
    #ifdef UART4_TX_PJ2_AF2
    {hal_ll_uart_module_num( UART_MODULE_4 ), GPIO_PJ2, HAL_LL_UART4_BASE_ADDRESS, HAL_LL_ALTERNATE_FUNCTION_2},
    #endif
    #ifdef UART5_TX_PG0_AF1
    {hal_ll_uart_module_num( UART_MODULE_5 ), GPIO_PG0, HAL_LL_UART5_BASE_ADDRESS, HAL_LL_ALTERNATE_FUNCTION_1},
    #endif
    #ifdef UART0_TX_PA1_AF1
    {hal_ll_uart_module_num( UART_MODULE_0 ), GPIO_PA1, HAL_LL_UART0_BASE_ADDRESS, HAL_LL_ALTERNATE_FUNCTION_1},
    #endif
    #ifdef UART0_TX_PA2_AF2
    {hal_ll_uart_module_num( UART_MODULE_0 ), GPIO_PA2, HAL_LL_UART0_BASE_ADDRESS, HAL_LL_ALTERNATE_FUNCTION_2},
    #endif
    #ifdef UART0_TX_PM1_AF1
    {hal_ll_uart_module_num( UART_MODULE_0 ), GPIO_PM1, HAL_LL_UART0_BASE_ADDRESS, HAL_LL_ALTERNATE_FUNCTION_1},
    #endif
    #ifdef UART0_TX_PM2_AF2
    {hal_ll_uart_module_num( UART_MODULE_0 ), GPIO_PM2, HAL_LL_UART0_BASE_ADDRESS, HAL_LL_ALTERNATE_FUNCTION_2},
    #endif
    #ifdef UART1_TX_PJ1_AF1
    {hal_ll_uart_module_num( UART_MODULE_1 ), GPIO_PJ1, HAL_LL_UART1_BASE_ADDRESS, HAL_LL_ALTERNATE_FUNCTION_1},
    #endif
    #ifdef UART1_TX_PJ2_AF2
    {hal_ll_uart_module_num( UART_MODULE_1 ), GPIO_PJ2, HAL_LL_UART1_BASE_ADDRESS, HAL_LL_ALTERNATE_FUNCTION_2},
    #endif
    #ifdef UART1_TX_PK1_AF1
    {hal_ll_uart_module_num( UART_MODULE_1 ), GPIO_PK1, HAL_LL_UART1_BASE_ADDRESS, HAL_LL_ALTERNATE_FUNCTION_1},
    #endif
    #ifdef UART1_TX_PK2_AF2
    {hal_ll_uart_module_num( UART_MODULE_1 ), GPIO_PK2, HAL_LL_UART1_BASE_ADDRESS, HAL_LL_ALTERNATE_FUNCTION_2},
    #endif
    #ifdef UART2_TX_PB2_AF1
    {hal_ll_uart_module_num( UART_MODULE_2 ), GPIO_PB2, HAL_LL_UART2_BASE_ADDRESS, HAL_LL_ALTERNATE_FUNCTION_1},
    #endif
    #ifdef UART2_TX_PB3_AF2
    {hal_ll_uart_module_num( UART_MODULE_2 ), GPIO_PB3, HAL_LL_UART2_BASE_ADDRESS, HAL_LL_ALTERNATE_FUNCTION_2},
    #endif
    #ifdef UART2_TX_PL0_AF1
    {hal_ll_uart_module_num( UART_MODULE_2 ), GPIO_PL0, HAL_LL_UART2_BASE_ADDRESS, HAL_LL_ALTERNATE_FUNCTION_1},
    #endif
    #ifdef UART2_TX_PL1_AF2
    {hal_ll_uart_module_num( UART_MODULE_2 ), GPIO_PL1, HAL_LL_UART2_BASE_ADDRESS, HAL_LL_ALTERNATE_FUNCTION_2},
    #endif
    #ifdef UART3_TX_PA6_AF2
    {hal_ll_uart_module_num( UART_MODULE_3 ), GPIO_PA6, HAL_LL_UART3_BASE_ADDRESS, HAL_LL_ALTERNATE_FUNCTION_2},
    #endif
    #ifdef UART3_TX_PA7_AF1
    {hal_ll_uart_module_num( UART_MODULE_3 ), GPIO_PA7, HAL_LL_UART3_BASE_ADDRESS, HAL_LL_ALTERNATE_FUNCTION_1},
    #endif
    #ifdef UART3_TX_PG2_AF2
    {hal_ll_uart_module_num( UART_MODULE_3 ), GPIO_PG2, HAL_LL_UART3_BASE_ADDRESS, HAL_LL_ALTERNATE_FUNCTION_2},
    #endif
    #ifdef UART3_TX_PG3_AF1
    {hal_ll_uart_module_num( UART_MODULE_3 ), GPIO_PG3, HAL_LL_UART3_BASE_ADDRESS, HAL_LL_ALTERNATE_FUNCTION_1},
    #endif
    #ifdef UART4_TX_PC3_AF1
    {hal_ll_uart_module_num( UART_MODULE_4 ), GPIO_PC3, HAL_LL_UART4_BASE_ADDRESS, HAL_LL_ALTERNATE_FUNCTION_1},
    #endif
    #ifdef UART4_TX_PC4_AF2
    {hal_ll_uart_module_num( UART_MODULE_4 ), GPIO_PC4, HAL_LL_UART4_BASE_ADDRESS, HAL_LL_ALTERNATE_FUNCTION_2},
    #endif
    #ifdef UART4_TX_PV6_AF1
    {hal_ll_uart_module_num( UART_MODULE_4 ), GPIO_PV6, HAL_LL_UART4_BASE_ADDRESS, HAL_LL_ALTERNATE_FUNCTION_1},
    #endif
    #ifdef UART4_TX_PV7_AF2
    {hal_ll_uart_module_num( UART_MODULE_4 ), GPIO_PV7, HAL_LL_UART4_BASE_ADDRESS, HAL_LL_ALTERNATE_FUNCTION_2},
    #endif
    #ifdef UART5_TX_PN2_AF2
    {hal_ll_uart_module_num( UART_MODULE_5 ), GPIO_PN2, HAL_LL_UART5_BASE_ADDRESS, HAL_LL_ALTERNATE_FUNCTION_2},
    #endif
    #ifdef UART5_TX_PN3_AF1
    {hal_ll_uart_module_num( UART_MODULE_5 ), GPIO_PN3, HAL_LL_UART5_BASE_ADDRESS, HAL_LL_ALTERNATE_FUNCTION_1},
    #endif
    #ifdef UART6_TX_PK5_AF2
    {hal_ll_uart_module_num( UART_MODULE_6 ), GPIO_PK5, HAL_LL_UART6_BASE_ADDRESS, HAL_LL_ALTERNATE_FUNCTION_2},
    #endif
    #ifdef UART6_TX_PK6_AF1
    {hal_ll_uart_module_num( UART_MODULE_6 ), GPIO_PK6, HAL_LL_UART6_BASE_ADDRESS, HAL_LL_ALTERNATE_FUNCTION_1},
    #endif
    #ifdef UART7_TX_PR0_AF2
    {hal_ll_uart_module_num( UART_MODULE_7 ), GPIO_PR0, HAL_LL_UART7_BASE_ADDRESS, HAL_LL_ALTERNATE_FUNCTION_2},
    #endif
    #ifdef UART7_TX_PR1_AF1
    {hal_ll_uart_module_num( UART_MODULE_7 ), GPIO_PR1, HAL_LL_UART7_BASE_ADDRESS, HAL_LL_ALTERNATE_FUNCTION_1},
    #endif

    {HAL_LL_MODULE_ERROR, HAL_LL_PIN_NC, HAL_LL_MODULE_ERROR, HAL_LL_PIN_NC}
};

/*!< UART RX Pins. */
static const hal_ll_uart_pin_map_t hal_ll_uart_rx_map[] = {
    #ifdef UART0_RX_PC0_AF2
    {hal_ll_uart_module_num( UART_MODULE_0 ), GPIO_PC0, HAL_LL_UART0_BASE_ADDRESS, HAL_LL_ALTERNATE_FUNCTION_2},
    #endif
    #ifdef UART0_RX_PC1_AF1
    {hal_ll_uart_module_num( UART_MODULE_0 ), GPIO_PC1, HAL_LL_UART0_BASE_ADDRESS, HAL_LL_ALTERNATE_FUNCTION_1},
    #endif
    #ifdef UART0_RX_PD2_AF1
    {hal_ll_uart_module_num( UART_MODULE_0 ), GPIO_PD2, HAL_LL_UART0_BASE_ADDRESS, HAL_LL_ALTERNATE_FUNCTION_1},
    #endif
    #ifdef UART0_RX_PD3_AF2
    {hal_ll_uart_module_num( UART_MODULE_0 ), GPIO_PD3, HAL_LL_UART0_BASE_ADDRESS, HAL_LL_ALTERNATE_FUNCTION_2},
    #endif
    #ifdef UART0_RX_PN0_AF2
    {hal_ll_uart_module_num( UART_MODULE_0 ), GPIO_PN0, HAL_LL_UART0_BASE_ADDRESS, HAL_LL_ALTERNATE_FUNCTION_2},
    #endif
    #ifdef UART0_RX_PN1_AF1
    {hal_ll_uart_module_num( UART_MODULE_0 ), GPIO_PN1, HAL_LL_UART0_BASE_ADDRESS, HAL_LL_ALTERNATE_FUNCTION_1},
    #endif
    #ifdef UART1_RX_PA3_AF2
    {hal_ll_uart_module_num( UART_MODULE_1 ), GPIO_PA3, HAL_LL_UART1_BASE_ADDRESS, HAL_LL_ALTERNATE_FUNCTION_2},
    #endif
    #ifdef UART1_RX_PA4_AF1
    {hal_ll_uart_module_num( UART_MODULE_1 ), GPIO_PA4, HAL_LL_UART1_BASE_ADDRESS, HAL_LL_ALTERNATE_FUNCTION_1},
    #endif
    #ifdef UART1_RX_PA5_AF2
    {hal_ll_uart_module_num( UART_MODULE_1 ), GPIO_PA5, HAL_LL_UART1_BASE_ADDRESS, HAL_LL_ALTERNATE_FUNCTION_2},
    #endif
    #ifdef UART1_RX_PA6_AF1
    {hal_ll_uart_module_num( UART_MODULE_1 ), GPIO_PA6, HAL_LL_UART1_BASE_ADDRESS, HAL_LL_ALTERNATE_FUNCTION_1},
    #endif
    #ifdef UART1_RX_PC4_AF2
    {hal_ll_uart_module_num( UART_MODULE_1 ), GPIO_PC4, HAL_LL_UART1_BASE_ADDRESS, HAL_LL_ALTERNATE_FUNCTION_2},
    #endif
    #ifdef UART1_RX_PC5_AF1
    {hal_ll_uart_module_num( UART_MODULE_1 ), GPIO_PC5, HAL_LL_UART1_BASE_ADDRESS, HAL_LL_ALTERNATE_FUNCTION_1},
    #endif
    #ifdef UART1_RX_PU5_AF2
    {hal_ll_uart_module_num( UART_MODULE_1 ), GPIO_PU5, HAL_LL_UART1_BASE_ADDRESS, HAL_LL_ALTERNATE_FUNCTION_2},
    #endif
    #ifdef UART1_RX_PU6_AF1
    {hal_ll_uart_module_num( UART_MODULE_1 ), GPIO_PU6, HAL_LL_UART1_BASE_ADDRESS, HAL_LL_ALTERNATE_FUNCTION_1},
    #endif
    #ifdef UART2_RX_PA1_AF2
    {hal_ll_uart_module_num( UART_MODULE_2 ), GPIO_PA1, HAL_LL_UART2_BASE_ADDRESS, HAL_LL_ALTERNATE_FUNCTION_2},
    #endif
    #ifdef UART2_RX_PA2_AF1
    {hal_ll_uart_module_num( UART_MODULE_2 ), GPIO_PA2, HAL_LL_UART2_BASE_ADDRESS, HAL_LL_ALTERNATE_FUNCTION_1},
    #endif
    #ifdef UART2_RX_PC2_AF2
    {hal_ll_uart_module_num( UART_MODULE_2 ), GPIO_PC2, HAL_LL_UART2_BASE_ADDRESS, HAL_LL_ALTERNATE_FUNCTION_2},
    #endif
    #ifdef UART2_RX_PC3_AF1
    {hal_ll_uart_module_num( UART_MODULE_2 ), GPIO_PC3, HAL_LL_UART2_BASE_ADDRESS, HAL_LL_ALTERNATE_FUNCTION_1},
    #endif
    #ifdef UART2_RX_PF0_AF2
    {hal_ll_uart_module_num( UART_MODULE_2 ), GPIO_PF0, HAL_LL_UART2_BASE_ADDRESS, HAL_LL_ALTERNATE_FUNCTION_2},
    #endif
    #ifdef UART2_RX_PF1_AF1
    {hal_ll_uart_module_num( UART_MODULE_2 ), GPIO_PF1, HAL_LL_UART2_BASE_ADDRESS, HAL_LL_ALTERNATE_FUNCTION_1},
    #endif
    #ifdef UART2_RX_PU0_AF2
    {hal_ll_uart_module_num( UART_MODULE_2 ), GPIO_PU0, HAL_LL_UART2_BASE_ADDRESS, HAL_LL_ALTERNATE_FUNCTION_2},
    #endif
    #ifdef UART2_RX_PU1_AF1
    {hal_ll_uart_module_num( UART_MODULE_2 ), GPIO_PU1, HAL_LL_UART2_BASE_ADDRESS, HAL_LL_ALTERNATE_FUNCTION_1},
    #endif
    #ifdef UART3_RX_PC0_AF2
    {hal_ll_uart_module_num( UART_MODULE_3 ), GPIO_PC0, HAL_LL_UART3_BASE_ADDRESS, HAL_LL_ALTERNATE_FUNCTION_2},
    #endif
    #ifdef UART3_RX_PC1_AF1
    {hal_ll_uart_module_num( UART_MODULE_3 ), GPIO_PC1, HAL_LL_UART3_BASE_ADDRESS, HAL_LL_ALTERNATE_FUNCTION_1},
    #endif
    #ifdef UART3_RX_PD4_AF1
    {hal_ll_uart_module_num( UART_MODULE_3 ), GPIO_PD4, HAL_LL_UART3_BASE_ADDRESS, HAL_LL_ALTERNATE_FUNCTION_1},
    #endif
    #ifdef UART3_RX_PD5_AF2
    {hal_ll_uart_module_num( UART_MODULE_3 ), GPIO_PD5, HAL_LL_UART3_BASE_ADDRESS, HAL_LL_ALTERNATE_FUNCTION_2},
    #endif
    #ifdef UART3_RX_PF3_AF2
    {hal_ll_uart_module_num( UART_MODULE_3 ), GPIO_PF3, HAL_LL_UART3_BASE_ADDRESS, HAL_LL_ALTERNATE_FUNCTION_2},
    #endif
    #ifdef UART3_RX_PF4_AF1
    {hal_ll_uart_module_num( UART_MODULE_3 ), GPIO_PF4, HAL_LL_UART3_BASE_ADDRESS, HAL_LL_ALTERNATE_FUNCTION_1},
    #endif
    #ifdef UART3_RX_PF6_AF2
    {hal_ll_uart_module_num( UART_MODULE_3 ), GPIO_PF6, HAL_LL_UART3_BASE_ADDRESS, HAL_LL_ALTERNATE_FUNCTION_2},
    #endif
    #ifdef UART3_RX_PF7_AF1
    {hal_ll_uart_module_num( UART_MODULE_3 ), GPIO_PF7, HAL_LL_UART3_BASE_ADDRESS, HAL_LL_ALTERNATE_FUNCTION_1},
    #endif
    #ifdef UART4_RX_PA7_AF2
    {hal_ll_uart_module_num( UART_MODULE_4 ), GPIO_PA7, HAL_LL_UART4_BASE_ADDRESS, HAL_LL_ALTERNATE_FUNCTION_2},
    #endif
    #ifdef UART4_RX_PJ2_AF1
    {hal_ll_uart_module_num( UART_MODULE_4 ), GPIO_PJ2, HAL_LL_UART4_BASE_ADDRESS, HAL_LL_ALTERNATE_FUNCTION_1},
    #endif
    #ifdef UART5_RX_PG1_AF1
    {hal_ll_uart_module_num( UART_MODULE_5 ), GPIO_PG1, HAL_LL_UART5_BASE_ADDRESS, HAL_LL_ALTERNATE_FUNCTION_1},
    #endif
    #ifdef UART0_RX_PA1_AF2
    {hal_ll_uart_module_num( UART_MODULE_0 ), GPIO_PA1, HAL_LL_UART0_BASE_ADDRESS, HAL_LL_ALTERNATE_FUNCTION_2},
    #endif
    #ifdef UART0_RX_PA2_AF1
    {hal_ll_uart_module_num( UART_MODULE_0 ), GPIO_PA2, HAL_LL_UART0_BASE_ADDRESS, HAL_LL_ALTERNATE_FUNCTION_1},
    #endif
    #ifdef UART0_RX_PM1_AF2
    {hal_ll_uart_module_num( UART_MODULE_0 ), GPIO_PM1, HAL_LL_UART0_BASE_ADDRESS, HAL_LL_ALTERNATE_FUNCTION_2},
    #endif
    #ifdef UART0_RX_PM2_AF1
    {hal_ll_uart_module_num( UART_MODULE_0 ), GPIO_PM2, HAL_LL_UART0_BASE_ADDRESS, HAL_LL_ALTERNATE_FUNCTION_1},
    #endif
    #ifdef UART1_RX_PJ1_AF2
    {hal_ll_uart_module_num( UART_MODULE_1 ), GPIO_PJ1, HAL_LL_UART1_BASE_ADDRESS, HAL_LL_ALTERNATE_FUNCTION_2},
    #endif
    #ifdef UART1_RX_PJ2_AF1
    {hal_ll_uart_module_num( UART_MODULE_1 ), GPIO_PJ2, HAL_LL_UART1_BASE_ADDRESS, HAL_LL_ALTERNATE_FUNCTION_1},
    #endif
    #ifdef UART1_RX_PK1_AF2
    {hal_ll_uart_module_num( UART_MODULE_1 ), GPIO_PK1, HAL_LL_UART1_BASE_ADDRESS, HAL_LL_ALTERNATE_FUNCTION_2},
    #endif
    #ifdef UART1_RX_PK2_AF1
    {hal_ll_uart_module_num( UART_MODULE_1 ), GPIO_PK2, HAL_LL_UART1_BASE_ADDRESS, HAL_LL_ALTERNATE_FUNCTION_1},
    #endif
    #ifdef UART2_RX_PB2_AF2
    {hal_ll_uart_module_num( UART_MODULE_2 ), GPIO_PB2, HAL_LL_UART2_BASE_ADDRESS, HAL_LL_ALTERNATE_FUNCTION_2},
    #endif
    #ifdef UART2_RX_PB3_AF1
    {hal_ll_uart_module_num( UART_MODULE_2 ), GPIO_PB3, HAL_LL_UART2_BASE_ADDRESS, HAL_LL_ALTERNATE_FUNCTION_1},
    #endif
    #ifdef UART2_RX_PL0_AF2
    {hal_ll_uart_module_num( UART_MODULE_2 ), GPIO_PL0, HAL_LL_UART2_BASE_ADDRESS, HAL_LL_ALTERNATE_FUNCTION_2},
    #endif
    #ifdef UART2_RX_PL1_AF1
    {hal_ll_uart_module_num( UART_MODULE_2 ), GPIO_PL1, HAL_LL_UART2_BASE_ADDRESS, HAL_LL_ALTERNATE_FUNCTION_1},
    #endif
    #ifdef UART3_RX_PA6_AF1
    {hal_ll_uart_module_num( UART_MODULE_3 ), GPIO_PA6, HAL_LL_UART3_BASE_ADDRESS, HAL_LL_ALTERNATE_FUNCTION_1},
    #endif
    #ifdef UART3_RX_PA7_AF2
    {hal_ll_uart_module_num( UART_MODULE_3 ), GPIO_PA7, HAL_LL_UART3_BASE_ADDRESS, HAL_LL_ALTERNATE_FUNCTION_2},
    #endif
    #ifdef UART3_RX_PG2_AF1
    {hal_ll_uart_module_num( UART_MODULE_3 ), GPIO_PG2, HAL_LL_UART3_BASE_ADDRESS, HAL_LL_ALTERNATE_FUNCTION_1},
    #endif
    #ifdef UART3_RX_PG3_AF2
    {hal_ll_uart_module_num( UART_MODULE_3 ), GPIO_PG3, HAL_LL_UART3_BASE_ADDRESS, HAL_LL_ALTERNATE_FUNCTION_2},
    #endif
    #ifdef UART4_RX_PC3_AF2
    {hal_ll_uart_module_num( UART_MODULE_4 ), GPIO_PC3, HAL_LL_UART4_BASE_ADDRESS, HAL_LL_ALTERNATE_FUNCTION_2},
    #endif
    #ifdef UART4_RX_PC4_AF1
    {hal_ll_uart_module_num( UART_MODULE_4 ), GPIO_PC4, HAL_LL_UART4_BASE_ADDRESS, HAL_LL_ALTERNATE_FUNCTION_1},
    #endif
    #ifdef UART4_RX_PV6_AF2
    {hal_ll_uart_module_num( UART_MODULE_4 ), GPIO_PV6, HAL_LL_UART4_BASE_ADDRESS, HAL_LL_ALTERNATE_FUNCTION_2},
    #endif
    #ifdef UART4_RX_PV7_AF1
    {hal_ll_uart_module_num( UART_MODULE_4 ), GPIO_PV7, HAL_LL_UART4_BASE_ADDRESS, HAL_LL_ALTERNATE_FUNCTION_1},
    #endif
    #ifdef UART5_RX_PN2_AF1
    {hal_ll_uart_module_num( UART_MODULE_5 ), GPIO_PN2, HAL_LL_UART5_BASE_ADDRESS, HAL_LL_ALTERNATE_FUNCTION_1},
    #endif
    #ifdef UART5_RX_PN3_AF2
    {hal_ll_uart_module_num( UART_MODULE_5 ), GPIO_PN3, HAL_LL_UART5_BASE_ADDRESS, HAL_LL_ALTERNATE_FUNCTION_2},
    #endif
    #ifdef UART6_RX_PK5_AF1
    {hal_ll_uart_module_num( UART_MODULE_6 ), GPIO_PK5, HAL_LL_UART6_BASE_ADDRESS, HAL_LL_ALTERNATE_FUNCTION_1},
    #endif
    #ifdef UART6_RX_PK6_AF2
    {hal_ll_uart_module_num( UART_MODULE_6 ), GPIO_PK6, HAL_LL_UART6_BASE_ADDRESS, HAL_LL_ALTERNATE_FUNCTION_2},
    #endif
    #ifdef UART7_RX_PR0_AF1
    {hal_ll_uart_module_num( UART_MODULE_7 ), GPIO_PR0, HAL_LL_UART7_BASE_ADDRESS, HAL_LL_ALTERNATE_FUNCTION_1},
    #endif
    #ifdef UART7_RX_PR1_AF2
    {hal_ll_uart_module_num( UART_MODULE_7 ), GPIO_PR1, HAL_LL_UART7_BASE_ADDRESS, HAL_LL_ALTERNATE_FUNCTION_2},
    #endif

    {HAL_LL_MODULE_ERROR, HAL_LL_PIN_NC, HAL_LL_MODULE_ERROR, HAL_LL_PIN_NC}
};

#ifdef __cplusplus
}
#endif

#endif // _HAL_LL_UART_PIN_MAP_H_
// ------------------------------------------------------------------------- END
