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

#define BOARD_NAME "STM32F413ZH_DISCOVERY"

#include "hal_target.h"

// Mapping
#define HEADER_CONNECTOR_CN1_D1  	GPIO_PC10
#define HEADER_CONNECTOR_CN1_D2  	GPIO_PC11
#define HEADER_CONNECTOR_CN1_D3  	GPIO_PA6
#define HEADER_CONNECTOR_CN1_D4  	// Pin not routed
#define HEADER_CONNECTOR_CN1_D5  	GPIO_PC12
#define HEADER_CONNECTOR_CN1_D6  	// Pin not routed
#define HEADER_CONNECTOR_CN1_D7  	GPIO_PC8
#define HEADER_CONNECTOR_CN1_D8  	GPIO_PC9
#define HEADER_CONNECTOR_CN1_D9  	// Pin not routed
#define HEADER_CONNECTOR_CN1_D10 	GPIO_PF11

#define HEADER_CONNECTOR_CN2_D1  	// Pin not routed
#define HEADER_CONNECTOR_CN2_D2  	GPIO_PA11
#define HEADER_CONNECTOR_CN2_D3  	GPIO_PA12
#define HEADER_CONNECTOR_CN2_D4  	// Pin not routed
#define HEADER_CONNECTOR_CN2_D5  	// Pin not routed

#define HEADER_CONNECTOR_CN6_D1  	GPIO_PA4
#define HEADER_CONNECTOR_CN6_D2  	GPIO_PB8
#define HEADER_CONNECTOR_CN6_D3  	GPIO_PA15
#define HEADER_CONNECTOR_CN6_D4  	GPIO_PB5
#define HEADER_CONNECTOR_CN6_D5  	GPIO_PB4
#define HEADER_CONNECTOR_CN6_D6  	GPIO_PB12
#define HEADER_CONNECTOR_CN6_D7  	// Pin not routed
#define HEADER_CONNECTOR_CN6_D8  	// Pin not routed
#define HEADER_CONNECTOR_CN6_D9  	GPIO_PB11
#define HEADER_CONNECTOR_CN6_D10 	GPIO_PB10

#define HEADER_CONNECTOR_CN8_D1  	GPIO_PF6
#define HEADER_CONNECTOR_CN8_D2  	GPIO_PF7
#define HEADER_CONNECTOR_CN8_D3  	GPIO_PG13
#define HEADER_CONNECTOR_CN8_D4  	GPIO_PF10
#define HEADER_CONNECTOR_CN8_D5  	GPIO_PB6
#define HEADER_CONNECTOR_CN8_D6  	GPIO_PE6
#define HEADER_CONNECTOR_CN8_D7  	GPIO_PB0
#define HEADER_CONNECTOR_CN8_D8  	GPIO_PC13

#define HEADER_CONNECTOR_CN9_D1  	GPIO_PC0
#define HEADER_CONNECTOR_CN9_D2  	GPIO_PA1
#define HEADER_CONNECTOR_CN9_D3  	GPIO_PA2
#define HEADER_CONNECTOR_CN9_D4  	GPIO_PA5
#define HEADER_CONNECTOR_CN9_D5  	GPIO_PB1
#define HEADER_CONNECTOR_CN9_D6  	GPIO_PC4

#define HEADER_CONNECTOR_CN10_D1 	// Pin not routed
#define HEADER_CONNECTOR_CN10_D2 	GPIO_PC1
#define HEADER_CONNECTOR_CN10_D3 	// Pin not routed
#define HEADER_CONNECTOR_CN10_D4 	GPIO_PC7
#define HEADER_CONNECTOR_CN10_D5 	GPIO_PC6
#define HEADER_CONNECTOR_CN10_D6 	// Pin not routed
#define HEADER_CONNECTOR_CN10_D7 	GPIO_PB13
#define HEADER_CONNECTOR_CN10_D8 	// Pin not routed
#define HEADER_CONNECTOR_CN10_D9 	// Pin not routed
#define HEADER_CONNECTOR_CN10_D10	// Pin not routed

