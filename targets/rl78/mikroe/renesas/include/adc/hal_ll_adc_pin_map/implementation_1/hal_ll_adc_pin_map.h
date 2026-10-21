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
 * ADC channels, value is the ADS register code (R01UH1082 16.3.9).
 */
typedef enum
{
    HAL_LL_ADC_CHANNEL_0 = 0,
    HAL_LL_ADC_CHANNEL_1 = 1,
    HAL_LL_ADC_CHANNEL_16 = 16,
    HAL_LL_ADC_CHANNEL_17 = 17,
    HAL_LL_ADC_CHANNEL_18 = 18,
    HAL_LL_ADC_CHANNEL_19 = 19,
    HAL_LL_ADC_CHANNEL_20 = 20,
    HAL_LL_ADC_CHANNEL_21 = 21,
    HAL_LL_ADC_CHANNEL_22 = 22,
    HAL_LL_ADC_CHANNEL_23 = 23,
    HAL_LL_ADC_CHANNEL_24 = 24,
    HAL_LL_ADC_CHANNEL_25 = 25,
    HAL_LL_ADC_CHANNEL_26 = 26,

    HAL_LL_ADC_CHANNEL_NC = 0xFF
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
    #ifdef ADC0_P201_AN000
    {GPIO_P201, HAL_LL_ADC0_BASE_ADDR, hal_ll_adc_module_num( ADC_MODULE_0 ), HAL_LL_ADC_CHANNEL_0},
    #endif
    #ifdef ADC0_P200_AN001
    {GPIO_P200, HAL_LL_ADC0_BASE_ADDR, hal_ll_adc_module_num( ADC_MODULE_0 ), HAL_LL_ADC_CHANNEL_1},
    #endif
    #ifdef ADC0_P202_AN016
    {GPIO_P202, HAL_LL_ADC0_BASE_ADDR, hal_ll_adc_module_num( ADC_MODULE_0 ), HAL_LL_ADC_CHANNEL_16},
    #endif
    #ifdef ADC0_P203_AN017
    {GPIO_P203, HAL_LL_ADC0_BASE_ADDR, hal_ll_adc_module_num( ADC_MODULE_0 ), HAL_LL_ADC_CHANNEL_17},
    #endif
    #ifdef ADC0_P204_AN018
    {GPIO_P204, HAL_LL_ADC0_BASE_ADDR, hal_ll_adc_module_num( ADC_MODULE_0 ), HAL_LL_ADC_CHANNEL_18},
    #endif
    #ifdef ADC0_P205_AN019
    {GPIO_P205, HAL_LL_ADC0_BASE_ADDR, hal_ll_adc_module_num( ADC_MODULE_0 ), HAL_LL_ADC_CHANNEL_19},
    #endif
    #ifdef ADC0_P206_AN020
    {GPIO_P206, HAL_LL_ADC0_BASE_ADDR, hal_ll_adc_module_num( ADC_MODULE_0 ), HAL_LL_ADC_CHANNEL_20},
    #endif
    #ifdef ADC0_P207_AN021
    {GPIO_P207, HAL_LL_ADC0_BASE_ADDR, hal_ll_adc_module_num( ADC_MODULE_0 ), HAL_LL_ADC_CHANNEL_21},
    #endif
    #ifdef ADC0_P100_AN022
    {GPIO_P100, HAL_LL_ADC0_BASE_ADDR, hal_ll_adc_module_num( ADC_MODULE_0 ), HAL_LL_ADC_CHANNEL_22},
    #endif
    #ifdef ADC0_P101_AN023
    {GPIO_P101, HAL_LL_ADC0_BASE_ADDR, hal_ll_adc_module_num( ADC_MODULE_0 ), HAL_LL_ADC_CHANNEL_23},
    #endif
    #ifdef ADC0_P102_AN024
    {GPIO_P102, HAL_LL_ADC0_BASE_ADDR, hal_ll_adc_module_num( ADC_MODULE_0 ), HAL_LL_ADC_CHANNEL_24},
    #endif
    #ifdef ADC0_P103_AN025
    {GPIO_P103, HAL_LL_ADC0_BASE_ADDR, hal_ll_adc_module_num( ADC_MODULE_0 ), HAL_LL_ADC_CHANNEL_25},
    #endif
    #ifdef ADC0_P104_AN026
    {GPIO_P104, HAL_LL_ADC0_BASE_ADDR, hal_ll_adc_module_num( ADC_MODULE_0 ), HAL_LL_ADC_CHANNEL_26},
    #endif

    {HAL_LL_PIN_NC, HAL_LL_MODULE_ERROR, HAL_LL_PIN_NC, HAL_LL_ADC_CHANNEL_NC}
    //------------ END
};

#ifdef __cplusplus
}
#endif

#endif // _HAL_LL_ADC_PIN_MAP_H_
// ------------------------------------------------------------------------- END
