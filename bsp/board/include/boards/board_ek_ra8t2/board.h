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
 * @file  board.h
 * @brief Main board pin mapping.
 */

#ifndef _BOARD_H_
#define _BOARD_H_

#ifdef __cplusplus
extern "C"
{
#endif

#define BOARD_NAME "Evaluation Kit for RA8T2 MCU Group"

#include "mikrobus.h"

// Mapping
#define MIKROBUS_1      1
#define MIKROBUS_1_AN   GPIO_P004
#define MIKROBUS_1_RST  GPIO_P402
#define MIKROBUS_1_CS   GPIO_P204
#define MIKROBUS_1_SCK  GPIO_P203
#define MIKROBUS_1_MISO GPIO_P313
#define MIKROBUS_1_MOSI GPIO_P202
#define MIKROBUS_1_PWM  GPIO_P810
#define MIKROBUS_1_INT  GPIO_P903
#define MIKROBUS_1_RX   GPIO_P808
#define MIKROBUS_1_TX   GPIO_P809
#define MIKROBUS_1_SCL  GPIO_P400
#define MIKROBUS_1_SDA  GPIO_P401

#define ARDUINO_CONNECTOR_A0        GPIO_P001
#define ARDUINO_CONNECTOR_A1        GPIO_P007
#define ARDUINO_CONNECTOR_A2        GPIO_P003
#define ARDUINO_CONNECTOR_A3        GPIO_P004
#define ARDUINO_CONNECTOR_A4        GPIO_P014
#define ARDUINO_CONNECTOR_A5        GPIO_P015
#define ARDUINO_CONNECTOR_D0        GPIO_P808
#define ARDUINO_CONNECTOR_D1        GPIO_P809
#define ARDUINO_CONNECTOR_D2        GPIO_P011
#define ARDUINO_CONNECTOR_D3        GPIO_P811
#define ARDUINO_CONNECTOR_D4        GPIO_P810
#define ARDUINO_CONNECTOR_D5        GPIO_P601
#define ARDUINO_CONNECTOR_D6        GPIO_P600
#define ARDUINO_CONNECTOR_D7        GPIO_P502
#define ARDUINO_CONNECTOR_D8        GPIO_P903
#define ARDUINO_CONNECTOR_D9        GPIO_P110
#define ARDUINO_CONNECTOR_D10       GPIO_P204
#define ARDUINO_CONNECTOR_D11       GPIO_P202
#define ARDUINO_CONNECTOR_D12       GPIO_P313
#define ARDUINO_CONNECTOR_D13       GPIO_P203
#define ARDUINO_CONNECTOR_SDA       GPIO_P401
#define ARDUINO_CONNECTOR_SCL       GPIO_P400

#define HEADER_CONNECTOR_J2_D1     // Pin not routed.
#define HEADER_CONNECTOR_J2_D2     // Pin not routed.
#define HEADER_CONNECTOR_J2_D3     GPIO_PC15
#define HEADER_CONNECTOR_J2_D4     // Pin not routed.
#define HEADER_CONNECTOR_J2_D5     // Pin not routed.
#define HEADER_CONNECTOR_J2_D6     GPIO_PC09
#define HEADER_CONNECTOR_J2_D7     // Pin not routed.
#define HEADER_CONNECTOR_J2_D8     GPIO_P314
#define HEADER_CONNECTOR_J2_D9     GPIO_P901
#define HEADER_CONNECTOR_J2_D10    GPIO_P500
#define HEADER_CONNECTOR_J2_D11    GPIO_P008
#define HEADER_CONNECTOR_J2_D12    GPIO_P000
#define HEADER_CONNECTOR_J2_D13    GPIO_P205
#define HEADER_CONNECTOR_J2_D14    GPIO_PC08
#define HEADER_CONNECTOR_J2_D15    GPIO_P602
#define HEADER_CONNECTOR_J2_D16    GPIO_P315
#define HEADER_CONNECTOR_J2_D17    GPIO_P102
#define HEADER_CONNECTOR_J2_D18    GPIO_P900
#define HEADER_CONNECTOR_J2_D19    // Pin not routed.
#define HEADER_CONNECTOR_J2_D20    // Pin not routed.
#define HEADER_CONNECTOR_J2_D21    GPIO_P812
#define HEADER_CONNECTOR_J2_D22    GPIO_P501
#define HEADER_CONNECTOR_J2_D23    GPIO_P005
#define HEADER_CONNECTOR_J2_D24    GPIO_P013
#define HEADER_CONNECTOR_J2_D25    GPIO_P009
#define HEADER_CONNECTOR_J2_D26    GPIO_P512
#define HEADER_CONNECTOR_J2_D27    // Pin not routed.
#define HEADER_CONNECTOR_J2_D28    // Pin not routed.
#define HEADER_CONNECTOR_J2_D29    GPIO_P415
#define HEADER_CONNECTOR_J2_D30    GPIO_P714
#define HEADER_CONNECTOR_J2_D31    GPIO_P814
#define HEADER_CONNECTOR_J2_D32    GPIO_P410
#define HEADER_CONNECTOR_J2_D33    GPIO_P402
#define HEADER_CONNECTOR_J2_D34    GPIO_P409
#define HEADER_CONNECTOR_J2_D35    GPIO_P414
#define HEADER_CONNECTOR_J2_D36    GPIO_P400
#define HEADER_CONNECTOR_J2_D37    GPIO_P815
#define HEADER_CONNECTOR_J2_D38    GPIO_P401
#define HEADER_CONNECTOR_J2_D39    // Pin not routed.
#define HEADER_CONNECTOR_J2_D40    // Pin not routed.

#define HEADER_CONNECTOR_J3_D1     // Pin not routed.
#define HEADER_CONNECTOR_J3_D2     // Pin not routed.
#define HEADER_CONNECTOR_J3_D3     // Pin not routed.
#define HEADER_CONNECTOR_J3_D4     // Pin not routed.
#define HEADER_CONNECTOR_J3_D5     GPIO_P303
#define HEADER_CONNECTOR_J3_D6     GPIO_P915
#define HEADER_CONNECTOR_J3_D7     GPIO_P615
#define HEADER_CONNECTOR_J3_D8     // Pin not routed.
#define HEADER_CONNECTOR_J3_D9     GPIO_P210
#define HEADER_CONNECTOR_J3_D10    GPIO_P211
#define HEADER_CONNECTOR_J3_D11    // Pin not routed.
#define HEADER_CONNECTOR_J3_D12    GPIO_P914
#define HEADER_CONNECTOR_J3_D13    GPIO_PC12
#define HEADER_CONNECTOR_J3_D14    GPIO_P200
#define HEADER_CONNECTOR_J3_D15    GPIO_PC10
#define HEADER_CONNECTOR_J3_D16    GPIO_P201
#define HEADER_CONNECTOR_J3_D17    GPIO_P109
#define HEADER_CONNECTOR_J3_D18    GPIO_PA07
#define HEADER_CONNECTOR_J3_D19    GPIO_P108
#define HEADER_CONNECTOR_J3_D20    GPIO_P111
#define HEADER_CONNECTOR_J3_D21    GPIO_P403
#define HEADER_CONNECTOR_J3_D22    GPIO_P404
#define HEADER_CONNECTOR_J3_D23    GPIO_PB14
#define HEADER_CONNECTOR_J3_D24    GPIO_P002
#define HEADER_CONNECTOR_J3_D25    GPIO_P511
#define HEADER_CONNECTOR_J3_D26    GPIO_P212
#define HEADER_CONNECTOR_J3_D27    GPIO_P213
#define HEADER_CONNECTOR_J3_D28    GPIO_P215
#define HEADER_CONNECTOR_J3_D29    GPIO_P214
#define HEADER_CONNECTOR_J3_D30    // Pin not routed.
#define HEADER_CONNECTOR_J3_D31    // Pin not routed.
#define HEADER_CONNECTOR_J3_D32    GPIO_PB11
#define HEADER_CONNECTOR_J3_D33    GPIO_PB12
#define HEADER_CONNECTOR_J3_D34    GPIO_PB13
#define HEADER_CONNECTOR_J3_D35    // Pin not routed.
#define HEADER_CONNECTOR_J3_D36    // Pin not routed.
#define HEADER_CONNECTOR_J3_D37    // Pin not routed.
#define HEADER_CONNECTOR_J3_D38    // Pin not routed.
#define HEADER_CONNECTOR_J3_D39    // Pin not routed.
#define HEADER_CONNECTOR_J3_D40    // Pin not routed.

#define BUTTON1    GPIO_P009
#define BUTTON2    GPIO_P008

#define LED1       GPIO_P714
#define LED2       GPIO_P303
#define LED3       GPIO_PA07

#ifdef __cplusplus
}
#endif

#endif    // _BOARD_H_
// ------------------------------------------------------------------------- END
