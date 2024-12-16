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

#define BOARD_NAME "STM32F412ZG_DISCOVERY"

#include "hal_target.h"

// Mapping
#define HEADER_CONNECTOR_CN1_D1  	GPIO_PA1
#define HEADER_CONNECTOR_CN1_D2  	GPIO_PC1
#define HEADER_CONNECTOR_CN1_D3  	GPIO_PC3
#define HEADER_CONNECTOR_CN1_D4  	GPIO_PC4
#define HEADER_CONNECTOR_CN1_D5  	GPIO_PB9
#define HEADER_CONNECTOR_CN1_D6  	GPIO_PB0

#define HEADER_CONNECTOR_CN2_D1  	GPIO_PA5
#define HEADER_CONNECTOR_CN2_D2  	GPIO_PA6
#define HEADER_CONNECTOR_CN2_D3  	GPIO_PA7
#define HEADER_CONNECTOR_CN2_D4  	GPIO_PA15
#define HEADER_CONNECTOR_CN2_D5  	GPIO_PB8
#define HEADER_CONNECTOR_CN2_D6  	GPIO_PG10
#define HEADER_CONNECTOR_CN2_D7  	// Pin not routed
#define HEADER_CONNECTOR_CN2_D8  	GPIO_PG11

#define HEADER_CONNECTOR_CN11_D1 	GPIO_PG9
#define HEADER_CONNECTOR_CN11_D2 	GPIO_PG14
#define HEADER_CONNECTOR_CN11_D3 	GPIO_PG13
#define HEADER_CONNECTOR_CN11_D4 	GPIO_PF4
#define HEADER_CONNECTOR_CN11_D5 	GPIO_PG12
#define HEADER_CONNECTOR_CN11_D6 	GPIO_PF10
#define HEADER_CONNECTOR_CN11_D7 	GPIO_PF3
#define HEADER_CONNECTOR_CN11_D8 	GPIO_PG11

#define HEADER_CONNECTOR_CN12_D1 	GPIO_PG10
#define HEADER_CONNECTOR_CN12_D2 	GPIO_PB8
#define HEADER_CONNECTOR_CN12_D3 	GPIO_PA15
#define HEADER_CONNECTOR_CN12_D4 	GPIO_PA7
#define HEADER_CONNECTOR_CN12_D5 	GPIO_PA6
#define HEADER_CONNECTOR_CN12_D6 	GPIO_PA5
#define HEADER_CONNECTOR_CN12_D7 	// Pin not routed
#define HEADER_CONNECTOR_CN12_D8 	// Pin not routed
#define HEADER_CONNECTOR_CN12_D9 	GPIO_PB9
#define HEADER_CONNECTOR_CN12_D10	GPIO_PB10

#define HEADER_CONNECTOR_P1_D1   	// Pin not routed
#define HEADER_CONNECTOR_P1_D2   	// Pin not routed
#define HEADER_CONNECTOR_P1_D3   	// Pin not routed
#define HEADER_CONNECTOR_P1_D4   	// Pin not routed
#define HEADER_CONNECTOR_P1_D5   	// Pin not routed
#define HEADER_CONNECTOR_P1_D6   	// Pin not routed
#define HEADER_CONNECTOR_P1_D7   	GPIO_PC1
#define HEADER_CONNECTOR_P1_D8   	// Pin not routed
#define HEADER_CONNECTOR_P1_D9   	GPIO_PC3
#define HEADER_CONNECTOR_P1_D10  	// Pin not routed
#define HEADER_CONNECTOR_P1_D11  	GPIO_PA1
#define HEADER_CONNECTOR_P1_D12  	// Pin not routed
#define HEADER_CONNECTOR_P1_D13  	GPIO_PA3
#define HEADER_CONNECTOR_P1_D14  	// Pin not routed
#define HEADER_CONNECTOR_P1_D15  	GPIO_PA5
#define HEADER_CONNECTOR_P1_D16  	// Pin not routed
#define HEADER_CONNECTOR_P1_D17  	GPIO_PA7
#define HEADER_CONNECTOR_P1_D18  	// Pin not routed
#define HEADER_CONNECTOR_P1_D19  	GPIO_PC5
#define HEADER_CONNECTOR_P1_D20  	// Pin not routed
#define HEADER_CONNECTOR_P1_D21  	GPIO_PB1
#define HEADER_CONNECTOR_P1_D22  	// Pin not routed
#define HEADER_CONNECTOR_P1_D23  	// Pin not routed
#define HEADER_CONNECTOR_P1_D24  	// Pin not routed
#define HEADER_CONNECTOR_P1_D25  	GPIO_PF3
#define HEADER_CONNECTOR_P1_D26  	// Pin not routed
#define HEADER_CONNECTOR_P1_D27  	GPIO_PF10
#define HEADER_CONNECTOR_P1_D28  	// Pin not routed
#define HEADER_CONNECTOR_P1_D29  	// Pin not routed
#define HEADER_CONNECTOR_P1_D30  	// Pin not routed
#define HEADER_CONNECTOR_P1_D31  	GPIO_PG2
#define HEADER_CONNECTOR_P1_D32  	// Pin not routed
#define HEADER_CONNECTOR_P1_D33  	GPIO_PG9
#define HEADER_CONNECTOR_P1_D34  	// Pin not routed
#define HEADER_CONNECTOR_P1_D35  	GPIO_PB11
#define HEADER_CONNECTOR_P1_D36  	// Pin not routed
#define HEADER_CONNECTOR_P1_D37  	GPIO_PB13
#define HEADER_CONNECTOR_P1_D38  	// Pin not routed
#define HEADER_CONNECTOR_P1_D39  	GPIO_PB15
#define HEADER_CONNECTOR_P1_D40  	// Pin not routed
#define HEADER_CONNECTOR_P1_D41  	// Pin not routed
#define HEADER_CONNECTOR_P1_D42  	// Pin not routed
#define HEADER_CONNECTOR_P1_D43  	// Pin not routed
#define HEADER_CONNECTOR_P1_D44  	// Pin not routed
#define HEADER_CONNECTOR_P1_D45  	GPIO_PD13
#define HEADER_CONNECTOR_P1_D46  	// Pin not routed
#define HEADER_CONNECTOR_P1_D47  	// Pin not routed
#define HEADER_CONNECTOR_P1_D48  	// Pin not routed
#define HEADER_CONNECTOR_P1_D49  	// Pin not routed

