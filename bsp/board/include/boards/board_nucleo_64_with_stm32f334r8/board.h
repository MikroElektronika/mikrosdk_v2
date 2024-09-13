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

#define BOARD_NAME "Nucleo-F334R8"

#include "hal_target.h"

// Mapping
#define HEADER_CONNECTOR_CN5_D1  	PA9
#define HEADER_CONNECTOR_CN5_D2  	PC7
#define HEADER_CONNECTOR_CN5_D3  	PB6
#define HEADER_CONNECTOR_CN5_D4  	PA7
#define HEADER_CONNECTOR_CN5_D5  	PA6
#define HEADER_CONNECTOR_CN5_D6  	PA5
#define HEADER_CONNECTOR_CN5_D7  	// Pin not routed
#define HEADER_CONNECTOR_CN5_D8  	// Pin not routed
#define HEADER_CONNECTOR_CN5_D9  	PB9
#define HEADER_CONNECTOR_CN5_D10 	PB8

#define HEADER_CONNECTOR_CN6_D1  	// Pin not routed
#define HEADER_CONNECTOR_CN6_D2  	// Pin not routed
#define HEADER_CONNECTOR_CN6_D3  	// Pin not routed
#define HEADER_CONNECTOR_CN6_D4  	// Pin not routed
#define HEADER_CONNECTOR_CN6_D5  	// Pin not routed
#define HEADER_CONNECTOR_CN6_D6  	// Pin not routed
#define HEADER_CONNECTOR_CN6_D7  	// Pin not routed
#define HEADER_CONNECTOR_CN6_D8  	// Pin not routed

#define HEADER_CONNECTOR_CN7_D1  	PC10
#define HEADER_CONNECTOR_CN7_D2  	// Pin not routed
#define HEADER_CONNECTOR_CN7_D3  	PC12
#define HEADER_CONNECTOR_CN7_D4  	// Pin not routed
#define HEADER_CONNECTOR_CN7_D5  	// Pin not routed
#define HEADER_CONNECTOR_CN7_D6  	// Pin not routed
#define HEADER_CONNECTOR_CN7_D7  	// Pin not routed
#define HEADER_CONNECTOR_CN7_D8  	// Pin not routed
#define HEADER_CONNECTOR_CN7_D9  	// Pin not routed
#define HEADER_CONNECTOR_CN7_D10 	// Pin not routed
#define HEADER_CONNECTOR_CN7_D11 	// Pin not routed
#define HEADER_CONNECTOR_CN7_D12 	// Pin not routed
#define HEADER_CONNECTOR_CN7_D13 	PA13
#define HEADER_CONNECTOR_CN7_D14 	// Pin not routed
#define HEADER_CONNECTOR_CN7_D15 	PA14
#define HEADER_CONNECTOR_CN7_D16 	// Pin not routed
#define HEADER_CONNECTOR_CN7_D17 	PA15
#define HEADER_CONNECTOR_CN7_D18 	// Pin not routed
#define HEADER_CONNECTOR_CN7_D19 	// Pin not routed
#define HEADER_CONNECTOR_CN7_D20 	// Pin not routed
#define HEADER_CONNECTOR_CN7_D21 	PB7
#define HEADER_CONNECTOR_CN7_D22 	// Pin not routed
#define HEADER_CONNECTOR_CN7_D23 	PC13
#define HEADER_CONNECTOR_CN7_D24 	// Pin not routed
#define HEADER_CONNECTOR_CN7_D25 	PC14
#define HEADER_CONNECTOR_CN7_D26 	// Pin not routed
#define HEADER_CONNECTOR_CN7_D27 	PC15
#define HEADER_CONNECTOR_CN7_D28 	// Pin not routed
#define HEADER_CONNECTOR_CN7_D29 	PH0
#define HEADER_CONNECTOR_CN7_D30 	// Pin not routed
#define HEADER_CONNECTOR_CN7_D31 	PH1
#define HEADER_CONNECTOR_CN7_D32 	// Pin not routed
#define HEADER_CONNECTOR_CN7_D33 	// Pin not routed
#define HEADER_CONNECTOR_CN7_D34 	// Pin not routed
#define HEADER_CONNECTOR_CN7_D35 	PC2
#define HEADER_CONNECTOR_CN7_D36 	// Pin not routed
#define HEADER_CONNECTOR_CN7_D37 	PC3

