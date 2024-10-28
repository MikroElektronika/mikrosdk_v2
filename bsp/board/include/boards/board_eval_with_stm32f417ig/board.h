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
#define HEADER_CONNECTOR_CN1_D1      	// Pin not routed
#define HEADER_CONNECTOR_CN1_D2      	PE2
#define HEADER_CONNECTOR_CN1_D3      	PE3
#define HEADER_CONNECTOR_CN1_D4      	PE4
#define HEADER_CONNECTOR_CN1_D5      	PE5
#define HEADER_CONNECTOR_CN1_D6      	PE6
#define HEADER_CONNECTOR_CN1_D7      	PI8
#define HEADER_CONNECTOR_CN1_D8      	PC13
#define HEADER_CONNECTOR_CN1_D9      	PC14
#define HEADER_CONNECTOR_CN1_D10     	// Pin not routed
#define HEADER_CONNECTOR_CN1_D11     	PC15
#define HEADER_CONNECTOR_CN1_D12     	PI9
#define HEADER_CONNECTOR_CN1_D13     	PI10
#define HEADER_CONNECTOR_CN1_D14     	PI11
#define HEADER_CONNECTOR_CN1_D15     	PF0
#define HEADER_CONNECTOR_CN1_D16     	PF1
#define HEADER_CONNECTOR_CN1_D17     	PF2
#define HEADER_CONNECTOR_CN1_D18     	PF3
#define HEADER_CONNECTOR_CN1_D19     	// Pin not routed
#define HEADER_CONNECTOR_CN1_D20     	PF4
#define HEADER_CONNECTOR_CN1_D21     	PF5
#define HEADER_CONNECTOR_CN1_D22     	PF6
#define HEADER_CONNECTOR_CN1_D23     	PF7
#define HEADER_CONNECTOR_CN1_D24     	PF8
#define HEADER_CONNECTOR_CN1_D25     	PF9
#define HEADER_CONNECTOR_CN1_D26     	PF10
#define HEADER_CONNECTOR_CN1_D27     	PH0
#define HEADER_CONNECTOR_CN1_D28     	PH1
#define HEADER_CONNECTOR_CN1_D29     	PC0
#define HEADER_CONNECTOR_CN1_D30     	// Pin not routed
#define HEADER_CONNECTOR_CN1_D31     	PC1
#define HEADER_CONNECTOR_CN1_D32     	PC2
#define HEADER_CONNECTOR_CN1_D33     	PC3
#define HEADER_CONNECTOR_CN1_D34     	// Pin not routed
#define HEADER_CONNECTOR_CN1_D35     	PA0
#define HEADER_CONNECTOR_CN1_D36     	PA1
#define HEADER_CONNECTOR_CN1_D37     	PA2
#define HEADER_CONNECTOR_CN1_D38     	PH2
#define HEADER_CONNECTOR_CN1_D39     	// Pin not routed
#define HEADER_CONNECTOR_CN1_D40     	PH3
#define HEADER_CONNECTOR_CN1_D41     	PH4
#define HEADER_CONNECTOR_CN1_D42     	PH5
#define HEADER_CONNECTOR_CN1_D43     	// Pin not routed
#define HEADER_CONNECTOR_CN1_D44     	// Pin not routed
#define HEADER_CONNECTOR_CN1_D45     	// Pin not routed
#define HEADER_CONNECTOR_CN1_D46     	// Pin not routed
#define HEADER_CONNECTOR_CN1_D47     	// Pin not routed
#define HEADER_CONNECTOR_CN1_D48     	// Pin not routed
#define HEADER_CONNECTOR_CN1_D49     	// Pin not routed
#define HEADER_CONNECTOR_CN1_D50     	// Pin not routed

