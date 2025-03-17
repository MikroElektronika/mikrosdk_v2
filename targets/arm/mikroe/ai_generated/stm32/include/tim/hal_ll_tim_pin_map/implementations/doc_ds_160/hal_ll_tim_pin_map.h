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
#ifdef TIM_MODULE_5
#define TIM5_BASE_ADDRESS (0x40000C00UL)
#define TIM5_BASE_ADDR TIM5_BASE_ADDRESS
#define HAL_LL_TIM5_BASE_ADDR TIM5_BASE_ADDRESS
#define HAL_LL_TIM5_BASE_ADDRESS TIM5_BASE_ADDRESS
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

/*!< @brief TIM pins. */
static const hal_ll_tim_pin_map_t _tim_map[] = {
    #ifdef LPTIM1_ETR_PB6_AF1
    // {GPIO_PB6, LPTIM1_BASE_ADDRESS, 0, 1, hal_ll_lptim_module_num(LPTIM_MODULE_1)},
    #endif
    #ifdef LPTIM1_ETR_PC3_AF1
    // {GPIO_PC3, LPTIM1_BASE_ADDRESS, 0, 1, hal_ll_lptim_module_num(LPTIM_MODULE_1)},
    #endif
    #ifdef LPTIM1_ETR_PG12_AF1
    // {GPIO_PG12, LPTIM1_BASE_ADDRESS, 0, 1, hal_ll_lptim_module_num(LPTIM_MODULE_1)},
    #endif
    #ifdef LPTIM2_ETR_PA5_AF14
    // {GPIO_PA5, LPTIM2_BASE_ADDRESS, 0, 14, hal_ll_lptim_module_num(LPTIM_MODULE_2)},
    #endif
    #ifdef LPTIM2_ETR_PC3_AF14
    // {GPIO_PC3, LPTIM2_BASE_ADDRESS, 0, 14, hal_ll_lptim_module_num(LPTIM_MODULE_2)},
    #endif
    #ifdef LPTIM2_ETR_PD11_AF14
    // {GPIO_PD11, LPTIM2_BASE_ADDRESS, 0, 14, hal_ll_lptim_module_num(LPTIM_MODULE_2)},
    #endif
    #ifdef TIM15_BKIN_PA9_AF14
    // {GPIO_PA9, TIM15_BASE_ADDRESS, 0, 14, hal_ll_tim_module_num(TIM_MODULE_15)},
    #endif
    #ifdef TIM15_BKIN_PB12_AF14
    // {GPIO_PB12, TIM15_BASE_ADDRESS, 0, 14, hal_ll_tim_module_num(TIM_MODULE_15)},
    #endif
    #ifdef TIM15_CH1N_PA1_AF14
    {GPIO_PA1, TIM15_BASE_ADDRESS, HAL_LL_TIM_CHANNEL_1N, 14, hal_ll_tim_module_num(TIM_MODULE_15)},
    #endif
    #ifdef TIM15_CH1N_PB13_AF14
    {GPIO_PB13, TIM15_BASE_ADDRESS, HAL_LL_TIM_CHANNEL_1N, 14, hal_ll_tim_module_num(TIM_MODULE_15)},
    #endif
    #ifdef TIM15_CH1N_PG9_AF14
    {GPIO_PG9, TIM15_BASE_ADDRESS, HAL_LL_TIM_CHANNEL_1N, 14, hal_ll_tim_module_num(TIM_MODULE_15)},
    #endif
    #ifdef TIM15_CH1_PA2_AF14
    {GPIO_PA2, TIM15_BASE_ADDRESS, HAL_LL_TIM_CHANNEL_1, 14, hal_ll_tim_module_num(TIM_MODULE_15)},
    #endif
    #ifdef TIM15_CH1_PB14_AF14
    {GPIO_PB14, TIM15_BASE_ADDRESS, HAL_LL_TIM_CHANNEL_1, 14, hal_ll_tim_module_num(TIM_MODULE_15)},
    #endif
    #ifdef TIM15_CH1_PF9_AF14
    {GPIO_PF9, TIM15_BASE_ADDRESS, HAL_LL_TIM_CHANNEL_1, 14, hal_ll_tim_module_num(TIM_MODULE_15)},
    #endif
    #ifdef TIM15_CH1_PG10_AF14
    {GPIO_PG10, TIM15_BASE_ADDRESS, HAL_LL_TIM_CHANNEL_1, 14, hal_ll_tim_module_num(TIM_MODULE_15)},
    #endif
    #ifdef TIM15_CH2_PA3_AF14
    {GPIO_PA3, TIM15_BASE_ADDRESS, HAL_LL_TIM_CHANNEL_2, 14, hal_ll_tim_module_num(TIM_MODULE_15)},
    #endif
    #ifdef TIM15_CH2_PB15_AF14
    {GPIO_PB15, TIM15_BASE_ADDRESS, HAL_LL_TIM_CHANNEL_2, 14, hal_ll_tim_module_num(TIM_MODULE_15)},
    #endif
    #ifdef TIM15_CH2_PF10_AF14
    {GPIO_PF10, TIM15_BASE_ADDRESS, HAL_LL_TIM_CHANNEL_2, 14, hal_ll_tim_module_num(TIM_MODULE_15)},
    #endif
    #ifdef TIM15_CH2_PG11_AF14
    {GPIO_PG11, TIM15_BASE_ADDRESS, HAL_LL_TIM_CHANNEL_2, 14, hal_ll_tim_module_num(TIM_MODULE_15)},
    #endif
    #ifdef TIM16_BKIN_PB5_AF14
    // {GPIO_PB5, TIM16_BASE_ADDRESS, 0, 14, hal_ll_tim_module_num(TIM_MODULE_16)},
    #endif
    #ifdef TIM16_CH1N_PB6_AF14
    {GPIO_PB6, TIM16_BASE_ADDRESS, HAL_LL_TIM_CHANNEL_1N, 14, hal_ll_tim_module_num(TIM_MODULE_16)},
    #endif
    #ifdef TIM16_CH1_PA6_AF14
    {GPIO_PA6, TIM16_BASE_ADDRESS, HAL_LL_TIM_CHANNEL_1, 14, hal_ll_tim_module_num(TIM_MODULE_16)},
    #endif
    #ifdef TIM16_CH1_PB8_AF14
    {GPIO_PB8, TIM16_BASE_ADDRESS, HAL_LL_TIM_CHANNEL_1, 14, hal_ll_tim_module_num(TIM_MODULE_16)},
    #endif
    #ifdef TIM16_CH1_PE0_AF14
    {GPIO_PE0, TIM16_BASE_ADDRESS, HAL_LL_TIM_CHANNEL_1, 14, hal_ll_tim_module_num(TIM_MODULE_16)},
    #endif
    #ifdef TIM17_BKIN_PA10_AF14
    // {GPIO_PA10, TIM17_BASE_ADDRESS, 0, 14, hal_ll_tim_module_num(TIM_MODULE_17)},
    #endif
    #ifdef TIM17_BKIN_PB4_AF14
    // {GPIO_PB4, TIM17_BASE_ADDRESS, 0, 14, hal_ll_tim_module_num(TIM_MODULE_17)},
    #endif
    #ifdef TIM17_CH1N_PB7_AF14
    {GPIO_PB7, TIM17_BASE_ADDRESS, HAL_LL_TIM_CHANNEL_1N, 14, hal_ll_tim_module_num(TIM_MODULE_17)},
    #endif
    #ifdef TIM17_CH1_PA7_AF14
    {GPIO_PA7, TIM17_BASE_ADDRESS, HAL_LL_TIM_CHANNEL_1, 14, hal_ll_tim_module_num(TIM_MODULE_17)},
    #endif
    #ifdef TIM17_CH1_PB9_AF14
    {GPIO_PB9, TIM17_BASE_ADDRESS, HAL_LL_TIM_CHANNEL_1, 14, hal_ll_tim_module_num(TIM_MODULE_17)},
    #endif
    #ifdef TIM17_CH1_PE1_AF14
    {GPIO_PE1, TIM17_BASE_ADDRESS, HAL_LL_TIM_CHANNEL_1, 14, hal_ll_tim_module_num(TIM_MODULE_17)},
    #endif
    #ifdef TIM1_BKIN2_PA11_AF12
    // {GPIO_PA11, TIM1_BASE_ADDRESS, 0, 12, hal_ll_tim_module_num(TIM_MODULE_1)},
    #endif
    #ifdef TIM1_BKIN2_PE14_AF3
    // {GPIO_PE14, TIM1_BASE_ADDRESS, 0, 3, hal_ll_tim_module_num(TIM_MODULE_1)},
    #endif
    #ifdef TIM1_BKIN_PA6_AF12
    // {GPIO_PA6, TIM1_BASE_ADDRESS, 0, 12, hal_ll_tim_module_num(TIM_MODULE_1)},
    #endif
    #ifdef TIM1_BKIN_PB12_AF3
    // {GPIO_PB12, TIM1_BASE_ADDRESS, 0, 3, hal_ll_tim_module_num(TIM_MODULE_1)},
    #endif
    #ifdef TIM1_BKIN_PE15_AF3
    // {GPIO_PE15, TIM1_BASE_ADDRESS, 0, 3, hal_ll_tim_module_num(TIM_MODULE_1)},
    #endif
    #ifdef TIM1_CH1N_PA7_AF1
    {GPIO_PA7, TIM1_BASE_ADDRESS, HAL_LL_TIM_CHANNEL_1N, 1, hal_ll_tim_module_num(TIM_MODULE_1)},
    #endif
    #ifdef TIM1_CH1N_PB13_AF1
    {GPIO_PB13, TIM1_BASE_ADDRESS, HAL_LL_TIM_CHANNEL_1N, 1, hal_ll_tim_module_num(TIM_MODULE_1)},
    #endif
    #ifdef TIM1_CH1N_PE8_AF1
    {GPIO_PE8, TIM1_BASE_ADDRESS, HAL_LL_TIM_CHANNEL_1N, 1, hal_ll_tim_module_num(TIM_MODULE_1)},
    #endif
    #ifdef TIM1_CH1_PA8_AF1
    {GPIO_PA8, TIM1_BASE_ADDRESS, HAL_LL_TIM_CHANNEL_1, 1, hal_ll_tim_module_num(TIM_MODULE_1)},
    #endif
    #ifdef TIM1_CH1_PE9_AF1
    {GPIO_PE9, TIM1_BASE_ADDRESS, HAL_LL_TIM_CHANNEL_1, 1, hal_ll_tim_module_num(TIM_MODULE_1)},
    #endif
    #ifdef TIM1_CH2N_PB0_AF1
    {GPIO_PB0, TIM1_BASE_ADDRESS, HAL_LL_TIM_CHANNEL_2N, 1, hal_ll_tim_module_num(TIM_MODULE_1)},
    #endif
    #ifdef TIM1_CH2N_PB14_AF1
    {GPIO_PB14, TIM1_BASE_ADDRESS, HAL_LL_TIM_CHANNEL_2N, 1, hal_ll_tim_module_num(TIM_MODULE_1)},
    #endif
    #ifdef TIM1_CH2N_PE10_AF1
    {GPIO_PE10, TIM1_BASE_ADDRESS, HAL_LL_TIM_CHANNEL_2N, 1, hal_ll_tim_module_num(TIM_MODULE_1)},
    #endif
    #ifdef TIM1_CH2_PA9_AF1
    {GPIO_PA9, TIM1_BASE_ADDRESS, HAL_LL_TIM_CHANNEL_2, 1, hal_ll_tim_module_num(TIM_MODULE_1)},
    #endif
    #ifdef TIM1_CH2_PE11_AF1
    {GPIO_PE11, TIM1_BASE_ADDRESS, HAL_LL_TIM_CHANNEL_2, 1, hal_ll_tim_module_num(TIM_MODULE_1)},
    #endif
    #ifdef TIM1_CH3N_PB15_AF1
    {GPIO_PB15, TIM1_BASE_ADDRESS, HAL_LL_TIM_CHANNEL_3N, 1, hal_ll_tim_module_num(TIM_MODULE_1)},
    #endif
    #ifdef TIM1_CH3N_PB1_AF1
    {GPIO_PB1, TIM1_BASE_ADDRESS, HAL_LL_TIM_CHANNEL_3N, 1, hal_ll_tim_module_num(TIM_MODULE_1)},
    #endif
    #ifdef TIM1_CH3N_PE12_AF1
    {GPIO_PE12, TIM1_BASE_ADDRESS, HAL_LL_TIM_CHANNEL_3N, 1, hal_ll_tim_module_num(TIM_MODULE_1)},
    #endif
    #ifdef TIM1_CH3_PA10_AF1
    {GPIO_PA10, TIM1_BASE_ADDRESS, HAL_LL_TIM_CHANNEL_3, 1, hal_ll_tim_module_num(TIM_MODULE_1)},
    #endif
    #ifdef TIM1_CH3_PE13_AF1
    {GPIO_PE13, TIM1_BASE_ADDRESS, HAL_LL_TIM_CHANNEL_3, 1, hal_ll_tim_module_num(TIM_MODULE_1)},
    #endif
    #ifdef TIM1_CH4_PA11_AF1
    {GPIO_PA11, TIM1_BASE_ADDRESS, HAL_LL_TIM_CHANNEL_4, 1, hal_ll_tim_module_num(TIM_MODULE_1)},
    #endif
    #ifdef TIM1_CH4_PE14_AF1
    {GPIO_PE14, TIM1_BASE_ADDRESS, HAL_LL_TIM_CHANNEL_4, 1, hal_ll_tim_module_num(TIM_MODULE_1)},
    #endif
    #ifdef TIM1_ETR_PA12_AF1
    // {GPIO_PA12, TIM1_BASE_ADDRESS, 0, 1, hal_ll_tim_module_num(TIM_MODULE_1)},
    #endif
    #ifdef TIM1_ETR_PE7_AF1
    // {GPIO_PE7, TIM1_BASE_ADDRESS, 0, 1, hal_ll_tim_module_num(TIM_MODULE_1)},
    #endif
    #ifdef TIM2_CH1_PA0_AF1
    {GPIO_PA0, TIM2_BASE_ADDRESS, HAL_LL_TIM_CHANNEL_1, 1, hal_ll_tim_module_num(TIM_MODULE_2)},
    #endif
    #ifdef TIM2_CH1_PA15_AF1
    {GPIO_PA15, TIM2_BASE_ADDRESS, HAL_LL_TIM_CHANNEL_1, 1, hal_ll_tim_module_num(TIM_MODULE_2)},
    #endif
    #ifdef TIM2_CH1_PA5_AF1
    {GPIO_PA5, TIM2_BASE_ADDRESS, HAL_LL_TIM_CHANNEL_1, 1, hal_ll_tim_module_num(TIM_MODULE_2)},
    #endif
    #ifdef TIM2_CH2_PA1_AF1
    {GPIO_PA1, TIM2_BASE_ADDRESS, HAL_LL_TIM_CHANNEL_2, 1, hal_ll_tim_module_num(TIM_MODULE_2)},
    #endif
    #ifdef TIM2_CH2_PB3_AF1
    {GPIO_PB3, TIM2_BASE_ADDRESS, HAL_LL_TIM_CHANNEL_2, 1, hal_ll_tim_module_num(TIM_MODULE_2)},
    #endif
    #ifdef TIM2_CH3_PA2_AF1
    {GPIO_PA2, TIM2_BASE_ADDRESS, HAL_LL_TIM_CHANNEL_3, 1, hal_ll_tim_module_num(TIM_MODULE_2)},
    #endif
    #ifdef TIM2_CH3_PB10_AF1
    {GPIO_PB10, TIM2_BASE_ADDRESS, HAL_LL_TIM_CHANNEL_3, 1, hal_ll_tim_module_num(TIM_MODULE_2)},
    #endif
    #ifdef TIM2_CH4_PA3_AF1
    {GPIO_PA3, TIM2_BASE_ADDRESS, HAL_LL_TIM_CHANNEL_4, 1, hal_ll_tim_module_num(TIM_MODULE_2)},
    #endif
    #ifdef TIM2_CH4_PB11_AF1
    {GPIO_PB11, TIM2_BASE_ADDRESS, HAL_LL_TIM_CHANNEL_4, 1, hal_ll_tim_module_num(TIM_MODULE_2)},
    #endif
    #ifdef TIM2_ETR_PA0_AF14
    // {GPIO_PA0, TIM2_BASE_ADDRESS, 0, 14, hal_ll_tim_module_num(TIM_MODULE_2)},
    #endif
    #ifdef TIM2_ETR_PA15_AF2
    // {GPIO_PA15, TIM2_BASE_ADDRESS, 0, 2, hal_ll_tim_module_num(TIM_MODULE_2)},
    #endif
    #ifdef TIM2_ETR_PA5_AF2
    // {GPIO_PA5, TIM2_BASE_ADDRESS, 0, 2, hal_ll_tim_module_num(TIM_MODULE_2)},
    #endif
    #ifdef TIM3_CH1_PA6_AF2
    {GPIO_PA6, TIM3_BASE_ADDRESS, HAL_LL_TIM_CHANNEL_1, 2, hal_ll_tim_module_num(TIM_MODULE_3)},
    #endif
    #ifdef TIM3_CH1_PB4_AF2
    {GPIO_PB4, TIM3_BASE_ADDRESS, HAL_LL_TIM_CHANNEL_1, 2, hal_ll_tim_module_num(TIM_MODULE_3)},
    #endif
    #ifdef TIM3_CH1_PC6_AF2
    {GPIO_PC6, TIM3_BASE_ADDRESS, HAL_LL_TIM_CHANNEL_1, 2, hal_ll_tim_module_num(TIM_MODULE_3)},
    #endif
    #ifdef TIM3_CH1_PE3_AF2
    {GPIO_PE3, TIM3_BASE_ADDRESS, HAL_LL_TIM_CHANNEL_1, 2, hal_ll_tim_module_num(TIM_MODULE_3)},
    #endif
    #ifdef TIM3_CH2_PA7_AF2
    {GPIO_PA7, TIM3_BASE_ADDRESS, HAL_LL_TIM_CHANNEL_2, 2, hal_ll_tim_module_num(TIM_MODULE_3)},
    #endif
    #ifdef TIM3_CH2_PB5_AF2
    {GPIO_PB5, TIM3_BASE_ADDRESS, HAL_LL_TIM_CHANNEL_2, 2, hal_ll_tim_module_num(TIM_MODULE_3)},
    #endif
    #ifdef TIM3_CH2_PC7_AF2
    {GPIO_PC7, TIM3_BASE_ADDRESS, HAL_LL_TIM_CHANNEL_2, 2, hal_ll_tim_module_num(TIM_MODULE_3)},
    #endif
    #ifdef TIM3_CH2_PE4_AF2
    {GPIO_PE4, TIM3_BASE_ADDRESS, HAL_LL_TIM_CHANNEL_2, 2, hal_ll_tim_module_num(TIM_MODULE_3)},
    #endif
    #ifdef TIM3_CH3_PB0_AF2
    {GPIO_PB0, TIM3_BASE_ADDRESS, HAL_LL_TIM_CHANNEL_3, 2, hal_ll_tim_module_num(TIM_MODULE_3)},
    #endif
    #ifdef TIM3_CH3_PC8_AF2
    {GPIO_PC8, TIM3_BASE_ADDRESS, HAL_LL_TIM_CHANNEL_3, 2, hal_ll_tim_module_num(TIM_MODULE_3)},
    #endif
    #ifdef TIM3_CH3_PE5_AF2
    {GPIO_PE5, TIM3_BASE_ADDRESS, HAL_LL_TIM_CHANNEL_3, 2, hal_ll_tim_module_num(TIM_MODULE_3)},
    #endif
    #ifdef TIM3_CH4_PB1_AF2
    {GPIO_PB1, TIM3_BASE_ADDRESS, HAL_LL_TIM_CHANNEL_4, 2, hal_ll_tim_module_num(TIM_MODULE_3)},
    #endif
    #ifdef TIM3_CH4_PC9_AF2
    {GPIO_PC9, TIM3_BASE_ADDRESS, HAL_LL_TIM_CHANNEL_4, 2, hal_ll_tim_module_num(TIM_MODULE_3)},
    #endif
    #ifdef TIM3_CH4_PE6_AF2
    {GPIO_PE6, TIM3_BASE_ADDRESS, HAL_LL_TIM_CHANNEL_4, 2, hal_ll_tim_module_num(TIM_MODULE_3)},
    #endif
    #ifdef TIM3_ETR_PD2_AF2
    // {GPIO_PD2, TIM3_BASE_ADDRESS, 0, 2, hal_ll_tim_module_num(TIM_MODULE_3)},
    #endif
    #ifdef TIM3_ETR_PE2_AF2
    // {GPIO_PE2, TIM3_BASE_ADDRESS, 0, 2, hal_ll_tim_module_num(TIM_MODULE_3)},
    #endif
    #ifdef TIM4_CH1_PB6_AF2
    {GPIO_PB6, TIM4_BASE_ADDRESS, HAL_LL_TIM_CHANNEL_1, 2, hal_ll_tim_module_num(TIM_MODULE_4)},
    #endif
    #ifdef TIM4_CH1_PD12_AF2
    {GPIO_PD12, TIM4_BASE_ADDRESS, HAL_LL_TIM_CHANNEL_1, 2, hal_ll_tim_module_num(TIM_MODULE_4)},
    #endif
    #ifdef TIM4_CH2_PB7_AF2
    {GPIO_PB7, TIM4_BASE_ADDRESS, HAL_LL_TIM_CHANNEL_2, 2, hal_ll_tim_module_num(TIM_MODULE_4)},
    #endif
    #ifdef TIM4_CH2_PD13_AF2
    {GPIO_PD13, TIM4_BASE_ADDRESS, HAL_LL_TIM_CHANNEL_2, 2, hal_ll_tim_module_num(TIM_MODULE_4)},
    #endif
    #ifdef TIM4_CH3_PB8_AF2
    {GPIO_PB8, TIM4_BASE_ADDRESS, HAL_LL_TIM_CHANNEL_3, 2, hal_ll_tim_module_num(TIM_MODULE_4)},
    #endif
    #ifdef TIM4_CH3_PD14_AF2
    {GPIO_PD14, TIM4_BASE_ADDRESS, HAL_LL_TIM_CHANNEL_3, 2, hal_ll_tim_module_num(TIM_MODULE_4)},
    #endif
    #ifdef TIM4_CH4_PB9_AF2
    {GPIO_PB9, TIM4_BASE_ADDRESS, HAL_LL_TIM_CHANNEL_4, 2, hal_ll_tim_module_num(TIM_MODULE_4)},
    #endif
    #ifdef TIM4_CH4_PD15_AF2
    {GPIO_PD15, TIM4_BASE_ADDRESS, HAL_LL_TIM_CHANNEL_4, 2, hal_ll_tim_module_num(TIM_MODULE_4)},
    #endif
    #ifdef TIM4_ETR_PE0_AF2
    // {GPIO_PE0, TIM4_BASE_ADDRESS, 0, 2, hal_ll_tim_module_num(TIM_MODULE_4)},
    #endif
    #ifdef TIM5_CH1_PA0_AF2
    {GPIO_PA0, TIM5_BASE_ADDRESS, HAL_LL_TIM_CHANNEL_1, 2, hal_ll_tim_module_num(TIM_MODULE_5)},
    #endif
    #ifdef TIM5_CH1_PF6_AF2
    {GPIO_PF6, TIM5_BASE_ADDRESS, HAL_LL_TIM_CHANNEL_1, 2, hal_ll_tim_module_num(TIM_MODULE_5)},
    #endif
    #ifdef TIM5_CH2_PA1_AF2
    {GPIO_PA1, TIM5_BASE_ADDRESS, HAL_LL_TIM_CHANNEL_2, 2, hal_ll_tim_module_num(TIM_MODULE_5)},
    #endif
    #ifdef TIM5_CH2_PF7_AF2
    {GPIO_PF7, TIM5_BASE_ADDRESS, HAL_LL_TIM_CHANNEL_2, 2, hal_ll_tim_module_num(TIM_MODULE_5)},
    #endif
    #ifdef TIM5_CH3_PA2_AF2
    {GPIO_PA2, TIM5_BASE_ADDRESS, HAL_LL_TIM_CHANNEL_3, 2, hal_ll_tim_module_num(TIM_MODULE_5)},
    #endif
    #ifdef TIM5_CH3_PF8_AF2
    {GPIO_PF8, TIM5_BASE_ADDRESS, HAL_LL_TIM_CHANNEL_3, 2, hal_ll_tim_module_num(TIM_MODULE_5)},
    #endif
    #ifdef TIM5_CH4_PA3_AF2
    {GPIO_PA3, TIM5_BASE_ADDRESS, HAL_LL_TIM_CHANNEL_4, 2, hal_ll_tim_module_num(TIM_MODULE_5)},
    #endif
    #ifdef TIM5_CH4_PF9_AF2
    {GPIO_PF9, TIM5_BASE_ADDRESS, HAL_LL_TIM_CHANNEL_4, 2, hal_ll_tim_module_num(TIM_MODULE_5)},
    #endif
    #ifdef TIM5_ETR_PF6_AF1
    // {GPIO_PF6, TIM5_BASE_ADDRESS, 0, 1, hal_ll_tim_module_num(TIM_MODULE_5)},
    #endif
    #ifdef TIM8_BKIN2_PB6_AF12
    // {GPIO_PB6, TIM8_BASE_ADDRESS, 0, 12, hal_ll_tim_module_num(TIM_MODULE_8)},
    #endif
    #ifdef TIM8_BKIN2_PC9_AF14
    // {GPIO_PC9, TIM8_BASE_ADDRESS, 0, 14, hal_ll_tim_module_num(TIM_MODULE_8)},
    #endif
    #ifdef TIM8_BKIN_PA6_AF13
    // {GPIO_PA6, TIM8_BASE_ADDRESS, 0, 13, hal_ll_tim_module_num(TIM_MODULE_8)},
    #endif
    #ifdef TIM8_BKIN_PB7_AF13
    // {GPIO_PB7, TIM8_BASE_ADDRESS, 0, 13, hal_ll_tim_module_num(TIM_MODULE_8)},
    #endif
    #ifdef TIM8_CH1N_PA5_AF3
    {GPIO_PA5, TIM8_BASE_ADDRESS, HAL_LL_TIM_CHANNEL_1N, 3, hal_ll_tim_module_num(TIM_MODULE_8)},
    #endif
    #ifdef TIM8_CH1N_PA7_AF3
    {GPIO_PA7, TIM8_BASE_ADDRESS, HAL_LL_TIM_CHANNEL_1N, 3, hal_ll_tim_module_num(TIM_MODULE_8)},
    #endif
    #ifdef TIM8_CH1_PC6_AF3
    {GPIO_PC6, TIM8_BASE_ADDRESS, HAL_LL_TIM_CHANNEL_1, 3, hal_ll_tim_module_num(TIM_MODULE_8)},
    #endif
    #ifdef TIM8_CH2N_PB0_AF3
    {GPIO_PB0, TIM8_BASE_ADDRESS, HAL_LL_TIM_CHANNEL_2N, 3, hal_ll_tim_module_num(TIM_MODULE_8)},
    #endif
    #ifdef TIM8_CH2N_PB14_AF3
    {GPIO_PB14, TIM8_BASE_ADDRESS, HAL_LL_TIM_CHANNEL_2N, 3, hal_ll_tim_module_num(TIM_MODULE_8)},
    #endif
    #ifdef TIM8_CH2_PC7_AF3
    {GPIO_PC7, TIM8_BASE_ADDRESS, HAL_LL_TIM_CHANNEL_2, 3, hal_ll_tim_module_num(TIM_MODULE_8)},
    #endif
    #ifdef TIM8_CH3N_PB15_AF3
    {GPIO_PB15, TIM8_BASE_ADDRESS, HAL_LL_TIM_CHANNEL_3N, 3, hal_ll_tim_module_num(TIM_MODULE_8)},
    #endif
    #ifdef TIM8_CH3N_PB1_AF3
    {GPIO_PB1, TIM8_BASE_ADDRESS, HAL_LL_TIM_CHANNEL_3N, 3, hal_ll_tim_module_num(TIM_MODULE_8)},
    #endif
    #ifdef TIM8_CH3_PC8_AF3
    {GPIO_PC8, TIM8_BASE_ADDRESS, HAL_LL_TIM_CHANNEL_3, 3, hal_ll_tim_module_num(TIM_MODULE_8)},
    #endif
    #ifdef TIM8_CH4_PC9_AF3
    {GPIO_PC9, TIM8_BASE_ADDRESS, HAL_LL_TIM_CHANNEL_4, 3, hal_ll_tim_module_num(TIM_MODULE_8)},
    #endif
    #ifdef TIM8_ETR_PA0_AF3
    // {GPIO_PA0, TIM8_BASE_ADDRESS, 0, 3, hal_ll_tim_module_num(TIM_MODULE_8)},
    #endif
    #ifdef TIM5_CH1_PH10_AF2
    {GPIO_PH10, TIM5_BASE_ADDRESS, HAL_LL_TIM_CHANNEL_1, 2, hal_ll_tim_module_num(TIM_MODULE_5)},
    #endif
    #ifdef TIM5_CH2_PH11_AF2
    {GPIO_PH11, TIM5_BASE_ADDRESS, HAL_LL_TIM_CHANNEL_2, 2, hal_ll_tim_module_num(TIM_MODULE_5)},
    #endif
    #ifdef TIM5_CH3_PH12_AF2
    {GPIO_PH12, TIM5_BASE_ADDRESS, HAL_LL_TIM_CHANNEL_3, 2, hal_ll_tim_module_num(TIM_MODULE_5)},
    #endif
    #ifdef TIM5_CH4_PI0_AF2
    {GPIO_PI0, TIM5_BASE_ADDRESS, HAL_LL_TIM_CHANNEL_4, 2, hal_ll_tim_module_num(TIM_MODULE_5)},
    #endif
    #ifdef TIM8_BKIN_PI4_AF3
    // {GPIO_PI4, TIM8_BASE_ADDRESS, 0, 3, hal_ll_tim_module_num(TIM_MODULE_8)},
    #endif
    #ifdef TIM8_CH1N_PH13_AF3
    {GPIO_PH13, TIM8_BASE_ADDRESS, HAL_LL_TIM_CHANNEL_1N, 3, hal_ll_tim_module_num(TIM_MODULE_8)},
    #endif
    #ifdef TIM8_CH1_PI5_AF3
    {GPIO_PI5, TIM8_BASE_ADDRESS, HAL_LL_TIM_CHANNEL_1, 3, hal_ll_tim_module_num(TIM_MODULE_8)},
    #endif
    #ifdef TIM8_CH2N_PH14_AF3
    {GPIO_PH14, TIM8_BASE_ADDRESS, HAL_LL_TIM_CHANNEL_2N, 3, hal_ll_tim_module_num(TIM_MODULE_8)},
    #endif
    #ifdef TIM8_CH2_PI6_AF3
    {GPIO_PI6, TIM8_BASE_ADDRESS, HAL_LL_TIM_CHANNEL_2, 3, hal_ll_tim_module_num(TIM_MODULE_8)},
    #endif
    #ifdef TIM8_CH3N_PH15_AF3
    {GPIO_PH15, TIM8_BASE_ADDRESS, HAL_LL_TIM_CHANNEL_3N, 3, hal_ll_tim_module_num(TIM_MODULE_8)},
    #endif
    #ifdef TIM8_CH3_PI7_AF3
    {GPIO_PI7, TIM8_BASE_ADDRESS, HAL_LL_TIM_CHANNEL_3, 3, hal_ll_tim_module_num(TIM_MODULE_8)},
    #endif
    #ifdef TIM8_CH4_PI2_AF3
    {GPIO_PI2, TIM8_BASE_ADDRESS, HAL_LL_TIM_CHANNEL_4, 3, hal_ll_tim_module_num(TIM_MODULE_8)},
    #endif
    #ifdef TIM8_ETR_PI3_AF3
    // {GPIO_PI3, TIM8_BASE_ADDRESS, 0, 3, hal_ll_tim_module_num(TIM_MODULE_8)},
    #endif
    { HAL_LL_PIN_NC, HAL_LL_MODULE_ERROR, HAL_LL_CHANNEL_ERROR, HAL_LL_PIN_NC, HAL_LL_PIN_NC }
};

#ifdef __cplusplus
}
#endif

#endif // _HAL_LL_TIM_PIN_MAP_H_
// ------------------------------------------------------------------------- END
