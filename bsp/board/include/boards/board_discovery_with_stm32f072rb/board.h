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

#define BOARD_NAME "STM32F072RB_DISCOVERY"

#include "hal_target.h"

// Mapping
#define HEADER_CONNECTOR_CN3_D1	PB11
#define HEADER_CONNECTOR_CN3_D2	// Pin not routed
#define HEADER_CONNECTOR_CN3_D3	PB10
#define HEADER_CONNECTOR_CN3_D4	PC5
#define HEADER_CONNECTOR_CN3_D5	// Pin not routed
#define HEADER_CONNECTOR_CN3_D6	// Pin not routed
#define HEADER_CONNECTOR_CN3_D7	// Pin not routed
#define HEADER_CONNECTOR_CN3_D8	// Pin not routed

#define HEADER_CONNECTOR_CN4_D1	// Pin not routed
#define HEADER_CONNECTOR_CN4_D2	PA14
#define HEADER_CONNECTOR_CN4_D3	// Pin not routed
#define HEADER_CONNECTOR_CN4_D4	PA13
#define HEADER_CONNECTOR_CN4_D5	// Pin not routed

#define HEADER_CONNECTOR_P1_D1 	// Pin not routed
#define HEADER_CONNECTOR_P1_D2 	// Pin not routed
#define HEADER_CONNECTOR_P1_D3 	// Pin not routed
#define HEADER_CONNECTOR_P1_D4 	PC13
#define HEADER_CONNECTOR_P1_D5 	PC14
#define HEADER_CONNECTOR_P1_D6 	PC15
#define HEADER_CONNECTOR_P1_D7 	PF0
#define HEADER_CONNECTOR_P1_D8 	PF1
#define HEADER_CONNECTOR_P1_D9 	// Pin not routed
#define HEADER_CONNECTOR_P1_D10	// Pin not routed
#define HEADER_CONNECTOR_P1_D11	PC0
#define HEADER_CONNECTOR_P1_D12	PC1
#define HEADER_CONNECTOR_P1_D13	PC2
#define HEADER_CONNECTOR_P1_D14	PC3
#define HEADER_CONNECTOR_P1_D15	PA0
#define HEADER_CONNECTOR_P1_D16	PA1
#define HEADER_CONNECTOR_P1_D17	PA2
#define HEADER_CONNECTOR_P1_D18	PA3
#define HEADER_CONNECTOR_P1_D19	// Pin not routed
#define HEADER_CONNECTOR_P1_D20	// Pin not routed
#define HEADER_CONNECTOR_P1_D21	PA4
#define HEADER_CONNECTOR_P1_D22	PA5
#define HEADER_CONNECTOR_P1_D23	PA6
#define HEADER_CONNECTOR_P1_D24	PA7
#define HEADER_CONNECTOR_P1_D25	PC4
#define HEADER_CONNECTOR_P1_D26	PC5
#define HEADER_CONNECTOR_P1_D27	PB0
#define HEADER_CONNECTOR_P1_D28	PB1
#define HEADER_CONNECTOR_P1_D29	PB2
#define HEADER_CONNECTOR_P1_D30	PB10
#define HEADER_CONNECTOR_P1_D31	PB11
#define HEADER_CONNECTOR_P1_D32	PB12
#define HEADER_CONNECTOR_P1_D33	// Pin not routed

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
#define HEADER_CONNECTOR_P2_D12	PD2
#define HEADER_CONNECTOR_P2_D13	PC12
#define HEADER_CONNECTOR_P2_D14	PC11
#define HEADER_CONNECTOR_P2_D15	PC10
#define HEADER_CONNECTOR_P2_D16	PA15
#define HEADER_CONNECTOR_P2_D17	PA14
#define HEADER_CONNECTOR_P2_D18	// Pin not routed
#define HEADER_CONNECTOR_P2_D19	// Pin not routed
#define HEADER_CONNECTOR_P2_D20	PA13
#define HEADER_CONNECTOR_P2_D21	PA12
#define HEADER_CONNECTOR_P2_D22	PA11
#define HEADER_CONNECTOR_P2_D23	PA10
#define HEADER_CONNECTOR_P2_D24	PA9
#define HEADER_CONNECTOR_P2_D25	PA8
#define HEADER_CONNECTOR_P2_D26	PC9
#define HEADER_CONNECTOR_P2_D27	PC8
#define HEADER_CONNECTOR_P2_D28	PC7
#define HEADER_CONNECTOR_P2_D29	PC6
#define HEADER_CONNECTOR_P2_D30	PB15
#define HEADER_CONNECTOR_P2_D31	PB14
#define HEADER_CONNECTOR_P2_D32	PB13
#define HEADER_CONNECTOR_P2_D33	// Pin not routed

#ifdef __cplusplus
}
#endif

#endif    // _BOARD_H_
// ------------------------------------------------------------------------- END
