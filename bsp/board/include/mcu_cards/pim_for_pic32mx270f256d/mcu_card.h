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
#define LEFT_CN_PIN_001 // Pin not routed.
#define LEFT_CN_PIN_002 // Pin not routed.
#define LEFT_CN_PIN_003 // Pin not routed.
#define LEFT_CN_PIN_004 // Pin not routed.
#define LEFT_CN_PIN_005 // Pin not routed.
#define LEFT_CN_PIN_006 // Pin not routed.
#define LEFT_CN_PIN_007 // Pin not routed.
#define LEFT_CN_PIN_008 // Pin not routed.
#define LEFT_CN_PIN_009 // Pin not routed.
#define LEFT_CN_PIN_010 PC2
#define LEFT_CN_PIN_011 // Pin not routed.
#define LEFT_CN_PIN_012 // Pin not routed.
#define LEFT_CN_PIN_013 // Pin not routed.
#define LEFT_CN_PIN_014 // Pin not routed.
#define LEFT_CN_PIN_015 // Pin not routed.
#define LEFT_CN_PIN_016 // Pin not routed.
#define LEFT_CN_PIN_017 // Pin not routed.
#define LEFT_CN_PIN_018 // Pin not routed.
#define LEFT_CN_PIN_019 // Pin not routed.
#define LEFT_CN_PIN_020 // Pin not routed.
#define LEFT_CN_PIN_021 // Pin not routed.
#define LEFT_CN_PIN_022 // Pin not routed.
#define LEFT_CN_PIN_023 // Pin not routed.
#define LEFT_CN_PIN_024 // Pin not routed.
#define LEFT_CN_PIN_025 // Pin not routed.

// Down connector
#define DOWN_CN_PIN_026 // Pin not routed.
#define DOWN_CN_PIN_027 // Pin not routed.
#define DOWN_CN_PIN_028 // Pin not routed.
#define DOWN_CN_PIN_029 // Pin not routed.
#define DOWN_CN_PIN_030 // Pin not routed.
#define DOWN_CN_PIN_031 // Pin not routed.
#define DOWN_CN_PIN_032 // Pin not routed.
#define DOWN_CN_PIN_033 // Pin not routed.
#define DOWN_CN_PIN_034 // Pin not routed.
#define DOWN_CN_PIN_035 // Pin not routed.
#define DOWN_CN_PIN_036 // Pin not routed.
#define DOWN_CN_PIN_037 // Pin not routed.
#define DOWN_CN_PIN_038 // Pin not routed.
#define DOWN_CN_PIN_039 // Pin not routed.
#define DOWN_CN_PIN_040 // Pin not routed.
#define DOWN_CN_PIN_041 // Pin not routed.
#define DOWN_CN_PIN_042 // Pin not routed.
#define DOWN_CN_PIN_043 // Pin not routed.
#define DOWN_CN_PIN_044 // Pin not routed.
#define DOWN_CN_PIN_045 // Pin not routed.
#define DOWN_CN_PIN_046 // Pin not routed.
#define DOWN_CN_PIN_047 // Pin not routed.
#define DOWN_CN_PIN_048 // Pin not routed.
#define DOWN_CN_PIN_049 // Pin not routed.
#define DOWN_CN_PIN_050 // Pin not routed.

// Right connector
#define RIGHT_CN_PIN_051 // Pin not routed.
#define RIGHT_CN_PIN_052 // Pin not routed.
#define RIGHT_CN_PIN_053 // Pin not routed.
#define RIGHT_CN_PIN_054 // Pin not routed.
#define RIGHT_CN_PIN_055 // Pin not routed.
#define RIGHT_CN_PIN_056 // Pin not routed.
#define RIGHT_CN_PIN_057 // Pin not routed.
#define RIGHT_CN_PIN_058 // Pin not routed.
#define RIGHT_CN_PIN_059 // Pin not routed.
#define RIGHT_CN_PIN_060 // Pin not routed.
#define RIGHT_CN_PIN_061 // Pin not routed.
#define RIGHT_CN_PIN_062 // Pin not routed.
#define RIGHT_CN_PIN_063 // Pin not routed.
#define RIGHT_CN_PIN_064 // Pin not routed.
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

// Up conncetor
#define UP_CN_PIN_076 // Pin not routed.
#define UP_CN_PIN_077 // Pin not routed.
#define UP_CN_PIN_078 PC3
#define UP_CN_PIN_079 // Pin not routed.
#define UP_CN_PIN_080 // Pin not routed.
#define UP_CN_PIN_081 // Pin not routed.
#define UP_CN_PIN_082 // Pin not routed.
#define UP_CN_PIN_083 // Pin not routed.
#define UP_CN_PIN_084 // Pin not routed.
#define UP_CN_PIN_085 // Pin not routed.
#define UP_CN_PIN_086 // Pin not routed.
#define UP_CN_PIN_087 // Pin not routed.
#define UP_CN_PIN_088 // Pin not routed.
#define UP_CN_PIN_089 // Pin not routed.
#define UP_CN_PIN_090 // Pin not routed.
#define UP_CN_PIN_091 // Pin not routed.
#define UP_CN_PIN_092 // Pin not routed.
#define UP_CN_PIN_093 // Pin not routed.
#define UP_CN_PIN_094 // Pin not routed.
#define UP_CN_PIN_095 // Pin not routed.
#define UP_CN_PIN_096 // Pin not routed.
#define UP_CN_PIN_097 // Pin not routed.
#define UP_CN_PIN_098 // Pin not routed.
#define UP_CN_PIN_099 // Pin not routed.
#define UP_CN_PIN_100 // Pin not routed.

#ifdef __cplusplus
}
#endif

#endif // _MCU_CARD_H_
// ------------------------------------------------------------------------- END
