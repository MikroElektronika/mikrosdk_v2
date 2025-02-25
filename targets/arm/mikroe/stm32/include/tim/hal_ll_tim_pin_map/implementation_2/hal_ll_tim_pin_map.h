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

#define CAPTURE_COMPARE_COMPLEMENTARY_OUTPUT

/*!< If module is remapped */
#define HAL_LL_TIM_REMAP_DISABLE            0
#define HAL_LL_TIM_REMAP_ENABLE             0x80000000ul

/*!< @brief Macro defining `weak` attribute */
#define __weak __attribute__((weak))

/*!< Abbreviations used in source. */
typedef uint32_t        hal_ll_tim_gpio_af_t;

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
static const hal_ll_base_addr_t HAL_LL_TIM1_BASE_ADDR = 0x40012C00;
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
static const hal_ll_base_addr_t HAL_LL_TIM8_BASE_ADDR = 0x40013400;
#endif
#ifdef TIM_MODULE_9
static const hal_ll_base_addr_t HAL_LL_TIM9_BASE_ADDR = 0x40014000;
#endif
#ifdef TIM_MODULE_10
static const hal_ll_base_addr_t HAL_LL_TIM10_BASE_ADDR = 0x40014400;
#endif
#ifdef TIM_MODULE_11
static const hal_ll_base_addr_t HAL_LL_TIM11_BASE_ADDR = 0x40014800;
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
#ifdef TIM_MODULE_19
static const hal_ll_base_addr_t HAL_LL_TIM19_BASE_ADDR = 0x40015C00;
#endif
#ifdef TIM_MODULE_20
static const hal_ll_base_addr_t HAL_LL_TIM20_BASE_ADDR = 0x40015000;
#endif
#ifdef TIM_MODULE_21
static const hal_ll_base_addr_t HAL_LL_TIM21_BASE_ADDR = 0x40010800;
#endif
#ifdef TIM_MODULE_22
static const hal_ll_base_addr_t HAL_LL_TIM22_BASE_ADDR = 0x40011400;
#endif

/*!< TIM modules. */
#ifdef TIM_MODULE_1
static const hal_ll_tim_gpio_af_t HAL_LL_TIM1_GPIO_AF0 = 0;
static const hal_ll_tim_gpio_af_t HAL_LL_TIM1_GPIO_AF1 = 1;
static const hal_ll_tim_gpio_af_t HAL_LL_TIM1_GPIO_AF2 = 2;
static const hal_ll_tim_gpio_af_t HAL_LL_TIM1_GPIO_AF4 = 4;
static const hal_ll_tim_gpio_af_t HAL_LL_TIM1_GPIO_AF6 = 6;
static const hal_ll_tim_gpio_af_t HAL_LL_TIM1_GPIO_AF11 = 11;
static const hal_ll_tim_gpio_af_t HAL_LL_TIM1_GPIO_AF_1  = 0x00000040;
static const hal_ll_tim_gpio_af_t HAL_LL_TIM1_GPIO_AF_2  = 0x000000C0;
#endif
#ifdef TIM_MODULE_2
static const hal_ll_tim_gpio_af_t HAL_LL_TIM2_GPIO_AF0 = 0;
static const hal_ll_tim_gpio_af_t HAL_LL_TIM2_GPIO_AF1 = 1;
static const hal_ll_tim_gpio_af_t HAL_LL_TIM2_GPIO_AF2 = 2;
static const hal_ll_tim_gpio_af_t HAL_LL_TIM2_GPIO_AF5 = 5;
static const hal_ll_tim_gpio_af_t HAL_LL_TIM2_GPIO_AF10 = 10;
static const hal_ll_tim_gpio_af_t HAL_LL_TIM2_GPIO_AF   = 0x00000300;
#endif
#ifdef TIM_MODULE_3
static const hal_ll_tim_gpio_af_t HAL_LL_TIM3_GPIO_AF0 = 0;
static const hal_ll_tim_gpio_af_t HAL_LL_TIM3_GPIO_AF1 = 1;
static const hal_ll_tim_gpio_af_t HAL_LL_TIM3_GPIO_AF2 = 2;
static const hal_ll_tim_gpio_af_t HAL_LL_TIM3_GPIO_AF4 = 4;
static const hal_ll_tim_gpio_af_t HAL_LL_TIM3_GPIO_AF10 = 10;
static const hal_ll_tim_gpio_af_t HAL_LL_TIM3_GPIO_AF_1  = 0x00000400;
static const hal_ll_tim_gpio_af_t HAL_LL_TIM3_GPIO_AF_2  = 0x00000C00;
#endif
#ifdef TIM_MODULE_4
static const hal_ll_tim_gpio_af_t HAL_LL_TIM4_GPIO_AF2 = 2;
static const hal_ll_tim_gpio_af_t HAL_LL_TIM4_GPIO_AF10 = 10;
static const hal_ll_tim_gpio_af_t HAL_LL_TIM4_GPIO_AF   = 0x00001000;
#endif
#ifdef TIM_MODULE_5
static const hal_ll_tim_gpio_af_t HAL_LL_TIM5_GPIO_AF2 = 2;
#endif
#ifdef TIM_MODULE_8
static const hal_ll_tim_gpio_af_t HAL_LL_TIM8_GPIO_AF2 = 2;
static const hal_ll_tim_gpio_af_t HAL_LL_TIM8_GPIO_AF3 = 3;
static const hal_ll_tim_gpio_af_t HAL_LL_TIM8_GPIO_AF4 = 4;
static const hal_ll_tim_gpio_af_t HAL_LL_TIM8_GPIO_AF5 = 5;
static const hal_ll_tim_gpio_af_t HAL_LL_TIM8_GPIO_AF10 = 10;
#endif
#ifdef TIM_MODULE_9
static const hal_ll_tim_gpio_af_t HAL_LL_TIM9_GPIO_AF  = 0x00000020;
#endif
#ifdef TIM_MODULE_10
static const hal_ll_tim_gpio_af_t HAL_LL_TIM10_GPIO_AF = 0x00000040;
#endif
#ifdef TIM_MODULE_11
static const hal_ll_tim_gpio_af_t HAL_LL_TIM11_GPIO_AF = 0x00000080;
#endif
#ifdef TIM_MODULE_12
static const hal_ll_tim_gpio_af_t HAL_LL_TIM12_GPIO_AF9 = 9;
static const hal_ll_tim_gpio_af_t HAL_LL_TIM12_GPIO_AF10 = 10;
static const hal_ll_tim_gpio_af_t HAL_LL_TIM12_GPIO_AF  = 0x00001000;
#endif
#ifdef TIM_MODULE_13
static const hal_ll_tim_gpio_af_t HAL_LL_TIM13_GPIO_AF2 = 2;
static const hal_ll_tim_gpio_af_t HAL_LL_TIM13_GPIO_AF9 = 9;
static const hal_ll_tim_gpio_af_t HAL_LL_TIM13_GPIO_AF  = 0x00000100;
#endif
#ifdef TIM_MODULE_14
static const hal_ll_tim_gpio_af_t HAL_LL_TIM14_GPIO_AF0 = 0;
static const hal_ll_tim_gpio_af_t HAL_LL_TIM14_GPIO_AF2 = 2;
static const hal_ll_tim_gpio_af_t HAL_LL_TIM14_GPIO_AF4 = 4;
static const hal_ll_tim_gpio_af_t HAL_LL_TIM14_GPIO_AF9 = 9;
static const hal_ll_tim_gpio_af_t HAL_LL_TIM14_GPIO_AF  = 0x00000200;
#endif
#ifdef TIM_MODULE_15
static const hal_ll_tim_gpio_af_t HAL_LL_TIM15_GPIO_AF0 = 0;
static const hal_ll_tim_gpio_af_t HAL_LL_TIM15_GPIO_AF1 = 1;
static const hal_ll_tim_gpio_af_t HAL_LL_TIM15_GPIO_AF2 = 2;
static const hal_ll_tim_gpio_af_t HAL_LL_TIM15_GPIO_AF3 = 3;
static const hal_ll_tim_gpio_af_t HAL_LL_TIM15_GPIO_AF4 = 4;
static const hal_ll_tim_gpio_af_t HAL_LL_TIM15_GPIO_AF5 = 5;
static const hal_ll_tim_gpio_af_t HAL_LL_TIM15_GPIO_AF9 = 9;
static const hal_ll_tim_gpio_af_t HAL_LL_TIM15_GPIO_AF14 = 14;
static const hal_ll_tim_gpio_af_t HAL_LL_TIM15_GPIO_AF15 = 15;
static const hal_ll_tim_gpio_af_t HAL_LL_TIM15_GPIO_AF  = 0x00000001;
#endif
#ifdef TIM_MODULE_16
static const hal_ll_tim_gpio_af_t HAL_LL_TIM16_GPIO_AF0 = 0;
static const hal_ll_tim_gpio_af_t HAL_LL_TIM16_GPIO_AF1 = 1;
static const hal_ll_tim_gpio_af_t HAL_LL_TIM16_GPIO_AF2 = 2;
static const hal_ll_tim_gpio_af_t HAL_LL_TIM16_GPIO_AF4 = 4;
static const hal_ll_tim_gpio_af_t HAL_LL_TIM16_GPIO_AF5 = 5;
static const hal_ll_tim_gpio_af_t HAL_LL_TIM16_GPIO_AF14 = 14;
static const hal_ll_tim_gpio_af_t HAL_LL_TIM16_GPIO_AF  = 0x00000002;
#endif
#ifdef TIM_MODULE_17
static const hal_ll_tim_gpio_af_t HAL_LL_TIM17_GPIO_AF0 = 0;
static const hal_ll_tim_gpio_af_t HAL_LL_TIM17_GPIO_AF1 = 1;
static const hal_ll_tim_gpio_af_t HAL_LL_TIM17_GPIO_AF2 = 2;
static const hal_ll_tim_gpio_af_t HAL_LL_TIM17_GPIO_AF4 = 4;
static const hal_ll_tim_gpio_af_t HAL_LL_TIM17_GPIO_AF5 = 5;
static const hal_ll_tim_gpio_af_t HAL_LL_TIM17_GPIO_AF10 = 10;
static const hal_ll_tim_gpio_af_t HAL_LL_TIM17_GPIO_AF14 = 14;
static const hal_ll_tim_gpio_af_t HAL_LL_TIM17_GPIO_AF  = 0x00000004;
#endif
#ifdef TIM_MODULE_19
static const hal_ll_tim_gpio_af_t HAL_LL_TIM19_GPIO_AF2 = 2;
static const hal_ll_tim_gpio_af_t HAL_LL_TIM19_GPIO_AF11 = 11;
#endif
#ifdef TIM_MODULE_20
static const hal_ll_tim_gpio_af_t HAL_LL_TIM20_GPIO_AF2 = 2;
static const hal_ll_tim_gpio_af_t HAL_LL_TIM20_GPIO_AF3 = 3;
static const hal_ll_tim_gpio_af_t HAL_LL_TIM20_GPIO_AF6 = 6;
#endif
#ifdef TIM_MODULE_21
static const hal_ll_tim_gpio_af_t HAL_LL_TIM21_GPIO_AF0 = 0;
static const hal_ll_tim_gpio_af_t HAL_LL_TIM21_GPIO_AF1 = 1;
static const hal_ll_tim_gpio_af_t HAL_LL_TIM21_GPIO_AF5 = 5;
static const hal_ll_tim_gpio_af_t HAL_LL_TIM21_GPIO_AF6 = 6;
#endif
#ifdef TIM_MODULE_22
static const hal_ll_tim_gpio_af_t HAL_LL_TIM22_GPIO_AF0 = 0;
static const hal_ll_tim_gpio_af_t HAL_LL_TIM22_GPIO_AF4 = 4;
static const hal_ll_tim_gpio_af_t HAL_LL_TIM22_GPIO_AF5 = 5;
#endif

