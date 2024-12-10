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

#define BOARD_NAME "STM32F429NI-Eval"

#include "hal_target.h"

// Mapping
#define HEADER_CONNECTOR_CN1_D1     GPIO_PA6
#define HEADER_CONNECTOR_CN1_D2     // Pin not routed
#define HEADER_CONNECTOR_CN1_D3     GPIO_PC6
#define HEADER_CONNECTOR_CN1_D4     // Pin not routed
#define HEADER_CONNECTOR_CN1_D5     GPIO_PA7
#define HEADER_CONNECTOR_CN1_D6     // Pin not routed
#define HEADER_CONNECTOR_CN1_D7     GPIO_PC7
#define HEADER_CONNECTOR_CN1_D8     // Pin not routed
#define HEADER_CONNECTOR_CN1_D9     GPIO_PB0
#define HEADER_CONNECTOR_CN1_D10    // Pin not routed
#define HEADER_CONNECTOR_CN1_D11    GPIO_PC8
#define HEADER_CONNECTOR_CN1_D12    // Pin not routed
#define HEADER_CONNECTOR_CN1_D13    GPIO_PB1
#define HEADER_CONNECTOR_CN1_D14    GPIO_PC4
#define HEADER_CONNECTOR_CN1_D15    GPIO_PC1
#define HEADER_CONNECTOR_CN1_D16    // Pin not routed
#define HEADER_CONNECTOR_CN1_D17    GPIO_PC2
#define HEADER_CONNECTOR_CN1_D18    // Pin not routed
#define HEADER_CONNECTOR_CN1_D19    GPIO_PC3
#define HEADER_CONNECTOR_CN1_D20    // Pin not routed
#define HEADER_CONNECTOR_CN1_D21    GPIO_PG11
#define HEADER_CONNECTOR_CN1_D22    // Pin not routed
#define HEADER_CONNECTOR_CN1_D23    GPIO_PB8
#define HEADER_CONNECTOR_CN1_D24    // Pin not routed
#define HEADER_CONNECTOR_CN1_D25    // Pin not routed
#define HEADER_CONNECTOR_CN1_D26    GPIO_PC5
#define HEADER_CONNECTOR_CN1_D27    GPIO_PA12
#define HEADER_CONNECTOR_CN1_D28    // Pin not routed
#define HEADER_CONNECTOR_CN1_D29    GPIO_PA11
#define HEADER_CONNECTOR_CN1_D30    // Pin not routed
#define HEADER_CONNECTOR_CN1_D31    GPIO_PA0
#define HEADER_CONNECTOR_CN1_D32    // Pin not routed
#define HEADER_CONNECTOR_CN1_D33    GPIO_PA1
#define HEADER_CONNECTOR_CN1_D34    GPIO_PA2

#define HEADER_CONNECTOR_CN2_D1  	GPIO_PB9
#define HEADER_CONNECTOR_CN2_D2  	GPIO_PC11
#define HEADER_CONNECTOR_CN2_D3  	GPIO_PB6
#define HEADER_CONNECTOR_CN2_D4  	GPIO_PC10
#define HEADER_CONNECTOR_CN2_D5  	// Pin not routed
#define HEADER_CONNECTOR_CN2_D6  	GPIO_PC12
#define HEADER_CONNECTOR_CN2_D7  	// Pin not routed
#define HEADER_CONNECTOR_CN2_D8  	// Pin not routed
#define HEADER_CONNECTOR_CN2_D9  	// Pin not routed
#define HEADER_CONNECTOR_CN2_D10 	// Pin not routed

#define HEADER_CONNECTOR_CN3_D1  	GPIO_PB9
#define HEADER_CONNECTOR_CN3_D2  	GPIO_PC11
#define HEADER_CONNECTOR_CN3_D3  	GPIO_PB6
#define HEADER_CONNECTOR_CN3_D4  	GPIO_PC10
#define HEADER_CONNECTOR_CN3_D5  	// Pin not routed
#define HEADER_CONNECTOR_CN3_D6  	GPIO_PC12
#define HEADER_CONNECTOR_CN3_D7  	// Pin not routed
#define HEADER_CONNECTOR_CN3_D8  	// Pin not routed

#define HEADER_CONNECTOR_CN4_D1  	GPIO_PF10
#define HEADER_CONNECTOR_CN4_D2  	// Pin not routed

