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

/*!< @brief TIM pin structure. */
typedef struct {
    hal_ll_pin_name_t pin;
    hal_ll_base_addr_t base;
    uint8_t af;
    hal_ll_pin_name_t module_index;
    hal_ll_tim_pin_type_t pin_type;
} hal_ll_tim_pin_map_t;

/*!<TIM pins. */
static const hal_ll_tim_pin_map_t hal_ll_tim_pin_map[] = {
    // ===== T32A0 =====
    #ifdef TIM_MODULE_0
    #ifdef TIM0_CHA_PA3_FR4
    { GPIO_PA3, HAL_LL_TIM0_BASE_ADDR, 4, hal_ll_tim_module_num(TIM_MODULE_0), HAL_LL_TIM_PIN_A },
    #endif
    #ifdef TIM0_CHB_PA4_FR4
    { GPIO_PA4, HAL_LL_TIM0_BASE_ADDR, 4, hal_ll_tim_module_num(TIM_MODULE_0), HAL_LL_TIM_PIN_B },
    #endif
    #ifdef TIM0_CHC_PA3_FR5
    { GPIO_PA3, HAL_LL_TIM0_BASE_ADDR, 5, hal_ll_tim_module_num(TIM_MODULE_0), HAL_LL_TIM_PIN_C },
    #endif
    #endif
    // ===== T32A1 =====
    #ifdef TIM_MODULE_1
    #ifdef TIM1_CHA_PF4_FR4
     { GPIO_PF4, HAL_LL_TIM1_BASE_ADDR, 4, hal_ll_tim_module_num(TIM_MODULE_1), HAL_LL_TIM_PIN_A },
     #endif
    #ifdef TIM1_CHB_PV0_FR4
     { GPIO_PV0, HAL_LL_TIM1_BASE_ADDR, 4, hal_ll_tim_module_num(TIM_MODULE_1), HAL_LL_TIM_PIN_B },
    #endif
    #ifdef TIM1_CHC_PF4_FR5
     { GPIO_PF4, HAL_LL_TIM1_BASE_ADDR, 5, hal_ll_tim_module_num(TIM_MODULE_1), HAL_LL_TIM_PIN_C },
     #endif
    #endif
    // ===== T32A2 =====
    #ifdef TIM_MODULE_2
    #ifdef TIM2_CHA_PC1_FR5
     { GPIO_PC1, HAL_LL_TIM2_BASE_ADDR, 5, hal_ll_tim_module_num(TIM_MODULE_2), HAL_LL_TIM_PIN_A },
    #endif
    #ifdef TIM2_CHA_PU2_FR4
     { GPIO_PU2, HAL_LL_TIM2_BASE_ADDR, 4, hal_ll_tim_module_num(TIM_MODULE_2), HAL_LL_TIM_PIN_A },
    #endif
    #ifdef TIM2_CHB_PD1_FR4
     { GPIO_PD1, HAL_LL_TIM2_BASE_ADDR, 4, hal_ll_tim_module_num(TIM_MODULE_2), HAL_LL_TIM_PIN_B },
    #endif
    #ifdef TIM2_CHB_PU4_FR4
     { GPIO_PU4, HAL_LL_TIM2_BASE_ADDR, 4, hal_ll_tim_module_num(TIM_MODULE_2), HAL_LL_TIM_PIN_B },
    #endif
    #ifdef TIM2_CHC_PC1_FR6
     { GPIO_PC1, HAL_LL_TIM2_BASE_ADDR, 6, hal_ll_tim_module_num(TIM_MODULE_2), HAL_LL_TIM_PIN_C },
    #endif
    #ifdef TIM2_CHC_PU2_FR5
     { GPIO_PU2, HAL_LL_TIM2_BASE_ADDR, 5, hal_ll_tim_module_num(TIM_MODULE_2), HAL_LL_TIM_PIN_C },
     #endif
     #endif
    // ===== T32A3 =====
    #ifdef TIM_MODULE_3
    #ifdef TIM3_CHA_PC2_FR5
     { GPIO_PC2, HAL_LL_TIM3_BASE_ADDR, 5, hal_ll_tim_module_num(TIM_MODULE_3), HAL_LL_TIM_PIN_A },
    #endif
    #ifdef TIM3_CHA_PE2_FR4
     { GPIO_PE2, HAL_LL_TIM3_BASE_ADDR, 4, hal_ll_tim_module_num(TIM_MODULE_3), HAL_LL_TIM_PIN_A },
    #endif
    #ifdef TIM3_CHB_PC3_FR5
     { GPIO_PC3, HAL_LL_TIM3_BASE_ADDR, 5, hal_ll_tim_module_num(TIM_MODULE_3), HAL_LL_TIM_PIN_B },
    #endif
    #ifdef TIM3_CHB_PE6_FR4
     { GPIO_PE6, HAL_LL_TIM3_BASE_ADDR, 4, hal_ll_tim_module_num(TIM_MODULE_3), HAL_LL_TIM_PIN_B },
    #endif
    #ifdef TIM3_CHC_PC2_FR6
     { GPIO_PC2, HAL_LL_TIM3_BASE_ADDR, 6, hal_ll_tim_module_num(TIM_MODULE_3), HAL_LL_TIM_PIN_C },
    #endif
    #ifdef TIM3_CHC_PE2_FR5
     { GPIO_PE2, HAL_LL_TIM3_BASE_ADDR, 5, hal_ll_tim_module_num(TIM_MODULE_3), HAL_LL_TIM_PIN_C },
     #endif
     #endif
    // ===== T32A4 =====
    #ifdef TIM_MODULE_4
    #ifdef TIM4_CHA_PG2_FR4
     { GPIO_PG2, HAL_LL_TIM4_BASE_ADDR, 4, hal_ll_tim_module_num(TIM_MODULE_4), HAL_LL_TIM_PIN_A },
    #endif
    #ifdef TIM4_CHB_PG3_FR4
     { GPIO_PG3, HAL_LL_TIM4_BASE_ADDR, 4, hal_ll_tim_module_num(TIM_MODULE_4), HAL_LL_TIM_PIN_B },
    #endif
    #ifdef TIM4_CHC_PG2_FR5
     { GPIO_PG2, HAL_LL_TIM4_BASE_ADDR, 5, hal_ll_tim_module_num(TIM_MODULE_4), HAL_LL_TIM_PIN_C },
     #endif
     #endif
    // ===== T32A5 =====
    #ifdef TIM_MODULE_5
    #ifdef TIM5_CHA_PF1_FR4
     { GPIO_PF1, HAL_LL_TIM5_BASE_ADDR, 4, hal_ll_tim_module_num(TIM_MODULE_5), HAL_LL_TIM_PIN_A },
    #endif
    #ifdef TIM5_CHA_PN1_FR4
     { GPIO_PN1, HAL_LL_TIM5_BASE_ADDR, 4, hal_ll_tim_module_num(TIM_MODULE_5), HAL_LL_TIM_PIN_A },
    #endif
    #ifdef TIM5_CHC_PF1_FR5
     { GPIO_PF1, HAL_LL_TIM5_BASE_ADDR, 5, hal_ll_tim_module_num(TIM_MODULE_5), HAL_LL_TIM_PIN_C },
    #endif
    #ifdef TIM5_CHC_PN1_FR5
     { GPIO_PN1, HAL_LL_TIM5_BASE_ADDR, 5, hal_ll_tim_module_num(TIM_MODULE_5), HAL_LL_TIM_PIN_C },
     #endif
     #endif
    { HAL_LL_PIN_NC, HAL_LL_MODULE_ERROR, HAL_LL_PIN_NC, HAL_LL_PIN_NC, HAL_LL_PIN_NC }
};

#ifdef __cplusplus
}
#endif

#endif // _HAL_LL_TIM_PIN_MAP_H_
// ------------------------------------------------------------------------- END
