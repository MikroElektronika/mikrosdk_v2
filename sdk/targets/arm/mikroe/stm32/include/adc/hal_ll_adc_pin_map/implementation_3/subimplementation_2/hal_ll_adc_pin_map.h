/****************************************************************************
**
** Copyright (C) 2023 MikroElektronika d.o.o.
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
 * @file  hal_ll_adc_pin_map.h
 * @brief Header file containing symbolic pin name definitions.
 */

#ifndef _HAL_LL_ADC_PIN_MAP_H_
#define _HAL_LL_ADC_PIN_MAP_H_

#ifdef __cplusplus
extern "C"{
#endif

#include "hal_ll_pin_names.h"

/*!< @brief Helper macro for getting adequate module index number */
#define hal_ll_adc_module_num(_module_num) (_module_num - 1)

/**
 * ADC channels.
 */
typedef enum
{
    HAL_LL_ADC_CHANNEL_0 = 0,
    HAL_LL_ADC_CHANNEL_1,
    HAL_LL_ADC_CHANNEL_2,
    HAL_LL_ADC_CHANNEL_3,
    HAL_LL_ADC_CHANNEL_4,
    HAL_LL_ADC_CHANNEL_5,
    HAL_LL_ADC_CHANNEL_6,
    HAL_LL_ADC_CHANNEL_7,
    HAL_LL_ADC_CHANNEL_8,
    HAL_LL_ADC_CHANNEL_9,
    HAL_LL_ADC_CHANNEL_10,
    HAL_LL_ADC_CHANNEL_11,
    HAL_LL_ADC_CHANNEL_12,
    HAL_LL_ADC_CHANNEL_13,
    HAL_LL_ADC_CHANNEL_14,
    HAL_LL_ADC_CHANNEL_15,
    HAL_LL_ADC_CHANNEL_16,
    HAL_LL_ADC_CHANNEL_17,
    HAL_LL_ADC_CHANNEL_18,
    HAL_LL_ADC_CHANNEL_19,
    HAL_LL_ADC_CHANNEL_20,
    HAL_LL_ADC_CHANNEL_21,
    HAL_LL_ADC_CHANNEL_22,
    HAL_LL_ADC_CHANNEL_23,
    HAL_LL_ADC_CHANNEL_24,
    HAL_LL_ADC_CHANNEL_25,
    HAL_LL_ADC_CHANNEL_26,
    HAL_LL_ADC_CHANNEL_27,
    HAL_LL_ADC_CHANNEL_28,
    HAL_LL_ADC_CHANNEL_29,
    HAL_LL_ADC_CHANNEL_30,
    HAL_LL_ADC_CHANNEL_31,

    HAL_LL_ADC_CHANNEL_NC = 0xFFFF
} hal_ll_adc_channel_t;

/*!< @brief ADC pin structure. */
typedef struct
{
    hal_ll_pin_name_t     pin;
    hal_ll_base_addr_t    base;
    hal_ll_pin_name_t     module_index;
    hal_ll_adc_channel_t  channel;
} hal_ll_adc_pin_map_t;

// ------------------------------------------------------------------ CONSTANTS
/*!< ADC module base addresses. */
#ifdef ADC_MODULE_1
static const hal_ll_base_addr_t ADC1_BASE_ADDR = 0x40012400;
#endif

/*!< ADC input pins. */
static const hal_ll_adc_pin_map_t _adc_map[] =
{
    #ifdef ADC1_PA0_CH0
    {PA0,  ADC1_BASE_ADDR, ADC_MODULE_1 - 1, HAL_LL_ADC_CHANNEL_0},
    #endif
    #ifdef ADC1_PA1_CH1
    {PA1,  ADC1_BASE_ADDR, ADC_MODULE_1 - 1, HAL_LL_ADC_CHANNEL_1},
    #endif
    #ifdef ADC1_PA2_CH2
    {PA2,  ADC1_BASE_ADDR, ADC_MODULE_1 - 1, HAL_LL_ADC_CHANNEL_2},
    #endif
    #ifdef ADC1_PA3_CH3
    {PA3,  ADC1_BASE_ADDR, ADC_MODULE_1 - 1, HAL_LL_ADC_CHANNEL_3},
    #endif
    #ifdef ADC1_PA4_CH4
    {PA4,  ADC1_BASE_ADDR, ADC_MODULE_1 - 1, HAL_LL_ADC_CHANNEL_4},
    #endif
    #ifdef ADC1_PA5_CH5
    {PA5,  ADC1_BASE_ADDR, ADC_MODULE_1 - 1, HAL_LL_ADC_CHANNEL_5},
    #endif
    #ifdef ADC1_PA6_CH6
    {PA6,  ADC1_BASE_ADDR, ADC_MODULE_1 - 1, HAL_LL_ADC_CHANNEL_6},
    #endif
    #ifdef ADC1_PA7_CH7
    {PA7,  ADC1_BASE_ADDR, ADC_MODULE_1 - 1, HAL_LL_ADC_CHANNEL_7},
    #endif
    #ifdef ADC1_PB0_CH8
    {PB0,  ADC1_BASE_ADDR, ADC_MODULE_1 - 1, HAL_LL_ADC_CHANNEL_8},
    #endif
    #ifdef ADC1_PB1_CH9
    {PB1,  ADC1_BASE_ADDR, ADC_MODULE_1 - 1, HAL_LL_ADC_CHANNEL_9},
    #endif
    #ifdef ADC1_PB2_CH10
    {PB2,  ADC1_BASE_ADDR, ADC_MODULE_1 - 1, HAL_LL_ADC_CHANNEL_10},
    #endif
    #ifdef ADC1_PB10_CH11
    {PB10, ADC1_BASE_ADDR, ADC_MODULE_1 - 1, HAL_LL_ADC_CHANNEL_11},
    #endif
    #ifdef ADC1_PB12_CH16
    {PB12, ADC1_BASE_ADDR, ADC_MODULE_1 - 1, HAL_LL_ADC_CHANNEL_16},
    #endif
    #ifdef ADC1_PC4_CH17
    {PC4,  ADC1_BASE_ADDR, ADC_MODULE_1 - 1, HAL_LL_ADC_CHANNEL_17},
    #endif
    #ifdef ADC1_PC5_CH18
    {PC5,  ADC1_BASE_ADDR, ADC_MODULE_1 - 1, HAL_LL_ADC_CHANNEL_18},
    #endif

    {HAL_LL_PIN_NC, HAL_LL_MODULE_ERROR, HAL_LL_PIN_NC, HAL_LL_CHANNEL_ERROR}
};

#ifdef __cplusplus
}
#endif

#endif // _HAL_LL_ADC_PIN_MAP_H_
// ------------------------------------------------------------------------- END
