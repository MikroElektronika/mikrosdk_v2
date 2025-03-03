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

#define BOARD_NAME "32-BIT ACCESSORY DEVELOPMENT STARTER KIT"

#include "pim_socket.h"

// Mapping
#define J2_D1   PIM_PIN_023
#define J2_D2   PIM_PIN_052
#define J2_D3   PIM_PIN_055
#define J2_D4   PIM_PIN_051
#define J2_D5   PIM_PIN_054
#define J2_D6   PIM_PIN_057
#define J2_D7   PIM_PIN_053
#define J2_D8   PIM_PIN_056
#define J2_D9   // Pin not routed
#define J2_D10  // Pin not routed
#define J2_D11  PIM_PIN_025
#define J2_D12  PIM_PIN_024
#define J2_D13  PIM_PIN_022
#define J2_D14  PIM_PIN_021
#define J2_D15  // Pin not routed
#define J2_D16  // Pin not routed
#define J2_D17  PIM_PIN_019
#define J2_D18  PIM_PIN_018
#define J2_D19  PIM_PIN_047
#define J2_D20  PIM_PIN_048
#define J2_D21  // Pin not routed
#define J2_D22  // Pin not routed
#define J2_D23  // Pin not routed
#define J2_D24  // Pin not routed
#define J2_D25  // Pin not routed
#define J2_D26  // Pin not routed
#define J2_D27  PIM_PIN_090
#define J2_D28  PIM_PIN_087
#define J2_D29  PIM_PIN_089
#define J2_D30  PIM_PIN_088
#define J2_D31  // Pin not routed
#define J2_D32  // Pin not routed
#define J2_D33  PIM_PIN_014
#define J2_D34  PIM_PIN_049
#define J2_D35  PIM_PIN_010
#define J2_D36  PIM_PIN_050
#define J2_D37  PIM_PIN_011
#define J2_D38  PIM_PIN_058
#define J2_D39  PIM_PIN_012
#define J2_D40  PIM_PIN_059
#define J2_D41  // Pin not routed
#define J2_D42  // Pin not routed
#define J2_D43  PIM_PIN_032
#define J2_D44  PIM_PIN_033
#define J2_D45  PIM_PIN_028
#define J2_D46  PIM_PIN_029
#define J2_D47  // Pin not routed
#define J2_D48  // Pin not routed
#define J2_D49  PIM_PIN_067
#define J2_D50  PIM_PIN_066
#define J2_D51  PIM_PIN_040
#define J2_D52  PIM_PIN_039
#define J2_D53  // Pin not routed
#define J2_D54  // Pin not routed
#define J2_D55  // Pin not routed
#define J2_D56  // Pin not routed
#define J2_D57  // Pin not routed
#define J2_D58  // Pin not routed
#define J2_D59  // Pin not routed
#define J2_D60  PIM_PIN_090
#define J2_D61  // Pin not routed
#define J2_D62  PIM_PIN_089
#define J2_D63  // Pin not routed
#define J2_D64  // Pin not routed
#define J2_D65  PIM_PIN_001
#define J2_D66  PIM_PIN_097
#define J2_D67  PIM_PIN_096
#define J2_D68  PIM_PIN_095
#define J2_D69  PIM_PIN_017
#define J2_D70  PIM_PIN_038
#define J2_D71  PIM_PIN_060
#define J2_D72  PIM_PIN_061
#define J2_D73  PIM_PIN_091
#define J2_D74  PIM_PIN_092
#define J2_D75  PIM_PIN_026
#define J2_D76  PIM_PIN_027
#define J2_D77  PIM_PIN_020
#define J2_D78  // Pin not routed
#define J2_D79  PIM_PIN_034
#define J2_D80  PIM_PIN_035
#define J2_D81  PIM_PIN_041
#define J2_D82  PIM_PIN_042
#define J2_D83  PIM_PIN_043
#define J2_D84  PIM_PIN_044
#define J2_D85  PIM_PIN_006
#define J2_D86  PIM_PIN_007
#define J2_D87  PIM_PIN_008
#define J2_D88  PIM_PIN_009
#define J2_D89  PIM_PIN_097
#define J2_D90  PIM_PIN_074
#define J2_D91  // Pin not routed
#define J2_D92  // Pin not routed
#define J2_D93  PIM_PIN_072
#define J2_D94  PIM_PIN_076
#define J2_D95  PIM_PIN_077
#define J2_D96  PIM_PIN_078
#define J2_D97  PIM_PIN_081
#define J2_D98  PIM_PIN_082
#define J2_D99  PIM_PIN_083
#define J2_D100 PIM_PIN_084
#define J2_D101 PIM_PIN_068
#define J2_D102 PIM_PIN_069
#define J2_D103 PIM_PIN_070
#define J2_D104 PIM_PIN_071
#define J2_D105 PIM_PIN_079
#define J2_D106 PIM_PIN_080
#define J2_D107 // Pin not routed
#define J2_D108 // Pin not routed
#define J2_D109 PIM_PIN_093
#define J2_D110 PIM_PIN_094
#define J2_D111 PIM_PIN_098
#define J2_D112 PIM_PIN_099
#define J2_D113 PIM_PIN_100
#define J2_D114 PIM_PIN_003
#define J2_D115 PIM_PIN_004
#define J2_D116 PIM_PIN_005
#define J2_D117 // Pin not routed
#define J2_D118 // Pin not routed
#define J2_D119 // Pin not routed
#define J2_D120 // Pin not routed

