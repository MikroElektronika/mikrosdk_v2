/****************************************************************************
**
** Copyright (C) 2024 MikroElektronika d.o.o.
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
    {PB4, hal_ll_uart_module_num(UART_MODULE_1), false},
    #endif
    #ifdef UART1_TX_RC13_ALT
    {PC13, hal_ll_uart_module_num(UART_MODULE_1), true},
    #endif
    #ifdef UART1_TX_RF3
    {PF3, hal_ll_uart_module_num(UART_MODULE_1), false},
    #endif
    #ifdef UART2_TX_RF5
    {PF5, hal_ll_uart_module_num(UART_MODULE_2), false},
    #endif
    #ifdef UART1_TX_RA4_RP20
    {PA4, hal_ll_uart_module_num(UART_MODULE_1), false},
    #endif
    #ifdef UART1_TX_RB10_RP42
    {PB10, hal_ll_uart_module_num(UART_MODULE_1), false},
    #endif
    #ifdef UART1_TX_RB11_RP43
    {PB11, hal_ll_uart_module_num(UART_MODULE_1), false},
    #endif
    #ifdef UART1_TX_RB3_RP35
    {PB3, hal_ll_uart_module_num(UART_MODULE_1), false},
    #endif
    #ifdef UART1_TX_RB4_RP36
    {PB4, hal_ll_uart_module_num(UART_MODULE_1), false},
    #endif
    #ifdef UART1_TX_RB5_RP37
    {PB5, hal_ll_uart_module_num(UART_MODULE_1), false},
    #endif
    #ifdef UART1_TX_RB6_RP38
    {PB6, hal_ll_uart_module_num(UART_MODULE_1), false},
    #endif
    #ifdef UART1_TX_RB7_RP39
    {PB7, hal_ll_uart_module_num(UART_MODULE_1), false},
    #endif
    #ifdef UART1_TX_RB8_RP40
    {PB8, hal_ll_uart_module_num(UART_MODULE_1), false},
    #endif
    #ifdef UART1_TX_RB9_RP41
    {PB9, hal_ll_uart_module_num(UART_MODULE_1), false},
    #endif
    #ifdef UART1_TX_RC0_RP48
    {PC0, hal_ll_uart_module_num(UART_MODULE_1), false},
    #endif
    #ifdef UART1_TX_RC1_RP49
    {PC1, hal_ll_uart_module_num(UART_MODULE_1), false},
    #endif
    #ifdef UART1_TX_RC6_RP54
    {PC6, hal_ll_uart_module_num(UART_MODULE_1), false},
    #endif
    #ifdef UART1_TX_RC7_RP55
    {PC7, hal_ll_uart_module_num(UART_MODULE_1), false},
    #endif
    #ifdef UART1_TX_RC8_RP56
    {PC8, hal_ll_uart_module_num(UART_MODULE_1), false},
    #endif
    #ifdef UART1_TX_RC9_RP57
    {PC9, hal_ll_uart_module_num(UART_MODULE_1), false},
    #endif
    #ifdef UART2_TX_RA4_RP20
    {PA4, hal_ll_uart_module_num(UART_MODULE_2), false},
    #endif
    #ifdef UART2_TX_RB10_RP42
    {PB10, hal_ll_uart_module_num(UART_MODULE_2), false},
    #endif
    #ifdef UART2_TX_RB11_RP43
    {PB11, hal_ll_uart_module_num(UART_MODULE_2), false},
    #endif
    #ifdef UART2_TX_RB3_RP35
    {PB3, hal_ll_uart_module_num(UART_MODULE_2), false},
    #endif
    #ifdef UART2_TX_RB4_RP36
    {PB4, hal_ll_uart_module_num(UART_MODULE_2), false},
    #endif
    #ifdef UART2_TX_RB5_RP37
    {PB5, hal_ll_uart_module_num(UART_MODULE_2), false},
    #endif
    #ifdef UART2_TX_RB6_RP38
    {PB6, hal_ll_uart_module_num(UART_MODULE_2), false},
    #endif
    #ifdef UART2_TX_RB7_RP39
    {PB7, hal_ll_uart_module_num(UART_MODULE_2), false},
    #endif
    #ifdef UART2_TX_RB8_RP40
    {PB8, hal_ll_uart_module_num(UART_MODULE_2), false},
    #endif
    #ifdef UART2_TX_RB9_RP41
    {PB9, hal_ll_uart_module_num(UART_MODULE_2), false},
    #endif
    #ifdef UART2_TX_RC0_RP48
    {PC0, hal_ll_uart_module_num(UART_MODULE_2), false},
    #endif
    #ifdef UART2_TX_RC1_RP49
    {PC1, hal_ll_uart_module_num(UART_MODULE_2), false},
    #endif
    #ifdef UART2_TX_RC6_RP54
    {PC6, hal_ll_uart_module_num(UART_MODULE_2), false},
    #endif
    #ifdef UART2_TX_RC7_RP55
    {PC7, hal_ll_uart_module_num(UART_MODULE_2), false},
    #endif
    #ifdef UART2_TX_RC8_RP56
    {PC8, hal_ll_uart_module_num(UART_MODULE_2), false},
    #endif
    #ifdef UART2_TX_RC9_RP57
    {PC9, hal_ll_uart_module_num(UART_MODULE_2), false},
    #endif
    #ifdef UART3_TX_RA4_RP20
    {PA4, hal_ll_uart_module_num(UART_MODULE_3), false},
    #endif
    #ifdef UART3_TX_RB10_RP42
    {PB10, hal_ll_uart_module_num(UART_MODULE_3), false},
    #endif
    #ifdef UART3_TX_RB11_RP43
    {PB11, hal_ll_uart_module_num(UART_MODULE_3), false},
    #endif
    #ifdef UART3_TX_RB3_RP35
    {PB3, hal_ll_uart_module_num(UART_MODULE_3), false},
    #endif
    #ifdef UART3_TX_RB4_RP36
    {PB4, hal_ll_uart_module_num(UART_MODULE_3), false},
    #endif
    #ifdef UART3_TX_RB5_RP37
    {PB5, hal_ll_uart_module_num(UART_MODULE_3), false},
    #endif
    #ifdef UART3_TX_RB6_RP38
    {PB6, hal_ll_uart_module_num(UART_MODULE_3), false},
    #endif
    #ifdef UART3_TX_RB7_RP39
    {PB7, hal_ll_uart_module_num(UART_MODULE_3), false},
    #endif
    #ifdef UART3_TX_RB8_RP40
    {PB8, hal_ll_uart_module_num(UART_MODULE_3), false},
    #endif
    #ifdef UART3_TX_RB9_RP41
    {PB9, hal_ll_uart_module_num(UART_MODULE_3), false},
    #endif
    #ifdef UART3_TX_RC0_RP48
    {PC0, hal_ll_uart_module_num(UART_MODULE_3), false},
    #endif
    #ifdef UART3_TX_RC1_RP49
    {PC1, hal_ll_uart_module_num(UART_MODULE_3), false},
    #endif
    #ifdef UART3_TX_RC6_RP54
    {PC6, hal_ll_uart_module_num(UART_MODULE_3), false},
    #endif
    #ifdef UART3_TX_RC7_RP55
    {PC7, hal_ll_uart_module_num(UART_MODULE_3), false},
    #endif
    #ifdef UART3_TX_RC8_RP56
    {PC8, hal_ll_uart_module_num(UART_MODULE_3), false},
    #endif
    #ifdef UART3_TX_RC9_RP57
    {PC9, hal_ll_uart_module_num(UART_MODULE_3), false},
    #endif
    #ifdef UART4_TX_RA4_RP20
    {PA4, hal_ll_uart_module_num(UART_MODULE_4), false},
    #endif
    #ifdef UART4_TX_RB10_RP42
    {PB10, hal_ll_uart_module_num(UART_MODULE_4), false},
    #endif
    #ifdef UART4_TX_RB11_RP43
    {PB11, hal_ll_uart_module_num(UART_MODULE_4), false},
    #endif
    #ifdef UART4_TX_RB3_RP35
    {PB3, hal_ll_uart_module_num(UART_MODULE_4), false},
    #endif
    #ifdef UART4_TX_RB4_RP36
    {PB4, hal_ll_uart_module_num(UART_MODULE_4), false},
    #endif
    #ifdef UART4_TX_RB5_RP37
    {PB5, hal_ll_uart_module_num(UART_MODULE_4), false},
    #endif
    #ifdef UART4_TX_RB6_RP38
    {PB6, hal_ll_uart_module_num(UART_MODULE_4), false},
    #endif
    #ifdef UART4_TX_RB7_RP39
    {PB7, hal_ll_uart_module_num(UART_MODULE_4), false},
    #endif
    #ifdef UART4_TX_RB8_RP40
    {PB8, hal_ll_uart_module_num(UART_MODULE_4), false},
    #endif
    #ifdef UART4_TX_RB9_RP41
    {PB9, hal_ll_uart_module_num(UART_MODULE_4), false},
    #endif
    #ifdef UART4_TX_RC0_RP48
    {PC0, hal_ll_uart_module_num(UART_MODULE_4), false},
    #endif
    #ifdef UART4_TX_RC1_RP49
    {PC1, hal_ll_uart_module_num(UART_MODULE_4), false},
    #endif
    #ifdef UART4_TX_RC6_RP54
    {PC6, hal_ll_uart_module_num(UART_MODULE_4), false},
    #endif
    #ifdef UART4_TX_RC7_RP55
    {PC7, hal_ll_uart_module_num(UART_MODULE_4), false},
    #endif
    #ifdef UART4_TX_RC8_RP56
    {PC8, hal_ll_uart_module_num(UART_MODULE_4), false},
    #endif
    #ifdef UART4_TX_RC9_RP57
    {PC9, hal_ll_uart_module_num(UART_MODULE_4), false},
    #endif
    #ifdef UART1_TX_RD5_RP69
    {PD5, hal_ll_uart_module_num(UART_MODULE_1), false},
    #endif
    #ifdef UART1_TX_RD6_RP70
    {PD6, hal_ll_uart_module_num(UART_MODULE_1), false},
    #endif
    #ifdef UART1_TX_RF1_RP97
    {PF1, hal_ll_uart_module_num(UART_MODULE_1), false},
    #endif
    #ifdef UART1_TX_RG6_RP118
    {PG6, hal_ll_uart_module_num(UART_MODULE_1), false},
    #endif
    #ifdef UART1_TX_RG8_RP120
    {PG8, hal_ll_uart_module_num(UART_MODULE_1), false},
    #endif
    #ifdef UART2_TX_RD5_RP69
    {PD5, hal_ll_uart_module_num(UART_MODULE_2), false},
    #endif
    #ifdef UART2_TX_RD6_RP70
    {PD6, hal_ll_uart_module_num(UART_MODULE_2), false},
    #endif
    #ifdef UART2_TX_RF1_RP97
    {PF1, hal_ll_uart_module_num(UART_MODULE_2), false},
    #endif
    #ifdef UART2_TX_RG6_RP118
    {PG6, hal_ll_uart_module_num(UART_MODULE_2), false},
    #endif
    #ifdef UART2_TX_RG8_RP120
    {PG8, hal_ll_uart_module_num(UART_MODULE_2), false},
    #endif
    #ifdef UART3_TX_RD5_RP69
    {PD5, hal_ll_uart_module_num(UART_MODULE_3), false},
    #endif
    #ifdef UART3_TX_RD6_RP70
    {PD6, hal_ll_uart_module_num(UART_MODULE_3), false},
    #endif
    #ifdef UART3_TX_RF1_RP97
    {PF1, hal_ll_uart_module_num(UART_MODULE_3), false},
    #endif
    #ifdef UART3_TX_RG6_RP118
    {PG6, hal_ll_uart_module_num(UART_MODULE_3), false},
    #endif
    #ifdef UART3_TX_RG8_RP120
    {PG8, hal_ll_uart_module_num(UART_MODULE_3), false},
    #endif
    #ifdef UART4_TX_RD5_RP69
    {PD5, hal_ll_uart_module_num(UART_MODULE_4), false},
    #endif
    #ifdef UART4_TX_RD6_RP70
    {PD6, hal_ll_uart_module_num(UART_MODULE_4), false},
    #endif
    #ifdef UART4_TX_RF1_RP97
    {PF1, hal_ll_uart_module_num(UART_MODULE_4), false},
    #endif
    #ifdef UART4_TX_RG6_RP118
    {PG6, hal_ll_uart_module_num(UART_MODULE_4), false},
    #endif
    #ifdef UART4_TX_RG8_RP120
    {PG8, hal_ll_uart_module_num(UART_MODULE_4), false},
    #endif
    #ifdef UART1_TX_RE1_RP81
    {PE1, hal_ll_uart_module_num(UART_MODULE_1), false},
    #endif
    #ifdef UART1_TX_RG1_RP113
    {PG1, hal_ll_uart_module_num(UART_MODULE_1), false},
    #endif
    #ifdef UART1_TX_RG13_RP125
    {PG13, hal_ll_uart_module_num(UART_MODULE_1), false},
    #endif
    #ifdef UART1_TX_RG14_RP126
    {PG14, hal_ll_uart_module_num(UART_MODULE_1), false},
    #endif
    #ifdef UART1_TX_RG15_RP127
    {PG15, hal_ll_uart_module_num(UART_MODULE_1), false},
    #endif
    #ifdef UART2_TX_RE1_RP81
    {PE1, hal_ll_uart_module_num(UART_MODULE_2), false},
    #endif
    #ifdef UART2_TX_RG1_RP113
    {PG1, hal_ll_uart_module_num(UART_MODULE_2), false},
    #endif
    #ifdef UART2_TX_RG13_RP125
    {PG13, hal_ll_uart_module_num(UART_MODULE_2), false},
    #endif
    #ifdef UART2_TX_RG14_RP126
    {PG14, hal_ll_uart_module_num(UART_MODULE_2), false},
    #endif
    #ifdef UART2_TX_RG15_RP127
    {PG15, hal_ll_uart_module_num(UART_MODULE_2), false},
    #endif
    #ifdef UART3_TX_RE1_RP81
    {PE1, hal_ll_uart_module_num(UART_MODULE_3), false},
    #endif
    #ifdef UART3_TX_RG1_RP113
    {PG1, hal_ll_uart_module_num(UART_MODULE_3), false},
    #endif
    #ifdef UART3_TX_RG13_RP125
    {PG13, hal_ll_uart_module_num(UART_MODULE_3), false},
    #endif
    #ifdef UART3_TX_RG14_RP126
    {PG14, hal_ll_uart_module_num(UART_MODULE_3), false},
    #endif
    #ifdef UART3_TX_RG15_RP127
    {PG15, hal_ll_uart_module_num(UART_MODULE_3), false},
    #endif
    #ifdef UART4_TX_RE1_RP81
    {PE1, hal_ll_uart_module_num(UART_MODULE_4), false},
    #endif
    #ifdef UART4_TX_RG1_RP113
    {PG1, hal_ll_uart_module_num(UART_MODULE_4), false},
    #endif
    #ifdef UART4_TX_RG13_RP125
    {PG13, hal_ll_uart_module_num(UART_MODULE_4), false},
    #endif
    #ifdef UART4_TX_RG14_RP126
    {PG14, hal_ll_uart_module_num(UART_MODULE_4), false},
    #endif
    #ifdef UART4_TX_RG15_RP127
    {PG15, hal_ll_uart_module_num(UART_MODULE_4), false},
    #endif
    #ifdef UART1_TX_RA0_RP16
    {PA0, hal_ll_uart_module_num(UART_MODULE_1), false},
    #endif
    #ifdef UART1_TX_RA1_RP17
    {PA1, hal_ll_uart_module_num(UART_MODULE_1), false},
    #endif
    #ifdef UART1_TX_RA2_RP18
    {PA2, hal_ll_uart_module_num(UART_MODULE_1), false},
    #endif
    #ifdef UART1_TX_RA3_RP19
    {PA3, hal_ll_uart_module_num(UART_MODULE_1), false},
    #endif
    #ifdef UART1_TX_RB0_RP32
    {PB0, hal_ll_uart_module_num(UART_MODULE_1), false},
    #endif
    #ifdef UART1_TX_RB1_RP33
    {PB1, hal_ll_uart_module_num(UART_MODULE_1), false},
    #endif
    #ifdef UART1_TX_RB12_RP44
    {PB12, hal_ll_uart_module_num(UART_MODULE_1), false},
    #endif
    #ifdef UART1_TX_RB13_RP45
    {PB13, hal_ll_uart_module_num(UART_MODULE_1), false},
    #endif
    #ifdef UART1_TX_RB14_RP46
    {PB14, hal_ll_uart_module_num(UART_MODULE_1), false},
    #endif
    #ifdef UART1_TX_RB15_RP47
    {PB15, hal_ll_uart_module_num(UART_MODULE_1), false},
    #endif
    #ifdef UART1_TX_RB2_RP34
    {PB2, hal_ll_uart_module_num(UART_MODULE_1), false},
    #endif
    #ifdef UART2_TX_RA0_RP16
    {PA0, hal_ll_uart_module_num(UART_MODULE_2), false},
    #endif
    #ifdef UART2_TX_RA1_RP17
    {PA1, hal_ll_uart_module_num(UART_MODULE_2), false},
    #endif
    #ifdef UART2_TX_RA2_RP18
    {PA2, hal_ll_uart_module_num(UART_MODULE_2), false},
    #endif
    #ifdef UART2_TX_RA3_RP19
    {PA3, hal_ll_uart_module_num(UART_MODULE_2), false},
    #endif
    #ifdef UART2_TX_RB0_RP32
    {PB0, hal_ll_uart_module_num(UART_MODULE_2), false},
    #endif
    #ifdef UART2_TX_RB1_RP33
    {PB1, hal_ll_uart_module_num(UART_MODULE_2), false},
    #endif
    #ifdef UART2_TX_RB12_RP44
    {PB12, hal_ll_uart_module_num(UART_MODULE_2), false},
    #endif
    #ifdef UART2_TX_RB13_RP45
    {PB13, hal_ll_uart_module_num(UART_MODULE_2), false},
    #endif
    #ifdef UART2_TX_RB14_RP46
    {PB14, hal_ll_uart_module_num(UART_MODULE_2), false},
    #endif
    #ifdef UART2_TX_RB15_RP47
    {PB15, hal_ll_uart_module_num(UART_MODULE_2), false},
    #endif
    #ifdef UART2_TX_RB2_RP34
    {PB2, hal_ll_uart_module_num(UART_MODULE_2), false},
    #endif
    #ifdef UART1_TX_RC10_RP58
    {PC10, hal_ll_uart_module_num(UART_MODULE_1), false},
    #endif
    #ifdef UART1_TX_RC12_RP60
    {PC12, hal_ll_uart_module_num(UART_MODULE_1), false},
    #endif
    #ifdef UART1_TX_RC13_RP61
    {PC13, hal_ll_uart_module_num(UART_MODULE_1), false},
    #endif
    #ifdef UART1_TX_RC2_RP50
    {PC2, hal_ll_uart_module_num(UART_MODULE_1), false},
    #endif
    #ifdef UART1_TX_RC3_RP51
    {PC3, hal_ll_uart_module_num(UART_MODULE_1), false},
    #endif
    #ifdef UART1_TX_RC4_RP52
    {PC4, hal_ll_uart_module_num(UART_MODULE_1), false},
    #endif
    #ifdef UART1_TX_RC5_RP53
    {PC5, hal_ll_uart_module_num(UART_MODULE_1), false},
    #endif
    #ifdef UART2_TX_RC10_RP58
    {PC10, hal_ll_uart_module_num(UART_MODULE_2), false},
    #endif
    #ifdef UART2_TX_RC12_RP60
    {PC12, hal_ll_uart_module_num(UART_MODULE_2), false},
    #endif
    #ifdef UART2_TX_RC13_RP61
    {PC13, hal_ll_uart_module_num(UART_MODULE_2), false},
    #endif
    #ifdef UART2_TX_RC2_RP50
    {PC2, hal_ll_uart_module_num(UART_MODULE_2), false},
    #endif
    #ifdef UART2_TX_RC3_RP51
    {PC3, hal_ll_uart_module_num(UART_MODULE_2), false},
    #endif
    #ifdef UART2_TX_RC4_RP52
    {PC4, hal_ll_uart_module_num(UART_MODULE_2), false},
    #endif
    #ifdef UART2_TX_RC5_RP53
    {PC5, hal_ll_uart_module_num(UART_MODULE_2), false},
    #endif
    #ifdef UART1_TX_RD10_RP74
    {PD10, hal_ll_uart_module_num(UART_MODULE_1), false},
    #endif
    #ifdef UART1_TX_RD4_RP68
    {PD4, hal_ll_uart_module_num(UART_MODULE_1), false},
    #endif
    #ifdef UART2_TX_RD10_RP74
    {PD10, hal_ll_uart_module_num(UART_MODULE_2), false},
    #endif
    #ifdef UART2_TX_RD4_RP68
    {PD4, hal_ll_uart_module_num(UART_MODULE_2), false},
    #endif
    #ifdef UART1_TX_RC14_RP62
    {PC14, hal_ll_uart_module_num(UART_MODULE_1), false},
    #endif
    #ifdef UART1_TX_RC15_RP63
    {PC15, hal_ll_uart_module_num(UART_MODULE_1), false},
    #endif
    #ifdef UART1_TX_RD0_RP64
    {PD0, hal_ll_uart_module_num(UART_MODULE_1), false},
    #endif
    #ifdef UART1_TX_RD1_RP65
    {PD1, hal_ll_uart_module_num(UART_MODULE_1), false},
    #endif
    #ifdef UART1_TX_RD11_RP75
    {PD11, hal_ll_uart_module_num(UART_MODULE_1), false},
    #endif
    #ifdef UART1_TX_RD12_RP76
    {PD12, hal_ll_uart_module_num(UART_MODULE_1), false},
    #endif
    #ifdef UART1_TX_RD2_RP66
    {PD2, hal_ll_uart_module_num(UART_MODULE_1), false},
    #endif
    #ifdef UART1_TX_RD3_RP67
    {PD3, hal_ll_uart_module_num(UART_MODULE_1), false},
    #endif
    #ifdef UART1_TX_RD7_RP71
    {PD7, hal_ll_uart_module_num(UART_MODULE_1), false},
    #endif
    #ifdef UART1_TX_RD8_RP72
    {PD8, hal_ll_uart_module_num(UART_MODULE_1), false},
    #endif
    #ifdef UART1_TX_RD9_RP73
    {PD9, hal_ll_uart_module_num(UART_MODULE_1), false},
    #endif
    #ifdef UART2_TX_RC14_RP62
    {PC14, hal_ll_uart_module_num(UART_MODULE_2), false},
    #endif
    #ifdef UART2_TX_RC15_RP63
    {PC15, hal_ll_uart_module_num(UART_MODULE_2), false},
    #endif
    #ifdef UART2_TX_RD0_RP64
    {PD0, hal_ll_uart_module_num(UART_MODULE_2), false},
    #endif
    #ifdef UART2_TX_RD1_RP65
    {PD1, hal_ll_uart_module_num(UART_MODULE_2), false},
    #endif
    #ifdef UART2_TX_RD11_RP75
    {PD11, hal_ll_uart_module_num(UART_MODULE_2), false},
    #endif
    #ifdef UART2_TX_RD12_RP76
    {PD12, hal_ll_uart_module_num(UART_MODULE_2), false},
    #endif
    #ifdef UART2_TX_RD2_RP66
    {PD2, hal_ll_uart_module_num(UART_MODULE_2), false},
    #endif
    #ifdef UART2_TX_RD3_RP67
    {PD3, hal_ll_uart_module_num(UART_MODULE_2), false},
    #endif
    #ifdef UART2_TX_RD7_RP71
    {PD7, hal_ll_uart_module_num(UART_MODULE_2), false},
    #endif
    #ifdef UART2_TX_RD8_RP72
    {PD8, hal_ll_uart_module_num(UART_MODULE_2), false},
    #endif
    #ifdef UART2_TX_RD9_RP73
    {PD9, hal_ll_uart_module_num(UART_MODULE_2), false},
    #endif
    #ifdef UART1_TX_RC11_RP59
    {PC11, hal_ll_uart_module_num(UART_MODULE_1), false},
    #endif
    #ifdef UART2_TX_RC11_RP59
    {PC11, hal_ll_uart_module_num(UART_MODULE_2), false},
    #endif
    #ifdef UART1_TX_RE0_RP80
    {PE0, hal_ll_uart_module_num(UART_MODULE_1), false},
    #endif
    #ifdef UART1_TX_RE2_RP82
    {PE2, hal_ll_uart_module_num(UART_MODULE_1), false},
    #endif
    #ifdef UART1_TX_RE4_RP84
    {PE4, hal_ll_uart_module_num(UART_MODULE_1), false},
    #endif
    #ifdef UART1_TX_RE5_RP85
    {PE5, hal_ll_uart_module_num(UART_MODULE_1), false},
    #endif
    #ifdef UART1_TX_RE7_RP87
    {PE7, hal_ll_uart_module_num(UART_MODULE_1), false},
    #endif
    #ifdef UART1_TX_RF0_RP96
    {PF0, hal_ll_uart_module_num(UART_MODULE_1), false},
    #endif
    #ifdef UART1_TX_RF3_RP99
    {PF3, hal_ll_uart_module_num(UART_MODULE_1), false},
    #endif
    #ifdef UART1_TX_RF4_RP100
    {PF4, hal_ll_uart_module_num(UART_MODULE_1), false},
    #endif
    #ifdef UART1_TX_RF5_RP101
    {PF5, hal_ll_uart_module_num(UART_MODULE_1), false},
    #endif
    #ifdef UART2_TX_RE0_RP80
    {PE0, hal_ll_uart_module_num(UART_MODULE_2), false},
    #endif
    #ifdef UART2_TX_RE2_RP82
    {PE2, hal_ll_uart_module_num(UART_MODULE_2), false},
    #endif
    #ifdef UART2_TX_RE4_RP84
    {PE4, hal_ll_uart_module_num(UART_MODULE_2), false},
    #endif
    #ifdef UART2_TX_RE5_RP85
    {PE5, hal_ll_uart_module_num(UART_MODULE_2), false},
    #endif
    #ifdef UART2_TX_RE7_RP87
    {PE7, hal_ll_uart_module_num(UART_MODULE_2), false},
    #endif
    #ifdef UART2_TX_RF0_RP96
    {PF0, hal_ll_uart_module_num(UART_MODULE_2), false},
    #endif
    #ifdef UART2_TX_RF3_RP99
    {PF3, hal_ll_uart_module_num(UART_MODULE_2), false},
    #endif
    #ifdef UART2_TX_RF4_RP100
    {PF4, hal_ll_uart_module_num(UART_MODULE_2), false},
    #endif
    #ifdef UART2_TX_RF5_RP101
    {PF5, hal_ll_uart_module_num(UART_MODULE_2), false},
    #endif
    #ifdef UART3_TX_RD0_RP64
    {PD0, hal_ll_uart_module_num(UART_MODULE_3), false},
    #endif
    #ifdef UART3_TX_RD1_RP65
    {PD1, hal_ll_uart_module_num(UART_MODULE_3), false},
    #endif
    #ifdef UART3_TX_RD2_RP66
    {PD2, hal_ll_uart_module_num(UART_MODULE_3), false},
    #endif
    #ifdef UART3_TX_RD3_RP67
    {PD3, hal_ll_uart_module_num(UART_MODULE_3), false},
    #endif
    #ifdef UART3_TX_RD4_RP68
    {PD4, hal_ll_uart_module_num(UART_MODULE_3), false},
    #endif
    #ifdef UART3_TX_RD7_RP71
    {PD7, hal_ll_uart_module_num(UART_MODULE_3), false},
    #endif
    #ifdef UART3_TX_RE0_RP80
    {PE0, hal_ll_uart_module_num(UART_MODULE_3), false},
    #endif
    #ifdef UART3_TX_RE2_RP82
    {PE2, hal_ll_uart_module_num(UART_MODULE_3), false},
    #endif
    #ifdef UART3_TX_RE4_RP84
    {PE4, hal_ll_uart_module_num(UART_MODULE_3), false},
    #endif
    #ifdef UART3_TX_RE5_RP85
    {PE5, hal_ll_uart_module_num(UART_MODULE_3), false},
    #endif
    #ifdef UART3_TX_RE7_RP87
    {PE7, hal_ll_uart_module_num(UART_MODULE_3), false},
    #endif
    #ifdef UART3_TX_RF0_RP96
    {PF0, hal_ll_uart_module_num(UART_MODULE_3), false},
    #endif
    #ifdef UART3_TX_RF3_RP99
    {PF3, hal_ll_uart_module_num(UART_MODULE_3), false},
    #endif
    #ifdef UART3_TX_RF4_RP100
    {PF4, hal_ll_uart_module_num(UART_MODULE_3), false},
    #endif
    #ifdef UART3_TX_RF5_RP101
    {PF5, hal_ll_uart_module_num(UART_MODULE_3), false},
    #endif
    #ifdef UART4_TX_RD0_RP64
    {PD0, hal_ll_uart_module_num(UART_MODULE_4), false},
    #endif
    #ifdef UART4_TX_RD1_RP65
    {PD1, hal_ll_uart_module_num(UART_MODULE_4), false},
    #endif
    #ifdef UART4_TX_RD2_RP66
    {PD2, hal_ll_uart_module_num(UART_MODULE_4), false},
    #endif
    #ifdef UART4_TX_RD3_RP67
    {PD3, hal_ll_uart_module_num(UART_MODULE_4), false},
    #endif
    #ifdef UART4_TX_RD4_RP68
    {PD4, hal_ll_uart_module_num(UART_MODULE_4), false},
    #endif
    #ifdef UART4_TX_RD7_RP71
    {PD7, hal_ll_uart_module_num(UART_MODULE_4), false},
    #endif
    #ifdef UART4_TX_RE0_RP80
    {PE0, hal_ll_uart_module_num(UART_MODULE_4), false},
    #endif
    #ifdef UART4_TX_RE2_RP82
    {PE2, hal_ll_uart_module_num(UART_MODULE_4), false},
    #endif
    #ifdef UART4_TX_RE4_RP84
    {PE4, hal_ll_uart_module_num(UART_MODULE_4), false},
    #endif
    #ifdef UART4_TX_RE5_RP85
    {PE5, hal_ll_uart_module_num(UART_MODULE_4), false},
    #endif
    #ifdef UART4_TX_RE7_RP87
    {PE7, hal_ll_uart_module_num(UART_MODULE_4), false},
    #endif
    #ifdef UART4_TX_RF0_RP96
    {PF0, hal_ll_uart_module_num(UART_MODULE_4), false},
    #endif
    #ifdef UART4_TX_RF3_RP99
    {PF3, hal_ll_uart_module_num(UART_MODULE_4), false},
    #endif
    #ifdef UART4_TX_RF4_RP100
    {PF4, hal_ll_uart_module_num(UART_MODULE_4), false},
    #endif
    #ifdef UART4_TX_RF5_RP101
    {PF5, hal_ll_uart_module_num(UART_MODULE_4), false},
    #endif
    #ifdef UART1_TX_RD15_RP79
    {PD15, hal_ll_uart_module_num(UART_MODULE_1), false},
    #endif
    #ifdef UART1_TX_RF12_RP108
    {PF12, hal_ll_uart_module_num(UART_MODULE_1), false},
    #endif
    #ifdef UART1_TX_RF13_RP109
    {PF13, hal_ll_uart_module_num(UART_MODULE_1), false},
    #endif
    #ifdef UART1_TX_RF2_RP98
    {PF2, hal_ll_uart_module_num(UART_MODULE_1), false},
    #endif
    #ifdef UART1_TX_RF8_RP104
    {PF8, hal_ll_uart_module_num(UART_MODULE_1), false},
    #endif
    #ifdef UART1_TX_RG0_RP112
    {PG0, hal_ll_uart_module_num(UART_MODULE_1), false},
    #endif
    #ifdef UART2_TX_RD15_RP79
    {PD15, hal_ll_uart_module_num(UART_MODULE_2), false},
    #endif
    #ifdef UART2_TX_RF12_RP108
    {PF12, hal_ll_uart_module_num(UART_MODULE_2), false},
    #endif
    #ifdef UART2_TX_RF13_RP109
    {PF13, hal_ll_uart_module_num(UART_MODULE_2), false},
    #endif
    #ifdef UART2_TX_RF2_RP98
    {PF2, hal_ll_uart_module_num(UART_MODULE_2), false},
    #endif
    #ifdef UART2_TX_RF8_RP104
    {PF8, hal_ll_uart_module_num(UART_MODULE_2), false},
    #endif
    #ifdef UART2_TX_RG0_RP112
    {PG0, hal_ll_uart_module_num(UART_MODULE_2), false},
    #endif
    #ifdef UART3_TX_RD15_RP79
    {PD15, hal_ll_uart_module_num(UART_MODULE_3), false},
    #endif
    #ifdef UART3_TX_RF12_RP108
    {PF12, hal_ll_uart_module_num(UART_MODULE_3), false},
    #endif
    #ifdef UART3_TX_RF13_RP109
    {PF13, hal_ll_uart_module_num(UART_MODULE_3), false},
    #endif
    #ifdef UART3_TX_RF2_RP98
    {PF2, hal_ll_uart_module_num(UART_MODULE_3), false},
    #endif
    #ifdef UART3_TX_RF8_RP104
    {PF8, hal_ll_uart_module_num(UART_MODULE_3), false},
    #endif
    #ifdef UART3_TX_RG0_RP112
    {PG0, hal_ll_uart_module_num(UART_MODULE_3), false},
    #endif
    #ifdef UART4_TX_RD15_RP79
    {PD15, hal_ll_uart_module_num(UART_MODULE_4), false},
    #endif
    #ifdef UART4_TX_RF12_RP108
    {PF12, hal_ll_uart_module_num(UART_MODULE_4), false},
    #endif
    #ifdef UART4_TX_RF13_RP109
    {PF13, hal_ll_uart_module_num(UART_MODULE_4), false},
    #endif
    #ifdef UART4_TX_RF2_RP98
    {PF2, hal_ll_uart_module_num(UART_MODULE_4), false},
    #endif
    #ifdef UART4_TX_RF8_RP104
    {PF8, hal_ll_uart_module_num(UART_MODULE_4), false},
    #endif
    #ifdef UART4_TX_RG0_RP112
    {PG0, hal_ll_uart_module_num(UART_MODULE_4), false},
    #endif
    #ifdef UART1_TX_RF6_RP102
    {PF6, hal_ll_uart_module_num(UART_MODULE_1), false},
    #endif
    #ifdef UART2_TX_RF6_RP102
    {PF6, hal_ll_uart_module_num(UART_MODULE_2), false},
    #endif
    #ifdef UART3_TX_RF6_RP102
    {PF6, hal_ll_uart_module_num(UART_MODULE_3), false},
    #endif
    #ifdef UART4_TX_RF6_RP102
    {PF6, hal_ll_uart_module_num(UART_MODULE_4), false},
    #endif
    #ifdef UART1_TX_RB0_RP0
    {PB0, hal_ll_uart_module_num(UART_MODULE_1), false},
    #endif
    #ifdef UART1_TX_RB1_RP1
    {PB1, hal_ll_uart_module_num(UART_MODULE_1), false},
    #endif
    #ifdef UART1_TX_RB10_RP10
    {PB10, hal_ll_uart_module_num(UART_MODULE_1), false},
    #endif
    #ifdef UART1_TX_RB11_RP11
    {PB11, hal_ll_uart_module_num(UART_MODULE_1), false},
    #endif
    #ifdef UART1_TX_RB12_RP12
    {PB12, hal_ll_uart_module_num(UART_MODULE_1), false},
    #endif
    #ifdef UART1_TX_RB13_RP13
    {PB13, hal_ll_uart_module_num(UART_MODULE_1), false},
    #endif
    #ifdef UART1_TX_RB14_RP14
    {PB14, hal_ll_uart_module_num(UART_MODULE_1), false},
    #endif
    #ifdef UART1_TX_RB15_RP15
    {PB15, hal_ll_uart_module_num(UART_MODULE_1), false},
    #endif
    #ifdef UART1_TX_RB2_RP2
    {PB2, hal_ll_uart_module_num(UART_MODULE_1), false},
    #endif
    #ifdef UART1_TX_RB3_RP3
    {PB3, hal_ll_uart_module_num(UART_MODULE_1), false},
    #endif
    #ifdef UART1_TX_RB4_RP4
    {PB4, hal_ll_uart_module_num(UART_MODULE_1), false},
    #endif
    #ifdef UART1_TX_RB5_RP5
    {PB5, hal_ll_uart_module_num(UART_MODULE_1), false},
    #endif
    #ifdef UART1_TX_RB6_RP6
    {PB6, hal_ll_uart_module_num(UART_MODULE_1), false},
    #endif
    #ifdef UART1_TX_RB7_RP7
    {PB7, hal_ll_uart_module_num(UART_MODULE_1), false},
    #endif
    #ifdef UART1_TX_RB8_RP8
    {PB8, hal_ll_uart_module_num(UART_MODULE_1), false},
    #endif
    #ifdef UART1_TX_RB9_RP9
    {PB9, hal_ll_uart_module_num(UART_MODULE_1), false},
    #endif
    #ifdef UART2_TX_RB0_RP0
    {PB0, hal_ll_uart_module_num(UART_MODULE_2), false},
    #endif
    #ifdef UART2_TX_RB1_RP1
    {PB1, hal_ll_uart_module_num(UART_MODULE_2), false},
    #endif
    #ifdef UART2_TX_RB10_RP10
    {PB10, hal_ll_uart_module_num(UART_MODULE_2), false},
    #endif
    #ifdef UART2_TX_RB11_RP11
    {PB11, hal_ll_uart_module_num(UART_MODULE_2), false},
    #endif
    #ifdef UART2_TX_RB12_RP12
    {PB12, hal_ll_uart_module_num(UART_MODULE_2), false},
    #endif
    #ifdef UART2_TX_RB13_RP13
    {PB13, hal_ll_uart_module_num(UART_MODULE_2), false},
    #endif
    #ifdef UART2_TX_RB14_RP14
    {PB14, hal_ll_uart_module_num(UART_MODULE_2), false},
    #endif
    #ifdef UART2_TX_RB15_RP15
    {PB15, hal_ll_uart_module_num(UART_MODULE_2), false},
    #endif
    #ifdef UART2_TX_RB2_RP2
    {PB2, hal_ll_uart_module_num(UART_MODULE_2), false},
    #endif
    #ifdef UART2_TX_RB3_RP3
    {PB3, hal_ll_uart_module_num(UART_MODULE_2), false},
    #endif
    #ifdef UART2_TX_RB4_RP4
    {PB4, hal_ll_uart_module_num(UART_MODULE_2), false},
    #endif
    #ifdef UART2_TX_RB5_RP5
    {PB5, hal_ll_uart_module_num(UART_MODULE_2), false},
    #endif
    #ifdef UART2_TX_RB6_RP6
    {PB6, hal_ll_uart_module_num(UART_MODULE_2), false},
    #endif
    #ifdef UART2_TX_RB7_RP7
    {PB7, hal_ll_uart_module_num(UART_MODULE_2), false},
    #endif
    #ifdef UART2_TX_RB8_RP8
    {PB8, hal_ll_uart_module_num(UART_MODULE_2), false},
    #endif
    #ifdef UART2_TX_RB9_RP9
    {PB9, hal_ll_uart_module_num(UART_MODULE_2), false},
    #endif
    #ifdef UART1_TX_RC0_RP16
    {PC0, hal_ll_uart_module_num(UART_MODULE_1), false},
    #endif
    #ifdef UART1_TX_RC1_RP17
    {PC1, hal_ll_uart_module_num(UART_MODULE_1), false},
    #endif
    #ifdef UART1_TX_RC2_RP18
    {PC2, hal_ll_uart_module_num(UART_MODULE_1), false},
    #endif
    #ifdef UART1_TX_RC3_RP19
    {PC3, hal_ll_uart_module_num(UART_MODULE_1), false},
    #endif
    #ifdef UART1_TX_RC4_RP20
    {PC4, hal_ll_uart_module_num(UART_MODULE_1), false},
    #endif
    #ifdef UART1_TX_RC5_RP21
    {PC5, hal_ll_uart_module_num(UART_MODULE_1), false},
    #endif
    #ifdef UART1_TX_RC6_RP22
    {PC6, hal_ll_uart_module_num(UART_MODULE_1), false},
    #endif
    #ifdef UART1_TX_RC7_RP23
    {PC7, hal_ll_uart_module_num(UART_MODULE_1), false},
    #endif
    #ifdef UART1_TX_RC8_RP24
    {PC8, hal_ll_uart_module_num(UART_MODULE_1), false},
    #endif
    #ifdef UART1_TX_RC9_RP25
    {PC9, hal_ll_uart_module_num(UART_MODULE_1), false},
    #endif
    #ifdef UART2_TX_RC0_RP16
    {PC0, hal_ll_uart_module_num(UART_MODULE_2), false},
    #endif
    #ifdef UART2_TX_RC1_RP17
    {PC1, hal_ll_uart_module_num(UART_MODULE_2), false},
    #endif
    #ifdef UART2_TX_RC2_RP18
    {PC2, hal_ll_uart_module_num(UART_MODULE_2), false},
    #endif
    #ifdef UART2_TX_RC3_RP19
    {PC3, hal_ll_uart_module_num(UART_MODULE_2), false},
    #endif
    #ifdef UART2_TX_RC4_RP20
    {PC4, hal_ll_uart_module_num(UART_MODULE_2), false},
    #endif
    #ifdef UART2_TX_RC5_RP21
    {PC5, hal_ll_uart_module_num(UART_MODULE_2), false},
    #endif
    #ifdef UART2_TX_RC6_RP22
    {PC6, hal_ll_uart_module_num(UART_MODULE_2), false},
    #endif
    #ifdef UART2_TX_RC7_RP23
    {PC7, hal_ll_uart_module_num(UART_MODULE_2), false},
    #endif
    #ifdef UART2_TX_RC8_RP24
    {PC8, hal_ll_uart_module_num(UART_MODULE_2), false},
    #endif
    #ifdef UART2_TX_RC9_RP25
    {PC9, hal_ll_uart_module_num(UART_MODULE_2), false},
    #endif
    #ifdef UART1_TX_RC10_RP26
    {PC10, hal_ll_uart_module_num(UART_MODULE_1), false},
    #endif
    #ifdef UART1_TX_RC11_RP27
    {PC11, hal_ll_uart_module_num(UART_MODULE_1), false},
    #endif
    #ifdef UART1_TX_RC12_RP28
    {PC12, hal_ll_uart_module_num(UART_MODULE_1), false},
    #endif
    #ifdef UART1_TX_RC13_RP29
    {PC13, hal_ll_uart_module_num(UART_MODULE_1), false},
    #endif
    #ifdef UART1_TX_RB7
    {PB7, hal_ll_uart_module_num(UART_MODULE_1), false},
    #endif
    #ifdef UART2_TX_RB0
    {PB0, hal_ll_uart_module_num(UART_MODULE_2), false},
    #endif
    #ifdef UART1_TX_RC7
    {PC7, hal_ll_uart_module_num(UART_MODULE_1), false},
    #endif
    #ifdef UART1_TX_RB15_RP29
    {PB15, hal_ll_uart_module_num(UART_MODULE_1), false},
    #endif
    #ifdef UART1_TX_RB2_RP13
    {PB2, hal_ll_uart_module_num(UART_MODULE_1), false},
    #endif
    #ifdef UART1_TX_RB4_RP28
    {PB4, hal_ll_uart_module_num(UART_MODULE_1), false},
    #endif
    #ifdef UART1_TX_RB5_RP18
    {PB5, hal_ll_uart_module_num(UART_MODULE_1), false},
    #endif
    #ifdef UART1_TX_RD0_RP11
    {PD0, hal_ll_uart_module_num(UART_MODULE_1), false},
    #endif
    #ifdef UART1_TX_RD1_RP24
    {PD1, hal_ll_uart_module_num(UART_MODULE_1), false},
    #endif
    #ifdef UART1_TX_RD10_RP3
    {PD10, hal_ll_uart_module_num(UART_MODULE_1), false},
    #endif
    #ifdef UART1_TX_RD11_RP12
    {PD11, hal_ll_uart_module_num(UART_MODULE_1), false},
    #endif
    #ifdef UART1_TX_RD2_RP23
    {PD2, hal_ll_uart_module_num(UART_MODULE_1), false},
    #endif
    #ifdef UART1_TX_RD3_RP22
    {PD3, hal_ll_uart_module_num(UART_MODULE_1), false},
    #endif
    #ifdef UART1_TX_RD4_RP25
    {PD4, hal_ll_uart_module_num(UART_MODULE_1), false},
    #endif
    #ifdef UART1_TX_RD5_RP20
    {PD5, hal_ll_uart_module_num(UART_MODULE_1), false},
    #endif
    #ifdef UART1_TX_RD8_RP2
    {PD8, hal_ll_uart_module_num(UART_MODULE_1), false},
    #endif
    #ifdef UART1_TX_RD9_RP4
    {PD9, hal_ll_uart_module_num(UART_MODULE_1), false},
    #endif
    #ifdef UART1_TX_RF2_RP30
    {PF2, hal_ll_uart_module_num(UART_MODULE_1), false},
    #endif
    #ifdef UART1_TX_RF3_RP16
    {PF3, hal_ll_uart_module_num(UART_MODULE_1), false},
    #endif
    #ifdef UART1_TX_RF4_RP10
    {PF4, hal_ll_uart_module_num(UART_MODULE_1), false},
    #endif
    #ifdef UART1_TX_RF5_RP17
    {PF5, hal_ll_uart_module_num(UART_MODULE_1), false},
    #endif
    #ifdef UART1_TX_RG6_RP21
    {PG6, hal_ll_uart_module_num(UART_MODULE_1), false},
    #endif
    #ifdef UART1_TX_RG7_RP26
    {PG7, hal_ll_uart_module_num(UART_MODULE_1), false},
    #endif
    #ifdef UART1_TX_RG8_RP19
    {PG8, hal_ll_uart_module_num(UART_MODULE_1), false},
    #endif
    #ifdef UART1_TX_RG9_RP27
    {PG9, hal_ll_uart_module_num(UART_MODULE_1), false},
    #endif
    #ifdef UART2_TX_RB15_RP29
    {PB15, hal_ll_uart_module_num(UART_MODULE_2), false},
    #endif
    #ifdef UART2_TX_RB2_RP13
    {PB2, hal_ll_uart_module_num(UART_MODULE_2), false},
    #endif
    #ifdef UART2_TX_RB4_RP28
    {PB4, hal_ll_uart_module_num(UART_MODULE_2), false},
    #endif
    #ifdef UART2_TX_RB5_RP18
    {PB5, hal_ll_uart_module_num(UART_MODULE_2), false},
    #endif
    #ifdef UART2_TX_RD0_RP11
    {PD0, hal_ll_uart_module_num(UART_MODULE_2), false},
    #endif
    #ifdef UART2_TX_RD1_RP24
    {PD1, hal_ll_uart_module_num(UART_MODULE_2), false},
    #endif
    #ifdef UART2_TX_RD10_RP3
    {PD10, hal_ll_uart_module_num(UART_MODULE_2), false},
    #endif
    #ifdef UART2_TX_RD11_RP12
    {PD11, hal_ll_uart_module_num(UART_MODULE_2), false},
    #endif
    #ifdef UART2_TX_RD2_RP23
    {PD2, hal_ll_uart_module_num(UART_MODULE_2), false},
    #endif
    #ifdef UART2_TX_RD3_RP22
    {PD3, hal_ll_uart_module_num(UART_MODULE_2), false},
    #endif
    #ifdef UART2_TX_RD4_RP25
    {PD4, hal_ll_uart_module_num(UART_MODULE_2), false},
    #endif
    #ifdef UART2_TX_RD5_RP20
    {PD5, hal_ll_uart_module_num(UART_MODULE_2), false},
    #endif
    #ifdef UART2_TX_RD8_RP2
    {PD8, hal_ll_uart_module_num(UART_MODULE_2), false},
    #endif
    #ifdef UART2_TX_RD9_RP4
    {PD9, hal_ll_uart_module_num(UART_MODULE_2), false},
    #endif
    #ifdef UART2_TX_RF2_RP30
    {PF2, hal_ll_uart_module_num(UART_MODULE_2), false},
    #endif
    #ifdef UART2_TX_RF3_RP16
    {PF3, hal_ll_uart_module_num(UART_MODULE_2), false},
    #endif
    #ifdef UART2_TX_RF4_RP10
    {PF4, hal_ll_uart_module_num(UART_MODULE_2), false},
    #endif
    #ifdef UART2_TX_RF5_RP17
    {PF5, hal_ll_uart_module_num(UART_MODULE_2), false},
    #endif
    #ifdef UART2_TX_RG6_RP21
    {PG6, hal_ll_uart_module_num(UART_MODULE_2), false},
    #endif
    #ifdef UART2_TX_RG7_RP26
    {PG7, hal_ll_uart_module_num(UART_MODULE_2), false},
    #endif
    #ifdef UART2_TX_RG8_RP19
    {PG8, hal_ll_uart_module_num(UART_MODULE_2), false},
    #endif
    #ifdef UART2_TX_RG9_RP27
    {PG9, hal_ll_uart_module_num(UART_MODULE_2), false},
    #endif
    #ifdef UART3_TX_RB0_RP0
    {PB0, hal_ll_uart_module_num(UART_MODULE_3), false},
    #endif
    #ifdef UART3_TX_RB1_RP1
    {PB1, hal_ll_uart_module_num(UART_MODULE_3), false},
    #endif
    #ifdef UART3_TX_RB14_RP14
    {PB14, hal_ll_uart_module_num(UART_MODULE_3), false},
    #endif
    #ifdef UART3_TX_RB15_RP29
    {PB15, hal_ll_uart_module_num(UART_MODULE_3), false},
    #endif
    #ifdef UART3_TX_RB2_RP13
    {PB2, hal_ll_uart_module_num(UART_MODULE_3), false},
    #endif
    #ifdef UART3_TX_RB4_RP28
    {PB4, hal_ll_uart_module_num(UART_MODULE_3), false},
    #endif
    #ifdef UART3_TX_RB5_RP18
    {PB5, hal_ll_uart_module_num(UART_MODULE_3), false},
    #endif
    #ifdef UART3_TX_RB6_RP6
    {PB6, hal_ll_uart_module_num(UART_MODULE_3), false},
    #endif
    #ifdef UART3_TX_RB7_RP7
    {PB7, hal_ll_uart_module_num(UART_MODULE_3), false},
    #endif
    #ifdef UART3_TX_RB8_RP8
    {PB8, hal_ll_uart_module_num(UART_MODULE_3), false},
    #endif
    #ifdef UART3_TX_RB9_RP9
    {PB9, hal_ll_uart_module_num(UART_MODULE_3), false},
    #endif
    #ifdef UART3_TX_RD0_RP11
    {PD0, hal_ll_uart_module_num(UART_MODULE_3), false},
    #endif
    #ifdef UART3_TX_RD1_RP24
    {PD1, hal_ll_uart_module_num(UART_MODULE_3), false},
    #endif
    #ifdef UART3_TX_RD10_RP3
    {PD10, hal_ll_uart_module_num(UART_MODULE_3), false},
    #endif
    #ifdef UART3_TX_RD11_RP12
    {PD11, hal_ll_uart_module_num(UART_MODULE_3), false},
    #endif
    #ifdef UART3_TX_RD2_RP23
    {PD2, hal_ll_uart_module_num(UART_MODULE_3), false},
    #endif
    #ifdef UART3_TX_RD3_RP22
    {PD3, hal_ll_uart_module_num(UART_MODULE_3), false},
    #endif
    #ifdef UART3_TX_RD4_RP25
    {PD4, hal_ll_uart_module_num(UART_MODULE_3), false},
    #endif
    #ifdef UART3_TX_RD5_RP20
    {PD5, hal_ll_uart_module_num(UART_MODULE_3), false},
    #endif
    #ifdef UART3_TX_RD8_RP2
    {PD8, hal_ll_uart_module_num(UART_MODULE_3), false},
    #endif
    #ifdef UART3_TX_RD9_RP4
    {PD9, hal_ll_uart_module_num(UART_MODULE_3), false},
    #endif
    #ifdef UART3_TX_RF2_RP30
    {PF2, hal_ll_uart_module_num(UART_MODULE_3), false},
    #endif
    #ifdef UART3_TX_RF3_RP16
    {PF3, hal_ll_uart_module_num(UART_MODULE_3), false},
    #endif
    #ifdef UART3_TX_RF4_RP10
    {PF4, hal_ll_uart_module_num(UART_MODULE_3), false},
    #endif
    #ifdef UART3_TX_RF5_RP17
    {PF5, hal_ll_uart_module_num(UART_MODULE_3), false},
    #endif
    #ifdef UART3_TX_RG6_RP21
    {PG6, hal_ll_uart_module_num(UART_MODULE_3), false},
    #endif
    #ifdef UART3_TX_RG7_RP26
    {PG7, hal_ll_uart_module_num(UART_MODULE_3), false},
    #endif
    #ifdef UART3_TX_RG8_RP19
    {PG8, hal_ll_uart_module_num(UART_MODULE_3), false},
    #endif
    #ifdef UART3_TX_RG9_RP27
    {PG9, hal_ll_uart_module_num(UART_MODULE_3), false},
    #endif
    #ifdef UART4_TX_RB0_RP0
    {PB0, hal_ll_uart_module_num(UART_MODULE_4), false},
    #endif
    #ifdef UART4_TX_RB1_RP1
    {PB1, hal_ll_uart_module_num(UART_MODULE_4), false},
    #endif
    #ifdef UART4_TX_RB14_RP14
    {PB14, hal_ll_uart_module_num(UART_MODULE_4), false},
    #endif
    #ifdef UART4_TX_RB15_RP29
    {PB15, hal_ll_uart_module_num(UART_MODULE_4), false},
    #endif
    #ifdef UART4_TX_RB2_RP13
    {PB2, hal_ll_uart_module_num(UART_MODULE_4), false},
    #endif
    #ifdef UART4_TX_RB4_RP28
    {PB4, hal_ll_uart_module_num(UART_MODULE_4), false},
    #endif
    #ifdef UART4_TX_RB5_RP18
    {PB5, hal_ll_uart_module_num(UART_MODULE_4), false},
    #endif
    #ifdef UART4_TX_RB6_RP6
    {PB6, hal_ll_uart_module_num(UART_MODULE_4), false},
    #endif
    #ifdef UART4_TX_RB7_RP7
    {PB7, hal_ll_uart_module_num(UART_MODULE_4), false},
    #endif
    #ifdef UART4_TX_RB8_RP8
    {PB8, hal_ll_uart_module_num(UART_MODULE_4), false},
    #endif
    #ifdef UART4_TX_RB9_RP9
    {PB9, hal_ll_uart_module_num(UART_MODULE_4), false},
    #endif
    #ifdef UART4_TX_RD0_RP11
    {PD0, hal_ll_uart_module_num(UART_MODULE_4), false},
    #endif
    #ifdef UART4_TX_RD1_RP24
    {PD1, hal_ll_uart_module_num(UART_MODULE_4), false},
    #endif
    #ifdef UART4_TX_RD10_RP3
    {PD10, hal_ll_uart_module_num(UART_MODULE_4), false},
    #endif
    #ifdef UART4_TX_RD11_RP12
    {PD11, hal_ll_uart_module_num(UART_MODULE_4), false},
    #endif
    #ifdef UART4_TX_RD2_RP23
    {PD2, hal_ll_uart_module_num(UART_MODULE_4), false},
    #endif
    #ifdef UART4_TX_RD3_RP22
    {PD3, hal_ll_uart_module_num(UART_MODULE_4), false},
    #endif
    #ifdef UART4_TX_RD4_RP25
    {PD4, hal_ll_uart_module_num(UART_MODULE_4), false},
    #endif
    #ifdef UART4_TX_RD5_RP20
    {PD5, hal_ll_uart_module_num(UART_MODULE_4), false},
    #endif
    #ifdef UART4_TX_RD8_RP2
    {PD8, hal_ll_uart_module_num(UART_MODULE_4), false},
    #endif
    #ifdef UART4_TX_RD9_RP4
    {PD9, hal_ll_uart_module_num(UART_MODULE_4), false},
    #endif
    #ifdef UART4_TX_RF2_RP30
    {PF2, hal_ll_uart_module_num(UART_MODULE_4), false},
    #endif
    #ifdef UART4_TX_RF3_RP16
    {PF3, hal_ll_uart_module_num(UART_MODULE_4), false},
    #endif
    #ifdef UART4_TX_RF4_RP10
    {PF4, hal_ll_uart_module_num(UART_MODULE_4), false},
    #endif
    #ifdef UART4_TX_RF5_RP17
    {PF5, hal_ll_uart_module_num(UART_MODULE_4), false},
    #endif
    #ifdef UART4_TX_RG6_RP21
    {PG6, hal_ll_uart_module_num(UART_MODULE_4), false},
    #endif
    #ifdef UART4_TX_RG7_RP26
    {PG7, hal_ll_uart_module_num(UART_MODULE_4), false},
    #endif
    #ifdef UART4_TX_RG8_RP19
    {PG8, hal_ll_uart_module_num(UART_MODULE_4), false},
    #endif
    #ifdef UART4_TX_RG9_RP27
    {PG9, hal_ll_uart_module_num(UART_MODULE_4), false},
    #endif
    #ifdef UART5_TX_RD1
    {PD1, hal_ll_uart_module_num(UART_MODULE_5), false},
    #endif
    #ifdef UART6_TX_RB7
    {PB7, hal_ll_uart_module_num(UART_MODULE_6), false},
    #endif
    #ifdef UART1_TX_RD15_RP5
    {PD15, hal_ll_uart_module_num(UART_MODULE_1), false},
    #endif
    #ifdef UART1_TX_RF13_RP31
    {PF13, hal_ll_uart_module_num(UART_MODULE_1), false},
    #endif
    #ifdef UART1_TX_RF8_RP15
    {PF8, hal_ll_uart_module_num(UART_MODULE_1), false},
    #endif
    #ifdef UART2_TX_RD15_RP5
    {PD15, hal_ll_uart_module_num(UART_MODULE_2), false},
    #endif
    #ifdef UART2_TX_RF13_RP31
    {PF13, hal_ll_uart_module_num(UART_MODULE_2), false},
    #endif
    #ifdef UART2_TX_RF8_RP15
    {PF8, hal_ll_uart_module_num(UART_MODULE_2), false},
    #endif
    #ifdef UART3_TX_RD15_RP5
    {PD15, hal_ll_uart_module_num(UART_MODULE_3), false},
    #endif
    #ifdef UART3_TX_RF13_RP31
    {PF13, hal_ll_uart_module_num(UART_MODULE_3), false},
    #endif
    #ifdef UART3_TX_RF8_RP15
    {PF8, hal_ll_uart_module_num(UART_MODULE_3), false},
    #endif
    #ifdef UART4_TX_RD15_RP5
    {PD15, hal_ll_uart_module_num(UART_MODULE_4), false},
    #endif
    #ifdef UART4_TX_RF13_RP31
    {PF13, hal_ll_uart_module_num(UART_MODULE_4), false},
    #endif
    #ifdef UART4_TX_RF8_RP15
    {PF8, hal_ll_uart_module_num(UART_MODULE_4), false},
    #endif
    #ifdef UART3_TX_RB10_RP10
    {PB10, hal_ll_uart_module_num(UART_MODULE_3), false},
    #endif
    #ifdef UART3_TX_RB11_RP11
    {PB11, hal_ll_uart_module_num(UART_MODULE_3), false},
    #endif
    #ifdef UART3_TX_RB12_RP12
    {PB12, hal_ll_uart_module_num(UART_MODULE_3), false},
    #endif
    #ifdef UART3_TX_RB13_RP13
    {PB13, hal_ll_uart_module_num(UART_MODULE_3), false},
    #endif
    #ifdef UART3_TX_RB15_RP15
    {PB15, hal_ll_uart_module_num(UART_MODULE_3), false},
    #endif
    #ifdef UART3_TX_RB2_RP2
    {PB2, hal_ll_uart_module_num(UART_MODULE_3), false},
    #endif
    #ifdef UART3_TX_RB3_RP3
    {PB3, hal_ll_uart_module_num(UART_MODULE_3), false},
    #endif
    #ifdef UART3_TX_RB5_RP5
    {PB5, hal_ll_uart_module_num(UART_MODULE_3), false},
    #endif
    #ifdef UART4_TX_RB10_RP10
    {PB10, hal_ll_uart_module_num(UART_MODULE_4), false},
    #endif
    #ifdef UART4_TX_RB11_RP11
    {PB11, hal_ll_uart_module_num(UART_MODULE_4), false},
    #endif
    #ifdef UART4_TX_RB12_RP12
    {PB12, hal_ll_uart_module_num(UART_MODULE_4), false},
    #endif
    #ifdef UART4_TX_RB13_RP13
    {PB13, hal_ll_uart_module_num(UART_MODULE_4), false},
    #endif
    #ifdef UART4_TX_RB15_RP15
    {PB15, hal_ll_uart_module_num(UART_MODULE_4), false},
    #endif
    #ifdef UART4_TX_RB2_RP2
    {PB2, hal_ll_uart_module_num(UART_MODULE_4), false},
    #endif
    #ifdef UART4_TX_RB3_RP3
    {PB3, hal_ll_uart_module_num(UART_MODULE_4), false},
    #endif
    #ifdef UART4_TX_RB5_RP5
    {PB5, hal_ll_uart_module_num(UART_MODULE_4), false},
    #endif
    #ifdef UART3_TX_RC0_RP16
    {PC0, hal_ll_uart_module_num(UART_MODULE_3), false},
    #endif
    #ifdef UART3_TX_RC1_RP17
    {PC1, hal_ll_uart_module_num(UART_MODULE_3), false},
    #endif
    #ifdef UART3_TX_RC2_RP18
    {PC2, hal_ll_uart_module_num(UART_MODULE_3), false},
    #endif
    #ifdef UART3_TX_RC3_RP19
    {PC3, hal_ll_uart_module_num(UART_MODULE_3), false},
    #endif
    #ifdef UART3_TX_RC4_RP20
    {PC4, hal_ll_uart_module_num(UART_MODULE_3), false},
    #endif
    #ifdef UART3_TX_RC5_RP21
    {PC5, hal_ll_uart_module_num(UART_MODULE_3), false},
    #endif
    #ifdef UART3_TX_RC6_RP22
    {PC6, hal_ll_uart_module_num(UART_MODULE_3), false},
    #endif
    #ifdef UART3_TX_RC7_RP23
    {PC7, hal_ll_uart_module_num(UART_MODULE_3), false},
    #endif
    #ifdef UART3_TX_RC8_RP24
    {PC8, hal_ll_uart_module_num(UART_MODULE_3), false},
    #endif
    #ifdef UART3_TX_RC9_RP25
    {PC9, hal_ll_uart_module_num(UART_MODULE_3), false},
    #endif
    #ifdef UART4_TX_RC0_RP16
    {PC0, hal_ll_uart_module_num(UART_MODULE_4), false},
    #endif
    #ifdef UART4_TX_RC1_RP17
    {PC1, hal_ll_uart_module_num(UART_MODULE_4), false},
    #endif
    #ifdef UART4_TX_RC2_RP18
    {PC2, hal_ll_uart_module_num(UART_MODULE_4), false},
    #endif
    #ifdef UART4_TX_RC3_RP19
    {PC3, hal_ll_uart_module_num(UART_MODULE_4), false},
    #endif
    #ifdef UART4_TX_RC4_RP20
    {PC4, hal_ll_uart_module_num(UART_MODULE_4), false},
    #endif
    #ifdef UART4_TX_RC5_RP21
    {PC5, hal_ll_uart_module_num(UART_MODULE_4), false},
    #endif
    #ifdef UART4_TX_RC6_RP22
    {PC6, hal_ll_uart_module_num(UART_MODULE_4), false},
    #endif
    #ifdef UART4_TX_RC7_RP23
    {PC7, hal_ll_uart_module_num(UART_MODULE_4), false},
    #endif
    #ifdef UART4_TX_RC8_RP24
    {PC8, hal_ll_uart_module_num(UART_MODULE_4), false},
    #endif
    #ifdef UART4_TX_RC9_RP25
    {PC9, hal_ll_uart_module_num(UART_MODULE_4), false},
    #endif
    #ifdef UART1_TX_RA0_RP26
    {PA0, hal_ll_uart_module_num(UART_MODULE_1), false},
    #endif
    #ifdef UART1_TX_RA1_RP27
    {PA1, hal_ll_uart_module_num(UART_MODULE_1), false},
    #endif
    #ifdef UART2_TX_RA0_RP26
    {PA0, hal_ll_uart_module_num(UART_MODULE_2), false},
    #endif
    #ifdef UART2_TX_RA1_RP27
    {PA1, hal_ll_uart_module_num(UART_MODULE_2), false},
    #endif
    #ifdef UART1_TX_RA10_RP28
    {PA10, hal_ll_uart_module_num(UART_MODULE_1), false},
    #endif
    #ifdef UART2_TX_RA10_RP28
    {PA10, hal_ll_uart_module_num(UART_MODULE_2), false},
    #endif
    #ifdef UART1_TX_RA0_RP5
    {PA0, hal_ll_uart_module_num(UART_MODULE_1), false},
    #endif
    #ifdef UART1_TX_RA1_RP6
    {PA1, hal_ll_uart_module_num(UART_MODULE_1), false},
    #endif
    #ifdef UART2_TX_RA0_RP5
    {PA0, hal_ll_uart_module_num(UART_MODULE_2), false},
    #endif
    #ifdef UART2_TX_RA1_RP6
    {PA1, hal_ll_uart_module_num(UART_MODULE_2), false},
    #endif
    #ifdef UART3_TX_RA0_RP5
    {PA0, hal_ll_uart_module_num(UART_MODULE_3), false},
    #endif
    #ifdef UART3_TX_RA1_RP6
    {PA1, hal_ll_uart_module_num(UART_MODULE_3), false},
    #endif
    #ifdef UART4_TX_RA0_RP5
    {PA0, hal_ll_uart_module_num(UART_MODULE_4), false},
    #endif
    #ifdef UART4_TX_RA1_RP6
    {PA1, hal_ll_uart_module_num(UART_MODULE_4), false},
    #endif
    { HAL_LL_PIN_NC, HAL_LL_MODULE_ERROR, false }
    //------------ END TX
};

/*!< @brief UART RX pins */
static const hal_ll_uart_pin_map_t hal_ll_uart_rx_map[] = {
    //------------ BEGIN RX
    #ifdef UART1_RX_RB5
    {PB5, hal_ll_uart_module_num(UART_MODULE_1), false},
    #endif
    #ifdef UART1_RX_RC14_ALT
    {PC14, hal_ll_uart_module_num(UART_MODULE_1), true},
    #endif
    #ifdef UART1_RX_RF2
    {PF2, hal_ll_uart_module_num(UART_MODULE_1), false},
    #endif
    #ifdef UART2_RX_RF4
    {PF4, hal_ll_uart_module_num(UART_MODULE_2), false},
    #endif
    #ifdef UART1_RX_RA0_RPI16
    {PA0, hal_ll_uart_module_num(UART_MODULE_1), false},
    #endif
    #ifdef UART1_RX_RA1_RPI17
    {PA1, hal_ll_uart_module_num(UART_MODULE_1), false},
    #endif
    #ifdef UART1_RX_RA2_RPI18
    {PA2, hal_ll_uart_module_num(UART_MODULE_1), false},
    #endif
    #ifdef UART1_RX_RA3_RPI19
    {PA3, hal_ll_uart_module_num(UART_MODULE_1), false},
    #endif
    #ifdef UART1_RX_RA4_RP20
    {PA4, hal_ll_uart_module_num(UART_MODULE_1), false},
    #endif
    #ifdef UART1_RX_RA8_RPI24
    {PA8, hal_ll_uart_module_num(UART_MODULE_1), false},
    #endif
    #ifdef UART1_RX_RA9_RPI25
    {PA9, hal_ll_uart_module_num(UART_MODULE_1), false},
    #endif
    #ifdef UART1_RX_RB0_RPI32
    {PB0, hal_ll_uart_module_num(UART_MODULE_1), false},
    #endif
    #ifdef UART1_RX_RB1_RPI33
    {PB1, hal_ll_uart_module_num(UART_MODULE_1), false},
    #endif
    #ifdef UART1_RX_RB10_RP42
    {PB10, hal_ll_uart_module_num(UART_MODULE_1), false},
    #endif
    #ifdef UART1_RX_RB11_RP43
    {PB11, hal_ll_uart_module_num(UART_MODULE_1), false},
    #endif
    #ifdef UART1_RX_RB12_RPI44
    {PB12, hal_ll_uart_module_num(UART_MODULE_1), false},
    #endif
    #ifdef UART1_RX_RB13_RPI45
    {PB13, hal_ll_uart_module_num(UART_MODULE_1), false},
    #endif
    #ifdef UART1_RX_RB14_RPI46
    {PB14, hal_ll_uart_module_num(UART_MODULE_1), false},
    #endif
    #ifdef UART1_RX_RB15_RPI47
    {PB15, hal_ll_uart_module_num(UART_MODULE_1), false},
    #endif
    #ifdef UART1_RX_RB2_RPI34
    {PB2, hal_ll_uart_module_num(UART_MODULE_1), false},
    #endif
    #ifdef UART1_RX_RB3_RP35
    {PB3, hal_ll_uart_module_num(UART_MODULE_1), false},
    #endif
    #ifdef UART1_RX_RB4_RP36
    {PB4, hal_ll_uart_module_num(UART_MODULE_1), false},
    #endif
    #ifdef UART1_RX_RB5_RP37
    {PB5, hal_ll_uart_module_num(UART_MODULE_1), false},
    #endif
    #ifdef UART1_RX_RB6_RP38
    {PB6, hal_ll_uart_module_num(UART_MODULE_1), false},
    #endif
    #ifdef UART1_RX_RB7_RP39
    {PB7, hal_ll_uart_module_num(UART_MODULE_1), false},
    #endif
    #ifdef UART1_RX_RB8_RP40
    {PB8, hal_ll_uart_module_num(UART_MODULE_1), false},
    #endif
    #ifdef UART1_RX_RB9_RP41
    {PB9, hal_ll_uart_module_num(UART_MODULE_1), false},
    #endif
    #ifdef UART1_RX_RC0_RP48
    {PC0, hal_ll_uart_module_num(UART_MODULE_1), false},
    #endif
    #ifdef UART1_RX_RC1_RP49
    {PC1, hal_ll_uart_module_num(UART_MODULE_1), false},
    #endif
    #ifdef UART1_RX_RC2_RPI50
    {PC2, hal_ll_uart_module_num(UART_MODULE_1), false},
    #endif
    #ifdef UART1_RX_RC3_RPI51
    {PC3, hal_ll_uart_module_num(UART_MODULE_1), false},
    #endif
    #ifdef UART1_RX_RC4_RPI52
    {PC4, hal_ll_uart_module_num(UART_MODULE_1), false},
    #endif
    #ifdef UART1_RX_RC5_RPI53
    {PC5, hal_ll_uart_module_num(UART_MODULE_1), false},
    #endif
    #ifdef UART1_RX_RC6_RP54
    {PC6, hal_ll_uart_module_num(UART_MODULE_1), false},
    #endif
    #ifdef UART1_RX_RC7_RP55
    {PC7, hal_ll_uart_module_num(UART_MODULE_1), false},
    #endif
    #ifdef UART1_RX_RC8_RP56
    {PC8, hal_ll_uart_module_num(UART_MODULE_1), false},
    #endif
    #ifdef UART1_RX_RC9_RP57
    {PC9, hal_ll_uart_module_num(UART_MODULE_1), false},
    #endif
    #ifdef UART2_RX_RA0_RPI16
    {PA0, hal_ll_uart_module_num(UART_MODULE_2), false},
    #endif
    #ifdef UART2_RX_RA1_RPI17
    {PA1, hal_ll_uart_module_num(UART_MODULE_2), false},
    #endif
    #ifdef UART2_RX_RA2_RPI18
    {PA2, hal_ll_uart_module_num(UART_MODULE_2), false},
    #endif
    #ifdef UART2_RX_RA3_RPI19
    {PA3, hal_ll_uart_module_num(UART_MODULE_2), false},
    #endif
    #ifdef UART2_RX_RA4_RP20
    {PA4, hal_ll_uart_module_num(UART_MODULE_2), false},
    #endif
    #ifdef UART2_RX_RA8_RPI24
    {PA8, hal_ll_uart_module_num(UART_MODULE_2), false},
    #endif
    #ifdef UART2_RX_RA9_RPI25
    {PA9, hal_ll_uart_module_num(UART_MODULE_2), false},
    #endif
    #ifdef UART2_RX_RB0_RPI32
    {PB0, hal_ll_uart_module_num(UART_MODULE_2), false},
    #endif
    #ifdef UART2_RX_RB1_RPI33
    {PB1, hal_ll_uart_module_num(UART_MODULE_2), false},
    #endif
    #ifdef UART2_RX_RB10_RP42
    {PB10, hal_ll_uart_module_num(UART_MODULE_2), false},
    #endif
    #ifdef UART2_RX_RB11_RP43
    {PB11, hal_ll_uart_module_num(UART_MODULE_2), false},
    #endif
    #ifdef UART2_RX_RB12_RPI44
    {PB12, hal_ll_uart_module_num(UART_MODULE_2), false},
    #endif
    #ifdef UART2_RX_RB13_RPI45
    {PB13, hal_ll_uart_module_num(UART_MODULE_2), false},
    #endif
    #ifdef UART2_RX_RB14_RPI46
    {PB14, hal_ll_uart_module_num(UART_MODULE_2), false},
    #endif
    #ifdef UART2_RX_RB15_RPI47
    {PB15, hal_ll_uart_module_num(UART_MODULE_2), false},
    #endif
    #ifdef UART2_RX_RB2_RPI34
    {PB2, hal_ll_uart_module_num(UART_MODULE_2), false},
    #endif
    #ifdef UART2_RX_RB3_RP35
    {PB3, hal_ll_uart_module_num(UART_MODULE_2), false},
    #endif
    #ifdef UART2_RX_RB4_RP36
    {PB4, hal_ll_uart_module_num(UART_MODULE_2), false},
    #endif
    #ifdef UART2_RX_RB5_RP37
    {PB5, hal_ll_uart_module_num(UART_MODULE_2), false},
    #endif
    #ifdef UART2_RX_RB6_RP38
    {PB6, hal_ll_uart_module_num(UART_MODULE_2), false},
    #endif
    #ifdef UART2_RX_RB7_RP39
    {PB7, hal_ll_uart_module_num(UART_MODULE_2), false},
    #endif
    #ifdef UART2_RX_RB8_RP40
    {PB8, hal_ll_uart_module_num(UART_MODULE_2), false},
    #endif
    #ifdef UART2_RX_RB9_RP41
    {PB9, hal_ll_uart_module_num(UART_MODULE_2), false},
    #endif
    #ifdef UART2_RX_RC0_RP48
    {PC0, hal_ll_uart_module_num(UART_MODULE_2), false},
    #endif
    #ifdef UART2_RX_RC1_RP49
    {PC1, hal_ll_uart_module_num(UART_MODULE_2), false},
    #endif
    #ifdef UART2_RX_RC2_RPI50
    {PC2, hal_ll_uart_module_num(UART_MODULE_2), false},
    #endif
    #ifdef UART2_RX_RC3_RPI51
    {PC3, hal_ll_uart_module_num(UART_MODULE_2), false},
    #endif
    #ifdef UART2_RX_RC4_RPI52
    {PC4, hal_ll_uart_module_num(UART_MODULE_2), false},
    #endif
    #ifdef UART2_RX_RC5_RPI53
    {PC5, hal_ll_uart_module_num(UART_MODULE_2), false},
    #endif
    #ifdef UART2_RX_RC6_RP54
    {PC6, hal_ll_uart_module_num(UART_MODULE_2), false},
    #endif
    #ifdef UART2_RX_RC7_RP55
    {PC7, hal_ll_uart_module_num(UART_MODULE_2), false},
    #endif
    #ifdef UART2_RX_RC8_RP56
    {PC8, hal_ll_uart_module_num(UART_MODULE_2), false},
    #endif
    #ifdef UART2_RX_RC9_RP57
    {PC9, hal_ll_uart_module_num(UART_MODULE_2), false},
    #endif
    #ifdef UART3_RX_RA0_RPI16
    {PA0, hal_ll_uart_module_num(UART_MODULE_3), false},
    #endif
    #ifdef UART3_RX_RA1_RPI17
    {PA1, hal_ll_uart_module_num(UART_MODULE_3), false},
    #endif
    #ifdef UART3_RX_RA2_RPI18
    {PA2, hal_ll_uart_module_num(UART_MODULE_3), false},
    #endif
    #ifdef UART3_RX_RA3_RPI19
    {PA3, hal_ll_uart_module_num(UART_MODULE_3), false},
    #endif
    #ifdef UART3_RX_RA4_RP20
    {PA4, hal_ll_uart_module_num(UART_MODULE_3), false},
    #endif
    #ifdef UART3_RX_RA8_RPI24
    {PA8, hal_ll_uart_module_num(UART_MODULE_3), false},
    #endif
    #ifdef UART3_RX_RA9_RPI25
    {PA9, hal_ll_uart_module_num(UART_MODULE_3), false},
    #endif
    #ifdef UART3_RX_RB0_RPI32
    {PB0, hal_ll_uart_module_num(UART_MODULE_3), false},
    #endif
    #ifdef UART3_RX_RB1_RPI33
    {PB1, hal_ll_uart_module_num(UART_MODULE_3), false},
    #endif
    #ifdef UART3_RX_RB10_RP42
    {PB10, hal_ll_uart_module_num(UART_MODULE_3), false},
    #endif
    #ifdef UART3_RX_RB11_RP43
    {PB11, hal_ll_uart_module_num(UART_MODULE_3), false},
    #endif
    #ifdef UART3_RX_RB12_RPI44
    {PB12, hal_ll_uart_module_num(UART_MODULE_3), false},
    #endif
    #ifdef UART3_RX_RB13_RPI45
    {PB13, hal_ll_uart_module_num(UART_MODULE_3), false},
    #endif
    #ifdef UART3_RX_RB14_RPI46
    {PB14, hal_ll_uart_module_num(UART_MODULE_3), false},
    #endif
    #ifdef UART3_RX_RB15_RPI47
    {PB15, hal_ll_uart_module_num(UART_MODULE_3), false},
    #endif
    #ifdef UART3_RX_RB2_RPI34
    {PB2, hal_ll_uart_module_num(UART_MODULE_3), false},
    #endif
    #ifdef UART3_RX_RB3_RP35
    {PB3, hal_ll_uart_module_num(UART_MODULE_3), false},
    #endif
    #ifdef UART3_RX_RB4_RP36
    {PB4, hal_ll_uart_module_num(UART_MODULE_3), false},
    #endif
    #ifdef UART3_RX_RB5_RP37
    {PB5, hal_ll_uart_module_num(UART_MODULE_3), false},
    #endif
    #ifdef UART3_RX_RB6_RP38
    {PB6, hal_ll_uart_module_num(UART_MODULE_3), false},
    #endif
    #ifdef UART3_RX_RB7_RP39
    {PB7, hal_ll_uart_module_num(UART_MODULE_3), false},
    #endif
    #ifdef UART3_RX_RB8_RP40
    {PB8, hal_ll_uart_module_num(UART_MODULE_3), false},
    #endif
    #ifdef UART3_RX_RB9_RP41
    {PB9, hal_ll_uart_module_num(UART_MODULE_3), false},
    #endif
    #ifdef UART3_RX_RC0_RP48
    {PC0, hal_ll_uart_module_num(UART_MODULE_3), false},
    #endif
    #ifdef UART3_RX_RC1_RP49
    {PC1, hal_ll_uart_module_num(UART_MODULE_3), false},
    #endif
    #ifdef UART3_RX_RC2_RPI50
    {PC2, hal_ll_uart_module_num(UART_MODULE_3), false},
    #endif
    #ifdef UART3_RX_RC3_RPI51
    {PC3, hal_ll_uart_module_num(UART_MODULE_3), false},
    #endif
    #ifdef UART3_RX_RC4_RPI52
    {PC4, hal_ll_uart_module_num(UART_MODULE_3), false},
    #endif
    #ifdef UART3_RX_RC5_RPI53
    {PC5, hal_ll_uart_module_num(UART_MODULE_3), false},
    #endif
    #ifdef UART3_RX_RC6_RP54
    {PC6, hal_ll_uart_module_num(UART_MODULE_3), false},
    #endif
    #ifdef UART3_RX_RC7_RP55
    {PC7, hal_ll_uart_module_num(UART_MODULE_3), false},
    #endif
    #ifdef UART3_RX_RC8_RP56
    {PC8, hal_ll_uart_module_num(UART_MODULE_3), false},
    #endif
    #ifdef UART3_RX_RC9_RP57
    {PC9, hal_ll_uart_module_num(UART_MODULE_3), false},
    #endif
    #ifdef UART4_RX_RA0_RPI16
    {PA0, hal_ll_uart_module_num(UART_MODULE_4), false},
    #endif
    #ifdef UART4_RX_RA1_RPI17
    {PA1, hal_ll_uart_module_num(UART_MODULE_4), false},
    #endif
    #ifdef UART4_RX_RA2_RPI18
    {PA2, hal_ll_uart_module_num(UART_MODULE_4), false},
    #endif
    #ifdef UART4_RX_RA3_RPI19
    {PA3, hal_ll_uart_module_num(UART_MODULE_4), false},
    #endif
    #ifdef UART4_RX_RA4_RP20
    {PA4, hal_ll_uart_module_num(UART_MODULE_4), false},
    #endif
    #ifdef UART4_RX_RA8_RPI24
    {PA8, hal_ll_uart_module_num(UART_MODULE_4), false},
    #endif
    #ifdef UART4_RX_RA9_RPI25
    {PA9, hal_ll_uart_module_num(UART_MODULE_4), false},
    #endif
    #ifdef UART4_RX_RB0_RPI32
    {PB0, hal_ll_uart_module_num(UART_MODULE_4), false},
    #endif
    #ifdef UART4_RX_RB1_RPI33
    {PB1, hal_ll_uart_module_num(UART_MODULE_4), false},
    #endif
    #ifdef UART4_RX_RB10_RP42
    {PB10, hal_ll_uart_module_num(UART_MODULE_4), false},
    #endif
    #ifdef UART4_RX_RB11_RP43
    {PB11, hal_ll_uart_module_num(UART_MODULE_4), false},
    #endif
    #ifdef UART4_RX_RB12_RPI44
    {PB12, hal_ll_uart_module_num(UART_MODULE_4), false},
    #endif
    #ifdef UART4_RX_RB13_RPI45
    {PB13, hal_ll_uart_module_num(UART_MODULE_4), false},
    #endif
    #ifdef UART4_RX_RB14_RPI46
    {PB14, hal_ll_uart_module_num(UART_MODULE_4), false},
    #endif
    #ifdef UART4_RX_RB15_RPI47
    {PB15, hal_ll_uart_module_num(UART_MODULE_4), false},
    #endif
    #ifdef UART4_RX_RB2_RPI34
    {PB2, hal_ll_uart_module_num(UART_MODULE_4), false},
    #endif
    #ifdef UART4_RX_RB3_RP35
    {PB3, hal_ll_uart_module_num(UART_MODULE_4), false},
    #endif
    #ifdef UART4_RX_RB4_RP36
    {PB4, hal_ll_uart_module_num(UART_MODULE_4), false},
    #endif
    #ifdef UART4_RX_RB5_RP37
    {PB5, hal_ll_uart_module_num(UART_MODULE_4), false},
    #endif
    #ifdef UART4_RX_RB6_RP38
    {PB6, hal_ll_uart_module_num(UART_MODULE_4), false},
    #endif
    #ifdef UART4_RX_RB7_RP39
    {PB7, hal_ll_uart_module_num(UART_MODULE_4), false},
    #endif
    #ifdef UART4_RX_RB8_RP40
    {PB8, hal_ll_uart_module_num(UART_MODULE_4), false},
    #endif
    #ifdef UART4_RX_RB9_RP41
    {PB9, hal_ll_uart_module_num(UART_MODULE_4), false},
    #endif
    #ifdef UART4_RX_RC0_RP48
    {PC0, hal_ll_uart_module_num(UART_MODULE_4), false},
    #endif
    #ifdef UART4_RX_RC1_RP49
    {PC1, hal_ll_uart_module_num(UART_MODULE_4), false},
    #endif
    #ifdef UART4_RX_RC2_RPI50
    {PC2, hal_ll_uart_module_num(UART_MODULE_4), false},
    #endif
    #ifdef UART4_RX_RC3_RPI51
    {PC3, hal_ll_uart_module_num(UART_MODULE_4), false},
    #endif
    #ifdef UART4_RX_RC4_RPI52
    {PC4, hal_ll_uart_module_num(UART_MODULE_4), false},
    #endif
    #ifdef UART4_RX_RC5_RPI53
    {PC5, hal_ll_uart_module_num(UART_MODULE_4), false},
    #endif
    #ifdef UART4_RX_RC6_RP54
    {PC6, hal_ll_uart_module_num(UART_MODULE_4), false},
    #endif
    #ifdef UART4_RX_RC7_RP55
    {PC7, hal_ll_uart_module_num(UART_MODULE_4), false},
    #endif
    #ifdef UART4_RX_RC8_RP56
    {PC8, hal_ll_uart_module_num(UART_MODULE_4), false},
    #endif
    #ifdef UART4_RX_RC9_RP57
    {PC9, hal_ll_uart_module_num(UART_MODULE_4), false},
    #endif
    #ifdef UART1_RX_RA11_RPI27
    {PA11, hal_ll_uart_module_num(UART_MODULE_1), false},
    #endif
    #ifdef UART1_RX_RA12_RPI28
    {PA12, hal_ll_uart_module_num(UART_MODULE_1), false},
    #endif
    #ifdef UART1_RX_RC10_RPI58
    {PC10, hal_ll_uart_module_num(UART_MODULE_1), false},
    #endif
    #ifdef UART1_RX_RC12_RPI60
    {PC12, hal_ll_uart_module_num(UART_MODULE_1), false},
    #endif
    #ifdef UART1_RX_RC13_RPI61
    {PC13, hal_ll_uart_module_num(UART_MODULE_1), false},
    #endif
    #ifdef UART1_RX_RC15_RPI63
    {PC15, hal_ll_uart_module_num(UART_MODULE_1), false},
    #endif
    #ifdef UART1_RX_RD5_RP69
    {PD5, hal_ll_uart_module_num(UART_MODULE_1), false},
    #endif
    #ifdef UART1_RX_RD6_RP70
    {PD6, hal_ll_uart_module_num(UART_MODULE_1), false},
    #endif
    #ifdef UART1_RX_RD8_RPI72
    {PD8, hal_ll_uart_module_num(UART_MODULE_1), false},
    #endif
    #ifdef UART1_RX_RE14_RPI94
    {PE14, hal_ll_uart_module_num(UART_MODULE_1), false},
    #endif
    #ifdef UART1_RX_RE15_RPI95
    {PE15, hal_ll_uart_module_num(UART_MODULE_1), false},
    #endif
    #ifdef UART1_RX_RF0_RPI96
    {PF0, hal_ll_uart_module_num(UART_MODULE_1), false},
    #endif
    #ifdef UART1_RX_RF1_RP97
    {PF1, hal_ll_uart_module_num(UART_MODULE_1), false},
    #endif
    #ifdef UART1_RX_RG6_RP118
    {PG6, hal_ll_uart_module_num(UART_MODULE_1), false},
    #endif
    #ifdef UART1_RX_RG7_RPI119
    {PG7, hal_ll_uart_module_num(UART_MODULE_1), false},
    #endif
    #ifdef UART1_RX_RG8_RP120
    {PG8, hal_ll_uart_module_num(UART_MODULE_1), false},
    #endif
    #ifdef UART1_RX_RG9_RPI121
    {PG9, hal_ll_uart_module_num(UART_MODULE_1), false},
    #endif
    #ifdef UART2_RX_RA11_RPI27
    {PA11, hal_ll_uart_module_num(UART_MODULE_2), false},
    #endif
    #ifdef UART2_RX_RA12_RPI28
    {PA12, hal_ll_uart_module_num(UART_MODULE_2), false},
    #endif
    #ifdef UART2_RX_RC10_RPI58
    {PC10, hal_ll_uart_module_num(UART_MODULE_2), false},
    #endif
    #ifdef UART2_RX_RC12_RPI60
    {PC12, hal_ll_uart_module_num(UART_MODULE_2), false},
    #endif
    #ifdef UART2_RX_RC13_RPI61
    {PC13, hal_ll_uart_module_num(UART_MODULE_2), false},
    #endif
    #ifdef UART2_RX_RC15_RPI63
    {PC15, hal_ll_uart_module_num(UART_MODULE_2), false},
    #endif
    #ifdef UART2_RX_RD5_RP69
    {PD5, hal_ll_uart_module_num(UART_MODULE_2), false},
    #endif
    #ifdef UART2_RX_RD6_RP70
    {PD6, hal_ll_uart_module_num(UART_MODULE_2), false},
    #endif
    #ifdef UART2_RX_RD8_RPI72
    {PD8, hal_ll_uart_module_num(UART_MODULE_2), false},
    #endif
    #ifdef UART2_RX_RE14_RPI94
    {PE14, hal_ll_uart_module_num(UART_MODULE_2), false},
    #endif
    #ifdef UART2_RX_RE15_RPI95
    {PE15, hal_ll_uart_module_num(UART_MODULE_2), false},
    #endif
    #ifdef UART2_RX_RF0_RPI96
    {PF0, hal_ll_uart_module_num(UART_MODULE_2), false},
    #endif
    #ifdef UART2_RX_RF1_RP97
    {PF1, hal_ll_uart_module_num(UART_MODULE_2), false},
    #endif
    #ifdef UART2_RX_RG6_RP118
    {PG6, hal_ll_uart_module_num(UART_MODULE_2), false},
    #endif
    #ifdef UART2_RX_RG7_RPI119
    {PG7, hal_ll_uart_module_num(UART_MODULE_2), false},
    #endif
    #ifdef UART2_RX_RG8_RP120
    {PG8, hal_ll_uart_module_num(UART_MODULE_2), false},
    #endif
    #ifdef UART2_RX_RG9_RPI121
    {PG9, hal_ll_uart_module_num(UART_MODULE_2), false},
    #endif
    #ifdef UART3_RX_RA11_RPI27
    {PA11, hal_ll_uart_module_num(UART_MODULE_3), false},
    #endif
    #ifdef UART3_RX_RA12_RPI28
    {PA12, hal_ll_uart_module_num(UART_MODULE_3), false},
    #endif
    #ifdef UART3_RX_RC10_RPI58
    {PC10, hal_ll_uart_module_num(UART_MODULE_3), false},
    #endif
    #ifdef UART3_RX_RC12_RPI60
    {PC12, hal_ll_uart_module_num(UART_MODULE_3), false},
    #endif
    #ifdef UART3_RX_RC13_RPI61
    {PC13, hal_ll_uart_module_num(UART_MODULE_3), false},
    #endif
    #ifdef UART3_RX_RC15_RPI63
    {PC15, hal_ll_uart_module_num(UART_MODULE_3), false},
    #endif
    #ifdef UART3_RX_RD5_RP69
    {PD5, hal_ll_uart_module_num(UART_MODULE_3), false},
    #endif
    #ifdef UART3_RX_RD6_RP70
    {PD6, hal_ll_uart_module_num(UART_MODULE_3), false},
    #endif
    #ifdef UART3_RX_RD8_RPI72
    {PD8, hal_ll_uart_module_num(UART_MODULE_3), false},
    #endif
    #ifdef UART3_RX_RE14_RPI94
    {PE14, hal_ll_uart_module_num(UART_MODULE_3), false},
    #endif
    #ifdef UART3_RX_RE15_RPI95
    {PE15, hal_ll_uart_module_num(UART_MODULE_3), false},
    #endif
    #ifdef UART3_RX_RF0_RPI96
    {PF0, hal_ll_uart_module_num(UART_MODULE_3), false},
    #endif
    #ifdef UART3_RX_RF1_RP97
    {PF1, hal_ll_uart_module_num(UART_MODULE_3), false},
    #endif
    #ifdef UART3_RX_RG6_RP118
    {PG6, hal_ll_uart_module_num(UART_MODULE_3), false},
    #endif
    #ifdef UART3_RX_RG7_RPI119
    {PG7, hal_ll_uart_module_num(UART_MODULE_3), false},
    #endif
    #ifdef UART3_RX_RG8_RP120
    {PG8, hal_ll_uart_module_num(UART_MODULE_3), false},
    #endif
    #ifdef UART3_RX_RG9_RPI121
    {PG9, hal_ll_uart_module_num(UART_MODULE_3), false},
    #endif
    #ifdef UART4_RX_RA11_RPI27
    {PA11, hal_ll_uart_module_num(UART_MODULE_4), false},
    #endif
    #ifdef UART4_RX_RA12_RPI28
    {PA12, hal_ll_uart_module_num(UART_MODULE_4), false},
    #endif
    #ifdef UART4_RX_RC10_RPI58
    {PC10, hal_ll_uart_module_num(UART_MODULE_4), false},
    #endif
    #ifdef UART4_RX_RC12_RPI60
    {PC12, hal_ll_uart_module_num(UART_MODULE_4), false},
    #endif
    #ifdef UART4_RX_RC13_RPI61
    {PC13, hal_ll_uart_module_num(UART_MODULE_4), false},
    #endif
    #ifdef UART4_RX_RC15_RPI63
    {PC15, hal_ll_uart_module_num(UART_MODULE_4), false},
    #endif
    #ifdef UART4_RX_RD5_RP69
    {PD5, hal_ll_uart_module_num(UART_MODULE_4), false},
    #endif
    #ifdef UART4_RX_RD6_RP70
    {PD6, hal_ll_uart_module_num(UART_MODULE_4), false},
    #endif
    #ifdef UART4_RX_RD8_RPI72
    {PD8, hal_ll_uart_module_num(UART_MODULE_4), false},
    #endif
    #ifdef UART4_RX_RE14_RPI94
    {PE14, hal_ll_uart_module_num(UART_MODULE_4), false},
    #endif
    #ifdef UART4_RX_RE15_RPI95
    {PE15, hal_ll_uart_module_num(UART_MODULE_4), false},
    #endif
    #ifdef UART4_RX_RF0_RPI96
    {PF0, hal_ll_uart_module_num(UART_MODULE_4), false},
    #endif
    #ifdef UART4_RX_RF1_RP97
    {PF1, hal_ll_uart_module_num(UART_MODULE_4), false},
    #endif
    #ifdef UART4_RX_RG6_RP118
    {PG6, hal_ll_uart_module_num(UART_MODULE_4), false},
    #endif
    #ifdef UART4_RX_RG7_RPI119
    {PG7, hal_ll_uart_module_num(UART_MODULE_4), false},
    #endif
    #ifdef UART4_RX_RG8_RP120
    {PG8, hal_ll_uart_module_num(UART_MODULE_4), false},
    #endif
    #ifdef UART4_RX_RG9_RPI121
    {PG9, hal_ll_uart_module_num(UART_MODULE_4), false},
    #endif
    #ifdef UART1_RX_RD12_RPI76
    {PD12, hal_ll_uart_module_num(UART_MODULE_1), false},
    #endif
    #ifdef UART1_RX_RD13_RPI77
    {PD13, hal_ll_uart_module_num(UART_MODULE_1), false},
    #endif
    #ifdef UART1_RX_RE0_RPI80
    {PE0, hal_ll_uart_module_num(UART_MODULE_1), false},
    #endif
    #ifdef UART1_RX_RE1_RP81
    {PE1, hal_ll_uart_module_num(UART_MODULE_1), false},
    #endif
    #ifdef UART1_RX_RG0_RPI112
    {PG0, hal_ll_uart_module_num(UART_MODULE_1), false},
    #endif
    #ifdef UART1_RX_RG1_RP113
    {PG1, hal_ll_uart_module_num(UART_MODULE_1), false},
    #endif
    #ifdef UART1_RX_RG12_RPI124
    {PG12, hal_ll_uart_module_num(UART_MODULE_1), false},
    #endif
    #ifdef UART1_RX_RG13_RP125
    {PG13, hal_ll_uart_module_num(UART_MODULE_1), false},
    #endif
    #ifdef UART1_RX_RG14_RP126
    {PG14, hal_ll_uart_module_num(UART_MODULE_1), false},
    #endif
    #ifdef UART1_RX_RG15_RP127
    {PG15, hal_ll_uart_module_num(UART_MODULE_1), false},
    #endif
    #ifdef UART2_RX_RD12_RPI76
    {PD12, hal_ll_uart_module_num(UART_MODULE_2), false},
    #endif
    #ifdef UART2_RX_RD13_RPI77
    {PD13, hal_ll_uart_module_num(UART_MODULE_2), false},
    #endif
    #ifdef UART2_RX_RE0_RPI80
    {PE0, hal_ll_uart_module_num(UART_MODULE_2), false},
    #endif
    #ifdef UART2_RX_RE1_RP81
    {PE1, hal_ll_uart_module_num(UART_MODULE_2), false},
    #endif
    #ifdef UART2_RX_RG0_RPI112
    {PG0, hal_ll_uart_module_num(UART_MODULE_2), false},
    #endif
    #ifdef UART2_RX_RG1_RP113
    {PG1, hal_ll_uart_module_num(UART_MODULE_2), false},
    #endif
    #ifdef UART2_RX_RG12_RPI124
    {PG12, hal_ll_uart_module_num(UART_MODULE_2), false},
    #endif
    #ifdef UART2_RX_RG13_RP125
    {PG13, hal_ll_uart_module_num(UART_MODULE_2), false},
    #endif
    #ifdef UART2_RX_RG14_RP126
    {PG14, hal_ll_uart_module_num(UART_MODULE_2), false},
    #endif
    #ifdef UART2_RX_RG15_RP127
    {PG15, hal_ll_uart_module_num(UART_MODULE_2), false},
    #endif
    #ifdef UART3_RX_RD12_RPI76
    {PD12, hal_ll_uart_module_num(UART_MODULE_3), false},
    #endif
    #ifdef UART3_RX_RD13_RPI77
    {PD13, hal_ll_uart_module_num(UART_MODULE_3), false},
    #endif
    #ifdef UART3_RX_RE0_RPI80
    {PE0, hal_ll_uart_module_num(UART_MODULE_3), false},
    #endif
    #ifdef UART3_RX_RE1_RP81
    {PE1, hal_ll_uart_module_num(UART_MODULE_3), false},
    #endif
    #ifdef UART3_RX_RG0_RPI112
    {PG0, hal_ll_uart_module_num(UART_MODULE_3), false},
    #endif
    #ifdef UART3_RX_RG1_RP113
    {PG1, hal_ll_uart_module_num(UART_MODULE_3), false},
    #endif
    #ifdef UART3_RX_RG12_RPI124
    {PG12, hal_ll_uart_module_num(UART_MODULE_3), false},
    #endif
    #ifdef UART3_RX_RG13_RP125
    {PG13, hal_ll_uart_module_num(UART_MODULE_3), false},
    #endif
    #ifdef UART3_RX_RG14_RP126
    {PG14, hal_ll_uart_module_num(UART_MODULE_3), false},
    #endif
    #ifdef UART3_RX_RG15_RP127
    {PG15, hal_ll_uart_module_num(UART_MODULE_3), false},
    #endif
    #ifdef UART4_RX_RD12_RPI76
    {PD12, hal_ll_uart_module_num(UART_MODULE_4), false},
    #endif
    #ifdef UART4_RX_RD13_RPI77
    {PD13, hal_ll_uart_module_num(UART_MODULE_4), false},
    #endif
    #ifdef UART4_RX_RE0_RPI80
    {PE0, hal_ll_uart_module_num(UART_MODULE_4), false},
    #endif
    #ifdef UART4_RX_RE1_RP81
    {PE1, hal_ll_uart_module_num(UART_MODULE_4), false},
    #endif
    #ifdef UART4_RX_RG0_RPI112
    {PG0, hal_ll_uart_module_num(UART_MODULE_4), false},
    #endif
    #ifdef UART4_RX_RG1_RP113
    {PG1, hal_ll_uart_module_num(UART_MODULE_4), false},
    #endif
    #ifdef UART4_RX_RG12_RPI124
    {PG12, hal_ll_uart_module_num(UART_MODULE_4), false},
    #endif
    #ifdef UART4_RX_RG13_RP125
    {PG13, hal_ll_uart_module_num(UART_MODULE_4), false},
    #endif
    #ifdef UART4_RX_RG14_RP126
    {PG14, hal_ll_uart_module_num(UART_MODULE_4), false},
    #endif
    #ifdef UART4_RX_RG15_RP127
    {PG15, hal_ll_uart_module_num(UART_MODULE_4), false},
    #endif
    #ifdef UART1_RX_RA0_RP16
    {PA0, hal_ll_uart_module_num(UART_MODULE_1), false},
    #endif
    #ifdef UART1_RX_RA1_RP17
    {PA1, hal_ll_uart_module_num(UART_MODULE_1), false},
    #endif
    #ifdef UART1_RX_RA2_RP18
    {PA2, hal_ll_uart_module_num(UART_MODULE_1), false},
    #endif
    #ifdef UART1_RX_RA3_RP19
    {PA3, hal_ll_uart_module_num(UART_MODULE_1), false},
    #endif
    #ifdef UART1_RX_RB0_RP32
    {PB0, hal_ll_uart_module_num(UART_MODULE_1), false},
    #endif
    #ifdef UART1_RX_RB1_RP33
    {PB1, hal_ll_uart_module_num(UART_MODULE_1), false},
    #endif
    #ifdef UART1_RX_RB12_RP44
    {PB12, hal_ll_uart_module_num(UART_MODULE_1), false},
    #endif
    #ifdef UART1_RX_RB13_RP45
    {PB13, hal_ll_uart_module_num(UART_MODULE_1), false},
    #endif
    #ifdef UART1_RX_RB14_RP46
    {PB14, hal_ll_uart_module_num(UART_MODULE_1), false},
    #endif
    #ifdef UART1_RX_RB15_RP47
    {PB15, hal_ll_uart_module_num(UART_MODULE_1), false},
    #endif
    #ifdef UART1_RX_RB2_RP34
    {PB2, hal_ll_uart_module_num(UART_MODULE_1), false},
    #endif
    #ifdef UART2_RX_RA0_RP16
    {PA0, hal_ll_uart_module_num(UART_MODULE_2), false},
    #endif
    #ifdef UART2_RX_RA1_RP17
    {PA1, hal_ll_uart_module_num(UART_MODULE_2), false},
    #endif
    #ifdef UART2_RX_RA2_RP18
    {PA2, hal_ll_uart_module_num(UART_MODULE_2), false},
    #endif
    #ifdef UART2_RX_RA3_RP19
    {PA3, hal_ll_uart_module_num(UART_MODULE_2), false},
    #endif
    #ifdef UART2_RX_RB0_RP32
    {PB0, hal_ll_uart_module_num(UART_MODULE_2), false},
    #endif
    #ifdef UART2_RX_RB1_RP33
    {PB1, hal_ll_uart_module_num(UART_MODULE_2), false},
    #endif
    #ifdef UART2_RX_RB12_RP44
    {PB12, hal_ll_uart_module_num(UART_MODULE_2), false},
    #endif
    #ifdef UART2_RX_RB13_RP45
    {PB13, hal_ll_uart_module_num(UART_MODULE_2), false},
    #endif
    #ifdef UART2_RX_RB14_RP46
    {PB14, hal_ll_uart_module_num(UART_MODULE_2), false},
    #endif
    #ifdef UART2_RX_RB15_RP47
    {PB15, hal_ll_uart_module_num(UART_MODULE_2), false},
    #endif
    #ifdef UART2_RX_RB2_RP34
    {PB2, hal_ll_uart_module_num(UART_MODULE_2), false},
    #endif
    #ifdef UART1_RX_RC10_RP58
    {PC10, hal_ll_uart_module_num(UART_MODULE_1), false},
    #endif
    #ifdef UART1_RX_RC12_RP60
    {PC12, hal_ll_uart_module_num(UART_MODULE_1), false},
    #endif
    #ifdef UART1_RX_RC13_RP61
    {PC13, hal_ll_uart_module_num(UART_MODULE_1), false},
    #endif
    #ifdef UART1_RX_RC2_RP50
    {PC2, hal_ll_uart_module_num(UART_MODULE_1), false},
    #endif
    #ifdef UART1_RX_RC3_RP51
    {PC3, hal_ll_uart_module_num(UART_MODULE_1), false},
    #endif
    #ifdef UART1_RX_RC4_RP52
    {PC4, hal_ll_uart_module_num(UART_MODULE_1), false},
    #endif
    #ifdef UART1_RX_RC5_RP53
    {PC5, hal_ll_uart_module_num(UART_MODULE_1), false},
    #endif
    #ifdef UART2_RX_RC10_RP58
    {PC10, hal_ll_uart_module_num(UART_MODULE_2), false},
    #endif
    #ifdef UART2_RX_RC12_RP60
    {PC12, hal_ll_uart_module_num(UART_MODULE_2), false},
    #endif
    #ifdef UART2_RX_RC13_RP61
    {PC13, hal_ll_uart_module_num(UART_MODULE_2), false},
    #endif
    #ifdef UART2_RX_RC2_RP50
    {PC2, hal_ll_uart_module_num(UART_MODULE_2), false},
    #endif
    #ifdef UART2_RX_RC3_RP51
    {PC3, hal_ll_uart_module_num(UART_MODULE_2), false},
    #endif
    #ifdef UART2_RX_RC4_RP52
    {PC4, hal_ll_uart_module_num(UART_MODULE_2), false},
    #endif
    #ifdef UART2_RX_RC5_RP53
    {PC5, hal_ll_uart_module_num(UART_MODULE_2), false},
    #endif
    #ifdef UART1_RX_RD10_RP74
    {PD10, hal_ll_uart_module_num(UART_MODULE_1), false},
    #endif
    #ifdef UART1_RX_RD4_RP68
    {PD4, hal_ll_uart_module_num(UART_MODULE_1), false},
    #endif
    #ifdef UART2_RX_RD10_RP74
    {PD10, hal_ll_uart_module_num(UART_MODULE_2), false},
    #endif
    #ifdef UART2_RX_RD4_RP68
    {PD4, hal_ll_uart_module_num(UART_MODULE_2), false},
    #endif
    #ifdef UART1_RX_RC14_RP62
    {PC14, hal_ll_uart_module_num(UART_MODULE_1), false},
    #endif
    #ifdef UART1_RX_RC15_RP63
    {PC15, hal_ll_uart_module_num(UART_MODULE_1), false},
    #endif
    #ifdef UART1_RX_RD0_RP64
    {PD0, hal_ll_uart_module_num(UART_MODULE_1), false},
    #endif
    #ifdef UART1_RX_RD1_RP65
    {PD1, hal_ll_uart_module_num(UART_MODULE_1), false},
    #endif
    #ifdef UART1_RX_RD11_RP75
    {PD11, hal_ll_uart_module_num(UART_MODULE_1), false},
    #endif
    #ifdef UART1_RX_RD12_RP76
    {PD12, hal_ll_uart_module_num(UART_MODULE_1), false},
    #endif
    #ifdef UART1_RX_RD2_RP66
    {PD2, hal_ll_uart_module_num(UART_MODULE_1), false},
    #endif
    #ifdef UART1_RX_RD3_RP67
    {PD3, hal_ll_uart_module_num(UART_MODULE_1), false},
    #endif
    #ifdef UART1_RX_RD7_RP71
    {PD7, hal_ll_uart_module_num(UART_MODULE_1), false},
    #endif
    #ifdef UART1_RX_RD8_RP72
    {PD8, hal_ll_uart_module_num(UART_MODULE_1), false},
    #endif
    #ifdef UART1_RX_RD9_RP73
    {PD9, hal_ll_uart_module_num(UART_MODULE_1), false},
    #endif
    #ifdef UART2_RX_RC14_RP62
    {PC14, hal_ll_uart_module_num(UART_MODULE_2), false},
    #endif
    #ifdef UART2_RX_RC15_RP63
    {PC15, hal_ll_uart_module_num(UART_MODULE_2), false},
    #endif
    #ifdef UART2_RX_RD0_RP64
    {PD0, hal_ll_uart_module_num(UART_MODULE_2), false},
    #endif
    #ifdef UART2_RX_RD1_RP65
    {PD1, hal_ll_uart_module_num(UART_MODULE_2), false},
    #endif
    #ifdef UART2_RX_RD11_RP75
    {PD11, hal_ll_uart_module_num(UART_MODULE_2), false},
    #endif
    #ifdef UART2_RX_RD12_RP76
    {PD12, hal_ll_uart_module_num(UART_MODULE_2), false},
    #endif
    #ifdef UART2_RX_RD2_RP66
    {PD2, hal_ll_uart_module_num(UART_MODULE_2), false},
    #endif
    #ifdef UART2_RX_RD3_RP67
    {PD3, hal_ll_uart_module_num(UART_MODULE_2), false},
    #endif
    #ifdef UART2_RX_RD7_RP71
    {PD7, hal_ll_uart_module_num(UART_MODULE_2), false},
    #endif
    #ifdef UART2_RX_RD8_RP72
    {PD8, hal_ll_uart_module_num(UART_MODULE_2), false},
    #endif
    #ifdef UART2_RX_RD9_RP73
    {PD9, hal_ll_uart_module_num(UART_MODULE_2), false},
    #endif
    #ifdef UART1_RX_RC11_RP59
    {PC11, hal_ll_uart_module_num(UART_MODULE_1), false},
    #endif
    #ifdef UART2_RX_RC11_RP59
    {PC11, hal_ll_uart_module_num(UART_MODULE_2), false},
    #endif
    #ifdef UART1_RX_RB10_RPI42
    {PB10, hal_ll_uart_module_num(UART_MODULE_1), false},
    #endif
    #ifdef UART1_RX_RB11_RPI43
    {PB11, hal_ll_uart_module_num(UART_MODULE_1), false},
    #endif
    #ifdef UART1_RX_RB3_RPI35
    {PB3, hal_ll_uart_module_num(UART_MODULE_1), false},
    #endif
    #ifdef UART1_RX_RB4_RPI36
    {PB4, hal_ll_uart_module_num(UART_MODULE_1), false},
    #endif
    #ifdef UART1_RX_RB5_RPI37
    {PB5, hal_ll_uart_module_num(UART_MODULE_1), false},
    #endif
    #ifdef UART1_RX_RB6_RPI38
    {PB6, hal_ll_uart_module_num(UART_MODULE_1), false},
    #endif
    #ifdef UART1_RX_RB7_RPI39
    {PB7, hal_ll_uart_module_num(UART_MODULE_1), false},
    #endif
    #ifdef UART1_RX_RB8_RPI40
    {PB8, hal_ll_uart_module_num(UART_MODULE_1), false},
    #endif
    #ifdef UART1_RX_RB9_RPI41
    {PB9, hal_ll_uart_module_num(UART_MODULE_1), false},
    #endif
    #ifdef UART1_RX_RC14_RPI62
    {PC14, hal_ll_uart_module_num(UART_MODULE_1), false},
    #endif
    #ifdef UART1_RX_RD10_RPI74
    {PD10, hal_ll_uart_module_num(UART_MODULE_1), false},
    #endif
    #ifdef UART1_RX_RD11_RPI75
    {PD11, hal_ll_uart_module_num(UART_MODULE_1), false},
    #endif
    #ifdef UART1_RX_RD9_RPI73
    {PD9, hal_ll_uart_module_num(UART_MODULE_1), false},
    #endif
    #ifdef UART1_RX_RE0_RP80
    {PE0, hal_ll_uart_module_num(UART_MODULE_1), false},
    #endif
    #ifdef UART1_RX_RE1_RPI81
    {PE1, hal_ll_uart_module_num(UART_MODULE_1), false},
    #endif
    #ifdef UART1_RX_RE2_RP82
    {PE2, hal_ll_uart_module_num(UART_MODULE_1), false},
    #endif
    #ifdef UART1_RX_RE3_RPI83
    {PE3, hal_ll_uart_module_num(UART_MODULE_1), false},
    #endif
    #ifdef UART1_RX_RE4_RP84
    {PE4, hal_ll_uart_module_num(UART_MODULE_1), false},
    #endif
    #ifdef UART1_RX_RE5_RP85
    {PE5, hal_ll_uart_module_num(UART_MODULE_1), false},
    #endif
    #ifdef UART1_RX_RE6_RPI86
    {PE6, hal_ll_uart_module_num(UART_MODULE_1), false},
    #endif
    #ifdef UART1_RX_RE7_RP87
    {PE7, hal_ll_uart_module_num(UART_MODULE_1), false},
    #endif
    #ifdef UART1_RX_RF0_RP96
    {PF0, hal_ll_uart_module_num(UART_MODULE_1), false},
    #endif
    #ifdef UART1_RX_RF3_RP99
    {PF3, hal_ll_uart_module_num(UART_MODULE_1), false},
    #endif
    #ifdef UART1_RX_RF4_RP100
    {PF4, hal_ll_uart_module_num(UART_MODULE_1), false},
    #endif
    #ifdef UART1_RX_RF5_RP101
    {PF5, hal_ll_uart_module_num(UART_MODULE_1), false},
    #endif
    #ifdef UART2_RX_RB10_RPI42
    {PB10, hal_ll_uart_module_num(UART_MODULE_2), false},
    #endif
    #ifdef UART2_RX_RB11_RPI43
    {PB11, hal_ll_uart_module_num(UART_MODULE_2), false},
    #endif
    #ifdef UART2_RX_RB3_RPI35
    {PB3, hal_ll_uart_module_num(UART_MODULE_2), false},
    #endif
    #ifdef UART2_RX_RB4_RPI36
    {PB4, hal_ll_uart_module_num(UART_MODULE_2), false},
    #endif
    #ifdef UART2_RX_RB5_RPI37
    {PB5, hal_ll_uart_module_num(UART_MODULE_2), false},
    #endif
    #ifdef UART2_RX_RB6_RPI38
    {PB6, hal_ll_uart_module_num(UART_MODULE_2), false},
    #endif
    #ifdef UART2_RX_RB7_RPI39
    {PB7, hal_ll_uart_module_num(UART_MODULE_2), false},
    #endif
    #ifdef UART2_RX_RB8_RPI40
    {PB8, hal_ll_uart_module_num(UART_MODULE_2), false},
    #endif
    #ifdef UART2_RX_RB9_RPI41
    {PB9, hal_ll_uart_module_num(UART_MODULE_2), false},
    #endif
    #ifdef UART2_RX_RC14_RPI62
    {PC14, hal_ll_uart_module_num(UART_MODULE_2), false},
    #endif
    #ifdef UART2_RX_RD10_RPI74
    {PD10, hal_ll_uart_module_num(UART_MODULE_2), false},
    #endif
    #ifdef UART2_RX_RD11_RPI75
    {PD11, hal_ll_uart_module_num(UART_MODULE_2), false},
    #endif
    #ifdef UART2_RX_RD9_RPI73
    {PD9, hal_ll_uart_module_num(UART_MODULE_2), false},
    #endif
    #ifdef UART2_RX_RE0_RP80
    {PE0, hal_ll_uart_module_num(UART_MODULE_2), false},
    #endif
    #ifdef UART2_RX_RE1_RPI81
    {PE1, hal_ll_uart_module_num(UART_MODULE_2), false},
    #endif
    #ifdef UART2_RX_RE2_RP82
    {PE2, hal_ll_uart_module_num(UART_MODULE_2), false},
    #endif
    #ifdef UART2_RX_RE3_RPI83
    {PE3, hal_ll_uart_module_num(UART_MODULE_2), false},
    #endif
    #ifdef UART2_RX_RE4_RP84
    {PE4, hal_ll_uart_module_num(UART_MODULE_2), false},
    #endif
    #ifdef UART2_RX_RE5_RP85
    {PE5, hal_ll_uart_module_num(UART_MODULE_2), false},
    #endif
    #ifdef UART2_RX_RE6_RPI86
    {PE6, hal_ll_uart_module_num(UART_MODULE_2), false},
    #endif
    #ifdef UART2_RX_RE7_RP87
    {PE7, hal_ll_uart_module_num(UART_MODULE_2), false},
    #endif
    #ifdef UART2_RX_RF0_RP96
    {PF0, hal_ll_uart_module_num(UART_MODULE_2), false},
    #endif
    #ifdef UART2_RX_RF3_RP99
    {PF3, hal_ll_uart_module_num(UART_MODULE_2), false},
    #endif
    #ifdef UART2_RX_RF4_RP100
    {PF4, hal_ll_uart_module_num(UART_MODULE_2), false},
    #endif
    #ifdef UART2_RX_RF5_RP101
    {PF5, hal_ll_uart_module_num(UART_MODULE_2), false},
    #endif
    #ifdef UART3_RX_RB10_RPI42
    {PB10, hal_ll_uart_module_num(UART_MODULE_3), false},
    #endif
    #ifdef UART3_RX_RB11_RPI43
    {PB11, hal_ll_uart_module_num(UART_MODULE_3), false},
    #endif
    #ifdef UART3_RX_RB3_RPI35
    {PB3, hal_ll_uart_module_num(UART_MODULE_3), false},
    #endif
    #ifdef UART3_RX_RB4_RPI36
    {PB4, hal_ll_uart_module_num(UART_MODULE_3), false},
    #endif
    #ifdef UART3_RX_RB5_RPI37
    {PB5, hal_ll_uart_module_num(UART_MODULE_3), false},
    #endif
    #ifdef UART3_RX_RB6_RPI38
    {PB6, hal_ll_uart_module_num(UART_MODULE_3), false},
    #endif
    #ifdef UART3_RX_RB7_RPI39
    {PB7, hal_ll_uart_module_num(UART_MODULE_3), false},
    #endif
    #ifdef UART3_RX_RB8_RPI40
    {PB8, hal_ll_uart_module_num(UART_MODULE_3), false},
    #endif
    #ifdef UART3_RX_RB9_RPI41
    {PB9, hal_ll_uart_module_num(UART_MODULE_3), false},
    #endif
    #ifdef UART3_RX_RC14_RPI62
    {PC14, hal_ll_uart_module_num(UART_MODULE_3), false},
    #endif
    #ifdef UART3_RX_RD0_RP64
    {PD0, hal_ll_uart_module_num(UART_MODULE_3), false},
    #endif
    #ifdef UART3_RX_RD1_RP65
    {PD1, hal_ll_uart_module_num(UART_MODULE_3), false},
    #endif
    #ifdef UART3_RX_RD10_RPI74
    {PD10, hal_ll_uart_module_num(UART_MODULE_3), false},
    #endif
    #ifdef UART3_RX_RD11_RPI75
    {PD11, hal_ll_uart_module_num(UART_MODULE_3), false},
    #endif
    #ifdef UART3_RX_RD2_RP66
    {PD2, hal_ll_uart_module_num(UART_MODULE_3), false},
    #endif
    #ifdef UART3_RX_RD3_RP67
    {PD3, hal_ll_uart_module_num(UART_MODULE_3), false},
    #endif
    #ifdef UART3_RX_RD4_RP68
    {PD4, hal_ll_uart_module_num(UART_MODULE_3), false},
    #endif
    #ifdef UART3_RX_RD7_RP71
    {PD7, hal_ll_uart_module_num(UART_MODULE_3), false},
    #endif
    #ifdef UART3_RX_RD9_RPI73
    {PD9, hal_ll_uart_module_num(UART_MODULE_3), false},
    #endif
    #ifdef UART3_RX_RE0_RP80
    {PE0, hal_ll_uart_module_num(UART_MODULE_3), false},
    #endif
    #ifdef UART3_RX_RE1_RPI81
    {PE1, hal_ll_uart_module_num(UART_MODULE_3), false},
    #endif
    #ifdef UART3_RX_RE2_RP82
    {PE2, hal_ll_uart_module_num(UART_MODULE_3), false},
    #endif
    #ifdef UART3_RX_RE3_RPI83
    {PE3, hal_ll_uart_module_num(UART_MODULE_3), false},
    #endif
    #ifdef UART3_RX_RE4_RP84
    {PE4, hal_ll_uart_module_num(UART_MODULE_3), false},
    #endif
    #ifdef UART3_RX_RE5_RP85
    {PE5, hal_ll_uart_module_num(UART_MODULE_3), false},
    #endif
    #ifdef UART3_RX_RE6_RPI86
    {PE6, hal_ll_uart_module_num(UART_MODULE_3), false},
    #endif
    #ifdef UART3_RX_RE7_RP87
    {PE7, hal_ll_uart_module_num(UART_MODULE_3), false},
    #endif
    #ifdef UART3_RX_RF0_RP96
    {PF0, hal_ll_uart_module_num(UART_MODULE_3), false},
    #endif
    #ifdef UART3_RX_RF3_RP99
    {PF3, hal_ll_uart_module_num(UART_MODULE_3), false},
    #endif
    #ifdef UART3_RX_RF4_RP100
    {PF4, hal_ll_uart_module_num(UART_MODULE_3), false},
    #endif
    #ifdef UART3_RX_RF5_RP101
    {PF5, hal_ll_uart_module_num(UART_MODULE_3), false},
    #endif
    #ifdef UART4_RX_RB10_RPI42
    {PB10, hal_ll_uart_module_num(UART_MODULE_4), false},
    #endif
    #ifdef UART4_RX_RB11_RPI43
    {PB11, hal_ll_uart_module_num(UART_MODULE_4), false},
    #endif
    #ifdef UART4_RX_RB3_RPI35
    {PB3, hal_ll_uart_module_num(UART_MODULE_4), false},
    #endif
    #ifdef UART4_RX_RB4_RPI36
    {PB4, hal_ll_uart_module_num(UART_MODULE_4), false},
    #endif
    #ifdef UART4_RX_RB5_RPI37
    {PB5, hal_ll_uart_module_num(UART_MODULE_4), false},
    #endif
    #ifdef UART4_RX_RB6_RPI38
    {PB6, hal_ll_uart_module_num(UART_MODULE_4), false},
    #endif
    #ifdef UART4_RX_RB7_RPI39
    {PB7, hal_ll_uart_module_num(UART_MODULE_4), false},
    #endif
    #ifdef UART4_RX_RB8_RPI40
    {PB8, hal_ll_uart_module_num(UART_MODULE_4), false},
    #endif
    #ifdef UART4_RX_RB9_RPI41
    {PB9, hal_ll_uart_module_num(UART_MODULE_4), false},
    #endif
    #ifdef UART4_RX_RC14_RPI62
    {PC14, hal_ll_uart_module_num(UART_MODULE_4), false},
    #endif
    #ifdef UART4_RX_RD0_RP64
    {PD0, hal_ll_uart_module_num(UART_MODULE_4), false},
    #endif
    #ifdef UART4_RX_RD1_RP65
    {PD1, hal_ll_uart_module_num(UART_MODULE_4), false},
    #endif
    #ifdef UART4_RX_RD10_RPI74
    {PD10, hal_ll_uart_module_num(UART_MODULE_4), false},
    #endif
    #ifdef UART4_RX_RD11_RPI75
    {PD11, hal_ll_uart_module_num(UART_MODULE_4), false},
    #endif
    #ifdef UART4_RX_RD2_RP66
    {PD2, hal_ll_uart_module_num(UART_MODULE_4), false},
    #endif
    #ifdef UART4_RX_RD3_RP67
    {PD3, hal_ll_uart_module_num(UART_MODULE_4), false},
    #endif
    #ifdef UART4_RX_RD4_RP68
    {PD4, hal_ll_uart_module_num(UART_MODULE_4), false},
    #endif
    #ifdef UART4_RX_RD7_RP71
    {PD7, hal_ll_uart_module_num(UART_MODULE_4), false},
    #endif
    #ifdef UART4_RX_RD9_RPI73
    {PD9, hal_ll_uart_module_num(UART_MODULE_4), false},
    #endif
    #ifdef UART4_RX_RE0_RP80
    {PE0, hal_ll_uart_module_num(UART_MODULE_4), false},
    #endif
    #ifdef UART4_RX_RE1_RPI81
    {PE1, hal_ll_uart_module_num(UART_MODULE_4), false},
    #endif
    #ifdef UART4_RX_RE2_RP82
    {PE2, hal_ll_uart_module_num(UART_MODULE_4), false},
    #endif
    #ifdef UART4_RX_RE3_RPI83
    {PE3, hal_ll_uart_module_num(UART_MODULE_4), false},
    #endif
    #ifdef UART4_RX_RE4_RP84
    {PE4, hal_ll_uart_module_num(UART_MODULE_4), false},
    #endif
    #ifdef UART4_RX_RE5_RP85
    {PE5, hal_ll_uart_module_num(UART_MODULE_4), false},
    #endif
    #ifdef UART4_RX_RE6_RPI86
    {PE6, hal_ll_uart_module_num(UART_MODULE_4), false},
    #endif
    #ifdef UART4_RX_RE7_RP87
    {PE7, hal_ll_uart_module_num(UART_MODULE_4), false},
    #endif
    #ifdef UART4_RX_RF0_RP96
    {PF0, hal_ll_uart_module_num(UART_MODULE_4), false},
    #endif
    #ifdef UART4_RX_RF3_RP99
    {PF3, hal_ll_uart_module_num(UART_MODULE_4), false},
    #endif
    #ifdef UART4_RX_RF4_RP100
    {PF4, hal_ll_uart_module_num(UART_MODULE_4), false},
    #endif
    #ifdef UART4_RX_RF5_RP101
    {PF5, hal_ll_uart_module_num(UART_MODULE_4), false},
    #endif
    #ifdef UART1_RX_RA14_RPI30
    {PA14, hal_ll_uart_module_num(UART_MODULE_1), false},
    #endif
    #ifdef UART1_RX_RA15_RPI31
    {PA15, hal_ll_uart_module_num(UART_MODULE_1), false},
    #endif
    #ifdef UART1_RX_RA4_RPI20
    {PA4, hal_ll_uart_module_num(UART_MODULE_1), false},
    #endif
    #ifdef UART1_RX_RA5_RPI21
    {PA5, hal_ll_uart_module_num(UART_MODULE_1), false},
    #endif
    #ifdef UART1_RX_RA6_RPI22
    {PA6, hal_ll_uart_module_num(UART_MODULE_1), false},
    #endif
    #ifdef UART1_RX_RA7_RPI23
    {PA7, hal_ll_uart_module_num(UART_MODULE_1), false},
    #endif
    #ifdef UART1_RX_RC1_RPI49
    {PC1, hal_ll_uart_module_num(UART_MODULE_1), false},
    #endif
    #ifdef UART1_RX_RD14_RPI78
    {PD14, hal_ll_uart_module_num(UART_MODULE_1), false},
    #endif
    #ifdef UART1_RX_RD15_RP79
    {PD15, hal_ll_uart_module_num(UART_MODULE_1), false},
    #endif
    #ifdef UART1_RX_RE8_RPI88
    {PE8, hal_ll_uart_module_num(UART_MODULE_1), false},
    #endif
    #ifdef UART1_RX_RE9_RPI89
    {PE9, hal_ll_uart_module_num(UART_MODULE_1), false},
    #endif
    #ifdef UART1_RX_RF12_RP108
    {PF12, hal_ll_uart_module_num(UART_MODULE_1), false},
    #endif
    #ifdef UART1_RX_RF13_RP109
    {PF13, hal_ll_uart_module_num(UART_MODULE_1), false},
    #endif
    #ifdef UART1_RX_RF2_RP98
    {PF2, hal_ll_uart_module_num(UART_MODULE_1), false},
    #endif
    #ifdef UART1_RX_RF8_RP104
    {PF8, hal_ll_uart_module_num(UART_MODULE_1), false},
    #endif
    #ifdef UART1_RX_RG0_RP112
    {PG0, hal_ll_uart_module_num(UART_MODULE_1), false},
    #endif
    #ifdef UART2_RX_RA14_RPI30
    {PA14, hal_ll_uart_module_num(UART_MODULE_2), false},
    #endif
    #ifdef UART2_RX_RA15_RPI31
    {PA15, hal_ll_uart_module_num(UART_MODULE_2), false},
    #endif
    #ifdef UART2_RX_RA4_RPI20
    {PA4, hal_ll_uart_module_num(UART_MODULE_2), false},
    #endif
    #ifdef UART2_RX_RA5_RPI21
    {PA5, hal_ll_uart_module_num(UART_MODULE_2), false},
    #endif
    #ifdef UART2_RX_RA6_RPI22
    {PA6, hal_ll_uart_module_num(UART_MODULE_2), false},
    #endif
    #ifdef UART2_RX_RA7_RPI23
    {PA7, hal_ll_uart_module_num(UART_MODULE_2), false},
    #endif
    #ifdef UART2_RX_RC1_RPI49
    {PC1, hal_ll_uart_module_num(UART_MODULE_2), false},
    #endif
    #ifdef UART2_RX_RD14_RPI78
    {PD14, hal_ll_uart_module_num(UART_MODULE_2), false},
    #endif
    #ifdef UART2_RX_RD15_RP79
    {PD15, hal_ll_uart_module_num(UART_MODULE_2), false},
    #endif
    #ifdef UART2_RX_RE8_RPI88
    {PE8, hal_ll_uart_module_num(UART_MODULE_2), false},
    #endif
    #ifdef UART2_RX_RE9_RPI89
    {PE9, hal_ll_uart_module_num(UART_MODULE_2), false},
    #endif
    #ifdef UART2_RX_RF12_RP108
    {PF12, hal_ll_uart_module_num(UART_MODULE_2), false},
    #endif
    #ifdef UART2_RX_RF13_RP109
    {PF13, hal_ll_uart_module_num(UART_MODULE_2), false},
    #endif
    #ifdef UART2_RX_RF2_RP98
    {PF2, hal_ll_uart_module_num(UART_MODULE_2), false},
    #endif
    #ifdef UART2_RX_RF8_RP104
    {PF8, hal_ll_uart_module_num(UART_MODULE_2), false},
    #endif
    #ifdef UART2_RX_RG0_RP112
    {PG0, hal_ll_uart_module_num(UART_MODULE_2), false},
    #endif
    #ifdef UART3_RX_RA14_RPI30
    {PA14, hal_ll_uart_module_num(UART_MODULE_3), false},
    #endif
    #ifdef UART3_RX_RA15_RPI31
    {PA15, hal_ll_uart_module_num(UART_MODULE_3), false},
    #endif
    #ifdef UART3_RX_RA4_RPI20
    {PA4, hal_ll_uart_module_num(UART_MODULE_3), false},
    #endif
    #ifdef UART3_RX_RA5_RPI21
    {PA5, hal_ll_uart_module_num(UART_MODULE_3), false},
    #endif
    #ifdef UART3_RX_RA6_RPI22
    {PA6, hal_ll_uart_module_num(UART_MODULE_3), false},
    #endif
    #ifdef UART3_RX_RA7_RPI23
    {PA7, hal_ll_uart_module_num(UART_MODULE_3), false},
    #endif
    #ifdef UART3_RX_RC1_RPI49
    {PC1, hal_ll_uart_module_num(UART_MODULE_3), false},
    #endif
    #ifdef UART3_RX_RD14_RPI78
    {PD14, hal_ll_uart_module_num(UART_MODULE_3), false},
    #endif
    #ifdef UART3_RX_RD15_RP79
    {PD15, hal_ll_uart_module_num(UART_MODULE_3), false},
    #endif
    #ifdef UART3_RX_RE8_RPI88
    {PE8, hal_ll_uart_module_num(UART_MODULE_3), false},
    #endif
    #ifdef UART3_RX_RE9_RPI89
    {PE9, hal_ll_uart_module_num(UART_MODULE_3), false},
    #endif
    #ifdef UART3_RX_RF12_RP108
    {PF12, hal_ll_uart_module_num(UART_MODULE_3), false},
    #endif
    #ifdef UART3_RX_RF13_RP109
    {PF13, hal_ll_uart_module_num(UART_MODULE_3), false},
    #endif
    #ifdef UART3_RX_RF2_RP98
    {PF2, hal_ll_uart_module_num(UART_MODULE_3), false},
    #endif
    #ifdef UART3_RX_RF8_RP104
    {PF8, hal_ll_uart_module_num(UART_MODULE_3), false},
    #endif
    #ifdef UART3_RX_RG0_RP112
    {PG0, hal_ll_uart_module_num(UART_MODULE_3), false},
    #endif
    #ifdef UART4_RX_RA14_RPI30
    {PA14, hal_ll_uart_module_num(UART_MODULE_4), false},
    #endif
    #ifdef UART4_RX_RA15_RPI31
    {PA15, hal_ll_uart_module_num(UART_MODULE_4), false},
    #endif
    #ifdef UART4_RX_RA4_RPI20
    {PA4, hal_ll_uart_module_num(UART_MODULE_4), false},
    #endif
    #ifdef UART4_RX_RA5_RPI21
    {PA5, hal_ll_uart_module_num(UART_MODULE_4), false},
    #endif
    #ifdef UART4_RX_RA6_RPI22
    {PA6, hal_ll_uart_module_num(UART_MODULE_4), false},
    #endif
    #ifdef UART4_RX_RA7_RPI23
    {PA7, hal_ll_uart_module_num(UART_MODULE_4), false},
    #endif
    #ifdef UART4_RX_RC1_RPI49
    {PC1, hal_ll_uart_module_num(UART_MODULE_4), false},
    #endif
    #ifdef UART4_RX_RD14_RPI78
    {PD14, hal_ll_uart_module_num(UART_MODULE_4), false},
    #endif
    #ifdef UART4_RX_RD15_RP79
    {PD15, hal_ll_uart_module_num(UART_MODULE_4), false},
    #endif
    #ifdef UART4_RX_RE8_RPI88
    {PE8, hal_ll_uart_module_num(UART_MODULE_4), false},
    #endif
    #ifdef UART4_RX_RE9_RPI89
    {PE9, hal_ll_uart_module_num(UART_MODULE_4), false},
    #endif
    #ifdef UART4_RX_RF12_RP108
    {PF12, hal_ll_uart_module_num(UART_MODULE_4), false},
    #endif
    #ifdef UART4_RX_RF13_RP109
    {PF13, hal_ll_uart_module_num(UART_MODULE_4), false},
    #endif
    #ifdef UART4_RX_RF2_RP98
    {PF2, hal_ll_uart_module_num(UART_MODULE_4), false},
    #endif
    #ifdef UART4_RX_RF8_RP104
    {PF8, hal_ll_uart_module_num(UART_MODULE_4), false},
    #endif
    #ifdef UART4_RX_RG0_RP112
    {PG0, hal_ll_uart_module_num(UART_MODULE_4), false},
    #endif
    #ifdef UART1_RX_RF6_RP102
    {PF6, hal_ll_uart_module_num(UART_MODULE_1), false},
    #endif
    #ifdef UART2_RX_RF6_RP102
    {PF6, hal_ll_uart_module_num(UART_MODULE_2), false},
    #endif
    #ifdef UART3_RX_RF6_RP102
    {PF6, hal_ll_uart_module_num(UART_MODULE_3), false},
    #endif
    #ifdef UART4_RX_RF6_RP102
    {PF6, hal_ll_uart_module_num(UART_MODULE_4), false},
    #endif
    #ifdef UART1_RX_RB0_RP0
    {PB0, hal_ll_uart_module_num(UART_MODULE_1), false},
    #endif
    #ifdef UART1_RX_RB1_RP1
    {PB1, hal_ll_uart_module_num(UART_MODULE_1), false},
    #endif
    #ifdef UART1_RX_RB10_RP10
    {PB10, hal_ll_uart_module_num(UART_MODULE_1), false},
    #endif
    #ifdef UART1_RX_RB11_RP11
    {PB11, hal_ll_uart_module_num(UART_MODULE_1), false},
    #endif
    #ifdef UART1_RX_RB12_RP12
    {PB12, hal_ll_uart_module_num(UART_MODULE_1), false},
    #endif
    #ifdef UART1_RX_RB13_RP13
    {PB13, hal_ll_uart_module_num(UART_MODULE_1), false},
    #endif
    #ifdef UART1_RX_RB14_RP14
    {PB14, hal_ll_uart_module_num(UART_MODULE_1), false},
    #endif
    #ifdef UART1_RX_RB15_RP15
    {PB15, hal_ll_uart_module_num(UART_MODULE_1), false},
    #endif
    #ifdef UART1_RX_RB2_RP2
    {PB2, hal_ll_uart_module_num(UART_MODULE_1), false},
    #endif
    #ifdef UART1_RX_RB3_RP3
    {PB3, hal_ll_uart_module_num(UART_MODULE_1), false},
    #endif
    #ifdef UART1_RX_RB4_RP4
    {PB4, hal_ll_uart_module_num(UART_MODULE_1), false},
    #endif
    #ifdef UART1_RX_RB5_RP5
    {PB5, hal_ll_uart_module_num(UART_MODULE_1), false},
    #endif
    #ifdef UART1_RX_RB6_RP6
    {PB6, hal_ll_uart_module_num(UART_MODULE_1), false},
    #endif
    #ifdef UART1_RX_RB7_RP7
    {PB7, hal_ll_uart_module_num(UART_MODULE_1), false},
    #endif
    #ifdef UART1_RX_RB8_RP8
    {PB8, hal_ll_uart_module_num(UART_MODULE_1), false},
    #endif
    #ifdef UART1_RX_RB9_RP9
    {PB9, hal_ll_uart_module_num(UART_MODULE_1), false},
    #endif
    #ifdef UART2_RX_RB0_RP0
    {PB0, hal_ll_uart_module_num(UART_MODULE_2), false},
    #endif
    #ifdef UART2_RX_RB1_RP1
    {PB1, hal_ll_uart_module_num(UART_MODULE_2), false},
    #endif
    #ifdef UART2_RX_RB10_RP10
    {PB10, hal_ll_uart_module_num(UART_MODULE_2), false},
    #endif
    #ifdef UART2_RX_RB11_RP11
    {PB11, hal_ll_uart_module_num(UART_MODULE_2), false},
    #endif
    #ifdef UART2_RX_RB12_RP12
    {PB12, hal_ll_uart_module_num(UART_MODULE_2), false},
    #endif
    #ifdef UART2_RX_RB13_RP13
    {PB13, hal_ll_uart_module_num(UART_MODULE_2), false},
    #endif
    #ifdef UART2_RX_RB14_RP14
    {PB14, hal_ll_uart_module_num(UART_MODULE_2), false},
    #endif
    #ifdef UART2_RX_RB15_RP15
    {PB15, hal_ll_uart_module_num(UART_MODULE_2), false},
    #endif
    #ifdef UART2_RX_RB2_RP2
    {PB2, hal_ll_uart_module_num(UART_MODULE_2), false},
    #endif
    #ifdef UART2_RX_RB3_RP3
    {PB3, hal_ll_uart_module_num(UART_MODULE_2), false},
    #endif
    #ifdef UART2_RX_RB4_RP4
    {PB4, hal_ll_uart_module_num(UART_MODULE_2), false},
    #endif
    #ifdef UART2_RX_RB5_RP5
    {PB5, hal_ll_uart_module_num(UART_MODULE_2), false},
    #endif
    #ifdef UART2_RX_RB6_RP6
    {PB6, hal_ll_uart_module_num(UART_MODULE_2), false},
    #endif
    #ifdef UART2_RX_RB7_RP7
    {PB7, hal_ll_uart_module_num(UART_MODULE_2), false},
    #endif
    #ifdef UART2_RX_RB8_RP8
    {PB8, hal_ll_uart_module_num(UART_MODULE_2), false},
    #endif
    #ifdef UART2_RX_RB9_RP9
    {PB9, hal_ll_uart_module_num(UART_MODULE_2), false},
    #endif
    #ifdef UART1_RX_RC0_RP16
    {PC0, hal_ll_uart_module_num(UART_MODULE_1), false},
    #endif
    #ifdef UART1_RX_RC1_RP17
    {PC1, hal_ll_uart_module_num(UART_MODULE_1), false},
    #endif
    #ifdef UART1_RX_RC2_RP18
    {PC2, hal_ll_uart_module_num(UART_MODULE_1), false},
    #endif
    #ifdef UART1_RX_RC3_RP19
    {PC3, hal_ll_uart_module_num(UART_MODULE_1), false},
    #endif
    #ifdef UART1_RX_RC4_RP20
    {PC4, hal_ll_uart_module_num(UART_MODULE_1), false},
    #endif
    #ifdef UART1_RX_RC5_RP21
    {PC5, hal_ll_uart_module_num(UART_MODULE_1), false},
    #endif
    #ifdef UART1_RX_RC6_RP22
    {PC6, hal_ll_uart_module_num(UART_MODULE_1), false},
    #endif
    #ifdef UART1_RX_RC7_RP23
    {PC7, hal_ll_uart_module_num(UART_MODULE_1), false},
    #endif
    #ifdef UART1_RX_RC8_RP24
    {PC8, hal_ll_uart_module_num(UART_MODULE_1), false},
    #endif
    #ifdef UART1_RX_RC9_RP25
    {PC9, hal_ll_uart_module_num(UART_MODULE_1), false},
    #endif
    #ifdef UART2_RX_RC0_RP16
    {PC0, hal_ll_uart_module_num(UART_MODULE_2), false},
    #endif
    #ifdef UART2_RX_RC1_RP17
    {PC1, hal_ll_uart_module_num(UART_MODULE_2), false},
    #endif
    #ifdef UART2_RX_RC2_RP18
    {PC2, hal_ll_uart_module_num(UART_MODULE_2), false},
    #endif
    #ifdef UART2_RX_RC3_RP19
    {PC3, hal_ll_uart_module_num(UART_MODULE_2), false},
    #endif
    #ifdef UART2_RX_RC4_RP20
    {PC4, hal_ll_uart_module_num(UART_MODULE_2), false},
    #endif
    #ifdef UART2_RX_RC5_RP21
    {PC5, hal_ll_uart_module_num(UART_MODULE_2), false},
    #endif
    #ifdef UART2_RX_RC6_RP22
    {PC6, hal_ll_uart_module_num(UART_MODULE_2), false},
    #endif
    #ifdef UART2_RX_RC7_RP23
    {PC7, hal_ll_uart_module_num(UART_MODULE_2), false},
    #endif
    #ifdef UART2_RX_RC8_RP24
    {PC8, hal_ll_uart_module_num(UART_MODULE_2), false},
    #endif
    #ifdef UART2_RX_RC9_RP25
    {PC9, hal_ll_uart_module_num(UART_MODULE_2), false},
    #endif
    #ifdef UART1_RX_RC10_RP26
    {PC10, hal_ll_uart_module_num(UART_MODULE_1), false},
    #endif
    #ifdef UART1_RX_RC11_RP27
    {PC11, hal_ll_uart_module_num(UART_MODULE_1), false},
    #endif
    #ifdef UART1_RX_RC12_RP28
    {PC12, hal_ll_uart_module_num(UART_MODULE_1), false},
    #endif
    #ifdef UART1_RX_RC13_RP29
    {PC13, hal_ll_uart_module_num(UART_MODULE_1), false},
    #endif
    #ifdef UART1_RX_RB2
    {PB2, hal_ll_uart_module_num(UART_MODULE_1), false},
    #endif
    #ifdef UART2_RX_RB1
    {PB1, hal_ll_uart_module_num(UART_MODULE_2), false},
    #endif
    #ifdef UART1_RX_RC6
    {PC6, hal_ll_uart_module_num(UART_MODULE_1), false},
    #endif
    #ifdef UART1_RX_RB15_RP29
    {PB15, hal_ll_uart_module_num(UART_MODULE_1), false},
    #endif
    #ifdef UART1_RX_RB2_RP13
    {PB2, hal_ll_uart_module_num(UART_MODULE_1), false},
    #endif
    #ifdef UART1_RX_RB4_RP28
    {PB4, hal_ll_uart_module_num(UART_MODULE_1), false},
    #endif
    #ifdef UART1_RX_RB5_RP18
    {PB5, hal_ll_uart_module_num(UART_MODULE_1), false},
    #endif
    #ifdef UART1_RX_RC14_RPI37
    {PC14, hal_ll_uart_module_num(UART_MODULE_1), false},
    #endif
    #ifdef UART1_RX_RD0_RP11
    {PD0, hal_ll_uart_module_num(UART_MODULE_1), false},
    #endif
    #ifdef UART1_RX_RD1_RP24
    {PD1, hal_ll_uart_module_num(UART_MODULE_1), false},
    #endif
    #ifdef UART1_RX_RD10_RP3
    {PD10, hal_ll_uart_module_num(UART_MODULE_1), false},
    #endif
    #ifdef UART1_RX_RD11_RP12
    {PD11, hal_ll_uart_module_num(UART_MODULE_1), false},
    #endif
    #ifdef UART1_RX_RD2_RP23
    {PD2, hal_ll_uart_module_num(UART_MODULE_1), false},
    #endif
    #ifdef UART1_RX_RD3_RP22
    {PD3, hal_ll_uart_module_num(UART_MODULE_1), false},
    #endif
    #ifdef UART1_RX_RD4_RP25
    {PD4, hal_ll_uart_module_num(UART_MODULE_1), false},
    #endif
    #ifdef UART1_RX_RD5_RP20
    {PD5, hal_ll_uart_module_num(UART_MODULE_1), false},
    #endif
    #ifdef UART1_RX_RD8_RP2
    {PD8, hal_ll_uart_module_num(UART_MODULE_1), false},
    #endif
    #ifdef UART1_RX_RD9_RP4
    {PD9, hal_ll_uart_module_num(UART_MODULE_1), false},
    #endif
    #ifdef UART1_RX_RF2_RP30
    {PF2, hal_ll_uart_module_num(UART_MODULE_1), false},
    #endif
    #ifdef UART1_RX_RF3_RP16
    {PF3, hal_ll_uart_module_num(UART_MODULE_1), false},
    #endif
    #ifdef UART1_RX_RF4_RP10
    {PF4, hal_ll_uart_module_num(UART_MODULE_1), false},
    #endif
    #ifdef UART1_RX_RF5_RP17
    {PF5, hal_ll_uart_module_num(UART_MODULE_1), false},
    #endif
    #ifdef UART1_RX_RG6_RP21
    {PG6, hal_ll_uart_module_num(UART_MODULE_1), false},
    #endif
    #ifdef UART1_RX_RG7_RP26
    {PG7, hal_ll_uart_module_num(UART_MODULE_1), false},
    #endif
    #ifdef UART1_RX_RG8_RP19
    {PG8, hal_ll_uart_module_num(UART_MODULE_1), false},
    #endif
    #ifdef UART1_RX_RG9_RP27
    {PG9, hal_ll_uart_module_num(UART_MODULE_1), false},
    #endif
    #ifdef UART2_RX_RB15_RP29
    {PB15, hal_ll_uart_module_num(UART_MODULE_2), false},
    #endif
    #ifdef UART2_RX_RB2_RP13
    {PB2, hal_ll_uart_module_num(UART_MODULE_2), false},
    #endif
    #ifdef UART2_RX_RB4_RP28
    {PB4, hal_ll_uart_module_num(UART_MODULE_2), false},
    #endif
    #ifdef UART2_RX_RB5_RP18
    {PB5, hal_ll_uart_module_num(UART_MODULE_2), false},
    #endif
    #ifdef UART2_RX_RC14_RPI37
    {PC14, hal_ll_uart_module_num(UART_MODULE_2), false},
    #endif
    #ifdef UART2_RX_RD0_RP11
    {PD0, hal_ll_uart_module_num(UART_MODULE_2), false},
    #endif
    #ifdef UART2_RX_RD1_RP24
    {PD1, hal_ll_uart_module_num(UART_MODULE_2), false},
    #endif
    #ifdef UART2_RX_RD10_RP3
    {PD10, hal_ll_uart_module_num(UART_MODULE_2), false},
    #endif
    #ifdef UART2_RX_RD11_RP12
    {PD11, hal_ll_uart_module_num(UART_MODULE_2), false},
    #endif
    #ifdef UART2_RX_RD2_RP23
    {PD2, hal_ll_uart_module_num(UART_MODULE_2), false},
    #endif
    #ifdef UART2_RX_RD3_RP22
    {PD3, hal_ll_uart_module_num(UART_MODULE_2), false},
    #endif
    #ifdef UART2_RX_RD4_RP25
    {PD4, hal_ll_uart_module_num(UART_MODULE_2), false},
    #endif
    #ifdef UART2_RX_RD5_RP20
    {PD5, hal_ll_uart_module_num(UART_MODULE_2), false},
    #endif
    #ifdef UART2_RX_RD8_RP2
    {PD8, hal_ll_uart_module_num(UART_MODULE_2), false},
    #endif
    #ifdef UART2_RX_RD9_RP4
    {PD9, hal_ll_uart_module_num(UART_MODULE_2), false},
    #endif
    #ifdef UART2_RX_RF2_RP30
    {PF2, hal_ll_uart_module_num(UART_MODULE_2), false},
    #endif
    #ifdef UART2_RX_RF3_RP16
    {PF3, hal_ll_uart_module_num(UART_MODULE_2), false},
    #endif
    #ifdef UART2_RX_RF4_RP10
    {PF4, hal_ll_uart_module_num(UART_MODULE_2), false},
    #endif
    #ifdef UART2_RX_RF5_RP17
    {PF5, hal_ll_uart_module_num(UART_MODULE_2), false},
    #endif
    #ifdef UART2_RX_RG6_RP21
    {PG6, hal_ll_uart_module_num(UART_MODULE_2), false},
    #endif
    #ifdef UART2_RX_RG7_RP26
    {PG7, hal_ll_uart_module_num(UART_MODULE_2), false},
    #endif
    #ifdef UART2_RX_RG8_RP19
    {PG8, hal_ll_uart_module_num(UART_MODULE_2), false},
    #endif
    #ifdef UART2_RX_RG9_RP27
    {PG9, hal_ll_uart_module_num(UART_MODULE_2), false},
    #endif
    #ifdef UART3_RX_RB0_RP0
    {PB0, hal_ll_uart_module_num(UART_MODULE_3), false},
    #endif
    #ifdef UART3_RX_RB1_RP1
    {PB1, hal_ll_uart_module_num(UART_MODULE_3), false},
    #endif
    #ifdef UART3_RX_RB14_RP14
    {PB14, hal_ll_uart_module_num(UART_MODULE_3), false},
    #endif
    #ifdef UART3_RX_RB15_RP29
    {PB15, hal_ll_uart_module_num(UART_MODULE_3), false},
    #endif
    #ifdef UART3_RX_RB2_RP13
    {PB2, hal_ll_uart_module_num(UART_MODULE_3), false},
    #endif
    #ifdef UART3_RX_RB4_RP28
    {PB4, hal_ll_uart_module_num(UART_MODULE_3), false},
    #endif
    #ifdef UART3_RX_RB5_RP18
    {PB5, hal_ll_uart_module_num(UART_MODULE_3), false},
    #endif
    #ifdef UART3_RX_RB6_RP6
    {PB6, hal_ll_uart_module_num(UART_MODULE_3), false},
    #endif
    #ifdef UART3_RX_RB7_RP7
    {PB7, hal_ll_uart_module_num(UART_MODULE_3), false},
    #endif
    #ifdef UART3_RX_RB8_RP8
    {PB8, hal_ll_uart_module_num(UART_MODULE_3), false},
    #endif
    #ifdef UART3_RX_RB9_RP9
    {PB9, hal_ll_uart_module_num(UART_MODULE_3), false},
    #endif
    #ifdef UART3_RX_RC14_RPI37
    {PC14, hal_ll_uart_module_num(UART_MODULE_3), false},
    #endif
    #ifdef UART3_RX_RD0_RP11
    {PD0, hal_ll_uart_module_num(UART_MODULE_3), false},
    #endif
    #ifdef UART3_RX_RD1_RP24
    {PD1, hal_ll_uart_module_num(UART_MODULE_3), false},
    #endif
    #ifdef UART3_RX_RD10_RP3
    {PD10, hal_ll_uart_module_num(UART_MODULE_3), false},
    #endif
    #ifdef UART3_RX_RD11_RP12
    {PD11, hal_ll_uart_module_num(UART_MODULE_3), false},
    #endif
    #ifdef UART3_RX_RD2_RP23
    {PD2, hal_ll_uart_module_num(UART_MODULE_3), false},
    #endif
    #ifdef UART3_RX_RD3_RP22
    {PD3, hal_ll_uart_module_num(UART_MODULE_3), false},
    #endif
    #ifdef UART3_RX_RD4_RP25
    {PD4, hal_ll_uart_module_num(UART_MODULE_3), false},
    #endif
    #ifdef UART3_RX_RD5_RP20
    {PD5, hal_ll_uart_module_num(UART_MODULE_3), false},
    #endif
    #ifdef UART3_RX_RD8_RP2
    {PD8, hal_ll_uart_module_num(UART_MODULE_3), false},
    #endif
    #ifdef UART3_RX_RD9_RP4
    {PD9, hal_ll_uart_module_num(UART_MODULE_3), false},
    #endif
    #ifdef UART3_RX_RF2_RP30
    {PF2, hal_ll_uart_module_num(UART_MODULE_3), false},
    #endif
    #ifdef UART3_RX_RF3_RP16
    {PF3, hal_ll_uart_module_num(UART_MODULE_3), false},
    #endif
    #ifdef UART3_RX_RF4_RP10
    {PF4, hal_ll_uart_module_num(UART_MODULE_3), false},
    #endif
    #ifdef UART3_RX_RF5_RP17
    {PF5, hal_ll_uart_module_num(UART_MODULE_3), false},
    #endif
    #ifdef UART3_RX_RG6_RP21
    {PG6, hal_ll_uart_module_num(UART_MODULE_3), false},
    #endif
    #ifdef UART3_RX_RG7_RP26
    {PG7, hal_ll_uart_module_num(UART_MODULE_3), false},
    #endif
    #ifdef UART3_RX_RG8_RP19
    {PG8, hal_ll_uart_module_num(UART_MODULE_3), false},
    #endif
    #ifdef UART3_RX_RG9_RP27
    {PG9, hal_ll_uart_module_num(UART_MODULE_3), false},
    #endif
    #ifdef UART4_RX_RB0_RP0
    {PB0, hal_ll_uart_module_num(UART_MODULE_4), false},
    #endif
    #ifdef UART4_RX_RB1_RP1
    {PB1, hal_ll_uart_module_num(UART_MODULE_4), false},
    #endif
    #ifdef UART4_RX_RB14_RP14
    {PB14, hal_ll_uart_module_num(UART_MODULE_4), false},
    #endif
    #ifdef UART4_RX_RB15_RP29
    {PB15, hal_ll_uart_module_num(UART_MODULE_4), false},
    #endif
    #ifdef UART4_RX_RB2_RP13
    {PB2, hal_ll_uart_module_num(UART_MODULE_4), false},
    #endif
    #ifdef UART4_RX_RB4_RP28
    {PB4, hal_ll_uart_module_num(UART_MODULE_4), false},
    #endif
    #ifdef UART4_RX_RB5_RP18
    {PB5, hal_ll_uart_module_num(UART_MODULE_4), false},
    #endif
    #ifdef UART4_RX_RB6_RP6
    {PB6, hal_ll_uart_module_num(UART_MODULE_4), false},
    #endif
    #ifdef UART4_RX_RB7_RP7
    {PB7, hal_ll_uart_module_num(UART_MODULE_4), false},
    #endif
    #ifdef UART4_RX_RB8_RP8
    {PB8, hal_ll_uart_module_num(UART_MODULE_4), false},
    #endif
    #ifdef UART4_RX_RB9_RP9
    {PB9, hal_ll_uart_module_num(UART_MODULE_4), false},
    #endif
    #ifdef UART4_RX_RC14_RPI37
    {PC14, hal_ll_uart_module_num(UART_MODULE_4), false},
    #endif
    #ifdef UART4_RX_RD0_RP11
    {PD0, hal_ll_uart_module_num(UART_MODULE_4), false},
    #endif
    #ifdef UART4_RX_RD1_RP24
    {PD1, hal_ll_uart_module_num(UART_MODULE_4), false},
    #endif
    #ifdef UART4_RX_RD10_RP3
    {PD10, hal_ll_uart_module_num(UART_MODULE_4), false},
    #endif
    #ifdef UART4_RX_RD11_RP12
    {PD11, hal_ll_uart_module_num(UART_MODULE_4), false},
    #endif
    #ifdef UART4_RX_RD2_RP23
    {PD2, hal_ll_uart_module_num(UART_MODULE_4), false},
    #endif
    #ifdef UART4_RX_RD3_RP22
    {PD3, hal_ll_uart_module_num(UART_MODULE_4), false},
    #endif
    #ifdef UART4_RX_RD4_RP25
    {PD4, hal_ll_uart_module_num(UART_MODULE_4), false},
    #endif
    #ifdef UART4_RX_RD5_RP20
    {PD5, hal_ll_uart_module_num(UART_MODULE_4), false},
    #endif
    #ifdef UART4_RX_RD8_RP2
    {PD8, hal_ll_uart_module_num(UART_MODULE_4), false},
    #endif
    #ifdef UART4_RX_RD9_RP4
    {PD9, hal_ll_uart_module_num(UART_MODULE_4), false},
    #endif
    #ifdef UART4_RX_RF2_RP30
    {PF2, hal_ll_uart_module_num(UART_MODULE_4), false},
    #endif
    #ifdef UART4_RX_RF3_RP16
    {PF3, hal_ll_uart_module_num(UART_MODULE_4), false},
    #endif
    #ifdef UART4_RX_RF4_RP10
    {PF4, hal_ll_uart_module_num(UART_MODULE_4), false},
    #endif
    #ifdef UART4_RX_RF5_RP17
    {PF5, hal_ll_uart_module_num(UART_MODULE_4), false},
    #endif
    #ifdef UART4_RX_RG6_RP21
    {PG6, hal_ll_uart_module_num(UART_MODULE_4), false},
    #endif
    #ifdef UART4_RX_RG7_RP26
    {PG7, hal_ll_uart_module_num(UART_MODULE_4), false},
    #endif
    #ifdef UART4_RX_RG8_RP19
    {PG8, hal_ll_uart_module_num(UART_MODULE_4), false},
    #endif
    #ifdef UART4_RX_RG9_RP27
    {PG9, hal_ll_uart_module_num(UART_MODULE_4), false},
    #endif
    #ifdef UART5_RX_RD6
    {PD6, hal_ll_uart_module_num(UART_MODULE_5), false},
    #endif
    #ifdef UART6_RX_RB12
    {PB12, hal_ll_uart_module_num(UART_MODULE_6), false},
    #endif
    #ifdef UART1_RX_RA14_RPI36
    {PA14, hal_ll_uart_module_num(UART_MODULE_1), false},
    #endif
    #ifdef UART1_RX_RA15_RPI35
    {PA15, hal_ll_uart_module_num(UART_MODULE_1), false},
    #endif
    #ifdef UART1_RX_RC1_RPI38
    {PC1, hal_ll_uart_module_num(UART_MODULE_1), false},
    #endif
    #ifdef UART1_RX_RC2_RPI39
    {PC2, hal_ll_uart_module_num(UART_MODULE_1), false},
    #endif
    #ifdef UART1_RX_RC3_RPI40
    {PC3, hal_ll_uart_module_num(UART_MODULE_1), false},
    #endif
    #ifdef UART1_RX_RC4_RPI41
    {PC4, hal_ll_uart_module_num(UART_MODULE_1), false},
    #endif
    #ifdef UART1_RX_RD12_RPI42
    {PD12, hal_ll_uart_module_num(UART_MODULE_1), false},
    #endif
    #ifdef UART1_RX_RD14_RPI43
    {PD14, hal_ll_uart_module_num(UART_MODULE_1), false},
    #endif
    #ifdef UART1_RX_RD15_RP5
    {PD15, hal_ll_uart_module_num(UART_MODULE_1), false},
    #endif
    #ifdef UART1_RX_RE8_RPI33
    {PE8, hal_ll_uart_module_num(UART_MODULE_1), false},
    #endif
    #ifdef UART1_RX_RE9_RPI34
    {PE9, hal_ll_uart_module_num(UART_MODULE_1), false},
    #endif
    #ifdef UART1_RX_RF12_RPI32
    {PF12, hal_ll_uart_module_num(UART_MODULE_1), false},
    #endif
    #ifdef UART1_RX_RF13_RP31
    {PF13, hal_ll_uart_module_num(UART_MODULE_1), false},
    #endif
    #ifdef UART1_RX_RF8_RP15
    {PF8, hal_ll_uart_module_num(UART_MODULE_1), false},
    #endif
    #ifdef UART2_RX_RA14_RPI36
    {PA14, hal_ll_uart_module_num(UART_MODULE_2), false},
    #endif
    #ifdef UART2_RX_RA15_RPI35
    {PA15, hal_ll_uart_module_num(UART_MODULE_2), false},
    #endif
    #ifdef UART2_RX_RC1_RPI38
    {PC1, hal_ll_uart_module_num(UART_MODULE_2), false},
    #endif
    #ifdef UART2_RX_RC2_RPI39
    {PC2, hal_ll_uart_module_num(UART_MODULE_2), false},
    #endif
    #ifdef UART2_RX_RC3_RPI40
    {PC3, hal_ll_uart_module_num(UART_MODULE_2), false},
    #endif
    #ifdef UART2_RX_RC4_RPI41
    {PC4, hal_ll_uart_module_num(UART_MODULE_2), false},
    #endif
    #ifdef UART2_RX_RD12_RPI42
    {PD12, hal_ll_uart_module_num(UART_MODULE_2), false},
    #endif
    #ifdef UART2_RX_RD14_RPI43
    {PD14, hal_ll_uart_module_num(UART_MODULE_2), false},
    #endif
    #ifdef UART2_RX_RD15_RP5
    {PD15, hal_ll_uart_module_num(UART_MODULE_2), false},
    #endif
    #ifdef UART2_RX_RE8_RPI33
    {PE8, hal_ll_uart_module_num(UART_MODULE_2), false},
    #endif
    #ifdef UART2_RX_RE9_RPI34
    {PE9, hal_ll_uart_module_num(UART_MODULE_2), false},
    #endif
    #ifdef UART2_RX_RF12_RPI32
    {PF12, hal_ll_uart_module_num(UART_MODULE_2), false},
    #endif
    #ifdef UART2_RX_RF13_RP31
    {PF13, hal_ll_uart_module_num(UART_MODULE_2), false},
    #endif
    #ifdef UART2_RX_RF8_RP15
    {PF8, hal_ll_uart_module_num(UART_MODULE_2), false},
    #endif
    #ifdef UART3_RX_RA14_RPI36
    {PA14, hal_ll_uart_module_num(UART_MODULE_3), false},
    #endif
    #ifdef UART3_RX_RA15_RPI35
    {PA15, hal_ll_uart_module_num(UART_MODULE_3), false},
    #endif
    #ifdef UART3_RX_RC1_RPI38
    {PC1, hal_ll_uart_module_num(UART_MODULE_3), false},
    #endif
    #ifdef UART3_RX_RC2_RPI39
    {PC2, hal_ll_uart_module_num(UART_MODULE_3), false},
    #endif
    #ifdef UART3_RX_RC3_RPI40
    {PC3, hal_ll_uart_module_num(UART_MODULE_3), false},
    #endif
    #ifdef UART3_RX_RC4_RPI41
    {PC4, hal_ll_uart_module_num(UART_MODULE_3), false},
    #endif
    #ifdef UART3_RX_RD12_RPI42
    {PD12, hal_ll_uart_module_num(UART_MODULE_3), false},
    #endif
    #ifdef UART3_RX_RD14_RPI43
    {PD14, hal_ll_uart_module_num(UART_MODULE_3), false},
    #endif
    #ifdef UART3_RX_RD15_RP5
    {PD15, hal_ll_uart_module_num(UART_MODULE_3), false},
    #endif
    #ifdef UART3_RX_RE8_RPI33
    {PE8, hal_ll_uart_module_num(UART_MODULE_3), false},
    #endif
    #ifdef UART3_RX_RE9_RPI34
    {PE9, hal_ll_uart_module_num(UART_MODULE_3), false},
    #endif
    #ifdef UART3_RX_RF12_RPI32
    {PF12, hal_ll_uart_module_num(UART_MODULE_3), false},
    #endif
    #ifdef UART3_RX_RF13_RP31
    {PF13, hal_ll_uart_module_num(UART_MODULE_3), false},
    #endif
    #ifdef UART3_RX_RF8_RP15
    {PF8, hal_ll_uart_module_num(UART_MODULE_3), false},
    #endif
    #ifdef UART4_RX_RA14_RPI36
    {PA14, hal_ll_uart_module_num(UART_MODULE_4), false},
    #endif
    #ifdef UART4_RX_RA15_RPI35
    {PA15, hal_ll_uart_module_num(UART_MODULE_4), false},
    #endif
    #ifdef UART4_RX_RC1_RPI38
    {PC1, hal_ll_uart_module_num(UART_MODULE_4), false},
    #endif
    #ifdef UART4_RX_RC2_RPI39
    {PC2, hal_ll_uart_module_num(UART_MODULE_4), false},
    #endif
    #ifdef UART4_RX_RC3_RPI40
    {PC3, hal_ll_uart_module_num(UART_MODULE_4), false},
    #endif
    #ifdef UART4_RX_RC4_RPI41
    {PC4, hal_ll_uart_module_num(UART_MODULE_4), false},
    #endif
    #ifdef UART4_RX_RD12_RPI42
    {PD12, hal_ll_uart_module_num(UART_MODULE_4), false},
    #endif
    #ifdef UART4_RX_RD14_RPI43
    {PD14, hal_ll_uart_module_num(UART_MODULE_4), false},
    #endif
    #ifdef UART4_RX_RD15_RP5
    {PD15, hal_ll_uart_module_num(UART_MODULE_4), false},
    #endif
    #ifdef UART4_RX_RE8_RPI33
    {PE8, hal_ll_uart_module_num(UART_MODULE_4), false},
    #endif
    #ifdef UART4_RX_RE9_RPI34
    {PE9, hal_ll_uart_module_num(UART_MODULE_4), false},
    #endif
    #ifdef UART4_RX_RF12_RPI32
    {PF12, hal_ll_uart_module_num(UART_MODULE_4), false},
    #endif
    #ifdef UART4_RX_RF13_RP31
    {PF13, hal_ll_uart_module_num(UART_MODULE_4), false},
    #endif
    #ifdef UART4_RX_RF8_RP15
    {PF8, hal_ll_uart_module_num(UART_MODULE_4), false},
    #endif
    #ifdef UART1_RX_RF6_RPI45
    {PF6, hal_ll_uart_module_num(UART_MODULE_1), false},
    #endif
    #ifdef UART2_RX_RF6_RPI45
    {PF6, hal_ll_uart_module_num(UART_MODULE_2), false},
    #endif
    #ifdef UART3_RX_RF6_RPI45
    {PF6, hal_ll_uart_module_num(UART_MODULE_3), false},
    #endif
    #ifdef UART4_RX_RF6_RPI45
    {PF6, hal_ll_uart_module_num(UART_MODULE_4), false},
    #endif
    #ifdef UART1_RX_RF7_RPI44
    {PF7, hal_ll_uart_module_num(UART_MODULE_1), false},
    #endif
    #ifdef UART2_RX_RF7_RPI44
    {PF7, hal_ll_uart_module_num(UART_MODULE_2), false},
    #endif
    #ifdef UART3_RX_RF7_RPI44
    {PF7, hal_ll_uart_module_num(UART_MODULE_3), false},
    #endif
    #ifdef UART4_RX_RF7_RPI44
    {PF7, hal_ll_uart_module_num(UART_MODULE_4), false},
    #endif
    #ifdef UART1_RX_RB4_RPI4
    {PB4, hal_ll_uart_module_num(UART_MODULE_1), false},
    #endif
    #ifdef UART2_RX_RB4_RPI4
    {PB4, hal_ll_uart_module_num(UART_MODULE_2), false},
    #endif
    #ifdef UART3_RX_RB10_RP10
    {PB10, hal_ll_uart_module_num(UART_MODULE_3), false},
    #endif
    #ifdef UART3_RX_RB11_RP11
    {PB11, hal_ll_uart_module_num(UART_MODULE_3), false},
    #endif
    #ifdef UART3_RX_RB12_RP12
    {PB12, hal_ll_uart_module_num(UART_MODULE_3), false},
    #endif
    #ifdef UART3_RX_RB13_RP13
    {PB13, hal_ll_uart_module_num(UART_MODULE_3), false},
    #endif
    #ifdef UART3_RX_RB15_RP15
    {PB15, hal_ll_uart_module_num(UART_MODULE_3), false},
    #endif
    #ifdef UART3_RX_RB2_RP2
    {PB2, hal_ll_uart_module_num(UART_MODULE_3), false},
    #endif
    #ifdef UART3_RX_RB3_RP3
    {PB3, hal_ll_uart_module_num(UART_MODULE_3), false},
    #endif
    #ifdef UART3_RX_RB4_RPI4
    {PB4, hal_ll_uart_module_num(UART_MODULE_3), false},
    #endif
    #ifdef UART3_RX_RB5_RP5
    {PB5, hal_ll_uart_module_num(UART_MODULE_3), false},
    #endif
    #ifdef UART4_RX_RB10_RP10
    {PB10, hal_ll_uart_module_num(UART_MODULE_4), false},
    #endif
    #ifdef UART4_RX_RB11_RP11
    {PB11, hal_ll_uart_module_num(UART_MODULE_4), false},
    #endif
    #ifdef UART4_RX_RB12_RP12
    {PB12, hal_ll_uart_module_num(UART_MODULE_4), false},
    #endif
    #ifdef UART4_RX_RB13_RP13
    {PB13, hal_ll_uart_module_num(UART_MODULE_4), false},
    #endif
    #ifdef UART4_RX_RB15_RP15
    {PB15, hal_ll_uart_module_num(UART_MODULE_4), false},
    #endif
    #ifdef UART4_RX_RB2_RP2
    {PB2, hal_ll_uart_module_num(UART_MODULE_4), false},
    #endif
    #ifdef UART4_RX_RB3_RP3
    {PB3, hal_ll_uart_module_num(UART_MODULE_4), false},
    #endif
    #ifdef UART4_RX_RB4_RPI4
    {PB4, hal_ll_uart_module_num(UART_MODULE_4), false},
    #endif
    #ifdef UART4_RX_RB5_RP5
    {PB5, hal_ll_uart_module_num(UART_MODULE_4), false},
    #endif
    #ifdef UART3_RX_RC0_RP16
    {PC0, hal_ll_uart_module_num(UART_MODULE_3), false},
    #endif
    #ifdef UART3_RX_RC1_RP17
    {PC1, hal_ll_uart_module_num(UART_MODULE_3), false},
    #endif
    #ifdef UART3_RX_RC2_RP18
    {PC2, hal_ll_uart_module_num(UART_MODULE_3), false},
    #endif
    #ifdef UART3_RX_RC3_RP19
    {PC3, hal_ll_uart_module_num(UART_MODULE_3), false},
    #endif
    #ifdef UART3_RX_RC4_RP20
    {PC4, hal_ll_uart_module_num(UART_MODULE_3), false},
    #endif
    #ifdef UART3_RX_RC5_RP21
    {PC5, hal_ll_uart_module_num(UART_MODULE_3), false},
    #endif
    #ifdef UART3_RX_RC6_RP22
    {PC6, hal_ll_uart_module_num(UART_MODULE_3), false},
    #endif
    #ifdef UART3_RX_RC7_RP23
    {PC7, hal_ll_uart_module_num(UART_MODULE_3), false},
    #endif
    #ifdef UART3_RX_RC8_RP24
    {PC8, hal_ll_uart_module_num(UART_MODULE_3), false},
    #endif
    #ifdef UART3_RX_RC9_RP25
    {PC9, hal_ll_uart_module_num(UART_MODULE_3), false},
    #endif
    #ifdef UART4_RX_RC0_RP16
    {PC0, hal_ll_uart_module_num(UART_MODULE_4), false},
    #endif
    #ifdef UART4_RX_RC1_RP17
    {PC1, hal_ll_uart_module_num(UART_MODULE_4), false},
    #endif
    #ifdef UART4_RX_RC2_RP18
    {PC2, hal_ll_uart_module_num(UART_MODULE_4), false},
    #endif
    #ifdef UART4_RX_RC3_RP19
    {PC3, hal_ll_uart_module_num(UART_MODULE_4), false},
    #endif
    #ifdef UART4_RX_RC4_RP20
    {PC4, hal_ll_uart_module_num(UART_MODULE_4), false},
    #endif
    #ifdef UART4_RX_RC5_RP21
    {PC5, hal_ll_uart_module_num(UART_MODULE_4), false},
    #endif
    #ifdef UART4_RX_RC6_RP22
    {PC6, hal_ll_uart_module_num(UART_MODULE_4), false},
    #endif
    #ifdef UART4_RX_RC7_RP23
    {PC7, hal_ll_uart_module_num(UART_MODULE_4), false},
    #endif
    #ifdef UART4_RX_RC8_RP24
    {PC8, hal_ll_uart_module_num(UART_MODULE_4), false},
    #endif
    #ifdef UART4_RX_RC9_RP25
    {PC9, hal_ll_uart_module_num(UART_MODULE_4), false},
    #endif
    #ifdef UART1_RX_RA0_RP26
    {PA0, hal_ll_uart_module_num(UART_MODULE_1), false},
    #endif
    #ifdef UART1_RX_RA1_RP27
    {PA1, hal_ll_uart_module_num(UART_MODULE_1), false},
    #endif
    #ifdef UART2_RX_RA0_RP26
    {PA0, hal_ll_uart_module_num(UART_MODULE_2), false},
    #endif
    #ifdef UART2_RX_RA1_RP27
    {PA1, hal_ll_uart_module_num(UART_MODULE_2), false},
    #endif
    #ifdef UART1_RX_RA10_RP28
    {PA10, hal_ll_uart_module_num(UART_MODULE_1), false},
    #endif
    #ifdef UART2_RX_RA10_RP28
    {PA10, hal_ll_uart_module_num(UART_MODULE_2), false},
    #endif
    #ifdef UART1_RX_RA11_RPIN29
    {PA11, hal_ll_uart_module_num(UART_MODULE_1), false},
    #endif
    #ifdef UART1_RX_RA12_RPIN30
    {PA12, hal_ll_uart_module_num(UART_MODULE_1), false},
    #endif
    #ifdef UART1_RX_RA13_RPIN31
    {PA13, hal_ll_uart_module_num(UART_MODULE_1), false},
    #endif
    #ifdef UART1_RX_RA14_RPIN32
    {PA14, hal_ll_uart_module_num(UART_MODULE_1), false},
    #endif
    #ifdef UART2_RX_RA11_RPIN29
    {PA11, hal_ll_uart_module_num(UART_MODULE_2), false},
    #endif
    #ifdef UART2_RX_RA12_RPIN30
    {PA12, hal_ll_uart_module_num(UART_MODULE_2), false},
    #endif
    #ifdef UART2_RX_RA13_RPIN31
    {PA13, hal_ll_uart_module_num(UART_MODULE_2), false},
    #endif
    #ifdef UART2_RX_RA14_RPIN32
    {PA14, hal_ll_uart_module_num(UART_MODULE_2), false},
    #endif
    #ifdef UART1_RX_RA0_RP5
    {PA0, hal_ll_uart_module_num(UART_MODULE_1), false},
    #endif
    #ifdef UART1_RX_RA1_RP6
    {PA1, hal_ll_uart_module_num(UART_MODULE_1), false},
    #endif
    #ifdef UART2_RX_RA0_RP5
    {PA0, hal_ll_uart_module_num(UART_MODULE_2), false},
    #endif
    #ifdef UART2_RX_RA1_RP6
    {PA1, hal_ll_uart_module_num(UART_MODULE_2), false},
    #endif
    #ifdef UART3_RX_RA0_RP5
    {PA0, hal_ll_uart_module_num(UART_MODULE_3), false},
    #endif
    #ifdef UART3_RX_RA1_RP6
    {PA1, hal_ll_uart_module_num(UART_MODULE_3), false},
    #endif
    #ifdef UART4_RX_RA0_RP5
    {PA0, hal_ll_uart_module_num(UART_MODULE_4), false},
    #endif
    #ifdef UART4_RX_RA1_RP6
    {PA1, hal_ll_uart_module_num(UART_MODULE_4), false},
    #endif
    { HAL_LL_PIN_NC, HAL_LL_MODULE_ERROR, false }
    //------------ END RX
};

#ifdef __cplusplus
}
#endif

#endif // _HAL_LL_UART_PIN_MAP_H_
// ------------------------------------------------------------------------- END
