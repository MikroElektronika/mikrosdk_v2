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

#define BOARD_NAME "Evaluation Kit for RA6M3 MCU Group"

#include "mikrobus.h"

// Mapping
#define MIKROBUS_1      1
#define MIKROBUS_1_AN   GPIO_P000
#define MIKROBUS_1_RST  GPIO_P413
#define MIKROBUS_1_CS   GPIO_P414
#define MIKROBUS_1_SCK  GPIO_P412
#define MIKROBUS_1_MISO GPIO_P410
#define MIKROBUS_1_MOSI GPIO_P411
#define MIKROBUS_1_PWM  GPIO_P415
#define MIKROBUS_1_INT  GPIO_P505
#define MIKROBUS_1_RX   GPIO_P614
#define MIKROBUS_1_TX   GPIO_P613
#define MIKROBUS_1_SCL  GPIO_P515
#define MIKROBUS_1_SDA  GPIO_P511

#define ARDUINO_CONNECTOR_A0        GPIO_P000
#define ARDUINO_CONNECTOR_A1        GPIO_P001
#define ARDUINO_CONNECTOR_A2        GPIO_P002
#define ARDUINO_CONNECTOR_A3        GPIO_P507
#define ARDUINO_CONNECTOR_A4        GPIO_P508
#define ARDUINO_CONNECTOR_A5        GPIO_P014
#define ARDUINO_CONNECTOR_D0        GPIO_P614
#define ARDUINO_CONNECTOR_D1        GPIO_P613
#define ARDUINO_CONNECTOR_D2        GPIO_P506
#define ARDUINO_CONNECTOR_D3        GPIO_P505
#define ARDUINO_CONNECTOR_D4        GPIO_P908
#define ARDUINO_CONNECTOR_D5        GPIO_P907
#define ARDUINO_CONNECTOR_D6        GPIO_P504
#define ARDUINO_CONNECTOR_D7        GPIO_P503
#define ARDUINO_CONNECTOR_D8        GPIO_P611
#define ARDUINO_CONNECTOR_D9        GPIO_P415
#define ARDUINO_CONNECTOR_D10       GPIO_P414
#define ARDUINO_CONNECTOR_D11       GPIO_P411
#define ARDUINO_CONNECTOR_D12       GPIO_P410
#define ARDUINO_CONNECTOR_D13       GPIO_P412
#define ARDUINO_CONNECTOR_SCL       GPIO_P512
#define ARDUINO_CONNECTOR_SDA       GPIO_P511

#define HEADER_CONNECTOR_J1_D1      // Pin not routed.
#define HEADER_CONNECTOR_J1_D2      // Pin not routed.
#define HEADER_CONNECTOR_J1_D3      GPIO_P104
#define HEADER_CONNECTOR_J1_D4      GPIO_P600
#define HEADER_CONNECTOR_J1_D5      GPIO_P512
#define HEADER_CONNECTOR_J1_D6      GPIO_P601
#define HEADER_CONNECTOR_J1_D7      GPIO_P107
#define HEADER_CONNECTOR_J1_D8      GPIO_P106
#define HEADER_CONNECTOR_J1_D9      GPIO_P600
#define HEADER_CONNECTOR_J1_D10     GPIO_P602
#define HEADER_CONNECTOR_J1_D11     GPIO_P602
#define HEADER_CONNECTOR_J1_D12     GPIO_P601
#define HEADER_CONNECTOR_J1_D13     GPIO_P610
#define HEADER_CONNECTOR_J1_D14     GPIO_P114
#define HEADER_CONNECTOR_J1_D15     GPIO_P608
#define HEADER_CONNECTOR_J1_D16     GPIO_P609
#define HEADER_CONNECTOR_J1_D17     GPIO_P115
#define HEADER_CONNECTOR_J1_D18     GPIO_P113
#define HEADER_CONNECTOR_J1_D19     GPIO_P113
#define HEADER_CONNECTOR_J1_D20     GPIO_P114
#define HEADER_CONNECTOR_J1_D21     GPIO_P511
#define HEADER_CONNECTOR_J1_D22     GPIO_P302
#define HEADER_CONNECTOR_J1_D23     GPIO_P111
#define HEADER_CONNECTOR_J1_D24     GPIO_P112
#define HEADER_CONNECTOR_J1_D25     GPIO_P301
#define HEADER_CONNECTOR_J1_D26     GPIO_P303
#define HEADER_CONNECTOR_J1_D27     GPIO_P303
#define HEADER_CONNECTOR_J1_D28     GPIO_P302
#define HEADER_CONNECTOR_J1_D29     GPIO_P102
#define HEADER_CONNECTOR_J1_D30     // Pin not routed.
#define HEADER_CONNECTOR_J1_D31     // Pin not routed.
#define HEADER_CONNECTOR_J1_D32     GPIO_P103
#define HEADER_CONNECTOR_J1_D33     GPIO_P301
#define HEADER_CONNECTOR_J1_D34     // Pin not routed.
#define HEADER_CONNECTOR_J1_D35     GPIO_P304
#define HEADER_CONNECTOR_J1_D36     // Pin not routed.
#define HEADER_CONNECTOR_J1_D37     GPIO_P101
#define HEADER_CONNECTOR_J1_D38     GPIO_P206
#define HEADER_CONNECTOR_J1_D39     GPIO_P603
#define HEADER_CONNECTOR_J1_D40     // Pin not routed.

