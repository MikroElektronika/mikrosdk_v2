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

#define BOARD_NAME "Renesas Flexible Motor Control CPU Board for RA8T1 MCU Group"

#include "hal_target.h"

// Mapping
#define HEADER_CONNECTOR_CN1_D1     // Pin not routed.
#define HEADER_CONNECTOR_CN1_D2     // Pin not routed.
#define HEADER_CONNECTOR_CN1_D3     GPIO_P008
#define HEADER_CONNECTOR_CN1_D4     // Pin not routed.
#define HEADER_CONNECTOR_CN1_D5     GPIO_P004
#define HEADER_CONNECTOR_CN1_D6     // Pin not routed.
#define HEADER_CONNECTOR_CN1_D7     GPIO_P005
#define HEADER_CONNECTOR_CN1_D8     // Pin not routed.
#define HEADER_CONNECTOR_CN1_D9     GPIO_P006
#define HEADER_CONNECTOR_CN1_D10    // Pin not routed.
#define HEADER_CONNECTOR_CN1_D11    GPIO_P011
#define HEADER_CONNECTOR_CN1_D12    GPIO_P010
#define HEADER_CONNECTOR_CN1_D13    GPIO_P015
#define HEADER_CONNECTOR_CN1_D14    // Pin not routed.
#define HEADER_CONNECTOR_CN1_D15    GPIO_P015
#define HEADER_CONNECTOR_CN1_D16    GPIO_P010
#define HEADER_CONNECTOR_CN1_D17    GPIO_P014
#define HEADER_CONNECTOR_CN1_D18    // Pin not routed.
#define HEADER_CONNECTOR_CN1_D19    // Pin not routed.
#define HEADER_CONNECTOR_CN1_D20    // Pin not routed.
#define HEADER_CONNECTOR_CN1_D21    // Pin not routed.
#define HEADER_CONNECTOR_CN1_D22    // Pin not routed.
#define HEADER_CONNECTOR_CN1_D23    // Pin not routed.
#define HEADER_CONNECTOR_CN1_D24    // Pin not routed.
#define HEADER_CONNECTOR_CN1_D25    // Pin not routed.
#define HEADER_CONNECTOR_CN1_D26    // Pin not routed.
#define HEADER_CONNECTOR_CN1_D27    GPIO_P609
#define HEADER_CONNECTOR_CN1_D28    // Pin not routed.
#define HEADER_CONNECTOR_CN1_D29    GPIO_P115
#define HEADER_CONNECTOR_CN1_D30    // Pin not routed.
#define HEADER_CONNECTOR_CN1_D31    GPIO_P114
#define HEADER_CONNECTOR_CN1_D32    // Pin not routed.
#define HEADER_CONNECTOR_CN1_D33    GPIO_P113
#define HEADER_CONNECTOR_CN1_D34    // Pin not routed.

#define HEADER_CONNECTOR_CN2_D1     GPIO_P112
#define HEADER_CONNECTOR_CN2_D2     // Pin not routed.
#define HEADER_CONNECTOR_CN2_D3     GPIO_P300
#define HEADER_CONNECTOR_CN2_D4     // Pin not routed.
#define HEADER_CONNECTOR_CN2_D5     GPIO_P102
#define HEADER_CONNECTOR_CN2_D6     GPIO_P101
#define HEADER_CONNECTOR_CN2_D7     GPIO_P100
#define HEADER_CONNECTOR_CN2_D8     GPIO_P106
#define HEADER_CONNECTOR_CN2_D9     // Pin not routed.
#define HEADER_CONNECTOR_CN2_D10    GPIO_PA08
#define HEADER_CONNECTOR_CN2_D11    GPIO_P612
#define HEADER_CONNECTOR_CN2_D12    GPIO_P613
#define HEADER_CONNECTOR_CN2_D13    GPIO_P613
#define HEADER_CONNECTOR_CN2_D14    GPIO_P410
#define HEADER_CONNECTOR_CN2_D15    GPIO_PA11
#define HEADER_CONNECTOR_CN2_D16    GPIO_PA15
#define HEADER_CONNECTOR_CN2_D17    GPIO_PA13
#define HEADER_CONNECTOR_CN2_D18    GPIO_PA12
#define HEADER_CONNECTOR_CN2_D19    GPIO_PA14
#define HEADER_CONNECTOR_CN2_D20    // Pin not routed.
#define HEADER_CONNECTOR_CN2_D21    GPIO_P907
#define HEADER_CONNECTOR_CN2_D22    GPIO_P905
#define HEADER_CONNECTOR_CN2_D23    GPIO_P906
#define HEADER_CONNECTOR_CN2_D24    GPIO_P206
#define HEADER_CONNECTOR_CN2_D25    GPIO_P205
#define HEADER_CONNECTOR_CN2_D26    GPIO_P615
#define HEADER_CONNECTOR_CN2_D27    GPIO_P502
#define HEADER_CONNECTOR_CN2_D28    GPIO_P500
#define HEADER_CONNECTOR_CN2_D29    GPIO_P501
#define HEADER_CONNECTOR_CN2_D30    GPIO_P812
#define HEADER_CONNECTOR_CN2_D31    // Pin not routed.
#define HEADER_CONNECTOR_CN2_D32    // Pin not routed.
#define HEADER_CONNECTOR_CN2_D33    // Pin not routed.
#define HEADER_CONNECTOR_CN2_D34    // Pin not routed.

