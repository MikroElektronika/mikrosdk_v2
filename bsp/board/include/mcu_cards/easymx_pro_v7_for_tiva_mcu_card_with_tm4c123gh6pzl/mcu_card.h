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
** a written agreement between you and The mikroElektronika Company.
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
#define MCU_CARD_REV_MINOR (01)

#define NC HAL_PIN_NC

// Left connector
#define LEFT_CN_PIN_1 // Pin not routed.
#define LEFT_CN_PIN_2 // Pin not routed.
#define LEFT_CN_PIN_3 // Pin not routed.
#define LEFT_CN_PIN_4 // Pin not routed.
#define LEFT_CN_PIN_5 // Pin not routed.
#define LEFT_CN_PIN_6 // Pin not routed.
#define LEFT_CN_PIN_7 PF7
#define LEFT_CN_PIN_8 PG3
#define LEFT_CN_PIN_9 PG2
#define LEFT_CN_PIN_10 PG1
#define LEFT_CN_PIN_11 PG0
#define LEFT_CN_PIN_12 // Pin not routed.
#define LEFT_CN_PIN_13 // Pin not routed.
#define LEFT_CN_PIN_14 // Pin not routed.
#define LEFT_CN_PIN_15 PB1
#define LEFT_CN_PIN_16 PB0
#define LEFT_CN_PIN_17 PB3
#define LEFT_CN_PIN_18 PB2
#define LEFT_CN_PIN_19 PG5
#define LEFT_CN_PIN_20 PG4
#define LEFT_CN_PIN_21 // Pin not routed.
#define LEFT_CN_PIN_22 // Pin not routed.
#define LEFT_CN_PIN_23 // Pin not routed.
#define LEFT_CN_PIN_24 // Pin not routed.
#define LEFT_CN_PIN_25 // Pin not routed.
#define LEFT_CN_PIN_26 // Pin not routed.

// Down connector
#define DOWN_CN_PIN_27 // Pin not routed.
#define DOWN_CN_PIN_28 // Pin not routed.
#define DOWN_CN_PIN_29 PH6
#define DOWN_CN_PIN_30 PH7
#define DOWN_CN_PIN_31 PH4
#define DOWN_CN_PIN_32 PH5
#define DOWN_CN_PIN_33 PC2
#define DOWN_CN_PIN_34 PC3
#define DOWN_CN_PIN_35 PC0
#define DOWN_CN_PIN_36 PC1
#define DOWN_CN_PIN_37 PG7
#define DOWN_CN_PIN_38 PG6
#define DOWN_CN_PIN_39 PE7
#define DOWN_CN_PIN_40 PE6
#define DOWN_CN_PIN_41 PB5
#define DOWN_CN_PIN_42 PB4
#define DOWN_CN_PIN_43 // Pin not routed.
#define DOWN_CN_PIN_44 PE4
#define DOWN_CN_PIN_45 PE5
#define DOWN_CN_PIN_46 // Pin not routed.
#define DOWN_CN_PIN_47 PD4
#define DOWN_CN_PIN_48 PD5
#define DOWN_CN_PIN_49 PD6
#define DOWN_CN_PIN_50 PD7
#define DOWN_CN_PIN_51 // Pin not routed.
#define DOWN_CN_PIN_52 // Pin not routed.

// Right connector
#define RIGHT_CN_PIN_53 // Pin not routed.
#define RIGHT_CN_PIN_54 // Pin not routed.
#define RIGHT_CN_PIN_55 PD1
#define RIGHT_CN_PIN_56 PD0
#define RIGHT_CN_PIN_57 PD3
#define RIGHT_CN_PIN_58 PD2
#define RIGHT_CN_PIN_59 // Pin not routed.
#define RIGHT_CN_PIN_60 // Pin not routed.
#define RIGHT_CN_PIN_61 PJ1
#define RIGHT_CN_PIN_62 PJ2
#define RIGHT_CN_PIN_63 // Pin not routed.
#define RIGHT_CN_PIN_64 PE3
#define RIGHT_CN_PIN_65 PE2
#define RIGHT_CN_PIN_66 PE1
#define RIGHT_CN_PIN_67 PE0
#define RIGHT_CN_PIN_68 PH0
#define RIGHT_CN_PIN_69 PH1
#define RIGHT_CN_PIN_70 PH2
#define RIGHT_CN_PIN_71 PH3
#define RIGHT_CN_PIN_72 // Pin not routed.
#define RIGHT_CN_PIN_73 PC7
#define RIGHT_CN_PIN_74 PC6
#define RIGHT_CN_PIN_75 PC5
#define RIGHT_CN_PIN_76 PC4
#define RIGHT_CN_PIN_77 // Pin not routed.
#define RIGHT_CN_PIN_78 // Pin not routed.

// Up connector
#define UP_CN_PIN_79 // Pin not routed.
#define UP_CN_PIN_80 // Pin not routed.
#define UP_CN_PIN_81 PA1
#define UP_CN_PIN_82 PA0
#define UP_CN_PIN_83 PA3
#define UP_CN_PIN_84 PA2
#define UP_CN_PIN_85 PA5
#define UP_CN_PIN_86 PA4
#define UP_CN_PIN_87 PA7
#define UP_CN_PIN_88 PA6
#define UP_CN_PIN_89 // Pin not routed.
#define UP_CN_PIN_90 // Pin not routed.
#define UP_CN_PIN_91 PF6
#define UP_CN_PIN_92 PF5
#define UP_CN_PIN_93 PF4
#define UP_CN_PIN_94 PF0
#define UP_CN_PIN_95 PF1
#define UP_CN_PIN_96 PF2
#define UP_CN_PIN_97 PF3
#define UP_CN_PIN_98 // Pin not routed.
#define UP_CN_PIN_99 PK3
#define UP_CN_PIN_100 PK2
#define UP_CN_PIN_101 PK1
#define UP_CN_PIN_102 PK0
#define UP_CN_PIN_103 // Pin not routed.
#define UP_CN_PIN_104 // Pin not routed.

#define LCD_TFT_8BIT_CH0 PORT_G
#define LCD_TFT_CH0_8BIT_MASK 0xFF

#define LCD_TFT_16BIT_CH0 HAL_PORT_NC
#define LCD_TFT_16BIT_CH0_MASK 0x0000

#define LCD_TFT_16BIT_CH1 HAL_PORT_NC
#define LCD_TFT_16BIT_CH1_MASK 0x0000

#ifdef __cplusplus
}
#endif

#endif // _MCU_CARD_H_
// ------------------------------------------------------------------------- END
