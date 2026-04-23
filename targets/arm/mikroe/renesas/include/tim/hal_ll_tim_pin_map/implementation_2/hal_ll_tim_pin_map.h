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

/*!< @brief TIM pin structure. */
typedef struct {
    hal_ll_pin_name_t pin;
    hal_ll_base_addr_t base;
    uint8_t af;
    hal_ll_pin_name_t module_index;
    uint8_t channel;
} hal_ll_tim_pin_map_t;

/*!< TIM pins. */
static const hal_ll_tim_pin_map_t hal_ll_tim_pin_map[] = {
    #ifdef TIM0_P100_CH1_AF2
    {GPIO_P100, HAL_LL_TIM0_BASE_ADDR, 2, hal_ll_tim_module_num( TIM_MODULE_0 ), 1},
    #endif
    #ifdef TIM0_P105_CH1_AF1
    {GPIO_P105, HAL_LL_TIM0_BASE_ADDR, 1, hal_ll_tim_module_num( TIM_MODULE_0 ), 1},
    #endif
    #ifdef TIM0_P110_CH1_AF1
    {GPIO_P110, HAL_LL_TIM0_BASE_ADDR, 1, hal_ll_tim_module_num( TIM_MODULE_0 ), 1},
    #endif
    #ifdef TIM0_P411_CH1_AF2
    {GPIO_P411, HAL_LL_TIM0_BASE_ADDR, 2, hal_ll_tim_module_num( TIM_MODULE_0 ), 1},
    #endif
    #ifdef TIM0_P104_CH2_AF1
    {GPIO_P104, HAL_LL_TIM0_BASE_ADDR, 1, hal_ll_tim_module_num( TIM_MODULE_0 ), 2},
    #endif
    #ifdef TIM0_P109_CH2_AF1
    {GPIO_P109, HAL_LL_TIM0_BASE_ADDR, 1, hal_ll_tim_module_num( TIM_MODULE_0 ), 2},
    #endif
    #ifdef TIM0_P213_CH2_AF2
    {GPIO_P213, HAL_LL_TIM0_BASE_ADDR, 2, hal_ll_tim_module_num( TIM_MODULE_0 ), 2},
    #endif
    #ifdef TIM0_P410_CH2_AF2
    {GPIO_P410, HAL_LL_TIM0_BASE_ADDR, 2, hal_ll_tim_module_num( TIM_MODULE_0 ), 2},
    #endif
    #ifdef TIM0_P108_CH3_AF2
    {GPIO_P108, HAL_LL_TIM0_BASE_ADDR, 2, hal_ll_tim_module_num( TIM_MODULE_0 ), 3},
    #endif
    #ifdef TIM0_P112_CH3_AF1
    {GPIO_P112, HAL_LL_TIM0_BASE_ADDR, 1, hal_ll_tim_module_num( TIM_MODULE_0 ), 3},
    #endif
    #ifdef TIM0_P212_CH3_AF2
    {GPIO_P212, HAL_LL_TIM0_BASE_ADDR, 2, hal_ll_tim_module_num( TIM_MODULE_0 ), 3},
    #endif
    #ifdef TIM0_P409_CH3_AF2
    {GPIO_P409, HAL_LL_TIM0_BASE_ADDR, 2, hal_ll_tim_module_num( TIM_MODULE_0 ), 3},
    #endif
    #ifdef TIM0_P500_CH3_AF1
    {GPIO_P500, HAL_LL_TIM0_BASE_ADDR, 1, hal_ll_tim_module_num( TIM_MODULE_0 ), 3},
    #endif
    #ifdef TIM0_P100_CH4_AF1
    {GPIO_P100, HAL_LL_TIM0_BASE_ADDR, 1, hal_ll_tim_module_num( TIM_MODULE_0 ), 4},
    #endif
    #ifdef TIM0_P300_CH4_AF2
    {GPIO_P300, HAL_LL_TIM0_BASE_ADDR, 2, hal_ll_tim_module_num( TIM_MODULE_0 ), 4},
    #endif
    #ifdef TIM0_P408_CH4_AF2
    {GPIO_P408, HAL_LL_TIM0_BASE_ADDR, 2, hal_ll_tim_module_num( TIM_MODULE_0 ), 4},
    #endif
    #ifdef TIM0_P501_CH4_AF1
    {GPIO_P501, HAL_LL_TIM0_BASE_ADDR, 1, hal_ll_tim_module_num( TIM_MODULE_0 ), 4},
    #endif
    #ifdef TIM0_P103_CH5_AF1
    {GPIO_P103, HAL_LL_TIM0_BASE_ADDR, 1, hal_ll_tim_module_num( TIM_MODULE_0 ), 5},
    #endif
    #ifdef TIM0_P201_CH5_AF1
    {GPIO_P201, HAL_LL_TIM0_BASE_ADDR, 1, hal_ll_tim_module_num( TIM_MODULE_0 ), 5},
    #endif
    #ifdef TIM0_P302_CH5_AF1
    {GPIO_P302, HAL_LL_TIM0_BASE_ADDR, 1, hal_ll_tim_module_num( TIM_MODULE_0 ), 5},
    #endif
    #ifdef TIM0_P102_CH6_AF1
    {GPIO_P102, HAL_LL_TIM0_BASE_ADDR, 1, hal_ll_tim_module_num( TIM_MODULE_0 ), 6},
    #endif
    #ifdef TIM0_P301_CH6_AF1
    {GPIO_P301, HAL_LL_TIM0_BASE_ADDR, 1, hal_ll_tim_module_num( TIM_MODULE_0 ), 6},
    #endif
    #ifdef TIM0_P101_CH7_AF1
    {GPIO_P101, HAL_LL_TIM0_BASE_ADDR, 1, hal_ll_tim_module_num( TIM_MODULE_0 ), 7},
    #endif
    #ifdef TIM0_P111_CH7_AF1
    {GPIO_P111, HAL_LL_TIM0_BASE_ADDR, 1, hal_ll_tim_module_num( TIM_MODULE_0 ), 7},
    #endif

    { HAL_LL_PIN_NC, HAL_LL_MODULE_ERROR, HAL_LL_PIN_NC, HAL_LL_PIN_NC, HAL_LL_PIN_NC }
};

#ifdef __cplusplus
}
#endif

#endif // _HAL_LL_TIM_PIN_MAP_H_
// ------------------------------------------------------------------------- END
