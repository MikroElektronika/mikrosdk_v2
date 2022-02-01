/****************************************************************************
**
** Copyright (C) 2022 MikroElektronika d.o.o.
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
#define LEFT_CN_PIN_007 NC
#define LEFT_CN_PIN_008 NC
#define LEFT_CN_PIN_009 NC
#define LEFT_CN_PIN_010 NC
#define LEFT_CN_PIN_011 NC
#define LEFT_CN_PIN_012 PB0
#define LEFT_CN_PIN_013 PB1
#define LEFT_CN_PIN_014 PB2
#define LEFT_CN_PIN_015 PB3
#define LEFT_CN_PIN_016 PB4
#define LEFT_CN_PIN_017 PB5
#define LEFT_CN_PIN_018 PB6
#define LEFT_CN_PIN_019 PB7
#define LEFT_CN_PIN_020 NC
#define LEFT_CN_PIN_021 NC
#define LEFT_CN_PIN_022 NC
#define LEFT_CN_PIN_023 NC
#define LEFT_CN_PIN_024 NC
#define LEFT_CN_PIN_025 PD0
#define LEFT_CN_PIN_026 PE2
#define LEFT_CN_PIN_027 PD1
#define LEFT_CN_PIN_028 PD2
#define LEFT_CN_PIN_029 PC2
#define LEFT_CN_PIN_030 PF0
#define LEFT_CN_PIN_031 PF1
#define LEFT_CN_PIN_032 PF2
#define LEFT_CN_PIN_033 PF3
#define LEFT_CN_PIN_034 PF4
#define LEFT_CN_PIN_035 PF5
#define LEFT_CN_PIN_036 PF6
#define LEFT_CN_PIN_037 PF7
#define LEFT_CN_PIN_038 NC
#define LEFT_CN_PIN_039 NC
#define LEFT_CN_PIN_040 NC
#define LEFT_CN_PIN_041 NC
#define LEFT_CN_PIN_042 NC
#define LEFT_CN_PIN_043 NC
#define LEFT_CN_PIN_044 NC
#define LEFT_CN_PIN_045 NC
#define LEFT_CN_PIN_046 NC
#define LEFT_CN_PIN_047 NC
#define LEFT_CN_PIN_048 NC
#define LEFT_CN_PIN_049 NC
#define LEFT_CN_PIN_050 NC
#define LEFT_CN_PIN_051 NC
#define LEFT_CN_PIN_052 NC
#define LEFT_CN_PIN_053 NC
#define LEFT_CN_PIN_054 PC0
#define LEFT_CN_PIN_055 PD3
#define LEFT_CN_PIN_056 PB5
#define LEFT_CN_PIN_057 PA4
#define LEFT_CN_PIN_058 PB1
#define LEFT_CN_PIN_059 PB2
#define LEFT_CN_PIN_060 PA2
#define LEFT_CN_PIN_061 PA5
#define LEFT_CN_PIN_062 PC1
#define LEFT_CN_PIN_063 NC
#define LEFT_CN_PIN_064 NC
#define LEFT_CN_PIN_065 NC
#define LEFT_CN_PIN_066 NC
#define LEFT_CN_PIN_067 NC
#define LEFT_CN_PIN_068 NC
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
#define LEFT_CN_PIN_085 PB2
#define LEFT_CN_PIN_086 PB1
#define LEFT_CN_PIN_087 PB6
#define LEFT_CN_PIN_088 PB7
#define LEFT_CN_PIN_089 PA2
#define LEFT_CN_PIN_090 PB5
#define LEFT_CN_PIN_091 PC5
#define LEFT_CN_PIN_092 PC4
#define LEFT_CN_PIN_093 PC3
#define LEFT_CN_PIN_094 PE2
#define LEFT_CN_PIN_095 PA4
#define LEFT_CN_PIN_096 PD7
#define LEFT_CN_PIN_097 PB2
#define LEFT_CN_PIN_098 PB1
#define LEFT_CN_PIN_099 PB6
#define LEFT_CN_PIN_100 PB7
#define LEFT_CN_PIN_101 PA2
#define LEFT_CN_PIN_102 PB5
#define LEFT_CN_PIN_103 PC5
#define LEFT_CN_PIN_104 PC4
#define LEFT_CN_PIN_105 PC3
#define LEFT_CN_PIN_106 PE2
#define LEFT_CN_PIN_107 PA4
#define LEFT_CN_PIN_108 PD7
#define LEFT_CN_PIN_109 PB2
#define LEFT_CN_PIN_110 PB1
#define LEFT_CN_PIN_111 PC6
#define LEFT_CN_PIN_112 PC7
#define LEFT_CN_PIN_113 PA1
#define LEFT_CN_PIN_114 PB4
#define LEFT_CN_PIN_115 PC5
#define LEFT_CN_PIN_116 PC4
#define LEFT_CN_PIN_117 PC3
#define LEFT_CN_PIN_118 PE1
#define LEFT_CN_PIN_119 PA3
#define LEFT_CN_PIN_120 PD6
#define LEFT_CN_PIN_121 PB2
#define LEFT_CN_PIN_122 PB1
#define LEFT_CN_PIN_123 PC6
#define LEFT_CN_PIN_124 PC7
#define LEFT_CN_PIN_125 PA1
#define LEFT_CN_PIN_126 PB4
#define LEFT_CN_PIN_127 PC5
#define LEFT_CN_PIN_128 PC4
#define LEFT_CN_PIN_129 PC3
#define LEFT_CN_PIN_130 PE1
#define LEFT_CN_PIN_131 PA3
#define LEFT_CN_PIN_132 PD5
#define LEFT_CN_PIN_133 PB2
#define LEFT_CN_PIN_134 PB1
#define LEFT_CN_PIN_135 PC6
#define LEFT_CN_PIN_136 PC7
#define LEFT_CN_PIN_137 PA0
#define LEFT_CN_PIN_138 PB0
#define LEFT_CN_PIN_139 PC5
#define LEFT_CN_PIN_140 PC4
#define LEFT_CN_PIN_141 PC3
#define LEFT_CN_PIN_142 PE0
#define LEFT_CN_PIN_143 PB3
#define LEFT_CN_PIN_144 PD4
#define LEFT_CN_PIN_145 NC
#define LEFT_CN_PIN_146 NC
#define LEFT_CN_PIN_147 NC
#define LEFT_CN_PIN_148 NC
#define LEFT_CN_PIN_149 NC
#define LEFT_CN_PIN_150 NC
#define LEFT_CN_PIN_151 NC
#define LEFT_CN_PIN_152 NC
#define LEFT_CN_PIN_153 NC
#define LEFT_CN_PIN_154 NC
#define LEFT_CN_PIN_155 NC
#define LEFT_CN_PIN_156 NC
#define LEFT_CN_PIN_157 NC
#define LEFT_CN_PIN_158 NC
#define LEFT_CN_PIN_159 NC
#define LEFT_CN_PIN_160 NC
#define LEFT_CN_PIN_161 NC
#define LEFT_CN_PIN_162 NC
#define LEFT_CN_PIN_163 NC
#define LEFT_CN_PIN_164 NC
#define LEFT_CN_PIN_165 NC
#define LEFT_CN_PIN_166 NC
#define LEFT_CN_PIN_167 PC6
#define LEFT_CN_PIN_168 NC

// Right connector
#define RIGHT_CN_PIN_001 PE0
#define RIGHT_CN_PIN_002 PE1
#define RIGHT_CN_PIN_003 PE2
#define RIGHT_CN_PIN_004 NC
#define RIGHT_CN_PIN_005 NC
#define RIGHT_CN_PIN_006 NC
#define RIGHT_CN_PIN_007 NC
#define RIGHT_CN_PIN_008 NC
#define RIGHT_CN_PIN_009 NC
#define RIGHT_CN_PIN_010 NC
#define RIGHT_CN_PIN_011 NC
#define RIGHT_CN_PIN_012 NC
#define RIGHT_CN_PIN_013 NC
#define RIGHT_CN_PIN_014 NC
#define RIGHT_CN_PIN_015 NC
#define RIGHT_CN_PIN_016 NC
#define RIGHT_CN_PIN_017 NC
#define RIGHT_CN_PIN_018 NC
#define RIGHT_CN_PIN_019 NC
#define RIGHT_CN_PIN_020 NC
#define RIGHT_CN_PIN_021 NC
#define RIGHT_CN_PIN_022 NC
#define RIGHT_CN_PIN_023 NC
#define RIGHT_CN_PIN_024 NC
#define RIGHT_CN_PIN_025 NC
#define RIGHT_CN_PIN_026 NC
#define RIGHT_CN_PIN_027 NC
#define RIGHT_CN_PIN_028 NC
#define RIGHT_CN_PIN_029 NC
#define RIGHT_CN_PIN_030 NC
#define RIGHT_CN_PIN_031 NC
#define RIGHT_CN_PIN_032 NC
#define RIGHT_CN_PIN_033 NC
#define RIGHT_CN_PIN_034 NC
#define RIGHT_CN_PIN_035 NC
#define RIGHT_CN_PIN_036 NC
#define RIGHT_CN_PIN_037 NC
#define RIGHT_CN_PIN_038 NC
#define RIGHT_CN_PIN_039 NC
#define RIGHT_CN_PIN_040 NC
#define RIGHT_CN_PIN_041 NC
#define RIGHT_CN_PIN_042 NC
#define RIGHT_CN_PIN_043 NC
#define RIGHT_CN_PIN_044 NC
#define RIGHT_CN_PIN_045 NC
#define RIGHT_CN_PIN_046 NC
#define RIGHT_CN_PIN_047 NC
#define RIGHT_CN_PIN_048 NC
#define RIGHT_CN_PIN_049 NC
#define RIGHT_CN_PIN_050 NC
#define RIGHT_CN_PIN_051 NC
#define RIGHT_CN_PIN_052 NC
#define RIGHT_CN_PIN_053 NC
#define RIGHT_CN_PIN_054 NC
#define RIGHT_CN_PIN_055 NC
#define RIGHT_CN_PIN_056 NC
#define RIGHT_CN_PIN_057 NC
#define RIGHT_CN_PIN_058 NC
#define RIGHT_CN_PIN_059 NC
#define RIGHT_CN_PIN_060 NC
#define RIGHT_CN_PIN_061 NC
#define RIGHT_CN_PIN_062 NC
#define RIGHT_CN_PIN_063 NC
#define RIGHT_CN_PIN_064 NC
#define RIGHT_CN_PIN_065 NC
#define RIGHT_CN_PIN_066 NC
#define RIGHT_CN_PIN_067 NC
#define RIGHT_CN_PIN_068 NC
#define RIGHT_CN_PIN_069 NC
#define RIGHT_CN_PIN_070 NC
#define RIGHT_CN_PIN_071 NC
#define RIGHT_CN_PIN_072 NC
#define RIGHT_CN_PIN_073 NC
#define RIGHT_CN_PIN_074 NC
#define RIGHT_CN_PIN_075 NC
#define RIGHT_CN_PIN_076 NC
#define RIGHT_CN_PIN_077 NC
#define RIGHT_CN_PIN_078 NC
#define RIGHT_CN_PIN_079 NC
#define RIGHT_CN_PIN_080 NC
#define RIGHT_CN_PIN_081 NC
#define RIGHT_CN_PIN_082 NC
#define RIGHT_CN_PIN_083 NC
#define RIGHT_CN_PIN_084 NC
#define RIGHT_CN_PIN_085 NC
#define RIGHT_CN_PIN_086 NC
#define RIGHT_CN_PIN_087 NC
#define RIGHT_CN_PIN_088 NC
#define RIGHT_CN_PIN_089 NC
#define RIGHT_CN_PIN_090 NC
#define RIGHT_CN_PIN_091 NC
#define RIGHT_CN_PIN_092 NC
#define RIGHT_CN_PIN_093 NC
#define RIGHT_CN_PIN_094 NC
#define RIGHT_CN_PIN_095 NC
#define RIGHT_CN_PIN_096 NC
#define RIGHT_CN_PIN_097 NC
#define RIGHT_CN_PIN_098 NC
#define RIGHT_CN_PIN_099 NC
#define RIGHT_CN_PIN_100 NC
#define RIGHT_CN_PIN_101 NC
#define RIGHT_CN_PIN_102 NC
#define RIGHT_CN_PIN_103 NC
#define RIGHT_CN_PIN_104 NC
#define RIGHT_CN_PIN_105 NC
#define RIGHT_CN_PIN_106 NC
#define RIGHT_CN_PIN_107 NC
#define RIGHT_CN_PIN_108 NC
#define RIGHT_CN_PIN_109 NC
#define RIGHT_CN_PIN_110 NC
#define RIGHT_CN_PIN_111 NC
#define RIGHT_CN_PIN_112 NC
#define RIGHT_CN_PIN_113 NC
#define RIGHT_CN_PIN_114 NC
#define RIGHT_CN_PIN_115 NC
#define RIGHT_CN_PIN_116 NC
#define RIGHT_CN_PIN_117 NC
#define RIGHT_CN_PIN_118 NC
#define RIGHT_CN_PIN_119 NC
#define RIGHT_CN_PIN_120 NC
#define RIGHT_CN_PIN_121 NC
#define RIGHT_CN_PIN_122 NC
#define RIGHT_CN_PIN_123 NC
#define RIGHT_CN_PIN_124 NC
#define RIGHT_CN_PIN_125 PD7
#define RIGHT_CN_PIN_126 PD6
#define RIGHT_CN_PIN_127 PD5
#define RIGHT_CN_PIN_128 PD4
#define RIGHT_CN_PIN_129 NC
#define RIGHT_CN_PIN_130 NC
#define RIGHT_CN_PIN_131 NC
#define RIGHT_CN_PIN_132 NC
#define RIGHT_CN_PIN_133 NC
#define RIGHT_CN_PIN_134 NC
#define RIGHT_CN_PIN_135 NC
#define RIGHT_CN_PIN_136 NC
#define RIGHT_CN_PIN_137 NC
#define RIGHT_CN_PIN_138 NC
#define RIGHT_CN_PIN_139 NC
#define RIGHT_CN_PIN_140 NC
#define RIGHT_CN_PIN_141 NC
#define RIGHT_CN_PIN_142 NC
#define RIGHT_CN_PIN_143 NC
#define RIGHT_CN_PIN_144 NC
#define RIGHT_CN_PIN_145 NC
#define RIGHT_CN_PIN_146 NC
#define RIGHT_CN_PIN_147 NC
#define RIGHT_CN_PIN_148 NC
#define RIGHT_CN_PIN_149 NC
#define RIGHT_CN_PIN_150 NC
#define RIGHT_CN_PIN_151 NC
#define RIGHT_CN_PIN_152 NC
#define RIGHT_CN_PIN_153 NC
#define RIGHT_CN_PIN_154 NC
#define RIGHT_CN_PIN_155 NC
#define RIGHT_CN_PIN_156 NC
#define RIGHT_CN_PIN_157 NC
#define RIGHT_CN_PIN_158 NC
#define RIGHT_CN_PIN_159 PC7
#define RIGHT_CN_PIN_160 PC6
#define RIGHT_CN_PIN_161 PF7
#define RIGHT_CN_PIN_162 PF6
#define RIGHT_CN_PIN_163 PF5
#define RIGHT_CN_PIN_164 PF4
#define RIGHT_CN_PIN_165 PF3
#define RIGHT_CN_PIN_166 PF2
#define RIGHT_CN_PIN_167 PF1
#define RIGHT_CN_PIN_168 PF0

#define LCD_TFT_8BIT_CH0 PORT_F
#define LCD_TFT_CH0_8BIT_MASK 0x00FF

#define LCD_TFT_16BIT_CH0 HAL_PORT_NC
#define LCD_TFT_16BIT_CH0_MASK 0x00

#define LCD_TFT_16BIT_CH1 HAL_PORT_NC
#define LCD_TFT_16BIT_CH1_MASK 0x00

#ifdef __cplusplus
}
#endif

#endif // _MCU_CARD_H_
// ------------------------------------------------------------------------- END
