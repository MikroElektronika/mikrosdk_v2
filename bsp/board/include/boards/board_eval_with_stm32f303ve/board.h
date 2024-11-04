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
#define HEADER_CONNECTOR_CN1_D1  	PA10
#define HEADER_CONNECTOR_CN1_D2  	// Pin not routed
#define HEADER_CONNECTOR_CN1_D3  	PF6
#define HEADER_CONNECTOR_CN1_D4  	PE14
#define HEADER_CONNECTOR_CN1_D5  	// Pin not routed
#define HEADER_CONNECTOR_CN1_D6  	// Pin not routed
#define HEADER_CONNECTOR_CN1_D7  	// Pin not routed
#define HEADER_CONNECTOR_CN1_D8  	// Pin not routed

#define HEADER_CONNECTOR_CN2_D1  	PE15
#define HEADER_CONNECTOR_CN2_D2  	// Pin not routed
#define HEADER_CONNECTOR_CN2_D3  	PE9
#define HEADER_CONNECTOR_CN2_D4  	// Pin not routed
#define HEADER_CONNECTOR_CN2_D5  	PE8
#define HEADER_CONNECTOR_CN2_D6  	// Pin not routed
#define HEADER_CONNECTOR_CN2_D7  	PE11
#define HEADER_CONNECTOR_CN2_D8  	// Pin not routed
#define HEADER_CONNECTOR_CN2_D9  	PE10
#define HEADER_CONNECTOR_CN2_D10 	// Pin not routed
#define HEADER_CONNECTOR_CN2_D11 	PE13
#define HEADER_CONNECTOR_CN2_D12 	// Pin not routed
#define HEADER_CONNECTOR_CN2_D13 	PE12
#define HEADER_CONNECTOR_CN2_D14 	PA0
#define HEADER_CONNECTOR_CN2_D15 	// Pin not routed
#define HEADER_CONNECTOR_CN2_D16 	// Pin not routed
#define HEADER_CONNECTOR_CN2_D17 	// Pin not routed
#define HEADER_CONNECTOR_CN2_D18 	// Pin not routed
#define HEADER_CONNECTOR_CN2_D19 	// Pin not routed
#define HEADER_CONNECTOR_CN2_D20 	// Pin not routed
#define HEADER_CONNECTOR_CN2_D21 	PE4
#define HEADER_CONNECTOR_CN2_D22 	// Pin not routed
#define HEADER_CONNECTOR_CN2_D23 	PE5
#define HEADER_CONNECTOR_CN2_D24 	PD8
#define HEADER_CONNECTOR_CN2_D25 	// Pin not routed
#define HEADER_CONNECTOR_CN2_D26 	// Pin not routed
#define HEADER_CONNECTOR_CN2_D27 	PE2
#define HEADER_CONNECTOR_CN2_D28 	// Pin not routed
#define HEADER_CONNECTOR_CN2_D29 	PE3
#define HEADER_CONNECTOR_CN2_D30 	PD2
#define HEADER_CONNECTOR_CN2_D31 	PD3
#define HEADER_CONNECTOR_CN2_D32 	PD9
#define HEADER_CONNECTOR_CN2_D33 	PD4
#define HEADER_CONNECTOR_CN2_D34 	PD7

#define HEADER_CONNECTOR_CN4_D1  	PB7
#define HEADER_CONNECTOR_CN4_D2  	// Pin not routed
#define HEADER_CONNECTOR_CN4_D3  	PC6
#define HEADER_CONNECTOR_CN4_D4  	// Pin not routed
#define HEADER_CONNECTOR_CN4_D5  	PC10
#define HEADER_CONNECTOR_CN4_D6  	// Pin not routed
#define HEADER_CONNECTOR_CN4_D7  	PC7
#define HEADER_CONNECTOR_CN4_D8  	// Pin not routed
#define HEADER_CONNECTOR_CN4_D9  	PC11
#define HEADER_CONNECTOR_CN4_D10 	// Pin not routed
#define HEADER_CONNECTOR_CN4_D11 	PC8
#define HEADER_CONNECTOR_CN4_D12 	// Pin not routed
#define HEADER_CONNECTOR_CN4_D13 	PC12
#define HEADER_CONNECTOR_CN4_D14 	PC1
#define HEADER_CONNECTOR_CN4_D15 	// Pin not routed
#define HEADER_CONNECTOR_CN4_D16 	// Pin not routed
#define HEADER_CONNECTOR_CN4_D17 	// Pin not routed
#define HEADER_CONNECTOR_CN4_D18 	// Pin not routed
#define HEADER_CONNECTOR_CN4_D19 	// Pin not routed
#define HEADER_CONNECTOR_CN4_D20 	// Pin not routed
#define HEADER_CONNECTOR_CN4_D21 	PD15
#define HEADER_CONNECTOR_CN4_D22 	// Pin not routed
#define HEADER_CONNECTOR_CN4_D23 	PF10
#define HEADER_CONNECTOR_CN4_D24 	PD8
#define HEADER_CONNECTOR_CN4_D25 	// Pin not routed
#define HEADER_CONNECTOR_CN4_D26 	PF2
#define HEADER_CONNECTOR_CN4_D27 	PE2
#define HEADER_CONNECTOR_CN4_D28 	// Pin not routed
#define HEADER_CONNECTOR_CN4_D29 	PE3
#define HEADER_CONNECTOR_CN4_D30 	PD2
#define HEADER_CONNECTOR_CN4_D31 	PB6
#define HEADER_CONNECTOR_CN4_D32 	PD9
#define HEADER_CONNECTOR_CN4_D33 	PD13
#define HEADER_CONNECTOR_CN4_D34 	PB8

