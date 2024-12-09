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

#define BOARD_NAME "STM32H753XI-Eval"

#include "hal_target.h"

// Mapping
#define HEADER_CONNECTOR_CN2_D1  	// Pin not routed
#define HEADER_CONNECTOR_CN2_D2  	PB15
#define HEADER_CONNECTOR_CN2_D3  	PB14
#define HEADER_CONNECTOR_CN2_D4  	// Pin not routed
#define HEADER_CONNECTOR_CN2_D5  	// Pin not routed
#define HEADER_CONNECTOR_CN2_D6  	// Pin not routed
#define HEADER_CONNECTOR_CN2_D7  	// Pin not routed
#define HEADER_CONNECTOR_CN2_D8  	// Pin not routed
#define HEADER_CONNECTOR_CN2_D9  	// Pin not routed

#define HEADER_CONNECTOR_CN4_D1  	PB7
#define HEADER_CONNECTOR_CN4_D2  	// Pin not routed
#define HEADER_CONNECTOR_CN4_D3  	PB6
#define HEADER_CONNECTOR_CN4_D4  	PA4
#define HEADER_CONNECTOR_CN4_D5  	// Pin not routed
#define HEADER_CONNECTOR_CN4_D6  	// Pin not routed
#define HEADER_CONNECTOR_CN4_D7  	// Pin not routed
#define HEADER_CONNECTOR_CN4_D8  	// Pin not routed

#define HEADER_CONNECTOR_CN6_D1  	PC0
#define HEADER_CONNECTOR_CN6_D2  	// Pin not routed
#define HEADER_CONNECTOR_CN6_D3  	PH0
#define HEADER_CONNECTOR_CN6_D4  	// Pin not routed
#define HEADER_CONNECTOR_CN6_D5  	// Pin not routed
#define HEADER_CONNECTOR_CN6_D6  	// Pin not routed
#define HEADER_CONNECTOR_CN6_D7  	PI11
#define HEADER_CONNECTOR_CN6_D8  	// Pin not routed
#define HEADER_CONNECTOR_CN6_D9  	PB5
#define HEADER_CONNECTOR_CN6_D10 	// Pin not routed
#define HEADER_CONNECTOR_CN6_D11 	PF8
#define HEADER_CONNECTOR_CN6_D12 	// Pin not routed
#define HEADER_CONNECTOR_CN6_D13 	PG14
#define HEADER_CONNECTOR_CN6_D14 	// Pin not routed
#define HEADER_CONNECTOR_CN6_D15 	PH3
#define HEADER_CONNECTOR_CN6_D16 	// Pin not routed
#define HEADER_CONNECTOR_CN6_D17 	PH2
#define HEADER_CONNECTOR_CN6_D18 	// Pin not routed
#define HEADER_CONNECTOR_CN6_D19 	PA4
#define HEADER_CONNECTOR_CN6_D20 	// Pin not routed
#define HEADER_CONNECTOR_CN6_D21 	PA3
#define HEADER_CONNECTOR_CN6_D22 	// Pin not routed
#define HEADER_CONNECTOR_CN6_D23 	PF9
#define HEADER_CONNECTOR_CN6_D24 	// Pin not routed
#define HEADER_CONNECTOR_CN6_D25 	PA6
#define HEADER_CONNECTOR_CN6_D26 	// Pin not routed
#define HEADER_CONNECTOR_CN6_D27 	PC4
#define HEADER_CONNECTOR_CN6_D28 	// Pin not routed
#define HEADER_CONNECTOR_CN6_D29 	PB0
#define HEADER_CONNECTOR_CN6_D30 	// Pin not routed
#define HEADER_CONNECTOR_CN6_D31 	PB1
#define HEADER_CONNECTOR_CN6_D32 	// Pin not routed
#define HEADER_CONNECTOR_CN6_D33 	PJ3
#define HEADER_CONNECTOR_CN6_D34 	// Pin not routed
#define HEADER_CONNECTOR_CN6_D35 	PA1
#define HEADER_CONNECTOR_CN6_D36 	// Pin not routed
#define HEADER_CONNECTOR_CN6_D37 	PC3
#define HEADER_CONNECTOR_CN6_D38 	// Pin not routed
#define HEADER_CONNECTOR_CN6_D39 	// Pin not routed
#define HEADER_CONNECTOR_CN6_D40 	// Pin not routed
#define HEADER_CONNECTOR_CN6_D41 	PJ1
#define HEADER_CONNECTOR_CN6_D42 	// Pin not routed
#define HEADER_CONNECTOR_CN6_D43 	PJ0
#define HEADER_CONNECTOR_CN6_D44 	// Pin not routed
#define HEADER_CONNECTOR_CN6_D45 	PB14
#define HEADER_CONNECTOR_CN6_D46 	// Pin not routed
#define HEADER_CONNECTOR_CN6_D47 	PB15
#define HEADER_CONNECTOR_CN6_D48 	// Pin not routed
#define HEADER_CONNECTOR_CN6_D49 	// Pin not routed
#define HEADER_CONNECTOR_CN6_D50 	// Pin not routed
#define HEADER_CONNECTOR_CN6_D51 	PB11
#define HEADER_CONNECTOR_CN6_D52 	// Pin not routed
#define HEADER_CONNECTOR_CN6_D53 	PJ7

