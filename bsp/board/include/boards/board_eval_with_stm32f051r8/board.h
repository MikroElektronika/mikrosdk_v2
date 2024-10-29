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

#define BOARD_NAME "STM32F051R8-Eval"

#include "hal_target.h"

// Mapping
#define HEADER_CONNECTOR_CN1_D1     PB12
#define HEADER_CONNECTOR_CN1_D2     // Pin not routed
#define HEADER_CONNECTOR_CN1_D3     PA8
#define HEADER_CONNECTOR_CN1_D4     // Pin not routed
#define HEADER_CONNECTOR_CN1_D5     PB13
#define HEADER_CONNECTOR_CN1_D6     // Pin not routed
#define HEADER_CONNECTOR_CN1_D7     PA9
#define HEADER_CONNECTOR_CN1_D8     // Pin not routed
#define HEADER_CONNECTOR_CN1_D9     PB14
#define HEADER_CONNECTOR_CN1_D10    // Pin not routed
#define HEADER_CONNECTOR_CN1_D11    PA10
#define HEADER_CONNECTOR_CN1_D12    // Pin not routed
#define HEADER_CONNECTOR_CN1_D13    PB15
#define HEADER_CONNECTOR_CN1_D14    PA1
#define HEADER_CONNECTOR_CN1_D15    PA2
#define HEADER_CONNECTOR_CN1_D16    // Pin not routed
#define HEADER_CONNECTOR_CN1_D17    PC5
#define HEADER_CONNECTOR_CN1_D18    // Pin not routed
#define HEADER_CONNECTOR_CN1_D19    PC4
#define HEADER_CONNECTOR_CN1_D20    // Pin not routed
#define HEADER_CONNECTOR_CN1_D21    PA6
#define HEADER_CONNECTOR_CN1_D22    // Pin not routed
#define HEADER_CONNECTOR_CN1_D23    PB11
#define HEADER_CONNECTOR_CN1_D24    // Pin not routed
#define HEADER_CONNECTOR_CN1_D25    // Pin not routed
#define HEADER_CONNECTOR_CN1_D26    PC2
#define HEADER_CONNECTOR_CN1_D27    PB0
#define HEADER_CONNECTOR_CN1_D28    // Pin not routed
#define HEADER_CONNECTOR_CN1_D29    PB1
#define HEADER_CONNECTOR_CN1_D30    // Pin not routed
#define HEADER_CONNECTOR_CN1_D31    PA15
#define HEADER_CONNECTOR_CN1_D32    // Pin not routed
#define HEADER_CONNECTOR_CN1_D33    PB3
#define HEADER_CONNECTOR_CN1_D34    PB10

#define HEADER_CONNECTOR_CN2_D1     PB7
#define HEADER_CONNECTOR_CN2_D2     PB6

#define HEADER_CONNECTOR_CN5_D1     // Pin not routed
#define HEADER_CONNECTOR_CN5_D2     PB15
#define HEADER_CONNECTOR_CN5_D3     PC6
#define HEADER_CONNECTOR_CN5_D4     PC7
#define HEADER_CONNECTOR_CN5_D5     PC8
#define HEADER_CONNECTOR_CN5_D6     PC9
#define HEADER_CONNECTOR_CN5_D7     PA8
#define HEADER_CONNECTOR_CN5_D8     PA9
#define HEADER_CONNECTOR_CN5_D9     PA10
#define HEADER_CONNECTOR_CN5_D10    // Pin not routed
#define HEADER_CONNECTOR_CN5_D11    PA11
#define HEADER_CONNECTOR_CN5_D12    PA12
#define HEADER_CONNECTOR_CN5_D13    PA13
#define HEADER_CONNECTOR_CN5_D14    PF6
#define HEADER_CONNECTOR_CN5_D15    PF7
#define HEADER_CONNECTOR_CN5_D16    PA14
#define HEADER_CONNECTOR_CN5_D17    PA15
#define HEADER_CONNECTOR_CN5_D18    PC10
#define HEADER_CONNECTOR_CN5_D19    // Pin not routed
#define HEADER_CONNECTOR_CN5_D20    PC11
#define HEADER_CONNECTOR_CN5_D21    PC12
#define HEADER_CONNECTOR_CN5_D22    PD2
#define HEADER_CONNECTOR_CN5_D23    PB3
#define HEADER_CONNECTOR_CN5_D24    PB4
#define HEADER_CONNECTOR_CN5_D25    PB5
#define HEADER_CONNECTOR_CN5_D26    PB6
#define HEADER_CONNECTOR_CN5_D27    PB7
#define HEADER_CONNECTOR_CN5_D28    // Pin not routed
#define HEADER_CONNECTOR_CN5_D29    PB8
#define HEADER_CONNECTOR_CN5_D30    // Pin not routed
#define HEADER_CONNECTOR_CN5_D31    PB9
#define HEADER_CONNECTOR_CN5_D32    PC14
#define HEADER_CONNECTOR_CN5_D33    PC15
#define HEADER_CONNECTOR_CN5_D34    // Pin not routed

