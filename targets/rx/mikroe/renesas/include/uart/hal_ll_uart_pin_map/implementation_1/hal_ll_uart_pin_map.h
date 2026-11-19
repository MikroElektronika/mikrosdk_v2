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
    #ifdef SCI11_TX_P902_AF45
    {hal_ll_uart_module_num( SCI_MODULE_11 ), GPIO_P902, HAL_LL_SCI11_BASE_ADDR, 45},
    #endif
    #ifdef SCI11_TX_PA00_AF45
    {hal_ll_uart_module_num( SCI_MODULE_11 ), GPIO_PA00, HAL_LL_SCI11_BASE_ADDR, 45},
    #endif
    #ifdef SCI11_TX_PB05_AF45
    {hal_ll_uart_module_num( SCI_MODULE_11 ), GPIO_PB05, HAL_LL_SCI11_BASE_ADDR, 45},
    #endif
    #ifdef SCI11_TX_PD03_AF45
    {hal_ll_uart_module_num( SCI_MODULE_11 ), GPIO_PD03, HAL_LL_SCI11_BASE_ADDR, 45},
    #endif
    #ifdef SCI12_TX_P001_AF12
    {hal_ll_uart_module_num( SCI_MODULE_12 ), GPIO_P001, HAL_LL_SCI12_BASE_ADDR, 12},
    #endif
    #ifdef SCI12_TX_P201_AF12
    {hal_ll_uart_module_num( SCI_MODULE_12 ), GPIO_P201, HAL_LL_SCI12_BASE_ADDR, 12},
    #endif
    #ifdef SCI12_TX_P203_AF12
    {hal_ll_uart_module_num( SCI_MODULE_12 ), GPIO_P203, HAL_LL_SCI12_BASE_ADDR, 12},
    #endif
    #ifdef SCI12_TX_P801_AF12
    {hal_ll_uart_module_num( SCI_MODULE_12 ), GPIO_P801, HAL_LL_SCI12_BASE_ADDR, 12},
    #endif
    #ifdef SCI12_TX_PB03_AF12
    {hal_ll_uart_module_num( SCI_MODULE_12 ), GPIO_PB03, HAL_LL_SCI12_BASE_ADDR, 12},
    #endif
    #ifdef SCI12_TX_PB05_AF12
    {hal_ll_uart_module_num( SCI_MODULE_12 ), GPIO_PB05, HAL_LL_SCI12_BASE_ADDR, 12},
    #endif
    #ifdef SCI12_TX_PD04_AF12
    {hal_ll_uart_module_num( SCI_MODULE_12 ), GPIO_PD04, HAL_LL_SCI12_BASE_ADDR, 12},
    #endif
    #ifdef SCI1_TX_PD03_AF10
    {hal_ll_uart_module_num( SCI_MODULE_1 ), GPIO_PD03, HAL_LL_SCI1_BASE_ADDR, 10},
    #endif
    #ifdef SCI5_TX_P306_AF10
    {hal_ll_uart_module_num( SCI_MODULE_5 ), GPIO_P306, HAL_LL_SCI5_BASE_ADDR, 10},
    #endif
    #ifdef SCI5_TX_P900_AF10
    {hal_ll_uart_module_num( SCI_MODULE_5 ), GPIO_P900, HAL_LL_SCI5_BASE_ADDR, 10},
    #endif
    #ifdef SCI5_TX_PB05_AF10
    {hal_ll_uart_module_num( SCI_MODULE_5 ), GPIO_PB05, HAL_LL_SCI5_BASE_ADDR, 10},
    #endif
    #ifdef SCI5_TX_PD07_AF10
    {hal_ll_uart_module_num( SCI_MODULE_5 ), GPIO_PD07, HAL_LL_SCI5_BASE_ADDR, 10},
    #endif
    #ifdef SCI6_TX_P801_AF10
    {hal_ll_uart_module_num( SCI_MODULE_6 ), GPIO_P801, HAL_LL_SCI6_BASE_ADDR, 10},
    #endif
    #ifdef SCI6_TX_PB00_AF10
    {hal_ll_uart_module_num( SCI_MODULE_6 ), GPIO_PB00, HAL_LL_SCI6_BASE_ADDR, 10},
    #endif
    #ifdef SCI6_TX_PB02_AF10
    {hal_ll_uart_module_num( SCI_MODULE_6 ), GPIO_PB02, HAL_LL_SCI6_BASE_ADDR, 10},
    #endif
    #ifdef SCI8_TX_P201_AF44
    {hal_ll_uart_module_num( SCI_MODULE_8 ), GPIO_P201, HAL_LL_SCI8_BASE_ADDR, 44},
    #endif
    #ifdef SCI8_TX_P203_AF44
    {hal_ll_uart_module_num( SCI_MODULE_8 ), GPIO_P203, HAL_LL_SCI8_BASE_ADDR, 44},
    #endif
    #ifdef SCI8_TX_PA04_AF45
    {hal_ll_uart_module_num( SCI_MODULE_8 ), GPIO_PA04, HAL_LL_SCI8_BASE_ADDR, 45},
    #endif
    #ifdef SCI8_TX_PB00_AF44
    {hal_ll_uart_module_num( SCI_MODULE_8 ), GPIO_PB00, HAL_LL_SCI8_BASE_ADDR, 44},
    #endif
    #ifdef SCI8_TX_PD00_AF45
    {hal_ll_uart_module_num( SCI_MODULE_8 ), GPIO_PD00, HAL_LL_SCI8_BASE_ADDR, 45},
    #endif
    #ifdef SCI8_TX_PD07_AF45
    {hal_ll_uart_module_num( SCI_MODULE_8 ), GPIO_PD07, HAL_LL_SCI8_BASE_ADDR, 45},
    #endif
    #ifdef SCI9_TX_P001_AF44
    {hal_ll_uart_module_num( SCI_MODULE_9 ), GPIO_P001, HAL_LL_SCI9_BASE_ADDR, 44},
    #endif
    #ifdef SCI9_TX_P100_AF44
    {hal_ll_uart_module_num( SCI_MODULE_9 ), GPIO_P100, HAL_LL_SCI9_BASE_ADDR, 44},
    #endif
    #ifdef SCI9_TX_P903_AF44
    {hal_ll_uart_module_num( SCI_MODULE_9 ), GPIO_P903, HAL_LL_SCI9_BASE_ADDR, 44},
    #endif
    #ifdef SCI9_TX_P904_AF44
    {hal_ll_uart_module_num( SCI_MODULE_9 ), GPIO_P904, HAL_LL_SCI9_BASE_ADDR, 44},
    #endif
    #ifdef SCI9_TX_PA01_AF44
    {hal_ll_uart_module_num( SCI_MODULE_9 ), GPIO_PA01, HAL_LL_SCI9_BASE_ADDR, 44},
    #endif
    #ifdef SCI9_TX_PA03_AF44
    {hal_ll_uart_module_num( SCI_MODULE_9 ), GPIO_PA03, HAL_LL_SCI9_BASE_ADDR, 44},
    #endif

    {HAL_LL_MODULE_ERROR, HAL_LL_PIN_NC, HAL_LL_MODULE_ERROR, HAL_LL_PIN_NC}
};