#define HEADER_CONNECTOR_CN5_D1  	// Pin not routed
#define HEADER_CONNECTOR_CN5_D2  	// Pin not routed
#define HEADER_CONNECTOR_CN5_D3  	// Pin not routed
#define HEADER_CONNECTOR_CN5_D4  	// Pin not routed
#define HEADER_CONNECTOR_CN5_D5  	GPIO_PD6
#define HEADER_CONNECTOR_CN5_D6  	GPIO_PD2
#define HEADER_CONNECTOR_CN5_D7  	// Pin not routed
#define HEADER_CONNECTOR_CN5_D8  	// Pin not routed
#define HEADER_CONNECTOR_CN5_D9  	GPIO_PC10
#define HEADER_CONNECTOR_CN5_D10 	GPIO_PC12
#define HEADER_CONNECTOR_CN5_D11 	// Pin not routed
#define HEADER_CONNECTOR_CN5_D12 	// Pin not routed
#define HEADER_CONNECTOR_CN5_D13 	GPIO_PB6
#define HEADER_CONNECTOR_CN5_D14 	GPIO_PB9
#define HEADER_CONNECTOR_CN5_D15 	// Pin not routed
#define HEADER_CONNECTOR_CN5_D16 	// Pin not routed
#define HEADER_CONNECTOR_CN5_D17 	// Pin not routed
#define HEADER_CONNECTOR_CN5_D18 	// Pin not routed
#define HEADER_CONNECTOR_CN5_D19 	// Pin not routed
#define HEADER_CONNECTOR_CN5_D20 	// Pin not routed
#define HEADER_CONNECTOR_CN5_D21 	// Pin not routed
#define HEADER_CONNECTOR_CN5_D22 	// Pin not routed
#define HEADER_CONNECTOR_CN5_D23 	GPIO_PC6
#define HEADER_CONNECTOR_CN5_D24 	GPIO_PC7
#define HEADER_CONNECTOR_CN5_D25 	GPIO_PC8
#define HEADER_CONNECTOR_CN5_D26 	GPIO_PC9
#define HEADER_CONNECTOR_CN5_D27 	GPIO_PC11
#define HEADER_CONNECTOR_CN5_D28 	GPIO_PD3
#define HEADER_CONNECTOR_CN5_D29 	GPIO_PB8
#define HEADER_CONNECTOR_CN5_D30 	GPIO_PE6
#define HEADER_CONNECTOR_CN5_D31 	GPIO_PA4
#define HEADER_CONNECTOR_CN5_D32 	GPIO_PB7
#define HEADER_CONNECTOR_CN5_D33 	GPIO_PA6
#define HEADER_CONNECTOR_CN5_D34 	// Pin not routed
#define HEADER_CONNECTOR_CN5_D35 	// Pin not routed
#define HEADER_CONNECTOR_CN5_D36 	// Pin not routed
#define HEADER_CONNECTOR_CN5_D37 	// Pin not routed
#define HEADER_CONNECTOR_CN5_D38 	// Pin not routed
#define HEADER_CONNECTOR_CN5_D39 	// Pin not routed
#define HEADER_CONNECTOR_CN5_D40 	// Pin not routed
#define HEADER_CONNECTOR_CN5_D41 	// Pin not routed
#define HEADER_CONNECTOR_CN5_D42 	// Pin not routed

