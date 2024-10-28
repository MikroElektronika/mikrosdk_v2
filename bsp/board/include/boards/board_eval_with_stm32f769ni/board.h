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

#define BOARD_NAME "STM32F769NI-Eval"

#include "hal_target.h"

// Mapping
#define HEADER_CONNECTOR_CN1_D1      	PA6
#define HEADER_CONNECTOR_CN1_D2      	// Pin not routed
#define HEADER_CONNECTOR_CN1_D3      	PC6
#define HEADER_CONNECTOR_CN1_D4      	// Pin not routed
#define HEADER_CONNECTOR_CN1_D5      	PA7
#define HEADER_CONNECTOR_CN1_D6      	// Pin not routed
#define HEADER_CONNECTOR_CN1_D7      	PC7
#define HEADER_CONNECTOR_CN1_D8      	// Pin not routed
#define HEADER_CONNECTOR_CN1_D9      	PB0
#define HEADER_CONNECTOR_CN1_D10     	// Pin not routed
#define HEADER_CONNECTOR_CN1_D11     	PC8
#define HEADER_CONNECTOR_CN1_D12     	// Pin not routed
#define HEADER_CONNECTOR_CN1_D13     	PB1
#define HEADER_CONNECTOR_CN1_D14     	PC4
#define HEADER_CONNECTOR_CN1_D15     	PC1
#define HEADER_CONNECTOR_CN1_D16     	// Pin not routed
#define HEADER_CONNECTOR_CN1_D17     	PC2
#define HEADER_CONNECTOR_CN1_D18     	// Pin not routed
#define HEADER_CONNECTOR_CN1_D19     	PC3
#define HEADER_CONNECTOR_CN1_D20     	// Pin not routed
#define HEADER_CONNECTOR_CN1_D21     	PG11
#define HEADER_CONNECTOR_CN1_D22     	// Pin not routed
#define HEADER_CONNECTOR_CN1_D23     	PH6
#define HEADER_CONNECTOR_CN1_D24     	// Pin not routed
#define HEADER_CONNECTOR_CN1_D25     	// Pin not routed
#define HEADER_CONNECTOR_CN1_D26     	PC5
#define HEADER_CONNECTOR_CN1_D27     	PA12
#define HEADER_CONNECTOR_CN1_D28     	// Pin not routed
#define HEADER_CONNECTOR_CN1_D29     	PA11
#define HEADER_CONNECTOR_CN1_D30     	// Pin not routed
#define HEADER_CONNECTOR_CN1_D31     	PA0
#define HEADER_CONNECTOR_CN1_D32     	// Pin not routed
#define HEADER_CONNECTOR_CN1_D33     	PA1
#define HEADER_CONNECTOR_CN1_D34     	PA2

#define HEADER_CONNECTOR_CN2_D1      	PB9
#define HEADER_CONNECTOR_CN2_D2      	// Pin not routed
#define HEADER_CONNECTOR_CN2_D3      	PB8
#define HEADER_CONNECTOR_CN2_D4      	PC10
#define HEADER_CONNECTOR_CN2_D5      	// Pin not routed
#define HEADER_CONNECTOR_CN2_D6      	// Pin not routed
#define HEADER_CONNECTOR_CN2_D7      	// Pin not routed
#define HEADER_CONNECTOR_CN2_D8      	// Pin not routed

#define HEADER_CONNECTOR_CN3_D1      	PF10
#define HEADER_CONNECTOR_CN3_D2      	// Pin not routed