/*!< UART RX Pins. */
static const hal_ll_uart_pin_map_t hal_ll_uart_rx_map[] = {
    #ifdef SCI11_RX_P903_AF45
    {hal_ll_uart_module_num( SCI_MODULE_11 ), GPIO_P903, HAL_LL_SCI11_BASE_ADDR, 45},
    #endif
    #ifdef SCI11_RX_PA01_AF45
    {hal_ll_uart_module_num( SCI_MODULE_11 ), GPIO_PA01, HAL_LL_SCI11_BASE_ADDR, 45},
    #endif
    #ifdef SCI11_RX_PB06_AF45
    {hal_ll_uart_module_num( SCI_MODULE_11 ), GPIO_PB06, HAL_LL_SCI11_BASE_ADDR, 45},
    #endif
    #ifdef SCI11_RX_PD05_AF45
    {hal_ll_uart_module_num( SCI_MODULE_11 ), GPIO_PD05, HAL_LL_SCI11_BASE_ADDR, 45},
    #endif
    #ifdef SCI12_RX_P000_AF12
    {hal_ll_uart_module_num( SCI_MODULE_12 ), GPIO_P000, HAL_LL_SCI12_BASE_ADDR, 12},
    #endif
    #ifdef SCI12_RX_P202_AF12
    {hal_ll_uart_module_num( SCI_MODULE_12 ), GPIO_P202, HAL_LL_SCI12_BASE_ADDR, 12},
    #endif
    #ifdef SCI12_RX_P800_AF12
    {hal_ll_uart_module_num( SCI_MODULE_12 ), GPIO_P800, HAL_LL_SCI12_BASE_ADDR, 12},
    #endif
    #ifdef SCI12_RX_PB04_AF12
    {hal_ll_uart_module_num( SCI_MODULE_12 ), GPIO_PB04, HAL_LL_SCI12_BASE_ADDR, 12},
    #endif
    #ifdef SCI12_RX_PB06_AF12
    {hal_ll_uart_module_num( SCI_MODULE_12 ), GPIO_PB06, HAL_LL_SCI12_BASE_ADDR, 12},
    #endif
    #ifdef SCI12_RX_PD06_AF12
    {hal_ll_uart_module_num( SCI_MODULE_12 ), GPIO_PD06, HAL_LL_SCI12_BASE_ADDR, 12},
    #endif
    #ifdef SCI1_RX_PD05_AF10
    {hal_ll_uart_module_num( SCI_MODULE_1 ), GPIO_PD05, HAL_LL_SCI1_BASE_ADDR, 10},
    #endif
    #ifdef SCI5_RX_P307_AF10
    {hal_ll_uart_module_num( SCI_MODULE_5 ), GPIO_P307, HAL_LL_SCI5_BASE_ADDR, 10},
    #endif
    #ifdef SCI5_RX_P901_AF10
    {hal_ll_uart_module_num( SCI_MODULE_5 ), GPIO_P901, HAL_LL_SCI5_BASE_ADDR, 10},
    #endif
    #ifdef SCI5_RX_PB06_AF10
    {hal_ll_uart_module_num( SCI_MODULE_5 ), GPIO_PB06, HAL_LL_SCI5_BASE_ADDR, 10},
    #endif
    #ifdef SCI5_RX_PE00_AF10
    {hal_ll_uart_module_num( SCI_MODULE_5 ), GPIO_PE00, HAL_LL_SCI5_BASE_ADDR, 10},
    #endif
    #ifdef SCI6_RX_P800_AF10
    {hal_ll_uart_module_num( SCI_MODULE_6 ), GPIO_P800, HAL_LL_SCI6_BASE_ADDR, 10},
    #endif
    #ifdef SCI6_RX_P905_AF10
    {hal_ll_uart_module_num( SCI_MODULE_6 ), GPIO_P905, HAL_LL_SCI6_BASE_ADDR, 10},
    #endif
    #ifdef SCI6_RX_PA05_AF10
    {hal_ll_uart_module_num( SCI_MODULE_6 ), GPIO_PA05, HAL_LL_SCI6_BASE_ADDR, 10},
    #endif
    #ifdef SCI6_RX_PB01_AF10
    {hal_ll_uart_module_num( SCI_MODULE_6 ), GPIO_PB01, HAL_LL_SCI6_BASE_ADDR, 10},
    #endif
    #ifdef SCI8_RX_P200_AF45
    {hal_ll_uart_module_num( SCI_MODULE_8 ), GPIO_P200, HAL_LL_SCI8_BASE_ADDR, 45},
    #endif
    #ifdef SCI8_RX_P202_AF44
    {hal_ll_uart_module_num( SCI_MODULE_8 ), GPIO_P202, HAL_LL_SCI8_BASE_ADDR, 44},
    #endif
    #ifdef SCI8_RX_P905_AF45
    {hal_ll_uart_module_num( SCI_MODULE_8 ), GPIO_P905, HAL_LL_SCI8_BASE_ADDR, 45},
    #endif
    #ifdef SCI8_RX_PA05_AF45
    {hal_ll_uart_module_num( SCI_MODULE_8 ), GPIO_PA05, HAL_LL_SCI8_BASE_ADDR, 45},
    #endif
    #ifdef SCI8_RX_PD01_AF45
    {hal_ll_uart_module_num( SCI_MODULE_8 ), GPIO_PD01, HAL_LL_SCI8_BASE_ADDR, 45},
    #endif
    #ifdef SCI9_RX_P000_AF44
    {hal_ll_uart_module_num( SCI_MODULE_9 ), GPIO_P000, HAL_LL_SCI9_BASE_ADDR, 44},
    #endif
    #ifdef SCI9_RX_PA02_AF45
    {hal_ll_uart_module_num( SCI_MODULE_9 ), GPIO_PA02, HAL_LL_SCI9_BASE_ADDR, 45},
    #endif

    {HAL_LL_MODULE_ERROR, HAL_LL_PIN_NC, HAL_LL_MODULE_ERROR, HAL_LL_PIN_NC}
};

#ifdef __cplusplus
}
#endif

#endif // _HAL_LL_UART_PIN_MAP_H_
// ------------------------------------------------------------------------- END
