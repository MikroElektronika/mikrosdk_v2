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
/*

  This file is part of mikroSDK.

  Copyright (c) ${COPYRIGHT_YEAR}, MikroElektronika - www.mikroe.com

  All rights reserved.

-------------------------------------------------------------------------- */
/*!
 * @file  hal_ll_tim_pin_map.h
 * @brief CCP/TIM HAL LOW LEVEL PIN MAPS.
 */

#ifndef _HAL_LL_TIM_PIN_MAP_H_
#define _HAL_LL_TIM_PIN_MAP_H_

#ifdef __cplusplus
extern "C"{
#endif

#include "hal_ll_pin_names.h"

/*!< @brief Helper macro for getting adequate module index number */
#define hal_ll_tim_module_num(_module_num) (_module_num - 1)

/*!< @brief Macro defining `weak` attribute */
#define __weak __attribute__((weak))

/*!< @brief TIM Master pin map structure. */
typedef struct {
    hal_ll_pin_name_t pin;
    uint8_t timer;
    uint8_t module_index;
} hal_ll_tim_pin_map_t;

/*!< @brief TIM Modules. */
typedef enum {
    HAL_LL_TIM_INDEX_2 = 0,
    HAL_LL_TIM_INDEX_4,
    HAL_LL_TIM_INDEX_6,
    HAL_LL_TIM_INDEX_8
} hal_ll_tim_index_t;

/*!< @brief CCP/TIM pins */
static const hal_ll_tim_pin_map_t _tim_map[] = {
    //------------ BEGIN CCP
    #ifdef OCR_MODULE
    #endif

    #ifdef OCR_MODULE_1
    #ifdef PWM1_OC_RA0
    { GPIO_PA0, HAL_LL_TIM_INDEX_2, hal_ll_tim_module_num(OCR_MODULE_1) },
    #endif
    #ifdef PWM1_OC_RB3
    { GPIO_PB3, HAL_LL_TIM_INDEX_2, hal_ll_tim_module_num(OCR_MODULE_1) },
    #endif
    #ifdef PWM1_OC_RB4
    { GPIO_PB4, HAL_LL_TIM_INDEX_2, hal_ll_tim_module_num(OCR_MODULE_1) },
    #endif
    #ifdef PWM1_OC_RB15
    { GPIO_PB15, HAL_LL_TIM_INDEX_2, hal_ll_tim_module_num(OCR_MODULE_1) },
    #endif
    #ifdef PWM1_OC_RB7
    { GPIO_PB7, HAL_LL_TIM_INDEX_2, hal_ll_tim_module_num(OCR_MODULE_1) },
    #endif
    #ifdef PWM1_OC_RC0
    { GPIO_PC0, HAL_LL_TIM_INDEX_2, hal_ll_tim_module_num(OCR_MODULE_1) },
    #endif
    #ifdef PWM1_OC_RC7
    { GPIO_PC7, HAL_LL_TIM_INDEX_2, hal_ll_tim_module_num(OCR_MODULE_1) },
    #endif
    #ifdef PWM1_OC_RC5
    { GPIO_PC5, HAL_LL_TIM_INDEX_2, hal_ll_tim_module_num(OCR_MODULE_1) },
    #endif
    #ifdef PWM1_OC_RD1
    { GPIO_PD1, HAL_LL_TIM_INDEX_2, hal_ll_tim_module_num(OCR_MODULE_1) },
    #endif
    #ifdef PWM1_OC_RG9
    { GPIO_PG9, HAL_LL_TIM_INDEX_2, hal_ll_tim_module_num(OCR_MODULE_1) },
    #endif
    #ifdef PWM1_OC_RB14
    { GPIO_PB14, HAL_LL_TIM_INDEX_2, hal_ll_tim_module_num(OCR_MODULE_1) },
    #endif
    #ifdef PWM1_OC_RD0
    { GPIO_PD0, HAL_LL_TIM_INDEX_2, hal_ll_tim_module_num(OCR_MODULE_1) },
    #endif
    #ifdef PWM1_OC_RD8
    { GPIO_PD8, HAL_LL_TIM_INDEX_2, hal_ll_tim_module_num(OCR_MODULE_1) },
    #endif
    #ifdef PWM1_OC_RB6
    { GPIO_PB6, HAL_LL_TIM_INDEX_2, hal_ll_tim_module_num(OCR_MODULE_1) },
    #endif
    #ifdef PWM1_OC_RD5
    { GPIO_PD5, HAL_LL_TIM_INDEX_2, hal_ll_tim_module_num(OCR_MODULE_1) },
    #endif
    #ifdef PWM1_OC_RF3
    { GPIO_PF3, HAL_LL_TIM_INDEX_2, hal_ll_tim_module_num(OCR_MODULE_1) },
    #endif
    #ifdef PWM1_OC_RF6
    { GPIO_PF6, HAL_LL_TIM_INDEX_2, hal_ll_tim_module_num(OCR_MODULE_1) },
    #endif
    #ifdef PWM1_OC_RF13
    { GPIO_PF13, HAL_LL_TIM_INDEX_2, hal_ll_tim_module_num(OCR_MODULE_1) },
    #endif
    #ifdef PWM1_OC_RC2
    { GPIO_PC2, HAL_LL_TIM_INDEX_2, hal_ll_tim_module_num(OCR_MODULE_1) },
    #endif
    #ifdef PWM1_OC_RE8
    { GPIO_PE8, HAL_LL_TIM_INDEX_2, hal_ll_tim_module_num(OCR_MODULE_1) },
    #endif
    #ifdef PWM1_OC_RF2
    { GPIO_PF2, HAL_LL_TIM_INDEX_2, hal_ll_tim_module_num(OCR_MODULE_1) },
    #endif
    #ifdef PWM1_OC_RB2
    { GPIO_PB2, HAL_LL_TIM_INDEX_2, hal_ll_tim_module_num(OCR_MODULE_1) },
    #endif
    #endif

    #ifdef OCR_MODULE_2
    #ifdef PWM2_OC_RA1
    { GPIO_PA1, HAL_LL_TIM_INDEX_2, hal_ll_tim_module_num(OCR_MODULE_2) },
    #endif
    #ifdef PWM2_OC_RB5
    { GPIO_PB5, HAL_LL_TIM_INDEX_2, hal_ll_tim_module_num(OCR_MODULE_2) },
    #endif
    #ifdef PWM2_OC_RB1
    { GPIO_PB1, HAL_LL_TIM_INDEX_2, hal_ll_tim_module_num(OCR_MODULE_2) },
    #endif
    #ifdef PWM2_OC_RB11
    { GPIO_PB11, HAL_LL_TIM_INDEX_2, hal_ll_tim_module_num(OCR_MODULE_2) },
    #endif
    #ifdef PWM2_OC_RB8
    { GPIO_PB8, HAL_LL_TIM_INDEX_2, hal_ll_tim_module_num(OCR_MODULE_2) },
    #endif
    #ifdef PWM2_OC_RA8
    { GPIO_PA8, HAL_LL_TIM_INDEX_2, hal_ll_tim_module_num(OCR_MODULE_2) },
    #endif
    #ifdef PWM2_OC_RC8
    { GPIO_PC8, HAL_LL_TIM_INDEX_2, hal_ll_tim_module_num(OCR_MODULE_2) },
    #endif
    #ifdef PWM2_OC_RA9
    { GPIO_PA9, HAL_LL_TIM_INDEX_2, hal_ll_tim_module_num(OCR_MODULE_2) },
    #endif
    #ifdef PWM2_OC_RD1
    { GPIO_PD1, HAL_LL_TIM_INDEX_2, hal_ll_tim_module_num(OCR_MODULE_2) },
    #endif
    #ifdef PWM2_OC_RG9
    { GPIO_PG9, HAL_LL_TIM_INDEX_2, hal_ll_tim_module_num(OCR_MODULE_2) },
    #endif
    #ifdef PWM2_OC_RB14
    { GPIO_PB14, HAL_LL_TIM_INDEX_2, hal_ll_tim_module_num(OCR_MODULE_2) },
    #endif
    #ifdef PWM2_OC_RD0
    { GPIO_PD0, HAL_LL_TIM_INDEX_2, hal_ll_tim_module_num(OCR_MODULE_2) },
    #endif
    #ifdef PWM2_OC_RD8
    { GPIO_PD8, HAL_LL_TIM_INDEX_2, hal_ll_tim_module_num(OCR_MODULE_2) },
    #endif
    #ifdef PWM2_OC_RB6
    { GPIO_PB6, HAL_LL_TIM_INDEX_2, hal_ll_tim_module_num(OCR_MODULE_2) },
    #endif
    #ifdef PWM2_OC_RD5
    { GPIO_PD5, HAL_LL_TIM_INDEX_2, hal_ll_tim_module_num(OCR_MODULE_2) },
    #endif
    #ifdef PWM2_OC_RF3
    { GPIO_PF3, HAL_LL_TIM_INDEX_2, hal_ll_tim_module_num(OCR_MODULE_2) },
    #endif
    #ifdef PWM2_OC_RF6
    { GPIO_PF6, HAL_LL_TIM_INDEX_2, hal_ll_tim_module_num(OCR_MODULE_2) },
    #endif
    #ifdef PWM2_OC_RF13
    { GPIO_PF13, HAL_LL_TIM_INDEX_2, hal_ll_tim_module_num(OCR_MODULE_2) },
    #endif
    #ifdef PWM2_OC_RC2
    { GPIO_PC2, HAL_LL_TIM_INDEX_2, hal_ll_tim_module_num(OCR_MODULE_2) },
    #endif
    #ifdef PWM2_OC_RE8
    { GPIO_PE8, HAL_LL_TIM_INDEX_2, hal_ll_tim_module_num(OCR_MODULE_2) },
    #endif
    #ifdef PWM2_OC_RF2
    { GPIO_PF2, HAL_LL_TIM_INDEX_2, hal_ll_tim_module_num(OCR_MODULE_2) },
    #endif
    #ifdef PWM2_OC_RB2
    { GPIO_PB2, HAL_LL_TIM_INDEX_2, hal_ll_tim_module_num(OCR_MODULE_2) },
    #endif
    #endif

    #ifdef OCR_MODULE_3
    #ifdef PWM3_OC_RA3
    { GPIO_PA3, HAL_LL_TIM_INDEX_2, hal_ll_tim_module_num(OCR_MODULE_3) },
    #endif
    #ifdef PWM3_OC_RB14
    { GPIO_PB14, HAL_LL_TIM_INDEX_2, hal_ll_tim_module_num(OCR_MODULE_3) },
    #endif
    #ifdef PWM3_OC_RB0
    { GPIO_PB0, HAL_LL_TIM_INDEX_2, hal_ll_tim_module_num(OCR_MODULE_3) },
    #endif
    #ifdef PWM3_OC_RB10
    { GPIO_PB10, HAL_LL_TIM_INDEX_2, hal_ll_tim_module_num(OCR_MODULE_3) },
    #endif
    #ifdef PWM3_OC_RB9
    { GPIO_PB9, HAL_LL_TIM_INDEX_2, hal_ll_tim_module_num(OCR_MODULE_3) },
    #endif
    #ifdef PWM3_OC_RC9
    { GPIO_PC9, HAL_LL_TIM_INDEX_2, hal_ll_tim_module_num(OCR_MODULE_3) },
    #endif
    #ifdef PWM3_OC_RC2
    { GPIO_PC2, HAL_LL_TIM_INDEX_2, hal_ll_tim_module_num(OCR_MODULE_3) },
    #endif
    #ifdef PWM3_OC_RC4
    { GPIO_PC4, HAL_LL_TIM_INDEX_2, hal_ll_tim_module_num(OCR_MODULE_3) },
    #endif
    #ifdef PWM3_OC_RD2
    { GPIO_PD2, HAL_LL_TIM_INDEX_2, hal_ll_tim_module_num(OCR_MODULE_3) },
    #endif
    #ifdef PWM3_OC_RG8
    { GPIO_PG8, HAL_LL_TIM_INDEX_2, hal_ll_tim_module_num(OCR_MODULE_3) },
    #endif
    #ifdef PWM3_OC_RF4
    { GPIO_PF4, HAL_LL_TIM_INDEX_2, hal_ll_tim_module_num(OCR_MODULE_3) },
    #endif
    #ifdef PWM3_OC_RD10
    { GPIO_PD10, HAL_LL_TIM_INDEX_2, hal_ll_tim_module_num(OCR_MODULE_3) },
    #endif
    #ifdef PWM3_OC_RF1
    { GPIO_PF1, HAL_LL_TIM_INDEX_2, hal_ll_tim_module_num(OCR_MODULE_3) },
    #endif
    #ifdef PWM3_OC_RC14
    { GPIO_PC14, HAL_LL_TIM_INDEX_2, hal_ll_tim_module_num(OCR_MODULE_3) },
    #endif
    #ifdef PWM3_OC_RB5
    { GPIO_PB5, HAL_LL_TIM_INDEX_2, hal_ll_tim_module_num(OCR_MODULE_3) },
    #endif
    #ifdef PWM3_OC_RC1
    { GPIO_PC1, HAL_LL_TIM_INDEX_2, hal_ll_tim_module_num(OCR_MODULE_3) },
    #endif
    #ifdef PWM3_OC_RD14
    { GPIO_PD14, HAL_LL_TIM_INDEX_2, hal_ll_tim_module_num(OCR_MODULE_3) },
    #endif
    #ifdef PWM3_OC_RG1
    { GPIO_PG1, HAL_LL_TIM_INDEX_2, hal_ll_tim_module_num(OCR_MODULE_3) },
    #endif
    #ifdef PWM3_OC_RA14
    { GPIO_PA14, HAL_LL_TIM_INDEX_2, hal_ll_tim_module_num(OCR_MODULE_3) },
    #endif
    #ifdef PWM3_OC_RD6
    { GPIO_PD6, HAL_LL_TIM_INDEX_2, hal_ll_tim_module_num(OCR_MODULE_3) },
    #endif
    #endif

    #ifdef OCR_MODULE_4
    #ifdef PWM4_OC_RA2
    { GPIO_PA2, HAL_LL_TIM_INDEX_2, hal_ll_tim_module_num(OCR_MODULE_4) },
    #endif
    #ifdef PWM4_OC_RB6
    { GPIO_PB6, HAL_LL_TIM_INDEX_2, hal_ll_tim_module_num(OCR_MODULE_4) },
    #endif
    #ifdef PWM4_OC_RA4
    { GPIO_PA4, HAL_LL_TIM_INDEX_2, hal_ll_tim_module_num(OCR_MODULE_4) },
    #endif
    #ifdef PWM4_OC_RB13
    { GPIO_PB13, HAL_LL_TIM_INDEX_2, hal_ll_tim_module_num(OCR_MODULE_4) },
    #endif
    #ifdef PWM4_OC_RB2
    { GPIO_PB2, HAL_LL_TIM_INDEX_2, hal_ll_tim_module_num(OCR_MODULE_4) },
    #endif
    #ifdef PWM4_OC_RC1
    { GPIO_PC1, HAL_LL_TIM_INDEX_2, hal_ll_tim_module_num(OCR_MODULE_4) },
    #endif
    #ifdef PWM4_OC_RC3
    { GPIO_PC3, HAL_LL_TIM_INDEX_2, hal_ll_tim_module_num(OCR_MODULE_4) },
    #endif
    #ifdef PWM4_OC_RC6
    { GPIO_PC6, HAL_LL_TIM_INDEX_2, hal_ll_tim_module_num(OCR_MODULE_4) },
    #endif
    #ifdef PWM4_OC_RD3
    { GPIO_PD3, HAL_LL_TIM_INDEX_2, hal_ll_tim_module_num(OCR_MODULE_4) },
    #endif
    #ifdef PWM4_OC_RG7
    { GPIO_PG7, HAL_LL_TIM_INDEX_2, hal_ll_tim_module_num(OCR_MODULE_4) },
    #endif
    #ifdef PWM4_OC_RF5
    { GPIO_PF5, HAL_LL_TIM_INDEX_2, hal_ll_tim_module_num(OCR_MODULE_4) },
    #endif
    #ifdef PWM4_OC_RD11
    { GPIO_PD11, HAL_LL_TIM_INDEX_2, hal_ll_tim_module_num(OCR_MODULE_4) },
    #endif
    #ifdef PWM4_OC_RF0
    { GPIO_PF0, HAL_LL_TIM_INDEX_2, hal_ll_tim_module_num(OCR_MODULE_4) },
    #endif
    #ifdef PWM4_OC_RB1
    { GPIO_PB1, HAL_LL_TIM_INDEX_2, hal_ll_tim_module_num(OCR_MODULE_4) },
    #endif
    #ifdef PWM4_OC_RE5
    { GPIO_PE5, HAL_LL_TIM_INDEX_2, hal_ll_tim_module_num(OCR_MODULE_4) },
    #endif
    #ifdef PWM4_OC_RC13
    { GPIO_PC13, HAL_LL_TIM_INDEX_2, hal_ll_tim_module_num(OCR_MODULE_4) },
    #endif
    #ifdef PWM4_OC_RB3
    { GPIO_PB3, HAL_LL_TIM_INDEX_2, hal_ll_tim_module_num(OCR_MODULE_4) },
    #endif
    #ifdef PWM4_OC_RF3
    { GPIO_PF3, HAL_LL_TIM_INDEX_2, hal_ll_tim_module_num(OCR_MODULE_4) },
    #endif
    #ifdef PWM4_OC_RC4
    { GPIO_PC4, HAL_LL_TIM_INDEX_2, hal_ll_tim_module_num(OCR_MODULE_4) },
    #endif
    #ifdef PWM4_OC_RD15
    { GPIO_PD15, HAL_LL_TIM_INDEX_2, hal_ll_tim_module_num(OCR_MODULE_4) },
    #endif
    #ifdef PWM4_OC_RG0
    { GPIO_PG0, HAL_LL_TIM_INDEX_2, hal_ll_tim_module_num(OCR_MODULE_4) },
    #endif
    #ifdef PWM4_OC_RA15
    { GPIO_PA15, HAL_LL_TIM_INDEX_2, hal_ll_tim_module_num(OCR_MODULE_4) },
    #endif
    #ifdef PWM4_OC_RD7
    { GPIO_PD7, HAL_LL_TIM_INDEX_2, hal_ll_tim_module_num(OCR_MODULE_4) },
    #endif
    #endif

    #ifdef OCR_MODULE_5
    #ifdef PWM5_OC_RA2
    { GPIO_PA2, HAL_LL_TIM_INDEX_2, hal_ll_tim_module_num(OCR_MODULE_5) },
    #endif
    #ifdef PWM5_OC_RB6
    { GPIO_PB6, HAL_LL_TIM_INDEX_2, hal_ll_tim_module_num(OCR_MODULE_5) },
    #endif
    #ifdef PWM5_OC_RA4
    { GPIO_PA4, HAL_LL_TIM_INDEX_2, hal_ll_tim_module_num(OCR_MODULE_5) },
    #endif
    #ifdef PWM5_OC_RB13
    { GPIO_PB13, HAL_LL_TIM_INDEX_2, hal_ll_tim_module_num(OCR_MODULE_5) },
    #endif
    #ifdef PWM5_OC_RB2
    { GPIO_PB2, HAL_LL_TIM_INDEX_2, hal_ll_tim_module_num(OCR_MODULE_5) },
    #endif
    #ifdef PWM5_OC_RC1
    { GPIO_PC1, HAL_LL_TIM_INDEX_2, hal_ll_tim_module_num(OCR_MODULE_5) },
    #endif
    #ifdef PWM5_OC_RC3
    { GPIO_PC3, HAL_LL_TIM_INDEX_2, hal_ll_tim_module_num(OCR_MODULE_5) },
    #endif
    #ifdef PWM5_OC_RC6
    { GPIO_PC6, HAL_LL_TIM_INDEX_2, hal_ll_tim_module_num(OCR_MODULE_5) },
    #endif
    #ifdef PWM5_OC_RD9
    { GPIO_PD9, HAL_LL_TIM_INDEX_2, hal_ll_tim_module_num(OCR_MODULE_5) },
    #endif
    #ifdef PWM5_OC_RG6
    { GPIO_PG6, HAL_LL_TIM_INDEX_2, hal_ll_tim_module_num(OCR_MODULE_5) },
    #endif
    #ifdef PWM5_OC_RB8
    { GPIO_PB8, HAL_LL_TIM_INDEX_2, hal_ll_tim_module_num(OCR_MODULE_5) },
    #endif
    #ifdef PWM5_OC_RB15
    { GPIO_PB15, HAL_LL_TIM_INDEX_2, hal_ll_tim_module_num(OCR_MODULE_5) },
    #endif
    #ifdef PWM5_OC_RD4
    { GPIO_PD4, HAL_LL_TIM_INDEX_2, hal_ll_tim_module_num(OCR_MODULE_5) },
    #endif
    #ifdef PWM5_OC_RB0
    { GPIO_PB0, HAL_LL_TIM_INDEX_2, hal_ll_tim_module_num(OCR_MODULE_5) },
    #endif
    #ifdef PWM5_OC_RE3
    { GPIO_PE3, HAL_LL_TIM_INDEX_2, hal_ll_tim_module_num(OCR_MODULE_5) },
    #endif
    #ifdef PWM5_OC_RB7
    { GPIO_PB7, HAL_LL_TIM_INDEX_2, hal_ll_tim_module_num(OCR_MODULE_5) },
    #endif
    #ifdef PWM5_OC_RF12
    { GPIO_PF12, HAL_LL_TIM_INDEX_2, hal_ll_tim_module_num(OCR_MODULE_5) },
    #endif
    #ifdef PWM5_OC_RD12
    { GPIO_PD12, HAL_LL_TIM_INDEX_2, hal_ll_tim_module_num(OCR_MODULE_5) },
    #endif
    #ifdef PWM5_OC_RF8
    { GPIO_PF8, HAL_LL_TIM_INDEX_2, hal_ll_tim_module_num(OCR_MODULE_5) },
    #endif
    #ifdef PWM5_OC_RE9
    { GPIO_PE9, HAL_LL_TIM_INDEX_2, hal_ll_tim_module_num(OCR_MODULE_5) },
    #endif
    #endif

    #ifdef OCR_MODULE_6
    #ifdef PWM6_OC_RD2
    { GPIO_PD2, HAL_LL_TIM_INDEX_2, hal_ll_tim_module_num(OCR_MODULE_6) },
    #endif
    #ifdef PWM6_OC_RG8
    { GPIO_PG8, HAL_LL_TIM_INDEX_2, hal_ll_tim_module_num(OCR_MODULE_6) },
    #endif
    #ifdef PWM6_OC_RF4
    { GPIO_PF4, HAL_LL_TIM_INDEX_2, hal_ll_tim_module_num(OCR_MODULE_6) },
    #endif
    #ifdef PWM6_OC_RD10
    { GPIO_PD10, HAL_LL_TIM_INDEX_2, hal_ll_tim_module_num(OCR_MODULE_6) },
    #endif
    #ifdef PWM6_OC_RF1
    { GPIO_PF1, HAL_LL_TIM_INDEX_2, hal_ll_tim_module_num(OCR_MODULE_6) },
    #endif
    #ifdef PWM6_OC_RB9
    { GPIO_PB9, HAL_LL_TIM_INDEX_2, hal_ll_tim_module_num(OCR_MODULE_6) },
    #endif
    #ifdef PWM6_OC_RB10
    { GPIO_PB10, HAL_LL_TIM_INDEX_2, hal_ll_tim_module_num(OCR_MODULE_6) },
    #endif
    #ifdef PWM6_OC_RC14
    { GPIO_PC14, HAL_LL_TIM_INDEX_2, hal_ll_tim_module_num(OCR_MODULE_6) },
    #endif
    #ifdef PWM6_OC_RB5
    { GPIO_PB5, HAL_LL_TIM_INDEX_2, hal_ll_tim_module_num(OCR_MODULE_6) },
    #endif
    #ifdef PWM6_OC_RC1
    { GPIO_PC1, HAL_LL_TIM_INDEX_2, hal_ll_tim_module_num(OCR_MODULE_6) },
    #endif
    #ifdef PWM6_OC_RD14
    { GPIO_PD14, HAL_LL_TIM_INDEX_2, hal_ll_tim_module_num(OCR_MODULE_6) },
    #endif
    #ifdef PWM6_OC_RG1
    { GPIO_PG1, HAL_LL_TIM_INDEX_2, hal_ll_tim_module_num(OCR_MODULE_6) },
    #endif
    #ifdef PWM6_OC_RA14
    { GPIO_PA14, HAL_LL_TIM_INDEX_2, hal_ll_tim_module_num(OCR_MODULE_6) },
    #endif
    #ifdef PWM6_OC_RD6
    { GPIO_PD6, HAL_LL_TIM_INDEX_2, hal_ll_tim_module_num(OCR_MODULE_6) },
    #endif
    #endif

    #ifdef OCR_MODULE_7
    #ifdef PWM7_OC_RD3
    { GPIO_PD3, HAL_LL_TIM_INDEX_2, hal_ll_tim_module_num(OCR_MODULE_7) },
    #endif
    #ifdef PWM7_OC_RG7
    { GPIO_PG7, HAL_LL_TIM_INDEX_2, hal_ll_tim_module_num(OCR_MODULE_7) },
    #endif
    #ifdef PWM7_OC_RF5
    { GPIO_PF5, HAL_LL_TIM_INDEX_2, hal_ll_tim_module_num(OCR_MODULE_7) },
    #endif
    #ifdef PWM7_OC_RD11
    { GPIO_PD11, HAL_LL_TIM_INDEX_2, hal_ll_tim_module_num(OCR_MODULE_7) },
    #endif
    #ifdef PWM7_OC_RF0
    { GPIO_PF0, HAL_LL_TIM_INDEX_2, hal_ll_tim_module_num(OCR_MODULE_7) },
    #endif
    #ifdef PWM7_OC_RB1
    { GPIO_PB1, HAL_LL_TIM_INDEX_2, hal_ll_tim_module_num(OCR_MODULE_7) },
    #endif
    #ifdef PWM7_OC_RE5
    { GPIO_PE5, HAL_LL_TIM_INDEX_2, hal_ll_tim_module_num(OCR_MODULE_7) },
    #endif
    #ifdef PWM7_OC_RC13
    { GPIO_PC13, HAL_LL_TIM_INDEX_2, hal_ll_tim_module_num(OCR_MODULE_7) },
    #endif
    #ifdef PWM7_OC_RB3
    { GPIO_PB3, HAL_LL_TIM_INDEX_2, hal_ll_tim_module_num(OCR_MODULE_7) },
    #endif
    #ifdef PWM7_OC_RC4
    { GPIO_PC4, HAL_LL_TIM_INDEX_2, hal_ll_tim_module_num(OCR_MODULE_7) },
    #endif
    #ifdef PWM7_OC_RD15
    { GPIO_PD15, HAL_LL_TIM_INDEX_2, hal_ll_tim_module_num(OCR_MODULE_7) },
    #endif
    #ifdef PWM7_OC_RG0
    { GPIO_PG0, HAL_LL_TIM_INDEX_2, hal_ll_tim_module_num(OCR_MODULE_7) },
    #endif
    #ifdef PWM7_OC_RA15
    { GPIO_PA15, HAL_LL_TIM_INDEX_2, hal_ll_tim_module_num(OCR_MODULE_7) },
    #endif
    #ifdef PWM7_OC_RD7
    { GPIO_PD7, HAL_LL_TIM_INDEX_2, hal_ll_tim_module_num(OCR_MODULE_7) },
    #endif
    #endif

    #ifdef OCR_MODULE_8
    #ifdef PWM8_OC_RD9
    { GPIO_PD9, HAL_LL_TIM_INDEX_2, hal_ll_tim_module_num(OCR_MODULE_8) },
    #endif
    #ifdef PWM8_OC_RG6
    { GPIO_PG6, HAL_LL_TIM_INDEX_2, hal_ll_tim_module_num(OCR_MODULE_8) },
    #endif
    #ifdef PWM8_OC_RB8
    { GPIO_PB8, HAL_LL_TIM_INDEX_2, hal_ll_tim_module_num(OCR_MODULE_8) },
    #endif
    #ifdef PWM8_OC_RB15
    { GPIO_PB15, HAL_LL_TIM_INDEX_2, hal_ll_tim_module_num(OCR_MODULE_8) },
    #endif
    #ifdef PWM8_OC_RD4
    { GPIO_PD4, HAL_LL_TIM_INDEX_2, hal_ll_tim_module_num(OCR_MODULE_8) },
    #endif
    #ifdef PWM8_OC_RB0
    { GPIO_PB0, HAL_LL_TIM_INDEX_2, hal_ll_tim_module_num(OCR_MODULE_8) },
    #endif
    #ifdef PWM8_OC_RE3
    { GPIO_PE3, HAL_LL_TIM_INDEX_2, hal_ll_tim_module_num(OCR_MODULE_8) },
    #endif
    #ifdef PWM8_OC_RB7
    { GPIO_PB7, HAL_LL_TIM_INDEX_2, hal_ll_tim_module_num(OCR_MODULE_8) },
    #endif
    #ifdef PWM8_OC_RF12
    { GPIO_PF12, HAL_LL_TIM_INDEX_2, hal_ll_tim_module_num(OCR_MODULE_8) },
    #endif
    #ifdef PWM8_OC_RD12
    { GPIO_PD12, HAL_LL_TIM_INDEX_2, hal_ll_tim_module_num(OCR_MODULE_8) },
    #endif
    #ifdef PWM8_OC_RF8
    { GPIO_PF8, HAL_LL_TIM_INDEX_2, hal_ll_tim_module_num(OCR_MODULE_8) },
    #endif
    #ifdef PWM8_OC_RC3
    { GPIO_PC3, HAL_LL_TIM_INDEX_2, hal_ll_tim_module_num(OCR_MODULE_8) },
    #endif
    #ifdef PWM8_OC_RE9
    { GPIO_PE9, HAL_LL_TIM_INDEX_2, hal_ll_tim_module_num(OCR_MODULE_8) },
    #endif
    #endif

    #ifdef OCR_MODULE_9
    #ifdef PWM9_OC_RD1
    { GPIO_PD1, HAL_LL_TIM_INDEX_2, hal_ll_tim_module_num(OCR_MODULE_9) },
    #endif
    #ifdef PWM9_OC_RG9
    { GPIO_PG9, HAL_LL_TIM_INDEX_2, hal_ll_tim_module_num(OCR_MODULE_9) },
    #endif
    #ifdef PWM9_OC_RB14
    { GPIO_PB14, HAL_LL_TIM_INDEX_2, hal_ll_tim_module_num(OCR_MODULE_9) },
    #endif
    #ifdef PWM9_OC_RD0
    { GPIO_PD0, HAL_LL_TIM_INDEX_2, hal_ll_tim_module_num(OCR_MODULE_9) },
    #endif
    #ifdef PWM9_OC_RB6
    { GPIO_PB6, HAL_LL_TIM_INDEX_2, hal_ll_tim_module_num(OCR_MODULE_9) },
    #endif
    #ifdef PWM9_OC_RD5
    { GPIO_PD5, HAL_LL_TIM_INDEX_2, hal_ll_tim_module_num(OCR_MODULE_9) },
    #endif
    #ifdef PWM9_OC_RB2
    { GPIO_PB2, HAL_LL_TIM_INDEX_2, hal_ll_tim_module_num(OCR_MODULE_9) },
    #endif
    #ifdef PWM9_OC_RF3
    { GPIO_PF3, HAL_LL_TIM_INDEX_2, hal_ll_tim_module_num(OCR_MODULE_9) },
    #endif
    #ifdef PWM9_OC_RF13
    { GPIO_PF13, HAL_LL_TIM_INDEX_2, hal_ll_tim_module_num(OCR_MODULE_9) },
    #endif
    #ifdef PWM9_OC_RF2
    { GPIO_PF2, HAL_LL_TIM_INDEX_2, hal_ll_tim_module_num(OCR_MODULE_9) },
    #endif
    #ifdef PWM9_OC_RC2
    { GPIO_PC2, HAL_LL_TIM_INDEX_2, hal_ll_tim_module_num(OCR_MODULE_9) },
    #endif
    #ifdef PWM9_OC_RE8
    { GPIO_PE8, HAL_LL_TIM_INDEX_2, hal_ll_tim_module_num(OCR_MODULE_9) },
    #endif
    #endif


    { HAL_LL_PIN_NC, HAL_LL_MODULE_ERROR, HAL_LL_MODULE_ERROR }
    //------------ END CCP
};

#ifdef __cplusplus
}
#endif

#endif // _HAL_LL_TIM_PIN_MAP_H_
// ---------------------------------------------------------------------- END
