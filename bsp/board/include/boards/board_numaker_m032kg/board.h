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

#define BOARD_NAME "NuMaker M032KG"

#include "hal_target.h"
#include "shield.h"

// Mapping
#define ARDUINO_CONNECTOR_A0        GPIO_PB7
#define ARDUINO_CONNECTOR_A1        GPIO_PB6
#define ARDUINO_CONNECTOR_A2        GPIO_PB5
#define ARDUINO_CONNECTOR_A3        GPIO_PB4
#define ARDUINO_CONNECTOR_A4        GPIO_PB0
#define ARDUINO_CONNECTOR_A5        GPIO_PB1
#define ARDUINO_CONNECTOR_D0        GPIO_PB2
#define ARDUINO_CONNECTOR_D1        GPIO_PB3
#define ARDUINO_CONNECTOR_D2        GPIO_PC4
#define ARDUINO_CONNECTOR_D3        GPIO_PC5
#define ARDUINO_CONNECTOR_D4        GPIO_PC3
#define ARDUINO_CONNECTOR_D5        GPIO_PC2
#define ARDUINO_CONNECTOR_D6        GPIO_PA7
#define ARDUINO_CONNECTOR_D7        GPIO_PA6
#define ARDUINO_CONNECTOR_D8        GPIO_PA5
#define ARDUINO_CONNECTOR_D9        GPIO_PA4
#define ARDUINO_CONNECTOR_D10       GPIO_PA3
#define ARDUINO_CONNECTOR_D11       GPIO_PA0
#define ARDUINO_CONNECTOR_D12       GPIO_PA1
#define ARDUINO_CONNECTOR_D13       GPIO_PA2
#define ARDUINO_CONNECTOR_SCL       GPIO_PC1
#define ARDUINO_CONNECTOR_SDA       GPIO_PC0

#define LED1       GPIO_PB14

#ifdef __cplusplus
}
#endif

#endif    // _BOARD_H_
// ------------------------------------------------------------------------- END
