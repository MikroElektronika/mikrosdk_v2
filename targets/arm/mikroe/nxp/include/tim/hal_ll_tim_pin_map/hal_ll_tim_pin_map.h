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

/*!< @brief Macro defining `weak` attribute */
#define __weak __attribute__((weak))
/*!< @brief Helper macro for getting adequate module index number */
#define hal_ll_tim_module_num(_module_num) (_module_num - 1)

/*!< TIM module base addresses. */
#ifdef TIM_MODULE_0
static const hal_ll_base_addr_t HAL_LL_TIM0_BASE_ADDR = 0x40038000;
#endif

#ifdef TIM_MODULE_1
static const hal_ll_base_addr_t HAL_LL_TIM1_BASE_ADDR = 0x40039000;
#endif

#ifdef TIM_MODULE_2
#if defined(MK51) || defined(MK53) || defined(MK60)
static const hal_ll_base_addr_t HAL_LL_TIM2_BASE_ADDR = 0x400B8000;
#else
static const hal_ll_base_addr_t HAL_LL_TIM2_BASE_ADDR = 0x4003A000;
#endif
#endif

#ifdef TIM_MODULE_3
#if defined(MKV4) || defined(MKV5)
static const hal_ll_base_addr_t HAL_LL_TIM3_BASE_ADDR = 0x40026000;
#else
static const hal_ll_base_addr_t HAL_LL_TIM3_BASE_ADDR = 0x400B9000;
#endif
#endif

/**
 * TIM channels and channel pairs.
 */
typedef enum {
    HAL_LL_TIM_CHANNEL_0 = 0,
    HAL_LL_TIM_CHANNEL_1,
    HAL_LL_TIM_CHANNEL_2,
    HAL_LL_TIM_CHANNEL_3,
    HAL_LL_TIM_CHANNEL_4,
    HAL_LL_TIM_CHANNEL_5,
    HAL_LL_TIM_CHANNEL_6,
    HAL_LL_TIM_CHANNEL_7
} hal_ll_tim_channel_t;

typedef enum {
    HAL_LL_TIM_CHANNEL_PAIR_INDEX_0 = 0,
    HAL_LL_TIM_CHANNEL_PAIR_INDEX_1 = 0,
    HAL_LL_TIM_CHANNEL_PAIR_INDEX_2 = 1,
    HAL_LL_TIM_CHANNEL_PAIR_INDEX_3 = 1,
    HAL_LL_TIM_CHANNEL_PAIR_INDEX_4 = 2,
    HAL_LL_TIM_CHANNEL_PAIR_INDEX_5 = 2,
    HAL_LL_TIM_CHANNEL_PAIR_INDEX_6 = 3,
    HAL_LL_TIM_CHANNEL_PAIR_INDEX_7 = 3
} hal_ll_tim_channel_pair_index_t;

/*!< @brief TIM pin structure. */
typedef struct {
    hal_ll_pin_name_t pin;
    hal_ll_base_addr_t base;
    hal_ll_channel_t channel;
    uint8_t channel_pair_index;
    uint8_t af;
    hal_ll_pin_name_t module_index;
} hal_ll_tim_pin_map_t;

