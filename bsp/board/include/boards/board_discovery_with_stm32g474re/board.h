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

#define BOARD_NAME "STM32G474RE_DISCOVERY"

#include "hal_target.h"

// Mapping
#define HEADER_CONNECTOR_CN8_D1 	// Pin not routed
#define HEADER_CONNECTOR_CN8_D2 	PC13
#define HEADER_CONNECTOR_CN8_D3 	PC14
#define HEADER_CONNECTOR_CN8_D4 	PC15
#define HEADER_CONNECTOR_CN8_D5 	PF0
#define HEADER_CONNECTOR_CN8_D6 	PF1
#define HEADER_CONNECTOR_CN8_D7 	PG10
#define HEADER_CONNECTOR_CN8_D8 	PC0
#define HEADER_CONNECTOR_CN8_D9 	PC1
#define HEADER_CONNECTOR_CN8_D10	PC2
#define HEADER_CONNECTOR_CN8_D11	PC3
#define HEADER_CONNECTOR_CN8_D12	PA0
#define HEADER_CONNECTOR_CN8_D13	PA1
#define HEADER_CONNECTOR_CN8_D14	PA2
#define HEADER_CONNECTOR_CN8_D15	// Pin not routed
#define HEADER_CONNECTOR_CN8_D16	// Pin not routed
#define HEADER_CONNECTOR_CN8_D17	PA3
#define HEADER_CONNECTOR_CN8_D18	PA4
#define HEADER_CONNECTOR_CN8_D19	PA5
#define HEADER_CONNECTOR_CN8_D20	PA6
#define HEADER_CONNECTOR_CN8_D21	PA7
#define HEADER_CONNECTOR_CN8_D22	PC4
#define HEADER_CONNECTOR_CN8_D23	PB2
#define HEADER_CONNECTOR_CN8_D24	PB0
#define HEADER_CONNECTOR_CN8_D25	PB1
#define HEADER_CONNECTOR_CN8_D26	PB10
#define HEADER_CONNECTOR_CN8_D27	// Pin not routed
#define HEADER_CONNECTOR_CN8_D28	// Pin not routed
#define HEADER_CONNECTOR_CN8_D29	// Pin not routed
#define HEADER_CONNECTOR_CN8_D30	PC5
#define HEADER_CONNECTOR_CN8_D31	// Pin not routed
#define HEADER_CONNECTOR_CN8_D32	// Pin not routed
#define HEADER_CONNECTOR_CN8_D33	PB11
#define HEADER_CONNECTOR_CN8_D34	PB12
#define HEADER_CONNECTOR_CN8_D35	PB13
#define HEADER_CONNECTOR_CN8_D36	PB14
#define HEADER_CONNECTOR_CN8_D37	PB15
#define HEADER_CONNECTOR_CN8_D38	PC6
#define HEADER_CONNECTOR_CN8_D39	PC7
#define HEADER_CONNECTOR_CN8_D40	PC8
#define HEADER_CONNECTOR_CN8_D41	PC9
#define HEADER_CONNECTOR_CN8_D42	PA8
#define HEADER_CONNECTOR_CN8_D43	PA9
#define HEADER_CONNECTOR_CN8_D44	PA10
#define HEADER_CONNECTOR_CN8_D45	PA11
#define HEADER_CONNECTOR_CN8_D46	PA12
#define HEADER_CONNECTOR_CN8_D47	// Pin not routed
#define HEADER_CONNECTOR_CN8_D48	// Pin not routed
#define HEADER_CONNECTOR_CN8_D49	PA13
#define HEADER_CONNECTOR_CN8_D50	PA14
#define HEADER_CONNECTOR_CN8_D51	PA15
#define HEADER_CONNECTOR_CN8_D52	PC10
#define HEADER_CONNECTOR_CN8_D53	PC11
#define HEADER_CONNECTOR_CN8_D54	PC12
#define HEADER_CONNECTOR_CN8_D55	PD2
#define HEADER_CONNECTOR_CN8_D56	PB3
#define HEADER_CONNECTOR_CN8_D57	PB4
#define HEADER_CONNECTOR_CN8_D58	PB5
#define HEADER_CONNECTOR_CN8_D59	PB6
#define HEADER_CONNECTOR_CN8_D60	PB7
#define HEADER_CONNECTOR_CN8_D61	PB8
#define HEADER_CONNECTOR_CN8_D62	PB9
#define HEADER_CONNECTOR_CN8_D63	// Pin not routed
#define HEADER_CONNECTOR_CN8_D64	// Pin not routed

