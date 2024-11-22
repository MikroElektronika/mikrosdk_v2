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
    {PA0, HAL_LL_TIM0_BASE_ADDRESS, HAL_LL_TIM_CHANNEL_0, 0x01, hal_ll_tim_module_num(TIM_MODULE_0)},
    {PA1, HAL_LL_TIM0_BASE_ADDRESS, HAL_LL_TIM_CHANNEL_0, 0x11, hal_ll_tim_module_num(TIM_MODULE_0)},
    {PA15, HAL_LL_TIM0_BASE_ADDRESS, HAL_LL_TIM_CHANNEL_1, 0x01, hal_ll_tim_module_num(TIM_MODULE_0)},
    {PA16, HAL_LL_TIM0_BASE_ADDRESS, HAL_LL_TIM_CHANNEL_1, 0x11, hal_ll_tim_module_num(TIM_MODULE_0)},
    {PA26, HAL_LL_TIM0_BASE_ADDRESS, HAL_LL_TIM_CHANNEL_2, 0x01, hal_ll_tim_module_num(TIM_MODULE_0)},
    {PA27, HAL_LL_TIM0_BASE_ADDRESS, HAL_LL_TIM_CHANNEL_2, 0x11, hal_ll_tim_module_num(TIM_MODULE_0)},
    {PC23, HAL_LL_TIM1_BASE_ADDRESS, HAL_LL_TIM_CHANNEL_0, 0x01, hal_ll_tim_module_num(TIM_MODULE_1)},
    {PC24, HAL_LL_TIM1_BASE_ADDRESS, HAL_LL_TIM_CHANNEL_0, 0x11, hal_ll_tim_module_num(TIM_MODULE_1)},
    {PC26, HAL_LL_TIM1_BASE_ADDRESS, HAL_LL_TIM_CHANNEL_1, 0x01, hal_ll_tim_module_num(TIM_MODULE_1)},
    {PC27, HAL_LL_TIM1_BASE_ADDRESS, HAL_LL_TIM_CHANNEL_1, 0x11, hal_ll_tim_module_num(TIM_MODULE_1)},
    {PC29, HAL_LL_TIM1_BASE_ADDRESS, HAL_LL_TIM_CHANNEL_2, 0x01, hal_ll_tim_module_num(TIM_MODULE_1)},
    {PC30, HAL_LL_TIM1_BASE_ADDRESS, HAL_LL_TIM_CHANNEL_2, 0x11, hal_ll_tim_module_num(TIM_MODULE_1)},
    {PC5, HAL_LL_TIM2_BASE_ADDRESS, HAL_LL_TIM_CHANNEL_0, 0x01, hal_ll_tim_module_num(TIM_MODULE_2)},
    {PC6, HAL_LL_TIM2_BASE_ADDRESS, HAL_LL_TIM_CHANNEL_0, 0x11, hal_ll_tim_module_num(TIM_MODULE_2)},
    {PC8, HAL_LL_TIM2_BASE_ADDRESS, HAL_LL_TIM_CHANNEL_1, 0x01, hal_ll_tim_module_num(TIM_MODULE_2)},
    {PC9, HAL_LL_TIM2_BASE_ADDRESS, HAL_LL_TIM_CHANNEL_1, 0x11, hal_ll_tim_module_num(TIM_MODULE_2)},
    {PC11, HAL_LL_TIM2_BASE_ADDRESS, HAL_LL_TIM_CHANNEL_2, 0x01, hal_ll_tim_module_num(TIM_MODULE_2)},
    {PC12, HAL_LL_TIM2_BASE_ADDRESS, HAL_LL_TIM_CHANNEL_2, 0x11, hal_ll_tim_module_num(TIM_MODULE_2)},
    {PE0, HAL_LL_TIM3_BASE_ADDRESS, HAL_LL_TIM_CHANNEL_0, 0x01, hal_ll_tim_module_num(TIM_MODULE_3)},
    {PE1, HAL_LL_TIM3_BASE_ADDRESS, HAL_LL_TIM_CHANNEL_0, 0x11, hal_ll_tim_module_num(TIM_MODULE_3)},
    {PE3, HAL_LL_TIM3_BASE_ADDRESS, HAL_LL_TIM_CHANNEL_1, 0x01, hal_ll_tim_module_num(TIM_MODULE_3)},
    {PE4, HAL_LL_TIM3_BASE_ADDRESS, HAL_LL_TIM_CHANNEL_1, 0x11, hal_ll_tim_module_num(TIM_MODULE_3)},
    {PD21, HAL_LL_TIM3_BASE_ADDRESS, HAL_LL_TIM_CHANNEL_2, 0x02, hal_ll_tim_module_num(TIM_MODULE_3)},
    {PD22, HAL_LL_TIM3_BASE_ADDRESS, HAL_LL_TIM_CHANNEL_2, 0x12, hal_ll_tim_module_num(TIM_MODULE_3)},

    { HAL_LL_PIN_NC, HAL_LL_MODULE_ERROR, HAL_LL_CHANNEL_ERROR, HAL_LL_PIN_NC, HAL_LL_PIN_NC }
};

#ifdef __cplusplus
}
#endif

#endif // _HAL_LL_TIM_PIN_MAP_H_
// ------------------------------------------------------------------------- END
