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

#define BOARD_NAME "STM32G081RB-Eval"

#include "hal_target.h"

// Mapping
#define HEADER_CONNECTOR_CN1_D1  	PB12
#define HEADER_CONNECTOR_CN1_D2  	// Pin not routed
#define HEADER_CONNECTOR_CN1_D3  	PA8
#define HEADER_CONNECTOR_CN1_D4  	// Pin not routed
#define HEADER_CONNECTOR_CN1_D5  	PD2
#define HEADER_CONNECTOR_CN1_D6  	// Pin not routed
#define HEADER_CONNECTOR_CN1_D7  	PA9
#define HEADER_CONNECTOR_CN1_D8  	// Pin not routed
#define HEADER_CONNECTOR_CN1_D9  	PD3
#define HEADER_CONNECTOR_CN1_D10 	// Pin not routed
#define HEADER_CONNECTOR_CN1_D11 	PA10
#define HEADER_CONNECTOR_CN1_D12 	// Pin not routed
#define HEADER_CONNECTOR_CN1_D13 	PD4
#define HEADER_CONNECTOR_CN1_D14 	PA1
#define HEADER_CONNECTOR_CN1_D15 	PA2
#define HEADER_CONNECTOR_CN1_D16 	// Pin not routed
#define HEADER_CONNECTOR_CN1_D17 	PA6
#define HEADER_CONNECTOR_CN1_D18 	// Pin not routed
#define HEADER_CONNECTOR_CN1_D19 	PB10
#define HEADER_CONNECTOR_CN1_D20 	// Pin not routed
#define HEADER_CONNECTOR_CN1_D21 	PB9
#define HEADER_CONNECTOR_CN1_D22 	// Pin not routed
#define HEADER_CONNECTOR_CN1_D23 	PB15
#define HEADER_CONNECTOR_CN1_D24 	// Pin not routed
#define HEADER_CONNECTOR_CN1_D25 	// Pin not routed
#define HEADER_CONNECTOR_CN1_D26 	PA3
#define HEADER_CONNECTOR_CN1_D27 	PC1
#define HEADER_CONNECTOR_CN1_D28 	// Pin not routed
#define HEADER_CONNECTOR_CN1_D29 	PB1
#define HEADER_CONNECTOR_CN1_D30 	// Pin not routed
#define HEADER_CONNECTOR_CN1_D31 	PC6
#define HEADER_CONNECTOR_CN1_D32 	// Pin not routed
#define HEADER_CONNECTOR_CN1_D33 	PB5
#define HEADER_CONNECTOR_CN1_D34 	PB0

#define HEADER_CONNECTOR_CN2_D1  	PB7
#define HEADER_CONNECTOR_CN2_D2  	// Pin not routed
#define HEADER_CONNECTOR_CN2_D3  	PB6
#define HEADER_CONNECTOR_CN2_D4  	PC0
#define HEADER_CONNECTOR_CN2_D5  	// Pin not routed
#define HEADER_CONNECTOR_CN2_D6  	// Pin not routed
#define HEADER_CONNECTOR_CN2_D7  	// Pin not routed
#define HEADER_CONNECTOR_CN2_D8  	// Pin not routed

#define HEADER_CONNECTOR_CN4_D1  	PA1
#define HEADER_CONNECTOR_CN4_D2  	PA15
#define HEADER_CONNECTOR_CN4_D3  	PB6
#define HEADER_CONNECTOR_CN4_D4  	PB7
#define HEADER_CONNECTOR_CN4_D5  	// Pin not routed
#define HEADER_CONNECTOR_CN4_D6  	// Pin not routed
#define HEADER_CONNECTOR_CN4_D7  	PC6
#define HEADER_CONNECTOR_CN4_D8  	PB13
#define HEADER_CONNECTOR_CN4_D9  	PB14
#define HEADER_CONNECTOR_CN4_D10 	PB1
#define HEADER_CONNECTOR_CN4_D11 	PB10
#define HEADER_CONNECTOR_CN4_D12 	PA3
#define HEADER_CONNECTOR_CN4_D13 	PB12
#define HEADER_CONNECTOR_CN4_D14 	// Pin not routed
#define HEADER_CONNECTOR_CN4_D15 	PB11
#define HEADER_CONNECTOR_CN4_D16 	// Pin not routed
#define HEADER_CONNECTOR_CN4_D17 	// Pin not routed
#define HEADER_CONNECTOR_CN4_D18 	// Pin not routed

