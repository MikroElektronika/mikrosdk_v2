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

#define BOARD_NAME "LPCXpresso802 for the LPC802 family of MCUs"

#include "hal_target.h"
#include "shield.h"

// Mapping
#define ARDUINO_CONNECTOR_A0        GPIO_P0_15   // shared with potentiometer
#define ARDUINO_CONNECTOR_A1        // Pin not routed
#define ARDUINO_CONNECTOR_A2        // Pin not routed
#define ARDUINO_CONNECTOR_A3        // Pin not routed
#define ARDUINO_CONNECTOR_A4        // Pin not routed
#define ARDUINO_CONNECTOR_A5        // Pin not routed
#define ARDUINO_CONNECTOR_D0        GPIO_P0_4   // shared with debug UART
#define ARDUINO_CONNECTOR_D1        GPIO_P0_0   // shared with debug UART
#define ARDUINO_CONNECTOR_D2        // Pin not routed
#define ARDUINO_CONNECTOR_D3        // Pin not routed
#define ARDUINO_CONNECTOR_D4        GPIO_P0_9   // shared with user LED2
#define ARDUINO_CONNECTOR_D5        GPIO_P0_7
#define ARDUINO_CONNECTOR_D6        GPIO_P0_12   // shared with user LED3 / ISP button
#define ARDUINO_CONNECTOR_D7        GPIO_P0_8   // shared with user LED1 / WAKE button
#define ARDUINO_CONNECTOR_D8        GPIO_P0_12   // shared with user LED3 / ISP button
#define ARDUINO_CONNECTOR_D9        GPIO_P0_17
#define ARDUINO_CONNECTOR_D10       GPIO_P0_11   // shared with SPI flash
#define ARDUINO_CONNECTOR_D11       GPIO_P0_13   // shared with SPI flash
#define ARDUINO_CONNECTOR_D12       GPIO_P0_1   // shared with SPI flash
#define ARDUINO_CONNECTOR_D13       GPIO_P0_14   // shared with SPI flash
#define ARDUINO_CONNECTOR_SCL       GPIO_P0_16   // shared with LM75 temperature sensor
#define ARDUINO_CONNECTOR_SDA       GPIO_P0_10   // shared with LM75 temperature sensor

#define BUTTON1    GPIO_P0_12   // PB1 ISP, shared with user LED3
#define BUTTON3    GPIO_P0_8   // PB3 WAKE, shared with user LED1

#define LED1       GPIO_P0_8
#define LED2       GPIO_P0_9
#define LED3       GPIO_P0_12

#ifdef __cplusplus
}
#endif

#endif    // _BOARD_H_
// ------------------------------------------------------------------------- END
