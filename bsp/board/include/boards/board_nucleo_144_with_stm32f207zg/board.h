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

#define BOARD_NAME "Nucleo-F207ZG"

#include "hal_target.h"

// Mapping
#define HEADER_CONNECTOR_CN7_D1   	PC6
#define HEADER_CONNECTOR_CN7_D2   	PB8
#define HEADER_CONNECTOR_CN7_D3   	PB15
#define HEADER_CONNECTOR_CN7_D4   	PB9
#define HEADER_CONNECTOR_CN7_D5   	PB13
#define HEADER_CONNECTOR_CN7_D6   	// Pin not routed
#define HEADER_CONNECTOR_CN7_D7   	PB12
#define HEADER_CONNECTOR_CN7_D8   	// Pin not routed
#define HEADER_CONNECTOR_CN7_D9   	PA15
#define HEADER_CONNECTOR_CN7_D10  	PA5
#define HEADER_CONNECTOR_CN7_D11  	PC7
#define HEADER_CONNECTOR_CN7_D12  	PA6
#define HEADER_CONNECTOR_CN7_D13  	PB5
#define HEADER_CONNECTOR_CN7_D14  	PA7
#define HEADER_CONNECTOR_CN7_D15  	PB3
#define HEADER_CONNECTOR_CN7_D16  	PD14
#define HEADER_CONNECTOR_CN7_D17  	PA4
#define HEADER_CONNECTOR_CN7_D18  	PD15
#define HEADER_CONNECTOR_CN7_D19  	PB4
#define HEADER_CONNECTOR_CN7_D20  	PF12

#define HEADER_CONNECTOR_CN8_D1   	// Pin not routed
#define HEADER_CONNECTOR_CN8_D2   	PC8
#define HEADER_CONNECTOR_CN8_D3   	// Pin not routed
#define HEADER_CONNECTOR_CN8_D4   	PC9
#define HEADER_CONNECTOR_CN8_D5   	// Pin not routed
#define HEADER_CONNECTOR_CN8_D6   	PC10
#define HEADER_CONNECTOR_CN8_D7   	// Pin not routed
#define HEADER_CONNECTOR_CN8_D8   	PC11
#define HEADER_CONNECTOR_CN8_D9   	// Pin not routed
#define HEADER_CONNECTOR_CN8_D10  	PC12
#define HEADER_CONNECTOR_CN8_D11  	// Pin not routed
#define HEADER_CONNECTOR_CN8_D12  	PD2
#define HEADER_CONNECTOR_CN8_D13  	// Pin not routed
#define HEADER_CONNECTOR_CN8_D14  	PG2
#define HEADER_CONNECTOR_CN8_D15  	// Pin not routed
#define HEADER_CONNECTOR_CN8_D16  	PG3

#define HEADER_CONNECTOR_CN9_D1   	PA3
#define HEADER_CONNECTOR_CN9_D2   	PD7
#define HEADER_CONNECTOR_CN9_D3   	PC0
#define HEADER_CONNECTOR_CN9_D4   	PD6
#define HEADER_CONNECTOR_CN9_D5   	PC3
#define HEADER_CONNECTOR_CN9_D6   	PD5
#define HEADER_CONNECTOR_CN9_D7   	PF3
#define HEADER_CONNECTOR_CN9_D8   	PD4
#define HEADER_CONNECTOR_CN9_D9   	PB9
#define HEADER_CONNECTOR_CN9_D10  	PD3
#define HEADER_CONNECTOR_CN9_D11  	PB8
#define HEADER_CONNECTOR_CN9_D12  	// Pin not routed
#define HEADER_CONNECTOR_CN9_D13  	// Pin not routed
#define HEADER_CONNECTOR_CN9_D14  	PE2
#define HEADER_CONNECTOR_CN9_D15  	PA7
#define HEADER_CONNECTOR_CN9_D16  	PE4
#define HEADER_CONNECTOR_CN9_D17  	PF2
#define HEADER_CONNECTOR_CN9_D18  	PE5
#define HEADER_CONNECTOR_CN9_D19  	PF1
#define HEADER_CONNECTOR_CN9_D20  	PE6
#define HEADER_CONNECTOR_CN9_D21  	PF0
#define HEADER_CONNECTOR_CN9_D22  	PE3
#define HEADER_CONNECTOR_CN9_D23  	// Pin not routed
#define HEADER_CONNECTOR_CN9_D24  	PF8
#define HEADER_CONNECTOR_CN9_D25  	PD0
#define HEADER_CONNECTOR_CN9_D26  	PF7
#define HEADER_CONNECTOR_CN9_D27  	PD1
#define HEADER_CONNECTOR_CN9_D28  	PF9
#define HEADER_CONNECTOR_CN9_D29  	PG0
#define HEADER_CONNECTOR_CN9_D30  	PG1

