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
#define LEFT_CN_PIN_1      // Pin not routed.
#define LEFT_CN_PIN_2      // Pin not routed.
#define LEFT_CN_PIN_3      // Pin not routed.
#define LEFT_CN_PIN_4      // Pin not routed.
#define LEFT_CN_PIN_5      // Pin not routed.
#define LEFT_CN_PIN_6      // Pin not routed.
#define LEFT_CN_PIN_7   PB6
#define LEFT_CN_PIN_8   PB7
#define LEFT_CN_PIN_9   PA9
#define LEFT_CN_PIN_10  PA10
#define LEFT_CN_PIN_11  PB8
#define LEFT_CN_PIN_12  PB9
#define LEFT_CN_PIN_13  PB10
#define LEFT_CN_PIN_14  PB11
#define LEFT_CN_PIN_15  PF13
#define LEFT_CN_PIN_16  PA1
#define LEFT_CN_PIN_17  PB12
#define LEFT_CN_PIN_18  PF12
#define LEFT_CN_PIN_19  PB14
#define LEFT_CN_PIN_20  PB13
#define LEFT_CN_PIN_21  PD14
#define LEFT_CN_PIN_22  PB15
#define LEFT_CN_PIN_23  PF4
#define LEFT_CN_PIN_24  PF5
#define LEFT_CN_PIN_25     // Pin not routed.
#define LEFT_CN_PIN_26     // Pin not routed.

// Down connector
#define DOWN_CN_PIN_27     // Pin not routed.
#define DOWN_CN_PIN_28     // Pin not routed.
#define DOWN_CN_PIN_29  PG2
#define DOWN_CN_PIN_30  PG3
#define DOWN_CN_PIN_31     // Pin not routed.
#define DOWN_CN_PIN_32     // Pin not routed.
#define DOWN_CN_PIN_33     // Pin not routed.
#define DOWN_CN_PIN_34     // Pin not routed.
#define DOWN_CN_PIN_35     // Pin not routed.
#define DOWN_CN_PIN_36  PF3
#define DOWN_CN_PIN_37  PF2
#define DOWN_CN_PIN_38  PD15
#define DOWN_CN_PIN_39  PA2
#define DOWN_CN_PIN_40  PF8
#define DOWN_CN_PIN_41  PA4
#define DOWN_CN_PIN_42  PA3
#define DOWN_CN_PIN_43  PA14
#define DOWN_CN_PIN_44  PA5
#define DOWN_CN_PIN_45  PD8
#define DOWN_CN_PIN_46  PA15
#define DOWN_CN_PIN_47  PD10
#define DOWN_CN_PIN_48  PD9
#define DOWN_CN_PIN_49  PD0
#define DOWN_CN_PIN_50  PD11
#define DOWN_CN_PIN_51     // Pin not routed.
#define DOWN_CN_PIN_52     // Pin not routed.

// Right connector
#define RIGHT_CN_PIN_53 PD1
#define RIGHT_CN_PIN_54    // Pin not routed.
#define RIGHT_CN_PIN_55 PD3
#define RIGHT_CN_PIN_56 PD2
#define RIGHT_CN_PIN_57 PD12
#define RIGHT_CN_PIN_58 PD13
#define RIGHT_CN_PIN_59 PD4
#define RIGHT_CN_PIN_60 PD5
#define RIGHT_CN_PIN_61 PD6
#define RIGHT_CN_PIN_62 PD7
#define RIGHT_CN_PIN_63 PF1
#define RIGHT_CN_PIN_64 PF0
#define RIGHT_CN_PIN_65 PG0
#define RIGHT_CN_PIN_66 PG1
#define RIGHT_CN_PIN_67 PA7
#define RIGHT_CN_PIN_68 PA6
#define RIGHT_CN_PIN_69 PE1
#define RIGHT_CN_PIN_70 PE0
#define RIGHT_CN_PIN_71 PG12
#define RIGHT_CN_PIN_72 PG14
#define RIGHT_CN_PIN_73 PE2
#define RIGHT_CN_PIN_74 PG13
#define RIGHT_CN_PIN_75 PE4
#define RIGHT_CN_PIN_76 PE3
#define RIGHT_CN_PIN_77    // Pin not routed.
#define RIGHT_CN_PIN_78    // Pin not routed.

// Up connector
#define UP_CN_PIN_79       // Pin not routed.
#define UP_CN_PIN_80       // Pin not routed.
#define UP_CN_PIN_81    PE5
#define UP_CN_PIN_82    PG15
#define UP_CN_PIN_83    PE7
#define UP_CN_PIN_84    PE6
#define UP_CN_PIN_85    PC2
#define UP_CN_PIN_86    PC1
#define UP_CN_PIN_87    PC4
#define UP_CN_PIN_88    PC3
#define UP_CN_PIN_89    PG7
#define UP_CN_PIN_90    PG6
#define UP_CN_PIN_91       // Pin not routed.
#define UP_CN_PIN_92    PG8
#define UP_CN_PIN_93    PA0
#define UP_CN_PIN_94    PG9
#define UP_CN_PIN_95    PE9
#define UP_CN_PIN_96    PE8
#define UP_CN_PIN_97    PB4
#define UP_CN_PIN_98    PB5
#define UP_CN_PIN_99    PB2
#define UP_CN_PIN_100   PB3
#define UP_CN_PIN_101   PB0
#define UP_CN_PIN_102   PB1
#define UP_CN_PIN_103      // Pin not routed.
#define UP_CN_PIN_104      // Pin not routed.

#define MCU_CALIBRATION_XMIN 120
#define MCU_CALIBRATION_XMAX 910
#define MCU_CALIBRATION_YMIN 78
#define MCU_CALIBRATION_YMAX 945

#define MCU_THRESHOLD_LOWER (70)
#define MCU_THRESHOLD_UPPER (1000)

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
