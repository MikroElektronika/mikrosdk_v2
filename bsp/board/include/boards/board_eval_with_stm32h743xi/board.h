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

#define BOARD_NAME "STM32H743XI-Eval"

#include "hal_target.h"

// Mapping
#define HEADER_CONNECTOR_CN4,_D1  	// Pin not routed
#define HEADER_CONNECTOR_CN4,_D2  	// Pin not routed
#define HEADER_CONNECTOR_CN4,_D3  	// Pin not routed
#define HEADER_CONNECTOR_CN4,_D4  	// Pin not routed
#define HEADER_CONNECTOR_CN4,_D5  	// Pin not routed
#define HEADER_CONNECTOR_CN4,_D6  	// Pin not routed
#define HEADER_CONNECTOR_CN4,_D7  	// Pin not routed
#define HEADER_CONNECTOR_CN4,_D8  	// Pin not routed
#define HEADER_CONNECTOR_CN4,_D9  	// Pin not routed
#define HEADER_CONNECTOR_CN4,_D10 	// Pin not routed
#define HEADER_CONNECTOR_CN4,_D11 	// Pin not routed
#define HEADER_CONNECTOR_CN4,_D12 	// Pin not routed
#define HEADER_CONNECTOR_CN4,_D13 	// Pin not routed
#define HEADER_CONNECTOR_CN4,_D14 	// Pin not routed
#define HEADER_CONNECTOR_CN4,_D15 	// Pin not routed
#define HEADER_CONNECTOR_CN4,_D16 	PB7
#define HEADER_CONNECTOR_CN4,_D17 	// Pin not routed
#define HEADER_CONNECTOR_CN4,_D18 	PB6
#define HEADER_CONNECTOR_CN4,_D19 	PA4

#define HEADER_CONNECTOR_CN15_D1  	// Pin not routed
#define HEADER_CONNECTOR_CN15_D2  	// Pin not routed
#define HEADER_CONNECTOR_CN15_D3  	// Pin not routed
#define HEADER_CONNECTOR_CN15_D4  	// Pin not routed
#define HEADER_CONNECTOR_CN15_D5  	// Pin not routed
#define HEADER_CONNECTOR_CN15_D6  	// Pin not routed
#define HEADER_CONNECTOR_CN15_D7  	// Pin not routed
#define HEADER_CONNECTOR_CN15_D8  	// Pin not routed
#define HEADER_CONNECTOR_CN15_D9  	// Pin not routed
#define HEADER_CONNECTOR_CN15_D10 	// Pin not routed
#define HEADER_CONNECTOR_CN15_D11 	// Pin not routed
#define HEADER_CONNECTOR_CN15_D12 	// Pin not routed
#define HEADER_CONNECTOR_CN15_D13 	// Pin not routed
#define HEADER_CONNECTOR_CN15_D14 	// Pin not routed
#define HEADER_CONNECTOR_CN15_D15 	// Pin not routed
#define HEADER_CONNECTOR_CN15_D16 	// Pin not routed
#define HEADER_CONNECTOR_CN15_D17 	// Pin not routed
#define HEADER_CONNECTOR_CN15_D18 	// Pin not routed
#define HEADER_CONNECTOR_CN15_D19 	// Pin not routed
#define HEADER_CONNECTOR_CN15_D20 	// Pin not routed
#define HEADER_CONNECTOR_CN15_D21 	// Pin not routed
#define HEADER_CONNECTOR_CN15_D22 	// Pin not routed
#define HEADER_CONNECTOR_CN15_D23 	// Pin not routed
#define HEADER_CONNECTOR_CN15_D24 	// Pin not routed
#define HEADER_CONNECTOR_CN15_D25 	PA6
#define HEADER_CONNECTOR_CN15_D26 	// Pin not routed
#define HEADER_CONNECTOR_CN15_D27 	// Pin not routed
#define HEADER_CONNECTOR_CN15_D28 	// Pin not routed
#define HEADER_CONNECTOR_CN15_D29 	// Pin not routed
#define HEADER_CONNECTOR_CN15_D30 	// Pin not routed
#define HEADER_CONNECTOR_CN15_D31 	// Pin not routed
#define HEADER_CONNECTOR_CN15_D32 	// Pin not routed
#define HEADER_CONNECTOR_CN15_D33 	// Pin not routed
#define HEADER_CONNECTOR_CN15_D34 	// Pin not routed
#define HEADER_CONNECTOR_CN15_D35 	PA15
#define HEADER_CONNECTOR_CN15_D36 	// Pin not routed
#define HEADER_CONNECTOR_CN15_D37 	// Pin not routed
#define HEADER_CONNECTOR_CN15_D38 	// Pin not routed
#define HEADER_CONNECTOR_CN15_D39 	// Pin not routed
#define HEADER_CONNECTOR_CN15_D40 	// Pin not routed
#define HEADER_CONNECTOR_CN15_D41 	// Pin not routed
#define HEADER_CONNECTOR_CN15_D42 	// Pin not routed
#define HEADER_CONNECTOR_CN15_D43 	// Pin not routed
#define HEADER_CONNECTOR_CN15_D44 	// Pin not routed
#define HEADER_CONNECTOR_CN15_D45 	// Pin not routed
#define HEADER_CONNECTOR_CN15_D46 	// Pin not routed
#define HEADER_CONNECTOR_CN15_D47 	// Pin not routed
#define HEADER_CONNECTOR_CN15_D48 	// Pin not routed
#define HEADER_CONNECTOR_CN15_D49 	// Pin not routed
#define HEADER_CONNECTOR_CN15_D50 	// Pin not routed
#define HEADER_CONNECTOR_CN15_D51 	// Pin not routed
#define HEADER_CONNECTOR_CN15_D52 	PA8

