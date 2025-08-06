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
static const hal_ll_base_addr_t HAL_LL_TIM0_BASE_ADDR = 0x40078000UL;
#endif
#ifdef TIM_MODULE_1
static const hal_ll_base_addr_t HAL_LL_TIM1_BASE_ADDR = 0x40078100UL;
#endif
#ifdef TIM_MODULE_2
static const hal_ll_base_addr_t HAL_LL_TIM2_BASE_ADDR = 0x40078200UL;
#endif
#ifdef TIM_MODULE_3
static const hal_ll_base_addr_t HAL_LL_TIM3_BASE_ADDR = 0x40078300UL;
#endif
#ifdef TIM_MODULE_4
static const hal_ll_base_addr_t HAL_LL_TIM4_BASE_ADDR = 0x40078400UL;
#endif
#ifdef TIM_MODULE_5
static const hal_ll_base_addr_t HAL_LL_TIM5_BASE_ADDR = 0x40078500UL;
#endif
#ifdef TIM_MODULE_6
static const hal_ll_base_addr_t HAL_LL_TIM6_BASE_ADDR = 0x40078600UL;
#endif
#ifdef TIM_MODULE_7
static const hal_ll_base_addr_t HAL_LL_TIM7_BASE_ADDR = 0x40078700UL;
#endif
#ifdef TIM_MODULE_8
static const hal_ll_base_addr_t HAL_LL_TIM8_BASE_ADDR = 0x40078800UL;
#endif
#ifdef TIM_MODULE_9
static const hal_ll_base_addr_t HAL_LL_TIM9_BASE_ADDR = 0x40078900UL;
#endif
#ifdef TIM_MODULE_10
static const hal_ll_base_addr_t HAL_LL_TIM10_BASE_ADDR = 0x40078A00UL;
#endif
#ifdef TIM_MODULE_11
static const hal_ll_base_addr_t HAL_LL_TIM11_BASE_ADDR = 0x40078B00UL;
#endif
#ifdef TIM_MODULE_12
static const hal_ll_base_addr_t HAL_LL_TIM12_BASE_ADDR = 0x40078C00UL;
#endif
#ifdef TIM_MODULE_13
static const hal_ll_base_addr_t HAL_LL_TIM13_BASE_ADDR = 0x40078D00UL;
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