#define HEADER_CONNECTOR_CN2_D1      	// Pin not routed
#define HEADER_CONNECTOR_CN2_D2      	// Pin not routed
#define HEADER_CONNECTOR_CN2_D3      	// Pin not routed
#define HEADER_CONNECTOR_CN2_D4      	PA4
#define HEADER_CONNECTOR_CN2_D5      	// Pin not routed
#define HEADER_CONNECTOR_CN2_D6      	PA6
#define HEADER_CONNECTOR_CN2_D7      	// Pin not routed
#define HEADER_CONNECTOR_CN2_D8      	PC4
#define HEADER_CONNECTOR_CN2_D9      	// Pin not routed
#define HEADER_CONNECTOR_CN2_D10     	// Pin not routed
#define HEADER_CONNECTOR_CN2_D11     	PB0
#define HEADER_CONNECTOR_CN2_D12     	PB1
#define HEADER_CONNECTOR_CN2_D13     	PB2
#define HEADER_CONNECTOR_CN2_D14     	PF11
#define HEADER_CONNECTOR_CN2_D15     	PF12
#define HEADER_CONNECTOR_CN2_D16     	PF13
#define HEADER_CONNECTOR_CN2_D17     	PF14
#define HEADER_CONNECTOR_CN2_D18     	PF15
#define HEADER_CONNECTOR_CN2_D19     	// Pin not routed
#define HEADER_CONNECTOR_CN2_D20     	PG0
#define HEADER_CONNECTOR_CN2_D21     	PG1
#define HEADER_CONNECTOR_CN2_D22     	PE7
#define HEADER_CONNECTOR_CN2_D23     	PE8
#define HEADER_CONNECTOR_CN2_D24     	PE9
#define HEADER_CONNECTOR_CN2_D25     	PE10
#define HEADER_CONNECTOR_CN2_D26     	PE11
#define HEADER_CONNECTOR_CN2_D27     	PE12
#define HEADER_CONNECTOR_CN2_D28     	PE13
#define HEADER_CONNECTOR_CN2_D29     	PE14
#define HEADER_CONNECTOR_CN2_D30     	// Pin not routed
#define HEADER_CONNECTOR_CN2_D31     	PE15
#define HEADER_CONNECTOR_CN2_D32     	PB10
#define HEADER_CONNECTOR_CN2_D33     	PB11
#define HEADER_CONNECTOR_CN2_D34     	PH6
#define HEADER_CONNECTOR_CN2_D35     	PH7
#define HEADER_CONNECTOR_CN2_D36     	PH8
#define HEADER_CONNECTOR_CN2_D37     	PH9
#define HEADER_CONNECTOR_CN2_D38     	PH10
#define HEADER_CONNECTOR_CN2_D39     	// Pin not routed
#define HEADER_CONNECTOR_CN2_D40     	PH11

#define HEADER_CONNECTOR_CN3_D1      	// Pin not routed
#define HEADER_CONNECTOR_CN3_D2      	PI2
#define HEADER_CONNECTOR_CN3_D3      	PI1
#define HEADER_CONNECTOR_CN3_D4      	PI0
#define HEADER_CONNECTOR_CN3_D5      	PH15
#define HEADER_CONNECTOR_CN3_D6      	PH14
#define HEADER_CONNECTOR_CN3_D7      	PH13
#define HEADER_CONNECTOR_CN3_D8      	PA13
#define HEADER_CONNECTOR_CN3_D9      	PC13
#define HEADER_CONNECTOR_CN3_D10     	// Pin not routed
#define HEADER_CONNECTOR_CN3_D11     	// Pin not routed
#define HEADER_CONNECTOR_CN3_D12     	PA12
#define HEADER_CONNECTOR_CN3_D13     	PA11
#define HEADER_CONNECTOR_CN3_D14     	PA10
#define HEADER_CONNECTOR_CN3_D15     	PA9
#define HEADER_CONNECTOR_CN3_D16     	PA8
#define HEADER_CONNECTOR_CN3_D17     	PC9
#define HEADER_CONNECTOR_CN3_D18     	PC8
#define HEADER_CONNECTOR_CN3_D19     	// Pin not routed
#define HEADER_CONNECTOR_CN3_D20     	PC7
#define HEADER_CONNECTOR_CN3_D21     	PC6
#define HEADER_CONNECTOR_CN3_D22     	PG8
#define HEADER_CONNECTOR_CN3_D23     	PG7
#define HEADER_CONNECTOR_CN3_D24     	PG6
#define HEADER_CONNECTOR_CN3_D25     	PG5
#define HEADER_CONNECTOR_CN3_D26     	PG4
#define HEADER_CONNECTOR_CN3_D27     	PG3
#define HEADER_CONNECTOR_CN3_D28     	PG2
#define HEADER_CONNECTOR_CN3_D29     	PD15
#define HEADER_CONNECTOR_CN3_D30     	// Pin not routed
#define HEADER_CONNECTOR_CN3_D31     	PD14
#define HEADER_CONNECTOR_CN3_D32     	PD13
#define HEADER_CONNECTOR_CN3_D33     	PD12
#define HEADER_CONNECTOR_CN3_D34     	PD11
#define HEADER_CONNECTOR_CN3_D35     	PD10
#define HEADER_CONNECTOR_CN3_D36     	PD9
#define HEADER_CONNECTOR_CN3_D37     	PD8
#define HEADER_CONNECTOR_CN3_D38     	PB15
#define HEADER_CONNECTOR_CN3_D39     	// Pin not routed
#define HEADER_CONNECTOR_CN3_D40     	PB14
#define HEADER_CONNECTOR_CN3_D41     	PB13
#define HEADER_CONNECTOR_CN3_D42     	PB12
#define HEADER_CONNECTOR_CN3_D43     	PH12
#define HEADER_CONNECTOR_CN3_D44     	// Pin not routed
#define HEADER_CONNECTOR_CN3_D45     	// Pin not routed
#define HEADER_CONNECTOR_CN3_D46     	// Pin not routed
#define HEADER_CONNECTOR_CN3_D47     	// Pin not routed
#define HEADER_CONNECTOR_CN3_D48     	// Pin not routed
#define HEADER_CONNECTOR_CN3_D49     	// Pin not routed
#define HEADER_CONNECTOR_CN3_D50     	// Pin not routed

