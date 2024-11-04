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

#define BOARD_NAME "STM32F373VC-Eval"

#include "hal_target.h"

// Mapping
#define HEADER_CONNECTOR_CN1_D1  	// Pin not routed
#define HEADER_CONNECTOR_CN1_D2  	// Pin not routed
#define HEADER_CONNECTOR_CN1_D3  	// Pin not routed
#define HEADER_CONNECTOR_CN1_D4  	// Pin not routed
#define HEADER_CONNECTOR_CN1_D5  	// Pin not routed
#define HEADER_CONNECTOR_CN1_D6  	// Pin not routed
#define HEADER_CONNECTOR_CN1_D7  	// Pin not routed
#define HEADER_CONNECTOR_CN1_D8  	// Pin not routed
#define HEADER_CONNECTOR_CN1_D9  	// Pin not routed
#define HEADER_CONNECTOR_CN1_D10 	// Pin not routed
#define HEADER_CONNECTOR_CN1_D11 	// Pin not routed
#define HEADER_CONNECTOR_CN1_D12 	// Pin not routed
#define HEADER_CONNECTOR_CN1_D13 	// Pin not routed
#define HEADER_CONNECTOR_CN1_D14 	// Pin not routed
#define HEADER_CONNECTOR_CN1_D15 	PB6
#define HEADER_CONNECTOR_CN1_D16 	PB7
#define HEADER_CONNECTOR_CN1_D17 	// Pin not routed
#define HEADER_CONNECTOR_CN1_D18 	// Pin not routed
#define HEADER_CONNECTOR_CN1_D19 	// Pin not routed

#define HEADER_CONNECTOR_CN3_D1  	PA10
#define HEADER_CONNECTOR_CN3_D2  	PA9
#define HEADER_CONNECTOR_CN3_D3  	// Pin not routed
#define HEADER_CONNECTOR_CN3_D4  	// Pin not routed

#define HEADER_CONNECTOR_CN7_D1  	// Pin not routed
#define HEADER_CONNECTOR_CN7_D2  	PE2
#define HEADER_CONNECTOR_CN7_D3  	PC12
#define HEADER_CONNECTOR_CN7_D4  	// Pin not routed
#define HEADER_CONNECTOR_CN7_D5  	PC10
#define HEADER_CONNECTOR_CN7_D6  	// Pin not routed
#define HEADER_CONNECTOR_CN7_D7  	PC11
#define HEADER_CONNECTOR_CN7_D8  	// Pin not routed
#define HEADER_CONNECTOR_CN7_D9  	// Pin not routed
#define HEADER_CONNECTOR_CN7_D10 	PE3

#define HEADER_CONNECTOR_CN12_D1 	// Pin not routed
#define HEADER_CONNECTOR_CN12_D2 	PD6
#define HEADER_CONNECTOR_CN12_D3 	PD5
#define HEADER_CONNECTOR_CN12_D4 	// Pin not routed
#define HEADER_CONNECTOR_CN12_D5 	// Pin not routed
#define HEADER_CONNECTOR_CN12_D6 	// Pin not routed
#define HEADER_CONNECTOR_CN12_D7 	PD4
#define HEADER_CONNECTOR_CN12_D8 	PD3
#define HEADER_CONNECTOR_CN12_D9 	// Pin not routed