#define HEADER_CONNECTOR_CN6_D1  	// Pin not routed
#define HEADER_CONNECTOR_CN6_D2  	PC6
#define HEADER_CONNECTOR_CN6_D3  	PC7
#define HEADER_CONNECTOR_CN6_D4  	PC8
#define HEADER_CONNECTOR_CN6_D5  	PC9
#define HEADER_CONNECTOR_CN6_D6  	PA8
#define HEADER_CONNECTOR_CN6_D7  	PA10
#define HEADER_CONNECTOR_CN6_D8  	PA9
#define HEADER_CONNECTOR_CN6_D9  	PA11
#define HEADER_CONNECTOR_CN6_D10 	// Pin not routed
#define HEADER_CONNECTOR_CN6_D11 	PC14
#define HEADER_CONNECTOR_CN6_D12 	PA12
#define HEADER_CONNECTOR_CN6_D13 	PA13
#define HEADER_CONNECTOR_CN6_D14 	PF6
#define HEADER_CONNECTOR_CN6_D15 	PC15
#define HEADER_CONNECTOR_CN6_D16 	PA14
#define HEADER_CONNECTOR_CN6_D17 	PA15
#define HEADER_CONNECTOR_CN6_D18 	PC10
#define HEADER_CONNECTOR_CN6_D19 	// Pin not routed
#define HEADER_CONNECTOR_CN6_D20 	PC11
#define HEADER_CONNECTOR_CN6_D21 	PD0
#define HEADER_CONNECTOR_CN6_D22 	PC12
#define HEADER_CONNECTOR_CN6_D23 	PD2
#define HEADER_CONNECTOR_CN6_D24 	PD1
#define HEADER_CONNECTOR_CN6_D25 	PD4
#define HEADER_CONNECTOR_CN6_D26 	PD3
#define HEADER_CONNECTOR_CN6_D27 	PD6
#define HEADER_CONNECTOR_CN6_D28 	PD5
#define HEADER_CONNECTOR_CN6_D29 	PD7
#define HEADER_CONNECTOR_CN6_D30 	// Pin not routed
#define HEADER_CONNECTOR_CN6_D31 	PB4
#define HEADER_CONNECTOR_CN6_D32 	PB3
#define HEADER_CONNECTOR_CN6_D33 	PB6
#define HEADER_CONNECTOR_CN6_D34 	PB5
#define HEADER_CONNECTOR_CN6_D35 	PB8
#define HEADER_CONNECTOR_CN6_D36 	PB7
#define HEADER_CONNECTOR_CN6_D37 	PE0
#define HEADER_CONNECTOR_CN6_D38 	PB9
#define HEADER_CONNECTOR_CN6_D39 	// Pin not routed
#define HEADER_CONNECTOR_CN6_D40 	PE1
#define HEADER_CONNECTOR_CN6_D41 	PE3
#define HEADER_CONNECTOR_CN6_D42 	PE2
#define HEADER_CONNECTOR_CN6_D43 	PE5
#define HEADER_CONNECTOR_CN6_D44 	PE4
#define HEADER_CONNECTOR_CN6_D45 	PF9
#define HEADER_CONNECTOR_CN6_D46 	PE6
#define HEADER_CONNECTOR_CN6_D47 	PF10
#define HEADER_CONNECTOR_CN6_D48 	// Pin not routed
#define HEADER_CONNECTOR_CN6_D49 	// Pin not routed
#define HEADER_CONNECTOR_CN6_D50 	// Pin not routed
#define HEADER_CONNECTOR_CN6_D51 	PB11
#define HEADER_CONNECTOR_CN6_D52 	PB12

