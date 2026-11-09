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

#define BOARD_NAME "Discovery kit with STM32H747XI MCU"

#include "hal_target.h"
#include "shield.h"

// Mapping
#define ARDUINO_CONNECTOR_A0        GPIO_PA4
#define ARDUINO_CONNECTOR_A1        GPIO_PF10
#define ARDUINO_CONNECTOR_A2        // PA0_C analog-only pad, no GPIO equivalent
#define ARDUINO_CONNECTOR_A3        // PA1_C analog-only pad, no GPIO equivalent
#define ARDUINO_CONNECTOR_A4        // PC2_C analog-only pad, no GPIO equivalent
#define ARDUINO_CONNECTOR_A5        // PC3_C analog-only pad, no GPIO equivalent
#define ARDUINO_CONNECTOR_D0        GPIO_PJ9
#define ARDUINO_CONNECTOR_D1        GPIO_PJ8
#define ARDUINO_CONNECTOR_D2        GPIO_PJ3
#define ARDUINO_CONNECTOR_D3        GPIO_PF8
#define ARDUINO_CONNECTOR_D4        GPIO_PJ4
#define ARDUINO_CONNECTOR_D5        GPIO_PA6
#define ARDUINO_CONNECTOR_D6        GPIO_PJ7
#define ARDUINO_CONNECTOR_D7        GPIO_PJ0
#define ARDUINO_CONNECTOR_D8        GPIO_PJ5
#define ARDUINO_CONNECTOR_D9        GPIO_PJ6
#define ARDUINO_CONNECTOR_D10       GPIO_PK1
#define ARDUINO_CONNECTOR_D11       GPIO_PJ10
#define ARDUINO_CONNECTOR_D12       GPIO_PJ11
#define ARDUINO_CONNECTOR_D13       GPIO_PK0
#define ARDUINO_CONNECTOR_SCL       GPIO_PD12
#define ARDUINO_CONNECTOR_SDA       GPIO_PD13

#define BUTTON2    GPIO_PC13

#define LED1       GPIO_PI12
#define LED2       GPIO_PI13
#define LED3       GPIO_PI14
#define LED4       GPIO_PI15

#ifdef __cplusplus
}
#endif

#endif    // _BOARD_H_
// ------------------------------------------------------------------------- END
