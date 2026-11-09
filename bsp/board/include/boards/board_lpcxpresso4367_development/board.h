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

#define BOARD_NAME "LPCXpresso4367 Development Board"

#include "hal_target.h"
#include "shield.h"

// Mapping
#define ARDUINO_CONNECTOR_A0        // Pin not routed (dedicated ADC_0 analog-only pin, no GPIO)
#define ARDUINO_CONNECTOR_A1        // Pin not routed (dedicated ADC_1 analog-only pin, no GPIO)
#define ARDUINO_CONNECTOR_A2        // Pin not routed (dedicated ADC_2 analog-only pin, no GPIO)
#define ARDUINO_CONNECTOR_A3        // Pin not routed (dedicated ADC_3 analog-only pin, no GPIO)
#define ARDUINO_CONNECTOR_A4        // Pin not routed
#define ARDUINO_CONNECTOR_A5        GPIO_P2_5
#define ARDUINO_CONNECTOR_D0        GPIO_P2_11
#define ARDUINO_CONNECTOR_D1        GPIO_P2_10
#define ARDUINO_CONNECTOR_D2        GPIO_P2_13
#define ARDUINO_CONNECTOR_D3        GPIO_P1_8
#define ARDUINO_CONNECTOR_D4        GPIO_P2_2
#define ARDUINO_CONNECTOR_D5        GPIO_P1_7
#define ARDUINO_CONNECTOR_D6        GPIO_P2_9   // BOOT3 boot-mode pin
#define ARDUINO_CONNECTOR_D7        GPIO_P2_12
#define ARDUINO_CONNECTOR_D8        GPIO_P2_6
#define ARDUINO_CONNECTOR_D9        GPIO_P6_5
#define ARDUINO_CONNECTOR_D10       GPIO_P1_5   // via U8 SSEL mux, default SEL=1 to Arduino D10
#define ARDUINO_CONNECTOR_D11       GPIO_P1_4
#define ARDUINO_CONNECTOR_D12       GPIO_P1_3
#define ARDUINO_CONNECTOR_D13       GPIO_PF_4
#define ARDUINO_CONNECTOR_SCL       GPIO_P2_4
#define ARDUINO_CONNECTOR_SDA       GPIO_P2_3

#define BUTTON2    GPIO_P2_7   // SW2 ISP, shared with RGB LED green

#define LED_R      GPIO_P6_11
#define LED_G      GPIO_P2_7   // shared with ISP button SW2
#define LED_B      GPIO_P6_9

#ifdef __cplusplus
}
#endif

#endif    // _BOARD_H_
// ------------------------------------------------------------------------- END