#define HEADER_CONNECTOR_CN13_D1 	// Pin not routed
#define HEADER_CONNECTOR_CN13_D2 	PC6
#define HEADER_CONNECTOR_CN13_D3 	PC7
#define HEADER_CONNECTOR_CN13_D4 	PC8
#define HEADER_CONNECTOR_CN13_D5 	PC9
#define HEADER_CONNECTOR_CN13_D6 	PA8
#define HEADER_CONNECTOR_CN13_D7 	PA10
#define HEADER_CONNECTOR_CN13_D8 	PA9
#define HEADER_CONNECTOR_CN13_D9 	PA11
#define HEADER_CONNECTOR_CN13_D10	// Pin not routed
#define HEADER_CONNECTOR_CN13_D11	PC14
#define HEADER_CONNECTOR_CN13_D12	PA12
#define HEADER_CONNECTOR_CN13_D13	PA13
#define HEADER_CONNECTOR_CN13_D14	PF6
#define HEADER_CONNECTOR_CN13_D15	PC15
#define HEADER_CONNECTOR_CN13_D16	PA14
#define HEADER_CONNECTOR_CN13_D17	PA15
#define HEADER_CONNECTOR_CN13_D18	PC10
#define HEADER_CONNECTOR_CN13_D19	// Pin not routed
#define HEADER_CONNECTOR_CN13_D20	PC11
#define HEADER_CONNECTOR_CN13_D21	PD0
#define HEADER_CONNECTOR_CN13_D22	PC12
#define HEADER_CONNECTOR_CN13_D23	PD2
#define HEADER_CONNECTOR_CN13_D24	PD1
#define HEADER_CONNECTOR_CN13_D25	PD4
#define HEADER_CONNECTOR_CN13_D26	PD3
#define HEADER_CONNECTOR_CN13_D27	PD6
#define HEADER_CONNECTOR_CN13_D28	PD5
#define HEADER_CONNECTOR_CN13_D29	PD7
#define HEADER_CONNECTOR_CN13_D30	// Pin not routed
#define HEADER_CONNECTOR_CN13_D31	PB3
#define HEADER_CONNECTOR_CN13_D32	PB4
#define HEADER_CONNECTOR_CN13_D33	PB5
#define HEADER_CONNECTOR_CN13_D34	PB6
#define HEADER_CONNECTOR_CN13_D35	PB7
#define HEADER_CONNECTOR_CN13_D36	PB8
#define HEADER_CONNECTOR_CN13_D37	PB9
#define HEADER_CONNECTOR_CN13_D38	PE0
#define HEADER_CONNECTOR_CN13_D39	// Pin not routed
#define HEADER_CONNECTOR_CN13_D40	PE1
#define HEADER_CONNECTOR_CN13_D41	PE3
#define HEADER_CONNECTOR_CN13_D42	PE2
#define HEADER_CONNECTOR_CN13_D43	PE5
#define HEADER_CONNECTOR_CN13_D44	PE4
#define HEADER_CONNECTOR_CN13_D45	PF9
#define HEADER_CONNECTOR_CN13_D46	PE6
#define HEADER_CONNECTOR_CN13_D47	PF10
#define HEADER_CONNECTOR_CN13_D48	// Pin not routed
#define HEADER_CONNECTOR_CN13_D49	// Pin not routed
#define HEADER_CONNECTOR_CN13_D50	// Pin not routed

