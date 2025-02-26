/****************************************************************************
**
** Copyright (C) 2025 MikroElektronika d.o.o.
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

// Mapping
#define HEADER_CONNECTOR_J3_D1  // Pin not routed
#define HEADER_CONNECTOR_J3_D2  GPIO_PA5
#define HEADER_CONNECTOR_J3_D3  // Pin not routed
#define HEADER_CONNECTOR_J3_D4  GPIO_PA4
#define HEADER_CONNECTOR_J3_D5  // Pin not routed
#define HEADER_CONNECTOR_J3_D6  GPIO_PA3
#define HEADER_CONNECTOR_J3_D7  // Pin not routed
#define HEADER_CONNECTOR_J3_D8  GPIO_PC5
#define HEADER_CONNECTOR_J3_D9  GPIO_PC7
#define HEADER_CONNECTOR_J3_D10 GPIO_PC4
#define HEADER_CONNECTOR_J3_D11 GPIO_PC6
#define HEADER_CONNECTOR_J3_D12 GPIO_PC3
#define HEADER_CONNECTOR_J3_D13 GPIO_PB7
#define HEADER_CONNECTOR_J3_D14 GPIO_PA0
#define HEADER_CONNECTOR_J3_D15 GPIO_PB6
#define HEADER_CONNECTOR_J3_D16 GPIO_PA1
#define HEADER_CONNECTOR_J3_D17 GPIO_PB5
#define HEADER_CONNECTOR_J3_D18 GPIO_PA2
#define HEADER_CONNECTOR_J3_D19 GPIO_PB4
#define HEADER_CONNECTOR_J3_D20 GPIO_PC0
#define HEADER_CONNECTOR_J3_D21 GPIO_PB3
#define HEADER_CONNECTOR_J3_D22 GPIO_PC1
#define HEADER_CONNECTOR_J3_D23 GPIO_PB2
#define HEADER_CONNECTOR_J3_D24 GPIO_PC2
#define HEADER_CONNECTOR_J3_D25 GPIO_PB1
#define HEADER_CONNECTOR_J3_D26 // Pin not routed
#define HEADER_CONNECTOR_J3_D27 GPIO_PB0
#define HEADER_CONNECTOR_J3_D28 // Pin not routed

#ifdef __cplusplus
}
#endif

#endif // _DIP_SOCKET_H_
// ------------------------------------------------------------------------- END
