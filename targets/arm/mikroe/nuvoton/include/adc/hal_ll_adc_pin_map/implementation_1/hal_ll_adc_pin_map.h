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

/*!< @brief Macro defining `weak` attribute */
#define __weak __attribute__((weak))

/*!< @brief Helper macro for getting adequate module index number */
#define hal_ll_adc_module_num(_module_num) (_module_num - 1)

/*!< ADC module base addresses. */
#ifdef ADC_MODULE_0
static const hal_ll_base_addr_t HAL_LL_ADC0_BASE_ADDR = ( hal_ll_base_addr_t ) 0x40043000;
#endif

/**
 * ADC channels.
 */
typedef enum
{
    HAL_LL_ADC_CHANNEL_0,
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

    HAL_LL_ADC_CHANNEL_NC = 0xFFFF
} hal_ll_adc_channel_t;

/*!< @brief ADC pin structure. */
typedef struct
{
    uint8_t pin;
    hal_ll_base_addr_t base;
    uint8_t module_index;
    uint8_t channel;
} hal_ll_pin_channel_list_t;

static const hal_ll_pin_channel_list_t hal_ll_analog_in_register_list[] =
{
    #ifdef ADC0_PB0_CH0
    {GPIO_PB0,  HAL_LL_ADC0_BASE_ADDR, hal_ll_adc_module_num(ADC_MODULE_0), HAL_LL_ADC_CHANNEL_0},
    #endif
    #ifdef ADC0_PB1_CH1
    {GPIO_PB1,  HAL_LL_ADC0_BASE_ADDR, hal_ll_adc_module_num(ADC_MODULE_0), HAL_LL_ADC_CHANNEL_1},
    #endif
    #ifdef ADC0_PB2_CH2
    {GPIO_PB2,  HAL_LL_ADC0_BASE_ADDR, hal_ll_adc_module_num(ADC_MODULE_0), HAL_LL_ADC_CHANNEL_2},
    #endif
    #ifdef ADC0_PB3_CH3
    {GPIO_PB3,  HAL_LL_ADC0_BASE_ADDR, hal_ll_adc_module_num(ADC_MODULE_0), HAL_LL_ADC_CHANNEL_3},
    #endif
    #ifdef ADC0_PB4_CH4
    {GPIO_PB4,  HAL_LL_ADC0_BASE_ADDR, hal_ll_adc_module_num(ADC_MODULE_0), HAL_LL_ADC_CHANNEL_4},
    #endif
    #ifdef ADC0_PB5_CH5
    {GPIO_PB5,  HAL_LL_ADC0_BASE_ADDR, hal_ll_adc_module_num(ADC_MODULE_0), HAL_LL_ADC_CHANNEL_5},
    #endif
    #ifdef ADC0_PB6_CH6
    {GPIO_PB6,  HAL_LL_ADC0_BASE_ADDR, hal_ll_adc_module_num(ADC_MODULE_0), HAL_LL_ADC_CHANNEL_6},
    #endif
    #ifdef ADC0_PB7_CH7
    {GPIO_PB7,  HAL_LL_ADC0_BASE_ADDR, hal_ll_adc_module_num(ADC_MODULE_0), HAL_LL_ADC_CHANNEL_7},
    #endif
    #ifdef ADC0_PB8_CH8
    {GPIO_PB8,  HAL_LL_ADC0_BASE_ADDR, hal_ll_adc_module_num(ADC_MODULE_0), HAL_LL_ADC_CHANNEL_8},
    #endif
    #ifdef ADC0_PB9_CH9
    {GPIO_PB9,  HAL_LL_ADC0_BASE_ADDR, hal_ll_adc_module_num(ADC_MODULE_0), HAL_LL_ADC_CHANNEL_9},
    #endif
    #ifdef ADC0_PB10_CH10
    {GPIO_PB10,  HAL_LL_ADC0_BASE_ADDR, hal_ll_adc_module_num(ADC_MODULE_0), HAL_LL_ADC_CHANNEL_10},
    #endif
    #ifdef ADC0_PB11_CH11
    {GPIO_PB11,  HAL_LL_ADC0_BASE_ADDR, hal_ll_adc_module_num(ADC_MODULE_0), HAL_LL_ADC_CHANNEL_11},
    #endif
    #ifdef ADC0_PB12_CH12
    {GPIO_PB12,  HAL_LL_ADC0_BASE_ADDR, hal_ll_adc_module_num(ADC_MODULE_0), HAL_LL_ADC_CHANNEL_12},
    #endif
    #ifdef ADC0_PB13_CH13
    {GPIO_PB13,  HAL_LL_ADC0_BASE_ADDR, hal_ll_adc_module_num(ADC_MODULE_0), HAL_LL_ADC_CHANNEL_13},
    #endif
    #ifdef ADC0_PB14_CH14
    {GPIO_PB14,  HAL_LL_ADC0_BASE_ADDR, hal_ll_adc_module_num(ADC_MODULE_0), HAL_LL_ADC_CHANNEL_14},
    #endif
    #ifdef ADC0_PB15_CH15
    {GPIO_PB15,  HAL_LL_ADC0_BASE_ADDR, hal_ll_adc_module_num(ADC_MODULE_0), HAL_LL_ADC_CHANNEL_15},
    #endif

    {HAL_LL_PIN_NC, HAL_LL_MODULE_ERROR, HAL_LL_PIN_NC, HAL_LL_PIN_NC}
    //------------ END
};

#ifdef __cplusplus
}
#endif

#endif // _HAL_LL_ADC_PIN_MAP_H_
// ------------------------------------------------------------------------- END