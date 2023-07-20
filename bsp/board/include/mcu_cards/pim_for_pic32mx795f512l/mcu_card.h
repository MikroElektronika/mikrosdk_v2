/****************************************************************************
**
** Copyright (C) 2023 MikroElektronika d.o.o.
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
#define MCU_CARD_REV_MAJOR (2)
#define MCU_CARD_REV_MINOR (0)

// Left connector
#define LEFT_CN_PIN_001 PG15 // Pin not routed to mikroBUS
#define LEFT_CN_PIN_002 // Pin not routed to mikroBUS
#define LEFT_CN_PIN_003 PE5 // Pin not routed to mikroBUS
#define LEFT_CN_PIN_004 PE6 // Pin not routed to mikroBUS
#define LEFT_CN_PIN_005 PE7 // Pin not routed to mikroBUS
#define LEFT_CN_PIN_006 PC1 // Pin not routed to mikroBUS
#define LEFT_CN_PIN_007 PC2 // Pin not routed to mikroBUS
#define LEFT_CN_PIN_008 PC3 // Pin not routed to mikroBUS
#define LEFT_CN_PIN_009 PC4 // Pin not routed to mikroBUS
#define LEFT_CN_PIN_010 PG6
#define LEFT_CN_PIN_011 PG7
#define LEFT_CN_PIN_012 PG8
#define LEFT_CN_PIN_013 // Pin not routed to mikroBUS
#define LEFT_CN_PIN_014 PG9
#define LEFT_CN_PIN_015 // Pin not routed to mikroBUS
#define LEFT_CN_PIN_016 // Pin not routed to mikroBUS
#define LEFT_CN_PIN_017 PA0 // Pin not routed to mikroBUS
#define LEFT_CN_PIN_018 PE8 // Pin not routed to mikroBUS
#define LEFT_CN_PIN_019 PE9 // Pin not routed to mikroBUS
#define LEFT_CN_PIN_020 PB2 // Pin not routed to mikroBUS
#define LEFT_CN_PIN_021 PB4 // Pin not routed to mikroBUS
#define LEFT_CN_PIN_022 PB3 // Pin not routed to mikroBUS
#define LEFT_CN_PIN_023 PD9
#define LEFT_CN_PIN_024 PB1
#define LEFT_CN_PIN_025 PB0

// Down connector
#define DOWN_CN_PIN_026 PB6 // Pin not routed to mikroBUS
#define DOWN_CN_PIN_027 PB7 // Pin not routed to mikroBUS
#define DOWN_CN_PIN_028 PA9 // Pin not routed to mikroBUS
#define DOWN_CN_PIN_029 P10 // Pin not routed to mikroBUS
#define DOWN_CN_PIN_030 // Pin not routed to mikroBUS
#define DOWN_CN_PIN_031 // Pin not routed to mikroBUS
#define DOWN_CN_PIN_032 PB8 // Pin not routed to mikroBUS
#define DOWN_CN_PIN_033 PB9 // Pin not routed to mikroBUS
#define DOWN_CN_PIN_034 PB10 // Pin not routed to mikroBUS
#define DOWN_CN_PIN_035 PB11 // Pin not routed to mikroBUS
#define DOWN_CN_PIN_036 // Pin not routed to mikroBUS
#define DOWN_CN_PIN_037 // Pin not routed to mikroBUS
#define DOWN_CN_PIN_038 PA1 // Pin not routed to mikroBUS
#define DOWN_CN_PIN_039 PF13 // Pin not routed to mikroBUS
#define DOWN_CN_PIN_040 PF12 // Pin not routed to mikroBUS
#define DOWN_CN_PIN_041 PB12 // Pin not routed to mikroBUS
#define DOWN_CN_PIN_042 PB13 // Pin not routed to mikroBUS
#define DOWN_CN_PIN_043 PB14 // Pin not routed to mikroBUS
#define DOWN_CN_PIN_044 PB15 // Pin not routed to mikroBUS
#define DOWN_CN_PIN_045 // Pin not routed to mikroBUS
#define DOWN_CN_PIN_046 // Pin not routed to mikroBUS
#define DOWN_CN_PIN_047 PD14 // Pin not routed to mikroBUS
#define DOWN_CN_PIN_048 PD15 // Pin not routed to mikroBUS
#define DOWN_CN_PIN_049 PF4
#define DOWN_CN_PIN_050 PF5

// Right connector
#define RIGHT_CN_PIN_051 PF8
#define RIGHT_CN_PIN_052 PF2
#define RIGHT_CN_PIN_053 PD0
#define RIGHT_CN_PIN_054 PC4
#define RIGHT_CN_PIN_055 PD10
#define RIGHT_CN_PIN_056 PA15
#define RIGHT_CN_PIN_057 PA14
#define RIGHT_CN_PIN_058 PA2 // Pin not routed to mikroBUS
#define RIGHT_CN_PIN_059 PA3 // Pin not routed to mikroBUS
#define RIGHT_CN_PIN_060 PA4 // Pin not routed to mikroBUS
#define RIGHT_CN_PIN_061 PA5 // Pin not routed to mikroBUS
#define RIGHT_CN_PIN_062 // Pin not routed to mikroBUS
#define RIGHT_CN_PIN_063 // Pin not routed to mikroBUS
#define RIGHT_CN_PIN_064 // Pin not routed to mikroBUS
#define RIGHT_CN_PIN_065 // Pin not routed to mikroBUS
#define RIGHT_CN_PIN_066 PE8 // Pin not routed to mikroBUS
#define RIGHT_CN_PIN_067 PA15
#define RIGHT_CN_PIN_068 PD8 // Pin not routed to mikroBUS
#define RIGHT_CN_PIN_069 PG15 // Pin not routed to mikroBUS
#define RIGHT_CN_PIN_070 PD10 // Pin not routed to mikroBUS
#define RIGHT_CN_PIN_071 PD11 // Pin not routed to mikroBUS
#define RIGHT_CN_PIN_072 PD0
#define RIGHT_CN_PIN_073 PC13 // Pin not routed to mikroBUS
#define RIGHT_CN_PIN_074 PC14 // Pin not routed to mikroBUS
#define RIGHT_CN_PIN_075 // Pin not routed to mikroBUS

// Up connector
#define UP_CN_PIN_076 PD1 // Pin not routed to mikroBUS
#define UP_CN_PIN_077 PD2 // Pin not routed to mikroBUS
#define UP_CN_PIN_078 PD3
#define UP_CN_PIN_079 PD12 // Pin not routed to mikroBUS
#define UP_CN_PIN_080 PD13 // Pin not routed to mikroBUS
#define UP_CN_PIN_081 PD4 // Pin not routed to mikroBUS
#define UP_CN_PIN_082 PD5 // Pin not routed to mikroBUS
#define UP_CN_PIN_083 PD6 // Pin not routed to mikroBUS
#define UP_CN_PIN_084 PD7 // Pin not routed to mikroBUS
#define UP_CN_PIN_085 // Pin not routed to mikroBUS
#define UP_CN_PIN_086 // Pin not routed to mikroBUS
#define UP_CN_PIN_087 PF0 // Pin not routed to mikroBUS
#define UP_CN_PIN_088 PF1 // Pin not routed to mikroBUS
#define UP_CN_PIN_089 PG1 // Pin not routed to mikroBUS
#define UP_CN_PIN_090 PG0 // Pin not routed to mikroBUS
#define UP_CN_PIN_091 PA6 // Pin not routed to mikroBUS
#define UP_CN_PIN_092 PA7 // Pin not routed to mikroBUS
#define UP_CN_PIN_093 PE0 // Pin not routed to mikroBUS
#define UP_CN_PIN_094 PE1 // Pin not routed to mikroBUS
#define UP_CN_PIN_095 PF3
#define UP_CN_PIN_096 PB5 // Pin not routed to mikroBUS
#define UP_CN_PIN_097 PG13 // Pin not routed to mikroBUS
#define UP_CN_PIN_098 PE2 // Pin not routed to mikroBUS
#define UP_CN_PIN_099 PE3 // Pin not routed to mikroBUS
#define UP_CN_PIN_100 PE4 // Pin not routed to mikroBUS

#ifdef __cplusplus
}
#endif

#endif // _MCU_CARD_H_
// ------------------------------------------------------------------------- END
