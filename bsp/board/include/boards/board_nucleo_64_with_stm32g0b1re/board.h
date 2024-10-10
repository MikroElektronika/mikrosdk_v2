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

#define BOARD_NAME "Nucleo-G0B1RE"

#include "hal_target.h"

// Mapping
#define HEADER_CONNECTOR_CN1_D1 	PC10
#define HEADER_CONNECTOR_CN1_D2 	PC11
#define HEADER_CONNECTOR_CN1_D3 	PC12
#define HEADER_CONNECTOR_CN1_D4 	PD2
#define HEADER_CONNECTOR_CN1_D5 	// Pin not routed
#define HEADER_CONNECTOR_CN1_D6 	// Pin not routed
#define HEADER_CONNECTOR_CN1_D7 	PA14
#define HEADER_CONNECTOR_CN1_D8 	// Pin not routed
#define HEADER_CONNECTOR_CN1_D9 	PD0
#define HEADER_CONNECTOR_CN1_D10 	PD1
#define HEADER_CONNECTOR_CN1_D11 	PD3
#define HEADER_CONNECTOR_CN1_D12 	// Pin not routed
#define HEADER_CONNECTOR_CN1_D13 	PA13
#define HEADER_CONNECTOR_CN1_D14 	// Pin not routed
#define HEADER_CONNECTOR_CN1_D15 	PD4
#define HEADER_CONNECTOR_CN1_D16 	// Pin not routed
#define HEADER_CONNECTOR_CN1_D17 	PA15
#define HEADER_CONNECTOR_CN1_D18 	// Pin not routed
#define HEADER_CONNECTOR_CN1_D19 	// Pin not routed
#define HEADER_CONNECTOR_CN1_D20 	// Pin not routed
#define HEADER_CONNECTOR_CN1_D21 	PB7
#define HEADER_CONNECTOR_CN1_D22 	// Pin not routed
#define HEADER_CONNECTOR_CN1_D23 	PC13
#define HEADER_CONNECTOR_CN1_D24 	// Pin not routed
#define HEADER_CONNECTOR_CN1_D25 	PC14
#define HEADER_CONNECTOR_CN1_D26 	PD5
#define HEADER_CONNECTOR_CN1_D27 	PC15
#define HEADER_CONNECTOR_CN1_D28 	PA0
#define HEADER_CONNECTOR_CN1_D29 	PF0
#define HEADER_CONNECTOR_CN1_D30 	PA1
#define HEADER_CONNECTOR_CN1_D31 	PF1
#define HEADER_CONNECTOR_CN1_D32 	PA4
#define HEADER_CONNECTOR_CN1_D33 	// Pin not routed
#define HEADER_CONNECTOR_CN1_D34 	PB1
#define HEADER_CONNECTOR_CN1_D35 	PC2
#define HEADER_CONNECTOR_CN1_D36 	PB9
#define HEADER_CONNECTOR_CN1_D37 	PC3
#define HEADER_CONNECTOR_CN1_D38 	PB8

#define HEADER_CONNECTOR_CN2_D1 	PC9
#define HEADER_CONNECTOR_CN2_D2 	PC8
#define HEADER_CONNECTOR_CN2_D3 	PB8
#define HEADER_CONNECTOR_CN2_D4 	PC6
#define HEADER_CONNECTOR_CN2_D5 	PB9
#define HEADER_CONNECTOR_CN2_D6 	PA3
#define HEADER_CONNECTOR_CN2_D7 	// Pin not routed
#define HEADER_CONNECTOR_CN2_D8 	// Pin not routed
#define HEADER_CONNECTOR_CN2_D9 	// Pin not routed
#define HEADER_CONNECTOR_CN2_D10 	PD6
#define HEADER_CONNECTOR_CN2_D11 	PA5
#define HEADER_CONNECTOR_CN2_D12 	PA12
#define HEADER_CONNECTOR_CN2_D13 	PA6
#define HEADER_CONNECTOR_CN2_D14 	PA11
#define HEADER_CONNECTOR_CN2_D15 	PA7
#define HEADER_CONNECTOR_CN2_D16 	PC1
#define HEADER_CONNECTOR_CN2_D17 	PB0
#define HEADER_CONNECTOR_CN2_D18 	PC0
#define HEADER_CONNECTOR_CN2_D19 	PC7
#define HEADER_CONNECTOR_CN2_D20 	// Pin not routed
#define HEADER_CONNECTOR_CN2_D21 	PA9
#define HEADER_CONNECTOR_CN2_D22 	PB2
#define HEADER_CONNECTOR_CN2_D23 	PA8
#define HEADER_CONNECTOR_CN2_D24 	PB6
#define HEADER_CONNECTOR_CN2_D25 	PB14
#define HEADER_CONNECTOR_CN2_D26 	PB15
#define HEADER_CONNECTOR_CN2_D27 	PB4
#define HEADER_CONNECTOR_CN2_D28 	PB10
#define HEADER_CONNECTOR_CN2_D29 	PB5
#define HEADER_CONNECTOR_CN2_D30 	PB13
#define HEADER_CONNECTOR_CN2_D31 	PB3
#define HEADER_CONNECTOR_CN2_D32 	// Pin not routed
#define HEADER_CONNECTOR_CN2_D33 	PA10
#define HEADER_CONNECTOR_CN2_D34 	PA2
#define HEADER_CONNECTOR_CN2_D35 	PC4
#define HEADER_CONNECTOR_CN2_D36 	PD8
#define HEADER_CONNECTOR_CN2_D37 	PC5
#define HEADER_CONNECTOR_CN2_D38 	PD9

#define HEADER_CONNECTOR_CN5_D1 	PA9
#define HEADER_CONNECTOR_CN5_D2 	PC7
#define HEADER_CONNECTOR_CN5_D3 	PB0
#define HEADER_CONNECTOR_CN5_D4 	PA7
#define HEADER_CONNECTOR_CN5_D5 	PA6
#define HEADER_CONNECTOR_CN5_D6 	PA5
#define HEADER_CONNECTOR_CN5_D7 	// Pin not routed
#define HEADER_CONNECTOR_CN5_D8 	// Pin not routed
#define HEADER_CONNECTOR_CN5_D9 	PB9
#define HEADER_CONNECTOR_CN5_D10	PB8

#define HEADER_CONNECTOR_CN8_D1 	PA0
#define HEADER_CONNECTOR_CN8_D2 	PA1
#define HEADER_CONNECTOR_CN8_D3 	PA4
#define HEADER_CONNECTOR_CN8_D4 	PB1
#define HEADER_CONNECTOR_CN8_D5 	PB9
#define HEADER_CONNECTOR_CN8_D6 	PB8

#define HEADER_CONNECTOR_CN9_D1 	PC5
#define HEADER_CONNECTOR_CN9_D2 	PC4
#define HEADER_CONNECTOR_CN9_D3 	PA10
#define HEADER_CONNECTOR_CN9_D4 	PB3
#define HEADER_CONNECTOR_CN9_D5 	PB5
#define HEADER_CONNECTOR_CN9_D6 	PB4
#define HEADER_CONNECTOR_CN9_D7 	PB14
#define HEADER_CONNECTOR_CN9_D8 	PA8

#ifdef __cplusplus
}
#endif

#endif    // _BOARD_H_
// ------------------------------------------------------------------------- END
