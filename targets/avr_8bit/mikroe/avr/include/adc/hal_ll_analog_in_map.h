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
 * @file  hal_ll_analog_in_map.h
 * @brief Macros used for setting pin analog functionality.
 */

#ifndef _HAL_LL_ANALOG_IN_MAP_H_
#define _HAL_LL_ANALOG_IN_MAP_H_

#ifdef __cplusplus
extern "C"{
#endif

#include "hal_ll_pin_names.h"

/*!< @brief Helper macro for getting adequate module index number */
#define hal_ll_adc_module_num(_module_num) (_module_num - 1)

/*!< @brief Macro defining `weak` attribute */
#define __weak __attribute__((weak))

enum channel {
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
    HAL_LL_ADC_CHANNEL_15
};

typedef struct {
    uint8_t pin;
    uint8_t module_index;
    uint8_t channel;
    uint16_t analog_in_register_addr;
} hal_ll_adc_pin_map_t;

static const hal_ll_adc_pin_map_t _adc_map[] = {
    //------------ BEGIN
    #ifdef ADC0_PF0_CH0
    {PF0, hal_ll_adc_module_num(ADC_MODULE_0), HAL_LL_ADC_CHANNEL_0, HAL_LL_ADC0_BASE_ADDRESS},
    #endif
    #ifdef ADC0_PF1_CH1
    {PF1, hal_ll_adc_module_num(ADC_MODULE_0), HAL_LL_ADC_CHANNEL_1, HAL_LL_ADC0_BASE_ADDRESS},
    #endif
    #ifdef ADC0_PF2_CH2
    {PF2, hal_ll_adc_module_num(ADC_MODULE_0), HAL_LL_ADC_CHANNEL_2, HAL_LL_ADC0_BASE_ADDRESS},
    #endif
    #ifdef ADC0_PF3_CH3
    {PF3, hal_ll_adc_module_num(ADC_MODULE_0), HAL_LL_ADC_CHANNEL_3, HAL_LL_ADC0_BASE_ADDRESS},
    #endif
    #ifdef ADC0_PF4_CH4
    {PF4, hal_ll_adc_module_num(ADC_MODULE_0), HAL_LL_ADC_CHANNEL_4, HAL_LL_ADC0_BASE_ADDRESS},
    #endif
    #ifdef ADC0_PF5_CH5
    {PF5, hal_ll_adc_module_num(ADC_MODULE_0), HAL_LL_ADC_CHANNEL_5, HAL_LL_ADC0_BASE_ADDRESS},
    #endif
    #ifdef ADC0_PF6_CH6
    {PF6, hal_ll_adc_module_num(ADC_MODULE_0), HAL_LL_ADC_CHANNEL_6, HAL_LL_ADC0_BASE_ADDRESS},
    #endif
    #ifdef ADC0_PF7_CH7
    {PF7, hal_ll_adc_module_num(ADC_MODULE_0), HAL_LL_ADC_CHANNEL_7, HAL_LL_ADC0_BASE_ADDRESS},
    #endif
    #ifdef ADC0_PK0_CH8
    {PK0, hal_ll_adc_module_num(ADC_MODULE_0), HAL_LL_ADC_CHANNEL_8, HAL_LL_ADC0_BASE_ADDRESS},
    #endif
    #ifdef ADC0_PK1_CH9
    {PK1, hal_ll_adc_module_num(ADC_MODULE_0), HAL_LL_ADC_CHANNEL_9, HAL_LL_ADC0_BASE_ADDRESS},
    #endif
    #ifdef ADC0_PK2_CH10
    {PK2, hal_ll_adc_module_num(ADC_MODULE_0), HAL_LL_ADC_CHANNEL_10, HAL_LL_ADC0_BASE_ADDRESS},
    #endif
    #ifdef ADC0_PK3_CH11
    {PK3, hal_ll_adc_module_num(ADC_MODULE_0), HAL_LL_ADC_CHANNEL_11, HAL_LL_ADC0_BASE_ADDRESS},
    #endif
    #ifdef ADC0_PK4_CH12
    {PK4, hal_ll_adc_module_num(ADC_MODULE_0), HAL_LL_ADC_CHANNEL_12, HAL_LL_ADC0_BASE_ADDRESS},
    #endif
    #ifdef ADC0_PK5_CH13
    {PK5, hal_ll_adc_module_num(ADC_MODULE_0), HAL_LL_ADC_CHANNEL_13, HAL_LL_ADC0_BASE_ADDRESS},
    #endif
    #ifdef ADC0_PK6_CH14
    {PK6, hal_ll_adc_module_num(ADC_MODULE_0), HAL_LL_ADC_CHANNEL_14, HAL_LL_ADC0_BASE_ADDRESS},
    #endif
    #ifdef ADC0_PK7_CH15
    {PK7, hal_ll_adc_module_num(ADC_MODULE_0), HAL_LL_ADC_CHANNEL_15, HAL_LL_ADC0_BASE_ADDRESS},
    #endif
    #ifdef ADC0_PA0_CH0
    {PA0, hal_ll_adc_module_num(ADC_MODULE_0), HAL_LL_ADC_CHANNEL_0, HAL_LL_ADC0_BASE_ADDRESS},
    #endif
    #ifdef ADC0_PA1_CH1
    {PA1, hal_ll_adc_module_num(ADC_MODULE_0), HAL_LL_ADC_CHANNEL_1, HAL_LL_ADC0_BASE_ADDRESS},
    #endif
    #ifdef ADC0_PA2_CH2
    {PA2, hal_ll_adc_module_num(ADC_MODULE_0), HAL_LL_ADC_CHANNEL_2, HAL_LL_ADC0_BASE_ADDRESS},
    #endif
    #ifdef ADC0_PA3_CH3
    {PA3, hal_ll_adc_module_num(ADC_MODULE_0), HAL_LL_ADC_CHANNEL_3, HAL_LL_ADC0_BASE_ADDRESS},
    #endif
    #ifdef ADC0_PA4_CH4
    {PA4, hal_ll_adc_module_num(ADC_MODULE_0), HAL_LL_ADC_CHANNEL_4, HAL_LL_ADC0_BASE_ADDRESS},
    #endif
    #ifdef ADC0_PA5_CH5
    {PA5, hal_ll_adc_module_num(ADC_MODULE_0), HAL_LL_ADC_CHANNEL_5, HAL_LL_ADC0_BASE_ADDRESS},
    #endif
    #ifdef ADC0_PA6_CH6
    {PA6, hal_ll_adc_module_num(ADC_MODULE_0), HAL_LL_ADC_CHANNEL_6, HAL_LL_ADC0_BASE_ADDRESS},
    #endif
    #ifdef ADC0_PA7_CH7
    {PA7, hal_ll_adc_module_num(ADC_MODULE_0), HAL_LL_ADC_CHANNEL_7, HAL_LL_ADC0_BASE_ADDRESS},
    #endif
    #ifdef ADC0_PC0_CH0
    {PC0, hal_ll_adc_module_num(ADC_MODULE_0), HAL_LL_ADC_CHANNEL_0, HAL_LL_ADC0_BASE_ADDRESS},
    #endif
    #ifdef ADC0_PC1_CH1
    {PC1, hal_ll_adc_module_num(ADC_MODULE_0), HAL_LL_ADC_CHANNEL_1, HAL_LL_ADC0_BASE_ADDRESS},
    #endif
    #ifdef ADC0_PC2_CH2
    {PC2, hal_ll_adc_module_num(ADC_MODULE_0), HAL_LL_ADC_CHANNEL_2, HAL_LL_ADC0_BASE_ADDRESS},
    #endif
    #ifdef ADC0_PC3_CH3
    {PC3, hal_ll_adc_module_num(ADC_MODULE_0), HAL_LL_ADC_CHANNEL_3, HAL_LL_ADC0_BASE_ADDRESS},
    #endif
    #ifdef ADC0_PC4_CH4
    {PC4, hal_ll_adc_module_num(ADC_MODULE_0), HAL_LL_ADC_CHANNEL_4, HAL_LL_ADC0_BASE_ADDRESS},
    #endif
    #ifdef ADC0_PC5_CH5
    {PC5, hal_ll_adc_module_num(ADC_MODULE_0), HAL_LL_ADC_CHANNEL_5, HAL_LL_ADC0_BASE_ADDRESS},
    #endif
    #ifdef ADC0_PE2_CH6
    {PE2, hal_ll_adc_module_num(ADC_MODULE_0), HAL_LL_ADC_CHANNEL_6, HAL_LL_ADC0_BASE_ADDRESS},
    #endif
    #ifdef ADC0_PE3_CH7
    {PE3, hal_ll_adc_module_num(ADC_MODULE_0), HAL_LL_ADC_CHANNEL_7, HAL_LL_ADC0_BASE_ADDRESS},
    #endif
    #ifdef ADC0_PB4_CH11
    {PB4, hal_ll_adc_module_num(ADC_MODULE_0), HAL_LL_ADC_CHANNEL_11, HAL_LL_ADC0_BASE_ADDRESS},
    #endif
    #ifdef ADC0_PB5_CH12
    {PB5, hal_ll_adc_module_num(ADC_MODULE_0), HAL_LL_ADC_CHANNEL_12, HAL_LL_ADC0_BASE_ADDRESS},
    #endif
    #ifdef ADC0_PB6_CH13
    {PB6, hal_ll_adc_module_num(ADC_MODULE_0), HAL_LL_ADC_CHANNEL_13, HAL_LL_ADC0_BASE_ADDRESS},
    #endif
    #ifdef ADC0_PD4_CH8
    {PD4, hal_ll_adc_module_num(ADC_MODULE_0), HAL_LL_ADC_CHANNEL_8, HAL_LL_ADC0_BASE_ADDRESS},
    #endif
    #ifdef ADC0_PD6_CH9
    {PD6, hal_ll_adc_module_num(ADC_MODULE_0), HAL_LL_ADC_CHANNEL_9, HAL_LL_ADC0_BASE_ADDRESS},
    #endif
    #ifdef ADC0_PD7_CH10
    {PD7, hal_ll_adc_module_num(ADC_MODULE_0), HAL_LL_ADC_CHANNEL_10, HAL_LL_ADC0_BASE_ADDRESS},
    #endif
    #ifdef ADC0_PB0_CH0
    {PB0, hal_ll_adc_module_num(ADC_MODULE_0), HAL_LL_ADC_CHANNEL_0, HAL_LL_ADC0_BASE_ADDRESS},
    #endif
    #ifdef ADC0_PB0_CH8
    {PB0, hal_ll_adc_module_num(ADC_MODULE_0), HAL_LL_ADC_CHANNEL_8, HAL_LL_ADC0_BASE_ADDRESS},
    #endif
    #ifdef ADC0_PB1_CH1
    {PB1, hal_ll_adc_module_num(ADC_MODULE_0), HAL_LL_ADC_CHANNEL_1, HAL_LL_ADC0_BASE_ADDRESS},
    #endif
    #ifdef ADC0_PB1_CH9
    {PB1, hal_ll_adc_module_num(ADC_MODULE_0), HAL_LL_ADC_CHANNEL_9, HAL_LL_ADC0_BASE_ADDRESS},
    #endif
    #ifdef ADC0_PB2_CH10
    {PB2, hal_ll_adc_module_num(ADC_MODULE_0), HAL_LL_ADC_CHANNEL_10, HAL_LL_ADC0_BASE_ADDRESS},
    #endif
    #ifdef ADC0_PB2_CH2
    {PB2, hal_ll_adc_module_num(ADC_MODULE_0), HAL_LL_ADC_CHANNEL_2, HAL_LL_ADC0_BASE_ADDRESS},
    #endif
    #ifdef ADC0_PB3_CH11
    {PB3, hal_ll_adc_module_num(ADC_MODULE_0), HAL_LL_ADC_CHANNEL_11, HAL_LL_ADC0_BASE_ADDRESS},
    #endif
    #ifdef ADC0_PB3_CH3
    {PB3, hal_ll_adc_module_num(ADC_MODULE_0), HAL_LL_ADC_CHANNEL_3, HAL_LL_ADC0_BASE_ADDRESS},
    #endif
    #ifdef ADC0_PB4_CH12
    {PB4, hal_ll_adc_module_num(ADC_MODULE_0), HAL_LL_ADC_CHANNEL_12, HAL_LL_ADC0_BASE_ADDRESS},
    #endif
    #ifdef ADC0_PB4_CH4
    {PB4, hal_ll_adc_module_num(ADC_MODULE_0), HAL_LL_ADC_CHANNEL_4, HAL_LL_ADC0_BASE_ADDRESS},
    #endif
    #ifdef ADC0_PB5_CH13
    {PB5, hal_ll_adc_module_num(ADC_MODULE_0), HAL_LL_ADC_CHANNEL_13, HAL_LL_ADC0_BASE_ADDRESS},
    #endif
    #ifdef ADC0_PB5_CH5
    {PB5, hal_ll_adc_module_num(ADC_MODULE_0), HAL_LL_ADC_CHANNEL_5, HAL_LL_ADC0_BASE_ADDRESS},
    #endif
    #ifdef ADC0_PB6_CH14
    {PB6, hal_ll_adc_module_num(ADC_MODULE_0), HAL_LL_ADC_CHANNEL_14, HAL_LL_ADC0_BASE_ADDRESS},
    #endif
    #ifdef ADC0_PB6_CH6
    {PB6, hal_ll_adc_module_num(ADC_MODULE_0), HAL_LL_ADC_CHANNEL_6, HAL_LL_ADC0_BASE_ADDRESS},
    #endif
    #ifdef ADC0_PB7_CH15
    {PB7, hal_ll_adc_module_num(ADC_MODULE_0), HAL_LL_ADC_CHANNEL_15, HAL_LL_ADC0_BASE_ADDRESS},
    #endif
    #ifdef ADC0_PB7_CH7
    {PB7, hal_ll_adc_module_num(ADC_MODULE_0), HAL_LL_ADC_CHANNEL_7, HAL_LL_ADC0_BASE_ADDRESS},
    #endif
    #ifdef ADC1_PA0_CH0
    {PA0, hal_ll_adc_module_num(ADC_MODULE_1), HAL_LL_ADC_CHANNEL_0, HAL_LL_ADC1_BASE_ADDRESS},
    #endif
    #ifdef ADC1_PB0_CH0
    {PB0, hal_ll_adc_module_num(ADC_MODULE_1), HAL_LL_ADC_CHANNEL_0, HAL_LL_ADC1_BASE_ADDRESS},
    #endif
    #ifdef ADC1_PB0_CH8
    {PB0, hal_ll_adc_module_num(ADC_MODULE_1), HAL_LL_ADC_CHANNEL_8, HAL_LL_ADC1_BASE_ADDRESS},
    #endif
    #ifdef ADC1_PB1_CH1
    {PB1, hal_ll_adc_module_num(ADC_MODULE_1), HAL_LL_ADC_CHANNEL_1, HAL_LL_ADC1_BASE_ADDRESS},
    #endif
    #ifdef ADC1_PB1_CH9
    {PB1, hal_ll_adc_module_num(ADC_MODULE_1), HAL_LL_ADC_CHANNEL_9, HAL_LL_ADC1_BASE_ADDRESS},
    #endif
    #ifdef ADC1_PB2_CH10
    {PB2, hal_ll_adc_module_num(ADC_MODULE_1), HAL_LL_ADC_CHANNEL_10, HAL_LL_ADC1_BASE_ADDRESS},
    #endif
    #ifdef ADC1_PB2_CH2
    {PB2, hal_ll_adc_module_num(ADC_MODULE_1), HAL_LL_ADC_CHANNEL_2, HAL_LL_ADC1_BASE_ADDRESS},
    #endif
    #ifdef ADC1_PB3_CH11
    {PB3, hal_ll_adc_module_num(ADC_MODULE_1), HAL_LL_ADC_CHANNEL_11, HAL_LL_ADC1_BASE_ADDRESS},
    #endif
    #ifdef ADC1_PB3_CH3
    {PB3, hal_ll_adc_module_num(ADC_MODULE_1), HAL_LL_ADC_CHANNEL_3, HAL_LL_ADC1_BASE_ADDRESS},
    #endif
    #ifdef ADC1_PB4_CH12
    {PB4, hal_ll_adc_module_num(ADC_MODULE_1), HAL_LL_ADC_CHANNEL_12, HAL_LL_ADC1_BASE_ADDRESS},
    #endif
    #ifdef ADC1_PB4_CH4
    {PB4, hal_ll_adc_module_num(ADC_MODULE_1), HAL_LL_ADC_CHANNEL_4, HAL_LL_ADC1_BASE_ADDRESS},
    #endif
    #ifdef ADC1_PB5_CH13
    {PB5, hal_ll_adc_module_num(ADC_MODULE_1), HAL_LL_ADC_CHANNEL_13, HAL_LL_ADC1_BASE_ADDRESS},
    #endif
    #ifdef ADC1_PB5_CH5
    {PB5, hal_ll_adc_module_num(ADC_MODULE_1), HAL_LL_ADC_CHANNEL_5, HAL_LL_ADC1_BASE_ADDRESS},
    #endif
    #ifdef ADC1_PB6_CH14
    {PB6, hal_ll_adc_module_num(ADC_MODULE_1), HAL_LL_ADC_CHANNEL_14, HAL_LL_ADC1_BASE_ADDRESS},
    #endif
    #ifdef ADC1_PB6_CH6
    {PB6, hal_ll_adc_module_num(ADC_MODULE_1), HAL_LL_ADC_CHANNEL_6, HAL_LL_ADC1_BASE_ADDRESS},
    #endif
    #ifdef ADC1_PB7_CH15
    {PB7, hal_ll_adc_module_num(ADC_MODULE_1), HAL_LL_ADC_CHANNEL_15, HAL_LL_ADC1_BASE_ADDRESS},
    #endif
    #ifdef ADC1_PB7_CH7
    {PB7, hal_ll_adc_module_num(ADC_MODULE_1), HAL_LL_ADC_CHANNEL_7, HAL_LL_ADC1_BASE_ADDRESS},
    #endif
    #ifdef ADC0_PD0_CH8
    {PD0, hal_ll_adc_module_num(ADC_MODULE_0), HAL_LL_ADC_CHANNEL_8, HAL_LL_ADC0_BASE_ADDRESS},
    #endif
    #ifdef ADC0_PD1_CH9
    {PD1, hal_ll_adc_module_num(ADC_MODULE_0), HAL_LL_ADC_CHANNEL_9, HAL_LL_ADC0_BASE_ADDRESS},
    #endif
    #ifdef ADC0_PD2_CH10
    {PD2, hal_ll_adc_module_num(ADC_MODULE_0), HAL_LL_ADC_CHANNEL_10, HAL_LL_ADC0_BASE_ADDRESS},
    #endif
    #ifdef ADC0_PD3_CH11
    {PD3, hal_ll_adc_module_num(ADC_MODULE_0), HAL_LL_ADC_CHANNEL_11, HAL_LL_ADC0_BASE_ADDRESS},
    #endif
    #ifdef ADC0_PD4_CH12
    {PD4, hal_ll_adc_module_num(ADC_MODULE_0), HAL_LL_ADC_CHANNEL_12, HAL_LL_ADC0_BASE_ADDRESS},
    #endif
    #ifdef ADC0_PD5_CH13
    {PD5, hal_ll_adc_module_num(ADC_MODULE_0), HAL_LL_ADC_CHANNEL_13, HAL_LL_ADC0_BASE_ADDRESS},
    #endif
    #ifdef ADC0_PD6_CH14
    {PD6, hal_ll_adc_module_num(ADC_MODULE_0), HAL_LL_ADC_CHANNEL_14, HAL_LL_ADC0_BASE_ADDRESS},
    #endif
    #ifdef ADC0_PD7_CH15
    {PD7, hal_ll_adc_module_num(ADC_MODULE_0), HAL_LL_ADC_CHANNEL_15, HAL_LL_ADC0_BASE_ADDRESS},
    #endif
    #ifdef ADC0_PB0_CH7
    {PB0, hal_ll_adc_module_num(ADC_MODULE_0), HAL_LL_ADC_CHANNEL_7, HAL_LL_ADC0_BASE_ADDRESS},
    #endif
    #ifdef ADC0_PB1_CH8
    {PB1, hal_ll_adc_module_num(ADC_MODULE_0), HAL_LL_ADC_CHANNEL_8, HAL_LL_ADC0_BASE_ADDRESS},
    #endif
    #ifdef ADC0_PB2_CH9
    {PB2, hal_ll_adc_module_num(ADC_MODULE_0), HAL_LL_ADC_CHANNEL_9, HAL_LL_ADC0_BASE_ADDRESS},
    #endif
    #ifdef ADC0_PB3_CH10
    {PB3, hal_ll_adc_module_num(ADC_MODULE_0), HAL_LL_ADC_CHANNEL_10, HAL_LL_ADC0_BASE_ADDRESS},
    #endif
    #ifdef ADC0_PB7_CH14
    {PB7, hal_ll_adc_module_num(ADC_MODULE_0), HAL_LL_ADC_CHANNEL_14, HAL_LL_ADC0_BASE_ADDRESS},
    #endif
    #ifdef ADC1_PB0_CH7
    {PB0, hal_ll_adc_module_num(ADC_MODULE_1), HAL_LL_ADC_CHANNEL_7, HAL_LL_ADC1_BASE_ADDRESS},
    #endif
    #ifdef ADC1_PB1_CH8
    {PB1, hal_ll_adc_module_num(ADC_MODULE_1), HAL_LL_ADC_CHANNEL_8, HAL_LL_ADC1_BASE_ADDRESS},
    #endif
    #ifdef ADC1_PB2_CH9
    {PB2, hal_ll_adc_module_num(ADC_MODULE_1), HAL_LL_ADC_CHANNEL_9, HAL_LL_ADC1_BASE_ADDRESS},
    #endif
    #ifdef ADC1_PB3_CH10
    {PB3, hal_ll_adc_module_num(ADC_MODULE_1), HAL_LL_ADC_CHANNEL_10, HAL_LL_ADC1_BASE_ADDRESS},
    #endif
    #ifdef ADC1_PB4_CH11
    {PB4, hal_ll_adc_module_num(ADC_MODULE_1), HAL_LL_ADC_CHANNEL_11, HAL_LL_ADC1_BASE_ADDRESS},
    #endif
    #ifdef ADC1_PB5_CH12
    {PB5, hal_ll_adc_module_num(ADC_MODULE_1), HAL_LL_ADC_CHANNEL_12, HAL_LL_ADC1_BASE_ADDRESS},
    #endif
    #ifdef ADC1_PB6_CH13
    {PB6, hal_ll_adc_module_num(ADC_MODULE_1), HAL_LL_ADC_CHANNEL_13, HAL_LL_ADC1_BASE_ADDRESS},
    #endif
    #ifdef ADC1_PB7_CH14
    {PB7, hal_ll_adc_module_num(ADC_MODULE_1), HAL_LL_ADC_CHANNEL_14, HAL_LL_ADC1_BASE_ADDRESS},
    #endif

    { HAL_LL_PIN_NC, HAL_LL_PIN_NC, HAL_LL_PIN_NC, HAL_LL_MODULE_ERROR }
    //------------ END
};

#ifdef __cplusplus
}
#endif

#endif // _HAL_LL_ANALOG_IN_MAP_H_
// ------------------------------------------------------------------------- END
