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
extern "C" {
#endif

#include "hal_ll_pin_names.h"

    /*!< @brief Macro defining `weak` attribute */
#define __weak __attribute__((weak))
/*!< @brief Helper macro for getting adequate module index number */
//#define hal_ll_uart_module_num(_module_num) (_module_num - 1)
#define hal_ll_uart_module_num(_module_num) (_module_num )


/*!< @brief UART module base addresses */
#ifdef UART_MODULE_0
    static const hal_ll_base_addr_t HAL_LL_UART0_BASE_ADDRESS = 0x400CE000UL;
#endif
#ifdef UART_MODULE_1
    static const hal_ll_base_addr_t HAL_LL_UART1_BASE_ADDRESS = 0x400CE400UL;
#endif
#ifdef UART_MODULE_2
    static const hal_ll_base_addr_t HAL_LL_UART2_BASE_ADDRESS = 0x400CE800UL;
#endif
#ifdef UART_MODULE_3
    static const hal_ll_base_addr_t HAL_LL_UART3_BASE_ADDRESS = 0x400CEC00UL;
#endif


    /*!< @brief UART pin structure. */
    typedef struct {
        uint8_t module_index;
        hal_ll_pin_name_t pin;
        hal_ll_base_addr_t base;
        uint8_t af;
    } hal_ll_uart_pin_map_t;

    /*!< UART TX Pins. */
    static const hal_ll_uart_pin_map_t hal_ll_uart_tx_map[] = {
        // TODO - Define pin mappings here!
    #ifdef UART_MODULE_0
        { hal_ll_uart_module_num(UART_MODULE_0), GPIO_PC0, HAL_LL_UART0_BASE_ADDRESS, 1 },
        { hal_ll_uart_module_num(UART_MODULE_0), GPIO_PC1, HAL_LL_UART0_BASE_ADDRESS, 2 },
        { hal_ll_uart_module_num(UART_MODULE_0), GPIO_PN1, HAL_LL_UART0_BASE_ADDRESS, 2 },
        { hal_ll_uart_module_num(UART_MODULE_0), GPIO_PN0, HAL_LL_UART0_BASE_ADDRESS, 1 },
    #endif
    #ifdef UART_MODULE_1
        { hal_ll_uart_module_num(UART_MODULE_1), GPIO_PC5, HAL_LL_UART1_BASE_ADDRESS, 2 },
        { hal_ll_uart_module_num(UART_MODULE_1), GPIO_PC4, HAL_LL_UART1_BASE_ADDRESS, 1 },
        { hal_ll_uart_module_num(UART_MODULE_1), GPIO_PU6, HAL_LL_UART1_BASE_ADDRESS, 2 },
        { hal_ll_uart_module_num(UART_MODULE_1), GPIO_PU5, HAL_LL_UART1_BASE_ADDRESS, 1 },
    #endif
    #ifdef UART_MODULE_2
        { hal_ll_uart_module_num(UART_MODULE_2), GPIO_PF1, HAL_LL_UART2_BASE_ADDRESS, 2 },
        { hal_ll_uart_module_num(UART_MODULE_2), GPIO_PF0, HAL_LL_UART2_BASE_ADDRESS, 1 },
        { hal_ll_uart_module_num(UART_MODULE_2), GPIO_PU1, HAL_LL_UART2_BASE_ADDRESS, 2 },
        { hal_ll_uart_module_num(UART_MODULE_2), GPIO_PU0, HAL_LL_UART2_BASE_ADDRESS, 1 },
    #endif
    #ifdef UART_MODULE_3
        { hal_ll_uart_module_num(UART_MODULE_3), GPIO_PF4, HAL_LL_UART3_BASE_ADDRESS, 2 },
        { hal_ll_uart_module_num(UART_MODULE_3), GPIO_PF3, HAL_LL_UART3_BASE_ADDRESS, 1 },
        { hal_ll_uart_module_num(UART_MODULE_3), GPIO_PF7, HAL_LL_UART3_BASE_ADDRESS, 2 },
        { hal_ll_uart_module_num(UART_MODULE_3), GPIO_PF6, HAL_LL_UART3_BASE_ADDRESS, 1 },
    #endif

        {HAL_LL_MODULE_ERROR, HAL_LL_PIN_NC, HAL_LL_MODULE_ERROR, HAL_LL_PIN_NC}
    };

    /*!< UART RX Pins. */
    static const hal_ll_uart_pin_map_t hal_ll_uart_rx_map[] = {
        // TODO - Define pin mappings here!
    #ifdef UART_MODULE_0
        { hal_ll_uart_module_num(UART_MODULE_0), GPIO_PC0, HAL_LL_UART0_BASE_ADDRESS, 2 },
        { hal_ll_uart_module_num(UART_MODULE_0), GPIO_PC1, HAL_LL_UART0_BASE_ADDRESS, 1 },
        { hal_ll_uart_module_num(UART_MODULE_0), GPIO_PN0, HAL_LL_UART0_BASE_ADDRESS, 2 },
        { hal_ll_uart_module_num(UART_MODULE_0), GPIO_PN1, HAL_LL_UART0_BASE_ADDRESS, 1 },
    #endif
    #ifdef UART_MODULE_1
        { hal_ll_uart_module_num(UART_MODULE_1), GPIO_PC4, HAL_LL_UART1_BASE_ADDRESS, 2 },
        { hal_ll_uart_module_num(UART_MODULE_1), GPIO_PC5, HAL_LL_UART1_BASE_ADDRESS, 1 },
        { hal_ll_uart_module_num(UART_MODULE_1), GPIO_PU5, HAL_LL_UART1_BASE_ADDRESS, 2 },
        { hal_ll_uart_module_num(UART_MODULE_1), GPIO_PU6, HAL_LL_UART1_BASE_ADDRESS, 1 },
    #endif
    #ifdef UART_MODULE_2
        { hal_ll_uart_module_num(UART_MODULE_2), GPIO_PF0, HAL_LL_UART2_BASE_ADDRESS, 2 },
        { hal_ll_uart_module_num(UART_MODULE_2), GPIO_PF1, HAL_LL_UART2_BASE_ADDRESS, 1 },
        { hal_ll_uart_module_num(UART_MODULE_2), GPIO_PU0, HAL_LL_UART2_BASE_ADDRESS, 2 },
        { hal_ll_uart_module_num(UART_MODULE_2), GPIO_PU1, HAL_LL_UART2_BASE_ADDRESS, 1 },
    #endif
    #ifdef UART_MODULE_3
        { hal_ll_uart_module_num(UART_MODULE_3), GPIO_PF3, HAL_LL_UART3_BASE_ADDRESS, 2 },
        { hal_ll_uart_module_num(UART_MODULE_3), GPIO_PF4, HAL_LL_UART3_BASE_ADDRESS, 1 },
        { hal_ll_uart_module_num(UART_MODULE_3), GPIO_PF6, HAL_LL_UART3_BASE_ADDRESS, 2 },
        { hal_ll_uart_module_num(UART_MODULE_3), GPIO_PF7, HAL_LL_UART3_BASE_ADDRESS, 1 },
    #endif

        {HAL_LL_MODULE_ERROR, HAL_LL_PIN_NC, HAL_LL_MODULE_ERROR, HAL_LL_PIN_NC}
    };

#ifdef __cplusplus
}
#endif

#endif // _HAL_LL_UART_PIN_MAP_H_
// ------------------------------------------------------------------------- END