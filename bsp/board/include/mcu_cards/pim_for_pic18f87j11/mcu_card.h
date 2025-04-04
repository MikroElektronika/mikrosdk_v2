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

// Left connector
#define LEFT_CN_PIN_012 GPIO_PH2
#define LEFT_CN_PIN_013 GPIO_PH3
#define LEFT_CN_PIN_014 GPIO_PE1
#define LEFT_CN_PIN_015 GPIO_PE0
#define LEFT_CN_PIN_016 GPIO_PG0
#define LEFT_CN_PIN_017 GPIO_PG1
#define LEFT_CN_PIN_018 GPIO_PG2
#define LEFT_CN_PIN_019 GPIO_PG3
#define LEFT_CN_PIN_020 // Pin not routed.
#define LEFT_CN_PIN_021 GPIO_PG4
#define LEFT_CN_PIN_022 // Pin not routed.
#define LEFT_CN_PIN_023 // Pin not routed.
#define LEFT_CN_PIN_024 // Pin not routed.
#define LEFT_CN_PIN_025 GPIO_PF7
#define LEFT_CN_PIN_026 GPIO_PF6
#define LEFT_CN_PIN_027 GPIO_PF5
#define LEFT_CN_PIN_028 GPIO_PF4
#define LEFT_CN_PIN_029 GPIO_PF3
#define LEFT_CN_PIN_030 GPIO_PF2
#define LEFT_CN_PIN_031 GPIO_PH7
#define LEFT_CN_PIN_032 GPIO_PH6

// Down connector
#define DOWN_CN_PIN_033 GPIO_PH5
#define DOWN_CN_PIN_034 GPIO_PH4
#define DOWN_CN_PIN_035 GPIO_PF1
#define DOWN_CN_PIN_036 GPIO_PF0
#define DOWN_CN_PIN_037 // Pin not routed.
#define DOWN_CN_PIN_038 GPIO_PA3
#define DOWN_CN_PIN_039 GPIO_PA2
#define DOWN_CN_PIN_040 GPIO_PA1
#define DOWN_CN_PIN_041 GPIO_PA0
#define DOWN_CN_PIN_042 // Pin not routed.
#define DOWN_CN_PIN_043 // Pin not routed.
#define DOWN_CN_PIN_044 // Pin not routed.
#define DOWN_CN_PIN_045 // Pin not routed.
#define DOWN_CN_PIN_046 GPIO_PA5
#define DOWN_CN_PIN_047 GPIO_PA4
#define DOWN_CN_PIN_048 GPIO_PC1
#define DOWN_CN_PIN_049 GPIO_PC0
#define DOWN_CN_PIN_050 GPIO_PC6
#define DOWN_CN_PIN_051 GPIO_PC7
#define DOWN_CN_PIN_052 GPIO_PJ4
#define DOWN_CN_PIN_053 GPIO_PJ5

// Right connector
#define RIGHT_CN_PIN_054 GPIO_PJ6
#define RIGHT_CN_PIN_055 GPIO_PJ7
#define RIGHT_CN_PIN_056 GPIO_PC2
#define RIGHT_CN_PIN_057 GPIO_PC3
#define RIGHT_CN_PIN_058 GPIO_PC4
#define RIGHT_CN_PIN_059 GPIO_PC5
#define RIGHT_CN_PIN_060 GPIO_PB7
#define RIGHT_CN_PIN_061 // Pin not routed.
#define RIGHT_CN_PIN_062 // Pin not routed.
#define RIGHT_CN_PIN_063 // Pin not routed.
#define RIGHT_CN_PIN_064 // Pin not routed.
#define RIGHT_CN_PIN_065 // Pin not routed.
#define RIGHT_CN_PIN_066 GPIO_PB6
#define RIGHT_CN_PIN_067 GPIO_PB5
#define RIGHT_CN_PIN_068 GPIO_PB4
#define RIGHT_CN_PIN_069 GPIO_PB3
#define RIGHT_CN_PIN_070 GPIO_PB2
#define RIGHT_CN_PIN_071 GPIO_PB1
#define RIGHT_CN_PIN_072 GPIO_PB0
#define RIGHT_CN_PIN_073 GPIO_PJ3
#define RIGHT_CN_PIN_074 GPIO_PJ2

// Up connector
#define UP_CN_PIN_001 // Pin not routed.
#define UP_CN_PIN_002 // Pin not routed.
#define UP_CN_PIN_003 GPIO_PD0
#define UP_CN_PIN_004 GPIO_PE7
#define UP_CN_PIN_005 GPIO_PE6
#define UP_CN_PIN_006 GPIO_PE5
#define UP_CN_PIN_007 GPIO_PE4
#define UP_CN_PIN_008 GPIO_PE3
#define UP_CN_PIN_009 GPIO_PE2
#define UP_CN_PIN_010 GPIO_PH0
#define UP_CN_PIN_011 GPIO_PH1
#define UP_CN_PIN_075 GPIO_PJ1
#define UP_CN_PIN_076 GPIO_PJ0
#define UP_CN_PIN_077 GPIO_PD7
#define UP_CN_PIN_078 GPIO_PD6
#define UP_CN_PIN_079 GPIO_PD5
#define UP_CN_PIN_080 GPIO_PD4
#define UP_CN_PIN_081 GPIO_PD3
#define UP_CN_PIN_082 GPIO_PD2
#define UP_CN_PIN_083 GPIO_PD1
#define UP_CN_PIN_084 // Pin not routed.

#ifdef __cplusplus
}
#endif

#endif // _MCU_CARD_H_
// ------------------------------------------------------------------------- END
