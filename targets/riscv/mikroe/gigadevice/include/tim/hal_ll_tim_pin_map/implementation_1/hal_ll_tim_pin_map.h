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

/*!< @brief Macro defining `weak` attribute */
#define __weak __attribute__((weak))
/*!< @brief Helper macro for getting adequate module index number */
#define hal_ll_tim_module_num(_module_num) (_module_num - 1)

/*!< If module is remapped. */
#define HAL_LL_TIM_REMAP 0x80000000

/*!< TIM module base addresses. */
#ifdef TIM_MODULE_0
static const hal_ll_base_addr_t HAL_LL_TIM0_BASE_ADDR = 0x40012C00;
#endif
#ifdef TIM_MODULE_1
static const hal_ll_base_addr_t HAL_LL_TIM1_BASE_ADDR = 0x40000000;
#endif
#ifdef TIM_MODULE_2
static const hal_ll_base_addr_t HAL_LL_TIM2_BASE_ADDR = 0x40000400;
#endif
#ifdef TIM_MODULE_3
static const hal_ll_base_addr_t HAL_LL_TIM3_BASE_ADDR = 0x40000800;
#endif
#ifdef TIM_MODULE_4
static const hal_ll_base_addr_t HAL_LL_TIM4_BASE_ADDR = 0x40000C00;
#endif

/*!< @brief TIM module alternate functions. */
static const uint32_t HAL_LL_TIM_GPIO_AF_NO_REMAP = 0x00000000;
#ifdef TIM_MODULE_0
static const uint32_t HAL_LL_TIM0_GPIO_AF_PARTIAL_REMAP = 0x00000040;
static const uint32_t HAL_LL_TIM0_GPIO_AF_FULL_REMAP = 0x000000C0;
#endif
#ifdef TIM_MODULE_1
static const uint32_t HAL_LL_TIM1_GPIO_AF_PARTIAL_REMAP = 0x00000100;
static const uint32_t HAL_LL_TIM1_GPIO_AF_FULL_REMAP = 0x00000300;
#endif
#ifdef TIM_MODULE_2
static const uint32_t HAL_LL_TIM2_GPIO_AF_PARTIAL_REMAP = 0x00000800;
static const uint32_t HAL_LL_TIM2_GPIO_AF_FULL_REMAP = 0x00000C00;
#endif
#ifdef TIM_MODULE_3
static const uint32_t HAL_LL_TIM3_GPIO_AF_FULL_REMAP = 0x00001000;
#endif
#ifdef TIM_MODULE_4
static const uint32_t HAL_LL_TIM4_GPIO_AF_NO_REMAP = 0x00000000;
#endif

typedef enum {
    HAL_LL_TIM_CHANNEL_0 = 0, /* Standard PWM channel 0. */
    HAL_LL_TIM_CHANNEL_1, /* Standard PWM channel 1. */
    HAL_LL_TIM_CHANNEL_2, /* Standard PWM channel 2. */
    HAL_LL_TIM_CHANNEL_3, /* Standard PWM channel 3. */
    HAL_LL_TIM_CHANNEL_0N, /* Complementary PWM channel 0. */
    HAL_LL_TIM_CHANNEL_1N, /* Complementary PWM channel 1. */
    HAL_LL_TIM_CHANNEL_2N, /* Complementary PWM channel 2. */
    HAL_LL_TIM_CHANNEL_3N /* Complementary PWM channel 3. */
} hal_ll_tim_channel_t;

/*!< @brief TIM pin structure. */
typedef struct {
    hal_ll_pin_name_t pin;
    hal_ll_base_addr_t base;
    hal_ll_tim_channel_t channel;
    uint32_t af;
    uint8_t module_index;
} hal_ll_tim_pin_map_t;