#define HEADER_CONNECTOR_CN15,_D1 	PF10
#define HEADER_CONNECTOR_CN15,_D2 	// Pin not routed
#define HEADER_CONNECTOR_CN15,_D3 	// Pin not routed
#define HEADER_CONNECTOR_CN15,_D4 	// Pin not routed
#define HEADER_CONNECTOR_CN15,_D5 	// Pin not routed
#define HEADER_CONNECTOR_CN15,_D6 	// Pin not routed
#define HEADER_CONNECTOR_CN15,_D7 	// Pin not routed
#define HEADER_CONNECTOR_CN15,_D8 	// Pin not routed
#define HEADER_CONNECTOR_CN15,_D9 	// Pin not routed
#define HEADER_CONNECTOR_CN15,_D10	// Pin not routed
#define HEADER_CONNECTOR_CN15,_D11	// Pin not routed
#define HEADER_CONNECTOR_CN15,_D12	// Pin not routed
#define HEADER_CONNECTOR_CN15,_D13	// Pin not routed
#define HEADER_CONNECTOR_CN15,_D14	// Pin not routed
#define HEADER_CONNECTOR_CN15,_D15	// Pin not routed
#define HEADER_CONNECTOR_CN15,_D16	// Pin not routed
#define HEADER_CONNECTOR_CN15,_D17	// Pin not routed
#define HEADER_CONNECTOR_CN15,_D18	// Pin not routed
#define HEADER_CONNECTOR_CN15,_D19	// Pin not routed
#define HEADER_CONNECTOR_CN15,_D20	// Pin not routed
#define HEADER_CONNECTOR_CN15,_D21	// Pin not routed
#define HEADER_CONNECTOR_CN15,_D22	// Pin not routed
#define HEADER_CONNECTOR_CN15,_D23	// Pin not routed
#define HEADER_CONNECTOR_CN15,_D24	// Pin not routed
#define HEADER_CONNECTOR_CN15,_D25	// Pin not routed
#define HEADER_CONNECTOR_CN15,_D26	// Pin not routed
#define HEADER_CONNECTOR_CN15,_D27	// Pin not routed
#define HEADER_CONNECTOR_CN15,_D28	// Pin not routed
#define HEADER_CONNECTOR_CN15,_D29	// Pin not routed
#define HEADER_CONNECTOR_CN15,_D30	// Pin not routed
#define HEADER_CONNECTOR_CN15,_D31	// Pin not routed
#define HEADER_CONNECTOR_CN15,_D32	// Pin not routed
#define HEADER_CONNECTOR_CN15,_D33	// Pin not routed
#define HEADER_CONNECTOR_CN15,_D34	// Pin not routed
#define HEADER_CONNECTOR_CN15,_D35	// Pin not routed
#define HEADER_CONNECTOR_CN15,_D36	// Pin not routed
#define HEADER_CONNECTOR_CN15,_D37	// Pin not routed
#define HEADER_CONNECTOR_CN15,_D38	// Pin not routed
#define HEADER_CONNECTOR_CN15,_D39	// Pin not routed
#define HEADER_CONNECTOR_CN15,_D40	PJ2
#define HEADER_CONNECTOR_CN15,_D41	// Pin not routed
#define HEADER_CONNECTOR_CN15,_D42	// Pin not routed
#define HEADER_CONNECTOR_CN15,_D43	// Pin not routed
#define HEADER_CONNECTOR_CN15,_D44	// Pin not routed
#define HEADER_CONNECTOR_CN15,_D45	// Pin not routed
#define HEADER_CONNECTOR_CN15,_D46	// Pin not routed
#define HEADER_CONNECTOR_CN15,_D47	// Pin not routed
#define HEADER_CONNECTOR_CN15,_D48	// Pin not routed
#define HEADER_CONNECTOR_CN15,_D49	// Pin not routed
#define HEADER_CONNECTOR_CN15,_D50	// Pin not routed
#define HEADER_CONNECTOR_CN15,_D51	// Pin not routed
#define HEADER_CONNECTOR_CN15,_D52	PA8