#define HEADER_CONNECTOR_CN3_D1     // Pin not routed.
#define HEADER_CONNECTOR_CN3_D2     // Pin not routed.
#define HEADER_CONNECTOR_CN3_D3     GPIO_P000
#define HEADER_CONNECTOR_CN3_D4     // Pin not routed.
#define HEADER_CONNECTOR_CN3_D5     GPIO_P513
#define HEADER_CONNECTOR_CN3_D6     // Pin not routed.
#define HEADER_CONNECTOR_CN3_D7     GPIO_P001
#define HEADER_CONNECTOR_CN3_D8     // Pin not routed.
#define HEADER_CONNECTOR_CN3_D9     GPIO_P002
#define HEADER_CONNECTOR_CN3_D10    // Pin not routed.
#define HEADER_CONNECTOR_CN3_D11    GPIO_P003
#define HEADER_CONNECTOR_CN3_D12    GPIO_P806
#define HEADER_CONNECTOR_CN3_D13    GPIO_P805
#define HEADER_CONNECTOR_CN3_D14    // Pin not routed.
#define HEADER_CONNECTOR_CN3_D15    GPIO_P011
#define HEADER_CONNECTOR_CN3_D16    GPIO_P009
#define HEADER_CONNECTOR_CN3_D17    GPIO_P009
#define HEADER_CONNECTOR_CN3_D18    // Pin not routed.
#define HEADER_CONNECTOR_CN3_D19    // Pin not routed.
#define HEADER_CONNECTOR_CN3_D20    // Pin not routed.
#define HEADER_CONNECTOR_CN3_D21    // Pin not routed.
#define HEADER_CONNECTOR_CN3_D22    // Pin not routed.
#define HEADER_CONNECTOR_CN3_D23    // Pin not routed.
#define HEADER_CONNECTOR_CN3_D24    // Pin not routed.
#define HEADER_CONNECTOR_CN3_D25    // Pin not routed.
#define HEADER_CONNECTOR_CN3_D26    // Pin not routed.
#define HEADER_CONNECTOR_CN3_D27    GPIO_P803
#define HEADER_CONNECTOR_CN3_D28    // Pin not routed.
#define HEADER_CONNECTOR_CN3_D29    GPIO_P802
#define HEADER_CONNECTOR_CN3_D30    // Pin not routed.
#define HEADER_CONNECTOR_CN3_D31    GPIO_P602
#define HEADER_CONNECTOR_CN3_D32    // Pin not routed.
#define HEADER_CONNECTOR_CN3_D33    GPIO_P603
#define HEADER_CONNECTOR_CN3_D34    // Pin not routed.

