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

#define BOARD_NAME "LPCXpresso Board for LPC11U68"

#include "hal_target.h"
#include "shield.h"

// Mapping
#define ARDUINO_CONNECTOR_A0        GPIO_P1_9
#define ARDUINO_CONNECTOR_A1        GPIO_P0_14
#define ARDUINO_CONNECTOR_A2        GPIO_P0_13
#define ARDUINO_CONNECTOR_A3        GPIO_P0_12
#define ARDUINO_CONNECTOR_A4        GPIO_P0_23
#define ARDUINO_CONNECTOR_A5        GPIO_P0_11
#define ARDUINO_CONNECTOR_D0        GPIO_P2_11
#define ARDUINO_CONNECTOR_D1        GPIO_P2_12
#define ARDUINO_CONNECTOR_D2        GPIO_P1_18
#define ARDUINO_CONNECTOR_D3        GPIO_P1_24
#define ARDUINO_CONNECTOR_D4        GPIO_P1_19
#define ARDUINO_CONNECTOR_D5        GPIO_P1_26
#define ARDUINO_CONNECTOR_D6        GPIO_P1_27
#define ARDUINO_CONNECTOR_D7        GPIO_P1_25
#define ARDUINO_CONNECTOR_D8        GPIO_P1_28
#define ARDUINO_CONNECTOR_D9        GPIO_P2_3
#define ARDUINO_CONNECTOR_D10       GPIO_P0_2
#define ARDUINO_CONNECTOR_D11       GPIO_P0_9
#define ARDUINO_CONNECTOR_D12       GPIO_P0_8
#define ARDUINO_CONNECTOR_D13       GPIO_P1_29
#define ARDUINO_CONNECTOR_SCL       GPIO_P0_4
#define ARDUINO_CONNECTOR_SDA       GPIO_P0_5

#define BUTTON2    GPIO_P0_16   // SW2 WAKEUP

#define LED_R      GPIO_P2_17
#define LED_G      GPIO_P2_16
#define LED_B      GPIO_P2_18

#ifdef __cplusplus
}
#endif

#endif    // _BOARD_H_
// ------------------------------------------------------------------------- END