#define HEADER_CONNECTOR_CN4_D1      	// Pin not routed
#define HEADER_CONNECTOR_CN4_D2      	PI7
#define HEADER_CONNECTOR_CN4_D3      	PI6
#define HEADER_CONNECTOR_CN4_D4      	PI5
#define HEADER_CONNECTOR_CN4_D5      	PI4
#define HEADER_CONNECTOR_CN4_D6      	PE1
#define HEADER_CONNECTOR_CN4_D7      	PE0
#define HEADER_CONNECTOR_CN4_D8      	PB9
#define HEADER_CONNECTOR_CN4_D9      	PB8
#define HEADER_CONNECTOR_CN4_D10     	// Pin not routed
#define HEADER_CONNECTOR_CN4_D11     	// Pin not routed
#define HEADER_CONNECTOR_CN4_D12     	PB7
#define HEADER_CONNECTOR_CN4_D13     	PB6
#define HEADER_CONNECTOR_CN4_D14     	PB5
#define HEADER_CONNECTOR_CN4_D15     	PB4
#define HEADER_CONNECTOR_CN4_D16     	PB3
#define HEADER_CONNECTOR_CN4_D17     	PG15
#define HEADER_CONNECTOR_CN4_D18     	PG14
#define HEADER_CONNECTOR_CN4_D19     	// Pin not routed
#define HEADER_CONNECTOR_CN4_D20     	PG13
#define HEADER_CONNECTOR_CN4_D21     	PG12
#define HEADER_CONNECTOR_CN4_D22     	PG11
#define HEADER_CONNECTOR_CN4_D23     	PG10
#define HEADER_CONNECTOR_CN4_D24     	PG9
#define HEADER_CONNECTOR_CN4_D25     	PD7
#define HEADER_CONNECTOR_CN4_D26     	PD6
#define HEADER_CONNECTOR_CN4_D27     	PD5
#define HEADER_CONNECTOR_CN4_D28     	PD4
#define HEADER_CONNECTOR_CN4_D29     	PD3
#define HEADER_CONNECTOR_CN4_D30     	// Pin not routed
#define HEADER_CONNECTOR_CN4_D31     	PD2
#define HEADER_CONNECTOR_CN4_D32     	PD1
#define HEADER_CONNECTOR_CN4_D33     	PD0
#define HEADER_CONNECTOR_CN4_D34     	PC12
#define HEADER_CONNECTOR_CN4_D35     	PC11
#define HEADER_CONNECTOR_CN4_D36     	PC10
#define HEADER_CONNECTOR_CN4_D37     	PA15
#define HEADER_CONNECTOR_CN4_D38     	PA14
#define HEADER_CONNECTOR_CN4_D39     	// Pin not routed
#define HEADER_CONNECTOR_CN4_D40     	PI3

