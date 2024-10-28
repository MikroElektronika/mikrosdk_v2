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

#define BOARD_NAME "STM32L476ZG-Eval"

#include "hal_target.h"

// Mapping
#define HEADER_CONNECTOR_CN6_D1     	// Pin not routed
#define HEADER_CONNECTOR_CN6_D2     	// Pin not routed
#define HEADER_CONNECTOR_CN6_D3     	PG6
#define HEADER_CONNECTOR_CN6_D4     	PG7
#define HEADER_CONNECTOR_CN6_D5     	PA13
#define HEADER_CONNECTOR_CN6_D6     	PA11
#define HEADER_CONNECTOR_CN6_D7     	PA12
#define HEADER_CONNECTOR_CN6_D8     	PA14
#define HEADER_CONNECTOR_CN6_D9     	PG8
#define HEADER_CONNECTOR_CN6_D10    	PG5
#define HEADER_CONNECTOR_CN6_D11    	// Pin not routed
#define HEADER_CONNECTOR_CN6_D12    	PG3
#define HEADER_CONNECTOR_CN6_D13    	PG2
#define HEADER_CONNECTOR_CN6_D14    	PG4
#define HEADER_CONNECTOR_CN6_D15    	PD3
#define HEADER_CONNECTOR_CN6_D16    	PD1
#define HEADER_CONNECTOR_CN6_D17    	PD0
#define HEADER_CONNECTOR_CN6_D18    	PD4
#define HEADER_CONNECTOR_CN6_D19    	PD5
#define HEADER_CONNECTOR_CN6_D20    	PG9
#define HEADER_CONNECTOR_CN6_D21    	PG10
#define HEADER_CONNECTOR_CN6_D22    	// Pin not routed
#define HEADER_CONNECTOR_CN6_D23    	PD7
#define HEADER_CONNECTOR_CN6_D24    	PD6
#define HEADER_CONNECTOR_CN6_D25    	PF0
#define HEADER_CONNECTOR_CN6_D26    	PF1
#define HEADER_CONNECTOR_CN6_D27    	PG11
#define HEADER_CONNECTOR_CN6_D28    	// Pin not routed
#define HEADER_CONNECTOR_CN6_D29    	PG13
#define HEADER_CONNECTOR_CN6_D30    	PC13
#define HEADER_CONNECTOR_CN6_D31    	PG12
#define HEADER_CONNECTOR_CN6_D32    	PF2
#define HEADER_CONNECTOR_CN6_D33    	PG14
#define HEADER_CONNECTOR_CN6_D34    	PF3
#define HEADER_CONNECTOR_CN6_D35    	PG15
#define HEADER_CONNECTOR_CN6_D36    	// Pin not routed
#define HEADER_CONNECTOR_CN6_D37    	PF4
#define HEADER_CONNECTOR_CN6_D38    	PF5
#define HEADER_CONNECTOR_CN6_D39    	// Pin not routed
#define HEADER_CONNECTOR_CN6_D40    	PB6

#define HEADER_CONNECTOR_CN7_D1     	// Pin not routed
#define HEADER_CONNECTOR_CN7_D2     	PE15
#define HEADER_CONNECTOR_CN7_D3     	// Pin not routed
#define HEADER_CONNECTOR_CN7_D4     	PE13
#define HEADER_CONNECTOR_CN7_D5     	PE12
#define HEADER_CONNECTOR_CN7_D6     	PE11
#define HEADER_CONNECTOR_CN7_D7     	PE10
#define HEADER_CONNECTOR_CN7_D8     	PE9
#define HEADER_CONNECTOR_CN7_D9     	PE8
#define HEADER_CONNECTOR_CN7_D10    	PE7
#define HEADER_CONNECTOR_CN7_D11    	PG1
#define HEADER_CONNECTOR_CN7_D12    	PG0
#define HEADER_CONNECTOR_CN7_D13    	PB2
#define HEADER_CONNECTOR_CN7_D14    	PF15
#define HEADER_CONNECTOR_CN7_D15    	// Pin not routed
#define HEADER_CONNECTOR_CN7_D16    	PF14
#define HEADER_CONNECTOR_CN7_D17    	PF12
#define HEADER_CONNECTOR_CN7_D18    	PF13
#define HEADER_CONNECTOR_CN7_D19    	PF11
#define HEADER_CONNECTOR_CN7_D20    	// Pin not routed
#define HEADER_CONNECTOR_CN7_D21    	PE4
#define HEADER_CONNECTOR_CN7_D22    	PE6
#define HEADER_CONNECTOR_CN7_D23    	PE5
#define HEADER_CONNECTOR_CN7_D24    	PC15
#define HEADER_CONNECTOR_CN7_D25    	PC14
#define HEADER_CONNECTOR_CN7_D26    	// Pin not routed
#define HEADER_CONNECTOR_CN7_D27    	PF6
#define HEADER_CONNECTOR_CN7_D28    	PF7
#define HEADER_CONNECTOR_CN7_D29    	PF9
#define HEADER_CONNECTOR_CN7_D30    	PF8
#define HEADER_CONNECTOR_CN7_D31    	PF10
#define HEADER_CONNECTOR_CN7_D32    	// Pin not routed
#define HEADER_CONNECTOR_CN7_D33    	PH1
#define HEADER_CONNECTOR_CN7_D34    	PH0
#define HEADER_CONNECTOR_CN7_D35    	PA5
#define HEADER_CONNECTOR_CN7_D36    	PC3
#define HEADER_CONNECTOR_CN7_D37    	PA0
#define HEADER_CONNECTOR_CN7_D38    	PA4
#define HEADER_CONNECTOR_CN7_D39    	// Pin not routed
#define HEADER_CONNECTOR_CN7_D40    	// Pin not routed

#define HEADER_CONNECTOR_GENERAL1_D1	// Pin not routed
#define HEADER_CONNECTOR_GENERAL1_D2	// Pin not routed
#define HEADER_CONNECTOR_GENERAL1_D3	PE14

#ifdef __cplusplus
}
#endif

#endif    // _BOARD_H_
// ------------------------------------------------------------------------- END
