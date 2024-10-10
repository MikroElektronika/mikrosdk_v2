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

#define BOARD_NAME "STM32F417IG-Eval"

#include "hal_target.h"

// Mapping
#define HEADER_CONNECTOR_CN5_D1   	// Pin not routed
#define HEADER_CONNECTOR_CN5_D2   	// Pin not routed
#define HEADER_CONNECTOR_CN5_D3   	// Pin not routed
#define HEADER_CONNECTOR_CN5_D4   	// Pin not routed
#define HEADER_CONNECTOR_CN5_D5   	PH15

#define HEADER_CONNECTOR_CN5._D1  	// Pin not routed
#define HEADER_CONNECTOR_CN5._D2  	// Pin not routed
#define HEADER_CONNECTOR_CN5._D3  	// Pin not routed
#define HEADER_CONNECTOR_CN5._D4  	// Pin not routed
#define HEADER_CONNECTOR_CN5._D5  	// Pin not routed
#define HEADER_CONNECTOR_CN5._D6  	// Pin not routed
#define HEADER_CONNECTOR_CN5._D7  	// Pin not routed
#define HEADER_CONNECTOR_CN5._D8  	// Pin not routed
#define HEADER_CONNECTOR_CN5._D9  	PB8
#define HEADER_CONNECTOR_CN5._D10 	// Pin not routed
#define HEADER_CONNECTOR_CN5._D11 	// Pin not routed
#define HEADER_CONNECTOR_CN5._D12 	// Pin not routed
#define HEADER_CONNECTOR_CN5._D13 	// Pin not routed
#define HEADER_CONNECTOR_CN5._D14 	// Pin not routed
#define HEADER_CONNECTOR_CN5._D15 	// Pin not routed
#define HEADER_CONNECTOR_CN5._D16 	// Pin not routed
#define HEADER_CONNECTOR_CN5._D17 	// Pin not routed
#define HEADER_CONNECTOR_CN5._D18 	// Pin not routed
#define HEADER_CONNECTOR_CN5._D19 	// Pin not routed
#define HEADER_CONNECTOR_CN5._D20 	// Pin not routed
#define HEADER_CONNECTOR_CN5._D21 	// Pin not routed
#define HEADER_CONNECTOR_CN5._D22 	// Pin not routed
#define HEADER_CONNECTOR_CN5._D23 	// Pin not routed
#define HEADER_CONNECTOR_CN5._D24 	// Pin not routed
#define HEADER_CONNECTOR_CN5._D25 	// Pin not routed
#define HEADER_CONNECTOR_CN5._D26 	// Pin not routed
#define HEADER_CONNECTOR_CN5._D27 	// Pin not routed
#define HEADER_CONNECTOR_CN5._D28 	// Pin not routed
#define HEADER_CONNECTOR_CN5._D29 	// Pin not routed
#define HEADER_CONNECTOR_CN5._D30 	// Pin not routed
#define HEADER_CONNECTOR_CN5._D31 	// Pin not routed
#define HEADER_CONNECTOR_CN5._D32 	PD13

#define HEADER_CONNECTOR_CN6._D1  	// Pin not routed
#define HEADER_CONNECTOR_CN6._D2  	// Pin not routed
#define HEADER_CONNECTOR_CN6._D3  	// Pin not routed
#define HEADER_CONNECTOR_CN6._D4  	// Pin not routed
#define HEADER_CONNECTOR_CN6._D5  	// Pin not routed
#define HEADER_CONNECTOR_CN6._D6  	// Pin not routed
#define HEADER_CONNECTOR_CN6._D7  	PH13
#define HEADER_CONNECTOR_CN6._D8  	// Pin not routed
#define HEADER_CONNECTOR_CN6._D9  	// Pin not routed
#define HEADER_CONNECTOR_CN6._D10 	// Pin not routed
#define HEADER_CONNECTOR_CN6._D11 	// Pin not routed
#define HEADER_CONNECTOR_CN6._D12 	// Pin not routed
#define HEADER_CONNECTOR_CN6._D13 	// Pin not routed
#define HEADER_CONNECTOR_CN6._D14 	// Pin not routed
#define HEADER_CONNECTOR_CN6._D15 	// Pin not routed
#define HEADER_CONNECTOR_CN6._D16 	// Pin not routed
#define HEADER_CONNECTOR_CN6._D17 	// Pin not routed
#define HEADER_CONNECTOR_CN6._D18 	PC8

