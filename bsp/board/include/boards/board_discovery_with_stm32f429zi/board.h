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

#define BOARD_NAME "STM32F429ZI_DISCOVERY"

#include "hal_target.h"

// Mapping
#define HEADER_CONNECTOR_CN2_D1	// Pin not routed
#define HEADER_CONNECTOR_CN2_D2	PA14
#define HEADER_CONNECTOR_CN2_D3	// Pin not routed
#define HEADER_CONNECTOR_CN2_D4	PA13
#define HEADER_CONNECTOR_CN2_D5	// Pin not routed
#define HEADER_CONNECTOR_CN2_D6	PB3

#define HEADER_CONNECTOR_CN3_D1	PC9
#define HEADER_CONNECTOR_CN3_D2	// Pin not routed
#define HEADER_CONNECTOR_CN3_D3	PA8
#define HEADER_CONNECTOR_CN3_D4	PA7
#define HEADER_CONNECTOR_CN3_D5	// Pin not routed
#define HEADER_CONNECTOR_CN3_D6	// Pin not routed
#define HEADER_CONNECTOR_CN3_D7	// Pin not routed
#define HEADER_CONNECTOR_CN3_D8	// Pin not routed

#define HEADER_CONNECTOR_CN6_D1	PB13
#define HEADER_CONNECTOR_CN6_D2	PB14
#define HEADER_CONNECTOR_CN6_D3	PB15
#define HEADER_CONNECTOR_CN6_D4	PB12
#define HEADER_CONNECTOR_CN6_D5	// Pin not routed

#define HEADER_CONNECTOR_P1_D1 	// Pin not routed
#define HEADER_CONNECTOR_P1_D2 	// Pin not routed
#define HEADER_CONNECTOR_P1_D3 	PF4
#define HEADER_CONNECTOR_P1_D4 	PF5
#define HEADER_CONNECTOR_P1_D5 	PF2
#define HEADER_CONNECTOR_P1_D6 	PF3
#define HEADER_CONNECTOR_P1_D7 	PF0
#define HEADER_CONNECTOR_P1_D8 	PF1
#define HEADER_CONNECTOR_P1_D9 	PC14
#define HEADER_CONNECTOR_P1_D10	PC15
#define HEADER_CONNECTOR_P1_D11	PE6
#define HEADER_CONNECTOR_P1_D12	PC13
#define HEADER_CONNECTOR_P1_D13	PE4
#define HEADER_CONNECTOR_P1_D14	PE5
#define HEADER_CONNECTOR_P1_D15	PE2
#define HEADER_CONNECTOR_P1_D16	PE3
#define HEADER_CONNECTOR_P1_D17	PE0
#define HEADER_CONNECTOR_P1_D18	PE1
#define HEADER_CONNECTOR_P1_D19	PB8
#define HEADER_CONNECTOR_P1_D20	PB9
#define HEADER_CONNECTOR_P1_D21	// Pin not routed
#define HEADER_CONNECTOR_P1_D22	// Pin not routed
#define HEADER_CONNECTOR_P1_D23	PB6
#define HEADER_CONNECTOR_P1_D24	PB7
#define HEADER_CONNECTOR_P1_D25	PB4
#define HEADER_CONNECTOR_P1_D26	PB5
#define HEADER_CONNECTOR_P1_D27	PG15
#define HEADER_CONNECTOR_P1_D28	PB3
#define HEADER_CONNECTOR_P1_D29	PG13
#define HEADER_CONNECTOR_P1_D30	PG14
#define HEADER_CONNECTOR_P1_D31	PG11
#define HEADER_CONNECTOR_P1_D32	PG12
#define HEADER_CONNECTOR_P1_D33	PG9
#define HEADER_CONNECTOR_P1_D34	PG10
#define HEADER_CONNECTOR_P1_D35	PD7
#define HEADER_CONNECTOR_P1_D36	PD6
#define HEADER_CONNECTOR_P1_D37	PD5
#define HEADER_CONNECTOR_P1_D38	PD4
#define HEADER_CONNECTOR_P1_D39	PD3
#define HEADER_CONNECTOR_P1_D40	PD2
#define HEADER_CONNECTOR_P1_D41	PD1
#define HEADER_CONNECTOR_P1_D42	PD0
#define HEADER_CONNECTOR_P1_D43	PC12
#define HEADER_CONNECTOR_P1_D44	PC11
#define HEADER_CONNECTOR_P1_D45	PC10
#define HEADER_CONNECTOR_P1_D46	PA15
#define HEADER_CONNECTOR_P1_D47	PA14
#define HEADER_CONNECTOR_P1_D48	PA13
#define HEADER_CONNECTOR_P1_D49	PA12
#define HEADER_CONNECTOR_P1_D50	PA11
#define HEADER_CONNECTOR_P1_D51	PA10
#define HEADER_CONNECTOR_P1_D52	PA9
#define HEADER_CONNECTOR_P1_D53	PA8
#define HEADER_CONNECTOR_P1_D54	PC9
#define HEADER_CONNECTOR_P1_D55	PC8
#define HEADER_CONNECTOR_P1_D56	PC7
#define HEADER_CONNECTOR_P1_D57	PC6
#define HEADER_CONNECTOR_P1_D58	PG8
#define HEADER_CONNECTOR_P1_D59	PG7
#define HEADER_CONNECTOR_P1_D60	PG6
#define HEADER_CONNECTOR_P1_D61	PG5
#define HEADER_CONNECTOR_P1_D62	PG4
#define HEADER_CONNECTOR_P1_D63	// Pin not routed
#define HEADER_CONNECTOR_P1_D64	// Pin not routed

