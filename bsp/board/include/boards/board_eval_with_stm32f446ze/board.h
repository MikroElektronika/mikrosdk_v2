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
** EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES
** OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT.
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

#define BOARD_NAME "STM32F446ZE-Eval"

#include "hal_target.h"

// Mapping
#define HEADER_CONNECTOR_CN3_D1     GPIO_PA6
#define HEADER_CONNECTOR_CN3_D2     // Pin not routed
#define HEADER_CONNECTOR_CN3_D3     GPIO_PC6
#define HEADER_CONNECTOR_CN3_D4     // Pin not routed
#define HEADER_CONNECTOR_CN3_D5     GPIO_PA5
#define HEADER_CONNECTOR_CN3_D6     // Pin not routed
#define HEADER_CONNECTOR_CN3_D7     GPIO_PC7
#define HEADER_CONNECTOR_CN3_D8     // Pin not routed
#define HEADER_CONNECTOR_CN3_D9     GPIO_PB0
#define HEADER_CONNECTOR_CN3_D10    // Pin not routed
#define HEADER_CONNECTOR_CN3_D11    GPIO_PC8
#define HEADER_CONNECTOR_CN3_D12    // Pin not routed
#define HEADER_CONNECTOR_CN3_D13    GPIO_PB1
#define HEADER_CONNECTOR_CN3_D14    GPIO_PC0
#define HEADER_CONNECTOR_CN3_D15    GPIO_PA1
#define HEADER_CONNECTOR_CN3_D16    // Pin not routed
#define HEADER_CONNECTOR_CN3_D17    GPIO_PA2
#define HEADER_CONNECTOR_CN3_D18    // Pin not routed
#define HEADER_CONNECTOR_CN3_D19    GPIO_PA3
#define HEADER_CONNECTOR_CN3_D20    // Pin not routed
#define HEADER_CONNECTOR_CN3_D21    GPIO_PG6
#define HEADER_CONNECTOR_CN3_D22    // Pin not routed
#define HEADER_CONNECTOR_CN3_D23    GPIO_PD3
#define HEADER_CONNECTOR_CN3_D24    GPIO_PC2
#define HEADER_CONNECTOR_CN3_D25    // Pin not routed
#define HEADER_CONNECTOR_CN3_D26    GPIO_PC1
#define HEADER_CONNECTOR_CN3_D27    GPIO_PA8
#define HEADER_CONNECTOR_CN3_D28    // Pin not routed
#define HEADER_CONNECTOR_CN3_D29    GPIO_PA11
#define HEADER_CONNECTOR_CN3_D30    GPIO_PB12
#define HEADER_CONNECTOR_CN3_D31    GPIO_PB6
#define HEADER_CONNECTOR_CN3_D32    GPIO_PC3
#define HEADER_CONNECTOR_CN3_D33    GPIO_PB7
#define HEADER_CONNECTOR_CN3_D34    GPIO_PB8

#define HEADER_CONNECTOR_CN4_D1  	// Pin not routed
#define HEADER_CONNECTOR_CN4_D2  	// Pin not routed
#define HEADER_CONNECTOR_CN4_D3  	GPIO_PD2
#define HEADER_CONNECTOR_CN4_D4  	// Pin not routed
#define HEADER_CONNECTOR_CN4_D5  	GPIO_PC12
#define HEADER_CONNECTOR_CN4_D6  	// Pin not routed
#define HEADER_CONNECTOR_CN4_D7  	GPIO_PC8
#define HEADER_CONNECTOR_CN4_D8  	GPIO_PC9
#define HEADER_CONNECTOR_CN4_D9  	// Pin not routed
#define HEADER_CONNECTOR_CN4_D10 	// Pin not routed

