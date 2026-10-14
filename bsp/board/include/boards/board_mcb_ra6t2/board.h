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

#define BOARD_NAME "Renesas Flexible Motor Control CPU Board for RA6T2 MCU Group"

#include "hal_target.h"

// Mapping
#define HEADER_CONNECTOR_CN4_D1     // Pin not routed.
#define HEADER_CONNECTOR_CN4_D2     // Pin not routed.
#define HEADER_CONNECTOR_CN4_D3     GPIO_PA06
#define HEADER_CONNECTOR_CN4_D4     // Pin not routed.
#define HEADER_CONNECTOR_CN4_D5     GPIO_PA04
#define HEADER_CONNECTOR_CN4_D6     GPIO_PA05
#define HEADER_CONNECTOR_CN4_D7     GPIO_PA02
#define HEADER_CONNECTOR_CN4_D8     GPIO_PA03
#define HEADER_CONNECTOR_CN4_D9     GPIO_PA00
#define HEADER_CONNECTOR_CN4_D10    GPIO_PA01
#define HEADER_CONNECTOR_CN4_D11    GPIO_PA07
#define HEADER_CONNECTOR_CN4_D12    GPIO_PA03
#define HEADER_CONNECTOR_CN4_D13    GPIO_PA01
#define HEADER_CONNECTOR_CN4_D14    // Pin not routed.
#define HEADER_CONNECTOR_CN4_D15    GPIO_PB10
#define HEADER_CONNECTOR_CN4_D16    GPIO_PE15
#define HEADER_CONNECTOR_CN4_D17    GPIO_PB00
#define HEADER_CONNECTOR_CN4_D18    // Pin not routed.
#define HEADER_CONNECTOR_CN4_D19    // Pin not routed.
#define HEADER_CONNECTOR_CN4_D20    // Pin not routed.
#define HEADER_CONNECTOR_CN4_D21    // Pin not routed.
#define HEADER_CONNECTOR_CN4_D22    // Pin not routed.
#define HEADER_CONNECTOR_CN4_D23    // Pin not routed.
#define HEADER_CONNECTOR_CN4_D24    // Pin not routed.
#define HEADER_CONNECTOR_CN4_D25    // Pin not routed.
#define HEADER_CONNECTOR_CN4_D26    // Pin not routed.
#define HEADER_CONNECTOR_CN4_D27    GPIO_PB05
#define HEADER_CONNECTOR_CN4_D28    // Pin not routed.
#define HEADER_CONNECTOR_CN4_D29    GPIO_PB04
#define HEADER_CONNECTOR_CN4_D30    // Pin not routed.
#define HEADER_CONNECTOR_CN4_D31    GPIO_PB07
#define HEADER_CONNECTOR_CN4_D32    // Pin not routed.
#define HEADER_CONNECTOR_CN4_D33    GPIO_PB06
#define HEADER_CONNECTOR_CN4_D34    // Pin not routed.

#define HEADER_CONNECTOR_CN5_D1     GPIO_PB09
#define HEADER_CONNECTOR_CN5_D2     // Pin not routed.
#define HEADER_CONNECTOR_CN5_D3     GPIO_PB08
#define HEADER_CONNECTOR_CN5_D4     // Pin not routed.
#define HEADER_CONNECTOR_CN5_D5     // Pin not routed.
#define HEADER_CONNECTOR_CN5_D6     // Pin not routed.
#define HEADER_CONNECTOR_CN5_D7     // Pin not routed.
#define HEADER_CONNECTOR_CN5_D8     // Pin not routed.
#define HEADER_CONNECTOR_CN5_D9     // Pin not routed.
#define HEADER_CONNECTOR_CN5_D10    // Pin not routed.
#define HEADER_CONNECTOR_CN5_D11    // Pin not routed.
#define HEADER_CONNECTOR_CN5_D12    GPIO_PC13
#define HEADER_CONNECTOR_CN5_D13    GPIO_P001
#define HEADER_CONNECTOR_CN5_D14    GPIO_PB14
#define HEADER_CONNECTOR_CN5_D15    GPIO_PE01
#define HEADER_CONNECTOR_CN5_D16    GPIO_PD04
#define HEADER_CONNECTOR_CN5_D17    GPIO_PD07
#define HEADER_CONNECTOR_CN5_D18    GPIO_PD01
#define HEADER_CONNECTOR_CN5_D19    GPIO_PD02
#define HEADER_CONNECTOR_CN5_D20    GPIO_PD03
#define HEADER_CONNECTOR_CN5_D21    GPIO_PC04
#define HEADER_CONNECTOR_CN5_D22    GPIO_PC05
#define HEADER_CONNECTOR_CN5_D23    GPIO_PB01
#define HEADER_CONNECTOR_CN5_D24    GPIO_PC11
#define HEADER_CONNECTOR_CN5_D25    GPIO_PC10
#define HEADER_CONNECTOR_CN5_D26    GPIO_PE00
#define HEADER_CONNECTOR_CN5_D27    GPIO_PC04
#define HEADER_CONNECTOR_CN5_D28    GPIO_PC05
#define HEADER_CONNECTOR_CN5_D29    GPIO_PE15
#define HEADER_CONNECTOR_CN5_D30    GPIO_PB10
#define HEADER_CONNECTOR_CN5_D31    // Pin not routed.
#define HEADER_CONNECTOR_CN5_D32    // Pin not routed.
#define HEADER_CONNECTOR_CN5_D33    // Pin not routed.
#define HEADER_CONNECTOR_CN5_D34    // Pin not routed.