#define HEADER_CONNECTOR_CN4_D1      	// Pin not routed
#define HEADER_CONNECTOR_CN4_D2      	// Pin not routed
#define HEADER_CONNECTOR_CN4_D3      	// Pin not routed
#define HEADER_CONNECTOR_CN4_D4      	// Pin not routed
#define HEADER_CONNECTOR_CN4_D5      	PD6
#define HEADER_CONNECTOR_CN4_D6      	PD2
#define HEADER_CONNECTOR_CN4_D7      	// Pin not routed
#define HEADER_CONNECTOR_CN4_D8      	// Pin not routed
#define HEADER_CONNECTOR_CN4_D9      	PC10
#define HEADER_CONNECTOR_CN4_D10     	PC12
#define HEADER_CONNECTOR_CN4_D11     	// Pin not routed
#define HEADER_CONNECTOR_CN4_D12     	// Pin not routed
#define HEADER_CONNECTOR_CN4_D13     	PB8
#define HEADER_CONNECTOR_CN4_D14     	PB9
#define HEADER_CONNECTOR_CN4_D15     	// Pin not routed
#define HEADER_CONNECTOR_CN4_D16     	// Pin not routed
#define HEADER_CONNECTOR_CN4_D17     	// Pin not routed
#define HEADER_CONNECTOR_CN4_D18     	// Pin not routed
#define HEADER_CONNECTOR_CN4_D19     	// Pin not routed
#define HEADER_CONNECTOR_CN4_D20     	// Pin not routed
#define HEADER_CONNECTOR_CN4_D21     	// Pin not routed
#define HEADER_CONNECTOR_CN4_D22     	// Pin not routed
#define HEADER_CONNECTOR_CN4_D23     	PC6
#define HEADER_CONNECTOR_CN4_D24     	PC7
#define HEADER_CONNECTOR_CN4_D25     	PC8
#define HEADER_CONNECTOR_CN4_D26     	PC9
#define HEADER_CONNECTOR_CN4_D27     	PC11
#define HEADER_CONNECTOR_CN4_D28     	PD3
#define HEADER_CONNECTOR_CN4_D29     	PE5
#define HEADER_CONNECTOR_CN4_D30     	PE6
#define HEADER_CONNECTOR_CN4_D31     	PA4
#define HEADER_CONNECTOR_CN4_D32     	PB7
#define HEADER_CONNECTOR_CN4_D33     	PA6
#define HEADER_CONNECTOR_CN4_D34     	// Pin not routed
#define HEADER_CONNECTOR_CN4_D35     	// Pin not routed
#define HEADER_CONNECTOR_CN4_D36     	// Pin not routed
#define HEADER_CONNECTOR_CN4_D37     	// Pin not routed
#define HEADER_CONNECTOR_CN4_D38     	// Pin not routed
#define HEADER_CONNECTOR_CN4_D39     	// Pin not routed
#define HEADER_CONNECTOR_CN4_D40     	// Pin not routed

