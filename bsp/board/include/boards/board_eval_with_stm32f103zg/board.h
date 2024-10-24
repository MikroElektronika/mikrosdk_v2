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

#define BOARD_NAME "STM32F103ZG-Eval"

#include "hal_target.h"

// Mapping
#define HEADER_CONNECTOR_CN1_D1     PA6
#define HEADER_CONNECTOR_CN1_D2     // Pin not routed
#define HEADER_CONNECTOR_CN1_D3     PC6
#define HEADER_CONNECTOR_CN1_D4     // Pin not routed
#define HEADER_CONNECTOR_CN1_D5     PA7
#define HEADER_CONNECTOR_CN1_D6     // Pin not routed
#define HEADER_CONNECTOR_CN1_D7     PC7
#define HEADER_CONNECTOR_CN1_D8     // Pin not routed
#define HEADER_CONNECTOR_CN1_D9     PB0
#define HEADER_CONNECTOR_CN1_D10    // Pin not routed
#define HEADER_CONNECTOR_CN1_D11    PC8
#define HEADER_CONNECTOR_CN1_D12    // Pin not routed
#define HEADER_CONNECTOR_CN1_D13    PB1
#define HEADER_CONNECTOR_CN1_D14    PC0
#define HEADER_CONNECTOR_CN1_D15    PC1
#define HEADER_CONNECTOR_CN1_D16    // Pin not routed
#define HEADER_CONNECTOR_CN1_D17    PC2
#define HEADER_CONNECTOR_CN1_D18    // Pin not routed
#define HEADER_CONNECTOR_CN1_D19    PC3
#define HEADER_CONNECTOR_CN1_D20    // Pin not routed
#define HEADER_CONNECTOR_CN1_D21    PB12
#define HEADER_CONNECTOR_CN1_D22    // Pin not routed
#define HEADER_CONNECTOR_CN1_D23    PA3
#define HEADER_CONNECTOR_CN1_D24    // Pin not routed
#define HEADER_CONNECTOR_CN1_D25    // Pin not routed
#define HEADER_CONNECTOR_CN1_D26    PC5
#define HEADER_CONNECTOR_CN1_D27    PB4
#define HEADER_CONNECTOR_CN1_D28    // Pin not routed
#define HEADER_CONNECTOR_CN1_D29    PB5
#define HEADER_CONNECTOR_CN1_D30    // Pin not routed
#define HEADER_CONNECTOR_CN1_D31    PA0
#define HEADER_CONNECTOR_CN1_D32    // Pin not routed
#define HEADER_CONNECTOR_CN1_D33    PA1
#define HEADER_CONNECTOR_CN1_D34    PA2

#define HEADER_CONNECTOR_CN6_D1     // Pin not routed
#define HEADER_CONNECTOR_CN6_D2     // Pin not routed
#define HEADER_CONNECTOR_CN6_D3     PB6
#define HEADER_CONNECTOR_CN6_D4     PA5
#define HEADER_CONNECTOR_CN6_D5     PB7
#define HEADER_CONNECTOR_CN6_D6     PA7
#define HEADER_CONNECTOR_CN6_D7     PB1
#define HEADER_CONNECTOR_CN6_D8     PA6
#define HEADER_CONNECTOR_CN6_D9     PF11
#define HEADER_CONNECTOR_CN6_D10    PB5
#define HEADER_CONNECTOR_CN6_D11    PA8

#define HEADER_CONNECTOR_CN7_D1     // Pin not routed
#define HEADER_CONNECTOR_CN7_D2     PA13
#define HEADER_CONNECTOR_CN7_D3     // Pin not routed
#define HEADER_CONNECTOR_CN7_D4     PA14
#define HEADER_CONNECTOR_CN7_D5     // Pin not routed
#define HEADER_CONNECTOR_CN7_D6     PB3
#define HEADER_CONNECTOR_CN7_D7     // Pin not routed
#define HEADER_CONNECTOR_CN7_D8     PA15
#define HEADER_CONNECTOR_CN7_D9     // Pin not routed
#define HEADER_CONNECTOR_CN7_D10    // Pin not routed
#define HEADER_CONNECTOR_CN7_D11    // Pin not routed
#define HEADER_CONNECTOR_CN7_D12    PE2
#define HEADER_CONNECTOR_CN7_D13    // Pin not routed
#define HEADER_CONNECTOR_CN7_D14    PB3
#define HEADER_CONNECTOR_CN7_D15    // Pin not routed
#define HEADER_CONNECTOR_CN7_D16    PB4
#define HEADER_CONNECTOR_CN7_D17    // Pin not routed
#define HEADER_CONNECTOR_CN7_D18    PE5
#define HEADER_CONNECTOR_CN7_D19    // Pin not routed
#define HEADER_CONNECTOR_CN7_D20    PE6

