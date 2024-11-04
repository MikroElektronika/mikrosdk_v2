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

#define BOARD_NAME "STM32L4R9AI-Eval"

#include "hal_target.h"

// Mapping
#define HEADER_CONNECTOR_CN2_D1  	PH5
#define HEADER_CONNECTOR_CN2_D2  	// Pin not routed
#define HEADER_CONNECTOR_CN2_D3  	PH4
#define HEADER_CONNECTOR_CN2_D4  	// Pin not routed
#define HEADER_CONNECTOR_CN2_D5  	// Pin not routed
#define HEADER_CONNECTOR_CN2_D6  	// Pin not routed
#define HEADER_CONNECTOR_CN2_D7  	// Pin not routed
#define HEADER_CONNECTOR_CN2_D8  	// Pin not routed

#define HEADER_CONNECTOR_CN5_D1  	PH9
#define HEADER_CONNECTOR_CN5_D2  	PI5
#define HEADER_CONNECTOR_CN5_D3  	PH14
#define HEADER_CONNECTOR_CN5_D4  	PH12
#define HEADER_CONNECTOR_CN5_D5  	PH15
#define HEADER_CONNECTOR_CN5_D6  	PI6
#define HEADER_CONNECTOR_CN5_D7  	PI3
#define HEADER_CONNECTOR_CN5_D8  	PG15
#define HEADER_CONNECTOR_CN5_D9  	// Pin not routed
#define HEADER_CONNECTOR_CN5_D10 	// Pin not routed
#define HEADER_CONNECTOR_CN5_D11 	PH13
#define HEADER_CONNECTOR_CN5_D12 	PB4
#define HEADER_CONNECTOR_CN5_D13 	PG13
#define HEADER_CONNECTOR_CN5_D14 	PB6
#define HEADER_CONNECTOR_CN5_D15 	PB5
#define HEADER_CONNECTOR_CN5_D16 	PB7
#define HEADER_CONNECTOR_CN5_D17 	PI9
#define HEADER_CONNECTOR_CN5_D18 	PI10
#define HEADER_CONNECTOR_CN5_D19 	PI11
#define HEADER_CONNECTOR_CN5_D20 	PI7
#define HEADER_CONNECTOR_CN5_D21 	// Pin not routed
#define HEADER_CONNECTOR_CN5_D22 	PH3
#define HEADER_CONNECTOR_CN5_D23 	PC14
#define HEADER_CONNECTOR_CN5_D24 	PC15
#define HEADER_CONNECTOR_CN5_D25 	PC13
#define HEADER_CONNECTOR_CN5_D26 	PH0
#define HEADER_CONNECTOR_CN5_D27 	PH1
#define HEADER_CONNECTOR_CN5_D28 	PA0
#define HEADER_CONNECTOR_CN5_D29 	// Pin not routed
#define HEADER_CONNECTOR_CN5_D30 	// Pin not routed
#define HEADER_CONNECTOR_CN5_D31 	PA5
#define HEADER_CONNECTOR_CN5_D32 	PA1
#define HEADER_CONNECTOR_CN5_D33 	PC2
#define HEADER_CONNECTOR_CN5_D34 	PA4
#define HEADER_CONNECTOR_CN5_D35 	PH8
#define HEADER_CONNECTOR_CN5_D36 	PH11
#define HEADER_CONNECTOR_CN5_D37 	PH10
#define HEADER_CONNECTOR_CN5_D38 	// Pin not routed
#define HEADER_CONNECTOR_CN5_D39 	// Pin not routed
#define HEADER_CONNECTOR_CN5_D40 	// Pin not routed

