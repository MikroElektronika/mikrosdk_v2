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
 * @file  hal_ll_analog_in_map.h
 * @brief Macros used for setting pin analog functionality.
 */

#ifndef _HAL_LL_ANALOG_IN_MAP_H_
#define _HAL_LL_ANALOG_IN_MAP_H_

#ifdef __cplusplus
extern "C"{
#endif

#include "hal_ll_pin_names.h"

/**
 * @note Defining register for MCUs that don't have it defined.
 */
#ifndef HAL_LL_AD2PCFGL_REG_ADDRESS
#define HAL_LL_AD2PCFGL_REG_ADDRESS 0
#endif

/*!< @brief Helper macro for getting adequate module index number */
#define hal_ll_adc_module_num(_module_num) (_module_num - 1)

typedef struct {
    uint16_t address[2];
} analog_in_registers_t;

typedef struct {
    hal_ll_pin_name_t pin;
    uint8_t module_index;
    analog_in_registers_t analog_in_register_addresses;
    uint8_t analog_in_register_bit;
    uint8_t analog_in_channel_bit;
    uint8_t analog_write_value;
} hal_ll_pin_channel_list_t;

static const hal_ll_pin_channel_list_t hal_ll_analog_in_register_list[] =
{
    //------------ BEGIN
    // BEGIN ADPCFG
    #ifdef _ADC_ADPCFG_
    #ifdef ADC_RB0_AN0
    {PB0, hal_ll_adc_module_num(ADC_MODULE), {HAL_LL_ADPCFG_REG_ADDRESS, 0}, ADC_RB0, ADC_RB0_AN0, 0},
    #endif
    #ifdef ADC_RB1_AN1
    {PB1, hal_ll_adc_module_num(ADC_MODULE), {HAL_LL_ADPCFG_REG_ADDRESS, 0}, ADC_RB1, ADC_RB1_AN1, 0},
    #endif
    #ifdef ADC_RB2_AN2
    {PB2, hal_ll_adc_module_num(ADC_MODULE), {HAL_LL_ADPCFG_REG_ADDRESS, 0}, ADC_RB2, ADC_RB2_AN2, 0},
    #endif
    #ifdef ADC_RB3_AN3
    {PB3, hal_ll_adc_module_num(ADC_MODULE), {HAL_LL_ADPCFG_REG_ADDRESS, 0}, ADC_RB3, ADC_RB3_AN3, 0},
    #endif
    #ifdef ADC_RB4_AN4
    {PB4, hal_ll_adc_module_num(ADC_MODULE), {HAL_LL_ADPCFG_REG_ADDRESS, 0}, ADC_RB4, ADC_RB4_AN4, 0},
    #endif
    #ifdef ADC_RB5_AN5
    {PB5, hal_ll_adc_module_num(ADC_MODULE), {HAL_LL_ADPCFG_REG_ADDRESS, 0}, ADC_RB5, ADC_RB5_AN5, 0},
    #endif
    #ifdef ADC_RB6_AN6
    {PB6, hal_ll_adc_module_num(ADC_MODULE), {HAL_LL_ADPCFG_REG_ADDRESS, 0}, ADC_RB6, ADC_RB6_AN6, 0},
    #endif
    #ifdef ADC_RB7_AN7
    {PB7, hal_ll_adc_module_num(ADC_MODULE), {HAL_LL_ADPCFG_REG_ADDRESS, 0}, ADC_RB7, ADC_RB7_AN7, 0},
    #endif
    #ifdef ADC_RB8_AN8
    {PB8, hal_ll_adc_module_num(ADC_MODULE), {HAL_LL_ADPCFG_REG_ADDRESS, 0}, ADC_RB8, ADC_RB8_AN8, 0},
    #endif
    #ifdef ADC_RB9_AN9
    {PB9, hal_ll_adc_module_num(ADC_MODULE), {HAL_LL_ADPCFG_REG_ADDRESS, 0}, ADC_RB9, ADC_RB9_AN9, 0},
    #endif
    #ifdef ADC_RB10_AN10
    {PB10, hal_ll_adc_module_num(ADC_MODULE), {HAL_LL_ADPCFG_REG_ADDRESS, 0}, ADC_RB10, ADC_RB10_AN10, 0},
    #endif
    #ifdef ADC_RB11_AN11
    {PB11, hal_ll_adc_module_num(ADC_MODULE), {HAL_LL_ADPCFG_REG_ADDRESS, 0}, ADC_RB11, ADC_RB11_AN11, 0},
    #endif
    #ifdef ADC_RB12_AN12
    {PB12, hal_ll_adc_module_num(ADC_MODULE), {HAL_LL_ADPCFG_REG_ADDRESS, 0}, ADC_RB12, ADC_RB12_AN12, 0},
    #endif
    #ifdef ADC_RB13_AN13
    {PB13, hal_ll_adc_module_num(ADC_MODULE), {HAL_LL_ADPCFG_REG_ADDRESS, 0}, ADC_RB13, ADC_RB13_AN13, 0},
    #endif
    #ifdef ADC_RB14_AN14
    {PB14, hal_ll_adc_module_num(ADC_MODULE), {HAL_LL_ADPCFG_REG_ADDRESS, 0}, ADC_RB14, ADC_RB14_AN14, 0},
    #endif
    #ifdef ADC_RB15_AN15
    {PB15, hal_ll_adc_module_num(ADC_MODULE), {HAL_LL_ADPCFG_REG_ADDRESS, 0}, ADC_RB15, ADC_RB15_AN15, 0},
    #endif
    #ifdef ADC1_RA0_AN0
    {PA0, hal_ll_adc_module_num(ADC_MODULE_1), {HAL_LL_ADPCFG_REG_ADDRESS, 0}, ADC1_RA0, ADC1_RA0_AN0, 0},
    #endif
    #ifdef ADC1_RA1_AN1
    {PA1, hal_ll_adc_module_num(ADC_MODULE_1), {HAL_LL_ADPCFG_REG_ADDRESS, 0}, ADC1_RA1, ADC1_RA1_AN1, 0},
    #endif
    #ifdef ADC1_RA2_AN32
    {PA2, hal_ll_adc_module_num(ADC_MODULE_1), {HAL_LL_ADPCFG_REG_ADDRESS, 0}, ADC1_RA2, ADC1_RA2_AN32, 0},
    #endif
    #ifdef ADC1_RA4_AN24
    {PA4, hal_ll_adc_module_num(ADC_MODULE_1), {HAL_LL_ADPCFG_REG_ADDRESS, 0}, ADC1_RA4, ADC1_RA4_AN24, 0},
    #endif
    #ifdef ADC1_RA9_AN28
    {PA9, hal_ll_adc_module_num(ADC_MODULE_1), {HAL_LL_ADPCFG_REG_ADDRESS, 0}, ADC1_RA9, ADC1_RA9_AN28, 0},
    #endif
    #ifdef ADC1_RB0_AN2
    {PB0, hal_ll_adc_module_num(ADC_MODULE_1), {HAL_LL_ADPCFG_REG_ADDRESS, 0}, ADC1_RB0, ADC1_RB0_AN2, 0},
    #endif
    #ifdef ADC1_RB1_AN3
    {PB1, hal_ll_adc_module_num(ADC_MODULE_1), {HAL_LL_ADPCFG_REG_ADDRESS, 0}, ADC1_RB1, ADC1_RB1_AN3, 0},
    #endif
    #ifdef ADC1_RB2_AN4
    {PB2, hal_ll_adc_module_num(ADC_MODULE_1), {HAL_LL_ADPCFG_REG_ADDRESS, 0}, ADC1_RB2, ADC1_RB2_AN4, 0},
    #endif
    #ifdef ADC1_RB3_AN5
    {PB3, hal_ll_adc_module_num(ADC_MODULE_1), {HAL_LL_ADPCFG_REG_ADDRESS, 0}, ADC1_RB3, ADC1_RB3_AN5, 0},
    #endif
    #ifdef ADC1_RB7_AN25
    {PB7, hal_ll_adc_module_num(ADC_MODULE_1), {HAL_LL_ADPCFG_REG_ADDRESS, 0}, ADC1_RB7, ADC1_RB7_AN25, 0},
    #endif
    #ifdef ADC1_RB8_AN26
    {PB8, hal_ll_adc_module_num(ADC_MODULE_1), {HAL_LL_ADPCFG_REG_ADDRESS, 0}, ADC1_RB8, ADC1_RB8_AN26, 0},
    #endif
    #ifdef ADC1_RB9_AN27
    {PB9, hal_ll_adc_module_num(ADC_MODULE_1), {HAL_LL_ADPCFG_REG_ADDRESS, 0}, ADC1_RB9, ADC1_RB9_AN27, 0},
    #endif
    #ifdef ADC1_RC0_AN6
    {PC0, hal_ll_adc_module_num(ADC_MODULE_1), {HAL_LL_ADPCFG_REG_ADDRESS, 0}, ADC1_RC0, ADC1_RC0_AN6, 0},
    #endif
    #ifdef ADC1_RC1_AN7
    {PC1, hal_ll_adc_module_num(ADC_MODULE_1), {HAL_LL_ADPCFG_REG_ADDRESS, 0}, ADC1_RC1, ADC1_RC1_AN7, 0},
    #endif
    #ifdef ADC1_RC2_AN8
    {PC2, hal_ll_adc_module_num(ADC_MODULE_1), {HAL_LL_ADPCFG_REG_ADDRESS, 0}, ADC1_RC2, ADC1_RC2_AN8, 0},
    #endif
    #ifdef ADC1_RC3_AN29
    {PC3, hal_ll_adc_module_num(ADC_MODULE_1), {HAL_LL_ADPCFG_REG_ADDRESS, 0}, ADC1_RC3, ADC1_RC3_AN29, 0},
    #endif
    #ifdef ADC1_RC4_AN30
    {PC4, hal_ll_adc_module_num(ADC_MODULE_1), {HAL_LL_ADPCFG_REG_ADDRESS, 0}, ADC1_RC4, ADC1_RC4_AN30, 0},
    #endif
    #ifdef ADC1_RC5_AN31
    {PC5, hal_ll_adc_module_num(ADC_MODULE_1), {HAL_LL_ADPCFG_REG_ADDRESS, 0}, ADC1_RC5, ADC1_RC5_AN31, 0},
    #endif
    #ifdef ADC2_RA0_AN0
    {PA0, hal_ll_adc_module_num(ADC_MODULE_2), {HAL_LL_ADPCFG_REG_ADDRESS, 0}, ADC2_RA0, ADC2_RA0_AN0, 0},
    #endif
    #ifdef ADC2_RA1_AN1
    {PA1, hal_ll_adc_module_num(ADC_MODULE_2), {HAL_LL_ADPCFG_REG_ADDRESS, 0}, ADC2_RA1, ADC2_RA1_AN1, 0},
    #endif
    #ifdef ADC2_RA4_AN24
    {PA4, hal_ll_adc_module_num(ADC_MODULE_2), {HAL_LL_ADPCFG_REG_ADDRESS, 0}, ADC2_RA4, ADC2_RA4_AN24, 0},
    #endif
    #ifdef ADC2_RA9_AN28
    {PA9, hal_ll_adc_module_num(ADC_MODULE_2), {HAL_LL_ADPCFG_REG_ADDRESS, 0}, ADC2_RA9, ADC2_RA9_AN28, 0},
    #endif
    #ifdef ADC2_RB0_AN2
    {PB0, hal_ll_adc_module_num(ADC_MODULE_2), {HAL_LL_ADPCFG_REG_ADDRESS, 0}, ADC2_RB0, ADC2_RB0_AN2, 0},
    #endif
    #ifdef ADC2_RB1_AN3
    {PB1, hal_ll_adc_module_num(ADC_MODULE_2), {HAL_LL_ADPCFG_REG_ADDRESS, 0}, ADC2_RB1, ADC2_RB1_AN3, 0},
    #endif
    #ifdef ADC2_RB2_AN4
    {PB2, hal_ll_adc_module_num(ADC_MODULE_2), {HAL_LL_ADPCFG_REG_ADDRESS, 0}, ADC2_RB2, ADC2_RB2_AN4, 0},
    #endif
    #ifdef ADC2_RB3_AN5
    {PB3, hal_ll_adc_module_num(ADC_MODULE_2), {HAL_LL_ADPCFG_REG_ADDRESS, 0}, ADC2_RB3, ADC2_RB3_AN5, 0},
    #endif
    #ifdef ADC2_RB7_AN25
    {PB7, hal_ll_adc_module_num(ADC_MODULE_2), {HAL_LL_ADPCFG_REG_ADDRESS, 0}, ADC2_RB7, ADC2_RB7_AN25, 0},
    #endif
    #ifdef ADC2_RB8_AN26
    {PB8, hal_ll_adc_module_num(ADC_MODULE_2), {HAL_LL_ADPCFG_REG_ADDRESS, 0}, ADC2_RB8, ADC2_RB8_AN26, 0},
    #endif
    #ifdef ADC2_RB9_AN27
    {PB9, hal_ll_adc_module_num(ADC_MODULE_2), {HAL_LL_ADPCFG_REG_ADDRESS, 0}, ADC2_RB9, ADC2_RB9_AN27, 0},
    #endif
    #ifdef ADC2_RC0_AN6
    {PC0, hal_ll_adc_module_num(ADC_MODULE_2), {HAL_LL_ADPCFG_REG_ADDRESS, 0}, ADC2_RC0, ADC2_RC0_AN6, 0},
    #endif
    #ifdef ADC2_RC1_AN7
    {PC1, hal_ll_adc_module_num(ADC_MODULE_2), {HAL_LL_ADPCFG_REG_ADDRESS, 0}, ADC2_RC1, ADC2_RC1_AN7, 0},
    #endif
    #ifdef ADC2_RC2_AN8
    {PC2, hal_ll_adc_module_num(ADC_MODULE_2), {HAL_LL_ADPCFG_REG_ADDRESS, 0}, ADC2_RC2, ADC2_RC2_AN8, 0},
    #endif
    #ifdef ADC2_RC3_AN29
    {PC3, hal_ll_adc_module_num(ADC_MODULE_2), {HAL_LL_ADPCFG_REG_ADDRESS, 0}, ADC2_RC3, ADC2_RC3_AN29, 0},
    #endif
    #ifdef ADC2_RC4_AN30
    {PC4, hal_ll_adc_module_num(ADC_MODULE_2), {HAL_LL_ADPCFG_REG_ADDRESS, 0}, ADC2_RC4, ADC2_RC4_AN30, 0},
    #endif
    #ifdef ADC2_RC5_AN31
    {PC5, hal_ll_adc_module_num(ADC_MODULE_2), {HAL_LL_ADPCFG_REG_ADDRESS, 0}, ADC2_RC5, ADC2_RC5_AN31, 0},
    #endif
    #ifdef ADC1_RA11_AN9
    {PA11, hal_ll_adc_module_num(ADC_MODULE_1), {HAL_LL_ADPCFG_REG_ADDRESS, 0}, ADC1_RA11, ADC1_RA11_AN9, 0},
    #endif
    #ifdef ADC1_RA12_AN10
    {PA12, hal_ll_adc_module_num(ADC_MODULE_1), {HAL_LL_ADPCFG_REG_ADDRESS, 0}, ADC1_RA12, ADC1_RA12_AN10, 0},
    #endif
    #ifdef ADC1_RC10_AN48
    {PC10, hal_ll_adc_module_num(ADC_MODULE_1), {HAL_LL_ADPCFG_REG_ADDRESS, 0}, ADC1_RC10, ADC1_RC10_AN48, 0},
    #endif
    #ifdef ADC1_RC11_AN11
    {PC11, hal_ll_adc_module_num(ADC_MODULE_1), {HAL_LL_ADPCFG_REG_ADDRESS, 0}, ADC1_RC11, ADC1_RC11_AN11, 0},
    #endif
    #ifdef ADC1_RC12_AN49
    {PC12, hal_ll_adc_module_num(ADC_MODULE_1), {HAL_LL_ADPCFG_REG_ADDRESS, 0}, ADC1_RC12, ADC1_RC12_AN49, 0},
    #endif
    #ifdef ADC1_RE12_AN12
    {PE12, hal_ll_adc_module_num(ADC_MODULE_1), {HAL_LL_ADPCFG_REG_ADDRESS, 0}, ADC1_RE12, ADC1_RE12_AN12, 0},
    #endif
    #ifdef ADC1_RE13_AN13
    {PE13, hal_ll_adc_module_num(ADC_MODULE_1), {HAL_LL_ADPCFG_REG_ADDRESS, 0}, ADC1_RE13, ADC1_RE13_AN13, 0},
    #endif
    #ifdef ADC1_RE14_AN14
    {PE14, hal_ll_adc_module_num(ADC_MODULE_1), {HAL_LL_ADPCFG_REG_ADDRESS, 0}, ADC1_RE14, ADC1_RE14_AN14, 0},
    #endif
    #ifdef ADC1_RE15_AN15
    {PE15, hal_ll_adc_module_num(ADC_MODULE_1), {HAL_LL_ADPCFG_REG_ADDRESS, 0}, ADC1_RE15, ADC1_RE15_AN15, 0},
    #endif
    #ifdef ADC1_RG6_AN19
    {PG6, hal_ll_adc_module_num(ADC_MODULE_1), {HAL_LL_ADPCFG_REG_ADDRESS, 0}, ADC1_RG6, ADC1_RG6_AN19, 0},
    #endif
    #ifdef ADC1_RG7_AN18
    {PG7, hal_ll_adc_module_num(ADC_MODULE_1), {HAL_LL_ADPCFG_REG_ADDRESS, 0}, ADC1_RG7, ADC1_RG7_AN18, 0},
    #endif
    #ifdef ADC1_RG8_AN17
    {PG8, hal_ll_adc_module_num(ADC_MODULE_1), {HAL_LL_ADPCFG_REG_ADDRESS, 0}, ADC1_RG8, ADC1_RG8_AN17, 0},
    #endif
    #ifdef ADC1_RG9_AN16
    {PG9, hal_ll_adc_module_num(ADC_MODULE_1), {HAL_LL_ADPCFG_REG_ADDRESS, 0}, ADC1_RG9, ADC1_RG9_AN16, 0},
    #endif
    #ifdef ADC2_RA11_AN9
    {PA11, hal_ll_adc_module_num(ADC_MODULE_2), {HAL_LL_ADPCFG_REG_ADDRESS, 0}, ADC2_RA11, ADC2_RA11_AN9, 0},
    #endif
    #ifdef ADC2_RA12_AN10
    {PA12, hal_ll_adc_module_num(ADC_MODULE_2), {HAL_LL_ADPCFG_REG_ADDRESS, 0}, ADC2_RA12, ADC2_RA12_AN10, 0},
    #endif
    #ifdef ADC2_RC11_AN11
    {PC11, hal_ll_adc_module_num(ADC_MODULE_2), {HAL_LL_ADPCFG_REG_ADDRESS, 0}, ADC2_RC11, ADC2_RC11_AN11, 0},
    #endif
    #ifdef ADC2_RE12_AN12
    {PE12, hal_ll_adc_module_num(ADC_MODULE_2), {HAL_LL_ADPCFG_REG_ADDRESS, 0}, ADC2_RE12, ADC2_RE12_AN12, 0},
    #endif
    #ifdef ADC2_RE13_AN13
    {PE13, hal_ll_adc_module_num(ADC_MODULE_2), {HAL_LL_ADPCFG_REG_ADDRESS, 0}, ADC2_RE13, ADC2_RE13_AN13, 0},
    #endif
    #ifdef ADC2_RE14_AN14
    {PE14, hal_ll_adc_module_num(ADC_MODULE_2), {HAL_LL_ADPCFG_REG_ADDRESS, 0}, ADC2_RE14, ADC2_RE14_AN14, 0},
    #endif
    #ifdef ADC2_RE15_AN15
    {PE15, hal_ll_adc_module_num(ADC_MODULE_2), {HAL_LL_ADPCFG_REG_ADDRESS, 0}, ADC2_RE15, ADC2_RE15_AN15, 0},
    #endif
    #ifdef ADC2_RG6_AN19
    {PG6, hal_ll_adc_module_num(ADC_MODULE_2), {HAL_LL_ADPCFG_REG_ADDRESS, 0}, ADC2_RG6, ADC2_RG6_AN19, 0},
    #endif
    #ifdef ADC2_RG7_AN18
    {PG7, hal_ll_adc_module_num(ADC_MODULE_2), {HAL_LL_ADPCFG_REG_ADDRESS, 0}, ADC2_RG7, ADC2_RG7_AN18, 0},
    #endif
    #ifdef ADC2_RG8_AN17
    {PG8, hal_ll_adc_module_num(ADC_MODULE_2), {HAL_LL_ADPCFG_REG_ADDRESS, 0}, ADC2_RG8, ADC2_RG8_AN17, 0},
    #endif
    #ifdef ADC2_RG9_AN16
    {PG9, hal_ll_adc_module_num(ADC_MODULE_2), {HAL_LL_ADPCFG_REG_ADDRESS, 0}, ADC2_RG9, ADC2_RG9_AN16, 0},
    #endif
    #ifdef ADC1_RA14_AN46
    {PA14, hal_ll_adc_module_num(ADC_MODULE_1), {HAL_LL_ADPCFG_REG_ADDRESS, 0}, ADC1_RA14, ADC1_RA14_AN46, 0},
    #endif
    #ifdef ADC1_RA15_AN47
    {PA15, hal_ll_adc_module_num(ADC_MODULE_1), {HAL_LL_ADPCFG_REG_ADDRESS, 0}, ADC1_RA15, ADC1_RA15_AN47, 0},
    #endif
    #ifdef ADC1_RD14_AN38
    {PD14, hal_ll_adc_module_num(ADC_MODULE_1), {HAL_LL_ADPCFG_REG_ADDRESS, 0}, ADC1_RD14, ADC1_RD14_AN38, 0},
    #endif
    #ifdef ADC1_RD15_AN39
    {PD15, hal_ll_adc_module_num(ADC_MODULE_1), {HAL_LL_ADPCFG_REG_ADDRESS, 0}, ADC1_RD15, ADC1_RD15_AN39, 0},
    #endif
    #ifdef ADC1_RE0_AN40
    {PE0, hal_ll_adc_module_num(ADC_MODULE_1), {HAL_LL_ADPCFG_REG_ADDRESS, 0}, ADC1_RE0, ADC1_RE0_AN40, 0},
    #endif
    #ifdef ADC1_RE1_AN41
    {PE1, hal_ll_adc_module_num(ADC_MODULE_1), {HAL_LL_ADPCFG_REG_ADDRESS, 0}, ADC1_RE1, ADC1_RE1_AN41, 0},
    #endif
    #ifdef ADC1_RE8_AN21
    {PE8, hal_ll_adc_module_num(ADC_MODULE_1), {HAL_LL_ADPCFG_REG_ADDRESS, 0}, ADC1_RE8, ADC1_RE8_AN21, 0},
    #endif
    #ifdef ADC1_RE9_AN20
    {PE9, hal_ll_adc_module_num(ADC_MODULE_1), {HAL_LL_ADPCFG_REG_ADDRESS, 0}, ADC1_RE9, ADC1_RE9_AN20, 0},
    #endif
    #ifdef ADC1_RF10_AN34
    {PF10, hal_ll_adc_module_num(ADC_MODULE_1), {HAL_LL_ADPCFG_REG_ADDRESS, 0}, ADC1_RF10, ADC1_RF10_AN34, 0},
    #endif
    #ifdef ADC1_RF12_AN37
    {PF12, hal_ll_adc_module_num(ADC_MODULE_1), {HAL_LL_ADPCFG_REG_ADDRESS, 0}, ADC1_RF12, ADC1_RF12_AN37, 0},
    #endif
    #ifdef ADC1_RF13_AN36
    {PF13, hal_ll_adc_module_num(ADC_MODULE_1), {HAL_LL_ADPCFG_REG_ADDRESS, 0}, ADC1_RF13, ADC1_RF13_AN36, 0},
    #endif
    #ifdef ADC1_RF4_AN44
    {PF4, hal_ll_adc_module_num(ADC_MODULE_1), {HAL_LL_ADPCFG_REG_ADDRESS, 0}, ADC1_RF4, ADC1_RF4_AN44, 0},
    #endif
    #ifdef ADC1_RF5_AN45
    {PF5, hal_ll_adc_module_num(ADC_MODULE_1), {HAL_LL_ADPCFG_REG_ADDRESS, 0}, ADC1_RF5, ADC1_RF5_AN45, 0},
    #endif
    #ifdef ADC1_RF9_AN33
    {PF9, hal_ll_adc_module_num(ADC_MODULE_1), {HAL_LL_ADPCFG_REG_ADDRESS, 0}, ADC1_RF9, ADC1_RF9_AN33, 0},
    #endif
    #ifdef ADC1_RG10_AN22
    {PG10, hal_ll_adc_module_num(ADC_MODULE_1), {HAL_LL_ADPCFG_REG_ADDRESS, 0}, ADC1_RG10, ADC1_RG10_AN22, 0},
    #endif
    #ifdef ADC1_RG11_AN35
    {PG11, hal_ll_adc_module_num(ADC_MODULE_1), {HAL_LL_ADPCFG_REG_ADDRESS, 0}, ADC1_RG11, ADC1_RG11_AN35, 0},
    #endif
    #ifdef ADC1_RG15_AN23
    {PG15, hal_ll_adc_module_num(ADC_MODULE_1), {HAL_LL_ADPCFG_REG_ADDRESS, 0}, ADC1_RG15, ADC1_RG15_AN23, 0},
    #endif
    #ifdef ADC1_RG2_AN42
    {PG2, hal_ll_adc_module_num(ADC_MODULE_1), {HAL_LL_ADPCFG_REG_ADDRESS, 0}, ADC1_RG2, ADC1_RG2_AN42, 0},
    #endif
    #ifdef ADC1_RG3_AN43
    {PG3, hal_ll_adc_module_num(ADC_MODULE_1), {HAL_LL_ADPCFG_REG_ADDRESS, 0}, ADC1_RG3, ADC1_RG3_AN43, 0},
    #endif
    #ifdef ADC2_RE8_AN21
    {PE8, hal_ll_adc_module_num(ADC_MODULE_2), {HAL_LL_ADPCFG_REG_ADDRESS, 0}, ADC2_RE8, ADC2_RE8_AN21, 0},
    #endif
    #ifdef ADC2_RE9_AN20
    {PE9, hal_ll_adc_module_num(ADC_MODULE_2), {HAL_LL_ADPCFG_REG_ADDRESS, 0}, ADC2_RE9, ADC2_RE9_AN20, 0},
    #endif
    #ifdef ADC2_RG10_AN22
    {PG10, hal_ll_adc_module_num(ADC_MODULE_2), {HAL_LL_ADPCFG_REG_ADDRESS, 0}, ADC2_RG10, ADC2_RG10_AN22, 0},
    #endif
    #ifdef ADC2_RG15_AN23
    {PG15, hal_ll_adc_module_num(ADC_MODULE_2), {HAL_LL_ADPCFG_REG_ADDRESS, 0}, ADC2_RG15, ADC2_RG15_AN23, 0},
    #endif
    #ifdef ADC1_RA2_AN2
    {PA2, hal_ll_adc_module_num(ADC_MODULE_1), {HAL_LL_ADPCFG_REG_ADDRESS, 0}, ADC1_RA2, ADC1_RA2_AN2, 0},
    #endif
    #ifdef ADC1_RB0_AN3
    {PB0, hal_ll_adc_module_num(ADC_MODULE_1), {HAL_LL_ADPCFG_REG_ADDRESS, 0}, ADC1_RB0, ADC1_RB0_AN3, 0},
    #endif
    #ifdef ADC1_RB1_AN6
    {PB1, hal_ll_adc_module_num(ADC_MODULE_1), {HAL_LL_ADPCFG_REG_ADDRESS, 0}, ADC1_RB1, ADC1_RB1_AN6, 0},
    #endif
    #ifdef ADC1_RB2_AN7
    {PB2, hal_ll_adc_module_num(ADC_MODULE_1), {HAL_LL_ADPCFG_REG_ADDRESS, 0}, ADC1_RB2, ADC1_RB2_AN7, 0},
    #endif
    #ifdef ADC1_RB3_AN18
    {PB3, hal_ll_adc_module_num(ADC_MODULE_1), {HAL_LL_ADPCFG_REG_ADDRESS, 0}, ADC1_RB3, ADC1_RB3_AN18, 0},
    #endif
    #ifdef ADC1_RB5_AN19
    {PB5, hal_ll_adc_module_num(ADC_MODULE_1), {HAL_LL_ADPCFG_REG_ADDRESS, 0}, ADC1_RB5, ADC1_RB5_AN19, 0},
    #endif
    #ifdef ADC1_RB6_AN20
    {PB6, hal_ll_adc_module_num(ADC_MODULE_1), {HAL_LL_ADPCFG_REG_ADDRESS, 0}, ADC1_RB6, ADC1_RB6_AN20, 0},
    #endif
    #ifdef ADC1_RB7_AN21
    {PB7, hal_ll_adc_module_num(ADC_MODULE_1), {HAL_LL_ADPCFG_REG_ADDRESS, 0}, ADC1_RB7, ADC1_RB7_AN21, 0},
    #endif
    #ifdef ADC1_RB9_AN4
    {PB9, hal_ll_adc_module_num(ADC_MODULE_1), {HAL_LL_ADPCFG_REG_ADDRESS, 0}, ADC1_RB9, ADC1_RB9_AN4, 0},
    #endif
    #ifdef ADC1_RC1_AN8
    {PC1, hal_ll_adc_module_num(ADC_MODULE_1), {HAL_LL_ADPCFG_REG_ADDRESS, 0}, ADC1_RC1, ADC1_RC1_AN8, 0},
    #endif
    #ifdef ADC1_RC10_AN10
    {PC10, hal_ll_adc_module_num(ADC_MODULE_1), {HAL_LL_ADPCFG_REG_ADDRESS, 0}, ADC1_RC10, ADC1_RC10_AN10, 0},
    #endif
    #ifdef ADC1_RC12_AN14
    {PC12, hal_ll_adc_module_num(ADC_MODULE_1), {HAL_LL_ADPCFG_REG_ADDRESS, 0}, ADC1_RC12, ADC1_RC12_AN14, 0},
    #endif
    #ifdef ADC1_RC2_AN9
    {PC2, hal_ll_adc_module_num(ADC_MODULE_1), {HAL_LL_ADPCFG_REG_ADDRESS, 0}, ADC1_RC2, ADC1_RC2_AN9, 0},
    #endif
    #ifdef ADC1_RC6_AN17
    {PC6, hal_ll_adc_module_num(ADC_MODULE_1), {HAL_LL_ADPCFG_REG_ADDRESS, 0}, ADC1_RC6, ADC1_RC6_AN17, 0},
    #endif
    #ifdef ADC1_RC9_AN11
    {PC9, hal_ll_adc_module_num(ADC_MODULE_1), {HAL_LL_ADPCFG_REG_ADDRESS, 0}, ADC1_RC9, ADC1_RC9_AN11, 0},
    #endif
    #ifdef ADC1_RD13_AN13
    {PD13, hal_ll_adc_module_num(ADC_MODULE_1), {HAL_LL_ADPCFG_REG_ADDRESS, 0}, ADC1_RD13, ADC1_RD13_AN13, 0},
    #endif
    #ifdef ADC1_RD2_AN16
    {PD2, hal_ll_adc_module_num(ADC_MODULE_1), {HAL_LL_ADPCFG_REG_ADDRESS, 0}, ADC1_RD2, ADC1_RD2_AN16, 0},
    #endif
    #ifdef ADC1_RD5_AN12
    {PD5, hal_ll_adc_module_num(ADC_MODULE_1), {HAL_LL_ADPCFG_REG_ADDRESS, 0}, ADC1_RD5, ADC1_RD5_AN12, 0},
    #endif
    #ifdef ADC1_RD7_AN15
    {PD7, hal_ll_adc_module_num(ADC_MODULE_1), {HAL_LL_ADPCFG_REG_ADDRESS, 0}, ADC1_RD7, ADC1_RD7_AN15, 0},
    #endif
    #ifdef ADC1_RD8_AN5
    {PD8, hal_ll_adc_module_num(ADC_MODULE_1), {HAL_LL_ADPCFG_REG_ADDRESS, 0}, ADC1_RD8, ADC1_RD8_AN5, 0},
    #endif
    #ifdef ADC1_RB10_AN5
    {PB10, hal_ll_adc_module_num(ADC_MODULE_1), {HAL_LL_ADPCFG_REG_ADDRESS, 0}, ADC1_RB10, ADC1_RB10_AN5, 0},
    #endif
    #ifdef ADC1_RB3_AN8
    {PB3, hal_ll_adc_module_num(ADC_MODULE_1), {HAL_LL_ADPCFG_REG_ADDRESS, 0}, ADC1_RB3, ADC1_RB3_AN8, 0},
    #endif
    #ifdef ADC1_RB5_AN9
    {PB5, hal_ll_adc_module_num(ADC_MODULE_1), {HAL_LL_ADPCFG_REG_ADDRESS, 0}, ADC1_RB5, ADC1_RB5_AN9, 0},
    #endif
    #ifdef ADC1_RB6_AN10
    {PB6, hal_ll_adc_module_num(ADC_MODULE_1), {HAL_LL_ADPCFG_REG_ADDRESS, 0}, ADC1_RB6, ADC1_RB6_AN10, 0},
    #endif
    #ifdef ADC1_RB7_AN11
    {PB7, hal_ll_adc_module_num(ADC_MODULE_1), {HAL_LL_ADPCFG_REG_ADDRESS, 0}, ADC1_RB7, ADC1_RB7_AN11, 0},
    #endif
    #ifdef ADC1_RC11_AN12
    {PC11, hal_ll_adc_module_num(ADC_MODULE_1), {HAL_LL_ADPCFG_REG_ADDRESS, 0}, ADC1_RC11, ADC1_RC11_AN12, 0},
    #endif
    #ifdef ADC1_RB0_AN0
    {PB0, hal_ll_adc_module_num(ADC_MODULE_1), {HAL_LL_ADPCFG_REG_ADDRESS, 0}, ADC1_RB0, ADC1_RB0_AN0, 0},
    #endif
    #ifdef ADC1_RB1_AN1
    {PB1, hal_ll_adc_module_num(ADC_MODULE_1), {HAL_LL_ADPCFG_REG_ADDRESS, 0}, ADC1_RB1, ADC1_RB1_AN1, 0},
    #endif
    #ifdef ADC1_RB10_AN10
    {PB10, hal_ll_adc_module_num(ADC_MODULE_1), {HAL_LL_ADPCFG_REG_ADDRESS, 0}, ADC1_RB10, ADC1_RB10_AN10, 0},
    #endif
    #ifdef ADC1_RB11_AN11
    {PB11, hal_ll_adc_module_num(ADC_MODULE_1), {HAL_LL_ADPCFG_REG_ADDRESS, 0}, ADC1_RB11, ADC1_RB11_AN11, 0},
    #endif
    #ifdef ADC1_RB12_AN12
    {PB12, hal_ll_adc_module_num(ADC_MODULE_1), {HAL_LL_ADPCFG_REG_ADDRESS, 0}, ADC1_RB12, ADC1_RB12_AN12, 0},
    #endif
    #ifdef ADC1_RB13_AN13
    {PB13, hal_ll_adc_module_num(ADC_MODULE_1), {HAL_LL_ADPCFG_REG_ADDRESS, 0}, ADC1_RB13, ADC1_RB13_AN13, 0},
    #endif
    #ifdef ADC1_RB14_AN14
    {PB14, hal_ll_adc_module_num(ADC_MODULE_1), {HAL_LL_ADPCFG_REG_ADDRESS, 0}, ADC1_RB14, ADC1_RB14_AN14, 0},
    #endif
    #ifdef ADC1_RB15_AN15
    {PB15, hal_ll_adc_module_num(ADC_MODULE_1), {HAL_LL_ADPCFG_REG_ADDRESS, 0}, ADC1_RB15, ADC1_RB15_AN15, 0},
    #endif
    #ifdef ADC1_RB2_AN2
    {PB2, hal_ll_adc_module_num(ADC_MODULE_1), {HAL_LL_ADPCFG_REG_ADDRESS, 0}, ADC1_RB2, ADC1_RB2_AN2, 0},
    #endif
    #ifdef ADC1_RB3_AN3
    {PB3, hal_ll_adc_module_num(ADC_MODULE_1), {HAL_LL_ADPCFG_REG_ADDRESS, 0}, ADC1_RB3, ADC1_RB3_AN3, 0},
    #endif
    #ifdef ADC1_RB4_AN4
    {PB4, hal_ll_adc_module_num(ADC_MODULE_1), {HAL_LL_ADPCFG_REG_ADDRESS, 0}, ADC1_RB4, ADC1_RB4_AN4, 0},
    #endif
    #ifdef ADC1_RB5_AN5
    {PB5, hal_ll_adc_module_num(ADC_MODULE_1), {HAL_LL_ADPCFG_REG_ADDRESS, 0}, ADC1_RB5, ADC1_RB5_AN5, 0},
    #endif
    #ifdef ADC1_RB6_AN6
    {PB6, hal_ll_adc_module_num(ADC_MODULE_1), {HAL_LL_ADPCFG_REG_ADDRESS, 0}, ADC1_RB6, ADC1_RB6_AN6, 0},
    #endif
    #ifdef ADC1_RB7_AN7
    {PB7, hal_ll_adc_module_num(ADC_MODULE_1), {HAL_LL_ADPCFG_REG_ADDRESS, 0}, ADC1_RB7, ADC1_RB7_AN7, 0},
    #endif
    #ifdef ADC1_RB8_AN8
    {PB8, hal_ll_adc_module_num(ADC_MODULE_1), {HAL_LL_ADPCFG_REG_ADDRESS, 0}, ADC1_RB8, ADC1_RB8_AN8, 0},
    #endif
    #ifdef ADC1_RB9_AN9
    {PB9, hal_ll_adc_module_num(ADC_MODULE_1), {HAL_LL_ADPCFG_REG_ADDRESS, 0}, ADC1_RB9, ADC1_RB9_AN9, 0},
    #endif
    #ifdef ADC1_RE0_AN24
    {PE0, hal_ll_adc_module_num(ADC_MODULE_1), {HAL_LL_ADPCFG_REG_ADDRESS, 0}, ADC1_RE0, ADC1_RE0_AN24, 0},
    #endif
    #ifdef ADC1_RE1_AN25
    {PE1, hal_ll_adc_module_num(ADC_MODULE_1), {HAL_LL_ADPCFG_REG_ADDRESS, 0}, ADC1_RE1, ADC1_RE1_AN25, 0},
    #endif
    #ifdef ADC1_RE2_AN26
    {PE2, hal_ll_adc_module_num(ADC_MODULE_1), {HAL_LL_ADPCFG_REG_ADDRESS, 0}, ADC1_RE2, ADC1_RE2_AN26, 0},
    #endif
    #ifdef ADC1_RE3_AN27
    {PE3, hal_ll_adc_module_num(ADC_MODULE_1), {HAL_LL_ADPCFG_REG_ADDRESS, 0}, ADC1_RE3, ADC1_RE3_AN27, 0},
    #endif
    #ifdef ADC1_RE4_AN28
    {PE4, hal_ll_adc_module_num(ADC_MODULE_1), {HAL_LL_ADPCFG_REG_ADDRESS, 0}, ADC1_RE4, ADC1_RE4_AN28, 0},
    #endif
    #ifdef ADC1_RE5_AN29
    {PE5, hal_ll_adc_module_num(ADC_MODULE_1), {HAL_LL_ADPCFG_REG_ADDRESS, 0}, ADC1_RE5, ADC1_RE5_AN29, 0},
    #endif
    #ifdef ADC1_RE6_AN30
    {PE6, hal_ll_adc_module_num(ADC_MODULE_1), {HAL_LL_ADPCFG_REG_ADDRESS, 0}, ADC1_RE6, ADC1_RE6_AN30, 0},
    #endif
    #ifdef ADC1_RE7_AN31
    {PE7, hal_ll_adc_module_num(ADC_MODULE_1), {HAL_LL_ADPCFG_REG_ADDRESS, 0}, ADC1_RE7, ADC1_RE7_AN31, 0},
    #endif
    #ifdef ADC2_RB0_AN0
    {PB0, hal_ll_adc_module_num(ADC_MODULE_2), {HAL_LL_ADPCFG_REG_ADDRESS, 0}, ADC2_RB0, ADC2_RB0_AN0, 0},
    #endif
    #ifdef ADC2_RB1_AN1
    {PB1, hal_ll_adc_module_num(ADC_MODULE_2), {HAL_LL_ADPCFG_REG_ADDRESS, 0}, ADC2_RB1, ADC2_RB1_AN1, 0},
    #endif
    #ifdef ADC2_RB10_AN10
    {PB10, hal_ll_adc_module_num(ADC_MODULE_2), {HAL_LL_ADPCFG_REG_ADDRESS, 0}, ADC2_RB10, ADC2_RB10_AN10, 0},
    #endif
    #ifdef ADC2_RB11_AN11
    {PB11, hal_ll_adc_module_num(ADC_MODULE_2), {HAL_LL_ADPCFG_REG_ADDRESS, 0}, ADC2_RB11, ADC2_RB11_AN11, 0},
    #endif
    #ifdef ADC2_RB12_AN12
    {PB12, hal_ll_adc_module_num(ADC_MODULE_2), {HAL_LL_ADPCFG_REG_ADDRESS, 0}, ADC2_RB12, ADC2_RB12_AN12, 0},
    #endif
    #ifdef ADC2_RB13_AN13
    {PB13, hal_ll_adc_module_num(ADC_MODULE_2), {HAL_LL_ADPCFG_REG_ADDRESS, 0}, ADC2_RB13, ADC2_RB13_AN13, 0},
    #endif
    #ifdef ADC2_RB14_AN14
    {PB14, hal_ll_adc_module_num(ADC_MODULE_2), {HAL_LL_ADPCFG_REG_ADDRESS, 0}, ADC2_RB14, ADC2_RB14_AN14, 0},
    #endif
    #ifdef ADC2_RB15_AN15
    {PB15, hal_ll_adc_module_num(ADC_MODULE_2), {HAL_LL_ADPCFG_REG_ADDRESS, 0}, ADC2_RB15, ADC2_RB15_AN15, 0},
    #endif
    #ifdef ADC2_RB2_AN2
    {PB2, hal_ll_adc_module_num(ADC_MODULE_2), {HAL_LL_ADPCFG_REG_ADDRESS, 0}, ADC2_RB2, ADC2_RB2_AN2, 0},
    #endif
    #ifdef ADC2_RB3_AN3
    {PB3, hal_ll_adc_module_num(ADC_MODULE_2), {HAL_LL_ADPCFG_REG_ADDRESS, 0}, ADC2_RB3, ADC2_RB3_AN3, 0},
    #endif
    #ifdef ADC2_RB4_AN4
    {PB4, hal_ll_adc_module_num(ADC_MODULE_2), {HAL_LL_ADPCFG_REG_ADDRESS, 0}, ADC2_RB4, ADC2_RB4_AN4, 0},
    #endif
    #ifdef ADC2_RB5_AN5
    {PB5, hal_ll_adc_module_num(ADC_MODULE_2), {HAL_LL_ADPCFG_REG_ADDRESS, 0}, ADC2_RB5, ADC2_RB5_AN5, 0},
    #endif
    #ifdef ADC2_RB6_AN6
    {PB6, hal_ll_adc_module_num(ADC_MODULE_2), {HAL_LL_ADPCFG_REG_ADDRESS, 0}, ADC2_RB6, ADC2_RB6_AN6, 0},
    #endif
    #ifdef ADC2_RB7_AN7
    {PB7, hal_ll_adc_module_num(ADC_MODULE_2), {HAL_LL_ADPCFG_REG_ADDRESS, 0}, ADC2_RB7, ADC2_RB7_AN7, 0},
    #endif
    #ifdef ADC2_RB8_AN8
    {PB8, hal_ll_adc_module_num(ADC_MODULE_2), {HAL_LL_ADPCFG_REG_ADDRESS, 0}, ADC2_RB8, ADC2_RB8_AN8, 0},
    #endif
    #ifdef ADC2_RB9_AN9
    {PB9, hal_ll_adc_module_num(ADC_MODULE_2), {HAL_LL_ADPCFG_REG_ADDRESS, 0}, ADC2_RB9, ADC2_RB9_AN9, 0},
    #endif
    #ifdef ADC1_RA6_AN22
    {PA6, hal_ll_adc_module_num(ADC_MODULE_1), {HAL_LL_ADPCFG_REG_ADDRESS, 0}, ADC1_RA6, ADC1_RA6_AN22, 0},
    #endif
    #ifdef ADC1_RA7_AN23
    {PA7, hal_ll_adc_module_num(ADC_MODULE_1), {HAL_LL_ADPCFG_REG_ADDRESS, 0}, ADC1_RA7, ADC1_RA7_AN23, 0},
    #endif
    #ifdef ADC1_RC1_AN16
    {PC1, hal_ll_adc_module_num(ADC_MODULE_1), {HAL_LL_ADPCFG_REG_ADDRESS, 0}, ADC1_RC1, ADC1_RC1_AN16, 0},
    #endif
    #ifdef ADC1_RC2_AN17
    {PC2, hal_ll_adc_module_num(ADC_MODULE_1), {HAL_LL_ADPCFG_REG_ADDRESS, 0}, ADC1_RC2, ADC1_RC2_AN17, 0},
    #endif
    #ifdef ADC1_RC3_AN18
    {PC3, hal_ll_adc_module_num(ADC_MODULE_1), {HAL_LL_ADPCFG_REG_ADDRESS, 0}, ADC1_RC3, ADC1_RC3_AN18, 0},
    #endif
    #ifdef ADC1_RC4_AN19
    {PC4, hal_ll_adc_module_num(ADC_MODULE_1), {HAL_LL_ADPCFG_REG_ADDRESS, 0}, ADC1_RC4, ADC1_RC4_AN19, 0},
    #endif
    #ifdef ADC1_RE8_AN20
    {PE8, hal_ll_adc_module_num(ADC_MODULE_1), {HAL_LL_ADPCFG_REG_ADDRESS, 0}, ADC1_RE8, ADC1_RE8_AN20, 0},
    #endif
    #ifdef ADC1_RE9_AN21
    {PE9, hal_ll_adc_module_num(ADC_MODULE_1), {HAL_LL_ADPCFG_REG_ADDRESS, 0}, ADC1_RE9, ADC1_RE9_AN21, 0},
    #endif
    #ifdef ADC1_RA10_AN56
    {PA10, hal_ll_adc_module_num(ADC_MODULE_1), {HAL_LL_ADPCFG_REG_ADDRESS, 0}, ADC1_RA10, ADC1_RA10_AN56, 0},
    #endif
    #ifdef ADC1_RA7_AN55
    {PA7, hal_ll_adc_module_num(ADC_MODULE_1), {HAL_LL_ADPCFG_REG_ADDRESS, 0}, ADC1_RA7, ADC1_RA7_AN55, 0},
    #endif
    #ifdef ADC1_RC6_AN53
    {PC6, hal_ll_adc_module_num(ADC_MODULE_1), {HAL_LL_ADPCFG_REG_ADDRESS, 0}, ADC1_RC6, ADC1_RC6_AN53, 0},
    #endif
    #ifdef ADC1_RC7_AN52
    {PC7, hal_ll_adc_module_num(ADC_MODULE_1), {HAL_LL_ADPCFG_REG_ADDRESS, 0}, ADC1_RC7, ADC1_RC7_AN52, 0},
    #endif
    #ifdef ADC1_RC8_AN51
    {PC8, hal_ll_adc_module_num(ADC_MODULE_1), {HAL_LL_ADPCFG_REG_ADDRESS, 0}, ADC1_RC8, ADC1_RC8_AN51, 0},
    #endif
    #ifdef ADC1_RC9_AN54
    {PC9, hal_ll_adc_module_num(ADC_MODULE_1), {HAL_LL_ADPCFG_REG_ADDRESS, 0}, ADC1_RC9, ADC1_RC9_AN54, 0},
    #endif
    #ifdef ADC_RA0_AN0
    {PA0, hal_ll_adc_module_num(ADC_MODULE), {HAL_LL_ADPCFG_REG_ADDRESS, 0}, ADC_RA0, ADC_RA0_AN0, 0},
    #endif
    #ifdef ADC_RA1_AN1
    {PA1, hal_ll_adc_module_num(ADC_MODULE), {HAL_LL_ADPCFG_REG_ADDRESS, 0}, ADC_RA1, ADC_RA1_AN1, 0},
    #endif
    #ifdef ADC_RB0_AN2
    {PB0, hal_ll_adc_module_num(ADC_MODULE), {HAL_LL_ADPCFG_REG_ADDRESS, 0}, ADC_RB0, ADC_RB0_AN2, 0},
    #endif
    #ifdef ADC_RB1_AN3
    {PB1, hal_ll_adc_module_num(ADC_MODULE), {HAL_LL_ADPCFG_REG_ADDRESS, 0}, ADC_RB1, ADC_RB1_AN3, 0},
    #endif
    #ifdef ADC_RB13_AN11
    {PB13, hal_ll_adc_module_num(ADC_MODULE), {HAL_LL_ADPCFG_REG_ADDRESS, 0}, ADC_RB13, ADC_RB13_AN11, 0},
    #endif
    #ifdef ADC_RB14_AN10
    {PB14, hal_ll_adc_module_num(ADC_MODULE), {HAL_LL_ADPCFG_REG_ADDRESS, 0}, ADC_RB14, ADC_RB14_AN10, 0},
    #endif
    #ifdef ADC_RB15_AN9
    {PB15, hal_ll_adc_module_num(ADC_MODULE), {HAL_LL_ADPCFG_REG_ADDRESS, 0}, ADC_RB15, ADC_RB15_AN9, 0},
    #endif
    #ifdef ADC_RB2_AN4
    {PB2, hal_ll_adc_module_num(ADC_MODULE), {HAL_LL_ADPCFG_REG_ADDRESS, 0}, ADC_RB2, ADC_RB2_AN4, 0},
    #endif
    #ifdef ADC_RB3_AN5
    {PB3, hal_ll_adc_module_num(ADC_MODULE), {HAL_LL_ADPCFG_REG_ADDRESS, 0}, ADC_RB3, ADC_RB3_AN5, 0},
    #endif
    #ifdef ADC_RC0_AN6
    {PC0, hal_ll_adc_module_num(ADC_MODULE), {HAL_LL_ADPCFG_REG_ADDRESS, 0}, ADC_RC0, ADC_RC0_AN6, 0},
    #endif
    #ifdef ADC_RC1_AN7
    {PC1, hal_ll_adc_module_num(ADC_MODULE), {HAL_LL_ADPCFG_REG_ADDRESS, 0}, ADC_RC1, ADC_RC1_AN7, 0},
    #endif
    #ifdef ADC_RC2_AN8
    {PC2, hal_ll_adc_module_num(ADC_MODULE), {HAL_LL_ADPCFG_REG_ADDRESS, 0}, ADC_RC2, ADC_RC2_AN8, 0},
    #endif
    #ifdef ADC_RC1_AN16
    {PC1, hal_ll_adc_module_num(ADC_MODULE), {HAL_LL_ADPCFG_REG_ADDRESS, 0}, ADC_RC1, ADC_RC1_AN16, 0},
    #endif
    #ifdef ADC_RC2_AN17
    {PC2, hal_ll_adc_module_num(ADC_MODULE), {HAL_LL_ADPCFG_REG_ADDRESS, 0}, ADC_RC2, ADC_RC2_AN17, 0},
    #endif
    #ifdef ADC_RA12_AN20
    {PA12, hal_ll_adc_module_num(ADC_MODULE), {HAL_LL_ADPCFG_REG_ADDRESS, 0}, ADC_RA12, ADC_RA12_AN20, 0},
    #endif
    #ifdef ADC_RA13_AN21
    {PA13, hal_ll_adc_module_num(ADC_MODULE), {HAL_LL_ADPCFG_REG_ADDRESS, 0}, ADC_RA13, ADC_RA13_AN21, 0},
    #endif
    #ifdef ADC_RA6_AN22
    {PA6, hal_ll_adc_module_num(ADC_MODULE), {HAL_LL_ADPCFG_REG_ADDRESS, 0}, ADC_RA6, ADC_RA6_AN22, 0},
    #endif
    #ifdef ADC_RA7_AN23
    {PA7, hal_ll_adc_module_num(ADC_MODULE), {HAL_LL_ADPCFG_REG_ADDRESS, 0}, ADC_RA7, ADC_RA7_AN23, 0},
    #endif
    #ifdef ADC_RC3_AN18
    {PC3, hal_ll_adc_module_num(ADC_MODULE), {HAL_LL_ADPCFG_REG_ADDRESS, 0}, ADC_RC3, ADC_RC3_AN18, 0},
    #endif
    #ifdef ADC_RC4_AN19
    {PC4, hal_ll_adc_module_num(ADC_MODULE), {HAL_LL_ADPCFG_REG_ADDRESS, 0}, ADC_RC4, ADC_RC4_AN19, 0},
    #endif
    #ifdef ADC_RE0_AN24
    {PE0, hal_ll_adc_module_num(ADC_MODULE), {HAL_LL_ADPCFG_REG_ADDRESS, 0}, ADC_RE0, ADC_RE0_AN24, 0},
    #endif
    #ifdef ADC_RE1_AN25
    {PE1, hal_ll_adc_module_num(ADC_MODULE), {HAL_LL_ADPCFG_REG_ADDRESS, 0}, ADC_RE1, ADC_RE1_AN25, 0},
    #endif
    #ifdef ADC_RE2_AN26
    {PE2, hal_ll_adc_module_num(ADC_MODULE), {HAL_LL_ADPCFG_REG_ADDRESS, 0}, ADC_RE2, ADC_RE2_AN26, 0},
    #endif
    #ifdef ADC_RE3_AN27
    {PE3, hal_ll_adc_module_num(ADC_MODULE), {HAL_LL_ADPCFG_REG_ADDRESS, 0}, ADC_RE3, ADC_RE3_AN27, 0},
    #endif
    #ifdef ADC_RE4_AN28
    {PE4, hal_ll_adc_module_num(ADC_MODULE), {HAL_LL_ADPCFG_REG_ADDRESS, 0}, ADC_RE4, ADC_RE4_AN28, 0},
    #endif
    #ifdef ADC_RE5_AN29
    {PE5, hal_ll_adc_module_num(ADC_MODULE), {HAL_LL_ADPCFG_REG_ADDRESS, 0}, ADC_RE5, ADC_RE5_AN29, 0},
    #endif
    #ifdef ADC_RE6_AN30
    {PE6, hal_ll_adc_module_num(ADC_MODULE), {HAL_LL_ADPCFG_REG_ADDRESS, 0}, ADC_RE6, ADC_RE6_AN30, 0},
    #endif
    #ifdef ADC_RE7_AN31
    {PE7, hal_ll_adc_module_num(ADC_MODULE), {HAL_LL_ADPCFG_REG_ADDRESS, 0}, ADC_RE7, ADC_RE7_AN31, 0},
    #endif
    #ifdef ADC2_RC1_AN16
    {PC1, hal_ll_adc_module_num(ADC_MODULE_2), {HAL_LL_ADPCFG_REG_ADDRESS, 0}, ADC2_RC1, ADC2_RC1_AN16, 0},
    #endif
    #ifdef ADC2_RC2_AN17
    {PC2, hal_ll_adc_module_num(ADC_MODULE_2), {HAL_LL_ADPCFG_REG_ADDRESS, 0}, ADC2_RC2, ADC2_RC2_AN17, 0},
    #endif
    #ifdef ADC1_RA12_AN20
    {PA12, hal_ll_adc_module_num(ADC_MODULE_1), {HAL_LL_ADPCFG_REG_ADDRESS, 0}, ADC1_RA12, ADC1_RA12_AN20, 0},
    #endif
    #ifdef ADC1_RA13_AN21
    {PA13, hal_ll_adc_module_num(ADC_MODULE_1), {HAL_LL_ADPCFG_REG_ADDRESS, 0}, ADC1_RA13, ADC1_RA13_AN21, 0},
    #endif
    #ifdef ADC2_RA12_AN20
    {PA12, hal_ll_adc_module_num(ADC_MODULE_2), {HAL_LL_ADPCFG_REG_ADDRESS, 0}, ADC2_RA12, ADC2_RA12_AN20, 0},
    #endif
    #ifdef ADC2_RA13_AN21
    {PA13, hal_ll_adc_module_num(ADC_MODULE_2), {HAL_LL_ADPCFG_REG_ADDRESS, 0}, ADC2_RA13, ADC2_RA13_AN21, 0},
    #endif
    #ifdef ADC2_RA6_AN22
    {PA6, hal_ll_adc_module_num(ADC_MODULE_2), {HAL_LL_ADPCFG_REG_ADDRESS, 0}, ADC2_RA6, ADC2_RA6_AN22, 0},
    #endif
    #ifdef ADC2_RA7_AN23
    {PA7, hal_ll_adc_module_num(ADC_MODULE_2), {HAL_LL_ADPCFG_REG_ADDRESS, 0}, ADC2_RA7, ADC2_RA7_AN23, 0},
    #endif
    #ifdef ADC2_RC3_AN18
    {PC3, hal_ll_adc_module_num(ADC_MODULE_2), {HAL_LL_ADPCFG_REG_ADDRESS, 0}, ADC2_RC3, ADC2_RC3_AN18, 0},
    #endif
    #ifdef ADC2_RC4_AN19
    {PC4, hal_ll_adc_module_num(ADC_MODULE_2), {HAL_LL_ADPCFG_REG_ADDRESS, 0}, ADC2_RC4, ADC2_RC4_AN19, 0},
    #endif
    #ifdef ADC2_RE0_AN24
    {PE0, hal_ll_adc_module_num(ADC_MODULE_2), {HAL_LL_ADPCFG_REG_ADDRESS, 0}, ADC2_RE0, ADC2_RE0_AN24, 0},
    #endif
    #ifdef ADC2_RE1_AN25
    {PE1, hal_ll_adc_module_num(ADC_MODULE_2), {HAL_LL_ADPCFG_REG_ADDRESS, 0}, ADC2_RE1, ADC2_RE1_AN25, 0},
    #endif
    #ifdef ADC2_RE2_AN26
    {PE2, hal_ll_adc_module_num(ADC_MODULE_2), {HAL_LL_ADPCFG_REG_ADDRESS, 0}, ADC2_RE2, ADC2_RE2_AN26, 0},
    #endif
    #ifdef ADC2_RE3_AN27
    {PE3, hal_ll_adc_module_num(ADC_MODULE_2), {HAL_LL_ADPCFG_REG_ADDRESS, 0}, ADC2_RE3, ADC2_RE3_AN27, 0},
    #endif
    #ifdef ADC2_RE4_AN28
    {PE4, hal_ll_adc_module_num(ADC_MODULE_2), {HAL_LL_ADPCFG_REG_ADDRESS, 0}, ADC2_RE4, ADC2_RE4_AN28, 0},
    #endif
    #ifdef ADC2_RE5_AN29
    {PE5, hal_ll_adc_module_num(ADC_MODULE_2), {HAL_LL_ADPCFG_REG_ADDRESS, 0}, ADC2_RE5, ADC2_RE5_AN29, 0},
    #endif
    #ifdef ADC2_RE6_AN30
    {PE6, hal_ll_adc_module_num(ADC_MODULE_2), {HAL_LL_ADPCFG_REG_ADDRESS, 0}, ADC2_RE6, ADC2_RE6_AN30, 0},
    #endif
    #ifdef ADC2_RE7_AN31
    {PE7, hal_ll_adc_module_num(ADC_MODULE_2), {HAL_LL_ADPCFG_REG_ADDRESS, 0}, ADC2_RE7, ADC2_RE7_AN31, 0},
    #endif
    #ifdef ADC_RE8_AN20
    {PE8, hal_ll_adc_module_num(ADC_MODULE), {HAL_LL_ADPCFG_REG_ADDRESS, 0}, ADC_RE8, ADC_RE8_AN20, 0},
    #endif
    #ifdef ADC_RE9_AN21
    {PE9, hal_ll_adc_module_num(ADC_MODULE), {HAL_LL_ADPCFG_REG_ADDRESS, 0}, ADC_RE9, ADC_RE9_AN21, 0},
    #endif
    #ifdef ADC2_RE8_AN20
    {PE8, hal_ll_adc_module_num(ADC_MODULE_2), {HAL_LL_ADPCFG_REG_ADDRESS, 0}, ADC2_RE8, ADC2_RE8_AN20, 0},
    #endif
    #ifdef ADC2_RE9_AN21
    {PE9, hal_ll_adc_module_num(ADC_MODULE_2), {HAL_LL_ADPCFG_REG_ADDRESS, 0}, ADC2_RE9, ADC2_RE9_AN21, 0},
    #endif
    #ifdef ADC_RA2_AN2
    {PA2, hal_ll_adc_module_num(ADC_MODULE), {HAL_LL_ADPCFG_REG_ADDRESS, 0}, ADC_RA2, ADC_RA2_AN2, 0},
    #endif
    #ifdef ADC_RB0_AN3
    {PB0, hal_ll_adc_module_num(ADC_MODULE), {HAL_LL_ADPCFG_REG_ADDRESS, 0}, ADC_RB0, ADC_RB0_AN3, 0},
    #endif
    #ifdef ADC_RB1_AN6
    {PB1, hal_ll_adc_module_num(ADC_MODULE), {HAL_LL_ADPCFG_REG_ADDRESS, 0}, ADC_RB1, ADC_RB1_AN6, 0},
    #endif
    #ifdef ADC_RB10_AN5
    {PB10, hal_ll_adc_module_num(ADC_MODULE), {HAL_LL_ADPCFG_REG_ADDRESS, 0}, ADC_RB10, ADC_RB10_AN5, 0},
    #endif
    #ifdef ADC_RB2_AN7
    {PB2, hal_ll_adc_module_num(ADC_MODULE), {HAL_LL_ADPCFG_REG_ADDRESS, 0}, ADC_RB2, ADC_RB2_AN7, 0},
    #endif
    #ifdef ADC_RB9_AN4
    {PB9, hal_ll_adc_module_num(ADC_MODULE), {HAL_LL_ADPCFG_REG_ADDRESS, 0}, ADC_RB9, ADC_RB9_AN4, 0},
    #endif
    #ifdef ADC_RC1_AN8
    {PC1, hal_ll_adc_module_num(ADC_MODULE), {HAL_LL_ADPCFG_REG_ADDRESS, 0}, ADC_RC1, ADC_RC1_AN8, 0},
    #endif
    #ifdef ADC_RC10_AN10
    {PC10, hal_ll_adc_module_num(ADC_MODULE), {HAL_LL_ADPCFG_REG_ADDRESS, 0}, ADC_RC10, ADC_RC10_AN10, 0},
    #endif
    #ifdef ADC_RC2_AN9
    {PC2, hal_ll_adc_module_num(ADC_MODULE), {HAL_LL_ADPCFG_REG_ADDRESS, 0}, ADC_RC2, ADC_RC2_AN9, 0},
    #endif
    #ifdef ADC_RC9_AN11
    {PC9, hal_ll_adc_module_num(ADC_MODULE), {HAL_LL_ADPCFG_REG_ADDRESS, 0}, ADC_RC9, ADC_RC9_AN11, 0},
    #endif
    #ifdef ADC_RA4_AN10
    {PA4, hal_ll_adc_module_num(ADC_MODULE), {HAL_LL_ADPCFG_REG_ADDRESS, 0}, ADC_RA4, ADC_RA4_AN10, 0},
    #endif
    #ifdef ADC_RB4_AN9
    {PB4, hal_ll_adc_module_num(ADC_MODULE), {HAL_LL_ADPCFG_REG_ADDRESS, 0}, ADC_RB4, ADC_RB4_AN9, 0},
    #endif
    #ifdef ADC_RC3_AN11
    {PC3, hal_ll_adc_module_num(ADC_MODULE), {HAL_LL_ADPCFG_REG_ADDRESS, 0}, ADC_RC3, ADC_RC3_AN11, 0},
    #endif
    #ifdef ADC_RC4_AN12
    {PC4, hal_ll_adc_module_num(ADC_MODULE), {HAL_LL_ADPCFG_REG_ADDRESS, 0}, ADC_RC4, ADC_RC4_AN12, 0},
    #endif
    #ifdef ADC_RC5_AN15
    {PC5, hal_ll_adc_module_num(ADC_MODULE), {HAL_LL_ADPCFG_REG_ADDRESS, 0}, ADC_RC5, ADC_RC5_AN15, 0},
    #endif
    #ifdef ADC1_RA2_AN13
    {PA2, hal_ll_adc_module_num(ADC_MODULE_1), {HAL_LL_ADPCFG_REG_ADDRESS, 0}, ADC1_RA2, ADC1_RA2_AN13, 0},
    #endif
    #ifdef ADC1_RA3_AN14
    {PA3, hal_ll_adc_module_num(ADC_MODULE_1), {HAL_LL_ADPCFG_REG_ADDRESS, 0}, ADC1_RA3, ADC1_RA3_AN14, 0},
    #endif
    #ifdef ADC1_RB13_AN11
    {PB13, hal_ll_adc_module_num(ADC_MODULE_1), {HAL_LL_ADPCFG_REG_ADDRESS, 0}, ADC1_RB13, ADC1_RB13_AN11, 0},
    #endif
    #ifdef ADC1_RB14_AN10
    {PB14, hal_ll_adc_module_num(ADC_MODULE_1), {HAL_LL_ADPCFG_REG_ADDRESS, 0}, ADC1_RB14, ADC1_RB14_AN10, 0},
    #endif
    #ifdef ADC1_RB15_AN9
    {PB15, hal_ll_adc_module_num(ADC_MODULE_1), {HAL_LL_ADPCFG_REG_ADDRESS, 0}, ADC1_RB15, ADC1_RB15_AN9, 0},
    #endif
    #ifdef ADC1_RB4_AN15
    {PB4, hal_ll_adc_module_num(ADC_MODULE_1), {HAL_LL_ADPCFG_REG_ADDRESS, 0}, ADC1_RB4, ADC1_RB4_AN15, 0},
    #endif
    #ifdef ADC1_RA4_AN16
    {PA4, hal_ll_adc_module_num(ADC_MODULE_1), {HAL_LL_ADPCFG_REG_ADDRESS, 0}, ADC1_RA4, ADC1_RA4_AN16, 0},
    #endif
    #ifdef ADC1_RB5_AN17
    {PB5, hal_ll_adc_module_num(ADC_MODULE_1), {HAL_LL_ADPCFG_REG_ADDRESS, 0}, ADC1_RB5, ADC1_RB5_AN17, 0},
    #endif
    #ifdef ADC1_RB6_AN18
    {PB6, hal_ll_adc_module_num(ADC_MODULE_1), {HAL_LL_ADPCFG_REG_ADDRESS, 0}, ADC1_RB6, ADC1_RB6_AN18, 0},
    #endif
    #ifdef ADC1_RB7_AN19
    {PB7, hal_ll_adc_module_num(ADC_MODULE_1), {HAL_LL_ADPCFG_REG_ADDRESS, 0}, ADC1_RB7, ADC1_RB7_AN19, 0},
    #endif
    #ifdef ADC1_RB8_AN20
    {PB8, hal_ll_adc_module_num(ADC_MODULE_1), {HAL_LL_ADPCFG_REG_ADDRESS, 0}, ADC1_RB8, ADC1_RB8_AN20, 0},
    #endif
    #ifdef ADC1_RB9_AN21
    {PB9, hal_ll_adc_module_num(ADC_MODULE_1), {HAL_LL_ADPCFG_REG_ADDRESS, 0}, ADC1_RB9, ADC1_RB9_AN21, 0},
    #endif
    #ifdef ADC1_RA6_AN23
    {PA6, hal_ll_adc_module_num(ADC_MODULE_1), {HAL_LL_ADPCFG_REG_ADDRESS, 0}, ADC1_RA6, ADC1_RA6_AN23, 0},
    #endif
    #ifdef ADC1_RA7_AN22
    {PA7, hal_ll_adc_module_num(ADC_MODULE_1), {HAL_LL_ADPCFG_REG_ADDRESS, 0}, ADC1_RA7, ADC1_RA7_AN22, 0},
    #endif
    #ifdef ADC1_RC4_AN16
    {PC4, hal_ll_adc_module_num(ADC_MODULE_1), {HAL_LL_ADPCFG_REG_ADDRESS, 0}, ADC1_RC4, ADC1_RC4_AN16, 0},
    #endif
    #ifdef ADC1_RG6_AN17
    {PG6, hal_ll_adc_module_num(ADC_MODULE_1), {HAL_LL_ADPCFG_REG_ADDRESS, 0}, ADC1_RG6, ADC1_RG6_AN17, 0},
    #endif
    #ifdef ADC1_RG8_AN19
    {PG8, hal_ll_adc_module_num(ADC_MODULE_1), {HAL_LL_ADPCFG_REG_ADDRESS, 0}, ADC1_RG8, ADC1_RG8_AN19, 0},
    #endif
    #ifdef ADC1_RG9_AN20
    {PG9, hal_ll_adc_module_num(ADC_MODULE_1), {HAL_LL_ADPCFG_REG_ADDRESS, 0}, ADC1_RG9, ADC1_RG9_AN20, 0},
    #endif
    #ifdef ADC1_RB12_AN8
    {PB12, hal_ll_adc_module_num(ADC_MODULE_1), {HAL_LL_ADPCFG_REG_ADDRESS, 0}, ADC1_RB12, ADC1_RB12_AN8, 0},
    #endif
    #ifdef ADC1_RB13_AN7
    {PB13, hal_ll_adc_module_num(ADC_MODULE_1), {HAL_LL_ADPCFG_REG_ADDRESS, 0}, ADC1_RB13, ADC1_RB13_AN7, 0},
    #endif
    #ifdef ADC1_RB14_AN6
    {PB14, hal_ll_adc_module_num(ADC_MODULE_1), {HAL_LL_ADPCFG_REG_ADDRESS, 0}, ADC1_RB14, ADC1_RB14_AN6, 0},
    #endif
    #ifdef ADC1_RC0_AN10
    {PC0, hal_ll_adc_module_num(ADC_MODULE_1), {HAL_LL_ADPCFG_REG_ADDRESS, 0}, ADC1_RC0, ADC1_RC0_AN10, 0},
    #endif
    #ifdef ADC1_RC1_AN11
    {PC1, hal_ll_adc_module_num(ADC_MODULE_1), {HAL_LL_ADPCFG_REG_ADDRESS, 0}, ADC1_RC1, ADC1_RC1_AN11, 0},
    #endif
    #ifdef ADC1_RC2_AN12
    {PC2, hal_ll_adc_module_num(ADC_MODULE_1), {HAL_LL_ADPCFG_REG_ADDRESS, 0}, ADC1_RC2, ADC1_RC2_AN12, 0},
    #endif
    #ifdef ADC1_RC3_AN13
    {PC3, hal_ll_adc_module_num(ADC_MODULE_1), {HAL_LL_ADPCFG_REG_ADDRESS, 0}, ADC1_RC3, ADC1_RC3_AN13, 0},
    #endif
    #ifdef ADC1_RD0_AN43
    {PD0, hal_ll_adc_module_num(ADC_MODULE_1), {HAL_LL_ADPCFG_REG_ADDRESS, 0}, ADC1_RD0, ADC1_RD0_AN43, 0},
    #endif
    #ifdef ADC1_RD1_AN35
    {PD1, hal_ll_adc_module_num(ADC_MODULE_1), {HAL_LL_ADPCFG_REG_ADDRESS, 0}, ADC1_RD1, ADC1_RD1_AN35, 0},
    #endif
    #ifdef ADC1_RD10_AN41
    {PD10, hal_ll_adc_module_num(ADC_MODULE_1), {HAL_LL_ADPCFG_REG_ADDRESS, 0}, ADC1_RD10, ADC1_RD10_AN41, 0},
    #endif
    #ifdef ADC1_RD11_AN42
    {PD11, hal_ll_adc_module_num(ADC_MODULE_1), {HAL_LL_ADPCFG_REG_ADDRESS, 0}, ADC1_RD11, ADC1_RD11_AN42, 0},
    #endif
    #ifdef ADC1_RD2_AN25
    {PD2, hal_ll_adc_module_num(ADC_MODULE_1), {HAL_LL_ADPCFG_REG_ADDRESS, 0}, ADC1_RD2, ADC1_RD2_AN25, 0},
    #endif
    #ifdef ADC1_RD3_AN44
    {PD3, hal_ll_adc_module_num(ADC_MODULE_1), {HAL_LL_ADPCFG_REG_ADDRESS, 0}, ADC1_RD3, ADC1_RD3_AN44, 0},
    #endif
    #ifdef ADC1_RD4_AN47
    {PD4, hal_ll_adc_module_num(ADC_MODULE_1), {HAL_LL_ADPCFG_REG_ADDRESS, 0}, ADC1_RD4, ADC1_RD4_AN47, 0},
    #endif
    #ifdef ADC1_RD5_AN48
    {PD5, hal_ll_adc_module_num(ADC_MODULE_1), {HAL_LL_ADPCFG_REG_ADDRESS, 0}, ADC1_RD5, ADC1_RD5_AN48, 0},
    #endif
    #ifdef ADC1_RD6_AN34
    {PD6, hal_ll_adc_module_num(ADC_MODULE_1), {HAL_LL_ADPCFG_REG_ADDRESS, 0}, ADC1_RD6, ADC1_RD6_AN34, 0},
    #endif
    #ifdef ADC1_RD7_AN20
    {PD7, hal_ll_adc_module_num(ADC_MODULE_1), {HAL_LL_ADPCFG_REG_ADDRESS, 0}, ADC1_RD7, ADC1_RD7_AN20, 0},
    #endif
    #ifdef ADC1_RD8_AN40
    {PD8, hal_ll_adc_module_num(ADC_MODULE_1), {HAL_LL_ADPCFG_REG_ADDRESS, 0}, ADC1_RD8, ADC1_RD8_AN40, 0},
    #endif
    #ifdef ADC1_RD9_AN24
    {PD9, hal_ll_adc_module_num(ADC_MODULE_1), {HAL_LL_ADPCFG_REG_ADDRESS, 0}, ADC1_RD9, ADC1_RD9_AN24, 0},
    #endif
    #ifdef ADC1_RF3_AN30
    {PF3, hal_ll_adc_module_num(ADC_MODULE_1), {HAL_LL_ADPCFG_REG_ADDRESS, 0}, ADC1_RF3, ADC1_RF3_AN30, 0},
    #endif
    #ifdef ADC1_RF4_AN11
    {PF4, hal_ll_adc_module_num(ADC_MODULE_1), {HAL_LL_ADPCFG_REG_ADDRESS, 0}, ADC1_RF4, ADC1_RF4_AN11, 0},
    #endif
    #ifdef ADC1_RF5_AN10
    {PF5, hal_ll_adc_module_num(ADC_MODULE_1), {HAL_LL_ADPCFG_REG_ADDRESS, 0}, ADC1_RF5, ADC1_RF5_AN10, 0},
    #endif
    #ifdef ADC1_RG9_AN49
    {PG9, hal_ll_adc_module_num(ADC_MODULE_1), {HAL_LL_ADPCFG_REG_ADDRESS, 0}, ADC1_RG9, ADC1_RG9_AN49, 0},
    #endif
    #ifdef ADC1_RA1_AN26
    {PA1, hal_ll_adc_module_num(ADC_MODULE_1), {HAL_LL_ADPCFG_REG_ADDRESS, 0}, ADC1_RA1, ADC1_RA1_AN26, 0},
    #endif
    #ifdef ADC1_RA14_AN38
    {PA14, hal_ll_adc_module_num(ADC_MODULE_1), {HAL_LL_ADPCFG_REG_ADDRESS, 0}, ADC1_RA14, ADC1_RA14_AN38, 0},
    #endif
    #ifdef ADC1_RA15_AN39
    {PA15, hal_ll_adc_module_num(ADC_MODULE_1), {HAL_LL_ADPCFG_REG_ADDRESS, 0}, ADC1_RA15, ADC1_RA15_AN39, 0},
    #endif
    #ifdef ADC1_RA4_AN36
    {PA4, hal_ll_adc_module_num(ADC_MODULE_1), {HAL_LL_ADPCFG_REG_ADDRESS, 0}, ADC1_RA4, ADC1_RA4_AN36, 0},
    #endif
    #ifdef ADC1_RA5_AN37
    {PA5, hal_ll_adc_module_num(ADC_MODULE_1), {HAL_LL_ADPCFG_REG_ADDRESS, 0}, ADC1_RA5, ADC1_RA5_AN37, 0},
    #endif
    #ifdef ADC1_RC3_AN9
    {PC3, hal_ll_adc_module_num(ADC_MODULE_1), {HAL_LL_ADPCFG_REG_ADDRESS, 0}, ADC1_RC3, ADC1_RC3_AN9, 0},
    #endif
    #ifdef ADC1_RD12_AN45
    {PD12, hal_ll_adc_module_num(ADC_MODULE_1), {HAL_LL_ADPCFG_REG_ADDRESS, 0}, ADC1_RD12, ADC1_RD12_AN45, 0},
    #endif
    #ifdef ADC1_RD13_AN46
    {PD13, hal_ll_adc_module_num(ADC_MODULE_1), {HAL_LL_ADPCFG_REG_ADDRESS, 0}, ADC1_RD13, ADC1_RD13_AN46, 0},
    #endif
    #ifdef ADC1_RD14_AN28
    {PD14, hal_ll_adc_module_num(ADC_MODULE_1), {HAL_LL_ADPCFG_REG_ADDRESS, 0}, ADC1_RD14, ADC1_RD14_AN28, 0},
    #endif
    #ifdef ADC1_RD15_AN29
    {PD15, hal_ll_adc_module_num(ADC_MODULE_1), {HAL_LL_ADPCFG_REG_ADDRESS, 0}, ADC1_RD15, ADC1_RD15_AN29, 0},
    #endif
    #ifdef ADC1_RF13_AN27
    {PF13, hal_ll_adc_module_num(ADC_MODULE_1), {HAL_LL_ADPCFG_REG_ADDRESS, 0}, ADC1_RF13, ADC1_RF13_AN27, 0},
    #endif
    #ifdef ADC1_RF2_AN31
    {PF2, hal_ll_adc_module_num(ADC_MODULE_1), {HAL_LL_ADPCFG_REG_ADDRESS, 0}, ADC1_RF2, ADC1_RF2_AN31, 0},
    #endif
    #ifdef ADC1_RF8_AN32
    {PF8, hal_ll_adc_module_num(ADC_MODULE_1), {HAL_LL_ADPCFG_REG_ADDRESS, 0}, ADC1_RF8, ADC1_RF8_AN32, 0},
    #endif
    #ifdef ADC1_RG15_AN33
    {PG15, hal_ll_adc_module_num(ADC_MODULE_1), {HAL_LL_ADPCFG_REG_ADDRESS, 0}, ADC1_RG15, ADC1_RG15_AN33, 0},
    #endif
    #ifdef ADC1_RC3_AN12
    {PC3, hal_ll_adc_module_num(ADC_MODULE_1), {HAL_LL_ADPCFG_REG_ADDRESS, 0}, ADC1_RC3, ADC1_RC3_AN12, 0},
    #endif
    #endif
    // EOF list

    // BEGIN AD1PCFG
    #ifdef _ADC_AD1PCFG_
    #ifdef ADC_RB0_AN0
    {PB0, hal_ll_adc_module_num(ADC_MODULE), {HAL_LL_AD1PCFG_REG_ADDRESS, 0}, ADC_RB0, ADC_RB0_AN0, 0},
    #endif
    #ifdef ADC_RB1_AN1
    {PB1, hal_ll_adc_module_num(ADC_MODULE), {HAL_LL_AD1PCFG_REG_ADDRESS, 0}, ADC_RB1, ADC_RB1_AN1, 0},
    #endif
    #ifdef ADC_RB2_AN2
    {PB2, hal_ll_adc_module_num(ADC_MODULE), {HAL_LL_AD1PCFG_REG_ADDRESS, 0}, ADC_RB2, ADC_RB2_AN2, 0},
    #endif
    #ifdef ADC_RB3_AN3
    {PB3, hal_ll_adc_module_num(ADC_MODULE), {HAL_LL_AD1PCFG_REG_ADDRESS, 0}, ADC_RB3, ADC_RB3_AN3, 0},
    #endif
    #ifdef ADC_RB4_AN4
    {PB4, hal_ll_adc_module_num(ADC_MODULE), {HAL_LL_AD1PCFG_REG_ADDRESS, 0}, ADC_RB4, ADC_RB4_AN4, 0},
    #endif
    #ifdef ADC_RB5_AN5
    {PB5, hal_ll_adc_module_num(ADC_MODULE), {HAL_LL_AD1PCFG_REG_ADDRESS, 0}, ADC_RB5, ADC_RB5_AN5, 0},
    #endif
    #ifdef ADC_RB6_AN6
    {PB6, hal_ll_adc_module_num(ADC_MODULE), {HAL_LL_AD1PCFG_REG_ADDRESS, 0}, ADC_RB6, ADC_RB6_AN6, 0},
    #endif
    #ifdef ADC_RB7_AN7
    {PB7, hal_ll_adc_module_num(ADC_MODULE), {HAL_LL_AD1PCFG_REG_ADDRESS, 0}, ADC_RB7, ADC_RB7_AN7, 0},
    #endif
    #ifdef ADC_RB8_AN8
    {PB8, hal_ll_adc_module_num(ADC_MODULE), {HAL_LL_AD1PCFG_REG_ADDRESS, 0}, ADC_RB8, ADC_RB8_AN8, 0},
    #endif
    #ifdef ADC_RB9_AN9
    {PB9, hal_ll_adc_module_num(ADC_MODULE), {HAL_LL_AD1PCFG_REG_ADDRESS, 0}, ADC_RB9, ADC_RB9_AN9, 0},
    #endif
    #ifdef ADC_RB10_AN10
    {PB10, hal_ll_adc_module_num(ADC_MODULE), {HAL_LL_AD1PCFG_REG_ADDRESS, 0}, ADC_RB10, ADC_RB10_AN10, 0},
    #endif
    #ifdef ADC_RB11_AN11
    {PB11, hal_ll_adc_module_num(ADC_MODULE), {HAL_LL_AD1PCFG_REG_ADDRESS, 0}, ADC_RB11, ADC_RB11_AN11, 0},
    #endif
    #ifdef ADC_RB12_AN12
    {PB12, hal_ll_adc_module_num(ADC_MODULE), {HAL_LL_AD1PCFG_REG_ADDRESS, 0}, ADC_RB12, ADC_RB12_AN12, 0},
    #endif
    #ifdef ADC_RB13_AN13
    {PB13, hal_ll_adc_module_num(ADC_MODULE), {HAL_LL_AD1PCFG_REG_ADDRESS, 0}, ADC_RB13, ADC_RB13_AN13, 0},
    #endif
    #ifdef ADC_RB14_AN14
    {PB14, hal_ll_adc_module_num(ADC_MODULE), {HAL_LL_AD1PCFG_REG_ADDRESS, 0}, ADC_RB14, ADC_RB14_AN14, 0},
    #endif
    #ifdef ADC_RB15_AN15
    {PB15, hal_ll_adc_module_num(ADC_MODULE), {HAL_LL_AD1PCFG_REG_ADDRESS, 0}, ADC_RB15, ADC_RB15_AN15, 0},
    #endif
    #ifdef ADC1_RA0_AN0
    {PA0, hal_ll_adc_module_num(ADC_MODULE_1), {HAL_LL_AD1PCFG_REG_ADDRESS, 0}, ADC1_RA0, ADC1_RA0_AN0, 0},
    #endif
    #ifdef ADC1_RA1_AN1
    {PA1, hal_ll_adc_module_num(ADC_MODULE_1), {HAL_LL_AD1PCFG_REG_ADDRESS, 0}, ADC1_RA1, ADC1_RA1_AN1, 0},
    #endif
    #ifdef ADC1_RA2_AN32
    {PA2, hal_ll_adc_module_num(ADC_MODULE_1), {HAL_LL_AD1PCFG_REG_ADDRESS, 0}, ADC1_RA2, ADC1_RA2_AN32, 0},
    #endif
    #ifdef ADC1_RA4_AN24
    {PA4, hal_ll_adc_module_num(ADC_MODULE_1), {HAL_LL_AD1PCFG_REG_ADDRESS, 0}, ADC1_RA4, ADC1_RA4_AN24, 0},
    #endif
    #ifdef ADC1_RA9_AN28
    {PA9, hal_ll_adc_module_num(ADC_MODULE_1), {HAL_LL_AD1PCFG_REG_ADDRESS, 0}, ADC1_RA9, ADC1_RA9_AN28, 0},
    #endif
    #ifdef ADC1_RB0_AN2
    {PB0, hal_ll_adc_module_num(ADC_MODULE_1), {HAL_LL_AD1PCFG_REG_ADDRESS, 0}, ADC1_RB0, ADC1_RB0_AN2, 0},
    #endif
    #ifdef ADC1_RB1_AN3
    {PB1, hal_ll_adc_module_num(ADC_MODULE_1), {HAL_LL_AD1PCFG_REG_ADDRESS, 0}, ADC1_RB1, ADC1_RB1_AN3, 0},
    #endif
    #ifdef ADC1_RB2_AN4
    {PB2, hal_ll_adc_module_num(ADC_MODULE_1), {HAL_LL_AD1PCFG_REG_ADDRESS, 0}, ADC1_RB2, ADC1_RB2_AN4, 0},
    #endif
    #ifdef ADC1_RB3_AN5
    {PB3, hal_ll_adc_module_num(ADC_MODULE_1), {HAL_LL_AD1PCFG_REG_ADDRESS, 0}, ADC1_RB3, ADC1_RB3_AN5, 0},
    #endif
    #ifdef ADC1_RB7_AN25
    {PB7, hal_ll_adc_module_num(ADC_MODULE_1), {HAL_LL_AD1PCFG_REG_ADDRESS, 0}, ADC1_RB7, ADC1_RB7_AN25, 0},
    #endif
    #ifdef ADC1_RB8_AN26
    {PB8, hal_ll_adc_module_num(ADC_MODULE_1), {HAL_LL_AD1PCFG_REG_ADDRESS, 0}, ADC1_RB8, ADC1_RB8_AN26, 0},
    #endif
    #ifdef ADC1_RB9_AN27
    {PB9, hal_ll_adc_module_num(ADC_MODULE_1), {HAL_LL_AD1PCFG_REG_ADDRESS, 0}, ADC1_RB9, ADC1_RB9_AN27, 0},
    #endif
    #ifdef ADC1_RC0_AN6
    {PC0, hal_ll_adc_module_num(ADC_MODULE_1), {HAL_LL_AD1PCFG_REG_ADDRESS, 0}, ADC1_RC0, ADC1_RC0_AN6, 0},
    #endif
    #ifdef ADC1_RC1_AN7
    {PC1, hal_ll_adc_module_num(ADC_MODULE_1), {HAL_LL_AD1PCFG_REG_ADDRESS, 0}, ADC1_RC1, ADC1_RC1_AN7, 0},
    #endif
    #ifdef ADC1_RC2_AN8
    {PC2, hal_ll_adc_module_num(ADC_MODULE_1), {HAL_LL_AD1PCFG_REG_ADDRESS, 0}, ADC1_RC2, ADC1_RC2_AN8, 0},
    #endif
    #ifdef ADC1_RC3_AN29
    {PC3, hal_ll_adc_module_num(ADC_MODULE_1), {HAL_LL_AD1PCFG_REG_ADDRESS, 0}, ADC1_RC3, ADC1_RC3_AN29, 0},
    #endif
    #ifdef ADC1_RC4_AN30
    {PC4, hal_ll_adc_module_num(ADC_MODULE_1), {HAL_LL_AD1PCFG_REG_ADDRESS, 0}, ADC1_RC4, ADC1_RC4_AN30, 0},
    #endif
    #ifdef ADC1_RC5_AN31
    {PC5, hal_ll_adc_module_num(ADC_MODULE_1), {HAL_LL_AD1PCFG_REG_ADDRESS, 0}, ADC1_RC5, ADC1_RC5_AN31, 0},
    #endif
    #ifdef ADC2_RA0_AN0
    {PA0, hal_ll_adc_module_num(ADC_MODULE_2), {HAL_LL_AD1PCFG_REG_ADDRESS, 0}, ADC2_RA0, ADC2_RA0_AN0, 0},
    #endif
    #ifdef ADC2_RA1_AN1
    {PA1, hal_ll_adc_module_num(ADC_MODULE_2), {HAL_LL_AD1PCFG_REG_ADDRESS, 0}, ADC2_RA1, ADC2_RA1_AN1, 0},
    #endif
    #ifdef ADC2_RA4_AN24
    {PA4, hal_ll_adc_module_num(ADC_MODULE_2), {HAL_LL_AD1PCFG_REG_ADDRESS, 0}, ADC2_RA4, ADC2_RA4_AN24, 0},
    #endif
    #ifdef ADC2_RA9_AN28
    {PA9, hal_ll_adc_module_num(ADC_MODULE_2), {HAL_LL_AD1PCFG_REG_ADDRESS, 0}, ADC2_RA9, ADC2_RA9_AN28, 0},
    #endif
    #ifdef ADC2_RB0_AN2
    {PB0, hal_ll_adc_module_num(ADC_MODULE_2), {HAL_LL_AD1PCFG_REG_ADDRESS, 0}, ADC2_RB0, ADC2_RB0_AN2, 0},
    #endif
    #ifdef ADC2_RB1_AN3
    {PB1, hal_ll_adc_module_num(ADC_MODULE_2), {HAL_LL_AD1PCFG_REG_ADDRESS, 0}, ADC2_RB1, ADC2_RB1_AN3, 0},
    #endif
    #ifdef ADC2_RB2_AN4
    {PB2, hal_ll_adc_module_num(ADC_MODULE_2), {HAL_LL_AD1PCFG_REG_ADDRESS, 0}, ADC2_RB2, ADC2_RB2_AN4, 0},
    #endif
    #ifdef ADC2_RB3_AN5
    {PB3, hal_ll_adc_module_num(ADC_MODULE_2), {HAL_LL_AD1PCFG_REG_ADDRESS, 0}, ADC2_RB3, ADC2_RB3_AN5, 0},
    #endif
    #ifdef ADC2_RB7_AN25
    {PB7, hal_ll_adc_module_num(ADC_MODULE_2), {HAL_LL_AD1PCFG_REG_ADDRESS, 0}, ADC2_RB7, ADC2_RB7_AN25, 0},
    #endif
    #ifdef ADC2_RB8_AN26
    {PB8, hal_ll_adc_module_num(ADC_MODULE_2), {HAL_LL_AD1PCFG_REG_ADDRESS, 0}, ADC2_RB8, ADC2_RB8_AN26, 0},
    #endif
    #ifdef ADC2_RB9_AN27
    {PB9, hal_ll_adc_module_num(ADC_MODULE_2), {HAL_LL_AD1PCFG_REG_ADDRESS, 0}, ADC2_RB9, ADC2_RB9_AN27, 0},
    #endif
    #ifdef ADC2_RC0_AN6
    {PC0, hal_ll_adc_module_num(ADC_MODULE_2), {HAL_LL_AD1PCFG_REG_ADDRESS, 0}, ADC2_RC0, ADC2_RC0_AN6, 0},
    #endif
    #ifdef ADC2_RC1_AN7
    {PC1, hal_ll_adc_module_num(ADC_MODULE_2), {HAL_LL_AD1PCFG_REG_ADDRESS, 0}, ADC2_RC1, ADC2_RC1_AN7, 0},
    #endif
    #ifdef ADC2_RC2_AN8
    {PC2, hal_ll_adc_module_num(ADC_MODULE_2), {HAL_LL_AD1PCFG_REG_ADDRESS, 0}, ADC2_RC2, ADC2_RC2_AN8, 0},
    #endif
    #ifdef ADC2_RC3_AN29
    {PC3, hal_ll_adc_module_num(ADC_MODULE_2), {HAL_LL_AD1PCFG_REG_ADDRESS, 0}, ADC2_RC3, ADC2_RC3_AN29, 0},
    #endif
    #ifdef ADC2_RC4_AN30
    {PC4, hal_ll_adc_module_num(ADC_MODULE_2), {HAL_LL_AD1PCFG_REG_ADDRESS, 0}, ADC2_RC4, ADC2_RC4_AN30, 0},
    #endif
    #ifdef ADC2_RC5_AN31
    {PC5, hal_ll_adc_module_num(ADC_MODULE_2), {HAL_LL_AD1PCFG_REG_ADDRESS, 0}, ADC2_RC5, ADC2_RC5_AN31, 0},
    #endif
    #ifdef ADC1_RA11_AN9
    {PA11, hal_ll_adc_module_num(ADC_MODULE_1), {HAL_LL_AD1PCFG_REG_ADDRESS, 0}, ADC1_RA11, ADC1_RA11_AN9, 0},
    #endif
    #ifdef ADC1_RA12_AN10
    {PA12, hal_ll_adc_module_num(ADC_MODULE_1), {HAL_LL_AD1PCFG_REG_ADDRESS, 0}, ADC1_RA12, ADC1_RA12_AN10, 0},
    #endif
    #ifdef ADC1_RC10_AN48
    {PC10, hal_ll_adc_module_num(ADC_MODULE_1), {HAL_LL_AD1PCFG_REG_ADDRESS, 0}, ADC1_RC10, ADC1_RC10_AN48, 0},
    #endif
    #ifdef ADC1_RC11_AN11
    {PC11, hal_ll_adc_module_num(ADC_MODULE_1), {HAL_LL_AD1PCFG_REG_ADDRESS, 0}, ADC1_RC11, ADC1_RC11_AN11, 0},
    #endif
    #ifdef ADC1_RC12_AN49
    {PC12, hal_ll_adc_module_num(ADC_MODULE_1), {HAL_LL_AD1PCFG_REG_ADDRESS, 0}, ADC1_RC12, ADC1_RC12_AN49, 0},
    #endif
    #ifdef ADC1_RE12_AN12
    {PE12, hal_ll_adc_module_num(ADC_MODULE_1), {HAL_LL_AD1PCFG_REG_ADDRESS, 0}, ADC1_RE12, ADC1_RE12_AN12, 0},
    #endif
    #ifdef ADC1_RE13_AN13
    {PE13, hal_ll_adc_module_num(ADC_MODULE_1), {HAL_LL_AD1PCFG_REG_ADDRESS, 0}, ADC1_RE13, ADC1_RE13_AN13, 0},
    #endif
    #ifdef ADC1_RE14_AN14
    {PE14, hal_ll_adc_module_num(ADC_MODULE_1), {HAL_LL_AD1PCFG_REG_ADDRESS, 0}, ADC1_RE14, ADC1_RE14_AN14, 0},
    #endif
    #ifdef ADC1_RE15_AN15
    {PE15, hal_ll_adc_module_num(ADC_MODULE_1), {HAL_LL_AD1PCFG_REG_ADDRESS, 0}, ADC1_RE15, ADC1_RE15_AN15, 0},
    #endif
    #ifdef ADC1_RG6_AN19
    {PG6, hal_ll_adc_module_num(ADC_MODULE_1), {HAL_LL_AD1PCFG_REG_ADDRESS, 0}, ADC1_RG6, ADC1_RG6_AN19, 0},
    #endif
    #ifdef ADC1_RG7_AN18
    {PG7, hal_ll_adc_module_num(ADC_MODULE_1), {HAL_LL_AD1PCFG_REG_ADDRESS, 0}, ADC1_RG7, ADC1_RG7_AN18, 0},
    #endif
    #ifdef ADC1_RG8_AN17
    {PG8, hal_ll_adc_module_num(ADC_MODULE_1), {HAL_LL_AD1PCFG_REG_ADDRESS, 0}, ADC1_RG8, ADC1_RG8_AN17, 0},
    #endif
    #ifdef ADC1_RG9_AN16
    {PG9, hal_ll_adc_module_num(ADC_MODULE_1), {HAL_LL_AD1PCFG_REG_ADDRESS, 0}, ADC1_RG9, ADC1_RG9_AN16, 0},
    #endif
    #ifdef ADC2_RA11_AN9
    {PA11, hal_ll_adc_module_num(ADC_MODULE_2), {HAL_LL_AD1PCFG_REG_ADDRESS, 0}, ADC2_RA11, ADC2_RA11_AN9, 0},
    #endif
    #ifdef ADC2_RA12_AN10
    {PA12, hal_ll_adc_module_num(ADC_MODULE_2), {HAL_LL_AD1PCFG_REG_ADDRESS, 0}, ADC2_RA12, ADC2_RA12_AN10, 0},
    #endif
    #ifdef ADC2_RC11_AN11
    {PC11, hal_ll_adc_module_num(ADC_MODULE_2), {HAL_LL_AD1PCFG_REG_ADDRESS, 0}, ADC2_RC11, ADC2_RC11_AN11, 0},
    #endif
    #ifdef ADC2_RE12_AN12
    {PE12, hal_ll_adc_module_num(ADC_MODULE_2), {HAL_LL_AD1PCFG_REG_ADDRESS, 0}, ADC2_RE12, ADC2_RE12_AN12, 0},
    #endif
    #ifdef ADC2_RE13_AN13
    {PE13, hal_ll_adc_module_num(ADC_MODULE_2), {HAL_LL_AD1PCFG_REG_ADDRESS, 0}, ADC2_RE13, ADC2_RE13_AN13, 0},
    #endif
    #ifdef ADC2_RE14_AN14
    {PE14, hal_ll_adc_module_num(ADC_MODULE_2), {HAL_LL_AD1PCFG_REG_ADDRESS, 0}, ADC2_RE14, ADC2_RE14_AN14, 0},
    #endif
    #ifdef ADC2_RE15_AN15
    {PE15, hal_ll_adc_module_num(ADC_MODULE_2), {HAL_LL_AD1PCFG_REG_ADDRESS, 0}, ADC2_RE15, ADC2_RE15_AN15, 0},
    #endif
    #ifdef ADC2_RG6_AN19
    {PG6, hal_ll_adc_module_num(ADC_MODULE_2), {HAL_LL_AD1PCFG_REG_ADDRESS, 0}, ADC2_RG6, ADC2_RG6_AN19, 0},
    #endif
    #ifdef ADC2_RG7_AN18
    {PG7, hal_ll_adc_module_num(ADC_MODULE_2), {HAL_LL_AD1PCFG_REG_ADDRESS, 0}, ADC2_RG7, ADC2_RG7_AN18, 0},
    #endif
    #ifdef ADC2_RG8_AN17
    {PG8, hal_ll_adc_module_num(ADC_MODULE_2), {HAL_LL_AD1PCFG_REG_ADDRESS, 0}, ADC2_RG8, ADC2_RG8_AN17, 0},
    #endif
    #ifdef ADC2_RG9_AN16
    {PG9, hal_ll_adc_module_num(ADC_MODULE_2), {HAL_LL_AD1PCFG_REG_ADDRESS, 0}, ADC2_RG9, ADC2_RG9_AN16, 0},
    #endif
    #ifdef ADC1_RA14_AN46
    {PA14, hal_ll_adc_module_num(ADC_MODULE_1), {HAL_LL_AD1PCFG_REG_ADDRESS, 0}, ADC1_RA14, ADC1_RA14_AN46, 0},
    #endif
    #ifdef ADC1_RA15_AN47
    {PA15, hal_ll_adc_module_num(ADC_MODULE_1), {HAL_LL_AD1PCFG_REG_ADDRESS, 0}, ADC1_RA15, ADC1_RA15_AN47, 0},
    #endif
    #ifdef ADC1_RD14_AN38
    {PD14, hal_ll_adc_module_num(ADC_MODULE_1), {HAL_LL_AD1PCFG_REG_ADDRESS, 0}, ADC1_RD14, ADC1_RD14_AN38, 0},
    #endif
    #ifdef ADC1_RD15_AN39
    {PD15, hal_ll_adc_module_num(ADC_MODULE_1), {HAL_LL_AD1PCFG_REG_ADDRESS, 0}, ADC1_RD15, ADC1_RD15_AN39, 0},
    #endif
    #ifdef ADC1_RE0_AN40
    {PE0, hal_ll_adc_module_num(ADC_MODULE_1), {HAL_LL_AD1PCFG_REG_ADDRESS, 0}, ADC1_RE0, ADC1_RE0_AN40, 0},
    #endif
    #ifdef ADC1_RE1_AN41
    {PE1, hal_ll_adc_module_num(ADC_MODULE_1), {HAL_LL_AD1PCFG_REG_ADDRESS, 0}, ADC1_RE1, ADC1_RE1_AN41, 0},
    #endif
    #ifdef ADC1_RE8_AN21
    {PE8, hal_ll_adc_module_num(ADC_MODULE_1), {HAL_LL_AD1PCFG_REG_ADDRESS, 0}, ADC1_RE8, ADC1_RE8_AN21, 0},
    #endif
    #ifdef ADC1_RE9_AN20
    {PE9, hal_ll_adc_module_num(ADC_MODULE_1), {HAL_LL_AD1PCFG_REG_ADDRESS, 0}, ADC1_RE9, ADC1_RE9_AN20, 0},
    #endif
    #ifdef ADC1_RF10_AN34
    {PF10, hal_ll_adc_module_num(ADC_MODULE_1), {HAL_LL_AD1PCFG_REG_ADDRESS, 0}, ADC1_RF10, ADC1_RF10_AN34, 0},
    #endif
    #ifdef ADC1_RF12_AN37
    {PF12, hal_ll_adc_module_num(ADC_MODULE_1), {HAL_LL_AD1PCFG_REG_ADDRESS, 0}, ADC1_RF12, ADC1_RF12_AN37, 0},
    #endif
    #ifdef ADC1_RF13_AN36
    {PF13, hal_ll_adc_module_num(ADC_MODULE_1), {HAL_LL_AD1PCFG_REG_ADDRESS, 0}, ADC1_RF13, ADC1_RF13_AN36, 0},
    #endif
    #ifdef ADC1_RF4_AN44
    {PF4, hal_ll_adc_module_num(ADC_MODULE_1), {HAL_LL_AD1PCFG_REG_ADDRESS, 0}, ADC1_RF4, ADC1_RF4_AN44, 0},
    #endif
    #ifdef ADC1_RF5_AN45
    {PF5, hal_ll_adc_module_num(ADC_MODULE_1), {HAL_LL_AD1PCFG_REG_ADDRESS, 0}, ADC1_RF5, ADC1_RF5_AN45, 0},
    #endif
    #ifdef ADC1_RF9_AN33
    {PF9, hal_ll_adc_module_num(ADC_MODULE_1), {HAL_LL_AD1PCFG_REG_ADDRESS, 0}, ADC1_RF9, ADC1_RF9_AN33, 0},
    #endif
    #ifdef ADC1_RG10_AN22
    {PG10, hal_ll_adc_module_num(ADC_MODULE_1), {HAL_LL_AD1PCFG_REG_ADDRESS, 0}, ADC1_RG10, ADC1_RG10_AN22, 0},
    #endif
    #ifdef ADC1_RG11_AN35
    {PG11, hal_ll_adc_module_num(ADC_MODULE_1), {HAL_LL_AD1PCFG_REG_ADDRESS, 0}, ADC1_RG11, ADC1_RG11_AN35, 0},
    #endif
    #ifdef ADC1_RG15_AN23
    {PG15, hal_ll_adc_module_num(ADC_MODULE_1), {HAL_LL_AD1PCFG_REG_ADDRESS, 0}, ADC1_RG15, ADC1_RG15_AN23, 0},
    #endif
    #ifdef ADC1_RG2_AN42
    {PG2, hal_ll_adc_module_num(ADC_MODULE_1), {HAL_LL_AD1PCFG_REG_ADDRESS, 0}, ADC1_RG2, ADC1_RG2_AN42, 0},
    #endif
    #ifdef ADC1_RG3_AN43
    {PG3, hal_ll_adc_module_num(ADC_MODULE_1), {HAL_LL_AD1PCFG_REG_ADDRESS, 0}, ADC1_RG3, ADC1_RG3_AN43, 0},
    #endif
    #ifdef ADC2_RE8_AN21
    {PE8, hal_ll_adc_module_num(ADC_MODULE_2), {HAL_LL_AD1PCFG_REG_ADDRESS, 0}, ADC2_RE8, ADC2_RE8_AN21, 0},
    #endif
    #ifdef ADC2_RE9_AN20
    {PE9, hal_ll_adc_module_num(ADC_MODULE_2), {HAL_LL_AD1PCFG_REG_ADDRESS, 0}, ADC2_RE9, ADC2_RE9_AN20, 0},
    #endif
    #ifdef ADC2_RG10_AN22
    {PG10, hal_ll_adc_module_num(ADC_MODULE_2), {HAL_LL_AD1PCFG_REG_ADDRESS, 0}, ADC2_RG10, ADC2_RG10_AN22, 0},
    #endif
    #ifdef ADC2_RG15_AN23
    {PG15, hal_ll_adc_module_num(ADC_MODULE_2), {HAL_LL_AD1PCFG_REG_ADDRESS, 0}, ADC2_RG15, ADC2_RG15_AN23, 0},
    #endif
    #ifdef ADC1_RA2_AN2
    {PA2, hal_ll_adc_module_num(ADC_MODULE_1), {HAL_LL_AD1PCFG_REG_ADDRESS, 0}, ADC1_RA2, ADC1_RA2_AN2, 0},
    #endif
    #ifdef ADC1_RB0_AN3
    {PB0, hal_ll_adc_module_num(ADC_MODULE_1), {HAL_LL_AD1PCFG_REG_ADDRESS, 0}, ADC1_RB0, ADC1_RB0_AN3, 0},
    #endif
    #ifdef ADC1_RB1_AN6
    {PB1, hal_ll_adc_module_num(ADC_MODULE_1), {HAL_LL_AD1PCFG_REG_ADDRESS, 0}, ADC1_RB1, ADC1_RB1_AN6, 0},
    #endif
    #ifdef ADC1_RB2_AN7
    {PB2, hal_ll_adc_module_num(ADC_MODULE_1), {HAL_LL_AD1PCFG_REG_ADDRESS, 0}, ADC1_RB2, ADC1_RB2_AN7, 0},
    #endif
    #ifdef ADC1_RB3_AN18
    {PB3, hal_ll_adc_module_num(ADC_MODULE_1), {HAL_LL_AD1PCFG_REG_ADDRESS, 0}, ADC1_RB3, ADC1_RB3_AN18, 0},
    #endif
    #ifdef ADC1_RB5_AN19
    {PB5, hal_ll_adc_module_num(ADC_MODULE_1), {HAL_LL_AD1PCFG_REG_ADDRESS, 0}, ADC1_RB5, ADC1_RB5_AN19, 0},
    #endif
    #ifdef ADC1_RB6_AN20
    {PB6, hal_ll_adc_module_num(ADC_MODULE_1), {HAL_LL_AD1PCFG_REG_ADDRESS, 0}, ADC1_RB6, ADC1_RB6_AN20, 0},
    #endif
    #ifdef ADC1_RB7_AN21
    {PB7, hal_ll_adc_module_num(ADC_MODULE_1), {HAL_LL_AD1PCFG_REG_ADDRESS, 0}, ADC1_RB7, ADC1_RB7_AN21, 0},
    #endif
    #ifdef ADC1_RB9_AN4
    {PB9, hal_ll_adc_module_num(ADC_MODULE_1), {HAL_LL_AD1PCFG_REG_ADDRESS, 0}, ADC1_RB9, ADC1_RB9_AN4, 0},
    #endif
    #ifdef ADC1_RC1_AN8
    {PC1, hal_ll_adc_module_num(ADC_MODULE_1), {HAL_LL_AD1PCFG_REG_ADDRESS, 0}, ADC1_RC1, ADC1_RC1_AN8, 0},
    #endif
    #ifdef ADC1_RC10_AN10
    {PC10, hal_ll_adc_module_num(ADC_MODULE_1), {HAL_LL_AD1PCFG_REG_ADDRESS, 0}, ADC1_RC10, ADC1_RC10_AN10, 0},
    #endif
    #ifdef ADC1_RC12_AN14
    {PC12, hal_ll_adc_module_num(ADC_MODULE_1), {HAL_LL_AD1PCFG_REG_ADDRESS, 0}, ADC1_RC12, ADC1_RC12_AN14, 0},
    #endif
    #ifdef ADC1_RC2_AN9
    {PC2, hal_ll_adc_module_num(ADC_MODULE_1), {HAL_LL_AD1PCFG_REG_ADDRESS, 0}, ADC1_RC2, ADC1_RC2_AN9, 0},
    #endif
    #ifdef ADC1_RC6_AN17
    {PC6, hal_ll_adc_module_num(ADC_MODULE_1), {HAL_LL_AD1PCFG_REG_ADDRESS, 0}, ADC1_RC6, ADC1_RC6_AN17, 0},
    #endif
    #ifdef ADC1_RC9_AN11
    {PC9, hal_ll_adc_module_num(ADC_MODULE_1), {HAL_LL_AD1PCFG_REG_ADDRESS, 0}, ADC1_RC9, ADC1_RC9_AN11, 0},
    #endif
    #ifdef ADC1_RD13_AN13
    {PD13, hal_ll_adc_module_num(ADC_MODULE_1), {HAL_LL_AD1PCFG_REG_ADDRESS, 0}, ADC1_RD13, ADC1_RD13_AN13, 0},
    #endif
    #ifdef ADC1_RD2_AN16
    {PD2, hal_ll_adc_module_num(ADC_MODULE_1), {HAL_LL_AD1PCFG_REG_ADDRESS, 0}, ADC1_RD2, ADC1_RD2_AN16, 0},
    #endif
    #ifdef ADC1_RD5_AN12
    {PD5, hal_ll_adc_module_num(ADC_MODULE_1), {HAL_LL_AD1PCFG_REG_ADDRESS, 0}, ADC1_RD5, ADC1_RD5_AN12, 0},
    #endif
    #ifdef ADC1_RD7_AN15
    {PD7, hal_ll_adc_module_num(ADC_MODULE_1), {HAL_LL_AD1PCFG_REG_ADDRESS, 0}, ADC1_RD7, ADC1_RD7_AN15, 0},
    #endif
    #ifdef ADC1_RD8_AN5
    {PD8, hal_ll_adc_module_num(ADC_MODULE_1), {HAL_LL_AD1PCFG_REG_ADDRESS, 0}, ADC1_RD8, ADC1_RD8_AN5, 0},
    #endif
    #ifdef ADC1_RB10_AN5
    {PB10, hal_ll_adc_module_num(ADC_MODULE_1), {HAL_LL_AD1PCFG_REG_ADDRESS, 0}, ADC1_RB10, ADC1_RB10_AN5, 0},
    #endif
    #ifdef ADC1_RB3_AN8
    {PB3, hal_ll_adc_module_num(ADC_MODULE_1), {HAL_LL_AD1PCFG_REG_ADDRESS, 0}, ADC1_RB3, ADC1_RB3_AN8, 0},
    #endif
    #ifdef ADC1_RB5_AN9
    {PB5, hal_ll_adc_module_num(ADC_MODULE_1), {HAL_LL_AD1PCFG_REG_ADDRESS, 0}, ADC1_RB5, ADC1_RB5_AN9, 0},
    #endif
    #ifdef ADC1_RB6_AN10
    {PB6, hal_ll_adc_module_num(ADC_MODULE_1), {HAL_LL_AD1PCFG_REG_ADDRESS, 0}, ADC1_RB6, ADC1_RB6_AN10, 0},
    #endif
    #ifdef ADC1_RB7_AN11
    {PB7, hal_ll_adc_module_num(ADC_MODULE_1), {HAL_LL_AD1PCFG_REG_ADDRESS, 0}, ADC1_RB7, ADC1_RB7_AN11, 0},
    #endif
    #ifdef ADC1_RC11_AN12
    {PC11, hal_ll_adc_module_num(ADC_MODULE_1), {HAL_LL_AD1PCFG_REG_ADDRESS, 0}, ADC1_RC11, ADC1_RC11_AN12, 0},
    #endif
    #ifdef ADC1_RB0_AN0
    {PB0, hal_ll_adc_module_num(ADC_MODULE_1), {HAL_LL_AD1PCFG_REG_ADDRESS, 0}, ADC1_RB0, ADC1_RB0_AN0, 0},
    #endif
    #ifdef ADC1_RB1_AN1
    {PB1, hal_ll_adc_module_num(ADC_MODULE_1), {HAL_LL_AD1PCFG_REG_ADDRESS, 0}, ADC1_RB1, ADC1_RB1_AN1, 0},
    #endif
    #ifdef ADC1_RB10_AN10
    {PB10, hal_ll_adc_module_num(ADC_MODULE_1), {HAL_LL_AD1PCFG_REG_ADDRESS, 0}, ADC1_RB10, ADC1_RB10_AN10, 0},
    #endif
    #ifdef ADC1_RB11_AN11
    {PB11, hal_ll_adc_module_num(ADC_MODULE_1), {HAL_LL_AD1PCFG_REG_ADDRESS, 0}, ADC1_RB11, ADC1_RB11_AN11, 0},
    #endif
    #ifdef ADC1_RB12_AN12
    {PB12, hal_ll_adc_module_num(ADC_MODULE_1), {HAL_LL_AD1PCFG_REG_ADDRESS, 0}, ADC1_RB12, ADC1_RB12_AN12, 0},
    #endif
    #ifdef ADC1_RB13_AN13
    {PB13, hal_ll_adc_module_num(ADC_MODULE_1), {HAL_LL_AD1PCFG_REG_ADDRESS, 0}, ADC1_RB13, ADC1_RB13_AN13, 0},
    #endif
    #ifdef ADC1_RB14_AN14
    {PB14, hal_ll_adc_module_num(ADC_MODULE_1), {HAL_LL_AD1PCFG_REG_ADDRESS, 0}, ADC1_RB14, ADC1_RB14_AN14, 0},
    #endif
    #ifdef ADC1_RB15_AN15
    {PB15, hal_ll_adc_module_num(ADC_MODULE_1), {HAL_LL_AD1PCFG_REG_ADDRESS, 0}, ADC1_RB15, ADC1_RB15_AN15, 0},
    #endif
    #ifdef ADC1_RB2_AN2
    {PB2, hal_ll_adc_module_num(ADC_MODULE_1), {HAL_LL_AD1PCFG_REG_ADDRESS, 0}, ADC1_RB2, ADC1_RB2_AN2, 0},
    #endif
    #ifdef ADC1_RB3_AN3
    {PB3, hal_ll_adc_module_num(ADC_MODULE_1), {HAL_LL_AD1PCFG_REG_ADDRESS, 0}, ADC1_RB3, ADC1_RB3_AN3, 0},
    #endif
    #ifdef ADC1_RB4_AN4
    {PB4, hal_ll_adc_module_num(ADC_MODULE_1), {HAL_LL_AD1PCFG_REG_ADDRESS, 0}, ADC1_RB4, ADC1_RB4_AN4, 0},
    #endif
    #ifdef ADC1_RB5_AN5
    {PB5, hal_ll_adc_module_num(ADC_MODULE_1), {HAL_LL_AD1PCFG_REG_ADDRESS, 0}, ADC1_RB5, ADC1_RB5_AN5, 0},
    #endif
    #ifdef ADC1_RB6_AN6
    {PB6, hal_ll_adc_module_num(ADC_MODULE_1), {HAL_LL_AD1PCFG_REG_ADDRESS, 0}, ADC1_RB6, ADC1_RB6_AN6, 0},
    #endif
    #ifdef ADC1_RB7_AN7
    {PB7, hal_ll_adc_module_num(ADC_MODULE_1), {HAL_LL_AD1PCFG_REG_ADDRESS, 0}, ADC1_RB7, ADC1_RB7_AN7, 0},
    #endif
    #ifdef ADC1_RB8_AN8
    {PB8, hal_ll_adc_module_num(ADC_MODULE_1), {HAL_LL_AD1PCFG_REG_ADDRESS, 0}, ADC1_RB8, ADC1_RB8_AN8, 0},
    #endif
    #ifdef ADC1_RB9_AN9
    {PB9, hal_ll_adc_module_num(ADC_MODULE_1), {HAL_LL_AD1PCFG_REG_ADDRESS, 0}, ADC1_RB9, ADC1_RB9_AN9, 0},
    #endif
    #ifdef ADC1_RE0_AN24
    {PE0, hal_ll_adc_module_num(ADC_MODULE_1), {HAL_LL_AD1PCFG_REG_ADDRESS, 0}, ADC1_RE0, ADC1_RE0_AN24, 0},
    #endif
    #ifdef ADC1_RE1_AN25
    {PE1, hal_ll_adc_module_num(ADC_MODULE_1), {HAL_LL_AD1PCFG_REG_ADDRESS, 0}, ADC1_RE1, ADC1_RE1_AN25, 0},
    #endif
    #ifdef ADC1_RE2_AN26
    {PE2, hal_ll_adc_module_num(ADC_MODULE_1), {HAL_LL_AD1PCFG_REG_ADDRESS, 0}, ADC1_RE2, ADC1_RE2_AN26, 0},
    #endif
    #ifdef ADC1_RE3_AN27
    {PE3, hal_ll_adc_module_num(ADC_MODULE_1), {HAL_LL_AD1PCFG_REG_ADDRESS, 0}, ADC1_RE3, ADC1_RE3_AN27, 0},
    #endif
    #ifdef ADC1_RE4_AN28
    {PE4, hal_ll_adc_module_num(ADC_MODULE_1), {HAL_LL_AD1PCFG_REG_ADDRESS, 0}, ADC1_RE4, ADC1_RE4_AN28, 0},
    #endif
    #ifdef ADC1_RE5_AN29
    {PE5, hal_ll_adc_module_num(ADC_MODULE_1), {HAL_LL_AD1PCFG_REG_ADDRESS, 0}, ADC1_RE5, ADC1_RE5_AN29, 0},
    #endif
    #ifdef ADC1_RE6_AN30
    {PE6, hal_ll_adc_module_num(ADC_MODULE_1), {HAL_LL_AD1PCFG_REG_ADDRESS, 0}, ADC1_RE6, ADC1_RE6_AN30, 0},
    #endif
    #ifdef ADC1_RE7_AN31
    {PE7, hal_ll_adc_module_num(ADC_MODULE_1), {HAL_LL_AD1PCFG_REG_ADDRESS, 0}, ADC1_RE7, ADC1_RE7_AN31, 0},
    #endif
    #ifdef ADC2_RB0_AN0
    {PB0, hal_ll_adc_module_num(ADC_MODULE_2), {HAL_LL_AD1PCFG_REG_ADDRESS, 0}, ADC2_RB0, ADC2_RB0_AN0, 0},
    #endif
    #ifdef ADC2_RB1_AN1
    {PB1, hal_ll_adc_module_num(ADC_MODULE_2), {HAL_LL_AD1PCFG_REG_ADDRESS, 0}, ADC2_RB1, ADC2_RB1_AN1, 0},
    #endif
    #ifdef ADC2_RB10_AN10
    {PB10, hal_ll_adc_module_num(ADC_MODULE_2), {HAL_LL_AD1PCFG_REG_ADDRESS, 0}, ADC2_RB10, ADC2_RB10_AN10, 0},
    #endif
    #ifdef ADC2_RB11_AN11
    {PB11, hal_ll_adc_module_num(ADC_MODULE_2), {HAL_LL_AD1PCFG_REG_ADDRESS, 0}, ADC2_RB11, ADC2_RB11_AN11, 0},
    #endif
    #ifdef ADC2_RB12_AN12
    {PB12, hal_ll_adc_module_num(ADC_MODULE_2), {HAL_LL_AD1PCFG_REG_ADDRESS, 0}, ADC2_RB12, ADC2_RB12_AN12, 0},
    #endif
    #ifdef ADC2_RB13_AN13
    {PB13, hal_ll_adc_module_num(ADC_MODULE_2), {HAL_LL_AD1PCFG_REG_ADDRESS, 0}, ADC2_RB13, ADC2_RB13_AN13, 0},
    #endif
    #ifdef ADC2_RB14_AN14
    {PB14, hal_ll_adc_module_num(ADC_MODULE_2), {HAL_LL_AD1PCFG_REG_ADDRESS, 0}, ADC2_RB14, ADC2_RB14_AN14, 0},
    #endif
    #ifdef ADC2_RB15_AN15
    {PB15, hal_ll_adc_module_num(ADC_MODULE_2), {HAL_LL_AD1PCFG_REG_ADDRESS, 0}, ADC2_RB15, ADC2_RB15_AN15, 0},
    #endif
    #ifdef ADC2_RB2_AN2
    {PB2, hal_ll_adc_module_num(ADC_MODULE_2), {HAL_LL_AD1PCFG_REG_ADDRESS, 0}, ADC2_RB2, ADC2_RB2_AN2, 0},
    #endif
    #ifdef ADC2_RB3_AN3
    {PB3, hal_ll_adc_module_num(ADC_MODULE_2), {HAL_LL_AD1PCFG_REG_ADDRESS, 0}, ADC2_RB3, ADC2_RB3_AN3, 0},
    #endif
    #ifdef ADC2_RB4_AN4
    {PB4, hal_ll_adc_module_num(ADC_MODULE_2), {HAL_LL_AD1PCFG_REG_ADDRESS, 0}, ADC2_RB4, ADC2_RB4_AN4, 0},
    #endif
    #ifdef ADC2_RB5_AN5
    {PB5, hal_ll_adc_module_num(ADC_MODULE_2), {HAL_LL_AD1PCFG_REG_ADDRESS, 0}, ADC2_RB5, ADC2_RB5_AN5, 0},
    #endif
    #ifdef ADC2_RB6_AN6
    {PB6, hal_ll_adc_module_num(ADC_MODULE_2), {HAL_LL_AD1PCFG_REG_ADDRESS, 0}, ADC2_RB6, ADC2_RB6_AN6, 0},
    #endif
    #ifdef ADC2_RB7_AN7
    {PB7, hal_ll_adc_module_num(ADC_MODULE_2), {HAL_LL_AD1PCFG_REG_ADDRESS, 0}, ADC2_RB7, ADC2_RB7_AN7, 0},
    #endif
    #ifdef ADC2_RB8_AN8
    {PB8, hal_ll_adc_module_num(ADC_MODULE_2), {HAL_LL_AD1PCFG_REG_ADDRESS, 0}, ADC2_RB8, ADC2_RB8_AN8, 0},
    #endif
    #ifdef ADC2_RB9_AN9
    {PB9, hal_ll_adc_module_num(ADC_MODULE_2), {HAL_LL_AD1PCFG_REG_ADDRESS, 0}, ADC2_RB9, ADC2_RB9_AN9, 0},
    #endif
    #ifdef ADC1_RA6_AN22
    {PA6, hal_ll_adc_module_num(ADC_MODULE_1), {HAL_LL_AD1PCFG_REG_ADDRESS, 0}, ADC1_RA6, ADC1_RA6_AN22, 0},
    #endif
    #ifdef ADC1_RA7_AN23
    {PA7, hal_ll_adc_module_num(ADC_MODULE_1), {HAL_LL_AD1PCFG_REG_ADDRESS, 0}, ADC1_RA7, ADC1_RA7_AN23, 0},
    #endif
    #ifdef ADC1_RC1_AN16
    {PC1, hal_ll_adc_module_num(ADC_MODULE_1), {HAL_LL_AD1PCFG_REG_ADDRESS, 0}, ADC1_RC1, ADC1_RC1_AN16, 0},
    #endif
    #ifdef ADC1_RC2_AN17
    {PC2, hal_ll_adc_module_num(ADC_MODULE_1), {HAL_LL_AD1PCFG_REG_ADDRESS, 0}, ADC1_RC2, ADC1_RC2_AN17, 0},
    #endif
    #ifdef ADC1_RC3_AN18
    {PC3, hal_ll_adc_module_num(ADC_MODULE_1), {HAL_LL_AD1PCFG_REG_ADDRESS, 0}, ADC1_RC3, ADC1_RC3_AN18, 0},
    #endif
    #ifdef ADC1_RC4_AN19
    {PC4, hal_ll_adc_module_num(ADC_MODULE_1), {HAL_LL_AD1PCFG_REG_ADDRESS, 0}, ADC1_RC4, ADC1_RC4_AN19, 0},
    #endif
    #ifdef ADC1_RE8_AN20
    {PE8, hal_ll_adc_module_num(ADC_MODULE_1), {HAL_LL_AD1PCFG_REG_ADDRESS, 0}, ADC1_RE8, ADC1_RE8_AN20, 0},
    #endif
    #ifdef ADC1_RE9_AN21
    {PE9, hal_ll_adc_module_num(ADC_MODULE_1), {HAL_LL_AD1PCFG_REG_ADDRESS, 0}, ADC1_RE9, ADC1_RE9_AN21, 0},
    #endif
    #ifdef ADC1_RA10_AN56
    {PA10, hal_ll_adc_module_num(ADC_MODULE_1), {HAL_LL_AD1PCFG_REG_ADDRESS, 0}, ADC1_RA10, ADC1_RA10_AN56, 0},
    #endif
    #ifdef ADC1_RA7_AN55
    {PA7, hal_ll_adc_module_num(ADC_MODULE_1), {HAL_LL_AD1PCFG_REG_ADDRESS, 0}, ADC1_RA7, ADC1_RA7_AN55, 0},
    #endif
    #ifdef ADC1_RC6_AN53
    {PC6, hal_ll_adc_module_num(ADC_MODULE_1), {HAL_LL_AD1PCFG_REG_ADDRESS, 0}, ADC1_RC6, ADC1_RC6_AN53, 0},
    #endif
    #ifdef ADC1_RC7_AN52
    {PC7, hal_ll_adc_module_num(ADC_MODULE_1), {HAL_LL_AD1PCFG_REG_ADDRESS, 0}, ADC1_RC7, ADC1_RC7_AN52, 0},
    #endif
    #ifdef ADC1_RC8_AN51
    {PC8, hal_ll_adc_module_num(ADC_MODULE_1), {HAL_LL_AD1PCFG_REG_ADDRESS, 0}, ADC1_RC8, ADC1_RC8_AN51, 0},
    #endif
    #ifdef ADC1_RC9_AN54
    {PC9, hal_ll_adc_module_num(ADC_MODULE_1), {HAL_LL_AD1PCFG_REG_ADDRESS, 0}, ADC1_RC9, ADC1_RC9_AN54, 0},
    #endif
    #ifdef ADC_RA0_AN0
    {PA0, hal_ll_adc_module_num(ADC_MODULE), {HAL_LL_AD1PCFG_REG_ADDRESS, 0}, ADC_RA0, ADC_RA0_AN0, 0},
    #endif
    #ifdef ADC_RA1_AN1
    {PA1, hal_ll_adc_module_num(ADC_MODULE), {HAL_LL_AD1PCFG_REG_ADDRESS, 0}, ADC_RA1, ADC_RA1_AN1, 0},
    #endif
    #ifdef ADC_RB0_AN2
    {PB0, hal_ll_adc_module_num(ADC_MODULE), {HAL_LL_AD1PCFG_REG_ADDRESS, 0}, ADC_RB0, ADC_RB0_AN2, 0},
    #endif
    #ifdef ADC_RB1_AN3
    {PB1, hal_ll_adc_module_num(ADC_MODULE), {HAL_LL_AD1PCFG_REG_ADDRESS, 0}, ADC_RB1, ADC_RB1_AN3, 0},
    #endif
    #ifdef ADC_RB13_AN11
    {PB13, hal_ll_adc_module_num(ADC_MODULE), {HAL_LL_AD1PCFG_REG_ADDRESS, 0}, ADC_RB13, ADC_RB13_AN11, 0},
    #endif
    #ifdef ADC_RB14_AN10
    {PB14, hal_ll_adc_module_num(ADC_MODULE), {HAL_LL_AD1PCFG_REG_ADDRESS, 0}, ADC_RB14, ADC_RB14_AN10, 0},
    #endif
    #ifdef ADC_RB15_AN9
    {PB15, hal_ll_adc_module_num(ADC_MODULE), {HAL_LL_AD1PCFG_REG_ADDRESS, 0}, ADC_RB15, ADC_RB15_AN9, 0},
    #endif
    #ifdef ADC_RB2_AN4
    {PB2, hal_ll_adc_module_num(ADC_MODULE), {HAL_LL_AD1PCFG_REG_ADDRESS, 0}, ADC_RB2, ADC_RB2_AN4, 0},
    #endif
    #ifdef ADC_RB3_AN5
    {PB3, hal_ll_adc_module_num(ADC_MODULE), {HAL_LL_AD1PCFG_REG_ADDRESS, 0}, ADC_RB3, ADC_RB3_AN5, 0},
    #endif
    #ifdef ADC_RC0_AN6
    {PC0, hal_ll_adc_module_num(ADC_MODULE), {HAL_LL_AD1PCFG_REG_ADDRESS, 0}, ADC_RC0, ADC_RC0_AN6, 0},
    #endif
    #ifdef ADC_RC1_AN7
    {PC1, hal_ll_adc_module_num(ADC_MODULE), {HAL_LL_AD1PCFG_REG_ADDRESS, 0}, ADC_RC1, ADC_RC1_AN7, 0},
    #endif
    #ifdef ADC_RC2_AN8
    {PC2, hal_ll_adc_module_num(ADC_MODULE), {HAL_LL_AD1PCFG_REG_ADDRESS, 0}, ADC_RC2, ADC_RC2_AN8, 0},
    #endif
    #ifdef ADC_RC1_AN16
    {PC1, hal_ll_adc_module_num(ADC_MODULE), {HAL_LL_AD1PCFG_REG_ADDRESS, 0}, ADC_RC1, ADC_RC1_AN16, 0},
    #endif
    #ifdef ADC_RC2_AN17
    {PC2, hal_ll_adc_module_num(ADC_MODULE), {HAL_LL_AD1PCFG_REG_ADDRESS, 0}, ADC_RC2, ADC_RC2_AN17, 0},
    #endif
    #ifdef ADC_RA12_AN20
    {PA12, hal_ll_adc_module_num(ADC_MODULE), {HAL_LL_AD1PCFG_REG_ADDRESS, 0}, ADC_RA12, ADC_RA12_AN20, 0},
    #endif
    #ifdef ADC_RA13_AN21
    {PA13, hal_ll_adc_module_num(ADC_MODULE), {HAL_LL_AD1PCFG_REG_ADDRESS, 0}, ADC_RA13, ADC_RA13_AN21, 0},
    #endif
    #ifdef ADC_RA6_AN22
    {PA6, hal_ll_adc_module_num(ADC_MODULE), {HAL_LL_AD1PCFG_REG_ADDRESS, 0}, ADC_RA6, ADC_RA6_AN22, 0},
    #endif
    #ifdef ADC_RA7_AN23
    {PA7, hal_ll_adc_module_num(ADC_MODULE), {HAL_LL_AD1PCFG_REG_ADDRESS, 0}, ADC_RA7, ADC_RA7_AN23, 0},
    #endif
    #ifdef ADC_RC3_AN18
    {PC3, hal_ll_adc_module_num(ADC_MODULE), {HAL_LL_AD1PCFG_REG_ADDRESS, 0}, ADC_RC3, ADC_RC3_AN18, 0},
    #endif
    #ifdef ADC_RC4_AN19
    {PC4, hal_ll_adc_module_num(ADC_MODULE), {HAL_LL_AD1PCFG_REG_ADDRESS, 0}, ADC_RC4, ADC_RC4_AN19, 0},
    #endif
    #ifdef ADC_RE0_AN24
    {PE0, hal_ll_adc_module_num(ADC_MODULE), {HAL_LL_AD1PCFG_REG_ADDRESS, 0}, ADC_RE0, ADC_RE0_AN24, 0},
    #endif
    #ifdef ADC_RE1_AN25
    {PE1, hal_ll_adc_module_num(ADC_MODULE), {HAL_LL_AD1PCFG_REG_ADDRESS, 0}, ADC_RE1, ADC_RE1_AN25, 0},
    #endif
    #ifdef ADC_RE2_AN26
    {PE2, hal_ll_adc_module_num(ADC_MODULE), {HAL_LL_AD1PCFG_REG_ADDRESS, 0}, ADC_RE2, ADC_RE2_AN26, 0},
    #endif
    #ifdef ADC_RE3_AN27
    {PE3, hal_ll_adc_module_num(ADC_MODULE), {HAL_LL_AD1PCFG_REG_ADDRESS, 0}, ADC_RE3, ADC_RE3_AN27, 0},
    #endif
    #ifdef ADC_RE4_AN28
    {PE4, hal_ll_adc_module_num(ADC_MODULE), {HAL_LL_AD1PCFG_REG_ADDRESS, 0}, ADC_RE4, ADC_RE4_AN28, 0},
    #endif
    #ifdef ADC_RE5_AN29
    {PE5, hal_ll_adc_module_num(ADC_MODULE), {HAL_LL_AD1PCFG_REG_ADDRESS, 0}, ADC_RE5, ADC_RE5_AN29, 0},
    #endif
    #ifdef ADC_RE6_AN30
    {PE6, hal_ll_adc_module_num(ADC_MODULE), {HAL_LL_AD1PCFG_REG_ADDRESS, 0}, ADC_RE6, ADC_RE6_AN30, 0},
    #endif
    #ifdef ADC_RE7_AN31
    {PE7, hal_ll_adc_module_num(ADC_MODULE), {HAL_LL_AD1PCFG_REG_ADDRESS, 0}, ADC_RE7, ADC_RE7_AN31, 0},
    #endif
    #ifdef ADC2_RC1_AN16
    {PC1, hal_ll_adc_module_num(ADC_MODULE_2), {HAL_LL_AD1PCFG_REG_ADDRESS, 0}, ADC2_RC1, ADC2_RC1_AN16, 0},
    #endif
    #ifdef ADC2_RC2_AN17
    {PC2, hal_ll_adc_module_num(ADC_MODULE_2), {HAL_LL_AD1PCFG_REG_ADDRESS, 0}, ADC2_RC2, ADC2_RC2_AN17, 0},
    #endif
    #ifdef ADC1_RA12_AN20
    {PA12, hal_ll_adc_module_num(ADC_MODULE_1), {HAL_LL_AD1PCFG_REG_ADDRESS, 0}, ADC1_RA12, ADC1_RA12_AN20, 0},
    #endif
    #ifdef ADC1_RA13_AN21
    {PA13, hal_ll_adc_module_num(ADC_MODULE_1), {HAL_LL_AD1PCFG_REG_ADDRESS, 0}, ADC1_RA13, ADC1_RA13_AN21, 0},
    #endif
    #ifdef ADC2_RA12_AN20
    {PA12, hal_ll_adc_module_num(ADC_MODULE_2), {HAL_LL_AD1PCFG_REG_ADDRESS, 0}, ADC2_RA12, ADC2_RA12_AN20, 0},
    #endif
    #ifdef ADC2_RA13_AN21
    {PA13, hal_ll_adc_module_num(ADC_MODULE_2), {HAL_LL_AD1PCFG_REG_ADDRESS, 0}, ADC2_RA13, ADC2_RA13_AN21, 0},
    #endif
    #ifdef ADC2_RA6_AN22
    {PA6, hal_ll_adc_module_num(ADC_MODULE_2), {HAL_LL_AD1PCFG_REG_ADDRESS, 0}, ADC2_RA6, ADC2_RA6_AN22, 0},
    #endif
    #ifdef ADC2_RA7_AN23
    {PA7, hal_ll_adc_module_num(ADC_MODULE_2), {HAL_LL_AD1PCFG_REG_ADDRESS, 0}, ADC2_RA7, ADC2_RA7_AN23, 0},
    #endif
    #ifdef ADC2_RC3_AN18
    {PC3, hal_ll_adc_module_num(ADC_MODULE_2), {HAL_LL_AD1PCFG_REG_ADDRESS, 0}, ADC2_RC3, ADC2_RC3_AN18, 0},
    #endif
    #ifdef ADC2_RC4_AN19
    {PC4, hal_ll_adc_module_num(ADC_MODULE_2), {HAL_LL_AD1PCFG_REG_ADDRESS, 0}, ADC2_RC4, ADC2_RC4_AN19, 0},
    #endif
    #ifdef ADC2_RE0_AN24
    {PE0, hal_ll_adc_module_num(ADC_MODULE_2), {HAL_LL_AD1PCFG_REG_ADDRESS, 0}, ADC2_RE0, ADC2_RE0_AN24, 0},
    #endif
    #ifdef ADC2_RE1_AN25
    {PE1, hal_ll_adc_module_num(ADC_MODULE_2), {HAL_LL_AD1PCFG_REG_ADDRESS, 0}, ADC2_RE1, ADC2_RE1_AN25, 0},
    #endif
    #ifdef ADC2_RE2_AN26
    {PE2, hal_ll_adc_module_num(ADC_MODULE_2), {HAL_LL_AD1PCFG_REG_ADDRESS, 0}, ADC2_RE2, ADC2_RE2_AN26, 0},
    #endif
    #ifdef ADC2_RE3_AN27
    {PE3, hal_ll_adc_module_num(ADC_MODULE_2), {HAL_LL_AD1PCFG_REG_ADDRESS, 0}, ADC2_RE3, ADC2_RE3_AN27, 0},
    #endif
    #ifdef ADC2_RE4_AN28
    {PE4, hal_ll_adc_module_num(ADC_MODULE_2), {HAL_LL_AD1PCFG_REG_ADDRESS, 0}, ADC2_RE4, ADC2_RE4_AN28, 0},
    #endif
    #ifdef ADC2_RE5_AN29
    {PE5, hal_ll_adc_module_num(ADC_MODULE_2), {HAL_LL_AD1PCFG_REG_ADDRESS, 0}, ADC2_RE5, ADC2_RE5_AN29, 0},
    #endif
    #ifdef ADC2_RE6_AN30
    {PE6, hal_ll_adc_module_num(ADC_MODULE_2), {HAL_LL_AD1PCFG_REG_ADDRESS, 0}, ADC2_RE6, ADC2_RE6_AN30, 0},
    #endif
    #ifdef ADC2_RE7_AN31
    {PE7, hal_ll_adc_module_num(ADC_MODULE_2), {HAL_LL_AD1PCFG_REG_ADDRESS, 0}, ADC2_RE7, ADC2_RE7_AN31, 0},
    #endif
    #ifdef ADC_RE8_AN20
    {PE8, hal_ll_adc_module_num(ADC_MODULE), {HAL_LL_AD1PCFG_REG_ADDRESS, 0}, ADC_RE8, ADC_RE8_AN20, 0},
    #endif
    #ifdef ADC_RE9_AN21
    {PE9, hal_ll_adc_module_num(ADC_MODULE), {HAL_LL_AD1PCFG_REG_ADDRESS, 0}, ADC_RE9, ADC_RE9_AN21, 0},
    #endif
    #ifdef ADC2_RE8_AN20
    {PE8, hal_ll_adc_module_num(ADC_MODULE_2), {HAL_LL_AD1PCFG_REG_ADDRESS, 0}, ADC2_RE8, ADC2_RE8_AN20, 0},
    #endif
    #ifdef ADC2_RE9_AN21
    {PE9, hal_ll_adc_module_num(ADC_MODULE_2), {HAL_LL_AD1PCFG_REG_ADDRESS, 0}, ADC2_RE9, ADC2_RE9_AN21, 0},
    #endif
    #ifdef ADC_RA2_AN2
    {PA2, hal_ll_adc_module_num(ADC_MODULE), {HAL_LL_AD1PCFG_REG_ADDRESS, 0}, ADC_RA2, ADC_RA2_AN2, 0},
    #endif
    #ifdef ADC_RB0_AN3
    {PB0, hal_ll_adc_module_num(ADC_MODULE), {HAL_LL_AD1PCFG_REG_ADDRESS, 0}, ADC_RB0, ADC_RB0_AN3, 0},
    #endif
    #ifdef ADC_RB1_AN6
    {PB1, hal_ll_adc_module_num(ADC_MODULE), {HAL_LL_AD1PCFG_REG_ADDRESS, 0}, ADC_RB1, ADC_RB1_AN6, 0},
    #endif
    #ifdef ADC_RB10_AN5
    {PB10, hal_ll_adc_module_num(ADC_MODULE), {HAL_LL_AD1PCFG_REG_ADDRESS, 0}, ADC_RB10, ADC_RB10_AN5, 0},
    #endif
    #ifdef ADC_RB2_AN7
    {PB2, hal_ll_adc_module_num(ADC_MODULE), {HAL_LL_AD1PCFG_REG_ADDRESS, 0}, ADC_RB2, ADC_RB2_AN7, 0},
    #endif
    #ifdef ADC_RB9_AN4
    {PB9, hal_ll_adc_module_num(ADC_MODULE), {HAL_LL_AD1PCFG_REG_ADDRESS, 0}, ADC_RB9, ADC_RB9_AN4, 0},
    #endif
    #ifdef ADC_RC1_AN8
    {PC1, hal_ll_adc_module_num(ADC_MODULE), {HAL_LL_AD1PCFG_REG_ADDRESS, 0}, ADC_RC1, ADC_RC1_AN8, 0},
    #endif
    #ifdef ADC_RC10_AN10
    {PC10, hal_ll_adc_module_num(ADC_MODULE), {HAL_LL_AD1PCFG_REG_ADDRESS, 0}, ADC_RC10, ADC_RC10_AN10, 0},
    #endif
    #ifdef ADC_RC2_AN9
    {PC2, hal_ll_adc_module_num(ADC_MODULE), {HAL_LL_AD1PCFG_REG_ADDRESS, 0}, ADC_RC2, ADC_RC2_AN9, 0},
    #endif
    #ifdef ADC_RC9_AN11
    {PC9, hal_ll_adc_module_num(ADC_MODULE), {HAL_LL_AD1PCFG_REG_ADDRESS, 0}, ADC_RC9, ADC_RC9_AN11, 0},
    #endif
    #ifdef ADC_RA4_AN10
    {PA4, hal_ll_adc_module_num(ADC_MODULE), {HAL_LL_AD1PCFG_REG_ADDRESS, 0}, ADC_RA4, ADC_RA4_AN10, 0},
    #endif
    #ifdef ADC_RB4_AN9
    {PB4, hal_ll_adc_module_num(ADC_MODULE), {HAL_LL_AD1PCFG_REG_ADDRESS, 0}, ADC_RB4, ADC_RB4_AN9, 0},
    #endif
    #ifdef ADC_RC3_AN11
    {PC3, hal_ll_adc_module_num(ADC_MODULE), {HAL_LL_AD1PCFG_REG_ADDRESS, 0}, ADC_RC3, ADC_RC3_AN11, 0},
    #endif
    #ifdef ADC_RC4_AN12
    {PC4, hal_ll_adc_module_num(ADC_MODULE), {HAL_LL_AD1PCFG_REG_ADDRESS, 0}, ADC_RC4, ADC_RC4_AN12, 0},
    #endif
    #ifdef ADC_RC5_AN15
    {PC5, hal_ll_adc_module_num(ADC_MODULE), {HAL_LL_AD1PCFG_REG_ADDRESS, 0}, ADC_RC5, ADC_RC5_AN15, 0},
    #endif
    #ifdef ADC1_RA2_AN13
    {PA2, hal_ll_adc_module_num(ADC_MODULE_1), {HAL_LL_AD1PCFG_REG_ADDRESS, 0}, ADC1_RA2, ADC1_RA2_AN13, 0},
    #endif
    #ifdef ADC1_RA3_AN14
    {PA3, hal_ll_adc_module_num(ADC_MODULE_1), {HAL_LL_AD1PCFG_REG_ADDRESS, 0}, ADC1_RA3, ADC1_RA3_AN14, 0},
    #endif
    #ifdef ADC1_RB13_AN11
    {PB13, hal_ll_adc_module_num(ADC_MODULE_1), {HAL_LL_AD1PCFG_REG_ADDRESS, 0}, ADC1_RB13, ADC1_RB13_AN11, 0},
    #endif
    #ifdef ADC1_RB14_AN10
    {PB14, hal_ll_adc_module_num(ADC_MODULE_1), {HAL_LL_AD1PCFG_REG_ADDRESS, 0}, ADC1_RB14, ADC1_RB14_AN10, 0},
    #endif
    #ifdef ADC1_RB15_AN9
    {PB15, hal_ll_adc_module_num(ADC_MODULE_1), {HAL_LL_AD1PCFG_REG_ADDRESS, 0}, ADC1_RB15, ADC1_RB15_AN9, 0},
    #endif
    #ifdef ADC1_RB4_AN15
    {PB4, hal_ll_adc_module_num(ADC_MODULE_1), {HAL_LL_AD1PCFG_REG_ADDRESS, 0}, ADC1_RB4, ADC1_RB4_AN15, 0},
    #endif
    #ifdef ADC1_RA4_AN16
    {PA4, hal_ll_adc_module_num(ADC_MODULE_1), {HAL_LL_AD1PCFG_REG_ADDRESS, 0}, ADC1_RA4, ADC1_RA4_AN16, 0},
    #endif
    #ifdef ADC1_RB5_AN17
    {PB5, hal_ll_adc_module_num(ADC_MODULE_1), {HAL_LL_AD1PCFG_REG_ADDRESS, 0}, ADC1_RB5, ADC1_RB5_AN17, 0},
    #endif
    #ifdef ADC1_RB6_AN18
    {PB6, hal_ll_adc_module_num(ADC_MODULE_1), {HAL_LL_AD1PCFG_REG_ADDRESS, 0}, ADC1_RB6, ADC1_RB6_AN18, 0},
    #endif
    #ifdef ADC1_RB7_AN19
    {PB7, hal_ll_adc_module_num(ADC_MODULE_1), {HAL_LL_AD1PCFG_REG_ADDRESS, 0}, ADC1_RB7, ADC1_RB7_AN19, 0},
    #endif
    #ifdef ADC1_RB8_AN20
    {PB8, hal_ll_adc_module_num(ADC_MODULE_1), {HAL_LL_AD1PCFG_REG_ADDRESS, 0}, ADC1_RB8, ADC1_RB8_AN20, 0},
    #endif
    #ifdef ADC1_RB9_AN21
    {PB9, hal_ll_adc_module_num(ADC_MODULE_1), {HAL_LL_AD1PCFG_REG_ADDRESS, 0}, ADC1_RB9, ADC1_RB9_AN21, 0},
    #endif
    #ifdef ADC1_RA6_AN23
    {PA6, hal_ll_adc_module_num(ADC_MODULE_1), {HAL_LL_AD1PCFG_REG_ADDRESS, 0}, ADC1_RA6, ADC1_RA6_AN23, 0},
    #endif
    #ifdef ADC1_RA7_AN22
    {PA7, hal_ll_adc_module_num(ADC_MODULE_1), {HAL_LL_AD1PCFG_REG_ADDRESS, 0}, ADC1_RA7, ADC1_RA7_AN22, 0},
    #endif
    #ifdef ADC1_RC4_AN16
    {PC4, hal_ll_adc_module_num(ADC_MODULE_1), {HAL_LL_AD1PCFG_REG_ADDRESS, 0}, ADC1_RC4, ADC1_RC4_AN16, 0},
    #endif
    #ifdef ADC1_RG6_AN17
    {PG6, hal_ll_adc_module_num(ADC_MODULE_1), {HAL_LL_AD1PCFG_REG_ADDRESS, 0}, ADC1_RG6, ADC1_RG6_AN17, 0},
    #endif
    #ifdef ADC1_RG8_AN19
    {PG8, hal_ll_adc_module_num(ADC_MODULE_1), {HAL_LL_AD1PCFG_REG_ADDRESS, 0}, ADC1_RG8, ADC1_RG8_AN19, 0},
    #endif
    #ifdef ADC1_RG9_AN20
    {PG9, hal_ll_adc_module_num(ADC_MODULE_1), {HAL_LL_AD1PCFG_REG_ADDRESS, 0}, ADC1_RG9, ADC1_RG9_AN20, 0},
    #endif
    #ifdef ADC1_RB12_AN8
    {PB12, hal_ll_adc_module_num(ADC_MODULE_1), {HAL_LL_AD1PCFG_REG_ADDRESS, 0}, ADC1_RB12, ADC1_RB12_AN8, 0},
    #endif
    #ifdef ADC1_RB13_AN7
    {PB13, hal_ll_adc_module_num(ADC_MODULE_1), {HAL_LL_AD1PCFG_REG_ADDRESS, 0}, ADC1_RB13, ADC1_RB13_AN7, 0},
    #endif
    #ifdef ADC1_RB14_AN6
    {PB14, hal_ll_adc_module_num(ADC_MODULE_1), {HAL_LL_AD1PCFG_REG_ADDRESS, 0}, ADC1_RB14, ADC1_RB14_AN6, 0},
    #endif
    #ifdef ADC1_RC0_AN10
    {PC0, hal_ll_adc_module_num(ADC_MODULE_1), {HAL_LL_AD1PCFG_REG_ADDRESS, 0}, ADC1_RC0, ADC1_RC0_AN10, 0},
    #endif
    #ifdef ADC1_RC1_AN11
    {PC1, hal_ll_adc_module_num(ADC_MODULE_1), {HAL_LL_AD1PCFG_REG_ADDRESS, 0}, ADC1_RC1, ADC1_RC1_AN11, 0},
    #endif
    #ifdef ADC1_RC2_AN12
    {PC2, hal_ll_adc_module_num(ADC_MODULE_1), {HAL_LL_AD1PCFG_REG_ADDRESS, 0}, ADC1_RC2, ADC1_RC2_AN12, 0},
    #endif
    #ifdef ADC1_RC3_AN13
    {PC3, hal_ll_adc_module_num(ADC_MODULE_1), {HAL_LL_AD1PCFG_REG_ADDRESS, 0}, ADC1_RC3, ADC1_RC3_AN13, 0},
    #endif
    #ifdef ADC1_RD0_AN43
    {PD0, hal_ll_adc_module_num(ADC_MODULE_1), {HAL_LL_AD1PCFG_REG_ADDRESS, 0}, ADC1_RD0, ADC1_RD0_AN43, 0},
    #endif
    #ifdef ADC1_RD1_AN35
    {PD1, hal_ll_adc_module_num(ADC_MODULE_1), {HAL_LL_AD1PCFG_REG_ADDRESS, 0}, ADC1_RD1, ADC1_RD1_AN35, 0},
    #endif
    #ifdef ADC1_RD10_AN41
    {PD10, hal_ll_adc_module_num(ADC_MODULE_1), {HAL_LL_AD1PCFG_REG_ADDRESS, 0}, ADC1_RD10, ADC1_RD10_AN41, 0},
    #endif
    #ifdef ADC1_RD11_AN42
    {PD11, hal_ll_adc_module_num(ADC_MODULE_1), {HAL_LL_AD1PCFG_REG_ADDRESS, 0}, ADC1_RD11, ADC1_RD11_AN42, 0},
    #endif
    #ifdef ADC1_RD2_AN25
    {PD2, hal_ll_adc_module_num(ADC_MODULE_1), {HAL_LL_AD1PCFG_REG_ADDRESS, 0}, ADC1_RD2, ADC1_RD2_AN25, 0},
    #endif
    #ifdef ADC1_RD3_AN44
    {PD3, hal_ll_adc_module_num(ADC_MODULE_1), {HAL_LL_AD1PCFG_REG_ADDRESS, 0}, ADC1_RD3, ADC1_RD3_AN44, 0},
    #endif
    #ifdef ADC1_RD4_AN47
    {PD4, hal_ll_adc_module_num(ADC_MODULE_1), {HAL_LL_AD1PCFG_REG_ADDRESS, 0}, ADC1_RD4, ADC1_RD4_AN47, 0},
    #endif
    #ifdef ADC1_RD5_AN48
    {PD5, hal_ll_adc_module_num(ADC_MODULE_1), {HAL_LL_AD1PCFG_REG_ADDRESS, 0}, ADC1_RD5, ADC1_RD5_AN48, 0},
    #endif
    #ifdef ADC1_RD6_AN34
    {PD6, hal_ll_adc_module_num(ADC_MODULE_1), {HAL_LL_AD1PCFG_REG_ADDRESS, 0}, ADC1_RD6, ADC1_RD6_AN34, 0},
    #endif
    #ifdef ADC1_RD7_AN20
    {PD7, hal_ll_adc_module_num(ADC_MODULE_1), {HAL_LL_AD1PCFG_REG_ADDRESS, 0}, ADC1_RD7, ADC1_RD7_AN20, 0},
    #endif
    #ifdef ADC1_RD8_AN40
    {PD8, hal_ll_adc_module_num(ADC_MODULE_1), {HAL_LL_AD1PCFG_REG_ADDRESS, 0}, ADC1_RD8, ADC1_RD8_AN40, 0},
    #endif
    #ifdef ADC1_RD9_AN24
    {PD9, hal_ll_adc_module_num(ADC_MODULE_1), {HAL_LL_AD1PCFG_REG_ADDRESS, 0}, ADC1_RD9, ADC1_RD9_AN24, 0},
    #endif
    #ifdef ADC1_RF3_AN30
    {PF3, hal_ll_adc_module_num(ADC_MODULE_1), {HAL_LL_AD1PCFG_REG_ADDRESS, 0}, ADC1_RF3, ADC1_RF3_AN30, 0},
    #endif
    #ifdef ADC1_RF4_AN11
    {PF4, hal_ll_adc_module_num(ADC_MODULE_1), {HAL_LL_AD1PCFG_REG_ADDRESS, 0}, ADC1_RF4, ADC1_RF4_AN11, 0},
    #endif
    #ifdef ADC1_RF5_AN10
    {PF5, hal_ll_adc_module_num(ADC_MODULE_1), {HAL_LL_AD1PCFG_REG_ADDRESS, 0}, ADC1_RF5, ADC1_RF5_AN10, 0},
    #endif
    #ifdef ADC1_RG9_AN49
    {PG9, hal_ll_adc_module_num(ADC_MODULE_1), {HAL_LL_AD1PCFG_REG_ADDRESS, 0}, ADC1_RG9, ADC1_RG9_AN49, 0},
    #endif
    #ifdef ADC1_RA1_AN26
    {PA1, hal_ll_adc_module_num(ADC_MODULE_1), {HAL_LL_AD1PCFG_REG_ADDRESS, 0}, ADC1_RA1, ADC1_RA1_AN26, 0},
    #endif
    #ifdef ADC1_RA14_AN38
    {PA14, hal_ll_adc_module_num(ADC_MODULE_1), {HAL_LL_AD1PCFG_REG_ADDRESS, 0}, ADC1_RA14, ADC1_RA14_AN38, 0},
    #endif
    #ifdef ADC1_RA15_AN39
    {PA15, hal_ll_adc_module_num(ADC_MODULE_1), {HAL_LL_AD1PCFG_REG_ADDRESS, 0}, ADC1_RA15, ADC1_RA15_AN39, 0},
    #endif
    #ifdef ADC1_RA4_AN36
    {PA4, hal_ll_adc_module_num(ADC_MODULE_1), {HAL_LL_AD1PCFG_REG_ADDRESS, 0}, ADC1_RA4, ADC1_RA4_AN36, 0},
    #endif
    #ifdef ADC1_RA5_AN37
    {PA5, hal_ll_adc_module_num(ADC_MODULE_1), {HAL_LL_AD1PCFG_REG_ADDRESS, 0}, ADC1_RA5, ADC1_RA5_AN37, 0},
    #endif
    #ifdef ADC1_RC3_AN9
    {PC3, hal_ll_adc_module_num(ADC_MODULE_1), {HAL_LL_AD1PCFG_REG_ADDRESS, 0}, ADC1_RC3, ADC1_RC3_AN9, 0},
    #endif
    #ifdef ADC1_RD12_AN45
    {PD12, hal_ll_adc_module_num(ADC_MODULE_1), {HAL_LL_AD1PCFG_REG_ADDRESS, 0}, ADC1_RD12, ADC1_RD12_AN45, 0},
    #endif
    #ifdef ADC1_RD13_AN46
    {PD13, hal_ll_adc_module_num(ADC_MODULE_1), {HAL_LL_AD1PCFG_REG_ADDRESS, 0}, ADC1_RD13, ADC1_RD13_AN46, 0},
    #endif
    #ifdef ADC1_RD14_AN28
    {PD14, hal_ll_adc_module_num(ADC_MODULE_1), {HAL_LL_AD1PCFG_REG_ADDRESS, 0}, ADC1_RD14, ADC1_RD14_AN28, 0},
    #endif
    #ifdef ADC1_RD15_AN29
    {PD15, hal_ll_adc_module_num(ADC_MODULE_1), {HAL_LL_AD1PCFG_REG_ADDRESS, 0}, ADC1_RD15, ADC1_RD15_AN29, 0},
    #endif
    #ifdef ADC1_RF13_AN27
    {PF13, hal_ll_adc_module_num(ADC_MODULE_1), {HAL_LL_AD1PCFG_REG_ADDRESS, 0}, ADC1_RF13, ADC1_RF13_AN27, 0},
    #endif
    #ifdef ADC1_RF2_AN31
    {PF2, hal_ll_adc_module_num(ADC_MODULE_1), {HAL_LL_AD1PCFG_REG_ADDRESS, 0}, ADC1_RF2, ADC1_RF2_AN31, 0},
    #endif
    #ifdef ADC1_RF8_AN32
    {PF8, hal_ll_adc_module_num(ADC_MODULE_1), {HAL_LL_AD1PCFG_REG_ADDRESS, 0}, ADC1_RF8, ADC1_RF8_AN32, 0},
    #endif
    #ifdef ADC1_RG15_AN33
    {PG15, hal_ll_adc_module_num(ADC_MODULE_1), {HAL_LL_AD1PCFG_REG_ADDRESS, 0}, ADC1_RG15, ADC1_RG15_AN33, 0},
    #endif
    #ifdef ADC1_RC3_AN12
    {PC3, hal_ll_adc_module_num(ADC_MODULE_1), {HAL_LL_AD1PCFG_REG_ADDRESS, 0}, ADC1_RC3, ADC1_RC3_AN12, 0},
    #endif
    #endif
    // EOF list

    // BEGIN ADPCFGL/H
    #ifdef _ADC_ADPCFGLH_
    #ifdef ADC_RB0_AN0
    {PB0, hal_ll_adc_module_num(ADC_MODULE), {HAL_LL_AD1PCFGL_REG_ADDRESS, HAL_LL_AD2PCFGL_REG_ADDRESS}, ADC_RB0, ADC_RB0_AN0, 0},
    #endif
    #ifdef ADC_RB1_AN1
    {PB1, hal_ll_adc_module_num(ADC_MODULE), {HAL_LL_AD1PCFGL_REG_ADDRESS, HAL_LL_AD2PCFGL_REG_ADDRESS}, ADC_RB1, ADC_RB1_AN1, 0},
    #endif
    #ifdef ADC_RB2_AN2
    {PB2, hal_ll_adc_module_num(ADC_MODULE), {HAL_LL_AD1PCFGL_REG_ADDRESS, HAL_LL_AD2PCFGL_REG_ADDRESS}, ADC_RB2, ADC_RB2_AN2, 0},
    #endif
    #ifdef ADC_RB3_AN3
    {PB3, hal_ll_adc_module_num(ADC_MODULE), {HAL_LL_AD1PCFGL_REG_ADDRESS, HAL_LL_AD2PCFGL_REG_ADDRESS}, ADC_RB3, ADC_RB3_AN3, 0},
    #endif
    #ifdef ADC_RB4_AN4
    {PB4, hal_ll_adc_module_num(ADC_MODULE), {HAL_LL_AD1PCFGL_REG_ADDRESS, HAL_LL_AD2PCFGL_REG_ADDRESS}, ADC_RB4, ADC_RB4_AN4, 0},
    #endif
    #ifdef ADC_RB5_AN5
    {PB5, hal_ll_adc_module_num(ADC_MODULE), {HAL_LL_AD1PCFGL_REG_ADDRESS, HAL_LL_AD2PCFGL_REG_ADDRESS}, ADC_RB5, ADC_RB5_AN5, 0},
    #endif
    #ifdef ADC_RB6_AN6
    {PB6, hal_ll_adc_module_num(ADC_MODULE), {HAL_LL_AD1PCFGL_REG_ADDRESS, HAL_LL_AD2PCFGL_REG_ADDRESS}, ADC_RB6, ADC_RB6_AN6, 0},
    #endif
    #ifdef ADC_RB7_AN7
    {PB7, hal_ll_adc_module_num(ADC_MODULE), {HAL_LL_AD1PCFGL_REG_ADDRESS, HAL_LL_AD2PCFGL_REG_ADDRESS}, ADC_RB7, ADC_RB7_AN7, 0},
    #endif
    #ifdef ADC_RB8_AN8
    {PB8, hal_ll_adc_module_num(ADC_MODULE), {HAL_LL_AD1PCFGL_REG_ADDRESS, HAL_LL_AD2PCFGL_REG_ADDRESS}, ADC_RB8, ADC_RB8_AN8, 0},
    #endif
    #ifdef ADC_RB9_AN9
    {PB9, hal_ll_adc_module_num(ADC_MODULE), {HAL_LL_AD1PCFGL_REG_ADDRESS, HAL_LL_AD2PCFGL_REG_ADDRESS}, ADC_RB9, ADC_RB9_AN9, 0},
    #endif
    #ifdef ADC_RB10_AN10
    {PB10, hal_ll_adc_module_num(ADC_MODULE), {HAL_LL_AD1PCFGL_REG_ADDRESS, HAL_LL_AD2PCFGL_REG_ADDRESS}, ADC_RB10, ADC_RB10_AN10, 0},
    #endif
    #ifdef ADC_RB11_AN11
    {PB11, hal_ll_adc_module_num(ADC_MODULE), {HAL_LL_AD1PCFGL_REG_ADDRESS, HAL_LL_AD2PCFGL_REG_ADDRESS}, ADC_RB11, ADC_RB11_AN11, 0},
    #endif
    #ifdef ADC_RB12_AN12
    {PB12, hal_ll_adc_module_num(ADC_MODULE), {HAL_LL_AD1PCFGL_REG_ADDRESS, HAL_LL_AD2PCFGL_REG_ADDRESS}, ADC_RB12, ADC_RB12_AN12, 0},
    #endif
    #ifdef ADC_RB13_AN13
    {PB13, hal_ll_adc_module_num(ADC_MODULE), {HAL_LL_AD1PCFGL_REG_ADDRESS, HAL_LL_AD2PCFGL_REG_ADDRESS}, ADC_RB13, ADC_RB13_AN13, 0},
    #endif
    #ifdef ADC_RB14_AN14
    {PB14, hal_ll_adc_module_num(ADC_MODULE), {HAL_LL_AD1PCFGL_REG_ADDRESS, HAL_LL_AD2PCFGL_REG_ADDRESS}, ADC_RB14, ADC_RB14_AN14, 0},
    #endif
    #ifdef ADC_RB15_AN15
    {PB15, hal_ll_adc_module_num(ADC_MODULE), {HAL_LL_AD1PCFGL_REG_ADDRESS, HAL_LL_AD2PCFGL_REG_ADDRESS}, ADC_RB15, ADC_RB15_AN15, 0},
    #endif
    #ifdef ADC1_RA0_AN0
    {PA0, hal_ll_adc_module_num(ADC_MODULE_1), {HAL_LL_AD1PCFGL_REG_ADDRESS, HAL_LL_AD2PCFGL_REG_ADDRESS}, ADC1_RA0, ADC1_RA0_AN0, 0},
    #endif
    #ifdef ADC1_RA1_AN1
    {PA1, hal_ll_adc_module_num(ADC_MODULE_1), {HAL_LL_AD1PCFGL_REG_ADDRESS, HAL_LL_AD2PCFGL_REG_ADDRESS}, ADC1_RA1, ADC1_RA1_AN1, 0},
    #endif
    #ifdef ADC1_RA2_AN32
    {PA2, hal_ll_adc_module_num(ADC_MODULE_1), {HAL_LL_AD1PCFGH_REG_ADDRESS, 0}, ADC1_RA2, ADC1_RA2_AN32, 0},
    #endif
    #ifdef ADC1_RA4_AN24
    {PA4, hal_ll_adc_module_num(ADC_MODULE_1), {HAL_LL_AD1PCFGH_REG_ADDRESS, 0}, ADC1_RA4, ADC1_RA4_AN24, 0},
    #endif
    #ifdef ADC1_RA9_AN28
    {PA9, hal_ll_adc_module_num(ADC_MODULE_1), {HAL_LL_AD1PCFGH_REG_ADDRESS, 0}, ADC1_RA9, ADC1_RA9_AN28, 0},
    #endif
    #ifdef ADC1_RB0_AN2
    {PB0, hal_ll_adc_module_num(ADC_MODULE_1), {HAL_LL_AD1PCFGL_REG_ADDRESS, HAL_LL_AD2PCFGL_REG_ADDRESS}, ADC1_RB0, ADC1_RB0_AN2, 0},
    #endif
    #ifdef ADC1_RB1_AN3
    {PB1, hal_ll_adc_module_num(ADC_MODULE_1), {HAL_LL_AD1PCFGL_REG_ADDRESS, HAL_LL_AD2PCFGL_REG_ADDRESS}, ADC1_RB1, ADC1_RB1_AN3, 0},
    #endif
    #ifdef ADC1_RB2_AN4
    {PB2, hal_ll_adc_module_num(ADC_MODULE_1), {HAL_LL_AD1PCFGL_REG_ADDRESS, HAL_LL_AD2PCFGL_REG_ADDRESS}, ADC1_RB2, ADC1_RB2_AN4, 0},
    #endif
    #ifdef ADC1_RB3_AN5
    {PB3, hal_ll_adc_module_num(ADC_MODULE_1), {HAL_LL_AD1PCFGL_REG_ADDRESS, HAL_LL_AD2PCFGL_REG_ADDRESS}, ADC1_RB3, ADC1_RB3_AN5, 0},
    #endif
    #ifdef ADC1_RB7_AN25
    {PB7, hal_ll_adc_module_num(ADC_MODULE_1), {HAL_LL_AD1PCFGH_REG_ADDRESS, 0}, ADC1_RB7, ADC1_RB7_AN25, 0},
    #endif
    #ifdef ADC1_RB8_AN26
    {PB8, hal_ll_adc_module_num(ADC_MODULE_1), {HAL_LL_AD1PCFGH_REG_ADDRESS, 0}, ADC1_RB8, ADC1_RB8_AN26, 0},
    #endif
    #ifdef ADC1_RB9_AN27
    {PB9, hal_ll_adc_module_num(ADC_MODULE_1), {HAL_LL_AD1PCFGH_REG_ADDRESS, 0}, ADC1_RB9, ADC1_RB9_AN27, 0},
    #endif
    #ifdef ADC1_RC0_AN6
    {PC0, hal_ll_adc_module_num(ADC_MODULE_1), {HAL_LL_AD1PCFGL_REG_ADDRESS, HAL_LL_AD2PCFGL_REG_ADDRESS}, ADC1_RC0, ADC1_RC0_AN6, 0},
    #endif
    #ifdef ADC1_RC1_AN7
    {PC1, hal_ll_adc_module_num(ADC_MODULE_1), {HAL_LL_AD1PCFGL_REG_ADDRESS, HAL_LL_AD2PCFGL_REG_ADDRESS}, ADC1_RC1, ADC1_RC1_AN7, 0},
    #endif
    #ifdef ADC1_RC2_AN8
    {PC2, hal_ll_adc_module_num(ADC_MODULE_1), {HAL_LL_AD1PCFGL_REG_ADDRESS, HAL_LL_AD2PCFGL_REG_ADDRESS}, ADC1_RC2, ADC1_RC2_AN8, 0},
    #endif
    #ifdef ADC1_RC3_AN29
    {PC3, hal_ll_adc_module_num(ADC_MODULE_1), {HAL_LL_AD1PCFGH_REG_ADDRESS, 0}, ADC1_RC3, ADC1_RC3_AN29, 0},
    #endif
    #ifdef ADC1_RC4_AN30
    {PC4, hal_ll_adc_module_num(ADC_MODULE_1), {HAL_LL_AD1PCFGH_REG_ADDRESS, 0}, ADC1_RC4, ADC1_RC4_AN30, 0},
    #endif
    #ifdef ADC1_RC5_AN31
    {PC5, hal_ll_adc_module_num(ADC_MODULE_1), {HAL_LL_AD1PCFGH_REG_ADDRESS, 0}, ADC1_RC5, ADC1_RC5_AN31, 0},
    #endif
    #ifdef ADC2_RA0_AN0
    {PA0, hal_ll_adc_module_num(ADC_MODULE_2), {HAL_LL_AD1PCFGL_REG_ADDRESS, HAL_LL_AD2PCFGL_REG_ADDRESS}, ADC2_RA0, ADC2_RA0_AN0, 0},
    #endif
    #ifdef ADC2_RA1_AN1
    {PA1, hal_ll_adc_module_num(ADC_MODULE_2), {HAL_LL_AD1PCFGL_REG_ADDRESS, HAL_LL_AD2PCFGL_REG_ADDRESS}, ADC2_RA1, ADC2_RA1_AN1, 0},
    #endif
    #ifdef ADC2_RA4_AN24
    {PA4, hal_ll_adc_module_num(ADC_MODULE_2), {HAL_LL_AD1PCFGH_REG_ADDRESS, 0}, ADC2_RA4, ADC2_RA4_AN24, 0},
    #endif
    #ifdef ADC2_RA9_AN28
    {PA9, hal_ll_adc_module_num(ADC_MODULE_2), {HAL_LL_AD1PCFGH_REG_ADDRESS, 0}, ADC2_RA9, ADC2_RA9_AN28, 0},
    #endif
    #ifdef ADC2_RB0_AN2
    {PB0, hal_ll_adc_module_num(ADC_MODULE_2), {HAL_LL_AD1PCFGL_REG_ADDRESS, HAL_LL_AD2PCFGL_REG_ADDRESS}, ADC2_RB0, ADC2_RB0_AN2, 0},
    #endif
    #ifdef ADC2_RB1_AN3
    {PB1, hal_ll_adc_module_num(ADC_MODULE_2), {HAL_LL_AD1PCFGL_REG_ADDRESS, HAL_LL_AD2PCFGL_REG_ADDRESS}, ADC2_RB1, ADC2_RB1_AN3, 0},
    #endif
    #ifdef ADC2_RB2_AN4
    {PB2, hal_ll_adc_module_num(ADC_MODULE_2), {HAL_LL_AD1PCFGL_REG_ADDRESS, HAL_LL_AD2PCFGL_REG_ADDRESS}, ADC2_RB2, ADC2_RB2_AN4, 0},
    #endif
    #ifdef ADC2_RB3_AN5
    {PB3, hal_ll_adc_module_num(ADC_MODULE_2), {HAL_LL_AD1PCFGL_REG_ADDRESS, HAL_LL_AD2PCFGL_REG_ADDRESS}, ADC2_RB3, ADC2_RB3_AN5, 0},
    #endif
    #ifdef ADC2_RB7_AN25
    {PB7, hal_ll_adc_module_num(ADC_MODULE_2), {HAL_LL_AD1PCFGH_REG_ADDRESS, 0}, ADC2_RB7, ADC2_RB7_AN25, 0},
    #endif
    #ifdef ADC2_RB8_AN26
    {PB8, hal_ll_adc_module_num(ADC_MODULE_2), {HAL_LL_AD1PCFGH_REG_ADDRESS, 0}, ADC2_RB8, ADC2_RB8_AN26, 0},
    #endif
    #ifdef ADC2_RB9_AN27
    {PB9, hal_ll_adc_module_num(ADC_MODULE_2), {HAL_LL_AD1PCFGH_REG_ADDRESS, 0}, ADC2_RB9, ADC2_RB9_AN27, 0},
    #endif
    #ifdef ADC2_RC0_AN6
    {PC0, hal_ll_adc_module_num(ADC_MODULE_2), {HAL_LL_AD1PCFGL_REG_ADDRESS, HAL_LL_AD2PCFGL_REG_ADDRESS}, ADC2_RC0, ADC2_RC0_AN6, 0},
    #endif
    #ifdef ADC2_RC1_AN7
    {PC1, hal_ll_adc_module_num(ADC_MODULE_2), {HAL_LL_AD1PCFGL_REG_ADDRESS, HAL_LL_AD2PCFGL_REG_ADDRESS}, ADC2_RC1, ADC2_RC1_AN7, 0},
    #endif
    #ifdef ADC2_RC2_AN8
    {PC2, hal_ll_adc_module_num(ADC_MODULE_2), {HAL_LL_AD1PCFGL_REG_ADDRESS, HAL_LL_AD2PCFGL_REG_ADDRESS}, ADC2_RC2, ADC2_RC2_AN8, 0},
    #endif
    #ifdef ADC2_RC3_AN29
    {PC3, hal_ll_adc_module_num(ADC_MODULE_2), {HAL_LL_AD1PCFGH_REG_ADDRESS, 0}, ADC2_RC3, ADC2_RC3_AN29, 0},
    #endif
    #ifdef ADC2_RC4_AN30
    {PC4, hal_ll_adc_module_num(ADC_MODULE_2), {HAL_LL_AD1PCFGH_REG_ADDRESS, 0}, ADC2_RC4, ADC2_RC4_AN30, 0},
    #endif
    #ifdef ADC2_RC5_AN31
    {PC5, hal_ll_adc_module_num(ADC_MODULE_2), {HAL_LL_AD1PCFGH_REG_ADDRESS, 0}, ADC2_RC5, ADC2_RC5_AN31, 0},
    #endif
    #ifdef ADC1_RA11_AN9
    {PA11, hal_ll_adc_module_num(ADC_MODULE_1), {HAL_LL_AD1PCFGL_REG_ADDRESS, HAL_LL_AD2PCFGL_REG_ADDRESS}, ADC1_RA11, ADC1_RA11_AN9, 0},
    #endif
    #ifdef ADC1_RA12_AN10
    {PA12, hal_ll_adc_module_num(ADC_MODULE_1), {HAL_LL_AD1PCFGL_REG_ADDRESS, HAL_LL_AD2PCFGL_REG_ADDRESS}, ADC1_RA12, ADC1_RA12_AN10, 0},
    #endif
    #ifdef ADC1_RC10_AN48
    {PC10, hal_ll_adc_module_num(ADC_MODULE_1), {HAL_LL_AD1PCFGH_REG_ADDRESS, 0}, ADC1_RC10, ADC1_RC10_AN48, 0},
    #endif
    #ifdef ADC1_RC11_AN11
    {PC11, hal_ll_adc_module_num(ADC_MODULE_1), {HAL_LL_AD1PCFGL_REG_ADDRESS, HAL_LL_AD2PCFGL_REG_ADDRESS}, ADC1_RC11, ADC1_RC11_AN11, 0},
    #endif
    #ifdef ADC1_RC12_AN49
    {PC12, hal_ll_adc_module_num(ADC_MODULE_1), {HAL_LL_AD1PCFGH_REG_ADDRESS, 0}, ADC1_RC12, ADC1_RC12_AN49, 0},
    #endif
    #ifdef ADC1_RE12_AN12
    {PE12, hal_ll_adc_module_num(ADC_MODULE_1), {HAL_LL_AD1PCFGL_REG_ADDRESS, HAL_LL_AD2PCFGL_REG_ADDRESS}, ADC1_RE12, ADC1_RE12_AN12, 0},
    #endif
    #ifdef ADC1_RE13_AN13
    {PE13, hal_ll_adc_module_num(ADC_MODULE_1), {HAL_LL_AD1PCFGL_REG_ADDRESS, HAL_LL_AD2PCFGL_REG_ADDRESS}, ADC1_RE13, ADC1_RE13_AN13, 0},
    #endif
    #ifdef ADC1_RE14_AN14
    {PE14, hal_ll_adc_module_num(ADC_MODULE_1), {HAL_LL_AD1PCFGL_REG_ADDRESS, HAL_LL_AD2PCFGL_REG_ADDRESS}, ADC1_RE14, ADC1_RE14_AN14, 0},
    #endif
    #ifdef ADC1_RE15_AN15
    {PE15, hal_ll_adc_module_num(ADC_MODULE_1), {HAL_LL_AD1PCFGL_REG_ADDRESS, HAL_LL_AD2PCFGL_REG_ADDRESS}, ADC1_RE15, ADC1_RE15_AN15, 0},
    #endif
    #ifdef ADC1_RG6_AN19
    {PG6, hal_ll_adc_module_num(ADC_MODULE_1), {HAL_LL_AD1PCFGH_REG_ADDRESS, 0}, ADC1_RG6, ADC1_RG6_AN19, 0},
    #endif
    #ifdef ADC1_RG7_AN18
    {PG7, hal_ll_adc_module_num(ADC_MODULE_1), {HAL_LL_AD1PCFGH_REG_ADDRESS, 0}, ADC1_RG7, ADC1_RG7_AN18, 0},
    #endif
    #ifdef ADC1_RG8_AN17
    {PG8, hal_ll_adc_module_num(ADC_MODULE_1), {HAL_LL_AD1PCFGH_REG_ADDRESS, 0}, ADC1_RG8, ADC1_RG8_AN17, 0},
    #endif
    #ifdef ADC1_RG9_AN16
    {PG9, hal_ll_adc_module_num(ADC_MODULE_1), {HAL_LL_AD1PCFGH_REG_ADDRESS, 0}, ADC1_RG9, ADC1_RG9_AN16, 0},
    #endif
    #ifdef ADC2_RA11_AN9
    {PA11, hal_ll_adc_module_num(ADC_MODULE_2), {HAL_LL_AD1PCFGL_REG_ADDRESS, HAL_LL_AD2PCFGL_REG_ADDRESS}, ADC2_RA11, ADC2_RA11_AN9, 0},
    #endif
    #ifdef ADC2_RA12_AN10
    {PA12, hal_ll_adc_module_num(ADC_MODULE_2), {HAL_LL_AD1PCFGL_REG_ADDRESS, HAL_LL_AD2PCFGL_REG_ADDRESS}, ADC2_RA12, ADC2_RA12_AN10, 0},
    #endif
    #ifdef ADC2_RC11_AN11
    {PC11, hal_ll_adc_module_num(ADC_MODULE_2), {HAL_LL_AD1PCFGL_REG_ADDRESS, HAL_LL_AD2PCFGL_REG_ADDRESS}, ADC2_RC11, ADC2_RC11_AN11, 0},
    #endif
    #ifdef ADC2_RE12_AN12
    {PE12, hal_ll_adc_module_num(ADC_MODULE_2), {HAL_LL_AD1PCFGL_REG_ADDRESS, HAL_LL_AD2PCFGL_REG_ADDRESS}, ADC2_RE12, ADC2_RE12_AN12, 0},
    #endif
    #ifdef ADC2_RE13_AN13
    {PE13, hal_ll_adc_module_num(ADC_MODULE_2), {HAL_LL_AD1PCFGL_REG_ADDRESS, HAL_LL_AD2PCFGL_REG_ADDRESS}, ADC2_RE13, ADC2_RE13_AN13, 0},
    #endif
    #ifdef ADC2_RE14_AN14
    {PE14, hal_ll_adc_module_num(ADC_MODULE_2), {HAL_LL_AD1PCFGL_REG_ADDRESS, HAL_LL_AD2PCFGL_REG_ADDRESS}, ADC2_RE14, ADC2_RE14_AN14, 0},
    #endif
    #ifdef ADC2_RE15_AN15
    {PE15, hal_ll_adc_module_num(ADC_MODULE_2), {HAL_LL_AD1PCFGL_REG_ADDRESS, HAL_LL_AD2PCFGL_REG_ADDRESS}, ADC2_RE15, ADC2_RE15_AN15, 0},
    #endif
    #ifdef ADC2_RG6_AN19
    {PG6, hal_ll_adc_module_num(ADC_MODULE_2), {HAL_LL_AD1PCFGH_REG_ADDRESS, 0}, ADC2_RG6, ADC2_RG6_AN19, 0},
    #endif
    #ifdef ADC2_RG7_AN18
    {PG7, hal_ll_adc_module_num(ADC_MODULE_2), {HAL_LL_AD1PCFGH_REG_ADDRESS, 0}, ADC2_RG7, ADC2_RG7_AN18, 0},
    #endif
    #ifdef ADC2_RG8_AN17
    {PG8, hal_ll_adc_module_num(ADC_MODULE_2), {HAL_LL_AD1PCFGH_REG_ADDRESS, 0}, ADC2_RG8, ADC2_RG8_AN17, 0},
    #endif
    #ifdef ADC2_RG9_AN16
    {PG9, hal_ll_adc_module_num(ADC_MODULE_2), {HAL_LL_AD1PCFGH_REG_ADDRESS, 0}, ADC2_RG9, ADC2_RG9_AN16, 0},
    #endif
    #ifdef ADC1_RA14_AN46
    {PA14, hal_ll_adc_module_num(ADC_MODULE_1), {HAL_LL_AD1PCFGH_REG_ADDRESS, 0}, ADC1_RA14, ADC1_RA14_AN46, 0},
    #endif
    #ifdef ADC1_RA15_AN47
    {PA15, hal_ll_adc_module_num(ADC_MODULE_1), {HAL_LL_AD1PCFGH_REG_ADDRESS, 0}, ADC1_RA15, ADC1_RA15_AN47, 0},
    #endif
    #ifdef ADC1_RD14_AN38
    {PD14, hal_ll_adc_module_num(ADC_MODULE_1), {HAL_LL_AD1PCFGH_REG_ADDRESS, 0}, ADC1_RD14, ADC1_RD14_AN38, 0},
    #endif
    #ifdef ADC1_RD15_AN39
    {PD15, hal_ll_adc_module_num(ADC_MODULE_1), {HAL_LL_AD1PCFGH_REG_ADDRESS, 0}, ADC1_RD15, ADC1_RD15_AN39, 0},
    #endif
    #ifdef ADC1_RE0_AN40
    {PE0, hal_ll_adc_module_num(ADC_MODULE_1), {HAL_LL_AD1PCFGH_REG_ADDRESS, 0}, ADC1_RE0, ADC1_RE0_AN40, 0},
    #endif
    #ifdef ADC1_RE1_AN41
    {PE1, hal_ll_adc_module_num(ADC_MODULE_1), {HAL_LL_AD1PCFGH_REG_ADDRESS, 0}, ADC1_RE1, ADC1_RE1_AN41, 0},
    #endif
    #ifdef ADC1_RE8_AN21
    {PE8, hal_ll_adc_module_num(ADC_MODULE_1), {HAL_LL_AD1PCFGH_REG_ADDRESS, 0}, ADC1_RE8, ADC1_RE8_AN21, 0},
    #endif
    #ifdef ADC1_RE9_AN20
    {PE9, hal_ll_adc_module_num(ADC_MODULE_1), {HAL_LL_AD1PCFGH_REG_ADDRESS, 0}, ADC1_RE9, ADC1_RE9_AN20, 0},
    #endif
    #ifdef ADC1_RF10_AN34
    {PF10, hal_ll_adc_module_num(ADC_MODULE_1), {HAL_LL_AD1PCFGH_REG_ADDRESS, 0}, ADC1_RF10, ADC1_RF10_AN34, 0},
    #endif
    #ifdef ADC1_RF12_AN37
    {PF12, hal_ll_adc_module_num(ADC_MODULE_1), {HAL_LL_AD1PCFGH_REG_ADDRESS, 0}, ADC1_RF12, ADC1_RF12_AN37, 0},
    #endif
    #ifdef ADC1_RF13_AN36
    {PF13, hal_ll_adc_module_num(ADC_MODULE_1), {HAL_LL_AD1PCFGH_REG_ADDRESS, 0}, ADC1_RF13, ADC1_RF13_AN36, 0},
    #endif
    #ifdef ADC1_RF4_AN44
    {PF4, hal_ll_adc_module_num(ADC_MODULE_1), {HAL_LL_AD1PCFGH_REG_ADDRESS, 0}, ADC1_RF4, ADC1_RF4_AN44, 0},
    #endif
    #ifdef ADC1_RF5_AN45
    {PF5, hal_ll_adc_module_num(ADC_MODULE_1), {HAL_LL_AD1PCFGH_REG_ADDRESS, 0}, ADC1_RF5, ADC1_RF5_AN45, 0},
    #endif
    #ifdef ADC1_RF9_AN33
    {PF9, hal_ll_adc_module_num(ADC_MODULE_1), {HAL_LL_AD1PCFGH_REG_ADDRESS, 0}, ADC1_RF9, ADC1_RF9_AN33, 0},
    #endif
    #ifdef ADC1_RG10_AN22
    {PG10, hal_ll_adc_module_num(ADC_MODULE_1), {HAL_LL_AD1PCFGH_REG_ADDRESS, 0}, ADC1_RG10, ADC1_RG10_AN22, 0},
    #endif
    #ifdef ADC1_RG11_AN35
    {PG11, hal_ll_adc_module_num(ADC_MODULE_1), {HAL_LL_AD1PCFGH_REG_ADDRESS, 0}, ADC1_RG11, ADC1_RG11_AN35, 0},
    #endif
    #ifdef ADC1_RG15_AN23
    {PG15, hal_ll_adc_module_num(ADC_MODULE_1), {HAL_LL_AD1PCFGH_REG_ADDRESS, 0}, ADC1_RG15, ADC1_RG15_AN23, 0},
    #endif
    #ifdef ADC1_RG2_AN42
    {PG2, hal_ll_adc_module_num(ADC_MODULE_1), {HAL_LL_AD1PCFGH_REG_ADDRESS, 0}, ADC1_RG2, ADC1_RG2_AN42, 0},
    #endif
    #ifdef ADC1_RG3_AN43
    {PG3, hal_ll_adc_module_num(ADC_MODULE_1), {HAL_LL_AD1PCFGH_REG_ADDRESS, 0}, ADC1_RG3, ADC1_RG3_AN43, 0},
    #endif
    #ifdef ADC2_RE8_AN21
    {PE8, hal_ll_adc_module_num(ADC_MODULE_2), {HAL_LL_AD1PCFGH_REG_ADDRESS, 0}, ADC2_RE8, ADC2_RE8_AN21, 0},
    #endif
    #ifdef ADC2_RE9_AN20
    {PE9, hal_ll_adc_module_num(ADC_MODULE_2), {HAL_LL_AD1PCFGH_REG_ADDRESS, 0}, ADC2_RE9, ADC2_RE9_AN20, 0},
    #endif
    #ifdef ADC2_RG10_AN22
    {PG10, hal_ll_adc_module_num(ADC_MODULE_2), {HAL_LL_AD1PCFGH_REG_ADDRESS, 0}, ADC2_RG10, ADC2_RG10_AN22, 0},
    #endif
    #ifdef ADC2_RG15_AN23
    {PG15, hal_ll_adc_module_num(ADC_MODULE_2), {HAL_LL_AD1PCFGH_REG_ADDRESS, 0}, ADC2_RG15, ADC2_RG15_AN23, 0},
    #endif
    #ifdef ADC1_RA2_AN2
    {PA2, hal_ll_adc_module_num(ADC_MODULE_1), {HAL_LL_AD1PCFGL_REG_ADDRESS, HAL_LL_AD2PCFGL_REG_ADDRESS}, ADC1_RA2, ADC1_RA2_AN2, 0},
    #endif
    #ifdef ADC1_RB0_AN3
    {PB0, hal_ll_adc_module_num(ADC_MODULE_1), {HAL_LL_AD1PCFGL_REG_ADDRESS, HAL_LL_AD2PCFGL_REG_ADDRESS}, ADC1_RB0, ADC1_RB0_AN3, 0},
    #endif
    #ifdef ADC1_RB1_AN6
    {PB1, hal_ll_adc_module_num(ADC_MODULE_1), {HAL_LL_AD1PCFGL_REG_ADDRESS, HAL_LL_AD2PCFGL_REG_ADDRESS}, ADC1_RB1, ADC1_RB1_AN6, 0},
    #endif
    #ifdef ADC1_RB2_AN7
    {PB2, hal_ll_adc_module_num(ADC_MODULE_1), {HAL_LL_AD1PCFGL_REG_ADDRESS, HAL_LL_AD2PCFGL_REG_ADDRESS}, ADC1_RB2, ADC1_RB2_AN7, 0},
    #endif
    #ifdef ADC1_RB3_AN18
    {PB3, hal_ll_adc_module_num(ADC_MODULE_1), {HAL_LL_AD1PCFGH_REG_ADDRESS, 0}, ADC1_RB3, ADC1_RB3_AN18, 0},
    #endif
    #ifdef ADC1_RB5_AN19
    {PB5, hal_ll_adc_module_num(ADC_MODULE_1), {HAL_LL_AD1PCFGH_REG_ADDRESS, 0}, ADC1_RB5, ADC1_RB5_AN19, 0},
    #endif
    #ifdef ADC1_RB6_AN20
    {PB6, hal_ll_adc_module_num(ADC_MODULE_1), {HAL_LL_AD1PCFGH_REG_ADDRESS, 0}, ADC1_RB6, ADC1_RB6_AN20, 0},
    #endif
    #ifdef ADC1_RB7_AN21
    {PB7, hal_ll_adc_module_num(ADC_MODULE_1), {HAL_LL_AD1PCFGH_REG_ADDRESS, 0}, ADC1_RB7, ADC1_RB7_AN21, 0},
    #endif
    #ifdef ADC1_RB9_AN4
    {PB9, hal_ll_adc_module_num(ADC_MODULE_1), {HAL_LL_AD1PCFGL_REG_ADDRESS, HAL_LL_AD2PCFGL_REG_ADDRESS}, ADC1_RB9, ADC1_RB9_AN4, 0},
    #endif
    #ifdef ADC1_RC1_AN8
    {PC1, hal_ll_adc_module_num(ADC_MODULE_1), {HAL_LL_AD1PCFGL_REG_ADDRESS, HAL_LL_AD2PCFGL_REG_ADDRESS}, ADC1_RC1, ADC1_RC1_AN8, 0},
    #endif
    #ifdef ADC1_RC10_AN10
    {PC10, hal_ll_adc_module_num(ADC_MODULE_1), {HAL_LL_AD1PCFGL_REG_ADDRESS, HAL_LL_AD2PCFGL_REG_ADDRESS}, ADC1_RC10, ADC1_RC10_AN10, 0},
    #endif
    #ifdef ADC1_RC12_AN14
    {PC12, hal_ll_adc_module_num(ADC_MODULE_1), {HAL_LL_AD1PCFGL_REG_ADDRESS, HAL_LL_AD2PCFGL_REG_ADDRESS}, ADC1_RC12, ADC1_RC12_AN14, 0},
    #endif
    #ifdef ADC1_RC2_AN9
    {PC2, hal_ll_adc_module_num(ADC_MODULE_1), {HAL_LL_AD1PCFGL_REG_ADDRESS, HAL_LL_AD2PCFGL_REG_ADDRESS}, ADC1_RC2, ADC1_RC2_AN9, 0},
    #endif
    #ifdef ADC1_RC6_AN17
    {PC6, hal_ll_adc_module_num(ADC_MODULE_1), {HAL_LL_AD1PCFGH_REG_ADDRESS, 0}, ADC1_RC6, ADC1_RC6_AN17, 0},
    #endif
    #ifdef ADC1_RC9_AN11
    {PC9, hal_ll_adc_module_num(ADC_MODULE_1), {HAL_LL_AD1PCFGL_REG_ADDRESS, HAL_LL_AD2PCFGL_REG_ADDRESS}, ADC1_RC9, ADC1_RC9_AN11, 0},
    #endif
    #ifdef ADC1_RD13_AN13
    {PD13, hal_ll_adc_module_num(ADC_MODULE_1), {HAL_LL_AD1PCFGL_REG_ADDRESS, HAL_LL_AD2PCFGL_REG_ADDRESS}, ADC1_RD13, ADC1_RD13_AN13, 0},
    #endif
    #ifdef ADC1_RD2_AN16
    {PD2, hal_ll_adc_module_num(ADC_MODULE_1), {HAL_LL_AD1PCFGH_REG_ADDRESS, 0}, ADC1_RD2, ADC1_RD2_AN16, 0},
    #endif
    #ifdef ADC1_RD5_AN12
    {PD5, hal_ll_adc_module_num(ADC_MODULE_1), {HAL_LL_AD1PCFGL_REG_ADDRESS, HAL_LL_AD2PCFGL_REG_ADDRESS}, ADC1_RD5, ADC1_RD5_AN12, 0},
    #endif
    #ifdef ADC1_RD7_AN15
    {PD7, hal_ll_adc_module_num(ADC_MODULE_1), {HAL_LL_AD1PCFGL_REG_ADDRESS, HAL_LL_AD2PCFGL_REG_ADDRESS}, ADC1_RD7, ADC1_RD7_AN15, 0},
    #endif
    #ifdef ADC1_RD8_AN5
    {PD8, hal_ll_adc_module_num(ADC_MODULE_1), {HAL_LL_AD1PCFGL_REG_ADDRESS, HAL_LL_AD2PCFGL_REG_ADDRESS}, ADC1_RD8, ADC1_RD8_AN5, 0},
    #endif
    #ifdef ADC1_RB10_AN5
    {PB10, hal_ll_adc_module_num(ADC_MODULE_1), {HAL_LL_AD1PCFGL_REG_ADDRESS, HAL_LL_AD2PCFGL_REG_ADDRESS}, ADC1_RB10, ADC1_RB10_AN5, 0},
    #endif
    #ifdef ADC1_RB3_AN8
    {PB3, hal_ll_adc_module_num(ADC_MODULE_1), {HAL_LL_AD1PCFGL_REG_ADDRESS, HAL_LL_AD2PCFGL_REG_ADDRESS}, ADC1_RB3, ADC1_RB3_AN8, 0},
    #endif
    #ifdef ADC1_RB5_AN9
    {PB5, hal_ll_adc_module_num(ADC_MODULE_1), {HAL_LL_AD1PCFGL_REG_ADDRESS, HAL_LL_AD2PCFGL_REG_ADDRESS}, ADC1_RB5, ADC1_RB5_AN9, 0},
    #endif
    #ifdef ADC1_RB6_AN10
    {PB6, hal_ll_adc_module_num(ADC_MODULE_1), {HAL_LL_AD1PCFGL_REG_ADDRESS, HAL_LL_AD2PCFGL_REG_ADDRESS}, ADC1_RB6, ADC1_RB6_AN10, 0},
    #endif
    #ifdef ADC1_RB7_AN11
    {PB7, hal_ll_adc_module_num(ADC_MODULE_1), {HAL_LL_AD1PCFGL_REG_ADDRESS, HAL_LL_AD2PCFGL_REG_ADDRESS}, ADC1_RB7, ADC1_RB7_AN11, 0},
    #endif
    #ifdef ADC1_RC11_AN12
    {PC11, hal_ll_adc_module_num(ADC_MODULE_1), {HAL_LL_AD1PCFGL_REG_ADDRESS, HAL_LL_AD2PCFGL_REG_ADDRESS}, ADC1_RC11, ADC1_RC11_AN12, 0},
    #endif
    #ifdef ADC1_RB0_AN0
    {PB0, hal_ll_adc_module_num(ADC_MODULE_1), {HAL_LL_AD1PCFGL_REG_ADDRESS, HAL_LL_AD2PCFGL_REG_ADDRESS}, ADC1_RB0, ADC1_RB0_AN0, 0},
    #endif
    #ifdef ADC1_RB1_AN1
    {PB1, hal_ll_adc_module_num(ADC_MODULE_1), {HAL_LL_AD1PCFGL_REG_ADDRESS, HAL_LL_AD2PCFGL_REG_ADDRESS}, ADC1_RB1, ADC1_RB1_AN1, 0},
    #endif
    #ifdef ADC1_RB10_AN10
    {PB10, hal_ll_adc_module_num(ADC_MODULE_1), {HAL_LL_AD1PCFGL_REG_ADDRESS, HAL_LL_AD2PCFGL_REG_ADDRESS}, ADC1_RB10, ADC1_RB10_AN10, 0},
    #endif
    #ifdef ADC1_RB11_AN11
    {PB11, hal_ll_adc_module_num(ADC_MODULE_1), {HAL_LL_AD1PCFGL_REG_ADDRESS, HAL_LL_AD2PCFGL_REG_ADDRESS}, ADC1_RB11, ADC1_RB11_AN11, 0},
    #endif
    #ifdef ADC1_RB12_AN12
    {PB12, hal_ll_adc_module_num(ADC_MODULE_1), {HAL_LL_AD1PCFGL_REG_ADDRESS, HAL_LL_AD2PCFGL_REG_ADDRESS}, ADC1_RB12, ADC1_RB12_AN12, 0},
    #endif
    #ifdef ADC1_RB13_AN13
    {PB13, hal_ll_adc_module_num(ADC_MODULE_1), {HAL_LL_AD1PCFGL_REG_ADDRESS, HAL_LL_AD2PCFGL_REG_ADDRESS}, ADC1_RB13, ADC1_RB13_AN13, 0},
    #endif
    #ifdef ADC1_RB14_AN14
    {PB14, hal_ll_adc_module_num(ADC_MODULE_1), {HAL_LL_AD1PCFGL_REG_ADDRESS, HAL_LL_AD2PCFGL_REG_ADDRESS}, ADC1_RB14, ADC1_RB14_AN14, 0},
    #endif
    #ifdef ADC1_RB15_AN15
    {PB15, hal_ll_adc_module_num(ADC_MODULE_1), {HAL_LL_AD1PCFGL_REG_ADDRESS, HAL_LL_AD2PCFGL_REG_ADDRESS}, ADC1_RB15, ADC1_RB15_AN15, 0},
    #endif
    #ifdef ADC1_RB2_AN2
    {PB2, hal_ll_adc_module_num(ADC_MODULE_1), {HAL_LL_AD1PCFGL_REG_ADDRESS, HAL_LL_AD2PCFGL_REG_ADDRESS}, ADC1_RB2, ADC1_RB2_AN2, 0},
    #endif
    #ifdef ADC1_RB3_AN3
    {PB3, hal_ll_adc_module_num(ADC_MODULE_1), {HAL_LL_AD1PCFGL_REG_ADDRESS, HAL_LL_AD2PCFGL_REG_ADDRESS}, ADC1_RB3, ADC1_RB3_AN3, 0},
    #endif
    #ifdef ADC1_RB4_AN4
    {PB4, hal_ll_adc_module_num(ADC_MODULE_1), {HAL_LL_AD1PCFGL_REG_ADDRESS, HAL_LL_AD2PCFGL_REG_ADDRESS}, ADC1_RB4, ADC1_RB4_AN4, 0},
    #endif
    #ifdef ADC1_RB5_AN5
    {PB5, hal_ll_adc_module_num(ADC_MODULE_1), {HAL_LL_AD1PCFGL_REG_ADDRESS, HAL_LL_AD2PCFGL_REG_ADDRESS}, ADC1_RB5, ADC1_RB5_AN5, 0},
    #endif
    #ifdef ADC1_RB6_AN6
    {PB6, hal_ll_adc_module_num(ADC_MODULE_1), {HAL_LL_AD1PCFGL_REG_ADDRESS, HAL_LL_AD2PCFGL_REG_ADDRESS}, ADC1_RB6, ADC1_RB6_AN6, 0},
    #endif
    #ifdef ADC1_RB7_AN7
    {PB7, hal_ll_adc_module_num(ADC_MODULE_1), {HAL_LL_AD1PCFGL_REG_ADDRESS, HAL_LL_AD2PCFGL_REG_ADDRESS}, ADC1_RB7, ADC1_RB7_AN7, 0},
    #endif
    #ifdef ADC1_RB8_AN8
    {PB8, hal_ll_adc_module_num(ADC_MODULE_1), {HAL_LL_AD1PCFGL_REG_ADDRESS, HAL_LL_AD2PCFGL_REG_ADDRESS}, ADC1_RB8, ADC1_RB8_AN8, 0},
    #endif
    #ifdef ADC1_RB9_AN9
    {PB9, hal_ll_adc_module_num(ADC_MODULE_1), {HAL_LL_AD1PCFGL_REG_ADDRESS, HAL_LL_AD2PCFGL_REG_ADDRESS}, ADC1_RB9, ADC1_RB9_AN9, 0},
    #endif
    #ifdef ADC1_RE0_AN24
    {PE0, hal_ll_adc_module_num(ADC_MODULE_1), {HAL_LL_AD1PCFGH_REG_ADDRESS, 0}, ADC1_RE0, ADC1_RE0_AN24, 0},
    #endif
    #ifdef ADC1_RE1_AN25
    {PE1, hal_ll_adc_module_num(ADC_MODULE_1), {HAL_LL_AD1PCFGH_REG_ADDRESS, 0}, ADC1_RE1, ADC1_RE1_AN25, 0},
    #endif
    #ifdef ADC1_RE2_AN26
    {PE2, hal_ll_adc_module_num(ADC_MODULE_1), {HAL_LL_AD1PCFGH_REG_ADDRESS, 0}, ADC1_RE2, ADC1_RE2_AN26, 0},
    #endif
    #ifdef ADC1_RE3_AN27
    {PE3, hal_ll_adc_module_num(ADC_MODULE_1), {HAL_LL_AD1PCFGH_REG_ADDRESS, 0}, ADC1_RE3, ADC1_RE3_AN27, 0},
    #endif
    #ifdef ADC1_RE4_AN28
    {PE4, hal_ll_adc_module_num(ADC_MODULE_1), {HAL_LL_AD1PCFGH_REG_ADDRESS, 0}, ADC1_RE4, ADC1_RE4_AN28, 0},
    #endif
    #ifdef ADC1_RE5_AN29
    {PE5, hal_ll_adc_module_num(ADC_MODULE_1), {HAL_LL_AD1PCFGH_REG_ADDRESS, 0}, ADC1_RE5, ADC1_RE5_AN29, 0},
    #endif
    #ifdef ADC1_RE6_AN30
    {PE6, hal_ll_adc_module_num(ADC_MODULE_1), {HAL_LL_AD1PCFGH_REG_ADDRESS, 0}, ADC1_RE6, ADC1_RE6_AN30, 0},
    #endif
    #ifdef ADC1_RE7_AN31
    {PE7, hal_ll_adc_module_num(ADC_MODULE_1), {HAL_LL_AD1PCFGH_REG_ADDRESS, 0}, ADC1_RE7, ADC1_RE7_AN31, 0},
    #endif
    #ifdef ADC2_RB0_AN0
    {PB0, hal_ll_adc_module_num(ADC_MODULE_2), {HAL_LL_AD1PCFGL_REG_ADDRESS, HAL_LL_AD2PCFGL_REG_ADDRESS}, ADC2_RB0, ADC2_RB0_AN0, 0},
    #endif
    #ifdef ADC2_RB1_AN1
    {PB1, hal_ll_adc_module_num(ADC_MODULE_2), {HAL_LL_AD1PCFGL_REG_ADDRESS, HAL_LL_AD2PCFGL_REG_ADDRESS}, ADC2_RB1, ADC2_RB1_AN1, 0},
    #endif
    #ifdef ADC2_RB10_AN10
    {PB10, hal_ll_adc_module_num(ADC_MODULE_2), {HAL_LL_AD1PCFGL_REG_ADDRESS, HAL_LL_AD2PCFGL_REG_ADDRESS}, ADC2_RB10, ADC2_RB10_AN10, 0},
    #endif
    #ifdef ADC2_RB11_AN11
    {PB11, hal_ll_adc_module_num(ADC_MODULE_2), {HAL_LL_AD1PCFGL_REG_ADDRESS, HAL_LL_AD2PCFGL_REG_ADDRESS}, ADC2_RB11, ADC2_RB11_AN11, 0},
    #endif
    #ifdef ADC2_RB12_AN12
    {PB12, hal_ll_adc_module_num(ADC_MODULE_2), {HAL_LL_AD1PCFGL_REG_ADDRESS, HAL_LL_AD2PCFGL_REG_ADDRESS}, ADC2_RB12, ADC2_RB12_AN12, 0},
    #endif
    #ifdef ADC2_RB13_AN13
    {PB13, hal_ll_adc_module_num(ADC_MODULE_2), {HAL_LL_AD1PCFGL_REG_ADDRESS, HAL_LL_AD2PCFGL_REG_ADDRESS}, ADC2_RB13, ADC2_RB13_AN13, 0},
    #endif
    #ifdef ADC2_RB14_AN14
    {PB14, hal_ll_adc_module_num(ADC_MODULE_2), {HAL_LL_AD1PCFGL_REG_ADDRESS, HAL_LL_AD2PCFGL_REG_ADDRESS}, ADC2_RB14, ADC2_RB14_AN14, 0},
    #endif
    #ifdef ADC2_RB15_AN15
    {PB15, hal_ll_adc_module_num(ADC_MODULE_2), {HAL_LL_AD1PCFGL_REG_ADDRESS, HAL_LL_AD2PCFGL_REG_ADDRESS}, ADC2_RB15, ADC2_RB15_AN15, 0},
    #endif
    #ifdef ADC2_RB2_AN2
    {PB2, hal_ll_adc_module_num(ADC_MODULE_2), {HAL_LL_AD1PCFGL_REG_ADDRESS, HAL_LL_AD2PCFGL_REG_ADDRESS}, ADC2_RB2, ADC2_RB2_AN2, 0},
    #endif
    #ifdef ADC2_RB3_AN3
    {PB3, hal_ll_adc_module_num(ADC_MODULE_2), {HAL_LL_AD1PCFGL_REG_ADDRESS, HAL_LL_AD2PCFGL_REG_ADDRESS}, ADC2_RB3, ADC2_RB3_AN3, 0},
    #endif
    #ifdef ADC2_RB4_AN4
    {PB4, hal_ll_adc_module_num(ADC_MODULE_2), {HAL_LL_AD1PCFGL_REG_ADDRESS, HAL_LL_AD2PCFGL_REG_ADDRESS}, ADC2_RB4, ADC2_RB4_AN4, 0},
    #endif
    #ifdef ADC2_RB5_AN5
    {PB5, hal_ll_adc_module_num(ADC_MODULE_2), {HAL_LL_AD1PCFGL_REG_ADDRESS, HAL_LL_AD2PCFGL_REG_ADDRESS}, ADC2_RB5, ADC2_RB5_AN5, 0},
    #endif
    #ifdef ADC2_RB6_AN6
    {PB6, hal_ll_adc_module_num(ADC_MODULE_2), {HAL_LL_AD1PCFGL_REG_ADDRESS, HAL_LL_AD2PCFGL_REG_ADDRESS}, ADC2_RB6, ADC2_RB6_AN6, 0},
    #endif
    #ifdef ADC2_RB7_AN7
    {PB7, hal_ll_adc_module_num(ADC_MODULE_2), {HAL_LL_AD1PCFGL_REG_ADDRESS, HAL_LL_AD2PCFGL_REG_ADDRESS}, ADC2_RB7, ADC2_RB7_AN7, 0},
    #endif
    #ifdef ADC2_RB8_AN8
    {PB8, hal_ll_adc_module_num(ADC_MODULE_2), {HAL_LL_AD1PCFGL_REG_ADDRESS, HAL_LL_AD2PCFGL_REG_ADDRESS}, ADC2_RB8, ADC2_RB8_AN8, 0},
    #endif
    #ifdef ADC2_RB9_AN9
    {PB9, hal_ll_adc_module_num(ADC_MODULE_2), {HAL_LL_AD1PCFGL_REG_ADDRESS, HAL_LL_AD2PCFGL_REG_ADDRESS}, ADC2_RB9, ADC2_RB9_AN9, 0},
    #endif
    #ifdef ADC1_RA6_AN22
    {PA6, hal_ll_adc_module_num(ADC_MODULE_1), {HAL_LL_AD1PCFGH_REG_ADDRESS, 0}, ADC1_RA6, ADC1_RA6_AN22, 0},
    #endif
    #ifdef ADC1_RA7_AN23
    {PA7, hal_ll_adc_module_num(ADC_MODULE_1), {HAL_LL_AD1PCFGH_REG_ADDRESS, 0}, ADC1_RA7, ADC1_RA7_AN23, 0},
    #endif
    #ifdef ADC1_RC1_AN16
    {PC1, hal_ll_adc_module_num(ADC_MODULE_1), {HAL_LL_AD1PCFGH_REG_ADDRESS, 0}, ADC1_RC1, ADC1_RC1_AN16, 0},
    #endif
    #ifdef ADC1_RC2_AN17
    {PC2, hal_ll_adc_module_num(ADC_MODULE_1), {HAL_LL_AD1PCFGH_REG_ADDRESS, 0}, ADC1_RC2, ADC1_RC2_AN17, 0},
    #endif
    #ifdef ADC1_RC3_AN18
    {PC3, hal_ll_adc_module_num(ADC_MODULE_1), {HAL_LL_AD1PCFGH_REG_ADDRESS, 0}, ADC1_RC3, ADC1_RC3_AN18, 0},
    #endif
    #ifdef ADC1_RC4_AN19
    {PC4, hal_ll_adc_module_num(ADC_MODULE_1), {HAL_LL_AD1PCFGH_REG_ADDRESS, 0}, ADC1_RC4, ADC1_RC4_AN19, 0},
    #endif
    #ifdef ADC1_RE8_AN20
    {PE8, hal_ll_adc_module_num(ADC_MODULE_1), {HAL_LL_AD1PCFGH_REG_ADDRESS, 0}, ADC1_RE8, ADC1_RE8_AN20, 0},
    #endif
    #ifdef ADC1_RE9_AN21
    {PE9, hal_ll_adc_module_num(ADC_MODULE_1), {HAL_LL_AD1PCFGH_REG_ADDRESS, 0}, ADC1_RE9, ADC1_RE9_AN21, 0},
    #endif
    #ifdef ADC1_RA10_AN56
    {PA10, hal_ll_adc_module_num(ADC_MODULE_1), {HAL_LL_AD1PCFGH_REG_ADDRESS, 0}, ADC1_RA10, ADC1_RA10_AN56, 0},
    #endif
    #ifdef ADC1_RA7_AN55
    {PA7, hal_ll_adc_module_num(ADC_MODULE_1), {HAL_LL_AD1PCFGH_REG_ADDRESS, 0}, ADC1_RA7, ADC1_RA7_AN55, 0},
    #endif
    #ifdef ADC1_RC6_AN53
    {PC6, hal_ll_adc_module_num(ADC_MODULE_1), {HAL_LL_AD1PCFGH_REG_ADDRESS, 0}, ADC1_RC6, ADC1_RC6_AN53, 0},
    #endif
    #ifdef ADC1_RC7_AN52
    {PC7, hal_ll_adc_module_num(ADC_MODULE_1), {HAL_LL_AD1PCFGH_REG_ADDRESS, 0}, ADC1_RC7, ADC1_RC7_AN52, 0},
    #endif
    #ifdef ADC1_RC8_AN51
    {PC8, hal_ll_adc_module_num(ADC_MODULE_1), {HAL_LL_AD1PCFGH_REG_ADDRESS, 0}, ADC1_RC8, ADC1_RC8_AN51, 0},
    #endif
    #ifdef ADC1_RC9_AN54
    {PC9, hal_ll_adc_module_num(ADC_MODULE_1), {HAL_LL_AD1PCFGH_REG_ADDRESS, 0}, ADC1_RC9, ADC1_RC9_AN54, 0},
    #endif
    #ifdef ADC_RA0_AN0
    {PA0, hal_ll_adc_module_num(ADC_MODULE), {HAL_LL_AD1PCFGL_REG_ADDRESS, HAL_LL_AD2PCFGL_REG_ADDRESS}, ADC_RA0, ADC_RA0_AN0, 0},
    #endif
    #ifdef ADC_RA1_AN1
    {PA1, hal_ll_adc_module_num(ADC_MODULE), {HAL_LL_AD1PCFGL_REG_ADDRESS, HAL_LL_AD2PCFGL_REG_ADDRESS}, ADC_RA1, ADC_RA1_AN1, 0},
    #endif
    #ifdef ADC_RB0_AN2
    {PB0, hal_ll_adc_module_num(ADC_MODULE), {HAL_LL_AD1PCFGL_REG_ADDRESS, HAL_LL_AD2PCFGL_REG_ADDRESS}, ADC_RB0, ADC_RB0_AN2, 0},
    #endif
    #ifdef ADC_RB1_AN3
    {PB1, hal_ll_adc_module_num(ADC_MODULE), {HAL_LL_AD1PCFGL_REG_ADDRESS, HAL_LL_AD2PCFGL_REG_ADDRESS}, ADC_RB1, ADC_RB1_AN3, 0},
    #endif
    #ifdef ADC_RB13_AN11
    {PB13, hal_ll_adc_module_num(ADC_MODULE), {HAL_LL_AD1PCFGL_REG_ADDRESS, HAL_LL_AD2PCFGL_REG_ADDRESS}, ADC_RB13, ADC_RB13_AN11, 0},
    #endif
    #ifdef ADC_RB14_AN10
    {PB14, hal_ll_adc_module_num(ADC_MODULE), {HAL_LL_AD1PCFGL_REG_ADDRESS, HAL_LL_AD2PCFGL_REG_ADDRESS}, ADC_RB14, ADC_RB14_AN10, 0},
    #endif
    #ifdef ADC_RB15_AN9
    {PB15, hal_ll_adc_module_num(ADC_MODULE), {HAL_LL_AD1PCFGL_REG_ADDRESS, HAL_LL_AD2PCFGL_REG_ADDRESS}, ADC_RB15, ADC_RB15_AN9, 0},
    #endif
    #ifdef ADC_RB2_AN4
    {PB2, hal_ll_adc_module_num(ADC_MODULE), {HAL_LL_AD1PCFGL_REG_ADDRESS, HAL_LL_AD2PCFGL_REG_ADDRESS}, ADC_RB2, ADC_RB2_AN4, 0},
    #endif
    #ifdef ADC_RB3_AN5
    {PB3, hal_ll_adc_module_num(ADC_MODULE), {HAL_LL_AD1PCFGL_REG_ADDRESS, HAL_LL_AD2PCFGL_REG_ADDRESS}, ADC_RB3, ADC_RB3_AN5, 0},
    #endif
    #ifdef ADC_RC0_AN6
    {PC0, hal_ll_adc_module_num(ADC_MODULE), {HAL_LL_AD1PCFGL_REG_ADDRESS, HAL_LL_AD2PCFGL_REG_ADDRESS}, ADC_RC0, ADC_RC0_AN6, 0},
    #endif
    #ifdef ADC_RC1_AN7
    {PC1, hal_ll_adc_module_num(ADC_MODULE), {HAL_LL_AD1PCFGL_REG_ADDRESS, HAL_LL_AD2PCFGL_REG_ADDRESS}, ADC_RC1, ADC_RC1_AN7, 0},
    #endif
    #ifdef ADC_RC2_AN8
    {PC2, hal_ll_adc_module_num(ADC_MODULE), {HAL_LL_AD1PCFGL_REG_ADDRESS, HAL_LL_AD2PCFGL_REG_ADDRESS}, ADC_RC2, ADC_RC2_AN8, 0},
    #endif
    #ifdef ADC_RC1_AN16
    {PC1, hal_ll_adc_module_num(ADC_MODULE), {HAL_LL_AD1PCFGH_REG_ADDRESS, 0}, ADC_RC1, ADC_RC1_AN16, 0},
    #endif
    #ifdef ADC_RC2_AN17
    {PC2, hal_ll_adc_module_num(ADC_MODULE), {HAL_LL_AD1PCFGH_REG_ADDRESS, 0}, ADC_RC2, ADC_RC2_AN17, 0},
    #endif
    #ifdef ADC_RA12_AN20
    {PA12, hal_ll_adc_module_num(ADC_MODULE), {HAL_LL_AD1PCFGH_REG_ADDRESS, 0}, ADC_RA12, ADC_RA12_AN20, 0},
    #endif
    #ifdef ADC_RA13_AN21
    {PA13, hal_ll_adc_module_num(ADC_MODULE), {HAL_LL_AD1PCFGH_REG_ADDRESS, 0}, ADC_RA13, ADC_RA13_AN21, 0},
    #endif
    #ifdef ADC_RA6_AN22
    {PA6, hal_ll_adc_module_num(ADC_MODULE), {HAL_LL_AD1PCFGH_REG_ADDRESS, 0}, ADC_RA6, ADC_RA6_AN22, 0},
    #endif
    #ifdef ADC_RA7_AN23
    {PA7, hal_ll_adc_module_num(ADC_MODULE), {HAL_LL_AD1PCFGH_REG_ADDRESS, 0}, ADC_RA7, ADC_RA7_AN23, 0},
    #endif
    #ifdef ADC_RC3_AN18
    {PC3, hal_ll_adc_module_num(ADC_MODULE), {HAL_LL_AD1PCFGH_REG_ADDRESS, 0}, ADC_RC3, ADC_RC3_AN18, 0},
    #endif
    #ifdef ADC_RC4_AN19
    {PC4, hal_ll_adc_module_num(ADC_MODULE), {HAL_LL_AD1PCFGH_REG_ADDRESS, 0}, ADC_RC4, ADC_RC4_AN19, 0},
    #endif
    #ifdef ADC_RE0_AN24
    {PE0, hal_ll_adc_module_num(ADC_MODULE), {HAL_LL_AD1PCFGH_REG_ADDRESS, 0}, ADC_RE0, ADC_RE0_AN24, 0},
    #endif
    #ifdef ADC_RE1_AN25
    {PE1, hal_ll_adc_module_num(ADC_MODULE), {HAL_LL_AD1PCFGH_REG_ADDRESS, 0}, ADC_RE1, ADC_RE1_AN25, 0},
    #endif
    #ifdef ADC_RE2_AN26
    {PE2, hal_ll_adc_module_num(ADC_MODULE), {HAL_LL_AD1PCFGH_REG_ADDRESS, 0}, ADC_RE2, ADC_RE2_AN26, 0},
    #endif
    #ifdef ADC_RE3_AN27
    {PE3, hal_ll_adc_module_num(ADC_MODULE), {HAL_LL_AD1PCFGH_REG_ADDRESS, 0}, ADC_RE3, ADC_RE3_AN27, 0},
    #endif
    #ifdef ADC_RE4_AN28
    {PE4, hal_ll_adc_module_num(ADC_MODULE), {HAL_LL_AD1PCFGH_REG_ADDRESS, 0}, ADC_RE4, ADC_RE4_AN28, 0},
    #endif
    #ifdef ADC_RE5_AN29
    {PE5, hal_ll_adc_module_num(ADC_MODULE), {HAL_LL_AD1PCFGH_REG_ADDRESS, 0}, ADC_RE5, ADC_RE5_AN29, 0},
    #endif
    #ifdef ADC_RE6_AN30
    {PE6, hal_ll_adc_module_num(ADC_MODULE), {HAL_LL_AD1PCFGH_REG_ADDRESS, 0}, ADC_RE6, ADC_RE6_AN30, 0},
    #endif
    #ifdef ADC_RE7_AN31
    {PE7, hal_ll_adc_module_num(ADC_MODULE), {HAL_LL_AD1PCFGH_REG_ADDRESS, 0}, ADC_RE7, ADC_RE7_AN31, 0},
    #endif
    #ifdef ADC2_RC1_AN16
    {PC1, hal_ll_adc_module_num(ADC_MODULE_2), {HAL_LL_AD1PCFGH_REG_ADDRESS, 0}, ADC2_RC1, ADC2_RC1_AN16, 0},
    #endif
    #ifdef ADC2_RC2_AN17
    {PC2, hal_ll_adc_module_num(ADC_MODULE_2), {HAL_LL_AD1PCFGH_REG_ADDRESS, 0}, ADC2_RC2, ADC2_RC2_AN17, 0},
    #endif
    #ifdef ADC1_RA12_AN20
    {PA12, hal_ll_adc_module_num(ADC_MODULE_1), {HAL_LL_AD1PCFGH_REG_ADDRESS, 0}, ADC1_RA12, ADC1_RA12_AN20, 0},
    #endif
    #ifdef ADC1_RA13_AN21
    {PA13, hal_ll_adc_module_num(ADC_MODULE_1), {HAL_LL_AD1PCFGH_REG_ADDRESS, 0}, ADC1_RA13, ADC1_RA13_AN21, 0},
    #endif
    #ifdef ADC2_RA12_AN20
    {PA12, hal_ll_adc_module_num(ADC_MODULE_2), {HAL_LL_AD1PCFGH_REG_ADDRESS, 0}, ADC2_RA12, ADC2_RA12_AN20, 0},
    #endif
    #ifdef ADC2_RA13_AN21
    {PA13, hal_ll_adc_module_num(ADC_MODULE_2), {HAL_LL_AD1PCFGH_REG_ADDRESS, 0}, ADC2_RA13, ADC2_RA13_AN21, 0},
    #endif
    #ifdef ADC2_RA6_AN22
    {PA6, hal_ll_adc_module_num(ADC_MODULE_2), {HAL_LL_AD1PCFGH_REG_ADDRESS, 0}, ADC2_RA6, ADC2_RA6_AN22, 0},
    #endif
    #ifdef ADC2_RA7_AN23
    {PA7, hal_ll_adc_module_num(ADC_MODULE_2), {HAL_LL_AD1PCFGH_REG_ADDRESS, 0}, ADC2_RA7, ADC2_RA7_AN23, 0},
    #endif
    #ifdef ADC2_RC3_AN18
    {PC3, hal_ll_adc_module_num(ADC_MODULE_2), {HAL_LL_AD1PCFGH_REG_ADDRESS, 0}, ADC2_RC3, ADC2_RC3_AN18, 0},
    #endif
    #ifdef ADC2_RC4_AN19
    {PC4, hal_ll_adc_module_num(ADC_MODULE_2), {HAL_LL_AD1PCFGH_REG_ADDRESS, 0}, ADC2_RC4, ADC2_RC4_AN19, 0},
    #endif
    #ifdef ADC2_RE0_AN24
    {PE0, hal_ll_adc_module_num(ADC_MODULE_2), {HAL_LL_AD1PCFGH_REG_ADDRESS, 0}, ADC2_RE0, ADC2_RE0_AN24, 0},
    #endif
    #ifdef ADC2_RE1_AN25
    {PE1, hal_ll_adc_module_num(ADC_MODULE_2), {HAL_LL_AD1PCFGH_REG_ADDRESS, 0}, ADC2_RE1, ADC2_RE1_AN25, 0},
    #endif
    #ifdef ADC2_RE2_AN26
    {PE2, hal_ll_adc_module_num(ADC_MODULE_2), {HAL_LL_AD1PCFGH_REG_ADDRESS, 0}, ADC2_RE2, ADC2_RE2_AN26, 0},
    #endif
    #ifdef ADC2_RE3_AN27
    {PE3, hal_ll_adc_module_num(ADC_MODULE_2), {HAL_LL_AD1PCFGH_REG_ADDRESS, 0}, ADC2_RE3, ADC2_RE3_AN27, 0},
    #endif
    #ifdef ADC2_RE4_AN28
    {PE4, hal_ll_adc_module_num(ADC_MODULE_2), {HAL_LL_AD1PCFGH_REG_ADDRESS, 0}, ADC2_RE4, ADC2_RE4_AN28, 0},
    #endif
    #ifdef ADC2_RE5_AN29
    {PE5, hal_ll_adc_module_num(ADC_MODULE_2), {HAL_LL_AD1PCFGH_REG_ADDRESS, 0}, ADC2_RE5, ADC2_RE5_AN29, 0},
    #endif
    #ifdef ADC2_RE6_AN30
    {PE6, hal_ll_adc_module_num(ADC_MODULE_2), {HAL_LL_AD1PCFGH_REG_ADDRESS, 0}, ADC2_RE6, ADC2_RE6_AN30, 0},
    #endif
    #ifdef ADC2_RE7_AN31
    {PE7, hal_ll_adc_module_num(ADC_MODULE_2), {HAL_LL_AD1PCFGH_REG_ADDRESS, 0}, ADC2_RE7, ADC2_RE7_AN31, 0},
    #endif
    #ifdef ADC_RE8_AN20
    {PE8, hal_ll_adc_module_num(ADC_MODULE), {HAL_LL_AD1PCFGH_REG_ADDRESS, 0}, ADC_RE8, ADC_RE8_AN20, 0},
    #endif
    #ifdef ADC_RE9_AN21
    {PE9, hal_ll_adc_module_num(ADC_MODULE), {HAL_LL_AD1PCFGH_REG_ADDRESS, 0}, ADC_RE9, ADC_RE9_AN21, 0},
    #endif
    #ifdef ADC2_RE8_AN20
    {PE8, hal_ll_adc_module_num(ADC_MODULE_2), {HAL_LL_AD1PCFGH_REG_ADDRESS, 0}, ADC2_RE8, ADC2_RE8_AN20, 0},
    #endif
    #ifdef ADC2_RE9_AN21
    {PE9, hal_ll_adc_module_num(ADC_MODULE_2), {HAL_LL_AD1PCFGH_REG_ADDRESS, 0}, ADC2_RE9, ADC2_RE9_AN21, 0},
    #endif
    #ifdef ADC_RA2_AN2
    {PA2, hal_ll_adc_module_num(ADC_MODULE), {HAL_LL_AD1PCFGL_REG_ADDRESS, HAL_LL_AD2PCFGL_REG_ADDRESS}, ADC_RA2, ADC_RA2_AN2, 0},
    #endif
    #ifdef ADC_RB0_AN3
    {PB0, hal_ll_adc_module_num(ADC_MODULE), {HAL_LL_AD1PCFGL_REG_ADDRESS, HAL_LL_AD2PCFGL_REG_ADDRESS}, ADC_RB0, ADC_RB0_AN3, 0},
    #endif
    #ifdef ADC_RB1_AN6
    {PB1, hal_ll_adc_module_num(ADC_MODULE), {HAL_LL_AD1PCFGL_REG_ADDRESS, HAL_LL_AD2PCFGL_REG_ADDRESS}, ADC_RB1, ADC_RB1_AN6, 0},
    #endif
    #ifdef ADC_RB10_AN5
    {PB10, hal_ll_adc_module_num(ADC_MODULE), {HAL_LL_AD1PCFGL_REG_ADDRESS, HAL_LL_AD2PCFGL_REG_ADDRESS}, ADC_RB10, ADC_RB10_AN5, 0},
    #endif
    #ifdef ADC_RB2_AN7
    {PB2, hal_ll_adc_module_num(ADC_MODULE), {HAL_LL_AD1PCFGL_REG_ADDRESS, HAL_LL_AD2PCFGL_REG_ADDRESS}, ADC_RB2, ADC_RB2_AN7, 0},
    #endif
    #ifdef ADC_RB9_AN4
    {PB9, hal_ll_adc_module_num(ADC_MODULE), {HAL_LL_AD1PCFGL_REG_ADDRESS, HAL_LL_AD2PCFGL_REG_ADDRESS}, ADC_RB9, ADC_RB9_AN4, 0},
    #endif
    #ifdef ADC_RC1_AN8
    {PC1, hal_ll_adc_module_num(ADC_MODULE), {HAL_LL_AD1PCFGL_REG_ADDRESS, HAL_LL_AD2PCFGL_REG_ADDRESS}, ADC_RC1, ADC_RC1_AN8, 0},
    #endif
    #ifdef ADC_RC10_AN10
    {PC10, hal_ll_adc_module_num(ADC_MODULE), {HAL_LL_AD1PCFGL_REG_ADDRESS, HAL_LL_AD2PCFGL_REG_ADDRESS}, ADC_RC10, ADC_RC10_AN10, 0},
    #endif
    #ifdef ADC_RC2_AN9
    {PC2, hal_ll_adc_module_num(ADC_MODULE), {HAL_LL_AD1PCFGL_REG_ADDRESS, HAL_LL_AD2PCFGL_REG_ADDRESS}, ADC_RC2, ADC_RC2_AN9, 0},
    #endif
    #ifdef ADC_RC9_AN11
    {PC9, hal_ll_adc_module_num(ADC_MODULE), {HAL_LL_AD1PCFGL_REG_ADDRESS, HAL_LL_AD2PCFGL_REG_ADDRESS}, ADC_RC9, ADC_RC9_AN11, 0},
    #endif
    #ifdef ADC_RA4_AN10
    {PA4, hal_ll_adc_module_num(ADC_MODULE), {HAL_LL_AD1PCFGL_REG_ADDRESS, HAL_LL_AD2PCFGL_REG_ADDRESS}, ADC_RA4, ADC_RA4_AN10, 0},
    #endif
    #ifdef ADC_RB4_AN9
    {PB4, hal_ll_adc_module_num(ADC_MODULE), {HAL_LL_AD1PCFGL_REG_ADDRESS, HAL_LL_AD2PCFGL_REG_ADDRESS}, ADC_RB4, ADC_RB4_AN9, 0},
    #endif
    #ifdef ADC_RC3_AN11
    {PC3, hal_ll_adc_module_num(ADC_MODULE), {HAL_LL_AD1PCFGL_REG_ADDRESS, HAL_LL_AD2PCFGL_REG_ADDRESS}, ADC_RC3, ADC_RC3_AN11, 0},
    #endif
    #ifdef ADC_RC4_AN12
    {PC4, hal_ll_adc_module_num(ADC_MODULE), {HAL_LL_AD1PCFGL_REG_ADDRESS, HAL_LL_AD2PCFGL_REG_ADDRESS}, ADC_RC4, ADC_RC4_AN12, 0},
    #endif
    #ifdef ADC_RC5_AN15
    {PC5, hal_ll_adc_module_num(ADC_MODULE), {HAL_LL_AD1PCFGL_REG_ADDRESS, HAL_LL_AD2PCFGL_REG_ADDRESS}, ADC_RC5, ADC_RC5_AN15, 0},
    #endif
    #ifdef ADC1_RA2_AN13
    {PA2, hal_ll_adc_module_num(ADC_MODULE_1), {HAL_LL_AD1PCFGL_REG_ADDRESS, HAL_LL_AD2PCFGL_REG_ADDRESS}, ADC1_RA2, ADC1_RA2_AN13, 0},
    #endif
    #ifdef ADC1_RA3_AN14
    {PA3, hal_ll_adc_module_num(ADC_MODULE_1), {HAL_LL_AD1PCFGL_REG_ADDRESS, HAL_LL_AD2PCFGL_REG_ADDRESS}, ADC1_RA3, ADC1_RA3_AN14, 0},
    #endif
    #ifdef ADC1_RB13_AN11
    {PB13, hal_ll_adc_module_num(ADC_MODULE_1), {HAL_LL_AD1PCFGL_REG_ADDRESS, HAL_LL_AD2PCFGL_REG_ADDRESS}, ADC1_RB13, ADC1_RB13_AN11, 0},
    #endif
    #ifdef ADC1_RB14_AN10
    {PB14, hal_ll_adc_module_num(ADC_MODULE_1), {HAL_LL_AD1PCFGL_REG_ADDRESS, HAL_LL_AD2PCFGL_REG_ADDRESS}, ADC1_RB14, ADC1_RB14_AN10, 0},
    #endif
    #ifdef ADC1_RB15_AN9
    {PB15, hal_ll_adc_module_num(ADC_MODULE_1), {HAL_LL_AD1PCFGL_REG_ADDRESS, HAL_LL_AD2PCFGL_REG_ADDRESS}, ADC1_RB15, ADC1_RB15_AN9, 0},
    #endif
    #ifdef ADC1_RB4_AN15
    {PB4, hal_ll_adc_module_num(ADC_MODULE_1), {HAL_LL_AD1PCFGL_REG_ADDRESS, HAL_LL_AD2PCFGL_REG_ADDRESS}, ADC1_RB4, ADC1_RB4_AN15, 0},
    #endif
    #ifdef ADC1_RA4_AN16
    {PA4, hal_ll_adc_module_num(ADC_MODULE_1), {HAL_LL_AD1PCFGH_REG_ADDRESS, 0}, ADC1_RA4, ADC1_RA4_AN16, 0},
    #endif
    #ifdef ADC1_RB5_AN17
    {PB5, hal_ll_adc_module_num(ADC_MODULE_1), {HAL_LL_AD1PCFGH_REG_ADDRESS, 0}, ADC1_RB5, ADC1_RB5_AN17, 0},
    #endif
    #ifdef ADC1_RB6_AN18
    {PB6, hal_ll_adc_module_num(ADC_MODULE_1), {HAL_LL_AD1PCFGH_REG_ADDRESS, 0}, ADC1_RB6, ADC1_RB6_AN18, 0},
    #endif
    #ifdef ADC1_RB7_AN19
    {PB7, hal_ll_adc_module_num(ADC_MODULE_1), {HAL_LL_AD1PCFGH_REG_ADDRESS, 0}, ADC1_RB7, ADC1_RB7_AN19, 0},
    #endif
    #ifdef ADC1_RB8_AN20
    {PB8, hal_ll_adc_module_num(ADC_MODULE_1), {HAL_LL_AD1PCFGH_REG_ADDRESS, 0}, ADC1_RB8, ADC1_RB8_AN20, 0},
    #endif
    #ifdef ADC1_RB9_AN21
    {PB9, hal_ll_adc_module_num(ADC_MODULE_1), {HAL_LL_AD1PCFGH_REG_ADDRESS, 0}, ADC1_RB9, ADC1_RB9_AN21, 0},
    #endif
    #ifdef ADC1_RA6_AN23
    {PA6, hal_ll_adc_module_num(ADC_MODULE_1), {HAL_LL_AD1PCFGH_REG_ADDRESS, 0}, ADC1_RA6, ADC1_RA6_AN23, 0},
    #endif
    #ifdef ADC1_RA7_AN22
    {PA7, hal_ll_adc_module_num(ADC_MODULE_1), {HAL_LL_AD1PCFGH_REG_ADDRESS, 0}, ADC1_RA7, ADC1_RA7_AN22, 0},
    #endif
    #ifdef ADC1_RC4_AN16
    {PC4, hal_ll_adc_module_num(ADC_MODULE_1), {HAL_LL_AD1PCFGH_REG_ADDRESS, 0}, ADC1_RC4, ADC1_RC4_AN16, 0},
    #endif
    #ifdef ADC1_RG6_AN17
    {PG6, hal_ll_adc_module_num(ADC_MODULE_1), {HAL_LL_AD1PCFGH_REG_ADDRESS, 0}, ADC1_RG6, ADC1_RG6_AN17, 0},
    #endif
    #ifdef ADC1_RG8_AN19
    {PG8, hal_ll_adc_module_num(ADC_MODULE_1), {HAL_LL_AD1PCFGH_REG_ADDRESS, 0}, ADC1_RG8, ADC1_RG8_AN19, 0},
    #endif
    #ifdef ADC1_RG9_AN20
    {PG9, hal_ll_adc_module_num(ADC_MODULE_1), {HAL_LL_AD1PCFGH_REG_ADDRESS, 0}, ADC1_RG9, ADC1_RG9_AN20, 0},
    #endif
    #ifdef ADC1_RB12_AN8
    {PB12, hal_ll_adc_module_num(ADC_MODULE_1), {HAL_LL_AD1PCFGL_REG_ADDRESS, HAL_LL_AD2PCFGL_REG_ADDRESS}, ADC1_RB12, ADC1_RB12_AN8, 0},
    #endif
    #ifdef ADC1_RB13_AN7
    {PB13, hal_ll_adc_module_num(ADC_MODULE_1), {HAL_LL_AD1PCFGL_REG_ADDRESS, HAL_LL_AD2PCFGL_REG_ADDRESS}, ADC1_RB13, ADC1_RB13_AN7, 0},
    #endif
    #ifdef ADC1_RB14_AN6
    {PB14, hal_ll_adc_module_num(ADC_MODULE_1), {HAL_LL_AD1PCFGL_REG_ADDRESS, HAL_LL_AD2PCFGL_REG_ADDRESS}, ADC1_RB14, ADC1_RB14_AN6, 0},
    #endif
    #ifdef ADC1_RC0_AN10
    {PC0, hal_ll_adc_module_num(ADC_MODULE_1), {HAL_LL_AD1PCFGL_REG_ADDRESS, HAL_LL_AD2PCFGL_REG_ADDRESS}, ADC1_RC0, ADC1_RC0_AN10, 0},
    #endif
    #ifdef ADC1_RC1_AN11
    {PC1, hal_ll_adc_module_num(ADC_MODULE_1), {HAL_LL_AD1PCFGL_REG_ADDRESS, HAL_LL_AD2PCFGL_REG_ADDRESS}, ADC1_RC1, ADC1_RC1_AN11, 0},
    #endif
    #ifdef ADC1_RC2_AN12
    {PC2, hal_ll_adc_module_num(ADC_MODULE_1), {HAL_LL_AD1PCFGL_REG_ADDRESS, HAL_LL_AD2PCFGL_REG_ADDRESS}, ADC1_RC2, ADC1_RC2_AN12, 0},
    #endif
    #ifdef ADC1_RC3_AN13
    {PC3, hal_ll_adc_module_num(ADC_MODULE_1), {HAL_LL_AD1PCFGL_REG_ADDRESS, HAL_LL_AD2PCFGL_REG_ADDRESS}, ADC1_RC3, ADC1_RC3_AN13, 0},
    #endif
    #ifdef ADC1_RD0_AN43
    {PD0, hal_ll_adc_module_num(ADC_MODULE_1), {HAL_LL_AD1PCFGH_REG_ADDRESS, 0}, ADC1_RD0, ADC1_RD0_AN43, 0},
    #endif
    #ifdef ADC1_RD1_AN35
    {PD1, hal_ll_adc_module_num(ADC_MODULE_1), {HAL_LL_AD1PCFGH_REG_ADDRESS, 0}, ADC1_RD1, ADC1_RD1_AN35, 0},
    #endif
    #ifdef ADC1_RD10_AN41
    {PD10, hal_ll_adc_module_num(ADC_MODULE_1), {HAL_LL_AD1PCFGH_REG_ADDRESS, 0}, ADC1_RD10, ADC1_RD10_AN41, 0},
    #endif
    #ifdef ADC1_RD11_AN42
    {PD11, hal_ll_adc_module_num(ADC_MODULE_1), {HAL_LL_AD1PCFGH_REG_ADDRESS, 0}, ADC1_RD11, ADC1_RD11_AN42, 0},
    #endif
    #ifdef ADC1_RD2_AN25
    {PD2, hal_ll_adc_module_num(ADC_MODULE_1), {HAL_LL_AD1PCFGH_REG_ADDRESS, 0}, ADC1_RD2, ADC1_RD2_AN25, 0},
    #endif
    #ifdef ADC1_RD3_AN44
    {PD3, hal_ll_adc_module_num(ADC_MODULE_1), {HAL_LL_AD1PCFGH_REG_ADDRESS, 0}, ADC1_RD3, ADC1_RD3_AN44, 0},
    #endif
    #ifdef ADC1_RD4_AN47
    {PD4, hal_ll_adc_module_num(ADC_MODULE_1), {HAL_LL_AD1PCFGH_REG_ADDRESS, 0}, ADC1_RD4, ADC1_RD4_AN47, 0},
    #endif
    #ifdef ADC1_RD5_AN48
    {PD5, hal_ll_adc_module_num(ADC_MODULE_1), {HAL_LL_AD1PCFGH_REG_ADDRESS, 0}, ADC1_RD5, ADC1_RD5_AN48, 0},
    #endif
    #ifdef ADC1_RD6_AN34
    {PD6, hal_ll_adc_module_num(ADC_MODULE_1), {HAL_LL_AD1PCFGH_REG_ADDRESS, 0}, ADC1_RD6, ADC1_RD6_AN34, 0},
    #endif
    #ifdef ADC1_RD7_AN20
    {PD7, hal_ll_adc_module_num(ADC_MODULE_1), {HAL_LL_AD1PCFGH_REG_ADDRESS, 0}, ADC1_RD7, ADC1_RD7_AN20, 0},
    #endif
    #ifdef ADC1_RD8_AN40
    {PD8, hal_ll_adc_module_num(ADC_MODULE_1), {HAL_LL_AD1PCFGH_REG_ADDRESS, 0}, ADC1_RD8, ADC1_RD8_AN40, 0},
    #endif
    #ifdef ADC1_RD9_AN24
    {PD9, hal_ll_adc_module_num(ADC_MODULE_1), {HAL_LL_AD1PCFGH_REG_ADDRESS, 0}, ADC1_RD9, ADC1_RD9_AN24, 0},
    #endif
    #ifdef ADC1_RF3_AN30
    {PF3, hal_ll_adc_module_num(ADC_MODULE_1), {HAL_LL_AD1PCFGH_REG_ADDRESS, 0}, ADC1_RF3, ADC1_RF3_AN30, 0},
    #endif
    #ifdef ADC1_RF4_AN11
    {PF4, hal_ll_adc_module_num(ADC_MODULE_1), {HAL_LL_AD1PCFGL_REG_ADDRESS, HAL_LL_AD2PCFGL_REG_ADDRESS}, ADC1_RF4, ADC1_RF4_AN11, 0},
    #endif
    #ifdef ADC1_RF5_AN10
    {PF5, hal_ll_adc_module_num(ADC_MODULE_1), {HAL_LL_AD1PCFGL_REG_ADDRESS, HAL_LL_AD2PCFGL_REG_ADDRESS}, ADC1_RF5, ADC1_RF5_AN10, 0},
    #endif
    #ifdef ADC1_RG9_AN49
    {PG9, hal_ll_adc_module_num(ADC_MODULE_1), {HAL_LL_AD1PCFGH_REG_ADDRESS, 0}, ADC1_RG9, ADC1_RG9_AN49, 0},
    #endif
    #ifdef ADC1_RA1_AN26
    {PA1, hal_ll_adc_module_num(ADC_MODULE_1), {HAL_LL_AD1PCFGH_REG_ADDRESS, 0}, ADC1_RA1, ADC1_RA1_AN26, 0},
    #endif
    #ifdef ADC1_RA14_AN38
    {PA14, hal_ll_adc_module_num(ADC_MODULE_1), {HAL_LL_AD1PCFGH_REG_ADDRESS, 0}, ADC1_RA14, ADC1_RA14_AN38, 0},
    #endif
    #ifdef ADC1_RA15_AN39
    {PA15, hal_ll_adc_module_num(ADC_MODULE_1), {HAL_LL_AD1PCFGH_REG_ADDRESS, 0}, ADC1_RA15, ADC1_RA15_AN39, 0},
    #endif
    #ifdef ADC1_RA4_AN36
    {PA4, hal_ll_adc_module_num(ADC_MODULE_1), {HAL_LL_AD1PCFGH_REG_ADDRESS, 0}, ADC1_RA4, ADC1_RA4_AN36, 0},
    #endif
    #ifdef ADC1_RA5_AN37
    {PA5, hal_ll_adc_module_num(ADC_MODULE_1), {HAL_LL_AD1PCFGH_REG_ADDRESS, 0}, ADC1_RA5, ADC1_RA5_AN37, 0},
    #endif
    #ifdef ADC1_RC3_AN9
    {PC3, hal_ll_adc_module_num(ADC_MODULE_1), {HAL_LL_AD1PCFGL_REG_ADDRESS, HAL_LL_AD2PCFGL_REG_ADDRESS}, ADC1_RC3, ADC1_RC3_AN9, 0},
    #endif
    #ifdef ADC1_RD12_AN45
    {PD12, hal_ll_adc_module_num(ADC_MODULE_1), {HAL_LL_AD1PCFGH_REG_ADDRESS, 0}, ADC1_RD12, ADC1_RD12_AN45, 0},
    #endif
    #ifdef ADC1_RD13_AN46
    {PD13, hal_ll_adc_module_num(ADC_MODULE_1), {HAL_LL_AD1PCFGH_REG_ADDRESS, 0}, ADC1_RD13, ADC1_RD13_AN46, 0},
    #endif
    #ifdef ADC1_RD14_AN28
    {PD14, hal_ll_adc_module_num(ADC_MODULE_1), {HAL_LL_AD1PCFGH_REG_ADDRESS, 0}, ADC1_RD14, ADC1_RD14_AN28, 0},
    #endif
    #ifdef ADC1_RD15_AN29
    {PD15, hal_ll_adc_module_num(ADC_MODULE_1), {HAL_LL_AD1PCFGH_REG_ADDRESS, 0}, ADC1_RD15, ADC1_RD15_AN29, 0},
    #endif
    #ifdef ADC1_RF13_AN27
    {PF13, hal_ll_adc_module_num(ADC_MODULE_1), {HAL_LL_AD1PCFGH_REG_ADDRESS, 0}, ADC1_RF13, ADC1_RF13_AN27, 0},
    #endif
    #ifdef ADC1_RF2_AN31
    {PF2, hal_ll_adc_module_num(ADC_MODULE_1), {HAL_LL_AD1PCFGH_REG_ADDRESS, 0}, ADC1_RF2, ADC1_RF2_AN31, 0},
    #endif
    #ifdef ADC1_RF8_AN32
    {PF8, hal_ll_adc_module_num(ADC_MODULE_1), {HAL_LL_AD1PCFGH_REG_ADDRESS, 0}, ADC1_RF8, ADC1_RF8_AN32, 0},
    #endif
    #ifdef ADC1_RG15_AN33
    {PG15, hal_ll_adc_module_num(ADC_MODULE_1), {HAL_LL_AD1PCFGH_REG_ADDRESS, 0}, ADC1_RG15, ADC1_RG15_AN33, 0},
    #endif
    #ifdef ADC1_RC3_AN12
    {PC3, hal_ll_adc_module_num(ADC_MODULE_1), {HAL_LL_AD1PCFGL_REG_ADDRESS, HAL_LL_AD2PCFGL_REG_ADDRESS}, ADC1_RC3, ADC1_RC3_AN12, 0},
    #endif
    #endif
    // EOF list

    // BEGIN ANSEL
    #ifdef _ADC_ANSEL_
    #ifdef ADC_RB0_AN0
    {PB0, hal_ll_adc_module_num(ADC_MODULE), {HAL_LL_ANSELB_REG_ADDRESS, 0}, ADC_RB0, ADC_RB0_AN0, 1},
    #endif
    #ifdef ADC_RB1_AN1
    {PB1, hal_ll_adc_module_num(ADC_MODULE), {HAL_LL_ANSELB_REG_ADDRESS, 0}, ADC_RB1, ADC_RB1_AN1, 1},
    #endif
    #ifdef ADC_RB2_AN2
    {PB2, hal_ll_adc_module_num(ADC_MODULE), {HAL_LL_ANSELB_REG_ADDRESS, 0}, ADC_RB2, ADC_RB2_AN2, 1},
    #endif
    #ifdef ADC_RB3_AN3
    {PB3, hal_ll_adc_module_num(ADC_MODULE), {HAL_LL_ANSELB_REG_ADDRESS, 0}, ADC_RB3, ADC_RB3_AN3, 1},
    #endif
    #ifdef ADC_RB4_AN4
    {PB4, hal_ll_adc_module_num(ADC_MODULE), {HAL_LL_ANSELB_REG_ADDRESS, 0}, ADC_RB4, ADC_RB4_AN4, 1},
    #endif
    #ifdef ADC_RB5_AN5
    {PB5, hal_ll_adc_module_num(ADC_MODULE), {HAL_LL_ANSELB_REG_ADDRESS, 0}, ADC_RB5, ADC_RB5_AN5, 1},
    #endif
    #ifdef ADC_RB6_AN6
    {PB6, hal_ll_adc_module_num(ADC_MODULE), {HAL_LL_ANSELB_REG_ADDRESS, 0}, ADC_RB6, ADC_RB6_AN6, 1},
    #endif
    #ifdef ADC_RB7_AN7
    {PB7, hal_ll_adc_module_num(ADC_MODULE), {HAL_LL_ANSELB_REG_ADDRESS, 0}, ADC_RB7, ADC_RB7_AN7, 1},
    #endif
    #ifdef ADC_RB8_AN8
    {PB8, hal_ll_adc_module_num(ADC_MODULE), {HAL_LL_ANSELB_REG_ADDRESS, 0}, ADC_RB8, ADC_RB8_AN8, 1},
    #endif
    #ifdef ADC_RB9_AN9
    {PB9, hal_ll_adc_module_num(ADC_MODULE), {HAL_LL_ANSELB_REG_ADDRESS, 0}, ADC_RB9, ADC_RB9_AN9, 1},
    #endif
    #ifdef ADC_RB10_AN10
    {PB10, hal_ll_adc_module_num(ADC_MODULE), {HAL_LL_ANSELB_REG_ADDRESS, 0}, ADC_RB10, ADC_RB10_AN10, 1},
    #endif
    #ifdef ADC_RB11_AN11
    {PB11, hal_ll_adc_module_num(ADC_MODULE), {HAL_LL_ANSELB_REG_ADDRESS, 0}, ADC_RB11, ADC_RB11_AN11, 1},
    #endif
    #ifdef ADC_RB12_AN12
    {PB12, hal_ll_adc_module_num(ADC_MODULE), {HAL_LL_ANSELB_REG_ADDRESS, 0}, ADC_RB12, ADC_RB12_AN12, 1},
    #endif
    #ifdef ADC_RB13_AN13
    {PB13, hal_ll_adc_module_num(ADC_MODULE), {HAL_LL_ANSELB_REG_ADDRESS, 0}, ADC_RB13, ADC_RB13_AN13, 1},
    #endif
    #ifdef ADC_RB14_AN14
    {PB14, hal_ll_adc_module_num(ADC_MODULE), {HAL_LL_ANSELB_REG_ADDRESS, 0}, ADC_RB14, ADC_RB14_AN14, 1},
    #endif
    #ifdef ADC_RB15_AN15
    {PB15, hal_ll_adc_module_num(ADC_MODULE), {HAL_LL_ANSELB_REG_ADDRESS, 0}, ADC_RB15, ADC_RB15_AN15, 1},
    #endif
    #ifdef ADC1_RA0_AN0
    {PA0, hal_ll_adc_module_num(ADC_MODULE_1), {HAL_LL_ANSELA_REG_ADDRESS, 0}, ADC1_RA0, ADC1_RA0_AN0, 1},
    #endif
    #ifdef ADC1_RA1_AN1
    {PA1, hal_ll_adc_module_num(ADC_MODULE_1), {HAL_LL_ANSELA_REG_ADDRESS, 0}, ADC1_RA1, ADC1_RA1_AN1, 1},
    #endif
    #ifdef ADC1_RA2_AN32
    {PA2, hal_ll_adc_module_num(ADC_MODULE_1), {HAL_LL_ANSELA_REG_ADDRESS, 0}, ADC1_RA2, ADC1_RA2_AN32, 1},
    #endif
    #ifdef ADC1_RA4_AN24
    {PA4, hal_ll_adc_module_num(ADC_MODULE_1), {HAL_LL_ANSELA_REG_ADDRESS, 0}, ADC1_RA4, ADC1_RA4_AN24, 1},
    #endif
    #ifdef ADC1_RA9_AN28
    {PA9, hal_ll_adc_module_num(ADC_MODULE_1), {HAL_LL_ANSELA_REG_ADDRESS, 0}, ADC1_RA9, ADC1_RA9_AN28, 1},
    #endif
    #ifdef ADC1_RB0_AN2
    {PB0, hal_ll_adc_module_num(ADC_MODULE_1), {HAL_LL_ANSELB_REG_ADDRESS, 0}, ADC1_RB0, ADC1_RB0_AN2, 1},
    #endif
    #ifdef ADC1_RB1_AN3
    {PB1, hal_ll_adc_module_num(ADC_MODULE_1), {HAL_LL_ANSELB_REG_ADDRESS, 0}, ADC1_RB1, ADC1_RB1_AN3, 1},
    #endif
    #ifdef ADC1_RB2_AN4
    {PB2, hal_ll_adc_module_num(ADC_MODULE_1), {HAL_LL_ANSELB_REG_ADDRESS, 0}, ADC1_RB2, ADC1_RB2_AN4, 1},
    #endif
    #ifdef ADC1_RB3_AN5
    {PB3, hal_ll_adc_module_num(ADC_MODULE_1), {HAL_LL_ANSELB_REG_ADDRESS, 0}, ADC1_RB3, ADC1_RB3_AN5, 1},
    #endif
    #ifdef ADC1_RB7_AN25
    {PB7, hal_ll_adc_module_num(ADC_MODULE_1), {HAL_LL_ANSELB_REG_ADDRESS, 0}, ADC1_RB7, ADC1_RB7_AN25, 1},
    #endif
    #ifdef ADC1_RB8_AN26
    {PB8, hal_ll_adc_module_num(ADC_MODULE_1), {HAL_LL_ANSELB_REG_ADDRESS, 0}, ADC1_RB8, ADC1_RB8_AN26, 1},
    #endif
    #ifdef ADC1_RB9_AN27
    {PB9, hal_ll_adc_module_num(ADC_MODULE_1), {HAL_LL_ANSELB_REG_ADDRESS, 0}, ADC1_RB9, ADC1_RB9_AN27, 1},
    #endif
    #ifdef ADC1_RC0_AN6
    {PC0, hal_ll_adc_module_num(ADC_MODULE_1), {HAL_LL_ANSELC_REG_ADDRESS, 0}, ADC1_RC0, ADC1_RC0_AN6, 1},
    #endif
    #ifdef ADC1_RC1_AN7
    {PC1, hal_ll_adc_module_num(ADC_MODULE_1), {HAL_LL_ANSELC_REG_ADDRESS, 0}, ADC1_RC1, ADC1_RC1_AN7, 1},
    #endif
    #ifdef ADC1_RC2_AN8
    {PC2, hal_ll_adc_module_num(ADC_MODULE_1), {HAL_LL_ANSELC_REG_ADDRESS, 0}, ADC1_RC2, ADC1_RC2_AN8, 1},
    #endif
    #ifdef ADC1_RC3_AN29
    {PC3, hal_ll_adc_module_num(ADC_MODULE_1), {HAL_LL_ANSELC_REG_ADDRESS, 0}, ADC1_RC3, ADC1_RC3_AN29, 1},
    #endif
    #ifdef ADC1_RC4_AN30
    {PC4, hal_ll_adc_module_num(ADC_MODULE_1), {HAL_LL_ANSELC_REG_ADDRESS, 0}, ADC1_RC4, ADC1_RC4_AN30, 1},
    #endif
    #ifdef ADC1_RC5_AN31
    {PC5, hal_ll_adc_module_num(ADC_MODULE_1), {HAL_LL_ANSELC_REG_ADDRESS, 0}, ADC1_RC5, ADC1_RC5_AN31, 1},
    #endif
    #ifdef ADC2_RA0_AN0
    {PA0, hal_ll_adc_module_num(ADC_MODULE_2), {HAL_LL_ANSELA_REG_ADDRESS, 0}, ADC2_RA0, ADC2_RA0_AN0, 1},
    #endif
    #ifdef ADC2_RA1_AN1
    {PA1, hal_ll_adc_module_num(ADC_MODULE_2), {HAL_LL_ANSELA_REG_ADDRESS, 0}, ADC2_RA1, ADC2_RA1_AN1, 1},
    #endif
    #ifdef ADC2_RA4_AN24
    {PA4, hal_ll_adc_module_num(ADC_MODULE_2), {HAL_LL_ANSELA_REG_ADDRESS, 0}, ADC2_RA4, ADC2_RA4_AN24, 1},
    #endif
    #ifdef ADC2_RA9_AN28
    {PA9, hal_ll_adc_module_num(ADC_MODULE_2), {HAL_LL_ANSELA_REG_ADDRESS, 0}, ADC2_RA9, ADC2_RA9_AN28, 1},
    #endif
    #ifdef ADC2_RB0_AN2
    {PB0, hal_ll_adc_module_num(ADC_MODULE_2), {HAL_LL_ANSELB_REG_ADDRESS, 0}, ADC2_RB0, ADC2_RB0_AN2, 1},
    #endif
    #ifdef ADC2_RB1_AN3
    {PB1, hal_ll_adc_module_num(ADC_MODULE_2), {HAL_LL_ANSELB_REG_ADDRESS, 0}, ADC2_RB1, ADC2_RB1_AN3, 1},
    #endif
    #ifdef ADC2_RB2_AN4
    {PB2, hal_ll_adc_module_num(ADC_MODULE_2), {HAL_LL_ANSELB_REG_ADDRESS, 0}, ADC2_RB2, ADC2_RB2_AN4, 1},
    #endif
    #ifdef ADC2_RB3_AN5
    {PB3, hal_ll_adc_module_num(ADC_MODULE_2), {HAL_LL_ANSELB_REG_ADDRESS, 0}, ADC2_RB3, ADC2_RB3_AN5, 1},
    #endif
    #ifdef ADC2_RB7_AN25
    {PB7, hal_ll_adc_module_num(ADC_MODULE_2), {HAL_LL_ANSELB_REG_ADDRESS, 0}, ADC2_RB7, ADC2_RB7_AN25, 1},
    #endif
    #ifdef ADC2_RB8_AN26
    {PB8, hal_ll_adc_module_num(ADC_MODULE_2), {HAL_LL_ANSELB_REG_ADDRESS, 0}, ADC2_RB8, ADC2_RB8_AN26, 1},
    #endif
    #ifdef ADC2_RB9_AN27
    {PB9, hal_ll_adc_module_num(ADC_MODULE_2), {HAL_LL_ANSELB_REG_ADDRESS, 0}, ADC2_RB9, ADC2_RB9_AN27, 1},
    #endif
    #ifdef ADC2_RC0_AN6
    {PC0, hal_ll_adc_module_num(ADC_MODULE_2), {HAL_LL_ANSELC_REG_ADDRESS, 0}, ADC2_RC0, ADC2_RC0_AN6, 1},
    #endif
    #ifdef ADC2_RC1_AN7
    {PC1, hal_ll_adc_module_num(ADC_MODULE_2), {HAL_LL_ANSELC_REG_ADDRESS, 0}, ADC2_RC1, ADC2_RC1_AN7, 1},
    #endif
    #ifdef ADC2_RC2_AN8
    {PC2, hal_ll_adc_module_num(ADC_MODULE_2), {HAL_LL_ANSELC_REG_ADDRESS, 0}, ADC2_RC2, ADC2_RC2_AN8, 1},
    #endif
    #ifdef ADC2_RC3_AN29
    {PC3, hal_ll_adc_module_num(ADC_MODULE_2), {HAL_LL_ANSELC_REG_ADDRESS, 0}, ADC2_RC3, ADC2_RC3_AN29, 1},
    #endif
    #ifdef ADC2_RC4_AN30
    {PC4, hal_ll_adc_module_num(ADC_MODULE_2), {HAL_LL_ANSELC_REG_ADDRESS, 0}, ADC2_RC4, ADC2_RC4_AN30, 1},
    #endif
    #ifdef ADC2_RC5_AN31
    {PC5, hal_ll_adc_module_num(ADC_MODULE_2), {HAL_LL_ANSELC_REG_ADDRESS, 0}, ADC2_RC5, ADC2_RC5_AN31, 1},
    #endif
    #ifdef ADC1_RA11_AN9
    {PA11, hal_ll_adc_module_num(ADC_MODULE_1), {HAL_LL_ANSELA_REG_ADDRESS, 0}, ADC1_RA11, ADC1_RA11_AN9, 1},
    #endif
    #ifdef ADC1_RA12_AN10
    {PA12, hal_ll_adc_module_num(ADC_MODULE_1), {HAL_LL_ANSELA_REG_ADDRESS, 0}, ADC1_RA12, ADC1_RA12_AN10, 1},
    #endif
    #ifdef ADC1_RC10_AN48
    {PC10, hal_ll_adc_module_num(ADC_MODULE_1), {HAL_LL_ANSELC_REG_ADDRESS, 0}, ADC1_RC10, ADC1_RC10_AN48, 1},
    #endif
    #ifdef ADC1_RC11_AN11
    {PC11, hal_ll_adc_module_num(ADC_MODULE_1), {HAL_LL_ANSELC_REG_ADDRESS, 0}, ADC1_RC11, ADC1_RC11_AN11, 1},
    #endif
    #ifdef ADC1_RC12_AN49
    {PC12, hal_ll_adc_module_num(ADC_MODULE_1), {HAL_LL_ANSELC_REG_ADDRESS, 0}, ADC1_RC12, ADC1_RC12_AN49, 1},
    #endif
    #ifdef ADC1_RE12_AN12
    {PE12, hal_ll_adc_module_num(ADC_MODULE_1), {HAL_LL_ANSELE_REG_ADDRESS, 0}, ADC1_RE12, ADC1_RE12_AN12, 1},
    #endif
    #ifdef ADC1_RE13_AN13
    {PE13, hal_ll_adc_module_num(ADC_MODULE_1), {HAL_LL_ANSELE_REG_ADDRESS, 0}, ADC1_RE13, ADC1_RE13_AN13, 1},
    #endif
    #ifdef ADC1_RE14_AN14
    {PE14, hal_ll_adc_module_num(ADC_MODULE_1), {HAL_LL_ANSELE_REG_ADDRESS, 0}, ADC1_RE14, ADC1_RE14_AN14, 1},
    #endif
    #ifdef ADC1_RE15_AN15
    {PE15, hal_ll_adc_module_num(ADC_MODULE_1), {HAL_LL_ANSELE_REG_ADDRESS, 0}, ADC1_RE15, ADC1_RE15_AN15, 1},
    #endif
    #ifdef ADC1_RG6_AN19
    {PG6, hal_ll_adc_module_num(ADC_MODULE_1), {HAL_LL_ANSELG_REG_ADDRESS, 0}, ADC1_RG6, ADC1_RG6_AN19, 1},
    #endif
    #ifdef ADC1_RG7_AN18
    {PG7, hal_ll_adc_module_num(ADC_MODULE_1), {HAL_LL_ANSELG_REG_ADDRESS, 0}, ADC1_RG7, ADC1_RG7_AN18, 1},
    #endif
    #ifdef ADC1_RG8_AN17
    {PG8, hal_ll_adc_module_num(ADC_MODULE_1), {HAL_LL_ANSELG_REG_ADDRESS, 0}, ADC1_RG8, ADC1_RG8_AN17, 1},
    #endif
    #ifdef ADC1_RG9_AN16
    {PG9, hal_ll_adc_module_num(ADC_MODULE_1), {HAL_LL_ANSELG_REG_ADDRESS, 0}, ADC1_RG9, ADC1_RG9_AN16, 1},
    #endif
    #ifdef ADC2_RA11_AN9
    {PA11, hal_ll_adc_module_num(ADC_MODULE_2), {HAL_LL_ANSELA_REG_ADDRESS, 0}, ADC2_RA11, ADC2_RA11_AN9, 1},
    #endif
    #ifdef ADC2_RA12_AN10
    {PA12, hal_ll_adc_module_num(ADC_MODULE_2), {HAL_LL_ANSELA_REG_ADDRESS, 0}, ADC2_RA12, ADC2_RA12_AN10, 1},
    #endif
    #ifdef ADC2_RC11_AN11
    {PC11, hal_ll_adc_module_num(ADC_MODULE_2), {HAL_LL_ANSELC_REG_ADDRESS, 0}, ADC2_RC11, ADC2_RC11_AN11, 1},
    #endif
    #ifdef ADC2_RE12_AN12
    {PE12, hal_ll_adc_module_num(ADC_MODULE_2), {HAL_LL_ANSELE_REG_ADDRESS, 0}, ADC2_RE12, ADC2_RE12_AN12, 1},
    #endif
    #ifdef ADC2_RE13_AN13
    {PE13, hal_ll_adc_module_num(ADC_MODULE_2), {HAL_LL_ANSELE_REG_ADDRESS, 0}, ADC2_RE13, ADC2_RE13_AN13, 1},
    #endif
    #ifdef ADC2_RE14_AN14
    {PE14, hal_ll_adc_module_num(ADC_MODULE_2), {HAL_LL_ANSELE_REG_ADDRESS, 0}, ADC2_RE14, ADC2_RE14_AN14, 1},
    #endif
    #ifdef ADC2_RE15_AN15
    {PE15, hal_ll_adc_module_num(ADC_MODULE_2), {HAL_LL_ANSELE_REG_ADDRESS, 0}, ADC2_RE15, ADC2_RE15_AN15, 1},
    #endif
    #ifdef ADC2_RG6_AN19
    {PG6, hal_ll_adc_module_num(ADC_MODULE_2), {HAL_LL_ANSELG_REG_ADDRESS, 0}, ADC2_RG6, ADC2_RG6_AN19, 1},
    #endif
    #ifdef ADC2_RG7_AN18
    {PG7, hal_ll_adc_module_num(ADC_MODULE_2), {HAL_LL_ANSELG_REG_ADDRESS, 0}, ADC2_RG7, ADC2_RG7_AN18, 1},
    #endif
    #ifdef ADC2_RG8_AN17
    {PG8, hal_ll_adc_module_num(ADC_MODULE_2), {HAL_LL_ANSELG_REG_ADDRESS, 0}, ADC2_RG8, ADC2_RG8_AN17, 1},
    #endif
    #ifdef ADC2_RG9_AN16
    {PG9, hal_ll_adc_module_num(ADC_MODULE_2), {HAL_LL_ANSELG_REG_ADDRESS, 0}, ADC2_RG9, ADC2_RG9_AN16, 1},
    #endif
    #ifdef ADC1_RA14_AN46
    {PA14, hal_ll_adc_module_num(ADC_MODULE_1), {HAL_LL_ANSELA_REG_ADDRESS, 0}, ADC1_RA14, ADC1_RA14_AN46, 1},
    #endif
    #ifdef ADC1_RA15_AN47
    {PA15, hal_ll_adc_module_num(ADC_MODULE_1), {HAL_LL_ANSELA_REG_ADDRESS, 0}, ADC1_RA15, ADC1_RA15_AN47, 1},
    #endif
    #ifdef ADC1_RD14_AN38
    {PD14, hal_ll_adc_module_num(ADC_MODULE_1), {HAL_LL_ANSELD_REG_ADDRESS, 0}, ADC1_RD14, ADC1_RD14_AN38, 1},
    #endif
    #ifdef ADC1_RD15_AN39
    {PD15, hal_ll_adc_module_num(ADC_MODULE_1), {HAL_LL_ANSELD_REG_ADDRESS, 0}, ADC1_RD15, ADC1_RD15_AN39, 1},
    #endif
    #ifdef ADC1_RE0_AN40
    {PE0, hal_ll_adc_module_num(ADC_MODULE_1), {HAL_LL_ANSELE_REG_ADDRESS, 0}, ADC1_RE0, ADC1_RE0_AN40, 1},
    #endif
    #ifdef ADC1_RE1_AN41
    {PE1, hal_ll_adc_module_num(ADC_MODULE_1), {HAL_LL_ANSELE_REG_ADDRESS, 0}, ADC1_RE1, ADC1_RE1_AN41, 1},
    #endif
    #ifdef ADC1_RE8_AN21
    {PE8, hal_ll_adc_module_num(ADC_MODULE_1), {HAL_LL_ANSELE_REG_ADDRESS, 0}, ADC1_RE8, ADC1_RE8_AN21, 1},
    #endif
    #ifdef ADC1_RE9_AN20
    {PE9, hal_ll_adc_module_num(ADC_MODULE_1), {HAL_LL_ANSELE_REG_ADDRESS, 0}, ADC1_RE9, ADC1_RE9_AN20, 1},
    #endif
    #ifdef ADC1_RF10_AN34
    {PF10, hal_ll_adc_module_num(ADC_MODULE_1), {HAL_LL_ANSELF_REG_ADDRESS, 0}, ADC1_RF10, ADC1_RF10_AN34, 1},
    #endif
    #ifdef ADC1_RF12_AN37
    {PF12, hal_ll_adc_module_num(ADC_MODULE_1), {HAL_LL_ANSELF_REG_ADDRESS, 0}, ADC1_RF12, ADC1_RF12_AN37, 1},
    #endif
    #ifdef ADC1_RF13_AN36
    {PF13, hal_ll_adc_module_num(ADC_MODULE_1), {HAL_LL_ANSELF_REG_ADDRESS, 0}, ADC1_RF13, ADC1_RF13_AN36, 1},
    #endif
    #ifdef ADC1_RF4_AN44
    {PF4, hal_ll_adc_module_num(ADC_MODULE_1), {HAL_LL_ANSELF_REG_ADDRESS, 0}, ADC1_RF4, ADC1_RF4_AN44, 1},
    #endif
    #ifdef ADC1_RF5_AN45
    {PF5, hal_ll_adc_module_num(ADC_MODULE_1), {HAL_LL_ANSELF_REG_ADDRESS, 0}, ADC1_RF5, ADC1_RF5_AN45, 1},
    #endif
    #ifdef ADC1_RF9_AN33
    {PF9, hal_ll_adc_module_num(ADC_MODULE_1), {HAL_LL_ANSELF_REG_ADDRESS, 0}, ADC1_RF9, ADC1_RF9_AN33, 1},
    #endif
    #ifdef ADC1_RG10_AN22
    {PG10, hal_ll_adc_module_num(ADC_MODULE_1), {HAL_LL_ANSELG_REG_ADDRESS, 0}, ADC1_RG10, ADC1_RG10_AN22, 1},
    #endif
    #ifdef ADC1_RG11_AN35
    {PG11, hal_ll_adc_module_num(ADC_MODULE_1), {HAL_LL_ANSELG_REG_ADDRESS, 0}, ADC1_RG11, ADC1_RG11_AN35, 1},
    #endif
    #ifdef ADC1_RG15_AN23
    {PG15, hal_ll_adc_module_num(ADC_MODULE_1), {HAL_LL_ANSELG_REG_ADDRESS, 0}, ADC1_RG15, ADC1_RG15_AN23, 1},
    #endif
    #ifdef ADC1_RG2_AN42
    {PG2, hal_ll_adc_module_num(ADC_MODULE_1), {HAL_LL_ANSELG_REG_ADDRESS, 0}, ADC1_RG2, ADC1_RG2_AN42, 1},
    #endif
    #ifdef ADC1_RG3_AN43
    {PG3, hal_ll_adc_module_num(ADC_MODULE_1), {HAL_LL_ANSELG_REG_ADDRESS, 0}, ADC1_RG3, ADC1_RG3_AN43, 1},
    #endif
    #ifdef ADC2_RE8_AN21
    {PE8, hal_ll_adc_module_num(ADC_MODULE_2), {HAL_LL_ANSELE_REG_ADDRESS, 0}, ADC2_RE8, ADC2_RE8_AN21, 1},
    #endif
    #ifdef ADC2_RE9_AN20
    {PE9, hal_ll_adc_module_num(ADC_MODULE_2), {HAL_LL_ANSELE_REG_ADDRESS, 0}, ADC2_RE9, ADC2_RE9_AN20, 1},
    #endif
    #ifdef ADC2_RG10_AN22
    {PG10, hal_ll_adc_module_num(ADC_MODULE_2), {HAL_LL_ANSELG_REG_ADDRESS, 0}, ADC2_RG10, ADC2_RG10_AN22, 1},
    #endif
    #ifdef ADC2_RG15_AN23
    {PG15, hal_ll_adc_module_num(ADC_MODULE_2), {HAL_LL_ANSELG_REG_ADDRESS, 0}, ADC2_RG15, ADC2_RG15_AN23, 1},
    #endif
    #ifdef ADC1_RA2_AN2
    {PA2, hal_ll_adc_module_num(ADC_MODULE_1), {HAL_LL_ANSELA_REG_ADDRESS, 0}, ADC1_RA2, ADC1_RA2_AN2, 1},
    #endif
    #ifdef ADC1_RB0_AN3
    {PB0, hal_ll_adc_module_num(ADC_MODULE_1), {HAL_LL_ANSELB_REG_ADDRESS, 0}, ADC1_RB0, ADC1_RB0_AN3, 1},
    #endif
    #ifdef ADC1_RB1_AN6
    {PB1, hal_ll_adc_module_num(ADC_MODULE_1), {HAL_LL_ANSELB_REG_ADDRESS, 0}, ADC1_RB1, ADC1_RB1_AN6, 1},
    #endif
    #ifdef ADC1_RB2_AN7
    {PB2, hal_ll_adc_module_num(ADC_MODULE_1), {HAL_LL_ANSELB_REG_ADDRESS, 0}, ADC1_RB2, ADC1_RB2_AN7, 1},
    #endif
    #ifdef ADC1_RB3_AN18
    {PB3, hal_ll_adc_module_num(ADC_MODULE_1), {HAL_LL_ANSELB_REG_ADDRESS, 0}, ADC1_RB3, ADC1_RB3_AN18, 1},
    #endif
    #ifdef ADC1_RB5_AN19
    {PB5, hal_ll_adc_module_num(ADC_MODULE_1), {HAL_LL_ANSELB_REG_ADDRESS, 0}, ADC1_RB5, ADC1_RB5_AN19, 1},
    #endif
    #ifdef ADC1_RB6_AN20
    {PB6, hal_ll_adc_module_num(ADC_MODULE_1), {HAL_LL_ANSELB_REG_ADDRESS, 0}, ADC1_RB6, ADC1_RB6_AN20, 1},
    #endif
    #ifdef ADC1_RB7_AN21
    {PB7, hal_ll_adc_module_num(ADC_MODULE_1), {HAL_LL_ANSELB_REG_ADDRESS, 0}, ADC1_RB7, ADC1_RB7_AN21, 1},
    #endif
    #ifdef ADC1_RB9_AN4
    {PB9, hal_ll_adc_module_num(ADC_MODULE_1), {HAL_LL_ANSELB_REG_ADDRESS, 0}, ADC1_RB9, ADC1_RB9_AN4, 1},
    #endif
    #ifdef ADC1_RC1_AN8
    {PC1, hal_ll_adc_module_num(ADC_MODULE_1), {HAL_LL_ANSELC_REG_ADDRESS, 0}, ADC1_RC1, ADC1_RC1_AN8, 1},
    #endif
    #ifdef ADC1_RC10_AN10
    {PC10, hal_ll_adc_module_num(ADC_MODULE_1), {HAL_LL_ANSELC_REG_ADDRESS, 0}, ADC1_RC10, ADC1_RC10_AN10, 1},
    #endif
    #ifdef ADC1_RC12_AN14
    {PC12, hal_ll_adc_module_num(ADC_MODULE_1), {HAL_LL_ANSELC_REG_ADDRESS, 0}, ADC1_RC12, ADC1_RC12_AN14, 1},
    #endif
    #ifdef ADC1_RC2_AN9
    {PC2, hal_ll_adc_module_num(ADC_MODULE_1), {HAL_LL_ANSELC_REG_ADDRESS, 0}, ADC1_RC2, ADC1_RC2_AN9, 1},
    #endif
    #ifdef ADC1_RC6_AN17
    {PC6, hal_ll_adc_module_num(ADC_MODULE_1), {HAL_LL_ANSELC_REG_ADDRESS, 0}, ADC1_RC6, ADC1_RC6_AN17, 1},
    #endif
    #ifdef ADC1_RC9_AN11
    {PC9, hal_ll_adc_module_num(ADC_MODULE_1), {HAL_LL_ANSELC_REG_ADDRESS, 0}, ADC1_RC9, ADC1_RC9_AN11, 1},
    #endif
    #ifdef ADC1_RD13_AN13
    {PD13, hal_ll_adc_module_num(ADC_MODULE_1), {HAL_LL_ANSELD_REG_ADDRESS, 0}, ADC1_RD13, ADC1_RD13_AN13, 1},
    #endif
    #ifdef ADC1_RD2_AN16
    {PD2, hal_ll_adc_module_num(ADC_MODULE_1), {HAL_LL_ANSELD_REG_ADDRESS, 0}, ADC1_RD2, ADC1_RD2_AN16, 1},
    #endif
    #ifdef ADC1_RD5_AN12
    {PD5, hal_ll_adc_module_num(ADC_MODULE_1), {HAL_LL_ANSELD_REG_ADDRESS, 0}, ADC1_RD5, ADC1_RD5_AN12, 1},
    #endif
    #ifdef ADC1_RD7_AN15
    {PD7, hal_ll_adc_module_num(ADC_MODULE_1), {HAL_LL_ANSELD_REG_ADDRESS, 0}, ADC1_RD7, ADC1_RD7_AN15, 1},
    #endif
    #ifdef ADC1_RD8_AN5
    {PD8, hal_ll_adc_module_num(ADC_MODULE_1), {HAL_LL_ANSELD_REG_ADDRESS, 0}, ADC1_RD8, ADC1_RD8_AN5, 1},
    #endif
    #ifdef ADC1_RB10_AN5
    {PB10, hal_ll_adc_module_num(ADC_MODULE_1), {HAL_LL_ANSELB_REG_ADDRESS, 0}, ADC1_RB10, ADC1_RB10_AN5, 1},
    #endif
    #ifdef ADC1_RB3_AN8
    {PB3, hal_ll_adc_module_num(ADC_MODULE_1), {HAL_LL_ANSELB_REG_ADDRESS, 0}, ADC1_RB3, ADC1_RB3_AN8, 1},
    #endif
    #ifdef ADC1_RB5_AN9
    {PB5, hal_ll_adc_module_num(ADC_MODULE_1), {HAL_LL_ANSELB_REG_ADDRESS, 0}, ADC1_RB5, ADC1_RB5_AN9, 1},
    #endif
    #ifdef ADC1_RB6_AN10
    {PB6, hal_ll_adc_module_num(ADC_MODULE_1), {HAL_LL_ANSELB_REG_ADDRESS, 0}, ADC1_RB6, ADC1_RB6_AN10, 1},
    #endif
    #ifdef ADC1_RB7_AN11
    {PB7, hal_ll_adc_module_num(ADC_MODULE_1), {HAL_LL_ANSELB_REG_ADDRESS, 0}, ADC1_RB7, ADC1_RB7_AN11, 1},
    #endif
    #ifdef ADC1_RC11_AN12
    {PC11, hal_ll_adc_module_num(ADC_MODULE_1), {HAL_LL_ANSELC_REG_ADDRESS, 0}, ADC1_RC11, ADC1_RC11_AN12, 1},
    #endif
    #ifdef ADC1_RB0_AN0
    {PB0, hal_ll_adc_module_num(ADC_MODULE_1), {HAL_LL_ANSELB_REG_ADDRESS, 0}, ADC1_RB0, ADC1_RB0_AN0, 1},
    #endif
    #ifdef ADC1_RB1_AN1
    {PB1, hal_ll_adc_module_num(ADC_MODULE_1), {HAL_LL_ANSELB_REG_ADDRESS, 0}, ADC1_RB1, ADC1_RB1_AN1, 1},
    #endif
    #ifdef ADC1_RB10_AN10
    {PB10, hal_ll_adc_module_num(ADC_MODULE_1), {HAL_LL_ANSELB_REG_ADDRESS, 0}, ADC1_RB10, ADC1_RB10_AN10, 1},
    #endif
    #ifdef ADC1_RB11_AN11
    {PB11, hal_ll_adc_module_num(ADC_MODULE_1), {HAL_LL_ANSELB_REG_ADDRESS, 0}, ADC1_RB11, ADC1_RB11_AN11, 1},
    #endif
    #ifdef ADC1_RB12_AN12
    {PB12, hal_ll_adc_module_num(ADC_MODULE_1), {HAL_LL_ANSELB_REG_ADDRESS, 0}, ADC1_RB12, ADC1_RB12_AN12, 1},
    #endif
    #ifdef ADC1_RB13_AN13
    {PB13, hal_ll_adc_module_num(ADC_MODULE_1), {HAL_LL_ANSELB_REG_ADDRESS, 0}, ADC1_RB13, ADC1_RB13_AN13, 1},
    #endif
    #ifdef ADC1_RB14_AN14
    {PB14, hal_ll_adc_module_num(ADC_MODULE_1), {HAL_LL_ANSELB_REG_ADDRESS, 0}, ADC1_RB14, ADC1_RB14_AN14, 1},
    #endif
    #ifdef ADC1_RB15_AN15
    {PB15, hal_ll_adc_module_num(ADC_MODULE_1), {HAL_LL_ANSELB_REG_ADDRESS, 0}, ADC1_RB15, ADC1_RB15_AN15, 1},
    #endif
    #ifdef ADC1_RB2_AN2
    {PB2, hal_ll_adc_module_num(ADC_MODULE_1), {HAL_LL_ANSELB_REG_ADDRESS, 0}, ADC1_RB2, ADC1_RB2_AN2, 1},
    #endif
    #ifdef ADC1_RB3_AN3
    {PB3, hal_ll_adc_module_num(ADC_MODULE_1), {HAL_LL_ANSELB_REG_ADDRESS, 0}, ADC1_RB3, ADC1_RB3_AN3, 1},
    #endif
    #ifdef ADC1_RB4_AN4
    {PB4, hal_ll_adc_module_num(ADC_MODULE_1), {HAL_LL_ANSELB_REG_ADDRESS, 0}, ADC1_RB4, ADC1_RB4_AN4, 1},
    #endif
    #ifdef ADC1_RB5_AN5
    {PB5, hal_ll_adc_module_num(ADC_MODULE_1), {HAL_LL_ANSELB_REG_ADDRESS, 0}, ADC1_RB5, ADC1_RB5_AN5, 1},
    #endif
    #ifdef ADC1_RB6_AN6
    {PB6, hal_ll_adc_module_num(ADC_MODULE_1), {HAL_LL_ANSELB_REG_ADDRESS, 0}, ADC1_RB6, ADC1_RB6_AN6, 1},
    #endif
    #ifdef ADC1_RB7_AN7
    {PB7, hal_ll_adc_module_num(ADC_MODULE_1), {HAL_LL_ANSELB_REG_ADDRESS, 0}, ADC1_RB7, ADC1_RB7_AN7, 1},
    #endif
    #ifdef ADC1_RB8_AN8
    {PB8, hal_ll_adc_module_num(ADC_MODULE_1), {HAL_LL_ANSELB_REG_ADDRESS, 0}, ADC1_RB8, ADC1_RB8_AN8, 1},
    #endif
    #ifdef ADC1_RB9_AN9
    {PB9, hal_ll_adc_module_num(ADC_MODULE_1), {HAL_LL_ANSELB_REG_ADDRESS, 0}, ADC1_RB9, ADC1_RB9_AN9, 1},
    #endif
    #ifdef ADC1_RE0_AN24
    {PE0, hal_ll_adc_module_num(ADC_MODULE_1), {HAL_LL_ANSELE_REG_ADDRESS, 0}, ADC1_RE0, ADC1_RE0_AN24, 1},
    #endif
    #ifdef ADC1_RE1_AN25
    {PE1, hal_ll_adc_module_num(ADC_MODULE_1), {HAL_LL_ANSELE_REG_ADDRESS, 0}, ADC1_RE1, ADC1_RE1_AN25, 1},
    #endif
    #ifdef ADC1_RE2_AN26
    {PE2, hal_ll_adc_module_num(ADC_MODULE_1), {HAL_LL_ANSELE_REG_ADDRESS, 0}, ADC1_RE2, ADC1_RE2_AN26, 1},
    #endif
    #ifdef ADC1_RE3_AN27
    {PE3, hal_ll_adc_module_num(ADC_MODULE_1), {HAL_LL_ANSELE_REG_ADDRESS, 0}, ADC1_RE3, ADC1_RE3_AN27, 1},
    #endif
    #ifdef ADC1_RE4_AN28
    {PE4, hal_ll_adc_module_num(ADC_MODULE_1), {HAL_LL_ANSELE_REG_ADDRESS, 0}, ADC1_RE4, ADC1_RE4_AN28, 1},
    #endif
    #ifdef ADC1_RE5_AN29
    {PE5, hal_ll_adc_module_num(ADC_MODULE_1), {HAL_LL_ANSELE_REG_ADDRESS, 0}, ADC1_RE5, ADC1_RE5_AN29, 1},
    #endif
    #ifdef ADC1_RE6_AN30
    {PE6, hal_ll_adc_module_num(ADC_MODULE_1), {HAL_LL_ANSELE_REG_ADDRESS, 0}, ADC1_RE6, ADC1_RE6_AN30, 1},
    #endif
    #ifdef ADC1_RE7_AN31
    {PE7, hal_ll_adc_module_num(ADC_MODULE_1), {HAL_LL_ANSELE_REG_ADDRESS, 0}, ADC1_RE7, ADC1_RE7_AN31, 1},
    #endif
    #ifdef ADC2_RB0_AN0
    {PB0, hal_ll_adc_module_num(ADC_MODULE_2), {HAL_LL_ANSELB_REG_ADDRESS, 0}, ADC2_RB0, ADC2_RB0_AN0, 1},
    #endif
    #ifdef ADC2_RB1_AN1
    {PB1, hal_ll_adc_module_num(ADC_MODULE_2), {HAL_LL_ANSELB_REG_ADDRESS, 0}, ADC2_RB1, ADC2_RB1_AN1, 1},
    #endif
    #ifdef ADC2_RB10_AN10
    {PB10, hal_ll_adc_module_num(ADC_MODULE_2), {HAL_LL_ANSELB_REG_ADDRESS, 0}, ADC2_RB10, ADC2_RB10_AN10, 1},
    #endif
    #ifdef ADC2_RB11_AN11
    {PB11, hal_ll_adc_module_num(ADC_MODULE_2), {HAL_LL_ANSELB_REG_ADDRESS, 0}, ADC2_RB11, ADC2_RB11_AN11, 1},
    #endif
    #ifdef ADC2_RB12_AN12
    {PB12, hal_ll_adc_module_num(ADC_MODULE_2), {HAL_LL_ANSELB_REG_ADDRESS, 0}, ADC2_RB12, ADC2_RB12_AN12, 1},
    #endif
    #ifdef ADC2_RB13_AN13
    {PB13, hal_ll_adc_module_num(ADC_MODULE_2), {HAL_LL_ANSELB_REG_ADDRESS, 0}, ADC2_RB13, ADC2_RB13_AN13, 1},
    #endif
    #ifdef ADC2_RB14_AN14
    {PB14, hal_ll_adc_module_num(ADC_MODULE_2), {HAL_LL_ANSELB_REG_ADDRESS, 0}, ADC2_RB14, ADC2_RB14_AN14, 1},
    #endif
    #ifdef ADC2_RB15_AN15
    {PB15, hal_ll_adc_module_num(ADC_MODULE_2), {HAL_LL_ANSELB_REG_ADDRESS, 0}, ADC2_RB15, ADC2_RB15_AN15, 1},
    #endif
    #ifdef ADC2_RB2_AN2
    {PB2, hal_ll_adc_module_num(ADC_MODULE_2), {HAL_LL_ANSELB_REG_ADDRESS, 0}, ADC2_RB2, ADC2_RB2_AN2, 1},
    #endif
    #ifdef ADC2_RB3_AN3
    {PB3, hal_ll_adc_module_num(ADC_MODULE_2), {HAL_LL_ANSELB_REG_ADDRESS, 0}, ADC2_RB3, ADC2_RB3_AN3, 1},
    #endif
    #ifdef ADC2_RB4_AN4
    {PB4, hal_ll_adc_module_num(ADC_MODULE_2), {HAL_LL_ANSELB_REG_ADDRESS, 0}, ADC2_RB4, ADC2_RB4_AN4, 1},
    #endif
    #ifdef ADC2_RB5_AN5
    {PB5, hal_ll_adc_module_num(ADC_MODULE_2), {HAL_LL_ANSELB_REG_ADDRESS, 0}, ADC2_RB5, ADC2_RB5_AN5, 1},
    #endif
    #ifdef ADC2_RB6_AN6
    {PB6, hal_ll_adc_module_num(ADC_MODULE_2), {HAL_LL_ANSELB_REG_ADDRESS, 0}, ADC2_RB6, ADC2_RB6_AN6, 1},
    #endif
    #ifdef ADC2_RB7_AN7
    {PB7, hal_ll_adc_module_num(ADC_MODULE_2), {HAL_LL_ANSELB_REG_ADDRESS, 0}, ADC2_RB7, ADC2_RB7_AN7, 1},
    #endif
    #ifdef ADC2_RB8_AN8
    {PB8, hal_ll_adc_module_num(ADC_MODULE_2), {HAL_LL_ANSELB_REG_ADDRESS, 0}, ADC2_RB8, ADC2_RB8_AN8, 1},
    #endif
    #ifdef ADC2_RB9_AN9
    {PB9, hal_ll_adc_module_num(ADC_MODULE_2), {HAL_LL_ANSELB_REG_ADDRESS, 0}, ADC2_RB9, ADC2_RB9_AN9, 1},
    #endif
    #ifdef ADC1_RA6_AN22
    {PA6, hal_ll_adc_module_num(ADC_MODULE_1), {HAL_LL_ANSELA_REG_ADDRESS, 0}, ADC1_RA6, ADC1_RA6_AN22, 1},
    #endif
    #ifdef ADC1_RA7_AN23
    {PA7, hal_ll_adc_module_num(ADC_MODULE_1), {HAL_LL_ANSELA_REG_ADDRESS, 0}, ADC1_RA7, ADC1_RA7_AN23, 1},
    #endif
    #ifdef ADC1_RC1_AN16
    {PC1, hal_ll_adc_module_num(ADC_MODULE_1), {HAL_LL_ANSELC_REG_ADDRESS, 0}, ADC1_RC1, ADC1_RC1_AN16, 1},
    #endif
    #ifdef ADC1_RC2_AN17
    {PC2, hal_ll_adc_module_num(ADC_MODULE_1), {HAL_LL_ANSELC_REG_ADDRESS, 0}, ADC1_RC2, ADC1_RC2_AN17, 1},
    #endif
    #ifdef ADC1_RC3_AN18
    {PC3, hal_ll_adc_module_num(ADC_MODULE_1), {HAL_LL_ANSELC_REG_ADDRESS, 0}, ADC1_RC3, ADC1_RC3_AN18, 1},
    #endif
    #ifdef ADC1_RC4_AN19
    {PC4, hal_ll_adc_module_num(ADC_MODULE_1), {HAL_LL_ANSELC_REG_ADDRESS, 0}, ADC1_RC4, ADC1_RC4_AN19, 1},
    #endif
    #ifdef ADC1_RE8_AN20
    {PE8, hal_ll_adc_module_num(ADC_MODULE_1), {HAL_LL_ANSELE_REG_ADDRESS, 0}, ADC1_RE8, ADC1_RE8_AN20, 1},
    #endif
    #ifdef ADC1_RE9_AN21
    {PE9, hal_ll_adc_module_num(ADC_MODULE_1), {HAL_LL_ANSELE_REG_ADDRESS, 0}, ADC1_RE9, ADC1_RE9_AN21, 1},
    #endif
    #ifdef ADC1_RA10_AN56
    {PA10, hal_ll_adc_module_num(ADC_MODULE_1), {HAL_LL_ANSELA_REG_ADDRESS, 0}, ADC1_RA10, ADC1_RA10_AN56, 1},
    #endif
    #ifdef ADC1_RA7_AN55
    {PA7, hal_ll_adc_module_num(ADC_MODULE_1), {HAL_LL_ANSELA_REG_ADDRESS, 0}, ADC1_RA7, ADC1_RA7_AN55, 1},
    #endif
    #ifdef ADC1_RC6_AN53
    {PC6, hal_ll_adc_module_num(ADC_MODULE_1), {HAL_LL_ANSELC_REG_ADDRESS, 0}, ADC1_RC6, ADC1_RC6_AN53, 1},
    #endif
    #ifdef ADC1_RC7_AN52
    {PC7, hal_ll_adc_module_num(ADC_MODULE_1), {HAL_LL_ANSELC_REG_ADDRESS, 0}, ADC1_RC7, ADC1_RC7_AN52, 1},
    #endif
    #ifdef ADC1_RC8_AN51
    {PC8, hal_ll_adc_module_num(ADC_MODULE_1), {HAL_LL_ANSELC_REG_ADDRESS, 0}, ADC1_RC8, ADC1_RC8_AN51, 1},
    #endif
    #ifdef ADC1_RC9_AN54
    {PC9, hal_ll_adc_module_num(ADC_MODULE_1), {HAL_LL_ANSELC_REG_ADDRESS, 0}, ADC1_RC9, ADC1_RC9_AN54, 1},
    #endif
    #ifdef ADC_RA0_AN0
    {PA0, hal_ll_adc_module_num(ADC_MODULE), {HAL_LL_ANSELA_REG_ADDRESS, 0}, ADC_RA0, ADC_RA0_AN0, 1},
    #endif
    #ifdef ADC_RA1_AN1
    {PA1, hal_ll_adc_module_num(ADC_MODULE), {HAL_LL_ANSELA_REG_ADDRESS, 0}, ADC_RA1, ADC_RA1_AN1, 1},
    #endif
    #ifdef ADC_RB0_AN2
    {PB0, hal_ll_adc_module_num(ADC_MODULE), {HAL_LL_ANSELB_REG_ADDRESS, 0}, ADC_RB0, ADC_RB0_AN2, 1},
    #endif
    #ifdef ADC_RB1_AN3
    {PB1, hal_ll_adc_module_num(ADC_MODULE), {HAL_LL_ANSELB_REG_ADDRESS, 0}, ADC_RB1, ADC_RB1_AN3, 1},
    #endif
    #ifdef ADC_RB13_AN11
    {PB13, hal_ll_adc_module_num(ADC_MODULE), {HAL_LL_ANSELB_REG_ADDRESS, 0}, ADC_RB13, ADC_RB13_AN11, 1},
    #endif
    #ifdef ADC_RB14_AN10
    {PB14, hal_ll_adc_module_num(ADC_MODULE), {HAL_LL_ANSELB_REG_ADDRESS, 0}, ADC_RB14, ADC_RB14_AN10, 1},
    #endif
    #ifdef ADC_RB15_AN9
    {PB15, hal_ll_adc_module_num(ADC_MODULE), {HAL_LL_ANSELB_REG_ADDRESS, 0}, ADC_RB15, ADC_RB15_AN9, 1},
    #endif
    #ifdef ADC_RB2_AN4
    {PB2, hal_ll_adc_module_num(ADC_MODULE), {HAL_LL_ANSELB_REG_ADDRESS, 0}, ADC_RB2, ADC_RB2_AN4, 1},
    #endif
    #ifdef ADC_RB3_AN5
    {PB3, hal_ll_adc_module_num(ADC_MODULE), {HAL_LL_ANSELB_REG_ADDRESS, 0}, ADC_RB3, ADC_RB3_AN5, 1},
    #endif
    #ifdef ADC_RC0_AN6
    {PC0, hal_ll_adc_module_num(ADC_MODULE), {HAL_LL_ANSELC_REG_ADDRESS, 0}, ADC_RC0, ADC_RC0_AN6, 1},
    #endif
    #ifdef ADC_RC1_AN7
    {PC1, hal_ll_adc_module_num(ADC_MODULE), {HAL_LL_ANSELC_REG_ADDRESS, 0}, ADC_RC1, ADC_RC1_AN7, 1},
    #endif
    #ifdef ADC_RC2_AN8
    {PC2, hal_ll_adc_module_num(ADC_MODULE), {HAL_LL_ANSELC_REG_ADDRESS, 0}, ADC_RC2, ADC_RC2_AN8, 1},
    #endif
    #ifdef ADC_RC1_AN16
    {PC1, hal_ll_adc_module_num(ADC_MODULE), {HAL_LL_ANSELC_REG_ADDRESS, 0}, ADC_RC1, ADC_RC1_AN16, 1},
    #endif
    #ifdef ADC_RC2_AN17
    {PC2, hal_ll_adc_module_num(ADC_MODULE), {HAL_LL_ANSELC_REG_ADDRESS, 0}, ADC_RC2, ADC_RC2_AN17, 1},
    #endif
    #ifdef ADC_RA12_AN20
    {PA12, hal_ll_adc_module_num(ADC_MODULE), {HAL_LL_ANSELA_REG_ADDRESS, 0}, ADC_RA12, ADC_RA12_AN20, 1},
    #endif
    #ifdef ADC_RA13_AN21
    {PA13, hal_ll_adc_module_num(ADC_MODULE), {HAL_LL_ANSELA_REG_ADDRESS, 0}, ADC_RA13, ADC_RA13_AN21, 1},
    #endif
    #ifdef ADC_RA6_AN22
    {PA6, hal_ll_adc_module_num(ADC_MODULE), {HAL_LL_ANSELA_REG_ADDRESS, 0}, ADC_RA6, ADC_RA6_AN22, 1},
    #endif
    #ifdef ADC_RA7_AN23
    {PA7, hal_ll_adc_module_num(ADC_MODULE), {HAL_LL_ANSELA_REG_ADDRESS, 0}, ADC_RA7, ADC_RA7_AN23, 1},
    #endif
    #ifdef ADC_RC3_AN18
    {PC3, hal_ll_adc_module_num(ADC_MODULE), {HAL_LL_ANSELC_REG_ADDRESS, 0}, ADC_RC3, ADC_RC3_AN18, 1},
    #endif
    #ifdef ADC_RC4_AN19
    {PC4, hal_ll_adc_module_num(ADC_MODULE), {HAL_LL_ANSELC_REG_ADDRESS, 0}, ADC_RC4, ADC_RC4_AN19, 1},
    #endif
    #ifdef ADC_RE0_AN24
    {PE0, hal_ll_adc_module_num(ADC_MODULE), {HAL_LL_ANSELE_REG_ADDRESS, 0}, ADC_RE0, ADC_RE0_AN24, 1},
    #endif
    #ifdef ADC_RE1_AN25
    {PE1, hal_ll_adc_module_num(ADC_MODULE), {HAL_LL_ANSELE_REG_ADDRESS, 0}, ADC_RE1, ADC_RE1_AN25, 1},
    #endif
    #ifdef ADC_RE2_AN26
    {PE2, hal_ll_adc_module_num(ADC_MODULE), {HAL_LL_ANSELE_REG_ADDRESS, 0}, ADC_RE2, ADC_RE2_AN26, 1},
    #endif
    #ifdef ADC_RE3_AN27
    {PE3, hal_ll_adc_module_num(ADC_MODULE), {HAL_LL_ANSELE_REG_ADDRESS, 0}, ADC_RE3, ADC_RE3_AN27, 1},
    #endif
    #ifdef ADC_RE4_AN28
    {PE4, hal_ll_adc_module_num(ADC_MODULE), {HAL_LL_ANSELE_REG_ADDRESS, 0}, ADC_RE4, ADC_RE4_AN28, 1},
    #endif
    #ifdef ADC_RE5_AN29
    {PE5, hal_ll_adc_module_num(ADC_MODULE), {HAL_LL_ANSELE_REG_ADDRESS, 0}, ADC_RE5, ADC_RE5_AN29, 1},
    #endif
    #ifdef ADC_RE6_AN30
    {PE6, hal_ll_adc_module_num(ADC_MODULE), {HAL_LL_ANSELE_REG_ADDRESS, 0}, ADC_RE6, ADC_RE6_AN30, 1},
    #endif
    #ifdef ADC_RE7_AN31
    {PE7, hal_ll_adc_module_num(ADC_MODULE), {HAL_LL_ANSELE_REG_ADDRESS, 0}, ADC_RE7, ADC_RE7_AN31, 1},
    #endif
    #ifdef ADC2_RC1_AN16
    {PC1, hal_ll_adc_module_num(ADC_MODULE_2), {HAL_LL_ANSELC_REG_ADDRESS, 0}, ADC2_RC1, ADC2_RC1_AN16, 1},
    #endif
    #ifdef ADC2_RC2_AN17
    {PC2, hal_ll_adc_module_num(ADC_MODULE_2), {HAL_LL_ANSELC_REG_ADDRESS, 0}, ADC2_RC2, ADC2_RC2_AN17, 1},
    #endif
    #ifdef ADC1_RA12_AN20
    {PA12, hal_ll_adc_module_num(ADC_MODULE_1), {HAL_LL_ANSELA_REG_ADDRESS, 0}, ADC1_RA12, ADC1_RA12_AN20, 1},
    #endif
    #ifdef ADC1_RA13_AN21
    {PA13, hal_ll_adc_module_num(ADC_MODULE_1), {HAL_LL_ANSELA_REG_ADDRESS, 0}, ADC1_RA13, ADC1_RA13_AN21, 1},
    #endif
    #ifdef ADC2_RA12_AN20
    {PA12, hal_ll_adc_module_num(ADC_MODULE_2), {HAL_LL_ANSELA_REG_ADDRESS, 0}, ADC2_RA12, ADC2_RA12_AN20, 1},
    #endif
    #ifdef ADC2_RA13_AN21
    {PA13, hal_ll_adc_module_num(ADC_MODULE_2), {HAL_LL_ANSELA_REG_ADDRESS, 0}, ADC2_RA13, ADC2_RA13_AN21, 1},
    #endif
    #ifdef ADC2_RA6_AN22
    {PA6, hal_ll_adc_module_num(ADC_MODULE_2), {HAL_LL_ANSELA_REG_ADDRESS, 0}, ADC2_RA6, ADC2_RA6_AN22, 1},
    #endif
    #ifdef ADC2_RA7_AN23
    {PA7, hal_ll_adc_module_num(ADC_MODULE_2), {HAL_LL_ANSELA_REG_ADDRESS, 0}, ADC2_RA7, ADC2_RA7_AN23, 1},
    #endif
    #ifdef ADC2_RC3_AN18
    {PC3, hal_ll_adc_module_num(ADC_MODULE_2), {HAL_LL_ANSELC_REG_ADDRESS, 0}, ADC2_RC3, ADC2_RC3_AN18, 1},
    #endif
    #ifdef ADC2_RC4_AN19
    {PC4, hal_ll_adc_module_num(ADC_MODULE_2), {HAL_LL_ANSELC_REG_ADDRESS, 0}, ADC2_RC4, ADC2_RC4_AN19, 1},
    #endif
    #ifdef ADC2_RE0_AN24
    {PE0, hal_ll_adc_module_num(ADC_MODULE_2), {HAL_LL_ANSELE_REG_ADDRESS, 0}, ADC2_RE0, ADC2_RE0_AN24, 1},
    #endif
    #ifdef ADC2_RE1_AN25
    {PE1, hal_ll_adc_module_num(ADC_MODULE_2), {HAL_LL_ANSELE_REG_ADDRESS, 0}, ADC2_RE1, ADC2_RE1_AN25, 1},
    #endif
    #ifdef ADC2_RE2_AN26
    {PE2, hal_ll_adc_module_num(ADC_MODULE_2), {HAL_LL_ANSELE_REG_ADDRESS, 0}, ADC2_RE2, ADC2_RE2_AN26, 1},
    #endif
    #ifdef ADC2_RE3_AN27
    {PE3, hal_ll_adc_module_num(ADC_MODULE_2), {HAL_LL_ANSELE_REG_ADDRESS, 0}, ADC2_RE3, ADC2_RE3_AN27, 1},
    #endif
    #ifdef ADC2_RE4_AN28
    {PE4, hal_ll_adc_module_num(ADC_MODULE_2), {HAL_LL_ANSELE_REG_ADDRESS, 0}, ADC2_RE4, ADC2_RE4_AN28, 1},
    #endif
    #ifdef ADC2_RE5_AN29
    {PE5, hal_ll_adc_module_num(ADC_MODULE_2), {HAL_LL_ANSELE_REG_ADDRESS, 0}, ADC2_RE5, ADC2_RE5_AN29, 1},
    #endif
    #ifdef ADC2_RE6_AN30
    {PE6, hal_ll_adc_module_num(ADC_MODULE_2), {HAL_LL_ANSELE_REG_ADDRESS, 0}, ADC2_RE6, ADC2_RE6_AN30, 1},
    #endif
    #ifdef ADC2_RE7_AN31
    {PE7, hal_ll_adc_module_num(ADC_MODULE_2), {HAL_LL_ANSELE_REG_ADDRESS, 0}, ADC2_RE7, ADC2_RE7_AN31, 1},
    #endif
    #ifdef ADC_RE8_AN20
    {PE8, hal_ll_adc_module_num(ADC_MODULE), {HAL_LL_ANSELE_REG_ADDRESS, 0}, ADC_RE8, ADC_RE8_AN20, 1},
    #endif
    #ifdef ADC_RE9_AN21
    {PE9, hal_ll_adc_module_num(ADC_MODULE), {HAL_LL_ANSELE_REG_ADDRESS, 0}, ADC_RE9, ADC_RE9_AN21, 1},
    #endif
    #ifdef ADC2_RE8_AN20
    {PE8, hal_ll_adc_module_num(ADC_MODULE_2), {HAL_LL_ANSELE_REG_ADDRESS, 0}, ADC2_RE8, ADC2_RE8_AN20, 1},
    #endif
    #ifdef ADC2_RE9_AN21
    {PE9, hal_ll_adc_module_num(ADC_MODULE_2), {HAL_LL_ANSELE_REG_ADDRESS, 0}, ADC2_RE9, ADC2_RE9_AN21, 1},
    #endif
    #ifdef ADC_RA2_AN2
    {PA2, hal_ll_adc_module_num(ADC_MODULE), {HAL_LL_ANSELA_REG_ADDRESS, 0}, ADC_RA2, ADC_RA2_AN2, 1},
    #endif
    #ifdef ADC_RB0_AN3
    {PB0, hal_ll_adc_module_num(ADC_MODULE), {HAL_LL_ANSELB_REG_ADDRESS, 0}, ADC_RB0, ADC_RB0_AN3, 1},
    #endif
    #ifdef ADC_RB1_AN6
    {PB1, hal_ll_adc_module_num(ADC_MODULE), {HAL_LL_ANSELB_REG_ADDRESS, 0}, ADC_RB1, ADC_RB1_AN6, 1},
    #endif
    #ifdef ADC_RB10_AN5
    {PB10, hal_ll_adc_module_num(ADC_MODULE), {HAL_LL_ANSELB_REG_ADDRESS, 0}, ADC_RB10, ADC_RB10_AN5, 1},
    #endif
    #ifdef ADC_RB2_AN7
    {PB2, hal_ll_adc_module_num(ADC_MODULE), {HAL_LL_ANSELB_REG_ADDRESS, 0}, ADC_RB2, ADC_RB2_AN7, 1},
    #endif
    #ifdef ADC_RB9_AN4
    {PB9, hal_ll_adc_module_num(ADC_MODULE), {HAL_LL_ANSELB_REG_ADDRESS, 0}, ADC_RB9, ADC_RB9_AN4, 1},
    #endif
    #ifdef ADC_RC1_AN8
    {PC1, hal_ll_adc_module_num(ADC_MODULE), {HAL_LL_ANSELC_REG_ADDRESS, 0}, ADC_RC1, ADC_RC1_AN8, 1},
    #endif
    #ifdef ADC_RC10_AN10
    {PC10, hal_ll_adc_module_num(ADC_MODULE), {HAL_LL_ANSELC_REG_ADDRESS, 0}, ADC_RC10, ADC_RC10_AN10, 1},
    #endif
    #ifdef ADC_RC2_AN9
    {PC2, hal_ll_adc_module_num(ADC_MODULE), {HAL_LL_ANSELC_REG_ADDRESS, 0}, ADC_RC2, ADC_RC2_AN9, 1},
    #endif
    #ifdef ADC_RC9_AN11
    {PC9, hal_ll_adc_module_num(ADC_MODULE), {HAL_LL_ANSELC_REG_ADDRESS, 0}, ADC_RC9, ADC_RC9_AN11, 1},
    #endif
    #ifdef ADC_RA4_AN10
    {PA4, hal_ll_adc_module_num(ADC_MODULE), {HAL_LL_ANSELA_REG_ADDRESS, 0}, ADC_RA4, ADC_RA4_AN10, 1},
    #endif
    #ifdef ADC_RB4_AN9
    {PB4, hal_ll_adc_module_num(ADC_MODULE), {HAL_LL_ANSELB_REG_ADDRESS, 0}, ADC_RB4, ADC_RB4_AN9, 1},
    #endif
    #ifdef ADC_RC3_AN11
    {PC3, hal_ll_adc_module_num(ADC_MODULE), {HAL_LL_ANSELC_REG_ADDRESS, 0}, ADC_RC3, ADC_RC3_AN11, 1},
    #endif
    #ifdef ADC_RC4_AN12
    {PC4, hal_ll_adc_module_num(ADC_MODULE), {HAL_LL_ANSELC_REG_ADDRESS, 0}, ADC_RC4, ADC_RC4_AN12, 1},
    #endif
    #ifdef ADC_RC5_AN15
    {PC5, hal_ll_adc_module_num(ADC_MODULE), {HAL_LL_ANSELC_REG_ADDRESS, 0}, ADC_RC5, ADC_RC5_AN15, 1},
    #endif
    #ifdef ADC1_RA2_AN13
    {PA2, hal_ll_adc_module_num(ADC_MODULE_1), {HAL_LL_ANSELA_REG_ADDRESS, 0}, ADC1_RA2, ADC1_RA2_AN13, 1},
    #endif
    #ifdef ADC1_RA3_AN14
    {PA3, hal_ll_adc_module_num(ADC_MODULE_1), {HAL_LL_ANSELA_REG_ADDRESS, 0}, ADC1_RA3, ADC1_RA3_AN14, 1},
    #endif
    #ifdef ADC1_RB13_AN11
    {PB13, hal_ll_adc_module_num(ADC_MODULE_1), {HAL_LL_ANSELB_REG_ADDRESS, 0}, ADC1_RB13, ADC1_RB13_AN11, 1},
    #endif
    #ifdef ADC1_RB14_AN10
    {PB14, hal_ll_adc_module_num(ADC_MODULE_1), {HAL_LL_ANSELB_REG_ADDRESS, 0}, ADC1_RB14, ADC1_RB14_AN10, 1},
    #endif
    #ifdef ADC1_RB15_AN9
    {PB15, hal_ll_adc_module_num(ADC_MODULE_1), {HAL_LL_ANSELB_REG_ADDRESS, 0}, ADC1_RB15, ADC1_RB15_AN9, 1},
    #endif
    #ifdef ADC1_RB4_AN15
    {PB4, hal_ll_adc_module_num(ADC_MODULE_1), {HAL_LL_ANSELB_REG_ADDRESS, 0}, ADC1_RB4, ADC1_RB4_AN15, 1},
    #endif
    #ifdef ADC1_RA4_AN16
    {PA4, hal_ll_adc_module_num(ADC_MODULE_1), {HAL_LL_ANSELA_REG_ADDRESS, 0}, ADC1_RA4, ADC1_RA4_AN16, 1},
    #endif
    #ifdef ADC1_RB5_AN17
    {PB5, hal_ll_adc_module_num(ADC_MODULE_1), {HAL_LL_ANSELB_REG_ADDRESS, 0}, ADC1_RB5, ADC1_RB5_AN17, 1},
    #endif
    #ifdef ADC1_RB6_AN18
    {PB6, hal_ll_adc_module_num(ADC_MODULE_1), {HAL_LL_ANSELB_REG_ADDRESS, 0}, ADC1_RB6, ADC1_RB6_AN18, 1},
    #endif
    #ifdef ADC1_RB7_AN19
    {PB7, hal_ll_adc_module_num(ADC_MODULE_1), {HAL_LL_ANSELB_REG_ADDRESS, 0}, ADC1_RB7, ADC1_RB7_AN19, 1},
    #endif
    #ifdef ADC1_RB8_AN20
    {PB8, hal_ll_adc_module_num(ADC_MODULE_1), {HAL_LL_ANSELB_REG_ADDRESS, 0}, ADC1_RB8, ADC1_RB8_AN20, 1},
    #endif
    #ifdef ADC1_RB9_AN21
    {PB9, hal_ll_adc_module_num(ADC_MODULE_1), {HAL_LL_ANSELB_REG_ADDRESS, 0}, ADC1_RB9, ADC1_RB9_AN21, 1},
    #endif
    #ifdef ADC1_RA6_AN23
    {PA6, hal_ll_adc_module_num(ADC_MODULE_1), {HAL_LL_ANSELA_REG_ADDRESS, 0}, ADC1_RA6, ADC1_RA6_AN23, 1},
    #endif
    #ifdef ADC1_RA7_AN22
    {PA7, hal_ll_adc_module_num(ADC_MODULE_1), {HAL_LL_ANSELA_REG_ADDRESS, 0}, ADC1_RA7, ADC1_RA7_AN22, 1},
    #endif
    #ifdef ADC1_RC4_AN16
    {PC4, hal_ll_adc_module_num(ADC_MODULE_1), {HAL_LL_ANSELC_REG_ADDRESS, 0}, ADC1_RC4, ADC1_RC4_AN16, 1},
    #endif
    #ifdef ADC1_RG6_AN17
    {PG6, hal_ll_adc_module_num(ADC_MODULE_1), {HAL_LL_ANSELG_REG_ADDRESS, 0}, ADC1_RG6, ADC1_RG6_AN17, 1},
    #endif
    #ifdef ADC1_RG8_AN19
    {PG8, hal_ll_adc_module_num(ADC_MODULE_1), {HAL_LL_ANSELG_REG_ADDRESS, 0}, ADC1_RG8, ADC1_RG8_AN19, 1},
    #endif
    #ifdef ADC1_RG9_AN20
    {PG9, hal_ll_adc_module_num(ADC_MODULE_1), {HAL_LL_ANSELG_REG_ADDRESS, 0}, ADC1_RG9, ADC1_RG9_AN20, 1},
    #endif
    #ifdef ADC1_RB12_AN8
    {PB12, hal_ll_adc_module_num(ADC_MODULE_1), {HAL_LL_ANSELB_REG_ADDRESS, 0}, ADC1_RB12, ADC1_RB12_AN8, 1},
    #endif
    #ifdef ADC1_RB13_AN7
    {PB13, hal_ll_adc_module_num(ADC_MODULE_1), {HAL_LL_ANSELB_REG_ADDRESS, 0}, ADC1_RB13, ADC1_RB13_AN7, 1},
    #endif
    #ifdef ADC1_RB14_AN6
    {PB14, hal_ll_adc_module_num(ADC_MODULE_1), {HAL_LL_ANSELB_REG_ADDRESS, 0}, ADC1_RB14, ADC1_RB14_AN6, 1},
    #endif
    #ifdef ADC1_RC0_AN10
    {PC0, hal_ll_adc_module_num(ADC_MODULE_1), {HAL_LL_ANSELC_REG_ADDRESS, 0}, ADC1_RC0, ADC1_RC0_AN10, 1},
    #endif
    #ifdef ADC1_RC1_AN11
    {PC1, hal_ll_adc_module_num(ADC_MODULE_1), {HAL_LL_ANSELC_REG_ADDRESS, 0}, ADC1_RC1, ADC1_RC1_AN11, 1},
    #endif
    #ifdef ADC1_RC2_AN12
    {PC2, hal_ll_adc_module_num(ADC_MODULE_1), {HAL_LL_ANSELC_REG_ADDRESS, 0}, ADC1_RC2, ADC1_RC2_AN12, 1},
    #endif
    #ifdef ADC1_RC3_AN13
    {PC3, hal_ll_adc_module_num(ADC_MODULE_1), {HAL_LL_ANSELC_REG_ADDRESS, 0}, ADC1_RC3, ADC1_RC3_AN13, 1},
    #endif
    #ifdef ADC1_RD0_AN43
    {PD0, hal_ll_adc_module_num(ADC_MODULE_1), {HAL_LL_ANSELD_REG_ADDRESS, 0}, ADC1_RD0, ADC1_RD0_AN43, 1},
    #endif
    #ifdef ADC1_RD1_AN35
    {PD1, hal_ll_adc_module_num(ADC_MODULE_1), {HAL_LL_ANSELD_REG_ADDRESS, 0}, ADC1_RD1, ADC1_RD1_AN35, 1},
    #endif
    #ifdef ADC1_RD10_AN41
    {PD10, hal_ll_adc_module_num(ADC_MODULE_1), {HAL_LL_ANSELD_REG_ADDRESS, 0}, ADC1_RD10, ADC1_RD10_AN41, 1},
    #endif
    #ifdef ADC1_RD11_AN42
    {PD11, hal_ll_adc_module_num(ADC_MODULE_1), {HAL_LL_ANSELD_REG_ADDRESS, 0}, ADC1_RD11, ADC1_RD11_AN42, 1},
    #endif
    #ifdef ADC1_RD2_AN25
    {PD2, hal_ll_adc_module_num(ADC_MODULE_1), {HAL_LL_ANSELD_REG_ADDRESS, 0}, ADC1_RD2, ADC1_RD2_AN25, 1},
    #endif
    #ifdef ADC1_RD3_AN44
    {PD3, hal_ll_adc_module_num(ADC_MODULE_1), {HAL_LL_ANSELD_REG_ADDRESS, 0}, ADC1_RD3, ADC1_RD3_AN44, 1},
    #endif
    #ifdef ADC1_RD4_AN47
    {PD4, hal_ll_adc_module_num(ADC_MODULE_1), {HAL_LL_ANSELD_REG_ADDRESS, 0}, ADC1_RD4, ADC1_RD4_AN47, 1},
    #endif
    #ifdef ADC1_RD5_AN48
    {PD5, hal_ll_adc_module_num(ADC_MODULE_1), {HAL_LL_ANSELD_REG_ADDRESS, 0}, ADC1_RD5, ADC1_RD5_AN48, 1},
    #endif
    #ifdef ADC1_RD6_AN34
    {PD6, hal_ll_adc_module_num(ADC_MODULE_1), {HAL_LL_ANSELD_REG_ADDRESS, 0}, ADC1_RD6, ADC1_RD6_AN34, 1},
    #endif
    #ifdef ADC1_RD7_AN20
    {PD7, hal_ll_adc_module_num(ADC_MODULE_1), {HAL_LL_ANSELD_REG_ADDRESS, 0}, ADC1_RD7, ADC1_RD7_AN20, 1},
    #endif
    #ifdef ADC1_RD8_AN40
    {PD8, hal_ll_adc_module_num(ADC_MODULE_1), {HAL_LL_ANSELD_REG_ADDRESS, 0}, ADC1_RD8, ADC1_RD8_AN40, 1},
    #endif
    #ifdef ADC1_RD9_AN24
    {PD9, hal_ll_adc_module_num(ADC_MODULE_1), {HAL_LL_ANSELD_REG_ADDRESS, 0}, ADC1_RD9, ADC1_RD9_AN24, 1},
    #endif
    #ifdef ADC1_RF3_AN30
    {PF3, hal_ll_adc_module_num(ADC_MODULE_1), {HAL_LL_ANSELF_REG_ADDRESS, 0}, ADC1_RF3, ADC1_RF3_AN30, 1},
    #endif
    #ifdef ADC1_RF4_AN11
    {PF4, hal_ll_adc_module_num(ADC_MODULE_1), {HAL_LL_ANSELF_REG_ADDRESS, 0}, ADC1_RF4, ADC1_RF4_AN11, 1},
    #endif
    #ifdef ADC1_RF5_AN10
    {PF5, hal_ll_adc_module_num(ADC_MODULE_1), {HAL_LL_ANSELF_REG_ADDRESS, 0}, ADC1_RF5, ADC1_RF5_AN10, 1},
    #endif
    #ifdef ADC1_RG9_AN49
    {PG9, hal_ll_adc_module_num(ADC_MODULE_1), {HAL_LL_ANSELG_REG_ADDRESS, 0}, ADC1_RG9, ADC1_RG9_AN49, 1},
    #endif
    #ifdef ADC1_RA1_AN26
    {PA1, hal_ll_adc_module_num(ADC_MODULE_1), {HAL_LL_ANSELA_REG_ADDRESS, 0}, ADC1_RA1, ADC1_RA1_AN26, 1},
    #endif
    #ifdef ADC1_RA14_AN38
    {PA14, hal_ll_adc_module_num(ADC_MODULE_1), {HAL_LL_ANSELA_REG_ADDRESS, 0}, ADC1_RA14, ADC1_RA14_AN38, 1},
    #endif
    #ifdef ADC1_RA15_AN39
    {PA15, hal_ll_adc_module_num(ADC_MODULE_1), {HAL_LL_ANSELA_REG_ADDRESS, 0}, ADC1_RA15, ADC1_RA15_AN39, 1},
    #endif
    #ifdef ADC1_RA4_AN36
    {PA4, hal_ll_adc_module_num(ADC_MODULE_1), {HAL_LL_ANSELA_REG_ADDRESS, 0}, ADC1_RA4, ADC1_RA4_AN36, 1},
    #endif
    #ifdef ADC1_RA5_AN37
    {PA5, hal_ll_adc_module_num(ADC_MODULE_1), {HAL_LL_ANSELA_REG_ADDRESS, 0}, ADC1_RA5, ADC1_RA5_AN37, 1},
    #endif
    #ifdef ADC1_RC3_AN9
    {PC3, hal_ll_adc_module_num(ADC_MODULE_1), {HAL_LL_ANSELC_REG_ADDRESS, 0}, ADC1_RC3, ADC1_RC3_AN9, 1},
    #endif
    #ifdef ADC1_RD12_AN45
    {PD12, hal_ll_adc_module_num(ADC_MODULE_1), {HAL_LL_ANSELD_REG_ADDRESS, 0}, ADC1_RD12, ADC1_RD12_AN45, 1},
    #endif
    #ifdef ADC1_RD13_AN46
    {PD13, hal_ll_adc_module_num(ADC_MODULE_1), {HAL_LL_ANSELD_REG_ADDRESS, 0}, ADC1_RD13, ADC1_RD13_AN46, 1},
    #endif
    #ifdef ADC1_RD14_AN28
    {PD14, hal_ll_adc_module_num(ADC_MODULE_1), {HAL_LL_ANSELD_REG_ADDRESS, 0}, ADC1_RD14, ADC1_RD14_AN28, 1},
    #endif
    #ifdef ADC1_RD15_AN29
    {PD15, hal_ll_adc_module_num(ADC_MODULE_1), {HAL_LL_ANSELD_REG_ADDRESS, 0}, ADC1_RD15, ADC1_RD15_AN29, 1},
    #endif
    #ifdef ADC1_RF13_AN27
    {PF13, hal_ll_adc_module_num(ADC_MODULE_1), {HAL_LL_ANSELF_REG_ADDRESS, 0}, ADC1_RF13, ADC1_RF13_AN27, 1},
    #endif
    #ifdef ADC1_RF2_AN31
    {PF2, hal_ll_adc_module_num(ADC_MODULE_1), {HAL_LL_ANSELF_REG_ADDRESS, 0}, ADC1_RF2, ADC1_RF2_AN31, 1},
    #endif
    #ifdef ADC1_RF8_AN32
    {PF8, hal_ll_adc_module_num(ADC_MODULE_1), {HAL_LL_ANSELF_REG_ADDRESS, 0}, ADC1_RF8, ADC1_RF8_AN32, 1},
    #endif
    #ifdef ADC1_RG15_AN33
    {PG15, hal_ll_adc_module_num(ADC_MODULE_1), {HAL_LL_ANSELG_REG_ADDRESS, 0}, ADC1_RG15, ADC1_RG15_AN33, 1},
    #endif
    #ifdef ADC1_RC3_AN12
    {PC3, hal_ll_adc_module_num(ADC_MODULE_1), {HAL_LL_ANSELC_REG_ADDRESS, 0}, ADC1_RC3, ADC1_RC3_AN12, 1},
    #endif
    #endif
    // EOF list

    // BEGIN ANS
    #ifdef _ADC_ANS_
    #ifdef ADC_RB0_AN0
    {PB0, hal_ll_adc_module_num(ADC_MODULE), {HAL_LL_ANSB_REG_ADDRESS, 0}, ADC_RB0, ADC_RB0_AN0, 1},
    #endif
    #ifdef ADC_RB1_AN1
    {PB1, hal_ll_adc_module_num(ADC_MODULE), {HAL_LL_ANSB_REG_ADDRESS, 0}, ADC_RB1, ADC_RB1_AN1, 1},
    #endif
    #ifdef ADC_RB2_AN2
    {PB2, hal_ll_adc_module_num(ADC_MODULE), {HAL_LL_ANSB_REG_ADDRESS, 0}, ADC_RB2, ADC_RB2_AN2, 1},
    #endif
    #ifdef ADC_RB3_AN3
    {PB3, hal_ll_adc_module_num(ADC_MODULE), {HAL_LL_ANSB_REG_ADDRESS, 0}, ADC_RB3, ADC_RB3_AN3, 1},
    #endif
    #ifdef ADC_RB4_AN4
    {PB4, hal_ll_adc_module_num(ADC_MODULE), {HAL_LL_ANSB_REG_ADDRESS, 0}, ADC_RB4, ADC_RB4_AN4, 1},
    #endif
    #ifdef ADC_RB5_AN5
    {PB5, hal_ll_adc_module_num(ADC_MODULE), {HAL_LL_ANSB_REG_ADDRESS, 0}, ADC_RB5, ADC_RB5_AN5, 1},
    #endif
    #ifdef ADC_RB6_AN6
    {PB6, hal_ll_adc_module_num(ADC_MODULE), {HAL_LL_ANSB_REG_ADDRESS, 0}, ADC_RB6, ADC_RB6_AN6, 1},
    #endif
    #ifdef ADC_RB7_AN7
    {PB7, hal_ll_adc_module_num(ADC_MODULE), {HAL_LL_ANSB_REG_ADDRESS, 0}, ADC_RB7, ADC_RB7_AN7, 1},
    #endif
    #ifdef ADC_RB8_AN8
    {PB8, hal_ll_adc_module_num(ADC_MODULE), {HAL_LL_ANSB_REG_ADDRESS, 0}, ADC_RB8, ADC_RB8_AN8, 1},
    #endif
    #ifdef ADC_RB9_AN9
    {PB9, hal_ll_adc_module_num(ADC_MODULE), {HAL_LL_ANSB_REG_ADDRESS, 0}, ADC_RB9, ADC_RB9_AN9, 1},
    #endif
    #ifdef ADC_RB10_AN10
    {PB10, hal_ll_adc_module_num(ADC_MODULE), {HAL_LL_ANSB_REG_ADDRESS, 0}, ADC_RB10, ADC_RB10_AN10, 1},
    #endif
    #ifdef ADC_RB11_AN11
    {PB11, hal_ll_adc_module_num(ADC_MODULE), {HAL_LL_ANSB_REG_ADDRESS, 0}, ADC_RB11, ADC_RB11_AN11, 1},
    #endif
    #ifdef ADC_RB12_AN12
    {PB12, hal_ll_adc_module_num(ADC_MODULE), {HAL_LL_ANSB_REG_ADDRESS, 0}, ADC_RB12, ADC_RB12_AN12, 1},
    #endif
    #ifdef ADC_RB13_AN13
    {PB13, hal_ll_adc_module_num(ADC_MODULE), {HAL_LL_ANSB_REG_ADDRESS, 0}, ADC_RB13, ADC_RB13_AN13, 1},
    #endif
    #ifdef ADC_RB14_AN14
    {PB14, hal_ll_adc_module_num(ADC_MODULE), {HAL_LL_ANSB_REG_ADDRESS, 0}, ADC_RB14, ADC_RB14_AN14, 1},
    #endif
    #ifdef ADC_RB15_AN15
    {PB15, hal_ll_adc_module_num(ADC_MODULE), {HAL_LL_ANSB_REG_ADDRESS, 0}, ADC_RB15, ADC_RB15_AN15, 1},
    #endif
    #ifdef ADC1_RA0_AN0
    {PA0, hal_ll_adc_module_num(ADC_MODULE_1), {HAL_LL_ANSA_REG_ADDRESS, 0}, ADC1_RA0, ADC1_RA0_AN0, 1},
    #endif
    #ifdef ADC1_RA1_AN1
    {PA1, hal_ll_adc_module_num(ADC_MODULE_1), {HAL_LL_ANSA_REG_ADDRESS, 0}, ADC1_RA1, ADC1_RA1_AN1, 1},
    #endif
    #ifdef ADC1_RA2_AN32
    {PA2, hal_ll_adc_module_num(ADC_MODULE_1), {HAL_LL_ANSA_REG_ADDRESS, 0}, ADC1_RA2, ADC1_RA2_AN32, 1},
    #endif
    #ifdef ADC1_RA4_AN24
    {PA4, hal_ll_adc_module_num(ADC_MODULE_1), {HAL_LL_ANSA_REG_ADDRESS, 0}, ADC1_RA4, ADC1_RA4_AN24, 1},
    #endif
    #ifdef ADC1_RA9_AN28
    {PA9, hal_ll_adc_module_num(ADC_MODULE_1), {HAL_LL_ANSA_REG_ADDRESS, 0}, ADC1_RA9, ADC1_RA9_AN28, 1},
    #endif
    #ifdef ADC1_RB0_AN2
    {PB0, hal_ll_adc_module_num(ADC_MODULE_1), {HAL_LL_ANSB_REG_ADDRESS, 0}, ADC1_RB0, ADC1_RB0_AN2, 1},
    #endif
    #ifdef ADC1_RB1_AN3
    {PB1, hal_ll_adc_module_num(ADC_MODULE_1), {HAL_LL_ANSB_REG_ADDRESS, 0}, ADC1_RB1, ADC1_RB1_AN3, 1},
    #endif
    #ifdef ADC1_RB2_AN4
    {PB2, hal_ll_adc_module_num(ADC_MODULE_1), {HAL_LL_ANSB_REG_ADDRESS, 0}, ADC1_RB2, ADC1_RB2_AN4, 1},
    #endif
    #ifdef ADC1_RB3_AN5
    {PB3, hal_ll_adc_module_num(ADC_MODULE_1), {HAL_LL_ANSB_REG_ADDRESS, 0}, ADC1_RB3, ADC1_RB3_AN5, 1},
    #endif
    #ifdef ADC1_RB7_AN25
    {PB7, hal_ll_adc_module_num(ADC_MODULE_1), {HAL_LL_ANSB_REG_ADDRESS, 0}, ADC1_RB7, ADC1_RB7_AN25, 1},
    #endif
    #ifdef ADC1_RB8_AN26
    {PB8, hal_ll_adc_module_num(ADC_MODULE_1), {HAL_LL_ANSB_REG_ADDRESS, 0}, ADC1_RB8, ADC1_RB8_AN26, 1},
    #endif
    #ifdef ADC1_RB9_AN27
    {PB9, hal_ll_adc_module_num(ADC_MODULE_1), {HAL_LL_ANSB_REG_ADDRESS, 0}, ADC1_RB9, ADC1_RB9_AN27, 1},
    #endif
    #ifdef ADC1_RC0_AN6
    {PC0, hal_ll_adc_module_num(ADC_MODULE_1), {HAL_LL_ANSC_REG_ADDRESS, 0}, ADC1_RC0, ADC1_RC0_AN6, 1},
    #endif
    #ifdef ADC1_RC1_AN7
    {PC1, hal_ll_adc_module_num(ADC_MODULE_1), {HAL_LL_ANSC_REG_ADDRESS, 0}, ADC1_RC1, ADC1_RC1_AN7, 1},
    #endif
    #ifdef ADC1_RC2_AN8
    {PC2, hal_ll_adc_module_num(ADC_MODULE_1), {HAL_LL_ANSC_REG_ADDRESS, 0}, ADC1_RC2, ADC1_RC2_AN8, 1},
    #endif
    #ifdef ADC1_RC3_AN29
    {PC3, hal_ll_adc_module_num(ADC_MODULE_1), {HAL_LL_ANSC_REG_ADDRESS, 0}, ADC1_RC3, ADC1_RC3_AN29, 1},
    #endif
    #ifdef ADC1_RC4_AN30
    {PC4, hal_ll_adc_module_num(ADC_MODULE_1), {HAL_LL_ANSC_REG_ADDRESS, 0}, ADC1_RC4, ADC1_RC4_AN30, 1},
    #endif
    #ifdef ADC1_RC5_AN31
    {PC5, hal_ll_adc_module_num(ADC_MODULE_1), {HAL_LL_ANSC_REG_ADDRESS, 0}, ADC1_RC5, ADC1_RC5_AN31, 1},
    #endif
    #ifdef ADC2_RA0_AN0
    {PA0, hal_ll_adc_module_num(ADC_MODULE_2), {HAL_LL_ANSA_REG_ADDRESS, 0}, ADC2_RA0, ADC2_RA0_AN0, 1},
    #endif
    #ifdef ADC2_RA1_AN1
    {PA1, hal_ll_adc_module_num(ADC_MODULE_2), {HAL_LL_ANSA_REG_ADDRESS, 0}, ADC2_RA1, ADC2_RA1_AN1, 1},
    #endif
    #ifdef ADC2_RA4_AN24
    {PA4, hal_ll_adc_module_num(ADC_MODULE_2), {HAL_LL_ANSA_REG_ADDRESS, 0}, ADC2_RA4, ADC2_RA4_AN24, 1},
    #endif
    #ifdef ADC2_RA9_AN28
    {PA9, hal_ll_adc_module_num(ADC_MODULE_2), {HAL_LL_ANSA_REG_ADDRESS, 0}, ADC2_RA9, ADC2_RA9_AN28, 1},
    #endif
    #ifdef ADC2_RB0_AN2
    {PB0, hal_ll_adc_module_num(ADC_MODULE_2), {HAL_LL_ANSB_REG_ADDRESS, 0}, ADC2_RB0, ADC2_RB0_AN2, 1},
    #endif
    #ifdef ADC2_RB1_AN3
    {PB1, hal_ll_adc_module_num(ADC_MODULE_2), {HAL_LL_ANSB_REG_ADDRESS, 0}, ADC2_RB1, ADC2_RB1_AN3, 1},
    #endif
    #ifdef ADC2_RB2_AN4
    {PB2, hal_ll_adc_module_num(ADC_MODULE_2), {HAL_LL_ANSB_REG_ADDRESS, 0}, ADC2_RB2, ADC2_RB2_AN4, 1},
    #endif
    #ifdef ADC2_RB3_AN5
    {PB3, hal_ll_adc_module_num(ADC_MODULE_2), {HAL_LL_ANSB_REG_ADDRESS, 0}, ADC2_RB3, ADC2_RB3_AN5, 1},
    #endif
    #ifdef ADC2_RB7_AN25
    {PB7, hal_ll_adc_module_num(ADC_MODULE_2), {HAL_LL_ANSB_REG_ADDRESS, 0}, ADC2_RB7, ADC2_RB7_AN25, 1},
    #endif
    #ifdef ADC2_RB8_AN26
    {PB8, hal_ll_adc_module_num(ADC_MODULE_2), {HAL_LL_ANSB_REG_ADDRESS, 0}, ADC2_RB8, ADC2_RB8_AN26, 1},
    #endif
    #ifdef ADC2_RB9_AN27
    {PB9, hal_ll_adc_module_num(ADC_MODULE_2), {HAL_LL_ANSB_REG_ADDRESS, 0}, ADC2_RB9, ADC2_RB9_AN27, 1},
    #endif
    #ifdef ADC2_RC0_AN6
    {PC0, hal_ll_adc_module_num(ADC_MODULE_2), {HAL_LL_ANSC_REG_ADDRESS, 0}, ADC2_RC0, ADC2_RC0_AN6, 1},
    #endif
    #ifdef ADC2_RC1_AN7
    {PC1, hal_ll_adc_module_num(ADC_MODULE_2), {HAL_LL_ANSC_REG_ADDRESS, 0}, ADC2_RC1, ADC2_RC1_AN7, 1},
    #endif
    #ifdef ADC2_RC2_AN8
    {PC2, hal_ll_adc_module_num(ADC_MODULE_2), {HAL_LL_ANSC_REG_ADDRESS, 0}, ADC2_RC2, ADC2_RC2_AN8, 1},
    #endif
    #ifdef ADC2_RC3_AN29
    {PC3, hal_ll_adc_module_num(ADC_MODULE_2), {HAL_LL_ANSC_REG_ADDRESS, 0}, ADC2_RC3, ADC2_RC3_AN29, 1},
    #endif
    #ifdef ADC2_RC4_AN30
    {PC4, hal_ll_adc_module_num(ADC_MODULE_2), {HAL_LL_ANSC_REG_ADDRESS, 0}, ADC2_RC4, ADC2_RC4_AN30, 1},
    #endif
    #ifdef ADC2_RC5_AN31
    {PC5, hal_ll_adc_module_num(ADC_MODULE_2), {HAL_LL_ANSC_REG_ADDRESS, 0}, ADC2_RC5, ADC2_RC5_AN31, 1},
    #endif
    #ifdef ADC1_RA11_AN9
    {PA11, hal_ll_adc_module_num(ADC_MODULE_1), {HAL_LL_ANSA_REG_ADDRESS, 0}, ADC1_RA11, ADC1_RA11_AN9, 1},
    #endif
    #ifdef ADC1_RA12_AN10
    {PA12, hal_ll_adc_module_num(ADC_MODULE_1), {HAL_LL_ANSA_REG_ADDRESS, 0}, ADC1_RA12, ADC1_RA12_AN10, 1},
    #endif
    #ifdef ADC1_RC10_AN48
    {PC10, hal_ll_adc_module_num(ADC_MODULE_1), {HAL_LL_ANSC_REG_ADDRESS, 0}, ADC1_RC10, ADC1_RC10_AN48, 1},
    #endif
    #ifdef ADC1_RC11_AN11
    {PC11, hal_ll_adc_module_num(ADC_MODULE_1), {HAL_LL_ANSC_REG_ADDRESS, 0}, ADC1_RC11, ADC1_RC11_AN11, 1},
    #endif
    #ifdef ADC1_RC12_AN49
    {PC12, hal_ll_adc_module_num(ADC_MODULE_1), {HAL_LL_ANSC_REG_ADDRESS, 0}, ADC1_RC12, ADC1_RC12_AN49, 1},
    #endif
    #ifdef ADC1_RE12_AN12
    {PE12, hal_ll_adc_module_num(ADC_MODULE_1), {HAL_LL_ANSE_REG_ADDRESS, 0}, ADC1_RE12, ADC1_RE12_AN12, 1},
    #endif
    #ifdef ADC1_RE13_AN13
    {PE13, hal_ll_adc_module_num(ADC_MODULE_1), {HAL_LL_ANSE_REG_ADDRESS, 0}, ADC1_RE13, ADC1_RE13_AN13, 1},
    #endif
    #ifdef ADC1_RE14_AN14
    {PE14, hal_ll_adc_module_num(ADC_MODULE_1), {HAL_LL_ANSE_REG_ADDRESS, 0}, ADC1_RE14, ADC1_RE14_AN14, 1},
    #endif
    #ifdef ADC1_RE15_AN15
    {PE15, hal_ll_adc_module_num(ADC_MODULE_1), {HAL_LL_ANSE_REG_ADDRESS, 0}, ADC1_RE15, ADC1_RE15_AN15, 1},
    #endif
    #ifdef ADC1_RG6_AN19
    {PG6, hal_ll_adc_module_num(ADC_MODULE_1), {HAL_LL_ANSG_REG_ADDRESS, 0}, ADC1_RG6, ADC1_RG6_AN19, 1},
    #endif
    #ifdef ADC1_RG7_AN18
    {PG7, hal_ll_adc_module_num(ADC_MODULE_1), {HAL_LL_ANSG_REG_ADDRESS, 0}, ADC1_RG7, ADC1_RG7_AN18, 1},
    #endif
    #ifdef ADC1_RG8_AN17
    {PG8, hal_ll_adc_module_num(ADC_MODULE_1), {HAL_LL_ANSG_REG_ADDRESS, 0}, ADC1_RG8, ADC1_RG8_AN17, 1},
    #endif
    #ifdef ADC1_RG9_AN16
    {PG9, hal_ll_adc_module_num(ADC_MODULE_1), {HAL_LL_ANSG_REG_ADDRESS, 0}, ADC1_RG9, ADC1_RG9_AN16, 1},
    #endif
    #ifdef ADC2_RA11_AN9
    {PA11, hal_ll_adc_module_num(ADC_MODULE_2), {HAL_LL_ANSA_REG_ADDRESS, 0}, ADC2_RA11, ADC2_RA11_AN9, 1},
    #endif
    #ifdef ADC2_RA12_AN10
    {PA12, hal_ll_adc_module_num(ADC_MODULE_2), {HAL_LL_ANSA_REG_ADDRESS, 0}, ADC2_RA12, ADC2_RA12_AN10, 1},
    #endif
    #ifdef ADC2_RC11_AN11
    {PC11, hal_ll_adc_module_num(ADC_MODULE_2), {HAL_LL_ANSC_REG_ADDRESS, 0}, ADC2_RC11, ADC2_RC11_AN11, 1},
    #endif
    #ifdef ADC2_RE12_AN12
    {PE12, hal_ll_adc_module_num(ADC_MODULE_2), {HAL_LL_ANSE_REG_ADDRESS, 0}, ADC2_RE12, ADC2_RE12_AN12, 1},
    #endif
    #ifdef ADC2_RE13_AN13
    {PE13, hal_ll_adc_module_num(ADC_MODULE_2), {HAL_LL_ANSE_REG_ADDRESS, 0}, ADC2_RE13, ADC2_RE13_AN13, 1},
    #endif
    #ifdef ADC2_RE14_AN14
    {PE14, hal_ll_adc_module_num(ADC_MODULE_2), {HAL_LL_ANSE_REG_ADDRESS, 0}, ADC2_RE14, ADC2_RE14_AN14, 1},
    #endif
    #ifdef ADC2_RE15_AN15
    {PE15, hal_ll_adc_module_num(ADC_MODULE_2), {HAL_LL_ANSE_REG_ADDRESS, 0}, ADC2_RE15, ADC2_RE15_AN15, 1},
    #endif
    #ifdef ADC2_RG6_AN19
    {PG6, hal_ll_adc_module_num(ADC_MODULE_2), {HAL_LL_ANSG_REG_ADDRESS, 0}, ADC2_RG6, ADC2_RG6_AN19, 1},
    #endif
    #ifdef ADC2_RG7_AN18
    {PG7, hal_ll_adc_module_num(ADC_MODULE_2), {HAL_LL_ANSG_REG_ADDRESS, 0}, ADC2_RG7, ADC2_RG7_AN18, 1},
    #endif
    #ifdef ADC2_RG8_AN17
    {PG8, hal_ll_adc_module_num(ADC_MODULE_2), {HAL_LL_ANSG_REG_ADDRESS, 0}, ADC2_RG8, ADC2_RG8_AN17, 1},
    #endif
    #ifdef ADC2_RG9_AN16
    {PG9, hal_ll_adc_module_num(ADC_MODULE_2), {HAL_LL_ANSG_REG_ADDRESS, 0}, ADC2_RG9, ADC2_RG9_AN16, 1},
    #endif
    #ifdef ADC1_RA14_AN46
    {PA14, hal_ll_adc_module_num(ADC_MODULE_1), {HAL_LL_ANSA_REG_ADDRESS, 0}, ADC1_RA14, ADC1_RA14_AN46, 1},
    #endif
    #ifdef ADC1_RA15_AN47
    {PA15, hal_ll_adc_module_num(ADC_MODULE_1), {HAL_LL_ANSA_REG_ADDRESS, 0}, ADC1_RA15, ADC1_RA15_AN47, 1},
    #endif
    #ifdef ADC1_RD14_AN38
    {PD14, hal_ll_adc_module_num(ADC_MODULE_1), {HAL_LL_ANSD_REG_ADDRESS, 0}, ADC1_RD14, ADC1_RD14_AN38, 1},
    #endif
    #ifdef ADC1_RD15_AN39
    {PD15, hal_ll_adc_module_num(ADC_MODULE_1), {HAL_LL_ANSD_REG_ADDRESS, 0}, ADC1_RD15, ADC1_RD15_AN39, 1},
    #endif
    #ifdef ADC1_RE0_AN40
    {PE0, hal_ll_adc_module_num(ADC_MODULE_1), {HAL_LL_ANSE_REG_ADDRESS, 0}, ADC1_RE0, ADC1_RE0_AN40, 1},
    #endif
    #ifdef ADC1_RE1_AN41
    {PE1, hal_ll_adc_module_num(ADC_MODULE_1), {HAL_LL_ANSE_REG_ADDRESS, 0}, ADC1_RE1, ADC1_RE1_AN41, 1},
    #endif
    #ifdef ADC1_RE8_AN21
    {PE8, hal_ll_adc_module_num(ADC_MODULE_1), {HAL_LL_ANSE_REG_ADDRESS, 0}, ADC1_RE8, ADC1_RE8_AN21, 1},
    #endif
    #ifdef ADC1_RE9_AN20
    {PE9, hal_ll_adc_module_num(ADC_MODULE_1), {HAL_LL_ANSE_REG_ADDRESS, 0}, ADC1_RE9, ADC1_RE9_AN20, 1},
    #endif
    #ifdef ADC1_RF10_AN34
    {PF10, hal_ll_adc_module_num(ADC_MODULE_1), {HAL_LL_ANSF_REG_ADDRESS, 0}, ADC1_RF10, ADC1_RF10_AN34, 1},
    #endif
    #ifdef ADC1_RF12_AN37
    {PF12, hal_ll_adc_module_num(ADC_MODULE_1), {HAL_LL_ANSF_REG_ADDRESS, 0}, ADC1_RF12, ADC1_RF12_AN37, 1},
    #endif
    #ifdef ADC1_RF13_AN36
    {PF13, hal_ll_adc_module_num(ADC_MODULE_1), {HAL_LL_ANSF_REG_ADDRESS, 0}, ADC1_RF13, ADC1_RF13_AN36, 1},
    #endif
    #ifdef ADC1_RF4_AN44
    {PF4, hal_ll_adc_module_num(ADC_MODULE_1), {HAL_LL_ANSF_REG_ADDRESS, 0}, ADC1_RF4, ADC1_RF4_AN44, 1},
    #endif
    #ifdef ADC1_RF5_AN45
    {PF5, hal_ll_adc_module_num(ADC_MODULE_1), {HAL_LL_ANSF_REG_ADDRESS, 0}, ADC1_RF5, ADC1_RF5_AN45, 1},
    #endif
    #ifdef ADC1_RF9_AN33
    {PF9, hal_ll_adc_module_num(ADC_MODULE_1), {HAL_LL_ANSF_REG_ADDRESS, 0}, ADC1_RF9, ADC1_RF9_AN33, 1},
    #endif
    #ifdef ADC1_RG10_AN22
    {PG10, hal_ll_adc_module_num(ADC_MODULE_1), {HAL_LL_ANSG_REG_ADDRESS, 0}, ADC1_RG10, ADC1_RG10_AN22, 1},
    #endif
    #ifdef ADC1_RG11_AN35
    {PG11, hal_ll_adc_module_num(ADC_MODULE_1), {HAL_LL_ANSG_REG_ADDRESS, 0}, ADC1_RG11, ADC1_RG11_AN35, 1},
    #endif
    #ifdef ADC1_RG15_AN23
    {PG15, hal_ll_adc_module_num(ADC_MODULE_1), {HAL_LL_ANSG_REG_ADDRESS, 0}, ADC1_RG15, ADC1_RG15_AN23, 1},
    #endif
    #ifdef ADC1_RG2_AN42
    {PG2, hal_ll_adc_module_num(ADC_MODULE_1), {HAL_LL_ANSG_REG_ADDRESS, 0}, ADC1_RG2, ADC1_RG2_AN42, 1},
    #endif
    #ifdef ADC1_RG3_AN43
    {PG3, hal_ll_adc_module_num(ADC_MODULE_1), {HAL_LL_ANSG_REG_ADDRESS, 0}, ADC1_RG3, ADC1_RG3_AN43, 1},
    #endif
    #ifdef ADC2_RE8_AN21
    {PE8, hal_ll_adc_module_num(ADC_MODULE_2), {HAL_LL_ANSE_REG_ADDRESS, 0}, ADC2_RE8, ADC2_RE8_AN21, 1},
    #endif
    #ifdef ADC2_RE9_AN20
    {PE9, hal_ll_adc_module_num(ADC_MODULE_2), {HAL_LL_ANSE_REG_ADDRESS, 0}, ADC2_RE9, ADC2_RE9_AN20, 1},
    #endif
    #ifdef ADC2_RG10_AN22
    {PG10, hal_ll_adc_module_num(ADC_MODULE_2), {HAL_LL_ANSG_REG_ADDRESS, 0}, ADC2_RG10, ADC2_RG10_AN22, 1},
    #endif
    #ifdef ADC2_RG15_AN23
    {PG15, hal_ll_adc_module_num(ADC_MODULE_2), {HAL_LL_ANSG_REG_ADDRESS, 0}, ADC2_RG15, ADC2_RG15_AN23, 1},
    #endif
    #ifdef ADC1_RA2_AN2
    {PA2, hal_ll_adc_module_num(ADC_MODULE_1), {HAL_LL_ANSA_REG_ADDRESS, 0}, ADC1_RA2, ADC1_RA2_AN2, 1},
    #endif
    #ifdef ADC1_RB0_AN3
    {PB0, hal_ll_adc_module_num(ADC_MODULE_1), {HAL_LL_ANSB_REG_ADDRESS, 0}, ADC1_RB0, ADC1_RB0_AN3, 1},
    #endif
    #ifdef ADC1_RB1_AN6
    {PB1, hal_ll_adc_module_num(ADC_MODULE_1), {HAL_LL_ANSB_REG_ADDRESS, 0}, ADC1_RB1, ADC1_RB1_AN6, 1},
    #endif
    #ifdef ADC1_RB2_AN7
    {PB2, hal_ll_adc_module_num(ADC_MODULE_1), {HAL_LL_ANSB_REG_ADDRESS, 0}, ADC1_RB2, ADC1_RB2_AN7, 1},
    #endif
    #ifdef ADC1_RB3_AN18
    {PB3, hal_ll_adc_module_num(ADC_MODULE_1), {HAL_LL_ANSB_REG_ADDRESS, 0}, ADC1_RB3, ADC1_RB3_AN18, 1},
    #endif
    #ifdef ADC1_RB5_AN19
    {PB5, hal_ll_adc_module_num(ADC_MODULE_1), {HAL_LL_ANSB_REG_ADDRESS, 0}, ADC1_RB5, ADC1_RB5_AN19, 1},
    #endif
    #ifdef ADC1_RB6_AN20
    {PB6, hal_ll_adc_module_num(ADC_MODULE_1), {HAL_LL_ANSB_REG_ADDRESS, 0}, ADC1_RB6, ADC1_RB6_AN20, 1},
    #endif
    #ifdef ADC1_RB7_AN21
    {PB7, hal_ll_adc_module_num(ADC_MODULE_1), {HAL_LL_ANSB_REG_ADDRESS, 0}, ADC1_RB7, ADC1_RB7_AN21, 1},
    #endif
    #ifdef ADC1_RB9_AN4
    {PB9, hal_ll_adc_module_num(ADC_MODULE_1), {HAL_LL_ANSB_REG_ADDRESS, 0}, ADC1_RB9, ADC1_RB9_AN4, 1},
    #endif
    #ifdef ADC1_RC1_AN8
    {PC1, hal_ll_adc_module_num(ADC_MODULE_1), {HAL_LL_ANSC_REG_ADDRESS, 0}, ADC1_RC1, ADC1_RC1_AN8, 1},
    #endif
    #ifdef ADC1_RC10_AN10
    {PC10, hal_ll_adc_module_num(ADC_MODULE_1), {HAL_LL_ANSC_REG_ADDRESS, 0}, ADC1_RC10, ADC1_RC10_AN10, 1},
    #endif
    #ifdef ADC1_RC12_AN14
    {PC12, hal_ll_adc_module_num(ADC_MODULE_1), {HAL_LL_ANSC_REG_ADDRESS, 0}, ADC1_RC12, ADC1_RC12_AN14, 1},
    #endif
    #ifdef ADC1_RC2_AN9
    {PC2, hal_ll_adc_module_num(ADC_MODULE_1), {HAL_LL_ANSC_REG_ADDRESS, 0}, ADC1_RC2, ADC1_RC2_AN9, 1},
    #endif
    #ifdef ADC1_RC6_AN17
    {PC6, hal_ll_adc_module_num(ADC_MODULE_1), {HAL_LL_ANSC_REG_ADDRESS, 0}, ADC1_RC6, ADC1_RC6_AN17, 1},
    #endif
    #ifdef ADC1_RC9_AN11
    {PC9, hal_ll_adc_module_num(ADC_MODULE_1), {HAL_LL_ANSC_REG_ADDRESS, 0}, ADC1_RC9, ADC1_RC9_AN11, 1},
    #endif
    #ifdef ADC1_RD13_AN13
    {PD13, hal_ll_adc_module_num(ADC_MODULE_1), {HAL_LL_ANSD_REG_ADDRESS, 0}, ADC1_RD13, ADC1_RD13_AN13, 1},
    #endif
    #ifdef ADC1_RD2_AN16
    {PD2, hal_ll_adc_module_num(ADC_MODULE_1), {HAL_LL_ANSD_REG_ADDRESS, 0}, ADC1_RD2, ADC1_RD2_AN16, 1},
    #endif
    #ifdef ADC1_RD5_AN12
    {PD5, hal_ll_adc_module_num(ADC_MODULE_1), {HAL_LL_ANSD_REG_ADDRESS, 0}, ADC1_RD5, ADC1_RD5_AN12, 1},
    #endif
    #ifdef ADC1_RD7_AN15
    {PD7, hal_ll_adc_module_num(ADC_MODULE_1), {HAL_LL_ANSD_REG_ADDRESS, 0}, ADC1_RD7, ADC1_RD7_AN15, 1},
    #endif
    #ifdef ADC1_RD8_AN5
    {PD8, hal_ll_adc_module_num(ADC_MODULE_1), {HAL_LL_ANSD_REG_ADDRESS, 0}, ADC1_RD8, ADC1_RD8_AN5, 1},
    #endif
    #ifdef ADC1_RB10_AN5
    {PB10, hal_ll_adc_module_num(ADC_MODULE_1), {HAL_LL_ANSB_REG_ADDRESS, 0}, ADC1_RB10, ADC1_RB10_AN5, 1},
    #endif
    #ifdef ADC1_RB3_AN8
    {PB3, hal_ll_adc_module_num(ADC_MODULE_1), {HAL_LL_ANSB_REG_ADDRESS, 0}, ADC1_RB3, ADC1_RB3_AN8, 1},
    #endif
    #ifdef ADC1_RB5_AN9
    {PB5, hal_ll_adc_module_num(ADC_MODULE_1), {HAL_LL_ANSB_REG_ADDRESS, 0}, ADC1_RB5, ADC1_RB5_AN9, 1},
    #endif
    #ifdef ADC1_RB6_AN10
    {PB6, hal_ll_adc_module_num(ADC_MODULE_1), {HAL_LL_ANSB_REG_ADDRESS, 0}, ADC1_RB6, ADC1_RB6_AN10, 1},
    #endif
    #ifdef ADC1_RB7_AN11
    {PB7, hal_ll_adc_module_num(ADC_MODULE_1), {HAL_LL_ANSB_REG_ADDRESS, 0}, ADC1_RB7, ADC1_RB7_AN11, 1},
    #endif
    #ifdef ADC1_RC11_AN12
    {PC11, hal_ll_adc_module_num(ADC_MODULE_1), {HAL_LL_ANSC_REG_ADDRESS, 0}, ADC1_RC11, ADC1_RC11_AN12, 1},
    #endif
    #ifdef ADC1_RB0_AN0
    {PB0, hal_ll_adc_module_num(ADC_MODULE_1), {HAL_LL_ANSB_REG_ADDRESS, 0}, ADC1_RB0, ADC1_RB0_AN0, 1},
    #endif
    #ifdef ADC1_RB1_AN1
    {PB1, hal_ll_adc_module_num(ADC_MODULE_1), {HAL_LL_ANSB_REG_ADDRESS, 0}, ADC1_RB1, ADC1_RB1_AN1, 1},
    #endif
    #ifdef ADC1_RB10_AN10
    {PB10, hal_ll_adc_module_num(ADC_MODULE_1), {HAL_LL_ANSB_REG_ADDRESS, 0}, ADC1_RB10, ADC1_RB10_AN10, 1},
    #endif
    #ifdef ADC1_RB11_AN11
    {PB11, hal_ll_adc_module_num(ADC_MODULE_1), {HAL_LL_ANSB_REG_ADDRESS, 0}, ADC1_RB11, ADC1_RB11_AN11, 1},
    #endif
    #ifdef ADC1_RB12_AN12
    {PB12, hal_ll_adc_module_num(ADC_MODULE_1), {HAL_LL_ANSB_REG_ADDRESS, 0}, ADC1_RB12, ADC1_RB12_AN12, 1},
    #endif
    #ifdef ADC1_RB13_AN13
    {PB13, hal_ll_adc_module_num(ADC_MODULE_1), {HAL_LL_ANSB_REG_ADDRESS, 0}, ADC1_RB13, ADC1_RB13_AN13, 1},
    #endif
    #ifdef ADC1_RB14_AN14
    {PB14, hal_ll_adc_module_num(ADC_MODULE_1), {HAL_LL_ANSB_REG_ADDRESS, 0}, ADC1_RB14, ADC1_RB14_AN14, 1},
    #endif
    #ifdef ADC1_RB15_AN15
    {PB15, hal_ll_adc_module_num(ADC_MODULE_1), {HAL_LL_ANSB_REG_ADDRESS, 0}, ADC1_RB15, ADC1_RB15_AN15, 1},
    #endif
    #ifdef ADC1_RB2_AN2
    {PB2, hal_ll_adc_module_num(ADC_MODULE_1), {HAL_LL_ANSB_REG_ADDRESS, 0}, ADC1_RB2, ADC1_RB2_AN2, 1},
    #endif
    #ifdef ADC1_RB3_AN3
    {PB3, hal_ll_adc_module_num(ADC_MODULE_1), {HAL_LL_ANSB_REG_ADDRESS, 0}, ADC1_RB3, ADC1_RB3_AN3, 1},
    #endif
    #ifdef ADC1_RB4_AN4
    {PB4, hal_ll_adc_module_num(ADC_MODULE_1), {HAL_LL_ANSB_REG_ADDRESS, 0}, ADC1_RB4, ADC1_RB4_AN4, 1},
    #endif
    #ifdef ADC1_RB5_AN5
    {PB5, hal_ll_adc_module_num(ADC_MODULE_1), {HAL_LL_ANSB_REG_ADDRESS, 0}, ADC1_RB5, ADC1_RB5_AN5, 1},
    #endif
    #ifdef ADC1_RB6_AN6
    {PB6, hal_ll_adc_module_num(ADC_MODULE_1), {HAL_LL_ANSB_REG_ADDRESS, 0}, ADC1_RB6, ADC1_RB6_AN6, 1},
    #endif
    #ifdef ADC1_RB7_AN7
    {PB7, hal_ll_adc_module_num(ADC_MODULE_1), {HAL_LL_ANSB_REG_ADDRESS, 0}, ADC1_RB7, ADC1_RB7_AN7, 1},
    #endif
    #ifdef ADC1_RB8_AN8
    {PB8, hal_ll_adc_module_num(ADC_MODULE_1), {HAL_LL_ANSB_REG_ADDRESS, 0}, ADC1_RB8, ADC1_RB8_AN8, 1},
    #endif
    #ifdef ADC1_RB9_AN9
    {PB9, hal_ll_adc_module_num(ADC_MODULE_1), {HAL_LL_ANSB_REG_ADDRESS, 0}, ADC1_RB9, ADC1_RB9_AN9, 1},
    #endif
    #ifdef ADC1_RE0_AN24
    {PE0, hal_ll_adc_module_num(ADC_MODULE_1), {HAL_LL_ANSE_REG_ADDRESS, 0}, ADC1_RE0, ADC1_RE0_AN24, 1},
    #endif
    #ifdef ADC1_RE1_AN25
    {PE1, hal_ll_adc_module_num(ADC_MODULE_1), {HAL_LL_ANSE_REG_ADDRESS, 0}, ADC1_RE1, ADC1_RE1_AN25, 1},
    #endif
    #ifdef ADC1_RE2_AN26
    {PE2, hal_ll_adc_module_num(ADC_MODULE_1), {HAL_LL_ANSE_REG_ADDRESS, 0}, ADC1_RE2, ADC1_RE2_AN26, 1},
    #endif
    #ifdef ADC1_RE3_AN27
    {PE3, hal_ll_adc_module_num(ADC_MODULE_1), {HAL_LL_ANSE_REG_ADDRESS, 0}, ADC1_RE3, ADC1_RE3_AN27, 1},
    #endif
    #ifdef ADC1_RE4_AN28
    {PE4, hal_ll_adc_module_num(ADC_MODULE_1), {HAL_LL_ANSE_REG_ADDRESS, 0}, ADC1_RE4, ADC1_RE4_AN28, 1},
    #endif
    #ifdef ADC1_RE5_AN29
    {PE5, hal_ll_adc_module_num(ADC_MODULE_1), {HAL_LL_ANSE_REG_ADDRESS, 0}, ADC1_RE5, ADC1_RE5_AN29, 1},
    #endif
    #ifdef ADC1_RE6_AN30
    {PE6, hal_ll_adc_module_num(ADC_MODULE_1), {HAL_LL_ANSE_REG_ADDRESS, 0}, ADC1_RE6, ADC1_RE6_AN30, 1},
    #endif
    #ifdef ADC1_RE7_AN31
    {PE7, hal_ll_adc_module_num(ADC_MODULE_1), {HAL_LL_ANSE_REG_ADDRESS, 0}, ADC1_RE7, ADC1_RE7_AN31, 1},
    #endif
    #ifdef ADC2_RB0_AN0
    {PB0, hal_ll_adc_module_num(ADC_MODULE_2), {HAL_LL_ANSB_REG_ADDRESS, 0}, ADC2_RB0, ADC2_RB0_AN0, 1},
    #endif
    #ifdef ADC2_RB1_AN1
    {PB1, hal_ll_adc_module_num(ADC_MODULE_2), {HAL_LL_ANSB_REG_ADDRESS, 0}, ADC2_RB1, ADC2_RB1_AN1, 1},
    #endif
    #ifdef ADC2_RB10_AN10
    {PB10, hal_ll_adc_module_num(ADC_MODULE_2), {HAL_LL_ANSB_REG_ADDRESS, 0}, ADC2_RB10, ADC2_RB10_AN10, 1},
    #endif
    #ifdef ADC2_RB11_AN11
    {PB11, hal_ll_adc_module_num(ADC_MODULE_2), {HAL_LL_ANSB_REG_ADDRESS, 0}, ADC2_RB11, ADC2_RB11_AN11, 1},
    #endif
    #ifdef ADC2_RB12_AN12
    {PB12, hal_ll_adc_module_num(ADC_MODULE_2), {HAL_LL_ANSB_REG_ADDRESS, 0}, ADC2_RB12, ADC2_RB12_AN12, 1},
    #endif
    #ifdef ADC2_RB13_AN13
    {PB13, hal_ll_adc_module_num(ADC_MODULE_2), {HAL_LL_ANSB_REG_ADDRESS, 0}, ADC2_RB13, ADC2_RB13_AN13, 1},
    #endif
    #ifdef ADC2_RB14_AN14
    {PB14, hal_ll_adc_module_num(ADC_MODULE_2), {HAL_LL_ANSB_REG_ADDRESS, 0}, ADC2_RB14, ADC2_RB14_AN14, 1},
    #endif
    #ifdef ADC2_RB15_AN15
    {PB15, hal_ll_adc_module_num(ADC_MODULE_2), {HAL_LL_ANSB_REG_ADDRESS, 0}, ADC2_RB15, ADC2_RB15_AN15, 1},
    #endif
    #ifdef ADC2_RB2_AN2
    {PB2, hal_ll_adc_module_num(ADC_MODULE_2), {HAL_LL_ANSB_REG_ADDRESS, 0}, ADC2_RB2, ADC2_RB2_AN2, 1},
    #endif
    #ifdef ADC2_RB3_AN3
    {PB3, hal_ll_adc_module_num(ADC_MODULE_2), {HAL_LL_ANSB_REG_ADDRESS, 0}, ADC2_RB3, ADC2_RB3_AN3, 1},
    #endif
    #ifdef ADC2_RB4_AN4
    {PB4, hal_ll_adc_module_num(ADC_MODULE_2), {HAL_LL_ANSB_REG_ADDRESS, 0}, ADC2_RB4, ADC2_RB4_AN4, 1},
    #endif
    #ifdef ADC2_RB5_AN5
    {PB5, hal_ll_adc_module_num(ADC_MODULE_2), {HAL_LL_ANSB_REG_ADDRESS, 0}, ADC2_RB5, ADC2_RB5_AN5, 1},
    #endif
    #ifdef ADC2_RB6_AN6
    {PB6, hal_ll_adc_module_num(ADC_MODULE_2), {HAL_LL_ANSB_REG_ADDRESS, 0}, ADC2_RB6, ADC2_RB6_AN6, 1},
    #endif
    #ifdef ADC2_RB7_AN7
    {PB7, hal_ll_adc_module_num(ADC_MODULE_2), {HAL_LL_ANSB_REG_ADDRESS, 0}, ADC2_RB7, ADC2_RB7_AN7, 1},
    #endif
    #ifdef ADC2_RB8_AN8
    {PB8, hal_ll_adc_module_num(ADC_MODULE_2), {HAL_LL_ANSB_REG_ADDRESS, 0}, ADC2_RB8, ADC2_RB8_AN8, 1},
    #endif
    #ifdef ADC2_RB9_AN9
    {PB9, hal_ll_adc_module_num(ADC_MODULE_2), {HAL_LL_ANSB_REG_ADDRESS, 0}, ADC2_RB9, ADC2_RB9_AN9, 1},
    #endif
    #ifdef ADC1_RA6_AN22
    {PA6, hal_ll_adc_module_num(ADC_MODULE_1), {HAL_LL_ANSA_REG_ADDRESS, 0}, ADC1_RA6, ADC1_RA6_AN22, 1},
    #endif
    #ifdef ADC1_RA7_AN23
    {PA7, hal_ll_adc_module_num(ADC_MODULE_1), {HAL_LL_ANSA_REG_ADDRESS, 0}, ADC1_RA7, ADC1_RA7_AN23, 1},
    #endif
    #ifdef ADC1_RC1_AN16
    {PC1, hal_ll_adc_module_num(ADC_MODULE_1), {HAL_LL_ANSC_REG_ADDRESS, 0}, ADC1_RC1, ADC1_RC1_AN16, 1},
    #endif
    #ifdef ADC1_RC2_AN17
    {PC2, hal_ll_adc_module_num(ADC_MODULE_1), {HAL_LL_ANSC_REG_ADDRESS, 0}, ADC1_RC2, ADC1_RC2_AN17, 1},
    #endif
    #ifdef ADC1_RC3_AN18
    {PC3, hal_ll_adc_module_num(ADC_MODULE_1), {HAL_LL_ANSC_REG_ADDRESS, 0}, ADC1_RC3, ADC1_RC3_AN18, 1},
    #endif
    #ifdef ADC1_RC4_AN19
    {PC4, hal_ll_adc_module_num(ADC_MODULE_1), {HAL_LL_ANSC_REG_ADDRESS, 0}, ADC1_RC4, ADC1_RC4_AN19, 1},
    #endif
    #ifdef ADC1_RE8_AN20
    {PE8, hal_ll_adc_module_num(ADC_MODULE_1), {HAL_LL_ANSE_REG_ADDRESS, 0}, ADC1_RE8, ADC1_RE8_AN20, 1},
    #endif
    #ifdef ADC1_RE9_AN21
    {PE9, hal_ll_adc_module_num(ADC_MODULE_1), {HAL_LL_ANSE_REG_ADDRESS, 0}, ADC1_RE9, ADC1_RE9_AN21, 1},
    #endif
    #ifdef ADC1_RA10_AN56
    {PA10, hal_ll_adc_module_num(ADC_MODULE_1), {HAL_LL_ANSA_REG_ADDRESS, 0}, ADC1_RA10, ADC1_RA10_AN56, 1},
    #endif
    #ifdef ADC1_RA7_AN55
    {PA7, hal_ll_adc_module_num(ADC_MODULE_1), {HAL_LL_ANSA_REG_ADDRESS, 0}, ADC1_RA7, ADC1_RA7_AN55, 1},
    #endif
    #ifdef ADC1_RC6_AN53
    {PC6, hal_ll_adc_module_num(ADC_MODULE_1), {HAL_LL_ANSC_REG_ADDRESS, 0}, ADC1_RC6, ADC1_RC6_AN53, 1},
    #endif
    #ifdef ADC1_RC7_AN52
    {PC7, hal_ll_adc_module_num(ADC_MODULE_1), {HAL_LL_ANSC_REG_ADDRESS, 0}, ADC1_RC7, ADC1_RC7_AN52, 1},
    #endif
    #ifdef ADC1_RC8_AN51
    {PC8, hal_ll_adc_module_num(ADC_MODULE_1), {HAL_LL_ANSC_REG_ADDRESS, 0}, ADC1_RC8, ADC1_RC8_AN51, 1},
    #endif
    #ifdef ADC1_RC9_AN54
    {PC9, hal_ll_adc_module_num(ADC_MODULE_1), {HAL_LL_ANSC_REG_ADDRESS, 0}, ADC1_RC9, ADC1_RC9_AN54, 1},
    #endif
    #ifdef ADC_RA0_AN0
    {PA0, hal_ll_adc_module_num(ADC_MODULE), {HAL_LL_ANSA_REG_ADDRESS, 0}, ADC_RA0, ADC_RA0_AN0, 1},
    #endif
    #ifdef ADC_RA1_AN1
    {PA1, hal_ll_adc_module_num(ADC_MODULE), {HAL_LL_ANSA_REG_ADDRESS, 0}, ADC_RA1, ADC_RA1_AN1, 1},
    #endif
    #ifdef ADC_RB0_AN2
    {PB0, hal_ll_adc_module_num(ADC_MODULE), {HAL_LL_ANSB_REG_ADDRESS, 0}, ADC_RB0, ADC_RB0_AN2, 1},
    #endif
    #ifdef ADC_RB1_AN3
    {PB1, hal_ll_adc_module_num(ADC_MODULE), {HAL_LL_ANSB_REG_ADDRESS, 0}, ADC_RB1, ADC_RB1_AN3, 1},
    #endif
    #ifdef ADC_RB13_AN11
    {PB13, hal_ll_adc_module_num(ADC_MODULE), {HAL_LL_ANSB_REG_ADDRESS, 0}, ADC_RB13, ADC_RB13_AN11, 1},
    #endif
    #ifdef ADC_RB14_AN10
    {PB14, hal_ll_adc_module_num(ADC_MODULE), {HAL_LL_ANSB_REG_ADDRESS, 0}, ADC_RB14, ADC_RB14_AN10, 1},
    #endif
    #ifdef ADC_RB15_AN9
    {PB15, hal_ll_adc_module_num(ADC_MODULE), {HAL_LL_ANSB_REG_ADDRESS, 0}, ADC_RB15, ADC_RB15_AN9, 1},
    #endif
    #ifdef ADC_RB2_AN4
    {PB2, hal_ll_adc_module_num(ADC_MODULE), {HAL_LL_ANSB_REG_ADDRESS, 0}, ADC_RB2, ADC_RB2_AN4, 1},
    #endif
    #ifdef ADC_RB3_AN5
    {PB3, hal_ll_adc_module_num(ADC_MODULE), {HAL_LL_ANSB_REG_ADDRESS, 0}, ADC_RB3, ADC_RB3_AN5, 1},
    #endif
    #ifdef ADC_RC0_AN6
    {PC0, hal_ll_adc_module_num(ADC_MODULE), {HAL_LL_ANSC_REG_ADDRESS, 0}, ADC_RC0, ADC_RC0_AN6, 1},
    #endif
    #ifdef ADC_RC1_AN7
    {PC1, hal_ll_adc_module_num(ADC_MODULE), {HAL_LL_ANSC_REG_ADDRESS, 0}, ADC_RC1, ADC_RC1_AN7, 1},
    #endif
    #ifdef ADC_RC2_AN8
    {PC2, hal_ll_adc_module_num(ADC_MODULE), {HAL_LL_ANSC_REG_ADDRESS, 0}, ADC_RC2, ADC_RC2_AN8, 1},
    #endif
    #ifdef ADC_RC1_AN16
    {PC1, hal_ll_adc_module_num(ADC_MODULE), {HAL_LL_ANSC_REG_ADDRESS, 0}, ADC_RC1, ADC_RC1_AN16, 1},
    #endif
    #ifdef ADC_RC2_AN17
    {PC2, hal_ll_adc_module_num(ADC_MODULE), {HAL_LL_ANSC_REG_ADDRESS, 0}, ADC_RC2, ADC_RC2_AN17, 1},
    #endif
    #ifdef ADC_RA12_AN20
    {PA12, hal_ll_adc_module_num(ADC_MODULE), {HAL_LL_ANSA_REG_ADDRESS, 0}, ADC_RA12, ADC_RA12_AN20, 1},
    #endif
    #ifdef ADC_RA13_AN21
    {PA13, hal_ll_adc_module_num(ADC_MODULE), {HAL_LL_ANSA_REG_ADDRESS, 0}, ADC_RA13, ADC_RA13_AN21, 1},
    #endif
    #ifdef ADC_RA6_AN22
    {PA6, hal_ll_adc_module_num(ADC_MODULE), {HAL_LL_ANSA_REG_ADDRESS, 0}, ADC_RA6, ADC_RA6_AN22, 1},
    #endif
    #ifdef ADC_RA7_AN23
    {PA7, hal_ll_adc_module_num(ADC_MODULE), {HAL_LL_ANSA_REG_ADDRESS, 0}, ADC_RA7, ADC_RA7_AN23, 1},
    #endif
    #ifdef ADC_RC3_AN18
    {PC3, hal_ll_adc_module_num(ADC_MODULE), {HAL_LL_ANSC_REG_ADDRESS, 0}, ADC_RC3, ADC_RC3_AN18, 1},
    #endif
    #ifdef ADC_RC4_AN19
    {PC4, hal_ll_adc_module_num(ADC_MODULE), {HAL_LL_ANSC_REG_ADDRESS, 0}, ADC_RC4, ADC_RC4_AN19, 1},
    #endif
    #ifdef ADC_RE0_AN24
    {PE0, hal_ll_adc_module_num(ADC_MODULE), {HAL_LL_ANSE_REG_ADDRESS, 0}, ADC_RE0, ADC_RE0_AN24, 1},
    #endif
    #ifdef ADC_RE1_AN25
    {PE1, hal_ll_adc_module_num(ADC_MODULE), {HAL_LL_ANSE_REG_ADDRESS, 0}, ADC_RE1, ADC_RE1_AN25, 1},
    #endif
    #ifdef ADC_RE2_AN26
    {PE2, hal_ll_adc_module_num(ADC_MODULE), {HAL_LL_ANSE_REG_ADDRESS, 0}, ADC_RE2, ADC_RE2_AN26, 1},
    #endif
    #ifdef ADC_RE3_AN27
    {PE3, hal_ll_adc_module_num(ADC_MODULE), {HAL_LL_ANSE_REG_ADDRESS, 0}, ADC_RE3, ADC_RE3_AN27, 1},
    #endif
    #ifdef ADC_RE4_AN28
    {PE4, hal_ll_adc_module_num(ADC_MODULE), {HAL_LL_ANSE_REG_ADDRESS, 0}, ADC_RE4, ADC_RE4_AN28, 1},
    #endif
    #ifdef ADC_RE5_AN29
    {PE5, hal_ll_adc_module_num(ADC_MODULE), {HAL_LL_ANSE_REG_ADDRESS, 0}, ADC_RE5, ADC_RE5_AN29, 1},
    #endif
    #ifdef ADC_RE6_AN30
    {PE6, hal_ll_adc_module_num(ADC_MODULE), {HAL_LL_ANSE_REG_ADDRESS, 0}, ADC_RE6, ADC_RE6_AN30, 1},
    #endif
    #ifdef ADC_RE7_AN31
    {PE7, hal_ll_adc_module_num(ADC_MODULE), {HAL_LL_ANSE_REG_ADDRESS, 0}, ADC_RE7, ADC_RE7_AN31, 1},
    #endif
    #ifdef ADC2_RC1_AN16
    {PC1, hal_ll_adc_module_num(ADC_MODULE_2), {HAL_LL_ANSC_REG_ADDRESS, 0}, ADC2_RC1, ADC2_RC1_AN16, 1},
    #endif
    #ifdef ADC2_RC2_AN17
    {PC2, hal_ll_adc_module_num(ADC_MODULE_2), {HAL_LL_ANSC_REG_ADDRESS, 0}, ADC2_RC2, ADC2_RC2_AN17, 1},
    #endif
    #ifdef ADC1_RA12_AN20
    {PA12, hal_ll_adc_module_num(ADC_MODULE_1), {HAL_LL_ANSA_REG_ADDRESS, 0}, ADC1_RA12, ADC1_RA12_AN20, 1},
    #endif
    #ifdef ADC1_RA13_AN21
    {PA13, hal_ll_adc_module_num(ADC_MODULE_1), {HAL_LL_ANSA_REG_ADDRESS, 0}, ADC1_RA13, ADC1_RA13_AN21, 1},
    #endif
    #ifdef ADC2_RA12_AN20
    {PA12, hal_ll_adc_module_num(ADC_MODULE_2), {HAL_LL_ANSA_REG_ADDRESS, 0}, ADC2_RA12, ADC2_RA12_AN20, 1},
    #endif
    #ifdef ADC2_RA13_AN21
    {PA13, hal_ll_adc_module_num(ADC_MODULE_2), {HAL_LL_ANSA_REG_ADDRESS, 0}, ADC2_RA13, ADC2_RA13_AN21, 1},
    #endif
    #ifdef ADC2_RA6_AN22
    {PA6, hal_ll_adc_module_num(ADC_MODULE_2), {HAL_LL_ANSA_REG_ADDRESS, 0}, ADC2_RA6, ADC2_RA6_AN22, 1},
    #endif
    #ifdef ADC2_RA7_AN23
    {PA7, hal_ll_adc_module_num(ADC_MODULE_2), {HAL_LL_ANSA_REG_ADDRESS, 0}, ADC2_RA7, ADC2_RA7_AN23, 1},
    #endif
    #ifdef ADC2_RC3_AN18
    {PC3, hal_ll_adc_module_num(ADC_MODULE_2), {HAL_LL_ANSC_REG_ADDRESS, 0}, ADC2_RC3, ADC2_RC3_AN18, 1},
    #endif
    #ifdef ADC2_RC4_AN19
    {PC4, hal_ll_adc_module_num(ADC_MODULE_2), {HAL_LL_ANSC_REG_ADDRESS, 0}, ADC2_RC4, ADC2_RC4_AN19, 1},
    #endif
    #ifdef ADC2_RE0_AN24
    {PE0, hal_ll_adc_module_num(ADC_MODULE_2), {HAL_LL_ANSE_REG_ADDRESS, 0}, ADC2_RE0, ADC2_RE0_AN24, 1},
    #endif
    #ifdef ADC2_RE1_AN25
    {PE1, hal_ll_adc_module_num(ADC_MODULE_2), {HAL_LL_ANSE_REG_ADDRESS, 0}, ADC2_RE1, ADC2_RE1_AN25, 1},
    #endif
    #ifdef ADC2_RE2_AN26
    {PE2, hal_ll_adc_module_num(ADC_MODULE_2), {HAL_LL_ANSE_REG_ADDRESS, 0}, ADC2_RE2, ADC2_RE2_AN26, 1},
    #endif
    #ifdef ADC2_RE3_AN27
    {PE3, hal_ll_adc_module_num(ADC_MODULE_2), {HAL_LL_ANSE_REG_ADDRESS, 0}, ADC2_RE3, ADC2_RE3_AN27, 1},
    #endif
    #ifdef ADC2_RE4_AN28
    {PE4, hal_ll_adc_module_num(ADC_MODULE_2), {HAL_LL_ANSE_REG_ADDRESS, 0}, ADC2_RE4, ADC2_RE4_AN28, 1},
    #endif
    #ifdef ADC2_RE5_AN29
    {PE5, hal_ll_adc_module_num(ADC_MODULE_2), {HAL_LL_ANSE_REG_ADDRESS, 0}, ADC2_RE5, ADC2_RE5_AN29, 1},
    #endif
    #ifdef ADC2_RE6_AN30
    {PE6, hal_ll_adc_module_num(ADC_MODULE_2), {HAL_LL_ANSE_REG_ADDRESS, 0}, ADC2_RE6, ADC2_RE6_AN30, 1},
    #endif
    #ifdef ADC2_RE7_AN31
    {PE7, hal_ll_adc_module_num(ADC_MODULE_2), {HAL_LL_ANSE_REG_ADDRESS, 0}, ADC2_RE7, ADC2_RE7_AN31, 1},
    #endif
    #ifdef ADC_RE8_AN20
    {PE8, hal_ll_adc_module_num(ADC_MODULE), {HAL_LL_ANSE_REG_ADDRESS, 0}, ADC_RE8, ADC_RE8_AN20, 1},
    #endif
    #ifdef ADC_RE9_AN21
    {PE9, hal_ll_adc_module_num(ADC_MODULE), {HAL_LL_ANSE_REG_ADDRESS, 0}, ADC_RE9, ADC_RE9_AN21, 1},
    #endif
    #ifdef ADC2_RE8_AN20
    {PE8, hal_ll_adc_module_num(ADC_MODULE_2), {HAL_LL_ANSE_REG_ADDRESS, 0}, ADC2_RE8, ADC2_RE8_AN20, 1},
    #endif
    #ifdef ADC2_RE9_AN21
    {PE9, hal_ll_adc_module_num(ADC_MODULE_2), {HAL_LL_ANSE_REG_ADDRESS, 0}, ADC2_RE9, ADC2_RE9_AN21, 1},
    #endif
    #ifdef ADC_RA2_AN2
    {PA2, hal_ll_adc_module_num(ADC_MODULE), {HAL_LL_ANSA_REG_ADDRESS, 0}, ADC_RA2, ADC_RA2_AN2, 1},
    #endif
    #ifdef ADC_RB0_AN3
    {PB0, hal_ll_adc_module_num(ADC_MODULE), {HAL_LL_ANSB_REG_ADDRESS, 0}, ADC_RB0, ADC_RB0_AN3, 1},
    #endif
    #ifdef ADC_RB1_AN6
    {PB1, hal_ll_adc_module_num(ADC_MODULE), {HAL_LL_ANSB_REG_ADDRESS, 0}, ADC_RB1, ADC_RB1_AN6, 1},
    #endif
    #ifdef ADC_RB10_AN5
    {PB10, hal_ll_adc_module_num(ADC_MODULE), {HAL_LL_ANSB_REG_ADDRESS, 0}, ADC_RB10, ADC_RB10_AN5, 1},
    #endif
    #ifdef ADC_RB2_AN7
    {PB2, hal_ll_adc_module_num(ADC_MODULE), {HAL_LL_ANSB_REG_ADDRESS, 0}, ADC_RB2, ADC_RB2_AN7, 1},
    #endif
    #ifdef ADC_RB9_AN4
    {PB9, hal_ll_adc_module_num(ADC_MODULE), {HAL_LL_ANSB_REG_ADDRESS, 0}, ADC_RB9, ADC_RB9_AN4, 1},
    #endif
    #ifdef ADC_RC1_AN8
    {PC1, hal_ll_adc_module_num(ADC_MODULE), {HAL_LL_ANSC_REG_ADDRESS, 0}, ADC_RC1, ADC_RC1_AN8, 1},
    #endif
    #ifdef ADC_RC10_AN10
    {PC10, hal_ll_adc_module_num(ADC_MODULE), {HAL_LL_ANSC_REG_ADDRESS, 0}, ADC_RC10, ADC_RC10_AN10, 1},
    #endif
    #ifdef ADC_RC2_AN9
    {PC2, hal_ll_adc_module_num(ADC_MODULE), {HAL_LL_ANSC_REG_ADDRESS, 0}, ADC_RC2, ADC_RC2_AN9, 1},
    #endif
    #ifdef ADC_RC9_AN11
    {PC9, hal_ll_adc_module_num(ADC_MODULE), {HAL_LL_ANSC_REG_ADDRESS, 0}, ADC_RC9, ADC_RC9_AN11, 1},
    #endif
    #ifdef ADC_RA4_AN10
    {PA4, hal_ll_adc_module_num(ADC_MODULE), {HAL_LL_ANSA_REG_ADDRESS, 0}, ADC_RA4, ADC_RA4_AN10, 1},
    #endif
    #ifdef ADC_RB4_AN9
    {PB4, hal_ll_adc_module_num(ADC_MODULE), {HAL_LL_ANSB_REG_ADDRESS, 0}, ADC_RB4, ADC_RB4_AN9, 1},
    #endif
    #ifdef ADC_RC3_AN11
    {PC3, hal_ll_adc_module_num(ADC_MODULE), {HAL_LL_ANSC_REG_ADDRESS, 0}, ADC_RC3, ADC_RC3_AN11, 1},
    #endif
    #ifdef ADC_RC4_AN12
    {PC4, hal_ll_adc_module_num(ADC_MODULE), {HAL_LL_ANSC_REG_ADDRESS, 0}, ADC_RC4, ADC_RC4_AN12, 1},
    #endif
    #ifdef ADC_RC5_AN15
    {PC5, hal_ll_adc_module_num(ADC_MODULE), {HAL_LL_ANSC_REG_ADDRESS, 0}, ADC_RC5, ADC_RC5_AN15, 1},
    #endif
    #ifdef ADC1_RA2_AN13
    {PA2, hal_ll_adc_module_num(ADC_MODULE_1), {HAL_LL_ANSA_REG_ADDRESS, 0}, ADC1_RA2, ADC1_RA2_AN13, 1},
    #endif
    #ifdef ADC1_RA3_AN14
    {PA3, hal_ll_adc_module_num(ADC_MODULE_1), {HAL_LL_ANSA_REG_ADDRESS, 0}, ADC1_RA3, ADC1_RA3_AN14, 1},
    #endif
    #ifdef ADC1_RB13_AN11
    {PB13, hal_ll_adc_module_num(ADC_MODULE_1), {HAL_LL_ANSB_REG_ADDRESS, 0}, ADC1_RB13, ADC1_RB13_AN11, 1},
    #endif
    #ifdef ADC1_RB14_AN10
    {PB14, hal_ll_adc_module_num(ADC_MODULE_1), {HAL_LL_ANSB_REG_ADDRESS, 0}, ADC1_RB14, ADC1_RB14_AN10, 1},
    #endif
    #ifdef ADC1_RB15_AN9
    {PB15, hal_ll_adc_module_num(ADC_MODULE_1), {HAL_LL_ANSB_REG_ADDRESS, 0}, ADC1_RB15, ADC1_RB15_AN9, 1},
    #endif
    #ifdef ADC1_RB4_AN15
    {PB4, hal_ll_adc_module_num(ADC_MODULE_1), {HAL_LL_ANSB_REG_ADDRESS, 0}, ADC1_RB4, ADC1_RB4_AN15, 1},
    #endif
    #ifdef ADC1_RA4_AN16
    {PA4, hal_ll_adc_module_num(ADC_MODULE_1), {HAL_LL_ANSA_REG_ADDRESS, 0}, ADC1_RA4, ADC1_RA4_AN16, 1},
    #endif
    #ifdef ADC1_RB5_AN17
    {PB5, hal_ll_adc_module_num(ADC_MODULE_1), {HAL_LL_ANSB_REG_ADDRESS, 0}, ADC1_RB5, ADC1_RB5_AN17, 1},
    #endif
    #ifdef ADC1_RB6_AN18
    {PB6, hal_ll_adc_module_num(ADC_MODULE_1), {HAL_LL_ANSB_REG_ADDRESS, 0}, ADC1_RB6, ADC1_RB6_AN18, 1},
    #endif
    #ifdef ADC1_RB7_AN19
    {PB7, hal_ll_adc_module_num(ADC_MODULE_1), {HAL_LL_ANSB_REG_ADDRESS, 0}, ADC1_RB7, ADC1_RB7_AN19, 1},
    #endif
    #ifdef ADC1_RB8_AN20
    {PB8, hal_ll_adc_module_num(ADC_MODULE_1), {HAL_LL_ANSB_REG_ADDRESS, 0}, ADC1_RB8, ADC1_RB8_AN20, 1},
    #endif
    #ifdef ADC1_RB9_AN21
    {PB9, hal_ll_adc_module_num(ADC_MODULE_1), {HAL_LL_ANSB_REG_ADDRESS, 0}, ADC1_RB9, ADC1_RB9_AN21, 1},
    #endif
    #ifdef ADC1_RA6_AN23
    {PA6, hal_ll_adc_module_num(ADC_MODULE_1), {HAL_LL_ANSA_REG_ADDRESS, 0}, ADC1_RA6, ADC1_RA6_AN23, 1},
    #endif
    #ifdef ADC1_RA7_AN22
    {PA7, hal_ll_adc_module_num(ADC_MODULE_1), {HAL_LL_ANSA_REG_ADDRESS, 0}, ADC1_RA7, ADC1_RA7_AN22, 1},
    #endif
    #ifdef ADC1_RC4_AN16
    {PC4, hal_ll_adc_module_num(ADC_MODULE_1), {HAL_LL_ANSC_REG_ADDRESS, 0}, ADC1_RC4, ADC1_RC4_AN16, 1},
    #endif
    #ifdef ADC1_RG6_AN17
    {PG6, hal_ll_adc_module_num(ADC_MODULE_1), {HAL_LL_ANSG_REG_ADDRESS, 0}, ADC1_RG6, ADC1_RG6_AN17, 1},
    #endif
    #ifdef ADC1_RG8_AN19
    {PG8, hal_ll_adc_module_num(ADC_MODULE_1), {HAL_LL_ANSG_REG_ADDRESS, 0}, ADC1_RG8, ADC1_RG8_AN19, 1},
    #endif
    #ifdef ADC1_RG9_AN20
    {PG9, hal_ll_adc_module_num(ADC_MODULE_1), {HAL_LL_ANSG_REG_ADDRESS, 0}, ADC1_RG9, ADC1_RG9_AN20, 1},
    #endif
    #ifdef ADC1_RB12_AN8
    {PB12, hal_ll_adc_module_num(ADC_MODULE_1), {HAL_LL_ANSB_REG_ADDRESS, 0}, ADC1_RB12, ADC1_RB12_AN8, 1},
    #endif
    #ifdef ADC1_RB13_AN7
    {PB13, hal_ll_adc_module_num(ADC_MODULE_1), {HAL_LL_ANSB_REG_ADDRESS, 0}, ADC1_RB13, ADC1_RB13_AN7, 1},
    #endif
    #ifdef ADC1_RB14_AN6
    {PB14, hal_ll_adc_module_num(ADC_MODULE_1), {HAL_LL_ANSB_REG_ADDRESS, 0}, ADC1_RB14, ADC1_RB14_AN6, 1},
    #endif
    #ifdef ADC1_RC0_AN10
    {PC0, hal_ll_adc_module_num(ADC_MODULE_1), {HAL_LL_ANSC_REG_ADDRESS, 0}, ADC1_RC0, ADC1_RC0_AN10, 1},
    #endif
    #ifdef ADC1_RC1_AN11
    {PC1, hal_ll_adc_module_num(ADC_MODULE_1), {HAL_LL_ANSC_REG_ADDRESS, 0}, ADC1_RC1, ADC1_RC1_AN11, 1},
    #endif
    #ifdef ADC1_RC2_AN12
    {PC2, hal_ll_adc_module_num(ADC_MODULE_1), {HAL_LL_ANSC_REG_ADDRESS, 0}, ADC1_RC2, ADC1_RC2_AN12, 1},
    #endif
    #ifdef ADC1_RC3_AN13
    {PC3, hal_ll_adc_module_num(ADC_MODULE_1), {HAL_LL_ANSC_REG_ADDRESS, 0}, ADC1_RC3, ADC1_RC3_AN13, 1},
    #endif
    #ifdef ADC1_RD0_AN43
    {PD0, hal_ll_adc_module_num(ADC_MODULE_1), {HAL_LL_ANSD_REG_ADDRESS, 0}, ADC1_RD0, ADC1_RD0_AN43, 1},
    #endif
    #ifdef ADC1_RD1_AN35
    {PD1, hal_ll_adc_module_num(ADC_MODULE_1), {HAL_LL_ANSD_REG_ADDRESS, 0}, ADC1_RD1, ADC1_RD1_AN35, 1},
    #endif
    #ifdef ADC1_RD10_AN41
    {PD10, hal_ll_adc_module_num(ADC_MODULE_1), {HAL_LL_ANSD_REG_ADDRESS, 0}, ADC1_RD10, ADC1_RD10_AN41, 1},
    #endif
    #ifdef ADC1_RD11_AN42
    {PD11, hal_ll_adc_module_num(ADC_MODULE_1), {HAL_LL_ANSD_REG_ADDRESS, 0}, ADC1_RD11, ADC1_RD11_AN42, 1},
    #endif
    #ifdef ADC1_RD2_AN25
    {PD2, hal_ll_adc_module_num(ADC_MODULE_1), {HAL_LL_ANSD_REG_ADDRESS, 0}, ADC1_RD2, ADC1_RD2_AN25, 1},
    #endif
    #ifdef ADC1_RD3_AN44
    {PD3, hal_ll_adc_module_num(ADC_MODULE_1), {HAL_LL_ANSD_REG_ADDRESS, 0}, ADC1_RD3, ADC1_RD3_AN44, 1},
    #endif
    #ifdef ADC1_RD4_AN47
    {PD4, hal_ll_adc_module_num(ADC_MODULE_1), {HAL_LL_ANSD_REG_ADDRESS, 0}, ADC1_RD4, ADC1_RD4_AN47, 1},
    #endif
    #ifdef ADC1_RD5_AN48
    {PD5, hal_ll_adc_module_num(ADC_MODULE_1), {HAL_LL_ANSD_REG_ADDRESS, 0}, ADC1_RD5, ADC1_RD5_AN48, 1},
    #endif
    #ifdef ADC1_RD6_AN34
    {PD6, hal_ll_adc_module_num(ADC_MODULE_1), {HAL_LL_ANSD_REG_ADDRESS, 0}, ADC1_RD6, ADC1_RD6_AN34, 1},
    #endif
    #ifdef ADC1_RD7_AN20
    {PD7, hal_ll_adc_module_num(ADC_MODULE_1), {HAL_LL_ANSD_REG_ADDRESS, 0}, ADC1_RD7, ADC1_RD7_AN20, 1},
    #endif
    #ifdef ADC1_RD8_AN40
    {PD8, hal_ll_adc_module_num(ADC_MODULE_1), {HAL_LL_ANSD_REG_ADDRESS, 0}, ADC1_RD8, ADC1_RD8_AN40, 1},
    #endif
    #ifdef ADC1_RD9_AN24
    {PD9, hal_ll_adc_module_num(ADC_MODULE_1), {HAL_LL_ANSD_REG_ADDRESS, 0}, ADC1_RD9, ADC1_RD9_AN24, 1},
    #endif
    #ifdef ADC1_RF3_AN30
    {PF3, hal_ll_adc_module_num(ADC_MODULE_1), {HAL_LL_ANSF_REG_ADDRESS, 0}, ADC1_RF3, ADC1_RF3_AN30, 1},
    #endif
    #ifdef ADC1_RF4_AN11
    {PF4, hal_ll_adc_module_num(ADC_MODULE_1), {HAL_LL_ANSF_REG_ADDRESS, 0}, ADC1_RF4, ADC1_RF4_AN11, 1},
    #endif
    #ifdef ADC1_RF5_AN10
    {PF5, hal_ll_adc_module_num(ADC_MODULE_1), {HAL_LL_ANSF_REG_ADDRESS, 0}, ADC1_RF5, ADC1_RF5_AN10, 1},
    #endif
    #ifdef ADC1_RG9_AN49
    {PG9, hal_ll_adc_module_num(ADC_MODULE_1), {HAL_LL_ANSG_REG_ADDRESS, 0}, ADC1_RG9, ADC1_RG9_AN49, 1},
    #endif
    #ifdef ADC1_RA1_AN26
    {PA1, hal_ll_adc_module_num(ADC_MODULE_1), {HAL_LL_ANSA_REG_ADDRESS, 0}, ADC1_RA1, ADC1_RA1_AN26, 1},
    #endif
    #ifdef ADC1_RA14_AN38
    {PA14, hal_ll_adc_module_num(ADC_MODULE_1), {HAL_LL_ANSA_REG_ADDRESS, 0}, ADC1_RA14, ADC1_RA14_AN38, 1},
    #endif
    #ifdef ADC1_RA15_AN39
    {PA15, hal_ll_adc_module_num(ADC_MODULE_1), {HAL_LL_ANSA_REG_ADDRESS, 0}, ADC1_RA15, ADC1_RA15_AN39, 1},
    #endif
    #ifdef ADC1_RA4_AN36
    {PA4, hal_ll_adc_module_num(ADC_MODULE_1), {HAL_LL_ANSA_REG_ADDRESS, 0}, ADC1_RA4, ADC1_RA4_AN36, 1},
    #endif
    #ifdef ADC1_RA5_AN37
    {PA5, hal_ll_adc_module_num(ADC_MODULE_1), {HAL_LL_ANSA_REG_ADDRESS, 0}, ADC1_RA5, ADC1_RA5_AN37, 1},
    #endif
    #ifdef ADC1_RC3_AN9
    {PC3, hal_ll_adc_module_num(ADC_MODULE_1), {HAL_LL_ANSC_REG_ADDRESS, 0}, ADC1_RC3, ADC1_RC3_AN9, 1},
    #endif
    #ifdef ADC1_RD12_AN45
    {PD12, hal_ll_adc_module_num(ADC_MODULE_1), {HAL_LL_ANSD_REG_ADDRESS, 0}, ADC1_RD12, ADC1_RD12_AN45, 1},
    #endif
    #ifdef ADC1_RD13_AN46
    {PD13, hal_ll_adc_module_num(ADC_MODULE_1), {HAL_LL_ANSD_REG_ADDRESS, 0}, ADC1_RD13, ADC1_RD13_AN46, 1},
    #endif
    #ifdef ADC1_RD14_AN28
    {PD14, hal_ll_adc_module_num(ADC_MODULE_1), {HAL_LL_ANSD_REG_ADDRESS, 0}, ADC1_RD14, ADC1_RD14_AN28, 1},
    #endif
    #ifdef ADC1_RD15_AN29
    {PD15, hal_ll_adc_module_num(ADC_MODULE_1), {HAL_LL_ANSD_REG_ADDRESS, 0}, ADC1_RD15, ADC1_RD15_AN29, 1},
    #endif
    #ifdef ADC1_RF13_AN27
    {PF13, hal_ll_adc_module_num(ADC_MODULE_1), {HAL_LL_ANSF_REG_ADDRESS, 0}, ADC1_RF13, ADC1_RF13_AN27, 1},
    #endif
    #ifdef ADC1_RF2_AN31
    {PF2, hal_ll_adc_module_num(ADC_MODULE_1), {HAL_LL_ANSF_REG_ADDRESS, 0}, ADC1_RF2, ADC1_RF2_AN31, 1},
    #endif
    #ifdef ADC1_RF8_AN32
    {PF8, hal_ll_adc_module_num(ADC_MODULE_1), {HAL_LL_ANSF_REG_ADDRESS, 0}, ADC1_RF8, ADC1_RF8_AN32, 1},
    #endif
    #ifdef ADC1_RG15_AN33
    {PG15, hal_ll_adc_module_num(ADC_MODULE_1), {HAL_LL_ANSG_REG_ADDRESS, 0}, ADC1_RG15, ADC1_RG15_AN33, 1},
    #endif
    #ifdef ADC1_RC3_AN12
    {PC3, hal_ll_adc_module_num(ADC_MODULE_1), {HAL_LL_ANSC_REG_ADDRESS, 0}, ADC1_RC3, ADC1_RC3_AN12, 1},
    #endif
    #endif
    // EOF list

    #ifdef HAL_LL_ANSELA_ANSA3
    {PA3, 0, {HAL_LL_ANSELA_REG_ADDRESS , 0}, HAL_LL_ANSELA_ANSA3, 0, 1},
    #endif
    #ifdef HAL_LL_ANSELA_ANSA4
    {PA4, 0, {HAL_LL_ANSELA_REG_ADDRESS , 0}, HAL_LL_ANSELA_ANSA4, 0, 1},
    #endif
    #ifdef HAL_LL_ANSELB_ANSB8
    {PB8, 0, {HAL_LL_ANSELB_REG_ADDRESS , 0}, HAL_LL_ANSELB_ANSB8, 0, 1},
    #endif
    #ifdef HAL_LL_ANSELC_ANSC4
    {PC4, 0, {HAL_LL_ANSELC_REG_ADDRESS , 0}, HAL_LL_ANSELC_ANSC4, 0, 1},
    #endif
    #ifdef HAL_LL_ANSELC_ANSC5
    {PC5, 0, {HAL_LL_ANSELC_REG_ADDRESS , 0}, HAL_LL_ANSELC_ANSC5, 0, 1},
    #endif
    #ifdef HAL_LL_ANSELB_ANSB4
    {PB4, 0, {HAL_LL_ANSELB_REG_ADDRESS , 0}, HAL_LL_ANSELB_ANSB4, 0, 1},
    #endif
    #ifdef HAL_LL_ANSELC_ANSC0
    {PC0, 0, {HAL_LL_ANSELC_REG_ADDRESS , 0}, HAL_LL_ANSELC_ANSC0, 0, 1},
    #endif
    #ifdef HAL_LL_ANSELD_ANSD14
    {PD14, 0, {HAL_LL_ANSELD_REG_ADDRESS , 0}, HAL_LL_ANSELD_ANSD14, 0, 1},
    #endif
    #ifdef HAL_LL_ANSELC_ANSC13
    {PC13, 0, {HAL_LL_ANSELC_REG_ADDRESS , 0}, HAL_LL_ANSELC_ANSC13, 0, 1},
    #endif
    #ifdef HAL_LL_ANSELC_ANSC14
    {PC14, 0, {HAL_LL_ANSELC_REG_ADDRESS , 0}, HAL_LL_ANSELC_ANSC14, 0, 1},
    #endif
    #ifdef HAL_LL_ANSELD_ANSD6
    {PD6, 0, {HAL_LL_ANSELD_REG_ADDRESS , 0}, HAL_LL_ANSELD_ANSD6, 0, 1},
    #endif
    #ifdef HAL_LL_ANSELD_ANSD7
    {PD7, 0, {HAL_LL_ANSELD_REG_ADDRESS , 0}, HAL_LL_ANSELD_ANSD7, 0, 1},
    #endif
    #ifdef HAL_LL_ANSELG_ANSG6
    {PG6, 0, {HAL_LL_ANSELG_REG_ADDRESS , 0}, HAL_LL_ANSELG_ANSG6, 0, 1},
    #endif
    #ifdef HAL_LL_ANSELG_ANSG7
    {PG7, 0, {HAL_LL_ANSELG_REG_ADDRESS , 0}, HAL_LL_ANSELG_ANSG7, 0, 1},
    #endif
    #ifdef HAL_LL_ANSELG_ANSG8
    {PG8, 0, {HAL_LL_ANSELG_REG_ADDRESS , 0}, HAL_LL_ANSELG_ANSG8, 0, 1},
    #endif
    #ifdef HAL_LL_ANSELG_ANSG9
    {PG9, 0, {HAL_LL_ANSELG_REG_ADDRESS , 0}, HAL_LL_ANSELG_ANSG9, 0, 1},
    #endif
    #ifdef HAL_LL_ANSELA_ANSA9
    {PA9, 0, {HAL_LL_ANSELA_REG_ADDRESS , 0}, HAL_LL_ANSELA_ANSA9, 0, 1},
    #endif
    #ifdef HAL_LL_ANSELA_ANSA10
    {PA10, 0, {HAL_LL_ANSELA_REG_ADDRESS , 0}, HAL_LL_ANSELA_ANSA10, 0, 1},
    #endif

    { HAL_LL_PIN_NC, HAL_LL_MODULE_ERROR, {HAL_LL_MODULE_ERROR,HAL_LL_MODULE_ERROR}, 0xFF, 0xFF, 0 }
    //------------ END
};

#ifdef __cplusplus
}
#endif

#endif // _HAL_LL_ANALOG_IN_MAP_H_
// ------------------------------------------------------------------------- END
