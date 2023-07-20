/****************************************************************************
**
** Copyright (C) 2023 MikroElektronika d.o.o.
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
** OF MERCHANTABILITY, EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED
** TO THE WARRANTIES FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT.
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
#define HEADER_CONNECTOR_D0 PD0
#define HEADER_CONNECTOR_D1 PD1
#define HEADER_CONNECTOR_D2 PD2
#define HEADER_CONNECTOR_D3 PD3
#define HEADER_CONNECTOR_D4 PD4
#define HEADER_CONNECTOR_D5 PD5
#define HEADER_CONNECTOR_D6 PD6
#define HEADER_CONNECTOR_D7 PD7
#define HEADER_CONNECTOR_D8 PB0
#define HEADER_CONNECTOR_D9 PB1
#define HEADER_CONNECTOR_D10 PB2
#define HEADER_CONNECTOR_D11 PB3
#define HEADER_CONNECTOR_D12 PB4
#define HEADER_CONNECTOR_D13 PB5
#define HEADER_CONNECTOR_D14 PC0
#define HEADER_CONNECTOR_D15 PC1
#define HEADER_CONNECTOR_D16 PC2
#define HEADER_CONNECTOR_D17 PC3
#define HEADER_CONNECTOR_D18 PC4
#define HEADER_CONNECTOR_D19 PC5

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

#define HEADER_CONNECTOR_DIGITAL_LED_BUILTIN PB5
#define HEADER_CONNECTOR_DIGITAL_LED_TX PD5
#define HEADER_CONNECTOR_DIGITAL_LED_RX PD4

#define USB_UART_TX SHIELD_SW1_TX
#define USB_UART_RX SHIELD_SW1_RX

#ifdef __cplusplus
}
#endif

#endif // _BOARD_H_
// ------------------------------------------------------------------------- END
