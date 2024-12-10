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
} hal_ll_uart_pin_map_t;

/*!< @brief UART TX pins */
static const hal_ll_uart_pin_map_t hal_ll_uart_tx_map[] = {
    //------------ BEGIN TX
    #ifdef UART_MODULE
    #endif

    #ifdef UART_MODULE_1
    #ifdef UART1_TX_RA0
    { GPIO_PA0, hal_ll_uart_module_num(UART_MODULE_1) },
    #endif
    #ifdef UART1_TX_RB3
    { GPIO_PB3, hal_ll_uart_module_num(UART_MODULE_1) },
    #endif
    #ifdef UART1_TX_RB4
    { GPIO_PB4, hal_ll_uart_module_num(UART_MODULE_1) },
    #endif
    #ifdef UART1_TX_RB15
    { GPIO_PB15, hal_ll_uart_module_num(UART_MODULE_1) },
    #endif
    #ifdef UART1_TX_RB7
    { GPIO_PB7, hal_ll_uart_module_num(UART_MODULE_1) },
    #endif
    #ifdef UART1_TX_RC0
    { GPIO_PC0, hal_ll_uart_module_num(UART_MODULE_1) },
    #endif
    #ifdef UART1_TX_RC7
    { GPIO_PC7, hal_ll_uart_module_num(UART_MODULE_1) },
    #endif
    #ifdef UART1_TX_RC5
    { GPIO_PC5, hal_ll_uart_module_num(UART_MODULE_1) },
    #endif
    #ifdef UART1_TX_RD3
    { GPIO_PD3, hal_ll_uart_module_num(UART_MODULE_1) },
    #endif
    #ifdef UART1_TX_RG7
    { GPIO_PG7, hal_ll_uart_module_num(UART_MODULE_1) },
    #endif
    #ifdef UART1_TX_RF5
    { GPIO_PF5, hal_ll_uart_module_num(UART_MODULE_1) },
    #endif
    #ifdef UART1_TX_RD11
    { GPIO_PD11, hal_ll_uart_module_num(UART_MODULE_1) },
    #endif
    #ifdef UART1_TX_RF0
    { GPIO_PF0, hal_ll_uart_module_num(UART_MODULE_1) },
    #endif
    #ifdef UART1_TX_RB1
    { GPIO_PB1, hal_ll_uart_module_num(UART_MODULE_1) },
    #endif
    #ifdef UART1_TX_RE5
    { GPIO_PE5, hal_ll_uart_module_num(UART_MODULE_1) },
    #endif
    #ifdef UART1_TX_RC13
    { GPIO_PC13, hal_ll_uart_module_num(UART_MODULE_1) },
    #endif
    #ifdef UART1_TX_RF3
    { GPIO_PF3, hal_ll_uart_module_num(UART_MODULE_1) },
    #endif
    #ifdef UART1_TX_RC4
    { GPIO_PC4, hal_ll_uart_module_num(UART_MODULE_1) },
    #endif
    #ifdef UART1_TX_RD15
    { GPIO_PD15, hal_ll_uart_module_num(UART_MODULE_1) },
    #endif
    #ifdef UART1_TX_RG0
    { GPIO_PG0, hal_ll_uart_module_num(UART_MODULE_1) },
    #endif
    #ifdef UART1_TX_RA15
    { GPIO_PA15, hal_ll_uart_module_num(UART_MODULE_1) },
    #endif
    #ifdef UART1_TX_RF8
    { GPIO_PF8, hal_ll_uart_module_num(UART_MODULE_1) },
    #endif
    #ifdef UART1_TX_RD7
    { GPIO_PD7, hal_ll_uart_module_num(UART_MODULE_1) },
    #endif
    #endif

    #ifdef UART_MODULE_2
    #ifdef UART2_TX_RA3
    { GPIO_PA3, hal_ll_uart_module_num(UART_MODULE_2) },
    #endif
    #ifdef UART2_TX_RB14
    { GPIO_PB14, hal_ll_uart_module_num(UART_MODULE_2) },
    #endif
    #ifdef UART2_TX_RB0
    { GPIO_PB0, hal_ll_uart_module_num(UART_MODULE_2) },
    #endif
    #ifdef UART2_TX_RB10
    { GPIO_PB10, hal_ll_uart_module_num(UART_MODULE_2) },
    #endif
    #ifdef UART2_TX_RB9
    { GPIO_PB9, hal_ll_uart_module_num(UART_MODULE_2) },
    #endif
    #ifdef UART2_TX_RC9
    { GPIO_PC9, hal_ll_uart_module_num(UART_MODULE_2) },
    #endif
    #ifdef UART2_TX_RC2
    { GPIO_PC2, hal_ll_uart_module_num(UART_MODULE_2) },
    #endif
    #ifdef UART2_TX_RC4
    { GPIO_PC4, hal_ll_uart_module_num(UART_MODULE_2) },
    #endif
    #ifdef UART2_TX_RD3
    { GPIO_PD3, hal_ll_uart_module_num(UART_MODULE_2) },
    #endif
    #ifdef UART2_TX_RG7
    { GPIO_PG7, hal_ll_uart_module_num(UART_MODULE_2) },
    #endif
    #ifdef UART2_TX_RF5
    { GPIO_PF5, hal_ll_uart_module_num(UART_MODULE_2) },
    #endif
    #ifdef UART2_TX_RD11
    { GPIO_PD11, hal_ll_uart_module_num(UART_MODULE_2) },
    #endif
    #ifdef UART2_TX_RF0
    { GPIO_PF0, hal_ll_uart_module_num(UART_MODULE_2) },
    #endif
    #ifdef UART2_TX_RB1
    { GPIO_PB1, hal_ll_uart_module_num(UART_MODULE_2) },
    #endif
    #ifdef UART2_TX_RE5
    { GPIO_PE5, hal_ll_uart_module_num(UART_MODULE_2) },
    #endif
    #ifdef UART2_TX_RC13
    { GPIO_PC13, hal_ll_uart_module_num(UART_MODULE_2) },
    #endif
    #ifdef UART2_TX_RB3
    { GPIO_PB3, hal_ll_uart_module_num(UART_MODULE_2) },
    #endif
    #ifdef UART2_TX_RF3
    { GPIO_PF3, hal_ll_uart_module_num(UART_MODULE_2) },
    #endif
    #ifdef UART2_TX_RD15
    { GPIO_PD15, hal_ll_uart_module_num(UART_MODULE_2) },
    #endif
    #ifdef UART2_TX_RG0
    { GPIO_PG0, hal_ll_uart_module_num(UART_MODULE_2) },
    #endif
    #ifdef UART2_TX_RA15
    { GPIO_PA15, hal_ll_uart_module_num(UART_MODULE_2) },
    #endif
    #ifdef UART2_TX_RD1
    { GPIO_PD1, hal_ll_uart_module_num(UART_MODULE_2) },
    #endif
    #ifdef UART2_TX_RG9
    { GPIO_PG9, hal_ll_uart_module_num(UART_MODULE_2) },
    #endif
    #ifdef UART2_TX_RD0
    { GPIO_PD0, hal_ll_uart_module_num(UART_MODULE_2) },
    #endif
    #ifdef UART2_TX_RB6
    { GPIO_PB6, hal_ll_uart_module_num(UART_MODULE_2) },
    #endif
    #ifdef UART2_TX_RD5
    { GPIO_PD5, hal_ll_uart_module_num(UART_MODULE_2) },
    #endif
    #ifdef UART2_TX_RB2
    { GPIO_PB2, hal_ll_uart_module_num(UART_MODULE_2) },
    #endif
    #ifdef UART2_TX_RF13
    { GPIO_PF13, hal_ll_uart_module_num(UART_MODULE_2) },
    #endif
    #ifdef UART2_TX_RF2
    { GPIO_PF2, hal_ll_uart_module_num(UART_MODULE_2) },
    #endif
    #ifdef UART2_TX_RE8
    { GPIO_PE8, hal_ll_uart_module_num(UART_MODULE_2) },
    #endif
    #endif

    #ifdef UART_MODULE_3
    #ifdef UART3_TX_RD2
    { GPIO_PD2, hal_ll_uart_module_num(UART_MODULE_3) },
    #endif
    #ifdef UART3_TX_RG8
    { GPIO_PG8, hal_ll_uart_module_num(UART_MODULE_3) },
    #endif
    #ifdef UART3_TX_RF4
    { GPIO_PF4, hal_ll_uart_module_num(UART_MODULE_3) },
    #endif
    #ifdef UART3_TX_RD10
    { GPIO_PD10, hal_ll_uart_module_num(UART_MODULE_3) },
    #endif
    #ifdef UART3_TX_RF1
    { GPIO_PF1, hal_ll_uart_module_num(UART_MODULE_3) },
    #endif
    #ifdef UART3_TX_RB9
    { GPIO_PB9, hal_ll_uart_module_num(UART_MODULE_3) },
    #endif
    #ifdef UART3_TX_RB10
    { GPIO_PB10, hal_ll_uart_module_num(UART_MODULE_3) },
    #endif
    #ifdef UART3_TX_RC14
    { GPIO_PC14, hal_ll_uart_module_num(UART_MODULE_3) },
    #endif
    #ifdef UART3_TX_RB5
    { GPIO_PB5, hal_ll_uart_module_num(UART_MODULE_3) },
    #endif
    #ifdef UART3_TX_RC1
    { GPIO_PC1, hal_ll_uart_module_num(UART_MODULE_3) },
    #endif
    #ifdef UART3_TX_RD14
    { GPIO_PD14, hal_ll_uart_module_num(UART_MODULE_3) },
    #endif
    #ifdef UART3_TX_RG1
    { GPIO_PG1, hal_ll_uart_module_num(UART_MODULE_3) },
    #endif
    #ifdef UART3_TX_RA14
    { GPIO_PA14, hal_ll_uart_module_num(UART_MODULE_3) },
    #endif
    #ifdef UART3_TX_RD6
    { GPIO_PD6, hal_ll_uart_module_num(UART_MODULE_3) },
    #endif
    #endif

    #ifdef UART_MODULE_4
    #ifdef UART4_TX_RD9
    { GPIO_PD9, hal_ll_uart_module_num(UART_MODULE_4) },
    #endif
    #ifdef UART4_TX_RG6
    { GPIO_PG6, hal_ll_uart_module_num(UART_MODULE_4) },
    #endif
    #ifdef UART4_TX_RB8
    { GPIO_PB8, hal_ll_uart_module_num(UART_MODULE_4) },
    #endif
    #ifdef UART4_TX_RB15
    { GPIO_PB15, hal_ll_uart_module_num(UART_MODULE_4) },
    #endif
    #ifdef UART4_TX_RD4
    { GPIO_PD4, hal_ll_uart_module_num(UART_MODULE_4) },
    #endif
    #ifdef UART4_TX_RB0
    { GPIO_PB0, hal_ll_uart_module_num(UART_MODULE_4) },
    #endif
    #ifdef UART4_TX_RE3
    { GPIO_PE3, hal_ll_uart_module_num(UART_MODULE_4) },
    #endif
    #ifdef UART4_TX_RB7
    { GPIO_PB7, hal_ll_uart_module_num(UART_MODULE_4) },
    #endif
    #ifdef UART4_TX_RF12
    { GPIO_PF12, hal_ll_uart_module_num(UART_MODULE_4) },
    #endif
    #ifdef UART4_TX_RD12
    { GPIO_PD12, hal_ll_uart_module_num(UART_MODULE_4) },
    #endif
    #ifdef UART4_TX_RF8
    { GPIO_PF8, hal_ll_uart_module_num(UART_MODULE_4) },
    #endif
    #ifdef UART4_TX_RC3
    { GPIO_PC3, hal_ll_uart_module_num(UART_MODULE_4) },
    #endif
    #ifdef UART4_TX_RE9
    { GPIO_PE9, hal_ll_uart_module_num(UART_MODULE_4) },
    #endif
    #ifdef UART4_TX_RB2
    { GPIO_PB2, hal_ll_uart_module_num(UART_MODULE_4) },
    #endif
    #ifdef UART4_TX_RD1
    { GPIO_PD1, hal_ll_uart_module_num(UART_MODULE_4) },
    #endif
    #ifdef UART4_TX_RD15
    { GPIO_PD15, hal_ll_uart_module_num(UART_MODULE_4) },
    #endif
    #endif

    #ifdef UART_MODULE_5
    #ifdef UART5_TX_RD9
    { GPIO_PD9, hal_ll_uart_module_num(UART_MODULE_5) },
    #endif
    #ifdef UART5_TX_RG6
    { GPIO_PG6, hal_ll_uart_module_num(UART_MODULE_5) },
    #endif
    #ifdef UART5_TX_RB8
    { GPIO_PB8, hal_ll_uart_module_num(UART_MODULE_5) },
    #endif
    #ifdef UART5_TX_RB15
    { GPIO_PB15, hal_ll_uart_module_num(UART_MODULE_5) },
    #endif
    #ifdef UART5_TX_RD4
    { GPIO_PD4, hal_ll_uart_module_num(UART_MODULE_5) },
    #endif
    #ifdef UART5_TX_RB0
    { GPIO_PB0, hal_ll_uart_module_num(UART_MODULE_5) },
    #endif
    #ifdef UART5_TX_RE3
    { GPIO_PE3, hal_ll_uart_module_num(UART_MODULE_5) },
    #endif
    #ifdef UART5_TX_RB7
    { GPIO_PB7, hal_ll_uart_module_num(UART_MODULE_5) },
    #endif
    #ifdef UART5_TX_RF12
    { GPIO_PF12, hal_ll_uart_module_num(UART_MODULE_5) },
    #endif
    #ifdef UART5_TX_RD12
    { GPIO_PD12, hal_ll_uart_module_num(UART_MODULE_5) },
    #endif
    #ifdef UART5_TX_RF8
    { GPIO_PF8, hal_ll_uart_module_num(UART_MODULE_5) },
    #endif
    #ifdef UART5_TX_RC3
    { GPIO_PC3, hal_ll_uart_module_num(UART_MODULE_5) },
    #endif
    #ifdef UART5_TX_RE9
    { GPIO_PE9, hal_ll_uart_module_num(UART_MODULE_5) },
    #endif
    #ifdef UART5_TX_RD1
    { GPIO_PD1, hal_ll_uart_module_num(UART_MODULE_5) },
    #endif
    #ifdef UART5_TX_RG9
    { GPIO_PG9, hal_ll_uart_module_num(UART_MODULE_5) },
    #endif
    #ifdef UART5_TX_RB14
    { GPIO_PB14, hal_ll_uart_module_num(UART_MODULE_5) },
    #endif
    #ifdef UART5_TX_RD0
    { GPIO_PD0, hal_ll_uart_module_num(UART_MODULE_5) },
    #endif
    #ifdef UART5_TX_RD8
    { GPIO_PD8, hal_ll_uart_module_num(UART_MODULE_5) },
    #endif
    #ifdef UART5_TX_RB6
    { GPIO_PB6, hal_ll_uart_module_num(UART_MODULE_5) },
    #endif
    #ifdef UART5_TX_RD5
    { GPIO_PD5, hal_ll_uart_module_num(UART_MODULE_5) },
    #endif
    #ifdef UART5_TX_RF3
    { GPIO_PF3, hal_ll_uart_module_num(UART_MODULE_5) },
    #endif
    #ifdef UART5_TX_RF6
    { GPIO_PF6, hal_ll_uart_module_num(UART_MODULE_5) },
    #endif
    #ifdef UART5_TX_RF13
    { GPIO_PF13, hal_ll_uart_module_num(UART_MODULE_5) },
    #endif
    #ifdef UART5_TX_RC2
    { GPIO_PC2, hal_ll_uart_module_num(UART_MODULE_5) },
    #endif
    #ifdef UART5_TX_RE8
    { GPIO_PE8, hal_ll_uart_module_num(UART_MODULE_5) },
    #endif
    #ifdef UART5_TX_RF2
    { GPIO_PF2, hal_ll_uart_module_num(UART_MODULE_5) },
    #endif
    #ifdef UART5_TX_RB2
    { GPIO_PB2, hal_ll_uart_module_num(UART_MODULE_5) },
    #endif
    #ifdef UART5_TX_RD3
    { GPIO_PD3, hal_ll_uart_module_num(UART_MODULE_5) },
    #endif
    #ifdef UART5_TX_RG7
    { GPIO_PG7, hal_ll_uart_module_num(UART_MODULE_5) },
    #endif
    #ifdef UART5_TX_RF5
    { GPIO_PF5, hal_ll_uart_module_num(UART_MODULE_5) },
    #endif
    #ifdef UART5_TX_RD11
    { GPIO_PD11, hal_ll_uart_module_num(UART_MODULE_5) },
    #endif
    #ifdef UART5_TX_RF0
    { GPIO_PF0, hal_ll_uart_module_num(UART_MODULE_5) },
    #endif
    #ifdef UART5_TX_RB1
    { GPIO_PB1, hal_ll_uart_module_num(UART_MODULE_5) },
    #endif
    #ifdef UART5_TX_RE5
    { GPIO_PE5, hal_ll_uart_module_num(UART_MODULE_5) },
    #endif
    #ifdef UART5_TX_RC13
    { GPIO_PC13, hal_ll_uart_module_num(UART_MODULE_5) },
    #endif
    #ifdef UART5_TX_RB3
    { GPIO_PB3, hal_ll_uart_module_num(UART_MODULE_5) },
    #endif
    #ifdef UART5_TX_RC4
    { GPIO_PC4, hal_ll_uart_module_num(UART_MODULE_5) },
    #endif
    #ifdef UART5_TX_RD15
    { GPIO_PD15, hal_ll_uart_module_num(UART_MODULE_5) },
    #endif
    #ifdef UART5_TX_RG0
    { GPIO_PG0, hal_ll_uart_module_num(UART_MODULE_5) },
    #endif
    #ifdef UART5_TX_RA15
    { GPIO_PA15, hal_ll_uart_module_num(UART_MODULE_5) },
    #endif
    #ifdef UART5_TX_RD7
    { GPIO_PD7, hal_ll_uart_module_num(UART_MODULE_5) },
    #endif
    #endif

    #ifdef UART_MODULE_6
    #ifdef UART6_TX_RG6
    { GPIO_PG6, hal_ll_uart_module_num(UART_MODULE_6) },
    #endif
    #ifdef UART6_TX_RD9
    { GPIO_PD9, hal_ll_uart_module_num(UART_MODULE_6) },
    #endif
    #ifdef UART6_TX_RB8
    { GPIO_PB8, hal_ll_uart_module_num(UART_MODULE_6) },
    #endif
    #ifdef UART6_TX_RB15
    { GPIO_PB15, hal_ll_uart_module_num(UART_MODULE_6) },
    #endif
    #ifdef UART6_TX_RD4
    { GPIO_PD4, hal_ll_uart_module_num(UART_MODULE_6) },
    #endif
    #ifdef UART6_TX_RB0
    { GPIO_PB0, hal_ll_uart_module_num(UART_MODULE_6) },
    #endif
    #ifdef UART6_TX_RE3
    { GPIO_PE3, hal_ll_uart_module_num(UART_MODULE_6) },
    #endif
    #ifdef UART6_TX_RB7
    { GPIO_PB7, hal_ll_uart_module_num(UART_MODULE_6) },
    #endif
    #ifdef UART6_TX_RD1
    { GPIO_PD1, hal_ll_uart_module_num(UART_MODULE_6) },
    #endif
    #ifdef UART6_TX_RG9
    { GPIO_PG9, hal_ll_uart_module_num(UART_MODULE_6) },
    #endif
    #ifdef UART6_TX_RB14
    { GPIO_PB14, hal_ll_uart_module_num(UART_MODULE_6) },
    #endif
    #ifdef UART6_TX_RD0
    { GPIO_PD0, hal_ll_uart_module_num(UART_MODULE_6) },
    #endif
    #ifdef UART6_TX_RB6
    { GPIO_PB6, hal_ll_uart_module_num(UART_MODULE_6) },
    #endif
    #ifdef UART6_TX_RD5
    { GPIO_PD5, hal_ll_uart_module_num(UART_MODULE_6) },
    #endif
    #ifdef UART6_TX_RB2
    { GPIO_PB2, hal_ll_uart_module_num(UART_MODULE_6) },
    #endif
    #ifdef UART6_TX_RF3
    { GPIO_PF3, hal_ll_uart_module_num(UART_MODULE_6) },
    #endif
    #ifdef UART6_TX_RF12
    { GPIO_PF12, hal_ll_uart_module_num(UART_MODULE_6) },
    #endif
    #ifdef UART6_TX_RD12
    { GPIO_PD12, hal_ll_uart_module_num(UART_MODULE_6) },
    #endif
    #ifdef UART6_TX_RF8
    { GPIO_PF8, hal_ll_uart_module_num(UART_MODULE_6) },
    #endif
    #ifdef UART6_TX_RC3
    { GPIO_PC3, hal_ll_uart_module_num(UART_MODULE_6) },
    #endif
    #ifdef UART6_TX_RE9
    { GPIO_PE9, hal_ll_uart_module_num(UART_MODULE_6) },
    #endif
    #ifdef UART6_TX_RF13
    { GPIO_PF13, hal_ll_uart_module_num(UART_MODULE_6) },
    #endif
    #ifdef UART6_TX_RF2
    { GPIO_PF2, hal_ll_uart_module_num(UART_MODULE_6) },
    #endif
    #ifdef UART6_TX_RC2
    { GPIO_PC2, hal_ll_uart_module_num(UART_MODULE_6) },
    #endif
    #ifdef UART6_TX_RE8
    { GPIO_PE8, hal_ll_uart_module_num(UART_MODULE_6) },
    #endif
    #endif

    { HAL_LL_PIN_NC, HAL_LL_MODULE_ERROR }
    //------------ END TX
};

