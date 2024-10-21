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

#define BOARD_NAME "STM32F413ZH_DISCOVERY"

#include "hal_target.h"

// Mapping
#define HEADER_CONNECTOR_CN1_D1  	PC10
#define HEADER_CONNECTOR_CN1_D2  	PC11
#define HEADER_CONNECTOR_CN1_D3  	PA6
#define HEADER_CONNECTOR_CN1_D4  	// Pin not routed
#define HEADER_CONNECTOR_CN1_D5  	PC12
#define HEADER_CONNECTOR_CN1_D6  	// Pin not routed
#define HEADER_CONNECTOR_CN1_D7  	PC8
#define HEADER_CONNECTOR_CN1_D8  	PC9
#define HEADER_CONNECTOR_CN1_D9  	// Pin not routed
#define HEADER_CONNECTOR_CN1_D10 	PF11

#define HEADER_CONNECTOR_CN2_D1  	// Pin not routed
#define HEADER_CONNECTOR_CN2_D2  	PA11
#define HEADER_CONNECTOR_CN2_D3  	PA12
#define HEADER_CONNECTOR_CN2_D4  	// Pin not routed
#define HEADER_CONNECTOR_CN2_D5  	// Pin not routed

#define HEADER_CONNECTOR_CN6_D1  	PA4
#define HEADER_CONNECTOR_CN6_D2  	PB8
#define HEADER_CONNECTOR_CN6_D3  	PA15
#define HEADER_CONNECTOR_CN6_D4  	PB5
#define HEADER_CONNECTOR_CN6_D5  	PB4
#define HEADER_CONNECTOR_CN6_D6  	PB12
#define HEADER_CONNECTOR_CN6_D7  	// Pin not routed
#define HEADER_CONNECTOR_CN6_D8  	// Pin not routed
#define HEADER_CONNECTOR_CN6_D9  	PB11
#define HEADER_CONNECTOR_CN6_D10 	PB10

#define HEADER_CONNECTOR_CN8_D1  	PF6
#define HEADER_CONNECTOR_CN8_D2  	PF7
#define HEADER_CONNECTOR_CN8_D3  	PG13
#define HEADER_CONNECTOR_CN8_D4  	PF10
#define HEADER_CONNECTOR_CN8_D5  	PB6
#define HEADER_CONNECTOR_CN8_D6  	PE6
#define HEADER_CONNECTOR_CN8_D7  	PB0
#define HEADER_CONNECTOR_CN8_D8  	PC13

#define HEADER_CONNECTOR_CN9_D1  	PC0
#define HEADER_CONNECTOR_CN9_D2  	PA1
#define HEADER_CONNECTOR_CN9_D3  	PA2
#define HEADER_CONNECTOR_CN9_D4  	PA5
#define HEADER_CONNECTOR_CN9_D5  	PB1
#define HEADER_CONNECTOR_CN9_D6  	PC4

#define HEADER_CONNECTOR_CN10_D1 	// Pin not routed
#define HEADER_CONNECTOR_CN10_D2 	PC1
#define HEADER_CONNECTOR_CN10_D3 	// Pin not routed
#define HEADER_CONNECTOR_CN10_D4 	PC7
#define HEADER_CONNECTOR_CN10_D5 	PC6
#define HEADER_CONNECTOR_CN10_D6 	// Pin not routed
#define HEADER_CONNECTOR_CN10_D7 	PB13
#define HEADER_CONNECTOR_CN10_D8 	// Pin not routed
#define HEADER_CONNECTOR_CN10_D9 	// Pin not routed
#define HEADER_CONNECTOR_CN10_D10	// Pin not routed

#define HEADER_CONNECTOR_CN11_D1 	// Pin not routed
#define HEADER_CONNECTOR_CN11_D2 	PA13
#define HEADER_CONNECTOR_CN11_D3 	// Pin not routed
#define HEADER_CONNECTOR_CN11_D4 	PA14
#define HEADER_CONNECTOR_CN11_D5 	// Pin not routed
#define HEADER_CONNECTOR_CN11_D6 	PB3
#define HEADER_CONNECTOR_CN11_D7 	// Pin not routed
#define HEADER_CONNECTOR_CN11_D8 	// Pin not routed
#define HEADER_CONNECTOR_CN11_D9 	// Pin not routed
#define HEADER_CONNECTOR_CN11_D10	// Pin not routed