#define HEADER_CONNECTOR_CN18_D1  	// Pin not routed
#define HEADER_CONNECTOR_CN18_D2  	// Pin not routed
#define HEADER_CONNECTOR_CN18_D3  	// Pin not routed
#define HEADER_CONNECTOR_CN18_D4  	// Pin not routed
#define HEADER_CONNECTOR_CN18_D5  	// Pin not routed
#define HEADER_CONNECTOR_CN18_D6  	// Pin not routed
#define HEADER_CONNECTOR_CN18_D7  	// Pin not routed
#define HEADER_CONNECTOR_CN18_D8  	// Pin not routed
#define HEADER_CONNECTOR_CN18_D9  	// Pin not routed
#define HEADER_CONNECTOR_CN18_D10 	// Pin not routed
#define HEADER_CONNECTOR_CN18_D11 	// Pin not routed
#define HEADER_CONNECTOR_CN18_D12 	// Pin not routed
#define HEADER_CONNECTOR_CN18_D13 	// Pin not routed
#define HEADER_CONNECTOR_CN18_D14 	// Pin not routed
#define HEADER_CONNECTOR_CN18_D15 	// Pin not routed
#define HEADER_CONNECTOR_CN18_D16 	// Pin not routed
#define HEADER_CONNECTOR_CN18_D17 	// Pin not routed
#define HEADER_CONNECTOR_CN18_D18 	// Pin not routed
#define HEADER_CONNECTOR_CN18_D19 	// Pin not routed
#define HEADER_CONNECTOR_CN18_D20 	// Pin not routed
#define HEADER_CONNECTOR_CN18_D21 	// Pin not routed
#define HEADER_CONNECTOR_CN18_D22 	// Pin not routed
#define HEADER_CONNECTOR_CN18_D23 	// Pin not routed
#define HEADER_CONNECTOR_CN18_D24 	// Pin not routed
#define HEADER_CONNECTOR_CN18_D25 	// Pin not routed
#define HEADER_CONNECTOR_CN18_D26 	// Pin not routed
#define HEADER_CONNECTOR_CN18_D27 	// Pin not routed
#define HEADER_CONNECTOR_CN18_D28 	// Pin not routed
#define HEADER_CONNECTOR_CN18_D29 	// Pin not routed
#define HEADER_CONNECTOR_CN18_D30 	// Pin not routed
#define HEADER_CONNECTOR_CN18_D31 	// Pin not routed
#define HEADER_CONNECTOR_CN18_D32 	// Pin not routed
#define HEADER_CONNECTOR_CN18_D33 	// Pin not routed
#define HEADER_CONNECTOR_CN18_D34 	// Pin not routed
#define HEADER_CONNECTOR_CN18_D35 	// Pin not routed
#define HEADER_CONNECTOR_CN18_D36 	// Pin not routed
#define HEADER_CONNECTOR_CN18_D37 	// Pin not routed
#define HEADER_CONNECTOR_CN18_D38 	// Pin not routed
#define HEADER_CONNECTOR_CN18_D39 	// Pin not routed
#define HEADER_CONNECTOR_CN18_D40 	// Pin not routed
#define HEADER_CONNECTOR_CN18_D41 	// Pin not routed
#define HEADER_CONNECTOR_CN18_D42 	// Pin not routed
#define HEADER_CONNECTOR_CN18_D43 	// Pin not routed
#define HEADER_CONNECTOR_CN18_D44 	// Pin not routed
#define HEADER_CONNECTOR_CN18_D45 	// Pin not routed
#define HEADER_CONNECTOR_CN18_D46 	// Pin not routed
#define HEADER_CONNECTOR_CN18_D47 	PA10

