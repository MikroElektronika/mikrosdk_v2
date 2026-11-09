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

#define BOARD_NAME "RL78 G23 64p Fast Prototyping Board"

#include "hal_target.h"
#include "shield.h"

// Mapping
#define ARDUINO_CONNECTOR_A0        GPIO_P22
#define ARDUINO_CONNECTOR_A1        GPIO_P23
#define ARDUINO_CONNECTOR_A2        GPIO_P24
#define ARDUINO_CONNECTOR_A3        GPIO_P25
#define ARDUINO_CONNECTOR_A4        GPIO_P26
#define ARDUINO_CONNECTOR_A5        GPIO_P27
#define ARDUINO_CONNECTOR_D0        GPIO_P03
#define ARDUINO_CONNECTOR_D1        GPIO_P02
#define ARDUINO_CONNECTOR_D2        GPIO_P43
#define ARDUINO_CONNECTOR_D3        GPIO_P42
#define ARDUINO_CONNECTOR_D4        GPIO_P77
#define ARDUINO_CONNECTOR_D5        GPIO_P41
#define ARDUINO_CONNECTOR_D6        GPIO_P31
#define ARDUINO_CONNECTOR_D7        GPIO_P76
#define ARDUINO_CONNECTOR_D8        GPIO_P73
#define ARDUINO_CONNECTOR_D9        GPIO_P06
#define ARDUINO_CONNECTOR_D10       GPIO_P05
#define ARDUINO_CONNECTOR_D11       GPIO_P51
#define ARDUINO_CONNECTOR_D12       GPIO_P50
#define ARDUINO_CONNECTOR_D13       GPIO_P30
#define ARDUINO_CONNECTOR_SCL       GPIO_P60
#define ARDUINO_CONNECTOR_SDA       GPIO_P61

#define BUTTON1    GPIO_P137

#define LED1       GPIO_P53
#define LED2       GPIO_P52

#ifdef __cplusplus
}
#endif

#endif    // _BOARD_H_
// ------------------------------------------------------------------------- END
