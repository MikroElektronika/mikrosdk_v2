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
static const hal_ll_base_addr_t HAL_LL_ADC0_BASE_ADDR = ( hal_ll_base_addr_t ) 0x4005C000;
#endif
#ifdef ADC_MODULE_1
static const hal_ll_base_addr_t HAL_LL_ADC1_BASE_ADDR = ( hal_ll_base_addr_t ) 0x4005C200;
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
    #ifdef ADC0_P000_AN000
    {GPIO_P000, HAL_LL_ADC0_BASE_ADDR, hal_ll_adc_module_num( ADC_MODULE_0 ), HAL_LL_ADC_CHANNEL_0},
    #endif
    #ifdef ADC0_P001_AN001
    {GPIO_P001, HAL_LL_ADC0_BASE_ADDR, hal_ll_adc_module_num( ADC_MODULE_0 ), HAL_LL_ADC_CHANNEL_1},
    #endif
    #ifdef ADC0_P002_AN002
    {GPIO_P002, HAL_LL_ADC0_BASE_ADDR, hal_ll_adc_module_num( ADC_MODULE_0 ), HAL_LL_ADC_CHANNEL_2},
    #endif
    #ifdef ADC0_P003_AN003
    {GPIO_P003, HAL_LL_ADC0_BASE_ADDR, hal_ll_adc_module_num( ADC_MODULE_0 ), HAL_LL_ADC_CHANNEL_3},
    #endif
    #ifdef ADC0_P003_AN007
    {GPIO_P003, HAL_LL_ADC0_BASE_ADDR, hal_ll_adc_module_num( ADC_MODULE_0 ), HAL_LL_ADC_CHANNEL_7},
    #endif
    #ifdef ADC0_P004_AN004
    {GPIO_P004, HAL_LL_ADC0_BASE_ADDR, hal_ll_adc_module_num( ADC_MODULE_0 ), HAL_LL_ADC_CHANNEL_4},
    #endif
    #ifdef ADC0_P005_AN011
    {GPIO_P005, HAL_LL_ADC0_BASE_ADDR, hal_ll_adc_module_num( ADC_MODULE_0 ), HAL_LL_ADC_CHANNEL_11},
    #endif
    #ifdef ADC0_P006_AN012
    {GPIO_P006, HAL_LL_ADC0_BASE_ADDR, hal_ll_adc_module_num( ADC_MODULE_0 ), HAL_LL_ADC_CHANNEL_12},
    #endif
    #ifdef ADC0_P007_AN013
    {GPIO_P007, HAL_LL_ADC0_BASE_ADDR, hal_ll_adc_module_num( ADC_MODULE_0 ), HAL_LL_ADC_CHANNEL_13},
    #endif
    #ifdef ADC0_P008_AN003
    {GPIO_P008, HAL_LL_ADC0_BASE_ADDR, hal_ll_adc_module_num( ADC_MODULE_0 ), HAL_LL_ADC_CHANNEL_3},
    #endif
    #ifdef ADC0_P008_AN014
    {GPIO_P008, HAL_LL_ADC0_BASE_ADDR, hal_ll_adc_module_num( ADC_MODULE_0 ), HAL_LL_ADC_CHANNEL_14},
    #endif
    #ifdef ADC0_P009_AN004
    {GPIO_P009, HAL_LL_ADC0_BASE_ADDR, hal_ll_adc_module_num( ADC_MODULE_0 ), HAL_LL_ADC_CHANNEL_4},
    #endif
    #ifdef ADC0_P010_AN005
    {GPIO_P010, HAL_LL_ADC0_BASE_ADDR, hal_ll_adc_module_num( ADC_MODULE_0 ), HAL_LL_ADC_CHANNEL_5},
    #endif
    #ifdef ADC0_P011_AN006
    {GPIO_P011, HAL_LL_ADC0_BASE_ADDR, hal_ll_adc_module_num( ADC_MODULE_0 ), HAL_LL_ADC_CHANNEL_6},
    #endif
    #ifdef ADC0_P012_AN007
    {GPIO_P012, HAL_LL_ADC0_BASE_ADDR, hal_ll_adc_module_num( ADC_MODULE_0 ), HAL_LL_ADC_CHANNEL_7},
    #endif
    #ifdef ADC0_P013_AN008
    {GPIO_P013, HAL_LL_ADC0_BASE_ADDR, hal_ll_adc_module_num( ADC_MODULE_0 ), HAL_LL_ADC_CHANNEL_8},
    #endif
    #ifdef ADC0_P014_AN005
    {GPIO_P014, HAL_LL_ADC0_BASE_ADDR, hal_ll_adc_module_num( ADC_MODULE_0 ), HAL_LL_ADC_CHANNEL_5},
    #endif
    #ifdef ADC0_P014_AN009
    {GPIO_P014, HAL_LL_ADC0_BASE_ADDR, hal_ll_adc_module_num( ADC_MODULE_0 ), HAL_LL_ADC_CHANNEL_9},
    #endif
    #ifdef ADC0_P015_AN006
    {GPIO_P015, HAL_LL_ADC0_BASE_ADDR, hal_ll_adc_module_num( ADC_MODULE_0 ), HAL_LL_ADC_CHANNEL_6},
    #endif
    #ifdef ADC0_P015_AN010
    {GPIO_P015, HAL_LL_ADC0_BASE_ADDR, hal_ll_adc_module_num( ADC_MODULE_0 ), HAL_LL_ADC_CHANNEL_10},
    #endif
    #ifdef ADC0_P100_AN022
    {GPIO_P100, HAL_LL_ADC0_BASE_ADDR, hal_ll_adc_module_num( ADC_MODULE_0 ), HAL_LL_ADC_CHANNEL_22},
    #endif
    #ifdef ADC0_P101_AN021
    {GPIO_P101, HAL_LL_ADC0_BASE_ADDR, hal_ll_adc_module_num( ADC_MODULE_0 ), HAL_LL_ADC_CHANNEL_21},
    #endif
    #ifdef ADC0_P102_AN020
    {GPIO_P102, HAL_LL_ADC0_BASE_ADDR, hal_ll_adc_module_num( ADC_MODULE_0 ), HAL_LL_ADC_CHANNEL_20},
    #endif
    #ifdef ADC0_P103_AN019
    {GPIO_P103, HAL_LL_ADC0_BASE_ADDR, hal_ll_adc_module_num( ADC_MODULE_0 ), HAL_LL_ADC_CHANNEL_19},
    #endif
    #ifdef ADC0_P500_AN016
    {GPIO_P500, HAL_LL_ADC0_BASE_ADDR, hal_ll_adc_module_num( ADC_MODULE_0 ), HAL_LL_ADC_CHANNEL_16},
    #endif
    #ifdef ADC0_P501_AN017
    {GPIO_P501, HAL_LL_ADC0_BASE_ADDR, hal_ll_adc_module_num( ADC_MODULE_0 ), HAL_LL_ADC_CHANNEL_17},
    #endif
    #ifdef ADC0_P502_AN017
    {GPIO_P502, HAL_LL_ADC0_BASE_ADDR, hal_ll_adc_module_num( ADC_MODULE_0 ), HAL_LL_ADC_CHANNEL_17},
    #endif
    #ifdef ADC0_P502_AN018
    {GPIO_P502, HAL_LL_ADC0_BASE_ADDR, hal_ll_adc_module_num( ADC_MODULE_0 ), HAL_LL_ADC_CHANNEL_18},
    #endif
    #ifdef ADC0_P503_AN023
    {GPIO_P503, HAL_LL_ADC0_BASE_ADDR, hal_ll_adc_module_num( ADC_MODULE_0 ), HAL_LL_ADC_CHANNEL_23},
    #endif
    #ifdef ADC0_P504_AN018
    {GPIO_P504, HAL_LL_ADC0_BASE_ADDR, hal_ll_adc_module_num( ADC_MODULE_0 ), HAL_LL_ADC_CHANNEL_18},
    #endif
    #ifdef ADC0_P504_AN024
    {GPIO_P504, HAL_LL_ADC0_BASE_ADDR, hal_ll_adc_module_num( ADC_MODULE_0 ), HAL_LL_ADC_CHANNEL_24},
    #endif
    #ifdef ADC0_P505_AN025
    {GPIO_P505, HAL_LL_ADC0_BASE_ADDR, hal_ll_adc_module_num( ADC_MODULE_0 ), HAL_LL_ADC_CHANNEL_25},
    #endif
    #ifdef ADC0_P506_AN019
    {GPIO_P506, HAL_LL_ADC0_BASE_ADDR, hal_ll_adc_module_num( ADC_MODULE_0 ), HAL_LL_ADC_CHANNEL_19},
    #endif
    #ifdef ADC0_P508_AN020
    {GPIO_P508, HAL_LL_ADC0_BASE_ADDR, hal_ll_adc_module_num( ADC_MODULE_0 ), HAL_LL_ADC_CHANNEL_20},
    #endif
    #ifdef ADC1_P004_AN100
    {GPIO_P004, HAL_LL_ADC1_BASE_ADDR, hal_ll_adc_module_num( ADC_MODULE_1 ), HAL_LL_ADC_CHANNEL_0},
    #endif
    #ifdef ADC1_P005_AN101
    {GPIO_P005, HAL_LL_ADC1_BASE_ADDR, hal_ll_adc_module_num( ADC_MODULE_1 ), HAL_LL_ADC_CHANNEL_1},
    #endif
    #ifdef ADC1_P006_AN102
    {GPIO_P006, HAL_LL_ADC1_BASE_ADDR, hal_ll_adc_module_num( ADC_MODULE_1 ), HAL_LL_ADC_CHANNEL_2},
    #endif
    #ifdef ADC1_P007_AN107
    {GPIO_P007, HAL_LL_ADC1_BASE_ADDR, hal_ll_adc_module_num( ADC_MODULE_1 ), HAL_LL_ADC_CHANNEL_7},
    #endif
    #ifdef ADC1_P010_AN103
    {GPIO_P010, HAL_LL_ADC1_BASE_ADDR, hal_ll_adc_module_num( ADC_MODULE_1 ), HAL_LL_ADC_CHANNEL_3},
    #endif
    #ifdef ADC1_P014_AN105
    {GPIO_P014, HAL_LL_ADC1_BASE_ADDR, hal_ll_adc_module_num( ADC_MODULE_1 ), HAL_LL_ADC_CHANNEL_5},
    #endif
    #ifdef ADC1_P015_AN106
    {GPIO_P015, HAL_LL_ADC1_BASE_ADDR, hal_ll_adc_module_num( ADC_MODULE_1 ), HAL_LL_ADC_CHANNEL_6},
    #endif
    #ifdef ADC1_P501_AN116
    {GPIO_P501, HAL_LL_ADC1_BASE_ADDR, hal_ll_adc_module_num( ADC_MODULE_1 ), HAL_LL_ADC_CHANNEL_16},
    #endif
    #ifdef ADC1_P503_AN117
    {GPIO_P503, HAL_LL_ADC1_BASE_ADDR, hal_ll_adc_module_num( ADC_MODULE_1 ), HAL_LL_ADC_CHANNEL_17},
    #endif
    #ifdef ADC1_P505_AN118
    {GPIO_P505, HAL_LL_ADC1_BASE_ADDR, hal_ll_adc_module_num( ADC_MODULE_1 ), HAL_LL_ADC_CHANNEL_18},
    #endif
    #ifdef ADC1_P507_AN119
    {GPIO_P507, HAL_LL_ADC1_BASE_ADDR, hal_ll_adc_module_num( ADC_MODULE_1 ), HAL_LL_ADC_CHANNEL_19},
    #endif

    {HAL_LL_PIN_NC, HAL_LL_MODULE_ERROR, HAL_LL_PIN_NC, HAL_LL_PIN_NC}
    //------------ END
};

#ifdef __cplusplus
}
#endif

#endif // _HAL_LL_ADC_PIN_MAP_H_
// ------------------------------------------------------------------------- END