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

typedef struct
{
    uint8_t pin;
    uint8_t module_index;
    uint8_t channel;
    uint8_t analog_in_register_bit;
    uint32_t analog_in_register_addr;
} hal_ll_pin_channel_list_t;

static const hal_ll_pin_channel_list_t hal_ll_analog_in_register_list[HAL_LL_AN_COUNT+1] =
{
    #ifdef HAL_LL_RA0_AN0
    { GPIO_PA0, 0, HAL_LL_RA0_AN0, 0, HAL_LL_RA0_AN0_ADDRESS },
    #endif
    #ifdef HAL_LL_RA1_AN1
    { GPIO_PA1, 0, HAL_LL_RA1_AN1, 1, HAL_LL_RA1_AN1_ADDRESS },
    #endif
    #ifdef HAL_LL_RB0_AN2
    { GPIO_PB0, 0, HAL_LL_RB0_AN2, 0, HAL_LL_RB0_AN2_ADDRESS },
    #endif
    #ifdef HAL_LL_RB1_AN3
    { GPIO_PB1, 0, HAL_LL_RB1_AN3, 1, HAL_LL_RB1_AN3_ADDRESS },
    #endif
    #ifdef HAL_LL_RB12_AN12
    { GPIO_PB12, 0, HAL_LL_RB12_AN12, 12, HAL_LL_RB12_AN12_ADDRESS },
    #endif
    #ifdef HAL_LL_RB13_AN11
    { GPIO_PB13, 0, HAL_LL_RB13_AN11, 13, HAL_LL_RB13_AN11_ADDRESS },
    #endif
    #ifdef HAL_LL_RB14_AN10
    { GPIO_PB14, 0, HAL_LL_RB14_AN10, 14, HAL_LL_RB14_AN10_ADDRESS },
    #endif
    #ifdef HAL_LL_RB15_AN9
    { GPIO_PB15, 0, HAL_LL_RB15_AN9, 15, HAL_LL_RB15_AN9_ADDRESS },
    #endif
    #ifdef HAL_LL_RB2_AN4
    { GPIO_PB2, 0, HAL_LL_RB2_AN4, 2, HAL_LL_RB2_AN4_ADDRESS },
    #endif
    #ifdef HAL_LL_RB3_AN5
    { GPIO_PB3, 0, HAL_LL_RB3_AN5, 3, HAL_LL_RB3_AN5_ADDRESS },
    #endif
    #ifdef HAL_LL_RC0_AN6
    { GPIO_PC0, 0, HAL_LL_RC0_AN6, 0, HAL_LL_RC0_AN6_ADDRESS },
    #endif
    #ifdef HAL_LL_RC1_AN7
    { GPIO_PC1, 0, HAL_LL_RC1_AN7, 1, HAL_LL_RC1_AN7_ADDRESS },
    #endif
    #ifdef HAL_LL_RC2_AN8
    { GPIO_PC2, 0, HAL_LL_RC2_AN8, 2, HAL_LL_RC2_AN8_ADDRESS },
    #endif
    #ifdef HAL_LL_RB0_AN0
    { GPIO_PB0, 0, HAL_LL_RB0_AN0, 0, HAL_LL_RB0_AN0_ADDRESS },
    #endif
    #ifdef HAL_LL_RB1_AN1
    { GPIO_PB1, 0, HAL_LL_RB1_AN1, 1, HAL_LL_RB1_AN1_ADDRESS },
    #endif
    #ifdef HAL_LL_RB10_AN10
    { GPIO_PB10, 0, HAL_LL_RB10_AN10, 10, HAL_LL_RB10_AN10_ADDRESS },
    #endif
    #ifdef HAL_LL_RB11_AN11
    { GPIO_PB11, 0, HAL_LL_RB11_AN11, 11, HAL_LL_RB11_AN11_ADDRESS },
    #endif
    #ifdef HAL_LL_RB13_AN13
    { GPIO_PB13, 0, HAL_LL_RB13_AN13, 13, HAL_LL_RB13_AN13_ADDRESS },
    #endif
    #ifdef HAL_LL_RB14_AN14
    { GPIO_PB14, 0, HAL_LL_RB14_AN14, 14, HAL_LL_RB14_AN14_ADDRESS },
    #endif
    #ifdef HAL_LL_RB15_AN15
    { GPIO_PB15, 0, HAL_LL_RB15_AN15, 15, HAL_LL_RB15_AN15_ADDRESS },
    #endif
    #ifdef HAL_LL_RB2_AN2
    { GPIO_PB2, 0, HAL_LL_RB2_AN2, 2, HAL_LL_RB2_AN2_ADDRESS },
    #endif
    #ifdef HAL_LL_RB3_AN3
    { GPIO_PB3, 0, HAL_LL_RB3_AN3, 3, HAL_LL_RB3_AN3_ADDRESS },
    #endif
    #ifdef HAL_LL_RB4_AN4
    { GPIO_PB4, 0, HAL_LL_RB4_AN4, 4, HAL_LL_RB4_AN4_ADDRESS },
    #endif
    #ifdef HAL_LL_RB5_AN5
    { GPIO_PB5, 0, HAL_LL_RB5_AN5, 5, HAL_LL_RB5_AN5_ADDRESS },
    #endif
    #ifdef HAL_LL_RB6_AN6
    { GPIO_PB6, 0, HAL_LL_RB6_AN6, 6, HAL_LL_RB6_AN6_ADDRESS },
    #endif
    #ifdef HAL_LL_RB7_AN7
    { GPIO_PB7, 0, HAL_LL_RB7_AN7, 7, HAL_LL_RB7_AN7_ADDRESS },
    #endif
    #ifdef HAL_LL_RB8_AN8
    { GPIO_PB8, 0, HAL_LL_RB8_AN8, 8, HAL_LL_RB8_AN8_ADDRESS },
    #endif
    #ifdef HAL_LL_RB9_AN9
    { GPIO_PB9, 0, HAL_LL_RB9_AN9, 9, HAL_LL_RB9_AN9_ADDRESS },
    #endif
    #ifdef HAL_LL_RD1_AN24
    { GPIO_PD1, 0, HAL_LL_RD1_AN24, 1, HAL_LL_RD1_AN24_ADDRESS },
    #endif
    #ifdef HAL_LL_RD2_AN25
    { GPIO_PD2, 0, HAL_LL_RD2_AN25, 2, HAL_LL_RD2_AN25_ADDRESS },
    #endif
    #ifdef HAL_LL_RD3_AN26
    { GPIO_PD3, 0, HAL_LL_RD3_AN26, 3, HAL_LL_RD3_AN26_ADDRESS },
    #endif
    #ifdef HAL_LL_RE2_AN20
    { GPIO_PE2, 0, HAL_LL_RE2_AN20, 2, HAL_LL_RE2_AN20_ADDRESS },
    #endif
    #ifdef HAL_LL_RE4_AN21
    { GPIO_PE4, 0, HAL_LL_RE4_AN21, 4, HAL_LL_RE4_AN21_ADDRESS },
    #endif
    #ifdef HAL_LL_RE5_AN22
    { GPIO_PE5, 0, HAL_LL_RE5_AN22, 5, HAL_LL_RE5_AN22_ADDRESS },
    #endif
    #ifdef HAL_LL_RE6_AN23
    { GPIO_PE6, 0, HAL_LL_RE6_AN23, 6, HAL_LL_RE6_AN23_ADDRESS },
    #endif
    #ifdef HAL_LL_RE7_AN27
    { GPIO_PE7, 0, HAL_LL_RE7_AN27, 7, HAL_LL_RE7_AN27_ADDRESS },
    #endif
    #ifdef HAL_LL_RG6_AN16
    { GPIO_PG6, 0, HAL_LL_RG6_AN16, 6, HAL_LL_RG6_AN16_ADDRESS },
    #endif
    #ifdef HAL_LL_RG7_AN17
    { GPIO_PG7, 0, HAL_LL_RG7_AN17, 7, HAL_LL_RG7_AN17_ADDRESS },
    #endif
    #ifdef HAL_LL_RG8_AN18
    { GPIO_PG8, 0, HAL_LL_RG8_AN18, 8, HAL_LL_RG8_AN18_ADDRESS },
    #endif
    #ifdef HAL_LL_RG9_AN19
    { GPIO_PG9, 0, HAL_LL_RG9_AN19, 9, HAL_LL_RG9_AN19_ADDRESS },
    #endif
    #ifdef HAL_LL_RC1_AN29
    { GPIO_PC1, 0, HAL_LL_RC1_AN29, 1, HAL_LL_RC1_AN29_ADDRESS },
    #endif
    #ifdef HAL_LL_RC2_AN30
    { GPIO_PC2, 0, HAL_LL_RC2_AN30, 2, HAL_LL_RC2_AN30_ADDRESS },
    #endif
    #ifdef HAL_LL_RC3_AN31
    { GPIO_PC3, 0, HAL_LL_RC3_AN31, 3, HAL_LL_RC3_AN31_ADDRESS },
    #endif
    #ifdef HAL_LL_RD12_AN40
    { GPIO_PD12, 0, HAL_LL_RD12_AN40, 12, HAL_LL_RD12_AN40_ADDRESS },
    #endif
    #ifdef HAL_LL_RD13_AN41
    { GPIO_PD13, 0, HAL_LL_RD13_AN41, 13, HAL_LL_RD13_AN41_ADDRESS },
    #endif
    #ifdef HAL_LL_RD14_AN36
    { GPIO_PD14, 0, HAL_LL_RD14_AN36, 14, HAL_LL_RD14_AN36_ADDRESS },
    #endif
    #ifdef HAL_LL_RD15_AN37
    { GPIO_PD15, 0, HAL_LL_RD15_AN37, 15, HAL_LL_RD15_AN37_ADDRESS },
    #endif
    #ifdef HAL_LL_RD6_AN42
    { GPIO_PD6, 0, HAL_LL_RD6_AN42, 6, HAL_LL_RD6_AN42_ADDRESS },
    #endif
    #ifdef HAL_LL_RD7_AN43
    { GPIO_PD7, 0, HAL_LL_RD7_AN43, 7, HAL_LL_RD7_AN43_ADDRESS },
    #endif
    #ifdef HAL_LL_RE0_AN46
    { GPIO_PE0, 0, HAL_LL_RE0_AN46, 0, HAL_LL_RE0_AN46_ADDRESS },
    #endif
    #ifdef HAL_LL_RE1_AN47
    { GPIO_PE1, 0, HAL_LL_RE1_AN47, 1, HAL_LL_RE1_AN47_ADDRESS },
    #endif
    #ifdef HAL_LL_RE8_AN32
    { GPIO_PE8, 0, HAL_LL_RE8_AN32, 8, HAL_LL_RE8_AN32_ADDRESS },
    #endif
    #ifdef HAL_LL_RE9_AN33
    { GPIO_PE9, 0, HAL_LL_RE9_AN33, 9, HAL_LL_RE9_AN33_ADDRESS },
    #endif
    #ifdef HAL_LL_RF0_AN44
    { GPIO_PF0, 0, HAL_LL_RF0_AN44, 0, HAL_LL_RF0_AN44_ADDRESS },
    #endif
    #ifdef HAL_LL_RF1_AN45
    { GPIO_PF1, 0, HAL_LL_RF1_AN45, 1, HAL_LL_RF1_AN45_ADDRESS },
    #endif
    #ifdef HAL_LL_RF12_AN35
    { GPIO_PF12, 0, HAL_LL_RF12_AN35, 12, HAL_LL_RF12_AN35_ADDRESS },
    #endif
    #ifdef HAL_LL_RF13_AN34
    { GPIO_PF13, 0, HAL_LL_RF13_AN34, 13, HAL_LL_RF13_AN34_ADDRESS },
    #endif
    #ifdef HAL_LL_RF2_AN38
    { GPIO_PF2, 0, HAL_LL_RF2_AN38, 2, HAL_LL_RF2_AN38_ADDRESS },
    #endif
    #ifdef HAL_LL_RF8_AN39
    { GPIO_PF8, 0, HAL_LL_RF8_AN39, 8, HAL_LL_RF8_AN39_ADDRESS },
    #endif
    #ifdef HAL_LL_RG15_AN28
    { GPIO_PG15, 0, HAL_LL_RG15_AN28, 15, HAL_LL_RG15_AN28_ADDRESS },
    #endif
    #ifdef HAL_LL_RC3_AN12
    { GPIO_PC3, 0, HAL_LL_RC3_AN12, 3, HAL_LL_RC3_AN12_ADDRESS },
    #endif
    #ifdef HAL_LL_RB0_AN0_ANSELB
    { GPIO_PB0, 0, HAL_LL_RB0_AN0_ANSELB, HAL_LL_RB0_AN0_ANSELB_BIT , HAL_LL_ANSELB_ADDRESS },
    #endif
    #ifdef HAL_LL_RB1_AN1_ANSELB
    { GPIO_PB1, 0, HAL_LL_RB1_AN1_ANSELB, HAL_LL_RB1_AN1_ANSELB_BIT , HAL_LL_ANSELB_ADDRESS },
    #endif
    #ifdef HAL_LL_RB10_AN5_ANSELB
    { GPIO_PB10, 0, HAL_LL_RB10_AN5_ANSELB, HAL_LL_RB10_AN5_ANSELB_BIT , HAL_LL_ANSELB_ADDRESS },
    #endif
    #ifdef HAL_LL_RB11_AN6_ANSELB
    { GPIO_PB11, 0, HAL_LL_RB11_AN6_ANSELB, HAL_LL_RB11_AN6_ANSELB_BIT , HAL_LL_ANSELB_ADDRESS },
    #endif
    #ifdef HAL_LL_RB12_AN7_ANSELB
    { GPIO_PB12, 0, HAL_LL_RB12_AN7_ANSELB, HAL_LL_RB12_AN7_ANSELB_BIT , HAL_LL_ANSELB_ADDRESS },
    #endif
    #ifdef HAL_LL_RB13_AN8_ANSELB
    { GPIO_PB13, 0, HAL_LL_RB13_AN8_ANSELB, HAL_LL_RB13_AN8_ANSELB_BIT , HAL_LL_ANSELB_ADDRESS },
    #endif
    #ifdef HAL_LL_RB14_AN9_ANSELB
    { GPIO_PB14, 0, HAL_LL_RB14_AN9_ANSELB, HAL_LL_RB14_AN9_ANSELB_BIT , HAL_LL_ANSELB_ADDRESS },
    #endif
    #ifdef HAL_LL_RB15_AN10_ANSELB
    { GPIO_PB15, 0, HAL_LL_RB15_AN10_ANSELB, HAL_LL_RB15_AN10_ANSELB_BIT , HAL_LL_ANSELB_ADDRESS },
    #endif
    #ifdef HAL_LL_RB2_AN2_ANSELB
    { GPIO_PB2, 0, HAL_LL_RB2_AN2_ANSELB, HAL_LL_RB2_AN2_ANSELB_BIT , HAL_LL_ANSELB_ADDRESS },
    #endif
    #ifdef HAL_LL_RB3_AN3_ANSELB
    { GPIO_PB3, 0, HAL_LL_RB3_AN3_ANSELB, HAL_LL_RB3_AN3_ANSELB_BIT , HAL_LL_ANSELB_ADDRESS },
    #endif
    #ifdef HAL_LL_RB4_AN4_ANSELB
    { GPIO_PB4, 0, HAL_LL_RB4_AN4_ANSELB, HAL_LL_RB4_AN4_ANSELB_BIT , HAL_LL_ANSELB_ADDRESS },
    #endif
    #ifdef HAL_LL_RB5_AN45_ANSELB
    { GPIO_PB5, 0, HAL_LL_RB5_AN45_ANSELB, HAL_LL_RB5_AN45_ANSELB_BIT , HAL_LL_ANSELB_ADDRESS },
    #endif
    #ifdef HAL_LL_RB6_AN46_ANSELB
    { GPIO_PB6, 0, HAL_LL_RB6_AN46_ANSELB, HAL_LL_RB6_AN46_ANSELB_BIT , HAL_LL_ANSELB_ADDRESS },
    #endif
    #ifdef HAL_LL_RB7_AN47_ANSELB
    { GPIO_PB7, 0, HAL_LL_RB7_AN47_ANSELB, HAL_LL_RB7_AN47_ANSELB_BIT , HAL_LL_ANSELB_ADDRESS },
    #endif
    #ifdef HAL_LL_RB8_AN48_ANSELB
    { GPIO_PB8, 0, HAL_LL_RB8_AN48_ANSELB, HAL_LL_RB8_AN48_ANSELB_BIT , HAL_LL_ANSELB_ADDRESS },
    #endif
    #ifdef HAL_LL_RB9_AN49_ANSELB
    { GPIO_PB9, 0, HAL_LL_RB9_AN49_ANSELB, HAL_LL_RB9_AN49_ANSELB_BIT , HAL_LL_ANSELB_ADDRESS },
    #endif
    #ifdef HAL_LL_RE4_AN18_ANSELE
    { GPIO_PE4, 0, HAL_LL_RE4_AN18_ANSELE, HAL_LL_RE4_AN18_ANSELE_BIT , HAL_LL_ANSELE_ADDRESS },
    #endif
    #ifdef HAL_LL_RE5_AN17_ANSELE
    { GPIO_PE5, 0, HAL_LL_RE5_AN17_ANSELE, HAL_LL_RE5_AN17_ANSELE_BIT , HAL_LL_ANSELE_ADDRESS },
    #endif
    #ifdef HAL_LL_RE6_AN16_ANSELE
    { GPIO_PE6, 0, HAL_LL_RE6_AN16_ANSELE, HAL_LL_RE6_AN16_ANSELE_BIT , HAL_LL_ANSELE_ADDRESS },
    #endif
    #ifdef HAL_LL_RE7_AN15_ANSELE
    { GPIO_PE7, 0, HAL_LL_RE7_AN15_ANSELE, HAL_LL_RE7_AN15_ANSELE_BIT , HAL_LL_ANSELE_ADDRESS },
    #endif
    #ifdef HAL_LL_RG6_AN14_ANSELG
    { GPIO_PG6, 0, HAL_LL_RG6_AN14_ANSELG, HAL_LL_RG6_AN14_ANSELG_BIT , HAL_LL_ANSELG_ADDRESS },
    #endif
    #ifdef HAL_LL_RG7_AN13_ANSELG
    { GPIO_PG7, 0, HAL_LL_RG7_AN13_ANSELG, HAL_LL_RG7_AN13_ANSELG_BIT , HAL_LL_ANSELG_ADDRESS },
    #endif
    #ifdef HAL_LL_RG8_AN12_ANSELG
    { GPIO_PG8, 0, HAL_LL_RG8_AN12_ANSELG, HAL_LL_RG8_AN12_ANSELG_BIT , HAL_LL_ANSELG_ADDRESS },
    #endif
    #ifdef HAL_LL_RG9_AN11_ANSELG
    { GPIO_PG9, 0, HAL_LL_RG9_AN11_ANSELG, HAL_LL_RG9_AN11_ANSELG_BIT , HAL_LL_ANSELG_ADDRESS },
    #endif
    #ifdef HAL_LL_RA0_AN24_ANSELA
    { GPIO_PA0, 0, HAL_LL_RA0_AN24_ANSELA, HAL_LL_RA0_AN24_ANSELA_BIT , HAL_LL_ANSELA_ADDRESS },
    #endif
    #ifdef HAL_LL_RA1_AN29_ANSELA
    { GPIO_PA1, 0, HAL_LL_RA1_AN29_ANSELA, HAL_LL_RA1_AN29_ANSELA_BIT , HAL_LL_ANSELA_ADDRESS },
    #endif
    #ifdef HAL_LL_RA10_AN28_ANSELA
    { GPIO_PA10, 0, HAL_LL_RA10_AN28_ANSELA, HAL_LL_RA10_AN28_ANSELA_BIT , HAL_LL_ANSELA_ADDRESS },
    #endif
    #ifdef HAL_LL_RA5_AN34_ANSELA
    { GPIO_PA5, 0, HAL_LL_RA5_AN34_ANSELA, HAL_LL_RA5_AN34_ANSELA_BIT , HAL_LL_ANSELA_ADDRESS },
    #endif
    #ifdef HAL_LL_RA9_AN27_ANSELA
    { GPIO_PA9, 0, HAL_LL_RA9_AN27_ANSELA, HAL_LL_RA9_AN27_ANSELA_BIT , HAL_LL_ANSELA_ADDRESS },
    #endif
    #ifdef HAL_LL_RC1_AN22_ANSELC
    { GPIO_PC1, 0, HAL_LL_RC1_AN22_ANSELC, HAL_LL_RC1_AN22_ANSELC_BIT , HAL_LL_ANSELC_ADDRESS },
    #endif
    #ifdef HAL_LL_RC2_AN21_ANSELC
    { GPIO_PC2, 0, HAL_LL_RC2_AN21_ANSELC, HAL_LL_RC2_AN21_ANSELC_BIT , HAL_LL_ANSELC_ADDRESS },
    #endif
    #ifdef HAL_LL_RC3_AN20_ANSELC
    { GPIO_PC3, 0, HAL_LL_RC3_AN20_ANSELC, HAL_LL_RC3_AN20_ANSELC_BIT , HAL_LL_ANSELC_ADDRESS },
    #endif
    #ifdef HAL_LL_RC4_AN19_ANSELC
    { GPIO_PC4, 0, HAL_LL_RC4_AN19_ANSELC, HAL_LL_RC4_AN19_ANSELC_BIT , HAL_LL_ANSELC_ADDRESS },
    #endif
    #ifdef HAL_LL_RD14_AN32_ANSELD
    { GPIO_PD14, 0, HAL_LL_RD14_AN32_ANSELD, HAL_LL_RD14_AN32_ANSELD_BIT , HAL_LL_ANSELD_ADDRESS },
    #endif
    #ifdef HAL_LL_RD15_AN33_ANSELD
    { GPIO_PD15, 0, HAL_LL_RD15_AN33_ANSELD, HAL_LL_RD15_AN33_ANSELD_BIT , HAL_LL_ANSELD_ADDRESS },
    #endif
    #ifdef HAL_LL_RE8_AN25_ANSELE
    { GPIO_PE8, 0, HAL_LL_RE8_AN25_ANSELE, HAL_LL_RE8_AN25_ANSELE_BIT , HAL_LL_ANSELE_ADDRESS },
    #endif
    #ifdef HAL_LL_RE9_AN26_ANSELE
    { GPIO_PE9, 0, HAL_LL_RE9_AN26_ANSELE, HAL_LL_RE9_AN26_ANSELE_BIT , HAL_LL_ANSELE_ADDRESS },
    #endif
    #ifdef HAL_LL_RF12_AN31_ANSELF
    { GPIO_PF12, 0, HAL_LL_RF12_AN31_ANSELF, HAL_LL_RF12_AN31_ANSELF_BIT , HAL_LL_ANSELF_ADDRESS },
    #endif
    #ifdef HAL_LL_RF13_AN30_ANSELF
    { GPIO_PF13, 0, HAL_LL_RF13_AN30_ANSELF, HAL_LL_RF13_AN30_ANSELF_BIT , HAL_LL_ANSELF_ADDRESS },
    #endif
    #ifdef HAL_LL_RG15_AN23_ANSELG
    { GPIO_PG15, 0, HAL_LL_RG15_AN23_ANSELG, HAL_LL_RG15_AN23_ANSELG_BIT , HAL_LL_ANSELG_ADDRESS },
    #endif
    #ifdef HAL_LL_RH0_AN38_ANSELH
    { GPIO_PH0, 0, HAL_LL_RH0_AN38_ANSELH, HAL_LL_RH0_AN38_ANSELH_BIT , HAL_LL_ANSELH_ADDRESS },
    #endif
    #ifdef HAL_LL_RH1_AN39_ANSELH
    { GPIO_PH1, 0, HAL_LL_RH1_AN39_ANSELH, HAL_LL_RH1_AN39_ANSELH_BIT , HAL_LL_ANSELH_ADDRESS },
    #endif
    #ifdef HAL_LL_RH4_AN40_ANSELH
    { GPIO_PH4, 0, HAL_LL_RH4_AN40_ANSELH, HAL_LL_RH4_AN40_ANSELH_BIT , HAL_LL_ANSELH_ADDRESS },
    #endif
    #ifdef HAL_LL_RH5_AN41_ANSELH
    { GPIO_PH5, 0, HAL_LL_RH5_AN41_ANSELH, HAL_LL_RH5_AN41_ANSELH_BIT , HAL_LL_ANSELH_ADDRESS },
    #endif
    #ifdef HAL_LL_RH6_AN42_ANSELH
    { GPIO_PH6, 0, HAL_LL_RH6_AN42_ANSELH, HAL_LL_RH6_AN42_ANSELH_BIT , HAL_LL_ANSELH_ADDRESS },
    #endif
    #ifdef HAL_LL_RJ11_AN37_ANSELJ
    { GPIO_PJ11, 0, HAL_LL_RJ11_AN37_ANSELJ, HAL_LL_RJ11_AN37_ANSELJ_BIT , HAL_LL_ANSELJ_ADDRESS },
    #endif
    #ifdef HAL_LL_RJ8_AN35_ANSELJ
    { GPIO_PJ8, 0, HAL_LL_RJ8_AN35_ANSELJ, HAL_LL_RJ8_AN35_ANSELJ_BIT , HAL_LL_ANSELJ_ADDRESS },
    #endif
    #ifdef HAL_LL_RJ9_AN36_ANSELJ
    { GPIO_PJ9, 0, HAL_LL_RJ9_AN36_ANSELJ, HAL_LL_RJ9_AN36_ANSELJ_BIT , HAL_LL_ANSELJ_ADDRESS },
    #endif

    { 0xFF, 0xFF, 0xFF, 0xFF, 0xFFFFFFF }
};

#ifdef __cplusplus
}
#endif

#endif // _HAL_LL_ANALOG_IN_MAP_H_
// ------------------------------------------------------------------------- END
