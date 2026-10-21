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
#include "mcu_reg_addresses.h"

/*!< @brief Macro defining `weak` attribute */
#define __weak __attribute__((weak))

/*!< @brief Helper macro for getting adequate module index number */
#define hal_ll_adc_module_num(_module_num) (_module_num - 1)

/**
 * ADC channels.
 */
typedef enum
{
    HAL_LL_ADC_CHANNEL_0,   // AINB00, AINC00
    HAL_LL_ADC_CHANNEL_1,   // AINB01, AINC01
    HAL_LL_ADC_CHANNEL_2,   // AINB02, AINC02
    HAL_LL_ADC_CHANNEL_3,   // AINB03, AINC03
    HAL_LL_ADC_CHANNEL_4,   // AINB04, AINC04
    HAL_LL_ADC_CHANNEL_5,   // AINA05, AINC05
    HAL_LL_ADC_CHANNEL_6,   // AINA06
    HAL_LL_ADC_CHANNEL_7,   // AINA07
    HAL_LL_ADC_CHANNEL_8,   // AINA08
    HAL_LL_ADC_CHANNEL_9,   // AINA09
    HAL_LL_ADC_CHANNEL_10,  // TMPM4L
    HAL_LL_ADC_CHANNEL_11,  // TMPM4L
    HAL_LL_ADC_CHANNEL_12,  // TMPM4L
    HAL_LL_ADC_CHANNEL_13,  // AINA13
    HAL_LL_ADC_CHANNEL_14,  // AINA14
    HAL_LL_ADC_CHANNEL_15,  // AINA15
    HAL_LL_ADC_CHANNEL_16,  // AINA16
    HAL_LL_ADC_CHANNEL_17,  // AINA17
    HAL_LL_ADC_CHANNEL_18,  // AINA18
    HAL_LL_ADC_CHANNEL_19,  // TMPM3H AINA19
    HAL_LL_ADC_CHANNEL_20,  // TMPM3H AINA20

    HAL_LL_ADC_CHANNEL_NC = 0xFF
} hal_ll_adc_channel_t;

/*!< @brief ADC pin structure. */
typedef struct
{
    hal_ll_pin_name_t pin;
    hal_ll_base_addr_t base;
    uint8_t module_index;
    uint8_t channel;
} hal_ll_pin_channel_list_t;

