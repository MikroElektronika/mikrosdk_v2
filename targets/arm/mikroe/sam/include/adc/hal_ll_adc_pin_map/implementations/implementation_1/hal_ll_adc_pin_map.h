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
static const hal_ll_base_addr_t ADC0_BASE_ADDR = 0x4003C000;
static const hal_ll_base_addr_t ADC1_BASE_ADDR = 0x40064000;

/*!< ADC input pins. */
static const hal_ll_adc_pin_map_t _adc_map[] =
{
    {PD30, ADC0_BASE_ADDR, hal_ll_adc_module_num(ADC_MODULE_0), HAL_LL_ADC_CHANNEL_0},
    {PA21, ADC0_BASE_ADDR, hal_ll_adc_module_num(ADC_MODULE_0), HAL_LL_ADC_CHANNEL_1},
    {PB3, ADC0_BASE_ADDR, hal_ll_adc_module_num(ADC_MODULE_0), HAL_LL_ADC_CHANNEL_2},
    {PE5, ADC0_BASE_ADDR, hal_ll_adc_module_num(ADC_MODULE_0), HAL_LL_ADC_CHANNEL_3},
    {PE4, ADC0_BASE_ADDR, hal_ll_adc_module_num(ADC_MODULE_0), HAL_LL_ADC_CHANNEL_4},
    {PB2, ADC0_BASE_ADDR, hal_ll_adc_module_num(ADC_MODULE_0), HAL_LL_ADC_CHANNEL_5},
    {PA17, ADC0_BASE_ADDR, hal_ll_adc_module_num(ADC_MODULE_0), HAL_LL_ADC_CHANNEL_6},
    {PA18, ADC0_BASE_ADDR, hal_ll_adc_module_num(ADC_MODULE_0), HAL_LL_ADC_CHANNEL_7},
    {PA19, ADC0_BASE_ADDR, hal_ll_adc_module_num(ADC_MODULE_0), HAL_LL_ADC_CHANNEL_8},
    {PA20, ADC0_BASE_ADDR, hal_ll_adc_module_num(ADC_MODULE_0), HAL_LL_ADC_CHANNEL_9},
    {PB0, ADC0_BASE_ADDR, hal_ll_adc_module_num(ADC_MODULE_0), HAL_LL_ADC_CHANNEL_10},
    {PB1, ADC1_BASE_ADDR, hal_ll_adc_module_num(ADC_MODULE_1), HAL_LL_ADC_CHANNEL_0},
    {PC13, ADC1_BASE_ADDR, hal_ll_adc_module_num(ADC_MODULE_1), HAL_LL_ADC_CHANNEL_1},
    {PC15, ADC1_BASE_ADDR, hal_ll_adc_module_num(ADC_MODULE_1), HAL_LL_ADC_CHANNEL_2},
    {PC12, ADC1_BASE_ADDR, hal_ll_adc_module_num(ADC_MODULE_1), HAL_LL_ADC_CHANNEL_3},
    {PC29, ADC1_BASE_ADDR, hal_ll_adc_module_num(ADC_MODULE_1), HAL_LL_ADC_CHANNEL_4},
    {PC30, ADC1_BASE_ADDR, hal_ll_adc_module_num(ADC_MODULE_1), HAL_LL_ADC_CHANNEL_5},
    {PC31, ADC1_BASE_ADDR, hal_ll_adc_module_num(ADC_MODULE_1), HAL_LL_ADC_CHANNEL_6},
    {PC26, ADC1_BASE_ADDR, hal_ll_adc_module_num(ADC_MODULE_1), HAL_LL_ADC_CHANNEL_7},
    {PC27, ADC1_BASE_ADDR, hal_ll_adc_module_num(ADC_MODULE_1), HAL_LL_ADC_CHANNEL_8},
    {PC0, ADC1_BASE_ADDR, hal_ll_adc_module_num(ADC_MODULE_1), HAL_LL_ADC_CHANNEL_9},
    {PE3, ADC1_BASE_ADDR, hal_ll_adc_module_num(ADC_MODULE_1), HAL_LL_ADC_CHANNEL_10},
    {PE0, ADC1_BASE_ADDR, hal_ll_adc_module_num(ADC_MODULE_1), HAL_LL_ADC_CHANNEL_11},

    {HAL_LL_PIN_NC, HAL_LL_MODULE_ERROR, HAL_LL_PIN_NC, HAL_LL_CHANNEL_ERROR}
};

#ifdef __cplusplus
}
#endif

#endif // _HAL_LL_ADC_PIN_MAP_H_
// ------------------------------------------------------------------------- END