#define HEADER_CONNECTOR_CN5_D1      	// Pin not routed
#define HEADER_CONNECTOR_CN5_D2      	PI11
#define HEADER_CONNECTOR_CN5_D3      	PH0
#define HEADER_CONNECTOR_CN5_D4      	PB5
#define HEADER_CONNECTOR_CN5_D5      	// Pin not routed
#define HEADER_CONNECTOR_CN5_D6      	PH1
#define HEADER_CONNECTOR_CN5_D7      	PF6
#define HEADER_CONNECTOR_CN5_D8      	PF7
#define HEADER_CONNECTOR_CN5_D9      	PF10
#define HEADER_CONNECTOR_CN5_D10     	// Pin not routed
#define HEADER_CONNECTOR_CN5_D11     	PC0
#define HEADER_CONNECTOR_CN5_D12     	PF9
#define HEADER_CONNECTOR_CN5_D13     	PA2
#define HEADER_CONNECTOR_CN5_D14     	PA1
#define HEADER_CONNECTOR_CN5_D15     	PA0
#define HEADER_CONNECTOR_CN5_D16     	PC1
#define HEADER_CONNECTOR_CN5_D17     	PF8
#define HEADER_CONNECTOR_CN5_D18     	PA3
#define HEADER_CONNECTOR_CN5_D19     	// Pin not routed
#define HEADER_CONNECTOR_CN5_D20     	PA6
#define HEADER_CONNECTOR_CN5_D21     	PA4
#define HEADER_CONNECTOR_CN5_D22     	PA7
#define HEADER_CONNECTOR_CN5_D23     	PC2
#define HEADER_CONNECTOR_CN5_D24     	PA5
#define HEADER_CONNECTOR_CN5_D25     	PC4
#define HEADER_CONNECTOR_CN5_D26     	PB1
#define HEADER_CONNECTOR_CN5_D27     	PC3
#define HEADER_CONNECTOR_CN5_D28     	PH4
#define HEADER_CONNECTOR_CN5_D29     	PB2
#define HEADER_CONNECTOR_CN5_D30     	// Pin not routed
#define HEADER_CONNECTOR_CN5_D31     	PJ3
#define HEADER_CONNECTOR_CN5_D32     	PI14
#define HEADER_CONNECTOR_CN5_D33     	PB10
#define HEADER_CONNECTOR_CN5_D34     	PJ4
#define HEADER_CONNECTOR_CN5_D35     	PB14
#define HEADER_CONNECTOR_CN5_D36     	PB11
#define HEADER_CONNECTOR_CN5_D37     	PH6
#define HEADER_CONNECTOR_CN5_D38     	PB15
#define HEADER_CONNECTOR_CN5_D39     	// Pin not routed
#define HEADER_CONNECTOR_CN5_D40     	PH7
#define HEADER_CONNECTOR_CN5_D41     	PB12
#define HEADER_CONNECTOR_CN5_D42     	PJ5
#define HEADER_CONNECTOR_CN5_D43     	PB13
#define HEADER_CONNECTOR_CN5_D44     	PJ6
#define HEADER_CONNECTOR_CN5_D45     	PJ9
#define HEADER_CONNECTOR_CN5_D46     	PC5
#define HEADER_CONNECTOR_CN5_D47     	PG7
#define HEADER_CONNECTOR_CN5_D48     	// Pin not routed
#define HEADER_CONNECTOR_CN5_D49     	// Pin not routed
#define HEADER_CONNECTOR_CN5_D50     	// Pin not routed
#define HEADER_CONNECTOR_CN5_D51     	PG6
#define HEADER_CONNECTOR_CN5_D52     	PB0
#define HEADER_CONNECTOR_CN5_D53     	PJ7
#define HEADER_CONNECTOR_CN5_D54     	PJ0
#define HEADER_CONNECTOR_CN5_D55     	PJ10
#define HEADER_CONNECTOR_CN5_D56     	PJ2
#define HEADER_CONNECTOR_CN5_D57     	PJ8
#define HEADER_CONNECTOR_CN5_D58     	PJ1
#define HEADER_CONNECTOR_CN5_D59     	// Pin not routed
#define HEADER_CONNECTOR_CN5_D60     	// Pin not routed

