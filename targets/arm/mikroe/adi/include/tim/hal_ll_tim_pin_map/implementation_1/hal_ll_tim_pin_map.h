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

typedef enum {
    HAL_LL_TIM_PIN_A = 0,
    HAL_LL_TIM_PIN_B,
    HAL_LL_TIM_PIN_AN,
    HAL_LL_TIM_PIN_BN,
    HAL_LL_TIM_PIN_NONE
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
    #ifdef TIM0_P004_CHA_AF3
    {GPIO_P004, HAL_LL_TIM0_BASE_ADDR, 3, hal_ll_tim_module_num( TIM_MODULE_0 ), HAL_LL_TIM_PIN_A},
    #endif
    #ifdef TIM0_P009_CHAN_AF3
    {GPIO_P009, HAL_LL_TIM0_BASE_ADDR, 3, hal_ll_tim_module_num( TIM_MODULE_0 ), HAL_LL_TIM_PIN_AN},
    #endif
    #ifdef TIM0_P010_CHBN_AF3
    {GPIO_P010, HAL_LL_TIM0_BASE_ADDR, 3, hal_ll_tim_module_num( TIM_MODULE_0 ), HAL_LL_TIM_PIN_BN},
    #endif
    #ifdef TIM0_P011_CHAN_AF3
    {GPIO_P011, HAL_LL_TIM0_BASE_ADDR, 3, hal_ll_tim_module_num( TIM_MODULE_0 ), HAL_LL_TIM_PIN_AN},
    #endif
    #ifdef TIM0_P012_CHBN_AF3
    {GPIO_P012, HAL_LL_TIM0_BASE_ADDR, 3, hal_ll_tim_module_num( TIM_MODULE_0 ), HAL_LL_TIM_PIN_BN},
    #endif
    #ifdef TIM0_P013_CHA_AF2
    {GPIO_P013, HAL_LL_TIM0_BASE_ADDR, 2, hal_ll_tim_module_num( TIM_MODULE_0 ), HAL_LL_TIM_PIN_A},
    #endif
    #ifdef TIM0_P014_CHB_AF2
    {GPIO_P014, HAL_LL_TIM0_BASE_ADDR, 2, hal_ll_tim_module_num( TIM_MODULE_0 ), HAL_LL_TIM_PIN_B},
    #endif
    #ifdef TIM1_P007_CHA_AF2
    {GPIO_P007, HAL_LL_TIM1_BASE_ADDR, 2, hal_ll_tim_module_num( TIM_MODULE_1 ), HAL_LL_TIM_PIN_A},
    #endif
    #ifdef TIM1_P008_CHB_AF2
    {GPIO_P008, HAL_LL_TIM1_BASE_ADDR, 2, hal_ll_tim_module_num( TIM_MODULE_1 ), HAL_LL_TIM_PIN_B},
    #endif
    #ifdef TIM1_P015_CHA_AF3
    {GPIO_P015, HAL_LL_TIM1_BASE_ADDR, 3, hal_ll_tim_module_num( TIM_MODULE_1 ), HAL_LL_TIM_PIN_A},
    #endif
    #ifdef TIM1_P017_CHB_AF3
    {GPIO_P017, HAL_LL_TIM1_BASE_ADDR, 3, hal_ll_tim_module_num( TIM_MODULE_1 ), HAL_LL_TIM_PIN_B},
    #endif
    #ifdef TIM2_P006_CHB_AF3
    {GPIO_P006, HAL_LL_TIM2_BASE_ADDR, 3, hal_ll_tim_module_num( TIM_MODULE_2 ), HAL_LL_TIM_PIN_B},
    #endif
    #ifdef TIM2_P104_CHA_AF2
    {GPIO_P104, HAL_LL_TIM2_BASE_ADDR, 2, hal_ll_tim_module_num( TIM_MODULE_2 ), HAL_LL_TIM_PIN_A},
    #endif
    #ifdef TIM2_P105_CHB_AF2
    {GPIO_P105, HAL_LL_TIM2_BASE_ADDR, 2, hal_ll_tim_module_num( TIM_MODULE_2 ), HAL_LL_TIM_PIN_B},
    #endif
    #ifdef TIM2_P220_CHA_AF3
    {GPIO_P220, HAL_LL_TIM2_BASE_ADDR, 3, hal_ll_tim_module_num( TIM_MODULE_2 ), HAL_LL_TIM_PIN_A},
    #endif
    #ifdef TIM2_P221_CHB_AF3
    {GPIO_P221, HAL_LL_TIM2_BASE_ADDR, 3, hal_ll_tim_module_num( TIM_MODULE_2 ), HAL_LL_TIM_PIN_B},
    #endif
    #ifdef TIM3_P113_CHA_AF1
    {GPIO_P113, HAL_LL_TIM3_BASE_ADDR, 1, hal_ll_tim_module_num( TIM_MODULE_3 ), HAL_LL_TIM_PIN_A},
    #endif
    #ifdef TIM3_P114_CHB_AF1
    {GPIO_P114, HAL_LL_TIM3_BASE_ADDR, 1, hal_ll_tim_module_num( TIM_MODULE_3 ), HAL_LL_TIM_PIN_B},
    #endif
    #ifdef TIM3_P230_CHA_AF3
    {GPIO_P230, HAL_LL_TIM3_BASE_ADDR, 3, hal_ll_tim_module_num( TIM_MODULE_3 ), HAL_LL_TIM_PIN_A},
    #endif
    #ifdef TIM3_P231_CHB_AF3
    {GPIO_P231, HAL_LL_TIM3_BASE_ADDR, 3, hal_ll_tim_module_num( TIM_MODULE_3 ), HAL_LL_TIM_PIN_B},
    #endif

    { HAL_LL_PIN_NC, HAL_LL_MODULE_ERROR, HAL_LL_PIN_NC, HAL_LL_PIN_NC, HAL_LL_PIN_NC }
};

#ifdef __cplusplus
}
#endif

#endif // _HAL_LL_TIM_PIN_MAP_H_
// ------------------------------------------------------------------------- END
