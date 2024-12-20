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

/*!< @brief Helper macro for getting adequate module index number */
#define hal_ll_tim_module_num(_module_num) (_module_num)

/*!< @brief Alternate pin function structure. */
typedef struct
{
    hal_ll_pin_name_t pin;
    hal_ll_base_addr_t base;
    hal_ll_channel_t channel;
    uint8_t af;
    hal_ll_pin_name_t module_index;
} hal_ll_tim_pin_map_t;

typedef enum
{
    HAL_LL_TIM_CHANNEL_0 = 0,
    HAL_LL_TIM_CHANNEL_1,
    HAL_LL_TIM_CHANNEL_2
} hal_ll_tim_channel_t;

#ifdef TIM_MODULE_0
#define HAL_LL_TIM0_BASE_ADDRESS (0x4000C000UL)
#endif
#ifdef TIM_MODULE_1
#define HAL_LL_TIM1_BASE_ADDRESS (0x40010000UL)
#endif
#ifdef TIM_MODULE_2
#define HAL_LL_TIM2_BASE_ADDRESS (0x40014000UL)
#endif
#ifdef TIM_MODULE_3
#define HAL_LL_TIM3_BASE_ADDRESS (0x40054000UL)
#endif

#define HAL_LL_ALTERNATE_FUNCTION_MASK  0x0F
#define HAL_LL_SIGNAL_CHANNEL_AB_MASK   0xF0

