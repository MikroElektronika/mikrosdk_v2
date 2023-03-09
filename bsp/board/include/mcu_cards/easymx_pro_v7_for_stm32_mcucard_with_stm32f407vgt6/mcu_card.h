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
#define MCU_CARD_REV_MAJOR (1)
#define MCU_CARD_REV_MINOR (00)

#define NC HAL_PIN_NC

// Left connector
#define LEFT_CN_PIN_1       // Pin not routed to mikroBUS.
#define LEFT_CN_PIN_2       // Pin not routed to mikroBUS.
#define LEFT_CN_PIN_3       // Pin not routed to mikroBUS.
#define LEFT_CN_PIN_4       // Pin not routed to mikroBUS.
#define LEFT_CN_PIN_5       // Pin not routed to mikroBUS.
#define LEFT_CN_PIN_6       // Pin not routed to mikroBUS.
#define LEFT_CN_PIN_7   PC10
#define LEFT_CN_PIN_9   PC12
#define LEFT_CN_PIN_10  PC11
#define LEFT_CN_PIN_11  PD9
#define LEFT_CN_PIN_12  PD8
#define LEFT_CN_PIN_13  PD11
#define LEFT_CN_PIN_14  PD10
#define LEFT_CN_PIN_15  PD13
#define LEFT_CN_PIN_16  PD12
#define LEFT_CN_PIN_17       // Pin not routed to mikroBUS.
#define LEFT_CN_PIN_18  PD14
#define LEFT_CN_PIN_19       // Pin not routed to mikroBUS.
#define LEFT_CN_PIN_20       // Pin not routed to mikroBUS.
#define LEFT_CN_PIN_21       // Pin not routed to mikroBUS.
#define LEFT_CN_PIN_22       // Pin not routed to mikroBUS.

// Down connector
#define DOWN_CN_PIN_29  PA10
#define DOWN_CN_PIN_30  PA9
#define DOWN_CN_PIN_31      // Pin not routed to mikroBUS.
#define DOWN_CN_PIN_32      // Pin not routed to mikroBUS.
#define DOWN_CN_PIN_33      // Pin not routed to mikroBUS.
#define DOWN_CN_PIN_34      // Pin not routed to mikroBUS.
#define DOWN_CN_PIN_35      // Pin not routed to mikroBUS.
#define DOWN_CN_PIN_36      // Pin not routed to mikroBUS.
#define DOWN_CN_PIN_38      // Pin not routed to mikroBUS.
#define DOWN_CN_PIN_41      // Pin not routed to mikroBUS.
#define DOWN_CN_PIN_42      // Pin not routed to mikroBUS.
#define DOWN_CN_PIN_43      // Pin not routed to mikroBUS.
#define DOWN_CN_PIN_44      // Pin not routed to mikroBUS.
#define DOWN_CN_PIN_45  PD5
#define DOWN_CN_PIN_46      // Pin not routed to mikroBUS.
#define DOWN_CN_PIN_47      // Pin not routed to mikroBUS.
#define DOWN_CN_PIN_48  PD6
#define DOWN_CN_PIN_49      // Pin not routed to mikroBUS.
#define DOWN_CN_PIN_50      // Pin not routed to mikroBUS.

// Right connector
#define RIGHT_CN_PIN_55 PB6
#define RIGHT_CN_PIN_56     // Pin not routed to mikroBUS.
#define RIGHT_CN_PIN_57     // Pin not routed to mikroBUS.
#define RIGHT_CN_PIN_58 PB7
#define RIGHT_CN_PIN_59 PB8
#define RIGHT_CN_PIN_60 PB9
#define RIGHT_CN_PIN_61 PE0
#define RIGHT_CN_PIN_62 PE1
#define RIGHT_CN_PIN_63 PE2
#define RIGHT_CN_PIN_64 PE3
#define RIGHT_CN_PIN_65 PE4
#define RIGHT_CN_PIN_66 PE5
#define RIGHT_CN_PIN_67 PE6
#define RIGHT_CN_PIN_68     // Pin not routed to mikroBUS.
#define RIGHT_CN_PIN_70     // Pin not routed to mikroBUS.
#define RIGHT_CN_PIN_72 PC2
#define RIGHT_CN_PIN_73 PC3
#define RIGHT_CN_PIN_75 PA0

// Up connector
#define UP_CN_PIN_81        // Pin not routed to mikroBUS.
#define UP_CN_PIN_83    PA5
#define UP_CN_PIN_84    PA4
#define UP_CN_PIN_86        // Pin not routed to mikroBUS.
#define UP_CN_PIN_89    PB1
#define UP_CN_PIN_90    PB0
#define UP_CN_PIN_91    PE7
#define UP_CN_PIN_92        // Pin not routed to mikroBUS.
#define UP_CN_PIN_93    PE9
#define UP_CN_PIN_94    PE8
#define UP_CN_PIN_95    PE11
#define UP_CN_PIN_96    PE10
#define UP_CN_PIN_97    PE13
#define UP_CN_PIN_98    PE12
#define UP_CN_PIN_99    PE15
#define UP_CN_PIN_100       // Pin not routed to mikroBUS.

#define LCD_TFT_8BIT_CH0 PORT_E
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