/*!< TIM pins. */
static const hal_ll_tim_pin_map_t _tim_map[] = {
    #ifdef TIMER1_CH0_PA0_REMAP_NONE
    {PA0, HAL_LL_TIM1_BASE_ADDR, HAL_LL_TIM_CHANNEL_0, HAL_LL_TIM_GPIO_AF_NO_REMAP, hal_ll_tim_module_num(TIM_MODULE_1)},
    #endif
    #ifdef TIMER1_CH1_PA1_REMAP_NONE
    {PA1, HAL_LL_TIM1_BASE_ADDR, HAL_LL_TIM_CHANNEL_1, HAL_LL_TIM_GPIO_AF_NO_REMAP, hal_ll_tim_module_num(TIM_MODULE_1)},
    #endif
    #ifdef TIMER1_CH2_PA2_REMAP_NONE
    {PA2, HAL_LL_TIM1_BASE_ADDR, HAL_LL_TIM_CHANNEL_2, HAL_LL_TIM_GPIO_AF_NO_REMAP, hal_ll_tim_module_num(TIM_MODULE_1)},
    #endif
    #ifdef TIMER1_CH3_PA3_REMAP_NONE
    {PA3, HAL_LL_TIM1_BASE_ADDR, HAL_LL_TIM_CHANNEL_3, HAL_LL_TIM_GPIO_AF_NO_REMAP, hal_ll_tim_module_num(TIM_MODULE_1)},
    #endif
    #ifdef TIMER2_CH0_PA6_REMAP_NONE
    {PA6, HAL_LL_TIM2_BASE_ADDR, HAL_LL_TIM_CHANNEL_0, HAL_LL_TIM_GPIO_AF_NO_REMAP, hal_ll_tim_module_num(TIM_MODULE_2)},
    #endif
    #ifdef TIMER2_CH1_PA7_REMAP_NONE
    {PA7, HAL_LL_TIM2_BASE_ADDR, HAL_LL_TIM_CHANNEL_1, HAL_LL_TIM_GPIO_AF_NO_REMAP, hal_ll_tim_module_num(TIM_MODULE_2)},
    #endif
    #ifdef TIMER0_CH0_PA7_REMAP_PARTIAL
    {PA7, HAL_LL_TIM0_BASE_ADDR, HAL_LL_TIM_CHANNEL_0, HAL_LL_TIM_REMAP | HAL_LL_TIM0_GPIO_AF_PARTIAL_REMAP, hal_ll_tim_module_num(TIM_MODULE_0)},
    #endif
    #ifdef TIMER0_CH0_ON_PA7_INVERTED_REMAP_NONE
    {PA7, HAL_LL_TIM0_BASE_ADDR, HAL_LL_TIM_CHANNEL_0N, HAL_LL_TIM_GPIO_AF_NO_REMAP, hal_ll_tim_module_num(TIM_MODULE_0)},
    #endif
    #ifdef TIMER2_CH2_PB0_REMAP_NONE
    {PB0, HAL_LL_TIM2_BASE_ADDR, HAL_LL_TIM_CHANNEL_2, HAL_LL_TIM_GPIO_AF_NO_REMAP, hal_ll_tim_module_num(TIM_MODULE_2)},
    #endif
    #ifdef TIMER0_CH1_PB0_REMAP_PARTIAL
    {PB0, HAL_LL_TIM0_BASE_ADDR, HAL_LL_TIM_CHANNEL_1, HAL_LL_TIM_REMAP | HAL_LL_TIM0_GPIO_AF_PARTIAL_REMAP, hal_ll_tim_module_num(TIM_MODULE_0)},
    #endif
    #ifdef TIMER0_CH1_ON_PB0_INVERTED_REMAP_NONE
    {PB0, HAL_LL_TIM0_BASE_ADDR, HAL_LL_TIM_CHANNEL_1N, HAL_LL_TIM_GPIO_AF_NO_REMAP, hal_ll_tim_module_num(TIM_MODULE_0)},
    #endif
    #ifdef TIMER2_CH3_PB1_REMAP_NONE
    {PB1, HAL_LL_TIM2_BASE_ADDR, HAL_LL_TIM_CHANNEL_3, HAL_LL_TIM_GPIO_AF_NO_REMAP, hal_ll_tim_module_num(TIM_MODULE_2)},
    #endif
    #ifdef TIMER0_CH2_PB1_REMAP_PARTIAL
    {PB1, HAL_LL_TIM0_BASE_ADDR, HAL_LL_TIM_CHANNEL_2, HAL_LL_TIM_REMAP | HAL_LL_TIM0_GPIO_AF_PARTIAL_REMAP, hal_ll_tim_module_num(TIM_MODULE_0)},
    #endif
    #ifdef TIMER0_CH2_ON_PB1_INVERTED_REMAP_NONE
    {PB1, HAL_LL_TIM0_BASE_ADDR, HAL_LL_TIM_CHANNEL_2N, HAL_LL_TIM_GPIO_AF_NO_REMAP, hal_ll_tim_module_num(TIM_MODULE_0)},
    #endif
    #ifdef TIMER1_CH2_PB10_REMAP_FULL
    {PB10, HAL_LL_TIM1_BASE_ADDR, HAL_LL_TIM_CHANNEL_2, HAL_LL_TIM_REMAP | HAL_LL_TIM1_GPIO_AF_FULL_REMAP, hal_ll_tim_module_num(TIM_MODULE_1)},
    #endif
    #ifdef TIMER1_CH3_PB11_REMAP_FULL
    {PB11, HAL_LL_TIM1_BASE_ADDR, HAL_LL_TIM_CHANNEL_3, HAL_LL_TIM_REMAP | HAL_LL_TIM1_GPIO_AF_FULL_REMAP, hal_ll_tim_module_num(TIM_MODULE_1)},
    #endif
    #ifdef TIMER0_CH0_PB13_REMAP_NONE
    {PB13, HAL_LL_TIM0_BASE_ADDR, HAL_LL_TIM_CHANNEL_0, HAL_LL_TIM_GPIO_AF_NO_REMAP, hal_ll_tim_module_num(TIM_MODULE_0)},
    #endif
    #ifdef TIMER0_CH0_ON_PB13_INVERTED_REMAP_NONE
    {PB13, HAL_LL_TIM0_BASE_ADDR, HAL_LL_TIM_CHANNEL_0N, HAL_LL_TIM_GPIO_AF_NO_REMAP, hal_ll_tim_module_num(TIM_MODULE_0)},
    #endif
    #ifdef TIMER0_CH1_PB14_REMAP_NONE
    {PB14, HAL_LL_TIM0_BASE_ADDR, HAL_LL_TIM_CHANNEL_1, HAL_LL_TIM_GPIO_AF_NO_REMAP, hal_ll_tim_module_num(TIM_MODULE_0)},
    #endif
    #ifdef TIMER0_CH1_ON_PB14_INVERTED_REMAP_NONE
    {PB14, HAL_LL_TIM0_BASE_ADDR, HAL_LL_TIM_CHANNEL_1N, HAL_LL_TIM_GPIO_AF_NO_REMAP, hal_ll_tim_module_num(TIM_MODULE_0)},
    #endif
    #ifdef TIMER0_CH2_PB15_REMAP_NONE
    {PB15, HAL_LL_TIM0_BASE_ADDR, HAL_LL_TIM_CHANNEL_2, HAL_LL_TIM_GPIO_AF_NO_REMAP, hal_ll_tim_module_num(TIM_MODULE_0)},
    #endif
    #ifdef TIMER0_CH2_ON_PB15_INVERTED_REMAP_NONE
    {PB15, HAL_LL_TIM0_BASE_ADDR, HAL_LL_TIM_CHANNEL_2N, HAL_LL_TIM_GPIO_AF_NO_REMAP, hal_ll_tim_module_num(TIM_MODULE_0)},
    #endif
    #ifdef TIMER0_CH0_PA8_REMAP_NONE
    {PA8, HAL_LL_TIM0_BASE_ADDR, HAL_LL_TIM_CHANNEL_0, HAL_LL_TIM_GPIO_AF_NO_REMAP, hal_ll_tim_module_num(TIM_MODULE_0)},
    #endif
    #ifdef TIMER0_CH1_PA9_REMAP_NONE
    {PA9, HAL_LL_TIM0_BASE_ADDR, HAL_LL_TIM_CHANNEL_1, HAL_LL_TIM_GPIO_AF_NO_REMAP, hal_ll_tim_module_num(TIM_MODULE_0)},
    #endif
    #ifdef TIMER0_CH2_PA10_REMAP_NONE
    {PA10, HAL_LL_TIM0_BASE_ADDR, HAL_LL_TIM_CHANNEL_2, HAL_LL_TIM_GPIO_AF_NO_REMAP, hal_ll_tim_module_num(TIM_MODULE_0)},
    #endif
    #ifdef TIMER0_CH3_PA11_REMAP_NONE
    {PA11, HAL_LL_TIM0_BASE_ADDR, HAL_LL_TIM_CHANNEL_3, HAL_LL_TIM_GPIO_AF_NO_REMAP, hal_ll_tim_module_num(TIM_MODULE_0)},
    #endif
    #ifdef TIMER1_CH0_PA15_REMAP_NONE
    {PA15, HAL_LL_TIM1_BASE_ADDR, HAL_LL_TIM_CHANNEL_0, HAL_LL_TIM_GPIO_AF_NO_REMAP, hal_ll_tim_module_num(TIM_MODULE_1)},
    #endif
    #ifdef TIMER1_CH1_PB3_REMAP_PARTIAL
    {PB3, HAL_LL_TIM1_BASE_ADDR, HAL_LL_TIM_CHANNEL_1, HAL_LL_TIM_REMAP | HAL_LL_TIM1_GPIO_AF_PARTIAL_REMAP, hal_ll_tim_module_num(TIM_MODULE_1)},
    #endif
    #ifdef TIMER2_CH0_PB4_REMAP_PARTIAL
    {PB4, HAL_LL_TIM2_BASE_ADDR, HAL_LL_TIM_CHANNEL_0, HAL_LL_TIM_REMAP | HAL_LL_TIM2_GPIO_AF_PARTIAL_REMAP, hal_ll_tim_module_num(TIM_MODULE_2)},
    #endif
    #ifdef TIMER2_CH1_PB5_REMAP_PARTIAL
    {PB5, HAL_LL_TIM2_BASE_ADDR, HAL_LL_TIM_CHANNEL_1, HAL_LL_TIM_REMAP | HAL_LL_TIM2_GPIO_AF_PARTIAL_REMAP, hal_ll_tim_module_num(TIM_MODULE_2)},
    #endif
    #ifdef TIMER4_CH0_PA0_REMAP_NONE
    {PA0, HAL_LL_TIM4_BASE_ADDR, HAL_LL_TIM_CHANNEL_0, HAL_LL_TIM_GPIO_AF_NO_REMAP, hal_ll_tim_module_num(TIM_MODULE_4)},
    #endif
    #ifdef TIMER4_CH1_PA1_REMAP_NONE
    {PA1, HAL_LL_TIM4_BASE_ADDR, HAL_LL_TIM_CHANNEL_1, HAL_LL_TIM_GPIO_AF_NO_REMAP, hal_ll_tim_module_num(TIM_MODULE_4)},
    #endif
    #ifdef TIMER4_CH2_PA2_REMAP_NONE
    {PA2, HAL_LL_TIM4_BASE_ADDR, HAL_LL_TIM_CHANNEL_2, HAL_LL_TIM_GPIO_AF_NO_REMAP, hal_ll_tim_module_num(TIM_MODULE_4)},
    #endif
    #ifdef TIMER4_CH3_PA3_REMAP_NONE
    {PA3, HAL_LL_TIM4_BASE_ADDR, HAL_LL_TIM_CHANNEL_3, HAL_LL_TIM_GPIO_AF_NO_REMAP, hal_ll_tim_module_num(TIM_MODULE_4)},
    #endif
    #ifdef TIMER3_CH0_PB6_REMAP_NONE
    {PB6, HAL_LL_TIM3_BASE_ADDR, HAL_LL_TIM_CHANNEL_0, HAL_LL_TIM_GPIO_AF_NO_REMAP, hal_ll_tim_module_num(TIM_MODULE_3)},
    #endif
    #ifdef TIMER3_CH1_PB7_REMAP_NONE
    {PB7, HAL_LL_TIM3_BASE_ADDR, HAL_LL_TIM_CHANNEL_1, HAL_LL_TIM_GPIO_AF_NO_REMAP, hal_ll_tim_module_num(TIM_MODULE_3)},
    #endif
    #ifdef TIMER3_CH2_PB8_REMAP_NONE
    {PB8, HAL_LL_TIM3_BASE_ADDR, HAL_LL_TIM_CHANNEL_2, HAL_LL_TIM_GPIO_AF_NO_REMAP, hal_ll_tim_module_num(TIM_MODULE_3)},
    #endif
    #ifdef TIMER3_CH3_PB9_REMAP_NONE
    {PB9, HAL_LL_TIM3_BASE_ADDR, HAL_LL_TIM_CHANNEL_3, HAL_LL_TIM_GPIO_AF_NO_REMAP, hal_ll_tim_module_num(TIM_MODULE_3)},
    #endif
    #ifdef TIMER2_CH0_PC6_REMAP_FULL
    {PC6, HAL_LL_TIM2_BASE_ADDR, HAL_LL_TIM_CHANNEL_0, HAL_LL_TIM_REMAP | HAL_LL_TIM2_GPIO_AF_FULL_REMAP, hal_ll_tim_module_num(TIM_MODULE_2)},
    #endif
    #ifdef TIMER2_CH1_PC7_REMAP_FULL
    {PC7, HAL_LL_TIM2_BASE_ADDR, HAL_LL_TIM_CHANNEL_1, HAL_LL_TIM_REMAP | HAL_LL_TIM2_GPIO_AF_FULL_REMAP, hal_ll_tim_module_num(TIM_MODULE_2)},
    #endif
    #ifdef TIMER2_CH2_PC8_REMAP_FULL
    {PC8, HAL_LL_TIM2_BASE_ADDR, HAL_LL_TIM_CHANNEL_2, HAL_LL_TIM_REMAP | HAL_LL_TIM2_GPIO_AF_FULL_REMAP, hal_ll_tim_module_num(TIM_MODULE_2)},
    #endif
    #ifdef TIMER2_CH3_PC9_REMAP_FULL
    {PC9, HAL_LL_TIM2_BASE_ADDR, HAL_LL_TIM_CHANNEL_3, HAL_LL_TIM_REMAP | HAL_LL_TIM2_GPIO_AF_FULL_REMAP, hal_ll_tim_module_num(TIM_MODULE_2)},
    #endif
    #ifdef TIMER0_CH0_PE8_REMAP_FULL
    {PE8, HAL_LL_TIM0_BASE_ADDR, HAL_LL_TIM_CHANNEL_0, HAL_LL_TIM_REMAP | HAL_LL_TIM0_GPIO_AF_FULL_REMAP, hal_ll_tim_module_num(TIM_MODULE_0)},
    #endif
    #ifdef TIMER0_CH0_ON_PE8_INVERTED_REMAP_NONE
    {PE8, HAL_LL_TIM0_BASE_ADDR, HAL_LL_TIM_CHANNEL_0N, HAL_LL_TIM_GPIO_AF_NO_REMAP, hal_ll_tim_module_num(TIM_MODULE_0)},
    #endif
    #ifdef TIMER0_CH0_PE9_REMAP_FULL
    {PE9, HAL_LL_TIM0_BASE_ADDR, HAL_LL_TIM_CHANNEL_0, HAL_LL_TIM_REMAP | HAL_LL_TIM0_GPIO_AF_FULL_REMAP, hal_ll_tim_module_num(TIM_MODULE_0)},
    #endif
    #ifdef TIMER0_CH1_PE10_REMAP_FULL
    {PE10, HAL_LL_TIM0_BASE_ADDR, HAL_LL_TIM_CHANNEL_1, HAL_LL_TIM_REMAP | HAL_LL_TIM0_GPIO_AF_FULL_REMAP, hal_ll_tim_module_num(TIM_MODULE_0)},
    #endif
    #ifdef TIMER0_CH1_ON_PE10_INVERTED_REMAP_NONE
    {PE10, HAL_LL_TIM0_BASE_ADDR, HAL_LL_TIM_CHANNEL_1N, HAL_LL_TIM_GPIO_AF_NO_REMAP, hal_ll_tim_module_num(TIM_MODULE_0)},
    #endif
    #ifdef TIMER0_CH1_PE11_REMAP_FULL
    {PE11, HAL_LL_TIM0_BASE_ADDR, HAL_LL_TIM_CHANNEL_1, HAL_LL_TIM_REMAP | HAL_LL_TIM0_GPIO_AF_FULL_REMAP, hal_ll_tim_module_num(TIM_MODULE_0)},
    #endif
    #ifdef TIMER0_CH2_PE12_REMAP_FULL
    {PE12, HAL_LL_TIM0_BASE_ADDR, HAL_LL_TIM_CHANNEL_2, HAL_LL_TIM_REMAP | HAL_LL_TIM0_GPIO_AF_FULL_REMAP, hal_ll_tim_module_num(TIM_MODULE_0)},
    #endif
    #ifdef TIMER0_CH2_ON_PE12_INVERTED_REMAP_NONE
    {PE12, HAL_LL_TIM0_BASE_ADDR, HAL_LL_TIM_CHANNEL_2N, HAL_LL_TIM_GPIO_AF_NO_REMAP, hal_ll_tim_module_num(TIM_MODULE_0)},
    #endif
    #ifdef TIMER0_CH2_PE13_REMAP_FULL
    {PE13, HAL_LL_TIM0_BASE_ADDR, HAL_LL_TIM_CHANNEL_2, HAL_LL_TIM_REMAP | HAL_LL_TIM0_GPIO_AF_FULL_REMAP, hal_ll_tim_module_num(TIM_MODULE_0)},
    #endif
    #ifdef TIMER0_CH3_PE14_REMAP_FULL
    {PE14, HAL_LL_TIM0_BASE_ADDR, HAL_LL_TIM_CHANNEL_3, HAL_LL_TIM_REMAP | HAL_LL_TIM0_GPIO_AF_FULL_REMAP, hal_ll_tim_module_num(TIM_MODULE_0)},
    #endif
    #ifdef TIMER3_CH0_PD12_REMAP_FULL
    {PD12, HAL_LL_TIM3_BASE_ADDR, HAL_LL_TIM_CHANNEL_0, HAL_LL_TIM_REMAP | HAL_LL_TIM3_GPIO_AF_FULL_REMAP, hal_ll_tim_module_num(TIM_MODULE_3)},
    #endif
    #ifdef TIMER3_CH1_PD13_REMAP_FULL
    {PD13, HAL_LL_TIM3_BASE_ADDR, HAL_LL_TIM_CHANNEL_1, HAL_LL_TIM_REMAP | HAL_LL_TIM3_GPIO_AF_FULL_REMAP, hal_ll_tim_module_num(TIM_MODULE_3)},
    #endif
    #ifdef TIMER3_CH2_PD14_REMAP_FULL
    {PD14, HAL_LL_TIM3_BASE_ADDR, HAL_LL_TIM_CHANNEL_2, HAL_LL_TIM_REMAP | HAL_LL_TIM3_GPIO_AF_FULL_REMAP, hal_ll_tim_module_num(TIM_MODULE_3)},
    #endif
    #ifdef TIMER3_CH3_PD15_REMAP_FULL
    {PD15, HAL_LL_TIM3_BASE_ADDR, HAL_LL_TIM_CHANNEL_3, HAL_LL_TIM_REMAP | HAL_LL_TIM3_GPIO_AF_FULL_REMAP, hal_ll_tim_module_num(TIM_MODULE_3)},
    #endif

    { HAL_LL_PIN_NC, HAL_LL_MODULE_ERROR, HAL_LL_PIN_NC, HAL_LL_MODULE_ERROR, HAL_LL_PIN_NC }
};

#ifdef __cplusplus
}
#endif

#endif // _HAL_LL_TIM_PIN_MAP_H_
// ------------------------------------------------------------------------- END
