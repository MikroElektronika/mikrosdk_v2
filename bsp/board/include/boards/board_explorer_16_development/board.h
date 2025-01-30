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

#define BOARD_NAME "Explorer 16 Development Board"

#include "pim_socket.h"

// Mapping
#define J5_D1   PIM_PIN_023
#define J5_D2   PIM_PIN_052
#define J5_D3   PIM_PIN_055
#define J5_D4   PIM_PIN_051
#define J5_D5   PIM_PIN_054
#define J5_D6   PIM_PIN_057
#define J5_D7   PIM_PIN_053
#define J5_D8   PIM_PIN_056
#define J5_D9   // Pin not routed
#define J5_D10  // Pin not routed
#define J5_D11  PIM_PIN_025
#define J5_D12  PIM_PIN_024
#define J5_D13  PIM_PIN_022
#define J5_D14  PIM_PIN_021
#define J5_D15  // Pin not routed
#define J5_D16  // Pin not routed
#define J5_D17  PIM_PIN_019
#define J5_D18  PIM_PIN_018
#define J5_D19  PIM_PIN_047
#define J5_D20  PIM_PIN_048
#define J5_D21  // Pin not routed
#define J5_D22  // Pin not routed
#define J5_D23  // Pin not routed
#define J5_D24  // Pin not routed
#define J5_D25  // Pin not routed
#define J5_D26  // Pin not routed
#define J5_D27  PIM_PIN_090
#define J5_D28  PIM_PIN_087
#define J5_D29  PIM_PIN_089
#define J5_D30  PIM_PIN_088
#define J5_D31  // Pin not routed
#define J5_D32  // Pin not routed
#define J5_D33  PIM_PIN_014
#define J5_D34  PIM_PIN_049
#define J5_D35  PIM_PIN_010
#define J5_D36  PIM_PIN_050
#define J5_D37  PIM_PIN_011
#define J5_D38  PIM_PIN_058
#define J5_D39  PIM_PIN_012
#define J5_D40  PIM_PIN_059
#define J5_D41  // Pin not routed
#define J5_D42  // Pin not routed
#define J5_D43  PIM_PIN_032
#define J5_D44  PIM_PIN_033
#define J5_D45  PIM_PIN_028
#define J5_D46  PIM_PIN_029
#define J5_D47  // Pin not routed
#define J5_D48  // Pin not routed
#define J5_D49  PIM_PIN_067
#define J5_D50  PIM_PIN_066
#define J5_D51  PIM_PIN_040
#define J5_D52  PIM_PIN_039
#define J5_D53  // Pin not routed
#define J5_D54  // Pin not routed
#define J5_D55  // Pin not routed
#define J5_D56  // Pin not routed
#define J5_D57  // Pin not routed
#define J5_D58  // Pin not routed
#define J5_D59  // Pin not routed
#define J5_D60  PIM_PIN_090
#define J5_D61  // Pin not routed
#define J5_D62  PIM_PIN_089
#define J5_D63  // Pin not routed
#define J5_D64  // Pin not routed
#define J5_D65  PIM_PIN_001
#define J5_D66  PIM_PIN_097
#define J5_D67  PIM_PIN_096
#define J5_D68  PIM_PIN_095
#define J5_D69  PIM_PIN_017
#define J5_D70  PIM_PIN_038
#define J5_D71  PIM_PIN_060
#define J5_D72  PIM_PIN_061
#define J5_D73  PIM_PIN_091
#define J5_D74  PIM_PIN_092
#define J5_D75  PIM_PIN_026
#define J5_D76  PIM_PIN_027
#define J5_D77  PIM_PIN_020
#define J5_D78  // Pin not routed
#define J5_D79  PIM_PIN_034
#define J5_D80  PIM_PIN_035
#define J5_D81  PIM_PIN_041
#define J5_D82  PIM_PIN_042
#define J5_D83  PIM_PIN_043
#define J5_D84  PIM_PIN_044
#define J5_D85  PIM_PIN_006
#define J5_D86  PIM_PIN_007
#define J5_D87  PIM_PIN_008
#define J5_D88  PIM_PIN_009
#define J5_D89  PIM_PIN_097
#define J5_D90  PIM_PIN_074
#define J5_D91  // Pin not routed
#define J5_D92  // Pin not routed
#define J5_D93  PIM_PIN_072
#define J5_D94  PIM_PIN_076
#define J5_D95  PIM_PIN_077
#define J5_D96  PIM_PIN_078
#define J5_D97  PIM_PIN_081
#define J5_D98  PIM_PIN_082
#define J5_D99  PIM_PIN_083
#define J5_D100 PIM_PIN_084
#define J5_D101 PIM_PIN_068
#define J5_D102 PIM_PIN_069
#define J5_D103 PIM_PIN_070
#define J5_D104 PIM_PIN_071
#define J5_D105 PIM_PIN_079
#define J5_D106 PIM_PIN_080
#define J5_D107 // Pin not routed
#define J5_D108 // Pin not routed
#define J5_D109 PIM_PIN_093
#define J5_D110 PIM_PIN_094
#define J5_D111 PIM_PIN_098
#define J5_D112 PIM_PIN_099
#define J5_D113 PIM_PIN_100
#define J5_D114 PIM_PIN_003
#define J5_D115 PIM_PIN_004
#define J5_D116 PIM_PIN_005
#define J5_D117 // Pin not routed
#define J5_D118 // Pin not routed
#define J5_D119 // Pin not routed
#define J5_D120 // Pin not routed

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

