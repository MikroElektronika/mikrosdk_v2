/****************************************************************************
**
** Copyright (C) 2022 MikroElektronika d.o.o.
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

/*!< @brief Macro defining `weak` attribute */
#define __weak __attribute__((weak))

/*!< @brief TIM Master pin map structure. */
typedef struct
{
    hal_ll_pin_name_t pin;
    uint8_t timer;
    uint8_t module_index;
} hal_ll_tim_pin_map_t;

/*!< @brief TIM Modules. */
typedef enum
{
    HAL_LL_TIM_INDEX_2 = 0,
    HAL_LL_TIM_INDEX_4,
    HAL_LL_TIM_INDEX_6,
    HAL_LL_TIM_INDEX_8,
}hal_ll_tim_index_t;

/*!< @brief CCP/TIM pins */
__weak static const hal_ll_tim_pin_map_t _tim_map[] =
{
    //------------ BEGIN CCP
    #ifdef CCP_MODULE
    #endif

    #ifdef CCP_MODULE_1
    #ifdef PWM_CCP1_RC2
    { PC2, HAL_LL_TIM_INDEX_2, hal_ll_tim_module_num(CCP_MODULE_1) },
    #endif
    #ifdef PWM_CCP1_RA0
    { PA0, HAL_LL_TIM_INDEX_2, hal_ll_tim_module_num(CCP_MODULE_1) },
    #endif
    #ifdef PWM_CCP1_RA1
    { PA1, HAL_LL_TIM_INDEX_2, hal_ll_tim_module_num(CCP_MODULE_1) },
    #endif
    #ifdef PWM_CCP1_RA5
    { PA5, HAL_LL_TIM_INDEX_2, hal_ll_tim_module_num(CCP_MODULE_1) },
    #endif
    #ifdef PWM_CCP1_RB0
    { PB0, HAL_LL_TIM_INDEX_2, hal_ll_tim_module_num(CCP_MODULE_1) },
    #endif
    #ifdef PWM_CCP1_RB1
    { PB1, HAL_LL_TIM_INDEX_2, hal_ll_tim_module_num(CCP_MODULE_1) },
    #endif
    #ifdef PWM_CCP1_RB2
    { PB2, HAL_LL_TIM_INDEX_2, hal_ll_tim_module_num(CCP_MODULE_1) },
    #endif
    #ifdef PWM_CCP1_RB3
    { PB3, HAL_LL_TIM_INDEX_2, hal_ll_tim_module_num(CCP_MODULE_1) },
    #endif
    #ifdef PWM_CCP1_RB4
    { PB4, HAL_LL_TIM_INDEX_2, hal_ll_tim_module_num(CCP_MODULE_1) },
    #endif
    #ifdef PWM_CCP1_RB5
    { PB5, HAL_LL_TIM_INDEX_2, hal_ll_tim_module_num(CCP_MODULE_1) },
    #endif
    #ifdef PWM_CCP1_RB6
    { PB6, HAL_LL_TIM_INDEX_2, hal_ll_tim_module_num(CCP_MODULE_1) },
    #endif
    #ifdef PWM_CCP1_RB7
    { PB7, HAL_LL_TIM_INDEX_2, hal_ll_tim_module_num(CCP_MODULE_1) },
    #endif
    #ifdef PWM_CCP1_RC0
    { PC0, HAL_LL_TIM_INDEX_2, hal_ll_tim_module_num(CCP_MODULE_1) },
    #endif
    #ifdef PWM_CCP1_RC1
    { PC1, HAL_LL_TIM_INDEX_2, hal_ll_tim_module_num(CCP_MODULE_1) },
    #endif
    #ifdef PWM_CCP1_RC3
    { PC3, HAL_LL_TIM_INDEX_2, hal_ll_tim_module_num(CCP_MODULE_1) },
    #endif
    #ifdef PWM_CCP1_RC4
    { PC4, HAL_LL_TIM_INDEX_2, hal_ll_tim_module_num(CCP_MODULE_1) },
    #endif
    #ifdef PWM_CCP1_RC5
    { PC5, HAL_LL_TIM_INDEX_2, hal_ll_tim_module_num(CCP_MODULE_1) },
    #endif
    #ifdef PWM_CCP1_RC6
    { PC6, HAL_LL_TIM_INDEX_2, hal_ll_tim_module_num(CCP_MODULE_1) },
    #endif
    #ifdef PWM_CCP1_RC7
    { PC7, HAL_LL_TIM_INDEX_2, hal_ll_tim_module_num(CCP_MODULE_1) },
    #endif
    #ifdef PWM_CCP1_RD2
    { PD2, HAL_LL_TIM_INDEX_2, hal_ll_tim_module_num(CCP_MODULE_1) },
    #endif
    #ifdef PWM_CCP1_RD3
    { PD3, HAL_LL_TIM_INDEX_2, hal_ll_tim_module_num(CCP_MODULE_1) },
    #endif
    #ifdef PWM_CCP1_RD4
    { PD4, HAL_LL_TIM_INDEX_2, hal_ll_tim_module_num(CCP_MODULE_1) },
    #endif
    #ifdef PWM_CCP1_RD5
    { PD5, HAL_LL_TIM_INDEX_2, hal_ll_tim_module_num(CCP_MODULE_1) },
    #endif
    #ifdef PWM_CCP1_RD6
    { PD6, HAL_LL_TIM_INDEX_2, hal_ll_tim_module_num(CCP_MODULE_1) },
    #endif
    #ifdef PWM_CCP1_RD7
    { PD7, HAL_LL_TIM_INDEX_2, hal_ll_tim_module_num(CCP_MODULE_1) },
    #endif
    #ifdef PWM_CCP1_RF0
    { PF0, HAL_LL_TIM_INDEX_2, hal_ll_tim_module_num(CCP_MODULE_1) },
    #endif
    #ifdef PWM_CCP1_RF1
    { PF1, HAL_LL_TIM_INDEX_2, hal_ll_tim_module_num(CCP_MODULE_1) },
    #endif
    #ifdef PWM_CCP1_RF2
    { PF2, HAL_LL_TIM_INDEX_2, hal_ll_tim_module_num(CCP_MODULE_1) },
    #endif
    #ifdef PWM_CCP1_RF3
    { PF3, HAL_LL_TIM_INDEX_2, hal_ll_tim_module_num(CCP_MODULE_1) },
    #endif
    #ifdef PWM_CCP1_RF4
    { PF4, HAL_LL_TIM_INDEX_2, hal_ll_tim_module_num(CCP_MODULE_1) },
    #endif
    #ifdef PWM_CCP1_RF5
    { PF5, HAL_LL_TIM_INDEX_2, hal_ll_tim_module_num(CCP_MODULE_1) },
    #endif
    #ifdef PWM_CCP1_RF6
    { PF6, HAL_LL_TIM_INDEX_2, hal_ll_tim_module_num(CCP_MODULE_1) },
    #endif
    #ifdef PWM_CCP1_RF7
    { PF7, HAL_LL_TIM_INDEX_2, hal_ll_tim_module_num(CCP_MODULE_1) },
    #endif
    #ifdef PWM_CCP1_RA3
    { PA3, HAL_LL_TIM_INDEX_2, hal_ll_tim_module_num(CCP_MODULE_1) },
    #endif
    #ifdef PWM_CCP1_RE7
    { PE7, HAL_LL_TIM_INDEX_2, hal_ll_tim_module_num(CCP_MODULE_1) },
    #endif
    #ifdef PWM_CCP1_RG1
    { PG1, HAL_LL_TIM_INDEX_2, hal_ll_tim_module_num(CCP_MODULE_1) },
    #endif
    #ifdef PWM_CCP1_RG3
    { PG3, HAL_LL_TIM_INDEX_2, hal_ll_tim_module_num(CCP_MODULE_1) },
    #endif
    #ifdef PWM_CCP1_RE0
    { PE0, HAL_LL_TIM_INDEX_2, hal_ll_tim_module_num(CCP_MODULE_1) },
    #endif
    #ifdef PWM_CCP1_RE1
    { PE1, HAL_LL_TIM_INDEX_2, hal_ll_tim_module_num(CCP_MODULE_1) },
    #endif
    #ifdef PWM_CCP1_RE2
    { PE2, HAL_LL_TIM_INDEX_2, hal_ll_tim_module_num(CCP_MODULE_1) },
    #endif
    #ifdef PWM_CCP1_RE3
    { PE3, HAL_LL_TIM_INDEX_2, hal_ll_tim_module_num(CCP_MODULE_1) },
    #endif
    #ifdef PWM_CCP1_RE4
    { PE4, HAL_LL_TIM_INDEX_2, hal_ll_tim_module_num(CCP_MODULE_1) },
    #endif
    #ifdef PWM_CCP1_RE5
    { PE5, HAL_LL_TIM_INDEX_2, hal_ll_tim_module_num(CCP_MODULE_1) },
    #endif
    #ifdef PWM_CCP1_RE6
    { PE6, HAL_LL_TIM_INDEX_2, hal_ll_tim_module_num(CCP_MODULE_1) },
    #endif
    #endif

    #ifdef CCP_MODULE_2
    #ifdef PWM_CCP2_RB3
    { PB3, HAL_LL_TIM_INDEX_2, hal_ll_tim_module_num(CCP_MODULE_2) },
    #endif
    #ifdef PWM_CCP2_RC1
    { PC1, HAL_LL_TIM_INDEX_2, hal_ll_tim_module_num(CCP_MODULE_2) },
    #endif
    #ifdef PWM_CCP2_RA0
    { PA0, HAL_LL_TIM_INDEX_2, hal_ll_tim_module_num(CCP_MODULE_2) },
    #endif
    #ifdef PWM_CCP2_RA1
    { PA1, HAL_LL_TIM_INDEX_2, hal_ll_tim_module_num(CCP_MODULE_2) },
    #endif
    #ifdef PWM_CCP2_RA5
    { PA5, HAL_LL_TIM_INDEX_2, hal_ll_tim_module_num(CCP_MODULE_2) },
    #endif
    #ifdef PWM_CCP2_RB0
    { PB0, HAL_LL_TIM_INDEX_2, hal_ll_tim_module_num(CCP_MODULE_2) },
    #endif
    #ifdef PWM_CCP2_RB1
    { PB1, HAL_LL_TIM_INDEX_2, hal_ll_tim_module_num(CCP_MODULE_2) },
    #endif
    #ifdef PWM_CCP2_RB2
    { PB2, HAL_LL_TIM_INDEX_2, hal_ll_tim_module_num(CCP_MODULE_2) },
    #endif
    #ifdef PWM_CCP2_RB4
    { PB4, HAL_LL_TIM_INDEX_2, hal_ll_tim_module_num(CCP_MODULE_2) },
    #endif
    #ifdef PWM_CCP2_RB5
    { PB5, HAL_LL_TIM_INDEX_2, hal_ll_tim_module_num(CCP_MODULE_2) },
    #endif
    #ifdef PWM_CCP2_RB6
    { PB6, HAL_LL_TIM_INDEX_2, hal_ll_tim_module_num(CCP_MODULE_2) },
    #endif
    #ifdef PWM_CCP2_RB7
    { PB7, HAL_LL_TIM_INDEX_2, hal_ll_tim_module_num(CCP_MODULE_2) },
    #endif
    #ifdef PWM_CCP2_RC0
    { PC0, HAL_LL_TIM_INDEX_2, hal_ll_tim_module_num(CCP_MODULE_2) },
    #endif
    #ifdef PWM_CCP2_RC2
    { PC2, HAL_LL_TIM_INDEX_2, hal_ll_tim_module_num(CCP_MODULE_2) },
    #endif
    #ifdef PWM_CCP2_RC3
    { PC3, HAL_LL_TIM_INDEX_2, hal_ll_tim_module_num(CCP_MODULE_2) },
    #endif
    #ifdef PWM_CCP2_RC4
    { PC4, HAL_LL_TIM_INDEX_2, hal_ll_tim_module_num(CCP_MODULE_2) },
    #endif
    #ifdef PWM_CCP2_RC5
    { PC5, HAL_LL_TIM_INDEX_2, hal_ll_tim_module_num(CCP_MODULE_2) },
    #endif
    #ifdef PWM_CCP2_RC6
    { PC6, HAL_LL_TIM_INDEX_2, hal_ll_tim_module_num(CCP_MODULE_2) },
    #endif
    #ifdef PWM_CCP2_RC7
    { PC7, HAL_LL_TIM_INDEX_2, hal_ll_tim_module_num(CCP_MODULE_2) },
    #endif
    #ifdef PWM_CCP2_RD2
    { PD2, HAL_LL_TIM_INDEX_2, hal_ll_tim_module_num(CCP_MODULE_2) },
    #endif
    #ifdef PWM_CCP2_RD3
    { PD3, HAL_LL_TIM_INDEX_2, hal_ll_tim_module_num(CCP_MODULE_2) },
    #endif
    #ifdef PWM_CCP2_RD4
    { PD4, HAL_LL_TIM_INDEX_2, hal_ll_tim_module_num(CCP_MODULE_2) },
    #endif
    #ifdef PWM_CCP2_RD5
    { PD5, HAL_LL_TIM_INDEX_2, hal_ll_tim_module_num(CCP_MODULE_2) },
    #endif
    #ifdef PWM_CCP2_RD6
    { PD6, HAL_LL_TIM_INDEX_2, hal_ll_tim_module_num(CCP_MODULE_2) },
    #endif
    #ifdef PWM_CCP2_RD7
    { PD7, HAL_LL_TIM_INDEX_2, hal_ll_tim_module_num(CCP_MODULE_2) },
    #endif
    #ifdef PWM_CCP2_RF0
    { PF0, HAL_LL_TIM_INDEX_2, hal_ll_tim_module_num(CCP_MODULE_2) },
    #endif
    #ifdef PWM_CCP2_RF1
    { PF1, HAL_LL_TIM_INDEX_2, hal_ll_tim_module_num(CCP_MODULE_2) },
    #endif
    #ifdef PWM_CCP2_RF2
    { PF2, HAL_LL_TIM_INDEX_2, hal_ll_tim_module_num(CCP_MODULE_2) },
    #endif
    #ifdef PWM_CCP2_RF3
    { PF3, HAL_LL_TIM_INDEX_2, hal_ll_tim_module_num(CCP_MODULE_2) },
    #endif
    #ifdef PWM_CCP2_RF4
    { PF4, HAL_LL_TIM_INDEX_2, hal_ll_tim_module_num(CCP_MODULE_2) },
    #endif
    #ifdef PWM_CCP2_RF5
    { PF5, HAL_LL_TIM_INDEX_2, hal_ll_tim_module_num(CCP_MODULE_2) },
    #endif
    #ifdef PWM_CCP2_RF6
    { PF6, HAL_LL_TIM_INDEX_2, hal_ll_tim_module_num(CCP_MODULE_2) },
    #endif
    #ifdef PWM_CCP2_RF7
    { PF7, HAL_LL_TIM_INDEX_2, hal_ll_tim_module_num(CCP_MODULE_2) },
    #endif
    #ifdef PWM_CCP2_RE7
    { PE7, HAL_LL_TIM_INDEX_2, hal_ll_tim_module_num(CCP_MODULE_2) },
    #endif
    #ifdef PWM_CCP2_RA3
    { PA3, HAL_LL_TIM_INDEX_2, hal_ll_tim_module_num(CCP_MODULE_2) },
    #endif
    #ifdef PWM_CCP2_RG1
    { PG1, HAL_LL_TIM_INDEX_2, hal_ll_tim_module_num(CCP_MODULE_2) },
    #endif
    #ifdef PWM_CCP2_RG3
    { PG3, HAL_LL_TIM_INDEX_2, hal_ll_tim_module_num(CCP_MODULE_2) },
    #endif
    #ifdef PWM_CCP2_RE0
    { PE0, HAL_LL_TIM_INDEX_2, hal_ll_tim_module_num(CCP_MODULE_2) },
    #endif
    #ifdef PWM_CCP2_RE1
    { PE1, HAL_LL_TIM_INDEX_2, hal_ll_tim_module_num(CCP_MODULE_2) },
    #endif
    #ifdef PWM_CCP2_RE2
    { PE2, HAL_LL_TIM_INDEX_2, hal_ll_tim_module_num(CCP_MODULE_2) },
    #endif
    #ifdef PWM_CCP2_RE3
    { PE3, HAL_LL_TIM_INDEX_2, hal_ll_tim_module_num(CCP_MODULE_2) },
    #endif
    #ifdef PWM_CCP2_RE4
    { PE4, HAL_LL_TIM_INDEX_2, hal_ll_tim_module_num(CCP_MODULE_2) },
    #endif
    #ifdef PWM_CCP2_RE5
    { PE5, HAL_LL_TIM_INDEX_2, hal_ll_tim_module_num(CCP_MODULE_2) },
    #endif
    #ifdef PWM_CCP2_RE6
    { PE6, HAL_LL_TIM_INDEX_2, hal_ll_tim_module_num(CCP_MODULE_2) },
    #endif
    #endif

    #ifdef CCP_MODULE_3
    #ifdef PWM_CCP3_RB0
    { PB0, HAL_LL_TIM_INDEX_2, hal_ll_tim_module_num(CCP_MODULE_3) },
    #endif
    #ifdef PWM_CCP3_RB1
    { PB1, HAL_LL_TIM_INDEX_2, hal_ll_tim_module_num(CCP_MODULE_3) },
    #endif
    #ifdef PWM_CCP3_RB2
    { PB2, HAL_LL_TIM_INDEX_2, hal_ll_tim_module_num(CCP_MODULE_3) },
    #endif
    #ifdef PWM_CCP3_RB3
    { PB3, HAL_LL_TIM_INDEX_2, hal_ll_tim_module_num(CCP_MODULE_3) },
    #endif
    #ifdef PWM_CCP3_RB4
    { PB4, HAL_LL_TIM_INDEX_2, hal_ll_tim_module_num(CCP_MODULE_3) },
    #endif
    #ifdef PWM_CCP3_RB5
    { PB5, HAL_LL_TIM_INDEX_2, hal_ll_tim_module_num(CCP_MODULE_3) },
    #endif
    #ifdef PWM_CCP3_RB6
    { PB6, HAL_LL_TIM_INDEX_2, hal_ll_tim_module_num(CCP_MODULE_3) },
    #endif
    #ifdef PWM_CCP3_RB7
    { PB7, HAL_LL_TIM_INDEX_2, hal_ll_tim_module_num(CCP_MODULE_3) },
    #endif
    #ifdef PWM_CCP3_RC0
    { PC0, HAL_LL_TIM_INDEX_2, hal_ll_tim_module_num(CCP_MODULE_3) },
    #endif
    #ifdef PWM_CCP3_RC1
    { PC1, HAL_LL_TIM_INDEX_2, hal_ll_tim_module_num(CCP_MODULE_3) },
    #endif
    #ifdef PWM_CCP3_RC2
    { PC2, HAL_LL_TIM_INDEX_2, hal_ll_tim_module_num(CCP_MODULE_3) },
    #endif
    #ifdef PWM_CCP3_RC3
    { PC3, HAL_LL_TIM_INDEX_2, hal_ll_tim_module_num(CCP_MODULE_3) },
    #endif
    #ifdef PWM_CCP3_RC4
    { PC4, HAL_LL_TIM_INDEX_2, hal_ll_tim_module_num(CCP_MODULE_3) },
    #endif
    #ifdef PWM_CCP3_RC5
    { PC5, HAL_LL_TIM_INDEX_2, hal_ll_tim_module_num(CCP_MODULE_3) },
    #endif
    #ifdef PWM_CCP3_RC6
    { PC6, HAL_LL_TIM_INDEX_2, hal_ll_tim_module_num(CCP_MODULE_3) },
    #endif
    #ifdef PWM_CCP3_RC7
    { PC7, HAL_LL_TIM_INDEX_2, hal_ll_tim_module_num(CCP_MODULE_3) },
    #endif
    #ifdef PWM_CCP3_RA0
    { PA0, HAL_LL_TIM_INDEX_2, hal_ll_tim_module_num(CCP_MODULE_3) },
    #endif
    #ifdef PWM_CCP3_RA1
    { PA1, HAL_LL_TIM_INDEX_2, hal_ll_tim_module_num(CCP_MODULE_3) },
    #endif
    #ifdef PWM_CCP3_RA5
    { PA5, HAL_LL_TIM_INDEX_2, hal_ll_tim_module_num(CCP_MODULE_3) },
    #endif
    #ifdef PWM_CCP3_RD0
    { PD0, HAL_LL_TIM_INDEX_2, hal_ll_tim_module_num(CCP_MODULE_3) },
    #endif
    #ifdef PWM_CCP3_RD1
    { PD1, HAL_LL_TIM_INDEX_2, hal_ll_tim_module_num(CCP_MODULE_3) },
    #endif
    #ifdef PWM_CCP3_RD2
    { PD2, HAL_LL_TIM_INDEX_2, hal_ll_tim_module_num(CCP_MODULE_3) },
    #endif
    #ifdef PWM_CCP3_RD3
    { PD3, HAL_LL_TIM_INDEX_2, hal_ll_tim_module_num(CCP_MODULE_3) },
    #endif
    #ifdef PWM_CCP3_RD4
    { PD4, HAL_LL_TIM_INDEX_2, hal_ll_tim_module_num(CCP_MODULE_3) },
    #endif
    #ifdef PWM_CCP3_RD5
    { PD5, HAL_LL_TIM_INDEX_2, hal_ll_tim_module_num(CCP_MODULE_3) },
    #endif
    #ifdef PWM_CCP3_RD6
    { PD6, HAL_LL_TIM_INDEX_2, hal_ll_tim_module_num(CCP_MODULE_3) },
    #endif
    #ifdef PWM_CCP3_RD7
    { PD7, HAL_LL_TIM_INDEX_2, hal_ll_tim_module_num(CCP_MODULE_3) },
    #endif
    #ifdef PWM_CCP3_RE0
    { PE0, HAL_LL_TIM_INDEX_2, hal_ll_tim_module_num(CCP_MODULE_3) },
    #endif
    #ifdef PWM_CCP3_RG0
    { PG0, HAL_LL_TIM_INDEX_2, hal_ll_tim_module_num(CCP_MODULE_3) },
    #endif
    #ifdef PWM_CCP3_RA2
    { PA2, HAL_LL_TIM_INDEX_2, hal_ll_tim_module_num(CCP_MODULE_3) },
    #endif
    #ifdef PWM_CCP3_RA6
    { PA6, HAL_LL_TIM_INDEX_2, hal_ll_tim_module_num(CCP_MODULE_3) },
    #endif
    #ifdef PWM_CCP3_RA7
    { PA7, HAL_LL_TIM_INDEX_2, hal_ll_tim_module_num(CCP_MODULE_3) },
    #endif
    #ifdef PWM_CCP3_RE2
    { PE2, HAL_LL_TIM_INDEX_2, hal_ll_tim_module_num(CCP_MODULE_3) },
    #endif
    #ifdef PWM_CCP3_RE6
    { PE6, HAL_LL_TIM_INDEX_2, hal_ll_tim_module_num(CCP_MODULE_3) },
    #endif
    #ifdef PWM_CCP3_RF7
    { PF7, HAL_LL_TIM_INDEX_2, hal_ll_tim_module_num(CCP_MODULE_3) },
    #endif
    #ifdef PWM_CCP3_RG2
    { PG2, HAL_LL_TIM_INDEX_2, hal_ll_tim_module_num(CCP_MODULE_3) },
    #endif
    #ifdef PWM_CCP3_RE1
    { PE1, HAL_LL_TIM_INDEX_2, hal_ll_tim_module_num(CCP_MODULE_3) },
    #endif
    #ifdef PWM_CCP3_RE3
    { PE3, HAL_LL_TIM_INDEX_2, hal_ll_tim_module_num(CCP_MODULE_3) },
    #endif
    #ifdef PWM_CCP3_RE4
    { PE4, HAL_LL_TIM_INDEX_2, hal_ll_tim_module_num(CCP_MODULE_3) },
    #endif
    #ifdef PWM_CCP3_RE5
    { PE5, HAL_LL_TIM_INDEX_2, hal_ll_tim_module_num(CCP_MODULE_3) },
    #endif
    #ifdef PWM_CCP3_RE7
    { PE7, HAL_LL_TIM_INDEX_2, hal_ll_tim_module_num(CCP_MODULE_3) },
    #endif
    #endif

    #ifdef CCP_MODULE_4
    #ifdef PWM_CCP4_RB0
    { PB0, HAL_LL_TIM_INDEX_2, hal_ll_tim_module_num(CCP_MODULE_4) },
    #endif
    #ifdef PWM_CCP4_RB1
    { PB1, HAL_LL_TIM_INDEX_2, hal_ll_tim_module_num(CCP_MODULE_4) },
    #endif
    #ifdef PWM_CCP4_RB2
    { PB2, HAL_LL_TIM_INDEX_2, hal_ll_tim_module_num(CCP_MODULE_4) },
    #endif
    #ifdef PWM_CCP4_RB3
    { PB3, HAL_LL_TIM_INDEX_2, hal_ll_tim_module_num(CCP_MODULE_4) },
    #endif
    #ifdef PWM_CCP4_RB4
    { PB4, HAL_LL_TIM_INDEX_2, hal_ll_tim_module_num(CCP_MODULE_4) },
    #endif
    #ifdef PWM_CCP4_RB5
    { PB5, HAL_LL_TIM_INDEX_2, hal_ll_tim_module_num(CCP_MODULE_4) },
    #endif
    #ifdef PWM_CCP4_RB6
    { PB6, HAL_LL_TIM_INDEX_2, hal_ll_tim_module_num(CCP_MODULE_4) },
    #endif
    #ifdef PWM_CCP4_RB7
    { PB7, HAL_LL_TIM_INDEX_2, hal_ll_tim_module_num(CCP_MODULE_4) },
    #endif
    #ifdef PWM_CCP4_RC0
    { PC0, HAL_LL_TIM_INDEX_2, hal_ll_tim_module_num(CCP_MODULE_4) },
    #endif
    #ifdef PWM_CCP4_RC1
    { PC1, HAL_LL_TIM_INDEX_2, hal_ll_tim_module_num(CCP_MODULE_4) },
    #endif
    #ifdef PWM_CCP4_RC2
    { PC2, HAL_LL_TIM_INDEX_2, hal_ll_tim_module_num(CCP_MODULE_4) },
    #endif
    #ifdef PWM_CCP4_RC3
    { PC3, HAL_LL_TIM_INDEX_2, hal_ll_tim_module_num(CCP_MODULE_4) },
    #endif
    #ifdef PWM_CCP4_RC4
    { PC4, HAL_LL_TIM_INDEX_2, hal_ll_tim_module_num(CCP_MODULE_4) },
    #endif
    #ifdef PWM_CCP4_RC5
    { PC5, HAL_LL_TIM_INDEX_2, hal_ll_tim_module_num(CCP_MODULE_4) },
    #endif
    #ifdef PWM_CCP4_RC6
    { PC6, HAL_LL_TIM_INDEX_2, hal_ll_tim_module_num(CCP_MODULE_4) },
    #endif
    #ifdef PWM_CCP4_RC7
    { PC7, HAL_LL_TIM_INDEX_2, hal_ll_tim_module_num(CCP_MODULE_4) },
    #endif
    #ifdef PWM_CCP4_RD0
    { PD0, HAL_LL_TIM_INDEX_2, hal_ll_tim_module_num(CCP_MODULE_4) },
    #endif
    #ifdef PWM_CCP4_RD1
    { PD1, HAL_LL_TIM_INDEX_2, hal_ll_tim_module_num(CCP_MODULE_4) },
    #endif
    #ifdef PWM_CCP4_RD2
    { PD2, HAL_LL_TIM_INDEX_2, hal_ll_tim_module_num(CCP_MODULE_4) },
    #endif
    #ifdef PWM_CCP4_RD3
    { PD3, HAL_LL_TIM_INDEX_2, hal_ll_tim_module_num(CCP_MODULE_4) },
    #endif
    #ifdef PWM_CCP4_RD4
    { PD4, HAL_LL_TIM_INDEX_2, hal_ll_tim_module_num(CCP_MODULE_4) },
    #endif
    #ifdef PWM_CCP4_RD5
    { PD5, HAL_LL_TIM_INDEX_2, hal_ll_tim_module_num(CCP_MODULE_4) },
    #endif
    #ifdef PWM_CCP4_RD6
    { PD6, HAL_LL_TIM_INDEX_2, hal_ll_tim_module_num(CCP_MODULE_4) },
    #endif
    #ifdef PWM_CCP4_RD7
    { PD7, HAL_LL_TIM_INDEX_2, hal_ll_tim_module_num(CCP_MODULE_4) },
    #endif
    #ifdef PWM_CCP4_RG3
    { PG3, HAL_LL_TIM_INDEX_2, hal_ll_tim_module_num(CCP_MODULE_4) },
    #endif
    #ifdef PWM_CCP4_RA3
    { PA3, HAL_LL_TIM_INDEX_2, hal_ll_tim_module_num(CCP_MODULE_4) },
    #endif
    #ifdef PWM_CCP4_RE7
    { PE7, HAL_LL_TIM_INDEX_2, hal_ll_tim_module_num(CCP_MODULE_4) },
    #endif
    #ifdef PWM_CCP4_RF5
    { PF5, HAL_LL_TIM_INDEX_2, hal_ll_tim_module_num(CCP_MODULE_4) },
    #endif
    #ifdef PWM_CCP4_RG1
    { PG1, HAL_LL_TIM_INDEX_2, hal_ll_tim_module_num(CCP_MODULE_4) },
    #endif
    #ifdef PWM_CCP4_RE0
    { PE0, HAL_LL_TIM_INDEX_2, hal_ll_tim_module_num(CCP_MODULE_4) },
    #endif
    #ifdef PWM_CCP4_RE1
    { PE1, HAL_LL_TIM_INDEX_2, hal_ll_tim_module_num(CCP_MODULE_4) },
    #endif
    #ifdef PWM_CCP4_RE2
    { PE2, HAL_LL_TIM_INDEX_2, hal_ll_tim_module_num(CCP_MODULE_4) },
    #endif
    #ifdef PWM_CCP4_RE3
    { PE3, HAL_LL_TIM_INDEX_2, hal_ll_tim_module_num(CCP_MODULE_4) },
    #endif
    #ifdef PWM_CCP4_RE4
    { PE4, HAL_LL_TIM_INDEX_2, hal_ll_tim_module_num(CCP_MODULE_4) },
    #endif
    #ifdef PWM_CCP4_RE5
    { PE5, HAL_LL_TIM_INDEX_2, hal_ll_tim_module_num(CCP_MODULE_4) },
    #endif
    #ifdef PWM_CCP4_RE6
    { PE6, HAL_LL_TIM_INDEX_2, hal_ll_tim_module_num(CCP_MODULE_4) },
    #endif
    #ifdef PWM_CCP4_RG0
    { PG0, HAL_LL_TIM_INDEX_2, hal_ll_tim_module_num(CCP_MODULE_4) },
    #endif
    #ifdef PWM_CCP4_RG2
    { PG2, HAL_LL_TIM_INDEX_2, hal_ll_tim_module_num(CCP_MODULE_4) },
    #endif
    #ifdef PWM_CCP4_RG4
    { PG4, HAL_LL_TIM_INDEX_2, hal_ll_tim_module_num(CCP_MODULE_4) },
    #endif
    #ifdef PWM_CCP4_RG5
    { PG5, HAL_LL_TIM_INDEX_2, hal_ll_tim_module_num(CCP_MODULE_4) },
    #endif
    #ifdef PWM_CCP4_RG6
    { PG6, HAL_LL_TIM_INDEX_2, hal_ll_tim_module_num(CCP_MODULE_4) },
    #endif
    #ifdef PWM_CCP4_RG7
    { PG7, HAL_LL_TIM_INDEX_2, hal_ll_tim_module_num(CCP_MODULE_4) },
    #endif
    #endif

    #ifdef CCP_MODULE_5
    #ifdef PWM_CCP5_RB5
    { PB5, HAL_LL_TIM_INDEX_2, hal_ll_tim_module_num(CCP_MODULE_5) },
    #endif
    #ifdef PWM_CCP5_RA4
    { PA4, HAL_LL_TIM_INDEX_2, hal_ll_tim_module_num(CCP_MODULE_5) },
    #endif
    #ifdef PWM_CCP5_RE2
    { PE2, HAL_LL_TIM_INDEX_2, hal_ll_tim_module_num(CCP_MODULE_5) },
    #endif
    #ifdef PWM_CCP5_RG4
    { PG4, HAL_LL_TIM_INDEX_2, hal_ll_tim_module_num(CCP_MODULE_5) },
    #endif
    #ifdef PWM_CCP5_RA0
    { PA0, HAL_LL_TIM_INDEX_2, hal_ll_tim_module_num(CCP_MODULE_5) },
    #endif
    #ifdef PWM_CCP5_RB0
    { PB0, HAL_LL_TIM_INDEX_2, hal_ll_tim_module_num(CCP_MODULE_5) },
    #endif
    #ifdef PWM_CCP5_RB4
    { PB4, HAL_LL_TIM_INDEX_2, hal_ll_tim_module_num(CCP_MODULE_5) },
    #endif
    #ifdef PWM_CCP5_RC5
    { PC5, HAL_LL_TIM_INDEX_2, hal_ll_tim_module_num(CCP_MODULE_5) },
    #endif
    #ifdef PWM_CCP5_RD0
    { PD0, HAL_LL_TIM_INDEX_2, hal_ll_tim_module_num(CCP_MODULE_5) },
    #endif
    #ifdef PWM_CCP5_RD4
    { PD4, HAL_LL_TIM_INDEX_2, hal_ll_tim_module_num(CCP_MODULE_5) },
    #endif
    #ifdef PWM_CCP5_RE0
    { PE0, HAL_LL_TIM_INDEX_2, hal_ll_tim_module_num(CCP_MODULE_5) },
    #endif
    #ifdef PWM_CCP5_RE4
    { PE4, HAL_LL_TIM_INDEX_2, hal_ll_tim_module_num(CCP_MODULE_5) },
    #endif
    #ifdef PWM_CCP5_RF2
    { PF2, HAL_LL_TIM_INDEX_2, hal_ll_tim_module_num(CCP_MODULE_5) },
    #endif
    #ifdef PWM_CCP5_RF6
    { PF6, HAL_LL_TIM_INDEX_2, hal_ll_tim_module_num(CCP_MODULE_5) },
    #endif
    #ifdef PWM_CCP5_RE1
    { PE1, HAL_LL_TIM_INDEX_2, hal_ll_tim_module_num(CCP_MODULE_5) },
    #endif
    #ifdef PWM_CCP5_RE3
    { PE3, HAL_LL_TIM_INDEX_2, hal_ll_tim_module_num(CCP_MODULE_5) },
    #endif
    #ifdef PWM_CCP5_RE5
    { PE5, HAL_LL_TIM_INDEX_2, hal_ll_tim_module_num(CCP_MODULE_5) },
    #endif
    #ifdef PWM_CCP5_RE6
    { PE6, HAL_LL_TIM_INDEX_2, hal_ll_tim_module_num(CCP_MODULE_5) },
    #endif
    #ifdef PWM_CCP5_RE7
    { PE7, HAL_LL_TIM_INDEX_2, hal_ll_tim_module_num(CCP_MODULE_5) },
    #endif
    #ifdef PWM_CCP5_RG0
    { PG0, HAL_LL_TIM_INDEX_2, hal_ll_tim_module_num(CCP_MODULE_5) },
    #endif
    #ifdef PWM_CCP5_RG1
    { PG1, HAL_LL_TIM_INDEX_2, hal_ll_tim_module_num(CCP_MODULE_5) },
    #endif
    #ifdef PWM_CCP5_RG2
    { PG2, HAL_LL_TIM_INDEX_2, hal_ll_tim_module_num(CCP_MODULE_5) },
    #endif
    #ifdef PWM_CCP5_RG3
    { PG3, HAL_LL_TIM_INDEX_2, hal_ll_tim_module_num(CCP_MODULE_5) },
    #endif
    #ifdef PWM_CCP5_RG5
    { PG5, HAL_LL_TIM_INDEX_2, hal_ll_tim_module_num(CCP_MODULE_5) },
    #endif
    #ifdef PWM_CCP5_RG6
    { PG6, HAL_LL_TIM_INDEX_2, hal_ll_tim_module_num(CCP_MODULE_5) },
    #endif
    #ifdef PWM_CCP5_RG7
    { PG7, HAL_LL_TIM_INDEX_2, hal_ll_tim_module_num(CCP_MODULE_5) },
    #endif
    #endif

    #ifdef CCP_MODULE_6
    #ifdef PWM_CCP6_RB6
    { PB6, HAL_LL_TIM_INDEX_2, hal_ll_tim_module_num(CCP_MODULE_6) },
    #endif
    #ifdef PWM_CCP6_RA2
    { PA2, HAL_LL_TIM_INDEX_2, hal_ll_tim_module_num(CCP_MODULE_6) },
    #endif
    #ifdef PWM_CCP6_RA7
    { PA7, HAL_LL_TIM_INDEX_2, hal_ll_tim_module_num(CCP_MODULE_6) },
    #endif
    #ifdef PWM_CCP6_RA6
    { PA6, HAL_LL_TIM_INDEX_2, hal_ll_tim_module_num(CCP_MODULE_6) },
    #endif
    #ifdef PWM_CCP6_RB2
    { PB2, HAL_LL_TIM_INDEX_2, hal_ll_tim_module_num(CCP_MODULE_6) },
    #endif
    #ifdef PWM_CCP6_RC6
    { PC6, HAL_LL_TIM_INDEX_2, hal_ll_tim_module_num(CCP_MODULE_6) },
    #endif
    #ifdef PWM_CCP6_RD2
    { PD2, HAL_LL_TIM_INDEX_2, hal_ll_tim_module_num(CCP_MODULE_6) },
    #endif
    #ifdef PWM_CCP6_RD6
    { PD6, HAL_LL_TIM_INDEX_2, hal_ll_tim_module_num(CCP_MODULE_6) },
    #endif
    #ifdef PWM_CCP6_RE2
    { PE2, HAL_LL_TIM_INDEX_2, hal_ll_tim_module_num(CCP_MODULE_6) },
    #endif
    #ifdef PWM_CCP6_RE6
    { PE6, HAL_LL_TIM_INDEX_2, hal_ll_tim_module_num(CCP_MODULE_6) },
    #endif
    #ifdef PWM_CCP6_RF7
    { PF7, HAL_LL_TIM_INDEX_2, hal_ll_tim_module_num(CCP_MODULE_6) },
    #endif
    #ifdef PWM_CCP6_RG2
    { PG2, HAL_LL_TIM_INDEX_2, hal_ll_tim_module_num(CCP_MODULE_6) },
    #endif
    #ifdef PWM_CCP6_RH7
    { PH7, HAL_LL_TIM_INDEX_2, hal_ll_tim_module_num(CCP_MODULE_6) },
    #endif
    #endif

    #ifdef CCP_MODULE_7
    #ifdef PWM_CCP7_RB7
    { PB7, HAL_LL_TIM_INDEX_2, hal_ll_tim_module_num(CCP_MODULE_7) },
    #endif
    #ifdef PWM_CCP7_RA1
    { PA1, HAL_LL_TIM_INDEX_2, hal_ll_tim_module_num(CCP_MODULE_7) },
    #endif
    #ifdef PWM_CCP7_RA5
    { PA5, HAL_LL_TIM_INDEX_2, hal_ll_tim_module_num(CCP_MODULE_7) },
    #endif
    #ifdef PWM_CCP7_RB1
    { PB1, HAL_LL_TIM_INDEX_2, hal_ll_tim_module_num(CCP_MODULE_7) },
    #endif
    #ifdef PWM_CCP7_RB5
    { PB5, HAL_LL_TIM_INDEX_2, hal_ll_tim_module_num(CCP_MODULE_7) },
    #endif
    #ifdef PWM_CCP7_RC4
    { PC4, HAL_LL_TIM_INDEX_2, hal_ll_tim_module_num(CCP_MODULE_7) },
    #endif
    #ifdef PWM_CCP7_RD1
    { PD1, HAL_LL_TIM_INDEX_2, hal_ll_tim_module_num(CCP_MODULE_7) },
    #endif
    #ifdef PWM_CCP7_RD5
    { PD5, HAL_LL_TIM_INDEX_2, hal_ll_tim_module_num(CCP_MODULE_7) },
    #endif
    #ifdef PWM_CCP7_RE1
    { PE1, HAL_LL_TIM_INDEX_2, hal_ll_tim_module_num(CCP_MODULE_7) },
    #endif
    #ifdef PWM_CCP7_RE3
    { PE3, HAL_LL_TIM_INDEX_2, hal_ll_tim_module_num(CCP_MODULE_7) },
    #endif
    #ifdef PWM_CCP7_RE5
    { PE5, HAL_LL_TIM_INDEX_2, hal_ll_tim_module_num(CCP_MODULE_7) },
    #endif
    #ifdef PWM_CCP7_RH6
    { PH6, HAL_LL_TIM_INDEX_2, hal_ll_tim_module_num(CCP_MODULE_7) },
    #endif
    #endif

    #ifdef CCP_MODULE_8
    #ifdef PWM_CCP8_RC1
    { PC1, HAL_LL_TIM_INDEX_2, hal_ll_tim_module_num(CCP_MODULE_8) },
    #endif
    #ifdef PWM_CCP8_RA0
    { PA0, HAL_LL_TIM_INDEX_2, hal_ll_tim_module_num(CCP_MODULE_8) },
    #endif
    #ifdef PWM_CCP8_RA4
    { PA4, HAL_LL_TIM_INDEX_2, hal_ll_tim_module_num(CCP_MODULE_8) },
    #endif
    #ifdef PWM_CCP8_RB0
    { PB0, HAL_LL_TIM_INDEX_2, hal_ll_tim_module_num(CCP_MODULE_8) },
    #endif
    #ifdef PWM_CCP8_RB4
    { PB4, HAL_LL_TIM_INDEX_2, hal_ll_tim_module_num(CCP_MODULE_8) },
    #endif
    #ifdef PWM_CCP8_RC5
    { PC5, HAL_LL_TIM_INDEX_2, hal_ll_tim_module_num(CCP_MODULE_8) },
    #endif
    #ifdef PWM_CCP8_RD0
    { PD0, HAL_LL_TIM_INDEX_2, hal_ll_tim_module_num(CCP_MODULE_8) },
    #endif
    #ifdef PWM_CCP8_RD4
    { PD4, HAL_LL_TIM_INDEX_2, hal_ll_tim_module_num(CCP_MODULE_8) },
    #endif
    #ifdef PWM_CCP8_RE0
    { PE0, HAL_LL_TIM_INDEX_2, hal_ll_tim_module_num(CCP_MODULE_8) },
    #endif
    #ifdef PWM_CCP8_RE4
    { PE4, HAL_LL_TIM_INDEX_2, hal_ll_tim_module_num(CCP_MODULE_8) },
    #endif
    #ifdef PWM_CCP8_RF2
    { PF2, HAL_LL_TIM_INDEX_2, hal_ll_tim_module_num(CCP_MODULE_8) },
    #endif
    #ifdef PWM_CCP8_RF6
    { PF6, HAL_LL_TIM_INDEX_2, hal_ll_tim_module_num(CCP_MODULE_8) },
    #endif
    #ifdef PWM_CCP8_RG4
    { PG4, HAL_LL_TIM_INDEX_2, hal_ll_tim_module_num(CCP_MODULE_8) },
    #endif
    #ifdef PWM_CCP8_RH5
    { PH5, HAL_LL_TIM_INDEX_2, hal_ll_tim_module_num(CCP_MODULE_8) },
    #endif
    #endif

    #ifdef CCP_MODULE_9
    #ifdef PWM_CCP9_RC6
    { PC6, HAL_LL_TIM_INDEX_2, hal_ll_tim_module_num(CCP_MODULE_9) },
    #endif
    #ifdef PWM_CCP9_RA1
    { PA1, HAL_LL_TIM_INDEX_2, hal_ll_tim_module_num(CCP_MODULE_9) },
    #endif
    #ifdef PWM_CCP9_RA5
    { PA5, HAL_LL_TIM_INDEX_2, hal_ll_tim_module_num(CCP_MODULE_9) },
    #endif
    #ifdef PWM_CCP9_RB1
    { PB1, HAL_LL_TIM_INDEX_2, hal_ll_tim_module_num(CCP_MODULE_9) },
    #endif
    #ifdef PWM_CCP9_RB5
    { PB5, HAL_LL_TIM_INDEX_2, hal_ll_tim_module_num(CCP_MODULE_9) },
    #endif
    #ifdef PWM_CCP9_RC4
    { PC4, HAL_LL_TIM_INDEX_2, hal_ll_tim_module_num(CCP_MODULE_9) },
    #endif
    #ifdef PWM_CCP9_RD1
    { PD1, HAL_LL_TIM_INDEX_2, hal_ll_tim_module_num(CCP_MODULE_9) },
    #endif
    #ifdef PWM_CCP9_RD5
    { PD5, HAL_LL_TIM_INDEX_2, hal_ll_tim_module_num(CCP_MODULE_9) },
    #endif
    #ifdef PWM_CCP9_RE1
    { PE1, HAL_LL_TIM_INDEX_2, hal_ll_tim_module_num(CCP_MODULE_9) },
    #endif
    #ifdef PWM_CCP9_RE3
    { PE3, HAL_LL_TIM_INDEX_2, hal_ll_tim_module_num(CCP_MODULE_9) },
    #endif
    #ifdef PWM_CCP9_RE5
    { PE5, HAL_LL_TIM_INDEX_2, hal_ll_tim_module_num(CCP_MODULE_9) },
    #endif
    #ifdef PWM_CCP9_RH4
    { PH4, HAL_LL_TIM_INDEX_2, hal_ll_tim_module_num(CCP_MODULE_9) },
    #endif
    #endif

    #ifdef CCP_MODULE_10
    #ifdef PWM_CCP10_RC7
    { PC7, HAL_LL_TIM_INDEX_2, hal_ll_tim_module_num(CCP_MODULE_10) },
    #endif
    #ifdef PWM_CCP10_RA2
    { PA2, HAL_LL_TIM_INDEX_2, hal_ll_tim_module_num(CCP_MODULE_10) },
    #endif
    #ifdef PWM_CCP10_RA6
    { PA6, HAL_LL_TIM_INDEX_2, hal_ll_tim_module_num(CCP_MODULE_10) },
    #endif
    #ifdef PWM_CCP10_RA7
    { PA7, HAL_LL_TIM_INDEX_2, hal_ll_tim_module_num(CCP_MODULE_10) },
    #endif
    #ifdef PWM_CCP10_RB2
    { PB2, HAL_LL_TIM_INDEX_2, hal_ll_tim_module_num(CCP_MODULE_10) },
    #endif
    #ifdef PWM_CCP10_RC6
    { PC6, HAL_LL_TIM_INDEX_2, hal_ll_tim_module_num(CCP_MODULE_10) },
    #endif
    #ifdef PWM_CCP10_RD2
    { PD2, HAL_LL_TIM_INDEX_2, hal_ll_tim_module_num(CCP_MODULE_10) },
    #endif
    #ifdef PWM_CCP10_RD6
    { PD6, HAL_LL_TIM_INDEX_2, hal_ll_tim_module_num(CCP_MODULE_10) },
    #endif
    #ifdef PWM_CCP10_RE2
    { PE2, HAL_LL_TIM_INDEX_2, hal_ll_tim_module_num(CCP_MODULE_10) },
    #endif
    #ifdef PWM_CCP10_RE6
    { PE6, HAL_LL_TIM_INDEX_2, hal_ll_tim_module_num(CCP_MODULE_10) },
    #endif
    #ifdef PWM_CCP10_RF7
    { PF7, HAL_LL_TIM_INDEX_2, hal_ll_tim_module_num(CCP_MODULE_10) },
    #endif
    #ifdef PWM_CCP10_RG2
    { PG2, HAL_LL_TIM_INDEX_2, hal_ll_tim_module_num(CCP_MODULE_10) },
    #endif
    #endif

    { HAL_LL_PIN_NC, HAL_LL_MODULE_ERROR, HAL_LL_MODULE_ERROR }
    //------------ END CCP
};

#ifdef __cplusplus
}
#endif

#endif // _HAL_LL_TIM_PIN_MAP_H_
// ------------------------------------------------------------------------- END
