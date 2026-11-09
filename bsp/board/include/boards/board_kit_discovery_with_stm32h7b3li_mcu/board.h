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

#define BOARD_NAME "Discovery kit with STM32H7B3LI MCU"

#include "hal_target.h"
#include "shield.h"

// Mapping
#define ARDUINO_CONNECTOR_A0        GPIO_PA4  // via SB45, shared with camera DCMI_HSYNC
#define ARDUINO_CONNECTOR_A1        GPIO_PC4
#define ARDUINO_CONNECTOR_A2        // PA0_C analog-only pad, no GPIO equivalent
#define ARDUINO_CONNECTOR_A3        // PA1_C analog-only pad, no GPIO equivalent
#define ARDUINO_CONNECTOR_A4        // PC2_C analog-only pad, no GPIO equivalent
#define ARDUINO_CONNECTOR_A5        // PC3_C analog-only pad, no GPIO equivalent
#define ARDUINO_CONNECTOR_D0        GPIO_PH14
#define ARDUINO_CONNECTOR_D1        GPIO_PH13
#define ARDUINO_CONNECTOR_D2        GPIO_PI9
#define ARDUINO_CONNECTOR_D3        GPIO_PH9
#define ARDUINO_CONNECTOR_D4        GPIO_PE2
#define ARDUINO_CONNECTOR_D5        GPIO_PH11
#define ARDUINO_CONNECTOR_D6        GPIO_PH10
#define ARDUINO_CONNECTOR_D7        GPIO_PI10
#define ARDUINO_CONNECTOR_D8        GPIO_PF10
#define ARDUINO_CONNECTOR_D9        GPIO_PI7
#define ARDUINO_CONNECTOR_D10       GPIO_PI0
#define ARDUINO_CONNECTOR_D11       GPIO_PB15
#define ARDUINO_CONNECTOR_D12       GPIO_PB14
#define ARDUINO_CONNECTOR_D13       GPIO_PA12  // shared with LD1 LED
#define ARDUINO_CONNECTOR_SCL       GPIO_PD12
#define ARDUINO_CONNECTOR_SDA       GPIO_PD13

#define BUTTON2    GPIO_PC13

#define LED2       GPIO_PG2
#define LED3       GPIO_PG11

#ifdef __cplusplus
}
#endif

#endif    // _BOARD_H_
// ------------------------------------------------------------------------- END