#define HEADER_CONNECTOR_CN11_D1 	// Pin not routed
#define HEADER_CONNECTOR_CN11_D2 	GPIO_PA13
#define HEADER_CONNECTOR_CN11_D3 	// Pin not routed
#define HEADER_CONNECTOR_CN11_D4 	GPIO_PA14
#define HEADER_CONNECTOR_CN11_D5 	// Pin not routed
#define HEADER_CONNECTOR_CN11_D6 	GPIO_PB3
#define HEADER_CONNECTOR_CN11_D7 	// Pin not routed
#define HEADER_CONNECTOR_CN11_D8 	// Pin not routed
#define HEADER_CONNECTOR_CN11_D9 	// Pin not routed
#define HEADER_CONNECTOR_CN11_D10	// Pin not routed

#define HEADER_CONNECTOR_CN12_D1 	// Pin not routed
#define HEADER_CONNECTOR_CN12_D2 	// Pin not routed
#define HEADER_CONNECTOR_CN12_D3 	GPIO_PD2
#define HEADER_CONNECTOR_CN12_D4 	GPIO_PA8
#define HEADER_CONNECTOR_CN12_D5 	GPIO_PA7
#define HEADER_CONNECTOR_CN12_D6 	GPIO_PD6
#define HEADER_CONNECTOR_CN12_D7 	GPIO_PB7
#define HEADER_CONNECTOR_CN12_D8 	// Pin not routed
#define HEADER_CONNECTOR_CN12_D9 	// Pin not routed
#define HEADER_CONNECTOR_CN12_D10	// Pin not routed
#define HEADER_CONNECTOR_CN12_D11	// Pin not routed
#define HEADER_CONNECTOR_CN12_D12	GPIO_PE4
#define HEADER_CONNECTOR_CN12_D13	// Pin not routed
#define HEADER_CONNECTOR_CN12_D14	// Pin not routed
#define HEADER_CONNECTOR_CN12_D15	// Pin not routed
#define HEADER_CONNECTOR_CN12_D16	// Pin not routed
#define HEADER_CONNECTOR_CN12_D17	// Pin not routed
#define HEADER_CONNECTOR_CN12_D18	// Pin not routed
#define HEADER_CONNECTOR_CN12_D19	// Pin not routed
#define HEADER_CONNECTOR_CN12_D20	// Pin not routed

#define HEADER_CONNECTOR_CN15_D1 	GPIO_PA9
#define HEADER_CONNECTOR_CN15_D2 	GPIO_PA11
#define HEADER_CONNECTOR_CN15_D3 	GPIO_PA12
#define HEADER_CONNECTOR_CN15_D4 	GPIO_PA10
#define HEADER_CONNECTOR_CN15_D5 	// Pin not routed

#define HEADER_CONNECTOR_CN16_D1 	// Pin not routed
#define HEADER_CONNECTOR_CN16_D2 	GPIO_PB14
#define HEADER_CONNECTOR_CN16_D3 	GPIO_PD10
#define HEADER_CONNECTOR_CN16_D4 	GPIO_PD9
#define HEADER_CONNECTOR_CN16_D5 	GPIO_PD8
#define HEADER_CONNECTOR_CN16_D6 	GPIO_PE15
#define HEADER_CONNECTOR_CN16_D7 	GPIO_PE14
#define HEADER_CONNECTOR_CN16_D8 	GPIO_PE13
#define HEADER_CONNECTOR_CN16_D9 	GPIO_PE12
#define HEADER_CONNECTOR_CN16_D10	GPIO_PE11
#define HEADER_CONNECTOR_CN16_D11	GPIO_PE13
#define HEADER_CONNECTOR_CN16_D12	GPIO_PE9
#define HEADER_CONNECTOR_CN16_D13	GPIO_PE8
#define HEADER_CONNECTOR_CN16_D14	GPIO_PE7
#define HEADER_CONNECTOR_CN16_D15	GPIO_PD1
#define HEADER_CONNECTOR_CN16_D16	GPIO_PD0
#define HEADER_CONNECTOR_CN16_D17	GPIO_PD15
#define HEADER_CONNECTOR_CN16_D18	GPIO_PD14
#define HEADER_CONNECTOR_CN16_D19	GPIO_PD4
#define HEADER_CONNECTOR_CN16_D20	GPIO_PD5
#define HEADER_CONNECTOR_CN16_D21	GPIO_PF0
#define HEADER_CONNECTOR_CN16_D22	GPIO_PG10
#define HEADER_CONNECTOR_CN16_D23	GPIO_PB13
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