#define HEADER_CONNECTOR_CN10_D1  	// Pin not routed
#define HEADER_CONNECTOR_CN10_D2  	PF13
#define HEADER_CONNECTOR_CN10_D3  	// Pin not routed
#define HEADER_CONNECTOR_CN10_D4  	PE9
#define HEADER_CONNECTOR_CN10_D5  	// Pin not routed
#define HEADER_CONNECTOR_CN10_D6  	PE11
#define HEADER_CONNECTOR_CN10_D7  	PB1
#define HEADER_CONNECTOR_CN10_D8  	PF14
#define HEADER_CONNECTOR_CN10_D9  	PC2
#define HEADER_CONNECTOR_CN10_D10 	PE13
#define HEADER_CONNECTOR_CN10_D11 	PF4
#define HEADER_CONNECTOR_CN10_D12 	PF15
#define HEADER_CONNECTOR_CN10_D13 	PB6
#define HEADER_CONNECTOR_CN10_D14 	PG14
#define HEADER_CONNECTOR_CN10_D15 	PB2
#define HEADER_CONNECTOR_CN10_D16 	PG9
#define HEADER_CONNECTOR_CN10_D17 	// Pin not routed
#define HEADER_CONNECTOR_CN10_D18 	PE8
#define HEADER_CONNECTOR_CN10_D19 	PD13
#define HEADER_CONNECTOR_CN10_D20 	PE7
#define HEADER_CONNECTOR_CN10_D21 	PD12
#define HEADER_CONNECTOR_CN10_D22 	// Pin not routed
#define HEADER_CONNECTOR_CN10_D23 	PD11
#define HEADER_CONNECTOR_CN10_D24 	PE10
#define HEADER_CONNECTOR_CN10_D25 	PE2
#define HEADER_CONNECTOR_CN10_D26 	PE12
#define HEADER_CONNECTOR_CN10_D27 	// Pin not routed
#define HEADER_CONNECTOR_CN10_D28 	PE14
#define HEADER_CONNECTOR_CN10_D29 	PA0
#define HEADER_CONNECTOR_CN10_D30 	PE15
#define HEADER_CONNECTOR_CN10_D31 	PB0
#define HEADER_CONNECTOR_CN10_D32 	PB10
#define HEADER_CONNECTOR_CN10_D33 	PE0
#define HEADER_CONNECTOR_CN10_D34 	PB11

