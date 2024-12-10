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

#define BOARD_NAME "Nucleo-L412RB"

#include "hal_target.h"

// Mapping
#define HEADER_CONNECTOR_CN1_D1 	PC10
#define HEADER_CONNECTOR_CN1_D2 	PC11
#define HEADER_CONNECTOR_CN1_D3 	PC12
#define HEADER_CONNECTOR_CN1_D4 	PD2
#define HEADER_CONNECTOR_CN1_D5 	// Pin not routed
#define HEADER_CONNECTOR_CN1_D6 	// Pin not routed
#define HEADER_CONNECTOR_CN1_D7 	// Pin not routed
#define HEADER_CONNECTOR_CN1_D8 	// Pin not routed
#define HEADER_CONNECTOR_CN1_D9 	// Pin not routed
#define HEADER_CONNECTOR_CN1_D10	// Pin not routed
#define HEADER_CONNECTOR_CN1_D11	// Pin not routed
#define HEADER_CONNECTOR_CN1_D12	// Pin not routed
#define HEADER_CONNECTOR_CN1_D13	PB12
#define HEADER_CONNECTOR_CN1_D14	// Pin not routed
#define HEADER_CONNECTOR_CN1_D15	PA13
#define HEADER_CONNECTOR_CN1_D16	// Pin not routed
#define HEADER_CONNECTOR_CN1_D17	PA14
#define HEADER_CONNECTOR_CN1_D18	// Pin not routed
#define HEADER_CONNECTOR_CN1_D19	// Pin not routed
#define HEADER_CONNECTOR_CN1_D20	// Pin not routed
#define HEADER_CONNECTOR_CN1_D21	// Pin not routed
#define HEADER_CONNECTOR_CN1_D22	// Pin not routed
#define HEADER_CONNECTOR_CN1_D23	PC13
#define HEADER_CONNECTOR_CN1_D24	// Pin not routed
#define HEADER_CONNECTOR_CN1_D25	PC14
#define HEADER_CONNECTOR_CN1_D26	// Pin not routed
#define HEADER_CONNECTOR_CN1_D27	PC15
#define HEADER_CONNECTOR_CN1_D28	PA0
#define HEADER_CONNECTOR_CN1_D29	PH0
#define HEADER_CONNECTOR_CN1_D30	PA1
#define HEADER_CONNECTOR_CN1_D31	PH1
#define HEADER_CONNECTOR_CN1_D32	PC3
#define HEADER_CONNECTOR_CN1_D33	// Pin not routed
#define HEADER_CONNECTOR_CN1_D34	PC2
#define HEADER_CONNECTOR_CN1_D35	PB4
#define HEADER_CONNECTOR_CN1_D36	PC1
#define HEADER_CONNECTOR_CN1_D37	PB9
#define HEADER_CONNECTOR_CN1_D38	PC0

#define HEADER_CONNECTOR_CN2_D1 	PC9
#define HEADER_CONNECTOR_CN2_D2 	PC8
#define HEADER_CONNECTOR_CN2_D3 	PB8
#define HEADER_CONNECTOR_CN2_D4 	PC6
#define HEADER_CONNECTOR_CN2_D5 	PB7
#define HEADER_CONNECTOR_CN2_D6 	PC5
#define HEADER_CONNECTOR_CN2_D7 	// Pin not routed
#define HEADER_CONNECTOR_CN2_D8 	// Pin not routed
#define HEADER_CONNECTOR_CN2_D9 	// Pin not routed
#define HEADER_CONNECTOR_CN2_D10	PB0
#define HEADER_CONNECTOR_CN2_D11	PB13
#define HEADER_CONNECTOR_CN2_D12	PA10
#define HEADER_CONNECTOR_CN2_D13	PB14
#define HEADER_CONNECTOR_CN2_D14	PA9
#define HEADER_CONNECTOR_CN2_D15	PB15
#define HEADER_CONNECTOR_CN2_D16	PB11
#define HEADER_CONNECTOR_CN2_D17	PA11
#define HEADER_CONNECTOR_CN2_D18	PB2
#define HEADER_CONNECTOR_CN2_D19	PA8
#define HEADER_CONNECTOR_CN2_D20	// Pin not routed
#define HEADER_CONNECTOR_CN2_D21	PB6
#define HEADER_CONNECTOR_CN2_D22	PB1
#define HEADER_CONNECTOR_CN2_D23	PC7
#define HEADER_CONNECTOR_CN2_D24	PA7
#define HEADER_CONNECTOR_CN2_D25	PB10
#define HEADER_CONNECTOR_CN2_D26	PA6
#define HEADER_CONNECTOR_CN2_D27	PA15
#define HEADER_CONNECTOR_CN2_D28	PA5
#define HEADER_CONNECTOR_CN2_D29	PB5
#define HEADER_CONNECTOR_CN2_D30	PA4
#define HEADER_CONNECTOR_CN2_D31	PB3
#define HEADER_CONNECTOR_CN2_D32	// Pin not routed
#define HEADER_CONNECTOR_CN2_D33	PA12
#define HEADER_CONNECTOR_CN2_D34	PC4
#define HEADER_CONNECTOR_CN2_D35	PA2
#define HEADER_CONNECTOR_CN2_D36	PA3
#define HEADER_CONNECTOR_CN2_D37	PA3
#define HEADER_CONNECTOR_CN2_D38	PA2

#define HEADER_CONNECTOR_CN7_D1 	PB6
#define HEADER_CONNECTOR_CN7_D2 	PA8
#define HEADER_CONNECTOR_CN7_D3 	PA11
#define HEADER_CONNECTOR_CN7_D4 	PB15
#define HEADER_CONNECTOR_CN7_D5 	PB14
#define HEADER_CONNECTOR_CN7_D6 	PB13
#define HEADER_CONNECTOR_CN7_D7 	// Pin not routed
#define HEADER_CONNECTOR_CN7_D8 	// Pin not routed
#define HEADER_CONNECTOR_CN7_D9 	PB7
#define HEADER_CONNECTOR_CN7_D10	PB8

#define HEADER_CONNECTOR_CN9_D1 	PA3
#define HEADER_CONNECTOR_CN9_D2 	PA2
#define HEADER_CONNECTOR_CN9_D3 	PA12
#define HEADER_CONNECTOR_CN9_D4 	PB3
#define HEADER_CONNECTOR_CN9_D5 	PB5
#define HEADER_CONNECTOR_CN9_D6 	PA15
#define HEADER_CONNECTOR_CN9_D7 	PB10
#define HEADER_CONNECTOR_CN9_D8 	PC7

#define HEADER_CONNECTOR_CN10_D1	PA0
#define HEADER_CONNECTOR_CN10_D2	PA1
#define HEADER_CONNECTOR_CN10_D3	PC3
#define HEADER_CONNECTOR_CN10_D4	PC2
#define HEADER_CONNECTOR_CN10_D5	PC1
#define HEADER_CONNECTOR_CN10_D6	PC0

#define HEADER_CONNECTOR_CN11_D1	// Pin not routed
#define HEADER_CONNECTOR_CN11_D2	// Pin not routed
#define HEADER_CONNECTOR_CN11_D3	// Pin not routed
#define HEADER_CONNECTOR_CN11_D4	PA5
#define HEADER_CONNECTOR_CN11_D5	PA4
#define HEADER_CONNECTOR_CN11_D6	PA7
#define HEADER_CONNECTOR_CN11_D7	PA6
#define HEADER_CONNECTOR_CN11_D8	// Pin not routed

#ifdef __cplusplus
}
#endif

#endif    // _BOARD_H_
// ------------------------------------------------------------------------- END