/*!< TIM pins. */
static const hal_ll_tim_pin_map_t hal_ll_tim_pin_map[] = {
    #ifdef TIM0_P108_CHB_AF3
    {GPIO_P108, HAL_LL_TIM0_BASE_ADDR, 3, hal_ll_tim_module_num( TIM_MODULE_0 ), HAL_LL_TIM_PIN_B},
    #endif
    #ifdef TIM0_P212_CHB_AF3
    {GPIO_P212, HAL_LL_TIM0_BASE_ADDR, 3, hal_ll_tim_module_num( TIM_MODULE_0 ), HAL_LL_TIM_PIN_B},
    #endif
    #ifdef TIM0_P213_CHA_AF3
    {GPIO_P213, HAL_LL_TIM0_BASE_ADDR, 3, hal_ll_tim_module_num( TIM_MODULE_0 ), HAL_LL_TIM_PIN_A},
    #endif
    #ifdef TIM0_P300_CHA_AF3
    {GPIO_P300, HAL_LL_TIM0_BASE_ADDR, 3, hal_ll_tim_module_num( TIM_MODULE_0 ), HAL_LL_TIM_PIN_A},
    #endif
    #ifdef TIM1_P109_CHA_AF3
    {GPIO_P109, HAL_LL_TIM1_BASE_ADDR, 3, hal_ll_tim_module_num( TIM_MODULE_1 ), HAL_LL_TIM_PIN_A},
    #endif
    #ifdef TIM1_P110_CHB_AF3
    {GPIO_P110, HAL_LL_TIM1_BASE_ADDR, 3, hal_ll_tim_module_num( TIM_MODULE_1 ), HAL_LL_TIM_PIN_B},
    #endif
    #ifdef TIM2_P102_CHB_AF3
    {GPIO_P102, HAL_LL_TIM2_BASE_ADDR, 3, hal_ll_tim_module_num( TIM_MODULE_2 ), HAL_LL_TIM_PIN_B},
    #endif
    #ifdef TIM3_P111_CHA_AF3
    {GPIO_P111, HAL_LL_TIM3_BASE_ADDR, 3, hal_ll_tim_module_num( TIM_MODULE_3 ), HAL_LL_TIM_PIN_A},
    #endif
    #ifdef TIM3_P112_CHB_AF3
    {GPIO_P112, HAL_LL_TIM3_BASE_ADDR, 3, hal_ll_tim_module_num( TIM_MODULE_3 ), HAL_LL_TIM_PIN_B},
    #endif
    #ifdef TIM4_P301_CHB_AF3
    {GPIO_P301, HAL_LL_TIM4_BASE_ADDR, 3, hal_ll_tim_module_num( TIM_MODULE_4 ), HAL_LL_TIM_PIN_B},
    #endif
    #ifdef TIM5_P100_CHB_AF3
    {GPIO_P100, HAL_LL_TIM5_BASE_ADDR, 3, hal_ll_tim_module_num( TIM_MODULE_5 ), HAL_LL_TIM_PIN_B},
    #endif
    #ifdef TIM5_P101_CHA_AF3
    {GPIO_P101, HAL_LL_TIM5_BASE_ADDR, 3, hal_ll_tim_module_num( TIM_MODULE_5 ), HAL_LL_TIM_PIN_A},
    #endif
    #ifdef TIM5_P408_CHB_AF3
    {GPIO_P408, HAL_LL_TIM5_BASE_ADDR, 3, hal_ll_tim_module_num( TIM_MODULE_5 ), HAL_LL_TIM_PIN_B},
    #endif
    #ifdef TIM0_P106_CHB_AF3
    {GPIO_P106, HAL_LL_TIM0_BASE_ADDR, 3, hal_ll_tim_module_num( TIM_MODULE_0 ), HAL_LL_TIM_PIN_B},
    #endif
    #ifdef TIM0_P107_CHA_AF3
    {GPIO_P107, HAL_LL_TIM0_BASE_ADDR, 3, hal_ll_tim_module_num( TIM_MODULE_0 ), HAL_LL_TIM_PIN_A},
    #endif
    #ifdef TIM1_P104_CHB_AF3
    {GPIO_P104, HAL_LL_TIM1_BASE_ADDR, 3, hal_ll_tim_module_num( TIM_MODULE_1 ), HAL_LL_TIM_PIN_B},
    #endif
    #ifdef TIM1_P105_CHA_AF3
    {GPIO_P105, HAL_LL_TIM1_BASE_ADDR, 3, hal_ll_tim_module_num( TIM_MODULE_1 ), HAL_LL_TIM_PIN_A},
    #endif
    #ifdef TIM2_P103_CHA_AF3
    {GPIO_P103, HAL_LL_TIM2_BASE_ADDR, 3, hal_ll_tim_module_num( TIM_MODULE_2 ), HAL_LL_TIM_PIN_A},
    #endif
    #ifdef TIM2_P113_CHA_AF3
    {GPIO_P113, HAL_LL_TIM2_BASE_ADDR, 3, hal_ll_tim_module_num( TIM_MODULE_2 ), HAL_LL_TIM_PIN_A},
    #endif
    #ifdef TIM2_P500_CHA_AF3
    {GPIO_P500, HAL_LL_TIM2_BASE_ADDR, 3, hal_ll_tim_module_num( TIM_MODULE_2 ), HAL_LL_TIM_PIN_A},
    #endif
    #ifdef TIM2_P501_CHB_AF3
    {GPIO_P501, HAL_LL_TIM2_BASE_ADDR, 3, hal_ll_tim_module_num( TIM_MODULE_2 ), HAL_LL_TIM_PIN_B},
    #endif
    #ifdef TIM3_P502_CHB_AF3
    {GPIO_P502, HAL_LL_TIM3_BASE_ADDR, 3, hal_ll_tim_module_num( TIM_MODULE_3 ), HAL_LL_TIM_PIN_B},
    #endif
    #ifdef TIM4_P204_CHB_AF3
    {GPIO_P204, HAL_LL_TIM4_BASE_ADDR, 3, hal_ll_tim_module_num( TIM_MODULE_4 ), HAL_LL_TIM_PIN_B},
    #endif
    #ifdef TIM4_P205_CHA_AF3
    {GPIO_P205, HAL_LL_TIM4_BASE_ADDR, 3, hal_ll_tim_module_num( TIM_MODULE_4 ), HAL_LL_TIM_PIN_A},
    #endif
    #ifdef TIM4_P302_CHA_AF3
    {GPIO_P302, HAL_LL_TIM4_BASE_ADDR, 3, hal_ll_tim_module_num( TIM_MODULE_4 ), HAL_LL_TIM_PIN_A},
    #endif
    #ifdef TIM5_P409_CHA_AF3
    {GPIO_P409, HAL_LL_TIM5_BASE_ADDR, 3, hal_ll_tim_module_num( TIM_MODULE_5 ), HAL_LL_TIM_PIN_A},
    #endif
    #ifdef TIM6_P400_CHA_AF3
    {GPIO_P400, HAL_LL_TIM6_BASE_ADDR, 3, hal_ll_tim_module_num( TIM_MODULE_6 ), HAL_LL_TIM_PIN_A},
    #endif
    #ifdef TIM6_P401_CHB_AF3
    {GPIO_P401, HAL_LL_TIM6_BASE_ADDR, 3, hal_ll_tim_module_num( TIM_MODULE_6 ), HAL_LL_TIM_PIN_B},
    #endif
    #ifdef TIM6_P410_CHB_AF3
    {GPIO_P410, HAL_LL_TIM6_BASE_ADDR, 3, hal_ll_tim_module_num( TIM_MODULE_6 ), HAL_LL_TIM_PIN_B},
    #endif
    #ifdef TIM6_P411_CHA_AF3
    {GPIO_P411, HAL_LL_TIM6_BASE_ADDR, 3, hal_ll_tim_module_num( TIM_MODULE_6 ), HAL_LL_TIM_PIN_A},
    #endif
    #ifdef TIM7_P303_CHB_AF3
    {GPIO_P303, HAL_LL_TIM7_BASE_ADDR, 3, hal_ll_tim_module_num( TIM_MODULE_7 ), HAL_LL_TIM_PIN_B},
    #endif
    #ifdef TIM7_P304_CHA_AF3
    {GPIO_P304, HAL_LL_TIM7_BASE_ADDR, 3, hal_ll_tim_module_num( TIM_MODULE_7 ), HAL_LL_TIM_PIN_A},
    #endif
    #ifdef TIM0_P414_CHB_AF3
    {GPIO_P414, HAL_LL_TIM0_BASE_ADDR, 3, hal_ll_tim_module_num( TIM_MODULE_0 ), HAL_LL_TIM_PIN_B},
    #endif
    #ifdef TIM0_P415_CHA_AF3
    {GPIO_P415, HAL_LL_TIM0_BASE_ADDR, 3, hal_ll_tim_module_num( TIM_MODULE_0 ), HAL_LL_TIM_PIN_A},
    #endif
    #ifdef TIM1_P405_CHA_AF3
    {GPIO_P405, HAL_LL_TIM1_BASE_ADDR, 3, hal_ll_tim_module_num( TIM_MODULE_1 ), HAL_LL_TIM_PIN_A},
    #endif
    #ifdef TIM1_P406_CHB_AF3
    {GPIO_P406, HAL_LL_TIM1_BASE_ADDR, 3, hal_ll_tim_module_num( TIM_MODULE_1 ), HAL_LL_TIM_PIN_B},
    #endif
    #ifdef TIM2_P114_CHB_AF3
    {GPIO_P114, HAL_LL_TIM2_BASE_ADDR, 3, hal_ll_tim_module_num( TIM_MODULE_2 ), HAL_LL_TIM_PIN_B},
    #endif
    #ifdef TIM3_P403_CHA_AF3
    {GPIO_P403, HAL_LL_TIM3_BASE_ADDR, 3, hal_ll_tim_module_num( TIM_MODULE_3 ), HAL_LL_TIM_PIN_A},
    #endif
    #ifdef TIM3_P404_CHB_AF3
    {GPIO_P404, HAL_LL_TIM3_BASE_ADDR, 3, hal_ll_tim_module_num( TIM_MODULE_3 ), HAL_LL_TIM_PIN_B},
    #endif
    #ifdef TIM4_P115_CHA_AF3
    {GPIO_P115, HAL_LL_TIM4_BASE_ADDR, 3, hal_ll_tim_module_num( TIM_MODULE_4 ), HAL_LL_TIM_PIN_A},
    #endif
    #ifdef TIM4_P608_CHB_AF3
    {GPIO_P608, HAL_LL_TIM4_BASE_ADDR, 3, hal_ll_tim_module_num( TIM_MODULE_4 ), HAL_LL_TIM_PIN_B},
    #endif
    #ifdef TIM5_P202_CHB_AF3
    {GPIO_P202, HAL_LL_TIM5_BASE_ADDR, 3, hal_ll_tim_module_num( TIM_MODULE_5 ), HAL_LL_TIM_PIN_B},
    #endif
    #ifdef TIM5_P203_CHA_AF3
    {GPIO_P203, HAL_LL_TIM5_BASE_ADDR, 3, hal_ll_tim_module_num( TIM_MODULE_5 ), HAL_LL_TIM_PIN_A},
    #endif
    #ifdef TIM5_P609_CHA_AF3
    {GPIO_P609, HAL_LL_TIM5_BASE_ADDR, 3, hal_ll_tim_module_num( TIM_MODULE_5 ), HAL_LL_TIM_PIN_A},
    #endif
    #ifdef TIM5_P610_CHB_AF3
    {GPIO_P610, HAL_LL_TIM5_BASE_ADDR, 3, hal_ll_tim_module_num( TIM_MODULE_5 ), HAL_LL_TIM_PIN_B},
    #endif
    #ifdef TIM6_P600_CHB_AF3
    {GPIO_P600, HAL_LL_TIM6_BASE_ADDR, 3, hal_ll_tim_module_num( TIM_MODULE_6 ), HAL_LL_TIM_PIN_B},
    #endif
    #ifdef TIM6_P601_CHA_AF3
    {GPIO_P601, HAL_LL_TIM6_BASE_ADDR, 3, hal_ll_tim_module_num( TIM_MODULE_6 ), HAL_LL_TIM_PIN_A},
    #endif
    #ifdef TIM7_P602_CHB_AF3
    {GPIO_P602, HAL_LL_TIM7_BASE_ADDR, 3, hal_ll_tim_module_num( TIM_MODULE_7 ), HAL_LL_TIM_PIN_B},
    #endif
    #ifdef TIM7_P603_CHA_AF3
    {GPIO_P603, HAL_LL_TIM7_BASE_ADDR, 3, hal_ll_tim_module_num( TIM_MODULE_7 ), HAL_LL_TIM_PIN_A},
    #endif

    { HAL_LL_PIN_NC, HAL_LL_MODULE_ERROR, HAL_LL_PIN_NC, HAL_LL_PIN_NC, HAL_LL_PIN_NC }
};

#ifdef __cplusplus
}
#endif

#endif // _HAL_LL_TIM_PIN_MAP_H_
// ------------------------------------------------------------------------- END