#define HEADER_CONNECTOR_CN10_D1    // Pin not routed
#define HEADER_CONNECTOR_CN10_D2    PC6
#define HEADER_CONNECTOR_CN10_D3    PC7
#define HEADER_CONNECTOR_CN10_D4    PC8
#define HEADER_CONNECTOR_CN10_D5    PC9
#define HEADER_CONNECTOR_CN10_D6    PA8
#define HEADER_CONNECTOR_CN10_D7    PA9
#define HEADER_CONNECTOR_CN10_D8    PA10
#define HEADER_CONNECTOR_CN10_D9    PA0
#define HEADER_CONNECTOR_CN10_D10   // Pin not routed
#define HEADER_CONNECTOR_CN10_D11   // Pin not routed
#define HEADER_CONNECTOR_CN10_D12   PA11
#define HEADER_CONNECTOR_CN10_D13   PA12
#define HEADER_CONNECTOR_CN10_D14   PA13
#define HEADER_CONNECTOR_CN10_D15   PA14
#define HEADER_CONNECTOR_CN10_D16   PA15
#define HEADER_CONNECTOR_CN10_D17   PC10
#define HEADER_CONNECTOR_CN10_D18   PC11
#define HEADER_CONNECTOR_CN10_D19   // Pin not routed
#define HEADER_CONNECTOR_CN10_D20   PC12
#define HEADER_CONNECTOR_CN10_D21   PD0
#define HEADER_CONNECTOR_CN10_D22   PD1
#define HEADER_CONNECTOR_CN10_D23   PE2
#define HEADER_CONNECTOR_CN10_D24   PE1
#define HEADER_CONNECTOR_CN10_D25   PD2
#define HEADER_CONNECTOR_CN10_D26   PD3
#define HEADER_CONNECTOR_CN10_D27   PD4
#define HEADER_CONNECTOR_CN10_D28   PD5
#define HEADER_CONNECTOR_CN10_D29   PD6
#define HEADER_CONNECTOR_CN10_D30   // Pin not routed
#define HEADER_CONNECTOR_CN10_D31   PD7
#define HEADER_CONNECTOR_CN10_D32   PG9
#define HEADER_CONNECTOR_CN10_D33   PG10
#define HEADER_CONNECTOR_CN10_D34   PG11
#define HEADER_CONNECTOR_CN10_D35   PG12
#define HEADER_CONNECTOR_CN10_D36   PG13
#define HEADER_CONNECTOR_CN10_D37   PG14
#define HEADER_CONNECTOR_CN10_D38   PG15
#define HEADER_CONNECTOR_CN10_D39   // Pin not routed
#define HEADER_CONNECTOR_CN10_D40   PB3
#define HEADER_CONNECTOR_CN10_D41   PB4
#define HEADER_CONNECTOR_CN10_D42   PB5
#define HEADER_CONNECTOR_CN10_D43   PB6
#define HEADER_CONNECTOR_CN10_D44   PB7
#define HEADER_CONNECTOR_CN10_D45   PB8
#define HEADER_CONNECTOR_CN10_D46   PB9
#define HEADER_CONNECTOR_CN10_D47   PE0
#define HEADER_CONNECTOR_CN10_D48   // Pin not routed
#define HEADER_CONNECTOR_CN10_D49   // Pin not routed
#define HEADER_CONNECTOR_CN10_D50   // Pin not routed
#define HEADER_CONNECTOR_CN10_D51   PE4
#define HEADER_CONNECTOR_CN10_D52   PE3
#define HEADER_CONNECTOR_CN10_D53   PE6
#define HEADER_CONNECTOR_CN10_D54   PE5
#define HEADER_CONNECTOR_CN10_D55   PC14
#define HEADER_CONNECTOR_CN10_D56   PC13
#define HEADER_CONNECTOR_CN10_D57   PF0
#define HEADER_CONNECTOR_CN10_D58   PC15
#define HEADER_CONNECTOR_CN10_D59   // Pin not routed
#define HEADER_CONNECTOR_CN10_D60   PF1
#define HEADER_CONNECTOR_CN10_D61   PF2
#define HEADER_CONNECTOR_CN10_D62   PF3
#define HEADER_CONNECTOR_CN10_D63   PF4
#define HEADER_CONNECTOR_CN10_D64   PF5
#define HEADER_CONNECTOR_CN10_D65   PF6
#define HEADER_CONNECTOR_CN10_D66   PF7
#define HEADER_CONNECTOR_CN10_D67   PF8
#define HEADER_CONNECTOR_CN10_D68   PF9

