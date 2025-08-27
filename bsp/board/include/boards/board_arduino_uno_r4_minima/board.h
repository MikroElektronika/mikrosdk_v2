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

#define BOARD_NAME "Arduino UNO R4 Minima"

#include "hal_target.h"

// Mapping
#define HEADER_CONNECTOR_D0 GPIO_P301
#define HEADER_CONNECTOR_D1 GPIO_P302
#define HEADER_CONNECTOR_D2 GPIO_P105
#define HEADER_CONNECTOR_D3 GPIO_P104
#define HEADER_CONNECTOR_D4 GPIO_P103
#define HEADER_CONNECTOR_D5 GPIO_P102
#define HEADER_CONNECTOR_D6 GPIO_P106
#define HEADER_CONNECTOR_D7 GPIO_P107
#define HEADER_CONNECTOR_D8 GPIO_P304
#define HEADER_CONNECTOR_D9 GPIO_P303
#define HEADER_CONNECTOR_D10 GPIO_P112
#define HEADER_CONNECTOR_D11 GPIO_P109
#define HEADER_CONNECTOR_D12 GPIO_P110
#define HEADER_CONNECTOR_D13 GPIO_P111
#define HEADER_CONNECTOR_D14 GPIO_P014
#define HEADER_CONNECTOR_D15 GPIO_P000
#define HEADER_CONNECTOR_D16 GPIO_P001
#define HEADER_CONNECTOR_D17 GPIO_P002
#define HEADER_CONNECTOR_D18 GPIO_P101
#define HEADER_CONNECTOR_D19 GPIO_P100

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

#define HEADER_CONNECTOR_DIGITAL_LED_BUILTIN GPIO_P111
#define HEADER_CONNECTOR_DIGITAL_LED_TX GPIO_P012
#define HEADER_CONNECTOR_DIGITAL_LED_RX GPIO_P013

#define USB_UART_TX HEADER_CONNECTOR_D1
#define USB_UART_RX HEADER_CONNECTOR_D0

#ifdef __cplusplus
}
#endif

#endif    // _BOARD_H_
// ------------------------------------------------------------------------- END
