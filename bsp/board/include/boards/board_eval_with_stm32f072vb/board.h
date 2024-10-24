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

#define BOARD_NAME "STM32F072VB-Eval"

#include "hal_target.h"

// Mapping
#define HEADER_CONNECTOR_CN1_D1     PB12
#define HEADER_CONNECTOR_CN1_D2     // Pin not routed
#define HEADER_CONNECTOR_CN1_D3     PE9
#define HEADER_CONNECTOR_CN1_D4     // Pin not routed
#define HEADER_CONNECTOR_CN1_D5     PE8
#define HEADER_CONNECTOR_CN1_D6     // Pin not routed
#define HEADER_CONNECTOR_CN1_D7     PE11
#define HEADER_CONNECTOR_CN1_D8     // Pin not routed
#define HEADER_CONNECTOR_CN1_D9     PE10
#define HEADER_CONNECTOR_CN1_D10    // Pin not routed
#define HEADER_CONNECTOR_CN1_D11    PE13
#define HEADER_CONNECTOR_CN1_D12    // Pin not routed
#define HEADER_CONNECTOR_CN1_D13    PE12
#define HEADER_CONNECTOR_CN1_D14    PA1
#define HEADER_CONNECTOR_CN1_D15    PA2
#define HEADER_CONNECTOR_CN1_D16    // Pin not routed
#define HEADER_CONNECTOR_CN1_D17    PC5
#define HEADER_CONNECTOR_CN1_D18    // Pin not routed
#define HEADER_CONNECTOR_CN1_D19    PC4
#define HEADER_CONNECTOR_CN1_D20    // Pin not routed
#define HEADER_CONNECTOR_CN1_D21    PE7
#define HEADER_CONNECTOR_CN1_D22    // Pin not routed
#define HEADER_CONNECTOR_CN1_D23    PB11
#define HEADER_CONNECTOR_CN1_D24    // Pin not routed
#define HEADER_CONNECTOR_CN1_D25    // Pin not routed
#define HEADER_CONNECTOR_CN1_D26    PC2
#define HEADER_CONNECTOR_CN1_D27    PC8
#define HEADER_CONNECTOR_CN1_D28    // Pin not routed
#define HEADER_CONNECTOR_CN1_D29    PC9
#define HEADER_CONNECTOR_CN1_D30    // Pin not routed
#define HEADER_CONNECTOR_CN1_D31    PA6
#define HEADER_CONNECTOR_CN1_D32    // Pin not routed
#define HEADER_CONNECTOR_CN1_D33    PA7
#define HEADER_CONNECTOR_CN1_D34    PB0

#define HEADER_CONNECTOR_CN2_D1     PB7
#define HEADER_CONNECTOR_CN2_D2     // Pin not routed
#define HEADER_CONNECTOR_CN2_D3     PB6
#define HEADER_CONNECTOR_CN2_D4     PD7