#define HEADER_CONNECTOR_CN6_D1   	// Pin not routed
#define HEADER_CONNECTOR_CN6_D2   	// Pin not routed
#define HEADER_CONNECTOR_CN6_D3   	// Pin not routed
#define HEADER_CONNECTOR_CN6_D4   	// Pin not routed
#define HEADER_CONNECTOR_CN6_D5   	// Pin not routed
#define HEADER_CONNECTOR_CN6_D6   	// Pin not routed
#define HEADER_CONNECTOR_CN6_D7   	// Pin not routed
#define HEADER_CONNECTOR_CN6_D8   	// Pin not routed
#define HEADER_CONNECTOR_CN6_D9   	// Pin not routed
#define HEADER_CONNECTOR_CN6_D10  	// Pin not routed
#define HEADER_CONNECTOR_CN6_D11  	// Pin not routed
#define HEADER_CONNECTOR_CN6_D12  	// Pin not routed
#define HEADER_CONNECTOR_CN6_D13  	// Pin not routed
#define HEADER_CONNECTOR_CN6_D14  	// Pin not routed
#define HEADER_CONNECTOR_CN6_D15  	// Pin not routed
#define HEADER_CONNECTOR_CN6_D16  	// Pin not routed
#define HEADER_CONNECTOR_CN6_D17  	// Pin not routed
#define HEADER_CONNECTOR_CN6_D18  	// Pin not routed
#define HEADER_CONNECTOR_CN6_D19  	// Pin not routed
#define HEADER_CONNECTOR_CN6_D20  	// Pin not routed
#define HEADER_CONNECTOR_CN6_D21  	// Pin not routed
#define HEADER_CONNECTOR_CN6_D22  	// Pin not routed
#define HEADER_CONNECTOR_CN6_D23  	// Pin not routed
#define HEADER_CONNECTOR_CN6_D24  	// Pin not routed
#define HEADER_CONNECTOR_CN6_D25  	// Pin not routed
#define HEADER_CONNECTOR_CN6_D26  	// Pin not routed
#define HEADER_CONNECTOR_CN6_D27  	// Pin not routed
#define HEADER_CONNECTOR_CN6_D28  	// Pin not routed
#define HEADER_CONNECTOR_CN6_D29  	// Pin not routed
#define HEADER_CONNECTOR_CN6_D30  	// Pin not routed
#define HEADER_CONNECTOR_CN6_D31  	// Pin not routed
#define HEADER_CONNECTOR_CN6_D32  	// Pin not routed
#define HEADER_CONNECTOR_CN6_D33  	// Pin not routed
#define HEADER_CONNECTOR_CN6_D34  	PC12
#define HEADER_CONNECTOR_CN6_D35  	// Pin not routed
#define HEADER_CONNECTOR_CN6_D36  	PC10

#define HEADER_CONNECTOR_CN8._D1  	// Pin not routed
#define HEADER_CONNECTOR_CN8._D2  	// Pin not routed
#define HEADER_CONNECTOR_CN8._D3  	// Pin not routed
#define HEADER_CONNECTOR_CN8._D4  	// Pin not routed
#define HEADER_CONNECTOR_CN8._D5  	// Pin not routed
#define HEADER_CONNECTOR_CN8._D6  	// Pin not routed
#define HEADER_CONNECTOR_CN8._D7  	// Pin not routed
#define HEADER_CONNECTOR_CN8._D8  	// Pin not routed
#define HEADER_CONNECTOR_CN8._D9  	// Pin not routed
#define HEADER_CONNECTOR_CN8._D10 	// Pin not routed
#define HEADER_CONNECTOR_CN8._D11 	// Pin not routed
#define HEADER_CONNECTOR_CN8._D12 	// Pin not routed
#define HEADER_CONNECTOR_CN8._D13 	// Pin not routed
#define HEADER_CONNECTOR_CN8._D14 	// Pin not routed
#define HEADER_CONNECTOR_CN8._D15 	PA9