/*!< TIM pins. */
static const hal_ll_tim_pin_map_t _tim_map[] = {
    #ifdef TIM_MODULE_1
    #ifdef TIM1_CH1_PA8
    {GPIO_PA8, HAL_LL_TIM1_BASE_ADDR, HAL_LL_TIM_CHANNEL_1, HAL_LL_TIM1_GPIO_AF_1, hal_ll_tim_module_num(TIM_MODULE_1)},
    #endif
    #ifdef TIM1_CH1_PA8_AF1
    {GPIO_PA8, HAL_LL_TIM1_BASE_ADDR, HAL_LL_TIM_CHANNEL_1, HAL_LL_TIM1_GPIO_AF1, hal_ll_tim_module_num(TIM_MODULE_1)},
    #endif
    #ifdef TIM1_CH1_PA8_AF2
    {GPIO_PA8, HAL_LL_TIM1_BASE_ADDR, HAL_LL_TIM_CHANNEL_1, HAL_LL_TIM1_GPIO_AF2, hal_ll_tim_module_num(TIM_MODULE_1)},
    #endif
    #ifdef TIM1_CH1_PA8_AF6
    {GPIO_PA8, HAL_LL_TIM1_BASE_ADDR, HAL_LL_TIM_CHANNEL_1, HAL_LL_TIM1_GPIO_AF6, hal_ll_tim_module_num(TIM_MODULE_1)},
    #endif
    #ifdef TIM1_CH1_PC0_AF2
    {GPIO_PC0, HAL_LL_TIM1_BASE_ADDR, HAL_LL_TIM_CHANNEL_1, HAL_LL_TIM1_GPIO_AF2, hal_ll_tim_module_num(TIM_MODULE_1)},
    #endif
    #ifdef TIM1_CH1_PC8_AF2
    {GPIO_PC8, HAL_LL_TIM1_BASE_ADDR, HAL_LL_TIM_CHANNEL_1, HAL_LL_TIM1_GPIO_AF2, hal_ll_tim_module_num(TIM_MODULE_1)},
    #endif
    #ifdef TIM1_CH1_PE9_AF0
    {GPIO_PE9, HAL_LL_TIM1_BASE_ADDR, HAL_LL_TIM_CHANNEL_1, HAL_LL_TIM1_GPIO_AF0, hal_ll_tim_module_num(TIM_MODULE_1)},
    #endif
    #ifdef TIM1_CH1_PE9_AF1
    {GPIO_PE9, HAL_LL_TIM1_BASE_ADDR, HAL_LL_TIM_CHANNEL_1, HAL_LL_TIM1_GPIO_AF1, hal_ll_tim_module_num(TIM_MODULE_1)},
    #endif
    #ifdef TIM1_CH1_PE9_AF2
    {GPIO_PE9, HAL_LL_TIM1_BASE_ADDR, HAL_LL_TIM_CHANNEL_1, HAL_LL_TIM1_GPIO_AF2, hal_ll_tim_module_num(TIM_MODULE_1)},
    #endif
    #ifdef TIM1_CH1_PE9_REMAP
    {GPIO_PE9, HAL_LL_TIM1_BASE_ADDR, HAL_LL_TIM_CHANNEL_1, HAL_LL_TIM1_GPIO_AF_2, hal_ll_tim_module_num(TIM_MODULE_1)},
    #endif
    #ifdef TIM1_CH2_PA9
    {GPIO_PA9, HAL_LL_TIM1_BASE_ADDR, HAL_LL_TIM_CHANNEL_2, HAL_LL_TIM_REMAP_DISABLE, hal_ll_tim_module_num(TIM_MODULE_1)},
    #endif
    #ifdef TIM1_CH2_PA9_AF1
    {GPIO_PA9, HAL_LL_TIM1_BASE_ADDR, HAL_LL_TIM_CHANNEL_2, HAL_LL_TIM1_GPIO_AF1, hal_ll_tim_module_num(TIM_MODULE_1)},
    #endif
    #ifdef TIM1_CH2_PA9_AF2
    {GPIO_PA9, HAL_LL_TIM1_BASE_ADDR, HAL_LL_TIM_CHANNEL_2, HAL_LL_TIM1_GPIO_AF2, hal_ll_tim_module_num(TIM_MODULE_1)},
    #endif
    #ifdef TIM1_CH2_PA9_AF6
    {GPIO_PA9, HAL_LL_TIM1_BASE_ADDR, HAL_LL_TIM_CHANNEL_2, HAL_LL_TIM1_GPIO_AF6, hal_ll_tim_module_num(TIM_MODULE_1)},
    #endif
    #ifdef TIM1_CH2_PB3_AF1
    {GPIO_PB3, HAL_LL_TIM1_BASE_ADDR, HAL_LL_TIM_CHANNEL_2, HAL_LL_TIM1_GPIO_AF1, hal_ll_tim_module_num(TIM_MODULE_1)},
    #endif
    #ifdef TIM1_CH2_PC1_AF2
    {GPIO_PC1, HAL_LL_TIM1_BASE_ADDR, HAL_LL_TIM_CHANNEL_2, HAL_LL_TIM1_GPIO_AF2, hal_ll_tim_module_num(TIM_MODULE_1)},
    #endif
    #ifdef TIM1_CH2_PC9_AF2
    {GPIO_PC9, HAL_LL_TIM1_BASE_ADDR, HAL_LL_TIM_CHANNEL_2, HAL_LL_TIM1_GPIO_AF2, hal_ll_tim_module_num(TIM_MODULE_1)},
    #endif
    #ifdef TIM1_CH2_PE11_AF0
    {GPIO_PE11, HAL_LL_TIM1_BASE_ADDR, HAL_LL_TIM_CHANNEL_2, HAL_LL_TIM1_GPIO_AF0, hal_ll_tim_module_num(TIM_MODULE_1)},
    #endif
    #ifdef TIM1_CH2_PE11_AF1
    {GPIO_PE11, HAL_LL_TIM1_BASE_ADDR, HAL_LL_TIM_CHANNEL_2, HAL_LL_TIM1_GPIO_AF1, hal_ll_tim_module_num(TIM_MODULE_1)},
    #endif
    #ifdef TIM1_CH2_PE11_AF2
    {GPIO_PE11, HAL_LL_TIM1_BASE_ADDR, HAL_LL_TIM_CHANNEL_2, HAL_LL_TIM1_GPIO_AF2, hal_ll_tim_module_num(TIM_MODULE_1)},
    #endif
    #ifdef TIM1_CH2_PE11_REMAP
    {GPIO_PE11, HAL_LL_TIM1_BASE_ADDR, HAL_LL_TIM_CHANNEL_2, HAL_LL_TIM1_GPIO_AF_2, hal_ll_tim_module_num(TIM_MODULE_1)},
    #endif
    #ifdef TIM1_CH3_PA10
    {GPIO_PA10, HAL_LL_TIM1_BASE_ADDR, HAL_LL_TIM_CHANNEL_3, HAL_LL_TIM_REMAP_DISABLE, hal_ll_tim_module_num(TIM_MODULE_1)},
    #endif
    #ifdef TIM1_CH3_PA10_AF1
    {GPIO_PA10, HAL_LL_TIM1_BASE_ADDR, HAL_LL_TIM_CHANNEL_3, HAL_LL_TIM1_GPIO_AF1, hal_ll_tim_module_num(TIM_MODULE_1)},
    #endif
    #ifdef TIM1_CH3_PA10_AF2
    {GPIO_PA10, HAL_LL_TIM1_BASE_ADDR, HAL_LL_TIM_CHANNEL_3, HAL_LL_TIM1_GPIO_AF2, hal_ll_tim_module_num(TIM_MODULE_1)},
    #endif
    #ifdef TIM1_CH3_PA10_AF6
    {GPIO_PA10, HAL_LL_TIM1_BASE_ADDR, HAL_LL_TIM_CHANNEL_3, HAL_LL_TIM1_GPIO_AF6, hal_ll_tim_module_num(TIM_MODULE_1)},
    #endif
    #ifdef TIM1_CH3_PB6_AF1
    {GPIO_PB6, HAL_LL_TIM1_BASE_ADDR, HAL_LL_TIM_CHANNEL_3, HAL_LL_TIM1_GPIO_AF1, hal_ll_tim_module_num(TIM_MODULE_1)},
    #endif
    #ifdef TIM1_CH3_PC10_AF2
    {GPIO_PC10, HAL_LL_TIM1_BASE_ADDR, HAL_LL_TIM_CHANNEL_3, HAL_LL_TIM1_GPIO_AF2, hal_ll_tim_module_num(TIM_MODULE_1)},
    #endif
    #ifdef TIM1_CH3_PC2_AF2
    {GPIO_PC2, HAL_LL_TIM1_BASE_ADDR, HAL_LL_TIM_CHANNEL_3, HAL_LL_TIM1_GPIO_AF2, hal_ll_tim_module_num(TIM_MODULE_1)},
    #endif
    #ifdef TIM1_CH3_PE13_AF0
    {GPIO_PE13, HAL_LL_TIM1_BASE_ADDR, HAL_LL_TIM_CHANNEL_3, HAL_LL_TIM1_GPIO_AF0, hal_ll_tim_module_num(TIM_MODULE_1)},
    #endif
    #ifdef TIM1_CH3_PE13_AF1
    {GPIO_PE13, HAL_LL_TIM1_BASE_ADDR, HAL_LL_TIM_CHANNEL_3, HAL_LL_TIM1_GPIO_AF1, hal_ll_tim_module_num(TIM_MODULE_1)},
    #endif
    #ifdef TIM1_CH3_PE13_AF2
    {GPIO_PE13, HAL_LL_TIM1_BASE_ADDR, HAL_LL_TIM_CHANNEL_3, HAL_LL_TIM1_GPIO_AF2, hal_ll_tim_module_num(TIM_MODULE_1)},
    #endif
    #ifdef TIM1_CH3_PE13_REMAP
    {GPIO_PE13, HAL_LL_TIM1_BASE_ADDR, HAL_LL_TIM_CHANNEL_3,HAL_LL_TIM1_GPIO_AF_2, hal_ll_tim_module_num(TIM_MODULE_1)},
    #endif
    #ifdef TIM1_CH4_PA11
    {GPIO_PA11, HAL_LL_TIM1_BASE_ADDR, HAL_LL_TIM_CHANNEL_4, HAL_LL_TIM_REMAP_DISABLE, hal_ll_tim_module_num(TIM_MODULE_1)},
    #endif
    #ifdef TIM1_CH4_PA11_AF1
    {GPIO_PA11, HAL_LL_TIM1_BASE_ADDR, HAL_LL_TIM_CHANNEL_4, HAL_LL_TIM1_GPIO_AF1, hal_ll_tim_module_num(TIM_MODULE_1)},
    #endif
    #ifdef TIM1_CH4_PA11_AF11
    {GPIO_PA11, HAL_LL_TIM1_BASE_ADDR, HAL_LL_TIM_CHANNEL_4, HAL_LL_TIM1_GPIO_AF11, hal_ll_tim_module_num(TIM_MODULE_1)},
    #endif
    #ifdef TIM1_CH4_PA11_AF2
    {GPIO_PA11, HAL_LL_TIM1_BASE_ADDR, HAL_LL_TIM_CHANNEL_4, HAL_LL_TIM1_GPIO_AF2, hal_ll_tim_module_num(TIM_MODULE_1)},
    #endif
    #ifdef TIM1_CH4_PC11_AF2
    {GPIO_PC11, HAL_LL_TIM1_BASE_ADDR, HAL_LL_TIM_CHANNEL_4, HAL_LL_TIM1_GPIO_AF2, hal_ll_tim_module_num(TIM_MODULE_1)},
    #endif
    #ifdef TIM1_CH4_PC3_AF2
    {GPIO_PC3, HAL_LL_TIM1_BASE_ADDR, HAL_LL_TIM_CHANNEL_4, HAL_LL_TIM1_GPIO_AF2, hal_ll_tim_module_num(TIM_MODULE_1)},
    #endif
    #ifdef TIM1_CH4_PE14_AF0
    {GPIO_PE14, HAL_LL_TIM1_BASE_ADDR, HAL_LL_TIM_CHANNEL_4, HAL_LL_TIM1_GPIO_AF0, hal_ll_tim_module_num(TIM_MODULE_1)},
    #endif
    #ifdef TIM1_CH4_PE14_AF1
    {GPIO_PE14, HAL_LL_TIM1_BASE_ADDR, HAL_LL_TIM_CHANNEL_4, HAL_LL_TIM1_GPIO_AF1, hal_ll_tim_module_num(TIM_MODULE_1)},
    #endif
    #ifdef TIM1_CH4_PE14_AF2
    {GPIO_PE14, HAL_LL_TIM1_BASE_ADDR, HAL_LL_TIM_CHANNEL_4, HAL_LL_TIM1_GPIO_AF2, hal_ll_tim_module_num(TIM_MODULE_1)},
    #endif
    #ifdef TIM1_CH4_PE14_REMAP
    {GPIO_PE14, HAL_LL_TIM1_BASE_ADDR, HAL_LL_TIM_CHANNEL_4, HAL_LL_TIM1_GPIO_AF_2, hal_ll_tim_module_num(TIM_MODULE_1)},
    #endif
    #endif

    // STM32F1xx,TIM2_REMAP - pins are set only for no remap and full remap.
    #ifdef TIM_MODULE_2
    #ifdef TIM2_CH1_PA0
    {GPIO_PA0, HAL_LL_TIM2_BASE_ADDR, HAL_LL_TIM_CHANNEL_1, HAL_LL_TIM_REMAP_DISABLE, hal_ll_tim_module_num(TIM_MODULE_2)},
    #endif
    #ifdef TIM2_CH1_PA0_AF1
    {GPIO_PA0, HAL_LL_TIM2_BASE_ADDR, HAL_LL_TIM_CHANNEL_1, HAL_LL_TIM2_GPIO_AF1, hal_ll_tim_module_num(TIM_MODULE_2)},
    #endif
    #ifdef TIM2_CH1_PA0_AF2
    {GPIO_PA0, HAL_LL_TIM2_BASE_ADDR, HAL_LL_TIM_CHANNEL_1, HAL_LL_TIM2_GPIO_AF2, hal_ll_tim_module_num(TIM_MODULE_2)},
    #endif
    #ifdef TIM2_CH1_PA15
    {GPIO_PA15, HAL_LL_TIM2_BASE_ADDR, HAL_LL_TIM_CHANNEL_1, HAL_LL_TIM2_GPIO_AF, hal_ll_tim_module_num(TIM_MODULE_2)},
    #endif
    #ifdef TIM2_CH1_PA15_AF1
    {GPIO_PA15, HAL_LL_TIM2_BASE_ADDR, HAL_LL_TIM_CHANNEL_1, HAL_LL_TIM2_GPIO_AF1, hal_ll_tim_module_num(TIM_MODULE_2)},
    #endif
    #ifdef TIM2_CH1_PA15_AF2
    {GPIO_PA15, HAL_LL_TIM2_BASE_ADDR, HAL_LL_TIM_CHANNEL_1, HAL_LL_TIM2_GPIO_AF2, hal_ll_tim_module_num(TIM_MODULE_2)},
    #endif
    #ifdef TIM2_CH1_PA15_AF5
    {GPIO_PA15, HAL_LL_TIM2_BASE_ADDR, HAL_LL_TIM_CHANNEL_1, HAL_LL_TIM2_GPIO_AF5, hal_ll_tim_module_num(TIM_MODULE_2)},
    #endif
    #ifdef TIM2_CH1_PA5_AF1
    {GPIO_PA5, HAL_LL_TIM2_BASE_ADDR, HAL_LL_TIM_CHANNEL_1, HAL_LL_TIM2_GPIO_AF1, hal_ll_tim_module_num(TIM_MODULE_2)},
    #endif
    #ifdef TIM2_CH1_PA5_AF2
    {GPIO_PA5, HAL_LL_TIM2_BASE_ADDR, HAL_LL_TIM_CHANNEL_1, HAL_LL_TIM2_GPIO_AF2, hal_ll_tim_module_num(TIM_MODULE_2)},
    #endif
    #ifdef TIM2_CH1_PA5_AF5
    {GPIO_PA5, HAL_LL_TIM2_BASE_ADDR, HAL_LL_TIM_CHANNEL_1, HAL_LL_TIM2_GPIO_AF5, hal_ll_tim_module_num(TIM_MODULE_2)},
    #endif
    #ifdef TIM2_CH1_PA8_AF5
    {GPIO_PA8, HAL_LL_TIM2_BASE_ADDR, HAL_LL_TIM_CHANNEL_1, HAL_LL_TIM2_GPIO_AF5, hal_ll_tim_module_num(TIM_MODULE_2)},
    #endif
    #ifdef TIM2_CH1_PC4_AF2
    {GPIO_PC4, HAL_LL_TIM2_BASE_ADDR, HAL_LL_TIM_CHANNEL_1, HAL_LL_TIM2_GPIO_AF2, hal_ll_tim_module_num(TIM_MODULE_2)},
    #endif
    #ifdef TIM2_CH1_PD3_AF2
    {GPIO_PD3, HAL_LL_TIM2_BASE_ADDR, HAL_LL_TIM_CHANNEL_1, HAL_LL_TIM2_GPIO_AF2, hal_ll_tim_module_num(TIM_MODULE_2)},
    #endif
    #ifdef TIM2_CH1_PE9_AF0
    {GPIO_PE9, HAL_LL_TIM2_BASE_ADDR, HAL_LL_TIM_CHANNEL_1, HAL_LL_TIM2_GPIO_AF0, hal_ll_tim_module_num(TIM_MODULE_2)},
    #endif
    #ifdef TIM2_CH2_PA1
    {GPIO_PA1, HAL_LL_TIM2_BASE_ADDR, HAL_LL_TIM_CHANNEL_2, HAL_LL_TIM_REMAP_DISABLE, hal_ll_tim_module_num(TIM_MODULE_2)},
    #endif
    #ifdef TIM2_CH2_PA1_AF1
    {GPIO_PA1, HAL_LL_TIM2_BASE_ADDR, HAL_LL_TIM_CHANNEL_2, HAL_LL_TIM2_GPIO_AF1, hal_ll_tim_module_num(TIM_MODULE_2)},
    #endif
    #ifdef TIM2_CH2_PA1_AF2
    {GPIO_PA1, HAL_LL_TIM2_BASE_ADDR, HAL_LL_TIM_CHANNEL_2, HAL_LL_TIM2_GPIO_AF2, hal_ll_tim_module_num(TIM_MODULE_2)},
    #endif
    #ifdef TIM2_CH2_PB0_AF2
    {GPIO_PB0, HAL_LL_TIM2_BASE_ADDR, HAL_LL_TIM_CHANNEL_2, HAL_LL_TIM2_GPIO_AF2, hal_ll_tim_module_num(TIM_MODULE_2)},
    #endif
    #ifdef TIM2_CH2_PB3
    {GPIO_PB3, HAL_LL_TIM2_BASE_ADDR, HAL_LL_TIM_CHANNEL_2, HAL_LL_TIM2_GPIO_AF, hal_ll_tim_module_num(TIM_MODULE_2)},
    #endif
    #ifdef TIM2_CH2_PB3_AF1
    {GPIO_PB3, HAL_LL_TIM2_BASE_ADDR, HAL_LL_TIM_CHANNEL_2, HAL_LL_TIM2_GPIO_AF1, hal_ll_tim_module_num(TIM_MODULE_2)},
    #endif
    #ifdef TIM2_CH2_PB3_AF2
    {GPIO_PB3, HAL_LL_TIM2_BASE_ADDR, HAL_LL_TIM_CHANNEL_2, HAL_LL_TIM2_GPIO_AF2, hal_ll_tim_module_num(TIM_MODULE_2)},
    #endif
    #ifdef TIM2_CH2_PC5_AF2
    {GPIO_PC5, HAL_LL_TIM2_BASE_ADDR, HAL_LL_TIM_CHANNEL_2, HAL_LL_TIM2_GPIO_AF2, hal_ll_tim_module_num(TIM_MODULE_2)},
    #endif
    #ifdef TIM2_CH2_PD4_AF2
    {GPIO_PD4, HAL_LL_TIM2_BASE_ADDR, HAL_LL_TIM_CHANNEL_2, HAL_LL_TIM2_GPIO_AF2, hal_ll_tim_module_num(TIM_MODULE_2)},
    #endif
    #ifdef TIM2_CH2_PE10_AF0
    {GPIO_PE10, HAL_LL_TIM2_BASE_ADDR, HAL_LL_TIM_CHANNEL_2, HAL_LL_TIM2_GPIO_AF0, hal_ll_tim_module_num(TIM_MODULE_2)},
    #endif
    #ifdef TIM2_CH3_PA10_AF5
    {GPIO_PA10, HAL_LL_TIM2_BASE_ADDR, HAL_LL_TIM_CHANNEL_3, HAL_LL_TIM2_GPIO_AF5, hal_ll_tim_module_num(TIM_MODULE_2)},
    #endif
    #ifdef TIM2_CH3_PA2
    {GPIO_PA2, HAL_LL_TIM2_BASE_ADDR, HAL_LL_TIM_CHANNEL_3, HAL_LL_TIM_REMAP_DISABLE, hal_ll_tim_module_num(TIM_MODULE_2)},
    #endif
    #ifdef TIM2_CH3_PA2_AF1
    {GPIO_PA2, HAL_LL_TIM2_BASE_ADDR, HAL_LL_TIM_CHANNEL_3, HAL_LL_TIM2_GPIO_AF1, hal_ll_tim_module_num(TIM_MODULE_2)},
    #endif
    #ifdef TIM2_CH3_PA2_AF2
    {GPIO_PA2, HAL_LL_TIM2_BASE_ADDR, HAL_LL_TIM_CHANNEL_3, HAL_LL_TIM2_GPIO_AF2, hal_ll_tim_module_num(TIM_MODULE_2)},
    #endif
    #ifdef TIM2_CH3_PA9_AF10
    {GPIO_PA9, HAL_LL_TIM2_BASE_ADDR, HAL_LL_TIM_CHANNEL_3, HAL_LL_TIM2_GPIO_AF10, hal_ll_tim_module_num(TIM_MODULE_2)},
    #endif
    #ifdef TIM2_CH3_PB0_AF5
    {GPIO_PB0, HAL_LL_TIM2_BASE_ADDR, HAL_LL_TIM_CHANNEL_3, HAL_LL_TIM2_GPIO_AF5, hal_ll_tim_module_num(TIM_MODULE_2)},
    #endif
    #ifdef TIM2_CH3_PB10
    {GPIO_PB10, HAL_LL_TIM2_BASE_ADDR, HAL_LL_TIM_CHANNEL_3, HAL_LL_TIM2_GPIO_AF, hal_ll_tim_module_num(TIM_MODULE_2)},
    #endif
    #ifdef TIM2_CH3_PB10_AF1
    {GPIO_PB10, HAL_LL_TIM2_BASE_ADDR, HAL_LL_TIM_CHANNEL_3, HAL_LL_TIM2_GPIO_AF1, hal_ll_tim_module_num(TIM_MODULE_2)},
    #endif
    #ifdef TIM2_CH3_PB10_AF2
    {GPIO_PB10, HAL_LL_TIM2_BASE_ADDR, HAL_LL_TIM_CHANNEL_3, HAL_LL_TIM2_GPIO_AF2, hal_ll_tim_module_num(TIM_MODULE_2)},
    #endif
    #ifdef TIM2_CH3_PB6_AF5
    {GPIO_PB6, HAL_LL_TIM2_BASE_ADDR, HAL_LL_TIM_CHANNEL_3, HAL_LL_TIM2_GPIO_AF5, hal_ll_tim_module_num(TIM_MODULE_2)},
    #endif
    #ifdef TIM2_CH3_PC6_AF2
    {GPIO_PC6, HAL_LL_TIM2_BASE_ADDR, HAL_LL_TIM_CHANNEL_3, HAL_LL_TIM2_GPIO_AF2, hal_ll_tim_module_num(TIM_MODULE_2)},
    #endif
    #ifdef TIM2_CH3_PD7_AF2
    {GPIO_PD7, HAL_LL_TIM2_BASE_ADDR, HAL_LL_TIM_CHANNEL_3, HAL_LL_TIM2_GPIO_AF2, hal_ll_tim_module_num(TIM_MODULE_2)},
    #endif
    #ifdef TIM2_CH3_PE11_AF0
    {GPIO_PE11, HAL_LL_TIM2_BASE_ADDR, HAL_LL_TIM_CHANNEL_3, HAL_LL_TIM2_GPIO_AF0, hal_ll_tim_module_num(TIM_MODULE_2)},
    #endif
    #ifdef TIM2_CH4_PA10_AF10
    {GPIO_PA10, HAL_LL_TIM2_BASE_ADDR, HAL_LL_TIM_CHANNEL_4, HAL_LL_TIM2_GPIO_AF10, hal_ll_tim_module_num(TIM_MODULE_2)},
    #endif
    #ifdef TIM2_CH4_PA3
    {GPIO_PA3, HAL_LL_TIM2_BASE_ADDR, HAL_LL_TIM_CHANNEL_4, HAL_LL_TIM_REMAP_DISABLE, hal_ll_tim_module_num(TIM_MODULE_2)},
    #endif
    #ifdef TIM2_CH4_PA3_AF1
    {GPIO_PA3, HAL_LL_TIM2_BASE_ADDR, HAL_LL_TIM_CHANNEL_4, HAL_LL_TIM2_GPIO_AF1, hal_ll_tim_module_num(TIM_MODULE_2)},
    #endif
    #ifdef TIM2_CH4_PA3_AF2
    {GPIO_PA3, HAL_LL_TIM2_BASE_ADDR, HAL_LL_TIM_CHANNEL_4, HAL_LL_TIM2_GPIO_AF2, hal_ll_tim_module_num(TIM_MODULE_2)},
    #endif
    #ifdef TIM2_CH4_PB1_AF5
    {GPIO_PB1, HAL_LL_TIM2_BASE_ADDR, HAL_LL_TIM_CHANNEL_4, HAL_LL_TIM2_GPIO_AF5, hal_ll_tim_module_num(TIM_MODULE_2)},
    #endif
    #ifdef TIM2_CH4_PB11
    {GPIO_PB11, HAL_LL_TIM2_BASE_ADDR, HAL_LL_TIM_CHANNEL_4, HAL_LL_TIM2_GPIO_AF, hal_ll_tim_module_num(TIM_MODULE_2)},
    #endif
    #ifdef TIM2_CH4_PB11_AF1
    {GPIO_PB11, HAL_LL_TIM2_BASE_ADDR, HAL_LL_TIM_CHANNEL_4, HAL_LL_TIM2_GPIO_AF1, hal_ll_tim_module_num(TIM_MODULE_2)},
    #endif
    #ifdef TIM2_CH4_PB11_AF2
    {GPIO_PB11, HAL_LL_TIM2_BASE_ADDR, HAL_LL_TIM_CHANNEL_4, HAL_LL_TIM2_GPIO_AF2, hal_ll_tim_module_num(TIM_MODULE_2)},
    #endif
    #ifdef TIM2_CH4_PB7_AF5
    {GPIO_PB7, HAL_LL_TIM2_BASE_ADDR, HAL_LL_TIM_CHANNEL_4, HAL_LL_TIM2_GPIO_AF5, hal_ll_tim_module_num(TIM_MODULE_2)},
    #endif
    #ifdef TIM2_CH4_PC7_AF2
    {GPIO_PC7, HAL_LL_TIM2_BASE_ADDR, HAL_LL_TIM_CHANNEL_4, HAL_LL_TIM2_GPIO_AF2, hal_ll_tim_module_num(TIM_MODULE_2)},
    #endif
    #ifdef TIM2_CH4_PD6_AF2
    {GPIO_PD6, HAL_LL_TIM2_BASE_ADDR, HAL_LL_TIM_CHANNEL_4, HAL_LL_TIM2_GPIO_AF2, hal_ll_tim_module_num(TIM_MODULE_2)},
    #endif
    #ifdef TIM2_CH4_PE12_AF0
    {GPIO_PE12, HAL_LL_TIM2_BASE_ADDR, HAL_LL_TIM_CHANNEL_4, HAL_LL_TIM2_GPIO_AF0, hal_ll_tim_module_num(TIM_MODULE_2)},
    #endif
    #endif

    #ifdef TIM_MODULE_3
    #ifdef TIM3_CH1_PA6
    {GPIO_PA6, HAL_LL_TIM3_BASE_ADDR, HAL_LL_TIM_CHANNEL_1, HAL_LL_TIM_REMAP_DISABLE, hal_ll_tim_module_num(TIM_MODULE_3)},
    #endif
    #ifdef TIM3_CH1_PA6_AF1
    {GPIO_PA6, HAL_LL_TIM3_BASE_ADDR, HAL_LL_TIM_CHANNEL_1, HAL_LL_TIM3_GPIO_AF1, hal_ll_tim_module_num(TIM_MODULE_3)},
    #endif
    #ifdef TIM3_CH1_PA6_AF2
    {GPIO_PA6, HAL_LL_TIM3_BASE_ADDR, HAL_LL_TIM_CHANNEL_1, HAL_LL_TIM3_GPIO_AF2, hal_ll_tim_module_num(TIM_MODULE_3)},
    #endif
    #ifdef TIM3_CH1_PB4_AF1
    {GPIO_PB4, HAL_LL_TIM3_BASE_ADDR, HAL_LL_TIM_CHANNEL_1, HAL_LL_TIM3_GPIO_AF1, hal_ll_tim_module_num(TIM_MODULE_3)},
    #endif
    #ifdef TIM3_CH1_PB4_AF2
    {GPIO_PB4, HAL_LL_TIM3_BASE_ADDR, HAL_LL_TIM_CHANNEL_1, HAL_LL_TIM3_GPIO_AF2, hal_ll_tim_module_num(TIM_MODULE_3)},
    #endif
    #ifdef TIM3_CH1_PB4_REMAP
    {GPIO_PB4, HAL_LL_TIM3_BASE_ADDR, HAL_LL_TIM_CHANNEL_1, HAL_LL_TIM3_GPIO_AF_1, hal_ll_tim_module_num(TIM_MODULE_3)},
    #endif
    #ifdef TIM3_CH1_PC6_AF0
    {GPIO_PC6, HAL_LL_TIM3_BASE_ADDR, HAL_LL_TIM_CHANNEL_1, HAL_LL_TIM3_GPIO_AF0, hal_ll_tim_module_num(TIM_MODULE_3)},
    #endif
    #ifdef TIM3_CH1_PC6_AF1
    {GPIO_PC6, HAL_LL_TIM3_BASE_ADDR, HAL_LL_TIM_CHANNEL_1, HAL_LL_TIM3_GPIO_AF1, hal_ll_tim_module_num(TIM_MODULE_3)},
    #endif
    #ifdef TIM3_CH1_PC6_AF2
    {GPIO_PC6, HAL_LL_TIM3_BASE_ADDR, HAL_LL_TIM_CHANNEL_1, HAL_LL_TIM3_GPIO_AF2, hal_ll_tim_module_num(TIM_MODULE_3)},
    #endif
    #ifdef TIM3_CH1_PC6_REMAP
    {GPIO_PC6, HAL_LL_TIM3_BASE_ADDR, HAL_LL_TIM_CHANNEL_1, HAL_LL_TIM3_GPIO_AF_2, hal_ll_tim_module_num(TIM_MODULE_3)},
    #endif
    #ifdef TIM3_CH1_PE2_AF2
    {GPIO_PE2, HAL_LL_TIM3_BASE_ADDR, HAL_LL_TIM_CHANNEL_1, HAL_LL_TIM3_GPIO_AF2, hal_ll_tim_module_num(TIM_MODULE_3)},
    #endif
    #ifdef TIM3_CH1_PE3_AF0
    {GPIO_PE3, HAL_LL_TIM3_BASE_ADDR, HAL_LL_TIM_CHANNEL_1, HAL_LL_TIM3_GPIO_AF0, hal_ll_tim_module_num(TIM_MODULE_3)},
    #endif
    #ifdef TIM3_CH1_PE3_AF2
    {GPIO_PE3, HAL_LL_TIM3_BASE_ADDR, HAL_LL_TIM_CHANNEL_1, HAL_LL_TIM3_GPIO_AF2, hal_ll_tim_module_num(TIM_MODULE_3)},
    #endif
    #ifdef TIM3_CH2_PA4_AF2
    {GPIO_PA4, HAL_LL_TIM3_BASE_ADDR, HAL_LL_TIM_CHANNEL_2, HAL_LL_TIM3_GPIO_AF2, hal_ll_tim_module_num(TIM_MODULE_3)},
    #endif
    #ifdef TIM3_CH2_PA7
    {GPIO_PA7, HAL_LL_TIM3_BASE_ADDR, HAL_LL_TIM_CHANNEL_2, HAL_LL_TIM_REMAP_DISABLE, hal_ll_tim_module_num(TIM_MODULE_3)},
    #endif
    #ifdef TIM3_CH2_PA7_AF1
    {GPIO_PA7, HAL_LL_TIM3_BASE_ADDR, HAL_LL_TIM_CHANNEL_2, HAL_LL_TIM3_GPIO_AF1, hal_ll_tim_module_num(TIM_MODULE_3)},
    #endif
    #ifdef TIM3_CH2_PA7_AF2
    {GPIO_PA7, HAL_LL_TIM3_BASE_ADDR, HAL_LL_TIM_CHANNEL_2, HAL_LL_TIM3_GPIO_AF2, hal_ll_tim_module_num(TIM_MODULE_3)},
    #endif
    #ifdef TIM3_CH2_PB0_AF10
    {GPIO_PB0, HAL_LL_TIM3_BASE_ADDR, HAL_LL_TIM_CHANNEL_2, HAL_LL_TIM3_GPIO_AF10, hal_ll_tim_module_num(TIM_MODULE_3)},
    #endif
    #ifdef TIM3_CH2_PB5_AF1
    {GPIO_PB5, HAL_LL_TIM3_BASE_ADDR, HAL_LL_TIM_CHANNEL_2, HAL_LL_TIM3_GPIO_AF1, hal_ll_tim_module_num(TIM_MODULE_3)},
    #endif
    #ifdef TIM3_CH2_PB5_AF2
    {GPIO_PB5, HAL_LL_TIM3_BASE_ADDR, HAL_LL_TIM_CHANNEL_2, HAL_LL_TIM3_GPIO_AF2, hal_ll_tim_module_num(TIM_MODULE_3)},
    #endif
    #ifdef TIM3_CH2_PB5_AF4
    {GPIO_PB5, HAL_LL_TIM3_BASE_ADDR, HAL_LL_TIM_CHANNEL_2, HAL_LL_TIM3_GPIO_AF4, hal_ll_tim_module_num(TIM_MODULE_3)},
    #endif
    #ifdef TIM3_CH2_PB5_REMAP
    {GPIO_PB5, HAL_LL_TIM3_BASE_ADDR, HAL_LL_TIM_CHANNEL_2, HAL_LL_TIM3_GPIO_AF_1, hal_ll_tim_module_num(TIM_MODULE_3)},
    #endif
    #ifdef TIM3_CH2_PC7_AF0
    {GPIO_PC7, HAL_LL_TIM3_BASE_ADDR, HAL_LL_TIM_CHANNEL_2, HAL_LL_TIM3_GPIO_AF0, hal_ll_tim_module_num(TIM_MODULE_3)},
    #endif
    #ifdef TIM3_CH2_PC7_AF1
    {GPIO_PC7, HAL_LL_TIM3_BASE_ADDR, HAL_LL_TIM_CHANNEL_2, HAL_LL_TIM3_GPIO_AF1, hal_ll_tim_module_num(TIM_MODULE_3)},
    #endif
    #ifdef TIM3_CH2_PC7_AF2
    {GPIO_PC7, HAL_LL_TIM3_BASE_ADDR, HAL_LL_TIM_CHANNEL_2, HAL_LL_TIM3_GPIO_AF2, hal_ll_tim_module_num(TIM_MODULE_3)},
    #endif
    #ifdef TIM3_CH2_PC7_REMAP
    {GPIO_PC7, HAL_LL_TIM3_BASE_ADDR, HAL_LL_TIM_CHANNEL_2, HAL_LL_TIM3_GPIO_AF_2, hal_ll_tim_module_num(TIM_MODULE_3)},
    #endif
    #ifdef TIM3_CH2_PE3_AF2
    {GPIO_PE3, HAL_LL_TIM3_BASE_ADDR, HAL_LL_TIM_CHANNEL_2, HAL_LL_TIM3_GPIO_AF2, hal_ll_tim_module_num(TIM_MODULE_3)},
    #endif
    #ifdef TIM3_CH2_PE4_AF0
    {GPIO_PE4, HAL_LL_TIM3_BASE_ADDR, HAL_LL_TIM_CHANNEL_2, HAL_LL_TIM3_GPIO_AF0, hal_ll_tim_module_num(TIM_MODULE_3)},
    #endif
    #ifdef TIM3_CH2_PE4_AF2
    {GPIO_PE4, HAL_LL_TIM3_BASE_ADDR, HAL_LL_TIM_CHANNEL_2, HAL_LL_TIM3_GPIO_AF2, hal_ll_tim_module_num(TIM_MODULE_3)},
    #endif
    #ifdef TIM3_CH3_PB0
    {GPIO_PB0, HAL_LL_TIM3_BASE_ADDR, HAL_LL_TIM_CHANNEL_3, HAL_LL_TIM_REMAP_DISABLE, hal_ll_tim_module_num(TIM_MODULE_3)},
    #endif
    #ifdef TIM3_CH3_PB0_AF1
    {GPIO_PB0, HAL_LL_TIM3_BASE_ADDR, HAL_LL_TIM_CHANNEL_3, HAL_LL_TIM3_GPIO_AF1, hal_ll_tim_module_num(TIM_MODULE_3)},
    #endif
    #ifdef TIM3_CH3_PB0_AF2
    {GPIO_PB0, HAL_LL_TIM3_BASE_ADDR, HAL_LL_TIM_CHANNEL_3, HAL_LL_TIM3_GPIO_AF2, hal_ll_tim_module_num(TIM_MODULE_3)},
    #endif
    #ifdef TIM3_CH3_PB6_AF10
    {GPIO_PB6, HAL_LL_TIM3_BASE_ADDR, HAL_LL_TIM_CHANNEL_3, HAL_LL_TIM3_GPIO_AF10, hal_ll_tim_module_num(TIM_MODULE_3)},
    #endif
    #ifdef TIM3_CH3_PC8_AF0
    {GPIO_PC8, HAL_LL_TIM3_BASE_ADDR, HAL_LL_TIM_CHANNEL_3, HAL_LL_TIM3_GPIO_AF0, hal_ll_tim_module_num(TIM_MODULE_3)},
    #endif
    #ifdef TIM3_CH3_PC8_AF1
    {GPIO_PC8, HAL_LL_TIM3_BASE_ADDR, HAL_LL_TIM_CHANNEL_3, HAL_LL_TIM3_GPIO_AF1, hal_ll_tim_module_num(TIM_MODULE_3)},
    #endif
    #ifdef TIM3_CH3_PC8_AF2
    {GPIO_PC8, HAL_LL_TIM3_BASE_ADDR, HAL_LL_TIM_CHANNEL_3, HAL_LL_TIM3_GPIO_AF2, hal_ll_tim_module_num(TIM_MODULE_3)},
    #endif
    #ifdef TIM3_CH3_PC8_REMAP
    {GPIO_PC8, HAL_LL_TIM3_BASE_ADDR, HAL_LL_TIM_CHANNEL_3, HAL_LL_TIM3_GPIO_AF_2, hal_ll_tim_module_num(TIM_MODULE_3)},
    #endif
    #ifdef TIM3_CH3_PE4_AF2
    {GPIO_PE4, HAL_LL_TIM3_BASE_ADDR, HAL_LL_TIM_CHANNEL_3, HAL_LL_TIM3_GPIO_AF2, hal_ll_tim_module_num(TIM_MODULE_3)},
    #endif
    #ifdef TIM3_CH3_PE5_AF0
    {GPIO_PE5, HAL_LL_TIM3_BASE_ADDR, HAL_LL_TIM_CHANNEL_3, HAL_LL_TIM3_GPIO_AF0, hal_ll_tim_module_num(TIM_MODULE_3)},
    #endif
    #ifdef TIM3_CH3_PE5_AF2
    {GPIO_PE5, HAL_LL_TIM3_BASE_ADDR, HAL_LL_TIM_CHANNEL_3, HAL_LL_TIM3_GPIO_AF2, hal_ll_tim_module_num(TIM_MODULE_3)},
    #endif
    #ifdef TIM3_CH4_PB1
    {GPIO_PB1, HAL_LL_TIM3_BASE_ADDR, HAL_LL_TIM_CHANNEL_4, HAL_LL_TIM_REMAP_DISABLE, hal_ll_tim_module_num(TIM_MODULE_3)},
    #endif
    #ifdef TIM3_CH4_PB1_AF1
    {GPIO_PB1, HAL_LL_TIM3_BASE_ADDR, HAL_LL_TIM_CHANNEL_4, HAL_LL_TIM3_GPIO_AF1, hal_ll_tim_module_num(TIM_MODULE_3)},
    #endif
    #ifdef TIM3_CH4_PB1_AF2
    {GPIO_PB1, HAL_LL_TIM3_BASE_ADDR, HAL_LL_TIM_CHANNEL_4, HAL_LL_TIM3_GPIO_AF2, hal_ll_tim_module_num(TIM_MODULE_3)},
    #endif
    #ifdef TIM3_CH4_PB7_AF10
    {GPIO_PB7, HAL_LL_TIM3_BASE_ADDR, HAL_LL_TIM_CHANNEL_4, HAL_LL_TIM3_GPIO_AF10, hal_ll_tim_module_num(TIM_MODULE_3)},
    #endif
    #ifdef TIM3_CH4_PC9_AF0
    {GPIO_PC9, HAL_LL_TIM3_BASE_ADDR, HAL_LL_TIM_CHANNEL_4, HAL_LL_TIM3_GPIO_AF0, hal_ll_tim_module_num(TIM_MODULE_3)},
    #endif
    #ifdef TIM3_CH4_PC9_AF1
    {GPIO_PC9, HAL_LL_TIM3_BASE_ADDR, HAL_LL_TIM_CHANNEL_4, HAL_LL_TIM3_GPIO_AF1, hal_ll_tim_module_num(TIM_MODULE_3)},
    #endif
    #ifdef TIM3_CH4_PC9_AF2
    {GPIO_PC9, HAL_LL_TIM3_BASE_ADDR, HAL_LL_TIM_CHANNEL_4, HAL_LL_TIM3_GPIO_AF2, hal_ll_tim_module_num(TIM_MODULE_3)},
    #endif
    #ifdef TIM3_CH4_PC9_REMAP
    {GPIO_PC9, HAL_LL_TIM3_BASE_ADDR, HAL_LL_TIM_CHANNEL_4, HAL_LL_TIM3_GPIO_AF_2, hal_ll_tim_module_num(TIM_MODULE_3)},
    #endif
    #ifdef TIM3_CH4_PE5_AF2
    {GPIO_PE5, HAL_LL_TIM3_BASE_ADDR, HAL_LL_TIM_CHANNEL_4, HAL_LL_TIM3_GPIO_AF2, hal_ll_tim_module_num(TIM_MODULE_3)},
    #endif
    #ifdef TIM3_CH4_PE6_AF0
    {GPIO_PE6, HAL_LL_TIM3_BASE_ADDR, HAL_LL_TIM_CHANNEL_4, HAL_LL_TIM3_GPIO_AF0, hal_ll_tim_module_num(TIM_MODULE_3)},
    #endif
    #ifdef TIM3_CH4_PE6_AF2
    {GPIO_PE6, HAL_LL_TIM3_BASE_ADDR, HAL_LL_TIM_CHANNEL_4, HAL_LL_TIM3_GPIO_AF2, hal_ll_tim_module_num(TIM_MODULE_3)},
    #endif
    #endif

    #ifdef TIM_MODULE_4
    #ifdef TIM4_CH1_PA11_AF10
    {GPIO_PA11, HAL_LL_TIM4_BASE_ADDR, HAL_LL_TIM_CHANNEL_1, HAL_LL_TIM4_GPIO_AF10, hal_ll_tim_module_num(TIM_MODULE_4)},
    #endif
    #ifdef TIM4_CH1_PB6
    {GPIO_PB6, HAL_LL_TIM4_BASE_ADDR, HAL_LL_TIM_CHANNEL_1, HAL_LL_TIM_REMAP_DISABLE, hal_ll_tim_module_num(TIM_MODULE_4)},
    #endif
    #ifdef TIM4_CH1_PB6_AF2
    {GPIO_PB6, HAL_LL_TIM4_BASE_ADDR, HAL_LL_TIM_CHANNEL_1, HAL_LL_TIM4_GPIO_AF2, hal_ll_tim_module_num(TIM_MODULE_4)},
    #endif
    #ifdef TIM4_CH1_PD12_AF2
    {GPIO_PD12, HAL_LL_TIM4_BASE_ADDR, HAL_LL_TIM_CHANNEL_1, HAL_LL_TIM4_GPIO_AF2, hal_ll_tim_module_num(TIM_MODULE_4)},
    #endif
    #ifdef TIM4_CH1_PD12_REMAP
    {GPIO_PD12, HAL_LL_TIM4_BASE_ADDR, HAL_LL_TIM_CHANNEL_1, HAL_LL_TIM4_GPIO_AF, hal_ll_tim_module_num(TIM_MODULE_4)},
    #endif
    #ifdef TIM4_CH2_PA12_AF10
    {GPIO_PA12, HAL_LL_TIM4_BASE_ADDR, HAL_LL_TIM_CHANNEL_2, HAL_LL_TIM4_GPIO_AF10, hal_ll_tim_module_num(TIM_MODULE_4)},
    #endif
    #ifdef TIM4_CH2_PB7
    {GPIO_PB7, HAL_LL_TIM4_BASE_ADDR, HAL_LL_TIM_CHANNEL_2, HAL_LL_TIM_REMAP_DISABLE, hal_ll_tim_module_num(TIM_MODULE_4)},
    #endif
    #ifdef TIM4_CH2_PB7_AF2
    {GPIO_PB7, HAL_LL_TIM4_BASE_ADDR, HAL_LL_TIM_CHANNEL_2, HAL_LL_TIM4_GPIO_AF2, hal_ll_tim_module_num(TIM_MODULE_4)},
    #endif
    #ifdef TIM4_CH2_PD13_AF2
    {GPIO_PD13, HAL_LL_TIM4_BASE_ADDR, HAL_LL_TIM_CHANNEL_2, HAL_LL_TIM4_GPIO_AF2, hal_ll_tim_module_num(TIM_MODULE_4)},
    #endif
    #ifdef TIM4_CH2_PD13_REMAP
    {GPIO_PD13, HAL_LL_TIM4_BASE_ADDR, HAL_LL_TIM_CHANNEL_2, HAL_LL_TIM4_GPIO_AF, hal_ll_tim_module_num(TIM_MODULE_4)},
    #endif
    #ifdef TIM4_CH3_PA13_AF10
    {GPIO_PA13, HAL_LL_TIM4_BASE_ADDR, HAL_LL_TIM_CHANNEL_3, HAL_LL_TIM4_GPIO_AF10, hal_ll_tim_module_num(TIM_MODULE_4)},
    #endif
    #ifdef TIM4_CH3_PB8
    {GPIO_PB8, HAL_LL_TIM4_BASE_ADDR, HAL_LL_TIM_CHANNEL_3, HAL_LL_TIM_REMAP_DISABLE, hal_ll_tim_module_num(TIM_MODULE_4)},
    #endif
    #ifdef TIM4_CH3_PB8_AF2
    {GPIO_PB8, HAL_LL_TIM4_BASE_ADDR, HAL_LL_TIM_CHANNEL_3, HAL_LL_TIM4_GPIO_AF2, hal_ll_tim_module_num(TIM_MODULE_4)},
    #endif
    #ifdef TIM4_CH3_PD14_AF2
    {GPIO_PD14, HAL_LL_TIM4_BASE_ADDR, HAL_LL_TIM_CHANNEL_3, HAL_LL_TIM4_GPIO_AF2, hal_ll_tim_module_num(TIM_MODULE_4)},
    #endif
    #ifdef TIM4_CH3_PD14_REMAP
    {GPIO_PD14, HAL_LL_TIM4_BASE_ADDR, HAL_LL_TIM_CHANNEL_3, HAL_LL_TIM4_GPIO_AF, hal_ll_tim_module_num(TIM_MODULE_4)},
    #endif
    #ifdef TIM4_CH4_PB9
    {GPIO_PB9, HAL_LL_TIM4_BASE_ADDR, HAL_LL_TIM_CHANNEL_4, HAL_LL_TIM_REMAP_DISABLE, hal_ll_tim_module_num(TIM_MODULE_4)},
    #endif
    #ifdef TIM4_CH4_PB9_AF2
    {GPIO_PB9, HAL_LL_TIM4_BASE_ADDR, HAL_LL_TIM_CHANNEL_4, HAL_LL_TIM4_GPIO_AF2, hal_ll_tim_module_num(TIM_MODULE_4)},
    #endif
    #ifdef TIM4_CH4_PD15_AF2
    {GPIO_PD15, HAL_LL_TIM4_BASE_ADDR, HAL_LL_TIM_CHANNEL_4, HAL_LL_TIM4_GPIO_AF2, hal_ll_tim_module_num(TIM_MODULE_4)},
    #endif
    #ifdef TIM4_CH4_PD15_REMAP
    {GPIO_PD15, HAL_LL_TIM4_BASE_ADDR, HAL_LL_TIM_CHANNEL_4, HAL_LL_TIM4_GPIO_AF, hal_ll_tim_module_num(TIM_MODULE_4)},
    #endif
    #ifdef TIM4_CH4_PF6_AF2
    {GPIO_PF6, HAL_LL_TIM4_BASE_ADDR, HAL_LL_TIM_CHANNEL_4, HAL_LL_TIM4_GPIO_AF2, hal_ll_tim_module_num(TIM_MODULE_4)},
    #endif
    #endif

    #ifdef TIM_MODULE_5
    #ifdef TIM5_CH1_PA0_AF2
    {GPIO_PA0, HAL_LL_TIM5_BASE_ADDR, HAL_LL_TIM_CHANNEL_1, HAL_LL_TIM5_GPIO_AF2, hal_ll_tim_module_num(TIM_MODULE_5)},
    #endif
    #ifdef TIM5_CH1_PA8_AF2
    {GPIO_PA8, HAL_LL_TIM5_BASE_ADDR, HAL_LL_TIM_CHANNEL_1, HAL_LL_TIM5_GPIO_AF2, hal_ll_tim_module_num(TIM_MODULE_5)},
    #endif
    #ifdef TIM5_CH1_PC0_AF2
    {GPIO_PC0, HAL_LL_TIM5_BASE_ADDR, HAL_LL_TIM_CHANNEL_1, HAL_LL_TIM5_GPIO_AF2, hal_ll_tim_module_num(TIM_MODULE_5)},
    #endif
    #ifdef TIM5_CH1_PF6_AF2
    {GPIO_PF6, HAL_LL_TIM5_BASE_ADDR, HAL_LL_TIM_CHANNEL_1, HAL_LL_TIM5_GPIO_AF2, hal_ll_tim_module_num(TIM_MODULE_5)},
    #endif
    #ifdef TIM5_CH1_PH10_AF2
    {GPIO_PH10, HAL_LL_TIM5_BASE_ADDR, HAL_LL_TIM_CHANNEL_1, HAL_LL_TIM5_GPIO_AF2, hal_ll_tim_module_num(TIM_MODULE_5)},
    #endif
    #ifdef TIM5_CH2_PA1_AF2
    {GPIO_PA1, HAL_LL_TIM5_BASE_ADDR, HAL_LL_TIM_CHANNEL_2, HAL_LL_TIM5_GPIO_AF2, hal_ll_tim_module_num(TIM_MODULE_5)},
    #endif
    #ifdef TIM5_CH2_PA11_AF2
    {GPIO_PA11, HAL_LL_TIM5_BASE_ADDR, HAL_LL_TIM_CHANNEL_2, HAL_LL_TIM5_GPIO_AF2, hal_ll_tim_module_num(TIM_MODULE_5)},
    #endif
    #ifdef TIM5_CH2_PC1_AF2
    {GPIO_PC1, HAL_LL_TIM5_BASE_ADDR, HAL_LL_TIM_CHANNEL_2, HAL_LL_TIM5_GPIO_AF2, hal_ll_tim_module_num(TIM_MODULE_5)},
    #endif
    #ifdef TIM5_CH2_PF7_AF2
    {GPIO_PF7, HAL_LL_TIM5_BASE_ADDR, HAL_LL_TIM_CHANNEL_2, HAL_LL_TIM5_GPIO_AF2, hal_ll_tim_module_num(TIM_MODULE_5)},
    #endif
    #ifdef TIM5_CH2_PH11_AF2
    {GPIO_PH11, HAL_LL_TIM5_BASE_ADDR, HAL_LL_TIM_CHANNEL_2, HAL_LL_TIM5_GPIO_AF2, hal_ll_tim_module_num(TIM_MODULE_5)},
    #endif
    #ifdef TIM5_CH3_PA12_AF2
    {GPIO_PA12, HAL_LL_TIM5_BASE_ADDR, HAL_LL_TIM_CHANNEL_3, HAL_LL_TIM5_GPIO_AF2, hal_ll_tim_module_num(TIM_MODULE_5)},
    #endif
    #ifdef TIM5_CH3_PA2_AF2
    {GPIO_PA2, HAL_LL_TIM5_BASE_ADDR, HAL_LL_TIM_CHANNEL_3, HAL_LL_TIM5_GPIO_AF2, hal_ll_tim_module_num(TIM_MODULE_5)},
    #endif
    #ifdef TIM5_CH3_PC2_AF2
    {GPIO_PC2, HAL_LL_TIM5_BASE_ADDR, HAL_LL_TIM_CHANNEL_3, HAL_LL_TIM5_GPIO_AF2, hal_ll_tim_module_num(TIM_MODULE_5)},
    #endif
    #ifdef TIM5_CH3_PF8_AF2
    {GPIO_PF8, HAL_LL_TIM5_BASE_ADDR, HAL_LL_TIM_CHANNEL_3, HAL_LL_TIM5_GPIO_AF2, hal_ll_tim_module_num(TIM_MODULE_5)},
    #endif
    #ifdef TIM5_CH3_PH12_AF2
    {GPIO_PH12, HAL_LL_TIM5_BASE_ADDR, HAL_LL_TIM_CHANNEL_3, HAL_LL_TIM5_GPIO_AF2, hal_ll_tim_module_num(TIM_MODULE_5)},
    #endif
    #ifdef TIM5_CH4_PA13_AF2
    {GPIO_PA13, HAL_LL_TIM5_BASE_ADDR, HAL_LL_TIM_CHANNEL_4, HAL_LL_TIM5_GPIO_AF2, hal_ll_tim_module_num(TIM_MODULE_5)},
    #endif
    #ifdef TIM5_CH4_PA3_AF2
    {GPIO_PA3, HAL_LL_TIM5_BASE_ADDR, HAL_LL_TIM_CHANNEL_4, HAL_LL_TIM5_GPIO_AF2, hal_ll_tim_module_num(TIM_MODULE_5)},
    #endif
    #ifdef TIM5_CH4_PC3_AF2
    {GPIO_PC3, HAL_LL_TIM5_BASE_ADDR, HAL_LL_TIM_CHANNEL_4, HAL_LL_TIM5_GPIO_AF2, hal_ll_tim_module_num(TIM_MODULE_5)},
    #endif
    #ifdef TIM5_CH4_PF9_AF2
    {GPIO_PF9, HAL_LL_TIM5_BASE_ADDR, HAL_LL_TIM_CHANNEL_4, HAL_LL_TIM5_GPIO_AF2, hal_ll_tim_module_num(TIM_MODULE_5)},
    #endif
    #ifdef TIM5_CH4_PI0_AF2
    {GPIO_PI0, HAL_LL_TIM5_BASE_ADDR, HAL_LL_TIM_CHANNEL_4, HAL_LL_TIM5_GPIO_AF2, hal_ll_tim_module_num(TIM_MODULE_5)},
    #endif
    #endif

    #ifdef TIM_MODULE_8
    #ifdef TIM8_CH1_PA15_AF2
    {GPIO_PA15, HAL_LL_TIM8_BASE_ADDR, HAL_LL_TIM_CHANNEL_1, HAL_LL_TIM8_GPIO_AF2, hal_ll_tim_module_num(TIM_MODULE_8)},
    #endif
    #ifdef TIM8_CH1_PB6_AF5
    {GPIO_PB6, HAL_LL_TIM8_BASE_ADDR, HAL_LL_TIM_CHANNEL_1, HAL_LL_TIM8_GPIO_AF5, hal_ll_tim_module_num(TIM_MODULE_8)},
    #endif
    #ifdef TIM8_CH1_PC6_AF3
    {GPIO_PC6, HAL_LL_TIM8_BASE_ADDR, HAL_LL_TIM_CHANNEL_1, HAL_LL_TIM8_GPIO_AF3, hal_ll_tim_module_num(TIM_MODULE_8)},
    #endif
    #ifdef TIM8_CH1_PC6_AF4
    {GPIO_PC6, HAL_LL_TIM8_BASE_ADDR, HAL_LL_TIM_CHANNEL_1, HAL_LL_TIM8_GPIO_AF4, hal_ll_tim_module_num(TIM_MODULE_8)},
    #endif
    #ifdef TIM8_CH1_PI5_AF3
    {GPIO_PI5, HAL_LL_TIM8_BASE_ADDR, HAL_LL_TIM_CHANNEL_1, HAL_LL_TIM8_GPIO_AF3, hal_ll_tim_module_num(TIM_MODULE_8)},
    #endif
    #ifdef TIM8_CH2_PA14_AF5
    {GPIO_PA14, HAL_LL_TIM8_BASE_ADDR, HAL_LL_TIM_CHANNEL_2, HAL_LL_TIM8_GPIO_AF5, hal_ll_tim_module_num(TIM_MODULE_8)},
    #endif
    #ifdef TIM8_CH2_PB8_AF10
    {GPIO_PB8, HAL_LL_TIM8_BASE_ADDR, HAL_LL_TIM_CHANNEL_2, HAL_LL_TIM8_GPIO_AF10, hal_ll_tim_module_num(TIM_MODULE_8)},
    #endif
    #ifdef TIM8_CH2_PC7_AF3
    {GPIO_PC7, HAL_LL_TIM8_BASE_ADDR, HAL_LL_TIM_CHANNEL_2, HAL_LL_TIM8_GPIO_AF3, hal_ll_tim_module_num(TIM_MODULE_8)},
    #endif
    #ifdef TIM8_CH2_PC7_AF4
    {GPIO_PC7, HAL_LL_TIM8_BASE_ADDR, HAL_LL_TIM_CHANNEL_2, HAL_LL_TIM8_GPIO_AF4, hal_ll_tim_module_num(TIM_MODULE_8)},
    #endif
    #ifdef TIM8_CH2_PI6_AF3
    {GPIO_PI6, HAL_LL_TIM8_BASE_ADDR, HAL_LL_TIM_CHANNEL_2, HAL_LL_TIM8_GPIO_AF3, hal_ll_tim_module_num(TIM_MODULE_8)},
    #endif
    #ifdef TIM8_CH3_PB9_AF10
    {GPIO_PB9, HAL_LL_TIM8_BASE_ADDR, HAL_LL_TIM_CHANNEL_3, HAL_LL_TIM8_GPIO_AF10, hal_ll_tim_module_num(TIM_MODULE_8)},
    #endif
    #ifdef TIM8_CH3_PC8_AF3
    {GPIO_PC8, HAL_LL_TIM8_BASE_ADDR, HAL_LL_TIM_CHANNEL_3, HAL_LL_TIM8_GPIO_AF3, hal_ll_tim_module_num(TIM_MODULE_8)},
    #endif
    #ifdef TIM8_CH3_PC8_AF4
    {GPIO_PC8, HAL_LL_TIM8_BASE_ADDR, HAL_LL_TIM_CHANNEL_3, HAL_LL_TIM8_GPIO_AF4, hal_ll_tim_module_num(TIM_MODULE_8)},
    #endif
    #ifdef TIM8_CH3_PI7_AF3
    {GPIO_PI7, HAL_LL_TIM8_BASE_ADDR, HAL_LL_TIM_CHANNEL_3, HAL_LL_TIM8_GPIO_AF3, hal_ll_tim_module_num(TIM_MODULE_8)},
    #endif
    #ifdef TIM8_CH4_PC9_AF3
    {GPIO_PC9, HAL_LL_TIM8_BASE_ADDR, HAL_LL_TIM_CHANNEL_4, HAL_LL_TIM8_GPIO_AF3, hal_ll_tim_module_num(TIM_MODULE_8)},
    #endif
    #ifdef TIM8_CH4_PC9_AF4
    {GPIO_PC9, HAL_LL_TIM8_BASE_ADDR, HAL_LL_TIM_CHANNEL_4, HAL_LL_TIM8_GPIO_AF4, hal_ll_tim_module_num(TIM_MODULE_8)},
    #endif
    #ifdef TIM8_CH4_PD1_AF4
    {GPIO_PD1, HAL_LL_TIM8_BASE_ADDR, HAL_LL_TIM_CHANNEL_4, HAL_LL_TIM8_GPIO_AF4, hal_ll_tim_module_num(TIM_MODULE_8)},
    #endif
    #ifdef TIM8_CH4_PI2_AF3
    {GPIO_PI2, HAL_LL_TIM8_BASE_ADDR, HAL_LL_TIM_CHANNEL_4, HAL_LL_TIM8_GPIO_AF3, hal_ll_tim_module_num(TIM_MODULE_8)},
    #endif
    #endif

    #ifdef TIM_MODULE_9
    #ifdef TIM9_CH1_PA2
    {GPIO_PA2, HAL_LL_TIM9_BASE_ADDR, HAL_LL_TIM_CHANNEL_1, HAL_LL_TIM_REMAP_DISABLE, hal_ll_tim_module_num(TIM_MODULE_9)},
    #endif
    #ifdef TIM9_CH1_PE5_REMAP
    {GPIO_PE5, HAL_LL_TIM9_BASE_ADDR, HAL_LL_TIM_CHANNEL_1, ( HAL_LL_TIM9_GPIO_AF | HAL_LL_TIM_REMAP_ENABLE ), hal_ll_tim_module_num(TIM_MODULE_9)},
    #endif
    #ifdef TIM9_CH2_PA3
    {GPIO_PA3, HAL_LL_TIM9_BASE_ADDR, HAL_LL_TIM_CHANNEL_2, HAL_LL_TIM_REMAP_DISABLE, hal_ll_tim_module_num(TIM_MODULE_9)},
    #endif
    #ifdef TIM9_CH2_PE6_REMAP
    {GPIO_PE6, HAL_LL_TIM9_BASE_ADDR, HAL_LL_TIM_CHANNEL_2, ( HAL_LL_TIM9_GPIO_AF | HAL_LL_TIM_REMAP_ENABLE ), hal_ll_tim_module_num(TIM_MODULE_9)},
    #endif
    #endif

    #ifdef TIM_MODULE_10
    #ifdef TIM10_CH1_PB8
    {GPIO_PB8, HAL_LL_TIM10_BASE_ADDR, HAL_LL_TIM_CHANNEL_1, HAL_LL_TIM_REMAP_DISABLE, hal_ll_tim_module_num(TIM_MODULE_10)},
    #endif
    #ifdef TIM10_CH1_PF6_REMAP
    {GPIO_PF6, HAL_LL_TIM10_BASE_ADDR, HAL_LL_TIM_CHANNEL_1, ( HAL_LL_TIM10_GPIO_AF | HAL_LL_TIM_REMAP_ENABLE ), hal_ll_tim_module_num(TIM_MODULE_10)},
    #endif
    #endif

    #ifdef TIM_MODULE_11
    #ifdef TIM11_CH1_PB9
    {GPIO_PB9, HAL_LL_TIM11_BASE_ADDR, HAL_LL_TIM_CHANNEL_1, HAL_LL_TIM_REMAP_DISABLE, hal_ll_tim_module_num(TIM_MODULE_11)},
    #endif
    #ifdef TIM11_CH1_PF7_REMAP
    {GPIO_PF7, HAL_LL_TIM11_BASE_ADDR, HAL_LL_TIM_CHANNEL_1, ( HAL_LL_TIM11_GPIO_AF | HAL_LL_TIM_REMAP_ENABLE ), hal_ll_tim_module_num(TIM_MODULE_11)},
    #endif
    #endif

    #ifdef TIM_MODULE_12
    #ifdef TIM12_CH1_PA14_AF10
    {GPIO_PA14, HAL_LL_TIM12_BASE_ADDR, HAL_LL_TIM_CHANNEL_1, HAL_LL_TIM12_GPIO_AF10, hal_ll_tim_module_num(TIM_MODULE_12)},
    #endif
    #ifdef TIM12_CH1_PA4_AF10
    {GPIO_PA4, HAL_LL_TIM12_BASE_ADDR, HAL_LL_TIM_CHANNEL_1, HAL_LL_TIM12_GPIO_AF10, hal_ll_tim_module_num(TIM_MODULE_12)},
    #endif
    #ifdef TIM12_CH1_PB12_REMAP
    {GPIO_PB12, HAL_LL_TIM12_BASE_ADDR, HAL_LL_TIM_CHANNEL_1, ( HAL_LL_TIM12_GPIO_AF | HAL_LL_TIM_REMAP_ENABLE ), hal_ll_tim_module_num(TIM_MODULE_12)},
    #endif
    #ifdef TIM12_CH1_PB14
    {GPIO_PB14, HAL_LL_TIM12_BASE_ADDR, HAL_LL_TIM_CHANNEL_1, HAL_LL_TIM_REMAP_DISABLE, hal_ll_tim_module_num(TIM_MODULE_12)},
    #endif
    #ifdef TIM12_CH1_PB14_AF9
    {GPIO_PB14, HAL_LL_TIM12_BASE_ADDR, HAL_LL_TIM_CHANNEL_1, HAL_LL_TIM12_GPIO_AF9, hal_ll_tim_module_num(TIM_MODULE_12)},
    #endif
    #ifdef TIM12_CH1_PC4
    {GPIO_PC4, HAL_LL_TIM12_BASE_ADDR, HAL_LL_TIM_CHANNEL_1, HAL_LL_TIM_REMAP_DISABLE, hal_ll_tim_module_num(TIM_MODULE_12)},
    #endif
    #ifdef TIM12_CH2_PA15_AF10
    {GPIO_PA15, HAL_LL_TIM12_BASE_ADDR, HAL_LL_TIM_CHANNEL_2, HAL_LL_TIM12_GPIO_AF10, hal_ll_tim_module_num(TIM_MODULE_12)},
    #endif
    #ifdef TIM12_CH2_PA5_AF10
    {GPIO_PA5, HAL_LL_TIM12_BASE_ADDR, HAL_LL_TIM_CHANNEL_2, HAL_LL_TIM12_GPIO_AF10, hal_ll_tim_module_num(TIM_MODULE_12)},
    #endif
    #ifdef TIM12_CH2_PB13_REMAP
    {GPIO_PB13, HAL_LL_TIM12_BASE_ADDR, HAL_LL_TIM_CHANNEL_2, ( HAL_LL_TIM12_GPIO_AF | HAL_LL_TIM_REMAP_ENABLE ), hal_ll_tim_module_num(TIM_MODULE_12)},
    #endif
    #ifdef TIM12_CH2_PB15
    {GPIO_PB15, HAL_LL_TIM12_BASE_ADDR, HAL_LL_TIM_CHANNEL_2, HAL_LL_TIM_REMAP_DISABLE, hal_ll_tim_module_num(TIM_MODULE_12)},
    #endif
    #ifdef TIM12_CH2_PB15_AF9
    {GPIO_PB15, HAL_LL_TIM12_BASE_ADDR, HAL_LL_TIM_CHANNEL_2, HAL_LL_TIM12_GPIO_AF9, hal_ll_tim_module_num(TIM_MODULE_12)},
    #endif
    #ifdef TIM12_CH2_PC5
    {GPIO_PC5, HAL_LL_TIM12_BASE_ADDR, HAL_LL_TIM_CHANNEL_2, HAL_LL_TIM_REMAP_DISABLE, hal_ll_tim_module_num(TIM_MODULE_12)},
    #endif
    #endif

    #ifdef TIM_MODULE_13
    #ifdef TIM13_CH1_PA6
    {GPIO_PA6, HAL_LL_TIM13_BASE_ADDR, HAL_LL_TIM_CHANNEL_1, HAL_LL_TIM_REMAP_DISABLE, hal_ll_tim_module_num(TIM_MODULE_13)},
    #endif
    #ifdef TIM13_CH1_PA6_AF9
    {GPIO_PA6, HAL_LL_TIM13_BASE_ADDR, HAL_LL_TIM_CHANNEL_1, HAL_LL_TIM13_GPIO_AF9, hal_ll_tim_module_num(TIM_MODULE_13)},
    #endif
    #ifdef TIM13_CH1_PA9_AF2
    {GPIO_PA9, HAL_LL_TIM13_BASE_ADDR, HAL_LL_TIM_CHANNEL_1, HAL_LL_TIM13_GPIO_AF2, hal_ll_tim_module_num(TIM_MODULE_13)},
    #endif
    #ifdef TIM13_CH1_PB0_REMAP
    {GPIO_PB0, HAL_LL_TIM13_BASE_ADDR, HAL_LL_TIM_CHANNEL_1, ( HAL_LL_TIM13_GPIO_AF | HAL_LL_TIM_REMAP_ENABLE ), hal_ll_tim_module_num(TIM_MODULE_13)},
    #endif
    #ifdef TIM13_CH1_PB3_AF9
    {GPIO_PB3, HAL_LL_TIM13_BASE_ADDR, HAL_LL_TIM_CHANNEL_1, HAL_LL_TIM13_GPIO_AF9, hal_ll_tim_module_num(TIM_MODULE_13)},
    #endif
    #ifdef TIM13_CH1_PC4_AF2
    {GPIO_PC4, HAL_LL_TIM13_BASE_ADDR, HAL_LL_TIM_CHANNEL_1, HAL_LL_TIM13_GPIO_AF2, hal_ll_tim_module_num(TIM_MODULE_13)},
    #endif
    #ifdef TIM13_CH1_PC8
    {GPIO_PC8, HAL_LL_TIM13_BASE_ADDR, HAL_LL_TIM_CHANNEL_1, HAL_LL_TIM_REMAP_DISABLE, hal_ll_tim_module_num(TIM_MODULE_13)},
    #endif
    #ifdef TIM13_CH1_PF8_REMAP
    {GPIO_PF8, HAL_LL_TIM13_BASE_ADDR, HAL_LL_TIM_CHANNEL_1, ( HAL_LL_TIM13_GPIO_AF | HAL_LL_TIM_REMAP_ENABLE ), hal_ll_tim_module_num(TIM_MODULE_13)},
    #endif
    #endif

    #ifdef TIM_MODULE_14
    #ifdef TIM14_CH1_PA10_AF9
    {GPIO_PA10, HAL_LL_TIM14_BASE_ADDR, HAL_LL_TIM_CHANNEL_1, HAL_LL_TIM14_GPIO_AF9, hal_ll_tim_module_num(TIM_MODULE_14)},
    #endif
    #ifdef TIM14_CH1_PA4_AF4
    {GPIO_PA4, HAL_LL_TIM14_BASE_ADDR, HAL_LL_TIM_CHANNEL_1, HAL_LL_TIM14_GPIO_AF4, hal_ll_tim_module_num(TIM_MODULE_14)},
    #endif
    #ifdef TIM14_CH1_PA5_AF9
    {GPIO_PA5, HAL_LL_TIM14_BASE_ADDR, HAL_LL_TIM_CHANNEL_1, HAL_LL_TIM14_GPIO_AF9, hal_ll_tim_module_num(TIM_MODULE_14)},
    #endif
    #ifdef TIM14_CH1_PA7
    {GPIO_PA7, HAL_LL_TIM14_BASE_ADDR, HAL_LL_TIM_CHANNEL_1, HAL_LL_TIM_REMAP_DISABLE, hal_ll_tim_module_num(TIM_MODULE_14)},
    #endif
    #ifdef TIM14_CH1_PA7_AF4
    {GPIO_PA7, HAL_LL_TIM14_BASE_ADDR, HAL_LL_TIM_CHANNEL_1, HAL_LL_TIM14_GPIO_AF4, hal_ll_tim_module_num(TIM_MODULE_14)},
    #endif
    #ifdef TIM14_CH1_PA7_AF9
    {GPIO_PA7, HAL_LL_TIM14_BASE_ADDR, HAL_LL_TIM_CHANNEL_1, HAL_LL_TIM14_GPIO_AF9, hal_ll_tim_module_num(TIM_MODULE_14)},
    #endif
    #ifdef TIM14_CH1_PB1_AF0
    {GPIO_PB1, HAL_LL_TIM14_BASE_ADDR, HAL_LL_TIM_CHANNEL_1, HAL_LL_TIM14_GPIO_AF0, hal_ll_tim_module_num(TIM_MODULE_14)},
    #endif
    #ifdef TIM14_CH1_PB1_REMAP
    {GPIO_PB1, HAL_LL_TIM14_BASE_ADDR, HAL_LL_TIM_CHANNEL_1, ( HAL_LL_TIM14_GPIO_AF | HAL_LL_TIM_REMAP_ENABLE ), hal_ll_tim_module_num(TIM_MODULE_14)},
    #endif
    #ifdef TIM14_CH1_PC12_AF2
    {GPIO_PC12, HAL_LL_TIM14_BASE_ADDR, HAL_LL_TIM_CHANNEL_1, HAL_LL_TIM14_GPIO_AF2, hal_ll_tim_module_num(TIM_MODULE_14)},
    #endif
    #ifdef TIM14_CH1_PC9
    {GPIO_PC9, HAL_LL_TIM14_BASE_ADDR, HAL_LL_TIM_CHANNEL_1, HAL_LL_TIM_REMAP_DISABLE, hal_ll_tim_module_num(TIM_MODULE_14)},
    #endif
    #ifdef TIM14_CH1_PF0_AF2
    {GPIO_PF0, HAL_LL_TIM14_BASE_ADDR, HAL_LL_TIM_CHANNEL_1, HAL_LL_TIM14_GPIO_AF2, hal_ll_tim_module_num(TIM_MODULE_14)},
    #endif
    #ifdef TIM14_CH1_PF9_AF2
    {GPIO_PF9, HAL_LL_TIM14_BASE_ADDR, HAL_LL_TIM_CHANNEL_1, HAL_LL_TIM14_GPIO_AF2, hal_ll_tim_module_num(TIM_MODULE_14)},
    #endif
    #ifdef TIM14_CH1_PF9_REMAP
    {GPIO_PF9, HAL_LL_TIM14_BASE_ADDR, HAL_LL_TIM_CHANNEL_1, ( HAL_LL_TIM14_GPIO_AF | HAL_LL_TIM_REMAP_ENABLE ), hal_ll_tim_module_num(TIM_MODULE_14)},
    #endif
    #endif

    #ifdef TIM_MODULE_15
    #ifdef TIM15_CH1_PA2
    {GPIO_PA2, HAL_LL_TIM15_BASE_ADDR, HAL_LL_TIM_CHANNEL_1, HAL_LL_TIM_REMAP_DISABLE, hal_ll_tim_module_num(TIM_MODULE_15)},
    #endif
    #ifdef TIM15_CH1_PA2_AF0
    {GPIO_PA2, HAL_LL_TIM15_BASE_ADDR, HAL_LL_TIM_CHANNEL_1, HAL_LL_TIM15_GPIO_AF0, hal_ll_tim_module_num(TIM_MODULE_15)},
    #endif
    #ifdef TIM15_CH1_PA2_AF14
    {GPIO_PA2, HAL_LL_TIM15_BASE_ADDR, HAL_LL_TIM_CHANNEL_1, HAL_LL_TIM15_GPIO_AF14, hal_ll_tim_module_num(TIM_MODULE_15)},
    #endif
    #ifdef TIM15_CH1_PA2_AF5
    {GPIO_PA2, HAL_LL_TIM15_BASE_ADDR, HAL_LL_TIM_CHANNEL_1, HAL_LL_TIM15_GPIO_AF5, hal_ll_tim_module_num(TIM_MODULE_15)},
    #endif
    #ifdef TIM15_CH1_PA2_AF9
    {GPIO_PA2, HAL_LL_TIM15_BASE_ADDR, HAL_LL_TIM_CHANNEL_1, HAL_LL_TIM15_GPIO_AF9, hal_ll_tim_module_num(TIM_MODULE_15)},
    #endif
    #ifdef TIM15_CH1_PB14_AF1
    {GPIO_PB14, HAL_LL_TIM15_BASE_ADDR, HAL_LL_TIM_CHANNEL_1, HAL_LL_TIM15_GPIO_AF1, hal_ll_tim_module_num(TIM_MODULE_15)},
    #endif
    #ifdef TIM15_CH1_PB14_AF14
    {GPIO_PB14, HAL_LL_TIM15_BASE_ADDR, HAL_LL_TIM_CHANNEL_1, HAL_LL_TIM15_GPIO_AF14, hal_ll_tim_module_num(TIM_MODULE_15)},
    #endif
    #ifdef TIM15_CH1_PB14_AF5
    {GPIO_PB14, HAL_LL_TIM15_BASE_ADDR, HAL_LL_TIM_CHANNEL_1, HAL_LL_TIM15_GPIO_AF5, hal_ll_tim_module_num(TIM_MODULE_15)},
    #endif
    #ifdef TIM15_CH1_PB14_REMAP
    {GPIO_PB14, HAL_LL_TIM15_BASE_ADDR, HAL_LL_TIM_CHANNEL_1, ( HAL_LL_TIM15_GPIO_AF | HAL_LL_TIM_REMAP_ENABLE ), hal_ll_tim_module_num(TIM_MODULE_15)},
    #endif
    #ifdef TIM15_CH1_PB6_AF9
    {GPIO_PB6, HAL_LL_TIM15_BASE_ADDR, HAL_LL_TIM_CHANNEL_1, HAL_LL_TIM15_GPIO_AF9, hal_ll_tim_module_num(TIM_MODULE_15)},
    #endif
    #ifdef TIM15_CH1_PC1_AF2
    {GPIO_PC1, HAL_LL_TIM15_BASE_ADDR, HAL_LL_TIM_CHANNEL_1, HAL_LL_TIM15_GPIO_AF2, hal_ll_tim_module_num(TIM_MODULE_15)},
    #endif
    #ifdef TIM15_CH1_PF9_AF0
    {GPIO_PF9, HAL_LL_TIM15_BASE_ADDR, HAL_LL_TIM_CHANNEL_1, HAL_LL_TIM15_GPIO_AF0, hal_ll_tim_module_num(TIM_MODULE_15)},
    #endif
    #ifdef TIM15_CH1_PF9_AF14
    {GPIO_PF9, HAL_LL_TIM15_BASE_ADDR, HAL_LL_TIM_CHANNEL_1, HAL_LL_TIM15_GPIO_AF14, hal_ll_tim_module_num(TIM_MODULE_15)},
    #endif
    #ifdef TIM15_CH1_PF9_AF3
    {GPIO_PF9, HAL_LL_TIM15_BASE_ADDR, HAL_LL_TIM_CHANNEL_1, HAL_LL_TIM15_GPIO_AF3, hal_ll_tim_module_num(TIM_MODULE_15)},
    #endif
    #ifdef TIM15_CH1_PG10_AF14
    {GPIO_PG10, HAL_LL_TIM15_BASE_ADDR, HAL_LL_TIM_CHANNEL_1, HAL_LL_TIM15_GPIO_AF14, hal_ll_tim_module_num(TIM_MODULE_15)},
    #endif
    #ifdef TIM15_CH2_PA3
    {GPIO_PA3, HAL_LL_TIM15_BASE_ADDR, HAL_LL_TIM_CHANNEL_2, HAL_LL_TIM_REMAP_DISABLE, hal_ll_tim_module_num(TIM_MODULE_15)},
    #endif
    #ifdef TIM15_CH2_PA3_AF0
    {GPIO_PA3, HAL_LL_TIM15_BASE_ADDR, HAL_LL_TIM_CHANNEL_2, HAL_LL_TIM15_GPIO_AF0, hal_ll_tim_module_num(TIM_MODULE_15)},
    #endif
    #ifdef TIM15_CH2_PA3_AF14
    {GPIO_PA3, HAL_LL_TIM15_BASE_ADDR, HAL_LL_TIM_CHANNEL_2, HAL_LL_TIM15_GPIO_AF14, hal_ll_tim_module_num(TIM_MODULE_15)},
    #endif
    #ifdef TIM15_CH2_PA3_AF5
    {GPIO_PA3, HAL_LL_TIM15_BASE_ADDR, HAL_LL_TIM_CHANNEL_2, HAL_LL_TIM15_GPIO_AF5, hal_ll_tim_module_num(TIM_MODULE_15)},
    #endif
    #ifdef TIM15_CH2_PA3_AF9
    {GPIO_PA3, HAL_LL_TIM15_BASE_ADDR, HAL_LL_TIM_CHANNEL_2, HAL_LL_TIM15_GPIO_AF9, hal_ll_tim_module_num(TIM_MODULE_15)},
    #endif
    #ifdef TIM15_CH2_PB15_AF1
    {GPIO_PB15, HAL_LL_TIM15_BASE_ADDR, HAL_LL_TIM_CHANNEL_2, HAL_LL_TIM15_GPIO_AF1, hal_ll_tim_module_num(TIM_MODULE_15)},
    #endif
    #ifdef TIM15_CH2_PB15_AF14
    {GPIO_PB15, HAL_LL_TIM15_BASE_ADDR, HAL_LL_TIM_CHANNEL_2, HAL_LL_TIM15_GPIO_AF14, hal_ll_tim_module_num(TIM_MODULE_15)},
    #endif
    #ifdef TIM15_CH2_PB15_AF5
    {GPIO_PB15, HAL_LL_TIM15_BASE_ADDR, HAL_LL_TIM_CHANNEL_2, HAL_LL_TIM15_GPIO_AF5, hal_ll_tim_module_num(TIM_MODULE_15)},
    #endif
    #ifdef TIM15_CH2_PB7_AF9
    {GPIO_PB7, HAL_LL_TIM15_BASE_ADDR, HAL_LL_TIM_CHANNEL_2, HAL_LL_TIM15_GPIO_AF9, hal_ll_tim_module_num(TIM_MODULE_15)},
    #endif
    #ifdef TIM15_CH2_PC2_AF2
    {GPIO_PC2, HAL_LL_TIM15_BASE_ADDR, HAL_LL_TIM_CHANNEL_2, HAL_LL_TIM15_GPIO_AF2, hal_ll_tim_module_num(TIM_MODULE_15)},
    #endif
    #ifdef TIM15_CH2_PF10_AF0
    {GPIO_PF10, HAL_LL_TIM15_BASE_ADDR, HAL_LL_TIM_CHANNEL_2, HAL_LL_TIM15_GPIO_AF0, hal_ll_tim_module_num(TIM_MODULE_15)},
    #endif
    #ifdef TIM15_CH2_PF10_AF14
    {GPIO_PF10, HAL_LL_TIM15_BASE_ADDR, HAL_LL_TIM_CHANNEL_2, HAL_LL_TIM15_GPIO_AF14, hal_ll_tim_module_num(TIM_MODULE_15)},
    #endif
    #ifdef TIM15_CH2_PF10_AF3
    {GPIO_PF10, HAL_LL_TIM15_BASE_ADDR, HAL_LL_TIM_CHANNEL_2, HAL_LL_TIM15_GPIO_AF3, hal_ll_tim_module_num(TIM_MODULE_15)},
    #endif
    #ifdef TIM15_CH2_PG11_AF14
    {GPIO_PG11, HAL_LL_TIM15_BASE_ADDR, HAL_LL_TIM_CHANNEL_2, HAL_LL_TIM15_GPIO_AF14, hal_ll_tim_module_num(TIM_MODULE_15)},
    #endif
    #endif

    #ifdef TIM_MODULE_16
    #ifdef TIM16_CH1_PA12_AF1
    {GPIO_PA12, HAL_LL_TIM16_BASE_ADDR, HAL_LL_TIM_CHANNEL_1, HAL_LL_TIM16_GPIO_AF1, hal_ll_tim_module_num(TIM_MODULE_16)},
    #endif
    #ifdef TIM16_CH1_PA6_AF1
    {GPIO_PA6, HAL_LL_TIM16_BASE_ADDR, HAL_LL_TIM_CHANNEL_1, HAL_LL_TIM16_GPIO_AF1, hal_ll_tim_module_num(TIM_MODULE_16)},
    #endif
    #ifdef TIM16_CH1_PA6_AF14
    {GPIO_PA6, HAL_LL_TIM16_BASE_ADDR, HAL_LL_TIM_CHANNEL_1, HAL_LL_TIM16_GPIO_AF14, hal_ll_tim_module_num(TIM_MODULE_16)},
    #endif
    #ifdef TIM16_CH1_PA6_AF5
    {GPIO_PA6, HAL_LL_TIM16_BASE_ADDR, HAL_LL_TIM_CHANNEL_1, HAL_LL_TIM16_GPIO_AF5, hal_ll_tim_module_num(TIM_MODULE_16)},
    #endif
    #ifdef TIM16_CH1_PA6_REMAP
    {GPIO_PA6, HAL_LL_TIM16_BASE_ADDR, HAL_LL_TIM_CHANNEL_1, ( HAL_LL_TIM16_GPIO_AF | HAL_LL_TIM_REMAP_ENABLE ), hal_ll_tim_module_num(TIM_MODULE_16)},
    #endif
    #ifdef TIM16_CH1_PB4_AF1
    {GPIO_PB4, HAL_LL_TIM16_BASE_ADDR, HAL_LL_TIM_CHANNEL_1, HAL_LL_TIM16_GPIO_AF1, hal_ll_tim_module_num(TIM_MODULE_16)},
    #endif
    #ifdef TIM16_CH1_PB8
    {GPIO_PB8, HAL_LL_TIM16_BASE_ADDR, HAL_LL_TIM_CHANNEL_1, HAL_LL_TIM_REMAP_DISABLE, hal_ll_tim_module_num(TIM_MODULE_16)},
    #endif
    #ifdef TIM16_CH1_PB8_AF1
    {GPIO_PB8, HAL_LL_TIM16_BASE_ADDR, HAL_LL_TIM_CHANNEL_1, HAL_LL_TIM16_GPIO_AF1, hal_ll_tim_module_num(TIM_MODULE_16)},
    #endif
    #ifdef TIM16_CH1_PB8_AF14
    {GPIO_PB8, HAL_LL_TIM16_BASE_ADDR, HAL_LL_TIM_CHANNEL_1, HAL_LL_TIM16_GPIO_AF14, hal_ll_tim_module_num(TIM_MODULE_16)},
    #endif
    #ifdef TIM16_CH1_PB8_AF2
    {GPIO_PB8, HAL_LL_TIM16_BASE_ADDR, HAL_LL_TIM_CHANNEL_1, HAL_LL_TIM16_GPIO_AF2, hal_ll_tim_module_num(TIM_MODULE_16)},
    #endif
    #ifdef TIM16_CH1_PD0_AF2
    {GPIO_PD0, HAL_LL_TIM16_BASE_ADDR, HAL_LL_TIM_CHANNEL_1, HAL_LL_TIM16_GPIO_AF2, hal_ll_tim_module_num(TIM_MODULE_16)},
    #endif
    #ifdef TIM16_CH1_PE0_AF0
    {GPIO_PE0, HAL_LL_TIM16_BASE_ADDR, HAL_LL_TIM_CHANNEL_1, HAL_LL_TIM16_GPIO_AF0, hal_ll_tim_module_num(TIM_MODULE_16)},
    #endif
    #ifdef TIM16_CH1_PE0_AF14
    {GPIO_PE0, HAL_LL_TIM16_BASE_ADDR, HAL_LL_TIM_CHANNEL_1, HAL_LL_TIM16_GPIO_AF14, hal_ll_tim_module_num(TIM_MODULE_16)},
    #endif
    #ifdef TIM16_CH1_PE0_AF4
    {GPIO_PE0, HAL_LL_TIM16_BASE_ADDR, HAL_LL_TIM_CHANNEL_1, HAL_LL_TIM16_GPIO_AF4, hal_ll_tim_module_num(TIM_MODULE_16)},
    #endif
    #endif

    #ifdef TIM_MODULE_17
    #ifdef TIM17_CH1_PA7_AF1
    {GPIO_PA7, HAL_LL_TIM17_BASE_ADDR, HAL_LL_TIM_CHANNEL_1, HAL_LL_TIM17_GPIO_AF1, hal_ll_tim_module_num(TIM_MODULE_17)},
    #endif
    #ifdef TIM17_CH1_PA7_AF14
    {GPIO_PA7, HAL_LL_TIM17_BASE_ADDR, HAL_LL_TIM_CHANNEL_1, HAL_LL_TIM17_GPIO_AF14, hal_ll_tim_module_num(TIM_MODULE_17)},
    #endif
    #ifdef TIM17_CH1_PA7_AF5
    {GPIO_PA7, HAL_LL_TIM17_BASE_ADDR, HAL_LL_TIM_CHANNEL_1, HAL_LL_TIM17_GPIO_AF5, hal_ll_tim_module_num(TIM_MODULE_17)},
    #endif
    #ifdef TIM17_CH1_PA7_REMAP
    {GPIO_PA7, HAL_LL_TIM17_BASE_ADDR, HAL_LL_TIM_CHANNEL_1, ( HAL_LL_TIM17_GPIO_AF | HAL_LL_TIM_REMAP_ENABLE ), hal_ll_tim_module_num(TIM_MODULE_17)},
    #endif
    #ifdef TIM17_CH1_PB5_AF10
    {GPIO_PB5, HAL_LL_TIM17_BASE_ADDR, HAL_LL_TIM_CHANNEL_1, HAL_LL_TIM17_GPIO_AF10, hal_ll_tim_module_num(TIM_MODULE_17)},
    #endif
    #ifdef TIM17_CH1_PB9
    {GPIO_PB9, HAL_LL_TIM17_BASE_ADDR, HAL_LL_TIM_CHANNEL_1, HAL_LL_TIM_REMAP_DISABLE, hal_ll_tim_module_num(TIM_MODULE_17)},
    #endif
    #ifdef TIM17_CH1_PB9_AF1
    {GPIO_PB9, HAL_LL_TIM17_BASE_ADDR, HAL_LL_TIM_CHANNEL_1, HAL_LL_TIM17_GPIO_AF1, hal_ll_tim_module_num(TIM_MODULE_17)},
    #endif
    #ifdef TIM17_CH1_PB9_AF14
    {GPIO_PB9, HAL_LL_TIM17_BASE_ADDR, HAL_LL_TIM_CHANNEL_1, HAL_LL_TIM17_GPIO_AF14, hal_ll_tim_module_num(TIM_MODULE_17)},
    #endif
    #ifdef TIM17_CH1_PB9_AF2
    {GPIO_PB9, HAL_LL_TIM17_BASE_ADDR, HAL_LL_TIM_CHANNEL_1, HAL_LL_TIM17_GPIO_AF2, hal_ll_tim_module_num(TIM_MODULE_17)},
    #endif
    #ifdef TIM17_CH1_PD1_AF2
    {GPIO_PD1, HAL_LL_TIM17_BASE_ADDR, HAL_LL_TIM_CHANNEL_1, HAL_LL_TIM17_GPIO_AF2, hal_ll_tim_module_num(TIM_MODULE_17)},
    #endif
    #ifdef TIM17_CH1_PE1_AF0
    {GPIO_PE1, HAL_LL_TIM17_BASE_ADDR, HAL_LL_TIM_CHANNEL_1, HAL_LL_TIM17_GPIO_AF0, hal_ll_tim_module_num(TIM_MODULE_17)},
    #endif
    #ifdef TIM17_CH1_PE1_AF14
    {GPIO_PE1, HAL_LL_TIM17_BASE_ADDR, HAL_LL_TIM_CHANNEL_1, HAL_LL_TIM17_GPIO_AF14, hal_ll_tim_module_num(TIM_MODULE_17)},
    #endif
    #ifdef TIM17_CH1_PE1_AF4
    {GPIO_PE1, HAL_LL_TIM17_BASE_ADDR, HAL_LL_TIM_CHANNEL_1, HAL_LL_TIM17_GPIO_AF4, hal_ll_tim_module_num(TIM_MODULE_17)},
    #endif
    #endif

    #ifdef TIM_MODULE_19
    #ifdef TIM19_CH1_PA0_AF11
    {GPIO_PA0, HAL_LL_TIM19_BASE_ADDR, HAL_LL_TIM_CHANNEL_1, HAL_LL_TIM19_GPIO_AF11, hal_ll_tim_module_num(TIM_MODULE_19)},
    #endif
    #ifdef TIM19_CH1_PB6_AF11
    {GPIO_PB6, HAL_LL_TIM19_BASE_ADDR, HAL_LL_TIM_CHANNEL_1, HAL_LL_TIM19_GPIO_AF11, hal_ll_tim_module_num(TIM_MODULE_19)},
    #endif
    #ifdef TIM19_CH1_PC10_AF2
    {GPIO_PC10, HAL_LL_TIM19_BASE_ADDR, HAL_LL_TIM_CHANNEL_1, HAL_LL_TIM19_GPIO_AF2, hal_ll_tim_module_num(TIM_MODULE_19)},
    #endif
    #ifdef TIM19_CH2_PA1_AF11
    {GPIO_PA1, HAL_LL_TIM19_BASE_ADDR, HAL_LL_TIM_CHANNEL_2, HAL_LL_TIM19_GPIO_AF11, hal_ll_tim_module_num(TIM_MODULE_19)},
    #endif
    #ifdef TIM19_CH2_PB7_AF11
    {GPIO_PB7, HAL_LL_TIM19_BASE_ADDR, HAL_LL_TIM_CHANNEL_2, HAL_LL_TIM19_GPIO_AF11, hal_ll_tim_module_num(TIM_MODULE_19)},
    #endif
    #ifdef TIM19_CH2_PC11_AF2
    {GPIO_PC11, HAL_LL_TIM19_BASE_ADDR, HAL_LL_TIM_CHANNEL_2, HAL_LL_TIM19_GPIO_AF2, hal_ll_tim_module_num(TIM_MODULE_19)},
    #endif
    #ifdef TIM19_CH3_PA2_AF11
    {GPIO_PA2, HAL_LL_TIM19_BASE_ADDR, HAL_LL_TIM_CHANNEL_3, HAL_LL_TIM19_GPIO_AF11, hal_ll_tim_module_num(TIM_MODULE_19)},
    #endif
    #ifdef TIM19_CH3_PB8_AF11
    {GPIO_PB8, HAL_LL_TIM19_BASE_ADDR, HAL_LL_TIM_CHANNEL_3, HAL_LL_TIM19_GPIO_AF11, hal_ll_tim_module_num(TIM_MODULE_19)},
    #endif
    #ifdef TIM19_CH3_PC12_AF2
    {GPIO_PC12, HAL_LL_TIM19_BASE_ADDR, HAL_LL_TIM_CHANNEL_3, HAL_LL_TIM19_GPIO_AF2, hal_ll_tim_module_num(TIM_MODULE_19)},
    #endif
    #ifdef TIM19_CH4_PA3_AF11
    {GPIO_PA3, HAL_LL_TIM19_BASE_ADDR, HAL_LL_TIM_CHANNEL_4, HAL_LL_TIM19_GPIO_AF11, hal_ll_tim_module_num(TIM_MODULE_19)},
    #endif
    #ifdef TIM19_CH4_PB9_AF11
    {GPIO_PB9, HAL_LL_TIM19_BASE_ADDR, HAL_LL_TIM_CHANNEL_4, HAL_LL_TIM19_GPIO_AF11, hal_ll_tim_module_num(TIM_MODULE_19)},
    #endif
    #ifdef TIM19_CH4_PD0_AF2
    {GPIO_PD0, HAL_LL_TIM19_BASE_ADDR, HAL_LL_TIM_CHANNEL_4, HAL_LL_TIM19_GPIO_AF2, hal_ll_tim_module_num(TIM_MODULE_19)},
    #endif
    #endif

    #ifdef TIM_MODULE_20
    #ifdef TIM20_CH1_PE2_AF6
    {GPIO_PE2, HAL_LL_TIM20_BASE_ADDR, HAL_LL_TIM_CHANNEL_1, HAL_LL_TIM20_GPIO_AF6, hal_ll_tim_module_num(TIM_MODULE_20)},
    #endif
    #ifdef TIM20_CH1_PF12_AF2
    {GPIO_PF12, HAL_LL_TIM20_BASE_ADDR, HAL_LL_TIM_CHANNEL_1, HAL_LL_TIM20_GPIO_AF2, hal_ll_tim_module_num(TIM_MODULE_20)},
    #endif
    #ifdef TIM20_CH1_PH0_AF2
    {GPIO_PH0, HAL_LL_TIM20_BASE_ADDR, HAL_LL_TIM_CHANNEL_1, HAL_LL_TIM20_GPIO_AF2, hal_ll_tim_module_num(TIM_MODULE_20)},
    #endif
    #ifdef TIM20_CH2_PE3_AF6
    {GPIO_PE3, HAL_LL_TIM20_BASE_ADDR, HAL_LL_TIM_CHANNEL_2, HAL_LL_TIM20_GPIO_AF6, hal_ll_tim_module_num(TIM_MODULE_20)},
    #endif
    #ifdef TIM20_CH2_PF13_AF2
    {GPIO_PF13, HAL_LL_TIM20_BASE_ADDR, HAL_LL_TIM_CHANNEL_2, HAL_LL_TIM20_GPIO_AF2, hal_ll_tim_module_num(TIM_MODULE_20)},
    #endif
    #ifdef TIM20_CH2_PH1_AF2
    {GPIO_PH1, HAL_LL_TIM20_BASE_ADDR, HAL_LL_TIM_CHANNEL_2, HAL_LL_TIM20_GPIO_AF2, hal_ll_tim_module_num(TIM_MODULE_20)},
    #endif
    #ifdef TIM20_CH3_PF14_AF2
    {GPIO_PF14, HAL_LL_TIM20_BASE_ADDR, HAL_LL_TIM_CHANNEL_3, HAL_LL_TIM20_GPIO_AF2, hal_ll_tim_module_num(TIM_MODULE_20)},
    #endif
    #ifdef TIM20_CH3_PF2_AF2
    {GPIO_PF2, HAL_LL_TIM20_BASE_ADDR, HAL_LL_TIM_CHANNEL_3, HAL_LL_TIM20_GPIO_AF2, hal_ll_tim_module_num(TIM_MODULE_20)},
    #endif
    #ifdef TIM20_CH4_PE1_AF6
    {GPIO_PE1, HAL_LL_TIM20_BASE_ADDR, HAL_LL_TIM_CHANNEL_4, HAL_LL_TIM20_GPIO_AF6, hal_ll_tim_module_num(TIM_MODULE_20)},
    #endif
    #ifdef TIM20_CH4_PF15_AF2
    {GPIO_PF15, HAL_LL_TIM20_BASE_ADDR, HAL_LL_TIM_CHANNEL_4, HAL_LL_TIM20_GPIO_AF2, hal_ll_tim_module_num(TIM_MODULE_20)},
    #endif
    #ifdef TIM20_CH4_PF3_AF2
    {GPIO_PF3, HAL_LL_TIM20_BASE_ADDR, HAL_LL_TIM_CHANNEL_4, HAL_LL_TIM20_GPIO_AF2, hal_ll_tim_module_num(TIM_MODULE_20)},
    #endif
    #endif

    #ifdef TIM_MODULE_21
    #ifdef TIM21_CH1_PA10_AF0
    {GPIO_PA10, HAL_LL_TIM21_BASE_ADDR, HAL_LL_TIM_CHANNEL_1, HAL_LL_TIM21_GPIO_AF0, hal_ll_tim_module_num(TIM_MODULE_21)},
    #endif
    #ifdef TIM21_CH1_PA2_AF0
    {GPIO_PA2, HAL_LL_TIM21_BASE_ADDR, HAL_LL_TIM_CHANNEL_1, HAL_LL_TIM21_GPIO_AF0, hal_ll_tim_module_num(TIM_MODULE_21)},
    #endif
    #ifdef TIM21_CH1_PB13_AF5
    {GPIO_PB13, HAL_LL_TIM21_BASE_ADDR, HAL_LL_TIM_CHANNEL_1, HAL_LL_TIM21_GPIO_AF5, hal_ll_tim_module_num(TIM_MODULE_21)},
    #endif
    #ifdef TIM21_CH1_PB13_AF6
    {GPIO_PB13, HAL_LL_TIM21_BASE_ADDR, HAL_LL_TIM_CHANNEL_1, HAL_LL_TIM21_GPIO_AF6, hal_ll_tim_module_num(TIM_MODULE_21)},
    #endif
    #ifdef TIM21_CH1_PB5_AF5
    {GPIO_PB5, HAL_LL_TIM21_BASE_ADDR, HAL_LL_TIM_CHANNEL_1, HAL_LL_TIM21_GPIO_AF5, hal_ll_tim_module_num(TIM_MODULE_21)},
    #endif
    #ifdef TIM21_CH1_PB6_AF5
    {GPIO_PB6, HAL_LL_TIM21_BASE_ADDR, HAL_LL_TIM_CHANNEL_1, HAL_LL_TIM21_GPIO_AF5, hal_ll_tim_module_num(TIM_MODULE_21)},
    #endif
    #ifdef TIM21_CH1_PD0_AF0
    {GPIO_PD0, HAL_LL_TIM21_BASE_ADDR, HAL_LL_TIM_CHANNEL_1, HAL_LL_TIM21_GPIO_AF0, hal_ll_tim_module_num(TIM_MODULE_21)},
    #endif
    #ifdef TIM21_CH1_PE5_AF0
    {GPIO_PE5, HAL_LL_TIM21_BASE_ADDR, HAL_LL_TIM_CHANNEL_1, HAL_LL_TIM21_GPIO_AF0, hal_ll_tim_module_num(TIM_MODULE_21)},
    #endif
    #ifdef TIM21_CH2_PA11_AF5
    {GPIO_PA11, HAL_LL_TIM21_BASE_ADDR, HAL_LL_TIM_CHANNEL_2, HAL_LL_TIM21_GPIO_AF5, hal_ll_tim_module_num(TIM_MODULE_21)},
    #endif
    #ifdef TIM21_CH2_PA3_AF0
    {GPIO_PA3, HAL_LL_TIM21_BASE_ADDR, HAL_LL_TIM_CHANNEL_2, HAL_LL_TIM21_GPIO_AF0, hal_ll_tim_module_num(TIM_MODULE_21)},
    #endif
    #ifdef TIM21_CH2_PA9_AF5
    {GPIO_PA9, HAL_LL_TIM21_BASE_ADDR, HAL_LL_TIM_CHANNEL_2, HAL_LL_TIM21_GPIO_AF5, hal_ll_tim_module_num(TIM_MODULE_21)},
    #endif
    #ifdef TIM21_CH2_PB14_AF5
    {GPIO_PB14, HAL_LL_TIM21_BASE_ADDR, HAL_LL_TIM_CHANNEL_2, HAL_LL_TIM21_GPIO_AF5, hal_ll_tim_module_num(TIM_MODULE_21)},
    #endif
    #ifdef TIM21_CH2_PB14_AF6
    {GPIO_PB14, HAL_LL_TIM21_BASE_ADDR, HAL_LL_TIM_CHANNEL_2, HAL_LL_TIM21_GPIO_AF6, hal_ll_tim_module_num(TIM_MODULE_21)},
    #endif
    #ifdef TIM21_CH2_PD7_AF1
    {GPIO_PD7, HAL_LL_TIM21_BASE_ADDR, HAL_LL_TIM_CHANNEL_2, HAL_LL_TIM21_GPIO_AF1, hal_ll_tim_module_num(TIM_MODULE_21)},
    #endif
    #ifdef TIM21_CH2_PE6_AF0
    {GPIO_PE6, HAL_LL_TIM21_BASE_ADDR, HAL_LL_TIM_CHANNEL_2, HAL_LL_TIM21_GPIO_AF0, hal_ll_tim_module_num(TIM_MODULE_21)},
    #endif
    #endif

    #ifdef TIM_MODULE_22
    #ifdef TIM22_CH1_PA6_AF5
    {GPIO_PA6, HAL_LL_TIM22_BASE_ADDR, HAL_LL_TIM_CHANNEL_1, HAL_LL_TIM22_GPIO_AF5, hal_ll_tim_module_num(TIM_MODULE_22)},
    #endif
    #ifdef TIM22_CH1_PA9_AF5
    {GPIO_PA9, HAL_LL_TIM22_BASE_ADDR, HAL_LL_TIM_CHANNEL_1, HAL_LL_TIM22_GPIO_AF5, hal_ll_tim_module_num(TIM_MODULE_22)},
    #endif
    #ifdef TIM22_CH1_PB4_AF4
    {GPIO_PB4, HAL_LL_TIM22_BASE_ADDR, HAL_LL_TIM_CHANNEL_1, HAL_LL_TIM22_GPIO_AF4, hal_ll_tim_module_num(TIM_MODULE_22)},
    #endif
    #ifdef TIM22_CH1_PC6_AF0
    {GPIO_PC6, HAL_LL_TIM22_BASE_ADDR, HAL_LL_TIM_CHANNEL_1, HAL_LL_TIM22_GPIO_AF0, hal_ll_tim_module_num(TIM_MODULE_22)},
    #endif
    #ifdef TIM22_CH1_PE3_AF0
    {GPIO_PE3, HAL_LL_TIM22_BASE_ADDR, HAL_LL_TIM_CHANNEL_1, HAL_LL_TIM22_GPIO_AF0, hal_ll_tim_module_num(TIM_MODULE_22)},
    #endif
    #ifdef TIM22_CH2_PA10_AF5
    {GPIO_PA10, HAL_LL_TIM22_BASE_ADDR, HAL_LL_TIM_CHANNEL_2, HAL_LL_TIM22_GPIO_AF5, hal_ll_tim_module_num(TIM_MODULE_22)},
    #endif
    #ifdef TIM22_CH2_PA7_AF5
    {GPIO_PA7, HAL_LL_TIM22_BASE_ADDR, HAL_LL_TIM_CHANNEL_2, HAL_LL_TIM22_GPIO_AF5, hal_ll_tim_module_num(TIM_MODULE_22)},
    #endif
    #ifdef TIM22_CH2_PB5_AF4
    {GPIO_PB5, HAL_LL_TIM22_BASE_ADDR, HAL_LL_TIM_CHANNEL_2, HAL_LL_TIM22_GPIO_AF4, hal_ll_tim_module_num(TIM_MODULE_22)},
    #endif
    #ifdef TIM22_CH2_PC7_AF0
    {GPIO_PC7, HAL_LL_TIM22_BASE_ADDR, HAL_LL_TIM_CHANNEL_2, HAL_LL_TIM22_GPIO_AF0, hal_ll_tim_module_num(TIM_MODULE_22)},
    #endif
    #ifdef TIM22_CH2_PE4_AF0
    {GPIO_PE4, HAL_LL_TIM22_BASE_ADDR, HAL_LL_TIM_CHANNEL_2, HAL_LL_TIM22_GPIO_AF0, hal_ll_tim_module_num(TIM_MODULE_22)},
    #endif
    #endif

    #ifdef CAPTURE_COMPARE_COMPLEMENTARY_OUTPUT
    #ifdef TIM1_CH1N_PA11_AF6
    {GPIO_PA11, HAL_LL_TIM1_BASE_ADDR, HAL_LL_TIM_CHANNEL_1N, HAL_LL_TIM1_GPIO_AF6, hal_ll_tim_module_num(TIM_MODULE_1)},
    #endif
    #ifdef TIM1_CH1N_PA7_AF1
    {GPIO_PA7, HAL_LL_TIM1_BASE_ADDR, HAL_LL_TIM_CHANNEL_1N, HAL_LL_TIM1_GPIO_AF1, hal_ll_tim_module_num(TIM_MODULE_1)},
    #endif
    #ifdef TIM1_CH1N_PA7_AF2
    {GPIO_PA7, HAL_LL_TIM1_BASE_ADDR, HAL_LL_TIM_CHANNEL_1N, HAL_LL_TIM1_GPIO_AF2, hal_ll_tim_module_num(TIM_MODULE_1)},
    #endif
    #ifdef TIM1_CH1N_PA7_AF6
    {GPIO_PA7, HAL_LL_TIM1_BASE_ADDR, HAL_LL_TIM_CHANNEL_1N, HAL_LL_TIM1_GPIO_AF6, hal_ll_tim_module_num(TIM_MODULE_1)},
    #endif
    #ifdef TIM1_CH1N_PA7_REMAP
    {GPIO_PA7, HAL_LL_TIM1_BASE_ADDR, HAL_LL_TIM_CHANNEL_1N, HAL_LL_TIM1_GPIO_AF_1, hal_ll_tim_module_num(TIM_MODULE_1)},
    #endif
    #ifdef TIM1_CH1N_PB13
    {GPIO_PB13, HAL_LL_TIM1_BASE_ADDR, HAL_LL_TIM_CHANNEL_1N, HAL_LL_TIM_REMAP_DISABLE, hal_ll_tim_module_num(TIM_MODULE_1)},
    #endif
    #ifdef TIM1_CH1N_PB13_AF1
    {GPIO_PB13, HAL_LL_TIM1_BASE_ADDR, HAL_LL_TIM_CHANNEL_1N, HAL_LL_TIM1_GPIO_AF1, hal_ll_tim_module_num(TIM_MODULE_1)},
    #endif
    #ifdef TIM1_CH1N_PB13_AF2
    {GPIO_PB13, HAL_LL_TIM1_BASE_ADDR, HAL_LL_TIM_CHANNEL_1N, HAL_LL_TIM1_GPIO_AF2, hal_ll_tim_module_num(TIM_MODULE_1)},
    #endif
    #ifdef TIM1_CH1N_PB13_AF6
    {GPIO_PB13, HAL_LL_TIM1_BASE_ADDR, HAL_LL_TIM_CHANNEL_1N, HAL_LL_TIM1_GPIO_AF6, hal_ll_tim_module_num(TIM_MODULE_1)},
    #endif
    #ifdef TIM1_CH1N_PC13_AF4
    {GPIO_PC13, HAL_LL_TIM1_BASE_ADDR, HAL_LL_TIM_CHANNEL_1N, HAL_LL_TIM1_GPIO_AF4, hal_ll_tim_module_num(TIM_MODULE_1)},
    #endif
    #ifdef TIM1_CH1N_PD2_AF2
    {GPIO_PD2, HAL_LL_TIM1_BASE_ADDR, HAL_LL_TIM_CHANNEL_1N, HAL_LL_TIM1_GPIO_AF2, hal_ll_tim_module_num(TIM_MODULE_1)},
    #endif
    #ifdef TIM1_CH1N_PE8_AF0
    {GPIO_PE8, HAL_LL_TIM1_BASE_ADDR, HAL_LL_TIM_CHANNEL_1N, HAL_LL_TIM1_GPIO_AF0, hal_ll_tim_module_num(TIM_MODULE_1)},
    #endif
    #ifdef TIM1_CH1N_PE8_AF1
    {GPIO_PE8, HAL_LL_TIM1_BASE_ADDR, HAL_LL_TIM_CHANNEL_1N, HAL_LL_TIM1_GPIO_AF1, hal_ll_tim_module_num(TIM_MODULE_1)},
    #endif
    #ifdef TIM1_CH1N_PE8_AF2
    {GPIO_PE8, HAL_LL_TIM1_BASE_ADDR, HAL_LL_TIM_CHANNEL_1N, HAL_LL_TIM1_GPIO_AF2, hal_ll_tim_module_num(TIM_MODULE_1)},
    #endif
    #ifdef TIM1_CH1N_PE8_REMAP
    {GPIO_PE8, HAL_LL_TIM1_BASE_ADDR, HAL_LL_TIM_CHANNEL_1N, HAL_LL_TIM1_GPIO_AF_2, hal_ll_tim_module_num(TIM_MODULE_1)},
    #endif
    #ifdef TIM1_CH2N_PA12_AF6
    {GPIO_PA12, HAL_LL_TIM1_BASE_ADDR, HAL_LL_TIM_CHANNEL_2N, HAL_LL_TIM1_GPIO_AF6, hal_ll_tim_module_num(TIM_MODULE_1)},
    #endif
    #ifdef TIM1_CH2N_PB0_AF1
    {GPIO_PB0, HAL_LL_TIM1_BASE_ADDR, HAL_LL_TIM_CHANNEL_2N, HAL_LL_TIM1_GPIO_AF1, hal_ll_tim_module_num(TIM_MODULE_1)},
    #endif
    #ifdef TIM1_CH2N_PB0_AF2
    {GPIO_PB0, HAL_LL_TIM1_BASE_ADDR, HAL_LL_TIM_CHANNEL_2N, HAL_LL_TIM1_GPIO_AF2, hal_ll_tim_module_num(TIM_MODULE_1)},
    #endif
    #ifdef TIM1_CH2N_PB0_AF6
    {GPIO_PB0, HAL_LL_TIM1_BASE_ADDR, HAL_LL_TIM_CHANNEL_2N, HAL_LL_TIM1_GPIO_AF6, hal_ll_tim_module_num(TIM_MODULE_1)},
    #endif
    #ifdef TIM1_CH2N_PB0_REMAP
    {GPIO_PB0, HAL_LL_TIM1_BASE_ADDR, HAL_LL_TIM_CHANNEL_2N, HAL_LL_TIM1_GPIO_AF_1, hal_ll_tim_module_num(TIM_MODULE_1)},
    #endif
    #ifdef TIM1_CH2N_PB14
    {GPIO_PB14, HAL_LL_TIM1_BASE_ADDR, HAL_LL_TIM_CHANNEL_2N, HAL_LL_TIM_REMAP_DISABLE, hal_ll_tim_module_num(TIM_MODULE_1)},
    #endif
    #ifdef TIM1_CH2N_PB14_AF1
    {GPIO_PB14, HAL_LL_TIM1_BASE_ADDR, HAL_LL_TIM_CHANNEL_2N, HAL_LL_TIM1_GPIO_AF1, hal_ll_tim_module_num(TIM_MODULE_1)},
    #endif
    #ifdef TIM1_CH2N_PB14_AF2
    {GPIO_PB14, HAL_LL_TIM1_BASE_ADDR, HAL_LL_TIM_CHANNEL_2N, HAL_LL_TIM1_GPIO_AF2, hal_ll_tim_module_num(TIM_MODULE_1)},
    #endif
    #ifdef TIM1_CH2N_PB14_AF6
    {GPIO_PB14, HAL_LL_TIM1_BASE_ADDR, HAL_LL_TIM_CHANNEL_2N, HAL_LL_TIM1_GPIO_AF6, hal_ll_tim_module_num(TIM_MODULE_1)},
    #endif
    #ifdef TIM1_CH2N_PD3_AF2
    {GPIO_PD3, HAL_LL_TIM1_BASE_ADDR, HAL_LL_TIM_CHANNEL_2N, HAL_LL_TIM1_GPIO_AF2, hal_ll_tim_module_num(TIM_MODULE_1)},
    #endif
    #ifdef TIM1_CH2N_PE10_AF0
    {GPIO_PE10, HAL_LL_TIM1_BASE_ADDR, HAL_LL_TIM_CHANNEL_2N, HAL_LL_TIM1_GPIO_AF0, hal_ll_tim_module_num(TIM_MODULE_1)},
    #endif
    #ifdef TIM1_CH2N_PE10_AF1
    {GPIO_PE10, HAL_LL_TIM1_BASE_ADDR, HAL_LL_TIM_CHANNEL_2N, HAL_LL_TIM1_GPIO_AF1, hal_ll_tim_module_num(TIM_MODULE_1)},
    #endif
    #ifdef TIM1_CH2N_PE10_AF2
    {GPIO_PE10, HAL_LL_TIM1_BASE_ADDR, HAL_LL_TIM_CHANNEL_2N, HAL_LL_TIM1_GPIO_AF2, hal_ll_tim_module_num(TIM_MODULE_1)},
    #endif
    #ifdef TIM1_CH2N_PE10_REMAP
    {GPIO_PE10, HAL_LL_TIM1_BASE_ADDR, HAL_LL_TIM_CHANNEL_2N, HAL_LL_TIM1_GPIO_AF_2, hal_ll_tim_module_num(TIM_MODULE_1)},
    #endif
    #ifdef TIM1_CH3N_PB1_AF1
    {GPIO_PB1, HAL_LL_TIM1_BASE_ADDR, HAL_LL_TIM_CHANNEL_3N, HAL_LL_TIM1_GPIO_AF1, hal_ll_tim_module_num(TIM_MODULE_1)},
    #endif
    #ifdef TIM1_CH3N_PB1_AF2
    {GPIO_PB1, HAL_LL_TIM1_BASE_ADDR, HAL_LL_TIM_CHANNEL_3N, HAL_LL_TIM1_GPIO_AF2, hal_ll_tim_module_num(TIM_MODULE_1)},
    #endif
    #ifdef TIM1_CH3N_PB1_AF6
    {GPIO_PB1, HAL_LL_TIM1_BASE_ADDR, HAL_LL_TIM_CHANNEL_3N, HAL_LL_TIM1_GPIO_AF6, hal_ll_tim_module_num(TIM_MODULE_1)},
    #endif
    #ifdef TIM1_CH3N_PB1_REMAP
    {GPIO_PB1, HAL_LL_TIM1_BASE_ADDR, HAL_LL_TIM_CHANNEL_3N, HAL_LL_TIM1_GPIO_AF_1, hal_ll_tim_module_num(TIM_MODULE_1)},
    #endif
    #ifdef TIM1_CH3N_PB15
    {GPIO_PB15, HAL_LL_TIM1_BASE_ADDR, HAL_LL_TIM_CHANNEL_3N, HAL_LL_TIM_REMAP_DISABLE, hal_ll_tim_module_num(TIM_MODULE_1)},
    #endif
    #ifdef TIM1_CH3N_PB15_AF1
    {GPIO_PB15, HAL_LL_TIM1_BASE_ADDR, HAL_LL_TIM_CHANNEL_3N, HAL_LL_TIM1_GPIO_AF1, hal_ll_tim_module_num(TIM_MODULE_1)},
    #endif
    #ifdef TIM1_CH3N_PB15_AF2
    {GPIO_PB15, HAL_LL_TIM1_BASE_ADDR, HAL_LL_TIM_CHANNEL_3N, HAL_LL_TIM1_GPIO_AF2, hal_ll_tim_module_num(TIM_MODULE_1)},
    #endif
    #ifdef TIM1_CH3N_PB15_AF4
    {GPIO_PB15, HAL_LL_TIM1_BASE_ADDR, HAL_LL_TIM_CHANNEL_3N, HAL_LL_TIM1_GPIO_AF4, hal_ll_tim_module_num(TIM_MODULE_1)},
    #endif
    #ifdef TIM1_CH3N_PD4_AF2
    {GPIO_PD4, HAL_LL_TIM1_BASE_ADDR, HAL_LL_TIM_CHANNEL_3N, HAL_LL_TIM1_GPIO_AF2, hal_ll_tim_module_num(TIM_MODULE_1)},
    #endif
    #ifdef TIM1_CH3N_PE12_AF0
    {GPIO_PE12, HAL_LL_TIM1_BASE_ADDR, HAL_LL_TIM_CHANNEL_3N, HAL_LL_TIM1_GPIO_AF0, hal_ll_tim_module_num(TIM_MODULE_1)},
    #endif
    #ifdef TIM1_CH3N_PE12_AF1
    {GPIO_PE12, HAL_LL_TIM1_BASE_ADDR, HAL_LL_TIM_CHANNEL_3N, HAL_LL_TIM1_GPIO_AF1, hal_ll_tim_module_num(TIM_MODULE_1)},
    #endif
    #ifdef TIM1_CH3N_PE12_AF2
    {GPIO_PE12, HAL_LL_TIM1_BASE_ADDR, HAL_LL_TIM_CHANNEL_3N, HAL_LL_TIM1_GPIO_AF2, hal_ll_tim_module_num(TIM_MODULE_1)},
    #endif
    #ifdef TIM1_CH3N_PE12_REMAP
    {GPIO_PE12, HAL_LL_TIM1_BASE_ADDR, HAL_LL_TIM_CHANNEL_3N, HAL_LL_TIM1_GPIO_AF_2, hal_ll_tim_module_num(TIM_MODULE_1)},
    #endif
    #ifdef TIM1_CH3N_PF0_AF6
    {GPIO_PF0, HAL_LL_TIM1_BASE_ADDR, HAL_LL_TIM_CHANNEL_3N, HAL_LL_TIM1_GPIO_AF6, hal_ll_tim_module_num(TIM_MODULE_1)},
    #endif
    #ifdef TIM8_CH1N_PA5_AF3
    {GPIO_PA5, HAL_LL_TIM8_BASE_ADDR, HAL_LL_TIM_CHANNEL_1N, HAL_LL_TIM8_GPIO_AF3, hal_ll_tim_module_num(TIM_MODULE_8)},
    #endif
    #ifdef TIM8_CH1N_PA7_AF3
    {GPIO_PA7, HAL_LL_TIM8_BASE_ADDR, HAL_LL_TIM_CHANNEL_1N, HAL_LL_TIM8_GPIO_AF3, hal_ll_tim_module_num(TIM_MODULE_8)},
    #endif
    #ifdef TIM8_CH1N_PA7_AF4
    {GPIO_PA7, HAL_LL_TIM8_BASE_ADDR, HAL_LL_TIM_CHANNEL_1N, HAL_LL_TIM8_GPIO_AF4, hal_ll_tim_module_num(TIM_MODULE_8)},
    #endif
    #ifdef TIM8_CH1N_PB3_AF4
    {GPIO_PB3, HAL_LL_TIM8_BASE_ADDR, HAL_LL_TIM_CHANNEL_1N, HAL_LL_TIM8_GPIO_AF4, hal_ll_tim_module_num(TIM_MODULE_8)},
    #endif
    #ifdef TIM8_CH1N_PC10_AF4
    {GPIO_PC10, HAL_LL_TIM8_BASE_ADDR, HAL_LL_TIM_CHANNEL_1N, HAL_LL_TIM8_GPIO_AF4, hal_ll_tim_module_num(TIM_MODULE_8)},
    #endif
    #ifdef TIM8_CH1N_PH13_AF3
    {GPIO_PH13, HAL_LL_TIM8_BASE_ADDR, HAL_LL_TIM_CHANNEL_1N, HAL_LL_TIM8_GPIO_AF3, hal_ll_tim_module_num(TIM_MODULE_8)},
    #endif
    #ifdef TIM8_CH2N_PB0_AF3
    {GPIO_PB0, HAL_LL_TIM8_BASE_ADDR, HAL_LL_TIM_CHANNEL_2N, HAL_LL_TIM8_GPIO_AF3, hal_ll_tim_module_num(TIM_MODULE_8)},
    #endif
    #ifdef TIM8_CH2N_PB0_AF4
    {GPIO_PB0, HAL_LL_TIM8_BASE_ADDR, HAL_LL_TIM_CHANNEL_2N, HAL_LL_TIM8_GPIO_AF4, hal_ll_tim_module_num(TIM_MODULE_8)},
    #endif
    #ifdef TIM8_CH2N_PB14_AF3
    {GPIO_PB14, HAL_LL_TIM8_BASE_ADDR, HAL_LL_TIM_CHANNEL_2N, HAL_LL_TIM8_GPIO_AF3, hal_ll_tim_module_num(TIM_MODULE_8)},
    #endif
    #ifdef TIM8_CH2N_PB4_AF4
    {GPIO_PB4, HAL_LL_TIM8_BASE_ADDR, HAL_LL_TIM_CHANNEL_2N, HAL_LL_TIM8_GPIO_AF4, hal_ll_tim_module_num(TIM_MODULE_8)},
    #endif
    #ifdef TIM8_CH2N_PC11_AF4
    {GPIO_PC11, HAL_LL_TIM8_BASE_ADDR, HAL_LL_TIM_CHANNEL_2N, HAL_LL_TIM8_GPIO_AF4, hal_ll_tim_module_num(TIM_MODULE_8)},
    #endif
    #ifdef TIM8_CH2N_PH14_AF3
    {GPIO_PH14, HAL_LL_TIM8_BASE_ADDR, HAL_LL_TIM_CHANNEL_2N, HAL_LL_TIM8_GPIO_AF3, hal_ll_tim_module_num(TIM_MODULE_8)},
    #endif
    #ifdef TIM8_CH3N_PB1_AF3
    {GPIO_PB1, HAL_LL_TIM8_BASE_ADDR, HAL_LL_TIM_CHANNEL_3N, HAL_LL_TIM8_GPIO_AF3, hal_ll_tim_module_num(TIM_MODULE_8)},
    #endif
    #ifdef TIM8_CH3N_PB1_AF4
    {GPIO_PB1, HAL_LL_TIM8_BASE_ADDR, HAL_LL_TIM_CHANNEL_3N, HAL_LL_TIM8_GPIO_AF4, hal_ll_tim_module_num(TIM_MODULE_8)},
    #endif
    #ifdef TIM8_CH3N_PB15_AF3
    {GPIO_PB15, HAL_LL_TIM8_BASE_ADDR, HAL_LL_TIM_CHANNEL_3N, HAL_LL_TIM8_GPIO_AF3, hal_ll_tim_module_num(TIM_MODULE_8)},
    #endif
    #ifdef TIM8_CH3N_PB5_AF3
    {GPIO_PB5, HAL_LL_TIM8_BASE_ADDR, HAL_LL_TIM_CHANNEL_3N, HAL_LL_TIM8_GPIO_AF3, hal_ll_tim_module_num(TIM_MODULE_8)},
    #endif
    #ifdef TIM8_CH3N_PC12_AF4
    {GPIO_PC12, HAL_LL_TIM8_BASE_ADDR, HAL_LL_TIM_CHANNEL_3N, HAL_LL_TIM8_GPIO_AF4, hal_ll_tim_module_num(TIM_MODULE_8)},
    #endif
    #ifdef TIM8_CH3N_PH15_AF3
    {GPIO_PH15, HAL_LL_TIM8_BASE_ADDR, HAL_LL_TIM_CHANNEL_3N, HAL_LL_TIM8_GPIO_AF3, hal_ll_tim_module_num(TIM_MODULE_8)},
    #endif
    #ifdef TIM15_CH1N_PA1_AF14
    {GPIO_PA1, HAL_LL_TIM15_BASE_ADDR, HAL_LL_TIM_CHANNEL_1N, HAL_LL_TIM15_GPIO_AF14, hal_ll_tim_module_num(TIM_MODULE_15)},
    #endif
    #ifdef TIM15_CH1N_PA1_AF5
    {GPIO_PA1, HAL_LL_TIM15_BASE_ADDR, HAL_LL_TIM_CHANNEL_1N, HAL_LL_TIM15_GPIO_AF5, hal_ll_tim_module_num(TIM_MODULE_15)},
    #endif
    #ifdef TIM15_CH1N_PA1_AF9
    {GPIO_PA1, HAL_LL_TIM15_BASE_ADDR, HAL_LL_TIM_CHANNEL_1N, HAL_LL_TIM15_GPIO_AF9, hal_ll_tim_module_num(TIM_MODULE_15)},
    #endif
    #ifdef TIM15_CH1N_PB13_AF14
    {GPIO_PB13, HAL_LL_TIM15_BASE_ADDR, HAL_LL_TIM_CHANNEL_1N, HAL_LL_TIM15_GPIO_AF14, hal_ll_tim_module_num(TIM_MODULE_15)},
    #endif
    #ifdef TIM15_CH1N_PB13_AF5
    {GPIO_PB13, HAL_LL_TIM15_BASE_ADDR, HAL_LL_TIM_CHANNEL_1N, HAL_LL_TIM15_GPIO_AF5, hal_ll_tim_module_num(TIM_MODULE_15)},
    #endif
    #ifdef TIM15_CH1N_PB15
    {GPIO_PB15, HAL_LL_TIM15_BASE_ADDR, HAL_LL_TIM_CHANNEL_1N, HAL_LL_TIM_REMAP_DISABLE, hal_ll_tim_module_num(TIM_MODULE_15)},
    #endif
    #ifdef TIM15_CH1N_PB15_AF2
    {GPIO_PB15, HAL_LL_TIM15_BASE_ADDR, HAL_LL_TIM_CHANNEL_1N, HAL_LL_TIM15_GPIO_AF2, hal_ll_tim_module_num(TIM_MODULE_15)},
    #endif
    #ifdef TIM15_CH1N_PB15_AF3
    {GPIO_PB15, HAL_LL_TIM15_BASE_ADDR, HAL_LL_TIM_CHANNEL_1N, HAL_LL_TIM15_GPIO_AF3, hal_ll_tim_module_num(TIM_MODULE_15)},
    #endif
    #ifdef TIM15_CH1N_PB15_AF4
    {GPIO_PB15, HAL_LL_TIM15_BASE_ADDR, HAL_LL_TIM_CHANNEL_1N, HAL_LL_TIM15_GPIO_AF4, hal_ll_tim_module_num(TIM_MODULE_15)},
    #endif
    #ifdef TIM15_CH1N_PB4_AF9
    {GPIO_PB4, HAL_LL_TIM15_BASE_ADDR, HAL_LL_TIM_CHANNEL_1N, HAL_LL_TIM15_GPIO_AF9, hal_ll_tim_module_num(TIM_MODULE_15)},
    #endif
    #ifdef TIM15_CH1N_PF1_AF2
    {GPIO_PF1, HAL_LL_TIM15_BASE_ADDR, HAL_LL_TIM_CHANNEL_1N, HAL_LL_TIM15_GPIO_AF2, hal_ll_tim_module_num(TIM_MODULE_15)},
    #endif
    #ifdef TIM15_CH1N_PG9_AF14
    {GPIO_PG9, HAL_LL_TIM15_BASE_ADDR, HAL_LL_TIM_CHANNEL_1N, HAL_LL_TIM15_GPIO_AF14, hal_ll_tim_module_num(TIM_MODULE_15)},
    #endif
    #ifdef TIM16_CH1N_PA13_AF1
    {GPIO_PA13, HAL_LL_TIM16_BASE_ADDR, HAL_LL_TIM_CHANNEL_1N, HAL_LL_TIM16_GPIO_AF1, hal_ll_tim_module_num(TIM_MODULE_16)},
    #endif
    #ifdef TIM16_CH1N_PB6
    {GPIO_PB6, HAL_LL_TIM16_BASE_ADDR, HAL_LL_TIM_CHANNEL_1N, HAL_LL_TIM_REMAP_DISABLE, hal_ll_tim_module_num(TIM_MODULE_16)},
    #endif
    #ifdef TIM16_CH1N_PB6_AF1
    {GPIO_PB6, HAL_LL_TIM16_BASE_ADDR, HAL_LL_TIM_CHANNEL_1N, HAL_LL_TIM16_GPIO_AF1, hal_ll_tim_module_num(TIM_MODULE_16)},
    #endif
    #ifdef TIM16_CH1N_PB6_AF14
    {GPIO_PB6, HAL_LL_TIM16_BASE_ADDR, HAL_LL_TIM_CHANNEL_1N, HAL_LL_TIM16_GPIO_AF14, hal_ll_tim_module_num(TIM_MODULE_16)},
    #endif
    #ifdef TIM16_CH1N_PB6_AF2
    {GPIO_PB6, HAL_LL_TIM16_BASE_ADDR, HAL_LL_TIM_CHANNEL_1N, HAL_LL_TIM16_GPIO_AF2, hal_ll_tim_module_num(TIM_MODULE_16)},
    #endif
    #ifdef TIM17_CH1N_PB7
    {GPIO_PB7, HAL_LL_TIM17_BASE_ADDR, HAL_LL_TIM_CHANNEL_1N, HAL_LL_TIM_REMAP_DISABLE, hal_ll_tim_module_num(TIM_MODULE_17)},
    #endif
    #ifdef TIM17_CH1N_PB7_AF1
    {GPIO_PB7, HAL_LL_TIM17_BASE_ADDR, HAL_LL_TIM_CHANNEL_1N, HAL_LL_TIM17_GPIO_AF1, hal_ll_tim_module_num(TIM_MODULE_17)},
    #endif
    #ifdef TIM17_CH1N_PB7_AF14
    {GPIO_PB7, HAL_LL_TIM17_BASE_ADDR, HAL_LL_TIM_CHANNEL_1N, HAL_LL_TIM17_GPIO_AF14, hal_ll_tim_module_num(TIM_MODULE_17)},
    #endif
    #ifdef TIM17_CH1N_PB7_AF2
    {GPIO_PB7, HAL_LL_TIM17_BASE_ADDR, HAL_LL_TIM_CHANNEL_1N, HAL_LL_TIM17_GPIO_AF2, hal_ll_tim_module_num(TIM_MODULE_17)},
    #endif
    #ifdef TIM20_CH1N_PE4_AF6
    {GPIO_PE4, HAL_LL_TIM20_BASE_ADDR, HAL_LL_TIM_CHANNEL_1N, HAL_LL_TIM20_GPIO_AF6, hal_ll_tim_module_num(TIM_MODULE_20)},
    #endif
    #ifdef TIM20_CH1N_PF4_AF3
    {GPIO_PF4, HAL_LL_TIM20_BASE_ADDR, HAL_LL_TIM_CHANNEL_1N, HAL_LL_TIM20_GPIO_AF3, hal_ll_tim_module_num(TIM_MODULE_20)},
    #endif
    #ifdef TIM20_CH1N_PG0_AF2
    {GPIO_PG0, HAL_LL_TIM20_BASE_ADDR, HAL_LL_TIM_CHANNEL_1N, HAL_LL_TIM20_GPIO_AF2, hal_ll_tim_module_num(TIM_MODULE_20)},
    #endif
    #ifdef TIM20_CH2N_PE5_AF6
    {GPIO_PE5, HAL_LL_TIM20_BASE_ADDR, HAL_LL_TIM_CHANNEL_2N, HAL_LL_TIM20_GPIO_AF6, hal_ll_tim_module_num(TIM_MODULE_20)},
    #endif
    #ifdef TIM20_CH2N_PF5_AF2
    {GPIO_PF5, HAL_LL_TIM20_BASE_ADDR, HAL_LL_TIM_CHANNEL_2N, HAL_LL_TIM20_GPIO_AF2, hal_ll_tim_module_num(TIM_MODULE_20)},
    #endif
    #ifdef TIM20_CH2N_PG1_AF2
    {GPIO_PG1, HAL_LL_TIM20_BASE_ADDR, HAL_LL_TIM_CHANNEL_2N, HAL_LL_TIM20_GPIO_AF2, hal_ll_tim_module_num(TIM_MODULE_20)},
    #endif
    #ifdef TIM20_CH3N_PE6_AF6
    {GPIO_PE6, HAL_LL_TIM20_BASE_ADDR, HAL_LL_TIM_CHANNEL_3N, HAL_LL_TIM20_GPIO_AF6, hal_ll_tim_module_num(TIM_MODULE_20)},
    #endif
    #ifdef TIM20_CH3N_PG2_AF2
    {GPIO_PG2, HAL_LL_TIM20_BASE_ADDR, HAL_LL_TIM_CHANNEL_3N, HAL_LL_TIM20_GPIO_AF2, hal_ll_tim_module_num(TIM_MODULE_20)},
    #endif
    #endif

    { HAL_LL_PIN_NC, HAL_LL_MODULE_ERROR, HAL_LL_CHANNEL_ERROR, HAL_LL_PIN_NC, HAL_LL_PIN_NC }
};

#ifdef __cplusplus
}
#endif

#endif // _HAL_LL_TIM_PIN_MAP_H_
// ------------------------------------------------------------------------- END
