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
 * @file  shield.h
 * @brief Click shield for Nucleo-32 connections mapping.
 */

#ifndef _SHIELD_H_
#define _SHIELD_H_

#ifdef __cplusplus
extern "C"{
#endif

#include "mikrobus.h"

// MikroBUS definitions
#define MIKROBUS_1 1
#define MIKROBUS_1_AN   HEADER_CONNECTOR_CN4_D12
#define MIKROBUS_1_RST  HEADER_CONNECTOR_CN3_D13
#define MIKROBUS_1_CS   HEADER_CONNECTOR_CN4_D9
#define MIKROBUS_1_SCK  HEADER_CONNECTOR_CN4_D15
#define MIKROBUS_1_MISO HEADER_CONNECTOR_CN3_D15
#define MIKROBUS_1_MOSI HEADER_CONNECTOR_CN3_D14
#define MIKROBUS_1_PWM  HEADER_CONNECTOR_CN3_D12
#define MIKROBUS_1_INT  HEADER_CONNECTOR_CN3_D5
#define MIKROBUS_1_RX   HEADER_CONNECTOR_CN3_D2
#define MIKROBUS_1_TX   HEADER_CONNECTOR_CN3_D1
#define MIKROBUS_1_SCL  HEADER_CONNECTOR_CN3_D8
#define MIKROBUS_1_SDA  HEADER_CONNECTOR_CN3_D7

#define MIKROBUS_2 2
#define MIKROBUS_2_AN   HEADER_CONNECTOR_CN4_D8
#define MIKROBUS_2_RST  HEADER_CONNECTOR_CN4_D11
#define MIKROBUS_2_CS   HEADER_CONNECTOR_CN3_D6
#define MIKROBUS_2_SCK  HEADER_CONNECTOR_CN4_D15
#define MIKROBUS_2_MISO HEADER_CONNECTOR_CN3_D15
#define MIKROBUS_2_MOSI HEADER_CONNECTOR_CN3_D14
#define MIKROBUS_2_PWM  HEADER_CONNECTOR_CN4_D7
#define MIKROBUS_2_INT  HEADER_CONNECTOR_CN4_D6
#define MIKROBUS_2_RX   HEADER_CONNECTOR_CN4_D10
#define MIKROBUS_2_TX   HEADER_CONNECTOR_CN4_D5
#define MIKROBUS_2_SCL  HEADER_CONNECTOR_CN3_D8
#define MIKROBUS_2_SDA  HEADER_CONNECTOR_CN3_D7

#ifdef __cplusplus
}
#endif

#endif // _SHIELD_H_
// ------------------------------------------------------------------------- END