#define HEADER_CONNECTOR_CN6_D1      	// Pin not routed
#define HEADER_CONNECTOR_CN6_D2      	PI13
#define HEADER_CONNECTOR_CN6_D3      	PC15
#define HEADER_CONNECTOR_CN6_D4      	PC14
#define HEADER_CONNECTOR_CN6_D5      	PI15
#define HEADER_CONNECTOR_CN6_D6      	PC13
#define HEADER_CONNECTOR_CN6_D7      	PI12
#define HEADER_CONNECTOR_CN6_D8      	PK7
#define HEADER_CONNECTOR_CN6_D9      	PI8
#define HEADER_CONNECTOR_CN6_D10     	// Pin not routed
#define HEADER_CONNECTOR_CN6_D11     	PK6
#define HEADER_CONNECTOR_CN6_D12     	PK5
#define HEADER_CONNECTOR_CN6_D13     	PK4
#define HEADER_CONNECTOR_CN6_D14     	PB9
#define HEADER_CONNECTOR_CN6_D15     	PG12
#define HEADER_CONNECTOR_CN6_D16     	PK3
#define HEADER_CONNECTOR_CN6_D17     	PG9
#define HEADER_CONNECTOR_CN6_D18     	PB6
#define HEADER_CONNECTOR_CN6_D19     	// Pin not routed
#define HEADER_CONNECTOR_CN6_D20     	PJ14
#define HEADER_CONNECTOR_CN6_D21     	PB7
#define HEADER_CONNECTOR_CN6_D22     	PJ15
#define HEADER_CONNECTOR_CN6_D23     	PD3
#define HEADER_CONNECTOR_CN6_D24     	PB4
#define HEADER_CONNECTOR_CN6_D25     	PG13
#define HEADER_CONNECTOR_CN6_D26     	PJ13
#define HEADER_CONNECTOR_CN6_D27     	PJ12
#define HEADER_CONNECTOR_CN6_D28     	PC12
#define HEADER_CONNECTOR_CN6_D29     	PG14
#define HEADER_CONNECTOR_CN6_D30     	// Pin not routed
#define HEADER_CONNECTOR_CN6_D31     	PB8
#define HEADER_CONNECTOR_CN6_D32     	PA15
#define HEADER_CONNECTOR_CN6_D33     	PG11
#define HEADER_CONNECTOR_CN6_D34     	PK1
#define HEADER_CONNECTOR_CN6_D35     	PJ11
#define HEADER_CONNECTOR_CN6_D36     	PA14
#define HEADER_CONNECTOR_CN6_D37     	PK0
#define HEADER_CONNECTOR_CN6_D38     	PK2
#define HEADER_CONNECTOR_CN6_D39     	// Pin not routed
#define HEADER_CONNECTOR_CN6_D40     	PA13
#define HEADER_CONNECTOR_CN6_D41     	PA11
#define HEADER_CONNECTOR_CN6_D42     	PA12
#define HEADER_CONNECTOR_CN6_D43     	PA9
#define HEADER_CONNECTOR_CN6_D44     	PA10
#define HEADER_CONNECTOR_CN6_D45     	PB3
#define HEADER_CONNECTOR_CN6_D46     	PC9
#define HEADER_CONNECTOR_CN6_D47     	PD6
#define HEADER_CONNECTOR_CN6_D48     	// Pin not routed
#define HEADER_CONNECTOR_CN6_D49     	// Pin not routed
#define HEADER_CONNECTOR_CN6_D50     	// Pin not routed
#define HEADER_CONNECTOR_CN6_D51     	PC8
#define HEADER_CONNECTOR_CN6_D52     	PA8
#define HEADER_CONNECTOR_CN6_D53     	PC11
#define HEADER_CONNECTOR_CN6_D54     	// Pin not routed
#define HEADER_CONNECTOR_CN6_D55     	PC10
#define HEADER_CONNECTOR_CN6_D56     	PD7
#define HEADER_CONNECTOR_CN6_D57     	PD2
#define HEADER_CONNECTOR_CN6_D58     	PC6
#define HEADER_CONNECTOR_CN6_D59     	// Pin not routed
#define HEADER_CONNECTOR_CN6_D60     	// Pin not routed

#define HEADER_CONNECTOR_CN7_D1      	// Pin not routed
#define HEADER_CONNECTOR_CN7_D2      	PA10
#define HEADER_CONNECTOR_CN7_D3      	PA9
#define HEADER_CONNECTOR_CN7_D4      	// Pin not routed
#define HEADER_CONNECTOR_CN7_D5      	// Pin not routed
#define HEADER_CONNECTOR_CN7_D6      	// Pin not routed
#define HEADER_CONNECTOR_CN7_D7      	// Pin not routed
#define HEADER_CONNECTOR_CN7_D8      	// Pin not routed
#define HEADER_CONNECTOR_CN7_D9      	// Pin not routed