#define HEADER_CONNECTOR_CN7_D1     // Pin not routed
#define HEADER_CONNECTOR_CN7_D2     PD15
#define HEADER_CONNECTOR_CN7_D3     PC7
#define HEADER_CONNECTOR_CN7_D4     PC6
#define HEADER_CONNECTOR_CN7_D5     PC9
#define HEADER_CONNECTOR_CN7_D6     PC8
#define HEADER_CONNECTOR_CN7_D7     PA9
#define HEADER_CONNECTOR_CN7_D8     PA8
#define HEADER_CONNECTOR_CN7_D9     PA10
#define HEADER_CONNECTOR_CN7_D10    // Pin not routed
#define HEADER_CONNECTOR_CN7_D11    PC14
#define HEADER_CONNECTOR_CN7_D12    PA11
#define HEADER_CONNECTOR_CN7_D13    PA12
#define HEADER_CONNECTOR_CN7_D14    PA13
#define HEADER_CONNECTOR_CN7_D15    PC15
#define HEADER_CONNECTOR_CN7_D16    PF6
#define HEADER_CONNECTOR_CN7_D17    PA14
#define HEADER_CONNECTOR_CN7_D18    PA15
#define HEADER_CONNECTOR_CN7_D19    // Pin not routed
#define HEADER_CONNECTOR_CN7_D20    PC10
#define HEADER_CONNECTOR_CN7_D21    PC11
#define HEADER_CONNECTOR_CN7_D22    PC12
#define HEADER_CONNECTOR_CN7_D23    PD0
#define HEADER_CONNECTOR_CN7_D24    PD1
#define HEADER_CONNECTOR_CN7_D25    PD2
#define HEADER_CONNECTOR_CN7_D26    PD3
#define HEADER_CONNECTOR_CN7_D27    PD4
#define HEADER_CONNECTOR_CN7_D28    PD5
#define HEADER_CONNECTOR_CN7_D29    PD6
#define HEADER_CONNECTOR_CN7_D30    // Pin not routed
#define HEADER_CONNECTOR_CN7_D31    PD7
#define HEADER_CONNECTOR_CN7_D32    PB3
#define HEADER_CONNECTOR_CN7_D33    PB4
#define HEADER_CONNECTOR_CN7_D34    PB5
#define HEADER_CONNECTOR_CN7_D35    PB6
#define HEADER_CONNECTOR_CN7_D36    PB7
#define HEADER_CONNECTOR_CN7_D37    PB8
#define HEADER_CONNECTOR_CN7_D38    PB9
#define HEADER_CONNECTOR_CN7_D39    // Pin not routed
#define HEADER_CONNECTOR_CN7_D40    PE0
#define HEADER_CONNECTOR_CN7_D41    PE1
#define HEADER_CONNECTOR_CN7_D42    PE2
#define HEADER_CONNECTOR_CN7_D43    PE3
#define HEADER_CONNECTOR_CN7_D44    PE6
#define HEADER_CONNECTOR_CN7_D45    PF9
#define HEADER_CONNECTOR_CN7_D46    PC0
#define HEADER_CONNECTOR_CN7_D47    PF10
#define HEADER_CONNECTOR_CN7_D48    // Pin not routed
#define HEADER_CONNECTOR_CN7_D49    PC1
#define HEADER_CONNECTOR_CN7_D50    // Pin not routed
#define HEADER_CONNECTOR_CN7_D51    PE5
#define HEADER_CONNECTOR_CN7_D52    PE4

