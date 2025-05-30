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

/*!< ADC module base addresses. */
#ifdef ADC_MODULE_1
static const hal_ll_base_addr_t ADC1_BASE_ADDR = 0x40012000;
#endif
#ifdef ADC_MODULE_2
static const hal_ll_base_addr_t ADC2_BASE_ADDR = 0x40012100;
#endif
#ifdef ADC_MODULE_3
static const hal_ll_base_addr_t ADC3_BASE_ADDR = 0x40012200;
#endif

/*!< ADC input pins. */
static const hal_ll_adc_pin_map_t _adc_map[] =
{
    #ifdef ADC1_PA0_CH0
    {GPIO_PA0,  ADC1_BASE_ADDR, hal_ll_adc_module_num(ADC_MODULE_1), HAL_LL_ADC_CHANNEL_0},
    #endif
    #ifdef ADC1_PA1_CH1
    {GPIO_PA1,  ADC1_BASE_ADDR, hal_ll_adc_module_num(ADC_MODULE_1), HAL_LL_ADC_CHANNEL_1},
    #endif
    #ifdef ADC1_PA2_CH2
    {GPIO_PA2,  ADC1_BASE_ADDR, hal_ll_adc_module_num(ADC_MODULE_1), HAL_LL_ADC_CHANNEL_2},
    #endif
    #ifdef ADC1_PA3_CH3
    {GPIO_PA3,  ADC1_BASE_ADDR, hal_ll_adc_module_num(ADC_MODULE_1), HAL_LL_ADC_CHANNEL_3},
    #endif
    #ifdef ADC1_PA4_CH4
    {GPIO_PA4,  ADC1_BASE_ADDR, hal_ll_adc_module_num(ADC_MODULE_1), HAL_LL_ADC_CHANNEL_4},
    #endif
    #ifdef ADC1_PA5_CH5
    {GPIO_PA5,  ADC1_BASE_ADDR, hal_ll_adc_module_num(ADC_MODULE_1), HAL_LL_ADC_CHANNEL_5},
    #endif
    #ifdef ADC1_PA6_CH6
    {GPIO_PA6,  ADC1_BASE_ADDR, hal_ll_adc_module_num(ADC_MODULE_1), HAL_LL_ADC_CHANNEL_6},
    #endif
    #ifdef ADC1_PA7_CH7
    {GPIO_PA7,  ADC1_BASE_ADDR, hal_ll_adc_module_num(ADC_MODULE_1), HAL_LL_ADC_CHANNEL_7},
    #endif
    #ifdef ADC1_PB0_CH8
    {GPIO_PB0,  ADC1_BASE_ADDR, hal_ll_adc_module_num(ADC_MODULE_1), HAL_LL_ADC_CHANNEL_8},
    #endif
    #ifdef ADC1_PB1_CH9
    {GPIO_PB1,  ADC1_BASE_ADDR, hal_ll_adc_module_num(ADC_MODULE_1), HAL_LL_ADC_CHANNEL_9},
    #endif
    #ifdef ADC1_PC0_CH10
    {GPIO_PC0,  ADC1_BASE_ADDR, hal_ll_adc_module_num(ADC_MODULE_1), HAL_LL_ADC_CHANNEL_10},
    #endif
    #ifdef ADC1_PC1_CH11
    {GPIO_PC1,  ADC1_BASE_ADDR, hal_ll_adc_module_num(ADC_MODULE_1), HAL_LL_ADC_CHANNEL_11},
    #endif
    #ifdef ADC1_PC2_CH12
    {GPIO_PC2,  ADC1_BASE_ADDR, hal_ll_adc_module_num(ADC_MODULE_1), HAL_LL_ADC_CHANNEL_12},
    #endif
    #ifdef ADC1_PC3_CH13
    {GPIO_PC3,  ADC1_BASE_ADDR, hal_ll_adc_module_num(ADC_MODULE_1), HAL_LL_ADC_CHANNEL_13},
    #endif
    #ifdef ADC1_PC4_CH14
    {GPIO_PC4,  ADC1_BASE_ADDR, hal_ll_adc_module_num(ADC_MODULE_1), HAL_LL_ADC_CHANNEL_14},
    #endif
    #ifdef ADC1_PC5_CH15
    {GPIO_PC5,  ADC1_BASE_ADDR, hal_ll_adc_module_num(ADC_MODULE_1), HAL_LL_ADC_CHANNEL_15},
    #endif
    #ifdef ADC2_PA0_CH0
    {GPIO_PA0,  ADC2_BASE_ADDR, hal_ll_adc_module_num(ADC_MODULE_2), HAL_LL_ADC_CHANNEL_0},
    #endif
    #ifdef ADC2_PA1_CH1
    {GPIO_PA1,  ADC2_BASE_ADDR, hal_ll_adc_module_num(ADC_MODULE_2), HAL_LL_ADC_CHANNEL_1},
    #endif
    #ifdef ADC2_PA2_CH2
    {GPIO_PA2,  ADC2_BASE_ADDR, hal_ll_adc_module_num(ADC_MODULE_2), HAL_LL_ADC_CHANNEL_2},
    #endif
    #ifdef ADC2_PA3_CH3
    {GPIO_PA3,  ADC2_BASE_ADDR, hal_ll_adc_module_num(ADC_MODULE_2), HAL_LL_ADC_CHANNEL_3},
    #endif
    #ifdef ADC2_PA4_CH4
    {GPIO_PA4,  ADC2_BASE_ADDR, hal_ll_adc_module_num(ADC_MODULE_2), HAL_LL_ADC_CHANNEL_4},
    #endif
    #ifdef ADC2_PA5_CH5
    {GPIO_PA5,  ADC2_BASE_ADDR, hal_ll_adc_module_num(ADC_MODULE_2), HAL_LL_ADC_CHANNEL_5},
    #endif
    #ifdef ADC2_PA6_CH6
    {GPIO_PA6,  ADC2_BASE_ADDR, hal_ll_adc_module_num(ADC_MODULE_2), HAL_LL_ADC_CHANNEL_6},
    #endif
    #ifdef ADC2_PA7_CH7
    {GPIO_PA7,  ADC2_BASE_ADDR, hal_ll_adc_module_num(ADC_MODULE_2), HAL_LL_ADC_CHANNEL_7},
    #endif
    #ifdef ADC2_PB0_CH8
    {GPIO_PB0,  ADC2_BASE_ADDR, hal_ll_adc_module_num(ADC_MODULE_2), HAL_LL_ADC_CHANNEL_8},
    #endif
    #ifdef ADC2_PB1_CH9
    {GPIO_PB1,  ADC2_BASE_ADDR, hal_ll_adc_module_num(ADC_MODULE_2), HAL_LL_ADC_CHANNEL_9},
    #endif
    #ifdef ADC2_PC0_CH10
    {GPIO_PC0,  ADC2_BASE_ADDR, hal_ll_adc_module_num(ADC_MODULE_2), HAL_LL_ADC_CHANNEL_10},
    #endif
    #ifdef ADC2_PC1_CH11
    {GPIO_PC1,  ADC2_BASE_ADDR, hal_ll_adc_module_num(ADC_MODULE_2), HAL_LL_ADC_CHANNEL_11},
    #endif
    #ifdef ADC2_PC2_CH12
    {GPIO_PC2,  ADC2_BASE_ADDR, hal_ll_adc_module_num(ADC_MODULE_2), HAL_LL_ADC_CHANNEL_12},
    #endif
    #ifdef ADC2_PC3_CH13
    {GPIO_PC3,  ADC2_BASE_ADDR, hal_ll_adc_module_num(ADC_MODULE_2), HAL_LL_ADC_CHANNEL_13},
    #endif
    #ifdef ADC2_PC4_CH14
    {GPIO_PC4,  ADC2_BASE_ADDR, hal_ll_adc_module_num(ADC_MODULE_2), HAL_LL_ADC_CHANNEL_14},
    #endif
    #ifdef ADC2_PC5_CH15
    {GPIO_PC5,  ADC2_BASE_ADDR, hal_ll_adc_module_num(ADC_MODULE_2), HAL_LL_ADC_CHANNEL_15},
    #endif
    #ifdef ADC3_PA0_CH0
    {GPIO_PA0,  ADC3_BASE_ADDR, hal_ll_adc_module_num(ADC_MODULE_3), HAL_LL_ADC_CHANNEL_0},
    #endif
    #ifdef ADC3_PA1_CH1
    {GPIO_PA1,  ADC3_BASE_ADDR, hal_ll_adc_module_num(ADC_MODULE_3), HAL_LL_ADC_CHANNEL_1},
    #endif
    #ifdef ADC3_PA2_CH2
    {GPIO_PA2,  ADC3_BASE_ADDR, hal_ll_adc_module_num(ADC_MODULE_3), HAL_LL_ADC_CHANNEL_2},
    #endif
    #ifdef ADC3_PA3_CH3
    {GPIO_PA3,  ADC3_BASE_ADDR, hal_ll_adc_module_num(ADC_MODULE_3), HAL_LL_ADC_CHANNEL_3},
    #endif
    #ifdef ADC3_PF6_CH4
    {GPIO_PF6,  ADC3_BASE_ADDR, hal_ll_adc_module_num(ADC_MODULE_3), HAL_LL_ADC_CHANNEL_4},
    #endif
    #ifdef ADC3_PF7_CH5
    {GPIO_PF7,  ADC3_BASE_ADDR, hal_ll_adc_module_num(ADC_MODULE_3), HAL_LL_ADC_CHANNEL_5},
    #endif
    #ifdef ADC3_PF8_CH6
    {GPIO_PF8,  ADC3_BASE_ADDR, hal_ll_adc_module_num(ADC_MODULE_3), HAL_LL_ADC_CHANNEL_6},
    #endif
    #ifdef ADC3_PF9_CH7
    {GPIO_PF9,  ADC3_BASE_ADDR, hal_ll_adc_module_num(ADC_MODULE_3), HAL_LL_ADC_CHANNEL_7},
    #endif
    #ifdef ADC3_PF10_CH8
    {GPIO_PF10,  ADC3_BASE_ADDR, hal_ll_adc_module_num(ADC_MODULE_3), HAL_LL_ADC_CHANNEL_8},
    #endif
    #ifdef ADC3_PF3_CH9
    {GPIO_PF3,  ADC3_BASE_ADDR, hal_ll_adc_module_num(ADC_MODULE_3), HAL_LL_ADC_CHANNEL_9},
    #endif
    #ifdef ADC3_PC0_CH10
    {GPIO_PC0,  ADC3_BASE_ADDR, hal_ll_adc_module_num(ADC_MODULE_3), HAL_LL_ADC_CHANNEL_10},
    #endif
    #ifdef ADC3_PC1_CH11
    {GPIO_PC1,  ADC3_BASE_ADDR, hal_ll_adc_module_num(ADC_MODULE_3), HAL_LL_ADC_CHANNEL_11},
    #endif
    #ifdef ADC3_PC2_CH12
    {GPIO_PC2,  ADC3_BASE_ADDR, hal_ll_adc_module_num(ADC_MODULE_3), HAL_LL_ADC_CHANNEL_12},
    #endif
    #ifdef ADC3_PC3_CH13
    {GPIO_PC3,  ADC3_BASE_ADDR, hal_ll_adc_module_num(ADC_MODULE_3), HAL_LL_ADC_CHANNEL_13},
    #endif
    #ifdef ADC3_PF4_CH14
    {GPIO_PF4,  ADC3_BASE_ADDR, hal_ll_adc_module_num(ADC_MODULE_3), HAL_LL_ADC_CHANNEL_14},
    #endif
    #ifdef ADC3_PF5_CH15
    {GPIO_PF5,  ADC3_BASE_ADDR, hal_ll_adc_module_num(ADC_MODULE_3), HAL_LL_ADC_CHANNEL_15},
    #endif

    {HAL_LL_PIN_NC, HAL_LL_MODULE_ERROR, HAL_LL_PIN_NC, HAL_LL_CHANNEL_ERROR}
};

#ifdef __cplusplus
}
#endif

#endif // _HAL_LL_ADC_PIN_MAP_H_
// ------------------------------------------------------------------------- END