#define HEADER_CONNECTOR_CN6_D1  	// Pin not routed
#define HEADER_CONNECTOR_CN6_D2  	GPIO_PI11
#define HEADER_CONNECTOR_CN6_D3  	GPIO_PH0
#define HEADER_CONNECTOR_CN6_D4  	GPIO_PB5
#define HEADER_CONNECTOR_CN6_D5  	// Pin not routed
#define HEADER_CONNECTOR_CN6_D6  	GPIO_PH1
#define HEADER_CONNECTOR_CN6_D7  	GPIO_PF6
#define HEADER_CONNECTOR_CN6_D8  	GPIO_PF7
#define HEADER_CONNECTOR_CN6_D9  	GPIO_PF10
#define HEADER_CONNECTOR_CN6_D10 	// Pin not routed
#define HEADER_CONNECTOR_CN6_D11 	GPIO_PC0
#define HEADER_CONNECTOR_CN6_D12 	GPIO_PF9
#define HEADER_CONNECTOR_CN6_D13 	GPIO_PA2
#define HEADER_CONNECTOR_CN6_D14 	GPIO_PA1
#define HEADER_CONNECTOR_CN6_D15 	GPIO_PA0
#define HEADER_CONNECTOR_CN6_D16 	GPIO_PC1
#define HEADER_CONNECTOR_CN6_D17 	GPIO_PF8
#define HEADER_CONNECTOR_CN6_D18 	GPIO_PA3
#define HEADER_CONNECTOR_CN6_D19 	// Pin not routed
#define HEADER_CONNECTOR_CN6_D20 	GPIO_PA6
#define HEADER_CONNECTOR_CN6_D21 	GPIO_PA4
#define HEADER_CONNECTOR_CN6_D22 	GPIO_PA7
#define HEADER_CONNECTOR_CN6_D23 	GPIO_PC2
#define HEADER_CONNECTOR_CN6_D24 	GPIO_PA5
#define HEADER_CONNECTOR_CN6_D25 	GPIO_PC4
#define HEADER_CONNECTOR_CN6_D26 	GPIO_PB1
#define HEADER_CONNECTOR_CN6_D27 	GPIO_PC3
#define HEADER_CONNECTOR_CN6_D28 	GPIO_PH4
#define HEADER_CONNECTOR_CN6_D29 	GPIO_PB2
#define HEADER_CONNECTOR_CN6_D30 	// Pin not routed
#define HEADER_CONNECTOR_CN6_D31 	GPIO_PJ3
#define HEADER_CONNECTOR_CN6_D32 	GPIO_PI14
#define HEADER_CONNECTOR_CN6_D33 	GPIO_PB10
#define HEADER_CONNECTOR_CN6_D34 	GPIO_PJ4
#define HEADER_CONNECTOR_CN6_D35 	GPIO_PB14
#define HEADER_CONNECTOR_CN6_D36 	GPIO_PB11
#define HEADER_CONNECTOR_CN6_D37 	GPIO_PH6
#define HEADER_CONNECTOR_CN6_D38 	GPIO_PB15
#define HEADER_CONNECTOR_CN6_D39 	// Pin not routed
#define HEADER_CONNECTOR_CN6_D40 	GPIO_PH7
#define HEADER_CONNECTOR_CN6_D41 	GPIO_PB12
#define HEADER_CONNECTOR_CN6_D42 	GPIO_PJ5
#define HEADER_CONNECTOR_CN6_D43 	GPIO_PB13
#define HEADER_CONNECTOR_CN6_D44 	GPIO_PJ6
#define HEADER_CONNECTOR_CN6_D45 	GPIO_PJ9
#define HEADER_CONNECTOR_CN6_D46 	GPIO_PC5
#define HEADER_CONNECTOR_CN6_D47 	GPIO_PG7
#define HEADER_CONNECTOR_CN6_D48 	// Pin not routed
#define HEADER_CONNECTOR_CN6_D49 	// Pin not routed
#define HEADER_CONNECTOR_CN6_D50 	// Pin not routed
#define HEADER_CONNECTOR_CN6_D51 	GPIO_PG6
#define HEADER_CONNECTOR_CN6_D52 	GPIO_PB0
#define HEADER_CONNECTOR_CN6_D53 	GPIO_PJ7
#define HEADER_CONNECTOR_CN6_D54 	GPIO_PJ0
#define HEADER_CONNECTOR_CN6_D55 	GPIO_PJ10
#define HEADER_CONNECTOR_CN6_D56 	GPIO_PJ2
#define HEADER_CONNECTOR_CN6_D57 	GPIO_PJ8
#define HEADER_CONNECTOR_CN6_D58 	GPIO_PJ1
#define HEADER_CONNECTOR_CN6_D59 	// Pin not routed
#define HEADER_CONNECTOR_CN6_D60 	// Pin not routed

