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
#define LEFT_CN_PIN_012 PA8
#define LEFT_CN_PIN_013 PA9
#define LEFT_CN_PIN_014 PA10
#define LEFT_CN_PIN_015 PA11
#define LEFT_CN_PIN_016 PA12
#define LEFT_CN_PIN_017 PA13
#define LEFT_CN_PIN_018 PA14
#define LEFT_CN_PIN_019 PA15
#define LEFT_CN_PIN_020     // Pin not routed.
#define LEFT_CN_PIN_021 PC17
#define LEFT_CN_PIN_022 PC18
#define LEFT_CN_PIN_023 PC19
#define LEFT_CN_PIN_024 PD0
#define LEFT_CN_PIN_025 PB9
#define LEFT_CN_PIN_026 PB16
#define LEFT_CN_PIN_027 PB17
#define LEFT_CN_PIN_028 PB19
#define LEFT_CN_PIN_029 PB20
#define LEFT_CN_PIN_030 PB0
#define LEFT_CN_PIN_031 PB1
#define LEFT_CN_PIN_032 PB2
#define LEFT_CN_PIN_033 PB3
#define LEFT_CN_PIN_034 PB4
#define LEFT_CN_PIN_035 PB5
#define LEFT_CN_PIN_036 PB6
#define LEFT_CN_PIN_037 PB7
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
#define LEFT_CN_PIN_054 PB21
#define LEFT_CN_PIN_055 PB22
#define LEFT_CN_PIN_056 PB18
#define LEFT_CN_PIN_057 PB23
#define LEFT_CN_PIN_058 PC10
#define LEFT_CN_PIN_059 PC11
#define LEFT_CN_PIN_060 PC12
#define LEFT_CN_PIN_061 PC13
#define LEFT_CN_PIN_062 PC16
#define LEFT_CN_PIN_063     // Pin not routed.
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
#define LEFT_CN_PIN_081     // Pin not routed.
#define LEFT_CN_PIN_082     // Pin not routed.
#define LEFT_CN_PIN_083     // Pin not routed.
#define LEFT_CN_PIN_084     // Pin not routed.
#define LEFT_CN_PIN_085 PC11
#define LEFT_CN_PIN_086 PC10
#define LEFT_CN_PIN_087 PC15
#define LEFT_CN_PIN_088 PC14
#define LEFT_CN_PIN_089 PB8
#define LEFT_CN_PIN_090 PA13
#define LEFT_CN_PIN_091 PE1
#define LEFT_CN_PIN_092 PE3
#define LEFT_CN_PIN_093 PE2
#define LEFT_CN_PIN_094 PA25
#define LEFT_CN_PIN_095 PE11
#define LEFT_CN_PIN_096 PC9
#define LEFT_CN_PIN_097 PC11
#define LEFT_CN_PIN_098 PC10
#define LEFT_CN_PIN_099 PC15
#define LEFT_CN_PIN_100 PC14
#define LEFT_CN_PIN_101 PA29
#define LEFT_CN_PIN_102 PA12
#define LEFT_CN_PIN_103 PE1
#define LEFT_CN_PIN_104 PE3
#define LEFT_CN_PIN_105 PE2
#define LEFT_CN_PIN_106 PA24
#define LEFT_CN_PIN_107 PE10
#define LEFT_CN_PIN_108 PC8
#define LEFT_CN_PIN_109 PC11
#define LEFT_CN_PIN_110 PC10
#define LEFT_CN_PIN_111 PC14
#define LEFT_CN_PIN_112 PC15
#define LEFT_CN_PIN_113 PA28
#define LEFT_CN_PIN_114 PA11
#define LEFT_CN_PIN_115 PE1
#define LEFT_CN_PIN_116 PE3
#define LEFT_CN_PIN_117 PE2
#define LEFT_CN_PIN_118 PA16
#define LEFT_CN_PIN_119 PE7
#define LEFT_CN_PIN_120 PB11
#define LEFT_CN_PIN_121 PC11
#define LEFT_CN_PIN_122 PC10
#define LEFT_CN_PIN_123 PE8
#define LEFT_CN_PIN_124 PE9
#define LEFT_CN_PIN_125 PA27
#define LEFT_CN_PIN_126 PA5
#define LEFT_CN_PIN_127 PE1
#define LEFT_CN_PIN_128 PE3
#define LEFT_CN_PIN_129 PE2
#define LEFT_CN_PIN_130 PE28
#define LEFT_CN_PIN_131 PE6
#define LEFT_CN_PIN_132 PB10
#define LEFT_CN_PIN_133 PC11
#define LEFT_CN_PIN_134 PC10
#define LEFT_CN_PIN_135 PE4
#define LEFT_CN_PIN_136 PE5
#define LEFT_CN_PIN_137 PA26
#define LEFT_CN_PIN_138 PA4
#define LEFT_CN_PIN_139 PE1
#define LEFT_CN_PIN_140 PE3
#define LEFT_CN_PIN_141 PE2
#define LEFT_CN_PIN_142 PE12
#define LEFT_CN_PIN_143 PE0
#define LEFT_CN_PIN_144 PA17
#define LEFT_CN_PIN_145 PA0
#define LEFT_CN_PIN_146 PD4
#define LEFT_CN_PIN_147 PD1
#define LEFT_CN_PIN_148 PA7
#define LEFT_CN_PIN_149 PA8
#define LEFT_CN_PIN_150 PA9
#define LEFT_CN_PIN_151 PA10
#define LEFT_CN_PIN_152 PA6
#define LEFT_CN_PIN_153 PA1
#define LEFT_CN_PIN_154 PA2
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
#define RIGHT_CN_PIN_001 PC0
#define RIGHT_CN_PIN_002 PC1
#define RIGHT_CN_PIN_003 PC2
#define RIGHT_CN_PIN_004 PC3
#define RIGHT_CN_PIN_005 PC4
#define RIGHT_CN_PIN_006 PC5
#define RIGHT_CN_PIN_007 PC6
#define RIGHT_CN_PIN_008 PC7
#define RIGHT_CN_PIN_009     // Pin not routed.
#define RIGHT_CN_PIN_010     // Pin not routed.
#define RIGHT_CN_PIN_011     // Pin not routed.
#define RIGHT_CN_PIN_012 PD0
#define RIGHT_CN_PIN_013 PD1
#define RIGHT_CN_PIN_014 PD2
#define RIGHT_CN_PIN_015 PD3
#define RIGHT_CN_PIN_016 PD4
#define RIGHT_CN_PIN_017 PD5
#define RIGHT_CN_PIN_018 PD6
#define RIGHT_CN_PIN_019 PD7
#define RIGHT_CN_PIN_020 PE0
#define RIGHT_CN_PIN_021 PE1
#define RIGHT_CN_PIN_022 PE2
#define RIGHT_CN_PIN_023 PE3
#define RIGHT_CN_PIN_024 PE4
#define RIGHT_CN_PIN_025 PE5
#define RIGHT_CN_PIN_026 PE6
#define RIGHT_CN_PIN_027 PE7
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
#define RIGHT_CN_PIN_102 PD14
#define RIGHT_CN_PIN_103 PD13
#define RIGHT_CN_PIN_104 PD12
#define RIGHT_CN_PIN_105 PD11
#define RIGHT_CN_PIN_106 PD10
#define RIGHT_CN_PIN_107 PD7
#define RIGHT_CN_PIN_108 PD6
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
#define RIGHT_CN_PIN_125     // Pin not routed.
#define RIGHT_CN_PIN_126     // Pin not routed.
#define RIGHT_CN_PIN_127     // Pin not routed.
#define RIGHT_CN_PIN_128     // Pin not routed.
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
#define RIGHT_CN_PIN_143     // Pin not routed.
#define RIGHT_CN_PIN_144     // Pin not routed.
#define RIGHT_CN_PIN_145 PE12
#define RIGHT_CN_PIN_146 PE11
#define RIGHT_CN_PIN_147 PE10
#define RIGHT_CN_PIN_148 PE9
#define RIGHT_CN_PIN_149 PE8
#define RIGHT_CN_PIN_150 PD15
#define RIGHT_CN_PIN_151 PD14
#define RIGHT_CN_PIN_152 PD13
#define RIGHT_CN_PIN_153 PD12
#define RIGHT_CN_PIN_154 PD11
#define RIGHT_CN_PIN_155 PD10
#define RIGHT_CN_PIN_156     // Pin not routed.
#define RIGHT_CN_PIN_157     // Pin not routed.
#define RIGHT_CN_PIN_158     // Pin not routed.
#define RIGHT_CN_PIN_159 PD2
#define RIGHT_CN_PIN_160 PD3
#define RIGHT_CN_PIN_161 PC15
#define RIGHT_CN_PIN_162 PC14
#define RIGHT_CN_PIN_163 PC13
#define RIGHT_CN_PIN_164 PC12
#define RIGHT_CN_PIN_165 PC11
#define RIGHT_CN_PIN_166 PC10
#define RIGHT_CN_PIN_167 PC9
#define RIGHT_CN_PIN_168 PC8

#define LCD_TFT_8BIT_CH0 PORT_B
#define LCD_TFT_CH0_8BIT_MASK 0x00FF

#define LCD_TFT_16BIT_CH0 PORT_B
#define LCD_TFT_16BIT_CH0_MASK 0x00FF

#define LCD_TFT_16BIT_CH1 PORT_C
#define LCD_TFT_16BIT_CH1_MASK 0x00FF

#ifdef __cplusplus
}
#endif

#endif // _MCU_CARD_H_
// ------------------------------------------------------------------------- END
