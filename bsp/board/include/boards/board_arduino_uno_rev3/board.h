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
extern "C"{
#endif

// Hardware revision number
#define BOARD_REV_MAJOR (3)
#define BOARD_REV_MINOR (0)

#define BOARD_NAME "Arduino Uno Rev3"

#include "hal_target.h"
#include "shield.h"

/// Mapping
#define HEADER_CONNECTOR_D0 GPIO_PD0
#define HEADER_CONNECTOR_D1 GPIO_PD1
#define HEADER_CONNECTOR_D2 GPIO_PD2
#define HEADER_CONNECTOR_D3 GPIO_PD3
#define HEADER_CONNECTOR_D4 GPIO_PD4
#define HEADER_CONNECTOR_D5 GPIO_PD5
#define HEADER_CONNECTOR_D6 GPIO_PD6
#define HEADER_CONNECTOR_D7 GPIO_PD7
#define HEADER_CONNECTOR_D8 GPIO_PB0
#define HEADER_CONNECTOR_D9 GPIO_PB1
#define HEADER_CONNECTOR_D10 GPIO_PB2
#define HEADER_CONNECTOR_D11 GPIO_PB3
#define HEADER_CONNECTOR_D12 GPIO_PB4
#define HEADER_CONNECTOR_D13 GPIO_PB5
#define HEADER_CONNECTOR_D14 GPIO_PC0
#define HEADER_CONNECTOR_D15 GPIO_PC1
#define HEADER_CONNECTOR_D16 GPIO_PC2
#define HEADER_CONNECTOR_D17 GPIO_PC3
#define HEADER_CONNECTOR_D18 GPIO_PC4
#define HEADER_CONNECTOR_D19 GPIO_PC5

#define HEADER_CONNECTOR_ANALOG_IN_A0 HEADER_CONNECTOR_D14
#define HEADER_CONNECTOR_ANALOG_IN_A1 HEADER_CONNECTOR_D15
#define HEADER_CONNECTOR_ANALOG_IN_A2 HEADER_CONNECTOR_D16
#define HEADER_CONNECTOR_ANALOG_IN_A3 HEADER_CONNECTOR_D17
#define HEADER_CONNECTOR_ANALOG_IN_A4 HEADER_CONNECTOR_D18
#define HEADER_CONNECTOR_ANALOG_IN_A5 HEADER_CONNECTOR_D19

#define HEADER_CONNECTOR_DIGITAL_SCL HEADER_CONNECTOR_D19
#define HEADER_CONNECTOR_DIGITAL_SDA HEADER_CONNECTOR_D18
#define HEADER_CONNECTOR_DIGITAL_SCK HEADER_CONNECTOR_D13
#define HEADER_CONNECTOR_DIGITAL_CIPO HEADER_CONNECTOR_D12
#define HEADER_CONNECTOR_DIGITAL_COPI HEADER_CONNECTOR_D11
#define HEADER_CONNECTOR_DIGITAL_SS HEADER_CONNECTOR_D10

#define HEADER_CONNECTOR_DIGITAL_LED_BUILTIN GPIO_PB5
#define HEADER_CONNECTOR_DIGITAL_LED_TX GPIO_PD5
#define HEADER_CONNECTOR_DIGITAL_LED_RX GPIO_PD4

#define USB_UART_TX SHIELD_SW1_TX
#define USB_UART_RX SHIELD_SW1_RX

#ifdef __cplusplus
}
#endif

#endif // _BOARD_H_
// ------------------------------------------------------------------------- END
