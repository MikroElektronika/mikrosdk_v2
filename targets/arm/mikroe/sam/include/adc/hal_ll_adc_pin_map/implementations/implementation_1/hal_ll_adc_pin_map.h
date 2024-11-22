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
#define hal_ll_adc_module_num(_module_num) (_module_num)

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
#ifdef ADC_MODULE_0
static const hal_ll_base_addr_t HAL_LL_ADC0_BASE_ADDR = 0x4003C000;
#endif
#ifdef ADC_MODULE_1
static const hal_ll_base_addr_t HAL_LL_ADC1_BASE_ADDR = 0x40064000;
#endif

/*!< ADC input pins. */
static const hal_ll_adc_pin_map_t _adc_map[] =
{
    #ifdef ADC0_PD30_CH0
    {PD30, HAL_LL_ADC0_BASE_ADDR, hal_ll_adc_module_num(ADC_MODULE_0), HAL_LL_ADC_CHANNEL_0},
    #endif
    #ifdef ADC0_PA21_CH1
    {PA21, HAL_LL_ADC0_BASE_ADDR, hal_ll_adc_module_num(ADC_MODULE_0), HAL_LL_ADC_CHANNEL_1},
    #endif
    #ifdef ADC0_PB3_CH2
    {PB3, HAL_LL_ADC0_BASE_ADDR, hal_ll_adc_module_num(ADC_MODULE_0), HAL_LL_ADC_CHANNEL_2},
    #endif
    #ifdef ADC0_PE5_CH3
    {PE5, HAL_LL_ADC0_BASE_ADDR, hal_ll_adc_module_num(ADC_MODULE_0), HAL_LL_ADC_CHANNEL_3},
    #endif
    #ifdef ADC0_PE4_CH4
    {PE4, HAL_LL_ADC0_BASE_ADDR, hal_ll_adc_module_num(ADC_MODULE_0), HAL_LL_ADC_CHANNEL_4},
    #endif
    #ifdef ADC0_PB2_CH5
    {PB2, HAL_LL_ADC0_BASE_ADDR, hal_ll_adc_module_num(ADC_MODULE_0), HAL_LL_ADC_CHANNEL_5},
    #endif
    #ifdef ADC0_PA17_CH6
    {PA17, HAL_LL_ADC0_BASE_ADDR, hal_ll_adc_module_num(ADC_MODULE_0), HAL_LL_ADC_CHANNEL_6},
    #endif
    #ifdef ADC0_PA18_CH7
    {PA18, HAL_LL_ADC0_BASE_ADDR, hal_ll_adc_module_num(ADC_MODULE_0), HAL_LL_ADC_CHANNEL_7},
    #endif
    #ifdef ADC0_PA19_CH8
    {PA19, HAL_LL_ADC0_BASE_ADDR, hal_ll_adc_module_num(ADC_MODULE_0), HAL_LL_ADC_CHANNEL_8},
    #endif
    #ifdef ADC0_PA20_CH9
    {PA20, HAL_LL_ADC0_BASE_ADDR, hal_ll_adc_module_num(ADC_MODULE_0), HAL_LL_ADC_CHANNEL_9},
    #endif
    #ifdef ADC0_PB0_CH10
    {PB0, HAL_LL_ADC0_BASE_ADDR, hal_ll_adc_module_num(ADC_MODULE_0), HAL_LL_ADC_CHANNEL_10},
    #endif
    #ifdef ADC1_PB1_CH0
    {PB1, HAL_LL_ADC1_BASE_ADDR, hal_ll_adc_module_num(ADC_MODULE_1), HAL_LL_ADC_CHANNEL_0},
    #endif
    #ifdef ADC1_PC13_CH1
    {PC13, HAL_LL_ADC1_BASE_ADDR, hal_ll_adc_module_num(ADC_MODULE_1), HAL_LL_ADC_CHANNEL_1},
    #endif
    #ifdef ADC1_PC15_CH2
    {PC15, HAL_LL_ADC1_BASE_ADDR, hal_ll_adc_module_num(ADC_MODULE_1), HAL_LL_ADC_CHANNEL_2},
    #endif
    #ifdef ADC1_PC12_CH3
    {PC12, HAL_LL_ADC1_BASE_ADDR, hal_ll_adc_module_num(ADC_MODULE_1), HAL_LL_ADC_CHANNEL_3},
    #endif
    #ifdef ADC1_PC29_CH4
    {PC29, HAL_LL_ADC1_BASE_ADDR, hal_ll_adc_module_num(ADC_MODULE_1), HAL_LL_ADC_CHANNEL_4},
    #endif
    #ifdef ADC1_PC30_CH5
    {PC30, HAL_LL_ADC1_BASE_ADDR, hal_ll_adc_module_num(ADC_MODULE_1), HAL_LL_ADC_CHANNEL_5},
    #endif
    #ifdef ADC1_PC31_CH6
    {PC31, HAL_LL_ADC1_BASE_ADDR, hal_ll_adc_module_num(ADC_MODULE_1), HAL_LL_ADC_CHANNEL_6},
    #endif
    #ifdef ADC1_PC26_CH7
    {PC26, HAL_LL_ADC1_BASE_ADDR, hal_ll_adc_module_num(ADC_MODULE_1), HAL_LL_ADC_CHANNEL_7},
    #endif
    #ifdef ADC1_PC27_CH8
    {PC27, HAL_LL_ADC1_BASE_ADDR, hal_ll_adc_module_num(ADC_MODULE_1), HAL_LL_ADC_CHANNEL_8},
    #endif
    #ifdef ADC1_PC0_CH9
    {PC0, HAL_LL_ADC1_BASE_ADDR, hal_ll_adc_module_num(ADC_MODULE_1), HAL_LL_ADC_CHANNEL_9},
    #endif
    #ifdef ADC1_PE3_CH10
    {PE3, HAL_LL_ADC1_BASE_ADDR, hal_ll_adc_module_num(ADC_MODULE_1), HAL_LL_ADC_CHANNEL_10},
    #endif
    #ifdef ADC1_PE0_CH11
    {PE0, HAL_LL_ADC1_BASE_ADDR, hal_ll_adc_module_num(ADC_MODULE_1), HAL_LL_ADC_CHANNEL_11},
    #endif

    {HAL_LL_PIN_NC, HAL_LL_MODULE_ERROR, HAL_LL_PIN_NC, HAL_LL_CHANNEL_ERROR}
};

#ifdef __cplusplus
}
#endif

#endif // _HAL_LL_ADC_PIN_MAP_H_
// ------------------------------------------------------------------------- END
