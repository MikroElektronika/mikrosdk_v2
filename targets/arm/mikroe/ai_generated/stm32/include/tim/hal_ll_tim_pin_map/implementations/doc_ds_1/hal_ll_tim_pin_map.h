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
#ifdef TIM_MODULE_3
#define TIM3_BASE_ADDRESS (0x40000400UL)
#define TIM3_BASE_ADDR TIM3_BASE_ADDRESS
#define HAL_LL_TIM3_BASE_ADDR TIM3_BASE_ADDRESS
#define HAL_LL_TIM3_BASE_ADDRESS TIM3_BASE_ADDRESS
#endif
#ifdef TIM_MODULE_14
#define TIM14_BASE_ADDRESS (0x40002000UL)
#define TIM14_BASE_ADDR TIM14_BASE_ADDRESS
#define HAL_LL_TIM14_BASE_ADDR TIM14_BASE_ADDRESS
#define HAL_LL_TIM14_BASE_ADDRESS TIM14_BASE_ADDRESS
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
    #ifdef TIM14_CH1_PA4_AF4
    {PA4, TIM14_BASE_ADDRESS, HAL_LL_TIM_CHANNEL_1, 4, hal_ll_tim_module_num(TIM_MODULE_14)},
    #endif
    #ifdef TIM14_CH1_PA7_AF4
    {PA7, TIM14_BASE_ADDRESS, HAL_LL_TIM_CHANNEL_1, 4, hal_ll_tim_module_num(TIM_MODULE_14)},
    #endif
    #ifdef TIM14_CH1_PA8_AF13
    {PA8, TIM14_BASE_ADDRESS, HAL_LL_TIM_CHANNEL_1, 13, hal_ll_tim_module_num(TIM_MODULE_14)},
    #endif
    #ifdef TIM16_BKIN_PB6_AF14
    // {PB6, TIM16_BASE_ADDRESS, 0, 14, hal_ll_tim_module_num(TIM_MODULE_16)},
    #endif
    #ifdef TIM16_CH1N_PA2_AF2
    {PA2, TIM16_BASE_ADDRESS, HAL_LL_TIM_CHANNEL_1N, 2, hal_ll_tim_module_num(TIM_MODULE_16)},
    #endif
    #ifdef TIM16_CH1N_PB6_AF2
    {PB6, TIM16_BASE_ADDRESS, HAL_LL_TIM_CHANNEL_1N, 2, hal_ll_tim_module_num(TIM_MODULE_16)},
    #endif
    #ifdef TIM16_CH1_PA0_AF2
    {PA0, TIM16_BASE_ADDRESS, HAL_LL_TIM_CHANNEL_1, 2, hal_ll_tim_module_num(TIM_MODULE_16)},
    #endif
    #ifdef TIM16_CH1_PA6_AF5
    {PA6, TIM16_BASE_ADDRESS, HAL_LL_TIM_CHANNEL_1, 5, hal_ll_tim_module_num(TIM_MODULE_16)},
    #endif
    #ifdef TIM16_CH1_PB7_AF10
    {PB7, TIM16_BASE_ADDRESS, HAL_LL_TIM_CHANNEL_1, 10, hal_ll_tim_module_num(TIM_MODULE_16)},
    #endif
    #ifdef TIM17_BKIN_PA10_AF5
    // {PA10, TIM17_BASE_ADDRESS, 0, 5, hal_ll_tim_module_num(TIM_MODULE_17)},
    #endif
    #ifdef TIM17_BKIN_PB6_AF15
    // {PB6, TIM17_BASE_ADDRESS, 0, 15, hal_ll_tim_module_num(TIM_MODULE_17)},
    #endif
    #ifdef TIM17_CH1N_PA4_AF5
    {PA4, TIM17_BASE_ADDRESS, HAL_LL_TIM_CHANNEL_1N, 5, hal_ll_tim_module_num(TIM_MODULE_17)},
    #endif
    #ifdef TIM17_CH1N_PB7_AF2
    {PB7, TIM17_BASE_ADDRESS, HAL_LL_TIM_CHANNEL_1N, 2, hal_ll_tim_module_num(TIM_MODULE_17)},
    #endif
    #ifdef TIM17_CH1_PA1_AF2
    {PA1, TIM17_BASE_ADDRESS, HAL_LL_TIM_CHANNEL_1, 2, hal_ll_tim_module_num(TIM_MODULE_17)},
    #endif
    #ifdef TIM17_CH1_PA7_AF5
    {PA7, TIM17_BASE_ADDRESS, HAL_LL_TIM_CHANNEL_1, 5, hal_ll_tim_module_num(TIM_MODULE_17)},
    #endif
    #ifdef TIM17_CH1_PC14_AF10
    {PC14, TIM17_BASE_ADDRESS, HAL_LL_TIM_CHANNEL_1, 10, hal_ll_tim_module_num(TIM_MODULE_17)},
    #endif
    #ifdef TIM1_BKIN2_PA11_AF5
    // {PA11, TIM1_BASE_ADDRESS, 0, 5, hal_ll_tim_module_num(TIM_MODULE_1)},
    #endif
    #ifdef TIM1_BKIN2_PC14_AF2
    // {PC14, TIM1_BASE_ADDRESS, 0, 2, hal_ll_tim_module_num(TIM_MODULE_1)},
    #endif
    #ifdef TIM1_BKIN_PA6_AF2
    // {PA6, TIM1_BASE_ADDRESS, 0, 2, hal_ll_tim_module_num(TIM_MODULE_1)},
    #endif
    #ifdef TIM1_CH1N_PA3_AF2
    {PA3, TIM1_BASE_ADDRESS, HAL_LL_TIM_CHANNEL_1N, 2, hal_ll_tim_module_num(TIM_MODULE_1)},
    #endif
    #ifdef TIM1_CH1N_PA7_AF2
    {PA7, TIM1_BASE_ADDRESS, HAL_LL_TIM_CHANNEL_1N, 2, hal_ll_tim_module_num(TIM_MODULE_1)},
    #endif
    #ifdef TIM1_CH1_PA0_AF5
    {PA0, TIM1_BASE_ADDRESS, HAL_LL_TIM_CHANNEL_1, 5, hal_ll_tim_module_num(TIM_MODULE_1)},
    #endif
    #ifdef TIM1_CH1_PA14_AF10
    {PA14, TIM1_BASE_ADDRESS, HAL_LL_TIM_CHANNEL_1, 10, hal_ll_tim_module_num(TIM_MODULE_1)},
    #endif
    #ifdef TIM1_CH1_PA5_AF5
    {PA5, TIM1_BASE_ADDRESS, HAL_LL_TIM_CHANNEL_1, 5, hal_ll_tim_module_num(TIM_MODULE_1)},
    #endif
    #ifdef TIM1_CH1_PA8_AF2
    {PA8, TIM1_BASE_ADDRESS, HAL_LL_TIM_CHANNEL_1, 2, hal_ll_tim_module_num(TIM_MODULE_1)},
    #endif
    #ifdef TIM1_CH2N_PA4_AF2
    {PA4, TIM1_BASE_ADDRESS, HAL_LL_TIM_CHANNEL_2N, 2, hal_ll_tim_module_num(TIM_MODULE_1)},
    #endif
    #ifdef TIM1_CH2N_PA8_AF9
    {PA8, TIM1_BASE_ADDRESS, HAL_LL_TIM_CHANNEL_2N, 9, hal_ll_tim_module_num(TIM_MODULE_1)},
    #endif
    #ifdef TIM1_CH2_PA1_AF5
    {PA1, TIM1_BASE_ADDRESS, HAL_LL_TIM_CHANNEL_2, 5, hal_ll_tim_module_num(TIM_MODULE_1)},
    #endif
    #ifdef TIM1_CH2_PA9_AF2
    {PA9, TIM1_BASE_ADDRESS, HAL_LL_TIM_CHANNEL_2, 2, hal_ll_tim_module_num(TIM_MODULE_1)},
    #endif
    #ifdef TIM1_CH2_PB6_AF11
    {PB6, TIM1_BASE_ADDRESS, HAL_LL_TIM_CHANNEL_2, 11, hal_ll_tim_module_num(TIM_MODULE_1)},
    #endif
    #ifdef TIM1_CH3N_PA5_AF2
    {PA5, TIM1_BASE_ADDRESS, HAL_LL_TIM_CHANNEL_3N, 2, hal_ll_tim_module_num(TIM_MODULE_1)},
    #endif
    #ifdef TIM1_CH3N_PA8_AF10
    {PA8, TIM1_BASE_ADDRESS, HAL_LL_TIM_CHANNEL_3N, 10, hal_ll_tim_module_num(TIM_MODULE_1)},
    #endif
    #ifdef TIM1_CH3_PA10_AF2
    {PA10, TIM1_BASE_ADDRESS, HAL_LL_TIM_CHANNEL_3, 2, hal_ll_tim_module_num(TIM_MODULE_1)},
    #endif
    #ifdef TIM1_CH3_PA2_AF5
    {PA2, TIM1_BASE_ADDRESS, HAL_LL_TIM_CHANNEL_3, 5, hal_ll_tim_module_num(TIM_MODULE_1)},
    #endif
    #ifdef TIM1_CH3_PB6_AF1
    {PB6, TIM1_BASE_ADDRESS, HAL_LL_TIM_CHANNEL_3, 1, hal_ll_tim_module_num(TIM_MODULE_1)},
    #endif
    #ifdef TIM1_CH4_PA11_AF2
    {PA11, TIM1_BASE_ADDRESS, HAL_LL_TIM_CHANNEL_4, 2, hal_ll_tim_module_num(TIM_MODULE_1)},
    #endif
    #ifdef TIM1_CH4_PA3_AF5
    {PA3, TIM1_BASE_ADDRESS, HAL_LL_TIM_CHANNEL_4, 5, hal_ll_tim_module_num(TIM_MODULE_1)},
    #endif
    #ifdef TIM1_CH4_PB7_AF1
    {PB7, TIM1_BASE_ADDRESS, HAL_LL_TIM_CHANNEL_4, 1, hal_ll_tim_module_num(TIM_MODULE_1)},
    #endif
    #ifdef TIM1_CH4_PF2_AF1
    {PF2, TIM1_BASE_ADDRESS, HAL_LL_TIM_CHANNEL_4, 1, hal_ll_tim_module_num(TIM_MODULE_1)},
    #endif
    #ifdef TIM1_ETR_PA12_AF2
    // {PA12, TIM1_BASE_ADDRESS, 0, 2, hal_ll_tim_module_num(TIM_MODULE_1)},
    #endif
    #ifdef TIM1_ETR_PC14_AF1
    // {PC14, TIM1_BASE_ADDRESS, 0, 1, hal_ll_tim_module_num(TIM_MODULE_1)},
    #endif
    #ifdef TIM1_ETR_PC15_AF2
    // {PC15, TIM1_BASE_ADDRESS, 0, 2, hal_ll_tim_module_num(TIM_MODULE_1)},
    #endif
    #ifdef TIM3_CH1_PA6_AF1
    {PA6, TIM3_BASE_ADDRESS, HAL_LL_TIM_CHANNEL_1, 1, hal_ll_tim_module_num(TIM_MODULE_3)},
    #endif
    #ifdef TIM3_CH1_PB6_AF12
    {PB6, TIM3_BASE_ADDRESS, HAL_LL_TIM_CHANNEL_1, 12, hal_ll_tim_module_num(TIM_MODULE_3)},
    #endif
    #ifdef TIM3_CH1_PB7_AF11
    {PB7, TIM3_BASE_ADDRESS, HAL_LL_TIM_CHANNEL_1, 11, hal_ll_tim_module_num(TIM_MODULE_3)},
    #endif
    #ifdef TIM3_CH2_PA7_AF1
    {PA7, TIM3_BASE_ADDRESS, HAL_LL_TIM_CHANNEL_2, 1, hal_ll_tim_module_num(TIM_MODULE_3)},
    #endif
    #ifdef TIM3_CH2_PB6_AF13
    {PB6, TIM3_BASE_ADDRESS, HAL_LL_TIM_CHANNEL_2, 13, hal_ll_tim_module_num(TIM_MODULE_3)},
    #endif
    #ifdef TIM3_CH2_PC14_AF11
    {PC14, TIM3_BASE_ADDRESS, HAL_LL_TIM_CHANNEL_2, 11, hal_ll_tim_module_num(TIM_MODULE_3)},
    #endif
    #ifdef TIM3_CH3_PA8_AF11
    {PA8, TIM3_BASE_ADDRESS, HAL_LL_TIM_CHANNEL_3, 11, hal_ll_tim_module_num(TIM_MODULE_3)},
    #endif
    #ifdef TIM3_CH3_PB6_AF3
    {PB6, TIM3_BASE_ADDRESS, HAL_LL_TIM_CHANNEL_3, 3, hal_ll_tim_module_num(TIM_MODULE_3)},
    #endif
    #ifdef TIM3_CH3_PC15_AF3
    {PC15, TIM3_BASE_ADDRESS, HAL_LL_TIM_CHANNEL_3, 3, hal_ll_tim_module_num(TIM_MODULE_3)},
    #endif
    #ifdef TIM3_CH4_PA8_AF12
    {PA8, TIM3_BASE_ADDRESS, HAL_LL_TIM_CHANNEL_4, 12, hal_ll_tim_module_num(TIM_MODULE_3)},
    #endif
    #ifdef TIM3_CH4_PB7_AF3
    {PB7, TIM3_BASE_ADDRESS, HAL_LL_TIM_CHANNEL_4, 3, hal_ll_tim_module_num(TIM_MODULE_3)},
    #endif
    #ifdef TIM3_ETR_PA13_AF3
    // {PA13, TIM3_BASE_ADDRESS, 0, 3, hal_ll_tim_module_num(TIM_MODULE_3)},
    #endif
    #ifdef TIM3_ETR_PA2_AF3
    // {PA2, TIM3_BASE_ADDRESS, 0, 3, hal_ll_tim_module_num(TIM_MODULE_3)},
    #endif
    #ifdef TIM3_ETR_PA9_AF3
    // {PA9, TIM3_BASE_ADDRESS, 0, 3, hal_ll_tim_module_num(TIM_MODULE_3)},
    #endif
    { HAL_LL_PIN_NC, HAL_LL_MODULE_ERROR, HAL_LL_CHANNEL_ERROR, HAL_LL_PIN_NC, HAL_LL_PIN_NC }
};

#ifdef __cplusplus
}
#endif

#endif // _HAL_LL_TIM_PIN_MAP_H_
// ------------------------------------------------------------------------- END
