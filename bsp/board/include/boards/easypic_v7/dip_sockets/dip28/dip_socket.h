/****************************************************************************
**
** Copyright (C) 2020 MikroElektronika d.o.o.
** Contact: https://www.mikroe.com/contact
**
** This file is part of the mikroSDK package
**
** Commercial License Usage
**
** Licensees holding valid commercial NECTO compilers AI licenses may use this
** file in accordance with the commercial license agreement provided with the
** Software or, alternatively, in accordance with the terms contained in
** a written agreement between you and The mikroElektronika Company.
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
#define MIKROBUS_1_AN_DIP   PA2
#define MIKROBUS_1_CS_DIP       // Pin not routed to mikroBUS.
#define MIKROBUS_1_SCK_DIP  PC3
#define MIKROBUS_1_MISO_DIP PC4
#define MIKROBUS_1_MOSI_DIP PC5
#define MIKROBUS_1_PWM_DIP  PC0
#define MIKROBUS_1_INT_DIP  PB0
#define MIKROBUS_1_RX_DIP   PC7
#define MIKROBUS_1_TX_DIP   PC6
#define MIKROBUS_1_SCL_DIP  PC3
#define MIKROBUS_1_SDA_DIP  PC4

#define MIKROBUS_2_AN_DIP   PA3
#define MIKROBUS_2_CS_DIP   PA5
#define MIKROBUS_2_SCK_DIP  PC3
#define MIKROBUS_2_MISO_DIP PC4
#define MIKROBUS_2_MOSI_DIP PC5
#define MIKROBUS_2_PWM_DIP  PC1
#define MIKROBUS_2_INT_DIP  PB1
#define MIKROBUS_2_RX_DIP   PC7
#define MIKROBUS_2_TX_DIP   PC6
#define MIKROBUS_2_SCL_DIP  PC3
#define MIKROBUS_2_SDA_DIP  PC4

#define USB_UART_TX_DIP     PC6
#define USB_UART_RX_DIP     PC7

#ifdef __cplusplus
}
#endif

#endif // _DIP_SOCKET_H_
// ------------------------------------------------------------------------- END
