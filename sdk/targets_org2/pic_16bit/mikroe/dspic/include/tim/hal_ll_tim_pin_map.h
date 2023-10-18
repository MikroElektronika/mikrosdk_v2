/****************************************************************************
**
** Copyright (C) 2023 MikroElektronika d.o.o.
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
 * @file  hal_ll_tim_pin_map.h
 * @brief CCP/TIM HAL LOW LEVEL PIN MAPS.
 */

#ifndef _HAL_LL_TIM_PIN_MAP_H_
#define _HAL_LL_TIM_PIN_MAP_H_

#ifdef __cplusplus
extern "C"{
#endif

#include "hal_ll_pin_names.h"

/*!< @brief Helper macro for getting adequate module index number */
#define hal_ll_tim_module_num(_module_num) (_module_num - 1)

/*!< @brief TIM Master pin map structure. */
typedef struct
{
    hal_ll_pin_name_t pin;
    uint8_t timer;
    uint8_t channel;
    uint8_t module_index;
} hal_ll_tim_pin_map_t;

/*!< @brief TIM Modules. */
typedef enum
{
    HAL_LL_TIM_INDEX_1 = 0,
    HAL_LL_TIM_INDEX_2,
    HAL_LL_TIM_INDEX_3,
    HAL_LL_TIM_INDEX_4,
    HAL_LL_TIM_INDEX_5,
    HAL_LL_TIM_INDEX_NOT_SET
} hal_ll_tim_index_t;

typedef enum
{
    HAL_LL_CCP_CHANNEL_1 = 0,
    HAL_LL_CCP_CHANNEL_2,
    HAL_LL_CCP_CHANNEL_3,
    HAL_LL_CCP_CHANNEL_4,
    HAL_LL_CCP_CHANNEL_5,
    HAL_LL_CCP_CHANNEL_6,
    HAL_LL_CCP_CHANNEL_7,
    HAL_LL_CCP_CHANNEL_8,
    HAL_LL_CCP_CHANNEL_9,
    HAL_LL_CCP_CHANNEL_10,
    HAL_LL_CCP_CHANNEL_11,
    HAL_LL_CCP_CHANNEL_12,
    HAL_LL_CCP_CHANNEL_13,
    HAL_LL_CCP_CHANNEL_14,
    HAL_LL_CCP_CHANNEL_15,
    HAL_LL_CCP_CHANNEL_16,
    HAL_LL_CCP_CHANNEL_NOT_SET
} hal_ll_ccp_channel_t;

/*!< @brief CCP/TIM pins */
static const hal_ll_tim_pin_map_t _tim_map[] = {
    //------------ BEGIN CCP
    #ifdef PWM_CCP1_RB7
    {PB7, HAL_LL_TIM_INDEX_2, HAL_LL_CCP_CHANNEL_8, hal_ll_tim_module_num(CCP_MODULE_1)},
    #endif
    #ifdef PWM_CCP1_RD0
    {PD0, HAL_LL_TIM_INDEX_2, HAL_LL_CCP_CHANNEL_1, hal_ll_tim_module_num(CCP_MODULE_1)},
    #endif
    #ifdef PWM_CCP2_RB7
    {PB7, HAL_LL_TIM_INDEX_2, HAL_LL_CCP_CHANNEL_8, hal_ll_tim_module_num(CCP_MODULE_2)},
    #endif
    #ifdef PWM_CCP2_RD0
    {PD0, HAL_LL_TIM_INDEX_2, HAL_LL_CCP_CHANNEL_1, hal_ll_tim_module_num(CCP_MODULE_2)},
    #endif
    #ifdef PWM_CCP3_RB7
    {PB7, HAL_LL_TIM_INDEX_2, HAL_LL_CCP_CHANNEL_8, hal_ll_tim_module_num(CCP_MODULE_3)},
    #endif
    #ifdef PWM_CCP3_RD0
    {PD0, HAL_LL_TIM_INDEX_2, HAL_LL_CCP_CHANNEL_1, hal_ll_tim_module_num(CCP_MODULE_3)},
    #endif
    #ifdef PWM_CCP1_RB8
    {PB8, HAL_LL_TIM_INDEX_2, HAL_LL_CCP_CHANNEL_9, hal_ll_tim_module_num(CCP_MODULE_1)},
    #endif
    #ifdef PWM_CCP1_RB9
    {PB9, HAL_LL_TIM_INDEX_2, HAL_LL_CCP_CHANNEL_10, hal_ll_tim_module_num(CCP_MODULE_1)},
    #endif
    #ifdef PWM_CCP2_RB8
    {PB8, HAL_LL_TIM_INDEX_2, HAL_LL_CCP_CHANNEL_9, hal_ll_tim_module_num(CCP_MODULE_2)},
    #endif
    #ifdef PWM_CCP2_RB9
    {PB9, HAL_LL_TIM_INDEX_2, HAL_LL_CCP_CHANNEL_10, hal_ll_tim_module_num(CCP_MODULE_2)},
    #endif
    #ifdef PWM_CCP3_RB8
    {PB8, HAL_LL_TIM_INDEX_2, HAL_LL_CCP_CHANNEL_9, hal_ll_tim_module_num(CCP_MODULE_3)},
    #endif
    #ifdef PWM_CCP3_RB9
    {PB9, HAL_LL_TIM_INDEX_2, HAL_LL_CCP_CHANNEL_10, hal_ll_tim_module_num(CCP_MODULE_3)},
    #endif
    #ifdef PWM_CCP1_RD1
    {PD1, HAL_LL_TIM_INDEX_2, HAL_LL_CCP_CHANNEL_2, hal_ll_tim_module_num(CCP_MODULE_1)},
    #endif
    #ifdef PWM_CCP2_RD1
    {PD1, HAL_LL_TIM_INDEX_2, HAL_LL_CCP_CHANNEL_2, hal_ll_tim_module_num(CCP_MODULE_2)},
    #endif
    #ifdef PWM_CCP3_RD1
    {PD1, HAL_LL_TIM_INDEX_2, HAL_LL_CCP_CHANNEL_2, hal_ll_tim_module_num(CCP_MODULE_3)},
    #endif
    #ifdef PWM_CCP1_RD2
    {PD2, HAL_LL_TIM_INDEX_2, HAL_LL_CCP_CHANNEL_3, hal_ll_tim_module_num(CCP_MODULE_1)},
    #endif
    #ifdef PWM_CCP1_RD3
    {PD3, HAL_LL_TIM_INDEX_2, HAL_LL_CCP_CHANNEL_4, hal_ll_tim_module_num(CCP_MODULE_1)},
    #endif
    #ifdef PWM_CCP2_RD2
    {PD2, HAL_LL_TIM_INDEX_2, HAL_LL_CCP_CHANNEL_3, hal_ll_tim_module_num(CCP_MODULE_2)},
    #endif
    #ifdef PWM_CCP2_RD3
    {PD3, HAL_LL_TIM_INDEX_2, HAL_LL_CCP_CHANNEL_4, hal_ll_tim_module_num(CCP_MODULE_2)},
    #endif
    #ifdef PWM_CCP3_RD2
    {PD2, HAL_LL_TIM_INDEX_2, HAL_LL_CCP_CHANNEL_3, hal_ll_tim_module_num(CCP_MODULE_3)},
    #endif
    #ifdef PWM_CCP3_RD3
    {PD3, HAL_LL_TIM_INDEX_2, HAL_LL_CCP_CHANNEL_4, hal_ll_tim_module_num(CCP_MODULE_3)},
    #endif
    #ifdef PWM_CCP4_RD0
    {PD0, HAL_LL_TIM_INDEX_2, HAL_LL_CCP_CHANNEL_1, hal_ll_tim_module_num(CCP_MODULE_4)},
    #endif
    #ifdef PWM_CCP4_RD1
    {PD1, HAL_LL_TIM_INDEX_2, HAL_LL_CCP_CHANNEL_2, hal_ll_tim_module_num(CCP_MODULE_4)},
    #endif
    #ifdef PWM_CCP4_RD2
    {PD2, HAL_LL_TIM_INDEX_2, HAL_LL_CCP_CHANNEL_3, hal_ll_tim_module_num(CCP_MODULE_4)},
    #endif
    #ifdef PWM_CCP4_RD3
    {PD3, HAL_LL_TIM_INDEX_2, HAL_LL_CCP_CHANNEL_4, hal_ll_tim_module_num(CCP_MODULE_4)},
    #endif
    #ifdef PWM_CCP5_RD0
    {PD0, HAL_LL_TIM_INDEX_2, HAL_LL_CCP_CHANNEL_1, hal_ll_tim_module_num(CCP_MODULE_5)},
    #endif
    #ifdef PWM_CCP5_RD1
    {PD1, HAL_LL_TIM_INDEX_2, HAL_LL_CCP_CHANNEL_2, hal_ll_tim_module_num(CCP_MODULE_5)},
    #endif
    #ifdef PWM_CCP5_RD2
    {PD2, HAL_LL_TIM_INDEX_2, HAL_LL_CCP_CHANNEL_3, hal_ll_tim_module_num(CCP_MODULE_5)},
    #endif
    #ifdef PWM_CCP5_RD3
    {PD3, HAL_LL_TIM_INDEX_2, HAL_LL_CCP_CHANNEL_4, hal_ll_tim_module_num(CCP_MODULE_5)},
    #endif
    #ifdef PWM_CCP1_RD4
    {PD4, HAL_LL_TIM_INDEX_2, HAL_LL_CCP_CHANNEL_5, hal_ll_tim_module_num(CCP_MODULE_1)},
    #endif
    #ifdef PWM_CCP1_RD5
    {PD5, HAL_LL_TIM_INDEX_2, HAL_LL_CCP_CHANNEL_6, hal_ll_tim_module_num(CCP_MODULE_1)},
    #endif
    #ifdef PWM_CCP1_RD6
    {PD6, HAL_LL_TIM_INDEX_2, HAL_LL_CCP_CHANNEL_7, hal_ll_tim_module_num(CCP_MODULE_1)},
    #endif
    #ifdef PWM_CCP1_RD7
    {PD7, HAL_LL_TIM_INDEX_2, HAL_LL_CCP_CHANNEL_8, hal_ll_tim_module_num(CCP_MODULE_1)},
    #endif
    #ifdef PWM_CCP2_RD4
    {PD4, HAL_LL_TIM_INDEX_2, HAL_LL_CCP_CHANNEL_5, hal_ll_tim_module_num(CCP_MODULE_2)},
    #endif
    #ifdef PWM_CCP2_RD5
    {PD5, HAL_LL_TIM_INDEX_2, HAL_LL_CCP_CHANNEL_6, hal_ll_tim_module_num(CCP_MODULE_2)},
    #endif
    #ifdef PWM_CCP2_RD6
    {PD6, HAL_LL_TIM_INDEX_2, HAL_LL_CCP_CHANNEL_7, hal_ll_tim_module_num(CCP_MODULE_2)},
    #endif
    #ifdef PWM_CCP2_RD7
    {PD7, HAL_LL_TIM_INDEX_2, HAL_LL_CCP_CHANNEL_8, hal_ll_tim_module_num(CCP_MODULE_2)},
    #endif
    #ifdef PWM_CCP3_RD4
    {PD4, HAL_LL_TIM_INDEX_2, HAL_LL_CCP_CHANNEL_5, hal_ll_tim_module_num(CCP_MODULE_3)},
    #endif
    #ifdef PWM_CCP3_RD5
    {PD5, HAL_LL_TIM_INDEX_2, HAL_LL_CCP_CHANNEL_6, hal_ll_tim_module_num(CCP_MODULE_3)},
    #endif
    #ifdef PWM_CCP3_RD6
    {PD6, HAL_LL_TIM_INDEX_2, HAL_LL_CCP_CHANNEL_7, hal_ll_tim_module_num(CCP_MODULE_3)},
    #endif
    #ifdef PWM_CCP3_RD7
    {PD7, HAL_LL_TIM_INDEX_2, HAL_LL_CCP_CHANNEL_8, hal_ll_tim_module_num(CCP_MODULE_3)},
    #endif
    #ifdef PWM_CCP4_RD4
    {PD4, HAL_LL_TIM_INDEX_2, HAL_LL_CCP_CHANNEL_5, hal_ll_tim_module_num(CCP_MODULE_4)},
    #endif
    #ifdef PWM_CCP4_RD5
    {PD5, HAL_LL_TIM_INDEX_2, HAL_LL_CCP_CHANNEL_6, hal_ll_tim_module_num(CCP_MODULE_4)},
    #endif
    #ifdef PWM_CCP4_RD6
    {PD6, HAL_LL_TIM_INDEX_2, HAL_LL_CCP_CHANNEL_7, hal_ll_tim_module_num(CCP_MODULE_4)},
    #endif
    #ifdef PWM_CCP4_RD7
    {PD7, HAL_LL_TIM_INDEX_2, HAL_LL_CCP_CHANNEL_8, hal_ll_tim_module_num(CCP_MODULE_4)},
    #endif
    #ifdef PWM_CCP5_RD4
    {PD4, HAL_LL_TIM_INDEX_2, HAL_LL_CCP_CHANNEL_5, hal_ll_tim_module_num(CCP_MODULE_5)},
    #endif
    #ifdef PWM_CCP5_RD5
    {PD5, HAL_LL_TIM_INDEX_2, HAL_LL_CCP_CHANNEL_6, hal_ll_tim_module_num(CCP_MODULE_5)},
    #endif
    #ifdef PWM_CCP5_RD6
    {PD6, HAL_LL_TIM_INDEX_2, HAL_LL_CCP_CHANNEL_7, hal_ll_tim_module_num(CCP_MODULE_5)},
    #endif
    #ifdef PWM_CCP5_RD7
    {PD7, HAL_LL_TIM_INDEX_2, HAL_LL_CCP_CHANNEL_8, hal_ll_tim_module_num(CCP_MODULE_5)},
    #endif
    #ifdef PWM_CCP1_OC1_RA4_RP20
    {PA4, HAL_LL_TIM_INDEX_2, HAL_LL_CCP_CHANNEL_1, hal_ll_tim_module_num(CCP_MODULE_1)},
    #endif
    #ifdef PWM_CCP2_OC1_RB7_RP39
    {PB7, HAL_LL_TIM_INDEX_2, HAL_LL_CCP_CHANNEL_1, hal_ll_tim_module_num(CCP_MODULE_2)},
    #endif
    #ifdef PWM_CCP2_OC2_RB3_RP35
    {PB3, HAL_LL_TIM_INDEX_2, HAL_LL_CCP_CHANNEL_2, hal_ll_tim_module_num(CCP_MODULE_2)},
    #endif
    #ifdef PWM_CCP2_OC3_RB5_RP37
    {PB5, HAL_LL_TIM_INDEX_2, HAL_LL_CCP_CHANNEL_3, hal_ll_tim_module_num(CCP_MODULE_2)},
    #endif
    #ifdef PWM_CCP2_OC6_RB10_RP42
    {PB10, HAL_LL_TIM_INDEX_2, HAL_LL_CCP_CHANNEL_6, hal_ll_tim_module_num(CCP_MODULE_2)},
    #endif
    #ifdef PWM_CCP2_OC6_RB6_RP38
    {PB6, HAL_LL_TIM_INDEX_2, HAL_LL_CCP_CHANNEL_6, hal_ll_tim_module_num(CCP_MODULE_2)},
    #endif
    #ifdef PWM_CCP2_OC6_RB8_RP40
    {PB8, HAL_LL_TIM_INDEX_2, HAL_LL_CCP_CHANNEL_6, hal_ll_tim_module_num(CCP_MODULE_2)},
    #endif
    #ifdef PWM_CCP2_OC8_RB11_RP43
    {PB11, HAL_LL_TIM_INDEX_2, HAL_LL_CCP_CHANNEL_8, hal_ll_tim_module_num(CCP_MODULE_2)},
    #endif
    #ifdef PWM_CCP2_OC8_RB4_RP36
    {PB4, HAL_LL_TIM_INDEX_2, HAL_LL_CCP_CHANNEL_8, hal_ll_tim_module_num(CCP_MODULE_2)},
    #endif
    #ifdef PWM_CCP2_OC8_RB9_RP41
    {PB9, HAL_LL_TIM_INDEX_2, HAL_LL_CCP_CHANNEL_8, hal_ll_tim_module_num(CCP_MODULE_2)},
    #endif
    #ifdef PWM_CCP3_OC2_RC9_RP57
    {PC9, HAL_LL_TIM_INDEX_2, HAL_LL_CCP_CHANNEL_2, hal_ll_tim_module_num(CCP_MODULE_3)},
    #endif
    #ifdef PWM_CCP3_OC3_RC1_RP49
    {PC1, HAL_LL_TIM_INDEX_2, HAL_LL_CCP_CHANNEL_3, hal_ll_tim_module_num(CCP_MODULE_3)},
    #endif
    #ifdef PWM_CCP3_OC4_RC0_RP48
    {PC0, HAL_LL_TIM_INDEX_2, HAL_LL_CCP_CHANNEL_4, hal_ll_tim_module_num(CCP_MODULE_3)},
    #endif
    #ifdef PWM_CCP3_OC4_RC6_RP54
    {PC6, HAL_LL_TIM_INDEX_2, HAL_LL_CCP_CHANNEL_4, hal_ll_tim_module_num(CCP_MODULE_3)},
    #endif
    #ifdef PWM_CCP3_OC6_RC7_RP55
    {PC7, HAL_LL_TIM_INDEX_2, HAL_LL_CCP_CHANNEL_6, hal_ll_tim_module_num(CCP_MODULE_3)},
    #endif
    #ifdef PWM_CCP3_OC8_RC8_RP56
    {PC8, HAL_LL_TIM_INDEX_2, HAL_LL_CCP_CHANNEL_8, hal_ll_tim_module_num(CCP_MODULE_3)},
    #endif
    #ifdef PWM_CCP4_OC8_RA4_RP20
    {PA4, HAL_LL_TIM_INDEX_2, HAL_LL_CCP_CHANNEL_8, hal_ll_tim_module_num(CCP_MODULE_4)},
    #endif
    #ifdef PWM_CCP5_OC1_RB3_RP35
    {PB3, HAL_LL_TIM_INDEX_2, HAL_LL_CCP_CHANNEL_1, hal_ll_tim_module_num(CCP_MODULE_5)},
    #endif
    #ifdef PWM_CCP5_OC2_RB5_RP37
    {PB5, HAL_LL_TIM_INDEX_2, HAL_LL_CCP_CHANNEL_2, hal_ll_tim_module_num(CCP_MODULE_5)},
    #endif
    #ifdef PWM_CCP5_OC5_RB10_RP42
    {PB10, HAL_LL_TIM_INDEX_2, HAL_LL_CCP_CHANNEL_5, hal_ll_tim_module_num(CCP_MODULE_5)},
    #endif
    #ifdef PWM_CCP5_OC5_RB6_RP38
    {PB6, HAL_LL_TIM_INDEX_2, HAL_LL_CCP_CHANNEL_5, hal_ll_tim_module_num(CCP_MODULE_5)},
    #endif
    #ifdef PWM_CCP5_OC5_RB8_RP40
    {PB8, HAL_LL_TIM_INDEX_2, HAL_LL_CCP_CHANNEL_5, hal_ll_tim_module_num(CCP_MODULE_5)},
    #endif
    #ifdef PWM_CCP5_OC7_RB11_RP43
    {PB11, HAL_LL_TIM_INDEX_2, HAL_LL_CCP_CHANNEL_7, hal_ll_tim_module_num(CCP_MODULE_5)},
    #endif
    #ifdef PWM_CCP5_OC7_RB4_RP36
    {PB4, HAL_LL_TIM_INDEX_2, HAL_LL_CCP_CHANNEL_7, hal_ll_tim_module_num(CCP_MODULE_5)},
    #endif
    #ifdef PWM_CCP5_OC7_RB9_RP41
    {PB9, HAL_LL_TIM_INDEX_2, HAL_LL_CCP_CHANNEL_7, hal_ll_tim_module_num(CCP_MODULE_5)},
    #endif
    #ifdef PWM_CCP5_OC8_RB7_RP39
    {PB7, HAL_LL_TIM_INDEX_2, HAL_LL_CCP_CHANNEL_8, hal_ll_tim_module_num(CCP_MODULE_5)},
    #endif
    #ifdef PWM_CCP6_OC1_RC9_RP57
    {PC9, HAL_LL_TIM_INDEX_2, HAL_LL_CCP_CHANNEL_1, hal_ll_tim_module_num(CCP_MODULE_6)},
    #endif
    #ifdef PWM_CCP6_OC2_RC1_RP49
    {PC1, HAL_LL_TIM_INDEX_2, HAL_LL_CCP_CHANNEL_2, hal_ll_tim_module_num(CCP_MODULE_6)},
    #endif
    #ifdef PWM_CCP6_OC3_RC0_RP48
    {PC0, HAL_LL_TIM_INDEX_2, HAL_LL_CCP_CHANNEL_3, hal_ll_tim_module_num(CCP_MODULE_6)},
    #endif
    #ifdef PWM_CCP6_OC3_RC6_RP54
    {PC6, HAL_LL_TIM_INDEX_2, HAL_LL_CCP_CHANNEL_3, hal_ll_tim_module_num(CCP_MODULE_6)},
    #endif
    #ifdef PWM_CCP6_OC5_RC7_RP55
    {PC7, HAL_LL_TIM_INDEX_2, HAL_LL_CCP_CHANNEL_5, hal_ll_tim_module_num(CCP_MODULE_6)},
    #endif
    #ifdef PWM_CCP6_OC7_RC8_RP56
    {PC8, HAL_LL_TIM_INDEX_2, HAL_LL_CCP_CHANNEL_7, hal_ll_tim_module_num(CCP_MODULE_6)},
    #endif
    #ifdef PWM_CCP7_OC7_RA4_RP20
    {PA4, HAL_LL_TIM_INDEX_2, HAL_LL_CCP_CHANNEL_7, hal_ll_tim_module_num(CCP_MODULE_7)},
    #endif
    #ifdef PWM_CCP8_OC1_RB5_RP37
    {PB5, HAL_LL_TIM_INDEX_2, HAL_LL_CCP_CHANNEL_1, hal_ll_tim_module_num(CCP_MODULE_8)},
    #endif
    #ifdef PWM_CCP8_OC4_RB10_RP42
    {PB10, HAL_LL_TIM_INDEX_2, HAL_LL_CCP_CHANNEL_4, hal_ll_tim_module_num(CCP_MODULE_8)},
    #endif
    #ifdef PWM_CCP8_OC4_RB6_RP38
    {PB6, HAL_LL_TIM_INDEX_2, HAL_LL_CCP_CHANNEL_4, hal_ll_tim_module_num(CCP_MODULE_8)},
    #endif
    #ifdef PWM_CCP8_OC4_RB8_RP40
    {PB8, HAL_LL_TIM_INDEX_2, HAL_LL_CCP_CHANNEL_4, hal_ll_tim_module_num(CCP_MODULE_8)},
    #endif
    #ifdef PWM_CCP8_OC6_RB11_RP43
    {PB11, HAL_LL_TIM_INDEX_2, HAL_LL_CCP_CHANNEL_6, hal_ll_tim_module_num(CCP_MODULE_8)},
    #endif
    #ifdef PWM_CCP8_OC6_RB4_RP36
    {PB4, HAL_LL_TIM_INDEX_2, HAL_LL_CCP_CHANNEL_6, hal_ll_tim_module_num(CCP_MODULE_8)},
    #endif
    #ifdef PWM_CCP8_OC6_RB9_RP41
    {PB9, HAL_LL_TIM_INDEX_2, HAL_LL_CCP_CHANNEL_6, hal_ll_tim_module_num(CCP_MODULE_8)},
    #endif
    #ifdef PWM_CCP8_OC7_RB7_RP39
    {PB7, HAL_LL_TIM_INDEX_2, HAL_LL_CCP_CHANNEL_7, hal_ll_tim_module_num(CCP_MODULE_8)},
    #endif
    #ifdef PWM_CCP8_OC8_RB3_RP35
    {PB3, HAL_LL_TIM_INDEX_2, HAL_LL_CCP_CHANNEL_8, hal_ll_tim_module_num(CCP_MODULE_8)},
    #endif
    #ifdef PWM_CCP9_OC1_RC1_RP49
    {PC1, HAL_LL_TIM_INDEX_2, HAL_LL_CCP_CHANNEL_1, hal_ll_tim_module_num(CCP_MODULE_9)},
    #endif
    #ifdef PWM_CCP9_OC2_RC0_RP48
    {PC0, HAL_LL_TIM_INDEX_2, HAL_LL_CCP_CHANNEL_2, hal_ll_tim_module_num(CCP_MODULE_9)},
    #endif
    #ifdef PWM_CCP9_OC2_RC6_RP54
    {PC6, HAL_LL_TIM_INDEX_2, HAL_LL_CCP_CHANNEL_2, hal_ll_tim_module_num(CCP_MODULE_9)},
    #endif
    #ifdef PWM_CCP9_OC4_RC7_RP55
    {PC7, HAL_LL_TIM_INDEX_2, HAL_LL_CCP_CHANNEL_4, hal_ll_tim_module_num(CCP_MODULE_9)},
    #endif
    #ifdef PWM_CCP9_OC6_RC8_RP56
    {PC8, HAL_LL_TIM_INDEX_2, HAL_LL_CCP_CHANNEL_6, hal_ll_tim_module_num(CCP_MODULE_9)},
    #endif
    #ifdef PWM_CCP9_OC8_RC9_RP57
    {PC9, HAL_LL_TIM_INDEX_2, HAL_LL_CCP_CHANNEL_8, hal_ll_tim_module_num(CCP_MODULE_9)},
    #endif
    #ifdef PWM_CCP2_OC2_RB10_RP42
    {PB10, HAL_LL_TIM_INDEX_2, HAL_LL_CCP_CHANNEL_2, hal_ll_tim_module_num(CCP_MODULE_2)},
    #endif
    #ifdef PWM_CCP2_OC2_RB7_RP39
    {PB7, HAL_LL_TIM_INDEX_2, HAL_LL_CCP_CHANNEL_2, hal_ll_tim_module_num(CCP_MODULE_2)},
    #endif
    #ifdef PWM_CCP2_OC5_RB11_RP43
    {PB11, HAL_LL_TIM_INDEX_2, HAL_LL_CCP_CHANNEL_5, hal_ll_tim_module_num(CCP_MODULE_2)},
    #endif
    #ifdef PWM_CCP2_OC5_RB9_RP41
    {PB9, HAL_LL_TIM_INDEX_2, HAL_LL_CCP_CHANNEL_5, hal_ll_tim_module_num(CCP_MODULE_2)},
    #endif
    #ifdef PWM_CCP2_OC7_RB4_RP36
    {PB4, HAL_LL_TIM_INDEX_2, HAL_LL_CCP_CHANNEL_7, hal_ll_tim_module_num(CCP_MODULE_2)},
    #endif
    #ifdef PWM_CCP2_OC7_RB8_RP40
    {PB8, HAL_LL_TIM_INDEX_2, HAL_LL_CCP_CHANNEL_7, hal_ll_tim_module_num(CCP_MODULE_2)},
    #endif
    #ifdef PWM_CCP2_OC8_RB3_RP35
    {PB3, HAL_LL_TIM_INDEX_2, HAL_LL_CCP_CHANNEL_8, hal_ll_tim_module_num(CCP_MODULE_2)},
    #endif
    #ifdef PWM_CCP3_OC3_RC6_RP54
    {PC6, HAL_LL_TIM_INDEX_2, HAL_LL_CCP_CHANNEL_3, hal_ll_tim_module_num(CCP_MODULE_3)},
    #endif
    #ifdef PWM_CCP3_OC3_RC9_RP57
    {PC9, HAL_LL_TIM_INDEX_2, HAL_LL_CCP_CHANNEL_3, hal_ll_tim_module_num(CCP_MODULE_3)},
    #endif
    #ifdef PWM_CCP3_OC5_RC7_RP55
    {PC7, HAL_LL_TIM_INDEX_2, HAL_LL_CCP_CHANNEL_5, hal_ll_tim_module_num(CCP_MODULE_3)},
    #endif
    #ifdef PWM_CCP3_OC6_RC1_RP49
    {PC1, HAL_LL_TIM_INDEX_2, HAL_LL_CCP_CHANNEL_6, hal_ll_tim_module_num(CCP_MODULE_3)},
    #endif
    #ifdef PWM_CCP3_OC8_RC0_RP48
    {PC0, HAL_LL_TIM_INDEX_2, HAL_LL_CCP_CHANNEL_8, hal_ll_tim_module_num(CCP_MODULE_3)},
    #endif
    #ifdef PWM_CCP4_OC5_RD5_RP69
    {PD5, HAL_LL_TIM_INDEX_2, HAL_LL_CCP_CHANNEL_5, hal_ll_tim_module_num(CCP_MODULE_4)},
    #endif
    #ifdef PWM_CCP4_OC7_RD6_RP70
    {PD6, HAL_LL_TIM_INDEX_2, HAL_LL_CCP_CHANNEL_7, hal_ll_tim_module_num(CCP_MODULE_4)},
    #endif
    #ifdef PWM_CCP5_OC8_RF1_RP97
    {PF1, HAL_LL_TIM_INDEX_2, HAL_LL_CCP_CHANNEL_8, hal_ll_tim_module_num(CCP_MODULE_5)},
    #endif
    #ifdef PWM_CCP6_OC1_RG6_RP118
    {PG6, HAL_LL_TIM_INDEX_2, HAL_LL_CCP_CHANNEL_1, hal_ll_tim_module_num(CCP_MODULE_6)},
    #endif
    #ifdef PWM_CCP6_OC4_RG8_RP120
    {PG8, HAL_LL_TIM_INDEX_2, HAL_LL_CCP_CHANNEL_4, hal_ll_tim_module_num(CCP_MODULE_6)},
    #endif
    #ifdef PWM_CCP7_OC8_RA4_RP20
    {PA4, HAL_LL_TIM_INDEX_2, HAL_LL_CCP_CHANNEL_8, hal_ll_tim_module_num(CCP_MODULE_7)},
    #endif
    #ifdef PWM_CCP8_OC1_RB10_RP42
    {PB10, HAL_LL_TIM_INDEX_2, HAL_LL_CCP_CHANNEL_1, hal_ll_tim_module_num(CCP_MODULE_8)},
    #endif
    #ifdef PWM_CCP8_OC1_RB7_RP39
    {PB7, HAL_LL_TIM_INDEX_2, HAL_LL_CCP_CHANNEL_1, hal_ll_tim_module_num(CCP_MODULE_8)},
    #endif
    #ifdef PWM_CCP8_OC2_RB5_RP37
    {PB5, HAL_LL_TIM_INDEX_2, HAL_LL_CCP_CHANNEL_2, hal_ll_tim_module_num(CCP_MODULE_8)},
    #endif
    #ifdef PWM_CCP8_OC4_RB11_RP43
    {PB11, HAL_LL_TIM_INDEX_2, HAL_LL_CCP_CHANNEL_4, hal_ll_tim_module_num(CCP_MODULE_8)},
    #endif
    #ifdef PWM_CCP8_OC4_RB9_RP41
    {PB9, HAL_LL_TIM_INDEX_2, HAL_LL_CCP_CHANNEL_4, hal_ll_tim_module_num(CCP_MODULE_8)},
    #endif
    #ifdef PWM_CCP8_OC5_RB6_RP38
    {PB6, HAL_LL_TIM_INDEX_2, HAL_LL_CCP_CHANNEL_5, hal_ll_tim_module_num(CCP_MODULE_8)},
    #endif
    #ifdef PWM_CCP8_OC6_RB8_RP40
    {PB8, HAL_LL_TIM_INDEX_2, HAL_LL_CCP_CHANNEL_6, hal_ll_tim_module_num(CCP_MODULE_8)},
    #endif
    #ifdef PWM_CCP8_OC7_RB3_RP35
    {PB3, HAL_LL_TIM_INDEX_2, HAL_LL_CCP_CHANNEL_7, hal_ll_tim_module_num(CCP_MODULE_8)},
    #endif
    #ifdef PWM_CCP9_OC2_RC9_RP57
    {PC9, HAL_LL_TIM_INDEX_2, HAL_LL_CCP_CHANNEL_2, hal_ll_tim_module_num(CCP_MODULE_9)},
    #endif
    #ifdef PWM_CCP9_OC5_RC1_RP49
    {PC1, HAL_LL_TIM_INDEX_2, HAL_LL_CCP_CHANNEL_5, hal_ll_tim_module_num(CCP_MODULE_9)},
    #endif
    #ifdef PWM_CCP9_OC7_RC0_RP48
    {PC0, HAL_LL_TIM_INDEX_2, HAL_LL_CCP_CHANNEL_7, hal_ll_tim_module_num(CCP_MODULE_9)},
    #endif
    #ifdef PWM_CCP9_OC7_RC8_RP56
    {PC8, HAL_LL_TIM_INDEX_2, HAL_LL_CCP_CHANNEL_7, hal_ll_tim_module_num(CCP_MODULE_9)},
    #endif
    #ifdef PWM_CCP3_OC1_RC9_RP57
    {PC9, HAL_LL_TIM_INDEX_2, HAL_LL_CCP_CHANNEL_1, hal_ll_tim_module_num(CCP_MODULE_3)},
    #endif
    #ifdef PWM_CCP3_OC7_RC1_RP49
    {PC1, HAL_LL_TIM_INDEX_2, HAL_LL_CCP_CHANNEL_7, hal_ll_tim_module_num(CCP_MODULE_3)},
    #endif
    #ifdef PWM_CCP3_OC7_RC8_RP56
    {PC8, HAL_LL_TIM_INDEX_2, HAL_LL_CCP_CHANNEL_7, hal_ll_tim_module_num(CCP_MODULE_3)},
    #endif
    #ifdef PWM_CCP4_OC2_RD5_RP69
    {PD5, HAL_LL_TIM_INDEX_2, HAL_LL_CCP_CHANNEL_2, hal_ll_tim_module_num(CCP_MODULE_4)},
    #endif
    #ifdef PWM_CCP4_OC4_RD6_RP70
    {PD6, HAL_LL_TIM_INDEX_2, HAL_LL_CCP_CHANNEL_4, hal_ll_tim_module_num(CCP_MODULE_4)},
    #endif
    #ifdef PWM_CCP5_OC5_RE1_RP81
    {PE1, HAL_LL_TIM_INDEX_2, HAL_LL_CCP_CHANNEL_5, hal_ll_tim_module_num(CCP_MODULE_5)},
    #endif
    #ifdef PWM_CCP6_OC7_RF1_RP97
    {PF1, HAL_LL_TIM_INDEX_2, HAL_LL_CCP_CHANNEL_7, hal_ll_tim_module_num(CCP_MODULE_6)},
    #endif
    #ifdef PWM_CCP7_OC1_RG1_RP113
    {PG1, HAL_LL_TIM_INDEX_2, HAL_LL_CCP_CHANNEL_1, hal_ll_tim_module_num(CCP_MODULE_7)},
    #endif
    #ifdef PWM_CCP7_OC2_RG14_RP126
    {PG14, HAL_LL_TIM_INDEX_2, HAL_LL_CCP_CHANNEL_2, hal_ll_tim_module_num(CCP_MODULE_7)},
    #endif
    #ifdef PWM_CCP7_OC2_RG6_RP118
    {PG6, HAL_LL_TIM_INDEX_2, HAL_LL_CCP_CHANNEL_2, hal_ll_tim_module_num(CCP_MODULE_7)},
    #endif
    #ifdef PWM_CCP7_OC3_RG13_RP125
    {PG13, HAL_LL_TIM_INDEX_2, HAL_LL_CCP_CHANNEL_3, hal_ll_tim_module_num(CCP_MODULE_7)},
    #endif
    #ifdef PWM_CCP7_OC5_RG8_RP120
    {PG8, HAL_LL_TIM_INDEX_2, HAL_LL_CCP_CHANNEL_5, hal_ll_tim_module_num(CCP_MODULE_7)},
    #endif
    #ifdef PWM_CCP7_OC8_RG15_RP127
    {PG15, HAL_LL_TIM_INDEX_2, HAL_LL_CCP_CHANNEL_8, hal_ll_tim_module_num(CCP_MODULE_7)},
    #endif
    #ifdef PWM_CCP8_OC4_RA4_RP20
    {PA4, HAL_LL_TIM_INDEX_2, HAL_LL_CCP_CHANNEL_4, hal_ll_tim_module_num(CCP_MODULE_8)},
    #endif
    #ifdef PWM_CCP9_OC1_RB6_RP38
    {PB6, HAL_LL_TIM_INDEX_2, HAL_LL_CCP_CHANNEL_1, hal_ll_tim_module_num(CCP_MODULE_9)},
    #endif
    #ifdef PWM_CCP9_OC2_RB4_RP36
    {PB4, HAL_LL_TIM_INDEX_2, HAL_LL_CCP_CHANNEL_2, hal_ll_tim_module_num(CCP_MODULE_9)},
    #endif
    #ifdef PWM_CCP9_OC2_RB8_RP40
    {PB8, HAL_LL_TIM_INDEX_2, HAL_LL_CCP_CHANNEL_2, hal_ll_tim_module_num(CCP_MODULE_9)},
    #endif
    #ifdef PWM_CCP9_OC3_RB3_RP35
    {PB3, HAL_LL_TIM_INDEX_2, HAL_LL_CCP_CHANNEL_3, hal_ll_tim_module_num(CCP_MODULE_9)},
    #endif
    #ifdef PWM_CCP9_OC5_RB10_RP42
    {PB10, HAL_LL_TIM_INDEX_2, HAL_LL_CCP_CHANNEL_5, hal_ll_tim_module_num(CCP_MODULE_9)},
    #endif
    #ifdef PWM_CCP9_OC5_RB7_RP39
    {PB7, HAL_LL_TIM_INDEX_2, HAL_LL_CCP_CHANNEL_5, hal_ll_tim_module_num(CCP_MODULE_9)},
    #endif
    #ifdef PWM_CCP9_OC6_RB5_RP37
    {PB5, HAL_LL_TIM_INDEX_2, HAL_LL_CCP_CHANNEL_6, hal_ll_tim_module_num(CCP_MODULE_9)},
    #endif
    #ifdef PWM_CCP9_OC8_RB11_RP43
    {PB11, HAL_LL_TIM_INDEX_2, HAL_LL_CCP_CHANNEL_8, hal_ll_tim_module_num(CCP_MODULE_9)},
    #endif
    #ifdef PWM_CCP9_OC8_RB9_RP41
    {PB9, HAL_LL_TIM_INDEX_2, HAL_LL_CCP_CHANNEL_8, hal_ll_tim_module_num(CCP_MODULE_9)},
    #endif
    #ifdef PWM_CCP2_OC1_RB10_RP42
    {PB10, HAL_LL_TIM_INDEX_2, HAL_LL_CCP_CHANNEL_1, hal_ll_tim_module_num(CCP_MODULE_2)},
    #endif
    #ifdef PWM_CCP2_OC1_RB6_RP38
    {PB6, HAL_LL_TIM_INDEX_2, HAL_LL_CCP_CHANNEL_1, hal_ll_tim_module_num(CCP_MODULE_2)},
    #endif
    #ifdef PWM_CCP2_OC1_RB9_RP41
    {PB9, HAL_LL_TIM_INDEX_2, HAL_LL_CCP_CHANNEL_1, hal_ll_tim_module_num(CCP_MODULE_2)},
    #endif
    #ifdef PWM_CCP2_OC2_RB5_RP37
    {PB5, HAL_LL_TIM_INDEX_2, HAL_LL_CCP_CHANNEL_2, hal_ll_tim_module_num(CCP_MODULE_2)},
    #endif
    #ifdef PWM_CCP2_OC3_RB11_RP43
    {PB11, HAL_LL_TIM_INDEX_2, HAL_LL_CCP_CHANNEL_3, hal_ll_tim_module_num(CCP_MODULE_2)},
    #endif
    #ifdef PWM_CCP2_OC3_RB8_RP40
    {PB8, HAL_LL_TIM_INDEX_2, HAL_LL_CCP_CHANNEL_3, hal_ll_tim_module_num(CCP_MODULE_2)},
    #endif
    #ifdef PWM_CCP2_OC4_RB3_RP35
    {PB3, HAL_LL_TIM_INDEX_2, HAL_LL_CCP_CHANNEL_4, hal_ll_tim_module_num(CCP_MODULE_2)},
    #endif
    #ifdef PWM_CCP2_OC4_RB4_RP36
    {PB4, HAL_LL_TIM_INDEX_2, HAL_LL_CCP_CHANNEL_4, hal_ll_tim_module_num(CCP_MODULE_2)},
    #endif
    #ifdef PWM_CCP2_OC4_RB7_RP39
    {PB7, HAL_LL_TIM_INDEX_2, HAL_LL_CCP_CHANNEL_4, hal_ll_tim_module_num(CCP_MODULE_2)},
    #endif
    #ifdef PWM_CCP3_OC1_RA4_RP20
    {PA4, HAL_LL_TIM_INDEX_2, HAL_LL_CCP_CHANNEL_1, hal_ll_tim_module_num(CCP_MODULE_3)},
    #endif
    #ifdef PWM_CCP4_OC1_RB10_RP42
    {PB10, HAL_LL_TIM_INDEX_2, HAL_LL_CCP_CHANNEL_1, hal_ll_tim_module_num(CCP_MODULE_4)},
    #endif
    #ifdef PWM_CCP4_OC1_RB6_RP38
    {PB6, HAL_LL_TIM_INDEX_2, HAL_LL_CCP_CHANNEL_1, hal_ll_tim_module_num(CCP_MODULE_4)},
    #endif
    #ifdef PWM_CCP4_OC1_RB9_RP41
    {PB9, HAL_LL_TIM_INDEX_2, HAL_LL_CCP_CHANNEL_1, hal_ll_tim_module_num(CCP_MODULE_4)},
    #endif
    #ifdef PWM_CCP4_OC2_RB5_RP37
    {PB5, HAL_LL_TIM_INDEX_2, HAL_LL_CCP_CHANNEL_2, hal_ll_tim_module_num(CCP_MODULE_4)},
    #endif
    #ifdef PWM_CCP4_OC3_RB11_RP43
    {PB11, HAL_LL_TIM_INDEX_2, HAL_LL_CCP_CHANNEL_3, hal_ll_tim_module_num(CCP_MODULE_4)},
    #endif
    #ifdef PWM_CCP4_OC3_RB8_RP40
    {PB8, HAL_LL_TIM_INDEX_2, HAL_LL_CCP_CHANNEL_3, hal_ll_tim_module_num(CCP_MODULE_4)},
    #endif
    #ifdef PWM_CCP4_OC4_RB3_RP35
    {PB3, HAL_LL_TIM_INDEX_2, HAL_LL_CCP_CHANNEL_4, hal_ll_tim_module_num(CCP_MODULE_4)},
    #endif
    #ifdef PWM_CCP4_OC4_RB4_RP36
    {PB4, HAL_LL_TIM_INDEX_2, HAL_LL_CCP_CHANNEL_4, hal_ll_tim_module_num(CCP_MODULE_4)},
    #endif
    #ifdef PWM_CCP4_OC4_RB7_RP39
    {PB7, HAL_LL_TIM_INDEX_2, HAL_LL_CCP_CHANNEL_4, hal_ll_tim_module_num(CCP_MODULE_4)},
    #endif
    #ifdef PWM_CCP5_OC1_RA4_RP20
    {PA4, HAL_LL_TIM_INDEX_2, HAL_LL_CCP_CHANNEL_1, hal_ll_tim_module_num(CCP_MODULE_5)},
    #endif
    #ifdef PWM_CCP2_OC1_RB11_RP43
    {PB11, HAL_LL_TIM_INDEX_2, HAL_LL_CCP_CHANNEL_1, hal_ll_tim_module_num(CCP_MODULE_2)},
    #endif
    #ifdef PWM_CCP2_OC2_RB4_RP36
    {PB4, HAL_LL_TIM_INDEX_2, HAL_LL_CCP_CHANNEL_2, hal_ll_tim_module_num(CCP_MODULE_2)},
    #endif
    #ifdef PWM_CCP2_OC3_RB6_RP38
    {PB6, HAL_LL_TIM_INDEX_2, HAL_LL_CCP_CHANNEL_3, hal_ll_tim_module_num(CCP_MODULE_2)},
    #endif
    #ifdef PWM_CCP2_OC4_RB10_RP42
    {PB10, HAL_LL_TIM_INDEX_2, HAL_LL_CCP_CHANNEL_4, hal_ll_tim_module_num(CCP_MODULE_2)},
    #endif
    #ifdef PWM_CCP2_OC4_RB5_RP37
    {PB5, HAL_LL_TIM_INDEX_2, HAL_LL_CCP_CHANNEL_4, hal_ll_tim_module_num(CCP_MODULE_2)},
    #endif
    #ifdef PWM_CCP2_OC4_RB8_RP40
    {PB8, HAL_LL_TIM_INDEX_2, HAL_LL_CCP_CHANNEL_4, hal_ll_tim_module_num(CCP_MODULE_2)},
    #endif
    #ifdef PWM_CCP3_OC1_RC6_RP54
    {PC6, HAL_LL_TIM_INDEX_2, HAL_LL_CCP_CHANNEL_1, hal_ll_tim_module_num(CCP_MODULE_3)},
    #endif
    #ifdef PWM_CCP3_OC2_RC7_RP55
    {PC7, HAL_LL_TIM_INDEX_2, HAL_LL_CCP_CHANNEL_2, hal_ll_tim_module_num(CCP_MODULE_3)},
    #endif
    #ifdef PWM_CCP3_OC3_RC8_RP56
    {PC8, HAL_LL_TIM_INDEX_2, HAL_LL_CCP_CHANNEL_3, hal_ll_tim_module_num(CCP_MODULE_3)},
    #endif
    #ifdef PWM_CCP3_OC4_RC9_RP57
    {PC9, HAL_LL_TIM_INDEX_2, HAL_LL_CCP_CHANNEL_4, hal_ll_tim_module_num(CCP_MODULE_3)},
    #endif
    #ifdef PWM_CCP4_OC1_RA4_RP20
    {PA4, HAL_LL_TIM_INDEX_2, HAL_LL_CCP_CHANNEL_1, hal_ll_tim_module_num(CCP_MODULE_4)},
    #endif
    #ifdef PWM_CCP5_OC1_RB11_RP43
    {PB11, HAL_LL_TIM_INDEX_2, HAL_LL_CCP_CHANNEL_1, hal_ll_tim_module_num(CCP_MODULE_5)},
    #endif
    #ifdef PWM_CCP5_OC1_RB9_RP41
    {PB9, HAL_LL_TIM_INDEX_2, HAL_LL_CCP_CHANNEL_1, hal_ll_tim_module_num(CCP_MODULE_5)},
    #endif
    #ifdef PWM_CCP5_OC2_RB3_RP35
    {PB3, HAL_LL_TIM_INDEX_2, HAL_LL_CCP_CHANNEL_2, hal_ll_tim_module_num(CCP_MODULE_5)},
    #endif
    #ifdef PWM_CCP5_OC2_RB4_RP36
    {PB4, HAL_LL_TIM_INDEX_2, HAL_LL_CCP_CHANNEL_2, hal_ll_tim_module_num(CCP_MODULE_5)},
    #endif
    #ifdef PWM_CCP5_OC2_RB7_RP39
    {PB7, HAL_LL_TIM_INDEX_2, HAL_LL_CCP_CHANNEL_2, hal_ll_tim_module_num(CCP_MODULE_5)},
    #endif
    #ifdef PWM_CCP5_OC3_RB6_RP38
    {PB6, HAL_LL_TIM_INDEX_2, HAL_LL_CCP_CHANNEL_3, hal_ll_tim_module_num(CCP_MODULE_5)},
    #endif
    #ifdef PWM_CCP5_OC4_RB10_RP42
    {PB10, HAL_LL_TIM_INDEX_2, HAL_LL_CCP_CHANNEL_4, hal_ll_tim_module_num(CCP_MODULE_5)},
    #endif
    #ifdef PWM_CCP5_OC4_RB5_RP37
    {PB5, HAL_LL_TIM_INDEX_2, HAL_LL_CCP_CHANNEL_4, hal_ll_tim_module_num(CCP_MODULE_5)},
    #endif
    #ifdef PWM_CCP5_OC4_RB8_RP40
    {PB8, HAL_LL_TIM_INDEX_2, HAL_LL_CCP_CHANNEL_4, hal_ll_tim_module_num(CCP_MODULE_5)},
    #endif
    #ifdef PWM_CCP2_OC1_RB3_RP35
    {PB3, HAL_LL_TIM_INDEX_2, HAL_LL_CCP_CHANNEL_1, hal_ll_tim_module_num(CCP_MODULE_2)},
    #endif
    #ifdef PWM_CCP2_OC1_RB4_RP36
    {PB4, HAL_LL_TIM_INDEX_2, HAL_LL_CCP_CHANNEL_1, hal_ll_tim_module_num(CCP_MODULE_2)},
    #endif
    #ifdef PWM_CCP2_OC2_RB6_RP38
    {PB6, HAL_LL_TIM_INDEX_2, HAL_LL_CCP_CHANNEL_2, hal_ll_tim_module_num(CCP_MODULE_2)},
    #endif
    #ifdef PWM_CCP2_OC3_RB10_RP42
    {PB10, HAL_LL_TIM_INDEX_2, HAL_LL_CCP_CHANNEL_3, hal_ll_tim_module_num(CCP_MODULE_2)},
    #endif
    #ifdef PWM_CCP2_OC4_RB11_RP43
    {PB11, HAL_LL_TIM_INDEX_2, HAL_LL_CCP_CHANNEL_4, hal_ll_tim_module_num(CCP_MODULE_2)},
    #endif
    #ifdef PWM_CCP2_OC4_RB9_RP41
    {PB9, HAL_LL_TIM_INDEX_2, HAL_LL_CCP_CHANNEL_4, hal_ll_tim_module_num(CCP_MODULE_2)},
    #endif
    #ifdef PWM_CCP4_OC1_RF1_RP97
    {PF1, HAL_LL_TIM_INDEX_2, HAL_LL_CCP_CHANNEL_1, hal_ll_tim_module_num(CCP_MODULE_4)},
    #endif
    #ifdef PWM_CCP5_OC2_RG6_RP118
    {PG6, HAL_LL_TIM_INDEX_2, HAL_LL_CCP_CHANNEL_2, hal_ll_tim_module_num(CCP_MODULE_5)},
    #endif
    #ifdef PWM_CCP5_OC3_RG8_RP120
    {PG8, HAL_LL_TIM_INDEX_2, HAL_LL_CCP_CHANNEL_3, hal_ll_tim_module_num(CCP_MODULE_5)},
    #endif
    #ifdef PWM_CCP1_OC1_RA2_RP18
    {PA2, HAL_LL_TIM_INDEX_2, HAL_LL_CCP_CHANNEL_1, hal_ll_tim_module_num(CCP_MODULE_1)},
    #endif
    #ifdef PWM_CCP1_OC1_RA3_RP19
    {PA3, HAL_LL_TIM_INDEX_2, HAL_LL_CCP_CHANNEL_1, hal_ll_tim_module_num(CCP_MODULE_1)},
    #endif
    #ifdef PWM_CCP1_OC3_RA0_RP16
    {PA0, HAL_LL_TIM_INDEX_2, HAL_LL_CCP_CHANNEL_3, hal_ll_tim_module_num(CCP_MODULE_1)},
    #endif
    #ifdef PWM_CCP1_OC3_RA1_RP17
    {PA1, HAL_LL_TIM_INDEX_2, HAL_LL_CCP_CHANNEL_3, hal_ll_tim_module_num(CCP_MODULE_1)},
    #endif
    #ifdef PWM_CCP1_OC3_RA4_RP20
    {PA4, HAL_LL_TIM_INDEX_2, HAL_LL_CCP_CHANNEL_3, hal_ll_tim_module_num(CCP_MODULE_1)},
    #endif
    #ifdef PWM_CCP2_OC1_RB12_RP44
    {PB12, HAL_LL_TIM_INDEX_2, HAL_LL_CCP_CHANNEL_1, hal_ll_tim_module_num(CCP_MODULE_2)},
    #endif
    #ifdef PWM_CCP2_OC1_RB2_RP34
    {PB2, HAL_LL_TIM_INDEX_2, HAL_LL_CCP_CHANNEL_1, hal_ll_tim_module_num(CCP_MODULE_2)},
    #endif
    #ifdef PWM_CCP2_OC1_RB5_RP37
    {PB5, HAL_LL_TIM_INDEX_2, HAL_LL_CCP_CHANNEL_1, hal_ll_tim_module_num(CCP_MODULE_2)},
    #endif
    #ifdef PWM_CCP2_OC2_RB1_RP33
    {PB1, HAL_LL_TIM_INDEX_2, HAL_LL_CCP_CHANNEL_2, hal_ll_tim_module_num(CCP_MODULE_2)},
    #endif
    #ifdef PWM_CCP2_OC2_RB11_RP43
    {PB11, HAL_LL_TIM_INDEX_2, HAL_LL_CCP_CHANNEL_2, hal_ll_tim_module_num(CCP_MODULE_2)},
    #endif
    #ifdef PWM_CCP2_OC2_RB14_RP46
    {PB14, HAL_LL_TIM_INDEX_2, HAL_LL_CCP_CHANNEL_2, hal_ll_tim_module_num(CCP_MODULE_2)},
    #endif
    #ifdef PWM_CCP2_OC2_RB15_RP47
    {PB15, HAL_LL_TIM_INDEX_2, HAL_LL_CCP_CHANNEL_2, hal_ll_tim_module_num(CCP_MODULE_2)},
    #endif
    #ifdef PWM_CCP2_OC2_RB8_RP40
    {PB8, HAL_LL_TIM_INDEX_2, HAL_LL_CCP_CHANNEL_2, hal_ll_tim_module_num(CCP_MODULE_2)},
    #endif
    #ifdef PWM_CCP2_OC4_RB0_RP32
    {PB0, HAL_LL_TIM_INDEX_2, HAL_LL_CCP_CHANNEL_4, hal_ll_tim_module_num(CCP_MODULE_2)},
    #endif
    #ifdef PWM_CCP2_OC4_RB13_RP45
    {PB13, HAL_LL_TIM_INDEX_2, HAL_LL_CCP_CHANNEL_4, hal_ll_tim_module_num(CCP_MODULE_2)},
    #endif
    #ifdef PWM_CCP3_OC2_RA0_RP16
    {PA0, HAL_LL_TIM_INDEX_2, HAL_LL_CCP_CHANNEL_2, hal_ll_tim_module_num(CCP_MODULE_3)},
    #endif
    #ifdef PWM_CCP3_OC2_RA1_RP17
    {PA1, HAL_LL_TIM_INDEX_2, HAL_LL_CCP_CHANNEL_2, hal_ll_tim_module_num(CCP_MODULE_3)},
    #endif
    #ifdef PWM_CCP3_OC2_RA4_RP20
    {PA4, HAL_LL_TIM_INDEX_2, HAL_LL_CCP_CHANNEL_2, hal_ll_tim_module_num(CCP_MODULE_3)},
    #endif
    #ifdef PWM_CCP3_OC4_RA2_RP18
    {PA2, HAL_LL_TIM_INDEX_2, HAL_LL_CCP_CHANNEL_4, hal_ll_tim_module_num(CCP_MODULE_3)},
    #endif
    #ifdef PWM_CCP3_OC4_RA3_RP19
    {PA3, HAL_LL_TIM_INDEX_2, HAL_LL_CCP_CHANNEL_4, hal_ll_tim_module_num(CCP_MODULE_3)},
    #endif
    #ifdef PWM_CCP4_OC1_RB1_RP33
    {PB1, HAL_LL_TIM_INDEX_2, HAL_LL_CCP_CHANNEL_1, hal_ll_tim_module_num(CCP_MODULE_4)},
    #endif
    #ifdef PWM_CCP4_OC1_RB11_RP43
    {PB11, HAL_LL_TIM_INDEX_2, HAL_LL_CCP_CHANNEL_1, hal_ll_tim_module_num(CCP_MODULE_4)},
    #endif
    #ifdef PWM_CCP4_OC1_RB14_RP46
    {PB14, HAL_LL_TIM_INDEX_2, HAL_LL_CCP_CHANNEL_1, hal_ll_tim_module_num(CCP_MODULE_4)},
    #endif
    #ifdef PWM_CCP4_OC1_RB15_RP47
    {PB15, HAL_LL_TIM_INDEX_2, HAL_LL_CCP_CHANNEL_1, hal_ll_tim_module_num(CCP_MODULE_4)},
    #endif
    #ifdef PWM_CCP4_OC1_RB4_RP36
    {PB4, HAL_LL_TIM_INDEX_2, HAL_LL_CCP_CHANNEL_1, hal_ll_tim_module_num(CCP_MODULE_4)},
    #endif
    #ifdef PWM_CCP4_OC1_RB7_RP39
    {PB7, HAL_LL_TIM_INDEX_2, HAL_LL_CCP_CHANNEL_1, hal_ll_tim_module_num(CCP_MODULE_4)},
    #endif
    #ifdef PWM_CCP4_OC1_RB8_RP40
    {PB8, HAL_LL_TIM_INDEX_2, HAL_LL_CCP_CHANNEL_1, hal_ll_tim_module_num(CCP_MODULE_4)},
    #endif
    #ifdef PWM_CCP4_OC3_RB0_RP32
    {PB0, HAL_LL_TIM_INDEX_2, HAL_LL_CCP_CHANNEL_3, hal_ll_tim_module_num(CCP_MODULE_4)},
    #endif
    #ifdef PWM_CCP4_OC3_RB13_RP45
    {PB13, HAL_LL_TIM_INDEX_2, HAL_LL_CCP_CHANNEL_3, hal_ll_tim_module_num(CCP_MODULE_4)},
    #endif
    #ifdef PWM_CCP4_OC3_RB3_RP35
    {PB3, HAL_LL_TIM_INDEX_2, HAL_LL_CCP_CHANNEL_3, hal_ll_tim_module_num(CCP_MODULE_4)},
    #endif
    #ifdef PWM_CCP4_OC4_RB12_RP44
    {PB12, HAL_LL_TIM_INDEX_2, HAL_LL_CCP_CHANNEL_4, hal_ll_tim_module_num(CCP_MODULE_4)},
    #endif
    #ifdef PWM_CCP4_OC4_RB2_RP34
    {PB2, HAL_LL_TIM_INDEX_2, HAL_LL_CCP_CHANNEL_4, hal_ll_tim_module_num(CCP_MODULE_4)},
    #endif
    #ifdef PWM_CCP4_OC4_RB5_RP37
    {PB5, HAL_LL_TIM_INDEX_2, HAL_LL_CCP_CHANNEL_4, hal_ll_tim_module_num(CCP_MODULE_4)},
    #endif
    #ifdef PWM_CCP4_OC4_RB6_RP38
    {PB6, HAL_LL_TIM_INDEX_2, HAL_LL_CCP_CHANNEL_4, hal_ll_tim_module_num(CCP_MODULE_4)},
    #endif
    #ifdef PWM_CCP4_OC4_RB9_RP41
    {PB9, HAL_LL_TIM_INDEX_2, HAL_LL_CCP_CHANNEL_4, hal_ll_tim_module_num(CCP_MODULE_4)},
    #endif
    #ifdef PWM_CCP5_OC1_RA0_RP16
    {PA0, HAL_LL_TIM_INDEX_2, HAL_LL_CCP_CHANNEL_1, hal_ll_tim_module_num(CCP_MODULE_5)},
    #endif
    #ifdef PWM_CCP5_OC1_RA1_RP17
    {PA1, HAL_LL_TIM_INDEX_2, HAL_LL_CCP_CHANNEL_1, hal_ll_tim_module_num(CCP_MODULE_5)},
    #endif
    #ifdef PWM_CCP5_OC3_RA2_RP18
    {PA2, HAL_LL_TIM_INDEX_2, HAL_LL_CCP_CHANNEL_3, hal_ll_tim_module_num(CCP_MODULE_5)},
    #endif
    #ifdef PWM_CCP5_OC3_RA3_RP19
    {PA3, HAL_LL_TIM_INDEX_2, HAL_LL_CCP_CHANNEL_3, hal_ll_tim_module_num(CCP_MODULE_5)},
    #endif
    #ifdef PWM_CCP1_OC1_RA0_RP16
    {PA0, HAL_LL_TIM_INDEX_2, HAL_LL_CCP_CHANNEL_1, hal_ll_tim_module_num(CCP_MODULE_1)},
    #endif
    #ifdef PWM_CCP1_OC1_RA1_RP17
    {PA1, HAL_LL_TIM_INDEX_2, HAL_LL_CCP_CHANNEL_1, hal_ll_tim_module_num(CCP_MODULE_1)},
    #endif
    #ifdef PWM_CCP1_OC2_RA2_RP18
    {PA2, HAL_LL_TIM_INDEX_2, HAL_LL_CCP_CHANNEL_2, hal_ll_tim_module_num(CCP_MODULE_1)},
    #endif
    #ifdef PWM_CCP1_OC3_RA3_RP19
    {PA3, HAL_LL_TIM_INDEX_2, HAL_LL_CCP_CHANNEL_3, hal_ll_tim_module_num(CCP_MODULE_1)},
    #endif
    #ifdef PWM_CCP2_OC2_RB0_RP32
    {PB0, HAL_LL_TIM_INDEX_2, HAL_LL_CCP_CHANNEL_2, hal_ll_tim_module_num(CCP_MODULE_2)},
    #endif
    #ifdef PWM_CCP2_OC2_RB13_RP45
    {PB13, HAL_LL_TIM_INDEX_2, HAL_LL_CCP_CHANNEL_2, hal_ll_tim_module_num(CCP_MODULE_2)},
    #endif
    #ifdef PWM_CCP2_OC3_RB12_RP44
    {PB12, HAL_LL_TIM_INDEX_2, HAL_LL_CCP_CHANNEL_3, hal_ll_tim_module_num(CCP_MODULE_2)},
    #endif
    #ifdef PWM_CCP2_OC3_RB15_RP47
    {PB15, HAL_LL_TIM_INDEX_2, HAL_LL_CCP_CHANNEL_3, hal_ll_tim_module_num(CCP_MODULE_2)},
    #endif
    #ifdef PWM_CCP2_OC3_RB2_RP34
    {PB2, HAL_LL_TIM_INDEX_2, HAL_LL_CCP_CHANNEL_3, hal_ll_tim_module_num(CCP_MODULE_2)},
    #endif
    #ifdef PWM_CCP2_OC3_RB9_RP41
    {PB9, HAL_LL_TIM_INDEX_2, HAL_LL_CCP_CHANNEL_3, hal_ll_tim_module_num(CCP_MODULE_2)},
    #endif
    #ifdef PWM_CCP2_OC4_RB1_RP33
    {PB1, HAL_LL_TIM_INDEX_2, HAL_LL_CCP_CHANNEL_4, hal_ll_tim_module_num(CCP_MODULE_2)},
    #endif
    #ifdef PWM_CCP2_OC4_RB14_RP46
    {PB14, HAL_LL_TIM_INDEX_2, HAL_LL_CCP_CHANNEL_4, hal_ll_tim_module_num(CCP_MODULE_2)},
    #endif
    #ifdef PWM_CCP3_OC1_RC3_RP51
    {PC3, HAL_LL_TIM_INDEX_2, HAL_LL_CCP_CHANNEL_1, hal_ll_tim_module_num(CCP_MODULE_3)},
    #endif
    #ifdef PWM_CCP3_OC1_RC5_RP53
    {PC5, HAL_LL_TIM_INDEX_2, HAL_LL_CCP_CHANNEL_1, hal_ll_tim_module_num(CCP_MODULE_3)},
    #endif
    #ifdef PWM_CCP3_OC2_RC0_RP48
    {PC0, HAL_LL_TIM_INDEX_2, HAL_LL_CCP_CHANNEL_2, hal_ll_tim_module_num(CCP_MODULE_3)},
    #endif
    #ifdef PWM_CCP3_OC2_RC12_RP60
    {PC12, HAL_LL_TIM_INDEX_2, HAL_LL_CCP_CHANNEL_2, hal_ll_tim_module_num(CCP_MODULE_3)},
    #endif
    #ifdef PWM_CCP3_OC2_RC8_RP56
    {PC8, HAL_LL_TIM_INDEX_2, HAL_LL_CCP_CHANNEL_2, hal_ll_tim_module_num(CCP_MODULE_3)},
    #endif
    #ifdef PWM_CCP3_OC3_RC4_RP52
    {PC4, HAL_LL_TIM_INDEX_2, HAL_LL_CCP_CHANNEL_3, hal_ll_tim_module_num(CCP_MODULE_3)},
    #endif
    #ifdef PWM_CCP3_OC4_RC1_RP49
    {PC1, HAL_LL_TIM_INDEX_2, HAL_LL_CCP_CHANNEL_4, hal_ll_tim_module_num(CCP_MODULE_3)},
    #endif
    #ifdef PWM_CCP3_OC4_RC10_RP58
    {PC10, HAL_LL_TIM_INDEX_2, HAL_LL_CCP_CHANNEL_4, hal_ll_tim_module_num(CCP_MODULE_3)},
    #endif
    #ifdef PWM_CCP3_OC4_RC13_RP61
    {PC13, HAL_LL_TIM_INDEX_2, HAL_LL_CCP_CHANNEL_4, hal_ll_tim_module_num(CCP_MODULE_3)},
    #endif
    #ifdef PWM_CCP3_OC4_RC2_RP50
    {PC2, HAL_LL_TIM_INDEX_2, HAL_LL_CCP_CHANNEL_4, hal_ll_tim_module_num(CCP_MODULE_3)},
    #endif
    #ifdef PWM_CCP3_OC4_RC7_RP55
    {PC7, HAL_LL_TIM_INDEX_2, HAL_LL_CCP_CHANNEL_4, hal_ll_tim_module_num(CCP_MODULE_3)},
    #endif
    #ifdef PWM_CCP4_OC1_RA2_RP18
    {PA2, HAL_LL_TIM_INDEX_2, HAL_LL_CCP_CHANNEL_1, hal_ll_tim_module_num(CCP_MODULE_4)},
    #endif
    #ifdef PWM_CCP4_OC2_RA3_RP19
    {PA3, HAL_LL_TIM_INDEX_2, HAL_LL_CCP_CHANNEL_2, hal_ll_tim_module_num(CCP_MODULE_4)},
    #endif
    #ifdef PWM_CCP4_OC4_RA0_RP16
    {PA0, HAL_LL_TIM_INDEX_2, HAL_LL_CCP_CHANNEL_4, hal_ll_tim_module_num(CCP_MODULE_4)},
    #endif
    #ifdef PWM_CCP4_OC4_RA1_RP17
    {PA1, HAL_LL_TIM_INDEX_2, HAL_LL_CCP_CHANNEL_4, hal_ll_tim_module_num(CCP_MODULE_4)},
    #endif
    #ifdef PWM_CCP4_OC4_RA4_RP20
    {PA4, HAL_LL_TIM_INDEX_2, HAL_LL_CCP_CHANNEL_4, hal_ll_tim_module_num(CCP_MODULE_4)},
    #endif
    #ifdef PWM_CCP5_OC1_RB0_RP32
    {PB0, HAL_LL_TIM_INDEX_2, HAL_LL_CCP_CHANNEL_1, hal_ll_tim_module_num(CCP_MODULE_5)},
    #endif
    #ifdef PWM_CCP5_OC1_RB13_RP45
    {PB13, HAL_LL_TIM_INDEX_2, HAL_LL_CCP_CHANNEL_1, hal_ll_tim_module_num(CCP_MODULE_5)},
    #endif
    #ifdef PWM_CCP5_OC1_RB5_RP37
    {PB5, HAL_LL_TIM_INDEX_2, HAL_LL_CCP_CHANNEL_1, hal_ll_tim_module_num(CCP_MODULE_5)},
    #endif
    #ifdef PWM_CCP5_OC1_RB6_RP38
    {PB6, HAL_LL_TIM_INDEX_2, HAL_LL_CCP_CHANNEL_1, hal_ll_tim_module_num(CCP_MODULE_5)},
    #endif
    #ifdef PWM_CCP5_OC2_RB12_RP44
    {PB12, HAL_LL_TIM_INDEX_2, HAL_LL_CCP_CHANNEL_2, hal_ll_tim_module_num(CCP_MODULE_5)},
    #endif
    #ifdef PWM_CCP5_OC2_RB15_RP47
    {PB15, HAL_LL_TIM_INDEX_2, HAL_LL_CCP_CHANNEL_2, hal_ll_tim_module_num(CCP_MODULE_5)},
    #endif
    #ifdef PWM_CCP5_OC2_RB2_RP34
    {PB2, HAL_LL_TIM_INDEX_2, HAL_LL_CCP_CHANNEL_2, hal_ll_tim_module_num(CCP_MODULE_5)},
    #endif
    #ifdef PWM_CCP5_OC2_RB8_RP40
    {PB8, HAL_LL_TIM_INDEX_2, HAL_LL_CCP_CHANNEL_2, hal_ll_tim_module_num(CCP_MODULE_5)},
    #endif
    #ifdef PWM_CCP5_OC2_RB9_RP41
    {PB9, HAL_LL_TIM_INDEX_2, HAL_LL_CCP_CHANNEL_2, hal_ll_tim_module_num(CCP_MODULE_5)},
    #endif
    #ifdef PWM_CCP5_OC3_RB1_RP33
    {PB1, HAL_LL_TIM_INDEX_2, HAL_LL_CCP_CHANNEL_3, hal_ll_tim_module_num(CCP_MODULE_5)},
    #endif
    #ifdef PWM_CCP5_OC3_RB11_RP43
    {PB11, HAL_LL_TIM_INDEX_2, HAL_LL_CCP_CHANNEL_3, hal_ll_tim_module_num(CCP_MODULE_5)},
    #endif
    #ifdef PWM_CCP5_OC3_RB14_RP46
    {PB14, HAL_LL_TIM_INDEX_2, HAL_LL_CCP_CHANNEL_3, hal_ll_tim_module_num(CCP_MODULE_5)},
    #endif
    #ifdef PWM_CCP5_OC3_RB4_RP36
    {PB4, HAL_LL_TIM_INDEX_2, HAL_LL_CCP_CHANNEL_3, hal_ll_tim_module_num(CCP_MODULE_5)},
    #endif
    #ifdef PWM_CCP5_OC3_RB7_RP39
    {PB7, HAL_LL_TIM_INDEX_2, HAL_LL_CCP_CHANNEL_3, hal_ll_tim_module_num(CCP_MODULE_5)},
    #endif
    #ifdef PWM_CCP4_OC1_RD10_RP74
    {PD10, HAL_LL_TIM_INDEX_2, HAL_LL_CCP_CHANNEL_1, hal_ll_tim_module_num(CCP_MODULE_4)},
    #endif
    #ifdef PWM_CCP4_OC4_RD4_RP68
    {PD4, HAL_LL_TIM_INDEX_2, HAL_LL_CCP_CHANNEL_4, hal_ll_tim_module_num(CCP_MODULE_4)},
    #endif
    #ifdef PWM_CCP5_OC1_RA2_RP18
    {PA2, HAL_LL_TIM_INDEX_2, HAL_LL_CCP_CHANNEL_1, hal_ll_tim_module_num(CCP_MODULE_5)},
    #endif
    #ifdef PWM_CCP5_OC2_RA3_RP19
    {PA3, HAL_LL_TIM_INDEX_2, HAL_LL_CCP_CHANNEL_2, hal_ll_tim_module_num(CCP_MODULE_5)},
    #endif
    #ifdef PWM_CCP5_OC4_RA0_RP16
    {PA0, HAL_LL_TIM_INDEX_2, HAL_LL_CCP_CHANNEL_4, hal_ll_tim_module_num(CCP_MODULE_5)},
    #endif
    #ifdef PWM_CCP5_OC4_RA1_RP17
    {PA1, HAL_LL_TIM_INDEX_2, HAL_LL_CCP_CHANNEL_4, hal_ll_tim_module_num(CCP_MODULE_5)},
    #endif
    #ifdef PWM_CCP5_OC4_RA4_RP20
    {PA4, HAL_LL_TIM_INDEX_2, HAL_LL_CCP_CHANNEL_4, hal_ll_tim_module_num(CCP_MODULE_5)},
    #endif
    #ifdef PWM_CCP2_OC1_RB14_RP46
    {PB14, HAL_LL_TIM_INDEX_2, HAL_LL_CCP_CHANNEL_1, hal_ll_tim_module_num(CCP_MODULE_2)},
    #endif
    #ifdef PWM_CCP2_OC1_RB15_RP47
    {PB15, HAL_LL_TIM_INDEX_2, HAL_LL_CCP_CHANNEL_1, hal_ll_tim_module_num(CCP_MODULE_2)},
    #endif
    #ifdef PWM_CCP2_OC1_RB8_RP40
    {PB8, HAL_LL_TIM_INDEX_2, HAL_LL_CCP_CHANNEL_1, hal_ll_tim_module_num(CCP_MODULE_2)},
    #endif
    #ifdef PWM_CCP2_OC3_RB13_RP45
    {PB13, HAL_LL_TIM_INDEX_2, HAL_LL_CCP_CHANNEL_3, hal_ll_tim_module_num(CCP_MODULE_2)},
    #endif
    #ifdef PWM_CCP2_OC4_RB12_RP44
    {PB12, HAL_LL_TIM_INDEX_2, HAL_LL_CCP_CHANNEL_4, hal_ll_tim_module_num(CCP_MODULE_2)},
    #endif
    #ifdef PWM_CCP2_OC4_RB6_RP38
    {PB6, HAL_LL_TIM_INDEX_2, HAL_LL_CCP_CHANNEL_4, hal_ll_tim_module_num(CCP_MODULE_2)},
    #endif
    #ifdef PWM_CCP3_OC1_RC1_RP49
    {PC1, HAL_LL_TIM_INDEX_2, HAL_LL_CCP_CHANNEL_1, hal_ll_tim_module_num(CCP_MODULE_3)},
    #endif
    #ifdef PWM_CCP3_OC1_RC10_RP58
    {PC10, HAL_LL_TIM_INDEX_2, HAL_LL_CCP_CHANNEL_1, hal_ll_tim_module_num(CCP_MODULE_3)},
    #endif
    #ifdef PWM_CCP3_OC1_RC13_RP61
    {PC13, HAL_LL_TIM_INDEX_2, HAL_LL_CCP_CHANNEL_1, hal_ll_tim_module_num(CCP_MODULE_3)},
    #endif
    #ifdef PWM_CCP3_OC1_RC15_RP63
    {PC15, HAL_LL_TIM_INDEX_2, HAL_LL_CCP_CHANNEL_1, hal_ll_tim_module_num(CCP_MODULE_3)},
    #endif
    #ifdef PWM_CCP3_OC2_RC3_RP51
    {PC3, HAL_LL_TIM_INDEX_2, HAL_LL_CCP_CHANNEL_2, hal_ll_tim_module_num(CCP_MODULE_3)},
    #endif
    #ifdef PWM_CCP3_OC2_RC5_RP53
    {PC5, HAL_LL_TIM_INDEX_2, HAL_LL_CCP_CHANNEL_2, hal_ll_tim_module_num(CCP_MODULE_3)},
    #endif
    #ifdef PWM_CCP3_OC3_RC0_RP48
    {PC0, HAL_LL_TIM_INDEX_2, HAL_LL_CCP_CHANNEL_3, hal_ll_tim_module_num(CCP_MODULE_3)},
    #endif
    #ifdef PWM_CCP3_OC3_RC12_RP60
    {PC12, HAL_LL_TIM_INDEX_2, HAL_LL_CCP_CHANNEL_3, hal_ll_tim_module_num(CCP_MODULE_3)},
    #endif
    #ifdef PWM_CCP3_OC3_RC14_RP62
    {PC14, HAL_LL_TIM_INDEX_2, HAL_LL_CCP_CHANNEL_3, hal_ll_tim_module_num(CCP_MODULE_3)},
    #endif
    #ifdef PWM_CCP3_OC4_RC4_RP52
    {PC4, HAL_LL_TIM_INDEX_2, HAL_LL_CCP_CHANNEL_4, hal_ll_tim_module_num(CCP_MODULE_3)},
    #endif
    #ifdef PWM_CCP4_OC1_RD0_RP64
    {PD0, HAL_LL_TIM_INDEX_2, HAL_LL_CCP_CHANNEL_1, hal_ll_tim_module_num(CCP_MODULE_4)},
    #endif
    #ifdef PWM_CCP4_OC1_RD12_RP76
    {PD12, HAL_LL_TIM_INDEX_2, HAL_LL_CCP_CHANNEL_1, hal_ll_tim_module_num(CCP_MODULE_4)},
    #endif
    #ifdef PWM_CCP4_OC2_RD1_RP65
    {PD1, HAL_LL_TIM_INDEX_2, HAL_LL_CCP_CHANNEL_2, hal_ll_tim_module_num(CCP_MODULE_4)},
    #endif
    #ifdef PWM_CCP4_OC2_RD10_RP74
    {PD10, HAL_LL_TIM_INDEX_2, HAL_LL_CCP_CHANNEL_2, hal_ll_tim_module_num(CCP_MODULE_4)},
    #endif
    #ifdef PWM_CCP4_OC2_RD2_RP66
    {PD2, HAL_LL_TIM_INDEX_2, HAL_LL_CCP_CHANNEL_2, hal_ll_tim_module_num(CCP_MODULE_4)},
    #endif
    #ifdef PWM_CCP4_OC2_RD6_RP70
    {PD6, HAL_LL_TIM_INDEX_2, HAL_LL_CCP_CHANNEL_2, hal_ll_tim_module_num(CCP_MODULE_4)},
    #endif
    #ifdef PWM_CCP4_OC2_RD8_RP72
    {PD8, HAL_LL_TIM_INDEX_2, HAL_LL_CCP_CHANNEL_2, hal_ll_tim_module_num(CCP_MODULE_4)},
    #endif
    #ifdef PWM_CCP4_OC3_RD11_RP75
    {PD11, HAL_LL_TIM_INDEX_2, HAL_LL_CCP_CHANNEL_3, hal_ll_tim_module_num(CCP_MODULE_4)},
    #endif
    #ifdef PWM_CCP4_OC3_RD5_RP69
    {PD5, HAL_LL_TIM_INDEX_2, HAL_LL_CCP_CHANNEL_3, hal_ll_tim_module_num(CCP_MODULE_4)},
    #endif
    #ifdef PWM_CCP4_OC4_RD3_RP67
    {PD3, HAL_LL_TIM_INDEX_2, HAL_LL_CCP_CHANNEL_4, hal_ll_tim_module_num(CCP_MODULE_4)},
    #endif
    #ifdef PWM_CCP4_OC4_RD7_RP71
    {PD7, HAL_LL_TIM_INDEX_2, HAL_LL_CCP_CHANNEL_4, hal_ll_tim_module_num(CCP_MODULE_4)},
    #endif
    #ifdef PWM_CCP4_OC4_RD9_RP73
    {PD9, HAL_LL_TIM_INDEX_2, HAL_LL_CCP_CHANNEL_4, hal_ll_tim_module_num(CCP_MODULE_4)},
    #endif
    #ifdef PWM_CCP2_OC2_RB9_RP41
    {PB9, HAL_LL_TIM_INDEX_2, HAL_LL_CCP_CHANNEL_2, hal_ll_tim_module_num(CCP_MODULE_2)},
    #endif
    #ifdef PWM_CCP3_OC4_RA4_RP20
    {PA4, HAL_LL_TIM_INDEX_2, HAL_LL_CCP_CHANNEL_4, hal_ll_tim_module_num(CCP_MODULE_3)},
    #endif
    #ifdef PWM_CCP4_OC3_RB4_RP36
    {PB4, HAL_LL_TIM_INDEX_2, HAL_LL_CCP_CHANNEL_3, hal_ll_tim_module_num(CCP_MODULE_4)},
    #endif
    #ifdef PWM_CCP4_OC4_RB11_RP43
    {PB11, HAL_LL_TIM_INDEX_2, HAL_LL_CCP_CHANNEL_4, hal_ll_tim_module_num(CCP_MODULE_4)},
    #endif
    #ifdef PWM_CCP5_OC3_RA4_RP20
    {PA4, HAL_LL_TIM_INDEX_2, HAL_LL_CCP_CHANNEL_3, hal_ll_tim_module_num(CCP_MODULE_5)},
    #endif
    #ifdef PWM_CCP3_OC1_RC7_RP55
    {PC7, HAL_LL_TIM_INDEX_2, HAL_LL_CCP_CHANNEL_1, hal_ll_tim_module_num(CCP_MODULE_3)},
    #endif
    #ifdef PWM_CCP5_OC3_RB10_RP42
    {PB10, HAL_LL_TIM_INDEX_2, HAL_LL_CCP_CHANNEL_3, hal_ll_tim_module_num(CCP_MODULE_5)},
    #endif
    #ifdef PWM_CCP5_OC3_RB3_RP35
    {PB3, HAL_LL_TIM_INDEX_2, HAL_LL_CCP_CHANNEL_3, hal_ll_tim_module_num(CCP_MODULE_5)},
    #endif
    #ifdef PWM_CCP5_OC4_RB7_RP39
    {PB7, HAL_LL_TIM_INDEX_2, HAL_LL_CCP_CHANNEL_4, hal_ll_tim_module_num(CCP_MODULE_5)},
    #endif
    #ifdef PWM_CCP5_OC4_RB9_RP41
    {PB9, HAL_LL_TIM_INDEX_2, HAL_LL_CCP_CHANNEL_4, hal_ll_tim_module_num(CCP_MODULE_5)},
    #endif
    #ifdef PWM_CCP4_OC4_RF1_RP97
    {PF1, HAL_LL_TIM_INDEX_2, HAL_LL_CCP_CHANNEL_4, hal_ll_tim_module_num(CCP_MODULE_4)},
    #endif
    #ifdef PWM_CCP5_OC1_RG6_RP118
    {PG6, HAL_LL_TIM_INDEX_2, HAL_LL_CCP_CHANNEL_1, hal_ll_tim_module_num(CCP_MODULE_5)},
    #endif
    #ifdef PWM_CCP5_OC2_RG8_RP120
    {PG8, HAL_LL_TIM_INDEX_2, HAL_LL_CCP_CHANNEL_2, hal_ll_tim_module_num(CCP_MODULE_5)},
    #endif
    #ifdef PWM_CCP1_OC1_RB0_RP32
    {PB0, HAL_LL_TIM_INDEX_2, HAL_LL_CCP_CHANNEL_1, hal_ll_tim_module_num(CCP_MODULE_1)},
    #endif
    #ifdef PWM_CCP1_OC1_RB1_RP33
    {PB1, HAL_LL_TIM_INDEX_2, HAL_LL_CCP_CHANNEL_1, hal_ll_tim_module_num(CCP_MODULE_1)},
    #endif
    #ifdef PWM_CCP1_OC1_RB10_RP42
    {PB10, HAL_LL_TIM_INDEX_2, HAL_LL_CCP_CHANNEL_1, hal_ll_tim_module_num(CCP_MODULE_1)},
    #endif
    #ifdef PWM_CCP1_OC1_RB11_RP43
    {PB11, HAL_LL_TIM_INDEX_2, HAL_LL_CCP_CHANNEL_1, hal_ll_tim_module_num(CCP_MODULE_1)},
    #endif
    #ifdef PWM_CCP1_OC1_RB12_RP44
    {PB12, HAL_LL_TIM_INDEX_2, HAL_LL_CCP_CHANNEL_1, hal_ll_tim_module_num(CCP_MODULE_1)},
    #endif
    #ifdef PWM_CCP1_OC1_RB13_RP45
    {PB13, HAL_LL_TIM_INDEX_2, HAL_LL_CCP_CHANNEL_1, hal_ll_tim_module_num(CCP_MODULE_1)},
    #endif
    #ifdef PWM_CCP1_OC1_RB14_RP46
    {PB14, HAL_LL_TIM_INDEX_2, HAL_LL_CCP_CHANNEL_1, hal_ll_tim_module_num(CCP_MODULE_1)},
    #endif
    #ifdef PWM_CCP1_OC1_RB15_RP47
    {PB15, HAL_LL_TIM_INDEX_2, HAL_LL_CCP_CHANNEL_1, hal_ll_tim_module_num(CCP_MODULE_1)},
    #endif
    #ifdef PWM_CCP1_OC1_RB2_RP34
    {PB2, HAL_LL_TIM_INDEX_2, HAL_LL_CCP_CHANNEL_1, hal_ll_tim_module_num(CCP_MODULE_1)},
    #endif
    #ifdef PWM_CCP1_OC1_RB3_RP35
    {PB3, HAL_LL_TIM_INDEX_2, HAL_LL_CCP_CHANNEL_1, hal_ll_tim_module_num(CCP_MODULE_1)},
    #endif
    #ifdef PWM_CCP1_OC1_RB4_RP36
    {PB4, HAL_LL_TIM_INDEX_2, HAL_LL_CCP_CHANNEL_1, hal_ll_tim_module_num(CCP_MODULE_1)},
    #endif
    #ifdef PWM_CCP1_OC1_RB5_RP37
    {PB5, HAL_LL_TIM_INDEX_2, HAL_LL_CCP_CHANNEL_1, hal_ll_tim_module_num(CCP_MODULE_1)},
    #endif
    #ifdef PWM_CCP1_OC1_RB6_RP38
    {PB6, HAL_LL_TIM_INDEX_2, HAL_LL_CCP_CHANNEL_1, hal_ll_tim_module_num(CCP_MODULE_1)},
    #endif
    #ifdef PWM_CCP1_OC1_RB7_RP39
    {PB7, HAL_LL_TIM_INDEX_2, HAL_LL_CCP_CHANNEL_1, hal_ll_tim_module_num(CCP_MODULE_1)},
    #endif
    #ifdef PWM_CCP1_OC1_RB8_RP40
    {PB8, HAL_LL_TIM_INDEX_2, HAL_LL_CCP_CHANNEL_1, hal_ll_tim_module_num(CCP_MODULE_1)},
    #endif
    #ifdef PWM_CCP1_OC1_RB9_RP41
    {PB9, HAL_LL_TIM_INDEX_2, HAL_LL_CCP_CHANNEL_1, hal_ll_tim_module_num(CCP_MODULE_1)},
    #endif
    #ifdef PWM_CCP2_OC1_RB0_RP32
    {PB0, HAL_LL_TIM_INDEX_2, HAL_LL_CCP_CHANNEL_1, hal_ll_tim_module_num(CCP_MODULE_2)},
    #endif
    #ifdef PWM_CCP2_OC1_RB1_RP33
    {PB1, HAL_LL_TIM_INDEX_2, HAL_LL_CCP_CHANNEL_1, hal_ll_tim_module_num(CCP_MODULE_2)},
    #endif
    #ifdef PWM_CCP2_OC1_RB13_RP45
    {PB13, HAL_LL_TIM_INDEX_2, HAL_LL_CCP_CHANNEL_1, hal_ll_tim_module_num(CCP_MODULE_2)},
    #endif
    #ifdef PWM_CCP3_OC1_RB0_RP32
    {PB0, HAL_LL_TIM_INDEX_2, HAL_LL_CCP_CHANNEL_1, hal_ll_tim_module_num(CCP_MODULE_3)},
    #endif
    #ifdef PWM_CCP3_OC1_RB1_RP33
    {PB1, HAL_LL_TIM_INDEX_2, HAL_LL_CCP_CHANNEL_1, hal_ll_tim_module_num(CCP_MODULE_3)},
    #endif
    #ifdef PWM_CCP3_OC1_RB10_RP42
    {PB10, HAL_LL_TIM_INDEX_2, HAL_LL_CCP_CHANNEL_1, hal_ll_tim_module_num(CCP_MODULE_3)},
    #endif
    #ifdef PWM_CCP3_OC1_RB11_RP43
    {PB11, HAL_LL_TIM_INDEX_2, HAL_LL_CCP_CHANNEL_1, hal_ll_tim_module_num(CCP_MODULE_3)},
    #endif
    #ifdef PWM_CCP3_OC1_RB12_RP44
    {PB12, HAL_LL_TIM_INDEX_2, HAL_LL_CCP_CHANNEL_1, hal_ll_tim_module_num(CCP_MODULE_3)},
    #endif
    #ifdef PWM_CCP3_OC1_RB13_RP45
    {PB13, HAL_LL_TIM_INDEX_2, HAL_LL_CCP_CHANNEL_1, hal_ll_tim_module_num(CCP_MODULE_3)},
    #endif
    #ifdef PWM_CCP3_OC1_RB14_RP46
    {PB14, HAL_LL_TIM_INDEX_2, HAL_LL_CCP_CHANNEL_1, hal_ll_tim_module_num(CCP_MODULE_3)},
    #endif
    #ifdef PWM_CCP3_OC1_RB15_RP47
    {PB15, HAL_LL_TIM_INDEX_2, HAL_LL_CCP_CHANNEL_1, hal_ll_tim_module_num(CCP_MODULE_3)},
    #endif
    #ifdef PWM_CCP3_OC1_RB2_RP34
    {PB2, HAL_LL_TIM_INDEX_2, HAL_LL_CCP_CHANNEL_1, hal_ll_tim_module_num(CCP_MODULE_3)},
    #endif
    #ifdef PWM_CCP3_OC1_RB3_RP35
    {PB3, HAL_LL_TIM_INDEX_2, HAL_LL_CCP_CHANNEL_1, hal_ll_tim_module_num(CCP_MODULE_3)},
    #endif
    #ifdef PWM_CCP3_OC1_RB4_RP36
    {PB4, HAL_LL_TIM_INDEX_2, HAL_LL_CCP_CHANNEL_1, hal_ll_tim_module_num(CCP_MODULE_3)},
    #endif
    #ifdef PWM_CCP3_OC1_RB5_RP37
    {PB5, HAL_LL_TIM_INDEX_2, HAL_LL_CCP_CHANNEL_1, hal_ll_tim_module_num(CCP_MODULE_3)},
    #endif
    #ifdef PWM_CCP3_OC1_RB6_RP38
    {PB6, HAL_LL_TIM_INDEX_2, HAL_LL_CCP_CHANNEL_1, hal_ll_tim_module_num(CCP_MODULE_3)},
    #endif
    #ifdef PWM_CCP3_OC1_RB7_RP39
    {PB7, HAL_LL_TIM_INDEX_2, HAL_LL_CCP_CHANNEL_1, hal_ll_tim_module_num(CCP_MODULE_3)},
    #endif
    #ifdef PWM_CCP3_OC1_RB8_RP40
    {PB8, HAL_LL_TIM_INDEX_2, HAL_LL_CCP_CHANNEL_1, hal_ll_tim_module_num(CCP_MODULE_3)},
    #endif
    #ifdef PWM_CCP3_OC1_RB9_RP41
    {PB9, HAL_LL_TIM_INDEX_2, HAL_LL_CCP_CHANNEL_1, hal_ll_tim_module_num(CCP_MODULE_3)},
    #endif
    #ifdef PWM_CCP1_OC2_RB12_RP44
    {PB12, HAL_LL_TIM_INDEX_2, HAL_LL_CCP_CHANNEL_2, hal_ll_tim_module_num(CCP_MODULE_1)},
    #endif
    #ifdef PWM_CCP1_OC2_RB3_RP35
    {PB3, HAL_LL_TIM_INDEX_2, HAL_LL_CCP_CHANNEL_2, hal_ll_tim_module_num(CCP_MODULE_1)},
    #endif
    #ifdef PWM_CCP1_OC2_RB5_RP37
    {PB5, HAL_LL_TIM_INDEX_2, HAL_LL_CCP_CHANNEL_2, hal_ll_tim_module_num(CCP_MODULE_1)},
    #endif
    #ifdef PWM_CCP1_OC2_RB6_RP38
    {PB6, HAL_LL_TIM_INDEX_2, HAL_LL_CCP_CHANNEL_2, hal_ll_tim_module_num(CCP_MODULE_1)},
    #endif
    #ifdef PWM_CCP1_OC2_RB9_RP41
    {PB9, HAL_LL_TIM_INDEX_2, HAL_LL_CCP_CHANNEL_2, hal_ll_tim_module_num(CCP_MODULE_1)},
    #endif
    #ifdef PWM_CCP1_OC3_RB10_RP42
    {PB10, HAL_LL_TIM_INDEX_2, HAL_LL_CCP_CHANNEL_3, hal_ll_tim_module_num(CCP_MODULE_1)},
    #endif
    #ifdef PWM_CCP1_OC3_RB11_RP43
    {PB11, HAL_LL_TIM_INDEX_2, HAL_LL_CCP_CHANNEL_3, hal_ll_tim_module_num(CCP_MODULE_1)},
    #endif
    #ifdef PWM_CCP1_OC3_RB14_RP46
    {PB14, HAL_LL_TIM_INDEX_2, HAL_LL_CCP_CHANNEL_3, hal_ll_tim_module_num(CCP_MODULE_1)},
    #endif
    #ifdef PWM_CCP1_OC3_RB15_RP47
    {PB15, HAL_LL_TIM_INDEX_2, HAL_LL_CCP_CHANNEL_3, hal_ll_tim_module_num(CCP_MODULE_1)},
    #endif
    #ifdef PWM_CCP1_OC3_RB2_RP34
    {PB2, HAL_LL_TIM_INDEX_2, HAL_LL_CCP_CHANNEL_3, hal_ll_tim_module_num(CCP_MODULE_1)},
    #endif
    #ifdef PWM_CCP1_OC3_RB7_RP39
    {PB7, HAL_LL_TIM_INDEX_2, HAL_LL_CCP_CHANNEL_3, hal_ll_tim_module_num(CCP_MODULE_1)},
    #endif
    #ifdef PWM_CCP1_OC4_RB1_RP33
    {PB1, HAL_LL_TIM_INDEX_2, HAL_LL_CCP_CHANNEL_4, hal_ll_tim_module_num(CCP_MODULE_1)},
    #endif
    #ifdef PWM_CCP1_OC4_RB4_RP36
    {PB4, HAL_LL_TIM_INDEX_2, HAL_LL_CCP_CHANNEL_4, hal_ll_tim_module_num(CCP_MODULE_1)},
    #endif
    #ifdef PWM_CCP1_OC4_RB8_RP40
    {PB8, HAL_LL_TIM_INDEX_2, HAL_LL_CCP_CHANNEL_4, hal_ll_tim_module_num(CCP_MODULE_1)},
    #endif
    #ifdef PWM_CCP2_OC2_RB12_RP44
    {PB12, HAL_LL_TIM_INDEX_2, HAL_LL_CCP_CHANNEL_2, hal_ll_tim_module_num(CCP_MODULE_2)},
    #endif
    #ifdef PWM_CCP2_OC3_RB14_RP46
    {PB14, HAL_LL_TIM_INDEX_2, HAL_LL_CCP_CHANNEL_3, hal_ll_tim_module_num(CCP_MODULE_2)},
    #endif
    #ifdef PWM_CCP2_OC3_RB7_RP39
    {PB7, HAL_LL_TIM_INDEX_2, HAL_LL_CCP_CHANNEL_3, hal_ll_tim_module_num(CCP_MODULE_2)},
    #endif
    #ifdef PWM_CCP3_OC2_RB12_RP44
    {PB12, HAL_LL_TIM_INDEX_2, HAL_LL_CCP_CHANNEL_2, hal_ll_tim_module_num(CCP_MODULE_3)},
    #endif
    #ifdef PWM_CCP3_OC2_RB3_RP35
    {PB3, HAL_LL_TIM_INDEX_2, HAL_LL_CCP_CHANNEL_2, hal_ll_tim_module_num(CCP_MODULE_3)},
    #endif
    #ifdef PWM_CCP3_OC2_RB5_RP37
    {PB5, HAL_LL_TIM_INDEX_2, HAL_LL_CCP_CHANNEL_2, hal_ll_tim_module_num(CCP_MODULE_3)},
    #endif
    #ifdef PWM_CCP3_OC2_RB6_RP38
    {PB6, HAL_LL_TIM_INDEX_2, HAL_LL_CCP_CHANNEL_2, hal_ll_tim_module_num(CCP_MODULE_3)},
    #endif
    #ifdef PWM_CCP3_OC2_RB9_RP41
    {PB9, HAL_LL_TIM_INDEX_2, HAL_LL_CCP_CHANNEL_2, hal_ll_tim_module_num(CCP_MODULE_3)},
    #endif
    #ifdef PWM_CCP3_OC3_RB10_RP42
    {PB10, HAL_LL_TIM_INDEX_2, HAL_LL_CCP_CHANNEL_3, hal_ll_tim_module_num(CCP_MODULE_3)},
    #endif
    #ifdef PWM_CCP3_OC3_RB11_RP43
    {PB11, HAL_LL_TIM_INDEX_2, HAL_LL_CCP_CHANNEL_3, hal_ll_tim_module_num(CCP_MODULE_3)},
    #endif
    #ifdef PWM_CCP3_OC3_RB14_RP46
    {PB14, HAL_LL_TIM_INDEX_2, HAL_LL_CCP_CHANNEL_3, hal_ll_tim_module_num(CCP_MODULE_3)},
    #endif
    #ifdef PWM_CCP3_OC3_RB15_RP47
    {PB15, HAL_LL_TIM_INDEX_2, HAL_LL_CCP_CHANNEL_3, hal_ll_tim_module_num(CCP_MODULE_3)},
    #endif
    #ifdef PWM_CCP3_OC3_RB2_RP34
    {PB2, HAL_LL_TIM_INDEX_2, HAL_LL_CCP_CHANNEL_3, hal_ll_tim_module_num(CCP_MODULE_3)},
    #endif
    #ifdef PWM_CCP3_OC3_RB7_RP39
    {PB7, HAL_LL_TIM_INDEX_2, HAL_LL_CCP_CHANNEL_3, hal_ll_tim_module_num(CCP_MODULE_3)},
    #endif
    #ifdef PWM_CCP3_OC4_RB1_RP33
    {PB1, HAL_LL_TIM_INDEX_2, HAL_LL_CCP_CHANNEL_4, hal_ll_tim_module_num(CCP_MODULE_3)},
    #endif
    #ifdef PWM_CCP3_OC4_RB4_RP36
    {PB4, HAL_LL_TIM_INDEX_2, HAL_LL_CCP_CHANNEL_4, hal_ll_tim_module_num(CCP_MODULE_3)},
    #endif
    #ifdef PWM_CCP3_OC4_RB8_RP40
    {PB8, HAL_LL_TIM_INDEX_2, HAL_LL_CCP_CHANNEL_4, hal_ll_tim_module_num(CCP_MODULE_3)},
    #endif
    #ifdef PWM_CCP4_OC1_RB0_RP32
    {PB0, HAL_LL_TIM_INDEX_2, HAL_LL_CCP_CHANNEL_1, hal_ll_tim_module_num(CCP_MODULE_4)},
    #endif
    #ifdef PWM_CCP4_OC1_RB13_RP45
    {PB13, HAL_LL_TIM_INDEX_2, HAL_LL_CCP_CHANNEL_1, hal_ll_tim_module_num(CCP_MODULE_4)},
    #endif
    #ifdef PWM_CCP4_OC2_RB12_RP44
    {PB12, HAL_LL_TIM_INDEX_2, HAL_LL_CCP_CHANNEL_2, hal_ll_tim_module_num(CCP_MODULE_4)},
    #endif
    #ifdef PWM_CCP4_OC2_RB3_RP35
    {PB3, HAL_LL_TIM_INDEX_2, HAL_LL_CCP_CHANNEL_2, hal_ll_tim_module_num(CCP_MODULE_4)},
    #endif
    #ifdef PWM_CCP4_OC2_RB6_RP38
    {PB6, HAL_LL_TIM_INDEX_2, HAL_LL_CCP_CHANNEL_2, hal_ll_tim_module_num(CCP_MODULE_4)},
    #endif
    #ifdef PWM_CCP4_OC2_RB9_RP41
    {PB9, HAL_LL_TIM_INDEX_2, HAL_LL_CCP_CHANNEL_2, hal_ll_tim_module_num(CCP_MODULE_4)},
    #endif
    #ifdef PWM_CCP4_OC3_RB10_RP42
    {PB10, HAL_LL_TIM_INDEX_2, HAL_LL_CCP_CHANNEL_3, hal_ll_tim_module_num(CCP_MODULE_4)},
    #endif
    #ifdef PWM_CCP4_OC3_RB14_RP46
    {PB14, HAL_LL_TIM_INDEX_2, HAL_LL_CCP_CHANNEL_3, hal_ll_tim_module_num(CCP_MODULE_4)},
    #endif
    #ifdef PWM_CCP4_OC3_RB15_RP47
    {PB15, HAL_LL_TIM_INDEX_2, HAL_LL_CCP_CHANNEL_3, hal_ll_tim_module_num(CCP_MODULE_4)},
    #endif
    #ifdef PWM_CCP4_OC3_RB2_RP34
    {PB2, HAL_LL_TIM_INDEX_2, HAL_LL_CCP_CHANNEL_3, hal_ll_tim_module_num(CCP_MODULE_4)},
    #endif
    #ifdef PWM_CCP4_OC3_RB7_RP39
    {PB7, HAL_LL_TIM_INDEX_2, HAL_LL_CCP_CHANNEL_3, hal_ll_tim_module_num(CCP_MODULE_4)},
    #endif
    #ifdef PWM_CCP4_OC4_RB1_RP33
    {PB1, HAL_LL_TIM_INDEX_2, HAL_LL_CCP_CHANNEL_4, hal_ll_tim_module_num(CCP_MODULE_4)},
    #endif
    #ifdef PWM_CCP4_OC4_RB8_RP40
    {PB8, HAL_LL_TIM_INDEX_2, HAL_LL_CCP_CHANNEL_4, hal_ll_tim_module_num(CCP_MODULE_4)},
    #endif
    #ifdef PWM_CCP5_OC2_RB6_RP38
    {PB6, HAL_LL_TIM_INDEX_2, HAL_LL_CCP_CHANNEL_2, hal_ll_tim_module_num(CCP_MODULE_5)},
    #endif
    #ifdef PWM_CCP5_OC3_RB15_RP47
    {PB15, HAL_LL_TIM_INDEX_2, HAL_LL_CCP_CHANNEL_3, hal_ll_tim_module_num(CCP_MODULE_5)},
    #endif
    #ifdef PWM_CCP5_OC3_RB2_RP34
    {PB2, HAL_LL_TIM_INDEX_2, HAL_LL_CCP_CHANNEL_3, hal_ll_tim_module_num(CCP_MODULE_5)},
    #endif
    #ifdef PWM_CCP5_OC4_RB1_RP33
    {PB1, HAL_LL_TIM_INDEX_2, HAL_LL_CCP_CHANNEL_4, hal_ll_tim_module_num(CCP_MODULE_5)},
    #endif
    #ifdef PWM_CCP5_OC4_RB4_RP36
    {PB4, HAL_LL_TIM_INDEX_2, HAL_LL_CCP_CHANNEL_4, hal_ll_tim_module_num(CCP_MODULE_5)},
    #endif
    #ifdef PWM_CCP1_OC2_RB1_RP33
    {PB1, HAL_LL_TIM_INDEX_2, HAL_LL_CCP_CHANNEL_2, hal_ll_tim_module_num(CCP_MODULE_1)},
    #endif
    #ifdef PWM_CCP1_OC2_RB4_RP36
    {PB4, HAL_LL_TIM_INDEX_2, HAL_LL_CCP_CHANNEL_2, hal_ll_tim_module_num(CCP_MODULE_1)},
    #endif
    #ifdef PWM_CCP1_OC3_RB0_RP32
    {PB0, HAL_LL_TIM_INDEX_2, HAL_LL_CCP_CHANNEL_3, hal_ll_tim_module_num(CCP_MODULE_1)},
    #endif
    #ifdef PWM_CCP1_OC3_RB13_RP45
    {PB13, HAL_LL_TIM_INDEX_2, HAL_LL_CCP_CHANNEL_3, hal_ll_tim_module_num(CCP_MODULE_1)},
    #endif
    #ifdef PWM_CCP1_OC3_RB5_RP37
    {PB5, HAL_LL_TIM_INDEX_2, HAL_LL_CCP_CHANNEL_3, hal_ll_tim_module_num(CCP_MODULE_1)},
    #endif
    #ifdef PWM_CCP1_OC3_RB6_RP38
    {PB6, HAL_LL_TIM_INDEX_2, HAL_LL_CCP_CHANNEL_3, hal_ll_tim_module_num(CCP_MODULE_1)},
    #endif
    #ifdef PWM_CCP1_OC4_RB12_RP44
    {PB12, HAL_LL_TIM_INDEX_2, HAL_LL_CCP_CHANNEL_4, hal_ll_tim_module_num(CCP_MODULE_1)},
    #endif
    #ifdef PWM_CCP1_OC4_RB15_RP47
    {PB15, HAL_LL_TIM_INDEX_2, HAL_LL_CCP_CHANNEL_4, hal_ll_tim_module_num(CCP_MODULE_1)},
    #endif
    #ifdef PWM_CCP1_OC4_RB3_RP35
    {PB3, HAL_LL_TIM_INDEX_2, HAL_LL_CCP_CHANNEL_4, hal_ll_tim_module_num(CCP_MODULE_1)},
    #endif
    #ifdef PWM_CCP1_OC4_RB9_RP41
    {PB9, HAL_LL_TIM_INDEX_2, HAL_LL_CCP_CHANNEL_4, hal_ll_tim_module_num(CCP_MODULE_1)},
    #endif
    #ifdef PWM_CCP2_OC1_RC13_RP61
    {PC13, HAL_LL_TIM_INDEX_2, HAL_LL_CCP_CHANNEL_1, hal_ll_tim_module_num(CCP_MODULE_2)},
    #endif
    #ifdef PWM_CCP2_OC1_RC9_RP57
    {PC9, HAL_LL_TIM_INDEX_2, HAL_LL_CCP_CHANNEL_1, hal_ll_tim_module_num(CCP_MODULE_2)},
    #endif
    #ifdef PWM_CCP2_OC2_RC12_RP60
    {PC12, HAL_LL_TIM_INDEX_2, HAL_LL_CCP_CHANNEL_2, hal_ll_tim_module_num(CCP_MODULE_2)},
    #endif
    #ifdef PWM_CCP2_OC2_RC3_RP51
    {PC3, HAL_LL_TIM_INDEX_2, HAL_LL_CCP_CHANNEL_2, hal_ll_tim_module_num(CCP_MODULE_2)},
    #endif
    #ifdef PWM_CCP2_OC2_RC5_RP53
    {PC5, HAL_LL_TIM_INDEX_2, HAL_LL_CCP_CHANNEL_2, hal_ll_tim_module_num(CCP_MODULE_2)},
    #endif
    #ifdef PWM_CCP2_OC2_RC8_RP56
    {PC8, HAL_LL_TIM_INDEX_2, HAL_LL_CCP_CHANNEL_2, hal_ll_tim_module_num(CCP_MODULE_2)},
    #endif
    #ifdef PWM_CCP2_OC3_RC0_RP48
    {PC0, HAL_LL_TIM_INDEX_2, HAL_LL_CCP_CHANNEL_3, hal_ll_tim_module_num(CCP_MODULE_2)},
    #endif
    #ifdef PWM_CCP2_OC3_RC11_RP59
    {PC11, HAL_LL_TIM_INDEX_2, HAL_LL_CCP_CHANNEL_3, hal_ll_tim_module_num(CCP_MODULE_2)},
    #endif
    #ifdef PWM_CCP2_OC4_RC1_RP49
    {PC1, HAL_LL_TIM_INDEX_2, HAL_LL_CCP_CHANNEL_4, hal_ll_tim_module_num(CCP_MODULE_2)},
    #endif
    #ifdef PWM_CCP2_OC4_RC10_RP58
    {PC10, HAL_LL_TIM_INDEX_2, HAL_LL_CCP_CHANNEL_4, hal_ll_tim_module_num(CCP_MODULE_2)},
    #endif
    #ifdef PWM_CCP2_OC4_RC2_RP50
    {PC2, HAL_LL_TIM_INDEX_2, HAL_LL_CCP_CHANNEL_4, hal_ll_tim_module_num(CCP_MODULE_2)},
    #endif
    #ifdef PWM_CCP2_OC4_RC4_RP52
    {PC4, HAL_LL_TIM_INDEX_2, HAL_LL_CCP_CHANNEL_4, hal_ll_tim_module_num(CCP_MODULE_2)},
    #endif
    #ifdef PWM_CCP2_OC4_RC6_RP54
    {PC6, HAL_LL_TIM_INDEX_2, HAL_LL_CCP_CHANNEL_4, hal_ll_tim_module_num(CCP_MODULE_2)},
    #endif
    #ifdef PWM_CCP2_OC4_RC7_RP55
    {PC7, HAL_LL_TIM_INDEX_2, HAL_LL_CCP_CHANNEL_4, hal_ll_tim_module_num(CCP_MODULE_2)},
    #endif
    #ifdef PWM_CCP3_OC2_RB0_RP32
    {PB0, HAL_LL_TIM_INDEX_2, HAL_LL_CCP_CHANNEL_2, hal_ll_tim_module_num(CCP_MODULE_3)},
    #endif
    #ifdef PWM_CCP3_OC2_RB13_RP45
    {PB13, HAL_LL_TIM_INDEX_2, HAL_LL_CCP_CHANNEL_2, hal_ll_tim_module_num(CCP_MODULE_3)},
    #endif
    #ifdef PWM_CCP3_OC3_RB12_RP44
    {PB12, HAL_LL_TIM_INDEX_2, HAL_LL_CCP_CHANNEL_3, hal_ll_tim_module_num(CCP_MODULE_3)},
    #endif
    #ifdef PWM_CCP3_OC3_RB3_RP35
    {PB3, HAL_LL_TIM_INDEX_2, HAL_LL_CCP_CHANNEL_3, hal_ll_tim_module_num(CCP_MODULE_3)},
    #endif
    #ifdef PWM_CCP3_OC3_RB9_RP41
    {PB9, HAL_LL_TIM_INDEX_2, HAL_LL_CCP_CHANNEL_3, hal_ll_tim_module_num(CCP_MODULE_3)},
    #endif
    #ifdef PWM_CCP3_OC4_RB10_RP42
    {PB10, HAL_LL_TIM_INDEX_2, HAL_LL_CCP_CHANNEL_4, hal_ll_tim_module_num(CCP_MODULE_3)},
    #endif
    #ifdef PWM_CCP3_OC4_RB11_RP43
    {PB11, HAL_LL_TIM_INDEX_2, HAL_LL_CCP_CHANNEL_4, hal_ll_tim_module_num(CCP_MODULE_3)},
    #endif
    #ifdef PWM_CCP3_OC4_RB14_RP46
    {PB14, HAL_LL_TIM_INDEX_2, HAL_LL_CCP_CHANNEL_4, hal_ll_tim_module_num(CCP_MODULE_3)},
    #endif
    #ifdef PWM_CCP3_OC4_RB2_RP34
    {PB2, HAL_LL_TIM_INDEX_2, HAL_LL_CCP_CHANNEL_4, hal_ll_tim_module_num(CCP_MODULE_3)},
    #endif
    #ifdef PWM_CCP3_OC4_RB7_RP39
    {PB7, HAL_LL_TIM_INDEX_2, HAL_LL_CCP_CHANNEL_4, hal_ll_tim_module_num(CCP_MODULE_3)},
    #endif
    #ifdef PWM_CCP4_OC1_RC12_RP60
    {PC12, HAL_LL_TIM_INDEX_2, HAL_LL_CCP_CHANNEL_1, hal_ll_tim_module_num(CCP_MODULE_4)},
    #endif
    #ifdef PWM_CCP4_OC1_RC3_RP51
    {PC3, HAL_LL_TIM_INDEX_2, HAL_LL_CCP_CHANNEL_1, hal_ll_tim_module_num(CCP_MODULE_4)},
    #endif
    #ifdef PWM_CCP4_OC1_RC5_RP53
    {PC5, HAL_LL_TIM_INDEX_2, HAL_LL_CCP_CHANNEL_1, hal_ll_tim_module_num(CCP_MODULE_4)},
    #endif
    #ifdef PWM_CCP4_OC1_RC8_RP56
    {PC8, HAL_LL_TIM_INDEX_2, HAL_LL_CCP_CHANNEL_1, hal_ll_tim_module_num(CCP_MODULE_4)},
    #endif
    #ifdef PWM_CCP4_OC2_RC0_RP48
    {PC0, HAL_LL_TIM_INDEX_2, HAL_LL_CCP_CHANNEL_2, hal_ll_tim_module_num(CCP_MODULE_4)},
    #endif
    #ifdef PWM_CCP4_OC2_RC11_RP59
    {PC11, HAL_LL_TIM_INDEX_2, HAL_LL_CCP_CHANNEL_2, hal_ll_tim_module_num(CCP_MODULE_4)},
    #endif
    #ifdef PWM_CCP4_OC3_RC1_RP49
    {PC1, HAL_LL_TIM_INDEX_2, HAL_LL_CCP_CHANNEL_3, hal_ll_tim_module_num(CCP_MODULE_4)},
    #endif
    #ifdef PWM_CCP4_OC3_RC10_RP58
    {PC10, HAL_LL_TIM_INDEX_2, HAL_LL_CCP_CHANNEL_3, hal_ll_tim_module_num(CCP_MODULE_4)},
    #endif
    #ifdef PWM_CCP4_OC3_RC2_RP50
    {PC2, HAL_LL_TIM_INDEX_2, HAL_LL_CCP_CHANNEL_3, hal_ll_tim_module_num(CCP_MODULE_4)},
    #endif
    #ifdef PWM_CCP4_OC3_RC4_RP52
    {PC4, HAL_LL_TIM_INDEX_2, HAL_LL_CCP_CHANNEL_3, hal_ll_tim_module_num(CCP_MODULE_4)},
    #endif
    #ifdef PWM_CCP4_OC3_RC6_RP54
    {PC6, HAL_LL_TIM_INDEX_2, HAL_LL_CCP_CHANNEL_3, hal_ll_tim_module_num(CCP_MODULE_4)},
    #endif
    #ifdef PWM_CCP4_OC3_RC7_RP55
    {PC7, HAL_LL_TIM_INDEX_2, HAL_LL_CCP_CHANNEL_3, hal_ll_tim_module_num(CCP_MODULE_4)},
    #endif
    #ifdef PWM_CCP4_OC4_RC13_RP61
    {PC13, HAL_LL_TIM_INDEX_2, HAL_LL_CCP_CHANNEL_4, hal_ll_tim_module_num(CCP_MODULE_4)},
    #endif
    #ifdef PWM_CCP4_OC4_RC9_RP57
    {PC9, HAL_LL_TIM_INDEX_2, HAL_LL_CCP_CHANNEL_4, hal_ll_tim_module_num(CCP_MODULE_4)},
    #endif
    #ifdef PWM_CCP5_OC3_RB8_RP40
    {PB8, HAL_LL_TIM_INDEX_2, HAL_LL_CCP_CHANNEL_3, hal_ll_tim_module_num(CCP_MODULE_5)},
    #endif
    #ifdef PWM_CCP1_OC2_RB11_RP43
    {PB11, HAL_LL_TIM_INDEX_2, HAL_LL_CCP_CHANNEL_2, hal_ll_tim_module_num(CCP_MODULE_1)},
    #endif
    #ifdef PWM_CCP1_OC2_RB14_RP46
    {PB14, HAL_LL_TIM_INDEX_2, HAL_LL_CCP_CHANNEL_2, hal_ll_tim_module_num(CCP_MODULE_1)},
    #endif
    #ifdef PWM_CCP1_OC2_RB15_RP47
    {PB15, HAL_LL_TIM_INDEX_2, HAL_LL_CCP_CHANNEL_2, hal_ll_tim_module_num(CCP_MODULE_1)},
    #endif
    #ifdef PWM_CCP1_OC2_RB7_RP39
    {PB7, HAL_LL_TIM_INDEX_2, HAL_LL_CCP_CHANNEL_2, hal_ll_tim_module_num(CCP_MODULE_1)},
    #endif
    #ifdef PWM_CCP1_OC3_RB8_RP40
    {PB8, HAL_LL_TIM_INDEX_2, HAL_LL_CCP_CHANNEL_3, hal_ll_tim_module_num(CCP_MODULE_1)},
    #endif
    #ifdef PWM_CCP1_OC4_RB13_RP45
    {PB13, HAL_LL_TIM_INDEX_2, HAL_LL_CCP_CHANNEL_4, hal_ll_tim_module_num(CCP_MODULE_1)},
    #endif
    #ifdef PWM_CCP2_OC1_RC1_RP49
    {PC1, HAL_LL_TIM_INDEX_2, HAL_LL_CCP_CHANNEL_1, hal_ll_tim_module_num(CCP_MODULE_2)},
    #endif
    #ifdef PWM_CCP2_OC1_RC10_RP58
    {PC10, HAL_LL_TIM_INDEX_2, HAL_LL_CCP_CHANNEL_1, hal_ll_tim_module_num(CCP_MODULE_2)},
    #endif
    #ifdef PWM_CCP2_OC1_RC15_RP63
    {PC15, HAL_LL_TIM_INDEX_2, HAL_LL_CCP_CHANNEL_1, hal_ll_tim_module_num(CCP_MODULE_2)},
    #endif
    #ifdef PWM_CCP2_OC2_RC13_RP61
    {PC13, HAL_LL_TIM_INDEX_2, HAL_LL_CCP_CHANNEL_2, hal_ll_tim_module_num(CCP_MODULE_2)},
    #endif
    #ifdef PWM_CCP2_OC2_RC9_RP57
    {PC9, HAL_LL_TIM_INDEX_2, HAL_LL_CCP_CHANNEL_2, hal_ll_tim_module_num(CCP_MODULE_2)},
    #endif
    #ifdef PWM_CCP2_OC3_RC12_RP60
    {PC12, HAL_LL_TIM_INDEX_2, HAL_LL_CCP_CHANNEL_3, hal_ll_tim_module_num(CCP_MODULE_2)},
    #endif
    #ifdef PWM_CCP2_OC3_RC14_RP62
    {PC14, HAL_LL_TIM_INDEX_2, HAL_LL_CCP_CHANNEL_3, hal_ll_tim_module_num(CCP_MODULE_2)},
    #endif
    #ifdef PWM_CCP2_OC4_RC0_RP48
    {PC0, HAL_LL_TIM_INDEX_2, HAL_LL_CCP_CHANNEL_4, hal_ll_tim_module_num(CCP_MODULE_2)},
    #endif
    #ifdef PWM_CCP2_OC4_RC11_RP59
    {PC11, HAL_LL_TIM_INDEX_2, HAL_LL_CCP_CHANNEL_4, hal_ll_tim_module_num(CCP_MODULE_2)},
    #endif
    #ifdef PWM_CCP3_OC2_RB10_RP42
    {PB10, HAL_LL_TIM_INDEX_2, HAL_LL_CCP_CHANNEL_2, hal_ll_tim_module_num(CCP_MODULE_3)},
    #endif
    #ifdef PWM_CCP3_OC2_RB2_RP34
    {PB2, HAL_LL_TIM_INDEX_2, HAL_LL_CCP_CHANNEL_2, hal_ll_tim_module_num(CCP_MODULE_3)},
    #endif
    #ifdef PWM_CCP3_OC2_RB8_RP40
    {PB8, HAL_LL_TIM_INDEX_2, HAL_LL_CCP_CHANNEL_2, hal_ll_tim_module_num(CCP_MODULE_3)},
    #endif
    #ifdef PWM_CCP3_OC3_RB1_RP33
    {PB1, HAL_LL_TIM_INDEX_2, HAL_LL_CCP_CHANNEL_3, hal_ll_tim_module_num(CCP_MODULE_3)},
    #endif
    #ifdef PWM_CCP3_OC3_RB13_RP45
    {PB13, HAL_LL_TIM_INDEX_2, HAL_LL_CCP_CHANNEL_3, hal_ll_tim_module_num(CCP_MODULE_3)},
    #endif
    #ifdef PWM_CCP3_OC3_RB4_RP36
    {PB4, HAL_LL_TIM_INDEX_2, HAL_LL_CCP_CHANNEL_3, hal_ll_tim_module_num(CCP_MODULE_3)},
    #endif
    #ifdef PWM_CCP3_OC4_RB0_RP32
    {PB0, HAL_LL_TIM_INDEX_2, HAL_LL_CCP_CHANNEL_4, hal_ll_tim_module_num(CCP_MODULE_3)},
    #endif
    #ifdef PWM_CCP3_OC4_RB12_RP44
    {PB12, HAL_LL_TIM_INDEX_2, HAL_LL_CCP_CHANNEL_4, hal_ll_tim_module_num(CCP_MODULE_3)},
    #endif
    #ifdef PWM_CCP3_OC4_RB5_RP37
    {PB5, HAL_LL_TIM_INDEX_2, HAL_LL_CCP_CHANNEL_4, hal_ll_tim_module_num(CCP_MODULE_3)},
    #endif
    #ifdef PWM_CCP3_OC4_RB6_RP38
    {PB6, HAL_LL_TIM_INDEX_2, HAL_LL_CCP_CHANNEL_4, hal_ll_tim_module_num(CCP_MODULE_3)},
    #endif
    #ifdef PWM_CCP4_OC1_RC13_RP61
    {PC13, HAL_LL_TIM_INDEX_2, HAL_LL_CCP_CHANNEL_1, hal_ll_tim_module_num(CCP_MODULE_4)},
    #endif
    #ifdef PWM_CCP4_OC1_RC9_RP57
    {PC9, HAL_LL_TIM_INDEX_2, HAL_LL_CCP_CHANNEL_1, hal_ll_tim_module_num(CCP_MODULE_4)},
    #endif
    #ifdef PWM_CCP4_OC2_RC12_RP60
    {PC12, HAL_LL_TIM_INDEX_2, HAL_LL_CCP_CHANNEL_2, hal_ll_tim_module_num(CCP_MODULE_4)},
    #endif
    #ifdef PWM_CCP4_OC2_RC14_RP62
    {PC14, HAL_LL_TIM_INDEX_2, HAL_LL_CCP_CHANNEL_2, hal_ll_tim_module_num(CCP_MODULE_4)},
    #endif
    #ifdef PWM_CCP4_OC3_RC0_RP48
    {PC0, HAL_LL_TIM_INDEX_2, HAL_LL_CCP_CHANNEL_3, hal_ll_tim_module_num(CCP_MODULE_4)},
    #endif
    #ifdef PWM_CCP4_OC3_RC11_RP59
    {PC11, HAL_LL_TIM_INDEX_2, HAL_LL_CCP_CHANNEL_3, hal_ll_tim_module_num(CCP_MODULE_4)},
    #endif
    #ifdef PWM_CCP4_OC4_RC1_RP49
    {PC1, HAL_LL_TIM_INDEX_2, HAL_LL_CCP_CHANNEL_4, hal_ll_tim_module_num(CCP_MODULE_4)},
    #endif
    #ifdef PWM_CCP4_OC4_RC10_RP58
    {PC10, HAL_LL_TIM_INDEX_2, HAL_LL_CCP_CHANNEL_4, hal_ll_tim_module_num(CCP_MODULE_4)},
    #endif
    #ifdef PWM_CCP4_OC4_RC15_RP63
    {PC15, HAL_LL_TIM_INDEX_2, HAL_LL_CCP_CHANNEL_4, hal_ll_tim_module_num(CCP_MODULE_4)},
    #endif
    #ifdef PWM_CCP5_OC1_RB10_RP42
    {PB10, HAL_LL_TIM_INDEX_2, HAL_LL_CCP_CHANNEL_1, hal_ll_tim_module_num(CCP_MODULE_5)},
    #endif
    #ifdef PWM_CCP5_OC1_RB2_RP34
    {PB2, HAL_LL_TIM_INDEX_2, HAL_LL_CCP_CHANNEL_1, hal_ll_tim_module_num(CCP_MODULE_5)},
    #endif
    #ifdef PWM_CCP5_OC1_RB8_RP40
    {PB8, HAL_LL_TIM_INDEX_2, HAL_LL_CCP_CHANNEL_1, hal_ll_tim_module_num(CCP_MODULE_5)},
    #endif
    #ifdef PWM_CCP5_OC2_RB1_RP33
    {PB1, HAL_LL_TIM_INDEX_2, HAL_LL_CCP_CHANNEL_2, hal_ll_tim_module_num(CCP_MODULE_5)},
    #endif
    #ifdef PWM_CCP5_OC2_RB13_RP45
    {PB13, HAL_LL_TIM_INDEX_2, HAL_LL_CCP_CHANNEL_2, hal_ll_tim_module_num(CCP_MODULE_5)},
    #endif
    #ifdef PWM_CCP5_OC3_RB0_RP32
    {PB0, HAL_LL_TIM_INDEX_2, HAL_LL_CCP_CHANNEL_3, hal_ll_tim_module_num(CCP_MODULE_5)},
    #endif
    #ifdef PWM_CCP5_OC3_RB12_RP44
    {PB12, HAL_LL_TIM_INDEX_2, HAL_LL_CCP_CHANNEL_3, hal_ll_tim_module_num(CCP_MODULE_5)},
    #endif
    #ifdef PWM_CCP5_OC3_RB5_RP37
    {PB5, HAL_LL_TIM_INDEX_2, HAL_LL_CCP_CHANNEL_3, hal_ll_tim_module_num(CCP_MODULE_5)},
    #endif
    #ifdef PWM_CCP5_OC4_RB11_RP43
    {PB11, HAL_LL_TIM_INDEX_2, HAL_LL_CCP_CHANNEL_4, hal_ll_tim_module_num(CCP_MODULE_5)},
    #endif
    #ifdef PWM_CCP5_OC4_RB14_RP46
    {PB14, HAL_LL_TIM_INDEX_2, HAL_LL_CCP_CHANNEL_4, hal_ll_tim_module_num(CCP_MODULE_5)},
    #endif
    #ifdef PWM_CCP5_OC4_RB15_RP47
    {PB15, HAL_LL_TIM_INDEX_2, HAL_LL_CCP_CHANNEL_4, hal_ll_tim_module_num(CCP_MODULE_5)},
    #endif
    #ifdef PWM_CCP5_OC4_RB3_RP35
    {PB3, HAL_LL_TIM_INDEX_2, HAL_LL_CCP_CHANNEL_4, hal_ll_tim_module_num(CCP_MODULE_5)},
    #endif
    #ifdef PWM_CCP1_OC1_RD0_RP64
    {PD0, HAL_LL_TIM_INDEX_2, HAL_LL_CCP_CHANNEL_1, hal_ll_tim_module_num(CCP_MODULE_1)},
    #endif
    #ifdef PWM_CCP1_OC10_RD4_RP68
    {PD4, HAL_LL_TIM_INDEX_2, HAL_LL_CCP_CHANNEL_10, hal_ll_tim_module_num(CCP_MODULE_1)},
    #endif
    #ifdef PWM_CCP1_OC12_RD5_RP69
    {PD5, HAL_LL_TIM_INDEX_2, HAL_LL_CCP_CHANNEL_12, hal_ll_tim_module_num(CCP_MODULE_1)},
    #endif
    #ifdef PWM_CCP1_OC14_RD6_RP70
    {PD6, HAL_LL_TIM_INDEX_2, HAL_LL_CCP_CHANNEL_14, hal_ll_tim_module_num(CCP_MODULE_1)},
    #endif
    #ifdef PWM_CCP1_OC16_RD7_RP71
    {PD7, HAL_LL_TIM_INDEX_2, HAL_LL_CCP_CHANNEL_16, hal_ll_tim_module_num(CCP_MODULE_1)},
    #endif
    #ifdef PWM_CCP1_OC4_RD1_RP65
    {PD1, HAL_LL_TIM_INDEX_2, HAL_LL_CCP_CHANNEL_4, hal_ll_tim_module_num(CCP_MODULE_1)},
    #endif
    #ifdef PWM_CCP1_OC6_RD2_RP66
    {PD2, HAL_LL_TIM_INDEX_2, HAL_LL_CCP_CHANNEL_6, hal_ll_tim_module_num(CCP_MODULE_1)},
    #endif
    #ifdef PWM_CCP1_OC8_RD3_RP67
    {PD3, HAL_LL_TIM_INDEX_2, HAL_LL_CCP_CHANNEL_8, hal_ll_tim_module_num(CCP_MODULE_1)},
    #endif
    #ifdef PWM_CCP2_OC11_RE0_RP80
    {PE0, HAL_LL_TIM_INDEX_2, HAL_LL_CCP_CHANNEL_11, hal_ll_tim_module_num(CCP_MODULE_2)},
    #endif
    #ifdef PWM_CCP2_OC15_RE2_RP82
    {PE2, HAL_LL_TIM_INDEX_2, HAL_LL_CCP_CHANNEL_15, hal_ll_tim_module_num(CCP_MODULE_2)},
    #endif
    #ifdef PWM_CCP2_OC3_RE4_RP84
    {PE4, HAL_LL_TIM_INDEX_2, HAL_LL_CCP_CHANNEL_3, hal_ll_tim_module_num(CCP_MODULE_2)},
    #endif
    #ifdef PWM_CCP2_OC3_RE5_RP85
    {PE5, HAL_LL_TIM_INDEX_2, HAL_LL_CCP_CHANNEL_3, hal_ll_tim_module_num(CCP_MODULE_2)},
    #endif
    #ifdef PWM_CCP2_OC7_RE7_RP87
    {PE7, HAL_LL_TIM_INDEX_2, HAL_LL_CCP_CHANNEL_7, hal_ll_tim_module_num(CCP_MODULE_2)},
    #endif
    #ifdef PWM_CCP3_OC1_RF1_RP97
    {PF1, HAL_LL_TIM_INDEX_2, HAL_LL_CCP_CHANNEL_1, hal_ll_tim_module_num(CCP_MODULE_3)},
    #endif
    #ifdef PWM_CCP3_OC10_RF5_RP101
    {PF5, HAL_LL_TIM_INDEX_2, HAL_LL_CCP_CHANNEL_10, hal_ll_tim_module_num(CCP_MODULE_3)},
    #endif
    #ifdef PWM_CCP3_OC13_RF3_RP99
    {PF3, HAL_LL_TIM_INDEX_2, HAL_LL_CCP_CHANNEL_13, hal_ll_tim_module_num(CCP_MODULE_3)},
    #endif
    #ifdef PWM_CCP3_OC15_RF0_RP96
    {PF0, HAL_LL_TIM_INDEX_2, HAL_LL_CCP_CHANNEL_15, hal_ll_tim_module_num(CCP_MODULE_3)},
    #endif
    #ifdef PWM_CCP3_OC7_RF4_RP100
    {PF4, HAL_LL_TIM_INDEX_2, HAL_LL_CCP_CHANNEL_7, hal_ll_tim_module_num(CCP_MODULE_3)},
    #endif
    #ifdef PWM_CCP4_OC3_RG6_RP118
    {PG6, HAL_LL_TIM_INDEX_2, HAL_LL_CCP_CHANNEL_3, hal_ll_tim_module_num(CCP_MODULE_4)},
    #endif
    #ifdef PWM_CCP4_OC7_RG8_RP120
    {PG8, HAL_LL_TIM_INDEX_2, HAL_LL_CCP_CHANNEL_7, hal_ll_tim_module_num(CCP_MODULE_4)},
    #endif
    #ifdef PWM_CCP5_OC10_RD7_RP71
    {PD7, HAL_LL_TIM_INDEX_2, HAL_LL_CCP_CHANNEL_10, hal_ll_tim_module_num(CCP_MODULE_5)},
    #endif
    #ifdef PWM_CCP5_OC11_RD0_RP64
    {PD0, HAL_LL_TIM_INDEX_2, HAL_LL_CCP_CHANNEL_11, hal_ll_tim_module_num(CCP_MODULE_5)},
    #endif
    #ifdef PWM_CCP5_OC14_RD1_RP65
    {PD1, HAL_LL_TIM_INDEX_2, HAL_LL_CCP_CHANNEL_14, hal_ll_tim_module_num(CCP_MODULE_5)},
    #endif
    #ifdef PWM_CCP5_OC16_RD2_RP66
    {PD2, HAL_LL_TIM_INDEX_2, HAL_LL_CCP_CHANNEL_16, hal_ll_tim_module_num(CCP_MODULE_5)},
    #endif
    #ifdef PWM_CCP5_OC2_RD3_RP67
    {PD3, HAL_LL_TIM_INDEX_2, HAL_LL_CCP_CHANNEL_2, hal_ll_tim_module_num(CCP_MODULE_5)},
    #endif
    #ifdef PWM_CCP5_OC4_RD4_RP68
    {PD4, HAL_LL_TIM_INDEX_2, HAL_LL_CCP_CHANNEL_4, hal_ll_tim_module_num(CCP_MODULE_5)},
    #endif
    #ifdef PWM_CCP5_OC6_RD5_RP69
    {PD5, HAL_LL_TIM_INDEX_2, HAL_LL_CCP_CHANNEL_6, hal_ll_tim_module_num(CCP_MODULE_5)},
    #endif
    #ifdef PWM_CCP5_OC8_RD6_RP70
    {PD6, HAL_LL_TIM_INDEX_2, HAL_LL_CCP_CHANNEL_8, hal_ll_tim_module_num(CCP_MODULE_5)},
    #endif
    #ifdef PWM_CCP6_OC1_RE7_RP87
    {PE7, HAL_LL_TIM_INDEX_2, HAL_LL_CCP_CHANNEL_1, hal_ll_tim_module_num(CCP_MODULE_6)},
    #endif
    #ifdef PWM_CCP6_OC13_RE4_RP84
    {PE4, HAL_LL_TIM_INDEX_2, HAL_LL_CCP_CHANNEL_13, hal_ll_tim_module_num(CCP_MODULE_6)},
    #endif
    #ifdef PWM_CCP6_OC13_RE5_RP85
    {PE5, HAL_LL_TIM_INDEX_2, HAL_LL_CCP_CHANNEL_13, hal_ll_tim_module_num(CCP_MODULE_6)},
    #endif
    #ifdef PWM_CCP6_OC5_RE0_RP80
    {PE0, HAL_LL_TIM_INDEX_2, HAL_LL_CCP_CHANNEL_5, hal_ll_tim_module_num(CCP_MODULE_6)},
    #endif
    #ifdef PWM_CCP6_OC9_RE2_RP82
    {PE2, HAL_LL_TIM_INDEX_2, HAL_LL_CCP_CHANNEL_9, hal_ll_tim_module_num(CCP_MODULE_6)},
    #endif
    #ifdef PWM_CCP7_OC1_RF4_RP100
    {PF4, HAL_LL_TIM_INDEX_2, HAL_LL_CCP_CHANNEL_1, hal_ll_tim_module_num(CCP_MODULE_7)},
    #endif
    #ifdef PWM_CCP7_OC11_RF1_RP97
    {PF1, HAL_LL_TIM_INDEX_2, HAL_LL_CCP_CHANNEL_11, hal_ll_tim_module_num(CCP_MODULE_7)},
    #endif
    #ifdef PWM_CCP7_OC4_RF5_RP101
    {PF5, HAL_LL_TIM_INDEX_2, HAL_LL_CCP_CHANNEL_4, hal_ll_tim_module_num(CCP_MODULE_7)},
    #endif
    #ifdef PWM_CCP7_OC7_RF3_RP99
    {PF3, HAL_LL_TIM_INDEX_2, HAL_LL_CCP_CHANNEL_7, hal_ll_tim_module_num(CCP_MODULE_7)},
    #endif
    #ifdef PWM_CCP7_OC9_RF0_RP96
    {PF0, HAL_LL_TIM_INDEX_2, HAL_LL_CCP_CHANNEL_9, hal_ll_tim_module_num(CCP_MODULE_7)},
    #endif
    #ifdef PWM_CCP8_OC1_RG8_RP120
    {PG8, HAL_LL_TIM_INDEX_2, HAL_LL_CCP_CHANNEL_1, hal_ll_tim_module_num(CCP_MODULE_8)},
    #endif
    #ifdef PWM_CCP8_OC13_RG6_RP118
    {PG6, HAL_LL_TIM_INDEX_2, HAL_LL_CCP_CHANNEL_13, hal_ll_tim_module_num(CCP_MODULE_8)},
    #endif
    #ifdef PWM_CCP9_OC10_RD2_RP66
    {PD2, HAL_LL_TIM_INDEX_2, HAL_LL_CCP_CHANNEL_10, hal_ll_tim_module_num(CCP_MODULE_9)},
    #endif
    #ifdef PWM_CCP9_OC12_RD3_RP67
    {PD3, HAL_LL_TIM_INDEX_2, HAL_LL_CCP_CHANNEL_12, hal_ll_tim_module_num(CCP_MODULE_9)},
    #endif
    #ifdef PWM_CCP9_OC14_RD4_RP68
    {PD4, HAL_LL_TIM_INDEX_2, HAL_LL_CCP_CHANNEL_14, hal_ll_tim_module_num(CCP_MODULE_9)},
    #endif
    #ifdef PWM_CCP9_OC16_RD5_RP69
    {PD5, HAL_LL_TIM_INDEX_2, HAL_LL_CCP_CHANNEL_16, hal_ll_tim_module_num(CCP_MODULE_9)},
    #endif
    #ifdef PWM_CCP9_OC2_RD6_RP70
    {PD6, HAL_LL_TIM_INDEX_2, HAL_LL_CCP_CHANNEL_2, hal_ll_tim_module_num(CCP_MODULE_9)},
    #endif
    #ifdef PWM_CCP9_OC4_RD7_RP71
    {PD7, HAL_LL_TIM_INDEX_2, HAL_LL_CCP_CHANNEL_4, hal_ll_tim_module_num(CCP_MODULE_9)},
    #endif
    #ifdef PWM_CCP9_OC5_RD0_RP64
    {PD0, HAL_LL_TIM_INDEX_2, HAL_LL_CCP_CHANNEL_5, hal_ll_tim_module_num(CCP_MODULE_9)},
    #endif
    #ifdef PWM_CCP9_OC8_RD1_RP65
    {PD1, HAL_LL_TIM_INDEX_2, HAL_LL_CCP_CHANNEL_8, hal_ll_tim_module_num(CCP_MODULE_9)},
    #endif
    #ifdef PWM_CCP1_OC1_RD15_RP79
    {PD15, HAL_LL_TIM_INDEX_2, HAL_LL_CCP_CHANNEL_1, hal_ll_tim_module_num(CCP_MODULE_1)},
    #endif
    #ifdef PWM_CCP1_OC1_RD7_RP71
    {PD7, HAL_LL_TIM_INDEX_2, HAL_LL_CCP_CHANNEL_1, hal_ll_tim_module_num(CCP_MODULE_1)},
    #endif
    #ifdef PWM_CCP1_OC11_RD4_RP68
    {PD4, HAL_LL_TIM_INDEX_2, HAL_LL_CCP_CHANNEL_11, hal_ll_tim_module_num(CCP_MODULE_1)},
    #endif
    #ifdef PWM_CCP1_OC13_RD5_RP69
    {PD5, HAL_LL_TIM_INDEX_2, HAL_LL_CCP_CHANNEL_13, hal_ll_tim_module_num(CCP_MODULE_1)},
    #endif
    #ifdef PWM_CCP1_OC15_RD6_RP70
    {PD6, HAL_LL_TIM_INDEX_2, HAL_LL_CCP_CHANNEL_15, hal_ll_tim_module_num(CCP_MODULE_1)},
    #endif
    #ifdef PWM_CCP1_OC2_RD0_RP64
    {PD0, HAL_LL_TIM_INDEX_2, HAL_LL_CCP_CHANNEL_2, hal_ll_tim_module_num(CCP_MODULE_1)},
    #endif
    #ifdef PWM_CCP1_OC5_RD1_RP65
    {PD1, HAL_LL_TIM_INDEX_2, HAL_LL_CCP_CHANNEL_5, hal_ll_tim_module_num(CCP_MODULE_1)},
    #endif
    #ifdef PWM_CCP1_OC7_RD2_RP66
    {PD2, HAL_LL_TIM_INDEX_2, HAL_LL_CCP_CHANNEL_7, hal_ll_tim_module_num(CCP_MODULE_1)},
    #endif
    #ifdef PWM_CCP1_OC9_RD3_RP67
    {PD3, HAL_LL_TIM_INDEX_2, HAL_LL_CCP_CHANNEL_9, hal_ll_tim_module_num(CCP_MODULE_1)},
    #endif
    #ifdef PWM_CCP2_OC12_RE0_RP80
    {PE0, HAL_LL_TIM_INDEX_2, HAL_LL_CCP_CHANNEL_12, hal_ll_tim_module_num(CCP_MODULE_2)},
    #endif
    #ifdef PWM_CCP2_OC16_RE2_RP82
    {PE2, HAL_LL_TIM_INDEX_2, HAL_LL_CCP_CHANNEL_16, hal_ll_tim_module_num(CCP_MODULE_2)},
    #endif
    #ifdef PWM_CCP2_OC4_RE4_RP84
    {PE4, HAL_LL_TIM_INDEX_2, HAL_LL_CCP_CHANNEL_4, hal_ll_tim_module_num(CCP_MODULE_2)},
    #endif
    #ifdef PWM_CCP2_OC4_RE5_RP85
    {PE5, HAL_LL_TIM_INDEX_2, HAL_LL_CCP_CHANNEL_4, hal_ll_tim_module_num(CCP_MODULE_2)},
    #endif
    #ifdef PWM_CCP2_OC8_RE7_RP87
    {PE7, HAL_LL_TIM_INDEX_2, HAL_LL_CCP_CHANNEL_8, hal_ll_tim_module_num(CCP_MODULE_2)},
    #endif
    #ifdef PWM_CCP3_OC10_RF4_RP100
    {PF4, HAL_LL_TIM_INDEX_2, HAL_LL_CCP_CHANNEL_10, hal_ll_tim_module_num(CCP_MODULE_3)},
    #endif
    #ifdef PWM_CCP3_OC13_RF5_RP101
    {PF5, HAL_LL_TIM_INDEX_2, HAL_LL_CCP_CHANNEL_13, hal_ll_tim_module_num(CCP_MODULE_3)},
    #endif
    #ifdef PWM_CCP3_OC16_RF3_RP99
    {PF3, HAL_LL_TIM_INDEX_2, HAL_LL_CCP_CHANNEL_16, hal_ll_tim_module_num(CCP_MODULE_3)},
    #endif
    #ifdef PWM_CCP3_OC2_RF2_RP98
    {PF2, HAL_LL_TIM_INDEX_2, HAL_LL_CCP_CHANNEL_2, hal_ll_tim_module_num(CCP_MODULE_3)},
    #endif
    #ifdef PWM_CCP3_OC3_RF8_RP104
    {PF8, HAL_LL_TIM_INDEX_2, HAL_LL_CCP_CHANNEL_3, hal_ll_tim_module_num(CCP_MODULE_3)},
    #endif
    #ifdef PWM_CCP3_OC4_RF0_RP96
    {PF0, HAL_LL_TIM_INDEX_2, HAL_LL_CCP_CHANNEL_4, hal_ll_tim_module_num(CCP_MODULE_3)},
    #endif
    #ifdef PWM_CCP3_OC6_RF1_RP97
    {PF1, HAL_LL_TIM_INDEX_2, HAL_LL_CCP_CHANNEL_6, hal_ll_tim_module_num(CCP_MODULE_3)},
    #endif
    #ifdef PWM_CCP3_OC8_RF13_RP109
    {PF13, HAL_LL_TIM_INDEX_2, HAL_LL_CCP_CHANNEL_8, hal_ll_tim_module_num(CCP_MODULE_3)},
    #endif
    #ifdef PWM_CCP3_OC9_RF12_RP108
    {PF12, HAL_LL_TIM_INDEX_2, HAL_LL_CCP_CHANNEL_9, hal_ll_tim_module_num(CCP_MODULE_3)},
    #endif
    #ifdef PWM_CCP4_OC1_RG1_RP113
    {PG1, HAL_LL_TIM_INDEX_2, HAL_LL_CCP_CHANNEL_1, hal_ll_tim_module_num(CCP_MODULE_4)},
    #endif
    #ifdef PWM_CCP4_OC13_RG8_RP120
    {PG8, HAL_LL_TIM_INDEX_2, HAL_LL_CCP_CHANNEL_13, hal_ll_tim_module_num(CCP_MODULE_4)},
    #endif
    #ifdef PWM_CCP4_OC2_RG0_RP112
    {PG0, HAL_LL_TIM_INDEX_2, HAL_LL_CCP_CHANNEL_2, hal_ll_tim_module_num(CCP_MODULE_4)},
    #endif
    #ifdef PWM_CCP4_OC3_RG14_RP126
    {PG14, HAL_LL_TIM_INDEX_2, HAL_LL_CCP_CHANNEL_3, hal_ll_tim_module_num(CCP_MODULE_4)},
    #endif
    #ifdef PWM_CCP4_OC4_RG13_RP125
    {PG13, HAL_LL_TIM_INDEX_2, HAL_LL_CCP_CHANNEL_4, hal_ll_tim_module_num(CCP_MODULE_4)},
    #endif
    #ifdef PWM_CCP4_OC8_RG15_RP127
    {PG15, HAL_LL_TIM_INDEX_2, HAL_LL_CCP_CHANNEL_8, hal_ll_tim_module_num(CCP_MODULE_4)},
    #endif
    #ifdef PWM_CCP4_OC9_RG6_RP118
    {PG6, HAL_LL_TIM_INDEX_2, HAL_LL_CCP_CHANNEL_9, hal_ll_tim_module_num(CCP_MODULE_4)},
    #endif
    #ifdef PWM_CCP5_OC1_RD5_RP69
    {PD5, HAL_LL_TIM_INDEX_2, HAL_LL_CCP_CHANNEL_1, hal_ll_tim_module_num(CCP_MODULE_5)},
    #endif
    #ifdef PWM_CCP5_OC11_RD2_RP66
    {PD2, HAL_LL_TIM_INDEX_2, HAL_LL_CCP_CHANNEL_11, hal_ll_tim_module_num(CCP_MODULE_5)},
    #endif
    #ifdef PWM_CCP5_OC13_RD3_RP67
    {PD3, HAL_LL_TIM_INDEX_2, HAL_LL_CCP_CHANNEL_13, hal_ll_tim_module_num(CCP_MODULE_5)},
    #endif
    #ifdef PWM_CCP5_OC15_RD4_RP68
    {PD4, HAL_LL_TIM_INDEX_2, HAL_LL_CCP_CHANNEL_15, hal_ll_tim_module_num(CCP_MODULE_5)},
    #endif
    #ifdef PWM_CCP5_OC3_RD6_RP70
    {PD6, HAL_LL_TIM_INDEX_2, HAL_LL_CCP_CHANNEL_3, hal_ll_tim_module_num(CCP_MODULE_5)},
    #endif
    #ifdef PWM_CCP5_OC5_RD15_RP79
    {PD15, HAL_LL_TIM_INDEX_2, HAL_LL_CCP_CHANNEL_5, hal_ll_tim_module_num(CCP_MODULE_5)},
    #endif
    #ifdef PWM_CCP5_OC5_RD7_RP71
    {PD7, HAL_LL_TIM_INDEX_2, HAL_LL_CCP_CHANNEL_5, hal_ll_tim_module_num(CCP_MODULE_5)},
    #endif
    #ifdef PWM_CCP5_OC6_RD0_RP64
    {PD0, HAL_LL_TIM_INDEX_2, HAL_LL_CCP_CHANNEL_6, hal_ll_tim_module_num(CCP_MODULE_5)},
    #endif
    #ifdef PWM_CCP5_OC9_RD1_RP65
    {PD1, HAL_LL_TIM_INDEX_2, HAL_LL_CCP_CHANNEL_9, hal_ll_tim_module_num(CCP_MODULE_5)},
    #endif
    #ifdef PWM_CCP6_OC12_RE7_RP87
    {PE7, HAL_LL_TIM_INDEX_2, HAL_LL_CCP_CHANNEL_12, hal_ll_tim_module_num(CCP_MODULE_6)},
    #endif
    #ifdef PWM_CCP6_OC16_RE0_RP80
    {PE0, HAL_LL_TIM_INDEX_2, HAL_LL_CCP_CHANNEL_16, hal_ll_tim_module_num(CCP_MODULE_6)},
    #endif
    #ifdef PWM_CCP6_OC4_RE2_RP82
    {PE2, HAL_LL_TIM_INDEX_2, HAL_LL_CCP_CHANNEL_4, hal_ll_tim_module_num(CCP_MODULE_6)},
    #endif
    #ifdef PWM_CCP6_OC8_RE4_RP84
    {PE4, HAL_LL_TIM_INDEX_2, HAL_LL_CCP_CHANNEL_8, hal_ll_tim_module_num(CCP_MODULE_6)},
    #endif
    #ifdef PWM_CCP6_OC8_RE5_RP85
    {PE5, HAL_LL_TIM_INDEX_2, HAL_LL_CCP_CHANNEL_8, hal_ll_tim_module_num(CCP_MODULE_6)},
    #endif
    #ifdef PWM_CCP7_OC1_RF5_RP101
    {PF5, HAL_LL_TIM_INDEX_2, HAL_LL_CCP_CHANNEL_1, hal_ll_tim_module_num(CCP_MODULE_7)},
    #endif
    #ifdef PWM_CCP7_OC10_RF1_RP97
    {PF1, HAL_LL_TIM_INDEX_2, HAL_LL_CCP_CHANNEL_10, hal_ll_tim_module_num(CCP_MODULE_7)},
    #endif
    #ifdef PWM_CCP7_OC12_RF13_RP109
    {PF13, HAL_LL_TIM_INDEX_2, HAL_LL_CCP_CHANNEL_12, hal_ll_tim_module_num(CCP_MODULE_7)},
    #endif
    #ifdef PWM_CCP7_OC13_RF12_RP108
    {PF12, HAL_LL_TIM_INDEX_2, HAL_LL_CCP_CHANNEL_13, hal_ll_tim_module_num(CCP_MODULE_7)},
    #endif
    #ifdef PWM_CCP7_OC14_RF4_RP100
    {PF4, HAL_LL_TIM_INDEX_2, HAL_LL_CCP_CHANNEL_14, hal_ll_tim_module_num(CCP_MODULE_7)},
    #endif
    #ifdef PWM_CCP7_OC4_RF3_RP99
    {PF3, HAL_LL_TIM_INDEX_2, HAL_LL_CCP_CHANNEL_4, hal_ll_tim_module_num(CCP_MODULE_7)},
    #endif
    #ifdef PWM_CCP7_OC6_RF2_RP98
    {PF2, HAL_LL_TIM_INDEX_2, HAL_LL_CCP_CHANNEL_6, hal_ll_tim_module_num(CCP_MODULE_7)},
    #endif
    #ifdef PWM_CCP7_OC7_RF8_RP104
    {PF8, HAL_LL_TIM_INDEX_2, HAL_LL_CCP_CHANNEL_7, hal_ll_tim_module_num(CCP_MODULE_7)},
    #endif
    #ifdef PWM_CCP7_OC8_RF0_RP96
    {PF0, HAL_LL_TIM_INDEX_2, HAL_LL_CCP_CHANNEL_8, hal_ll_tim_module_num(CCP_MODULE_7)},
    #endif
    #ifdef PWM_CCP8_OC12_RG15_RP127
    {PG15, HAL_LL_TIM_INDEX_2, HAL_LL_CCP_CHANNEL_12, hal_ll_tim_module_num(CCP_MODULE_8)},
    #endif
    #ifdef PWM_CCP8_OC5_RG1_RP113
    {PG1, HAL_LL_TIM_INDEX_2, HAL_LL_CCP_CHANNEL_5, hal_ll_tim_module_num(CCP_MODULE_8)},
    #endif
    #ifdef PWM_CCP8_OC6_RG0_RP112
    {PG0, HAL_LL_TIM_INDEX_2, HAL_LL_CCP_CHANNEL_6, hal_ll_tim_module_num(CCP_MODULE_8)},
    #endif
    #ifdef PWM_CCP8_OC7_RG14_RP126
    {PG14, HAL_LL_TIM_INDEX_2, HAL_LL_CCP_CHANNEL_7, hal_ll_tim_module_num(CCP_MODULE_8)},
    #endif
    #ifdef PWM_CCP8_OC8_RG13_RP125
    {PG13, HAL_LL_TIM_INDEX_2, HAL_LL_CCP_CHANNEL_8, hal_ll_tim_module_num(CCP_MODULE_8)},
    #endif
    #ifdef PWM_CCP9_OC1_RD3_RP67
    {PD3, HAL_LL_TIM_INDEX_2, HAL_LL_CCP_CHANNEL_1, hal_ll_tim_module_num(CCP_MODULE_9)},
    #endif
    #ifdef PWM_CCP9_OC10_RD0_RP64
    {PD0, HAL_LL_TIM_INDEX_2, HAL_LL_CCP_CHANNEL_10, hal_ll_tim_module_num(CCP_MODULE_9)},
    #endif
    #ifdef PWM_CCP9_OC13_RD1_RP65
    {PD1, HAL_LL_TIM_INDEX_2, HAL_LL_CCP_CHANNEL_13, hal_ll_tim_module_num(CCP_MODULE_9)},
    #endif
    #ifdef PWM_CCP9_OC15_RD2_RP66
    {PD2, HAL_LL_TIM_INDEX_2, HAL_LL_CCP_CHANNEL_15, hal_ll_tim_module_num(CCP_MODULE_9)},
    #endif
    #ifdef PWM_CCP9_OC3_RD4_RP68
    {PD4, HAL_LL_TIM_INDEX_2, HAL_LL_CCP_CHANNEL_3, hal_ll_tim_module_num(CCP_MODULE_9)},
    #endif
    #ifdef PWM_CCP9_OC5_RD5_RP69
    {PD5, HAL_LL_TIM_INDEX_2, HAL_LL_CCP_CHANNEL_5, hal_ll_tim_module_num(CCP_MODULE_9)},
    #endif
    #ifdef PWM_CCP9_OC7_RD6_RP70
    {PD6, HAL_LL_TIM_INDEX_2, HAL_LL_CCP_CHANNEL_7, hal_ll_tim_module_num(CCP_MODULE_9)},
    #endif
    #ifdef PWM_CCP9_OC9_RD15_RP79
    {PD15, HAL_LL_TIM_INDEX_2, HAL_LL_CCP_CHANNEL_9, hal_ll_tim_module_num(CCP_MODULE_9)},
    #endif
    #ifdef PWM_CCP9_OC9_RD7_RP71
    {PD7, HAL_LL_TIM_INDEX_2, HAL_LL_CCP_CHANNEL_9, hal_ll_tim_module_num(CCP_MODULE_9)},
    #endif
    #ifdef PWM_CCP1_OC11_RD5_RP69
    {PD5, HAL_LL_TIM_INDEX_2, HAL_LL_CCP_CHANNEL_11, hal_ll_tim_module_num(CCP_MODULE_1)},
    #endif
    #ifdef PWM_CCP1_OC12_RD6_RP70
    {PD6, HAL_LL_TIM_INDEX_2, HAL_LL_CCP_CHANNEL_12, hal_ll_tim_module_num(CCP_MODULE_1)},
    #endif
    #ifdef PWM_CCP1_OC14_RD7_RP71
    {PD7, HAL_LL_TIM_INDEX_2, HAL_LL_CCP_CHANNEL_14, hal_ll_tim_module_num(CCP_MODULE_1)},
    #endif
    #ifdef PWM_CCP2_OC1_RE5_RP85
    {PE5, HAL_LL_TIM_INDEX_2, HAL_LL_CCP_CHANNEL_1, hal_ll_tim_module_num(CCP_MODULE_2)},
    #endif
    #ifdef PWM_CCP2_OC10_RE2_RP82
    {PE2, HAL_LL_TIM_INDEX_2, HAL_LL_CCP_CHANNEL_10, hal_ll_tim_module_num(CCP_MODULE_2)},
    #endif
    #ifdef PWM_CCP2_OC13_RE4_RP84
    {PE4, HAL_LL_TIM_INDEX_2, HAL_LL_CCP_CHANNEL_13, hal_ll_tim_module_num(CCP_MODULE_2)},
    #endif
    #ifdef PWM_CCP2_OC4_RE7_RP87
    {PE7, HAL_LL_TIM_INDEX_2, HAL_LL_CCP_CHANNEL_4, hal_ll_tim_module_num(CCP_MODULE_2)},
    #endif
    #ifdef PWM_CCP2_OC7_RE0_RP80
    {PE0, HAL_LL_TIM_INDEX_2, HAL_LL_CCP_CHANNEL_7, hal_ll_tim_module_num(CCP_MODULE_2)},
    #endif
    #ifdef PWM_CCP3_OC1_RF12_RP108
    {PF12, HAL_LL_TIM_INDEX_2, HAL_LL_CCP_CHANNEL_1, hal_ll_tim_module_num(CCP_MODULE_3)},
    #endif
    #ifdef PWM_CCP3_OC10_RF0_RP96
    {PF0, HAL_LL_TIM_INDEX_2, HAL_LL_CCP_CHANNEL_10, hal_ll_tim_module_num(CCP_MODULE_3)},
    #endif
    #ifdef PWM_CCP3_OC12_RF1_RP97
    {PF1, HAL_LL_TIM_INDEX_2, HAL_LL_CCP_CHANNEL_12, hal_ll_tim_module_num(CCP_MODULE_3)},
    #endif
    #ifdef PWM_CCP3_OC16_RF13_RP109
    {PF13, HAL_LL_TIM_INDEX_2, HAL_LL_CCP_CHANNEL_16, hal_ll_tim_module_num(CCP_MODULE_3)},
    #endif
    #ifdef PWM_CCP3_OC2_RF4_RP100
    {PF4, HAL_LL_TIM_INDEX_2, HAL_LL_CCP_CHANNEL_2, hal_ll_tim_module_num(CCP_MODULE_3)},
    #endif
    #ifdef PWM_CCP3_OC4_RF5_RP101
    {PF5, HAL_LL_TIM_INDEX_2, HAL_LL_CCP_CHANNEL_4, hal_ll_tim_module_num(CCP_MODULE_3)},
    #endif
    #ifdef PWM_CCP3_OC6_RF3_RP99
    {PF3, HAL_LL_TIM_INDEX_2, HAL_LL_CCP_CHANNEL_6, hal_ll_tim_module_num(CCP_MODULE_3)},
    #endif
    #ifdef PWM_CCP3_OC8_RF2_RP98
    {PF2, HAL_LL_TIM_INDEX_2, HAL_LL_CCP_CHANNEL_8, hal_ll_tim_module_num(CCP_MODULE_3)},
    #endif
    #ifdef PWM_CCP3_OC9_RF8_RP104
    {PF8, HAL_LL_TIM_INDEX_2, HAL_LL_CCP_CHANNEL_9, hal_ll_tim_module_num(CCP_MODULE_3)},
    #endif
    #ifdef PWM_CCP4_OC14_RG15_RP127
    {PG15, HAL_LL_TIM_INDEX_2, HAL_LL_CCP_CHANNEL_14, hal_ll_tim_module_num(CCP_MODULE_4)},
    #endif
    #ifdef PWM_CCP4_OC15_RG6_RP118
    {PG6, HAL_LL_TIM_INDEX_2, HAL_LL_CCP_CHANNEL_15, hal_ll_tim_module_num(CCP_MODULE_4)},
    #endif
    #ifdef PWM_CCP4_OC2_RG8_RP120
    {PG8, HAL_LL_TIM_INDEX_2, HAL_LL_CCP_CHANNEL_2, hal_ll_tim_module_num(CCP_MODULE_4)},
    #endif
    #ifdef PWM_CCP4_OC5_RG1_RP113
    {PG1, HAL_LL_TIM_INDEX_2, HAL_LL_CCP_CHANNEL_5, hal_ll_tim_module_num(CCP_MODULE_4)},
    #endif
    #ifdef PWM_CCP4_OC6_RG0_RP112
    {PG0, HAL_LL_TIM_INDEX_2, HAL_LL_CCP_CHANNEL_6, hal_ll_tim_module_num(CCP_MODULE_4)},
    #endif
    #ifdef PWM_CCP4_OC7_RG14_RP126
    {PG14, HAL_LL_TIM_INDEX_2, HAL_LL_CCP_CHANNEL_7, hal_ll_tim_module_num(CCP_MODULE_4)},
    #endif
    #ifdef PWM_CCP4_OC8_RG13_RP125
    {PG13, HAL_LL_TIM_INDEX_2, HAL_LL_CCP_CHANNEL_8, hal_ll_tim_module_num(CCP_MODULE_4)},
    #endif
    #ifdef PWM_CCP5_OC1_RD3_RP67
    {PD3, HAL_LL_TIM_INDEX_2, HAL_LL_CCP_CHANNEL_1, hal_ll_tim_module_num(CCP_MODULE_5)},
    #endif
    #ifdef PWM_CCP5_OC10_RD0_RP64
    {PD0, HAL_LL_TIM_INDEX_2, HAL_LL_CCP_CHANNEL_10, hal_ll_tim_module_num(CCP_MODULE_5)},
    #endif
    #ifdef PWM_CCP5_OC13_RD1_RP65
    {PD1, HAL_LL_TIM_INDEX_2, HAL_LL_CCP_CHANNEL_13, hal_ll_tim_module_num(CCP_MODULE_5)},
    #endif
    #ifdef PWM_CCP5_OC15_RD2_RP66
    {PD2, HAL_LL_TIM_INDEX_2, HAL_LL_CCP_CHANNEL_15, hal_ll_tim_module_num(CCP_MODULE_5)},
    #endif
    #ifdef PWM_CCP5_OC2_RD4_RP68
    {PD4, HAL_LL_TIM_INDEX_2, HAL_LL_CCP_CHANNEL_2, hal_ll_tim_module_num(CCP_MODULE_5)},
    #endif
    #ifdef PWM_CCP5_OC3_RD5_RP69
    {PD5, HAL_LL_TIM_INDEX_2, HAL_LL_CCP_CHANNEL_3, hal_ll_tim_module_num(CCP_MODULE_5)},
    #endif
    #ifdef PWM_CCP5_OC4_RD6_RP70
    {PD6, HAL_LL_TIM_INDEX_2, HAL_LL_CCP_CHANNEL_4, hal_ll_tim_module_num(CCP_MODULE_5)},
    #endif
    #ifdef PWM_CCP5_OC6_RD7_RP71
    {PD7, HAL_LL_TIM_INDEX_2, HAL_LL_CCP_CHANNEL_6, hal_ll_tim_module_num(CCP_MODULE_5)},
    #endif
    #ifdef PWM_CCP5_OC9_RD15_RP79
    {PD15, HAL_LL_TIM_INDEX_2, HAL_LL_CCP_CHANNEL_9, hal_ll_tim_module_num(CCP_MODULE_5)},
    #endif
    #ifdef PWM_CCP6_OC15_RE0_RP80
    {PE0, HAL_LL_TIM_INDEX_2, HAL_LL_CCP_CHANNEL_15, hal_ll_tim_module_num(CCP_MODULE_6)},
    #endif
    #ifdef PWM_CCP6_OC2_RE2_RP82
    {PE2, HAL_LL_TIM_INDEX_2, HAL_LL_CCP_CHANNEL_2, hal_ll_tim_module_num(CCP_MODULE_6)},
    #endif
    #ifdef PWM_CCP6_OC5_RE4_RP84
    {PE4, HAL_LL_TIM_INDEX_2, HAL_LL_CCP_CHANNEL_5, hal_ll_tim_module_num(CCP_MODULE_6)},
    #endif
    #ifdef PWM_CCP6_OC9_RE5_RP85
    {PE5, HAL_LL_TIM_INDEX_2, HAL_LL_CCP_CHANNEL_9, hal_ll_tim_module_num(CCP_MODULE_6)},
    #endif
    #ifdef PWM_CCP7_OC1_RF8_RP104
    {PF8, HAL_LL_TIM_INDEX_2, HAL_LL_CCP_CHANNEL_1, hal_ll_tim_module_num(CCP_MODULE_7)},
    #endif
    #ifdef PWM_CCP7_OC10_RF4_RP100
    {PF4, HAL_LL_TIM_INDEX_2, HAL_LL_CCP_CHANNEL_10, hal_ll_tim_module_num(CCP_MODULE_7)},
    #endif
    #ifdef PWM_CCP7_OC12_RF5_RP101
    {PF5, HAL_LL_TIM_INDEX_2, HAL_LL_CCP_CHANNEL_12, hal_ll_tim_module_num(CCP_MODULE_7)},
    #endif
    #ifdef PWM_CCP7_OC14_RF3_RP99
    {PF3, HAL_LL_TIM_INDEX_2, HAL_LL_CCP_CHANNEL_14, hal_ll_tim_module_num(CCP_MODULE_7)},
    #endif
    #ifdef PWM_CCP7_OC16_RF2_RP98
    {PF2, HAL_LL_TIM_INDEX_2, HAL_LL_CCP_CHANNEL_16, hal_ll_tim_module_num(CCP_MODULE_7)},
    #endif
    #ifdef PWM_CCP7_OC2_RF0_RP96
    {PF0, HAL_LL_TIM_INDEX_2, HAL_LL_CCP_CHANNEL_2, hal_ll_tim_module_num(CCP_MODULE_7)},
    #endif
    #ifdef PWM_CCP7_OC4_RF1_RP97
    {PF1, HAL_LL_TIM_INDEX_2, HAL_LL_CCP_CHANNEL_4, hal_ll_tim_module_num(CCP_MODULE_7)},
    #endif
    #ifdef PWM_CCP7_OC8_RF13_RP109
    {PF13, HAL_LL_TIM_INDEX_2, HAL_LL_CCP_CHANNEL_8, hal_ll_tim_module_num(CCP_MODULE_7)},
    #endif
    #ifdef PWM_CCP7_OC9_RF12_RP108
    {PF12, HAL_LL_TIM_INDEX_2, HAL_LL_CCP_CHANNEL_9, hal_ll_tim_module_num(CCP_MODULE_7)},
    #endif
    #ifdef PWM_CCP8_OC10_RG8_RP120
    {PG8, HAL_LL_TIM_INDEX_2, HAL_LL_CCP_CHANNEL_10, hal_ll_tim_module_num(CCP_MODULE_8)},
    #endif
    #ifdef PWM_CCP8_OC13_RG1_RP113
    {PG1, HAL_LL_TIM_INDEX_2, HAL_LL_CCP_CHANNEL_13, hal_ll_tim_module_num(CCP_MODULE_8)},
    #endif
    #ifdef PWM_CCP8_OC14_RG0_RP112
    {PG0, HAL_LL_TIM_INDEX_2, HAL_LL_CCP_CHANNEL_14, hal_ll_tim_module_num(CCP_MODULE_8)},
    #endif
    #ifdef PWM_CCP8_OC15_RG14_RP126
    {PG14, HAL_LL_TIM_INDEX_2, HAL_LL_CCP_CHANNEL_15, hal_ll_tim_module_num(CCP_MODULE_8)},
    #endif
    #ifdef PWM_CCP8_OC16_RG13_RP125
    {PG13, HAL_LL_TIM_INDEX_2, HAL_LL_CCP_CHANNEL_16, hal_ll_tim_module_num(CCP_MODULE_8)},
    #endif
    #ifdef PWM_CCP8_OC6_RG15_RP127
    {PG15, HAL_LL_TIM_INDEX_2, HAL_LL_CCP_CHANNEL_6, hal_ll_tim_module_num(CCP_MODULE_8)},
    #endif
    #ifdef PWM_CCP8_OC7_RG6_RP118
    {PG6, HAL_LL_TIM_INDEX_2, HAL_LL_CCP_CHANNEL_7, hal_ll_tim_module_num(CCP_MODULE_8)},
    #endif
    #ifdef PWM_CCP9_OC1_RD15_RP79
    {PD15, HAL_LL_TIM_INDEX_2, HAL_LL_CCP_CHANNEL_1, hal_ll_tim_module_num(CCP_MODULE_9)},
    #endif
    #ifdef PWM_CCP9_OC10_RD4_RP68
    {PD4, HAL_LL_TIM_INDEX_2, HAL_LL_CCP_CHANNEL_10, hal_ll_tim_module_num(CCP_MODULE_9)},
    #endif
    #ifdef PWM_CCP9_OC11_RD5_RP69
    {PD5, HAL_LL_TIM_INDEX_2, HAL_LL_CCP_CHANNEL_11, hal_ll_tim_module_num(CCP_MODULE_9)},
    #endif
    #ifdef PWM_CCP9_OC12_RD6_RP70
    {PD6, HAL_LL_TIM_INDEX_2, HAL_LL_CCP_CHANNEL_12, hal_ll_tim_module_num(CCP_MODULE_9)},
    #endif
    #ifdef PWM_CCP9_OC14_RD7_RP71
    {PD7, HAL_LL_TIM_INDEX_2, HAL_LL_CCP_CHANNEL_14, hal_ll_tim_module_num(CCP_MODULE_9)},
    #endif
    #ifdef PWM_CCP9_OC2_RD0_RP64
    {PD0, HAL_LL_TIM_INDEX_2, HAL_LL_CCP_CHANNEL_2, hal_ll_tim_module_num(CCP_MODULE_9)},
    #endif
    #ifdef PWM_CCP9_OC5_RD1_RP65
    {PD1, HAL_LL_TIM_INDEX_2, HAL_LL_CCP_CHANNEL_5, hal_ll_tim_module_num(CCP_MODULE_9)},
    #endif
    #ifdef PWM_CCP9_OC7_RD2_RP66
    {PD2, HAL_LL_TIM_INDEX_2, HAL_LL_CCP_CHANNEL_7, hal_ll_tim_module_num(CCP_MODULE_9)},
    #endif
    #ifdef PWM_CCP9_OC9_RD3_RP67
    {PD3, HAL_LL_TIM_INDEX_2, HAL_LL_CCP_CHANNEL_9, hal_ll_tim_module_num(CCP_MODULE_9)},
    #endif
    #ifdef PWM_CCP3_OC1_RC8_RP56
    {PC8, HAL_LL_TIM_INDEX_2, HAL_LL_CCP_CHANNEL_1, hal_ll_tim_module_num(CCP_MODULE_3)},
    #endif
    #ifdef PWM_CCP4_OC2_RA4_RP20
    {PA4, HAL_LL_TIM_INDEX_2, HAL_LL_CCP_CHANNEL_2, hal_ll_tim_module_num(CCP_MODULE_4)},
    #endif
    #ifdef PWM_CCP5_OC1_RB4_RP36
    {PB4, HAL_LL_TIM_INDEX_2, HAL_LL_CCP_CHANNEL_1, hal_ll_tim_module_num(CCP_MODULE_5)},
    #endif
    #ifdef PWM_CCP5_OC1_RB7_RP39
    {PB7, HAL_LL_TIM_INDEX_2, HAL_LL_CCP_CHANNEL_1, hal_ll_tim_module_num(CCP_MODULE_5)},
    #endif
    #ifdef PWM_CCP5_OC2_RB10_RP42
    {PB10, HAL_LL_TIM_INDEX_2, HAL_LL_CCP_CHANNEL_2, hal_ll_tim_module_num(CCP_MODULE_5)},
    #endif
    #ifdef PWM_CCP3_OC4_RC8_RP56
    {PC8, HAL_LL_TIM_INDEX_2, HAL_LL_CCP_CHANNEL_4, hal_ll_tim_module_num(CCP_MODULE_3)},
    #endif
    #ifdef PWM_CCP1_OC11_RD6_RP70
    {PD6, HAL_LL_TIM_INDEX_2, HAL_LL_CCP_CHANNEL_11, hal_ll_tim_module_num(CCP_MODULE_1)},
    #endif
    #ifdef PWM_CCP1_OC13_RD7_RP71
    {PD7, HAL_LL_TIM_INDEX_2, HAL_LL_CCP_CHANNEL_13, hal_ll_tim_module_num(CCP_MODULE_1)},
    #endif
    #ifdef PWM_CCP1_OC3_RD1_RP65
    {PD1, HAL_LL_TIM_INDEX_2, HAL_LL_CCP_CHANNEL_3, hal_ll_tim_module_num(CCP_MODULE_1)},
    #endif
    #ifdef PWM_CCP1_OC4_RD2_RP66
    {PD2, HAL_LL_TIM_INDEX_2, HAL_LL_CCP_CHANNEL_4, hal_ll_tim_module_num(CCP_MODULE_1)},
    #endif
    #ifdef PWM_CCP1_OC5_RD3_RP67
    {PD3, HAL_LL_TIM_INDEX_2, HAL_LL_CCP_CHANNEL_5, hal_ll_tim_module_num(CCP_MODULE_1)},
    #endif
    #ifdef PWM_CCP1_OC7_RD4_RP68
    {PD4, HAL_LL_TIM_INDEX_2, HAL_LL_CCP_CHANNEL_7, hal_ll_tim_module_num(CCP_MODULE_1)},
    #endif
    #ifdef PWM_CCP1_OC9_RD5_RP69
    {PD5, HAL_LL_TIM_INDEX_2, HAL_LL_CCP_CHANNEL_9, hal_ll_tim_module_num(CCP_MODULE_1)},
    #endif
    #ifdef PWM_CCP2_OC11_RE4_RP84
    {PE4, HAL_LL_TIM_INDEX_2, HAL_LL_CCP_CHANNEL_11, hal_ll_tim_module_num(CCP_MODULE_2)},
    #endif
    #ifdef PWM_CCP2_OC15_RE5_RP85
    {PE5, HAL_LL_TIM_INDEX_2, HAL_LL_CCP_CHANNEL_15, hal_ll_tim_module_num(CCP_MODULE_2)},
    #endif
    #ifdef PWM_CCP2_OC2_RE7_RP87
    {PE7, HAL_LL_TIM_INDEX_2, HAL_LL_CCP_CHANNEL_2, hal_ll_tim_module_num(CCP_MODULE_2)},
    #endif
    #ifdef PWM_CCP2_OC5_RE0_RP80
    {PE0, HAL_LL_TIM_INDEX_2, HAL_LL_CCP_CHANNEL_5, hal_ll_tim_module_num(CCP_MODULE_2)},
    #endif
    #ifdef PWM_CCP2_OC8_RE2_RP82
    {PE2, HAL_LL_TIM_INDEX_2, HAL_LL_CCP_CHANNEL_8, hal_ll_tim_module_num(CCP_MODULE_2)},
    #endif
    #ifdef PWM_CCP3_OC1_RF5_RP101
    {PF5, HAL_LL_TIM_INDEX_2, HAL_LL_CCP_CHANNEL_1, hal_ll_tim_module_num(CCP_MODULE_3)},
    #endif
    #ifdef PWM_CCP3_OC14_RF4_RP100
    {PF4, HAL_LL_TIM_INDEX_2, HAL_LL_CCP_CHANNEL_14, hal_ll_tim_module_num(CCP_MODULE_3)},
    #endif
    #ifdef PWM_CCP3_OC4_RF3_RP99
    {PF3, HAL_LL_TIM_INDEX_2, HAL_LL_CCP_CHANNEL_4, hal_ll_tim_module_num(CCP_MODULE_3)},
    #endif
    #ifdef PWM_CCP3_OC5_RF2_RP98
    {PF2, HAL_LL_TIM_INDEX_2, HAL_LL_CCP_CHANNEL_5, hal_ll_tim_module_num(CCP_MODULE_3)},
    #endif
    #ifdef PWM_CCP3_OC6_RF6_RP102
    {PF6, HAL_LL_TIM_INDEX_2, HAL_LL_CCP_CHANNEL_6, hal_ll_tim_module_num(CCP_MODULE_3)},
    #endif
    #ifdef PWM_CCP3_OC7_RF0_RP96
    {PF0, HAL_LL_TIM_INDEX_2, HAL_LL_CCP_CHANNEL_7, hal_ll_tim_module_num(CCP_MODULE_3)},
    #endif
    #ifdef PWM_CCP3_OC8_RF1_RP97
    {PF1, HAL_LL_TIM_INDEX_2, HAL_LL_CCP_CHANNEL_8, hal_ll_tim_module_num(CCP_MODULE_3)},
    #endif
    #ifdef PWM_CCP5_OC1_RD0_RP64
    {PD0, HAL_LL_TIM_INDEX_2, HAL_LL_CCP_CHANNEL_1, hal_ll_tim_module_num(CCP_MODULE_5)},
    #endif
    #ifdef PWM_CCP5_OC11_RD6_RP70
    {PD6, HAL_LL_TIM_INDEX_2, HAL_LL_CCP_CHANNEL_11, hal_ll_tim_module_num(CCP_MODULE_5)},
    #endif
    #ifdef PWM_CCP5_OC13_RD7_RP71
    {PD7, HAL_LL_TIM_INDEX_2, HAL_LL_CCP_CHANNEL_13, hal_ll_tim_module_num(CCP_MODULE_5)},
    #endif
    #ifdef PWM_CCP5_OC3_RD1_RP65
    {PD1, HAL_LL_TIM_INDEX_2, HAL_LL_CCP_CHANNEL_3, hal_ll_tim_module_num(CCP_MODULE_5)},
    #endif
    #ifdef PWM_CCP5_OC4_RD2_RP66
    {PD2, HAL_LL_TIM_INDEX_2, HAL_LL_CCP_CHANNEL_4, hal_ll_tim_module_num(CCP_MODULE_5)},
    #endif
    #ifdef PWM_CCP5_OC5_RD3_RP67
    {PD3, HAL_LL_TIM_INDEX_2, HAL_LL_CCP_CHANNEL_5, hal_ll_tim_module_num(CCP_MODULE_5)},
    #endif
    #ifdef PWM_CCP5_OC7_RD4_RP68
    {PD4, HAL_LL_TIM_INDEX_2, HAL_LL_CCP_CHANNEL_7, hal_ll_tim_module_num(CCP_MODULE_5)},
    #endif
    #ifdef PWM_CCP5_OC9_RD5_RP69
    {PD5, HAL_LL_TIM_INDEX_2, HAL_LL_CCP_CHANNEL_9, hal_ll_tim_module_num(CCP_MODULE_5)},
    #endif
    #ifdef PWM_CCP6_OC11_RE4_RP84
    {PE4, HAL_LL_TIM_INDEX_2, HAL_LL_CCP_CHANNEL_11, hal_ll_tim_module_num(CCP_MODULE_6)},
    #endif
    #ifdef PWM_CCP6_OC15_RE5_RP85
    {PE5, HAL_LL_TIM_INDEX_2, HAL_LL_CCP_CHANNEL_15, hal_ll_tim_module_num(CCP_MODULE_6)},
    #endif
    #ifdef PWM_CCP6_OC2_RE7_RP87
    {PE7, HAL_LL_TIM_INDEX_2, HAL_LL_CCP_CHANNEL_2, hal_ll_tim_module_num(CCP_MODULE_6)},
    #endif
    #ifdef PWM_CCP6_OC8_RE2_RP82
    {PE2, HAL_LL_TIM_INDEX_2, HAL_LL_CCP_CHANNEL_8, hal_ll_tim_module_num(CCP_MODULE_6)},
    #endif
    #ifdef PWM_CCP7_OC5_RF2_RP98
    {PF2, HAL_LL_TIM_INDEX_2, HAL_LL_CCP_CHANNEL_5, hal_ll_tim_module_num(CCP_MODULE_7)},
    #endif
    #ifdef PWM_CCP7_OC6_RF6_RP102
    {PF6, HAL_LL_TIM_INDEX_2, HAL_LL_CCP_CHANNEL_6, hal_ll_tim_module_num(CCP_MODULE_7)},
    #endif
    #ifdef PWM_CCP7_OC7_RF0_RP96
    {PF0, HAL_LL_TIM_INDEX_2, HAL_LL_CCP_CHANNEL_7, hal_ll_tim_module_num(CCP_MODULE_7)},
    #endif
    #ifdef PWM_CCP7_OC8_RF1_RP97
    {PF1, HAL_LL_TIM_INDEX_2, HAL_LL_CCP_CHANNEL_8, hal_ll_tim_module_num(CCP_MODULE_7)},
    #endif
    #ifdef PWM_CCP8_OC13_RG8_RP120
    {PG8, HAL_LL_TIM_INDEX_2, HAL_LL_CCP_CHANNEL_13, hal_ll_tim_module_num(CCP_MODULE_8)},
    #endif
    #ifdef PWM_CCP8_OC9_RG6_RP118
    {PG6, HAL_LL_TIM_INDEX_2, HAL_LL_CCP_CHANNEL_9, hal_ll_tim_module_num(CCP_MODULE_8)},
    #endif
    #ifdef PWM_CCP9_OC1_RD0_RP64
    {PD0, HAL_LL_TIM_INDEX_2, HAL_LL_CCP_CHANNEL_1, hal_ll_tim_module_num(CCP_MODULE_9)},
    #endif
    #ifdef PWM_CCP9_OC11_RD6_RP70
    {PD6, HAL_LL_TIM_INDEX_2, HAL_LL_CCP_CHANNEL_11, hal_ll_tim_module_num(CCP_MODULE_9)},
    #endif
    #ifdef PWM_CCP9_OC13_RD7_RP71
    {PD7, HAL_LL_TIM_INDEX_2, HAL_LL_CCP_CHANNEL_13, hal_ll_tim_module_num(CCP_MODULE_9)},
    #endif
    #ifdef PWM_CCP9_OC3_RD1_RP65
    {PD1, HAL_LL_TIM_INDEX_2, HAL_LL_CCP_CHANNEL_3, hal_ll_tim_module_num(CCP_MODULE_9)},
    #endif
    #ifdef PWM_CCP9_OC4_RD2_RP66
    {PD2, HAL_LL_TIM_INDEX_2, HAL_LL_CCP_CHANNEL_4, hal_ll_tim_module_num(CCP_MODULE_9)},
    #endif
    #ifdef PWM_CCP9_OC5_RD3_RP67
    {PD3, HAL_LL_TIM_INDEX_2, HAL_LL_CCP_CHANNEL_5, hal_ll_tim_module_num(CCP_MODULE_9)},
    #endif
    #ifdef PWM_CCP9_OC7_RD4_RP68
    {PD4, HAL_LL_TIM_INDEX_2, HAL_LL_CCP_CHANNEL_7, hal_ll_tim_module_num(CCP_MODULE_9)},
    #endif
    #ifdef PWM_CCP9_OC9_RD5_RP69
    {PD5, HAL_LL_TIM_INDEX_2, HAL_LL_CCP_CHANNEL_9, hal_ll_tim_module_num(CCP_MODULE_9)},
    #endif
    #ifdef PWM_CCP2_OC11_RE2_RP82
    {PE2, HAL_LL_TIM_INDEX_2, HAL_LL_CCP_CHANNEL_11, hal_ll_tim_module_num(CCP_MODULE_2)},
    #endif
    #ifdef PWM_CCP2_OC15_RE4_RP84
    {PE4, HAL_LL_TIM_INDEX_2, HAL_LL_CCP_CHANNEL_15, hal_ll_tim_module_num(CCP_MODULE_2)},
    #endif
    #ifdef PWM_CCP2_OC3_RE7_RP87
    {PE7, HAL_LL_TIM_INDEX_2, HAL_LL_CCP_CHANNEL_3, hal_ll_tim_module_num(CCP_MODULE_2)},
    #endif
    #ifdef PWM_CCP3_OC10_RF2_RP98
    {PF2, HAL_LL_TIM_INDEX_2, HAL_LL_CCP_CHANNEL_10, hal_ll_tim_module_num(CCP_MODULE_3)},
    #endif
    #ifdef PWM_CCP3_OC11_RF6_RP102
    {PF6, HAL_LL_TIM_INDEX_2, HAL_LL_CCP_CHANNEL_11, hal_ll_tim_module_num(CCP_MODULE_3)},
    #endif
    #ifdef PWM_CCP3_OC12_RF0_RP96
    {PF0, HAL_LL_TIM_INDEX_2, HAL_LL_CCP_CHANNEL_12, hal_ll_tim_module_num(CCP_MODULE_3)},
    #endif
    #ifdef PWM_CCP3_OC13_RF1_RP97
    {PF1, HAL_LL_TIM_INDEX_2, HAL_LL_CCP_CHANNEL_13, hal_ll_tim_module_num(CCP_MODULE_3)},
    #endif
    #ifdef PWM_CCP3_OC3_RF4_RP100
    {PF4, HAL_LL_TIM_INDEX_2, HAL_LL_CCP_CHANNEL_3, hal_ll_tim_module_num(CCP_MODULE_3)},
    #endif
    #ifdef PWM_CCP3_OC6_RF5_RP101
    {PF5, HAL_LL_TIM_INDEX_2, HAL_LL_CCP_CHANNEL_6, hal_ll_tim_module_num(CCP_MODULE_3)},
    #endif
    #ifdef PWM_CCP3_OC9_RF3_RP99
    {PF3, HAL_LL_TIM_INDEX_2, HAL_LL_CCP_CHANNEL_9, hal_ll_tim_module_num(CCP_MODULE_3)},
    #endif
    #ifdef PWM_CCP4_OC14_RG6_RP118
    {PG6, HAL_LL_TIM_INDEX_2, HAL_LL_CCP_CHANNEL_14, hal_ll_tim_module_num(CCP_MODULE_4)},
    #endif
    #ifdef PWM_CCP5_OC10_RD3_RP67
    {PD3, HAL_LL_TIM_INDEX_2, HAL_LL_CCP_CHANNEL_10, hal_ll_tim_module_num(CCP_MODULE_5)},
    #endif
    #ifdef PWM_CCP5_OC12_RD4_RP68
    {PD4, HAL_LL_TIM_INDEX_2, HAL_LL_CCP_CHANNEL_12, hal_ll_tim_module_num(CCP_MODULE_5)},
    #endif
    #ifdef PWM_CCP5_OC14_RD5_RP69
    {PD5, HAL_LL_TIM_INDEX_2, HAL_LL_CCP_CHANNEL_14, hal_ll_tim_module_num(CCP_MODULE_5)},
    #endif
    #ifdef PWM_CCP5_OC16_RD6_RP70
    {PD6, HAL_LL_TIM_INDEX_2, HAL_LL_CCP_CHANNEL_16, hal_ll_tim_module_num(CCP_MODULE_5)},
    #endif
    #ifdef PWM_CCP5_OC2_RD7_RP71
    {PD7, HAL_LL_TIM_INDEX_2, HAL_LL_CCP_CHANNEL_2, hal_ll_tim_module_num(CCP_MODULE_5)},
    #endif
    #ifdef PWM_CCP5_OC8_RD1_RP65
    {PD1, HAL_LL_TIM_INDEX_2, HAL_LL_CCP_CHANNEL_8, hal_ll_tim_module_num(CCP_MODULE_5)},
    #endif
    #ifdef PWM_CCP5_OC9_RD2_RP66
    {PD2, HAL_LL_TIM_INDEX_2, HAL_LL_CCP_CHANNEL_9, hal_ll_tim_module_num(CCP_MODULE_5)},
    #endif
    #ifdef PWM_CCP6_OC12_RE0_RP80
    {PE0, HAL_LL_TIM_INDEX_2, HAL_LL_CCP_CHANNEL_12, hal_ll_tim_module_num(CCP_MODULE_6)},
    #endif
    #ifdef PWM_CCP6_OC16_RE2_RP82
    {PE2, HAL_LL_TIM_INDEX_2, HAL_LL_CCP_CHANNEL_16, hal_ll_tim_module_num(CCP_MODULE_6)},
    #endif
    #ifdef PWM_CCP6_OC4_RE4_RP84
    {PE4, HAL_LL_TIM_INDEX_2, HAL_LL_CCP_CHANNEL_4, hal_ll_tim_module_num(CCP_MODULE_6)},
    #endif
    #ifdef PWM_CCP6_OC4_RE5_RP85
    {PE5, HAL_LL_TIM_INDEX_2, HAL_LL_CCP_CHANNEL_4, hal_ll_tim_module_num(CCP_MODULE_6)},
    #endif
    #ifdef PWM_CCP6_OC8_RE7_RP87
    {PE7, HAL_LL_TIM_INDEX_2, HAL_LL_CCP_CHANNEL_8, hal_ll_tim_module_num(CCP_MODULE_6)},
    #endif
    #ifdef PWM_CCP7_OC1_RF0_RP96
    {PF0, HAL_LL_TIM_INDEX_2, HAL_LL_CCP_CHANNEL_1, hal_ll_tim_module_num(CCP_MODULE_7)},
    #endif
    #ifdef PWM_CCP7_OC11_RF5_RP101
    {PF5, HAL_LL_TIM_INDEX_2, HAL_LL_CCP_CHANNEL_11, hal_ll_tim_module_num(CCP_MODULE_7)},
    #endif
    #ifdef PWM_CCP7_OC15_RF2_RP98
    {PF2, HAL_LL_TIM_INDEX_2, HAL_LL_CCP_CHANNEL_15, hal_ll_tim_module_num(CCP_MODULE_7)},
    #endif
    #ifdef PWM_CCP7_OC16_RF6_RP102
    {PF6, HAL_LL_TIM_INDEX_2, HAL_LL_CCP_CHANNEL_16, hal_ll_tim_module_num(CCP_MODULE_7)},
    #endif
    #ifdef PWM_CCP7_OC2_RF1_RP97
    {PF1, HAL_LL_TIM_INDEX_2, HAL_LL_CCP_CHANNEL_2, hal_ll_tim_module_num(CCP_MODULE_7)},
    #endif
    #ifdef PWM_CCP7_OC8_RF4_RP100
    {PF4, HAL_LL_TIM_INDEX_2, HAL_LL_CCP_CHANNEL_8, hal_ll_tim_module_num(CCP_MODULE_7)},
    #endif
    #ifdef PWM_CCP8_OC3_RG6_RP118
    {PG6, HAL_LL_TIM_INDEX_2, HAL_LL_CCP_CHANNEL_3, hal_ll_tim_module_num(CCP_MODULE_8)},
    #endif
    #ifdef PWM_CCP8_OC7_RG8_RP120
    {PG8, HAL_LL_TIM_INDEX_2, HAL_LL_CCP_CHANNEL_7, hal_ll_tim_module_num(CCP_MODULE_8)},
    #endif
    #ifdef PWM_CCP9_OC1_RD4_RP68
    {PD4, HAL_LL_TIM_INDEX_2, HAL_LL_CCP_CHANNEL_1, hal_ll_tim_module_num(CCP_MODULE_9)},
    #endif
    #ifdef PWM_CCP9_OC11_RD0_RP64
    {PD0, HAL_LL_TIM_INDEX_2, HAL_LL_CCP_CHANNEL_11, hal_ll_tim_module_num(CCP_MODULE_9)},
    #endif
    #ifdef PWM_CCP9_OC14_RD2_RP66
    {PD2, HAL_LL_TIM_INDEX_2, HAL_LL_CCP_CHANNEL_14, hal_ll_tim_module_num(CCP_MODULE_9)},
    #endif
    #ifdef PWM_CCP9_OC15_RD3_RP67
    {PD3, HAL_LL_TIM_INDEX_2, HAL_LL_CCP_CHANNEL_15, hal_ll_tim_module_num(CCP_MODULE_9)},
    #endif
    #ifdef PWM_CCP9_OC3_RD5_RP69
    {PD5, HAL_LL_TIM_INDEX_2, HAL_LL_CCP_CHANNEL_3, hal_ll_tim_module_num(CCP_MODULE_9)},
    #endif
    #ifdef PWM_CCP9_OC5_RD6_RP70
    {PD6, HAL_LL_TIM_INDEX_2, HAL_LL_CCP_CHANNEL_5, hal_ll_tim_module_num(CCP_MODULE_9)},
    #endif
    #ifdef PWM_CCP9_OC7_RD7_RP71
    {PD7, HAL_LL_TIM_INDEX_2, HAL_LL_CCP_CHANNEL_7, hal_ll_tim_module_num(CCP_MODULE_9)},
    #endif
    #ifdef PWM_CCP4_OC3_RB5_RP37
    {PB5, HAL_LL_TIM_INDEX_2, HAL_LL_CCP_CHANNEL_3, hal_ll_tim_module_num(CCP_MODULE_4)},
    #endif
    #ifdef PWM_CCP2_OC3_RB4_RP36
    {PB4, HAL_LL_TIM_INDEX_2, HAL_LL_CCP_CHANNEL_3, hal_ll_tim_module_num(CCP_MODULE_2)},
    #endif
    #ifdef PWM_CCP3_OC1_RC0_RP48
    {PC0, HAL_LL_TIM_INDEX_2, HAL_LL_CCP_CHANNEL_1, hal_ll_tim_module_num(CCP_MODULE_3)},
    #endif
    #ifdef PWM_CCP3_OC3_RC7_RP55
    {PC7, HAL_LL_TIM_INDEX_2, HAL_LL_CCP_CHANNEL_3, hal_ll_tim_module_num(CCP_MODULE_3)},
    #endif
    #ifdef PWM_CCP5_OC2_RB11_RP43
    {PB11, HAL_LL_TIM_INDEX_2, HAL_LL_CCP_CHANNEL_2, hal_ll_tim_module_num(CCP_MODULE_5)},
    #endif
    #ifdef PWM_CCP5_OC3_RB9_RP41
    {PB9, HAL_LL_TIM_INDEX_2, HAL_LL_CCP_CHANNEL_3, hal_ll_tim_module_num(CCP_MODULE_5)},
    #endif
    #ifdef PWM_CCP4_OC1_RD6_RP70
    {PD6, HAL_LL_TIM_INDEX_2, HAL_LL_CCP_CHANNEL_1, hal_ll_tim_module_num(CCP_MODULE_4)},
    #endif
    #ifdef PWM_CCP4_OC4_RD5_RP69
    {PD5, HAL_LL_TIM_INDEX_2, HAL_LL_CCP_CHANNEL_4, hal_ll_tim_module_num(CCP_MODULE_4)},
    #endif
    #ifdef PWM_CCP5_OC2_RF1_RP97
    {PF1, HAL_LL_TIM_INDEX_2, HAL_LL_CCP_CHANNEL_2, hal_ll_tim_module_num(CCP_MODULE_5)},
    #endif
    #ifdef PWM_CCP1_OC1_RB0_RP0
    {PB0, HAL_LL_TIM_INDEX_2, HAL_LL_CCP_CHANNEL_1, hal_ll_tim_module_num(CCP_MODULE_1)},
    #endif
    #ifdef PWM_CCP1_OC1_RB1_RP1
    {PB1, HAL_LL_TIM_INDEX_2, HAL_LL_CCP_CHANNEL_1, hal_ll_tim_module_num(CCP_MODULE_1)},
    #endif
    #ifdef PWM_CCP1_OC1_RB10_RP10
    {PB10, HAL_LL_TIM_INDEX_2, HAL_LL_CCP_CHANNEL_1, hal_ll_tim_module_num(CCP_MODULE_1)},
    #endif
    #ifdef PWM_CCP1_OC1_RB11_RP11
    {PB11, HAL_LL_TIM_INDEX_2, HAL_LL_CCP_CHANNEL_1, hal_ll_tim_module_num(CCP_MODULE_1)},
    #endif
    #ifdef PWM_CCP1_OC1_RB12_RP12
    {PB12, HAL_LL_TIM_INDEX_2, HAL_LL_CCP_CHANNEL_1, hal_ll_tim_module_num(CCP_MODULE_1)},
    #endif
    #ifdef PWM_CCP1_OC1_RB13_RP13
    {PB13, HAL_LL_TIM_INDEX_2, HAL_LL_CCP_CHANNEL_1, hal_ll_tim_module_num(CCP_MODULE_1)},
    #endif
    #ifdef PWM_CCP1_OC1_RB14_RP14
    {PB14, HAL_LL_TIM_INDEX_2, HAL_LL_CCP_CHANNEL_1, hal_ll_tim_module_num(CCP_MODULE_1)},
    #endif
    #ifdef PWM_CCP1_OC1_RB15_RP15
    {PB15, HAL_LL_TIM_INDEX_2, HAL_LL_CCP_CHANNEL_1, hal_ll_tim_module_num(CCP_MODULE_1)},
    #endif
    #ifdef PWM_CCP1_OC1_RB2_RP2
    {PB2, HAL_LL_TIM_INDEX_2, HAL_LL_CCP_CHANNEL_1, hal_ll_tim_module_num(CCP_MODULE_1)},
    #endif
    #ifdef PWM_CCP1_OC1_RB3_RP3
    {PB3, HAL_LL_TIM_INDEX_2, HAL_LL_CCP_CHANNEL_1, hal_ll_tim_module_num(CCP_MODULE_1)},
    #endif
    #ifdef PWM_CCP1_OC1_RB4_RP4
    {PB4, HAL_LL_TIM_INDEX_2, HAL_LL_CCP_CHANNEL_1, hal_ll_tim_module_num(CCP_MODULE_1)},
    #endif
    #ifdef PWM_CCP1_OC1_RB5_RP5
    {PB5, HAL_LL_TIM_INDEX_2, HAL_LL_CCP_CHANNEL_1, hal_ll_tim_module_num(CCP_MODULE_1)},
    #endif
    #ifdef PWM_CCP1_OC1_RB6_RP6
    {PB6, HAL_LL_TIM_INDEX_2, HAL_LL_CCP_CHANNEL_1, hal_ll_tim_module_num(CCP_MODULE_1)},
    #endif
    #ifdef PWM_CCP1_OC1_RB7_RP7
    {PB7, HAL_LL_TIM_INDEX_2, HAL_LL_CCP_CHANNEL_1, hal_ll_tim_module_num(CCP_MODULE_1)},
    #endif
    #ifdef PWM_CCP1_OC1_RB8_RP8
    {PB8, HAL_LL_TIM_INDEX_2, HAL_LL_CCP_CHANNEL_1, hal_ll_tim_module_num(CCP_MODULE_1)},
    #endif
    #ifdef PWM_CCP1_OC1_RB9_RP9
    {PB9, HAL_LL_TIM_INDEX_2, HAL_LL_CCP_CHANNEL_1, hal_ll_tim_module_num(CCP_MODULE_1)},
    #endif
    #ifdef PWM_CCP1_OC2_RB0_RP0
    {PB0, HAL_LL_TIM_INDEX_2, HAL_LL_CCP_CHANNEL_2, hal_ll_tim_module_num(CCP_MODULE_1)},
    #endif
    #ifdef PWM_CCP1_OC2_RB1_RP1
    {PB1, HAL_LL_TIM_INDEX_2, HAL_LL_CCP_CHANNEL_2, hal_ll_tim_module_num(CCP_MODULE_1)},
    #endif
    #ifdef PWM_CCP1_OC2_RB10_RP10
    {PB10, HAL_LL_TIM_INDEX_2, HAL_LL_CCP_CHANNEL_2, hal_ll_tim_module_num(CCP_MODULE_1)},
    #endif
    #ifdef PWM_CCP1_OC2_RB11_RP11
    {PB11, HAL_LL_TIM_INDEX_2, HAL_LL_CCP_CHANNEL_2, hal_ll_tim_module_num(CCP_MODULE_1)},
    #endif
    #ifdef PWM_CCP1_OC2_RB12_RP12
    {PB12, HAL_LL_TIM_INDEX_2, HAL_LL_CCP_CHANNEL_2, hal_ll_tim_module_num(CCP_MODULE_1)},
    #endif
    #ifdef PWM_CCP1_OC2_RB13_RP13
    {PB13, HAL_LL_TIM_INDEX_2, HAL_LL_CCP_CHANNEL_2, hal_ll_tim_module_num(CCP_MODULE_1)},
    #endif
    #ifdef PWM_CCP1_OC2_RB14_RP14
    {PB14, HAL_LL_TIM_INDEX_2, HAL_LL_CCP_CHANNEL_2, hal_ll_tim_module_num(CCP_MODULE_1)},
    #endif
    #ifdef PWM_CCP1_OC2_RB15_RP15
    {PB15, HAL_LL_TIM_INDEX_2, HAL_LL_CCP_CHANNEL_2, hal_ll_tim_module_num(CCP_MODULE_1)},
    #endif
    #ifdef PWM_CCP1_OC2_RB2_RP2
    {PB2, HAL_LL_TIM_INDEX_2, HAL_LL_CCP_CHANNEL_2, hal_ll_tim_module_num(CCP_MODULE_1)},
    #endif
    #ifdef PWM_CCP1_OC2_RB3_RP3
    {PB3, HAL_LL_TIM_INDEX_2, HAL_LL_CCP_CHANNEL_2, hal_ll_tim_module_num(CCP_MODULE_1)},
    #endif
    #ifdef PWM_CCP1_OC2_RB4_RP4
    {PB4, HAL_LL_TIM_INDEX_2, HAL_LL_CCP_CHANNEL_2, hal_ll_tim_module_num(CCP_MODULE_1)},
    #endif
    #ifdef PWM_CCP1_OC2_RB5_RP5
    {PB5, HAL_LL_TIM_INDEX_2, HAL_LL_CCP_CHANNEL_2, hal_ll_tim_module_num(CCP_MODULE_1)},
    #endif
    #ifdef PWM_CCP1_OC2_RB6_RP6
    {PB6, HAL_LL_TIM_INDEX_2, HAL_LL_CCP_CHANNEL_2, hal_ll_tim_module_num(CCP_MODULE_1)},
    #endif
    #ifdef PWM_CCP1_OC2_RB7_RP7
    {PB7, HAL_LL_TIM_INDEX_2, HAL_LL_CCP_CHANNEL_2, hal_ll_tim_module_num(CCP_MODULE_1)},
    #endif
    #ifdef PWM_CCP1_OC2_RB8_RP8
    {PB8, HAL_LL_TIM_INDEX_2, HAL_LL_CCP_CHANNEL_2, hal_ll_tim_module_num(CCP_MODULE_1)},
    #endif
    #ifdef PWM_CCP1_OC2_RB9_RP9
    {PB9, HAL_LL_TIM_INDEX_2, HAL_LL_CCP_CHANNEL_2, hal_ll_tim_module_num(CCP_MODULE_1)},
    #endif
    #ifdef PWM_CCP1_OC3_RB0_RP0
    {PB0, HAL_LL_TIM_INDEX_2, HAL_LL_CCP_CHANNEL_3, hal_ll_tim_module_num(CCP_MODULE_1)},
    #endif
    #ifdef PWM_CCP1_OC3_RB1_RP1
    {PB1, HAL_LL_TIM_INDEX_2, HAL_LL_CCP_CHANNEL_3, hal_ll_tim_module_num(CCP_MODULE_1)},
    #endif
    #ifdef PWM_CCP1_OC3_RB10_RP10
    {PB10, HAL_LL_TIM_INDEX_2, HAL_LL_CCP_CHANNEL_3, hal_ll_tim_module_num(CCP_MODULE_1)},
    #endif
    #ifdef PWM_CCP1_OC3_RB11_RP11
    {PB11, HAL_LL_TIM_INDEX_2, HAL_LL_CCP_CHANNEL_3, hal_ll_tim_module_num(CCP_MODULE_1)},
    #endif
    #ifdef PWM_CCP1_OC3_RB12_RP12
    {PB12, HAL_LL_TIM_INDEX_2, HAL_LL_CCP_CHANNEL_3, hal_ll_tim_module_num(CCP_MODULE_1)},
    #endif
    #ifdef PWM_CCP1_OC3_RB13_RP13
    {PB13, HAL_LL_TIM_INDEX_2, HAL_LL_CCP_CHANNEL_3, hal_ll_tim_module_num(CCP_MODULE_1)},
    #endif
    #ifdef PWM_CCP1_OC3_RB14_RP14
    {PB14, HAL_LL_TIM_INDEX_2, HAL_LL_CCP_CHANNEL_3, hal_ll_tim_module_num(CCP_MODULE_1)},
    #endif
    #ifdef PWM_CCP1_OC3_RB15_RP15
    {PB15, HAL_LL_TIM_INDEX_2, HAL_LL_CCP_CHANNEL_3, hal_ll_tim_module_num(CCP_MODULE_1)},
    #endif
    #ifdef PWM_CCP1_OC3_RB2_RP2
    {PB2, HAL_LL_TIM_INDEX_2, HAL_LL_CCP_CHANNEL_3, hal_ll_tim_module_num(CCP_MODULE_1)},
    #endif
    #ifdef PWM_CCP1_OC3_RB3_RP3
    {PB3, HAL_LL_TIM_INDEX_2, HAL_LL_CCP_CHANNEL_3, hal_ll_tim_module_num(CCP_MODULE_1)},
    #endif
    #ifdef PWM_CCP1_OC3_RB4_RP4
    {PB4, HAL_LL_TIM_INDEX_2, HAL_LL_CCP_CHANNEL_3, hal_ll_tim_module_num(CCP_MODULE_1)},
    #endif
    #ifdef PWM_CCP1_OC3_RB5_RP5
    {PB5, HAL_LL_TIM_INDEX_2, HAL_LL_CCP_CHANNEL_3, hal_ll_tim_module_num(CCP_MODULE_1)},
    #endif
    #ifdef PWM_CCP1_OC3_RB6_RP6
    {PB6, HAL_LL_TIM_INDEX_2, HAL_LL_CCP_CHANNEL_3, hal_ll_tim_module_num(CCP_MODULE_1)},
    #endif
    #ifdef PWM_CCP1_OC3_RB7_RP7
    {PB7, HAL_LL_TIM_INDEX_2, HAL_LL_CCP_CHANNEL_3, hal_ll_tim_module_num(CCP_MODULE_1)},
    #endif
    #ifdef PWM_CCP1_OC3_RB8_RP8
    {PB8, HAL_LL_TIM_INDEX_2, HAL_LL_CCP_CHANNEL_3, hal_ll_tim_module_num(CCP_MODULE_1)},
    #endif
    #ifdef PWM_CCP1_OC3_RB9_RP9
    {PB9, HAL_LL_TIM_INDEX_2, HAL_LL_CCP_CHANNEL_3, hal_ll_tim_module_num(CCP_MODULE_1)},
    #endif
    #ifdef PWM_CCP1_OC4_RB0_RP0
    {PB0, HAL_LL_TIM_INDEX_2, HAL_LL_CCP_CHANNEL_4, hal_ll_tim_module_num(CCP_MODULE_1)},
    #endif
    #ifdef PWM_CCP1_OC4_RB1_RP1
    {PB1, HAL_LL_TIM_INDEX_2, HAL_LL_CCP_CHANNEL_4, hal_ll_tim_module_num(CCP_MODULE_1)},
    #endif
    #ifdef PWM_CCP1_OC4_RB10_RP10
    {PB10, HAL_LL_TIM_INDEX_2, HAL_LL_CCP_CHANNEL_4, hal_ll_tim_module_num(CCP_MODULE_1)},
    #endif
    #ifdef PWM_CCP1_OC4_RB11_RP11
    {PB11, HAL_LL_TIM_INDEX_2, HAL_LL_CCP_CHANNEL_4, hal_ll_tim_module_num(CCP_MODULE_1)},
    #endif
    #ifdef PWM_CCP1_OC4_RB12_RP12
    {PB12, HAL_LL_TIM_INDEX_2, HAL_LL_CCP_CHANNEL_4, hal_ll_tim_module_num(CCP_MODULE_1)},
    #endif
    #ifdef PWM_CCP1_OC4_RB13_RP13
    {PB13, HAL_LL_TIM_INDEX_2, HAL_LL_CCP_CHANNEL_4, hal_ll_tim_module_num(CCP_MODULE_1)},
    #endif
    #ifdef PWM_CCP1_OC4_RB14_RP14
    {PB14, HAL_LL_TIM_INDEX_2, HAL_LL_CCP_CHANNEL_4, hal_ll_tim_module_num(CCP_MODULE_1)},
    #endif
    #ifdef PWM_CCP1_OC4_RB15_RP15
    {PB15, HAL_LL_TIM_INDEX_2, HAL_LL_CCP_CHANNEL_4, hal_ll_tim_module_num(CCP_MODULE_1)},
    #endif
    #ifdef PWM_CCP1_OC4_RB2_RP2
    {PB2, HAL_LL_TIM_INDEX_2, HAL_LL_CCP_CHANNEL_4, hal_ll_tim_module_num(CCP_MODULE_1)},
    #endif
    #ifdef PWM_CCP1_OC4_RB3_RP3
    {PB3, HAL_LL_TIM_INDEX_2, HAL_LL_CCP_CHANNEL_4, hal_ll_tim_module_num(CCP_MODULE_1)},
    #endif
    #ifdef PWM_CCP1_OC4_RB4_RP4
    {PB4, HAL_LL_TIM_INDEX_2, HAL_LL_CCP_CHANNEL_4, hal_ll_tim_module_num(CCP_MODULE_1)},
    #endif
    #ifdef PWM_CCP1_OC4_RB5_RP5
    {PB5, HAL_LL_TIM_INDEX_2, HAL_LL_CCP_CHANNEL_4, hal_ll_tim_module_num(CCP_MODULE_1)},
    #endif
    #ifdef PWM_CCP1_OC4_RB6_RP6
    {PB6, HAL_LL_TIM_INDEX_2, HAL_LL_CCP_CHANNEL_4, hal_ll_tim_module_num(CCP_MODULE_1)},
    #endif
    #ifdef PWM_CCP1_OC4_RB7_RP7
    {PB7, HAL_LL_TIM_INDEX_2, HAL_LL_CCP_CHANNEL_4, hal_ll_tim_module_num(CCP_MODULE_1)},
    #endif
    #ifdef PWM_CCP1_OC4_RB8_RP8
    {PB8, HAL_LL_TIM_INDEX_2, HAL_LL_CCP_CHANNEL_4, hal_ll_tim_module_num(CCP_MODULE_1)},
    #endif
    #ifdef PWM_CCP1_OC4_RB9_RP9
    {PB9, HAL_LL_TIM_INDEX_2, HAL_LL_CCP_CHANNEL_4, hal_ll_tim_module_num(CCP_MODULE_1)},
    #endif
    #ifdef PWM_CCP2_OC1_RB0_RP0
    {PB0, HAL_LL_TIM_INDEX_2, HAL_LL_CCP_CHANNEL_1, hal_ll_tim_module_num(CCP_MODULE_2)},
    #endif
    #ifdef PWM_CCP2_OC1_RB1_RP1
    {PB1, HAL_LL_TIM_INDEX_2, HAL_LL_CCP_CHANNEL_1, hal_ll_tim_module_num(CCP_MODULE_2)},
    #endif
    #ifdef PWM_CCP2_OC1_RB10_RP10
    {PB10, HAL_LL_TIM_INDEX_2, HAL_LL_CCP_CHANNEL_1, hal_ll_tim_module_num(CCP_MODULE_2)},
    #endif
    #ifdef PWM_CCP2_OC1_RB11_RP11
    {PB11, HAL_LL_TIM_INDEX_2, HAL_LL_CCP_CHANNEL_1, hal_ll_tim_module_num(CCP_MODULE_2)},
    #endif
    #ifdef PWM_CCP2_OC1_RB12_RP12
    {PB12, HAL_LL_TIM_INDEX_2, HAL_LL_CCP_CHANNEL_1, hal_ll_tim_module_num(CCP_MODULE_2)},
    #endif
    #ifdef PWM_CCP2_OC1_RB13_RP13
    {PB13, HAL_LL_TIM_INDEX_2, HAL_LL_CCP_CHANNEL_1, hal_ll_tim_module_num(CCP_MODULE_2)},
    #endif
    #ifdef PWM_CCP2_OC1_RB14_RP14
    {PB14, HAL_LL_TIM_INDEX_2, HAL_LL_CCP_CHANNEL_1, hal_ll_tim_module_num(CCP_MODULE_2)},
    #endif
    #ifdef PWM_CCP2_OC1_RB15_RP15
    {PB15, HAL_LL_TIM_INDEX_2, HAL_LL_CCP_CHANNEL_1, hal_ll_tim_module_num(CCP_MODULE_2)},
    #endif
    #ifdef PWM_CCP2_OC1_RB2_RP2
    {PB2, HAL_LL_TIM_INDEX_2, HAL_LL_CCP_CHANNEL_1, hal_ll_tim_module_num(CCP_MODULE_2)},
    #endif
    #ifdef PWM_CCP2_OC1_RB3_RP3
    {PB3, HAL_LL_TIM_INDEX_2, HAL_LL_CCP_CHANNEL_1, hal_ll_tim_module_num(CCP_MODULE_2)},
    #endif
    #ifdef PWM_CCP2_OC1_RB4_RP4
    {PB4, HAL_LL_TIM_INDEX_2, HAL_LL_CCP_CHANNEL_1, hal_ll_tim_module_num(CCP_MODULE_2)},
    #endif
    #ifdef PWM_CCP2_OC1_RB5_RP5
    {PB5, HAL_LL_TIM_INDEX_2, HAL_LL_CCP_CHANNEL_1, hal_ll_tim_module_num(CCP_MODULE_2)},
    #endif
    #ifdef PWM_CCP2_OC1_RB6_RP6
    {PB6, HAL_LL_TIM_INDEX_2, HAL_LL_CCP_CHANNEL_1, hal_ll_tim_module_num(CCP_MODULE_2)},
    #endif
    #ifdef PWM_CCP2_OC1_RB7_RP7
    {PB7, HAL_LL_TIM_INDEX_2, HAL_LL_CCP_CHANNEL_1, hal_ll_tim_module_num(CCP_MODULE_2)},
    #endif
    #ifdef PWM_CCP2_OC1_RB8_RP8
    {PB8, HAL_LL_TIM_INDEX_2, HAL_LL_CCP_CHANNEL_1, hal_ll_tim_module_num(CCP_MODULE_2)},
    #endif
    #ifdef PWM_CCP2_OC1_RB9_RP9
    {PB9, HAL_LL_TIM_INDEX_2, HAL_LL_CCP_CHANNEL_1, hal_ll_tim_module_num(CCP_MODULE_2)},
    #endif
    #ifdef PWM_CCP2_OC2_RB0_RP0
    {PB0, HAL_LL_TIM_INDEX_2, HAL_LL_CCP_CHANNEL_2, hal_ll_tim_module_num(CCP_MODULE_2)},
    #endif
    #ifdef PWM_CCP2_OC2_RB1_RP1
    {PB1, HAL_LL_TIM_INDEX_2, HAL_LL_CCP_CHANNEL_2, hal_ll_tim_module_num(CCP_MODULE_2)},
    #endif
    #ifdef PWM_CCP2_OC2_RB10_RP10
    {PB10, HAL_LL_TIM_INDEX_2, HAL_LL_CCP_CHANNEL_2, hal_ll_tim_module_num(CCP_MODULE_2)},
    #endif
    #ifdef PWM_CCP2_OC2_RB11_RP11
    {PB11, HAL_LL_TIM_INDEX_2, HAL_LL_CCP_CHANNEL_2, hal_ll_tim_module_num(CCP_MODULE_2)},
    #endif
    #ifdef PWM_CCP2_OC2_RB12_RP12
    {PB12, HAL_LL_TIM_INDEX_2, HAL_LL_CCP_CHANNEL_2, hal_ll_tim_module_num(CCP_MODULE_2)},
    #endif
    #ifdef PWM_CCP2_OC2_RB13_RP13
    {PB13, HAL_LL_TIM_INDEX_2, HAL_LL_CCP_CHANNEL_2, hal_ll_tim_module_num(CCP_MODULE_2)},
    #endif
    #ifdef PWM_CCP2_OC2_RB14_RP14
    {PB14, HAL_LL_TIM_INDEX_2, HAL_LL_CCP_CHANNEL_2, hal_ll_tim_module_num(CCP_MODULE_2)},
    #endif
    #ifdef PWM_CCP2_OC2_RB15_RP15
    {PB15, HAL_LL_TIM_INDEX_2, HAL_LL_CCP_CHANNEL_2, hal_ll_tim_module_num(CCP_MODULE_2)},
    #endif
    #ifdef PWM_CCP2_OC2_RB2_RP2
    {PB2, HAL_LL_TIM_INDEX_2, HAL_LL_CCP_CHANNEL_2, hal_ll_tim_module_num(CCP_MODULE_2)},
    #endif
    #ifdef PWM_CCP2_OC2_RB3_RP3
    {PB3, HAL_LL_TIM_INDEX_2, HAL_LL_CCP_CHANNEL_2, hal_ll_tim_module_num(CCP_MODULE_2)},
    #endif
    #ifdef PWM_CCP2_OC2_RB4_RP4
    {PB4, HAL_LL_TIM_INDEX_2, HAL_LL_CCP_CHANNEL_2, hal_ll_tim_module_num(CCP_MODULE_2)},
    #endif
    #ifdef PWM_CCP2_OC2_RB5_RP5
    {PB5, HAL_LL_TIM_INDEX_2, HAL_LL_CCP_CHANNEL_2, hal_ll_tim_module_num(CCP_MODULE_2)},
    #endif
    #ifdef PWM_CCP2_OC2_RB6_RP6
    {PB6, HAL_LL_TIM_INDEX_2, HAL_LL_CCP_CHANNEL_2, hal_ll_tim_module_num(CCP_MODULE_2)},
    #endif
    #ifdef PWM_CCP2_OC2_RB7_RP7
    {PB7, HAL_LL_TIM_INDEX_2, HAL_LL_CCP_CHANNEL_2, hal_ll_tim_module_num(CCP_MODULE_2)},
    #endif
    #ifdef PWM_CCP2_OC2_RB8_RP8
    {PB8, HAL_LL_TIM_INDEX_2, HAL_LL_CCP_CHANNEL_2, hal_ll_tim_module_num(CCP_MODULE_2)},
    #endif
    #ifdef PWM_CCP2_OC2_RB9_RP9
    {PB9, HAL_LL_TIM_INDEX_2, HAL_LL_CCP_CHANNEL_2, hal_ll_tim_module_num(CCP_MODULE_2)},
    #endif
    #ifdef PWM_CCP2_OC3_RB0_RP0
    {PB0, HAL_LL_TIM_INDEX_2, HAL_LL_CCP_CHANNEL_3, hal_ll_tim_module_num(CCP_MODULE_2)},
    #endif
    #ifdef PWM_CCP2_OC3_RB1_RP1
    {PB1, HAL_LL_TIM_INDEX_2, HAL_LL_CCP_CHANNEL_3, hal_ll_tim_module_num(CCP_MODULE_2)},
    #endif
    #ifdef PWM_CCP2_OC3_RB10_RP10
    {PB10, HAL_LL_TIM_INDEX_2, HAL_LL_CCP_CHANNEL_3, hal_ll_tim_module_num(CCP_MODULE_2)},
    #endif
    #ifdef PWM_CCP2_OC3_RB11_RP11
    {PB11, HAL_LL_TIM_INDEX_2, HAL_LL_CCP_CHANNEL_3, hal_ll_tim_module_num(CCP_MODULE_2)},
    #endif
    #ifdef PWM_CCP2_OC3_RB12_RP12
    {PB12, HAL_LL_TIM_INDEX_2, HAL_LL_CCP_CHANNEL_3, hal_ll_tim_module_num(CCP_MODULE_2)},
    #endif
    #ifdef PWM_CCP2_OC3_RB13_RP13
    {PB13, HAL_LL_TIM_INDEX_2, HAL_LL_CCP_CHANNEL_3, hal_ll_tim_module_num(CCP_MODULE_2)},
    #endif
    #ifdef PWM_CCP2_OC3_RB14_RP14
    {PB14, HAL_LL_TIM_INDEX_2, HAL_LL_CCP_CHANNEL_3, hal_ll_tim_module_num(CCP_MODULE_2)},
    #endif
    #ifdef PWM_CCP2_OC3_RB15_RP15
    {PB15, HAL_LL_TIM_INDEX_2, HAL_LL_CCP_CHANNEL_3, hal_ll_tim_module_num(CCP_MODULE_2)},
    #endif
    #ifdef PWM_CCP2_OC3_RB2_RP2
    {PB2, HAL_LL_TIM_INDEX_2, HAL_LL_CCP_CHANNEL_3, hal_ll_tim_module_num(CCP_MODULE_2)},
    #endif
    #ifdef PWM_CCP2_OC3_RB3_RP3
    {PB3, HAL_LL_TIM_INDEX_2, HAL_LL_CCP_CHANNEL_3, hal_ll_tim_module_num(CCP_MODULE_2)},
    #endif
    #ifdef PWM_CCP2_OC3_RB4_RP4
    {PB4, HAL_LL_TIM_INDEX_2, HAL_LL_CCP_CHANNEL_3, hal_ll_tim_module_num(CCP_MODULE_2)},
    #endif
    #ifdef PWM_CCP2_OC3_RB5_RP5
    {PB5, HAL_LL_TIM_INDEX_2, HAL_LL_CCP_CHANNEL_3, hal_ll_tim_module_num(CCP_MODULE_2)},
    #endif
    #ifdef PWM_CCP2_OC3_RB6_RP6
    {PB6, HAL_LL_TIM_INDEX_2, HAL_LL_CCP_CHANNEL_3, hal_ll_tim_module_num(CCP_MODULE_2)},
    #endif
    #ifdef PWM_CCP2_OC3_RB7_RP7
    {PB7, HAL_LL_TIM_INDEX_2, HAL_LL_CCP_CHANNEL_3, hal_ll_tim_module_num(CCP_MODULE_2)},
    #endif
    #ifdef PWM_CCP2_OC3_RB8_RP8
    {PB8, HAL_LL_TIM_INDEX_2, HAL_LL_CCP_CHANNEL_3, hal_ll_tim_module_num(CCP_MODULE_2)},
    #endif
    #ifdef PWM_CCP2_OC3_RB9_RP9
    {PB9, HAL_LL_TIM_INDEX_2, HAL_LL_CCP_CHANNEL_3, hal_ll_tim_module_num(CCP_MODULE_2)},
    #endif
    #ifdef PWM_CCP2_OC4_RB0_RP0
    {PB0, HAL_LL_TIM_INDEX_2, HAL_LL_CCP_CHANNEL_4, hal_ll_tim_module_num(CCP_MODULE_2)},
    #endif
    #ifdef PWM_CCP2_OC4_RB1_RP1
    {PB1, HAL_LL_TIM_INDEX_2, HAL_LL_CCP_CHANNEL_4, hal_ll_tim_module_num(CCP_MODULE_2)},
    #endif
    #ifdef PWM_CCP2_OC4_RB10_RP10
    {PB10, HAL_LL_TIM_INDEX_2, HAL_LL_CCP_CHANNEL_4, hal_ll_tim_module_num(CCP_MODULE_2)},
    #endif
    #ifdef PWM_CCP2_OC4_RB11_RP11
    {PB11, HAL_LL_TIM_INDEX_2, HAL_LL_CCP_CHANNEL_4, hal_ll_tim_module_num(CCP_MODULE_2)},
    #endif
    #ifdef PWM_CCP2_OC4_RB12_RP12
    {PB12, HAL_LL_TIM_INDEX_2, HAL_LL_CCP_CHANNEL_4, hal_ll_tim_module_num(CCP_MODULE_2)},
    #endif
    #ifdef PWM_CCP2_OC4_RB13_RP13
    {PB13, HAL_LL_TIM_INDEX_2, HAL_LL_CCP_CHANNEL_4, hal_ll_tim_module_num(CCP_MODULE_2)},
    #endif
    #ifdef PWM_CCP2_OC4_RB14_RP14
    {PB14, HAL_LL_TIM_INDEX_2, HAL_LL_CCP_CHANNEL_4, hal_ll_tim_module_num(CCP_MODULE_2)},
    #endif
    #ifdef PWM_CCP2_OC4_RB15_RP15
    {PB15, HAL_LL_TIM_INDEX_2, HAL_LL_CCP_CHANNEL_4, hal_ll_tim_module_num(CCP_MODULE_2)},
    #endif
    #ifdef PWM_CCP2_OC4_RB2_RP2
    {PB2, HAL_LL_TIM_INDEX_2, HAL_LL_CCP_CHANNEL_4, hal_ll_tim_module_num(CCP_MODULE_2)},
    #endif
    #ifdef PWM_CCP2_OC4_RB3_RP3
    {PB3, HAL_LL_TIM_INDEX_2, HAL_LL_CCP_CHANNEL_4, hal_ll_tim_module_num(CCP_MODULE_2)},
    #endif
    #ifdef PWM_CCP2_OC4_RB4_RP4
    {PB4, HAL_LL_TIM_INDEX_2, HAL_LL_CCP_CHANNEL_4, hal_ll_tim_module_num(CCP_MODULE_2)},
    #endif
    #ifdef PWM_CCP2_OC4_RB5_RP5
    {PB5, HAL_LL_TIM_INDEX_2, HAL_LL_CCP_CHANNEL_4, hal_ll_tim_module_num(CCP_MODULE_2)},
    #endif
    #ifdef PWM_CCP2_OC4_RB6_RP6
    {PB6, HAL_LL_TIM_INDEX_2, HAL_LL_CCP_CHANNEL_4, hal_ll_tim_module_num(CCP_MODULE_2)},
    #endif
    #ifdef PWM_CCP2_OC4_RB7_RP7
    {PB7, HAL_LL_TIM_INDEX_2, HAL_LL_CCP_CHANNEL_4, hal_ll_tim_module_num(CCP_MODULE_2)},
    #endif
    #ifdef PWM_CCP2_OC4_RB8_RP8
    {PB8, HAL_LL_TIM_INDEX_2, HAL_LL_CCP_CHANNEL_4, hal_ll_tim_module_num(CCP_MODULE_2)},
    #endif
    #ifdef PWM_CCP2_OC4_RB9_RP9
    {PB9, HAL_LL_TIM_INDEX_2, HAL_LL_CCP_CHANNEL_4, hal_ll_tim_module_num(CCP_MODULE_2)},
    #endif
    #ifdef PWM_CCP3_OC1_RB0_RP0
    {PB0, HAL_LL_TIM_INDEX_2, HAL_LL_CCP_CHANNEL_1, hal_ll_tim_module_num(CCP_MODULE_3)},
    #endif
    #ifdef PWM_CCP3_OC1_RB1_RP1
    {PB1, HAL_LL_TIM_INDEX_2, HAL_LL_CCP_CHANNEL_1, hal_ll_tim_module_num(CCP_MODULE_3)},
    #endif
    #ifdef PWM_CCP3_OC1_RB10_RP10
    {PB10, HAL_LL_TIM_INDEX_2, HAL_LL_CCP_CHANNEL_1, hal_ll_tim_module_num(CCP_MODULE_3)},
    #endif
    #ifdef PWM_CCP3_OC1_RB11_RP11
    {PB11, HAL_LL_TIM_INDEX_2, HAL_LL_CCP_CHANNEL_1, hal_ll_tim_module_num(CCP_MODULE_3)},
    #endif
    #ifdef PWM_CCP3_OC1_RB12_RP12
    {PB12, HAL_LL_TIM_INDEX_2, HAL_LL_CCP_CHANNEL_1, hal_ll_tim_module_num(CCP_MODULE_3)},
    #endif
    #ifdef PWM_CCP3_OC1_RB13_RP13
    {PB13, HAL_LL_TIM_INDEX_2, HAL_LL_CCP_CHANNEL_1, hal_ll_tim_module_num(CCP_MODULE_3)},
    #endif
    #ifdef PWM_CCP3_OC1_RB14_RP14
    {PB14, HAL_LL_TIM_INDEX_2, HAL_LL_CCP_CHANNEL_1, hal_ll_tim_module_num(CCP_MODULE_3)},
    #endif
    #ifdef PWM_CCP3_OC1_RB15_RP15
    {PB15, HAL_LL_TIM_INDEX_2, HAL_LL_CCP_CHANNEL_1, hal_ll_tim_module_num(CCP_MODULE_3)},
    #endif
    #ifdef PWM_CCP3_OC1_RB2_RP2
    {PB2, HAL_LL_TIM_INDEX_2, HAL_LL_CCP_CHANNEL_1, hal_ll_tim_module_num(CCP_MODULE_3)},
    #endif
    #ifdef PWM_CCP3_OC1_RB3_RP3
    {PB3, HAL_LL_TIM_INDEX_2, HAL_LL_CCP_CHANNEL_1, hal_ll_tim_module_num(CCP_MODULE_3)},
    #endif
    #ifdef PWM_CCP3_OC1_RB4_RP4
    {PB4, HAL_LL_TIM_INDEX_2, HAL_LL_CCP_CHANNEL_1, hal_ll_tim_module_num(CCP_MODULE_3)},
    #endif
    #ifdef PWM_CCP3_OC1_RB5_RP5
    {PB5, HAL_LL_TIM_INDEX_2, HAL_LL_CCP_CHANNEL_1, hal_ll_tim_module_num(CCP_MODULE_3)},
    #endif
    #ifdef PWM_CCP3_OC1_RB6_RP6
    {PB6, HAL_LL_TIM_INDEX_2, HAL_LL_CCP_CHANNEL_1, hal_ll_tim_module_num(CCP_MODULE_3)},
    #endif
    #ifdef PWM_CCP3_OC1_RB7_RP7
    {PB7, HAL_LL_TIM_INDEX_2, HAL_LL_CCP_CHANNEL_1, hal_ll_tim_module_num(CCP_MODULE_3)},
    #endif
    #ifdef PWM_CCP3_OC1_RB8_RP8
    {PB8, HAL_LL_TIM_INDEX_2, HAL_LL_CCP_CHANNEL_1, hal_ll_tim_module_num(CCP_MODULE_3)},
    #endif
    #ifdef PWM_CCP3_OC1_RB9_RP9
    {PB9, HAL_LL_TIM_INDEX_2, HAL_LL_CCP_CHANNEL_1, hal_ll_tim_module_num(CCP_MODULE_3)},
    #endif
    #ifdef PWM_CCP3_OC2_RB0_RP0
    {PB0, HAL_LL_TIM_INDEX_2, HAL_LL_CCP_CHANNEL_2, hal_ll_tim_module_num(CCP_MODULE_3)},
    #endif
    #ifdef PWM_CCP3_OC2_RB1_RP1
    {PB1, HAL_LL_TIM_INDEX_2, HAL_LL_CCP_CHANNEL_2, hal_ll_tim_module_num(CCP_MODULE_3)},
    #endif
    #ifdef PWM_CCP3_OC2_RB10_RP10
    {PB10, HAL_LL_TIM_INDEX_2, HAL_LL_CCP_CHANNEL_2, hal_ll_tim_module_num(CCP_MODULE_3)},
    #endif
    #ifdef PWM_CCP3_OC2_RB11_RP11
    {PB11, HAL_LL_TIM_INDEX_2, HAL_LL_CCP_CHANNEL_2, hal_ll_tim_module_num(CCP_MODULE_3)},
    #endif
    #ifdef PWM_CCP3_OC2_RB12_RP12
    {PB12, HAL_LL_TIM_INDEX_2, HAL_LL_CCP_CHANNEL_2, hal_ll_tim_module_num(CCP_MODULE_3)},
    #endif
    #ifdef PWM_CCP3_OC2_RB13_RP13
    {PB13, HAL_LL_TIM_INDEX_2, HAL_LL_CCP_CHANNEL_2, hal_ll_tim_module_num(CCP_MODULE_3)},
    #endif
    #ifdef PWM_CCP3_OC2_RB14_RP14
    {PB14, HAL_LL_TIM_INDEX_2, HAL_LL_CCP_CHANNEL_2, hal_ll_tim_module_num(CCP_MODULE_3)},
    #endif
    #ifdef PWM_CCP3_OC2_RB15_RP15
    {PB15, HAL_LL_TIM_INDEX_2, HAL_LL_CCP_CHANNEL_2, hal_ll_tim_module_num(CCP_MODULE_3)},
    #endif
    #ifdef PWM_CCP3_OC2_RB2_RP2
    {PB2, HAL_LL_TIM_INDEX_2, HAL_LL_CCP_CHANNEL_2, hal_ll_tim_module_num(CCP_MODULE_3)},
    #endif
    #ifdef PWM_CCP3_OC2_RB3_RP3
    {PB3, HAL_LL_TIM_INDEX_2, HAL_LL_CCP_CHANNEL_2, hal_ll_tim_module_num(CCP_MODULE_3)},
    #endif
    #ifdef PWM_CCP3_OC2_RB4_RP4
    {PB4, HAL_LL_TIM_INDEX_2, HAL_LL_CCP_CHANNEL_2, hal_ll_tim_module_num(CCP_MODULE_3)},
    #endif
    #ifdef PWM_CCP3_OC2_RB5_RP5
    {PB5, HAL_LL_TIM_INDEX_2, HAL_LL_CCP_CHANNEL_2, hal_ll_tim_module_num(CCP_MODULE_3)},
    #endif
    #ifdef PWM_CCP3_OC2_RB6_RP6
    {PB6, HAL_LL_TIM_INDEX_2, HAL_LL_CCP_CHANNEL_2, hal_ll_tim_module_num(CCP_MODULE_3)},
    #endif
    #ifdef PWM_CCP3_OC2_RB7_RP7
    {PB7, HAL_LL_TIM_INDEX_2, HAL_LL_CCP_CHANNEL_2, hal_ll_tim_module_num(CCP_MODULE_3)},
    #endif
    #ifdef PWM_CCP3_OC2_RB8_RP8
    {PB8, HAL_LL_TIM_INDEX_2, HAL_LL_CCP_CHANNEL_2, hal_ll_tim_module_num(CCP_MODULE_3)},
    #endif
    #ifdef PWM_CCP3_OC2_RB9_RP9
    {PB9, HAL_LL_TIM_INDEX_2, HAL_LL_CCP_CHANNEL_2, hal_ll_tim_module_num(CCP_MODULE_3)},
    #endif
    #ifdef PWM_CCP3_OC3_RB0_RP0
    {PB0, HAL_LL_TIM_INDEX_2, HAL_LL_CCP_CHANNEL_3, hal_ll_tim_module_num(CCP_MODULE_3)},
    #endif
    #ifdef PWM_CCP3_OC3_RB1_RP1
    {PB1, HAL_LL_TIM_INDEX_2, HAL_LL_CCP_CHANNEL_3, hal_ll_tim_module_num(CCP_MODULE_3)},
    #endif
    #ifdef PWM_CCP3_OC3_RB10_RP10
    {PB10, HAL_LL_TIM_INDEX_2, HAL_LL_CCP_CHANNEL_3, hal_ll_tim_module_num(CCP_MODULE_3)},
    #endif
    #ifdef PWM_CCP3_OC3_RB11_RP11
    {PB11, HAL_LL_TIM_INDEX_2, HAL_LL_CCP_CHANNEL_3, hal_ll_tim_module_num(CCP_MODULE_3)},
    #endif
    #ifdef PWM_CCP3_OC3_RB12_RP12
    {PB12, HAL_LL_TIM_INDEX_2, HAL_LL_CCP_CHANNEL_3, hal_ll_tim_module_num(CCP_MODULE_3)},
    #endif
    #ifdef PWM_CCP3_OC3_RB13_RP13
    {PB13, HAL_LL_TIM_INDEX_2, HAL_LL_CCP_CHANNEL_3, hal_ll_tim_module_num(CCP_MODULE_3)},
    #endif
    #ifdef PWM_CCP3_OC3_RB14_RP14
    {PB14, HAL_LL_TIM_INDEX_2, HAL_LL_CCP_CHANNEL_3, hal_ll_tim_module_num(CCP_MODULE_3)},
    #endif
    #ifdef PWM_CCP3_OC3_RB15_RP15
    {PB15, HAL_LL_TIM_INDEX_2, HAL_LL_CCP_CHANNEL_3, hal_ll_tim_module_num(CCP_MODULE_3)},
    #endif
    #ifdef PWM_CCP3_OC3_RB2_RP2
    {PB2, HAL_LL_TIM_INDEX_2, HAL_LL_CCP_CHANNEL_3, hal_ll_tim_module_num(CCP_MODULE_3)},
    #endif
    #ifdef PWM_CCP3_OC3_RB3_RP3
    {PB3, HAL_LL_TIM_INDEX_2, HAL_LL_CCP_CHANNEL_3, hal_ll_tim_module_num(CCP_MODULE_3)},
    #endif
    #ifdef PWM_CCP3_OC3_RB4_RP4
    {PB4, HAL_LL_TIM_INDEX_2, HAL_LL_CCP_CHANNEL_3, hal_ll_tim_module_num(CCP_MODULE_3)},
    #endif
    #ifdef PWM_CCP3_OC3_RB5_RP5
    {PB5, HAL_LL_TIM_INDEX_2, HAL_LL_CCP_CHANNEL_3, hal_ll_tim_module_num(CCP_MODULE_3)},
    #endif
    #ifdef PWM_CCP3_OC3_RB6_RP6
    {PB6, HAL_LL_TIM_INDEX_2, HAL_LL_CCP_CHANNEL_3, hal_ll_tim_module_num(CCP_MODULE_3)},
    #endif
    #ifdef PWM_CCP3_OC3_RB7_RP7
    {PB7, HAL_LL_TIM_INDEX_2, HAL_LL_CCP_CHANNEL_3, hal_ll_tim_module_num(CCP_MODULE_3)},
    #endif
    #ifdef PWM_CCP3_OC3_RB8_RP8
    {PB8, HAL_LL_TIM_INDEX_2, HAL_LL_CCP_CHANNEL_3, hal_ll_tim_module_num(CCP_MODULE_3)},
    #endif
    #ifdef PWM_CCP3_OC3_RB9_RP9
    {PB9, HAL_LL_TIM_INDEX_2, HAL_LL_CCP_CHANNEL_3, hal_ll_tim_module_num(CCP_MODULE_3)},
    #endif
    #ifdef PWM_CCP3_OC4_RB0_RP0
    {PB0, HAL_LL_TIM_INDEX_2, HAL_LL_CCP_CHANNEL_4, hal_ll_tim_module_num(CCP_MODULE_3)},
    #endif
    #ifdef PWM_CCP3_OC4_RB1_RP1
    {PB1, HAL_LL_TIM_INDEX_2, HAL_LL_CCP_CHANNEL_4, hal_ll_tim_module_num(CCP_MODULE_3)},
    #endif
    #ifdef PWM_CCP3_OC4_RB10_RP10
    {PB10, HAL_LL_TIM_INDEX_2, HAL_LL_CCP_CHANNEL_4, hal_ll_tim_module_num(CCP_MODULE_3)},
    #endif
    #ifdef PWM_CCP3_OC4_RB11_RP11
    {PB11, HAL_LL_TIM_INDEX_2, HAL_LL_CCP_CHANNEL_4, hal_ll_tim_module_num(CCP_MODULE_3)},
    #endif
    #ifdef PWM_CCP3_OC4_RB12_RP12
    {PB12, HAL_LL_TIM_INDEX_2, HAL_LL_CCP_CHANNEL_4, hal_ll_tim_module_num(CCP_MODULE_3)},
    #endif
    #ifdef PWM_CCP3_OC4_RB13_RP13
    {PB13, HAL_LL_TIM_INDEX_2, HAL_LL_CCP_CHANNEL_4, hal_ll_tim_module_num(CCP_MODULE_3)},
    #endif
    #ifdef PWM_CCP3_OC4_RB14_RP14
    {PB14, HAL_LL_TIM_INDEX_2, HAL_LL_CCP_CHANNEL_4, hal_ll_tim_module_num(CCP_MODULE_3)},
    #endif
    #ifdef PWM_CCP3_OC4_RB15_RP15
    {PB15, HAL_LL_TIM_INDEX_2, HAL_LL_CCP_CHANNEL_4, hal_ll_tim_module_num(CCP_MODULE_3)},
    #endif
    #ifdef PWM_CCP3_OC4_RB2_RP2
    {PB2, HAL_LL_TIM_INDEX_2, HAL_LL_CCP_CHANNEL_4, hal_ll_tim_module_num(CCP_MODULE_3)},
    #endif
    #ifdef PWM_CCP3_OC4_RB3_RP3
    {PB3, HAL_LL_TIM_INDEX_2, HAL_LL_CCP_CHANNEL_4, hal_ll_tim_module_num(CCP_MODULE_3)},
    #endif
    #ifdef PWM_CCP3_OC4_RB4_RP4
    {PB4, HAL_LL_TIM_INDEX_2, HAL_LL_CCP_CHANNEL_4, hal_ll_tim_module_num(CCP_MODULE_3)},
    #endif
    #ifdef PWM_CCP3_OC4_RB5_RP5
    {PB5, HAL_LL_TIM_INDEX_2, HAL_LL_CCP_CHANNEL_4, hal_ll_tim_module_num(CCP_MODULE_3)},
    #endif
    #ifdef PWM_CCP3_OC4_RB6_RP6
    {PB6, HAL_LL_TIM_INDEX_2, HAL_LL_CCP_CHANNEL_4, hal_ll_tim_module_num(CCP_MODULE_3)},
    #endif
    #ifdef PWM_CCP3_OC4_RB7_RP7
    {PB7, HAL_LL_TIM_INDEX_2, HAL_LL_CCP_CHANNEL_4, hal_ll_tim_module_num(CCP_MODULE_3)},
    #endif
    #ifdef PWM_CCP3_OC4_RB8_RP8
    {PB8, HAL_LL_TIM_INDEX_2, HAL_LL_CCP_CHANNEL_4, hal_ll_tim_module_num(CCP_MODULE_3)},
    #endif
    #ifdef PWM_CCP3_OC4_RB9_RP9
    {PB9, HAL_LL_TIM_INDEX_2, HAL_LL_CCP_CHANNEL_4, hal_ll_tim_module_num(CCP_MODULE_3)},
    #endif
    #ifdef PWM_CCP4_OC1_RB0_RP0
    {PB0, HAL_LL_TIM_INDEX_2, HAL_LL_CCP_CHANNEL_1, hal_ll_tim_module_num(CCP_MODULE_4)},
    #endif
    #ifdef PWM_CCP4_OC1_RB1_RP1
    {PB1, HAL_LL_TIM_INDEX_2, HAL_LL_CCP_CHANNEL_1, hal_ll_tim_module_num(CCP_MODULE_4)},
    #endif
    #ifdef PWM_CCP4_OC1_RB10_RP10
    {PB10, HAL_LL_TIM_INDEX_2, HAL_LL_CCP_CHANNEL_1, hal_ll_tim_module_num(CCP_MODULE_4)},
    #endif
    #ifdef PWM_CCP4_OC1_RB11_RP11
    {PB11, HAL_LL_TIM_INDEX_2, HAL_LL_CCP_CHANNEL_1, hal_ll_tim_module_num(CCP_MODULE_4)},
    #endif
    #ifdef PWM_CCP4_OC1_RB12_RP12
    {PB12, HAL_LL_TIM_INDEX_2, HAL_LL_CCP_CHANNEL_1, hal_ll_tim_module_num(CCP_MODULE_4)},
    #endif
    #ifdef PWM_CCP4_OC1_RB13_RP13
    {PB13, HAL_LL_TIM_INDEX_2, HAL_LL_CCP_CHANNEL_1, hal_ll_tim_module_num(CCP_MODULE_4)},
    #endif
    #ifdef PWM_CCP4_OC1_RB14_RP14
    {PB14, HAL_LL_TIM_INDEX_2, HAL_LL_CCP_CHANNEL_1, hal_ll_tim_module_num(CCP_MODULE_4)},
    #endif
    #ifdef PWM_CCP4_OC1_RB15_RP15
    {PB15, HAL_LL_TIM_INDEX_2, HAL_LL_CCP_CHANNEL_1, hal_ll_tim_module_num(CCP_MODULE_4)},
    #endif
    #ifdef PWM_CCP4_OC1_RB2_RP2
    {PB2, HAL_LL_TIM_INDEX_2, HAL_LL_CCP_CHANNEL_1, hal_ll_tim_module_num(CCP_MODULE_4)},
    #endif
    #ifdef PWM_CCP4_OC1_RB3_RP3
    {PB3, HAL_LL_TIM_INDEX_2, HAL_LL_CCP_CHANNEL_1, hal_ll_tim_module_num(CCP_MODULE_4)},
    #endif
    #ifdef PWM_CCP4_OC1_RB4_RP4
    {PB4, HAL_LL_TIM_INDEX_2, HAL_LL_CCP_CHANNEL_1, hal_ll_tim_module_num(CCP_MODULE_4)},
    #endif
    #ifdef PWM_CCP4_OC1_RB5_RP5
    {PB5, HAL_LL_TIM_INDEX_2, HAL_LL_CCP_CHANNEL_1, hal_ll_tim_module_num(CCP_MODULE_4)},
    #endif
    #ifdef PWM_CCP4_OC1_RB6_RP6
    {PB6, HAL_LL_TIM_INDEX_2, HAL_LL_CCP_CHANNEL_1, hal_ll_tim_module_num(CCP_MODULE_4)},
    #endif
    #ifdef PWM_CCP4_OC1_RB7_RP7
    {PB7, HAL_LL_TIM_INDEX_2, HAL_LL_CCP_CHANNEL_1, hal_ll_tim_module_num(CCP_MODULE_4)},
    #endif
    #ifdef PWM_CCP4_OC1_RB8_RP8
    {PB8, HAL_LL_TIM_INDEX_2, HAL_LL_CCP_CHANNEL_1, hal_ll_tim_module_num(CCP_MODULE_4)},
    #endif
    #ifdef PWM_CCP4_OC1_RB9_RP9
    {PB9, HAL_LL_TIM_INDEX_2, HAL_LL_CCP_CHANNEL_1, hal_ll_tim_module_num(CCP_MODULE_4)},
    #endif
    #ifdef PWM_CCP4_OC2_RB0_RP0
    {PB0, HAL_LL_TIM_INDEX_2, HAL_LL_CCP_CHANNEL_2, hal_ll_tim_module_num(CCP_MODULE_4)},
    #endif
    #ifdef PWM_CCP4_OC2_RB1_RP1
    {PB1, HAL_LL_TIM_INDEX_2, HAL_LL_CCP_CHANNEL_2, hal_ll_tim_module_num(CCP_MODULE_4)},
    #endif
    #ifdef PWM_CCP4_OC2_RB10_RP10
    {PB10, HAL_LL_TIM_INDEX_2, HAL_LL_CCP_CHANNEL_2, hal_ll_tim_module_num(CCP_MODULE_4)},
    #endif
    #ifdef PWM_CCP4_OC2_RB11_RP11
    {PB11, HAL_LL_TIM_INDEX_2, HAL_LL_CCP_CHANNEL_2, hal_ll_tim_module_num(CCP_MODULE_4)},
    #endif
    #ifdef PWM_CCP4_OC2_RB12_RP12
    {PB12, HAL_LL_TIM_INDEX_2, HAL_LL_CCP_CHANNEL_2, hal_ll_tim_module_num(CCP_MODULE_4)},
    #endif
    #ifdef PWM_CCP4_OC2_RB13_RP13
    {PB13, HAL_LL_TIM_INDEX_2, HAL_LL_CCP_CHANNEL_2, hal_ll_tim_module_num(CCP_MODULE_4)},
    #endif
    #ifdef PWM_CCP4_OC2_RB14_RP14
    {PB14, HAL_LL_TIM_INDEX_2, HAL_LL_CCP_CHANNEL_2, hal_ll_tim_module_num(CCP_MODULE_4)},
    #endif
    #ifdef PWM_CCP4_OC2_RB15_RP15
    {PB15, HAL_LL_TIM_INDEX_2, HAL_LL_CCP_CHANNEL_2, hal_ll_tim_module_num(CCP_MODULE_4)},
    #endif
    #ifdef PWM_CCP4_OC2_RB2_RP2
    {PB2, HAL_LL_TIM_INDEX_2, HAL_LL_CCP_CHANNEL_2, hal_ll_tim_module_num(CCP_MODULE_4)},
    #endif
    #ifdef PWM_CCP4_OC2_RB3_RP3
    {PB3, HAL_LL_TIM_INDEX_2, HAL_LL_CCP_CHANNEL_2, hal_ll_tim_module_num(CCP_MODULE_4)},
    #endif
    #ifdef PWM_CCP4_OC2_RB4_RP4
    {PB4, HAL_LL_TIM_INDEX_2, HAL_LL_CCP_CHANNEL_2, hal_ll_tim_module_num(CCP_MODULE_4)},
    #endif
    #ifdef PWM_CCP4_OC2_RB5_RP5
    {PB5, HAL_LL_TIM_INDEX_2, HAL_LL_CCP_CHANNEL_2, hal_ll_tim_module_num(CCP_MODULE_4)},
    #endif
    #ifdef PWM_CCP4_OC2_RB6_RP6
    {PB6, HAL_LL_TIM_INDEX_2, HAL_LL_CCP_CHANNEL_2, hal_ll_tim_module_num(CCP_MODULE_4)},
    #endif
    #ifdef PWM_CCP4_OC2_RB7_RP7
    {PB7, HAL_LL_TIM_INDEX_2, HAL_LL_CCP_CHANNEL_2, hal_ll_tim_module_num(CCP_MODULE_4)},
    #endif
    #ifdef PWM_CCP4_OC2_RB8_RP8
    {PB8, HAL_LL_TIM_INDEX_2, HAL_LL_CCP_CHANNEL_2, hal_ll_tim_module_num(CCP_MODULE_4)},
    #endif
    #ifdef PWM_CCP4_OC2_RB9_RP9
    {PB9, HAL_LL_TIM_INDEX_2, HAL_LL_CCP_CHANNEL_2, hal_ll_tim_module_num(CCP_MODULE_4)},
    #endif
    #ifdef PWM_CCP4_OC3_RB0_RP0
    {PB0, HAL_LL_TIM_INDEX_2, HAL_LL_CCP_CHANNEL_3, hal_ll_tim_module_num(CCP_MODULE_4)},
    #endif
    #ifdef PWM_CCP4_OC3_RB1_RP1
    {PB1, HAL_LL_TIM_INDEX_2, HAL_LL_CCP_CHANNEL_3, hal_ll_tim_module_num(CCP_MODULE_4)},
    #endif
    #ifdef PWM_CCP4_OC3_RB10_RP10
    {PB10, HAL_LL_TIM_INDEX_2, HAL_LL_CCP_CHANNEL_3, hal_ll_tim_module_num(CCP_MODULE_4)},
    #endif
    #ifdef PWM_CCP4_OC3_RB11_RP11
    {PB11, HAL_LL_TIM_INDEX_2, HAL_LL_CCP_CHANNEL_3, hal_ll_tim_module_num(CCP_MODULE_4)},
    #endif
    #ifdef PWM_CCP4_OC3_RB12_RP12
    {PB12, HAL_LL_TIM_INDEX_2, HAL_LL_CCP_CHANNEL_3, hal_ll_tim_module_num(CCP_MODULE_4)},
    #endif
    #ifdef PWM_CCP4_OC3_RB13_RP13
    {PB13, HAL_LL_TIM_INDEX_2, HAL_LL_CCP_CHANNEL_3, hal_ll_tim_module_num(CCP_MODULE_4)},
    #endif
    #ifdef PWM_CCP4_OC3_RB14_RP14
    {PB14, HAL_LL_TIM_INDEX_2, HAL_LL_CCP_CHANNEL_3, hal_ll_tim_module_num(CCP_MODULE_4)},
    #endif
    #ifdef PWM_CCP4_OC3_RB15_RP15
    {PB15, HAL_LL_TIM_INDEX_2, HAL_LL_CCP_CHANNEL_3, hal_ll_tim_module_num(CCP_MODULE_4)},
    #endif
    #ifdef PWM_CCP4_OC3_RB2_RP2
    {PB2, HAL_LL_TIM_INDEX_2, HAL_LL_CCP_CHANNEL_3, hal_ll_tim_module_num(CCP_MODULE_4)},
    #endif
    #ifdef PWM_CCP4_OC3_RB3_RP3
    {PB3, HAL_LL_TIM_INDEX_2, HAL_LL_CCP_CHANNEL_3, hal_ll_tim_module_num(CCP_MODULE_4)},
    #endif
    #ifdef PWM_CCP4_OC3_RB4_RP4
    {PB4, HAL_LL_TIM_INDEX_2, HAL_LL_CCP_CHANNEL_3, hal_ll_tim_module_num(CCP_MODULE_4)},
    #endif
    #ifdef PWM_CCP4_OC3_RB5_RP5
    {PB5, HAL_LL_TIM_INDEX_2, HAL_LL_CCP_CHANNEL_3, hal_ll_tim_module_num(CCP_MODULE_4)},
    #endif
    #ifdef PWM_CCP4_OC3_RB6_RP6
    {PB6, HAL_LL_TIM_INDEX_2, HAL_LL_CCP_CHANNEL_3, hal_ll_tim_module_num(CCP_MODULE_4)},
    #endif
    #ifdef PWM_CCP4_OC3_RB7_RP7
    {PB7, HAL_LL_TIM_INDEX_2, HAL_LL_CCP_CHANNEL_3, hal_ll_tim_module_num(CCP_MODULE_4)},
    #endif
    #ifdef PWM_CCP4_OC3_RB8_RP8
    {PB8, HAL_LL_TIM_INDEX_2, HAL_LL_CCP_CHANNEL_3, hal_ll_tim_module_num(CCP_MODULE_4)},
    #endif
    #ifdef PWM_CCP4_OC3_RB9_RP9
    {PB9, HAL_LL_TIM_INDEX_2, HAL_LL_CCP_CHANNEL_3, hal_ll_tim_module_num(CCP_MODULE_4)},
    #endif
    #ifdef PWM_CCP4_OC4_RB0_RP0
    {PB0, HAL_LL_TIM_INDEX_2, HAL_LL_CCP_CHANNEL_4, hal_ll_tim_module_num(CCP_MODULE_4)},
    #endif
    #ifdef PWM_CCP4_OC4_RB1_RP1
    {PB1, HAL_LL_TIM_INDEX_2, HAL_LL_CCP_CHANNEL_4, hal_ll_tim_module_num(CCP_MODULE_4)},
    #endif
    #ifdef PWM_CCP4_OC4_RB10_RP10
    {PB10, HAL_LL_TIM_INDEX_2, HAL_LL_CCP_CHANNEL_4, hal_ll_tim_module_num(CCP_MODULE_4)},
    #endif
    #ifdef PWM_CCP4_OC4_RB11_RP11
    {PB11, HAL_LL_TIM_INDEX_2, HAL_LL_CCP_CHANNEL_4, hal_ll_tim_module_num(CCP_MODULE_4)},
    #endif
    #ifdef PWM_CCP4_OC4_RB12_RP12
    {PB12, HAL_LL_TIM_INDEX_2, HAL_LL_CCP_CHANNEL_4, hal_ll_tim_module_num(CCP_MODULE_4)},
    #endif
    #ifdef PWM_CCP4_OC4_RB13_RP13
    {PB13, HAL_LL_TIM_INDEX_2, HAL_LL_CCP_CHANNEL_4, hal_ll_tim_module_num(CCP_MODULE_4)},
    #endif
    #ifdef PWM_CCP4_OC4_RB14_RP14
    {PB14, HAL_LL_TIM_INDEX_2, HAL_LL_CCP_CHANNEL_4, hal_ll_tim_module_num(CCP_MODULE_4)},
    #endif
    #ifdef PWM_CCP4_OC4_RB15_RP15
    {PB15, HAL_LL_TIM_INDEX_2, HAL_LL_CCP_CHANNEL_4, hal_ll_tim_module_num(CCP_MODULE_4)},
    #endif
    #ifdef PWM_CCP4_OC4_RB2_RP2
    {PB2, HAL_LL_TIM_INDEX_2, HAL_LL_CCP_CHANNEL_4, hal_ll_tim_module_num(CCP_MODULE_4)},
    #endif
    #ifdef PWM_CCP4_OC4_RB3_RP3
    {PB3, HAL_LL_TIM_INDEX_2, HAL_LL_CCP_CHANNEL_4, hal_ll_tim_module_num(CCP_MODULE_4)},
    #endif
    #ifdef PWM_CCP4_OC4_RB4_RP4
    {PB4, HAL_LL_TIM_INDEX_2, HAL_LL_CCP_CHANNEL_4, hal_ll_tim_module_num(CCP_MODULE_4)},
    #endif
    #ifdef PWM_CCP4_OC4_RB5_RP5
    {PB5, HAL_LL_TIM_INDEX_2, HAL_LL_CCP_CHANNEL_4, hal_ll_tim_module_num(CCP_MODULE_4)},
    #endif
    #ifdef PWM_CCP4_OC4_RB6_RP6
    {PB6, HAL_LL_TIM_INDEX_2, HAL_LL_CCP_CHANNEL_4, hal_ll_tim_module_num(CCP_MODULE_4)},
    #endif
    #ifdef PWM_CCP4_OC4_RB7_RP7
    {PB7, HAL_LL_TIM_INDEX_2, HAL_LL_CCP_CHANNEL_4, hal_ll_tim_module_num(CCP_MODULE_4)},
    #endif
    #ifdef PWM_CCP4_OC4_RB8_RP8
    {PB8, HAL_LL_TIM_INDEX_2, HAL_LL_CCP_CHANNEL_4, hal_ll_tim_module_num(CCP_MODULE_4)},
    #endif
    #ifdef PWM_CCP4_OC4_RB9_RP9
    {PB9, HAL_LL_TIM_INDEX_2, HAL_LL_CCP_CHANNEL_4, hal_ll_tim_module_num(CCP_MODULE_4)},
    #endif
    #ifdef PWM_CCP5_OC1_RB0_RP0
    {PB0, HAL_LL_TIM_INDEX_2, HAL_LL_CCP_CHANNEL_1, hal_ll_tim_module_num(CCP_MODULE_5)},
    #endif
    #ifdef PWM_CCP5_OC1_RB1_RP1
    {PB1, HAL_LL_TIM_INDEX_2, HAL_LL_CCP_CHANNEL_1, hal_ll_tim_module_num(CCP_MODULE_5)},
    #endif
    #ifdef PWM_CCP5_OC1_RB10_RP10
    {PB10, HAL_LL_TIM_INDEX_2, HAL_LL_CCP_CHANNEL_1, hal_ll_tim_module_num(CCP_MODULE_5)},
    #endif
    #ifdef PWM_CCP5_OC1_RB11_RP11
    {PB11, HAL_LL_TIM_INDEX_2, HAL_LL_CCP_CHANNEL_1, hal_ll_tim_module_num(CCP_MODULE_5)},
    #endif
    #ifdef PWM_CCP5_OC1_RB12_RP12
    {PB12, HAL_LL_TIM_INDEX_2, HAL_LL_CCP_CHANNEL_1, hal_ll_tim_module_num(CCP_MODULE_5)},
    #endif
    #ifdef PWM_CCP5_OC1_RB13_RP13
    {PB13, HAL_LL_TIM_INDEX_2, HAL_LL_CCP_CHANNEL_1, hal_ll_tim_module_num(CCP_MODULE_5)},
    #endif
    #ifdef PWM_CCP5_OC1_RB14_RP14
    {PB14, HAL_LL_TIM_INDEX_2, HAL_LL_CCP_CHANNEL_1, hal_ll_tim_module_num(CCP_MODULE_5)},
    #endif
    #ifdef PWM_CCP5_OC1_RB15_RP15
    {PB15, HAL_LL_TIM_INDEX_2, HAL_LL_CCP_CHANNEL_1, hal_ll_tim_module_num(CCP_MODULE_5)},
    #endif
    #ifdef PWM_CCP5_OC1_RB2_RP2
    {PB2, HAL_LL_TIM_INDEX_2, HAL_LL_CCP_CHANNEL_1, hal_ll_tim_module_num(CCP_MODULE_5)},
    #endif
    #ifdef PWM_CCP5_OC1_RB3_RP3
    {PB3, HAL_LL_TIM_INDEX_2, HAL_LL_CCP_CHANNEL_1, hal_ll_tim_module_num(CCP_MODULE_5)},
    #endif
    #ifdef PWM_CCP5_OC1_RB4_RP4
    {PB4, HAL_LL_TIM_INDEX_2, HAL_LL_CCP_CHANNEL_1, hal_ll_tim_module_num(CCP_MODULE_5)},
    #endif
    #ifdef PWM_CCP5_OC1_RB5_RP5
    {PB5, HAL_LL_TIM_INDEX_2, HAL_LL_CCP_CHANNEL_1, hal_ll_tim_module_num(CCP_MODULE_5)},
    #endif
    #ifdef PWM_CCP5_OC1_RB6_RP6
    {PB6, HAL_LL_TIM_INDEX_2, HAL_LL_CCP_CHANNEL_1, hal_ll_tim_module_num(CCP_MODULE_5)},
    #endif
    #ifdef PWM_CCP5_OC1_RB7_RP7
    {PB7, HAL_LL_TIM_INDEX_2, HAL_LL_CCP_CHANNEL_1, hal_ll_tim_module_num(CCP_MODULE_5)},
    #endif
    #ifdef PWM_CCP5_OC1_RB8_RP8
    {PB8, HAL_LL_TIM_INDEX_2, HAL_LL_CCP_CHANNEL_1, hal_ll_tim_module_num(CCP_MODULE_5)},
    #endif
    #ifdef PWM_CCP5_OC1_RB9_RP9
    {PB9, HAL_LL_TIM_INDEX_2, HAL_LL_CCP_CHANNEL_1, hal_ll_tim_module_num(CCP_MODULE_5)},
    #endif
    #ifdef PWM_CCP5_OC2_RB0_RP0
    {PB0, HAL_LL_TIM_INDEX_2, HAL_LL_CCP_CHANNEL_2, hal_ll_tim_module_num(CCP_MODULE_5)},
    #endif
    #ifdef PWM_CCP5_OC2_RB1_RP1
    {PB1, HAL_LL_TIM_INDEX_2, HAL_LL_CCP_CHANNEL_2, hal_ll_tim_module_num(CCP_MODULE_5)},
    #endif
    #ifdef PWM_CCP5_OC2_RB10_RP10
    {PB10, HAL_LL_TIM_INDEX_2, HAL_LL_CCP_CHANNEL_2, hal_ll_tim_module_num(CCP_MODULE_5)},
    #endif
    #ifdef PWM_CCP5_OC2_RB11_RP11
    {PB11, HAL_LL_TIM_INDEX_2, HAL_LL_CCP_CHANNEL_2, hal_ll_tim_module_num(CCP_MODULE_5)},
    #endif
    #ifdef PWM_CCP5_OC2_RB12_RP12
    {PB12, HAL_LL_TIM_INDEX_2, HAL_LL_CCP_CHANNEL_2, hal_ll_tim_module_num(CCP_MODULE_5)},
    #endif
    #ifdef PWM_CCP5_OC2_RB13_RP13
    {PB13, HAL_LL_TIM_INDEX_2, HAL_LL_CCP_CHANNEL_2, hal_ll_tim_module_num(CCP_MODULE_5)},
    #endif
    #ifdef PWM_CCP5_OC2_RB14_RP14
    {PB14, HAL_LL_TIM_INDEX_2, HAL_LL_CCP_CHANNEL_2, hal_ll_tim_module_num(CCP_MODULE_5)},
    #endif
    #ifdef PWM_CCP5_OC2_RB15_RP15
    {PB15, HAL_LL_TIM_INDEX_2, HAL_LL_CCP_CHANNEL_2, hal_ll_tim_module_num(CCP_MODULE_5)},
    #endif
    #ifdef PWM_CCP5_OC2_RB2_RP2
    {PB2, HAL_LL_TIM_INDEX_2, HAL_LL_CCP_CHANNEL_2, hal_ll_tim_module_num(CCP_MODULE_5)},
    #endif
    #ifdef PWM_CCP5_OC2_RB3_RP3
    {PB3, HAL_LL_TIM_INDEX_2, HAL_LL_CCP_CHANNEL_2, hal_ll_tim_module_num(CCP_MODULE_5)},
    #endif
    #ifdef PWM_CCP5_OC2_RB4_RP4
    {PB4, HAL_LL_TIM_INDEX_2, HAL_LL_CCP_CHANNEL_2, hal_ll_tim_module_num(CCP_MODULE_5)},
    #endif
    #ifdef PWM_CCP5_OC2_RB5_RP5
    {PB5, HAL_LL_TIM_INDEX_2, HAL_LL_CCP_CHANNEL_2, hal_ll_tim_module_num(CCP_MODULE_5)},
    #endif
    #ifdef PWM_CCP5_OC2_RB6_RP6
    {PB6, HAL_LL_TIM_INDEX_2, HAL_LL_CCP_CHANNEL_2, hal_ll_tim_module_num(CCP_MODULE_5)},
    #endif
    #ifdef PWM_CCP5_OC2_RB7_RP7
    {PB7, HAL_LL_TIM_INDEX_2, HAL_LL_CCP_CHANNEL_2, hal_ll_tim_module_num(CCP_MODULE_5)},
    #endif
    #ifdef PWM_CCP5_OC2_RB8_RP8
    {PB8, HAL_LL_TIM_INDEX_2, HAL_LL_CCP_CHANNEL_2, hal_ll_tim_module_num(CCP_MODULE_5)},
    #endif
    #ifdef PWM_CCP5_OC2_RB9_RP9
    {PB9, HAL_LL_TIM_INDEX_2, HAL_LL_CCP_CHANNEL_2, hal_ll_tim_module_num(CCP_MODULE_5)},
    #endif
    #ifdef PWM_CCP5_OC3_RB0_RP0
    {PB0, HAL_LL_TIM_INDEX_2, HAL_LL_CCP_CHANNEL_3, hal_ll_tim_module_num(CCP_MODULE_5)},
    #endif
    #ifdef PWM_CCP5_OC3_RB1_RP1
    {PB1, HAL_LL_TIM_INDEX_2, HAL_LL_CCP_CHANNEL_3, hal_ll_tim_module_num(CCP_MODULE_5)},
    #endif
    #ifdef PWM_CCP5_OC3_RB10_RP10
    {PB10, HAL_LL_TIM_INDEX_2, HAL_LL_CCP_CHANNEL_3, hal_ll_tim_module_num(CCP_MODULE_5)},
    #endif
    #ifdef PWM_CCP5_OC3_RB11_RP11
    {PB11, HAL_LL_TIM_INDEX_2, HAL_LL_CCP_CHANNEL_3, hal_ll_tim_module_num(CCP_MODULE_5)},
    #endif
    #ifdef PWM_CCP5_OC3_RB12_RP12
    {PB12, HAL_LL_TIM_INDEX_2, HAL_LL_CCP_CHANNEL_3, hal_ll_tim_module_num(CCP_MODULE_5)},
    #endif
    #ifdef PWM_CCP5_OC3_RB13_RP13
    {PB13, HAL_LL_TIM_INDEX_2, HAL_LL_CCP_CHANNEL_3, hal_ll_tim_module_num(CCP_MODULE_5)},
    #endif
    #ifdef PWM_CCP5_OC3_RB14_RP14
    {PB14, HAL_LL_TIM_INDEX_2, HAL_LL_CCP_CHANNEL_3, hal_ll_tim_module_num(CCP_MODULE_5)},
    #endif
    #ifdef PWM_CCP5_OC3_RB15_RP15
    {PB15, HAL_LL_TIM_INDEX_2, HAL_LL_CCP_CHANNEL_3, hal_ll_tim_module_num(CCP_MODULE_5)},
    #endif
    #ifdef PWM_CCP5_OC3_RB2_RP2
    {PB2, HAL_LL_TIM_INDEX_2, HAL_LL_CCP_CHANNEL_3, hal_ll_tim_module_num(CCP_MODULE_5)},
    #endif
    #ifdef PWM_CCP5_OC3_RB3_RP3
    {PB3, HAL_LL_TIM_INDEX_2, HAL_LL_CCP_CHANNEL_3, hal_ll_tim_module_num(CCP_MODULE_5)},
    #endif
    #ifdef PWM_CCP5_OC3_RB4_RP4
    {PB4, HAL_LL_TIM_INDEX_2, HAL_LL_CCP_CHANNEL_3, hal_ll_tim_module_num(CCP_MODULE_5)},
    #endif
    #ifdef PWM_CCP5_OC3_RB5_RP5
    {PB5, HAL_LL_TIM_INDEX_2, HAL_LL_CCP_CHANNEL_3, hal_ll_tim_module_num(CCP_MODULE_5)},
    #endif
    #ifdef PWM_CCP5_OC3_RB6_RP6
    {PB6, HAL_LL_TIM_INDEX_2, HAL_LL_CCP_CHANNEL_3, hal_ll_tim_module_num(CCP_MODULE_5)},
    #endif
    #ifdef PWM_CCP5_OC3_RB7_RP7
    {PB7, HAL_LL_TIM_INDEX_2, HAL_LL_CCP_CHANNEL_3, hal_ll_tim_module_num(CCP_MODULE_5)},
    #endif
    #ifdef PWM_CCP5_OC3_RB8_RP8
    {PB8, HAL_LL_TIM_INDEX_2, HAL_LL_CCP_CHANNEL_3, hal_ll_tim_module_num(CCP_MODULE_5)},
    #endif
    #ifdef PWM_CCP5_OC3_RB9_RP9
    {PB9, HAL_LL_TIM_INDEX_2, HAL_LL_CCP_CHANNEL_3, hal_ll_tim_module_num(CCP_MODULE_5)},
    #endif
    #ifdef PWM_CCP5_OC4_RB0_RP0
    {PB0, HAL_LL_TIM_INDEX_2, HAL_LL_CCP_CHANNEL_4, hal_ll_tim_module_num(CCP_MODULE_5)},
    #endif
    #ifdef PWM_CCP5_OC4_RB1_RP1
    {PB1, HAL_LL_TIM_INDEX_2, HAL_LL_CCP_CHANNEL_4, hal_ll_tim_module_num(CCP_MODULE_5)},
    #endif
    #ifdef PWM_CCP5_OC4_RB10_RP10
    {PB10, HAL_LL_TIM_INDEX_2, HAL_LL_CCP_CHANNEL_4, hal_ll_tim_module_num(CCP_MODULE_5)},
    #endif
    #ifdef PWM_CCP5_OC4_RB11_RP11
    {PB11, HAL_LL_TIM_INDEX_2, HAL_LL_CCP_CHANNEL_4, hal_ll_tim_module_num(CCP_MODULE_5)},
    #endif
    #ifdef PWM_CCP5_OC4_RB12_RP12
    {PB12, HAL_LL_TIM_INDEX_2, HAL_LL_CCP_CHANNEL_4, hal_ll_tim_module_num(CCP_MODULE_5)},
    #endif
    #ifdef PWM_CCP5_OC4_RB13_RP13
    {PB13, HAL_LL_TIM_INDEX_2, HAL_LL_CCP_CHANNEL_4, hal_ll_tim_module_num(CCP_MODULE_5)},
    #endif
    #ifdef PWM_CCP5_OC4_RB14_RP14
    {PB14, HAL_LL_TIM_INDEX_2, HAL_LL_CCP_CHANNEL_4, hal_ll_tim_module_num(CCP_MODULE_5)},
    #endif
    #ifdef PWM_CCP5_OC4_RB15_RP15
    {PB15, HAL_LL_TIM_INDEX_2, HAL_LL_CCP_CHANNEL_4, hal_ll_tim_module_num(CCP_MODULE_5)},
    #endif
    #ifdef PWM_CCP5_OC4_RB2_RP2
    {PB2, HAL_LL_TIM_INDEX_2, HAL_LL_CCP_CHANNEL_4, hal_ll_tim_module_num(CCP_MODULE_5)},
    #endif
    #ifdef PWM_CCP5_OC4_RB3_RP3
    {PB3, HAL_LL_TIM_INDEX_2, HAL_LL_CCP_CHANNEL_4, hal_ll_tim_module_num(CCP_MODULE_5)},
    #endif
    #ifdef PWM_CCP5_OC4_RB4_RP4
    {PB4, HAL_LL_TIM_INDEX_2, HAL_LL_CCP_CHANNEL_4, hal_ll_tim_module_num(CCP_MODULE_5)},
    #endif
    #ifdef PWM_CCP5_OC4_RB5_RP5
    {PB5, HAL_LL_TIM_INDEX_2, HAL_LL_CCP_CHANNEL_4, hal_ll_tim_module_num(CCP_MODULE_5)},
    #endif
    #ifdef PWM_CCP5_OC4_RB6_RP6
    {PB6, HAL_LL_TIM_INDEX_2, HAL_LL_CCP_CHANNEL_4, hal_ll_tim_module_num(CCP_MODULE_5)},
    #endif
    #ifdef PWM_CCP5_OC4_RB7_RP7
    {PB7, HAL_LL_TIM_INDEX_2, HAL_LL_CCP_CHANNEL_4, hal_ll_tim_module_num(CCP_MODULE_5)},
    #endif
    #ifdef PWM_CCP5_OC4_RB8_RP8
    {PB8, HAL_LL_TIM_INDEX_2, HAL_LL_CCP_CHANNEL_4, hal_ll_tim_module_num(CCP_MODULE_5)},
    #endif
    #ifdef PWM_CCP5_OC4_RB9_RP9
    {PB9, HAL_LL_TIM_INDEX_2, HAL_LL_CCP_CHANNEL_4, hal_ll_tim_module_num(CCP_MODULE_5)},
    #endif
    #ifdef PWM_CCP1_OC1_RC0_RP16
    {PC0, HAL_LL_TIM_INDEX_2, HAL_LL_CCP_CHANNEL_1, hal_ll_tim_module_num(CCP_MODULE_1)},
    #endif
    #ifdef PWM_CCP1_OC1_RC1_RP17
    {PC1, HAL_LL_TIM_INDEX_2, HAL_LL_CCP_CHANNEL_1, hal_ll_tim_module_num(CCP_MODULE_1)},
    #endif
    #ifdef PWM_CCP1_OC1_RC2_RP18
    {PC2, HAL_LL_TIM_INDEX_2, HAL_LL_CCP_CHANNEL_1, hal_ll_tim_module_num(CCP_MODULE_1)},
    #endif
    #ifdef PWM_CCP1_OC1_RC3_RP19
    {PC3, HAL_LL_TIM_INDEX_2, HAL_LL_CCP_CHANNEL_1, hal_ll_tim_module_num(CCP_MODULE_1)},
    #endif
    #ifdef PWM_CCP1_OC1_RC4_RP20
    {PC4, HAL_LL_TIM_INDEX_2, HAL_LL_CCP_CHANNEL_1, hal_ll_tim_module_num(CCP_MODULE_1)},
    #endif
    #ifdef PWM_CCP1_OC1_RC5_RP21
    {PC5, HAL_LL_TIM_INDEX_2, HAL_LL_CCP_CHANNEL_1, hal_ll_tim_module_num(CCP_MODULE_1)},
    #endif
    #ifdef PWM_CCP1_OC1_RC6_RP22
    {PC6, HAL_LL_TIM_INDEX_2, HAL_LL_CCP_CHANNEL_1, hal_ll_tim_module_num(CCP_MODULE_1)},
    #endif
    #ifdef PWM_CCP1_OC1_RC7_RP23
    {PC7, HAL_LL_TIM_INDEX_2, HAL_LL_CCP_CHANNEL_1, hal_ll_tim_module_num(CCP_MODULE_1)},
    #endif
    #ifdef PWM_CCP1_OC1_RC8_RP24
    {PC8, HAL_LL_TIM_INDEX_2, HAL_LL_CCP_CHANNEL_1, hal_ll_tim_module_num(CCP_MODULE_1)},
    #endif
    #ifdef PWM_CCP1_OC1_RC9_RP25
    {PC9, HAL_LL_TIM_INDEX_2, HAL_LL_CCP_CHANNEL_1, hal_ll_tim_module_num(CCP_MODULE_1)},
    #endif
    #ifdef PWM_CCP1_OC2_RC0_RP16
    {PC0, HAL_LL_TIM_INDEX_2, HAL_LL_CCP_CHANNEL_2, hal_ll_tim_module_num(CCP_MODULE_1)},
    #endif
    #ifdef PWM_CCP1_OC2_RC1_RP17
    {PC1, HAL_LL_TIM_INDEX_2, HAL_LL_CCP_CHANNEL_2, hal_ll_tim_module_num(CCP_MODULE_1)},
    #endif
    #ifdef PWM_CCP1_OC2_RC2_RP18
    {PC2, HAL_LL_TIM_INDEX_2, HAL_LL_CCP_CHANNEL_2, hal_ll_tim_module_num(CCP_MODULE_1)},
    #endif
    #ifdef PWM_CCP1_OC2_RC3_RP19
    {PC3, HAL_LL_TIM_INDEX_2, HAL_LL_CCP_CHANNEL_2, hal_ll_tim_module_num(CCP_MODULE_1)},
    #endif
    #ifdef PWM_CCP1_OC2_RC4_RP20
    {PC4, HAL_LL_TIM_INDEX_2, HAL_LL_CCP_CHANNEL_2, hal_ll_tim_module_num(CCP_MODULE_1)},
    #endif
    #ifdef PWM_CCP1_OC2_RC5_RP21
    {PC5, HAL_LL_TIM_INDEX_2, HAL_LL_CCP_CHANNEL_2, hal_ll_tim_module_num(CCP_MODULE_1)},
    #endif
    #ifdef PWM_CCP1_OC2_RC6_RP22
    {PC6, HAL_LL_TIM_INDEX_2, HAL_LL_CCP_CHANNEL_2, hal_ll_tim_module_num(CCP_MODULE_1)},
    #endif
    #ifdef PWM_CCP1_OC2_RC7_RP23
    {PC7, HAL_LL_TIM_INDEX_2, HAL_LL_CCP_CHANNEL_2, hal_ll_tim_module_num(CCP_MODULE_1)},
    #endif
    #ifdef PWM_CCP1_OC2_RC8_RP24
    {PC8, HAL_LL_TIM_INDEX_2, HAL_LL_CCP_CHANNEL_2, hal_ll_tim_module_num(CCP_MODULE_1)},
    #endif
    #ifdef PWM_CCP1_OC2_RC9_RP25
    {PC9, HAL_LL_TIM_INDEX_2, HAL_LL_CCP_CHANNEL_2, hal_ll_tim_module_num(CCP_MODULE_1)},
    #endif
    #ifdef PWM_CCP1_OC3_RC0_RP16
    {PC0, HAL_LL_TIM_INDEX_2, HAL_LL_CCP_CHANNEL_3, hal_ll_tim_module_num(CCP_MODULE_1)},
    #endif
    #ifdef PWM_CCP1_OC3_RC1_RP17
    {PC1, HAL_LL_TIM_INDEX_2, HAL_LL_CCP_CHANNEL_3, hal_ll_tim_module_num(CCP_MODULE_1)},
    #endif
    #ifdef PWM_CCP1_OC3_RC2_RP18
    {PC2, HAL_LL_TIM_INDEX_2, HAL_LL_CCP_CHANNEL_3, hal_ll_tim_module_num(CCP_MODULE_1)},
    #endif
    #ifdef PWM_CCP1_OC3_RC3_RP19
    {PC3, HAL_LL_TIM_INDEX_2, HAL_LL_CCP_CHANNEL_3, hal_ll_tim_module_num(CCP_MODULE_1)},
    #endif
    #ifdef PWM_CCP1_OC3_RC4_RP20
    {PC4, HAL_LL_TIM_INDEX_2, HAL_LL_CCP_CHANNEL_3, hal_ll_tim_module_num(CCP_MODULE_1)},
    #endif
    #ifdef PWM_CCP1_OC3_RC5_RP21
    {PC5, HAL_LL_TIM_INDEX_2, HAL_LL_CCP_CHANNEL_3, hal_ll_tim_module_num(CCP_MODULE_1)},
    #endif
    #ifdef PWM_CCP1_OC3_RC6_RP22
    {PC6, HAL_LL_TIM_INDEX_2, HAL_LL_CCP_CHANNEL_3, hal_ll_tim_module_num(CCP_MODULE_1)},
    #endif
    #ifdef PWM_CCP1_OC3_RC7_RP23
    {PC7, HAL_LL_TIM_INDEX_2, HAL_LL_CCP_CHANNEL_3, hal_ll_tim_module_num(CCP_MODULE_1)},
    #endif
    #ifdef PWM_CCP1_OC3_RC8_RP24
    {PC8, HAL_LL_TIM_INDEX_2, HAL_LL_CCP_CHANNEL_3, hal_ll_tim_module_num(CCP_MODULE_1)},
    #endif
    #ifdef PWM_CCP1_OC3_RC9_RP25
    {PC9, HAL_LL_TIM_INDEX_2, HAL_LL_CCP_CHANNEL_3, hal_ll_tim_module_num(CCP_MODULE_1)},
    #endif
    #ifdef PWM_CCP1_OC4_RC0_RP16
    {PC0, HAL_LL_TIM_INDEX_2, HAL_LL_CCP_CHANNEL_4, hal_ll_tim_module_num(CCP_MODULE_1)},
    #endif
    #ifdef PWM_CCP1_OC4_RC1_RP17
    {PC1, HAL_LL_TIM_INDEX_2, HAL_LL_CCP_CHANNEL_4, hal_ll_tim_module_num(CCP_MODULE_1)},
    #endif
    #ifdef PWM_CCP1_OC4_RC2_RP18
    {PC2, HAL_LL_TIM_INDEX_2, HAL_LL_CCP_CHANNEL_4, hal_ll_tim_module_num(CCP_MODULE_1)},
    #endif
    #ifdef PWM_CCP1_OC4_RC3_RP19
    {PC3, HAL_LL_TIM_INDEX_2, HAL_LL_CCP_CHANNEL_4, hal_ll_tim_module_num(CCP_MODULE_1)},
    #endif
    #ifdef PWM_CCP1_OC4_RC4_RP20
    {PC4, HAL_LL_TIM_INDEX_2, HAL_LL_CCP_CHANNEL_4, hal_ll_tim_module_num(CCP_MODULE_1)},
    #endif
    #ifdef PWM_CCP1_OC4_RC5_RP21
    {PC5, HAL_LL_TIM_INDEX_2, HAL_LL_CCP_CHANNEL_4, hal_ll_tim_module_num(CCP_MODULE_1)},
    #endif
    #ifdef PWM_CCP1_OC4_RC6_RP22
    {PC6, HAL_LL_TIM_INDEX_2, HAL_LL_CCP_CHANNEL_4, hal_ll_tim_module_num(CCP_MODULE_1)},
    #endif
    #ifdef PWM_CCP1_OC4_RC7_RP23
    {PC7, HAL_LL_TIM_INDEX_2, HAL_LL_CCP_CHANNEL_4, hal_ll_tim_module_num(CCP_MODULE_1)},
    #endif
    #ifdef PWM_CCP1_OC4_RC8_RP24
    {PC8, HAL_LL_TIM_INDEX_2, HAL_LL_CCP_CHANNEL_4, hal_ll_tim_module_num(CCP_MODULE_1)},
    #endif
    #ifdef PWM_CCP1_OC4_RC9_RP25
    {PC9, HAL_LL_TIM_INDEX_2, HAL_LL_CCP_CHANNEL_4, hal_ll_tim_module_num(CCP_MODULE_1)},
    #endif
    #ifdef PWM_CCP2_OC1_RC0_RP16
    {PC0, HAL_LL_TIM_INDEX_2, HAL_LL_CCP_CHANNEL_1, hal_ll_tim_module_num(CCP_MODULE_2)},
    #endif
    #ifdef PWM_CCP2_OC1_RC1_RP17
    {PC1, HAL_LL_TIM_INDEX_2, HAL_LL_CCP_CHANNEL_1, hal_ll_tim_module_num(CCP_MODULE_2)},
    #endif
    #ifdef PWM_CCP2_OC1_RC2_RP18
    {PC2, HAL_LL_TIM_INDEX_2, HAL_LL_CCP_CHANNEL_1, hal_ll_tim_module_num(CCP_MODULE_2)},
    #endif
    #ifdef PWM_CCP2_OC1_RC3_RP19
    {PC3, HAL_LL_TIM_INDEX_2, HAL_LL_CCP_CHANNEL_1, hal_ll_tim_module_num(CCP_MODULE_2)},
    #endif
    #ifdef PWM_CCP2_OC1_RC4_RP20
    {PC4, HAL_LL_TIM_INDEX_2, HAL_LL_CCP_CHANNEL_1, hal_ll_tim_module_num(CCP_MODULE_2)},
    #endif
    #ifdef PWM_CCP2_OC1_RC5_RP21
    {PC5, HAL_LL_TIM_INDEX_2, HAL_LL_CCP_CHANNEL_1, hal_ll_tim_module_num(CCP_MODULE_2)},
    #endif
    #ifdef PWM_CCP2_OC1_RC6_RP22
    {PC6, HAL_LL_TIM_INDEX_2, HAL_LL_CCP_CHANNEL_1, hal_ll_tim_module_num(CCP_MODULE_2)},
    #endif
    #ifdef PWM_CCP2_OC1_RC7_RP23
    {PC7, HAL_LL_TIM_INDEX_2, HAL_LL_CCP_CHANNEL_1, hal_ll_tim_module_num(CCP_MODULE_2)},
    #endif
    #ifdef PWM_CCP2_OC1_RC8_RP24
    {PC8, HAL_LL_TIM_INDEX_2, HAL_LL_CCP_CHANNEL_1, hal_ll_tim_module_num(CCP_MODULE_2)},
    #endif
    #ifdef PWM_CCP2_OC1_RC9_RP25
    {PC9, HAL_LL_TIM_INDEX_2, HAL_LL_CCP_CHANNEL_1, hal_ll_tim_module_num(CCP_MODULE_2)},
    #endif
    #ifdef PWM_CCP2_OC2_RC0_RP16
    {PC0, HAL_LL_TIM_INDEX_2, HAL_LL_CCP_CHANNEL_2, hal_ll_tim_module_num(CCP_MODULE_2)},
    #endif
    #ifdef PWM_CCP2_OC2_RC1_RP17
    {PC1, HAL_LL_TIM_INDEX_2, HAL_LL_CCP_CHANNEL_2, hal_ll_tim_module_num(CCP_MODULE_2)},
    #endif
    #ifdef PWM_CCP2_OC2_RC2_RP18
    {PC2, HAL_LL_TIM_INDEX_2, HAL_LL_CCP_CHANNEL_2, hal_ll_tim_module_num(CCP_MODULE_2)},
    #endif
    #ifdef PWM_CCP2_OC2_RC3_RP19
    {PC3, HAL_LL_TIM_INDEX_2, HAL_LL_CCP_CHANNEL_2, hal_ll_tim_module_num(CCP_MODULE_2)},
    #endif
    #ifdef PWM_CCP2_OC2_RC4_RP20
    {PC4, HAL_LL_TIM_INDEX_2, HAL_LL_CCP_CHANNEL_2, hal_ll_tim_module_num(CCP_MODULE_2)},
    #endif
    #ifdef PWM_CCP2_OC2_RC5_RP21
    {PC5, HAL_LL_TIM_INDEX_2, HAL_LL_CCP_CHANNEL_2, hal_ll_tim_module_num(CCP_MODULE_2)},
    #endif
    #ifdef PWM_CCP2_OC2_RC6_RP22
    {PC6, HAL_LL_TIM_INDEX_2, HAL_LL_CCP_CHANNEL_2, hal_ll_tim_module_num(CCP_MODULE_2)},
    #endif
    #ifdef PWM_CCP2_OC2_RC7_RP23
    {PC7, HAL_LL_TIM_INDEX_2, HAL_LL_CCP_CHANNEL_2, hal_ll_tim_module_num(CCP_MODULE_2)},
    #endif
    #ifdef PWM_CCP2_OC2_RC8_RP24
    {PC8, HAL_LL_TIM_INDEX_2, HAL_LL_CCP_CHANNEL_2, hal_ll_tim_module_num(CCP_MODULE_2)},
    #endif
    #ifdef PWM_CCP2_OC2_RC9_RP25
    {PC9, HAL_LL_TIM_INDEX_2, HAL_LL_CCP_CHANNEL_2, hal_ll_tim_module_num(CCP_MODULE_2)},
    #endif
    #ifdef PWM_CCP2_OC3_RC0_RP16
    {PC0, HAL_LL_TIM_INDEX_2, HAL_LL_CCP_CHANNEL_3, hal_ll_tim_module_num(CCP_MODULE_2)},
    #endif
    #ifdef PWM_CCP2_OC3_RC1_RP17
    {PC1, HAL_LL_TIM_INDEX_2, HAL_LL_CCP_CHANNEL_3, hal_ll_tim_module_num(CCP_MODULE_2)},
    #endif
    #ifdef PWM_CCP2_OC3_RC2_RP18
    {PC2, HAL_LL_TIM_INDEX_2, HAL_LL_CCP_CHANNEL_3, hal_ll_tim_module_num(CCP_MODULE_2)},
    #endif
    #ifdef PWM_CCP2_OC3_RC3_RP19
    {PC3, HAL_LL_TIM_INDEX_2, HAL_LL_CCP_CHANNEL_3, hal_ll_tim_module_num(CCP_MODULE_2)},
    #endif
    #ifdef PWM_CCP2_OC3_RC4_RP20
    {PC4, HAL_LL_TIM_INDEX_2, HAL_LL_CCP_CHANNEL_3, hal_ll_tim_module_num(CCP_MODULE_2)},
    #endif
    #ifdef PWM_CCP2_OC3_RC5_RP21
    {PC5, HAL_LL_TIM_INDEX_2, HAL_LL_CCP_CHANNEL_3, hal_ll_tim_module_num(CCP_MODULE_2)},
    #endif
    #ifdef PWM_CCP2_OC3_RC6_RP22
    {PC6, HAL_LL_TIM_INDEX_2, HAL_LL_CCP_CHANNEL_3, hal_ll_tim_module_num(CCP_MODULE_2)},
    #endif
    #ifdef PWM_CCP2_OC3_RC7_RP23
    {PC7, HAL_LL_TIM_INDEX_2, HAL_LL_CCP_CHANNEL_3, hal_ll_tim_module_num(CCP_MODULE_2)},
    #endif
    #ifdef PWM_CCP2_OC3_RC8_RP24
    {PC8, HAL_LL_TIM_INDEX_2, HAL_LL_CCP_CHANNEL_3, hal_ll_tim_module_num(CCP_MODULE_2)},
    #endif
    #ifdef PWM_CCP2_OC3_RC9_RP25
    {PC9, HAL_LL_TIM_INDEX_2, HAL_LL_CCP_CHANNEL_3, hal_ll_tim_module_num(CCP_MODULE_2)},
    #endif
    #ifdef PWM_CCP2_OC4_RC0_RP16
    {PC0, HAL_LL_TIM_INDEX_2, HAL_LL_CCP_CHANNEL_4, hal_ll_tim_module_num(CCP_MODULE_2)},
    #endif
    #ifdef PWM_CCP2_OC4_RC1_RP17
    {PC1, HAL_LL_TIM_INDEX_2, HAL_LL_CCP_CHANNEL_4, hal_ll_tim_module_num(CCP_MODULE_2)},
    #endif
    #ifdef PWM_CCP2_OC4_RC2_RP18
    {PC2, HAL_LL_TIM_INDEX_2, HAL_LL_CCP_CHANNEL_4, hal_ll_tim_module_num(CCP_MODULE_2)},
    #endif
    #ifdef PWM_CCP2_OC4_RC3_RP19
    {PC3, HAL_LL_TIM_INDEX_2, HAL_LL_CCP_CHANNEL_4, hal_ll_tim_module_num(CCP_MODULE_2)},
    #endif
    #ifdef PWM_CCP2_OC4_RC4_RP20
    {PC4, HAL_LL_TIM_INDEX_2, HAL_LL_CCP_CHANNEL_4, hal_ll_tim_module_num(CCP_MODULE_2)},
    #endif
    #ifdef PWM_CCP2_OC4_RC5_RP21
    {PC5, HAL_LL_TIM_INDEX_2, HAL_LL_CCP_CHANNEL_4, hal_ll_tim_module_num(CCP_MODULE_2)},
    #endif
    #ifdef PWM_CCP2_OC4_RC6_RP22
    {PC6, HAL_LL_TIM_INDEX_2, HAL_LL_CCP_CHANNEL_4, hal_ll_tim_module_num(CCP_MODULE_2)},
    #endif
    #ifdef PWM_CCP2_OC4_RC7_RP23
    {PC7, HAL_LL_TIM_INDEX_2, HAL_LL_CCP_CHANNEL_4, hal_ll_tim_module_num(CCP_MODULE_2)},
    #endif
    #ifdef PWM_CCP2_OC4_RC8_RP24
    {PC8, HAL_LL_TIM_INDEX_2, HAL_LL_CCP_CHANNEL_4, hal_ll_tim_module_num(CCP_MODULE_2)},
    #endif
    #ifdef PWM_CCP2_OC4_RC9_RP25
    {PC9, HAL_LL_TIM_INDEX_2, HAL_LL_CCP_CHANNEL_4, hal_ll_tim_module_num(CCP_MODULE_2)},
    #endif
    #ifdef PWM_CCP3_OC1_RC0_RP16
    {PC0, HAL_LL_TIM_INDEX_2, HAL_LL_CCP_CHANNEL_1, hal_ll_tim_module_num(CCP_MODULE_3)},
    #endif
    #ifdef PWM_CCP3_OC1_RC1_RP17
    {PC1, HAL_LL_TIM_INDEX_2, HAL_LL_CCP_CHANNEL_1, hal_ll_tim_module_num(CCP_MODULE_3)},
    #endif
    #ifdef PWM_CCP3_OC1_RC2_RP18
    {PC2, HAL_LL_TIM_INDEX_2, HAL_LL_CCP_CHANNEL_1, hal_ll_tim_module_num(CCP_MODULE_3)},
    #endif
    #ifdef PWM_CCP3_OC1_RC3_RP19
    {PC3, HAL_LL_TIM_INDEX_2, HAL_LL_CCP_CHANNEL_1, hal_ll_tim_module_num(CCP_MODULE_3)},
    #endif
    #ifdef PWM_CCP3_OC1_RC4_RP20
    {PC4, HAL_LL_TIM_INDEX_2, HAL_LL_CCP_CHANNEL_1, hal_ll_tim_module_num(CCP_MODULE_3)},
    #endif
    #ifdef PWM_CCP3_OC1_RC5_RP21
    {PC5, HAL_LL_TIM_INDEX_2, HAL_LL_CCP_CHANNEL_1, hal_ll_tim_module_num(CCP_MODULE_3)},
    #endif
    #ifdef PWM_CCP3_OC1_RC6_RP22
    {PC6, HAL_LL_TIM_INDEX_2, HAL_LL_CCP_CHANNEL_1, hal_ll_tim_module_num(CCP_MODULE_3)},
    #endif
    #ifdef PWM_CCP3_OC1_RC7_RP23
    {PC7, HAL_LL_TIM_INDEX_2, HAL_LL_CCP_CHANNEL_1, hal_ll_tim_module_num(CCP_MODULE_3)},
    #endif
    #ifdef PWM_CCP3_OC1_RC8_RP24
    {PC8, HAL_LL_TIM_INDEX_2, HAL_LL_CCP_CHANNEL_1, hal_ll_tim_module_num(CCP_MODULE_3)},
    #endif
    #ifdef PWM_CCP3_OC1_RC9_RP25
    {PC9, HAL_LL_TIM_INDEX_2, HAL_LL_CCP_CHANNEL_1, hal_ll_tim_module_num(CCP_MODULE_3)},
    #endif
    #ifdef PWM_CCP3_OC2_RC0_RP16
    {PC0, HAL_LL_TIM_INDEX_2, HAL_LL_CCP_CHANNEL_2, hal_ll_tim_module_num(CCP_MODULE_3)},
    #endif
    #ifdef PWM_CCP3_OC2_RC1_RP17
    {PC1, HAL_LL_TIM_INDEX_2, HAL_LL_CCP_CHANNEL_2, hal_ll_tim_module_num(CCP_MODULE_3)},
    #endif
    #ifdef PWM_CCP3_OC2_RC2_RP18
    {PC2, HAL_LL_TIM_INDEX_2, HAL_LL_CCP_CHANNEL_2, hal_ll_tim_module_num(CCP_MODULE_3)},
    #endif
    #ifdef PWM_CCP3_OC2_RC3_RP19
    {PC3, HAL_LL_TIM_INDEX_2, HAL_LL_CCP_CHANNEL_2, hal_ll_tim_module_num(CCP_MODULE_3)},
    #endif
    #ifdef PWM_CCP3_OC2_RC4_RP20
    {PC4, HAL_LL_TIM_INDEX_2, HAL_LL_CCP_CHANNEL_2, hal_ll_tim_module_num(CCP_MODULE_3)},
    #endif
    #ifdef PWM_CCP3_OC2_RC5_RP21
    {PC5, HAL_LL_TIM_INDEX_2, HAL_LL_CCP_CHANNEL_2, hal_ll_tim_module_num(CCP_MODULE_3)},
    #endif
    #ifdef PWM_CCP3_OC2_RC6_RP22
    {PC6, HAL_LL_TIM_INDEX_2, HAL_LL_CCP_CHANNEL_2, hal_ll_tim_module_num(CCP_MODULE_3)},
    #endif
    #ifdef PWM_CCP3_OC2_RC7_RP23
    {PC7, HAL_LL_TIM_INDEX_2, HAL_LL_CCP_CHANNEL_2, hal_ll_tim_module_num(CCP_MODULE_3)},
    #endif
    #ifdef PWM_CCP3_OC2_RC8_RP24
    {PC8, HAL_LL_TIM_INDEX_2, HAL_LL_CCP_CHANNEL_2, hal_ll_tim_module_num(CCP_MODULE_3)},
    #endif
    #ifdef PWM_CCP3_OC2_RC9_RP25
    {PC9, HAL_LL_TIM_INDEX_2, HAL_LL_CCP_CHANNEL_2, hal_ll_tim_module_num(CCP_MODULE_3)},
    #endif
    #ifdef PWM_CCP3_OC3_RC0_RP16
    {PC0, HAL_LL_TIM_INDEX_2, HAL_LL_CCP_CHANNEL_3, hal_ll_tim_module_num(CCP_MODULE_3)},
    #endif
    #ifdef PWM_CCP3_OC3_RC1_RP17
    {PC1, HAL_LL_TIM_INDEX_2, HAL_LL_CCP_CHANNEL_3, hal_ll_tim_module_num(CCP_MODULE_3)},
    #endif
    #ifdef PWM_CCP3_OC3_RC2_RP18
    {PC2, HAL_LL_TIM_INDEX_2, HAL_LL_CCP_CHANNEL_3, hal_ll_tim_module_num(CCP_MODULE_3)},
    #endif
    #ifdef PWM_CCP3_OC3_RC3_RP19
    {PC3, HAL_LL_TIM_INDEX_2, HAL_LL_CCP_CHANNEL_3, hal_ll_tim_module_num(CCP_MODULE_3)},
    #endif
    #ifdef PWM_CCP3_OC3_RC4_RP20
    {PC4, HAL_LL_TIM_INDEX_2, HAL_LL_CCP_CHANNEL_3, hal_ll_tim_module_num(CCP_MODULE_3)},
    #endif
    #ifdef PWM_CCP3_OC3_RC5_RP21
    {PC5, HAL_LL_TIM_INDEX_2, HAL_LL_CCP_CHANNEL_3, hal_ll_tim_module_num(CCP_MODULE_3)},
    #endif
    #ifdef PWM_CCP3_OC3_RC6_RP22
    {PC6, HAL_LL_TIM_INDEX_2, HAL_LL_CCP_CHANNEL_3, hal_ll_tim_module_num(CCP_MODULE_3)},
    #endif
    #ifdef PWM_CCP3_OC3_RC7_RP23
    {PC7, HAL_LL_TIM_INDEX_2, HAL_LL_CCP_CHANNEL_3, hal_ll_tim_module_num(CCP_MODULE_3)},
    #endif
    #ifdef PWM_CCP3_OC3_RC8_RP24
    {PC8, HAL_LL_TIM_INDEX_2, HAL_LL_CCP_CHANNEL_3, hal_ll_tim_module_num(CCP_MODULE_3)},
    #endif
    #ifdef PWM_CCP3_OC3_RC9_RP25
    {PC9, HAL_LL_TIM_INDEX_2, HAL_LL_CCP_CHANNEL_3, hal_ll_tim_module_num(CCP_MODULE_3)},
    #endif
    #ifdef PWM_CCP3_OC4_RC0_RP16
    {PC0, HAL_LL_TIM_INDEX_2, HAL_LL_CCP_CHANNEL_4, hal_ll_tim_module_num(CCP_MODULE_3)},
    #endif
    #ifdef PWM_CCP3_OC4_RC1_RP17
    {PC1, HAL_LL_TIM_INDEX_2, HAL_LL_CCP_CHANNEL_4, hal_ll_tim_module_num(CCP_MODULE_3)},
    #endif
    #ifdef PWM_CCP3_OC4_RC2_RP18
    {PC2, HAL_LL_TIM_INDEX_2, HAL_LL_CCP_CHANNEL_4, hal_ll_tim_module_num(CCP_MODULE_3)},
    #endif
    #ifdef PWM_CCP3_OC4_RC3_RP19
    {PC3, HAL_LL_TIM_INDEX_2, HAL_LL_CCP_CHANNEL_4, hal_ll_tim_module_num(CCP_MODULE_3)},
    #endif
    #ifdef PWM_CCP3_OC4_RC4_RP20
    {PC4, HAL_LL_TIM_INDEX_2, HAL_LL_CCP_CHANNEL_4, hal_ll_tim_module_num(CCP_MODULE_3)},
    #endif
    #ifdef PWM_CCP3_OC4_RC5_RP21
    {PC5, HAL_LL_TIM_INDEX_2, HAL_LL_CCP_CHANNEL_4, hal_ll_tim_module_num(CCP_MODULE_3)},
    #endif
    #ifdef PWM_CCP3_OC4_RC6_RP22
    {PC6, HAL_LL_TIM_INDEX_2, HAL_LL_CCP_CHANNEL_4, hal_ll_tim_module_num(CCP_MODULE_3)},
    #endif
    #ifdef PWM_CCP3_OC4_RC7_RP23
    {PC7, HAL_LL_TIM_INDEX_2, HAL_LL_CCP_CHANNEL_4, hal_ll_tim_module_num(CCP_MODULE_3)},
    #endif
    #ifdef PWM_CCP3_OC4_RC8_RP24
    {PC8, HAL_LL_TIM_INDEX_2, HAL_LL_CCP_CHANNEL_4, hal_ll_tim_module_num(CCP_MODULE_3)},
    #endif
    #ifdef PWM_CCP3_OC4_RC9_RP25
    {PC9, HAL_LL_TIM_INDEX_2, HAL_LL_CCP_CHANNEL_4, hal_ll_tim_module_num(CCP_MODULE_3)},
    #endif
    #ifdef PWM_CCP4_OC1_RC0_RP16
    {PC0, HAL_LL_TIM_INDEX_2, HAL_LL_CCP_CHANNEL_1, hal_ll_tim_module_num(CCP_MODULE_4)},
    #endif
    #ifdef PWM_CCP4_OC1_RC1_RP17
    {PC1, HAL_LL_TIM_INDEX_2, HAL_LL_CCP_CHANNEL_1, hal_ll_tim_module_num(CCP_MODULE_4)},
    #endif
    #ifdef PWM_CCP4_OC1_RC2_RP18
    {PC2, HAL_LL_TIM_INDEX_2, HAL_LL_CCP_CHANNEL_1, hal_ll_tim_module_num(CCP_MODULE_4)},
    #endif
    #ifdef PWM_CCP4_OC1_RC3_RP19
    {PC3, HAL_LL_TIM_INDEX_2, HAL_LL_CCP_CHANNEL_1, hal_ll_tim_module_num(CCP_MODULE_4)},
    #endif
    #ifdef PWM_CCP4_OC1_RC4_RP20
    {PC4, HAL_LL_TIM_INDEX_2, HAL_LL_CCP_CHANNEL_1, hal_ll_tim_module_num(CCP_MODULE_4)},
    #endif
    #ifdef PWM_CCP4_OC1_RC5_RP21
    {PC5, HAL_LL_TIM_INDEX_2, HAL_LL_CCP_CHANNEL_1, hal_ll_tim_module_num(CCP_MODULE_4)},
    #endif
    #ifdef PWM_CCP4_OC1_RC6_RP22
    {PC6, HAL_LL_TIM_INDEX_2, HAL_LL_CCP_CHANNEL_1, hal_ll_tim_module_num(CCP_MODULE_4)},
    #endif
    #ifdef PWM_CCP4_OC1_RC7_RP23
    {PC7, HAL_LL_TIM_INDEX_2, HAL_LL_CCP_CHANNEL_1, hal_ll_tim_module_num(CCP_MODULE_4)},
    #endif
    #ifdef PWM_CCP4_OC1_RC8_RP24
    {PC8, HAL_LL_TIM_INDEX_2, HAL_LL_CCP_CHANNEL_1, hal_ll_tim_module_num(CCP_MODULE_4)},
    #endif
    #ifdef PWM_CCP4_OC1_RC9_RP25
    {PC9, HAL_LL_TIM_INDEX_2, HAL_LL_CCP_CHANNEL_1, hal_ll_tim_module_num(CCP_MODULE_4)},
    #endif
    #ifdef PWM_CCP4_OC2_RC0_RP16
    {PC0, HAL_LL_TIM_INDEX_2, HAL_LL_CCP_CHANNEL_2, hal_ll_tim_module_num(CCP_MODULE_4)},
    #endif
    #ifdef PWM_CCP4_OC2_RC1_RP17
    {PC1, HAL_LL_TIM_INDEX_2, HAL_LL_CCP_CHANNEL_2, hal_ll_tim_module_num(CCP_MODULE_4)},
    #endif
    #ifdef PWM_CCP4_OC2_RC2_RP18
    {PC2, HAL_LL_TIM_INDEX_2, HAL_LL_CCP_CHANNEL_2, hal_ll_tim_module_num(CCP_MODULE_4)},
    #endif
    #ifdef PWM_CCP4_OC2_RC3_RP19
    {PC3, HAL_LL_TIM_INDEX_2, HAL_LL_CCP_CHANNEL_2, hal_ll_tim_module_num(CCP_MODULE_4)},
    #endif
    #ifdef PWM_CCP4_OC2_RC4_RP20
    {PC4, HAL_LL_TIM_INDEX_2, HAL_LL_CCP_CHANNEL_2, hal_ll_tim_module_num(CCP_MODULE_4)},
    #endif
    #ifdef PWM_CCP4_OC2_RC5_RP21
    {PC5, HAL_LL_TIM_INDEX_2, HAL_LL_CCP_CHANNEL_2, hal_ll_tim_module_num(CCP_MODULE_4)},
    #endif
    #ifdef PWM_CCP4_OC2_RC6_RP22
    {PC6, HAL_LL_TIM_INDEX_2, HAL_LL_CCP_CHANNEL_2, hal_ll_tim_module_num(CCP_MODULE_4)},
    #endif
    #ifdef PWM_CCP4_OC2_RC7_RP23
    {PC7, HAL_LL_TIM_INDEX_2, HAL_LL_CCP_CHANNEL_2, hal_ll_tim_module_num(CCP_MODULE_4)},
    #endif
    #ifdef PWM_CCP4_OC2_RC8_RP24
    {PC8, HAL_LL_TIM_INDEX_2, HAL_LL_CCP_CHANNEL_2, hal_ll_tim_module_num(CCP_MODULE_4)},
    #endif
    #ifdef PWM_CCP4_OC2_RC9_RP25
    {PC9, HAL_LL_TIM_INDEX_2, HAL_LL_CCP_CHANNEL_2, hal_ll_tim_module_num(CCP_MODULE_4)},
    #endif
    #ifdef PWM_CCP4_OC3_RC0_RP16
    {PC0, HAL_LL_TIM_INDEX_2, HAL_LL_CCP_CHANNEL_3, hal_ll_tim_module_num(CCP_MODULE_4)},
    #endif
    #ifdef PWM_CCP4_OC3_RC1_RP17
    {PC1, HAL_LL_TIM_INDEX_2, HAL_LL_CCP_CHANNEL_3, hal_ll_tim_module_num(CCP_MODULE_4)},
    #endif
    #ifdef PWM_CCP4_OC3_RC2_RP18
    {PC2, HAL_LL_TIM_INDEX_2, HAL_LL_CCP_CHANNEL_3, hal_ll_tim_module_num(CCP_MODULE_4)},
    #endif
    #ifdef PWM_CCP4_OC3_RC3_RP19
    {PC3, HAL_LL_TIM_INDEX_2, HAL_LL_CCP_CHANNEL_3, hal_ll_tim_module_num(CCP_MODULE_4)},
    #endif
    #ifdef PWM_CCP4_OC3_RC4_RP20
    {PC4, HAL_LL_TIM_INDEX_2, HAL_LL_CCP_CHANNEL_3, hal_ll_tim_module_num(CCP_MODULE_4)},
    #endif
    #ifdef PWM_CCP4_OC3_RC5_RP21
    {PC5, HAL_LL_TIM_INDEX_2, HAL_LL_CCP_CHANNEL_3, hal_ll_tim_module_num(CCP_MODULE_4)},
    #endif
    #ifdef PWM_CCP4_OC3_RC6_RP22
    {PC6, HAL_LL_TIM_INDEX_2, HAL_LL_CCP_CHANNEL_3, hal_ll_tim_module_num(CCP_MODULE_4)},
    #endif
    #ifdef PWM_CCP4_OC3_RC7_RP23
    {PC7, HAL_LL_TIM_INDEX_2, HAL_LL_CCP_CHANNEL_3, hal_ll_tim_module_num(CCP_MODULE_4)},
    #endif
    #ifdef PWM_CCP4_OC3_RC8_RP24
    {PC8, HAL_LL_TIM_INDEX_2, HAL_LL_CCP_CHANNEL_3, hal_ll_tim_module_num(CCP_MODULE_4)},
    #endif
    #ifdef PWM_CCP4_OC3_RC9_RP25
    {PC9, HAL_LL_TIM_INDEX_2, HAL_LL_CCP_CHANNEL_3, hal_ll_tim_module_num(CCP_MODULE_4)},
    #endif
    #ifdef PWM_CCP4_OC4_RC0_RP16
    {PC0, HAL_LL_TIM_INDEX_2, HAL_LL_CCP_CHANNEL_4, hal_ll_tim_module_num(CCP_MODULE_4)},
    #endif
    #ifdef PWM_CCP4_OC4_RC1_RP17
    {PC1, HAL_LL_TIM_INDEX_2, HAL_LL_CCP_CHANNEL_4, hal_ll_tim_module_num(CCP_MODULE_4)},
    #endif
    #ifdef PWM_CCP4_OC4_RC2_RP18
    {PC2, HAL_LL_TIM_INDEX_2, HAL_LL_CCP_CHANNEL_4, hal_ll_tim_module_num(CCP_MODULE_4)},
    #endif
    #ifdef PWM_CCP4_OC4_RC3_RP19
    {PC3, HAL_LL_TIM_INDEX_2, HAL_LL_CCP_CHANNEL_4, hal_ll_tim_module_num(CCP_MODULE_4)},
    #endif
    #ifdef PWM_CCP4_OC4_RC4_RP20
    {PC4, HAL_LL_TIM_INDEX_2, HAL_LL_CCP_CHANNEL_4, hal_ll_tim_module_num(CCP_MODULE_4)},
    #endif
    #ifdef PWM_CCP4_OC4_RC5_RP21
    {PC5, HAL_LL_TIM_INDEX_2, HAL_LL_CCP_CHANNEL_4, hal_ll_tim_module_num(CCP_MODULE_4)},
    #endif
    #ifdef PWM_CCP4_OC4_RC6_RP22
    {PC6, HAL_LL_TIM_INDEX_2, HAL_LL_CCP_CHANNEL_4, hal_ll_tim_module_num(CCP_MODULE_4)},
    #endif
    #ifdef PWM_CCP4_OC4_RC7_RP23
    {PC7, HAL_LL_TIM_INDEX_2, HAL_LL_CCP_CHANNEL_4, hal_ll_tim_module_num(CCP_MODULE_4)},
    #endif
    #ifdef PWM_CCP4_OC4_RC8_RP24
    {PC8, HAL_LL_TIM_INDEX_2, HAL_LL_CCP_CHANNEL_4, hal_ll_tim_module_num(CCP_MODULE_4)},
    #endif
    #ifdef PWM_CCP4_OC4_RC9_RP25
    {PC9, HAL_LL_TIM_INDEX_2, HAL_LL_CCP_CHANNEL_4, hal_ll_tim_module_num(CCP_MODULE_4)},
    #endif
    #ifdef PWM_CCP5_OC1_RC0_RP16
    {PC0, HAL_LL_TIM_INDEX_2, HAL_LL_CCP_CHANNEL_1, hal_ll_tim_module_num(CCP_MODULE_5)},
    #endif
    #ifdef PWM_CCP5_OC1_RC1_RP17
    {PC1, HAL_LL_TIM_INDEX_2, HAL_LL_CCP_CHANNEL_1, hal_ll_tim_module_num(CCP_MODULE_5)},
    #endif
    #ifdef PWM_CCP5_OC1_RC2_RP18
    {PC2, HAL_LL_TIM_INDEX_2, HAL_LL_CCP_CHANNEL_1, hal_ll_tim_module_num(CCP_MODULE_5)},
    #endif
    #ifdef PWM_CCP5_OC1_RC3_RP19
    {PC3, HAL_LL_TIM_INDEX_2, HAL_LL_CCP_CHANNEL_1, hal_ll_tim_module_num(CCP_MODULE_5)},
    #endif
    #ifdef PWM_CCP5_OC1_RC4_RP20
    {PC4, HAL_LL_TIM_INDEX_2, HAL_LL_CCP_CHANNEL_1, hal_ll_tim_module_num(CCP_MODULE_5)},
    #endif
    #ifdef PWM_CCP5_OC1_RC5_RP21
    {PC5, HAL_LL_TIM_INDEX_2, HAL_LL_CCP_CHANNEL_1, hal_ll_tim_module_num(CCP_MODULE_5)},
    #endif
    #ifdef PWM_CCP5_OC1_RC6_RP22
    {PC6, HAL_LL_TIM_INDEX_2, HAL_LL_CCP_CHANNEL_1, hal_ll_tim_module_num(CCP_MODULE_5)},
    #endif
    #ifdef PWM_CCP5_OC1_RC7_RP23
    {PC7, HAL_LL_TIM_INDEX_2, HAL_LL_CCP_CHANNEL_1, hal_ll_tim_module_num(CCP_MODULE_5)},
    #endif
    #ifdef PWM_CCP5_OC1_RC8_RP24
    {PC8, HAL_LL_TIM_INDEX_2, HAL_LL_CCP_CHANNEL_1, hal_ll_tim_module_num(CCP_MODULE_5)},
    #endif
    #ifdef PWM_CCP5_OC1_RC9_RP25
    {PC9, HAL_LL_TIM_INDEX_2, HAL_LL_CCP_CHANNEL_1, hal_ll_tim_module_num(CCP_MODULE_5)},
    #endif
    #ifdef PWM_CCP5_OC2_RC0_RP16
    {PC0, HAL_LL_TIM_INDEX_2, HAL_LL_CCP_CHANNEL_2, hal_ll_tim_module_num(CCP_MODULE_5)},
    #endif
    #ifdef PWM_CCP5_OC2_RC1_RP17
    {PC1, HAL_LL_TIM_INDEX_2, HAL_LL_CCP_CHANNEL_2, hal_ll_tim_module_num(CCP_MODULE_5)},
    #endif
    #ifdef PWM_CCP5_OC2_RC2_RP18
    {PC2, HAL_LL_TIM_INDEX_2, HAL_LL_CCP_CHANNEL_2, hal_ll_tim_module_num(CCP_MODULE_5)},
    #endif
    #ifdef PWM_CCP5_OC2_RC3_RP19
    {PC3, HAL_LL_TIM_INDEX_2, HAL_LL_CCP_CHANNEL_2, hal_ll_tim_module_num(CCP_MODULE_5)},
    #endif
    #ifdef PWM_CCP5_OC2_RC4_RP20
    {PC4, HAL_LL_TIM_INDEX_2, HAL_LL_CCP_CHANNEL_2, hal_ll_tim_module_num(CCP_MODULE_5)},
    #endif
    #ifdef PWM_CCP5_OC2_RC5_RP21
    {PC5, HAL_LL_TIM_INDEX_2, HAL_LL_CCP_CHANNEL_2, hal_ll_tim_module_num(CCP_MODULE_5)},
    #endif
    #ifdef PWM_CCP5_OC2_RC6_RP22
    {PC6, HAL_LL_TIM_INDEX_2, HAL_LL_CCP_CHANNEL_2, hal_ll_tim_module_num(CCP_MODULE_5)},
    #endif
    #ifdef PWM_CCP5_OC2_RC7_RP23
    {PC7, HAL_LL_TIM_INDEX_2, HAL_LL_CCP_CHANNEL_2, hal_ll_tim_module_num(CCP_MODULE_5)},
    #endif
    #ifdef PWM_CCP5_OC2_RC8_RP24
    {PC8, HAL_LL_TIM_INDEX_2, HAL_LL_CCP_CHANNEL_2, hal_ll_tim_module_num(CCP_MODULE_5)},
    #endif
    #ifdef PWM_CCP5_OC2_RC9_RP25
    {PC9, HAL_LL_TIM_INDEX_2, HAL_LL_CCP_CHANNEL_2, hal_ll_tim_module_num(CCP_MODULE_5)},
    #endif
    #ifdef PWM_CCP5_OC3_RC0_RP16
    {PC0, HAL_LL_TIM_INDEX_2, HAL_LL_CCP_CHANNEL_3, hal_ll_tim_module_num(CCP_MODULE_5)},
    #endif
    #ifdef PWM_CCP5_OC3_RC1_RP17
    {PC1, HAL_LL_TIM_INDEX_2, HAL_LL_CCP_CHANNEL_3, hal_ll_tim_module_num(CCP_MODULE_5)},
    #endif
    #ifdef PWM_CCP5_OC3_RC2_RP18
    {PC2, HAL_LL_TIM_INDEX_2, HAL_LL_CCP_CHANNEL_3, hal_ll_tim_module_num(CCP_MODULE_5)},
    #endif
    #ifdef PWM_CCP5_OC3_RC3_RP19
    {PC3, HAL_LL_TIM_INDEX_2, HAL_LL_CCP_CHANNEL_3, hal_ll_tim_module_num(CCP_MODULE_5)},
    #endif
    #ifdef PWM_CCP5_OC3_RC4_RP20
    {PC4, HAL_LL_TIM_INDEX_2, HAL_LL_CCP_CHANNEL_3, hal_ll_tim_module_num(CCP_MODULE_5)},
    #endif
    #ifdef PWM_CCP5_OC3_RC5_RP21
    {PC5, HAL_LL_TIM_INDEX_2, HAL_LL_CCP_CHANNEL_3, hal_ll_tim_module_num(CCP_MODULE_5)},
    #endif
    #ifdef PWM_CCP5_OC3_RC6_RP22
    {PC6, HAL_LL_TIM_INDEX_2, HAL_LL_CCP_CHANNEL_3, hal_ll_tim_module_num(CCP_MODULE_5)},
    #endif
    #ifdef PWM_CCP5_OC3_RC7_RP23
    {PC7, HAL_LL_TIM_INDEX_2, HAL_LL_CCP_CHANNEL_3, hal_ll_tim_module_num(CCP_MODULE_5)},
    #endif
    #ifdef PWM_CCP5_OC3_RC8_RP24
    {PC8, HAL_LL_TIM_INDEX_2, HAL_LL_CCP_CHANNEL_3, hal_ll_tim_module_num(CCP_MODULE_5)},
    #endif
    #ifdef PWM_CCP5_OC3_RC9_RP25
    {PC9, HAL_LL_TIM_INDEX_2, HAL_LL_CCP_CHANNEL_3, hal_ll_tim_module_num(CCP_MODULE_5)},
    #endif
    #ifdef PWM_CCP5_OC4_RC0_RP16
    {PC0, HAL_LL_TIM_INDEX_2, HAL_LL_CCP_CHANNEL_4, hal_ll_tim_module_num(CCP_MODULE_5)},
    #endif
    #ifdef PWM_CCP5_OC4_RC1_RP17
    {PC1, HAL_LL_TIM_INDEX_2, HAL_LL_CCP_CHANNEL_4, hal_ll_tim_module_num(CCP_MODULE_5)},
    #endif
    #ifdef PWM_CCP5_OC4_RC2_RP18
    {PC2, HAL_LL_TIM_INDEX_2, HAL_LL_CCP_CHANNEL_4, hal_ll_tim_module_num(CCP_MODULE_5)},
    #endif
    #ifdef PWM_CCP5_OC4_RC3_RP19
    {PC3, HAL_LL_TIM_INDEX_2, HAL_LL_CCP_CHANNEL_4, hal_ll_tim_module_num(CCP_MODULE_5)},
    #endif
    #ifdef PWM_CCP5_OC4_RC4_RP20
    {PC4, HAL_LL_TIM_INDEX_2, HAL_LL_CCP_CHANNEL_4, hal_ll_tim_module_num(CCP_MODULE_5)},
    #endif
    #ifdef PWM_CCP5_OC4_RC5_RP21
    {PC5, HAL_LL_TIM_INDEX_2, HAL_LL_CCP_CHANNEL_4, hal_ll_tim_module_num(CCP_MODULE_5)},
    #endif
    #ifdef PWM_CCP5_OC4_RC6_RP22
    {PC6, HAL_LL_TIM_INDEX_2, HAL_LL_CCP_CHANNEL_4, hal_ll_tim_module_num(CCP_MODULE_5)},
    #endif
    #ifdef PWM_CCP5_OC4_RC7_RP23
    {PC7, HAL_LL_TIM_INDEX_2, HAL_LL_CCP_CHANNEL_4, hal_ll_tim_module_num(CCP_MODULE_5)},
    #endif
    #ifdef PWM_CCP5_OC4_RC8_RP24
    {PC8, HAL_LL_TIM_INDEX_2, HAL_LL_CCP_CHANNEL_4, hal_ll_tim_module_num(CCP_MODULE_5)},
    #endif
    #ifdef PWM_CCP5_OC4_RC9_RP25
    {PC9, HAL_LL_TIM_INDEX_2, HAL_LL_CCP_CHANNEL_4, hal_ll_tim_module_num(CCP_MODULE_5)},
    #endif
    #ifdef PWM_CCP6_RD0
    {PD0, HAL_LL_TIM_INDEX_2, HAL_LL_CCP_CHANNEL_1, hal_ll_tim_module_num(CCP_MODULE_6)},
    #endif
    #ifdef PWM_CCP6_RD1
    {PD1, HAL_LL_TIM_INDEX_2, HAL_LL_CCP_CHANNEL_2, hal_ll_tim_module_num(CCP_MODULE_6)},
    #endif
    #ifdef PWM_CCP6_RD2
    {PD2, HAL_LL_TIM_INDEX_2, HAL_LL_CCP_CHANNEL_3, hal_ll_tim_module_num(CCP_MODULE_6)},
    #endif
    #ifdef PWM_CCP6_RD3
    {PD3, HAL_LL_TIM_INDEX_2, HAL_LL_CCP_CHANNEL_4, hal_ll_tim_module_num(CCP_MODULE_6)},
    #endif
    #ifdef PWM_CCP6_RD4
    {PD4, HAL_LL_TIM_INDEX_2, HAL_LL_CCP_CHANNEL_5, hal_ll_tim_module_num(CCP_MODULE_6)},
    #endif
    #ifdef PWM_CCP6_RD5
    {PD5, HAL_LL_TIM_INDEX_2, HAL_LL_CCP_CHANNEL_6, hal_ll_tim_module_num(CCP_MODULE_6)},
    #endif
    #ifdef PWM_CCP6_RD6
    {PD6, HAL_LL_TIM_INDEX_2, HAL_LL_CCP_CHANNEL_7, hal_ll_tim_module_num(CCP_MODULE_6)},
    #endif
    #ifdef PWM_CCP6_RD7
    {PD7, HAL_LL_TIM_INDEX_2, HAL_LL_CCP_CHANNEL_8, hal_ll_tim_module_num(CCP_MODULE_6)},
    #endif
    #ifdef PWM_CCP7_RD0
    {PD0, HAL_LL_TIM_INDEX_2, HAL_LL_CCP_CHANNEL_1, hal_ll_tim_module_num(CCP_MODULE_7)},
    #endif
    #ifdef PWM_CCP7_RD1
    {PD1, HAL_LL_TIM_INDEX_2, HAL_LL_CCP_CHANNEL_2, hal_ll_tim_module_num(CCP_MODULE_7)},
    #endif
    #ifdef PWM_CCP7_RD2
    {PD2, HAL_LL_TIM_INDEX_2, HAL_LL_CCP_CHANNEL_3, hal_ll_tim_module_num(CCP_MODULE_7)},
    #endif
    #ifdef PWM_CCP7_RD3
    {PD3, HAL_LL_TIM_INDEX_2, HAL_LL_CCP_CHANNEL_4, hal_ll_tim_module_num(CCP_MODULE_7)},
    #endif
    #ifdef PWM_CCP7_RD4
    {PD4, HAL_LL_TIM_INDEX_2, HAL_LL_CCP_CHANNEL_5, hal_ll_tim_module_num(CCP_MODULE_7)},
    #endif
    #ifdef PWM_CCP7_RD5
    {PD5, HAL_LL_TIM_INDEX_2, HAL_LL_CCP_CHANNEL_6, hal_ll_tim_module_num(CCP_MODULE_7)},
    #endif
    #ifdef PWM_CCP7_RD6
    {PD6, HAL_LL_TIM_INDEX_2, HAL_LL_CCP_CHANNEL_7, hal_ll_tim_module_num(CCP_MODULE_7)},
    #endif
    #ifdef PWM_CCP7_RD7
    {PD7, HAL_LL_TIM_INDEX_2, HAL_LL_CCP_CHANNEL_8, hal_ll_tim_module_num(CCP_MODULE_7)},
    #endif
    #ifdef PWM_CCP8_RD0
    {PD0, HAL_LL_TIM_INDEX_2, HAL_LL_CCP_CHANNEL_1, hal_ll_tim_module_num(CCP_MODULE_8)},
    #endif
    #ifdef PWM_CCP8_RD1
    {PD1, HAL_LL_TIM_INDEX_2, HAL_LL_CCP_CHANNEL_2, hal_ll_tim_module_num(CCP_MODULE_8)},
    #endif
    #ifdef PWM_CCP8_RD2
    {PD2, HAL_LL_TIM_INDEX_2, HAL_LL_CCP_CHANNEL_3, hal_ll_tim_module_num(CCP_MODULE_8)},
    #endif
    #ifdef PWM_CCP8_RD3
    {PD3, HAL_LL_TIM_INDEX_2, HAL_LL_CCP_CHANNEL_4, hal_ll_tim_module_num(CCP_MODULE_8)},
    #endif
    #ifdef PWM_CCP8_RD4
    {PD4, HAL_LL_TIM_INDEX_2, HAL_LL_CCP_CHANNEL_5, hal_ll_tim_module_num(CCP_MODULE_8)},
    #endif
    #ifdef PWM_CCP8_RD5
    {PD5, HAL_LL_TIM_INDEX_2, HAL_LL_CCP_CHANNEL_6, hal_ll_tim_module_num(CCP_MODULE_8)},
    #endif
    #ifdef PWM_CCP8_RD6
    {PD6, HAL_LL_TIM_INDEX_2, HAL_LL_CCP_CHANNEL_7, hal_ll_tim_module_num(CCP_MODULE_8)},
    #endif
    #ifdef PWM_CCP8_RD7
    {PD7, HAL_LL_TIM_INDEX_2, HAL_LL_CCP_CHANNEL_8, hal_ll_tim_module_num(CCP_MODULE_8)},
    #endif
    #ifdef PWM_CCP9_RD0
    {PD0, HAL_LL_TIM_INDEX_2, HAL_LL_CCP_CHANNEL_1, hal_ll_tim_module_num(CCP_MODULE_9)},
    #endif
    #ifdef PWM_CCP9_RD1
    {PD1, HAL_LL_TIM_INDEX_2, HAL_LL_CCP_CHANNEL_2, hal_ll_tim_module_num(CCP_MODULE_9)},
    #endif
    #ifdef PWM_CCP9_RD2
    {PD2, HAL_LL_TIM_INDEX_2, HAL_LL_CCP_CHANNEL_3, hal_ll_tim_module_num(CCP_MODULE_9)},
    #endif
    #ifdef PWM_CCP9_RD3
    {PD3, HAL_LL_TIM_INDEX_2, HAL_LL_CCP_CHANNEL_4, hal_ll_tim_module_num(CCP_MODULE_9)},
    #endif
    #ifdef PWM_CCP9_RD4
    {PD4, HAL_LL_TIM_INDEX_2, HAL_LL_CCP_CHANNEL_5, hal_ll_tim_module_num(CCP_MODULE_9)},
    #endif
    #ifdef PWM_CCP9_RD5
    {PD5, HAL_LL_TIM_INDEX_2, HAL_LL_CCP_CHANNEL_6, hal_ll_tim_module_num(CCP_MODULE_9)},
    #endif
    #ifdef PWM_CCP9_RD6
    {PD6, HAL_LL_TIM_INDEX_2, HAL_LL_CCP_CHANNEL_7, hal_ll_tim_module_num(CCP_MODULE_9)},
    #endif
    #ifdef PWM_CCP9_RD7
    {PD7, HAL_LL_TIM_INDEX_2, HAL_LL_CCP_CHANNEL_8, hal_ll_tim_module_num(CCP_MODULE_9)},
    #endif
    #ifdef PWM_CCP1_OC1_RC10_RP26
    {PC10, HAL_LL_TIM_INDEX_2, HAL_LL_CCP_CHANNEL_1, hal_ll_tim_module_num(CCP_MODULE_1)},
    #endif
    #ifdef PWM_CCP1_OC1_RC11_RP27
    {PC11, HAL_LL_TIM_INDEX_2, HAL_LL_CCP_CHANNEL_1, hal_ll_tim_module_num(CCP_MODULE_1)},
    #endif
    #ifdef PWM_CCP1_OC1_RC12_RP28
    {PC12, HAL_LL_TIM_INDEX_2, HAL_LL_CCP_CHANNEL_1, hal_ll_tim_module_num(CCP_MODULE_1)},
    #endif
    #ifdef PWM_CCP1_OC1_RC13_RP29
    {PC13, HAL_LL_TIM_INDEX_2, HAL_LL_CCP_CHANNEL_1, hal_ll_tim_module_num(CCP_MODULE_1)},
    #endif
    #ifdef PWM_CCP1_OC2_RC10_RP26
    {PC10, HAL_LL_TIM_INDEX_2, HAL_LL_CCP_CHANNEL_2, hal_ll_tim_module_num(CCP_MODULE_1)},
    #endif
    #ifdef PWM_CCP1_OC2_RC11_RP27
    {PC11, HAL_LL_TIM_INDEX_2, HAL_LL_CCP_CHANNEL_2, hal_ll_tim_module_num(CCP_MODULE_1)},
    #endif
    #ifdef PWM_CCP1_OC2_RC12_RP28
    {PC12, HAL_LL_TIM_INDEX_2, HAL_LL_CCP_CHANNEL_2, hal_ll_tim_module_num(CCP_MODULE_1)},
    #endif
    #ifdef PWM_CCP1_OC2_RC13_RP29
    {PC13, HAL_LL_TIM_INDEX_2, HAL_LL_CCP_CHANNEL_2, hal_ll_tim_module_num(CCP_MODULE_1)},
    #endif
    #ifdef PWM_CCP2_OC1_RC10_RP26
    {PC10, HAL_LL_TIM_INDEX_2, HAL_LL_CCP_CHANNEL_1, hal_ll_tim_module_num(CCP_MODULE_2)},
    #endif
    #ifdef PWM_CCP2_OC1_RC11_RP27
    {PC11, HAL_LL_TIM_INDEX_2, HAL_LL_CCP_CHANNEL_1, hal_ll_tim_module_num(CCP_MODULE_2)},
    #endif
    #ifdef PWM_CCP2_OC1_RC12_RP28
    {PC12, HAL_LL_TIM_INDEX_2, HAL_LL_CCP_CHANNEL_1, hal_ll_tim_module_num(CCP_MODULE_2)},
    #endif
    #ifdef PWM_CCP2_OC1_RC13_RP29
    {PC13, HAL_LL_TIM_INDEX_2, HAL_LL_CCP_CHANNEL_1, hal_ll_tim_module_num(CCP_MODULE_2)},
    #endif
    #ifdef PWM_CCP2_OC2_RC10_RP26
    {PC10, HAL_LL_TIM_INDEX_2, HAL_LL_CCP_CHANNEL_2, hal_ll_tim_module_num(CCP_MODULE_2)},
    #endif
    #ifdef PWM_CCP2_OC2_RC11_RP27
    {PC11, HAL_LL_TIM_INDEX_2, HAL_LL_CCP_CHANNEL_2, hal_ll_tim_module_num(CCP_MODULE_2)},
    #endif
    #ifdef PWM_CCP2_OC2_RC12_RP28
    {PC12, HAL_LL_TIM_INDEX_2, HAL_LL_CCP_CHANNEL_2, hal_ll_tim_module_num(CCP_MODULE_2)},
    #endif
    #ifdef PWM_CCP2_OC2_RC13_RP29
    {PC13, HAL_LL_TIM_INDEX_2, HAL_LL_CCP_CHANNEL_2, hal_ll_tim_module_num(CCP_MODULE_2)},
    #endif
    #ifdef PWM_CCP3_OC1_RC10_RP26
    {PC10, HAL_LL_TIM_INDEX_2, HAL_LL_CCP_CHANNEL_1, hal_ll_tim_module_num(CCP_MODULE_3)},
    #endif
    #ifdef PWM_CCP3_OC1_RC11_RP27
    {PC11, HAL_LL_TIM_INDEX_2, HAL_LL_CCP_CHANNEL_1, hal_ll_tim_module_num(CCP_MODULE_3)},
    #endif
    #ifdef PWM_CCP3_OC1_RC12_RP28
    {PC12, HAL_LL_TIM_INDEX_2, HAL_LL_CCP_CHANNEL_1, hal_ll_tim_module_num(CCP_MODULE_3)},
    #endif
    #ifdef PWM_CCP3_OC1_RC13_RP29
    {PC13, HAL_LL_TIM_INDEX_2, HAL_LL_CCP_CHANNEL_1, hal_ll_tim_module_num(CCP_MODULE_3)},
    #endif
    #ifdef PWM_CCP3_OC2_RC10_RP26
    {PC10, HAL_LL_TIM_INDEX_2, HAL_LL_CCP_CHANNEL_2, hal_ll_tim_module_num(CCP_MODULE_3)},
    #endif
    #ifdef PWM_CCP3_OC2_RC11_RP27
    {PC11, HAL_LL_TIM_INDEX_2, HAL_LL_CCP_CHANNEL_2, hal_ll_tim_module_num(CCP_MODULE_3)},
    #endif
    #ifdef PWM_CCP3_OC2_RC12_RP28
    {PC12, HAL_LL_TIM_INDEX_2, HAL_LL_CCP_CHANNEL_2, hal_ll_tim_module_num(CCP_MODULE_3)},
    #endif
    #ifdef PWM_CCP3_OC2_RC13_RP29
    {PC13, HAL_LL_TIM_INDEX_2, HAL_LL_CCP_CHANNEL_2, hal_ll_tim_module_num(CCP_MODULE_3)},
    #endif
    #ifdef PWM_CCP1_OC1_RA6
    {PA6, HAL_LL_TIM_INDEX_2, HAL_LL_CCP_CHANNEL_1, hal_ll_tim_module_num(CCP_MODULE_1)},
    #endif
    #ifdef PWM_CCP2_OC2_RB0
    {PB0, HAL_LL_TIM_INDEX_2, HAL_LL_CCP_CHANNEL_2, hal_ll_tim_module_num(CCP_MODULE_2)},
    #endif
    #ifdef PWM_CCP3_OC3_RB1
    {PB1, HAL_LL_TIM_INDEX_2, HAL_LL_CCP_CHANNEL_3, hal_ll_tim_module_num(CCP_MODULE_3)},
    #endif
    #ifdef PWM_CCP2_OC2_RB11
    {PB11, HAL_LL_TIM_INDEX_2, HAL_LL_CCP_CHANNEL_2, hal_ll_tim_module_num(CCP_MODULE_2)},
    #endif
    #ifdef PWM_CCP3_OC3_RB10
    {PB10, HAL_LL_TIM_INDEX_2, HAL_LL_CCP_CHANNEL_3, hal_ll_tim_module_num(CCP_MODULE_3)},
    #endif
    #ifdef PWM_CCP1_OC1_RB7
    {PB7, HAL_LL_TIM_INDEX_2, HAL_LL_CCP_CHANNEL_1, hal_ll_tim_module_num(CCP_MODULE_1)},
    #endif
    #ifdef PWM_CCP2_OC2_RC8
    {PC8, HAL_LL_TIM_INDEX_2, HAL_LL_CCP_CHANNEL_2, hal_ll_tim_module_num(CCP_MODULE_2)},
    #endif
    #ifdef PWM_CCP3_OC3_RA10
    {PA10, HAL_LL_TIM_INDEX_2, HAL_LL_CCP_CHANNEL_3, hal_ll_tim_module_num(CCP_MODULE_3)},
    #endif
    #ifdef PWM_CCP1_RA7
    {PA7, HAL_LL_TIM_INDEX_2, HAL_LL_CCP_CHANNEL_8, hal_ll_tim_module_num(CCP_MODULE_1)},
    #endif
    #ifdef PWM_CCP1_OC1_RB4_RP28
    {PB4, HAL_LL_TIM_INDEX_2, HAL_LL_CCP_CHANNEL_1, hal_ll_tim_module_num(CCP_MODULE_1)},
    #endif
    #ifdef PWM_CCP1_OC1_RB5_RP18
    {PB5, HAL_LL_TIM_INDEX_2, HAL_LL_CCP_CHANNEL_1, hal_ll_tim_module_num(CCP_MODULE_1)},
    #endif
    #ifdef PWM_CCP1_OC4_RB15_RP29
    {PB15, HAL_LL_TIM_INDEX_2, HAL_LL_CCP_CHANNEL_4, hal_ll_tim_module_num(CCP_MODULE_1)},
    #endif
    #ifdef PWM_CCP1_OC5_RB1_RP1
    {PB1, HAL_LL_TIM_INDEX_2, HAL_LL_CCP_CHANNEL_5, hal_ll_tim_module_num(CCP_MODULE_1)},
    #endif
    #ifdef PWM_CCP1_OC5_RB9_RP9
    {PB9, HAL_LL_TIM_INDEX_2, HAL_LL_CCP_CHANNEL_5, hal_ll_tim_module_num(CCP_MODULE_1)},
    #endif
    #ifdef PWM_CCP1_OC6_RB0_RP0
    {PB0, HAL_LL_TIM_INDEX_2, HAL_LL_CCP_CHANNEL_6, hal_ll_tim_module_num(CCP_MODULE_1)},
    #endif
    #ifdef PWM_CCP1_OC6_RB2_RP13
    {PB2, HAL_LL_TIM_INDEX_2, HAL_LL_CCP_CHANNEL_6, hal_ll_tim_module_num(CCP_MODULE_1)},
    #endif
    #ifdef PWM_CCP2_OC1_RD9_RP4
    {PD9, HAL_LL_TIM_INDEX_2, HAL_LL_CCP_CHANNEL_1, hal_ll_tim_module_num(CCP_MODULE_2)},
    #endif
    #ifdef PWM_CCP2_OC2_RD3_RP22
    {PD3, HAL_LL_TIM_INDEX_2, HAL_LL_CCP_CHANNEL_2, hal_ll_tim_module_num(CCP_MODULE_2)},
    #endif
    #ifdef PWM_CCP2_OC2_RD5_RP20
    {PD5, HAL_LL_TIM_INDEX_2, HAL_LL_CCP_CHANNEL_2, hal_ll_tim_module_num(CCP_MODULE_2)},
    #endif
    #ifdef PWM_CCP2_OC3_RD1_RP24
    {PD1, HAL_LL_TIM_INDEX_2, HAL_LL_CCP_CHANNEL_3, hal_ll_tim_module_num(CCP_MODULE_2)},
    #endif
    #ifdef PWM_CCP2_OC3_RD10_RP3
    {PD10, HAL_LL_TIM_INDEX_2, HAL_LL_CCP_CHANNEL_3, hal_ll_tim_module_num(CCP_MODULE_2)},
    #endif
    #ifdef PWM_CCP2_OC3_RD8_RP2
    {PD8, HAL_LL_TIM_INDEX_2, HAL_LL_CCP_CHANNEL_3, hal_ll_tim_module_num(CCP_MODULE_2)},
    #endif
    #ifdef PWM_CCP2_OC5_RD0_RP11
    {PD0, HAL_LL_TIM_INDEX_2, HAL_LL_CCP_CHANNEL_5, hal_ll_tim_module_num(CCP_MODULE_2)},
    #endif
    #ifdef PWM_CCP2_OC5_RD4_RP25
    {PD4, HAL_LL_TIM_INDEX_2, HAL_LL_CCP_CHANNEL_5, hal_ll_tim_module_num(CCP_MODULE_2)},
    #endif
    #ifdef PWM_CCP2_OC6_RD11_RP12
    {PD11, HAL_LL_TIM_INDEX_2, HAL_LL_CCP_CHANNEL_6, hal_ll_tim_module_num(CCP_MODULE_2)},
    #endif
    #ifdef PWM_CCP2_OC6_RD2_RP23
    {PD2, HAL_LL_TIM_INDEX_2, HAL_LL_CCP_CHANNEL_6, hal_ll_tim_module_num(CCP_MODULE_2)},
    #endif
    #ifdef PWM_CCP3_OC2_RF5_RP17
    {PF5, HAL_LL_TIM_INDEX_2, HAL_LL_CCP_CHANNEL_2, hal_ll_tim_module_num(CCP_MODULE_3)},
    #endif
    #ifdef PWM_CCP3_OC5_RF3_RP16
    {PF3, HAL_LL_TIM_INDEX_2, HAL_LL_CCP_CHANNEL_5, hal_ll_tim_module_num(CCP_MODULE_3)},
    #endif
    #ifdef PWM_CCP3_OC5_RF4_RP10
    {PF4, HAL_LL_TIM_INDEX_2, HAL_LL_CCP_CHANNEL_5, hal_ll_tim_module_num(CCP_MODULE_3)},
    #endif
    #ifdef PWM_CCP3_OC6_RF2_RP30
    {PF2, HAL_LL_TIM_INDEX_2, HAL_LL_CCP_CHANNEL_6, hal_ll_tim_module_num(CCP_MODULE_3)},
    #endif
    #ifdef PWM_CCP4_OC1_RG6_RP21
    {PG6, HAL_LL_TIM_INDEX_2, HAL_LL_CCP_CHANNEL_1, hal_ll_tim_module_num(CCP_MODULE_4)},
    #endif
    #ifdef PWM_CCP4_OC3_RG9_RP27
    {PG9, HAL_LL_TIM_INDEX_2, HAL_LL_CCP_CHANNEL_3, hal_ll_tim_module_num(CCP_MODULE_4)},
    #endif
    #ifdef PWM_CCP4_OC4_RD6
    {PD6, HAL_LL_TIM_INDEX_2, HAL_LL_CCP_CHANNEL_4, hal_ll_tim_module_num(CCP_MODULE_4)},
    #endif
    #ifdef PWM_CCP4_OC4_RG8_RP19
    {PG8, HAL_LL_TIM_INDEX_2, HAL_LL_CCP_CHANNEL_4, hal_ll_tim_module_num(CCP_MODULE_4)},
    #endif
    #ifdef PWM_CCP4_OC6_RG7_RP26
    {PG7, HAL_LL_TIM_INDEX_2, HAL_LL_CCP_CHANNEL_6, hal_ll_tim_module_num(CCP_MODULE_4)},
    #endif
    #ifdef PWM_CCP5_OC1_RB15_RP29
    {PB15, HAL_LL_TIM_INDEX_2, HAL_LL_CCP_CHANNEL_1, hal_ll_tim_module_num(CCP_MODULE_5)},
    #endif
    #ifdef PWM_CCP5_OC3_RB2_RP13
    {PB2, HAL_LL_TIM_INDEX_2, HAL_LL_CCP_CHANNEL_3, hal_ll_tim_module_num(CCP_MODULE_5)},
    #endif
    #ifdef PWM_CCP5_OC4_RB4_RP28
    {PB4, HAL_LL_TIM_INDEX_2, HAL_LL_CCP_CHANNEL_4, hal_ll_tim_module_num(CCP_MODULE_5)},
    #endif
    #ifdef PWM_CCP5_OC4_RB5_RP18
    {PB5, HAL_LL_TIM_INDEX_2, HAL_LL_CCP_CHANNEL_4, hal_ll_tim_module_num(CCP_MODULE_5)},
    #endif
    #ifdef PWM_CCP5_OC5_RB8_RP8
    {PB8, HAL_LL_TIM_INDEX_2, HAL_LL_CCP_CHANNEL_5, hal_ll_tim_module_num(CCP_MODULE_5)},
    #endif
    #ifdef PWM_CCP5_OC5_RD7
    {PD7, HAL_LL_TIM_INDEX_2, HAL_LL_CCP_CHANNEL_5, hal_ll_tim_module_num(CCP_MODULE_5)},
    #endif
    #ifdef PWM_CCP6_OC6_RF0
    {PF0, HAL_LL_TIM_INDEX_2, HAL_LL_CCP_CHANNEL_6, hal_ll_tim_module_num(CCP_MODULE_6)},
    #endif
    #ifdef PWM_CCP1_OC2_RB15_RP29
    {PB15, HAL_LL_TIM_INDEX_2, HAL_LL_CCP_CHANNEL_2, hal_ll_tim_module_num(CCP_MODULE_1)},
    #endif
    #ifdef PWM_CCP1_OC6_RB6_RP6
    {PB6, HAL_LL_TIM_INDEX_2, HAL_LL_CCP_CHANNEL_6, hal_ll_tim_module_num(CCP_MODULE_1)},
    #endif
    #ifdef PWM_CCP2_OC1_RD15_RP5
    {PD15, HAL_LL_TIM_INDEX_2, HAL_LL_CCP_CHANNEL_1, hal_ll_tim_module_num(CCP_MODULE_2)},
    #endif
    #ifdef PWM_CCP2_OC1_RD3_RP22
    {PD3, HAL_LL_TIM_INDEX_2, HAL_LL_CCP_CHANNEL_1, hal_ll_tim_module_num(CCP_MODULE_2)},
    #endif
    #ifdef PWM_CCP2_OC1_RD5_RP20
    {PD5, HAL_LL_TIM_INDEX_2, HAL_LL_CCP_CHANNEL_1, hal_ll_tim_module_num(CCP_MODULE_2)},
    #endif
    #ifdef PWM_CCP2_OC2_RD1_RP24
    {PD1, HAL_LL_TIM_INDEX_2, HAL_LL_CCP_CHANNEL_2, hal_ll_tim_module_num(CCP_MODULE_2)},
    #endif
    #ifdef PWM_CCP2_OC2_RD10_RP3
    {PD10, HAL_LL_TIM_INDEX_2, HAL_LL_CCP_CHANNEL_2, hal_ll_tim_module_num(CCP_MODULE_2)},
    #endif
    #ifdef PWM_CCP2_OC2_RD8_RP2
    {PD8, HAL_LL_TIM_INDEX_2, HAL_LL_CCP_CHANNEL_2, hal_ll_tim_module_num(CCP_MODULE_2)},
    #endif
    #ifdef PWM_CCP2_OC4_RD0_RP11
    {PD0, HAL_LL_TIM_INDEX_2, HAL_LL_CCP_CHANNEL_4, hal_ll_tim_module_num(CCP_MODULE_2)},
    #endif
    #ifdef PWM_CCP2_OC4_RD4_RP25
    {PD4, HAL_LL_TIM_INDEX_2, HAL_LL_CCP_CHANNEL_4, hal_ll_tim_module_num(CCP_MODULE_2)},
    #endif
    #ifdef PWM_CCP2_OC5_RD11_RP12
    {PD11, HAL_LL_TIM_INDEX_2, HAL_LL_CCP_CHANNEL_5, hal_ll_tim_module_num(CCP_MODULE_2)},
    #endif
    #ifdef PWM_CCP2_OC5_RD2_RP23
    {PD2, HAL_LL_TIM_INDEX_2, HAL_LL_CCP_CHANNEL_5, hal_ll_tim_module_num(CCP_MODULE_2)},
    #endif
    #ifdef PWM_CCP2_OC6_RD9_RP4
    {PD9, HAL_LL_TIM_INDEX_2, HAL_LL_CCP_CHANNEL_6, hal_ll_tim_module_num(CCP_MODULE_2)},
    #endif
    #ifdef PWM_CCP3_OC1_RF5_RP17
    {PF5, HAL_LL_TIM_INDEX_2, HAL_LL_CCP_CHANNEL_1, hal_ll_tim_module_num(CCP_MODULE_3)},
    #endif
    #ifdef PWM_CCP3_OC3_RF3_RP16
    {PF3, HAL_LL_TIM_INDEX_2, HAL_LL_CCP_CHANNEL_3, hal_ll_tim_module_num(CCP_MODULE_3)},
    #endif
    #ifdef PWM_CCP3_OC4_RF13_RP31
    {PF13, HAL_LL_TIM_INDEX_2, HAL_LL_CCP_CHANNEL_4, hal_ll_tim_module_num(CCP_MODULE_3)},
    #endif
    #ifdef PWM_CCP3_OC4_RF2_RP30
    {PF2, HAL_LL_TIM_INDEX_2, HAL_LL_CCP_CHANNEL_4, hal_ll_tim_module_num(CCP_MODULE_3)},
    #endif
    #ifdef PWM_CCP3_OC5_RF8_RP15
    {PF8, HAL_LL_TIM_INDEX_2, HAL_LL_CCP_CHANNEL_5, hal_ll_tim_module_num(CCP_MODULE_3)},
    #endif
    #ifdef PWM_CCP4_OC5_RG8_RP19
    {PG8, HAL_LL_TIM_INDEX_2, HAL_LL_CCP_CHANNEL_5, hal_ll_tim_module_num(CCP_MODULE_4)},
    #endif
    #ifdef PWM_CCP4_OC5_RG9_RP27
    {PG9, HAL_LL_TIM_INDEX_2, HAL_LL_CCP_CHANNEL_5, hal_ll_tim_module_num(CCP_MODULE_4)},
    #endif
    #ifdef PWM_CCP4_OC6_RG6_RP21
    {PG6, HAL_LL_TIM_INDEX_2, HAL_LL_CCP_CHANNEL_6, hal_ll_tim_module_num(CCP_MODULE_4)},
    #endif
    #ifdef PWM_CCP5_OC1_RB4_RP28
    {PB4, HAL_LL_TIM_INDEX_2, HAL_LL_CCP_CHANNEL_1, hal_ll_tim_module_num(CCP_MODULE_5)},
    #endif
    #ifdef PWM_CCP5_OC1_RB5_RP18
    {PB5, HAL_LL_TIM_INDEX_2, HAL_LL_CCP_CHANNEL_1, hal_ll_tim_module_num(CCP_MODULE_5)},
    #endif
    #ifdef PWM_CCP5_OC2_RB15_RP29
    {PB15, HAL_LL_TIM_INDEX_2, HAL_LL_CCP_CHANNEL_2, hal_ll_tim_module_num(CCP_MODULE_5)},
    #endif
    #ifdef PWM_CCP5_OC5_RB1_RP1
    {PB1, HAL_LL_TIM_INDEX_2, HAL_LL_CCP_CHANNEL_5, hal_ll_tim_module_num(CCP_MODULE_5)},
    #endif
    #ifdef PWM_CCP5_OC6_RB0_RP0
    {PB0, HAL_LL_TIM_INDEX_2, HAL_LL_CCP_CHANNEL_6, hal_ll_tim_module_num(CCP_MODULE_5)},
    #endif
    #ifdef PWM_CCP5_OC6_RB2_RP13
    {PB2, HAL_LL_TIM_INDEX_2, HAL_LL_CCP_CHANNEL_6, hal_ll_tim_module_num(CCP_MODULE_5)},
    #endif
    #ifdef PWM_CCP5_OC6_RB6_RP6
    {PB6, HAL_LL_TIM_INDEX_2, HAL_LL_CCP_CHANNEL_6, hal_ll_tim_module_num(CCP_MODULE_5)},
    #endif
    #ifdef PWM_CCP1_OC1_RB2_RP13
    {PB2, HAL_LL_TIM_INDEX_2, HAL_LL_CCP_CHANNEL_1, hal_ll_tim_module_num(CCP_MODULE_1)},
    #endif
    #ifdef PWM_CCP1_OC5_RB14_RP14
    {PB14, HAL_LL_TIM_INDEX_2, HAL_LL_CCP_CHANNEL_5, hal_ll_tim_module_num(CCP_MODULE_1)},
    #endif
    #ifdef PWM_CCP1_OC5_RB15_RP29
    {PB15, HAL_LL_TIM_INDEX_2, HAL_LL_CCP_CHANNEL_5, hal_ll_tim_module_num(CCP_MODULE_1)},
    #endif
    #ifdef PWM_CCP1_OC5_RB7_RP7
    {PB7, HAL_LL_TIM_INDEX_2, HAL_LL_CCP_CHANNEL_5, hal_ll_tim_module_num(CCP_MODULE_1)},
    #endif
    #ifdef PWM_CCP1_OC6_RB1_RP1
    {PB1, HAL_LL_TIM_INDEX_2, HAL_LL_CCP_CHANNEL_6, hal_ll_tim_module_num(CCP_MODULE_1)},
    #endif
    #ifdef PWM_CCP1_OC6_RB9_RP9
    {PB9, HAL_LL_TIM_INDEX_2, HAL_LL_CCP_CHANNEL_6, hal_ll_tim_module_num(CCP_MODULE_1)},
    #endif
    #ifdef PWM_CCP2_OC1_RD1_RP24
    {PD1, HAL_LL_TIM_INDEX_2, HAL_LL_CCP_CHANNEL_1, hal_ll_tim_module_num(CCP_MODULE_2)},
    #endif
    #ifdef PWM_CCP2_OC2_RD0_RP11
    {PD0, HAL_LL_TIM_INDEX_2, HAL_LL_CCP_CHANNEL_2, hal_ll_tim_module_num(CCP_MODULE_2)},
    #endif
    #ifdef PWM_CCP2_OC2_RD9_RP4
    {PD9, HAL_LL_TIM_INDEX_2, HAL_LL_CCP_CHANNEL_2, hal_ll_tim_module_num(CCP_MODULE_2)},
    #endif
    #ifdef PWM_CCP2_OC3_RD11_RP12
    {PD11, HAL_LL_TIM_INDEX_2, HAL_LL_CCP_CHANNEL_3, hal_ll_tim_module_num(CCP_MODULE_2)},
    #endif
    #ifdef PWM_CCP2_OC3_RD4_RP25
    {PD4, HAL_LL_TIM_INDEX_2, HAL_LL_CCP_CHANNEL_3, hal_ll_tim_module_num(CCP_MODULE_2)},
    #endif
    #ifdef PWM_CCP2_OC4_RD2_RP23
    {PD2, HAL_LL_TIM_INDEX_2, HAL_LL_CCP_CHANNEL_4, hal_ll_tim_module_num(CCP_MODULE_2)},
    #endif
    #ifdef PWM_CCP2_OC4_RD8_RP2
    {PD8, HAL_LL_TIM_INDEX_2, HAL_LL_CCP_CHANNEL_4, hal_ll_tim_module_num(CCP_MODULE_2)},
    #endif
    #ifdef PWM_CCP2_OC5_RD10_RP3
    {PD10, HAL_LL_TIM_INDEX_2, HAL_LL_CCP_CHANNEL_5, hal_ll_tim_module_num(CCP_MODULE_2)},
    #endif
    #ifdef PWM_CCP2_OC6_RD3_RP22
    {PD3, HAL_LL_TIM_INDEX_2, HAL_LL_CCP_CHANNEL_6, hal_ll_tim_module_num(CCP_MODULE_2)},
    #endif
    #ifdef PWM_CCP2_OC6_RD5_RP20
    {PD5, HAL_LL_TIM_INDEX_2, HAL_LL_CCP_CHANNEL_6, hal_ll_tim_module_num(CCP_MODULE_2)},
    #endif
    #ifdef PWM_CCP3_OC3_RF4_RP10
    {PF4, HAL_LL_TIM_INDEX_2, HAL_LL_CCP_CHANNEL_3, hal_ll_tim_module_num(CCP_MODULE_3)},
    #endif
    #ifdef PWM_CCP3_OC6_RF5_RP17
    {PF5, HAL_LL_TIM_INDEX_2, HAL_LL_CCP_CHANNEL_6, hal_ll_tim_module_num(CCP_MODULE_3)},
    #endif
    #ifdef PWM_CCP4_OC1_RG9_RP27
    {PG9, HAL_LL_TIM_INDEX_2, HAL_LL_CCP_CHANNEL_1, hal_ll_tim_module_num(CCP_MODULE_4)},
    #endif
    #ifdef PWM_CCP4_OC2_RG8_RP19
    {PG8, HAL_LL_TIM_INDEX_2, HAL_LL_CCP_CHANNEL_2, hal_ll_tim_module_num(CCP_MODULE_4)},
    #endif
    #ifdef PWM_CCP4_OC4_RG7_RP26
    {PG7, HAL_LL_TIM_INDEX_2, HAL_LL_CCP_CHANNEL_4, hal_ll_tim_module_num(CCP_MODULE_4)},
    #endif
    #ifdef PWM_CCP4_OC5_RG6_RP21
    {PG6, HAL_LL_TIM_INDEX_2, HAL_LL_CCP_CHANNEL_5, hal_ll_tim_module_num(CCP_MODULE_4)},
    #endif
    #ifdef PWM_CCP5_OC2_RB2_RP13
    {PB2, HAL_LL_TIM_INDEX_2, HAL_LL_CCP_CHANNEL_2, hal_ll_tim_module_num(CCP_MODULE_5)},
    #endif
    #ifdef PWM_CCP5_OC2_RB4_RP28
    {PB4, HAL_LL_TIM_INDEX_2, HAL_LL_CCP_CHANNEL_2, hal_ll_tim_module_num(CCP_MODULE_5)},
    #endif
    #ifdef PWM_CCP5_OC2_RB5_RP18
    {PB5, HAL_LL_TIM_INDEX_2, HAL_LL_CCP_CHANNEL_2, hal_ll_tim_module_num(CCP_MODULE_5)},
    #endif
    #ifdef PWM_CCP5_OC6_RB14_RP14
    {PB14, HAL_LL_TIM_INDEX_2, HAL_LL_CCP_CHANNEL_6, hal_ll_tim_module_num(CCP_MODULE_5)},
    #endif
    #ifdef PWM_CCP5_OC6_RB15_RP29
    {PB15, HAL_LL_TIM_INDEX_2, HAL_LL_CCP_CHANNEL_6, hal_ll_tim_module_num(CCP_MODULE_5)},
    #endif
    #ifdef PWM_CCP5_OC6_RB7_RP7
    {PB7, HAL_LL_TIM_INDEX_2, HAL_LL_CCP_CHANNEL_6, hal_ll_tim_module_num(CCP_MODULE_5)},
    #endif
    #ifdef PWM_CCP1_OC3_RB15_RP29
    {PB15, HAL_LL_TIM_INDEX_2, HAL_LL_CCP_CHANNEL_3, hal_ll_tim_module_num(CCP_MODULE_1)},
    #endif
    #ifdef PWM_CCP2_OC1_RD2_RP23
    {PD2, HAL_LL_TIM_INDEX_2, HAL_LL_CCP_CHANNEL_1, hal_ll_tim_module_num(CCP_MODULE_2)},
    #endif
    #ifdef PWM_CCP2_OC2_RD15_RP5
    {PD15, HAL_LL_TIM_INDEX_2, HAL_LL_CCP_CHANNEL_2, hal_ll_tim_module_num(CCP_MODULE_2)},
    #endif
    #ifdef PWM_CCP2_OC3_RD3_RP22
    {PD3, HAL_LL_TIM_INDEX_2, HAL_LL_CCP_CHANNEL_3, hal_ll_tim_module_num(CCP_MODULE_2)},
    #endif
    #ifdef PWM_CCP2_OC3_RD5_RP20
    {PD5, HAL_LL_TIM_INDEX_2, HAL_LL_CCP_CHANNEL_3, hal_ll_tim_module_num(CCP_MODULE_2)},
    #endif
    #ifdef PWM_CCP2_OC4_RD1_RP24
    {PD1, HAL_LL_TIM_INDEX_2, HAL_LL_CCP_CHANNEL_4, hal_ll_tim_module_num(CCP_MODULE_2)},
    #endif
    #ifdef PWM_CCP2_OC6_RD4_RP25
    {PD4, HAL_LL_TIM_INDEX_2, HAL_LL_CCP_CHANNEL_6, hal_ll_tim_module_num(CCP_MODULE_2)},
    #endif
    #ifdef PWM_CCP3_OC1_RF2_RP30
    {PF2, HAL_LL_TIM_INDEX_2, HAL_LL_CCP_CHANNEL_1, hal_ll_tim_module_num(CCP_MODULE_3)},
    #endif
    #ifdef PWM_CCP3_OC1_RF4_RP10
    {PF4, HAL_LL_TIM_INDEX_2, HAL_LL_CCP_CHANNEL_1, hal_ll_tim_module_num(CCP_MODULE_3)},
    #endif
    #ifdef PWM_CCP3_OC2_RF8_RP15
    {PF8, HAL_LL_TIM_INDEX_2, HAL_LL_CCP_CHANNEL_2, hal_ll_tim_module_num(CCP_MODULE_3)},
    #endif
    #ifdef PWM_CCP3_OC3_RF5_RP17
    {PF5, HAL_LL_TIM_INDEX_2, HAL_LL_CCP_CHANNEL_3, hal_ll_tim_module_num(CCP_MODULE_3)},
    #endif
    #ifdef PWM_CCP3_OC6_RF13_RP31
    {PF13, HAL_LL_TIM_INDEX_2, HAL_LL_CCP_CHANNEL_6, hal_ll_tim_module_num(CCP_MODULE_3)},
    #endif
    #ifdef PWM_CCP4_OC2_RG9_RP27
    {PG9, HAL_LL_TIM_INDEX_2, HAL_LL_CCP_CHANNEL_2, hal_ll_tim_module_num(CCP_MODULE_4)},
    #endif
    #ifdef PWM_CCP4_OC3_RG6_RP21
    {PG6, HAL_LL_TIM_INDEX_2, HAL_LL_CCP_CHANNEL_3, hal_ll_tim_module_num(CCP_MODULE_4)},
    #endif
    #ifdef PWM_CCP4_OC3_RG7_RP26
    {PG7, HAL_LL_TIM_INDEX_2, HAL_LL_CCP_CHANNEL_3, hal_ll_tim_module_num(CCP_MODULE_4)},
    #endif
    #ifdef PWM_CCP5_OC4_RB2_RP13
    {PB2, HAL_LL_TIM_INDEX_2, HAL_LL_CCP_CHANNEL_4, hal_ll_tim_module_num(CCP_MODULE_5)},
    #endif
    #ifdef PWM_CCP1_OC2_RB2_RP13
    {PB2, HAL_LL_TIM_INDEX_2, HAL_LL_CCP_CHANNEL_2, hal_ll_tim_module_num(CCP_MODULE_1)},
    #endif
    #ifdef PWM_CCP1_OC5_RB6_RP6
    {PB6, HAL_LL_TIM_INDEX_2, HAL_LL_CCP_CHANNEL_5, hal_ll_tim_module_num(CCP_MODULE_1)},
    #endif
    #ifdef PWM_CCP1_OC6_RB4_RP28
    {PB4, HAL_LL_TIM_INDEX_2, HAL_LL_CCP_CHANNEL_6, hal_ll_tim_module_num(CCP_MODULE_1)},
    #endif
    #ifdef PWM_CCP1_OC8_RB14_RP14
    {PB14, HAL_LL_TIM_INDEX_2, HAL_LL_CCP_CHANNEL_8, hal_ll_tim_module_num(CCP_MODULE_1)},
    #endif
    #ifdef PWM_CCP1_OC8_RB7_RP7
    {PB7, HAL_LL_TIM_INDEX_2, HAL_LL_CCP_CHANNEL_8, hal_ll_tim_module_num(CCP_MODULE_1)},
    #endif
    #ifdef PWM_CCP2_OC1_RD4_RP25
    {PD4, HAL_LL_TIM_INDEX_2, HAL_LL_CCP_CHANNEL_1, hal_ll_tim_module_num(CCP_MODULE_2)},
    #endif
    #ifdef PWM_CCP2_OC5_RD8_RP2
    {PD8, HAL_LL_TIM_INDEX_2, HAL_LL_CCP_CHANNEL_5, hal_ll_tim_module_num(CCP_MODULE_2)},
    #endif
    #ifdef PWM_CCP2_OC8_RD0_RP11
    {PD0, HAL_LL_TIM_INDEX_2, HAL_LL_CCP_CHANNEL_8, hal_ll_tim_module_num(CCP_MODULE_2)},
    #endif
    #ifdef PWM_CCP2_OC8_RD3_RP22
    {PD3, HAL_LL_TIM_INDEX_2, HAL_LL_CCP_CHANNEL_8, hal_ll_tim_module_num(CCP_MODULE_2)},
    #endif
    #ifdef PWM_CCP2_OC8_RD9_RP4
    {PD9, HAL_LL_TIM_INDEX_2, HAL_LL_CCP_CHANNEL_8, hal_ll_tim_module_num(CCP_MODULE_2)},
    #endif
    #ifdef PWM_CCP3_OC2_RF3_RP16
    {PF3, HAL_LL_TIM_INDEX_2, HAL_LL_CCP_CHANNEL_2, hal_ll_tim_module_num(CCP_MODULE_3)},
    #endif
    #ifdef PWM_CCP3_OC8_RF5_RP17
    {PF5, HAL_LL_TIM_INDEX_2, HAL_LL_CCP_CHANNEL_8, hal_ll_tim_module_num(CCP_MODULE_3)},
    #endif
    #ifdef PWM_CCP4_OC4_RG6_RP21
    {PG6, HAL_LL_TIM_INDEX_2, HAL_LL_CCP_CHANNEL_4, hal_ll_tim_module_num(CCP_MODULE_4)},
    #endif
    #ifdef PWM_CCP4_OC8_RG8_RP19
    {PG8, HAL_LL_TIM_INDEX_2, HAL_LL_CCP_CHANNEL_8, hal_ll_tim_module_num(CCP_MODULE_4)},
    #endif
    #ifdef PWM_CCP5_OC5_RB0_RP0
    {PB0, HAL_LL_TIM_INDEX_2, HAL_LL_CCP_CHANNEL_5, hal_ll_tim_module_num(CCP_MODULE_5)},
    #endif
    #ifdef PWM_CCP5_OC5_RB5_RP18
    {PB5, HAL_LL_TIM_INDEX_2, HAL_LL_CCP_CHANNEL_5, hal_ll_tim_module_num(CCP_MODULE_5)},
    #endif
    #ifdef PWM_CCP5_OC7_RB8_RP8
    {PB8, HAL_LL_TIM_INDEX_2, HAL_LL_CCP_CHANNEL_7, hal_ll_tim_module_num(CCP_MODULE_5)},
    #endif
    #ifdef PWM_CCP5_OC9_RB6_RP6
    {PB6, HAL_LL_TIM_INDEX_2, HAL_LL_CCP_CHANNEL_9, hal_ll_tim_module_num(CCP_MODULE_5)},
    #endif
    #ifdef PWM_CCP5_OC9_RB9_RP9
    {PB9, HAL_LL_TIM_INDEX_2, HAL_LL_CCP_CHANNEL_9, hal_ll_tim_module_num(CCP_MODULE_5)},
    #endif
    #ifdef PWM_CCP1_OC3_RB2_RP13
    {PB2, HAL_LL_TIM_INDEX_2, HAL_LL_CCP_CHANNEL_3, hal_ll_tim_module_num(CCP_MODULE_1)},
    #endif
    #ifdef PWM_CCP1_OC6_RB8_RP8
    {PB8, HAL_LL_TIM_INDEX_2, HAL_LL_CCP_CHANNEL_6, hal_ll_tim_module_num(CCP_MODULE_1)},
    #endif
    #ifdef PWM_CCP1_OC7_RB15_RP29
    {PB15, HAL_LL_TIM_INDEX_2, HAL_LL_CCP_CHANNEL_7, hal_ll_tim_module_num(CCP_MODULE_1)},
    #endif
    #ifdef PWM_CCP1_OC7_RB6_RP6
    {PB6, HAL_LL_TIM_INDEX_2, HAL_LL_CCP_CHANNEL_7, hal_ll_tim_module_num(CCP_MODULE_1)},
    #endif
    #ifdef PWM_CCP1_OC8_RB1_RP1
    {PB1, HAL_LL_TIM_INDEX_2, HAL_LL_CCP_CHANNEL_8, hal_ll_tim_module_num(CCP_MODULE_1)},
    #endif
    #ifdef PWM_CCP1_OC9_RB9_RP9
    {PB9, HAL_LL_TIM_INDEX_2, HAL_LL_CCP_CHANNEL_9, hal_ll_tim_module_num(CCP_MODULE_1)},
    #endif
    #ifdef PWM_CCP2_OC5_RD5_RP20
    {PD5, HAL_LL_TIM_INDEX_2, HAL_LL_CCP_CHANNEL_5, hal_ll_tim_module_num(CCP_MODULE_2)},
    #endif
    #ifdef PWM_CCP2_OC7_RD9_RP4
    {PD9, HAL_LL_TIM_INDEX_2, HAL_LL_CCP_CHANNEL_7, hal_ll_tim_module_num(CCP_MODULE_2)},
    #endif
    #ifdef PWM_CCP3_OC5_RF2_RP30
    {PF2, HAL_LL_TIM_INDEX_2, HAL_LL_CCP_CHANNEL_5, hal_ll_tim_module_num(CCP_MODULE_3)},
    #endif
    #ifdef PWM_CCP3_OC7_RF13_RP31
    {PF13, HAL_LL_TIM_INDEX_2, HAL_LL_CCP_CHANNEL_7, hal_ll_tim_module_num(CCP_MODULE_3)},
    #endif
    #ifdef PWM_CCP3_OC7_RF8_RP15
    {PF8, HAL_LL_TIM_INDEX_2, HAL_LL_CCP_CHANNEL_7, hal_ll_tim_module_num(CCP_MODULE_3)},
    #endif
    #ifdef PWM_CCP3_OC8_RF4_RP10
    {PF4, HAL_LL_TIM_INDEX_2, HAL_LL_CCP_CHANNEL_8, hal_ll_tim_module_num(CCP_MODULE_3)},
    #endif
    #ifdef PWM_CCP4_OC1_RG8_RP19
    {PG8, HAL_LL_TIM_INDEX_2, HAL_LL_CCP_CHANNEL_1, hal_ll_tim_module_num(CCP_MODULE_4)},
    #endif
    #ifdef PWM_CCP4_OC5_RG7_RP26
    {PG7, HAL_LL_TIM_INDEX_2, HAL_LL_CCP_CHANNEL_5, hal_ll_tim_module_num(CCP_MODULE_4)},
    #endif
    #ifdef PWM_CCP4_OC6_RG9_RP27
    {PG9, HAL_LL_TIM_INDEX_2, HAL_LL_CCP_CHANNEL_6, hal_ll_tim_module_num(CCP_MODULE_4)},
    #endif
    #ifdef PWM_CCP4_OC9_RG6_RP21
    {PG6, HAL_LL_TIM_INDEX_2, HAL_LL_CCP_CHANNEL_9, hal_ll_tim_module_num(CCP_MODULE_4)},
    #endif
    #ifdef PWM_CCP5_OC6_RB4_RP28
    {PB4, HAL_LL_TIM_INDEX_2, HAL_LL_CCP_CHANNEL_6, hal_ll_tim_module_num(CCP_MODULE_5)},
    #endif
    #ifdef PWM_CCP5_OC6_RB8_RP8
    {PB8, HAL_LL_TIM_INDEX_2, HAL_LL_CCP_CHANNEL_6, hal_ll_tim_module_num(CCP_MODULE_5)},
    #endif
    #ifdef PWM_CCP5_OC7_RB15_RP29
    {PB15, HAL_LL_TIM_INDEX_2, HAL_LL_CCP_CHANNEL_7, hal_ll_tim_module_num(CCP_MODULE_5)},
    #endif
    #ifdef PWM_CCP5_OC7_RB6_RP6
    {PB6, HAL_LL_TIM_INDEX_2, HAL_LL_CCP_CHANNEL_7, hal_ll_tim_module_num(CCP_MODULE_5)},
    #endif
    #ifdef PWM_CCP5_OC8_RB1_RP1
    {PB1, HAL_LL_TIM_INDEX_2, HAL_LL_CCP_CHANNEL_8, hal_ll_tim_module_num(CCP_MODULE_5)},
    #endif
    #ifdef PWM_CCP1_OC1_RD0
    {PD0, HAL_LL_TIM_INDEX_2, HAL_LL_CCP_CHANNEL_1, hal_ll_tim_module_num(CCP_MODULE_1)},
    #endif
    #ifdef PWM_CCP2_OC2_RD1
    {PD1, HAL_LL_TIM_INDEX_2, HAL_LL_CCP_CHANNEL_2, hal_ll_tim_module_num(CCP_MODULE_2)},
    #endif
    #ifdef PWM_CCP3_OC3_RD2
    {PD2, HAL_LL_TIM_INDEX_2, HAL_LL_CCP_CHANNEL_3, hal_ll_tim_module_num(CCP_MODULE_3)},
    #endif
    #ifdef PWM_CCP4_OC4_RD3
    {PD3, HAL_LL_TIM_INDEX_2, HAL_LL_CCP_CHANNEL_4, hal_ll_tim_module_num(CCP_MODULE_4)},
    #endif
    #ifdef PWM_CCP5_OC5_RD4
    {PD4, HAL_LL_TIM_INDEX_2, HAL_LL_CCP_CHANNEL_5, hal_ll_tim_module_num(CCP_MODULE_5)},
    #endif
    #ifdef PWM_CCP5_OCFB_RB15
    {PB15, HAL_LL_TIM_INDEX_2, HAL_LL_CCP_CHANNEL_16, hal_ll_tim_module_num(CCP_MODULE_5)},
    #endif
    #ifdef PWM_CCP1_OC5_RB4_RP28
    {PB4, HAL_LL_TIM_INDEX_2, HAL_LL_CCP_CHANNEL_5, hal_ll_tim_module_num(CCP_MODULE_1)},
    #endif
    #ifdef PWM_CCP1_OC6_RB7_RP7
    {PB7, HAL_LL_TIM_INDEX_2, HAL_LL_CCP_CHANNEL_6, hal_ll_tim_module_num(CCP_MODULE_1)},
    #endif
    #ifdef PWM_CCP1_OC7_RB0_RP0
    {PB0, HAL_LL_TIM_INDEX_2, HAL_LL_CCP_CHANNEL_7, hal_ll_tim_module_num(CCP_MODULE_1)},
    #endif
    #ifdef PWM_CCP1_OC9_RB15_RP29
    {PB15, HAL_LL_TIM_INDEX_2, HAL_LL_CCP_CHANNEL_9, hal_ll_tim_module_num(CCP_MODULE_1)},
    #endif
    #ifdef PWM_CCP1_OC9_RB2_RP13
    {PB2, HAL_LL_TIM_INDEX_2, HAL_LL_CCP_CHANNEL_9, hal_ll_tim_module_num(CCP_MODULE_1)},
    #endif
    #ifdef PWM_CCP1_OC9_RB8_RP8
    {PB8, HAL_LL_TIM_INDEX_2, HAL_LL_CCP_CHANNEL_9, hal_ll_tim_module_num(CCP_MODULE_1)},
    #endif
    #ifdef PWM_CCP2_OC5_RD3_RP22
    {PD3, HAL_LL_TIM_INDEX_2, HAL_LL_CCP_CHANNEL_5, hal_ll_tim_module_num(CCP_MODULE_2)},
    #endif
    #ifdef PWM_CCP2_OC7_RD10_RP3
    {PD10, HAL_LL_TIM_INDEX_2, HAL_LL_CCP_CHANNEL_7, hal_ll_tim_module_num(CCP_MODULE_2)},
    #endif
    #ifdef PWM_CCP2_OC7_RD4_RP25
    {PD4, HAL_LL_TIM_INDEX_2, HAL_LL_CCP_CHANNEL_7, hal_ll_tim_module_num(CCP_MODULE_2)},
    #endif
    #ifdef PWM_CCP2_OC9_RD11_RP12
    {PD11, HAL_LL_TIM_INDEX_2, HAL_LL_CCP_CHANNEL_9, hal_ll_tim_module_num(CCP_MODULE_2)},
    #endif
    #ifdef PWM_CCP2_OC9_RD5_RP20
    {PD5, HAL_LL_TIM_INDEX_2, HAL_LL_CCP_CHANNEL_9, hal_ll_tim_module_num(CCP_MODULE_2)},
    #endif
    #ifdef PWM_CCP3_OC2_RF4_RP10
    {PF4, HAL_LL_TIM_INDEX_2, HAL_LL_CCP_CHANNEL_2, hal_ll_tim_module_num(CCP_MODULE_3)},
    #endif
    #ifdef PWM_CCP3_OC5_RF5_RP17
    {PF5, HAL_LL_TIM_INDEX_2, HAL_LL_CCP_CHANNEL_5, hal_ll_tim_module_num(CCP_MODULE_3)},
    #endif
    #ifdef PWM_CCP3_OC8_RF3_RP16
    {PF3, HAL_LL_TIM_INDEX_2, HAL_LL_CCP_CHANNEL_8, hal_ll_tim_module_num(CCP_MODULE_3)},
    #endif
    #ifdef PWM_CCP3_OC9_RF2_RP30
    {PF2, HAL_LL_TIM_INDEX_2, HAL_LL_CCP_CHANNEL_9, hal_ll_tim_module_num(CCP_MODULE_3)},
    #endif
    #ifdef PWM_CCP4_OC7_RG8_RP19
    {PG8, HAL_LL_TIM_INDEX_2, HAL_LL_CCP_CHANNEL_7, hal_ll_tim_module_num(CCP_MODULE_4)},
    #endif
    #ifdef PWM_CCP5_OC3_RB15_RP29
    {PB15, HAL_LL_TIM_INDEX_2, HAL_LL_CCP_CHANNEL_3, hal_ll_tim_module_num(CCP_MODULE_5)},
    #endif
    #ifdef PWM_CCP5_OC5_RB9_RP9
    {PB9, HAL_LL_TIM_INDEX_2, HAL_LL_CCP_CHANNEL_5, hal_ll_tim_module_num(CCP_MODULE_5)},
    #endif
    #ifdef PWM_CCP5_OC6_RB1_RP1
    {PB1, HAL_LL_TIM_INDEX_2, HAL_LL_CCP_CHANNEL_6, hal_ll_tim_module_num(CCP_MODULE_5)},
    #endif
    #ifdef PWM_CCP5_OC8_RB14_RP14
    {PB14, HAL_LL_TIM_INDEX_2, HAL_LL_CCP_CHANNEL_8, hal_ll_tim_module_num(CCP_MODULE_5)},
    #endif
    #ifdef PWM_CCP5_OC8_RB4_RP28
    {PB4, HAL_LL_TIM_INDEX_2, HAL_LL_CCP_CHANNEL_8, hal_ll_tim_module_num(CCP_MODULE_5)},
    #endif
    #ifdef PWM_CCP5_OC9_RB7_RP7
    {PB7, HAL_LL_TIM_INDEX_2, HAL_LL_CCP_CHANNEL_9, hal_ll_tim_module_num(CCP_MODULE_5)},
    #endif
    #ifdef PWM_CCP1_OC8_RB9_RP9
    {PB9, HAL_LL_TIM_INDEX_2, HAL_LL_CCP_CHANNEL_8, hal_ll_tim_module_num(CCP_MODULE_1)},
    #endif
    #ifdef PWM_CCP1_OC9_RB6_RP6
    {PB6, HAL_LL_TIM_INDEX_2, HAL_LL_CCP_CHANNEL_9, hal_ll_tim_module_num(CCP_MODULE_1)},
    #endif
    #ifdef PWM_CCP2_OC1_RD8_RP2
    {PD8, HAL_LL_TIM_INDEX_2, HAL_LL_CCP_CHANNEL_1, hal_ll_tim_module_num(CCP_MODULE_2)},
    #endif
    #ifdef PWM_CCP2_OC3_RD9_RP4
    {PD9, HAL_LL_TIM_INDEX_2, HAL_LL_CCP_CHANNEL_3, hal_ll_tim_module_num(CCP_MODULE_2)},
    #endif
    #ifdef PWM_CCP2_OC4_RD10_RP3
    {PD10, HAL_LL_TIM_INDEX_2, HAL_LL_CCP_CHANNEL_4, hal_ll_tim_module_num(CCP_MODULE_2)},
    #endif
    #ifdef PWM_CCP2_OC9_RD1_RP24
    {PD1, HAL_LL_TIM_INDEX_2, HAL_LL_CCP_CHANNEL_9, hal_ll_tim_module_num(CCP_MODULE_2)},
    #endif
    #ifdef PWM_CCP2_OC9_RD15_RP5
    {PD15, HAL_LL_TIM_INDEX_2, HAL_LL_CCP_CHANNEL_9, hal_ll_tim_module_num(CCP_MODULE_2)},
    #endif
    #ifdef PWM_CCP4_OC3_RG8_RP19
    {PG8, HAL_LL_TIM_INDEX_2, HAL_LL_CCP_CHANNEL_3, hal_ll_tim_module_num(CCP_MODULE_4)},
    #endif
    #ifdef PWM_CCP4_OC9_RG7_RP26
    {PG7, HAL_LL_TIM_INDEX_2, HAL_LL_CCP_CHANNEL_9, hal_ll_tim_module_num(CCP_MODULE_4)},
    #endif
    #ifdef PWM_CCP5_OC4_RB15_RP29
    {PB15, HAL_LL_TIM_INDEX_2, HAL_LL_CCP_CHANNEL_4, hal_ll_tim_module_num(CCP_MODULE_5)},
    #endif
    #ifdef PWM_CCP5_OC7_RB9_RP9
    {PB9, HAL_LL_TIM_INDEX_2, HAL_LL_CCP_CHANNEL_7, hal_ll_tim_module_num(CCP_MODULE_5)},
    #endif
    #ifdef PWM_CCP5_OC8_RB2_RP13
    {PB2, HAL_LL_TIM_INDEX_2, HAL_LL_CCP_CHANNEL_8, hal_ll_tim_module_num(CCP_MODULE_5)},
    #endif
    #ifdef PWM_CCP5_OC8_RB6_RP6
    {PB6, HAL_LL_TIM_INDEX_2, HAL_LL_CCP_CHANNEL_8, hal_ll_tim_module_num(CCP_MODULE_5)},
    #endif
    #ifdef PWM_CCP5_OC9_RB14_RP14
    {PB14, HAL_LL_TIM_INDEX_2, HAL_LL_CCP_CHANNEL_9, hal_ll_tim_module_num(CCP_MODULE_5)},
    #endif
    #ifdef PWM_CCP5_OC9_RB5_RP18
    {PB5, HAL_LL_TIM_INDEX_2, HAL_LL_CCP_CHANNEL_9, hal_ll_tim_module_num(CCP_MODULE_5)},
    #endif
    #ifdef PWM_CCP3_OC4_RF3_RP16
    {PF3, HAL_LL_TIM_INDEX_2, HAL_LL_CCP_CHANNEL_4, hal_ll_tim_module_num(CCP_MODULE_3)},
    #endif
    #ifdef PWM_CCP3_OC6_RF8_RP15
    {PF8, HAL_LL_TIM_INDEX_2, HAL_LL_CCP_CHANNEL_6, hal_ll_tim_module_num(CCP_MODULE_3)},
    #endif
    #ifdef PWM_CCP3_OC8_RF13_RP31
    {PF13, HAL_LL_TIM_INDEX_2, HAL_LL_CCP_CHANNEL_8, hal_ll_tim_module_num(CCP_MODULE_3)},
    #endif
    #ifdef PWM_CCP3_OC9_RF4_RP10
    {PF4, HAL_LL_TIM_INDEX_2, HAL_LL_CCP_CHANNEL_9, hal_ll_tim_module_num(CCP_MODULE_3)},
    #endif
    #ifdef PWM_CCP4_OC1_RG7_RP26
    {PG7, HAL_LL_TIM_INDEX_2, HAL_LL_CCP_CHANNEL_1, hal_ll_tim_module_num(CCP_MODULE_4)},
    #endif
    #ifdef PWM_CCP4_OC7_RG6_RP21
    {PG6, HAL_LL_TIM_INDEX_2, HAL_LL_CCP_CHANNEL_7, hal_ll_tim_module_num(CCP_MODULE_4)},
    #endif
    #ifdef PWM_CCP4_OC7_RG9_RP27
    {PG9, HAL_LL_TIM_INDEX_2, HAL_LL_CCP_CHANNEL_7, hal_ll_tim_module_num(CCP_MODULE_4)},
    #endif
    #ifdef PWM_CCP5_OC5_RB15_RP29
    {PB15, HAL_LL_TIM_INDEX_2, HAL_LL_CCP_CHANNEL_5, hal_ll_tim_module_num(CCP_MODULE_5)},
    #endif
    #ifdef PWM_CCP5_OC5_RB4_RP28
    {PB4, HAL_LL_TIM_INDEX_2, HAL_LL_CCP_CHANNEL_5, hal_ll_tim_module_num(CCP_MODULE_5)},
    #endif
    #ifdef PWM_CCP5_OC8_RB9_RP9
    {PB9, HAL_LL_TIM_INDEX_2, HAL_LL_CCP_CHANNEL_8, hal_ll_tim_module_num(CCP_MODULE_5)},
    #endif
    #ifdef PWM_CCP5_OC9_RB2_RP13
    {PB2, HAL_LL_TIM_INDEX_2, HAL_LL_CCP_CHANNEL_9, hal_ll_tim_module_num(CCP_MODULE_5)},
    #endif
    #ifdef PWM_CCP1_OC5_RB12_RP12
    {PB12, HAL_LL_TIM_INDEX_2, HAL_LL_CCP_CHANNEL_5, hal_ll_tim_module_num(CCP_MODULE_1)},
    #endif
    #ifdef PWM_CCP1_OC5_RB2_RP2
    {PB2, HAL_LL_TIM_INDEX_2, HAL_LL_CCP_CHANNEL_5, hal_ll_tim_module_num(CCP_MODULE_1)},
    #endif
    #ifdef PWM_CCP1_OC5_RB5_RP5
    {PB5, HAL_LL_TIM_INDEX_2, HAL_LL_CCP_CHANNEL_5, hal_ll_tim_module_num(CCP_MODULE_1)},
    #endif
    #ifdef PWM_CCP1_OC6_RB11_RP11
    {PB11, HAL_LL_TIM_INDEX_2, HAL_LL_CCP_CHANNEL_6, hal_ll_tim_module_num(CCP_MODULE_1)},
    #endif
    #ifdef PWM_CCP1_OC6_RB3_RP3
    {PB3, HAL_LL_TIM_INDEX_2, HAL_LL_CCP_CHANNEL_6, hal_ll_tim_module_num(CCP_MODULE_1)},
    #endif
    #ifdef PWM_CCP2_OC5_RB12_RP12
    {PB12, HAL_LL_TIM_INDEX_2, HAL_LL_CCP_CHANNEL_5, hal_ll_tim_module_num(CCP_MODULE_2)},
    #endif
    #ifdef PWM_CCP2_OC5_RB2_RP2
    {PB2, HAL_LL_TIM_INDEX_2, HAL_LL_CCP_CHANNEL_5, hal_ll_tim_module_num(CCP_MODULE_2)},
    #endif
    #ifdef PWM_CCP2_OC5_RB5_RP5
    {PB5, HAL_LL_TIM_INDEX_2, HAL_LL_CCP_CHANNEL_5, hal_ll_tim_module_num(CCP_MODULE_2)},
    #endif
    #ifdef PWM_CCP2_OC5_RB7_RP7
    {PB7, HAL_LL_TIM_INDEX_2, HAL_LL_CCP_CHANNEL_5, hal_ll_tim_module_num(CCP_MODULE_2)},
    #endif
    #ifdef PWM_CCP2_OC6_RB1_RP1
    {PB1, HAL_LL_TIM_INDEX_2, HAL_LL_CCP_CHANNEL_6, hal_ll_tim_module_num(CCP_MODULE_2)},
    #endif
    #ifdef PWM_CCP2_OC6_RB11_RP11
    {PB11, HAL_LL_TIM_INDEX_2, HAL_LL_CCP_CHANNEL_6, hal_ll_tim_module_num(CCP_MODULE_2)},
    #endif
    #ifdef PWM_CCP2_OC6_RB3_RP3
    {PB3, HAL_LL_TIM_INDEX_2, HAL_LL_CCP_CHANNEL_6, hal_ll_tim_module_num(CCP_MODULE_2)},
    #endif
    #ifdef PWM_CCP2_OC6_RB9_RP9
    {PB9, HAL_LL_TIM_INDEX_2, HAL_LL_CCP_CHANNEL_6, hal_ll_tim_module_num(CCP_MODULE_2)},
    #endif
    #ifdef PWM_CCP3_OC5_RB12_RP12
    {PB12, HAL_LL_TIM_INDEX_2, HAL_LL_CCP_CHANNEL_5, hal_ll_tim_module_num(CCP_MODULE_3)},
    #endif
    #ifdef PWM_CCP3_OC5_RB2_RP2
    {PB2, HAL_LL_TIM_INDEX_2, HAL_LL_CCP_CHANNEL_5, hal_ll_tim_module_num(CCP_MODULE_3)},
    #endif
    #ifdef PWM_CCP3_OC5_RB5_RP5
    {PB5, HAL_LL_TIM_INDEX_2, HAL_LL_CCP_CHANNEL_5, hal_ll_tim_module_num(CCP_MODULE_3)},
    #endif
    #ifdef PWM_CCP3_OC5_RB7_RP7
    {PB7, HAL_LL_TIM_INDEX_2, HAL_LL_CCP_CHANNEL_5, hal_ll_tim_module_num(CCP_MODULE_3)},
    #endif
    #ifdef PWM_CCP3_OC6_RB1_RP1
    {PB1, HAL_LL_TIM_INDEX_2, HAL_LL_CCP_CHANNEL_6, hal_ll_tim_module_num(CCP_MODULE_3)},
    #endif
    #ifdef PWM_CCP3_OC6_RB11_RP11
    {PB11, HAL_LL_TIM_INDEX_2, HAL_LL_CCP_CHANNEL_6, hal_ll_tim_module_num(CCP_MODULE_3)},
    #endif
    #ifdef PWM_CCP3_OC6_RB3_RP3
    {PB3, HAL_LL_TIM_INDEX_2, HAL_LL_CCP_CHANNEL_6, hal_ll_tim_module_num(CCP_MODULE_3)},
    #endif
    #ifdef PWM_CCP3_OC6_RB9_RP9
    {PB9, HAL_LL_TIM_INDEX_2, HAL_LL_CCP_CHANNEL_6, hal_ll_tim_module_num(CCP_MODULE_3)},
    #endif
    #ifdef PWM_CCP4_OC5_RB12_RP12
    {PB12, HAL_LL_TIM_INDEX_2, HAL_LL_CCP_CHANNEL_5, hal_ll_tim_module_num(CCP_MODULE_4)},
    #endif
    #ifdef PWM_CCP4_OC5_RB2_RP2
    {PB2, HAL_LL_TIM_INDEX_2, HAL_LL_CCP_CHANNEL_5, hal_ll_tim_module_num(CCP_MODULE_4)},
    #endif
    #ifdef PWM_CCP4_OC5_RB5_RP5
    {PB5, HAL_LL_TIM_INDEX_2, HAL_LL_CCP_CHANNEL_5, hal_ll_tim_module_num(CCP_MODULE_4)},
    #endif
    #ifdef PWM_CCP4_OC5_RB7_RP7
    {PB7, HAL_LL_TIM_INDEX_2, HAL_LL_CCP_CHANNEL_5, hal_ll_tim_module_num(CCP_MODULE_4)},
    #endif
    #ifdef PWM_CCP4_OC6_RB1_RP1
    {PB1, HAL_LL_TIM_INDEX_2, HAL_LL_CCP_CHANNEL_6, hal_ll_tim_module_num(CCP_MODULE_4)},
    #endif
    #ifdef PWM_CCP4_OC6_RB11_RP11
    {PB11, HAL_LL_TIM_INDEX_2, HAL_LL_CCP_CHANNEL_6, hal_ll_tim_module_num(CCP_MODULE_4)},
    #endif
    #ifdef PWM_CCP4_OC6_RB3_RP3
    {PB3, HAL_LL_TIM_INDEX_2, HAL_LL_CCP_CHANNEL_6, hal_ll_tim_module_num(CCP_MODULE_4)},
    #endif
    #ifdef PWM_CCP4_OC6_RB9_RP9
    {PB9, HAL_LL_TIM_INDEX_2, HAL_LL_CCP_CHANNEL_6, hal_ll_tim_module_num(CCP_MODULE_4)},
    #endif
    #ifdef PWM_CCP5_OC5_RB12_RP12
    {PB12, HAL_LL_TIM_INDEX_2, HAL_LL_CCP_CHANNEL_5, hal_ll_tim_module_num(CCP_MODULE_5)},
    #endif
    #ifdef PWM_CCP5_OC5_RB2_RP2
    {PB2, HAL_LL_TIM_INDEX_2, HAL_LL_CCP_CHANNEL_5, hal_ll_tim_module_num(CCP_MODULE_5)},
    #endif
    #ifdef PWM_CCP5_OC5_RB5_RP5
    {PB5, HAL_LL_TIM_INDEX_2, HAL_LL_CCP_CHANNEL_5, hal_ll_tim_module_num(CCP_MODULE_5)},
    #endif
    #ifdef PWM_CCP5_OC5_RB7_RP7
    {PB7, HAL_LL_TIM_INDEX_2, HAL_LL_CCP_CHANNEL_5, hal_ll_tim_module_num(CCP_MODULE_5)},
    #endif
    #ifdef PWM_CCP5_OC6_RB11_RP11
    {PB11, HAL_LL_TIM_INDEX_2, HAL_LL_CCP_CHANNEL_6, hal_ll_tim_module_num(CCP_MODULE_5)},
    #endif
    #ifdef PWM_CCP5_OC6_RB3_RP3
    {PB3, HAL_LL_TIM_INDEX_2, HAL_LL_CCP_CHANNEL_6, hal_ll_tim_module_num(CCP_MODULE_5)},
    #endif
    #ifdef PWM_CCP5_OC6_RB9_RP9
    {PB9, HAL_LL_TIM_INDEX_2, HAL_LL_CCP_CHANNEL_6, hal_ll_tim_module_num(CCP_MODULE_5)},
    #endif
    #ifdef PWM_CCP1_OC6_RB12_RP12
    {PB12, HAL_LL_TIM_INDEX_2, HAL_LL_CCP_CHANNEL_6, hal_ll_tim_module_num(CCP_MODULE_1)},
    #endif
    #ifdef PWM_CCP2_OC5_RC0_RP16
    {PC0, HAL_LL_TIM_INDEX_2, HAL_LL_CCP_CHANNEL_5, hal_ll_tim_module_num(CCP_MODULE_2)},
    #endif
    #ifdef PWM_CCP2_OC5_RC2_RP18
    {PC2, HAL_LL_TIM_INDEX_2, HAL_LL_CCP_CHANNEL_5, hal_ll_tim_module_num(CCP_MODULE_2)},
    #endif
    #ifdef PWM_CCP2_OC6_RC5_RP21
    {PC5, HAL_LL_TIM_INDEX_2, HAL_LL_CCP_CHANNEL_6, hal_ll_tim_module_num(CCP_MODULE_2)},
    #endif
    #ifdef PWM_CCP2_OC6_RC6_RP22
    {PC6, HAL_LL_TIM_INDEX_2, HAL_LL_CCP_CHANNEL_6, hal_ll_tim_module_num(CCP_MODULE_2)},
    #endif
    #ifdef PWM_CCP2_OC6_RC8_RP24
    {PC8, HAL_LL_TIM_INDEX_2, HAL_LL_CCP_CHANNEL_6, hal_ll_tim_module_num(CCP_MODULE_2)},
    #endif
    #ifdef PWM_CCP3_OC5_RB0_RP0
    {PB0, HAL_LL_TIM_INDEX_2, HAL_LL_CCP_CHANNEL_5, hal_ll_tim_module_num(CCP_MODULE_3)},
    #endif
    #ifdef PWM_CCP3_OC5_RB13_RP13
    {PB13, HAL_LL_TIM_INDEX_2, HAL_LL_CCP_CHANNEL_5, hal_ll_tim_module_num(CCP_MODULE_3)},
    #endif
    #ifdef PWM_CCP3_OC6_RB14_RP14
    {PB14, HAL_LL_TIM_INDEX_2, HAL_LL_CCP_CHANNEL_6, hal_ll_tim_module_num(CCP_MODULE_3)},
    #endif
    #ifdef PWM_CCP4_OC5_RC4_RP20
    {PC4, HAL_LL_TIM_INDEX_2, HAL_LL_CCP_CHANNEL_5, hal_ll_tim_module_num(CCP_MODULE_4)},
    #endif
    #ifdef PWM_CCP4_OC6_RC0_RP16
    {PC0, HAL_LL_TIM_INDEX_2, HAL_LL_CCP_CHANNEL_6, hal_ll_tim_module_num(CCP_MODULE_4)},
    #endif
    #ifdef PWM_CCP4_OC6_RC2_RP18
    {PC2, HAL_LL_TIM_INDEX_2, HAL_LL_CCP_CHANNEL_6, hal_ll_tim_module_num(CCP_MODULE_4)},
    #endif
    #ifdef PWM_CCP5_OC5_RB10_RP10
    {PB10, HAL_LL_TIM_INDEX_2, HAL_LL_CCP_CHANNEL_5, hal_ll_tim_module_num(CCP_MODULE_5)},
    #endif
    #ifdef PWM_CCP5_OC5_RB3_RP3
    {PB3, HAL_LL_TIM_INDEX_2, HAL_LL_CCP_CHANNEL_5, hal_ll_tim_module_num(CCP_MODULE_5)},
    #endif
    #ifdef PWM_CCP5_OC6_RB13_RP13
    {PB13, HAL_LL_TIM_INDEX_2, HAL_LL_CCP_CHANNEL_6, hal_ll_tim_module_num(CCP_MODULE_5)},
    #endif
    #ifdef PWM_CCP1_OC4_RB2_RP13
    {PB2, HAL_LL_TIM_INDEX_2, HAL_LL_CCP_CHANNEL_4, hal_ll_tim_module_num(CCP_MODULE_1)},
    #endif
    #ifdef PWM_CCP1_OC5_RB8_RP8
    {PB8, HAL_LL_TIM_INDEX_2, HAL_LL_CCP_CHANNEL_5, hal_ll_tim_module_num(CCP_MODULE_1)},
    #endif
    #ifdef PWM_CCP1_OC6_RB15_RP29
    {PB15, HAL_LL_TIM_INDEX_2, HAL_LL_CCP_CHANNEL_6, hal_ll_tim_module_num(CCP_MODULE_1)},
    #endif
    #ifdef PWM_CCP1_OC7_RB14_RP14
    {PB14, HAL_LL_TIM_INDEX_2, HAL_LL_CCP_CHANNEL_7, hal_ll_tim_module_num(CCP_MODULE_1)},
    #endif
    #ifdef PWM_CCP2_OC3_RD0_RP11
    {PD0, HAL_LL_TIM_INDEX_2, HAL_LL_CCP_CHANNEL_3, hal_ll_tim_module_num(CCP_MODULE_2)},
    #endif
    #ifdef PWM_CCP2_OC5_RD1_RP24
    {PD1, HAL_LL_TIM_INDEX_2, HAL_LL_CCP_CHANNEL_5, hal_ll_tim_module_num(CCP_MODULE_2)},
    #endif
    #ifdef PWM_CCP2_OC7_RD11_RP12
    {PD11, HAL_LL_TIM_INDEX_2, HAL_LL_CCP_CHANNEL_7, hal_ll_tim_module_num(CCP_MODULE_2)},
    #endif
    #ifdef PWM_CCP2_OC7_RD2_RP23
    {PD2, HAL_LL_TIM_INDEX_2, HAL_LL_CCP_CHANNEL_7, hal_ll_tim_module_num(CCP_MODULE_2)},
    #endif
    #ifdef PWM_CCP3_OC6_RF3_RP16
    {PF3, HAL_LL_TIM_INDEX_2, HAL_LL_CCP_CHANNEL_6, hal_ll_tim_module_num(CCP_MODULE_3)},
    #endif
    #ifdef PWM_CCP4_OC4_RG9_RP27
    {PG9, HAL_LL_TIM_INDEX_2, HAL_LL_CCP_CHANNEL_4, hal_ll_tim_module_num(CCP_MODULE_4)},
    #endif
    #ifdef PWM_CCP4_OC6_RG8_RP19
    {PG8, HAL_LL_TIM_INDEX_2, HAL_LL_CCP_CHANNEL_6, hal_ll_tim_module_num(CCP_MODULE_4)},
    #endif
    #ifdef PWM_CCP5_OC5_RB2_RP13
    {PB2, HAL_LL_TIM_INDEX_2, HAL_LL_CCP_CHANNEL_5, hal_ll_tim_module_num(CCP_MODULE_5)},
    #endif
    #ifdef PWM_CCP5_OC7_RB4_RP28
    {PB4, HAL_LL_TIM_INDEX_2, HAL_LL_CCP_CHANNEL_7, hal_ll_tim_module_num(CCP_MODULE_5)},
    #endif
    #ifdef PWM_CCP1_OC1_RB15_RP29
    {PB15, HAL_LL_TIM_INDEX_2, HAL_LL_CCP_CHANNEL_1, hal_ll_tim_module_num(CCP_MODULE_1)},
    #endif
    #ifdef PWM_CCP1_OC5_RB0_RP0
    {PB0, HAL_LL_TIM_INDEX_2, HAL_LL_CCP_CHANNEL_5, hal_ll_tim_module_num(CCP_MODULE_1)},
    #endif
    #ifdef PWM_CCP1_OC7_RB8_RP8
    {PB8, HAL_LL_TIM_INDEX_2, HAL_LL_CCP_CHANNEL_7, hal_ll_tim_module_num(CCP_MODULE_1)},
    #endif
    #ifdef PWM_CCP2_OC1_RD10_RP3
    {PD10, HAL_LL_TIM_INDEX_2, HAL_LL_CCP_CHANNEL_1, hal_ll_tim_module_num(CCP_MODULE_2)},
    #endif
    #ifdef PWM_CCP2_OC4_RD11_RP12
    {PD11, HAL_LL_TIM_INDEX_2, HAL_LL_CCP_CHANNEL_4, hal_ll_tim_module_num(CCP_MODULE_2)},
    #endif
    #ifdef PWM_CCP2_OC5_RD9_RP4
    {PD9, HAL_LL_TIM_INDEX_2, HAL_LL_CCP_CHANNEL_5, hal_ll_tim_module_num(CCP_MODULE_2)},
    #endif
    #ifdef PWM_CCP2_OC7_RD0_RP11
    {PD0, HAL_LL_TIM_INDEX_2, HAL_LL_CCP_CHANNEL_7, hal_ll_tim_module_num(CCP_MODULE_2)},
    #endif
    #ifdef PWM_CCP2_OC7_RD15_RP5
    {PD15, HAL_LL_TIM_INDEX_2, HAL_LL_CCP_CHANNEL_7, hal_ll_tim_module_num(CCP_MODULE_2)},
    #endif
    #ifdef PWM_CCP2_OC7_RD3_RP22
    {PD3, HAL_LL_TIM_INDEX_2, HAL_LL_CCP_CHANNEL_7, hal_ll_tim_module_num(CCP_MODULE_2)},
    #endif
    #ifdef PWM_CCP4_OC2_RG6_RP21
    {PG6, HAL_LL_TIM_INDEX_2, HAL_LL_CCP_CHANNEL_2, hal_ll_tim_module_num(CCP_MODULE_4)},
    #endif
    #ifdef PWM_CCP4_OC7_RG7_RP26
    {PG7, HAL_LL_TIM_INDEX_2, HAL_LL_CCP_CHANNEL_7, hal_ll_tim_module_num(CCP_MODULE_4)},
    #endif
    #ifdef PWM_CCP3_OC2_RF13_RP31
    {PF13, HAL_LL_TIM_INDEX_2, HAL_LL_CCP_CHANNEL_2, hal_ll_tim_module_num(CCP_MODULE_3)},
    #endif
    #ifdef PWM_CCP3_OC4_RF4_RP10
    {PF4, HAL_LL_TIM_INDEX_2, HAL_LL_CCP_CHANNEL_4, hal_ll_tim_module_num(CCP_MODULE_3)},
    #endif
    #ifdef PWM_CCP3_OC7_RF5_RP17
    {PF5, HAL_LL_TIM_INDEX_2, HAL_LL_CCP_CHANNEL_7, hal_ll_tim_module_num(CCP_MODULE_3)},
    #endif
    #ifdef PWM_CCP1_OC2_RB4_RP28
    {PB4, HAL_LL_TIM_INDEX_2, HAL_LL_CCP_CHANNEL_2, hal_ll_tim_module_num(CCP_MODULE_1)},
    #endif
    #ifdef PWM_CCP1_OC6_RB14_RP14
    {PB14, HAL_LL_TIM_INDEX_2, HAL_LL_CCP_CHANNEL_6, hal_ll_tim_module_num(CCP_MODULE_1)},
    #endif
    #ifdef PWM_CCP2_OC1_RD0_RP11
    {PD0, HAL_LL_TIM_INDEX_2, HAL_LL_CCP_CHANNEL_1, hal_ll_tim_module_num(CCP_MODULE_2)},
    #endif
    #ifdef PWM_CCP2_OC1_RD11_RP12
    {PD11, HAL_LL_TIM_INDEX_2, HAL_LL_CCP_CHANNEL_1, hal_ll_tim_module_num(CCP_MODULE_2)},
    #endif
    #ifdef PWM_CCP2_OC4_RD5_RP20
    {PD5, HAL_LL_TIM_INDEX_2, HAL_LL_CCP_CHANNEL_4, hal_ll_tim_module_num(CCP_MODULE_2)},
    #endif
    #ifdef PWM_CCP4_OC2_RG7_RP26
    {PG7, HAL_LL_TIM_INDEX_2, HAL_LL_CCP_CHANNEL_2, hal_ll_tim_module_num(CCP_MODULE_4)},
    #endif
    #ifdef PWM_CCP3_OC1_RF8_RP15
    {PF8, HAL_LL_TIM_INDEX_2, HAL_LL_CCP_CHANNEL_1, hal_ll_tim_module_num(CCP_MODULE_3)},
    #endif
    #ifdef PWM_CCP5_OC3_RB5_RP18
    {PB5, HAL_LL_TIM_INDEX_2, HAL_LL_CCP_CHANNEL_3, hal_ll_tim_module_num(CCP_MODULE_5)},
    #endif
    #ifdef PWM_CCP2_OC3_RD2_RP23
    {PD2, HAL_LL_TIM_INDEX_2, HAL_LL_CCP_CHANNEL_3, hal_ll_tim_module_num(CCP_MODULE_2)},
    #endif
    #ifdef PWM_CCP2_OC6_RD10_RP3
    {PD10, HAL_LL_TIM_INDEX_2, HAL_LL_CCP_CHANNEL_6, hal_ll_tim_module_num(CCP_MODULE_2)},
    #endif
    #ifdef PWM_CCP2_OC6_RD15_RP5
    {PD15, HAL_LL_TIM_INDEX_2, HAL_LL_CCP_CHANNEL_6, hal_ll_tim_module_num(CCP_MODULE_2)},
    #endif
    #ifdef PWM_CCP5_OC3_RB4_RP28
    {PB4, HAL_LL_TIM_INDEX_2, HAL_LL_CCP_CHANNEL_3, hal_ll_tim_module_num(CCP_MODULE_5)},
    #endif
    #ifdef PWM_CCP1_OC1_RA0_RP26
    {PA0, HAL_LL_TIM_INDEX_2, HAL_LL_CCP_CHANNEL_1, hal_ll_tim_module_num(CCP_MODULE_1)},
    #endif
    #ifdef PWM_CCP1_OC3_RA1_RP27
    {PA1, HAL_LL_TIM_INDEX_2, HAL_LL_CCP_CHANNEL_3, hal_ll_tim_module_num(CCP_MODULE_1)},
    #endif
    #ifdef PWM_CCP3_OC1_RA0_RP26
    {PA0, HAL_LL_TIM_INDEX_2, HAL_LL_CCP_CHANNEL_1, hal_ll_tim_module_num(CCP_MODULE_3)},
    #endif
    #ifdef PWM_CCP3_OC3_RA1_RP27
    {PA1, HAL_LL_TIM_INDEX_2, HAL_LL_CCP_CHANNEL_3, hal_ll_tim_module_num(CCP_MODULE_3)},
    #endif
    #ifdef PWM_CCP1_OC1_RA10_RP28
    {PA10, HAL_LL_TIM_INDEX_2, HAL_LL_CCP_CHANNEL_1, hal_ll_tim_module_num(CCP_MODULE_1)},
    #endif
    #ifdef PWM_CCP1_OC2_RA1_RP27
    {PA1, HAL_LL_TIM_INDEX_2, HAL_LL_CCP_CHANNEL_2, hal_ll_tim_module_num(CCP_MODULE_1)},
    #endif
    #ifdef PWM_CCP1_OC3_RA0_RP26
    {PA0, HAL_LL_TIM_INDEX_2, HAL_LL_CCP_CHANNEL_3, hal_ll_tim_module_num(CCP_MODULE_1)},
    #endif
    #ifdef PWM_CCP1_OC9_RB14_RP14
    {PB14, HAL_LL_TIM_INDEX_2, HAL_LL_CCP_CHANNEL_9, hal_ll_tim_module_num(CCP_MODULE_1)},
    #endif
    #ifdef PWM_CCP1_OC9_RB7_RP7
    {PB7, HAL_LL_TIM_INDEX_2, HAL_LL_CCP_CHANNEL_9, hal_ll_tim_module_num(CCP_MODULE_1)},
    #endif
    #ifdef PWM_CCP2_OC8_RD11_RP12
    {PD11, HAL_LL_TIM_INDEX_2, HAL_LL_CCP_CHANNEL_8, hal_ll_tim_module_num(CCP_MODULE_2)},
    #endif
    #ifdef PWM_CCP2_OC8_RD8_RP2
    {PD8, HAL_LL_TIM_INDEX_2, HAL_LL_CCP_CHANNEL_8, hal_ll_tim_module_num(CCP_MODULE_2)},
    #endif
    #ifdef PWM_CCP5_OC7_RB0_RP0
    {PB0, HAL_LL_TIM_INDEX_2, HAL_LL_CCP_CHANNEL_7, hal_ll_tim_module_num(CCP_MODULE_5)},
    #endif
    #ifdef PWM_CCP5_OC7_RB5_RP18
    {PB5, HAL_LL_TIM_INDEX_2, HAL_LL_CCP_CHANNEL_7, hal_ll_tim_module_num(CCP_MODULE_5)},
    #endif
    #ifdef PWM_CCP1_OC9_RB0_RP0
    {PB0, HAL_LL_TIM_INDEX_2, HAL_LL_CCP_CHANNEL_9, hal_ll_tim_module_num(CCP_MODULE_1)},
    #endif
    #ifdef PWM_CCP2_OC4_RD15_RP5
    {PD15, HAL_LL_TIM_INDEX_2, HAL_LL_CCP_CHANNEL_4, hal_ll_tim_module_num(CCP_MODULE_2)},
    #endif
    #ifdef PWM_CCP3_OC4_RF5_RP17
    {PF5, HAL_LL_TIM_INDEX_2, HAL_LL_CCP_CHANNEL_4, hal_ll_tim_module_num(CCP_MODULE_3)},
    #endif
    #ifdef PWM_CCP3_OC8_RF2_RP30
    {PF2, HAL_LL_TIM_INDEX_2, HAL_LL_CCP_CHANNEL_8, hal_ll_tim_module_num(CCP_MODULE_3)},
    #endif
    #ifdef PWM_CCP3_OC9_RF8_RP15
    {PF8, HAL_LL_TIM_INDEX_2, HAL_LL_CCP_CHANNEL_9, hal_ll_tim_module_num(CCP_MODULE_3)},
    #endif
    #ifdef PWM_CCP5_OC9_RB1_RP1
    {PB1, HAL_LL_TIM_INDEX_2, HAL_LL_CCP_CHANNEL_9, hal_ll_tim_module_num(CCP_MODULE_5)},
    #endif
    #ifdef PWM_CCP5_OC9_RB4_RP28
    {PB4, HAL_LL_TIM_INDEX_2, HAL_LL_CCP_CHANNEL_9, hal_ll_tim_module_num(CCP_MODULE_5)},
    #endif
    #ifdef PWM_CCP2_OC7_RD5_RP20
    {PD5, HAL_LL_TIM_INDEX_2, HAL_LL_CCP_CHANNEL_7, hal_ll_tim_module_num(CCP_MODULE_2)},
    #endif
    #ifdef PWM_CCP2_OC8_RD1_RP24
    {PD1, HAL_LL_TIM_INDEX_2, HAL_LL_CCP_CHANNEL_8, hal_ll_tim_module_num(CCP_MODULE_2)},
    #endif
    #ifdef PWM_CCP3_OC7_RF2_RP30
    {PF2, HAL_LL_TIM_INDEX_2, HAL_LL_CCP_CHANNEL_7, hal_ll_tim_module_num(CCP_MODULE_3)},
    #endif
    #ifdef PWM_CCP3_OC8_RF8_RP15
    {PF8, HAL_LL_TIM_INDEX_2, HAL_LL_CCP_CHANNEL_8, hal_ll_tim_module_num(CCP_MODULE_3)},
    #endif
    #ifdef PWM_CCP3_OC9_RF13_RP31
    {PF13, HAL_LL_TIM_INDEX_2, HAL_LL_CCP_CHANNEL_9, hal_ll_tim_module_num(CCP_MODULE_3)},
    #endif
    #ifdef PWM_CCP4_OC9_RG9_RP27
    {PG9, HAL_LL_TIM_INDEX_2, HAL_LL_CCP_CHANNEL_9, hal_ll_tim_module_num(CCP_MODULE_4)},
    #endif
    #ifdef PWM_CCP5_OC5_RB6_RP6
    {PB6, HAL_LL_TIM_INDEX_2, HAL_LL_CCP_CHANNEL_5, hal_ll_tim_module_num(CCP_MODULE_5)},
    #endif
    #ifdef PWM_CCP5_OC7_RB14_RP14
    {PB14, HAL_LL_TIM_INDEX_2, HAL_LL_CCP_CHANNEL_7, hal_ll_tim_module_num(CCP_MODULE_5)},
    #endif
    #ifdef PWM_CCP5_OC8_RB7_RP7
    {PB7, HAL_LL_TIM_INDEX_2, HAL_LL_CCP_CHANNEL_8, hal_ll_tim_module_num(CCP_MODULE_5)},
    #endif
    #ifdef PWM_CCP1_OC1_RA0_RP5
    {PA0, HAL_LL_TIM_INDEX_2, HAL_LL_CCP_CHANNEL_1, hal_ll_tim_module_num(CCP_MODULE_1)},
    #endif
    #ifdef PWM_CCP1_OC3_RA1_RP6
    {PA1, HAL_LL_TIM_INDEX_2, HAL_LL_CCP_CHANNEL_3, hal_ll_tim_module_num(CCP_MODULE_1)},
    #endif
    #ifdef PWM_CCP2_OC5_RB10_RP10
    {PB10, HAL_LL_TIM_INDEX_2, HAL_LL_CCP_CHANNEL_5, hal_ll_tim_module_num(CCP_MODULE_2)},
    #endif
    #ifdef PWM_CCP2_OC6_RB7_RP7
    {PB7, HAL_LL_TIM_INDEX_2, HAL_LL_CCP_CHANNEL_6, hal_ll_tim_module_num(CCP_MODULE_2)},
    #endif
    #ifdef PWM_CCP3_OC1_RA0_RP5
    {PA0, HAL_LL_TIM_INDEX_2, HAL_LL_CCP_CHANNEL_1, hal_ll_tim_module_num(CCP_MODULE_3)},
    #endif
    #ifdef PWM_CCP3_OC3_RA1_RP6
    {PA1, HAL_LL_TIM_INDEX_2, HAL_LL_CCP_CHANNEL_3, hal_ll_tim_module_num(CCP_MODULE_3)},
    #endif
    #ifdef PWM_CCP4_OC5_RB10_RP10
    {PB10, HAL_LL_TIM_INDEX_2, HAL_LL_CCP_CHANNEL_5, hal_ll_tim_module_num(CCP_MODULE_4)},
    #endif
    #ifdef PWM_CCP4_OC6_RB7_RP7
    {PB7, HAL_LL_TIM_INDEX_2, HAL_LL_CCP_CHANNEL_6, hal_ll_tim_module_num(CCP_MODULE_4)},
    #endif
    #ifdef PWM_CCP5_OC1_RA0_RP5
    {PA0, HAL_LL_TIM_INDEX_2, HAL_LL_CCP_CHANNEL_1, hal_ll_tim_module_num(CCP_MODULE_5)},
    #endif
    #ifdef PWM_CCP5_OC3_RA1_RP6
    {PA1, HAL_LL_TIM_INDEX_2, HAL_LL_CCP_CHANNEL_3, hal_ll_tim_module_num(CCP_MODULE_5)},
    #endif
    #ifdef PWM_CCP1_OC4_RA1_RP6
    {PA1, HAL_LL_TIM_INDEX_2, HAL_LL_CCP_CHANNEL_4, hal_ll_tim_module_num(CCP_MODULE_1)},
    #endif
    #ifdef PWM_CCP2_OC6_RB0_RP0
    {PB0, HAL_LL_TIM_INDEX_2, HAL_LL_CCP_CHANNEL_6, hal_ll_tim_module_num(CCP_MODULE_2)},
    #endif
    #ifdef PWM_CCP3_OC5_RC0_RP16
    {PC0, HAL_LL_TIM_INDEX_2, HAL_LL_CCP_CHANNEL_5, hal_ll_tim_module_num(CCP_MODULE_3)},
    #endif
    #ifdef PWM_CCP3_OC5_RC2_RP18
    {PC2, HAL_LL_TIM_INDEX_2, HAL_LL_CCP_CHANNEL_5, hal_ll_tim_module_num(CCP_MODULE_3)},
    #endif
    #ifdef PWM_CCP3_OC6_RC5_RP21
    {PC5, HAL_LL_TIM_INDEX_2, HAL_LL_CCP_CHANNEL_6, hal_ll_tim_module_num(CCP_MODULE_3)},
    #endif
    #ifdef PWM_CCP3_OC6_RC6_RP22
    {PC6, HAL_LL_TIM_INDEX_2, HAL_LL_CCP_CHANNEL_6, hal_ll_tim_module_num(CCP_MODULE_3)},
    #endif
    #ifdef PWM_CCP3_OC6_RC8_RP24
    {PC8, HAL_LL_TIM_INDEX_2, HAL_LL_CCP_CHANNEL_6, hal_ll_tim_module_num(CCP_MODULE_3)},
    #endif
    #ifdef PWM_CCP4_OC2_RA0_RP5
    {PA0, HAL_LL_TIM_INDEX_2, HAL_LL_CCP_CHANNEL_2, hal_ll_tim_module_num(CCP_MODULE_4)},
    #endif
    #ifdef PWM_CCP4_OC5_RA1_RP6
    {PA1, HAL_LL_TIM_INDEX_2, HAL_LL_CCP_CHANNEL_5, hal_ll_tim_module_num(CCP_MODULE_4)},
    #endif
    #ifdef PWM_CCP5_OC6_RB10_RP10
    {PB10, HAL_LL_TIM_INDEX_2, HAL_LL_CCP_CHANNEL_6, hal_ll_tim_module_num(CCP_MODULE_5)},
    #endif
    #ifdef PWM_CCP2_OC7_RD8_RP2
    {PD8, HAL_LL_TIM_INDEX_2, HAL_LL_CCP_CHANNEL_7, hal_ll_tim_module_num(CCP_MODULE_2)},
    #endif
    #ifdef PWM_CCP3_OC7_RF3_RP16
    {PF3, HAL_LL_TIM_INDEX_2, HAL_LL_CCP_CHANNEL_7, hal_ll_tim_module_num(CCP_MODULE_3)},
    #endif
    #ifdef PWM_CCP5_OC1_RB2_RP13
    {PB2, HAL_LL_TIM_INDEX_2, HAL_LL_CCP_CHANNEL_1, hal_ll_tim_module_num(CCP_MODULE_5)},
    #endif
    #ifdef PWM_CCP5_OC7_RB7_RP7
    {PB7, HAL_LL_TIM_INDEX_2, HAL_LL_CCP_CHANNEL_7, hal_ll_tim_module_num(CCP_MODULE_5)},
    #endif
    #ifdef PWM_CCP5_OC9_RB0_RP0
    {PB0, HAL_LL_TIM_INDEX_2, HAL_LL_CCP_CHANNEL_9, hal_ll_tim_module_num(CCP_MODULE_5)},
    #endif
    #ifdef PWM_CCP2_OC2_RD2_RP23
    {PD2, HAL_LL_TIM_INDEX_2, HAL_LL_CCP_CHANNEL_2, hal_ll_tim_module_num(CCP_MODULE_2)},
    #endif
    #ifdef PWM_CCP3_OC1_RF3_RP16
    {PF3, HAL_LL_TIM_INDEX_2, HAL_LL_CCP_CHANNEL_1, hal_ll_tim_module_num(CCP_MODULE_3)},
    #endif
    #ifdef PWM_CCP5_OC6_RB5_RP18
    {PB5, HAL_LL_TIM_INDEX_2, HAL_LL_CCP_CHANNEL_6, hal_ll_tim_module_num(CCP_MODULE_5)},
    #endif
    #ifdef PWM_CCP2_OC2_RD11_RP12
    {PD11, HAL_LL_TIM_INDEX_2, HAL_LL_CCP_CHANNEL_2, hal_ll_tim_module_num(CCP_MODULE_2)},
    #endif
    #ifdef PWM_CCP2_OC3_RD15_RP5
    {PD15, HAL_LL_TIM_INDEX_2, HAL_LL_CCP_CHANNEL_3, hal_ll_tim_module_num(CCP_MODULE_2)},
    #endif
    #ifdef PWM_CCP3_OC2_RF2_RP30
    {PF2, HAL_LL_TIM_INDEX_2, HAL_LL_CCP_CHANNEL_2, hal_ll_tim_module_num(CCP_MODULE_3)},
    #endif
    #ifdef PWM_CCP3_OC3_RF13_RP31
    {PF13, HAL_LL_TIM_INDEX_2, HAL_LL_CCP_CHANNEL_3, hal_ll_tim_module_num(CCP_MODULE_3)},
    #endif
    #ifdef PWM_CCP3_OC4_RF8_RP15
    {PF8, HAL_LL_TIM_INDEX_2, HAL_LL_CCP_CHANNEL_4, hal_ll_tim_module_num(CCP_MODULE_3)},
    #endif
    #ifdef PWM_CCP2_OC4_RD9_RP4
    {PD9, HAL_LL_TIM_INDEX_2, HAL_LL_CCP_CHANNEL_4, hal_ll_tim_module_num(CCP_MODULE_2)},
    #endif
    #ifdef PWM_CCP2_OC6_RD0_RP11
    {PD0, HAL_LL_TIM_INDEX_2, HAL_LL_CCP_CHANNEL_6, hal_ll_tim_module_num(CCP_MODULE_2)},
    #endif
    #ifdef PWM_CCP2_OC6_RD1_RP24
    {PD1, HAL_LL_TIM_INDEX_2, HAL_LL_CCP_CHANNEL_6, hal_ll_tim_module_num(CCP_MODULE_2)},
    #endif
    #ifdef PWM_CCP3_OC1_RF13_RP31
    {PF13, HAL_LL_TIM_INDEX_2, HAL_LL_CCP_CHANNEL_1, hal_ll_tim_module_num(CCP_MODULE_3)},
    #endif
    #ifdef PWM_CCP1_OC5_RB2_RP13
    {PB2, HAL_LL_TIM_INDEX_2, HAL_LL_CCP_CHANNEL_5, hal_ll_tim_module_num(CCP_MODULE_1)},
    #endif
    #ifdef PWM_CCP1_OC7_RB4_RP28
    {PB4, HAL_LL_TIM_INDEX_2, HAL_LL_CCP_CHANNEL_7, hal_ll_tim_module_num(CCP_MODULE_1)},
    #endif
    #ifdef PWM_CCP4_OC8_RG7_RP26
    {PG7, HAL_LL_TIM_INDEX_2, HAL_LL_CCP_CHANNEL_8, hal_ll_tim_module_num(CCP_MODULE_4)},
    #endif
    #ifdef PWM_CCP5_OC5_RB14_RP14
    {PB14, HAL_LL_TIM_INDEX_2, HAL_LL_CCP_CHANNEL_5, hal_ll_tim_module_num(CCP_MODULE_5)},
    #endif
    #ifdef PWM_CCP3_OC3_RF2_RP30
    {PF2, HAL_LL_TIM_INDEX_2, HAL_LL_CCP_CHANNEL_3, hal_ll_tim_module_num(CCP_MODULE_3)},
    #endif
    #ifdef PWM_CCP3_OC9_RF5_RP17
    {PF5, HAL_LL_TIM_INDEX_2, HAL_LL_CCP_CHANNEL_9, hal_ll_tim_module_num(CCP_MODULE_3)},
    #endif
    #ifdef PWM_CCP1_OC5_RB13_RP13
    {PB13, HAL_LL_TIM_INDEX_2, HAL_LL_CCP_CHANNEL_5, hal_ll_tim_module_num(CCP_MODULE_1)},
    #endif
    #ifdef PWM_CCP2_OC5_RB1_RP1
    {PB1, HAL_LL_TIM_INDEX_2, HAL_LL_CCP_CHANNEL_5, hal_ll_tim_module_num(CCP_MODULE_2)},
    #endif
    #ifdef PWM_CCP2_OC5_RB13_RP13
    {PB13, HAL_LL_TIM_INDEX_2, HAL_LL_CCP_CHANNEL_5, hal_ll_tim_module_num(CCP_MODULE_2)},
    #endif
    #ifdef PWM_CCP2_OC5_RB9_RP9
    {PB9, HAL_LL_TIM_INDEX_2, HAL_LL_CCP_CHANNEL_5, hal_ll_tim_module_num(CCP_MODULE_2)},
    #endif
    #ifdef PWM_CCP3_OC5_RB1_RP1
    {PB1, HAL_LL_TIM_INDEX_2, HAL_LL_CCP_CHANNEL_5, hal_ll_tim_module_num(CCP_MODULE_3)},
    #endif
    #ifdef PWM_CCP3_OC5_RB9_RP9
    {PB9, HAL_LL_TIM_INDEX_2, HAL_LL_CCP_CHANNEL_5, hal_ll_tim_module_num(CCP_MODULE_3)},
    #endif
    #ifdef PWM_CCP4_OC5_RB1_RP1
    {PB1, HAL_LL_TIM_INDEX_2, HAL_LL_CCP_CHANNEL_5, hal_ll_tim_module_num(CCP_MODULE_4)},
    #endif
    #ifdef PWM_CCP4_OC5_RB13_RP13
    {PB13, HAL_LL_TIM_INDEX_2, HAL_LL_CCP_CHANNEL_5, hal_ll_tim_module_num(CCP_MODULE_4)},
    #endif
    #ifdef PWM_CCP4_OC5_RB9_RP9
    {PB9, HAL_LL_TIM_INDEX_2, HAL_LL_CCP_CHANNEL_5, hal_ll_tim_module_num(CCP_MODULE_4)},
    #endif
    #ifdef PWM_CCP5_OC5_RB13_RP13
    {PB13, HAL_LL_TIM_INDEX_2, HAL_LL_CCP_CHANNEL_5, hal_ll_tim_module_num(CCP_MODULE_5)},
    #endif
    #ifdef PWM_CCP1_OC5_RB4_RP4
    {PB4, HAL_LL_TIM_INDEX_2, HAL_LL_CCP_CHANNEL_5, hal_ll_tim_module_num(CCP_MODULE_1)},
    #endif
    #ifdef PWM_CCP2_OC5_RC5_RP21
    {PC5, HAL_LL_TIM_INDEX_2, HAL_LL_CCP_CHANNEL_5, hal_ll_tim_module_num(CCP_MODULE_2)},
    #endif
    #ifdef PWM_CCP2_OC5_RC8_RP24
    {PC8, HAL_LL_TIM_INDEX_2, HAL_LL_CCP_CHANNEL_5, hal_ll_tim_module_num(CCP_MODULE_2)},
    #endif
    #ifdef PWM_CCP3_OC5_RB10_RP10
    {PB10, HAL_LL_TIM_INDEX_2, HAL_LL_CCP_CHANNEL_5, hal_ll_tim_module_num(CCP_MODULE_3)},
    #endif
    #ifdef PWM_CCP4_OC5_RC0_RP16
    {PC0, HAL_LL_TIM_INDEX_2, HAL_LL_CCP_CHANNEL_5, hal_ll_tim_module_num(CCP_MODULE_4)},
    #endif
    #ifdef PWM_CCP3_OC3_RF8_RP15
    {PF8, HAL_LL_TIM_INDEX_2, HAL_LL_CCP_CHANNEL_3, hal_ll_tim_module_num(CCP_MODULE_3)},
    #endif
    #ifdef PWM_CCP1_OC5_RB10_RP10
    {PB10, HAL_LL_TIM_INDEX_2, HAL_LL_CCP_CHANNEL_5, hal_ll_tim_module_num(CCP_MODULE_1)},
    #endif
    #ifdef PWM_CCP2_OC5_RB6_RP6
    {PB6, HAL_LL_TIM_INDEX_2, HAL_LL_CCP_CHANNEL_5, hal_ll_tim_module_num(CCP_MODULE_2)},
    #endif
    #ifdef PWM_CCP3_OC5_RB6_RP6
    {PB6, HAL_LL_TIM_INDEX_2, HAL_LL_CCP_CHANNEL_5, hal_ll_tim_module_num(CCP_MODULE_3)},
    #endif
    #ifdef PWM_CCP4_OC5_RB6_RP6
    {PB6, HAL_LL_TIM_INDEX_2, HAL_LL_CCP_CHANNEL_5, hal_ll_tim_module_num(CCP_MODULE_4)},
    #endif
    #ifdef PWM_CCP1_OC5_RB15_RP15
    {PB15, HAL_LL_TIM_INDEX_2, HAL_LL_CCP_CHANNEL_5, hal_ll_tim_module_num(CCP_MODULE_1)},
    #endif
    #ifdef PWM_CCP1_OC5_RB3_RP3
    {PB3, HAL_LL_TIM_INDEX_2, HAL_LL_CCP_CHANNEL_5, hal_ll_tim_module_num(CCP_MODULE_1)},
    #endif
    #ifdef PWM_CCP4_OC5_RC1_RP17
    {PC1, HAL_LL_TIM_INDEX_2, HAL_LL_CCP_CHANNEL_5, hal_ll_tim_module_num(CCP_MODULE_4)},
    #endif
    #ifdef PWM_CCP4_OC5_RC3_RP19
    {PC3, HAL_LL_TIM_INDEX_2, HAL_LL_CCP_CHANNEL_5, hal_ll_tim_module_num(CCP_MODULE_4)},
    #endif
    #ifdef PWM_CCP4_OC5_RC6_RP22
    {PC6, HAL_LL_TIM_INDEX_2, HAL_LL_CCP_CHANNEL_5, hal_ll_tim_module_num(CCP_MODULE_4)},
    #endif
    #ifdef PWM_CCP5_OC5_RB11_RP11
    {PB11, HAL_LL_TIM_INDEX_2, HAL_LL_CCP_CHANNEL_5, hal_ll_tim_module_num(CCP_MODULE_5)},
    #endif
    #ifdef PWM_CCP1_OC1_RA1_RP6
    {PA1, HAL_LL_TIM_INDEX_2, HAL_LL_CCP_CHANNEL_1, hal_ll_tim_module_num(CCP_MODULE_1)},
    #endif
    #ifdef PWM_CCP3_OC4_RA0_RP5
    {PA0, HAL_LL_TIM_INDEX_2, HAL_LL_CCP_CHANNEL_4, hal_ll_tim_module_num(CCP_MODULE_3)},
    #endif
    #ifdef PWM_CCP3_OC4_RA1_RP6
    {PA1, HAL_LL_TIM_INDEX_2, HAL_LL_CCP_CHANNEL_4, hal_ll_tim_module_num(CCP_MODULE_3)},
    #endif
    #ifdef PWM_CCP5_OC2_RA0_RP5
    {PA0, HAL_LL_TIM_INDEX_2, HAL_LL_CCP_CHANNEL_2, hal_ll_tim_module_num(CCP_MODULE_5)},
    #endif
    #ifdef PWM_CCP5_OC2_RA1_RP6
    {PA1, HAL_LL_TIM_INDEX_2, HAL_LL_CCP_CHANNEL_2, hal_ll_tim_module_num(CCP_MODULE_5)},
    #endif
    #ifdef PWM_CCP2_OC5_RB0_RP0
    {PB0, HAL_LL_TIM_INDEX_2, HAL_LL_CCP_CHANNEL_5, hal_ll_tim_module_num(CCP_MODULE_2)},
    #endif
    #ifdef PWM_CCP2_OC5_RB15_RP15
    {PB15, HAL_LL_TIM_INDEX_2, HAL_LL_CCP_CHANNEL_5, hal_ll_tim_module_num(CCP_MODULE_2)},
    #endif
    #ifdef PWM_CCP2_OC5_RB4_RP4
    {PB4, HAL_LL_TIM_INDEX_2, HAL_LL_CCP_CHANNEL_5, hal_ll_tim_module_num(CCP_MODULE_2)},
    #endif
    #ifdef PWM_CCP3_OC5_RC1_RP17
    {PC1, HAL_LL_TIM_INDEX_2, HAL_LL_CCP_CHANNEL_5, hal_ll_tim_module_num(CCP_MODULE_3)},
    #endif
    #ifdef PWM_CCP3_OC5_RC3_RP19
    {PC3, HAL_LL_TIM_INDEX_2, HAL_LL_CCP_CHANNEL_5, hal_ll_tim_module_num(CCP_MODULE_3)},
    #endif
    #ifdef PWM_CCP3_OC5_RC5_RP21
    {PC5, HAL_LL_TIM_INDEX_2, HAL_LL_CCP_CHANNEL_5, hal_ll_tim_module_num(CCP_MODULE_3)},
    #endif
    #ifdef PWM_CCP3_OC5_RC6_RP22
    {PC6, HAL_LL_TIM_INDEX_2, HAL_LL_CCP_CHANNEL_5, hal_ll_tim_module_num(CCP_MODULE_3)},
    #endif
    #ifdef PWM_CCP4_OC2_RA1_RP6
    {PA1, HAL_LL_TIM_INDEX_2, HAL_LL_CCP_CHANNEL_2, hal_ll_tim_module_num(CCP_MODULE_4)},
    #endif
    #ifdef PWM_CCP2_OC5_RB8_RP8
    {PB8, HAL_LL_TIM_INDEX_2, HAL_LL_CCP_CHANNEL_5, hal_ll_tim_module_num(CCP_MODULE_2)},
    #endif
    #ifdef PWM_CCP2_OC6_RB10_RP10
    {PB10, HAL_LL_TIM_INDEX_2, HAL_LL_CCP_CHANNEL_6, hal_ll_tim_module_num(CCP_MODULE_2)},
    #endif
    #ifdef PWM_CCP3_OC2_RA0_RP5
    {PA0, HAL_LL_TIM_INDEX_2, HAL_LL_CCP_CHANNEL_2, hal_ll_tim_module_num(CCP_MODULE_3)},
    #endif
    #ifdef PWM_CCP4_OC5_RB11_RP11
    {PB11, HAL_LL_TIM_INDEX_2, HAL_LL_CCP_CHANNEL_5, hal_ll_tim_module_num(CCP_MODULE_4)},
    #endif
    #ifdef PWM_CCP4_OC6_RB8_RP8
    {PB8, HAL_LL_TIM_INDEX_2, HAL_LL_CCP_CHANNEL_6, hal_ll_tim_module_num(CCP_MODULE_4)},
    #endif
    #ifdef PWM_CCP5_OC3_RA0_RP5
    {PA0, HAL_LL_TIM_INDEX_2, HAL_LL_CCP_CHANNEL_3, hal_ll_tim_module_num(CCP_MODULE_5)},
    #endif
    #ifdef PWM_CCP5_OC5_RA1_RP6
    {PA1, HAL_LL_TIM_INDEX_2, HAL_LL_CCP_CHANNEL_5, hal_ll_tim_module_num(CCP_MODULE_5)},
    #endif
    { HAL_LL_PIN_NC, HAL_LL_TIM_INDEX_NOT_SET, HAL_LL_CCP_CHANNEL_NOT_SET, HAL_LL_MODULE_ERROR }
    //------------ END CCP
};

#ifdef __cplusplus
}
#endif

#endif // _HAL_LL_TIM_PIN_MAP_H_
// ------------------------------------------------------------------------- END
