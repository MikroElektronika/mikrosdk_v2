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

/*!< @brief Helper macro for getting adequate module index number */
#define hal_ll_uart_module_num(_module_num) (_module_num - 1)

/*!< @brief Pin structure */
typedef struct
{
    hal_ll_pin_name_t pin;
    uint8_t module_index;
    bool alternate_pins;
} hal_ll_uart_pin_map_t;

/*!< @brief UART TX pins */
static const hal_ll_uart_pin_map_t hal_ll_uart_tx_map[] = {
    //------------ BEGIN TX
    #ifdef UART1_TX_RB4
    {GPIO_PB4, hal_ll_uart_module_num(UART_MODULE_1), false},
    #endif
    #ifdef UART1_TX_RC13_ALT
    {GPIO_PC13, hal_ll_uart_module_num(UART_MODULE_1), true},
    #endif
    #ifdef UART1_TX_RF3
    {GPIO_PF3, hal_ll_uart_module_num(UART_MODULE_1), false},
    #endif
    #ifdef UART2_TX_RF5
    {GPIO_PF5, hal_ll_uart_module_num(UART_MODULE_2), false},
    #endif
    #ifdef UART1_TX_RA4_RP20
    {GPIO_PA4, hal_ll_uart_module_num(UART_MODULE_1), false},
    #endif
    #ifdef UART1_TX_RB10_RP42
    {GPIO_PB10, hal_ll_uart_module_num(UART_MODULE_1), false},
    #endif
    #ifdef UART1_TX_RB11_RP43
    {GPIO_PB11, hal_ll_uart_module_num(UART_MODULE_1), false},
    #endif
    #ifdef UART1_TX_RB3_RP35
    {GPIO_PB3, hal_ll_uart_module_num(UART_MODULE_1), false},
    #endif
    #ifdef UART1_TX_RB4_RP36
    {GPIO_PB4, hal_ll_uart_module_num(UART_MODULE_1), false},
    #endif
    #ifdef UART1_TX_RB5_RP37
    {GPIO_PB5, hal_ll_uart_module_num(UART_MODULE_1), false},
    #endif
    #ifdef UART1_TX_RB6_RP38
    {GPIO_PB6, hal_ll_uart_module_num(UART_MODULE_1), false},
    #endif
    #ifdef UART1_TX_RB7_RP39
    {GPIO_PB7, hal_ll_uart_module_num(UART_MODULE_1), false},
    #endif
    #ifdef UART1_TX_RB8_RP40
    {GPIO_PB8, hal_ll_uart_module_num(UART_MODULE_1), false},
    #endif
    #ifdef UART1_TX_RB9_RP41
    {GPIO_PB9, hal_ll_uart_module_num(UART_MODULE_1), false},
    #endif
    #ifdef UART1_TX_RC0_RP48
    {GPIO_PC0, hal_ll_uart_module_num(UART_MODULE_1), false},
    #endif
    #ifdef UART1_TX_RC1_RP49
    {GPIO_PC1, hal_ll_uart_module_num(UART_MODULE_1), false},
    #endif
    #ifdef UART1_TX_RC6_RP54
    {GPIO_PC6, hal_ll_uart_module_num(UART_MODULE_1), false},
    #endif
    #ifdef UART1_TX_RC7_RP55
    {GPIO_PC7, hal_ll_uart_module_num(UART_MODULE_1), false},
    #endif
    #ifdef UART1_TX_RC8_RP56
    {GPIO_PC8, hal_ll_uart_module_num(UART_MODULE_1), false},
    #endif
    #ifdef UART1_TX_RC9_RP57
    {GPIO_PC9, hal_ll_uart_module_num(UART_MODULE_1), false},
    #endif
    #ifdef UART2_TX_RA4_RP20
    {GPIO_PA4, hal_ll_uart_module_num(UART_MODULE_2), false},
    #endif
    #ifdef UART2_TX_RB10_RP42
    {GPIO_PB10, hal_ll_uart_module_num(UART_MODULE_2), false},
    #endif
    #ifdef UART2_TX_RB11_RP43
    {GPIO_PB11, hal_ll_uart_module_num(UART_MODULE_2), false},
    #endif
    #ifdef UART2_TX_RB3_RP35
    {GPIO_PB3, hal_ll_uart_module_num(UART_MODULE_2), false},
    #endif
    #ifdef UART2_TX_RB4_RP36
    {GPIO_PB4, hal_ll_uart_module_num(UART_MODULE_2), false},
    #endif
    #ifdef UART2_TX_RB5_RP37
    {GPIO_PB5, hal_ll_uart_module_num(UART_MODULE_2), false},
    #endif
    #ifdef UART2_TX_RB6_RP38
    {GPIO_PB6, hal_ll_uart_module_num(UART_MODULE_2), false},
    #endif
    #ifdef UART2_TX_RB7_RP39
    {GPIO_PB7, hal_ll_uart_module_num(UART_MODULE_2), false},
    #endif
    #ifdef UART2_TX_RB8_RP40
    {GPIO_PB8, hal_ll_uart_module_num(UART_MODULE_2), false},
    #endif
    #ifdef UART2_TX_RB9_RP41
    {GPIO_PB9, hal_ll_uart_module_num(UART_MODULE_2), false},
    #endif
    #ifdef UART2_TX_RC0_RP48
    {GPIO_PC0, hal_ll_uart_module_num(UART_MODULE_2), false},
    #endif
    #ifdef UART2_TX_RC1_RP49
    {GPIO_PC1, hal_ll_uart_module_num(UART_MODULE_2), false},
    #endif
    #ifdef UART2_TX_RC6_RP54
    {GPIO_PC6, hal_ll_uart_module_num(UART_MODULE_2), false},
    #endif
    #ifdef UART2_TX_RC7_RP55
    {GPIO_PC7, hal_ll_uart_module_num(UART_MODULE_2), false},
    #endif
    #ifdef UART2_TX_RC8_RP56
    {GPIO_PC8, hal_ll_uart_module_num(UART_MODULE_2), false},
    #endif
    #ifdef UART2_TX_RC9_RP57
    {GPIO_PC9, hal_ll_uart_module_num(UART_MODULE_2), false},
    #endif
    #ifdef UART3_TX_RA4_RP20
    {GPIO_PA4, hal_ll_uart_module_num(UART_MODULE_3), false},
    #endif
    #ifdef UART3_TX_RB10_RP42
    {GPIO_PB10, hal_ll_uart_module_num(UART_MODULE_3), false},
    #endif
    #ifdef UART3_TX_RB11_RP43
    {GPIO_PB11, hal_ll_uart_module_num(UART_MODULE_3), false},
    #endif
    #ifdef UART3_TX_RB3_RP35
    {GPIO_PB3, hal_ll_uart_module_num(UART_MODULE_3), false},
    #endif
    #ifdef UART3_TX_RB4_RP36
    {GPIO_PB4, hal_ll_uart_module_num(UART_MODULE_3), false},
    #endif
    #ifdef UART3_TX_RB5_RP37
    {GPIO_PB5, hal_ll_uart_module_num(UART_MODULE_3), false},
    #endif
    #ifdef UART3_TX_RB6_RP38
    {GPIO_PB6, hal_ll_uart_module_num(UART_MODULE_3), false},
    #endif
    #ifdef UART3_TX_RB7_RP39
    {GPIO_PB7, hal_ll_uart_module_num(UART_MODULE_3), false},
    #endif
    #ifdef UART3_TX_RB8_RP40
    {GPIO_PB8, hal_ll_uart_module_num(UART_MODULE_3), false},
    #endif
    #ifdef UART3_TX_RB9_RP41
    {GPIO_PB9, hal_ll_uart_module_num(UART_MODULE_3), false},
    #endif
    #ifdef UART3_TX_RC0_RP48
    {GPIO_PC0, hal_ll_uart_module_num(UART_MODULE_3), false},
    #endif
    #ifdef UART3_TX_RC1_RP49
    {GPIO_PC1, hal_ll_uart_module_num(UART_MODULE_3), false},
    #endif
    #ifdef UART3_TX_RC6_RP54
    {GPIO_PC6, hal_ll_uart_module_num(UART_MODULE_3), false},
    #endif
    #ifdef UART3_TX_RC7_RP55
    {GPIO_PC7, hal_ll_uart_module_num(UART_MODULE_3), false},
    #endif
    #ifdef UART3_TX_RC8_RP56
    {GPIO_PC8, hal_ll_uart_module_num(UART_MODULE_3), false},
    #endif
    #ifdef UART3_TX_RC9_RP57
    {GPIO_PC9, hal_ll_uart_module_num(UART_MODULE_3), false},
    #endif
    #ifdef UART4_TX_RA4_RP20
    {GPIO_PA4, hal_ll_uart_module_num(UART_MODULE_4), false},
    #endif
    #ifdef UART4_TX_RB10_RP42
    {GPIO_PB10, hal_ll_uart_module_num(UART_MODULE_4), false},
    #endif
    #ifdef UART4_TX_RB11_RP43
    {GPIO_PB11, hal_ll_uart_module_num(UART_MODULE_4), false},
    #endif
    #ifdef UART4_TX_RB3_RP35
    {GPIO_PB3, hal_ll_uart_module_num(UART_MODULE_4), false},
    #endif
    #ifdef UART4_TX_RB4_RP36
    {GPIO_PB4, hal_ll_uart_module_num(UART_MODULE_4), false},
    #endif
    #ifdef UART4_TX_RB5_RP37
    {GPIO_PB5, hal_ll_uart_module_num(UART_MODULE_4), false},
    #endif
    #ifdef UART4_TX_RB6_RP38
    {GPIO_PB6, hal_ll_uart_module_num(UART_MODULE_4), false},
    #endif
    #ifdef UART4_TX_RB7_RP39
    {GPIO_PB7, hal_ll_uart_module_num(UART_MODULE_4), false},
    #endif
    #ifdef UART4_TX_RB8_RP40
    {GPIO_PB8, hal_ll_uart_module_num(UART_MODULE_4), false},
    #endif
    #ifdef UART4_TX_RB9_RP41
    {GPIO_PB9, hal_ll_uart_module_num(UART_MODULE_4), false},
    #endif
    #ifdef UART4_TX_RC0_RP48
    {GPIO_PC0, hal_ll_uart_module_num(UART_MODULE_4), false},
    #endif
    #ifdef UART4_TX_RC1_RP49
    {GPIO_PC1, hal_ll_uart_module_num(UART_MODULE_4), false},
    #endif
    #ifdef UART4_TX_RC6_RP54
    {GPIO_PC6, hal_ll_uart_module_num(UART_MODULE_4), false},
    #endif
    #ifdef UART4_TX_RC7_RP55
    {GPIO_PC7, hal_ll_uart_module_num(UART_MODULE_4), false},
    #endif
    #ifdef UART4_TX_RC8_RP56
    {GPIO_PC8, hal_ll_uart_module_num(UART_MODULE_4), false},
    #endif
    #ifdef UART4_TX_RC9_RP57
    {GPIO_PC9, hal_ll_uart_module_num(UART_MODULE_4), false},
    #endif
    #ifdef UART1_TX_RD5_RP69
    {GPIO_PD5, hal_ll_uart_module_num(UART_MODULE_1), false},
    #endif
    #ifdef UART1_TX_RD6_RP70
    {GPIO_PD6, hal_ll_uart_module_num(UART_MODULE_1), false},
    #endif
    #ifdef UART1_TX_RF1_RP97
    {GPIO_PF1, hal_ll_uart_module_num(UART_MODULE_1), false},
    #endif
    #ifdef UART1_TX_RG6_RP118
    {GPIO_PG6, hal_ll_uart_module_num(UART_MODULE_1), false},
    #endif
    #ifdef UART1_TX_RG8_RP120
    {GPIO_PG8, hal_ll_uart_module_num(UART_MODULE_1), false},
    #endif
    #ifdef UART2_TX_RD5_RP69
    {GPIO_PD5, hal_ll_uart_module_num(UART_MODULE_2), false},
    #endif
    #ifdef UART2_TX_RD6_RP70
    {GPIO_PD6, hal_ll_uart_module_num(UART_MODULE_2), false},
    #endif
    #ifdef UART2_TX_RF1_RP97
    {GPIO_PF1, hal_ll_uart_module_num(UART_MODULE_2), false},
    #endif
    #ifdef UART2_TX_RG6_RP118
    {GPIO_PG6, hal_ll_uart_module_num(UART_MODULE_2), false},
    #endif
    #ifdef UART2_TX_RG8_RP120
    {GPIO_PG8, hal_ll_uart_module_num(UART_MODULE_2), false},
    #endif
    #ifdef UART3_TX_RD5_RP69
    {GPIO_PD5, hal_ll_uart_module_num(UART_MODULE_3), false},
    #endif
    #ifdef UART3_TX_RD6_RP70
    {GPIO_PD6, hal_ll_uart_module_num(UART_MODULE_3), false},
    #endif
    #ifdef UART3_TX_RF1_RP97
    {GPIO_PF1, hal_ll_uart_module_num(UART_MODULE_3), false},
    #endif
    #ifdef UART3_TX_RG6_RP118
    {GPIO_PG6, hal_ll_uart_module_num(UART_MODULE_3), false},
    #endif
    #ifdef UART3_TX_RG8_RP120
    {GPIO_PG8, hal_ll_uart_module_num(UART_MODULE_3), false},
    #endif
    #ifdef UART4_TX_RD5_RP69
    {GPIO_PD5, hal_ll_uart_module_num(UART_MODULE_4), false},
    #endif
    #ifdef UART4_TX_RD6_RP70
    {GPIO_PD6, hal_ll_uart_module_num(UART_MODULE_4), false},
    #endif
    #ifdef UART4_TX_RF1_RP97
    {GPIO_PF1, hal_ll_uart_module_num(UART_MODULE_4), false},
    #endif
    #ifdef UART4_TX_RG6_RP118
    {GPIO_PG6, hal_ll_uart_module_num(UART_MODULE_4), false},
    #endif
    #ifdef UART4_TX_RG8_RP120
    {GPIO_PG8, hal_ll_uart_module_num(UART_MODULE_4), false},
    #endif
    #ifdef UART1_TX_RE1_RP81
    {GPIO_PE1, hal_ll_uart_module_num(UART_MODULE_1), false},
    #endif
    #ifdef UART1_TX_RG1_RP113
    {GPIO_PG1, hal_ll_uart_module_num(UART_MODULE_1), false},
    #endif
    #ifdef UART1_TX_RG13_RP125
    {GPIO_PG13, hal_ll_uart_module_num(UART_MODULE_1), false},
    #endif
    #ifdef UART1_TX_RG14_RP126
    {GPIO_PG14, hal_ll_uart_module_num(UART_MODULE_1), false},
    #endif
    #ifdef UART1_TX_RG15_RP127
    {GPIO_PG15, hal_ll_uart_module_num(UART_MODULE_1), false},
    #endif
    #ifdef UART2_TX_RE1_RP81
    {GPIO_PE1, hal_ll_uart_module_num(UART_MODULE_2), false},
    #endif
    #ifdef UART2_TX_RG1_RP113
    {GPIO_PG1, hal_ll_uart_module_num(UART_MODULE_2), false},
    #endif
    #ifdef UART2_TX_RG13_RP125
    {GPIO_PG13, hal_ll_uart_module_num(UART_MODULE_2), false},
    #endif
    #ifdef UART2_TX_RG14_RP126
    {GPIO_PG14, hal_ll_uart_module_num(UART_MODULE_2), false},
    #endif
    #ifdef UART2_TX_RG15_RP127
    {GPIO_PG15, hal_ll_uart_module_num(UART_MODULE_2), false},
    #endif
    #ifdef UART3_TX_RE1_RP81
    {GPIO_PE1, hal_ll_uart_module_num(UART_MODULE_3), false},
    #endif
    #ifdef UART3_TX_RG1_RP113
    {GPIO_PG1, hal_ll_uart_module_num(UART_MODULE_3), false},
    #endif
    #ifdef UART3_TX_RG13_RP125
    {GPIO_PG13, hal_ll_uart_module_num(UART_MODULE_3), false},
    #endif
    #ifdef UART3_TX_RG14_RP126
    {GPIO_PG14, hal_ll_uart_module_num(UART_MODULE_3), false},
    #endif
    #ifdef UART3_TX_RG15_RP127
    {GPIO_PG15, hal_ll_uart_module_num(UART_MODULE_3), false},
    #endif
    #ifdef UART4_TX_RE1_RP81
    {GPIO_PE1, hal_ll_uart_module_num(UART_MODULE_4), false},
    #endif
    #ifdef UART4_TX_RG1_RP113
    {GPIO_PG1, hal_ll_uart_module_num(UART_MODULE_4), false},
    #endif
    #ifdef UART4_TX_RG13_RP125
    {GPIO_PG13, hal_ll_uart_module_num(UART_MODULE_4), false},
    #endif
    #ifdef UART4_TX_RG14_RP126
    {GPIO_PG14, hal_ll_uart_module_num(UART_MODULE_4), false},
    #endif
    #ifdef UART4_TX_RG15_RP127
    {GPIO_PG15, hal_ll_uart_module_num(UART_MODULE_4), false},
    #endif
    #ifdef UART1_TX_RA0_RP16
    {GPIO_PA0, hal_ll_uart_module_num(UART_MODULE_1), false},
    #endif
    #ifdef UART1_TX_RA1_RP17
    {GPIO_PA1, hal_ll_uart_module_num(UART_MODULE_1), false},
    #endif
    #ifdef UART1_TX_RA2_RP18
    {GPIO_PA2, hal_ll_uart_module_num(UART_MODULE_1), false},
    #endif
    #ifdef UART1_TX_RA3_RP19
    {GPIO_PA3, hal_ll_uart_module_num(UART_MODULE_1), false},
    #endif
    #ifdef UART1_TX_RB0_RP32
    {GPIO_PB0, hal_ll_uart_module_num(UART_MODULE_1), false},
    #endif
    #ifdef UART1_TX_RB1_RP33
    {GPIO_PB1, hal_ll_uart_module_num(UART_MODULE_1), false},
    #endif
    #ifdef UART1_TX_RB12_RP44
    {GPIO_PB12, hal_ll_uart_module_num(UART_MODULE_1), false},
    #endif
    #ifdef UART1_TX_RB13_RP45
    {GPIO_PB13, hal_ll_uart_module_num(UART_MODULE_1), false},
    #endif
    #ifdef UART1_TX_RB14_RP46
    {GPIO_PB14, hal_ll_uart_module_num(UART_MODULE_1), false},
    #endif
    #ifdef UART1_TX_RB15_RP47
    {GPIO_PB15, hal_ll_uart_module_num(UART_MODULE_1), false},
    #endif
    #ifdef UART1_TX_RB2_RP34
    {GPIO_PB2, hal_ll_uart_module_num(UART_MODULE_1), false},
    #endif
    #ifdef UART2_TX_RA0_RP16
    {GPIO_PA0, hal_ll_uart_module_num(UART_MODULE_2), false},
    #endif
    #ifdef UART2_TX_RA1_RP17
    {GPIO_PA1, hal_ll_uart_module_num(UART_MODULE_2), false},
    #endif
    #ifdef UART2_TX_RA2_RP18
    {GPIO_PA2, hal_ll_uart_module_num(UART_MODULE_2), false},
    #endif
    #ifdef UART2_TX_RA3_RP19
    {GPIO_PA3, hal_ll_uart_module_num(UART_MODULE_2), false},
    #endif
    #ifdef UART2_TX_RB0_RP32
    {GPIO_PB0, hal_ll_uart_module_num(UART_MODULE_2), false},
    #endif
    #ifdef UART2_TX_RB1_RP33
    {GPIO_PB1, hal_ll_uart_module_num(UART_MODULE_2), false},
    #endif
    #ifdef UART2_TX_RB12_RP44
    {GPIO_PB12, hal_ll_uart_module_num(UART_MODULE_2), false},
    #endif
    #ifdef UART2_TX_RB13_RP45
    {GPIO_PB13, hal_ll_uart_module_num(UART_MODULE_2), false},
    #endif
    #ifdef UART2_TX_RB14_RP46
    {GPIO_PB14, hal_ll_uart_module_num(UART_MODULE_2), false},
    #endif
    #ifdef UART2_TX_RB15_RP47
    {GPIO_PB15, hal_ll_uart_module_num(UART_MODULE_2), false},
    #endif
    #ifdef UART2_TX_RB2_RP34
    {GPIO_PB2, hal_ll_uart_module_num(UART_MODULE_2), false},
    #endif
    #ifdef UART1_TX_RC10_RP58
    {GPIO_PC10, hal_ll_uart_module_num(UART_MODULE_1), false},
    #endif
    #ifdef UART1_TX_RC12_RP60
    {GPIO_PC12, hal_ll_uart_module_num(UART_MODULE_1), false},
    #endif
    #ifdef UART1_TX_RC13_RP61
    {GPIO_PC13, hal_ll_uart_module_num(UART_MODULE_1), false},
    #endif
    #ifdef UART1_TX_RC2_RP50
    {GPIO_PC2, hal_ll_uart_module_num(UART_MODULE_1), false},
    #endif
    #ifdef UART1_TX_RC3_RP51
    {GPIO_PC3, hal_ll_uart_module_num(UART_MODULE_1), false},
    #endif
    #ifdef UART1_TX_RC4_RP52
    {GPIO_PC4, hal_ll_uart_module_num(UART_MODULE_1), false},
    #endif
    #ifdef UART1_TX_RC5_RP53
    {GPIO_PC5, hal_ll_uart_module_num(UART_MODULE_1), false},
    #endif
    #ifdef UART2_TX_RC10_RP58
    {GPIO_PC10, hal_ll_uart_module_num(UART_MODULE_2), false},
    #endif
    #ifdef UART2_TX_RC12_RP60
    {GPIO_PC12, hal_ll_uart_module_num(UART_MODULE_2), false},
    #endif
    #ifdef UART2_TX_RC13_RP61
    {GPIO_PC13, hal_ll_uart_module_num(UART_MODULE_2), false},
    #endif
    #ifdef UART2_TX_RC2_RP50
    {GPIO_PC2, hal_ll_uart_module_num(UART_MODULE_2), false},
    #endif
    #ifdef UART2_TX_RC3_RP51
    {GPIO_PC3, hal_ll_uart_module_num(UART_MODULE_2), false},
    #endif
    #ifdef UART2_TX_RC4_RP52
    {GPIO_PC4, hal_ll_uart_module_num(UART_MODULE_2), false},
    #endif
    #ifdef UART2_TX_RC5_RP53
    {GPIO_PC5, hal_ll_uart_module_num(UART_MODULE_2), false},
    #endif
    #ifdef UART1_TX_RD10_RP74
    {GPIO_PD10, hal_ll_uart_module_num(UART_MODULE_1), false},
    #endif
    #ifdef UART1_TX_RD4_RP68
    {GPIO_PD4, hal_ll_uart_module_num(UART_MODULE_1), false},
    #endif
    #ifdef UART2_TX_RD10_RP74
    {GPIO_PD10, hal_ll_uart_module_num(UART_MODULE_2), false},
    #endif
    #ifdef UART2_TX_RD4_RP68
    {GPIO_PD4, hal_ll_uart_module_num(UART_MODULE_2), false},
    #endif
    #ifdef UART1_TX_RC14_RP62
    {GPIO_PC14, hal_ll_uart_module_num(UART_MODULE_1), false},
    #endif
    #ifdef UART1_TX_RC15_RP63
    {GPIO_PC15, hal_ll_uart_module_num(UART_MODULE_1), false},
    #endif
    #ifdef UART1_TX_RD0_RP64
    {GPIO_PD0, hal_ll_uart_module_num(UART_MODULE_1), false},
    #endif
    #ifdef UART1_TX_RD1_RP65
    {GPIO_PD1, hal_ll_uart_module_num(UART_MODULE_1), false},
    #endif
    #ifdef UART1_TX_RD11_RP75
    {GPIO_PD11, hal_ll_uart_module_num(UART_MODULE_1), false},
    #endif
    #ifdef UART1_TX_RD12_RP76
    {GPIO_PD12, hal_ll_uart_module_num(UART_MODULE_1), false},
    #endif
    #ifdef UART1_TX_RD2_RP66
    {GPIO_PD2, hal_ll_uart_module_num(UART_MODULE_1), false},
    #endif
    #ifdef UART1_TX_RD3_RP67
    {GPIO_PD3, hal_ll_uart_module_num(UART_MODULE_1), false},
    #endif
    #ifdef UART1_TX_RD7_RP71
    {GPIO_PD7, hal_ll_uart_module_num(UART_MODULE_1), false},
    #endif
    #ifdef UART1_TX_RD8_RP72
    {GPIO_PD8, hal_ll_uart_module_num(UART_MODULE_1), false},
    #endif
    #ifdef UART1_TX_RD9_RP73
    {GPIO_PD9, hal_ll_uart_module_num(UART_MODULE_1), false},
    #endif
    #ifdef UART2_TX_RC14_RP62
    {GPIO_PC14, hal_ll_uart_module_num(UART_MODULE_2), false},
    #endif
    #ifdef UART2_TX_RC15_RP63
    {GPIO_PC15, hal_ll_uart_module_num(UART_MODULE_2), false},
    #endif
    #ifdef UART2_TX_RD0_RP64
    {GPIO_PD0, hal_ll_uart_module_num(UART_MODULE_2), false},
    #endif
    #ifdef UART2_TX_RD1_RP65
    {GPIO_PD1, hal_ll_uart_module_num(UART_MODULE_2), false},
    #endif
    #ifdef UART2_TX_RD11_RP75
    {GPIO_PD11, hal_ll_uart_module_num(UART_MODULE_2), false},
    #endif
    #ifdef UART2_TX_RD12_RP76
    {GPIO_PD12, hal_ll_uart_module_num(UART_MODULE_2), false},
    #endif
    #ifdef UART2_TX_RD2_RP66
    {GPIO_PD2, hal_ll_uart_module_num(UART_MODULE_2), false},
    #endif
    #ifdef UART2_TX_RD3_RP67
    {GPIO_PD3, hal_ll_uart_module_num(UART_MODULE_2), false},
    #endif
    #ifdef UART2_TX_RD7_RP71
    {GPIO_PD7, hal_ll_uart_module_num(UART_MODULE_2), false},
    #endif
    #ifdef UART2_TX_RD8_RP72
    {GPIO_PD8, hal_ll_uart_module_num(UART_MODULE_2), false},
    #endif
    #ifdef UART2_TX_RD9_RP73
    {GPIO_PD9, hal_ll_uart_module_num(UART_MODULE_2), false},
    #endif
    #ifdef UART1_TX_RC11_RP59
    {GPIO_PC11, hal_ll_uart_module_num(UART_MODULE_1), false},
    #endif
    #ifdef UART2_TX_RC11_RP59
    {GPIO_PC11, hal_ll_uart_module_num(UART_MODULE_2), false},
    #endif
    #ifdef UART1_TX_RE0_RP80
    {GPIO_PE0, hal_ll_uart_module_num(UART_MODULE_1), false},
    #endif
    #ifdef UART1_TX_RE2_RP82
    {GPIO_PE2, hal_ll_uart_module_num(UART_MODULE_1), false},
    #endif
    #ifdef UART1_TX_RE4_RP84
    {GPIO_PE4, hal_ll_uart_module_num(UART_MODULE_1), false},
    #endif
    #ifdef UART1_TX_RE5_RP85
    {GPIO_PE5, hal_ll_uart_module_num(UART_MODULE_1), false},
    #endif
    #ifdef UART1_TX_RE7_RP87
    {GPIO_PE7, hal_ll_uart_module_num(UART_MODULE_1), false},
    #endif
    #ifdef UART1_TX_RF0_RP96
    {GPIO_PF0, hal_ll_uart_module_num(UART_MODULE_1), false},
    #endif
    #ifdef UART1_TX_RF3_RP99
    {GPIO_PF3, hal_ll_uart_module_num(UART_MODULE_1), false},
    #endif
    #ifdef UART1_TX_RF4_RP100
    {GPIO_PF4, hal_ll_uart_module_num(UART_MODULE_1), false},
    #endif
    #ifdef UART1_TX_RF5_RP101
    {GPIO_PF5, hal_ll_uart_module_num(UART_MODULE_1), false},
    #endif
    #ifdef UART2_TX_RE0_RP80
    {GPIO_PE0, hal_ll_uart_module_num(UART_MODULE_2), false},
    #endif
    #ifdef UART2_TX_RE2_RP82
    {GPIO_PE2, hal_ll_uart_module_num(UART_MODULE_2), false},
    #endif
    #ifdef UART2_TX_RE4_RP84
    {GPIO_PE4, hal_ll_uart_module_num(UART_MODULE_2), false},
    #endif
    #ifdef UART2_TX_RE5_RP85
    {GPIO_PE5, hal_ll_uart_module_num(UART_MODULE_2), false},
    #endif
    #ifdef UART2_TX_RE7_RP87
    {GPIO_PE7, hal_ll_uart_module_num(UART_MODULE_2), false},
    #endif
    #ifdef UART2_TX_RF0_RP96
    {GPIO_PF0, hal_ll_uart_module_num(UART_MODULE_2), false},
    #endif
    #ifdef UART2_TX_RF3_RP99
    {GPIO_PF3, hal_ll_uart_module_num(UART_MODULE_2), false},
    #endif
    #ifdef UART2_TX_RF4_RP100
    {GPIO_PF4, hal_ll_uart_module_num(UART_MODULE_2), false},
    #endif
    #ifdef UART2_TX_RF5_RP101
    {GPIO_PF5, hal_ll_uart_module_num(UART_MODULE_2), false},
    #endif
    #ifdef UART3_TX_RD0_RP64
    {GPIO_PD0, hal_ll_uart_module_num(UART_MODULE_3), false},
    #endif
    #ifdef UART3_TX_RD1_RP65
    {GPIO_PD1, hal_ll_uart_module_num(UART_MODULE_3), false},
    #endif
    #ifdef UART3_TX_RD2_RP66
    {GPIO_PD2, hal_ll_uart_module_num(UART_MODULE_3), false},
    #endif
    #ifdef UART3_TX_RD3_RP67
    {GPIO_PD3, hal_ll_uart_module_num(UART_MODULE_3), false},
    #endif
    #ifdef UART3_TX_RD4_RP68
    {GPIO_PD4, hal_ll_uart_module_num(UART_MODULE_3), false},
    #endif
    #ifdef UART3_TX_RD7_RP71
    {GPIO_PD7, hal_ll_uart_module_num(UART_MODULE_3), false},
    #endif
    #ifdef UART3_TX_RE0_RP80
    {GPIO_PE0, hal_ll_uart_module_num(UART_MODULE_3), false},
    #endif
    #ifdef UART3_TX_RE2_RP82
    {GPIO_PE2, hal_ll_uart_module_num(UART_MODULE_3), false},
    #endif
    #ifdef UART3_TX_RE4_RP84
    {GPIO_PE4, hal_ll_uart_module_num(UART_MODULE_3), false},
    #endif
    #ifdef UART3_TX_RE5_RP85
    {GPIO_PE5, hal_ll_uart_module_num(UART_MODULE_3), false},
    #endif
    #ifdef UART3_TX_RE7_RP87
    {GPIO_PE7, hal_ll_uart_module_num(UART_MODULE_3), false},
    #endif
    #ifdef UART3_TX_RF0_RP96
    {GPIO_PF0, hal_ll_uart_module_num(UART_MODULE_3), false},
    #endif
    #ifdef UART3_TX_RF3_RP99
    {GPIO_PF3, hal_ll_uart_module_num(UART_MODULE_3), false},
    #endif
    #ifdef UART3_TX_RF4_RP100
    {GPIO_PF4, hal_ll_uart_module_num(UART_MODULE_3), false},
    #endif
    #ifdef UART3_TX_RF5_RP101
    {GPIO_PF5, hal_ll_uart_module_num(UART_MODULE_3), false},
    #endif
    #ifdef UART4_TX_RD0_RP64
    {GPIO_PD0, hal_ll_uart_module_num(UART_MODULE_4), false},
    #endif
    #ifdef UART4_TX_RD1_RP65
    {GPIO_PD1, hal_ll_uart_module_num(UART_MODULE_4), false},
    #endif
    #ifdef UART4_TX_RD2_RP66
    {GPIO_PD2, hal_ll_uart_module_num(UART_MODULE_4), false},
    #endif
    #ifdef UART4_TX_RD3_RP67
    {GPIO_PD3, hal_ll_uart_module_num(UART_MODULE_4), false},
    #endif
    #ifdef UART4_TX_RD4_RP68
    {GPIO_PD4, hal_ll_uart_module_num(UART_MODULE_4), false},
    #endif
    #ifdef UART4_TX_RD7_RP71
    {GPIO_PD7, hal_ll_uart_module_num(UART_MODULE_4), false},
    #endif
    #ifdef UART4_TX_RE0_RP80
    {GPIO_PE0, hal_ll_uart_module_num(UART_MODULE_4), false},
    #endif
    #ifdef UART4_TX_RE2_RP82
    {GPIO_PE2, hal_ll_uart_module_num(UART_MODULE_4), false},
    #endif
    #ifdef UART4_TX_RE4_RP84
    {GPIO_PE4, hal_ll_uart_module_num(UART_MODULE_4), false},
    #endif
    #ifdef UART4_TX_RE5_RP85
    {GPIO_PE5, hal_ll_uart_module_num(UART_MODULE_4), false},
    #endif
    #ifdef UART4_TX_RE7_RP87
    {GPIO_PE7, hal_ll_uart_module_num(UART_MODULE_4), false},
    #endif
    #ifdef UART4_TX_RF0_RP96
    {GPIO_PF0, hal_ll_uart_module_num(UART_MODULE_4), false},
    #endif
    #ifdef UART4_TX_RF3_RP99
    {GPIO_PF3, hal_ll_uart_module_num(UART_MODULE_4), false},
    #endif
    #ifdef UART4_TX_RF4_RP100
    {GPIO_PF4, hal_ll_uart_module_num(UART_MODULE_4), false},
    #endif
    #ifdef UART4_TX_RF5_RP101
    {GPIO_PF5, hal_ll_uart_module_num(UART_MODULE_4), false},
    #endif
    #ifdef UART1_TX_RD15_RP79
    {GPIO_PD15, hal_ll_uart_module_num(UART_MODULE_1), false},
    #endif
    #ifdef UART1_TX_RF12_RP108
    {GPIO_PF12, hal_ll_uart_module_num(UART_MODULE_1), false},
    #endif
    #ifdef UART1_TX_RF13_RP109
    {GPIO_PF13, hal_ll_uart_module_num(UART_MODULE_1), false},
    #endif
    #ifdef UART1_TX_RF2_RP98
    {GPIO_PF2, hal_ll_uart_module_num(UART_MODULE_1), false},
    #endif
    #ifdef UART1_TX_RF8_RP104
    {GPIO_PF8, hal_ll_uart_module_num(UART_MODULE_1), false},
    #endif
    #ifdef UART1_TX_RG0_RP112
    {GPIO_PG0, hal_ll_uart_module_num(UART_MODULE_1), false},
    #endif
    #ifdef UART2_TX_RD15_RP79
    {GPIO_PD15, hal_ll_uart_module_num(UART_MODULE_2), false},
    #endif
    #ifdef UART2_TX_RF12_RP108
    {GPIO_PF12, hal_ll_uart_module_num(UART_MODULE_2), false},
    #endif
    #ifdef UART2_TX_RF13_RP109
    {GPIO_PF13, hal_ll_uart_module_num(UART_MODULE_2), false},
    #endif
    #ifdef UART2_TX_RF2_RP98
    {GPIO_PF2, hal_ll_uart_module_num(UART_MODULE_2), false},
    #endif
    #ifdef UART2_TX_RF8_RP104
    {GPIO_PF8, hal_ll_uart_module_num(UART_MODULE_2), false},
    #endif
    #ifdef UART2_TX_RG0_RP112
    {GPIO_PG0, hal_ll_uart_module_num(UART_MODULE_2), false},
    #endif
    #ifdef UART3_TX_RD15_RP79
    {GPIO_PD15, hal_ll_uart_module_num(UART_MODULE_3), false},
    #endif
    #ifdef UART3_TX_RF12_RP108
    {GPIO_PF12, hal_ll_uart_module_num(UART_MODULE_3), false},
    #endif
    #ifdef UART3_TX_RF13_RP109
    {GPIO_PF13, hal_ll_uart_module_num(UART_MODULE_3), false},
    #endif
    #ifdef UART3_TX_RF2_RP98
    {GPIO_PF2, hal_ll_uart_module_num(UART_MODULE_3), false},
    #endif
    #ifdef UART3_TX_RF8_RP104
    {GPIO_PF8, hal_ll_uart_module_num(UART_MODULE_3), false},
    #endif
    #ifdef UART3_TX_RG0_RP112
    {GPIO_PG0, hal_ll_uart_module_num(UART_MODULE_3), false},
    #endif
    #ifdef UART4_TX_RD15_RP79
    {GPIO_PD15, hal_ll_uart_module_num(UART_MODULE_4), false},
    #endif
    #ifdef UART4_TX_RF12_RP108
    {GPIO_PF12, hal_ll_uart_module_num(UART_MODULE_4), false},
    #endif
    #ifdef UART4_TX_RF13_RP109
    {GPIO_PF13, hal_ll_uart_module_num(UART_MODULE_4), false},
    #endif
    #ifdef UART4_TX_RF2_RP98
    {GPIO_PF2, hal_ll_uart_module_num(UART_MODULE_4), false},
    #endif
    #ifdef UART4_TX_RF8_RP104
    {GPIO_PF8, hal_ll_uart_module_num(UART_MODULE_4), false},
    #endif
    #ifdef UART4_TX_RG0_RP112
    {GPIO_PG0, hal_ll_uart_module_num(UART_MODULE_4), false},
    #endif
    #ifdef UART1_TX_RF6_RP102
    {GPIO_PF6, hal_ll_uart_module_num(UART_MODULE_1), false},
    #endif
    #ifdef UART2_TX_RF6_RP102
    {GPIO_PF6, hal_ll_uart_module_num(UART_MODULE_2), false},
    #endif
    #ifdef UART3_TX_RF6_RP102
    {GPIO_PF6, hal_ll_uart_module_num(UART_MODULE_3), false},
    #endif
    #ifdef UART4_TX_RF6_RP102
    {GPIO_PF6, hal_ll_uart_module_num(UART_MODULE_4), false},
    #endif
    #ifdef UART1_TX_RB0_RP0
    {GPIO_PB0, hal_ll_uart_module_num(UART_MODULE_1), false},
    #endif
    #ifdef UART1_TX_RB1_RP1
    {GPIO_PB1, hal_ll_uart_module_num(UART_MODULE_1), false},
    #endif
    #ifdef UART1_TX_RB10_RP10
    {GPIO_PB10, hal_ll_uart_module_num(UART_MODULE_1), false},
    #endif
    #ifdef UART1_TX_RB11_RP11
    {GPIO_PB11, hal_ll_uart_module_num(UART_MODULE_1), false},
    #endif
    #ifdef UART1_TX_RB12_RP12
    {GPIO_PB12, hal_ll_uart_module_num(UART_MODULE_1), false},
    #endif
    #ifdef UART1_TX_RB13_RP13
    {GPIO_PB13, hal_ll_uart_module_num(UART_MODULE_1), false},
    #endif
    #ifdef UART1_TX_RB14_RP14
    {GPIO_PB14, hal_ll_uart_module_num(UART_MODULE_1), false},
    #endif
    #ifdef UART1_TX_RB15_RP15
    {GPIO_PB15, hal_ll_uart_module_num(UART_MODULE_1), false},
    #endif
    #ifdef UART1_TX_RB2_RP2
    {GPIO_PB2, hal_ll_uart_module_num(UART_MODULE_1), false},
    #endif
    #ifdef UART1_TX_RB3_RP3
    {GPIO_PB3, hal_ll_uart_module_num(UART_MODULE_1), false},
    #endif
    #ifdef UART1_TX_RB4_RP4
    {GPIO_PB4, hal_ll_uart_module_num(UART_MODULE_1), false},
    #endif
    #ifdef UART1_TX_RB5_RP5
    {GPIO_PB5, hal_ll_uart_module_num(UART_MODULE_1), false},
    #endif
    #ifdef UART1_TX_RB6_RP6
    {GPIO_PB6, hal_ll_uart_module_num(UART_MODULE_1), false},
    #endif
    #ifdef UART1_TX_RB7_RP7
    {GPIO_PB7, hal_ll_uart_module_num(UART_MODULE_1), false},
    #endif
    #ifdef UART1_TX_RB8_RP8
    {GPIO_PB8, hal_ll_uart_module_num(UART_MODULE_1), false},
    #endif
    #ifdef UART1_TX_RB9_RP9
    {GPIO_PB9, hal_ll_uart_module_num(UART_MODULE_1), false},
    #endif
    #ifdef UART2_TX_RB0_RP0
    {GPIO_PB0, hal_ll_uart_module_num(UART_MODULE_2), false},
    #endif
    #ifdef UART2_TX_RB1_RP1
    {GPIO_PB1, hal_ll_uart_module_num(UART_MODULE_2), false},
    #endif
    #ifdef UART2_TX_RB10_RP10
    {GPIO_PB10, hal_ll_uart_module_num(UART_MODULE_2), false},
    #endif
    #ifdef UART2_TX_RB11_RP11
    {GPIO_PB11, hal_ll_uart_module_num(UART_MODULE_2), false},
    #endif
    #ifdef UART2_TX_RB12_RP12
    {GPIO_PB12, hal_ll_uart_module_num(UART_MODULE_2), false},
    #endif
    #ifdef UART2_TX_RB13_RP13
    {GPIO_PB13, hal_ll_uart_module_num(UART_MODULE_2), false},
    #endif
    #ifdef UART2_TX_RB14_RP14
    {GPIO_PB14, hal_ll_uart_module_num(UART_MODULE_2), false},
    #endif
    #ifdef UART2_TX_RB15_RP15
    {GPIO_PB15, hal_ll_uart_module_num(UART_MODULE_2), false},
    #endif
    #ifdef UART2_TX_RB2_RP2
    {GPIO_PB2, hal_ll_uart_module_num(UART_MODULE_2), false},
    #endif
    #ifdef UART2_TX_RB3_RP3
    {GPIO_PB3, hal_ll_uart_module_num(UART_MODULE_2), false},
    #endif
    #ifdef UART2_TX_RB4_RP4
    {GPIO_PB4, hal_ll_uart_module_num(UART_MODULE_2), false},
    #endif
    #ifdef UART2_TX_RB5_RP5
    {GPIO_PB5, hal_ll_uart_module_num(UART_MODULE_2), false},
    #endif
    #ifdef UART2_TX_RB6_RP6
    {GPIO_PB6, hal_ll_uart_module_num(UART_MODULE_2), false},
    #endif
    #ifdef UART2_TX_RB7_RP7
    {GPIO_PB7, hal_ll_uart_module_num(UART_MODULE_2), false},
    #endif
    #ifdef UART2_TX_RB8_RP8
    {GPIO_PB8, hal_ll_uart_module_num(UART_MODULE_2), false},
    #endif
    #ifdef UART2_TX_RB9_RP9
    {GPIO_PB9, hal_ll_uart_module_num(UART_MODULE_2), false},
    #endif
    #ifdef UART1_TX_RC0_RP16
    {GPIO_PC0, hal_ll_uart_module_num(UART_MODULE_1), false},
    #endif
    #ifdef UART1_TX_RC1_RP17
    {GPIO_PC1, hal_ll_uart_module_num(UART_MODULE_1), false},
    #endif
    #ifdef UART1_TX_RC2_RP18
    {GPIO_PC2, hal_ll_uart_module_num(UART_MODULE_1), false},
    #endif
    #ifdef UART1_TX_RC3_RP19
    {GPIO_PC3, hal_ll_uart_module_num(UART_MODULE_1), false},
    #endif
    #ifdef UART1_TX_RC4_RP20
    {GPIO_PC4, hal_ll_uart_module_num(UART_MODULE_1), false},
    #endif
    #ifdef UART1_TX_RC5_RP21
    {GPIO_PC5, hal_ll_uart_module_num(UART_MODULE_1), false},
    #endif
    #ifdef UART1_TX_RC6_RP22
    {GPIO_PC6, hal_ll_uart_module_num(UART_MODULE_1), false},
    #endif
    #ifdef UART1_TX_RC7_RP23
    {GPIO_PC7, hal_ll_uart_module_num(UART_MODULE_1), false},
    #endif
    #ifdef UART1_TX_RC8_RP24
    {GPIO_PC8, hal_ll_uart_module_num(UART_MODULE_1), false},
    #endif
    #ifdef UART1_TX_RC9_RP25
    {GPIO_PC9, hal_ll_uart_module_num(UART_MODULE_1), false},
    #endif
    #ifdef UART2_TX_RC0_RP16
    {GPIO_PC0, hal_ll_uart_module_num(UART_MODULE_2), false},
    #endif
    #ifdef UART2_TX_RC1_RP17
    {GPIO_PC1, hal_ll_uart_module_num(UART_MODULE_2), false},
    #endif
    #ifdef UART2_TX_RC2_RP18
    {GPIO_PC2, hal_ll_uart_module_num(UART_MODULE_2), false},
    #endif
    #ifdef UART2_TX_RC3_RP19
    {GPIO_PC3, hal_ll_uart_module_num(UART_MODULE_2), false},
    #endif
    #ifdef UART2_TX_RC4_RP20
    {GPIO_PC4, hal_ll_uart_module_num(UART_MODULE_2), false},
    #endif
    #ifdef UART2_TX_RC5_RP21
    {GPIO_PC5, hal_ll_uart_module_num(UART_MODULE_2), false},
    #endif
    #ifdef UART2_TX_RC6_RP22
    {GPIO_PC6, hal_ll_uart_module_num(UART_MODULE_2), false},
    #endif
    #ifdef UART2_TX_RC7_RP23
    {GPIO_PC7, hal_ll_uart_module_num(UART_MODULE_2), false},
    #endif
    #ifdef UART2_TX_RC8_RP24
    {GPIO_PC8, hal_ll_uart_module_num(UART_MODULE_2), false},
    #endif
    #ifdef UART2_TX_RC9_RP25
    {GPIO_PC9, hal_ll_uart_module_num(UART_MODULE_2), false},
    #endif
    #ifdef UART1_TX_RC10_RP26
    {GPIO_PC10, hal_ll_uart_module_num(UART_MODULE_1), false},
    #endif
    #ifdef UART1_TX_RC11_RP27
    {GPIO_PC11, hal_ll_uart_module_num(UART_MODULE_1), false},
    #endif
    #ifdef UART1_TX_RC12_RP28
    {GPIO_PC12, hal_ll_uart_module_num(UART_MODULE_1), false},
    #endif
    #ifdef UART1_TX_RC13_RP29
    {GPIO_PC13, hal_ll_uart_module_num(UART_MODULE_1), false},
    #endif
    #ifdef UART1_TX_RB7
    {GPIO_PB7, hal_ll_uart_module_num(UART_MODULE_1), false},
    #endif
    #ifdef UART2_TX_RB0
    {GPIO_PB0, hal_ll_uart_module_num(UART_MODULE_2), false},
    #endif
    #ifdef UART1_TX_RC7
    {GPIO_PC7, hal_ll_uart_module_num(UART_MODULE_1), false},
    #endif
    #ifdef UART1_TX_RB15_RP29
    {GPIO_PB15, hal_ll_uart_module_num(UART_MODULE_1), false},
    #endif
    #ifdef UART1_TX_RB2_RP13
    {GPIO_PB2, hal_ll_uart_module_num(UART_MODULE_1), false},
    #endif
    #ifdef UART1_TX_RB4_RP28
    {GPIO_PB4, hal_ll_uart_module_num(UART_MODULE_1), false},
    #endif
    #ifdef UART1_TX_RB5_RP18
    {GPIO_PB5, hal_ll_uart_module_num(UART_MODULE_1), false},
    #endif
    #ifdef UART1_TX_RD0_RP11
    {GPIO_PD0, hal_ll_uart_module_num(UART_MODULE_1), false},
    #endif
    #ifdef UART1_TX_RD1_RP24
    {GPIO_PD1, hal_ll_uart_module_num(UART_MODULE_1), false},
    #endif
    #ifdef UART1_TX_RD10_RP3
    {GPIO_PD10, hal_ll_uart_module_num(UART_MODULE_1), false},
    #endif
    #ifdef UART1_TX_RD11_RP12
    {GPIO_PD11, hal_ll_uart_module_num(UART_MODULE_1), false},
    #endif
    #ifdef UART1_TX_RD2_RP23
    {GPIO_PD2, hal_ll_uart_module_num(UART_MODULE_1), false},
    #endif
    #ifdef UART1_TX_RD3_RP22
    {GPIO_PD3, hal_ll_uart_module_num(UART_MODULE_1), false},
    #endif
    #ifdef UART1_TX_RD4_RP25
    {GPIO_PD4, hal_ll_uart_module_num(UART_MODULE_1), false},
    #endif
    #ifdef UART1_TX_RD5_RP20
    {GPIO_PD5, hal_ll_uart_module_num(UART_MODULE_1), false},
    #endif
    #ifdef UART1_TX_RD8_RP2
    {GPIO_PD8, hal_ll_uart_module_num(UART_MODULE_1), false},
    #endif
    #ifdef UART1_TX_RD9_RP4
    {GPIO_PD9, hal_ll_uart_module_num(UART_MODULE_1), false},
    #endif
    #ifdef UART1_TX_RF2_RP30
    {GPIO_PF2, hal_ll_uart_module_num(UART_MODULE_1), false},
    #endif
    #ifdef UART1_TX_RF3_RP16
    {GPIO_PF3, hal_ll_uart_module_num(UART_MODULE_1), false},
    #endif
    #ifdef UART1_TX_RF4_RP10
    {GPIO_PF4, hal_ll_uart_module_num(UART_MODULE_1), false},
    #endif
    #ifdef UART1_TX_RF5_RP17
    {GPIO_PF5, hal_ll_uart_module_num(UART_MODULE_1), false},
    #endif
    #ifdef UART1_TX_RG6_RP21
    {GPIO_PG6, hal_ll_uart_module_num(UART_MODULE_1), false},
    #endif
    #ifdef UART1_TX_RG7_RP26
    {GPIO_PG7, hal_ll_uart_module_num(UART_MODULE_1), false},
    #endif
    #ifdef UART1_TX_RG8_RP19
    {GPIO_PG8, hal_ll_uart_module_num(UART_MODULE_1), false},
    #endif
    #ifdef UART1_TX_RG9_RP27
    {GPIO_PG9, hal_ll_uart_module_num(UART_MODULE_1), false},
    #endif
    #ifdef UART2_TX_RB15_RP29
    {GPIO_PB15, hal_ll_uart_module_num(UART_MODULE_2), false},
    #endif
    #ifdef UART2_TX_RB2_RP13
    {GPIO_PB2, hal_ll_uart_module_num(UART_MODULE_2), false},
    #endif
    #ifdef UART2_TX_RB4_RP28
    {GPIO_PB4, hal_ll_uart_module_num(UART_MODULE_2), false},
    #endif
    #ifdef UART2_TX_RB5_RP18
    {GPIO_PB5, hal_ll_uart_module_num(UART_MODULE_2), false},
    #endif
    #ifdef UART2_TX_RD0_RP11
    {GPIO_PD0, hal_ll_uart_module_num(UART_MODULE_2), false},
    #endif
    #ifdef UART2_TX_RD1_RP24
    {GPIO_PD1, hal_ll_uart_module_num(UART_MODULE_2), false},
    #endif
    #ifdef UART2_TX_RD10_RP3
    {GPIO_PD10, hal_ll_uart_module_num(UART_MODULE_2), false},
    #endif
    #ifdef UART2_TX_RD11_RP12
    {GPIO_PD11, hal_ll_uart_module_num(UART_MODULE_2), false},
    #endif
    #ifdef UART2_TX_RD2_RP23
    {GPIO_PD2, hal_ll_uart_module_num(UART_MODULE_2), false},
    #endif
    #ifdef UART2_TX_RD3_RP22
    {GPIO_PD3, hal_ll_uart_module_num(UART_MODULE_2), false},
    #endif
    #ifdef UART2_TX_RD4_RP25
    {GPIO_PD4, hal_ll_uart_module_num(UART_MODULE_2), false},
    #endif
    #ifdef UART2_TX_RD5_RP20
    {GPIO_PD5, hal_ll_uart_module_num(UART_MODULE_2), false},
    #endif
    #ifdef UART2_TX_RD8_RP2
    {GPIO_PD8, hal_ll_uart_module_num(UART_MODULE_2), false},
    #endif
    #ifdef UART2_TX_RD9_RP4
    {GPIO_PD9, hal_ll_uart_module_num(UART_MODULE_2), false},
    #endif
    #ifdef UART2_TX_RF2_RP30
    {GPIO_PF2, hal_ll_uart_module_num(UART_MODULE_2), false},
    #endif
    #ifdef UART2_TX_RF3_RP16
    {GPIO_PF3, hal_ll_uart_module_num(UART_MODULE_2), false},
    #endif
    #ifdef UART2_TX_RF4_RP10
    {GPIO_PF4, hal_ll_uart_module_num(UART_MODULE_2), false},
    #endif
    #ifdef UART2_TX_RF5_RP17
    {GPIO_PF5, hal_ll_uart_module_num(UART_MODULE_2), false},
    #endif
    #ifdef UART2_TX_RG6_RP21
    {GPIO_PG6, hal_ll_uart_module_num(UART_MODULE_2), false},
    #endif
    #ifdef UART2_TX_RG7_RP26
    {GPIO_PG7, hal_ll_uart_module_num(UART_MODULE_2), false},
    #endif
    #ifdef UART2_TX_RG8_RP19
    {GPIO_PG8, hal_ll_uart_module_num(UART_MODULE_2), false},
    #endif
    #ifdef UART2_TX_RG9_RP27
    {GPIO_PG9, hal_ll_uart_module_num(UART_MODULE_2), false},
    #endif
    #ifdef UART3_TX_RB0_RP0
    {GPIO_PB0, hal_ll_uart_module_num(UART_MODULE_3), false},
    #endif
    #ifdef UART3_TX_RB1_RP1
    {GPIO_PB1, hal_ll_uart_module_num(UART_MODULE_3), false},
    #endif
    #ifdef UART3_TX_RB14_RP14
    {GPIO_PB14, hal_ll_uart_module_num(UART_MODULE_3), false},
    #endif
    #ifdef UART3_TX_RB15_RP29
    {GPIO_PB15, hal_ll_uart_module_num(UART_MODULE_3), false},
    #endif
    #ifdef UART3_TX_RB2_RP13
    {GPIO_PB2, hal_ll_uart_module_num(UART_MODULE_3), false},
    #endif
    #ifdef UART3_TX_RB4_RP28
    {GPIO_PB4, hal_ll_uart_module_num(UART_MODULE_3), false},
    #endif
    #ifdef UART3_TX_RB5_RP18
    {GPIO_PB5, hal_ll_uart_module_num(UART_MODULE_3), false},
    #endif
    #ifdef UART3_TX_RB6_RP6
    {GPIO_PB6, hal_ll_uart_module_num(UART_MODULE_3), false},
    #endif
    #ifdef UART3_TX_RB7_RP7
    {GPIO_PB7, hal_ll_uart_module_num(UART_MODULE_3), false},
    #endif
    #ifdef UART3_TX_RB8_RP8
    {GPIO_PB8, hal_ll_uart_module_num(UART_MODULE_3), false},
    #endif
    #ifdef UART3_TX_RB9_RP9
    {GPIO_PB9, hal_ll_uart_module_num(UART_MODULE_3), false},
    #endif
    #ifdef UART3_TX_RD0_RP11
    {GPIO_PD0, hal_ll_uart_module_num(UART_MODULE_3), false},
    #endif
    #ifdef UART3_TX_RD1_RP24
    {GPIO_PD1, hal_ll_uart_module_num(UART_MODULE_3), false},
    #endif
    #ifdef UART3_TX_RD10_RP3
    {GPIO_PD10, hal_ll_uart_module_num(UART_MODULE_3), false},
    #endif
    #ifdef UART3_TX_RD11_RP12
    {GPIO_PD11, hal_ll_uart_module_num(UART_MODULE_3), false},
    #endif
    #ifdef UART3_TX_RD2_RP23
    {GPIO_PD2, hal_ll_uart_module_num(UART_MODULE_3), false},
    #endif
    #ifdef UART3_TX_RD3_RP22
    {GPIO_PD3, hal_ll_uart_module_num(UART_MODULE_3), false},
    #endif
    #ifdef UART3_TX_RD4_RP25
    {GPIO_PD4, hal_ll_uart_module_num(UART_MODULE_3), false},
    #endif
    #ifdef UART3_TX_RD5_RP20
    {GPIO_PD5, hal_ll_uart_module_num(UART_MODULE_3), false},
    #endif
    #ifdef UART3_TX_RD8_RP2
    {GPIO_PD8, hal_ll_uart_module_num(UART_MODULE_3), false},
    #endif
    #ifdef UART3_TX_RD9_RP4
    {GPIO_PD9, hal_ll_uart_module_num(UART_MODULE_3), false},
    #endif
    #ifdef UART3_TX_RF2_RP30
    {GPIO_PF2, hal_ll_uart_module_num(UART_MODULE_3), false},
    #endif
    #ifdef UART3_TX_RF3_RP16
    {GPIO_PF3, hal_ll_uart_module_num(UART_MODULE_3), false},
    #endif
    #ifdef UART3_TX_RF4_RP10
    {GPIO_PF4, hal_ll_uart_module_num(UART_MODULE_3), false},
    #endif
    #ifdef UART3_TX_RF5_RP17
    {GPIO_PF5, hal_ll_uart_module_num(UART_MODULE_3), false},
    #endif
    #ifdef UART3_TX_RG6_RP21
    {GPIO_PG6, hal_ll_uart_module_num(UART_MODULE_3), false},
    #endif
    #ifdef UART3_TX_RG7_RP26
    {GPIO_PG7, hal_ll_uart_module_num(UART_MODULE_3), false},
    #endif
    #ifdef UART3_TX_RG8_RP19
    {GPIO_PG8, hal_ll_uart_module_num(UART_MODULE_3), false},
    #endif
    #ifdef UART3_TX_RG9_RP27
    {GPIO_PG9, hal_ll_uart_module_num(UART_MODULE_3), false},
    #endif
    #ifdef UART4_TX_RB0_RP0
    {GPIO_PB0, hal_ll_uart_module_num(UART_MODULE_4), false},
    #endif
    #ifdef UART4_TX_RB1_RP1
    {GPIO_PB1, hal_ll_uart_module_num(UART_MODULE_4), false},
    #endif
    #ifdef UART4_TX_RB14_RP14
    {GPIO_PB14, hal_ll_uart_module_num(UART_MODULE_4), false},
    #endif
    #ifdef UART4_TX_RB15_RP29
    {GPIO_PB15, hal_ll_uart_module_num(UART_MODULE_4), false},
    #endif
    #ifdef UART4_TX_RB2_RP13
    {GPIO_PB2, hal_ll_uart_module_num(UART_MODULE_4), false},
    #endif
    #ifdef UART4_TX_RB4_RP28
    {GPIO_PB4, hal_ll_uart_module_num(UART_MODULE_4), false},
    #endif
    #ifdef UART4_TX_RB5_RP18
    {GPIO_PB5, hal_ll_uart_module_num(UART_MODULE_4), false},
    #endif
    #ifdef UART4_TX_RB6_RP6
    {GPIO_PB6, hal_ll_uart_module_num(UART_MODULE_4), false},
    #endif
    #ifdef UART4_TX_RB7_RP7
    {GPIO_PB7, hal_ll_uart_module_num(UART_MODULE_4), false},
    #endif
    #ifdef UART4_TX_RB8_RP8
    {GPIO_PB8, hal_ll_uart_module_num(UART_MODULE_4), false},
    #endif
    #ifdef UART4_TX_RB9_RP9
    {GPIO_PB9, hal_ll_uart_module_num(UART_MODULE_4), false},
    #endif
    #ifdef UART4_TX_RD0_RP11
    {GPIO_PD0, hal_ll_uart_module_num(UART_MODULE_4), false},
    #endif
    #ifdef UART4_TX_RD1_RP24
    {GPIO_PD1, hal_ll_uart_module_num(UART_MODULE_4), false},
    #endif
    #ifdef UART4_TX_RD10_RP3
    {GPIO_PD10, hal_ll_uart_module_num(UART_MODULE_4), false},
    #endif
    #ifdef UART4_TX_RD11_RP12
    {GPIO_PD11, hal_ll_uart_module_num(UART_MODULE_4), false},
    #endif
    #ifdef UART4_TX_RD2_RP23
    {GPIO_PD2, hal_ll_uart_module_num(UART_MODULE_4), false},
    #endif
    #ifdef UART4_TX_RD3_RP22
    {GPIO_PD3, hal_ll_uart_module_num(UART_MODULE_4), false},
    #endif
    #ifdef UART4_TX_RD4_RP25
    {GPIO_PD4, hal_ll_uart_module_num(UART_MODULE_4), false},
    #endif
    #ifdef UART4_TX_RD5_RP20
    {GPIO_PD5, hal_ll_uart_module_num(UART_MODULE_4), false},
    #endif
    #ifdef UART4_TX_RD8_RP2
    {GPIO_PD8, hal_ll_uart_module_num(UART_MODULE_4), false},
    #endif
    #ifdef UART4_TX_RD9_RP4
    {GPIO_PD9, hal_ll_uart_module_num(UART_MODULE_4), false},
    #endif
    #ifdef UART4_TX_RF2_RP30
    {GPIO_PF2, hal_ll_uart_module_num(UART_MODULE_4), false},
    #endif
    #ifdef UART4_TX_RF3_RP16
    {GPIO_PF3, hal_ll_uart_module_num(UART_MODULE_4), false},
    #endif
    #ifdef UART4_TX_RF4_RP10
    {GPIO_PF4, hal_ll_uart_module_num(UART_MODULE_4), false},
    #endif
    #ifdef UART4_TX_RF5_RP17
    {GPIO_PF5, hal_ll_uart_module_num(UART_MODULE_4), false},
    #endif
    #ifdef UART4_TX_RG6_RP21
    {GPIO_PG6, hal_ll_uart_module_num(UART_MODULE_4), false},
    #endif
    #ifdef UART4_TX_RG7_RP26
    {GPIO_PG7, hal_ll_uart_module_num(UART_MODULE_4), false},
    #endif
    #ifdef UART4_TX_RG8_RP19
    {GPIO_PG8, hal_ll_uart_module_num(UART_MODULE_4), false},
    #endif
    #ifdef UART4_TX_RG9_RP27
    {GPIO_PG9, hal_ll_uart_module_num(UART_MODULE_4), false},
    #endif
    #ifdef UART5_TX_RD1
    {GPIO_PD1, hal_ll_uart_module_num(UART_MODULE_5), false},
    #endif
    #ifdef UART6_TX_RB7
    {GPIO_PB7, hal_ll_uart_module_num(UART_MODULE_6), false},
    #endif
    #ifdef UART1_TX_RD15_RP5
    {GPIO_PD15, hal_ll_uart_module_num(UART_MODULE_1), false},
    #endif
    #ifdef UART1_TX_RF13_RP31
    {GPIO_PF13, hal_ll_uart_module_num(UART_MODULE_1), false},
    #endif
    #ifdef UART1_TX_RF8_RP15
    {GPIO_PF8, hal_ll_uart_module_num(UART_MODULE_1), false},
    #endif
    #ifdef UART2_TX_RD15_RP5
    {GPIO_PD15, hal_ll_uart_module_num(UART_MODULE_2), false},
    #endif
    #ifdef UART2_TX_RF13_RP31
    {GPIO_PF13, hal_ll_uart_module_num(UART_MODULE_2), false},
    #endif
    #ifdef UART2_TX_RF8_RP15
    {GPIO_PF8, hal_ll_uart_module_num(UART_MODULE_2), false},
    #endif
    #ifdef UART3_TX_RD15_RP5
    {GPIO_PD15, hal_ll_uart_module_num(UART_MODULE_3), false},
    #endif
    #ifdef UART3_TX_RF13_RP31
    {GPIO_PF13, hal_ll_uart_module_num(UART_MODULE_3), false},
    #endif
    #ifdef UART3_TX_RF8_RP15
    {GPIO_PF8, hal_ll_uart_module_num(UART_MODULE_3), false},
    #endif
    #ifdef UART4_TX_RD15_RP5
    {GPIO_PD15, hal_ll_uart_module_num(UART_MODULE_4), false},
    #endif
    #ifdef UART4_TX_RF13_RP31
    {GPIO_PF13, hal_ll_uart_module_num(UART_MODULE_4), false},
    #endif
    #ifdef UART4_TX_RF8_RP15
    {GPIO_PF8, hal_ll_uart_module_num(UART_MODULE_4), false},
    #endif
    #ifdef UART3_TX_RB10_RP10
    {GPIO_PB10, hal_ll_uart_module_num(UART_MODULE_3), false},
    #endif
    #ifdef UART3_TX_RB11_RP11
    {GPIO_PB11, hal_ll_uart_module_num(UART_MODULE_3), false},
    #endif
    #ifdef UART3_TX_RB12_RP12
    {GPIO_PB12, hal_ll_uart_module_num(UART_MODULE_3), false},
    #endif
    #ifdef UART3_TX_RB13_RP13
    {GPIO_PB13, hal_ll_uart_module_num(UART_MODULE_3), false},
    #endif
    #ifdef UART3_TX_RB15_RP15
    {GPIO_PB15, hal_ll_uart_module_num(UART_MODULE_3), false},
    #endif
    #ifdef UART3_TX_RB2_RP2
    {GPIO_PB2, hal_ll_uart_module_num(UART_MODULE_3), false},
    #endif
    #ifdef UART3_TX_RB3_RP3
    {GPIO_PB3, hal_ll_uart_module_num(UART_MODULE_3), false},
    #endif
    #ifdef UART3_TX_RB5_RP5
    {GPIO_PB5, hal_ll_uart_module_num(UART_MODULE_3), false},
    #endif
    #ifdef UART4_TX_RB10_RP10
    {GPIO_PB10, hal_ll_uart_module_num(UART_MODULE_4), false},
    #endif
    #ifdef UART4_TX_RB11_RP11
    {GPIO_PB11, hal_ll_uart_module_num(UART_MODULE_4), false},
    #endif
    #ifdef UART4_TX_RB12_RP12
    {GPIO_PB12, hal_ll_uart_module_num(UART_MODULE_4), false},
    #endif
    #ifdef UART4_TX_RB13_RP13
    {GPIO_PB13, hal_ll_uart_module_num(UART_MODULE_4), false},
    #endif
    #ifdef UART4_TX_RB15_RP15
    {GPIO_PB15, hal_ll_uart_module_num(UART_MODULE_4), false},
    #endif
    #ifdef UART4_TX_RB2_RP2
    {GPIO_PB2, hal_ll_uart_module_num(UART_MODULE_4), false},
    #endif
    #ifdef UART4_TX_RB3_RP3
    {GPIO_PB3, hal_ll_uart_module_num(UART_MODULE_4), false},
    #endif
    #ifdef UART4_TX_RB5_RP5
    {GPIO_PB5, hal_ll_uart_module_num(UART_MODULE_4), false},
    #endif
    #ifdef UART3_TX_RC0_RP16
    {GPIO_PC0, hal_ll_uart_module_num(UART_MODULE_3), false},
    #endif
    #ifdef UART3_TX_RC1_RP17
    {GPIO_PC1, hal_ll_uart_module_num(UART_MODULE_3), false},
    #endif
    #ifdef UART3_TX_RC2_RP18
    {GPIO_PC2, hal_ll_uart_module_num(UART_MODULE_3), false},
    #endif
    #ifdef UART3_TX_RC3_RP19
    {GPIO_PC3, hal_ll_uart_module_num(UART_MODULE_3), false},
    #endif
    #ifdef UART3_TX_RC4_RP20
    {GPIO_PC4, hal_ll_uart_module_num(UART_MODULE_3), false},
    #endif
    #ifdef UART3_TX_RC5_RP21
    {GPIO_PC5, hal_ll_uart_module_num(UART_MODULE_3), false},
    #endif
    #ifdef UART3_TX_RC6_RP22
    {GPIO_PC6, hal_ll_uart_module_num(UART_MODULE_3), false},
    #endif
    #ifdef UART3_TX_RC7_RP23
    {GPIO_PC7, hal_ll_uart_module_num(UART_MODULE_3), false},
    #endif
    #ifdef UART3_TX_RC8_RP24
    {GPIO_PC8, hal_ll_uart_module_num(UART_MODULE_3), false},
    #endif
    #ifdef UART3_TX_RC9_RP25
    {GPIO_PC9, hal_ll_uart_module_num(UART_MODULE_3), false},
    #endif
    #ifdef UART4_TX_RC0_RP16
    {GPIO_PC0, hal_ll_uart_module_num(UART_MODULE_4), false},
    #endif
    #ifdef UART4_TX_RC1_RP17
    {GPIO_PC1, hal_ll_uart_module_num(UART_MODULE_4), false},
    #endif
    #ifdef UART4_TX_RC2_RP18
    {GPIO_PC2, hal_ll_uart_module_num(UART_MODULE_4), false},
    #endif
    #ifdef UART4_TX_RC3_RP19
    {GPIO_PC3, hal_ll_uart_module_num(UART_MODULE_4), false},
    #endif
    #ifdef UART4_TX_RC4_RP20
    {GPIO_PC4, hal_ll_uart_module_num(UART_MODULE_4), false},
    #endif
    #ifdef UART4_TX_RC5_RP21
    {GPIO_PC5, hal_ll_uart_module_num(UART_MODULE_4), false},
    #endif
    #ifdef UART4_TX_RC6_RP22
    {GPIO_PC6, hal_ll_uart_module_num(UART_MODULE_4), false},
    #endif
    #ifdef UART4_TX_RC7_RP23
    {GPIO_PC7, hal_ll_uart_module_num(UART_MODULE_4), false},
    #endif
    #ifdef UART4_TX_RC8_RP24
    {GPIO_PC8, hal_ll_uart_module_num(UART_MODULE_4), false},
    #endif
    #ifdef UART4_TX_RC9_RP25
    {GPIO_PC9, hal_ll_uart_module_num(UART_MODULE_4), false},
    #endif
    #ifdef UART1_TX_RA0_RP26
    {GPIO_PA0, hal_ll_uart_module_num(UART_MODULE_1), false},
    #endif
    #ifdef UART1_TX_RA1_RP27
    {GPIO_PA1, hal_ll_uart_module_num(UART_MODULE_1), false},
    #endif
    #ifdef UART2_TX_RA0_RP26
    {GPIO_PA0, hal_ll_uart_module_num(UART_MODULE_2), false},
    #endif
    #ifdef UART2_TX_RA1_RP27
    {GPIO_PA1, hal_ll_uart_module_num(UART_MODULE_2), false},
    #endif
    #ifdef UART1_TX_RA10_RP28
    {GPIO_PA10, hal_ll_uart_module_num(UART_MODULE_1), false},
    #endif
    #ifdef UART2_TX_RA10_RP28
    {GPIO_PA10, hal_ll_uart_module_num(UART_MODULE_2), false},
    #endif
    #ifdef UART1_TX_RA0_RP5
    {GPIO_PA0, hal_ll_uart_module_num(UART_MODULE_1), false},
    #endif
    #ifdef UART1_TX_RA1_RP6
    {GPIO_PA1, hal_ll_uart_module_num(UART_MODULE_1), false},
    #endif
    #ifdef UART2_TX_RA0_RP5
    {GPIO_PA0, hal_ll_uart_module_num(UART_MODULE_2), false},
    #endif
    #ifdef UART2_TX_RA1_RP6
    {GPIO_PA1, hal_ll_uart_module_num(UART_MODULE_2), false},
    #endif
    #ifdef UART3_TX_RA0_RP5
    {GPIO_PA0, hal_ll_uart_module_num(UART_MODULE_3), false},
    #endif
    #ifdef UART3_TX_RA1_RP6
    {GPIO_PA1, hal_ll_uart_module_num(UART_MODULE_3), false},
    #endif
    #ifdef UART4_TX_RA0_RP5
    {GPIO_PA0, hal_ll_uart_module_num(UART_MODULE_4), false},
    #endif
    #ifdef UART4_TX_RA1_RP6
    {GPIO_PA1, hal_ll_uart_module_num(UART_MODULE_4), false},
    #endif
    { HAL_LL_PIN_NC, HAL_LL_MODULE_ERROR, false }
    //------------ END TX
};

