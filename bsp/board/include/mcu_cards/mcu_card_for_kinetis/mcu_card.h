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
#define MCU_CARD_REV_MINOR (85)

#define NC HAL_PIN_NC

// Left connector
#define LEFT_CN_PIN_001 GPIO_PA0
#define LEFT_CN_PIN_002 GPIO_PA1
#define LEFT_CN_PIN_003 GPIO_PA2
#define LEFT_CN_PIN_004 GPIO_PA3
#define LEFT_CN_PIN_005 GPIO_PA4
#define LEFT_CN_PIN_006     // Pin not routed.
#define LEFT_CN_PIN_007     // Pin not routed.
#define LEFT_CN_PIN_008     // Pin not routed.
#define LEFT_CN_PIN_009     // Pin not routed.
#define LEFT_CN_PIN_010     // Pin not routed.
#define LEFT_CN_PIN_011     // Pin not routed.
#define LEFT_CN_PIN_012     // Pin not routed.
#define LEFT_CN_PIN_013     // Pin not routed.
#define LEFT_CN_PIN_014 GPIO_PA10
#define LEFT_CN_PIN_015 GPIO_PA11
#define LEFT_CN_PIN_016     // Pin not routed.
#define LEFT_CN_PIN_017     // Pin not routed.
#define LEFT_CN_PIN_018     // Pin not routed.
#define LEFT_CN_PIN_019     // Pin not routed.
#define LEFT_CN_PIN_020     // Pin not routed.
#define LEFT_CN_PIN_021     // Pin not routed.
#define LEFT_CN_PIN_022     // Pin not routed.
#define LEFT_CN_PIN_023     // Pin not routed.
#define LEFT_CN_PIN_024     // Pin not routed.
#define LEFT_CN_PIN_025 GPIO_PC10
#define LEFT_CN_PIN_026 GPIO_PC11
#define LEFT_CN_PIN_027 GPIO_PC12
#define LEFT_CN_PIN_028 GPIO_PC13
#define LEFT_CN_PIN_029 GPIO_PC14
#define LEFT_CN_PIN_030 GPIO_PD0
#define LEFT_CN_PIN_031 GPIO_PD1
#define LEFT_CN_PIN_032 GPIO_PD2
#define LEFT_CN_PIN_033 GPIO_PD3
#define LEFT_CN_PIN_034 GPIO_PD4
#define LEFT_CN_PIN_035 GPIO_PD5
#define LEFT_CN_PIN_036 GPIO_PD6
#define LEFT_CN_PIN_037 GPIO_PD7
#define LEFT_CN_PIN_038 GPIO_PD8
#define LEFT_CN_PIN_039 GPIO_PD9
#define LEFT_CN_PIN_040 GPIO_PD10
#define LEFT_CN_PIN_041 GPIO_PD11
#define LEFT_CN_PIN_042 GPIO_PD12
#define LEFT_CN_PIN_043 GPIO_PD13
#define LEFT_CN_PIN_044 GPIO_PD14
#define LEFT_CN_PIN_045 GPIO_PD15
#define LEFT_CN_PIN_046     // Pin not routed.
#define LEFT_CN_PIN_047     // Pin not routed.
#define LEFT_CN_PIN_048     // Pin not routed.
#define LEFT_CN_PIN_049     // Pin not routed.
#define LEFT_CN_PIN_050     // Pin not routed.
#define LEFT_CN_PIN_051     // Pin not routed.
#define LEFT_CN_PIN_052     // Pin not routed.
#define LEFT_CN_PIN_053     // Pin not routed.
#define LEFT_CN_PIN_054 GPIO_PC8
#define LEFT_CN_PIN_055 GPIO_PC9
#define LEFT_CN_PIN_056 GPIO_PB12
#define LEFT_CN_PIN_057 GPIO_PB13
#define LEFT_CN_PIN_058 GPIO_PE24
#define LEFT_CN_PIN_059 GPIO_PE25
#define LEFT_CN_PIN_060 GPIO_PA11
#define LEFT_CN_PIN_061 GPIO_PA4
#define LEFT_CN_PIN_062 GPIO_PA10
#define LEFT_CN_PIN_063     // Pin not routed.
#define LEFT_CN_PIN_064     // Pin not routed.
#define LEFT_CN_PIN_065     // Pin not routed.
#define LEFT_CN_PIN_066     // Pin not routed.
#define LEFT_CN_PIN_067     // Pin not routed.
#define LEFT_CN_PIN_068     // Pin not routed.
#define LEFT_CN_PIN_069     // Pin not routed.
#define LEFT_CN_PIN_070     // Pin not routed.
#define LEFT_CN_PIN_071 GPIO_PB2
#define LEFT_CN_PIN_072 GPIO_PB3
#define LEFT_CN_PIN_073     // Pin not routed.
#define LEFT_CN_PIN_074     // Pin not routed.
#define LEFT_CN_PIN_075 GPIO_PB6
#define LEFT_CN_PIN_076 GPIO_PB7
#define LEFT_CN_PIN_077 GPIO_PB8
#define LEFT_CN_PIN_078 GPIO_PB9
#define LEFT_CN_PIN_079 GPIO_PB10
#define LEFT_CN_PIN_080 GPIO_PB11
#define LEFT_CN_PIN_081 GPIO_PB12
#define LEFT_CN_PIN_082 GPIO_PB13
#define LEFT_CN_PIN_083     // Pin not routed.
#define LEFT_CN_PIN_084     // Pin not routed.
#define LEFT_CN_PIN_085 GPIO_PB3
#define LEFT_CN_PIN_086 GPIO_PB2
#define LEFT_CN_PIN_087 GPIO_PD9
#define LEFT_CN_PIN_088 GPIO_PD8
#define LEFT_CN_PIN_089 GPIO_PC15
#define LEFT_CN_PIN_090 GPIO_PB12
#define LEFT_CN_PIN_091 GPIO_PB22
#define LEFT_CN_PIN_092 GPIO_PB23
#define LEFT_CN_PIN_093 GPIO_PB21
#define LEFT_CN_PIN_094 GPIO_PD12
#define LEFT_CN_PIN_095 GPIO_PD7
#define LEFT_CN_PIN_096 GPIO_PD6
#define LEFT_CN_PIN_097 GPIO_PB3
#define LEFT_CN_PIN_098 GPIO_PB2
#define LEFT_CN_PIN_099 GPIO_PD9
#define LEFT_CN_PIN_100 GPIO_PD8
#define LEFT_CN_PIN_101 GPIO_PC7
#define LEFT_CN_PIN_102 GPIO_PC8
#define LEFT_CN_PIN_103 GPIO_PB22
#define LEFT_CN_PIN_104 GPIO_PB23
#define LEFT_CN_PIN_105 GPIO_PB21
#define LEFT_CN_PIN_106 GPIO_PD11
#define LEFT_CN_PIN_107 GPIO_PC0
#define LEFT_CN_PIN_108 GPIO_PB11
#define LEFT_CN_PIN_109 GPIO_PB3
#define LEFT_CN_PIN_110 GPIO_PB2
#define LEFT_CN_PIN_111 GPIO_PC4
#define LEFT_CN_PIN_112 GPIO_PC3
#define LEFT_CN_PIN_113 GPIO_PC19
#define LEFT_CN_PIN_114 GPIO_PC1
#define LEFT_CN_PIN_115 GPIO_PB22
#define LEFT_CN_PIN_116 GPIO_PB23
#define LEFT_CN_PIN_117 GPIO_PB21
#define LEFT_CN_PIN_118 GPIO_PC2
#define LEFT_CN_PIN_119 GPIO_PD10
#define LEFT_CN_PIN_120 GPIO_PB10
#define LEFT_CN_PIN_121 GPIO_PB3
#define LEFT_CN_PIN_122 GPIO_PB2
#define LEFT_CN_PIN_123 GPIO_PB17
#define LEFT_CN_PIN_124 GPIO_PB16
#define LEFT_CN_PIN_125 GPIO_PB9
#define LEFT_CN_PIN_126 GPIO_PE5
#define LEFT_CN_PIN_127 GPIO_PB22
#define LEFT_CN_PIN_128 GPIO_PB23
#define LEFT_CN_PIN_129 GPIO_PB21
#define LEFT_CN_PIN_130 GPIO_PB8
#define LEFT_CN_PIN_131 GPIO_PC6
#define LEFT_CN_PIN_132 GPIO_PB7
#define LEFT_CN_PIN_133 GPIO_PB3
#define LEFT_CN_PIN_134 GPIO_PB2
#define LEFT_CN_PIN_135 GPIO_PC17
#define LEFT_CN_PIN_136 GPIO_PC16
#define LEFT_CN_PIN_137 GPIO_PC18
#define LEFT_CN_PIN_138 GPIO_PE6
#define LEFT_CN_PIN_139 GPIO_PB22
#define LEFT_CN_PIN_140 GPIO_PB23
#define LEFT_CN_PIN_141 GPIO_PB21
#define LEFT_CN_PIN_142 GPIO_PB20
#define LEFT_CN_PIN_143 GPIO_PC5
#define LEFT_CN_PIN_144 GPIO_PB6
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
#define LEFT_CN_PIN_158 GPIO_PE1
#define LEFT_CN_PIN_159 GPIO_PE2
#define LEFT_CN_PIN_160 GPIO_PE3
#define LEFT_CN_PIN_161 GPIO_PE4
#define LEFT_CN_PIN_162 GPIO_PE0
#define LEFT_CN_PIN_163     // Pin not routed.
#define LEFT_CN_PIN_164 GPIO_PA1
#define LEFT_CN_PIN_165 GPIO_PA2
#define LEFT_CN_PIN_166 GPIO_PA0
#define LEFT_CN_PIN_167 GPIO_PA3
#define LEFT_CN_PIN_168     // Pin not routed.