#define HEADER_CONNECTOR_CN10_D1     	PH3
#define HEADER_CONNECTOR_CN10_D2     	PH5
#define HEADER_CONNECTOR_CN10_D3     	PF13
#define HEADER_CONNECTOR_CN10_D4     	PF14
#define HEADER_CONNECTOR_CN10_D5     	PF12
#define HEADER_CONNECTOR_CN10_D6     	PG0
#define HEADER_CONNECTOR_CN10_D7     	PG1
#define HEADER_CONNECTOR_CN10_D8     	PF11
#define HEADER_CONNECTOR_CN10_D9     	// Pin not routed
#define HEADER_CONNECTOR_CN10_D10    	// Pin not routed
#define HEADER_CONNECTOR_CN10_D11    	PE7
#define HEADER_CONNECTOR_CN10_D12    	PE9
#define HEADER_CONNECTOR_CN10_D13    	PE10
#define HEADER_CONNECTOR_CN10_D14    	PE8
#define HEADER_CONNECTOR_CN10_D15    	PE12
#define HEADER_CONNECTOR_CN10_D16    	PE11
#define HEADER_CONNECTOR_CN10_D17    	PE15
#define HEADER_CONNECTOR_CN10_D18    	PF15
#define HEADER_CONNECTOR_CN10_D19    	PE13
#define HEADER_CONNECTOR_CN10_D20    	PE14
#define HEADER_CONNECTOR_CN10_D21    	PD11
#define HEADER_CONNECTOR_CN10_D22    	PH8
#define HEADER_CONNECTOR_CN10_D23    	PD12
#define HEADER_CONNECTOR_CN10_D24    	PH10
#define HEADER_CONNECTOR_CN10_D25    	PG5
#define HEADER_CONNECTOR_CN10_D26    	PH9
#define HEADER_CONNECTOR_CN10_D27    	PH11
#define HEADER_CONNECTOR_CN10_D28    	PG4
#define HEADER_CONNECTOR_CN10_D29    	// Pin not routed
#define HEADER_CONNECTOR_CN10_D30    	// Pin not routed
#define HEADER_CONNECTOR_CN10_D31    	PD13
#define HEADER_CONNECTOR_CN10_D32    	PH12
#define HEADER_CONNECTOR_CN10_D33    	PG2
#define HEADER_CONNECTOR_CN10_D34    	PG3
#define HEADER_CONNECTOR_CN10_D35    	PD8
#define HEADER_CONNECTOR_CN10_D36    	PD10
#define HEADER_CONNECTOR_CN10_D37    	PD9
#define HEADER_CONNECTOR_CN10_D38    	PD15
#define HEADER_CONNECTOR_CN10_D39    	PD14
#define HEADER_CONNECTOR_CN10_D40    	PG8

#define HEADER_CONNECTOR_CN11_D1     	PF5
#define HEADER_CONNECTOR_CN11_D2     	PH2
#define HEADER_CONNECTOR_CN11_D3     	PF4
#define HEADER_CONNECTOR_CN11_D4     	PE5
#define HEADER_CONNECTOR_CN11_D5     	PF3
#define HEADER_CONNECTOR_CN11_D6     	PC6
#define HEADER_CONNECTOR_CN11_D7     	PE6
#define HEADER_CONNECTOR_CN11_D8     	PF2
#define HEADER_CONNECTOR_CN11_D9     	// Pin not routed
#define HEADER_CONNECTOR_CN11_D10    	// Pin not routed
#define HEADER_CONNECTOR_CN11_D11    	PE4
#define HEADER_CONNECTOR_CN11_D12    	PF1
#define HEADER_CONNECTOR_CN11_D13    	PE3
#define HEADER_CONNECTOR_CN11_D14    	PF0
#define HEADER_CONNECTOR_CN11_D15    	PI5
#define HEADER_CONNECTOR_CN11_D16    	PE2
#define HEADER_CONNECTOR_CN11_D17    	PI4
#define HEADER_CONNECTOR_CN11_D18    	PI7
#define HEADER_CONNECTOR_CN11_D19    	PG15
#define HEADER_CONNECTOR_CN11_D20    	PI9
#define HEADER_CONNECTOR_CN11_D21    	PI10
#define HEADER_CONNECTOR_CN11_D22    	PI6
#define HEADER_CONNECTOR_CN11_D23    	PE1
#define HEADER_CONNECTOR_CN11_D24    	PC7
#define HEADER_CONNECTOR_CN11_D25    	PE0
#define HEADER_CONNECTOR_CN11_D26    	PD5
#define HEADER_CONNECTOR_CN11_D27    	PG6
#define HEADER_CONNECTOR_CN11_D28    	PD4
#define HEADER_CONNECTOR_CN11_D29    	// Pin not routed
#define HEADER_CONNECTOR_CN11_D30    	// Pin not routed
#define HEADER_CONNECTOR_CN11_D31    	PD0
#define HEADER_CONNECTOR_CN11_D32    	PD1
#define HEADER_CONNECTOR_CN11_D33    	PI2
#define HEADER_CONNECTOR_CN11_D34    	PI3
#define HEADER_CONNECTOR_CN11_D35    	PI1
#define HEADER_CONNECTOR_CN11_D36    	PH15
#define HEADER_CONNECTOR_CN11_D37    	PI0
#define HEADER_CONNECTOR_CN11_D38    	PH14
#define HEADER_CONNECTOR_CN11_D39    	PH13
#define HEADER_CONNECTOR_CN11_D40    	// Pin not routed