#define HEADER_CONNECTOR_CN11_D1  	// Pin not routed
#define HEADER_CONNECTOR_CN11_D2  	// Pin not routed
#define HEADER_CONNECTOR_CN11_D3  	// Pin not routed
#define HEADER_CONNECTOR_CN11_D4  	// Pin not routed
#define HEADER_CONNECTOR_CN11_D5  	// Pin not routed
#define HEADER_CONNECTOR_CN11_D6  	// Pin not routed
#define HEADER_CONNECTOR_CN11_D7  	// Pin not routed
#define HEADER_CONNECTOR_CN11_D8  	// Pin not routed
#define HEADER_CONNECTOR_CN11_D9  	// Pin not routed
#define HEADER_CONNECTOR_CN11_D10 	// Pin not routed
#define HEADER_CONNECTOR_CN11_D11 	// Pin not routed
#define HEADER_CONNECTOR_CN11_D12 	// Pin not routed
#define HEADER_CONNECTOR_CN11_D13 	// Pin not routed
#define HEADER_CONNECTOR_CN11_D14 	// Pin not routed
#define HEADER_CONNECTOR_CN11_D15 	// Pin not routed
#define HEADER_CONNECTOR_CN11_D16 	// Pin not routed
#define HEADER_CONNECTOR_CN11_D17 	// Pin not routed
#define HEADER_CONNECTOR_CN11_D18 	// Pin not routed
#define HEADER_CONNECTOR_CN11_D19 	// Pin not routed
#define HEADER_CONNECTOR_CN11_D20 	// Pin not routed
#define HEADER_CONNECTOR_CN11_D21 	// Pin not routed
#define HEADER_CONNECTOR_CN11_D22 	// Pin not routed
#define HEADER_CONNECTOR_CN11_D23 	// Pin not routed
#define HEADER_CONNECTOR_CN11_D24 	// Pin not routed
#define HEADER_CONNECTOR_CN11_D25 	// Pin not routed
#define HEADER_CONNECTOR_CN11_D26 	// Pin not routed
#define HEADER_CONNECTOR_CN11_D27 	// Pin not routed
#define HEADER_CONNECTOR_CN11_D28 	// Pin not routed
#define HEADER_CONNECTOR_CN11_D29 	// Pin not routed
#define HEADER_CONNECTOR_CN11_D30 	// Pin not routed
#define HEADER_CONNECTOR_CN11_D31 	// Pin not routed
#define HEADER_CONNECTOR_CN11_D32 	// Pin not routed
#define HEADER_CONNECTOR_CN11_D33 	// Pin not routed
#define HEADER_CONNECTOR_CN11_D34 	// Pin not routed
#define HEADER_CONNECTOR_CN11_D35 	// Pin not routed
#define HEADER_CONNECTOR_CN11_D36 	// Pin not routed
#define HEADER_CONNECTOR_CN11_D37 	// Pin not routed
#define HEADER_CONNECTOR_CN11_D38 	// Pin not routed
#define HEADER_CONNECTOR_CN11_D39 	// Pin not routed
#define HEADER_CONNECTOR_CN11_D40 	// Pin not routed
#define HEADER_CONNECTOR_CN11_D41 	PD5
#define HEADER_CONNECTOR_CN11_D42 	PG2
#define HEADER_CONNECTOR_CN11_D43 	PD6
#define HEADER_CONNECTOR_CN11_D44 	PG3
#define HEADER_CONNECTOR_CN11_D45 	PD7
#define HEADER_CONNECTOR_CN11_D46 	PE2
#define HEADER_CONNECTOR_CN11_D47 	PE3
#define HEADER_CONNECTOR_CN11_D48 	PE4
#define HEADER_CONNECTOR_CN11_D49 	// Pin not routed
#define HEADER_CONNECTOR_CN11_D50 	PE5
#define HEADER_CONNECTOR_CN11_D51 	PH1
#define HEADER_CONNECTOR_CN11_D52 	PF2
#define HEADER_CONNECTOR_CN11_D53 	PH0
#define HEADER_CONNECTOR_CN11_D54 	PF8
#define HEADER_CONNECTOR_CN11_D55 	PD1
#define HEADER_CONNECTOR_CN11_D56 	PF9
#define HEADER_CONNECTOR_CN11_D57 	PD0
#define HEADER_CONNECTOR_CN11_D58 	PG1
#define HEADER_CONNECTOR_CN11_D59 	PG0
#define HEADER_CONNECTOR_CN11_D60 	// Pin not routed
#define HEADER_CONNECTOR_CN11_D61 	PE1
#define HEADER_CONNECTOR_CN11_D62 	PE6
#define HEADER_CONNECTOR_CN11_D63 	PG9
#define HEADER_CONNECTOR_CN11_D64 	PG15
#define HEADER_CONNECTOR_CN11_D65 	PG12
#define HEADER_CONNECTOR_CN11_D66 	PG10
#define HEADER_CONNECTOR_CN11_D67 	PH2
#define HEADER_CONNECTOR_CN11_D68 	PG13
#define HEADER_CONNECTOR_CN11_D69 	PD9
#define HEADER_CONNECTOR_CN11_D70 	PG11