#define HEADER_CONNECTOR_CN6_D1      	PC10
#define HEADER_CONNECTOR_CN6_D2      	PC11
#define HEADER_CONNECTOR_CN6_D3      	PD2
#define HEADER_CONNECTOR_CN6_D4      	// Pin not routed
#define HEADER_CONNECTOR_CN6_D5      	PC12
#define HEADER_CONNECTOR_CN6_D6      	// Pin not routed
#define HEADER_CONNECTOR_CN6_D7      	PC8
#define HEADER_CONNECTOR_CN6_D8      	PC9
#define HEADER_CONNECTOR_CN6_D9      	// Pin not routed
#define HEADER_CONNECTOR_CN6_D10     	PH13

#define HEADER_CONNECTOR_CN14_D1     	// Pin not routed
#define HEADER_CONNECTOR_CN14_D2     	// Pin not routed
#define HEADER_CONNECTOR_CN14_D3     	PB4
#define HEADER_CONNECTOR_CN14_D4     	// Pin not routed
#define HEADER_CONNECTOR_CN14_D5     	PA15
#define HEADER_CONNECTOR_CN14_D6     	// Pin not routed
#define HEADER_CONNECTOR_CN14_D7     	PA13
#define HEADER_CONNECTOR_CN14_D8     	// Pin not routed
#define HEADER_CONNECTOR_CN14_D9     	PA14
#define HEADER_CONNECTOR_CN14_D10    	// Pin not routed
#define HEADER_CONNECTOR_CN14_D11    	// Pin not routed
#define HEADER_CONNECTOR_CN14_D12    	// Pin not routed
#define HEADER_CONNECTOR_CN14_D13    	PB3
#define HEADER_CONNECTOR_CN14_D14    	// Pin not routed
#define HEADER_CONNECTOR_CN14_D15    	// Pin not routed
#define HEADER_CONNECTOR_CN14_D16    	// Pin not routed
#define HEADER_CONNECTOR_CN14_D17    	// Pin not routed
#define HEADER_CONNECTOR_CN14_D18    	// Pin not routed
#define HEADER_CONNECTOR_CN14_D19    	// Pin not routed
#define HEADER_CONNECTOR_CN14_D20    	// Pin not routed

#define HEADER_CONNECTOR_CN15_D1     	// Pin not routed
#define HEADER_CONNECTOR_CN15_D2     	// Pin not routed
#define HEADER_CONNECTOR_CN15_D3     	PB9
#define HEADER_CONNECTOR_CN15_D4     	// Pin not routed
#define HEADER_CONNECTOR_CN15_D5     	PB6
#define HEADER_CONNECTOR_CN15_D6     	// Pin not routed
#define HEADER_CONNECTOR_CN15_D7     	PI5
#define HEADER_CONNECTOR_CN15_D8     	// Pin not routed
#define HEADER_CONNECTOR_CN15_D9     	PH8
#define HEADER_CONNECTOR_CN15_D10    	// Pin not routed
#define HEADER_CONNECTOR_CN15_D11    	// Pin not routed
#define HEADER_CONNECTOR_CN15_D12    	PI7
#define HEADER_CONNECTOR_CN15_D13    	// Pin not routed
#define HEADER_CONNECTOR_CN15_D14    	PI6
#define HEADER_CONNECTOR_CN15_D15    	// Pin not routed
#define HEADER_CONNECTOR_CN15_D16    	PI4
#define HEADER_CONNECTOR_CN15_D17    	PA6
#define HEADER_CONNECTOR_CN15_D18    	PH14
#define HEADER_CONNECTOR_CN15_D19    	PH9
#define HEADER_CONNECTOR_CN15_D20    	PH12
#define HEADER_CONNECTOR_CN15_D21    	PH10
#define HEADER_CONNECTOR_CN15_D22    	PH11
#define HEADER_CONNECTOR_CN15_D23    	// Pin not routed
#define HEADER_CONNECTOR_CN15_D24    	// Pin not routed

#define HEADER_CONNECTOR_CN16_D1     	// Pin not routed
#define HEADER_CONNECTOR_CN16_D2     	PC11
#define HEADER_CONNECTOR_CN16_D3     	PC10
#define HEADER_CONNECTOR_CN16_D4     	// Pin not routed
#define HEADER_CONNECTOR_CN16_D5     	// Pin not routed
#define HEADER_CONNECTOR_CN16_D6     	// Pin not routed
#define HEADER_CONNECTOR_CN16_D7     	// Pin not routed
#define HEADER_CONNECTOR_CN16_D8     	// Pin not routed
#define HEADER_CONNECTOR_CN16_D9     	// Pin not routed

