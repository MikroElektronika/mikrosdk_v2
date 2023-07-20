/****************************************************************************
**
** Copyright (C) 2023 MikroElektronika d.o.o.
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
 * @file  pim_socket.h
 * @brief PIM socket MCU card pin mapping.
 */

#ifndef _PIM_SOCKET_H_
#define _PIM_SOCKET_H_

#ifdef __cplusplus
extern "C"{
#endif

#include "mcu_card.h"
#include "hal_target.h"

// Left connector
#define PIM_PIN_001 LEFT_CN_PIN_001
#define PIM_PIN_002 LEFT_CN_PIN_002
#define PIM_PIN_003 LEFT_CN_PIN_003
#define PIM_PIN_004 LEFT_CN_PIN_004
#define PIM_PIN_005 LEFT_CN_PIN_005
#define PIM_PIN_006 LEFT_CN_PIN_006
#define PIM_PIN_007 LEFT_CN_PIN_007
#define PIM_PIN_008 LEFT_CN_PIN_008
#define PIM_PIN_009 LEFT_CN_PIN_009
#define PIM_PIN_010 LEFT_CN_PIN_010
#define PIM_PIN_011 LEFT_CN_PIN_011
#define PIM_PIN_012 LEFT_CN_PIN_012
#define PIM_PIN_013 LEFT_CN_PIN_013
#define PIM_PIN_014 LEFT_CN_PIN_014
#define PIM_PIN_015 LEFT_CN_PIN_015
#define PIM_PIN_016 LEFT_CN_PIN_016
#define PIM_PIN_017 LEFT_CN_PIN_017
#define PIM_PIN_018 LEFT_CN_PIN_018
#define PIM_PIN_019 LEFT_CN_PIN_019
#define PIM_PIN_020 LEFT_CN_PIN_020
#define PIM_PIN_021 LEFT_CN_PIN_021
#define PIM_PIN_022 LEFT_CN_PIN_022
#define PIM_PIN_023 LEFT_CN_PIN_023
#define PIM_PIN_024 LEFT_CN_PIN_024
#define PIM_PIN_025 LEFT_CN_PIN_025

// Down connector
#define PIM_PIN_026 DOWN_CN_PIN_026
#define PIM_PIN_027 DOWN_CN_PIN_027
#define PIM_PIN_028 DOWN_CN_PIN_028
#define PIM_PIN_029 DOWN_CN_PIN_029
#define PIM_PIN_030 DOWN_CN_PIN_030
#define PIM_PIN_031 DOWN_CN_PIN_031
#define PIM_PIN_032 DOWN_CN_PIN_032
#define PIM_PIN_033 DOWN_CN_PIN_033
#define PIM_PIN_034 DOWN_CN_PIN_034
#define PIM_PIN_035 DOWN_CN_PIN_035
#define PIM_PIN_036 DOWN_CN_PIN_036
#define PIM_PIN_037 DOWN_CN_PIN_037
#define PIM_PIN_038 DOWN_CN_PIN_038
#define PIM_PIN_039 DOWN_CN_PIN_039
#define PIM_PIN_040 DOWN_CN_PIN_040
#define PIM_PIN_041 DOWN_CN_PIN_041
#define PIM_PIN_042 DOWN_CN_PIN_042
#define PIM_PIN_043 DOWN_CN_PIN_043
#define PIM_PIN_044 DOWN_CN_PIN_044
#define PIM_PIN_045 DOWN_CN_PIN_045
#define PIM_PIN_046 DOWN_CN_PIN_046
#define PIM_PIN_047 DOWN_CN_PIN_047
#define PIM_PIN_048 DOWN_CN_PIN_048
#define PIM_PIN_049 DOWN_CN_PIN_049
#define PIM_PIN_050 DOWN_CN_PIN_050

// Right connector
#define PIM_PIN_051 RIGHT_CN_PIN_051
#define PIM_PIN_052 RIGHT_CN_PIN_052
#define PIM_PIN_053 RIGHT_CN_PIN_053
#define PIM_PIN_054 RIGHT_CN_PIN_054
#define PIM_PIN_055 RIGHT_CN_PIN_055
#define PIM_PIN_056 RIGHT_CN_PIN_056
#define PIM_PIN_057 RIGHT_CN_PIN_057
#define PIM_PIN_058 RIGHT_CN_PIN_058
#define PIM_PIN_059 RIGHT_CN_PIN_059
#define PIM_PIN_060 RIGHT_CN_PIN_060
#define PIM_PIN_061 RIGHT_CN_PIN_061
#define PIM_PIN_062 RIGHT_CN_PIN_062
#define PIM_PIN_063 RIGHT_CN_PIN_063
#define PIM_PIN_064 RIGHT_CN_PIN_064
#define PIM_PIN_065 RIGHT_CN_PIN_065
#define PIM_PIN_066 RIGHT_CN_PIN_066
#define PIM_PIN_067 RIGHT_CN_PIN_067
#define PIM_PIN_068 RIGHT_CN_PIN_068
#define PIM_PIN_069 RIGHT_CN_PIN_069
#define PIM_PIN_070 RIGHT_CN_PIN_070
#define PIM_PIN_071 RIGHT_CN_PIN_071
#define PIM_PIN_072 RIGHT_CN_PIN_072
#define PIM_PIN_073 RIGHT_CN_PIN_073
#define PIM_PIN_074 RIGHT_CN_PIN_074
#define PIM_PIN_075 RIGHT_CN_PIN_075

// Up connector
#define PIM_PIN_076 UP_CN_PIN_076
#define PIM_PIN_077 UP_CN_PIN_077
#define PIM_PIN_078 UP_CN_PIN_078
#define PIM_PIN_079 UP_CN_PIN_079
#define PIM_PIN_080 UP_CN_PIN_080
#define PIM_PIN_081 UP_CN_PIN_081
#define PIM_PIN_082 UP_CN_PIN_082
#define PIM_PIN_083 UP_CN_PIN_083
#define PIM_PIN_084 UP_CN_PIN_084
#define PIM_PIN_085 UP_CN_PIN_085
#define PIM_PIN_086 UP_CN_PIN_086
#define PIM_PIN_087 UP_CN_PIN_087
#define PIM_PIN_088 UP_CN_PIN_088
#define PIM_PIN_089 UP_CN_PIN_089
#define PIM_PIN_090 UP_CN_PIN_090
#define PIM_PIN_091 UP_CN_PIN_091
#define PIM_PIN_092 UP_CN_PIN_092
#define PIM_PIN_093 UP_CN_PIN_093
#define PIM_PIN_094 UP_CN_PIN_094
#define PIM_PIN_095 UP_CN_PIN_095
#define PIM_PIN_096 UP_CN_PIN_096
#define PIM_PIN_097 UP_CN_PIN_097
#define PIM_PIN_098 UP_CN_PIN_098
#define PIM_PIN_099 UP_CN_PIN_099
#define PIM_PIN_100 UP_CN_PIN_100

#ifdef __cplusplus
}
#endif

#endif // _PIM_SOCKET_H_
// ------------------------------------------------------------------------- END