#define HEADER_CONNECTOR_CN15_D1  	// Pin not routed
#define HEADER_CONNECTOR_CN15_D2  	PI7
#define HEADER_CONNECTOR_CN15_D3  	// Pin not routed
#define HEADER_CONNECTOR_CN15_D4  	PI5
#define HEADER_CONNECTOR_CN15_D5  	// Pin not routed
#define HEADER_CONNECTOR_CN15_D6  	PA6
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
#define HEADER_CONNECTOR_CN15_D25 	// Pin not routed
#define HEADER_CONNECTOR_CN15_D26 	// Pin not routed
#define HEADER_CONNECTOR_CN15_D27 	// Pin not routed
#define HEADER_CONNECTOR_CN15_D28 	// Pin not routed
#define HEADER_CONNECTOR_CN15_D29 	// Pin not routed
#define HEADER_CONNECTOR_CN15_D30 	// Pin not routed
#define HEADER_CONNECTOR_CN15_D31 	// Pin not routed
#define HEADER_CONNECTOR_CN15_D32 	// Pin not routed
#define HEADER_CONNECTOR_CN15_D33 	// Pin not routed
#define HEADER_CONNECTOR_CN15_D34 	// Pin not routed
#define HEADER_CONNECTOR_CN15_D35 	// Pin not routed
#define HEADER_CONNECTOR_CN15_D36 	// Pin not routed
#define HEADER_CONNECTOR_CN15_D37 	PH9

#define HEADER_CONNECTOR_CN15._D1 	// Pin not routed
#define HEADER_CONNECTOR_CN15._D2 	// Pin not routed
#define HEADER_CONNECTOR_CN15._D3 	PI6
#define HEADER_CONNECTOR_CN15._D4 	// Pin not routed
#define HEADER_CONNECTOR_CN15._D5 	PI4
#define HEADER_CONNECTOR_CN15._D6 	PH14
#define HEADER_CONNECTOR_CN15._D7 	// Pin not routed
#define HEADER_CONNECTOR_CN15._D8 	// Pin not routed
#define HEADER_CONNECTOR_CN15._D9 	// Pin not routed
#define HEADER_CONNECTOR_CN15._D10	// Pin not routed
#define HEADER_CONNECTOR_CN15._D11	// Pin not routed
#define HEADER_CONNECTOR_CN15._D12	// Pin not routed
#define HEADER_CONNECTOR_CN15._D13	// Pin not routed
#define HEADER_CONNECTOR_CN15._D14	// Pin not routed
#define HEADER_CONNECTOR_CN15._D15	// Pin not routed
#define HEADER_CONNECTOR_CN15._D16	// Pin not routed
#define HEADER_CONNECTOR_CN15._D17	// Pin not routed
#define HEADER_CONNECTOR_CN15._D18	// Pin not routed
#define HEADER_CONNECTOR_CN15._D19	// Pin not routed
#define HEADER_CONNECTOR_CN15._D20	// Pin not routed
#define HEADER_CONNECTOR_CN15._D21	// Pin not routed
#define HEADER_CONNECTOR_CN15._D22	// Pin not routed
#define HEADER_CONNECTOR_CN15._D23	// Pin not routed
#define HEADER_CONNECTOR_CN15._D24	// Pin not routed
#define HEADER_CONNECTOR_CN15._D25	// Pin not routed
#define HEADER_CONNECTOR_CN15._D26	// Pin not routed
#define HEADER_CONNECTOR_CN15._D27	// Pin not routed
#define HEADER_CONNECTOR_CN15._D28	// Pin not routed
#define HEADER_CONNECTOR_CN15._D29	// Pin not routed
#define HEADER_CONNECTOR_CN15._D30	// Pin not routed
#define HEADER_CONNECTOR_CN15._D31	// Pin not routed
#define HEADER_CONNECTOR_CN15._D32	// Pin not routed
#define HEADER_CONNECTOR_CN15._D33	// Pin not routed
#define HEADER_CONNECTOR_CN15._D34	// Pin not routed
#define HEADER_CONNECTOR_CN15._D35	// Pin not routed
#define HEADER_CONNECTOR_CN15._D36	PH8
#define HEADER_CONNECTOR_CN15._D37	// Pin not routed
#define HEADER_CONNECTOR_CN15._D38	PH10
#define HEADER_CONNECTOR_CN15._D39	// Pin not routed
#define HEADER_CONNECTOR_CN15._D40	PH11
#define HEADER_CONNECTOR_CN15._D41	// Pin not routed
#define HEADER_CONNECTOR_CN15._D42	// Pin not routed
#define HEADER_CONNECTOR_CN15._D43	PH12