#define HEADER_CONNECTOR_CN19_D1     	// Pin not routed
#define HEADER_CONNECTOR_CN19_D2     	// Pin not routed
#define HEADER_CONNECTOR_CN19_D3     	// Pin not routed
#define HEADER_CONNECTOR_CN19_D4     	// Pin not routed
#define HEADER_CONNECTOR_CN19_D5     	// Pin not routed
#define HEADER_CONNECTOR_CN19_D6     	PD1
#define HEADER_CONNECTOR_CN19_D7     	PD2
#define HEADER_CONNECTOR_CN19_D8     	PD3
#define HEADER_CONNECTOR_CN19_D9     	PD4
#define HEADER_CONNECTOR_CN19_D10    	PD5
#define HEADER_CONNECTOR_CN19_D11    	PD6
#define HEADER_CONNECTOR_CN19_D12    	PD7
#define HEADER_CONNECTOR_CN19_D13    	PD8
#define HEADER_CONNECTOR_CN19_D14    	PD10
#define HEADER_CONNECTOR_CN19_D15    	PD11
#define HEADER_CONNECTOR_CN19_D16    	PD12
#define HEADER_CONNECTOR_CN19_D17    	PD13
#define HEADER_CONNECTOR_CN19_D18    	PD14
#define HEADER_CONNECTOR_CN19_D19    	PD15
#define HEADER_CONNECTOR_CN19_D20    	PD16
#define HEADER_CONNECTOR_CN19_D21    	PD17
#define HEADER_CONNECTOR_CN19_D22    	// Pin not routed
#define HEADER_CONNECTOR_CN19_D23    	// Pin not routed
#define HEADER_CONNECTOR_CN19_D24    	// Pin not routed
#define HEADER_CONNECTOR_CN19_D25    	// Pin not routed
#define HEADER_CONNECTOR_CN19_D26    	// Pin not routed
#define HEADER_CONNECTOR_CN19_D27    	// Pin not routed
#define HEADER_CONNECTOR_CN19_D28    	// Pin not routed
#define HEADER_CONNECTOR_CN19_D29    	// Pin not routed
#define HEADER_CONNECTOR_CN19_D30    	// Pin not routed
#define HEADER_CONNECTOR_CN19_D31    	// Pin not routed
#define HEADER_CONNECTOR_CN19_D32    	// Pin not routed
#define HEADER_CONNECTOR_CN19_D33    	// Pin not routed
#define HEADER_CONNECTOR_CN19_D34    	// Pin not routed

#define HEADER_CONNECTOR_GENERAL1_D1 	// Pin not routed
#define HEADER_CONNECTOR_GENERAL1_D2 	// Pin not routed
#define HEADER_CONNECTOR_GENERAL1_D3 	// Pin not routed
#define HEADER_CONNECTOR_GENERAL1_D4 	// Pin not routed
#define HEADER_CONNECTOR_GENERAL1_D5 	// Pin not routed
#define HEADER_CONNECTOR_GENERAL1_D6 	// Pin not routed
#define HEADER_CONNECTOR_GENERAL1_D7 	// Pin not routed
#define HEADER_CONNECTOR_GENERAL1_D8 	// Pin not routed
#define HEADER_CONNECTOR_GENERAL1_D9 	PC5
#define HEADER_CONNECTOR_GENERAL1_D10	// Pin not routed
#define HEADER_CONNECTOR_GENERAL1_D11	// Pin not routed
#define HEADER_CONNECTOR_GENERAL1_D12	// Pin not routed
#define HEADER_CONNECTOR_GENERAL1_D13	// Pin not routed
#define HEADER_CONNECTOR_GENERAL1_D14	// Pin not routed
#define HEADER_CONNECTOR_GENERAL1_D15	// Pin not routed
#define HEADER_CONNECTOR_GENERAL1_D16	// Pin not routed
#define HEADER_CONNECTOR_GENERAL1_D17	// Pin not routed
#define HEADER_CONNECTOR_GENERAL1_D18	// Pin not routed

#ifdef __cplusplus
}
#endif

#endif    // _BOARD_H_
// ------------------------------------------------------------------------- END
