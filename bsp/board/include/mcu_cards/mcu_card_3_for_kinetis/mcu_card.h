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
#define MCU_CARD_REV_MINOR (84)

#define NC HAL_PIN_NC

// Left connector
#define LEFT_CN_PIN_001 PA0
#define LEFT_CN_PIN_002 PA1
#define LEFT_CN_PIN_003 PA2
#define LEFT_CN_PIN_004 PA3
#define LEFT_CN_PIN_005 PA4
#define LEFT_CN_PIN_006     // Pin not routed.
#define LEFT_CN_PIN_007 PA6
#define LEFT_CN_PIN_008     // Pin not routed.
#define LEFT_CN_PIN_009     // Pin not routed.
#define LEFT_CN_PIN_010     // Pin not routed.
#define LEFT_CN_PIN_011     // Pin not routed.
#define LEFT_CN_PIN_012     // Pin not routed.
#define LEFT_CN_PIN_013 PA9
#define LEFT_CN_PIN_014 PA10
#define LEFT_CN_PIN_015 PA11
#define LEFT_CN_PIN_016     // Pin not routed.
#define LEFT_CN_PIN_017     // Pin not routed.
#define LEFT_CN_PIN_018     // Pin not routed.
#define LEFT_CN_PIN_019     // Pin not routed.
#define LEFT_CN_PIN_020     // Pin not routed.
#define LEFT_CN_PIN_021 PA2
#define LEFT_CN_PIN_022 PA4
#define LEFT_CN_PIN_023 PA1
#define LEFT_CN_PIN_024 PA3
#define LEFT_CN_PIN_025 PA6
#define LEFT_CN_PIN_026 PA9
#define LEFT_CN_PIN_027 PA10
#define LEFT_CN_PIN_028 PB10
#define LEFT_CN_PIN_029 PB6
#define LEFT_CN_PIN_030 PD0
#define LEFT_CN_PIN_031 PD1
#define LEFT_CN_PIN_032 PD2
#define LEFT_CN_PIN_033 PD3
#define LEFT_CN_PIN_034 PD4
#define LEFT_CN_PIN_035 PD5
#define LEFT_CN_PIN_036 PD6
#define LEFT_CN_PIN_037 PD7
#define LEFT_CN_PIN_038 PD8
#define LEFT_CN_PIN_039 PD9
#define LEFT_CN_PIN_040 PD10
#define LEFT_CN_PIN_041 PD11
#define LEFT_CN_PIN_042 PD12
#define LEFT_CN_PIN_043 PD13
#define LEFT_CN_PIN_044 PD14
#define LEFT_CN_PIN_045 PD15
#define LEFT_CN_PIN_046     // Pin not routed.
#define LEFT_CN_PIN_047     // Pin not routed.
#define LEFT_CN_PIN_048     // Pin not routed.
#define LEFT_CN_PIN_049     // Pin not routed.
#define LEFT_CN_PIN_050     // Pin not routed.
#define LEFT_CN_PIN_051     // Pin not routed.
#define LEFT_CN_PIN_052     // Pin not routed.
#define LEFT_CN_PIN_053     // Pin not routed.
#define LEFT_CN_PIN_054 PB7
#define LEFT_CN_PIN_055 PB8
#define LEFT_CN_PIN_056 PB5
#define LEFT_CN_PIN_057 PB9
#define LEFT_CN_PIN_058 PE24
#define LEFT_CN_PIN_059 PE25
#define LEFT_CN_PIN_060 PC12
#define LEFT_CN_PIN_061 PC13
#define LEFT_CN_PIN_062 PB20
#define LEFT_CN_PIN_063     // Pin not routed.
#define LEFT_CN_PIN_064     // Pin not routed.
#define LEFT_CN_PIN_065     // Pin not routed.
#define LEFT_CN_PIN_066     // Pin not routed.
#define LEFT_CN_PIN_067     // Pin not routed.
#define LEFT_CN_PIN_068     // Pin not routed.
#define LEFT_CN_PIN_069     // Pin not routed.
#define LEFT_CN_PIN_070     // Pin not routed.
#define LEFT_CN_PIN_071     // Pin not routed.
#define LEFT_CN_PIN_072     // Pin not routed.
#define LEFT_CN_PIN_073     // Pin not routed.
#define LEFT_CN_PIN_074     // Pin not routed.
#define LEFT_CN_PIN_075     // Pin not routed.
#define LEFT_CN_PIN_076     // Pin not routed.
#define LEFT_CN_PIN_077 PA24
#define LEFT_CN_PIN_078 PA25
#define LEFT_CN_PIN_079 PA26
#define LEFT_CN_PIN_080 PA27
#define LEFT_CN_PIN_081 PA28
#define LEFT_CN_PIN_082 PA29
#define LEFT_CN_PIN_083     // Pin not routed.
#define LEFT_CN_PIN_084     // Pin not routed.
#define LEFT_CN_PIN_085 PC11
#define LEFT_CN_PIN_086 PC10
#define LEFT_CN_PIN_087 PC15
#define LEFT_CN_PIN_088 PC14
#define LEFT_CN_PIN_089 PE30
#define LEFT_CN_PIN_090 PE11
#define LEFT_CN_PIN_091 PB22
#define LEFT_CN_PIN_092 PB23
#define LEFT_CN_PIN_093 PB21
#define LEFT_CN_PIN_094 PE23
#define LEFT_CN_PIN_095 PA28
#define LEFT_CN_PIN_096 PB4
#define LEFT_CN_PIN_097 PC11
#define LEFT_CN_PIN_098 PC10
#define LEFT_CN_PIN_099 PC17
#define LEFT_CN_PIN_100 PC16
#define LEFT_CN_PIN_101 PE29
#define LEFT_CN_PIN_102 PE10
#define LEFT_CN_PIN_103 PB22
#define LEFT_CN_PIN_104 PB23
#define LEFT_CN_PIN_105 PB21
#define LEFT_CN_PIN_106 PE22
#define LEFT_CN_PIN_107 PA27
#define LEFT_CN_PIN_108 PB3
#define LEFT_CN_PIN_109 PC11
#define LEFT_CN_PIN_110 PC10
#define LEFT_CN_PIN_111 PE16
#define LEFT_CN_PIN_112 PE17
#define LEFT_CN_PIN_113 PE28
#define LEFT_CN_PIN_114 PE7
#define LEFT_CN_PIN_115 PB22
#define LEFT_CN_PIN_116 PB23
#define LEFT_CN_PIN_117 PB21
#define LEFT_CN_PIN_118 PC19
#define LEFT_CN_PIN_119 PA26
#define LEFT_CN_PIN_120 PB2
#define LEFT_CN_PIN_121 PE25
#define LEFT_CN_PIN_122 PE24
#define LEFT_CN_PIN_123 PC4
#define LEFT_CN_PIN_124 PC3
#define LEFT_CN_PIN_125 PE27
#define LEFT_CN_PIN_126 PE6
#define LEFT_CN_PIN_127 PB16
#define LEFT_CN_PIN_128 PB17
#define LEFT_CN_PIN_129 PB11
#define LEFT_CN_PIN_130 PC18
#define LEFT_CN_PIN_131 PE19
#define LEFT_CN_PIN_132 PB1
#define LEFT_CN_PIN_133 PE25
#define LEFT_CN_PIN_134 PE24
#define LEFT_CN_PIN_135 PE20
#define LEFT_CN_PIN_136 PE21
#define LEFT_CN_PIN_137 PA11
#define LEFT_CN_PIN_138 PE5
#define LEFT_CN_PIN_139 PB16
#define LEFT_CN_PIN_140 PB17
#define LEFT_CN_PIN_141 PB11
#define LEFT_CN_PIN_142 PA29
#define LEFT_CN_PIN_143 PE18
#define LEFT_CN_PIN_144 PB0
#define LEFT_CN_PIN_145 PC9
#define LEFT_CN_PIN_146 PC8
#define LEFT_CN_PIN_147 PC7
#define LEFT_CN_PIN_148 PC6
#define LEFT_CN_PIN_149 PC5
#define LEFT_CN_PIN_150 PC4
#define LEFT_CN_PIN_151 PC3
#define LEFT_CN_PIN_152 PC2
#define LEFT_CN_PIN_153 PC1
#define LEFT_CN_PIN_154 PC0
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
#define RIGHT_CN_PIN_001 PB0
#define RIGHT_CN_PIN_002 PB1
#define RIGHT_CN_PIN_003 PB2
#define RIGHT_CN_PIN_004 PB3
#define RIGHT_CN_PIN_005 PB4
#define RIGHT_CN_PIN_006 PB5
#define RIGHT_CN_PIN_007 PB6
#define RIGHT_CN_PIN_008 PB7
#define RIGHT_CN_PIN_009     // Pin not routed.
#define RIGHT_CN_PIN_010     // Pin not routed.
#define RIGHT_CN_PIN_011     // Pin not routed.
#define RIGHT_CN_PIN_012 PB16
#define RIGHT_CN_PIN_013 PB17
#define RIGHT_CN_PIN_014 PB18
#define RIGHT_CN_PIN_015 PB19
#define RIGHT_CN_PIN_016 PB20
#define RIGHT_CN_PIN_017 PB21
#define RIGHT_CN_PIN_018 PB22
#define RIGHT_CN_PIN_019 PB23
#define RIGHT_CN_PIN_020 PC0
#define RIGHT_CN_PIN_021 PC1
#define RIGHT_CN_PIN_022 PC2
#define RIGHT_CN_PIN_023 PC3
#define RIGHT_CN_PIN_024 PC4
#define RIGHT_CN_PIN_025 PC5
#define RIGHT_CN_PIN_026 PC6
#define RIGHT_CN_PIN_027 PC7
#define RIGHT_CN_PIN_028 PC16
#define RIGHT_CN_PIN_029 PC17
#define RIGHT_CN_PIN_030 PC18
#define RIGHT_CN_PIN_031 PC19
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
#define RIGHT_CN_PIN_043 PB19
#define RIGHT_CN_PIN_044 PB18
#define RIGHT_CN_PIN_045 PD0
#define RIGHT_CN_PIN_046 PD1
#define RIGHT_CN_PIN_047 PD2
#define RIGHT_CN_PIN_048 PD3
#define RIGHT_CN_PIN_049 PD4
#define RIGHT_CN_PIN_050 PD5
#define RIGHT_CN_PIN_051 PD6
#define RIGHT_CN_PIN_052 PD7
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
#define RIGHT_CN_PIN_069 PE0
#define RIGHT_CN_PIN_070 PE1
#define RIGHT_CN_PIN_071 PE2
#define RIGHT_CN_PIN_072 PE3
#define RIGHT_CN_PIN_073 PE4
#define RIGHT_CN_PIN_074 PE5
#define RIGHT_CN_PIN_075 PE6
#define RIGHT_CN_PIN_076 PE7
#define RIGHT_CN_PIN_077 PE16
#define RIGHT_CN_PIN_078 PE17
#define RIGHT_CN_PIN_079 PE18
#define RIGHT_CN_PIN_080 PE19
#define RIGHT_CN_PIN_081     // Pin not routed.
#define RIGHT_CN_PIN_082     // Pin not routed.
#define RIGHT_CN_PIN_083 PE22
#define RIGHT_CN_PIN_084 PE23
#define RIGHT_CN_PIN_085     // Pin not routed.
#define RIGHT_CN_PIN_086 PE30
#define RIGHT_CN_PIN_087 PE29
#define RIGHT_CN_PIN_088 PE28
#define RIGHT_CN_PIN_089 PE27
#define RIGHT_CN_PIN_090     // Pin not routed.
#define RIGHT_CN_PIN_091 PE25
#define RIGHT_CN_PIN_092 PE24
#define RIGHT_CN_PIN_093     // Pin not routed.
#define RIGHT_CN_PIN_094     // Pin not routed.
#define RIGHT_CN_PIN_095 PE13
#define RIGHT_CN_PIN_096 PE12
#define RIGHT_CN_PIN_097 PE11
#define RIGHT_CN_PIN_098 PE10
#define RIGHT_CN_PIN_099 PE9
#define RIGHT_CN_PIN_100 PE8
#define RIGHT_CN_PIN_101     // Pin not routed.
#define RIGHT_CN_PIN_102 PE4
#define RIGHT_CN_PIN_103 PE3
#define RIGHT_CN_PIN_104 PE2
#define RIGHT_CN_PIN_105 PE1
#define RIGHT_CN_PIN_106 PE0
#define RIGHT_CN_PIN_107 PE12
#define RIGHT_CN_PIN_108 PE13
#define RIGHT_CN_PIN_109     // Pin not routed.
#define RIGHT_CN_PIN_110     // Pin not routed.
#define RIGHT_CN_PIN_111     // Pin not routed.
#define RIGHT_CN_PIN_112     // Pin not routed.
#define RIGHT_CN_PIN_113     // Pin not routed.
#define RIGHT_CN_PIN_114     // Pin not routed.
#define RIGHT_CN_PIN_115     // Pin not routed.
#define RIGHT_CN_PIN_116     // Pin not routed.
#define RIGHT_CN_PIN_117 PD15
#define RIGHT_CN_PIN_118 PD14
#define RIGHT_CN_PIN_119 PD13
#define RIGHT_CN_PIN_120 PD12
#define RIGHT_CN_PIN_121 PD11
#define RIGHT_CN_PIN_122 PD10
#define RIGHT_CN_PIN_123 PD9
#define RIGHT_CN_PIN_124 PD8
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
#define RIGHT_CN_PIN_142 PC15
#define RIGHT_CN_PIN_143 PC14
#define RIGHT_CN_PIN_144 PC13
#define RIGHT_CN_PIN_145 PC12
#define RIGHT_CN_PIN_146 PC11
#define RIGHT_CN_PIN_147 PC10
#define RIGHT_CN_PIN_148 PC9
#define RIGHT_CN_PIN_149 PC8
#define RIGHT_CN_PIN_150     // Pin not routed.
#define RIGHT_CN_PIN_151     // Pin not routed.
#define RIGHT_CN_PIN_152     // Pin not routed.
#define RIGHT_CN_PIN_153     // Pin not routed.
#define RIGHT_CN_PIN_154     // Pin not routed.
#define RIGHT_CN_PIN_155     // Pin not routed.
#define RIGHT_CN_PIN_156     // Pin not routed.
#define RIGHT_CN_PIN_157     // Pin not routed.
#define RIGHT_CN_PIN_158     // Pin not routed.
#define RIGHT_CN_PIN_159 PE9
#define RIGHT_CN_PIN_160 PE8
#define RIGHT_CN_PIN_161     // Pin not routed.
#define RIGHT_CN_PIN_162     // Pin not routed.
#define RIGHT_CN_PIN_163     // Pin not routed.
#define RIGHT_CN_PIN_164     // Pin not routed.
#define RIGHT_CN_PIN_165 PB11
#define RIGHT_CN_PIN_166 PB10
#define RIGHT_CN_PIN_167 PB9
#define RIGHT_CN_PIN_168 PB8

#define LCD_TFT_8BIT_CH0 PORT_D
#define LCD_TFT_CH0_8BIT_MASK 0x00FF

#define LCD_TFT_16BIT_CH0 PORT_D
#define LCD_TFT_16BIT_CH0_MASK 0xFFFF

#define LCD_TFT_16BIT_CH1 HAL_PORT_NC
#define LCD_TFT_16BIT_CH1_MASK 0x0000

#ifdef __cplusplus
}
#endif

#endif // _MCU_CARD_H_
// ------------------------------------------------------------------------- END
