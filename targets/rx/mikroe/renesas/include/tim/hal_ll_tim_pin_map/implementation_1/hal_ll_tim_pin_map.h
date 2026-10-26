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
    #ifdef TIM0_P701_CHA_AF20
    {GPIO_P701, HAL_LL_TIM0_BASE_ADDR, 20, hal_ll_tim_module_num( TIM_MODULE_0 ), HAL_LL_TIM_PIN_A},
    #endif
    #ifdef TIM0_P704_CHB_AF20
    {GPIO_P704, HAL_LL_TIM0_BASE_ADDR, 20, hal_ll_tim_module_num( TIM_MODULE_0 ), HAL_LL_TIM_PIN_B},
    #endif
    #ifdef TIM0_PD01_CHB_AF21
    {GPIO_PD01, HAL_LL_TIM0_BASE_ADDR, 21, hal_ll_tim_module_num( TIM_MODULE_0 ), HAL_LL_TIM_PIN_B},
    #endif
    #ifdef TIM0_PD02_CHA_AF21
    {GPIO_PD02, HAL_LL_TIM0_BASE_ADDR, 21, hal_ll_tim_module_num( TIM_MODULE_0 ), HAL_LL_TIM_PIN_A},
    #endif
    #ifdef TIM0_PD06_CHB_AF20
    {GPIO_PD06, HAL_LL_TIM0_BASE_ADDR, 20, hal_ll_tim_module_num( TIM_MODULE_0 ), HAL_LL_TIM_PIN_B},
    #endif
    #ifdef TIM0_PD07_CHA_AF20
    {GPIO_PD07, HAL_LL_TIM0_BASE_ADDR, 20, hal_ll_tim_module_num( TIM_MODULE_0 ), HAL_LL_TIM_PIN_A},
    #endif
    #ifdef TIM1_P702_CHA_AF20
    {GPIO_P702, HAL_LL_TIM1_BASE_ADDR, 20, hal_ll_tim_module_num( TIM_MODULE_1 ), HAL_LL_TIM_PIN_A},
    #endif
    #ifdef TIM1_P705_CHB_AF20
    {GPIO_P705, HAL_LL_TIM1_BASE_ADDR, 20, hal_ll_tim_module_num( TIM_MODULE_1 ), HAL_LL_TIM_PIN_B},
    #endif
    #ifdef TIM1_PB07_CHB_AF20
    {GPIO_PB07, HAL_LL_TIM1_BASE_ADDR, 20, hal_ll_tim_module_num( TIM_MODULE_1 ), HAL_LL_TIM_PIN_B},
    #endif
    #ifdef TIM1_PD00_CHA_AF21
    {GPIO_PD00, HAL_LL_TIM1_BASE_ADDR, 21, hal_ll_tim_module_num( TIM_MODULE_1 ), HAL_LL_TIM_PIN_A},
    #endif
    #ifdef TIM1_PD04_CHB_AF20
    {GPIO_PD04, HAL_LL_TIM1_BASE_ADDR, 20, hal_ll_tim_module_num( TIM_MODULE_1 ), HAL_LL_TIM_PIN_B},
    #endif
    #ifdef TIM1_PD05_CHA_AF20
    {GPIO_PD05, HAL_LL_TIM1_BASE_ADDR, 20, hal_ll_tim_module_num( TIM_MODULE_1 ), HAL_LL_TIM_PIN_A},
    #endif
    #ifdef TIM2_P703_CHA_AF20
    {GPIO_P703, HAL_LL_TIM2_BASE_ADDR, 20, hal_ll_tim_module_num( TIM_MODULE_2 ), HAL_LL_TIM_PIN_A},
    #endif
    #ifdef TIM2_P706_CHB_AF20
    {GPIO_P706, HAL_LL_TIM2_BASE_ADDR, 20, hal_ll_tim_module_num( TIM_MODULE_2 ), HAL_LL_TIM_PIN_B},
    #endif
    #ifdef TIM2_PB05_CHB_AF20
    {GPIO_PB05, HAL_LL_TIM2_BASE_ADDR, 20, hal_ll_tim_module_num( TIM_MODULE_2 ), HAL_LL_TIM_PIN_B},
    #endif
    #ifdef TIM2_PB06_CHA_AF20
    {GPIO_PB06, HAL_LL_TIM2_BASE_ADDR, 20, hal_ll_tim_module_num( TIM_MODULE_2 ), HAL_LL_TIM_PIN_A},
    #endif
    #ifdef TIM2_PD02_CHB_AF20
    {GPIO_PD02, HAL_LL_TIM2_BASE_ADDR, 20, hal_ll_tim_module_num( TIM_MODULE_2 ), HAL_LL_TIM_PIN_B},
    #endif
    #ifdef TIM2_PD03_CHA_AF20
    {GPIO_PD03, HAL_LL_TIM2_BASE_ADDR, 20, hal_ll_tim_module_num( TIM_MODULE_2 ), HAL_LL_TIM_PIN_A},
    #endif
    #ifdef TIM3_P100_CHA_AF20
    {GPIO_P100, HAL_LL_TIM3_BASE_ADDR, 20, hal_ll_tim_module_num( TIM_MODULE_3 ), HAL_LL_TIM_PIN_A},
    #endif
    #ifdef TIM3_P101_CHB_AF20
    {GPIO_P101, HAL_LL_TIM3_BASE_ADDR, 20, hal_ll_tim_module_num( TIM_MODULE_3 ), HAL_LL_TIM_PIN_B},
    #endif
    #ifdef TIM3_P302_CHA_AF20
    {GPIO_P302, HAL_LL_TIM3_BASE_ADDR, 20, hal_ll_tim_module_num( TIM_MODULE_3 ), HAL_LL_TIM_PIN_A},
    #endif
    #ifdef TIM3_P303_CHB_AF20
    {GPIO_P303, HAL_LL_TIM3_BASE_ADDR, 20, hal_ll_tim_module_num( TIM_MODULE_3 ), HAL_LL_TIM_PIN_B},
    #endif
    #ifdef TIM3_PB05_CHB_AF21
    {GPIO_PB05, HAL_LL_TIM3_BASE_ADDR, 21, hal_ll_tim_module_num( TIM_MODULE_3 ), HAL_LL_TIM_PIN_B},
    #endif
    #ifdef TIM3_PB06_CHA_AF21
    {GPIO_PB06, HAL_LL_TIM3_BASE_ADDR, 21, hal_ll_tim_module_num( TIM_MODULE_3 ), HAL_LL_TIM_PIN_A},
    #endif
    #ifdef TIM3_PD00_CHB_AF20
    {GPIO_PD00, HAL_LL_TIM3_BASE_ADDR, 20, hal_ll_tim_module_num( TIM_MODULE_3 ), HAL_LL_TIM_PIN_B},
    #endif
    #ifdef TIM3_PD01_CHA_AF20
    {GPIO_PD01, HAL_LL_TIM3_BASE_ADDR, 20, hal_ll_tim_module_num( TIM_MODULE_3 ), HAL_LL_TIM_PIN_A},
    #endif
    #ifdef TIM3_PD06_CHB_AF21
    {GPIO_PD06, HAL_LL_TIM3_BASE_ADDR, 21, hal_ll_tim_module_num( TIM_MODULE_3 ), HAL_LL_TIM_PIN_B},
    #endif
    #ifdef TIM3_PD07_CHA_AF21
    {GPIO_PD07, HAL_LL_TIM3_BASE_ADDR, 21, hal_ll_tim_module_num( TIM_MODULE_3 ), HAL_LL_TIM_PIN_A},
    #endif
    #ifdef TIM3_PE05_CHA_AF20
    {GPIO_PE05, HAL_LL_TIM3_BASE_ADDR, 20, hal_ll_tim_module_num( TIM_MODULE_3 ), HAL_LL_TIM_PIN_A},
    #endif
    #ifdef TIM4_P701_CHA_AF21
    {GPIO_P701, HAL_LL_TIM4_BASE_ADDR, 21, hal_ll_tim_module_num( TIM_MODULE_4 ), HAL_LL_TIM_PIN_A},
    #endif
    #ifdef TIM4_P704_CHB_AF21
    {GPIO_P704, HAL_LL_TIM4_BASE_ADDR, 21, hal_ll_tim_module_num( TIM_MODULE_4 ), HAL_LL_TIM_PIN_B},
    #endif
    #ifdef TIM4_P902_CHB_AF20
    {GPIO_P902, HAL_LL_TIM4_BASE_ADDR, 20, hal_ll_tim_module_num( TIM_MODULE_4 ), HAL_LL_TIM_PIN_B},
    #endif
    #ifdef TIM4_P905_CHA_AF20
    {GPIO_P905, HAL_LL_TIM4_BASE_ADDR, 20, hal_ll_tim_module_num( TIM_MODULE_4 ), HAL_LL_TIM_PIN_A},
    #endif
    #ifdef TIM5_P702_CHA_AF21
    {GPIO_P702, HAL_LL_TIM5_BASE_ADDR, 21, hal_ll_tim_module_num( TIM_MODULE_5 ), HAL_LL_TIM_PIN_A},
    #endif
    #ifdef TIM5_P705_CHB_AF21
    {GPIO_P705, HAL_LL_TIM5_BASE_ADDR, 21, hal_ll_tim_module_num( TIM_MODULE_5 ), HAL_LL_TIM_PIN_B},
    #endif
    #ifdef TIM5_P901_CHB_AF20
    {GPIO_P901, HAL_LL_TIM5_BASE_ADDR, 20, hal_ll_tim_module_num( TIM_MODULE_5 ), HAL_LL_TIM_PIN_B},
    #endif
    #ifdef TIM5_P904_CHA_AF20
    {GPIO_P904, HAL_LL_TIM5_BASE_ADDR, 20, hal_ll_tim_module_num( TIM_MODULE_5 ), HAL_LL_TIM_PIN_A},
    #endif
    #ifdef TIM6_P703_CHA_AF21
    {GPIO_P703, HAL_LL_TIM6_BASE_ADDR, 21, hal_ll_tim_module_num( TIM_MODULE_6 ), HAL_LL_TIM_PIN_A},
    #endif
    #ifdef TIM6_P706_CHB_AF21
    {GPIO_P706, HAL_LL_TIM6_BASE_ADDR, 21, hal_ll_tim_module_num( TIM_MODULE_6 ), HAL_LL_TIM_PIN_B},
    #endif
    #ifdef TIM6_P900_CHB_AF20
    {GPIO_P900, HAL_LL_TIM6_BASE_ADDR, 20, hal_ll_tim_module_num( TIM_MODULE_6 ), HAL_LL_TIM_PIN_B},
    #endif
    #ifdef TIM6_P903_CHA_AF20
    {GPIO_P903, HAL_LL_TIM6_BASE_ADDR, 20, hal_ll_tim_module_num( TIM_MODULE_6 ), HAL_LL_TIM_PIN_A},
    #endif
    #ifdef TIM7_P302_CHA_AF21
    {GPIO_P302, HAL_LL_TIM7_BASE_ADDR, 21, hal_ll_tim_module_num( TIM_MODULE_7 ), HAL_LL_TIM_PIN_A},
    #endif
    #ifdef TIM7_P303_CHB_AF21
    {GPIO_P303, HAL_LL_TIM7_BASE_ADDR, 21, hal_ll_tim_module_num( TIM_MODULE_7 ), HAL_LL_TIM_PIN_B},
    #endif
    #ifdef TIM7_P902_CHB_AF21
    {GPIO_P902, HAL_LL_TIM7_BASE_ADDR, 21, hal_ll_tim_module_num( TIM_MODULE_7 ), HAL_LL_TIM_PIN_B},
    #endif
    #ifdef TIM7_P905_CHA_AF21
    {GPIO_P905, HAL_LL_TIM7_BASE_ADDR, 21, hal_ll_tim_module_num( TIM_MODULE_7 ), HAL_LL_TIM_PIN_A},
    #endif
    #ifdef TIM7_PB01_CHB_AF21
    {GPIO_PB01, HAL_LL_TIM7_BASE_ADDR, 21, hal_ll_tim_module_num( TIM_MODULE_7 ), HAL_LL_TIM_PIN_B},
    #endif
    #ifdef TIM7_PB02_CHA_AF21
    {GPIO_PB02, HAL_LL_TIM7_BASE_ADDR, 21, hal_ll_tim_module_num( TIM_MODULE_7 ), HAL_LL_TIM_PIN_A},
    #endif
    #ifdef TIM7_PD03_CHB_AF23
    {GPIO_PD03, HAL_LL_TIM7_BASE_ADDR, 23, hal_ll_tim_module_num( TIM_MODULE_7 ), HAL_LL_TIM_PIN_B},
    #endif
    #ifdef TIM7_PD05_CHA_AF23
    {GPIO_PD05, HAL_LL_TIM7_BASE_ADDR, 23, hal_ll_tim_module_num( TIM_MODULE_7 ), HAL_LL_TIM_PIN_A},
    #endif

    { HAL_LL_PIN_NC, HAL_LL_MODULE_ERROR, HAL_LL_PIN_NC, HAL_LL_PIN_NC, HAL_LL_PIN_NC }
};

#ifdef __cplusplus
}
#endif

#endif // _HAL_LL_TIM_PIN_MAP_H_
// ------------------------------------------------------------------------- END
