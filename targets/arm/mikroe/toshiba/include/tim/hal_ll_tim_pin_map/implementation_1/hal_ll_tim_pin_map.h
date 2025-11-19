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
static const hal_ll_base_addr_t HAL_LL_TIM0_BASE_ADDR = 0x400C1000UL; // T32A0
#endif
#ifdef TIM_MODULE_1
static const hal_ll_base_addr_t HAL_LL_TIM1_BASE_ADDR = 0x400C1400UL; // T32A1
#endif
#ifdef TIM_MODULE_2
static const hal_ll_base_addr_t HAL_LL_TIM2_BASE_ADDR = 0x400C1800UL; // T32A2
#endif
#ifdef TIM_MODULE_3
static const hal_ll_base_addr_t HAL_LL_TIM3_BASE_ADDR = 0x400C1C00UL; // T32A3
#endif
#ifdef TIM_MODULE_4
static const hal_ll_base_addr_t HAL_LL_TIM4_BASE_ADDR = 0x400C2000UL; // T32A4
#endif
#ifdef TIM_MODULE_5
static const hal_ll_base_addr_t HAL_LL_TIM5_BASE_ADDR = 0x400C2400UL; // T32A5
#endif

typedef enum {
    HAL_LL_TIM_PIN_A = 0,
    HAL_LL_TIM_PIN_B,
    HAL_LL_TIM_PIN_C
} hal_ll_tim_pin_type_t;

/**
 * Alternate Function Values.
 */
typedef enum
{
    HAL_LL_ALTERNATE_FUNCTION_1 = 1,
    HAL_LL_ALTERNATE_FUNCTION_2,
    HAL_LL_ALTERNATE_FUNCTION_3,
    HAL_LL_ALTERNATE_FUNCTION_4,
    HAL_LL_ALTERNATE_FUNCTION_5,
    HAL_LL_ALTERNATE_FUNCTION_6,
    HAL_LL_ALTERNATE_FUNCTION_7
} hal_ll_alternate_function_t;

/*!< @brief TIM pin structure. */
typedef struct {
    hal_ll_pin_name_t pin;
    hal_ll_base_addr_t base;
    hal_ll_alternate_function_t af;
    hal_ll_pin_name_t module_index;
    hal_ll_tim_pin_type_t pin_type;
} hal_ll_tim_pin_map_t;