#define J9_D1   PIM_PIN_023
#define J9_D2   PIM_PIN_052
#define J9_D3   PIM_PIN_055
#define J9_D4   PIM_PIN_051
#define J9_D5   PIM_PIN_054
#define J9_D6   PIM_PIN_057
#define J9_D7   PIM_PIN_053
#define J9_D8   PIM_PIN_056
#define J9_D9   // Pin not routed
#define J9_D10  // Pin not routed
#define J9_D11  PIM_PIN_025
#define J9_D12  PIM_PIN_024
#define J9_D13  PIM_PIN_022
#define J9_D14  PIM_PIN_021
#define J9_D15  // Pin not routed
#define J9_D16  // Pin not routed
#define J9_D17  PIM_PIN_019
#define J9_D18  PIM_PIN_018
#define J9_D19  PIM_PIN_047
#define J9_D20  PIM_PIN_048
#define J9_D21  // Pin not routed
#define J9_D22  // Pin not routed
#define J9_D23  // Pin not routed
#define J9_D24  // Pin not routed
#define J9_D25  // Pin not routed
#define J9_D26  // Pin not routed
#define J9_D27  PIM_PIN_090
#define J9_D28  PIM_PIN_087
#define J9_D29  PIM_PIN_089
#define J9_D30  PIM_PIN_088
#define J9_D31  // Pin not routed
#define J9_D32  // Pin not routed
#define J9_D33  PIM_PIN_014
#define J9_D34  PIM_PIN_049
#define J9_D35  PIM_PIN_010
#define J9_D36  PIM_PIN_050
#define J9_D37  PIM_PIN_011
#define J9_D38  PIM_PIN_058
#define J9_D39  PIM_PIN_012
#define J9_D40  PIM_PIN_059
#define J9_D41  // Pin not routed
#define J9_D42  // Pin not routed
#define J9_D43  PIM_PIN_032
#define J9_D44  PIM_PIN_033
#define J9_D45  PIM_PIN_028
#define J9_D46  PIM_PIN_029
#define J9_D47  // Pin not routed
#define J9_D48  // Pin not routed
#define J9_D49  PIM_PIN_067
#define J9_D50  PIM_PIN_066
#define J9_D51  PIM_PIN_040
#define J9_D52  PIM_PIN_039
#define J9_D53  // Pin not routed
#define J9_D54  // Pin not routed
#define J9_D55  // Pin not routed
#define J9_D56  // Pin not routed
#define J9_D57  // Pin not routed
#define J9_D58  // Pin not routed
#define J9_D59  // Pin not routed
#define J9_D60  PIM_PIN_090
#define J9_D61  // Pin not routed
#define J9_D62  PIM_PIN_089
#define J9_D63  // Pin not routed
#define J9_D64  // Pin not routed
#define J9_D65  PIM_PIN_001
#define J9_D66  PIM_PIN_097
#define J9_D67  PIM_PIN_096
#define J9_D68  PIM_PIN_095
#define J9_D69  PIM_PIN_017
#define J9_D70  PIM_PIN_038
#define J9_D71  PIM_PIN_060
#define J9_D72  PIM_PIN_061
#define J9_D73  PIM_PIN_091
#define J9_D74  PIM_PIN_092
#define J9_D75  PIM_PIN_026
#define J9_D76  PIM_PIN_027
#define J9_D77  PIM_PIN_020
#define J9_D78  // Pin not routed
#define J9_D79  PIM_PIN_034
#define J9_D80  PIM_PIN_035
#define J9_D81  PIM_PIN_041
#define J9_D82  PIM_PIN_042
#define J9_D83  PIM_PIN_043
#define J9_D84  PIM_PIN_044
#define J9_D85  PIM_PIN_006
#define J9_D86  PIM_PIN_007
#define J9_D87  PIM_PIN_008
#define J9_D88  PIM_PIN_009
#define J9_D89  PIM_PIN_097
#define J9_D90  PIM_PIN_074
#define J9_D91  // Pin not routed
#define J9_D92  // Pin not routed
#define J9_D93  PIM_PIN_072
#define J9_D94  PIM_PIN_076
#define J9_D95  PIM_PIN_077
#define J9_D96  PIM_PIN_078
#define J9_D97  PIM_PIN_081
#define J9_D98  PIM_PIN_082
#define J9_D99  PIM_PIN_083
#define J9_D100 PIM_PIN_084
#define J9_D101 PIM_PIN_068
#define J9_D102 PIM_PIN_069
#define J9_D103 PIM_PIN_070
#define J9_D104 PIM_PIN_071
#define J9_D105 PIM_PIN_079
#define J9_D106 PIM_PIN_080
#define J9_D107 // Pin not routed
#define J9_D108 // Pin not routed
#define J9_D109 PIM_PIN_093
#define J9_D110 PIM_PIN_094
#define J9_D111 PIM_PIN_098
#define J9_D112 PIM_PIN_099
#define J9_D113 PIM_PIN_100
#define J9_D114 PIM_PIN_003
#define J9_D115 PIM_PIN_004
#define J9_D116 PIM_PIN_005
#define J9_D117 // Pin not routed
#define J9_D118 // Pin not routed
#define J9_D119 // Pin not routed
#define J9_D120 // Pin not routed

#define LED3    PIM_PIN_017
#define LED4    PIM_PIN_038
#define LED5    PIM_PIN_058
#define LED6    PIM_PIN_059
#define LED7    PIM_PIN_060
#define LED8    PIM_PIN_061
#define LED9    PIM_PIN_091
#define LED10   PIM_PIN_092

#ifdef __cplusplus
}
#endif

#endif    // _BOARD_H_
// ------------------------------------------------------------------------- END
