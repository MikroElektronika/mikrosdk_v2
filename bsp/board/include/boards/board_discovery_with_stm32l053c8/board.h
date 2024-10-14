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

#define BOARD_NAME "STM32L053C8_DISCOVERY"

#include "hal_target.h"

// Mapping
#define HEADER_CONNECTOR_CN1_D1	PB7
#define HEADER_CONNECTOR_CN1_D2	PB6
#define HEADER_CONNECTOR_CN1_D3	PB12
#define HEADER_CONNECTOR_CN1_D4	PB14
#define HEADER_CONNECTOR_CN1_D5	PB15
#define HEADER_CONNECTOR_CN1_D6	PB13
#define HEADER_CONNECTOR_CN1_D7	// Pin not routed
#define HEADER_CONNECTOR_CN1_D8	// Pin not routed

#define HEADER_CONNECTOR_CN3_D1	// Pin not routed
#define HEADER_CONNECTOR_CN3_D2	PA11
#define HEADER_CONNECTOR_CN3_D3	PA12
#define HEADER_CONNECTOR_CN3_D4	// Pin not routed
#define HEADER_CONNECTOR_CN3_D5	// Pin not routed
#define HEADER_CONNECTOR_CN3_D6	// Pin not routed
#define HEADER_CONNECTOR_CN3_D7	// Pin not routed
#define HEADER_CONNECTOR_CN3_D8	// Pin not routed

#define HEADER_CONNECTOR_P2_D1 	// Pin not routed
#define HEADER_CONNECTOR_P2_D2 	// Pin not routed
#define HEADER_CONNECTOR_P2_D3 	PB9
#define HEADER_CONNECTOR_P2_D4 	PB8
#define HEADER_CONNECTOR_P2_D5 	// Pin not routed
#define HEADER_CONNECTOR_P2_D6 	// Pin not routed
#define HEADER_CONNECTOR_P2_D7 	PB7
#define HEADER_CONNECTOR_P2_D8 	PB6
#define HEADER_CONNECTOR_P2_D9 	PB5
#define HEADER_CONNECTOR_P2_D10	PB4
#define HEADER_CONNECTOR_P2_D11	PB3
#define HEADER_CONNECTOR_P2_D12	PA15
#define HEADER_CONNECTOR_P2_D13	PA14
#define HEADER_CONNECTOR_P2_D14	PA13
#define HEADER_CONNECTOR_P2_D15	PA12
#define HEADER_CONNECTOR_P2_D16	PA11
#define HEADER_CONNECTOR_P2_D17	PA10
#define HEADER_CONNECTOR_P2_D18	PA9
#define HEADER_CONNECTOR_P2_D19	PA8
#define HEADER_CONNECTOR_P2_D20	PB15
#define HEADER_CONNECTOR_P2_D21	PB14
#define HEADER_CONNECTOR_P2_D22	PB13
#define HEADER_CONNECTOR_P2_D23	PB12
#define HEADER_CONNECTOR_P2_D24	// Pin not routed
#define HEADER_CONNECTOR_P2_D25	// Pin not routed

#define HEADER_CONNECTOR_P3_D1 	// Pin not routed
#define HEADER_CONNECTOR_P3_D2 	// Pin not routed
#define HEADER_CONNECTOR_P3_D3 	// Pin not routed
#define HEADER_CONNECTOR_P3_D4 	PC13
#define HEADER_CONNECTOR_P3_D5 	PC14
#define HEADER_CONNECTOR_P3_D6 	PC15
#define HEADER_CONNECTOR_P3_D7 	PH0
#define HEADER_CONNECTOR_P3_D8 	PH1
#define HEADER_CONNECTOR_P3_D9 	// Pin not routed
#define HEADER_CONNECTOR_P3_D10	// Pin not routed
#define HEADER_CONNECTOR_P3_D11	PA0
#define HEADER_CONNECTOR_P3_D12	PA1
#define HEADER_CONNECTOR_P3_D13	PA2
#define HEADER_CONNECTOR_P3_D14	PA3
#define HEADER_CONNECTOR_P3_D15	PA4
#define HEADER_CONNECTOR_P3_D16	PA5
#define HEADER_CONNECTOR_P3_D17	PA6
#define HEADER_CONNECTOR_P3_D18	PA7
#define HEADER_CONNECTOR_P3_D19	PB0
#define HEADER_CONNECTOR_P3_D20	PB1
#define HEADER_CONNECTOR_P3_D21	PB2
#define HEADER_CONNECTOR_P3_D22	PB10
#define HEADER_CONNECTOR_P3_D23	PB11
#define HEADER_CONNECTOR_P3_D24	// Pin not routed
#define HEADER_CONNECTOR_P3_D25	// Pin not routed

#ifdef __cplusplus
}
#endif

#endif    // _BOARD_H_
// ------------------------------------------------------------------------- END