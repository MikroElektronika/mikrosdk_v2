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
#define MCU_CARD_REV_MAJOR (5)
#define MCU_CARD_REV_MINOR (0)

#define NC HAL_PIN_NC

// Left connector
#define LEFT_CN_PIN_001 // Pin not routed.
#define LEFT_CN_PIN_002 // Pin not routed.
#define LEFT_CN_PIN_003 GPIO_PB13 // Pin not routed.
#define LEFT_CN_PIN_004 GPIO_PB14 // Pin not routed.
#define LEFT_CN_PIN_005 GPIO_PB15 // Pin not routed.
#define LEFT_CN_PIN_006 // Pin not routed.
#define LEFT_CN_PIN_007 // Pin not routed.
#define LEFT_CN_PIN_008 // Pin not routed.
#define LEFT_CN_PIN_009 // Pin not routed.
#define LEFT_CN_PIN_010 GPIO_PG6
#define LEFT_CN_PIN_011 GPIO_PG7
#define LEFT_CN_PIN_012 GPIO_PG8
#define LEFT_CN_PIN_013 // Pin not routed.
#define LEFT_CN_PIN_014
#define LEFT_CN_PIN_015 // Pin not routed.
#define LEFT_CN_PIN_016 // Pin not routed.
#define LEFT_CN_PIN_017 GPIO_PC0 // Pin not routed.
#define LEFT_CN_PIN_018 GPIO_PB7 // Pin not routed.
#define LEFT_CN_PIN_019 // Pin not routed.
#define LEFT_CN_PIN_020 GPIO_PA0 // Pin not routed.
#define LEFT_CN_PIN_021 GPIO_PA1 // Pin not routed.
#define LEFT_CN_PIN_022 GPIO_PA11 // Pin not routed.
#define LEFT_CN_PIN_023 GPIO_PF1
#define LEFT_CN_PIN_024 GPIO_PB0
#define LEFT_CN_PIN_025 GPIO_PA12

// Down connector
#define DOWN_CN_PIN_026 GPIO_PB2 // Pin not routed.
#define DOWN_CN_PIN_027 GPIO_PB3 // Pin not routed.
#define DOWN_CN_PIN_028 // Pin not routed.
#define DOWN_CN_PIN_029 // Pin not routed.
#define DOWN_CN_PIN_030 // Pin not routed.
#define DOWN_CN_PIN_031 // Pin not routed.
#define DOWN_CN_PIN_032 GPIO_PB1 // Pin not routed.
#define DOWN_CN_PIN_033 // Pin not routed.
#define DOWN_CN_PIN_034 // Pin not routed.
#define DOWN_CN_PIN_035 // Pin not routed.
#define DOWN_CN_PIN_036 // Pin not routed.
#define DOWN_CN_PIN_037 // Pin not routed.
#define DOWN_CN_PIN_038 GPIO_PC1 // Pin not routed.
#define DOWN_CN_PIN_039 GPIO_PC2 // Pin not routed.
#define DOWN_CN_PIN_040 GPIO_PC11 // Pin not routed.
#define DOWN_CN_PIN_041 GPIO_PE15 // Pin not routed.
#define DOWN_CN_PIN_042 // Pin not routed.
#define DOWN_CN_PIN_043 GPIO_PA7 // Pin not routed.
#define DOWN_CN_PIN_044 GPIO_PA10 // Pin not routed.
#define DOWN_CN_PIN_045 // Pin not routed.
#define DOWN_CN_PIN_046 // Pin not routed.
#define DOWN_CN_PIN_047 GPIO_PD8 // Pin not routed.
#define DOWN_CN_PIN_048 GPIO_PC10 // Pin not routed.
#define DOWN_CN_PIN_049 GPIO_PB6
#define DOWN_CN_PIN_050 GPIO_PB5

// Right connector
#define RIGHT_CN_PIN_051 // Pin not routed.
#define RIGHT_CN_PIN_052 // Pin not routed.
#define RIGHT_CN_PIN_053 GPIO_PA4
#define RIGHT_CN_PIN_054 GPIO_PA9
#define RIGHT_CN_PIN_055 GPIO_PC3
#define RIGHT_CN_PIN_056 GPIO_PC4
#define RIGHT_CN_PIN_057 GPIO_PC5
#define RIGHT_CN_PIN_058 GPIO_PB4 // Pin not routed.
#define RIGHT_CN_PIN_059 GPIO_PA8 // Pin not routed.
#define RIGHT_CN_PIN_060 GPIO_PE12 // Pin not routed.
#define RIGHT_CN_PIN_061 GPIO_PE13 // Pin not routed.
#define RIGHT_CN_PIN_062 // Pin not routed.
#define RIGHT_CN_PIN_063 GPIO_PC12 // Pin not routed.
#define RIGHT_CN_PIN_064 GPIO_PC15 // Pin not routed.
#define RIGHT_CN_PIN_065 // Pin not routed.
#define RIGHT_CN_PIN_066 // Pin not routed.
#define RIGHT_CN_PIN_067 // Pin not routed.
#define RIGHT_CN_PIN_068 // Pin not routed.
#define RIGHT_CN_PIN_069 // Pin not routed.
#define RIGHT_CN_PIN_070 // Pin not routed.
#define RIGHT_CN_PIN_071 // Pin not routed.
#define RIGHT_CN_PIN_072 // Pin not routed.
#define RIGHT_CN_PIN_073 // Pin not routed.
#define RIGHT_CN_PIN_074 // Pin not routed.
#define RIGHT_CN_PIN_075 // Pin not routed.

// Up connector
#define UP_CN_PIN_076 // Pin not routed.
#define UP_CN_PIN_077 // Pin not routed.
#define UP_CN_PIN_078 // Pin not routed.
#define UP_CN_PIN_079 GPIO_PG9 // Pin not routed.
#define UP_CN_PIN_080 GPIO_PD5 // Pin not routed.
#define UP_CN_PIN_081 GPIO_PC6 // Pin not routed.
#define UP_CN_PIN_082 GPIO_PC13 // Pin not routed.
#define UP_CN_PIN_083 GPIO_PD6 // Pin not routed.
#define UP_CN_PIN_084 GPIO_PC7
#define UP_CN_PIN_085 // Pin not routed.
#define UP_CN_PIN_086 // Pin not routed.
#define UP_CN_PIN_087 GPIO_PF0 // Pin not routed.
#define UP_CN_PIN_088 GPIO_PC9 // Pin not routed.
#define UP_CN_PIN_089 // Pin not routed.
#define UP_CN_PIN_090 // Pin not routed.
#define UP_CN_PIN_091 GPIO_PE14 // Pin not routed.
#define UP_CN_PIN_092 GPIO_PC8 // Pin not routed.
#define UP_CN_PIN_093 GPIO_PB8 // Pin not routed.
#define UP_CN_PIN_094 GPIO_PB9 // Pin not routed.
#define UP_CN_PIN_095 // Pin not routed.
#define UP_CN_PIN_096 // Pin not routed.
#define UP_CN_PIN_097 // Pin not routed.
#define UP_CN_PIN_098 GPIO_PB10 // Pin not routed.
#define UP_CN_PIN_099 GPIO_PB11 // Pin not routed.
#define UP_CN_PIN_100 GPIO_PB12 // Pin not routed.

#ifdef __cplusplus
}
#endif

#endif // _MCU_CARD_H_
// ------------------------------------------------------------------------- END
