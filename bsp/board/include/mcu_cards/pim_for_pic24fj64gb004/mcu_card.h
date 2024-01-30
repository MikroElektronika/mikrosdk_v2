/****************************************************************************
**
** Copyright (C) 2024 MikroElektronika d.o.o.
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
#define LEFT_CN_PIN_001 // Pin not routed to mikroBUS
#define LEFT_CN_PIN_002 // Pin not routed to mikroBUS
#define LEFT_CN_PIN_003 PB7 // Pin not routed to mikroBUS
#define LEFT_CN_PIN_004 PA1 // Pin not routed to mikroBUS
#define LEFT_CN_PIN_005 PA0 // Pin not routed to mikroBUS
#define LEFT_CN_PIN_006 PC2 // Pin not routed to mikroBUS
#define LEFT_CN_PIN_007 PB15 // Pin not routed to mikroBUS
#define LEFT_CN_PIN_008 // Pin not routed to mikroBUS
#define LEFT_CN_PIN_009 // Pin not routed to mikroBUS
#define LEFT_CN_PIN_010 PC8
#define LEFT_CN_PIN_011 PC4
#define LEFT_CN_PIN_012 PC5
#define LEFT_CN_PIN_013 // Pin not routed to mikroBUS
#define LEFT_CN_PIN_014 PC2
#define LEFT_CN_PIN_015 // Pin not routed to mikroBUS
#define LEFT_CN_PIN_016 // Pin not routed to mikroBUS
#define LEFT_CN_PIN_017 PA10 // Pin not routed to mikroBUS
#define LEFT_CN_PIN_018 PC2 // Pin not routed to mikroBUS
#define LEFT_CN_PIN_019 PB2
#define LEFT_CN_PIN_020 // Pin not routed to mikroBUS
#define LEFT_CN_PIN_021 // Pin not routed to mikroBUS
#define LEFT_CN_PIN_022 PA9 // Pin not routed to mikroBUS
#define LEFT_CN_PIN_023 PC6
#define LEFT_CN_PIN_024 PA1
#define LEFT_CN_PIN_025 PA0

// Down connector
#define DOWN_CN_PIN_026 // Pin not routed to mikroBUS
#define DOWN_CN_PIN_027 // Pin not routed to mikroBUS
#define DOWN_CN_PIN_028 PA7 // Pin not routed to mikroBUS
#define DOWN_CN_PIN_029 PC9 // Pin not routed to mikroBUS
#define DOWN_CN_PIN_030 // Pin not routed to mikroBUS
#define DOWN_CN_PIN_031 // Pin not routed to mikroBUS
#define DOWN_CN_PIN_032 PC2 // Pin not routed to mikroBUS
#define DOWN_CN_PIN_033 PA0 // Pin not routed to mikroBUS
#define DOWN_CN_PIN_034 PB10 // Pin not routed to mikroBUS
#define DOWN_CN_PIN_035 PB11 // Pin not routed to mikroBUS
#define DOWN_CN_PIN_036 // Pin not routed to mikroBUS
#define DOWN_CN_PIN_037 // Pin not routed to mikroBUS
#define DOWN_CN_PIN_038 PA7 // Pin not routed to mikroBUS
#define DOWN_CN_PIN_039 PC7 // Pin not routed to mikroBUS
#define DOWN_CN_PIN_040 PB14 // Pin not routed to mikroBUS
#define DOWN_CN_PIN_041 // Pin not routed to mikroBUS
#define DOWN_CN_PIN_042 // Pin not routed to mikroBUS
#define DOWN_CN_PIN_043 PC6 // Pin not routed to mikroBUS
#define DOWN_CN_PIN_044 PC7 // Pin not routed to mikroBUS
#define DOWN_CN_PIN_045 // Pin not routed to mikroBUS
#define DOWN_CN_PIN_046 // Pin not routed to mikroBUS
#define DOWN_CN_PIN_047 PB3 // Pin not routed to mikroBUS
#define DOWN_CN_PIN_048 PC8 // Pin not routed to mikroBUS
#define DOWN_CN_PIN_049 PC3
#define DOWN_CN_PIN_050 PC9

// Right connector
#define RIGHT_CN_PIN_051 PB13
#define RIGHT_CN_PIN_052 PB7
#define RIGHT_CN_PIN_053 PC0
#define RIGHT_CN_PIN_054 PC1
#define RIGHT_CN_PIN_055 PB15
#define RIGHT_CN_PIN_056 PB9
#define RIGHT_CN_PIN_057 PB8
#define RIGHT_CN_PIN_058 PB3 // Pin not routed to mikroBUS
#define RIGHT_CN_PIN_059 PB2 // Pin not routed to mikroBUS
#define RIGHT_CN_PIN_060 PA9 // Pin not routed to mikroBUS
#define RIGHT_CN_PIN_061 PA8 // Pin not routed to mikroBUS
#define RIGHT_CN_PIN_062 // Pin not routed to mikroBUS
#define RIGHT_CN_PIN_063 // Pin not routed to mikroBUS
#define RIGHT_CN_PIN_064 // Pin not routed to mikroBUS
#define RIGHT_CN_PIN_065 // Pin not routed to mikroBUS
#define RIGHT_CN_PIN_066 PC9 // Pin not routed to mikroBUS
#define RIGHT_CN_PIN_067 PC3
#define RIGHT_CN_PIN_068 PB14 // Pin not routed to mikroBUS
#define RIGHT_CN_PIN_069 PA10 // Pin not routed to mikroBUS
#define RIGHT_CN_PIN_070 PA7 // Pin not routed to mikroBUS
#define RIGHT_CN_PIN_071 PB15 // Pin not routed to mikroBUS
#define RIGHT_CN_PIN_072 PC9
#define RIGHT_CN_PIN_073 // Pin not routed to mikroBUS
#define RIGHT_CN_PIN_074 // Pin not routed to mikroBUS
#define RIGHT_CN_PIN_075 // Pin not routed to mikroBUS

// Up connector
#define UP_CN_PIN_076 PA8 // Pin not routed to mikroBUS
#define UP_CN_PIN_077 PC7 // Pin not routed to mikroBUS
#define UP_CN_PIN_078 PC3
#define UP_CN_PIN_079 PA8 // Pin not routed to mikroBUS
#define UP_CN_PIN_080 PA7 // Pin not routed to mikroBUS
#define UP_CN_PIN_081 PB3 // Pin not routed to mikroBUS
#define UP_CN_PIN_082 PB13 // Pin not routed to mikroBUS
#define UP_CN_PIN_083 PA10 // Pin not routed to mikroBUS
#define UP_CN_PIN_084 PA9 // Pin not routed to mikroBUS
#define UP_CN_PIN_085 // Pin not routed to mikroBUS
#define UP_CN_PIN_086 // Pin not routed to mikroBUS
#define UP_CN_PIN_087 PB2 // Pin not routed to mikroBUS
#define UP_CN_PIN_088 PB3 // Pin not routed to mikroBUS
#define UP_CN_PIN_089 PB11 // Pin not routed to mikroBUS
#define UP_CN_PIN_090 PB10 // Pin not routed to mikroBUS
#define UP_CN_PIN_091 PC5 // Pin not routed to mikroBUS
#define UP_CN_PIN_092 PC6 // Pin not routed to mikroBUS
#define UP_CN_PIN_093 PB0 // Pin not routed to mikroBUS
#define UP_CN_PIN_094 PB1 // Pin not routed to mikroBUS
#define UP_CN_PIN_095 PB5
#define UP_CN_PIN_096 PA9 // Pin not routed to mikroBUS
#define UP_CN_PIN_097 PB14 // Pin not routed to mikroBUS
#define UP_CN_PIN_098 PB2 // Pin not routed to mikroBUS
#define UP_CN_PIN_099 PB9 // Pin not routed to mikroBUS
#define UP_CN_PIN_100 PB8 // Pin not routed to mikroBUS

#ifdef __cplusplus
}
#endif

#endif // _MCU_CARD_H_
// ------------------------------------------------------------------------- END