/*!< @brief UART RX pins */
static const hal_ll_uart_pin_map_t hal_ll_uart_rx_map[] = {
    //------------ BEGIN RX
    #ifdef UART1_RX_RB5
    {GPIO_PB5, hal_ll_uart_module_num(UART_MODULE_1), false},
    #endif
    #ifdef UART1_RX_RC14_ALT
    {GPIO_PC14, hal_ll_uart_module_num(UART_MODULE_1), true},
    #endif
    #ifdef UART1_RX_RF2
    {GPIO_PF2, hal_ll_uart_module_num(UART_MODULE_1), false},
    #endif
    #ifdef UART2_RX_RF4
    {GPIO_PF4, hal_ll_uart_module_num(UART_MODULE_2), false},
    #endif
    #ifdef UART1_RX_RA0_RPI16
    {GPIO_PA0, hal_ll_uart_module_num(UART_MODULE_1), false},
    #endif
    #ifdef UART1_RX_RA1_RPI17
    {GPIO_PA1, hal_ll_uart_module_num(UART_MODULE_1), false},
    #endif
    #ifdef UART1_RX_RA2_RPI18
    {GPIO_PA2, hal_ll_uart_module_num(UART_MODULE_1), false},
    #endif
    #ifdef UART1_RX_RA3_RPI19
    {GPIO_PA3, hal_ll_uart_module_num(UART_MODULE_1), false},
    #endif
    #ifdef UART1_RX_RA4_RP20
    {GPIO_PA4, hal_ll_uart_module_num(UART_MODULE_1), false},
    #endif
    #ifdef UART1_RX_RA8_RPI24
    {GPIO_PA8, hal_ll_uart_module_num(UART_MODULE_1), false},
    #endif
    #ifdef UART1_RX_RA9_RPI25
    {GPIO_PA9, hal_ll_uart_module_num(UART_MODULE_1), false},
    #endif
    #ifdef UART1_RX_RB0_RPI32
    {GPIO_PB0, hal_ll_uart_module_num(UART_MODULE_1), false},
    #endif
    #ifdef UART1_RX_RB1_RPI33
    {GPIO_PB1, hal_ll_uart_module_num(UART_MODULE_1), false},
    #endif
    #ifdef UART1_RX_RB10_RP42
    {GPIO_PB10, hal_ll_uart_module_num(UART_MODULE_1), false},
    #endif
    #ifdef UART1_RX_RB11_RP43
    {GPIO_PB11, hal_ll_uart_module_num(UART_MODULE_1), false},
    #endif
    #ifdef UART1_RX_RB12_RPI44
    {GPIO_PB12, hal_ll_uart_module_num(UART_MODULE_1), false},
    #endif
    #ifdef UART1_RX_RB13_RPI45
    {GPIO_PB13, hal_ll_uart_module_num(UART_MODULE_1), false},
    #endif
    #ifdef UART1_RX_RB14_RPI46
    {GPIO_PB14, hal_ll_uart_module_num(UART_MODULE_1), false},
    #endif
    #ifdef UART1_RX_RB15_RPI47
    {GPIO_PB15, hal_ll_uart_module_num(UART_MODULE_1), false},
    #endif
    #ifdef UART1_RX_RB2_RPI34
    {GPIO_PB2, hal_ll_uart_module_num(UART_MODULE_1), false},
    #endif
    #ifdef UART1_RX_RB3_RP35
    {GPIO_PB3, hal_ll_uart_module_num(UART_MODULE_1), false},
    #endif
    #ifdef UART1_RX_RB4_RP36
    {GPIO_PB4, hal_ll_uart_module_num(UART_MODULE_1), false},
    #endif
    #ifdef UART1_RX_RB5_RP37
    {GPIO_PB5, hal_ll_uart_module_num(UART_MODULE_1), false},
    #endif
    #ifdef UART1_RX_RB6_RP38
    {GPIO_PB6, hal_ll_uart_module_num(UART_MODULE_1), false},
    #endif
    #ifdef UART1_RX_RB7_RP39
    {GPIO_PB7, hal_ll_uart_module_num(UART_MODULE_1), false},
    #endif
    #ifdef UART1_RX_RB8_RP40
    {GPIO_PB8, hal_ll_uart_module_num(UART_MODULE_1), false},
    #endif
    #ifdef UART1_RX_RB9_RP41
    {GPIO_PB9, hal_ll_uart_module_num(UART_MODULE_1), false},
    #endif
    #ifdef UART1_RX_RC0_RP48
    {GPIO_PC0, hal_ll_uart_module_num(UART_MODULE_1), false},
    #endif
    #ifdef UART1_RX_RC1_RP49
    {GPIO_PC1, hal_ll_uart_module_num(UART_MODULE_1), false},
    #endif
    #ifdef UART1_RX_RC2_RPI50
    {GPIO_PC2, hal_ll_uart_module_num(UART_MODULE_1), false},
    #endif
    #ifdef UART1_RX_RC3_RPI51
    {GPIO_PC3, hal_ll_uart_module_num(UART_MODULE_1), false},
    #endif
    #ifdef UART1_RX_RC4_RPI52
    {GPIO_PC4, hal_ll_uart_module_num(UART_MODULE_1), false},
    #endif
    #ifdef UART1_RX_RC5_RPI53
    {GPIO_PC5, hal_ll_uart_module_num(UART_MODULE_1), false},
    #endif
    #ifdef UART1_RX_RC6_RP54
    {GPIO_PC6, hal_ll_uart_module_num(UART_MODULE_1), false},
    #endif
    #ifdef UART1_RX_RC7_RP55
    {GPIO_PC7, hal_ll_uart_module_num(UART_MODULE_1), false},
    #endif
    #ifdef UART1_RX_RC8_RP56
    {GPIO_PC8, hal_ll_uart_module_num(UART_MODULE_1), false},
    #endif
    #ifdef UART1_RX_RC9_RP57
    {GPIO_PC9, hal_ll_uart_module_num(UART_MODULE_1), false},
    #endif
    #ifdef UART2_RX_RA0_RPI16
    {GPIO_PA0, hal_ll_uart_module_num(UART_MODULE_2), false},
    #endif
    #ifdef UART2_RX_RA1_RPI17
    {GPIO_PA1, hal_ll_uart_module_num(UART_MODULE_2), false},
    #endif
    #ifdef UART2_RX_RA2_RPI18
    {GPIO_PA2, hal_ll_uart_module_num(UART_MODULE_2), false},
    #endif
    #ifdef UART2_RX_RA3_RPI19
    {GPIO_PA3, hal_ll_uart_module_num(UART_MODULE_2), false},
    #endif
    #ifdef UART2_RX_RA4_RP20
    {GPIO_PA4, hal_ll_uart_module_num(UART_MODULE_2), false},
    #endif
    #ifdef UART2_RX_RA8_RPI24
    {GPIO_PA8, hal_ll_uart_module_num(UART_MODULE_2), false},
    #endif
    #ifdef UART2_RX_RA9_RPI25
    {GPIO_PA9, hal_ll_uart_module_num(UART_MODULE_2), false},
    #endif
    #ifdef UART2_RX_RB0_RPI32
    {GPIO_PB0, hal_ll_uart_module_num(UART_MODULE_2), false},
    #endif
    #ifdef UART2_RX_RB1_RPI33
    {GPIO_PB1, hal_ll_uart_module_num(UART_MODULE_2), false},
    #endif
    #ifdef UART2_RX_RB10_RP42
    {GPIO_PB10, hal_ll_uart_module_num(UART_MODULE_2), false},
    #endif
    #ifdef UART2_RX_RB11_RP43
    {GPIO_PB11, hal_ll_uart_module_num(UART_MODULE_2), false},
    #endif
    #ifdef UART2_RX_RB12_RPI44
    {GPIO_PB12, hal_ll_uart_module_num(UART_MODULE_2), false},
    #endif
    #ifdef UART2_RX_RB13_RPI45
    {GPIO_PB13, hal_ll_uart_module_num(UART_MODULE_2), false},
    #endif
    #ifdef UART2_RX_RB14_RPI46
    {GPIO_PB14, hal_ll_uart_module_num(UART_MODULE_2), false},
    #endif
    #ifdef UART2_RX_RB15_RPI47
    {GPIO_PB15, hal_ll_uart_module_num(UART_MODULE_2), false},
    #endif
    #ifdef UART2_RX_RB2_RPI34
    {GPIO_PB2, hal_ll_uart_module_num(UART_MODULE_2), false},
    #endif
    #ifdef UART2_RX_RB3_RP35
    {GPIO_PB3, hal_ll_uart_module_num(UART_MODULE_2), false},
    #endif
    #ifdef UART2_RX_RB4_RP36
    {GPIO_PB4, hal_ll_uart_module_num(UART_MODULE_2), false},
    #endif
    #ifdef UART2_RX_RB5_RP37
    {GPIO_PB5, hal_ll_uart_module_num(UART_MODULE_2), false},
    #endif
    #ifdef UART2_RX_RB6_RP38
    {GPIO_PB6, hal_ll_uart_module_num(UART_MODULE_2), false},
    #endif
    #ifdef UART2_RX_RB7_RP39
    {GPIO_PB7, hal_ll_uart_module_num(UART_MODULE_2), false},
    #endif
    #ifdef UART2_RX_RB8_RP40
    {GPIO_PB8, hal_ll_uart_module_num(UART_MODULE_2), false},
    #endif
    #ifdef UART2_RX_RB9_RP41
    {GPIO_PB9, hal_ll_uart_module_num(UART_MODULE_2), false},
    #endif
    #ifdef UART2_RX_RC0_RP48
    {GPIO_PC0, hal_ll_uart_module_num(UART_MODULE_2), false},
    #endif
    #ifdef UART2_RX_RC1_RP49
    {GPIO_PC1, hal_ll_uart_module_num(UART_MODULE_2), false},
    #endif
    #ifdef UART2_RX_RC2_RPI50
    {GPIO_PC2, hal_ll_uart_module_num(UART_MODULE_2), false},
    #endif
    #ifdef UART2_RX_RC3_RPI51
    {GPIO_PC3, hal_ll_uart_module_num(UART_MODULE_2), false},
    #endif
    #ifdef UART2_RX_RC4_RPI52
    {GPIO_PC4, hal_ll_uart_module_num(UART_MODULE_2), false},
    #endif
    #ifdef UART2_RX_RC5_RPI53
    {GPIO_PC5, hal_ll_uart_module_num(UART_MODULE_2), false},
    #endif
    #ifdef UART2_RX_RC6_RP54
    {GPIO_PC6, hal_ll_uart_module_num(UART_MODULE_2), false},
    #endif
    #ifdef UART2_RX_RC7_RP55
    {GPIO_PC7, hal_ll_uart_module_num(UART_MODULE_2), false},
    #endif
    #ifdef UART2_RX_RC8_RP56
    {GPIO_PC8, hal_ll_uart_module_num(UART_MODULE_2), false},
    #endif
    #ifdef UART2_RX_RC9_RP57
    {GPIO_PC9, hal_ll_uart_module_num(UART_MODULE_2), false},
    #endif
    #ifdef UART3_RX_RA0_RPI16
    {GPIO_PA0, hal_ll_uart_module_num(UART_MODULE_3), false},
    #endif
    #ifdef UART3_RX_RA1_RPI17
    {GPIO_PA1, hal_ll_uart_module_num(UART_MODULE_3), false},
    #endif
    #ifdef UART3_RX_RA2_RPI18
    {GPIO_PA2, hal_ll_uart_module_num(UART_MODULE_3), false},
    #endif
    #ifdef UART3_RX_RA3_RPI19
    {GPIO_PA3, hal_ll_uart_module_num(UART_MODULE_3), false},
    #endif
    #ifdef UART3_RX_RA4_RP20
    {GPIO_PA4, hal_ll_uart_module_num(UART_MODULE_3), false},
    #endif
    #ifdef UART3_RX_RA8_RPI24
    {GPIO_PA8, hal_ll_uart_module_num(UART_MODULE_3), false},
    #endif
    #ifdef UART3_RX_RA9_RPI25
    {GPIO_PA9, hal_ll_uart_module_num(UART_MODULE_3), false},
    #endif
    #ifdef UART3_RX_RB0_RPI32
    {GPIO_PB0, hal_ll_uart_module_num(UART_MODULE_3), false},
    #endif
    #ifdef UART3_RX_RB1_RPI33
    {GPIO_PB1, hal_ll_uart_module_num(UART_MODULE_3), false},
    #endif
    #ifdef UART3_RX_RB10_RP42
    {GPIO_PB10, hal_ll_uart_module_num(UART_MODULE_3), false},
    #endif
    #ifdef UART3_RX_RB11_RP43
    {GPIO_PB11, hal_ll_uart_module_num(UART_MODULE_3), false},
    #endif
    #ifdef UART3_RX_RB12_RPI44
    {GPIO_PB12, hal_ll_uart_module_num(UART_MODULE_3), false},
    #endif
    #ifdef UART3_RX_RB13_RPI45
    {GPIO_PB13, hal_ll_uart_module_num(UART_MODULE_3), false},
    #endif
    #ifdef UART3_RX_RB14_RPI46
    {GPIO_PB14, hal_ll_uart_module_num(UART_MODULE_3), false},
    #endif
    #ifdef UART3_RX_RB15_RPI47
    {GPIO_PB15, hal_ll_uart_module_num(UART_MODULE_3), false},
    #endif
    #ifdef UART3_RX_RB2_RPI34
    {GPIO_PB2, hal_ll_uart_module_num(UART_MODULE_3), false},
    #endif
    #ifdef UART3_RX_RB3_RP35
    {GPIO_PB3, hal_ll_uart_module_num(UART_MODULE_3), false},
    #endif
    #ifdef UART3_RX_RB4_RP36
    {GPIO_PB4, hal_ll_uart_module_num(UART_MODULE_3), false},
    #endif
    #ifdef UART3_RX_RB5_RP37
    {GPIO_PB5, hal_ll_uart_module_num(UART_MODULE_3), false},
    #endif
    #ifdef UART3_RX_RB6_RP38
    {GPIO_PB6, hal_ll_uart_module_num(UART_MODULE_3), false},
    #endif
    #ifdef UART3_RX_RB7_RP39
    {GPIO_PB7, hal_ll_uart_module_num(UART_MODULE_3), false},
    #endif
    #ifdef UART3_RX_RB8_RP40
    {GPIO_PB8, hal_ll_uart_module_num(UART_MODULE_3), false},
    #endif
    #ifdef UART3_RX_RB9_RP41
    {GPIO_PB9, hal_ll_uart_module_num(UART_MODULE_3), false},
    #endif
    #ifdef UART3_RX_RC0_RP48
    {GPIO_PC0, hal_ll_uart_module_num(UART_MODULE_3), false},
    #endif
    #ifdef UART3_RX_RC1_RP49
    {GPIO_PC1, hal_ll_uart_module_num(UART_MODULE_3), false},
    #endif
    #ifdef UART3_RX_RC2_RPI50
    {GPIO_PC2, hal_ll_uart_module_num(UART_MODULE_3), false},
    #endif
    #ifdef UART3_RX_RC3_RPI51
    {GPIO_PC3, hal_ll_uart_module_num(UART_MODULE_3), false},
    #endif
    #ifdef UART3_RX_RC4_RPI52
    {GPIO_PC4, hal_ll_uart_module_num(UART_MODULE_3), false},
    #endif
    #ifdef UART3_RX_RC5_RPI53
    {GPIO_PC5, hal_ll_uart_module_num(UART_MODULE_3), false},
    #endif
    #ifdef UART3_RX_RC6_RP54
    {GPIO_PC6, hal_ll_uart_module_num(UART_MODULE_3), false},
    #endif
    #ifdef UART3_RX_RC7_RP55
    {GPIO_PC7, hal_ll_uart_module_num(UART_MODULE_3), false},
    #endif
    #ifdef UART3_RX_RC8_RP56
    {GPIO_PC8, hal_ll_uart_module_num(UART_MODULE_3), false},
    #endif
    #ifdef UART3_RX_RC9_RP57
    {GPIO_PC9, hal_ll_uart_module_num(UART_MODULE_3), false},
    #endif
    #ifdef UART4_RX_RA0_RPI16
    {GPIO_PA0, hal_ll_uart_module_num(UART_MODULE_4), false},
    #endif
    #ifdef UART4_RX_RA1_RPI17
    {GPIO_PA1, hal_ll_uart_module_num(UART_MODULE_4), false},
    #endif
    #ifdef UART4_RX_RA2_RPI18
    {GPIO_PA2, hal_ll_uart_module_num(UART_MODULE_4), false},
    #endif
    #ifdef UART4_RX_RA3_RPI19
    {GPIO_PA3, hal_ll_uart_module_num(UART_MODULE_4), false},
    #endif
    #ifdef UART4_RX_RA4_RP20
    {GPIO_PA4, hal_ll_uart_module_num(UART_MODULE_4), false},
    #endif
    #ifdef UART4_RX_RA8_RPI24
    {GPIO_PA8, hal_ll_uart_module_num(UART_MODULE_4), false},
    #endif
    #ifdef UART4_RX_RA9_RPI25
    {GPIO_PA9, hal_ll_uart_module_num(UART_MODULE_4), false},
    #endif
    #ifdef UART4_RX_RB0_RPI32
    {GPIO_PB0, hal_ll_uart_module_num(UART_MODULE_4), false},
    #endif
    #ifdef UART4_RX_RB1_RPI33
    {GPIO_PB1, hal_ll_uart_module_num(UART_MODULE_4), false},
    #endif
    #ifdef UART4_RX_RB10_RP42
    {GPIO_PB10, hal_ll_uart_module_num(UART_MODULE_4), false},
    #endif
    #ifdef UART4_RX_RB11_RP43
    {GPIO_PB11, hal_ll_uart_module_num(UART_MODULE_4), false},
    #endif
    #ifdef UART4_RX_RB12_RPI44
    {GPIO_PB12, hal_ll_uart_module_num(UART_MODULE_4), false},
    #endif
    #ifdef UART4_RX_RB13_RPI45
    {GPIO_PB13, hal_ll_uart_module_num(UART_MODULE_4), false},
    #endif
    #ifdef UART4_RX_RB14_RPI46
    {GPIO_PB14, hal_ll_uart_module_num(UART_MODULE_4), false},
    #endif
    #ifdef UART4_RX_RB15_RPI47
    {GPIO_PB15, hal_ll_uart_module_num(UART_MODULE_4), false},
    #endif
    #ifdef UART4_RX_RB2_RPI34
    {GPIO_PB2, hal_ll_uart_module_num(UART_MODULE_4), false},
    #endif
    #ifdef UART4_RX_RB3_RP35
    {GPIO_PB3, hal_ll_uart_module_num(UART_MODULE_4), false},
    #endif
    #ifdef UART4_RX_RB4_RP36
    {GPIO_PB4, hal_ll_uart_module_num(UART_MODULE_4), false},
    #endif
    #ifdef UART4_RX_RB5_RP37
    {GPIO_PB5, hal_ll_uart_module_num(UART_MODULE_4), false},
    #endif
    #ifdef UART4_RX_RB6_RP38
    {GPIO_PB6, hal_ll_uart_module_num(UART_MODULE_4), false},
    #endif
    #ifdef UART4_RX_RB7_RP39
    {GPIO_PB7, hal_ll_uart_module_num(UART_MODULE_4), false},
    #endif
    #ifdef UART4_RX_RB8_RP40
    {GPIO_PB8, hal_ll_uart_module_num(UART_MODULE_4), false},
    #endif
    #ifdef UART4_RX_RB9_RP41
    {GPIO_PB9, hal_ll_uart_module_num(UART_MODULE_4), false},
    #endif
    #ifdef UART4_RX_RC0_RP48
    {GPIO_PC0, hal_ll_uart_module_num(UART_MODULE_4), false},
    #endif
    #ifdef UART4_RX_RC1_RP49
    {GPIO_PC1, hal_ll_uart_module_num(UART_MODULE_4), false},
    #endif
    #ifdef UART4_RX_RC2_RPI50
    {GPIO_PC2, hal_ll_uart_module_num(UART_MODULE_4), false},
    #endif
    #ifdef UART4_RX_RC3_RPI51
    {GPIO_PC3, hal_ll_uart_module_num(UART_MODULE_4), false},
    #endif
    #ifdef UART4_RX_RC4_RPI52
    {GPIO_PC4, hal_ll_uart_module_num(UART_MODULE_4), false},
    #endif
    #ifdef UART4_RX_RC5_RPI53
    {GPIO_PC5, hal_ll_uart_module_num(UART_MODULE_4), false},
    #endif
    #ifdef UART4_RX_RC6_RP54
    {GPIO_PC6, hal_ll_uart_module_num(UART_MODULE_4), false},
    #endif
    #ifdef UART4_RX_RC7_RP55
    {GPIO_PC7, hal_ll_uart_module_num(UART_MODULE_4), false},
    #endif
    #ifdef UART4_RX_RC8_RP56
    {GPIO_PC8, hal_ll_uart_module_num(UART_MODULE_4), false},
    #endif
    #ifdef UART4_RX_RC9_RP57
    {GPIO_PC9, hal_ll_uart_module_num(UART_MODULE_4), false},
    #endif
    #ifdef UART1_RX_RA11_RPI27
    {GPIO_PA11, hal_ll_uart_module_num(UART_MODULE_1), false},
    #endif
    #ifdef UART1_RX_RA12_RPI28
    {GPIO_PA12, hal_ll_uart_module_num(UART_MODULE_1), false},
    #endif
    #ifdef UART1_RX_RC10_RPI58
    {GPIO_PC10, hal_ll_uart_module_num(UART_MODULE_1), false},
    #endif
    #ifdef UART1_RX_RC12_RPI60
    {GPIO_PC12, hal_ll_uart_module_num(UART_MODULE_1), false},
    #endif
    #ifdef UART1_RX_RC13_RPI61
    {GPIO_PC13, hal_ll_uart_module_num(UART_MODULE_1), false},
    #endif
    #ifdef UART1_RX_RC15_RPI63
    {GPIO_PC15, hal_ll_uart_module_num(UART_MODULE_1), false},
    #endif
    #ifdef UART1_RX_RD5_RP69
    {GPIO_PD5, hal_ll_uart_module_num(UART_MODULE_1), false},
    #endif
    #ifdef UART1_RX_RD6_RP70
    {GPIO_PD6, hal_ll_uart_module_num(UART_MODULE_1), false},
    #endif
    #ifdef UART1_RX_RD8_RPI72
    {GPIO_PD8, hal_ll_uart_module_num(UART_MODULE_1), false},
    #endif
    #ifdef UART1_RX_RE14_RPI94
    {GPIO_PE14, hal_ll_uart_module_num(UART_MODULE_1), false},
    #endif
    #ifdef UART1_RX_RE15_RPI95
    {GPIO_PE15, hal_ll_uart_module_num(UART_MODULE_1), false},
    #endif
    #ifdef UART1_RX_RF0_RPI96
    {GPIO_PF0, hal_ll_uart_module_num(UART_MODULE_1), false},
    #endif
    #ifdef UART1_RX_RF1_RP97
    {GPIO_PF1, hal_ll_uart_module_num(UART_MODULE_1), false},
    #endif
    #ifdef UART1_RX_RG6_RP118
    {GPIO_PG6, hal_ll_uart_module_num(UART_MODULE_1), false},
    #endif
    #ifdef UART1_RX_RG7_RPI119
    {GPIO_PG7, hal_ll_uart_module_num(UART_MODULE_1), false},
    #endif
    #ifdef UART1_RX_RG8_RP120
    {GPIO_PG8, hal_ll_uart_module_num(UART_MODULE_1), false},
    #endif
    #ifdef UART1_RX_RG9_RPI121
    {GPIO_PG9, hal_ll_uart_module_num(UART_MODULE_1), false},
    #endif
    #ifdef UART2_RX_RA11_RPI27
    {GPIO_PA11, hal_ll_uart_module_num(UART_MODULE_2), false},
    #endif
    #ifdef UART2_RX_RA12_RPI28
    {GPIO_PA12, hal_ll_uart_module_num(UART_MODULE_2), false},
    #endif
    #ifdef UART2_RX_RC10_RPI58
    {GPIO_PC10, hal_ll_uart_module_num(UART_MODULE_2), false},
    #endif
    #ifdef UART2_RX_RC12_RPI60
    {GPIO_PC12, hal_ll_uart_module_num(UART_MODULE_2), false},
    #endif
    #ifdef UART2_RX_RC13_RPI61
    {GPIO_PC13, hal_ll_uart_module_num(UART_MODULE_2), false},
    #endif
    #ifdef UART2_RX_RC15_RPI63
    {GPIO_PC15, hal_ll_uart_module_num(UART_MODULE_2), false},
    #endif
    #ifdef UART2_RX_RD5_RP69
    {GPIO_PD5, hal_ll_uart_module_num(UART_MODULE_2), false},
    #endif
    #ifdef UART2_RX_RD6_RP70
    {GPIO_PD6, hal_ll_uart_module_num(UART_MODULE_2), false},
    #endif
    #ifdef UART2_RX_RD8_RPI72
    {GPIO_PD8, hal_ll_uart_module_num(UART_MODULE_2), false},
    #endif
    #ifdef UART2_RX_RE14_RPI94
    {GPIO_PE14, hal_ll_uart_module_num(UART_MODULE_2), false},
    #endif
    #ifdef UART2_RX_RE15_RPI95
    {GPIO_PE15, hal_ll_uart_module_num(UART_MODULE_2), false},
    #endif
    #ifdef UART2_RX_RF0_RPI96
    {GPIO_PF0, hal_ll_uart_module_num(UART_MODULE_2), false},
    #endif
    #ifdef UART2_RX_RF1_RP97
    {GPIO_PF1, hal_ll_uart_module_num(UART_MODULE_2), false},
    #endif
    #ifdef UART2_RX_RG6_RP118
    {GPIO_PG6, hal_ll_uart_module_num(UART_MODULE_2), false},
    #endif
    #ifdef UART2_RX_RG7_RPI119
    {GPIO_PG7, hal_ll_uart_module_num(UART_MODULE_2), false},
    #endif
    #ifdef UART2_RX_RG8_RP120
    {GPIO_PG8, hal_ll_uart_module_num(UART_MODULE_2), false},
    #endif
    #ifdef UART2_RX_RG9_RPI121
    {GPIO_PG9, hal_ll_uart_module_num(UART_MODULE_2), false},
    #endif
    #ifdef UART3_RX_RA11_RPI27
    {GPIO_PA11, hal_ll_uart_module_num(UART_MODULE_3), false},
    #endif
    #ifdef UART3_RX_RA12_RPI28
    {GPIO_PA12, hal_ll_uart_module_num(UART_MODULE_3), false},
    #endif
    #ifdef UART3_RX_RC10_RPI58
    {GPIO_PC10, hal_ll_uart_module_num(UART_MODULE_3), false},
    #endif
    #ifdef UART3_RX_RC12_RPI60
    {GPIO_PC12, hal_ll_uart_module_num(UART_MODULE_3), false},
    #endif
    #ifdef UART3_RX_RC13_RPI61
    {GPIO_PC13, hal_ll_uart_module_num(UART_MODULE_3), false},
    #endif
    #ifdef UART3_RX_RC15_RPI63
    {GPIO_PC15, hal_ll_uart_module_num(UART_MODULE_3), false},
    #endif
    #ifdef UART3_RX_RD5_RP69
    {GPIO_PD5, hal_ll_uart_module_num(UART_MODULE_3), false},
    #endif
    #ifdef UART3_RX_RD6_RP70
    {GPIO_PD6, hal_ll_uart_module_num(UART_MODULE_3), false},
    #endif
    #ifdef UART3_RX_RD8_RPI72
    {GPIO_PD8, hal_ll_uart_module_num(UART_MODULE_3), false},
    #endif
    #ifdef UART3_RX_RE14_RPI94
    {GPIO_PE14, hal_ll_uart_module_num(UART_MODULE_3), false},
    #endif
    #ifdef UART3_RX_RE15_RPI95
    {GPIO_PE15, hal_ll_uart_module_num(UART_MODULE_3), false},
    #endif
    #ifdef UART3_RX_RF0_RPI96
    {GPIO_PF0, hal_ll_uart_module_num(UART_MODULE_3), false},
    #endif
    #ifdef UART3_RX_RF1_RP97
    {GPIO_PF1, hal_ll_uart_module_num(UART_MODULE_3), false},
    #endif
    #ifdef UART3_RX_RG6_RP118
    {GPIO_PG6, hal_ll_uart_module_num(UART_MODULE_3), false},
    #endif
    #ifdef UART3_RX_RG7_RPI119
    {GPIO_PG7, hal_ll_uart_module_num(UART_MODULE_3), false},
    #endif
    #ifdef UART3_RX_RG8_RP120
    {GPIO_PG8, hal_ll_uart_module_num(UART_MODULE_3), false},
    #endif
    #ifdef UART3_RX_RG9_RPI121
    {GPIO_PG9, hal_ll_uart_module_num(UART_MODULE_3), false},
    #endif
    #ifdef UART4_RX_RA11_RPI27
    {GPIO_PA11, hal_ll_uart_module_num(UART_MODULE_4), false},
    #endif
    #ifdef UART4_RX_RA12_RPI28
    {GPIO_PA12, hal_ll_uart_module_num(UART_MODULE_4), false},
    #endif
    #ifdef UART4_RX_RC10_RPI58
    {GPIO_PC10, hal_ll_uart_module_num(UART_MODULE_4), false},
    #endif
    #ifdef UART4_RX_RC12_RPI60
    {GPIO_PC12, hal_ll_uart_module_num(UART_MODULE_4), false},
    #endif
    #ifdef UART4_RX_RC13_RPI61
    {GPIO_PC13, hal_ll_uart_module_num(UART_MODULE_4), false},
    #endif
    #ifdef UART4_RX_RC15_RPI63
    {GPIO_PC15, hal_ll_uart_module_num(UART_MODULE_4), false},
    #endif
    #ifdef UART4_RX_RD5_RP69
    {GPIO_PD5, hal_ll_uart_module_num(UART_MODULE_4), false},
    #endif
    #ifdef UART4_RX_RD6_RP70
    {GPIO_PD6, hal_ll_uart_module_num(UART_MODULE_4), false},
    #endif
    #ifdef UART4_RX_RD8_RPI72
    {GPIO_PD8, hal_ll_uart_module_num(UART_MODULE_4), false},
    #endif
    #ifdef UART4_RX_RE14_RPI94
    {GPIO_PE14, hal_ll_uart_module_num(UART_MODULE_4), false},
    #endif
    #ifdef UART4_RX_RE15_RPI95
    {GPIO_PE15, hal_ll_uart_module_num(UART_MODULE_4), false},
    #endif
    #ifdef UART4_RX_RF0_RPI96
    {GPIO_PF0, hal_ll_uart_module_num(UART_MODULE_4), false},
    #endif
    #ifdef UART4_RX_RF1_RP97
    {GPIO_PF1, hal_ll_uart_module_num(UART_MODULE_4), false},
    #endif
    #ifdef UART4_RX_RG6_RP118
    {GPIO_PG6, hal_ll_uart_module_num(UART_MODULE_4), false},
    #endif
    #ifdef UART4_RX_RG7_RPI119
    {GPIO_PG7, hal_ll_uart_module_num(UART_MODULE_4), false},
    #endif
    #ifdef UART4_RX_RG8_RP120
    {GPIO_PG8, hal_ll_uart_module_num(UART_MODULE_4), false},
    #endif
    #ifdef UART4_RX_RG9_RPI121
    {GPIO_PG9, hal_ll_uart_module_num(UART_MODULE_4), false},
    #endif
    #ifdef UART1_RX_RD12_RPI76
    {GPIO_PD12, hal_ll_uart_module_num(UART_MODULE_1), false},
    #endif
    #ifdef UART1_RX_RD13_RPI77
    {GPIO_PD13, hal_ll_uart_module_num(UART_MODULE_1), false},
    #endif
    #ifdef UART1_RX_RE0_RPI80
    {GPIO_PE0, hal_ll_uart_module_num(UART_MODULE_1), false},
    #endif
    #ifdef UART1_RX_RE1_RP81
    {GPIO_PE1, hal_ll_uart_module_num(UART_MODULE_1), false},
    #endif
    #ifdef UART1_RX_RG0_RPI112
    {GPIO_PG0, hal_ll_uart_module_num(UART_MODULE_1), false},
    #endif
    #ifdef UART1_RX_RG1_RP113
    {GPIO_PG1, hal_ll_uart_module_num(UART_MODULE_1), false},
    #endif
    #ifdef UART1_RX_RG12_RPI124
    {GPIO_PG12, hal_ll_uart_module_num(UART_MODULE_1), false},
    #endif
    #ifdef UART1_RX_RG13_RP125
    {GPIO_PG13, hal_ll_uart_module_num(UART_MODULE_1), false},
    #endif
    #ifdef UART1_RX_RG14_RP126
    {GPIO_PG14, hal_ll_uart_module_num(UART_MODULE_1), false},
    #endif
    #ifdef UART1_RX_RG15_RP127
    {GPIO_PG15, hal_ll_uart_module_num(UART_MODULE_1), false},
    #endif
    #ifdef UART2_RX_RD12_RPI76
    {GPIO_PD12, hal_ll_uart_module_num(UART_MODULE_2), false},
    #endif
    #ifdef UART2_RX_RD13_RPI77
    {GPIO_PD13, hal_ll_uart_module_num(UART_MODULE_2), false},
    #endif
    #ifdef UART2_RX_RE0_RPI80
    {GPIO_PE0, hal_ll_uart_module_num(UART_MODULE_2), false},
    #endif
    #ifdef UART2_RX_RE1_RP81
    {GPIO_PE1, hal_ll_uart_module_num(UART_MODULE_2), false},
    #endif
    #ifdef UART2_RX_RG0_RPI112
    {GPIO_PG0, hal_ll_uart_module_num(UART_MODULE_2), false},
    #endif
    #ifdef UART2_RX_RG1_RP113
    {GPIO_PG1, hal_ll_uart_module_num(UART_MODULE_2), false},
    #endif
    #ifdef UART2_RX_RG12_RPI124
    {GPIO_PG12, hal_ll_uart_module_num(UART_MODULE_2), false},
    #endif
    #ifdef UART2_RX_RG13_RP125
    {GPIO_PG13, hal_ll_uart_module_num(UART_MODULE_2), false},
    #endif
    #ifdef UART2_RX_RG14_RP126
    {GPIO_PG14, hal_ll_uart_module_num(UART_MODULE_2), false},
    #endif
    #ifdef UART2_RX_RG15_RP127
    {GPIO_PG15, hal_ll_uart_module_num(UART_MODULE_2), false},
    #endif
    #ifdef UART3_RX_RD12_RPI76
    {GPIO_PD12, hal_ll_uart_module_num(UART_MODULE_3), false},
    #endif
    #ifdef UART3_RX_RD13_RPI77
    {GPIO_PD13, hal_ll_uart_module_num(UART_MODULE_3), false},
    #endif
    #ifdef UART3_RX_RE0_RPI80
    {GPIO_PE0, hal_ll_uart_module_num(UART_MODULE_3), false},
    #endif
    #ifdef UART3_RX_RE1_RP81
    {GPIO_PE1, hal_ll_uart_module_num(UART_MODULE_3), false},
    #endif
    #ifdef UART3_RX_RG0_RPI112
    {GPIO_PG0, hal_ll_uart_module_num(UART_MODULE_3), false},
    #endif
    #ifdef UART3_RX_RG1_RP113
    {GPIO_PG1, hal_ll_uart_module_num(UART_MODULE_3), false},
    #endif
    #ifdef UART3_RX_RG12_RPI124
    {GPIO_PG12, hal_ll_uart_module_num(UART_MODULE_3), false},
    #endif
    #ifdef UART3_RX_RG13_RP125
    {GPIO_PG13, hal_ll_uart_module_num(UART_MODULE_3), false},
    #endif
    #ifdef UART3_RX_RG14_RP126
    {GPIO_PG14, hal_ll_uart_module_num(UART_MODULE_3), false},
    #endif
    #ifdef UART3_RX_RG15_RP127
    {GPIO_PG15, hal_ll_uart_module_num(UART_MODULE_3), false},
    #endif
    #ifdef UART4_RX_RD12_RPI76
    {GPIO_PD12, hal_ll_uart_module_num(UART_MODULE_4), false},
    #endif
    #ifdef UART4_RX_RD13_RPI77
    {GPIO_PD13, hal_ll_uart_module_num(UART_MODULE_4), false},
    #endif
    #ifdef UART4_RX_RE0_RPI80
    {GPIO_PE0, hal_ll_uart_module_num(UART_MODULE_4), false},
    #endif
    #ifdef UART4_RX_RE1_RP81
    {GPIO_PE1, hal_ll_uart_module_num(UART_MODULE_4), false},
    #endif
    #ifdef UART4_RX_RG0_RPI112
    {GPIO_PG0, hal_ll_uart_module_num(UART_MODULE_4), false},
    #endif
    #ifdef UART4_RX_RG1_RP113
    {GPIO_PG1, hal_ll_uart_module_num(UART_MODULE_4), false},
    #endif
    #ifdef UART4_RX_RG12_RPI124
    {GPIO_PG12, hal_ll_uart_module_num(UART_MODULE_4), false},
    #endif
    #ifdef UART4_RX_RG13_RP125
    {GPIO_PG13, hal_ll_uart_module_num(UART_MODULE_4), false},
    #endif
    #ifdef UART4_RX_RG14_RP126
    {GPIO_PG14, hal_ll_uart_module_num(UART_MODULE_4), false},
    #endif
    #ifdef UART4_RX_RG15_RP127
    {GPIO_PG15, hal_ll_uart_module_num(UART_MODULE_4), false},
    #endif
    #ifdef UART1_RX_RA0_RP16
    {GPIO_PA0, hal_ll_uart_module_num(UART_MODULE_1), false},
    #endif
    #ifdef UART1_RX_RA1_RP17
    {GPIO_PA1, hal_ll_uart_module_num(UART_MODULE_1), false},
    #endif
    #ifdef UART1_RX_RA2_RP18
    {GPIO_PA2, hal_ll_uart_module_num(UART_MODULE_1), false},
    #endif
    #ifdef UART1_RX_RA3_RP19
    {GPIO_PA3, hal_ll_uart_module_num(UART_MODULE_1), false},
    #endif
    #ifdef UART1_RX_RB0_RP32
    {GPIO_PB0, hal_ll_uart_module_num(UART_MODULE_1), false},
    #endif
    #ifdef UART1_RX_RB1_RP33
    {GPIO_PB1, hal_ll_uart_module_num(UART_MODULE_1), false},
    #endif
    #ifdef UART1_RX_RB12_RP44
    {GPIO_PB12, hal_ll_uart_module_num(UART_MODULE_1), false},
    #endif
    #ifdef UART1_RX_RB13_RP45
    {GPIO_PB13, hal_ll_uart_module_num(UART_MODULE_1), false},
    #endif
    #ifdef UART1_RX_RB14_RP46
    {GPIO_PB14, hal_ll_uart_module_num(UART_MODULE_1), false},
    #endif
    #ifdef UART1_RX_RB15_RP47
    {GPIO_PB15, hal_ll_uart_module_num(UART_MODULE_1), false},
    #endif
    #ifdef UART1_RX_RB2_RP34
    {GPIO_PB2, hal_ll_uart_module_num(UART_MODULE_1), false},
    #endif
    #ifdef UART2_RX_RA0_RP16
    {GPIO_PA0, hal_ll_uart_module_num(UART_MODULE_2), false},
    #endif
    #ifdef UART2_RX_RA1_RP17
    {GPIO_PA1, hal_ll_uart_module_num(UART_MODULE_2), false},
    #endif
    #ifdef UART2_RX_RA2_RP18
    {GPIO_PA2, hal_ll_uart_module_num(UART_MODULE_2), false},
    #endif
    #ifdef UART2_RX_RA3_RP19
    {GPIO_PA3, hal_ll_uart_module_num(UART_MODULE_2), false},
    #endif
    #ifdef UART2_RX_RB0_RP32
    {GPIO_PB0, hal_ll_uart_module_num(UART_MODULE_2), false},
    #endif
    #ifdef UART2_RX_RB1_RP33
    {GPIO_PB1, hal_ll_uart_module_num(UART_MODULE_2), false},
    #endif
    #ifdef UART2_RX_RB12_RP44
    {GPIO_PB12, hal_ll_uart_module_num(UART_MODULE_2), false},
    #endif
    #ifdef UART2_RX_RB13_RP45
    {GPIO_PB13, hal_ll_uart_module_num(UART_MODULE_2), false},
    #endif
    #ifdef UART2_RX_RB14_RP46
    {GPIO_PB14, hal_ll_uart_module_num(UART_MODULE_2), false},
    #endif
    #ifdef UART2_RX_RB15_RP47
    {GPIO_PB15, hal_ll_uart_module_num(UART_MODULE_2), false},
    #endif
    #ifdef UART2_RX_RB2_RP34
    {GPIO_PB2, hal_ll_uart_module_num(UART_MODULE_2), false},
    #endif
    #ifdef UART1_RX_RC10_RP58
    {GPIO_PC10, hal_ll_uart_module_num(UART_MODULE_1), false},
    #endif
    #ifdef UART1_RX_RC12_RP60
    {GPIO_PC12, hal_ll_uart_module_num(UART_MODULE_1), false},
    #endif
    #ifdef UART1_RX_RC13_RP61
    {GPIO_PC13, hal_ll_uart_module_num(UART_MODULE_1), false},
    #endif
    #ifdef UART1_RX_RC2_RP50
    {GPIO_PC2, hal_ll_uart_module_num(UART_MODULE_1), false},
    #endif
    #ifdef UART1_RX_RC3_RP51
    {GPIO_PC3, hal_ll_uart_module_num(UART_MODULE_1), false},
    #endif
    #ifdef UART1_RX_RC4_RP52
    {GPIO_PC4, hal_ll_uart_module_num(UART_MODULE_1), false},
    #endif
    #ifdef UART1_RX_RC5_RP53
    {GPIO_PC5, hal_ll_uart_module_num(UART_MODULE_1), false},
    #endif
    #ifdef UART2_RX_RC10_RP58
    {GPIO_PC10, hal_ll_uart_module_num(UART_MODULE_2), false},
    #endif
    #ifdef UART2_RX_RC12_RP60
    {GPIO_PC12, hal_ll_uart_module_num(UART_MODULE_2), false},
    #endif
    #ifdef UART2_RX_RC13_RP61
    {GPIO_PC13, hal_ll_uart_module_num(UART_MODULE_2), false},
    #endif
    #ifdef UART2_RX_RC2_RP50
    {GPIO_PC2, hal_ll_uart_module_num(UART_MODULE_2), false},
    #endif
    #ifdef UART2_RX_RC3_RP51
    {GPIO_PC3, hal_ll_uart_module_num(UART_MODULE_2), false},
    #endif
    #ifdef UART2_RX_RC4_RP52
    {GPIO_PC4, hal_ll_uart_module_num(UART_MODULE_2), false},
    #endif
    #ifdef UART2_RX_RC5_RP53
    {GPIO_PC5, hal_ll_uart_module_num(UART_MODULE_2), false},
    #endif
    #ifdef UART1_RX_RD10_RP74
    {GPIO_PD10, hal_ll_uart_module_num(UART_MODULE_1), false},
    #endif
    #ifdef UART1_RX_RD4_RP68
    {GPIO_PD4, hal_ll_uart_module_num(UART_MODULE_1), false},
    #endif
    #ifdef UART2_RX_RD10_RP74
    {GPIO_PD10, hal_ll_uart_module_num(UART_MODULE_2), false},
    #endif
    #ifdef UART2_RX_RD4_RP68
    {GPIO_PD4, hal_ll_uart_module_num(UART_MODULE_2), false},
    #endif
    #ifdef UART1_RX_RC14_RP62
    {GPIO_PC14, hal_ll_uart_module_num(UART_MODULE_1), false},
    #endif
    #ifdef UART1_RX_RC15_RP63
    {GPIO_PC15, hal_ll_uart_module_num(UART_MODULE_1), false},
    #endif
    #ifdef UART1_RX_RD0_RP64
    {GPIO_PD0, hal_ll_uart_module_num(UART_MODULE_1), false},
    #endif
    #ifdef UART1_RX_RD1_RP65
    {GPIO_PD1, hal_ll_uart_module_num(UART_MODULE_1), false},
    #endif
    #ifdef UART1_RX_RD11_RP75
    {GPIO_PD11, hal_ll_uart_module_num(UART_MODULE_1), false},
    #endif
    #ifdef UART1_RX_RD12_RP76
    {GPIO_PD12, hal_ll_uart_module_num(UART_MODULE_1), false},
    #endif
    #ifdef UART1_RX_RD2_RP66
    {GPIO_PD2, hal_ll_uart_module_num(UART_MODULE_1), false},
    #endif
    #ifdef UART1_RX_RD3_RP67
    {GPIO_PD3, hal_ll_uart_module_num(UART_MODULE_1), false},
    #endif
    #ifdef UART1_RX_RD7_RP71
    {GPIO_PD7, hal_ll_uart_module_num(UART_MODULE_1), false},
    #endif
    #ifdef UART1_RX_RD8_RP72
    {GPIO_PD8, hal_ll_uart_module_num(UART_MODULE_1), false},
    #endif
    #ifdef UART1_RX_RD9_RP73
    {GPIO_PD9, hal_ll_uart_module_num(UART_MODULE_1), false},
    #endif
    #ifdef UART2_RX_RC14_RP62
    {GPIO_PC14, hal_ll_uart_module_num(UART_MODULE_2), false},
    #endif
    #ifdef UART2_RX_RC15_RP63
    {GPIO_PC15, hal_ll_uart_module_num(UART_MODULE_2), false},
    #endif
    #ifdef UART2_RX_RD0_RP64
    {GPIO_PD0, hal_ll_uart_module_num(UART_MODULE_2), false},
    #endif
    #ifdef UART2_RX_RD1_RP65
    {GPIO_PD1, hal_ll_uart_module_num(UART_MODULE_2), false},
    #endif
    #ifdef UART2_RX_RD11_RP75
    {GPIO_PD11, hal_ll_uart_module_num(UART_MODULE_2), false},
    #endif
    #ifdef UART2_RX_RD12_RP76
    {GPIO_PD12, hal_ll_uart_module_num(UART_MODULE_2), false},
    #endif
    #ifdef UART2_RX_RD2_RP66
    {GPIO_PD2, hal_ll_uart_module_num(UART_MODULE_2), false},
    #endif
    #ifdef UART2_RX_RD3_RP67
    {GPIO_PD3, hal_ll_uart_module_num(UART_MODULE_2), false},
    #endif
    #ifdef UART2_RX_RD7_RP71
    {GPIO_PD7, hal_ll_uart_module_num(UART_MODULE_2), false},
    #endif
    #ifdef UART2_RX_RD8_RP72
    {GPIO_PD8, hal_ll_uart_module_num(UART_MODULE_2), false},
    #endif
    #ifdef UART2_RX_RD9_RP73
    {GPIO_PD9, hal_ll_uart_module_num(UART_MODULE_2), false},
    #endif
    #ifdef UART1_RX_RC11_RP59
    {GPIO_PC11, hal_ll_uart_module_num(UART_MODULE_1), false},
    #endif
    #ifdef UART2_RX_RC11_RP59
    {GPIO_PC11, hal_ll_uart_module_num(UART_MODULE_2), false},
    #endif
    #ifdef UART1_RX_RB10_RPI42
    {GPIO_PB10, hal_ll_uart_module_num(UART_MODULE_1), false},
    #endif
    #ifdef UART1_RX_RB11_RPI43
    {GPIO_PB11, hal_ll_uart_module_num(UART_MODULE_1), false},
    #endif
    #ifdef UART1_RX_RB3_RPI35
    {GPIO_PB3, hal_ll_uart_module_num(UART_MODULE_1), false},
    #endif
    #ifdef UART1_RX_RB4_RPI36
    {GPIO_PB4, hal_ll_uart_module_num(UART_MODULE_1), false},
    #endif
    #ifdef UART1_RX_RB5_RPI37
    {GPIO_PB5, hal_ll_uart_module_num(UART_MODULE_1), false},
    #endif
    #ifdef UART1_RX_RB6_RPI38
    {GPIO_PB6, hal_ll_uart_module_num(UART_MODULE_1), false},
    #endif
    #ifdef UART1_RX_RB7_RPI39
    {GPIO_PB7, hal_ll_uart_module_num(UART_MODULE_1), false},
    #endif
    #ifdef UART1_RX_RB8_RPI40
    {GPIO_PB8, hal_ll_uart_module_num(UART_MODULE_1), false},
    #endif
    #ifdef UART1_RX_RB9_RPI41
    {GPIO_PB9, hal_ll_uart_module_num(UART_MODULE_1), false},
    #endif
    #ifdef UART1_RX_RC14_RPI62
    {GPIO_PC14, hal_ll_uart_module_num(UART_MODULE_1), false},
    #endif
    #ifdef UART1_RX_RD10_RPI74
    {GPIO_PD10, hal_ll_uart_module_num(UART_MODULE_1), false},
    #endif
    #ifdef UART1_RX_RD11_RPI75
    {GPIO_PD11, hal_ll_uart_module_num(UART_MODULE_1), false},
    #endif
    #ifdef UART1_RX_RD9_RPI73
    {GPIO_PD9, hal_ll_uart_module_num(UART_MODULE_1), false},
    #endif
    #ifdef UART1_RX_RE0_RP80
    {GPIO_PE0, hal_ll_uart_module_num(UART_MODULE_1), false},
    #endif
    #ifdef UART1_RX_RE1_RPI81
    {GPIO_PE1, hal_ll_uart_module_num(UART_MODULE_1), false},
    #endif
    #ifdef UART1_RX_RE2_RP82
    {GPIO_PE2, hal_ll_uart_module_num(UART_MODULE_1), false},
    #endif
    #ifdef UART1_RX_RE3_RPI83
    {GPIO_PE3, hal_ll_uart_module_num(UART_MODULE_1), false},
    #endif
    #ifdef UART1_RX_RE4_RP84
    {GPIO_PE4, hal_ll_uart_module_num(UART_MODULE_1), false},
    #endif
    #ifdef UART1_RX_RE5_RP85
    {GPIO_PE5, hal_ll_uart_module_num(UART_MODULE_1), false},
    #endif
    #ifdef UART1_RX_RE6_RPI86
    {GPIO_PE6, hal_ll_uart_module_num(UART_MODULE_1), false},
    #endif
    #ifdef UART1_RX_RE7_RP87
    {GPIO_PE7, hal_ll_uart_module_num(UART_MODULE_1), false},
    #endif
    #ifdef UART1_RX_RF0_RP96
    {GPIO_PF0, hal_ll_uart_module_num(UART_MODULE_1), false},
    #endif
    #ifdef UART1_RX_RF3_RP99
    {GPIO_PF3, hal_ll_uart_module_num(UART_MODULE_1), false},
    #endif
    #ifdef UART1_RX_RF4_RP100
    {GPIO_PF4, hal_ll_uart_module_num(UART_MODULE_1), false},
    #endif
    #ifdef UART1_RX_RF5_RP101
    {GPIO_PF5, hal_ll_uart_module_num(UART_MODULE_1), false},
    #endif
    #ifdef UART2_RX_RB10_RPI42
    {GPIO_PB10, hal_ll_uart_module_num(UART_MODULE_2), false},
    #endif
    #ifdef UART2_RX_RB11_RPI43
    {GPIO_PB11, hal_ll_uart_module_num(UART_MODULE_2), false},
    #endif
    #ifdef UART2_RX_RB3_RPI35
    {GPIO_PB3, hal_ll_uart_module_num(UART_MODULE_2), false},
    #endif
    #ifdef UART2_RX_RB4_RPI36
    {GPIO_PB4, hal_ll_uart_module_num(UART_MODULE_2), false},
    #endif
    #ifdef UART2_RX_RB5_RPI37
    {GPIO_PB5, hal_ll_uart_module_num(UART_MODULE_2), false},
    #endif
    #ifdef UART2_RX_RB6_RPI38
    {GPIO_PB6, hal_ll_uart_module_num(UART_MODULE_2), false},
    #endif
    #ifdef UART2_RX_RB7_RPI39
    {GPIO_PB7, hal_ll_uart_module_num(UART_MODULE_2), false},
    #endif
    #ifdef UART2_RX_RB8_RPI40
    {GPIO_PB8, hal_ll_uart_module_num(UART_MODULE_2), false},
    #endif
    #ifdef UART2_RX_RB9_RPI41
    {GPIO_PB9, hal_ll_uart_module_num(UART_MODULE_2), false},
    #endif
    #ifdef UART2_RX_RC14_RPI62
    {GPIO_PC14, hal_ll_uart_module_num(UART_MODULE_2), false},
    #endif
    #ifdef UART2_RX_RD10_RPI74
    {GPIO_PD10, hal_ll_uart_module_num(UART_MODULE_2), false},
    #endif
    #ifdef UART2_RX_RD11_RPI75
    {GPIO_PD11, hal_ll_uart_module_num(UART_MODULE_2), false},
    #endif
    #ifdef UART2_RX_RD9_RPI73
    {GPIO_PD9, hal_ll_uart_module_num(UART_MODULE_2), false},
    #endif
    #ifdef UART2_RX_RE0_RP80
    {GPIO_PE0, hal_ll_uart_module_num(UART_MODULE_2), false},
    #endif
    #ifdef UART2_RX_RE1_RPI81
    {GPIO_PE1, hal_ll_uart_module_num(UART_MODULE_2), false},
    #endif
    #ifdef UART2_RX_RE2_RP82
    {GPIO_PE2, hal_ll_uart_module_num(UART_MODULE_2), false},
    #endif
    #ifdef UART2_RX_RE3_RPI83
    {GPIO_PE3, hal_ll_uart_module_num(UART_MODULE_2), false},
    #endif
    #ifdef UART2_RX_RE4_RP84
    {GPIO_PE4, hal_ll_uart_module_num(UART_MODULE_2), false},
    #endif
    #ifdef UART2_RX_RE5_RP85
    {GPIO_PE5, hal_ll_uart_module_num(UART_MODULE_2), false},
    #endif
    #ifdef UART2_RX_RE6_RPI86
    {GPIO_PE6, hal_ll_uart_module_num(UART_MODULE_2), false},
    #endif
    #ifdef UART2_RX_RE7_RP87
    {GPIO_PE7, hal_ll_uart_module_num(UART_MODULE_2), false},
    #endif
    #ifdef UART2_RX_RF0_RP96
    {GPIO_PF0, hal_ll_uart_module_num(UART_MODULE_2), false},
    #endif
    #ifdef UART2_RX_RF3_RP99
    {GPIO_PF3, hal_ll_uart_module_num(UART_MODULE_2), false},
    #endif
    #ifdef UART2_RX_RF4_RP100
    {GPIO_PF4, hal_ll_uart_module_num(UART_MODULE_2), false},
    #endif
    #ifdef UART2_RX_RF5_RP101
    {GPIO_PF5, hal_ll_uart_module_num(UART_MODULE_2), false},
    #endif
    #ifdef UART3_RX_RB10_RPI42
    {GPIO_PB10, hal_ll_uart_module_num(UART_MODULE_3), false},
    #endif
    #ifdef UART3_RX_RB11_RPI43
    {GPIO_PB11, hal_ll_uart_module_num(UART_MODULE_3), false},
    #endif
    #ifdef UART3_RX_RB3_RPI35
    {GPIO_PB3, hal_ll_uart_module_num(UART_MODULE_3), false},
    #endif
    #ifdef UART3_RX_RB4_RPI36
    {GPIO_PB4, hal_ll_uart_module_num(UART_MODULE_3), false},
    #endif
    #ifdef UART3_RX_RB5_RPI37
    {GPIO_PB5, hal_ll_uart_module_num(UART_MODULE_3), false},
    #endif
    #ifdef UART3_RX_RB6_RPI38
    {GPIO_PB6, hal_ll_uart_module_num(UART_MODULE_3), false},
    #endif
    #ifdef UART3_RX_RB7_RPI39
    {GPIO_PB7, hal_ll_uart_module_num(UART_MODULE_3), false},
    #endif
    #ifdef UART3_RX_RB8_RPI40
    {GPIO_PB8, hal_ll_uart_module_num(UART_MODULE_3), false},
    #endif
    #ifdef UART3_RX_RB9_RPI41
    {GPIO_PB9, hal_ll_uart_module_num(UART_MODULE_3), false},
    #endif
    #ifdef UART3_RX_RC14_RPI62
    {GPIO_PC14, hal_ll_uart_module_num(UART_MODULE_3), false},
    #endif
    #ifdef UART3_RX_RD0_RP64
    {GPIO_PD0, hal_ll_uart_module_num(UART_MODULE_3), false},
    #endif
    #ifdef UART3_RX_RD1_RP65
    {GPIO_PD1, hal_ll_uart_module_num(UART_MODULE_3), false},
    #endif
    #ifdef UART3_RX_RD10_RPI74
    {GPIO_PD10, hal_ll_uart_module_num(UART_MODULE_3), false},
    #endif
    #ifdef UART3_RX_RD11_RPI75
    {GPIO_PD11, hal_ll_uart_module_num(UART_MODULE_3), false},
    #endif
    #ifdef UART3_RX_RD2_RP66
    {GPIO_PD2, hal_ll_uart_module_num(UART_MODULE_3), false},
    #endif
    #ifdef UART3_RX_RD3_RP67
    {GPIO_PD3, hal_ll_uart_module_num(UART_MODULE_3), false},
    #endif
    #ifdef UART3_RX_RD4_RP68
    {GPIO_PD4, hal_ll_uart_module_num(UART_MODULE_3), false},
    #endif
    #ifdef UART3_RX_RD7_RP71
    {GPIO_PD7, hal_ll_uart_module_num(UART_MODULE_3), false},
    #endif
    #ifdef UART3_RX_RD9_RPI73
    {GPIO_PD9, hal_ll_uart_module_num(UART_MODULE_3), false},
    #endif
    #ifdef UART3_RX_RE0_RP80
    {GPIO_PE0, hal_ll_uart_module_num(UART_MODULE_3), false},
    #endif
    #ifdef UART3_RX_RE1_RPI81
    {GPIO_PE1, hal_ll_uart_module_num(UART_MODULE_3), false},
    #endif
    #ifdef UART3_RX_RE2_RP82
    {GPIO_PE2, hal_ll_uart_module_num(UART_MODULE_3), false},
    #endif
    #ifdef UART3_RX_RE3_RPI83
    {GPIO_PE3, hal_ll_uart_module_num(UART_MODULE_3), false},
    #endif
    #ifdef UART3_RX_RE4_RP84
    {GPIO_PE4, hal_ll_uart_module_num(UART_MODULE_3), false},
    #endif
    #ifdef UART3_RX_RE5_RP85
    {GPIO_PE5, hal_ll_uart_module_num(UART_MODULE_3), false},
    #endif
    #ifdef UART3_RX_RE6_RPI86
    {GPIO_PE6, hal_ll_uart_module_num(UART_MODULE_3), false},
    #endif
    #ifdef UART3_RX_RE7_RP87
    {GPIO_PE7, hal_ll_uart_module_num(UART_MODULE_3), false},
    #endif
    #ifdef UART3_RX_RF0_RP96
    {GPIO_PF0, hal_ll_uart_module_num(UART_MODULE_3), false},
    #endif
    #ifdef UART3_RX_RF3_RP99
    {GPIO_PF3, hal_ll_uart_module_num(UART_MODULE_3), false},
    #endif
    #ifdef UART3_RX_RF4_RP100
    {GPIO_PF4, hal_ll_uart_module_num(UART_MODULE_3), false},
    #endif
    #ifdef UART3_RX_RF5_RP101
    {GPIO_PF5, hal_ll_uart_module_num(UART_MODULE_3), false},
    #endif
    #ifdef UART4_RX_RB10_RPI42
    {GPIO_PB10, hal_ll_uart_module_num(UART_MODULE_4), false},
    #endif
    #ifdef UART4_RX_RB11_RPI43
    {GPIO_PB11, hal_ll_uart_module_num(UART_MODULE_4), false},
    #endif
    #ifdef UART4_RX_RB3_RPI35
    {GPIO_PB3, hal_ll_uart_module_num(UART_MODULE_4), false},
    #endif
    #ifdef UART4_RX_RB4_RPI36
    {GPIO_PB4, hal_ll_uart_module_num(UART_MODULE_4), false},
    #endif
    #ifdef UART4_RX_RB5_RPI37
    {GPIO_PB5, hal_ll_uart_module_num(UART_MODULE_4), false},
    #endif
    #ifdef UART4_RX_RB6_RPI38
    {GPIO_PB6, hal_ll_uart_module_num(UART_MODULE_4), false},
    #endif
    #ifdef UART4_RX_RB7_RPI39
    {GPIO_PB7, hal_ll_uart_module_num(UART_MODULE_4), false},
    #endif
    #ifdef UART4_RX_RB8_RPI40
    {GPIO_PB8, hal_ll_uart_module_num(UART_MODULE_4), false},
    #endif
    #ifdef UART4_RX_RB9_RPI41
    {GPIO_PB9, hal_ll_uart_module_num(UART_MODULE_4), false},
    #endif
    #ifdef UART4_RX_RC14_RPI62
    {GPIO_PC14, hal_ll_uart_module_num(UART_MODULE_4), false},
    #endif
    #ifdef UART4_RX_RD0_RP64
    {GPIO_PD0, hal_ll_uart_module_num(UART_MODULE_4), false},
    #endif
    #ifdef UART4_RX_RD1_RP65
    {GPIO_PD1, hal_ll_uart_module_num(UART_MODULE_4), false},
    #endif
    #ifdef UART4_RX_RD10_RPI74
    {GPIO_PD10, hal_ll_uart_module_num(UART_MODULE_4), false},
    #endif
    #ifdef UART4_RX_RD11_RPI75
    {GPIO_PD11, hal_ll_uart_module_num(UART_MODULE_4), false},
    #endif
    #ifdef UART4_RX_RD2_RP66
    {GPIO_PD2, hal_ll_uart_module_num(UART_MODULE_4), false},
    #endif
    #ifdef UART4_RX_RD3_RP67
    {GPIO_PD3, hal_ll_uart_module_num(UART_MODULE_4), false},
    #endif
    #ifdef UART4_RX_RD4_RP68
    {GPIO_PD4, hal_ll_uart_module_num(UART_MODULE_4), false},
    #endif
    #ifdef UART4_RX_RD7_RP71
    {GPIO_PD7, hal_ll_uart_module_num(UART_MODULE_4), false},
    #endif
    #ifdef UART4_RX_RD9_RPI73
    {GPIO_PD9, hal_ll_uart_module_num(UART_MODULE_4), false},
    #endif
    #ifdef UART4_RX_RE0_RP80
    {GPIO_PE0, hal_ll_uart_module_num(UART_MODULE_4), false},
    #endif
    #ifdef UART4_RX_RE1_RPI81
    {GPIO_PE1, hal_ll_uart_module_num(UART_MODULE_4), false},
    #endif
    #ifdef UART4_RX_RE2_RP82
    {GPIO_PE2, hal_ll_uart_module_num(UART_MODULE_4), false},
    #endif
    #ifdef UART4_RX_RE3_RPI83
    {GPIO_PE3, hal_ll_uart_module_num(UART_MODULE_4), false},
    #endif
    #ifdef UART4_RX_RE4_RP84
    {GPIO_PE4, hal_ll_uart_module_num(UART_MODULE_4), false},
    #endif
    #ifdef UART4_RX_RE5_RP85
    {GPIO_PE5, hal_ll_uart_module_num(UART_MODULE_4), false},
    #endif
    #ifdef UART4_RX_RE6_RPI86
    {GPIO_PE6, hal_ll_uart_module_num(UART_MODULE_4), false},
    #endif
    #ifdef UART4_RX_RE7_RP87
    {GPIO_PE7, hal_ll_uart_module_num(UART_MODULE_4), false},
    #endif
    #ifdef UART4_RX_RF0_RP96
    {GPIO_PF0, hal_ll_uart_module_num(UART_MODULE_4), false},
    #endif
    #ifdef UART4_RX_RF3_RP99
    {GPIO_PF3, hal_ll_uart_module_num(UART_MODULE_4), false},
    #endif
    #ifdef UART4_RX_RF4_RP100
    {GPIO_PF4, hal_ll_uart_module_num(UART_MODULE_4), false},
    #endif
    #ifdef UART4_RX_RF5_RP101
    {GPIO_PF5, hal_ll_uart_module_num(UART_MODULE_4), false},
    #endif
    #ifdef UART1_RX_RA14_RPI30
    {GPIO_PA14, hal_ll_uart_module_num(UART_MODULE_1), false},
    #endif
    #ifdef UART1_RX_RA15_RPI31
    {GPIO_PA15, hal_ll_uart_module_num(UART_MODULE_1), false},
    #endif
    #ifdef UART1_RX_RA4_RPI20
    {GPIO_PA4, hal_ll_uart_module_num(UART_MODULE_1), false},
    #endif
    #ifdef UART1_RX_RA5_RPI21
    {GPIO_PA5, hal_ll_uart_module_num(UART_MODULE_1), false},
    #endif
    #ifdef UART1_RX_RA6_RPI22
    {GPIO_PA6, hal_ll_uart_module_num(UART_MODULE_1), false},
    #endif
    #ifdef UART1_RX_RA7_RPI23
    {GPIO_PA7, hal_ll_uart_module_num(UART_MODULE_1), false},
    #endif
    #ifdef UART1_RX_RC1_RPI49
    {GPIO_PC1, hal_ll_uart_module_num(UART_MODULE_1), false},
    #endif
    #ifdef UART1_RX_RD14_RPI78
    {GPIO_PD14, hal_ll_uart_module_num(UART_MODULE_1), false},
    #endif
    #ifdef UART1_RX_RD15_RP79
    {GPIO_PD15, hal_ll_uart_module_num(UART_MODULE_1), false},
    #endif
    #ifdef UART1_RX_RE8_RPI88
    {GPIO_PE8, hal_ll_uart_module_num(UART_MODULE_1), false},
    #endif
    #ifdef UART1_RX_RE9_RPI89
    {GPIO_PE9, hal_ll_uart_module_num(UART_MODULE_1), false},
    #endif
    #ifdef UART1_RX_RF12_RP108
    {GPIO_PF12, hal_ll_uart_module_num(UART_MODULE_1), false},
    #endif
    #ifdef UART1_RX_RF13_RP109
    {GPIO_PF13, hal_ll_uart_module_num(UART_MODULE_1), false},
    #endif
    #ifdef UART1_RX_RF2_RP98
    {GPIO_PF2, hal_ll_uart_module_num(UART_MODULE_1), false},
    #endif
    #ifdef UART1_RX_RF8_RP104
    {GPIO_PF8, hal_ll_uart_module_num(UART_MODULE_1), false},
    #endif
    #ifdef UART1_RX_RG0_RP112
    {GPIO_PG0, hal_ll_uart_module_num(UART_MODULE_1), false},
    #endif
    #ifdef UART2_RX_RA14_RPI30
    {GPIO_PA14, hal_ll_uart_module_num(UART_MODULE_2), false},
    #endif
    #ifdef UART2_RX_RA15_RPI31
    {GPIO_PA15, hal_ll_uart_module_num(UART_MODULE_2), false},
    #endif
    #ifdef UART2_RX_RA4_RPI20
    {GPIO_PA4, hal_ll_uart_module_num(UART_MODULE_2), false},
    #endif
    #ifdef UART2_RX_RA5_RPI21
    {GPIO_PA5, hal_ll_uart_module_num(UART_MODULE_2), false},
    #endif
    #ifdef UART2_RX_RA6_RPI22
    {GPIO_PA6, hal_ll_uart_module_num(UART_MODULE_2), false},
    #endif
    #ifdef UART2_RX_RA7_RPI23
    {GPIO_PA7, hal_ll_uart_module_num(UART_MODULE_2), false},
    #endif
    #ifdef UART2_RX_RC1_RPI49
    {GPIO_PC1, hal_ll_uart_module_num(UART_MODULE_2), false},
    #endif
    #ifdef UART2_RX_RD14_RPI78
    {GPIO_PD14, hal_ll_uart_module_num(UART_MODULE_2), false},
    #endif
    #ifdef UART2_RX_RD15_RP79
    {GPIO_PD15, hal_ll_uart_module_num(UART_MODULE_2), false},
    #endif
    #ifdef UART2_RX_RE8_RPI88
    {GPIO_PE8, hal_ll_uart_module_num(UART_MODULE_2), false},
    #endif
    #ifdef UART2_RX_RE9_RPI89
    {GPIO_PE9, hal_ll_uart_module_num(UART_MODULE_2), false},
    #endif
    #ifdef UART2_RX_RF12_RP108
    {GPIO_PF12, hal_ll_uart_module_num(UART_MODULE_2), false},
    #endif
    #ifdef UART2_RX_RF13_RP109
    {GPIO_PF13, hal_ll_uart_module_num(UART_MODULE_2), false},
    #endif
    #ifdef UART2_RX_RF2_RP98
    {GPIO_PF2, hal_ll_uart_module_num(UART_MODULE_2), false},
    #endif
    #ifdef UART2_RX_RF8_RP104
    {GPIO_PF8, hal_ll_uart_module_num(UART_MODULE_2), false},
    #endif
    #ifdef UART2_RX_RG0_RP112
    {GPIO_PG0, hal_ll_uart_module_num(UART_MODULE_2), false},
    #endif
    #ifdef UART3_RX_RA14_RPI30
    {GPIO_PA14, hal_ll_uart_module_num(UART_MODULE_3), false},
    #endif
    #ifdef UART3_RX_RA15_RPI31
    {GPIO_PA15, hal_ll_uart_module_num(UART_MODULE_3), false},
    #endif
    #ifdef UART3_RX_RA4_RPI20
    {GPIO_PA4, hal_ll_uart_module_num(UART_MODULE_3), false},
    #endif
    #ifdef UART3_RX_RA5_RPI21
    {GPIO_PA5, hal_ll_uart_module_num(UART_MODULE_3), false},
    #endif
    #ifdef UART3_RX_RA6_RPI22
    {GPIO_PA6, hal_ll_uart_module_num(UART_MODULE_3), false},
    #endif
    #ifdef UART3_RX_RA7_RPI23
    {GPIO_PA7, hal_ll_uart_module_num(UART_MODULE_3), false},
    #endif
    #ifdef UART3_RX_RC1_RPI49
    {GPIO_PC1, hal_ll_uart_module_num(UART_MODULE_3), false},
    #endif
    #ifdef UART3_RX_RD14_RPI78
    {GPIO_PD14, hal_ll_uart_module_num(UART_MODULE_3), false},
    #endif
    #ifdef UART3_RX_RD15_RP79
    {GPIO_PD15, hal_ll_uart_module_num(UART_MODULE_3), false},
    #endif
    #ifdef UART3_RX_RE8_RPI88
    {GPIO_PE8, hal_ll_uart_module_num(UART_MODULE_3), false},
    #endif
    #ifdef UART3_RX_RE9_RPI89
    {GPIO_PE9, hal_ll_uart_module_num(UART_MODULE_3), false},
    #endif
    #ifdef UART3_RX_RF12_RP108
    {GPIO_PF12, hal_ll_uart_module_num(UART_MODULE_3), false},
    #endif
    #ifdef UART3_RX_RF13_RP109
    {GPIO_PF13, hal_ll_uart_module_num(UART_MODULE_3), false},
    #endif
    #ifdef UART3_RX_RF2_RP98
    {GPIO_PF2, hal_ll_uart_module_num(UART_MODULE_3), false},
    #endif
    #ifdef UART3_RX_RF8_RP104
    {GPIO_PF8, hal_ll_uart_module_num(UART_MODULE_3), false},
    #endif
    #ifdef UART3_RX_RG0_RP112
    {GPIO_PG0, hal_ll_uart_module_num(UART_MODULE_3), false},
    #endif
    #ifdef UART4_RX_RA14_RPI30
    {GPIO_PA14, hal_ll_uart_module_num(UART_MODULE_4), false},
    #endif
    #ifdef UART4_RX_RA15_RPI31
    {GPIO_PA15, hal_ll_uart_module_num(UART_MODULE_4), false},
    #endif
    #ifdef UART4_RX_RA4_RPI20
    {GPIO_PA4, hal_ll_uart_module_num(UART_MODULE_4), false},
    #endif
    #ifdef UART4_RX_RA5_RPI21
    {GPIO_PA5, hal_ll_uart_module_num(UART_MODULE_4), false},
    #endif
    #ifdef UART4_RX_RA6_RPI22
    {GPIO_PA6, hal_ll_uart_module_num(UART_MODULE_4), false},
    #endif
    #ifdef UART4_RX_RA7_RPI23
    {GPIO_PA7, hal_ll_uart_module_num(UART_MODULE_4), false},
    #endif
    #ifdef UART4_RX_RC1_RPI49
    {GPIO_PC1, hal_ll_uart_module_num(UART_MODULE_4), false},
    #endif
    #ifdef UART4_RX_RD14_RPI78
    {GPIO_PD14, hal_ll_uart_module_num(UART_MODULE_4), false},
    #endif
    #ifdef UART4_RX_RD15_RP79
    {GPIO_PD15, hal_ll_uart_module_num(UART_MODULE_4), false},
    #endif
    #ifdef UART4_RX_RE8_RPI88
    {GPIO_PE8, hal_ll_uart_module_num(UART_MODULE_4), false},
    #endif
    #ifdef UART4_RX_RE9_RPI89
    {GPIO_PE9, hal_ll_uart_module_num(UART_MODULE_4), false},
    #endif
    #ifdef UART4_RX_RF12_RP108
    {GPIO_PF12, hal_ll_uart_module_num(UART_MODULE_4), false},
    #endif
    #ifdef UART4_RX_RF13_RP109
    {GPIO_PF13, hal_ll_uart_module_num(UART_MODULE_4), false},
    #endif
    #ifdef UART4_RX_RF2_RP98
    {GPIO_PF2, hal_ll_uart_module_num(UART_MODULE_4), false},
    #endif
    #ifdef UART4_RX_RF8_RP104
    {GPIO_PF8, hal_ll_uart_module_num(UART_MODULE_4), false},
    #endif
    #ifdef UART4_RX_RG0_RP112
    {GPIO_PG0, hal_ll_uart_module_num(UART_MODULE_4), false},
    #endif
    #ifdef UART1_RX_RF6_RP102
    {GPIO_PF6, hal_ll_uart_module_num(UART_MODULE_1), false},
    #endif
    #ifdef UART2_RX_RF6_RP102
    {GPIO_PF6, hal_ll_uart_module_num(UART_MODULE_2), false},
    #endif
    #ifdef UART3_RX_RF6_RP102
    {GPIO_PF6, hal_ll_uart_module_num(UART_MODULE_3), false},
    #endif
    #ifdef UART4_RX_RF6_RP102
    {GPIO_PF6, hal_ll_uart_module_num(UART_MODULE_4), false},
    #endif
    #ifdef UART1_RX_RB0_RP0
    {GPIO_PB0, hal_ll_uart_module_num(UART_MODULE_1), false},
    #endif
    #ifdef UART1_RX_RB1_RP1
    {GPIO_PB1, hal_ll_uart_module_num(UART_MODULE_1), false},
    #endif
    #ifdef UART1_RX_RB10_RP10
    {GPIO_PB10, hal_ll_uart_module_num(UART_MODULE_1), false},
    #endif
    #ifdef UART1_RX_RB11_RP11
    {GPIO_PB11, hal_ll_uart_module_num(UART_MODULE_1), false},
    #endif
    #ifdef UART1_RX_RB12_RP12
    {GPIO_PB12, hal_ll_uart_module_num(UART_MODULE_1), false},
    #endif
    #ifdef UART1_RX_RB13_RP13
    {GPIO_PB13, hal_ll_uart_module_num(UART_MODULE_1), false},
    #endif
    #ifdef UART1_RX_RB14_RP14
    {GPIO_PB14, hal_ll_uart_module_num(UART_MODULE_1), false},
    #endif
    #ifdef UART1_RX_RB15_RP15
    {GPIO_PB15, hal_ll_uart_module_num(UART_MODULE_1), false},
    #endif
    #ifdef UART1_RX_RB2_RP2
    {GPIO_PB2, hal_ll_uart_module_num(UART_MODULE_1), false},
    #endif
    #ifdef UART1_RX_RB3_RP3
    {GPIO_PB3, hal_ll_uart_module_num(UART_MODULE_1), false},
    #endif
    #ifdef UART1_RX_RB4_RP4
    {GPIO_PB4, hal_ll_uart_module_num(UART_MODULE_1), false},
    #endif
    #ifdef UART1_RX_RB5_RP5
    {GPIO_PB5, hal_ll_uart_module_num(UART_MODULE_1), false},
    #endif
    #ifdef UART1_RX_RB6_RP6
    {GPIO_PB6, hal_ll_uart_module_num(UART_MODULE_1), false},
    #endif
    #ifdef UART1_RX_RB7_RP7
    {GPIO_PB7, hal_ll_uart_module_num(UART_MODULE_1), false},
    #endif
    #ifdef UART1_RX_RB8_RP8
    {GPIO_PB8, hal_ll_uart_module_num(UART_MODULE_1), false},
    #endif
    #ifdef UART1_RX_RB9_RP9
    {GPIO_PB9, hal_ll_uart_module_num(UART_MODULE_1), false},
    #endif
    #ifdef UART2_RX_RB0_RP0
    {GPIO_PB0, hal_ll_uart_module_num(UART_MODULE_2), false},
    #endif
    #ifdef UART2_RX_RB1_RP1
    {GPIO_PB1, hal_ll_uart_module_num(UART_MODULE_2), false},
    #endif
    #ifdef UART2_RX_RB10_RP10
    {GPIO_PB10, hal_ll_uart_module_num(UART_MODULE_2), false},
    #endif
    #ifdef UART2_RX_RB11_RP11
    {GPIO_PB11, hal_ll_uart_module_num(UART_MODULE_2), false},
    #endif
    #ifdef UART2_RX_RB12_RP12
    {GPIO_PB12, hal_ll_uart_module_num(UART_MODULE_2), false},
    #endif
    #ifdef UART2_RX_RB13_RP13
    {GPIO_PB13, hal_ll_uart_module_num(UART_MODULE_2), false},
    #endif
    #ifdef UART2_RX_RB14_RP14
    {GPIO_PB14, hal_ll_uart_module_num(UART_MODULE_2), false},
    #endif
    #ifdef UART2_RX_RB15_RP15
    {GPIO_PB15, hal_ll_uart_module_num(UART_MODULE_2), false},
    #endif
    #ifdef UART2_RX_RB2_RP2
    {GPIO_PB2, hal_ll_uart_module_num(UART_MODULE_2), false},
    #endif
    #ifdef UART2_RX_RB3_RP3
    {GPIO_PB3, hal_ll_uart_module_num(UART_MODULE_2), false},
    #endif
    #ifdef UART2_RX_RB4_RP4
    {GPIO_PB4, hal_ll_uart_module_num(UART_MODULE_2), false},
    #endif
    #ifdef UART2_RX_RB5_RP5
    {GPIO_PB5, hal_ll_uart_module_num(UART_MODULE_2), false},
    #endif
    #ifdef UART2_RX_RB6_RP6
    {GPIO_PB6, hal_ll_uart_module_num(UART_MODULE_2), false},
    #endif
    #ifdef UART2_RX_RB7_RP7
    {GPIO_PB7, hal_ll_uart_module_num(UART_MODULE_2), false},
    #endif
    #ifdef UART2_RX_RB8_RP8
    {GPIO_PB8, hal_ll_uart_module_num(UART_MODULE_2), false},
    #endif
    #ifdef UART2_RX_RB9_RP9
    {GPIO_PB9, hal_ll_uart_module_num(UART_MODULE_2), false},
    #endif
    #ifdef UART1_RX_RC0_RP16
    {GPIO_PC0, hal_ll_uart_module_num(UART_MODULE_1), false},
    #endif
    #ifdef UART1_RX_RC1_RP17
    {GPIO_PC1, hal_ll_uart_module_num(UART_MODULE_1), false},
    #endif
    #ifdef UART1_RX_RC2_RP18
    {GPIO_PC2, hal_ll_uart_module_num(UART_MODULE_1), false},
    #endif
    #ifdef UART1_RX_RC3_RP19
    {GPIO_PC3, hal_ll_uart_module_num(UART_MODULE_1), false},
    #endif
    #ifdef UART1_RX_RC4_RP20
    {GPIO_PC4, hal_ll_uart_module_num(UART_MODULE_1), false},
    #endif
    #ifdef UART1_RX_RC5_RP21
    {GPIO_PC5, hal_ll_uart_module_num(UART_MODULE_1), false},
    #endif
    #ifdef UART1_RX_RC6_RP22
    {GPIO_PC6, hal_ll_uart_module_num(UART_MODULE_1), false},
    #endif
    #ifdef UART1_RX_RC7_RP23
    {GPIO_PC7, hal_ll_uart_module_num(UART_MODULE_1), false},
    #endif
    #ifdef UART1_RX_RC8_RP24
    {GPIO_PC8, hal_ll_uart_module_num(UART_MODULE_1), false},
    #endif
    #ifdef UART1_RX_RC9_RP25
    {GPIO_PC9, hal_ll_uart_module_num(UART_MODULE_1), false},
    #endif
    #ifdef UART2_RX_RC0_RP16
    {GPIO_PC0, hal_ll_uart_module_num(UART_MODULE_2), false},
    #endif
    #ifdef UART2_RX_RC1_RP17
    {GPIO_PC1, hal_ll_uart_module_num(UART_MODULE_2), false},
    #endif
    #ifdef UART2_RX_RC2_RP18
    {GPIO_PC2, hal_ll_uart_module_num(UART_MODULE_2), false},
    #endif
    #ifdef UART2_RX_RC3_RP19
    {GPIO_PC3, hal_ll_uart_module_num(UART_MODULE_2), false},
    #endif
    #ifdef UART2_RX_RC4_RP20
    {GPIO_PC4, hal_ll_uart_module_num(UART_MODULE_2), false},
    #endif
    #ifdef UART2_RX_RC5_RP21
    {GPIO_PC5, hal_ll_uart_module_num(UART_MODULE_2), false},
    #endif
    #ifdef UART2_RX_RC6_RP22
    {GPIO_PC6, hal_ll_uart_module_num(UART_MODULE_2), false},
    #endif
    #ifdef UART2_RX_RC7_RP23
    {GPIO_PC7, hal_ll_uart_module_num(UART_MODULE_2), false},
    #endif
    #ifdef UART2_RX_RC8_RP24
    {GPIO_PC8, hal_ll_uart_module_num(UART_MODULE_2), false},
    #endif
    #ifdef UART2_RX_RC9_RP25
    {GPIO_PC9, hal_ll_uart_module_num(UART_MODULE_2), false},
    #endif
    #ifdef UART1_RX_RC10_RP26
    {GPIO_PC10, hal_ll_uart_module_num(UART_MODULE_1), false},
    #endif
    #ifdef UART1_RX_RC11_RP27
    {GPIO_PC11, hal_ll_uart_module_num(UART_MODULE_1), false},
    #endif
    #ifdef UART1_RX_RC12_RP28
    {GPIO_PC12, hal_ll_uart_module_num(UART_MODULE_1), false},
    #endif
    #ifdef UART1_RX_RC13_RP29
    {GPIO_PC13, hal_ll_uart_module_num(UART_MODULE_1), false},
    #endif
    #ifdef UART1_RX_RB2
    {GPIO_PB2, hal_ll_uart_module_num(UART_MODULE_1), false},
    #endif
    #ifdef UART2_RX_RB1
    {GPIO_PB1, hal_ll_uart_module_num(UART_MODULE_2), false},
    #endif
    #ifdef UART1_RX_RC6
    {GPIO_PC6, hal_ll_uart_module_num(UART_MODULE_1), false},
    #endif
    #ifdef UART1_RX_RB15_RP29
    {GPIO_PB15, hal_ll_uart_module_num(UART_MODULE_1), false},
    #endif
    #ifdef UART1_RX_RB2_RP13
    {GPIO_PB2, hal_ll_uart_module_num(UART_MODULE_1), false},
    #endif
    #ifdef UART1_RX_RB4_RP28
    {GPIO_PB4, hal_ll_uart_module_num(UART_MODULE_1), false},
    #endif
    #ifdef UART1_RX_RB5_RP18
    {GPIO_PB5, hal_ll_uart_module_num(UART_MODULE_1), false},
    #endif
    #ifdef UART1_RX_RC14_RPI37
    {GPIO_PC14, hal_ll_uart_module_num(UART_MODULE_1), false},
    #endif
    #ifdef UART1_RX_RD0_RP11
    {GPIO_PD0, hal_ll_uart_module_num(UART_MODULE_1), false},
    #endif
    #ifdef UART1_RX_RD1_RP24
    {GPIO_PD1, hal_ll_uart_module_num(UART_MODULE_1), false},
    #endif
    #ifdef UART1_RX_RD10_RP3
    {GPIO_PD10, hal_ll_uart_module_num(UART_MODULE_1), false},
    #endif
    #ifdef UART1_RX_RD11_RP12
    {GPIO_PD11, hal_ll_uart_module_num(UART_MODULE_1), false},
    #endif
    #ifdef UART1_RX_RD2_RP23
    {GPIO_PD2, hal_ll_uart_module_num(UART_MODULE_1), false},
    #endif
    #ifdef UART1_RX_RD3_RP22
    {GPIO_PD3, hal_ll_uart_module_num(UART_MODULE_1), false},
    #endif
    #ifdef UART1_RX_RD4_RP25
    {GPIO_PD4, hal_ll_uart_module_num(UART_MODULE_1), false},
    #endif
    #ifdef UART1_RX_RD5_RP20
    {GPIO_PD5, hal_ll_uart_module_num(UART_MODULE_1), false},
    #endif
    #ifdef UART1_RX_RD8_RP2
    {GPIO_PD8, hal_ll_uart_module_num(UART_MODULE_1), false},
    #endif
    #ifdef UART1_RX_RD9_RP4
    {GPIO_PD9, hal_ll_uart_module_num(UART_MODULE_1), false},
    #endif
    #ifdef UART1_RX_RF2_RP30
    {GPIO_PF2, hal_ll_uart_module_num(UART_MODULE_1), false},
    #endif
    #ifdef UART1_RX_RF3_RP16
    {GPIO_PF3, hal_ll_uart_module_num(UART_MODULE_1), false},
    #endif
    #ifdef UART1_RX_RF4_RP10
    {GPIO_PF4, hal_ll_uart_module_num(UART_MODULE_1), false},
    #endif
    #ifdef UART1_RX_RF5_RP17
    {GPIO_PF5, hal_ll_uart_module_num(UART_MODULE_1), false},
    #endif
    #ifdef UART1_RX_RG6_RP21
    {GPIO_PG6, hal_ll_uart_module_num(UART_MODULE_1), false},
    #endif
    #ifdef UART1_RX_RG7_RP26
    {GPIO_PG7, hal_ll_uart_module_num(UART_MODULE_1), false},
    #endif
    #ifdef UART1_RX_RG8_RP19
    {GPIO_PG8, hal_ll_uart_module_num(UART_MODULE_1), false},
    #endif
    #ifdef UART1_RX_RG9_RP27
    {GPIO_PG9, hal_ll_uart_module_num(UART_MODULE_1), false},
    #endif
    #ifdef UART2_RX_RB15_RP29
    {GPIO_PB15, hal_ll_uart_module_num(UART_MODULE_2), false},
    #endif
    #ifdef UART2_RX_RB2_RP13
    {GPIO_PB2, hal_ll_uart_module_num(UART_MODULE_2), false},
    #endif
    #ifdef UART2_RX_RB4_RP28
    {GPIO_PB4, hal_ll_uart_module_num(UART_MODULE_2), false},
    #endif
    #ifdef UART2_RX_RB5_RP18
    {GPIO_PB5, hal_ll_uart_module_num(UART_MODULE_2), false},
    #endif
    #ifdef UART2_RX_RC14_RPI37
    {GPIO_PC14, hal_ll_uart_module_num(UART_MODULE_2), false},
    #endif
    #ifdef UART2_RX_RD0_RP11
    {GPIO_PD0, hal_ll_uart_module_num(UART_MODULE_2), false},
    #endif
    #ifdef UART2_RX_RD1_RP24
    {GPIO_PD1, hal_ll_uart_module_num(UART_MODULE_2), false},
    #endif
    #ifdef UART2_RX_RD10_RP3
    {GPIO_PD10, hal_ll_uart_module_num(UART_MODULE_2), false},
    #endif
    #ifdef UART2_RX_RD11_RP12
    {GPIO_PD11, hal_ll_uart_module_num(UART_MODULE_2), false},
    #endif
    #ifdef UART2_RX_RD2_RP23
    {GPIO_PD2, hal_ll_uart_module_num(UART_MODULE_2), false},
    #endif
    #ifdef UART2_RX_RD3_RP22
    {GPIO_PD3, hal_ll_uart_module_num(UART_MODULE_2), false},
    #endif
    #ifdef UART2_RX_RD4_RP25
    {GPIO_PD4, hal_ll_uart_module_num(UART_MODULE_2), false},
    #endif
    #ifdef UART2_RX_RD5_RP20
    {GPIO_PD5, hal_ll_uart_module_num(UART_MODULE_2), false},
    #endif
    #ifdef UART2_RX_RD8_RP2
    {GPIO_PD8, hal_ll_uart_module_num(UART_MODULE_2), false},
    #endif
    #ifdef UART2_RX_RD9_RP4
    {GPIO_PD9, hal_ll_uart_module_num(UART_MODULE_2), false},
    #endif
    #ifdef UART2_RX_RF2_RP30
    {GPIO_PF2, hal_ll_uart_module_num(UART_MODULE_2), false},
    #endif
    #ifdef UART2_RX_RF3_RP16
    {GPIO_PF3, hal_ll_uart_module_num(UART_MODULE_2), false},
    #endif
    #ifdef UART2_RX_RF4_RP10
    {GPIO_PF4, hal_ll_uart_module_num(UART_MODULE_2), false},
    #endif
    #ifdef UART2_RX_RF5_RP17
    {GPIO_PF5, hal_ll_uart_module_num(UART_MODULE_2), false},
    #endif
    #ifdef UART2_RX_RG6_RP21
    {GPIO_PG6, hal_ll_uart_module_num(UART_MODULE_2), false},
    #endif
    #ifdef UART2_RX_RG7_RP26
    {GPIO_PG7, hal_ll_uart_module_num(UART_MODULE_2), false},
    #endif
    #ifdef UART2_RX_RG8_RP19
    {GPIO_PG8, hal_ll_uart_module_num(UART_MODULE_2), false},
    #endif
    #ifdef UART2_RX_RG9_RP27
    {GPIO_PG9, hal_ll_uart_module_num(UART_MODULE_2), false},
    #endif
    #ifdef UART3_RX_RB0_RP0
    {GPIO_PB0, hal_ll_uart_module_num(UART_MODULE_3), false},
    #endif
    #ifdef UART3_RX_RB1_RP1
    {GPIO_PB1, hal_ll_uart_module_num(UART_MODULE_3), false},
    #endif
    #ifdef UART3_RX_RB14_RP14
    {GPIO_PB14, hal_ll_uart_module_num(UART_MODULE_3), false},
    #endif
    #ifdef UART3_RX_RB15_RP29
    {GPIO_PB15, hal_ll_uart_module_num(UART_MODULE_3), false},
    #endif
    #ifdef UART3_RX_RB2_RP13
    {GPIO_PB2, hal_ll_uart_module_num(UART_MODULE_3), false},
    #endif
    #ifdef UART3_RX_RB4_RP28
    {GPIO_PB4, hal_ll_uart_module_num(UART_MODULE_3), false},
    #endif
    #ifdef UART3_RX_RB5_RP18
    {GPIO_PB5, hal_ll_uart_module_num(UART_MODULE_3), false},
    #endif
    #ifdef UART3_RX_RB6_RP6
    {GPIO_PB6, hal_ll_uart_module_num(UART_MODULE_3), false},
    #endif
    #ifdef UART3_RX_RB7_RP7
    {GPIO_PB7, hal_ll_uart_module_num(UART_MODULE_3), false},
    #endif
    #ifdef UART3_RX_RB8_RP8
    {GPIO_PB8, hal_ll_uart_module_num(UART_MODULE_3), false},
    #endif
    #ifdef UART3_RX_RB9_RP9
    {GPIO_PB9, hal_ll_uart_module_num(UART_MODULE_3), false},
    #endif
    #ifdef UART3_RX_RC14_RPI37
    {GPIO_PC14, hal_ll_uart_module_num(UART_MODULE_3), false},
    #endif
    #ifdef UART3_RX_RD0_RP11
    {GPIO_PD0, hal_ll_uart_module_num(UART_MODULE_3), false},
    #endif
    #ifdef UART3_RX_RD1_RP24
    {GPIO_PD1, hal_ll_uart_module_num(UART_MODULE_3), false},
    #endif
    #ifdef UART3_RX_RD10_RP3
    {GPIO_PD10, hal_ll_uart_module_num(UART_MODULE_3), false},
    #endif
    #ifdef UART3_RX_RD11_RP12
    {GPIO_PD11, hal_ll_uart_module_num(UART_MODULE_3), false},
    #endif
    #ifdef UART3_RX_RD2_RP23
    {GPIO_PD2, hal_ll_uart_module_num(UART_MODULE_3), false},
    #endif
    #ifdef UART3_RX_RD3_RP22
    {GPIO_PD3, hal_ll_uart_module_num(UART_MODULE_3), false},
    #endif
    #ifdef UART3_RX_RD4_RP25
    {GPIO_PD4, hal_ll_uart_module_num(UART_MODULE_3), false},
    #endif
    #ifdef UART3_RX_RD5_RP20
    {GPIO_PD5, hal_ll_uart_module_num(UART_MODULE_3), false},
    #endif
    #ifdef UART3_RX_RD8_RP2
    {GPIO_PD8, hal_ll_uart_module_num(UART_MODULE_3), false},
    #endif
    #ifdef UART3_RX_RD9_RP4
    {GPIO_PD9, hal_ll_uart_module_num(UART_MODULE_3), false},
    #endif
    #ifdef UART3_RX_RF2_RP30
    {GPIO_PF2, hal_ll_uart_module_num(UART_MODULE_3), false},
    #endif
    #ifdef UART3_RX_RF3_RP16
    {GPIO_PF3, hal_ll_uart_module_num(UART_MODULE_3), false},
    #endif
    #ifdef UART3_RX_RF4_RP10
    {GPIO_PF4, hal_ll_uart_module_num(UART_MODULE_3), false},
    #endif
    #ifdef UART3_RX_RF5_RP17
    {GPIO_PF5, hal_ll_uart_module_num(UART_MODULE_3), false},
    #endif
    #ifdef UART3_RX_RG6_RP21
    {GPIO_PG6, hal_ll_uart_module_num(UART_MODULE_3), false},
    #endif
    #ifdef UART3_RX_RG7_RP26
    {GPIO_PG7, hal_ll_uart_module_num(UART_MODULE_3), false},
    #endif
    #ifdef UART3_RX_RG8_RP19
    {GPIO_PG8, hal_ll_uart_module_num(UART_MODULE_3), false},
    #endif
    #ifdef UART3_RX_RG9_RP27
    {GPIO_PG9, hal_ll_uart_module_num(UART_MODULE_3), false},
    #endif
    #ifdef UART4_RX_RB0_RP0
    {GPIO_PB0, hal_ll_uart_module_num(UART_MODULE_4), false},
    #endif
    #ifdef UART4_RX_RB1_RP1
    {GPIO_PB1, hal_ll_uart_module_num(UART_MODULE_4), false},
    #endif
    #ifdef UART4_RX_RB14_RP14
    {GPIO_PB14, hal_ll_uart_module_num(UART_MODULE_4), false},
    #endif
    #ifdef UART4_RX_RB15_RP29
    {GPIO_PB15, hal_ll_uart_module_num(UART_MODULE_4), false},
    #endif
    #ifdef UART4_RX_RB2_RP13
    {GPIO_PB2, hal_ll_uart_module_num(UART_MODULE_4), false},
    #endif
    #ifdef UART4_RX_RB4_RP28
    {GPIO_PB4, hal_ll_uart_module_num(UART_MODULE_4), false},
    #endif
    #ifdef UART4_RX_RB5_RP18
    {GPIO_PB5, hal_ll_uart_module_num(UART_MODULE_4), false},
    #endif
    #ifdef UART4_RX_RB6_RP6
    {GPIO_PB6, hal_ll_uart_module_num(UART_MODULE_4), false},
    #endif
    #ifdef UART4_RX_RB7_RP7
    {GPIO_PB7, hal_ll_uart_module_num(UART_MODULE_4), false},
    #endif
    #ifdef UART4_RX_RB8_RP8
    {GPIO_PB8, hal_ll_uart_module_num(UART_MODULE_4), false},
    #endif
    #ifdef UART4_RX_RB9_RP9
    {GPIO_PB9, hal_ll_uart_module_num(UART_MODULE_4), false},
    #endif
    #ifdef UART4_RX_RC14_RPI37
    {GPIO_PC14, hal_ll_uart_module_num(UART_MODULE_4), false},
    #endif
    #ifdef UART4_RX_RD0_RP11
    {GPIO_PD0, hal_ll_uart_module_num(UART_MODULE_4), false},
    #endif
    #ifdef UART4_RX_RD1_RP24
    {GPIO_PD1, hal_ll_uart_module_num(UART_MODULE_4), false},
    #endif
    #ifdef UART4_RX_RD10_RP3
    {GPIO_PD10, hal_ll_uart_module_num(UART_MODULE_4), false},
    #endif
    #ifdef UART4_RX_RD11_RP12
    {GPIO_PD11, hal_ll_uart_module_num(UART_MODULE_4), false},
    #endif
    #ifdef UART4_RX_RD2_RP23
    {GPIO_PD2, hal_ll_uart_module_num(UART_MODULE_4), false},
    #endif
    #ifdef UART4_RX_RD3_RP22
    {GPIO_PD3, hal_ll_uart_module_num(UART_MODULE_4), false},
    #endif
    #ifdef UART4_RX_RD4_RP25
    {GPIO_PD4, hal_ll_uart_module_num(UART_MODULE_4), false},
    #endif
    #ifdef UART4_RX_RD5_RP20
    {GPIO_PD5, hal_ll_uart_module_num(UART_MODULE_4), false},
    #endif
    #ifdef UART4_RX_RD8_RP2
    {GPIO_PD8, hal_ll_uart_module_num(UART_MODULE_4), false},
    #endif
    #ifdef UART4_RX_RD9_RP4
    {GPIO_PD9, hal_ll_uart_module_num(UART_MODULE_4), false},
    #endif
    #ifdef UART4_RX_RF2_RP30
    {GPIO_PF2, hal_ll_uart_module_num(UART_MODULE_4), false},
    #endif
    #ifdef UART4_RX_RF3_RP16
    {GPIO_PF3, hal_ll_uart_module_num(UART_MODULE_4), false},
    #endif
    #ifdef UART4_RX_RF4_RP10
    {GPIO_PF4, hal_ll_uart_module_num(UART_MODULE_4), false},
    #endif
    #ifdef UART4_RX_RF5_RP17
    {GPIO_PF5, hal_ll_uart_module_num(UART_MODULE_4), false},
    #endif
    #ifdef UART4_RX_RG6_RP21
    {GPIO_PG6, hal_ll_uart_module_num(UART_MODULE_4), false},
    #endif
    #ifdef UART4_RX_RG7_RP26
    {GPIO_PG7, hal_ll_uart_module_num(UART_MODULE_4), false},
    #endif
    #ifdef UART4_RX_RG8_RP19
    {GPIO_PG8, hal_ll_uart_module_num(UART_MODULE_4), false},
    #endif
    #ifdef UART4_RX_RG9_RP27
    {GPIO_PG9, hal_ll_uart_module_num(UART_MODULE_4), false},
    #endif
    #ifdef UART5_RX_RD6
    {GPIO_PD6, hal_ll_uart_module_num(UART_MODULE_5), false},
    #endif
    #ifdef UART6_RX_RB12
    {GPIO_PB12, hal_ll_uart_module_num(UART_MODULE_6), false},
    #endif
    #ifdef UART1_RX_RA14_RPI36
    {GPIO_PA14, hal_ll_uart_module_num(UART_MODULE_1), false},
    #endif
    #ifdef UART1_RX_RA15_RPI35
    {GPIO_PA15, hal_ll_uart_module_num(UART_MODULE_1), false},
    #endif
    #ifdef UART1_RX_RC1_RPI38
    {GPIO_PC1, hal_ll_uart_module_num(UART_MODULE_1), false},
    #endif
    #ifdef UART1_RX_RC2_RPI39
    {GPIO_PC2, hal_ll_uart_module_num(UART_MODULE_1), false},
    #endif
    #ifdef UART1_RX_RC3_RPI40
    {GPIO_PC3, hal_ll_uart_module_num(UART_MODULE_1), false},
    #endif
    #ifdef UART1_RX_RC4_RPI41
    {GPIO_PC4, hal_ll_uart_module_num(UART_MODULE_1), false},
    #endif
    #ifdef UART1_RX_RD12_RPI42
    {GPIO_PD12, hal_ll_uart_module_num(UART_MODULE_1), false},
    #endif
    #ifdef UART1_RX_RD14_RPI43
    {GPIO_PD14, hal_ll_uart_module_num(UART_MODULE_1), false},
    #endif
    #ifdef UART1_RX_RD15_RP5
    {GPIO_PD15, hal_ll_uart_module_num(UART_MODULE_1), false},
    #endif
    #ifdef UART1_RX_RE8_RPI33
    {GPIO_PE8, hal_ll_uart_module_num(UART_MODULE_1), false},
    #endif
    #ifdef UART1_RX_RE9_RPI34
    {GPIO_PE9, hal_ll_uart_module_num(UART_MODULE_1), false},
    #endif
    #ifdef UART1_RX_RF12_RPI32
    {GPIO_PF12, hal_ll_uart_module_num(UART_MODULE_1), false},
    #endif
    #ifdef UART1_RX_RF13_RP31
    {GPIO_PF13, hal_ll_uart_module_num(UART_MODULE_1), false},
    #endif
    #ifdef UART1_RX_RF8_RP15
    {GPIO_PF8, hal_ll_uart_module_num(UART_MODULE_1), false},
    #endif
    #ifdef UART2_RX_RA14_RPI36
    {GPIO_PA14, hal_ll_uart_module_num(UART_MODULE_2), false},
    #endif
    #ifdef UART2_RX_RA15_RPI35
    {GPIO_PA15, hal_ll_uart_module_num(UART_MODULE_2), false},
    #endif
    #ifdef UART2_RX_RC1_RPI38
    {GPIO_PC1, hal_ll_uart_module_num(UART_MODULE_2), false},
    #endif
    #ifdef UART2_RX_RC2_RPI39
    {GPIO_PC2, hal_ll_uart_module_num(UART_MODULE_2), false},
    #endif
    #ifdef UART2_RX_RC3_RPI40
    {GPIO_PC3, hal_ll_uart_module_num(UART_MODULE_2), false},
    #endif
    #ifdef UART2_RX_RC4_RPI41
    {GPIO_PC4, hal_ll_uart_module_num(UART_MODULE_2), false},
    #endif
    #ifdef UART2_RX_RD12_RPI42
    {GPIO_PD12, hal_ll_uart_module_num(UART_MODULE_2), false},
    #endif
    #ifdef UART2_RX_RD14_RPI43
    {GPIO_PD14, hal_ll_uart_module_num(UART_MODULE_2), false},
    #endif
    #ifdef UART2_RX_RD15_RP5
    {GPIO_PD15, hal_ll_uart_module_num(UART_MODULE_2), false},
    #endif
    #ifdef UART2_RX_RE8_RPI33
    {GPIO_PE8, hal_ll_uart_module_num(UART_MODULE_2), false},
    #endif
    #ifdef UART2_RX_RE9_RPI34
    {GPIO_PE9, hal_ll_uart_module_num(UART_MODULE_2), false},
    #endif
    #ifdef UART2_RX_RF12_RPI32
    {GPIO_PF12, hal_ll_uart_module_num(UART_MODULE_2), false},
    #endif
    #ifdef UART2_RX_RF13_RP31
    {GPIO_PF13, hal_ll_uart_module_num(UART_MODULE_2), false},
    #endif
    #ifdef UART2_RX_RF8_RP15
    {GPIO_PF8, hal_ll_uart_module_num(UART_MODULE_2), false},
    #endif
    #ifdef UART3_RX_RA14_RPI36
    {GPIO_PA14, hal_ll_uart_module_num(UART_MODULE_3), false},
    #endif
    #ifdef UART3_RX_RA15_RPI35
    {GPIO_PA15, hal_ll_uart_module_num(UART_MODULE_3), false},
    #endif
    #ifdef UART3_RX_RC1_RPI38
    {GPIO_PC1, hal_ll_uart_module_num(UART_MODULE_3), false},
    #endif
    #ifdef UART3_RX_RC2_RPI39
    {GPIO_PC2, hal_ll_uart_module_num(UART_MODULE_3), false},
    #endif
    #ifdef UART3_RX_RC3_RPI40
    {GPIO_PC3, hal_ll_uart_module_num(UART_MODULE_3), false},
    #endif
    #ifdef UART3_RX_RC4_RPI41
    {GPIO_PC4, hal_ll_uart_module_num(UART_MODULE_3), false},
    #endif
    #ifdef UART3_RX_RD12_RPI42
    {GPIO_PD12, hal_ll_uart_module_num(UART_MODULE_3), false},
    #endif
    #ifdef UART3_RX_RD14_RPI43
    {GPIO_PD14, hal_ll_uart_module_num(UART_MODULE_3), false},
    #endif
    #ifdef UART3_RX_RD15_RP5
    {GPIO_PD15, hal_ll_uart_module_num(UART_MODULE_3), false},
    #endif
    #ifdef UART3_RX_RE8_RPI33
    {GPIO_PE8, hal_ll_uart_module_num(UART_MODULE_3), false},
    #endif
    #ifdef UART3_RX_RE9_RPI34
    {GPIO_PE9, hal_ll_uart_module_num(UART_MODULE_3), false},
    #endif
    #ifdef UART3_RX_RF12_RPI32
    {GPIO_PF12, hal_ll_uart_module_num(UART_MODULE_3), false},
    #endif
    #ifdef UART3_RX_RF13_RP31
    {GPIO_PF13, hal_ll_uart_module_num(UART_MODULE_3), false},
    #endif
    #ifdef UART3_RX_RF8_RP15
    {GPIO_PF8, hal_ll_uart_module_num(UART_MODULE_3), false},
    #endif
    #ifdef UART4_RX_RA14_RPI36
    {GPIO_PA14, hal_ll_uart_module_num(UART_MODULE_4), false},
    #endif
    #ifdef UART4_RX_RA15_RPI35
    {GPIO_PA15, hal_ll_uart_module_num(UART_MODULE_4), false},
    #endif
    #ifdef UART4_RX_RC1_RPI38
    {GPIO_PC1, hal_ll_uart_module_num(UART_MODULE_4), false},
    #endif
    #ifdef UART4_RX_RC2_RPI39
    {GPIO_PC2, hal_ll_uart_module_num(UART_MODULE_4), false},
    #endif
    #ifdef UART4_RX_RC3_RPI40
    {GPIO_PC3, hal_ll_uart_module_num(UART_MODULE_4), false},
    #endif
    #ifdef UART4_RX_RC4_RPI41
    {GPIO_PC4, hal_ll_uart_module_num(UART_MODULE_4), false},
    #endif
    #ifdef UART4_RX_RD12_RPI42
    {GPIO_PD12, hal_ll_uart_module_num(UART_MODULE_4), false},
    #endif
    #ifdef UART4_RX_RD14_RPI43
    {GPIO_PD14, hal_ll_uart_module_num(UART_MODULE_4), false},
    #endif
    #ifdef UART4_RX_RD15_RP5
    {GPIO_PD15, hal_ll_uart_module_num(UART_MODULE_4), false},
    #endif
    #ifdef UART4_RX_RE8_RPI33
    {GPIO_PE8, hal_ll_uart_module_num(UART_MODULE_4), false},
    #endif
    #ifdef UART4_RX_RE9_RPI34
    {GPIO_PE9, hal_ll_uart_module_num(UART_MODULE_4), false},
    #endif
    #ifdef UART4_RX_RF12_RPI32
    {GPIO_PF12, hal_ll_uart_module_num(UART_MODULE_4), false},
    #endif
    #ifdef UART4_RX_RF13_RP31
    {GPIO_PF13, hal_ll_uart_module_num(UART_MODULE_4), false},
    #endif
    #ifdef UART4_RX_RF8_RP15
    {GPIO_PF8, hal_ll_uart_module_num(UART_MODULE_4), false},
    #endif
    #ifdef UART1_RX_RF6_RPI45
    {GPIO_PF6, hal_ll_uart_module_num(UART_MODULE_1), false},
    #endif
    #ifdef UART2_RX_RF6_RPI45
    {GPIO_PF6, hal_ll_uart_module_num(UART_MODULE_2), false},
    #endif
    #ifdef UART3_RX_RF6_RPI45
    {GPIO_PF6, hal_ll_uart_module_num(UART_MODULE_3), false},
    #endif
    #ifdef UART4_RX_RF6_RPI45
    {GPIO_PF6, hal_ll_uart_module_num(UART_MODULE_4), false},
    #endif
    #ifdef UART1_RX_RF7_RPI44
    {GPIO_PF7, hal_ll_uart_module_num(UART_MODULE_1), false},
    #endif
    #ifdef UART2_RX_RF7_RPI44
    {GPIO_PF7, hal_ll_uart_module_num(UART_MODULE_2), false},
    #endif
    #ifdef UART3_RX_RF7_RPI44
    {GPIO_PF7, hal_ll_uart_module_num(UART_MODULE_3), false},
    #endif
    #ifdef UART4_RX_RF7_RPI44
    {GPIO_PF7, hal_ll_uart_module_num(UART_MODULE_4), false},
    #endif
    #ifdef UART1_RX_RB4_RPI4
    {GPIO_PB4, hal_ll_uart_module_num(UART_MODULE_1), false},
    #endif
    #ifdef UART2_RX_RB4_RPI4
    {GPIO_PB4, hal_ll_uart_module_num(UART_MODULE_2), false},
    #endif
    #ifdef UART3_RX_RB10_RP10
    {GPIO_PB10, hal_ll_uart_module_num(UART_MODULE_3), false},
    #endif
    #ifdef UART3_RX_RB11_RP11
    {GPIO_PB11, hal_ll_uart_module_num(UART_MODULE_3), false},
    #endif
    #ifdef UART3_RX_RB12_RP12
    {GPIO_PB12, hal_ll_uart_module_num(UART_MODULE_3), false},
    #endif
    #ifdef UART3_RX_RB13_RP13
    {GPIO_PB13, hal_ll_uart_module_num(UART_MODULE_3), false},
    #endif
    #ifdef UART3_RX_RB15_RP15
    {GPIO_PB15, hal_ll_uart_module_num(UART_MODULE_3), false},
    #endif
    #ifdef UART3_RX_RB2_RP2
    {GPIO_PB2, hal_ll_uart_module_num(UART_MODULE_3), false},
    #endif
    #ifdef UART3_RX_RB3_RP3
    {GPIO_PB3, hal_ll_uart_module_num(UART_MODULE_3), false},
    #endif
    #ifdef UART3_RX_RB4_RPI4
    {GPIO_PB4, hal_ll_uart_module_num(UART_MODULE_3), false},
    #endif
    #ifdef UART3_RX_RB5_RP5
    {GPIO_PB5, hal_ll_uart_module_num(UART_MODULE_3), false},
    #endif
    #ifdef UART4_RX_RB10_RP10
    {GPIO_PB10, hal_ll_uart_module_num(UART_MODULE_4), false},
    #endif
    #ifdef UART4_RX_RB11_RP11
    {GPIO_PB11, hal_ll_uart_module_num(UART_MODULE_4), false},
    #endif
    #ifdef UART4_RX_RB12_RP12
    {GPIO_PB12, hal_ll_uart_module_num(UART_MODULE_4), false},
    #endif
    #ifdef UART4_RX_RB13_RP13
    {GPIO_PB13, hal_ll_uart_module_num(UART_MODULE_4), false},
    #endif
    #ifdef UART4_RX_RB15_RP15
    {GPIO_PB15, hal_ll_uart_module_num(UART_MODULE_4), false},
    #endif
    #ifdef UART4_RX_RB2_RP2
    {GPIO_PB2, hal_ll_uart_module_num(UART_MODULE_4), false},
    #endif
    #ifdef UART4_RX_RB3_RP3
    {GPIO_PB3, hal_ll_uart_module_num(UART_MODULE_4), false},
    #endif
    #ifdef UART4_RX_RB4_RPI4
    {GPIO_PB4, hal_ll_uart_module_num(UART_MODULE_4), false},
    #endif
    #ifdef UART4_RX_RB5_RP5
    {GPIO_PB5, hal_ll_uart_module_num(UART_MODULE_4), false},
    #endif
    #ifdef UART3_RX_RC0_RP16
    {GPIO_PC0, hal_ll_uart_module_num(UART_MODULE_3), false},
    #endif
    #ifdef UART3_RX_RC1_RP17
    {GPIO_PC1, hal_ll_uart_module_num(UART_MODULE_3), false},
    #endif
    #ifdef UART3_RX_RC2_RP18
    {GPIO_PC2, hal_ll_uart_module_num(UART_MODULE_3), false},
    #endif
    #ifdef UART3_RX_RC3_RP19
    {GPIO_PC3, hal_ll_uart_module_num(UART_MODULE_3), false},
    #endif
    #ifdef UART3_RX_RC4_RP20
    {GPIO_PC4, hal_ll_uart_module_num(UART_MODULE_3), false},
    #endif
    #ifdef UART3_RX_RC5_RP21
    {GPIO_PC5, hal_ll_uart_module_num(UART_MODULE_3), false},
    #endif
    #ifdef UART3_RX_RC6_RP22
    {GPIO_PC6, hal_ll_uart_module_num(UART_MODULE_3), false},
    #endif
    #ifdef UART3_RX_RC7_RP23
    {GPIO_PC7, hal_ll_uart_module_num(UART_MODULE_3), false},
    #endif
    #ifdef UART3_RX_RC8_RP24
    {GPIO_PC8, hal_ll_uart_module_num(UART_MODULE_3), false},
    #endif
    #ifdef UART3_RX_RC9_RP25
    {GPIO_PC9, hal_ll_uart_module_num(UART_MODULE_3), false},
    #endif
    #ifdef UART4_RX_RC0_RP16
    {GPIO_PC0, hal_ll_uart_module_num(UART_MODULE_4), false},
    #endif
    #ifdef UART4_RX_RC1_RP17
    {GPIO_PC1, hal_ll_uart_module_num(UART_MODULE_4), false},
    #endif
    #ifdef UART4_RX_RC2_RP18
    {GPIO_PC2, hal_ll_uart_module_num(UART_MODULE_4), false},
    #endif
    #ifdef UART4_RX_RC3_RP19
    {GPIO_PC3, hal_ll_uart_module_num(UART_MODULE_4), false},
    #endif
    #ifdef UART4_RX_RC4_RP20
    {GPIO_PC4, hal_ll_uart_module_num(UART_MODULE_4), false},
    #endif
    #ifdef UART4_RX_RC5_RP21
    {GPIO_PC5, hal_ll_uart_module_num(UART_MODULE_4), false},
    #endif
    #ifdef UART4_RX_RC6_RP22
    {GPIO_PC6, hal_ll_uart_module_num(UART_MODULE_4), false},
    #endif
    #ifdef UART4_RX_RC7_RP23
    {GPIO_PC7, hal_ll_uart_module_num(UART_MODULE_4), false},
    #endif
    #ifdef UART4_RX_RC8_RP24
    {GPIO_PC8, hal_ll_uart_module_num(UART_MODULE_4), false},
    #endif
    #ifdef UART4_RX_RC9_RP25
    {GPIO_PC9, hal_ll_uart_module_num(UART_MODULE_4), false},
    #endif
    #ifdef UART1_RX_RA0_RP26
    {GPIO_PA0, hal_ll_uart_module_num(UART_MODULE_1), false},
    #endif
    #ifdef UART1_RX_RA1_RP27
    {GPIO_PA1, hal_ll_uart_module_num(UART_MODULE_1), false},
    #endif
    #ifdef UART2_RX_RA0_RP26
    {GPIO_PA0, hal_ll_uart_module_num(UART_MODULE_2), false},
    #endif
    #ifdef UART2_RX_RA1_RP27
    {GPIO_PA1, hal_ll_uart_module_num(UART_MODULE_2), false},
    #endif
    #ifdef UART1_RX_RA10_RP28
    {GPIO_PA10, hal_ll_uart_module_num(UART_MODULE_1), false},
    #endif
    #ifdef UART2_RX_RA10_RP28
    {GPIO_PA10, hal_ll_uart_module_num(UART_MODULE_2), false},
    #endif
    #ifdef UART1_RX_RA11_RPIN29
    {GPIO_PA11, hal_ll_uart_module_num(UART_MODULE_1), false},
    #endif
    #ifdef UART1_RX_RA12_RPIN30
    {GPIO_PA12, hal_ll_uart_module_num(UART_MODULE_1), false},
    #endif
    #ifdef UART1_RX_RA13_RPIN31
    {GPIO_PA13, hal_ll_uart_module_num(UART_MODULE_1), false},
    #endif
    #ifdef UART1_RX_RA14_RPIN32
    {GPIO_PA14, hal_ll_uart_module_num(UART_MODULE_1), false},
    #endif
    #ifdef UART2_RX_RA11_RPIN29
    {GPIO_PA11, hal_ll_uart_module_num(UART_MODULE_2), false},
    #endif
    #ifdef UART2_RX_RA12_RPIN30
    {GPIO_PA12, hal_ll_uart_module_num(UART_MODULE_2), false},
    #endif
    #ifdef UART2_RX_RA13_RPIN31
    {GPIO_PA13, hal_ll_uart_module_num(UART_MODULE_2), false},
    #endif
    #ifdef UART2_RX_RA14_RPIN32
    {GPIO_PA14, hal_ll_uart_module_num(UART_MODULE_2), false},
    #endif
    #ifdef UART1_RX_RA0_RP5
    {GPIO_PA0, hal_ll_uart_module_num(UART_MODULE_1), false},
    #endif
    #ifdef UART1_RX_RA1_RP6
    {GPIO_PA1, hal_ll_uart_module_num(UART_MODULE_1), false},
    #endif
    #ifdef UART2_RX_RA0_RP5
    {GPIO_PA0, hal_ll_uart_module_num(UART_MODULE_2), false},
    #endif
    #ifdef UART2_RX_RA1_RP6
    {GPIO_PA1, hal_ll_uart_module_num(UART_MODULE_2), false},
    #endif
    #ifdef UART3_RX_RA0_RP5
    {GPIO_PA0, hal_ll_uart_module_num(UART_MODULE_3), false},
    #endif
    #ifdef UART3_RX_RA1_RP6
    {GPIO_PA1, hal_ll_uart_module_num(UART_MODULE_3), false},
    #endif
    #ifdef UART4_RX_RA0_RP5
    {GPIO_PA0, hal_ll_uart_module_num(UART_MODULE_4), false},
    #endif
    #ifdef UART4_RX_RA1_RP6
    {GPIO_PA1, hal_ll_uart_module_num(UART_MODULE_4), false},
    #endif
    { HAL_LL_PIN_NC, HAL_LL_MODULE_ERROR, false }
    //------------ END RX
};

#ifdef __cplusplus
}
#endif

#endif // _HAL_LL_UART_PIN_MAP_H_
// ------------------------------------------------------------------------- END
