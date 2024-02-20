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

/*!< @brief Macro defining `weak` attribute */
#define __weak __attribute__((weak))
/*!< @brief Helper macro for getting adequate module index number */
#define hal_ll_adc_module_num(_module_num) (_module_num - 1)

/*!< ADC module base addresses. */
#ifdef ADC_MODULE_0
static const hal_ll_base_addr_t HAL_LL_ADC0_BASE_ADDR = 0x4003B000;
#ifdef MKV5xHSADC
static const hal_ll_base_addr_t HAL_LL_HSADC0_BASE_ADDR = 0x4005C000;
#endif
#endif

#ifdef ADC_MODULE_1
static const hal_ll_base_addr_t HAL_LL_ADC1_BASE_ADDR = 0x400BB000;
#ifdef MKV5xHSADC
static const hal_ll_base_addr_t HAL_LL_HSADC1_BASE_ADDR = 0x400DC000;
#endif
#endif

/**
 * ADC channels and subchannels.
 */
typedef enum {
    // Channels.
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
    // Subchannels.
    HAL_LL_ADC_CHANNEL_SUB_DEFAULT = 0,
    HAL_LL_ADC_CHANNEL_SUB_A,
    HAL_LL_ADC_CHANNEL_SUB_B,
    // Mux channels
    HAL_LL_ADC_CHANNEL_MUX0_A,
    HAL_LL_ADC_CHANNEL_MUX1_A,
    HAL_LL_ADC_CHANNEL_MUX0_B,
    HAL_LL_ADC_CHANNEL_MUX1_B,
    HAL_LL_ADC_CHANNEL_MUX0_C,
    HAL_LL_ADC_CHANNEL_MUX1_C,
    HAL_LL_ADC_CHANNEL_MUX0_D,
    HAL_LL_ADC_CHANNEL_MUX1_D,
    HAL_LL_ADC_CHANNEL_MUX0_E,
    HAL_LL_ADC_CHANNEL_MUX1_E,
    HAL_LL_ADC_CHANNEL_MUX0_F,
    HAL_LL_ADC_CHANNEL_MUX1_F,
    HAL_LL_ADC_CHANNEL_MUX0_G,
    HAL_LL_ADC_CHANNEL_MUX1_G,

    // Invalid channel value.
    HAL_LL_ADC_CHANNEL_NC = 0xFFFF
} hal_ll_adc_channel_t;

/*!< @brief ADC pin structure. */
typedef struct {
    hal_ll_pin_name_t pin;
    hal_ll_base_addr_t base;
    uint8_t module_index;
    hal_ll_adc_channel_t channel;
    hal_ll_adc_channel_t channel_subgroup;
    uint8_t sample;
} hal_ll_adc_pin_map_t;