#define HEADER_CONNECTOR_P2_D1   	// Pin not routed
#define HEADER_CONNECTOR_P2_D2   	// Pin not routed
#define HEADER_CONNECTOR_P2_D3   	// Pin not routed
#define HEADER_CONNECTOR_P2_D4   	// Pin not routed
#define HEADER_CONNECTOR_P2_D5   	// Pin not routed
#define HEADER_CONNECTOR_P2_D6   	// Pin not routed
#define HEADER_CONNECTOR_P2_D7   	GPIO_PH0
#define HEADER_CONNECTOR_P2_D8   	// Pin not routed
#define HEADER_CONNECTOR_P2_D9   	GPIO_PC14
#define HEADER_CONNECTOR_P2_D10  	// Pin not routed
#define HEADER_CONNECTOR_P2_D11  	GPIO_PE6
#define HEADER_CONNECTOR_P2_D12  	// Pin not routed
#define HEADER_CONNECTOR_P2_D13  	GPIO_PE4
#define HEADER_CONNECTOR_P2_D14  	// Pin not routed
#define HEADER_CONNECTOR_P2_D15  	GPIO_PE2
#define HEADER_CONNECTOR_P2_D16  	// Pin not routed
#define HEADER_CONNECTOR_P2_D17  	GPIO_PE0
#define HEADER_CONNECTOR_P2_D18  	// Pin not routed
#define HEADER_CONNECTOR_P2_D19  	GPIO_PB8
#define HEADER_CONNECTOR_P2_D20  	// Pin not routed
#define HEADER_CONNECTOR_P2_D21  	// Pin not routed
#define HEADER_CONNECTOR_P2_D22  	// Pin not routed
#define HEADER_CONNECTOR_P2_D23  	GPIO_PB6
#define HEADER_CONNECTOR_P2_D24  	// Pin not routed
#define HEADER_CONNECTOR_P2_D25  	GPIO_PB4
#define HEADER_CONNECTOR_P2_D26  	// Pin not routed
#define HEADER_CONNECTOR_P2_D27  	// Pin not routed
#define HEADER_CONNECTOR_P2_D28  	// Pin not routed
#define HEADER_CONNECTOR_P2_D29  	// Pin not routed
#define HEADER_CONNECTOR_P2_D30  	// Pin not routed
#define HEADER_CONNECTOR_P2_D31  	GPIO_PG10
#define HEADER_CONNECTOR_P2_D32  	// Pin not routed
#define HEADER_CONNECTOR_P2_D33  	GPIO_PG12
#define HEADER_CONNECTOR_P2_D34  	// Pin not routed
#define HEADER_CONNECTOR_P2_D35  	GPIO_PG14
#define HEADER_CONNECTOR_P2_D36  	// Pin not routed
#define HEADER_CONNECTOR_P2_D37  	// Pin not routed
#define HEADER_CONNECTOR_P2_D38  	// Pin not routed
#define HEADER_CONNECTOR_P2_D39  	GPIO_PA14
#define HEADER_CONNECTOR_P2_D40  	// Pin not routed
#define HEADER_CONNECTOR_P2_D41  	GPIO_PA10
#define HEADER_CONNECTOR_P2_D42  	// Pin not routed
#define HEADER_CONNECTOR_P2_D43  	GPIO_PA8
#define HEADER_CONNECTOR_P2_D44  	// Pin not routed
#define HEADER_CONNECTOR_P2_D45  	// Pin not routed
#define HEADER_CONNECTOR_P2_D46  	// Pin not routed
#define HEADER_CONNECTOR_P2_D47  	GPIO_PC6
#define HEADER_CONNECTOR_P2_D48  	// Pin not routed
#define HEADER_CONNECTOR_P2_D49  	// Pin not routed

#ifdef __cplusplus
}
#endif

#endif    // _BOARD_H_
// ------------------------------------------------------------------------- END
