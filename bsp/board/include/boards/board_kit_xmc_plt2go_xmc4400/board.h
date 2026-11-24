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
 *
 * @note For board-specific changes and version history, refer to the changelogs:
 *       https://github.com/MikroElektronika/mikrosdk_v2/blob/master/changelog/v2.20.4/new_hw/2027-03-17.md
 */

#ifndef _BOARD_H_
#define _BOARD_H_

#ifdef __cplusplus
extern "C"
{
#endif

#define BOARD_NAME "XMC4400 Platform2Go Kit"

#include "mikrobus.h"
#include "shield.h"

// Mapping
#define MIKROBUS_1      1
#define MIKROBUS_1_AN   GPIO_P1414
#define MIKROBUS_1_RST  GPIO_P502
#define MIKROBUS_1_CS   GPIO_P012
#define MIKROBUS_1_SCK  GPIO_P108
#define MIKROBUS_1_MISO GPIO_P000
#define MIKROBUS_1_MOSI GPIO_P109
#define MIKROBUS_1_PWM  GPIO_P507
#define MIKROBUS_1_INT  GPIO_P001
#define MIKROBUS_1_RX   GPIO_P215
#define MIKROBUS_1_TX   GPIO_P214
#define MIKROBUS_1_SCL  GPIO_P300
#define MIKROBUS_1_SDA  GPIO_P205

#define ARDUINO_CONNECTOR_A0        GPIO_P1400
#define ARDUINO_CONNECTOR_A1        GPIO_P1401
#define ARDUINO_CONNECTOR_A2        GPIO_P1402
#define ARDUINO_CONNECTOR_A3        GPIO_P1403
#define ARDUINO_CONNECTOR_A4        GPIO_P1404
#define ARDUINO_CONNECTOR_A5        GPIO_P1405
#define ARDUINO_CONNECTOR_D0        GPIO_P215
#define ARDUINO_CONNECTOR_D1        GPIO_P214
#define ARDUINO_CONNECTOR_D2        GPIO_P100
#define ARDUINO_CONNECTOR_D3        GPIO_P306
#define ARDUINO_CONNECTOR_D4        GPIO_P106
#define ARDUINO_CONNECTOR_D5        GPIO_P303
#define ARDUINO_CONNECTOR_D6        GPIO_P304
#define ARDUINO_CONNECTOR_D7        GPIO_P114
#define ARDUINO_CONNECTOR_D8        GPIO_P401
#define ARDUINO_CONNECTOR_D9        GPIO_P011
#define ARDUINO_CONNECTOR_D10       GPIO_P002
#define ARDUINO_CONNECTOR_D11       GPIO_P109
#define ARDUINO_CONNECTOR_D12       GPIO_P000
#define ARDUINO_CONNECTOR_D13       GPIO_P108
#define ARDUINO_CONNECTOR_SCL       GPIO_P300
#define ARDUINO_CONNECTOR_SDA       GPIO_P205

#define BUTTON1    GPIO_P301
#define BUTTON2    GPIO_P302

#define LED1       GPIO_P006
#define LED2       GPIO_P007

#define USB_UART_TX GPIO_P115
#define USB_UART_RX GPIO_P005

#ifdef __cplusplus
}
#endif

#endif    // _BOARD_H_
// ------------------------------------------------------------------------- END
