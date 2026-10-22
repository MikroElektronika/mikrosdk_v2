/****************************************************************************
**
** Copyright (C) 2026 MikroElektronika d.o.o.
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

#define BOARD_NAME "RL78 L23 Fast Prototyping Board"

#include "hal_target.h"
#include "shield.h"

// Mapping
#define ARDUINO_CONNECTOR_A0        GPIO_P027
#define ARDUINO_CONNECTOR_A1        GPIO_P026
#define ARDUINO_CONNECTOR_A2        GPIO_P025
#define ARDUINO_CONNECTOR_A3        GPIO_P024
#define ARDUINO_CONNECTOR_A4        GPIO_P023
#define ARDUINO_CONNECTOR_A5        GPIO_P022
#define ARDUINO_CONNECTOR_D0        GPIO_P146
#define ARDUINO_CONNECTOR_D1        GPIO_P003
#define ARDUINO_CONNECTOR_D2        GPIO_P002
#define ARDUINO_CONNECTOR_D3        GPIO_P001
#define ARDUINO_CONNECTOR_D4        GPIO_P016
#define ARDUINO_CONNECTOR_D5        GPIO_P015
#define ARDUINO_CONNECTOR_D6        GPIO_P147
#define ARDUINO_CONNECTOR_D7        GPIO_P080
#define ARDUINO_CONNECTOR_D8        GPIO_P062
#define ARDUINO_CONNECTOR_D9        GPIO_P077
#define ARDUINO_CONNECTOR_D10       GPIO_P076
#define ARDUINO_CONNECTOR_D11       GPIO_P047
#define ARDUINO_CONNECTOR_D12       GPIO_P046
#define ARDUINO_CONNECTOR_D13       GPIO_P140
#define ARDUINO_CONNECTOR_SCL       GPIO_P060
#define ARDUINO_CONNECTOR_SDA       GPIO_P061

#define HEADER_CONNECTOR_J1_D1      GPIO_P130
#define HEADER_CONNECTOR_J1_D2      GPIO_P047
#define HEADER_CONNECTOR_J1_D3      GPIO_P046
#define HEADER_CONNECTOR_J1_D4      GPIO_P035
#define HEADER_CONNECTOR_J1_D5      GPIO_P034
#define HEADER_CONNECTOR_J1_D6      GPIO_P033
#define HEADER_CONNECTOR_J1_D7      GPIO_P032
#define HEADER_CONNECTOR_J1_D8      GPIO_P031
#define HEADER_CONNECTOR_J1_D9      GPIO_P030
#define HEADER_CONNECTOR_J1_D10     GPIO_P077
#define HEADER_CONNECTOR_J1_D11     GPIO_P076
#define HEADER_CONNECTOR_J1_D12     GPIO_P075
#define HEADER_CONNECTOR_J1_D13     GPIO_P074
#define HEADER_CONNECTOR_J1_D14     GPIO_P073
#define HEADER_CONNECTOR_J1_D15     GPIO_P072
#define HEADER_CONNECTOR_J1_D16     GPIO_P071
#define HEADER_CONNECTOR_J1_D17     GPIO_P070
#define HEADER_CONNECTOR_J1_D18     GPIO_P057
#define HEADER_CONNECTOR_J1_D19     GPIO_P056
#define HEADER_CONNECTOR_J1_D20     GPIO_P055
#define HEADER_CONNECTOR_J1_D21     GPIO_P054
#define HEADER_CONNECTOR_J1_D22     GPIO_P053
#define HEADER_CONNECTOR_J1_D23     GPIO_P052
#define HEADER_CONNECTOR_J1_D24     GPIO_P051
#define HEADER_CONNECTOR_J1_D25     GPIO_P050
#define HEADER_CONNECTOR_J1_D26     GPIO_P097
#define HEADER_CONNECTOR_J1_D27     GPIO_P096
#define HEADER_CONNECTOR_J1_D28     GPIO_P095
#define HEADER_CONNECTOR_J1_D29     GPIO_P094
#define HEADER_CONNECTOR_J1_D30     GPIO_P093
#define HEADER_CONNECTOR_J1_D31     GPIO_P092
#define HEADER_CONNECTOR_J1_D32     GPIO_P091
#define HEADER_CONNECTOR_J1_D33     GPIO_P090
#define HEADER_CONNECTOR_J1_D34     GPIO_P007
#define HEADER_CONNECTOR_J1_D35     GPIO_P006
#define HEADER_CONNECTOR_J1_D36     GPIO_P005
#define HEADER_CONNECTOR_J1_D37     GPIO_P004
#define HEADER_CONNECTOR_J1_D38     GPIO_P003
#define HEADER_CONNECTOR_J1_D39     GPIO_P002
#define HEADER_CONNECTOR_J1_D40     GPIO_P001
#define HEADER_CONNECTOR_J1_D41     GPIO_P000
#define HEADER_CONNECTOR_J1_D42     GPIO_P017
#define HEADER_CONNECTOR_J1_D43     GPIO_P016
#define HEADER_CONNECTOR_J1_D44     GPIO_P015
#define HEADER_CONNECTOR_J1_D45     GPIO_P014
#define HEADER_CONNECTOR_J1_D46     GPIO_P013
#define HEADER_CONNECTOR_J1_D47     GPIO_P012
#define HEADER_CONNECTOR_J1_D48     GPIO_P011
#define HEADER_CONNECTOR_J1_D49     GPIO_P010
#define HEADER_CONNECTOR_J1_D50     GPIO_P145
#define HEADER_CONNECTOR_J1_D51     GPIO_P144
#define HEADER_CONNECTOR_J1_D52     GPIO_P027
#define HEADER_CONNECTOR_J1_D53     GPIO_P026
#define HEADER_CONNECTOR_J1_D54     GPIO_P025
#define HEADER_CONNECTOR_J1_D55     GPIO_P024
#define HEADER_CONNECTOR_J1_D56     GPIO_P143
#define HEADER_CONNECTOR_J1_D57     GPIO_P142
#define HEADER_CONNECTOR_J1_D58     GPIO_P141
#define HEADER_CONNECTOR_J1_D59     GPIO_P023
#define HEADER_CONNECTOR_J1_D60     GPIO_P022

#define HEADER_CONNECTOR_J2_D1      GPIO_P127
#define HEADER_CONNECTOR_J2_D2      GPIO_P126
#define HEADER_CONNECTOR_J2_D3      GPIO_P087
#define HEADER_CONNECTOR_J2_D4      GPIO_P086
#define HEADER_CONNECTOR_J2_D5      GPIO_P085
#define HEADER_CONNECTOR_J2_D6      GPIO_P125
#define HEADER_CONNECTOR_J2_D7      GPIO_P140
#define HEADER_CONNECTOR_J2_D8      GPIO_P045
#define HEADER_CONNECTOR_J2_D9      GPIO_P044
#define HEADER_CONNECTOR_J2_D10     GPIO_P043
#define HEADER_CONNECTOR_J2_D11     GPIO_P042
#define HEADER_CONNECTOR_J2_D12     GPIO_P041
#define HEADER_CONNECTOR_J2_D13     GPIO_P066
#define HEADER_CONNECTOR_J2_D14     GPIO_P067
#define HEADER_CONNECTOR_J2_D15     GPIO_P040
#define HEADER_CONNECTOR_J2_D16     // Pin not routed.
#define HEADER_CONNECTOR_J2_D17     GPIO_P124
#define HEADER_CONNECTOR_J2_D18     GPIO_P123
#define HEADER_CONNECTOR_J2_D19     GPIO_P137
#define HEADER_CONNECTOR_J2_D20     GPIO_P122
#define HEADER_CONNECTOR_J2_D21     GPIO_P121
#define HEADER_CONNECTOR_J2_D22     GPIO_P060
#define HEADER_CONNECTOR_J2_D23     GPIO_P061
#define HEADER_CONNECTOR_J2_D24     GPIO_P064
#define HEADER_CONNECTOR_J2_D25     GPIO_P065
#define HEADER_CONNECTOR_J2_D26     GPIO_P062
#define HEADER_CONNECTOR_J2_D27     GPIO_P063
#define HEADER_CONNECTOR_J2_D28     GPIO_P084
#define HEADER_CONNECTOR_J2_D29     GPIO_P083
#define HEADER_CONNECTOR_J2_D30     GPIO_P082
#define HEADER_CONNECTOR_J2_D31     GPIO_P081
#define HEADER_CONNECTOR_J2_D32     GPIO_P080
#define HEADER_CONNECTOR_J2_D33     GPIO_P147
#define HEADER_CONNECTOR_J2_D34     GPIO_P146
#define HEADER_CONNECTOR_J2_D35     GPIO_P021
#define HEADER_CONNECTOR_J2_D36     GPIO_P020
#define HEADER_CONNECTOR_J2_D37     // Pin not routed.
#define HEADER_CONNECTOR_J2_D38     // Pin not routed.
#define HEADER_CONNECTOR_J2_D39     // Pin not routed.
#define HEADER_CONNECTOR_J2_D40     // Pin not routed.

#define BUTTON1    GPIO_P137

#define LED1       GPIO_P064
#define LED2       GPIO_P065

#ifdef __cplusplus
}
#endif

#endif    // _BOARD_H_
// ------------------------------------------------------------------------- END
