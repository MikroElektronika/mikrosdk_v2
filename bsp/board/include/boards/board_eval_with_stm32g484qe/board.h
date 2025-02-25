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

#define BOARD_NAME "STM32G484QE-Eval"

#include "hal_target.h"

// Mapping
#define HEADER_CONNECTOR_CN1_D1  	GPIO_PG8
#define HEADER_CONNECTOR_CN1_D2  	// Pin not routed
#define HEADER_CONNECTOR_CN1_D3  	GPIO_PG7
#define HEADER_CONNECTOR_CN1_D4  	// Pin not routed
#define HEADER_CONNECTOR_CN1_D5  	// Pin not routed
#define HEADER_CONNECTOR_CN1_D6  	// Pin not routed
#define HEADER_CONNECTOR_CN1_D7  	// Pin not routed
#define HEADER_CONNECTOR_CN1_D8  	// Pin not routed

#define HEADER_CONNECTOR_CN2_D1  	GPIO_PE15
#define HEADER_CONNECTOR_CN2_D2  	// Pin not routed
#define HEADER_CONNECTOR_CN2_D3  	GPIO_PE9
#define HEADER_CONNECTOR_CN2_D4  	// Pin not routed
#define HEADER_CONNECTOR_CN2_D5  	GPIO_PE8
#define HEADER_CONNECTOR_CN2_D6  	// Pin not routed
#define HEADER_CONNECTOR_CN2_D7  	GPIO_PE11
#define HEADER_CONNECTOR_CN2_D8  	// Pin not routed
#define HEADER_CONNECTOR_CN2_D9  	GPIO_PE10
#define HEADER_CONNECTOR_CN2_D10 	// Pin not routed
#define HEADER_CONNECTOR_CN2_D11 	GPIO_PE13
#define HEADER_CONNECTOR_CN2_D12 	// Pin not routed
#define HEADER_CONNECTOR_CN2_D13 	GPIO_PE12
#define HEADER_CONNECTOR_CN2_D14 	GPIO_PC1
#define HEADER_CONNECTOR_CN2_D15 	GPIO_PC2
#define HEADER_CONNECTOR_CN2_D16 	// Pin not routed
#define HEADER_CONNECTOR_CN2_D17 	GPIO_PC3
#define HEADER_CONNECTOR_CN2_D18 	// Pin not routed
#define HEADER_CONNECTOR_CN2_D19 	GPIO_PC0
#define HEADER_CONNECTOR_CN2_D20 	// Pin not routed
#define HEADER_CONNECTOR_CN2_D21 	GPIO_PE4
#define HEADER_CONNECTOR_CN2_D22 	// Pin not routed
#define HEADER_CONNECTOR_CN2_D23 	GPIO_PE5
#define HEADER_CONNECTOR_CN2_D24 	GPIO_PD8
#define HEADER_CONNECTOR_CN2_D25 	// Pin not routed
#define HEADER_CONNECTOR_CN2_D26 	GPIO_PC4
#define HEADER_CONNECTOR_CN2_D27 	GPIO_PE2
#define HEADER_CONNECTOR_CN2_D28 	// Pin not routed
#define HEADER_CONNECTOR_CN2_D29 	GPIO_PE3
#define HEADER_CONNECTOR_CN2_D30 	GPIO_PD2
#define HEADER_CONNECTOR_CN2_D31 	GPIO_PA0
#define HEADER_CONNECTOR_CN2_D32 	GPIO_PD9
#define HEADER_CONNECTOR_CN2_D33 	GPIO_PD4
#define HEADER_CONNECTOR_CN2_D34 	GPIO_PA15

#define HEADER_CONNECTOR_CN4_D1  	GPIO_PB7
#define HEADER_CONNECTOR_CN4_D2  	// Pin not routed
#define HEADER_CONNECTOR_CN4_D3  	GPIO_PC6
#define HEADER_CONNECTOR_CN4_D4  	// Pin not routed
#define HEADER_CONNECTOR_CN4_D5  	GPIO_PC10
#define HEADER_CONNECTOR_CN4_D6  	// Pin not routed
#define HEADER_CONNECTOR_CN4_D7  	GPIO_PC7
#define HEADER_CONNECTOR_CN4_D8  	// Pin not routed
#define HEADER_CONNECTOR_CN4_D9  	GPIO_PC11
#define HEADER_CONNECTOR_CN4_D10 	// Pin not routed
#define HEADER_CONNECTOR_CN4_D11 	GPIO_PC8
#define HEADER_CONNECTOR_CN4_D12 	// Pin not routed
#define HEADER_CONNECTOR_CN4_D13 	GPIO_PC12
#define HEADER_CONNECTOR_CN4_D14 	GPIO_PE14
#define HEADER_CONNECTOR_CN4_D15 	GPIO_PD10
#define HEADER_CONNECTOR_CN4_D16 	// Pin not routed
#define HEADER_CONNECTOR_CN4_D17 	GPIO_PD12
#define HEADER_CONNECTOR_CN4_D18 	// Pin not routed
#define HEADER_CONNECTOR_CN4_D19 	GPIO_PD13
#define HEADER_CONNECTOR_CN4_D20 	// Pin not routed
#define HEADER_CONNECTOR_CN4_D21 	GPIO_PD15
#define HEADER_CONNECTOR_CN4_D22 	// Pin not routed
#define HEADER_CONNECTOR_CN4_D23 	GPIO_PF10
#define HEADER_CONNECTOR_CN4_D24 	GPIO_PD8
#define HEADER_CONNECTOR_CN4_D25 	// Pin not routed
#define HEADER_CONNECTOR_CN4_D26 	GPIO_PE7
#define HEADER_CONNECTOR_CN4_D27 	GPIO_PE2
#define HEADER_CONNECTOR_CN4_D28 	// Pin not routed
#define HEADER_CONNECTOR_CN4_D29 	GPIO_PE3
#define HEADER_CONNECTOR_CN4_D30 	GPIO_PD2
#define HEADER_CONNECTOR_CN4_D31 	GPIO_PF6
#define HEADER_CONNECTOR_CN4_D32 	GPIO_PD9
#define HEADER_CONNECTOR_CN4_D33 	GPIO_PF7
#define HEADER_CONNECTOR_CN4_D34 	GPIO_PD11

#define HEADER_CONNECTOR_CN28_D1 	// Pin not routed
#define HEADER_CONNECTOR_CN28_D2 	GPIO_PF8
#define HEADER_CONNECTOR_CN28_D3 	GPIO_PB15
#define HEADER_CONNECTOR_CN28_D4 	// Pin not routed
#define HEADER_CONNECTOR_CN28_D5 	GPIO_PF9
#define HEADER_CONNECTOR_CN28_D6 	// Pin not routed
#define HEADER_CONNECTOR_CN28_D7 	GPIO_PV14
#define HEADER_CONNECTOR_CN28_D8 	// Pin not routed
#define HEADER_CONNECTOR_CN28_D9 	// Pin not routed
#define HEADER_CONNECTOR_CN28_D10	// Pin not routed

#ifdef __cplusplus
}
#endif

#endif    // _BOARD_H_
// ------------------------------------------------------------------------- END
