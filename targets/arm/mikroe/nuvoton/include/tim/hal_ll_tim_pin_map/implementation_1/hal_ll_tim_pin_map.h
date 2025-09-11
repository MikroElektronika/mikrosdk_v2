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

/*!< @brief TIMER module base addresses. */
#ifdef TIM_MODULE_0
static const hal_ll_base_addr_t HAL_LL_TIM0_BASE_ADDR = 0x40050000UL;
#endif
#ifdef TIM_MODULE_1
static const hal_ll_base_addr_t HAL_LL_TIM1_BASE_ADDR = 0x40050100UL;
#endif
#ifdef TIM_MODULE_2
static const hal_ll_base_addr_t HAL_LL_TIM2_BASE_ADDR = 0x40051000UL;
#endif
#ifdef TIM_MODULE_3
static const hal_ll_base_addr_t HAL_LL_TIM3_BASE_ADDR = 0x40051100UL;
#endif
#ifdef TIM_MODULE_4
static const hal_ll_base_addr_t HAL_LL_TIM4_BASE_ADDR = 0x40052000UL;
#endif
#ifdef TIM_MODULE_5
static const hal_ll_base_addr_t HAL_LL_TIM5_BASE_ADDR = 0x40052100UL;
#endif

typedef enum {
    HAL_LL_TIM_PIN_A = 0,
    HAL_LL_TIM_PIN_B
} hal_ll_tim_pin_type_t;

/*!< @brief TIM pin structure. */
typedef struct {
    hal_ll_pin_name_t pin;
    hal_ll_base_addr_t base;
    uint8_t af;
    hal_ll_pin_name_t module_index;
    hal_ll_tim_pin_type_t pin_type;
} hal_ll_tim_pin_map_t;

/*!< TIM modules. */
#ifdef TIM_MODULE_0
#define HAL_LL_TIM0_GPIO_AF13 13
#define HAL_LL_TIM0_GPIO_AF14 14
#endif
#ifdef TIM_MODULE_1
#define HAL_LL_TIM1_GPIO_AF13 13
#define HAL_LL_TIM1_GPIO_AF14 14
#endif
#ifdef TIM_MODULE_2
#define HAL_LL_TIM2_GPIO_AF13 13
#define HAL_LL_TIM2_GPIO_AF14 14
#endif
#ifdef TIM_MODULE_3
#define HAL_LL_TIM3_GPIO_AF13 13
#define HAL_LL_TIM3_GPIO_AF14 14
#endif
#ifdef TIM_MODULE_4
#define HAL_LL_TIM4_GPIO_AF10 10
#define HAL_LL_TIM4_GPIO_AF12 12
#define HAL_LL_TIM4_GPIO_AF13 13
#define HAL_LL_TIM4_GPIO_AF14 14
#endif
#ifdef TIM_MODULE_5
#define HAL_LL_TIM5_GPIO_AF10 10
#define HAL_LL_TIM5_GPIO_AF12 12
#define HAL_LL_TIM5_GPIO_AF13 13
#define HAL_LL_TIM5_GPIO_AF14 14
#endif

