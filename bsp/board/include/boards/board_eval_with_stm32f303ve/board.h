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

#define BOARD_NAME "STM32F303VE-Eval"

#include "hal_target.h"

// Mapping
#define HEADER_CONNECTOR_CN2_D1  	// Pin not routed
#define HEADER_CONNECTOR_CN2_D2  	// Pin not routed
#define HEADER_CONNECTOR_CN2_D3  	// Pin not routed
#define HEADER_CONNECTOR_CN2_D4  	// Pin not routed
#define HEADER_CONNECTOR_CN2_D5  	// Pin not routed
#define HEADER_CONNECTOR_CN2_D6  	// Pin not routed
#define HEADER_CONNECTOR_CN2_D7  	// Pin not routed
#define HEADER_CONNECTOR_CN2_D8  	// Pin not routed
#define HEADER_CONNECTOR_CN2_D9  	// Pin not routed
#define HEADER_CONNECTOR_CN2_D10 	// Pin not routed
#define HEADER_CONNECTOR_CN2_D11 	// Pin not routed
#define HEADER_CONNECTOR_CN2_D12 	// Pin not routed
#define HEADER_CONNECTOR_CN2_D13 	// Pin not routed
#define HEADER_CONNECTOR_CN2_D14 	// Pin not routed
#define HEADER_CONNECTOR_CN2_D15 	// Pin not routed
#define HEADER_CONNECTOR_CN2_D16 	// Pin not routed
#define HEADER_CONNECTOR_CN2_D17 	// Pin not routed
#define HEADER_CONNECTOR_CN2_D18 	// Pin not routed
#define HEADER_CONNECTOR_CN2_D19 	// Pin not routed
#define HEADER_CONNECTOR_CN2_D20 	// Pin not routed
#define HEADER_CONNECTOR_CN2_D21 	PE12
#define HEADER_CONNECTOR_CN2_D22 	// Pin not routed
#define HEADER_CONNECTOR_CN2_D23 	// Pin not routed
#define HEADER_CONNECTOR_CN2_D24 	// Pin not routed
#define HEADER_CONNECTOR_CN2_D25 	PD4
#define HEADER_CONNECTOR_CN2_D26 	PD3