#define HEADER_CONNECTOR_CN5_D1  	// Pin not routed
#define HEADER_CONNECTOR_CN5_D2  	// Pin not routed
#define HEADER_CONNECTOR_CN5_D3  	// Pin not routed
#define HEADER_CONNECTOR_CN5_D4  	// Pin not routed
#define HEADER_CONNECTOR_CN5_D5  	// Pin not routed
#define HEADER_CONNECTOR_CN5_D6  	// Pin not routed
#define HEADER_CONNECTOR_CN5_D7  	PB9
#define HEADER_CONNECTOR_CN5_D8  	PA2
#define HEADER_CONNECTOR_CN5_D9  	PB0
#define HEADER_CONNECTOR_CN5_D10 	// Pin not routed
#define HEADER_CONNECTOR_CN5_D11 	PB5
#define HEADER_CONNECTOR_CN5_D12 	PC1
#define HEADER_CONNECTOR_CN5_D13 	PD0
#define HEADER_CONNECTOR_CN5_D14 	PD2
#define HEADER_CONNECTOR_CN5_D15 	PD3
#define HEADER_CONNECTOR_CN5_D16 	// Pin not routed
#define HEADER_CONNECTOR_CN5_D17 	// Pin not routed
#define HEADER_CONNECTOR_CN5_D18 	// Pin not routed

#define HEADER_CONNECTOR_CN9_D1  	PD8
#define HEADER_CONNECTOR_CN9_D2  	PD9
#define HEADER_CONNECTOR_CN9_D3  	PC7
#define HEADER_CONNECTOR_CN9_D4  	PA11
#define HEADER_CONNECTOR_CN9_D5  	PA12
#define HEADER_CONNECTOR_CN9_D6  	PC8
#define HEADER_CONNECTOR_CN9_D7  	PC9
#define HEADER_CONNECTOR_CN9_D8  	PD1
#define HEADER_CONNECTOR_CN9_D9  	PD5
#define HEADER_CONNECTOR_CN9_D10 	// Pin not routed
#define HEADER_CONNECTOR_CN9_D11 	PD6
#define HEADER_CONNECTOR_CN9_D12 	PC5
#define HEADER_CONNECTOR_CN9_D13 	PC4
#define HEADER_CONNECTOR_CN9_D14 	PB4
#define HEADER_CONNECTOR_CN9_D15 	PC10
#define HEADER_CONNECTOR_CN9_D16 	PC11
#define HEADER_CONNECTOR_CN9_D17 	// Pin not routed
#define HEADER_CONNECTOR_CN9_D18 	PC15
#define HEADER_CONNECTOR_CN9_D19 	PC14
#define HEADER_CONNECTOR_CN9_D20 	// Pin not routed
#define HEADER_CONNECTOR_CN9_D21 	PC13
#define HEADER_CONNECTOR_CN9_D22 	// Pin not routed

