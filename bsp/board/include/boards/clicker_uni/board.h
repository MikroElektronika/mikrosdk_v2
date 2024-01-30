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
#define BOARD_REV_MINOR (0)

#define BOARD_NAME "UNI Clicker"

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
#define MIKROBUS_1_INT LEFT_CN_PIN_137
#define MIKROBUS_1_RX LEFT_CN_PIN_136
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
#define MIKROBUS_2_INT LEFT_CN_PIN_125
#define MIKROBUS_2_RX LEFT_CN_PIN_124
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
#define MIKROBUS_3_INT LEFT_CN_PIN_113
#define MIKROBUS_3_RX LEFT_CN_PIN_112
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
#define MIKROBUS_4_INT LEFT_CN_PIN_101
#define MIKROBUS_4_RX LEFT_CN_PIN_100
#define MIKROBUS_4_TX LEFT_CN_PIN_099
#define MIKROBUS_4_SCL LEFT_CN_PIN_098
#define MIKROBUS_4_SDA LEFT_CN_PIN_097

#define USB_UART_TX RIGHT_CN_PIN_159
#define USB_UART_RX RIGHT_CN_PIN_160

// LEDs
#define LED_1 LEFT_CN_PIN_035  // TFT_D5
#define LED_2 LEFT_CN_PIN_036  // TFT_D6
#define LED_3 LEFT_CN_PIN_037  // TFT_D7
#define LED_4 LEFT_CN_PIN_025  // TFT_RST

// Buttons
#define BUTTON_1 LEFT_CN_PIN_089  // MIKROBUS 5 INT
#define BUTTON_2 LEFT_CN_PIN_095  // MIKROBUS 5 RST
#define BUTTON_3 LEFT_CN_PIN_094  // MIKROBUS 5 CS
#define BUTTON_4 PG4

#ifdef __cplusplus
}
#endif

#endif // _BOARD_H_
// ------------------------------------------------------------------------- END