#define HEADER_CONNECTOR_CN7_D1  	// Pin not routed
#define HEADER_CONNECTOR_CN7_D2  	GPIO_PI13
#define HEADER_CONNECTOR_CN7_D3  	GPIO_PC15
#define HEADER_CONNECTOR_CN7_D4  	GPIO_PC14
#define HEADER_CONNECTOR_CN7_D5  	GPIO_PI15
#define HEADER_CONNECTOR_CN7_D6  	GPIO_PC13
#define HEADER_CONNECTOR_CN7_D7  	GPIO_PI12
#define HEADER_CONNECTOR_CN7_D8  	GPIO_PK7
#define HEADER_CONNECTOR_CN7_D9  	GPIO_PI8
#define HEADER_CONNECTOR_CN7_D10 	// Pin not routed
#define HEADER_CONNECTOR_CN7_D11 	GPIO_PK6
#define HEADER_CONNECTOR_CN7_D12 	GPIO_PK5
#define HEADER_CONNECTOR_CN7_D13 	GPIO_PK4
#define HEADER_CONNECTOR_CN7_D14 	GPIO_PB9
#define HEADER_CONNECTOR_CN7_D15 	GPIO_PG12
#define HEADER_CONNECTOR_CN7_D16 	GPIO_PK3
#define HEADER_CONNECTOR_CN7_D17 	GPIO_PG10
#define HEADER_CONNECTOR_CN7_D18 	GPIO_PB6
#define HEADER_CONNECTOR_CN7_D19 	// Pin not routed
#define HEADER_CONNECTOR_CN7_D20 	GPIO_PJ14
#define HEADER_CONNECTOR_CN7_D21 	GPIO_PB7
#define HEADER_CONNECTOR_CN7_D22 	GPIO_PJ15
#define HEADER_CONNECTOR_CN7_D23 	GPIO_PD3
#define HEADER_CONNECTOR_CN7_D24 	GPIO_PB4
#define HEADER_CONNECTOR_CN7_D25 	GPIO_PG13
#define HEADER_CONNECTOR_CN7_D26 	GPIO_PJ13
#define HEADER_CONNECTOR_CN7_D27 	GPIO_PJ12
#define HEADER_CONNECTOR_CN7_D28 	GPIO_PC12
#define HEADER_CONNECTOR_CN7_D29 	GPIO_PG14
#define HEADER_CONNECTOR_CN7_D30 	// Pin not routed
#define HEADER_CONNECTOR_CN7_D31 	GPIO_PB8
#define HEADER_CONNECTOR_CN7_D32 	GPIO_PA15
#define HEADER_CONNECTOR_CN7_D33 	GPIO_PG11
#define HEADER_CONNECTOR_CN7_D34 	GPIO_PK1
#define HEADER_CONNECTOR_CN7_D35 	GPIO_PJ11
#define HEADER_CONNECTOR_CN7_D36 	GPIO_PA14
#define HEADER_CONNECTOR_CN7_D37 	GPIO_PK0
#define HEADER_CONNECTOR_CN7_D38 	GPIO_PK2
#define HEADER_CONNECTOR_CN7_D39 	// Pin not routed
#define HEADER_CONNECTOR_CN7_D40 	GPIO_PA13
#define HEADER_CONNECTOR_CN7_D41 	GPIO_PA11
#define HEADER_CONNECTOR_CN7_D42 	GPIO_PA12
#define HEADER_CONNECTOR_CN7_D43 	GPIO_PA9
#define HEADER_CONNECTOR_CN7_D44 	GPIO_PA10
#define HEADER_CONNECTOR_CN7_D45 	GPIO_PB3
#define HEADER_CONNECTOR_CN7_D46 	GPIO_PC9
#define HEADER_CONNECTOR_CN7_D47 	GPIO_PD6
#define HEADER_CONNECTOR_CN7_D48 	// Pin not routed
#define HEADER_CONNECTOR_CN7_D49 	// Pin not routed
#define HEADER_CONNECTOR_CN7_D50 	// Pin not routed
#define HEADER_CONNECTOR_CN7_D51 	GPIO_PC8
#define HEADER_CONNECTOR_CN7_D52 	GPIO_PA8
#define HEADER_CONNECTOR_CN7_D53 	GPIO_PC11
#define HEADER_CONNECTOR_CN7_D54 	// Pin not routed
#define HEADER_CONNECTOR_CN7_D55 	GPIO_PC10
#define HEADER_CONNECTOR_CN7_D56 	GPIO_PC7
#define HEADER_CONNECTOR_CN7_D57 	GPIO_PD2
#define HEADER_CONNECTOR_CN7_D58 	GPIO_PC6
#define HEADER_CONNECTOR_CN7_D59 	// Pin not routed
#define HEADER_CONNECTOR_CN7_D60 	// Pin not routed

#define HEADER_CONNECTOR_CN8_D1  	// Pin not routed
#define HEADER_CONNECTOR_CN8_D2  	GPIO_PA10
#define HEADER_CONNECTOR_CN8_D3  	GPIO_PA9
#define HEADER_CONNECTOR_CN8_D4  	// Pin not routed
#define HEADER_CONNECTOR_CN8_D5  	// Pin not routed
#define HEADER_CONNECTOR_CN8_D6  	// Pin not routed
#define HEADER_CONNECTOR_CN8_D7  	// Pin not routed
#define HEADER_CONNECTOR_CN8_D8  	// Pin not routed
#define HEADER_CONNECTOR_CN8_D9  	// Pin not routed