#define HEADER_CONNECTOR_CN6_D1     // Pin not routed
#define HEADER_CONNECTOR_CN6_D2     PB14
#define HEADER_CONNECTOR_CN6_D3     PB13
#define HEADER_CONNECTOR_CN6_D4     PB12
#define HEADER_CONNECTOR_CN6_D5     PB11
#define HEADER_CONNECTOR_CN6_D6     PB10
#define HEADER_CONNECTOR_CN6_D7     PB2
#define HEADER_CONNECTOR_CN6_D8     PB1
#define HEADER_CONNECTOR_CN6_D9     PC13
#define HEADER_CONNECTOR_CN6_D10    // Pin not routed
#define HEADER_CONNECTOR_CN6_D11    // Pin not routed
#define HEADER_CONNECTOR_CN6_D12    PB0
#define HEADER_CONNECTOR_CN6_D13    PC5
#define HEADER_CONNECTOR_CN6_D14    PC4
#define HEADER_CONNECTOR_CN6_D15    PA7
#define HEADER_CONNECTOR_CN6_D16    PA6
#define HEADER_CONNECTOR_CN6_D17    PA5
#define HEADER_CONNECTOR_CN6_D18    PA4
#define HEADER_CONNECTOR_CN6_D19    // Pin not routed
#define HEADER_CONNECTOR_CN6_D20    // Pin not routed
#define HEADER_CONNECTOR_CN6_D21    PA3
#define HEADER_CONNECTOR_CN6_D22    PF4
#define HEADER_CONNECTOR_CN6_D23    PA1
#define HEADER_CONNECTOR_CN6_D24    PA2
#define HEADER_CONNECTOR_CN6_D25    PC3
#define HEADER_CONNECTOR_CN6_D26    PA0
#define HEADER_CONNECTOR_CN6_D27    PC1
#define HEADER_CONNECTOR_CN6_D28    PC2
#define HEADER_CONNECTOR_CN6_D29    PC0
#define HEADER_CONNECTOR_CN6_D30    // Pin not routed
#define HEADER_CONNECTOR_CN6_D31    PF0
#define HEADER_CONNECTOR_CN6_D32    // Pin not routed
#define HEADER_CONNECTOR_CN6_D33    PF0
#define HEADER_CONNECTOR_CN6_D34    PF1

#define HEADER_CONNECTOR_CN7_D1 	// Pin not routed
#define HEADER_CONNECTOR_CN7_D2     PA10
#define HEADER_CONNECTOR_CN7_D3     PA9
#define HEADER_CONNECTOR_CN7_D4     // Pin not routed
#define HEADER_CONNECTOR_CN7_D5     // Pin not routed
#define HEADER_CONNECTOR_CN7_D6     // Pin not routed
#define HEADER_CONNECTOR_CN7_D7     PA12
#define HEADER_CONNECTOR_CN7_D8     PA11

#define HEADER_CONNECTOR_CN8_D1     PC1

#define HEADER_CONNECTOR_CN16_D1 	PF4
#define HEADER_CONNECTOR_CN16_D2 	PA5
#define HEADER_CONNECTOR_CN16_D3 	PA7
#define HEADER_CONNECTOR_CN16_D4 	// Pin not routed
#define HEADER_CONNECTOR_CN16_D5 	// Pin not routed
#define HEADER_CONNECTOR_CN16_D6 	// Pin not routed
#define HEADER_CONNECTOR_CN16_D7 	PB4

#ifdef __cplusplus
}
#endif

#endif    // _BOARD_H_
// ------------------------------------------------------------------------- END