#define HEADER_CONNECTOR_J2_D1      // Pin not routed.
#define HEADER_CONNECTOR_J2_D2      // Pin not routed.
#define HEADER_CONNECTOR_J2_D3      GPIO_P207
#define HEADER_CONNECTOR_J2_D4      GPIO_P205
#define HEADER_CONNECTOR_J2_D5      GPIO_P204
#define HEADER_CONNECTOR_J2_D6      GPIO_P203
#define HEADER_CONNECTOR_J2_D7      GPIO_P202
#define HEADER_CONNECTOR_J2_D8      GPIO_P313
#define HEADER_CONNECTOR_J2_D9      GPIO_P314
#define HEADER_CONNECTOR_J2_D10     GPIO_P315
#define HEADER_CONNECTOR_J2_D11     GPIO_P900
#define HEADER_CONNECTOR_J2_D12     GPIO_P901
#define HEADER_CONNECTOR_J2_D13     // Pin not routed.
#define HEADER_CONNECTOR_J2_D14     GPIO_P201
#define HEADER_CONNECTOR_J2_D15     GPIO_P200
#define HEADER_CONNECTOR_J2_D16     GPIO_P908
#define HEADER_CONNECTOR_J2_D17     GPIO_P907
#define HEADER_CONNECTOR_J2_D18     GPIO_P906
#define HEADER_CONNECTOR_J2_D19     GPIO_P905
#define HEADER_CONNECTOR_J2_D20     GPIO_P312
#define HEADER_CONNECTOR_J2_D21     GPIO_P311
#define HEADER_CONNECTOR_J2_D22     GPIO_P310
#define HEADER_CONNECTOR_J2_D23     GPIO_P309
#define HEADER_CONNECTOR_J2_D24     GPIO_P308
#define HEADER_CONNECTOR_J2_D25     GPIO_P307
#define HEADER_CONNECTOR_J2_D26     GPIO_P306
#define HEADER_CONNECTOR_J2_D27     GPIO_P305
#define HEADER_CONNECTOR_J2_D28     // Pin not routed.
#define HEADER_CONNECTOR_J2_D29     GPIO_P612
#define HEADER_CONNECTOR_J2_D30     GPIO_P611
#define HEADER_CONNECTOR_J2_D31     GPIO_P614
#define HEADER_CONNECTOR_J2_D32     GPIO_P613
#define HEADER_CONNECTOR_J2_D33     GPIO_PA08
#define HEADER_CONNECTOR_J2_D34     GPIO_P615
#define HEADER_CONNECTOR_J2_D35     GPIO_PA10
#define HEADER_CONNECTOR_J2_D36     GPIO_PA09
#define HEADER_CONNECTOR_J2_D37     GPIO_PA00
#define HEADER_CONNECTOR_J2_D38     GPIO_PA01
#define HEADER_CONNECTOR_J2_D39     // Pin not routed.
#define HEADER_CONNECTOR_J2_D40     GPIO_P607

