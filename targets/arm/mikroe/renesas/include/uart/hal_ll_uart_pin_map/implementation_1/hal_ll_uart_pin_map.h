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
    #ifdef SCI0_TX_P100_AF4
    {hal_ll_uart_module_num( SCI_MODULE_0 ), GPIO_P100, HAL_LL_SCI0_BASE_ADDR, 4},
    #endif
    #ifdef SCI0_TX_P101_AF4
    {hal_ll_uart_module_num( SCI_MODULE_0 ), GPIO_P101, HAL_LL_SCI0_BASE_ADDR, 4},
    #endif
    #ifdef SCI0_TX_P110_AF4
    {hal_ll_uart_module_num( SCI_MODULE_0 ), GPIO_P110, HAL_LL_SCI0_BASE_ADDR, 4},
    #endif
    #ifdef SCI0_TX_P112_AF4
    {hal_ll_uart_module_num( SCI_MODULE_0 ), GPIO_P112, HAL_LL_SCI0_BASE_ADDR, 4},
    #endif
    #ifdef SCI0_TX_P205_AF4
    {hal_ll_uart_module_num( SCI_MODULE_0 ), GPIO_P205, HAL_LL_SCI0_BASE_ADDR, 4},
    #endif
    #ifdef SCI0_TX_P206_AF4
    {hal_ll_uart_module_num( SCI_MODULE_0 ), GPIO_P206, HAL_LL_SCI0_BASE_ADDR, 4},
    #endif
    #ifdef SCI0_TX_P213_AF4
    {hal_ll_uart_module_num( SCI_MODULE_0 ), GPIO_P213, HAL_LL_SCI0_BASE_ADDR, 4},
    #endif
    #ifdef SCI0_TX_P302_AF4
    {hal_ll_uart_module_num( SCI_MODULE_0 ), GPIO_P302, HAL_LL_SCI0_BASE_ADDR, 4},
    #endif
    #ifdef SCI0_TX_P407_AF4
    {hal_ll_uart_module_num( SCI_MODULE_0 ), GPIO_P407, HAL_LL_SCI0_BASE_ADDR, 4},
    #endif
    #ifdef SCI0_TX_P411_AF4
    {hal_ll_uart_module_num( SCI_MODULE_0 ), GPIO_P411, HAL_LL_SCI0_BASE_ADDR, 4},
    #endif
    #ifdef SCI0_TX_P501_AF4
    {hal_ll_uart_module_num( SCI_MODULE_0 ), GPIO_P501, HAL_LL_SCI0_BASE_ADDR, 4},
    #endif
    #ifdef SCI0_TX_P603_AF4
    {hal_ll_uart_module_num( SCI_MODULE_0 ), GPIO_P603, HAL_LL_SCI0_BASE_ADDR, 4},
    #endif
    #ifdef SCI0_TX_P609_AF4
    {hal_ll_uart_module_num( SCI_MODULE_0 ), GPIO_P609, HAL_LL_SCI0_BASE_ADDR, 4},
    #endif
    #ifdef SCI0_TX_PA09_AF4
    {hal_ll_uart_module_num( SCI_MODULE_0 ), GPIO_PA09, HAL_LL_SCI0_BASE_ADDR, 4},
    #endif
    #ifdef SCI0_TX_PA14_AF4
    {hal_ll_uart_module_num( SCI_MODULE_0 ), GPIO_PA14, HAL_LL_SCI0_BASE_ADDR, 4},
    #endif
    #ifdef SCI0_TX_PB06_AF4
    {hal_ll_uart_module_num( SCI_MODULE_0 ), GPIO_PB06, HAL_LL_SCI0_BASE_ADDR, 4},
    #endif
    #ifdef SCI0_TX_PE00_AF4
    {hal_ll_uart_module_num( SCI_MODULE_0 ), GPIO_PE00, HAL_LL_SCI0_BASE_ADDR, 4},
    #endif
    #ifdef SCI0_TX_PE04_AF4
    {hal_ll_uart_module_num( SCI_MODULE_0 ), GPIO_PE04, HAL_LL_SCI0_BASE_ADDR, 4},
    #endif
    #ifdef SCI1_TX_P115_AF5
    {hal_ll_uart_module_num( SCI_MODULE_1 ), GPIO_P115, HAL_LL_SCI1_BASE_ADDR, 5},
    #endif
    #ifdef SCI1_TX_P206_AF5
    {hal_ll_uart_module_num( SCI_MODULE_1 ), GPIO_P206, HAL_LL_SCI1_BASE_ADDR, 5},
    #endif
    #ifdef SCI1_TX_P212_AF5
    {hal_ll_uart_module_num( SCI_MODULE_1 ), GPIO_P212, HAL_LL_SCI1_BASE_ADDR, 5},
    #endif
    #ifdef SCI1_TX_P213_AF5
    {hal_ll_uart_module_num( SCI_MODULE_1 ), GPIO_P213, HAL_LL_SCI1_BASE_ADDR, 5},
    #endif
    #ifdef SCI1_TX_P300_AF5
    {hal_ll_uart_module_num( SCI_MODULE_1 ), GPIO_P300, HAL_LL_SCI1_BASE_ADDR, 5},
    #endif
    #ifdef SCI1_TX_P400_AF5
    {hal_ll_uart_module_num( SCI_MODULE_1 ), GPIO_P400, HAL_LL_SCI1_BASE_ADDR, 5},
    #endif
    #ifdef SCI1_TX_P401_AF5
    {hal_ll_uart_module_num( SCI_MODULE_1 ), GPIO_P401, HAL_LL_SCI1_BASE_ADDR, 5},
    #endif
    #ifdef SCI1_TX_P408_AF5
    {hal_ll_uart_module_num( SCI_MODULE_1 ), GPIO_P408, HAL_LL_SCI1_BASE_ADDR, 5},
    #endif
    #ifdef SCI1_TX_P410_AF5
    {hal_ll_uart_module_num( SCI_MODULE_1 ), GPIO_P410, HAL_LL_SCI1_BASE_ADDR, 5},
    #endif
    #ifdef SCI1_TX_P501_AF5
    {hal_ll_uart_module_num( SCI_MODULE_1 ), GPIO_P501, HAL_LL_SCI1_BASE_ADDR, 5},
    #endif
    #ifdef SCI1_TX_P506_AF5
    {hal_ll_uart_module_num( SCI_MODULE_1 ), GPIO_P506, HAL_LL_SCI1_BASE_ADDR, 5},
    #endif
    #ifdef SCI1_TX_P707_AF5
    {hal_ll_uart_module_num( SCI_MODULE_1 ), GPIO_P707, HAL_LL_SCI1_BASE_ADDR, 5},
    #endif
    #ifdef SCI1_TX_P709_AF5
    {hal_ll_uart_module_num( SCI_MODULE_1 ), GPIO_P709, HAL_LL_SCI1_BASE_ADDR, 5},
    #endif
    #ifdef SCI1_TX_PA12_AF5
    {hal_ll_uart_module_num( SCI_MODULE_1 ), GPIO_PA12, HAL_LL_SCI1_BASE_ADDR, 5},
    #endif
    #ifdef SCI1_TX_PB09_AF5
    {hal_ll_uart_module_num( SCI_MODULE_1 ), GPIO_PB09, HAL_LL_SCI1_BASE_ADDR, 5},
    #endif
    #ifdef SCI1_TX_PC10_AF5
    {hal_ll_uart_module_num( SCI_MODULE_1 ), GPIO_PC10, HAL_LL_SCI1_BASE_ADDR, 5},
    #endif
    #ifdef SCI1_TX_PD08_AF5
    {hal_ll_uart_module_num( SCI_MODULE_1 ), GPIO_PD08, HAL_LL_SCI1_BASE_ADDR, 5},
    #endif
    #ifdef SCI2_TX_P102_AF4
    {hal_ll_uart_module_num( SCI_MODULE_2 ), GPIO_P102, HAL_LL_SCI2_BASE_ADDR, 4},
    #endif
    #ifdef SCI2_TX_P106_AF4
    {hal_ll_uart_module_num( SCI_MODULE_2 ), GPIO_P106, HAL_LL_SCI2_BASE_ADDR, 4},
    #endif
    #ifdef SCI2_TX_P112_AF4
    {hal_ll_uart_module_num( SCI_MODULE_2 ), GPIO_P112, HAL_LL_SCI2_BASE_ADDR, 4},
    #endif
    #ifdef SCI2_TX_P302_AF4
    {hal_ll_uart_module_num( SCI_MODULE_2 ), GPIO_P302, HAL_LL_SCI2_BASE_ADDR, 4},
    #endif
    #ifdef SCI2_TX_P406_AF4
    {hal_ll_uart_module_num( SCI_MODULE_2 ), GPIO_P406, HAL_LL_SCI2_BASE_ADDR, 4},
    #endif
    #ifdef SCI2_TX_P801_AF4
    {hal_ll_uart_module_num( SCI_MODULE_2 ), GPIO_P801, HAL_LL_SCI2_BASE_ADDR, 4},
    #endif
    #ifdef SCI2_TX_PA03_AF4
    {hal_ll_uart_module_num( SCI_MODULE_2 ), GPIO_PA03, HAL_LL_SCI2_BASE_ADDR, 4},
    #endif
    #ifdef SCI2_TX_PB03_AF4
    {hal_ll_uart_module_num( SCI_MODULE_2 ), GPIO_PB03, HAL_LL_SCI2_BASE_ADDR, 4},
    #endif
    #ifdef SCI2_TX_PC06_AF4
    {hal_ll_uart_module_num( SCI_MODULE_2 ), GPIO_PC06, HAL_LL_SCI2_BASE_ADDR, 4},
    #endif
    #ifdef SCI2_TX_PD12_AF4
    {hal_ll_uart_module_num( SCI_MODULE_2 ), GPIO_PD12, HAL_LL_SCI2_BASE_ADDR, 4},
    #endif
    #ifdef SCI3_TX_P103_AF5
    {hal_ll_uart_module_num( SCI_MODULE_3 ), GPIO_P103, HAL_LL_SCI3_BASE_ADDR, 5},
    #endif
    #ifdef SCI3_TX_P310_AF5
    {hal_ll_uart_module_num( SCI_MODULE_3 ), GPIO_P310, HAL_LL_SCI3_BASE_ADDR, 5},
    #endif
    #ifdef SCI3_TX_P313_AF5
    {hal_ll_uart_module_num( SCI_MODULE_3 ), GPIO_P313, HAL_LL_SCI3_BASE_ADDR, 5},
    #endif
    #ifdef SCI3_TX_P409_AF5
    {hal_ll_uart_module_num( SCI_MODULE_3 ), GPIO_P409, HAL_LL_SCI3_BASE_ADDR, 5},
    #endif
    #ifdef SCI3_TX_P501_AF5
    {hal_ll_uart_module_num( SCI_MODULE_3 ), GPIO_P501, HAL_LL_SCI3_BASE_ADDR, 5},
    #endif
    #ifdef SCI3_TX_P707_AF5
    {hal_ll_uart_module_num( SCI_MODULE_3 ), GPIO_P707, HAL_LL_SCI3_BASE_ADDR, 5},
    #endif
    #ifdef SCI3_TX_P900_AF5
    {hal_ll_uart_module_num( SCI_MODULE_3 ), GPIO_P900, HAL_LL_SCI3_BASE_ADDR, 5},
    #endif
    #ifdef SCI3_TX_PB05_AF5
    {hal_ll_uart_module_num( SCI_MODULE_3 ), GPIO_PB05, HAL_LL_SCI3_BASE_ADDR, 5},
    #endif
    #ifdef SCI3_TX_PB13_AF5
    {hal_ll_uart_module_num( SCI_MODULE_3 ), GPIO_PB13, HAL_LL_SCI3_BASE_ADDR, 5},
    #endif
    #ifdef SCI3_TX_PD01_AF5
    {hal_ll_uart_module_num( SCI_MODULE_3 ), GPIO_PD01, HAL_LL_SCI3_BASE_ADDR, 5},
    #endif
    #ifdef SCI3_TX_PE06_AF5
    {hal_ll_uart_module_num( SCI_MODULE_3 ), GPIO_PE06, HAL_LL_SCI3_BASE_ADDR, 5},
    #endif
    #ifdef SCI4_TX_P205_AF4
    {hal_ll_uart_module_num( SCI_MODULE_4 ), GPIO_P205, HAL_LL_SCI4_BASE_ADDR, 4},
    #endif
    #ifdef SCI4_TX_P207_AF4
    {hal_ll_uart_module_num( SCI_MODULE_4 ), GPIO_P207, HAL_LL_SCI4_BASE_ADDR, 4},
    #endif
    #ifdef SCI4_TX_P415_AF4
    {hal_ll_uart_module_num( SCI_MODULE_4 ), GPIO_P415, HAL_LL_SCI4_BASE_ADDR, 4},
    #endif
    #ifdef SCI4_TX_P512_AF4
    {hal_ll_uart_module_num( SCI_MODULE_4 ), GPIO_P512, HAL_LL_SCI4_BASE_ADDR, 4},
    #endif
    #ifdef SCI4_TX_P714_AF4
    {hal_ll_uart_module_num( SCI_MODULE_4 ), GPIO_P714, HAL_LL_SCI4_BASE_ADDR, 4},
    #endif
    #ifdef SCI4_TX_P900_AF4
    {hal_ll_uart_module_num( SCI_MODULE_4 ), GPIO_P900, HAL_LL_SCI4_BASE_ADDR, 4},
    #endif
    #ifdef SCI4_TX_PB09_AF4
    {hal_ll_uart_module_num( SCI_MODULE_4 ), GPIO_PB09, HAL_LL_SCI4_BASE_ADDR, 4},
    #endif
    #ifdef SCI4_TX_PB10_AF4
    {hal_ll_uart_module_num( SCI_MODULE_4 ), GPIO_PB10, HAL_LL_SCI4_BASE_ADDR, 4},
    #endif
    #ifdef SCI4_TX_PC12_AF4
    {hal_ll_uart_module_num( SCI_MODULE_4 ), GPIO_PC12, HAL_LL_SCI4_BASE_ADDR, 4},
    #endif
    #ifdef SCI4_TX_PD15_AF4
    {hal_ll_uart_module_num( SCI_MODULE_4 ), GPIO_PD15, HAL_LL_SCI4_BASE_ADDR, 4},
    #endif
    #ifdef SCI5_TX_P302_AF5
    {hal_ll_uart_module_num( SCI_MODULE_5 ), GPIO_P302, HAL_LL_SCI5_BASE_ADDR, 5},
    #endif
    #ifdef SCI5_TX_P404_AF5
    {hal_ll_uart_module_num( SCI_MODULE_5 ), GPIO_P404, HAL_LL_SCI5_BASE_ADDR, 5},
    #endif
    #ifdef SCI5_TX_P501_AF5
    {hal_ll_uart_module_num( SCI_MODULE_5 ), GPIO_P501, HAL_LL_SCI5_BASE_ADDR, 5},
    #endif
    #ifdef SCI5_TX_P506_AF5
    {hal_ll_uart_module_num( SCI_MODULE_5 ), GPIO_P506, HAL_LL_SCI5_BASE_ADDR, 5},
    #endif
    #ifdef SCI5_TX_P608_AF5
    {hal_ll_uart_module_num( SCI_MODULE_5 ), GPIO_P608, HAL_LL_SCI5_BASE_ADDR, 5},
    #endif
    #ifdef SCI5_TX_P805_AF5
    {hal_ll_uart_module_num( SCI_MODULE_5 ), GPIO_P805, HAL_LL_SCI5_BASE_ADDR, 5},
    #endif
    #ifdef SCI5_TX_PA09_AF5
    {hal_ll_uart_module_num( SCI_MODULE_5 ), GPIO_PA09, HAL_LL_SCI5_BASE_ADDR, 5},
    #endif
    #ifdef SCI5_TX_PB03_AF5
    {hal_ll_uart_module_num( SCI_MODULE_5 ), GPIO_PB03, HAL_LL_SCI5_BASE_ADDR, 5},
    #endif
    #ifdef SCI6_TX_P301_AF4
    {hal_ll_uart_module_num( SCI_MODULE_6 ), GPIO_P301, HAL_LL_SCI6_BASE_ADDR, 4},
    #endif
    #ifdef SCI6_TX_P305_AF4
    {hal_ll_uart_module_num( SCI_MODULE_6 ), GPIO_P305, HAL_LL_SCI6_BASE_ADDR, 4},
    #endif
    #ifdef SCI6_TX_P506_AF4
    {hal_ll_uart_module_num( SCI_MODULE_6 ), GPIO_P506, HAL_LL_SCI6_BASE_ADDR, 4},
    #endif
    #ifdef SCI6_TX_P908_AF4
    {hal_ll_uart_module_num( SCI_MODULE_6 ), GPIO_P908, HAL_LL_SCI6_BASE_ADDR, 4},
    #endif
    #ifdef SCI6_TX_PC14_AF4
    {hal_ll_uart_module_num( SCI_MODULE_6 ), GPIO_PC14, HAL_LL_SCI6_BASE_ADDR, 4},
    #endif
    #ifdef SCI7_TX_P401_AF5
    {hal_ll_uart_module_num( SCI_MODULE_7 ), GPIO_P401, HAL_LL_SCI7_BASE_ADDR, 5},
    #endif
    #ifdef SCI7_TX_P613_AF5
    {hal_ll_uart_module_num( SCI_MODULE_7 ), GPIO_P613, HAL_LL_SCI7_BASE_ADDR, 5},
    #endif
    #ifdef SCI7_TX_P615_AF5
    {hal_ll_uart_module_num( SCI_MODULE_7 ), GPIO_P615, HAL_LL_SCI7_BASE_ADDR, 5},
    #endif
    #ifdef SCI7_TX_P809_AF5
    {hal_ll_uart_module_num( SCI_MODULE_7 ), GPIO_P809, HAL_LL_SCI7_BASE_ADDR, 5},
    #endif
    #ifdef SCI7_TX_PC03_AF5
    {hal_ll_uart_module_num( SCI_MODULE_7 ), GPIO_PC03, HAL_LL_SCI7_BASE_ADDR, 5},
    #endif
    #ifdef SCI8_TX_P105_AF4
    {hal_ll_uart_module_num( SCI_MODULE_8 ), GPIO_P105, HAL_LL_SCI8_BASE_ADDR, 4},
    #endif
    #ifdef SCI8_TX_P501_AF4
    {hal_ll_uart_module_num( SCI_MODULE_8 ), GPIO_P501, HAL_LL_SCI8_BASE_ADDR, 4},
    #endif
    #ifdef SCI8_TX_P805_AF4
    {hal_ll_uart_module_num( SCI_MODULE_8 ), GPIO_P805, HAL_LL_SCI8_BASE_ADDR, 4},
    #endif
    #ifdef SCI8_TX_PA00_AF4
    {hal_ll_uart_module_num( SCI_MODULE_8 ), GPIO_PA00, HAL_LL_SCI8_BASE_ADDR, 4},
    #endif
    #ifdef SCI8_TX_PD02_AF4
    {hal_ll_uart_module_num( SCI_MODULE_8 ), GPIO_PD02, HAL_LL_SCI8_BASE_ADDR, 4},
    #endif
    #ifdef SCI9_TX_P100_AF5
    {hal_ll_uart_module_num( SCI_MODULE_9 ), GPIO_P100, HAL_LL_SCI9_BASE_ADDR, 5},
    #endif
    #ifdef SCI9_TX_P101_AF4
    {hal_ll_uart_module_num( SCI_MODULE_9 ), GPIO_P101, HAL_LL_SCI9_BASE_ADDR, 4},
    #endif
    #ifdef SCI9_TX_P102_AF5
    {hal_ll_uart_module_num( SCI_MODULE_9 ), GPIO_P102, HAL_LL_SCI9_BASE_ADDR, 5},
    #endif
    #ifdef SCI9_TX_P108_AF4
    {hal_ll_uart_module_num( SCI_MODULE_9 ), GPIO_P108, HAL_LL_SCI9_BASE_ADDR, 4},
    #endif
    #ifdef SCI9_TX_P109_AF5
    {hal_ll_uart_module_num( SCI_MODULE_9 ), GPIO_P109, HAL_LL_SCI9_BASE_ADDR, 5},
    #endif
    #ifdef SCI9_TX_P112_AF4
    {hal_ll_uart_module_num( SCI_MODULE_9 ), GPIO_P112, HAL_LL_SCI9_BASE_ADDR, 4},
    #endif
    #ifdef SCI9_TX_P203_AF5
    {hal_ll_uart_module_num( SCI_MODULE_9 ), GPIO_P203, HAL_LL_SCI9_BASE_ADDR, 5},
    #endif
    #ifdef SCI9_TX_P205_AF4
    {hal_ll_uart_module_num( SCI_MODULE_9 ), GPIO_P205, HAL_LL_SCI9_BASE_ADDR, 4},
    #endif
    #ifdef SCI9_TX_P209_AF5
    {hal_ll_uart_module_num( SCI_MODULE_9 ), GPIO_P209, HAL_LL_SCI9_BASE_ADDR, 5},
    #endif
    #ifdef SCI9_TX_P304_AF5
    {hal_ll_uart_module_num( SCI_MODULE_9 ), GPIO_P304, HAL_LL_SCI9_BASE_ADDR, 5},
    #endif
    #ifdef SCI9_TX_P400_AF5
    {hal_ll_uart_module_num( SCI_MODULE_9 ), GPIO_P400, HAL_LL_SCI9_BASE_ADDR, 5},
    #endif
    #ifdef SCI9_TX_P407_AF5
    {hal_ll_uart_module_num( SCI_MODULE_9 ), GPIO_P407, HAL_LL_SCI9_BASE_ADDR, 5},
    #endif
    #ifdef SCI9_TX_P409_AF5
    {hal_ll_uart_module_num( SCI_MODULE_9 ), GPIO_P409, HAL_LL_SCI9_BASE_ADDR, 5},
    #endif
    #ifdef SCI9_TX_P510_AF5
    {hal_ll_uart_module_num( SCI_MODULE_9 ), GPIO_P510, HAL_LL_SCI9_BASE_ADDR, 5},
    #endif
    #ifdef SCI9_TX_P602_AF5
    {hal_ll_uart_module_num( SCI_MODULE_9 ), GPIO_P602, HAL_LL_SCI9_BASE_ADDR, 5},
    #endif
    #ifdef SCI9_TX_PA14_AF5
    {hal_ll_uart_module_num( SCI_MODULE_9 ), GPIO_PA14, HAL_LL_SCI9_BASE_ADDR, 5},
    #endif
    #ifdef SCI9_TX_PB03_AF5
    {hal_ll_uart_module_num( SCI_MODULE_9 ), GPIO_PB03, HAL_LL_SCI9_BASE_ADDR, 5},
    #endif
    #ifdef SCI9_TX_PD05_AF5
    {hal_ll_uart_module_num( SCI_MODULE_9 ), GPIO_PD05, HAL_LL_SCI9_BASE_ADDR, 5},
    #endif
    #ifdef SCI9_TX_PD15_AF5
    {hal_ll_uart_module_num( SCI_MODULE_9 ), GPIO_PD15, HAL_LL_SCI9_BASE_ADDR, 5},
    #endif
    #ifdef SCI9_TX_PE00_AF5
    {hal_ll_uart_module_num( SCI_MODULE_9 ), GPIO_PE00, HAL_LL_SCI9_BASE_ADDR, 5},
    #endif
    #ifdef UART0_TX_P101_AF5
    {hal_ll_uart_module_num( UART_MODULE_0 ), GPIO_P101, HAL_LL_UARTA0_BASE_ADDR, 5},
    #endif
    #ifdef UART0_TX_P109_AF22
    {hal_ll_uart_module_num( UART_MODULE_0 ), GPIO_P109, HAL_LL_UARTA0_BASE_ADDR, 22},
    #endif
    #ifdef UART0_TX_P109_AF5
    {hal_ll_uart_module_num( UART_MODULE_0 ), GPIO_P109, HAL_LL_UARTA0_BASE_ADDR, 5},
    #endif
    #ifdef UART0_TX_P208_AF5
    {hal_ll_uart_module_num( UART_MODULE_0 ), GPIO_P208, HAL_LL_UARTA0_BASE_ADDR, 5},
    #endif
    #ifdef UART0_TX_P213_AF5
    {hal_ll_uart_module_num( UART_MODULE_0 ), GPIO_P213, HAL_LL_UARTA0_BASE_ADDR, 5},
    #endif
    #ifdef UART0_TX_P306_AF22
    {hal_ll_uart_module_num( UART_MODULE_0 ), GPIO_P306, HAL_LL_UARTA0_BASE_ADDR, 22},
    #endif
    #ifdef UART0_TX_P402_AF5
    {hal_ll_uart_module_num( UART_MODULE_0 ), GPIO_P402, HAL_LL_UARTA0_BASE_ADDR, 5},
    #endif
    #ifdef UART0_TX_P403_AF22
    {hal_ll_uart_module_num( UART_MODULE_0 ), GPIO_P403, HAL_LL_UARTA0_BASE_ADDR, 22},
    #endif
    #ifdef UART0_TX_P501_AF5
    {hal_ll_uart_module_num( UART_MODULE_0 ), GPIO_P501, HAL_LL_UARTA0_BASE_ADDR, 5},
    #endif
    #ifdef UART0_TX_P508_AF22
    {hal_ll_uart_module_num( UART_MODULE_0 ), GPIO_P508, HAL_LL_UARTA0_BASE_ADDR, 22},
    #endif
    #ifdef UART1_TX_P014_AF22
    {hal_ll_uart_module_num( UART_MODULE_1 ), GPIO_P014, HAL_LL_UARTA1_BASE_ADDR, 22},
    #endif
    #ifdef UART1_TX_P103_AF5
    {hal_ll_uart_module_num( UART_MODULE_1 ), GPIO_P103, HAL_LL_UARTA1_BASE_ADDR, 5},
    #endif
    #ifdef UART1_TX_P106_AF5
    {hal_ll_uart_module_num( UART_MODULE_1 ), GPIO_P106, HAL_LL_UARTA1_BASE_ADDR, 5},
    #endif
    #ifdef UART1_TX_P206_AF5
    {hal_ll_uart_module_num( UART_MODULE_1 ), GPIO_P206, HAL_LL_UARTA1_BASE_ADDR, 5},
    #endif
    #ifdef UART1_TX_P302_AF5
    {hal_ll_uart_module_num( UART_MODULE_1 ), GPIO_P302, HAL_LL_UARTA1_BASE_ADDR, 5},
    #endif
    #ifdef UART1_TX_P408_AF22
    {hal_ll_uart_module_num( UART_MODULE_1 ), GPIO_P408, HAL_LL_UARTA1_BASE_ADDR, 22},
    #endif
    #ifdef UART1_TX_P411_AF5
    {hal_ll_uart_module_num( UART_MODULE_1 ), GPIO_P411, HAL_LL_UARTA1_BASE_ADDR, 5},
    #endif
    #ifdef UART1_TX_P512_AF22
    {hal_ll_uart_module_num( UART_MODULE_1 ), GPIO_P512, HAL_LL_UARTA1_BASE_ADDR, 22},
    #endif
    #ifdef UART1_TX_P815_AF22
    {hal_ll_uart_module_num( UART_MODULE_1 ), GPIO_P815, HAL_LL_UARTA1_BASE_ADDR, 22},
    #endif

    {HAL_LL_MODULE_ERROR, HAL_LL_PIN_NC, HAL_LL_MODULE_ERROR, HAL_LL_PIN_NC}
};