#define HEADER_CONNECTOR_CN9_D1 	// Pin not routed
#define HEADER_CONNECTOR_CN9_D2 	PC13
#define HEADER_CONNECTOR_CN9_D3 	PC14
#define HEADER_CONNECTOR_CN9_D4 	PC15
#define HEADER_CONNECTOR_CN9_D5 	PF0
#define HEADER_CONNECTOR_CN9_D6 	PF1
#define HEADER_CONNECTOR_CN9_D7 	PG10
#define HEADER_CONNECTOR_CN9_D8 	PC0
#define HEADER_CONNECTOR_CN9_D9 	PC1
#define HEADER_CONNECTOR_CN9_D10	PC2
#define HEADER_CONNECTOR_CN9_D11	PC3
#define HEADER_CONNECTOR_CN9_D12	PA0
#define HEADER_CONNECTOR_CN9_D13	PA1
#define HEADER_CONNECTOR_CN9_D14	PA2
#define HEADER_CONNECTOR_CN9_D15	// Pin not routed
#define HEADER_CONNECTOR_CN9_D16	// Pin not routed
#define HEADER_CONNECTOR_CN9_D17	PA3
#define HEADER_CONNECTOR_CN9_D18	PA4
#define HEADER_CONNECTOR_CN9_D19	PA5
#define HEADER_CONNECTOR_CN9_D20	PA6
#define HEADER_CONNECTOR_CN9_D21	PA7
#define HEADER_CONNECTOR_CN9_D22	PC4
#define HEADER_CONNECTOR_CN9_D23	PB2
#define HEADER_CONNECTOR_CN9_D24	PB0
#define HEADER_CONNECTOR_CN9_D25	PB1
#define HEADER_CONNECTOR_CN9_D26	PB10
#define HEADER_CONNECTOR_CN9_D27	// Pin not routed
#define HEADER_CONNECTOR_CN9_D28	// Pin not routed
#define HEADER_CONNECTOR_CN9_D29	// Pin not routed
#define HEADER_CONNECTOR_CN9_D30	PC5
#define HEADER_CONNECTOR_CN9_D31	// Pin not routed
#define HEADER_CONNECTOR_CN9_D32	// Pin not routed
#define HEADER_CONNECTOR_CN9_D33	PB11
#define HEADER_CONNECTOR_CN9_D34	PB12
#define HEADER_CONNECTOR_CN9_D35	PB13
#define HEADER_CONNECTOR_CN9_D36	PB14
#define HEADER_CONNECTOR_CN9_D37	PB15
#define HEADER_CONNECTOR_CN9_D38	PC6
#define HEADER_CONNECTOR_CN9_D39	PC7
#define HEADER_CONNECTOR_CN9_D40	PC8
#define HEADER_CONNECTOR_CN9_D41	PC9
#define HEADER_CONNECTOR_CN9_D42	PA8
#define HEADER_CONNECTOR_CN9_D43	PA9
#define HEADER_CONNECTOR_CN9_D44	PA10
#define HEADER_CONNECTOR_CN9_D45	PA11
#define HEADER_CONNECTOR_CN9_D46	PA12
#define HEADER_CONNECTOR_CN9_D47	// Pin not routed
#define HEADER_CONNECTOR_CN9_D48	// Pin not routed
#define HEADER_CONNECTOR_CN9_D49	PA13
#define HEADER_CONNECTOR_CN9_D50	PA14
#define HEADER_CONNECTOR_CN9_D51	PA15
#define HEADER_CONNECTOR_CN9_D52	PC10
#define HEADER_CONNECTOR_CN9_D53	PC11
#define HEADER_CONNECTOR_CN9_D54	PC12
#define HEADER_CONNECTOR_CN9_D55	PD2
#define HEADER_CONNECTOR_CN9_D56	PB3
#define HEADER_CONNECTOR_CN9_D57	PB4
#define HEADER_CONNECTOR_CN9_D58	PB5
#define HEADER_CONNECTOR_CN9_D59	PB6
#define HEADER_CONNECTOR_CN9_D60	PB7
#define HEADER_CONNECTOR_CN9_D61	PB8
#define HEADER_CONNECTOR_CN9_D62	PB9
#define HEADER_CONNECTOR_CN9_D63	// Pin not routed
#define HEADER_CONNECTOR_CN9_D64	// Pin not routed

#ifdef __cplusplus
}
#endif

#endif    // _BOARD_H_
// ------------------------------------------------------------------------- END
