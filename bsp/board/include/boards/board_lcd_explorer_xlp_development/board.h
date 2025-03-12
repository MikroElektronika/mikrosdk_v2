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

#define BOARD_NAME "LCD EXPLORER XLP DEVELOPMENT BOARD"

#include "pim_socket.h"

// Mapping
#define J6_D1   PIM_PIN_023
#define J6_D2   PIM_PIN_052
#define J6_D3   PIM_PIN_055
#define J6_D4   PIM_PIN_051
#define J6_D5   PIM_PIN_054
#define J6_D6   PIM_PIN_057
#define J6_D7   PIM_PIN_053
#define J6_D8   PIM_PIN_056
#define J6_D9   // Pin not routed
#define J6_D10  // Pin not routed
#define J6_D11  PIM_PIN_025
#define J6_D12  PIM_PIN_024
#define J6_D13  PIM_PIN_022
#define J6_D14  PIM_PIN_021
#define J6_D15  // Pin not routed
#define J6_D16  // Pin not routed
#define J6_D17  PIM_PIN_019
#define J6_D18  PIM_PIN_018
#define J6_D19  PIM_PIN_047
#define J6_D20  PIM_PIN_048
#define J6_D21  // Pin not routed
#define J6_D22  // Pin not routed
#define J6_D23  // Pin not routed
#define J6_D24  // Pin not routed
#define J6_D25  // Pin not routed
#define J6_D26  // Pin not routed
#define J6_D27  PIM_PIN_090
#define J6_D28  PIM_PIN_087
#define J6_D29  PIM_PIN_089
#define J6_D30  PIM_PIN_088
#define J6_D31  // Pin not routed
#define J6_D32  // Pin not routed
#define J6_D33  PIM_PIN_014
#define J6_D34  PIM_PIN_049
#define J6_D35  PIM_PIN_010
#define J6_D36  PIM_PIN_050
#define J6_D37  PIM_PIN_011
#define J6_D38  PIM_PIN_058
#define J6_D39  PIM_PIN_012
#define J6_D40  PIM_PIN_059
#define J6_D41  // Pin not routed
#define J6_D42  // Pin not routed
#define J6_D43  PIM_PIN_032
#define J6_D44  PIM_PIN_033
#define J6_D45  PIM_PIN_028
#define J6_D46  PIM_PIN_029
#define J6_D47  // Pin not routed
#define J6_D48  // Pin not routed
#define J6_D49  PIM_PIN_067
#define J6_D50  PIM_PIN_066
#define J6_D51  PIM_PIN_040
#define J6_D52  PIM_PIN_039
#define J6_D53  // Pin not routed
#define J6_D54  // Pin not routed
#define J6_D55  // Pin not routed
#define J6_D56  // Pin not routed
#define J6_D57  // Pin not routed
#define J6_D58  // Pin not routed
#define J6_D59  // Pin not routed
#define J6_D60  PIM_PIN_090
#define J6_D61  // Pin not routed
#define J6_D62  PIM_PIN_089
#define J6_D63  // Pin not routed
#define J6_D64  // Pin not routed
#define J6_D65  PIM_PIN_001
#define J6_D66  PIM_PIN_097
#define J6_D67  PIM_PIN_096
#define J6_D68  PIM_PIN_095
#define J6_D69  PIM_PIN_017
#define J6_D70  PIM_PIN_038
#define J6_D71  PIM_PIN_060
#define J6_D72  PIM_PIN_061
#define J6_D73  PIM_PIN_091
#define J6_D74  PIM_PIN_092
#define J6_D75  PIM_PIN_026
#define J6_D76  PIM_PIN_027
#define J6_D77  PIM_PIN_020
#define J6_D78  // Pin not routed
#define J6_D79  PIM_PIN_034
#define J6_D80  PIM_PIN_035
#define J6_D81  PIM_PIN_041
#define J6_D82  PIM_PIN_042
#define J6_D83  PIM_PIN_043
#define J6_D84  PIM_PIN_044
#define J6_D85  PIM_PIN_006
#define J6_D86  PIM_PIN_007
#define J6_D87  PIM_PIN_008
#define J6_D88  PIM_PIN_009
#define J6_D89  PIM_PIN_097
#define J6_D90  PIM_PIN_074
#define J6_D91  // Pin not routed
#define J6_D92  // Pin not routed
#define J6_D93  PIM_PIN_072
#define J6_D94  PIM_PIN_076
#define J6_D95  PIM_PIN_077
#define J6_D96  PIM_PIN_078
#define J6_D97  PIM_PIN_081
#define J6_D98  PIM_PIN_082
#define J6_D99  PIM_PIN_083
#define J6_D100 PIM_PIN_084
#define J6_D101 PIM_PIN_068
#define J6_D102 PIM_PIN_069
#define J6_D103 PIM_PIN_070
#define J6_D104 PIM_PIN_071
#define J6_D105 PIM_PIN_079
#define J6_D106 PIM_PIN_080
#define J6_D107 // Pin not routed
#define J6_D108 // Pin not routed
#define J6_D109 PIM_PIN_093
#define J6_D110 PIM_PIN_094
#define J6_D111 PIM_PIN_098
#define J6_D112 PIM_PIN_099
#define J6_D113 PIM_PIN_100
#define J6_D114 PIM_PIN_003
#define J6_D115 PIM_PIN_004
#define J6_D116 PIM_PIN_005
#define J6_D117 // Pin not routed
#define J6_D118 // Pin not routed
#define J6_D119 // Pin not routed
#define J6_D120 // Pin not routed