#define HEADER_CONNECTOR_CN11_D1 	GPIO_PH3
#define HEADER_CONNECTOR_CN11_D2 	GPIO_PH5
#define HEADER_CONNECTOR_CN11_D3 	GPIO_PF13
#define HEADER_CONNECTOR_CN11_D4 	GPIO_PF14
#define HEADER_CONNECTOR_CN11_D5 	GPIO_PF12
#define HEADER_CONNECTOR_CN11_D6 	GPIO_PG0
#define HEADER_CONNECTOR_CN11_D7 	GPIO_PG1
#define HEADER_CONNECTOR_CN11_D8 	GPIO_PF11
#define HEADER_CONNECTOR_CN11_D9 	// Pin not routed
#define HEADER_CONNECTOR_CN11_D10	// Pin not routed
#define HEADER_CONNECTOR_CN11_D11	GPIO_PE7
#define HEADER_CONNECTOR_CN11_D12	GPIO_PE9
#define HEADER_CONNECTOR_CN11_D13	GPIO_PE10
#define HEADER_CONNECTOR_CN11_D14	GPIO_PE8
#define HEADER_CONNECTOR_CN11_D15	GPIO_PE12
#define HEADER_CONNECTOR_CN11_D16	GPIO_PE11
#define HEADER_CONNECTOR_CN11_D17	GPIO_PE15
#define HEADER_CONNECTOR_CN11_D18	GPIO_PF15
#define HEADER_CONNECTOR_CN11_D19	GPIO_PE13
#define HEADER_CONNECTOR_CN11_D20	GPIO_PE14
#define HEADER_CONNECTOR_CN11_D21	GPIO_PD11
#define HEADER_CONNECTOR_CN11_D22	GPIO_PH8
#define HEADER_CONNECTOR_CN11_D23	GPIO_PD12
#define HEADER_CONNECTOR_CN11_D24	GPIO_PH10
#define HEADER_CONNECTOR_CN11_D25	GPIO_PG5
#define HEADER_CONNECTOR_CN11_D26	GPIO_PH9
#define HEADER_CONNECTOR_CN11_D27	GPIO_PH11
#define HEADER_CONNECTOR_CN11_D28	GPIO_PG4
#define HEADER_CONNECTOR_CN11_D29	// Pin not routed
#define HEADER_CONNECTOR_CN11_D30	// Pin not routed
#define HEADER_CONNECTOR_CN11_D31	GPIO_PD13
#define HEADER_CONNECTOR_CN11_D32	GPIO_PH12
#define HEADER_CONNECTOR_CN11_D33	GPIO_PG2
#define HEADER_CONNECTOR_CN11_D34	GPIO_PG3
#define HEADER_CONNECTOR_CN11_D35	GPIO_PD8
#define HEADER_CONNECTOR_CN11_D36	GPIO_PD10
#define HEADER_CONNECTOR_CN11_D37	GPIO_PD9
#define HEADER_CONNECTOR_CN11_D38	GPIO_PD15
#define HEADER_CONNECTOR_CN11_D39	GPIO_PD14
#define HEADER_CONNECTOR_CN11_D40	GPIO_PG8

