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
#define MCU_CARD_REV_MAJOR (1)
#define MCU_CARD_REV_MINOR (01)

#define NC HAL_PIN_NC

// Left connector
#define LEFT_CN_PIN_7       // Pin not routed.
#define LEFT_CN_PIN_8       // Pin not routed.
#define LEFT_CN_PIN_9   GPIO_PD7
#define LEFT_CN_PIN_10  GPIO_PD6
#define LEFT_CN_PIN_11  GPIO_PD5
#define LEFT_CN_PIN_12  GPIO_PD4
#define LEFT_CN_PIN_13  GPIO_PD3
#define LEFT_CN_PIN_14  GPIO_PD2
#define LEFT_CN_PIN_15  GPIO_PD1
#define LEFT_CN_PIN_16  GPIO_PD0
#define LEFT_CN_PIN_17      // Pin not routed.
#define LEFT_CN_PIN_18      // Pin not routed.
#define LEFT_CN_PIN_19  GPIO_PE5
#define LEFT_CN_PIN_20  GPIO_PE4
#define LEFT_CN_PIN_21  GPIO_PE3
#define LEFT_CN_PIN_22  GPIO_PE2
#define LEFT_CN_PIN_23      // Pin not routed.
#define LEFT_CN_PIN_24      // Pin not routed.

// Down connector
#define DOWN_CN_PIN_29      // Pin not routed.
#define DOWN_CN_PIN_30      // Pin not routed.
#define DOWN_CN_PIN_31  GPIO_PE0
#define DOWN_CN_PIN_32  GPIO_PE1
#define DOWN_CN_PIN_33  GPIO_PG1
#define DOWN_CN_PIN_34  GPIO_PG0
#define DOWN_CN_PIN_35  GPIO_PG3
#define DOWN_CN_PIN_36  GPIO_PG2
#define DOWN_CN_PIN_37      // Pin not routed.
#define DOWN_CN_PIN_41      // Pin not routed.
#define DOWN_CN_PIN_42      // Pin not routed.
#define DOWN_CN_PIN_43  GPIO_PF5
#define DOWN_CN_PIN_44      // Pin not routed.
#define DOWN_CN_PIN_45      // Pin not routed.
#define DOWN_CN_PIN_46  GPIO_PF2
#define DOWN_CN_PIN_47      // Pin not routed.
#define DOWN_CN_PIN_48      // Pin not routed.
#define DOWN_CN_PIN_49      // Pin not routed.
#define DOWN_CN_PIN_50      // Pin not routed.

// Right connector
#define RIGHT_CN_PIN_55     // Pin not routed.
#define RIGHT_CN_PIN_56     // Pin not routed.
#define RIGHT_CN_PIN_57     // Pin not routed.
#define RIGHT_CN_PIN_58     // Pin not routed.
#define RIGHT_CN_PIN_63 GPIO_PA2
#define RIGHT_CN_PIN_64     // Pin not routed.
#define RIGHT_CN_PIN_65 GPIO_PA0
#define RIGHT_CN_PIN_66 GPIO_PA1
#define RIGHT_CN_PIN_69 GPIO_PA4
#define RIGHT_CN_PIN_70     // Pin not routed.
#define RIGHT_CN_PIN_71 GPIO_PC0
#define RIGHT_CN_PIN_72 GPIO_PC1
#define RIGHT_CN_PIN_73 GPIO_PC7
#define RIGHT_CN_PIN_74 GPIO_PC6
#define RIGHT_CN_PIN_75     // Pin not routed.
#define RIGHT_CN_PIN_76     // Pin not routed.

// Up connector
#define UP_CN_PIN_85        // Pin not routed.
#define UP_CN_PIN_86        // Pin not routed.
#define UP_CN_PIN_87    GPIO_PC2
#define UP_CN_PIN_88    GPIO_PC3
#define UP_CN_PIN_89    GPIO_PC4
#define UP_CN_PIN_90    GPIO_PC5
#define UP_CN_PIN_91        // Pin not routed.
#define UP_CN_PIN_92        // Pin not routed.
#define UP_CN_PIN_93    GPIO_PB5
#define UP_CN_PIN_94    GPIO_PB4
#define UP_CN_PIN_95    GPIO_PB3
#define UP_CN_PIN_96    GPIO_PB2
#define UP_CN_PIN_97    GPIO_PB1
#define UP_CN_PIN_98    GPIO_PB0
#define UP_CN_PIN_99        // Pin not routed.
#define UP_CN_PIN_100       // Pin not routed.

#define MCU_CALIBRATION_XMIN 120
#define MCU_CALIBRATION_XMAX 910
#define MCU_CALIBRATION_YMIN 78
#define MCU_CALIBRATION_YMAX 945

#define MCU_THRESHOLD_LOWER (70)
#define MCU_THRESHOLD_UPPER (1000)

#define LCD_TFT_8BIT_CH0 GPIO_PORT_D
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
