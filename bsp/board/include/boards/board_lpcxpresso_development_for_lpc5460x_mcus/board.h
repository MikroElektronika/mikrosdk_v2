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

#define BOARD_NAME "LPCXpresso Development Board for LPC5460x MCUs"

#include "hal_target.h"
#include "shield.h"

// Mapping
#define ARDUINO_CONNECTOR_A0        GPIO_P0_16
#define ARDUINO_CONNECTOR_A1        GPIO_P0_31
#define ARDUINO_CONNECTOR_A2        GPIO_P1_0
#define ARDUINO_CONNECTOR_A3        GPIO_P2_0   // shared with Pmod2 INTR
#define ARDUINO_CONNECTOR_A4        GPIO_P3_4   // shared with accelerometer INTR
#define ARDUINO_CONNECTOR_A5        GPIO_P1_1   // shared with USER button SW5
#define ARDUINO_CONNECTOR_D0        GPIO_P3_26
#define ARDUINO_CONNECTOR_D1        GPIO_P3_27
#define ARDUINO_CONNECTOR_D2        GPIO_P3_2
#define ARDUINO_CONNECTOR_D3        GPIO_P4_5
#define ARDUINO_CONNECTOR_D4        GPIO_P3_10
#define ARDUINO_CONNECTOR_D5        GPIO_P3_14   // shared with user LED D12
#define ARDUINO_CONNECTOR_D6        GPIO_P3_1
#define ARDUINO_CONNECTOR_D7        GPIO_P1_22
#define ARDUINO_CONNECTOR_D8        GPIO_P4_7
#define ARDUINO_CONNECTOR_D9        GPIO_P2_1
#define ARDUINO_CONNECTOR_D10       GPIO_P3_30
#define ARDUINO_CONNECTOR_D11       GPIO_P3_21
#define ARDUINO_CONNECTOR_D12       GPIO_P3_22
#define ARDUINO_CONNECTOR_D13       GPIO_P3_20
#define ARDUINO_CONNECTOR_SCL       GPIO_P3_24
#define ARDUINO_CONNECTOR_SDA       GPIO_P3_23

#define BUTTON2    GPIO_P0_6   // SW2 ISP2
#define BUTTON3    GPIO_P0_5   // SW3 ISP1
#define BUTTON4    GPIO_P0_4   // SW4 ISP0
#define BUTTON5    GPIO_P1_1   // SW5 USER, shared with Arduino A5

#define LED9       GPIO_P2_2
#define LED11      GPIO_P3_3
#define LED12      GPIO_P3_14   // shared with Arduino D5

#ifdef __cplusplus
}
#endif

#endif    // _BOARD_H_
// ------------------------------------------------------------------------- END