#define HEADER_CONNECTOR_CN14_D1 	// Pin not routed
#define HEADER_CONNECTOR_CN14_D2 	PD15
#define HEADER_CONNECTOR_CN14_D3 	PD14
#define HEADER_CONNECTOR_CN14_D4 	PD13
#define HEADER_CONNECTOR_CN14_D5 	PD11
#define HEADER_CONNECTOR_CN14_D6 	PD12
#define HEADER_CONNECTOR_CN14_D7 	PD9
#define HEADER_CONNECTOR_CN14_D8 	PD10
#define HEADER_CONNECTOR_CN14_D9 	PC13
#define HEADER_CONNECTOR_CN14_D10	// Pin not routed
#define HEADER_CONNECTOR_CN14_D11	// Pin not routed
#define HEADER_CONNECTOR_CN14_D12	PD8
#define HEADER_CONNECTOR_CN14_D13	PB15
#define HEADER_CONNECTOR_CN14_D14	PB14
#define HEADER_CONNECTOR_CN14_D15	PB10
#define HEADER_CONNECTOR_CN14_D16	PE15
#define HEADER_CONNECTOR_CN14_D17	PE14
#define HEADER_CONNECTOR_CN14_D18	PE13
#define HEADER_CONNECTOR_CN14_D19	// Pin not routed
#define HEADER_CONNECTOR_CN14_D20	PE12
#define HEADER_CONNECTOR_CN14_D21	PE11
#define HEADER_CONNECTOR_CN14_D22	PE10
#define HEADER_CONNECTOR_CN14_D23	PF0
#define HEADER_CONNECTOR_CN14_D24	// Pin not routed
#define HEADER_CONNECTOR_CN14_D25	PE9
#define HEADER_CONNECTOR_CN14_D26	PF1
#define HEADER_CONNECTOR_CN14_D27	PE8
#define HEADER_CONNECTOR_CN14_D28	PE7
#define HEADER_CONNECTOR_CN14_D29	PB2
#define HEADER_CONNECTOR_CN14_D30	// Pin not routed
#define HEADER_CONNECTOR_CN14_D31	PB1
#define HEADER_CONNECTOR_CN14_D32	PB0
#define HEADER_CONNECTOR_CN14_D33	PC5
#define HEADER_CONNECTOR_CN14_D34	PC4
#define HEADER_CONNECTOR_CN14_D35	PA7
#define HEADER_CONNECTOR_CN14_D36	PA6
#define HEADER_CONNECTOR_CN14_D37	PA5
#define HEADER_CONNECTOR_CN14_D38	PA4
#define HEADER_CONNECTOR_CN14_D39	// Pin not routed
#define HEADER_CONNECTOR_CN14_D40	PF4
#define HEADER_CONNECTOR_CN14_D41	PA3
#define HEADER_CONNECTOR_CN14_D42	PA2
#define HEADER_CONNECTOR_CN14_D43	PA1
#define HEADER_CONNECTOR_CN14_D44	PA0
#define HEADER_CONNECTOR_CN14_D45	PF2
#define HEADER_CONNECTOR_CN14_D46	PC3
#define HEADER_CONNECTOR_CN14_D47	PC2
#define HEADER_CONNECTOR_CN14_D48	PC1
#define HEADER_CONNECTOR_CN14_D49	PC0
#define HEADER_CONNECTOR_CN14_D50	// Pin not routed

#define HEADER_CONNECTOR_CN17_D1 	// Pin not routed
#define HEADER_CONNECTOR_CN17_D2 	// Pin not routed
#define HEADER_CONNECTOR_CN17_D3 	PB4
#define HEADER_CONNECTOR_CN17_D4 	// Pin not routed
#define HEADER_CONNECTOR_CN17_D5 	PA15
#define HEADER_CONNECTOR_CN17_D6 	// Pin not routed
#define HEADER_CONNECTOR_CN17_D7 	PA13
#define HEADER_CONNECTOR_CN17_D8 	// Pin not routed
#define HEADER_CONNECTOR_CN17_D9 	PA14
#define HEADER_CONNECTOR_CN17_D10	// Pin not routed
#define HEADER_CONNECTOR_CN17_D11	// Pin not routed
#define HEADER_CONNECTOR_CN17_D12	// Pin not routed
#define HEADER_CONNECTOR_CN17_D13	PB3
#define HEADER_CONNECTOR_CN17_D14	// Pin not routed
#define HEADER_CONNECTOR_CN17_D15	// Pin not routed
#define HEADER_CONNECTOR_CN17_D16	// Pin not routed
#define HEADER_CONNECTOR_CN17_D17	// Pin not routed
#define HEADER_CONNECTOR_CN17_D18	// Pin not routed
#define HEADER_CONNECTOR_CN17_D19	// Pin not routed
#define HEADER_CONNECTOR_CN17_D20	// Pin not routed

#ifdef __cplusplus
}
#endif

#endif    // _BOARD_H_
// ------------------------------------------------------------------------- END