#define HEADER_CONNECTOR_CN8_D1  	PA0
#define HEADER_CONNECTOR_CN8_D2  	PA1
#define HEADER_CONNECTOR_CN8_D3  	PA4
#define HEADER_CONNECTOR_CN8_D4  	PB0
#define HEADER_CONNECTOR_CN8_D5  	PB9
#define HEADER_CONNECTOR_CN8_D6  	PB8

#define HEADER_CONNECTOR_CN9_D1  	PA3
#define HEADER_CONNECTOR_CN9_D2  	PA2
#define HEADER_CONNECTOR_CN9_D3  	PA10
#define HEADER_CONNECTOR_CN9_D4  	PB3
#define HEADER_CONNECTOR_CN9_D5  	PB5
#define HEADER_CONNECTOR_CN9_D6  	PB4
#define HEADER_CONNECTOR_CN9_D7  	PB10
#define HEADER_CONNECTOR_CN9_D8  	PA8

#define HEADER_CONNECTOR_CN10_D1 	PC9
#define HEADER_CONNECTOR_CN10_D2 	// Pin not routed
#define HEADER_CONNECTOR_CN10_D3 	PB8
#define HEADER_CONNECTOR_CN10_D4 	// Pin not routed
#define HEADER_CONNECTOR_CN10_D5 	PB9
#define HEADER_CONNECTOR_CN10_D6 	// Pin not routed
#define HEADER_CONNECTOR_CN10_D7 	// Pin not routed
#define HEADER_CONNECTOR_CN10_D8 	// Pin not routed
#define HEADER_CONNECTOR_CN10_D9 	// Pin not routed
#define HEADER_CONNECTOR_CN10_D10	// Pin not routed
#define HEADER_CONNECTOR_CN10_D11	PA5
#define HEADER_CONNECTOR_CN10_D12	// Pin not routed
#define HEADER_CONNECTOR_CN10_D13	PA6
#define HEADER_CONNECTOR_CN10_D14	// Pin not routed
#define HEADER_CONNECTOR_CN10_D15	PA7
#define HEADER_CONNECTOR_CN10_D16	// Pin not routed
#define HEADER_CONNECTOR_CN10_D17	PB6
#define HEADER_CONNECTOR_CN10_D18	// Pin not routed
#define HEADER_CONNECTOR_CN10_D19	PC7
#define HEADER_CONNECTOR_CN10_D20	// Pin not routed
#define HEADER_CONNECTOR_CN10_D21	PA9
#define HEADER_CONNECTOR_CN10_D22	// Pin not routed
#define HEADER_CONNECTOR_CN10_D23	PA8
#define HEADER_CONNECTOR_CN10_D24	// Pin not routed
#define HEADER_CONNECTOR_CN10_D25	PB10
#define HEADER_CONNECTOR_CN10_D26	// Pin not routed
#define HEADER_CONNECTOR_CN10_D27	PB4
#define HEADER_CONNECTOR_CN10_D28	// Pin not routed
#define HEADER_CONNECTOR_CN10_D29	PB5
#define HEADER_CONNECTOR_CN10_D30	// Pin not routed
#define HEADER_CONNECTOR_CN10_D31	PB3
#define HEADER_CONNECTOR_CN10_D32	// Pin not routed
#define HEADER_CONNECTOR_CN10_D33	PA10
#define HEADER_CONNECTOR_CN10_D34	// Pin not routed
#define HEADER_CONNECTOR_CN10_D35	PA2
#define HEADER_CONNECTOR_CN10_D36	// Pin not routed
#define HEADER_CONNECTOR_CN10_D37	PA3

#ifdef __cplusplus
}
#endif

#endif    // _BOARD_H_
// ------------------------------------------------------------------------- END