#define J4_D1   PIM_PIN_023
#define J4_D2   PIM_PIN_052
#define J4_D3   PIM_PIN_055
#define J4_D4   PIM_PIN_051
#define J4_D5   PIM_PIN_054
#define J4_D6   PIM_PIN_057
#define J4_D7   PIM_PIN_053
#define J4_D8   PIM_PIN_056
#define J4_D9   // Pin not routed
#define J4_D10  // Pin not routed
#define J4_D11  PIM_PIN_025
#define J4_D12  PIM_PIN_024
#define J4_D13  PIM_PIN_022
#define J4_D14  PIM_PIN_021
#define J4_D15  // Pin not routed
#define J4_D16  // Pin not routed
#define J4_D17  PIM_PIN_019
#define J4_D18  PIM_PIN_018
#define J4_D19  PIM_PIN_047
#define J4_D20  PIM_PIN_048
#define J4_D21  // Pin not routed
#define J4_D22  // Pin not routed
#define J4_D23  // Pin not routed
#define J4_D24  // Pin not routed
#define J4_D25  // Pin not routed
#define J4_D26  // Pin not routed
#define J4_D27  PIM_PIN_090
#define J4_D28  PIM_PIN_087
#define J4_D29  PIM_PIN_089
#define J4_D30  PIM_PIN_088
#define J4_D31  // Pin not routed
#define J4_D32  // Pin not routed
#define J4_D33  PIM_PIN_014
#define J4_D34  PIM_PIN_049
#define J4_D35  PIM_PIN_010
#define J4_D36  PIM_PIN_050
#define J4_D37  PIM_PIN_011
#define J4_D38  PIM_PIN_058
#define J4_D39  PIM_PIN_012
#define J4_D40  PIM_PIN_059
#define J4_D41  // Pin not routed
#define J4_D42  // Pin not routed
#define J4_D43  PIM_PIN_032
#define J4_D44  PIM_PIN_033
#define J4_D45  PIM_PIN_028
#define J4_D46  PIM_PIN_029
#define J4_D47  // Pin not routed
#define J4_D48  // Pin not routed
#define J4_D49  PIM_PIN_067
#define J4_D50  PIM_PIN_066
#define J4_D51  PIM_PIN_040
#define J4_D52  PIM_PIN_039
#define J4_D53  // Pin not routed
#define J4_D54  // Pin not routed
#define J4_D55  // Pin not routed
#define J4_D56  // Pin not routed
#define J4_D57  // Pin not routed
#define J4_D58  // Pin not routed
#define J4_D59  // Pin not routed
#define J4_D60  PIM_PIN_090
#define J4_D61  // Pin not routed
#define J4_D62  PIM_PIN_089
#define J4_D63  // Pin not routed
#define J4_D64  // Pin not routed
#define J4_D65  PIM_PIN_001
#define J4_D66  PIM_PIN_097
#define J4_D67  PIM_PIN_096
#define J4_D68  PIM_PIN_095
#define J4_D69  PIM_PIN_017
#define J4_D70  PIM_PIN_038
#define J4_D71  PIM_PIN_060
#define J4_D72  PIM_PIN_061
#define J4_D73  PIM_PIN_091
#define J4_D74  PIM_PIN_092
#define J4_D75  PIM_PIN_026
#define J4_D76  PIM_PIN_027
#define J4_D77  PIM_PIN_020
#define J4_D78  // Pin not routed
#define J4_D79  PIM_PIN_034
#define J4_D80  PIM_PIN_035
#define J4_D81  PIM_PIN_041
#define J4_D82  PIM_PIN_042
#define J4_D83  PIM_PIN_043
#define J4_D84  PIM_PIN_044
#define J4_D85  PIM_PIN_006
#define J4_D86  PIM_PIN_007
#define J4_D87  PIM_PIN_008
#define J4_D88  PIM_PIN_009
#define J4_D89  PIM_PIN_097
#define J4_D90  PIM_PIN_074
#define J4_D91  // Pin not routed
#define J4_D92  // Pin not routed
#define J4_D93  PIM_PIN_072
#define J4_D94  PIM_PIN_076
#define J4_D95  PIM_PIN_077
#define J4_D96  PIM_PIN_078
#define J4_D97  PIM_PIN_081
#define J4_D98  PIM_PIN_082
#define J4_D99  PIM_PIN_083
#define J4_D100 PIM_PIN_084
#define J4_D101 PIM_PIN_068
#define J4_D102 PIM_PIN_069
#define J4_D103 PIM_PIN_070
#define J4_D104 PIM_PIN_071
#define J4_D105 PIM_PIN_079
#define J4_D106 PIM_PIN_080
#define J4_D107 // Pin not routed
#define J4_D108 // Pin not routed
#define J4_D109 PIM_PIN_093
#define J4_D110 PIM_PIN_094
#define J4_D111 PIM_PIN_098
#define J4_D112 PIM_PIN_099
#define J4_D113 PIM_PIN_100
#define J4_D114 PIM_PIN_003
#define J4_D115 PIM_PIN_004
#define J4_D116 PIM_PIN_005
#define J4_D117 // Pin not routed
#define J4_D118 // Pin not routed
#define J4_D119 // Pin not routed
#define J4_D120 // Pin not routed

#ifdef __cplusplus
}
#endif

#endif    // _BOARD_H_
// ------------------------------------------------------------------------- END