#define HEADER_CONNECTOR_P2_D1 	// Pin not routed
#define HEADER_CONNECTOR_P2_D2 	// Pin not routed
#define HEADER_CONNECTOR_P2_D3 	PF6
#define HEADER_CONNECTOR_P2_D4 	// Pin not routed
#define HEADER_CONNECTOR_P2_D5 	PF8
#define HEADER_CONNECTOR_P2_D6 	PF7
#define HEADER_CONNECTOR_P2_D7 	PF10
#define HEADER_CONNECTOR_P2_D8 	PF9
#define HEADER_CONNECTOR_P2_D9 	PH1
#define HEADER_CONNECTOR_P2_D10	PH0
#define HEADER_CONNECTOR_P2_D11	// Pin not routed
#define HEADER_CONNECTOR_P2_D12	// Pin not routed
#define HEADER_CONNECTOR_P2_D13	PC1
#define HEADER_CONNECTOR_P2_D14	PC0
#define HEADER_CONNECTOR_P2_D15	PC3
#define HEADER_CONNECTOR_P2_D16	PC2
#define HEADER_CONNECTOR_P2_D17	PA1
#define HEADER_CONNECTOR_P2_D18	PA0
#define HEADER_CONNECTOR_P2_D19	PA3
#define HEADER_CONNECTOR_P2_D20	PA2
#define HEADER_CONNECTOR_P2_D21	PA5
#define HEADER_CONNECTOR_P2_D22	PA4
#define HEADER_CONNECTOR_P2_D23	PA7
#define HEADER_CONNECTOR_P2_D24	PA6
#define HEADER_CONNECTOR_P2_D25	PC5
#define HEADER_CONNECTOR_P2_D26	PC4
#define HEADER_CONNECTOR_P2_D27	PB1
#define HEADER_CONNECTOR_P2_D28	PB0
#define HEADER_CONNECTOR_P2_D29	// Pin not routed
#define HEADER_CONNECTOR_P2_D30	PB2
#define HEADER_CONNECTOR_P2_D31	PF12
#define HEADER_CONNECTOR_P2_D32	PF11
#define HEADER_CONNECTOR_P2_D33	PF14
#define HEADER_CONNECTOR_P2_D34	PF13
#define HEADER_CONNECTOR_P2_D35	PG0
#define HEADER_CONNECTOR_P2_D36	PF15
#define HEADER_CONNECTOR_P2_D37	PE7
#define HEADER_CONNECTOR_P2_D38	PG1
#define HEADER_CONNECTOR_P2_D39	PE9
#define HEADER_CONNECTOR_P2_D40	PE8
#define HEADER_CONNECTOR_P2_D41	PE11
#define HEADER_CONNECTOR_P2_D42	PE10
#define HEADER_CONNECTOR_P2_D43	PE13
#define HEADER_CONNECTOR_P2_D44	PE12
#define HEADER_CONNECTOR_P2_D45	PE15
#define HEADER_CONNECTOR_P2_D46	PE14
#define HEADER_CONNECTOR_P2_D47	PB11
#define HEADER_CONNECTOR_P2_D48	PB10
#define HEADER_CONNECTOR_P2_D49	PB13
#define HEADER_CONNECTOR_P2_D50	PB12
#define HEADER_CONNECTOR_P2_D51	// Pin not routed
#define HEADER_CONNECTOR_P2_D52	// Pin not routed
#define HEADER_CONNECTOR_P2_D53	PD9
#define HEADER_CONNECTOR_P2_D54	PD8
#define HEADER_CONNECTOR_P2_D55	PD11
#define HEADER_CONNECTOR_P2_D56	PD10
#define HEADER_CONNECTOR_P2_D57	PD13
#define HEADER_CONNECTOR_P2_D58	PD12
#define HEADER_CONNECTOR_P2_D59	PD15
#define HEADER_CONNECTOR_P2_D60	PD14
#define HEADER_CONNECTOR_P2_D61	PG3
#define HEADER_CONNECTOR_P2_D62	PG2
#define HEADER_CONNECTOR_P2_D63	// Pin not routed

#ifdef __cplusplus
}
#endif

#endif    // _BOARD_H_
// ------------------------------------------------------------------------- END
