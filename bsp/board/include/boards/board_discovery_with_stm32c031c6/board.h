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
** OF MERCHANTABILITY, EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED
** TO THE WARRANTIES FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT.
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

#define BOARD_NAME "STM32C031C6_DISCOVERY"

#include "hal_target.h"

// Mapping
#define HEADER_CONNECTOR_CN1_D1 	PA0
#define HEADER_CONNECTOR_CN1_D2 	PA2
#define HEADER_CONNECTOR_CN1_D3 	PA3
#define HEADER_CONNECTOR_CN1_D4 	PA1
#define HEADER_CONNECTOR_CN1_D5 	// Pin not routed
#define HEADER_CONNECTOR_CN1_D6 	// Pin not routed
#define HEADER_CONNECTOR_CN1_D7 	PA11
#define HEADER_CONNECTOR_CN1_D8 	PA7
#define HEADER_CONNECTOR_CN1_D9 	PD2
#define HEADER_CONNECTOR_CN1_D10	PA12
#define HEADER_CONNECTOR_CN1_D11	PC14
#define HEADER_CONNECTOR_CN1_D12	PC15
#define HEADER_CONNECTOR_CN1_D13	PA4
#define HEADER_CONNECTOR_CN1_D14	PA5
#define HEADER_CONNECTOR_CN1_D15	// Pin not routed
#define HEADER_CONNECTOR_CN1_D16	// Pin not routed
#define HEADER_CONNECTOR_CN1_D17	PB0
#define HEADER_CONNECTOR_CN1_D18	PA6
#define HEADER_CONNECTOR_CN1_D19	PD1
#define HEADER_CONNECTOR_CN1_D20	PD0

#define HEADER_CONNECTOR_CN6_D1 	// Pin not routed
#define HEADER_CONNECTOR_CN6_D2 	PA3
#define HEADER_CONNECTOR_CN6_D3 	PA2
#define HEADER_CONNECTOR_CN6_D4 	PA13
#define HEADER_CONNECTOR_CN6_D5 	PA14
#define HEADER_CONNECTOR_CN6_D6 	PA0
#define HEADER_CONNECTOR_CN6_D7 	// Pin not routed
#define HEADER_CONNECTOR_CN6_D8 	// Pin not routed
#define HEADER_CONNECTOR_CN6_D9 	// Pin not routed
#define HEADER_CONNECTOR_CN6_D10	// Pin not routed
#define HEADER_CONNECTOR_CN6_D11	PC14
#define HEADER_CONNECTOR_CN6_D12	PC15
#define HEADER_CONNECTOR_CN6_D13	PA5
#define HEADER_CONNECTOR_CN6_D14	PA4

#define HEADER_CONNECTOR_CN7_D1 	PA11
#define HEADER_CONNECTOR_CN7_D2 	PA12
#define HEADER_CONNECTOR_CN7_D3 	PA9
#define HEADER_CONNECTOR_CN7_D4 	PA10
#define HEADER_CONNECTOR_CN7_D5 	PA5
#define HEADER_CONNECTOR_CN7_D6 	PA4
#define HEADER_CONNECTOR_CN7_D7 	// Pin not routed
#define HEADER_CONNECTOR_CN7_D8 	// Pin not routed
#define HEADER_CONNECTOR_CN7_D9 	// Pin not routed
#define HEADER_CONNECTOR_CN7_D10	PA1
#define HEADER_CONNECTOR_CN7_D11	PA6
#define HEADER_CONNECTOR_CN7_D12	PA7
#define HEADER_CONNECTOR_CN7_D13	PB0
#define HEADER_CONNECTOR_CN7_D14	PB8

#ifdef __cplusplus
}
#endif

#endif    // _BOARD_H_
// ------------------------------------------------------------------------- END