#define HEADER_CONNECTOR_CN6_D1  	PH2
#define HEADER_CONNECTOR_CN6_D2  	PG11
#define HEADER_CONNECTOR_CN6_D3  	PI0
#define HEADER_CONNECTOR_CN6_D4  	PI2
#define HEADER_CONNECTOR_CN6_D5  	PD2
#define HEADER_CONNECTOR_CN6_D6  	PC8
#define HEADER_CONNECTOR_CN6_D7  	PI1
#define HEADER_CONNECTOR_CN6_D8  	PC10
#define HEADER_CONNECTOR_CN6_D9  	// Pin not routed
#define HEADER_CONNECTOR_CN6_D10 	// Pin not routed
#define HEADER_CONNECTOR_CN6_D11 	PA12
#define HEADER_CONNECTOR_CN6_D12 	PC11
#define HEADER_CONNECTOR_CN6_D13 	PA11
#define HEADER_CONNECTOR_CN6_D14 	PC12
#define HEADER_CONNECTOR_CN6_D15 	PG8
#define HEADER_CONNECTOR_CN6_D16 	PA10
#define HEADER_CONNECTOR_CN6_D17 	PA9
#define HEADER_CONNECTOR_CN6_D18 	PC6
#define HEADER_CONNECTOR_CN6_D19 	PC9
#define HEADER_CONNECTOR_CN6_D20 	PG7
#define HEADER_CONNECTOR_CN6_D21 	PC7
#define HEADER_CONNECTOR_CN6_D22 	PB14
#define HEADER_CONNECTOR_CN6_D23 	PB15
#define HEADER_CONNECTOR_CN6_D24 	PB12
#define HEADER_CONNECTOR_CN6_D25 	PB13
#define HEADER_CONNECTOR_CN6_D26 	PF11
#define HEADER_CONNECTOR_CN6_D27 	// Pin not routed
#define HEADER_CONNECTOR_CN6_D28 	PB0
#define HEADER_CONNECTOR_CN6_D29 	// Pin not routed
#define HEADER_CONNECTOR_CN6_D30 	// Pin not routed
#define HEADER_CONNECTOR_CN6_D31 	PA3
#define HEADER_CONNECTOR_CN6_D32 	PB1
#define HEADER_CONNECTOR_CN6_D33 	PA7
#define HEADER_CONNECTOR_CN6_D34 	PB2
#define HEADER_CONNECTOR_CN6_D35 	PC4
#define HEADER_CONNECTOR_CN6_D36 	PA6
#define HEADER_CONNECTOR_CN6_D37 	PC3
#define HEADER_CONNECTOR_CN6_D38 	PA2
#define HEADER_CONNECTOR_CN6_D39 	// Pin not routed
#define HEADER_CONNECTOR_CN6_D40 	// Pin not routed

#define HEADER_CONNECTOR_CN7_D1  	// Pin not routed
#define HEADER_CONNECTOR_CN7_D2  	PG8
#define HEADER_CONNECTOR_CN7_D3  	PG7
#define HEADER_CONNECTOR_CN7_D4  	// Pin not routed
#define HEADER_CONNECTOR_CN7_D5  	// Pin not routed
#define HEADER_CONNECTOR_CN7_D6  	// Pin not routed
#define HEADER_CONNECTOR_CN7_D7  	PB12
#define HEADER_CONNECTOR_CN7_D8  	PB13
#define HEADER_CONNECTOR_CN7_D9  	// Pin not routed

#define HEADER_CONNECTOR_CN8_D1  	PC10
#define HEADER_CONNECTOR_CN8_D2  	PC11
#define HEADER_CONNECTOR_CN8_D3  	PD2
#define HEADER_CONNECTOR_CN8_D4  	// Pin not routed
#define HEADER_CONNECTOR_CN8_D5  	PC12
#define HEADER_CONNECTOR_CN8_D6  	// Pin not routed
#define HEADER_CONNECTOR_CN8_D7  	PC8
#define HEADER_CONNECTOR_CN8_D8  	PC9
#define HEADER_CONNECTOR_CN8_D9  	// Pin not routed
#define HEADER_CONNECTOR_CN8_D10 	// Pin not routed

#define HEADER_CONNECTOR_CN13_D1 	PD1
#define HEADER_CONNECTOR_CN13_D2 	// Pin not routed
#define HEADER_CONNECTOR_CN13_D3 	PD0
#define HEADER_CONNECTOR_CN13_D4 	PD6
#define HEADER_CONNECTOR_CN13_D5 	PB8
#define HEADER_CONNECTOR_CN13_D6 	PD4
#define HEADER_CONNECTOR_CN13_D7 	PG10
#define HEADER_CONNECTOR_CN13_D8 	PE1
#define HEADER_CONNECTOR_CN13_D9 	// Pin not routed
#define HEADER_CONNECTOR_CN13_D10	// Pin not routed
#define HEADER_CONNECTOR_CN13_D11	PE0
#define HEADER_CONNECTOR_CN13_D12	PD5
#define HEADER_CONNECTOR_CN13_D13	PG12
#define HEADER_CONNECTOR_CN13_D14	PE2
#define HEADER_CONNECTOR_CN13_D15	PE4
#define HEADER_CONNECTOR_CN13_D16	PE3
#define HEADER_CONNECTOR_CN13_D17	PE5
#define HEADER_CONNECTOR_CN13_D18	PE6
#define HEADER_CONNECTOR_CN13_D19	PF1
#define HEADER_CONNECTOR_CN13_D20	PF0
#define HEADER_CONNECTOR_CN13_D21	PF2
#define HEADER_CONNECTOR_CN13_D22	PC0
#define HEADER_CONNECTOR_CN13_D23	PB9
#define HEADER_CONNECTOR_CN13_D24	PC1
#define HEADER_CONNECTOR_CN13_D25	PF10
#define HEADER_CONNECTOR_CN13_D26	PF3
#define HEADER_CONNECTOR_CN13_D27	PF5
#define HEADER_CONNECTOR_CN13_D28	PG4
#define HEADER_CONNECTOR_CN13_D29	// Pin not routed
#define HEADER_CONNECTOR_CN13_D30	// Pin not routed
#define HEADER_CONNECTOR_CN13_D31	PF4
#define HEADER_CONNECTOR_CN13_D32	PG1
#define HEADER_CONNECTOR_CN13_D33	PF15
#define HEADER_CONNECTOR_CN13_D34	PF12
#define HEADER_CONNECTOR_CN13_D35	PG0
#define HEADER_CONNECTOR_CN13_D36	PF13
#define HEADER_CONNECTOR_CN13_D37	PE10
#define HEADER_CONNECTOR_CN13_D38	PF14
#define HEADER_CONNECTOR_CN13_D39	// Pin not routed
#define HEADER_CONNECTOR_CN13_D40	// Pin not routed

