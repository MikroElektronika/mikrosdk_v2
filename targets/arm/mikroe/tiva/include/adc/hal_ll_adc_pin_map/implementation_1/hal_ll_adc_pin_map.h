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

/*!< @brief Macro defining `weak` attribute */
#define __weak __attribute__((weak))

/*!< @brief Helper macro for getting adequate module index number */
#define hal_ll_adc_module_num(_module_num) (_module_num - 1)

/*!< ADC module base addresses. */
#ifdef ADC_MODULE_0
static const hal_ll_base_addr_t ADC0_BASE_ADDR = 0x40038000;
#endif
#ifdef ADC_MODULE_1
static const hal_ll_base_addr_t ADC1_BASE_ADDR = 0x40039000;
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
    #ifdef ADC0_PE3_AIN0
    {PE3, ADC0_BASE_ADDR, hal_ll_adc_module_num(ADC_MODULE_0), HAL_LL_ADC_CHANNEL_0},
    #endif
    #ifdef ADC1_PE3_AIN0
    {PE3, ADC1_BASE_ADDR, hal_ll_adc_module_num(ADC_MODULE_1), HAL_LL_ADC_CHANNEL_0},
    #endif
    #ifdef ADC0_PE2_AIN1
    {PE2, ADC0_BASE_ADDR, hal_ll_adc_module_num(ADC_MODULE_0), HAL_LL_ADC_CHANNEL_1},
    #endif
    #ifdef ADC1_PE2_AIN1
    {PE2, ADC1_BASE_ADDR, hal_ll_adc_module_num(ADC_MODULE_1), HAL_LL_ADC_CHANNEL_1},
    #endif
    #ifdef ADC0_PE1_AIN2
    {PE1, ADC0_BASE_ADDR, hal_ll_adc_module_num(ADC_MODULE_0), HAL_LL_ADC_CHANNEL_2},
    #endif
    #ifdef ADC1_PE1_AIN2
    {PE1, ADC1_BASE_ADDR, hal_ll_adc_module_num(ADC_MODULE_1), HAL_LL_ADC_CHANNEL_2},
    #endif
    #ifdef ADC0_PE0_AIN3
    {PE0, ADC0_BASE_ADDR, hal_ll_adc_module_num(ADC_MODULE_0), HAL_LL_ADC_CHANNEL_3},
    #endif
    #ifdef ADC1_PE0_AIN3
    {PE0, ADC1_BASE_ADDR, hal_ll_adc_module_num(ADC_MODULE_1), HAL_LL_ADC_CHANNEL_3},
    #endif
    #ifdef ADC0_PD3_AIN4
    {PD3, ADC0_BASE_ADDR, hal_ll_adc_module_num(ADC_MODULE_0), HAL_LL_ADC_CHANNEL_4},
    #endif
    #ifdef ADC1_PD3_AIN4
    {PD3, ADC1_BASE_ADDR, hal_ll_adc_module_num(ADC_MODULE_1), HAL_LL_ADC_CHANNEL_4},
    #endif
    #ifdef ADC0_PD2_AIN5
    {PD2, ADC0_BASE_ADDR, hal_ll_adc_module_num(ADC_MODULE_0), HAL_LL_ADC_CHANNEL_5},
    #endif
    #ifdef ADC1_PD2_AIN5
    {PD2, ADC1_BASE_ADDR, hal_ll_adc_module_num(ADC_MODULE_1), HAL_LL_ADC_CHANNEL_5},
    #endif
    #ifdef ADC0_PD1_AIN6
    {PD1, ADC0_BASE_ADDR, hal_ll_adc_module_num(ADC_MODULE_0), HAL_LL_ADC_CHANNEL_6},
    #endif
    #ifdef ADC1_PD1_AIN6
    {PD1, ADC1_BASE_ADDR, hal_ll_adc_module_num(ADC_MODULE_1), HAL_LL_ADC_CHANNEL_6},
    #endif
    #ifdef ADC0_PD0_AIN7
    {PD0, ADC0_BASE_ADDR, hal_ll_adc_module_num(ADC_MODULE_0), HAL_LL_ADC_CHANNEL_7},
    #endif
    #ifdef ADC1_PD0_AIN7
    {PD0, ADC1_BASE_ADDR, hal_ll_adc_module_num(ADC_MODULE_1), HAL_LL_ADC_CHANNEL_7},
    #endif
    #ifdef ADC0_PE5_AIN8
    {PE5, ADC0_BASE_ADDR, hal_ll_adc_module_num(ADC_MODULE_0), HAL_LL_ADC_CHANNEL_8},
    #endif
    #ifdef ADC1_PE5_AIN8
    {PE5, ADC1_BASE_ADDR, hal_ll_adc_module_num(ADC_MODULE_1), HAL_LL_ADC_CHANNEL_8},
    #endif
    #ifdef ADC0_PE4_AIN9
    {PE4, ADC0_BASE_ADDR, hal_ll_adc_module_num(ADC_MODULE_0), HAL_LL_ADC_CHANNEL_9},
    #endif
    #ifdef ADC1_PE4_AIN9
    {PE4, ADC1_BASE_ADDR, hal_ll_adc_module_num(ADC_MODULE_1), HAL_LL_ADC_CHANNEL_9},
    #endif
    #ifdef ADC0_PB4_AIN10
    {PB4, ADC0_BASE_ADDR, hal_ll_adc_module_num(ADC_MODULE_0), HAL_LL_ADC_CHANNEL_10},
    #endif
    #ifdef ADC1_PB4_AIN10
    {PB4, ADC1_BASE_ADDR, hal_ll_adc_module_num(ADC_MODULE_1), HAL_LL_ADC_CHANNEL_10},
    #endif
    #ifdef ADC0_PB5_AIN11
    {PB5, ADC0_BASE_ADDR, hal_ll_adc_module_num(ADC_MODULE_0), HAL_LL_ADC_CHANNEL_11},
    #endif
    #ifdef ADC1_PB5_AIN11
    {PB5, ADC1_BASE_ADDR, hal_ll_adc_module_num(ADC_MODULE_1), HAL_LL_ADC_CHANNEL_11},
    #endif
    #ifdef ADC0_PD7_AIN4
    {PD7, ADC0_BASE_ADDR, hal_ll_adc_module_num(ADC_MODULE_0), HAL_LL_ADC_CHANNEL_4},
    #endif
    #ifdef ADC1_PD7_AIN4
    {PD7, ADC1_BASE_ADDR, hal_ll_adc_module_num(ADC_MODULE_1), HAL_LL_ADC_CHANNEL_4},
    #endif
    #ifdef ADC0_PD6_AIN5
    {PD6, ADC0_BASE_ADDR, hal_ll_adc_module_num(ADC_MODULE_0), HAL_LL_ADC_CHANNEL_5},
    #endif
    #ifdef ADC1_PD6_AIN5
    {PD6, ADC1_BASE_ADDR, hal_ll_adc_module_num(ADC_MODULE_1), HAL_LL_ADC_CHANNEL_5},
    #endif
    #ifdef ADC0_PD5_AIN6
    {PD5, ADC0_BASE_ADDR, hal_ll_adc_module_num(ADC_MODULE_0), HAL_LL_ADC_CHANNEL_6},
    #endif
    #ifdef ADC1_PD5_AIN6
    {PD5, ADC1_BASE_ADDR, hal_ll_adc_module_num(ADC_MODULE_1), HAL_LL_ADC_CHANNEL_6},
    #endif
    #ifdef ADC0_PD4_AIN7
    {PD4, ADC0_BASE_ADDR, hal_ll_adc_module_num(ADC_MODULE_0), HAL_LL_ADC_CHANNEL_7},
    #endif
    #ifdef ADC1_PD4_AIN7
    {PD4, ADC1_BASE_ADDR, hal_ll_adc_module_num(ADC_MODULE_1), HAL_LL_ADC_CHANNEL_7},
    #endif
    #ifdef ADC0_PD3_AIN12
    {PD3, ADC0_BASE_ADDR, hal_ll_adc_module_num(ADC_MODULE_0), HAL_LL_ADC_CHANNEL_12},
    #endif
    #ifdef ADC1_PD3_AIN12
    {PD3, ADC1_BASE_ADDR, hal_ll_adc_module_num(ADC_MODULE_1), HAL_LL_ADC_CHANNEL_12},
    #endif
    #ifdef ADC0_PD2_AIN13
    {PD2, ADC0_BASE_ADDR, hal_ll_adc_module_num(ADC_MODULE_0), HAL_LL_ADC_CHANNEL_13},
    #endif
    #ifdef ADC1_PD2_AIN13
    {PD2, ADC1_BASE_ADDR, hal_ll_adc_module_num(ADC_MODULE_1), HAL_LL_ADC_CHANNEL_13},
    #endif
    #ifdef ADC0_PD1_AIN14
    {PD1, ADC0_BASE_ADDR, hal_ll_adc_module_num(ADC_MODULE_0), HAL_LL_ADC_CHANNEL_14},
    #endif
    #ifdef ADC1_PD1_AIN14
    {PD1, ADC1_BASE_ADDR, hal_ll_adc_module_num(ADC_MODULE_1), HAL_LL_ADC_CHANNEL_14},
    #endif
    #ifdef ADC0_PD0_AIN15
    {PD0, ADC0_BASE_ADDR, hal_ll_adc_module_num(ADC_MODULE_0), HAL_LL_ADC_CHANNEL_15},
    #endif
    #ifdef ADC1_PD0_AIN15
    {PD0, ADC1_BASE_ADDR, hal_ll_adc_module_num(ADC_MODULE_1), HAL_LL_ADC_CHANNEL_15},
    #endif
    #ifdef ADC0_PH0_AIN16
    {PH0, ADC0_BASE_ADDR, hal_ll_adc_module_num(ADC_MODULE_0), HAL_LL_ADC_CHANNEL_16},
    #endif
    #ifdef ADC1_PH0_AIN16
    {PH0, ADC1_BASE_ADDR, hal_ll_adc_module_num(ADC_MODULE_1), HAL_LL_ADC_CHANNEL_16},
    #endif
    #ifdef ADC0_PH1_AIN17
    {PH1, ADC0_BASE_ADDR, hal_ll_adc_module_num(ADC_MODULE_0), HAL_LL_ADC_CHANNEL_17},
    #endif
    #ifdef ADC1_PH1_AIN17
    {PH1, ADC1_BASE_ADDR, hal_ll_adc_module_num(ADC_MODULE_1), HAL_LL_ADC_CHANNEL_17},
    #endif
    #ifdef ADC0_PH2_AIN18
    {PH2, ADC0_BASE_ADDR, hal_ll_adc_module_num(ADC_MODULE_0), HAL_LL_ADC_CHANNEL_18},
    #endif
    #ifdef ADC1_PH2_AIN18
    {PH2, ADC1_BASE_ADDR, hal_ll_adc_module_num(ADC_MODULE_1), HAL_LL_ADC_CHANNEL_18},
    #endif
    #ifdef ADC0_PH3_AIN19
    {PH3, ADC0_BASE_ADDR, hal_ll_adc_module_num(ADC_MODULE_0), HAL_LL_ADC_CHANNEL_19},
    #endif
    #ifdef ADC1_PH3_AIN19
    {PH3, ADC1_BASE_ADDR, hal_ll_adc_module_num(ADC_MODULE_1), HAL_LL_ADC_CHANNEL_19},
    #endif
    #ifdef ADC0_PE7_AIN20
    {PE7, ADC0_BASE_ADDR, hal_ll_adc_module_num(ADC_MODULE_0), HAL_LL_ADC_CHANNEL_20},
    #endif
    #ifdef ADC1_PE7_AIN20
    {PE7, ADC1_BASE_ADDR, hal_ll_adc_module_num(ADC_MODULE_1), HAL_LL_ADC_CHANNEL_20},
    #endif
    #ifdef ADC0_PE6_AIN21
    {PE6, ADC0_BASE_ADDR, hal_ll_adc_module_num(ADC_MODULE_0), HAL_LL_ADC_CHANNEL_21},
    #endif
    #ifdef ADC1_PE6_AIN21
    {PE6, ADC1_BASE_ADDR, hal_ll_adc_module_num(ADC_MODULE_1), HAL_LL_ADC_CHANNEL_21},
    #endif
    #ifdef ADC0_PK0_AIN16
    {PK0, ADC0_BASE_ADDR, hal_ll_adc_module_num(ADC_MODULE_0), HAL_LL_ADC_CHANNEL_16},
    #endif
    #ifdef ADC1_PK0_AIN16
    {PK0, ADC1_BASE_ADDR, hal_ll_adc_module_num(ADC_MODULE_1), HAL_LL_ADC_CHANNEL_16},
    #endif
    #ifdef ADC0_PK1_AIN17
    {PK1, ADC0_BASE_ADDR, hal_ll_adc_module_num(ADC_MODULE_0), HAL_LL_ADC_CHANNEL_17},
    #endif
    #ifdef ADC1_PK1_AIN17
    {PK1, ADC1_BASE_ADDR, hal_ll_adc_module_num(ADC_MODULE_1), HAL_LL_ADC_CHANNEL_17},
    #endif
    #ifdef ADC0_PK2_AIN18
    {PK2, ADC0_BASE_ADDR, hal_ll_adc_module_num(ADC_MODULE_0), HAL_LL_ADC_CHANNEL_18},
    #endif
    #ifdef ADC1_PK2_AIN18
    {PK2, ADC1_BASE_ADDR, hal_ll_adc_module_num(ADC_MODULE_1), HAL_LL_ADC_CHANNEL_18},
    #endif
    #ifdef ADC0_PK3_AIN19
    {PK3, ADC0_BASE_ADDR, hal_ll_adc_module_num(ADC_MODULE_0), HAL_LL_ADC_CHANNEL_19},
    #endif
    #ifdef ADC1_PK3_AIN19
    {PK3, ADC1_BASE_ADDR, hal_ll_adc_module_num(ADC_MODULE_1), HAL_LL_ADC_CHANNEL_19},
    #endif
    #ifdef ADC0_PP1_AIN22
    {PP1, ADC0_BASE_ADDR, hal_ll_adc_module_num(ADC_MODULE_0), HAL_LL_ADC_CHANNEL_22},
    #endif
    #ifdef ADC1_PP1_AIN22
    {PP1, ADC1_BASE_ADDR, hal_ll_adc_module_num(ADC_MODULE_1), HAL_LL_ADC_CHANNEL_22},
    #endif
    #ifdef ADC0_PP0_AIN23
    {PP0, ADC0_BASE_ADDR, hal_ll_adc_module_num(ADC_MODULE_0), HAL_LL_ADC_CHANNEL_23},
    #endif
    #ifdef ADC1_PP0_AIN23
    {PP0, ADC1_BASE_ADDR, hal_ll_adc_module_num(ADC_MODULE_1), HAL_LL_ADC_CHANNEL_23},
    #endif
    #ifdef ADC0_PN1_AIN22
    {PN1, ADC0_BASE_ADDR, hal_ll_adc_module_num(ADC_MODULE_0), HAL_LL_ADC_CHANNEL_22},
    #endif
    #ifdef ADC1_PN1_AIN22
    {PN1, ADC1_BASE_ADDR, hal_ll_adc_module_num(ADC_MODULE_1), HAL_LL_ADC_CHANNEL_22},
    #endif
    #ifdef ADC0_PN0_AIN23
    {PN0, ADC0_BASE_ADDR, hal_ll_adc_module_num(ADC_MODULE_0), HAL_LL_ADC_CHANNEL_23},
    #endif
    #ifdef ADC1_PN0_AIN23
    {PN0, ADC1_BASE_ADDR, hal_ll_adc_module_num(ADC_MODULE_1), HAL_LL_ADC_CHANNEL_23},
    #endif
    #ifdef ADC0_PE6_AIN20
    {PE6, ADC0_BASE_ADDR, hal_ll_adc_module_num(ADC_MODULE_0), HAL_LL_ADC_CHANNEL_20},
    #endif
    #ifdef ADC1_PE6_AIN20
    {PE6, ADC1_BASE_ADDR, hal_ll_adc_module_num(ADC_MODULE_1), HAL_LL_ADC_CHANNEL_20},
    #endif
    #ifdef ADC0_PE7_AIN21
    {PE7, ADC0_BASE_ADDR, hal_ll_adc_module_num(ADC_MODULE_0), HAL_LL_ADC_CHANNEL_21},
    #endif
    #ifdef ADC1_PE7_AIN21
    {PE7, ADC1_BASE_ADDR, hal_ll_adc_module_num(ADC_MODULE_1), HAL_LL_ADC_CHANNEL_21},
    #endif
    #ifdef ADC0_PP7_AIN22
    {PP7, ADC0_BASE_ADDR, hal_ll_adc_module_num(ADC_MODULE_0), HAL_LL_ADC_CHANNEL_22},
    #endif
    #ifdef ADC1_PP7_AIN22
    {PP7, ADC1_BASE_ADDR, hal_ll_adc_module_num(ADC_MODULE_1), HAL_LL_ADC_CHANNEL_22},
    #endif
    #ifdef ADC0_PP6_AIN23
    {PP6, ADC0_BASE_ADDR, hal_ll_adc_module_num(ADC_MODULE_0), HAL_LL_ADC_CHANNEL_23},
    #endif
    #ifdef ADC1_PP6_AIN23
    {PP6, ADC1_BASE_ADDR, hal_ll_adc_module_num(ADC_MODULE_1), HAL_LL_ADC_CHANNEL_23},
    #endif

    { HAL_LL_PIN_NC, HAL_LL_MODULE_ERROR, HAL_LL_PIN_NC, HAL_LL_CHANNEL_ERROR }
    //------------ END
};

#ifdef __cplusplus
}
#endif

#endif // _HAL_LL_ADC_PIN_MAP_H_
// ------------------------------------------------------------------------- END