static const hal_ll_pin_channel_list_t hal_ll_analog_in_register_list[] =
{
    #ifdef ADC0_PE0_CH0
    {GPIO_PE0, HAL_LL_ADC0_BASE_ADDR, hal_ll_adc_module_num( ADC_MODULE_0 ), HAL_LL_ADC_CHANNEL_0},
    #endif
    #ifdef ADC0_PE1_CH1
    {GPIO_PE1, HAL_LL_ADC0_BASE_ADDR, hal_ll_adc_module_num( ADC_MODULE_0 ), HAL_LL_ADC_CHANNEL_1},
    #endif
    #ifdef ADC0_PE2_CH2
    {GPIO_PE2, HAL_LL_ADC0_BASE_ADDR, hal_ll_adc_module_num( ADC_MODULE_0 ), HAL_LL_ADC_CHANNEL_2},
    #endif
    #ifdef ADC0_PE3_CH3
    {GPIO_PE3, HAL_LL_ADC0_BASE_ADDR, hal_ll_adc_module_num( ADC_MODULE_0 ), HAL_LL_ADC_CHANNEL_3},
    #endif
    #ifdef ADC0_PE4_CH4
    {GPIO_PE4, HAL_LL_ADC0_BASE_ADDR, hal_ll_adc_module_num( ADC_MODULE_0 ), HAL_LL_ADC_CHANNEL_4},
    #endif
    #ifdef ADC0_PE5_CH5
    {GPIO_PE5, HAL_LL_ADC0_BASE_ADDR, hal_ll_adc_module_num( ADC_MODULE_0 ), HAL_LL_ADC_CHANNEL_5},
    #endif
    #ifdef ADC0_PE6_CH6
    {GPIO_PE6, HAL_LL_ADC0_BASE_ADDR, hal_ll_adc_module_num( ADC_MODULE_0 ), HAL_LL_ADC_CHANNEL_6},
    #endif
    #ifdef ADC0_PE7_CH7
    {GPIO_PE7, HAL_LL_ADC0_BASE_ADDR, hal_ll_adc_module_num( ADC_MODULE_0 ), HAL_LL_ADC_CHANNEL_7},
    #endif
    #ifdef ADC0_PF0_CH8
    {GPIO_PF0, HAL_LL_ADC0_BASE_ADDR, hal_ll_adc_module_num( ADC_MODULE_0 ), HAL_LL_ADC_CHANNEL_8},
    #endif
    #ifdef ADC0_PF1_CH9
    {GPIO_PF1, HAL_LL_ADC0_BASE_ADDR, hal_ll_adc_module_num( ADC_MODULE_0 ), HAL_LL_ADC_CHANNEL_9},
    #endif
    #ifdef ADC0_PF2_CH10
    {GPIO_PF2, HAL_LL_ADC0_BASE_ADDR, hal_ll_adc_module_num( ADC_MODULE_0 ), HAL_LL_ADC_CHANNEL_10},
    #endif
    #ifdef ADC0_PF3_CH11
    {GPIO_PF3, HAL_LL_ADC0_BASE_ADDR, hal_ll_adc_module_num( ADC_MODULE_0 ), HAL_LL_ADC_CHANNEL_11},
    #endif
    #ifdef ADC0_PF4_CH12
    {GPIO_PF4, HAL_LL_ADC0_BASE_ADDR, hal_ll_adc_module_num( ADC_MODULE_0 ), HAL_LL_ADC_CHANNEL_12},
    #endif
    #ifdef ADC0_PF5_CH13
    {GPIO_PF5, HAL_LL_ADC0_BASE_ADDR, hal_ll_adc_module_num( ADC_MODULE_0 ), HAL_LL_ADC_CHANNEL_13},
    #endif
    #ifdef ADC0_PL0_CH16
    {GPIO_PL0, HAL_LL_ADC0_BASE_ADDR, hal_ll_adc_module_num( ADC_MODULE_0 ), HAL_LL_ADC_CHANNEL_16},
    #endif
    #ifdef ADC0_PL1_CH15
    {GPIO_PL1, HAL_LL_ADC0_BASE_ADDR, hal_ll_adc_module_num( ADC_MODULE_0 ), HAL_LL_ADC_CHANNEL_15},
    #endif
    #ifdef ADC0_PL2_CH17
    {GPIO_PL2, HAL_LL_ADC0_BASE_ADDR, hal_ll_adc_module_num( ADC_MODULE_0 ), HAL_LL_ADC_CHANNEL_17},
    #endif
    #ifdef ADC0_PL3_CH14
    {GPIO_PL3, HAL_LL_ADC0_BASE_ADDR, hal_ll_adc_module_num( ADC_MODULE_0 ), HAL_LL_ADC_CHANNEL_14},
    #endif
    #ifdef ADC0_PL4_CH18
    {GPIO_PL4, HAL_LL_ADC0_BASE_ADDR, hal_ll_adc_module_num( ADC_MODULE_0 ), HAL_LL_ADC_CHANNEL_18},
    #endif
    #ifdef ADC0_PL5_CH13
    {GPIO_PL5, HAL_LL_ADC0_BASE_ADDR, hal_ll_adc_module_num( ADC_MODULE_0 ), HAL_LL_ADC_CHANNEL_13},
    #endif
    #ifdef ADC0_PL6_CH9
    {GPIO_PL6, HAL_LL_ADC0_BASE_ADDR, hal_ll_adc_module_num( ADC_MODULE_0 ), HAL_LL_ADC_CHANNEL_9},
    #endif
    #ifdef ADC0_PL7_CH8
    {GPIO_PL7, HAL_LL_ADC0_BASE_ADDR, hal_ll_adc_module_num( ADC_MODULE_0 ), HAL_LL_ADC_CHANNEL_8},
    #endif
    #ifdef ADC0_PM0_CH7
    {GPIO_PM0, HAL_LL_ADC0_BASE_ADDR, hal_ll_adc_module_num( ADC_MODULE_0 ), HAL_LL_ADC_CHANNEL_7},
    #endif
    #ifdef ADC0_PM1_CH6
    {GPIO_PM1, HAL_LL_ADC0_BASE_ADDR, hal_ll_adc_module_num( ADC_MODULE_0 ), HAL_LL_ADC_CHANNEL_6},
    #endif
    #ifdef ADC0_PM2_CH5
    {GPIO_PM2, HAL_LL_ADC0_BASE_ADDR, hal_ll_adc_module_num( ADC_MODULE_0 ), HAL_LL_ADC_CHANNEL_5},
    #endif
    #ifdef ADC1_PE0_CH0
    {GPIO_PE0, HAL_LL_ADC1_BASE_ADDR, hal_ll_adc_module_num( ADC_MODULE_1 ), HAL_LL_ADC_CHANNEL_0},
    #endif
    #ifdef ADC1_PE1_CH1
    {GPIO_PE1, HAL_LL_ADC1_BASE_ADDR, hal_ll_adc_module_num( ADC_MODULE_1 ), HAL_LL_ADC_CHANNEL_1},
    #endif
    #ifdef ADC1_PE2_CH2
    {GPIO_PE2, HAL_LL_ADC1_BASE_ADDR, hal_ll_adc_module_num( ADC_MODULE_1 ), HAL_LL_ADC_CHANNEL_2},
    #endif
    #ifdef ADC1_PE3_CH3
    {GPIO_PE3, HAL_LL_ADC1_BASE_ADDR, hal_ll_adc_module_num( ADC_MODULE_1 ), HAL_LL_ADC_CHANNEL_3},
    #endif
    #ifdef ADC1_PE4_CH4
    {GPIO_PE4, HAL_LL_ADC1_BASE_ADDR, hal_ll_adc_module_num( ADC_MODULE_1 ), HAL_LL_ADC_CHANNEL_4},
    #endif
    #ifdef ADC1_PE5_CH5
    {GPIO_PE5, HAL_LL_ADC1_BASE_ADDR, hal_ll_adc_module_num( ADC_MODULE_1 ), HAL_LL_ADC_CHANNEL_5},
    #endif
    #ifdef ADC1_PE6_CH6
    {GPIO_PE6, HAL_LL_ADC1_BASE_ADDR, hal_ll_adc_module_num( ADC_MODULE_1 ), HAL_LL_ADC_CHANNEL_6},
    #endif
    #ifdef ADC1_PE7_CH7
    {GPIO_PE7, HAL_LL_ADC1_BASE_ADDR, hal_ll_adc_module_num( ADC_MODULE_1 ), HAL_LL_ADC_CHANNEL_7},
    #endif
    #ifdef ADC1_PF0_CH8
    {GPIO_PF0, HAL_LL_ADC1_BASE_ADDR, hal_ll_adc_module_num( ADC_MODULE_1 ), HAL_LL_ADC_CHANNEL_8},
    #endif
    #ifdef ADC1_PF1_CH9
    {GPIO_PF1, HAL_LL_ADC1_BASE_ADDR, hal_ll_adc_module_num( ADC_MODULE_1 ), HAL_LL_ADC_CHANNEL_9},
    #endif
    #ifdef ADC1_PF2_CH10
    {GPIO_PF2, HAL_LL_ADC1_BASE_ADDR, hal_ll_adc_module_num( ADC_MODULE_1 ), HAL_LL_ADC_CHANNEL_10},
    #endif
    #ifdef ADC1_PF3_CH11
    {GPIO_PF3, HAL_LL_ADC1_BASE_ADDR, hal_ll_adc_module_num( ADC_MODULE_1 ), HAL_LL_ADC_CHANNEL_11},
    #endif
    #ifdef ADC1_PF4_CH12
    {GPIO_PF4, HAL_LL_ADC1_BASE_ADDR, hal_ll_adc_module_num( ADC_MODULE_1 ), HAL_LL_ADC_CHANNEL_12},
    #endif
    #ifdef ADC1_PF5_CH13
    {GPIO_PF5, HAL_LL_ADC1_BASE_ADDR, hal_ll_adc_module_num( ADC_MODULE_1 ), HAL_LL_ADC_CHANNEL_13},
    #endif
    #ifdef ADC1_PK0_CH0
    {GPIO_PK0, HAL_LL_ADC1_BASE_ADDR, hal_ll_adc_module_num( ADC_MODULE_1 ), HAL_LL_ADC_CHANNEL_0},
    #endif
    #ifdef ADC1_PK1_CH1
    {GPIO_PK1, HAL_LL_ADC1_BASE_ADDR, hal_ll_adc_module_num( ADC_MODULE_1 ), HAL_LL_ADC_CHANNEL_1},
    #endif
    #ifdef ADC1_PK2_CH2
    {GPIO_PK2, HAL_LL_ADC1_BASE_ADDR, hal_ll_adc_module_num( ADC_MODULE_1 ), HAL_LL_ADC_CHANNEL_2},
    #endif
    #ifdef ADC1_PK3_CH3
    {GPIO_PK3, HAL_LL_ADC1_BASE_ADDR, hal_ll_adc_module_num( ADC_MODULE_1 ), HAL_LL_ADC_CHANNEL_3},
    #endif
    #ifdef ADC1_PK4_CH4
    {GPIO_PK4, HAL_LL_ADC1_BASE_ADDR, hal_ll_adc_module_num( ADC_MODULE_1 ), HAL_LL_ADC_CHANNEL_4},
    #endif
    #ifdef ADC2_PJ0_CH0
    {GPIO_PJ0, HAL_LL_ADC2_BASE_ADDR, hal_ll_adc_module_num( ADC_MODULE_2 ), HAL_LL_ADC_CHANNEL_0},
    #endif
    #ifdef ADC2_PJ1_CH1
    {GPIO_PJ1, HAL_LL_ADC2_BASE_ADDR, hal_ll_adc_module_num( ADC_MODULE_2 ), HAL_LL_ADC_CHANNEL_1},
    #endif
    #ifdef ADC2_PJ2_CH2
    {GPIO_PJ2, HAL_LL_ADC2_BASE_ADDR, hal_ll_adc_module_num( ADC_MODULE_2 ), HAL_LL_ADC_CHANNEL_2},
    #endif
    #ifdef ADC2_PJ3_CH3
    {GPIO_PJ3, HAL_LL_ADC2_BASE_ADDR, hal_ll_adc_module_num( ADC_MODULE_2 ), HAL_LL_ADC_CHANNEL_3},
    #endif
    #ifdef ADC2_PJ4_CH4
    {GPIO_PJ4, HAL_LL_ADC2_BASE_ADDR, hal_ll_adc_module_num( ADC_MODULE_2 ), HAL_LL_ADC_CHANNEL_4},
    #endif
    #ifdef ADC2_PJ5_CH5
    {GPIO_PJ5, HAL_LL_ADC2_BASE_ADDR, hal_ll_adc_module_num( ADC_MODULE_2 ), HAL_LL_ADC_CHANNEL_5},
    #endif

    #ifdef ADC0_PD0_CH0
    {GPIO_PD0, HAL_LL_ADC0_BASE_ADDR, hal_ll_adc_module_num( ADC_MODULE_0 ), HAL_LL_ADC_CHANNEL_0},
    #endif
    #ifdef ADC0_PD1_CH1
    {GPIO_PD1, HAL_LL_ADC0_BASE_ADDR, hal_ll_adc_module_num( ADC_MODULE_0 ), HAL_LL_ADC_CHANNEL_1},
    #endif
    #ifdef ADC0_PD2_CH2
    {GPIO_PD2, HAL_LL_ADC0_BASE_ADDR, hal_ll_adc_module_num( ADC_MODULE_0 ), HAL_LL_ADC_CHANNEL_2},
    #endif
    #ifdef ADC0_PD3_CH3
    {GPIO_PD3, HAL_LL_ADC0_BASE_ADDR, hal_ll_adc_module_num( ADC_MODULE_0 ), HAL_LL_ADC_CHANNEL_3},
    #endif
    #ifdef ADC0_PD4_CH19
    {GPIO_PD4, HAL_LL_ADC0_BASE_ADDR, hal_ll_adc_module_num( ADC_MODULE_0 ), HAL_LL_ADC_CHANNEL_19},
    #endif
    #ifdef ADC0_PD5_CH20
    {GPIO_PD5, HAL_LL_ADC0_BASE_ADDR, hal_ll_adc_module_num( ADC_MODULE_0 ), HAL_LL_ADC_CHANNEL_20},
    #endif
    #ifdef ADC0_PE0_CH4
    {GPIO_PE0, HAL_LL_ADC0_BASE_ADDR, hal_ll_adc_module_num( ADC_MODULE_0 ), HAL_LL_ADC_CHANNEL_4},
    #endif
    #ifdef ADC0_PE1_CH5
    {GPIO_PE1, HAL_LL_ADC0_BASE_ADDR, hal_ll_adc_module_num( ADC_MODULE_0 ), HAL_LL_ADC_CHANNEL_5},
    #endif
    #ifdef ADC0_PE2_CH6
    {GPIO_PE2, HAL_LL_ADC0_BASE_ADDR, hal_ll_adc_module_num( ADC_MODULE_0 ), HAL_LL_ADC_CHANNEL_6},
    #endif
    #ifdef ADC0_PE3_CH7
    {GPIO_PE3, HAL_LL_ADC0_BASE_ADDR, hal_ll_adc_module_num( ADC_MODULE_0 ), HAL_LL_ADC_CHANNEL_7},
    #endif
    #ifdef ADC0_PE4_CH8
    {GPIO_PE4, HAL_LL_ADC0_BASE_ADDR, hal_ll_adc_module_num( ADC_MODULE_0 ), HAL_LL_ADC_CHANNEL_8},
    #endif
    #ifdef ADC0_PE5_CH9
    {GPIO_PE5, HAL_LL_ADC0_BASE_ADDR, hal_ll_adc_module_num( ADC_MODULE_0 ), HAL_LL_ADC_CHANNEL_9},
    #endif
    #ifdef ADC0_PE6_CH10
    {GPIO_PE6, HAL_LL_ADC0_BASE_ADDR, hal_ll_adc_module_num( ADC_MODULE_0 ), HAL_LL_ADC_CHANNEL_10},
    #endif
    #ifdef ADC0_PF0_CH11
    {GPIO_PF0, HAL_LL_ADC0_BASE_ADDR, hal_ll_adc_module_num( ADC_MODULE_0 ), HAL_LL_ADC_CHANNEL_11},
    #endif
    #ifdef ADC0_PF1_CH12
    {GPIO_PF1, HAL_LL_ADC0_BASE_ADDR, hal_ll_adc_module_num( ADC_MODULE_0 ), HAL_LL_ADC_CHANNEL_12},
    #endif
    #ifdef ADC0_PF2_CH13
    {GPIO_PF2, HAL_LL_ADC0_BASE_ADDR, hal_ll_adc_module_num( ADC_MODULE_0 ), HAL_LL_ADC_CHANNEL_13},
    #endif
    #ifdef ADC0_PF3_CH14
    {GPIO_PF3, HAL_LL_ADC0_BASE_ADDR, hal_ll_adc_module_num( ADC_MODULE_0 ), HAL_LL_ADC_CHANNEL_14},
    #endif
    #ifdef ADC0_PF4_CH15
    {GPIO_PF4, HAL_LL_ADC0_BASE_ADDR, hal_ll_adc_module_num( ADC_MODULE_0 ), HAL_LL_ADC_CHANNEL_15},
    #endif
    #ifdef ADC0_PF5_CH16
    {GPIO_PF5, HAL_LL_ADC0_BASE_ADDR, hal_ll_adc_module_num( ADC_MODULE_0 ), HAL_LL_ADC_CHANNEL_16},
    #endif
    #ifdef ADC0_PF6_CH17
    {GPIO_PF6, HAL_LL_ADC0_BASE_ADDR, hal_ll_adc_module_num( ADC_MODULE_0 ), HAL_LL_ADC_CHANNEL_17},
    #endif
    #ifdef ADC0_PF7_CH18
    {GPIO_PF7, HAL_LL_ADC0_BASE_ADDR, hal_ll_adc_module_num( ADC_MODULE_0 ), HAL_LL_ADC_CHANNEL_18},
    #endif
    {HAL_LL_PIN_NC, HAL_LL_MODULE_ERROR, HAL_LL_PIN_NC, HAL_LL_PIN_NC}
    //------------ END
};

#ifdef __cplusplus
}
#endif

#endif // _HAL_LL_ADC_PIN_MAP_H_
// ------------------------------------------------------------------------- END