#define J7_D1   PIM_PIN_023
#define J7_D2   PIM_PIN_052
#define J7_D3   PIM_PIN_055
#define J7_D4   PIM_PIN_051
#define J7_D5   PIM_PIN_054
#define J7_D6   PIM_PIN_057
#define J7_D7   PIM_PIN_053
#define J7_D8   PIM_PIN_056
#define J7_D9   // Pin not routed
#define J7_D10  // Pin not routed
#define J7_D11  PIM_PIN_025
#define J7_D12  PIM_PIN_024
#define J7_D13  PIM_PIN_022
#define J7_D14  PIM_PIN_021
#define J7_D15  // Pin not routed
#define J7_D16  // Pin not routed
#define J7_D17  PIM_PIN_019
#define J7_D18  PIM_PIN_018
#define J7_D19  PIM_PIN_047
#define J7_D20  PIM_PIN_048
#define J7_D21  // Pin not routed
#define J7_D22  // Pin not routed
#define J7_D23  // Pin not routed
#define J7_D24  // Pin not routed
#define J7_D25  // Pin not routed
#define J7_D26  // Pin not routed
#define J7_D27  PIM_PIN_090
#define J7_D28  PIM_PIN_087
#define J7_D29  PIM_PIN_089
#define J7_D30  PIM_PIN_088
#define J7_D31  // Pin not routed
#define J7_D32  // Pin not routed
#define J7_D33  PIM_PIN_014
#define J7_D34  PIM_PIN_049
#define J7_D35  PIM_PIN_010
#define J7_D36  PIM_PIN_050
#define J7_D37  PIM_PIN_011
#define J7_D38  PIM_PIN_058
#define J7_D39  PIM_PIN_012
#define J7_D40  PIM_PIN_059
#define J7_D41  // Pin not routed
#define J7_D42  // Pin not routed
#define J7_D43  PIM_PIN_032
#define J7_D44  PIM_PIN_033
#define J7_D45  PIM_PIN_028
#define J7_D46  PIM_PIN_029
#define J7_D47  // Pin not routed
#define J7_D48  // Pin not routed
#define J7_D49  PIM_PIN_067
#define J7_D50  PIM_PIN_066
#define J7_D51  PIM_PIN_040
#define J7_D52  PIM_PIN_039
#define J7_D53  // Pin not routed
#define J7_D54  // Pin not routed
#define J7_D55  // Pin not routed
#define J7_D56  // Pin not routed
#define J7_D57  // Pin not routed
#define J7_D58  // Pin not routed
#define J7_D59  // Pin not routed
#define J7_D60  PIM_PIN_090
#define J7_D61  // Pin not routed
#define J7_D62  PIM_PIN_089
#define J7_D63  // Pin not routed
#define J7_D64  // Pin not routed
#define J7_D65  PIM_PIN_001
#define J7_D66  PIM_PIN_097
#define J7_D67  PIM_PIN_096
#define J7_D68  PIM_PIN_095
#define J7_D69  PIM_PIN_017
#define J7_D70  PIM_PIN_038
#define J7_D71  PIM_PIN_060
#define J7_D72  PIM_PIN_061
#define J7_D73  PIM_PIN_091
#define J7_D74  PIM_PIN_092
#define J7_D75  PIM_PIN_026
#define J7_D76  PIM_PIN_027
#define J7_D77  PIM_PIN_020
#define J7_D78  // Pin not routed
#define J7_D79  PIM_PIN_034
#define J7_D80  PIM_PIN_035
#define J7_D81  PIM_PIN_041
#define J7_D82  PIM_PIN_042
#define J7_D83  PIM_PIN_043
#define J7_D84  PIM_PIN_044
#define J7_D85  PIM_PIN_006
#define J7_D86  PIM_PIN_007
#define J7_D87  PIM_PIN_008
#define J7_D88  PIM_PIN_009
#define J7_D89  PIM_PIN_097
#define J7_D90  PIM_PIN_074
#define J7_D91  // Pin not routed
#define J7_D92  // Pin not routed
#define J7_D93  PIM_PIN_072
#define J7_D94  PIM_PIN_076
#define J7_D95  PIM_PIN_077
#define J7_D96  PIM_PIN_078
#define J7_D97  PIM_PIN_081
#define J7_D98  PIM_PIN_082
#define J7_D99  PIM_PIN_083
#define J7_D100 PIM_PIN_084
#define J7_D101 PIM_PIN_068
#define J7_D102 PIM_PIN_069
#define J7_D103 PIM_PIN_070
#define J7_D104 PIM_PIN_071
#define J7_D105 PIM_PIN_079
#define J7_D106 PIM_PIN_080
#define J7_D107 // Pin not routed
#define J7_D108 // Pin not routed
#define J7_D109 PIM_PIN_093
#define J7_D110 PIM_PIN_094
#define J7_D111 PIM_PIN_098
#define J7_D112 PIM_PIN_099
#define J7_D113 PIM_PIN_100
#define J7_D114 PIM_PIN_003
#define J7_D115 PIM_PIN_004
#define J7_D116 PIM_PIN_005
#define J7_D117 // Pin not routed
#define J7_D118 // Pin not routed
#define J7_D119 // Pin not routed
#define J7_D120 // Pin not routed

#ifdef __cplusplus
}
#endif

#endif    // _BOARD_H_
// ------------------------------------------------------------------------- END