#define HEADER_CONNECTOR_CN4_D1  	// Pin not routed
#define HEADER_CONNECTOR_CN4_D2  	// Pin not routed
#define HEADER_CONNECTOR_CN4_D3  	PC7
#define HEADER_CONNECTOR_CN4_D4  	// Pin not routed
#define HEADER_CONNECTOR_CN4_D5  	// Pin not routed
#define HEADER_CONNECTOR_CN4_D6  	// Pin not routed
#define HEADER_CONNECTOR_CN4_D7  	// Pin not routed
#define HEADER_CONNECTOR_CN4_D8  	// Pin not routed
#define HEADER_CONNECTOR_CN4_D9  	// Pin not routed
#define HEADER_CONNECTOR_CN4_D10 	// Pin not routed
#define HEADER_CONNECTOR_CN4_D11 	// Pin not routed
#define HEADER_CONNECTOR_CN4_D12 	// Pin not routed
#define HEADER_CONNECTOR_CN4_D13 	// Pin not routed
#define HEADER_CONNECTOR_CN4_D14 	// Pin not routed
#define HEADER_CONNECTOR_CN4_D15 	// Pin not routed
#define HEADER_CONNECTOR_CN4_D16 	// Pin not routed
#define HEADER_CONNECTOR_CN4_D17 	// Pin not routed
#define HEADER_CONNECTOR_CN4_D18 	// Pin not routed
#define HEADER_CONNECTOR_CN4_D19 	// Pin not routed
#define HEADER_CONNECTOR_CN4_D20 	// Pin not routed
#define HEADER_CONNECTOR_CN4_D21 	// Pin not routed
#define HEADER_CONNECTOR_CN4_D22 	// Pin not routed
#define HEADER_CONNECTOR_CN4_D23 	// Pin not routed
#define HEADER_CONNECTOR_CN4_D24 	// Pin not routed
#define HEADER_CONNECTOR_CN4_D25 	// Pin not routed
#define HEADER_CONNECTOR_CN4_D26 	// Pin not routed
#define HEADER_CONNECTOR_CN4_D27 	// Pin not routed
#define HEADER_CONNECTOR_CN4_D28 	// Pin not routed
#define HEADER_CONNECTOR_CN4_D29 	// Pin not routed
#define HEADER_CONNECTOR_CN4_D30 	// Pin not routed
#define HEADER_CONNECTOR_CN4_D31 	// Pin not routed
#define HEADER_CONNECTOR_CN4_D32 	// Pin not routed
#define HEADER_CONNECTOR_CN4_D33 	PB6
#define HEADER_CONNECTOR_CN4_D34 	// Pin not routed
#define HEADER_CONNECTOR_CN4_D35 	// Pin not routed
#define HEADER_CONNECTOR_CN4_D36 	// Pin not routed
#define HEADER_CONNECTOR_CN4_D37 	// Pin not routed
#define HEADER_CONNECTOR_CN4_D38 	// Pin not routed
#define HEADER_CONNECTOR_CN4_D39 	// Pin not routed
#define HEADER_CONNECTOR_CN4_D40 	// Pin not routed
#define HEADER_CONNECTOR_CN4_D41 	// Pin not routed
#define HEADER_CONNECTOR_CN4_D42 	// Pin not routed
#define HEADER_CONNECTOR_CN4_D43 	// Pin not routed
#define HEADER_CONNECTOR_CN4_D44 	// Pin not routed
#define HEADER_CONNECTOR_CN4_D45 	// Pin not routed
#define HEADER_CONNECTOR_CN4_D46 	// Pin not routed
#define HEADER_CONNECTOR_CN4_D47 	PF10

#define HEADER_CONNECTOR_CN9,_D1 	// Pin not routed
#define HEADER_CONNECTOR_CN9,_D2 	// Pin not routed
#define HEADER_CONNECTOR_CN9,_D3 	// Pin not routed
#define HEADER_CONNECTOR_CN9,_D4 	// Pin not routed
#define HEADER_CONNECTOR_CN9,_D5 	// Pin not routed
#define HEADER_CONNECTOR_CN9,_D6 	// Pin not routed
#define HEADER_CONNECTOR_CN9,_D7 	// Pin not routed
#define HEADER_CONNECTOR_CN9,_D8 	// Pin not routed
#define HEADER_CONNECTOR_CN9,_D9 	// Pin not routed
#define HEADER_CONNECTOR_CN9,_D10	// Pin not routed
#define HEADER_CONNECTOR_CN9,_D11	// Pin not routed
#define HEADER_CONNECTOR_CN9,_D12	// Pin not routed
#define HEADER_CONNECTOR_CN9,_D13	PA13
#define HEADER_CONNECTOR_CN9,_D14	// Pin not routed
#define HEADER_CONNECTOR_CN9,_D15	// Pin not routed
#define HEADER_CONNECTOR_CN9,_D16	PA14
#define HEADER_CONNECTOR_CN9,_D17	PA15
#define HEADER_CONNECTOR_CN9,_D18	// Pin not routed
#define HEADER_CONNECTOR_CN9,_D19	// Pin not routed
#define HEADER_CONNECTOR_CN9,_D20	// Pin not routed
#define HEADER_CONNECTOR_CN9,_D21	// Pin not routed
#define HEADER_CONNECTOR_CN9,_D22	// Pin not routed
#define HEADER_CONNECTOR_CN9,_D23	// Pin not routed
#define HEADER_CONNECTOR_CN9,_D24	// Pin not routed
#define HEADER_CONNECTOR_CN9,_D25	// Pin not routed
#define HEADER_CONNECTOR_CN9,_D26	// Pin not routed
#define HEADER_CONNECTOR_CN9,_D27	// Pin not routed
#define HEADER_CONNECTOR_CN9,_D28	// Pin not routed
#define HEADER_CONNECTOR_CN9,_D29	// Pin not routed
#define HEADER_CONNECTOR_CN9,_D30	// Pin not routed
#define HEADER_CONNECTOR_CN9,_D31	PB4
#define HEADER_CONNECTOR_CN9,_D32	PB3

