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

#define BOARD_NAME "STM32C011F6_DISCOVERY"

#include "hal_target.h"

// Mapping
#define HEADER_CONNECTOR_CN1_D1 	// Pin not routed
#define HEADER_CONNECTOR_CN1_D2 	GPIO_PA2
#define HEADER_CONNECTOR_CN1_D3 	// Pin not routed
#define HEADER_CONNECTOR_CN1_D4 	// Pin not routed

#define HEADER_CONNECTOR_CN2_D1 	GPIO_PC15
#define HEADER_CONNECTOR_CN2_D2 	GPIO_PA6
#define HEADER_CONNECTOR_CN2_D3 	// Pin not routed
#define HEADER_CONNECTOR_CN2_D4 	GPIO_PA7
#define HEADER_CONNECTOR_CN2_D5 	// Pin not routed
#define HEADER_CONNECTOR_CN2_D6 	GPIO_PA8
#define HEADER_CONNECTOR_CN2_D7 	GPIO_PF2
#define HEADER_CONNECTOR_CN2_D8 	GPIO_PA11
#define HEADER_CONNECTOR_CN2_D9 	GPIO_PA0
#define HEADER_CONNECTOR_CN2_D10	GPIO_PA12
#define HEADER_CONNECTOR_CN2_D11	GPIO_PA1
#define HEADER_CONNECTOR_CN2_D12	GPIO_PA13
#define HEADER_CONNECTOR_CN2_D13	GPIO_PA2
#define HEADER_CONNECTOR_CN2_D14	GPIO_PA14
#define HEADER_CONNECTOR_CN2_D15	GPIO_PA3
#define HEADER_CONNECTOR_CN2_D16	GPIO_PB6
#define HEADER_CONNECTOR_CN2_D17	GPIO_PA4
#define HEADER_CONNECTOR_CN2_D18	GPIO_PB7
#define HEADER_CONNECTOR_CN2_D19	GPIO_PA5
#define HEADER_CONNECTOR_CN2_D20	GPIO_PC14

#define HEADER_CONNECTOR_CN4_D1 	GPIO_PA3
#define HEADER_CONNECTOR_CN4_D2 	GPIO_PA2
#define HEADER_CONNECTOR_CN4_D3 	// Pin not routed
#define HEADER_CONNECTOR_CN4_D4 	// Pin not routed

#define HEADER_CONNECTOR_CN5_D1 	// Pin not routed
#define HEADER_CONNECTOR_CN5_D2 	GPIO_PC15
#define HEADER_CONNECTOR_CN5_D3 	// Pin not routed
#define HEADER_CONNECTOR_CN5_D4 	GPIO_PB7
#define HEADER_CONNECTOR_CN5_D5 	// Pin not routed
#define HEADER_CONNECTOR_CN5_D6 	GPIO_PA9
#define HEADER_CONNECTOR_CN5_D7 	// Pin not routed
#define HEADER_CONNECTOR_CN5_D8 	// Pin not routed
#define HEADER_CONNECTOR_CN5_D9 	// Pin not routed
#define HEADER_CONNECTOR_CN5_D10	// Pin not routed
#define HEADER_CONNECTOR_CN5_D11	GPIO_PA7
#define HEADER_CONNECTOR_CN5_D12	// Pin not routed
#define HEADER_CONNECTOR_CN5_D13	GPIO_PA4
#define HEADER_CONNECTOR_CN5_D14	// Pin not routed
#define HEADER_CONNECTOR_CN5_D15	GPIO_PA8
#define HEADER_CONNECTOR_CN5_D16	GPIO_PA6
#define HEADER_CONNECTOR_CN5_D17	// Pin not routed
#define HEADER_CONNECTOR_CN5_D18	GPIO_PA3
#define HEADER_CONNECTOR_CN5_D19	GPIO_PC14
#define HEADER_CONNECTOR_CN5_D20	// Pin not routed
#define HEADER_CONNECTOR_CN5_D21	GPIO_PA1
#define HEADER_CONNECTOR_CN5_D22	// Pin not routed
#define HEADER_CONNECTOR_CN5_D23	GPIO_PA0
#define HEADER_CONNECTOR_CN5_D24	// Pin not routed
#define HEADER_CONNECTOR_CN5_D25	// Pin not routed
#define HEADER_CONNECTOR_CN5_D26	GPIO_PA5
#define HEADER_CONNECTOR_CN5_D27	// Pin not routed
#define HEADER_CONNECTOR_CN5_D28	// Pin not routed
#define HEADER_CONNECTOR_CN5_D29	// Pin not routed
#define HEADER_CONNECTOR_CN5_D30	// Pin not routed
#define HEADER_CONNECTOR_CN5_D31	// Pin not routed
#define HEADER_CONNECTOR_CN5_D32	// Pin not routed
#define HEADER_CONNECTOR_CN5_D33	GPIO_PB6
#define HEADER_CONNECTOR_CN5_D34	GPIO_PA10
#define HEADER_CONNECTOR_CN5_D35	// Pin not routed
#define HEADER_CONNECTOR_CN5_D36	// Pin not routed
#define HEADER_CONNECTOR_CN5_D37	// Pin not routed
#define HEADER_CONNECTOR_CN5_D38	// Pin not routed

#ifdef __cplusplus
}
#endif

#endif    // _BOARD_H_
// ------------------------------------------------------------------------- END
