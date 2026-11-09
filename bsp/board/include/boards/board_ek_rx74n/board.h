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

#define BOARD_NAME "Evaluation Kit for RX74N MCU Group"

#include "mikrobus.h"

// Mapping
#define MIKROBUS_1      1
#define MIKROBUS_1_AN   GPIO_P406
#define MIKROBUS_1_RST  GPIO_P412
#define MIKROBUS_1_CS   GPIO_P211
#define MIKROBUS_1_SCK  GPIO_P208
#define MIKROBUS_1_MISO GPIO_P210
#define MIKROBUS_1_MOSI GPIO_P209
#define MIKROBUS_1_PWM  GPIO_P002
#define MIKROBUS_1_INT  GPIO_P501
#define MIKROBUS_1_RX   GPIO_P005
#define MIKROBUS_1_TX   GPIO_P004
#define MIKROBUS_1_SCL  GPIO_PG01
#define MIKROBUS_1_SDA  GPIO_PG02

#define ARDUINO_CONNECTOR_A0        GPIO_P400
#define ARDUINO_CONNECTOR_A1        GPIO_P401
#define ARDUINO_CONNECTOR_A2        GPIO_P402
#define ARDUINO_CONNECTOR_A3        GPIO_P403
#define ARDUINO_CONNECTOR_A4        GPIO_P404
#define ARDUINO_CONNECTOR_A5        GPIO_P405
#define ARDUINO_CONNECTOR_D0        GPIO_P800
#define ARDUINO_CONNECTOR_D1        GPIO_P801
#define ARDUINO_CONNECTOR_D2        GPIO_PF03
#define ARDUINO_CONNECTOR_D3        GPIO_P802
#define ARDUINO_CONNECTOR_D4        GPIO_P108
#define ARDUINO_CONNECTOR_D5        GPIO_P500
#define ARDUINO_CONNECTOR_D6        GPIO_P106
#define ARDUINO_CONNECTOR_D7        GPIO_P407
#define ARDUINO_CONNECTOR_D8        GPIO_P110
#define ARDUINO_CONNECTOR_D9        GPIO_PF04
#define ARDUINO_CONNECTOR_D10       GPIO_PA04
#define ARDUINO_CONNECTOR_D11       GPIO_PA06
#define ARDUINO_CONNECTOR_D12       GPIO_PA07
#define ARDUINO_CONNECTOR_D13       GPIO_PA05
#define ARDUINO_CONNECTOR_SCL       GPIO_P706
#define ARDUINO_CONNECTOR_SDA       GPIO_P707

#define BUTTON1    GPIO_P414
#define BUTTON2    GPIO_P109

#define LED1       GPIO_PF05
#define LED2       GPIO_P807
#define LED3       GPIO_P604

#ifdef __cplusplus
}
#endif

#endif    // _BOARD_H_
// ------------------------------------------------------------------------- END