#define HEADER_CONNECTOR_CN4_D1     GPIO_P600
#define HEADER_CONNECTOR_CN4_D2     // Pin not routed.
#define HEADER_CONNECTOR_CN4_D3     GPIO_P601
#define HEADER_CONNECTOR_CN4_D4     // Pin not routed.
#define HEADER_CONNECTOR_CN4_D5     GPIO_P102
#define HEADER_CONNECTOR_CN4_D6     GPIO_P101
#define HEADER_CONNECTOR_CN4_D7     GPIO_P100
#define HEADER_CONNECTOR_CN4_D8     GPIO_P104
#define HEADER_CONNECTOR_CN4_D9     // Pin not routed.
#define HEADER_CONNECTOR_CN4_D10    GPIO_P810
#define HEADER_CONNECTOR_CN4_D11    GPIO_P809
#define HEADER_CONNECTOR_CN4_D12    GPIO_P804
#define HEADER_CONNECTOR_CN4_D13    GPIO_P804
#define HEADER_CONNECTOR_CN4_D14    GPIO_P808
#define HEADER_CONNECTOR_CN4_D15    GPIO_P605
#define HEADER_CONNECTOR_CN4_D16    GPIO_P604
#define HEADER_CONNECTOR_CN4_D17    GPIO_P504
#define HEADER_CONNECTOR_CN4_D18    GPIO_P606
#define HEADER_CONNECTOR_CN4_D19    GPIO_PA06
#define HEADER_CONNECTOR_CN4_D20    // Pin not routed.
#define HEADER_CONNECTOR_CN4_D21    GPIO_PA10
#define HEADER_CONNECTOR_CN4_D22    GPIO_P801
#define HEADER_CONNECTOR_CN4_D23    GPIO_PA09
#define HEADER_CONNECTOR_CN4_D24    GPIO_P206
#define HEADER_CONNECTOR_CN4_D25    GPIO_PP205
#define HEADER_CONNECTOR_CN4_D26    GPIO_P614
#define HEADER_CONNECTOR_CN4_D27    GPIO_P003
#define HEADER_CONNECTOR_CN4_D28    GPIO_P806
#define HEADER_CONNECTOR_CN4_D29    GPIO_P805
#define HEADER_CONNECTOR_CN4_D30    GPIO_P007
#define HEADER_CONNECTOR_CN4_D31    // Pin not routed.
#define HEADER_CONNECTOR_CN4_D32    // Pin not routed.
#define HEADER_CONNECTOR_CN4_D33    // Pin not routed.
#define HEADER_CONNECTOR_CN4_D34    // Pin not routed.

#define HEADER_CONNECTOR_CN6_D1     GPIO_P204
#define HEADER_CONNECTOR_CN6_D2     GPIO_P202
#define HEADER_CONNECTOR_CN6_D3     GPIO_P313
#define HEADER_CONNECTOR_CN6_D4     GPIO_P203
#define HEADER_CONNECTOR_CN6_D5     // Pin not routed.
#define HEADER_CONNECTOR_CN6_D6     // Pin not routed.
#define HEADER_CONNECTOR_CN6_D7     GPIO_P708
#define HEADER_CONNECTOR_CN6_D8     GPIO_P412
#define HEADER_CONNECTOR_CN6_D9     GPIO_P411
#define HEADER_CONNECTOR_CN6_D10    GPIO_P902
#define HEADER_CONNECTOR_CN6_D11    // Pin not routed.
#define HEADER_CONNECTOR_CN6_D12    // Pin not routed.

#define HEADER_CONNECTOR_CN7_D1     GPIO_P908
#define HEADER_CONNECTOR_CN7_D2     GPIO_P710
#define HEADER_CONNECTOR_CN7_D3     GPIO_P205
#define HEADER_CONNECTOR_CN7_D4     GPIO_P206
#define HEADER_CONNECTOR_CN7_D5     // Pin not routed.
#define HEADER_CONNECTOR_CN7_D6     // Pin not routed.
#define HEADER_CONNECTOR_CN7_D7     GPIO_P712
#define HEADER_CONNECTOR_CN7_D8     GPIO_P413
#define HEADER_CONNECTOR_CN7_D9     GPIO_P207
#define HEADER_CONNECTOR_CN7_D10    GPIO_P315
#define HEADER_CONNECTOR_CN7_D11    // Pin not routed.
#define HEADER_CONNECTOR_CN7_D12    // Pin not routed.

#define LED1    GPIO_PA12
#define LED2    GPIO_PA14
#define LED3    GPIO_P606
#define LED4    GPIO_PA06

#ifdef __cplusplus
}
#endif

#endif    // _BOARD_H_
// ------------------------------------------------------------------------- END
