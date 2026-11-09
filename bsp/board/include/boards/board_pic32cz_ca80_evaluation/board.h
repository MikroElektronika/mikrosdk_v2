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

#define BOARD_NAME "PIC32CZ CA80 Evaluation Board"

#include "mikrobus.h"

// Mapping
#define MIKROBUS_1      1
#define MIKROBUS_1_AN   GPIO_PA14
#define MIKROBUS_1_RST  GPIO_PB27
#define MIKROBUS_1_CS   GPIO_PC14
#define MIKROBUS_1_SCK  GPIO_PC13
#define MIKROBUS_1_MISO GPIO_PC15
#define MIKROBUS_1_MOSI GPIO_PC12
#define MIKROBUS_1_PWM  GPIO_PA22
#define MIKROBUS_1_INT  GPIO_PA8
#define MIKROBUS_1_RX   GPIO_PC22
#define MIKROBUS_1_TX   GPIO_PC21
#define MIKROBUS_1_SCL  GPIO_PC26
#define MIKROBUS_1_SDA  GPIO_PC25

#define ARDUINO_CONNECTOR_A0        GPIO_PA18
#define ARDUINO_CONNECTOR_A1        GPIO_PA17
#define ARDUINO_CONNECTOR_A2        GPIO_PA16
#define ARDUINO_CONNECTOR_A3        GPIO_PA15
#define ARDUINO_CONNECTOR_A4        GPIO_PA29
#define ARDUINO_CONNECTOR_A5        GPIO_PA28
#define ARDUINO_CONNECTOR_D0        GPIO_PC22
#define ARDUINO_CONNECTOR_D1        GPIO_PC21
#define ARDUINO_CONNECTOR_D2        GPIO_PG6
#define ARDUINO_CONNECTOR_D3        GPIO_PG5
#define ARDUINO_CONNECTOR_D4        GPIO_PG7
#define ARDUINO_CONNECTOR_D5        GPIO_PA23
#define ARDUINO_CONNECTOR_D6        GPIO_PA22
#define ARDUINO_CONNECTOR_D7        GPIO_PG9
#define ARDUINO_CONNECTOR_D8        GPIO_PG10
#define ARDUINO_CONNECTOR_D9        GPIO_PB11
#define ARDUINO_CONNECTOR_D10       GPIO_PD26
#define ARDUINO_CONNECTOR_D11       GPIO_PD24
#define ARDUINO_CONNECTOR_D12       GPIO_PD27
#define ARDUINO_CONNECTOR_D13       GPIO_PD25
#define ARDUINO_CONNECTOR_SCL       GPIO_PC26
#define ARDUINO_CONNECTOR_SDA       GPIO_PC25

#define BUTTON0    GPIO_PB24
#define BUTTON1    GPIO_PC23

#define LED0       GPIO_PB21
#define LED1       GPIO_PB22

#ifdef __cplusplus
}
#endif

#endif    // _BOARD_H_
// ------------------------------------------------------------------------- END
