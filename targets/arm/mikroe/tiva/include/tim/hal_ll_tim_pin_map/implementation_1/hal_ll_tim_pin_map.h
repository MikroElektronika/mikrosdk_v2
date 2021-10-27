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

/*!< @brief Macro defining `weak` attribute */
#define __weak __attribute__((weak))
/*!< @brief Helper macro for getting adequate module index number */
#define hal_ll_tim_module_num(_module_num) (_module_num - 1)

/*!< @brief TIMER module base addresses. */
#ifdef TIM_MODULE_0
static const hal_ll_base_addr_t HAL_LL_TIM0_BASE_ADDR = 0x40030000;
#endif
#ifdef TIM_MODULE_1
static const hal_ll_base_addr_t HAL_LL_TIM1_BASE_ADDR = 0x40031000;
#endif
#ifdef TIM_MODULE_2
static const hal_ll_base_addr_t HAL_LL_TIM2_BASE_ADDR = 0x40032000;
#endif
#ifdef TIM_MODULE_3
static const hal_ll_base_addr_t HAL_LL_TIM3_BASE_ADDR = 0x40033000;
#endif
#ifdef TIM_MODULE_4
static const hal_ll_base_addr_t HAL_LL_TIM4_BASE_ADDR = 0x40034000;
#endif
#ifdef TIM_MODULE_5
static const hal_ll_base_addr_t HAL_LL_TIM5_BASE_ADDR = 0x40035000;
#endif
#ifdef TIM_MODULE_6
#ifdef TM4C129
static const hal_ll_base_addr_t HAL_LL_TIM6_BASE_ADDR = 0x400E0000;
#else
static const hal_ll_base_addr_t HAL_LL_TIM6_BASE_ADDR = 0x4003E000;
#endif
#endif
#ifdef TIM_MODULE_7
#ifdef TM4C129
static const hal_ll_base_addr_t HAL_LL_TIM7_BASE_ADDR = 0x400E1000;
#else
static const hal_ll_base_addr_t HAL_LL_TIM7_BASE_ADDR = 0x4003E100;
#endif
#endif

/*!< @brief TIM pin structure. */
typedef struct {
    hal_ll_pin_name_t pin;
    hal_ll_base_addr_t base;
    uint8_t af;
    hal_ll_pin_name_t module_index;
} hal_ll_tim_pin_map_t;

