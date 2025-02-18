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

#define BOARD_NAME "dsPICDEM Connectivity Development Board"

#include "pim_socket.h"

// Mapping
#define HEADER_J10_1    PIM_PIN_031
#define HEADER_J10_2    PIM_PIN_083
#define HEADER_J10_3    PIM_PIN_082
#define HEADER_J10_4    PIM_PIN_081
#define HEADER_J10_5    PIM_PIN_080
#define HEADER_J10_6    PIM_PIN_038
#define HEADER_J10_7    PIM_PIN_037
#define HEADER_J10_8    PIM_PIN_036
#define HEADER_J10_9    PIM_PIN_076
#define HEADER_J10_10   PIM_PIN_035
#define HEADER_J10_11   // Pin not routed
#define HEADER_J10_12   // Pin not routed
#define HEADER_J10_13   // Pin not routed
#define HEADER_J10_14   PIM_PIN_090
#define HEADER_J10_15   PIM_PIN_089
#define HEADER_J10_16   PIM_PIN_012
#define HEADER_J10_17   PIM_PIN_010
#define HEADER_J10_18   PIM_PIN_008
#define HEADER_J10_19   PIM_PIN_006
#define HEADER_J10_20   PIM_PIN_004
#define HEADER_J10_21   PIM_PIN_002

#define HEADER_J11_1    PIM_PIN_014
#define HEADER_J11_2    PIM_PIN_016
#define HEADER_J11_3    PIM_PIN_091
#define HEADER_J11_4    PIM_PIN_092
#define HEADER_J11_5    PIM_PIN_025
#define HEADER_J11_6    // Pin not routed
#define HEADER_J11_7    PIM_PIN_018
#define HEADER_J11_8    PIM_PIN_020
#define HEADER_J11_9    PIM_PIN_022
#define HEADER_J11_10   PIM_PIN_024
#define HEADER_J11_11   // Pin not routed
#define HEADER_J11_12   // Pin not routed
#define HEADER_J11_13   // Pin not routed
#define HEADER_J11_14   PIM_PIN_026
#define HEADER_J11_15   PIM_PIN_028
#define HEADER_J11_16   PIM_PIN_019
#define HEADER_J11_17   PIM_PIN_017
#define HEADER_J11_18   PIM_PIN_056
#define HEADER_J11_19   PIM_PIN_055
#define HEADER_J11_20   PIM_PIN_048
#define HEADER_J11_21   PIM_PIN_047

#define HEADER_J12_1    PIM_PIN_049
#define HEADER_J12_2    PIM_PIN_050
#define HEADER_J12_3    PIM_PIN_044
#define HEADER_J12_4    PIM_PIN_045
#define HEADER_J12_5    PIM_PIN_046
#define HEADER_J12_6    PIM_PIN_039
#define HEADER_J12_7    PIM_PIN_040
#define HEADER_J12_8    // Pin not routed
#define HEADER_J12_9    // Pin not routed
#define HEADER_J12_10   // Pin not routed
#define HEADER_J12_11   // Pin not routed
#define HEADER_J12_12   // Pin not routed
#define HEADER_J12_13   PIM_PIN_088
#define HEADER_J12_14   PIM_PIN_087
#define HEADER_J12_15   PIM_PIN_062
#define HEADER_J12_16   PIM_PIN_061
#define HEADER_J12_17   PIM_PIN_060
#define HEADER_J12_18   PIM_PIN_059
#define HEADER_J12_19   PIM_PIN_072
#define HEADER_J12_20   PIM_PIN_079
#define HEADER_J12_21   PIM_PIN_078

#define HEADER_J13_1    PIM_PIN_071
#define HEADER_J13_2    PIM_PIN_070
#define HEADER_J13_3    PIM_PIN_069
#define HEADER_J13_4    PIM_PIN_058
#define HEADER_J13_5    PIM_PIN_057
#define HEADER_J13_6    PIM_PIN_068
#define HEADER_J13_7    PIM_PIN_067
#define HEADER_J13_8    PIM_PIN_066
#define HEADER_J13_9    PIM_PIN_065
#define HEADER_J13_10   // Pin not routed
#define HEADER_J13_11   // Pin not routed
#define HEADER_J13_12   // Pin not routed
#define HEADER_J13_13   PIM_PIN_052
#define HEADER_J13_14   PIM_PIN_051
#define HEADER_J13_15   PIM_PIN_041
#define HEADER_J13_16   PIM_PIN_042
#define HEADER_J13_17   PIM_PIN_094
#define HEADER_J13_18   PIM_PIN_093
#define HEADER_J13_19   PIM_PIN_032
#define HEADER_J13_20   PIM_PIN_034
#define HEADER_J13_21   PIM_PIN_033

#define BUTTON_1    PIM_PIN_090
#define BUTTON_2    PIM_PIN_089
#define BUTTON_3    PIM_PIN_088
#define LED_1       PIM_PIN_082
#define LED_2       PIM_PIN_081
#define LED_3       PIM_PIN_080

#ifdef __cplusplus
}
#endif

#endif    // _BOARD_H_
// ------------------------------------------------------------------------- END
