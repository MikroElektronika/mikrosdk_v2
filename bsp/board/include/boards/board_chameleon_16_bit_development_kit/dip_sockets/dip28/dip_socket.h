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
#ifdef dsPIC30F
#define MCU_CONNECTOR_1     // Pin not routed
#define MCU_CONNECTOR_2     GPIO_PB0
#define MCU_CONNECTOR_3     GPIO_PB1
#define MCU_CONNECTOR_4     GPIO_PB2
#define MCU_CONNECTOR_5     GPIO_PB3
#define MCU_CONNECTOR_6     GPIO_PB4
#define MCU_CONNECTOR_7     GPIO_PB5
#define MCU_CONNECTOR_8     // Pin not routed
#define MCU_CONNECTOR_9     // Pin not routed
#define MCU_CONNECTOR_10    // Pin not routed
#define MCU_CONNECTOR_11    GPIO_PC13
#define MCU_CONNECTOR_12    GPIO_PC14
#define MCU_CONNECTOR_13    // Pin not routed
#define MCU_CONNECTOR_14    GPIO_PD1
#define MCU_CONNECTOR_15    GPIO_PD0
#define MCU_CONNECTOR_16    GPIO_PE8
#define MCU_CONNECTOR_17    GPIO_PF3
#define MCU_CONNECTOR_18    GPIO_PF2
#define MCU_CONNECTOR_19    // Pin not routed
#define MCU_CONNECTOR_20    // Pin not routed
#define MCU_CONNECTOR_21    GPIO_PE5
#define MCU_CONNECTOR_22    GPIO_PE4
#define MCU_CONNECTOR_23    GPIO_PE3
#define MCU_CONNECTOR_24    GPIO_PE2
#define MCU_CONNECTOR_25    GPIO_PE1
#define MCU_CONNECTOR_26    GPIO_PE0
#define MCU_CONNECTOR_27    // Pin not routed
#define MCU_CONNECTOR_28    // Pin not routed
#else
#define MCU_CONNECTOR_1     // Pin not routed
#define MCU_CONNECTOR_2     GPIO_PA0
#define MCU_CONNECTOR_3     GPIO_PA1
#define MCU_CONNECTOR_4     GPIO_PB0
#define MCU_CONNECTOR_5     GPIO_PB1
#define MCU_CONNECTOR_6     GPIO_PB2
#define MCU_CONNECTOR_7     GPIO_PB3
#define MCU_CONNECTOR_8     // Pin not routed
#define MCU_CONNECTOR_9     // Pin not routed
#define MCU_CONNECTOR_10    // Pin not routed
#define MCU_CONNECTOR_11    GPIO_PB4
#define MCU_CONNECTOR_12    GPIO_PA4
#define MCU_CONNECTOR_13    // Pin not routed
#define MCU_CONNECTOR_14    GPIO_PB5
#define MCU_CONNECTOR_15    GPIO_PB6
#define MCU_CONNECTOR_16    GPIO_PB7
#define MCU_CONNECTOR_17    GPIO_PB8
#define MCU_CONNECTOR_18    GPIO_PB9
#define MCU_CONNECTOR_19    // Pin not routed
#define MCU_CONNECTOR_20    // Pin not routed
#define MCU_CONNECTOR_21    GPIO_PB10
#define MCU_CONNECTOR_22    GPIO_PB11
#define MCU_CONNECTOR_23    GPIO_PB12
#define MCU_CONNECTOR_24    GPIO_PB13
#define MCU_CONNECTOR_25    GPIO_PB14
#define MCU_CONNECTOR_26    GPIO_PB15
#define MCU_CONNECTOR_27    // Pin not routed
#define MCU_CONNECTOR_28    // Pin not routed
#endif

#ifdef __cplusplus
}
#endif

#endif // _DIP_SOCKET_H_
// ------------------------------------------------------------------------- END
