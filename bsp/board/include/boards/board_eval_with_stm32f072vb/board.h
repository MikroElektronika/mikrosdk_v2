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
#define HEADER_CONNECTOR_CN1_D1     GPIO_PB12
#define HEADER_CONNECTOR_CN1_D2     // Pin not routed
#define HEADER_CONNECTOR_CN1_D3     GPIO_PE9
#define HEADER_CONNECTOR_CN1_D4     // Pin not routed
#define HEADER_CONNECTOR_CN1_D5     GPIO_PE8
#define HEADER_CONNECTOR_CN1_D6     // Pin not routed
#define HEADER_CONNECTOR_CN1_D7     GPIO_PE11
#define HEADER_CONNECTOR_CN1_D8     // Pin not routed
#define HEADER_CONNECTOR_CN1_D9     GPIO_PE10
#define HEADER_CONNECTOR_CN1_D10    // Pin not routed
#define HEADER_CONNECTOR_CN1_D11    GPIO_PE13
#define HEADER_CONNECTOR_CN1_D12    // Pin not routed
#define HEADER_CONNECTOR_CN1_D13    GPIO_PE12
#define HEADER_CONNECTOR_CN1_D14    GPIO_PA1
#define HEADER_CONNECTOR_CN1_D15    GPIO_PA2
#define HEADER_CONNECTOR_CN1_D16    // Pin not routed
#define HEADER_CONNECTOR_CN1_D17    GPIO_PC5
#define HEADER_CONNECTOR_CN1_D18    // Pin not routed
#define HEADER_CONNECTOR_CN1_D19    GPIO_PC4
#define HEADER_CONNECTOR_CN1_D20    // Pin not routed
#define HEADER_CONNECTOR_CN1_D21    GPIO_PE7
#define HEADER_CONNECTOR_CN1_D22    // Pin not routed
#define HEADER_CONNECTOR_CN1_D23    GPIO_PB11
#define HEADER_CONNECTOR_CN1_D24    // Pin not routed
#define HEADER_CONNECTOR_CN1_D25    // Pin not routed
#define HEADER_CONNECTOR_CN1_D26    GPIO_PC2
#define HEADER_CONNECTOR_CN1_D27    GPIO_PC8
#define HEADER_CONNECTOR_CN1_D28    // Pin not routed
#define HEADER_CONNECTOR_CN1_D29    GPIO_PC9
#define HEADER_CONNECTOR_CN1_D30    // Pin not routed
#define HEADER_CONNECTOR_CN1_D31    GPIO_PA6
#define HEADER_CONNECTOR_CN1_D32    // Pin not routed
#define HEADER_CONNECTOR_CN1_D33    GPIO_PA7
#define HEADER_CONNECTOR_CN1_D34    GPIO_PB0

#define HEADER_CONNECTOR_CN2_D1     GPIO_PB7
#define HEADER_CONNECTOR_CN2_D2     // Pin not routed
#define HEADER_CONNECTOR_CN2_D3     GPIO_PB6
#define HEADER_CONNECTOR_CN2_D4     GPIO_PD7

