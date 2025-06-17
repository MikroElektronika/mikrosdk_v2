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
 *
 * @note For board-specific changes and version history, refer to the changelogs:
 *       https://github.com/MikroElektronika/mikrosdk_v2/blob/master/changelog/{markdown_path}
 */

#ifndef _BOARD_H_
#define _BOARD_H_

#ifdef __cplusplus
extern "C"
{
#endif

#define BOARD_NAME "Curiosity PIC32MZ EF 2.0 Development Board"

#include "mikrobus.h"

// Mapping
#define MIKROBUS_1      1
#define MIKROBUS_1_AN   PB10
#define MIKROBUS_1_RST  PJ12
#define MIKROBUS_1_CS   PD9
#define MIKROBUS_1_SCK  PD1
#define MIKROBUS_1_MISO PD14
#define MIKROBUS_1_MOSI PD7
#define MIKROBUS_1_PWM  PD15
#define MIKROBUS_1_INT  PF12
#define MIKROBUS_1_RX   PC4
#define MIKROBUS_1_TX   PC1
#define MIKROBUS_1_SCL  PA2
#define MIKROBUS_1_SDA  PA3

#define MIKROBUS_2      2
#define MIKROBUS_2_AN   PB11
#define MIKROBUS_2_RST  PJ10
#define MIKROBUS_2_CS   PC2
#define MIKROBUS_2_SCK  PG6
#define MIKROBUS_2_MISO PG7
#define MIKROBUS_2_MOSI PG8
#define MIKROBUS_2_PWM  PD15
#define MIKROBUS_2_INT  PD10
#define MIKROBUS_2_RX   PE9
#define MIKROBUS_2_TX   PG9
#define MIKROBUS_2_SCL  PA2
#define MIKROBUS_2_SDA  PA3

// LEDs
#define LED_1       PJ7
#define LED_2       PK7
#define LED_3       PJ3
#define LED_4_RED   PB0
#define LED_4_GREEN PB1
#define LED_4_BLUE  PB5

// Buttons
#define BUTTON_1 PJ4
#define BUTTON_2 PJ5
#define BUTTON_3 PJ6
#define BUTTON_4 PC15

// CAN
#define CAN_RX PF5
#define CAN_TX PD5

// Ethernet
#define ETH_RXD0   PH8
#define ETH_RXD1   PH5
#define ETH_TXD0   PJ8
#define ETH_TXD1   PJ9
#define ETH_TXEN   PD6
#define ETH_CRS_DV PH13
#define ETH_RXER   PH4
#define ETH_MDIO   PJ11
#define ETH_MDC    PD11
#define ETH_NINT   PJ2
#define ETH_CLK    PB14
#define ETH_RST    PJ0

// UART
#define USB_UART_TX PF4
#define USB_UART_RX PD15

#ifdef __cplusplus
}
#endif

#endif    // _BOARD_H_
// ------------------------------------------------------------------------- END
