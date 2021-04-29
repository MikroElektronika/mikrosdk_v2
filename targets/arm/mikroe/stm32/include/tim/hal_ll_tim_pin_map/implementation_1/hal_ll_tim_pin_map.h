/****************************************************************************
**
** Copyright (C) 2021 MikroElektronika d.o.o.
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

#define CAPTURE_COMPARE_COMPLEMENTARY_OUTPUT

/*!< @brief Macro defining `weak` attribute */
#define __weak __attribute__((weak))

/*!< Abbreviations used in source. */
typedef uint32_t 			hal_ll_tim_gpio_af_t;

/*!< @brief Alternate pin function structure. */
typedef struct
{
	hal_ll_pin_name_t   pin;
	hal_ll_base_addr_t  base;
	hal_ll_channel_t    channel;
	uint32_t            af;
    hal_ll_pin_name_t   module_index;
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

/*!< TIM module base addresses. */
#ifdef TIM_MODULE_1
static const hal_ll_base_addr_t HAL_LL_TIM1_BASE_ADDR = 0x40010000;
#endif
#ifdef TIM_MODULE_2
static const hal_ll_base_addr_t HAL_LL_TIM2_BASE_ADDR = 0x40000000;
#endif
#ifdef TIM_MODULE_3
static const hal_ll_base_addr_t HAL_LL_TIM3_BASE_ADDR = 0x40000400;
#endif
#ifdef TIM_MODULE_4
static const hal_ll_base_addr_t HAL_LL_TIM4_BASE_ADDR = 0x40000800;
#endif
#ifdef TIM_MODULE_5
static const hal_ll_base_addr_t HAL_LL_TIM5_BASE_ADDR = 0x40000C00;
#endif
#ifdef TIM_MODULE_8
static const hal_ll_base_addr_t HAL_LL_TIM8_BASE_ADDR = 0x40010400;
#endif
#ifdef TIM_MODULE_9
#if defined(STM32L1xx)
static const hal_ll_base_addr_t HAL_LL_TIM9_BASE_ADDR = 0x40010800;
#else
static const hal_ll_base_addr_t HAL_LL_TIM9_BASE_ADDR = 0x40014000;
#endif
#endif
#ifdef TIM_MODULE_10
#if defined(STM32L1xx)
static const hal_ll_base_addr_t HAL_LL_TIM10_BASE_ADDR = 0x40010C00;
#else
static const hal_ll_base_addr_t HAL_LL_TIM10_BASE_ADDR = 0x40014400;
#endif
#endif
#ifdef TIM_MODULE_11
#if defined(STM32L1xx)
static const hal_ll_base_addr_t HAL_LL_TIM11_BASE_ADDR = 0x40011000;
#else
static const hal_ll_base_addr_t HAL_LL_TIM11_BASE_ADDR = 0x40014800;
#endif
#endif
#ifdef TIM_MODULE_12
static const hal_ll_base_addr_t HAL_LL_TIM12_BASE_ADDR = 0x40001800;
#endif
#ifdef TIM_MODULE_13
static const hal_ll_base_addr_t HAL_LL_TIM13_BASE_ADDR = 0x40001C00;
#endif
#ifdef TIM_MODULE_14
static const hal_ll_base_addr_t HAL_LL_TIM14_BASE_ADDR = 0x40002000;
#endif
#ifdef TIM_MODULE_15
static const hal_ll_base_addr_t HAL_LL_TIM15_BASE_ADDR = 0x40014000;
#endif
#ifdef TIM_MODULE_16
static const hal_ll_base_addr_t HAL_LL_TIM16_BASE_ADDR = 0x40014400;
#endif
#ifdef TIM_MODULE_17
static const hal_ll_base_addr_t HAL_LL_TIM17_BASE_ADDR = 0x40014800;
#endif

/*!< TIM modules. */
#ifdef TIM_MODULE_1
static const hal_ll_tim_gpio_af_t HAL_LL_TIM1_GPIO_AF1 = 1;
#endif
#ifdef TIM_MODULE_2
static const hal_ll_tim_gpio_af_t HAL_LL_TIM2_GPIO_AF1 = 1;
#endif
#ifdef TIM_MODULE_3
static const hal_ll_tim_gpio_af_t HAL_LL_TIM3_GPIO_AF2 = 2;
#endif
#ifdef TIM_MODULE_4
static const hal_ll_tim_gpio_af_t HAL_LL_TIM4_GPIO_AF2 = 2;
#endif
#ifdef TIM_MODULE_5
static const hal_ll_tim_gpio_af_t HAL_LL_TIM5_GPIO_AF2 = 2;
#endif
#ifdef TIM_MODULE_8
static const hal_ll_tim_gpio_af_t HAL_LL_TIM8_GPIO_AF3 = 3;
#endif
#ifdef TIM_MODULE_9
static const hal_ll_tim_gpio_af_t HAL_LL_TIM9_GPIO_AF3 = 3;
#endif
#ifdef TIM_MODULE_10
static const hal_ll_tim_gpio_af_t HAL_LL_TIM10_GPIO_AF3 = 3;
#endif
#ifdef TIM_MODULE_11
static const hal_ll_tim_gpio_af_t HAL_LL_TIM11_GPIO_AF3 = 3;
#endif
#ifdef TIM_MODULE_12
static const hal_ll_tim_gpio_af_t HAL_LL_TIM12_GPIO_AF2 = 2;
static const hal_ll_tim_gpio_af_t HAL_LL_TIM12_GPIO_AF9 = 9;
#endif
#ifdef TIM_MODULE_13
static const hal_ll_tim_gpio_af_t HAL_LL_TIM13_GPIO_AF9 = 9;
#endif
#ifdef TIM_MODULE_14
static const hal_ll_tim_gpio_af_t HAL_LL_TIM14_GPIO_AF9 = 9;
#endif
#ifdef TIM_MODULE_15
static const hal_ll_tim_gpio_af_t HAL_LL_TIM15_GPIO_AF4 = 4;
#endif
#ifdef TIM_MODULE_16
static const hal_ll_tim_gpio_af_t HAL_LL_TIM16_GPIO_AF1 = 1;
#endif
#ifdef TIM_MODULE_17
static const hal_ll_tim_gpio_af_t HAL_LL_TIM17_GPIO_AF1 = 1;
#endif

/*!< TIM pins. */
__weak static const hal_ll_tim_pin_map_t _tim_map[] = {
    #ifdef TIM_MODULE_1
    #ifdef TIM1_CH1_PA8_AF1
    {PA8, HAL_LL_TIM1_BASE_ADDR, HAL_LL_TIM_CHANNEL_1, HAL_LL_TIM1_GPIO_AF1, hal_ll_tim_module_num(TIM_MODULE_1)},
    #endif
    #ifdef TIM1_CH1_PE9_AF1
    {PE9, HAL_LL_TIM1_BASE_ADDR, HAL_LL_TIM_CHANNEL_1, HAL_LL_TIM1_GPIO_AF1, hal_ll_tim_module_num(TIM_MODULE_1)},
    #endif
    #ifdef TIM1_CH1_PK1_AF1
    {PK1, HAL_LL_TIM1_BASE_ADDR, HAL_LL_TIM_CHANNEL_1, HAL_LL_TIM1_GPIO_AF1, hal_ll_tim_module_num(TIM_MODULE_1)},
    #endif
    #ifdef TIM1_CH2_PA9_AF1
    {PA9, HAL_LL_TIM1_BASE_ADDR, HAL_LL_TIM_CHANNEL_2, HAL_LL_TIM1_GPIO_AF1, hal_ll_tim_module_num(TIM_MODULE_1)},
    #endif
    #ifdef TIM1_CH2_PE11_AF1
    {PE11, HAL_LL_TIM1_BASE_ADDR, HAL_LL_TIM_CHANNEL_2, HAL_LL_TIM1_GPIO_AF1, hal_ll_tim_module_num(TIM_MODULE_1)},
    #endif
    #ifdef TIM1_CH2_PJ11_AF1
    {PJ11, HAL_LL_TIM1_BASE_ADDR, HAL_LL_TIM_CHANNEL_2, HAL_LL_TIM1_GPIO_AF1, hal_ll_tim_module_num(TIM_MODULE_1)},
    #endif
    #ifdef TIM1_CH3_PA10_AF1
    {PA10, HAL_LL_TIM1_BASE_ADDR, HAL_LL_TIM_CHANNEL_3, HAL_LL_TIM1_GPIO_AF1, hal_ll_tim_module_num(TIM_MODULE_1)},
    #endif
    #ifdef TIM1_CH3_PE13_AF1
    {PE13, HAL_LL_TIM1_BASE_ADDR, HAL_LL_TIM_CHANNEL_3, HAL_LL_TIM1_GPIO_AF1, hal_ll_tim_module_num(TIM_MODULE_1)},
    #endif
    #ifdef TIM1_CH3_PJ9_AF1
    {PJ9, HAL_LL_TIM1_BASE_ADDR, HAL_LL_TIM_CHANNEL_3, HAL_LL_TIM1_GPIO_AF1, hal_ll_tim_module_num(TIM_MODULE_1)},
    #endif
    #ifdef TIM1_CH4_PA11_AF1
    {PA11, HAL_LL_TIM1_BASE_ADDR, HAL_LL_TIM_CHANNEL_4, HAL_LL_TIM1_GPIO_AF1, hal_ll_tim_module_num(TIM_MODULE_1)},
    #endif
    #ifdef TIM1_CH4_PE14_AF1
    {PE14, HAL_LL_TIM1_BASE_ADDR, HAL_LL_TIM_CHANNEL_4, HAL_LL_TIM1_GPIO_AF1, hal_ll_tim_module_num(TIM_MODULE_1)},
    #endif
    #endif

   	#ifdef TIM_MODULE_2
    #ifdef TIM2_CH1_PA0_AF1
    {PA0, HAL_LL_TIM2_BASE_ADDR, HAL_LL_TIM_CHANNEL_1, HAL_LL_TIM2_GPIO_AF1, hal_ll_tim_module_num(TIM_MODULE_2)},
    #endif
    #ifdef TIM2_CH1_PA15_AF1
    {PA15, HAL_LL_TIM2_BASE_ADDR, HAL_LL_TIM_CHANNEL_1, HAL_LL_TIM2_GPIO_AF1, hal_ll_tim_module_num(TIM_MODULE_2)},
    #endif
    #ifdef TIM2_CH1_PA5_AF1
    {PA5, HAL_LL_TIM2_BASE_ADDR, HAL_LL_TIM_CHANNEL_1, HAL_LL_TIM2_GPIO_AF1, hal_ll_tim_module_num(TIM_MODULE_2)},
    #endif
    #ifdef TIM2_CH1_PB8_AF1
    {PB8, HAL_LL_TIM2_BASE_ADDR, HAL_LL_TIM_CHANNEL_1, HAL_LL_TIM2_GPIO_AF1, hal_ll_tim_module_num(TIM_MODULE_2)},
    #endif
    #ifdef TIM2_CH1_PE9_AF1
    {PE9, HAL_LL_TIM2_BASE_ADDR, HAL_LL_TIM_CHANNEL_1, HAL_LL_TIM2_GPIO_AF1, hal_ll_tim_module_num(TIM_MODULE_2)},
    #endif
    #ifdef TIM2_CH2_PA1_AF1
    {PA1, HAL_LL_TIM2_BASE_ADDR, HAL_LL_TIM_CHANNEL_2, HAL_LL_TIM2_GPIO_AF1, hal_ll_tim_module_num(TIM_MODULE_2)},
    #endif
    #ifdef TIM2_CH2_PB3_AF1
    {PB3, HAL_LL_TIM2_BASE_ADDR, HAL_LL_TIM_CHANNEL_2, HAL_LL_TIM2_GPIO_AF1, hal_ll_tim_module_num(TIM_MODULE_2)},
    #endif
    #ifdef TIM2_CH2_PB9_AF1
    {PB9, HAL_LL_TIM2_BASE_ADDR, HAL_LL_TIM_CHANNEL_2, HAL_LL_TIM2_GPIO_AF1, hal_ll_tim_module_num(TIM_MODULE_2)},
    #endif
    #ifdef TIM2_CH2_PE10_AF1
    {PE10, HAL_LL_TIM2_BASE_ADDR, HAL_LL_TIM_CHANNEL_2, HAL_LL_TIM2_GPIO_AF1, hal_ll_tim_module_num(TIM_MODULE_2)},
    #endif
    #ifdef TIM2_CH3_PA2_AF1
    {PA2, HAL_LL_TIM2_BASE_ADDR, HAL_LL_TIM_CHANNEL_3, HAL_LL_TIM2_GPIO_AF1, hal_ll_tim_module_num(TIM_MODULE_2)},
    #endif
    #ifdef TIM2_CH3_PB10_AF1
    {PB10, HAL_LL_TIM2_BASE_ADDR, HAL_LL_TIM_CHANNEL_3, HAL_LL_TIM2_GPIO_AF1, hal_ll_tim_module_num(TIM_MODULE_2)},
    #endif
    #ifdef TIM2_CH3_PE11_AF1
    {PE11, HAL_LL_TIM2_BASE_ADDR, HAL_LL_TIM_CHANNEL_3, HAL_LL_TIM2_GPIO_AF1, hal_ll_tim_module_num(TIM_MODULE_2)},
    #endif
    #ifdef TIM2_CH4_PA3_AF1
    {PA3, HAL_LL_TIM2_BASE_ADDR, HAL_LL_TIM_CHANNEL_4, HAL_LL_TIM2_GPIO_AF1, hal_ll_tim_module_num(TIM_MODULE_2)},
    #endif
    #ifdef TIM2_CH4_PB11_AF1
    {PB11, HAL_LL_TIM2_BASE_ADDR, HAL_LL_TIM_CHANNEL_4, HAL_LL_TIM2_GPIO_AF1, hal_ll_tim_module_num(TIM_MODULE_2)},
    #endif
    #ifdef TIM2_CH4_PB2_AF1
    {PB2, HAL_LL_TIM2_BASE_ADDR, HAL_LL_TIM_CHANNEL_4, HAL_LL_TIM2_GPIO_AF1, hal_ll_tim_module_num(TIM_MODULE_2)},
    #endif
    #ifdef TIM2_CH4_PE12_AF1
    {PE12, HAL_LL_TIM2_BASE_ADDR, HAL_LL_TIM_CHANNEL_4, HAL_LL_TIM2_GPIO_AF1, hal_ll_tim_module_num(TIM_MODULE_2)},
    #endif
	#endif

	#ifdef TIM_MODULE_3
    #ifdef TIM3_CH1_PA6_AF2
    {PA6, HAL_LL_TIM3_BASE_ADDR, HAL_LL_TIM_CHANNEL_1, HAL_LL_TIM3_GPIO_AF2, hal_ll_tim_module_num(TIM_MODULE_3)},
    #endif
    #ifdef TIM3_CH1_PB4_AF2
    {PB4, HAL_LL_TIM3_BASE_ADDR, HAL_LL_TIM_CHANNEL_1, HAL_LL_TIM3_GPIO_AF2, hal_ll_tim_module_num(TIM_MODULE_3)},
    #endif
    #ifdef TIM3_CH1_PC6_AF2
    {PC6, HAL_LL_TIM3_BASE_ADDR, HAL_LL_TIM_CHANNEL_1, HAL_LL_TIM3_GPIO_AF2, hal_ll_tim_module_num(TIM_MODULE_3)},
    #endif
    #ifdef TIM3_CH1_PE3_AF2
    {PE3, HAL_LL_TIM3_BASE_ADDR, HAL_LL_TIM_CHANNEL_1, HAL_LL_TIM3_GPIO_AF2, hal_ll_tim_module_num(TIM_MODULE_3)},
    #endif
    #ifdef TIM3_CH2_PA7_AF2
    {PA7, HAL_LL_TIM3_BASE_ADDR, HAL_LL_TIM_CHANNEL_2, HAL_LL_TIM3_GPIO_AF2, hal_ll_tim_module_num(TIM_MODULE_3)},
    #endif
    #ifdef TIM3_CH2_PB5_AF2
    {PB5, HAL_LL_TIM3_BASE_ADDR, HAL_LL_TIM_CHANNEL_2, HAL_LL_TIM3_GPIO_AF2, hal_ll_tim_module_num(TIM_MODULE_3)},
    #endif
    #ifdef TIM3_CH2_PC7_AF2
    {PC7, HAL_LL_TIM3_BASE_ADDR, HAL_LL_TIM_CHANNEL_2, HAL_LL_TIM3_GPIO_AF2, hal_ll_tim_module_num(TIM_MODULE_3)},
    #endif
    #ifdef TIM3_CH2_PE4_AF2
    {PE4, HAL_LL_TIM3_BASE_ADDR, HAL_LL_TIM_CHANNEL_2, HAL_LL_TIM3_GPIO_AF2, hal_ll_tim_module_num(TIM_MODULE_3)},
    #endif
    #ifdef TIM3_CH3_PB0_AF2
    {PB0, HAL_LL_TIM3_BASE_ADDR, HAL_LL_TIM_CHANNEL_3, HAL_LL_TIM3_GPIO_AF2, hal_ll_tim_module_num(TIM_MODULE_3)},
    #endif
    #ifdef TIM3_CH3_PC8_AF2
    {PC8, HAL_LL_TIM3_BASE_ADDR, HAL_LL_TIM_CHANNEL_3, HAL_LL_TIM3_GPIO_AF2, hal_ll_tim_module_num(TIM_MODULE_3)},
    #endif
    #ifdef TIM3_CH4_PB1_AF2
    {PB1, HAL_LL_TIM3_BASE_ADDR, HAL_LL_TIM_CHANNEL_4, HAL_LL_TIM3_GPIO_AF2, hal_ll_tim_module_num(TIM_MODULE_3)},
    #endif
    #ifdef TIM3_CH4_PC9_AF2
    {PC9, HAL_LL_TIM3_BASE_ADDR, HAL_LL_TIM_CHANNEL_4, HAL_LL_TIM3_GPIO_AF2, hal_ll_tim_module_num(TIM_MODULE_3)},
    #endif
	#endif

	#ifdef TIM_MODULE_4
    #ifdef TIM4_CH1_PB6_AF2
    {PB6, HAL_LL_TIM4_BASE_ADDR, HAL_LL_TIM_CHANNEL_1, HAL_LL_TIM4_GPIO_AF2, hal_ll_tim_module_num(TIM_MODULE_4)},
    #endif
    #ifdef TIM4_CH1_PD12_AF2
    {PD12, HAL_LL_TIM4_BASE_ADDR, HAL_LL_TIM_CHANNEL_1, HAL_LL_TIM4_GPIO_AF2, hal_ll_tim_module_num(TIM_MODULE_4)},
    #endif
    #ifdef TIM4_CH2_PB7_AF2
    {PB7, HAL_LL_TIM4_BASE_ADDR, HAL_LL_TIM_CHANNEL_2, HAL_LL_TIM4_GPIO_AF2, hal_ll_tim_module_num(TIM_MODULE_4)},
    #endif
    #ifdef TIM4_CH2_PD13_AF2
    {PD13, HAL_LL_TIM4_BASE_ADDR, HAL_LL_TIM_CHANNEL_2, HAL_LL_TIM4_GPIO_AF2, hal_ll_tim_module_num(TIM_MODULE_4)},
    #endif
    #ifdef TIM4_CH3_PB8_AF2
    {PB8, HAL_LL_TIM4_BASE_ADDR, HAL_LL_TIM_CHANNEL_3, HAL_LL_TIM4_GPIO_AF2, hal_ll_tim_module_num(TIM_MODULE_4)},
    #endif
    #ifdef TIM4_CH3_PD14_AF2
    {PD14, HAL_LL_TIM4_BASE_ADDR, HAL_LL_TIM_CHANNEL_3, HAL_LL_TIM4_GPIO_AF2, hal_ll_tim_module_num(TIM_MODULE_4)},
    #endif
    #ifdef TIM4_CH4_PB9_AF2
    {PB9, HAL_LL_TIM4_BASE_ADDR, HAL_LL_TIM_CHANNEL_4, HAL_LL_TIM4_GPIO_AF2, hal_ll_tim_module_num(TIM_MODULE_4)},
    #endif
    #ifdef TIM4_CH4_PD15_AF2
    {PD15, HAL_LL_TIM4_BASE_ADDR, HAL_LL_TIM_CHANNEL_4, HAL_LL_TIM4_GPIO_AF2, hal_ll_tim_module_num(TIM_MODULE_4)},
    #endif
	#endif

	#ifdef TIM_MODULE_5
    #ifdef TIM5_CH1_PA0_AF2
    {PA0, HAL_LL_TIM5_BASE_ADDR, HAL_LL_TIM_CHANNEL_1, HAL_LL_TIM5_GPIO_AF2, hal_ll_tim_module_num(TIM_MODULE_5)},
    #endif
    #ifdef TIM5_CH1_PB12_AF2
    {PB12, HAL_LL_TIM5_BASE_ADDR, HAL_LL_TIM_CHANNEL_1, HAL_LL_TIM5_GPIO_AF2, hal_ll_tim_module_num(TIM_MODULE_5)},
    #endif
    #ifdef TIM5_CH1_PF3_AF2
    {PF3, HAL_LL_TIM5_BASE_ADDR, HAL_LL_TIM_CHANNEL_1, HAL_LL_TIM5_GPIO_AF2, hal_ll_tim_module_num(TIM_MODULE_5)},
    #endif
    #ifdef TIM5_CH1_PF6_AF2
    {PF6, HAL_LL_TIM5_BASE_ADDR, HAL_LL_TIM_CHANNEL_1, HAL_LL_TIM5_GPIO_AF2, hal_ll_tim_module_num(TIM_MODULE_5)},
    #endif
    #ifdef TIM5_CH1_PH10_AF2
    {PH10, HAL_LL_TIM5_BASE_ADDR, HAL_LL_TIM_CHANNEL_1, HAL_LL_TIM5_GPIO_AF2, hal_ll_tim_module_num(TIM_MODULE_5)},
    #endif
    #ifdef TIM5_CH2_PA1_AF2
    {PA1, HAL_LL_TIM5_BASE_ADDR, HAL_LL_TIM_CHANNEL_2, HAL_LL_TIM5_GPIO_AF2, hal_ll_tim_module_num(TIM_MODULE_5)},
    #endif
    #ifdef TIM5_CH2_PC10_AF2
    {PC10, HAL_LL_TIM5_BASE_ADDR, HAL_LL_TIM_CHANNEL_2, HAL_LL_TIM5_GPIO_AF2, hal_ll_tim_module_num(TIM_MODULE_5)},
    #endif
    #ifdef TIM5_CH2_PF4_AF2
    {PF4, HAL_LL_TIM5_BASE_ADDR, HAL_LL_TIM_CHANNEL_2, HAL_LL_TIM5_GPIO_AF2, hal_ll_tim_module_num(TIM_MODULE_5)},
    #endif
    #ifdef TIM5_CH2_PF7_AF2
    {PF7, HAL_LL_TIM5_BASE_ADDR, HAL_LL_TIM_CHANNEL_2, HAL_LL_TIM5_GPIO_AF2, hal_ll_tim_module_num(TIM_MODULE_5)},
    #endif
    #ifdef TIM5_CH2_PH11_AF2
    {PH11, HAL_LL_TIM5_BASE_ADDR, HAL_LL_TIM_CHANNEL_2, HAL_LL_TIM5_GPIO_AF2, hal_ll_tim_module_num(TIM_MODULE_5)},
    #endif
    #ifdef TIM5_CH3_PA2_AF2
    {PA2, HAL_LL_TIM5_BASE_ADDR, HAL_LL_TIM_CHANNEL_3, HAL_LL_TIM5_GPIO_AF2, hal_ll_tim_module_num(TIM_MODULE_5)},
    #endif
    #ifdef TIM5_CH3_PC11_AF2
    {PC11, HAL_LL_TIM5_BASE_ADDR, HAL_LL_TIM_CHANNEL_3, HAL_LL_TIM5_GPIO_AF2, hal_ll_tim_module_num(TIM_MODULE_5)},
    #endif
    #ifdef TIM5_CH3_PF5_AF2
    {PF5, HAL_LL_TIM5_BASE_ADDR, HAL_LL_TIM_CHANNEL_3, HAL_LL_TIM5_GPIO_AF2, hal_ll_tim_module_num(TIM_MODULE_5)},
    #endif
    #ifdef TIM5_CH3_PF8_AF2
    {PF8, HAL_LL_TIM5_BASE_ADDR, HAL_LL_TIM_CHANNEL_3, HAL_LL_TIM5_GPIO_AF2, hal_ll_tim_module_num(TIM_MODULE_5)},
    #endif
    #ifdef TIM5_CH3_PH12_AF2
    {PH12, HAL_LL_TIM5_BASE_ADDR, HAL_LL_TIM_CHANNEL_3, HAL_LL_TIM5_GPIO_AF2, hal_ll_tim_module_num(TIM_MODULE_5)},
    #endif
    #ifdef TIM5_CH4_PA3_AF2
    {PA3, HAL_LL_TIM5_BASE_ADDR, HAL_LL_TIM_CHANNEL_4, HAL_LL_TIM5_GPIO_AF2, hal_ll_tim_module_num(TIM_MODULE_5)},
    #endif
    #ifdef TIM5_CH4_PB11_AF2
    {PB11, HAL_LL_TIM5_BASE_ADDR, HAL_LL_TIM_CHANNEL_4, HAL_LL_TIM5_GPIO_AF2, hal_ll_tim_module_num(TIM_MODULE_5)},
    #endif
    #ifdef TIM5_CH4_PF10_AF2
    {PF10, HAL_LL_TIM5_BASE_ADDR, HAL_LL_TIM_CHANNEL_4, HAL_LL_TIM5_GPIO_AF2, hal_ll_tim_module_num(TIM_MODULE_5)},
    #endif
    #ifdef TIM5_CH4_PF9_AF2
    {PF9, HAL_LL_TIM5_BASE_ADDR, HAL_LL_TIM_CHANNEL_4, HAL_LL_TIM5_GPIO_AF2, hal_ll_tim_module_num(TIM_MODULE_5)},
    #endif
    #ifdef TIM5_CH4_PI0_AF2
    {PI0, HAL_LL_TIM5_BASE_ADDR, HAL_LL_TIM_CHANNEL_4, HAL_LL_TIM5_GPIO_AF2, hal_ll_tim_module_num(TIM_MODULE_5)},
    #endif
	#endif

	#ifdef TIM_MODULE_8
    #ifdef TIM8_CH1_PC6_AF3
    {PC6, HAL_LL_TIM8_BASE_ADDR, HAL_LL_TIM_CHANNEL_1, HAL_LL_TIM8_GPIO_AF3, hal_ll_tim_module_num(TIM_MODULE_8)},
    #endif
    #ifdef TIM8_CH1_PI5_AF3
    {PI5, HAL_LL_TIM8_BASE_ADDR, HAL_LL_TIM_CHANNEL_1, HAL_LL_TIM8_GPIO_AF3, hal_ll_tim_module_num(TIM_MODULE_8)},
    #endif
    #ifdef TIM8_CH1_PJ8_AF3
    {PJ8, HAL_LL_TIM8_BASE_ADDR, HAL_LL_TIM_CHANNEL_1, HAL_LL_TIM8_GPIO_AF3, hal_ll_tim_module_num(TIM_MODULE_8)},
    #endif
    #ifdef TIM8_CH2_PC7_AF3
    {PC7, HAL_LL_TIM8_BASE_ADDR, HAL_LL_TIM_CHANNEL_2, HAL_LL_TIM8_GPIO_AF3, hal_ll_tim_module_num(TIM_MODULE_8)},
    #endif
    #ifdef TIM8_CH2_PI6_AF3
    {PI6, HAL_LL_TIM8_BASE_ADDR, HAL_LL_TIM_CHANNEL_2, HAL_LL_TIM8_GPIO_AF3, hal_ll_tim_module_num(TIM_MODULE_8)},
    #endif
    #ifdef TIM8_CH2_PJ10_AF3
    {PJ10, HAL_LL_TIM8_BASE_ADDR, HAL_LL_TIM_CHANNEL_2, HAL_LL_TIM8_GPIO_AF3, hal_ll_tim_module_num(TIM_MODULE_8)},
    #endif
    #ifdef TIM8_CH2_PJ6_AF3
    {PJ6, HAL_LL_TIM8_BASE_ADDR, HAL_LL_TIM_CHANNEL_2, HAL_LL_TIM8_GPIO_AF3, hal_ll_tim_module_num(TIM_MODULE_8)},
    #endif
    #ifdef TIM8_CH3_PC8_AF3
    {PC8, HAL_LL_TIM8_BASE_ADDR, HAL_LL_TIM_CHANNEL_3, HAL_LL_TIM8_GPIO_AF3, hal_ll_tim_module_num(TIM_MODULE_8)},
    #endif
    #ifdef TIM8_CH3_PI7_AF3
    {PI7, HAL_LL_TIM8_BASE_ADDR, HAL_LL_TIM_CHANNEL_3, HAL_LL_TIM8_GPIO_AF3, hal_ll_tim_module_num(TIM_MODULE_8)},
    #endif
    #ifdef TIM8_CH3_PK0_AF3
    {PK0, HAL_LL_TIM8_BASE_ADDR, HAL_LL_TIM_CHANNEL_3, HAL_LL_TIM8_GPIO_AF3, hal_ll_tim_module_num(TIM_MODULE_8)},
    #endif
    #ifdef TIM8_CH4_PC9_AF3
    {PC9, HAL_LL_TIM8_BASE_ADDR, HAL_LL_TIM_CHANNEL_4, HAL_LL_TIM8_GPIO_AF3, hal_ll_tim_module_num(TIM_MODULE_8)},
    #endif
    #ifdef TIM8_CH4_PI2_AF3
    {PI2, HAL_LL_TIM8_BASE_ADDR, HAL_LL_TIM_CHANNEL_4, HAL_LL_TIM8_GPIO_AF3, hal_ll_tim_module_num(TIM_MODULE_8)},
    #endif
	#endif

	#ifdef TIM_MODULE_9
    #ifdef TIM9_CH1_PA2_AF3
    {PA2, HAL_LL_TIM9_BASE_ADDR, HAL_LL_TIM_CHANNEL_1, HAL_LL_TIM9_GPIO_AF3, hal_ll_tim_module_num(TIM_MODULE_9)},
    #endif
    #ifdef TIM9_CH1_PB13_AF3
    {PB13, HAL_LL_TIM9_BASE_ADDR, HAL_LL_TIM_CHANNEL_1, HAL_LL_TIM9_GPIO_AF3, hal_ll_tim_module_num(TIM_MODULE_9)},
    #endif
    #ifdef TIM9_CH1_PC4_AF3
    {PC4, HAL_LL_TIM9_BASE_ADDR, HAL_LL_TIM_CHANNEL_1, HAL_LL_TIM9_GPIO_AF3, hal_ll_tim_module_num(TIM_MODULE_9)},
    #endif
    #ifdef TIM9_CH1_PD0_AF3
    {PD0, HAL_LL_TIM9_BASE_ADDR, HAL_LL_TIM_CHANNEL_1, HAL_LL_TIM9_GPIO_AF3, hal_ll_tim_module_num(TIM_MODULE_9)},
    #endif
    #ifdef TIM9_CH1_PE5_AF3
    {PE5, HAL_LL_TIM9_BASE_ADDR, HAL_LL_TIM_CHANNEL_1, HAL_LL_TIM9_GPIO_AF3, hal_ll_tim_module_num(TIM_MODULE_9)},
    #endif
    #ifdef TIM9_CH2_PA3_AF3
    {PA3, HAL_LL_TIM9_BASE_ADDR, HAL_LL_TIM_CHANNEL_2, HAL_LL_TIM9_GPIO_AF3, hal_ll_tim_module_num(TIM_MODULE_9)},
    #endif
    #ifdef TIM9_CH2_PB14_AF3
    {PB14, HAL_LL_TIM9_BASE_ADDR, HAL_LL_TIM_CHANNEL_2, HAL_LL_TIM9_GPIO_AF3, hal_ll_tim_module_num(TIM_MODULE_9)},
    #endif
    #ifdef TIM9_CH2_PC5_AF3
    {PC5, HAL_LL_TIM9_BASE_ADDR, HAL_LL_TIM_CHANNEL_2, HAL_LL_TIM9_GPIO_AF3, hal_ll_tim_module_num(TIM_MODULE_9)},
    #endif
    #ifdef TIM9_CH2_PD7_AF3
    {PD7, HAL_LL_TIM9_BASE_ADDR, HAL_LL_TIM_CHANNEL_2, HAL_LL_TIM9_GPIO_AF3, hal_ll_tim_module_num(TIM_MODULE_9)},
    #endif
    #ifdef TIM9_CH2_PE6_AF3
    {PE6, HAL_LL_TIM9_BASE_ADDR, HAL_LL_TIM_CHANNEL_2, HAL_LL_TIM9_GPIO_AF3, hal_ll_tim_module_num(TIM_MODULE_9)},
    #endif
	#endif

	#ifdef TIM_MODULE_10
    #ifdef TIM10_CH1_PA6_AF3
    {PA6, HAL_LL_TIM10_BASE_ADDR, HAL_LL_TIM_CHANNEL_1, HAL_LL_TIM10_GPIO_AF3, hal_ll_tim_module_num(TIM_MODULE_10)},
    #endif
    #ifdef TIM10_CH1_PB12_AF3
    {PB12, HAL_LL_TIM10_BASE_ADDR, HAL_LL_TIM_CHANNEL_1, HAL_LL_TIM10_GPIO_AF3, hal_ll_tim_module_num(TIM_MODULE_10)},
    #endif
    #ifdef TIM10_CH1_PB8_AF3
    {PB8, HAL_LL_TIM10_BASE_ADDR, HAL_LL_TIM_CHANNEL_1, HAL_LL_TIM10_GPIO_AF3, hal_ll_tim_module_num(TIM_MODULE_10)},
    #endif
    #ifdef TIM10_CH1_PE0_AF3
    {PE0, HAL_LL_TIM10_BASE_ADDR, HAL_LL_TIM_CHANNEL_1, HAL_LL_TIM10_GPIO_AF3, hal_ll_tim_module_num(TIM_MODULE_10)},
    #endif
    #ifdef TIM10_CH1_PF6_AF3
    {PF6, HAL_LL_TIM10_BASE_ADDR, HAL_LL_TIM_CHANNEL_1, HAL_LL_TIM10_GPIO_AF3, hal_ll_tim_module_num(TIM_MODULE_10)},
    #endif
	#endif

	#ifdef TIM_MODULE_11
    #ifdef TIM11_CH1_PA7_AF3
    {PA7, HAL_LL_TIM11_BASE_ADDR, HAL_LL_TIM_CHANNEL_1, HAL_LL_TIM11_GPIO_AF3, hal_ll_tim_module_num(TIM_MODULE_11)},
    #endif
    #ifdef TIM11_CH1_PB15_AF3
    {PB15, HAL_LL_TIM11_BASE_ADDR, HAL_LL_TIM_CHANNEL_1, HAL_LL_TIM11_GPIO_AF3, hal_ll_tim_module_num(TIM_MODULE_11)},
    #endif
    #ifdef TIM11_CH1_PB9_AF3
    {PB9, HAL_LL_TIM11_BASE_ADDR, HAL_LL_TIM_CHANNEL_1, HAL_LL_TIM11_GPIO_AF3, hal_ll_tim_module_num(TIM_MODULE_11)},
    #endif
    #ifdef TIM11_CH1_PC12_AF3
    {PC12, HAL_LL_TIM11_BASE_ADDR, HAL_LL_TIM_CHANNEL_1, HAL_LL_TIM11_GPIO_AF3, hal_ll_tim_module_num(TIM_MODULE_11)},
    #endif
    #ifdef TIM11_CH1_PE1_AF3
    {PE1, HAL_LL_TIM11_BASE_ADDR, HAL_LL_TIM_CHANNEL_1, HAL_LL_TIM11_GPIO_AF3, hal_ll_tim_module_num(TIM_MODULE_11)},
    #endif
    #ifdef TIM11_CH1_PF7_AF3
    {PF7, HAL_LL_TIM11_BASE_ADDR, HAL_LL_TIM_CHANNEL_1, HAL_LL_TIM11_GPIO_AF3, hal_ll_tim_module_num(TIM_MODULE_11)},
    #endif
	#endif

	#ifdef TIM_MODULE_12
    #ifdef TIM12_CH1_PB14_AF2
    {PB14, HAL_LL_TIM12_BASE_ADDR, HAL_LL_TIM_CHANNEL_1, HAL_LL_TIM12_GPIO_AF2, hal_ll_tim_module_num(TIM_MODULE_12)},
    #endif
    #ifdef TIM12_CH1_PB14_AF9
    {PB14, HAL_LL_TIM12_BASE_ADDR, HAL_LL_TIM_CHANNEL_1, HAL_LL_TIM12_GPIO_AF9, hal_ll_tim_module_num(TIM_MODULE_12)},
    #endif
    #ifdef TIM12_CH1_PH6_AF2
    {PH6, HAL_LL_TIM12_BASE_ADDR, HAL_LL_TIM_CHANNEL_1, HAL_LL_TIM12_GPIO_AF2, hal_ll_tim_module_num(TIM_MODULE_12)},
    #endif
    #ifdef TIM12_CH1_PH6_AF9
    {PH6, HAL_LL_TIM12_BASE_ADDR, HAL_LL_TIM_CHANNEL_1, HAL_LL_TIM12_GPIO_AF9, hal_ll_tim_module_num(TIM_MODULE_12)},
    #endif
    #ifdef TIM12_CH2_PB15_AF2
    {PB15, HAL_LL_TIM12_BASE_ADDR, HAL_LL_TIM_CHANNEL_2, HAL_LL_TIM12_GPIO_AF2, hal_ll_tim_module_num(TIM_MODULE_12)},
    #endif
    #ifdef TIM12_CH2_PB15_AF9
    {PB15, HAL_LL_TIM12_BASE_ADDR, HAL_LL_TIM_CHANNEL_2, HAL_LL_TIM12_GPIO_AF9, hal_ll_tim_module_num(TIM_MODULE_12)},
    #endif
    #ifdef TIM12_CH2_PH9_AF2
    {PH9, HAL_LL_TIM12_BASE_ADDR, HAL_LL_TIM_CHANNEL_2, HAL_LL_TIM12_GPIO_AF2, hal_ll_tim_module_num(TIM_MODULE_12)},
    #endif
    #ifdef TIM12_CH2_PH9_AF9
    {PH9, HAL_LL_TIM12_BASE_ADDR, HAL_LL_TIM_CHANNEL_2, HAL_LL_TIM12_GPIO_AF9, hal_ll_tim_module_num(TIM_MODULE_12)},
    #endif
	#endif

	#ifdef TIM_MODULE_13
    #ifdef TIM13_CH1_PA6_AF9
    {PA6, HAL_LL_TIM13_BASE_ADDR, HAL_LL_TIM_CHANNEL_1, HAL_LL_TIM13_GPIO_AF9, hal_ll_tim_module_num(TIM_MODULE_13)},
    #endif
    #ifdef TIM13_CH1_PF8_AF9
    {PF8, HAL_LL_TIM13_BASE_ADDR, HAL_LL_TIM_CHANNEL_1, HAL_LL_TIM13_GPIO_AF9, hal_ll_tim_module_num(TIM_MODULE_13)},
    #endif
	#endif

	#ifdef TIM_MODULE_14
    #ifdef TIM14_CH1_PA7_AF9
    {PA7, HAL_LL_TIM14_BASE_ADDR, HAL_LL_TIM_CHANNEL_1, HAL_LL_TIM14_GPIO_AF9, hal_ll_tim_module_num(TIM_MODULE_14)},
    #endif
    #ifdef TIM14_CH1_PF9_AF9
    {PF9, HAL_LL_TIM14_BASE_ADDR, HAL_LL_TIM_CHANNEL_1, HAL_LL_TIM14_GPIO_AF9, hal_ll_tim_module_num(TIM_MODULE_14)},
    #endif
	#endif

    #ifdef TIM_MODULE_15
    #ifdef TIM15_CH1_PA2_AF4
    {PA2, HAL_LL_TIM15_BASE_ADDR, HAL_LL_TIM_CHANNEL_1, HAL_LL_TIM15_GPIO_AF4, hal_ll_tim_module_num(TIM_MODULE_15)},
    #endif
    #ifdef TIM15_CH1_PE5_AF4
    {PE5, HAL_LL_TIM15_BASE_ADDR, HAL_LL_TIM_CHANNEL_1, HAL_LL_TIM15_GPIO_AF4, hal_ll_tim_module_num(TIM_MODULE_15)},
    #endif
    #ifdef TIM15_CH2_PA3_AF4
    {PA3, HAL_LL_TIM15_BASE_ADDR, HAL_LL_TIM_CHANNEL_2, HAL_LL_TIM15_GPIO_AF4, hal_ll_tim_module_num(TIM_MODULE_15)},
    #endif
    #ifdef TIM15_CH2_PE6_AF4
    {PE6, HAL_LL_TIM15_BASE_ADDR, HAL_LL_TIM_CHANNEL_2, HAL_LL_TIM15_GPIO_AF4, hal_ll_tim_module_num(TIM_MODULE_15)},
    #endif
	#endif

    #ifdef TIM_MODULE_16
    #ifdef TIM16_CH1_PB8_AF1
    {PB8, HAL_LL_TIM16_BASE_ADDR, HAL_LL_TIM_CHANNEL_1, HAL_LL_TIM16_GPIO_AF1, hal_ll_tim_module_num(TIM_MODULE_16)},
    #endif
    #ifdef TIM16_CH1_PF6_AF1
    {PF6, HAL_LL_TIM16_BASE_ADDR, HAL_LL_TIM_CHANNEL_1, HAL_LL_TIM16_GPIO_AF1, hal_ll_tim_module_num(TIM_MODULE_16)},
    #endif
	#endif

    #ifdef TIM_MODULE_17
    #ifdef TIM17_CH1_PB9_AF1
    {PB9, HAL_LL_TIM17_BASE_ADDR, HAL_LL_TIM_CHANNEL_1, HAL_LL_TIM17_GPIO_AF1, hal_ll_tim_module_num(TIM_MODULE_17)},
    #endif
    #ifdef TIM17_CH1_PF7_AF1
    {PF7, HAL_LL_TIM17_BASE_ADDR, HAL_LL_TIM_CHANNEL_1, HAL_LL_TIM17_GPIO_AF1, hal_ll_tim_module_num(TIM_MODULE_17)},
    #endif
	#endif

    #ifdef CAPTURE_COMPARE_COMPLEMENTARY_OUTPUT
    #ifdef TIM1_CH1N_PA7_AF1
    {PA7, HAL_LL_TIM1_BASE_ADDR, HAL_LL_TIM_CHANNEL_1N, HAL_LL_TIM1_GPIO_AF1, hal_ll_tim_module_num(TIM_MODULE_1)},
    #endif
    #ifdef TIM1_CH1N_PB13_AF1
    {PB13, HAL_LL_TIM1_BASE_ADDR, HAL_LL_TIM_CHANNEL_1N, HAL_LL_TIM1_GPIO_AF1, hal_ll_tim_module_num(TIM_MODULE_1)},
    #endif
    #ifdef TIM1_CH1N_PE8_AF1
    {PE8, HAL_LL_TIM1_BASE_ADDR, HAL_LL_TIM_CHANNEL_1N, HAL_LL_TIM1_GPIO_AF1, hal_ll_tim_module_num(TIM_MODULE_1)},
    #endif
    #ifdef TIM1_CH1N_PK0_AF1
    {PK0, HAL_LL_TIM1_BASE_ADDR, HAL_LL_TIM_CHANNEL_1N, HAL_LL_TIM1_GPIO_AF1, hal_ll_tim_module_num(TIM_MODULE_1)},
    #endif
    #ifdef TIM1_CH2N_PB0_AF1
    {PB0, HAL_LL_TIM1_BASE_ADDR, HAL_LL_TIM_CHANNEL_2N, HAL_LL_TIM1_GPIO_AF1, hal_ll_tim_module_num(TIM_MODULE_1)},
    #endif
    #ifdef TIM1_CH2N_PB14_AF1
    {PB14, HAL_LL_TIM1_BASE_ADDR, HAL_LL_TIM_CHANNEL_2N, HAL_LL_TIM1_GPIO_AF1, hal_ll_tim_module_num(TIM_MODULE_1)},
    #endif
    #ifdef TIM1_CH2N_PE10_AF1
    {PE10, HAL_LL_TIM1_BASE_ADDR, HAL_LL_TIM_CHANNEL_2N, HAL_LL_TIM1_GPIO_AF1, hal_ll_tim_module_num(TIM_MODULE_1)},
    #endif
    #ifdef TIM1_CH2N_PJ10_AF1
    {PJ10, HAL_LL_TIM1_BASE_ADDR, HAL_LL_TIM_CHANNEL_2N, HAL_LL_TIM1_GPIO_AF1, hal_ll_tim_module_num(TIM_MODULE_1)},
    #endif
    #ifdef TIM1_CH3N_PB1_AF1
    {PB1, HAL_LL_TIM1_BASE_ADDR, HAL_LL_TIM_CHANNEL_3N, HAL_LL_TIM1_GPIO_AF1, hal_ll_tim_module_num(TIM_MODULE_1)},
    #endif
    #ifdef TIM1_CH3N_PB15_AF1
    {PB15, HAL_LL_TIM1_BASE_ADDR, HAL_LL_TIM_CHANNEL_3N, HAL_LL_TIM1_GPIO_AF1, hal_ll_tim_module_num(TIM_MODULE_1)},
    #endif
    #ifdef TIM1_CH3N_PE12_AF1
    {PE12, HAL_LL_TIM1_BASE_ADDR, HAL_LL_TIM_CHANNEL_3N, HAL_LL_TIM1_GPIO_AF1, hal_ll_tim_module_num(TIM_MODULE_1)},
    #endif
    #ifdef TIM1_CH3N_PJ8_AF1
    {PJ8, HAL_LL_TIM1_BASE_ADDR, HAL_LL_TIM_CHANNEL_3N, HAL_LL_TIM1_GPIO_AF1, hal_ll_tim_module_num(TIM_MODULE_1)},
    #endif
    #ifdef TIM8_CH1N_PA5_AF3
    {PA5, HAL_LL_TIM8_BASE_ADDR, HAL_LL_TIM_CHANNEL_1N, HAL_LL_TIM8_GPIO_AF3, hal_ll_tim_module_num(TIM_MODULE_8)},
    #endif
    #ifdef TIM8_CH1N_PA7_AF3
    {PA7, HAL_LL_TIM8_BASE_ADDR, HAL_LL_TIM_CHANNEL_1N, HAL_LL_TIM8_GPIO_AF3, hal_ll_tim_module_num(TIM_MODULE_8)},
    #endif
    #ifdef TIM8_CH1N_PH13_AF3
    {PH13, HAL_LL_TIM8_BASE_ADDR, HAL_LL_TIM_CHANNEL_1N, HAL_LL_TIM8_GPIO_AF3, hal_ll_tim_module_num(TIM_MODULE_8)},
    #endif
    #ifdef TIM8_CH1N_PJ9_AF3
    {PJ9, HAL_LL_TIM8_BASE_ADDR, HAL_LL_TIM_CHANNEL_1N, HAL_LL_TIM8_GPIO_AF3, hal_ll_tim_module_num(TIM_MODULE_8)},
    #endif
    #ifdef TIM8_CH2N_PB0_AF3
    {PB0, HAL_LL_TIM8_BASE_ADDR, HAL_LL_TIM_CHANNEL_2N, HAL_LL_TIM8_GPIO_AF3, hal_ll_tim_module_num(TIM_MODULE_8)},
    #endif
    #ifdef TIM8_CH2N_PB14_AF3
    {PB14, HAL_LL_TIM8_BASE_ADDR, HAL_LL_TIM_CHANNEL_2N, HAL_LL_TIM8_GPIO_AF3, hal_ll_tim_module_num(TIM_MODULE_8)},
    #endif
    #ifdef TIM8_CH2N_PH14_AF3
    {PH14, HAL_LL_TIM8_BASE_ADDR, HAL_LL_TIM_CHANNEL_2N, HAL_LL_TIM8_GPIO_AF3, hal_ll_tim_module_num(TIM_MODULE_8)},
    #endif
    #ifdef TIM8_CH2N_PJ11_AF3
    {PJ11, HAL_LL_TIM8_BASE_ADDR, HAL_LL_TIM_CHANNEL_2N, HAL_LL_TIM8_GPIO_AF3, hal_ll_tim_module_num(TIM_MODULE_8)},
    #endif
    #ifdef TIM8_CH2N_PJ7_AF3
    {PJ7, HAL_LL_TIM8_BASE_ADDR, HAL_LL_TIM_CHANNEL_2N, HAL_LL_TIM8_GPIO_AF3, hal_ll_tim_module_num(TIM_MODULE_8)},
    #endif
    #ifdef TIM8_CH3N_PB1_AF3
    {PB1, HAL_LL_TIM8_BASE_ADDR, HAL_LL_TIM_CHANNEL_3N, HAL_LL_TIM8_GPIO_AF3, hal_ll_tim_module_num(TIM_MODULE_8)},
    #endif
    #ifdef TIM8_CH3N_PB15_AF3
    {PB15, HAL_LL_TIM8_BASE_ADDR, HAL_LL_TIM_CHANNEL_3N, HAL_LL_TIM8_GPIO_AF3, hal_ll_tim_module_num(TIM_MODULE_8)},
    #endif
    #ifdef TIM8_CH3N_PH15_AF3
    {PH15, HAL_LL_TIM8_BASE_ADDR, HAL_LL_TIM_CHANNEL_3N, HAL_LL_TIM8_GPIO_AF3, hal_ll_tim_module_num(TIM_MODULE_8)},
    #endif
    #ifdef TIM8_CH3N_PK1_AF3
    {PK1, HAL_LL_TIM8_BASE_ADDR, HAL_LL_TIM_CHANNEL_3N, HAL_LL_TIM8_GPIO_AF3, hal_ll_tim_module_num(TIM_MODULE_8)},
    #endif
    #ifdef TIM15_CH1N_PA1_AF4
    {PA1, HAL_LL_TIM15_BASE_ADDR, HAL_LL_TIM_CHANNEL_1N, HAL_LL_TIM15_GPIO_AF4, hal_ll_tim_module_num(TIM_MODULE_15)},
    #endif
    #ifdef TIM15_CH1N_PE4_AF4
    {PE4, HAL_LL_TIM15_BASE_ADDR, HAL_LL_TIM_CHANNEL_1N, HAL_LL_TIM15_GPIO_AF4, hal_ll_tim_module_num(TIM_MODULE_15)},
    #endif
    #ifdef TIM16_CH1N_PB6_AF1
    {PB6, HAL_LL_TIM16_BASE_ADDR, HAL_LL_TIM_CHANNEL_1N, HAL_LL_TIM16_GPIO_AF1, hal_ll_tim_module_num(TIM_MODULE_16)},
    #endif
    #ifdef TIM16_CH1N_PF8_AF1
    {PF8, HAL_LL_TIM16_BASE_ADDR, HAL_LL_TIM_CHANNEL_1N, HAL_LL_TIM16_GPIO_AF1, hal_ll_tim_module_num(TIM_MODULE_16)},
    #endif
    #ifdef TIM17_CH1N_PB7_AF1
    {PB7, HAL_LL_TIM17_BASE_ADDR, HAL_LL_TIM_CHANNEL_1N, HAL_LL_TIM17_GPIO_AF1, hal_ll_tim_module_num(TIM_MODULE_17)},
    #endif
    #ifdef TIM17_CH1N_PF9_AF1
    {PF9, HAL_LL_TIM17_BASE_ADDR, HAL_LL_TIM_CHANNEL_1N, HAL_LL_TIM17_GPIO_AF1, hal_ll_tim_module_num(TIM_MODULE_17)},
    #endif
    #endif

	{ HAL_LL_PIN_NC, HAL_LL_MODULE_ERROR, HAL_LL_CHANNEL_ERROR, HAL_LL_PIN_NC, HAL_LL_PIN_NC }
};

#ifdef __cplusplus
}
#endif

#endif // _HAL_LL_TIM_PIN_MAP_H_
// ------------------------------------------------------------------------- END