#define HEADER_CONNECTOR_CN9_D1  	// Pin not routed
#define HEADER_CONNECTOR_CN9_D2  	// Pin not routed
#define HEADER_CONNECTOR_CN9_D3  	// Pin not routed
#define HEADER_CONNECTOR_CN9_D4  	// Pin not routed
#define HEADER_CONNECTOR_CN9_D5  	// Pin not routed
#define HEADER_CONNECTOR_CN9_D6  	// Pin not routed
#define HEADER_CONNECTOR_CN9_D7  	// Pin not routed
#define HEADER_CONNECTOR_CN9_D8  	// Pin not routed
#define HEADER_CONNECTOR_CN9_D9  	// Pin not routed
#define HEADER_CONNECTOR_CN9_D10 	// Pin not routed
#define HEADER_CONNECTOR_CN9_D11 	// Pin not routed
#define HEADER_CONNECTOR_CN9_D12 	// Pin not routed
#define HEADER_CONNECTOR_CN9_D13 	// Pin not routed
#define HEADER_CONNECTOR_CN9_D14 	// Pin not routed
#define HEADER_CONNECTOR_CN9_D15 	// Pin not routed
#define HEADER_CONNECTOR_CN9_D16 	// Pin not routed
#define HEADER_CONNECTOR_CN9_D17 	// Pin not routed
#define HEADER_CONNECTOR_CN9_D18 	// Pin not routed
#define HEADER_CONNECTOR_CN9_D19 	// Pin not routed
#define HEADER_CONNECTOR_CN9_D20 	// Pin not routed
#define HEADER_CONNECTOR_CN9_D21 	// Pin not routed
#define HEADER_CONNECTOR_CN9_D22 	// Pin not routed
#define HEADER_CONNECTOR_CN9_D23 	// Pin not routed
#define HEADER_CONNECTOR_CN9_D24 	// Pin not routed
#define HEADER_CONNECTOR_CN9_D25 	// Pin not routed
#define HEADER_CONNECTOR_CN9_D26 	// Pin not routed
#define HEADER_CONNECTOR_CN9_D27 	// Pin not routed
#define HEADER_CONNECTOR_CN9_D28 	// Pin not routed
#define HEADER_CONNECTOR_CN9_D29 	// Pin not routed
#define HEADER_CONNECTOR_CN9_D30 	// Pin not routed
#define HEADER_CONNECTOR_CN9_D31 	// Pin not routed
#define HEADER_CONNECTOR_CN9_D32 	// Pin not routed
#define HEADER_CONNECTOR_CN9_D33 	// Pin not routed
#define HEADER_CONNECTOR_CN9_D34 	// Pin not routed
#define HEADER_CONNECTOR_CN9_D35 	// Pin not routed
#define HEADER_CONNECTOR_CN9_D36 	// Pin not routed
#define HEADER_CONNECTOR_CN9_D37 	// Pin not routed
#define HEADER_CONNECTOR_CN9_D38 	// Pin not routed
#define HEADER_CONNECTOR_CN9_D39 	// Pin not routed
#define HEADER_CONNECTOR_CN9_D40 	// Pin not routed
#define HEADER_CONNECTOR_CN9_D41 	// Pin not routed
#define HEADER_CONNECTOR_CN9_D42 	// Pin not routed
#define HEADER_CONNECTOR_CN9_D43 	// Pin not routed
#define HEADER_CONNECTOR_CN9_D44 	// Pin not routed
#define HEADER_CONNECTOR_CN9_D45 	// Pin not routed
#define HEADER_CONNECTOR_CN9_D46 	PE6

#ifdef __cplusplus
}
#endif

#endif    // _BOARD_H_
// ------------------------------------------------------------------------- END
