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
#define MCU_CARD_REV_MINOR (01)

#define NC HAL_PIN_NC

// Left connector
#define LEFT_CN_PIN_14  PD2
#define LEFT_CN_PIN_15  PD1
#define LEFT_CN_PIN_16  PD0
#define LEFT_CN_PIN_17      // Pin not routed to mikroBUS.
#define LEFT_CN_PIN_18      // Pin not routed to mikroBUS.
#define LEFT_CN_PIN_19  PE5
#define LEFT_CN_PIN_20  PE4
#define LEFT_CN_PIN_21  PE3
#define LEFT_CN_PIN_22  PE2
#define LEFT_CN_PIN_23      // Pin not routed to mikroBUS.
#define LEFT_CN_PIN_24      // Pin not routed to mikroBUS.

// Down connector
#define DOWN_CN_PIN_29      // Pin not routed to mikroBUS.
#define DOWN_CN_PIN_30      // Pin not routed to mikroBUS.
#define DOWN_CN_PIN_31  PE0
#define DOWN_CN_PIN_32  PE1
#define DOWN_CN_PIN_33  PG1
#define DOWN_CN_PIN_34  PG0
#define DOWN_CN_PIN_35  PG3
#define DOWN_CN_PIN_36  PG2
#define DOWN_CN_PIN_37      // Pin not routed to mikroBUS.
#define DOWN_CN_PIN_41      // Pin not routed to mikroBUS.
#define DOWN_CN_PIN_42      // Pin not routed to mikroBUS.
#define DOWN_CN_PIN_43  PF5
#define DOWN_CN_PIN_44      // Pin not routed to mikroBUS.
#define DOWN_CN_PIN_45      // Pin not routed to mikroBUS.
#define DOWN_CN_PIN_46  PF2
#define DOWN_CN_PIN_47      // Pin not routed to mikroBUS.
#define DOWN_CN_PIN_48      // Pin not routed to mikroBUS.

// Right connector
#define RIGHT_CN_PIN_55     // Pin not routed to mikroBUS.
#define RIGHT_CN_PIN_56     // Pin not routed to mikroBUS.
#define RIGHT_CN_PIN_58     // Pin not routed to mikroBUS.
#define RIGHT_CN_PIN_63 PA2
#define RIGHT_CN_PIN_64     // Pin not routed to mikroBUS.
#define RIGHT_CN_PIN_65 PA0
#define RIGHT_CN_PIN_66 PA1
#define RIGHT_CN_PIN_69 PA4
#define RIGHT_CN_PIN_70     // Pin not routed to mikroBUS.
#define RIGHT_CN_PIN_71 PC0
#define RIGHT_CN_PIN_72 PC1
#define RIGHT_CN_PIN_73 PC7
#define RIGHT_CN_PIN_74 PC6
#define RIGHT_CN_PIN_75     // Pin not routed to mikroBUS.
#define RIGHT_CN_PIN_76     // Pin not routed to mikroBUS.

// Up connector
#define UP_CN_PIN_87    PC2
#define UP_CN_PIN_88    PC3
#define UP_CN_PIN_89    PC4
#define UP_CN_PIN_90    PC5
#define UP_CN_PIN_91        // Pin not routed to mikroBUS.
#define UP_CN_PIN_92        // Pin not routed to mikroBUS.
#define UP_CN_PIN_93    PB5
#define UP_CN_PIN_94    PB4
#define UP_CN_PIN_95    PB3
#define UP_CN_PIN_96    PB2
#define UP_CN_PIN_97    PB1
#define UP_CN_PIN_98    PB0

#define MCU_CALIBRATION_XMIN 120
#define MCU_CALIBRATION_XMAX 910
#define MCU_CALIBRATION_YMIN 78
#define MCU_CALIBRATION_YMAX 945

#define MCU_THRESHOLD_LOWER (70)
#define MCU_THRESHOLD_UPPER (1000)

#define LCD_TFT_8BIT_CH0 PORT_D
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