/*!< UART RX Pins. */
static const hal_ll_uart_pin_map_t hal_ll_uart_rx_map[] = {
    #ifdef SCI0_RX_P100_AF4
    {hal_ll_uart_module_num( SCI_MODULE_0 ), GPIO_P100, HAL_LL_SCI0_BASE_ADDR, 4},
    #endif
    #ifdef SCI0_RX_P101_AF4
    {hal_ll_uart_module_num( SCI_MODULE_0 ), GPIO_P101, HAL_LL_SCI0_BASE_ADDR, 4},
    #endif
    #ifdef SCI0_RX_P104_AF4
    {hal_ll_uart_module_num( SCI_MODULE_0 ), GPIO_P104, HAL_LL_SCI0_BASE_ADDR, 4},
    #endif
    #ifdef SCI0_RX_P113_AF4
    {hal_ll_uart_module_num( SCI_MODULE_0 ), GPIO_P113, HAL_LL_SCI0_BASE_ADDR, 4},
    #endif
    #ifdef SCI0_RX_P204_AF4
    {hal_ll_uart_module_num( SCI_MODULE_0 ), GPIO_P204, HAL_LL_SCI0_BASE_ADDR, 4},
    #endif
    #ifdef SCI0_RX_P206_AF4
    {hal_ll_uart_module_num( SCI_MODULE_0 ), GPIO_P206, HAL_LL_SCI0_BASE_ADDR, 4},
    #endif
    #ifdef SCI0_RX_P212_AF4
    {hal_ll_uart_module_num( SCI_MODULE_0 ), GPIO_P212, HAL_LL_SCI0_BASE_ADDR, 4},
    #endif
    #ifdef SCI0_RX_P301_AF4
    {hal_ll_uart_module_num( SCI_MODULE_0 ), GPIO_P301, HAL_LL_SCI0_BASE_ADDR, 4},
    #endif
    #ifdef SCI0_RX_P408_AF4
    {hal_ll_uart_module_num( SCI_MODULE_0 ), GPIO_P408, HAL_LL_SCI0_BASE_ADDR, 4},
    #endif
    #ifdef SCI0_RX_P410_AF4
    {hal_ll_uart_module_num( SCI_MODULE_0 ), GPIO_P410, HAL_LL_SCI0_BASE_ADDR, 4},
    #endif
    #ifdef SCI0_RX_P500_AF4
    {hal_ll_uart_module_num( SCI_MODULE_0 ), GPIO_P500, HAL_LL_SCI0_BASE_ADDR, 4},
    #endif
    #ifdef SCI0_RX_P602_AF4
    {hal_ll_uart_module_num( SCI_MODULE_0 ), GPIO_P602, HAL_LL_SCI0_BASE_ADDR, 4},
    #endif
    #ifdef SCI0_RX_P610_AF4
    {hal_ll_uart_module_num( SCI_MODULE_0 ), GPIO_P610, HAL_LL_SCI0_BASE_ADDR, 4},
    #endif
    #ifdef SCI0_RX_PA10_AF4
    {hal_ll_uart_module_num( SCI_MODULE_0 ), GPIO_PA10, HAL_LL_SCI0_BASE_ADDR, 4},
    #endif
    #ifdef SCI0_RX_PA15_AF4
    {hal_ll_uart_module_num( SCI_MODULE_0 ), GPIO_PA15, HAL_LL_SCI0_BASE_ADDR, 4},
    #endif
    #ifdef SCI0_RX_PB07_AF4
    {hal_ll_uart_module_num( SCI_MODULE_0 ), GPIO_PB07, HAL_LL_SCI0_BASE_ADDR, 4},
    #endif
    #ifdef SCI0_RX_PE01_AF4
    {hal_ll_uart_module_num( SCI_MODULE_0 ), GPIO_PE01, HAL_LL_SCI0_BASE_ADDR, 4},
    #endif
    #ifdef SCI0_RX_PE03_AF4
    {hal_ll_uart_module_num( SCI_MODULE_0 ), GPIO_PE03, HAL_LL_SCI0_BASE_ADDR, 4},
    #endif
    #ifdef SCI1_RX_P013_AF5
    {hal_ll_uart_module_num( SCI_MODULE_1 ), GPIO_P013, HAL_LL_SCI1_BASE_ADDR, 5},
    #endif
    #ifdef SCI1_RX_P108_AF5
    {hal_ll_uart_module_num( SCI_MODULE_1 ), GPIO_P108, HAL_LL_SCI1_BASE_ADDR, 5},
    #endif
    #ifdef SCI1_RX_P212_AF5
    {hal_ll_uart_module_num( SCI_MODULE_1 ), GPIO_P212, HAL_LL_SCI1_BASE_ADDR, 5},
    #endif
    #ifdef SCI1_RX_P213_AF5
    {hal_ll_uart_module_num( SCI_MODULE_1 ), GPIO_P213, HAL_LL_SCI1_BASE_ADDR, 5},
    #endif
    #ifdef SCI1_RX_P302_AF5
    {hal_ll_uart_module_num( SCI_MODULE_1 ), GPIO_P302, HAL_LL_SCI1_BASE_ADDR, 5},
    #endif
    #ifdef SCI1_RX_P400_AF5
    {hal_ll_uart_module_num( SCI_MODULE_1 ), GPIO_P400, HAL_LL_SCI1_BASE_ADDR, 5},
    #endif
    #ifdef SCI1_RX_P401_AF5
    {hal_ll_uart_module_num( SCI_MODULE_1 ), GPIO_P401, HAL_LL_SCI1_BASE_ADDR, 5},
    #endif
    #ifdef SCI1_RX_P402_AF5
    {hal_ll_uart_module_num( SCI_MODULE_1 ), GPIO_P402, HAL_LL_SCI1_BASE_ADDR, 5},
    #endif
    #ifdef SCI1_RX_P411_AF5
    {hal_ll_uart_module_num( SCI_MODULE_1 ), GPIO_P411, HAL_LL_SCI1_BASE_ADDR, 5},
    #endif
    #ifdef SCI1_RX_P502_AF5
    {hal_ll_uart_module_num( SCI_MODULE_1 ), GPIO_P502, HAL_LL_SCI1_BASE_ADDR, 5},
    #endif
    #ifdef SCI1_RX_P608_AF5
    {hal_ll_uart_module_num( SCI_MODULE_1 ), GPIO_P608, HAL_LL_SCI1_BASE_ADDR, 5},
    #endif
    #ifdef SCI1_RX_P706_AF5
    {hal_ll_uart_module_num( SCI_MODULE_1 ), GPIO_P706, HAL_LL_SCI1_BASE_ADDR, 5},
    #endif
    #ifdef SCI1_RX_P708_AF5
    {hal_ll_uart_module_num( SCI_MODULE_1 ), GPIO_P708, HAL_LL_SCI1_BASE_ADDR, 5},
    #endif
    #ifdef SCI1_RX_PA11_AF5
    {hal_ll_uart_module_num( SCI_MODULE_1 ), GPIO_PA11, HAL_LL_SCI1_BASE_ADDR, 5},
    #endif
    #ifdef SCI1_RX_PB08_AF5
    {hal_ll_uart_module_num( SCI_MODULE_1 ), GPIO_PB08, HAL_LL_SCI1_BASE_ADDR, 5},
    #endif
    #ifdef SCI1_RX_PC11_AF5
    {hal_ll_uart_module_num( SCI_MODULE_1 ), GPIO_PC11, HAL_LL_SCI1_BASE_ADDR, 5},
    #endif
    #ifdef SCI1_RX_PD09_AF5
    {hal_ll_uart_module_num( SCI_MODULE_1 ), GPIO_PD09, HAL_LL_SCI1_BASE_ADDR, 5},
    #endif
    #ifdef SCI2_RX_P103_AF4
    {hal_ll_uart_module_num( SCI_MODULE_2 ), GPIO_P103, HAL_LL_SCI2_BASE_ADDR, 4},
    #endif
    #ifdef SCI2_RX_P107_AF4
    {hal_ll_uart_module_num( SCI_MODULE_2 ), GPIO_P107, HAL_LL_SCI2_BASE_ADDR, 4},
    #endif
    #ifdef SCI2_RX_P113_AF4
    {hal_ll_uart_module_num( SCI_MODULE_2 ), GPIO_P113, HAL_LL_SCI2_BASE_ADDR, 4},
    #endif
    #ifdef SCI2_RX_P301_AF4
    {hal_ll_uart_module_num( SCI_MODULE_2 ), GPIO_P301, HAL_LL_SCI2_BASE_ADDR, 4},
    #endif
    #ifdef SCI2_RX_P700_AF4
    {hal_ll_uart_module_num( SCI_MODULE_2 ), GPIO_P700, HAL_LL_SCI2_BASE_ADDR, 4},
    #endif
    #ifdef SCI2_RX_P802_AF4
    {hal_ll_uart_module_num( SCI_MODULE_2 ), GPIO_P802, HAL_LL_SCI2_BASE_ADDR, 4},
    #endif
    #ifdef SCI2_RX_PA02_AF4
    {hal_ll_uart_module_num( SCI_MODULE_2 ), GPIO_PA02, HAL_LL_SCI2_BASE_ADDR, 4},
    #endif
    #ifdef SCI2_RX_PB04_AF4
    {hal_ll_uart_module_num( SCI_MODULE_2 ), GPIO_PB04, HAL_LL_SCI2_BASE_ADDR, 4},
    #endif
    #ifdef SCI2_RX_PC07_AF4
    {hal_ll_uart_module_num( SCI_MODULE_2 ), GPIO_PC07, HAL_LL_SCI2_BASE_ADDR, 4},
    #endif
    #ifdef SCI2_RX_PD11_AF4
    {hal_ll_uart_module_num( SCI_MODULE_2 ), GPIO_PD11, HAL_LL_SCI2_BASE_ADDR, 4},
    #endif
    #ifdef SCI3_RX_P102_AF5
    {hal_ll_uart_module_num( SCI_MODULE_3 ), GPIO_P102, HAL_LL_SCI3_BASE_ADDR, 5},
    #endif
    #ifdef SCI3_RX_P309_AF5
    {hal_ll_uart_module_num( SCI_MODULE_3 ), GPIO_P309, HAL_LL_SCI3_BASE_ADDR, 5},
    #endif
    #ifdef SCI3_RX_P314_AF5
    {hal_ll_uart_module_num( SCI_MODULE_3 ), GPIO_P314, HAL_LL_SCI3_BASE_ADDR, 5},
    #endif
    #ifdef SCI3_RX_P408_AF5
    {hal_ll_uart_module_num( SCI_MODULE_3 ), GPIO_P408, HAL_LL_SCI3_BASE_ADDR, 5},
    #endif
    #ifdef SCI3_RX_P500_AF5
    {hal_ll_uart_module_num( SCI_MODULE_3 ), GPIO_P500, HAL_LL_SCI3_BASE_ADDR, 5},
    #endif
    #ifdef SCI3_RX_P706_AF5
    {hal_ll_uart_module_num( SCI_MODULE_3 ), GPIO_P706, HAL_LL_SCI3_BASE_ADDR, 5},
    #endif
    #ifdef SCI3_RX_P901_AF5
    {hal_ll_uart_module_num( SCI_MODULE_3 ), GPIO_P901, HAL_LL_SCI3_BASE_ADDR, 5},
    #endif
    #ifdef SCI3_RX_P905_AF5
    {hal_ll_uart_module_num( SCI_MODULE_3 ), GPIO_P905, HAL_LL_SCI3_BASE_ADDR, 5},
    #endif
    #ifdef SCI3_RX_PB04_AF5
    {hal_ll_uart_module_num( SCI_MODULE_3 ), GPIO_PB04, HAL_LL_SCI3_BASE_ADDR, 5},
    #endif
    #ifdef SCI3_RX_PB12_AF5
    {hal_ll_uart_module_num( SCI_MODULE_3 ), GPIO_PB12, HAL_LL_SCI3_BASE_ADDR, 5},
    #endif
    #ifdef SCI3_RX_PD00_AF5
    {hal_ll_uart_module_num( SCI_MODULE_3 ), GPIO_PD00, HAL_LL_SCI3_BASE_ADDR, 5},
    #endif
    #ifdef SCI3_RX_PE05_AF5
    {hal_ll_uart_module_num( SCI_MODULE_3 ), GPIO_PE05, HAL_LL_SCI3_BASE_ADDR, 5},
    #endif
    #ifdef SCI4_RX_P203_AF4
    {hal_ll_uart_module_num( SCI_MODULE_4 ), GPIO_P203, HAL_LL_SCI4_BASE_ADDR, 4},
    #endif
    #ifdef SCI4_RX_P206_AF4
    {hal_ll_uart_module_num( SCI_MODULE_4 ), GPIO_P206, HAL_LL_SCI4_BASE_ADDR, 4},
    #endif
    #ifdef SCI4_RX_P315_AF4
    {hal_ll_uart_module_num( SCI_MODULE_4 ), GPIO_P315, HAL_LL_SCI4_BASE_ADDR, 4},
    #endif
    #ifdef SCI4_RX_P414_AF4
    {hal_ll_uart_module_num( SCI_MODULE_4 ), GPIO_P414, HAL_LL_SCI4_BASE_ADDR, 4},
    #endif
    #ifdef SCI4_RX_P511_AF4
    {hal_ll_uart_module_num( SCI_MODULE_4 ), GPIO_P511, HAL_LL_SCI4_BASE_ADDR, 4},
    #endif
    #ifdef SCI4_RX_P715_AF4
    {hal_ll_uart_module_num( SCI_MODULE_4 ), GPIO_P715, HAL_LL_SCI4_BASE_ADDR, 4},
    #endif
    #ifdef SCI4_RX_PB08_AF4
    {hal_ll_uart_module_num( SCI_MODULE_4 ), GPIO_PB08, HAL_LL_SCI4_BASE_ADDR, 4},
    #endif
    #ifdef SCI4_RX_PB15_AF4
    {hal_ll_uart_module_num( SCI_MODULE_4 ), GPIO_PB15, HAL_LL_SCI4_BASE_ADDR, 4},
    #endif
    #ifdef SCI4_RX_PD02_AF4
    {hal_ll_uart_module_num( SCI_MODULE_4 ), GPIO_PD02, HAL_LL_SCI4_BASE_ADDR, 4},
    #endif
    #ifdef SCI4_RX_PD14_AF4
    {hal_ll_uart_module_num( SCI_MODULE_4 ), GPIO_PD14, HAL_LL_SCI4_BASE_ADDR, 4},
    #endif
    #ifdef SCI4_RX_PE15_AF4
    {hal_ll_uart_module_num( SCI_MODULE_4 ), GPIO_PE15, HAL_LL_SCI4_BASE_ADDR, 4},
    #endif
    #ifdef SCI5_RX_P301_AF5
    {hal_ll_uart_module_num( SCI_MODULE_5 ), GPIO_P301, HAL_LL_SCI5_BASE_ADDR, 5},
    #endif
    #ifdef SCI5_RX_P405_AF5
    {hal_ll_uart_module_num( SCI_MODULE_5 ), GPIO_P405, HAL_LL_SCI5_BASE_ADDR, 5},
    #endif
    #ifdef SCI5_RX_P502_AF5
    {hal_ll_uart_module_num( SCI_MODULE_5 ), GPIO_P502, HAL_LL_SCI5_BASE_ADDR, 5},
    #endif
    #ifdef SCI5_RX_P507_AF5
    {hal_ll_uart_module_num( SCI_MODULE_5 ), GPIO_P507, HAL_LL_SCI5_BASE_ADDR, 5},
    #endif
    #ifdef SCI5_RX_P510_AF5
    {hal_ll_uart_module_num( SCI_MODULE_5 ), GPIO_P510, HAL_LL_SCI5_BASE_ADDR, 5},
    #endif
    #ifdef SCI5_RX_P513_AF5
    {hal_ll_uart_module_num( SCI_MODULE_5 ), GPIO_P513, HAL_LL_SCI5_BASE_ADDR, 5},
    #endif
    #ifdef SCI5_RX_PA08_AF5
    {hal_ll_uart_module_num( SCI_MODULE_5 ), GPIO_PA08, HAL_LL_SCI5_BASE_ADDR, 5},
    #endif
    #ifdef SCI5_RX_PB02_AF5
    {hal_ll_uart_module_num( SCI_MODULE_5 ), GPIO_PB02, HAL_LL_SCI5_BASE_ADDR, 5},
    #endif
    #ifdef SCI6_RX_P302_AF4
    {hal_ll_uart_module_num( SCI_MODULE_6 ), GPIO_P302, HAL_LL_SCI6_BASE_ADDR, 4},
    #endif
    #ifdef SCI6_RX_P304_AF4
    {hal_ll_uart_module_num( SCI_MODULE_6 ), GPIO_P304, HAL_LL_SCI6_BASE_ADDR, 4},
    #endif
    #ifdef SCI6_RX_P505_AF4
    {hal_ll_uart_module_num( SCI_MODULE_6 ), GPIO_P505, HAL_LL_SCI6_BASE_ADDR, 4},
    #endif
    #ifdef SCI6_RX_P909_AF4
    {hal_ll_uart_module_num( SCI_MODULE_6 ), GPIO_P909, HAL_LL_SCI6_BASE_ADDR, 4},
    #endif
    #ifdef SCI6_RX_PC13_AF4
    {hal_ll_uart_module_num( SCI_MODULE_6 ), GPIO_PC13, HAL_LL_SCI6_BASE_ADDR, 4},
    #endif
    #ifdef SCI7_RX_P402_AF5
    {hal_ll_uart_module_num( SCI_MODULE_7 ), GPIO_P402, HAL_LL_SCI7_BASE_ADDR, 5},
    #endif
    #ifdef SCI7_RX_P614_AF5
    {hal_ll_uart_module_num( SCI_MODULE_7 ), GPIO_P614, HAL_LL_SCI7_BASE_ADDR, 5},
    #endif
    #ifdef SCI7_RX_P808_AF5
    {hal_ll_uart_module_num( SCI_MODULE_7 ), GPIO_P808, HAL_LL_SCI7_BASE_ADDR, 5},
    #endif
    #ifdef SCI7_RX_PC04_AF5
    {hal_ll_uart_module_num( SCI_MODULE_7 ), GPIO_PC04, HAL_LL_SCI7_BASE_ADDR, 5},
    #endif
    #ifdef SCI8_RX_P104_AF4
    {hal_ll_uart_module_num( SCI_MODULE_8 ), GPIO_P104, HAL_LL_SCI8_BASE_ADDR, 4},
    #endif
    #ifdef SCI8_RX_P500_AF4
    {hal_ll_uart_module_num( SCI_MODULE_8 ), GPIO_P500, HAL_LL_SCI8_BASE_ADDR, 4},
    #endif
    #ifdef SCI8_RX_P607_AF4
    {hal_ll_uart_module_num( SCI_MODULE_8 ), GPIO_P607, HAL_LL_SCI8_BASE_ADDR, 4},
    #endif
    #ifdef SCI8_RX_P806_AF4
    {hal_ll_uart_module_num( SCI_MODULE_8 ), GPIO_P806, HAL_LL_SCI8_BASE_ADDR, 4},
    #endif
    #ifdef SCI8_RX_PD03_AF4
    {hal_ll_uart_module_num( SCI_MODULE_8 ), GPIO_PD03, HAL_LL_SCI8_BASE_ADDR, 4},
    #endif
    #ifdef SCI9_RX_P000_AF5
    {hal_ll_uart_module_num( SCI_MODULE_9 ), GPIO_P000, HAL_LL_SCI9_BASE_ADDR, 5},
    #endif
    #ifdef SCI9_RX_P100_AF4
    {hal_ll_uart_module_num( SCI_MODULE_9 ), GPIO_P100, HAL_LL_SCI9_BASE_ADDR, 4},
    #endif
    #ifdef SCI9_RX_P101_AF5
    {hal_ll_uart_module_num( SCI_MODULE_9 ), GPIO_P101, HAL_LL_SCI9_BASE_ADDR, 5},
    #endif
    #ifdef SCI9_RX_P103_AF5
    {hal_ll_uart_module_num( SCI_MODULE_9 ), GPIO_P103, HAL_LL_SCI9_BASE_ADDR, 5},
    #endif
    #ifdef SCI9_RX_P110_AF5
    {hal_ll_uart_module_num( SCI_MODULE_9 ), GPIO_P110, HAL_LL_SCI9_BASE_ADDR, 5},
    #endif
    #ifdef SCI9_RX_P111_AF4
    {hal_ll_uart_module_num( SCI_MODULE_9 ), GPIO_P111, HAL_LL_SCI9_BASE_ADDR, 4},
    #endif
    #ifdef SCI9_RX_P202_AF5
    {hal_ll_uart_module_num( SCI_MODULE_9 ), GPIO_P202, HAL_LL_SCI9_BASE_ADDR, 5},
    #endif
    #ifdef SCI9_RX_P208_AF5
    {hal_ll_uart_module_num( SCI_MODULE_9 ), GPIO_P208, HAL_LL_SCI9_BASE_ADDR, 5},
    #endif
    #ifdef SCI9_RX_P300_AF4
    {hal_ll_uart_module_num( SCI_MODULE_9 ), GPIO_P300, HAL_LL_SCI9_BASE_ADDR, 4},
    #endif
    #ifdef SCI9_RX_P401_AF5
    {hal_ll_uart_module_num( SCI_MODULE_9 ), GPIO_P401, HAL_LL_SCI9_BASE_ADDR, 5},
    #endif
    #ifdef SCI9_RX_P408_AF5
    {hal_ll_uart_module_num( SCI_MODULE_9 ), GPIO_P408, HAL_LL_SCI9_BASE_ADDR, 5},
    #endif
    #ifdef SCI9_RX_P511_AF5
    {hal_ll_uart_module_num( SCI_MODULE_9 ), GPIO_P511, HAL_LL_SCI9_BASE_ADDR, 5},
    #endif
    #ifdef SCI9_RX_P601_AF5
    {hal_ll_uart_module_num( SCI_MODULE_9 ), GPIO_P601, HAL_LL_SCI9_BASE_ADDR, 5},
    #endif
    #ifdef SCI9_RX_P914_AF4
    {hal_ll_uart_module_num( SCI_MODULE_9 ), GPIO_P914, HAL_LL_SCI9_BASE_ADDR, 4},
    #endif
    #ifdef SCI9_RX_PA12_AF5
    {hal_ll_uart_module_num( SCI_MODULE_9 ), GPIO_PA12, HAL_LL_SCI9_BASE_ADDR, 5},
    #endif
    #ifdef SCI9_RX_PA15_AF5
    {hal_ll_uart_module_num( SCI_MODULE_9 ), GPIO_PA15, HAL_LL_SCI9_BASE_ADDR, 5},
    #endif
    #ifdef SCI9_RX_PD06_AF5
    {hal_ll_uart_module_num( SCI_MODULE_9 ), GPIO_PD06, HAL_LL_SCI9_BASE_ADDR, 5},
    #endif
    #ifdef SCI9_RX_PD14_AF5
    {hal_ll_uart_module_num( SCI_MODULE_9 ), GPIO_PD14, HAL_LL_SCI9_BASE_ADDR, 5},
    #endif
    #ifdef SCI9_RX_PE01_AF5
    {hal_ll_uart_module_num( SCI_MODULE_9 ), GPIO_PE01, HAL_LL_SCI9_BASE_ADDR, 5},
    #endif
    #ifdef UART0_RX_P100_AF5
    {hal_ll_uart_module_num( UART_MODULE_0 ), GPIO_P100, HAL_LL_UARTA0_BASE_ADDR, 5},
    #endif
    #ifdef UART0_RX_P108_AF22
    {hal_ll_uart_module_num( UART_MODULE_0 ), GPIO_P108, HAL_LL_UARTA0_BASE_ADDR, 22},
    #endif
    #ifdef UART0_RX_P110_AF5
    {hal_ll_uart_module_num( UART_MODULE_0 ), GPIO_P110, HAL_LL_UARTA0_BASE_ADDR, 5},
    #endif
    #ifdef UART0_RX_P207_AF5
    {hal_ll_uart_module_num( UART_MODULE_0 ), GPIO_P207, HAL_LL_UARTA0_BASE_ADDR, 5},
    #endif
    #ifdef UART0_RX_P212_AF5
    {hal_ll_uart_module_num( UART_MODULE_0 ), GPIO_P212, HAL_LL_UARTA0_BASE_ADDR, 5},
    #endif
    #ifdef UART0_RX_P305_AF22
    {hal_ll_uart_module_num( UART_MODULE_0 ), GPIO_P305, HAL_LL_UARTA0_BASE_ADDR, 22},
    #endif
    #ifdef UART0_RX_P402_AF22
    {hal_ll_uart_module_num( UART_MODULE_0 ), GPIO_P402, HAL_LL_UARTA0_BASE_ADDR, 22},
    #endif
    #ifdef UART0_RX_P403_AF5
    {hal_ll_uart_module_num( UART_MODULE_0 ), GPIO_P403, HAL_LL_UARTA0_BASE_ADDR, 5},
    #endif
    #ifdef UART0_RX_P502_AF5
    {hal_ll_uart_module_num( UART_MODULE_0 ), GPIO_P502, HAL_LL_UARTA0_BASE_ADDR, 5},
    #endif
    #ifdef UART0_RX_P509_AF22
    {hal_ll_uart_module_num( UART_MODULE_0 ), GPIO_P509, HAL_LL_UARTA0_BASE_ADDR, 22},
    #endif
    #ifdef UART1_RX_P015_AF22
    {hal_ll_uart_module_num( UART_MODULE_1 ), GPIO_P015, HAL_LL_UARTA1_BASE_ADDR, 22},
    #endif
    #ifdef UART1_RX_P102_AF5
    {hal_ll_uart_module_num( UART_MODULE_1 ), GPIO_P102, HAL_LL_UARTA1_BASE_ADDR, 5},
    #endif
    #ifdef UART1_RX_P105_AF5
    {hal_ll_uart_module_num( UART_MODULE_1 ), GPIO_P105, HAL_LL_UARTA1_BASE_ADDR, 5},
    #endif
    #ifdef UART1_RX_P205_AF5
    {hal_ll_uart_module_num( UART_MODULE_1 ), GPIO_P205, HAL_LL_UARTA1_BASE_ADDR, 5},
    #endif
    #ifdef UART1_RX_P301_AF5
    {hal_ll_uart_module_num( UART_MODULE_1 ), GPIO_P301, HAL_LL_UARTA1_BASE_ADDR, 5},
    #endif
    #ifdef UART1_RX_P409_AF22
    {hal_ll_uart_module_num( UART_MODULE_1 ), GPIO_P409, HAL_LL_UARTA1_BASE_ADDR, 22},
    #endif
    #ifdef UART1_RX_P410_AF5
    {hal_ll_uart_module_num( UART_MODULE_1 ), GPIO_P410, HAL_LL_UARTA1_BASE_ADDR, 5},
    #endif
    #ifdef UART1_RX_P513_AF22
    {hal_ll_uart_module_num( UART_MODULE_1 ), GPIO_P513, HAL_LL_UARTA1_BASE_ADDR, 22},
    #endif
    #ifdef UART1_RX_P814_AF22
    {hal_ll_uart_module_num( UART_MODULE_1 ), GPIO_P814, HAL_LL_UARTA1_BASE_ADDR, 22},
    #endif

    {HAL_LL_MODULE_ERROR, HAL_LL_PIN_NC, HAL_LL_MODULE_ERROR, HAL_LL_PIN_NC}
};

#ifdef __cplusplus
}
#endif

#endif // _HAL_LL_UART_PIN_MAP_H_
// ------------------------------------------------------------------------- END
