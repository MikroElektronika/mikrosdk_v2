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

#define BOARD_NAME "LPCXpresso Development Board for LPC55S0x family of MCUs"

#include "mikrobus.h"

// Mapping
#define MIKROBUS_1      1
#define MIKROBUS_1_AN   GPIO_P0_16   // shared with Arduino A0
#define MIKROBUS_1_RST  // Pin not routed (connected to board RESET net, not a GPIO)
#define MIKROBUS_1_CS   GPIO_P1_1   // shared with Arduino D10
#define MIKROBUS_1_SCK  // Pin not routed (JP26 default selects CAN TXD; set JP26 for HS SPI SCK (P1_2))
#define MIKROBUS_1_MISO // Pin not routed (JP25 default selects CAN RXD; set JP25 for HS SPI MISO (P1_3))
#define MIKROBUS_1_MOSI GPIO_P0_26   // shared with Arduino D11
#define MIKROBUS_1_PWM  GPIO_P1_5
#define MIKROBUS_1_INT  GPIO_P0_28   // shared with WAKEUP button SW1
#define MIKROBUS_1_RX   GPIO_P1_10   // shared with Arduino D0
#define MIKROBUS_1_TX   GPIO_P1_11   // shared with Arduino D1
#define MIKROBUS_1_SCL  GPIO_P0_25   // via R80, shared with accelerometer I2C
#define MIKROBUS_1_SDA  GPIO_P0_24   // via R88, shared with accelerometer I2C / Arduino D9

#define ARDUINO_CONNECTOR_A0        GPIO_P0_16   // shared with mikroBUS AN
#define ARDUINO_CONNECTOR_A1        GPIO_P0_23   // same pin as Arduino D3
#define ARDUINO_CONNECTOR_A2        GPIO_P0_9
#define ARDUINO_CONNECTOR_A3        GPIO_P0_0
#define ARDUINO_CONNECTOR_A4        GPIO_P0_13
#define ARDUINO_CONNECTOR_A5        GPIO_P0_14
#define ARDUINO_CONNECTOR_D0        GPIO_P1_10   // shared with mikroBUS RX
#define ARDUINO_CONNECTOR_D1        GPIO_P1_11   // shared with mikroBUS TX
#define ARDUINO_CONNECTOR_D2        GPIO_P0_15
#define ARDUINO_CONNECTOR_D3        GPIO_P0_23   // same pin as Arduino A1
#define ARDUINO_CONNECTOR_D4        GPIO_P0_22   // shared with RGB LED blue
#define ARDUINO_CONNECTOR_D5        GPIO_P0_19
#define ARDUINO_CONNECTOR_D6        GPIO_P0_18   // shared with RGB LED green
#define ARDUINO_CONNECTOR_D7        GPIO_P0_2
#define ARDUINO_CONNECTOR_D8        GPIO_P0_10   // shared with debug SWO
#define ARDUINO_CONNECTOR_D9        GPIO_P0_24   // shared with mikroBUS SDA / accelerometer I2C
#define ARDUINO_CONNECTOR_D10       GPIO_P1_1   // shared with mikroBUS CS
#define ARDUINO_CONNECTOR_D11       GPIO_P0_26   // shared with mikroBUS MOSI
#define ARDUINO_CONNECTOR_D12       // Pin not routed (JP25 default selects CAN RXD; set JP25 for HS SPI MISO (P1_3))
#define ARDUINO_CONNECTOR_D13       // Pin not routed (JP26 default selects CAN TXD; set JP26 for HS SPI SCK (P1_2))
#define ARDUINO_CONNECTOR_SCL       GPIO_P0_21   // shared with RGB LED red
#define ARDUINO_CONNECTOR_SDA       GPIO_P0_20

#define BUTTON1    GPIO_P0_28   // SW1 WAKEUP, shared with mikroBUS INT
#define BUTTON3    GPIO_P1_9
#define BUTTON4    GPIO_P0_5   // SW4 ISP

#define LED_R      GPIO_P0_21   // shared with Arduino SCL
#define LED_G      GPIO_P0_18   // shared with Arduino D6
#define LED_B      GPIO_P0_22   // shared with Arduino D4

#ifdef __cplusplus
}
#endif

#endif    // _BOARD_H_
// ------------------------------------------------------------------------- END