#define HEADER_CONNECTOR_CN19_D1  	// Pin not routed
#define HEADER_CONNECTOR_CN19_D2  	// Pin not routed
#define HEADER_CONNECTOR_CN19_D3  	// Pin not routed
#define HEADER_CONNECTOR_CN19_D4  	// Pin not routed
#define HEADER_CONNECTOR_CN19_D5  	// Pin not routed
#define HEADER_CONNECTOR_CN19_D6  	PD1
#define HEADER_CONNECTOR_CN19_D7  	PD2
#define HEADER_CONNECTOR_CN19_D8  	PD3
#define HEADER_CONNECTOR_CN19_D9  	PD4
#define HEADER_CONNECTOR_CN19_D10 	PD5
#define HEADER_CONNECTOR_CN19_D11 	PD6
#define HEADER_CONNECTOR_CN19_D12 	PD7
#define HEADER_CONNECTOR_CN19_D13 	PD8
#define HEADER_CONNECTOR_CN19_D14 	PD10
#define HEADER_CONNECTOR_CN19_D15 	PD11
#define HEADER_CONNECTOR_CN19_D16 	PD12
#define HEADER_CONNECTOR_CN19_D17 	PD13
#define HEADER_CONNECTOR_CN19_D18 	PD14
#define HEADER_CONNECTOR_CN19_D19 	PD15
#define HEADER_CONNECTOR_CN19_D20 	PD16
#define HEADER_CONNECTOR_CN19_D21 	PD17
#define HEADER_CONNECTOR_CN19_D22 	// Pin not routed
#define HEADER_CONNECTOR_CN19_D23 	PG10
#define HEADER_CONNECTOR_CN19_D24 	// Pin not routed
#define HEADER_CONNECTOR_CN19_D25 	// Pin not routed
#define HEADER_CONNECTOR_CN19_D26 	// Pin not routed
#define HEADER_CONNECTOR_CN19_D27 	// Pin not routed
#define HEADER_CONNECTOR_CN19_D28 	// Pin not routed
#define HEADER_CONNECTOR_CN19_D29 	// Pin not routed
#define HEADER_CONNECTOR_CN19_D30 	// Pin not routed
#define HEADER_CONNECTOR_CN19_D31 	// Pin not routed
#define HEADER_CONNECTOR_CN19_D32 	// Pin not routed
#define HEADER_CONNECTOR_CN19_D33 	// Pin not routed
#define HEADER_CONNECTOR_CN19_D34 	// Pin not routed

#ifdef __cplusplus
}
#endif

#endif    // _BOARD_H_
// ------------------------------------------------------------------------- END