#define HEADER_CONNECTOR_CN12_D1 	GPIO_PF5
#define HEADER_CONNECTOR_CN12_D2 	GPIO_PH2
#define HEADER_CONNECTOR_CN12_D3 	GPIO_PF4
#define HEADER_CONNECTOR_CN12_D4 	GPIO_PE5
#define HEADER_CONNECTOR_CN12_D5 	GPIO_PF3
#define HEADER_CONNECTOR_CN12_D6 	GPIO_PD6
#define HEADER_CONNECTOR_CN12_D7 	GPIO_PE6
#define HEADER_CONNECTOR_CN12_D8 	GPIO_PF2
#define HEADER_CONNECTOR_CN12_D9 	// Pin not routed
#define HEADER_CONNECTOR_CN12_D10	// Pin not routed
#define HEADER_CONNECTOR_CN12_D11	GPIO_PE4
#define HEADER_CONNECTOR_CN12_D12	GPIO_PF1
#define HEADER_CONNECTOR_CN12_D13	GPIO_PE3
#define HEADER_CONNECTOR_CN12_D14	GPIO_PF0
#define HEADER_CONNECTOR_CN12_D15	GPIO_PI5
#define HEADER_CONNECTOR_CN12_D16	GPIO_PE2
#define HEADER_CONNECTOR_CN12_D17	GPIO_PI4
#define HEADER_CONNECTOR_CN12_D18	GPIO_PI7
#define HEADER_CONNECTOR_CN12_D19	GPIO_PG15
#define HEADER_CONNECTOR_CN12_D20	GPIO_PI9
#define HEADER_CONNECTOR_CN12_D21	GPIO_PI10
#define HEADER_CONNECTOR_CN12_D22	GPIO_PI6
#define HEADER_CONNECTOR_CN12_D23	GPIO_PE1
#define HEADER_CONNECTOR_CN12_D24	GPIO_PD7
#define HEADER_CONNECTOR_CN12_D25	GPIO_PE0
#define HEADER_CONNECTOR_CN12_D26	GPIO_PD5
#define HEADER_CONNECTOR_CN12_D27	GPIO_PG9
#define HEADER_CONNECTOR_CN12_D28	GPIO_PD4
#define HEADER_CONNECTOR_CN12_D29	// Pin not routed
#define HEADER_CONNECTOR_CN12_D30	// Pin not routed
#define HEADER_CONNECTOR_CN12_D31	GPIO_PD0
#define HEADER_CONNECTOR_CN12_D32	GPIO_PD1
#define HEADER_CONNECTOR_CN12_D33	GPIO_PI2
#define HEADER_CONNECTOR_CN12_D34	GPIO_PI3
#define HEADER_CONNECTOR_CN12_D35	GPIO_PI1
#define HEADER_CONNECTOR_CN12_D36	GPIO_PH15
#define HEADER_CONNECTOR_CN12_D37	GPIO_PI0
#define HEADER_CONNECTOR_CN12_D38	GPIO_PH14
#define HEADER_CONNECTOR_CN12_D39	GPIO_PH13
#define HEADER_CONNECTOR_CN12_D40	// Pin not routed

#define HEADER_CONNECTOR_CN15_D1 	// Pin not routed
#define HEADER_CONNECTOR_CN15_D2 	// Pin not routed
#define HEADER_CONNECTOR_CN15_D3 	GPIO_PB4
#define HEADER_CONNECTOR_CN15_D4 	// Pin not routed
#define HEADER_CONNECTOR_CN15_D5 	GPIO_PA15
#define HEADER_CONNECTOR_CN15_D6 	// Pin not routed
#define HEADER_CONNECTOR_CN15_D7 	GPIO_PA13
#define HEADER_CONNECTOR_CN15_D8 	// Pin not routed
#define HEADER_CONNECTOR_CN15_D9 	GPIO_PA14
#define HEADER_CONNECTOR_CN15_D10	// Pin not routed
#define HEADER_CONNECTOR_CN15_D11	// Pin not routed
#define HEADER_CONNECTOR_CN15_D12	// Pin not routed
#define HEADER_CONNECTOR_CN15_D13	GPIO_PB3
#define HEADER_CONNECTOR_CN15_D14	// Pin not routed
#define HEADER_CONNECTOR_CN15_D15	// Pin not routed
#define HEADER_CONNECTOR_CN15_D16	// Pin not routed
#define HEADER_CONNECTOR_CN15_D17	// Pin not routed
#define HEADER_CONNECTOR_CN15_D18	// Pin not routed
#define HEADER_CONNECTOR_CN15_D19	// Pin not routed
#define HEADER_CONNECTOR_CN15_D20	// Pin not routed

#define HEADER_CONNECTOR_CN17_D1 	GPIO_PC10
#define HEADER_CONNECTOR_CN17_D2 	GPIO_PC11
#define HEADER_CONNECTOR_CN17_D3 	GPIO_PD2
#define HEADER_CONNECTOR_CN17_D4 	// Pin not routed
#define HEADER_CONNECTOR_CN17_D5 	GPIO_PC12
#define HEADER_CONNECTOR_CN17_D6 	// Pin not routed
#define HEADER_CONNECTOR_CN17_D7 	GPIO_PC8
#define HEADER_CONNECTOR_CN17_D8 	GPIO_PC9
#define HEADER_CONNECTOR_CN17_D9 	// Pin not routed
#define HEADER_CONNECTOR_CN17_D10	// Pin not routed

#ifdef __cplusplus
}
#endif

#endif    // _BOARD_H_
// ------------------------------------------------------------------------- END
