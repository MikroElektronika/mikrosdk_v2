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

#define BOARD_NAME "MCP3564 ADC Evaluation Board For PIC32 MCUs"

#include "mikrobus.h"
#include "pim_socket.h"

// Mapping
#define MIKROBUS_1 1
#define MIKROBUS_1_AN   PIM_PIN_025
#define MIKROBUS_1_RST  PIM_PIN_021
#define MIKROBUS_1_CS   PIM_PIN_047
#define MIKROBUS_1_SCK  PIM_PIN_055
#define MIKROBUS_1_MISO PIM_PIN_054
#define MIKROBUS_1_MOSI PIM_PIN_053
#define MIKROBUS_1_PWM  PIM_PIN_072
#define MIKROBUS_1_INT  PIM_PIN_018
#define MIKROBUS_1_RX   PIM_PIN_052
#define MIKROBUS_1_TX   PIM_PIN_051
#define MIKROBUS_1_SCL  PIM_PIN_057
#define MIKROBUS_1_SDA  PIM_PIN_056

#define J29_D1      PIM_PIN_023
#define J29_D2      PIM_PIN_052
#define J29_D3      PIM_PIN_055
#define J29_D4      PIM_PIN_051
#define J29_D5      PIM_PIN_054
#define J29_D6      PIM_PIN_057
#define J29_D7      PIM_PIN_053
#define J29_D8      PIM_PIN_056
#define J29_D9      // Pin not routed
#define J29_D10     // Pin not routed
#define J29_D11     PIM_PIN_025
#define J29_D12     PIM_PIN_024
#define J29_D13     PIM_PIN_022
#define J29_D14     PIM_PIN_021
#define J29_D15     // Pin not routed
#define J29_D16     // Pin not routed
#define J29_D17     PIM_PIN_019
#define J29_D18     PIM_PIN_018
#define J29_D19     PIM_PIN_047
#define J29_D20     PIM_PIN_048
#define J29_D21     // Pin not routed
#define J29_D22     // Pin not routed
#define J29_D23     // Pin not routed
#define J29_D24     // Pin not routed
#define J29_D25     // Pin not routed
#define J29_D26     // Pin not routed
#define J29_D27     PIM_PIN_090
#define J29_D28     PIM_PIN_087
#define J29_D29     PIM_PIN_089
#define J29_D30     PIM_PIN_088
#define J29_D31     // Pin not routed
#define J29_D32     // Pin not routed
#define J29_D33     PIM_PIN_014
#define J29_D34     PIM_PIN_049
#define J29_D35     PIM_PIN_010
#define J29_D36     PIM_PIN_050
#define J29_D37     PIM_PIN_011
#define J29_D38     PIM_PIN_058
#define J29_D39     PIM_PIN_012
#define J29_D40     PIM_PIN_059
#define J29_D41     // Pin not routed
#define J29_D42     // Pin not routed
#define J29_D43     PIM_PIN_032
#define J29_D44     PIM_PIN_033
#define J29_D45     PIM_PIN_028
#define J29_D46     PIM_PIN_029
#define J29_D47     // Pin not routed
#define J29_D48     // Pin not routed
#define J29_D49     PIM_PIN_067
#define J29_D50     PIM_PIN_066
#define J29_D51     PIM_PIN_040
#define J29_D52     PIM_PIN_039
#define J29_D53     // Pin not routed
#define J29_D54     // Pin not routed
#define J29_D55     // Pin not routed
#define J29_D56     // Pin not routed
#define J29_D57     // Pin not routed
#define J29_D58     // Pin not routed
#define J29_D59     // Pin not routed
#define J29_D60     PIM_PIN_090
#define J29_D61     // Pin not routed
#define J29_D62     PIM_PIN_089
#define J29_D63     // Pin not routed
#define J29_D64     // Pin not routed
#define J29_D65     PIM_PIN_001
#define J29_D66     PIM_PIN_097
#define J29_D67     PIM_PIN_096
#define J29_D68     PIM_PIN_095
#define J29_D69     PIM_PIN_017
#define J29_D70     PIM_PIN_038
#define J29_D71     PIM_PIN_060
#define J29_D72     PIM_PIN_061
#define J29_D73     PIM_PIN_091
#define J29_D74     PIM_PIN_092
#define J29_D75     PIM_PIN_026
#define J29_D76     PIM_PIN_027
#define J29_D77     PIM_PIN_020
#define J29_D78     // Pin not routed
#define J29_D79     PIM_PIN_034
#define J29_D80     PIM_PIN_035
#define J29_D81     PIM_PIN_041
#define J29_D82     PIM_PIN_042
#define J29_D83     PIM_PIN_043
#define J29_D84     PIM_PIN_044
#define J29_D85     PIM_PIN_006
#define J29_D86     PIM_PIN_007
#define J29_D87     PIM_PIN_008
#define J29_D88     PIM_PIN_009
#define J29_D89     PIM_PIN_097
#define J29_D90     PIM_PIN_074
#define J29_D91     // Pin not routed
#define J29_D92     // Pin not routed
#define J29_D93     PIM_PIN_072
#define J29_D94     PIM_PIN_076
#define J29_D95     PIM_PIN_077
#define J29_D96     PIM_PIN_078
#define J29_D97     PIM_PIN_081
#define J29_D98     PIM_PIN_082
#define J29_D99     PIM_PIN_083
#define J29_D100    PIM_PIN_084
#define J29_D101    PIM_PIN_068
#define J29_D102    PIM_PIN_069
#define J29_D103    PIM_PIN_070
#define J29_D104    PIM_PIN_071
#define J29_D105    PIM_PIN_079
#define J29_D106    PIM_PIN_080
#define J29_D107    // Pin not routed
#define J29_D108    // Pin not routed
#define J29_D109    PIM_PIN_093
#define J29_D110    PIM_PIN_094
#define J29_D111    PIM_PIN_098
#define J29_D112    PIM_PIN_099
#define J29_D113    PIM_PIN_100
#define J29_D114    PIM_PIN_003
#define J29_D115    PIM_PIN_004
#define J29_D116    PIM_PIN_005
#define J29_D117    // Pin not routed
#define J29_D118    // Pin not routed
#define J29_D119    // Pin not routed
#define J29_D120    // Pin not routed

