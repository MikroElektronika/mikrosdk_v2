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
 * @file  mcu_card.h
 * @brief MCU card connections mapping.
 */

#ifndef _MCU_CARD_H_
#define _MCU_CARD_H_

#ifdef __cplusplus
extern "C"{
#endif

#include "hal_target.h"

// Hardware revision number
#define MCU_CARD_REV_MAJOR (1)
#define MCU_CARD_REV_MINOR (0)

#define NC HAL_PIN_NC

// Left connector
#define LEFT_CN_PIN_001 PG15 // Pin not routed.
#define LEFT_CN_PIN_002 // Pin not routed.
#define LEFT_CN_PIN_003 PA7 // Pin not routed.
#define LEFT_CN_PIN_004 PB14 // Pin not routed.
#define LEFT_CN_PIN_005 PB15 // Pin not routed.
#define LEFT_CN_PIN_006 PD1 // Pin not routed.
#define LEFT_CN_PIN_007 PD2 // Pin not routed.
#define LEFT_CN_PIN_008 PD3 // Pin not routed.
#define LEFT_CN_PIN_009 PD4 // Pin not routed.
#define LEFT_CN_PIN_010 PG6
#define LEFT_CN_PIN_011 PG7
#define LEFT_CN_PIN_012 PG8
#define LEFT_CN_PIN_013 // Pin not routed.
#define LEFT_CN_PIN_014 PG9
#define LEFT_CN_PIN_015 // Pin not routed.
#define LEFT_CN_PIN_016 // Pin not routed.
#define LEFT_CN_PIN_017 PG10 // Pin not routed.
#define LEFT_CN_PIN_018 PPE8 // Pin not routed.
#define LEFT_CN_PIN_019 PA12
#define LEFT_CN_PIN_020 PE9 // Pin not routed.
#define LEFT_CN_PIN_021 PA11 // Pin not routed.
#define LEFT_CN_PIN_022 PA0 // Pin not routed.
#define LEFT_CN_PIN_023 PA1
#define LEFT_CN_PIN_024 PB0
#define LEFT_CN_PIN_025 PB1

// Down connector
#define DOWN_CN_PIN_026 PB2 // Pin not routed.
#define DOWN_CN_PIN_027 PB3 // Pin not routed.
#define DOWN_CN_PIN_028 PF10 // Pin not routed.
#define DOWN_CN_PIN_029 PF9 // Pin not routed.
#define DOWN_CN_PIN_030 // Pin not routed.
#define DOWN_CN_PIN_031 // Pin not routed.
#define DOWN_CN_PIN_032 PC0 // Pin not routed.
#define DOWN_CN_PIN_033 PC1 // Pin not routed.
#define DOWN_CN_PIN_034 PC2 // Pin not routed.
#define DOWN_CN_PIN_035 PC11 // Pin not routed.
#define DOWN_CN_PIN_036 // Pin not routed.
#define DOWN_CN_PIN_037 // Pin not routed.
#define DOWN_CN_PIN_038 PG11 // Pin not routed.
#define DOWN_CN_PIN_039 PE12 // Pin not routed.
#define DOWN_CN_PIN_040 PE13 // Pin not routed.
#define DOWN_CN_PIN_041 PE12 // Pin not routed.
#define DOWN_CN_PIN_042 PE13 // Pin not routed.
#define DOWN_CN_PIN_043 PE14 // Pin not routed.
#define DOWN_CN_PIN_044 PE15 // Pin not routed.
#define DOWN_CN_PIN_045 // Pin not routed.
#define DOWN_CN_PIN_046 // Pin not routed.
#define DOWN_CN_PIN_047 PD14 // Pin not routed.
#define DOWN_CN_PIN_048 PD15 // Pin not routed.
#define DOWN_CN_PIN_049 PA8
#define DOWN_CN_PIN_050 PB4

// Right connector
#define RIGHT_CN_PIN_051 PE1
#define RIGHT_CN_PIN_052 PE0
#define RIGHT_CN_PIN_053 PA4
#define RIGHT_CN_PIN_054 PA9
#define RIGHT_CN_PIN_055 PC3
#define RIGHT_CN_PIN_056 PC4
#define RIGHT_CN_PIN_057 PC5
#define RIGHT_CN_PIN_058 PG2 // Pin not routed.
#define RIGHT_CN_PIN_059 PG3 // Pin not routed.
#define RIGHT_CN_PIN_060 PF4 // Pin not routed.
#define RIGHT_CN_PIN_061 PF5 // Pin not routed.
#define RIGHT_CN_PIN_062 // Pin not routed.
#define RIGHT_CN_PIN_063 PC12 // Pin not routed.
#define RIGHT_CN_PIN_064 PC15 // Pin not routed.
#define RIGHT_CN_PIN_065 // Pin not routed.
#define RIGHT_CN_PIN_066 PA14 // Pin not routed.
#define RIGHT_CN_PIN_067 PA15
#define RIGHT_CN_PIN_068 PD8 // Pin not routed.
#define RIGHT_CN_PIN_069 PB5 // Pin not routed.
#define RIGHT_CN_PIN_070 PB6 // Pin not routed.
#define RIGHT_CN_PIN_071 PC10 // Pin not routed.
#define RIGHT_CN_PIN_072 PB7
#define RIGHT_CN_PIN_073 PC13 // Pin not routed.
#define RIGHT_CN_PIN_074 PB8 // Pin not routed.
#define RIGHT_CN_PIN_075 // Pin not routed.

// Up connector
#define UP_CN_PIN_076 PB9 // Pin not routed.
#define UP_CN_PIN_077 PC6 // Pin not routed.
#define UP_CN_PIN_078 PC7
#define UP_CN_PIN_079 PD12 // Pin not routed.
#define UP_CN_PIN_080 PD13 // Pin not routed.
#define UP_CN_PIN_081 PC8 // Pin not routed.
#define UP_CN_PIN_082 PD5 // Pin not routed.
#define UP_CN_PIN_083 PD6 // Pin not routed.
#define UP_CN_PIN_084 PC9
#define UP_CN_PIN_085 // Pin not routed.
#define UP_CN_PIN_086 // Pin not routed.
#define UP_CN_PIN_087 PF0 // Pin not routed.
#define UP_CN_PIN_088 PF1 // Pin not routed.
#define UP_CN_PIN_089 PG1 // Pin not routed.
#define UP_CN_PIN_090 PG0 // Pin not routed.
#define UP_CN_PIN_091 PF6 // Pin not routed.
#define UP_CN_PIN_092 PF7 // Pin not routed.
#define UP_CN_PIN_093 PB10 // Pin not routed.
#define UP_CN_PIN_094 PB11 // Pin not routed.
#define UP_CN_PIN_095 PG14
#define UP_CN_PIN_096 PG12 // Pin not routed.
#define UP_CN_PIN_097 PG13 // Pin not routed.
#define UP_CN_PIN_098 PB12 // Pin not routed.
#define UP_CN_PIN_099 PB13 // Pin not routed.
#define UP_CN_PIN_100 PA10 // Pin not routed.

#ifdef __cplusplus
}
#endif

#endif // _MCU_CARD_H_
// ------------------------------------------------------------------------- END