#define HEADER_CONNECTOR_CN10_D1 	PA7
#define HEADER_CONNECTOR_CN10_D2 	PB2
#define HEADER_CONNECTOR_CN10_D3 	PA5
#define HEADER_CONNECTOR_CN10_D4 	PA6
#define HEADER_CONNECTOR_CN10_D5 	PA13
#define HEADER_CONNECTOR_CN10_D6 	PA4
#define HEADER_CONNECTOR_CN10_D7 	PB8
#define HEADER_CONNECTOR_CN10_D8 	PB3
#define HEADER_CONNECTOR_CN10_D9 	PA0
#define HEADER_CONNECTOR_CN10_D10	// Pin not routed
#define HEADER_CONNECTOR_CN10_D11	PC2
#define HEADER_CONNECTOR_CN10_D12	PC0
#define HEADER_CONNECTOR_CN10_D13	PF1
#define HEADER_CONNECTOR_CN10_D14	PC3
#define HEADER_CONNECTOR_CN10_D15	PF0
#define HEADER_CONNECTOR_CN10_D16	PC12
#define HEADER_CONNECTOR_CN10_D17	// Pin not routed
#define HEADER_CONNECTOR_CN10_D18	PF2
#define HEADER_CONNECTOR_CN10_D19	PA14
#define HEADER_CONNECTOR_CN10_D20	PF3
#define HEADER_CONNECTOR_CN10_D21	// Pin not routed
#define HEADER_CONNECTOR_CN10_D22	PF4

#define HEADER_CONNECTOR_CN11_D1 	// Pin not routed
#define HEADER_CONNECTOR_CN11_D2 	// Pin not routed
#define HEADER_CONNECTOR_CN11_D3 	// Pin not routed
#define HEADER_CONNECTOR_CN11_D4 	// Pin not routed
#define HEADER_CONNECTOR_CN11_D5 	// Pin not routed
#define HEADER_CONNECTOR_CN11_D6 	// Pin not routed
#define HEADER_CONNECTOR_CN11_D7 	PA12
#define HEADER_CONNECTOR_CN11_D8 	PA11
#define HEADER_CONNECTOR_CN11_D9 	// Pin not routed

#define HEADER_CONNECTOR_CN12_D1 	// Pin not routed
#define HEADER_CONNECTOR_CN12_D2 	// Pin not routed
#define HEADER_CONNECTOR_CN12_D3 	// Pin not routed
#define HEADER_CONNECTOR_CN12_D4 	// Pin not routed
#define HEADER_CONNECTOR_CN12_D5 	// Pin not routed
#define HEADER_CONNECTOR_CN12_D6 	// Pin not routed
#define HEADER_CONNECTOR_CN12_D7 	PA13
#define HEADER_CONNECTOR_CN12_D8 	// Pin not routed
#define HEADER_CONNECTOR_CN12_D9 	PA14
#define HEADER_CONNECTOR_CN12_D10	// Pin not routed
#define HEADER_CONNECTOR_CN12_D11	// Pin not routed
#define HEADER_CONNECTOR_CN12_D12	// Pin not routed
#define HEADER_CONNECTOR_CN12_D13	// Pin not routed
#define HEADER_CONNECTOR_CN12_D14	// Pin not routed
#define HEADER_CONNECTOR_CN12_D15	// Pin not routed
#define HEADER_CONNECTOR_CN12_D16	// Pin not routed
#define HEADER_CONNECTOR_CN12_D17	// Pin not routed
#define HEADER_CONNECTOR_CN12_D18	// Pin not routed
#define HEADER_CONNECTOR_CN12_D19	// Pin not routed
#define HEADER_CONNECTOR_CN12_D20	// Pin not routed

#define HEADER_CONNECTOR_CN13_D1 	// Pin not routed
#define HEADER_CONNECTOR_CN13_D2 	PA13
#define HEADER_CONNECTOR_CN13_D3 	// Pin not routed
#define HEADER_CONNECTOR_CN13_D4 	PA14
#define HEADER_CONNECTOR_CN13_D5 	// Pin not routed
#define HEADER_CONNECTOR_CN13_D6 	// Pin not routed
#define HEADER_CONNECTOR_CN13_D7 	// Pin not routed
#define HEADER_CONNECTOR_CN13_D8 	// Pin not routed
#define HEADER_CONNECTOR_CN13_D9 	// Pin not routed
#define HEADER_CONNECTOR_CN13_D10	// Pin not routed

#ifdef __cplusplus
}
#endif

#endif    // _BOARD_H_
// ------------------------------------------------------------------------- END