/*!< @brief UART RX pins */
static const hal_ll_uart_pin_map_t hal_ll_uart_rx_map[] = {
    //------------ BEGIN RX
    #ifdef UART_MODULE
    #endif

    #ifdef UART_MODULE_1
    #ifdef UART1_RX_RA2
    { GPIO_PA2, hal_ll_uart_module_num(UART_MODULE_1) },
    #endif
    #ifdef UART1_RX_RB6
    { GPIO_PB6, hal_ll_uart_module_num(UART_MODULE_1) },
    #endif
    #ifdef UART1_RX_RA4
    { GPIO_PA4, hal_ll_uart_module_num(UART_MODULE_1) },
    #endif
    #ifdef UART1_RX_RB13
    { GPIO_PB13, hal_ll_uart_module_num(UART_MODULE_1) },
    #endif
    #ifdef UART1_RX_RB2
    { GPIO_PB2, hal_ll_uart_module_num(UART_MODULE_1) },
    #endif
    #ifdef UART1_RX_RC1
    { GPIO_PC1, hal_ll_uart_module_num(UART_MODULE_1) },
    #endif
    #ifdef UART1_RX_RC3
    { GPIO_PC3, hal_ll_uart_module_num(UART_MODULE_1) },
    #endif
    #ifdef UART1_RX_RC6
    { GPIO_PC6, hal_ll_uart_module_num(UART_MODULE_1) },
    #endif
    #ifdef UART1_RX_RD2
    { GPIO_PD2, hal_ll_uart_module_num(UART_MODULE_1) },
    #endif
    #ifdef UART1_RX_RG8
    { GPIO_PG8, hal_ll_uart_module_num(UART_MODULE_1) },
    #endif
    #ifdef UART1_RX_RF4
    { GPIO_PF4, hal_ll_uart_module_num(UART_MODULE_1) },
    #endif
    #ifdef UART1_RX_RD10
    { GPIO_PD10, hal_ll_uart_module_num(UART_MODULE_1) },
    #endif
    #ifdef UART1_RX_RF1
    { GPIO_PF1, hal_ll_uart_module_num(UART_MODULE_1) },
    #endif
    #ifdef UART1_RX_RB9
    { GPIO_PB9, hal_ll_uart_module_num(UART_MODULE_1) },
    #endif
    #ifdef UART1_RX_RB10
    { GPIO_PB10, hal_ll_uart_module_num(UART_MODULE_1) },
    #endif
    #ifdef UART1_RX_RC14
    { GPIO_PC14, hal_ll_uart_module_num(UART_MODULE_1) },
    #endif
    #ifdef UART1_RX_RB5
    { GPIO_PB5, hal_ll_uart_module_num(UART_MODULE_1) },
    #endif
    #ifdef UART1_RX_RD14
    { GPIO_PD14, hal_ll_uart_module_num(UART_MODULE_1) },
    #endif
    #ifdef UART1_RX_RG1
    { GPIO_PG1, hal_ll_uart_module_num(UART_MODULE_1) },
    #endif
    #ifdef UART1_RX_RA14
    { GPIO_PA14, hal_ll_uart_module_num(UART_MODULE_1) },
    #endif
    #ifdef UART1_RX_RF2
    { GPIO_PF2, hal_ll_uart_module_num(UART_MODULE_1) },
    #endif
    #ifdef UART1_RX_RD6
    { GPIO_PD6, hal_ll_uart_module_num(UART_MODULE_1) },
    #endif
    #endif

    #ifdef UART_MODULE_2
    #ifdef UART2_RX_RA1
    { GPIO_PA1, hal_ll_uart_module_num(UART_MODULE_2) },
    #endif
    #ifdef UART2_RX_RB5
    { GPIO_PB5, hal_ll_uart_module_num(UART_MODULE_2) },
    #endif
    #ifdef UART2_RX_RB1
    { GPIO_PB1, hal_ll_uart_module_num(UART_MODULE_2) },
    #endif
    #ifdef UART2_RX_RB11
    { GPIO_PB11, hal_ll_uart_module_num(UART_MODULE_2) },
    #endif
    #ifdef UART2_RX_RB8
    { GPIO_PB8, hal_ll_uart_module_num(UART_MODULE_2) },
    #endif
    #ifdef UART2_RX_RA8
    { GPIO_PA8, hal_ll_uart_module_num(UART_MODULE_2) },
    #endif
    #ifdef UART2_RX_RC8
    { GPIO_PC8, hal_ll_uart_module_num(UART_MODULE_2) },
    #endif
    #ifdef UART2_RX_RA9
    { GPIO_PA9, hal_ll_uart_module_num(UART_MODULE_2) },
    #endif
    #ifdef UART2_RX_RD2
    { GPIO_PD2, hal_ll_uart_module_num(UART_MODULE_2) },
    #endif
    #ifdef UART2_RX_RG8
    { GPIO_PG8, hal_ll_uart_module_num(UART_MODULE_2) },
    #endif
    #ifdef UART2_RX_RF4
    { GPIO_PF4, hal_ll_uart_module_num(UART_MODULE_2) },
    #endif
    #ifdef UART2_RX_RD10
    { GPIO_PD10, hal_ll_uart_module_num(UART_MODULE_2) },
    #endif
    #ifdef UART2_RX_RF1
    { GPIO_PF1, hal_ll_uart_module_num(UART_MODULE_2) },
    #endif
    #ifdef UART2_RX_RB9
    { GPIO_PB9, hal_ll_uart_module_num(UART_MODULE_2) },
    #endif
    #ifdef UART2_RX_RB10
    { GPIO_PB10, hal_ll_uart_module_num(UART_MODULE_2) },
    #endif
    #ifdef UART2_RX_RC14
    { GPIO_PC14, hal_ll_uart_module_num(UART_MODULE_2) },
    #endif
    #ifdef UART2_RX_RC1
    { GPIO_PC1, hal_ll_uart_module_num(UART_MODULE_2) },
    #endif
    #ifdef UART2_RX_RD14
    { GPIO_PD14, hal_ll_uart_module_num(UART_MODULE_2) },
    #endif
    #ifdef UART2_RX_RG1
    { GPIO_PG1, hal_ll_uart_module_num(UART_MODULE_2) },
    #endif
    #ifdef UART2_RX_RA14
    { GPIO_PA14, hal_ll_uart_module_num(UART_MODULE_2) },
    #endif
    #ifdef UART2_RX_RF2
    { GPIO_PF2, hal_ll_uart_module_num(UART_MODULE_2) },
    #endif
    #ifdef UART2_RX_RD9
    { GPIO_PD9, hal_ll_uart_module_num(UART_MODULE_2) },
    #endif
    #ifdef UART2_RX_RG6
    { GPIO_PG6, hal_ll_uart_module_num(UART_MODULE_2) },
    #endif
    #ifdef UART2_RX_RB15
    { GPIO_PB15, hal_ll_uart_module_num(UART_MODULE_2) },
    #endif
    #ifdef UART2_RX_RD4
    { GPIO_PD4, hal_ll_uart_module_num(UART_MODULE_2) },
    #endif
    #ifdef UART2_RX_RB0
    { GPIO_PB0, hal_ll_uart_module_num(UART_MODULE_2) },
    #endif
    #ifdef UART2_RX_RE3
    { GPIO_PE3, hal_ll_uart_module_num(UART_MODULE_2) },
    #endif
    #ifdef UART2_RX_RB7
    { GPIO_PB7, hal_ll_uart_module_num(UART_MODULE_2) },
    #endif
    #ifdef UART2_RX_RF12
    { GPIO_PF12, hal_ll_uart_module_num(UART_MODULE_2) },
    #endif
    #ifdef UART2_RX_RD12
    { GPIO_PD12, hal_ll_uart_module_num(UART_MODULE_2) },
    #endif
    #ifdef UART2_RX_RF8
    { GPIO_PF8, hal_ll_uart_module_num(UART_MODULE_2) },
    #endif
    #ifdef UART2_RX_RC3
    { GPIO_PC3, hal_ll_uart_module_num(UART_MODULE_2) },
    #endif
    #ifdef UART2_RX_RE9
    { GPIO_PE9, hal_ll_uart_module_num(UART_MODULE_2) },
    #endif
    #endif

    #ifdef UART_MODULE_3
    #ifdef UART3_RX_RD3
    { GPIO_PD3, hal_ll_uart_module_num(UART_MODULE_3) },
    #endif
    #ifdef UART3_RX_RG7
    { GPIO_PG7, hal_ll_uart_module_num(UART_MODULE_3) },
    #endif
    #ifdef UART3_RX_RF5
    { GPIO_PF5, hal_ll_uart_module_num(UART_MODULE_3) },
    #endif
    #ifdef UART3_RX_RD11
    { GPIO_PD11, hal_ll_uart_module_num(UART_MODULE_3) },
    #endif
    #ifdef UART3_RX_RF0
    { GPIO_PF0, hal_ll_uart_module_num(UART_MODULE_3) },
    #endif
    #ifdef UART3_RX_RB1
    { GPIO_PB1, hal_ll_uart_module_num(UART_MODULE_3) },
    #endif
    #ifdef UART3_RX_RE5
    { GPIO_PE5, hal_ll_uart_module_num(UART_MODULE_3) },
    #endif
    #ifdef UART3_RX_RC13
    { GPIO_PC13, hal_ll_uart_module_num(UART_MODULE_3) },
    #endif
    #ifdef UART3_RX_RB3
    { GPIO_PB3, hal_ll_uart_module_num(UART_MODULE_3) },
    #endif
    #ifdef UART3_RX_RF12
    { GPIO_PF12, hal_ll_uart_module_num(UART_MODULE_3) },
    #endif
    #ifdef UART3_RX_RC4
    { GPIO_PC4, hal_ll_uart_module_num(UART_MODULE_3) },
    #endif
    #ifdef UART3_RX_RD15
    { GPIO_PD15, hal_ll_uart_module_num(UART_MODULE_3) },
    #endif
    #ifdef UART3_RX_RG0
    { GPIO_PG0, hal_ll_uart_module_num(UART_MODULE_3) },
    #endif
    #ifdef UART3_RX_RA15
    { GPIO_PA15, hal_ll_uart_module_num(UART_MODULE_3) },
    #endif
    #ifdef UART3_RX_RF2
    { GPIO_PF2, hal_ll_uart_module_num(UART_MODULE_3) },
    #endif
    #ifdef UART3_RX_RF7
    { GPIO_PF7, hal_ll_uart_module_num(UART_MODULE_3) },
    #endif
    #ifdef UART3_RX_RD7
    { GPIO_PD7, hal_ll_uart_module_num(UART_MODULE_3) },
    #endif
    #endif

    #ifdef UART_MODULE_4
    #ifdef UART4_RX_RD1
    { GPIO_PD1, hal_ll_uart_module_num(UART_MODULE_4) },
    #endif
    #ifdef UART4_RX_RG9
    { GPIO_PG9, hal_ll_uart_module_num(UART_MODULE_4) },
    #endif
    #ifdef UART4_RX_RB14
    { GPIO_PB14, hal_ll_uart_module_num(UART_MODULE_4) },
    #endif
    #ifdef UART4_RX_RD0
    { GPIO_PD0, hal_ll_uart_module_num(UART_MODULE_4) },
    #endif
    #ifdef UART4_RX_RB6
    { GPIO_PB6, hal_ll_uart_module_num(UART_MODULE_4) },
    #endif
    #ifdef UART4_RX_RD5
    { GPIO_PD5, hal_ll_uart_module_num(UART_MODULE_4) },
    #endif
    #ifdef UART4_RX_RB2
    { GPIO_PB2, hal_ll_uart_module_num(UART_MODULE_4) },
    #endif
    #ifdef UART4_RX_RF3
    { GPIO_PF3, hal_ll_uart_module_num(UART_MODULE_4) },
    #endif
    #ifdef UART4_RX_RF13
    { GPIO_PF13, hal_ll_uart_module_num(UART_MODULE_4) },
    #endif
    #ifdef UART4_RX_RF2
    { GPIO_PF2, hal_ll_uart_module_num(UART_MODULE_4) },
    #endif
    #ifdef UART4_RX_RC2
    { GPIO_PC2, hal_ll_uart_module_num(UART_MODULE_4) },
    #endif
    #ifdef UART4_RX_RE8
    { GPIO_PE8, hal_ll_uart_module_num(UART_MODULE_4) },
    #endif
    #ifdef UART4_RX_RD9
    { GPIO_PD9, hal_ll_uart_module_num(UART_MODULE_4) },
    #endif
    #ifdef UART4_RX_RD14
    { GPIO_PD14, hal_ll_uart_module_num(UART_MODULE_4) },
    #endif
    #endif

    #ifdef UART_MODULE_5
    #ifdef UART5_RX_RD1
    { GPIO_PD1, hal_ll_uart_module_num(UART_MODULE_5) },
    #endif
    #ifdef UART5_RX_RG9
    { GPIO_PG9, hal_ll_uart_module_num(UART_MODULE_5) },
    #endif
    #ifdef UART5_RX_RB14
    { GPIO_PB14, hal_ll_uart_module_num(UART_MODULE_5) },
    #endif
    #ifdef UART5_RX_RD0
    { GPIO_PD0, hal_ll_uart_module_num(UART_MODULE_5) },
    #endif
    #ifdef UART5_RX_RD8
    { GPIO_PD8, hal_ll_uart_module_num(UART_MODULE_5) },
    #endif
    #ifdef UART5_RX_RB6
    { GPIO_PB6, hal_ll_uart_module_num(UART_MODULE_5) },
    #endif
    #ifdef UART5_RX_RD5
    { GPIO_PD5, hal_ll_uart_module_num(UART_MODULE_5) },
    #endif
    #ifdef UART5_RX_RB2
    { GPIO_PB2, hal_ll_uart_module_num(UART_MODULE_5) },
    #endif
    #ifdef UART5_RX_RF3
    { GPIO_PF3, hal_ll_uart_module_num(UART_MODULE_5) },
    #endif
    #ifdef UART5_RX_RF13
    { GPIO_PF13, hal_ll_uart_module_num(UART_MODULE_5) },
    #endif
    #ifdef UART5_RX_RF2
    { GPIO_PF2, hal_ll_uart_module_num(UART_MODULE_5) },
    #endif
    #ifdef UART5_RX_RC2
    { GPIO_PC2, hal_ll_uart_module_num(UART_MODULE_5) },
    #endif
    #ifdef UART5_RX_RE8
    { GPIO_PE8, hal_ll_uart_module_num(UART_MODULE_5) },
    #endif
    #ifdef UART5_RX_RB8
    { GPIO_PB8, hal_ll_uart_module_num(UART_MODULE_5) },
    #endif
    #ifdef UART5_RX_RF12
    { GPIO_PF12, hal_ll_uart_module_num(UART_MODULE_5) },
    #endif
    #ifdef UART5_RX_RD2
    { GPIO_PD2, hal_ll_uart_module_num(UART_MODULE_5) },
    #endif
    #ifdef UART5_RX_RG8
    { GPIO_PG8, hal_ll_uart_module_num(UART_MODULE_5) },
    #endif
    #ifdef UART5_RX_RF4
    { GPIO_PF4, hal_ll_uart_module_num(UART_MODULE_5) },
    #endif
    #ifdef UART5_RX_RD10
    { GPIO_PD10, hal_ll_uart_module_num(UART_MODULE_5) },
    #endif
    #ifdef UART5_RX_RF1
    { GPIO_PF1, hal_ll_uart_module_num(UART_MODULE_5) },
    #endif
    #ifdef UART5_RX_RB9
    { GPIO_PB9, hal_ll_uart_module_num(UART_MODULE_5) },
    #endif
    #ifdef UART5_RX_RB10
    { GPIO_PB10, hal_ll_uart_module_num(UART_MODULE_5) },
    #endif
    #ifdef UART5_RX_RC14
    { GPIO_PC14, hal_ll_uart_module_num(UART_MODULE_5) },
    #endif
    #ifdef UART5_RX_RB5
    { GPIO_PB5, hal_ll_uart_module_num(UART_MODULE_5) },
    #endif
    #ifdef UART5_RX_RC1
    { GPIO_PC1, hal_ll_uart_module_num(UART_MODULE_5) },
    #endif
    #ifdef UART5_RX_RD14
    { GPIO_PD14, hal_ll_uart_module_num(UART_MODULE_5) },
    #endif
    #ifdef UART5_RX_RG1
    { GPIO_PG1, hal_ll_uart_module_num(UART_MODULE_5) },
    #endif
    #ifdef UART5_RX_RA14
    { GPIO_PA14, hal_ll_uart_module_num(UART_MODULE_5) },
    #endif
    #ifdef UART5_RX_RD6
    { GPIO_PD6, hal_ll_uart_module_num(UART_MODULE_5) },
    #endif
    #endif

    #ifdef UART_MODULE_6
    #ifdef UART6_RX_RG9
    { GPIO_PG9, hal_ll_uart_module_num(UART_MODULE_6) },
    #endif
    #ifdef UART6_RX_RD1
    { GPIO_PD1, hal_ll_uart_module_num(UART_MODULE_6) },
    #endif
    #ifdef UART6_RX_RB14
    { GPIO_PB14, hal_ll_uart_module_num(UART_MODULE_6) },
    #endif
    #ifdef UART6_RX_RD0
    { GPIO_PD0, hal_ll_uart_module_num(UART_MODULE_6) },
    #endif
    #ifdef UART6_RX_RB6
    { GPIO_PB6, hal_ll_uart_module_num(UART_MODULE_6) },
    #endif
    #ifdef UART6_RX_RD5
    { GPIO_PD5, hal_ll_uart_module_num(UART_MODULE_6) },
    #endif
    #ifdef UART6_RX_RB2
    { GPIO_PB2, hal_ll_uart_module_num(UART_MODULE_6) },
    #endif
    #ifdef UART6_RX_RF3
    { GPIO_PF3, hal_ll_uart_module_num(UART_MODULE_6) },
    #endif
    #ifdef UART6_RX_RF13
    { GPIO_PF13, hal_ll_uart_module_num(UART_MODULE_6) },
    #endif
    #ifdef UART6_RX_RF2
    { GPIO_PF2, hal_ll_uart_module_num(UART_MODULE_6) },
    #endif
    #ifdef UART6_RX_RC2
    { GPIO_PC2, hal_ll_uart_module_num(UART_MODULE_6) },
    #endif
    #ifdef UART6_RX_RE8
    { GPIO_PE8, hal_ll_uart_module_num(UART_MODULE_6) },
    #endif
    #endif

    { HAL_LL_PIN_NC, HAL_LL_MODULE_ERROR }
    //------------ END RX
};

#ifdef __cplusplus
}
#endif

#endif // _HAL_LL_UART_PIN_MAP_H_
// ---------------------------------------------------------------------- END