#define HEADER_CONNECTOR_J3_D1      // Pin not routed.
#define HEADER_CONNECTOR_J3_D2      GPIO_P001
#define HEADER_CONNECTOR_J3_D3      GPIO_P000
#define HEADER_CONNECTOR_J3_D4      GPIO_P806
#define HEADER_CONNECTOR_J3_D5      GPIO_P805
#define HEADER_CONNECTOR_J3_D6      GPIO_P513
#define HEADER_CONNECTOR_J3_D7      GPIO_P512
#define HEADER_CONNECTOR_J3_D8      GPIO_P511
#define HEADER_CONNECTOR_J3_D9      GPIO_P401
#define HEADER_CONNECTOR_J3_D10     GPIO_P400
#define HEADER_CONNECTOR_J3_D11     GPIO_P403
#define HEADER_CONNECTOR_J3_D12     GPIO_P402
#define HEADER_CONNECTOR_J3_D13     GPIO_P405
#define HEADER_CONNECTOR_J3_D14     GPIO_P404
#define HEADER_CONNECTOR_J3_D15     GPIO_P700
#define HEADER_CONNECTOR_J3_D16     GPIO_P406
#define HEADER_CONNECTOR_J3_D17     GPIO_P702
#define HEADER_CONNECTOR_J3_D18     GPIO_P701
#define HEADER_CONNECTOR_J3_D19     GPIO_P704
#define HEADER_CONNECTOR_J3_D20     GPIO_P703
#define HEADER_CONNECTOR_J3_D21     GPIO_P706
#define HEADER_CONNECTOR_J3_D22     GPIO_P705
#define HEADER_CONNECTOR_J3_D23     GPIO_PB00
#define HEADER_CONNECTOR_J3_D24     GPIO_P707
#define HEADER_CONNECTOR_J3_D25     // Pin not routed.
#define HEADER_CONNECTOR_J3_D26     GPIO_PB01
#define HEADER_CONNECTOR_J3_D27     GPIO_P213
#define HEADER_CONNECTOR_J3_D28     // Pin not routed.
#define HEADER_CONNECTOR_J3_D29     GPIO_P708
#define HEADER_CONNECTOR_J3_D30     GPIO_P212
#define HEADER_CONNECTOR_J3_D31     GPIO_P414
#define HEADER_CONNECTOR_J3_D32     GPIO_P415
#define HEADER_CONNECTOR_J3_D33     GPIO_P412
#define HEADER_CONNECTOR_J3_D34     GPIO_P413
#define HEADER_CONNECTOR_J3_D35     GPIO_P410
#define HEADER_CONNECTOR_J3_D36     GPIO_P411
#define HEADER_CONNECTOR_J3_D37     GPIO_P408
#define HEADER_CONNECTOR_J3_D38     GPIO_P409
#define HEADER_CONNECTOR_J3_D39     // Pin not routed.
#define HEADER_CONNECTOR_J3_D40     GPIO_P407

#define HEADER_CONNECTOR_J4_D1      // Pin not routed.
#define HEADER_CONNECTOR_J4_D2      GPIO_P606
#define HEADER_CONNECTOR_J4_D3      GPIO_P605
#define HEADER_CONNECTOR_J4_D4      GPIO_P604
#define HEADER_CONNECTOR_J4_D5      // Pin not routed.
#define HEADER_CONNECTOR_J4_D6      GPIO_P100
#define HEADER_CONNECTOR_J4_D7      GPIO_P105
#define HEADER_CONNECTOR_J4_D8      GPIO_P800
#define HEADER_CONNECTOR_J4_D9      GPIO_P801
#define HEADER_CONNECTOR_J4_D10     GPIO_P802
#define HEADER_CONNECTOR_J4_D11     GPIO_P803
#define HEADER_CONNECTOR_J4_D12     GPIO_P804
#define HEADER_CONNECTOR_J4_D13     GPIO_P500
#define HEADER_CONNECTOR_J4_D14     GPIO_P501
#define HEADER_CONNECTOR_J4_D15     // Pin not routed.
#define HEADER_CONNECTOR_J4_D16     // Pin not routed.
#define HEADER_CONNECTOR_J4_D17     // Pin not routed.
#define HEADER_CONNECTOR_J4_D18     // Pin not routed.
#define HEADER_CONNECTOR_J4_D19     // Pin not routed.
#define HEADER_CONNECTOR_J4_D20     // Pin not routed.
#define HEADER_CONNECTOR_J4_D21     GPIO_P502
#define HEADER_CONNECTOR_J4_D22     GPIO_P503
#define HEADER_CONNECTOR_J4_D23     GPIO_P504
#define HEADER_CONNECTOR_J4_D24     GPIO_P505
#define HEADER_CONNECTOR_J4_D25     GPIO_P506
#define HEADER_CONNECTOR_J4_D26     GPIO_P507
#define HEADER_CONNECTOR_J4_D27     GPIO_P508
#define HEADER_CONNECTOR_J4_D28     GPIO_P015
#define HEADER_CONNECTOR_J4_D29     GPIO_P014
#define HEADER_CONNECTOR_J4_D30     GPIO_P010
#define HEADER_CONNECTOR_J4_D31     GPIO_P009
#define HEADER_CONNECTOR_J4_D32     GPIO_P008
#define HEADER_CONNECTOR_J4_D33     GPIO_P007
#define HEADER_CONNECTOR_J4_D34     GPIO_P006
#define HEADER_CONNECTOR_J4_D35     GPIO_P005
#define HEADER_CONNECTOR_J4_D36     GPIO_P004
#define HEADER_CONNECTOR_J4_D37     GPIO_P003
#define HEADER_CONNECTOR_J4_D38     GPIO_P002
#define HEADER_CONNECTOR_J4_D39     // Pin not routed.
#define HEADER_CONNECTOR_J4_D40     // Pin not routed.

#define PUSH_BUTTON1    GPIO_P009
#define PUSH_BUTTON2    GPIO_P008

#define USER_LED1       GPIO_P403
#define USER_LED2       GPIO_P400
#define USER_LED3       GPIO_P100

#ifdef __cplusplus
}
#endif

#endif    // _BOARD_H_
// ------------------------------------------------------------------------- END