#define HEADER_CONNECTOR_CN7_D1     // Pin not routed
#define HEADER_CONNECTOR_CN7_D2     GPIO_PD15
#define HEADER_CONNECTOR_CN7_D3     GPIO_PC7
#define HEADER_CONNECTOR_CN7_D4     GPIO_PC6
#define HEADER_CONNECTOR_CN7_D5     GPIO_PC9
#define HEADER_CONNECTOR_CN7_D6     GPIO_PC8
#define HEADER_CONNECTOR_CN7_D7     GPIO_PA9
#define HEADER_CONNECTOR_CN7_D8     GPIO_PA8
#define HEADER_CONNECTOR_CN7_D9     GPIO_PA10
#define HEADER_CONNECTOR_CN7_D10    // Pin not routed
#define HEADER_CONNECTOR_CN7_D11    GPIO_PC14
#define HEADER_CONNECTOR_CN7_D12    GPIO_PA11
#define HEADER_CONNECTOR_CN7_D13    GPIO_PA12
#define HEADER_CONNECTOR_CN7_D14    GPIO_PA13
#define HEADER_CONNECTOR_CN7_D15    GPIO_PC15
#define HEADER_CONNECTOR_CN7_D16    GPIO_PF6
#define HEADER_CONNECTOR_CN7_D17    GPIO_PA14
#define HEADER_CONNECTOR_CN7_D18    GPIO_PA15
#define HEADER_CONNECTOR_CN7_D19    // Pin not routed
#define HEADER_CONNECTOR_CN7_D20    GPIO_PC10
#define HEADER_CONNECTOR_CN7_D21    GPIO_PC11
#define HEADER_CONNECTOR_CN7_D22    GPIO_PC12
#define HEADER_CONNECTOR_CN7_D23    GPIO_PD0
#define HEADER_CONNECTOR_CN7_D24    GPIO_PD1
#define HEADER_CONNECTOR_CN7_D25    GPIO_PD2
#define HEADER_CONNECTOR_CN7_D26    GPIO_PD3
#define HEADER_CONNECTOR_CN7_D27    GPIO_PD4
#define HEADER_CONNECTOR_CN7_D28    GPIO_PD5
#define HEADER_CONNECTOR_CN7_D29    GPIO_PD6
#define HEADER_CONNECTOR_CN7_D30    // Pin not routed
#define HEADER_CONNECTOR_CN7_D31    GPIO_PD7
#define HEADER_CONNECTOR_CN7_D32    GPIO_PB3
#define HEADER_CONNECTOR_CN7_D33    GPIO_PB4
#define HEADER_CONNECTOR_CN7_D34    GPIO_PB5
#define HEADER_CONNECTOR_CN7_D35    GPIO_PB6
#define HEADER_CONNECTOR_CN7_D36    GPIO_PB7
#define HEADER_CONNECTOR_CN7_D37    GPIO_PB8
#define HEADER_CONNECTOR_CN7_D38    GPIO_PB9
#define HEADER_CONNECTOR_CN7_D39    // Pin not routed
#define HEADER_CONNECTOR_CN7_D40    GPIO_PE0
#define HEADER_CONNECTOR_CN7_D41    GPIO_PE1
#define HEADER_CONNECTOR_CN7_D42    GPIO_PE2
#define HEADER_CONNECTOR_CN7_D43    GPIO_PE3
#define HEADER_CONNECTOR_CN7_D44    GPIO_PE6
#define HEADER_CONNECTOR_CN7_D45    GPIO_PF9
#define HEADER_CONNECTOR_CN7_D46    GPIO_PC0
#define HEADER_CONNECTOR_CN7_D47    GPIO_PF10
#define HEADER_CONNECTOR_CN7_D48    // Pin not routed
#define HEADER_CONNECTOR_CN7_D49    GPIO_PC1
#define HEADER_CONNECTOR_CN7_D50    // Pin not routed
#define HEADER_CONNECTOR_CN7_D51    GPIO_PE5
#define HEADER_CONNECTOR_CN7_D52    GPIO_PE4