#define HEADER_CONNECTOR_CN14_D1 	PA14
#define HEADER_CONNECTOR_CN14_D2 	PA13
#define HEADER_CONNECTOR_CN14_D3 	PD7
#define HEADER_CONNECTOR_CN14_D4 	PA15
#define HEADER_CONNECTOR_CN14_D5 	PD3
#define HEADER_CONNECTOR_CN14_D6 	PI4
#define HEADER_CONNECTOR_CN14_D7 	PB3
#define HEADER_CONNECTOR_CN14_D8 	PG9
#define HEADER_CONNECTOR_CN14_D9 	// Pin not routed
#define HEADER_CONNECTOR_CN14_D10	// Pin not routed
#define HEADER_CONNECTOR_CN14_D11	PG5
#define HEADER_CONNECTOR_CN14_D12	PA8
#define HEADER_CONNECTOR_CN14_D13	PD15
#define HEADER_CONNECTOR_CN14_D14	PG3
#define HEADER_CONNECTOR_CN14_D15	PD14
#define HEADER_CONNECTOR_CN14_D16	PG6
#define HEADER_CONNECTOR_CN14_D17	PD10
#define HEADER_CONNECTOR_CN14_D18	PG2
#define HEADER_CONNECTOR_CN14_D19	PH5
#define HEADER_CONNECTOR_CN14_D20	PD11
#define HEADER_CONNECTOR_CN14_D21	PB10
#define HEADER_CONNECTOR_CN14_D22	PH4
#define HEADER_CONNECTOR_CN14_D23	PD8
#define HEADER_CONNECTOR_CN14_D24	PB11
#define HEADER_CONNECTOR_CN14_D25	PD13
#define HEADER_CONNECTOR_CN14_D26	PD9
#define HEADER_CONNECTOR_CN14_D27	PE12
#define HEADER_CONNECTOR_CN14_D28	PD12
#define HEADER_CONNECTOR_CN14_D29	// Pin not routed
#define HEADER_CONNECTOR_CN14_D30	// Pin not routed
#define HEADER_CONNECTOR_CN14_D31	// Pin not routed
#define HEADER_CONNECTOR_CN14_D32	PE13
#define HEADER_CONNECTOR_CN14_D33	PE7
#define HEADER_CONNECTOR_CN14_D34	PE8
#define HEADER_CONNECTOR_CN14_D35	PE14
#define HEADER_CONNECTOR_CN14_D36	PE11
#define HEADER_CONNECTOR_CN14_D37	PE15
#define HEADER_CONNECTOR_CN14_D38	PE9
#define HEADER_CONNECTOR_CN14_D39	// Pin not routed
#define HEADER_CONNECTOR_CN14_D40	// Pin not routed

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

#define HEADER_CONNECTOR_CN20_D1 	// Pin not routed
#define HEADER_CONNECTOR_CN20_D2 	// Pin not routed
#define HEADER_CONNECTOR_CN20_D3 	// Pin not routed
#define HEADER_CONNECTOR_CN20_D4 	// Pin not routed
#define HEADER_CONNECTOR_CN20_D5 	// Pin not routed
#define HEADER_CONNECTOR_CN20_D6 	// Pin not routed
#define HEADER_CONNECTOR_CN20_D7 	PG13
#define HEADER_CONNECTOR_CN20_D8 	PB14
#define HEADER_CONNECTOR_CN20_D9 	// Pin not routed
#define HEADER_CONNECTOR_CN20_D10	// Pin not routed
#define HEADER_CONNECTOR_CN20_D11	// Pin not routed
#define HEADER_CONNECTOR_CN20_D12	// Pin not routed

#ifdef __cplusplus
}
#endif

#endif    // _BOARD_H_
// ------------------------------------------------------------------------- END