#define HEADER_CONNECTOR_CN16_D1     	// Pin not routed
#define HEADER_CONNECTOR_CN16_D2     	// Pin not routed
#define HEADER_CONNECTOR_CN16_D3     	// Pin not routed
#define HEADER_CONNECTOR_CN16_D4     	// Pin not routed
#define HEADER_CONNECTOR_CN16_D5     	// Pin not routed
#define HEADER_CONNECTOR_CN16_D6     	// Pin not routed
#define HEADER_CONNECTOR_CN16_D7     	// Pin not routed
#define HEADER_CONNECTOR_CN16_D8     	// Pin not routed
#define HEADER_CONNECTOR_CN16_D9     	// Pin not routed
#define HEADER_CONNECTOR_CN16_D10    	// Pin not routed
#define HEADER_CONNECTOR_CN16_D11    	// Pin not routed
#define HEADER_CONNECTOR_CN16_D12    	// Pin not routed
#define HEADER_CONNECTOR_CN16_D13    	PB3
#define HEADER_CONNECTOR_CN16_D14    	// Pin not routed
#define HEADER_CONNECTOR_CN16_D15    	// Pin not routed
#define HEADER_CONNECTOR_CN16_D16    	// Pin not routed
#define HEADER_CONNECTOR_CN16_D17    	// Pin not routed
#define HEADER_CONNECTOR_CN16_D18    	// Pin not routed
#define HEADER_CONNECTOR_CN16_D19    	// Pin not routed
#define HEADER_CONNECTOR_CN16_D20    	// Pin not routed

#define HEADER_CONNECTOR_CN17_D1     	PC10
#define HEADER_CONNECTOR_CN17_D2     	PC11
#define HEADER_CONNECTOR_CN17_D3     	PD2
#define HEADER_CONNECTOR_CN17_D4     	// Pin not routed
#define HEADER_CONNECTOR_CN17_D5     	PC12
#define HEADER_CONNECTOR_CN17_D6     	// Pin not routed
#define HEADER_CONNECTOR_CN17_D7     	PC8
#define HEADER_CONNECTOR_CN17_D8     	PC9
#define HEADER_CONNECTOR_CN17_D9     	// Pin not routed
#define HEADER_CONNECTOR_CN17_D10    	// Pin not routed

#define HEADER_CONNECTOR_CN29_D1     	PG12
#define HEADER_CONNECTOR_CN29_D2     	// Pin not routed
#define HEADER_CONNECTOR_CN29_D3     	// Pin not routed

#define HEADER_CONNECTOR_CN30_D1     	PB3
#define HEADER_CONNECTOR_CN30_D2     	PB4
#define HEADER_CONNECTOR_CN30_D3     	PD7
#define HEADER_CONNECTOR_CN30_D4     	// Pin not routed
#define HEADER_CONNECTOR_CN30_D5     	// Pin not routed
#define HEADER_CONNECTOR_CN30_D6     	// Pin not routed
#define HEADER_CONNECTOR_CN30_D7     	PG9
#define HEADER_CONNECTOR_CN30_D8     	PG10
#define HEADER_CONNECTOR_CN30_D9     	// Pin not routed
#define HEADER_CONNECTOR_CN30_D10    	// Pin not routed

#define HEADER_CONNECTOR_GENERAL1_D1 	// Pin not routed
#define HEADER_CONNECTOR_GENERAL1_D2 	// Pin not routed
#define HEADER_CONNECTOR_GENERAL1_D3 	// Pin not routed
#define HEADER_CONNECTOR_GENERAL1_D4 	// Pin not routed
#define HEADER_CONNECTOR_GENERAL1_D5 	// Pin not routed
#define HEADER_CONNECTOR_GENERAL1_D6 	// Pin not routed
#define HEADER_CONNECTOR_GENERAL1_D7 	PA13
#define HEADER_CONNECTOR_GENERAL1_D8 	// Pin not routed
#define HEADER_CONNECTOR_GENERAL1_D9 	PA14
#define HEADER_CONNECTOR_GENERAL1_D10	// Pin not routed

#ifdef __cplusplus
}
#endif

#endif    // _BOARD_H_
// ------------------------------------------------------------------------- END