#define HEADER_CONNECTOR_CN11_D1    // Pin not routed
#define HEADER_CONNECTOR_CN11_D2    PG8
#define HEADER_CONNECTOR_CN11_D3    PG7
#define HEADER_CONNECTOR_CN11_D4    PG6
#define HEADER_CONNECTOR_CN11_D5    PG5
#define HEADER_CONNECTOR_CN11_D6    PG4
#define HEADER_CONNECTOR_CN11_D7    PG3
#define HEADER_CONNECTOR_CN11_D8    PG2
#define HEADER_CONNECTOR_CN11_D9    PC13
#define HEADER_CONNECTOR_CN11_D10   // Pin not routed
#define HEADER_CONNECTOR_CN11_D11   // Pin not routed
#define HEADER_CONNECTOR_CN11_D12   PD13
#define HEADER_CONNECTOR_CN11_D13   PD12
#define HEADER_CONNECTOR_CN11_D14   PD11
#define HEADER_CONNECTOR_CN11_D15   PD10
#define HEADER_CONNECTOR_CN11_D16   PD9
#define HEADER_CONNECTOR_CN11_D17   PD8
#define HEADER_CONNECTOR_CN11_D18   PB15
#define HEADER_CONNECTOR_CN11_D19   // Pin not routed
#define HEADER_CONNECTOR_CN11_D20   PB14
#define HEADER_CONNECTOR_CN11_D21   PB13
#define HEADER_CONNECTOR_CN11_D22   PB12
#define HEADER_CONNECTOR_CN11_D23   PB11
#define HEADER_CONNECTOR_CN11_D24   PB10
#define HEADER_CONNECTOR_CN11_D25   PE15
#define HEADER_CONNECTOR_CN11_D26   PE14
#define HEADER_CONNECTOR_CN11_D27   PE13
#define HEADER_CONNECTOR_CN11_D28   PE12
#define HEADER_CONNECTOR_CN11_D29   PE11
#define HEADER_CONNECTOR_CN11_D30   // Pin not routed
#define HEADER_CONNECTOR_CN11_D31   PD15
#define HEADER_CONNECTOR_CN11_D32   PD14
#define HEADER_CONNECTOR_CN11_D33   PE9
#define HEADER_CONNECTOR_CN11_D34   PE10
#define HEADER_CONNECTOR_CN11_D35   PE7
#define HEADER_CONNECTOR_CN11_D36   PE8
#define HEADER_CONNECTOR_CN11_D37   PG1
#define HEADER_CONNECTOR_CN11_D38   // Pin not routed
#define HEADER_CONNECTOR_CN11_D39   // Pin not routed
#define HEADER_CONNECTOR_CN11_D40   PG0
#define HEADER_CONNECTOR_CN11_D41   PF14
#define HEADER_CONNECTOR_CN11_D42   PF15
#define HEADER_CONNECTOR_CN11_D43   PF12
#define HEADER_CONNECTOR_CN11_D44   PF13
#define HEADER_CONNECTOR_CN11_D45   PB2
#define HEADER_CONNECTOR_CN11_D46   PF11
#define HEADER_CONNECTOR_CN11_D47   PB1
#define HEADER_CONNECTOR_CN11_D48   // Pin not routed
#define HEADER_CONNECTOR_CN11_D49   // Pin not routed
#define HEADER_CONNECTOR_CN11_D50   // Pin not routed
#define HEADER_CONNECTOR_CN11_D51   PB0
#define HEADER_CONNECTOR_CN11_D52   PC5
#define HEADER_CONNECTOR_CN11_D53   PC4
#define HEADER_CONNECTOR_CN11_D54   PA7
#define HEADER_CONNECTOR_CN11_D55   PA6
#define HEADER_CONNECTOR_CN11_D56   PA5
#define HEADER_CONNECTOR_CN11_D57   PA4
#define HEADER_CONNECTOR_CN11_D58   PA3
#define HEADER_CONNECTOR_CN11_D59   // Pin not routed
#define HEADER_CONNECTOR_CN11_D60   PA2
#define HEADER_CONNECTOR_CN11_D61   PA1
#define HEADER_CONNECTOR_CN11_D62   // Pin not routed
#define HEADER_CONNECTOR_CN11_D63   PC3
#define HEADER_CONNECTOR_CN11_D64   PC2
#define HEADER_CONNECTOR_CN11_D65   PC1
#define HEADER_CONNECTOR_CN11_D66   PC0
#define HEADER_CONNECTOR_CN11_D67   PF10

#ifdef __cplusplus
}
#endif

#endif    // _BOARD_H_
// ------------------------------------------------------------------------- END