#define HEADER_CONNECTOR_CN10_D1 	// Pin not routed
#define HEADER_CONNECTOR_CN10_D2 	// Pin not routed
#define HEADER_CONNECTOR_CN10_D3 	GPIO_PD12
#define HEADER_CONNECTOR_CN10_D4 	// Pin not routed
#define HEADER_CONNECTOR_CN10_D5 	GPIO_PD13
#define HEADER_CONNECTOR_CN10_D6 	GPIO_PB4
#define HEADER_CONNECTOR_CN10_D7 	GPIO_PG3
#define HEADER_CONNECTOR_CN10_D8 	GPIO_PB5
#define HEADER_CONNECTOR_CN10_D9 	GPIO_PC6
#define HEADER_CONNECTOR_CN10_D10	GPIO_PB7
#define HEADER_CONNECTOR_CN10_D11	// Pin not routed
#define HEADER_CONNECTOR_CN10_D12	// Pin not routed
#define HEADER_CONNECTOR_CN10_D13	GPIO_PA10
#define HEADER_CONNECTOR_CN10_D14	// Pin not routed
#define HEADER_CONNECTOR_CN10_D15	// Pin not routed
#define HEADER_CONNECTOR_CN10_D16	GPIO_PB8
#define HEADER_CONNECTOR_CN10_D17	GPIO_PA11
#define HEADER_CONNECTOR_CN10_D18	GPIO_PB9
#define HEADER_CONNECTOR_CN10_D19	GPIO_PA12
#define HEADER_CONNECTOR_CN10_D20	// Pin not routed
#define HEADER_CONNECTOR_CN10_D21	GPIO_PA13
#define HEADER_CONNECTOR_CN10_D22	GPIO_PC1
#define HEADER_CONNECTOR_CN10_D23	GPIO_PA14
#define HEADER_CONNECTOR_CN10_D24	// Pin not routed
#define HEADER_CONNECTOR_CN10_D25	GPIO_PA15
#define HEADER_CONNECTOR_CN10_D26	GPIO_PG11
#define HEADER_CONNECTOR_CN10_D27	GPIO_PG9
#define HEADER_CONNECTOR_CN10_D28	GPIO_PB3
#define HEADER_CONNECTOR_CN10_D29	GPIO_PG10
#define HEADER_CONNECTOR_CN10_D30	// Pin not routed
#define HEADER_CONNECTOR_CN10_D31	// Pin not routed
#define HEADER_CONNECTOR_CN10_D32	// Pin not routed

#define HEADER_CONNECTOR_CN11_D1 	// Pin not routed
#define HEADER_CONNECTOR_CN11_D2 	// Pin not routed
#define HEADER_CONNECTOR_CN11_D3 	GPIO_PD14
#define HEADER_CONNECTOR_CN11_D4 	GPIO_PD15
#define HEADER_CONNECTOR_CN11_D5 	// Pin not routed
#define HEADER_CONNECTOR_CN11_D6 	GPIO_PD1
#define HEADER_CONNECTOR_CN11_D7 	// Pin not routed
#define HEADER_CONNECTOR_CN11_D8 	// Pin not routed
#define HEADER_CONNECTOR_CN11_D9 	GPIO_PE7
#define HEADER_CONNECTOR_CN11_D10	GPIO_PE8
#define HEADER_CONNECTOR_CN11_D11	GPIO_PE9
#define HEADER_CONNECTOR_CN11_D12	GPIO_PE10
#define HEADER_CONNECTOR_CN11_D13	GPIO_PG6
#define HEADER_CONNECTOR_CN11_D14	GPIO_PF6
#define HEADER_CONNECTOR_CN11_D15	GPIO_PF9
#define HEADER_CONNECTOR_CN11_D16	GPIO_PD3
#define HEADER_CONNECTOR_CN11_D17	GPIO_PF7
#define HEADER_CONNECTOR_CN11_D18	GPIO_PF8
#define HEADER_CONNECTOR_CN11_D19	GPIO_PA7
#define HEADER_CONNECTOR_CN11_D20	GPIO_PE0
#define HEADER_CONNECTOR_CN11_D21	GPIO_PF11
#define HEADER_CONNECTOR_CN11_D22	GPIO_PG15
#define HEADER_CONNECTOR_CN11_D23	GPIO_PG4
#define HEADER_CONNECTOR_CN11_D24	GPIO_PC4
#define HEADER_CONNECTOR_CN11_D25	// Pin not routed
#define HEADER_CONNECTOR_CN11_D26	GPIO_PG5
#define HEADER_CONNECTOR_CN11_D27	// Pin not routed
#define HEADER_CONNECTOR_CN11_D28	GPIO_PF0
#define HEADER_CONNECTOR_CN11_D29	// Pin not routed
#define HEADER_CONNECTOR_CN11_D30	GPIO_PF2
#define HEADER_CONNECTOR_CN11_D31	// Pin not routed
#define HEADER_CONNECTOR_CN11_D32	// Pin not routed

