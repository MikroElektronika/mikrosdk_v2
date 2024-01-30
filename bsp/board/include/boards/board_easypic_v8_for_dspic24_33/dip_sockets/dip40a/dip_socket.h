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
#define MIKROBUS_1_DIP_AN PB11
#define MIKROBUS_1_DIP_RST PA11
#define MIKROBUS_1_DIP_CS PB6
#define MIKROBUS_1_DIP_SCK PF6
#define MIKROBUS_1_DIP_MISO PF2
#define MIKROBUS_1_DIP_MOSI PF3
#define MIKROBUS_1_DIP_PWM PD2
#define MIKROBUS_1_DIP_INT PD8
#define MIKROBUS_1_DIP_RX PF2
#define MIKROBUS_1_DIP_TX PF3
#define MIKROBUS_1_DIP_SCL PF3
#define MIKROBUS_1_DIP_SDA PF2

#define MIKROBUS_2_DIP_AN PB7
#define MIKROBUS_2_DIP_RST PB10
#define MIKROBUS_2_DIP_CS PC13
#define MIKROBUS_2_DIP_SCK PF6
#define MIKROBUS_2_DIP_MISO PF2
#define MIKROBUS_2_DIP_MOSI PF3
#define MIKROBUS_2_DIP_PWM PD3
#define MIKROBUS_2_DIP_INT PD9
#define MIKROBUS_2_DIP_RX PF4
#define MIKROBUS_2_DIP_TX PF5
#define MIKROBUS_2_DIP_SCL PF3
#define MIKROBUS_2_DIP_SDA PF2

#define MIKROBUS_3_DIP_AN PB3
#define MIKROBUS_3_DIP_RST PB8
#define MIKROBUS_3_DIP_CS PC14
#define MIKROBUS_3_DIP_SCK PF6
#define MIKROBUS_3_DIP_MISO PF2
#define MIKROBUS_3_DIP_MOSI PF3
#define MIKROBUS_3_DIP_PWM PE3
#define MIKROBUS_3_DIP_INT PD1
#define MIKROBUS_3_DIP_RX PF2
#define MIKROBUS_3_DIP_TX PF3
#define MIKROBUS_3_DIP_SCL PF3
#define MIKROBUS_3_DIP_SDA PF2

#define MIKROBUS_4_DIP_AN PB5
#define MIKROBUS_4_DIP_RST PE5
#define MIKROBUS_4_DIP_CS PE4
#define MIKROBUS_4_DIP_SCK PF6
#define MIKROBUS_4_DIP_MISO PF7
#define MIKROBUS_4_DIP_MOSI PF8
#define MIKROBUS_4_DIP_PWM PE1
#define MIKROBUS_4_DIP_INT PA9
#define MIKROBUS_4_DIP_RX PF7
#define MIKROBUS_4_DIP_TX PF8
#define MIKROBUS_4_DIP_SCL PF8
#define MIKROBUS_4_DIP_SDA PF7

#define MIKROBUS_5_DIP_AN PB3
#define MIKROBUS_5_DIP_RST PB1
#define MIKROBUS_5_DIP_CS PB2
#define MIKROBUS_5_DIP_SCK PB6
#define MIKROBUS_5_DIP_MISO PB5
#define MIKROBUS_5_DIP_MOSI PB4
#define MIKROBUS_5_DIP_PWM PB7
#define MIKROBUS_5_DIP_INT PD0
#define MIKROBUS_5_DIP_RX PB5
#define MIKROBUS_5_DIP_TX PB4
#define MIKROBUS_5_DIP_SCL PB4
#define MIKROBUS_5_DIP_SDA PB5

#define USB_UART_DIP_TX MIKROBUS_1_DIP_TX
#define USB_UART_DIP_RX MIKROBUS_1_DIP_RX

#ifdef __cplusplus
}
#endif

#endif // _DIP_SOCKET_H_
// ------------------------------------------------------------------------- END