#define HEADER_CONNECTOR_CN12_D1 	// Pin not routed
#define HEADER_CONNECTOR_CN12_D2 	// Pin not routed
#define HEADER_CONNECTOR_CN12_D3 	PD2
#define HEADER_CONNECTOR_CN12_D4 	PA8
#define HEADER_CONNECTOR_CN12_D5 	PA7
#define HEADER_CONNECTOR_CN12_D6 	PD6
#define HEADER_CONNECTOR_CN12_D7 	PB7
#define HEADER_CONNECTOR_CN12_D8 	// Pin not routed
#define HEADER_CONNECTOR_CN12_D9 	// Pin not routed
#define HEADER_CONNECTOR_CN12_D10	// Pin not routed
#define HEADER_CONNECTOR_CN12_D11	// Pin not routed
#define HEADER_CONNECTOR_CN12_D12	PE4
#define HEADER_CONNECTOR_CN12_D13	// Pin not routed
#define HEADER_CONNECTOR_CN12_D14	// Pin not routed
#define HEADER_CONNECTOR_CN12_D15	// Pin not routed
#define HEADER_CONNECTOR_CN12_D16	// Pin not routed
#define HEADER_CONNECTOR_CN12_D17	// Pin not routed
#define HEADER_CONNECTOR_CN12_D18	// Pin not routed
#define HEADER_CONNECTOR_CN12_D19	// Pin not routed
#define HEADER_CONNECTOR_CN12_D20	// Pin not routed

#define HEADER_CONNECTOR_CN15_D1 	PA9
#define HEADER_CONNECTOR_CN15_D2 	PA11
#define HEADER_CONNECTOR_CN15_D3 	PA12
#define HEADER_CONNECTOR_CN15_D4 	PA10
#define HEADER_CONNECTOR_CN15_D5 	// Pin not routed

#define HEADER_CONNECTOR_CN16_D1 	// Pin not routed
#define HEADER_CONNECTOR_CN16_D2 	PB14
#define HEADER_CONNECTOR_CN16_D3 	PD10
#define HEADER_CONNECTOR_CN16_D4 	PD9
#define HEADER_CONNECTOR_CN16_D5 	PD8
#define HEADER_CONNECTOR_CN16_D6 	PE15
#define HEADER_CONNECTOR_CN16_D7 	PE14
#define HEADER_CONNECTOR_CN16_D8 	PE13
#define HEADER_CONNECTOR_CN16_D9 	PE12
#define HEADER_CONNECTOR_CN16_D10	PE11
#define HEADER_CONNECTOR_CN16_D11	PE13
#define HEADER_CONNECTOR_CN16_D12	PE9
#define HEADER_CONNECTOR_CN16_D13	PE8
#define HEADER_CONNECTOR_CN16_D14	PE7
#define HEADER_CONNECTOR_CN16_D15	PD1
#define HEADER_CONNECTOR_CN16_D16	PD0
#define HEADER_CONNECTOR_CN16_D17	PD15
#define HEADER_CONNECTOR_CN16_D18	PD14
#define HEADER_CONNECTOR_CN16_D19	PD4
#define HEADER_CONNECTOR_CN16_D20	PD5
#define HEADER_CONNECTOR_CN16_D21	PF0
#define HEADER_CONNECTOR_CN16_D22	PG10
#define HEADER_CONNECTOR_CN16_D23	PB13
#define HEADER_CONNECTOR_CN16_D24	// Pin not routed
#define HEADER_CONNECTOR_CN16_D25	// Pin not routed
#define HEADER_CONNECTOR_CN16_D26	// Pin not routed
#define HEADER_CONNECTOR_CN16_D27	// Pin not routed
#define HEADER_CONNECTOR_CN16_D28	// Pin not routed
#define HEADER_CONNECTOR_CN16_D29	// Pin not routed

#ifdef __cplusplus
}
#endif

#endif    // _BOARD_H_
// ------------------------------------------------------------------------- END
