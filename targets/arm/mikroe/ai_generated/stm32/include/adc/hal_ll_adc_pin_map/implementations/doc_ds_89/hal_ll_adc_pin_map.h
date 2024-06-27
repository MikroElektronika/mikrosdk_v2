/****************************************************************************
**
** Copyright (C) 2024 MikroElektronika d.o.o.
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
    hal_ll_pin_name_t pin;
    hal_ll_base_addr_t base;
    hal_ll_pin_name_t module_index;
    hal_ll_adc_channel_t channel;
} hal_ll_adc_pin_map_t;

#ifdef ADC_MODULE_1
#define ADC1_BASE_ADDRESS (0x50000000UL)
#define ADC1_BASE_ADDR ADC1_BASE_ADDRESS
#define HAL_LL_ADC1_BASE_ADDR ADC1_BASE_ADDRESS
#define HAL_LL_ADC1_BASE_ADDRESS ADC1_BASE_ADDRESS
#endif
#ifdef ADC_MODULE_2
#define ADC2_BASE_ADDRESS (0x50000100UL)
#define ADC2_BASE_ADDR ADC2_BASE_ADDRESS
#define HAL_LL_ADC2_BASE_ADDR ADC2_BASE_ADDRESS
#define HAL_LL_ADC2_BASE_ADDRESS ADC2_BASE_ADDRESS
#endif
#ifdef ADC_MODULE_3
#define ADC3_BASE_ADDRESS (0x50000400UL)
#define ADC3_BASE_ADDR ADC3_BASE_ADDRESS
#define HAL_LL_ADC3_BASE_ADDR ADC3_BASE_ADDRESS
#define HAL_LL_ADC3_BASE_ADDRESS ADC3_BASE_ADDRESS
#endif

/*!< ADC input pins. */
static const hal_ll_adc_pin_map_t _adc_map[] =
{
    #ifdef ADC1_PA0_CH1
    {PA0, ADC1_BASE_ADDRESS, hal_ll_adc_module_num(ADC_MODULE_1), HAL_LL_ADC_CHANNEL_1},
    #endif
    #ifdef ADC1_PA1_CH2
    {PA1, ADC1_BASE_ADDRESS, hal_ll_adc_module_num(ADC_MODULE_1), HAL_LL_ADC_CHANNEL_2},
    #endif
    #ifdef ADC1_PA2_CH3
    {PA2, ADC1_BASE_ADDRESS, hal_ll_adc_module_num(ADC_MODULE_1), HAL_LL_ADC_CHANNEL_3},
    #endif
    #ifdef ADC1_PA3_CH4
    {PA3, ADC1_BASE_ADDRESS, hal_ll_adc_module_num(ADC_MODULE_1), HAL_LL_ADC_CHANNEL_4},
    #endif
    #ifdef ADC1_PB0_CH15
    {PB0, ADC1_BASE_ADDRESS, hal_ll_adc_module_num(ADC_MODULE_1), HAL_LL_ADC_CHANNEL_15},
    #endif
    #ifdef ADC1_PB11_CH14
    {PB11, ADC1_BASE_ADDRESS, hal_ll_adc_module_num(ADC_MODULE_1), HAL_LL_ADC_CHANNEL_14},
    #endif
    #ifdef ADC1_PB12_CH11
    {PB12, ADC1_BASE_ADDRESS, hal_ll_adc_module_num(ADC_MODULE_1), HAL_LL_ADC_CHANNEL_11},
    #endif
    #ifdef ADC1_PB14_CH5
    {PB14, ADC1_BASE_ADDRESS, hal_ll_adc_module_num(ADC_MODULE_1), HAL_LL_ADC_CHANNEL_5},
    #endif
    #ifdef ADC1_PB1_CH12
    {PB1, ADC1_BASE_ADDRESS, hal_ll_adc_module_num(ADC_MODULE_1), HAL_LL_ADC_CHANNEL_12},
    #endif
    #ifdef ADC1_PC0_CH6
    {PC0, ADC1_BASE_ADDRESS, hal_ll_adc_module_num(ADC_MODULE_1), HAL_LL_ADC_CHANNEL_6},
    #endif
    #ifdef ADC1_PC1_CH7
    {PC1, ADC1_BASE_ADDRESS, hal_ll_adc_module_num(ADC_MODULE_1), HAL_LL_ADC_CHANNEL_7},
    #endif
    #ifdef ADC1_PC2_CH8
    {PC2, ADC1_BASE_ADDRESS, hal_ll_adc_module_num(ADC_MODULE_1), HAL_LL_ADC_CHANNEL_8},
    #endif
    #ifdef ADC1_PC3_CH9
    {PC3, ADC1_BASE_ADDRESS, hal_ll_adc_module_num(ADC_MODULE_1), HAL_LL_ADC_CHANNEL_9},
    #endif
    #ifdef ADC1_PF0_CH10
    {PF0, ADC1_BASE_ADDRESS, hal_ll_adc_module_num(ADC_MODULE_1), HAL_LL_ADC_CHANNEL_10},
    #endif
    #ifdef ADC2_PA0_CH1
    {PA0, ADC2_BASE_ADDRESS, hal_ll_adc_module_num(ADC_MODULE_2), HAL_LL_ADC_CHANNEL_1},
    #endif
    #ifdef ADC2_PA1_CH2
    {PA1, ADC2_BASE_ADDRESS, hal_ll_adc_module_num(ADC_MODULE_2), HAL_LL_ADC_CHANNEL_2},
    #endif
    #ifdef ADC2_PA4_CH17
    {PA4, ADC2_BASE_ADDRESS, hal_ll_adc_module_num(ADC_MODULE_2), HAL_LL_ADC_CHANNEL_17},
    #endif
    #ifdef ADC2_PA5_CH13
    {PA5, ADC2_BASE_ADDRESS, hal_ll_adc_module_num(ADC_MODULE_2), HAL_LL_ADC_CHANNEL_13},
    #endif
    #ifdef ADC2_PA6_CH3
    {PA6, ADC2_BASE_ADDRESS, hal_ll_adc_module_num(ADC_MODULE_2), HAL_LL_ADC_CHANNEL_3},
    #endif
    #ifdef ADC2_PA7_CH4
    {PA7, ADC2_BASE_ADDRESS, hal_ll_adc_module_num(ADC_MODULE_2), HAL_LL_ADC_CHANNEL_4},
    #endif
    #ifdef ADC2_PB11_CH14
    {PB11, ADC2_BASE_ADDRESS, hal_ll_adc_module_num(ADC_MODULE_2), HAL_LL_ADC_CHANNEL_14},
    #endif
    #ifdef ADC2_PB15_CH15
    {PB15, ADC2_BASE_ADDRESS, hal_ll_adc_module_num(ADC_MODULE_2), HAL_LL_ADC_CHANNEL_15},
    #endif
    #ifdef ADC2_PB2_CH12
    {PB2, ADC2_BASE_ADDRESS, hal_ll_adc_module_num(ADC_MODULE_2), HAL_LL_ADC_CHANNEL_12},
    #endif
    #ifdef ADC2_PC0_CH6
    {PC0, ADC2_BASE_ADDRESS, hal_ll_adc_module_num(ADC_MODULE_2), HAL_LL_ADC_CHANNEL_6},
    #endif
    #ifdef ADC2_PC1_CH7
    {PC1, ADC2_BASE_ADDRESS, hal_ll_adc_module_num(ADC_MODULE_2), HAL_LL_ADC_CHANNEL_7},
    #endif
    #ifdef ADC2_PC2_CH8
    {PC2, ADC2_BASE_ADDRESS, hal_ll_adc_module_num(ADC_MODULE_2), HAL_LL_ADC_CHANNEL_8},
    #endif
    #ifdef ADC2_PC3_CH9
    {PC3, ADC2_BASE_ADDRESS, hal_ll_adc_module_num(ADC_MODULE_2), HAL_LL_ADC_CHANNEL_9},
    #endif
    #ifdef ADC2_PC4_CH5
    {PC4, ADC2_BASE_ADDRESS, hal_ll_adc_module_num(ADC_MODULE_2), HAL_LL_ADC_CHANNEL_5},
    #endif
    #ifdef ADC2_PC5_CH11
    {PC5, ADC2_BASE_ADDRESS, hal_ll_adc_module_num(ADC_MODULE_2), HAL_LL_ADC_CHANNEL_11},
    #endif
    #ifdef ADC2_PF1_CH10
    {PF1, ADC2_BASE_ADDRESS, hal_ll_adc_module_num(ADC_MODULE_2), HAL_LL_ADC_CHANNEL_10},
    #endif
    #ifdef ADC3_PB0_CH12
    {PB0, ADC3_BASE_ADDRESS, hal_ll_adc_module_num(ADC_MODULE_3), HAL_LL_ADC_CHANNEL_12},
    #endif
    #ifdef ADC3_PB13_CH5
    {PB13, ADC3_BASE_ADDRESS, hal_ll_adc_module_num(ADC_MODULE_3), HAL_LL_ADC_CHANNEL_5},
    #endif
    #ifdef ADC3_PB1_CH1
    {PB1, ADC3_BASE_ADDRESS, hal_ll_adc_module_num(ADC_MODULE_3), HAL_LL_ADC_CHANNEL_1},
    #endif
    #ifdef ADC3_PD10_CH7
    {PD10, ADC3_BASE_ADDRESS, hal_ll_adc_module_num(ADC_MODULE_3), HAL_LL_ADC_CHANNEL_7},
    #endif
    #ifdef ADC3_PE10_CH14
    {PE10, ADC3_BASE_ADDRESS, hal_ll_adc_module_num(ADC_MODULE_3), HAL_LL_ADC_CHANNEL_14},
    #endif
    #ifdef ADC3_PE11_CH15
    {PE11, ADC3_BASE_ADDRESS, hal_ll_adc_module_num(ADC_MODULE_3), HAL_LL_ADC_CHANNEL_15},
    #endif
    #ifdef ADC3_PE12_CH16
    {PE12, ADC3_BASE_ADDRESS, hal_ll_adc_module_num(ADC_MODULE_3), HAL_LL_ADC_CHANNEL_16},
    #endif
    #ifdef ADC3_PE13_CH3
    {PE13, ADC3_BASE_ADDRESS, hal_ll_adc_module_num(ADC_MODULE_3), HAL_LL_ADC_CHANNEL_3},
    #endif
    #ifdef ADC3_PE7_CH4
    {PE7, ADC3_BASE_ADDRESS, hal_ll_adc_module_num(ADC_MODULE_3), HAL_LL_ADC_CHANNEL_4},
    #endif
    #ifdef ADC3_PE8_CH6
    {PE8, ADC3_BASE_ADDRESS, hal_ll_adc_module_num(ADC_MODULE_3), HAL_LL_ADC_CHANNEL_6},
    #endif
    #ifdef ADC3_PE9_CH2
    {PE9, ADC3_BASE_ADDRESS, hal_ll_adc_module_num(ADC_MODULE_3), HAL_LL_ADC_CHANNEL_2},
    #endif
    #ifdef ADC3_PD11_CH8
    {PD11, ADC3_BASE_ADDRESS, hal_ll_adc_module_num(ADC_MODULE_3), HAL_LL_ADC_CHANNEL_8},
    #endif
    #ifdef ADC3_PD12_CH9
    {PD12, ADC3_BASE_ADDRESS, hal_ll_adc_module_num(ADC_MODULE_3), HAL_LL_ADC_CHANNEL_9},
    #endif
    #ifdef ADC3_PD13_CH10
    {PD13, ADC3_BASE_ADDRESS, hal_ll_adc_module_num(ADC_MODULE_3), HAL_LL_ADC_CHANNEL_10},
    #endif
    #ifdef ADC3_PD14_CH11
    {PD14, ADC3_BASE_ADDRESS, hal_ll_adc_module_num(ADC_MODULE_3), HAL_LL_ADC_CHANNEL_11},
    #endif
    {HAL_LL_PIN_NC, HAL_LL_MODULE_ERROR, HAL_LL_PIN_NC, HAL_LL_CHANNEL_ERROR}
};

#ifdef __cplusplus
}
#endif

#endif // _HAL_LL_ADC_PIN_MAP_H_
// ------------------------------------------------------------------------- END
