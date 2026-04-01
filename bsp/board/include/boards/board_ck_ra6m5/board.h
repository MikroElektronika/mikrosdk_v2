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

#define BOARD_NAME "Cloud Kit Based on RA6M5 MCU Group"

#include "hal_target.h"
#include "shield.h"

// Mapping
#define ARDUINO_CONNECTOR_A0        GPIO_P000
#define ARDUINO_CONNECTOR_A1        GPIO_P001
#define ARDUINO_CONNECTOR_A2        GPIO_P002
#define ARDUINO_CONNECTOR_A3        GPIO_P003
#define ARDUINO_CONNECTOR_A4        GPIO_P014
#define ARDUINO_CONNECTOR_A5        GPIO_P015
#define ARDUINO_CONNECTOR_D0        GPIO_P706
#define ARDUINO_CONNECTOR_D1        GPIO_P707
#define ARDUINO_CONNECTOR_D2        GPIO_P006
#define ARDUINO_CONNECTOR_D3        GPIO_P111
#define ARDUINO_CONNECTOR_D4        GPIO_P415
#define ARDUINO_CONNECTOR_D5        GPIO_P105
#define ARDUINO_CONNECTOR_D6        GPIO_P104
#define ARDUINO_CONNECTOR_D7        GPIO_P115
#define ARDUINO_CONNECTOR_D8        GPIO_P611
#define ARDUINO_CONNECTOR_D9        GPIO_P608
#define ARDUINO_CONNECTOR_D10       GPIO_P503
#define ARDUINO_CONNECTOR_D11       GPIO_P506
#define ARDUINO_CONNECTOR_D12       GPIO_P505
#define ARDUINO_CONNECTOR_D13       GPIO_P504
#define ARDUINO_CONNECTOR_SCL       GPIO_P512
#define ARDUINO_CONNECTOR_SDA       GPIO_P511

#define HEADER_CONNECTOR_D0         GPIO_P706
#define HEADER_CONNECTOR_D1         GPIO_P707
#define HEADER_CONNECTOR_D2         GPIO_P006
#define HEADER_CONNECTOR_D3         GPIO_P111
#define HEADER_CONNECTOR_D4         GPIO_P415
#define HEADER_CONNECTOR_D5         GPIO_P105
#define HEADER_CONNECTOR_D6         GPIO_P104
#define HEADER_CONNECTOR_D7         GPIO_P115
#define HEADER_CONNECTOR_D8         GPIO_P611
#define HEADER_CONNECTOR_D9         GPIO_P608
#define HEADER_CONNECTOR_D10        GPIO_P503
#define HEADER_CONNECTOR_D11        GPIO_P506
#define HEADER_CONNECTOR_D12        GPIO_P505
#define HEADER_CONNECTOR_D13        GPIO_P504
#define HEADER_CONNECTOR_D14        GPIO_P000
#define HEADER_CONNECTOR_D15        GPIO_P001
#define HEADER_CONNECTOR_D16        GPIO_P002
#define HEADER_CONNECTOR_D17        GPIO_P003
#define HEADER_CONNECTOR_D18        GPIO_P015   // This pin doesn't have SCL functionality, but routed to SCL pin on click shield mikrobus.
#define HEADER_CONNECTOR_D19        GPIO_P014   // This pin doesn't have SDA functionality, but routed to SDA pin on click shield mikrobus.

#define HEADER_CONNECTOR_PMOD1_D1      GPIO_P205
#define HEADER_CONNECTOR_PMOD1_D2      GPIO_P203
#define HEADER_CONNECTOR_PMOD1_D3      GPIO_P202
#define HEADER_CONNECTOR_PMOD1_D4      GPIO_P204
#define HEADER_CONNECTOR_PMOD1_D5      // Pin not routed.
#define HEADER_CONNECTOR_PMOD1_D6      // Pin not routed.
#define HEADER_CONNECTOR_PMOD1_D7      GPIO_P005
#define HEADER_CONNECTOR_PMOD1_D8      GPIO_P311
#define HEADER_CONNECTOR_PMOD1_D9      GPIO_P206
#define HEADER_CONNECTOR_PMOD1_D10     GPIO_P207
#define HEADER_CONNECTOR_PMOD1_D11     // Pin not routed.
#define HEADER_CONNECTOR_PMOD1_D12     // Pin not routed.

#define HEADER_CONNECTOR_PMOD2_D1      GPIO_P413
#define HEADER_CONNECTOR_PMOD2_D2      GPIO_P411
#define HEADER_CONNECTOR_PMOD2_D3      GPIO_P100
#define HEADER_CONNECTOR_PMOD2_D4      GPIO_P412
#define HEADER_CONNECTOR_PMOD2_D5      // Pin not routed.
#define HEADER_CONNECTOR_PMOD2_D6      // Pin not routed.
#define HEADER_CONNECTOR_PMOD2_D7      GPIO_P004
#define HEADER_CONNECTOR_PMOD2_D8      GPIO_P101
#define HEADER_CONNECTOR_PMOD2_D9      GPIO_P414
#define HEADER_CONNECTOR_PMOD2_D10     GPIO_P708
#define HEADER_CONNECTOR_PMOD2_D11     // Pin not routed.
#define HEADER_CONNECTOR_PMOD2_D12     // Pin not routed.

#define BUTTON1    GPIO_P804

#define LED1       GPIO_P601
#define LED2       GPIO_P609
#define LED3       GPIO_P610

#ifdef __cplusplus
}
#endif

#endif    // _BOARD_H_
// ------------------------------------------------------------------------- END
