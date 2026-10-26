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
    #ifdef ADC0_P400_AN000
    {GPIO_P400, HAL_LL_ADC0_BASE_ADDR, hal_ll_adc_module_num( ADC_MODULE_0 ), HAL_LL_ADC_CHANNEL_0},
    #endif
    #ifdef ADC0_P401_AN001
    {GPIO_P401, HAL_LL_ADC0_BASE_ADDR, hal_ll_adc_module_num( ADC_MODULE_0 ), HAL_LL_ADC_CHANNEL_1},
    #endif
    #ifdef ADC0_P402_AN002
    {GPIO_P402, HAL_LL_ADC0_BASE_ADDR, hal_ll_adc_module_num( ADC_MODULE_0 ), HAL_LL_ADC_CHANNEL_2},
    #endif
    #ifdef ADC0_P403_AN003
    {GPIO_P403, HAL_LL_ADC0_BASE_ADDR, hal_ll_adc_module_num( ADC_MODULE_0 ), HAL_LL_ADC_CHANNEL_3},
    #endif
    #ifdef ADC0_P404_AN004
    {GPIO_P404, HAL_LL_ADC0_BASE_ADDR, hal_ll_adc_module_num( ADC_MODULE_0 ), HAL_LL_ADC_CHANNEL_4},
    #endif
    #ifdef ADC0_P405_AN005
    {GPIO_P405, HAL_LL_ADC0_BASE_ADDR, hal_ll_adc_module_num( ADC_MODULE_0 ), HAL_LL_ADC_CHANNEL_5},
    #endif
    #ifdef ADC0_P406_AN006
    {GPIO_P406, HAL_LL_ADC0_BASE_ADDR, hal_ll_adc_module_num( ADC_MODULE_0 ), HAL_LL_ADC_CHANNEL_6},
    #endif
    #ifdef ADC1_P404_AN100
    {GPIO_P404, HAL_LL_ADC1_BASE_ADDR, hal_ll_adc_module_num( ADC_MODULE_1 ), HAL_LL_ADC_CHANNEL_0},
    #endif
    #ifdef ADC1_P405_AN101
    {GPIO_P405, HAL_LL_ADC1_BASE_ADDR, hal_ll_adc_module_num( ADC_MODULE_1 ), HAL_LL_ADC_CHANNEL_1},
    #endif
    #ifdef ADC1_P406_AN102
    {GPIO_P406, HAL_LL_ADC1_BASE_ADDR, hal_ll_adc_module_num( ADC_MODULE_1 ), HAL_LL_ADC_CHANNEL_2},
    #endif
    #ifdef ADC1_P407_AN103
    {GPIO_P407, HAL_LL_ADC1_BASE_ADDR, hal_ll_adc_module_num( ADC_MODULE_1 ), HAL_LL_ADC_CHANNEL_3},
    #endif
    #ifdef ADC2_P200_AN216
    {GPIO_P200, HAL_LL_ADC2_BASE_ADDR, hal_ll_adc_module_num( ADC_MODULE_2 ), HAL_LL_ADC_CHANNEL_16},
    #endif
    #ifdef ADC2_P201_AN217
    {GPIO_P201, HAL_LL_ADC2_BASE_ADDR, hal_ll_adc_module_num( ADC_MODULE_2 ), HAL_LL_ADC_CHANNEL_17},
    #endif
    #ifdef ADC2_P407_AN206
    {GPIO_P407, HAL_LL_ADC2_BASE_ADDR, hal_ll_adc_module_num( ADC_MODULE_2 ), HAL_LL_ADC_CHANNEL_6},
    #endif
    #ifdef ADC2_P500_AN204
    {GPIO_P500, HAL_LL_ADC2_BASE_ADDR, hal_ll_adc_module_num( ADC_MODULE_2 ), HAL_LL_ADC_CHANNEL_4},
    #endif
    #ifdef ADC2_P501_AN205
    {GPIO_P501, HAL_LL_ADC2_BASE_ADDR, hal_ll_adc_module_num( ADC_MODULE_2 ), HAL_LL_ADC_CHANNEL_5},
    #endif
    #ifdef ADC2_P502_AN200
    {GPIO_P502, HAL_LL_ADC2_BASE_ADDR, hal_ll_adc_module_num( ADC_MODULE_2 ), HAL_LL_ADC_CHANNEL_0},
    #endif
    #ifdef ADC2_P503_AN201
    {GPIO_P503, HAL_LL_ADC2_BASE_ADDR, hal_ll_adc_module_num( ADC_MODULE_2 ), HAL_LL_ADC_CHANNEL_1},
    #endif
    #ifdef ADC2_P504_AN202
    {GPIO_P504, HAL_LL_ADC2_BASE_ADDR, hal_ll_adc_module_num( ADC_MODULE_2 ), HAL_LL_ADC_CHANNEL_2},
    #endif
    #ifdef ADC2_P505_AN203
    {GPIO_P505, HAL_LL_ADC2_BASE_ADDR, hal_ll_adc_module_num( ADC_MODULE_2 ), HAL_LL_ADC_CHANNEL_3},
    #endif
    #ifdef ADC2_P600_AN206
    {GPIO_P600, HAL_LL_ADC2_BASE_ADDR, hal_ll_adc_module_num( ADC_MODULE_2 ), HAL_LL_ADC_CHANNEL_6},
    #endif
    #ifdef ADC2_P601_AN207
    {GPIO_P601, HAL_LL_ADC2_BASE_ADDR, hal_ll_adc_module_num( ADC_MODULE_2 ), HAL_LL_ADC_CHANNEL_7},
    #endif
    #ifdef ADC2_P602_AN208
    {GPIO_P602, HAL_LL_ADC2_BASE_ADDR, hal_ll_adc_module_num( ADC_MODULE_2 ), HAL_LL_ADC_CHANNEL_8},
    #endif
    #ifdef ADC2_P603_AN209
    {GPIO_P603, HAL_LL_ADC2_BASE_ADDR, hal_ll_adc_module_num( ADC_MODULE_2 ), HAL_LL_ADC_CHANNEL_9},
    #endif
    #ifdef ADC2_P604_AN210
    {GPIO_P604, HAL_LL_ADC2_BASE_ADDR, hal_ll_adc_module_num( ADC_MODULE_2 ), HAL_LL_ADC_CHANNEL_10},
    #endif
    #ifdef ADC2_P605_AN211
    {GPIO_P605, HAL_LL_ADC2_BASE_ADDR, hal_ll_adc_module_num( ADC_MODULE_2 ), HAL_LL_ADC_CHANNEL_11},
    #endif

    {HAL_LL_PIN_NC, HAL_LL_MODULE_ERROR, HAL_LL_PIN_NC, HAL_LL_PIN_NC}
    //------------ END
};

#ifdef __cplusplus
}
#endif

#endif // _HAL_LL_ADC_PIN_MAP_H_
// ------------------------------------------------------------------------- END