/*!< TIM pins. */
static const hal_ll_tim_pin_map_t hal_ll_tim_pin_map[] = {
    
    #ifdef TIM0_PG2_AF13
    {GPIO_PG2, HAL_LL_TIM0_BASE_ADDR, HAL_LL_TIM0_GPIO_AF13, hal_ll_tim_module_num(TIM_MODULE_0)},
    #endif
    #ifdef TIM0_PB5_AF14
    {GPIO_PB5, HAL_LL_TIM0_BASE_ADDR, HAL_LL_TIM0_GPIO_AF14, hal_ll_tim_module_num(TIM_MODULE_0)},
    #endif
    #ifdef TIM0_PC7_AF14
    {GPIO_PC7, HAL_LL_TIM0_BASE_ADDR, HAL_LL_TIM0_GPIO_AF14, hal_ll_tim_module_num(TIM_MODULE_0)},
    #endif
    #ifdef TIM1_PC14_AF13
    {GPIO_PC14, HAL_LL_TIM1_BASE_ADDR, HAL_LL_TIM1_GPIO_AF13, hal_ll_tim_module_num(TIM_MODULE_1)},
    #endif
    #ifdef TIM1_PG3_AF13
    {GPIO_PG3, HAL_LL_TIM1_BASE_ADDR, HAL_LL_TIM1_GPIO_AF13, hal_ll_tim_module_num(TIM_MODULE_1)},
    #endif
    #ifdef TIM1_PB4_AF14
    {GPIO_PB4, HAL_LL_TIM1_BASE_ADDR, HAL_LL_TIM1_GPIO_AF14, hal_ll_tim_module_num(TIM_MODULE_1)},
    #endif
    #ifdef TIM1_PC6_AF14
    {GPIO_PC6, HAL_LL_TIM1_BASE_ADDR, HAL_LL_TIM1_GPIO_AF14, hal_ll_tim_module_num(TIM_MODULE_1)},
    #endif
    #ifdef TIM2_PG4_AF13
    {GPIO_PG4, HAL_LL_TIM2_BASE_ADDR, HAL_LL_TIM2_GPIO_AF13, hal_ll_tim_module_num(TIM_MODULE_2)},
    #endif
    #ifdef TIM2_PA7_AF14
    {GPIO_PA7, HAL_LL_TIM2_BASE_ADDR, HAL_LL_TIM2_GPIO_AF14, hal_ll_tim_module_num(TIM_MODULE_2)},
    #endif
    #ifdef TIM2_PB3_AF14
    {GPIO_PB3, HAL_LL_TIM2_BASE_ADDR, HAL_LL_TIM2_GPIO_AF14, hal_ll_tim_module_num(TIM_MODULE_2)},
    #endif
    #ifdef TIM2_PD0_AF14
    {GPIO_PD0, HAL_LL_TIM2_BASE_ADDR, HAL_LL_TIM2_GPIO_AF14, hal_ll_tim_module_num(TIM_MODULE_2)},
    #endif
    #ifdef TIM3_PF11_AF13
    {GPIO_PF11, HAL_LL_TIM3_BASE_ADDR, HAL_LL_TIM3_GPIO_AF13, hal_ll_tim_module_num(TIM_MODULE_3)},
    #endif
    #ifdef TIM3_PA6_AF14
    {GPIO_PA6, HAL_LL_TIM3_BASE_ADDR, HAL_LL_TIM3_GPIO_AF14, hal_ll_tim_module_num(TIM_MODULE_3)},
    #endif
    #ifdef TIM3_PB2_AF14
    {GPIO_PB2, HAL_LL_TIM3_BASE_ADDR, HAL_LL_TIM3_GPIO_AF14, hal_ll_tim_module_num(TIM_MODULE_3)},
    #endif
    #ifdef TIM4_PA7_AF10
    {GPIO_PA7, HAL_LL_TIM4_BASE_ADDR, HAL_LL_TIM4_GPIO_AF10, hal_ll_tim_module_num(TIM_MODULE_4)},
    #endif
    #ifdef TIM4_PG4_AF12
    {GPIO_PG4, HAL_LL_TIM4_BASE_ADDR, HAL_LL_TIM4_GPIO_AF12, hal_ll_tim_module_num(TIM_MODULE_4)},
    #endif
    #ifdef TIM4_PB3_AF13
    {GPIO_PB3, HAL_LL_TIM4_BASE_ADDR, HAL_LL_TIM4_GPIO_AF13, hal_ll_tim_module_num(TIM_MODULE_4)},
    #endif
    #ifdef TIM5_PA6_AF10
    {GPIO_PA6, HAL_LL_TIM5_BASE_ADDR, HAL_LL_TIM5_GPIO_AF10, hal_ll_tim_module_num(TIM_MODULE_5)},
    #endif
    #ifdef TIM5_PF11_AF12
    {GPIO_PF11, HAL_LL_TIM5_BASE_ADDR, HAL_LL_TIM5_GPIO_AF12, hal_ll_tim_module_num(TIM_MODULE_5)},
    #endif
    #ifdef TIM5_PB2_AF13
    {GPIO_PB2, HAL_LL_TIM5_BASE_ADDR, HAL_LL_TIM5_GPIO_AF13, hal_ll_tim_module_num(TIM_MODULE_5)},
    #endif

    { HAL_LL_PIN_NC, HAL_LL_MODULE_ERROR, HAL_LL_PIN_NC, HAL_LL_PIN_NC }
};

#ifdef __cplusplus
}
#endif

#endif // _HAL_LL_TIM_PIN_MAP_H_
// ------------------------------------------------------------------------- END