/*!< ADC input pins. */
static const hal_ll_adc_pin_map_t _adc_map[] = {
    #ifdef ADC0_SE8_PB0_AF0
    {PB0, HAL_LL_ADC0_BASE_ADDR, hal_ll_adc_module_num(ADC_MODULE_0), HAL_LL_ADC_CHANNEL_8, HAL_LL_ADC_CHANNEL_SUB_DEFAULT, 0xFF},
    #endif
    #ifdef ADC0_SE9_PB1_AF0
    {PB1, HAL_LL_ADC0_BASE_ADDR, hal_ll_adc_module_num(ADC_MODULE_0), HAL_LL_ADC_CHANNEL_9, HAL_LL_ADC_CHANNEL_SUB_DEFAULT, 0xFF},
    #endif
    #ifdef ADC0_SE15_PC1_AF0
    {PC1, HAL_LL_ADC0_BASE_ADDR, hal_ll_adc_module_num(ADC_MODULE_0), HAL_LL_ADC_CHANNEL_15, HAL_LL_ADC_CHANNEL_SUB_DEFAULT, 0xFF},
    #endif
    #ifdef ADC0_SE4_PC2_AF0_SUB_B
    {PC2, HAL_LL_ADC0_BASE_ADDR, hal_ll_adc_module_num(ADC_MODULE_0), HAL_LL_ADC_CHANNEL_4, HAL_LL_ADC_CHANNEL_SUB_B, 0xFF},
    #endif
    #ifdef ADC0_SE6_PD5_AF0_SUB_B
    {PD5, HAL_LL_ADC0_BASE_ADDR, hal_ll_adc_module_num(ADC_MODULE_0), HAL_LL_ADC_CHANNEL_6, HAL_LL_ADC_CHANNEL_SUB_B, 0xFF},
    #endif
    #ifdef ADC0_SE7_PD6_AF0_SUB_B
    {PD6, HAL_LL_ADC0_BASE_ADDR, hal_ll_adc_module_num(ADC_MODULE_0), HAL_LL_ADC_CHANNEL_7, HAL_LL_ADC_CHANNEL_SUB_B, 0xFF},
    #endif
    #ifdef ADC0_SE12_PB2_AF0
    {PB2, HAL_LL_ADC0_BASE_ADDR, hal_ll_adc_module_num(ADC_MODULE_0), HAL_LL_ADC_CHANNEL_12, HAL_LL_ADC_CHANNEL_SUB_DEFAULT, 0xFF},
    #endif
    #ifdef ADC0_SE13_PB3_AF0
    {PB3, HAL_LL_ADC0_BASE_ADDR, hal_ll_adc_module_num(ADC_MODULE_0), HAL_LL_ADC_CHANNEL_13, HAL_LL_ADC_CHANNEL_SUB_DEFAULT, 0xFF},
    #endif
    #ifdef ADC0_SE14_PC0_AF0
    {PC0, HAL_LL_ADC0_BASE_ADDR, hal_ll_adc_module_num(ADC_MODULE_0), HAL_LL_ADC_CHANNEL_14, HAL_LL_ADC_CHANNEL_SUB_DEFAULT, 0xFF},
    #endif
    #ifdef ADC0_SE5_PD1_AF0_SUB_B
    {PD1, HAL_LL_ADC0_BASE_ADDR, hal_ll_adc_module_num(ADC_MODULE_0), HAL_LL_ADC_CHANNEL_5, HAL_LL_ADC_CHANNEL_SUB_B, 0xFF},
    #endif
    #ifdef ADC1_SE4_PE0_AF0
    {PE0, HAL_LL_ADC1_BASE_ADDR, hal_ll_adc_module_num(ADC_MODULE_1), HAL_LL_ADC_CHANNEL_4, HAL_LL_ADC_CHANNEL_SUB_DEFAULT, 0xFF},
    #endif
    #ifdef ADC1_SE5_PE1_AF0
    {PE1, HAL_LL_ADC1_BASE_ADDR, hal_ll_adc_module_num(ADC_MODULE_1), HAL_LL_ADC_CHANNEL_5, HAL_LL_ADC_CHANNEL_SUB_DEFAULT, 0xFF},
    #endif
    #ifdef ADC1_SE8_PB0_AF0
    {PB0, HAL_LL_ADC1_BASE_ADDR, hal_ll_adc_module_num(ADC_MODULE_1), HAL_LL_ADC_CHANNEL_8, HAL_LL_ADC_CHANNEL_SUB_DEFAULT, 0xFF},
    #endif
    #ifdef ADC1_SE9_PB1_AF0
    {PB1, HAL_LL_ADC1_BASE_ADDR, hal_ll_adc_module_num(ADC_MODULE_1), HAL_LL_ADC_CHANNEL_9, HAL_LL_ADC_CHANNEL_SUB_DEFAULT, 0xFF},
    #endif
    #ifdef ADC1_SE4_PC8_AF0_SUB_B
    {PC8, HAL_LL_ADC1_BASE_ADDR, hal_ll_adc_module_num(ADC_MODULE_1), HAL_LL_ADC_CHANNEL_4, HAL_LL_ADC_CHANNEL_SUB_B, 0xFF},
    #endif
    #ifdef ADC1_SE5_PC9_AF0_SUB_B
    {PC9, HAL_LL_ADC1_BASE_ADDR, hal_ll_adc_module_num(ADC_MODULE_1), HAL_LL_ADC_CHANNEL_5, HAL_LL_ADC_CHANNEL_SUB_B, 0xFF},
    #endif
    #ifdef ADC1_SE6_PC10_AF0_SUB_B
    {PC10, HAL_LL_ADC1_BASE_ADDR, hal_ll_adc_module_num(ADC_MODULE_1), HAL_LL_ADC_CHANNEL_6, HAL_LL_ADC_CHANNEL_SUB_B, 0xFF},
    #endif
    #ifdef ADC1_SE7_PC11_AF0_SUB_B
    {PC11, HAL_LL_ADC1_BASE_ADDR, hal_ll_adc_module_num(ADC_MODULE_1), HAL_LL_ADC_CHANNEL_7, HAL_LL_ADC_CHANNEL_SUB_B, 0xFF},
    #endif
    #ifdef ADC1_SE6_PE2_AF0
    {PE2, HAL_LL_ADC1_BASE_ADDR, hal_ll_adc_module_num(ADC_MODULE_1), HAL_LL_ADC_CHANNEL_6, HAL_LL_ADC_CHANNEL_SUB_DEFAULT, 0xFF},
    #endif
    #ifdef ADC1_SE7_PE3_AF0
    {PE3, HAL_LL_ADC1_BASE_ADDR, hal_ll_adc_module_num(ADC_MODULE_1), HAL_LL_ADC_CHANNEL_7, HAL_LL_ADC_CHANNEL_SUB_DEFAULT, 0xFF},
    #endif
    #ifdef ADC0_SE17_PE24_AF0
    {PE24, HAL_LL_ADC0_BASE_ADDR, hal_ll_adc_module_num(ADC_MODULE_0), HAL_LL_ADC_CHANNEL_17, HAL_LL_ADC_CHANNEL_SUB_DEFAULT, 0xFF},
    #endif
    #ifdef ADC0_SE18_PE25_AF0
    {PE25, HAL_LL_ADC0_BASE_ADDR, hal_ll_adc_module_num(ADC_MODULE_0), HAL_LL_ADC_CHANNEL_18, HAL_LL_ADC_CHANNEL_SUB_DEFAULT, 0xFF},
    #endif
    #ifdef ADC1_SE17_PA17_AF0
    {PA17, HAL_LL_ADC1_BASE_ADDR, hal_ll_adc_module_num(ADC_MODULE_1), HAL_LL_ADC_CHANNEL_17, HAL_LL_ADC_CHANNEL_SUB_DEFAULT, 0xFF},
    #endif
    #ifdef ADC1_SE14_PB10_AF0
    {PB10, HAL_LL_ADC1_BASE_ADDR, hal_ll_adc_module_num(ADC_MODULE_1), HAL_LL_ADC_CHANNEL_14, HAL_LL_ADC_CHANNEL_SUB_DEFAULT, 0xFF},
    #endif
    #ifdef ADC1_SE15_PB11_AF0
    {PB11, HAL_LL_ADC1_BASE_ADDR, hal_ll_adc_module_num(ADC_MODULE_1), HAL_LL_ADC_CHANNEL_15, HAL_LL_ADC_CHANNEL_SUB_DEFAULT, 0xFF},
    #endif
    #ifdef ADC0_SE10_PA7_AF0
    {PA7, HAL_LL_ADC0_BASE_ADDR, hal_ll_adc_module_num(ADC_MODULE_0), HAL_LL_ADC_CHANNEL_10, HAL_LL_ADC_CHANNEL_SUB_DEFAULT, 0xFF},
    #endif
    #ifdef ADC0_SE11_PA8_AF0
    {PA8, HAL_LL_ADC0_BASE_ADDR, hal_ll_adc_module_num(ADC_MODULE_0), HAL_LL_ADC_CHANNEL_11, HAL_LL_ADC_CHANNEL_SUB_DEFAULT, 0xFF},
    #endif
    #ifdef ADC1_SE10_PB4_AF0
    {PB4, HAL_LL_ADC1_BASE_ADDR, hal_ll_adc_module_num(ADC_MODULE_1), HAL_LL_ADC_CHANNEL_10, HAL_LL_ADC_CHANNEL_SUB_DEFAULT, 0xFF},
    #endif
    #ifdef ADC1_SE11_PB5_AF0
    {PB5, HAL_LL_ADC1_BASE_ADDR, hal_ll_adc_module_num(ADC_MODULE_1), HAL_LL_ADC_CHANNEL_11, HAL_LL_ADC_CHANNEL_SUB_DEFAULT, 0xFF},
    #endif
    #ifdef ADC1_SE12_PB6_AF0
    {PB6, HAL_LL_ADC1_BASE_ADDR, hal_ll_adc_module_num(ADC_MODULE_1), HAL_LL_ADC_CHANNEL_12, HAL_LL_ADC_CHANNEL_SUB_DEFAULT, 0xFF},
    #endif
    #ifdef ADC1_SE13_PB7_AF0
    {PB7, HAL_LL_ADC1_BASE_ADDR, hal_ll_adc_module_num(ADC_MODULE_1), HAL_LL_ADC_CHANNEL_13, HAL_LL_ADC_CHANNEL_SUB_DEFAULT, 0xFF},
    #endif
    #ifdef ADC0_SE4_PE16_AF0
    {PE16, HAL_LL_ADC0_BASE_ADDR, hal_ll_adc_module_num(ADC_MODULE_0), HAL_LL_ADC_CHANNEL_4, HAL_LL_ADC_CHANNEL_SUB_DEFAULT, 0xFF},
    #endif
    #ifdef ADC0_SE5_PE17_AF0
    {PE17, HAL_LL_ADC0_BASE_ADDR, hal_ll_adc_module_num(ADC_MODULE_0), HAL_LL_ADC_CHANNEL_5, HAL_LL_ADC_CHANNEL_SUB_DEFAULT, 0xFF},
    #endif
    #ifdef ADC0_SE6_PE18_AF0
    {PE18, HAL_LL_ADC0_BASE_ADDR, hal_ll_adc_module_num(ADC_MODULE_0), HAL_LL_ADC_CHANNEL_6, HAL_LL_ADC_CHANNEL_SUB_DEFAULT, 0xFF},
    #endif
    #ifdef ADC0_SE7_PE19_AF0
    {PE19, HAL_LL_ADC0_BASE_ADDR, hal_ll_adc_module_num(ADC_MODULE_0), HAL_LL_ADC_CHANNEL_7, HAL_LL_ADC_CHANNEL_SUB_DEFAULT, 0xFF},
    #endif
    #ifdef ADC0_CH0_PE16_AF0
    {PE16, HAL_LL_ADC0_BASE_ADDR, hal_ll_adc_module_num(ADC_MODULE_0), HAL_LL_ADC_CHANNEL_0, HAL_LL_ADC_CHANNEL_SUB_DEFAULT, 0xFF},
    #endif
    #ifdef ADC0_CH1_PE17_AF0
    {PE17, HAL_LL_ADC0_BASE_ADDR, hal_ll_adc_module_num(ADC_MODULE_0), HAL_LL_ADC_CHANNEL_1, HAL_LL_ADC_CHANNEL_SUB_DEFAULT, 0xFF},
    #endif
    #ifdef ADC1_CH0_PE18_AF0
    {PE18, HAL_LL_ADC1_BASE_ADDR, hal_ll_adc_module_num(ADC_MODULE_1), HAL_LL_ADC_CHANNEL_0, HAL_LL_ADC_CHANNEL_SUB_DEFAULT, 0xFF},
    #endif
    #ifdef ADC1_CH1_PE19_AF0
    {PE19, HAL_LL_ADC1_BASE_ADDR, hal_ll_adc_module_num(ADC_MODULE_1), HAL_LL_ADC_CHANNEL_1, HAL_LL_ADC_CHANNEL_SUB_DEFAULT, 0xFF},
    #endif
    #ifdef ADC0_CH6_PE20_AF0_MUX0_B
    {PE20, HAL_LL_ADC0_BASE_ADDR, hal_ll_adc_module_num(ADC_MODULE_0), HAL_LL_ADC_CHANNEL_6, HAL_LL_ADC_CHANNEL_MUX0_B, 0xFF},
    #endif
    #ifdef ADC0_CH7_PE21_AF0_MUX1_B
    {PE21, HAL_LL_ADC0_BASE_ADDR, hal_ll_adc_module_num(ADC_MODULE_0), HAL_LL_ADC_CHANNEL_7, HAL_LL_ADC_CHANNEL_MUX1_B, 0xFF},
    #endif
    #ifdef ADC0_CH4_PE29_AF0
    {PE29, HAL_LL_ADC0_BASE_ADDR, hal_ll_adc_module_num(ADC_MODULE_0), HAL_LL_ADC_CHANNEL_4, HAL_LL_ADC_CHANNEL_SUB_DEFAULT, 0xFF},
    #endif
    #ifdef ADC0_CH5_PE30_AF0
    {PE30, HAL_LL_ADC0_BASE_ADDR, hal_ll_adc_module_num(ADC_MODULE_0), HAL_LL_ADC_CHANNEL_5, HAL_LL_ADC_CHANNEL_SUB_DEFAULT, 0xFF},
    #endif
    #ifdef ADC1_CH4_PE24_AF0
    {PE24, HAL_LL_ADC1_BASE_ADDR, hal_ll_adc_module_num(ADC_MODULE_1), HAL_LL_ADC_CHANNEL_4, HAL_LL_ADC_CHANNEL_SUB_DEFAULT, 0xFF},
    #endif
    #ifdef ADC1_CH5_PE25_AF0
    {PE25, HAL_LL_ADC1_BASE_ADDR, hal_ll_adc_module_num(ADC_MODULE_1), HAL_LL_ADC_CHANNEL_5, HAL_LL_ADC_CHANNEL_SUB_DEFAULT, 0xFF},
    #endif
    #ifdef ADC1_CH2_PB0_AF0
    {PB0, HAL_LL_ADC1_BASE_ADDR, hal_ll_adc_module_num(ADC_MODULE_1), HAL_LL_ADC_CHANNEL_2, HAL_LL_ADC_CHANNEL_SUB_DEFAULT, 0xFF},
    #endif
    #ifdef ADC1_CH3_PB1_AF0
    {PB1, HAL_LL_ADC1_BASE_ADDR, hal_ll_adc_module_num(ADC_MODULE_1), HAL_LL_ADC_CHANNEL_3, HAL_LL_ADC_CHANNEL_SUB_DEFAULT, 0xFF},
    #endif
    #ifdef ADC0_CH6_PB2_AF0_MUX0_E
    {PB2, HAL_LL_ADC0_BASE_ADDR, hal_ll_adc_module_num(ADC_MODULE_0), HAL_LL_ADC_CHANNEL_6, HAL_LL_ADC_CHANNEL_MUX0_E, 0xFF},
    #endif
    #ifdef ADC1_CH7_PB3_AF0_MUX1_E
    {PB3, HAL_LL_ADC1_BASE_ADDR, hal_ll_adc_module_num(ADC_MODULE_1), HAL_LL_ADC_CHANNEL_7, HAL_LL_ADC_CHANNEL_MUX1_E, 0xFF},
    #endif
    #ifdef ADC1_CH6_PC0_AF0_MUX0_B
    {PC0, HAL_LL_ADC1_BASE_ADDR, hal_ll_adc_module_num(ADC_MODULE_1), HAL_LL_ADC_CHANNEL_6, HAL_LL_ADC_CHANNEL_MUX0_B, 0xFF},
    #endif
    #ifdef ADC1_CH7_PC1_AF0_MUX1_B
    {PC1, HAL_LL_ADC1_BASE_ADDR, hal_ll_adc_module_num(ADC_MODULE_1), HAL_LL_ADC_CHANNEL_7, HAL_LL_ADC_CHANNEL_MUX1_B, 0xFF},
    #endif
    #ifdef ADC1_CH6_PC2_AF0_MUX0_C
    {PC2, HAL_LL_ADC1_BASE_ADDR, hal_ll_adc_module_num(ADC_MODULE_1), HAL_LL_ADC_CHANNEL_6, HAL_LL_ADC_CHANNEL_MUX0_C, 0xFF},
    #endif
    #ifdef ADC0_CH7_PD1_AF0_MUX1_F
    {PD1, HAL_LL_ADC0_BASE_ADDR, hal_ll_adc_module_num(ADC_MODULE_0), HAL_LL_ADC_CHANNEL_7, HAL_LL_ADC_CHANNEL_MUX1_F, 0xFF},
    #endif
    #ifdef ADC0_CH6_PD5_AF0_MUX0_G
    {PD5, HAL_LL_ADC0_BASE_ADDR, hal_ll_adc_module_num(ADC_MODULE_0), HAL_LL_ADC_CHANNEL_6, HAL_LL_ADC_CHANNEL_MUX0_G, 0xFF},
    #endif
    #ifdef ADC0_CH7_PD6_AF0_MUX1_G
    {PD6, HAL_LL_ADC0_BASE_ADDR, hal_ll_adc_module_num(ADC_MODULE_0), HAL_LL_ADC_CHANNEL_7, HAL_LL_ADC_CHANNEL_MUX1_G, 0xFF},
    #endif
    #ifdef ADC1_CH6_PE0_AF0_MUX0_F
    {PE0, HAL_LL_ADC1_BASE_ADDR, hal_ll_adc_module_num(ADC_MODULE_1), HAL_LL_ADC_CHANNEL_6, HAL_LL_ADC_CHANNEL_MUX0_F, 0xFF},
    #endif
    #ifdef ADC1_CH7_PE1_AF0_MUX1_F
    {PE1, HAL_LL_ADC1_BASE_ADDR, hal_ll_adc_module_num(ADC_MODULE_1), HAL_LL_ADC_CHANNEL_7, HAL_LL_ADC_CHANNEL_MUX1_F, 0xFF},
    #endif
    #ifdef ADC1_CH7_PC8_AF0_MUX1_C
    {PC8, HAL_LL_ADC1_BASE_ADDR, hal_ll_adc_module_num(ADC_MODULE_1), HAL_LL_ADC_CHANNEL_7, HAL_LL_ADC_CHANNEL_MUX1_C, 0xFF},
    #endif
    #ifdef ADC1_CH6_PC9_AF0_MUX0_D
    {PC9, HAL_LL_ADC1_BASE_ADDR, hal_ll_adc_module_num(ADC_MODULE_1), HAL_LL_ADC_CHANNEL_6, HAL_LL_ADC_CHANNEL_MUX0_D, 0xFF},
    #endif
    #ifdef ADC1_CH7_PC10_AF0_MUX1_D
    {PC10, HAL_LL_ADC1_BASE_ADDR, hal_ll_adc_module_num(ADC_MODULE_1), HAL_LL_ADC_CHANNEL_7, HAL_LL_ADC_CHANNEL_MUX1_D, 0xFF},
    #endif
    #ifdef ADC1_CH6_PC11_AF0_MUX0_E
    {PC11, HAL_LL_ADC1_BASE_ADDR, hal_ll_adc_module_num(ADC_MODULE_1), HAL_LL_ADC_CHANNEL_6, HAL_LL_ADC_CHANNEL_MUX0_E, 0xFF},
    #endif
    #ifdef ADC1_CH6_PE2_AF0_MUX0_G
    {PE2, HAL_LL_ADC1_BASE_ADDR, hal_ll_adc_module_num(ADC_MODULE_1), HAL_LL_ADC_CHANNEL_6, HAL_LL_ADC_CHANNEL_MUX0_G, 0xFF},
    #endif
    #ifdef ADC1_CH7_PE3_AF0_MUX1_G
    {PE3, HAL_LL_ADC1_BASE_ADDR, hal_ll_adc_module_num(ADC_MODULE_1), HAL_LL_ADC_CHANNEL_7, HAL_LL_ADC_CHANNEL_MUX1_G, 0xFF},
    #endif
    #ifdef ADC0_CH7_PA17_AF0_MUX1_E
    {PA17, HAL_LL_ADC0_BASE_ADDR, hal_ll_adc_module_num(ADC_MODULE_0), HAL_LL_ADC_CHANNEL_7, HAL_LL_ADC_CHANNEL_MUX1_E, 0xFF},
    #endif
    #ifdef ADC1_CH6_PB10_AF0_MUX0_A
    {PB10, HAL_LL_ADC1_BASE_ADDR, hal_ll_adc_module_num(ADC_MODULE_1), HAL_LL_ADC_CHANNEL_6, HAL_LL_ADC_CHANNEL_MUX0_A, 0xFF},
    #endif
    #ifdef ADC1_CH7_PB11_AF0_MUX1_A
    {PB11, HAL_LL_ADC1_BASE_ADDR, hal_ll_adc_module_num(ADC_MODULE_1), HAL_LL_ADC_CHANNEL_7, HAL_LL_ADC_CHANNEL_MUX1_A, 0xFF},
    #endif
    #ifdef ADC0_SE2_PE4_AF0
    {PE4, HAL_LL_ADC0_BASE_ADDR, hal_ll_adc_module_num(ADC_MODULE_0), HAL_LL_ADC_CHANNEL_2, HAL_LL_ADC_CHANNEL_SUB_DEFAULT, 0xFF},
    #endif
    #ifdef ADC0_SE10_PE5_AF0
    {PE5, HAL_LL_ADC0_BASE_ADDR, hal_ll_adc_module_num(ADC_MODULE_0), HAL_LL_ADC_CHANNEL_10, HAL_LL_ADC_CHANNEL_SUB_DEFAULT, 0xFF},
    #endif
    #ifdef ADC0_SE4_PE6_AF0
    {PE6, HAL_LL_ADC0_BASE_ADDR, hal_ll_adc_module_num(ADC_MODULE_0), HAL_LL_ADC_CHANNEL_4, HAL_LL_ADC_CHANNEL_SUB_DEFAULT, 0xFF},
    #endif
    #ifdef ADC0_SE1_PE16_AF0
    {PE16, HAL_LL_ADC0_BASE_ADDR, hal_ll_adc_module_num(ADC_MODULE_0), HAL_LL_ADC_CHANNEL_1, HAL_LL_ADC_CHANNEL_SUB_DEFAULT, 0xFF},
    #endif
    #ifdef ADC0_SE9_PE17_AF0
    {PE17, HAL_LL_ADC0_BASE_ADDR, hal_ll_adc_module_num(ADC_MODULE_0), HAL_LL_ADC_CHANNEL_9, HAL_LL_ADC_CHANNEL_SUB_DEFAULT, 0xFF},
    #endif
    #ifdef ADC0_SE5_PE18_AF0
    {PE18, HAL_LL_ADC0_BASE_ADDR, hal_ll_adc_module_num(ADC_MODULE_0), HAL_LL_ADC_CHANNEL_5, HAL_LL_ADC_CHANNEL_SUB_DEFAULT, 0xFF},
    #endif
    #ifdef ADC0_SE6_PE19_AF0
    {PE19, HAL_LL_ADC0_BASE_ADDR, hal_ll_adc_module_num(ADC_MODULE_0), HAL_LL_ADC_CHANNEL_6, HAL_LL_ADC_CHANNEL_SUB_DEFAULT, 0xFF},
    #endif
    #ifdef ADC0_SE5_PE20_AF0_SUB_B
    {PE20, HAL_LL_ADC0_BASE_ADDR, hal_ll_adc_module_num(ADC_MODULE_0), HAL_LL_ADC_CHANNEL_5, HAL_LL_ADC_CHANNEL_SUB_B, 0xFF},
    #endif
    #ifdef HSADC0B_CH16_PE0_AF0
    {PE0, HAL_LL_HSADC0_BASE_ADDR, hal_ll_adc_module_num(ADC_MODULE_0), HAL_LL_ADC_CHANNEL_16, HAL_LL_ADC_CHANNEL_SUB_B, 14},
    #endif
    #ifdef HSADC1A_CH0_PE0_AF0
    {PE0, HAL_LL_HSADC1_BASE_ADDR, hal_ll_adc_module_num(ADC_MODULE_1), HAL_LL_ADC_CHANNEL_0, HAL_LL_ADC_CHANNEL_SUB_A, 0},
    #endif
    #ifdef HSADC0B_CH17_PE1_AF0
    {PE1, HAL_LL_HSADC0_BASE_ADDR, hal_ll_adc_module_num(ADC_MODULE_0), HAL_LL_ADC_CHANNEL_17, HAL_LL_ADC_CHANNEL_SUB_B, 15},
    #endif
    #ifdef HSADC1A_CH1_PE1_AF0
    {PE1, HAL_LL_HSADC1_BASE_ADDR, hal_ll_adc_module_num(ADC_MODULE_1), HAL_LL_ADC_CHANNEL_1, HAL_LL_ADC_CHANNEL_SUB_A, 1},
    #endif
    #ifdef HSADC0B_CH10_PE2_AF0
    {PE2, HAL_LL_HSADC0_BASE_ADDR, hal_ll_adc_module_num(ADC_MODULE_0), HAL_LL_ADC_CHANNEL_10, HAL_LL_ADC_CHANNEL_SUB_B, 14},
    #endif
    #ifdef HSADC1B_CH0_PE2_AF0
    {PE2, HAL_LL_HSADC1_BASE_ADDR, hal_ll_adc_module_num(ADC_MODULE_1), HAL_LL_ADC_CHANNEL_0, HAL_LL_ADC_CHANNEL_SUB_B, 8},
    #endif
    #ifdef HSADC0B_CH11_PE3_AF0
    {PE3, HAL_LL_HSADC0_BASE_ADDR, hal_ll_adc_module_num(ADC_MODULE_0), HAL_LL_ADC_CHANNEL_11, HAL_LL_ADC_CHANNEL_SUB_B, 15},
    #endif
    #ifdef HSADC1B_CH1_PE3_AF0
    {PE3, HAL_LL_HSADC1_BASE_ADDR, hal_ll_adc_module_num(ADC_MODULE_1), HAL_LL_ADC_CHANNEL_1, HAL_LL_ADC_CHANNEL_SUB_B, 9},
    #endif
    #ifdef HSADC1A_CH4_PE4_AF0
    {PE4, HAL_LL_HSADC1_BASE_ADDR, hal_ll_adc_module_num(ADC_MODULE_1), HAL_LL_ADC_CHANNEL_4, HAL_LL_ADC_CHANNEL_SUB_A, 4},
    #endif
    #ifdef HSADC1A_CH5_PE5_AF0
    {PE5, HAL_LL_HSADC1_BASE_ADDR, hal_ll_adc_module_num(ADC_MODULE_1), HAL_LL_ADC_CHANNEL_5, HAL_LL_ADC_CHANNEL_SUB_A, 5},
    #endif
    #ifdef HSADC1B_CH7_PE6_AF0
    {PE6, HAL_LL_HSADC1_BASE_ADDR, hal_ll_adc_module_num(ADC_MODULE_1), HAL_LL_ADC_CHANNEL_7, HAL_LL_ADC_CHANNEL_SUB_B, 15},
    #endif
    #ifdef HSADC0A_CH0_PE16_AF0
    {PE16, HAL_LL_HSADC0_BASE_ADDR, hal_ll_adc_module_num(ADC_MODULE_0), HAL_LL_ADC_CHANNEL_0, HAL_LL_ADC_CHANNEL_SUB_A, 0},
    #endif
    #ifdef HSADC0A_CH1_PE17_AF0
    {PE17, HAL_LL_HSADC0_BASE_ADDR, hal_ll_adc_module_num(ADC_MODULE_0), HAL_LL_ADC_CHANNEL_1, HAL_LL_ADC_CHANNEL_SUB_A, 1},
    #endif
    #ifdef HSADC0B_CH0_PE18_AF0
    {PE18, HAL_LL_HSADC0_BASE_ADDR, hal_ll_adc_module_num(ADC_MODULE_0), HAL_LL_ADC_CHANNEL_0, HAL_LL_ADC_CHANNEL_SUB_B, 8},
    #endif
    #ifdef HSADC0B_CH1_PE19_AF0
    {PE19, HAL_LL_HSADC0_BASE_ADDR, hal_ll_adc_module_num(ADC_MODULE_0), HAL_LL_ADC_CHANNEL_1, HAL_LL_ADC_CHANNEL_SUB_B, 9},
    #endif
    #ifdef HSADC0A_CH8_PE20_AF0
    {PE20, HAL_LL_HSADC0_BASE_ADDR, hal_ll_adc_module_num(ADC_MODULE_0), HAL_LL_ADC_CHANNEL_8, HAL_LL_ADC_CHANNEL_SUB_A, 6},
    #endif
    #ifdef HSADC0A_CH9_PE21_AF0
    {PE21, HAL_LL_HSADC0_BASE_ADDR, hal_ll_adc_module_num(ADC_MODULE_0), HAL_LL_ADC_CHANNEL_9, HAL_LL_ADC_CHANNEL_SUB_A, 7},
    #endif
    #ifdef HSADC1A_CH7_PE21_AF0
    {PE21, HAL_LL_HSADC1_BASE_ADDR, hal_ll_adc_module_num(ADC_MODULE_1), HAL_LL_ADC_CHANNEL_7, HAL_LL_ADC_CHANNEL_SUB_A, 7},
    #endif
    #ifdef HSADC0A_CH4_PE29_AF0
    {PE29, HAL_LL_HSADC0_BASE_ADDR, hal_ll_adc_module_num(ADC_MODULE_0), HAL_LL_ADC_CHANNEL_4, HAL_LL_ADC_CHANNEL_SUB_A, 4},
    #endif
    #ifdef HSADC0A_CH5_PE30_AF0
    {PE30, HAL_LL_HSADC0_BASE_ADDR, hal_ll_adc_module_num(ADC_MODULE_0), HAL_LL_ADC_CHANNEL_5, HAL_LL_ADC_CHANNEL_SUB_A, 5},
    #endif
    #ifdef HSADC0B_CH4_PE24_AF0
    {PE24, HAL_LL_HSADC0_BASE_ADDR, hal_ll_adc_module_num(ADC_MODULE_0), HAL_LL_ADC_CHANNEL_4, HAL_LL_ADC_CHANNEL_SUB_B, 12},
    #endif
    #ifdef HSADC1B_CH4_PE24_AF0
    {PE24, HAL_LL_HSADC1_BASE_ADDR, hal_ll_adc_module_num(ADC_MODULE_1), HAL_LL_ADC_CHANNEL_4, HAL_LL_ADC_CHANNEL_SUB_B, 12},
    #endif
    #ifdef HSADC0B_CH5_PE25_AF0
    {PE25, HAL_LL_HSADC0_BASE_ADDR, hal_ll_adc_module_num(ADC_MODULE_0), HAL_LL_ADC_CHANNEL_5, HAL_LL_ADC_CHANNEL_SUB_B, 13},
    #endif
    #ifdef HSADC1B_CH5_PE25_AF0
    {PE25, HAL_LL_HSADC1_BASE_ADDR, hal_ll_adc_module_num(ADC_MODULE_1), HAL_LL_ADC_CHANNEL_5, HAL_LL_ADC_CHANNEL_SUB_B, 13},
    #endif
    #ifdef HSADC0A_CH15_PA17_AF0
    {PA17, HAL_LL_HSADC0_BASE_ADDR, hal_ll_adc_module_num(ADC_MODULE_0), HAL_LL_ADC_CHANNEL_15, HAL_LL_ADC_CHANNEL_SUB_A, 7},
    #endif
    #ifdef HSADC0B_CH2_PB0_AF0
    {PB0, HAL_LL_HSADC0_BASE_ADDR, hal_ll_adc_module_num(ADC_MODULE_0), HAL_LL_ADC_CHANNEL_2, HAL_LL_ADC_CHANNEL_SUB_B, 10},
    #endif
    #ifdef HSADC0B_CH3_PB1_AF0
    {PB1, HAL_LL_HSADC0_BASE_ADDR, hal_ll_adc_module_num(ADC_MODULE_0), HAL_LL_ADC_CHANNEL_3, HAL_LL_ADC_CHANNEL_SUB_B, 11},
    #endif
    #ifdef HSADC0A_CH14_PB2_AF0
    {PB2, HAL_LL_HSADC0_BASE_ADDR, hal_ll_adc_module_num(ADC_MODULE_0), HAL_LL_ADC_CHANNEL_14, HAL_LL_ADC_CHANNEL_SUB_A, 6},
    #endif
    #ifdef HSADC0B_CH15_PB3_AF0
    {PB3, HAL_LL_HSADC0_BASE_ADDR, hal_ll_adc_module_num(ADC_MODULE_0), HAL_LL_ADC_CHANNEL_15, HAL_LL_ADC_CHANNEL_SUB_B, 15},
    #endif
    #ifdef HSADC0B_CH6_PB10_AF0
    {PB10, HAL_LL_HSADC0_BASE_ADDR, hal_ll_adc_module_num(ADC_MODULE_0), HAL_LL_ADC_CHANNEL_6, HAL_LL_ADC_CHANNEL_SUB_B, 14},
    #endif
    #ifdef HSADC0B_CH7_PB11_AF0
    {PB11, HAL_LL_HSADC0_BASE_ADDR, hal_ll_adc_module_num(ADC_MODULE_0), HAL_LL_ADC_CHANNEL_7, HAL_LL_ADC_CHANNEL_SUB_B, 15},
    #endif
    #ifdef HSADC0B_CH8_PC0_AF0
    {PC0, HAL_LL_HSADC0_BASE_ADDR, hal_ll_adc_module_num(ADC_MODULE_0), HAL_LL_ADC_CHANNEL_8, HAL_LL_ADC_CHANNEL_SUB_B, 14},
    #endif
    #ifdef HSADC0B_CH9_PC1_AF0
    {PC1, HAL_LL_HSADC0_BASE_ADDR, hal_ll_adc_module_num(ADC_MODULE_0), HAL_LL_ADC_CHANNEL_9, HAL_LL_ADC_CHANNEL_SUB_B, 15},
    #endif
    #ifdef HSADC1B_CH10_PC2_AF0
    {PC2, HAL_LL_HSADC1_BASE_ADDR, hal_ll_adc_module_num(ADC_MODULE_1), HAL_LL_ADC_CHANNEL_10, HAL_LL_ADC_CHANNEL_SUB_B, 14},
    #endif
    #ifdef HSADC1B_CH11_PC8_AF0
    {PC8, HAL_LL_HSADC1_BASE_ADDR, hal_ll_adc_module_num(ADC_MODULE_1), HAL_LL_ADC_CHANNEL_11, HAL_LL_ADC_CHANNEL_SUB_B, 15},
    #endif
    #ifdef HSADC1B_CH12_PC9_AF0
    {PC9, HAL_LL_HSADC1_BASE_ADDR, hal_ll_adc_module_num(ADC_MODULE_1), HAL_LL_ADC_CHANNEL_12, HAL_LL_ADC_CHANNEL_SUB_B, 14},
    #endif
    #ifdef HSADC1B_CH13_PC10_AF0
    {PC10, HAL_LL_HSADC1_BASE_ADDR, hal_ll_adc_module_num(ADC_MODULE_1), HAL_LL_ADC_CHANNEL_13, HAL_LL_ADC_CHANNEL_SUB_B, 15},
    #endif
    #ifdef HSADC1B_CH14_PC11_AF0
    {PC11, HAL_LL_HSADC1_BASE_ADDR, hal_ll_adc_module_num(ADC_MODULE_1), HAL_LL_ADC_CHANNEL_14, HAL_LL_ADC_CHANNEL_SUB_B, 14},
    #endif
    #ifdef HSADC1A_CH11_PD1_AF0
    {PD1, HAL_LL_HSADC1_BASE_ADDR, hal_ll_adc_module_num(ADC_MODULE_1), HAL_LL_ADC_CHANNEL_11, HAL_LL_ADC_CHANNEL_SUB_A, 7},
    #endif
    #ifdef HSADC1A_CH8_PD5_AF0
    {PD5, HAL_LL_HSADC1_BASE_ADDR, hal_ll_adc_module_num(ADC_MODULE_1), HAL_LL_ADC_CHANNEL_8, HAL_LL_ADC_CHANNEL_SUB_A, 6},
    #endif
    #ifdef HSADC1A_CH9_PD6_AF0
    {PD6, HAL_LL_HSADC1_BASE_ADDR, hal_ll_adc_module_num(ADC_MODULE_1), HAL_LL_ADC_CHANNEL_9, HAL_LL_ADC_CHANNEL_SUB_A, 7},
    #endif
    #ifdef ADC0_SE3_PE11_AF0
    {PE11, HAL_LL_ADC0_BASE_ADDR, hal_ll_adc_module_num(ADC_MODULE_0), HAL_LL_ADC_CHANNEL_3, HAL_LL_ADC_CHANNEL_SUB_DEFAULT, 0xFF},
    #endif
    #ifdef ADC0_SE11_PE12_AF0
    {PE12, HAL_LL_ADC0_BASE_ADDR, hal_ll_adc_module_num(ADC_MODULE_0), HAL_LL_ADC_CHANNEL_11, HAL_LL_ADC_CHANNEL_SUB_DEFAULT, 0xFF},
    #endif
    #ifdef ADC0_SE6_PB4_AF0_SUB_B
    {PB4, HAL_LL_ADC0_BASE_ADDR, hal_ll_adc_module_num(ADC_MODULE_0), HAL_LL_ADC_CHANNEL_6, HAL_LL_ADC_CHANNEL_SUB_B, 0xFF},
    #endif
    #ifdef ADC0_SE7_PB5_AF0_SUB_B
    {PB5, HAL_LL_ADC0_BASE_ADDR, hal_ll_adc_module_num(ADC_MODULE_0), HAL_LL_ADC_CHANNEL_7, HAL_LL_ADC_CHANNEL_SUB_B, 0xFF},
    #endif
    #ifdef HSADC1A_CH6_PE11_AF0
    {PE11, HAL_LL_HSADC1_BASE_ADDR, hal_ll_adc_module_num(ADC_MODULE_1), HAL_LL_ADC_CHANNEL_6, HAL_LL_ADC_CHANNEL_SUB_A, 6},
    #endif
    #ifdef HSADC1B_CH6_PE12_AF0
    {PE12, HAL_LL_HSADC1_BASE_ADDR, hal_ll_adc_module_num(ADC_MODULE_1), HAL_LL_ADC_CHANNEL_6, HAL_LL_ADC_CHANNEL_SUB_B, 14},
    #endif
    #ifdef HSADC1B_CH8_PA7_AF0
    {PA7, HAL_LL_HSADC1_BASE_ADDR, hal_ll_adc_module_num(ADC_MODULE_1), HAL_LL_ADC_CHANNEL_8, HAL_LL_ADC_CHANNEL_SUB_B, 14},
    #endif
    #ifdef HSADC1B_CH9_PA8_AF0
    {PA8, HAL_LL_HSADC1_BASE_ADDR, hal_ll_adc_module_num(ADC_MODULE_1), HAL_LL_ADC_CHANNEL_9, HAL_LL_ADC_CHANNEL_SUB_B, 15},
    #endif
    #ifdef HSADC1A_CH12_PB6_AF0
    {PB6, HAL_LL_HSADC1_BASE_ADDR, hal_ll_adc_module_num(ADC_MODULE_1), HAL_LL_ADC_CHANNEL_12, HAL_LL_ADC_CHANNEL_SUB_A, 6},
    #endif
    #ifdef HSADC1A_CH13_PB7_AF0
    {PB7, HAL_LL_HSADC1_BASE_ADDR, hal_ll_adc_module_num(ADC_MODULE_1), HAL_LL_ADC_CHANNEL_13, HAL_LL_ADC_CHANNEL_SUB_A, 7},
    #endif

    {HAL_LL_PIN_NC, HAL_LL_MODULE_ERROR, HAL_LL_PIN_NC, HAL_LL_CHANNEL_ERROR, HAL_LL_CHANNEL_ERROR, 0xFF}
};

#ifdef __cplusplus
}
#endif

#endif // _HAL_LL_ADC_PIN_MAP_H_
// ------------------------------------------------------------------------- END