#define HEADER_CONNECTOR_CN12_D1  	// Pin not routed
#define HEADER_CONNECTOR_CN12_D2  	// Pin not routed
#define HEADER_CONNECTOR_CN12_D3  	// Pin not routed
#define HEADER_CONNECTOR_CN12_D4  	// Pin not routed
#define HEADER_CONNECTOR_CN12_D5  	// Pin not routed
#define HEADER_CONNECTOR_CN12_D6  	// Pin not routed
#define HEADER_CONNECTOR_CN12_D7  	// Pin not routed
#define HEADER_CONNECTOR_CN12_D8  	// Pin not routed
#define HEADER_CONNECTOR_CN12_D9  	// Pin not routed
#define HEADER_CONNECTOR_CN12_D10 	// Pin not routed
#define HEADER_CONNECTOR_CN12_D11 	// Pin not routed
#define HEADER_CONNECTOR_CN12_D12 	// Pin not routed
#define HEADER_CONNECTOR_CN12_D13 	// Pin not routed
#define HEADER_CONNECTOR_CN12_D14 	// Pin not routed
#define HEADER_CONNECTOR_CN12_D15 	// Pin not routed
#define HEADER_CONNECTOR_CN12_D16 	// Pin not routed
#define HEADER_CONNECTOR_CN12_D17 	// Pin not routed
#define HEADER_CONNECTOR_CN12_D18 	// Pin not routed
#define HEADER_CONNECTOR_CN12_D19 	// Pin not routed
#define HEADER_CONNECTOR_CN12_D20 	// Pin not routed
#define HEADER_CONNECTOR_CN12_D21 	// Pin not routed
#define HEADER_CONNECTOR_CN12_D22 	// Pin not routed
#define HEADER_CONNECTOR_CN12_D23 	// Pin not routed
#define HEADER_CONNECTOR_CN12_D24 	// Pin not routed
#define HEADER_CONNECTOR_CN12_D25 	// Pin not routed
#define HEADER_CONNECTOR_CN12_D26 	// Pin not routed
#define HEADER_CONNECTOR_CN12_D27 	// Pin not routed
#define HEADER_CONNECTOR_CN12_D28 	// Pin not routed
#define HEADER_CONNECTOR_CN12_D29 	// Pin not routed
#define HEADER_CONNECTOR_CN12_D30 	// Pin not routed
#define HEADER_CONNECTOR_CN12_D31 	// Pin not routed
#define HEADER_CONNECTOR_CN12_D32 	// Pin not routed
#define HEADER_CONNECTOR_CN12_D33 	// Pin not routed
#define HEADER_CONNECTOR_CN12_D34 	// Pin not routed
#define HEADER_CONNECTOR_CN12_D35 	// Pin not routed
#define HEADER_CONNECTOR_CN12_D36 	// Pin not routed
#define HEADER_CONNECTOR_CN12_D37 	// Pin not routed
#define HEADER_CONNECTOR_CN12_D38 	// Pin not routed
#define HEADER_CONNECTOR_CN12_D39 	// Pin not routed
#define HEADER_CONNECTOR_CN12_D40 	// Pin not routed
#define HEADER_CONNECTOR_CN12_D41 	PD13
#define HEADER_CONNECTOR_CN12_D42 	PF10
#define HEADER_CONNECTOR_CN12_D43 	PD12
#define HEADER_CONNECTOR_CN12_D44 	PE7
#define HEADER_CONNECTOR_CN12_D45 	PD11
#define HEADER_CONNECTOR_CN12_D46 	PD14
#define HEADER_CONNECTOR_CN12_D47 	PE10
#define HEADER_CONNECTOR_CN12_D48 	PD15
#define HEADER_CONNECTOR_CN12_D49 	PE12
#define HEADER_CONNECTOR_CN12_D50 	PF14
#define HEADER_CONNECTOR_CN12_D51 	PE14
#define HEADER_CONNECTOR_CN12_D52 	PE9
#define HEADER_CONNECTOR_CN12_D53 	PE15
#define HEADER_CONNECTOR_CN12_D54 	// Pin not routed
#define HEADER_CONNECTOR_CN12_D55 	PE13
#define HEADER_CONNECTOR_CN12_D56 	PE11
#define HEADER_CONNECTOR_CN12_D57 	PF13
#define HEADER_CONNECTOR_CN12_D58 	PF3
#define HEADER_CONNECTOR_CN12_D59 	PF12
#define HEADER_CONNECTOR_CN12_D60 	PF15
#define HEADER_CONNECTOR_CN12_D61 	PG14
#define HEADER_CONNECTOR_CN12_D62 	PF11
#define HEADER_CONNECTOR_CN12_D63 	// Pin not routed
#define HEADER_CONNECTOR_CN12_D64 	PE0
#define HEADER_CONNECTOR_CN12_D65 	PD10
#define HEADER_CONNECTOR_CN12_D66 	PG8
#define HEADER_CONNECTOR_CN12_D67 	PG7
#define HEADER_CONNECTOR_CN12_D68 	PG5
#define HEADER_CONNECTOR_CN12_D69 	PG4
#define HEADER_CONNECTOR_CN12_D70 	PG6

#define HEADER_CONNECTOR_U5V(2)_D1	// Pin not routed
#define HEADER_CONNECTOR_U5V(2)_D2	// Pin not routed
#define HEADER_CONNECTOR_U5V(2)_D3	// Pin not routed
#define HEADER_CONNECTOR_U5V(2)_D4	// Pin not routed
#define HEADER_CONNECTOR_U5V(2)_D5	// Pin not routed
#define HEADER_CONNECTOR_U5V(2)_D6	// Pin not routed
#define HEADER_CONNECTOR_U5V(2)_D7	// Pin not routed
#define HEADER_CONNECTOR_U5V(2)_D8	// Pin not routed

#ifdef __cplusplus
}
#endif

#endif    // _BOARD_H_
// ------------------------------------------------------------------------- END
