/****************************************************************************
**
** Copyright (C) 2024 MikroElektronika d.o.o.
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
 * @file  dip_socket.h
 * @brief Dip socket mikrobus pin mapping.
 */

#ifndef _DIP_SOCKET_H_
#define _DIP_SOCKET_H_

#ifdef __cplusplus
extern "C"{
#endif

#include "hal_target.h"

/// Mapping
#define MIKROBUS_1_DIP_AN   PA7
#define MIKROBUS_1_DIP_RST  PA4
#define MIKROBUS_1_DIP_CS       // Pin not routed to mikroBUS.
#define MIKROBUS_1_DIP_SCK      // Pin not routed to mikroBUS.
#define MIKROBUS_1_DIP_MISO     // Pin not routed to mikroBUS.
#define MIKROBUS_1_DIP_MOSI     // Pin not routed to mikroBUS.
#define MIKROBUS_1_DIP_PWM      // Pin not routed to mikroBUS.
#define MIKROBUS_1_DIP_INT      // Pin not routed to mikroBUS.
#define MIKROBUS_1_DIP_RX       // Pin not routed to mikroBUS.
#define MIKROBUS_1_DIP_TX       // Pin not routed to mikroBUS.
#define MIKROBUS_1_DIP_SCL      // Pin not routed to mikroBUS.
#define MIKROBUS_1_DIP_SDA      // Pin not routed to mikroBUS.

#define MIKROBUS_2_DIP_AN   PA3
#define MIKROBUS_2_DIP_RST  PA0
#define MIKROBUS_2_DIP_CS   PA1
#define MIKROBUS_2_DIP_SCK      // Pin not routed to mikroBUS.
#define MIKROBUS_2_DIP_MISO     // Pin not routed to mikroBUS.
#define MIKROBUS_2_DIP_MOSI     // Pin not routed to mikroBUS.
#define MIKROBUS_2_DIP_PWM      // Pin not routed to mikroBUS.
#define MIKROBUS_2_DIP_INT      // Pin not routed to mikroBUS.
#define MIKROBUS_2_DIP_RX       // Pin not routed to mikroBUS.
#define MIKROBUS_2_DIP_TX       // Pin not routed to mikroBUS.
#define MIKROBUS_2_DIP_SCL      // Pin not routed to mikroBUS.
#define MIKROBUS_2_DIP_SDA      // Pin not routed to mikroBUS.

#define MIKROBUS_3_DIP_AN       // Pin not routed to mikroBUS.
#define MIKROBUS_3_DIP_RST      // Pin not routed to mikroBUS.
#define MIKROBUS_3_DIP_CS   PB2
#define MIKROBUS_3_DIP_SCK      // Pin not routed to mikroBUS.
#define MIKROBUS_3_DIP_MISO PB3
#define MIKROBUS_3_DIP_MOSI     // Pin not routed to mikroBUS.
#define MIKROBUS_3_DIP_PWM      // Pin not routed to mikroBUS.
#define MIKROBUS_3_DIP_INT      // Pin not routed to mikroBUS.
#define MIKROBUS_3_DIP_RX       // Pin not routed to mikroBUS.
#define MIKROBUS_3_DIP_TX       // Pin not routed to mikroBUS.
#define MIKROBUS_3_DIP_SCL      // Pin not routed to mikroBUS.
#define MIKROBUS_3_DIP_SDA      // Pin not routed to mikroBUS.

#define MIKROBUS_4_DIP_AN   PA3
#define MIKROBUS_4_DIP_RST      // Pin not routed to mikroBUS.
#define MIKROBUS_4_DIP_CS   PA5
#define MIKROBUS_4_DIP_SCK  PB2
#define MIKROBUS_4_DIP_MISO PB1
#define MIKROBUS_4_DIP_MOSI PB0
#define MIKROBUS_4_DIP_PWM  PB3
#define MIKROBUS_4_DIP_INT      // Pin not routed to mikroBUS.
#define MIKROBUS_4_DIP_RX       // Pin not routed to mikroBUS.
#define MIKROBUS_4_DIP_TX       // Pin not routed to mikroBUS.
#define MIKROBUS_4_DIP_SCL  PA2
#define MIKROBUS_4_DIP_SDA  PA0

#define MIKROBUS_5_DIP_AN   PB1
#define MIKROBUS_5_DIP_RST      // Pin not routed to mikroBUS.
#define MIKROBUS_5_DIP_CS   PA3
#define MIKROBUS_5_DIP_SCK  PA4
#define MIKROBUS_5_DIP_MISO PA5
#define MIKROBUS_5_DIP_MOSI PA6
#define MIKROBUS_5_DIP_PWM      // Pin not routed to mikroBUS.
#define MIKROBUS_5_DIP_INT  PB2
#define MIKROBUS_5_DIP_RX       // Pin not routed to mikroBUS.
#define MIKROBUS_5_DIP_TX       // Pin not routed to mikroBUS.
#define MIKROBUS_5_DIP_SCL      // Pin not routed to mikroBUS.
#define MIKROBUS_5_DIP_SDA      // Pin not routed to mikroBUS.

#define USB_UART_DIP_TX         // UART not supported
#define USB_UART_DIP_RX         // UART not supported

#ifdef __cplusplus
}
#endif

#endif // _DIP_SOCKET_H_
// ------------------------------------------------------------------------- END
