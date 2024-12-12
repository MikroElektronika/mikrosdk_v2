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
/*!
 * @file  hal_ll_can_pin_map.h
 * @brief CAN HAL LOW LEVEL PIN MAPS.
 */

#ifndef _HAL_LL_CAN_PIN_MAP_H_
#define _HAL_LL_CAN_PIN_MAP_H_

#ifdef __cplusplus
extern "C"{
#endif

#include "hal_ll_pin_names.h"

/*!< @brief Helper macro for getting adequate module index number */
#define hal_ll_can_module_num(_module_num) (_module_num - 1)

/*!< @brief Macro defining `weak` attribute */
#define __weak __attribute__((weak))

/*!< @brief Pin structure */
typedef struct
{
    uint8_t module_index;
    hal_ll_pin_name_t pin;
    hal_ll_base_addr_t base;
} hal_ll_can_pin_map_t;

/*!< @brief CAN RX pins */
static const hal_ll_can_pin_map_t hal_ll_can_rx_map[] =
{
    //------------ BEGIN RX
    #ifdef CAN1_RX_RF0
    {hal_ll_can_module_num(CAN_MODULE_1), GPIO_PF0, HAL_LL_CAN1_BASE_ADDRESS},
    #endif
    #ifdef CAN2_RX_RG0
    {hal_ll_can_module_num(CAN_MODULE_2), GPIO_PG0, HAL_LL_CAN2_BASE_ADDRESS},
    #endif
    #ifdef CAN1_RX_RB9_RP41
    {hal_ll_can_module_num(CAN_MODULE_1), GPIO_PB9, HAL_LL_CAN1_BASE_ADDRESS},
    #endif
    #ifdef CAN2_RX_RB9_RP41
    {hal_ll_can_module_num(CAN_MODULE_2), GPIO_PB9, HAL_LL_CAN2_BASE_ADDRESS},
    #endif
    #ifdef CAN1_RX_RC6_RP54
    {hal_ll_can_module_num(CAN_MODULE_1), GPIO_PC6, HAL_LL_CAN1_BASE_ADDRESS},
    #endif
    #ifdef CAN2_RX_RC6_RP54
    {hal_ll_can_module_num(CAN_MODULE_2), GPIO_PC6, HAL_LL_CAN2_BASE_ADDRESS},
    #endif
    #ifdef CAN1_RX_RC7_RP55
    {hal_ll_can_module_num(CAN_MODULE_1), GPIO_PC7, HAL_LL_CAN1_BASE_ADDRESS},
    #endif
    #ifdef CAN2_RX_RC7_RP55
    {hal_ll_can_module_num(CAN_MODULE_2), GPIO_PC7, HAL_LL_CAN2_BASE_ADDRESS},
    #endif
    #ifdef CAN1_RX_RC8_RP56
    {hal_ll_can_module_num(CAN_MODULE_1), GPIO_PC8, HAL_LL_CAN1_BASE_ADDRESS},
    #endif
    #ifdef CAN2_RX_RC8_RP56
    {hal_ll_can_module_num(CAN_MODULE_2), GPIO_PC8, HAL_LL_CAN2_BASE_ADDRESS},
    #endif
    #ifdef CAN1_RX_RC9_RP57
    {hal_ll_can_module_num(CAN_MODULE_1), GPIO_PC9, HAL_LL_CAN1_BASE_ADDRESS},
    #endif
    #ifdef CAN2_RX_RC9_RP57
    {hal_ll_can_module_num(CAN_MODULE_2), GPIO_PC9, HAL_LL_CAN2_BASE_ADDRESS},
    #endif
    #ifdef CAN1_RX_RB10_RP42
    {hal_ll_can_module_num(CAN_MODULE_1), GPIO_PB10, HAL_LL_CAN1_BASE_ADDRESS},
    #endif
    #ifdef CAN2_RX_RB10_RP42
    {hal_ll_can_module_num(CAN_MODULE_2), GPIO_PB10, HAL_LL_CAN2_BASE_ADDRESS},
    #endif
    #ifdef CAN1_RX_RB11_RP43
    {hal_ll_can_module_num(CAN_MODULE_1), GPIO_PB11, HAL_LL_CAN1_BASE_ADDRESS},
    #endif
    #ifdef CAN2_RX_RB11_RP43
    {hal_ll_can_module_num(CAN_MODULE_2), GPIO_PB11, HAL_LL_CAN2_BASE_ADDRESS},
    #endif
    #ifdef CAN1_RX_RB3_RP35
    {hal_ll_can_module_num(CAN_MODULE_1), GPIO_PB3, HAL_LL_CAN1_BASE_ADDRESS},
    #endif
    #ifdef CAN2_RX_RB3_RP35
    {hal_ll_can_module_num(CAN_MODULE_2), GPIO_PB3, HAL_LL_CAN2_BASE_ADDRESS},
    #endif
    #ifdef CAN1_RX_RC0_RP48
    {hal_ll_can_module_num(CAN_MODULE_1), GPIO_PC0, HAL_LL_CAN1_BASE_ADDRESS},
    #endif
    #ifdef CAN2_RX_RC0_RP48
    {hal_ll_can_module_num(CAN_MODULE_2), GPIO_PC0, HAL_LL_CAN2_BASE_ADDRESS},
    #endif
    #ifdef CAN1_RX_RC1_RP49
    {hal_ll_can_module_num(CAN_MODULE_1), GPIO_PC1, HAL_LL_CAN1_BASE_ADDRESS},
    #endif
    #ifdef CAN2_RX_RC1_RP49
    {hal_ll_can_module_num(CAN_MODULE_2), GPIO_PC1, HAL_LL_CAN2_BASE_ADDRESS},
    #endif
    #ifdef CAN1_RX_RB4_RP36
    {hal_ll_can_module_num(CAN_MODULE_1), GPIO_PB4, HAL_LL_CAN1_BASE_ADDRESS},
    #endif
    #ifdef CAN2_RX_RB4_RP36
    {hal_ll_can_module_num(CAN_MODULE_2), GPIO_PB4, HAL_LL_CAN2_BASE_ADDRESS},
    #endif
    #ifdef CAN1_RX_RA4_RP20
    {hal_ll_can_module_num(CAN_MODULE_1), GPIO_PA4, HAL_LL_CAN1_BASE_ADDRESS},
    #endif
    #ifdef CAN2_RX_RA4_RP20
    {hal_ll_can_module_num(CAN_MODULE_2), GPIO_PA4, HAL_LL_CAN2_BASE_ADDRESS},
    #endif
    #ifdef CAN1_RX_RB5_RP37
    {hal_ll_can_module_num(CAN_MODULE_1), GPIO_PB5, HAL_LL_CAN1_BASE_ADDRESS},
    #endif
    #ifdef CAN2_RX_RB5_RP37
    {hal_ll_can_module_num(CAN_MODULE_2), GPIO_PB5, HAL_LL_CAN2_BASE_ADDRESS},
    #endif
    #ifdef CAN1_RX_RB6_RP38
    {hal_ll_can_module_num(CAN_MODULE_1), GPIO_PB6, HAL_LL_CAN1_BASE_ADDRESS},
    #endif
    #ifdef CAN2_RX_RB6_RP38
    {hal_ll_can_module_num(CAN_MODULE_2), GPIO_PB6, HAL_LL_CAN2_BASE_ADDRESS},
    #endif
    #ifdef CAN1_RX_RB7_RP39
    {hal_ll_can_module_num(CAN_MODULE_1), GPIO_PB7, HAL_LL_CAN1_BASE_ADDRESS},
    #endif
    #ifdef CAN2_RX_RB7_RP39
    {hal_ll_can_module_num(CAN_MODULE_2), GPIO_PB7, HAL_LL_CAN2_BASE_ADDRESS},
    #endif
    #ifdef CAN1_RX_RB8_RP40
    {hal_ll_can_module_num(CAN_MODULE_1), GPIO_PB8, HAL_LL_CAN1_BASE_ADDRESS},
    #endif
    #ifdef CAN2_RX_RB8_RP40
    {hal_ll_can_module_num(CAN_MODULE_2), GPIO_PB8, HAL_LL_CAN2_BASE_ADDRESS},
    #endif
    #ifdef CAN1_RX_RB12_RPI44
    {hal_ll_can_module_num(CAN_MODULE_1), GPIO_PB12, HAL_LL_CAN1_BASE_ADDRESS},
    #endif
    #ifdef CAN2_RX_RB12_RPI44
    {hal_ll_can_module_num(CAN_MODULE_2), GPIO_PB12, HAL_LL_CAN2_BASE_ADDRESS},
    #endif
    #ifdef CAN1_RX_RB13_RPI45
    {hal_ll_can_module_num(CAN_MODULE_1), GPIO_PB13, HAL_LL_CAN1_BASE_ADDRESS},
    #endif
    #ifdef CAN2_RX_RB13_RPI45
    {hal_ll_can_module_num(CAN_MODULE_2), GPIO_PB13, HAL_LL_CAN2_BASE_ADDRESS},
    #endif
    #ifdef CAN1_RX_RB14_RPI46
    {hal_ll_can_module_num(CAN_MODULE_1), GPIO_PB14, HAL_LL_CAN1_BASE_ADDRESS},
    #endif
    #ifdef CAN2_RX_RB14_RPI46
    {hal_ll_can_module_num(CAN_MODULE_2), GPIO_PB14, HAL_LL_CAN2_BASE_ADDRESS},
    #endif
    #ifdef CAN1_RX_RB15_RPI47
    {hal_ll_can_module_num(CAN_MODULE_1), GPIO_PB15, HAL_LL_CAN1_BASE_ADDRESS},
    #endif
    #ifdef CAN2_RX_RB15_RPI47
    {hal_ll_can_module_num(CAN_MODULE_2), GPIO_PB15, HAL_LL_CAN2_BASE_ADDRESS},
    #endif
    #ifdef CAN1_RX_RA0_RPI16
    {hal_ll_can_module_num(CAN_MODULE_1), GPIO_PA0, HAL_LL_CAN1_BASE_ADDRESS},
    #endif
    #ifdef CAN2_RX_RA0_RPI16
    {hal_ll_can_module_num(CAN_MODULE_2), GPIO_PA0, HAL_LL_CAN2_BASE_ADDRESS},
    #endif
    #ifdef CAN1_RX_RA1_RPI17
    {hal_ll_can_module_num(CAN_MODULE_1), GPIO_PA1, HAL_LL_CAN1_BASE_ADDRESS},
    #endif
    #ifdef CAN2_RX_RA1_RPI17
    {hal_ll_can_module_num(CAN_MODULE_2), GPIO_PA1, HAL_LL_CAN2_BASE_ADDRESS},
    #endif
    #ifdef CAN1_RX_RB0_RPI32
    {hal_ll_can_module_num(CAN_MODULE_1), GPIO_PB0, HAL_LL_CAN1_BASE_ADDRESS},
    #endif
    #ifdef CAN2_RX_RB0_RPI32
    {hal_ll_can_module_num(CAN_MODULE_2), GPIO_PB0, HAL_LL_CAN2_BASE_ADDRESS},
    #endif
    #ifdef CAN1_RX_RB1_RPI33
    {hal_ll_can_module_num(CAN_MODULE_1), GPIO_PB1, HAL_LL_CAN1_BASE_ADDRESS},
    #endif
    #ifdef CAN2_RX_RB1_RPI33
    {hal_ll_can_module_num(CAN_MODULE_2), GPIO_PB1, HAL_LL_CAN2_BASE_ADDRESS},
    #endif
    #ifdef CAN1_RX_RB2_RPI34
    {hal_ll_can_module_num(CAN_MODULE_1), GPIO_PB2, HAL_LL_CAN1_BASE_ADDRESS},
    #endif
    #ifdef CAN2_RX_RB2_RPI34
    {hal_ll_can_module_num(CAN_MODULE_2), GPIO_PB2, HAL_LL_CAN2_BASE_ADDRESS},
    #endif
    #ifdef CAN1_RX_RC2_RPI50
    {hal_ll_can_module_num(CAN_MODULE_1), GPIO_PC2, HAL_LL_CAN1_BASE_ADDRESS},
    #endif
    #ifdef CAN2_RX_RC2_RPI50
    {hal_ll_can_module_num(CAN_MODULE_2), GPIO_PC2, HAL_LL_CAN2_BASE_ADDRESS},
    #endif
    #ifdef CAN1_RX_RA2_RPI18
    {hal_ll_can_module_num(CAN_MODULE_1), GPIO_PA2, HAL_LL_CAN1_BASE_ADDRESS},
    #endif
    #ifdef CAN2_RX_RA2_RPI18
    {hal_ll_can_module_num(CAN_MODULE_2), GPIO_PA2, HAL_LL_CAN2_BASE_ADDRESS},
    #endif
    #ifdef CAN1_RX_RA3_RPI19
    {hal_ll_can_module_num(CAN_MODULE_1), GPIO_PA3, HAL_LL_CAN1_BASE_ADDRESS},
    #endif
    #ifdef CAN2_RX_RA3_RPI19
    {hal_ll_can_module_num(CAN_MODULE_2), GPIO_PA3, HAL_LL_CAN2_BASE_ADDRESS},
    #endif
    #ifdef CAN1_RX_RA8_RPI24
    {hal_ll_can_module_num(CAN_MODULE_1), GPIO_PA8, HAL_LL_CAN1_BASE_ADDRESS},
    #endif
    #ifdef CAN2_RX_RA8_RPI24
    {hal_ll_can_module_num(CAN_MODULE_2), GPIO_PA8, HAL_LL_CAN2_BASE_ADDRESS},
    #endif
    #ifdef CAN1_RX_RA9_RPI25
    {hal_ll_can_module_num(CAN_MODULE_1), GPIO_PA9, HAL_LL_CAN1_BASE_ADDRESS},
    #endif
    #ifdef CAN2_RX_RA9_RPI25
    {hal_ll_can_module_num(CAN_MODULE_2), GPIO_PA9, HAL_LL_CAN2_BASE_ADDRESS},
    #endif
    #ifdef CAN1_RX_RC3_RPI51
    {hal_ll_can_module_num(CAN_MODULE_1), GPIO_PC3, HAL_LL_CAN1_BASE_ADDRESS},
    #endif
    #ifdef CAN2_RX_RC3_RPI51
    {hal_ll_can_module_num(CAN_MODULE_2), GPIO_PC3, HAL_LL_CAN2_BASE_ADDRESS},
    #endif
    #ifdef CAN1_RX_RC4_RPI52
    {hal_ll_can_module_num(CAN_MODULE_1), GPIO_PC4, HAL_LL_CAN1_BASE_ADDRESS},
    #endif
    #ifdef CAN2_RX_RC4_RPI52
    {hal_ll_can_module_num(CAN_MODULE_2), GPIO_PC4, HAL_LL_CAN2_BASE_ADDRESS},
    #endif
    #ifdef CAN1_RX_RC5_RPI53
    {hal_ll_can_module_num(CAN_MODULE_1), GPIO_PC5, HAL_LL_CAN1_BASE_ADDRESS},
    #endif
    #ifdef CAN2_RX_RC5_RPI53
    {hal_ll_can_module_num(CAN_MODULE_2), GPIO_PC5, HAL_LL_CAN2_BASE_ADDRESS},
    #endif
    #ifdef CAN1_RX_RG8_RP120
    {hal_ll_can_module_num(CAN_MODULE_1), GPIO_PG8, HAL_LL_CAN1_BASE_ADDRESS},
    #endif
    #ifdef CAN2_RX_RG8_RP120
    {hal_ll_can_module_num(CAN_MODULE_2), GPIO_PG8, HAL_LL_CAN2_BASE_ADDRESS},
    #endif
    #ifdef CAN1_RX_RD5_RP69
    {hal_ll_can_module_num(CAN_MODULE_1), GPIO_PD5, HAL_LL_CAN1_BASE_ADDRESS},
    #endif
    #ifdef CAN2_RX_RD5_RP69
    {hal_ll_can_module_num(CAN_MODULE_2), GPIO_PD5, HAL_LL_CAN2_BASE_ADDRESS},
    #endif
    #ifdef CAN1_RX_RD6_RP70
    {hal_ll_can_module_num(CAN_MODULE_1), GPIO_PD6, HAL_LL_CAN1_BASE_ADDRESS},
    #endif
    #ifdef CAN2_RX_RD6_RP70
    {hal_ll_can_module_num(CAN_MODULE_2), GPIO_PD6, HAL_LL_CAN2_BASE_ADDRESS},
    #endif
    #ifdef CAN1_RX_RF1_RP97
    {hal_ll_can_module_num(CAN_MODULE_1), GPIO_PF1, HAL_LL_CAN1_BASE_ADDRESS},
    #endif
    #ifdef CAN2_RX_RF1_RP97
    {hal_ll_can_module_num(CAN_MODULE_2), GPIO_PF1, HAL_LL_CAN2_BASE_ADDRESS},
    #endif
    #ifdef CAN1_RX_RG6_RPI18
    {hal_ll_can_module_num(CAN_MODULE_1), GPIO_PG6, HAL_LL_CAN1_BASE_ADDRESS},
    #endif
    #ifdef CAN2_RX_RG6_RPI18
    {hal_ll_can_module_num(CAN_MODULE_2), GPIO_PG6, HAL_LL_CAN2_BASE_ADDRESS},
    #endif
    #ifdef CAN1_RX_RG7_RPI119
    {hal_ll_can_module_num(CAN_MODULE_1), GPIO_PG7, HAL_LL_CAN1_BASE_ADDRESS},
    #endif
    #ifdef CAN2_RX_RG7_RPI119
    {hal_ll_can_module_num(CAN_MODULE_2), GPIO_PG7, HAL_LL_CAN2_BASE_ADDRESS},
    #endif
    #ifdef CAN1_RX_RG9_RPI121
    {hal_ll_can_module_num(CAN_MODULE_1), GPIO_PG9, HAL_LL_CAN1_BASE_ADDRESS},
    #endif
    #ifdef CAN2_RX_RG9_RPI121
    {hal_ll_can_module_num(CAN_MODULE_2), GPIO_PG9, HAL_LL_CAN2_BASE_ADDRESS},
    #endif
    #ifdef CAN1_RX_RA12_RPI28
    {hal_ll_can_module_num(CAN_MODULE_1), GPIO_PA12, HAL_LL_CAN1_BASE_ADDRESS},
    #endif
    #ifdef CAN2_RX_RA12_RPI28
    {hal_ll_can_module_num(CAN_MODULE_2), GPIO_PA12, HAL_LL_CAN2_BASE_ADDRESS},
    #endif
    #ifdef CAN1_RX_RA11_RPI27
    {hal_ll_can_module_num(CAN_MODULE_1), GPIO_PA11, HAL_LL_CAN1_BASE_ADDRESS},
    #endif
    #ifdef CAN2_RX_RA11_RPI27
    {hal_ll_can_module_num(CAN_MODULE_2), GPIO_PA11, HAL_LL_CAN2_BASE_ADDRESS},
    #endif
    #ifdef CAN1_RX_RE14_RPI94
    {hal_ll_can_module_num(CAN_MODULE_1), GPIO_PE14, HAL_LL_CAN1_BASE_ADDRESS},
    #endif
    #ifdef CAN2_RX_RE14_RPI94
    {hal_ll_can_module_num(CAN_MODULE_2), GPIO_PE14, HAL_LL_CAN2_BASE_ADDRESS},
    #endif
    #ifdef CAN1_RX_RE15_RPI95
    {hal_ll_can_module_num(CAN_MODULE_1), GPIO_PE15, HAL_LL_CAN1_BASE_ADDRESS},
    #endif
    #ifdef CAN2_RX_RE15_RPI95
    {hal_ll_can_module_num(CAN_MODULE_2), GPIO_PE15, HAL_LL_CAN2_BASE_ADDRESS},
    #endif
    #ifdef CAN1_RX_RC12_RPI60
    {hal_ll_can_module_num(CAN_MODULE_1), GPIO_PC12, HAL_LL_CAN1_BASE_ADDRESS},
    #endif
    #ifdef CAN2_RX_RC12_RPI60
    {hal_ll_can_module_num(CAN_MODULE_2), GPIO_PC12, HAL_LL_CAN2_BASE_ADDRESS},
    #endif
    #ifdef CAN1_RX_RC15_RPI63
    {hal_ll_can_module_num(CAN_MODULE_1), GPIO_PC15, HAL_LL_CAN1_BASE_ADDRESS},
    #endif
    #ifdef CAN2_RX_RC15_RPI63
    {hal_ll_can_module_num(CAN_MODULE_2), GPIO_PC15, HAL_LL_CAN2_BASE_ADDRESS},
    #endif
    #ifdef CAN1_RX_RD8_RPI72
    {hal_ll_can_module_num(CAN_MODULE_1), GPIO_PD8, HAL_LL_CAN1_BASE_ADDRESS},
    #endif
    #ifdef CAN2_RX_RD8_RPI72
    {hal_ll_can_module_num(CAN_MODULE_2), GPIO_PD8, HAL_LL_CAN2_BASE_ADDRESS},
    #endif
    #ifdef CAN1_RX_RC10_RPI58
    {hal_ll_can_module_num(CAN_MODULE_1), GPIO_PC10, HAL_LL_CAN1_BASE_ADDRESS},
    #endif
    #ifdef CAN2_RX_RC10_RPI58
    {hal_ll_can_module_num(CAN_MODULE_2), GPIO_PC10, HAL_LL_CAN2_BASE_ADDRESS},
    #endif
    #ifdef CAN1_RX_RC13_RPI61
    {hal_ll_can_module_num(CAN_MODULE_1), GPIO_PC13, HAL_LL_CAN1_BASE_ADDRESS},
    #endif
    #ifdef CAN2_RX_RC13_RPI61
    {hal_ll_can_module_num(CAN_MODULE_2), GPIO_PC13, HAL_LL_CAN2_BASE_ADDRESS},
    #endif
    #ifdef CAN1_RX_RF0_RPI96
    {hal_ll_can_module_num(CAN_MODULE_1), GPIO_PF0, HAL_LL_CAN1_BASE_ADDRESS},
    #endif
    #ifdef CAN2_RX_RF0_RPI96
    {hal_ll_can_module_num(CAN_MODULE_2), GPIO_PF0, HAL_LL_CAN2_BASE_ADDRESS},
    #endif
    #ifdef CAN1_RX_RG15_RP127
    {hal_ll_can_module_num(CAN_MODULE_1), GPIO_PG15, HAL_LL_CAN1_BASE_ADDRESS},
    #endif
    #ifdef CAN2_RX_RG15_RP127
    {hal_ll_can_module_num(CAN_MODULE_2), GPIO_PG15, HAL_LL_CAN2_BASE_ADDRESS},
    #endif
    #ifdef CAN1_RX_RG6_RP118
    {hal_ll_can_module_num(CAN_MODULE_1), GPIO_PG6, HAL_LL_CAN1_BASE_ADDRESS},
    #endif
    #ifdef CAN2_RX_RG6_RP118
    {hal_ll_can_module_num(CAN_MODULE_2), GPIO_PG6, HAL_LL_CAN2_BASE_ADDRESS},
    #endif
    #ifdef CAN1_RX_RE1_RP81
    {hal_ll_can_module_num(CAN_MODULE_1), GPIO_PE1, HAL_LL_CAN1_BASE_ADDRESS},
    #endif
    #ifdef CAN2_RX_RE1_RP81
    {hal_ll_can_module_num(CAN_MODULE_2), GPIO_PE1, HAL_LL_CAN2_BASE_ADDRESS},
    #endif
    #ifdef CAN1_RX_RG1_RP113
    {hal_ll_can_module_num(CAN_MODULE_1), GPIO_PG1, HAL_LL_CAN1_BASE_ADDRESS},
    #endif
    #ifdef CAN2_RX_RG1_RP113
    {hal_ll_can_module_num(CAN_MODULE_2), GPIO_PG1, HAL_LL_CAN2_BASE_ADDRESS},
    #endif
    #ifdef CAN1_RX_RG14_RP126
    {hal_ll_can_module_num(CAN_MODULE_1), GPIO_PG14, HAL_LL_CAN1_BASE_ADDRESS},
    #endif
    #ifdef CAN2_RX_RG14_RP126
    {hal_ll_can_module_num(CAN_MODULE_2), GPIO_PG14, HAL_LL_CAN2_BASE_ADDRESS},
    #endif
    #ifdef CAN1_RX_RG13_RP125
    {hal_ll_can_module_num(CAN_MODULE_1), GPIO_PG13, HAL_LL_CAN1_BASE_ADDRESS},
    #endif
    #ifdef CAN2_RX_RG13_RP125
    {hal_ll_can_module_num(CAN_MODULE_2), GPIO_PG13, HAL_LL_CAN2_BASE_ADDRESS},
    #endif
    #ifdef CAN1_RX_RE0_RPI80
    {hal_ll_can_module_num(CAN_MODULE_1), GPIO_PE0, HAL_LL_CAN1_BASE_ADDRESS},
    #endif
    #ifdef CAN2_RX_RE0_RPI80
    {hal_ll_can_module_num(CAN_MODULE_2), GPIO_PE0, HAL_LL_CAN2_BASE_ADDRESS},
    #endif
    #ifdef CAN1_RX_RD12_RPI76
    {hal_ll_can_module_num(CAN_MODULE_1), GPIO_PD12, HAL_LL_CAN1_BASE_ADDRESS},
    #endif
    #ifdef CAN2_RX_RD12_RPI76
    {hal_ll_can_module_num(CAN_MODULE_2), GPIO_PD12, HAL_LL_CAN2_BASE_ADDRESS},
    #endif
    #ifdef CAN1_RX_RD13_RPI77
    {hal_ll_can_module_num(CAN_MODULE_1), GPIO_PD13, HAL_LL_CAN1_BASE_ADDRESS},
    #endif
    #ifdef CAN2_RX_RD13_RPI77
    {hal_ll_can_module_num(CAN_MODULE_2), GPIO_PD13, HAL_LL_CAN2_BASE_ADDRESS},
    #endif
    #ifdef CAN1_RX_RG0_RPI112
    {hal_ll_can_module_num(CAN_MODULE_1), GPIO_PG0, HAL_LL_CAN1_BASE_ADDRESS},
    #endif
    #ifdef CAN2_RX_RG0_RPI112
    {hal_ll_can_module_num(CAN_MODULE_2), GPIO_PG0, HAL_LL_CAN2_BASE_ADDRESS},
    #endif
    #ifdef CAN1_RX_RG12_RPI124
    {hal_ll_can_module_num(CAN_MODULE_1), GPIO_PG12, HAL_LL_CAN1_BASE_ADDRESS},
    #endif
    #ifdef CAN2_RX_RG12_RPI124
    {hal_ll_can_module_num(CAN_MODULE_2), GPIO_PG12, HAL_LL_CAN2_BASE_ADDRESS},
    #endif
    #ifdef CAN1_RX_RE5_RP85
    {hal_ll_can_module_num(CAN_MODULE_1), GPIO_PE5, HAL_LL_CAN1_BASE_ADDRESS},
    #endif
    #ifdef CAN2_RX_RE5_RP85
    {hal_ll_can_module_num(CAN_MODULE_2), GPIO_PE5, HAL_LL_CAN2_BASE_ADDRESS},
    #endif
    #ifdef CAN1_RX_RE7_RP87
    {hal_ll_can_module_num(CAN_MODULE_1), GPIO_PE7, HAL_LL_CAN1_BASE_ADDRESS},
    #endif
    #ifdef CAN2_RX_RE7_RP87
    {hal_ll_can_module_num(CAN_MODULE_2), GPIO_PE7, HAL_LL_CAN2_BASE_ADDRESS},
    #endif
    #ifdef CAN1_RX_RF4_RP100
    {hal_ll_can_module_num(CAN_MODULE_1), GPIO_PF4, HAL_LL_CAN1_BASE_ADDRESS},
    #endif
    #ifdef CAN2_RX_RF4_RP100
    {hal_ll_can_module_num(CAN_MODULE_2), GPIO_PF4, HAL_LL_CAN2_BASE_ADDRESS},
    #endif
    #ifdef CAN1_RX_RF5_RP101
    {hal_ll_can_module_num(CAN_MODULE_1), GPIO_PF5, HAL_LL_CAN1_BASE_ADDRESS},
    #endif
    #ifdef CAN2_RX_RF5_RP101
    {hal_ll_can_module_num(CAN_MODULE_2), GPIO_PF5, HAL_LL_CAN2_BASE_ADDRESS},
    #endif
    #ifdef CAN1_RX_RF3_RP99
    {hal_ll_can_module_num(CAN_MODULE_1), GPIO_PF3, HAL_LL_CAN1_BASE_ADDRESS},
    #endif
    #ifdef CAN2_RX_RF3_RP99
    {hal_ll_can_module_num(CAN_MODULE_2), GPIO_PF3, HAL_LL_CAN2_BASE_ADDRESS},
    #endif
    #ifdef CAN1_RX_RD0_RP64
    {hal_ll_can_module_num(CAN_MODULE_1), GPIO_PD0, HAL_LL_CAN1_BASE_ADDRESS},
    #endif
    #ifdef CAN2_RX_RD0_RP64
    {hal_ll_can_module_num(CAN_MODULE_2), GPIO_PD0, HAL_LL_CAN2_BASE_ADDRESS},
    #endif
    #ifdef CAN1_RX_RD1_RP65
    {hal_ll_can_module_num(CAN_MODULE_1), GPIO_PD1, HAL_LL_CAN1_BASE_ADDRESS},
    #endif
    #ifdef CAN2_RX_RD1_RP65
    {hal_ll_can_module_num(CAN_MODULE_2), GPIO_PD1, HAL_LL_CAN2_BASE_ADDRESS},
    #endif
    #ifdef CAN1_RX_RD2_RP66
    {hal_ll_can_module_num(CAN_MODULE_1), GPIO_PD2, HAL_LL_CAN1_BASE_ADDRESS},
    #endif
    #ifdef CAN2_RX_RD2_RP66
    {hal_ll_can_module_num(CAN_MODULE_2), GPIO_PD2, HAL_LL_CAN2_BASE_ADDRESS},
    #endif
    #ifdef CAN1_RX_RD3_RP67
    {hal_ll_can_module_num(CAN_MODULE_1), GPIO_PD3, HAL_LL_CAN1_BASE_ADDRESS},
    #endif
    #ifdef CAN2_RX_RD3_RP67
    {hal_ll_can_module_num(CAN_MODULE_2), GPIO_PD3, HAL_LL_CAN2_BASE_ADDRESS},
    #endif
    #ifdef CAN1_RX_RD4_RP68
    {hal_ll_can_module_num(CAN_MODULE_1), GPIO_PD4, HAL_LL_CAN1_BASE_ADDRESS},
    #endif
    #ifdef CAN2_RX_RD4_RP68
    {hal_ll_can_module_num(CAN_MODULE_2), GPIO_PD4, HAL_LL_CAN2_BASE_ADDRESS},
    #endif
    #ifdef CAN1_RX_RD7_RP71
    {hal_ll_can_module_num(CAN_MODULE_1), GPIO_PD7, HAL_LL_CAN1_BASE_ADDRESS},
    #endif
    #ifdef CAN2_RX_RD7_RP71
    {hal_ll_can_module_num(CAN_MODULE_2), GPIO_PD7, HAL_LL_CAN2_BASE_ADDRESS},
    #endif
    #ifdef CAN1_RX_RF0_RP96
    {hal_ll_can_module_num(CAN_MODULE_1), GPIO_PF0, HAL_LL_CAN1_BASE_ADDRESS},
    #endif
    #ifdef CAN2_RX_RF0_RP96
    {hal_ll_can_module_num(CAN_MODULE_2), GPIO_PF0, HAL_LL_CAN2_BASE_ADDRESS},
    #endif
    #ifdef CAN1_RX_RE0_RP80
    {hal_ll_can_module_num(CAN_MODULE_1), GPIO_PE0, HAL_LL_CAN1_BASE_ADDRESS},
    #endif
    #ifdef CAN2_RX_RE0_RP80
    {hal_ll_can_module_num(CAN_MODULE_2), GPIO_PE0, HAL_LL_CAN2_BASE_ADDRESS},
    #endif
    #ifdef CAN1_RX_RE2_RP82
    {hal_ll_can_module_num(CAN_MODULE_1), GPIO_PE2, HAL_LL_CAN1_BASE_ADDRESS},
    #endif
    #ifdef CAN2_RX_RE2_RP82
    {hal_ll_can_module_num(CAN_MODULE_2), GPIO_PE2, HAL_LL_CAN2_BASE_ADDRESS},
    #endif
    #ifdef CAN1_RX_RE4_RP84
    {hal_ll_can_module_num(CAN_MODULE_1), GPIO_PE4, HAL_LL_CAN1_BASE_ADDRESS},
    #endif
    #ifdef CAN2_RX_RE4_RP84
    {hal_ll_can_module_num(CAN_MODULE_2), GPIO_PE4, HAL_LL_CAN2_BASE_ADDRESS},
    #endif
    #ifdef CAN1_RX_RE6_RPI86
    {hal_ll_can_module_num(CAN_MODULE_1), GPIO_PE6, HAL_LL_CAN1_BASE_ADDRESS},
    #endif
    #ifdef CAN2_RX_RE6_RPI86
    {hal_ll_can_module_num(CAN_MODULE_2), GPIO_PE6, HAL_LL_CAN2_BASE_ADDRESS},
    #endif
    #ifdef CAN1_RX_RB5_RPI37
    {hal_ll_can_module_num(CAN_MODULE_1), GPIO_PB5, HAL_LL_CAN1_BASE_ADDRESS},
    #endif
    #ifdef CAN2_RX_RB5_RPI37
    {hal_ll_can_module_num(CAN_MODULE_2), GPIO_PB5, HAL_LL_CAN2_BASE_ADDRESS},
    #endif
    #ifdef CAN1_RX_RB4_RPI36
    {hal_ll_can_module_num(CAN_MODULE_1), GPIO_PB4, HAL_LL_CAN1_BASE_ADDRESS},
    #endif
    #ifdef CAN2_RX_RB4_RPI36
    {hal_ll_can_module_num(CAN_MODULE_2), GPIO_PB4, HAL_LL_CAN2_BASE_ADDRESS},
    #endif
    #ifdef CAN1_RX_RB3_RPI35
    {hal_ll_can_module_num(CAN_MODULE_1), GPIO_PB3, HAL_LL_CAN1_BASE_ADDRESS},
    #endif
    #ifdef CAN2_RX_RB3_RPI35
    {hal_ll_can_module_num(CAN_MODULE_2), GPIO_PB3, HAL_LL_CAN2_BASE_ADDRESS},
    #endif
    #ifdef CAN1_RX_RB6_RPI38
    {hal_ll_can_module_num(CAN_MODULE_1), GPIO_PB6, HAL_LL_CAN1_BASE_ADDRESS},
    #endif
    #ifdef CAN2_RX_RB6_RPI38
    {hal_ll_can_module_num(CAN_MODULE_2), GPIO_PB6, HAL_LL_CAN2_BASE_ADDRESS},
    #endif
    #ifdef CAN1_RX_RB7_RPI39
    {hal_ll_can_module_num(CAN_MODULE_1), GPIO_PB7, HAL_LL_CAN1_BASE_ADDRESS},
    #endif
    #ifdef CAN2_RX_RB7_RPI39
    {hal_ll_can_module_num(CAN_MODULE_2), GPIO_PB7, HAL_LL_CAN2_BASE_ADDRESS},
    #endif
    #ifdef CAN1_RX_RB8_RPI40
    {hal_ll_can_module_num(CAN_MODULE_1), GPIO_PB8, HAL_LL_CAN1_BASE_ADDRESS},
    #endif
    #ifdef CAN2_RX_RB8_RPI40
    {hal_ll_can_module_num(CAN_MODULE_2), GPIO_PB8, HAL_LL_CAN2_BASE_ADDRESS},
    #endif
    #ifdef CAN1_RX_RB9_RPI41
    {hal_ll_can_module_num(CAN_MODULE_1), GPIO_PB9, HAL_LL_CAN1_BASE_ADDRESS},
    #endif
    #ifdef CAN2_RX_RB9_RPI41
    {hal_ll_can_module_num(CAN_MODULE_2), GPIO_PB9, HAL_LL_CAN2_BASE_ADDRESS},
    #endif
    #ifdef CAN1_RX_RB10_RPI42
    {hal_ll_can_module_num(CAN_MODULE_1), GPIO_PB10, HAL_LL_CAN1_BASE_ADDRESS},
    #endif
    #ifdef CAN2_RX_RB10_RPI42
    {hal_ll_can_module_num(CAN_MODULE_2), GPIO_PB10, HAL_LL_CAN2_BASE_ADDRESS},
    #endif
    #ifdef CAN1_RX_RB11_RPI43
    {hal_ll_can_module_num(CAN_MODULE_1), GPIO_PB11, HAL_LL_CAN1_BASE_ADDRESS},
    #endif
    #ifdef CAN2_RX_RB11_RPI43
    {hal_ll_can_module_num(CAN_MODULE_2), GPIO_PB11, HAL_LL_CAN2_BASE_ADDRESS},
    #endif
    #ifdef CAN1_RX_RD9_RPI73
    {hal_ll_can_module_num(CAN_MODULE_1), GPIO_PD9, HAL_LL_CAN1_BASE_ADDRESS},
    #endif
    #ifdef CAN2_RX_RD9_RPI73
    {hal_ll_can_module_num(CAN_MODULE_2), GPIO_PD9, HAL_LL_CAN2_BASE_ADDRESS},
    #endif
    #ifdef CAN1_RX_RD10_RPI74
    {hal_ll_can_module_num(CAN_MODULE_1), GPIO_PD10, HAL_LL_CAN1_BASE_ADDRESS},
    #endif
    #ifdef CAN2_RX_RD10_RPI74
    {hal_ll_can_module_num(CAN_MODULE_2), GPIO_PD10, HAL_LL_CAN2_BASE_ADDRESS},
    #endif
    #ifdef CAN1_RX_RD11_RPI75
    {hal_ll_can_module_num(CAN_MODULE_1), GPIO_PD11, HAL_LL_CAN1_BASE_ADDRESS},
    #endif
    #ifdef CAN2_RX_RD11_RPI75
    {hal_ll_can_module_num(CAN_MODULE_2), GPIO_PD11, HAL_LL_CAN2_BASE_ADDRESS},
    #endif
    #ifdef CAN1_RX_RC14_RPI62
    {hal_ll_can_module_num(CAN_MODULE_1), GPIO_PC14, HAL_LL_CAN1_BASE_ADDRESS},
    #endif
    #ifdef CAN2_RX_RC14_RPI62
    {hal_ll_can_module_num(CAN_MODULE_2), GPIO_PC14, HAL_LL_CAN2_BASE_ADDRESS},
    #endif
    #ifdef CAN1_RX_RE1_RPI81
    {hal_ll_can_module_num(CAN_MODULE_1), GPIO_PE1, HAL_LL_CAN1_BASE_ADDRESS},
    #endif
    #ifdef CAN2_RX_RE1_RPI81
    {hal_ll_can_module_num(CAN_MODULE_2), GPIO_PE1, HAL_LL_CAN2_BASE_ADDRESS},
    #endif
    #ifdef CAN1_RX_RE3_RPI83
    {hal_ll_can_module_num(CAN_MODULE_1), GPIO_PE3, HAL_LL_CAN1_BASE_ADDRESS},
    #endif
    #ifdef CAN2_RX_RE3_RPI83
    {hal_ll_can_module_num(CAN_MODULE_2), GPIO_PE3, HAL_LL_CAN2_BASE_ADDRESS},
    #endif
    #ifdef CAN1_RX_RF13_RP109
    {hal_ll_can_module_num(CAN_MODULE_1), GPIO_PF13, HAL_LL_CAN1_BASE_ADDRESS},
    #endif
    #ifdef CAN2_RX_RF13_RP109
    {hal_ll_can_module_num(CAN_MODULE_2), GPIO_PF13, HAL_LL_CAN2_BASE_ADDRESS},
    #endif
    #ifdef CAN1_RX_RF12_RP108
    {hal_ll_can_module_num(CAN_MODULE_1), GPIO_PF12, HAL_LL_CAN1_BASE_ADDRESS},
    #endif
    #ifdef CAN2_RX_RF12_RP108
    {hal_ll_can_module_num(CAN_MODULE_2), GPIO_PF12, HAL_LL_CAN2_BASE_ADDRESS},
    #endif
    #ifdef CAN1_RX_RD15_RP79
    {hal_ll_can_module_num(CAN_MODULE_1), GPIO_PD15, HAL_LL_CAN1_BASE_ADDRESS},
    #endif
    #ifdef CAN2_RX_RD15_RP79
    {hal_ll_can_module_num(CAN_MODULE_2), GPIO_PD15, HAL_LL_CAN2_BASE_ADDRESS},
    #endif
    #ifdef CAN1_RX_RF2_RP98
    {hal_ll_can_module_num(CAN_MODULE_1), GPIO_PF2, HAL_LL_CAN1_BASE_ADDRESS},
    #endif
    #ifdef CAN2_RX_RF2_RP98
    {hal_ll_can_module_num(CAN_MODULE_2), GPIO_PF2, HAL_LL_CAN2_BASE_ADDRESS},
    #endif
    #ifdef CAN1_RX_RF8_RP104
    {hal_ll_can_module_num(CAN_MODULE_1), GPIO_PF8, HAL_LL_CAN1_BASE_ADDRESS},
    #endif
    #ifdef CAN2_RX_RF8_RP104
    {hal_ll_can_module_num(CAN_MODULE_2), GPIO_PF8, HAL_LL_CAN2_BASE_ADDRESS},
    #endif
    #ifdef CAN1_RX_RG0_RP112
    {hal_ll_can_module_num(CAN_MODULE_1), GPIO_PG0, HAL_LL_CAN1_BASE_ADDRESS},
    #endif
    #ifdef CAN2_RX_RG0_RP112
    {hal_ll_can_module_num(CAN_MODULE_2), GPIO_PG0, HAL_LL_CAN2_BASE_ADDRESS},
    #endif
    #ifdef CAN1_RX_RC1_RPI49
    {hal_ll_can_module_num(CAN_MODULE_1), GPIO_PC1, HAL_LL_CAN1_BASE_ADDRESS},
    #endif
    #ifdef CAN2_RX_RC1_RPI49
    {hal_ll_can_module_num(CAN_MODULE_2), GPIO_PC1, HAL_LL_CAN2_BASE_ADDRESS},
    #endif
    #ifdef CAN1_RX_RE8_RPI88
    {hal_ll_can_module_num(CAN_MODULE_1), GPIO_PE8, HAL_LL_CAN1_BASE_ADDRESS},
    #endif
    #ifdef CAN2_RX_RE8_RPI88
    {hal_ll_can_module_num(CAN_MODULE_2), GPIO_PE8, HAL_LL_CAN2_BASE_ADDRESS},
    #endif
    #ifdef CAN1_RX_RE9_RPI89
    {hal_ll_can_module_num(CAN_MODULE_1), GPIO_PE9, HAL_LL_CAN1_BASE_ADDRESS},
    #endif
    #ifdef CAN2_RX_RE9_RPI89
    {hal_ll_can_module_num(CAN_MODULE_2), GPIO_PE9, HAL_LL_CAN2_BASE_ADDRESS},
    #endif
    #ifdef CAN1_RX_RD14_RPI78
    {hal_ll_can_module_num(CAN_MODULE_1), GPIO_PD14, HAL_LL_CAN1_BASE_ADDRESS},
    #endif
    #ifdef CAN2_RX_RD14_RPI78
    {hal_ll_can_module_num(CAN_MODULE_2), GPIO_PD14, HAL_LL_CAN2_BASE_ADDRESS},
    #endif
    #ifdef CAN1_RX_RA4_RPI20
    {hal_ll_can_module_num(CAN_MODULE_1), GPIO_PA4, HAL_LL_CAN1_BASE_ADDRESS},
    #endif
    #ifdef CAN2_RX_RA4_RPI20
    {hal_ll_can_module_num(CAN_MODULE_2), GPIO_PA4, HAL_LL_CAN2_BASE_ADDRESS},
    #endif
    #ifdef CAN1_RX_RA5_RPI21
    {hal_ll_can_module_num(CAN_MODULE_1), GPIO_PA5, HAL_LL_CAN1_BASE_ADDRESS},
    #endif
    #ifdef CAN2_RX_RA5_RPI21
    {hal_ll_can_module_num(CAN_MODULE_2), GPIO_PA5, HAL_LL_CAN2_BASE_ADDRESS},
    #endif
    #ifdef CAN1_RX_RA14_RPI30
    {hal_ll_can_module_num(CAN_MODULE_1), GPIO_PA14, HAL_LL_CAN1_BASE_ADDRESS},
    #endif
    #ifdef CAN2_RX_RA14_RPI30
    {hal_ll_can_module_num(CAN_MODULE_2), GPIO_PA14, HAL_LL_CAN2_BASE_ADDRESS},
    #endif
    #ifdef CAN1_RX_RA15_RPI31
    {hal_ll_can_module_num(CAN_MODULE_1), GPIO_PA15, HAL_LL_CAN1_BASE_ADDRESS},
    #endif
    #ifdef CAN2_RX_RA15_RPI31
    {hal_ll_can_module_num(CAN_MODULE_2), GPIO_PA15, HAL_LL_CAN2_BASE_ADDRESS},
    #endif
    #ifdef CAN1_RX_RA6_RPI22
    {hal_ll_can_module_num(CAN_MODULE_1), GPIO_PA6, HAL_LL_CAN1_BASE_ADDRESS},
    #endif
    #ifdef CAN2_RX_RA6_RPI22
    {hal_ll_can_module_num(CAN_MODULE_2), GPIO_PA6, HAL_LL_CAN2_BASE_ADDRESS},
    #endif
    #ifdef CAN1_RX_RA7_RPI23
    {hal_ll_can_module_num(CAN_MODULE_1), GPIO_PA7, HAL_LL_CAN1_BASE_ADDRESS},
    #endif
    #ifdef CAN2_RX_RA7_RPI23
    {hal_ll_can_module_num(CAN_MODULE_2), GPIO_PA7, HAL_LL_CAN2_BASE_ADDRESS},
    #endif
    #ifdef CAN1_RX_RF6_RP102
    {hal_ll_can_module_num(CAN_MODULE_1), GPIO_PF6, HAL_LL_CAN1_BASE_ADDRESS},
    #endif
    #ifdef CAN2_RX_RF6_RP102
    {hal_ll_can_module_num(CAN_MODULE_2), GPIO_PF6, HAL_LL_CAN2_BASE_ADDRESS},
    #endif
    #ifdef CAN1_RX_RG7_RP119
    {hal_ll_can_module_num(CAN_MODULE_1), GPIO_PG7, HAL_LL_CAN1_BASE_ADDRESS},
    #endif
    #ifdef CAN2_RX_RG7_RP119
    {hal_ll_can_module_num(CAN_MODULE_2), GPIO_PG7, HAL_LL_CAN2_BASE_ADDRESS},
    #endif
    #ifdef CAN1_RX_RB0_RP0
    {hal_ll_can_module_num(CAN_MODULE_1), GPIO_PB0, HAL_LL_CAN1_BASE_ADDRESS},
    #endif
    #ifdef CAN1_RX_RB1_RP1
    {hal_ll_can_module_num(CAN_MODULE_1), GPIO_PB1, HAL_LL_CAN1_BASE_ADDRESS},
    #endif
    #ifdef CAN1_RX_RB2_RP2
    {hal_ll_can_module_num(CAN_MODULE_1), GPIO_PB2, HAL_LL_CAN1_BASE_ADDRESS},
    #endif
    #ifdef CAN1_RX_RB3_RP3
    {hal_ll_can_module_num(CAN_MODULE_1), GPIO_PB3, HAL_LL_CAN1_BASE_ADDRESS},
    #endif
    #ifdef CAN1_RX_RB4_RP4
    {hal_ll_can_module_num(CAN_MODULE_1), GPIO_PB4, HAL_LL_CAN1_BASE_ADDRESS},
    #endif
    #ifdef CAN1_RX_RB5_RP5
    {hal_ll_can_module_num(CAN_MODULE_1), GPIO_PB5, HAL_LL_CAN1_BASE_ADDRESS},
    #endif
    #ifdef CAN1_RX_RB6_RP6
    {hal_ll_can_module_num(CAN_MODULE_1), GPIO_PB6, HAL_LL_CAN1_BASE_ADDRESS},
    #endif
    #ifdef CAN1_RX_RB7_RP7
    {hal_ll_can_module_num(CAN_MODULE_1), GPIO_PB7, HAL_LL_CAN1_BASE_ADDRESS},
    #endif
    #ifdef CAN1_RX_RB8_RP8
    {hal_ll_can_module_num(CAN_MODULE_1), GPIO_PB8, HAL_LL_CAN1_BASE_ADDRESS},
    #endif
    #ifdef CAN1_RX_RB9_RP9
    {hal_ll_can_module_num(CAN_MODULE_1), GPIO_PB9, HAL_LL_CAN1_BASE_ADDRESS},
    #endif
    #ifdef CAN1_RX_RB10_RP10
    {hal_ll_can_module_num(CAN_MODULE_1), GPIO_PB10, HAL_LL_CAN1_BASE_ADDRESS},
    #endif
    #ifdef CAN1_RX_RB11_RP11
    {hal_ll_can_module_num(CAN_MODULE_1), GPIO_PB11, HAL_LL_CAN1_BASE_ADDRESS},
    #endif
    #ifdef CAN1_RX_RB12_RP12
    {hal_ll_can_module_num(CAN_MODULE_1), GPIO_PB12, HAL_LL_CAN1_BASE_ADDRESS},
    #endif
    #ifdef CAN1_RX_RB13_RP13
    {hal_ll_can_module_num(CAN_MODULE_1), GPIO_PB13, HAL_LL_CAN1_BASE_ADDRESS},
    #endif
    #ifdef CAN1_RX_RB14_RP14
    {hal_ll_can_module_num(CAN_MODULE_1), GPIO_PB14, HAL_LL_CAN1_BASE_ADDRESS},
    #endif
    #ifdef CAN1_RX_RB15_RP15
    {hal_ll_can_module_num(CAN_MODULE_1), GPIO_PB15, HAL_LL_CAN1_BASE_ADDRESS},
    #endif
    #ifdef CAN1_RX_RC6_RP22
    {hal_ll_can_module_num(CAN_MODULE_1), GPIO_PC6, HAL_LL_CAN1_BASE_ADDRESS},
    #endif
    #ifdef CAN1_RX_RC7_RP23
    {hal_ll_can_module_num(CAN_MODULE_1), GPIO_PC7, HAL_LL_CAN1_BASE_ADDRESS},
    #endif
    #ifdef CAN1_RX_RC8_RP24
    {hal_ll_can_module_num(CAN_MODULE_1), GPIO_PC8, HAL_LL_CAN1_BASE_ADDRESS},
    #endif
    #ifdef CAN1_RX_RC9_RP25
    {hal_ll_can_module_num(CAN_MODULE_1), GPIO_PC9, HAL_LL_CAN1_BASE_ADDRESS},
    #endif
    #ifdef CAN1_RX_RC0_RP16
    {hal_ll_can_module_num(CAN_MODULE_1), GPIO_PC0, HAL_LL_CAN1_BASE_ADDRESS},
    #endif
    #ifdef CAN1_RX_RC1_RP17
    {hal_ll_can_module_num(CAN_MODULE_1), GPIO_PC1, HAL_LL_CAN1_BASE_ADDRESS},
    #endif
    #ifdef CAN1_RX_RC2_RP18
    {hal_ll_can_module_num(CAN_MODULE_1), GPIO_PC2, HAL_LL_CAN1_BASE_ADDRESS},
    #endif
    #ifdef CAN1_RX_RC3_RP19
    {hal_ll_can_module_num(CAN_MODULE_1), GPIO_PC3, HAL_LL_CAN1_BASE_ADDRESS},
    #endif
    #ifdef CAN1_RX_RC4_RP20
    {hal_ll_can_module_num(CAN_MODULE_1), GPIO_PC4, HAL_LL_CAN1_BASE_ADDRESS},
    #endif
    #ifdef CAN1_RX_RC5_RP21
    {hal_ll_can_module_num(CAN_MODULE_1), GPIO_PC5, HAL_LL_CAN1_BASE_ADDRESS},
    #endif

    {HAL_LL_MODULE_ERROR, HAL_LL_PIN_NC, HAL_LL_MODULE_ERROR}
    //------------ END RX
};

/*!< @brief CAN TX pins */
static const hal_ll_can_pin_map_t hal_ll_can_tx_map[] =
{
    //------------ BEGIN TX
    #ifdef CAN1_TX_RF1
    {hal_ll_can_module_num(CAN_MODULE_1), GPIO_PF1, HAL_LL_CAN1_BASE_ADDRESS},
    #endif
    #ifdef CAN2_TX_RG1
    {hal_ll_can_module_num(CAN_MODULE_2), GPIO_PG1, HAL_LL_CAN2_BASE_ADDRESS},
    #endif
    #ifdef CAN1_TX_RB9_RP41
    {hal_ll_can_module_num(CAN_MODULE_1), GPIO_PB9, HAL_LL_CAN1_BASE_ADDRESS},
    #endif
    #ifdef CAN2_TX_RB9_RP41
    {hal_ll_can_module_num(CAN_MODULE_2), GPIO_PB9, HAL_LL_CAN2_BASE_ADDRESS},
    #endif
    #ifdef CAN1_TX_RC6_RP54
    {hal_ll_can_module_num(CAN_MODULE_1), GPIO_PC6, HAL_LL_CAN1_BASE_ADDRESS},
    #endif
    #ifdef CAN2_TX_RC6_RP54
    {hal_ll_can_module_num(CAN_MODULE_2), GPIO_PC6, HAL_LL_CAN2_BASE_ADDRESS},
    #endif
    #ifdef CAN1_TX_RC7_RP55
    {hal_ll_can_module_num(CAN_MODULE_1), GPIO_PC7, HAL_LL_CAN1_BASE_ADDRESS},
    #endif
    #ifdef CAN2_TX_RC7_RP55
    {hal_ll_can_module_num(CAN_MODULE_2), GPIO_PC7, HAL_LL_CAN2_BASE_ADDRESS},
    #endif
    #ifdef CAN1_TX_RC8_RP56
    {hal_ll_can_module_num(CAN_MODULE_1), GPIO_PC8, HAL_LL_CAN1_BASE_ADDRESS},
    #endif
    #ifdef CAN2_TX_RC8_RP56
    {hal_ll_can_module_num(CAN_MODULE_2), GPIO_PC8, HAL_LL_CAN2_BASE_ADDRESS},
    #endif
    #ifdef CAN1_TX_RC9_RP57
    {hal_ll_can_module_num(CAN_MODULE_1), GPIO_PC9, HAL_LL_CAN1_BASE_ADDRESS},
    #endif
    #ifdef CAN2_TX_RC9_RP57
    {hal_ll_can_module_num(CAN_MODULE_2), GPIO_PC9, HAL_LL_CAN2_BASE_ADDRESS},
    #endif
    #ifdef CAN1_TX_RB10_RP42
    {hal_ll_can_module_num(CAN_MODULE_1), GPIO_PB10, HAL_LL_CAN1_BASE_ADDRESS},
    #endif
    #ifdef CAN2_TX_RB10_RP42
    {hal_ll_can_module_num(CAN_MODULE_2), GPIO_PB10, HAL_LL_CAN2_BASE_ADDRESS},
    #endif
    #ifdef CAN1_TX_RB11_RP43
    {hal_ll_can_module_num(CAN_MODULE_1), GPIO_PB11, HAL_LL_CAN1_BASE_ADDRESS},
    #endif
    #ifdef CAN2_TX_RB11_RP43
    {hal_ll_can_module_num(CAN_MODULE_2), GPIO_PB11, HAL_LL_CAN2_BASE_ADDRESS},
    #endif
    #ifdef CAN1_TX_RB3_RP35
    {hal_ll_can_module_num(CAN_MODULE_1), GPIO_PB3, HAL_LL_CAN1_BASE_ADDRESS},
    #endif
    #ifdef CAN2_TX_RB3_RP35
    {hal_ll_can_module_num(CAN_MODULE_2), GPIO_PB3, HAL_LL_CAN2_BASE_ADDRESS},
    #endif
    #ifdef CAN1_TX_RC0_RP48
    {hal_ll_can_module_num(CAN_MODULE_1), GPIO_PC0, HAL_LL_CAN1_BASE_ADDRESS},
    #endif
    #ifdef CAN2_TX_RC0_RP48
    {hal_ll_can_module_num(CAN_MODULE_2), GPIO_PC0, HAL_LL_CAN2_BASE_ADDRESS},
    #endif
    #ifdef CAN1_TX_RC1_RP49
    {hal_ll_can_module_num(CAN_MODULE_1), GPIO_PC1, HAL_LL_CAN1_BASE_ADDRESS},
    #endif
    #ifdef CAN2_TX_RC1_RP49
    {hal_ll_can_module_num(CAN_MODULE_2), GPIO_PC1, HAL_LL_CAN2_BASE_ADDRESS},
    #endif
    #ifdef CAN1_TX_RB4_RP36
    {hal_ll_can_module_num(CAN_MODULE_1), GPIO_PB4, HAL_LL_CAN1_BASE_ADDRESS},
    #endif
    #ifdef CAN2_TX_RB4_RP36
    {hal_ll_can_module_num(CAN_MODULE_2), GPIO_PB4, HAL_LL_CAN2_BASE_ADDRESS},
    #endif
    #ifdef CAN1_TX_RA4_RP20
    {hal_ll_can_module_num(CAN_MODULE_1), GPIO_PA4, HAL_LL_CAN1_BASE_ADDRESS},
    #endif
    #ifdef CAN2_TX_RA4_RP20
    {hal_ll_can_module_num(CAN_MODULE_2), GPIO_PA4, HAL_LL_CAN2_BASE_ADDRESS},
    #endif
    #ifdef CAN1_TX_RB5_RP37
    {hal_ll_can_module_num(CAN_MODULE_1), GPIO_PB5, HAL_LL_CAN1_BASE_ADDRESS},
    #endif
    #ifdef CAN2_TX_RB5_RP37
    {hal_ll_can_module_num(CAN_MODULE_2), GPIO_PB5, HAL_LL_CAN2_BASE_ADDRESS},
    #endif
    #ifdef CAN1_TX_RB6_RP38
    {hal_ll_can_module_num(CAN_MODULE_1), GPIO_PB6, HAL_LL_CAN1_BASE_ADDRESS},
    #endif
    #ifdef CAN2_TX_RB6_RP38
    {hal_ll_can_module_num(CAN_MODULE_2), GPIO_PB6, HAL_LL_CAN2_BASE_ADDRESS},
    #endif
    #ifdef CAN1_TX_RB7_RP39
    {hal_ll_can_module_num(CAN_MODULE_1), GPIO_PB7, HAL_LL_CAN1_BASE_ADDRESS},
    #endif
    #ifdef CAN2_TX_RB7_RP39
    {hal_ll_can_module_num(CAN_MODULE_2), GPIO_PB7, HAL_LL_CAN2_BASE_ADDRESS},
    #endif
    #ifdef CAN1_TX_RB8_RP40
    {hal_ll_can_module_num(CAN_MODULE_1), GPIO_PB8, HAL_LL_CAN1_BASE_ADDRESS},
    #endif
    #ifdef CAN2_TX_RB8_RP40
    {hal_ll_can_module_num(CAN_MODULE_2), GPIO_PB8, HAL_LL_CAN2_BASE_ADDRESS},
    #endif
    #ifdef CAN1_TX_RG8_RP120
    {hal_ll_can_module_num(CAN_MODULE_1), GPIO_PG8, HAL_LL_CAN1_BASE_ADDRESS},
    #endif
    #ifdef CAN2_TX_RG8_RP120
    {hal_ll_can_module_num(CAN_MODULE_2), GPIO_PG8, HAL_LL_CAN2_BASE_ADDRESS},
    #endif
    #ifdef CAN1_TX_RD5_RP69
    {hal_ll_can_module_num(CAN_MODULE_1), GPIO_PD5, HAL_LL_CAN1_BASE_ADDRESS},
    #endif
    #ifdef CAN2_TX_RD5_RP69
    {hal_ll_can_module_num(CAN_MODULE_2), GPIO_PD5, HAL_LL_CAN2_BASE_ADDRESS},
    #endif
    #ifdef CAN1_TX_RD6_RP70
    {hal_ll_can_module_num(CAN_MODULE_1), GPIO_PD6, HAL_LL_CAN1_BASE_ADDRESS},
    #endif
    #ifdef CAN2_TX_RD6_RP70
    {hal_ll_can_module_num(CAN_MODULE_2), GPIO_PD6, HAL_LL_CAN2_BASE_ADDRESS},
    #endif
    #ifdef CAN1_TX_RF1_RP97
    {hal_ll_can_module_num(CAN_MODULE_1), GPIO_PF1, HAL_LL_CAN1_BASE_ADDRESS},
    #endif
    #ifdef CAN2_TX_RF1_RP97
    {hal_ll_can_module_num(CAN_MODULE_2), GPIO_PF1, HAL_LL_CAN2_BASE_ADDRESS},
    #endif
    #ifdef CAN1_TX_RG15_RP127
    {hal_ll_can_module_num(CAN_MODULE_1), GPIO_PG15, HAL_LL_CAN1_BASE_ADDRESS},
    #endif
    #ifdef CAN2_TX_RG15_RP127
    {hal_ll_can_module_num(CAN_MODULE_2), GPIO_PG15, HAL_LL_CAN2_BASE_ADDRESS},
    #endif
    #ifdef CAN1_TX_RG6_RP118
    {hal_ll_can_module_num(CAN_MODULE_1), GPIO_PG6, HAL_LL_CAN1_BASE_ADDRESS},
    #endif
    #ifdef CAN2_TX_RG6_RP118
    {hal_ll_can_module_num(CAN_MODULE_2), GPIO_PG6, HAL_LL_CAN2_BASE_ADDRESS},
    #endif
    #ifdef CAN1_TX_RE1_RP81
    {hal_ll_can_module_num(CAN_MODULE_1), GPIO_PE1, HAL_LL_CAN1_BASE_ADDRESS},
    #endif
    #ifdef CAN2_TX_RE1_RP81
    {hal_ll_can_module_num(CAN_MODULE_2), GPIO_PE1, HAL_LL_CAN2_BASE_ADDRESS},
    #endif
    #ifdef CAN1_TX_RG1_RP113
    {hal_ll_can_module_num(CAN_MODULE_1), GPIO_PG1, HAL_LL_CAN1_BASE_ADDRESS},
    #endif
    #ifdef CAN2_TX_RG1_RP113
    {hal_ll_can_module_num(CAN_MODULE_2), GPIO_PG1, HAL_LL_CAN2_BASE_ADDRESS},
    #endif
    #ifdef CAN1_TX_RG14_RP126
    {hal_ll_can_module_num(CAN_MODULE_1), GPIO_PG14, HAL_LL_CAN1_BASE_ADDRESS},
    #endif
    #ifdef CAN2_TX_RG14_RP126
    {hal_ll_can_module_num(CAN_MODULE_2), GPIO_PG14, HAL_LL_CAN2_BASE_ADDRESS},
    #endif
    #ifdef CAN1_TX_RG13_RP125
    {hal_ll_can_module_num(CAN_MODULE_1), GPIO_PG13, HAL_LL_CAN1_BASE_ADDRESS},
    #endif
    #ifdef CAN2_TX_RG13_RP125
    {hal_ll_can_module_num(CAN_MODULE_2), GPIO_PG13, HAL_LL_CAN2_BASE_ADDRESS},
    #endif
    #ifdef CAN1_TX_RE5_RP85
    {hal_ll_can_module_num(CAN_MODULE_1), GPIO_PE5, HAL_LL_CAN1_BASE_ADDRESS},
    #endif
    #ifdef CAN2_TX_RE5_RP85
    {hal_ll_can_module_num(CAN_MODULE_2), GPIO_PE5, HAL_LL_CAN2_BASE_ADDRESS},
    #endif
    #ifdef CAN1_TX_RE7_RP87
    {hal_ll_can_module_num(CAN_MODULE_1), GPIO_PE7, HAL_LL_CAN1_BASE_ADDRESS},
    #endif
    #ifdef CAN2_TX_RE7_RP87
    {hal_ll_can_module_num(CAN_MODULE_2), GPIO_PE7, HAL_LL_CAN2_BASE_ADDRESS},
    #endif
    #ifdef CAN1_TX_RF4_RP100
    {hal_ll_can_module_num(CAN_MODULE_1), GPIO_PF4, HAL_LL_CAN1_BASE_ADDRESS},
    #endif
    #ifdef CAN2_TX_RF4_RP100
    {hal_ll_can_module_num(CAN_MODULE_2), GPIO_PF4, HAL_LL_CAN2_BASE_ADDRESS},
    #endif
    #ifdef CAN1_TX_RF5_RP101
    {hal_ll_can_module_num(CAN_MODULE_1), GPIO_PF5, HAL_LL_CAN1_BASE_ADDRESS},
    #endif
    #ifdef CAN2_TX_RF5_RP101
    {hal_ll_can_module_num(CAN_MODULE_2), GPIO_PF5, HAL_LL_CAN2_BASE_ADDRESS},
    #endif
    #ifdef CAN1_TX_RF3_RP99
    {hal_ll_can_module_num(CAN_MODULE_1), GPIO_PF3, HAL_LL_CAN1_BASE_ADDRESS},
    #endif
    #ifdef CAN2_TX_RF3_RP99
    {hal_ll_can_module_num(CAN_MODULE_2), GPIO_PF3, HAL_LL_CAN2_BASE_ADDRESS},
    #endif
    #ifdef CAN1_TX_RD0_RP64
    {hal_ll_can_module_num(CAN_MODULE_1), GPIO_PD0, HAL_LL_CAN1_BASE_ADDRESS},
    #endif
    #ifdef CAN2_TX_RD0_RP64
    {hal_ll_can_module_num(CAN_MODULE_2), GPIO_PD0, HAL_LL_CAN2_BASE_ADDRESS},
    #endif
    #ifdef CAN1_TX_RD1_RP65
    {hal_ll_can_module_num(CAN_MODULE_1), GPIO_PD1, HAL_LL_CAN1_BASE_ADDRESS},
    #endif
    #ifdef CAN2_TX_RD1_RP65
    {hal_ll_can_module_num(CAN_MODULE_2), GPIO_PD1, HAL_LL_CAN2_BASE_ADDRESS},
    #endif
    #ifdef CAN1_TX_RD2_RP66
    {hal_ll_can_module_num(CAN_MODULE_1), GPIO_PD2, HAL_LL_CAN1_BASE_ADDRESS},
    #endif
    #ifdef CAN2_TX_RD2_RP66
    {hal_ll_can_module_num(CAN_MODULE_2), GPIO_PD2, HAL_LL_CAN2_BASE_ADDRESS},
    #endif
    #ifdef CAN1_TX_RD3_RP67
    {hal_ll_can_module_num(CAN_MODULE_1), GPIO_PD3, HAL_LL_CAN1_BASE_ADDRESS},
    #endif
    #ifdef CAN2_TX_RD3_RP67
    {hal_ll_can_module_num(CAN_MODULE_2), GPIO_PD3, HAL_LL_CAN2_BASE_ADDRESS},
    #endif
    #ifdef CAN1_TX_RD4_RP68
    {hal_ll_can_module_num(CAN_MODULE_1), GPIO_PD4, HAL_LL_CAN1_BASE_ADDRESS},
    #endif
    #ifdef CAN2_TX_RD4_RP68
    {hal_ll_can_module_num(CAN_MODULE_2), GPIO_PD4, HAL_LL_CAN2_BASE_ADDRESS},
    #endif
    #ifdef CAN1_TX_RD7_RP71
    {hal_ll_can_module_num(CAN_MODULE_1), GPIO_PD7, HAL_LL_CAN1_BASE_ADDRESS},
    #endif
    #ifdef CAN2_TX_RD7_RP71
    {hal_ll_can_module_num(CAN_MODULE_2), GPIO_PD7, HAL_LL_CAN2_BASE_ADDRESS},
    #endif
    #ifdef CAN1_TX_RF0_RP96
    {hal_ll_can_module_num(CAN_MODULE_1), GPIO_PF0, HAL_LL_CAN1_BASE_ADDRESS},
    #endif
    #ifdef CAN2_TX_RF0_RP96
    {hal_ll_can_module_num(CAN_MODULE_2), GPIO_PF0, HAL_LL_CAN2_BASE_ADDRESS},
    #endif
    #ifdef CAN1_TX_RE0_RP80
    {hal_ll_can_module_num(CAN_MODULE_1), GPIO_PE0, HAL_LL_CAN1_BASE_ADDRESS},
    #endif
    #ifdef CAN2_TX_RE0_RP80
    {hal_ll_can_module_num(CAN_MODULE_2), GPIO_PE0, HAL_LL_CAN2_BASE_ADDRESS},
    #endif
    #ifdef CAN1_TX_RE2_RP82
    {hal_ll_can_module_num(CAN_MODULE_1), GPIO_PE2, HAL_LL_CAN1_BASE_ADDRESS},
    #endif
    #ifdef CAN2_TX_RE2_RP82
    {hal_ll_can_module_num(CAN_MODULE_2), GPIO_PE2, HAL_LL_CAN2_BASE_ADDRESS},
    #endif
    #ifdef CAN1_TX_RE4_RP84
    {hal_ll_can_module_num(CAN_MODULE_1), GPIO_PE4, HAL_LL_CAN1_BASE_ADDRESS},
    #endif
    #ifdef CAN2_TX_RE4_RP84
    {hal_ll_can_module_num(CAN_MODULE_2), GPIO_PE4, HAL_LL_CAN2_BASE_ADDRESS},
    #endif
    #ifdef CAN1_TX_RF13_RP109
    {hal_ll_can_module_num(CAN_MODULE_1), GPIO_PF13, HAL_LL_CAN1_BASE_ADDRESS},
    #endif
    #ifdef CAN2_TX_RF13_RP109
    {hal_ll_can_module_num(CAN_MODULE_2), GPIO_PF13, HAL_LL_CAN2_BASE_ADDRESS},
    #endif
    #ifdef CAN1_TX_RF12_RP108
    {hal_ll_can_module_num(CAN_MODULE_1), GPIO_PF12, HAL_LL_CAN1_BASE_ADDRESS},
    #endif
    #ifdef CAN2_TX_RF12_RP108
    {hal_ll_can_module_num(CAN_MODULE_2), GPIO_PF12, HAL_LL_CAN2_BASE_ADDRESS},
    #endif
    #ifdef CAN1_TX_RD15_RP79
    {hal_ll_can_module_num(CAN_MODULE_1), GPIO_PD15, HAL_LL_CAN1_BASE_ADDRESS},
    #endif
    #ifdef CAN2_TX_RD15_RP79
    {hal_ll_can_module_num(CAN_MODULE_2), GPIO_PD15, HAL_LL_CAN2_BASE_ADDRESS},
    #endif
    #ifdef CAN1_TX_RF2_RP98
    {hal_ll_can_module_num(CAN_MODULE_1), GPIO_PF2, HAL_LL_CAN1_BASE_ADDRESS},
    #endif
    #ifdef CAN2_TX_RF2_RP98
    {hal_ll_can_module_num(CAN_MODULE_2), GPIO_PF2, HAL_LL_CAN2_BASE_ADDRESS},
    #endif
    #ifdef CAN1_TX_RF8_RP104
    {hal_ll_can_module_num(CAN_MODULE_1), GPIO_PF8, HAL_LL_CAN1_BASE_ADDRESS},
    #endif
    #ifdef CAN2_TX_RF8_RP104
    {hal_ll_can_module_num(CAN_MODULE_2), GPIO_PF8, HAL_LL_CAN2_BASE_ADDRESS},
    #endif
    #ifdef CAN1_TX_RG0_RP112
    {hal_ll_can_module_num(CAN_MODULE_1), GPIO_PG0, HAL_LL_CAN1_BASE_ADDRESS},
    #endif
    #ifdef CAN2_TX_RG0_RP112
    {hal_ll_can_module_num(CAN_MODULE_2), GPIO_PG0, HAL_LL_CAN2_BASE_ADDRESS},
    #endif
    #ifdef CAN1_TX_RF6_RP102
    {hal_ll_can_module_num(CAN_MODULE_1), GPIO_PF6, HAL_LL_CAN1_BASE_ADDRESS},
    #endif
    #ifdef CAN2_TX_RF6_RP102
    {hal_ll_can_module_num(CAN_MODULE_2), GPIO_PF6, HAL_LL_CAN2_BASE_ADDRESS},
    #endif
    #ifdef CAN1_TX_RG7_RP119
    {hal_ll_can_module_num(CAN_MODULE_1), GPIO_PG7, HAL_LL_CAN1_BASE_ADDRESS},
    #endif
    #ifdef CAN2_TX_RG7_RP119
    {hal_ll_can_module_num(CAN_MODULE_2), GPIO_PG7, HAL_LL_CAN2_BASE_ADDRESS},
    #endif
    #ifdef CAN1_TX_RB0_RP0
    {hal_ll_can_module_num(CAN_MODULE_1), GPIO_PB0, HAL_LL_CAN1_BASE_ADDRESS},
    #endif
    #ifdef CAN1_TX_RB1_RP1
    {hal_ll_can_module_num(CAN_MODULE_1), GPIO_PB1, HAL_LL_CAN1_BASE_ADDRESS},
    #endif
    #ifdef CAN1_TX_RB2_RP2
    {hal_ll_can_module_num(CAN_MODULE_1), GPIO_PB2, HAL_LL_CAN1_BASE_ADDRESS},
    #endif
    #ifdef CAN1_TX_RB3_RP3
    {hal_ll_can_module_num(CAN_MODULE_1), GPIO_PB3, HAL_LL_CAN1_BASE_ADDRESS},
    #endif
    #ifdef CAN1_TX_RB4_RP4
    {hal_ll_can_module_num(CAN_MODULE_1), GPIO_PB4, HAL_LL_CAN1_BASE_ADDRESS},
    #endif
    #ifdef CAN1_TX_RB5_RP5
    {hal_ll_can_module_num(CAN_MODULE_1), GPIO_PB5, HAL_LL_CAN1_BASE_ADDRESS},
    #endif
    #ifdef CAN1_TX_RB6_RP6
    {hal_ll_can_module_num(CAN_MODULE_1), GPIO_PB6, HAL_LL_CAN1_BASE_ADDRESS},
    #endif
    #ifdef CAN1_TX_RB7_RP7
    {hal_ll_can_module_num(CAN_MODULE_1), GPIO_PB7, HAL_LL_CAN1_BASE_ADDRESS},
    #endif
    #ifdef CAN1_TX_RB8_RP8
    {hal_ll_can_module_num(CAN_MODULE_1), GPIO_PB8, HAL_LL_CAN1_BASE_ADDRESS},
    #endif
    #ifdef CAN1_TX_RB9_RP9
    {hal_ll_can_module_num(CAN_MODULE_1), GPIO_PB9, HAL_LL_CAN1_BASE_ADDRESS},
    #endif
    #ifdef CAN1_TX_RB10_RP10
    {hal_ll_can_module_num(CAN_MODULE_1), GPIO_PB10, HAL_LL_CAN1_BASE_ADDRESS},
    #endif
    #ifdef CAN1_TX_RB11_RP11
    {hal_ll_can_module_num(CAN_MODULE_1), GPIO_PB11, HAL_LL_CAN1_BASE_ADDRESS},
    #endif
    #ifdef CAN1_TX_RB12_RP12
    {hal_ll_can_module_num(CAN_MODULE_1), GPIO_PB12, HAL_LL_CAN1_BASE_ADDRESS},
    #endif
    #ifdef CAN1_TX_RB13_RP13
    {hal_ll_can_module_num(CAN_MODULE_1), GPIO_PB13, HAL_LL_CAN1_BASE_ADDRESS},
    #endif
    #ifdef CAN1_TX_RB14_RP14
    {hal_ll_can_module_num(CAN_MODULE_1), GPIO_PB14, HAL_LL_CAN1_BASE_ADDRESS},
    #endif
    #ifdef CAN1_TX_RB15_RP15
    {hal_ll_can_module_num(CAN_MODULE_1), GPIO_PB15, HAL_LL_CAN1_BASE_ADDRESS},
    #endif
    #ifdef CAN1_TX_RC6_RP22
    {hal_ll_can_module_num(CAN_MODULE_1), GPIO_PC6, HAL_LL_CAN1_BASE_ADDRESS},
    #endif
    #ifdef CAN1_TX_RC7_RP23
    {hal_ll_can_module_num(CAN_MODULE_1), GPIO_PC7, HAL_LL_CAN1_BASE_ADDRESS},
    #endif
    #ifdef CAN1_TX_RC8_RP24
    {hal_ll_can_module_num(CAN_MODULE_1), GPIO_PC8, HAL_LL_CAN1_BASE_ADDRESS},
    #endif
    #ifdef CAN1_TX_RC9_RP25
    {hal_ll_can_module_num(CAN_MODULE_1), GPIO_PC9, HAL_LL_CAN1_BASE_ADDRESS},
    #endif
    #ifdef CAN1_TX_RC0_RP16
    {hal_ll_can_module_num(CAN_MODULE_1), GPIO_PC0, HAL_LL_CAN1_BASE_ADDRESS},
    #endif
    #ifdef CAN1_TX_RC1_RP17
    {hal_ll_can_module_num(CAN_MODULE_1), GPIO_PC1, HAL_LL_CAN1_BASE_ADDRESS},
    #endif
    #ifdef CAN1_TX_RC2_RP18
    {hal_ll_can_module_num(CAN_MODULE_1), GPIO_PC2, HAL_LL_CAN1_BASE_ADDRESS},
    #endif
    #ifdef CAN1_TX_RC3_RP19
    {hal_ll_can_module_num(CAN_MODULE_1), GPIO_PC3, HAL_LL_CAN1_BASE_ADDRESS},
    #endif
    #ifdef CAN1_TX_RC4_RP20
    {hal_ll_can_module_num(CAN_MODULE_1), GPIO_PC4, HAL_LL_CAN1_BASE_ADDRESS},
    #endif
    #ifdef CAN1_TX_RC5_RP21
    {hal_ll_can_module_num(CAN_MODULE_1), GPIO_PC5, HAL_LL_CAN1_BASE_ADDRESS},
    #endif

    {HAL_LL_MODULE_ERROR, HAL_LL_PIN_NC, HAL_LL_MODULE_ERROR}
    //------------ END TX
};

#ifdef __cplusplus
}
#endif

#endif // _HAL_LL_CAN_PIN_MAP_H_
// ------------------------------------------------------------------------- END