// Right connector
#define RIGHT_CN_PIN_001 GPIO_PC0
#define RIGHT_CN_PIN_002 GPIO_PC1
#define RIGHT_CN_PIN_003 GPIO_PC2
#define RIGHT_CN_PIN_004 GPIO_PC3
#define RIGHT_CN_PIN_005 GPIO_PC4
#define RIGHT_CN_PIN_006 GPIO_PC5
#define RIGHT_CN_PIN_007 GPIO_PC6
#define RIGHT_CN_PIN_008 GPIO_PC7
#define RIGHT_CN_PIN_009     // Pin not routed.
#define RIGHT_CN_PIN_010     // Pin not routed.
#define RIGHT_CN_PIN_011     // Pin not routed.
#define RIGHT_CN_PIN_012 GPIO_PD0
#define RIGHT_CN_PIN_013 GPIO_PD1
#define RIGHT_CN_PIN_014 GPIO_PD2
#define RIGHT_CN_PIN_015 GPIO_PD3
#define RIGHT_CN_PIN_016 GPIO_PD4
#define RIGHT_CN_PIN_017 GPIO_PD5
#define RIGHT_CN_PIN_018 GPIO_PD6
#define RIGHT_CN_PIN_019 GPIO_PD7
#define RIGHT_CN_PIN_020 GPIO_PE0
#define RIGHT_CN_PIN_021 GPIO_PE1
#define RIGHT_CN_PIN_022 GPIO_PE2
#define RIGHT_CN_PIN_023 GPIO_PE3
#define RIGHT_CN_PIN_024 GPIO_PE4
#define RIGHT_CN_PIN_025 GPIO_PE5
#define RIGHT_CN_PIN_026 GPIO_PE6
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
#define RIGHT_CN_PIN_043 GPIO_PB19
#define RIGHT_CN_PIN_044 GPIO_PB18
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
#define RIGHT_CN_PIN_125     // Pin not routed.
#define RIGHT_CN_PIN_126     // Pin not routed.
#define RIGHT_CN_PIN_127     // Pin not routed.
#define RIGHT_CN_PIN_128     // Pin not routed.
#define RIGHT_CN_PIN_129 GPIO_PA29
#define RIGHT_CN_PIN_130 GPIO_PC15
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
#define RIGHT_CN_PIN_145     // Pin not routed.
#define RIGHT_CN_PIN_146     // Pin not routed.
#define RIGHT_CN_PIN_147     // Pin not routed.
#define RIGHT_CN_PIN_148     // Pin not routed.
#define RIGHT_CN_PIN_149     // Pin not routed.
#define RIGHT_CN_PIN_150 GPIO_PD15
#define RIGHT_CN_PIN_151 GPIO_PD14
#define RIGHT_CN_PIN_152 GPIO_PD13
#define RIGHT_CN_PIN_153 GPIO_PD12
#define RIGHT_CN_PIN_154 GPIO_PD11
#define RIGHT_CN_PIN_155 GPIO_PD10
#define RIGHT_CN_PIN_156 GPIO_PD9
#define RIGHT_CN_PIN_157 GPIO_PD8
#define RIGHT_CN_PIN_158     // Pin not routed.
#define RIGHT_CN_PIN_159 GPIO_PD8
#define RIGHT_CN_PIN_160 GPIO_PD9
#define RIGHT_CN_PIN_161 GPIO_PC15
#define RIGHT_CN_PIN_162 GPIO_PC14
#define RIGHT_CN_PIN_163 GPIO_PC13
#define RIGHT_CN_PIN_164 GPIO_PC12
#define RIGHT_CN_PIN_165 GPIO_PC11
#define RIGHT_CN_PIN_166 GPIO_PC10
#define RIGHT_CN_PIN_167 GPIO_PC9
#define RIGHT_CN_PIN_168 GPIO_PC8

#define LCD_TFT_8BIT_CH0 GPIO_PORT_D
#define LCD_TFT_CH0_8BIT_MASK 0x00FF

#define LCD_TFT_16BIT_CH0 GPIO_PORT_D
#define LCD_TFT_16BIT_CH0_MASK 0xFFFF

#define LCD_TFT_16BIT_CH1 HAL_PORT_NC
#define LCD_TFT_16BIT_CH1_MASK 0x0000

#ifdef __cplusplus
}
#endif

#endif // _MCU_CARD_H_
// ------------------------------------------------------------------------- END