#define HEADER_CONNECTOR_CN8_D1     // Pin not routed
#define HEADER_CONNECTOR_CN8_D2     GPIO_PD11
#define HEADER_CONNECTOR_CN8_D3     GPIO_PD14
#define HEADER_CONNECTOR_CN8_D4     GPIO_PD10
#define HEADER_CONNECTOR_CN8_D5     GPIO_PD13
#define HEADER_CONNECTOR_CN8_D6     GPIO_PD9
#define HEADER_CONNECTOR_CN8_D7     GPIO_PD12
#define HEADER_CONNECTOR_CN8_D8     GPIO_PD8
#define HEADER_CONNECTOR_CN8_D9     GPIO_PC13
#define HEADER_CONNECTOR_CN8_D10    // Pin not routed
#define HEADER_CONNECTOR_CN8_D11    // Pin not routed
#define HEADER_CONNECTOR_CN8_D12    GPIO_PB15
#define HEADER_CONNECTOR_CN8_D13    GPIO_PB13
#define HEADER_CONNECTOR_CN8_D14    GPIO_PB14
#define HEADER_CONNECTOR_CN8_D15    GPIO_PB11
#define HEADER_CONNECTOR_CN8_D16    GPIO_PB12
#define HEADER_CONNECTOR_CN8_D17    GPIO_PE15
#define HEADER_CONNECTOR_CN8_D18    GPIO_PB10
#define HEADER_CONNECTOR_CN8_D19    // Pin not routed
#define HEADER_CONNECTOR_CN8_D20    GPIO_PE14
#define HEADER_CONNECTOR_CN8_D21    GPIO_PE12
#define HEADER_CONNECTOR_CN8_D22    GPIO_PE13
#define HEADER_CONNECTOR_CN8_D23    GPIO_PF0
#define HEADER_CONNECTOR_CN8_D24    // Pin not routed
#define HEADER_CONNECTOR_CN8_D25    GPIO_PE11
#define HEADER_CONNECTOR_CN8_D26    GPIO_PF1
#define HEADER_CONNECTOR_CN8_D27    GPIO_PE10
#define HEADER_CONNECTOR_CN8_D28    GPIO_PE9
#define HEADER_CONNECTOR_CN8_D29    GPIO_PE8
#define HEADER_CONNECTOR_CN8_D30    // Pin not routed
#define HEADER_CONNECTOR_CN8_D31    GPIO_PB2
#define HEADER_CONNECTOR_CN8_D32    GPIO_PE7
#define HEADER_CONNECTOR_CN8_D33    GPIO_PB0
#define HEADER_CONNECTOR_CN8_D34    GPIO_PB1
#define HEADER_CONNECTOR_CN8_D35    GPIO_PC5
#define HEADER_CONNECTOR_CN8_D36    GPIO_PC4
#define HEADER_CONNECTOR_CN8_D37    GPIO_PA7
#define HEADER_CONNECTOR_CN8_D38    GPIO_PA6
#define HEADER_CONNECTOR_CN8_D39    // Pin not routed
#define HEADER_CONNECTOR_CN8_D40    GPIO_PA5
#define HEADER_CONNECTOR_CN8_D41    GPIO_PA4
#define HEADER_CONNECTOR_CN8_D42    // Pin not routed
#define HEADER_CONNECTOR_CN8_D43    // Pin not routed
#define HEADER_CONNECTOR_CN8_D44    GPIO_PA3
#define HEADER_CONNECTOR_CN8_D45    GPIO_PA2
#define HEADER_CONNECTOR_CN8_D46    GPIO_PA1
#define HEADER_CONNECTOR_CN8_D47    GPIO_PA0
#define HEADER_CONNECTOR_CN8_D48    GPIO_PF3
#define HEADER_CONNECTOR_CN8_D49    GPIO_PF2
#define HEADER_CONNECTOR_CN8_D50    // Pin not routed
#define HEADER_CONNECTOR_CN8_D51    GPIO_PC2
#define HEADER_CONNECTOR_CN8_D52    GPIO_PC3

#define HEADER_CONNECTOR_CN9_D1 	// Pin not routed
#define HEADER_CONNECTOR_CN9_D2     GPIO_PF2
#define HEADER_CONNECTOR_CN9_D3     GPIO_PE15
#define HEADER_CONNECTOR_CN9_D4     // Pin not routed
#define HEADER_CONNECTOR_CN9_D5     GPIO_PB3
#define HEADER_CONNECTOR_CN9_D6     // Pin not routed
#define HEADER_CONNECTOR_CN9_D7     GPIO_PE14
#define HEADER_CONNECTOR_CN9_D8     GPIO_PA11
#define HEADER_CONNECTOR_CN9_D9     // Pin not routed
#define HEADER_CONNECTOR_CN9_D10    GPIO_PB15

#define HEADER_CONNECTOR_CN10_D1 	// Pin not routed
#define HEADER_CONNECTOR_CN10_D2    GPIO_PD6
#define HEADER_CONNECTOR_CN10_D3    GPIO_PD5
#define HEADER_CONNECTOR_CN10_D4    // Pin not routed
#define HEADER_CONNECTOR_CN10_D5    // Pin not routed
#define HEADER_CONNECTOR_CN10_D6    // Pin not routed
#define HEADER_CONNECTOR_CN10_D7    GPIO_PD4
#define HEADER_CONNECTOR_CN10_D8    GPIO_PD3

#define HEADER_CONNECTOR_CN15_D1 	GPIO_PE6
#define HEADER_CONNECTOR_CN15_D2 	GPIO_PB3
#define HEADER_CONNECTOR_CN15_D3 	GPIO_PE15
#define HEADER_CONNECTOR_CN15_D4 	// Pin not routed
#define HEADER_CONNECTOR_CN15_D5 	// Pin not routed
#define HEADER_CONNECTOR_CN15_D6 	// Pin not routed
#define HEADER_CONNECTOR_CN15_D7 	GPIO_PE14

#ifdef __cplusplus
}
#endif

#endif    // _BOARD_H_
// ------------------------------------------------------------------------- END
