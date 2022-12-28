/****************************************************************************
**
** Copyright (C) 2022 MikroElektronika d.o.o.
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
#define MIKROBUS_1_DIP_AN   PA2
#define MIKROBUS_1_DIP_RST  PE1
#define MIKROBUS_1_DIP_CS   PE0
#define MIKROBUS_1_DIP_SCK  PC3
#define MIKROBUS_1_DIP_MISO PC4
#define MIKROBUS_1_DIP_MOSI PC5
#define MIKROBUS_1_DIP_PWM  PC0
#define MIKROBUS_1_DIP_INT  PB0
#define MIKROBUS_1_DIP_RX   PC7
#define MIKROBUS_1_DIP_TX   PC6
#define MIKROBUS_1_DIP_SCL  PC3
#define MIKROBUS_1_DIP_SDA  PC4

#define MIKROBUS_2_DIP_AN   PA3
#define MIKROBUS_2_DIP_RST  PE2
#define MIKROBUS_2_DIP_CS   PA5
#define MIKROBUS_2_DIP_SCK  PC3
#define MIKROBUS_2_DIP_MISO PC4
#define MIKROBUS_2_DIP_MOSI PC5
#define MIKROBUS_2_DIP_PWM  PC1
#define MIKROBUS_2_DIP_INT  PB1
#define MIKROBUS_2_DIP_RX   PC7
#define MIKROBUS_2_DIP_TX   PC6
#define MIKROBUS_2_DIP_SCL  PC3
#define MIKROBUS_2_DIP_SDA  PC4

#define USB_UART_DIP_TX PC6
#define USB_UART_DIP_RX PC7

#ifdef __cplusplus
}
#endif

#endif // _DIP_SOCKET_H_
// ------------------------------------------------------------------------- END
