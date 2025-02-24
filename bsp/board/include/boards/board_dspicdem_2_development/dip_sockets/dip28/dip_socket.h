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
#ifndef GPIO_PB0
#define GPIO_PB0 // Pin not routed
#endif
#ifndef GPIO_PB1
#define GPIO_PB1 // Pin not routed
#endif
#ifndef GPIO_PB2
#define GPIO_PB2 // Pin not routed
#endif
#ifndef GPIO_PB3
#define GPIO_PB3 // Pin not routed
#endif
#ifndef GPIO_PB4
#define GPIO_PB4 // Pin not routed
#endif
#ifndef GPIO_PB5
#define GPIO_PB5 // Pin not routed
#endif
#ifndef GPIO_PB6
#define GPIO_PB6 // Pin not routed
#endif
#ifndef GPIO_PB7
#define GPIO_PB7 // Pin not routed
#endif
#ifndef GPIO_PB8
#define GPIO_PB8 // Pin not routed
#endif
#ifndef GPIO_PC13
#define GPIO_PC13 // Pin not routed
#endif
#ifndef GPIO_PC14
#define GPIO_PC14 // Pin not routed
#endif
#ifndef GPIO_PD9
#define GPIO_PD9 // Pin not routed
#endif
#ifndef GPIO_PD8
#define GPIO_PD8 // Pin not routed
#endif
#ifndef GPIO_PF6
#define GPIO_PF6 // Pin not routed
#endif
#ifndef GPIO_PF3
#define GPIO_PF3 // Pin not routed
#endif
#ifndef GPIO_PF2
#define GPIO_PF2 // Pin not routed
#endif
#ifndef GPIO_PF5
#define GPIO_PF5 // Pin not routed
#endif
#ifndef GPIO_PF4
#define GPIO_PF4 // Pin not routed
#endif
#ifndef GPIO_PB9
#define GPIO_PB9 // Pin not routed
#endif
#ifndef GPIO_PE8
#define GPIO_PE8 // Pin not routed
#endif
#ifndef GPIO_PD1
#define GPIO_PD1 // Pin not routed
#endif
#ifndef GPIO_PD0
#define GPIO_PD0 // Pin not routed
#endif
#ifndef GPIO_PE5
#define GPIO_PE5 // Pin not routed
#endif
#ifndef GPIO_PE4
#define GPIO_PE4 // Pin not routed
#endif
#ifndef GPIO_PE3
#define GPIO_PE3 // Pin not routed
#endif
#ifndef GPIO_PE2
#define GPIO_PE2 // Pin not routed
#endif
#ifndef GPIO_PE1
#define GPIO_PE1 // Pin not routed
#endif
#ifndef GPIO_PE0
#define GPIO_PE0 // Pin not routed
#endif

#define CONNECTOR_RB0_1     GPIO_PB0
#define CONNECTOR_RB1_1     GPIO_PB1
#define CONNECTOR_RB2_1     GPIO_PB2
#define CONNECTOR_RB3_1     GPIO_PB3
#define CONNECTOR_RB4_1     GPIO_PB4
#define CONNECTOR_RB5_1     GPIO_PB5
#define CONNECTOR_RB6_1     GPIO_PB6
#define CONNECTOR_RB7_1     GPIO_PB7
#define CONNECTOR_RB8_1     GPIO_PB8
#define CONNECTOR_RC13_1    GPIO_PC13
#define CONNECTOR_RC14_1    GPIO_PC14
#define CONNECTOR_RA11_1    // Pin not routed
#define CONNECTOR_RD9_1     GPIO_PD9
#define CONNECTOR_RD3_1     // Pin not routed
#define CONNECTOR_RD2_1     // Pin not routed
#define CONNECTOR_RD8_1     GPIO_PD8
#define CONNECTOR_RF6_1     GPIO_PF6
#define CONNECTOR_RF3_1     GPIO_PF3
#define CONNECTOR_RF2_1     GPIO_PF2
#define CONNECTOR_RF5_1     GPIO_PF5
#define CONNECTOR_RF4_1     GPIO_PF4
#define CONNECTOR_RF1_1     // Pin not routed
#define CONNECTOR_RF0_1     // Pin not routed
#define CONNECTOR_RD1_1     // Pin not routed
#define CONNECTOR_RD0_1     // Pin not routed
#define CONNECTOR_RB12_1    // Pin not routed
#define CONNECTOR_RB11_1    // Pin not routed
#define CONNECTOR_RB10_1    // Pin not routed
#define CONNECTOR_RB9_1     GPIO_PB9

#define CONNECTOR_RB0_2     GPIO_PB0
#define CONNECTOR_RB1_2     GPIO_PB1
#define CONNECTOR_RB2_2     GPIO_PB2
#define CONNECTOR_RB3_2     GPIO_PB3
#define CONNECTOR_RB4_2     GPIO_PB4
#define CONNECTOR_RB5_2     GPIO_PB5
#define CONNECTOR_RB6_2     // Pin not routed
#define CONNECTOR_RB7_2     // Pin not routed
#define CONNECTOR_RB8_2     // Pin not routed
#define CONNECTOR_RC13_2    GPIO_PC13
#define CONNECTOR_RC14_2    GPIO_PC14
#define CONNECTOR_RE8_2     GPIO_PE8
#define CONNECTOR_RD1_2     GPIO_PD1
#define CONNECTOR_RD3_2     // Pin not routed
#define CONNECTOR_RD2_2     // Pin not routed
#define CONNECTOR_RD0_2     GPIO_PD0
#define CONNECTOR_RF6_2     // Pin not routed
#define CONNECTOR_RF3_2     GPIO_PF3
#define CONNECTOR_RF2_2     GPIO_PF2
#define CONNECTOR_RF5_2     // Pin not routed
#define CONNECTOR_RF4_2     // Pin not routed
#define CONNECTOR_RF1_2     // Pin not routed
#define CONNECTOR_RF0_2     // Pin not routed
#define CONNECTOR_RE5_2     GPIO_PE5
#define CONNECTOR_RE4_2     GPIO_PE4
#define CONNECTOR_RE3_2     GPIO_PE3
#define CONNECTOR_RE2_2     GPIO_PE2
#define CONNECTOR_RE1_2     GPIO_PE1
#define CONNECTOR_RE0_2     GPIO_PE0

#ifdef __cplusplus
}
#endif

#endif // _DIP_SOCKET_H_
// ------------------------------------------------------------------------- END
