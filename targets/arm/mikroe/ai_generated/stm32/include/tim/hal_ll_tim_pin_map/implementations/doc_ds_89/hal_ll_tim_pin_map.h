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
 * @file  hal_ll_tim_pin_map.h
 * @brief TIM HAL LOW LEVEL PIN MAP.
 */

#ifndef _HAL_LL_TIM_PIN_MAP_H_
#define _HAL_LL_TIM_PIN_MAP_H_

#ifdef __cplusplus
extern "C"{
#endif

#include "hal_ll_pin_names.h"

/*!< @brief Helper macro for getting adequate module index number */
#define hal_ll_tim_module_num(_module_num) (_module_num - 1)

/*!< @brief Alternate pin function structure. */
typedef struct
{
    hal_ll_pin_name_t pin;
    hal_ll_base_addr_t base;
    hal_ll_channel_t channel;
    uint32_t af;
    hal_ll_pin_name_t module_index;
} hal_ll_tim_pin_map_t;

typedef enum
{
    HAL_LL_TIM_CHANNEL_0 = 0,
    HAL_LL_TIM_CHANNEL_1,
    HAL_LL_TIM_CHANNEL_2,
    HAL_LL_TIM_CHANNEL_3,
    HAL_LL_TIM_CHANNEL_4,
    HAL_LL_TIM_CHANNEL_1N,
    HAL_LL_TIM_CHANNEL_2N,
    HAL_LL_TIM_CHANNEL_3N,
    HAL_LL_TIM_CHANNEL_4N
} hal_ll_tim_channel_t;

#ifdef TIM_MODULE_1
#define TIM1_BASE_ADDRESS (0x40012C00UL)
#define TIM1_BASE_ADDR TIM1_BASE_ADDRESS
#define HAL_LL_TIM1_BASE_ADDR TIM1_BASE_ADDRESS
#define HAL_LL_TIM1_BASE_ADDRESS TIM1_BASE_ADDRESS
#endif
#ifdef TIM_MODULE_2
#define TIM2_BASE_ADDRESS (0x40000000UL)
#define TIM2_BASE_ADDR TIM2_BASE_ADDRESS
#define HAL_LL_TIM2_BASE_ADDR TIM2_BASE_ADDRESS
#define HAL_LL_TIM2_BASE_ADDRESS TIM2_BASE_ADDRESS
#endif
#ifdef TIM_MODULE_3
#define TIM3_BASE_ADDRESS (0x40000400UL)
#define TIM3_BASE_ADDR TIM3_BASE_ADDRESS
#define HAL_LL_TIM3_BASE_ADDR TIM3_BASE_ADDRESS
#define HAL_LL_TIM3_BASE_ADDRESS TIM3_BASE_ADDRESS
#endif
#ifdef TIM_MODULE_4
#define TIM4_BASE_ADDRESS (0x40000800UL)
#define TIM4_BASE_ADDR TIM4_BASE_ADDRESS
#define HAL_LL_TIM4_BASE_ADDR TIM4_BASE_ADDRESS
#define HAL_LL_TIM4_BASE_ADDRESS TIM4_BASE_ADDRESS
#endif
#ifdef TIM_MODULE_8
#define TIM8_BASE_ADDRESS (0x40013400UL)
#define TIM8_BASE_ADDR TIM8_BASE_ADDRESS
#define HAL_LL_TIM8_BASE_ADDR TIM8_BASE_ADDRESS
#define HAL_LL_TIM8_BASE_ADDRESS TIM8_BASE_ADDRESS
#endif
#ifdef TIM_MODULE_15
#define TIM15_BASE_ADDRESS (0x40014000UL)
#define TIM15_BASE_ADDR TIM15_BASE_ADDRESS
#define HAL_LL_TIM15_BASE_ADDR TIM15_BASE_ADDRESS
#define HAL_LL_TIM15_BASE_ADDRESS TIM15_BASE_ADDRESS
#endif
#ifdef TIM_MODULE_16
#define TIM16_BASE_ADDRESS (0x40014400UL)
#define TIM16_BASE_ADDR TIM16_BASE_ADDRESS
#define HAL_LL_TIM16_BASE_ADDR TIM16_BASE_ADDRESS
#define HAL_LL_TIM16_BASE_ADDRESS TIM16_BASE_ADDRESS
#endif
#ifdef TIM_MODULE_17
#define TIM17_BASE_ADDRESS (0x40014800UL)
#define TIM17_BASE_ADDR TIM17_BASE_ADDRESS
#define HAL_LL_TIM17_BASE_ADDR TIM17_BASE_ADDRESS
#define HAL_LL_TIM17_BASE_ADDRESS TIM17_BASE_ADDRESS
#endif
#ifdef TIM_MODULE_20
#define TIM20_BASE_ADDRESS (0x40015000UL)
#define TIM20_BASE_ADDR TIM20_BASE_ADDRESS
#define HAL_LL_TIM20_BASE_ADDR TIM20_BASE_ADDRESS
#define HAL_LL_TIM20_BASE_ADDRESS TIM20_BASE_ADDRESS
#endif

/*!< @brief TIM pins. */
static const hal_ll_tim_pin_map_t _tim_map[] = {
    #ifdef LPTIM1_ETR_PB6_AF11
    // {PB6, LPTIM1_BASE_ADDRESS, 0, 11, hal_ll_lptim_module_num(LPTIM_MODULE_1)},
    #endif
    #ifdef LPTIM1_ETR_PC3_AF1
    // {PC3, LPTIM1_BASE_ADDRESS, 0, 1, hal_ll_lptim_module_num(LPTIM_MODULE_1)},
    #endif
    #ifdef TIM15_BKIN_PA9_AF9
    // {PA9, TIM15_BASE_ADDRESS, 0, 9, hal_ll_tim_module_num(TIM_MODULE_15)},
    #endif
    #ifdef TIM15_BKIN_PC5_AF2
    // {PC5, TIM15_BASE_ADDRESS, 0, 2, hal_ll_tim_module_num(TIM_MODULE_15)},
    #endif
    #ifdef TIM15_CH1N_PA1_AF9
    {PA1, TIM15_BASE_ADDRESS, HAL_LL_TIM_CHANNEL_1N, 9, hal_ll_tim_module_num(TIM_MODULE_15)},
    #endif
    #ifdef TIM15_CH1N_PB15_AF2
    {PB15, TIM15_BASE_ADDRESS, HAL_LL_TIM_CHANNEL_1N, 2, hal_ll_tim_module_num(TIM_MODULE_15)},
    #endif
    #ifdef TIM15_CH1_PA2_AF9
    {PA2, TIM15_BASE_ADDRESS, HAL_LL_TIM_CHANNEL_1, 9, hal_ll_tim_module_num(TIM_MODULE_15)},
    #endif
    #ifdef TIM15_CH1_PB14_AF1
    {PB14, TIM15_BASE_ADDRESS, HAL_LL_TIM_CHANNEL_1, 1, hal_ll_tim_module_num(TIM_MODULE_15)},
    #endif
    #ifdef TIM15_CH2_PA3_AF9
    {PA3, TIM15_BASE_ADDRESS, HAL_LL_TIM_CHANNEL_2, 9, hal_ll_tim_module_num(TIM_MODULE_15)},
    #endif
    #ifdef TIM15_CH2_PB15_AF1
    {PB15, TIM15_BASE_ADDRESS, HAL_LL_TIM_CHANNEL_2, 1, hal_ll_tim_module_num(TIM_MODULE_15)},
    #endif
    #ifdef TIM16_BKIN_PB5_AF1
    // {PB5, TIM16_BASE_ADDRESS, 0, 1, hal_ll_tim_module_num(TIM_MODULE_16)},
    #endif
    #ifdef TIM16_CH1N_PA13_AF1
    {PA13, TIM16_BASE_ADDRESS, HAL_LL_TIM_CHANNEL_1N, 1, hal_ll_tim_module_num(TIM_MODULE_16)},
    #endif
    #ifdef TIM16_CH1N_PB6_AF1
    {PB6, TIM16_BASE_ADDRESS, HAL_LL_TIM_CHANNEL_1N, 1, hal_ll_tim_module_num(TIM_MODULE_16)},
    #endif
    #ifdef TIM16_CH1_PA12_AF1
    {PA12, TIM16_BASE_ADDRESS, HAL_LL_TIM_CHANNEL_1, 1, hal_ll_tim_module_num(TIM_MODULE_16)},
    #endif
    #ifdef TIM16_CH1_PA6_AF1
    {PA6, TIM16_BASE_ADDRESS, HAL_LL_TIM_CHANNEL_1, 1, hal_ll_tim_module_num(TIM_MODULE_16)},
    #endif
    #ifdef TIM16_CH1_PB4_AF1
    {PB4, TIM16_BASE_ADDRESS, HAL_LL_TIM_CHANNEL_1, 1, hal_ll_tim_module_num(TIM_MODULE_16)},
    #endif
    #ifdef TIM16_CH1_PB8_AF1
    {PB8, TIM16_BASE_ADDRESS, HAL_LL_TIM_CHANNEL_1, 1, hal_ll_tim_module_num(TIM_MODULE_16)},
    #endif
    #ifdef TIM17_BKIN_PA10_AF1
    // {PA10, TIM17_BASE_ADDRESS, 0, 1, hal_ll_tim_module_num(TIM_MODULE_17)},
    #endif
    #ifdef TIM17_BKIN_PB4_AF10
    // {PB4, TIM17_BASE_ADDRESS, 0, 10, hal_ll_tim_module_num(TIM_MODULE_17)},
    #endif
    #ifdef TIM17_CH1N_PB7_AF1
    {PB7, TIM17_BASE_ADDRESS, HAL_LL_TIM_CHANNEL_1N, 1, hal_ll_tim_module_num(TIM_MODULE_17)},
    #endif
    #ifdef TIM17_CH1_PA7_AF1
    {PA7, TIM17_BASE_ADDRESS, HAL_LL_TIM_CHANNEL_1, 1, hal_ll_tim_module_num(TIM_MODULE_17)},
    #endif
    #ifdef TIM17_CH1_PB5_AF10
    {PB5, TIM17_BASE_ADDRESS, HAL_LL_TIM_CHANNEL_1, 10, hal_ll_tim_module_num(TIM_MODULE_17)},
    #endif
    #ifdef TIM17_CH1_PB9_AF1
    {PB9, TIM17_BASE_ADDRESS, HAL_LL_TIM_CHANNEL_1, 1, hal_ll_tim_module_num(TIM_MODULE_17)},
    #endif
    #ifdef TIM1_BKIN2_PA11_AF12
    // {PA11, TIM1_BASE_ADDRESS, 0, 12, hal_ll_tim_module_num(TIM_MODULE_1)},
    #endif
    #ifdef TIM1_BKIN2_PC3_AF6
    // {PC3, TIM1_BASE_ADDRESS, 0, 6, hal_ll_tim_module_num(TIM_MODULE_1)},
    #endif
    #ifdef TIM1_BKIN2_PE14_AF6
    // {PE14, TIM1_BASE_ADDRESS, 0, 6, hal_ll_tim_module_num(TIM_MODULE_1)},
    #endif
    #ifdef TIM1_BKIN_PA14_AF6
    // {PA14, TIM1_BASE_ADDRESS, 0, 6, hal_ll_tim_module_num(TIM_MODULE_1)},
    #endif
    #ifdef TIM1_BKIN_PA15_AF9
    // {PA15, TIM1_BASE_ADDRESS, 0, 9, hal_ll_tim_module_num(TIM_MODULE_1)},
    #endif
    #ifdef TIM1_BKIN_PA6_AF6
    // {PA6, TIM1_BASE_ADDRESS, 0, 6, hal_ll_tim_module_num(TIM_MODULE_1)},
    #endif
    #ifdef TIM1_BKIN_PB10_AF12
    // {PB10, TIM1_BASE_ADDRESS, 0, 12, hal_ll_tim_module_num(TIM_MODULE_1)},
    #endif
    #ifdef TIM1_BKIN_PB12_AF6
    // {PB12, TIM1_BASE_ADDRESS, 0, 6, hal_ll_tim_module_num(TIM_MODULE_1)},
    #endif
    #ifdef TIM1_BKIN_PB8_AF12
    // {PB8, TIM1_BASE_ADDRESS, 0, 12, hal_ll_tim_module_num(TIM_MODULE_1)},
    #endif
    #ifdef TIM1_BKIN_PC13_AF2
    // {PC13, TIM1_BASE_ADDRESS, 0, 2, hal_ll_tim_module_num(TIM_MODULE_1)},
    #endif
    #ifdef TIM1_BKIN_PE15_AF2
    // {PE15, TIM1_BASE_ADDRESS, 0, 2, hal_ll_tim_module_num(TIM_MODULE_1)},
    #endif
    #ifdef TIM1_CH1N_PA11_AF6
    {PA11, TIM1_BASE_ADDRESS, HAL_LL_TIM_CHANNEL_1N, 6, hal_ll_tim_module_num(TIM_MODULE_1)},
    #endif
    #ifdef TIM1_CH1N_PA7_AF6
    {PA7, TIM1_BASE_ADDRESS, HAL_LL_TIM_CHANNEL_1N, 6, hal_ll_tim_module_num(TIM_MODULE_1)},
    #endif
    #ifdef TIM1_CH1N_PB13_AF6
    {PB13, TIM1_BASE_ADDRESS, HAL_LL_TIM_CHANNEL_1N, 6, hal_ll_tim_module_num(TIM_MODULE_1)},
    #endif
    #ifdef TIM1_CH1N_PC13_AF4
    {PC13, TIM1_BASE_ADDRESS, HAL_LL_TIM_CHANNEL_1N, 4, hal_ll_tim_module_num(TIM_MODULE_1)},
    #endif
    #ifdef TIM1_CH1N_PE8_AF2
    {PE8, TIM1_BASE_ADDRESS, HAL_LL_TIM_CHANNEL_1N, 2, hal_ll_tim_module_num(TIM_MODULE_1)},
    #endif
    #ifdef TIM1_CH1_PA8_AF6
    {PA8, TIM1_BASE_ADDRESS, HAL_LL_TIM_CHANNEL_1, 6, hal_ll_tim_module_num(TIM_MODULE_1)},
    #endif
    #ifdef TIM1_CH1_PC0_AF2
    {PC0, TIM1_BASE_ADDRESS, HAL_LL_TIM_CHANNEL_1, 2, hal_ll_tim_module_num(TIM_MODULE_1)},
    #endif
    #ifdef TIM1_CH1_PE9_AF2
    {PE9, TIM1_BASE_ADDRESS, HAL_LL_TIM_CHANNEL_1, 2, hal_ll_tim_module_num(TIM_MODULE_1)},
    #endif
    #ifdef TIM1_CH2N_PA12_AF6
    {PA12, TIM1_BASE_ADDRESS, HAL_LL_TIM_CHANNEL_2N, 6, hal_ll_tim_module_num(TIM_MODULE_1)},
    #endif
    #ifdef TIM1_CH2N_PB0_AF6
    {PB0, TIM1_BASE_ADDRESS, HAL_LL_TIM_CHANNEL_2N, 6, hal_ll_tim_module_num(TIM_MODULE_1)},
    #endif
    #ifdef TIM1_CH2N_PB14_AF6
    {PB14, TIM1_BASE_ADDRESS, HAL_LL_TIM_CHANNEL_2N, 6, hal_ll_tim_module_num(TIM_MODULE_1)},
    #endif
    #ifdef TIM1_CH2N_PE10_AF2
    {PE10, TIM1_BASE_ADDRESS, HAL_LL_TIM_CHANNEL_2N, 2, hal_ll_tim_module_num(TIM_MODULE_1)},
    #endif
    #ifdef TIM1_CH2_PA9_AF6
    {PA9, TIM1_BASE_ADDRESS, HAL_LL_TIM_CHANNEL_2, 6, hal_ll_tim_module_num(TIM_MODULE_1)},
    #endif
    #ifdef TIM1_CH2_PC1_AF2
    {PC1, TIM1_BASE_ADDRESS, HAL_LL_TIM_CHANNEL_2, 2, hal_ll_tim_module_num(TIM_MODULE_1)},
    #endif
    #ifdef TIM1_CH2_PE11_AF2
    {PE11, TIM1_BASE_ADDRESS, HAL_LL_TIM_CHANNEL_2, 2, hal_ll_tim_module_num(TIM_MODULE_1)},
    #endif
    #ifdef TIM1_CH3N_PB15_AF4
    {PB15, TIM1_BASE_ADDRESS, HAL_LL_TIM_CHANNEL_3N, 4, hal_ll_tim_module_num(TIM_MODULE_1)},
    #endif
    #ifdef TIM1_CH3N_PB1_AF6
    {PB1, TIM1_BASE_ADDRESS, HAL_LL_TIM_CHANNEL_3N, 6, hal_ll_tim_module_num(TIM_MODULE_1)},
    #endif
    #ifdef TIM1_CH3N_PB9_AF12
    {PB9, TIM1_BASE_ADDRESS, HAL_LL_TIM_CHANNEL_3N, 12, hal_ll_tim_module_num(TIM_MODULE_1)},
    #endif
    #ifdef TIM1_CH3N_PE12_AF2
    {PE12, TIM1_BASE_ADDRESS, HAL_LL_TIM_CHANNEL_3N, 2, hal_ll_tim_module_num(TIM_MODULE_1)},
    #endif
    #ifdef TIM1_CH3N_PF0_AF6
    {PF0, TIM1_BASE_ADDRESS, HAL_LL_TIM_CHANNEL_3N, 6, hal_ll_tim_module_num(TIM_MODULE_1)},
    #endif
    #ifdef TIM1_CH3_PA10_AF6
    {PA10, TIM1_BASE_ADDRESS, HAL_LL_TIM_CHANNEL_3, 6, hal_ll_tim_module_num(TIM_MODULE_1)},
    #endif
    #ifdef TIM1_CH3_PC2_AF2
    {PC2, TIM1_BASE_ADDRESS, HAL_LL_TIM_CHANNEL_3, 2, hal_ll_tim_module_num(TIM_MODULE_1)},
    #endif
    #ifdef TIM1_CH3_PE13_AF2
    {PE13, TIM1_BASE_ADDRESS, HAL_LL_TIM_CHANNEL_3, 2, hal_ll_tim_module_num(TIM_MODULE_1)},
    #endif
    #ifdef TIM1_CH4N_PC5_AF6
    {PC5, TIM1_BASE_ADDRESS, HAL_LL_TIM_CHANNEL_4N, 6, hal_ll_tim_module_num(TIM_MODULE_1)},
    #endif
    #ifdef TIM1_CH4N_PE15_AF6
    {PE15, TIM1_BASE_ADDRESS, HAL_LL_TIM_CHANNEL_4N, 6, hal_ll_tim_module_num(TIM_MODULE_1)},
    #endif
    #ifdef TIM1_CH4_PA11_AF11
    {PA11, TIM1_BASE_ADDRESS, HAL_LL_TIM_CHANNEL_4, 11, hal_ll_tim_module_num(TIM_MODULE_1)},
    #endif
    #ifdef TIM1_CH4_PC3_AF2
    {PC3, TIM1_BASE_ADDRESS, HAL_LL_TIM_CHANNEL_4, 2, hal_ll_tim_module_num(TIM_MODULE_1)},
    #endif
    #ifdef TIM1_CH4_PE14_AF2
    {PE14, TIM1_BASE_ADDRESS, HAL_LL_TIM_CHANNEL_4, 2, hal_ll_tim_module_num(TIM_MODULE_1)},
    #endif
    #ifdef TIM1_ETR_PA12_AF11
    // {PA12, TIM1_BASE_ADDRESS, 0, 11, hal_ll_tim_module_num(TIM_MODULE_1)},
    #endif
    #ifdef TIM1_ETR_PC4_AF2
    // {PC4, TIM1_BASE_ADDRESS, 0, 2, hal_ll_tim_module_num(TIM_MODULE_1)},
    #endif
    #ifdef TIM1_ETR_PE7_AF2
    // {PE7, TIM1_BASE_ADDRESS, 0, 2, hal_ll_tim_module_num(TIM_MODULE_1)},
    #endif
    #ifdef TIM20_CH1_PB2_AF3
    {PB2, TIM20_BASE_ADDRESS, HAL_LL_TIM_CHANNEL_1, 3, hal_ll_tim_module_num(TIM_MODULE_20)},
    #endif
    #ifdef TIM20_CH2_PC2_AF6
    {PC2, TIM20_BASE_ADDRESS, HAL_LL_TIM_CHANNEL_2, 6, hal_ll_tim_module_num(TIM_MODULE_20)},
    #endif
    #ifdef TIM20_CH3_PC8_AF6
    {PC8, TIM20_BASE_ADDRESS, HAL_LL_TIM_CHANNEL_3, 6, hal_ll_tim_module_num(TIM_MODULE_20)},
    #endif
    #ifdef TIM20_ETR_PA15_AF3
    // {PA15, TIM20_BASE_ADDRESS, 0, 3, hal_ll_tim_module_num(TIM_MODULE_20)},
    #endif
    #ifdef TIM2_CH1_PA0_AF1
    {PA0, TIM2_BASE_ADDRESS, HAL_LL_TIM_CHANNEL_1, 1, hal_ll_tim_module_num(TIM_MODULE_2)},
    #endif
    #ifdef TIM2_CH1_PA15_AF1
    {PA15, TIM2_BASE_ADDRESS, HAL_LL_TIM_CHANNEL_1, 1, hal_ll_tim_module_num(TIM_MODULE_2)},
    #endif
    #ifdef TIM2_CH1_PA5_AF1
    {PA5, TIM2_BASE_ADDRESS, HAL_LL_TIM_CHANNEL_1, 1, hal_ll_tim_module_num(TIM_MODULE_2)},
    #endif
    #ifdef TIM2_CH2_PA1_AF1
    {PA1, TIM2_BASE_ADDRESS, HAL_LL_TIM_CHANNEL_2, 1, hal_ll_tim_module_num(TIM_MODULE_2)},
    #endif
    #ifdef TIM2_CH2_PB3_AF1
    {PB3, TIM2_BASE_ADDRESS, HAL_LL_TIM_CHANNEL_2, 1, hal_ll_tim_module_num(TIM_MODULE_2)},
    #endif
    #ifdef TIM2_CH3_PA2_AF1
    {PA2, TIM2_BASE_ADDRESS, HAL_LL_TIM_CHANNEL_3, 1, hal_ll_tim_module_num(TIM_MODULE_2)},
    #endif
    #ifdef TIM2_CH3_PA9_AF10
    {PA9, TIM2_BASE_ADDRESS, HAL_LL_TIM_CHANNEL_3, 10, hal_ll_tim_module_num(TIM_MODULE_2)},
    #endif
    #ifdef TIM2_CH3_PB10_AF1
    {PB10, TIM2_BASE_ADDRESS, HAL_LL_TIM_CHANNEL_3, 1, hal_ll_tim_module_num(TIM_MODULE_2)},
    #endif
    #ifdef TIM2_CH4_PA10_AF10
    {PA10, TIM2_BASE_ADDRESS, HAL_LL_TIM_CHANNEL_4, 10, hal_ll_tim_module_num(TIM_MODULE_2)},
    #endif
    #ifdef TIM2_CH4_PA3_AF1
    {PA3, TIM2_BASE_ADDRESS, HAL_LL_TIM_CHANNEL_4, 1, hal_ll_tim_module_num(TIM_MODULE_2)},
    #endif
    #ifdef TIM2_CH4_PB11_AF1
    {PB11, TIM2_BASE_ADDRESS, HAL_LL_TIM_CHANNEL_4, 1, hal_ll_tim_module_num(TIM_MODULE_2)},
    #endif
    #ifdef TIM2_ETR_PA0_AF14
    // {PA0, TIM2_BASE_ADDRESS, 0, 14, hal_ll_tim_module_num(TIM_MODULE_2)},
    #endif
    #ifdef TIM2_ETR_PA15_AF14
    // {PA15, TIM2_BASE_ADDRESS, 0, 14, hal_ll_tim_module_num(TIM_MODULE_2)},
    #endif
    #ifdef TIM2_ETR_PA5_AF2
    // {PA5, TIM2_BASE_ADDRESS, 0, 2, hal_ll_tim_module_num(TIM_MODULE_2)},
    #endif
    #ifdef TIM3_CH1_PA6_AF2
    {PA6, TIM3_BASE_ADDRESS, HAL_LL_TIM_CHANNEL_1, 2, hal_ll_tim_module_num(TIM_MODULE_3)},
    #endif
    #ifdef TIM3_CH1_PB4_AF2
    {PB4, TIM3_BASE_ADDRESS, HAL_LL_TIM_CHANNEL_1, 2, hal_ll_tim_module_num(TIM_MODULE_3)},
    #endif
    #ifdef TIM3_CH1_PC6_AF2
    {PC6, TIM3_BASE_ADDRESS, HAL_LL_TIM_CHANNEL_1, 2, hal_ll_tim_module_num(TIM_MODULE_3)},
    #endif
    #ifdef TIM3_CH2_PA4_AF2
    {PA4, TIM3_BASE_ADDRESS, HAL_LL_TIM_CHANNEL_2, 2, hal_ll_tim_module_num(TIM_MODULE_3)},
    #endif
    #ifdef TIM3_CH2_PA7_AF2
    {PA7, TIM3_BASE_ADDRESS, HAL_LL_TIM_CHANNEL_2, 2, hal_ll_tim_module_num(TIM_MODULE_3)},
    #endif
    #ifdef TIM3_CH2_PB5_AF2
    {PB5, TIM3_BASE_ADDRESS, HAL_LL_TIM_CHANNEL_2, 2, hal_ll_tim_module_num(TIM_MODULE_3)},
    #endif
    #ifdef TIM3_CH2_PC7_AF2
    {PC7, TIM3_BASE_ADDRESS, HAL_LL_TIM_CHANNEL_2, 2, hal_ll_tim_module_num(TIM_MODULE_3)},
    #endif
    #ifdef TIM3_CH3_PB0_AF2
    {PB0, TIM3_BASE_ADDRESS, HAL_LL_TIM_CHANNEL_3, 2, hal_ll_tim_module_num(TIM_MODULE_3)},
    #endif
    #ifdef TIM3_CH3_PC8_AF2
    {PC8, TIM3_BASE_ADDRESS, HAL_LL_TIM_CHANNEL_3, 2, hal_ll_tim_module_num(TIM_MODULE_3)},
    #endif
    #ifdef TIM3_CH4_PB1_AF2
    {PB1, TIM3_BASE_ADDRESS, HAL_LL_TIM_CHANNEL_4, 2, hal_ll_tim_module_num(TIM_MODULE_3)},
    #endif
    #ifdef TIM3_CH4_PB7_AF10
    {PB7, TIM3_BASE_ADDRESS, HAL_LL_TIM_CHANNEL_4, 10, hal_ll_tim_module_num(TIM_MODULE_3)},
    #endif
    #ifdef TIM3_CH4_PC9_AF2
    {PC9, TIM3_BASE_ADDRESS, HAL_LL_TIM_CHANNEL_4, 2, hal_ll_tim_module_num(TIM_MODULE_3)},
    #endif
    #ifdef TIM3_ETR_PB3_AF10
    // {PB3, TIM3_BASE_ADDRESS, 0, 10, hal_ll_tim_module_num(TIM_MODULE_3)},
    #endif
    #ifdef TIM3_ETR_PD2_AF2
    // {PD2, TIM3_BASE_ADDRESS, 0, 2, hal_ll_tim_module_num(TIM_MODULE_3)},
    #endif
    #ifdef TIM4_CH1_PA11_AF10
    {PA11, TIM4_BASE_ADDRESS, HAL_LL_TIM_CHANNEL_1, 10, hal_ll_tim_module_num(TIM_MODULE_4)},
    #endif
    #ifdef TIM4_CH1_PB6_AF2
    {PB6, TIM4_BASE_ADDRESS, HAL_LL_TIM_CHANNEL_1, 2, hal_ll_tim_module_num(TIM_MODULE_4)},
    #endif
    #ifdef TIM4_CH2_PA12_AF10
    {PA12, TIM4_BASE_ADDRESS, HAL_LL_TIM_CHANNEL_2, 10, hal_ll_tim_module_num(TIM_MODULE_4)},
    #endif
    #ifdef TIM4_CH2_PB7_AF2
    {PB7, TIM4_BASE_ADDRESS, HAL_LL_TIM_CHANNEL_2, 2, hal_ll_tim_module_num(TIM_MODULE_4)},
    #endif
    #ifdef TIM4_CH3_PA13_AF10
    {PA13, TIM4_BASE_ADDRESS, HAL_LL_TIM_CHANNEL_3, 10, hal_ll_tim_module_num(TIM_MODULE_4)},
    #endif
    #ifdef TIM4_CH3_PB8_AF2
    {PB8, TIM4_BASE_ADDRESS, HAL_LL_TIM_CHANNEL_3, 2, hal_ll_tim_module_num(TIM_MODULE_4)},
    #endif
    #ifdef TIM4_CH4_PB9_AF2
    {PB9, TIM4_BASE_ADDRESS, HAL_LL_TIM_CHANNEL_4, 2, hal_ll_tim_module_num(TIM_MODULE_4)},
    #endif
    #ifdef TIM4_ETR_PA8_AF10
    // {PA8, TIM4_BASE_ADDRESS, 0, 10, hal_ll_tim_module_num(TIM_MODULE_4)},
    #endif
    #ifdef TIM4_ETR_PB3_AF2
    // {PB3, TIM4_BASE_ADDRESS, 0, 2, hal_ll_tim_module_num(TIM_MODULE_4)},
    #endif
    #ifdef TIM8_BKIN2_PB6_AF10
    // {PB6, TIM8_BASE_ADDRESS, 0, 10, hal_ll_tim_module_num(TIM_MODULE_8)},
    #endif
    #ifdef TIM8_BKIN2_PC9_AF6
    // {PC9, TIM8_BASE_ADDRESS, 0, 6, hal_ll_tim_module_num(TIM_MODULE_8)},
    #endif
    #ifdef TIM8_BKIN2_PD1_AF6
    // {PD1, TIM8_BASE_ADDRESS, 0, 6, hal_ll_tim_module_num(TIM_MODULE_8)},
    #endif
    #ifdef TIM8_BKIN_PA0_AF9
    // {PA0, TIM8_BASE_ADDRESS, 0, 9, hal_ll_tim_module_num(TIM_MODULE_8)},
    #endif
    #ifdef TIM8_BKIN_PA10_AF11
    // {PA10, TIM8_BASE_ADDRESS, 0, 11, hal_ll_tim_module_num(TIM_MODULE_8)},
    #endif
    #ifdef TIM8_BKIN_PA6_AF4
    // {PA6, TIM8_BASE_ADDRESS, 0, 4, hal_ll_tim_module_num(TIM_MODULE_8)},
    #endif
    #ifdef TIM8_BKIN_PB7_AF5
    // {PB7, TIM8_BASE_ADDRESS, 0, 5, hal_ll_tim_module_num(TIM_MODULE_8)},
    #endif
    #ifdef TIM8_BKIN_PD2_AF4
    // {PD2, TIM8_BASE_ADDRESS, 0, 4, hal_ll_tim_module_num(TIM_MODULE_8)},
    #endif
    #ifdef TIM8_CH1N_PA7_AF4
    {PA7, TIM8_BASE_ADDRESS, HAL_LL_TIM_CHANNEL_1N, 4, hal_ll_tim_module_num(TIM_MODULE_8)},
    #endif
    #ifdef TIM8_CH1N_PB3_AF4
    {PB3, TIM8_BASE_ADDRESS, HAL_LL_TIM_CHANNEL_1N, 4, hal_ll_tim_module_num(TIM_MODULE_8)},
    #endif
    #ifdef TIM8_CH1N_PC10_AF4
    {PC10, TIM8_BASE_ADDRESS, HAL_LL_TIM_CHANNEL_1N, 4, hal_ll_tim_module_num(TIM_MODULE_8)},
    #endif
    #ifdef TIM8_CH1_PA15_AF2
    {PA15, TIM8_BASE_ADDRESS, HAL_LL_TIM_CHANNEL_1, 2, hal_ll_tim_module_num(TIM_MODULE_8)},
    #endif
    #ifdef TIM8_CH1_PB6_AF5
    {PB6, TIM8_BASE_ADDRESS, HAL_LL_TIM_CHANNEL_1, 5, hal_ll_tim_module_num(TIM_MODULE_8)},
    #endif
    #ifdef TIM8_CH1_PC6_AF4
    {PC6, TIM8_BASE_ADDRESS, HAL_LL_TIM_CHANNEL_1, 4, hal_ll_tim_module_num(TIM_MODULE_8)},
    #endif
    #ifdef TIM8_CH2N_PB0_AF4
    {PB0, TIM8_BASE_ADDRESS, HAL_LL_TIM_CHANNEL_2N, 4, hal_ll_tim_module_num(TIM_MODULE_8)},
    #endif
    #ifdef TIM8_CH2N_PB4_AF4
    {PB4, TIM8_BASE_ADDRESS, HAL_LL_TIM_CHANNEL_2N, 4, hal_ll_tim_module_num(TIM_MODULE_8)},
    #endif
    #ifdef TIM8_CH2N_PC11_AF4
    {PC11, TIM8_BASE_ADDRESS, HAL_LL_TIM_CHANNEL_2N, 4, hal_ll_tim_module_num(TIM_MODULE_8)},
    #endif
    #ifdef TIM8_CH2_PA14_AF5
    {PA14, TIM8_BASE_ADDRESS, HAL_LL_TIM_CHANNEL_2, 5, hal_ll_tim_module_num(TIM_MODULE_8)},
    #endif
    #ifdef TIM8_CH2_PB8_AF10
    {PB8, TIM8_BASE_ADDRESS, HAL_LL_TIM_CHANNEL_2, 10, hal_ll_tim_module_num(TIM_MODULE_8)},
    #endif
    #ifdef TIM8_CH2_PC7_AF4
    {PC7, TIM8_BASE_ADDRESS, HAL_LL_TIM_CHANNEL_2, 4, hal_ll_tim_module_num(TIM_MODULE_8)},
    #endif
    #ifdef TIM8_CH3N_PB1_AF4
    {PB1, TIM8_BASE_ADDRESS, HAL_LL_TIM_CHANNEL_3N, 4, hal_ll_tim_module_num(TIM_MODULE_8)},
    #endif
    #ifdef TIM8_CH3N_PB5_AF3
    {PB5, TIM8_BASE_ADDRESS, HAL_LL_TIM_CHANNEL_3N, 3, hal_ll_tim_module_num(TIM_MODULE_8)},
    #endif
    #ifdef TIM8_CH3N_PC12_AF4
    {PC12, TIM8_BASE_ADDRESS, HAL_LL_TIM_CHANNEL_3N, 4, hal_ll_tim_module_num(TIM_MODULE_8)},
    #endif
    #ifdef TIM8_CH3_PB9_AF10
    {PB9, TIM8_BASE_ADDRESS, HAL_LL_TIM_CHANNEL_3, 10, hal_ll_tim_module_num(TIM_MODULE_8)},
    #endif
    #ifdef TIM8_CH3_PC8_AF4
    {PC8, TIM8_BASE_ADDRESS, HAL_LL_TIM_CHANNEL_3, 4, hal_ll_tim_module_num(TIM_MODULE_8)},
    #endif
    #ifdef TIM8_CH4N_PC13_AF6
    {PC13, TIM8_BASE_ADDRESS, HAL_LL_TIM_CHANNEL_4N, 6, hal_ll_tim_module_num(TIM_MODULE_8)},
    #endif
    #ifdef TIM8_CH4N_PD0_AF6
    {PD0, TIM8_BASE_ADDRESS, HAL_LL_TIM_CHANNEL_4N, 6, hal_ll_tim_module_num(TIM_MODULE_8)},
    #endif
    #ifdef TIM8_CH4_PC9_AF4
    {PC9, TIM8_BASE_ADDRESS, HAL_LL_TIM_CHANNEL_4, 4, hal_ll_tim_module_num(TIM_MODULE_8)},
    #endif
    #ifdef TIM8_CH4_PD1_AF4
    {PD1, TIM8_BASE_ADDRESS, HAL_LL_TIM_CHANNEL_4, 4, hal_ll_tim_module_num(TIM_MODULE_8)},
    #endif
    #ifdef TIM8_ETR_PA0_AF10
    // {PA0, TIM8_BASE_ADDRESS, 0, 10, hal_ll_tim_module_num(TIM_MODULE_8)},
    #endif
    #ifdef TIM8_ETR_PB6_AF6
    // {PB6, TIM8_BASE_ADDRESS, 0, 6, hal_ll_tim_module_num(TIM_MODULE_8)},
    #endif
    #ifdef TIM15_CH1_PF9_AF3
    {PF9, TIM15_BASE_ADDRESS, HAL_LL_TIM_CHANNEL_1, 3, hal_ll_tim_module_num(TIM_MODULE_15)},
    #endif
    #ifdef TIM15_CH2_PF10_AF3
    {PF10, TIM15_BASE_ADDRESS, HAL_LL_TIM_CHANNEL_2, 3, hal_ll_tim_module_num(TIM_MODULE_15)},
    #endif
    #ifdef TIM16_CH1_PE0_AF4
    {PE0, TIM16_BASE_ADDRESS, HAL_LL_TIM_CHANNEL_1, 4, hal_ll_tim_module_num(TIM_MODULE_16)},
    #endif
    #ifdef TIM17_CH1_PE1_AF4
    {PE1, TIM17_BASE_ADDRESS, HAL_LL_TIM_CHANNEL_1, 4, hal_ll_tim_module_num(TIM_MODULE_17)},
    #endif
    #ifdef TIM20_BKIN2_PF10_AF2
    // {PF10, TIM20_BASE_ADDRESS, 0, 2, hal_ll_tim_module_num(TIM_MODULE_20)},
    #endif
    #ifdef TIM20_BKIN_PF9_AF2
    // {PF9, TIM20_BASE_ADDRESS, 0, 2, hal_ll_tim_module_num(TIM_MODULE_20)},
    #endif
    #ifdef TIM20_CH1N_PE4_AF6
    {PE4, TIM20_BASE_ADDRESS, HAL_LL_TIM_CHANNEL_1N, 6, hal_ll_tim_module_num(TIM_MODULE_20)},
    #endif
    #ifdef TIM20_CH1_PE2_AF6
    {PE2, TIM20_BASE_ADDRESS, HAL_LL_TIM_CHANNEL_1, 6, hal_ll_tim_module_num(TIM_MODULE_20)},
    #endif
    #ifdef TIM20_CH2N_PE5_AF6
    {PE5, TIM20_BASE_ADDRESS, HAL_LL_TIM_CHANNEL_2N, 6, hal_ll_tim_module_num(TIM_MODULE_20)},
    #endif
    #ifdef TIM20_CH2_PE3_AF6
    {PE3, TIM20_BASE_ADDRESS, HAL_LL_TIM_CHANNEL_2, 6, hal_ll_tim_module_num(TIM_MODULE_20)},
    #endif
    #ifdef TIM20_CH3N_PE6_AF6
    {PE6, TIM20_BASE_ADDRESS, HAL_LL_TIM_CHANNEL_3N, 6, hal_ll_tim_module_num(TIM_MODULE_20)},
    #endif
    #ifdef TIM20_CH3_PF2_AF2
    {PF2, TIM20_BASE_ADDRESS, HAL_LL_TIM_CHANNEL_3, 2, hal_ll_tim_module_num(TIM_MODULE_20)},
    #endif
    #ifdef TIM20_CH4N_PE0_AF3
    {PE0, TIM20_BASE_ADDRESS, HAL_LL_TIM_CHANNEL_4N, 3, hal_ll_tim_module_num(TIM_MODULE_20)},
    #endif
    #ifdef TIM20_CH4_PE1_AF6
    {PE1, TIM20_BASE_ADDRESS, HAL_LL_TIM_CHANNEL_4, 6, hal_ll_tim_module_num(TIM_MODULE_20)},
    #endif
    #ifdef TIM20_ETR_PE0_AF6
    // {PE0, TIM20_BASE_ADDRESS, 0, 6, hal_ll_tim_module_num(TIM_MODULE_20)},
    #endif
    #ifdef TIM2_CH1_PD3_AF2
    {PD3, TIM2_BASE_ADDRESS, HAL_LL_TIM_CHANNEL_1, 2, hal_ll_tim_module_num(TIM_MODULE_2)},
    #endif
    #ifdef TIM2_CH2_PD4_AF2
    {PD4, TIM2_BASE_ADDRESS, HAL_LL_TIM_CHANNEL_2, 2, hal_ll_tim_module_num(TIM_MODULE_2)},
    #endif
    #ifdef TIM2_CH3_PD7_AF2
    {PD7, TIM2_BASE_ADDRESS, HAL_LL_TIM_CHANNEL_3, 2, hal_ll_tim_module_num(TIM_MODULE_2)},
    #endif
    #ifdef TIM2_CH4_PD6_AF2
    {PD6, TIM2_BASE_ADDRESS, HAL_LL_TIM_CHANNEL_4, 2, hal_ll_tim_module_num(TIM_MODULE_2)},
    #endif
    #ifdef TIM2_ETR_PD3_AF2
    // {PD3, TIM2_BASE_ADDRESS, 0, 2, hal_ll_tim_module_num(TIM_MODULE_2)},
    #endif
    #ifdef TIM3_CH1_PE2_AF2
    {PE2, TIM3_BASE_ADDRESS, HAL_LL_TIM_CHANNEL_1, 2, hal_ll_tim_module_num(TIM_MODULE_3)},
    #endif
    #ifdef TIM3_CH2_PE3_AF2
    {PE3, TIM3_BASE_ADDRESS, HAL_LL_TIM_CHANNEL_2, 2, hal_ll_tim_module_num(TIM_MODULE_3)},
    #endif
    #ifdef TIM3_CH3_PE4_AF2
    {PE4, TIM3_BASE_ADDRESS, HAL_LL_TIM_CHANNEL_3, 2, hal_ll_tim_module_num(TIM_MODULE_3)},
    #endif
    #ifdef TIM3_CH4_PE5_AF2
    {PE5, TIM3_BASE_ADDRESS, HAL_LL_TIM_CHANNEL_4, 2, hal_ll_tim_module_num(TIM_MODULE_3)},
    #endif
    #ifdef TIM4_CH1_PD12_AF2
    {PD12, TIM4_BASE_ADDRESS, HAL_LL_TIM_CHANNEL_1, 2, hal_ll_tim_module_num(TIM_MODULE_4)},
    #endif
    #ifdef TIM4_CH2_PD13_AF2
    {PD13, TIM4_BASE_ADDRESS, HAL_LL_TIM_CHANNEL_2, 2, hal_ll_tim_module_num(TIM_MODULE_4)},
    #endif
    #ifdef TIM4_CH3_PD14_AF2
    {PD14, TIM4_BASE_ADDRESS, HAL_LL_TIM_CHANNEL_3, 2, hal_ll_tim_module_num(TIM_MODULE_4)},
    #endif
    #ifdef TIM4_CH4_PD15_AF2
    {PD15, TIM4_BASE_ADDRESS, HAL_LL_TIM_CHANNEL_4, 2, hal_ll_tim_module_num(TIM_MODULE_4)},
    #endif
    #ifdef TIM4_ETR_PE0_AF2
    // {PE0, TIM4_BASE_ADDRESS, 0, 2, hal_ll_tim_module_num(TIM_MODULE_4)},
    #endif
    { HAL_LL_PIN_NC, HAL_LL_MODULE_ERROR, HAL_LL_CHANNEL_ERROR, HAL_LL_PIN_NC, HAL_LL_PIN_NC }
};

#ifdef __cplusplus
}
#endif

#endif // _HAL_LL_TIM_PIN_MAP_H_
// ------------------------------------------------------------------------- END
