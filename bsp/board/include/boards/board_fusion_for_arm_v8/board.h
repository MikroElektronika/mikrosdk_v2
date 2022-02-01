/****************************************************************************
**
** Copyright (C) 2022 MikroElektronika d.o.o.
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
#define BOARD_REV_MINOR (11)

#define BOARD_NAME "Fusion for ARM v8"

#include "mcu_card.h"
#include "mikrobus.h"

/// Mapping
#define MIKROBUS_1 1
#define MIKROBUS_1_AN LEFT_CN_PIN_144
#define MIKROBUS_1_RST LEFT_CN_PIN_143
#define MIKROBUS_1_CS LEFT_CN_PIN_142
#define MIKROBUS_1_SCK LEFT_CN_PIN_141
#define MIKROBUS_1_MISO LEFT_CN_PIN_140
#define MIKROBUS_1_MOSI LEFT_CN_PIN_139
#define MIKROBUS_1_PWM LEFT_CN_PIN_138
#define MIKROBUS_1_RX LEFT_CN_PIN_136
#define MIKROBUS_1_INT LEFT_CN_PIN_137
#define MIKROBUS_1_TX LEFT_CN_PIN_135
#define MIKROBUS_1_SCL LEFT_CN_PIN_134
#define MIKROBUS_1_SDA LEFT_CN_PIN_133

#define MIKROBUS_2 2
#define MIKROBUS_2_AN LEFT_CN_PIN_132
#define MIKROBUS_2_RST LEFT_CN_PIN_131
#define MIKROBUS_2_CS LEFT_CN_PIN_130
#define MIKROBUS_2_SCK LEFT_CN_PIN_129
#define MIKROBUS_2_MISO LEFT_CN_PIN_128
#define MIKROBUS_2_MOSI LEFT_CN_PIN_127
#define MIKROBUS_2_PWM LEFT_CN_PIN_126
#define MIKROBUS_2_RX LEFT_CN_PIN_124
#define MIKROBUS_2_INT LEFT_CN_PIN_125
#define MIKROBUS_2_TX LEFT_CN_PIN_123
#define MIKROBUS_2_SCL LEFT_CN_PIN_122
#define MIKROBUS_2_SDA LEFT_CN_PIN_121

#define MIKROBUS_3 3
#define MIKROBUS_3_AN LEFT_CN_PIN_120
#define MIKROBUS_3_RST LEFT_CN_PIN_119
#define MIKROBUS_3_CS LEFT_CN_PIN_118
#define MIKROBUS_3_SCK LEFT_CN_PIN_117
#define MIKROBUS_3_MISO LEFT_CN_PIN_116
#define MIKROBUS_3_MOSI LEFT_CN_PIN_115
#define MIKROBUS_3_PWM LEFT_CN_PIN_114
#define MIKROBUS_3_RX LEFT_CN_PIN_112
#define MIKROBUS_3_INT LEFT_CN_PIN_113
#define MIKROBUS_3_TX LEFT_CN_PIN_111
#define MIKROBUS_3_SCL LEFT_CN_PIN_110
#define MIKROBUS_3_SDA LEFT_CN_PIN_109

#define MIKROBUS_4 4
#define MIKROBUS_4_AN LEFT_CN_PIN_108
#define MIKROBUS_4_RST LEFT_CN_PIN_107
#define MIKROBUS_4_CS LEFT_CN_PIN_106
#define MIKROBUS_4_SCK LEFT_CN_PIN_105
#define MIKROBUS_4_MISO LEFT_CN_PIN_104
#define MIKROBUS_4_MOSI LEFT_CN_PIN_103
#define MIKROBUS_4_PWM LEFT_CN_PIN_102
#define MIKROBUS_4_RX LEFT_CN_PIN_100
#define MIKROBUS_4_INT LEFT_CN_PIN_101
#define MIKROBUS_4_TX LEFT_CN_PIN_099
#define MIKROBUS_4_SCL LEFT_CN_PIN_098
#define MIKROBUS_4_SDA LEFT_CN_PIN_097

#define MIKROBUS_5 5
#define MIKROBUS_5_AN LEFT_CN_PIN_096
#define MIKROBUS_5_RST LEFT_CN_PIN_095
#define MIKROBUS_5_CS LEFT_CN_PIN_094
#define MIKROBUS_5_SCK LEFT_CN_PIN_093
#define MIKROBUS_5_MISO LEFT_CN_PIN_092
#define MIKROBUS_5_MOSI LEFT_CN_PIN_091
#define MIKROBUS_5_PWM LEFT_CN_PIN_090
#define MIKROBUS_5_RX LEFT_CN_PIN_088
#define MIKROBUS_5_INT LEFT_CN_PIN_089
#define MIKROBUS_5_TX LEFT_CN_PIN_087
#define MIKROBUS_5_SCL LEFT_CN_PIN_086
#define MIKROBUS_5_SDA LEFT_CN_PIN_085

#define TFT_RST LEFT_CN_PIN_025
#define TFT_CS LEFT_CN_PIN_026
#define TFT_D_C LEFT_CN_PIN_027
#define TFT_RD LEFT_CN_PIN_028
#define TFT_WR LEFT_CN_PIN_029
#define TFT_TE LEFT_CN_PIN_055
#define TFT_GPIO LEFT_CN_PIN_054
#define TFT_BPWM LEFT_CN_PIN_057
#define TFT_D0 LEFT_CN_PIN_030
#define TFT_D1 LEFT_CN_PIN_031
#define TFT_D2 LEFT_CN_PIN_032
#define TFT_D3 LEFT_CN_PIN_033
#define TFT_D4 LEFT_CN_PIN_034
#define TFT_D5 LEFT_CN_PIN_035
#define TFT_D6 LEFT_CN_PIN_036
#define TFT_D7 LEFT_CN_PIN_037
#define TFT_D8 LEFT_CN_PIN_038
#define TFT_D9 LEFT_CN_PIN_039
#define TFT_D10 LEFT_CN_PIN_040
#define TFT_D11 LEFT_CN_PIN_041
#define TFT_D12 LEFT_CN_PIN_042
#define TFT_D13 LEFT_CN_PIN_043
#define TFT_D14 LEFT_CN_PIN_044
#define TFT_D15 LEFT_CN_PIN_045

#define CTP_SDA LEFT_CN_PIN_059
#define CTP_SCL LEFT_CN_PIN_058
#define CTP_WAKE LEFT_CN_PIN_061
#define CTP_INT LEFT_CN_PIN_060
#define CTP_RST LEFT_CN_PIN_062

#define AN1 RIGHT_CN_PIN_128
#define AN2 RIGHT_CN_PIN_127
#define AN3 RIGHT_CN_PIN_126
#define AN4 RIGHT_CN_PIN_125

#define USB_SW_ID RIGHT_CN_PIN_130
#define USB_VBUS RIGHT_CN_PIN_133
#define USB_N RIGHT_CN_PIN_132
#define USB_P RIGHT_CN_PIN_131
#define USB_PSW RIGHT_CN_PIN_129

#define USB_UART_TX RIGHT_CN_PIN_160
#define USB_UART_RX RIGHT_CN_PIN_159

#define CAN_RX RIGHT_CN_PIN_043
#define CAN_TX RIGHT_CN_PIN_044

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