/*!< TIM pins. */
static const hal_ll_tim_pin_map_t hal_ll_tim_pin_map[] = {
    #ifdef TIM0_CH0_PA3_AF4
    {GPIO_PA3, HAL_LL_TIM0_BASE_ADDR, HAL_LL_ALTERNATE_FUNCTION_4, hal_ll_tim_module_num( TIM_MODULE_0 ), HAL_LL_TIM_PIN_A},
    #endif
    #ifdef TIM0_CH1_PA4_AF4
    {GPIO_PA4, HAL_LL_TIM0_BASE_ADDR, HAL_LL_ALTERNATE_FUNCTION_4, hal_ll_tim_module_num( TIM_MODULE_0 ), HAL_LL_TIM_PIN_B},
    #endif
    #ifdef TIM0_CH2_PA3_AF5
    {GPIO_PA3, HAL_LL_TIM0_BASE_ADDR, HAL_LL_ALTERNATE_FUNCTION_5, hal_ll_tim_module_num( TIM_MODULE_0 ), HAL_LL_TIM_PIN_C},
    #endif
    #ifdef TIM1_CH0_PF4_AF4
    {GPIO_PF4, HAL_LL_TIM1_BASE_ADDR, HAL_LL_ALTERNATE_FUNCTION_4, hal_ll_tim_module_num( TIM_MODULE_1 ), HAL_LL_TIM_PIN_A},
    #endif
    #ifdef TIM1_CH1_PV0_AF4
    {GPIO_PV0, HAL_LL_TIM1_BASE_ADDR, HAL_LL_ALTERNATE_FUNCTION_4, hal_ll_tim_module_num( TIM_MODULE_1 ), HAL_LL_TIM_PIN_B},
    #endif
    #ifdef TIM1_CH2_PF4_AF5
    {GPIO_PF4, HAL_LL_TIM1_BASE_ADDR, HAL_LL_ALTERNATE_FUNCTION_5, hal_ll_tim_module_num( TIM_MODULE_1 ), HAL_LL_TIM_PIN_C},
    #endif
    #ifdef TIM2_CH0_PC1_AF5
    {GPIO_PC1, HAL_LL_TIM2_BASE_ADDR, HAL_LL_ALTERNATE_FUNCTION_5, hal_ll_tim_module_num( TIM_MODULE_2 ), HAL_LL_TIM_PIN_A},
    #endif
    #ifdef TIM2_CH0_PU2_AF4
    {GPIO_PU2, HAL_LL_TIM2_BASE_ADDR, HAL_LL_ALTERNATE_FUNCTION_4, hal_ll_tim_module_num( TIM_MODULE_2 ), HAL_LL_TIM_PIN_A},
    #endif
    #ifdef TIM2_CH1_PD1_AF4
    {GPIO_PD1, HAL_LL_TIM2_BASE_ADDR, HAL_LL_ALTERNATE_FUNCTION_4, hal_ll_tim_module_num( TIM_MODULE_2 ), HAL_LL_TIM_PIN_B},
    #endif
    #ifdef TIM2_CH1_PU4_AF4
    {GPIO_PU4, HAL_LL_TIM2_BASE_ADDR, HAL_LL_ALTERNATE_FUNCTION_4, hal_ll_tim_module_num( TIM_MODULE_2 ), HAL_LL_TIM_PIN_B},
    #endif
    #ifdef TIM2_CH2_PC1_AF6
    {GPIO_PC1, HAL_LL_TIM2_BASE_ADDR, HAL_LL_ALTERNATE_FUNCTION_6, hal_ll_tim_module_num( TIM_MODULE_2 ), HAL_LL_TIM_PIN_C},
    #endif
    #ifdef TIM2_CH2_PU2_AF5
    {GPIO_PU2, HAL_LL_TIM2_BASE_ADDR, HAL_LL_ALTERNATE_FUNCTION_5, hal_ll_tim_module_num( TIM_MODULE_2 ), HAL_LL_TIM_PIN_C},
    #endif
    #ifdef TIM3_CH0_PC2_AF5
    {GPIO_PC2, HAL_LL_TIM3_BASE_ADDR, HAL_LL_ALTERNATE_FUNCTION_5, hal_ll_tim_module_num( TIM_MODULE_3 ), HAL_LL_TIM_PIN_A},
    #endif
    #ifdef TIM3_CH0_PE2_AF4
    {GPIO_PE2, HAL_LL_TIM3_BASE_ADDR, HAL_LL_ALTERNATE_FUNCTION_4, hal_ll_tim_module_num( TIM_MODULE_3 ), HAL_LL_TIM_PIN_A},
    #endif
    #ifdef TIM3_CH1_PC3_AF5
    {GPIO_PC3, HAL_LL_TIM3_BASE_ADDR, HAL_LL_ALTERNATE_FUNCTION_5, hal_ll_tim_module_num( TIM_MODULE_3 ), HAL_LL_TIM_PIN_B},
    #endif
    #ifdef TIM3_CH1_PE6_AF4
    {GPIO_PE6, HAL_LL_TIM3_BASE_ADDR, HAL_LL_ALTERNATE_FUNCTION_4, hal_ll_tim_module_num( TIM_MODULE_3 ), HAL_LL_TIM_PIN_B},
    #endif
    #ifdef TIM3_CH2_PC2_AF6
    {GPIO_PC2, HAL_LL_TIM3_BASE_ADDR, HAL_LL_ALTERNATE_FUNCTION_6, hal_ll_tim_module_num( TIM_MODULE_3 ), HAL_LL_TIM_PIN_C},
    #endif
    #ifdef TIM3_CH2_PE2_AF5
    {GPIO_PE2, HAL_LL_TIM3_BASE_ADDR, HAL_LL_ALTERNATE_FUNCTION_5, hal_ll_tim_module_num( TIM_MODULE_3 ), HAL_LL_TIM_PIN_C},
    #endif
    #ifdef TIM4_CH0_PG2_AF4
    {GPIO_PG2, HAL_LL_TIM4_BASE_ADDR, HAL_LL_ALTERNATE_FUNCTION_4, hal_ll_tim_module_num( TIM_MODULE_4 ), HAL_LL_TIM_PIN_A},
    #endif
    #ifdef TIM4_CH1_PG3_AF4
    {GPIO_PG3, HAL_LL_TIM4_BASE_ADDR, HAL_LL_ALTERNATE_FUNCTION_4, hal_ll_tim_module_num( TIM_MODULE_4 ), HAL_LL_TIM_PIN_B},
    #endif
    #ifdef TIM4_CH2_PG2_AF5
    {GPIO_PG2, HAL_LL_TIM4_BASE_ADDR, HAL_LL_ALTERNATE_FUNCTION_5, hal_ll_tim_module_num( TIM_MODULE_4 ), HAL_LL_TIM_PIN_C},
    #endif
    #ifdef TIM5_CH0_PF1_AF4
    {GPIO_PF1, HAL_LL_TIM5_BASE_ADDR, HAL_LL_ALTERNATE_FUNCTION_4, hal_ll_tim_module_num( TIM_MODULE_5 ), HAL_LL_TIM_PIN_A},
    #endif
    #ifdef TIM5_CH0_PN1_AF4
    {GPIO_PN1, HAL_LL_TIM5_BASE_ADDR, HAL_LL_ALTERNATE_FUNCTION_4, hal_ll_tim_module_num( TIM_MODULE_5 ), HAL_LL_TIM_PIN_A},
    #endif
    #ifdef TIM5_CH2_PF1_AF5
    {GPIO_PF1, HAL_LL_TIM5_BASE_ADDR, HAL_LL_ALTERNATE_FUNCTION_5, hal_ll_tim_module_num( TIM_MODULE_5 ), HAL_LL_TIM_PIN_C},
    #endif
    #ifdef TIM5_CH2_PN1_AF5
    {GPIO_PN1, HAL_LL_TIM5_BASE_ADDR, HAL_LL_ALTERNATE_FUNCTION_5, hal_ll_tim_module_num( TIM_MODULE_5 ), HAL_LL_TIM_PIN_C},
    #endif

    { HAL_LL_PIN_NC, HAL_LL_MODULE_ERROR, HAL_LL_PIN_NC, HAL_LL_PIN_NC, HAL_LL_PIN_NC }
};

#ifdef __cplusplus
}
#endif

#endif // _HAL_LL_TIM_PIN_MAP_H_
// ------------------------------------------------------------------------- END
