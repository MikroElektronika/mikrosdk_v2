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
** EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES
** OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT.
** IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM,
** DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT
** OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE
** OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
**
****************************************************************************/
/*!
 * @file  board.h
 * @brief Main board pin mapping.
 */

#ifndef _BOARD_H_
#define _BOARD_H_

#ifdef __cplusplus
extern "C"{
#endif

// Hardware revision number
#define BOARD_REV_MAJOR (1)
#define BOARD_REV_MINOR (01)

#define BOARD_NAME "EasyMX PRO v7 for TIVA"

#include "mcu_card.h"
#include "mikrobus.h"

/// Mapping
#define MIKROBUS_1 1
#define MIKROBUS_1_AN   DOWN_CN_PIN_44
#define MIKROBUS_1_RST  RIGHT_CN_PIN_67
#define MIKROBUS_1_CS   LEFT_CN_PIN_16
#define MIKROBUS_1_SCK  UP_CN_PIN_84
#define MIKROBUS_1_MISO UP_CN_PIN_86
#define MIKROBUS_1_MOSI UP_CN_PIN_85
#define MIKROBUS_1_PWM  RIGHT_CN_PIN_56
#define MIKROBUS_1_INT  UP_CN_PIN_93
#define MIKROBUS_1_RX   RIGHT_CN_PIN_74
#define MIKROBUS_1_TX   RIGHT_CN_PIN_73
#define MIKROBUS_1_SCL  LEFT_CN_PIN_18
#define MIKROBUS_1_SDA  LEFT_CN_PIN_17

#define MIKROBUS_2 2
#define MIKROBUS_2_AN   DOWN_CN_PIN_45
#define MIKROBUS_2_RST  RIGHT_CN_PIN_66
#define MIKROBUS_2_CS   DOWN_CN_PIN_41
#define MIKROBUS_2_SCK  UP_CN_PIN_84
#define MIKROBUS_2_MISO UP_CN_PIN_86
#define MIKROBUS_2_MOSI UP_CN_PIN_85
#define MIKROBUS_2_PWM  RIGHT_CN_PIN_55
#define MIKROBUS_2_INT  DOWN_CN_PIN_49
#define MIKROBUS_2_RX   RIGHT_CN_PIN_76
#define MIKROBUS_2_TX   RIGHT_CN_PIN_75
#define MIKROBUS_2_SCL  LEFT_CN_PIN_18
#define MIKROBUS_2_SDA  LEFT_CN_PIN_17

#define USB_UART_TX  DOWN_CN_PIN_48
#define USB_UART_RX  DOWN_CN_PIN_47
#define USB_UARTB_TX RIGHT_CN_PIN_75
#define USB_UARTB_RX RIGHT_CN_PIN_76

#define TFT_CS1  RIGHT_CN_PIN_70
#define TFT_CS2  RIGHT_CN_PIN_71
#define TFT_RS   UP_CN_PIN_102
#define TFT_R_W  UP_CN_PIN_101
#define TFT_E    UP_CN_PIN_100
#define TFT_D0   LEFT_CN_PIN_11
#define TFT_D1   LEFT_CN_PIN_10
#define TFT_D2   LEFT_CN_PIN_9
#define TFT_D3   LEFT_CN_PIN_8
#define TFT_D4   LEFT_CN_PIN_20
#define TFT_D5   LEFT_CN_PIN_19
#define TFT_D6   DOWN_CN_PIN_38
#define TFT_D7   DOWN_CN_PIN_37
#define TFT_RST  UP_CN_PIN_99
#define TFT_BPWM RIGHT_CN_PIN_58

#define TFT_RD TFT_CS1
#define TFT_WR TFT_CS2
#define TFT_CS TFT_E

#define TP_MIKROE_XL DOWN_CN_PIN_39
#define TP_MIKROE_XR RIGHT_CN_PIN_68
#define TP_MIKROE_YU RIGHT_CN_PIN_69
#define TP_MIKROE_YD DOWN_CN_PIN_40

// Default TP_MIKROE touch panel calibration values.
#define TP_MIKROE_CALIBRATION_XMIN 340
#define TP_MIKROE_CALIBRATION_XMAX 3600
#define TP_MIKROE_CALIBRATION_YMIN 240
#define TP_MIKROE_CALIBRATION_YMAX 3700

#define TP_MIKROE_PRESSURE_THRESHOLD_LOWER (200)
#define TP_MIKROE_PRESSURE_THRESHOLD_UPPER (3800)

#define TFT_8BIT_DATA_PORT_CH0 LCD_TFT_8BIT_CH0
#define TFT_8BIT_DATA_PORT_CH0_MASK LCD_TFT_CH0_8BIT_MASK

#define TFT_16BIT_DATA_PORT_CH0 LCD_TFT_16BIT_CH0
#define TFT_16BIT_DATA_PORT_CH0_MASK LCD_TFT_16BIT_CH0_MASK

#define TFT_16BIT_DATA_PORT_CH1 LCD_TFT_16BIT_CH1
#define TFT_16BIT_DATA_PORT_CH1_MASK LCD_TFT_16BIT_CH1_MASK

#ifdef __cplusplus
}
#endif

#endif // _BOARD_H_
// ------------------------------------------------------------------------- END