#define HEADER_CONNECTOR_CN6_D1     GPIO_PA11
#define HEADER_CONNECTOR_CN6_D2     // Pin not routed.
#define HEADER_CONNECTOR_CN6_D3     GPIO_PA10
#define HEADER_CONNECTOR_CN6_D4     // Pin not routed.
#define HEADER_CONNECTOR_CN6_D5     // Pin not routed.
#define HEADER_CONNECTOR_CN6_D6     // Pin not routed.
#define HEADER_CONNECTOR_CN6_D7     // Pin not routed.
#define HEADER_CONNECTOR_CN6_D8     // Pin not routed.
#define HEADER_CONNECTOR_CN6_D9     // Pin not routed.
#define HEADER_CONNECTOR_CN6_D10    // Pin not routed.
#define HEADER_CONNECTOR_CN6_D11    // Pin not routed.
#define HEADER_CONNECTOR_CN6_D12    GPIO_PA12
#define HEADER_CONNECTOR_CN6_D13    GPIO_P000
#define HEADER_CONNECTOR_CN6_D14    GPIO_PB15
#define HEADER_CONNECTOR_CN6_D15    GPIO_PD11
#define HEADER_CONNECTOR_CN6_D16    GPIO_PC00
#define HEADER_CONNECTOR_CN6_D17    GPIO_PC01
#define HEADER_CONNECTOR_CN6_D18    GPIO_PD15
#define HEADER_CONNECTOR_CN6_D19    GPIO_PC06
#define HEADER_CONNECTOR_CN6_D20    GPIO_PC07
#define HEADER_CONNECTOR_CN6_D21    GPIO_PD12
#define HEADER_CONNECTOR_CN6_D22    GPIO_PD13
#define HEADER_CONNECTOR_CN6_D23    GPIO_PD14
#define HEADER_CONNECTOR_CN6_D24    GPIO_PC11
#define HEADER_CONNECTOR_CN6_D25    GPIO_PC10
#define HEADER_CONNECTOR_CN6_D26    GPIO_PD10
#define HEADER_CONNECTOR_CN6_D27    GPIO_PC02
#define HEADER_CONNECTOR_CN6_D28    GPIO_PC03
#define HEADER_CONNECTOR_CN6_D29    GPIO_PE11
#define HEADER_CONNECTOR_CN6_D30    GPIO_PE12
#define HEADER_CONNECTOR_CN6_D31    // Pin not routed.
#define HEADER_CONNECTOR_CN6_D32    // Pin not routed.
#define HEADER_CONNECTOR_CN6_D33    // Pin not routed.
#define HEADER_CONNECTOR_CN6_D34    // Pin not routed.

#define HEADER_CONNECTOR_CN7_D1     // Pin not routed.
#define HEADER_CONNECTOR_CN7_D2     // Pin not routed.
#define HEADER_CONNECTOR_CN7_D3     GPIO_PE13
#define HEADER_CONNECTOR_CN7_D4     // Pin not routed.
#define HEADER_CONNECTOR_CN7_D5     GPIO_PB02
#define HEADER_CONNECTOR_CN7_D6     GPIO_P002
#define HEADER_CONNECTOR_CN7_D7     GPIO_PE08
#define HEADER_CONNECTOR_CN7_D8     // Pin not routed.
#define HEADER_CONNECTOR_CN7_D9     GPIO_PE09
#define HEADER_CONNECTOR_CN7_D10    // Pin not routed.
#define HEADER_CONNECTOR_CN7_D11    GPIO_PE10
#define HEADER_CONNECTOR_CN7_D12    GPIO_PE11
#define HEADER_CONNECTOR_CN7_D13    GPIO_PE12
#define HEADER_CONNECTOR_CN7_D14    // Pin not routed.
#define HEADER_CONNECTOR_CN7_D15    GPIO_PC03
#define HEADER_CONNECTOR_CN7_D16    GPIO_PC02
#define HEADER_CONNECTOR_CN7_D17    GPIO_PE14
#define HEADER_CONNECTOR_CN7_D18    // Pin not routed.
#define HEADER_CONNECTOR_CN7_D19    // Pin not routed.
#define HEADER_CONNECTOR_CN7_D20    // Pin not routed.
#define HEADER_CONNECTOR_CN7_D21    // Pin not routed.
#define HEADER_CONNECTOR_CN7_D22    // Pin not routed.
#define HEADER_CONNECTOR_CN7_D23    // Pin not routed.
#define HEADER_CONNECTOR_CN7_D24    // Pin not routed.
#define HEADER_CONNECTOR_CN7_D25    // Pin not routed.
#define HEADER_CONNECTOR_CN7_D26    // Pin not routed.
#define HEADER_CONNECTOR_CN7_D27    GPIO_PC09
#define HEADER_CONNECTOR_CN7_D28    // Pin not routed.
#define HEADER_CONNECTOR_CN7_D29    GPIO_PC08
#define HEADER_CONNECTOR_CN7_D30    // Pin not routed.
#define HEADER_CONNECTOR_CN7_D31    GPIO_PA09
#define HEADER_CONNECTOR_CN7_D32    // Pin not routed.
#define HEADER_CONNECTOR_CN7_D33    GPIO_PA08
#define HEADER_CONNECTOR_CN7_D34    // Pin not routed.

#define LED1    GPIO_PD01
#define LED2    GPIO_PD02
#define LED3    GPIO_PD03
#define LED4    GPIO_PD15
#define LED5    GPIO_PC06
#define LED6    GPIO_PC07

#ifdef __cplusplus
}
#endif

#endif    // _BOARD_H_
// ------------------------------------------------------------------------- END