#define HEADER_CONNECTOR_CN7_D1  	// Pin not routed
#define HEADER_CONNECTOR_CN7_D2  	PD15
#define HEADER_CONNECTOR_CN7_D3  	PD14
#define HEADER_CONNECTOR_CN7_D4  	PD13
#define HEADER_CONNECTOR_CN7_D5  	PD11
#define HEADER_CONNECTOR_CN7_D6  	PD12
#define HEADER_CONNECTOR_CN7_D7  	PD9
#define HEADER_CONNECTOR_CN7_D8  	PD10
#define HEADER_CONNECTOR_CN7_D9  	PC13
#define HEADER_CONNECTOR_CN7_D10 	// Pin not routed
#define HEADER_CONNECTOR_CN7_D11 	// Pin not routed
#define HEADER_CONNECTOR_CN7_D12 	PD8
#define HEADER_CONNECTOR_CN7_D13 	PB15
#define HEADER_CONNECTOR_CN7_D14 	PB14
#define HEADER_CONNECTOR_CN7_D15 	PB13
#define HEADER_CONNECTOR_CN7_D16 	PB10
#define HEADER_CONNECTOR_CN7_D17 	PE15
#define HEADER_CONNECTOR_CN7_D18 	PE14
#define HEADER_CONNECTOR_CN7_D19 	// Pin not routed
#define HEADER_CONNECTOR_CN7_D20 	PE13
#define HEADER_CONNECTOR_CN7_D21 	PE12
#define HEADER_CONNECTOR_CN7_D22 	PE11
#define HEADER_CONNECTOR_CN7_D23 	PF0
#define HEADER_CONNECTOR_CN7_D24 	// Pin not routed
#define HEADER_CONNECTOR_CN7_D25 	PE10
#define HEADER_CONNECTOR_CN7_D26 	PF1
#define HEADER_CONNECTOR_CN7_D27 	PE9
#define HEADER_CONNECTOR_CN7_D28 	PE8
#define HEADER_CONNECTOR_CN7_D29 	PE7
#define HEADER_CONNECTOR_CN7_D30 	// Pin not routed
#define HEADER_CONNECTOR_CN7_D31 	PB2
#define HEADER_CONNECTOR_CN7_D32 	PB1
#define HEADER_CONNECTOR_CN7_D33 	PB0
#define HEADER_CONNECTOR_CN7_D34 	PC5
#define HEADER_CONNECTOR_CN7_D35 	PC4
#define HEADER_CONNECTOR_CN7_D36 	PA7
#define HEADER_CONNECTOR_CN7_D37 	PA6
#define HEADER_CONNECTOR_CN7_D38 	PA5
#define HEADER_CONNECTOR_CN7_D39 	// Pin not routed
#define HEADER_CONNECTOR_CN7_D40 	PA4
#define HEADER_CONNECTOR_CN7_D41 	// Pin not routed
#define HEADER_CONNECTOR_CN7_D42 	PA3
#define HEADER_CONNECTOR_CN7_D43 	PA2
#define HEADER_CONNECTOR_CN7_D44 	PA1
#define HEADER_CONNECTOR_CN7_D45 	PA0
#define HEADER_CONNECTOR_CN7_D46 	PF2
#define HEADER_CONNECTOR_CN7_D47 	PC3
#define HEADER_CONNECTOR_CN7_D48 	PC2
#define HEADER_CONNECTOR_CN7_D49 	PC1
#define HEADER_CONNECTOR_CN7_D50 	// Pin not routed
#define HEADER_CONNECTOR_CN7_D51 	PC0
#define HEADER_CONNECTOR_CN7_D52 	// Pin not routed

#define HEADER_CONNECTOR_CN8_D1  	// Pin not routed
#define HEADER_CONNECTOR_CN8_D2  	PE1
#define HEADER_CONNECTOR_CN8_D3  	PC4
#define HEADER_CONNECTOR_CN8_D4  	// Pin not routed
#define HEADER_CONNECTOR_CN8_D5  	// Pin not routed
#define HEADER_CONNECTOR_CN8_D6  	// Pin not routed
#define HEADER_CONNECTOR_CN8_D7  	// Pin not routed
#define HEADER_CONNECTOR_CN8_D8  	// Pin not routed
#define HEADER_CONNECTOR_CN8_D9  	// Pin not routed

#define HEADER_CONNECTOR_CN12_D1 	// Pin not routed
#define HEADER_CONNECTOR_CN12_D2 	PA11
#define HEADER_CONNECTOR_CN12_D3 	PA12
#define HEADER_CONNECTOR_CN12_D4 	// Pin not routed

#define HEADER_CONNECTOR_CN16_D1 	// Pin not routed
#define HEADER_CONNECTOR_CN16_D2 	PE15
#define HEADER_CONNECTOR_CN16_D3 	PB15
#define HEADER_CONNECTOR_CN16_D4 	// Pin not routed
#define HEADER_CONNECTOR_CN16_D5 	PF9
#define HEADER_CONNECTOR_CN16_D6 	// Pin not routed
#define HEADER_CONNECTOR_CN16_D7 	PB14
#define HEADER_CONNECTOR_CN16_D8 	// Pin not routed
#define HEADER_CONNECTOR_CN16_D9 	// Pin not routed
#define HEADER_CONNECTOR_CN16_D10	PC6

#ifdef __cplusplus
}
#endif

#endif    // _BOARD_H_
// ------------------------------------------------------------------------- END