#define HEADER_CONNECTOR_CN9_D1  	// Pin not routed
#define HEADER_CONNECTOR_CN9_D2  	// Pin not routed
#define HEADER_CONNECTOR_CN9_D3  	PB4
#define HEADER_CONNECTOR_CN9_D4  	// Pin not routed
#define HEADER_CONNECTOR_CN9_D5  	PA15
#define HEADER_CONNECTOR_CN9_D6  	// Pin not routed
#define HEADER_CONNECTOR_CN9_D7  	PA13
#define HEADER_CONNECTOR_CN9_D8  	// Pin not routed
#define HEADER_CONNECTOR_CN9_D9  	PA14
#define HEADER_CONNECTOR_CN9_D10 	// Pin not routed
#define HEADER_CONNECTOR_CN9_D11 	// Pin not routed
#define HEADER_CONNECTOR_CN9_D12 	// Pin not routed
#define HEADER_CONNECTOR_CN9_D13 	PB3
#define HEADER_CONNECTOR_CN9_D14 	// Pin not routed
#define HEADER_CONNECTOR_CN9_D15 	// Pin not routed
#define HEADER_CONNECTOR_CN9_D16 	// Pin not routed
#define HEADER_CONNECTOR_CN9_D17 	PJ7
#define HEADER_CONNECTOR_CN9_D18 	// Pin not routed
#define HEADER_CONNECTOR_CN9_D19 	PJ12
#define HEADER_CONNECTOR_CN9_D20 	// Pin not routed

#define HEADER_CONNECTOR_CN11_D1 	PH6
#define HEADER_CONNECTOR_CN11_D2 	// Pin not routed
#define HEADER_CONNECTOR_CN11_D3 	PF13
#define HEADER_CONNECTOR_CN11_D4 	// Pin not routed
#define HEADER_CONNECTOR_CN11_D5 	PF12
#define HEADER_CONNECTOR_CN11_D6 	// Pin not routed
#define HEADER_CONNECTOR_CN11_D7 	PG1
#define HEADER_CONNECTOR_CN11_D8 	// Pin not routed
#define HEADER_CONNECTOR_CN11_D9 	// Pin not routed
#define HEADER_CONNECTOR_CN11_D10	// Pin not routed
#define HEADER_CONNECTOR_CN11_D11	PE7
#define HEADER_CONNECTOR_CN11_D12	// Pin not routed
#define HEADER_CONNECTOR_CN11_D13	PE10
#define HEADER_CONNECTOR_CN11_D14	// Pin not routed
#define HEADER_CONNECTOR_CN11_D15	PE12
#define HEADER_CONNECTOR_CN11_D16	// Pin not routed
#define HEADER_CONNECTOR_CN11_D17	PE15
#define HEADER_CONNECTOR_CN11_D18	// Pin not routed
#define HEADER_CONNECTOR_CN11_D19	PE13
#define HEADER_CONNECTOR_CN11_D20	// Pin not routed
#define HEADER_CONNECTOR_CN11_D21	PD11
#define HEADER_CONNECTOR_CN11_D22	// Pin not routed
#define HEADER_CONNECTOR_CN11_D23	PD12
#define HEADER_CONNECTOR_CN11_D24	// Pin not routed
#define HEADER_CONNECTOR_CN11_D25	PG5
#define HEADER_CONNECTOR_CN11_D26	// Pin not routed
#define HEADER_CONNECTOR_CN11_D27	PH11
#define HEADER_CONNECTOR_CN11_D28	// Pin not routed
#define HEADER_CONNECTOR_CN11_D29	// Pin not routed
#define HEADER_CONNECTOR_CN11_D30	// Pin not routed
#define HEADER_CONNECTOR_CN11_D31	PD13
#define HEADER_CONNECTOR_CN11_D32	// Pin not routed
#define HEADER_CONNECTOR_CN11_D33	PG2
#define HEADER_CONNECTOR_CN11_D34	// Pin not routed
#define HEADER_CONNECTOR_CN11_D35	PD8

#define HEADER_CONNECTOR_CN12_D1 	PF5
#define HEADER_CONNECTOR_CN12_D2 	// Pin not routed
#define HEADER_CONNECTOR_CN12_D3 	PF4
#define HEADER_CONNECTOR_CN12_D4 	// Pin not routed
#define HEADER_CONNECTOR_CN12_D5 	PF3
#define HEADER_CONNECTOR_CN12_D6 	// Pin not routed
#define HEADER_CONNECTOR_CN12_D7 	PE6
#define HEADER_CONNECTOR_CN12_D8 	// Pin not routed
#define HEADER_CONNECTOR_CN12_D9 	// Pin not routed
#define HEADER_CONNECTOR_CN12_D10	// Pin not routed
#define HEADER_CONNECTOR_CN12_D11	PE4
#define HEADER_CONNECTOR_CN12_D12	// Pin not routed
#define HEADER_CONNECTOR_CN12_D13	PE3
#define HEADER_CONNECTOR_CN12_D14	// Pin not routed
#define HEADER_CONNECTOR_CN12_D15	PI5
#define HEADER_CONNECTOR_CN12_D16	// Pin not routed
#define HEADER_CONNECTOR_CN12_D17	PI4
#define HEADER_CONNECTOR_CN12_D18	// Pin not routed
#define HEADER_CONNECTOR_CN12_D19	PG15
#define HEADER_CONNECTOR_CN12_D20	// Pin not routed
#define HEADER_CONNECTOR_CN12_D21	PI10
#define HEADER_CONNECTOR_CN12_D22	// Pin not routed
#define HEADER_CONNECTOR_CN12_D23	PE1
#define HEADER_CONNECTOR_CN12_D24	// Pin not routed
#define HEADER_CONNECTOR_CN12_D25	PE0
#define HEADER_CONNECTOR_CN12_D26	// Pin not routed
#define HEADER_CONNECTOR_CN12_D27	PG10

#ifdef __cplusplus
}
#endif

#endif    // _BOARD_H_
// ------------------------------------------------------------------------- END
