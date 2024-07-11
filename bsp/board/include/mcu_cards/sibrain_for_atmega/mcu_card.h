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

#define PORT_MASK_LOW  (uint8_t)0xF
#define PORT_MASK_HIGH (uint8_t)0xF0

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
#define LEFT_CN_PIN_012 PB0
#define LEFT_CN_PIN_013 PB1
#define LEFT_CN_PIN_014 PB2
#define LEFT_CN_PIN_015 PB3
#define LEFT_CN_PIN_016 PB4
#define LEFT_CN_PIN_017 PB5
#define LEFT_CN_PIN_018 PB6
#define LEFT_CN_PIN_019 PB7
#define LEFT_CN_PIN_020     // Pin not routed.
#define LEFT_CN_PIN_021     // Pin not routed.
#define LEFT_CN_PIN_022     // Pin not routed.
#define LEFT_CN_PIN_023     // Pin not routed.
#define LEFT_CN_PIN_024     // Pin not routed.
#define LEFT_CN_PIN_025 PD7
#define LEFT_CN_PIN_026 PD6
#define LEFT_CN_PIN_027 PD5
#define LEFT_CN_PIN_028 PD4
#define LEFT_CN_PIN_029 PD3
#define LEFT_CN_PIN_030 PA0
#define LEFT_CN_PIN_031 PA1
#define LEFT_CN_PIN_032 PA2
#define LEFT_CN_PIN_033 PA3
#define LEFT_CN_PIN_034 PA4
#define LEFT_CN_PIN_035 PA5
#define LEFT_CN_PIN_036 PA6
#define LEFT_CN_PIN_037 PA7
#define LEFT_CN_PIN_038 PC0
#define LEFT_CN_PIN_039 PC1
#define LEFT_CN_PIN_040 PC2
#define LEFT_CN_PIN_041 PC3
#define LEFT_CN_PIN_042 PC4
#define LEFT_CN_PIN_043 PC5
#define LEFT_CN_PIN_044 PC6
#define LEFT_CN_PIN_045 PC7
#define LEFT_CN_PIN_046     // Pin not routed.
#define LEFT_CN_PIN_047     // Pin not routed.
#define LEFT_CN_PIN_048     // Pin not routed.
#define LEFT_CN_PIN_049     // Pin not routed.
#define LEFT_CN_PIN_050     // Pin not routed.
#define LEFT_CN_PIN_051     // Pin not routed.
#define LEFT_CN_PIN_052     // Pin not routed.
#define LEFT_CN_PIN_053     // Pin not routed.
#define LEFT_CN_PIN_054 PB0
#define LEFT_CN_PIN_055 PJ1
#define LEFT_CN_PIN_056 PB7
#define LEFT_CN_PIN_057 PJ0
#define LEFT_CN_PIN_058 PE4
#define LEFT_CN_PIN_059 PE5
#define LEFT_CN_PIN_060 PD1
#define LEFT_CN_PIN_061 PD0
#define LEFT_CN_PIN_062 PD2
#define LEFT_CN_PIN_063     // Pin not routed.
#define LEFT_CN_PIN_064     // Pin not routed.
#define LEFT_CN_PIN_065     // Pin not routed.
#define LEFT_CN_PIN_066     // Pin not routed.
#define LEFT_CN_PIN_067     // Pin not routed.
#define LEFT_CN_PIN_068     // Pin not routed.
#define LEFT_CN_PIN_069 PC0
#define LEFT_CN_PIN_070 PC1
#define LEFT_CN_PIN_071 PC2
#define LEFT_CN_PIN_072 PC3
#define LEFT_CN_PIN_073 PC4
#define LEFT_CN_PIN_074 PC5
#define LEFT_CN_PIN_075 PC6
#define LEFT_CN_PIN_076 PC7
#define LEFT_CN_PIN_077 PD0
#define LEFT_CN_PIN_078 PD1
#define LEFT_CN_PIN_079 PD2
#define LEFT_CN_PIN_080 PD3
#define LEFT_CN_PIN_081 PD4
#define LEFT_CN_PIN_082 PD5
#define LEFT_CN_PIN_083 PD6
#define LEFT_CN_PIN_084 PD7
#define LEFT_CN_PIN_085 PE5
#define LEFT_CN_PIN_086 PE4
#define LEFT_CN_PIN_087 PE1
#define LEFT_CN_PIN_088 PE0
#define LEFT_CN_PIN_089 PH7
#define LEFT_CN_PIN_090 PB7
#define LEFT_CN_PIN_091 PB2
#define LEFT_CN_PIN_092 PB3
#define LEFT_CN_PIN_093 PB1
#define LEFT_CN_PIN_094 PE2
#define LEFT_CN_PIN_095 PE3
#define LEFT_CN_PIN_096 PF5
#define LEFT_CN_PIN_097 PE5
#define LEFT_CN_PIN_098 PE4
#define LEFT_CN_PIN_099 PE1
#define LEFT_CN_PIN_100 PE0
#define LEFT_CN_PIN_101 PH6
#define LEFT_CN_PIN_102 PB7
#define LEFT_CN_PIN_103 PB2
#define LEFT_CN_PIN_104 PB3
#define LEFT_CN_PIN_105 PB1
#define LEFT_CN_PIN_106 PE6
#define LEFT_CN_PIN_107 PE7
#define LEFT_CN_PIN_108 PF3
#define LEFT_CN_PIN_109 PE5
#define LEFT_CN_PIN_110 PE4
#define LEFT_CN_PIN_111 PE1
#define LEFT_CN_PIN_112 PE0
#define LEFT_CN_PIN_113 PH5
#define LEFT_CN_PIN_114 PB6
#define LEFT_CN_PIN_115 PB2
#define LEFT_CN_PIN_116 PB3
#define LEFT_CN_PIN_117 PB1
#define LEFT_CN_PIN_118 PH3
#define LEFT_CN_PIN_119 PH2
#define LEFT_CN_PIN_120 PF2
#define LEFT_CN_PIN_121 PE5
#define LEFT_CN_PIN_122 PE4
#define LEFT_CN_PIN_123 PE1
#define LEFT_CN_PIN_124 PE0
#define LEFT_CN_PIN_125 PH4
#define LEFT_CN_PIN_126 PB5
#define LEFT_CN_PIN_127 PB2
#define LEFT_CN_PIN_128 PB3
#define LEFT_CN_PIN_129 PB1
#define LEFT_CN_PIN_130 PH1
#define LEFT_CN_PIN_131 PH0
#define LEFT_CN_PIN_132 PF1
#define LEFT_CN_PIN_133 PE5
#define LEFT_CN_PIN_134 PE4
#define LEFT_CN_PIN_135 PE1
#define LEFT_CN_PIN_136 PE0
#define LEFT_CN_PIN_137 PD1
#define LEFT_CN_PIN_138 PB4
#define LEFT_CN_PIN_139 PB2
#define LEFT_CN_PIN_140 PB3
#define LEFT_CN_PIN_141 PB1
#define LEFT_CN_PIN_142 PG1
#define LEFT_CN_PIN_143 PG0
#define LEFT_CN_PIN_144 PF0
#define LEFT_CN_PIN_145     // Pin not routed.
#define LEFT_CN_PIN_146     // Pin not routed.
#define LEFT_CN_PIN_147     // Pin not routed.
#define LEFT_CN_PIN_148     // Pin not routed.
#define LEFT_CN_PIN_149     // Pin not routed.
#define LEFT_CN_PIN_150     // Pin not routed.
#define LEFT_CN_PIN_151     // Pin not routed.
#define LEFT_CN_PIN_152     // Pin not routed.
#define LEFT_CN_PIN_153     // Pin not routed.
#define LEFT_CN_PIN_154     // Pin not routed.
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
#define RIGHT_CN_PIN_001 PE0
#define RIGHT_CN_PIN_002 PE1
#define RIGHT_CN_PIN_003 PE2
#define RIGHT_CN_PIN_004 PE3
#define RIGHT_CN_PIN_005 PE4
#define RIGHT_CN_PIN_006 PE5
#define RIGHT_CN_PIN_007 PE6
#define RIGHT_CN_PIN_008 PE7
#define RIGHT_CN_PIN_009     // Pin not routed.
#define RIGHT_CN_PIN_010     // Pin not routed.
#define RIGHT_CN_PIN_011     // Pin not routed.
#define RIGHT_CN_PIN_012 PG0
#define RIGHT_CN_PIN_013 PG1
#define RIGHT_CN_PIN_014 PG2
#define RIGHT_CN_PIN_015 PG3
#define RIGHT_CN_PIN_016 PG4
#define RIGHT_CN_PIN_017     // Pin not routed.
#define RIGHT_CN_PIN_018     // Pin not routed.
#define RIGHT_CN_PIN_019     // Pin not routed.
#define RIGHT_CN_PIN_020     // Pin not routed.
#define RIGHT_CN_PIN_021     // Pin not routed.
#define RIGHT_CN_PIN_022     // Pin not routed.
#define RIGHT_CN_PIN_023     // Pin not routed.
#define RIGHT_CN_PIN_024     // Pin not routed.
#define RIGHT_CN_PIN_025     // Pin not routed.
#define RIGHT_CN_PIN_026     // Pin not routed.
#define RIGHT_CN_PIN_027     // Pin not routed.
#define RIGHT_CN_PIN_028     // Pin not routed.
#define RIGHT_CN_PIN_029     // Pin not routed.
#define RIGHT_CN_PIN_030     // Pin not routed.
#define RIGHT_CN_PIN_031     // Pin not routed.
#define RIGHT_CN_PIN_032     // Pin not routed.
#define RIGHT_CN_PIN_033     // Pin not routed.
#define RIGHT_CN_PIN_034     // Pin not routed.
#define RIGHT_CN_PIN_035     // Pin not routed.
#define RIGHT_CN_PIN_036     // Pin not routed.
#define RIGHT_CN_PIN_037     // Pin not routed.
#define RIGHT_CN_PIN_038     // Pin not routed.
#define RIGHT_CN_PIN_039     // Pin not routed.
#define RIGHT_CN_PIN_040     // Pin not routed.
#define RIGHT_CN_PIN_041     // Pin not routed.
#define RIGHT_CN_PIN_042     // Pin not routed.
#define RIGHT_CN_PIN_043     // Pin not routed.
#define RIGHT_CN_PIN_044     // Pin not routed.
#define RIGHT_CN_PIN_045     // Pin not routed.
#define RIGHT_CN_PIN_046     // Pin not routed.
#define RIGHT_CN_PIN_047     // Pin not routed.
#define RIGHT_CN_PIN_048     // Pin not routed.
#define RIGHT_CN_PIN_049     // Pin not routed.
#define RIGHT_CN_PIN_050     // Pin not routed.
#define RIGHT_CN_PIN_051     // Pin not routed.
#define RIGHT_CN_PIN_052     // Pin not routed.
#define RIGHT_CN_PIN_053     // Pin not routed.
#define RIGHT_CN_PIN_054     // Pin not routed.
#define RIGHT_CN_PIN_055     // Pin not routed.
#define RIGHT_CN_PIN_056     // Pin not routed.
#define RIGHT_CN_PIN_057     // Pin not routed.
#define RIGHT_CN_PIN_058     // Pin not routed.
#define RIGHT_CN_PIN_059     // Pin not routed.
#define RIGHT_CN_PIN_060     // Pin not routed.
#define RIGHT_CN_PIN_061     // Pin not routed.
#define RIGHT_CN_PIN_062     // Pin not routed.
#define RIGHT_CN_PIN_063     // Pin not routed.
#define RIGHT_CN_PIN_064     // Pin not routed.
#define RIGHT_CN_PIN_065     // Pin not routed.
#define RIGHT_CN_PIN_066     // Pin not routed.
#define RIGHT_CN_PIN_067     // Pin not routed.
#define RIGHT_CN_PIN_068     // Pin not routed.
#define RIGHT_CN_PIN_069     // Pin not routed.
#define RIGHT_CN_PIN_070     // Pin not routed.
#define RIGHT_CN_PIN_071     // Pin not routed.
#define RIGHT_CN_PIN_072     // Pin not routed.
#define RIGHT_CN_PIN_073     // Pin not routed.
#define RIGHT_CN_PIN_074     // Pin not routed.
#define RIGHT_CN_PIN_075     // Pin not routed.
#define RIGHT_CN_PIN_076     // Pin not routed.
#define RIGHT_CN_PIN_077     // Pin not routed.
#define RIGHT_CN_PIN_078     // Pin not routed.
#define RIGHT_CN_PIN_079     // Pin not routed.
#define RIGHT_CN_PIN_080     // Pin not routed.
#define RIGHT_CN_PIN_081     // Pin not routed.
#define RIGHT_CN_PIN_082     // Pin not routed.
#define RIGHT_CN_PIN_083     // Pin not routed.
#define RIGHT_CN_PIN_084     // Pin not routed.
#define RIGHT_CN_PIN_085     // Pin not routed.
#define RIGHT_CN_PIN_086     // Pin not routed.
#define RIGHT_CN_PIN_087     // Pin not routed.
#define RIGHT_CN_PIN_088     // Pin not routed.
#define RIGHT_CN_PIN_089     // Pin not routed.
#define RIGHT_CN_PIN_090     // Pin not routed.
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
#define RIGHT_CN_PIN_102     // Pin not routed.
#define RIGHT_CN_PIN_103     // Pin not routed.
#define RIGHT_CN_PIN_104     // Pin not routed.
#define RIGHT_CN_PIN_105     // Pin not routed.
#define RIGHT_CN_PIN_106     // Pin not routed.
#define RIGHT_CN_PIN_107     // Pin not routed.
#define RIGHT_CN_PIN_108     // Pin not routed.
#define RIGHT_CN_PIN_109     // Pin not routed.
#define RIGHT_CN_PIN_110     // Pin not routed.
#define RIGHT_CN_PIN_111     // Pin not routed.
#define RIGHT_CN_PIN_112     // Pin not routed.
#define RIGHT_CN_PIN_113     // Pin not routed.
#define RIGHT_CN_PIN_114     // Pin not routed.
#define RIGHT_CN_PIN_115     // Pin not routed.
#define RIGHT_CN_PIN_116     // Pin not routed.
#define RIGHT_CN_PIN_117     // Pin not routed.
#define RIGHT_CN_PIN_118     // Pin not routed.
#define RIGHT_CN_PIN_119     // Pin not routed.
#define RIGHT_CN_PIN_120     // Pin not routed.
#define RIGHT_CN_PIN_121     // Pin not routed.
#define RIGHT_CN_PIN_122     // Pin not routed.
#define RIGHT_CN_PIN_123     // Pin not routed.
#define RIGHT_CN_PIN_124     // Pin not routed.
#define RIGHT_CN_PIN_125 PF3
#define RIGHT_CN_PIN_126 PF2
#define RIGHT_CN_PIN_127 PF1
#define RIGHT_CN_PIN_128 PF0
#define RIGHT_CN_PIN_129     // Pin not routed.
#define RIGHT_CN_PIN_130     // Pin not routed.
#define RIGHT_CN_PIN_131     // Pin not routed.
#define RIGHT_CN_PIN_132     // Pin not routed.
#define RIGHT_CN_PIN_133     // Pin not routed.
#define RIGHT_CN_PIN_134     // Pin not routed.
#define RIGHT_CN_PIN_135     // Pin not routed.
#define RIGHT_CN_PIN_136     // Pin not routed.
#define RIGHT_CN_PIN_137     // Pin not routed.
#define RIGHT_CN_PIN_138     // Pin not routed.
#define RIGHT_CN_PIN_139     // Pin not routed.
#define RIGHT_CN_PIN_140     // Pin not routed.
#define RIGHT_CN_PIN_141     // Pin not routed.
#define RIGHT_CN_PIN_142     // Pin not routed.
#define RIGHT_CN_PIN_143 PJ6
#define RIGHT_CN_PIN_144 PJ5
#define RIGHT_CN_PIN_145 PJ4
#define RIGHT_CN_PIN_146 PJ3
#define RIGHT_CN_PIN_147 PJ2
#define RIGHT_CN_PIN_148 PJ1
#define RIGHT_CN_PIN_149 PJ0
#define RIGHT_CN_PIN_150 PH7
#define RIGHT_CN_PIN_151 PH6
#define RIGHT_CN_PIN_152 PH5
#define RIGHT_CN_PIN_153 PH4
#define RIGHT_CN_PIN_154 PH3
#define RIGHT_CN_PIN_155 PH2
#define RIGHT_CN_PIN_156 PH1
#define RIGHT_CN_PIN_157 PH0
#define RIGHT_CN_PIN_158     // Pin not routed.
#define RIGHT_CN_PIN_159 PE0
#define RIGHT_CN_PIN_160 PE1
#define RIGHT_CN_PIN_161 PF7
#define RIGHT_CN_PIN_162 PF6
#define RIGHT_CN_PIN_163 PF5
#define RIGHT_CN_PIN_164 PF4
#define RIGHT_CN_PIN_165 PF3
#define RIGHT_CN_PIN_166 PF2
#define RIGHT_CN_PIN_167 PF1
#define RIGHT_CN_PIN_168 PF0

#define LCD_TFT_8BIT_CH0 PORT_A
#define LCD_TFT_CH0_8BIT_MASK 0xFF

#define LCD_TFT_16BIT_CH0 PORT_A
#define LCD_TFT_16BIT_CH0_MASK 0xFF

#define LCD_TFT_16BIT_CH1 PORT_C
#define LCD_TFT_16BIT_CH1_MASK 0xFF

#ifdef __cplusplus
}
#endif

#endif // _MCU_CARD_H_
// ------------------------------------------------------------------------- END