/*!< @brief TIM pins. */
static const hal_ll_tim_pin_map_t _tim_map[] = {
    #ifdef TIM0_CH0_A_PA0_AFB
    {GPIO_PA0, HAL_LL_TIM0_BASE_ADDRESS, HAL_LL_TIM_CHANNEL_0, 0x01, hal_ll_tim_module_num(TIM_MODULE_0)},
    #endif
    #ifdef TIM0_CH1_A_PA15_AFB
    {GPIO_PA15, HAL_LL_TIM0_BASE_ADDRESS, HAL_LL_TIM_CHANNEL_1, 0x01, hal_ll_tim_module_num(TIM_MODULE_0)},
    #endif
    #ifdef TIM0_CH2_A_PA26_AFB
    {GPIO_PA26, HAL_LL_TIM0_BASE_ADDRESS, HAL_LL_TIM_CHANNEL_2, 0x01, hal_ll_tim_module_num(TIM_MODULE_0)},
    #endif
    #ifdef TIM0_CH0_B_PA1_AFB
    {GPIO_PA1, HAL_LL_TIM0_BASE_ADDRESS, HAL_LL_TIM_CHANNEL_0, 0x11, hal_ll_tim_module_num(TIM_MODULE_0)},
    #endif
    #ifdef TIM0_CH1_B_PA16_AFB
    {GPIO_PA16, HAL_LL_TIM0_BASE_ADDRESS, HAL_LL_TIM_CHANNEL_1, 0x11, hal_ll_tim_module_num(TIM_MODULE_0)},
    #endif
    #ifdef TIM0_CH2_B_PA27_AFB
    {GPIO_PA27, HAL_LL_TIM0_BASE_ADDRESS, HAL_LL_TIM_CHANNEL_2, 0x11, hal_ll_tim_module_num(TIM_MODULE_0)},
    #endif
    #ifdef TIM3_CH2_A_PD21_AFC
    {GPIO_PD21, HAL_LL_TIM3_BASE_ADDRESS, HAL_LL_TIM_CHANNEL_2, 0x02, hal_ll_tim_module_num(TIM_MODULE_3)},
    #endif
    #ifdef TIM3_CH2_B_PD22_AFC
    {GPIO_PD22, HAL_LL_TIM3_BASE_ADDRESS, HAL_LL_TIM_CHANNEL_2, 0x12, hal_ll_tim_module_num(TIM_MODULE_3)},
    #endif
    #ifdef TIM1_CH0_A_PC23_AFB
    {GPIO_PC23, HAL_LL_TIM1_BASE_ADDRESS, HAL_LL_TIM_CHANNEL_0, 0x01, hal_ll_tim_module_num(TIM_MODULE_1)},
    #endif
    #ifdef TIM1_CH1_A_PC26_AFB
    {GPIO_PC26, HAL_LL_TIM1_BASE_ADDRESS, HAL_LL_TIM_CHANNEL_1, 0x01, hal_ll_tim_module_num(TIM_MODULE_1)},
    #endif
    #ifdef TIM1_CH2_A_PC29_AFB
    {GPIO_PC29, HAL_LL_TIM1_BASE_ADDRESS, HAL_LL_TIM_CHANNEL_2, 0x01, hal_ll_tim_module_num(TIM_MODULE_1)},
    #endif
    #ifdef TIM1_CH0_B_PC24_AFB
    {GPIO_PC24, HAL_LL_TIM1_BASE_ADDRESS, HAL_LL_TIM_CHANNEL_0, 0x11, hal_ll_tim_module_num(TIM_MODULE_1)},
    #endif
    #ifdef TIM1_CH1_B_PC27_AFB
    {GPIO_PC27, HAL_LL_TIM1_BASE_ADDRESS, HAL_LL_TIM_CHANNEL_1, 0x11, hal_ll_tim_module_num(TIM_MODULE_1)},
    #endif
    #ifdef TIM1_CH2_B_PC30_AFB
    {GPIO_PC30, HAL_LL_TIM1_BASE_ADDRESS, HAL_LL_TIM_CHANNEL_2, 0x11, hal_ll_tim_module_num(TIM_MODULE_1)},
    #endif
    #ifdef TIM2_CH0_A_PC5_AFB
    {GPIO_PC5, HAL_LL_TIM2_BASE_ADDRESS, HAL_LL_TIM_CHANNEL_0, 0x01, hal_ll_tim_module_num(TIM_MODULE_2)},
    #endif
    #ifdef TIM2_CH1_A_PC8_AFB
    {GPIO_PC8, HAL_LL_TIM2_BASE_ADDRESS, HAL_LL_TIM_CHANNEL_1, 0x01, hal_ll_tim_module_num(TIM_MODULE_2)},
    #endif
    #ifdef TIM2_CH2_A_PC11_AFB
    {GPIO_PC11, HAL_LL_TIM2_BASE_ADDRESS, HAL_LL_TIM_CHANNEL_2, 0x01, hal_ll_tim_module_num(TIM_MODULE_2)},
    #endif
    #ifdef TIM2_CH0_B_PC6_AFB
    {GPIO_PC6, HAL_LL_TIM2_BASE_ADDRESS, HAL_LL_TIM_CHANNEL_0, 0x11, hal_ll_tim_module_num(TIM_MODULE_2)},
    #endif
    #ifdef TIM2_CH1_B_PC9_AFB
    {GPIO_PC9, HAL_LL_TIM2_BASE_ADDRESS, HAL_LL_TIM_CHANNEL_1, 0x11, hal_ll_tim_module_num(TIM_MODULE_2)},
    #endif
    #ifdef TIM2_CH2_B_PC12_AFB
    {GPIO_PC12, HAL_LL_TIM2_BASE_ADDRESS, HAL_LL_TIM_CHANNEL_2, 0x11, hal_ll_tim_module_num(TIM_MODULE_2)},
    #endif
    #ifdef TIM3_CH0_A_PE0_AFB
    {GPIO_PE0, HAL_LL_TIM3_BASE_ADDRESS, HAL_LL_TIM_CHANNEL_0, 0x01, hal_ll_tim_module_num(TIM_MODULE_3)},
    #endif
    #ifdef TIM3_CH1_A_PE3_AFB
    {GPIO_PE3, HAL_LL_TIM3_BASE_ADDRESS, HAL_LL_TIM_CHANNEL_1, 0x01, hal_ll_tim_module_num(TIM_MODULE_3)},
    #endif
    #ifdef TIM3_CH0_B_PE1_AFB
    {GPIO_PE1, HAL_LL_TIM3_BASE_ADDRESS, HAL_LL_TIM_CHANNEL_0, 0x11, hal_ll_tim_module_num(TIM_MODULE_3)},
    #endif
    #ifdef TIM3_CH1_B_PE4_AFB
    {GPIO_PE4, HAL_LL_TIM3_BASE_ADDRESS, HAL_LL_TIM_CHANNEL_1, 0x11, hal_ll_tim_module_num(TIM_MODULE_3)},
    #endif

    { HAL_LL_PIN_NC, HAL_LL_MODULE_ERROR, HAL_LL_CHANNEL_ERROR, HAL_LL_PIN_NC, HAL_LL_PIN_NC }
};

#ifdef __cplusplus
}
#endif

#endif // _HAL_LL_TIM_PIN_MAP_H_
// ------------------------------------------------------------------------- END