#define HEADER_CONNECTOR_CN12_D1 	// Pin not routed
#define HEADER_CONNECTOR_CN12_D2 	// Pin not routed
#define HEADER_CONNECTOR_CN12_D3 	// Pin not routed
#define HEADER_CONNECTOR_CN12_D4 	GPIO_PD5
#define HEADER_CONNECTOR_CN12_D5 	// Pin not routed
#define HEADER_CONNECTOR_CN12_D6 	GPIO_PD4
#define HEADER_CONNECTOR_CN12_D7 	// Pin not routed
#define HEADER_CONNECTOR_CN12_D8 	// Pin not routed
#define HEADER_CONNECTOR_CN12_D9 	GPIO_PD9
#define HEADER_CONNECTOR_CN12_D10	GPIO_PD10
#define HEADER_CONNECTOR_CN12_D11	GPIO_PE15
#define HEADER_CONNECTOR_CN12_D12	GPIO_PD8
#define HEADER_CONNECTOR_CN12_D13	GPIO_PE13
#define HEADER_CONNECTOR_CN12_D14	GPIO_PE14
#define HEADER_CONNECTOR_CN12_D15	GPIO_PE11
#define HEADER_CONNECTOR_CN12_D16	GPIO_PE12
#define HEADER_CONNECTOR_CN12_D17	// Pin not routed
#define HEADER_CONNECTOR_CN12_D18	// Pin not routed
#define HEADER_CONNECTOR_CN12_D19	GPIO_PE1
#define HEADER_CONNECTOR_CN12_D20	GPIO_PD7
#define HEADER_CONNECTOR_CN12_D21	GPIO_PC5
#define HEADER_CONNECTOR_CN12_D22	GPIO_PG8
#define HEADER_CONNECTOR_CN12_D23	GPIO_PG1
#define HEADER_CONNECTOR_CN12_D24	GPIO_PG2
#define HEADER_CONNECTOR_CN12_D25	// Pin not routed
#define HEADER_CONNECTOR_CN12_D26	GPIO_PF14
#define HEADER_CONNECTOR_CN12_D27	// Pin not routed
#define HEADER_CONNECTOR_CN12_D28	GPIO_PF12
#define HEADER_CONNECTOR_CN12_D29	// Pin not routed
#define HEADER_CONNECTOR_CN12_D30	GPIO_PF4
#define HEADER_CONNECTOR_CN12_D31	// Pin not routed
#define HEADER_CONNECTOR_CN12_D32	// Pin not routed

#define HEADER_CONNECTOR_CN13_D1 	// Pin not routed
#define HEADER_CONNECTOR_CN13_D2 	// Pin not routed
#define HEADER_CONNECTOR_CN13_D3 	GPIO_PC13
#define HEADER_CONNECTOR_CN13_D4 	GPIO_PA2
#define HEADER_CONNECTOR_CN13_D5 	GPIO_PC14
#define HEADER_CONNECTOR_CN13_D6 	GPIO_PA3
#define HEADER_CONNECTOR_CN13_D7 	GPIO_PC15
#define HEADER_CONNECTOR_CN13_D8 	GPIO_PA4
#define HEADER_CONNECTOR_CN13_D9 	GPIO_PH0
#define HEADER_CONNECTOR_CN13_D10	GPIO_PA6
#define HEADER_CONNECTOR_CN13_D11	GPIO_PH1
#define HEADER_CONNECTOR_CN13_D12	GPIO_PA5
#define HEADER_CONNECTOR_CN13_D13	// Pin not routed
#define HEADER_CONNECTOR_CN13_D14	// Pin not routed
#define HEADER_CONNECTOR_CN13_D15	GPIO_PC0
#define HEADER_CONNECTOR_CN13_D16	GPIO_PB0
#define HEADER_CONNECTOR_CN13_D17	GPIO_PC2
#define HEADER_CONNECTOR_CN13_D18	GPIO_PB1
#define HEADER_CONNECTOR_CN13_D19	// Pin not routed
#define HEADER_CONNECTOR_CN13_D20	GPIO_PB10
#define HEADER_CONNECTOR_CN13_D21	// Pin not routed
#define HEADER_CONNECTOR_CN13_D22	// Pin not routed
#define HEADER_CONNECTOR_CN13_D23	// Pin not routed
#define HEADER_CONNECTOR_CN13_D24	GPIO_PB11
#define HEADER_CONNECTOR_CN13_D25	GPIO_PC3
#define HEADER_CONNECTOR_CN13_D26	GPIO_PB12
#define HEADER_CONNECTOR_CN13_D27	// Pin not routed
#define HEADER_CONNECTOR_CN13_D28	GPIO_PB13
#define HEADER_CONNECTOR_CN13_D29	GPIO_PA1
#define HEADER_CONNECTOR_CN13_D30	GPIO_PD11
#define HEADER_CONNECTOR_CN13_D31	// Pin not routed
#define HEADER_CONNECTOR_CN13_D32	// Pin not routed
#define HEADER_CONNECTOR_CN13_D33	// Pin not routed
#define HEADER_CONNECTOR_CN13_D34	// Pin not routed

#ifdef __cplusplus
}
#endif

#endif    // _BOARD_H_
// ------------------------------------------------------------------------- END
