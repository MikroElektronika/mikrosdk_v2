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

#define BOARD_NAME "Fast Prototyping Board for RA2E3 MCU Group"

#include "hal_target.h"
#include "shield.h"

// Mapping
#define ARDUINO_CONNECTOR_A0        GPIO_P000
#define ARDUINO_CONNECTOR_A1        GPIO_P001
#define ARDUINO_CONNECTOR_A2        GPIO_P002
#define ARDUINO_CONNECTOR_A3        GPIO_P012
#define ARDUINO_CONNECTOR_A4        GPIO_P013
#define ARDUINO_CONNECTOR_A5        GPIO_P014
#define ARDUINO_CONNECTOR_D0        GPIO_P110
#define ARDUINO_CONNECTOR_D1        GPIO_P109
#define ARDUINO_CONNECTOR_D2        GPIO_P409
#define ARDUINO_CONNECTOR_D3        GPIO_P111
#define ARDUINO_CONNECTOR_D4        GPIO_P301
#define ARDUINO_CONNECTOR_D5        GPIO_P302
#define ARDUINO_CONNECTOR_D6        GPIO_P500
#define ARDUINO_CONNECTOR_D7        GPIO_P206
#define ARDUINO_CONNECTOR_D8        GPIO_P112
#define ARDUINO_CONNECTOR_D9        GPIO_P104
#define ARDUINO_CONNECTOR_D10       GPIO_P103
#define ARDUINO_CONNECTOR_D11       GPIO_P101
#define ARDUINO_CONNECTOR_D12       GPIO_P100
#define ARDUINO_CONNECTOR_D13       GPIO_P102
#define ARDUINO_CONNECTOR_SCL       GPIO_P400
#define ARDUINO_CONNECTOR_SDA       GPIO_P401

#define HEADER_CONNECTOR_D0         GPIO_P110
#define HEADER_CONNECTOR_D1         GPIO_P109
#define HEADER_CONNECTOR_D2         GPIO_P409
#define HEADER_CONNECTOR_D3         GPIO_P111
#define HEADER_CONNECTOR_D4         GPIO_P301
#define HEADER_CONNECTOR_D5         GPIO_P302
#define HEADER_CONNECTOR_D6         GPIO_P500
#define HEADER_CONNECTOR_D7         GPIO_P206
#define HEADER_CONNECTOR_D8         GPIO_P112
#define HEADER_CONNECTOR_D9         GPIO_P104
#define HEADER_CONNECTOR_D10        GPIO_P103
#define HEADER_CONNECTOR_D11        GPIO_P101
#define HEADER_CONNECTOR_D12        GPIO_P100
#define HEADER_CONNECTOR_D13        GPIO_P102
#define HEADER_CONNECTOR_D14        GPIO_P000
#define HEADER_CONNECTOR_D15        GPIO_P001
#define HEADER_CONNECTOR_D16        GPIO_P002
#define HEADER_CONNECTOR_D17        GPIO_P012
#define HEADER_CONNECTOR_D18        GPIO_P014   // This pin doesn't have SCL functionality, but routed to SCL pin on click shield mikrobus.
#define HEADER_CONNECTOR_D19        GPIO_P013   // This pin doesn't have SDA functionality, but routed to SDA pin on click shield mikrobus.

#define HEADER_CONNECTOR_J3_D1      GPIO_P300
#define HEADER_CONNECTOR_J3_D2      GPIO_P301
#define HEADER_CONNECTOR_J3_D3      GPIO_P302
#define HEADER_CONNECTOR_J3_D4      GPIO_P200
#define HEADER_CONNECTOR_J3_D5      GPIO_P201
#define HEADER_CONNECTOR_J3_D6      // Pin not routed.
#define HEADER_CONNECTOR_J3_D7      GPIO_P206
#define HEADER_CONNECTOR_J3_D8      GPIO_P207
#define HEADER_CONNECTOR_J3_D9      GPIO_P208
#define HEADER_CONNECTOR_J3_D10     GPIO_P913
#define HEADER_CONNECTOR_J3_D11     GPIO_P914
#define HEADER_CONNECTOR_J3_D12     GPIO_P915
#define HEADER_CONNECTOR_J3_D13     GPIO_P407
#define HEADER_CONNECTOR_J3_D14     GPIO_P408
#define HEADER_CONNECTOR_J3_D15     GPIO_P409
#define HEADER_CONNECTOR_J3_D16     // Pin not routed.
#define HEADER_CONNECTOR_J3_D17     GPIO_P212
#define HEADER_CONNECTOR_J3_D18     GPIO_P213
#define HEADER_CONNECTOR_J3_D19     // Pin not routed.
#define HEADER_CONNECTOR_J3_D20     GPIO_P214
#define HEADER_CONNECTOR_J3_D21     GPIO_P215
#define HEADER_CONNECTOR_J3_D22     // Pin not routed.
#define HEADER_CONNECTOR_J3_D23     GPIO_P400
#define HEADER_CONNECTOR_J3_D24     GPIO_P401

#define HEADER_CONNECTOR_J4_D1      GPIO_P108
#define HEADER_CONNECTOR_J4_D2      GPIO_P109
#define HEADER_CONNECTOR_J4_D3      GPIO_P110
#define HEADER_CONNECTOR_J4_D4      GPIO_P111
#define HEADER_CONNECTOR_J4_D5      GPIO_P112
#define HEADER_CONNECTOR_J4_D6      // Pin not routed.
#define HEADER_CONNECTOR_J4_D7      // Pin not routed.
#define HEADER_CONNECTOR_J4_D8      GPIO_P104
#define HEADER_CONNECTOR_J4_D9      GPIO_P103
#define HEADER_CONNECTOR_J4_D10     GPIO_P102
#define HEADER_CONNECTOR_J4_D11     GPIO_P101
#define HEADER_CONNECTOR_J4_D12     GPIO_P100
#define HEADER_CONNECTOR_J4_D13     GPIO_P500
#define HEADER_CONNECTOR_J4_D14     GPIO_P015
#define HEADER_CONNECTOR_J4_D15     GPIO_P014
#define HEADER_CONNECTOR_J4_D16     GPIO_P013
#define HEADER_CONNECTOR_J4_D17     GPIO_P012
#define HEADER_CONNECTOR_J4_D18     // Pin not routed.
#define HEADER_CONNECTOR_J4_D19     // Pin not routed.
#define HEADER_CONNECTOR_J4_D20     GPIO_P011
#define HEADER_CONNECTOR_J4_D21     GPIO_P010
#define HEADER_CONNECTOR_J4_D22     GPIO_P002
#define HEADER_CONNECTOR_J4_D23     GPIO_P001
#define HEADER_CONNECTOR_J4_D24     GPIO_P000

#define BUTTON1    GPIO_P200

#define LED1       GPIO_P213
#define LED2       GPIO_P914

#ifdef __cplusplus
}
#endif

#endif    // _BOARD_H_
// ------------------------------------------------------------------------- END