#define HEADER_CONNECTOR_CN20_D1  	// Pin not routed
#define HEADER_CONNECTOR_CN20_D2  	// Pin not routed
#define HEADER_CONNECTOR_CN20_D3  	// Pin not routed
#define HEADER_CONNECTOR_CN20_D4  	// Pin not routed
#define HEADER_CONNECTOR_CN20_D5  	PI14
#define HEADER_CONNECTOR_CN20_D6  	PI12
#define HEADER_CONNECTOR_CN20_D7  	PI13
#define HEADER_CONNECTOR_CN20_D8  	// Pin not routed
#define HEADER_CONNECTOR_CN20_D9  	// Pin not routed
#define HEADER_CONNECTOR_CN20_D10 	// Pin not routed
#define HEADER_CONNECTOR_CN20_D11 	// Pin not routed
#define HEADER_CONNECTOR_CN20_D12 	// Pin not routed
#define HEADER_CONNECTOR_CN20_D13 	PK7
#define HEADER_CONNECTOR_CN20_D14 	// Pin not routed
#define HEADER_CONNECTOR_CN20_D15 	// Pin not routed
#define HEADER_CONNECTOR_CN20_D16 	// Pin not routed
#define HEADER_CONNECTOR_CN20_D17 	PK6
#define HEADER_CONNECTOR_CN20_D18 	// Pin not routed
#define HEADER_CONNECTOR_CN20_D19 	// Pin not routed
#define HEADER_CONNECTOR_CN20_D20 	// Pin not routed
#define HEADER_CONNECTOR_CN20_D21 	PK4
#define HEADER_CONNECTOR_CN20_D22 	PK5
#define HEADER_CONNECTOR_CN20_D23 	PK3
#define HEADER_CONNECTOR_CN20_D24 	PJ13
#define HEADER_CONNECTOR_CN20_D25 	// Pin not routed
#define HEADER_CONNECTOR_CN20_D26 	// Pin not routed
#define HEADER_CONNECTOR_CN20_D27 	// Pin not routed
#define HEADER_CONNECTOR_CN20_D28 	PJ14
#define HEADER_CONNECTOR_CN20_D29 	PJ15
#define HEADER_CONNECTOR_CN20_D30 	// Pin not routed
#define HEADER_CONNECTOR_CN20_D31 	PJ11
#define HEADER_CONNECTOR_CN20_D32 	PJ12
#define HEADER_CONNECTOR_CN20_D33 	PJ3
#define HEADER_CONNECTOR_CN20_D34 	// Pin not routed
#define HEADER_CONNECTOR_CN20_D35 	// Pin not routed
#define HEADER_CONNECTOR_CN20_D36 	PJ4
#define HEADER_CONNECTOR_CN20_D37 	// Pin not routed
#define HEADER_CONNECTOR_CN20_D38 	PI15
#define HEADER_CONNECTOR_CN20_D39 	// Pin not routed
#define HEADER_CONNECTOR_CN20_D40 	// Pin not routed
#define HEADER_CONNECTOR_CN20_D41 	PJ1
#define HEADER_CONNECTOR_CN20_D42 	PJ5
#define HEADER_CONNECTOR_CN20_D43 	PJ0
#define HEADER_CONNECTOR_CN20_D44 	// Pin not routed
#define HEADER_CONNECTOR_CN20_D45 	// Pin not routed
#define HEADER_CONNECTOR_CN20_D46 	// Pin not routed
#define HEADER_CONNECTOR_CN20_D47 	// Pin not routed
#define HEADER_CONNECTOR_CN20_D48 	// Pin not routed
#define HEADER_CONNECTOR_CN20_D49 	// Pin not routed
#define HEADER_CONNECTOR_CN20_D50 	// Pin not routed
#define HEADER_CONNECTOR_CN20_D51 	// Pin not routed
#define HEADER_CONNECTOR_CN20_D52 	// Pin not routed
#define HEADER_CONNECTOR_CN20_D53 	PJ7
#define HEADER_CONNECTOR_CN20_D54 	PJ8
#define HEADER_CONNECTOR_CN20_D55 	PK0
#define HEADER_CONNECTOR_CN20_D56 	PJ9
#define HEADER_CONNECTOR_CN20_D57 	PK1
#define HEADER_CONNECTOR_CN20_D58 	PK2

#ifdef __cplusplus
}
#endif

#endif    // _BOARD_H_
// ------------------------------------------------------------------------- END
