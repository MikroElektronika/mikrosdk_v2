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
/*

  This file is part of mikroSDK.

  Copyright (c) 2023, MikroElektonika - www.mikroe.com

  All rights reserved.

-------------------------------------------------------------------------- */
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

/*!< @brief Enumeration structure for PWM Channel selection. */
#define HAL_LL_TIM_CH_A ((uint8_t)0) /* Enable channel A driver for PWM pin. */
#define HAL_LL_TIM_CH_B ((uint8_t)1) /* Enable channel B driver for PWM pin. */
#define HAL_LL_TIM_CH_C ((uint8_t)2) /* Enable channel C driver for PWM pin. */
#define HAL_LL_TIM_CH_D ((uint8_t)3) /* Enable channel D driver for PWM pin. */
#define HAL_LL_TIM_CH_NONE ((uint8_t)4) /* This field represents standard PWM pin. */
#define HAL_LL_TIM_CH_DEFAULT (HAL_LL_TIM_CH_NONE) /* Default pin driver. */

/*!< @brief TIM Master pin map structure. */
typedef struct {
    hal_ll_pin_name_t pin;
    uint8_t module_index;
    uint8_t channel;
} hal_ll_tim_pin_map_t;

/*!< @brief CCP/TIM pins */
static const hal_ll_tim_pin_map_t _tim_map[] = {
    //------------ BEGIN CCP
    #ifdef TIM2_PB7_CH_A
    {PB7, hal_ll_tim_module_num(TIM_MODULE_2), HAL_LL_TIM_CH_A},
    #endif
    #ifdef TIM1_PB6_CH_B
    {PB6, hal_ll_tim_module_num(TIM_MODULE_1), HAL_LL_TIM_CH_B},
    #endif
    #ifdef TIM1_PB5_CH_A
    {PB5, hal_ll_tim_module_num(TIM_MODULE_1), HAL_LL_TIM_CH_A},
    #endif
    #ifdef TIM0_PB4_CH_A
    {PB4, hal_ll_tim_module_num(TIM_MODULE_0), HAL_LL_TIM_CH_A},
    #endif
    #ifdef TIM0_PB4_CH_NONE
    {PB4, hal_ll_tim_module_num(TIM_MODULE_0), HAL_LL_TIM_CH_DEFAULT},
    #endif
    #ifdef TIM1_PB7_CH_C
    {PB7, hal_ll_tim_module_num(TIM_MODULE_1), HAL_LL_TIM_CH_C},
    #endif
    #ifdef TIM2_PB7_CH_NONE
    {PB7, hal_ll_tim_module_num(TIM_MODULE_2), HAL_LL_TIM_CH_DEFAULT},
    #endif
    #ifdef TIM3_PE3_CH_A
    {PE3, hal_ll_tim_module_num(TIM_MODULE_3), HAL_LL_TIM_CH_A},
    #endif
    #ifdef TIM3_PE4_CH_B
    {PE4, hal_ll_tim_module_num(TIM_MODULE_3), HAL_LL_TIM_CH_B},
    #endif
    #ifdef TIM3_PE5_CH_C
    {PE5, hal_ll_tim_module_num(TIM_MODULE_3), HAL_LL_TIM_CH_C},
    #endif
    #ifdef TIM0_PB7_CH_A
    {PB7, hal_ll_tim_module_num(TIM_MODULE_0), HAL_LL_TIM_CH_A},
    #endif
    #ifdef TIM0_PG5_CH_B
    {PG5, hal_ll_tim_module_num(TIM_MODULE_0), HAL_LL_TIM_CH_B},
    #endif
    #ifdef TIM2_PB4_CH_A
    {PB4, hal_ll_tim_module_num(TIM_MODULE_2), HAL_LL_TIM_CH_A},
    #endif
    #ifdef TIM2_PH6_CH_B
    {PH6, hal_ll_tim_module_num(TIM_MODULE_2), HAL_LL_TIM_CH_B},
    #endif
    #ifdef TIM4_PH3_CH_A
    {PH3, hal_ll_tim_module_num(TIM_MODULE_4), HAL_LL_TIM_CH_A},
    #endif
    #ifdef TIM4_PH4_CH_B
    {PH4, hal_ll_tim_module_num(TIM_MODULE_4), HAL_LL_TIM_CH_B},
    #endif
    #ifdef TIM4_PH5_CH_C
    {PH5, hal_ll_tim_module_num(TIM_MODULE_4), HAL_LL_TIM_CH_C},
    #endif
    #ifdef TIM5_PL3_CH_A
    {PL3, hal_ll_tim_module_num(TIM_MODULE_5), HAL_LL_TIM_CH_A},
    #endif
    #ifdef TIM5_PL4_CH_B
    {PL4, hal_ll_tim_module_num(TIM_MODULE_5), HAL_LL_TIM_CH_B},
    #endif
    #ifdef TIM5_PL5_CH_C
    {PL5, hal_ll_tim_module_num(TIM_MODULE_5), HAL_LL_TIM_CH_C},
    #endif
    #ifdef TIM0_PB3_CH_A
    {PB3, hal_ll_tim_module_num(TIM_MODULE_0), HAL_LL_TIM_CH_A},
    #endif
    #ifdef TIM0_PB4_CH_B
    {PB4, hal_ll_tim_module_num(TIM_MODULE_0), HAL_LL_TIM_CH_B},
    #endif
    #ifdef TIM1_PD4_CH_B
    {PD4, hal_ll_tim_module_num(TIM_MODULE_1), HAL_LL_TIM_CH_B},
    #endif
    #ifdef TIM1_PD5_CH_A
    {PD5, hal_ll_tim_module_num(TIM_MODULE_1), HAL_LL_TIM_CH_A},
    #endif
    #ifdef TIM2_PD6_CH_B
    {PD6, hal_ll_tim_module_num(TIM_MODULE_2), HAL_LL_TIM_CH_B},
    #endif
    #ifdef TIM2_PD7_CH_A
    {PD7, hal_ll_tim_module_num(TIM_MODULE_2), HAL_LL_TIM_CH_A},
    #endif
    #ifdef TIM3_PB6_CH_A
    {PB6, hal_ll_tim_module_num(TIM_MODULE_3), HAL_LL_TIM_CH_A},
    #endif
    #ifdef TIM3_PB7_CH_B
    {PB7, hal_ll_tim_module_num(TIM_MODULE_3), HAL_LL_TIM_CH_B},
    #endif
    #ifdef TIM0_PB3_CH_NONE
    {PB3, hal_ll_tim_module_num(TIM_MODULE_0), HAL_LL_TIM_CH_DEFAULT},
    #endif
    #ifdef TIM2_PD7_CH_NONE
    {PD7, hal_ll_tim_module_num(TIM_MODULE_2), HAL_LL_TIM_CH_DEFAULT},
    #endif
    #ifdef TIM0_PD5_CH_B
    {PD5, hal_ll_tim_module_num(TIM_MODULE_0), HAL_LL_TIM_CH_B},
    #endif
    #ifdef TIM0_PD6_CH_A
    {PD6, hal_ll_tim_module_num(TIM_MODULE_0), HAL_LL_TIM_CH_A},
    #endif
    #ifdef TIM1_PB1_CH_A
    {PB1, hal_ll_tim_module_num(TIM_MODULE_1), HAL_LL_TIM_CH_A},
    #endif
    #ifdef TIM1_PB2_CH_B
    {PB2, hal_ll_tim_module_num(TIM_MODULE_1), HAL_LL_TIM_CH_B},
    #endif
    #ifdef TIM2_PB3_CH_A
    {PB3, hal_ll_tim_module_num(TIM_MODULE_2), HAL_LL_TIM_CH_A},
    #endif
    #ifdef TIM2_PD3_CH_B
    {PD3, hal_ll_tim_module_num(TIM_MODULE_2), HAL_LL_TIM_CH_B},
    #endif
    #ifdef TIM0_PD0_CH_B
    {PD0, hal_ll_tim_module_num(TIM_MODULE_0), HAL_LL_TIM_CH_B},
    #endif
    #ifdef TIM3_PC6_CH_A
    {PC6, hal_ll_tim_module_num(TIM_MODULE_3), HAL_LL_TIM_CH_A},
    #endif
    #ifdef TIM4_PB6_CH_B
    {PB6, hal_ll_tim_module_num(TIM_MODULE_4), HAL_LL_TIM_CH_B},
    #endif
    #ifdef TIM4_PC7_CH_A
    {PC7, hal_ll_tim_module_num(TIM_MODULE_4), HAL_LL_TIM_CH_A},
    #endif
    #ifdef TIM4_PD7_CH_D
    {PD7, hal_ll_tim_module_num(TIM_MODULE_4), HAL_LL_TIM_CH_D},
    #endif
    #ifdef TIM4_PB7_CH_B
    {PB7, hal_ll_tim_module_num(TIM_MODULE_4), HAL_LL_TIM_CH_B},
    #endif
    #ifdef TIM4_PC4_CH_A
    {PC4, hal_ll_tim_module_num(TIM_MODULE_4), HAL_LL_TIM_CH_A},
    #endif
    #ifdef TIM3_PD0_CH_A
    {PD0, hal_ll_tim_module_num(TIM_MODULE_3), HAL_LL_TIM_CH_A},
    #endif
    #ifdef TIM3_PD2_CH_B
    {PD2, hal_ll_tim_module_num(TIM_MODULE_3), HAL_LL_TIM_CH_B},
    #endif
    #ifdef TIM4_PD1_CH_A
    {PD1, hal_ll_tim_module_num(TIM_MODULE_4), HAL_LL_TIM_CH_A},
    #endif
    #ifdef TIM4_PD2_CH_B
    {PD2, hal_ll_tim_module_num(TIM_MODULE_4), HAL_LL_TIM_CH_B},
    #endif
    #ifdef TIM0_PC0_CH_A
    {PC0, hal_ll_tim_module_num(TIM_MODULE_0), HAL_LL_TIM_CH_A},
    #endif
    #ifdef TIM0_PC1_CH_B
    {PC1, hal_ll_tim_module_num(TIM_MODULE_0), HAL_LL_TIM_CH_B},
    #endif
    #ifdef TIM0_PC2_CH_C
    {PC2, hal_ll_tim_module_num(TIM_MODULE_0), HAL_LL_TIM_CH_C},
    #endif
    #ifdef TIM0_PC3_CH_D
    {PC3, hal_ll_tim_module_num(TIM_MODULE_0), HAL_LL_TIM_CH_D},
    #endif
    #ifdef TIM0_PC4_CH_A
    {PC4, hal_ll_tim_module_num(TIM_MODULE_0), HAL_LL_TIM_CH_A},
    #endif
    #ifdef TIM0_PC5_CH_B
    {PC5, hal_ll_tim_module_num(TIM_MODULE_0), HAL_LL_TIM_CH_B},
    #endif
    #ifdef TIM0_PC6_CH_C
    {PC6, hal_ll_tim_module_num(TIM_MODULE_0), HAL_LL_TIM_CH_C},
    #endif
    #ifdef TIM0_PC7_CH_D
    {PC7, hal_ll_tim_module_num(TIM_MODULE_0), HAL_LL_TIM_CH_D},
    #endif
    #ifdef TIM1_PC4_CH_A
    {PC4, hal_ll_tim_module_num(TIM_MODULE_1), HAL_LL_TIM_CH_A},
    #endif
    #ifdef TIM1_PC5_CH_B
    {PC5, hal_ll_tim_module_num(TIM_MODULE_1), HAL_LL_TIM_CH_B},
    #endif
    #ifdef TIM1_PD0_CH_A
    {PD0, hal_ll_tim_module_num(TIM_MODULE_1), HAL_LL_TIM_CH_A},
    #endif
    #ifdef TIM1_PD1_CH_B
    {PD1, hal_ll_tim_module_num(TIM_MODULE_1), HAL_LL_TIM_CH_B},
    #endif
    #ifdef TIM1_PD2_CH_C
    {PD2, hal_ll_tim_module_num(TIM_MODULE_1), HAL_LL_TIM_CH_C},
    #endif
    #ifdef TIM1_PD3_CH_D
    {PD3, hal_ll_tim_module_num(TIM_MODULE_1), HAL_LL_TIM_CH_D},
    #endif
    #ifdef TIM2_PE0_CH_A
    {PE0, hal_ll_tim_module_num(TIM_MODULE_2), HAL_LL_TIM_CH_A},
    #endif
    #ifdef TIM2_PE1_CH_B
    {PE1, hal_ll_tim_module_num(TIM_MODULE_2), HAL_LL_TIM_CH_B},
    #endif
    #ifdef TIM2_PE2_CH_C
    {PE2, hal_ll_tim_module_num(TIM_MODULE_2), HAL_LL_TIM_CH_C},
    #endif
    #ifdef TIM2_PE3_CH_D
    {PE3, hal_ll_tim_module_num(TIM_MODULE_2), HAL_LL_TIM_CH_D},
    #endif
    #ifdef TIM3_PF0_CH_A
    {PF0, hal_ll_tim_module_num(TIM_MODULE_3), HAL_LL_TIM_CH_A},
    #endif
    #ifdef TIM3_PF1_CH_B
    {PF1, hal_ll_tim_module_num(TIM_MODULE_3), HAL_LL_TIM_CH_B},
    #endif
    #ifdef TIM3_PF2_CH_C
    {PF2, hal_ll_tim_module_num(TIM_MODULE_3), HAL_LL_TIM_CH_C},
    #endif
    #ifdef TIM3_PF3_CH_D
    {PF3, hal_ll_tim_module_num(TIM_MODULE_3), HAL_LL_TIM_CH_D},
    #endif
    #ifdef TIM5_PD4_CH_A
    {PD4, hal_ll_tim_module_num(TIM_MODULE_5), HAL_LL_TIM_CH_A},
    #endif
    #ifdef TIM5_PD5_CH_B
    {PD5, hal_ll_tim_module_num(TIM_MODULE_5), HAL_LL_TIM_CH_B},
    #endif
    #ifdef TIM6_PE4_CH_A
    {PE4, hal_ll_tim_module_num(TIM_MODULE_6), HAL_LL_TIM_CH_A},
    #endif
    #ifdef TIM6_PE5_CH_B
    {PE5, hal_ll_tim_module_num(TIM_MODULE_6), HAL_LL_TIM_CH_B},
    #endif
    #ifdef TIM7_PF4_CH_A
    {PF4, hal_ll_tim_module_num(TIM_MODULE_7), HAL_LL_TIM_CH_A},
    #endif
    #ifdef TIM7_PF5_CH_B
    {PF5, hal_ll_tim_module_num(TIM_MODULE_7), HAL_LL_TIM_CH_B},
    #endif
    #ifdef TIM4_PC5_CH_B
    {PC5, hal_ll_tim_module_num(TIM_MODULE_4), HAL_LL_TIM_CH_B},
    #endif
    #ifdef TIM1_PD4_CH_A
    {PD4, hal_ll_tim_module_num(TIM_MODULE_1), HAL_LL_TIM_CH_A},
    #endif
    #ifdef TIM1_PD5_CH_B
    {PD5, hal_ll_tim_module_num(TIM_MODULE_1), HAL_LL_TIM_CH_B},
    #endif
    #ifdef TIM1_PD6_CH_C
    {PD6, hal_ll_tim_module_num(TIM_MODULE_1), HAL_LL_TIM_CH_C},
    #endif
    #ifdef TIM1_PD7_CH_D
    {PD7, hal_ll_tim_module_num(TIM_MODULE_1), HAL_LL_TIM_CH_D},
    #endif
    #ifdef TIM2_PE4_CH_A
    {PE4, hal_ll_tim_module_num(TIM_MODULE_2), HAL_LL_TIM_CH_A},
    #endif
    #ifdef TIM2_PE5_CH_B
    {PE5, hal_ll_tim_module_num(TIM_MODULE_2), HAL_LL_TIM_CH_B},
    #endif
    #ifdef TIM2_PE6_CH_C
    {PE6, hal_ll_tim_module_num(TIM_MODULE_2), HAL_LL_TIM_CH_C},
    #endif
    #ifdef TIM2_PE7_CH_D
    {PE7, hal_ll_tim_module_num(TIM_MODULE_2), HAL_LL_TIM_CH_D},
    #endif
    #ifdef TIM0_PC4_CH_A_ALT
    {PC4, hal_ll_tim_module_num(TIM_MODULE_0), HAL_LL_TIM_CH_A_ALT},
    #endif
    #ifdef TIM0_PC5_CH_B_ALT
    {PC5, hal_ll_tim_module_num(TIM_MODULE_0), HAL_LL_TIM_CH_B_ALT},
    #endif
    #ifdef TIM0_PC6_CH_C_ALT
    {PC6, hal_ll_tim_module_num(TIM_MODULE_0), HAL_LL_TIM_CH_C_ALT},
    #endif
    #ifdef TIM0_PC7_CH_D_ALT
    {PC7, hal_ll_tim_module_num(TIM_MODULE_0), HAL_LL_TIM_CH_D_ALT},
    #endif

    { HAL_LL_PIN_NC, HAL_LL_MODULE_ERROR, HAL_LL_MODULE_ERROR }
    //------------ END CCP
};

#ifdef __cplusplus
}
#endif

#endif // _HAL_LL_TIM_PIN_MAP_H_
// ---------------------------------------------------------------------- END
