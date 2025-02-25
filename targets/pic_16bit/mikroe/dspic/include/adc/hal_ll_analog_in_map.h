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
    {GPIO_PB0, hal_ll_adc_module_num(ADC_MODULE), {HAL_LL_ADPCFG_REG_ADDRESS, 0}, ADC_RB0, ADC_RB0_AN0, 0},
    #endif
    #ifdef ADC_RB1_AN1
    {GPIO_PB1, hal_ll_adc_module_num(ADC_MODULE), {HAL_LL_ADPCFG_REG_ADDRESS, 0}, ADC_RB1, ADC_RB1_AN1, 0},
    #endif
    #ifdef ADC_RB2_AN2
    {GPIO_PB2, hal_ll_adc_module_num(ADC_MODULE), {HAL_LL_ADPCFG_REG_ADDRESS, 0}, ADC_RB2, ADC_RB2_AN2, 0},
    #endif
    #ifdef ADC_RB3_AN3
    {GPIO_PB3, hal_ll_adc_module_num(ADC_MODULE), {HAL_LL_ADPCFG_REG_ADDRESS, 0}, ADC_RB3, ADC_RB3_AN3, 0},
    #endif
    #ifdef ADC_RB4_AN4
    {GPIO_PB4, hal_ll_adc_module_num(ADC_MODULE), {HAL_LL_ADPCFG_REG_ADDRESS, 0}, ADC_RB4, ADC_RB4_AN4, 0},
    #endif
    #ifdef ADC_RB5_AN5
    {GPIO_PB5, hal_ll_adc_module_num(ADC_MODULE), {HAL_LL_ADPCFG_REG_ADDRESS, 0}, ADC_RB5, ADC_RB5_AN5, 0},
    #endif
    #ifdef ADC_RB6_AN6
    {GPIO_PB6, hal_ll_adc_module_num(ADC_MODULE), {HAL_LL_ADPCFG_REG_ADDRESS, 0}, ADC_RB6, ADC_RB6_AN6, 0},
    #endif
    #ifdef ADC_RB7_AN7
    {GPIO_PB7, hal_ll_adc_module_num(ADC_MODULE), {HAL_LL_ADPCFG_REG_ADDRESS, 0}, ADC_RB7, ADC_RB7_AN7, 0},
    #endif
    #ifdef ADC_RB8_AN8
    {GPIO_PB8, hal_ll_adc_module_num(ADC_MODULE), {HAL_LL_ADPCFG_REG_ADDRESS, 0}, ADC_RB8, ADC_RB8_AN8, 0},
    #endif
    #ifdef ADC_RB9_AN9
    {GPIO_PB9, hal_ll_adc_module_num(ADC_MODULE), {HAL_LL_ADPCFG_REG_ADDRESS, 0}, ADC_RB9, ADC_RB9_AN9, 0},
    #endif
    #ifdef ADC_RB10_AN10
    {GPIO_PB10, hal_ll_adc_module_num(ADC_MODULE), {HAL_LL_ADPCFG_REG_ADDRESS, 0}, ADC_RB10, ADC_RB10_AN10, 0},
    #endif
    #ifdef ADC_RB11_AN11
    {GPIO_PB11, hal_ll_adc_module_num(ADC_MODULE), {HAL_LL_ADPCFG_REG_ADDRESS, 0}, ADC_RB11, ADC_RB11_AN11, 0},
    #endif
    #ifdef ADC_RB12_AN12
    {GPIO_PB12, hal_ll_adc_module_num(ADC_MODULE), {HAL_LL_ADPCFG_REG_ADDRESS, 0}, ADC_RB12, ADC_RB12_AN12, 0},
    #endif
    #ifdef ADC_RB13_AN13
    {GPIO_PB13, hal_ll_adc_module_num(ADC_MODULE), {HAL_LL_ADPCFG_REG_ADDRESS, 0}, ADC_RB13, ADC_RB13_AN13, 0},
    #endif
    #ifdef ADC_RB14_AN14
    {GPIO_PB14, hal_ll_adc_module_num(ADC_MODULE), {HAL_LL_ADPCFG_REG_ADDRESS, 0}, ADC_RB14, ADC_RB14_AN14, 0},
    #endif
    #ifdef ADC_RB15_AN15
    {GPIO_PB15, hal_ll_adc_module_num(ADC_MODULE), {HAL_LL_ADPCFG_REG_ADDRESS, 0}, ADC_RB15, ADC_RB15_AN15, 0},
    #endif
    #ifdef ADC1_RA0_AN0
    {GPIO_PA0, hal_ll_adc_module_num(ADC_MODULE_1), {HAL_LL_ADPCFG_REG_ADDRESS, 0}, ADC1_RA0, ADC1_RA0_AN0, 0},
    #endif
    #ifdef ADC1_RA1_AN1
    {GPIO_PA1, hal_ll_adc_module_num(ADC_MODULE_1), {HAL_LL_ADPCFG_REG_ADDRESS, 0}, ADC1_RA1, ADC1_RA1_AN1, 0},
    #endif
    #ifdef ADC1_RA2_AN32
    {GPIO_PA2, hal_ll_adc_module_num(ADC_MODULE_1), {HAL_LL_ADPCFG_REG_ADDRESS, 0}, ADC1_RA2, ADC1_RA2_AN32, 0},
    #endif
    #ifdef ADC1_RA4_AN24
    {GPIO_PA4, hal_ll_adc_module_num(ADC_MODULE_1), {HAL_LL_ADPCFG_REG_ADDRESS, 0}, ADC1_RA4, ADC1_RA4_AN24, 0},
    #endif
    #ifdef ADC1_RA9_AN28
    {GPIO_PA9, hal_ll_adc_module_num(ADC_MODULE_1), {HAL_LL_ADPCFG_REG_ADDRESS, 0}, ADC1_RA9, ADC1_RA9_AN28, 0},
    #endif
    #ifdef ADC1_RB0_AN2
    {GPIO_PB0, hal_ll_adc_module_num(ADC_MODULE_1), {HAL_LL_ADPCFG_REG_ADDRESS, 0}, ADC1_RB0, ADC1_RB0_AN2, 0},
    #endif
    #ifdef ADC1_RB1_AN3
    {GPIO_PB1, hal_ll_adc_module_num(ADC_MODULE_1), {HAL_LL_ADPCFG_REG_ADDRESS, 0}, ADC1_RB1, ADC1_RB1_AN3, 0},
    #endif
    #ifdef ADC1_RB2_AN4
    {GPIO_PB2, hal_ll_adc_module_num(ADC_MODULE_1), {HAL_LL_ADPCFG_REG_ADDRESS, 0}, ADC1_RB2, ADC1_RB2_AN4, 0},
    #endif
    #ifdef ADC1_RB3_AN5
    {GPIO_PB3, hal_ll_adc_module_num(ADC_MODULE_1), {HAL_LL_ADPCFG_REG_ADDRESS, 0}, ADC1_RB3, ADC1_RB3_AN5, 0},
    #endif
    #ifdef ADC1_RB7_AN25
    {GPIO_PB7, hal_ll_adc_module_num(ADC_MODULE_1), {HAL_LL_ADPCFG_REG_ADDRESS, 0}, ADC1_RB7, ADC1_RB7_AN25, 0},
    #endif
    #ifdef ADC1_RB8_AN26
    {GPIO_PB8, hal_ll_adc_module_num(ADC_MODULE_1), {HAL_LL_ADPCFG_REG_ADDRESS, 0}, ADC1_RB8, ADC1_RB8_AN26, 0},
    #endif
    #ifdef ADC1_RB9_AN27
    {GPIO_PB9, hal_ll_adc_module_num(ADC_MODULE_1), {HAL_LL_ADPCFG_REG_ADDRESS, 0}, ADC1_RB9, ADC1_RB9_AN27, 0},
    #endif
    #ifdef ADC1_RC0_AN6
    {GPIO_PC0, hal_ll_adc_module_num(ADC_MODULE_1), {HAL_LL_ADPCFG_REG_ADDRESS, 0}, ADC1_RC0, ADC1_RC0_AN6, 0},
    #endif
    #ifdef ADC1_RC1_AN7
    {GPIO_PC1, hal_ll_adc_module_num(ADC_MODULE_1), {HAL_LL_ADPCFG_REG_ADDRESS, 0}, ADC1_RC1, ADC1_RC1_AN7, 0},
    #endif
    #ifdef ADC1_RC2_AN8
    {GPIO_PC2, hal_ll_adc_module_num(ADC_MODULE_1), {HAL_LL_ADPCFG_REG_ADDRESS, 0}, ADC1_RC2, ADC1_RC2_AN8, 0},
    #endif
    #ifdef ADC1_RC3_AN29
    {GPIO_PC3, hal_ll_adc_module_num(ADC_MODULE_1), {HAL_LL_ADPCFG_REG_ADDRESS, 0}, ADC1_RC3, ADC1_RC3_AN29, 0},
    #endif
    #ifdef ADC1_RC4_AN30
    {GPIO_PC4, hal_ll_adc_module_num(ADC_MODULE_1), {HAL_LL_ADPCFG_REG_ADDRESS, 0}, ADC1_RC4, ADC1_RC4_AN30, 0},
    #endif
    #ifdef ADC1_RC5_AN31
    {GPIO_PC5, hal_ll_adc_module_num(ADC_MODULE_1), {HAL_LL_ADPCFG_REG_ADDRESS, 0}, ADC1_RC5, ADC1_RC5_AN31, 0},
    #endif
    #ifdef ADC2_RA0_AN0
    {GPIO_PA0, hal_ll_adc_module_num(ADC_MODULE_2), {HAL_LL_ADPCFG_REG_ADDRESS, 0}, ADC2_RA0, ADC2_RA0_AN0, 0},
    #endif
    #ifdef ADC2_RA1_AN1
    {GPIO_PA1, hal_ll_adc_module_num(ADC_MODULE_2), {HAL_LL_ADPCFG_REG_ADDRESS, 0}, ADC2_RA1, ADC2_RA1_AN1, 0},
    #endif
    #ifdef ADC2_RA4_AN24
    {GPIO_PA4, hal_ll_adc_module_num(ADC_MODULE_2), {HAL_LL_ADPCFG_REG_ADDRESS, 0}, ADC2_RA4, ADC2_RA4_AN24, 0},
    #endif
    #ifdef ADC2_RA9_AN28
    {GPIO_PA9, hal_ll_adc_module_num(ADC_MODULE_2), {HAL_LL_ADPCFG_REG_ADDRESS, 0}, ADC2_RA9, ADC2_RA9_AN28, 0},
    #endif
    #ifdef ADC2_RB0_AN2
    {GPIO_PB0, hal_ll_adc_module_num(ADC_MODULE_2), {HAL_LL_ADPCFG_REG_ADDRESS, 0}, ADC2_RB0, ADC2_RB0_AN2, 0},
    #endif
    #ifdef ADC2_RB1_AN3
    {GPIO_PB1, hal_ll_adc_module_num(ADC_MODULE_2), {HAL_LL_ADPCFG_REG_ADDRESS, 0}, ADC2_RB1, ADC2_RB1_AN3, 0},
    #endif
    #ifdef ADC2_RB2_AN4
    {GPIO_PB2, hal_ll_adc_module_num(ADC_MODULE_2), {HAL_LL_ADPCFG_REG_ADDRESS, 0}, ADC2_RB2, ADC2_RB2_AN4, 0},
    #endif
    #ifdef ADC2_RB3_AN5
    {GPIO_PB3, hal_ll_adc_module_num(ADC_MODULE_2), {HAL_LL_ADPCFG_REG_ADDRESS, 0}, ADC2_RB3, ADC2_RB3_AN5, 0},
    #endif
    #ifdef ADC2_RB7_AN25
    {GPIO_PB7, hal_ll_adc_module_num(ADC_MODULE_2), {HAL_LL_ADPCFG_REG_ADDRESS, 0}, ADC2_RB7, ADC2_RB7_AN25, 0},
    #endif
    #ifdef ADC2_RB8_AN26
    {GPIO_PB8, hal_ll_adc_module_num(ADC_MODULE_2), {HAL_LL_ADPCFG_REG_ADDRESS, 0}, ADC2_RB8, ADC2_RB8_AN26, 0},
    #endif
    #ifdef ADC2_RB9_AN27
    {GPIO_PB9, hal_ll_adc_module_num(ADC_MODULE_2), {HAL_LL_ADPCFG_REG_ADDRESS, 0}, ADC2_RB9, ADC2_RB9_AN27, 0},
    #endif
    #ifdef ADC2_RC0_AN6
    {GPIO_PC0, hal_ll_adc_module_num(ADC_MODULE_2), {HAL_LL_ADPCFG_REG_ADDRESS, 0}, ADC2_RC0, ADC2_RC0_AN6, 0},
    #endif
    #ifdef ADC2_RC1_AN7
    {GPIO_PC1, hal_ll_adc_module_num(ADC_MODULE_2), {HAL_LL_ADPCFG_REG_ADDRESS, 0}, ADC2_RC1, ADC2_RC1_AN7, 0},
    #endif
    #ifdef ADC2_RC2_AN8
    {GPIO_PC2, hal_ll_adc_module_num(ADC_MODULE_2), {HAL_LL_ADPCFG_REG_ADDRESS, 0}, ADC2_RC2, ADC2_RC2_AN8, 0},
    #endif
    #ifdef ADC2_RC3_AN29
    {GPIO_PC3, hal_ll_adc_module_num(ADC_MODULE_2), {HAL_LL_ADPCFG_REG_ADDRESS, 0}, ADC2_RC3, ADC2_RC3_AN29, 0},
    #endif
    #ifdef ADC2_RC4_AN30
    {GPIO_PC4, hal_ll_adc_module_num(ADC_MODULE_2), {HAL_LL_ADPCFG_REG_ADDRESS, 0}, ADC2_RC4, ADC2_RC4_AN30, 0},
    #endif
    #ifdef ADC2_RC5_AN31
    {GPIO_PC5, hal_ll_adc_module_num(ADC_MODULE_2), {HAL_LL_ADPCFG_REG_ADDRESS, 0}, ADC2_RC5, ADC2_RC5_AN31, 0},
    #endif
    #ifdef ADC1_RA11_AN9
    {GPIO_PA11, hal_ll_adc_module_num(ADC_MODULE_1), {HAL_LL_ADPCFG_REG_ADDRESS, 0}, ADC1_RA11, ADC1_RA11_AN9, 0},
    #endif
    #ifdef ADC1_RA12_AN10
    {GPIO_PA12, hal_ll_adc_module_num(ADC_MODULE_1), {HAL_LL_ADPCFG_REG_ADDRESS, 0}, ADC1_RA12, ADC1_RA12_AN10, 0},
    #endif
    #ifdef ADC1_RC10_AN48
    {GPIO_PC10, hal_ll_adc_module_num(ADC_MODULE_1), {HAL_LL_ADPCFG_REG_ADDRESS, 0}, ADC1_RC10, ADC1_RC10_AN48, 0},
    #endif
    #ifdef ADC1_RC11_AN11
    {GPIO_PC11, hal_ll_adc_module_num(ADC_MODULE_1), {HAL_LL_ADPCFG_REG_ADDRESS, 0}, ADC1_RC11, ADC1_RC11_AN11, 0},
    #endif
    #ifdef ADC1_RC12_AN49
    {GPIO_PC12, hal_ll_adc_module_num(ADC_MODULE_1), {HAL_LL_ADPCFG_REG_ADDRESS, 0}, ADC1_RC12, ADC1_RC12_AN49, 0},
    #endif
    #ifdef ADC1_RE12_AN12
    {GPIO_PE12, hal_ll_adc_module_num(ADC_MODULE_1), {HAL_LL_ADPCFG_REG_ADDRESS, 0}, ADC1_RE12, ADC1_RE12_AN12, 0},
    #endif
    #ifdef ADC1_RE13_AN13
    {GPIO_PE13, hal_ll_adc_module_num(ADC_MODULE_1), {HAL_LL_ADPCFG_REG_ADDRESS, 0}, ADC1_RE13, ADC1_RE13_AN13, 0},
    #endif
    #ifdef ADC1_RE14_AN14
    {GPIO_PE14, hal_ll_adc_module_num(ADC_MODULE_1), {HAL_LL_ADPCFG_REG_ADDRESS, 0}, ADC1_RE14, ADC1_RE14_AN14, 0},
    #endif
    #ifdef ADC1_RE15_AN15
    {GPIO_PE15, hal_ll_adc_module_num(ADC_MODULE_1), {HAL_LL_ADPCFG_REG_ADDRESS, 0}, ADC1_RE15, ADC1_RE15_AN15, 0},
    #endif
    #ifdef ADC1_RG6_AN19
    {GPIO_PG6, hal_ll_adc_module_num(ADC_MODULE_1), {HAL_LL_ADPCFG_REG_ADDRESS, 0}, ADC1_RG6, ADC1_RG6_AN19, 0},
    #endif
    #ifdef ADC1_RG7_AN18
    {GPIO_PG7, hal_ll_adc_module_num(ADC_MODULE_1), {HAL_LL_ADPCFG_REG_ADDRESS, 0}, ADC1_RG7, ADC1_RG7_AN18, 0},
    #endif
    #ifdef ADC1_RG8_AN17
    {GPIO_PG8, hal_ll_adc_module_num(ADC_MODULE_1), {HAL_LL_ADPCFG_REG_ADDRESS, 0}, ADC1_RG8, ADC1_RG8_AN17, 0},
    #endif
    #ifdef ADC1_RG9_AN16
    {GPIO_PG9, hal_ll_adc_module_num(ADC_MODULE_1), {HAL_LL_ADPCFG_REG_ADDRESS, 0}, ADC1_RG9, ADC1_RG9_AN16, 0},
    #endif
    #ifdef ADC2_RA11_AN9
    {GPIO_PA11, hal_ll_adc_module_num(ADC_MODULE_2), {HAL_LL_ADPCFG_REG_ADDRESS, 0}, ADC2_RA11, ADC2_RA11_AN9, 0},
    #endif
    #ifdef ADC2_RA12_AN10
    {GPIO_PA12, hal_ll_adc_module_num(ADC_MODULE_2), {HAL_LL_ADPCFG_REG_ADDRESS, 0}, ADC2_RA12, ADC2_RA12_AN10, 0},
    #endif
    #ifdef ADC2_RC11_AN11
    {GPIO_PC11, hal_ll_adc_module_num(ADC_MODULE_2), {HAL_LL_ADPCFG_REG_ADDRESS, 0}, ADC2_RC11, ADC2_RC11_AN11, 0},
    #endif
    #ifdef ADC2_RE12_AN12
    {GPIO_PE12, hal_ll_adc_module_num(ADC_MODULE_2), {HAL_LL_ADPCFG_REG_ADDRESS, 0}, ADC2_RE12, ADC2_RE12_AN12, 0},
    #endif
    #ifdef ADC2_RE13_AN13
    {GPIO_PE13, hal_ll_adc_module_num(ADC_MODULE_2), {HAL_LL_ADPCFG_REG_ADDRESS, 0}, ADC2_RE13, ADC2_RE13_AN13, 0},
    #endif
    #ifdef ADC2_RE14_AN14
    {GPIO_PE14, hal_ll_adc_module_num(ADC_MODULE_2), {HAL_LL_ADPCFG_REG_ADDRESS, 0}, ADC2_RE14, ADC2_RE14_AN14, 0},
    #endif
    #ifdef ADC2_RE15_AN15
    {GPIO_PE15, hal_ll_adc_module_num(ADC_MODULE_2), {HAL_LL_ADPCFG_REG_ADDRESS, 0}, ADC2_RE15, ADC2_RE15_AN15, 0},
    #endif
    #ifdef ADC2_RG6_AN19
    {GPIO_PG6, hal_ll_adc_module_num(ADC_MODULE_2), {HAL_LL_ADPCFG_REG_ADDRESS, 0}, ADC2_RG6, ADC2_RG6_AN19, 0},
    #endif
    #ifdef ADC2_RG7_AN18
    {GPIO_PG7, hal_ll_adc_module_num(ADC_MODULE_2), {HAL_LL_ADPCFG_REG_ADDRESS, 0}, ADC2_RG7, ADC2_RG7_AN18, 0},
    #endif
    #ifdef ADC2_RG8_AN17
    {GPIO_PG8, hal_ll_adc_module_num(ADC_MODULE_2), {HAL_LL_ADPCFG_REG_ADDRESS, 0}, ADC2_RG8, ADC2_RG8_AN17, 0},
    #endif
    #ifdef ADC2_RG9_AN16
    {GPIO_PG9, hal_ll_adc_module_num(ADC_MODULE_2), {HAL_LL_ADPCFG_REG_ADDRESS, 0}, ADC2_RG9, ADC2_RG9_AN16, 0},
    #endif
    #ifdef ADC1_RA14_AN46
    {GPIO_PA14, hal_ll_adc_module_num(ADC_MODULE_1), {HAL_LL_ADPCFG_REG_ADDRESS, 0}, ADC1_RA14, ADC1_RA14_AN46, 0},
    #endif
    #ifdef ADC1_RA15_AN47
    {GPIO_PA15, hal_ll_adc_module_num(ADC_MODULE_1), {HAL_LL_ADPCFG_REG_ADDRESS, 0}, ADC1_RA15, ADC1_RA15_AN47, 0},
    #endif
    #ifdef ADC1_RD14_AN38
    {GPIO_PD14, hal_ll_adc_module_num(ADC_MODULE_1), {HAL_LL_ADPCFG_REG_ADDRESS, 0}, ADC1_RD14, ADC1_RD14_AN38, 0},
    #endif
    #ifdef ADC1_RD15_AN39
    {GPIO_PD15, hal_ll_adc_module_num(ADC_MODULE_1), {HAL_LL_ADPCFG_REG_ADDRESS, 0}, ADC1_RD15, ADC1_RD15_AN39, 0},
    #endif
    #ifdef ADC1_RE0_AN40
    {GPIO_PE0, hal_ll_adc_module_num(ADC_MODULE_1), {HAL_LL_ADPCFG_REG_ADDRESS, 0}, ADC1_RE0, ADC1_RE0_AN40, 0},
    #endif
    #ifdef ADC1_RE1_AN41
    {GPIO_PE1, hal_ll_adc_module_num(ADC_MODULE_1), {HAL_LL_ADPCFG_REG_ADDRESS, 0}, ADC1_RE1, ADC1_RE1_AN41, 0},
    #endif
    #ifdef ADC1_RE8_AN21
    {GPIO_PE8, hal_ll_adc_module_num(ADC_MODULE_1), {HAL_LL_ADPCFG_REG_ADDRESS, 0}, ADC1_RE8, ADC1_RE8_AN21, 0},
    #endif
    #ifdef ADC1_RE9_AN20
    {GPIO_PE9, hal_ll_adc_module_num(ADC_MODULE_1), {HAL_LL_ADPCFG_REG_ADDRESS, 0}, ADC1_RE9, ADC1_RE9_AN20, 0},
    #endif
    #ifdef ADC1_RF10_AN34
    {GPIO_PF10, hal_ll_adc_module_num(ADC_MODULE_1), {HAL_LL_ADPCFG_REG_ADDRESS, 0}, ADC1_RF10, ADC1_RF10_AN34, 0},
    #endif
    #ifdef ADC1_RF12_AN37
    {GPIO_PF12, hal_ll_adc_module_num(ADC_MODULE_1), {HAL_LL_ADPCFG_REG_ADDRESS, 0}, ADC1_RF12, ADC1_RF12_AN37, 0},
    #endif
    #ifdef ADC1_RF13_AN36
    {GPIO_PF13, hal_ll_adc_module_num(ADC_MODULE_1), {HAL_LL_ADPCFG_REG_ADDRESS, 0}, ADC1_RF13, ADC1_RF13_AN36, 0},
    #endif
    #ifdef ADC1_RF4_AN44
    {GPIO_PF4, hal_ll_adc_module_num(ADC_MODULE_1), {HAL_LL_ADPCFG_REG_ADDRESS, 0}, ADC1_RF4, ADC1_RF4_AN44, 0},
    #endif
    #ifdef ADC1_RF5_AN45
    {GPIO_PF5, hal_ll_adc_module_num(ADC_MODULE_1), {HAL_LL_ADPCFG_REG_ADDRESS, 0}, ADC1_RF5, ADC1_RF5_AN45, 0},
    #endif
    #ifdef ADC1_RF9_AN33
    {GPIO_PF9, hal_ll_adc_module_num(ADC_MODULE_1), {HAL_LL_ADPCFG_REG_ADDRESS, 0}, ADC1_RF9, ADC1_RF9_AN33, 0},
    #endif
    #ifdef ADC1_RG10_AN22
    {GPIO_PG10, hal_ll_adc_module_num(ADC_MODULE_1), {HAL_LL_ADPCFG_REG_ADDRESS, 0}, ADC1_RG10, ADC1_RG10_AN22, 0},
    #endif
    #ifdef ADC1_RG11_AN35
    {GPIO_PG11, hal_ll_adc_module_num(ADC_MODULE_1), {HAL_LL_ADPCFG_REG_ADDRESS, 0}, ADC1_RG11, ADC1_RG11_AN35, 0},
    #endif
    #ifdef ADC1_RG15_AN23
    {GPIO_PG15, hal_ll_adc_module_num(ADC_MODULE_1), {HAL_LL_ADPCFG_REG_ADDRESS, 0}, ADC1_RG15, ADC1_RG15_AN23, 0},
    #endif
    #ifdef ADC1_RG2_AN42
    {GPIO_PG2, hal_ll_adc_module_num(ADC_MODULE_1), {HAL_LL_ADPCFG_REG_ADDRESS, 0}, ADC1_RG2, ADC1_RG2_AN42, 0},
    #endif
    #ifdef ADC1_RG3_AN43
    {GPIO_PG3, hal_ll_adc_module_num(ADC_MODULE_1), {HAL_LL_ADPCFG_REG_ADDRESS, 0}, ADC1_RG3, ADC1_RG3_AN43, 0},
    #endif
    #ifdef ADC2_RE8_AN21
    {GPIO_PE8, hal_ll_adc_module_num(ADC_MODULE_2), {HAL_LL_ADPCFG_REG_ADDRESS, 0}, ADC2_RE8, ADC2_RE8_AN21, 0},
    #endif
    #ifdef ADC2_RE9_AN20
    {GPIO_PE9, hal_ll_adc_module_num(ADC_MODULE_2), {HAL_LL_ADPCFG_REG_ADDRESS, 0}, ADC2_RE9, ADC2_RE9_AN20, 0},
    #endif
    #ifdef ADC2_RG10_AN22
    {GPIO_PG10, hal_ll_adc_module_num(ADC_MODULE_2), {HAL_LL_ADPCFG_REG_ADDRESS, 0}, ADC2_RG10, ADC2_RG10_AN22, 0},
    #endif
    #ifdef ADC2_RG15_AN23
    {GPIO_PG15, hal_ll_adc_module_num(ADC_MODULE_2), {HAL_LL_ADPCFG_REG_ADDRESS, 0}, ADC2_RG15, ADC2_RG15_AN23, 0},
    #endif
    #ifdef ADC1_RA2_AN2
    {GPIO_PA2, hal_ll_adc_module_num(ADC_MODULE_1), {HAL_LL_ADPCFG_REG_ADDRESS, 0}, ADC1_RA2, ADC1_RA2_AN2, 0},
    #endif
    #ifdef ADC1_RB0_AN3
    {GPIO_PB0, hal_ll_adc_module_num(ADC_MODULE_1), {HAL_LL_ADPCFG_REG_ADDRESS, 0}, ADC1_RB0, ADC1_RB0_AN3, 0},
    #endif
    #ifdef ADC1_RB1_AN6
    {GPIO_PB1, hal_ll_adc_module_num(ADC_MODULE_1), {HAL_LL_ADPCFG_REG_ADDRESS, 0}, ADC1_RB1, ADC1_RB1_AN6, 0},
    #endif
    #ifdef ADC1_RB2_AN7
    {GPIO_PB2, hal_ll_adc_module_num(ADC_MODULE_1), {HAL_LL_ADPCFG_REG_ADDRESS, 0}, ADC1_RB2, ADC1_RB2_AN7, 0},
    #endif
    #ifdef ADC1_RB3_AN18
    {GPIO_PB3, hal_ll_adc_module_num(ADC_MODULE_1), {HAL_LL_ADPCFG_REG_ADDRESS, 0}, ADC1_RB3, ADC1_RB3_AN18, 0},
    #endif
    #ifdef ADC1_RB5_AN19
    {GPIO_PB5, hal_ll_adc_module_num(ADC_MODULE_1), {HAL_LL_ADPCFG_REG_ADDRESS, 0}, ADC1_RB5, ADC1_RB5_AN19, 0},
    #endif
    #ifdef ADC1_RB6_AN20
    {GPIO_PB6, hal_ll_adc_module_num(ADC_MODULE_1), {HAL_LL_ADPCFG_REG_ADDRESS, 0}, ADC1_RB6, ADC1_RB6_AN20, 0},
    #endif
    #ifdef ADC1_RB7_AN21
    {GPIO_PB7, hal_ll_adc_module_num(ADC_MODULE_1), {HAL_LL_ADPCFG_REG_ADDRESS, 0}, ADC1_RB7, ADC1_RB7_AN21, 0},
    #endif
    #ifdef ADC1_RB9_AN4
    {GPIO_PB9, hal_ll_adc_module_num(ADC_MODULE_1), {HAL_LL_ADPCFG_REG_ADDRESS, 0}, ADC1_RB9, ADC1_RB9_AN4, 0},
    #endif
    #ifdef ADC1_RC1_AN8
    {GPIO_PC1, hal_ll_adc_module_num(ADC_MODULE_1), {HAL_LL_ADPCFG_REG_ADDRESS, 0}, ADC1_RC1, ADC1_RC1_AN8, 0},
    #endif
    #ifdef ADC1_RC10_AN10
    {GPIO_PC10, hal_ll_adc_module_num(ADC_MODULE_1), {HAL_LL_ADPCFG_REG_ADDRESS, 0}, ADC1_RC10, ADC1_RC10_AN10, 0},
    #endif
    #ifdef ADC1_RC12_AN14
    {GPIO_PC12, hal_ll_adc_module_num(ADC_MODULE_1), {HAL_LL_ADPCFG_REG_ADDRESS, 0}, ADC1_RC12, ADC1_RC12_AN14, 0},
    #endif
    #ifdef ADC1_RC2_AN9
    {GPIO_PC2, hal_ll_adc_module_num(ADC_MODULE_1), {HAL_LL_ADPCFG_REG_ADDRESS, 0}, ADC1_RC2, ADC1_RC2_AN9, 0},
    #endif
    #ifdef ADC1_RC6_AN17
    {GPIO_PC6, hal_ll_adc_module_num(ADC_MODULE_1), {HAL_LL_ADPCFG_REG_ADDRESS, 0}, ADC1_RC6, ADC1_RC6_AN17, 0},
    #endif
    #ifdef ADC1_RC9_AN11
    {GPIO_PC9, hal_ll_adc_module_num(ADC_MODULE_1), {HAL_LL_ADPCFG_REG_ADDRESS, 0}, ADC1_RC9, ADC1_RC9_AN11, 0},
    #endif
    #ifdef ADC1_RD13_AN13
    {GPIO_PD13, hal_ll_adc_module_num(ADC_MODULE_1), {HAL_LL_ADPCFG_REG_ADDRESS, 0}, ADC1_RD13, ADC1_RD13_AN13, 0},
    #endif
    #ifdef ADC1_RD2_AN16
    {GPIO_PD2, hal_ll_adc_module_num(ADC_MODULE_1), {HAL_LL_ADPCFG_REG_ADDRESS, 0}, ADC1_RD2, ADC1_RD2_AN16, 0},
    #endif
    #ifdef ADC1_RD5_AN12
    {GPIO_PD5, hal_ll_adc_module_num(ADC_MODULE_1), {HAL_LL_ADPCFG_REG_ADDRESS, 0}, ADC1_RD5, ADC1_RD5_AN12, 0},
    #endif
    #ifdef ADC1_RD7_AN15
    {GPIO_PD7, hal_ll_adc_module_num(ADC_MODULE_1), {HAL_LL_ADPCFG_REG_ADDRESS, 0}, ADC1_RD7, ADC1_RD7_AN15, 0},
    #endif
    #ifdef ADC1_RD8_AN5
    {GPIO_PD8, hal_ll_adc_module_num(ADC_MODULE_1), {HAL_LL_ADPCFG_REG_ADDRESS, 0}, ADC1_RD8, ADC1_RD8_AN5, 0},
    #endif
    #ifdef ADC1_RB10_AN5
    {GPIO_PB10, hal_ll_adc_module_num(ADC_MODULE_1), {HAL_LL_ADPCFG_REG_ADDRESS, 0}, ADC1_RB10, ADC1_RB10_AN5, 0},
    #endif
    #ifdef ADC1_RB3_AN8
    {GPIO_PB3, hal_ll_adc_module_num(ADC_MODULE_1), {HAL_LL_ADPCFG_REG_ADDRESS, 0}, ADC1_RB3, ADC1_RB3_AN8, 0},
    #endif
    #ifdef ADC1_RB5_AN9
    {GPIO_PB5, hal_ll_adc_module_num(ADC_MODULE_1), {HAL_LL_ADPCFG_REG_ADDRESS, 0}, ADC1_RB5, ADC1_RB5_AN9, 0},
    #endif
    #ifdef ADC1_RB6_AN10
    {GPIO_PB6, hal_ll_adc_module_num(ADC_MODULE_1), {HAL_LL_ADPCFG_REG_ADDRESS, 0}, ADC1_RB6, ADC1_RB6_AN10, 0},
    #endif
    #ifdef ADC1_RB7_AN11
    {GPIO_PB7, hal_ll_adc_module_num(ADC_MODULE_1), {HAL_LL_ADPCFG_REG_ADDRESS, 0}, ADC1_RB7, ADC1_RB7_AN11, 0},
    #endif
    #ifdef ADC1_RC11_AN12
    {GPIO_PC11, hal_ll_adc_module_num(ADC_MODULE_1), {HAL_LL_ADPCFG_REG_ADDRESS, 0}, ADC1_RC11, ADC1_RC11_AN12, 0},
    #endif
    #ifdef ADC1_RB0_AN0
    {GPIO_PB0, hal_ll_adc_module_num(ADC_MODULE_1), {HAL_LL_ADPCFG_REG_ADDRESS, 0}, ADC1_RB0, ADC1_RB0_AN0, 0},
    #endif
    #ifdef ADC1_RB1_AN1
    {GPIO_PB1, hal_ll_adc_module_num(ADC_MODULE_1), {HAL_LL_ADPCFG_REG_ADDRESS, 0}, ADC1_RB1, ADC1_RB1_AN1, 0},
    #endif
    #ifdef ADC1_RB10_AN10
    {GPIO_PB10, hal_ll_adc_module_num(ADC_MODULE_1), {HAL_LL_ADPCFG_REG_ADDRESS, 0}, ADC1_RB10, ADC1_RB10_AN10, 0},
    #endif
    #ifdef ADC1_RB11_AN11
    {GPIO_PB11, hal_ll_adc_module_num(ADC_MODULE_1), {HAL_LL_ADPCFG_REG_ADDRESS, 0}, ADC1_RB11, ADC1_RB11_AN11, 0},
    #endif
    #ifdef ADC1_RB12_AN12
    {GPIO_PB12, hal_ll_adc_module_num(ADC_MODULE_1), {HAL_LL_ADPCFG_REG_ADDRESS, 0}, ADC1_RB12, ADC1_RB12_AN12, 0},
    #endif
    #ifdef ADC1_RB13_AN13
    {GPIO_PB13, hal_ll_adc_module_num(ADC_MODULE_1), {HAL_LL_ADPCFG_REG_ADDRESS, 0}, ADC1_RB13, ADC1_RB13_AN13, 0},
    #endif
    #ifdef ADC1_RB14_AN14
    {GPIO_PB14, hal_ll_adc_module_num(ADC_MODULE_1), {HAL_LL_ADPCFG_REG_ADDRESS, 0}, ADC1_RB14, ADC1_RB14_AN14, 0},
    #endif
    #ifdef ADC1_RB15_AN15
    {GPIO_PB15, hal_ll_adc_module_num(ADC_MODULE_1), {HAL_LL_ADPCFG_REG_ADDRESS, 0}, ADC1_RB15, ADC1_RB15_AN15, 0},
    #endif
    #ifdef ADC1_RB2_AN2
    {GPIO_PB2, hal_ll_adc_module_num(ADC_MODULE_1), {HAL_LL_ADPCFG_REG_ADDRESS, 0}, ADC1_RB2, ADC1_RB2_AN2, 0},
    #endif
    #ifdef ADC1_RB3_AN3
    {GPIO_PB3, hal_ll_adc_module_num(ADC_MODULE_1), {HAL_LL_ADPCFG_REG_ADDRESS, 0}, ADC1_RB3, ADC1_RB3_AN3, 0},
    #endif
    #ifdef ADC1_RB4_AN4
    {GPIO_PB4, hal_ll_adc_module_num(ADC_MODULE_1), {HAL_LL_ADPCFG_REG_ADDRESS, 0}, ADC1_RB4, ADC1_RB4_AN4, 0},
    #endif
    #ifdef ADC1_RB5_AN5
    {GPIO_PB5, hal_ll_adc_module_num(ADC_MODULE_1), {HAL_LL_ADPCFG_REG_ADDRESS, 0}, ADC1_RB5, ADC1_RB5_AN5, 0},
    #endif
    #ifdef ADC1_RB6_AN6
    {GPIO_PB6, hal_ll_adc_module_num(ADC_MODULE_1), {HAL_LL_ADPCFG_REG_ADDRESS, 0}, ADC1_RB6, ADC1_RB6_AN6, 0},
    #endif
    #ifdef ADC1_RB7_AN7
    {GPIO_PB7, hal_ll_adc_module_num(ADC_MODULE_1), {HAL_LL_ADPCFG_REG_ADDRESS, 0}, ADC1_RB7, ADC1_RB7_AN7, 0},
    #endif
    #ifdef ADC1_RB8_AN8
    {GPIO_PB8, hal_ll_adc_module_num(ADC_MODULE_1), {HAL_LL_ADPCFG_REG_ADDRESS, 0}, ADC1_RB8, ADC1_RB8_AN8, 0},
    #endif
    #ifdef ADC1_RB9_AN9
    {GPIO_PB9, hal_ll_adc_module_num(ADC_MODULE_1), {HAL_LL_ADPCFG_REG_ADDRESS, 0}, ADC1_RB9, ADC1_RB9_AN9, 0},
    #endif
    #ifdef ADC1_RE0_AN24
    {GPIO_PE0, hal_ll_adc_module_num(ADC_MODULE_1), {HAL_LL_ADPCFG_REG_ADDRESS, 0}, ADC1_RE0, ADC1_RE0_AN24, 0},
    #endif
    #ifdef ADC1_RE1_AN25
    {GPIO_PE1, hal_ll_adc_module_num(ADC_MODULE_1), {HAL_LL_ADPCFG_REG_ADDRESS, 0}, ADC1_RE1, ADC1_RE1_AN25, 0},
    #endif
    #ifdef ADC1_RE2_AN26
    {GPIO_PE2, hal_ll_adc_module_num(ADC_MODULE_1), {HAL_LL_ADPCFG_REG_ADDRESS, 0}, ADC1_RE2, ADC1_RE2_AN26, 0},
    #endif
    #ifdef ADC1_RE3_AN27
    {GPIO_PE3, hal_ll_adc_module_num(ADC_MODULE_1), {HAL_LL_ADPCFG_REG_ADDRESS, 0}, ADC1_RE3, ADC1_RE3_AN27, 0},
    #endif
    #ifdef ADC1_RE4_AN28
    {GPIO_PE4, hal_ll_adc_module_num(ADC_MODULE_1), {HAL_LL_ADPCFG_REG_ADDRESS, 0}, ADC1_RE4, ADC1_RE4_AN28, 0},
    #endif
    #ifdef ADC1_RE5_AN29
    {GPIO_PE5, hal_ll_adc_module_num(ADC_MODULE_1), {HAL_LL_ADPCFG_REG_ADDRESS, 0}, ADC1_RE5, ADC1_RE5_AN29, 0},
    #endif
    #ifdef ADC1_RE6_AN30
    {GPIO_PE6, hal_ll_adc_module_num(ADC_MODULE_1), {HAL_LL_ADPCFG_REG_ADDRESS, 0}, ADC1_RE6, ADC1_RE6_AN30, 0},
    #endif
    #ifdef ADC1_RE7_AN31
    {GPIO_PE7, hal_ll_adc_module_num(ADC_MODULE_1), {HAL_LL_ADPCFG_REG_ADDRESS, 0}, ADC1_RE7, ADC1_RE7_AN31, 0},
    #endif
    #ifdef ADC2_RB0_AN0
    {GPIO_PB0, hal_ll_adc_module_num(ADC_MODULE_2), {HAL_LL_ADPCFG_REG_ADDRESS, 0}, ADC2_RB0, ADC2_RB0_AN0, 0},
    #endif
    #ifdef ADC2_RB1_AN1
    {GPIO_PB1, hal_ll_adc_module_num(ADC_MODULE_2), {HAL_LL_ADPCFG_REG_ADDRESS, 0}, ADC2_RB1, ADC2_RB1_AN1, 0},
    #endif
    #ifdef ADC2_RB10_AN10
    {GPIO_PB10, hal_ll_adc_module_num(ADC_MODULE_2), {HAL_LL_ADPCFG_REG_ADDRESS, 0}, ADC2_RB10, ADC2_RB10_AN10, 0},
    #endif
    #ifdef ADC2_RB11_AN11
    {GPIO_PB11, hal_ll_adc_module_num(ADC_MODULE_2), {HAL_LL_ADPCFG_REG_ADDRESS, 0}, ADC2_RB11, ADC2_RB11_AN11, 0},
    #endif
    #ifdef ADC2_RB12_AN12
    {GPIO_PB12, hal_ll_adc_module_num(ADC_MODULE_2), {HAL_LL_ADPCFG_REG_ADDRESS, 0}, ADC2_RB12, ADC2_RB12_AN12, 0},
    #endif
    #ifdef ADC2_RB13_AN13
    {GPIO_PB13, hal_ll_adc_module_num(ADC_MODULE_2), {HAL_LL_ADPCFG_REG_ADDRESS, 0}, ADC2_RB13, ADC2_RB13_AN13, 0},
    #endif
    #ifdef ADC2_RB14_AN14
    {GPIO_PB14, hal_ll_adc_module_num(ADC_MODULE_2), {HAL_LL_ADPCFG_REG_ADDRESS, 0}, ADC2_RB14, ADC2_RB14_AN14, 0},
    #endif
    #ifdef ADC2_RB15_AN15
    {GPIO_PB15, hal_ll_adc_module_num(ADC_MODULE_2), {HAL_LL_ADPCFG_REG_ADDRESS, 0}, ADC2_RB15, ADC2_RB15_AN15, 0},
    #endif
    #ifdef ADC2_RB2_AN2
    {GPIO_PB2, hal_ll_adc_module_num(ADC_MODULE_2), {HAL_LL_ADPCFG_REG_ADDRESS, 0}, ADC2_RB2, ADC2_RB2_AN2, 0},
    #endif
    #ifdef ADC2_RB3_AN3
    {GPIO_PB3, hal_ll_adc_module_num(ADC_MODULE_2), {HAL_LL_ADPCFG_REG_ADDRESS, 0}, ADC2_RB3, ADC2_RB3_AN3, 0},
    #endif
    #ifdef ADC2_RB4_AN4
    {GPIO_PB4, hal_ll_adc_module_num(ADC_MODULE_2), {HAL_LL_ADPCFG_REG_ADDRESS, 0}, ADC2_RB4, ADC2_RB4_AN4, 0},
    #endif
    #ifdef ADC2_RB5_AN5
    {GPIO_PB5, hal_ll_adc_module_num(ADC_MODULE_2), {HAL_LL_ADPCFG_REG_ADDRESS, 0}, ADC2_RB5, ADC2_RB5_AN5, 0},
    #endif
    #ifdef ADC2_RB6_AN6
    {GPIO_PB6, hal_ll_adc_module_num(ADC_MODULE_2), {HAL_LL_ADPCFG_REG_ADDRESS, 0}, ADC2_RB6, ADC2_RB6_AN6, 0},
    #endif
    #ifdef ADC2_RB7_AN7
    {GPIO_PB7, hal_ll_adc_module_num(ADC_MODULE_2), {HAL_LL_ADPCFG_REG_ADDRESS, 0}, ADC2_RB7, ADC2_RB7_AN7, 0},
    #endif
    #ifdef ADC2_RB8_AN8
    {GPIO_PB8, hal_ll_adc_module_num(ADC_MODULE_2), {HAL_LL_ADPCFG_REG_ADDRESS, 0}, ADC2_RB8, ADC2_RB8_AN8, 0},
    #endif
    #ifdef ADC2_RB9_AN9
    {GPIO_PB9, hal_ll_adc_module_num(ADC_MODULE_2), {HAL_LL_ADPCFG_REG_ADDRESS, 0}, ADC2_RB9, ADC2_RB9_AN9, 0},
    #endif
    #ifdef ADC1_RA6_AN22
    {GPIO_PA6, hal_ll_adc_module_num(ADC_MODULE_1), {HAL_LL_ADPCFG_REG_ADDRESS, 0}, ADC1_RA6, ADC1_RA6_AN22, 0},
    #endif
    #ifdef ADC1_RA7_AN23
    {GPIO_PA7, hal_ll_adc_module_num(ADC_MODULE_1), {HAL_LL_ADPCFG_REG_ADDRESS, 0}, ADC1_RA7, ADC1_RA7_AN23, 0},
    #endif
    #ifdef ADC1_RC1_AN16
    {GPIO_PC1, hal_ll_adc_module_num(ADC_MODULE_1), {HAL_LL_ADPCFG_REG_ADDRESS, 0}, ADC1_RC1, ADC1_RC1_AN16, 0},
    #endif
    #ifdef ADC1_RC2_AN17
    {GPIO_PC2, hal_ll_adc_module_num(ADC_MODULE_1), {HAL_LL_ADPCFG_REG_ADDRESS, 0}, ADC1_RC2, ADC1_RC2_AN17, 0},
    #endif
    #ifdef ADC1_RC3_AN18
    {GPIO_PC3, hal_ll_adc_module_num(ADC_MODULE_1), {HAL_LL_ADPCFG_REG_ADDRESS, 0}, ADC1_RC3, ADC1_RC3_AN18, 0},
    #endif
    #ifdef ADC1_RC4_AN19
    {GPIO_PC4, hal_ll_adc_module_num(ADC_MODULE_1), {HAL_LL_ADPCFG_REG_ADDRESS, 0}, ADC1_RC4, ADC1_RC4_AN19, 0},
    #endif
    #ifdef ADC1_RE8_AN20
    {GPIO_PE8, hal_ll_adc_module_num(ADC_MODULE_1), {HAL_LL_ADPCFG_REG_ADDRESS, 0}, ADC1_RE8, ADC1_RE8_AN20, 0},
    #endif
    #ifdef ADC1_RE9_AN21
    {GPIO_PE9, hal_ll_adc_module_num(ADC_MODULE_1), {HAL_LL_ADPCFG_REG_ADDRESS, 0}, ADC1_RE9, ADC1_RE9_AN21, 0},
    #endif
    #ifdef ADC1_RA10_AN56
    {GPIO_PA10, hal_ll_adc_module_num(ADC_MODULE_1), {HAL_LL_ADPCFG_REG_ADDRESS, 0}, ADC1_RA10, ADC1_RA10_AN56, 0},
    #endif
    #ifdef ADC1_RA7_AN55
    {GPIO_PA7, hal_ll_adc_module_num(ADC_MODULE_1), {HAL_LL_ADPCFG_REG_ADDRESS, 0}, ADC1_RA7, ADC1_RA7_AN55, 0},
    #endif
    #ifdef ADC1_RC6_AN53
    {GPIO_PC6, hal_ll_adc_module_num(ADC_MODULE_1), {HAL_LL_ADPCFG_REG_ADDRESS, 0}, ADC1_RC6, ADC1_RC6_AN53, 0},
    #endif
    #ifdef ADC1_RC7_AN52
    {GPIO_PC7, hal_ll_adc_module_num(ADC_MODULE_1), {HAL_LL_ADPCFG_REG_ADDRESS, 0}, ADC1_RC7, ADC1_RC7_AN52, 0},
    #endif
    #ifdef ADC1_RC8_AN51
    {GPIO_PC8, hal_ll_adc_module_num(ADC_MODULE_1), {HAL_LL_ADPCFG_REG_ADDRESS, 0}, ADC1_RC8, ADC1_RC8_AN51, 0},
    #endif
    #ifdef ADC1_RC9_AN54
    {GPIO_PC9, hal_ll_adc_module_num(ADC_MODULE_1), {HAL_LL_ADPCFG_REG_ADDRESS, 0}, ADC1_RC9, ADC1_RC9_AN54, 0},
    #endif
    #ifdef ADC_RA0_AN0
    {GPIO_PA0, hal_ll_adc_module_num(ADC_MODULE), {HAL_LL_ADPCFG_REG_ADDRESS, 0}, ADC_RA0, ADC_RA0_AN0, 0},
    #endif
    #ifdef ADC_RA1_AN1
    {GPIO_PA1, hal_ll_adc_module_num(ADC_MODULE), {HAL_LL_ADPCFG_REG_ADDRESS, 0}, ADC_RA1, ADC_RA1_AN1, 0},
    #endif
    #ifdef ADC_RB0_AN2
    {GPIO_PB0, hal_ll_adc_module_num(ADC_MODULE), {HAL_LL_ADPCFG_REG_ADDRESS, 0}, ADC_RB0, ADC_RB0_AN2, 0},
    #endif
    #ifdef ADC_RB1_AN3
    {GPIO_PB1, hal_ll_adc_module_num(ADC_MODULE), {HAL_LL_ADPCFG_REG_ADDRESS, 0}, ADC_RB1, ADC_RB1_AN3, 0},
    #endif
    #ifdef ADC_RB13_AN11
    {GPIO_PB13, hal_ll_adc_module_num(ADC_MODULE), {HAL_LL_ADPCFG_REG_ADDRESS, 0}, ADC_RB13, ADC_RB13_AN11, 0},
    #endif
    #ifdef ADC_RB14_AN10
    {GPIO_PB14, hal_ll_adc_module_num(ADC_MODULE), {HAL_LL_ADPCFG_REG_ADDRESS, 0}, ADC_RB14, ADC_RB14_AN10, 0},
    #endif
    #ifdef ADC_RB15_AN9
    {GPIO_PB15, hal_ll_adc_module_num(ADC_MODULE), {HAL_LL_ADPCFG_REG_ADDRESS, 0}, ADC_RB15, ADC_RB15_AN9, 0},
    #endif
    #ifdef ADC_RB2_AN4
    {GPIO_PB2, hal_ll_adc_module_num(ADC_MODULE), {HAL_LL_ADPCFG_REG_ADDRESS, 0}, ADC_RB2, ADC_RB2_AN4, 0},
    #endif
    #ifdef ADC_RB3_AN5
    {GPIO_PB3, hal_ll_adc_module_num(ADC_MODULE), {HAL_LL_ADPCFG_REG_ADDRESS, 0}, ADC_RB3, ADC_RB3_AN5, 0},
    #endif
    #ifdef ADC_RC0_AN6
    {GPIO_PC0, hal_ll_adc_module_num(ADC_MODULE), {HAL_LL_ADPCFG_REG_ADDRESS, 0}, ADC_RC0, ADC_RC0_AN6, 0},
    #endif
    #ifdef ADC_RC1_AN7
    {GPIO_PC1, hal_ll_adc_module_num(ADC_MODULE), {HAL_LL_ADPCFG_REG_ADDRESS, 0}, ADC_RC1, ADC_RC1_AN7, 0},
    #endif
    #ifdef ADC_RC2_AN8
    {GPIO_PC2, hal_ll_adc_module_num(ADC_MODULE), {HAL_LL_ADPCFG_REG_ADDRESS, 0}, ADC_RC2, ADC_RC2_AN8, 0},
    #endif
    #ifdef ADC_RC1_AN16
    {GPIO_PC1, hal_ll_adc_module_num(ADC_MODULE), {HAL_LL_ADPCFG_REG_ADDRESS, 0}, ADC_RC1, ADC_RC1_AN16, 0},
    #endif
    #ifdef ADC_RC2_AN17
    {GPIO_PC2, hal_ll_adc_module_num(ADC_MODULE), {HAL_LL_ADPCFG_REG_ADDRESS, 0}, ADC_RC2, ADC_RC2_AN17, 0},
    #endif
    #ifdef ADC_RA12_AN20
    {GPIO_PA12, hal_ll_adc_module_num(ADC_MODULE), {HAL_LL_ADPCFG_REG_ADDRESS, 0}, ADC_RA12, ADC_RA12_AN20, 0},
    #endif
    #ifdef ADC_RA13_AN21
    {GPIO_PA13, hal_ll_adc_module_num(ADC_MODULE), {HAL_LL_ADPCFG_REG_ADDRESS, 0}, ADC_RA13, ADC_RA13_AN21, 0},
    #endif
    #ifdef ADC_RA6_AN22
    {GPIO_PA6, hal_ll_adc_module_num(ADC_MODULE), {HAL_LL_ADPCFG_REG_ADDRESS, 0}, ADC_RA6, ADC_RA6_AN22, 0},
    #endif
    #ifdef ADC_RA7_AN23
    {GPIO_PA7, hal_ll_adc_module_num(ADC_MODULE), {HAL_LL_ADPCFG_REG_ADDRESS, 0}, ADC_RA7, ADC_RA7_AN23, 0},
    #endif
    #ifdef ADC_RC3_AN18
    {GPIO_PC3, hal_ll_adc_module_num(ADC_MODULE), {HAL_LL_ADPCFG_REG_ADDRESS, 0}, ADC_RC3, ADC_RC3_AN18, 0},
    #endif
    #ifdef ADC_RC4_AN19
    {GPIO_PC4, hal_ll_adc_module_num(ADC_MODULE), {HAL_LL_ADPCFG_REG_ADDRESS, 0}, ADC_RC4, ADC_RC4_AN19, 0},
    #endif
    #ifdef ADC_RE0_AN24
    {GPIO_PE0, hal_ll_adc_module_num(ADC_MODULE), {HAL_LL_ADPCFG_REG_ADDRESS, 0}, ADC_RE0, ADC_RE0_AN24, 0},
    #endif
    #ifdef ADC_RE1_AN25
    {GPIO_PE1, hal_ll_adc_module_num(ADC_MODULE), {HAL_LL_ADPCFG_REG_ADDRESS, 0}, ADC_RE1, ADC_RE1_AN25, 0},
    #endif
    #ifdef ADC_RE2_AN26
    {GPIO_PE2, hal_ll_adc_module_num(ADC_MODULE), {HAL_LL_ADPCFG_REG_ADDRESS, 0}, ADC_RE2, ADC_RE2_AN26, 0},
    #endif
    #ifdef ADC_RE3_AN27
    {GPIO_PE3, hal_ll_adc_module_num(ADC_MODULE), {HAL_LL_ADPCFG_REG_ADDRESS, 0}, ADC_RE3, ADC_RE3_AN27, 0},
    #endif
    #ifdef ADC_RE4_AN28
    {GPIO_PE4, hal_ll_adc_module_num(ADC_MODULE), {HAL_LL_ADPCFG_REG_ADDRESS, 0}, ADC_RE4, ADC_RE4_AN28, 0},
    #endif
    #ifdef ADC_RE5_AN29
    {GPIO_PE5, hal_ll_adc_module_num(ADC_MODULE), {HAL_LL_ADPCFG_REG_ADDRESS, 0}, ADC_RE5, ADC_RE5_AN29, 0},
    #endif
    #ifdef ADC_RE6_AN30
    {GPIO_PE6, hal_ll_adc_module_num(ADC_MODULE), {HAL_LL_ADPCFG_REG_ADDRESS, 0}, ADC_RE6, ADC_RE6_AN30, 0},
    #endif
    #ifdef ADC_RE7_AN31
    {GPIO_PE7, hal_ll_adc_module_num(ADC_MODULE), {HAL_LL_ADPCFG_REG_ADDRESS, 0}, ADC_RE7, ADC_RE7_AN31, 0},
    #endif
    #ifdef ADC2_RC1_AN16
    {GPIO_PC1, hal_ll_adc_module_num(ADC_MODULE_2), {HAL_LL_ADPCFG_REG_ADDRESS, 0}, ADC2_RC1, ADC2_RC1_AN16, 0},
    #endif
    #ifdef ADC2_RC2_AN17
    {GPIO_PC2, hal_ll_adc_module_num(ADC_MODULE_2), {HAL_LL_ADPCFG_REG_ADDRESS, 0}, ADC2_RC2, ADC2_RC2_AN17, 0},
    #endif
    #ifdef ADC1_RA12_AN20
    {GPIO_PA12, hal_ll_adc_module_num(ADC_MODULE_1), {HAL_LL_ADPCFG_REG_ADDRESS, 0}, ADC1_RA12, ADC1_RA12_AN20, 0},
    #endif
    #ifdef ADC1_RA13_AN21
    {GPIO_PA13, hal_ll_adc_module_num(ADC_MODULE_1), {HAL_LL_ADPCFG_REG_ADDRESS, 0}, ADC1_RA13, ADC1_RA13_AN21, 0},
    #endif
    #ifdef ADC2_RA12_AN20
    {GPIO_PA12, hal_ll_adc_module_num(ADC_MODULE_2), {HAL_LL_ADPCFG_REG_ADDRESS, 0}, ADC2_RA12, ADC2_RA12_AN20, 0},
    #endif
    #ifdef ADC2_RA13_AN21
    {GPIO_PA13, hal_ll_adc_module_num(ADC_MODULE_2), {HAL_LL_ADPCFG_REG_ADDRESS, 0}, ADC2_RA13, ADC2_RA13_AN21, 0},
    #endif
    #ifdef ADC2_RA6_AN22
    {GPIO_PA6, hal_ll_adc_module_num(ADC_MODULE_2), {HAL_LL_ADPCFG_REG_ADDRESS, 0}, ADC2_RA6, ADC2_RA6_AN22, 0},
    #endif
    #ifdef ADC2_RA7_AN23
    {GPIO_PA7, hal_ll_adc_module_num(ADC_MODULE_2), {HAL_LL_ADPCFG_REG_ADDRESS, 0}, ADC2_RA7, ADC2_RA7_AN23, 0},
    #endif
    #ifdef ADC2_RC3_AN18
    {GPIO_PC3, hal_ll_adc_module_num(ADC_MODULE_2), {HAL_LL_ADPCFG_REG_ADDRESS, 0}, ADC2_RC3, ADC2_RC3_AN18, 0},
    #endif
    #ifdef ADC2_RC4_AN19
    {GPIO_PC4, hal_ll_adc_module_num(ADC_MODULE_2), {HAL_LL_ADPCFG_REG_ADDRESS, 0}, ADC2_RC4, ADC2_RC4_AN19, 0},
    #endif
    #ifdef ADC2_RE0_AN24
    {GPIO_PE0, hal_ll_adc_module_num(ADC_MODULE_2), {HAL_LL_ADPCFG_REG_ADDRESS, 0}, ADC2_RE0, ADC2_RE0_AN24, 0},
    #endif
    #ifdef ADC2_RE1_AN25
    {GPIO_PE1, hal_ll_adc_module_num(ADC_MODULE_2), {HAL_LL_ADPCFG_REG_ADDRESS, 0}, ADC2_RE1, ADC2_RE1_AN25, 0},
    #endif
    #ifdef ADC2_RE2_AN26
    {GPIO_PE2, hal_ll_adc_module_num(ADC_MODULE_2), {HAL_LL_ADPCFG_REG_ADDRESS, 0}, ADC2_RE2, ADC2_RE2_AN26, 0},
    #endif
    #ifdef ADC2_RE3_AN27
    {GPIO_PE3, hal_ll_adc_module_num(ADC_MODULE_2), {HAL_LL_ADPCFG_REG_ADDRESS, 0}, ADC2_RE3, ADC2_RE3_AN27, 0},
    #endif
    #ifdef ADC2_RE4_AN28
    {GPIO_PE4, hal_ll_adc_module_num(ADC_MODULE_2), {HAL_LL_ADPCFG_REG_ADDRESS, 0}, ADC2_RE4, ADC2_RE4_AN28, 0},
    #endif
    #ifdef ADC2_RE5_AN29
    {GPIO_PE5, hal_ll_adc_module_num(ADC_MODULE_2), {HAL_LL_ADPCFG_REG_ADDRESS, 0}, ADC2_RE5, ADC2_RE5_AN29, 0},
    #endif
    #ifdef ADC2_RE6_AN30
    {GPIO_PE6, hal_ll_adc_module_num(ADC_MODULE_2), {HAL_LL_ADPCFG_REG_ADDRESS, 0}, ADC2_RE6, ADC2_RE6_AN30, 0},
    #endif
    #ifdef ADC2_RE7_AN31
    {GPIO_PE7, hal_ll_adc_module_num(ADC_MODULE_2), {HAL_LL_ADPCFG_REG_ADDRESS, 0}, ADC2_RE7, ADC2_RE7_AN31, 0},
    #endif
    #ifdef ADC_RE8_AN20
    {GPIO_PE8, hal_ll_adc_module_num(ADC_MODULE), {HAL_LL_ADPCFG_REG_ADDRESS, 0}, ADC_RE8, ADC_RE8_AN20, 0},
    #endif
    #ifdef ADC_RE9_AN21
    {GPIO_PE9, hal_ll_adc_module_num(ADC_MODULE), {HAL_LL_ADPCFG_REG_ADDRESS, 0}, ADC_RE9, ADC_RE9_AN21, 0},
    #endif
    #ifdef ADC2_RE8_AN20
    {GPIO_PE8, hal_ll_adc_module_num(ADC_MODULE_2), {HAL_LL_ADPCFG_REG_ADDRESS, 0}, ADC2_RE8, ADC2_RE8_AN20, 0},
    #endif
    #ifdef ADC2_RE9_AN21
    {GPIO_PE9, hal_ll_adc_module_num(ADC_MODULE_2), {HAL_LL_ADPCFG_REG_ADDRESS, 0}, ADC2_RE9, ADC2_RE9_AN21, 0},
    #endif
    #ifdef ADC_RA2_AN2
    {GPIO_PA2, hal_ll_adc_module_num(ADC_MODULE), {HAL_LL_ADPCFG_REG_ADDRESS, 0}, ADC_RA2, ADC_RA2_AN2, 0},
    #endif
    #ifdef ADC_RB0_AN3
    {GPIO_PB0, hal_ll_adc_module_num(ADC_MODULE), {HAL_LL_ADPCFG_REG_ADDRESS, 0}, ADC_RB0, ADC_RB0_AN3, 0},
    #endif
    #ifdef ADC_RB1_AN6
    {GPIO_PB1, hal_ll_adc_module_num(ADC_MODULE), {HAL_LL_ADPCFG_REG_ADDRESS, 0}, ADC_RB1, ADC_RB1_AN6, 0},
    #endif
    #ifdef ADC_RB10_AN5
    {GPIO_PB10, hal_ll_adc_module_num(ADC_MODULE), {HAL_LL_ADPCFG_REG_ADDRESS, 0}, ADC_RB10, ADC_RB10_AN5, 0},
    #endif
    #ifdef ADC_RB2_AN7
    {GPIO_PB2, hal_ll_adc_module_num(ADC_MODULE), {HAL_LL_ADPCFG_REG_ADDRESS, 0}, ADC_RB2, ADC_RB2_AN7, 0},
    #endif
    #ifdef ADC_RB9_AN4
    {GPIO_PB9, hal_ll_adc_module_num(ADC_MODULE), {HAL_LL_ADPCFG_REG_ADDRESS, 0}, ADC_RB9, ADC_RB9_AN4, 0},
    #endif
    #ifdef ADC_RC1_AN8
    {GPIO_PC1, hal_ll_adc_module_num(ADC_MODULE), {HAL_LL_ADPCFG_REG_ADDRESS, 0}, ADC_RC1, ADC_RC1_AN8, 0},
    #endif
    #ifdef ADC_RC10_AN10
    {GPIO_PC10, hal_ll_adc_module_num(ADC_MODULE), {HAL_LL_ADPCFG_REG_ADDRESS, 0}, ADC_RC10, ADC_RC10_AN10, 0},
    #endif
    #ifdef ADC_RC2_AN9
    {GPIO_PC2, hal_ll_adc_module_num(ADC_MODULE), {HAL_LL_ADPCFG_REG_ADDRESS, 0}, ADC_RC2, ADC_RC2_AN9, 0},
    #endif
    #ifdef ADC_RC9_AN11
    {GPIO_PC9, hal_ll_adc_module_num(ADC_MODULE), {HAL_LL_ADPCFG_REG_ADDRESS, 0}, ADC_RC9, ADC_RC9_AN11, 0},
    #endif
    #ifdef ADC_RA4_AN10
    {GPIO_PA4, hal_ll_adc_module_num(ADC_MODULE), {HAL_LL_ADPCFG_REG_ADDRESS, 0}, ADC_RA4, ADC_RA4_AN10, 0},
    #endif
    #ifdef ADC_RB4_AN9
    {GPIO_PB4, hal_ll_adc_module_num(ADC_MODULE), {HAL_LL_ADPCFG_REG_ADDRESS, 0}, ADC_RB4, ADC_RB4_AN9, 0},
    #endif
    #ifdef ADC_RC3_AN11
    {GPIO_PC3, hal_ll_adc_module_num(ADC_MODULE), {HAL_LL_ADPCFG_REG_ADDRESS, 0}, ADC_RC3, ADC_RC3_AN11, 0},
    #endif
    #ifdef ADC_RC4_AN12
    {GPIO_PC4, hal_ll_adc_module_num(ADC_MODULE), {HAL_LL_ADPCFG_REG_ADDRESS, 0}, ADC_RC4, ADC_RC4_AN12, 0},
    #endif
    #ifdef ADC_RC5_AN15
    {GPIO_PC5, hal_ll_adc_module_num(ADC_MODULE), {HAL_LL_ADPCFG_REG_ADDRESS, 0}, ADC_RC5, ADC_RC5_AN15, 0},
    #endif
    #ifdef ADC1_RA2_AN13
    {GPIO_PA2, hal_ll_adc_module_num(ADC_MODULE_1), {HAL_LL_ADPCFG_REG_ADDRESS, 0}, ADC1_RA2, ADC1_RA2_AN13, 0},
    #endif
    #ifdef ADC1_RA3_AN14
    {GPIO_PA3, hal_ll_adc_module_num(ADC_MODULE_1), {HAL_LL_ADPCFG_REG_ADDRESS, 0}, ADC1_RA3, ADC1_RA3_AN14, 0},
    #endif
    #ifdef ADC1_RB13_AN11
    {GPIO_PB13, hal_ll_adc_module_num(ADC_MODULE_1), {HAL_LL_ADPCFG_REG_ADDRESS, 0}, ADC1_RB13, ADC1_RB13_AN11, 0},
    #endif
    #ifdef ADC1_RB14_AN10
    {GPIO_PB14, hal_ll_adc_module_num(ADC_MODULE_1), {HAL_LL_ADPCFG_REG_ADDRESS, 0}, ADC1_RB14, ADC1_RB14_AN10, 0},
    #endif
    #ifdef ADC1_RB15_AN9
    {GPIO_PB15, hal_ll_adc_module_num(ADC_MODULE_1), {HAL_LL_ADPCFG_REG_ADDRESS, 0}, ADC1_RB15, ADC1_RB15_AN9, 0},
    #endif
    #ifdef ADC1_RB4_AN15
    {GPIO_PB4, hal_ll_adc_module_num(ADC_MODULE_1), {HAL_LL_ADPCFG_REG_ADDRESS, 0}, ADC1_RB4, ADC1_RB4_AN15, 0},
    #endif
    #ifdef ADC1_RA4_AN16
    {GPIO_PA4, hal_ll_adc_module_num(ADC_MODULE_1), {HAL_LL_ADPCFG_REG_ADDRESS, 0}, ADC1_RA4, ADC1_RA4_AN16, 0},
    #endif
    #ifdef ADC1_RB5_AN17
    {GPIO_PB5, hal_ll_adc_module_num(ADC_MODULE_1), {HAL_LL_ADPCFG_REG_ADDRESS, 0}, ADC1_RB5, ADC1_RB5_AN17, 0},
    #endif
    #ifdef ADC1_RB6_AN18
    {GPIO_PB6, hal_ll_adc_module_num(ADC_MODULE_1), {HAL_LL_ADPCFG_REG_ADDRESS, 0}, ADC1_RB6, ADC1_RB6_AN18, 0},
    #endif
    #ifdef ADC1_RB7_AN19
    {GPIO_PB7, hal_ll_adc_module_num(ADC_MODULE_1), {HAL_LL_ADPCFG_REG_ADDRESS, 0}, ADC1_RB7, ADC1_RB7_AN19, 0},
    #endif
    #ifdef ADC1_RB8_AN20
    {GPIO_PB8, hal_ll_adc_module_num(ADC_MODULE_1), {HAL_LL_ADPCFG_REG_ADDRESS, 0}, ADC1_RB8, ADC1_RB8_AN20, 0},
    #endif
    #ifdef ADC1_RB9_AN21
    {GPIO_PB9, hal_ll_adc_module_num(ADC_MODULE_1), {HAL_LL_ADPCFG_REG_ADDRESS, 0}, ADC1_RB9, ADC1_RB9_AN21, 0},
    #endif
    #ifdef ADC1_RA6_AN23
    {GPIO_PA6, hal_ll_adc_module_num(ADC_MODULE_1), {HAL_LL_ADPCFG_REG_ADDRESS, 0}, ADC1_RA6, ADC1_RA6_AN23, 0},
    #endif
    #ifdef ADC1_RA7_AN22
    {GPIO_PA7, hal_ll_adc_module_num(ADC_MODULE_1), {HAL_LL_ADPCFG_REG_ADDRESS, 0}, ADC1_RA7, ADC1_RA7_AN22, 0},
    #endif
    #ifdef ADC1_RC4_AN16
    {GPIO_PC4, hal_ll_adc_module_num(ADC_MODULE_1), {HAL_LL_ADPCFG_REG_ADDRESS, 0}, ADC1_RC4, ADC1_RC4_AN16, 0},
    #endif
    #ifdef ADC1_RG6_AN17
    {GPIO_PG6, hal_ll_adc_module_num(ADC_MODULE_1), {HAL_LL_ADPCFG_REG_ADDRESS, 0}, ADC1_RG6, ADC1_RG6_AN17, 0},
    #endif
    #ifdef ADC1_RG8_AN19
    {GPIO_PG8, hal_ll_adc_module_num(ADC_MODULE_1), {HAL_LL_ADPCFG_REG_ADDRESS, 0}, ADC1_RG8, ADC1_RG8_AN19, 0},
    #endif
    #ifdef ADC1_RG9_AN20
    {GPIO_PG9, hal_ll_adc_module_num(ADC_MODULE_1), {HAL_LL_ADPCFG_REG_ADDRESS, 0}, ADC1_RG9, ADC1_RG9_AN20, 0},
    #endif
    #ifdef ADC1_RB12_AN8
    {GPIO_PB12, hal_ll_adc_module_num(ADC_MODULE_1), {HAL_LL_ADPCFG_REG_ADDRESS, 0}, ADC1_RB12, ADC1_RB12_AN8, 0},
    #endif
    #ifdef ADC1_RB13_AN7
    {GPIO_PB13, hal_ll_adc_module_num(ADC_MODULE_1), {HAL_LL_ADPCFG_REG_ADDRESS, 0}, ADC1_RB13, ADC1_RB13_AN7, 0},
    #endif
    #ifdef ADC1_RB14_AN6
    {GPIO_PB14, hal_ll_adc_module_num(ADC_MODULE_1), {HAL_LL_ADPCFG_REG_ADDRESS, 0}, ADC1_RB14, ADC1_RB14_AN6, 0},
    #endif
    #ifdef ADC1_RC0_AN10
    {GPIO_PC0, hal_ll_adc_module_num(ADC_MODULE_1), {HAL_LL_ADPCFG_REG_ADDRESS, 0}, ADC1_RC0, ADC1_RC0_AN10, 0},
    #endif
    #ifdef ADC1_RC1_AN11
    {GPIO_PC1, hal_ll_adc_module_num(ADC_MODULE_1), {HAL_LL_ADPCFG_REG_ADDRESS, 0}, ADC1_RC1, ADC1_RC1_AN11, 0},
    #endif
    #ifdef ADC1_RC2_AN12
    {GPIO_PC2, hal_ll_adc_module_num(ADC_MODULE_1), {HAL_LL_ADPCFG_REG_ADDRESS, 0}, ADC1_RC2, ADC1_RC2_AN12, 0},
    #endif
    #ifdef ADC1_RC3_AN13
    {GPIO_PC3, hal_ll_adc_module_num(ADC_MODULE_1), {HAL_LL_ADPCFG_REG_ADDRESS, 0}, ADC1_RC3, ADC1_RC3_AN13, 0},
    #endif
    #ifdef ADC1_RD0_AN43
    {GPIO_PD0, hal_ll_adc_module_num(ADC_MODULE_1), {HAL_LL_ADPCFG_REG_ADDRESS, 0}, ADC1_RD0, ADC1_RD0_AN43, 0},
    #endif
    #ifdef ADC1_RD1_AN35
    {GPIO_PD1, hal_ll_adc_module_num(ADC_MODULE_1), {HAL_LL_ADPCFG_REG_ADDRESS, 0}, ADC1_RD1, ADC1_RD1_AN35, 0},
    #endif
    #ifdef ADC1_RD10_AN41
    {GPIO_PD10, hal_ll_adc_module_num(ADC_MODULE_1), {HAL_LL_ADPCFG_REG_ADDRESS, 0}, ADC1_RD10, ADC1_RD10_AN41, 0},
    #endif
    #ifdef ADC1_RD11_AN42
    {GPIO_PD11, hal_ll_adc_module_num(ADC_MODULE_1), {HAL_LL_ADPCFG_REG_ADDRESS, 0}, ADC1_RD11, ADC1_RD11_AN42, 0},
    #endif
    #ifdef ADC1_RD2_AN25
    {GPIO_PD2, hal_ll_adc_module_num(ADC_MODULE_1), {HAL_LL_ADPCFG_REG_ADDRESS, 0}, ADC1_RD2, ADC1_RD2_AN25, 0},
    #endif
    #ifdef ADC1_RD3_AN44
    {GPIO_PD3, hal_ll_adc_module_num(ADC_MODULE_1), {HAL_LL_ADPCFG_REG_ADDRESS, 0}, ADC1_RD3, ADC1_RD3_AN44, 0},
    #endif
    #ifdef ADC1_RD4_AN47
    {GPIO_PD4, hal_ll_adc_module_num(ADC_MODULE_1), {HAL_LL_ADPCFG_REG_ADDRESS, 0}, ADC1_RD4, ADC1_RD4_AN47, 0},
    #endif
    #ifdef ADC1_RD5_AN48
    {GPIO_PD5, hal_ll_adc_module_num(ADC_MODULE_1), {HAL_LL_ADPCFG_REG_ADDRESS, 0}, ADC1_RD5, ADC1_RD5_AN48, 0},
    #endif
    #ifdef ADC1_RD6_AN34
    {GPIO_PD6, hal_ll_adc_module_num(ADC_MODULE_1), {HAL_LL_ADPCFG_REG_ADDRESS, 0}, ADC1_RD6, ADC1_RD6_AN34, 0},
    #endif
    #ifdef ADC1_RD7_AN20
    {GPIO_PD7, hal_ll_adc_module_num(ADC_MODULE_1), {HAL_LL_ADPCFG_REG_ADDRESS, 0}, ADC1_RD7, ADC1_RD7_AN20, 0},
    #endif
    #ifdef ADC1_RD8_AN40
    {GPIO_PD8, hal_ll_adc_module_num(ADC_MODULE_1), {HAL_LL_ADPCFG_REG_ADDRESS, 0}, ADC1_RD8, ADC1_RD8_AN40, 0},
    #endif
    #ifdef ADC1_RD9_AN24
    {GPIO_PD9, hal_ll_adc_module_num(ADC_MODULE_1), {HAL_LL_ADPCFG_REG_ADDRESS, 0}, ADC1_RD9, ADC1_RD9_AN24, 0},
    #endif
    #ifdef ADC1_RF3_AN30
    {GPIO_PF3, hal_ll_adc_module_num(ADC_MODULE_1), {HAL_LL_ADPCFG_REG_ADDRESS, 0}, ADC1_RF3, ADC1_RF3_AN30, 0},
    #endif
    #ifdef ADC1_RF4_AN11
    {GPIO_PF4, hal_ll_adc_module_num(ADC_MODULE_1), {HAL_LL_ADPCFG_REG_ADDRESS, 0}, ADC1_RF4, ADC1_RF4_AN11, 0},
    #endif
    #ifdef ADC1_RF5_AN10
    {GPIO_PF5, hal_ll_adc_module_num(ADC_MODULE_1), {HAL_LL_ADPCFG_REG_ADDRESS, 0}, ADC1_RF5, ADC1_RF5_AN10, 0},
    #endif
    #ifdef ADC1_RG9_AN49
    {GPIO_PG9, hal_ll_adc_module_num(ADC_MODULE_1), {HAL_LL_ADPCFG_REG_ADDRESS, 0}, ADC1_RG9, ADC1_RG9_AN49, 0},
    #endif
    #ifdef ADC1_RA1_AN26
    {GPIO_PA1, hal_ll_adc_module_num(ADC_MODULE_1), {HAL_LL_ADPCFG_REG_ADDRESS, 0}, ADC1_RA1, ADC1_RA1_AN26, 0},
    #endif
    #ifdef ADC1_RA14_AN38
    {GPIO_PA14, hal_ll_adc_module_num(ADC_MODULE_1), {HAL_LL_ADPCFG_REG_ADDRESS, 0}, ADC1_RA14, ADC1_RA14_AN38, 0},
    #endif
    #ifdef ADC1_RA15_AN39
    {GPIO_PA15, hal_ll_adc_module_num(ADC_MODULE_1), {HAL_LL_ADPCFG_REG_ADDRESS, 0}, ADC1_RA15, ADC1_RA15_AN39, 0},
    #endif
    #ifdef ADC1_RA4_AN36
    {GPIO_PA4, hal_ll_adc_module_num(ADC_MODULE_1), {HAL_LL_ADPCFG_REG_ADDRESS, 0}, ADC1_RA4, ADC1_RA4_AN36, 0},
    #endif
    #ifdef ADC1_RA5_AN37
    {GPIO_PA5, hal_ll_adc_module_num(ADC_MODULE_1), {HAL_LL_ADPCFG_REG_ADDRESS, 0}, ADC1_RA5, ADC1_RA5_AN37, 0},
    #endif
    #ifdef ADC1_RC3_AN9
    {GPIO_PC3, hal_ll_adc_module_num(ADC_MODULE_1), {HAL_LL_ADPCFG_REG_ADDRESS, 0}, ADC1_RC3, ADC1_RC3_AN9, 0},
    #endif
    #ifdef ADC1_RD12_AN45
    {GPIO_PD12, hal_ll_adc_module_num(ADC_MODULE_1), {HAL_LL_ADPCFG_REG_ADDRESS, 0}, ADC1_RD12, ADC1_RD12_AN45, 0},
    #endif
    #ifdef ADC1_RD13_AN46
    {GPIO_PD13, hal_ll_adc_module_num(ADC_MODULE_1), {HAL_LL_ADPCFG_REG_ADDRESS, 0}, ADC1_RD13, ADC1_RD13_AN46, 0},
    #endif
    #ifdef ADC1_RD14_AN28
    {GPIO_PD14, hal_ll_adc_module_num(ADC_MODULE_1), {HAL_LL_ADPCFG_REG_ADDRESS, 0}, ADC1_RD14, ADC1_RD14_AN28, 0},
    #endif
    #ifdef ADC1_RD15_AN29
    {GPIO_PD15, hal_ll_adc_module_num(ADC_MODULE_1), {HAL_LL_ADPCFG_REG_ADDRESS, 0}, ADC1_RD15, ADC1_RD15_AN29, 0},
    #endif
    #ifdef ADC1_RF13_AN27
    {GPIO_PF13, hal_ll_adc_module_num(ADC_MODULE_1), {HAL_LL_ADPCFG_REG_ADDRESS, 0}, ADC1_RF13, ADC1_RF13_AN27, 0},
    #endif
    #ifdef ADC1_RF2_AN31
    {GPIO_PF2, hal_ll_adc_module_num(ADC_MODULE_1), {HAL_LL_ADPCFG_REG_ADDRESS, 0}, ADC1_RF2, ADC1_RF2_AN31, 0},
    #endif
    #ifdef ADC1_RF8_AN32
    {GPIO_PF8, hal_ll_adc_module_num(ADC_MODULE_1), {HAL_LL_ADPCFG_REG_ADDRESS, 0}, ADC1_RF8, ADC1_RF8_AN32, 0},
    #endif
    #ifdef ADC1_RG15_AN33
    {GPIO_PG15, hal_ll_adc_module_num(ADC_MODULE_1), {HAL_LL_ADPCFG_REG_ADDRESS, 0}, ADC1_RG15, ADC1_RG15_AN33, 0},
    #endif
    #ifdef ADC1_RC3_AN12
    {GPIO_PC3, hal_ll_adc_module_num(ADC_MODULE_1), {HAL_LL_ADPCFG_REG_ADDRESS, 0}, ADC1_RC3, ADC1_RC3_AN12, 0},
    #endif
    #endif
    // EOF list

    // BEGIN AD1PCFG
    #ifdef _ADC_AD1PCFG_
    #ifdef ADC_RB0_AN0
    {GPIO_PB0, hal_ll_adc_module_num(ADC_MODULE), {HAL_LL_AD1PCFG_REG_ADDRESS, 0}, ADC_RB0, ADC_RB0_AN0, 0},
    #endif
    #ifdef ADC_RB1_AN1
    {GPIO_PB1, hal_ll_adc_module_num(ADC_MODULE), {HAL_LL_AD1PCFG_REG_ADDRESS, 0}, ADC_RB1, ADC_RB1_AN1, 0},
    #endif
    #ifdef ADC_RB2_AN2
    {GPIO_PB2, hal_ll_adc_module_num(ADC_MODULE), {HAL_LL_AD1PCFG_REG_ADDRESS, 0}, ADC_RB2, ADC_RB2_AN2, 0},
    #endif
    #ifdef ADC_RB3_AN3
    {GPIO_PB3, hal_ll_adc_module_num(ADC_MODULE), {HAL_LL_AD1PCFG_REG_ADDRESS, 0}, ADC_RB3, ADC_RB3_AN3, 0},
    #endif
    #ifdef ADC_RB4_AN4
    {GPIO_PB4, hal_ll_adc_module_num(ADC_MODULE), {HAL_LL_AD1PCFG_REG_ADDRESS, 0}, ADC_RB4, ADC_RB4_AN4, 0},
    #endif
    #ifdef ADC_RB5_AN5
    {GPIO_PB5, hal_ll_adc_module_num(ADC_MODULE), {HAL_LL_AD1PCFG_REG_ADDRESS, 0}, ADC_RB5, ADC_RB5_AN5, 0},
    #endif
    #ifdef ADC_RB6_AN6
    {GPIO_PB6, hal_ll_adc_module_num(ADC_MODULE), {HAL_LL_AD1PCFG_REG_ADDRESS, 0}, ADC_RB6, ADC_RB6_AN6, 0},
    #endif
    #ifdef ADC_RB7_AN7
    {GPIO_PB7, hal_ll_adc_module_num(ADC_MODULE), {HAL_LL_AD1PCFG_REG_ADDRESS, 0}, ADC_RB7, ADC_RB7_AN7, 0},
    #endif
    #ifdef ADC_RB8_AN8
    {GPIO_PB8, hal_ll_adc_module_num(ADC_MODULE), {HAL_LL_AD1PCFG_REG_ADDRESS, 0}, ADC_RB8, ADC_RB8_AN8, 0},
    #endif
    #ifdef ADC_RB9_AN9
    {GPIO_PB9, hal_ll_adc_module_num(ADC_MODULE), {HAL_LL_AD1PCFG_REG_ADDRESS, 0}, ADC_RB9, ADC_RB9_AN9, 0},
    #endif
    #ifdef ADC_RB10_AN10
    {GPIO_PB10, hal_ll_adc_module_num(ADC_MODULE), {HAL_LL_AD1PCFG_REG_ADDRESS, 0}, ADC_RB10, ADC_RB10_AN10, 0},
    #endif
    #ifdef ADC_RB11_AN11
    {GPIO_PB11, hal_ll_adc_module_num(ADC_MODULE), {HAL_LL_AD1PCFG_REG_ADDRESS, 0}, ADC_RB11, ADC_RB11_AN11, 0},
    #endif
    #ifdef ADC_RB12_AN12
    {GPIO_PB12, hal_ll_adc_module_num(ADC_MODULE), {HAL_LL_AD1PCFG_REG_ADDRESS, 0}, ADC_RB12, ADC_RB12_AN12, 0},
    #endif
    #ifdef ADC_RB13_AN13
    {GPIO_PB13, hal_ll_adc_module_num(ADC_MODULE), {HAL_LL_AD1PCFG_REG_ADDRESS, 0}, ADC_RB13, ADC_RB13_AN13, 0},
    #endif
    #ifdef ADC_RB14_AN14
    {GPIO_PB14, hal_ll_adc_module_num(ADC_MODULE), {HAL_LL_AD1PCFG_REG_ADDRESS, 0}, ADC_RB14, ADC_RB14_AN14, 0},
    #endif
    #ifdef ADC_RB15_AN15
    {GPIO_PB15, hal_ll_adc_module_num(ADC_MODULE), {HAL_LL_AD1PCFG_REG_ADDRESS, 0}, ADC_RB15, ADC_RB15_AN15, 0},
    #endif
    #ifdef ADC1_RA0_AN0
    {GPIO_PA0, hal_ll_adc_module_num(ADC_MODULE_1), {HAL_LL_AD1PCFG_REG_ADDRESS, 0}, ADC1_RA0, ADC1_RA0_AN0, 0},
    #endif
    #ifdef ADC1_RA1_AN1
    {GPIO_PA1, hal_ll_adc_module_num(ADC_MODULE_1), {HAL_LL_AD1PCFG_REG_ADDRESS, 0}, ADC1_RA1, ADC1_RA1_AN1, 0},
    #endif
    #ifdef ADC1_RA2_AN32
    {GPIO_PA2, hal_ll_adc_module_num(ADC_MODULE_1), {HAL_LL_AD1PCFG_REG_ADDRESS, 0}, ADC1_RA2, ADC1_RA2_AN32, 0},
    #endif
    #ifdef ADC1_RA4_AN24
    {GPIO_PA4, hal_ll_adc_module_num(ADC_MODULE_1), {HAL_LL_AD1PCFG_REG_ADDRESS, 0}, ADC1_RA4, ADC1_RA4_AN24, 0},
    #endif
    #ifdef ADC1_RA9_AN28
    {GPIO_PA9, hal_ll_adc_module_num(ADC_MODULE_1), {HAL_LL_AD1PCFG_REG_ADDRESS, 0}, ADC1_RA9, ADC1_RA9_AN28, 0},
    #endif
    #ifdef ADC1_RB0_AN2
    {GPIO_PB0, hal_ll_adc_module_num(ADC_MODULE_1), {HAL_LL_AD1PCFG_REG_ADDRESS, 0}, ADC1_RB0, ADC1_RB0_AN2, 0},
    #endif
    #ifdef ADC1_RB1_AN3
    {GPIO_PB1, hal_ll_adc_module_num(ADC_MODULE_1), {HAL_LL_AD1PCFG_REG_ADDRESS, 0}, ADC1_RB1, ADC1_RB1_AN3, 0},
    #endif
    #ifdef ADC1_RB2_AN4
    {GPIO_PB2, hal_ll_adc_module_num(ADC_MODULE_1), {HAL_LL_AD1PCFG_REG_ADDRESS, 0}, ADC1_RB2, ADC1_RB2_AN4, 0},
    #endif
    #ifdef ADC1_RB3_AN5
    {GPIO_PB3, hal_ll_adc_module_num(ADC_MODULE_1), {HAL_LL_AD1PCFG_REG_ADDRESS, 0}, ADC1_RB3, ADC1_RB3_AN5, 0},
    #endif
    #ifdef ADC1_RB7_AN25
    {GPIO_PB7, hal_ll_adc_module_num(ADC_MODULE_1), {HAL_LL_AD1PCFG_REG_ADDRESS, 0}, ADC1_RB7, ADC1_RB7_AN25, 0},
    #endif
    #ifdef ADC1_RB8_AN26
    {GPIO_PB8, hal_ll_adc_module_num(ADC_MODULE_1), {HAL_LL_AD1PCFG_REG_ADDRESS, 0}, ADC1_RB8, ADC1_RB8_AN26, 0},
    #endif
    #ifdef ADC1_RB9_AN27
    {GPIO_PB9, hal_ll_adc_module_num(ADC_MODULE_1), {HAL_LL_AD1PCFG_REG_ADDRESS, 0}, ADC1_RB9, ADC1_RB9_AN27, 0},
    #endif
    #ifdef ADC1_RC0_AN6
    {GPIO_PC0, hal_ll_adc_module_num(ADC_MODULE_1), {HAL_LL_AD1PCFG_REG_ADDRESS, 0}, ADC1_RC0, ADC1_RC0_AN6, 0},
    #endif
    #ifdef ADC1_RC1_AN7
    {GPIO_PC1, hal_ll_adc_module_num(ADC_MODULE_1), {HAL_LL_AD1PCFG_REG_ADDRESS, 0}, ADC1_RC1, ADC1_RC1_AN7, 0},
    #endif
    #ifdef ADC1_RC2_AN8
    {GPIO_PC2, hal_ll_adc_module_num(ADC_MODULE_1), {HAL_LL_AD1PCFG_REG_ADDRESS, 0}, ADC1_RC2, ADC1_RC2_AN8, 0},
    #endif
    #ifdef ADC1_RC3_AN29
    {GPIO_PC3, hal_ll_adc_module_num(ADC_MODULE_1), {HAL_LL_AD1PCFG_REG_ADDRESS, 0}, ADC1_RC3, ADC1_RC3_AN29, 0},
    #endif
    #ifdef ADC1_RC4_AN30
    {GPIO_PC4, hal_ll_adc_module_num(ADC_MODULE_1), {HAL_LL_AD1PCFG_REG_ADDRESS, 0}, ADC1_RC4, ADC1_RC4_AN30, 0},
    #endif
    #ifdef ADC1_RC5_AN31
    {GPIO_PC5, hal_ll_adc_module_num(ADC_MODULE_1), {HAL_LL_AD1PCFG_REG_ADDRESS, 0}, ADC1_RC5, ADC1_RC5_AN31, 0},
    #endif
    #ifdef ADC2_RA0_AN0
    {GPIO_PA0, hal_ll_adc_module_num(ADC_MODULE_2), {HAL_LL_AD1PCFG_REG_ADDRESS, 0}, ADC2_RA0, ADC2_RA0_AN0, 0},
    #endif
    #ifdef ADC2_RA1_AN1
    {GPIO_PA1, hal_ll_adc_module_num(ADC_MODULE_2), {HAL_LL_AD1PCFG_REG_ADDRESS, 0}, ADC2_RA1, ADC2_RA1_AN1, 0},
    #endif
    #ifdef ADC2_RA4_AN24
    {GPIO_PA4, hal_ll_adc_module_num(ADC_MODULE_2), {HAL_LL_AD1PCFG_REG_ADDRESS, 0}, ADC2_RA4, ADC2_RA4_AN24, 0},
    #endif
    #ifdef ADC2_RA9_AN28
    {GPIO_PA9, hal_ll_adc_module_num(ADC_MODULE_2), {HAL_LL_AD1PCFG_REG_ADDRESS, 0}, ADC2_RA9, ADC2_RA9_AN28, 0},
    #endif
    #ifdef ADC2_RB0_AN2
    {GPIO_PB0, hal_ll_adc_module_num(ADC_MODULE_2), {HAL_LL_AD1PCFG_REG_ADDRESS, 0}, ADC2_RB0, ADC2_RB0_AN2, 0},
    #endif
    #ifdef ADC2_RB1_AN3
    {GPIO_PB1, hal_ll_adc_module_num(ADC_MODULE_2), {HAL_LL_AD1PCFG_REG_ADDRESS, 0}, ADC2_RB1, ADC2_RB1_AN3, 0},
    #endif
    #ifdef ADC2_RB2_AN4
    {GPIO_PB2, hal_ll_adc_module_num(ADC_MODULE_2), {HAL_LL_AD1PCFG_REG_ADDRESS, 0}, ADC2_RB2, ADC2_RB2_AN4, 0},
    #endif
    #ifdef ADC2_RB3_AN5
    {GPIO_PB3, hal_ll_adc_module_num(ADC_MODULE_2), {HAL_LL_AD1PCFG_REG_ADDRESS, 0}, ADC2_RB3, ADC2_RB3_AN5, 0},
    #endif
    #ifdef ADC2_RB7_AN25
    {GPIO_PB7, hal_ll_adc_module_num(ADC_MODULE_2), {HAL_LL_AD1PCFG_REG_ADDRESS, 0}, ADC2_RB7, ADC2_RB7_AN25, 0},
    #endif
    #ifdef ADC2_RB8_AN26
    {GPIO_PB8, hal_ll_adc_module_num(ADC_MODULE_2), {HAL_LL_AD1PCFG_REG_ADDRESS, 0}, ADC2_RB8, ADC2_RB8_AN26, 0},
    #endif
    #ifdef ADC2_RB9_AN27
    {GPIO_PB9, hal_ll_adc_module_num(ADC_MODULE_2), {HAL_LL_AD1PCFG_REG_ADDRESS, 0}, ADC2_RB9, ADC2_RB9_AN27, 0},
    #endif
    #ifdef ADC2_RC0_AN6
    {GPIO_PC0, hal_ll_adc_module_num(ADC_MODULE_2), {HAL_LL_AD1PCFG_REG_ADDRESS, 0}, ADC2_RC0, ADC2_RC0_AN6, 0},
    #endif
    #ifdef ADC2_RC1_AN7
    {GPIO_PC1, hal_ll_adc_module_num(ADC_MODULE_2), {HAL_LL_AD1PCFG_REG_ADDRESS, 0}, ADC2_RC1, ADC2_RC1_AN7, 0},
    #endif
    #ifdef ADC2_RC2_AN8
    {GPIO_PC2, hal_ll_adc_module_num(ADC_MODULE_2), {HAL_LL_AD1PCFG_REG_ADDRESS, 0}, ADC2_RC2, ADC2_RC2_AN8, 0},
    #endif
    #ifdef ADC2_RC3_AN29
    {GPIO_PC3, hal_ll_adc_module_num(ADC_MODULE_2), {HAL_LL_AD1PCFG_REG_ADDRESS, 0}, ADC2_RC3, ADC2_RC3_AN29, 0},
    #endif
    #ifdef ADC2_RC4_AN30
    {GPIO_PC4, hal_ll_adc_module_num(ADC_MODULE_2), {HAL_LL_AD1PCFG_REG_ADDRESS, 0}, ADC2_RC4, ADC2_RC4_AN30, 0},
    #endif
    #ifdef ADC2_RC5_AN31
    {GPIO_PC5, hal_ll_adc_module_num(ADC_MODULE_2), {HAL_LL_AD1PCFG_REG_ADDRESS, 0}, ADC2_RC5, ADC2_RC5_AN31, 0},
    #endif
    #ifdef ADC1_RA11_AN9
    {GPIO_PA11, hal_ll_adc_module_num(ADC_MODULE_1), {HAL_LL_AD1PCFG_REG_ADDRESS, 0}, ADC1_RA11, ADC1_RA11_AN9, 0},
    #endif
    #ifdef ADC1_RA12_AN10
    {GPIO_PA12, hal_ll_adc_module_num(ADC_MODULE_1), {HAL_LL_AD1PCFG_REG_ADDRESS, 0}, ADC1_RA12, ADC1_RA12_AN10, 0},
    #endif
    #ifdef ADC1_RC10_AN48
    {GPIO_PC10, hal_ll_adc_module_num(ADC_MODULE_1), {HAL_LL_AD1PCFG_REG_ADDRESS, 0}, ADC1_RC10, ADC1_RC10_AN48, 0},
    #endif
    #ifdef ADC1_RC11_AN11
    {GPIO_PC11, hal_ll_adc_module_num(ADC_MODULE_1), {HAL_LL_AD1PCFG_REG_ADDRESS, 0}, ADC1_RC11, ADC1_RC11_AN11, 0},
    #endif
    #ifdef ADC1_RC12_AN49
    {GPIO_PC12, hal_ll_adc_module_num(ADC_MODULE_1), {HAL_LL_AD1PCFG_REG_ADDRESS, 0}, ADC1_RC12, ADC1_RC12_AN49, 0},
    #endif
    #ifdef ADC1_RE12_AN12
    {GPIO_PE12, hal_ll_adc_module_num(ADC_MODULE_1), {HAL_LL_AD1PCFG_REG_ADDRESS, 0}, ADC1_RE12, ADC1_RE12_AN12, 0},
    #endif
    #ifdef ADC1_RE13_AN13
    {GPIO_PE13, hal_ll_adc_module_num(ADC_MODULE_1), {HAL_LL_AD1PCFG_REG_ADDRESS, 0}, ADC1_RE13, ADC1_RE13_AN13, 0},
    #endif
    #ifdef ADC1_RE14_AN14
    {GPIO_PE14, hal_ll_adc_module_num(ADC_MODULE_1), {HAL_LL_AD1PCFG_REG_ADDRESS, 0}, ADC1_RE14, ADC1_RE14_AN14, 0},
    #endif
    #ifdef ADC1_RE15_AN15
    {GPIO_PE15, hal_ll_adc_module_num(ADC_MODULE_1), {HAL_LL_AD1PCFG_REG_ADDRESS, 0}, ADC1_RE15, ADC1_RE15_AN15, 0},
    #endif
    #ifdef ADC1_RG6_AN19
    {GPIO_PG6, hal_ll_adc_module_num(ADC_MODULE_1), {HAL_LL_AD1PCFG_REG_ADDRESS, 0}, ADC1_RG6, ADC1_RG6_AN19, 0},
    #endif
    #ifdef ADC1_RG7_AN18
    {GPIO_PG7, hal_ll_adc_module_num(ADC_MODULE_1), {HAL_LL_AD1PCFG_REG_ADDRESS, 0}, ADC1_RG7, ADC1_RG7_AN18, 0},
    #endif
    #ifdef ADC1_RG8_AN17
    {GPIO_PG8, hal_ll_adc_module_num(ADC_MODULE_1), {HAL_LL_AD1PCFG_REG_ADDRESS, 0}, ADC1_RG8, ADC1_RG8_AN17, 0},
    #endif
    #ifdef ADC1_RG9_AN16
    {GPIO_PG9, hal_ll_adc_module_num(ADC_MODULE_1), {HAL_LL_AD1PCFG_REG_ADDRESS, 0}, ADC1_RG9, ADC1_RG9_AN16, 0},
    #endif
    #ifdef ADC2_RA11_AN9
    {GPIO_PA11, hal_ll_adc_module_num(ADC_MODULE_2), {HAL_LL_AD1PCFG_REG_ADDRESS, 0}, ADC2_RA11, ADC2_RA11_AN9, 0},
    #endif
    #ifdef ADC2_RA12_AN10
    {GPIO_PA12, hal_ll_adc_module_num(ADC_MODULE_2), {HAL_LL_AD1PCFG_REG_ADDRESS, 0}, ADC2_RA12, ADC2_RA12_AN10, 0},
    #endif
    #ifdef ADC2_RC11_AN11
    {GPIO_PC11, hal_ll_adc_module_num(ADC_MODULE_2), {HAL_LL_AD1PCFG_REG_ADDRESS, 0}, ADC2_RC11, ADC2_RC11_AN11, 0},
    #endif
    #ifdef ADC2_RE12_AN12
    {GPIO_PE12, hal_ll_adc_module_num(ADC_MODULE_2), {HAL_LL_AD1PCFG_REG_ADDRESS, 0}, ADC2_RE12, ADC2_RE12_AN12, 0},
    #endif
    #ifdef ADC2_RE13_AN13
    {GPIO_PE13, hal_ll_adc_module_num(ADC_MODULE_2), {HAL_LL_AD1PCFG_REG_ADDRESS, 0}, ADC2_RE13, ADC2_RE13_AN13, 0},
    #endif
    #ifdef ADC2_RE14_AN14
    {GPIO_PE14, hal_ll_adc_module_num(ADC_MODULE_2), {HAL_LL_AD1PCFG_REG_ADDRESS, 0}, ADC2_RE14, ADC2_RE14_AN14, 0},
    #endif
    #ifdef ADC2_RE15_AN15
    {GPIO_PE15, hal_ll_adc_module_num(ADC_MODULE_2), {HAL_LL_AD1PCFG_REG_ADDRESS, 0}, ADC2_RE15, ADC2_RE15_AN15, 0},
    #endif
    #ifdef ADC2_RG6_AN19
    {GPIO_PG6, hal_ll_adc_module_num(ADC_MODULE_2), {HAL_LL_AD1PCFG_REG_ADDRESS, 0}, ADC2_RG6, ADC2_RG6_AN19, 0},
    #endif
    #ifdef ADC2_RG7_AN18
    {GPIO_PG7, hal_ll_adc_module_num(ADC_MODULE_2), {HAL_LL_AD1PCFG_REG_ADDRESS, 0}, ADC2_RG7, ADC2_RG7_AN18, 0},
    #endif
    #ifdef ADC2_RG8_AN17
    {GPIO_PG8, hal_ll_adc_module_num(ADC_MODULE_2), {HAL_LL_AD1PCFG_REG_ADDRESS, 0}, ADC2_RG8, ADC2_RG8_AN17, 0},
    #endif
    #ifdef ADC2_RG9_AN16
    {GPIO_PG9, hal_ll_adc_module_num(ADC_MODULE_2), {HAL_LL_AD1PCFG_REG_ADDRESS, 0}, ADC2_RG9, ADC2_RG9_AN16, 0},
    #endif
    #ifdef ADC1_RA14_AN46
    {GPIO_PA14, hal_ll_adc_module_num(ADC_MODULE_1), {HAL_LL_AD1PCFG_REG_ADDRESS, 0}, ADC1_RA14, ADC1_RA14_AN46, 0},
    #endif
    #ifdef ADC1_RA15_AN47
    {GPIO_PA15, hal_ll_adc_module_num(ADC_MODULE_1), {HAL_LL_AD1PCFG_REG_ADDRESS, 0}, ADC1_RA15, ADC1_RA15_AN47, 0},
    #endif
    #ifdef ADC1_RD14_AN38
    {GPIO_PD14, hal_ll_adc_module_num(ADC_MODULE_1), {HAL_LL_AD1PCFG_REG_ADDRESS, 0}, ADC1_RD14, ADC1_RD14_AN38, 0},
    #endif
    #ifdef ADC1_RD15_AN39
    {GPIO_PD15, hal_ll_adc_module_num(ADC_MODULE_1), {HAL_LL_AD1PCFG_REG_ADDRESS, 0}, ADC1_RD15, ADC1_RD15_AN39, 0},
    #endif
    #ifdef ADC1_RE0_AN40
    {GPIO_PE0, hal_ll_adc_module_num(ADC_MODULE_1), {HAL_LL_AD1PCFG_REG_ADDRESS, 0}, ADC1_RE0, ADC1_RE0_AN40, 0},
    #endif
    #ifdef ADC1_RE1_AN41
    {GPIO_PE1, hal_ll_adc_module_num(ADC_MODULE_1), {HAL_LL_AD1PCFG_REG_ADDRESS, 0}, ADC1_RE1, ADC1_RE1_AN41, 0},
    #endif
    #ifdef ADC1_RE8_AN21
    {GPIO_PE8, hal_ll_adc_module_num(ADC_MODULE_1), {HAL_LL_AD1PCFG_REG_ADDRESS, 0}, ADC1_RE8, ADC1_RE8_AN21, 0},
    #endif
    #ifdef ADC1_RE9_AN20
    {GPIO_PE9, hal_ll_adc_module_num(ADC_MODULE_1), {HAL_LL_AD1PCFG_REG_ADDRESS, 0}, ADC1_RE9, ADC1_RE9_AN20, 0},
    #endif
    #ifdef ADC1_RF10_AN34
    {GPIO_PF10, hal_ll_adc_module_num(ADC_MODULE_1), {HAL_LL_AD1PCFG_REG_ADDRESS, 0}, ADC1_RF10, ADC1_RF10_AN34, 0},
    #endif
    #ifdef ADC1_RF12_AN37
    {GPIO_PF12, hal_ll_adc_module_num(ADC_MODULE_1), {HAL_LL_AD1PCFG_REG_ADDRESS, 0}, ADC1_RF12, ADC1_RF12_AN37, 0},
    #endif
    #ifdef ADC1_RF13_AN36
    {GPIO_PF13, hal_ll_adc_module_num(ADC_MODULE_1), {HAL_LL_AD1PCFG_REG_ADDRESS, 0}, ADC1_RF13, ADC1_RF13_AN36, 0},
    #endif
    #ifdef ADC1_RF4_AN44
    {GPIO_PF4, hal_ll_adc_module_num(ADC_MODULE_1), {HAL_LL_AD1PCFG_REG_ADDRESS, 0}, ADC1_RF4, ADC1_RF4_AN44, 0},
    #endif
    #ifdef ADC1_RF5_AN45
    {GPIO_PF5, hal_ll_adc_module_num(ADC_MODULE_1), {HAL_LL_AD1PCFG_REG_ADDRESS, 0}, ADC1_RF5, ADC1_RF5_AN45, 0},
    #endif
    #ifdef ADC1_RF9_AN33
    {GPIO_PF9, hal_ll_adc_module_num(ADC_MODULE_1), {HAL_LL_AD1PCFG_REG_ADDRESS, 0}, ADC1_RF9, ADC1_RF9_AN33, 0},
    #endif
    #ifdef ADC1_RG10_AN22
    {GPIO_PG10, hal_ll_adc_module_num(ADC_MODULE_1), {HAL_LL_AD1PCFG_REG_ADDRESS, 0}, ADC1_RG10, ADC1_RG10_AN22, 0},
    #endif
    #ifdef ADC1_RG11_AN35
    {GPIO_PG11, hal_ll_adc_module_num(ADC_MODULE_1), {HAL_LL_AD1PCFG_REG_ADDRESS, 0}, ADC1_RG11, ADC1_RG11_AN35, 0},
    #endif
    #ifdef ADC1_RG15_AN23
    {GPIO_PG15, hal_ll_adc_module_num(ADC_MODULE_1), {HAL_LL_AD1PCFG_REG_ADDRESS, 0}, ADC1_RG15, ADC1_RG15_AN23, 0},
    #endif
    #ifdef ADC1_RG2_AN42
    {GPIO_PG2, hal_ll_adc_module_num(ADC_MODULE_1), {HAL_LL_AD1PCFG_REG_ADDRESS, 0}, ADC1_RG2, ADC1_RG2_AN42, 0},
    #endif
    #ifdef ADC1_RG3_AN43
    {GPIO_PG3, hal_ll_adc_module_num(ADC_MODULE_1), {HAL_LL_AD1PCFG_REG_ADDRESS, 0}, ADC1_RG3, ADC1_RG3_AN43, 0},
    #endif
    #ifdef ADC2_RE8_AN21
    {GPIO_PE8, hal_ll_adc_module_num(ADC_MODULE_2), {HAL_LL_AD1PCFG_REG_ADDRESS, 0}, ADC2_RE8, ADC2_RE8_AN21, 0},
    #endif
    #ifdef ADC2_RE9_AN20
    {GPIO_PE9, hal_ll_adc_module_num(ADC_MODULE_2), {HAL_LL_AD1PCFG_REG_ADDRESS, 0}, ADC2_RE9, ADC2_RE9_AN20, 0},
    #endif
    #ifdef ADC2_RG10_AN22
    {GPIO_PG10, hal_ll_adc_module_num(ADC_MODULE_2), {HAL_LL_AD1PCFG_REG_ADDRESS, 0}, ADC2_RG10, ADC2_RG10_AN22, 0},
    #endif
    #ifdef ADC2_RG15_AN23
    {GPIO_PG15, hal_ll_adc_module_num(ADC_MODULE_2), {HAL_LL_AD1PCFG_REG_ADDRESS, 0}, ADC2_RG15, ADC2_RG15_AN23, 0},
    #endif
    #ifdef ADC1_RA2_AN2
    {GPIO_PA2, hal_ll_adc_module_num(ADC_MODULE_1), {HAL_LL_AD1PCFG_REG_ADDRESS, 0}, ADC1_RA2, ADC1_RA2_AN2, 0},
    #endif
    #ifdef ADC1_RB0_AN3
    {GPIO_PB0, hal_ll_adc_module_num(ADC_MODULE_1), {HAL_LL_AD1PCFG_REG_ADDRESS, 0}, ADC1_RB0, ADC1_RB0_AN3, 0},
    #endif
    #ifdef ADC1_RB1_AN6
    {GPIO_PB1, hal_ll_adc_module_num(ADC_MODULE_1), {HAL_LL_AD1PCFG_REG_ADDRESS, 0}, ADC1_RB1, ADC1_RB1_AN6, 0},
    #endif
    #ifdef ADC1_RB2_AN7
    {GPIO_PB2, hal_ll_adc_module_num(ADC_MODULE_1), {HAL_LL_AD1PCFG_REG_ADDRESS, 0}, ADC1_RB2, ADC1_RB2_AN7, 0},
    #endif
    #ifdef ADC1_RB3_AN18
    {GPIO_PB3, hal_ll_adc_module_num(ADC_MODULE_1), {HAL_LL_AD1PCFG_REG_ADDRESS, 0}, ADC1_RB3, ADC1_RB3_AN18, 0},
    #endif
    #ifdef ADC1_RB5_AN19
    {GPIO_PB5, hal_ll_adc_module_num(ADC_MODULE_1), {HAL_LL_AD1PCFG_REG_ADDRESS, 0}, ADC1_RB5, ADC1_RB5_AN19, 0},
    #endif
    #ifdef ADC1_RB6_AN20
    {GPIO_PB6, hal_ll_adc_module_num(ADC_MODULE_1), {HAL_LL_AD1PCFG_REG_ADDRESS, 0}, ADC1_RB6, ADC1_RB6_AN20, 0},
    #endif
    #ifdef ADC1_RB7_AN21
    {GPIO_PB7, hal_ll_adc_module_num(ADC_MODULE_1), {HAL_LL_AD1PCFG_REG_ADDRESS, 0}, ADC1_RB7, ADC1_RB7_AN21, 0},
    #endif
    #ifdef ADC1_RB9_AN4
    {GPIO_PB9, hal_ll_adc_module_num(ADC_MODULE_1), {HAL_LL_AD1PCFG_REG_ADDRESS, 0}, ADC1_RB9, ADC1_RB9_AN4, 0},
    #endif
    #ifdef ADC1_RC1_AN8
    {GPIO_PC1, hal_ll_adc_module_num(ADC_MODULE_1), {HAL_LL_AD1PCFG_REG_ADDRESS, 0}, ADC1_RC1, ADC1_RC1_AN8, 0},
    #endif
    #ifdef ADC1_RC10_AN10
    {GPIO_PC10, hal_ll_adc_module_num(ADC_MODULE_1), {HAL_LL_AD1PCFG_REG_ADDRESS, 0}, ADC1_RC10, ADC1_RC10_AN10, 0},
    #endif
    #ifdef ADC1_RC12_AN14
    {GPIO_PC12, hal_ll_adc_module_num(ADC_MODULE_1), {HAL_LL_AD1PCFG_REG_ADDRESS, 0}, ADC1_RC12, ADC1_RC12_AN14, 0},
    #endif
    #ifdef ADC1_RC2_AN9
    {GPIO_PC2, hal_ll_adc_module_num(ADC_MODULE_1), {HAL_LL_AD1PCFG_REG_ADDRESS, 0}, ADC1_RC2, ADC1_RC2_AN9, 0},
    #endif
    #ifdef ADC1_RC6_AN17
    {GPIO_PC6, hal_ll_adc_module_num(ADC_MODULE_1), {HAL_LL_AD1PCFG_REG_ADDRESS, 0}, ADC1_RC6, ADC1_RC6_AN17, 0},
    #endif
    #ifdef ADC1_RC9_AN11
    {GPIO_PC9, hal_ll_adc_module_num(ADC_MODULE_1), {HAL_LL_AD1PCFG_REG_ADDRESS, 0}, ADC1_RC9, ADC1_RC9_AN11, 0},
    #endif
    #ifdef ADC1_RD13_AN13
    {GPIO_PD13, hal_ll_adc_module_num(ADC_MODULE_1), {HAL_LL_AD1PCFG_REG_ADDRESS, 0}, ADC1_RD13, ADC1_RD13_AN13, 0},
    #endif
    #ifdef ADC1_RD2_AN16
    {GPIO_PD2, hal_ll_adc_module_num(ADC_MODULE_1), {HAL_LL_AD1PCFG_REG_ADDRESS, 0}, ADC1_RD2, ADC1_RD2_AN16, 0},
    #endif
    #ifdef ADC1_RD5_AN12
    {GPIO_PD5, hal_ll_adc_module_num(ADC_MODULE_1), {HAL_LL_AD1PCFG_REG_ADDRESS, 0}, ADC1_RD5, ADC1_RD5_AN12, 0},
    #endif
    #ifdef ADC1_RD7_AN15
    {GPIO_PD7, hal_ll_adc_module_num(ADC_MODULE_1), {HAL_LL_AD1PCFG_REG_ADDRESS, 0}, ADC1_RD7, ADC1_RD7_AN15, 0},
    #endif
    #ifdef ADC1_RD8_AN5
    {GPIO_PD8, hal_ll_adc_module_num(ADC_MODULE_1), {HAL_LL_AD1PCFG_REG_ADDRESS, 0}, ADC1_RD8, ADC1_RD8_AN5, 0},
    #endif
    #ifdef ADC1_RB10_AN5
    {GPIO_PB10, hal_ll_adc_module_num(ADC_MODULE_1), {HAL_LL_AD1PCFG_REG_ADDRESS, 0}, ADC1_RB10, ADC1_RB10_AN5, 0},
    #endif
    #ifdef ADC1_RB3_AN8
    {GPIO_PB3, hal_ll_adc_module_num(ADC_MODULE_1), {HAL_LL_AD1PCFG_REG_ADDRESS, 0}, ADC1_RB3, ADC1_RB3_AN8, 0},
    #endif
    #ifdef ADC1_RB5_AN9
    {GPIO_PB5, hal_ll_adc_module_num(ADC_MODULE_1), {HAL_LL_AD1PCFG_REG_ADDRESS, 0}, ADC1_RB5, ADC1_RB5_AN9, 0},
    #endif
    #ifdef ADC1_RB6_AN10
    {GPIO_PB6, hal_ll_adc_module_num(ADC_MODULE_1), {HAL_LL_AD1PCFG_REG_ADDRESS, 0}, ADC1_RB6, ADC1_RB6_AN10, 0},
    #endif
    #ifdef ADC1_RB7_AN11
    {GPIO_PB7, hal_ll_adc_module_num(ADC_MODULE_1), {HAL_LL_AD1PCFG_REG_ADDRESS, 0}, ADC1_RB7, ADC1_RB7_AN11, 0},
    #endif
    #ifdef ADC1_RC11_AN12
    {GPIO_PC11, hal_ll_adc_module_num(ADC_MODULE_1), {HAL_LL_AD1PCFG_REG_ADDRESS, 0}, ADC1_RC11, ADC1_RC11_AN12, 0},
    #endif
    #ifdef ADC1_RB0_AN0
    {GPIO_PB0, hal_ll_adc_module_num(ADC_MODULE_1), {HAL_LL_AD1PCFG_REG_ADDRESS, 0}, ADC1_RB0, ADC1_RB0_AN0, 0},
    #endif
    #ifdef ADC1_RB1_AN1
    {GPIO_PB1, hal_ll_adc_module_num(ADC_MODULE_1), {HAL_LL_AD1PCFG_REG_ADDRESS, 0}, ADC1_RB1, ADC1_RB1_AN1, 0},
    #endif
    #ifdef ADC1_RB10_AN10
    {GPIO_PB10, hal_ll_adc_module_num(ADC_MODULE_1), {HAL_LL_AD1PCFG_REG_ADDRESS, 0}, ADC1_RB10, ADC1_RB10_AN10, 0},
    #endif
    #ifdef ADC1_RB11_AN11
    {GPIO_PB11, hal_ll_adc_module_num(ADC_MODULE_1), {HAL_LL_AD1PCFG_REG_ADDRESS, 0}, ADC1_RB11, ADC1_RB11_AN11, 0},
    #endif
    #ifdef ADC1_RB12_AN12
    {GPIO_PB12, hal_ll_adc_module_num(ADC_MODULE_1), {HAL_LL_AD1PCFG_REG_ADDRESS, 0}, ADC1_RB12, ADC1_RB12_AN12, 0},
    #endif
    #ifdef ADC1_RB13_AN13
    {GPIO_PB13, hal_ll_adc_module_num(ADC_MODULE_1), {HAL_LL_AD1PCFG_REG_ADDRESS, 0}, ADC1_RB13, ADC1_RB13_AN13, 0},
    #endif
    #ifdef ADC1_RB14_AN14
    {GPIO_PB14, hal_ll_adc_module_num(ADC_MODULE_1), {HAL_LL_AD1PCFG_REG_ADDRESS, 0}, ADC1_RB14, ADC1_RB14_AN14, 0},
    #endif
    #ifdef ADC1_RB15_AN15
    {GPIO_PB15, hal_ll_adc_module_num(ADC_MODULE_1), {HAL_LL_AD1PCFG_REG_ADDRESS, 0}, ADC1_RB15, ADC1_RB15_AN15, 0},
    #endif
    #ifdef ADC1_RB2_AN2
    {GPIO_PB2, hal_ll_adc_module_num(ADC_MODULE_1), {HAL_LL_AD1PCFG_REG_ADDRESS, 0}, ADC1_RB2, ADC1_RB2_AN2, 0},
    #endif
    #ifdef ADC1_RB3_AN3
    {GPIO_PB3, hal_ll_adc_module_num(ADC_MODULE_1), {HAL_LL_AD1PCFG_REG_ADDRESS, 0}, ADC1_RB3, ADC1_RB3_AN3, 0},
    #endif
    #ifdef ADC1_RB4_AN4
    {GPIO_PB4, hal_ll_adc_module_num(ADC_MODULE_1), {HAL_LL_AD1PCFG_REG_ADDRESS, 0}, ADC1_RB4, ADC1_RB4_AN4, 0},
    #endif
    #ifdef ADC1_RB5_AN5
    {GPIO_PB5, hal_ll_adc_module_num(ADC_MODULE_1), {HAL_LL_AD1PCFG_REG_ADDRESS, 0}, ADC1_RB5, ADC1_RB5_AN5, 0},
    #endif
    #ifdef ADC1_RB6_AN6
    {GPIO_PB6, hal_ll_adc_module_num(ADC_MODULE_1), {HAL_LL_AD1PCFG_REG_ADDRESS, 0}, ADC1_RB6, ADC1_RB6_AN6, 0},
    #endif
    #ifdef ADC1_RB7_AN7
    {GPIO_PB7, hal_ll_adc_module_num(ADC_MODULE_1), {HAL_LL_AD1PCFG_REG_ADDRESS, 0}, ADC1_RB7, ADC1_RB7_AN7, 0},
    #endif
    #ifdef ADC1_RB8_AN8
    {GPIO_PB8, hal_ll_adc_module_num(ADC_MODULE_1), {HAL_LL_AD1PCFG_REG_ADDRESS, 0}, ADC1_RB8, ADC1_RB8_AN8, 0},
    #endif
    #ifdef ADC1_RB9_AN9
    {GPIO_PB9, hal_ll_adc_module_num(ADC_MODULE_1), {HAL_LL_AD1PCFG_REG_ADDRESS, 0}, ADC1_RB9, ADC1_RB9_AN9, 0},
    #endif
    #ifdef ADC1_RE0_AN24
    {GPIO_PE0, hal_ll_adc_module_num(ADC_MODULE_1), {HAL_LL_AD1PCFG_REG_ADDRESS, 0}, ADC1_RE0, ADC1_RE0_AN24, 0},
    #endif
    #ifdef ADC1_RE1_AN25
    {GPIO_PE1, hal_ll_adc_module_num(ADC_MODULE_1), {HAL_LL_AD1PCFG_REG_ADDRESS, 0}, ADC1_RE1, ADC1_RE1_AN25, 0},
    #endif
    #ifdef ADC1_RE2_AN26
    {GPIO_PE2, hal_ll_adc_module_num(ADC_MODULE_1), {HAL_LL_AD1PCFG_REG_ADDRESS, 0}, ADC1_RE2, ADC1_RE2_AN26, 0},
    #endif
    #ifdef ADC1_RE3_AN27
    {GPIO_PE3, hal_ll_adc_module_num(ADC_MODULE_1), {HAL_LL_AD1PCFG_REG_ADDRESS, 0}, ADC1_RE3, ADC1_RE3_AN27, 0},
    #endif
    #ifdef ADC1_RE4_AN28
    {GPIO_PE4, hal_ll_adc_module_num(ADC_MODULE_1), {HAL_LL_AD1PCFG_REG_ADDRESS, 0}, ADC1_RE4, ADC1_RE4_AN28, 0},
    #endif
    #ifdef ADC1_RE5_AN29
    {GPIO_PE5, hal_ll_adc_module_num(ADC_MODULE_1), {HAL_LL_AD1PCFG_REG_ADDRESS, 0}, ADC1_RE5, ADC1_RE5_AN29, 0},
    #endif
    #ifdef ADC1_RE6_AN30
    {GPIO_PE6, hal_ll_adc_module_num(ADC_MODULE_1), {HAL_LL_AD1PCFG_REG_ADDRESS, 0}, ADC1_RE6, ADC1_RE6_AN30, 0},
    #endif
    #ifdef ADC1_RE7_AN31
    {GPIO_PE7, hal_ll_adc_module_num(ADC_MODULE_1), {HAL_LL_AD1PCFG_REG_ADDRESS, 0}, ADC1_RE7, ADC1_RE7_AN31, 0},
    #endif
    #ifdef ADC2_RB0_AN0
    {GPIO_PB0, hal_ll_adc_module_num(ADC_MODULE_2), {HAL_LL_AD1PCFG_REG_ADDRESS, 0}, ADC2_RB0, ADC2_RB0_AN0, 0},
    #endif
    #ifdef ADC2_RB1_AN1
    {GPIO_PB1, hal_ll_adc_module_num(ADC_MODULE_2), {HAL_LL_AD1PCFG_REG_ADDRESS, 0}, ADC2_RB1, ADC2_RB1_AN1, 0},
    #endif
    #ifdef ADC2_RB10_AN10
    {GPIO_PB10, hal_ll_adc_module_num(ADC_MODULE_2), {HAL_LL_AD1PCFG_REG_ADDRESS, 0}, ADC2_RB10, ADC2_RB10_AN10, 0},
    #endif
    #ifdef ADC2_RB11_AN11
    {GPIO_PB11, hal_ll_adc_module_num(ADC_MODULE_2), {HAL_LL_AD1PCFG_REG_ADDRESS, 0}, ADC2_RB11, ADC2_RB11_AN11, 0},
    #endif
    #ifdef ADC2_RB12_AN12
    {GPIO_PB12, hal_ll_adc_module_num(ADC_MODULE_2), {HAL_LL_AD1PCFG_REG_ADDRESS, 0}, ADC2_RB12, ADC2_RB12_AN12, 0},
    #endif
    #ifdef ADC2_RB13_AN13
    {GPIO_PB13, hal_ll_adc_module_num(ADC_MODULE_2), {HAL_LL_AD1PCFG_REG_ADDRESS, 0}, ADC2_RB13, ADC2_RB13_AN13, 0},
    #endif
    #ifdef ADC2_RB14_AN14
    {GPIO_PB14, hal_ll_adc_module_num(ADC_MODULE_2), {HAL_LL_AD1PCFG_REG_ADDRESS, 0}, ADC2_RB14, ADC2_RB14_AN14, 0},
    #endif
    #ifdef ADC2_RB15_AN15
    {GPIO_PB15, hal_ll_adc_module_num(ADC_MODULE_2), {HAL_LL_AD1PCFG_REG_ADDRESS, 0}, ADC2_RB15, ADC2_RB15_AN15, 0},
    #endif
    #ifdef ADC2_RB2_AN2
    {GPIO_PB2, hal_ll_adc_module_num(ADC_MODULE_2), {HAL_LL_AD1PCFG_REG_ADDRESS, 0}, ADC2_RB2, ADC2_RB2_AN2, 0},
    #endif
    #ifdef ADC2_RB3_AN3
    {GPIO_PB3, hal_ll_adc_module_num(ADC_MODULE_2), {HAL_LL_AD1PCFG_REG_ADDRESS, 0}, ADC2_RB3, ADC2_RB3_AN3, 0},
    #endif
    #ifdef ADC2_RB4_AN4
    {GPIO_PB4, hal_ll_adc_module_num(ADC_MODULE_2), {HAL_LL_AD1PCFG_REG_ADDRESS, 0}, ADC2_RB4, ADC2_RB4_AN4, 0},
    #endif
    #ifdef ADC2_RB5_AN5
    {GPIO_PB5, hal_ll_adc_module_num(ADC_MODULE_2), {HAL_LL_AD1PCFG_REG_ADDRESS, 0}, ADC2_RB5, ADC2_RB5_AN5, 0},
    #endif
    #ifdef ADC2_RB6_AN6
    {GPIO_PB6, hal_ll_adc_module_num(ADC_MODULE_2), {HAL_LL_AD1PCFG_REG_ADDRESS, 0}, ADC2_RB6, ADC2_RB6_AN6, 0},
    #endif
    #ifdef ADC2_RB7_AN7
    {GPIO_PB7, hal_ll_adc_module_num(ADC_MODULE_2), {HAL_LL_AD1PCFG_REG_ADDRESS, 0}, ADC2_RB7, ADC2_RB7_AN7, 0},
    #endif
    #ifdef ADC2_RB8_AN8
    {GPIO_PB8, hal_ll_adc_module_num(ADC_MODULE_2), {HAL_LL_AD1PCFG_REG_ADDRESS, 0}, ADC2_RB8, ADC2_RB8_AN8, 0},
    #endif
    #ifdef ADC2_RB9_AN9
    {GPIO_PB9, hal_ll_adc_module_num(ADC_MODULE_2), {HAL_LL_AD1PCFG_REG_ADDRESS, 0}, ADC2_RB9, ADC2_RB9_AN9, 0},
    #endif
    #ifdef ADC1_RA6_AN22
    {GPIO_PA6, hal_ll_adc_module_num(ADC_MODULE_1), {HAL_LL_AD1PCFG_REG_ADDRESS, 0}, ADC1_RA6, ADC1_RA6_AN22, 0},
    #endif
    #ifdef ADC1_RA7_AN23
    {GPIO_PA7, hal_ll_adc_module_num(ADC_MODULE_1), {HAL_LL_AD1PCFG_REG_ADDRESS, 0}, ADC1_RA7, ADC1_RA7_AN23, 0},
    #endif
    #ifdef ADC1_RC1_AN16
    {GPIO_PC1, hal_ll_adc_module_num(ADC_MODULE_1), {HAL_LL_AD1PCFG_REG_ADDRESS, 0}, ADC1_RC1, ADC1_RC1_AN16, 0},
    #endif
    #ifdef ADC1_RC2_AN17
    {GPIO_PC2, hal_ll_adc_module_num(ADC_MODULE_1), {HAL_LL_AD1PCFG_REG_ADDRESS, 0}, ADC1_RC2, ADC1_RC2_AN17, 0},
    #endif
    #ifdef ADC1_RC3_AN18
    {GPIO_PC3, hal_ll_adc_module_num(ADC_MODULE_1), {HAL_LL_AD1PCFG_REG_ADDRESS, 0}, ADC1_RC3, ADC1_RC3_AN18, 0},
    #endif
    #ifdef ADC1_RC4_AN19
    {GPIO_PC4, hal_ll_adc_module_num(ADC_MODULE_1), {HAL_LL_AD1PCFG_REG_ADDRESS, 0}, ADC1_RC4, ADC1_RC4_AN19, 0},
    #endif
    #ifdef ADC1_RE8_AN20
    {GPIO_PE8, hal_ll_adc_module_num(ADC_MODULE_1), {HAL_LL_AD1PCFG_REG_ADDRESS, 0}, ADC1_RE8, ADC1_RE8_AN20, 0},
    #endif
    #ifdef ADC1_RE9_AN21
    {GPIO_PE9, hal_ll_adc_module_num(ADC_MODULE_1), {HAL_LL_AD1PCFG_REG_ADDRESS, 0}, ADC1_RE9, ADC1_RE9_AN21, 0},
    #endif
    #ifdef ADC1_RA10_AN56
    {GPIO_PA10, hal_ll_adc_module_num(ADC_MODULE_1), {HAL_LL_AD1PCFG_REG_ADDRESS, 0}, ADC1_RA10, ADC1_RA10_AN56, 0},
    #endif
    #ifdef ADC1_RA7_AN55
    {GPIO_PA7, hal_ll_adc_module_num(ADC_MODULE_1), {HAL_LL_AD1PCFG_REG_ADDRESS, 0}, ADC1_RA7, ADC1_RA7_AN55, 0},
    #endif
    #ifdef ADC1_RC6_AN53
    {GPIO_PC6, hal_ll_adc_module_num(ADC_MODULE_1), {HAL_LL_AD1PCFG_REG_ADDRESS, 0}, ADC1_RC6, ADC1_RC6_AN53, 0},
    #endif
    #ifdef ADC1_RC7_AN52
    {GPIO_PC7, hal_ll_adc_module_num(ADC_MODULE_1), {HAL_LL_AD1PCFG_REG_ADDRESS, 0}, ADC1_RC7, ADC1_RC7_AN52, 0},
    #endif
    #ifdef ADC1_RC8_AN51
    {GPIO_PC8, hal_ll_adc_module_num(ADC_MODULE_1), {HAL_LL_AD1PCFG_REG_ADDRESS, 0}, ADC1_RC8, ADC1_RC8_AN51, 0},
    #endif
    #ifdef ADC1_RC9_AN54
    {GPIO_PC9, hal_ll_adc_module_num(ADC_MODULE_1), {HAL_LL_AD1PCFG_REG_ADDRESS, 0}, ADC1_RC9, ADC1_RC9_AN54, 0},
    #endif
    #ifdef ADC_RA0_AN0
    {GPIO_PA0, hal_ll_adc_module_num(ADC_MODULE), {HAL_LL_AD1PCFG_REG_ADDRESS, 0}, ADC_RA0, ADC_RA0_AN0, 0},
    #endif
    #ifdef ADC_RA1_AN1
    {GPIO_PA1, hal_ll_adc_module_num(ADC_MODULE), {HAL_LL_AD1PCFG_REG_ADDRESS, 0}, ADC_RA1, ADC_RA1_AN1, 0},
    #endif
    #ifdef ADC_RB0_AN2
    {GPIO_PB0, hal_ll_adc_module_num(ADC_MODULE), {HAL_LL_AD1PCFG_REG_ADDRESS, 0}, ADC_RB0, ADC_RB0_AN2, 0},
    #endif
    #ifdef ADC_RB1_AN3
    {GPIO_PB1, hal_ll_adc_module_num(ADC_MODULE), {HAL_LL_AD1PCFG_REG_ADDRESS, 0}, ADC_RB1, ADC_RB1_AN3, 0},
    #endif
    #ifdef ADC_RB13_AN11
    {GPIO_PB13, hal_ll_adc_module_num(ADC_MODULE), {HAL_LL_AD1PCFG_REG_ADDRESS, 0}, ADC_RB13, ADC_RB13_AN11, 0},
    #endif
    #ifdef ADC_RB14_AN10
    {GPIO_PB14, hal_ll_adc_module_num(ADC_MODULE), {HAL_LL_AD1PCFG_REG_ADDRESS, 0}, ADC_RB14, ADC_RB14_AN10, 0},
    #endif
    #ifdef ADC_RB15_AN9
    {GPIO_PB15, hal_ll_adc_module_num(ADC_MODULE), {HAL_LL_AD1PCFG_REG_ADDRESS, 0}, ADC_RB15, ADC_RB15_AN9, 0},
    #endif
    #ifdef ADC_RB2_AN4
    {GPIO_PB2, hal_ll_adc_module_num(ADC_MODULE), {HAL_LL_AD1PCFG_REG_ADDRESS, 0}, ADC_RB2, ADC_RB2_AN4, 0},
    #endif
    #ifdef ADC_RB3_AN5
    {GPIO_PB3, hal_ll_adc_module_num(ADC_MODULE), {HAL_LL_AD1PCFG_REG_ADDRESS, 0}, ADC_RB3, ADC_RB3_AN5, 0},
    #endif
    #ifdef ADC_RC0_AN6
    {GPIO_PC0, hal_ll_adc_module_num(ADC_MODULE), {HAL_LL_AD1PCFG_REG_ADDRESS, 0}, ADC_RC0, ADC_RC0_AN6, 0},
    #endif
    #ifdef ADC_RC1_AN7
    {GPIO_PC1, hal_ll_adc_module_num(ADC_MODULE), {HAL_LL_AD1PCFG_REG_ADDRESS, 0}, ADC_RC1, ADC_RC1_AN7, 0},
    #endif
    #ifdef ADC_RC2_AN8
    {GPIO_PC2, hal_ll_adc_module_num(ADC_MODULE), {HAL_LL_AD1PCFG_REG_ADDRESS, 0}, ADC_RC2, ADC_RC2_AN8, 0},
    #endif
    #ifdef ADC_RC1_AN16
    {GPIO_PC1, hal_ll_adc_module_num(ADC_MODULE), {HAL_LL_AD1PCFG_REG_ADDRESS, 0}, ADC_RC1, ADC_RC1_AN16, 0},
    #endif
    #ifdef ADC_RC2_AN17
    {GPIO_PC2, hal_ll_adc_module_num(ADC_MODULE), {HAL_LL_AD1PCFG_REG_ADDRESS, 0}, ADC_RC2, ADC_RC2_AN17, 0},
    #endif
    #ifdef ADC_RA12_AN20
    {GPIO_PA12, hal_ll_adc_module_num(ADC_MODULE), {HAL_LL_AD1PCFG_REG_ADDRESS, 0}, ADC_RA12, ADC_RA12_AN20, 0},
    #endif
    #ifdef ADC_RA13_AN21
    {GPIO_PA13, hal_ll_adc_module_num(ADC_MODULE), {HAL_LL_AD1PCFG_REG_ADDRESS, 0}, ADC_RA13, ADC_RA13_AN21, 0},
    #endif
    #ifdef ADC_RA6_AN22
    {GPIO_PA6, hal_ll_adc_module_num(ADC_MODULE), {HAL_LL_AD1PCFG_REG_ADDRESS, 0}, ADC_RA6, ADC_RA6_AN22, 0},
    #endif
    #ifdef ADC_RA7_AN23
    {GPIO_PA7, hal_ll_adc_module_num(ADC_MODULE), {HAL_LL_AD1PCFG_REG_ADDRESS, 0}, ADC_RA7, ADC_RA7_AN23, 0},
    #endif
    #ifdef ADC_RC3_AN18
    {GPIO_PC3, hal_ll_adc_module_num(ADC_MODULE), {HAL_LL_AD1PCFG_REG_ADDRESS, 0}, ADC_RC3, ADC_RC3_AN18, 0},
    #endif
    #ifdef ADC_RC4_AN19
    {GPIO_PC4, hal_ll_adc_module_num(ADC_MODULE), {HAL_LL_AD1PCFG_REG_ADDRESS, 0}, ADC_RC4, ADC_RC4_AN19, 0},
    #endif
    #ifdef ADC_RE0_AN24
    {GPIO_PE0, hal_ll_adc_module_num(ADC_MODULE), {HAL_LL_AD1PCFG_REG_ADDRESS, 0}, ADC_RE0, ADC_RE0_AN24, 0},
    #endif
    #ifdef ADC_RE1_AN25
    {GPIO_PE1, hal_ll_adc_module_num(ADC_MODULE), {HAL_LL_AD1PCFG_REG_ADDRESS, 0}, ADC_RE1, ADC_RE1_AN25, 0},
    #endif
    #ifdef ADC_RE2_AN26
    {GPIO_PE2, hal_ll_adc_module_num(ADC_MODULE), {HAL_LL_AD1PCFG_REG_ADDRESS, 0}, ADC_RE2, ADC_RE2_AN26, 0},
    #endif
    #ifdef ADC_RE3_AN27
    {GPIO_PE3, hal_ll_adc_module_num(ADC_MODULE), {HAL_LL_AD1PCFG_REG_ADDRESS, 0}, ADC_RE3, ADC_RE3_AN27, 0},
    #endif
    #ifdef ADC_RE4_AN28
    {GPIO_PE4, hal_ll_adc_module_num(ADC_MODULE), {HAL_LL_AD1PCFG_REG_ADDRESS, 0}, ADC_RE4, ADC_RE4_AN28, 0},
    #endif
    #ifdef ADC_RE5_AN29
    {GPIO_PE5, hal_ll_adc_module_num(ADC_MODULE), {HAL_LL_AD1PCFG_REG_ADDRESS, 0}, ADC_RE5, ADC_RE5_AN29, 0},
    #endif
    #ifdef ADC_RE6_AN30
    {GPIO_PE6, hal_ll_adc_module_num(ADC_MODULE), {HAL_LL_AD1PCFG_REG_ADDRESS, 0}, ADC_RE6, ADC_RE6_AN30, 0},
    #endif
    #ifdef ADC_RE7_AN31
    {GPIO_PE7, hal_ll_adc_module_num(ADC_MODULE), {HAL_LL_AD1PCFG_REG_ADDRESS, 0}, ADC_RE7, ADC_RE7_AN31, 0},
    #endif
    #ifdef ADC2_RC1_AN16
    {GPIO_PC1, hal_ll_adc_module_num(ADC_MODULE_2), {HAL_LL_AD1PCFG_REG_ADDRESS, 0}, ADC2_RC1, ADC2_RC1_AN16, 0},
    #endif
    #ifdef ADC2_RC2_AN17
    {GPIO_PC2, hal_ll_adc_module_num(ADC_MODULE_2), {HAL_LL_AD1PCFG_REG_ADDRESS, 0}, ADC2_RC2, ADC2_RC2_AN17, 0},
    #endif
    #ifdef ADC1_RA12_AN20
    {GPIO_PA12, hal_ll_adc_module_num(ADC_MODULE_1), {HAL_LL_AD1PCFG_REG_ADDRESS, 0}, ADC1_RA12, ADC1_RA12_AN20, 0},
    #endif
    #ifdef ADC1_RA13_AN21
    {GPIO_PA13, hal_ll_adc_module_num(ADC_MODULE_1), {HAL_LL_AD1PCFG_REG_ADDRESS, 0}, ADC1_RA13, ADC1_RA13_AN21, 0},
    #endif
    #ifdef ADC2_RA12_AN20
    {GPIO_PA12, hal_ll_adc_module_num(ADC_MODULE_2), {HAL_LL_AD1PCFG_REG_ADDRESS, 0}, ADC2_RA12, ADC2_RA12_AN20, 0},
    #endif
    #ifdef ADC2_RA13_AN21
    {GPIO_PA13, hal_ll_adc_module_num(ADC_MODULE_2), {HAL_LL_AD1PCFG_REG_ADDRESS, 0}, ADC2_RA13, ADC2_RA13_AN21, 0},
    #endif
    #ifdef ADC2_RA6_AN22
    {GPIO_PA6, hal_ll_adc_module_num(ADC_MODULE_2), {HAL_LL_AD1PCFG_REG_ADDRESS, 0}, ADC2_RA6, ADC2_RA6_AN22, 0},
    #endif
    #ifdef ADC2_RA7_AN23
    {GPIO_PA7, hal_ll_adc_module_num(ADC_MODULE_2), {HAL_LL_AD1PCFG_REG_ADDRESS, 0}, ADC2_RA7, ADC2_RA7_AN23, 0},
    #endif
    #ifdef ADC2_RC3_AN18
    {GPIO_PC3, hal_ll_adc_module_num(ADC_MODULE_2), {HAL_LL_AD1PCFG_REG_ADDRESS, 0}, ADC2_RC3, ADC2_RC3_AN18, 0},
    #endif
    #ifdef ADC2_RC4_AN19
    {GPIO_PC4, hal_ll_adc_module_num(ADC_MODULE_2), {HAL_LL_AD1PCFG_REG_ADDRESS, 0}, ADC2_RC4, ADC2_RC4_AN19, 0},
    #endif
    #ifdef ADC2_RE0_AN24
    {GPIO_PE0, hal_ll_adc_module_num(ADC_MODULE_2), {HAL_LL_AD1PCFG_REG_ADDRESS, 0}, ADC2_RE0, ADC2_RE0_AN24, 0},
    #endif
    #ifdef ADC2_RE1_AN25
    {GPIO_PE1, hal_ll_adc_module_num(ADC_MODULE_2), {HAL_LL_AD1PCFG_REG_ADDRESS, 0}, ADC2_RE1, ADC2_RE1_AN25, 0},
    #endif
    #ifdef ADC2_RE2_AN26
    {GPIO_PE2, hal_ll_adc_module_num(ADC_MODULE_2), {HAL_LL_AD1PCFG_REG_ADDRESS, 0}, ADC2_RE2, ADC2_RE2_AN26, 0},
    #endif
    #ifdef ADC2_RE3_AN27
    {GPIO_PE3, hal_ll_adc_module_num(ADC_MODULE_2), {HAL_LL_AD1PCFG_REG_ADDRESS, 0}, ADC2_RE3, ADC2_RE3_AN27, 0},
    #endif
    #ifdef ADC2_RE4_AN28
    {GPIO_PE4, hal_ll_adc_module_num(ADC_MODULE_2), {HAL_LL_AD1PCFG_REG_ADDRESS, 0}, ADC2_RE4, ADC2_RE4_AN28, 0},
    #endif
    #ifdef ADC2_RE5_AN29
    {GPIO_PE5, hal_ll_adc_module_num(ADC_MODULE_2), {HAL_LL_AD1PCFG_REG_ADDRESS, 0}, ADC2_RE5, ADC2_RE5_AN29, 0},
    #endif
    #ifdef ADC2_RE6_AN30
    {GPIO_PE6, hal_ll_adc_module_num(ADC_MODULE_2), {HAL_LL_AD1PCFG_REG_ADDRESS, 0}, ADC2_RE6, ADC2_RE6_AN30, 0},
    #endif
    #ifdef ADC2_RE7_AN31
    {GPIO_PE7, hal_ll_adc_module_num(ADC_MODULE_2), {HAL_LL_AD1PCFG_REG_ADDRESS, 0}, ADC2_RE7, ADC2_RE7_AN31, 0},
    #endif
    #ifdef ADC_RE8_AN20
    {GPIO_PE8, hal_ll_adc_module_num(ADC_MODULE), {HAL_LL_AD1PCFG_REG_ADDRESS, 0}, ADC_RE8, ADC_RE8_AN20, 0},
    #endif
    #ifdef ADC_RE9_AN21
    {GPIO_PE9, hal_ll_adc_module_num(ADC_MODULE), {HAL_LL_AD1PCFG_REG_ADDRESS, 0}, ADC_RE9, ADC_RE9_AN21, 0},
    #endif
    #ifdef ADC2_RE8_AN20
    {GPIO_PE8, hal_ll_adc_module_num(ADC_MODULE_2), {HAL_LL_AD1PCFG_REG_ADDRESS, 0}, ADC2_RE8, ADC2_RE8_AN20, 0},
    #endif
    #ifdef ADC2_RE9_AN21
    {GPIO_PE9, hal_ll_adc_module_num(ADC_MODULE_2), {HAL_LL_AD1PCFG_REG_ADDRESS, 0}, ADC2_RE9, ADC2_RE9_AN21, 0},
    #endif
    #ifdef ADC_RA2_AN2
    {GPIO_PA2, hal_ll_adc_module_num(ADC_MODULE), {HAL_LL_AD1PCFG_REG_ADDRESS, 0}, ADC_RA2, ADC_RA2_AN2, 0},
    #endif
    #ifdef ADC_RB0_AN3
    {GPIO_PB0, hal_ll_adc_module_num(ADC_MODULE), {HAL_LL_AD1PCFG_REG_ADDRESS, 0}, ADC_RB0, ADC_RB0_AN3, 0},
    #endif
    #ifdef ADC_RB1_AN6
    {GPIO_PB1, hal_ll_adc_module_num(ADC_MODULE), {HAL_LL_AD1PCFG_REG_ADDRESS, 0}, ADC_RB1, ADC_RB1_AN6, 0},
    #endif
    #ifdef ADC_RB10_AN5
    {GPIO_PB10, hal_ll_adc_module_num(ADC_MODULE), {HAL_LL_AD1PCFG_REG_ADDRESS, 0}, ADC_RB10, ADC_RB10_AN5, 0},
    #endif
    #ifdef ADC_RB2_AN7
    {GPIO_PB2, hal_ll_adc_module_num(ADC_MODULE), {HAL_LL_AD1PCFG_REG_ADDRESS, 0}, ADC_RB2, ADC_RB2_AN7, 0},
    #endif
    #ifdef ADC_RB9_AN4
    {GPIO_PB9, hal_ll_adc_module_num(ADC_MODULE), {HAL_LL_AD1PCFG_REG_ADDRESS, 0}, ADC_RB9, ADC_RB9_AN4, 0},
    #endif
    #ifdef ADC_RC1_AN8
    {GPIO_PC1, hal_ll_adc_module_num(ADC_MODULE), {HAL_LL_AD1PCFG_REG_ADDRESS, 0}, ADC_RC1, ADC_RC1_AN8, 0},
    #endif
    #ifdef ADC_RC10_AN10
    {GPIO_PC10, hal_ll_adc_module_num(ADC_MODULE), {HAL_LL_AD1PCFG_REG_ADDRESS, 0}, ADC_RC10, ADC_RC10_AN10, 0},
    #endif
    #ifdef ADC_RC2_AN9
    {GPIO_PC2, hal_ll_adc_module_num(ADC_MODULE), {HAL_LL_AD1PCFG_REG_ADDRESS, 0}, ADC_RC2, ADC_RC2_AN9, 0},
    #endif
    #ifdef ADC_RC9_AN11
    {GPIO_PC9, hal_ll_adc_module_num(ADC_MODULE), {HAL_LL_AD1PCFG_REG_ADDRESS, 0}, ADC_RC9, ADC_RC9_AN11, 0},
    #endif
    #ifdef ADC_RA4_AN10
    {GPIO_PA4, hal_ll_adc_module_num(ADC_MODULE), {HAL_LL_AD1PCFG_REG_ADDRESS, 0}, ADC_RA4, ADC_RA4_AN10, 0},
    #endif
    #ifdef ADC_RB4_AN9
    {GPIO_PB4, hal_ll_adc_module_num(ADC_MODULE), {HAL_LL_AD1PCFG_REG_ADDRESS, 0}, ADC_RB4, ADC_RB4_AN9, 0},
    #endif
    #ifdef ADC_RC3_AN11
    {GPIO_PC3, hal_ll_adc_module_num(ADC_MODULE), {HAL_LL_AD1PCFG_REG_ADDRESS, 0}, ADC_RC3, ADC_RC3_AN11, 0},
    #endif
    #ifdef ADC_RC4_AN12
    {GPIO_PC4, hal_ll_adc_module_num(ADC_MODULE), {HAL_LL_AD1PCFG_REG_ADDRESS, 0}, ADC_RC4, ADC_RC4_AN12, 0},
    #endif
    #ifdef ADC_RC5_AN15
    {GPIO_PC5, hal_ll_adc_module_num(ADC_MODULE), {HAL_LL_AD1PCFG_REG_ADDRESS, 0}, ADC_RC5, ADC_RC5_AN15, 0},
    #endif
    #ifdef ADC1_RA2_AN13
    {GPIO_PA2, hal_ll_adc_module_num(ADC_MODULE_1), {HAL_LL_AD1PCFG_REG_ADDRESS, 0}, ADC1_RA2, ADC1_RA2_AN13, 0},
    #endif
    #ifdef ADC1_RA3_AN14
    {GPIO_PA3, hal_ll_adc_module_num(ADC_MODULE_1), {HAL_LL_AD1PCFG_REG_ADDRESS, 0}, ADC1_RA3, ADC1_RA3_AN14, 0},
    #endif
    #ifdef ADC1_RB13_AN11
    {GPIO_PB13, hal_ll_adc_module_num(ADC_MODULE_1), {HAL_LL_AD1PCFG_REG_ADDRESS, 0}, ADC1_RB13, ADC1_RB13_AN11, 0},
    #endif
    #ifdef ADC1_RB14_AN10
    {GPIO_PB14, hal_ll_adc_module_num(ADC_MODULE_1), {HAL_LL_AD1PCFG_REG_ADDRESS, 0}, ADC1_RB14, ADC1_RB14_AN10, 0},
    #endif
    #ifdef ADC1_RB15_AN9
    {GPIO_PB15, hal_ll_adc_module_num(ADC_MODULE_1), {HAL_LL_AD1PCFG_REG_ADDRESS, 0}, ADC1_RB15, ADC1_RB15_AN9, 0},
    #endif
    #ifdef ADC1_RB4_AN15
    {GPIO_PB4, hal_ll_adc_module_num(ADC_MODULE_1), {HAL_LL_AD1PCFG_REG_ADDRESS, 0}, ADC1_RB4, ADC1_RB4_AN15, 0},
    #endif
    #ifdef ADC1_RA4_AN16
    {GPIO_PA4, hal_ll_adc_module_num(ADC_MODULE_1), {HAL_LL_AD1PCFG_REG_ADDRESS, 0}, ADC1_RA4, ADC1_RA4_AN16, 0},
    #endif
    #ifdef ADC1_RB5_AN17
    {GPIO_PB5, hal_ll_adc_module_num(ADC_MODULE_1), {HAL_LL_AD1PCFG_REG_ADDRESS, 0}, ADC1_RB5, ADC1_RB5_AN17, 0},
    #endif
    #ifdef ADC1_RB6_AN18
    {GPIO_PB6, hal_ll_adc_module_num(ADC_MODULE_1), {HAL_LL_AD1PCFG_REG_ADDRESS, 0}, ADC1_RB6, ADC1_RB6_AN18, 0},
    #endif
    #ifdef ADC1_RB7_AN19
    {GPIO_PB7, hal_ll_adc_module_num(ADC_MODULE_1), {HAL_LL_AD1PCFG_REG_ADDRESS, 0}, ADC1_RB7, ADC1_RB7_AN19, 0},
    #endif
    #ifdef ADC1_RB8_AN20
    {GPIO_PB8, hal_ll_adc_module_num(ADC_MODULE_1), {HAL_LL_AD1PCFG_REG_ADDRESS, 0}, ADC1_RB8, ADC1_RB8_AN20, 0},
    #endif
    #ifdef ADC1_RB9_AN21
    {GPIO_PB9, hal_ll_adc_module_num(ADC_MODULE_1), {HAL_LL_AD1PCFG_REG_ADDRESS, 0}, ADC1_RB9, ADC1_RB9_AN21, 0},
    #endif
    #ifdef ADC1_RA6_AN23
    {GPIO_PA6, hal_ll_adc_module_num(ADC_MODULE_1), {HAL_LL_AD1PCFG_REG_ADDRESS, 0}, ADC1_RA6, ADC1_RA6_AN23, 0},
    #endif
    #ifdef ADC1_RA7_AN22
    {GPIO_PA7, hal_ll_adc_module_num(ADC_MODULE_1), {HAL_LL_AD1PCFG_REG_ADDRESS, 0}, ADC1_RA7, ADC1_RA7_AN22, 0},
    #endif
    #ifdef ADC1_RC4_AN16
    {GPIO_PC4, hal_ll_adc_module_num(ADC_MODULE_1), {HAL_LL_AD1PCFG_REG_ADDRESS, 0}, ADC1_RC4, ADC1_RC4_AN16, 0},
    #endif
    #ifdef ADC1_RG6_AN17
    {GPIO_PG6, hal_ll_adc_module_num(ADC_MODULE_1), {HAL_LL_AD1PCFG_REG_ADDRESS, 0}, ADC1_RG6, ADC1_RG6_AN17, 0},
    #endif
    #ifdef ADC1_RG8_AN19
    {GPIO_PG8, hal_ll_adc_module_num(ADC_MODULE_1), {HAL_LL_AD1PCFG_REG_ADDRESS, 0}, ADC1_RG8, ADC1_RG8_AN19, 0},
    #endif
    #ifdef ADC1_RG9_AN20
    {GPIO_PG9, hal_ll_adc_module_num(ADC_MODULE_1), {HAL_LL_AD1PCFG_REG_ADDRESS, 0}, ADC1_RG9, ADC1_RG9_AN20, 0},
    #endif
    #ifdef ADC1_RB12_AN8
    {GPIO_PB12, hal_ll_adc_module_num(ADC_MODULE_1), {HAL_LL_AD1PCFG_REG_ADDRESS, 0}, ADC1_RB12, ADC1_RB12_AN8, 0},
    #endif
    #ifdef ADC1_RB13_AN7
    {GPIO_PB13, hal_ll_adc_module_num(ADC_MODULE_1), {HAL_LL_AD1PCFG_REG_ADDRESS, 0}, ADC1_RB13, ADC1_RB13_AN7, 0},
    #endif
    #ifdef ADC1_RB14_AN6
    {GPIO_PB14, hal_ll_adc_module_num(ADC_MODULE_1), {HAL_LL_AD1PCFG_REG_ADDRESS, 0}, ADC1_RB14, ADC1_RB14_AN6, 0},
    #endif
    #ifdef ADC1_RC0_AN10
    {GPIO_PC0, hal_ll_adc_module_num(ADC_MODULE_1), {HAL_LL_AD1PCFG_REG_ADDRESS, 0}, ADC1_RC0, ADC1_RC0_AN10, 0},
    #endif
    #ifdef ADC1_RC1_AN11
    {GPIO_PC1, hal_ll_adc_module_num(ADC_MODULE_1), {HAL_LL_AD1PCFG_REG_ADDRESS, 0}, ADC1_RC1, ADC1_RC1_AN11, 0},
    #endif
    #ifdef ADC1_RC2_AN12
    {GPIO_PC2, hal_ll_adc_module_num(ADC_MODULE_1), {HAL_LL_AD1PCFG_REG_ADDRESS, 0}, ADC1_RC2, ADC1_RC2_AN12, 0},
    #endif
    #ifdef ADC1_RC3_AN13
    {GPIO_PC3, hal_ll_adc_module_num(ADC_MODULE_1), {HAL_LL_AD1PCFG_REG_ADDRESS, 0}, ADC1_RC3, ADC1_RC3_AN13, 0},
    #endif
    #ifdef ADC1_RD0_AN43
    {GPIO_PD0, hal_ll_adc_module_num(ADC_MODULE_1), {HAL_LL_AD1PCFG_REG_ADDRESS, 0}, ADC1_RD0, ADC1_RD0_AN43, 0},
    #endif
    #ifdef ADC1_RD1_AN35
    {GPIO_PD1, hal_ll_adc_module_num(ADC_MODULE_1), {HAL_LL_AD1PCFG_REG_ADDRESS, 0}, ADC1_RD1, ADC1_RD1_AN35, 0},
    #endif
    #ifdef ADC1_RD10_AN41
    {GPIO_PD10, hal_ll_adc_module_num(ADC_MODULE_1), {HAL_LL_AD1PCFG_REG_ADDRESS, 0}, ADC1_RD10, ADC1_RD10_AN41, 0},
    #endif
    #ifdef ADC1_RD11_AN42
    {GPIO_PD11, hal_ll_adc_module_num(ADC_MODULE_1), {HAL_LL_AD1PCFG_REG_ADDRESS, 0}, ADC1_RD11, ADC1_RD11_AN42, 0},
    #endif
    #ifdef ADC1_RD2_AN25
    {GPIO_PD2, hal_ll_adc_module_num(ADC_MODULE_1), {HAL_LL_AD1PCFG_REG_ADDRESS, 0}, ADC1_RD2, ADC1_RD2_AN25, 0},
    #endif
    #ifdef ADC1_RD3_AN44
    {GPIO_PD3, hal_ll_adc_module_num(ADC_MODULE_1), {HAL_LL_AD1PCFG_REG_ADDRESS, 0}, ADC1_RD3, ADC1_RD3_AN44, 0},
    #endif
    #ifdef ADC1_RD4_AN47
    {GPIO_PD4, hal_ll_adc_module_num(ADC_MODULE_1), {HAL_LL_AD1PCFG_REG_ADDRESS, 0}, ADC1_RD4, ADC1_RD4_AN47, 0},
    #endif
    #ifdef ADC1_RD5_AN48
    {GPIO_PD5, hal_ll_adc_module_num(ADC_MODULE_1), {HAL_LL_AD1PCFG_REG_ADDRESS, 0}, ADC1_RD5, ADC1_RD5_AN48, 0},
    #endif
    #ifdef ADC1_RD6_AN34
    {GPIO_PD6, hal_ll_adc_module_num(ADC_MODULE_1), {HAL_LL_AD1PCFG_REG_ADDRESS, 0}, ADC1_RD6, ADC1_RD6_AN34, 0},
    #endif
    #ifdef ADC1_RD7_AN20
    {GPIO_PD7, hal_ll_adc_module_num(ADC_MODULE_1), {HAL_LL_AD1PCFG_REG_ADDRESS, 0}, ADC1_RD7, ADC1_RD7_AN20, 0},
    #endif
    #ifdef ADC1_RD8_AN40
    {GPIO_PD8, hal_ll_adc_module_num(ADC_MODULE_1), {HAL_LL_AD1PCFG_REG_ADDRESS, 0}, ADC1_RD8, ADC1_RD8_AN40, 0},
    #endif
    #ifdef ADC1_RD9_AN24
    {GPIO_PD9, hal_ll_adc_module_num(ADC_MODULE_1), {HAL_LL_AD1PCFG_REG_ADDRESS, 0}, ADC1_RD9, ADC1_RD9_AN24, 0},
    #endif
    #ifdef ADC1_RF3_AN30
    {GPIO_PF3, hal_ll_adc_module_num(ADC_MODULE_1), {HAL_LL_AD1PCFG_REG_ADDRESS, 0}, ADC1_RF3, ADC1_RF3_AN30, 0},
    #endif
    #ifdef ADC1_RF4_AN11
    {GPIO_PF4, hal_ll_adc_module_num(ADC_MODULE_1), {HAL_LL_AD1PCFG_REG_ADDRESS, 0}, ADC1_RF4, ADC1_RF4_AN11, 0},
    #endif
    #ifdef ADC1_RF5_AN10
    {GPIO_PF5, hal_ll_adc_module_num(ADC_MODULE_1), {HAL_LL_AD1PCFG_REG_ADDRESS, 0}, ADC1_RF5, ADC1_RF5_AN10, 0},
    #endif
    #ifdef ADC1_RG9_AN49
    {GPIO_PG9, hal_ll_adc_module_num(ADC_MODULE_1), {HAL_LL_AD1PCFG_REG_ADDRESS, 0}, ADC1_RG9, ADC1_RG9_AN49, 0},
    #endif
    #ifdef ADC1_RA1_AN26
    {GPIO_PA1, hal_ll_adc_module_num(ADC_MODULE_1), {HAL_LL_AD1PCFG_REG_ADDRESS, 0}, ADC1_RA1, ADC1_RA1_AN26, 0},
    #endif
    #ifdef ADC1_RA14_AN38
    {GPIO_PA14, hal_ll_adc_module_num(ADC_MODULE_1), {HAL_LL_AD1PCFG_REG_ADDRESS, 0}, ADC1_RA14, ADC1_RA14_AN38, 0},
    #endif
    #ifdef ADC1_RA15_AN39
    {GPIO_PA15, hal_ll_adc_module_num(ADC_MODULE_1), {HAL_LL_AD1PCFG_REG_ADDRESS, 0}, ADC1_RA15, ADC1_RA15_AN39, 0},
    #endif
    #ifdef ADC1_RA4_AN36
    {GPIO_PA4, hal_ll_adc_module_num(ADC_MODULE_1), {HAL_LL_AD1PCFG_REG_ADDRESS, 0}, ADC1_RA4, ADC1_RA4_AN36, 0},
    #endif
    #ifdef ADC1_RA5_AN37
    {GPIO_PA5, hal_ll_adc_module_num(ADC_MODULE_1), {HAL_LL_AD1PCFG_REG_ADDRESS, 0}, ADC1_RA5, ADC1_RA5_AN37, 0},
    #endif
    #ifdef ADC1_RC3_AN9
    {GPIO_PC3, hal_ll_adc_module_num(ADC_MODULE_1), {HAL_LL_AD1PCFG_REG_ADDRESS, 0}, ADC1_RC3, ADC1_RC3_AN9, 0},
    #endif
    #ifdef ADC1_RD12_AN45
    {GPIO_PD12, hal_ll_adc_module_num(ADC_MODULE_1), {HAL_LL_AD1PCFG_REG_ADDRESS, 0}, ADC1_RD12, ADC1_RD12_AN45, 0},
    #endif
    #ifdef ADC1_RD13_AN46
    {GPIO_PD13, hal_ll_adc_module_num(ADC_MODULE_1), {HAL_LL_AD1PCFG_REG_ADDRESS, 0}, ADC1_RD13, ADC1_RD13_AN46, 0},
    #endif
    #ifdef ADC1_RD14_AN28
    {GPIO_PD14, hal_ll_adc_module_num(ADC_MODULE_1), {HAL_LL_AD1PCFG_REG_ADDRESS, 0}, ADC1_RD14, ADC1_RD14_AN28, 0},
    #endif
    #ifdef ADC1_RD15_AN29
    {GPIO_PD15, hal_ll_adc_module_num(ADC_MODULE_1), {HAL_LL_AD1PCFG_REG_ADDRESS, 0}, ADC1_RD15, ADC1_RD15_AN29, 0},
    #endif
    #ifdef ADC1_RF13_AN27
    {GPIO_PF13, hal_ll_adc_module_num(ADC_MODULE_1), {HAL_LL_AD1PCFG_REG_ADDRESS, 0}, ADC1_RF13, ADC1_RF13_AN27, 0},
    #endif
    #ifdef ADC1_RF2_AN31
    {GPIO_PF2, hal_ll_adc_module_num(ADC_MODULE_1), {HAL_LL_AD1PCFG_REG_ADDRESS, 0}, ADC1_RF2, ADC1_RF2_AN31, 0},
    #endif
    #ifdef ADC1_RF8_AN32
    {GPIO_PF8, hal_ll_adc_module_num(ADC_MODULE_1), {HAL_LL_AD1PCFG_REG_ADDRESS, 0}, ADC1_RF8, ADC1_RF8_AN32, 0},
    #endif
    #ifdef ADC1_RG15_AN33
    {GPIO_PG15, hal_ll_adc_module_num(ADC_MODULE_1), {HAL_LL_AD1PCFG_REG_ADDRESS, 0}, ADC1_RG15, ADC1_RG15_AN33, 0},
    #endif
    #ifdef ADC1_RC3_AN12
    {GPIO_PC3, hal_ll_adc_module_num(ADC_MODULE_1), {HAL_LL_AD1PCFG_REG_ADDRESS, 0}, ADC1_RC3, ADC1_RC3_AN12, 0},
    #endif
    #endif
    // EOF list

    // BEGIN ADPCFGL/H
    #ifdef _ADC_ADPCFGLH_
    #ifdef ADC_RB0_AN0
    {GPIO_PB0, hal_ll_adc_module_num(ADC_MODULE), {HAL_LL_AD1PCFGL_REG_ADDRESS, HAL_LL_AD2PCFGL_REG_ADDRESS}, ADC_RB0, ADC_RB0_AN0, 0},
    #endif
    #ifdef ADC_RB1_AN1
    {GPIO_PB1, hal_ll_adc_module_num(ADC_MODULE), {HAL_LL_AD1PCFGL_REG_ADDRESS, HAL_LL_AD2PCFGL_REG_ADDRESS}, ADC_RB1, ADC_RB1_AN1, 0},
    #endif
    #ifdef ADC_RB2_AN2
    {GPIO_PB2, hal_ll_adc_module_num(ADC_MODULE), {HAL_LL_AD1PCFGL_REG_ADDRESS, HAL_LL_AD2PCFGL_REG_ADDRESS}, ADC_RB2, ADC_RB2_AN2, 0},
    #endif
    #ifdef ADC_RB3_AN3
    {GPIO_PB3, hal_ll_adc_module_num(ADC_MODULE), {HAL_LL_AD1PCFGL_REG_ADDRESS, HAL_LL_AD2PCFGL_REG_ADDRESS}, ADC_RB3, ADC_RB3_AN3, 0},
    #endif
    #ifdef ADC_RB4_AN4
    {GPIO_PB4, hal_ll_adc_module_num(ADC_MODULE), {HAL_LL_AD1PCFGL_REG_ADDRESS, HAL_LL_AD2PCFGL_REG_ADDRESS}, ADC_RB4, ADC_RB4_AN4, 0},
    #endif
    #ifdef ADC_RB5_AN5
    {GPIO_PB5, hal_ll_adc_module_num(ADC_MODULE), {HAL_LL_AD1PCFGL_REG_ADDRESS, HAL_LL_AD2PCFGL_REG_ADDRESS}, ADC_RB5, ADC_RB5_AN5, 0},
    #endif
    #ifdef ADC_RB6_AN6
    {GPIO_PB6, hal_ll_adc_module_num(ADC_MODULE), {HAL_LL_AD1PCFGL_REG_ADDRESS, HAL_LL_AD2PCFGL_REG_ADDRESS}, ADC_RB6, ADC_RB6_AN6, 0},
    #endif
    #ifdef ADC_RB7_AN7
    {GPIO_PB7, hal_ll_adc_module_num(ADC_MODULE), {HAL_LL_AD1PCFGL_REG_ADDRESS, HAL_LL_AD2PCFGL_REG_ADDRESS}, ADC_RB7, ADC_RB7_AN7, 0},
    #endif
    #ifdef ADC_RB8_AN8
    {GPIO_PB8, hal_ll_adc_module_num(ADC_MODULE), {HAL_LL_AD1PCFGL_REG_ADDRESS, HAL_LL_AD2PCFGL_REG_ADDRESS}, ADC_RB8, ADC_RB8_AN8, 0},
    #endif
    #ifdef ADC_RB9_AN9
    {GPIO_PB9, hal_ll_adc_module_num(ADC_MODULE), {HAL_LL_AD1PCFGL_REG_ADDRESS, HAL_LL_AD2PCFGL_REG_ADDRESS}, ADC_RB9, ADC_RB9_AN9, 0},
    #endif
    #ifdef ADC_RB10_AN10
    {GPIO_PB10, hal_ll_adc_module_num(ADC_MODULE), {HAL_LL_AD1PCFGL_REG_ADDRESS, HAL_LL_AD2PCFGL_REG_ADDRESS}, ADC_RB10, ADC_RB10_AN10, 0},
    #endif
    #ifdef ADC_RB11_AN11
    {GPIO_PB11, hal_ll_adc_module_num(ADC_MODULE), {HAL_LL_AD1PCFGL_REG_ADDRESS, HAL_LL_AD2PCFGL_REG_ADDRESS}, ADC_RB11, ADC_RB11_AN11, 0},
    #endif
    #ifdef ADC_RB12_AN12
    {GPIO_PB12, hal_ll_adc_module_num(ADC_MODULE), {HAL_LL_AD1PCFGL_REG_ADDRESS, HAL_LL_AD2PCFGL_REG_ADDRESS}, ADC_RB12, ADC_RB12_AN12, 0},
    #endif
    #ifdef ADC_RB13_AN13
    {GPIO_PB13, hal_ll_adc_module_num(ADC_MODULE), {HAL_LL_AD1PCFGL_REG_ADDRESS, HAL_LL_AD2PCFGL_REG_ADDRESS}, ADC_RB13, ADC_RB13_AN13, 0},
    #endif
    #ifdef ADC_RB14_AN14
    {GPIO_PB14, hal_ll_adc_module_num(ADC_MODULE), {HAL_LL_AD1PCFGL_REG_ADDRESS, HAL_LL_AD2PCFGL_REG_ADDRESS}, ADC_RB14, ADC_RB14_AN14, 0},
    #endif
    #ifdef ADC_RB15_AN15
    {GPIO_PB15, hal_ll_adc_module_num(ADC_MODULE), {HAL_LL_AD1PCFGL_REG_ADDRESS, HAL_LL_AD2PCFGL_REG_ADDRESS}, ADC_RB15, ADC_RB15_AN15, 0},
    #endif
    #ifdef ADC1_RA0_AN0
    {GPIO_PA0, hal_ll_adc_module_num(ADC_MODULE_1), {HAL_LL_AD1PCFGL_REG_ADDRESS, HAL_LL_AD2PCFGL_REG_ADDRESS}, ADC1_RA0, ADC1_RA0_AN0, 0},
    #endif
    #ifdef ADC1_RA1_AN1
    {GPIO_PA1, hal_ll_adc_module_num(ADC_MODULE_1), {HAL_LL_AD1PCFGL_REG_ADDRESS, HAL_LL_AD2PCFGL_REG_ADDRESS}, ADC1_RA1, ADC1_RA1_AN1, 0},
    #endif
    #ifdef ADC1_RA2_AN32
    {GPIO_PA2, hal_ll_adc_module_num(ADC_MODULE_1), {HAL_LL_AD1PCFGH_REG_ADDRESS, 0}, ADC1_RA2, ADC1_RA2_AN32, 0},
    #endif
    #ifdef ADC1_RA4_AN24
    {GPIO_PA4, hal_ll_adc_module_num(ADC_MODULE_1), {HAL_LL_AD1PCFGH_REG_ADDRESS, 0}, ADC1_RA4, ADC1_RA4_AN24, 0},
    #endif
    #ifdef ADC1_RA9_AN28
    {GPIO_PA9, hal_ll_adc_module_num(ADC_MODULE_1), {HAL_LL_AD1PCFGH_REG_ADDRESS, 0}, ADC1_RA9, ADC1_RA9_AN28, 0},
    #endif
    #ifdef ADC1_RB0_AN2
    {GPIO_PB0, hal_ll_adc_module_num(ADC_MODULE_1), {HAL_LL_AD1PCFGL_REG_ADDRESS, HAL_LL_AD2PCFGL_REG_ADDRESS}, ADC1_RB0, ADC1_RB0_AN2, 0},
    #endif
    #ifdef ADC1_RB1_AN3
    {GPIO_PB1, hal_ll_adc_module_num(ADC_MODULE_1), {HAL_LL_AD1PCFGL_REG_ADDRESS, HAL_LL_AD2PCFGL_REG_ADDRESS}, ADC1_RB1, ADC1_RB1_AN3, 0},
    #endif
    #ifdef ADC1_RB2_AN4
    {GPIO_PB2, hal_ll_adc_module_num(ADC_MODULE_1), {HAL_LL_AD1PCFGL_REG_ADDRESS, HAL_LL_AD2PCFGL_REG_ADDRESS}, ADC1_RB2, ADC1_RB2_AN4, 0},
    #endif
    #ifdef ADC1_RB3_AN5
    {GPIO_PB3, hal_ll_adc_module_num(ADC_MODULE_1), {HAL_LL_AD1PCFGL_REG_ADDRESS, HAL_LL_AD2PCFGL_REG_ADDRESS}, ADC1_RB3, ADC1_RB3_AN5, 0},
    #endif
    #ifdef ADC1_RB7_AN25
    {GPIO_PB7, hal_ll_adc_module_num(ADC_MODULE_1), {HAL_LL_AD1PCFGH_REG_ADDRESS, 0}, ADC1_RB7, ADC1_RB7_AN25, 0},
    #endif
    #ifdef ADC1_RB8_AN26
    {GPIO_PB8, hal_ll_adc_module_num(ADC_MODULE_1), {HAL_LL_AD1PCFGH_REG_ADDRESS, 0}, ADC1_RB8, ADC1_RB8_AN26, 0},
    #endif
    #ifdef ADC1_RB9_AN27
    {GPIO_PB9, hal_ll_adc_module_num(ADC_MODULE_1), {HAL_LL_AD1PCFGH_REG_ADDRESS, 0}, ADC1_RB9, ADC1_RB9_AN27, 0},
    #endif
    #ifdef ADC1_RC0_AN6
    {GPIO_PC0, hal_ll_adc_module_num(ADC_MODULE_1), {HAL_LL_AD1PCFGL_REG_ADDRESS, HAL_LL_AD2PCFGL_REG_ADDRESS}, ADC1_RC0, ADC1_RC0_AN6, 0},
    #endif
    #ifdef ADC1_RC1_AN7
    {GPIO_PC1, hal_ll_adc_module_num(ADC_MODULE_1), {HAL_LL_AD1PCFGL_REG_ADDRESS, HAL_LL_AD2PCFGL_REG_ADDRESS}, ADC1_RC1, ADC1_RC1_AN7, 0},
    #endif
    #ifdef ADC1_RC2_AN8
    {GPIO_PC2, hal_ll_adc_module_num(ADC_MODULE_1), {HAL_LL_AD1PCFGL_REG_ADDRESS, HAL_LL_AD2PCFGL_REG_ADDRESS}, ADC1_RC2, ADC1_RC2_AN8, 0},
    #endif
    #ifdef ADC1_RC3_AN29
    {GPIO_PC3, hal_ll_adc_module_num(ADC_MODULE_1), {HAL_LL_AD1PCFGH_REG_ADDRESS, 0}, ADC1_RC3, ADC1_RC3_AN29, 0},
    #endif
    #ifdef ADC1_RC4_AN30
    {GPIO_PC4, hal_ll_adc_module_num(ADC_MODULE_1), {HAL_LL_AD1PCFGH_REG_ADDRESS, 0}, ADC1_RC4, ADC1_RC4_AN30, 0},
    #endif
    #ifdef ADC1_RC5_AN31
    {GPIO_PC5, hal_ll_adc_module_num(ADC_MODULE_1), {HAL_LL_AD1PCFGH_REG_ADDRESS, 0}, ADC1_RC5, ADC1_RC5_AN31, 0},
    #endif
    #ifdef ADC2_RA0_AN0
    {GPIO_PA0, hal_ll_adc_module_num(ADC_MODULE_2), {HAL_LL_AD1PCFGL_REG_ADDRESS, HAL_LL_AD2PCFGL_REG_ADDRESS}, ADC2_RA0, ADC2_RA0_AN0, 0},
    #endif
    #ifdef ADC2_RA1_AN1
    {GPIO_PA1, hal_ll_adc_module_num(ADC_MODULE_2), {HAL_LL_AD1PCFGL_REG_ADDRESS, HAL_LL_AD2PCFGL_REG_ADDRESS}, ADC2_RA1, ADC2_RA1_AN1, 0},
    #endif
    #ifdef ADC2_RA4_AN24
    {GPIO_PA4, hal_ll_adc_module_num(ADC_MODULE_2), {HAL_LL_AD1PCFGH_REG_ADDRESS, 0}, ADC2_RA4, ADC2_RA4_AN24, 0},
    #endif
    #ifdef ADC2_RA9_AN28
    {GPIO_PA9, hal_ll_adc_module_num(ADC_MODULE_2), {HAL_LL_AD1PCFGH_REG_ADDRESS, 0}, ADC2_RA9, ADC2_RA9_AN28, 0},
    #endif
    #ifdef ADC2_RB0_AN2
    {GPIO_PB0, hal_ll_adc_module_num(ADC_MODULE_2), {HAL_LL_AD1PCFGL_REG_ADDRESS, HAL_LL_AD2PCFGL_REG_ADDRESS}, ADC2_RB0, ADC2_RB0_AN2, 0},
    #endif
    #ifdef ADC2_RB1_AN3
    {GPIO_PB1, hal_ll_adc_module_num(ADC_MODULE_2), {HAL_LL_AD1PCFGL_REG_ADDRESS, HAL_LL_AD2PCFGL_REG_ADDRESS}, ADC2_RB1, ADC2_RB1_AN3, 0},
    #endif
    #ifdef ADC2_RB2_AN4
    {GPIO_PB2, hal_ll_adc_module_num(ADC_MODULE_2), {HAL_LL_AD1PCFGL_REG_ADDRESS, HAL_LL_AD2PCFGL_REG_ADDRESS}, ADC2_RB2, ADC2_RB2_AN4, 0},
    #endif
    #ifdef ADC2_RB3_AN5
    {GPIO_PB3, hal_ll_adc_module_num(ADC_MODULE_2), {HAL_LL_AD1PCFGL_REG_ADDRESS, HAL_LL_AD2PCFGL_REG_ADDRESS}, ADC2_RB3, ADC2_RB3_AN5, 0},
    #endif
    #ifdef ADC2_RB7_AN25
    {GPIO_PB7, hal_ll_adc_module_num(ADC_MODULE_2), {HAL_LL_AD1PCFGH_REG_ADDRESS, 0}, ADC2_RB7, ADC2_RB7_AN25, 0},
    #endif
    #ifdef ADC2_RB8_AN26
    {GPIO_PB8, hal_ll_adc_module_num(ADC_MODULE_2), {HAL_LL_AD1PCFGH_REG_ADDRESS, 0}, ADC2_RB8, ADC2_RB8_AN26, 0},
    #endif
    #ifdef ADC2_RB9_AN27
    {GPIO_PB9, hal_ll_adc_module_num(ADC_MODULE_2), {HAL_LL_AD1PCFGH_REG_ADDRESS, 0}, ADC2_RB9, ADC2_RB9_AN27, 0},
    #endif
    #ifdef ADC2_RC0_AN6
    {GPIO_PC0, hal_ll_adc_module_num(ADC_MODULE_2), {HAL_LL_AD1PCFGL_REG_ADDRESS, HAL_LL_AD2PCFGL_REG_ADDRESS}, ADC2_RC0, ADC2_RC0_AN6, 0},
    #endif
    #ifdef ADC2_RC1_AN7
    {GPIO_PC1, hal_ll_adc_module_num(ADC_MODULE_2), {HAL_LL_AD1PCFGL_REG_ADDRESS, HAL_LL_AD2PCFGL_REG_ADDRESS}, ADC2_RC1, ADC2_RC1_AN7, 0},
    #endif
    #ifdef ADC2_RC2_AN8
    {GPIO_PC2, hal_ll_adc_module_num(ADC_MODULE_2), {HAL_LL_AD1PCFGL_REG_ADDRESS, HAL_LL_AD2PCFGL_REG_ADDRESS}, ADC2_RC2, ADC2_RC2_AN8, 0},
    #endif
    #ifdef ADC2_RC3_AN29
    {GPIO_PC3, hal_ll_adc_module_num(ADC_MODULE_2), {HAL_LL_AD1PCFGH_REG_ADDRESS, 0}, ADC2_RC3, ADC2_RC3_AN29, 0},
    #endif
    #ifdef ADC2_RC4_AN30
    {GPIO_PC4, hal_ll_adc_module_num(ADC_MODULE_2), {HAL_LL_AD1PCFGH_REG_ADDRESS, 0}, ADC2_RC4, ADC2_RC4_AN30, 0},
    #endif
    #ifdef ADC2_RC5_AN31
    {GPIO_PC5, hal_ll_adc_module_num(ADC_MODULE_2), {HAL_LL_AD1PCFGH_REG_ADDRESS, 0}, ADC2_RC5, ADC2_RC5_AN31, 0},
    #endif
    #ifdef ADC1_RA11_AN9
    {GPIO_PA11, hal_ll_adc_module_num(ADC_MODULE_1), {HAL_LL_AD1PCFGL_REG_ADDRESS, HAL_LL_AD2PCFGL_REG_ADDRESS}, ADC1_RA11, ADC1_RA11_AN9, 0},
    #endif
    #ifdef ADC1_RA12_AN10
    {GPIO_PA12, hal_ll_adc_module_num(ADC_MODULE_1), {HAL_LL_AD1PCFGL_REG_ADDRESS, HAL_LL_AD2PCFGL_REG_ADDRESS}, ADC1_RA12, ADC1_RA12_AN10, 0},
    #endif
    #ifdef ADC1_RC10_AN48
    {GPIO_PC10, hal_ll_adc_module_num(ADC_MODULE_1), {HAL_LL_AD1PCFGH_REG_ADDRESS, 0}, ADC1_RC10, ADC1_RC10_AN48, 0},
    #endif
    #ifdef ADC1_RC11_AN11
    {GPIO_PC11, hal_ll_adc_module_num(ADC_MODULE_1), {HAL_LL_AD1PCFGL_REG_ADDRESS, HAL_LL_AD2PCFGL_REG_ADDRESS}, ADC1_RC11, ADC1_RC11_AN11, 0},
    #endif
    #ifdef ADC1_RC12_AN49
    {GPIO_PC12, hal_ll_adc_module_num(ADC_MODULE_1), {HAL_LL_AD1PCFGH_REG_ADDRESS, 0}, ADC1_RC12, ADC1_RC12_AN49, 0},
    #endif
    #ifdef ADC1_RE12_AN12
    {GPIO_PE12, hal_ll_adc_module_num(ADC_MODULE_1), {HAL_LL_AD1PCFGL_REG_ADDRESS, HAL_LL_AD2PCFGL_REG_ADDRESS}, ADC1_RE12, ADC1_RE12_AN12, 0},
    #endif
    #ifdef ADC1_RE13_AN13
    {GPIO_PE13, hal_ll_adc_module_num(ADC_MODULE_1), {HAL_LL_AD1PCFGL_REG_ADDRESS, HAL_LL_AD2PCFGL_REG_ADDRESS}, ADC1_RE13, ADC1_RE13_AN13, 0},
    #endif
    #ifdef ADC1_RE14_AN14
    {GPIO_PE14, hal_ll_adc_module_num(ADC_MODULE_1), {HAL_LL_AD1PCFGL_REG_ADDRESS, HAL_LL_AD2PCFGL_REG_ADDRESS}, ADC1_RE14, ADC1_RE14_AN14, 0},
    #endif
    #ifdef ADC1_RE15_AN15
    {GPIO_PE15, hal_ll_adc_module_num(ADC_MODULE_1), {HAL_LL_AD1PCFGL_REG_ADDRESS, HAL_LL_AD2PCFGL_REG_ADDRESS}, ADC1_RE15, ADC1_RE15_AN15, 0},
    #endif
    #ifdef ADC1_RG6_AN19
    {GPIO_PG6, hal_ll_adc_module_num(ADC_MODULE_1), {HAL_LL_AD1PCFGH_REG_ADDRESS, 0}, ADC1_RG6, ADC1_RG6_AN19, 0},
    #endif
    #ifdef ADC1_RG7_AN18
    {GPIO_PG7, hal_ll_adc_module_num(ADC_MODULE_1), {HAL_LL_AD1PCFGH_REG_ADDRESS, 0}, ADC1_RG7, ADC1_RG7_AN18, 0},
    #endif
    #ifdef ADC1_RG8_AN17
    {GPIO_PG8, hal_ll_adc_module_num(ADC_MODULE_1), {HAL_LL_AD1PCFGH_REG_ADDRESS, 0}, ADC1_RG8, ADC1_RG8_AN17, 0},
    #endif
    #ifdef ADC1_RG9_AN16
    {GPIO_PG9, hal_ll_adc_module_num(ADC_MODULE_1), {HAL_LL_AD1PCFGH_REG_ADDRESS, 0}, ADC1_RG9, ADC1_RG9_AN16, 0},
    #endif
    #ifdef ADC2_RA11_AN9
    {GPIO_PA11, hal_ll_adc_module_num(ADC_MODULE_2), {HAL_LL_AD1PCFGL_REG_ADDRESS, HAL_LL_AD2PCFGL_REG_ADDRESS}, ADC2_RA11, ADC2_RA11_AN9, 0},
    #endif
    #ifdef ADC2_RA12_AN10
    {GPIO_PA12, hal_ll_adc_module_num(ADC_MODULE_2), {HAL_LL_AD1PCFGL_REG_ADDRESS, HAL_LL_AD2PCFGL_REG_ADDRESS}, ADC2_RA12, ADC2_RA12_AN10, 0},
    #endif
    #ifdef ADC2_RC11_AN11
    {GPIO_PC11, hal_ll_adc_module_num(ADC_MODULE_2), {HAL_LL_AD1PCFGL_REG_ADDRESS, HAL_LL_AD2PCFGL_REG_ADDRESS}, ADC2_RC11, ADC2_RC11_AN11, 0},
    #endif
    #ifdef ADC2_RE12_AN12
    {GPIO_PE12, hal_ll_adc_module_num(ADC_MODULE_2), {HAL_LL_AD1PCFGL_REG_ADDRESS, HAL_LL_AD2PCFGL_REG_ADDRESS}, ADC2_RE12, ADC2_RE12_AN12, 0},
    #endif
    #ifdef ADC2_RE13_AN13
    {GPIO_PE13, hal_ll_adc_module_num(ADC_MODULE_2), {HAL_LL_AD1PCFGL_REG_ADDRESS, HAL_LL_AD2PCFGL_REG_ADDRESS}, ADC2_RE13, ADC2_RE13_AN13, 0},
    #endif
    #ifdef ADC2_RE14_AN14
    {GPIO_PE14, hal_ll_adc_module_num(ADC_MODULE_2), {HAL_LL_AD1PCFGL_REG_ADDRESS, HAL_LL_AD2PCFGL_REG_ADDRESS}, ADC2_RE14, ADC2_RE14_AN14, 0},
    #endif
    #ifdef ADC2_RE15_AN15
    {GPIO_PE15, hal_ll_adc_module_num(ADC_MODULE_2), {HAL_LL_AD1PCFGL_REG_ADDRESS, HAL_LL_AD2PCFGL_REG_ADDRESS}, ADC2_RE15, ADC2_RE15_AN15, 0},
    #endif
    #ifdef ADC2_RG6_AN19
    {GPIO_PG6, hal_ll_adc_module_num(ADC_MODULE_2), {HAL_LL_AD1PCFGH_REG_ADDRESS, 0}, ADC2_RG6, ADC2_RG6_AN19, 0},
    #endif
    #ifdef ADC2_RG7_AN18
    {GPIO_PG7, hal_ll_adc_module_num(ADC_MODULE_2), {HAL_LL_AD1PCFGH_REG_ADDRESS, 0}, ADC2_RG7, ADC2_RG7_AN18, 0},
    #endif
    #ifdef ADC2_RG8_AN17
    {GPIO_PG8, hal_ll_adc_module_num(ADC_MODULE_2), {HAL_LL_AD1PCFGH_REG_ADDRESS, 0}, ADC2_RG8, ADC2_RG8_AN17, 0},
    #endif
    #ifdef ADC2_RG9_AN16
    {GPIO_PG9, hal_ll_adc_module_num(ADC_MODULE_2), {HAL_LL_AD1PCFGH_REG_ADDRESS, 0}, ADC2_RG9, ADC2_RG9_AN16, 0},
    #endif
    #ifdef ADC1_RA14_AN46
    {GPIO_PA14, hal_ll_adc_module_num(ADC_MODULE_1), {HAL_LL_AD1PCFGH_REG_ADDRESS, 0}, ADC1_RA14, ADC1_RA14_AN46, 0},
    #endif
    #ifdef ADC1_RA15_AN47
    {GPIO_PA15, hal_ll_adc_module_num(ADC_MODULE_1), {HAL_LL_AD1PCFGH_REG_ADDRESS, 0}, ADC1_RA15, ADC1_RA15_AN47, 0},
    #endif
    #ifdef ADC1_RD14_AN38
    {GPIO_PD14, hal_ll_adc_module_num(ADC_MODULE_1), {HAL_LL_AD1PCFGH_REG_ADDRESS, 0}, ADC1_RD14, ADC1_RD14_AN38, 0},
    #endif
    #ifdef ADC1_RD15_AN39
    {GPIO_PD15, hal_ll_adc_module_num(ADC_MODULE_1), {HAL_LL_AD1PCFGH_REG_ADDRESS, 0}, ADC1_RD15, ADC1_RD15_AN39, 0},
    #endif
    #ifdef ADC1_RE0_AN40
    {GPIO_PE0, hal_ll_adc_module_num(ADC_MODULE_1), {HAL_LL_AD1PCFGH_REG_ADDRESS, 0}, ADC1_RE0, ADC1_RE0_AN40, 0},
    #endif
    #ifdef ADC1_RE1_AN41
    {GPIO_PE1, hal_ll_adc_module_num(ADC_MODULE_1), {HAL_LL_AD1PCFGH_REG_ADDRESS, 0}, ADC1_RE1, ADC1_RE1_AN41, 0},
    #endif
    #ifdef ADC1_RE8_AN21
    {GPIO_PE8, hal_ll_adc_module_num(ADC_MODULE_1), {HAL_LL_AD1PCFGH_REG_ADDRESS, 0}, ADC1_RE8, ADC1_RE8_AN21, 0},
    #endif
    #ifdef ADC1_RE9_AN20
    {GPIO_PE9, hal_ll_adc_module_num(ADC_MODULE_1), {HAL_LL_AD1PCFGH_REG_ADDRESS, 0}, ADC1_RE9, ADC1_RE9_AN20, 0},
    #endif
    #ifdef ADC1_RF10_AN34
    {GPIO_PF10, hal_ll_adc_module_num(ADC_MODULE_1), {HAL_LL_AD1PCFGH_REG_ADDRESS, 0}, ADC1_RF10, ADC1_RF10_AN34, 0},
    #endif
    #ifdef ADC1_RF12_AN37
    {GPIO_PF12, hal_ll_adc_module_num(ADC_MODULE_1), {HAL_LL_AD1PCFGH_REG_ADDRESS, 0}, ADC1_RF12, ADC1_RF12_AN37, 0},
    #endif
    #ifdef ADC1_RF13_AN36
    {GPIO_PF13, hal_ll_adc_module_num(ADC_MODULE_1), {HAL_LL_AD1PCFGH_REG_ADDRESS, 0}, ADC1_RF13, ADC1_RF13_AN36, 0},
    #endif
    #ifdef ADC1_RF4_AN44
    {GPIO_PF4, hal_ll_adc_module_num(ADC_MODULE_1), {HAL_LL_AD1PCFGH_REG_ADDRESS, 0}, ADC1_RF4, ADC1_RF4_AN44, 0},
    #endif
    #ifdef ADC1_RF5_AN45
    {GPIO_PF5, hal_ll_adc_module_num(ADC_MODULE_1), {HAL_LL_AD1PCFGH_REG_ADDRESS, 0}, ADC1_RF5, ADC1_RF5_AN45, 0},
    #endif
    #ifdef ADC1_RF9_AN33
    {GPIO_PF9, hal_ll_adc_module_num(ADC_MODULE_1), {HAL_LL_AD1PCFGH_REG_ADDRESS, 0}, ADC1_RF9, ADC1_RF9_AN33, 0},
    #endif
    #ifdef ADC1_RG10_AN22
    {GPIO_PG10, hal_ll_adc_module_num(ADC_MODULE_1), {HAL_LL_AD1PCFGH_REG_ADDRESS, 0}, ADC1_RG10, ADC1_RG10_AN22, 0},
    #endif
    #ifdef ADC1_RG11_AN35
    {GPIO_PG11, hal_ll_adc_module_num(ADC_MODULE_1), {HAL_LL_AD1PCFGH_REG_ADDRESS, 0}, ADC1_RG11, ADC1_RG11_AN35, 0},
    #endif
    #ifdef ADC1_RG15_AN23
    {GPIO_PG15, hal_ll_adc_module_num(ADC_MODULE_1), {HAL_LL_AD1PCFGH_REG_ADDRESS, 0}, ADC1_RG15, ADC1_RG15_AN23, 0},
    #endif
    #ifdef ADC1_RG2_AN42
    {GPIO_PG2, hal_ll_adc_module_num(ADC_MODULE_1), {HAL_LL_AD1PCFGH_REG_ADDRESS, 0}, ADC1_RG2, ADC1_RG2_AN42, 0},
    #endif
    #ifdef ADC1_RG3_AN43
    {GPIO_PG3, hal_ll_adc_module_num(ADC_MODULE_1), {HAL_LL_AD1PCFGH_REG_ADDRESS, 0}, ADC1_RG3, ADC1_RG3_AN43, 0},
    #endif
    #ifdef ADC2_RE8_AN21
    {GPIO_PE8, hal_ll_adc_module_num(ADC_MODULE_2), {HAL_LL_AD1PCFGH_REG_ADDRESS, 0}, ADC2_RE8, ADC2_RE8_AN21, 0},
    #endif
    #ifdef ADC2_RE9_AN20
    {GPIO_PE9, hal_ll_adc_module_num(ADC_MODULE_2), {HAL_LL_AD1PCFGH_REG_ADDRESS, 0}, ADC2_RE9, ADC2_RE9_AN20, 0},
    #endif
    #ifdef ADC2_RG10_AN22
    {GPIO_PG10, hal_ll_adc_module_num(ADC_MODULE_2), {HAL_LL_AD1PCFGH_REG_ADDRESS, 0}, ADC2_RG10, ADC2_RG10_AN22, 0},
    #endif
    #ifdef ADC2_RG15_AN23
    {GPIO_PG15, hal_ll_adc_module_num(ADC_MODULE_2), {HAL_LL_AD1PCFGH_REG_ADDRESS, 0}, ADC2_RG15, ADC2_RG15_AN23, 0},
    #endif
    #ifdef ADC1_RA2_AN2
    {GPIO_PA2, hal_ll_adc_module_num(ADC_MODULE_1), {HAL_LL_AD1PCFGL_REG_ADDRESS, HAL_LL_AD2PCFGL_REG_ADDRESS}, ADC1_RA2, ADC1_RA2_AN2, 0},
    #endif
    #ifdef ADC1_RB0_AN3
    {GPIO_PB0, hal_ll_adc_module_num(ADC_MODULE_1), {HAL_LL_AD1PCFGL_REG_ADDRESS, HAL_LL_AD2PCFGL_REG_ADDRESS}, ADC1_RB0, ADC1_RB0_AN3, 0},
    #endif
    #ifdef ADC1_RB1_AN6
    {GPIO_PB1, hal_ll_adc_module_num(ADC_MODULE_1), {HAL_LL_AD1PCFGL_REG_ADDRESS, HAL_LL_AD2PCFGL_REG_ADDRESS}, ADC1_RB1, ADC1_RB1_AN6, 0},
    #endif
    #ifdef ADC1_RB2_AN7
    {GPIO_PB2, hal_ll_adc_module_num(ADC_MODULE_1), {HAL_LL_AD1PCFGL_REG_ADDRESS, HAL_LL_AD2PCFGL_REG_ADDRESS}, ADC1_RB2, ADC1_RB2_AN7, 0},
    #endif
    #ifdef ADC1_RB3_AN18
    {GPIO_PB3, hal_ll_adc_module_num(ADC_MODULE_1), {HAL_LL_AD1PCFGH_REG_ADDRESS, 0}, ADC1_RB3, ADC1_RB3_AN18, 0},
    #endif
    #ifdef ADC1_RB5_AN19
    {GPIO_PB5, hal_ll_adc_module_num(ADC_MODULE_1), {HAL_LL_AD1PCFGH_REG_ADDRESS, 0}, ADC1_RB5, ADC1_RB5_AN19, 0},
    #endif
    #ifdef ADC1_RB6_AN20
    {GPIO_PB6, hal_ll_adc_module_num(ADC_MODULE_1), {HAL_LL_AD1PCFGH_REG_ADDRESS, 0}, ADC1_RB6, ADC1_RB6_AN20, 0},
    #endif
    #ifdef ADC1_RB7_AN21
    {GPIO_PB7, hal_ll_adc_module_num(ADC_MODULE_1), {HAL_LL_AD1PCFGH_REG_ADDRESS, 0}, ADC1_RB7, ADC1_RB7_AN21, 0},
    #endif
    #ifdef ADC1_RB9_AN4
    {GPIO_PB9, hal_ll_adc_module_num(ADC_MODULE_1), {HAL_LL_AD1PCFGL_REG_ADDRESS, HAL_LL_AD2PCFGL_REG_ADDRESS}, ADC1_RB9, ADC1_RB9_AN4, 0},
    #endif
    #ifdef ADC1_RC1_AN8
    {GPIO_PC1, hal_ll_adc_module_num(ADC_MODULE_1), {HAL_LL_AD1PCFGL_REG_ADDRESS, HAL_LL_AD2PCFGL_REG_ADDRESS}, ADC1_RC1, ADC1_RC1_AN8, 0},
    #endif
    #ifdef ADC1_RC10_AN10
    {GPIO_PC10, hal_ll_adc_module_num(ADC_MODULE_1), {HAL_LL_AD1PCFGL_REG_ADDRESS, HAL_LL_AD2PCFGL_REG_ADDRESS}, ADC1_RC10, ADC1_RC10_AN10, 0},
    #endif
    #ifdef ADC1_RC12_AN14
    {GPIO_PC12, hal_ll_adc_module_num(ADC_MODULE_1), {HAL_LL_AD1PCFGL_REG_ADDRESS, HAL_LL_AD2PCFGL_REG_ADDRESS}, ADC1_RC12, ADC1_RC12_AN14, 0},
    #endif
    #ifdef ADC1_RC2_AN9
    {GPIO_PC2, hal_ll_adc_module_num(ADC_MODULE_1), {HAL_LL_AD1PCFGL_REG_ADDRESS, HAL_LL_AD2PCFGL_REG_ADDRESS}, ADC1_RC2, ADC1_RC2_AN9, 0},
    #endif
    #ifdef ADC1_RC6_AN17
    {GPIO_PC6, hal_ll_adc_module_num(ADC_MODULE_1), {HAL_LL_AD1PCFGH_REG_ADDRESS, 0}, ADC1_RC6, ADC1_RC6_AN17, 0},
    #endif
    #ifdef ADC1_RC9_AN11
    {GPIO_PC9, hal_ll_adc_module_num(ADC_MODULE_1), {HAL_LL_AD1PCFGL_REG_ADDRESS, HAL_LL_AD2PCFGL_REG_ADDRESS}, ADC1_RC9, ADC1_RC9_AN11, 0},
    #endif
    #ifdef ADC1_RD13_AN13
    {GPIO_PD13, hal_ll_adc_module_num(ADC_MODULE_1), {HAL_LL_AD1PCFGL_REG_ADDRESS, HAL_LL_AD2PCFGL_REG_ADDRESS}, ADC1_RD13, ADC1_RD13_AN13, 0},
    #endif
    #ifdef ADC1_RD2_AN16
    {GPIO_PD2, hal_ll_adc_module_num(ADC_MODULE_1), {HAL_LL_AD1PCFGH_REG_ADDRESS, 0}, ADC1_RD2, ADC1_RD2_AN16, 0},
    #endif
    #ifdef ADC1_RD5_AN12
    {GPIO_PD5, hal_ll_adc_module_num(ADC_MODULE_1), {HAL_LL_AD1PCFGL_REG_ADDRESS, HAL_LL_AD2PCFGL_REG_ADDRESS}, ADC1_RD5, ADC1_RD5_AN12, 0},
    #endif
    #ifdef ADC1_RD7_AN15
    {GPIO_PD7, hal_ll_adc_module_num(ADC_MODULE_1), {HAL_LL_AD1PCFGL_REG_ADDRESS, HAL_LL_AD2PCFGL_REG_ADDRESS}, ADC1_RD7, ADC1_RD7_AN15, 0},
    #endif
    #ifdef ADC1_RD8_AN5
    {GPIO_PD8, hal_ll_adc_module_num(ADC_MODULE_1), {HAL_LL_AD1PCFGL_REG_ADDRESS, HAL_LL_AD2PCFGL_REG_ADDRESS}, ADC1_RD8, ADC1_RD8_AN5, 0},
    #endif
    #ifdef ADC1_RB10_AN5
    {GPIO_PB10, hal_ll_adc_module_num(ADC_MODULE_1), {HAL_LL_AD1PCFGL_REG_ADDRESS, HAL_LL_AD2PCFGL_REG_ADDRESS}, ADC1_RB10, ADC1_RB10_AN5, 0},
    #endif
    #ifdef ADC1_RB3_AN8
    {GPIO_PB3, hal_ll_adc_module_num(ADC_MODULE_1), {HAL_LL_AD1PCFGL_REG_ADDRESS, HAL_LL_AD2PCFGL_REG_ADDRESS}, ADC1_RB3, ADC1_RB3_AN8, 0},
    #endif
    #ifdef ADC1_RB5_AN9
    {GPIO_PB5, hal_ll_adc_module_num(ADC_MODULE_1), {HAL_LL_AD1PCFGL_REG_ADDRESS, HAL_LL_AD2PCFGL_REG_ADDRESS}, ADC1_RB5, ADC1_RB5_AN9, 0},
    #endif
    #ifdef ADC1_RB6_AN10
    {GPIO_PB6, hal_ll_adc_module_num(ADC_MODULE_1), {HAL_LL_AD1PCFGL_REG_ADDRESS, HAL_LL_AD2PCFGL_REG_ADDRESS}, ADC1_RB6, ADC1_RB6_AN10, 0},
    #endif
    #ifdef ADC1_RB7_AN11
    {GPIO_PB7, hal_ll_adc_module_num(ADC_MODULE_1), {HAL_LL_AD1PCFGL_REG_ADDRESS, HAL_LL_AD2PCFGL_REG_ADDRESS}, ADC1_RB7, ADC1_RB7_AN11, 0},
    #endif
    #ifdef ADC1_RC11_AN12
    {GPIO_PC11, hal_ll_adc_module_num(ADC_MODULE_1), {HAL_LL_AD1PCFGL_REG_ADDRESS, HAL_LL_AD2PCFGL_REG_ADDRESS}, ADC1_RC11, ADC1_RC11_AN12, 0},
    #endif
    #ifdef ADC1_RB0_AN0
    {GPIO_PB0, hal_ll_adc_module_num(ADC_MODULE_1), {HAL_LL_AD1PCFGL_REG_ADDRESS, HAL_LL_AD2PCFGL_REG_ADDRESS}, ADC1_RB0, ADC1_RB0_AN0, 0},
    #endif
    #ifdef ADC1_RB1_AN1
    {GPIO_PB1, hal_ll_adc_module_num(ADC_MODULE_1), {HAL_LL_AD1PCFGL_REG_ADDRESS, HAL_LL_AD2PCFGL_REG_ADDRESS}, ADC1_RB1, ADC1_RB1_AN1, 0},
    #endif
    #ifdef ADC1_RB10_AN10
    {GPIO_PB10, hal_ll_adc_module_num(ADC_MODULE_1), {HAL_LL_AD1PCFGL_REG_ADDRESS, HAL_LL_AD2PCFGL_REG_ADDRESS}, ADC1_RB10, ADC1_RB10_AN10, 0},
    #endif
    #ifdef ADC1_RB11_AN11
    {GPIO_PB11, hal_ll_adc_module_num(ADC_MODULE_1), {HAL_LL_AD1PCFGL_REG_ADDRESS, HAL_LL_AD2PCFGL_REG_ADDRESS}, ADC1_RB11, ADC1_RB11_AN11, 0},
    #endif
    #ifdef ADC1_RB12_AN12
    {GPIO_PB12, hal_ll_adc_module_num(ADC_MODULE_1), {HAL_LL_AD1PCFGL_REG_ADDRESS, HAL_LL_AD2PCFGL_REG_ADDRESS}, ADC1_RB12, ADC1_RB12_AN12, 0},
    #endif
    #ifdef ADC1_RB13_AN13
    {GPIO_PB13, hal_ll_adc_module_num(ADC_MODULE_1), {HAL_LL_AD1PCFGL_REG_ADDRESS, HAL_LL_AD2PCFGL_REG_ADDRESS}, ADC1_RB13, ADC1_RB13_AN13, 0},
    #endif
    #ifdef ADC1_RB14_AN14
    {GPIO_PB14, hal_ll_adc_module_num(ADC_MODULE_1), {HAL_LL_AD1PCFGL_REG_ADDRESS, HAL_LL_AD2PCFGL_REG_ADDRESS}, ADC1_RB14, ADC1_RB14_AN14, 0},
    #endif
    #ifdef ADC1_RB15_AN15
    {GPIO_PB15, hal_ll_adc_module_num(ADC_MODULE_1), {HAL_LL_AD1PCFGL_REG_ADDRESS, HAL_LL_AD2PCFGL_REG_ADDRESS}, ADC1_RB15, ADC1_RB15_AN15, 0},
    #endif
    #ifdef ADC1_RB2_AN2
    {GPIO_PB2, hal_ll_adc_module_num(ADC_MODULE_1), {HAL_LL_AD1PCFGL_REG_ADDRESS, HAL_LL_AD2PCFGL_REG_ADDRESS}, ADC1_RB2, ADC1_RB2_AN2, 0},
    #endif
    #ifdef ADC1_RB3_AN3
    {GPIO_PB3, hal_ll_adc_module_num(ADC_MODULE_1), {HAL_LL_AD1PCFGL_REG_ADDRESS, HAL_LL_AD2PCFGL_REG_ADDRESS}, ADC1_RB3, ADC1_RB3_AN3, 0},
    #endif
    #ifdef ADC1_RB4_AN4
    {GPIO_PB4, hal_ll_adc_module_num(ADC_MODULE_1), {HAL_LL_AD1PCFGL_REG_ADDRESS, HAL_LL_AD2PCFGL_REG_ADDRESS}, ADC1_RB4, ADC1_RB4_AN4, 0},
    #endif
    #ifdef ADC1_RB5_AN5
    {GPIO_PB5, hal_ll_adc_module_num(ADC_MODULE_1), {HAL_LL_AD1PCFGL_REG_ADDRESS, HAL_LL_AD2PCFGL_REG_ADDRESS}, ADC1_RB5, ADC1_RB5_AN5, 0},
    #endif
    #ifdef ADC1_RB6_AN6
    {GPIO_PB6, hal_ll_adc_module_num(ADC_MODULE_1), {HAL_LL_AD1PCFGL_REG_ADDRESS, HAL_LL_AD2PCFGL_REG_ADDRESS}, ADC1_RB6, ADC1_RB6_AN6, 0},
    #endif
    #ifdef ADC1_RB7_AN7
    {GPIO_PB7, hal_ll_adc_module_num(ADC_MODULE_1), {HAL_LL_AD1PCFGL_REG_ADDRESS, HAL_LL_AD2PCFGL_REG_ADDRESS}, ADC1_RB7, ADC1_RB7_AN7, 0},
    #endif
    #ifdef ADC1_RB8_AN8
    {GPIO_PB8, hal_ll_adc_module_num(ADC_MODULE_1), {HAL_LL_AD1PCFGL_REG_ADDRESS, HAL_LL_AD2PCFGL_REG_ADDRESS}, ADC1_RB8, ADC1_RB8_AN8, 0},
    #endif
    #ifdef ADC1_RB9_AN9
    {GPIO_PB9, hal_ll_adc_module_num(ADC_MODULE_1), {HAL_LL_AD1PCFGL_REG_ADDRESS, HAL_LL_AD2PCFGL_REG_ADDRESS}, ADC1_RB9, ADC1_RB9_AN9, 0},
    #endif
    #ifdef ADC1_RE0_AN24
    {GPIO_PE0, hal_ll_adc_module_num(ADC_MODULE_1), {HAL_LL_AD1PCFGH_REG_ADDRESS, 0}, ADC1_RE0, ADC1_RE0_AN24, 0},
    #endif
    #ifdef ADC1_RE1_AN25
    {GPIO_PE1, hal_ll_adc_module_num(ADC_MODULE_1), {HAL_LL_AD1PCFGH_REG_ADDRESS, 0}, ADC1_RE1, ADC1_RE1_AN25, 0},
    #endif
    #ifdef ADC1_RE2_AN26
    {GPIO_PE2, hal_ll_adc_module_num(ADC_MODULE_1), {HAL_LL_AD1PCFGH_REG_ADDRESS, 0}, ADC1_RE2, ADC1_RE2_AN26, 0},
    #endif
    #ifdef ADC1_RE3_AN27
    {GPIO_PE3, hal_ll_adc_module_num(ADC_MODULE_1), {HAL_LL_AD1PCFGH_REG_ADDRESS, 0}, ADC1_RE3, ADC1_RE3_AN27, 0},
    #endif
    #ifdef ADC1_RE4_AN28
    {GPIO_PE4, hal_ll_adc_module_num(ADC_MODULE_1), {HAL_LL_AD1PCFGH_REG_ADDRESS, 0}, ADC1_RE4, ADC1_RE4_AN28, 0},
    #endif
    #ifdef ADC1_RE5_AN29
    {GPIO_PE5, hal_ll_adc_module_num(ADC_MODULE_1), {HAL_LL_AD1PCFGH_REG_ADDRESS, 0}, ADC1_RE5, ADC1_RE5_AN29, 0},
    #endif
    #ifdef ADC1_RE6_AN30
    {GPIO_PE6, hal_ll_adc_module_num(ADC_MODULE_1), {HAL_LL_AD1PCFGH_REG_ADDRESS, 0}, ADC1_RE6, ADC1_RE6_AN30, 0},
    #endif
    #ifdef ADC1_RE7_AN31
    {GPIO_PE7, hal_ll_adc_module_num(ADC_MODULE_1), {HAL_LL_AD1PCFGH_REG_ADDRESS, 0}, ADC1_RE7, ADC1_RE7_AN31, 0},
    #endif
    #ifdef ADC2_RB0_AN0
    {GPIO_PB0, hal_ll_adc_module_num(ADC_MODULE_2), {HAL_LL_AD1PCFGL_REG_ADDRESS, HAL_LL_AD2PCFGL_REG_ADDRESS}, ADC2_RB0, ADC2_RB0_AN0, 0},
    #endif
    #ifdef ADC2_RB1_AN1
    {GPIO_PB1, hal_ll_adc_module_num(ADC_MODULE_2), {HAL_LL_AD1PCFGL_REG_ADDRESS, HAL_LL_AD2PCFGL_REG_ADDRESS}, ADC2_RB1, ADC2_RB1_AN1, 0},
    #endif
    #ifdef ADC2_RB10_AN10
    {GPIO_PB10, hal_ll_adc_module_num(ADC_MODULE_2), {HAL_LL_AD1PCFGL_REG_ADDRESS, HAL_LL_AD2PCFGL_REG_ADDRESS}, ADC2_RB10, ADC2_RB10_AN10, 0},
    #endif
    #ifdef ADC2_RB11_AN11
    {GPIO_PB11, hal_ll_adc_module_num(ADC_MODULE_2), {HAL_LL_AD1PCFGL_REG_ADDRESS, HAL_LL_AD2PCFGL_REG_ADDRESS}, ADC2_RB11, ADC2_RB11_AN11, 0},
    #endif
    #ifdef ADC2_RB12_AN12
    {GPIO_PB12, hal_ll_adc_module_num(ADC_MODULE_2), {HAL_LL_AD1PCFGL_REG_ADDRESS, HAL_LL_AD2PCFGL_REG_ADDRESS}, ADC2_RB12, ADC2_RB12_AN12, 0},
    #endif
    #ifdef ADC2_RB13_AN13
    {GPIO_PB13, hal_ll_adc_module_num(ADC_MODULE_2), {HAL_LL_AD1PCFGL_REG_ADDRESS, HAL_LL_AD2PCFGL_REG_ADDRESS}, ADC2_RB13, ADC2_RB13_AN13, 0},
    #endif
    #ifdef ADC2_RB14_AN14
    {GPIO_PB14, hal_ll_adc_module_num(ADC_MODULE_2), {HAL_LL_AD1PCFGL_REG_ADDRESS, HAL_LL_AD2PCFGL_REG_ADDRESS}, ADC2_RB14, ADC2_RB14_AN14, 0},
    #endif
    #ifdef ADC2_RB15_AN15
    {GPIO_PB15, hal_ll_adc_module_num(ADC_MODULE_2), {HAL_LL_AD1PCFGL_REG_ADDRESS, HAL_LL_AD2PCFGL_REG_ADDRESS}, ADC2_RB15, ADC2_RB15_AN15, 0},
    #endif
    #ifdef ADC2_RB2_AN2
    {GPIO_PB2, hal_ll_adc_module_num(ADC_MODULE_2), {HAL_LL_AD1PCFGL_REG_ADDRESS, HAL_LL_AD2PCFGL_REG_ADDRESS}, ADC2_RB2, ADC2_RB2_AN2, 0},
    #endif
    #ifdef ADC2_RB3_AN3
    {GPIO_PB3, hal_ll_adc_module_num(ADC_MODULE_2), {HAL_LL_AD1PCFGL_REG_ADDRESS, HAL_LL_AD2PCFGL_REG_ADDRESS}, ADC2_RB3, ADC2_RB3_AN3, 0},
    #endif
    #ifdef ADC2_RB4_AN4
    {GPIO_PB4, hal_ll_adc_module_num(ADC_MODULE_2), {HAL_LL_AD1PCFGL_REG_ADDRESS, HAL_LL_AD2PCFGL_REG_ADDRESS}, ADC2_RB4, ADC2_RB4_AN4, 0},
    #endif
    #ifdef ADC2_RB5_AN5
    {GPIO_PB5, hal_ll_adc_module_num(ADC_MODULE_2), {HAL_LL_AD1PCFGL_REG_ADDRESS, HAL_LL_AD2PCFGL_REG_ADDRESS}, ADC2_RB5, ADC2_RB5_AN5, 0},
    #endif
    #ifdef ADC2_RB6_AN6
    {GPIO_PB6, hal_ll_adc_module_num(ADC_MODULE_2), {HAL_LL_AD1PCFGL_REG_ADDRESS, HAL_LL_AD2PCFGL_REG_ADDRESS}, ADC2_RB6, ADC2_RB6_AN6, 0},
    #endif
    #ifdef ADC2_RB7_AN7
    {GPIO_PB7, hal_ll_adc_module_num(ADC_MODULE_2), {HAL_LL_AD1PCFGL_REG_ADDRESS, HAL_LL_AD2PCFGL_REG_ADDRESS}, ADC2_RB7, ADC2_RB7_AN7, 0},
    #endif
    #ifdef ADC2_RB8_AN8
    {GPIO_PB8, hal_ll_adc_module_num(ADC_MODULE_2), {HAL_LL_AD1PCFGL_REG_ADDRESS, HAL_LL_AD2PCFGL_REG_ADDRESS}, ADC2_RB8, ADC2_RB8_AN8, 0},
    #endif
    #ifdef ADC2_RB9_AN9
    {GPIO_PB9, hal_ll_adc_module_num(ADC_MODULE_2), {HAL_LL_AD1PCFGL_REG_ADDRESS, HAL_LL_AD2PCFGL_REG_ADDRESS}, ADC2_RB9, ADC2_RB9_AN9, 0},
    #endif
    #ifdef ADC1_RA6_AN22
    {GPIO_PA6, hal_ll_adc_module_num(ADC_MODULE_1), {HAL_LL_AD1PCFGH_REG_ADDRESS, 0}, ADC1_RA6, ADC1_RA6_AN22, 0},
    #endif
    #ifdef ADC1_RA7_AN23
    {GPIO_PA7, hal_ll_adc_module_num(ADC_MODULE_1), {HAL_LL_AD1PCFGH_REG_ADDRESS, 0}, ADC1_RA7, ADC1_RA7_AN23, 0},
    #endif
    #ifdef ADC1_RC1_AN16
    {GPIO_PC1, hal_ll_adc_module_num(ADC_MODULE_1), {HAL_LL_AD1PCFGH_REG_ADDRESS, 0}, ADC1_RC1, ADC1_RC1_AN16, 0},
    #endif
    #ifdef ADC1_RC2_AN17
    {GPIO_PC2, hal_ll_adc_module_num(ADC_MODULE_1), {HAL_LL_AD1PCFGH_REG_ADDRESS, 0}, ADC1_RC2, ADC1_RC2_AN17, 0},
    #endif
    #ifdef ADC1_RC3_AN18
    {GPIO_PC3, hal_ll_adc_module_num(ADC_MODULE_1), {HAL_LL_AD1PCFGH_REG_ADDRESS, 0}, ADC1_RC3, ADC1_RC3_AN18, 0},
    #endif
    #ifdef ADC1_RC4_AN19
    {GPIO_PC4, hal_ll_adc_module_num(ADC_MODULE_1), {HAL_LL_AD1PCFGH_REG_ADDRESS, 0}, ADC1_RC4, ADC1_RC4_AN19, 0},
    #endif
    #ifdef ADC1_RE8_AN20
    {GPIO_PE8, hal_ll_adc_module_num(ADC_MODULE_1), {HAL_LL_AD1PCFGH_REG_ADDRESS, 0}, ADC1_RE8, ADC1_RE8_AN20, 0},
    #endif
    #ifdef ADC1_RE9_AN21
    {GPIO_PE9, hal_ll_adc_module_num(ADC_MODULE_1), {HAL_LL_AD1PCFGH_REG_ADDRESS, 0}, ADC1_RE9, ADC1_RE9_AN21, 0},
    #endif
    #ifdef ADC1_RA10_AN56
    {GPIO_PA10, hal_ll_adc_module_num(ADC_MODULE_1), {HAL_LL_AD1PCFGH_REG_ADDRESS, 0}, ADC1_RA10, ADC1_RA10_AN56, 0},
    #endif
    #ifdef ADC1_RA7_AN55
    {GPIO_PA7, hal_ll_adc_module_num(ADC_MODULE_1), {HAL_LL_AD1PCFGH_REG_ADDRESS, 0}, ADC1_RA7, ADC1_RA7_AN55, 0},
    #endif
    #ifdef ADC1_RC6_AN53
    {GPIO_PC6, hal_ll_adc_module_num(ADC_MODULE_1), {HAL_LL_AD1PCFGH_REG_ADDRESS, 0}, ADC1_RC6, ADC1_RC6_AN53, 0},
    #endif
    #ifdef ADC1_RC7_AN52
    {GPIO_PC7, hal_ll_adc_module_num(ADC_MODULE_1), {HAL_LL_AD1PCFGH_REG_ADDRESS, 0}, ADC1_RC7, ADC1_RC7_AN52, 0},
    #endif
    #ifdef ADC1_RC8_AN51
    {GPIO_PC8, hal_ll_adc_module_num(ADC_MODULE_1), {HAL_LL_AD1PCFGH_REG_ADDRESS, 0}, ADC1_RC8, ADC1_RC8_AN51, 0},
    #endif
    #ifdef ADC1_RC9_AN54
    {GPIO_PC9, hal_ll_adc_module_num(ADC_MODULE_1), {HAL_LL_AD1PCFGH_REG_ADDRESS, 0}, ADC1_RC9, ADC1_RC9_AN54, 0},
    #endif
    #ifdef ADC_RA0_AN0
    {GPIO_PA0, hal_ll_adc_module_num(ADC_MODULE), {HAL_LL_AD1PCFGL_REG_ADDRESS, HAL_LL_AD2PCFGL_REG_ADDRESS}, ADC_RA0, ADC_RA0_AN0, 0},
    #endif
    #ifdef ADC_RA1_AN1
    {GPIO_PA1, hal_ll_adc_module_num(ADC_MODULE), {HAL_LL_AD1PCFGL_REG_ADDRESS, HAL_LL_AD2PCFGL_REG_ADDRESS}, ADC_RA1, ADC_RA1_AN1, 0},
    #endif
    #ifdef ADC_RB0_AN2
    {GPIO_PB0, hal_ll_adc_module_num(ADC_MODULE), {HAL_LL_AD1PCFGL_REG_ADDRESS, HAL_LL_AD2PCFGL_REG_ADDRESS}, ADC_RB0, ADC_RB0_AN2, 0},
    #endif
    #ifdef ADC_RB1_AN3
    {GPIO_PB1, hal_ll_adc_module_num(ADC_MODULE), {HAL_LL_AD1PCFGL_REG_ADDRESS, HAL_LL_AD2PCFGL_REG_ADDRESS}, ADC_RB1, ADC_RB1_AN3, 0},
    #endif
    #ifdef ADC_RB13_AN11
    {GPIO_PB13, hal_ll_adc_module_num(ADC_MODULE), {HAL_LL_AD1PCFGL_REG_ADDRESS, HAL_LL_AD2PCFGL_REG_ADDRESS}, ADC_RB13, ADC_RB13_AN11, 0},
    #endif
    #ifdef ADC_RB14_AN10
    {GPIO_PB14, hal_ll_adc_module_num(ADC_MODULE), {HAL_LL_AD1PCFGL_REG_ADDRESS, HAL_LL_AD2PCFGL_REG_ADDRESS}, ADC_RB14, ADC_RB14_AN10, 0},
    #endif
    #ifdef ADC_RB15_AN9
    {GPIO_PB15, hal_ll_adc_module_num(ADC_MODULE), {HAL_LL_AD1PCFGL_REG_ADDRESS, HAL_LL_AD2PCFGL_REG_ADDRESS}, ADC_RB15, ADC_RB15_AN9, 0},
    #endif
    #ifdef ADC_RB2_AN4
    {GPIO_PB2, hal_ll_adc_module_num(ADC_MODULE), {HAL_LL_AD1PCFGL_REG_ADDRESS, HAL_LL_AD2PCFGL_REG_ADDRESS}, ADC_RB2, ADC_RB2_AN4, 0},
    #endif
    #ifdef ADC_RB3_AN5
    {GPIO_PB3, hal_ll_adc_module_num(ADC_MODULE), {HAL_LL_AD1PCFGL_REG_ADDRESS, HAL_LL_AD2PCFGL_REG_ADDRESS}, ADC_RB3, ADC_RB3_AN5, 0},
    #endif
    #ifdef ADC_RC0_AN6
    {GPIO_PC0, hal_ll_adc_module_num(ADC_MODULE), {HAL_LL_AD1PCFGL_REG_ADDRESS, HAL_LL_AD2PCFGL_REG_ADDRESS}, ADC_RC0, ADC_RC0_AN6, 0},
    #endif
    #ifdef ADC_RC1_AN7
    {GPIO_PC1, hal_ll_adc_module_num(ADC_MODULE), {HAL_LL_AD1PCFGL_REG_ADDRESS, HAL_LL_AD2PCFGL_REG_ADDRESS}, ADC_RC1, ADC_RC1_AN7, 0},
    #endif
    #ifdef ADC_RC2_AN8
    {GPIO_PC2, hal_ll_adc_module_num(ADC_MODULE), {HAL_LL_AD1PCFGL_REG_ADDRESS, HAL_LL_AD2PCFGL_REG_ADDRESS}, ADC_RC2, ADC_RC2_AN8, 0},
    #endif
    #ifdef ADC_RC1_AN16
    {GPIO_PC1, hal_ll_adc_module_num(ADC_MODULE), {HAL_LL_AD1PCFGH_REG_ADDRESS, 0}, ADC_RC1, ADC_RC1_AN16, 0},
    #endif
    #ifdef ADC_RC2_AN17
    {GPIO_PC2, hal_ll_adc_module_num(ADC_MODULE), {HAL_LL_AD1PCFGH_REG_ADDRESS, 0}, ADC_RC2, ADC_RC2_AN17, 0},
    #endif
    #ifdef ADC_RA12_AN20
    {GPIO_PA12, hal_ll_adc_module_num(ADC_MODULE), {HAL_LL_AD1PCFGH_REG_ADDRESS, 0}, ADC_RA12, ADC_RA12_AN20, 0},
    #endif
    #ifdef ADC_RA13_AN21
    {GPIO_PA13, hal_ll_adc_module_num(ADC_MODULE), {HAL_LL_AD1PCFGH_REG_ADDRESS, 0}, ADC_RA13, ADC_RA13_AN21, 0},
    #endif
    #ifdef ADC_RA6_AN22
    {GPIO_PA6, hal_ll_adc_module_num(ADC_MODULE), {HAL_LL_AD1PCFGH_REG_ADDRESS, 0}, ADC_RA6, ADC_RA6_AN22, 0},
    #endif
    #ifdef ADC_RA7_AN23
    {GPIO_PA7, hal_ll_adc_module_num(ADC_MODULE), {HAL_LL_AD1PCFGH_REG_ADDRESS, 0}, ADC_RA7, ADC_RA7_AN23, 0},
    #endif
    #ifdef ADC_RC3_AN18
    {GPIO_PC3, hal_ll_adc_module_num(ADC_MODULE), {HAL_LL_AD1PCFGH_REG_ADDRESS, 0}, ADC_RC3, ADC_RC3_AN18, 0},
    #endif
    #ifdef ADC_RC4_AN19
    {GPIO_PC4, hal_ll_adc_module_num(ADC_MODULE), {HAL_LL_AD1PCFGH_REG_ADDRESS, 0}, ADC_RC4, ADC_RC4_AN19, 0},
    #endif
    #ifdef ADC_RE0_AN24
    {GPIO_PE0, hal_ll_adc_module_num(ADC_MODULE), {HAL_LL_AD1PCFGH_REG_ADDRESS, 0}, ADC_RE0, ADC_RE0_AN24, 0},
    #endif
    #ifdef ADC_RE1_AN25
    {GPIO_PE1, hal_ll_adc_module_num(ADC_MODULE), {HAL_LL_AD1PCFGH_REG_ADDRESS, 0}, ADC_RE1, ADC_RE1_AN25, 0},
    #endif
    #ifdef ADC_RE2_AN26
    {GPIO_PE2, hal_ll_adc_module_num(ADC_MODULE), {HAL_LL_AD1PCFGH_REG_ADDRESS, 0}, ADC_RE2, ADC_RE2_AN26, 0},
    #endif
    #ifdef ADC_RE3_AN27
    {GPIO_PE3, hal_ll_adc_module_num(ADC_MODULE), {HAL_LL_AD1PCFGH_REG_ADDRESS, 0}, ADC_RE3, ADC_RE3_AN27, 0},
    #endif
    #ifdef ADC_RE4_AN28
    {GPIO_PE4, hal_ll_adc_module_num(ADC_MODULE), {HAL_LL_AD1PCFGH_REG_ADDRESS, 0}, ADC_RE4, ADC_RE4_AN28, 0},
    #endif
    #ifdef ADC_RE5_AN29
    {GPIO_PE5, hal_ll_adc_module_num(ADC_MODULE), {HAL_LL_AD1PCFGH_REG_ADDRESS, 0}, ADC_RE5, ADC_RE5_AN29, 0},
    #endif
    #ifdef ADC_RE6_AN30
    {GPIO_PE6, hal_ll_adc_module_num(ADC_MODULE), {HAL_LL_AD1PCFGH_REG_ADDRESS, 0}, ADC_RE6, ADC_RE6_AN30, 0},
    #endif
    #ifdef ADC_RE7_AN31
    {GPIO_PE7, hal_ll_adc_module_num(ADC_MODULE), {HAL_LL_AD1PCFGH_REG_ADDRESS, 0}, ADC_RE7, ADC_RE7_AN31, 0},
    #endif
    #ifdef ADC2_RC1_AN16
    {GPIO_PC1, hal_ll_adc_module_num(ADC_MODULE_2), {HAL_LL_AD1PCFGH_REG_ADDRESS, 0}, ADC2_RC1, ADC2_RC1_AN16, 0},
    #endif
    #ifdef ADC2_RC2_AN17
    {GPIO_PC2, hal_ll_adc_module_num(ADC_MODULE_2), {HAL_LL_AD1PCFGH_REG_ADDRESS, 0}, ADC2_RC2, ADC2_RC2_AN17, 0},
    #endif
    #ifdef ADC1_RA12_AN20
    {GPIO_PA12, hal_ll_adc_module_num(ADC_MODULE_1), {HAL_LL_AD1PCFGH_REG_ADDRESS, 0}, ADC1_RA12, ADC1_RA12_AN20, 0},
    #endif
    #ifdef ADC1_RA13_AN21
    {GPIO_PA13, hal_ll_adc_module_num(ADC_MODULE_1), {HAL_LL_AD1PCFGH_REG_ADDRESS, 0}, ADC1_RA13, ADC1_RA13_AN21, 0},
    #endif
    #ifdef ADC2_RA12_AN20
    {GPIO_PA12, hal_ll_adc_module_num(ADC_MODULE_2), {HAL_LL_AD1PCFGH_REG_ADDRESS, 0}, ADC2_RA12, ADC2_RA12_AN20, 0},
    #endif
    #ifdef ADC2_RA13_AN21
    {GPIO_PA13, hal_ll_adc_module_num(ADC_MODULE_2), {HAL_LL_AD1PCFGH_REG_ADDRESS, 0}, ADC2_RA13, ADC2_RA13_AN21, 0},
    #endif
    #ifdef ADC2_RA6_AN22
    {GPIO_PA6, hal_ll_adc_module_num(ADC_MODULE_2), {HAL_LL_AD1PCFGH_REG_ADDRESS, 0}, ADC2_RA6, ADC2_RA6_AN22, 0},
    #endif
    #ifdef ADC2_RA7_AN23
    {GPIO_PA7, hal_ll_adc_module_num(ADC_MODULE_2), {HAL_LL_AD1PCFGH_REG_ADDRESS, 0}, ADC2_RA7, ADC2_RA7_AN23, 0},
    #endif
    #ifdef ADC2_RC3_AN18
    {GPIO_PC3, hal_ll_adc_module_num(ADC_MODULE_2), {HAL_LL_AD1PCFGH_REG_ADDRESS, 0}, ADC2_RC3, ADC2_RC3_AN18, 0},
    #endif
    #ifdef ADC2_RC4_AN19
    {GPIO_PC4, hal_ll_adc_module_num(ADC_MODULE_2), {HAL_LL_AD1PCFGH_REG_ADDRESS, 0}, ADC2_RC4, ADC2_RC4_AN19, 0},
    #endif
    #ifdef ADC2_RE0_AN24
    {GPIO_PE0, hal_ll_adc_module_num(ADC_MODULE_2), {HAL_LL_AD1PCFGH_REG_ADDRESS, 0}, ADC2_RE0, ADC2_RE0_AN24, 0},
    #endif
    #ifdef ADC2_RE1_AN25
    {GPIO_PE1, hal_ll_adc_module_num(ADC_MODULE_2), {HAL_LL_AD1PCFGH_REG_ADDRESS, 0}, ADC2_RE1, ADC2_RE1_AN25, 0},
    #endif
    #ifdef ADC2_RE2_AN26
    {GPIO_PE2, hal_ll_adc_module_num(ADC_MODULE_2), {HAL_LL_AD1PCFGH_REG_ADDRESS, 0}, ADC2_RE2, ADC2_RE2_AN26, 0},
    #endif
    #ifdef ADC2_RE3_AN27
    {GPIO_PE3, hal_ll_adc_module_num(ADC_MODULE_2), {HAL_LL_AD1PCFGH_REG_ADDRESS, 0}, ADC2_RE3, ADC2_RE3_AN27, 0},
    #endif
    #ifdef ADC2_RE4_AN28
    {GPIO_PE4, hal_ll_adc_module_num(ADC_MODULE_2), {HAL_LL_AD1PCFGH_REG_ADDRESS, 0}, ADC2_RE4, ADC2_RE4_AN28, 0},
    #endif
    #ifdef ADC2_RE5_AN29
    {GPIO_PE5, hal_ll_adc_module_num(ADC_MODULE_2), {HAL_LL_AD1PCFGH_REG_ADDRESS, 0}, ADC2_RE5, ADC2_RE5_AN29, 0},
    #endif
    #ifdef ADC2_RE6_AN30
    {GPIO_PE6, hal_ll_adc_module_num(ADC_MODULE_2), {HAL_LL_AD1PCFGH_REG_ADDRESS, 0}, ADC2_RE6, ADC2_RE6_AN30, 0},
    #endif
    #ifdef ADC2_RE7_AN31
    {GPIO_PE7, hal_ll_adc_module_num(ADC_MODULE_2), {HAL_LL_AD1PCFGH_REG_ADDRESS, 0}, ADC2_RE7, ADC2_RE7_AN31, 0},
    #endif
    #ifdef ADC_RE8_AN20
    {GPIO_PE8, hal_ll_adc_module_num(ADC_MODULE), {HAL_LL_AD1PCFGH_REG_ADDRESS, 0}, ADC_RE8, ADC_RE8_AN20, 0},
    #endif
    #ifdef ADC_RE9_AN21
    {GPIO_PE9, hal_ll_adc_module_num(ADC_MODULE), {HAL_LL_AD1PCFGH_REG_ADDRESS, 0}, ADC_RE9, ADC_RE9_AN21, 0},
    #endif
    #ifdef ADC2_RE8_AN20
    {GPIO_PE8, hal_ll_adc_module_num(ADC_MODULE_2), {HAL_LL_AD1PCFGH_REG_ADDRESS, 0}, ADC2_RE8, ADC2_RE8_AN20, 0},
    #endif
    #ifdef ADC2_RE9_AN21
    {GPIO_PE9, hal_ll_adc_module_num(ADC_MODULE_2), {HAL_LL_AD1PCFGH_REG_ADDRESS, 0}, ADC2_RE9, ADC2_RE9_AN21, 0},
    #endif
    #ifdef ADC_RA2_AN2
    {GPIO_PA2, hal_ll_adc_module_num(ADC_MODULE), {HAL_LL_AD1PCFGL_REG_ADDRESS, HAL_LL_AD2PCFGL_REG_ADDRESS}, ADC_RA2, ADC_RA2_AN2, 0},
    #endif
    #ifdef ADC_RB0_AN3
    {GPIO_PB0, hal_ll_adc_module_num(ADC_MODULE), {HAL_LL_AD1PCFGL_REG_ADDRESS, HAL_LL_AD2PCFGL_REG_ADDRESS}, ADC_RB0, ADC_RB0_AN3, 0},
    #endif
    #ifdef ADC_RB1_AN6
    {GPIO_PB1, hal_ll_adc_module_num(ADC_MODULE), {HAL_LL_AD1PCFGL_REG_ADDRESS, HAL_LL_AD2PCFGL_REG_ADDRESS}, ADC_RB1, ADC_RB1_AN6, 0},
    #endif
    #ifdef ADC_RB10_AN5
    {GPIO_PB10, hal_ll_adc_module_num(ADC_MODULE), {HAL_LL_AD1PCFGL_REG_ADDRESS, HAL_LL_AD2PCFGL_REG_ADDRESS}, ADC_RB10, ADC_RB10_AN5, 0},
    #endif
    #ifdef ADC_RB2_AN7
    {GPIO_PB2, hal_ll_adc_module_num(ADC_MODULE), {HAL_LL_AD1PCFGL_REG_ADDRESS, HAL_LL_AD2PCFGL_REG_ADDRESS}, ADC_RB2, ADC_RB2_AN7, 0},
    #endif
    #ifdef ADC_RB9_AN4
    {GPIO_PB9, hal_ll_adc_module_num(ADC_MODULE), {HAL_LL_AD1PCFGL_REG_ADDRESS, HAL_LL_AD2PCFGL_REG_ADDRESS}, ADC_RB9, ADC_RB9_AN4, 0},
    #endif
    #ifdef ADC_RC1_AN8
    {GPIO_PC1, hal_ll_adc_module_num(ADC_MODULE), {HAL_LL_AD1PCFGL_REG_ADDRESS, HAL_LL_AD2PCFGL_REG_ADDRESS}, ADC_RC1, ADC_RC1_AN8, 0},
    #endif
    #ifdef ADC_RC10_AN10
    {GPIO_PC10, hal_ll_adc_module_num(ADC_MODULE), {HAL_LL_AD1PCFGL_REG_ADDRESS, HAL_LL_AD2PCFGL_REG_ADDRESS}, ADC_RC10, ADC_RC10_AN10, 0},
    #endif
    #ifdef ADC_RC2_AN9
    {GPIO_PC2, hal_ll_adc_module_num(ADC_MODULE), {HAL_LL_AD1PCFGL_REG_ADDRESS, HAL_LL_AD2PCFGL_REG_ADDRESS}, ADC_RC2, ADC_RC2_AN9, 0},
    #endif
    #ifdef ADC_RC9_AN11
    {GPIO_PC9, hal_ll_adc_module_num(ADC_MODULE), {HAL_LL_AD1PCFGL_REG_ADDRESS, HAL_LL_AD2PCFGL_REG_ADDRESS}, ADC_RC9, ADC_RC9_AN11, 0},
    #endif
    #ifdef ADC_RA4_AN10
    {GPIO_PA4, hal_ll_adc_module_num(ADC_MODULE), {HAL_LL_AD1PCFGL_REG_ADDRESS, HAL_LL_AD2PCFGL_REG_ADDRESS}, ADC_RA4, ADC_RA4_AN10, 0},
    #endif
    #ifdef ADC_RB4_AN9
    {GPIO_PB4, hal_ll_adc_module_num(ADC_MODULE), {HAL_LL_AD1PCFGL_REG_ADDRESS, HAL_LL_AD2PCFGL_REG_ADDRESS}, ADC_RB4, ADC_RB4_AN9, 0},
    #endif
    #ifdef ADC_RC3_AN11
    {GPIO_PC3, hal_ll_adc_module_num(ADC_MODULE), {HAL_LL_AD1PCFGL_REG_ADDRESS, HAL_LL_AD2PCFGL_REG_ADDRESS}, ADC_RC3, ADC_RC3_AN11, 0},
    #endif
    #ifdef ADC_RC4_AN12
    {GPIO_PC4, hal_ll_adc_module_num(ADC_MODULE), {HAL_LL_AD1PCFGL_REG_ADDRESS, HAL_LL_AD2PCFGL_REG_ADDRESS}, ADC_RC4, ADC_RC4_AN12, 0},
    #endif
    #ifdef ADC_RC5_AN15
    {GPIO_PC5, hal_ll_adc_module_num(ADC_MODULE), {HAL_LL_AD1PCFGL_REG_ADDRESS, HAL_LL_AD2PCFGL_REG_ADDRESS}, ADC_RC5, ADC_RC5_AN15, 0},
    #endif
    #ifdef ADC1_RA2_AN13
    {GPIO_PA2, hal_ll_adc_module_num(ADC_MODULE_1), {HAL_LL_AD1PCFGL_REG_ADDRESS, HAL_LL_AD2PCFGL_REG_ADDRESS}, ADC1_RA2, ADC1_RA2_AN13, 0},
    #endif
    #ifdef ADC1_RA3_AN14
    {GPIO_PA3, hal_ll_adc_module_num(ADC_MODULE_1), {HAL_LL_AD1PCFGL_REG_ADDRESS, HAL_LL_AD2PCFGL_REG_ADDRESS}, ADC1_RA3, ADC1_RA3_AN14, 0},
    #endif
    #ifdef ADC1_RB13_AN11
    {GPIO_PB13, hal_ll_adc_module_num(ADC_MODULE_1), {HAL_LL_AD1PCFGL_REG_ADDRESS, HAL_LL_AD2PCFGL_REG_ADDRESS}, ADC1_RB13, ADC1_RB13_AN11, 0},
    #endif
    #ifdef ADC1_RB14_AN10
    {GPIO_PB14, hal_ll_adc_module_num(ADC_MODULE_1), {HAL_LL_AD1PCFGL_REG_ADDRESS, HAL_LL_AD2PCFGL_REG_ADDRESS}, ADC1_RB14, ADC1_RB14_AN10, 0},
    #endif
    #ifdef ADC1_RB15_AN9
    {GPIO_PB15, hal_ll_adc_module_num(ADC_MODULE_1), {HAL_LL_AD1PCFGL_REG_ADDRESS, HAL_LL_AD2PCFGL_REG_ADDRESS}, ADC1_RB15, ADC1_RB15_AN9, 0},
    #endif
    #ifdef ADC1_RB4_AN15
    {GPIO_PB4, hal_ll_adc_module_num(ADC_MODULE_1), {HAL_LL_AD1PCFGL_REG_ADDRESS, HAL_LL_AD2PCFGL_REG_ADDRESS}, ADC1_RB4, ADC1_RB4_AN15, 0},
    #endif
    #ifdef ADC1_RA4_AN16
    {GPIO_PA4, hal_ll_adc_module_num(ADC_MODULE_1), {HAL_LL_AD1PCFGH_REG_ADDRESS, 0}, ADC1_RA4, ADC1_RA4_AN16, 0},
    #endif
    #ifdef ADC1_RB5_AN17
    {GPIO_PB5, hal_ll_adc_module_num(ADC_MODULE_1), {HAL_LL_AD1PCFGH_REG_ADDRESS, 0}, ADC1_RB5, ADC1_RB5_AN17, 0},
    #endif
    #ifdef ADC1_RB6_AN18
    {GPIO_PB6, hal_ll_adc_module_num(ADC_MODULE_1), {HAL_LL_AD1PCFGH_REG_ADDRESS, 0}, ADC1_RB6, ADC1_RB6_AN18, 0},
    #endif
    #ifdef ADC1_RB7_AN19
    {GPIO_PB7, hal_ll_adc_module_num(ADC_MODULE_1), {HAL_LL_AD1PCFGH_REG_ADDRESS, 0}, ADC1_RB7, ADC1_RB7_AN19, 0},
    #endif
    #ifdef ADC1_RB8_AN20
    {GPIO_PB8, hal_ll_adc_module_num(ADC_MODULE_1), {HAL_LL_AD1PCFGH_REG_ADDRESS, 0}, ADC1_RB8, ADC1_RB8_AN20, 0},
    #endif
    #ifdef ADC1_RB9_AN21
    {GPIO_PB9, hal_ll_adc_module_num(ADC_MODULE_1), {HAL_LL_AD1PCFGH_REG_ADDRESS, 0}, ADC1_RB9, ADC1_RB9_AN21, 0},
    #endif
    #ifdef ADC1_RA6_AN23
    {GPIO_PA6, hal_ll_adc_module_num(ADC_MODULE_1), {HAL_LL_AD1PCFGH_REG_ADDRESS, 0}, ADC1_RA6, ADC1_RA6_AN23, 0},
    #endif
    #ifdef ADC1_RA7_AN22
    {GPIO_PA7, hal_ll_adc_module_num(ADC_MODULE_1), {HAL_LL_AD1PCFGH_REG_ADDRESS, 0}, ADC1_RA7, ADC1_RA7_AN22, 0},
    #endif
    #ifdef ADC1_RC4_AN16
    {GPIO_PC4, hal_ll_adc_module_num(ADC_MODULE_1), {HAL_LL_AD1PCFGH_REG_ADDRESS, 0}, ADC1_RC4, ADC1_RC4_AN16, 0},
    #endif
    #ifdef ADC1_RG6_AN17
    {GPIO_PG6, hal_ll_adc_module_num(ADC_MODULE_1), {HAL_LL_AD1PCFGH_REG_ADDRESS, 0}, ADC1_RG6, ADC1_RG6_AN17, 0},
    #endif
    #ifdef ADC1_RG8_AN19
    {GPIO_PG8, hal_ll_adc_module_num(ADC_MODULE_1), {HAL_LL_AD1PCFGH_REG_ADDRESS, 0}, ADC1_RG8, ADC1_RG8_AN19, 0},
    #endif
    #ifdef ADC1_RG9_AN20
    {GPIO_PG9, hal_ll_adc_module_num(ADC_MODULE_1), {HAL_LL_AD1PCFGH_REG_ADDRESS, 0}, ADC1_RG9, ADC1_RG9_AN20, 0},
    #endif
    #ifdef ADC1_RB12_AN8
    {GPIO_PB12, hal_ll_adc_module_num(ADC_MODULE_1), {HAL_LL_AD1PCFGL_REG_ADDRESS, HAL_LL_AD2PCFGL_REG_ADDRESS}, ADC1_RB12, ADC1_RB12_AN8, 0},
    #endif
    #ifdef ADC1_RB13_AN7
    {GPIO_PB13, hal_ll_adc_module_num(ADC_MODULE_1), {HAL_LL_AD1PCFGL_REG_ADDRESS, HAL_LL_AD2PCFGL_REG_ADDRESS}, ADC1_RB13, ADC1_RB13_AN7, 0},
    #endif
    #ifdef ADC1_RB14_AN6
    {GPIO_PB14, hal_ll_adc_module_num(ADC_MODULE_1), {HAL_LL_AD1PCFGL_REG_ADDRESS, HAL_LL_AD2PCFGL_REG_ADDRESS}, ADC1_RB14, ADC1_RB14_AN6, 0},
    #endif
    #ifdef ADC1_RC0_AN10
    {GPIO_PC0, hal_ll_adc_module_num(ADC_MODULE_1), {HAL_LL_AD1PCFGL_REG_ADDRESS, HAL_LL_AD2PCFGL_REG_ADDRESS}, ADC1_RC0, ADC1_RC0_AN10, 0},
    #endif
    #ifdef ADC1_RC1_AN11
    {GPIO_PC1, hal_ll_adc_module_num(ADC_MODULE_1), {HAL_LL_AD1PCFGL_REG_ADDRESS, HAL_LL_AD2PCFGL_REG_ADDRESS}, ADC1_RC1, ADC1_RC1_AN11, 0},
    #endif
    #ifdef ADC1_RC2_AN12
    {GPIO_PC2, hal_ll_adc_module_num(ADC_MODULE_1), {HAL_LL_AD1PCFGL_REG_ADDRESS, HAL_LL_AD2PCFGL_REG_ADDRESS}, ADC1_RC2, ADC1_RC2_AN12, 0},
    #endif
    #ifdef ADC1_RC3_AN13
    {GPIO_PC3, hal_ll_adc_module_num(ADC_MODULE_1), {HAL_LL_AD1PCFGL_REG_ADDRESS, HAL_LL_AD2PCFGL_REG_ADDRESS}, ADC1_RC3, ADC1_RC3_AN13, 0},
    #endif
    #ifdef ADC1_RD0_AN43
    {GPIO_PD0, hal_ll_adc_module_num(ADC_MODULE_1), {HAL_LL_AD1PCFGH_REG_ADDRESS, 0}, ADC1_RD0, ADC1_RD0_AN43, 0},
    #endif
    #ifdef ADC1_RD1_AN35
    {GPIO_PD1, hal_ll_adc_module_num(ADC_MODULE_1), {HAL_LL_AD1PCFGH_REG_ADDRESS, 0}, ADC1_RD1, ADC1_RD1_AN35, 0},
    #endif
    #ifdef ADC1_RD10_AN41
    {GPIO_PD10, hal_ll_adc_module_num(ADC_MODULE_1), {HAL_LL_AD1PCFGH_REG_ADDRESS, 0}, ADC1_RD10, ADC1_RD10_AN41, 0},
    #endif
    #ifdef ADC1_RD11_AN42
    {GPIO_PD11, hal_ll_adc_module_num(ADC_MODULE_1), {HAL_LL_AD1PCFGH_REG_ADDRESS, 0}, ADC1_RD11, ADC1_RD11_AN42, 0},
    #endif
    #ifdef ADC1_RD2_AN25
    {GPIO_PD2, hal_ll_adc_module_num(ADC_MODULE_1), {HAL_LL_AD1PCFGH_REG_ADDRESS, 0}, ADC1_RD2, ADC1_RD2_AN25, 0},
    #endif
    #ifdef ADC1_RD3_AN44
    {GPIO_PD3, hal_ll_adc_module_num(ADC_MODULE_1), {HAL_LL_AD1PCFGH_REG_ADDRESS, 0}, ADC1_RD3, ADC1_RD3_AN44, 0},
    #endif
    #ifdef ADC1_RD4_AN47
    {GPIO_PD4, hal_ll_adc_module_num(ADC_MODULE_1), {HAL_LL_AD1PCFGH_REG_ADDRESS, 0}, ADC1_RD4, ADC1_RD4_AN47, 0},
    #endif
    #ifdef ADC1_RD5_AN48
    {GPIO_PD5, hal_ll_adc_module_num(ADC_MODULE_1), {HAL_LL_AD1PCFGH_REG_ADDRESS, 0}, ADC1_RD5, ADC1_RD5_AN48, 0},
    #endif
    #ifdef ADC1_RD6_AN34
    {GPIO_PD6, hal_ll_adc_module_num(ADC_MODULE_1), {HAL_LL_AD1PCFGH_REG_ADDRESS, 0}, ADC1_RD6, ADC1_RD6_AN34, 0},
    #endif
    #ifdef ADC1_RD7_AN20
    {GPIO_PD7, hal_ll_adc_module_num(ADC_MODULE_1), {HAL_LL_AD1PCFGH_REG_ADDRESS, 0}, ADC1_RD7, ADC1_RD7_AN20, 0},
    #endif
    #ifdef ADC1_RD8_AN40
    {GPIO_PD8, hal_ll_adc_module_num(ADC_MODULE_1), {HAL_LL_AD1PCFGH_REG_ADDRESS, 0}, ADC1_RD8, ADC1_RD8_AN40, 0},
    #endif
    #ifdef ADC1_RD9_AN24
    {GPIO_PD9, hal_ll_adc_module_num(ADC_MODULE_1), {HAL_LL_AD1PCFGH_REG_ADDRESS, 0}, ADC1_RD9, ADC1_RD9_AN24, 0},
    #endif
    #ifdef ADC1_RF3_AN30
    {GPIO_PF3, hal_ll_adc_module_num(ADC_MODULE_1), {HAL_LL_AD1PCFGH_REG_ADDRESS, 0}, ADC1_RF3, ADC1_RF3_AN30, 0},
    #endif
    #ifdef ADC1_RF4_AN11
    {GPIO_PF4, hal_ll_adc_module_num(ADC_MODULE_1), {HAL_LL_AD1PCFGL_REG_ADDRESS, HAL_LL_AD2PCFGL_REG_ADDRESS}, ADC1_RF4, ADC1_RF4_AN11, 0},
    #endif
    #ifdef ADC1_RF5_AN10
    {GPIO_PF5, hal_ll_adc_module_num(ADC_MODULE_1), {HAL_LL_AD1PCFGL_REG_ADDRESS, HAL_LL_AD2PCFGL_REG_ADDRESS}, ADC1_RF5, ADC1_RF5_AN10, 0},
    #endif
    #ifdef ADC1_RG9_AN49
    {GPIO_PG9, hal_ll_adc_module_num(ADC_MODULE_1), {HAL_LL_AD1PCFGH_REG_ADDRESS, 0}, ADC1_RG9, ADC1_RG9_AN49, 0},
    #endif
    #ifdef ADC1_RA1_AN26
    {GPIO_PA1, hal_ll_adc_module_num(ADC_MODULE_1), {HAL_LL_AD1PCFGH_REG_ADDRESS, 0}, ADC1_RA1, ADC1_RA1_AN26, 0},
    #endif
    #ifdef ADC1_RA14_AN38
    {GPIO_PA14, hal_ll_adc_module_num(ADC_MODULE_1), {HAL_LL_AD1PCFGH_REG_ADDRESS, 0}, ADC1_RA14, ADC1_RA14_AN38, 0},
    #endif
    #ifdef ADC1_RA15_AN39
    {GPIO_PA15, hal_ll_adc_module_num(ADC_MODULE_1), {HAL_LL_AD1PCFGH_REG_ADDRESS, 0}, ADC1_RA15, ADC1_RA15_AN39, 0},
    #endif
    #ifdef ADC1_RA4_AN36
    {GPIO_PA4, hal_ll_adc_module_num(ADC_MODULE_1), {HAL_LL_AD1PCFGH_REG_ADDRESS, 0}, ADC1_RA4, ADC1_RA4_AN36, 0},
    #endif
    #ifdef ADC1_RA5_AN37
    {GPIO_PA5, hal_ll_adc_module_num(ADC_MODULE_1), {HAL_LL_AD1PCFGH_REG_ADDRESS, 0}, ADC1_RA5, ADC1_RA5_AN37, 0},
    #endif
    #ifdef ADC1_RC3_AN9
    {GPIO_PC3, hal_ll_adc_module_num(ADC_MODULE_1), {HAL_LL_AD1PCFGL_REG_ADDRESS, HAL_LL_AD2PCFGL_REG_ADDRESS}, ADC1_RC3, ADC1_RC3_AN9, 0},
    #endif
    #ifdef ADC1_RD12_AN45
    {GPIO_PD12, hal_ll_adc_module_num(ADC_MODULE_1), {HAL_LL_AD1PCFGH_REG_ADDRESS, 0}, ADC1_RD12, ADC1_RD12_AN45, 0},
    #endif
    #ifdef ADC1_RD13_AN46
    {GPIO_PD13, hal_ll_adc_module_num(ADC_MODULE_1), {HAL_LL_AD1PCFGH_REG_ADDRESS, 0}, ADC1_RD13, ADC1_RD13_AN46, 0},
    #endif
    #ifdef ADC1_RD14_AN28
    {GPIO_PD14, hal_ll_adc_module_num(ADC_MODULE_1), {HAL_LL_AD1PCFGH_REG_ADDRESS, 0}, ADC1_RD14, ADC1_RD14_AN28, 0},
    #endif
    #ifdef ADC1_RD15_AN29
    {GPIO_PD15, hal_ll_adc_module_num(ADC_MODULE_1), {HAL_LL_AD1PCFGH_REG_ADDRESS, 0}, ADC1_RD15, ADC1_RD15_AN29, 0},
    #endif
    #ifdef ADC1_RF13_AN27
    {GPIO_PF13, hal_ll_adc_module_num(ADC_MODULE_1), {HAL_LL_AD1PCFGH_REG_ADDRESS, 0}, ADC1_RF13, ADC1_RF13_AN27, 0},
    #endif
    #ifdef ADC1_RF2_AN31
    {GPIO_PF2, hal_ll_adc_module_num(ADC_MODULE_1), {HAL_LL_AD1PCFGH_REG_ADDRESS, 0}, ADC1_RF2, ADC1_RF2_AN31, 0},
    #endif
    #ifdef ADC1_RF8_AN32
    {GPIO_PF8, hal_ll_adc_module_num(ADC_MODULE_1), {HAL_LL_AD1PCFGH_REG_ADDRESS, 0}, ADC1_RF8, ADC1_RF8_AN32, 0},
    #endif
    #ifdef ADC1_RG15_AN33
    {GPIO_PG15, hal_ll_adc_module_num(ADC_MODULE_1), {HAL_LL_AD1PCFGH_REG_ADDRESS, 0}, ADC1_RG15, ADC1_RG15_AN33, 0},
    #endif
    #ifdef ADC1_RC3_AN12
    {GPIO_PC3, hal_ll_adc_module_num(ADC_MODULE_1), {HAL_LL_AD1PCFGL_REG_ADDRESS, HAL_LL_AD2PCFGL_REG_ADDRESS}, ADC1_RC3, ADC1_RC3_AN12, 0},
    #endif
    #endif
    // EOF list

    // BEGIN ANSEL
    #ifdef _ADC_ANSEL_
    #ifdef ADC_RB0_AN0
    {GPIO_PB0, hal_ll_adc_module_num(ADC_MODULE), {HAL_LL_ANSELB_REG_ADDRESS, 0}, ADC_RB0, ADC_RB0_AN0, 1},
    #endif
    #ifdef ADC_RB1_AN1
    {GPIO_PB1, hal_ll_adc_module_num(ADC_MODULE), {HAL_LL_ANSELB_REG_ADDRESS, 0}, ADC_RB1, ADC_RB1_AN1, 1},
    #endif
    #ifdef ADC_RB2_AN2
    {GPIO_PB2, hal_ll_adc_module_num(ADC_MODULE), {HAL_LL_ANSELB_REG_ADDRESS, 0}, ADC_RB2, ADC_RB2_AN2, 1},
    #endif
    #ifdef ADC_RB3_AN3
    {GPIO_PB3, hal_ll_adc_module_num(ADC_MODULE), {HAL_LL_ANSELB_REG_ADDRESS, 0}, ADC_RB3, ADC_RB3_AN3, 1},
    #endif
    #ifdef ADC_RB4_AN4
    {GPIO_PB4, hal_ll_adc_module_num(ADC_MODULE), {HAL_LL_ANSELB_REG_ADDRESS, 0}, ADC_RB4, ADC_RB4_AN4, 1},
    #endif
    #ifdef ADC_RB5_AN5
    {GPIO_PB5, hal_ll_adc_module_num(ADC_MODULE), {HAL_LL_ANSELB_REG_ADDRESS, 0}, ADC_RB5, ADC_RB5_AN5, 1},
    #endif
    #ifdef ADC_RB6_AN6
    {GPIO_PB6, hal_ll_adc_module_num(ADC_MODULE), {HAL_LL_ANSELB_REG_ADDRESS, 0}, ADC_RB6, ADC_RB6_AN6, 1},
    #endif
    #ifdef ADC_RB7_AN7
    {GPIO_PB7, hal_ll_adc_module_num(ADC_MODULE), {HAL_LL_ANSELB_REG_ADDRESS, 0}, ADC_RB7, ADC_RB7_AN7, 1},
    #endif
    #ifdef ADC_RB8_AN8
    {GPIO_PB8, hal_ll_adc_module_num(ADC_MODULE), {HAL_LL_ANSELB_REG_ADDRESS, 0}, ADC_RB8, ADC_RB8_AN8, 1},
    #endif
    #ifdef ADC_RB9_AN9
    {GPIO_PB9, hal_ll_adc_module_num(ADC_MODULE), {HAL_LL_ANSELB_REG_ADDRESS, 0}, ADC_RB9, ADC_RB9_AN9, 1},
    #endif
    #ifdef ADC_RB10_AN10
    {GPIO_PB10, hal_ll_adc_module_num(ADC_MODULE), {HAL_LL_ANSELB_REG_ADDRESS, 0}, ADC_RB10, ADC_RB10_AN10, 1},
    #endif
    #ifdef ADC_RB11_AN11
    {GPIO_PB11, hal_ll_adc_module_num(ADC_MODULE), {HAL_LL_ANSELB_REG_ADDRESS, 0}, ADC_RB11, ADC_RB11_AN11, 1},
    #endif
    #ifdef ADC_RB12_AN12
    {GPIO_PB12, hal_ll_adc_module_num(ADC_MODULE), {HAL_LL_ANSELB_REG_ADDRESS, 0}, ADC_RB12, ADC_RB12_AN12, 1},
    #endif
    #ifdef ADC_RB13_AN13
    {GPIO_PB13, hal_ll_adc_module_num(ADC_MODULE), {HAL_LL_ANSELB_REG_ADDRESS, 0}, ADC_RB13, ADC_RB13_AN13, 1},
    #endif
    #ifdef ADC_RB14_AN14
    {GPIO_PB14, hal_ll_adc_module_num(ADC_MODULE), {HAL_LL_ANSELB_REG_ADDRESS, 0}, ADC_RB14, ADC_RB14_AN14, 1},
    #endif
    #ifdef ADC_RB15_AN15
    {GPIO_PB15, hal_ll_adc_module_num(ADC_MODULE), {HAL_LL_ANSELB_REG_ADDRESS, 0}, ADC_RB15, ADC_RB15_AN15, 1},
    #endif
    #ifdef ADC1_RA0_AN0
    {GPIO_PA0, hal_ll_adc_module_num(ADC_MODULE_1), {HAL_LL_ANSELA_REG_ADDRESS, 0}, ADC1_RA0, ADC1_RA0_AN0, 1},
    #endif
    #ifdef ADC1_RA1_AN1
    {GPIO_PA1, hal_ll_adc_module_num(ADC_MODULE_1), {HAL_LL_ANSELA_REG_ADDRESS, 0}, ADC1_RA1, ADC1_RA1_AN1, 1},
    #endif
    #ifdef ADC1_RA2_AN32
    {GPIO_PA2, hal_ll_adc_module_num(ADC_MODULE_1), {HAL_LL_ANSELA_REG_ADDRESS, 0}, ADC1_RA2, ADC1_RA2_AN32, 1},
    #endif
    #ifdef ADC1_RA4_AN24
    {GPIO_PA4, hal_ll_adc_module_num(ADC_MODULE_1), {HAL_LL_ANSELA_REG_ADDRESS, 0}, ADC1_RA4, ADC1_RA4_AN24, 1},
    #endif
    #ifdef ADC1_RA9_AN28
    {GPIO_PA9, hal_ll_adc_module_num(ADC_MODULE_1), {HAL_LL_ANSELA_REG_ADDRESS, 0}, ADC1_RA9, ADC1_RA9_AN28, 1},
    #endif
    #ifdef ADC1_RB0_AN2
    {GPIO_PB0, hal_ll_adc_module_num(ADC_MODULE_1), {HAL_LL_ANSELB_REG_ADDRESS, 0}, ADC1_RB0, ADC1_RB0_AN2, 1},
    #endif
    #ifdef ADC1_RB1_AN3
    {GPIO_PB1, hal_ll_adc_module_num(ADC_MODULE_1), {HAL_LL_ANSELB_REG_ADDRESS, 0}, ADC1_RB1, ADC1_RB1_AN3, 1},
    #endif
    #ifdef ADC1_RB2_AN4
    {GPIO_PB2, hal_ll_adc_module_num(ADC_MODULE_1), {HAL_LL_ANSELB_REG_ADDRESS, 0}, ADC1_RB2, ADC1_RB2_AN4, 1},
    #endif
    #ifdef ADC1_RB3_AN5
    {GPIO_PB3, hal_ll_adc_module_num(ADC_MODULE_1), {HAL_LL_ANSELB_REG_ADDRESS, 0}, ADC1_RB3, ADC1_RB3_AN5, 1},
    #endif
    #ifdef ADC1_RB7_AN25
    {GPIO_PB7, hal_ll_adc_module_num(ADC_MODULE_1), {HAL_LL_ANSELB_REG_ADDRESS, 0}, ADC1_RB7, ADC1_RB7_AN25, 1},
    #endif
    #ifdef ADC1_RB8_AN26
    {GPIO_PB8, hal_ll_adc_module_num(ADC_MODULE_1), {HAL_LL_ANSELB_REG_ADDRESS, 0}, ADC1_RB8, ADC1_RB8_AN26, 1},
    #endif
    #ifdef ADC1_RB9_AN27
    {GPIO_PB9, hal_ll_adc_module_num(ADC_MODULE_1), {HAL_LL_ANSELB_REG_ADDRESS, 0}, ADC1_RB9, ADC1_RB9_AN27, 1},
    #endif
    #ifdef ADC1_RC0_AN6
    {GPIO_PC0, hal_ll_adc_module_num(ADC_MODULE_1), {HAL_LL_ANSELC_REG_ADDRESS, 0}, ADC1_RC0, ADC1_RC0_AN6, 1},
    #endif
    #ifdef ADC1_RC1_AN7
    {GPIO_PC1, hal_ll_adc_module_num(ADC_MODULE_1), {HAL_LL_ANSELC_REG_ADDRESS, 0}, ADC1_RC1, ADC1_RC1_AN7, 1},
    #endif
    #ifdef ADC1_RC2_AN8
    {GPIO_PC2, hal_ll_adc_module_num(ADC_MODULE_1), {HAL_LL_ANSELC_REG_ADDRESS, 0}, ADC1_RC2, ADC1_RC2_AN8, 1},
    #endif
    #ifdef ADC1_RC3_AN29
    {GPIO_PC3, hal_ll_adc_module_num(ADC_MODULE_1), {HAL_LL_ANSELC_REG_ADDRESS, 0}, ADC1_RC3, ADC1_RC3_AN29, 1},
    #endif
    #ifdef ADC1_RC4_AN30
    {GPIO_PC4, hal_ll_adc_module_num(ADC_MODULE_1), {HAL_LL_ANSELC_REG_ADDRESS, 0}, ADC1_RC4, ADC1_RC4_AN30, 1},
    #endif
    #ifdef ADC1_RC5_AN31
    {GPIO_PC5, hal_ll_adc_module_num(ADC_MODULE_1), {HAL_LL_ANSELC_REG_ADDRESS, 0}, ADC1_RC5, ADC1_RC5_AN31, 1},
    #endif
    #ifdef ADC2_RA0_AN0
    {GPIO_PA0, hal_ll_adc_module_num(ADC_MODULE_2), {HAL_LL_ANSELA_REG_ADDRESS, 0}, ADC2_RA0, ADC2_RA0_AN0, 1},
    #endif
    #ifdef ADC2_RA1_AN1
    {GPIO_PA1, hal_ll_adc_module_num(ADC_MODULE_2), {HAL_LL_ANSELA_REG_ADDRESS, 0}, ADC2_RA1, ADC2_RA1_AN1, 1},
    #endif
    #ifdef ADC2_RA4_AN24
    {GPIO_PA4, hal_ll_adc_module_num(ADC_MODULE_2), {HAL_LL_ANSELA_REG_ADDRESS, 0}, ADC2_RA4, ADC2_RA4_AN24, 1},
    #endif
    #ifdef ADC2_RA9_AN28
    {GPIO_PA9, hal_ll_adc_module_num(ADC_MODULE_2), {HAL_LL_ANSELA_REG_ADDRESS, 0}, ADC2_RA9, ADC2_RA9_AN28, 1},
    #endif
    #ifdef ADC2_RB0_AN2
    {GPIO_PB0, hal_ll_adc_module_num(ADC_MODULE_2), {HAL_LL_ANSELB_REG_ADDRESS, 0}, ADC2_RB0, ADC2_RB0_AN2, 1},
    #endif
    #ifdef ADC2_RB1_AN3
    {GPIO_PB1, hal_ll_adc_module_num(ADC_MODULE_2), {HAL_LL_ANSELB_REG_ADDRESS, 0}, ADC2_RB1, ADC2_RB1_AN3, 1},
    #endif
    #ifdef ADC2_RB2_AN4
    {GPIO_PB2, hal_ll_adc_module_num(ADC_MODULE_2), {HAL_LL_ANSELB_REG_ADDRESS, 0}, ADC2_RB2, ADC2_RB2_AN4, 1},
    #endif
    #ifdef ADC2_RB3_AN5
    {GPIO_PB3, hal_ll_adc_module_num(ADC_MODULE_2), {HAL_LL_ANSELB_REG_ADDRESS, 0}, ADC2_RB3, ADC2_RB3_AN5, 1},
    #endif
    #ifdef ADC2_RB7_AN25
    {GPIO_PB7, hal_ll_adc_module_num(ADC_MODULE_2), {HAL_LL_ANSELB_REG_ADDRESS, 0}, ADC2_RB7, ADC2_RB7_AN25, 1},
    #endif
    #ifdef ADC2_RB8_AN26
    {GPIO_PB8, hal_ll_adc_module_num(ADC_MODULE_2), {HAL_LL_ANSELB_REG_ADDRESS, 0}, ADC2_RB8, ADC2_RB8_AN26, 1},
    #endif
    #ifdef ADC2_RB9_AN27
    {GPIO_PB9, hal_ll_adc_module_num(ADC_MODULE_2), {HAL_LL_ANSELB_REG_ADDRESS, 0}, ADC2_RB9, ADC2_RB9_AN27, 1},
    #endif
    #ifdef ADC2_RC0_AN6
    {GPIO_PC0, hal_ll_adc_module_num(ADC_MODULE_2), {HAL_LL_ANSELC_REG_ADDRESS, 0}, ADC2_RC0, ADC2_RC0_AN6, 1},
    #endif
    #ifdef ADC2_RC1_AN7
    {GPIO_PC1, hal_ll_adc_module_num(ADC_MODULE_2), {HAL_LL_ANSELC_REG_ADDRESS, 0}, ADC2_RC1, ADC2_RC1_AN7, 1},
    #endif
    #ifdef ADC2_RC2_AN8
    {GPIO_PC2, hal_ll_adc_module_num(ADC_MODULE_2), {HAL_LL_ANSELC_REG_ADDRESS, 0}, ADC2_RC2, ADC2_RC2_AN8, 1},
    #endif
    #ifdef ADC2_RC3_AN29
    {GPIO_PC3, hal_ll_adc_module_num(ADC_MODULE_2), {HAL_LL_ANSELC_REG_ADDRESS, 0}, ADC2_RC3, ADC2_RC3_AN29, 1},
    #endif
    #ifdef ADC2_RC4_AN30
    {GPIO_PC4, hal_ll_adc_module_num(ADC_MODULE_2), {HAL_LL_ANSELC_REG_ADDRESS, 0}, ADC2_RC4, ADC2_RC4_AN30, 1},
    #endif
    #ifdef ADC2_RC5_AN31
    {GPIO_PC5, hal_ll_adc_module_num(ADC_MODULE_2), {HAL_LL_ANSELC_REG_ADDRESS, 0}, ADC2_RC5, ADC2_RC5_AN31, 1},
    #endif
    #ifdef ADC1_RA11_AN9
    {GPIO_PA11, hal_ll_adc_module_num(ADC_MODULE_1), {HAL_LL_ANSELA_REG_ADDRESS, 0}, ADC1_RA11, ADC1_RA11_AN9, 1},
    #endif
    #ifdef ADC1_RA12_AN10
    {GPIO_PA12, hal_ll_adc_module_num(ADC_MODULE_1), {HAL_LL_ANSELA_REG_ADDRESS, 0}, ADC1_RA12, ADC1_RA12_AN10, 1},
    #endif
    #ifdef ADC1_RC10_AN48
    {GPIO_PC10, hal_ll_adc_module_num(ADC_MODULE_1), {HAL_LL_ANSELC_REG_ADDRESS, 0}, ADC1_RC10, ADC1_RC10_AN48, 1},
    #endif
    #ifdef ADC1_RC11_AN11
    {GPIO_PC11, hal_ll_adc_module_num(ADC_MODULE_1), {HAL_LL_ANSELC_REG_ADDRESS, 0}, ADC1_RC11, ADC1_RC11_AN11, 1},
    #endif
    #ifdef ADC1_RC12_AN49
    {GPIO_PC12, hal_ll_adc_module_num(ADC_MODULE_1), {HAL_LL_ANSELC_REG_ADDRESS, 0}, ADC1_RC12, ADC1_RC12_AN49, 1},
    #endif
    #ifdef ADC1_RE12_AN12
    {GPIO_PE12, hal_ll_adc_module_num(ADC_MODULE_1), {HAL_LL_ANSELE_REG_ADDRESS, 0}, ADC1_RE12, ADC1_RE12_AN12, 1},
    #endif
    #ifdef ADC1_RE13_AN13
    {GPIO_PE13, hal_ll_adc_module_num(ADC_MODULE_1), {HAL_LL_ANSELE_REG_ADDRESS, 0}, ADC1_RE13, ADC1_RE13_AN13, 1},
    #endif
    #ifdef ADC1_RE14_AN14
    {GPIO_PE14, hal_ll_adc_module_num(ADC_MODULE_1), {HAL_LL_ANSELE_REG_ADDRESS, 0}, ADC1_RE14, ADC1_RE14_AN14, 1},
    #endif
    #ifdef ADC1_RE15_AN15
    {GPIO_PE15, hal_ll_adc_module_num(ADC_MODULE_1), {HAL_LL_ANSELE_REG_ADDRESS, 0}, ADC1_RE15, ADC1_RE15_AN15, 1},
    #endif
    #ifdef ADC1_RG6_AN19
    {GPIO_PG6, hal_ll_adc_module_num(ADC_MODULE_1), {HAL_LL_ANSELG_REG_ADDRESS, 0}, ADC1_RG6, ADC1_RG6_AN19, 1},
    #endif
    #ifdef ADC1_RG7_AN18
    {GPIO_PG7, hal_ll_adc_module_num(ADC_MODULE_1), {HAL_LL_ANSELG_REG_ADDRESS, 0}, ADC1_RG7, ADC1_RG7_AN18, 1},
    #endif
    #ifdef ADC1_RG8_AN17
    {GPIO_PG8, hal_ll_adc_module_num(ADC_MODULE_1), {HAL_LL_ANSELG_REG_ADDRESS, 0}, ADC1_RG8, ADC1_RG8_AN17, 1},
    #endif
    #ifdef ADC1_RG9_AN16
    {GPIO_PG9, hal_ll_adc_module_num(ADC_MODULE_1), {HAL_LL_ANSELG_REG_ADDRESS, 0}, ADC1_RG9, ADC1_RG9_AN16, 1},
    #endif
    #ifdef ADC2_RA11_AN9
    {GPIO_PA11, hal_ll_adc_module_num(ADC_MODULE_2), {HAL_LL_ANSELA_REG_ADDRESS, 0}, ADC2_RA11, ADC2_RA11_AN9, 1},
    #endif
    #ifdef ADC2_RA12_AN10
    {GPIO_PA12, hal_ll_adc_module_num(ADC_MODULE_2), {HAL_LL_ANSELA_REG_ADDRESS, 0}, ADC2_RA12, ADC2_RA12_AN10, 1},
    #endif
    #ifdef ADC2_RC11_AN11
    {GPIO_PC11, hal_ll_adc_module_num(ADC_MODULE_2), {HAL_LL_ANSELC_REG_ADDRESS, 0}, ADC2_RC11, ADC2_RC11_AN11, 1},
    #endif
    #ifdef ADC2_RE12_AN12
    {GPIO_PE12, hal_ll_adc_module_num(ADC_MODULE_2), {HAL_LL_ANSELE_REG_ADDRESS, 0}, ADC2_RE12, ADC2_RE12_AN12, 1},
    #endif
    #ifdef ADC2_RE13_AN13
    {GPIO_PE13, hal_ll_adc_module_num(ADC_MODULE_2), {HAL_LL_ANSELE_REG_ADDRESS, 0}, ADC2_RE13, ADC2_RE13_AN13, 1},
    #endif
    #ifdef ADC2_RE14_AN14
    {GPIO_PE14, hal_ll_adc_module_num(ADC_MODULE_2), {HAL_LL_ANSELE_REG_ADDRESS, 0}, ADC2_RE14, ADC2_RE14_AN14, 1},
    #endif
    #ifdef ADC2_RE15_AN15
    {GPIO_PE15, hal_ll_adc_module_num(ADC_MODULE_2), {HAL_LL_ANSELE_REG_ADDRESS, 0}, ADC2_RE15, ADC2_RE15_AN15, 1},
    #endif
    #ifdef ADC2_RG6_AN19
    {GPIO_PG6, hal_ll_adc_module_num(ADC_MODULE_2), {HAL_LL_ANSELG_REG_ADDRESS, 0}, ADC2_RG6, ADC2_RG6_AN19, 1},
    #endif
    #ifdef ADC2_RG7_AN18
    {GPIO_PG7, hal_ll_adc_module_num(ADC_MODULE_2), {HAL_LL_ANSELG_REG_ADDRESS, 0}, ADC2_RG7, ADC2_RG7_AN18, 1},
    #endif
    #ifdef ADC2_RG8_AN17
    {GPIO_PG8, hal_ll_adc_module_num(ADC_MODULE_2), {HAL_LL_ANSELG_REG_ADDRESS, 0}, ADC2_RG8, ADC2_RG8_AN17, 1},
    #endif
    #ifdef ADC2_RG9_AN16
    {GPIO_PG9, hal_ll_adc_module_num(ADC_MODULE_2), {HAL_LL_ANSELG_REG_ADDRESS, 0}, ADC2_RG9, ADC2_RG9_AN16, 1},
    #endif
    #ifdef ADC1_RA14_AN46
    {GPIO_PA14, hal_ll_adc_module_num(ADC_MODULE_1), {HAL_LL_ANSELA_REG_ADDRESS, 0}, ADC1_RA14, ADC1_RA14_AN46, 1},
    #endif
    #ifdef ADC1_RA15_AN47
    {GPIO_PA15, hal_ll_adc_module_num(ADC_MODULE_1), {HAL_LL_ANSELA_REG_ADDRESS, 0}, ADC1_RA15, ADC1_RA15_AN47, 1},
    #endif
    #ifdef ADC1_RD14_AN38
    {GPIO_PD14, hal_ll_adc_module_num(ADC_MODULE_1), {HAL_LL_ANSELD_REG_ADDRESS, 0}, ADC1_RD14, ADC1_RD14_AN38, 1},
    #endif
    #ifdef ADC1_RD15_AN39
    {GPIO_PD15, hal_ll_adc_module_num(ADC_MODULE_1), {HAL_LL_ANSELD_REG_ADDRESS, 0}, ADC1_RD15, ADC1_RD15_AN39, 1},
    #endif
    #ifdef ADC1_RE0_AN40
    {GPIO_PE0, hal_ll_adc_module_num(ADC_MODULE_1), {HAL_LL_ANSELE_REG_ADDRESS, 0}, ADC1_RE0, ADC1_RE0_AN40, 1},
    #endif
    #ifdef ADC1_RE1_AN41
    {GPIO_PE1, hal_ll_adc_module_num(ADC_MODULE_1), {HAL_LL_ANSELE_REG_ADDRESS, 0}, ADC1_RE1, ADC1_RE1_AN41, 1},
    #endif
    #ifdef ADC1_RE8_AN21
    {GPIO_PE8, hal_ll_adc_module_num(ADC_MODULE_1), {HAL_LL_ANSELE_REG_ADDRESS, 0}, ADC1_RE8, ADC1_RE8_AN21, 1},
    #endif
    #ifdef ADC1_RE9_AN20
    {GPIO_PE9, hal_ll_adc_module_num(ADC_MODULE_1), {HAL_LL_ANSELE_REG_ADDRESS, 0}, ADC1_RE9, ADC1_RE9_AN20, 1},
    #endif
    #ifdef ADC1_RF10_AN34
    {GPIO_PF10, hal_ll_adc_module_num(ADC_MODULE_1), {HAL_LL_ANSELF_REG_ADDRESS, 0}, ADC1_RF10, ADC1_RF10_AN34, 1},
    #endif
    #ifdef ADC1_RF12_AN37
    {GPIO_PF12, hal_ll_adc_module_num(ADC_MODULE_1), {HAL_LL_ANSELF_REG_ADDRESS, 0}, ADC1_RF12, ADC1_RF12_AN37, 1},
    #endif
    #ifdef ADC1_RF13_AN36
    {GPIO_PF13, hal_ll_adc_module_num(ADC_MODULE_1), {HAL_LL_ANSELF_REG_ADDRESS, 0}, ADC1_RF13, ADC1_RF13_AN36, 1},
    #endif
    #ifdef ADC1_RF4_AN44
    {GPIO_PF4, hal_ll_adc_module_num(ADC_MODULE_1), {HAL_LL_ANSELF_REG_ADDRESS, 0}, ADC1_RF4, ADC1_RF4_AN44, 1},
    #endif
    #ifdef ADC1_RF5_AN45
    {GPIO_PF5, hal_ll_adc_module_num(ADC_MODULE_1), {HAL_LL_ANSELF_REG_ADDRESS, 0}, ADC1_RF5, ADC1_RF5_AN45, 1},
    #endif
    #ifdef ADC1_RF9_AN33
    {GPIO_PF9, hal_ll_adc_module_num(ADC_MODULE_1), {HAL_LL_ANSELF_REG_ADDRESS, 0}, ADC1_RF9, ADC1_RF9_AN33, 1},
    #endif
    #ifdef ADC1_RG10_AN22
    {GPIO_PG10, hal_ll_adc_module_num(ADC_MODULE_1), {HAL_LL_ANSELG_REG_ADDRESS, 0}, ADC1_RG10, ADC1_RG10_AN22, 1},
    #endif
    #ifdef ADC1_RG11_AN35
    {GPIO_PG11, hal_ll_adc_module_num(ADC_MODULE_1), {HAL_LL_ANSELG_REG_ADDRESS, 0}, ADC1_RG11, ADC1_RG11_AN35, 1},
    #endif
    #ifdef ADC1_RG15_AN23
    {GPIO_PG15, hal_ll_adc_module_num(ADC_MODULE_1), {HAL_LL_ANSELG_REG_ADDRESS, 0}, ADC1_RG15, ADC1_RG15_AN23, 1},
    #endif
    #ifdef ADC1_RG2_AN42
    {GPIO_PG2, hal_ll_adc_module_num(ADC_MODULE_1), {HAL_LL_ANSELG_REG_ADDRESS, 0}, ADC1_RG2, ADC1_RG2_AN42, 1},
    #endif
    #ifdef ADC1_RG3_AN43
    {GPIO_PG3, hal_ll_adc_module_num(ADC_MODULE_1), {HAL_LL_ANSELG_REG_ADDRESS, 0}, ADC1_RG3, ADC1_RG3_AN43, 1},
    #endif
    #ifdef ADC2_RE8_AN21
    {GPIO_PE8, hal_ll_adc_module_num(ADC_MODULE_2), {HAL_LL_ANSELE_REG_ADDRESS, 0}, ADC2_RE8, ADC2_RE8_AN21, 1},
    #endif
    #ifdef ADC2_RE9_AN20
    {GPIO_PE9, hal_ll_adc_module_num(ADC_MODULE_2), {HAL_LL_ANSELE_REG_ADDRESS, 0}, ADC2_RE9, ADC2_RE9_AN20, 1},
    #endif
    #ifdef ADC2_RG10_AN22
    {GPIO_PG10, hal_ll_adc_module_num(ADC_MODULE_2), {HAL_LL_ANSELG_REG_ADDRESS, 0}, ADC2_RG10, ADC2_RG10_AN22, 1},
    #endif
    #ifdef ADC2_RG15_AN23
    {GPIO_PG15, hal_ll_adc_module_num(ADC_MODULE_2), {HAL_LL_ANSELG_REG_ADDRESS, 0}, ADC2_RG15, ADC2_RG15_AN23, 1},
    #endif
    #ifdef ADC1_RA2_AN2
    {GPIO_PA2, hal_ll_adc_module_num(ADC_MODULE_1), {HAL_LL_ANSELA_REG_ADDRESS, 0}, ADC1_RA2, ADC1_RA2_AN2, 1},
    #endif
    #ifdef ADC1_RB0_AN3
    {GPIO_PB0, hal_ll_adc_module_num(ADC_MODULE_1), {HAL_LL_ANSELB_REG_ADDRESS, 0}, ADC1_RB0, ADC1_RB0_AN3, 1},
    #endif
    #ifdef ADC1_RB1_AN6
    {GPIO_PB1, hal_ll_adc_module_num(ADC_MODULE_1), {HAL_LL_ANSELB_REG_ADDRESS, 0}, ADC1_RB1, ADC1_RB1_AN6, 1},
    #endif
    #ifdef ADC1_RB2_AN7
    {GPIO_PB2, hal_ll_adc_module_num(ADC_MODULE_1), {HAL_LL_ANSELB_REG_ADDRESS, 0}, ADC1_RB2, ADC1_RB2_AN7, 1},
    #endif
    #ifdef ADC1_RB3_AN18
    {GPIO_PB3, hal_ll_adc_module_num(ADC_MODULE_1), {HAL_LL_ANSELB_REG_ADDRESS, 0}, ADC1_RB3, ADC1_RB3_AN18, 1},
    #endif
    #ifdef ADC1_RB5_AN19
    {GPIO_PB5, hal_ll_adc_module_num(ADC_MODULE_1), {HAL_LL_ANSELB_REG_ADDRESS, 0}, ADC1_RB5, ADC1_RB5_AN19, 1},
    #endif
    #ifdef ADC1_RB6_AN20
    {GPIO_PB6, hal_ll_adc_module_num(ADC_MODULE_1), {HAL_LL_ANSELB_REG_ADDRESS, 0}, ADC1_RB6, ADC1_RB6_AN20, 1},
    #endif
    #ifdef ADC1_RB7_AN21
    {GPIO_PB7, hal_ll_adc_module_num(ADC_MODULE_1), {HAL_LL_ANSELB_REG_ADDRESS, 0}, ADC1_RB7, ADC1_RB7_AN21, 1},
    #endif
    #ifdef ADC1_RB9_AN4
    {GPIO_PB9, hal_ll_adc_module_num(ADC_MODULE_1), {HAL_LL_ANSELB_REG_ADDRESS, 0}, ADC1_RB9, ADC1_RB9_AN4, 1},
    #endif
    #ifdef ADC1_RC1_AN8
    {GPIO_PC1, hal_ll_adc_module_num(ADC_MODULE_1), {HAL_LL_ANSELC_REG_ADDRESS, 0}, ADC1_RC1, ADC1_RC1_AN8, 1},
    #endif
    #ifdef ADC1_RC10_AN10
    {GPIO_PC10, hal_ll_adc_module_num(ADC_MODULE_1), {HAL_LL_ANSELC_REG_ADDRESS, 0}, ADC1_RC10, ADC1_RC10_AN10, 1},
    #endif
    #ifdef ADC1_RC12_AN14
    {GPIO_PC12, hal_ll_adc_module_num(ADC_MODULE_1), {HAL_LL_ANSELC_REG_ADDRESS, 0}, ADC1_RC12, ADC1_RC12_AN14, 1},
    #endif
    #ifdef ADC1_RC2_AN9
    {GPIO_PC2, hal_ll_adc_module_num(ADC_MODULE_1), {HAL_LL_ANSELC_REG_ADDRESS, 0}, ADC1_RC2, ADC1_RC2_AN9, 1},
    #endif
    #ifdef ADC1_RC6_AN17
    {GPIO_PC6, hal_ll_adc_module_num(ADC_MODULE_1), {HAL_LL_ANSELC_REG_ADDRESS, 0}, ADC1_RC6, ADC1_RC6_AN17, 1},
    #endif
    #ifdef ADC1_RC9_AN11
    {GPIO_PC9, hal_ll_adc_module_num(ADC_MODULE_1), {HAL_LL_ANSELC_REG_ADDRESS, 0}, ADC1_RC9, ADC1_RC9_AN11, 1},
    #endif
    #ifdef ADC1_RD13_AN13
    {GPIO_PD13, hal_ll_adc_module_num(ADC_MODULE_1), {HAL_LL_ANSELD_REG_ADDRESS, 0}, ADC1_RD13, ADC1_RD13_AN13, 1},
    #endif
    #ifdef ADC1_RD2_AN16
    {GPIO_PD2, hal_ll_adc_module_num(ADC_MODULE_1), {HAL_LL_ANSELD_REG_ADDRESS, 0}, ADC1_RD2, ADC1_RD2_AN16, 1},
    #endif
    #ifdef ADC1_RD5_AN12
    {GPIO_PD5, hal_ll_adc_module_num(ADC_MODULE_1), {HAL_LL_ANSELD_REG_ADDRESS, 0}, ADC1_RD5, ADC1_RD5_AN12, 1},
    #endif
    #ifdef ADC1_RD7_AN15
    {GPIO_PD7, hal_ll_adc_module_num(ADC_MODULE_1), {HAL_LL_ANSELD_REG_ADDRESS, 0}, ADC1_RD7, ADC1_RD7_AN15, 1},
    #endif
    #ifdef ADC1_RD8_AN5
    {GPIO_PD8, hal_ll_adc_module_num(ADC_MODULE_1), {HAL_LL_ANSELD_REG_ADDRESS, 0}, ADC1_RD8, ADC1_RD8_AN5, 1},
    #endif
    #ifdef ADC1_RB10_AN5
    {GPIO_PB10, hal_ll_adc_module_num(ADC_MODULE_1), {HAL_LL_ANSELB_REG_ADDRESS, 0}, ADC1_RB10, ADC1_RB10_AN5, 1},
    #endif
    #ifdef ADC1_RB3_AN8
    {GPIO_PB3, hal_ll_adc_module_num(ADC_MODULE_1), {HAL_LL_ANSELB_REG_ADDRESS, 0}, ADC1_RB3, ADC1_RB3_AN8, 1},
    #endif
    #ifdef ADC1_RB5_AN9
    {GPIO_PB5, hal_ll_adc_module_num(ADC_MODULE_1), {HAL_LL_ANSELB_REG_ADDRESS, 0}, ADC1_RB5, ADC1_RB5_AN9, 1},
    #endif
    #ifdef ADC1_RB6_AN10
    {GPIO_PB6, hal_ll_adc_module_num(ADC_MODULE_1), {HAL_LL_ANSELB_REG_ADDRESS, 0}, ADC1_RB6, ADC1_RB6_AN10, 1},
    #endif
    #ifdef ADC1_RB7_AN11
    {GPIO_PB7, hal_ll_adc_module_num(ADC_MODULE_1), {HAL_LL_ANSELB_REG_ADDRESS, 0}, ADC1_RB7, ADC1_RB7_AN11, 1},
    #endif
    #ifdef ADC1_RC11_AN12
    {GPIO_PC11, hal_ll_adc_module_num(ADC_MODULE_1), {HAL_LL_ANSELC_REG_ADDRESS, 0}, ADC1_RC11, ADC1_RC11_AN12, 1},
    #endif
    #ifdef ADC1_RB0_AN0
    {GPIO_PB0, hal_ll_adc_module_num(ADC_MODULE_1), {HAL_LL_ANSELB_REG_ADDRESS, 0}, ADC1_RB0, ADC1_RB0_AN0, 1},
    #endif
    #ifdef ADC1_RB1_AN1
    {GPIO_PB1, hal_ll_adc_module_num(ADC_MODULE_1), {HAL_LL_ANSELB_REG_ADDRESS, 0}, ADC1_RB1, ADC1_RB1_AN1, 1},
    #endif
    #ifdef ADC1_RB10_AN10
    {GPIO_PB10, hal_ll_adc_module_num(ADC_MODULE_1), {HAL_LL_ANSELB_REG_ADDRESS, 0}, ADC1_RB10, ADC1_RB10_AN10, 1},
    #endif
    #ifdef ADC1_RB11_AN11
    {GPIO_PB11, hal_ll_adc_module_num(ADC_MODULE_1), {HAL_LL_ANSELB_REG_ADDRESS, 0}, ADC1_RB11, ADC1_RB11_AN11, 1},
    #endif
    #ifdef ADC1_RB12_AN12
    {GPIO_PB12, hal_ll_adc_module_num(ADC_MODULE_1), {HAL_LL_ANSELB_REG_ADDRESS, 0}, ADC1_RB12, ADC1_RB12_AN12, 1},
    #endif
    #ifdef ADC1_RB13_AN13
    {GPIO_PB13, hal_ll_adc_module_num(ADC_MODULE_1), {HAL_LL_ANSELB_REG_ADDRESS, 0}, ADC1_RB13, ADC1_RB13_AN13, 1},
    #endif
    #ifdef ADC1_RB14_AN14
    {GPIO_PB14, hal_ll_adc_module_num(ADC_MODULE_1), {HAL_LL_ANSELB_REG_ADDRESS, 0}, ADC1_RB14, ADC1_RB14_AN14, 1},
    #endif
    #ifdef ADC1_RB15_AN15
    {GPIO_PB15, hal_ll_adc_module_num(ADC_MODULE_1), {HAL_LL_ANSELB_REG_ADDRESS, 0}, ADC1_RB15, ADC1_RB15_AN15, 1},
    #endif
    #ifdef ADC1_RB2_AN2
    {GPIO_PB2, hal_ll_adc_module_num(ADC_MODULE_1), {HAL_LL_ANSELB_REG_ADDRESS, 0}, ADC1_RB2, ADC1_RB2_AN2, 1},
    #endif
    #ifdef ADC1_RB3_AN3
    {GPIO_PB3, hal_ll_adc_module_num(ADC_MODULE_1), {HAL_LL_ANSELB_REG_ADDRESS, 0}, ADC1_RB3, ADC1_RB3_AN3, 1},
    #endif
    #ifdef ADC1_RB4_AN4
    {GPIO_PB4, hal_ll_adc_module_num(ADC_MODULE_1), {HAL_LL_ANSELB_REG_ADDRESS, 0}, ADC1_RB4, ADC1_RB4_AN4, 1},
    #endif
    #ifdef ADC1_RB5_AN5
    {GPIO_PB5, hal_ll_adc_module_num(ADC_MODULE_1), {HAL_LL_ANSELB_REG_ADDRESS, 0}, ADC1_RB5, ADC1_RB5_AN5, 1},
    #endif
    #ifdef ADC1_RB6_AN6
    {GPIO_PB6, hal_ll_adc_module_num(ADC_MODULE_1), {HAL_LL_ANSELB_REG_ADDRESS, 0}, ADC1_RB6, ADC1_RB6_AN6, 1},
    #endif
    #ifdef ADC1_RB7_AN7
    {GPIO_PB7, hal_ll_adc_module_num(ADC_MODULE_1), {HAL_LL_ANSELB_REG_ADDRESS, 0}, ADC1_RB7, ADC1_RB7_AN7, 1},
    #endif
    #ifdef ADC1_RB8_AN8
    {GPIO_PB8, hal_ll_adc_module_num(ADC_MODULE_1), {HAL_LL_ANSELB_REG_ADDRESS, 0}, ADC1_RB8, ADC1_RB8_AN8, 1},
    #endif
    #ifdef ADC1_RB9_AN9
    {GPIO_PB9, hal_ll_adc_module_num(ADC_MODULE_1), {HAL_LL_ANSELB_REG_ADDRESS, 0}, ADC1_RB9, ADC1_RB9_AN9, 1},
    #endif
    #ifdef ADC1_RE0_AN24
    {GPIO_PE0, hal_ll_adc_module_num(ADC_MODULE_1), {HAL_LL_ANSELE_REG_ADDRESS, 0}, ADC1_RE0, ADC1_RE0_AN24, 1},
    #endif
    #ifdef ADC1_RE1_AN25
    {GPIO_PE1, hal_ll_adc_module_num(ADC_MODULE_1), {HAL_LL_ANSELE_REG_ADDRESS, 0}, ADC1_RE1, ADC1_RE1_AN25, 1},
    #endif
    #ifdef ADC1_RE2_AN26
    {GPIO_PE2, hal_ll_adc_module_num(ADC_MODULE_1), {HAL_LL_ANSELE_REG_ADDRESS, 0}, ADC1_RE2, ADC1_RE2_AN26, 1},
    #endif
    #ifdef ADC1_RE3_AN27
    {GPIO_PE3, hal_ll_adc_module_num(ADC_MODULE_1), {HAL_LL_ANSELE_REG_ADDRESS, 0}, ADC1_RE3, ADC1_RE3_AN27, 1},
    #endif
    #ifdef ADC1_RE4_AN28
    {GPIO_PE4, hal_ll_adc_module_num(ADC_MODULE_1), {HAL_LL_ANSELE_REG_ADDRESS, 0}, ADC1_RE4, ADC1_RE4_AN28, 1},
    #endif
    #ifdef ADC1_RE5_AN29
    {GPIO_PE5, hal_ll_adc_module_num(ADC_MODULE_1), {HAL_LL_ANSELE_REG_ADDRESS, 0}, ADC1_RE5, ADC1_RE5_AN29, 1},
    #endif
    #ifdef ADC1_RE6_AN30
    {GPIO_PE6, hal_ll_adc_module_num(ADC_MODULE_1), {HAL_LL_ANSELE_REG_ADDRESS, 0}, ADC1_RE6, ADC1_RE6_AN30, 1},
    #endif
    #ifdef ADC1_RE7_AN31
    {GPIO_PE7, hal_ll_adc_module_num(ADC_MODULE_1), {HAL_LL_ANSELE_REG_ADDRESS, 0}, ADC1_RE7, ADC1_RE7_AN31, 1},
    #endif
    #ifdef ADC2_RB0_AN0
    {GPIO_PB0, hal_ll_adc_module_num(ADC_MODULE_2), {HAL_LL_ANSELB_REG_ADDRESS, 0}, ADC2_RB0, ADC2_RB0_AN0, 1},
    #endif
    #ifdef ADC2_RB1_AN1
    {GPIO_PB1, hal_ll_adc_module_num(ADC_MODULE_2), {HAL_LL_ANSELB_REG_ADDRESS, 0}, ADC2_RB1, ADC2_RB1_AN1, 1},
    #endif
    #ifdef ADC2_RB10_AN10
    {GPIO_PB10, hal_ll_adc_module_num(ADC_MODULE_2), {HAL_LL_ANSELB_REG_ADDRESS, 0}, ADC2_RB10, ADC2_RB10_AN10, 1},
    #endif
    #ifdef ADC2_RB11_AN11
    {GPIO_PB11, hal_ll_adc_module_num(ADC_MODULE_2), {HAL_LL_ANSELB_REG_ADDRESS, 0}, ADC2_RB11, ADC2_RB11_AN11, 1},
    #endif
    #ifdef ADC2_RB12_AN12
    {GPIO_PB12, hal_ll_adc_module_num(ADC_MODULE_2), {HAL_LL_ANSELB_REG_ADDRESS, 0}, ADC2_RB12, ADC2_RB12_AN12, 1},
    #endif
    #ifdef ADC2_RB13_AN13
    {GPIO_PB13, hal_ll_adc_module_num(ADC_MODULE_2), {HAL_LL_ANSELB_REG_ADDRESS, 0}, ADC2_RB13, ADC2_RB13_AN13, 1},
    #endif
    #ifdef ADC2_RB14_AN14
    {GPIO_PB14, hal_ll_adc_module_num(ADC_MODULE_2), {HAL_LL_ANSELB_REG_ADDRESS, 0}, ADC2_RB14, ADC2_RB14_AN14, 1},
    #endif
    #ifdef ADC2_RB15_AN15
    {GPIO_PB15, hal_ll_adc_module_num(ADC_MODULE_2), {HAL_LL_ANSELB_REG_ADDRESS, 0}, ADC2_RB15, ADC2_RB15_AN15, 1},
    #endif
    #ifdef ADC2_RB2_AN2
    {GPIO_PB2, hal_ll_adc_module_num(ADC_MODULE_2), {HAL_LL_ANSELB_REG_ADDRESS, 0}, ADC2_RB2, ADC2_RB2_AN2, 1},
    #endif
    #ifdef ADC2_RB3_AN3
    {GPIO_PB3, hal_ll_adc_module_num(ADC_MODULE_2), {HAL_LL_ANSELB_REG_ADDRESS, 0}, ADC2_RB3, ADC2_RB3_AN3, 1},
    #endif
    #ifdef ADC2_RB4_AN4
    {GPIO_PB4, hal_ll_adc_module_num(ADC_MODULE_2), {HAL_LL_ANSELB_REG_ADDRESS, 0}, ADC2_RB4, ADC2_RB4_AN4, 1},
    #endif
    #ifdef ADC2_RB5_AN5
    {GPIO_PB5, hal_ll_adc_module_num(ADC_MODULE_2), {HAL_LL_ANSELB_REG_ADDRESS, 0}, ADC2_RB5, ADC2_RB5_AN5, 1},
    #endif
    #ifdef ADC2_RB6_AN6
    {GPIO_PB6, hal_ll_adc_module_num(ADC_MODULE_2), {HAL_LL_ANSELB_REG_ADDRESS, 0}, ADC2_RB6, ADC2_RB6_AN6, 1},
    #endif
    #ifdef ADC2_RB7_AN7
    {GPIO_PB7, hal_ll_adc_module_num(ADC_MODULE_2), {HAL_LL_ANSELB_REG_ADDRESS, 0}, ADC2_RB7, ADC2_RB7_AN7, 1},
    #endif
    #ifdef ADC2_RB8_AN8
    {GPIO_PB8, hal_ll_adc_module_num(ADC_MODULE_2), {HAL_LL_ANSELB_REG_ADDRESS, 0}, ADC2_RB8, ADC2_RB8_AN8, 1},
    #endif
    #ifdef ADC2_RB9_AN9
    {GPIO_PB9, hal_ll_adc_module_num(ADC_MODULE_2), {HAL_LL_ANSELB_REG_ADDRESS, 0}, ADC2_RB9, ADC2_RB9_AN9, 1},
    #endif
    #ifdef ADC1_RA6_AN22
    {GPIO_PA6, hal_ll_adc_module_num(ADC_MODULE_1), {HAL_LL_ANSELA_REG_ADDRESS, 0}, ADC1_RA6, ADC1_RA6_AN22, 1},
    #endif
    #ifdef ADC1_RA7_AN23
    {GPIO_PA7, hal_ll_adc_module_num(ADC_MODULE_1), {HAL_LL_ANSELA_REG_ADDRESS, 0}, ADC1_RA7, ADC1_RA7_AN23, 1},
    #endif
    #ifdef ADC1_RC1_AN16
    {GPIO_PC1, hal_ll_adc_module_num(ADC_MODULE_1), {HAL_LL_ANSELC_REG_ADDRESS, 0}, ADC1_RC1, ADC1_RC1_AN16, 1},
    #endif
    #ifdef ADC1_RC2_AN17
    {GPIO_PC2, hal_ll_adc_module_num(ADC_MODULE_1), {HAL_LL_ANSELC_REG_ADDRESS, 0}, ADC1_RC2, ADC1_RC2_AN17, 1},
    #endif
    #ifdef ADC1_RC3_AN18
    {GPIO_PC3, hal_ll_adc_module_num(ADC_MODULE_1), {HAL_LL_ANSELC_REG_ADDRESS, 0}, ADC1_RC3, ADC1_RC3_AN18, 1},
    #endif
    #ifdef ADC1_RC4_AN19
    {GPIO_PC4, hal_ll_adc_module_num(ADC_MODULE_1), {HAL_LL_ANSELC_REG_ADDRESS, 0}, ADC1_RC4, ADC1_RC4_AN19, 1},
    #endif
    #ifdef ADC1_RE8_AN20
    {GPIO_PE8, hal_ll_adc_module_num(ADC_MODULE_1), {HAL_LL_ANSELE_REG_ADDRESS, 0}, ADC1_RE8, ADC1_RE8_AN20, 1},
    #endif
    #ifdef ADC1_RE9_AN21
    {GPIO_PE9, hal_ll_adc_module_num(ADC_MODULE_1), {HAL_LL_ANSELE_REG_ADDRESS, 0}, ADC1_RE9, ADC1_RE9_AN21, 1},
    #endif
    #ifdef ADC1_RA10_AN56
    {GPIO_PA10, hal_ll_adc_module_num(ADC_MODULE_1), {HAL_LL_ANSELA_REG_ADDRESS, 0}, ADC1_RA10, ADC1_RA10_AN56, 1},
    #endif
    #ifdef ADC1_RA7_AN55
    {GPIO_PA7, hal_ll_adc_module_num(ADC_MODULE_1), {HAL_LL_ANSELA_REG_ADDRESS, 0}, ADC1_RA7, ADC1_RA7_AN55, 1},
    #endif
    #ifdef ADC1_RC6_AN53
    {GPIO_PC6, hal_ll_adc_module_num(ADC_MODULE_1), {HAL_LL_ANSELC_REG_ADDRESS, 0}, ADC1_RC6, ADC1_RC6_AN53, 1},
    #endif
    #ifdef ADC1_RC7_AN52
    {GPIO_PC7, hal_ll_adc_module_num(ADC_MODULE_1), {HAL_LL_ANSELC_REG_ADDRESS, 0}, ADC1_RC7, ADC1_RC7_AN52, 1},
    #endif
    #ifdef ADC1_RC8_AN51
    {GPIO_PC8, hal_ll_adc_module_num(ADC_MODULE_1), {HAL_LL_ANSELC_REG_ADDRESS, 0}, ADC1_RC8, ADC1_RC8_AN51, 1},
    #endif
    #ifdef ADC1_RC9_AN54
    {GPIO_PC9, hal_ll_adc_module_num(ADC_MODULE_1), {HAL_LL_ANSELC_REG_ADDRESS, 0}, ADC1_RC9, ADC1_RC9_AN54, 1},
    #endif
    #ifdef ADC_RA0_AN0
    {GPIO_PA0, hal_ll_adc_module_num(ADC_MODULE), {HAL_LL_ANSELA_REG_ADDRESS, 0}, ADC_RA0, ADC_RA0_AN0, 1},
    #endif
    #ifdef ADC_RA1_AN1
    {GPIO_PA1, hal_ll_adc_module_num(ADC_MODULE), {HAL_LL_ANSELA_REG_ADDRESS, 0}, ADC_RA1, ADC_RA1_AN1, 1},
    #endif
    #ifdef ADC_RB0_AN2
    {GPIO_PB0, hal_ll_adc_module_num(ADC_MODULE), {HAL_LL_ANSELB_REG_ADDRESS, 0}, ADC_RB0, ADC_RB0_AN2, 1},
    #endif
    #ifdef ADC_RB1_AN3
    {GPIO_PB1, hal_ll_adc_module_num(ADC_MODULE), {HAL_LL_ANSELB_REG_ADDRESS, 0}, ADC_RB1, ADC_RB1_AN3, 1},
    #endif
    #ifdef ADC_RB13_AN11
    {GPIO_PB13, hal_ll_adc_module_num(ADC_MODULE), {HAL_LL_ANSELB_REG_ADDRESS, 0}, ADC_RB13, ADC_RB13_AN11, 1},
    #endif
    #ifdef ADC_RB14_AN10
    {GPIO_PB14, hal_ll_adc_module_num(ADC_MODULE), {HAL_LL_ANSELB_REG_ADDRESS, 0}, ADC_RB14, ADC_RB14_AN10, 1},
    #endif
    #ifdef ADC_RB15_AN9
    {GPIO_PB15, hal_ll_adc_module_num(ADC_MODULE), {HAL_LL_ANSELB_REG_ADDRESS, 0}, ADC_RB15, ADC_RB15_AN9, 1},
    #endif
    #ifdef ADC_RB2_AN4
    {GPIO_PB2, hal_ll_adc_module_num(ADC_MODULE), {HAL_LL_ANSELB_REG_ADDRESS, 0}, ADC_RB2, ADC_RB2_AN4, 1},
    #endif
    #ifdef ADC_RB3_AN5
    {GPIO_PB3, hal_ll_adc_module_num(ADC_MODULE), {HAL_LL_ANSELB_REG_ADDRESS, 0}, ADC_RB3, ADC_RB3_AN5, 1},
    #endif
    #ifdef ADC_RC0_AN6
    {GPIO_PC0, hal_ll_adc_module_num(ADC_MODULE), {HAL_LL_ANSELC_REG_ADDRESS, 0}, ADC_RC0, ADC_RC0_AN6, 1},
    #endif
    #ifdef ADC_RC1_AN7
    {GPIO_PC1, hal_ll_adc_module_num(ADC_MODULE), {HAL_LL_ANSELC_REG_ADDRESS, 0}, ADC_RC1, ADC_RC1_AN7, 1},
    #endif
    #ifdef ADC_RC2_AN8
    {GPIO_PC2, hal_ll_adc_module_num(ADC_MODULE), {HAL_LL_ANSELC_REG_ADDRESS, 0}, ADC_RC2, ADC_RC2_AN8, 1},
    #endif
    #ifdef ADC_RC1_AN16
    {GPIO_PC1, hal_ll_adc_module_num(ADC_MODULE), {HAL_LL_ANSELC_REG_ADDRESS, 0}, ADC_RC1, ADC_RC1_AN16, 1},
    #endif
    #ifdef ADC_RC2_AN17
    {GPIO_PC2, hal_ll_adc_module_num(ADC_MODULE), {HAL_LL_ANSELC_REG_ADDRESS, 0}, ADC_RC2, ADC_RC2_AN17, 1},
    #endif
    #ifdef ADC_RA12_AN20
    {GPIO_PA12, hal_ll_adc_module_num(ADC_MODULE), {HAL_LL_ANSELA_REG_ADDRESS, 0}, ADC_RA12, ADC_RA12_AN20, 1},
    #endif
    #ifdef ADC_RA13_AN21
    {GPIO_PA13, hal_ll_adc_module_num(ADC_MODULE), {HAL_LL_ANSELA_REG_ADDRESS, 0}, ADC_RA13, ADC_RA13_AN21, 1},
    #endif
    #ifdef ADC_RA6_AN22
    {GPIO_PA6, hal_ll_adc_module_num(ADC_MODULE), {HAL_LL_ANSELA_REG_ADDRESS, 0}, ADC_RA6, ADC_RA6_AN22, 1},
    #endif
    #ifdef ADC_RA7_AN23
    {GPIO_PA7, hal_ll_adc_module_num(ADC_MODULE), {HAL_LL_ANSELA_REG_ADDRESS, 0}, ADC_RA7, ADC_RA7_AN23, 1},
    #endif
    #ifdef ADC_RC3_AN18
    {GPIO_PC3, hal_ll_adc_module_num(ADC_MODULE), {HAL_LL_ANSELC_REG_ADDRESS, 0}, ADC_RC3, ADC_RC3_AN18, 1},
    #endif
    #ifdef ADC_RC4_AN19
    {GPIO_PC4, hal_ll_adc_module_num(ADC_MODULE), {HAL_LL_ANSELC_REG_ADDRESS, 0}, ADC_RC4, ADC_RC4_AN19, 1},
    #endif
    #ifdef ADC_RE0_AN24
    {GPIO_PE0, hal_ll_adc_module_num(ADC_MODULE), {HAL_LL_ANSELE_REG_ADDRESS, 0}, ADC_RE0, ADC_RE0_AN24, 1},
    #endif
    #ifdef ADC_RE1_AN25
    {GPIO_PE1, hal_ll_adc_module_num(ADC_MODULE), {HAL_LL_ANSELE_REG_ADDRESS, 0}, ADC_RE1, ADC_RE1_AN25, 1},
    #endif
    #ifdef ADC_RE2_AN26
    {GPIO_PE2, hal_ll_adc_module_num(ADC_MODULE), {HAL_LL_ANSELE_REG_ADDRESS, 0}, ADC_RE2, ADC_RE2_AN26, 1},
    #endif
    #ifdef ADC_RE3_AN27
    {GPIO_PE3, hal_ll_adc_module_num(ADC_MODULE), {HAL_LL_ANSELE_REG_ADDRESS, 0}, ADC_RE3, ADC_RE3_AN27, 1},
    #endif
    #ifdef ADC_RE4_AN28
    {GPIO_PE4, hal_ll_adc_module_num(ADC_MODULE), {HAL_LL_ANSELE_REG_ADDRESS, 0}, ADC_RE4, ADC_RE4_AN28, 1},
    #endif
    #ifdef ADC_RE5_AN29
    {GPIO_PE5, hal_ll_adc_module_num(ADC_MODULE), {HAL_LL_ANSELE_REG_ADDRESS, 0}, ADC_RE5, ADC_RE5_AN29, 1},
    #endif
    #ifdef ADC_RE6_AN30
    {GPIO_PE6, hal_ll_adc_module_num(ADC_MODULE), {HAL_LL_ANSELE_REG_ADDRESS, 0}, ADC_RE6, ADC_RE6_AN30, 1},
    #endif
    #ifdef ADC_RE7_AN31
    {GPIO_PE7, hal_ll_adc_module_num(ADC_MODULE), {HAL_LL_ANSELE_REG_ADDRESS, 0}, ADC_RE7, ADC_RE7_AN31, 1},
    #endif
    #ifdef ADC2_RC1_AN16
    {GPIO_PC1, hal_ll_adc_module_num(ADC_MODULE_2), {HAL_LL_ANSELC_REG_ADDRESS, 0}, ADC2_RC1, ADC2_RC1_AN16, 1},
    #endif
    #ifdef ADC2_RC2_AN17
    {GPIO_PC2, hal_ll_adc_module_num(ADC_MODULE_2), {HAL_LL_ANSELC_REG_ADDRESS, 0}, ADC2_RC2, ADC2_RC2_AN17, 1},
    #endif
    #ifdef ADC1_RA12_AN20
    {GPIO_PA12, hal_ll_adc_module_num(ADC_MODULE_1), {HAL_LL_ANSELA_REG_ADDRESS, 0}, ADC1_RA12, ADC1_RA12_AN20, 1},
    #endif
    #ifdef ADC1_RA13_AN21
    {GPIO_PA13, hal_ll_adc_module_num(ADC_MODULE_1), {HAL_LL_ANSELA_REG_ADDRESS, 0}, ADC1_RA13, ADC1_RA13_AN21, 1},
    #endif
    #ifdef ADC2_RA12_AN20
    {GPIO_PA12, hal_ll_adc_module_num(ADC_MODULE_2), {HAL_LL_ANSELA_REG_ADDRESS, 0}, ADC2_RA12, ADC2_RA12_AN20, 1},
    #endif
    #ifdef ADC2_RA13_AN21
    {GPIO_PA13, hal_ll_adc_module_num(ADC_MODULE_2), {HAL_LL_ANSELA_REG_ADDRESS, 0}, ADC2_RA13, ADC2_RA13_AN21, 1},
    #endif
    #ifdef ADC2_RA6_AN22
    {GPIO_PA6, hal_ll_adc_module_num(ADC_MODULE_2), {HAL_LL_ANSELA_REG_ADDRESS, 0}, ADC2_RA6, ADC2_RA6_AN22, 1},
    #endif
    #ifdef ADC2_RA7_AN23
    {GPIO_PA7, hal_ll_adc_module_num(ADC_MODULE_2), {HAL_LL_ANSELA_REG_ADDRESS, 0}, ADC2_RA7, ADC2_RA7_AN23, 1},
    #endif
    #ifdef ADC2_RC3_AN18
    {GPIO_PC3, hal_ll_adc_module_num(ADC_MODULE_2), {HAL_LL_ANSELC_REG_ADDRESS, 0}, ADC2_RC3, ADC2_RC3_AN18, 1},
    #endif
    #ifdef ADC2_RC4_AN19
    {GPIO_PC4, hal_ll_adc_module_num(ADC_MODULE_2), {HAL_LL_ANSELC_REG_ADDRESS, 0}, ADC2_RC4, ADC2_RC4_AN19, 1},
    #endif
    #ifdef ADC2_RE0_AN24
    {GPIO_PE0, hal_ll_adc_module_num(ADC_MODULE_2), {HAL_LL_ANSELE_REG_ADDRESS, 0}, ADC2_RE0, ADC2_RE0_AN24, 1},
    #endif
    #ifdef ADC2_RE1_AN25
    {GPIO_PE1, hal_ll_adc_module_num(ADC_MODULE_2), {HAL_LL_ANSELE_REG_ADDRESS, 0}, ADC2_RE1, ADC2_RE1_AN25, 1},
    #endif
    #ifdef ADC2_RE2_AN26
    {GPIO_PE2, hal_ll_adc_module_num(ADC_MODULE_2), {HAL_LL_ANSELE_REG_ADDRESS, 0}, ADC2_RE2, ADC2_RE2_AN26, 1},
    #endif
    #ifdef ADC2_RE3_AN27
    {GPIO_PE3, hal_ll_adc_module_num(ADC_MODULE_2), {HAL_LL_ANSELE_REG_ADDRESS, 0}, ADC2_RE3, ADC2_RE3_AN27, 1},
    #endif
    #ifdef ADC2_RE4_AN28
    {GPIO_PE4, hal_ll_adc_module_num(ADC_MODULE_2), {HAL_LL_ANSELE_REG_ADDRESS, 0}, ADC2_RE4, ADC2_RE4_AN28, 1},
    #endif
    #ifdef ADC2_RE5_AN29
    {GPIO_PE5, hal_ll_adc_module_num(ADC_MODULE_2), {HAL_LL_ANSELE_REG_ADDRESS, 0}, ADC2_RE5, ADC2_RE5_AN29, 1},
    #endif
    #ifdef ADC2_RE6_AN30
    {GPIO_PE6, hal_ll_adc_module_num(ADC_MODULE_2), {HAL_LL_ANSELE_REG_ADDRESS, 0}, ADC2_RE6, ADC2_RE6_AN30, 1},
    #endif
    #ifdef ADC2_RE7_AN31
    {GPIO_PE7, hal_ll_adc_module_num(ADC_MODULE_2), {HAL_LL_ANSELE_REG_ADDRESS, 0}, ADC2_RE7, ADC2_RE7_AN31, 1},
    #endif
    #ifdef ADC_RE8_AN20
    {GPIO_PE8, hal_ll_adc_module_num(ADC_MODULE), {HAL_LL_ANSELE_REG_ADDRESS, 0}, ADC_RE8, ADC_RE8_AN20, 1},
    #endif
    #ifdef ADC_RE9_AN21
    {GPIO_PE9, hal_ll_adc_module_num(ADC_MODULE), {HAL_LL_ANSELE_REG_ADDRESS, 0}, ADC_RE9, ADC_RE9_AN21, 1},
    #endif
    #ifdef ADC2_RE8_AN20
    {GPIO_PE8, hal_ll_adc_module_num(ADC_MODULE_2), {HAL_LL_ANSELE_REG_ADDRESS, 0}, ADC2_RE8, ADC2_RE8_AN20, 1},
    #endif
    #ifdef ADC2_RE9_AN21
    {GPIO_PE9, hal_ll_adc_module_num(ADC_MODULE_2), {HAL_LL_ANSELE_REG_ADDRESS, 0}, ADC2_RE9, ADC2_RE9_AN21, 1},
    #endif
    #ifdef ADC_RA2_AN2
    {GPIO_PA2, hal_ll_adc_module_num(ADC_MODULE), {HAL_LL_ANSELA_REG_ADDRESS, 0}, ADC_RA2, ADC_RA2_AN2, 1},
    #endif
    #ifdef ADC_RB0_AN3
    {GPIO_PB0, hal_ll_adc_module_num(ADC_MODULE), {HAL_LL_ANSELB_REG_ADDRESS, 0}, ADC_RB0, ADC_RB0_AN3, 1},
    #endif
    #ifdef ADC_RB1_AN6
    {GPIO_PB1, hal_ll_adc_module_num(ADC_MODULE), {HAL_LL_ANSELB_REG_ADDRESS, 0}, ADC_RB1, ADC_RB1_AN6, 1},
    #endif
    #ifdef ADC_RB10_AN5
    {GPIO_PB10, hal_ll_adc_module_num(ADC_MODULE), {HAL_LL_ANSELB_REG_ADDRESS, 0}, ADC_RB10, ADC_RB10_AN5, 1},
    #endif
    #ifdef ADC_RB2_AN7
    {GPIO_PB2, hal_ll_adc_module_num(ADC_MODULE), {HAL_LL_ANSELB_REG_ADDRESS, 0}, ADC_RB2, ADC_RB2_AN7, 1},
    #endif
    #ifdef ADC_RB9_AN4
    {GPIO_PB9, hal_ll_adc_module_num(ADC_MODULE), {HAL_LL_ANSELB_REG_ADDRESS, 0}, ADC_RB9, ADC_RB9_AN4, 1},
    #endif
    #ifdef ADC_RC1_AN8
    {GPIO_PC1, hal_ll_adc_module_num(ADC_MODULE), {HAL_LL_ANSELC_REG_ADDRESS, 0}, ADC_RC1, ADC_RC1_AN8, 1},
    #endif
    #ifdef ADC_RC10_AN10
    {GPIO_PC10, hal_ll_adc_module_num(ADC_MODULE), {HAL_LL_ANSELC_REG_ADDRESS, 0}, ADC_RC10, ADC_RC10_AN10, 1},
    #endif
    #ifdef ADC_RC2_AN9
    {GPIO_PC2, hal_ll_adc_module_num(ADC_MODULE), {HAL_LL_ANSELC_REG_ADDRESS, 0}, ADC_RC2, ADC_RC2_AN9, 1},
    #endif
    #ifdef ADC_RC9_AN11
    {GPIO_PC9, hal_ll_adc_module_num(ADC_MODULE), {HAL_LL_ANSELC_REG_ADDRESS, 0}, ADC_RC9, ADC_RC9_AN11, 1},
    #endif
    #ifdef ADC_RA4_AN10
    {GPIO_PA4, hal_ll_adc_module_num(ADC_MODULE), {HAL_LL_ANSELA_REG_ADDRESS, 0}, ADC_RA4, ADC_RA4_AN10, 1},
    #endif
    #ifdef ADC_RB4_AN9
    {GPIO_PB4, hal_ll_adc_module_num(ADC_MODULE), {HAL_LL_ANSELB_REG_ADDRESS, 0}, ADC_RB4, ADC_RB4_AN9, 1},
    #endif
    #ifdef ADC_RC3_AN11
    {GPIO_PC3, hal_ll_adc_module_num(ADC_MODULE), {HAL_LL_ANSELC_REG_ADDRESS, 0}, ADC_RC3, ADC_RC3_AN11, 1},
    #endif
    #ifdef ADC_RC4_AN12
    {GPIO_PC4, hal_ll_adc_module_num(ADC_MODULE), {HAL_LL_ANSELC_REG_ADDRESS, 0}, ADC_RC4, ADC_RC4_AN12, 1},
    #endif
    #ifdef ADC_RC5_AN15
    {GPIO_PC5, hal_ll_adc_module_num(ADC_MODULE), {HAL_LL_ANSELC_REG_ADDRESS, 0}, ADC_RC5, ADC_RC5_AN15, 1},
    #endif
    #ifdef ADC1_RA2_AN13
    {GPIO_PA2, hal_ll_adc_module_num(ADC_MODULE_1), {HAL_LL_ANSELA_REG_ADDRESS, 0}, ADC1_RA2, ADC1_RA2_AN13, 1},
    #endif
    #ifdef ADC1_RA3_AN14
    {GPIO_PA3, hal_ll_adc_module_num(ADC_MODULE_1), {HAL_LL_ANSELA_REG_ADDRESS, 0}, ADC1_RA3, ADC1_RA3_AN14, 1},
    #endif
    #ifdef ADC1_RB13_AN11
    {GPIO_PB13, hal_ll_adc_module_num(ADC_MODULE_1), {HAL_LL_ANSELB_REG_ADDRESS, 0}, ADC1_RB13, ADC1_RB13_AN11, 1},
    #endif
    #ifdef ADC1_RB14_AN10
    {GPIO_PB14, hal_ll_adc_module_num(ADC_MODULE_1), {HAL_LL_ANSELB_REG_ADDRESS, 0}, ADC1_RB14, ADC1_RB14_AN10, 1},
    #endif
    #ifdef ADC1_RB15_AN9
    {GPIO_PB15, hal_ll_adc_module_num(ADC_MODULE_1), {HAL_LL_ANSELB_REG_ADDRESS, 0}, ADC1_RB15, ADC1_RB15_AN9, 1},
    #endif
    #ifdef ADC1_RB4_AN15
    {GPIO_PB4, hal_ll_adc_module_num(ADC_MODULE_1), {HAL_LL_ANSELB_REG_ADDRESS, 0}, ADC1_RB4, ADC1_RB4_AN15, 1},
    #endif
    #ifdef ADC1_RA4_AN16
    {GPIO_PA4, hal_ll_adc_module_num(ADC_MODULE_1), {HAL_LL_ANSELA_REG_ADDRESS, 0}, ADC1_RA4, ADC1_RA4_AN16, 1},
    #endif
    #ifdef ADC1_RB5_AN17
    {GPIO_PB5, hal_ll_adc_module_num(ADC_MODULE_1), {HAL_LL_ANSELB_REG_ADDRESS, 0}, ADC1_RB5, ADC1_RB5_AN17, 1},
    #endif
    #ifdef ADC1_RB6_AN18
    {GPIO_PB6, hal_ll_adc_module_num(ADC_MODULE_1), {HAL_LL_ANSELB_REG_ADDRESS, 0}, ADC1_RB6, ADC1_RB6_AN18, 1},
    #endif
    #ifdef ADC1_RB7_AN19
    {GPIO_PB7, hal_ll_adc_module_num(ADC_MODULE_1), {HAL_LL_ANSELB_REG_ADDRESS, 0}, ADC1_RB7, ADC1_RB7_AN19, 1},
    #endif
    #ifdef ADC1_RB8_AN20
    {GPIO_PB8, hal_ll_adc_module_num(ADC_MODULE_1), {HAL_LL_ANSELB_REG_ADDRESS, 0}, ADC1_RB8, ADC1_RB8_AN20, 1},
    #endif
    #ifdef ADC1_RB9_AN21
    {GPIO_PB9, hal_ll_adc_module_num(ADC_MODULE_1), {HAL_LL_ANSELB_REG_ADDRESS, 0}, ADC1_RB9, ADC1_RB9_AN21, 1},
    #endif
    #ifdef ADC1_RA6_AN23
    {GPIO_PA6, hal_ll_adc_module_num(ADC_MODULE_1), {HAL_LL_ANSELA_REG_ADDRESS, 0}, ADC1_RA6, ADC1_RA6_AN23, 1},
    #endif
    #ifdef ADC1_RA7_AN22
    {GPIO_PA7, hal_ll_adc_module_num(ADC_MODULE_1), {HAL_LL_ANSELA_REG_ADDRESS, 0}, ADC1_RA7, ADC1_RA7_AN22, 1},
    #endif
    #ifdef ADC1_RC4_AN16
    {GPIO_PC4, hal_ll_adc_module_num(ADC_MODULE_1), {HAL_LL_ANSELC_REG_ADDRESS, 0}, ADC1_RC4, ADC1_RC4_AN16, 1},
    #endif
    #ifdef ADC1_RG6_AN17
    {GPIO_PG6, hal_ll_adc_module_num(ADC_MODULE_1), {HAL_LL_ANSELG_REG_ADDRESS, 0}, ADC1_RG6, ADC1_RG6_AN17, 1},
    #endif
    #ifdef ADC1_RG8_AN19
    {GPIO_PG8, hal_ll_adc_module_num(ADC_MODULE_1), {HAL_LL_ANSELG_REG_ADDRESS, 0}, ADC1_RG8, ADC1_RG8_AN19, 1},
    #endif
    #ifdef ADC1_RG9_AN20
    {GPIO_PG9, hal_ll_adc_module_num(ADC_MODULE_1), {HAL_LL_ANSELG_REG_ADDRESS, 0}, ADC1_RG9, ADC1_RG9_AN20, 1},
    #endif
    #ifdef ADC1_RB12_AN8
    {GPIO_PB12, hal_ll_adc_module_num(ADC_MODULE_1), {HAL_LL_ANSELB_REG_ADDRESS, 0}, ADC1_RB12, ADC1_RB12_AN8, 1},
    #endif
    #ifdef ADC1_RB13_AN7
    {GPIO_PB13, hal_ll_adc_module_num(ADC_MODULE_1), {HAL_LL_ANSELB_REG_ADDRESS, 0}, ADC1_RB13, ADC1_RB13_AN7, 1},
    #endif
    #ifdef ADC1_RB14_AN6
    {GPIO_PB14, hal_ll_adc_module_num(ADC_MODULE_1), {HAL_LL_ANSELB_REG_ADDRESS, 0}, ADC1_RB14, ADC1_RB14_AN6, 1},
    #endif
    #ifdef ADC1_RC0_AN10
    {GPIO_PC0, hal_ll_adc_module_num(ADC_MODULE_1), {HAL_LL_ANSELC_REG_ADDRESS, 0}, ADC1_RC0, ADC1_RC0_AN10, 1},
    #endif
    #ifdef ADC1_RC1_AN11
    {GPIO_PC1, hal_ll_adc_module_num(ADC_MODULE_1), {HAL_LL_ANSELC_REG_ADDRESS, 0}, ADC1_RC1, ADC1_RC1_AN11, 1},
    #endif
    #ifdef ADC1_RC2_AN12
    {GPIO_PC2, hal_ll_adc_module_num(ADC_MODULE_1), {HAL_LL_ANSELC_REG_ADDRESS, 0}, ADC1_RC2, ADC1_RC2_AN12, 1},
    #endif
    #ifdef ADC1_RC3_AN13
    {GPIO_PC3, hal_ll_adc_module_num(ADC_MODULE_1), {HAL_LL_ANSELC_REG_ADDRESS, 0}, ADC1_RC3, ADC1_RC3_AN13, 1},
    #endif
    #ifdef ADC1_RD0_AN43
    {GPIO_PD0, hal_ll_adc_module_num(ADC_MODULE_1), {HAL_LL_ANSELD_REG_ADDRESS, 0}, ADC1_RD0, ADC1_RD0_AN43, 1},
    #endif
    #ifdef ADC1_RD1_AN35
    {GPIO_PD1, hal_ll_adc_module_num(ADC_MODULE_1), {HAL_LL_ANSELD_REG_ADDRESS, 0}, ADC1_RD1, ADC1_RD1_AN35, 1},
    #endif
    #ifdef ADC1_RD10_AN41
    {GPIO_PD10, hal_ll_adc_module_num(ADC_MODULE_1), {HAL_LL_ANSELD_REG_ADDRESS, 0}, ADC1_RD10, ADC1_RD10_AN41, 1},
    #endif
    #ifdef ADC1_RD11_AN42
    {GPIO_PD11, hal_ll_adc_module_num(ADC_MODULE_1), {HAL_LL_ANSELD_REG_ADDRESS, 0}, ADC1_RD11, ADC1_RD11_AN42, 1},
    #endif
    #ifdef ADC1_RD2_AN25
    {GPIO_PD2, hal_ll_adc_module_num(ADC_MODULE_1), {HAL_LL_ANSELD_REG_ADDRESS, 0}, ADC1_RD2, ADC1_RD2_AN25, 1},
    #endif
    #ifdef ADC1_RD3_AN44
    {GPIO_PD3, hal_ll_adc_module_num(ADC_MODULE_1), {HAL_LL_ANSELD_REG_ADDRESS, 0}, ADC1_RD3, ADC1_RD3_AN44, 1},
    #endif
    #ifdef ADC1_RD4_AN47
    {GPIO_PD4, hal_ll_adc_module_num(ADC_MODULE_1), {HAL_LL_ANSELD_REG_ADDRESS, 0}, ADC1_RD4, ADC1_RD4_AN47, 1},
    #endif
    #ifdef ADC1_RD5_AN48
    {GPIO_PD5, hal_ll_adc_module_num(ADC_MODULE_1), {HAL_LL_ANSELD_REG_ADDRESS, 0}, ADC1_RD5, ADC1_RD5_AN48, 1},
    #endif
    #ifdef ADC1_RD6_AN34
    {GPIO_PD6, hal_ll_adc_module_num(ADC_MODULE_1), {HAL_LL_ANSELD_REG_ADDRESS, 0}, ADC1_RD6, ADC1_RD6_AN34, 1},
    #endif
    #ifdef ADC1_RD7_AN20
    {GPIO_PD7, hal_ll_adc_module_num(ADC_MODULE_1), {HAL_LL_ANSELD_REG_ADDRESS, 0}, ADC1_RD7, ADC1_RD7_AN20, 1},
    #endif
    #ifdef ADC1_RD8_AN40
    {GPIO_PD8, hal_ll_adc_module_num(ADC_MODULE_1), {HAL_LL_ANSELD_REG_ADDRESS, 0}, ADC1_RD8, ADC1_RD8_AN40, 1},
    #endif
    #ifdef ADC1_RD9_AN24
    {GPIO_PD9, hal_ll_adc_module_num(ADC_MODULE_1), {HAL_LL_ANSELD_REG_ADDRESS, 0}, ADC1_RD9, ADC1_RD9_AN24, 1},
    #endif
    #ifdef ADC1_RF3_AN30
    {GPIO_PF3, hal_ll_adc_module_num(ADC_MODULE_1), {HAL_LL_ANSELF_REG_ADDRESS, 0}, ADC1_RF3, ADC1_RF3_AN30, 1},
    #endif
    #ifdef ADC1_RF4_AN11
    {GPIO_PF4, hal_ll_adc_module_num(ADC_MODULE_1), {HAL_LL_ANSELF_REG_ADDRESS, 0}, ADC1_RF4, ADC1_RF4_AN11, 1},
    #endif
    #ifdef ADC1_RF5_AN10
    {GPIO_PF5, hal_ll_adc_module_num(ADC_MODULE_1), {HAL_LL_ANSELF_REG_ADDRESS, 0}, ADC1_RF5, ADC1_RF5_AN10, 1},
    #endif
    #ifdef ADC1_RG9_AN49
    {GPIO_PG9, hal_ll_adc_module_num(ADC_MODULE_1), {HAL_LL_ANSELG_REG_ADDRESS, 0}, ADC1_RG9, ADC1_RG9_AN49, 1},
    #endif
    #ifdef ADC1_RA1_AN26
    {GPIO_PA1, hal_ll_adc_module_num(ADC_MODULE_1), {HAL_LL_ANSELA_REG_ADDRESS, 0}, ADC1_RA1, ADC1_RA1_AN26, 1},
    #endif
    #ifdef ADC1_RA14_AN38
    {GPIO_PA14, hal_ll_adc_module_num(ADC_MODULE_1), {HAL_LL_ANSELA_REG_ADDRESS, 0}, ADC1_RA14, ADC1_RA14_AN38, 1},
    #endif
    #ifdef ADC1_RA15_AN39
    {GPIO_PA15, hal_ll_adc_module_num(ADC_MODULE_1), {HAL_LL_ANSELA_REG_ADDRESS, 0}, ADC1_RA15, ADC1_RA15_AN39, 1},
    #endif
    #ifdef ADC1_RA4_AN36
    {GPIO_PA4, hal_ll_adc_module_num(ADC_MODULE_1), {HAL_LL_ANSELA_REG_ADDRESS, 0}, ADC1_RA4, ADC1_RA4_AN36, 1},
    #endif
    #ifdef ADC1_RA5_AN37
    {GPIO_PA5, hal_ll_adc_module_num(ADC_MODULE_1), {HAL_LL_ANSELA_REG_ADDRESS, 0}, ADC1_RA5, ADC1_RA5_AN37, 1},
    #endif
    #ifdef ADC1_RC3_AN9
    {GPIO_PC3, hal_ll_adc_module_num(ADC_MODULE_1), {HAL_LL_ANSELC_REG_ADDRESS, 0}, ADC1_RC3, ADC1_RC3_AN9, 1},
    #endif
    #ifdef ADC1_RD12_AN45
    {GPIO_PD12, hal_ll_adc_module_num(ADC_MODULE_1), {HAL_LL_ANSELD_REG_ADDRESS, 0}, ADC1_RD12, ADC1_RD12_AN45, 1},
    #endif
    #ifdef ADC1_RD13_AN46
    {GPIO_PD13, hal_ll_adc_module_num(ADC_MODULE_1), {HAL_LL_ANSELD_REG_ADDRESS, 0}, ADC1_RD13, ADC1_RD13_AN46, 1},
    #endif
    #ifdef ADC1_RD14_AN28
    {GPIO_PD14, hal_ll_adc_module_num(ADC_MODULE_1), {HAL_LL_ANSELD_REG_ADDRESS, 0}, ADC1_RD14, ADC1_RD14_AN28, 1},
    #endif
    #ifdef ADC1_RD15_AN29
    {GPIO_PD15, hal_ll_adc_module_num(ADC_MODULE_1), {HAL_LL_ANSELD_REG_ADDRESS, 0}, ADC1_RD15, ADC1_RD15_AN29, 1},
    #endif
    #ifdef ADC1_RF13_AN27
    {GPIO_PF13, hal_ll_adc_module_num(ADC_MODULE_1), {HAL_LL_ANSELF_REG_ADDRESS, 0}, ADC1_RF13, ADC1_RF13_AN27, 1},
    #endif
    #ifdef ADC1_RF2_AN31
    {GPIO_PF2, hal_ll_adc_module_num(ADC_MODULE_1), {HAL_LL_ANSELF_REG_ADDRESS, 0}, ADC1_RF2, ADC1_RF2_AN31, 1},
    #endif
    #ifdef ADC1_RF8_AN32
    {GPIO_PF8, hal_ll_adc_module_num(ADC_MODULE_1), {HAL_LL_ANSELF_REG_ADDRESS, 0}, ADC1_RF8, ADC1_RF8_AN32, 1},
    #endif
    #ifdef ADC1_RG15_AN33
    {GPIO_PG15, hal_ll_adc_module_num(ADC_MODULE_1), {HAL_LL_ANSELG_REG_ADDRESS, 0}, ADC1_RG15, ADC1_RG15_AN33, 1},
    #endif
    #ifdef ADC1_RC3_AN12
    {GPIO_PC3, hal_ll_adc_module_num(ADC_MODULE_1), {HAL_LL_ANSELC_REG_ADDRESS, 0}, ADC1_RC3, ADC1_RC3_AN12, 1},
    #endif
    #endif
    // EOF list

    // BEGIN ANS
    #ifdef _ADC_ANS_
    #ifdef ADC_RB0_AN0
    {GPIO_PB0, hal_ll_adc_module_num(ADC_MODULE), {HAL_LL_ANSB_REG_ADDRESS, 0}, ADC_RB0, ADC_RB0_AN0, 1},
    #endif
    #ifdef ADC_RB1_AN1
    {GPIO_PB1, hal_ll_adc_module_num(ADC_MODULE), {HAL_LL_ANSB_REG_ADDRESS, 0}, ADC_RB1, ADC_RB1_AN1, 1},
    #endif
    #ifdef ADC_RB2_AN2
    {GPIO_PB2, hal_ll_adc_module_num(ADC_MODULE), {HAL_LL_ANSB_REG_ADDRESS, 0}, ADC_RB2, ADC_RB2_AN2, 1},
    #endif
    #ifdef ADC_RB3_AN3
    {GPIO_PB3, hal_ll_adc_module_num(ADC_MODULE), {HAL_LL_ANSB_REG_ADDRESS, 0}, ADC_RB3, ADC_RB3_AN3, 1},
    #endif
    #ifdef ADC_RB4_AN4
    {GPIO_PB4, hal_ll_adc_module_num(ADC_MODULE), {HAL_LL_ANSB_REG_ADDRESS, 0}, ADC_RB4, ADC_RB4_AN4, 1},
    #endif
    #ifdef ADC_RB5_AN5
    {GPIO_PB5, hal_ll_adc_module_num(ADC_MODULE), {HAL_LL_ANSB_REG_ADDRESS, 0}, ADC_RB5, ADC_RB5_AN5, 1},
    #endif
    #ifdef ADC_RB6_AN6
    {GPIO_PB6, hal_ll_adc_module_num(ADC_MODULE), {HAL_LL_ANSB_REG_ADDRESS, 0}, ADC_RB6, ADC_RB6_AN6, 1},
    #endif
    #ifdef ADC_RB7_AN7
    {GPIO_PB7, hal_ll_adc_module_num(ADC_MODULE), {HAL_LL_ANSB_REG_ADDRESS, 0}, ADC_RB7, ADC_RB7_AN7, 1},
    #endif
    #ifdef ADC_RB8_AN8
    {GPIO_PB8, hal_ll_adc_module_num(ADC_MODULE), {HAL_LL_ANSB_REG_ADDRESS, 0}, ADC_RB8, ADC_RB8_AN8, 1},
    #endif
    #ifdef ADC_RB9_AN9
    {GPIO_PB9, hal_ll_adc_module_num(ADC_MODULE), {HAL_LL_ANSB_REG_ADDRESS, 0}, ADC_RB9, ADC_RB9_AN9, 1},
    #endif
    #ifdef ADC_RB10_AN10
    {GPIO_PB10, hal_ll_adc_module_num(ADC_MODULE), {HAL_LL_ANSB_REG_ADDRESS, 0}, ADC_RB10, ADC_RB10_AN10, 1},
    #endif
    #ifdef ADC_RB11_AN11
    {GPIO_PB11, hal_ll_adc_module_num(ADC_MODULE), {HAL_LL_ANSB_REG_ADDRESS, 0}, ADC_RB11, ADC_RB11_AN11, 1},
    #endif
    #ifdef ADC_RB12_AN12
    {GPIO_PB12, hal_ll_adc_module_num(ADC_MODULE), {HAL_LL_ANSB_REG_ADDRESS, 0}, ADC_RB12, ADC_RB12_AN12, 1},
    #endif
    #ifdef ADC_RB13_AN13
    {GPIO_PB13, hal_ll_adc_module_num(ADC_MODULE), {HAL_LL_ANSB_REG_ADDRESS, 0}, ADC_RB13, ADC_RB13_AN13, 1},
    #endif
    #ifdef ADC_RB14_AN14
    {GPIO_PB14, hal_ll_adc_module_num(ADC_MODULE), {HAL_LL_ANSB_REG_ADDRESS, 0}, ADC_RB14, ADC_RB14_AN14, 1},
    #endif
    #ifdef ADC_RB15_AN15
    {GPIO_PB15, hal_ll_adc_module_num(ADC_MODULE), {HAL_LL_ANSB_REG_ADDRESS, 0}, ADC_RB15, ADC_RB15_AN15, 1},
    #endif
    #ifdef ADC1_RA0_AN0
    {GPIO_PA0, hal_ll_adc_module_num(ADC_MODULE_1), {HAL_LL_ANSA_REG_ADDRESS, 0}, ADC1_RA0, ADC1_RA0_AN0, 1},
    #endif
    #ifdef ADC1_RA1_AN1
    {GPIO_PA1, hal_ll_adc_module_num(ADC_MODULE_1), {HAL_LL_ANSA_REG_ADDRESS, 0}, ADC1_RA1, ADC1_RA1_AN1, 1},
    #endif
    #ifdef ADC1_RA2_AN32
    {GPIO_PA2, hal_ll_adc_module_num(ADC_MODULE_1), {HAL_LL_ANSA_REG_ADDRESS, 0}, ADC1_RA2, ADC1_RA2_AN32, 1},
    #endif
    #ifdef ADC1_RA4_AN24
    {GPIO_PA4, hal_ll_adc_module_num(ADC_MODULE_1), {HAL_LL_ANSA_REG_ADDRESS, 0}, ADC1_RA4, ADC1_RA4_AN24, 1},
    #endif
    #ifdef ADC1_RA9_AN28
    {GPIO_PA9, hal_ll_adc_module_num(ADC_MODULE_1), {HAL_LL_ANSA_REG_ADDRESS, 0}, ADC1_RA9, ADC1_RA9_AN28, 1},
    #endif
    #ifdef ADC1_RB0_AN2
    {GPIO_PB0, hal_ll_adc_module_num(ADC_MODULE_1), {HAL_LL_ANSB_REG_ADDRESS, 0}, ADC1_RB0, ADC1_RB0_AN2, 1},
    #endif
    #ifdef ADC1_RB1_AN3
    {GPIO_PB1, hal_ll_adc_module_num(ADC_MODULE_1), {HAL_LL_ANSB_REG_ADDRESS, 0}, ADC1_RB1, ADC1_RB1_AN3, 1},
    #endif
    #ifdef ADC1_RB2_AN4
    {GPIO_PB2, hal_ll_adc_module_num(ADC_MODULE_1), {HAL_LL_ANSB_REG_ADDRESS, 0}, ADC1_RB2, ADC1_RB2_AN4, 1},
    #endif
    #ifdef ADC1_RB3_AN5
    {GPIO_PB3, hal_ll_adc_module_num(ADC_MODULE_1), {HAL_LL_ANSB_REG_ADDRESS, 0}, ADC1_RB3, ADC1_RB3_AN5, 1},
    #endif
    #ifdef ADC1_RB7_AN25
    {GPIO_PB7, hal_ll_adc_module_num(ADC_MODULE_1), {HAL_LL_ANSB_REG_ADDRESS, 0}, ADC1_RB7, ADC1_RB7_AN25, 1},
    #endif
    #ifdef ADC1_RB8_AN26
    {GPIO_PB8, hal_ll_adc_module_num(ADC_MODULE_1), {HAL_LL_ANSB_REG_ADDRESS, 0}, ADC1_RB8, ADC1_RB8_AN26, 1},
    #endif
    #ifdef ADC1_RB9_AN27
    {GPIO_PB9, hal_ll_adc_module_num(ADC_MODULE_1), {HAL_LL_ANSB_REG_ADDRESS, 0}, ADC1_RB9, ADC1_RB9_AN27, 1},
    #endif
    #ifdef ADC1_RC0_AN6
    {GPIO_PC0, hal_ll_adc_module_num(ADC_MODULE_1), {HAL_LL_ANSC_REG_ADDRESS, 0}, ADC1_RC0, ADC1_RC0_AN6, 1},
    #endif
    #ifdef ADC1_RC1_AN7
    {GPIO_PC1, hal_ll_adc_module_num(ADC_MODULE_1), {HAL_LL_ANSC_REG_ADDRESS, 0}, ADC1_RC1, ADC1_RC1_AN7, 1},
    #endif
    #ifdef ADC1_RC2_AN8
    {GPIO_PC2, hal_ll_adc_module_num(ADC_MODULE_1), {HAL_LL_ANSC_REG_ADDRESS, 0}, ADC1_RC2, ADC1_RC2_AN8, 1},
    #endif
    #ifdef ADC1_RC3_AN29
    {GPIO_PC3, hal_ll_adc_module_num(ADC_MODULE_1), {HAL_LL_ANSC_REG_ADDRESS, 0}, ADC1_RC3, ADC1_RC3_AN29, 1},
    #endif
    #ifdef ADC1_RC4_AN30
    {GPIO_PC4, hal_ll_adc_module_num(ADC_MODULE_1), {HAL_LL_ANSC_REG_ADDRESS, 0}, ADC1_RC4, ADC1_RC4_AN30, 1},
    #endif
    #ifdef ADC1_RC5_AN31
    {GPIO_PC5, hal_ll_adc_module_num(ADC_MODULE_1), {HAL_LL_ANSC_REG_ADDRESS, 0}, ADC1_RC5, ADC1_RC5_AN31, 1},
    #endif
    #ifdef ADC2_RA0_AN0
    {GPIO_PA0, hal_ll_adc_module_num(ADC_MODULE_2), {HAL_LL_ANSA_REG_ADDRESS, 0}, ADC2_RA0, ADC2_RA0_AN0, 1},
    #endif
    #ifdef ADC2_RA1_AN1
    {GPIO_PA1, hal_ll_adc_module_num(ADC_MODULE_2), {HAL_LL_ANSA_REG_ADDRESS, 0}, ADC2_RA1, ADC2_RA1_AN1, 1},
    #endif
    #ifdef ADC2_RA4_AN24
    {GPIO_PA4, hal_ll_adc_module_num(ADC_MODULE_2), {HAL_LL_ANSA_REG_ADDRESS, 0}, ADC2_RA4, ADC2_RA4_AN24, 1},
    #endif
    #ifdef ADC2_RA9_AN28
    {GPIO_PA9, hal_ll_adc_module_num(ADC_MODULE_2), {HAL_LL_ANSA_REG_ADDRESS, 0}, ADC2_RA9, ADC2_RA9_AN28, 1},
    #endif
    #ifdef ADC2_RB0_AN2
    {GPIO_PB0, hal_ll_adc_module_num(ADC_MODULE_2), {HAL_LL_ANSB_REG_ADDRESS, 0}, ADC2_RB0, ADC2_RB0_AN2, 1},
    #endif
    #ifdef ADC2_RB1_AN3
    {GPIO_PB1, hal_ll_adc_module_num(ADC_MODULE_2), {HAL_LL_ANSB_REG_ADDRESS, 0}, ADC2_RB1, ADC2_RB1_AN3, 1},
    #endif
    #ifdef ADC2_RB2_AN4
    {GPIO_PB2, hal_ll_adc_module_num(ADC_MODULE_2), {HAL_LL_ANSB_REG_ADDRESS, 0}, ADC2_RB2, ADC2_RB2_AN4, 1},
    #endif
    #ifdef ADC2_RB3_AN5
    {GPIO_PB3, hal_ll_adc_module_num(ADC_MODULE_2), {HAL_LL_ANSB_REG_ADDRESS, 0}, ADC2_RB3, ADC2_RB3_AN5, 1},
    #endif
    #ifdef ADC2_RB7_AN25
    {GPIO_PB7, hal_ll_adc_module_num(ADC_MODULE_2), {HAL_LL_ANSB_REG_ADDRESS, 0}, ADC2_RB7, ADC2_RB7_AN25, 1},
    #endif
    #ifdef ADC2_RB8_AN26
    {GPIO_PB8, hal_ll_adc_module_num(ADC_MODULE_2), {HAL_LL_ANSB_REG_ADDRESS, 0}, ADC2_RB8, ADC2_RB8_AN26, 1},
    #endif
    #ifdef ADC2_RB9_AN27
    {GPIO_PB9, hal_ll_adc_module_num(ADC_MODULE_2), {HAL_LL_ANSB_REG_ADDRESS, 0}, ADC2_RB9, ADC2_RB9_AN27, 1},
    #endif
    #ifdef ADC2_RC0_AN6
    {GPIO_PC0, hal_ll_adc_module_num(ADC_MODULE_2), {HAL_LL_ANSC_REG_ADDRESS, 0}, ADC2_RC0, ADC2_RC0_AN6, 1},
    #endif
    #ifdef ADC2_RC1_AN7
    {GPIO_PC1, hal_ll_adc_module_num(ADC_MODULE_2), {HAL_LL_ANSC_REG_ADDRESS, 0}, ADC2_RC1, ADC2_RC1_AN7, 1},
    #endif
    #ifdef ADC2_RC2_AN8
    {GPIO_PC2, hal_ll_adc_module_num(ADC_MODULE_2), {HAL_LL_ANSC_REG_ADDRESS, 0}, ADC2_RC2, ADC2_RC2_AN8, 1},
    #endif
    #ifdef ADC2_RC3_AN29
    {GPIO_PC3, hal_ll_adc_module_num(ADC_MODULE_2), {HAL_LL_ANSC_REG_ADDRESS, 0}, ADC2_RC3, ADC2_RC3_AN29, 1},
    #endif
    #ifdef ADC2_RC4_AN30
    {GPIO_PC4, hal_ll_adc_module_num(ADC_MODULE_2), {HAL_LL_ANSC_REG_ADDRESS, 0}, ADC2_RC4, ADC2_RC4_AN30, 1},
    #endif
    #ifdef ADC2_RC5_AN31
    {GPIO_PC5, hal_ll_adc_module_num(ADC_MODULE_2), {HAL_LL_ANSC_REG_ADDRESS, 0}, ADC2_RC5, ADC2_RC5_AN31, 1},
    #endif
    #ifdef ADC1_RA11_AN9
    {GPIO_PA11, hal_ll_adc_module_num(ADC_MODULE_1), {HAL_LL_ANSA_REG_ADDRESS, 0}, ADC1_RA11, ADC1_RA11_AN9, 1},
    #endif
    #ifdef ADC1_RA12_AN10
    {GPIO_PA12, hal_ll_adc_module_num(ADC_MODULE_1), {HAL_LL_ANSA_REG_ADDRESS, 0}, ADC1_RA12, ADC1_RA12_AN10, 1},
    #endif
    #ifdef ADC1_RC10_AN48
    {GPIO_PC10, hal_ll_adc_module_num(ADC_MODULE_1), {HAL_LL_ANSC_REG_ADDRESS, 0}, ADC1_RC10, ADC1_RC10_AN48, 1},
    #endif
    #ifdef ADC1_RC11_AN11
    {GPIO_PC11, hal_ll_adc_module_num(ADC_MODULE_1), {HAL_LL_ANSC_REG_ADDRESS, 0}, ADC1_RC11, ADC1_RC11_AN11, 1},
    #endif
    #ifdef ADC1_RC12_AN49
    {GPIO_PC12, hal_ll_adc_module_num(ADC_MODULE_1), {HAL_LL_ANSC_REG_ADDRESS, 0}, ADC1_RC12, ADC1_RC12_AN49, 1},
    #endif
    #ifdef ADC1_RE12_AN12
    {GPIO_PE12, hal_ll_adc_module_num(ADC_MODULE_1), {HAL_LL_ANSE_REG_ADDRESS, 0}, ADC1_RE12, ADC1_RE12_AN12, 1},
    #endif
    #ifdef ADC1_RE13_AN13
    {GPIO_PE13, hal_ll_adc_module_num(ADC_MODULE_1), {HAL_LL_ANSE_REG_ADDRESS, 0}, ADC1_RE13, ADC1_RE13_AN13, 1},
    #endif
    #ifdef ADC1_RE14_AN14
    {GPIO_PE14, hal_ll_adc_module_num(ADC_MODULE_1), {HAL_LL_ANSE_REG_ADDRESS, 0}, ADC1_RE14, ADC1_RE14_AN14, 1},
    #endif
    #ifdef ADC1_RE15_AN15
    {GPIO_PE15, hal_ll_adc_module_num(ADC_MODULE_1), {HAL_LL_ANSE_REG_ADDRESS, 0}, ADC1_RE15, ADC1_RE15_AN15, 1},
    #endif
    #ifdef ADC1_RG6_AN19
    {GPIO_PG6, hal_ll_adc_module_num(ADC_MODULE_1), {HAL_LL_ANSG_REG_ADDRESS, 0}, ADC1_RG6, ADC1_RG6_AN19, 1},
    #endif
    #ifdef ADC1_RG7_AN18
    {GPIO_PG7, hal_ll_adc_module_num(ADC_MODULE_1), {HAL_LL_ANSG_REG_ADDRESS, 0}, ADC1_RG7, ADC1_RG7_AN18, 1},
    #endif
    #ifdef ADC1_RG8_AN17
    {GPIO_PG8, hal_ll_adc_module_num(ADC_MODULE_1), {HAL_LL_ANSG_REG_ADDRESS, 0}, ADC1_RG8, ADC1_RG8_AN17, 1},
    #endif
    #ifdef ADC1_RG9_AN16
    {GPIO_PG9, hal_ll_adc_module_num(ADC_MODULE_1), {HAL_LL_ANSG_REG_ADDRESS, 0}, ADC1_RG9, ADC1_RG9_AN16, 1},
    #endif
    #ifdef ADC2_RA11_AN9
    {GPIO_PA11, hal_ll_adc_module_num(ADC_MODULE_2), {HAL_LL_ANSA_REG_ADDRESS, 0}, ADC2_RA11, ADC2_RA11_AN9, 1},
    #endif
    #ifdef ADC2_RA12_AN10
    {GPIO_PA12, hal_ll_adc_module_num(ADC_MODULE_2), {HAL_LL_ANSA_REG_ADDRESS, 0}, ADC2_RA12, ADC2_RA12_AN10, 1},
    #endif
    #ifdef ADC2_RC11_AN11
    {GPIO_PC11, hal_ll_adc_module_num(ADC_MODULE_2), {HAL_LL_ANSC_REG_ADDRESS, 0}, ADC2_RC11, ADC2_RC11_AN11, 1},
    #endif
    #ifdef ADC2_RE12_AN12
    {GPIO_PE12, hal_ll_adc_module_num(ADC_MODULE_2), {HAL_LL_ANSE_REG_ADDRESS, 0}, ADC2_RE12, ADC2_RE12_AN12, 1},
    #endif
    #ifdef ADC2_RE13_AN13
    {GPIO_PE13, hal_ll_adc_module_num(ADC_MODULE_2), {HAL_LL_ANSE_REG_ADDRESS, 0}, ADC2_RE13, ADC2_RE13_AN13, 1},
    #endif
    #ifdef ADC2_RE14_AN14
    {GPIO_PE14, hal_ll_adc_module_num(ADC_MODULE_2), {HAL_LL_ANSE_REG_ADDRESS, 0}, ADC2_RE14, ADC2_RE14_AN14, 1},
    #endif
    #ifdef ADC2_RE15_AN15
    {GPIO_PE15, hal_ll_adc_module_num(ADC_MODULE_2), {HAL_LL_ANSE_REG_ADDRESS, 0}, ADC2_RE15, ADC2_RE15_AN15, 1},
    #endif
    #ifdef ADC2_RG6_AN19
    {GPIO_PG6, hal_ll_adc_module_num(ADC_MODULE_2), {HAL_LL_ANSG_REG_ADDRESS, 0}, ADC2_RG6, ADC2_RG6_AN19, 1},
    #endif
    #ifdef ADC2_RG7_AN18
    {GPIO_PG7, hal_ll_adc_module_num(ADC_MODULE_2), {HAL_LL_ANSG_REG_ADDRESS, 0}, ADC2_RG7, ADC2_RG7_AN18, 1},
    #endif
    #ifdef ADC2_RG8_AN17
    {GPIO_PG8, hal_ll_adc_module_num(ADC_MODULE_2), {HAL_LL_ANSG_REG_ADDRESS, 0}, ADC2_RG8, ADC2_RG8_AN17, 1},
    #endif
    #ifdef ADC2_RG9_AN16
    {GPIO_PG9, hal_ll_adc_module_num(ADC_MODULE_2), {HAL_LL_ANSG_REG_ADDRESS, 0}, ADC2_RG9, ADC2_RG9_AN16, 1},
    #endif
    #ifdef ADC1_RA14_AN46
    {GPIO_PA14, hal_ll_adc_module_num(ADC_MODULE_1), {HAL_LL_ANSA_REG_ADDRESS, 0}, ADC1_RA14, ADC1_RA14_AN46, 1},
    #endif
    #ifdef ADC1_RA15_AN47
    {GPIO_PA15, hal_ll_adc_module_num(ADC_MODULE_1), {HAL_LL_ANSA_REG_ADDRESS, 0}, ADC1_RA15, ADC1_RA15_AN47, 1},
    #endif
    #ifdef ADC1_RD14_AN38
    {GPIO_PD14, hal_ll_adc_module_num(ADC_MODULE_1), {HAL_LL_ANSD_REG_ADDRESS, 0}, ADC1_RD14, ADC1_RD14_AN38, 1},
    #endif
    #ifdef ADC1_RD15_AN39
    {GPIO_PD15, hal_ll_adc_module_num(ADC_MODULE_1), {HAL_LL_ANSD_REG_ADDRESS, 0}, ADC1_RD15, ADC1_RD15_AN39, 1},
    #endif
    #ifdef ADC1_RE0_AN40
    {GPIO_PE0, hal_ll_adc_module_num(ADC_MODULE_1), {HAL_LL_ANSE_REG_ADDRESS, 0}, ADC1_RE0, ADC1_RE0_AN40, 1},
    #endif
    #ifdef ADC1_RE1_AN41
    {GPIO_PE1, hal_ll_adc_module_num(ADC_MODULE_1), {HAL_LL_ANSE_REG_ADDRESS, 0}, ADC1_RE1, ADC1_RE1_AN41, 1},
    #endif
    #ifdef ADC1_RE8_AN21
    {GPIO_PE8, hal_ll_adc_module_num(ADC_MODULE_1), {HAL_LL_ANSE_REG_ADDRESS, 0}, ADC1_RE8, ADC1_RE8_AN21, 1},
    #endif
    #ifdef ADC1_RE9_AN20
    {GPIO_PE9, hal_ll_adc_module_num(ADC_MODULE_1), {HAL_LL_ANSE_REG_ADDRESS, 0}, ADC1_RE9, ADC1_RE9_AN20, 1},
    #endif
    #ifdef ADC1_RF10_AN34
    {GPIO_PF10, hal_ll_adc_module_num(ADC_MODULE_1), {HAL_LL_ANSF_REG_ADDRESS, 0}, ADC1_RF10, ADC1_RF10_AN34, 1},
    #endif
    #ifdef ADC1_RF12_AN37
    {GPIO_PF12, hal_ll_adc_module_num(ADC_MODULE_1), {HAL_LL_ANSF_REG_ADDRESS, 0}, ADC1_RF12, ADC1_RF12_AN37, 1},
    #endif
    #ifdef ADC1_RF13_AN36
    {GPIO_PF13, hal_ll_adc_module_num(ADC_MODULE_1), {HAL_LL_ANSF_REG_ADDRESS, 0}, ADC1_RF13, ADC1_RF13_AN36, 1},
    #endif
    #ifdef ADC1_RF4_AN44
    {GPIO_PF4, hal_ll_adc_module_num(ADC_MODULE_1), {HAL_LL_ANSF_REG_ADDRESS, 0}, ADC1_RF4, ADC1_RF4_AN44, 1},
    #endif
    #ifdef ADC1_RF5_AN45
    {GPIO_PF5, hal_ll_adc_module_num(ADC_MODULE_1), {HAL_LL_ANSF_REG_ADDRESS, 0}, ADC1_RF5, ADC1_RF5_AN45, 1},
    #endif
    #ifdef ADC1_RF9_AN33
    {GPIO_PF9, hal_ll_adc_module_num(ADC_MODULE_1), {HAL_LL_ANSF_REG_ADDRESS, 0}, ADC1_RF9, ADC1_RF9_AN33, 1},
    #endif
    #ifdef ADC1_RG10_AN22
    {GPIO_PG10, hal_ll_adc_module_num(ADC_MODULE_1), {HAL_LL_ANSG_REG_ADDRESS, 0}, ADC1_RG10, ADC1_RG10_AN22, 1},
    #endif
    #ifdef ADC1_RG11_AN35
    {GPIO_PG11, hal_ll_adc_module_num(ADC_MODULE_1), {HAL_LL_ANSG_REG_ADDRESS, 0}, ADC1_RG11, ADC1_RG11_AN35, 1},
    #endif
    #ifdef ADC1_RG15_AN23
    {GPIO_PG15, hal_ll_adc_module_num(ADC_MODULE_1), {HAL_LL_ANSG_REG_ADDRESS, 0}, ADC1_RG15, ADC1_RG15_AN23, 1},
    #endif
    #ifdef ADC1_RG2_AN42
    {GPIO_PG2, hal_ll_adc_module_num(ADC_MODULE_1), {HAL_LL_ANSG_REG_ADDRESS, 0}, ADC1_RG2, ADC1_RG2_AN42, 1},
    #endif
    #ifdef ADC1_RG3_AN43
    {GPIO_PG3, hal_ll_adc_module_num(ADC_MODULE_1), {HAL_LL_ANSG_REG_ADDRESS, 0}, ADC1_RG3, ADC1_RG3_AN43, 1},
    #endif
    #ifdef ADC2_RE8_AN21
    {GPIO_PE8, hal_ll_adc_module_num(ADC_MODULE_2), {HAL_LL_ANSE_REG_ADDRESS, 0}, ADC2_RE8, ADC2_RE8_AN21, 1},
    #endif
    #ifdef ADC2_RE9_AN20
    {GPIO_PE9, hal_ll_adc_module_num(ADC_MODULE_2), {HAL_LL_ANSE_REG_ADDRESS, 0}, ADC2_RE9, ADC2_RE9_AN20, 1},
    #endif
    #ifdef ADC2_RG10_AN22
    {GPIO_PG10, hal_ll_adc_module_num(ADC_MODULE_2), {HAL_LL_ANSG_REG_ADDRESS, 0}, ADC2_RG10, ADC2_RG10_AN22, 1},
    #endif
    #ifdef ADC2_RG15_AN23
    {GPIO_PG15, hal_ll_adc_module_num(ADC_MODULE_2), {HAL_LL_ANSG_REG_ADDRESS, 0}, ADC2_RG15, ADC2_RG15_AN23, 1},
    #endif
    #ifdef ADC1_RA2_AN2
    {GPIO_PA2, hal_ll_adc_module_num(ADC_MODULE_1), {HAL_LL_ANSA_REG_ADDRESS, 0}, ADC1_RA2, ADC1_RA2_AN2, 1},
    #endif
    #ifdef ADC1_RB0_AN3
    {GPIO_PB0, hal_ll_adc_module_num(ADC_MODULE_1), {HAL_LL_ANSB_REG_ADDRESS, 0}, ADC1_RB0, ADC1_RB0_AN3, 1},
    #endif
    #ifdef ADC1_RB1_AN6
    {GPIO_PB1, hal_ll_adc_module_num(ADC_MODULE_1), {HAL_LL_ANSB_REG_ADDRESS, 0}, ADC1_RB1, ADC1_RB1_AN6, 1},
    #endif
    #ifdef ADC1_RB2_AN7
    {GPIO_PB2, hal_ll_adc_module_num(ADC_MODULE_1), {HAL_LL_ANSB_REG_ADDRESS, 0}, ADC1_RB2, ADC1_RB2_AN7, 1},
    #endif
    #ifdef ADC1_RB3_AN18
    {GPIO_PB3, hal_ll_adc_module_num(ADC_MODULE_1), {HAL_LL_ANSB_REG_ADDRESS, 0}, ADC1_RB3, ADC1_RB3_AN18, 1},
    #endif
    #ifdef ADC1_RB5_AN19
    {GPIO_PB5, hal_ll_adc_module_num(ADC_MODULE_1), {HAL_LL_ANSB_REG_ADDRESS, 0}, ADC1_RB5, ADC1_RB5_AN19, 1},
    #endif
    #ifdef ADC1_RB6_AN20
    {GPIO_PB6, hal_ll_adc_module_num(ADC_MODULE_1), {HAL_LL_ANSB_REG_ADDRESS, 0}, ADC1_RB6, ADC1_RB6_AN20, 1},
    #endif
    #ifdef ADC1_RB7_AN21
    {GPIO_PB7, hal_ll_adc_module_num(ADC_MODULE_1), {HAL_LL_ANSB_REG_ADDRESS, 0}, ADC1_RB7, ADC1_RB7_AN21, 1},
    #endif
    #ifdef ADC1_RB9_AN4
    {GPIO_PB9, hal_ll_adc_module_num(ADC_MODULE_1), {HAL_LL_ANSB_REG_ADDRESS, 0}, ADC1_RB9, ADC1_RB9_AN4, 1},
    #endif
    #ifdef ADC1_RC1_AN8
    {GPIO_PC1, hal_ll_adc_module_num(ADC_MODULE_1), {HAL_LL_ANSC_REG_ADDRESS, 0}, ADC1_RC1, ADC1_RC1_AN8, 1},
    #endif
    #ifdef ADC1_RC10_AN10
    {GPIO_PC10, hal_ll_adc_module_num(ADC_MODULE_1), {HAL_LL_ANSC_REG_ADDRESS, 0}, ADC1_RC10, ADC1_RC10_AN10, 1},
    #endif
    #ifdef ADC1_RC12_AN14
    {GPIO_PC12, hal_ll_adc_module_num(ADC_MODULE_1), {HAL_LL_ANSC_REG_ADDRESS, 0}, ADC1_RC12, ADC1_RC12_AN14, 1},
    #endif
    #ifdef ADC1_RC2_AN9
    {GPIO_PC2, hal_ll_adc_module_num(ADC_MODULE_1), {HAL_LL_ANSC_REG_ADDRESS, 0}, ADC1_RC2, ADC1_RC2_AN9, 1},
    #endif
    #ifdef ADC1_RC6_AN17
    {GPIO_PC6, hal_ll_adc_module_num(ADC_MODULE_1), {HAL_LL_ANSC_REG_ADDRESS, 0}, ADC1_RC6, ADC1_RC6_AN17, 1},
    #endif
    #ifdef ADC1_RC9_AN11
    {GPIO_PC9, hal_ll_adc_module_num(ADC_MODULE_1), {HAL_LL_ANSC_REG_ADDRESS, 0}, ADC1_RC9, ADC1_RC9_AN11, 1},
    #endif
    #ifdef ADC1_RD13_AN13
    {GPIO_PD13, hal_ll_adc_module_num(ADC_MODULE_1), {HAL_LL_ANSD_REG_ADDRESS, 0}, ADC1_RD13, ADC1_RD13_AN13, 1},
    #endif
    #ifdef ADC1_RD2_AN16
    {GPIO_PD2, hal_ll_adc_module_num(ADC_MODULE_1), {HAL_LL_ANSD_REG_ADDRESS, 0}, ADC1_RD2, ADC1_RD2_AN16, 1},
    #endif
    #ifdef ADC1_RD5_AN12
    {GPIO_PD5, hal_ll_adc_module_num(ADC_MODULE_1), {HAL_LL_ANSD_REG_ADDRESS, 0}, ADC1_RD5, ADC1_RD5_AN12, 1},
    #endif
    #ifdef ADC1_RD7_AN15
    {GPIO_PD7, hal_ll_adc_module_num(ADC_MODULE_1), {HAL_LL_ANSD_REG_ADDRESS, 0}, ADC1_RD7, ADC1_RD7_AN15, 1},
    #endif
    #ifdef ADC1_RD8_AN5
    {GPIO_PD8, hal_ll_adc_module_num(ADC_MODULE_1), {HAL_LL_ANSD_REG_ADDRESS, 0}, ADC1_RD8, ADC1_RD8_AN5, 1},
    #endif
    #ifdef ADC1_RB10_AN5
    {GPIO_PB10, hal_ll_adc_module_num(ADC_MODULE_1), {HAL_LL_ANSB_REG_ADDRESS, 0}, ADC1_RB10, ADC1_RB10_AN5, 1},
    #endif
    #ifdef ADC1_RB3_AN8
    {GPIO_PB3, hal_ll_adc_module_num(ADC_MODULE_1), {HAL_LL_ANSB_REG_ADDRESS, 0}, ADC1_RB3, ADC1_RB3_AN8, 1},
    #endif
    #ifdef ADC1_RB5_AN9
    {GPIO_PB5, hal_ll_adc_module_num(ADC_MODULE_1), {HAL_LL_ANSB_REG_ADDRESS, 0}, ADC1_RB5, ADC1_RB5_AN9, 1},
    #endif
    #ifdef ADC1_RB6_AN10
    {GPIO_PB6, hal_ll_adc_module_num(ADC_MODULE_1), {HAL_LL_ANSB_REG_ADDRESS, 0}, ADC1_RB6, ADC1_RB6_AN10, 1},
    #endif
    #ifdef ADC1_RB7_AN11
    {GPIO_PB7, hal_ll_adc_module_num(ADC_MODULE_1), {HAL_LL_ANSB_REG_ADDRESS, 0}, ADC1_RB7, ADC1_RB7_AN11, 1},
    #endif
    #ifdef ADC1_RC11_AN12
    {GPIO_PC11, hal_ll_adc_module_num(ADC_MODULE_1), {HAL_LL_ANSC_REG_ADDRESS, 0}, ADC1_RC11, ADC1_RC11_AN12, 1},
    #endif
    #ifdef ADC1_RB0_AN0
    {GPIO_PB0, hal_ll_adc_module_num(ADC_MODULE_1), {HAL_LL_ANSB_REG_ADDRESS, 0}, ADC1_RB0, ADC1_RB0_AN0, 1},
    #endif
    #ifdef ADC1_RB1_AN1
    {GPIO_PB1, hal_ll_adc_module_num(ADC_MODULE_1), {HAL_LL_ANSB_REG_ADDRESS, 0}, ADC1_RB1, ADC1_RB1_AN1, 1},
    #endif
    #ifdef ADC1_RB10_AN10
    {GPIO_PB10, hal_ll_adc_module_num(ADC_MODULE_1), {HAL_LL_ANSB_REG_ADDRESS, 0}, ADC1_RB10, ADC1_RB10_AN10, 1},
    #endif
    #ifdef ADC1_RB11_AN11
    {GPIO_PB11, hal_ll_adc_module_num(ADC_MODULE_1), {HAL_LL_ANSB_REG_ADDRESS, 0}, ADC1_RB11, ADC1_RB11_AN11, 1},
    #endif
    #ifdef ADC1_RB12_AN12
    {GPIO_PB12, hal_ll_adc_module_num(ADC_MODULE_1), {HAL_LL_ANSB_REG_ADDRESS, 0}, ADC1_RB12, ADC1_RB12_AN12, 1},
    #endif
    #ifdef ADC1_RB13_AN13
    {GPIO_PB13, hal_ll_adc_module_num(ADC_MODULE_1), {HAL_LL_ANSB_REG_ADDRESS, 0}, ADC1_RB13, ADC1_RB13_AN13, 1},
    #endif
    #ifdef ADC1_RB14_AN14
    {GPIO_PB14, hal_ll_adc_module_num(ADC_MODULE_1), {HAL_LL_ANSB_REG_ADDRESS, 0}, ADC1_RB14, ADC1_RB14_AN14, 1},
    #endif
    #ifdef ADC1_RB15_AN15
    {GPIO_PB15, hal_ll_adc_module_num(ADC_MODULE_1), {HAL_LL_ANSB_REG_ADDRESS, 0}, ADC1_RB15, ADC1_RB15_AN15, 1},
    #endif
    #ifdef ADC1_RB2_AN2
    {GPIO_PB2, hal_ll_adc_module_num(ADC_MODULE_1), {HAL_LL_ANSB_REG_ADDRESS, 0}, ADC1_RB2, ADC1_RB2_AN2, 1},
    #endif
    #ifdef ADC1_RB3_AN3
    {GPIO_PB3, hal_ll_adc_module_num(ADC_MODULE_1), {HAL_LL_ANSB_REG_ADDRESS, 0}, ADC1_RB3, ADC1_RB3_AN3, 1},
    #endif
    #ifdef ADC1_RB4_AN4
    {GPIO_PB4, hal_ll_adc_module_num(ADC_MODULE_1), {HAL_LL_ANSB_REG_ADDRESS, 0}, ADC1_RB4, ADC1_RB4_AN4, 1},
    #endif
    #ifdef ADC1_RB5_AN5
    {GPIO_PB5, hal_ll_adc_module_num(ADC_MODULE_1), {HAL_LL_ANSB_REG_ADDRESS, 0}, ADC1_RB5, ADC1_RB5_AN5, 1},
    #endif
    #ifdef ADC1_RB6_AN6
    {GPIO_PB6, hal_ll_adc_module_num(ADC_MODULE_1), {HAL_LL_ANSB_REG_ADDRESS, 0}, ADC1_RB6, ADC1_RB6_AN6, 1},
    #endif
    #ifdef ADC1_RB7_AN7
    {GPIO_PB7, hal_ll_adc_module_num(ADC_MODULE_1), {HAL_LL_ANSB_REG_ADDRESS, 0}, ADC1_RB7, ADC1_RB7_AN7, 1},
    #endif
    #ifdef ADC1_RB8_AN8
    {GPIO_PB8, hal_ll_adc_module_num(ADC_MODULE_1), {HAL_LL_ANSB_REG_ADDRESS, 0}, ADC1_RB8, ADC1_RB8_AN8, 1},
    #endif
    #ifdef ADC1_RB9_AN9
    {GPIO_PB9, hal_ll_adc_module_num(ADC_MODULE_1), {HAL_LL_ANSB_REG_ADDRESS, 0}, ADC1_RB9, ADC1_RB9_AN9, 1},
    #endif
    #ifdef ADC1_RE0_AN24
    {GPIO_PE0, hal_ll_adc_module_num(ADC_MODULE_1), {HAL_LL_ANSE_REG_ADDRESS, 0}, ADC1_RE0, ADC1_RE0_AN24, 1},
    #endif
    #ifdef ADC1_RE1_AN25
    {GPIO_PE1, hal_ll_adc_module_num(ADC_MODULE_1), {HAL_LL_ANSE_REG_ADDRESS, 0}, ADC1_RE1, ADC1_RE1_AN25, 1},
    #endif
    #ifdef ADC1_RE2_AN26
    {GPIO_PE2, hal_ll_adc_module_num(ADC_MODULE_1), {HAL_LL_ANSE_REG_ADDRESS, 0}, ADC1_RE2, ADC1_RE2_AN26, 1},
    #endif
    #ifdef ADC1_RE3_AN27
    {GPIO_PE3, hal_ll_adc_module_num(ADC_MODULE_1), {HAL_LL_ANSE_REG_ADDRESS, 0}, ADC1_RE3, ADC1_RE3_AN27, 1},
    #endif
    #ifdef ADC1_RE4_AN28
    {GPIO_PE4, hal_ll_adc_module_num(ADC_MODULE_1), {HAL_LL_ANSE_REG_ADDRESS, 0}, ADC1_RE4, ADC1_RE4_AN28, 1},
    #endif
    #ifdef ADC1_RE5_AN29
    {GPIO_PE5, hal_ll_adc_module_num(ADC_MODULE_1), {HAL_LL_ANSE_REG_ADDRESS, 0}, ADC1_RE5, ADC1_RE5_AN29, 1},
    #endif
    #ifdef ADC1_RE6_AN30
    {GPIO_PE6, hal_ll_adc_module_num(ADC_MODULE_1), {HAL_LL_ANSE_REG_ADDRESS, 0}, ADC1_RE6, ADC1_RE6_AN30, 1},
    #endif
    #ifdef ADC1_RE7_AN31
    {GPIO_PE7, hal_ll_adc_module_num(ADC_MODULE_1), {HAL_LL_ANSE_REG_ADDRESS, 0}, ADC1_RE7, ADC1_RE7_AN31, 1},
    #endif
    #ifdef ADC2_RB0_AN0
    {GPIO_PB0, hal_ll_adc_module_num(ADC_MODULE_2), {HAL_LL_ANSB_REG_ADDRESS, 0}, ADC2_RB0, ADC2_RB0_AN0, 1},
    #endif
    #ifdef ADC2_RB1_AN1
    {GPIO_PB1, hal_ll_adc_module_num(ADC_MODULE_2), {HAL_LL_ANSB_REG_ADDRESS, 0}, ADC2_RB1, ADC2_RB1_AN1, 1},
    #endif
    #ifdef ADC2_RB10_AN10
    {GPIO_PB10, hal_ll_adc_module_num(ADC_MODULE_2), {HAL_LL_ANSB_REG_ADDRESS, 0}, ADC2_RB10, ADC2_RB10_AN10, 1},
    #endif
    #ifdef ADC2_RB11_AN11
    {GPIO_PB11, hal_ll_adc_module_num(ADC_MODULE_2), {HAL_LL_ANSB_REG_ADDRESS, 0}, ADC2_RB11, ADC2_RB11_AN11, 1},
    #endif
    #ifdef ADC2_RB12_AN12
    {GPIO_PB12, hal_ll_adc_module_num(ADC_MODULE_2), {HAL_LL_ANSB_REG_ADDRESS, 0}, ADC2_RB12, ADC2_RB12_AN12, 1},
    #endif
    #ifdef ADC2_RB13_AN13
    {GPIO_PB13, hal_ll_adc_module_num(ADC_MODULE_2), {HAL_LL_ANSB_REG_ADDRESS, 0}, ADC2_RB13, ADC2_RB13_AN13, 1},
    #endif
    #ifdef ADC2_RB14_AN14
    {GPIO_PB14, hal_ll_adc_module_num(ADC_MODULE_2), {HAL_LL_ANSB_REG_ADDRESS, 0}, ADC2_RB14, ADC2_RB14_AN14, 1},
    #endif
    #ifdef ADC2_RB15_AN15
    {GPIO_PB15, hal_ll_adc_module_num(ADC_MODULE_2), {HAL_LL_ANSB_REG_ADDRESS, 0}, ADC2_RB15, ADC2_RB15_AN15, 1},
    #endif
    #ifdef ADC2_RB2_AN2
    {GPIO_PB2, hal_ll_adc_module_num(ADC_MODULE_2), {HAL_LL_ANSB_REG_ADDRESS, 0}, ADC2_RB2, ADC2_RB2_AN2, 1},
    #endif
    #ifdef ADC2_RB3_AN3
    {GPIO_PB3, hal_ll_adc_module_num(ADC_MODULE_2), {HAL_LL_ANSB_REG_ADDRESS, 0}, ADC2_RB3, ADC2_RB3_AN3, 1},
    #endif
    #ifdef ADC2_RB4_AN4
    {GPIO_PB4, hal_ll_adc_module_num(ADC_MODULE_2), {HAL_LL_ANSB_REG_ADDRESS, 0}, ADC2_RB4, ADC2_RB4_AN4, 1},
    #endif
    #ifdef ADC2_RB5_AN5
    {GPIO_PB5, hal_ll_adc_module_num(ADC_MODULE_2), {HAL_LL_ANSB_REG_ADDRESS, 0}, ADC2_RB5, ADC2_RB5_AN5, 1},
    #endif
    #ifdef ADC2_RB6_AN6
    {GPIO_PB6, hal_ll_adc_module_num(ADC_MODULE_2), {HAL_LL_ANSB_REG_ADDRESS, 0}, ADC2_RB6, ADC2_RB6_AN6, 1},
    #endif
    #ifdef ADC2_RB7_AN7
    {GPIO_PB7, hal_ll_adc_module_num(ADC_MODULE_2), {HAL_LL_ANSB_REG_ADDRESS, 0}, ADC2_RB7, ADC2_RB7_AN7, 1},
    #endif
    #ifdef ADC2_RB8_AN8
    {GPIO_PB8, hal_ll_adc_module_num(ADC_MODULE_2), {HAL_LL_ANSB_REG_ADDRESS, 0}, ADC2_RB8, ADC2_RB8_AN8, 1},
    #endif
    #ifdef ADC2_RB9_AN9
    {GPIO_PB9, hal_ll_adc_module_num(ADC_MODULE_2), {HAL_LL_ANSB_REG_ADDRESS, 0}, ADC2_RB9, ADC2_RB9_AN9, 1},
    #endif
    #ifdef ADC1_RA6_AN22
    {GPIO_PA6, hal_ll_adc_module_num(ADC_MODULE_1), {HAL_LL_ANSA_REG_ADDRESS, 0}, ADC1_RA6, ADC1_RA6_AN22, 1},
    #endif
    #ifdef ADC1_RA7_AN23
    {GPIO_PA7, hal_ll_adc_module_num(ADC_MODULE_1), {HAL_LL_ANSA_REG_ADDRESS, 0}, ADC1_RA7, ADC1_RA7_AN23, 1},
    #endif
    #ifdef ADC1_RC1_AN16
    {GPIO_PC1, hal_ll_adc_module_num(ADC_MODULE_1), {HAL_LL_ANSC_REG_ADDRESS, 0}, ADC1_RC1, ADC1_RC1_AN16, 1},
    #endif
    #ifdef ADC1_RC2_AN17
    {GPIO_PC2, hal_ll_adc_module_num(ADC_MODULE_1), {HAL_LL_ANSC_REG_ADDRESS, 0}, ADC1_RC2, ADC1_RC2_AN17, 1},
    #endif
    #ifdef ADC1_RC3_AN18
    {GPIO_PC3, hal_ll_adc_module_num(ADC_MODULE_1), {HAL_LL_ANSC_REG_ADDRESS, 0}, ADC1_RC3, ADC1_RC3_AN18, 1},
    #endif
    #ifdef ADC1_RC4_AN19
    {GPIO_PC4, hal_ll_adc_module_num(ADC_MODULE_1), {HAL_LL_ANSC_REG_ADDRESS, 0}, ADC1_RC4, ADC1_RC4_AN19, 1},
    #endif
    #ifdef ADC1_RE8_AN20
    {GPIO_PE8, hal_ll_adc_module_num(ADC_MODULE_1), {HAL_LL_ANSE_REG_ADDRESS, 0}, ADC1_RE8, ADC1_RE8_AN20, 1},
    #endif
    #ifdef ADC1_RE9_AN21
    {GPIO_PE9, hal_ll_adc_module_num(ADC_MODULE_1), {HAL_LL_ANSE_REG_ADDRESS, 0}, ADC1_RE9, ADC1_RE9_AN21, 1},
    #endif
    #ifdef ADC1_RA10_AN56
    {GPIO_PA10, hal_ll_adc_module_num(ADC_MODULE_1), {HAL_LL_ANSA_REG_ADDRESS, 0}, ADC1_RA10, ADC1_RA10_AN56, 1},
    #endif
    #ifdef ADC1_RA7_AN55
    {GPIO_PA7, hal_ll_adc_module_num(ADC_MODULE_1), {HAL_LL_ANSA_REG_ADDRESS, 0}, ADC1_RA7, ADC1_RA7_AN55, 1},
    #endif
    #ifdef ADC1_RC6_AN53
    {GPIO_PC6, hal_ll_adc_module_num(ADC_MODULE_1), {HAL_LL_ANSC_REG_ADDRESS, 0}, ADC1_RC6, ADC1_RC6_AN53, 1},
    #endif
    #ifdef ADC1_RC7_AN52
    {GPIO_PC7, hal_ll_adc_module_num(ADC_MODULE_1), {HAL_LL_ANSC_REG_ADDRESS, 0}, ADC1_RC7, ADC1_RC7_AN52, 1},
    #endif
    #ifdef ADC1_RC8_AN51
    {GPIO_PC8, hal_ll_adc_module_num(ADC_MODULE_1), {HAL_LL_ANSC_REG_ADDRESS, 0}, ADC1_RC8, ADC1_RC8_AN51, 1},
    #endif
    #ifdef ADC1_RC9_AN54
    {GPIO_PC9, hal_ll_adc_module_num(ADC_MODULE_1), {HAL_LL_ANSC_REG_ADDRESS, 0}, ADC1_RC9, ADC1_RC9_AN54, 1},
    #endif
    #ifdef ADC_RA0_AN0
    {GPIO_PA0, hal_ll_adc_module_num(ADC_MODULE), {HAL_LL_ANSA_REG_ADDRESS, 0}, ADC_RA0, ADC_RA0_AN0, 1},
    #endif
    #ifdef ADC_RA1_AN1
    {GPIO_PA1, hal_ll_adc_module_num(ADC_MODULE), {HAL_LL_ANSA_REG_ADDRESS, 0}, ADC_RA1, ADC_RA1_AN1, 1},
    #endif
    #ifdef ADC_RB0_AN2
    {GPIO_PB0, hal_ll_adc_module_num(ADC_MODULE), {HAL_LL_ANSB_REG_ADDRESS, 0}, ADC_RB0, ADC_RB0_AN2, 1},
    #endif
    #ifdef ADC_RB1_AN3
    {GPIO_PB1, hal_ll_adc_module_num(ADC_MODULE), {HAL_LL_ANSB_REG_ADDRESS, 0}, ADC_RB1, ADC_RB1_AN3, 1},
    #endif
    #ifdef ADC_RB13_AN11
    {GPIO_PB13, hal_ll_adc_module_num(ADC_MODULE), {HAL_LL_ANSB_REG_ADDRESS, 0}, ADC_RB13, ADC_RB13_AN11, 1},
    #endif
    #ifdef ADC_RB14_AN10
    {GPIO_PB14, hal_ll_adc_module_num(ADC_MODULE), {HAL_LL_ANSB_REG_ADDRESS, 0}, ADC_RB14, ADC_RB14_AN10, 1},
    #endif
    #ifdef ADC_RB15_AN9
    {GPIO_PB15, hal_ll_adc_module_num(ADC_MODULE), {HAL_LL_ANSB_REG_ADDRESS, 0}, ADC_RB15, ADC_RB15_AN9, 1},
    #endif
    #ifdef ADC_RB2_AN4
    {GPIO_PB2, hal_ll_adc_module_num(ADC_MODULE), {HAL_LL_ANSB_REG_ADDRESS, 0}, ADC_RB2, ADC_RB2_AN4, 1},
    #endif
    #ifdef ADC_RB3_AN5
    {GPIO_PB3, hal_ll_adc_module_num(ADC_MODULE), {HAL_LL_ANSB_REG_ADDRESS, 0}, ADC_RB3, ADC_RB3_AN5, 1},
    #endif
    #ifdef ADC_RC0_AN6
    {GPIO_PC0, hal_ll_adc_module_num(ADC_MODULE), {HAL_LL_ANSC_REG_ADDRESS, 0}, ADC_RC0, ADC_RC0_AN6, 1},
    #endif
    #ifdef ADC_RC1_AN7
    {GPIO_PC1, hal_ll_adc_module_num(ADC_MODULE), {HAL_LL_ANSC_REG_ADDRESS, 0}, ADC_RC1, ADC_RC1_AN7, 1},
    #endif
    #ifdef ADC_RC2_AN8
    {GPIO_PC2, hal_ll_adc_module_num(ADC_MODULE), {HAL_LL_ANSC_REG_ADDRESS, 0}, ADC_RC2, ADC_RC2_AN8, 1},
    #endif
    #ifdef ADC_RC1_AN16
    {GPIO_PC1, hal_ll_adc_module_num(ADC_MODULE), {HAL_LL_ANSC_REG_ADDRESS, 0}, ADC_RC1, ADC_RC1_AN16, 1},
    #endif
    #ifdef ADC_RC2_AN17
    {GPIO_PC2, hal_ll_adc_module_num(ADC_MODULE), {HAL_LL_ANSC_REG_ADDRESS, 0}, ADC_RC2, ADC_RC2_AN17, 1},
    #endif
    #ifdef ADC_RA12_AN20
    {GPIO_PA12, hal_ll_adc_module_num(ADC_MODULE), {HAL_LL_ANSA_REG_ADDRESS, 0}, ADC_RA12, ADC_RA12_AN20, 1},
    #endif
    #ifdef ADC_RA13_AN21
    {GPIO_PA13, hal_ll_adc_module_num(ADC_MODULE), {HAL_LL_ANSA_REG_ADDRESS, 0}, ADC_RA13, ADC_RA13_AN21, 1},
    #endif
    #ifdef ADC_RA6_AN22
    {GPIO_PA6, hal_ll_adc_module_num(ADC_MODULE), {HAL_LL_ANSA_REG_ADDRESS, 0}, ADC_RA6, ADC_RA6_AN22, 1},
    #endif
    #ifdef ADC_RA7_AN23
    {GPIO_PA7, hal_ll_adc_module_num(ADC_MODULE), {HAL_LL_ANSA_REG_ADDRESS, 0}, ADC_RA7, ADC_RA7_AN23, 1},
    #endif
    #ifdef ADC_RC3_AN18
    {GPIO_PC3, hal_ll_adc_module_num(ADC_MODULE), {HAL_LL_ANSC_REG_ADDRESS, 0}, ADC_RC3, ADC_RC3_AN18, 1},
    #endif
    #ifdef ADC_RC4_AN19
    {GPIO_PC4, hal_ll_adc_module_num(ADC_MODULE), {HAL_LL_ANSC_REG_ADDRESS, 0}, ADC_RC4, ADC_RC4_AN19, 1},
    #endif
    #ifdef ADC_RE0_AN24
    {GPIO_PE0, hal_ll_adc_module_num(ADC_MODULE), {HAL_LL_ANSE_REG_ADDRESS, 0}, ADC_RE0, ADC_RE0_AN24, 1},
    #endif
    #ifdef ADC_RE1_AN25
    {GPIO_PE1, hal_ll_adc_module_num(ADC_MODULE), {HAL_LL_ANSE_REG_ADDRESS, 0}, ADC_RE1, ADC_RE1_AN25, 1},
    #endif
    #ifdef ADC_RE2_AN26
    {GPIO_PE2, hal_ll_adc_module_num(ADC_MODULE), {HAL_LL_ANSE_REG_ADDRESS, 0}, ADC_RE2, ADC_RE2_AN26, 1},
    #endif
    #ifdef ADC_RE3_AN27
    {GPIO_PE3, hal_ll_adc_module_num(ADC_MODULE), {HAL_LL_ANSE_REG_ADDRESS, 0}, ADC_RE3, ADC_RE3_AN27, 1},
    #endif
    #ifdef ADC_RE4_AN28
    {GPIO_PE4, hal_ll_adc_module_num(ADC_MODULE), {HAL_LL_ANSE_REG_ADDRESS, 0}, ADC_RE4, ADC_RE4_AN28, 1},
    #endif
    #ifdef ADC_RE5_AN29
    {GPIO_PE5, hal_ll_adc_module_num(ADC_MODULE), {HAL_LL_ANSE_REG_ADDRESS, 0}, ADC_RE5, ADC_RE5_AN29, 1},
    #endif
    #ifdef ADC_RE6_AN30
    {GPIO_PE6, hal_ll_adc_module_num(ADC_MODULE), {HAL_LL_ANSE_REG_ADDRESS, 0}, ADC_RE6, ADC_RE6_AN30, 1},
    #endif
    #ifdef ADC_RE7_AN31
    {GPIO_PE7, hal_ll_adc_module_num(ADC_MODULE), {HAL_LL_ANSE_REG_ADDRESS, 0}, ADC_RE7, ADC_RE7_AN31, 1},
    #endif
    #ifdef ADC2_RC1_AN16
    {GPIO_PC1, hal_ll_adc_module_num(ADC_MODULE_2), {HAL_LL_ANSC_REG_ADDRESS, 0}, ADC2_RC1, ADC2_RC1_AN16, 1},
    #endif
    #ifdef ADC2_RC2_AN17
    {GPIO_PC2, hal_ll_adc_module_num(ADC_MODULE_2), {HAL_LL_ANSC_REG_ADDRESS, 0}, ADC2_RC2, ADC2_RC2_AN17, 1},
    #endif
    #ifdef ADC1_RA12_AN20
    {GPIO_PA12, hal_ll_adc_module_num(ADC_MODULE_1), {HAL_LL_ANSA_REG_ADDRESS, 0}, ADC1_RA12, ADC1_RA12_AN20, 1},
    #endif
    #ifdef ADC1_RA13_AN21
    {GPIO_PA13, hal_ll_adc_module_num(ADC_MODULE_1), {HAL_LL_ANSA_REG_ADDRESS, 0}, ADC1_RA13, ADC1_RA13_AN21, 1},
    #endif
    #ifdef ADC2_RA12_AN20
    {GPIO_PA12, hal_ll_adc_module_num(ADC_MODULE_2), {HAL_LL_ANSA_REG_ADDRESS, 0}, ADC2_RA12, ADC2_RA12_AN20, 1},
    #endif
    #ifdef ADC2_RA13_AN21
    {GPIO_PA13, hal_ll_adc_module_num(ADC_MODULE_2), {HAL_LL_ANSA_REG_ADDRESS, 0}, ADC2_RA13, ADC2_RA13_AN21, 1},
    #endif
    #ifdef ADC2_RA6_AN22
    {GPIO_PA6, hal_ll_adc_module_num(ADC_MODULE_2), {HAL_LL_ANSA_REG_ADDRESS, 0}, ADC2_RA6, ADC2_RA6_AN22, 1},
    #endif
    #ifdef ADC2_RA7_AN23
    {GPIO_PA7, hal_ll_adc_module_num(ADC_MODULE_2), {HAL_LL_ANSA_REG_ADDRESS, 0}, ADC2_RA7, ADC2_RA7_AN23, 1},
    #endif
    #ifdef ADC2_RC3_AN18
    {GPIO_PC3, hal_ll_adc_module_num(ADC_MODULE_2), {HAL_LL_ANSC_REG_ADDRESS, 0}, ADC2_RC3, ADC2_RC3_AN18, 1},
    #endif
    #ifdef ADC2_RC4_AN19
    {GPIO_PC4, hal_ll_adc_module_num(ADC_MODULE_2), {HAL_LL_ANSC_REG_ADDRESS, 0}, ADC2_RC4, ADC2_RC4_AN19, 1},
    #endif
    #ifdef ADC2_RE0_AN24
    {GPIO_PE0, hal_ll_adc_module_num(ADC_MODULE_2), {HAL_LL_ANSE_REG_ADDRESS, 0}, ADC2_RE0, ADC2_RE0_AN24, 1},
    #endif
    #ifdef ADC2_RE1_AN25
    {GPIO_PE1, hal_ll_adc_module_num(ADC_MODULE_2), {HAL_LL_ANSE_REG_ADDRESS, 0}, ADC2_RE1, ADC2_RE1_AN25, 1},
    #endif
    #ifdef ADC2_RE2_AN26
    {GPIO_PE2, hal_ll_adc_module_num(ADC_MODULE_2), {HAL_LL_ANSE_REG_ADDRESS, 0}, ADC2_RE2, ADC2_RE2_AN26, 1},
    #endif
    #ifdef ADC2_RE3_AN27
    {GPIO_PE3, hal_ll_adc_module_num(ADC_MODULE_2), {HAL_LL_ANSE_REG_ADDRESS, 0}, ADC2_RE3, ADC2_RE3_AN27, 1},
    #endif
    #ifdef ADC2_RE4_AN28
    {GPIO_PE4, hal_ll_adc_module_num(ADC_MODULE_2), {HAL_LL_ANSE_REG_ADDRESS, 0}, ADC2_RE4, ADC2_RE4_AN28, 1},
    #endif
    #ifdef ADC2_RE5_AN29
    {GPIO_PE5, hal_ll_adc_module_num(ADC_MODULE_2), {HAL_LL_ANSE_REG_ADDRESS, 0}, ADC2_RE5, ADC2_RE5_AN29, 1},
    #endif
    #ifdef ADC2_RE6_AN30
    {GPIO_PE6, hal_ll_adc_module_num(ADC_MODULE_2), {HAL_LL_ANSE_REG_ADDRESS, 0}, ADC2_RE6, ADC2_RE6_AN30, 1},
    #endif
    #ifdef ADC2_RE7_AN31
    {GPIO_PE7, hal_ll_adc_module_num(ADC_MODULE_2), {HAL_LL_ANSE_REG_ADDRESS, 0}, ADC2_RE7, ADC2_RE7_AN31, 1},
    #endif
    #ifdef ADC_RE8_AN20
    {GPIO_PE8, hal_ll_adc_module_num(ADC_MODULE), {HAL_LL_ANSE_REG_ADDRESS, 0}, ADC_RE8, ADC_RE8_AN20, 1},
    #endif
    #ifdef ADC_RE9_AN21
    {GPIO_PE9, hal_ll_adc_module_num(ADC_MODULE), {HAL_LL_ANSE_REG_ADDRESS, 0}, ADC_RE9, ADC_RE9_AN21, 1},
    #endif
    #ifdef ADC2_RE8_AN20
    {GPIO_PE8, hal_ll_adc_module_num(ADC_MODULE_2), {HAL_LL_ANSE_REG_ADDRESS, 0}, ADC2_RE8, ADC2_RE8_AN20, 1},
    #endif
    #ifdef ADC2_RE9_AN21
    {GPIO_PE9, hal_ll_adc_module_num(ADC_MODULE_2), {HAL_LL_ANSE_REG_ADDRESS, 0}, ADC2_RE9, ADC2_RE9_AN21, 1},
    #endif
    #ifdef ADC_RA2_AN2
    {GPIO_PA2, hal_ll_adc_module_num(ADC_MODULE), {HAL_LL_ANSA_REG_ADDRESS, 0}, ADC_RA2, ADC_RA2_AN2, 1},
    #endif
    #ifdef ADC_RB0_AN3
    {GPIO_PB0, hal_ll_adc_module_num(ADC_MODULE), {HAL_LL_ANSB_REG_ADDRESS, 0}, ADC_RB0, ADC_RB0_AN3, 1},
    #endif
    #ifdef ADC_RB1_AN6
    {GPIO_PB1, hal_ll_adc_module_num(ADC_MODULE), {HAL_LL_ANSB_REG_ADDRESS, 0}, ADC_RB1, ADC_RB1_AN6, 1},
    #endif
    #ifdef ADC_RB10_AN5
    {GPIO_PB10, hal_ll_adc_module_num(ADC_MODULE), {HAL_LL_ANSB_REG_ADDRESS, 0}, ADC_RB10, ADC_RB10_AN5, 1},
    #endif
    #ifdef ADC_RB2_AN7
    {GPIO_PB2, hal_ll_adc_module_num(ADC_MODULE), {HAL_LL_ANSB_REG_ADDRESS, 0}, ADC_RB2, ADC_RB2_AN7, 1},
    #endif
    #ifdef ADC_RB9_AN4
    {GPIO_PB9, hal_ll_adc_module_num(ADC_MODULE), {HAL_LL_ANSB_REG_ADDRESS, 0}, ADC_RB9, ADC_RB9_AN4, 1},
    #endif
    #ifdef ADC_RC1_AN8
    {GPIO_PC1, hal_ll_adc_module_num(ADC_MODULE), {HAL_LL_ANSC_REG_ADDRESS, 0}, ADC_RC1, ADC_RC1_AN8, 1},
    #endif
    #ifdef ADC_RC10_AN10
    {GPIO_PC10, hal_ll_adc_module_num(ADC_MODULE), {HAL_LL_ANSC_REG_ADDRESS, 0}, ADC_RC10, ADC_RC10_AN10, 1},
    #endif
    #ifdef ADC_RC2_AN9
    {GPIO_PC2, hal_ll_adc_module_num(ADC_MODULE), {HAL_LL_ANSC_REG_ADDRESS, 0}, ADC_RC2, ADC_RC2_AN9, 1},
    #endif
    #ifdef ADC_RC9_AN11
    {GPIO_PC9, hal_ll_adc_module_num(ADC_MODULE), {HAL_LL_ANSC_REG_ADDRESS, 0}, ADC_RC9, ADC_RC9_AN11, 1},
    #endif
    #ifdef ADC_RA4_AN10
    {GPIO_PA4, hal_ll_adc_module_num(ADC_MODULE), {HAL_LL_ANSA_REG_ADDRESS, 0}, ADC_RA4, ADC_RA4_AN10, 1},
    #endif
    #ifdef ADC_RB4_AN9
    {GPIO_PB4, hal_ll_adc_module_num(ADC_MODULE), {HAL_LL_ANSB_REG_ADDRESS, 0}, ADC_RB4, ADC_RB4_AN9, 1},
    #endif
    #ifdef ADC_RC3_AN11
    {GPIO_PC3, hal_ll_adc_module_num(ADC_MODULE), {HAL_LL_ANSC_REG_ADDRESS, 0}, ADC_RC3, ADC_RC3_AN11, 1},
    #endif
    #ifdef ADC_RC4_AN12
    {GPIO_PC4, hal_ll_adc_module_num(ADC_MODULE), {HAL_LL_ANSC_REG_ADDRESS, 0}, ADC_RC4, ADC_RC4_AN12, 1},
    #endif
    #ifdef ADC_RC5_AN15
    {GPIO_PC5, hal_ll_adc_module_num(ADC_MODULE), {HAL_LL_ANSC_REG_ADDRESS, 0}, ADC_RC5, ADC_RC5_AN15, 1},
    #endif
    #ifdef ADC1_RA2_AN13
    {GPIO_PA2, hal_ll_adc_module_num(ADC_MODULE_1), {HAL_LL_ANSA_REG_ADDRESS, 0}, ADC1_RA2, ADC1_RA2_AN13, 1},
    #endif
    #ifdef ADC1_RA3_AN14
    {GPIO_PA3, hal_ll_adc_module_num(ADC_MODULE_1), {HAL_LL_ANSA_REG_ADDRESS, 0}, ADC1_RA3, ADC1_RA3_AN14, 1},
    #endif
    #ifdef ADC1_RB13_AN11
    {GPIO_PB13, hal_ll_adc_module_num(ADC_MODULE_1), {HAL_LL_ANSB_REG_ADDRESS, 0}, ADC1_RB13, ADC1_RB13_AN11, 1},
    #endif
    #ifdef ADC1_RB14_AN10
    {GPIO_PB14, hal_ll_adc_module_num(ADC_MODULE_1), {HAL_LL_ANSB_REG_ADDRESS, 0}, ADC1_RB14, ADC1_RB14_AN10, 1},
    #endif
    #ifdef ADC1_RB15_AN9
    {GPIO_PB15, hal_ll_adc_module_num(ADC_MODULE_1), {HAL_LL_ANSB_REG_ADDRESS, 0}, ADC1_RB15, ADC1_RB15_AN9, 1},
    #endif
    #ifdef ADC1_RB4_AN15
    {GPIO_PB4, hal_ll_adc_module_num(ADC_MODULE_1), {HAL_LL_ANSB_REG_ADDRESS, 0}, ADC1_RB4, ADC1_RB4_AN15, 1},
    #endif
    #ifdef ADC1_RA4_AN16
    {GPIO_PA4, hal_ll_adc_module_num(ADC_MODULE_1), {HAL_LL_ANSA_REG_ADDRESS, 0}, ADC1_RA4, ADC1_RA4_AN16, 1},
    #endif
    #ifdef ADC1_RB5_AN17
    {GPIO_PB5, hal_ll_adc_module_num(ADC_MODULE_1), {HAL_LL_ANSB_REG_ADDRESS, 0}, ADC1_RB5, ADC1_RB5_AN17, 1},
    #endif
    #ifdef ADC1_RB6_AN18
    {GPIO_PB6, hal_ll_adc_module_num(ADC_MODULE_1), {HAL_LL_ANSB_REG_ADDRESS, 0}, ADC1_RB6, ADC1_RB6_AN18, 1},
    #endif
    #ifdef ADC1_RB7_AN19
    {GPIO_PB7, hal_ll_adc_module_num(ADC_MODULE_1), {HAL_LL_ANSB_REG_ADDRESS, 0}, ADC1_RB7, ADC1_RB7_AN19, 1},
    #endif
    #ifdef ADC1_RB8_AN20
    {GPIO_PB8, hal_ll_adc_module_num(ADC_MODULE_1), {HAL_LL_ANSB_REG_ADDRESS, 0}, ADC1_RB8, ADC1_RB8_AN20, 1},
    #endif
    #ifdef ADC1_RB9_AN21
    {GPIO_PB9, hal_ll_adc_module_num(ADC_MODULE_1), {HAL_LL_ANSB_REG_ADDRESS, 0}, ADC1_RB9, ADC1_RB9_AN21, 1},
    #endif
    #ifdef ADC1_RA6_AN23
    {GPIO_PA6, hal_ll_adc_module_num(ADC_MODULE_1), {HAL_LL_ANSA_REG_ADDRESS, 0}, ADC1_RA6, ADC1_RA6_AN23, 1},
    #endif
    #ifdef ADC1_RA7_AN22
    {GPIO_PA7, hal_ll_adc_module_num(ADC_MODULE_1), {HAL_LL_ANSA_REG_ADDRESS, 0}, ADC1_RA7, ADC1_RA7_AN22, 1},
    #endif
    #ifdef ADC1_RC4_AN16
    {GPIO_PC4, hal_ll_adc_module_num(ADC_MODULE_1), {HAL_LL_ANSC_REG_ADDRESS, 0}, ADC1_RC4, ADC1_RC4_AN16, 1},
    #endif
    #ifdef ADC1_RG6_AN17
    {GPIO_PG6, hal_ll_adc_module_num(ADC_MODULE_1), {HAL_LL_ANSG_REG_ADDRESS, 0}, ADC1_RG6, ADC1_RG6_AN17, 1},
    #endif
    #ifdef ADC1_RG8_AN19
    {GPIO_PG8, hal_ll_adc_module_num(ADC_MODULE_1), {HAL_LL_ANSG_REG_ADDRESS, 0}, ADC1_RG8, ADC1_RG8_AN19, 1},
    #endif
    #ifdef ADC1_RG9_AN20
    {GPIO_PG9, hal_ll_adc_module_num(ADC_MODULE_1), {HAL_LL_ANSG_REG_ADDRESS, 0}, ADC1_RG9, ADC1_RG9_AN20, 1},
    #endif
    #ifdef ADC1_RB12_AN8
    {GPIO_PB12, hal_ll_adc_module_num(ADC_MODULE_1), {HAL_LL_ANSB_REG_ADDRESS, 0}, ADC1_RB12, ADC1_RB12_AN8, 1},
    #endif
    #ifdef ADC1_RB13_AN7
    {GPIO_PB13, hal_ll_adc_module_num(ADC_MODULE_1), {HAL_LL_ANSB_REG_ADDRESS, 0}, ADC1_RB13, ADC1_RB13_AN7, 1},
    #endif
    #ifdef ADC1_RB14_AN6
    {GPIO_PB14, hal_ll_adc_module_num(ADC_MODULE_1), {HAL_LL_ANSB_REG_ADDRESS, 0}, ADC1_RB14, ADC1_RB14_AN6, 1},
    #endif
    #ifdef ADC1_RC0_AN10
    {GPIO_PC0, hal_ll_adc_module_num(ADC_MODULE_1), {HAL_LL_ANSC_REG_ADDRESS, 0}, ADC1_RC0, ADC1_RC0_AN10, 1},
    #endif
    #ifdef ADC1_RC1_AN11
    {GPIO_PC1, hal_ll_adc_module_num(ADC_MODULE_1), {HAL_LL_ANSC_REG_ADDRESS, 0}, ADC1_RC1, ADC1_RC1_AN11, 1},
    #endif
    #ifdef ADC1_RC2_AN12
    {GPIO_PC2, hal_ll_adc_module_num(ADC_MODULE_1), {HAL_LL_ANSC_REG_ADDRESS, 0}, ADC1_RC2, ADC1_RC2_AN12, 1},
    #endif
    #ifdef ADC1_RC3_AN13
    {GPIO_PC3, hal_ll_adc_module_num(ADC_MODULE_1), {HAL_LL_ANSC_REG_ADDRESS, 0}, ADC1_RC3, ADC1_RC3_AN13, 1},
    #endif
    #ifdef ADC1_RD0_AN43
    {GPIO_PD0, hal_ll_adc_module_num(ADC_MODULE_1), {HAL_LL_ANSD_REG_ADDRESS, 0}, ADC1_RD0, ADC1_RD0_AN43, 1},
    #endif
    #ifdef ADC1_RD1_AN35
    {GPIO_PD1, hal_ll_adc_module_num(ADC_MODULE_1), {HAL_LL_ANSD_REG_ADDRESS, 0}, ADC1_RD1, ADC1_RD1_AN35, 1},
    #endif
    #ifdef ADC1_RD10_AN41
    {GPIO_PD10, hal_ll_adc_module_num(ADC_MODULE_1), {HAL_LL_ANSD_REG_ADDRESS, 0}, ADC1_RD10, ADC1_RD10_AN41, 1},
    #endif
    #ifdef ADC1_RD11_AN42
    {GPIO_PD11, hal_ll_adc_module_num(ADC_MODULE_1), {HAL_LL_ANSD_REG_ADDRESS, 0}, ADC1_RD11, ADC1_RD11_AN42, 1},
    #endif
    #ifdef ADC1_RD2_AN25
    {GPIO_PD2, hal_ll_adc_module_num(ADC_MODULE_1), {HAL_LL_ANSD_REG_ADDRESS, 0}, ADC1_RD2, ADC1_RD2_AN25, 1},
    #endif
    #ifdef ADC1_RD3_AN44
    {GPIO_PD3, hal_ll_adc_module_num(ADC_MODULE_1), {HAL_LL_ANSD_REG_ADDRESS, 0}, ADC1_RD3, ADC1_RD3_AN44, 1},
    #endif
    #ifdef ADC1_RD4_AN47
    {GPIO_PD4, hal_ll_adc_module_num(ADC_MODULE_1), {HAL_LL_ANSD_REG_ADDRESS, 0}, ADC1_RD4, ADC1_RD4_AN47, 1},
    #endif
    #ifdef ADC1_RD5_AN48
    {GPIO_PD5, hal_ll_adc_module_num(ADC_MODULE_1), {HAL_LL_ANSD_REG_ADDRESS, 0}, ADC1_RD5, ADC1_RD5_AN48, 1},
    #endif
    #ifdef ADC1_RD6_AN34
    {GPIO_PD6, hal_ll_adc_module_num(ADC_MODULE_1), {HAL_LL_ANSD_REG_ADDRESS, 0}, ADC1_RD6, ADC1_RD6_AN34, 1},
    #endif
    #ifdef ADC1_RD7_AN20
    {GPIO_PD7, hal_ll_adc_module_num(ADC_MODULE_1), {HAL_LL_ANSD_REG_ADDRESS, 0}, ADC1_RD7, ADC1_RD7_AN20, 1},
    #endif
    #ifdef ADC1_RD8_AN40
    {GPIO_PD8, hal_ll_adc_module_num(ADC_MODULE_1), {HAL_LL_ANSD_REG_ADDRESS, 0}, ADC1_RD8, ADC1_RD8_AN40, 1},
    #endif
    #ifdef ADC1_RD9_AN24
    {GPIO_PD9, hal_ll_adc_module_num(ADC_MODULE_1), {HAL_LL_ANSD_REG_ADDRESS, 0}, ADC1_RD9, ADC1_RD9_AN24, 1},
    #endif
    #ifdef ADC1_RF3_AN30
    {GPIO_PF3, hal_ll_adc_module_num(ADC_MODULE_1), {HAL_LL_ANSF_REG_ADDRESS, 0}, ADC1_RF3, ADC1_RF3_AN30, 1},
    #endif
    #ifdef ADC1_RF4_AN11
    {GPIO_PF4, hal_ll_adc_module_num(ADC_MODULE_1), {HAL_LL_ANSF_REG_ADDRESS, 0}, ADC1_RF4, ADC1_RF4_AN11, 1},
    #endif
    #ifdef ADC1_RF5_AN10
    {GPIO_PF5, hal_ll_adc_module_num(ADC_MODULE_1), {HAL_LL_ANSF_REG_ADDRESS, 0}, ADC1_RF5, ADC1_RF5_AN10, 1},
    #endif
    #ifdef ADC1_RG9_AN49
    {GPIO_PG9, hal_ll_adc_module_num(ADC_MODULE_1), {HAL_LL_ANSG_REG_ADDRESS, 0}, ADC1_RG9, ADC1_RG9_AN49, 1},
    #endif
    #ifdef ADC1_RA1_AN26
    {GPIO_PA1, hal_ll_adc_module_num(ADC_MODULE_1), {HAL_LL_ANSA_REG_ADDRESS, 0}, ADC1_RA1, ADC1_RA1_AN26, 1},
    #endif
    #ifdef ADC1_RA14_AN38
    {GPIO_PA14, hal_ll_adc_module_num(ADC_MODULE_1), {HAL_LL_ANSA_REG_ADDRESS, 0}, ADC1_RA14, ADC1_RA14_AN38, 1},
    #endif
    #ifdef ADC1_RA15_AN39
    {GPIO_PA15, hal_ll_adc_module_num(ADC_MODULE_1), {HAL_LL_ANSA_REG_ADDRESS, 0}, ADC1_RA15, ADC1_RA15_AN39, 1},
    #endif
    #ifdef ADC1_RA4_AN36
    {GPIO_PA4, hal_ll_adc_module_num(ADC_MODULE_1), {HAL_LL_ANSA_REG_ADDRESS, 0}, ADC1_RA4, ADC1_RA4_AN36, 1},
    #endif
    #ifdef ADC1_RA5_AN37
    {GPIO_PA5, hal_ll_adc_module_num(ADC_MODULE_1), {HAL_LL_ANSA_REG_ADDRESS, 0}, ADC1_RA5, ADC1_RA5_AN37, 1},
    #endif
    #ifdef ADC1_RC3_AN9
    {GPIO_PC3, hal_ll_adc_module_num(ADC_MODULE_1), {HAL_LL_ANSC_REG_ADDRESS, 0}, ADC1_RC3, ADC1_RC3_AN9, 1},
    #endif
    #ifdef ADC1_RD12_AN45
    {GPIO_PD12, hal_ll_adc_module_num(ADC_MODULE_1), {HAL_LL_ANSD_REG_ADDRESS, 0}, ADC1_RD12, ADC1_RD12_AN45, 1},
    #endif
    #ifdef ADC1_RD13_AN46
    {GPIO_PD13, hal_ll_adc_module_num(ADC_MODULE_1), {HAL_LL_ANSD_REG_ADDRESS, 0}, ADC1_RD13, ADC1_RD13_AN46, 1},
    #endif
    #ifdef ADC1_RD14_AN28
    {GPIO_PD14, hal_ll_adc_module_num(ADC_MODULE_1), {HAL_LL_ANSD_REG_ADDRESS, 0}, ADC1_RD14, ADC1_RD14_AN28, 1},
    #endif
    #ifdef ADC1_RD15_AN29
    {GPIO_PD15, hal_ll_adc_module_num(ADC_MODULE_1), {HAL_LL_ANSD_REG_ADDRESS, 0}, ADC1_RD15, ADC1_RD15_AN29, 1},
    #endif
    #ifdef ADC1_RF13_AN27
    {GPIO_PF13, hal_ll_adc_module_num(ADC_MODULE_1), {HAL_LL_ANSF_REG_ADDRESS, 0}, ADC1_RF13, ADC1_RF13_AN27, 1},
    #endif
    #ifdef ADC1_RF2_AN31
    {GPIO_PF2, hal_ll_adc_module_num(ADC_MODULE_1), {HAL_LL_ANSF_REG_ADDRESS, 0}, ADC1_RF2, ADC1_RF2_AN31, 1},
    #endif
    #ifdef ADC1_RF8_AN32
    {GPIO_PF8, hal_ll_adc_module_num(ADC_MODULE_1), {HAL_LL_ANSF_REG_ADDRESS, 0}, ADC1_RF8, ADC1_RF8_AN32, 1},
    #endif
    #ifdef ADC1_RG15_AN33
    {GPIO_PG15, hal_ll_adc_module_num(ADC_MODULE_1), {HAL_LL_ANSG_REG_ADDRESS, 0}, ADC1_RG15, ADC1_RG15_AN33, 1},
    #endif
    #ifdef ADC1_RC3_AN12
    {GPIO_PC3, hal_ll_adc_module_num(ADC_MODULE_1), {HAL_LL_ANSC_REG_ADDRESS, 0}, ADC1_RC3, ADC1_RC3_AN12, 1},
    #endif
    #endif
    // EOF list

    #ifdef HAL_LL_ANSELA_ANSA3
    {GPIO_PA3, 0, {HAL_LL_ANSELA_REG_ADDRESS , 0}, HAL_LL_ANSELA_ANSA3, 0, 1},
    #endif
    #ifdef HAL_LL_ANSELA_ANSA4
    {GPIO_PA4, 0, {HAL_LL_ANSELA_REG_ADDRESS , 0}, HAL_LL_ANSELA_ANSA4, 0, 1},
    #endif
    #ifdef HAL_LL_ANSELB_ANSB8
    {GPIO_PB8, 0, {HAL_LL_ANSELB_REG_ADDRESS , 0}, HAL_LL_ANSELB_ANSB8, 0, 1},
    #endif
    #ifdef HAL_LL_ANSELC_ANSC4
    {GPIO_PC4, 0, {HAL_LL_ANSELC_REG_ADDRESS , 0}, HAL_LL_ANSELC_ANSC4, 0, 1},
    #endif
    #ifdef HAL_LL_ANSELC_ANSC5
    {GPIO_PC5, 0, {HAL_LL_ANSELC_REG_ADDRESS , 0}, HAL_LL_ANSELC_ANSC5, 0, 1},
    #endif
    #ifdef HAL_LL_ANSELB_ANSB4
    {GPIO_PB4, 0, {HAL_LL_ANSELB_REG_ADDRESS , 0}, HAL_LL_ANSELB_ANSB4, 0, 1},
    #endif
    #ifdef HAL_LL_ANSELC_ANSC0
    {GPIO_PC0, 0, {HAL_LL_ANSELC_REG_ADDRESS , 0}, HAL_LL_ANSELC_ANSC0, 0, 1},
    #endif
    #ifdef HAL_LL_ANSELD_ANSD14
    {GPIO_PD14, 0, {HAL_LL_ANSELD_REG_ADDRESS , 0}, HAL_LL_ANSELD_ANSD14, 0, 1},
    #endif
    #ifdef HAL_LL_ANSELC_ANSC13
    {GPIO_PC13, 0, {HAL_LL_ANSELC_REG_ADDRESS , 0}, HAL_LL_ANSELC_ANSC13, 0, 1},
    #endif
    #ifdef HAL_LL_ANSELC_ANSC14
    {GPIO_PC14, 0, {HAL_LL_ANSELC_REG_ADDRESS , 0}, HAL_LL_ANSELC_ANSC14, 0, 1},
    #endif
    #ifdef HAL_LL_ANSELD_ANSD6
    {GPIO_PD6, 0, {HAL_LL_ANSELD_REG_ADDRESS , 0}, HAL_LL_ANSELD_ANSD6, 0, 1},
    #endif
    #ifdef HAL_LL_ANSELD_ANSD7
    {GPIO_PD7, 0, {HAL_LL_ANSELD_REG_ADDRESS , 0}, HAL_LL_ANSELD_ANSD7, 0, 1},
    #endif
    #ifdef HAL_LL_ANSELG_ANSG6
    {GPIO_PG6, 0, {HAL_LL_ANSELG_REG_ADDRESS , 0}, HAL_LL_ANSELG_ANSG6, 0, 1},
    #endif
    #ifdef HAL_LL_ANSELG_ANSG7
    {GPIO_PG7, 0, {HAL_LL_ANSELG_REG_ADDRESS , 0}, HAL_LL_ANSELG_ANSG7, 0, 1},
    #endif
    #ifdef HAL_LL_ANSELG_ANSG8
    {GPIO_PG8, 0, {HAL_LL_ANSELG_REG_ADDRESS , 0}, HAL_LL_ANSELG_ANSG8, 0, 1},
    #endif
    #ifdef HAL_LL_ANSELG_ANSG9
    {GPIO_PG9, 0, {HAL_LL_ANSELG_REG_ADDRESS , 0}, HAL_LL_ANSELG_ANSG9, 0, 1},
    #endif
    #ifdef HAL_LL_ANSELA_ANSA9
    {GPIO_PA9, 0, {HAL_LL_ANSELA_REG_ADDRESS , 0}, HAL_LL_ANSELA_ANSA9, 0, 1},
    #endif
    #ifdef HAL_LL_ANSELA_ANSA10
    {GPIO_PA10, 0, {HAL_LL_ANSELA_REG_ADDRESS , 0}, HAL_LL_ANSELA_ANSA10, 0, 1},
    #endif

    { HAL_LL_PIN_NC, HAL_LL_MODULE_ERROR, {HAL_LL_MODULE_ERROR,HAL_LL_MODULE_ERROR}, 0xFF, 0xFF, 0 }
    //------------ END
};

#ifdef __cplusplus
}
#endif

#endif // _HAL_LL_ANALOG_IN_MAP_H_
// ------------------------------------------------------------------------- END