/*!< TIM pins. */
static const hal_ll_tim_pin_map_t _tim_map[] = {
    #ifdef TIM0_CH5_PA0_AF3
    {GPIO_PA0, HAL_LL_TIM0_BASE_ADDR, HAL_LL_TIM_CHANNEL_5, HAL_LL_TIM_CHANNEL_PAIR_INDEX_5, 3, hal_ll_tim_module_num(TIM_MODULE_0)},
    #endif
    #ifdef TIM0_CH6_PA1_AF3
    {GPIO_PA1, HAL_LL_TIM0_BASE_ADDR, HAL_LL_TIM_CHANNEL_6, HAL_LL_TIM_CHANNEL_PAIR_INDEX_6, 3, hal_ll_tim_module_num(TIM_MODULE_0)},
    #endif
    #ifdef TIM0_CH7_PA2_AF3
    {GPIO_PA2, HAL_LL_TIM0_BASE_ADDR, HAL_LL_TIM_CHANNEL_7, HAL_LL_TIM_CHANNEL_PAIR_INDEX_7, 3, hal_ll_tim_module_num(TIM_MODULE_0)},
    #endif
    #ifdef TIM0_CH0_PA3_AF3
    {GPIO_PA3, HAL_LL_TIM0_BASE_ADDR, HAL_LL_TIM_CHANNEL_0, HAL_LL_TIM_CHANNEL_PAIR_INDEX_0, 3, hal_ll_tim_module_num(TIM_MODULE_0)},
    #endif
    #ifdef TIM0_CH1_PA4_AF3
    {GPIO_PA4, HAL_LL_TIM0_BASE_ADDR, HAL_LL_TIM_CHANNEL_1, HAL_LL_TIM_CHANNEL_PAIR_INDEX_1, 3, hal_ll_tim_module_num(TIM_MODULE_0)},
    #endif
    #ifdef TIM1_CH0_PB0_AF3
    {GPIO_PB0, HAL_LL_TIM1_BASE_ADDR, HAL_LL_TIM_CHANNEL_0, HAL_LL_TIM_CHANNEL_PAIR_INDEX_0, 3, hal_ll_tim_module_num(TIM_MODULE_1)},
    #endif
    #ifdef TIM1_CH1_PB1_AF3
    {GPIO_PB1, HAL_LL_TIM1_BASE_ADDR, HAL_LL_TIM_CHANNEL_1, HAL_LL_TIM_CHANNEL_PAIR_INDEX_1, 3, hal_ll_tim_module_num(TIM_MODULE_1)},
    #endif
    #ifdef TIM0_CH0_PC1_AF4
    {GPIO_PC1, HAL_LL_TIM0_BASE_ADDR, HAL_LL_TIM_CHANNEL_0, HAL_LL_TIM_CHANNEL_PAIR_INDEX_0, 4, hal_ll_tim_module_num(TIM_MODULE_0)},
    #endif
    #ifdef TIM0_CH1_PC2_AF4
    {GPIO_PC2, HAL_LL_TIM0_BASE_ADDR, HAL_LL_TIM_CHANNEL_1, HAL_LL_TIM_CHANNEL_PAIR_INDEX_1, 4, hal_ll_tim_module_num(TIM_MODULE_0)},
    #endif
    #ifdef TIM0_CH2_PC3_AF4
    {GPIO_PC3, HAL_LL_TIM0_BASE_ADDR, HAL_LL_TIM_CHANNEL_2, HAL_LL_TIM_CHANNEL_PAIR_INDEX_2, 4, hal_ll_tim_module_num(TIM_MODULE_0)},
    #endif
    #ifdef TIM0_CH3_PC4_AF4
    {GPIO_PC4, HAL_LL_TIM0_BASE_ADDR, HAL_LL_TIM_CHANNEL_3, HAL_LL_TIM_CHANNEL_PAIR_INDEX_3, 4, hal_ll_tim_module_num(TIM_MODULE_0)},
    #endif
    #ifdef TIM0_CH4_PD4_AF4
    {GPIO_PD4, HAL_LL_TIM0_BASE_ADDR, HAL_LL_TIM_CHANNEL_4, HAL_LL_TIM_CHANNEL_PAIR_INDEX_4, 4, hal_ll_tim_module_num(TIM_MODULE_0)},
    #endif
    #ifdef TIM0_CH5_PD5_AF4
    {GPIO_PD5, HAL_LL_TIM0_BASE_ADDR, HAL_LL_TIM_CHANNEL_5, HAL_LL_TIM_CHANNEL_PAIR_INDEX_5, 4, hal_ll_tim_module_num(TIM_MODULE_0)},
    #endif
    #ifdef TIM0_CH6_PD6_AF4
    {GPIO_PD6, HAL_LL_TIM0_BASE_ADDR, HAL_LL_TIM_CHANNEL_6, HAL_LL_TIM_CHANNEL_PAIR_INDEX_6, 4, hal_ll_tim_module_num(TIM_MODULE_0)},
    #endif
    #ifdef TIM0_CH7_PD7_AF4
    {GPIO_PD7, HAL_LL_TIM0_BASE_ADDR, HAL_LL_TIM_CHANNEL_7, HAL_LL_TIM_CHANNEL_PAIR_INDEX_7, 4, hal_ll_tim_module_num(TIM_MODULE_0)},
    #endif
    #ifdef TIM0_CH2_PA5_AF3
    {GPIO_PA5, HAL_LL_TIM0_BASE_ADDR, HAL_LL_TIM_CHANNEL_2, HAL_LL_TIM_CHANNEL_PAIR_INDEX_2, 3, hal_ll_tim_module_num(TIM_MODULE_0)},
    #endif
    #ifdef TIM1_CH0_PA12_AF3
    {GPIO_PA12, HAL_LL_TIM1_BASE_ADDR, HAL_LL_TIM_CHANNEL_0, HAL_LL_TIM_CHANNEL_PAIR_INDEX_0, 3, hal_ll_tim_module_num(TIM_MODULE_1)},
    #endif
    #ifdef TIM1_CH1_PA13_AF3
    {GPIO_PA13, HAL_LL_TIM1_BASE_ADDR, HAL_LL_TIM_CHANNEL_1, HAL_LL_TIM_CHANNEL_PAIR_INDEX_1, 3, hal_ll_tim_module_num(TIM_MODULE_1)},
    #endif
    #ifdef TIM2_CH0_PB18_AF3
    {GPIO_PB18, HAL_LL_TIM2_BASE_ADDR, HAL_LL_TIM_CHANNEL_0, HAL_LL_TIM_CHANNEL_PAIR_INDEX_0, 3, hal_ll_tim_module_num(TIM_MODULE_2)},
    #endif
    #ifdef TIM2_CH1_PB19_AF3
    {GPIO_PB19, HAL_LL_TIM2_BASE_ADDR, HAL_LL_TIM_CHANNEL_1, HAL_LL_TIM_CHANNEL_PAIR_INDEX_1, 3, hal_ll_tim_module_num(TIM_MODULE_2)},
    #endif
    #ifdef TIM0_CH2_PC5_AF7
    {GPIO_PC5, HAL_LL_TIM0_BASE_ADDR, HAL_LL_TIM_CHANNEL_2, HAL_LL_TIM_CHANNEL_PAIR_INDEX_2, 7, hal_ll_tim_module_num(TIM_MODULE_0)},
    #endif
    #ifdef TIM3_CH4_PC8_AF3
    {GPIO_PC8, HAL_LL_TIM3_BASE_ADDR, HAL_LL_TIM_CHANNEL_4, HAL_LL_TIM_CHANNEL_PAIR_INDEX_4, 3, hal_ll_tim_module_num(TIM_MODULE_3)},
    #endif
    #ifdef TIM3_CH5_PC9_AF3
    {GPIO_PC9, HAL_LL_TIM3_BASE_ADDR, HAL_LL_TIM_CHANNEL_5, HAL_LL_TIM_CHANNEL_PAIR_INDEX_5, 3, hal_ll_tim_module_num(TIM_MODULE_3)},
    #endif
    #ifdef TIM3_CH6_PC10_AF3
    {GPIO_PC10, HAL_LL_TIM3_BASE_ADDR, HAL_LL_TIM_CHANNEL_6, HAL_LL_TIM_CHANNEL_PAIR_INDEX_6, 3, hal_ll_tim_module_num(TIM_MODULE_3)},
    #endif
    #ifdef TIM3_CH7_PC11_AF3
    {GPIO_PC11, HAL_LL_TIM3_BASE_ADDR, HAL_LL_TIM_CHANNEL_7, HAL_LL_TIM_CHANNEL_PAIR_INDEX_7, 3, hal_ll_tim_module_num(TIM_MODULE_3)},
    #endif
    #ifdef TIM3_CH0_PD0_AF4
    {GPIO_PD0, HAL_LL_TIM3_BASE_ADDR, HAL_LL_TIM_CHANNEL_0, HAL_LL_TIM_CHANNEL_PAIR_INDEX_0, 4, hal_ll_tim_module_num(TIM_MODULE_3)},
    #endif
    #ifdef TIM3_CH1_PD1_AF4
    {GPIO_PD1, HAL_LL_TIM3_BASE_ADDR, HAL_LL_TIM_CHANNEL_1, HAL_LL_TIM_CHANNEL_PAIR_INDEX_1, 4, hal_ll_tim_module_num(TIM_MODULE_3)},
    #endif
    #ifdef TIM3_CH2_PD2_AF4
    {GPIO_PD2, HAL_LL_TIM3_BASE_ADDR, HAL_LL_TIM_CHANNEL_2, HAL_LL_TIM_CHANNEL_PAIR_INDEX_2, 4, hal_ll_tim_module_num(TIM_MODULE_3)},
    #endif
    #ifdef TIM3_CH3_PD3_AF4
    {GPIO_PD3, HAL_LL_TIM3_BASE_ADDR, HAL_LL_TIM_CHANNEL_3, HAL_LL_TIM_CHANNEL_PAIR_INDEX_3, 4, hal_ll_tim_module_num(TIM_MODULE_3)},
    #endif
    #ifdef TIM3_CH0_PE5_AF6
    {GPIO_PE5, HAL_LL_TIM3_BASE_ADDR, HAL_LL_TIM_CHANNEL_0, HAL_LL_TIM_CHANNEL_PAIR_INDEX_0, 6, hal_ll_tim_module_num(TIM_MODULE_3)},
    #endif
    #ifdef TIM3_CH1_PE6_AF6
    {GPIO_PE6, HAL_LL_TIM3_BASE_ADDR, HAL_LL_TIM_CHANNEL_1, HAL_LL_TIM_CHANNEL_PAIR_INDEX_1, 6, hal_ll_tim_module_num(TIM_MODULE_3)},
    #endif
    #ifdef TIM3_CH2_PE7_AF6
    {GPIO_PE7, HAL_LL_TIM3_BASE_ADDR, HAL_LL_TIM_CHANNEL_2, HAL_LL_TIM_CHANNEL_PAIR_INDEX_2, 6, hal_ll_tim_module_num(TIM_MODULE_3)},
    #endif
    #ifdef TIM3_CH3_PE8_AF6
    {GPIO_PE8, HAL_LL_TIM3_BASE_ADDR, HAL_LL_TIM_CHANNEL_3, HAL_LL_TIM_CHANNEL_PAIR_INDEX_3, 6, hal_ll_tim_module_num(TIM_MODULE_3)},
    #endif
    #ifdef TIM3_CH4_PE9_AF6
    {GPIO_PE9, HAL_LL_TIM3_BASE_ADDR, HAL_LL_TIM_CHANNEL_4, HAL_LL_TIM_CHANNEL_PAIR_INDEX_4, 6, hal_ll_tim_module_num(TIM_MODULE_3)},
    #endif
    #ifdef TIM3_CH5_PE10_AF6
    {GPIO_PE10, HAL_LL_TIM3_BASE_ADDR, HAL_LL_TIM_CHANNEL_5, HAL_LL_TIM_CHANNEL_PAIR_INDEX_5, 6, hal_ll_tim_module_num(TIM_MODULE_3)},
    #endif
    #ifdef TIM3_CH6_PE11_AF6
    {GPIO_PE11, HAL_LL_TIM3_BASE_ADDR, HAL_LL_TIM_CHANNEL_6, HAL_LL_TIM_CHANNEL_PAIR_INDEX_6, 6, hal_ll_tim_module_num(TIM_MODULE_3)},
    #endif
    #ifdef TIM3_CH7_PE12_AF6
    {GPIO_PE12, HAL_LL_TIM3_BASE_ADDR, HAL_LL_TIM_CHANNEL_7, HAL_LL_TIM_CHANNEL_PAIR_INDEX_7, 6, hal_ll_tim_module_num(TIM_MODULE_3)},
    #endif
    #ifdef TIM0_CH3_PA6_AF3
    {GPIO_PA6, HAL_LL_TIM0_BASE_ADDR, HAL_LL_TIM_CHANNEL_3, HAL_LL_TIM_CHANNEL_PAIR_INDEX_3, 3, hal_ll_tim_module_num(TIM_MODULE_0)},
    #endif
    #ifdef TIM0_CH4_PA7_AF3
    {GPIO_PA7, HAL_LL_TIM0_BASE_ADDR, HAL_LL_TIM_CHANNEL_4, HAL_LL_TIM_CHANNEL_PAIR_INDEX_4, 3, hal_ll_tim_module_num(TIM_MODULE_0)},
    #endif
    #ifdef TIM1_CH0_PA8_AF3
    {GPIO_PA8, HAL_LL_TIM1_BASE_ADDR, HAL_LL_TIM_CHANNEL_0, HAL_LL_TIM_CHANNEL_PAIR_INDEX_0, 3, hal_ll_tim_module_num(TIM_MODULE_1)},
    #endif
    #ifdef TIM1_CH1_PA9_AF3
    {GPIO_PA9, HAL_LL_TIM1_BASE_ADDR, HAL_LL_TIM_CHANNEL_1, HAL_LL_TIM_CHANNEL_PAIR_INDEX_1, 3, hal_ll_tim_module_num(TIM_MODULE_1)},
    #endif
    #ifdef TIM2_CH0_PA10_AF3
    {GPIO_PA10, HAL_LL_TIM2_BASE_ADDR, HAL_LL_TIM_CHANNEL_0, HAL_LL_TIM_CHANNEL_PAIR_INDEX_0, 3, hal_ll_tim_module_num(TIM_MODULE_2)},
    #endif
    #ifdef TIM2_CH1_PA11_AF3
    {GPIO_PA11, HAL_LL_TIM2_BASE_ADDR, HAL_LL_TIM_CHANNEL_1, HAL_LL_TIM_CHANNEL_PAIR_INDEX_1, 3, hal_ll_tim_module_num(TIM_MODULE_2)},
    #endif
    #ifdef TIM1_CH0_PB12_AF3
    {GPIO_PB12, HAL_LL_TIM1_BASE_ADDR, HAL_LL_TIM_CHANNEL_0, HAL_LL_TIM_CHANNEL_PAIR_INDEX_0, 3, hal_ll_tim_module_num(TIM_MODULE_1)},
    #endif
    #ifdef TIM0_CH4_PB12_AF4
    {GPIO_PB12, HAL_LL_TIM0_BASE_ADDR, HAL_LL_TIM_CHANNEL_4, HAL_LL_TIM_CHANNEL_PAIR_INDEX_4, 4, hal_ll_tim_module_num(TIM_MODULE_0)},
    #endif
    #ifdef TIM1_CH1_PB13_AF3
    {GPIO_PB13, HAL_LL_TIM1_BASE_ADDR, HAL_LL_TIM_CHANNEL_1, HAL_LL_TIM_CHANNEL_PAIR_INDEX_1, 3, hal_ll_tim_module_num(TIM_MODULE_1)},
    #endif
    #ifdef TIM0_CH5_PB13_AF4
    {GPIO_PB13, HAL_LL_TIM0_BASE_ADDR, HAL_LL_TIM_CHANNEL_5, HAL_LL_TIM_CHANNEL_PAIR_INDEX_5, 4, hal_ll_tim_module_num(TIM_MODULE_0)},
    #endif
    #ifdef TIM1_CH0_PE20_AF3
    {GPIO_PE20, HAL_LL_TIM1_BASE_ADDR, HAL_LL_TIM_CHANNEL_0, HAL_LL_TIM_CHANNEL_PAIR_INDEX_0, 3, hal_ll_tim_module_num(TIM_MODULE_1)},
    #endif
    #ifdef TIM1_CH1_PE21_AF3
    {GPIO_PE21, HAL_LL_TIM1_BASE_ADDR, HAL_LL_TIM_CHANNEL_1, HAL_LL_TIM_CHANNEL_PAIR_INDEX_1, 3, hal_ll_tim_module_num(TIM_MODULE_1)},
    #endif
    #ifdef TIM0_CH2_PE29_AF3
    {GPIO_PE29, HAL_LL_TIM0_BASE_ADDR, HAL_LL_TIM_CHANNEL_2, HAL_LL_TIM_CHANNEL_PAIR_INDEX_2, 3, hal_ll_tim_module_num(TIM_MODULE_0)},
    #endif
    #ifdef TIM0_CH3_PE30_AF3
    {GPIO_PE30, HAL_LL_TIM0_BASE_ADDR, HAL_LL_TIM_CHANNEL_3, HAL_LL_TIM_CHANNEL_PAIR_INDEX_3, 3, hal_ll_tim_module_num(TIM_MODULE_0)},
    #endif
    #ifdef TIM0_CH0_PE24_AF3
    {GPIO_PE24, HAL_LL_TIM0_BASE_ADDR, HAL_LL_TIM_CHANNEL_0, HAL_LL_TIM_CHANNEL_PAIR_INDEX_0, 3, hal_ll_tim_module_num(TIM_MODULE_0)},
    #endif
    #ifdef TIM0_CH1_PE25_AF3
    {GPIO_PE25, HAL_LL_TIM0_BASE_ADDR, HAL_LL_TIM_CHANNEL_1, HAL_LL_TIM_CHANNEL_PAIR_INDEX_1, 3, hal_ll_tim_module_num(TIM_MODULE_0)},
    #endif
    #ifdef TIM1_CH1_PA1_AF6
    {GPIO_PA1, HAL_LL_TIM1_BASE_ADDR, HAL_LL_TIM_CHANNEL_1, HAL_LL_TIM_CHANNEL_PAIR_INDEX_1, 6, hal_ll_tim_module_num(TIM_MODULE_1)},
    #endif
    #ifdef TIM1_CH0_PA2_AF6
    {GPIO_PA2, HAL_LL_TIM1_BASE_ADDR, HAL_LL_TIM_CHANNEL_0, HAL_LL_TIM_CHANNEL_PAIR_INDEX_0, 6, hal_ll_tim_module_num(TIM_MODULE_1)},
    #endif
    #ifdef TIM3_CH2_PA18_AF6
    {GPIO_PA18, HAL_LL_TIM3_BASE_ADDR, HAL_LL_TIM_CHANNEL_2, HAL_LL_TIM_CHANNEL_PAIR_INDEX_2, 6, hal_ll_tim_module_num(TIM_MODULE_3)},
    #endif
    #ifdef TIM0_CH0_PD0_AF5
    {GPIO_PD0, HAL_LL_TIM0_BASE_ADDR, HAL_LL_TIM_CHANNEL_0, HAL_LL_TIM_CHANNEL_PAIR_INDEX_0, 5, hal_ll_tim_module_num(TIM_MODULE_0)},
    #endif
    #ifdef TIM0_CH1_PD1_AF5
    {GPIO_PD1, HAL_LL_TIM0_BASE_ADDR, HAL_LL_TIM_CHANNEL_1, HAL_LL_TIM_CHANNEL_PAIR_INDEX_1, 5, hal_ll_tim_module_num(TIM_MODULE_0)},
    #endif
    #ifdef TIM0_CH2_PD2_AF5
    {GPIO_PD2, HAL_LL_TIM0_BASE_ADDR, HAL_LL_TIM_CHANNEL_2, HAL_LL_TIM_CHANNEL_PAIR_INDEX_2, 5, hal_ll_tim_module_num(TIM_MODULE_0)},
    #endif
    #ifdef TIM0_CH3_PD3_AF5
    {GPIO_PD3, HAL_LL_TIM0_BASE_ADDR, HAL_LL_TIM_CHANNEL_3, HAL_LL_TIM_CHANNEL_PAIR_INDEX_3, 5, hal_ll_tim_module_num(TIM_MODULE_0)},
    #endif
    #ifdef TIM1_CH0_PD6_AF5
    {GPIO_PD6, HAL_LL_TIM1_BASE_ADDR, HAL_LL_TIM_CHANNEL_0, HAL_LL_TIM_CHANNEL_PAIR_INDEX_0, 5, hal_ll_tim_module_num(TIM_MODULE_1)},
    #endif
    #ifdef TIM1_CH1_PD7_AF5
    {GPIO_PD7, HAL_LL_TIM1_BASE_ADDR, HAL_LL_TIM_CHANNEL_1, HAL_LL_TIM_CHANNEL_PAIR_INDEX_1, 5, hal_ll_tim_module_num(TIM_MODULE_1)},
    #endif
    #ifdef TIM3_CH2_PB18_AF4
    {GPIO_PB18, HAL_LL_TIM3_BASE_ADDR, HAL_LL_TIM_CHANNEL_2, HAL_LL_TIM_CHANNEL_PAIR_INDEX_2, 4, hal_ll_tim_module_num(TIM_MODULE_3)},
    #endif
    #ifdef TIM3_CH3_PB19_AF4
    {GPIO_PB19, HAL_LL_TIM3_BASE_ADDR, HAL_LL_TIM_CHANNEL_3, HAL_LL_TIM_CHANNEL_PAIR_INDEX_3, 4, hal_ll_tim_module_num(TIM_MODULE_3)},
    #endif
    #ifdef TIM0_CH4_PE26_AF3
    {GPIO_PE26, HAL_LL_TIM0_BASE_ADDR, HAL_LL_TIM_CHANNEL_4, HAL_LL_TIM_CHANNEL_PAIR_INDEX_4, 3, hal_ll_tim_module_num(TIM_MODULE_0)},
    #endif
    #ifdef TIM2_CH0_PE22_AF3
    {GPIO_PE22, HAL_LL_TIM2_BASE_ADDR, HAL_LL_TIM_CHANNEL_0, HAL_LL_TIM_CHANNEL_PAIR_INDEX_0, 3, hal_ll_tim_module_num(TIM_MODULE_2)},
    #endif
    #ifdef TIM2_CH1_PE23_AF3
    {GPIO_PE23, HAL_LL_TIM2_BASE_ADDR, HAL_LL_TIM_CHANNEL_1, HAL_LL_TIM_CHANNEL_PAIR_INDEX_1, 3, hal_ll_tim_module_num(TIM_MODULE_2)},
    #endif

    { HAL_LL_PIN_NC, HAL_LL_MODULE_ERROR, HAL_LL_CHANNEL_ERROR, HAL_LL_CHANNEL_ERROR, HAL_LL_PIN_NC, HAL_LL_PIN_NC }
};

#ifdef __cplusplus
}
#endif

#endif // _HAL_LL_TIM_PIN_MAP_H_
// ------------------------------------------------------------------------- END