#define HEADER_CONNECTOR_CN8_D1     // Pin not routed
#define HEADER_CONNECTOR_CN8_D2     PD11
#define HEADER_CONNECTOR_CN8_D3     PD14
#define HEADER_CONNECTOR_CN8_D4     PD10
#define HEADER_CONNECTOR_CN8_D5     PD13
#define HEADER_CONNECTOR_CN8_D6     PD9
#define HEADER_CONNECTOR_CN8_D7     PD12
#define HEADER_CONNECTOR_CN8_D8     PD8
#define HEADER_CONNECTOR_CN8_D9     PC13
#define HEADER_CONNECTOR_CN8_D10    // Pin not routed
#define HEADER_CONNECTOR_CN8_D11    // Pin not routed
#define HEADER_CONNECTOR_CN8_D12    PB15
#define HEADER_CONNECTOR_CN8_D13    PB13
#define HEADER_CONNECTOR_CN8_D14    PB14
#define HEADER_CONNECTOR_CN8_D15    PB11
#define HEADER_CONNECTOR_CN8_D16    PB12
#define HEADER_CONNECTOR_CN8_D17    PE15
#define HEADER_CONNECTOR_CN8_D18    PB10
#define HEADER_CONNECTOR_CN8_D19    // Pin not routed
#define HEADER_CONNECTOR_CN8_D20    PE14
#define HEADER_CONNECTOR_CN8_D21    PE12
#define HEADER_CONNECTOR_CN8_D22    PE13
#define HEADER_CONNECTOR_CN8_D23    PF0
#define HEADER_CONNECTOR_CN8_D24    // Pin not routed
#define HEADER_CONNECTOR_CN8_D25    PE11
#define HEADER_CONNECTOR_CN8_D26    PF1
#define HEADER_CONNECTOR_CN8_D27    PE10
#define HEADER_CONNECTOR_CN8_D28    PE9
#define HEADER_CONNECTOR_CN8_D29    PE8
#define HEADER_CONNECTOR_CN8_D30    // Pin not routed
#define HEADER_CONNECTOR_CN8_D31    PB2
#define HEADER_CONNECTOR_CN8_D32    PE7
#define HEADER_CONNECTOR_CN8_D33    PB0
#define HEADER_CONNECTOR_CN8_D34    PB1
#define HEADER_CONNECTOR_CN8_D35    PC5
#define HEADER_CONNECTOR_CN8_D36    PC4
#define HEADER_CONNECTOR_CN8_D37    PA7
#define HEADER_CONNECTOR_CN8_D38    PA6
#define HEADER_CONNECTOR_CN8_D39    // Pin not routed
#define HEADER_CONNECTOR_CN8_D40    PA5
#define HEADER_CONNECTOR_CN8_D41    PA4
#define HEADER_CONNECTOR_CN8_D42    // Pin not routed
#define HEADER_CONNECTOR_CN8_D43    // Pin not routed
#define HEADER_CONNECTOR_CN8_D44    PA3
#define HEADER_CONNECTOR_CN8_D45    PA2
#define HEADER_CONNECTOR_CN8_D46    PA1
#define HEADER_CONNECTOR_CN8_D47    PA0
#define HEADER_CONNECTOR_CN8_D48    PF3
#define HEADER_CONNECTOR_CN8_D49    PF2
#define HEADER_CONNECTOR_CN8_D50    // Pin not routed
#define HEADER_CONNECTOR_CN8_D51    PC2
#define HEADER_CONNECTOR_CN8_D52    PC3

#define HEADER_CONNECTOR_CN9_D1 	// Pin not routed
#define HEADER_CONNECTOR_CN9_D2     PF2
#define HEADER_CONNECTOR_CN9_D3     PE15
#define HEADER_CONNECTOR_CN9_D4     // Pin not routed
#define HEADER_CONNECTOR_CN9_D5     PB3
#define HEADER_CONNECTOR_CN9_D6     // Pin not routed
#define HEADER_CONNECTOR_CN9_D7     PE14
#define HEADER_CONNECTOR_CN9_D8     PA11
#define HEADER_CONNECTOR_CN9_D9     // Pin not routed
#define HEADER_CONNECTOR_CN9_D10    PB15

#define HEADER_CONNECTOR_CN10_D1 	// Pin not routed
#define HEADER_CONNECTOR_CN10_D2    PD6
#define HEADER_CONNECTOR_CN10_D3    PD5
#define HEADER_CONNECTOR_CN10_D4    // Pin not routed
#define HEADER_CONNECTOR_CN10_D5    // Pin not routed
#define HEADER_CONNECTOR_CN10_D6    // Pin not routed
#define HEADER_CONNECTOR_CN10_D7    PD4
#define HEADER_CONNECTOR_CN10_D8    PD3

#define HEADER_CONNECTOR_CN15_D1 	PE6
#define HEADER_CONNECTOR_CN15_D2 	PB3
#define HEADER_CONNECTOR_CN15_D3 	PE15
#define HEADER_CONNECTOR_CN15_D4 	// Pin not routed
#define HEADER_CONNECTOR_CN15_D5 	// Pin not routed
#define HEADER_CONNECTOR_CN15_D6 	// Pin not routed
#define HEADER_CONNECTOR_CN15_D7 	PE14

#ifdef __cplusplus
}
#endif

#endif    // _BOARD_H_
// ------------------------------------------------------------------------- END