/*!< TIM pins. */
__weak static const hal_ll_tim_pin_map_t _tim_map[] = {
    #ifdef TIM0_CCP0_PB6_AF7
    {PB6, HAL_LL_TIM0_BASE_ADDR, 7, hal_ll_tim_module_num(TIM_MODULE_0)},
    #endif
    #ifdef TIM0_CCP0_PF0_AF7
    {PF0, HAL_LL_TIM0_BASE_ADDR, 7, hal_ll_tim_module_num(TIM_MODULE_0)},
    #endif
    #ifdef TIM0_CCP1_PB7_AF7
    {PB7, HAL_LL_TIM0_BASE_ADDR, 7, hal_ll_tim_module_num(TIM_MODULE_0)},
    #endif
    #ifdef TIM0_CCP1_PF1_AF7
    {PF1, HAL_LL_TIM0_BASE_ADDR, 7, hal_ll_tim_module_num(TIM_MODULE_0)},
    #endif
    #ifdef TIM1_CCP0_PB4_AF7
    {PB4, HAL_LL_TIM1_BASE_ADDR, 7, hal_ll_tim_module_num(TIM_MODULE_1)},
    #endif
    #ifdef TIM1_CCP0_PF2_AF7
    {PF2, HAL_LL_TIM1_BASE_ADDR, 7, hal_ll_tim_module_num(TIM_MODULE_1)},
    #endif
    #ifdef TIM1_CCP1_PB5_AF7
    {PB5, HAL_LL_TIM1_BASE_ADDR, 7, hal_ll_tim_module_num(TIM_MODULE_1)},
    #endif
    #ifdef TIM1_CCP1_PF3_AF7
    {PF3, HAL_LL_TIM1_BASE_ADDR, 7, hal_ll_tim_module_num(TIM_MODULE_1)},
    #endif
    #ifdef TIM2_CCP0_PB0_AF7
    {PB0, HAL_LL_TIM2_BASE_ADDR, 7, hal_ll_tim_module_num(TIM_MODULE_2)},
    #endif
    #ifdef TIM2_CCP0_PF4_AF7
    {PF4, HAL_LL_TIM2_BASE_ADDR, 7, hal_ll_tim_module_num(TIM_MODULE_2)},
    #endif
    #ifdef TIM2_CCP1_PB1_AF7
    {PB1, HAL_LL_TIM2_BASE_ADDR, 7, hal_ll_tim_module_num(TIM_MODULE_2)},
    #endif
    #ifdef TIM3_CCP0_PB2_AF7
    {PB2, HAL_LL_TIM3_BASE_ADDR, 7, hal_ll_tim_module_num(TIM_MODULE_3)},
    #endif
    #ifdef TIM3_CCP1_PB3_AF7
    {PB3, HAL_LL_TIM3_BASE_ADDR, 7, hal_ll_tim_module_num(TIM_MODULE_3)},
    #endif
    #ifdef TIM4_CCP0_PC0_AF7
    {PC0, HAL_LL_TIM4_BASE_ADDR, 7, hal_ll_tim_module_num(TIM_MODULE_4)},
    #endif
    #ifdef TIM4_CCP0_PG0_AF7
    {PG0, HAL_LL_TIM4_BASE_ADDR, 7, hal_ll_tim_module_num(TIM_MODULE_4)},
    #endif
    #ifdef TIM4_CCP1_PC1_AF7
    {PC1, HAL_LL_TIM4_BASE_ADDR, 7, hal_ll_tim_module_num(TIM_MODULE_4)},
    #endif
    #ifdef TIM4_CCP1_PG1_AF7
    {PG1, HAL_LL_TIM4_BASE_ADDR, 7, hal_ll_tim_module_num(TIM_MODULE_4)},
    #endif
    #ifdef TIM5_CCP0_PC2_AF7
    {PC2, HAL_LL_TIM5_BASE_ADDR, 7, hal_ll_tim_module_num(TIM_MODULE_5)},
    #endif
    #ifdef TIM5_CCP0_PG2_AF7
    {PG2, HAL_LL_TIM5_BASE_ADDR, 7, hal_ll_tim_module_num(TIM_MODULE_5)},
    #endif
    #ifdef TIM5_CCP1_PC3_AF7
    {PC3, HAL_LL_TIM5_BASE_ADDR, 7, hal_ll_tim_module_num(TIM_MODULE_5)},
    #endif
    #ifdef TIM5_CCP1_PG3_AF7
    {PG3, HAL_LL_TIM5_BASE_ADDR, 7, hal_ll_tim_module_num(TIM_MODULE_5)},
    #endif
    #ifdef TIM1_CCP0_PJ0_AF7
    {PJ0, HAL_LL_TIM1_BASE_ADDR, 7, hal_ll_tim_module_num(TIM_MODULE_1)},
    #endif
    #ifdef TIM1_CCP1_PJ1_AF7
    {PJ1, HAL_LL_TIM1_BASE_ADDR, 7, hal_ll_tim_module_num(TIM_MODULE_1)},
    #endif
    #ifdef TIM2_CCP0_PJ2_AF7
    {PJ2, HAL_LL_TIM2_BASE_ADDR, 7, hal_ll_tim_module_num(TIM_MODULE_2)},
    #endif
    #ifdef TIM2_CCP1_PF5_AF7
    {PF5, HAL_LL_TIM2_BASE_ADDR, 7, hal_ll_tim_module_num(TIM_MODULE_2)},
    #endif
    #ifdef TIM3_CCP0_PF6_AF7
    {PF6, HAL_LL_TIM3_BASE_ADDR, 7, hal_ll_tim_module_num(TIM_MODULE_3)},
    #endif
    #ifdef TIM3_CCP1_PF7_AF7
    {PF7, HAL_LL_TIM3_BASE_ADDR, 7, hal_ll_tim_module_num(TIM_MODULE_3)},
    #endif
    #ifdef TIM0_CCP0_PL0_AF7
    {PL0, HAL_LL_TIM0_BASE_ADDR, 7, hal_ll_tim_module_num(TIM_MODULE_0)},
    #endif
    #ifdef TIM0_CCP1_PL1_AF7
    {PL1, HAL_LL_TIM0_BASE_ADDR, 7, hal_ll_tim_module_num(TIM_MODULE_0)},
    #endif
    #ifdef TIM1_CCP0_PL2_AF7
    {PL2, HAL_LL_TIM1_BASE_ADDR, 7, hal_ll_tim_module_num(TIM_MODULE_1)},
    #endif
    #ifdef TIM1_CCP1_PL3_AF7
    {PL3, HAL_LL_TIM1_BASE_ADDR, 7, hal_ll_tim_module_num(TIM_MODULE_1)},
    #endif
    #ifdef TIM2_CCP0_PL4_AF7
    {PL4, HAL_LL_TIM2_BASE_ADDR, 7, hal_ll_tim_module_num(TIM_MODULE_2)},
    #endif
    #ifdef TIM2_CCP1_PJ3_AF7
    {PJ3, HAL_LL_TIM2_BASE_ADDR, 7, hal_ll_tim_module_num(TIM_MODULE_2)},
    #endif
    #ifdef TIM2_CCP1_PL5_AF7
    {PL5, HAL_LL_TIM2_BASE_ADDR, 7, hal_ll_tim_module_num(TIM_MODULE_2)},
    #endif
    #ifdef TIM3_CCP0_PJ4_AF7
    {PJ4, HAL_LL_TIM3_BASE_ADDR, 7, hal_ll_tim_module_num(TIM_MODULE_3)},
    #endif
    #ifdef TIM3_CCP0_PL6_AF7
    {PL6, HAL_LL_TIM3_BASE_ADDR, 7, hal_ll_tim_module_num(TIM_MODULE_3)},
    #endif
    #ifdef TIM3_CCP1_PJ5_AF7
    {PJ5, HAL_LL_TIM3_BASE_ADDR, 7, hal_ll_tim_module_num(TIM_MODULE_3)},
    #endif
    #ifdef TIM3_CCP1_PL7_AF7
    {PL7, HAL_LL_TIM3_BASE_ADDR, 7, hal_ll_tim_module_num(TIM_MODULE_3)},
    #endif
    #ifdef TIM4_CCP0_PM0_AF7
    {PM0, HAL_LL_TIM4_BASE_ADDR, 7, hal_ll_tim_module_num(TIM_MODULE_4)},
    #endif
    #ifdef TIM4_CCP0_PP0_AF7
    {PP0, HAL_LL_TIM4_BASE_ADDR, 7, hal_ll_tim_module_num(TIM_MODULE_4)},
    #endif
    #ifdef TIM4_CCP1_PM1_AF7
    {PM1, HAL_LL_TIM4_BASE_ADDR, 7, hal_ll_tim_module_num(TIM_MODULE_4)},
    #endif
    #ifdef TIM4_CCP1_PP1_AF7
    {PP1, HAL_LL_TIM4_BASE_ADDR, 7, hal_ll_tim_module_num(TIM_MODULE_4)},
    #endif
    #ifdef TIM5_CCP0_PM2_AF7
    {PM2, HAL_LL_TIM5_BASE_ADDR, 7, hal_ll_tim_module_num(TIM_MODULE_5)},
    #endif
    #ifdef TIM5_CCP0_PP2_AF7
    {PP2, HAL_LL_TIM5_BASE_ADDR, 7, hal_ll_tim_module_num(TIM_MODULE_5)},
    #endif
    #ifdef TIM5_CCP1_PM3_AF7
    {PM3, HAL_LL_TIM5_BASE_ADDR, 7, hal_ll_tim_module_num(TIM_MODULE_5)},
    #endif
    #ifdef TIM5_CCP1_PP3_AF7
    {PP3, HAL_LL_TIM5_BASE_ADDR, 7, hal_ll_tim_module_num(TIM_MODULE_5)},
    #endif
    #ifdef TIM0_CCP0_PA0_AF3
    {PA0, HAL_LL_TIM0_BASE_ADDR, 3, hal_ll_tim_module_num(TIM_MODULE_0)},
    #endif
    #ifdef TIM0_CCP0_PD0_AF3
    {PD0, HAL_LL_TIM0_BASE_ADDR, 3, hal_ll_tim_module_num(TIM_MODULE_0)},
    #endif
    #ifdef TIM0_CCP0_PL4_AF3
    {PL4, HAL_LL_TIM0_BASE_ADDR, 3, hal_ll_tim_module_num(TIM_MODULE_0)},
    #endif
    #ifdef TIM0_CCP1_PA1_AF3
    {PA1, HAL_LL_TIM0_BASE_ADDR, 3, hal_ll_tim_module_num(TIM_MODULE_0)},
    #endif
    #ifdef TIM0_CCP1_PD1_AF3
    {PD1, HAL_LL_TIM0_BASE_ADDR, 3, hal_ll_tim_module_num(TIM_MODULE_0)},
    #endif
    #ifdef TIM0_CCP1_PL5_AF3
    {PL5, HAL_LL_TIM0_BASE_ADDR, 3, hal_ll_tim_module_num(TIM_MODULE_0)},
    #endif
    #ifdef TIM1_CCP0_PA2_AF3
    {PA2, HAL_LL_TIM1_BASE_ADDR, 3, hal_ll_tim_module_num(TIM_MODULE_1)},
    #endif
    #ifdef TIM1_CCP0_PD2_AF3
    {PD2, HAL_LL_TIM1_BASE_ADDR, 3, hal_ll_tim_module_num(TIM_MODULE_1)},
    #endif
    #ifdef TIM1_CCP0_PL6_AF3
    {PL6, HAL_LL_TIM1_BASE_ADDR, 3, hal_ll_tim_module_num(TIM_MODULE_1)},
    #endif
    #ifdef TIM1_CCP1_PA3_AF3
    {PA3, HAL_LL_TIM1_BASE_ADDR, 3, hal_ll_tim_module_num(TIM_MODULE_1)},
    #endif
    #ifdef TIM1_CCP1_PD3_AF3
    {PD3, HAL_LL_TIM1_BASE_ADDR, 3, hal_ll_tim_module_num(TIM_MODULE_1)},
    #endif
    #ifdef TIM1_CCP1_PL7_AF3
    {PL7, HAL_LL_TIM1_BASE_ADDR, 3, hal_ll_tim_module_num(TIM_MODULE_1)},
    #endif
    #ifdef TIM2_CCP0_PA4_AF3
    {PA4, HAL_LL_TIM2_BASE_ADDR, 3, hal_ll_tim_module_num(TIM_MODULE_2)},
    #endif
    #ifdef TIM2_CCP0_PM0_AF3
    {PM0, HAL_LL_TIM2_BASE_ADDR, 3, hal_ll_tim_module_num(TIM_MODULE_2)},
    #endif
    #ifdef TIM2_CCP1_PA5_AF3
    {PA5, HAL_LL_TIM2_BASE_ADDR, 3, hal_ll_tim_module_num(TIM_MODULE_2)},
    #endif
    #ifdef TIM2_CCP1_PM1_AF3
    {PM1, HAL_LL_TIM2_BASE_ADDR, 3, hal_ll_tim_module_num(TIM_MODULE_2)},
    #endif
    #ifdef TIM3_CCP0_PA6_AF3
    {PA6, HAL_LL_TIM3_BASE_ADDR, 3, hal_ll_tim_module_num(TIM_MODULE_3)},
    #endif
    #ifdef TIM3_CCP0_PD4_AF3
    {PD4, HAL_LL_TIM3_BASE_ADDR, 3, hal_ll_tim_module_num(TIM_MODULE_3)},
    #endif
    #ifdef TIM3_CCP0_PM2_AF3
    {PM2, HAL_LL_TIM3_BASE_ADDR, 3, hal_ll_tim_module_num(TIM_MODULE_3)},
    #endif
    #ifdef TIM3_CCP1_PA7_AF3
    {PA7, HAL_LL_TIM3_BASE_ADDR, 3, hal_ll_tim_module_num(TIM_MODULE_3)},
    #endif
    #ifdef TIM3_CCP1_PD5_AF3
    {PD5, HAL_LL_TIM3_BASE_ADDR, 3, hal_ll_tim_module_num(TIM_MODULE_3)},
    #endif
    #ifdef TIM3_CCP1_PM3_AF3
    {PM3, HAL_LL_TIM3_BASE_ADDR, 3, hal_ll_tim_module_num(TIM_MODULE_3)},
    #endif
    #ifdef TIM4_CCP0_PB0_AF3
    {PB0, HAL_LL_TIM4_BASE_ADDR, 3, hal_ll_tim_module_num(TIM_MODULE_4)},
    #endif
    #ifdef TIM4_CCP0_PD6_AF3
    {PD6, HAL_LL_TIM4_BASE_ADDR, 3, hal_ll_tim_module_num(TIM_MODULE_4)},
    #endif
    #ifdef TIM4_CCP0_PM4_AF3
    {PM4, HAL_LL_TIM4_BASE_ADDR, 3, hal_ll_tim_module_num(TIM_MODULE_4)},
    #endif
    #ifdef TIM4_CCP1_PB1_AF3
    {PB1, HAL_LL_TIM4_BASE_ADDR, 3, hal_ll_tim_module_num(TIM_MODULE_4)},
    #endif
    #ifdef TIM4_CCP1_PD7_AF3
    {PD7, HAL_LL_TIM4_BASE_ADDR, 3, hal_ll_tim_module_num(TIM_MODULE_4)},
    #endif
    #ifdef TIM4_CCP1_PM5_AF3
    {PM5, HAL_LL_TIM4_BASE_ADDR, 3, hal_ll_tim_module_num(TIM_MODULE_4)},
    #endif
    #ifdef TIM5_CCP0_PB2_AF3
    {PB2, HAL_LL_TIM5_BASE_ADDR, 3, hal_ll_tim_module_num(TIM_MODULE_5)},
    #endif
    #ifdef TIM5_CCP0_PM6_AF3
    {PM6, HAL_LL_TIM5_BASE_ADDR, 3, hal_ll_tim_module_num(TIM_MODULE_5)},
    #endif
    #ifdef TIM5_CCP1_PB3_AF3
    {PB3, HAL_LL_TIM5_BASE_ADDR, 3, hal_ll_tim_module_num(TIM_MODULE_5)},
    #endif
    #ifdef TIM5_CCP1_PM7_AF3
    {PM7, HAL_LL_TIM5_BASE_ADDR, 3, hal_ll_tim_module_num(TIM_MODULE_5)},
    #endif
    #ifdef TIM0_CCP0_PR4_AF3
    {PR4, HAL_LL_TIM0_BASE_ADDR, 3, hal_ll_tim_module_num(TIM_MODULE_0)},
    #endif
    #ifdef TIM0_CCP1_PR5_AF3
    {PR5, HAL_LL_TIM0_BASE_ADDR, 3, hal_ll_tim_module_num(TIM_MODULE_0)},
    #endif
    #ifdef TIM1_CCP0_PR6_AF3
    {PR6, HAL_LL_TIM1_BASE_ADDR, 3, hal_ll_tim_module_num(TIM_MODULE_1)},
    #endif
    #ifdef TIM1_CCP1_PR7_AF3
    {PR7, HAL_LL_TIM1_BASE_ADDR, 3, hal_ll_tim_module_num(TIM_MODULE_1)},
    #endif
    #ifdef TIM2_CCP0_PS0_AF3
    {PS0, HAL_LL_TIM2_BASE_ADDR, 3, hal_ll_tim_module_num(TIM_MODULE_2)},
    #endif
    #ifdef TIM2_CCP1_PS1_AF3
    {PS1, HAL_LL_TIM2_BASE_ADDR, 3, hal_ll_tim_module_num(TIM_MODULE_2)},
    #endif
    #ifdef TIM3_CCP0_PS2_AF3
    {PS2, HAL_LL_TIM3_BASE_ADDR, 3, hal_ll_tim_module_num(TIM_MODULE_3)},
    #endif
    #ifdef TIM3_CCP1_PS3_AF3
    {PS3, HAL_LL_TIM3_BASE_ADDR, 3, hal_ll_tim_module_num(TIM_MODULE_3)},
    #endif
    #ifdef TIM4_CCP0_PS4_AF3
    {PS4, HAL_LL_TIM4_BASE_ADDR, 3, hal_ll_tim_module_num(TIM_MODULE_4)},
    #endif
    #ifdef TIM4_CCP1_PS5_AF3
    {PS5, HAL_LL_TIM4_BASE_ADDR, 3, hal_ll_tim_module_num(TIM_MODULE_4)},
    #endif
    #ifdef TIM5_CCP0_PS6_AF3
    {PS6, HAL_LL_TIM5_BASE_ADDR, 3, hal_ll_tim_module_num(TIM_MODULE_5)},
    #endif
    #ifdef TIM5_CCP1_PS7_AF3
    {PS7, HAL_LL_TIM5_BASE_ADDR, 3, hal_ll_tim_module_num(TIM_MODULE_5)},
    #endif
    #ifdef TIM6_CCP0_PB6_AF3
    {PB6, HAL_LL_TIM6_BASE_ADDR, 3, hal_ll_tim_module_num(TIM_MODULE_6)},
    #endif
    #ifdef TIM6_CCP0_PP0_AF5
    {PP0, HAL_LL_TIM6_BASE_ADDR, 5, hal_ll_tim_module_num(TIM_MODULE_6)},
    #endif
    #ifdef TIM6_CCP0_PQ0_AF3
    {PQ0, HAL_LL_TIM6_BASE_ADDR, 3, hal_ll_tim_module_num(TIM_MODULE_6)},
    #endif
    #ifdef TIM6_CCP0_PT0_AF3
    {PT0, HAL_LL_TIM6_BASE_ADDR, 3, hal_ll_tim_module_num(TIM_MODULE_6)},
    #endif
    #ifdef TIM6_CCP1_PB7_AF3
    {PB7, HAL_LL_TIM6_BASE_ADDR, 3, hal_ll_tim_module_num(TIM_MODULE_6)},
    #endif
    #ifdef TIM6_CCP1_PP1_AF5
    {PP1, HAL_LL_TIM6_BASE_ADDR, 5, hal_ll_tim_module_num(TIM_MODULE_6)},
    #endif
    #ifdef TIM6_CCP1_PQ1_AF3
    {PQ1, HAL_LL_TIM6_BASE_ADDR, 3, hal_ll_tim_module_num(TIM_MODULE_6)},
    #endif
    #ifdef TIM6_CCP1_PT1_AF3
    {PT1, HAL_LL_TIM6_BASE_ADDR, 3, hal_ll_tim_module_num(TIM_MODULE_6)},
    #endif
    #ifdef TIM7_CCP0_PC4_AF3
    {PC4, HAL_LL_TIM7_BASE_ADDR, 3, hal_ll_tim_module_num(TIM_MODULE_7)},
    #endif
    #ifdef TIM7_CCP0_PQ2_AF3
    {PQ2, HAL_LL_TIM7_BASE_ADDR, 3, hal_ll_tim_module_num(TIM_MODULE_7)},
    #endif
    #ifdef TIM7_CCP0_PT2_AF3
    {PT2, HAL_LL_TIM7_BASE_ADDR, 3, hal_ll_tim_module_num(TIM_MODULE_7)},
    #endif
    #ifdef TIM7_CCP1_PC5_AF3
    {PC5, HAL_LL_TIM7_BASE_ADDR, 3, hal_ll_tim_module_num(TIM_MODULE_7)},
    #endif
    #ifdef TIM7_CCP1_PQ3_AF3
    {PQ3, HAL_LL_TIM7_BASE_ADDR, 3, hal_ll_tim_module_num(TIM_MODULE_7)},
    #endif
    #ifdef TIM7_CCP1_PT3_AF3
    {PT3, HAL_LL_TIM7_BASE_ADDR, 3, hal_ll_tim_module_num(TIM_MODULE_7)},
    #endif

    { HAL_LL_PIN_NC, HAL_LL_MODULE_ERROR, HAL_LL_PIN_NC, HAL_LL_PIN_NC }
};

#ifdef __cplusplus
}
#endif

#endif // _HAL_LL_TIM_PIN_MAP_H_
// ------------------------------------------------------------------------- END
