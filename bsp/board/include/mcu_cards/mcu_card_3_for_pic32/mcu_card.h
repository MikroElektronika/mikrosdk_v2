/****************************************************************************
**
** Copyright (C) 2024 MikroElektronika d.o.o.
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
 * @file  mcu_card.h
 * @brief MCU card connections mapping.
 */

#ifndef _MCU_CARD_H_
#define _MCU_CARD_H_

#ifdef __cplusplus
extern "C"{
#endif

#include "hal_target.h"

// Hardware revision number
#define MCU_CARD_REV_MAJOR (0)
#define MCU_CARD_REV_MINOR (81)

#define NC HAL_PIN_NC

// Left connector
#define LEFT_CN_PIN_001 PA0
#define LEFT_CN_PIN_002 PA1
#define LEFT_CN_PIN_003 PA2
#define LEFT_CN_PIN_004 PA3
#define LEFT_CN_PIN_005 PA4
#define LEFT_CN_PIN_006 PA5
#define LEFT_CN_PIN_007 PA6
#define LEFT_CN_PIN_008 PA7
#define LEFT_CN_PIN_009     // Pin not routed.
#define LEFT_CN_PIN_010     // Pin not routed.
#define LEFT_CN_PIN_011     // Pin not routed.
#define LEFT_CN_PIN_012     // Pin not routed.
#define LEFT_CN_PIN_013     // Pin not routed.
#define LEFT_CN_PIN_014     // Pin not routed.
#define LEFT_CN_PIN_015     // Pin not routed.
#define LEFT_CN_PIN_016     // Pin not routed.
#define LEFT_CN_PIN_017     // Pin not routed.
#define LEFT_CN_PIN_018 PA14
#define LEFT_CN_PIN_019 PA15
#define LEFT_CN_PIN_020     // Pin not routed.
#define LEFT_CN_PIN_021 PJ4
#define LEFT_CN_PIN_022 PJ5
#define LEFT_CN_PIN_023 PA5
#define LEFT_CN_PIN_024 PA4
#define LEFT_CN_PIN_025 PK1
#define LEFT_CN_PIN_026 PJ7
#define LEFT_CN_PIN_027 PK7
#define LEFT_CN_PIN_028 PC4
#define LEFT_CN_PIN_029 PC3
#define LEFT_CN_PIN_030 PE0
#define LEFT_CN_PIN_031 PE1
#define LEFT_CN_PIN_032 PE2
#define LEFT_CN_PIN_033 PE3
#define LEFT_CN_PIN_034 PE4
#define LEFT_CN_PIN_035 PE5
#define LEFT_CN_PIN_036 PE6
#define LEFT_CN_PIN_037 PE7
#define LEFT_CN_PIN_038 PG0
#define LEFT_CN_PIN_039 PG1
#define LEFT_CN_PIN_040 PF1
#define LEFT_CN_PIN_041 PF0
#define LEFT_CN_PIN_042 PD12
#define LEFT_CN_PIN_043 PD13
#define LEFT_CN_PIN_044 PD2
#define LEFT_CN_PIN_045 PD3
#define LEFT_CN_PIN_046     // Pin not routed.
#define LEFT_CN_PIN_047     // Pin not routed.
#define LEFT_CN_PIN_048     // Pin not routed.
#define LEFT_CN_PIN_049     // Pin not routed.
#define LEFT_CN_PIN_050     // Pin not routed.
#define LEFT_CN_PIN_051     // Pin not routed.
#define LEFT_CN_PIN_052     // Pin not routed.
#define LEFT_CN_PIN_053     // Pin not routed.
#define LEFT_CN_PIN_054 PK2
#define LEFT_CN_PIN_055 PB4
#define LEFT_CN_PIN_056 PB5
#define LEFT_CN_PIN_057 PK3
#define LEFT_CN_PIN_058 PA14
#define LEFT_CN_PIN_059 PA15
#define LEFT_CN_PIN_060 PD15
#define LEFT_CN_PIN_061 PB2
#define LEFT_CN_PIN_062 PB1
#define LEFT_CN_PIN_063 PB0
#define LEFT_CN_PIN_064     // Pin not routed.
#define LEFT_CN_PIN_065     // Pin not routed.
#define LEFT_CN_PIN_066     // Pin not routed.
#define LEFT_CN_PIN_067     // Pin not routed.
#define LEFT_CN_PIN_068     // Pin not routed.
#define LEFT_CN_PIN_069 PB0
#define LEFT_CN_PIN_070 PB1
#define LEFT_CN_PIN_071 PB2
#define LEFT_CN_PIN_072 PB3
#define LEFT_CN_PIN_073 PB4
#define LEFT_CN_PIN_074 PB5
#define LEFT_CN_PIN_075 PB6
#define LEFT_CN_PIN_076 PB7
#define LEFT_CN_PIN_077 PB8
#define LEFT_CN_PIN_078 PB9
#define LEFT_CN_PIN_079 PB10
#define LEFT_CN_PIN_080 PB11
#define LEFT_CN_PIN_081 PB12
#define LEFT_CN_PIN_082 PB13
#define LEFT_CN_PIN_083 PB14
#define LEFT_CN_PIN_084 PB15
#define LEFT_CN_PIN_085 PA15
#define LEFT_CN_PIN_086 PA14
#define LEFT_CN_PIN_087 PC2
#define LEFT_CN_PIN_088 PG6
#define LEFT_CN_PIN_089 PD7
#define LEFT_CN_PIN_090 PB3
#define LEFT_CN_PIN_091 PG7
#define LEFT_CN_PIN_092 PG8
#define LEFT_CN_PIN_093 PD1
#define LEFT_CN_PIN_094 PJ0
#define LEFT_CN_PIN_095 PK0
#define LEFT_CN_PIN_096 PD14
#define LEFT_CN_PIN_097 PA15
#define LEFT_CN_PIN_098 PA14
#define LEFT_CN_PIN_099 PC2
#define LEFT_CN_PIN_100 PG6
#define LEFT_CN_PIN_101 PD10
#define LEFT_CN_PIN_102 PC1
#define LEFT_CN_PIN_103 PG7
#define LEFT_CN_PIN_104 PG8
#define LEFT_CN_PIN_105 PD1
#define LEFT_CN_PIN_106 PJ3
#define LEFT_CN_PIN_107 PJ2
#define LEFT_CN_PIN_108 PH6
#define LEFT_CN_PIN_109 PA3
#define LEFT_CN_PIN_110 PA2
#define LEFT_CN_PIN_111 PF4
#define LEFT_CN_PIN_112 PF5
#define LEFT_CN_PIN_113 PD9
#define LEFT_CN_PIN_114 PB10
#define LEFT_CN_PIN_115 PG7
#define LEFT_CN_PIN_116 PG8
#define LEFT_CN_PIN_117 PD1
#define LEFT_CN_PIN_118 PH10
#define LEFT_CN_PIN_119 PH9
#define LEFT_CN_PIN_120 PB13
#define LEFT_CN_PIN_121 PA3
#define LEFT_CN_PIN_122 PA2
#define LEFT_CN_PIN_123 PF8
#define LEFT_CN_PIN_124 PF2
#define LEFT_CN_PIN_125 PG9
#define LEFT_CN_PIN_126 PB9
#define LEFT_CN_PIN_127 PG7
#define LEFT_CN_PIN_128 PG8
#define LEFT_CN_PIN_129 PD1
#define LEFT_CN_PIN_130 PH1
#define LEFT_CN_PIN_131 PH0
#define LEFT_CN_PIN_132 PB12
#define LEFT_CN_PIN_133 PA3
#define LEFT_CN_PIN_134 PA2
#define LEFT_CN_PIN_135 PB14
#define LEFT_CN_PIN_136 PB15
#define LEFT_CN_PIN_137 PD0
#define LEFT_CN_PIN_138 PB8
#define LEFT_CN_PIN_139 PG7
#define LEFT_CN_PIN_140 PG8
#define LEFT_CN_PIN_141 PD1
#define LEFT_CN_PIN_142 PH3
#define LEFT_CN_PIN_143 PH2
#define LEFT_CN_PIN_144 PB11
#define LEFT_CN_PIN_145 PJ15
#define LEFT_CN_PIN_146 PE9
#define LEFT_CN_PIN_147 PJ6
#define LEFT_CN_PIN_148 PA7
#define LEFT_CN_PIN_149 PE8
#define LEFT_CN_PIN_150 PK4
#define LEFT_CN_PIN_151 PK5
#define LEFT_CN_PIN_152 PK6
#define LEFT_CN_PIN_153 PH11
#define LEFT_CN_PIN_154 PH7
#define LEFT_CN_PIN_155     // Pin not routed.
#define LEFT_CN_PIN_156     // Pin not routed.
#define LEFT_CN_PIN_157     // Pin not routed.
#define LEFT_CN_PIN_158     // Pin not routed.
#define LEFT_CN_PIN_159     // Pin not routed.
#define LEFT_CN_PIN_160     // Pin not routed.
#define LEFT_CN_PIN_161     // Pin not routed.
#define LEFT_CN_PIN_162     // Pin not routed.
#define LEFT_CN_PIN_163     // Pin not routed.
#define LEFT_CN_PIN_164     // Pin not routed.
#define LEFT_CN_PIN_165     // Pin not routed.
#define LEFT_CN_PIN_166     // Pin not routed.
#define LEFT_CN_PIN_167     // Pin not routed.
#define LEFT_CN_PIN_168     // Pin not routed.

// Right connector
#define RIGHT_CN_PIN_001     // Pin not routed.
#define RIGHT_CN_PIN_002 PC1
#define RIGHT_CN_PIN_003 PC2
#define RIGHT_CN_PIN_004 PC3
#define RIGHT_CN_PIN_005 PC4
#define RIGHT_CN_PIN_006     // Pin not routed.
#define RIGHT_CN_PIN_007     // Pin not routed.
#define RIGHT_CN_PIN_008     // Pin not routed.
#define RIGHT_CN_PIN_009     // Pin not routed.
#define RIGHT_CN_PIN_010     // Pin not routed.
#define RIGHT_CN_PIN_011     // Pin not routed.
#define RIGHT_CN_PIN_012 PD0
#define RIGHT_CN_PIN_013 PD1
#define RIGHT_CN_PIN_014 PD2
#define RIGHT_CN_PIN_015 PD3
#define RIGHT_CN_PIN_016 PD4
#define RIGHT_CN_PIN_017 PD5
#define RIGHT_CN_PIN_018     // Pin not routed.
#define RIGHT_CN_PIN_019 PD7
#define RIGHT_CN_PIN_020 PE0
#define RIGHT_CN_PIN_021 PE1
#define RIGHT_CN_PIN_022 PE2
#define RIGHT_CN_PIN_023 PE3
#define RIGHT_CN_PIN_024 PE4
#define RIGHT_CN_PIN_025 PE5
#define RIGHT_CN_PIN_026 PE6
#define RIGHT_CN_PIN_027 PE7
#define RIGHT_CN_PIN_028 PF0
#define RIGHT_CN_PIN_029 PF1
#define RIGHT_CN_PIN_030 PF2
#define RIGHT_CN_PIN_031 PF3
#define RIGHT_CN_PIN_032 PF4
#define RIGHT_CN_PIN_033 PF5
#define RIGHT_CN_PIN_034     // Pin not routed.
#define RIGHT_CN_PIN_035     // Pin not routed.
#define RIGHT_CN_PIN_036     // Pin not routed.
#define RIGHT_CN_PIN_037     // Pin not routed.
#define RIGHT_CN_PIN_038     // Pin not routed.
#define RIGHT_CN_PIN_039     // Pin not routed.
#define RIGHT_CN_PIN_040     // Pin not routed.
#define RIGHT_CN_PIN_041     // Pin not routed.
#define RIGHT_CN_PIN_042     // Pin not routed.
#define RIGHT_CN_PIN_043 PD4
#define RIGHT_CN_PIN_044 PD5
#define RIGHT_CN_PIN_045 PG0
#define RIGHT_CN_PIN_046 PG1
#define RIGHT_CN_PIN_047     // Pin not routed.
#define RIGHT_CN_PIN_048     // Pin not routed.
#define RIGHT_CN_PIN_049     // Pin not routed.
#define RIGHT_CN_PIN_050     // Pin not routed.
#define RIGHT_CN_PIN_051 PG6
#define RIGHT_CN_PIN_052 PG7
#define RIGHT_CN_PIN_053 PH0
#define RIGHT_CN_PIN_054 PH1
#define RIGHT_CN_PIN_055 PH2
#define RIGHT_CN_PIN_056 PH3
#define RIGHT_CN_PIN_057     // Pin not routed.
#define RIGHT_CN_PIN_058     // Pin not routed.
#define RIGHT_CN_PIN_059 PH6
#define RIGHT_CN_PIN_060 PH7
#define RIGHT_CN_PIN_061 PG12
#define RIGHT_CN_PIN_062 PG13
#define RIGHT_CN_PIN_063 PG14
#define RIGHT_CN_PIN_064 PA6
#define RIGHT_CN_PIN_065     // Pin not routed.
#define RIGHT_CN_PIN_066     // Pin not routed.
#define RIGHT_CN_PIN_067     // Pin not routed.
#define RIGHT_CN_PIN_068     // Pin not routed.
#define RIGHT_CN_PIN_069 PK0
#define RIGHT_CN_PIN_070 PK1
#define RIGHT_CN_PIN_071 PK2
#define RIGHT_CN_PIN_072 PK3
#define RIGHT_CN_PIN_073 PK4
#define RIGHT_CN_PIN_074 PK5
#define RIGHT_CN_PIN_075 PK6
#define RIGHT_CN_PIN_076 PK7
#define RIGHT_CN_PIN_077 PJ0
#define RIGHT_CN_PIN_078     // Pin not routed.
#define RIGHT_CN_PIN_079 PJ2
#define RIGHT_CN_PIN_080 PJ3
#define RIGHT_CN_PIN_081 PJ4
#define RIGHT_CN_PIN_082 PJ5
#define RIGHT_CN_PIN_083 PJ6
#define RIGHT_CN_PIN_084 PJ7
#define RIGHT_CN_PIN_085 PJ15
#define RIGHT_CN_PIN_086 PJ14
#define RIGHT_CN_PIN_087 PJ13
#define RIGHT_CN_PIN_088 PJ12
#define RIGHT_CN_PIN_089     // Pin not routed.
#define RIGHT_CN_PIN_090 PJ10
#define RIGHT_CN_PIN_091     // Pin not routed.
#define RIGHT_CN_PIN_092     // Pin not routed.
#define RIGHT_CN_PIN_093     // Pin not routed.
#define RIGHT_CN_PIN_094     // Pin not routed.
#define RIGHT_CN_PIN_095     // Pin not routed.
#define RIGHT_CN_PIN_096     // Pin not routed.
#define RIGHT_CN_PIN_097     // Pin not routed.
#define RIGHT_CN_PIN_098     // Pin not routed.
#define RIGHT_CN_PIN_099     // Pin not routed.
#define RIGHT_CN_PIN_100     // Pin not routed.
#define RIGHT_CN_PIN_101     // Pin not routed.
#define RIGHT_CN_PIN_102 PJ10
#define RIGHT_CN_PIN_103 PJ12
#define RIGHT_CN_PIN_104 PF12
#define RIGHT_CN_PIN_105 PJ14
#define RIGHT_CN_PIN_106 PF13
#define RIGHT_CN_PIN_107 PH14
#define RIGHT_CN_PIN_108 PH15
#define RIGHT_CN_PIN_109 PH15
#define RIGHT_CN_PIN_110 PH14
#define RIGHT_CN_PIN_111     // Pin not routed.
#define RIGHT_CN_PIN_112 PH12
#define RIGHT_CN_PIN_113 PH11
#define RIGHT_CN_PIN_114 PH10
#define RIGHT_CN_PIN_115 PH9
#define RIGHT_CN_PIN_116     // Pin not routed.
#define RIGHT_CN_PIN_117 PG15
#define RIGHT_CN_PIN_118 PG14
#define RIGHT_CN_PIN_119 PG13
#define RIGHT_CN_PIN_120 PG12
#define RIGHT_CN_PIN_121     // Pin not routed.
#define RIGHT_CN_PIN_122     // Pin not routed.
#define RIGHT_CN_PIN_123 PG9
#define RIGHT_CN_PIN_124 PG8
#define RIGHT_CN_PIN_125 PH6
#define RIGHT_CN_PIN_126 PB13
#define RIGHT_CN_PIN_127 PB12
#define RIGHT_CN_PIN_128 PB11
#define RIGHT_CN_PIN_129     // Pin not routed.
#define RIGHT_CN_PIN_130     // Pin not routed.
#define RIGHT_CN_PIN_131     // Pin not routed.
#define RIGHT_CN_PIN_132     // Pin not routed.
#define RIGHT_CN_PIN_133     // Pin not routed.
#define RIGHT_CN_PIN_134     // Pin not routed.
#define RIGHT_CN_PIN_135     // Pin not routed.
#define RIGHT_CN_PIN_136 PF13
#define RIGHT_CN_PIN_137 PF12
#define RIGHT_CN_PIN_138     // Pin not routed.
#define RIGHT_CN_PIN_139     // Pin not routed.
#define RIGHT_CN_PIN_140     // Pin not routed.
#define RIGHT_CN_PIN_141 PF8
#define RIGHT_CN_PIN_142     // Pin not routed.
#define RIGHT_CN_PIN_143     // Pin not routed.
#define RIGHT_CN_PIN_144     // Pin not routed.
#define RIGHT_CN_PIN_145     // Pin not routed.
#define RIGHT_CN_PIN_146     // Pin not routed.
#define RIGHT_CN_PIN_147     // Pin not routed.
#define RIGHT_CN_PIN_148 PE9
#define RIGHT_CN_PIN_149 PE8
#define RIGHT_CN_PIN_150 PD15
#define RIGHT_CN_PIN_151 PD14
#define RIGHT_CN_PIN_152 PD13
#define RIGHT_CN_PIN_153 PD12
#define RIGHT_CN_PIN_154     // Pin not routed.
#define RIGHT_CN_PIN_155 PD10
#define RIGHT_CN_PIN_156 PD9
#define RIGHT_CN_PIN_157     // Pin not routed.
#define RIGHT_CN_PIN_158     // Pin not routed.
#define RIGHT_CN_PIN_159 PG6
#define RIGHT_CN_PIN_160 PC2
#define RIGHT_CN_PIN_161     // Pin not routed.
#define RIGHT_CN_PIN_162     // Pin not routed.
#define RIGHT_CN_PIN_163     // Pin not routed.
#define RIGHT_CN_PIN_164     // Pin not routed.
#define RIGHT_CN_PIN_165     // Pin not routed.
#define RIGHT_CN_PIN_166     // Pin not routed.
#define RIGHT_CN_PIN_167     // Pin not routed.
#define RIGHT_CN_PIN_168     // Pin not routed.

#define LCD_TFT_8BIT_CH0 PORT_E
#define LCD_TFT_CH0_8BIT_MASK 0xFF

#define LCD_TFT_16BIT_CH0 HAL_PORT_NC
#define LCD_TFT_16BIT_CH0_MASK 0xFF

#define LCD_TFT_16BIT_CH1 HAL_PORT_NC
#define LCD_TFT_16BIT_CH1_MASK 0x00

#ifdef __cplusplus
}
#endif

#endif // _MCU_CARD_H_
// ------------------------------------------------------------------------- END