#define J30_D1      PIM_PIN_023
#define J30_D2      PIM_PIN_052
#define J30_D3      PIM_PIN_055
#define J30_D4      PIM_PIN_051
#define J30_D5      PIM_PIN_054
#define J30_D6      PIM_PIN_057
#define J30_D7      PIM_PIN_053
#define J30_D8      PIM_PIN_056
#define J30_D9      // Pin not routed
#define J30_D10     // Pin not routed
#define J30_D11     PIM_PIN_025
#define J30_D12     PIM_PIN_024
#define J30_D13     PIM_PIN_022
#define J30_D14     PIM_PIN_021
#define J30_D15     // Pin not routed
#define J30_D16     // Pin not routed
#define J30_D17     PIM_PIN_019
#define J30_D18     PIM_PIN_018
#define J30_D19     PIM_PIN_047
#define J30_D20     PIM_PIN_048
#define J30_D21     // Pin not routed
#define J30_D22     // Pin not routed
#define J30_D23     // Pin not routed
#define J30_D24     // Pin not routed
#define J30_D25     // Pin not routed
#define J30_D26     // Pin not routed
#define J30_D27     PIM_PIN_090
#define J30_D28     PIM_PIN_087
#define J30_D29     PIM_PIN_089
#define J30_D30     PIM_PIN_088
#define J30_D31     // Pin not routed
#define J30_D32     // Pin not routed
#define J30_D33     PIM_PIN_014
#define J30_D34     PIM_PIN_049
#define J30_D35     PIM_PIN_010
#define J30_D36     PIM_PIN_050
#define J30_D37     PIM_PIN_011
#define J30_D38     PIM_PIN_058
#define J30_D39     PIM_PIN_012
#define J30_D40     PIM_PIN_059
#define J30_D41     // Pin not routed
#define J30_D42     // Pin not routed
#define J30_D43     PIM_PIN_032
#define J30_D44     PIM_PIN_033
#define J30_D45     PIM_PIN_028
#define J30_D46     PIM_PIN_029
#define J30_D47     // Pin not routed
#define J30_D48     // Pin not routed
#define J30_D49     PIM_PIN_067
#define J30_D50     PIM_PIN_066
#define J30_D51     PIM_PIN_040
#define J30_D52     PIM_PIN_039
#define J30_D53     // Pin not routed
#define J30_D54     // Pin not routed
#define J30_D55     // Pin not routed
#define J30_D56     // Pin not routed
#define J30_D57     // Pin not routed
#define J30_D58     // Pin not routed
#define J30_D59     // Pin not routed
#define J30_D60     PIM_PIN_090
#define J30_D61     // Pin not routed
#define J30_D62     PIM_PIN_089
#define J30_D63     // Pin not routed
#define J30_D64     // Pin not routed
#define J30_D65     PIM_PIN_001
#define J30_D66     PIM_PIN_097
#define J30_D67     PIM_PIN_096
#define J30_D68     PIM_PIN_095
#define J30_D69     PIM_PIN_017
#define J30_D70     PIM_PIN_038
#define J30_D71     PIM_PIN_060
#define J30_D72     PIM_PIN_061
#define J30_D73     PIM_PIN_091
#define J30_D74     PIM_PIN_092
#define J30_D75     PIM_PIN_026
#define J30_D76     PIM_PIN_027
#define J30_D77     PIM_PIN_020
#define J30_D78     // Pin not routed
#define J30_D79     PIM_PIN_034
#define J30_D80     PIM_PIN_035
#define J30_D81     PIM_PIN_041
#define J30_D82     PIM_PIN_042
#define J30_D83     PIM_PIN_043
#define J30_D84     PIM_PIN_044
#define J30_D85     PIM_PIN_006
#define J30_D86     PIM_PIN_007
#define J30_D87     PIM_PIN_008
#define J30_D88     PIM_PIN_009
#define J30_D89     PIM_PIN_097
#define J30_D90     PIM_PIN_074
#define J30_D91     // Pin not routed
#define J30_D92     // Pin not routed
#define J30_D93     PIM_PIN_072
#define J30_D94     PIM_PIN_076
#define J30_D95     PIM_PIN_077
#define J30_D96     PIM_PIN_078
#define J30_D97     PIM_PIN_081
#define J30_D98     PIM_PIN_082
#define J30_D99     PIM_PIN_083
#define J30_D100    PIM_PIN_084
#define J30_D101    PIM_PIN_068
#define J30_D102    PIM_PIN_069
#define J30_D103    PIM_PIN_070
#define J30_D104    PIM_PIN_071
#define J30_D105    PIM_PIN_079
#define J30_D106    PIM_PIN_080
#define J30_D107    // Pin not routed
#define J30_D108    // Pin not routed
#define J30_D109    PIM_PIN_093
#define J30_D110    PIM_PIN_094
#define J30_D111    PIM_PIN_098
#define J30_D112    PIM_PIN_099
#define J30_D113    PIM_PIN_100
#define J30_D114    PIM_PIN_003
#define J30_D115    PIM_PIN_004
#define J30_D116    PIM_PIN_005
#define J30_D117    // Pin not routed
#define J30_D118    // Pin not routed
#define J30_D119    // Pin not routed
#define J30_D120    // Pin not routed

#define LED_1       PIM_PIN_081
#define LED_2       PIM_PIN_082
#define LED_3       PIM_PIN_031
#define LED_5       PIM_PIN_032

#define BUTTON_2    PIM_PIN_071
#define BUTTON_3    PIM_PIN_079
#define BUTTON_4    PIM_PIN_080

#ifdef __cplusplus
}
#endif

#endif    // _BOARD_H_
// ------------------------------------------------------------------------- END
