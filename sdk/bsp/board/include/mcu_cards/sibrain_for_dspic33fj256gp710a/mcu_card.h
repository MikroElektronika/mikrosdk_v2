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

#define PORT_MASK_LOW  (uint16_t)0x00FF
#define PORT_MASK_HIGH (uint16_t)0xFF00

// Left connector
#define LEFT_CN_PIN_001 PA0
#define LEFT_CN_PIN_002 PA1
#define LEFT_CN_PIN_003 PA2
#define LEFT_CN_PIN_004 PA3
#define LEFT_CN_PIN_005 PA4
#define LEFT_CN_PIN_006 PA5
#define LEFT_CN_PIN_007 PA6
#define LEFT_CN_PIN_008 PA7
#define LEFT_CN_PIN_009 NC
#define LEFT_CN_PIN_010 NC
#define LEFT_CN_PIN_011 NC
#define LEFT_CN_PIN_012 NC
#define LEFT_CN_PIN_013 PA9
#define LEFT_CN_PIN_014 NC
#define LEFT_CN_PIN_015 NC
#define LEFT_CN_PIN_016 PA12
#define LEFT_CN_PIN_017 PA13
#define LEFT_CN_PIN_018 PA14
#define LEFT_CN_PIN_019 PA15
#define LEFT_CN_PIN_020 NC
#define LEFT_CN_PIN_021 NC
#define LEFT_CN_PIN_022 NC
#define LEFT_CN_PIN_023 NC
#define LEFT_CN_PIN_024 NC
#define LEFT_CN_PIN_025 PA6
#define LEFT_CN_PIN_026 PA7
#define LEFT_CN_PIN_027 PA9
#define LEFT_CN_PIN_028 PB8
#define LEFT_CN_PIN_029 PB5
#define LEFT_CN_PIN_030 PE0
#define LEFT_CN_PIN_031 PE1
#define LEFT_CN_PIN_032 PE2
#define LEFT_CN_PIN_033 PE3
#define LEFT_CN_PIN_034 PE4
#define LEFT_CN_PIN_035 PE5
#define LEFT_CN_PIN_036 PE6
#define LEFT_CN_PIN_037 PE7
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
#define LEFT_CN_PIN_054 PB4
#define LEFT_CN_PIN_055 PB3
#define LEFT_CN_PIN_056 PD5
#define LEFT_CN_PIN_057 PB2
#define LEFT_CN_PIN_058 PA2
#define LEFT_CN_PIN_059 PA3
#define LEFT_CN_PIN_060 PA15
#define LEFT_CN_PIN_061 PB1
#define LEFT_CN_PIN_062 PB0
#define LEFT_CN_PIN_063 NC
#define LEFT_CN_PIN_064 NC
#define LEFT_CN_PIN_065 NC
#define LEFT_CN_PIN_066 NC
#define LEFT_CN_PIN_067 NC
#define LEFT_CN_PIN_068 NC
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
#define LEFT_CN_PIN_085 PG3
#define LEFT_CN_PIN_086 PG2
#define LEFT_CN_PIN_087 PF3
#define LEFT_CN_PIN_088 PF2
#define LEFT_CN_PIN_089 PA15
#define LEFT_CN_PIN_090 PD4
#define LEFT_CN_PIN_091 PG8
#define LEFT_CN_PIN_092 PG7
#define LEFT_CN_PIN_093 PG6
#define LEFT_CN_PIN_094 PG15
#define LEFT_CN_PIN_095 PD13
#define LEFT_CN_PIN_096 PB14
#define LEFT_CN_PIN_097 PG3
#define LEFT_CN_PIN_098 PG2
#define LEFT_CN_PIN_099 PF3
#define LEFT_CN_PIN_100 PF2
#define LEFT_CN_PIN_101 PA14
#define LEFT_CN_PIN_102 PD3
#define LEFT_CN_PIN_103 PG8
#define LEFT_CN_PIN_104 PG7
#define LEFT_CN_PIN_105 PG6
#define LEFT_CN_PIN_106 PG14
#define LEFT_CN_PIN_107 PD12
#define LEFT_CN_PIN_108 PB13
#define LEFT_CN_PIN_109 PG3
#define LEFT_CN_PIN_110 PG2
#define LEFT_CN_PIN_111 PF3
#define LEFT_CN_PIN_112 PF2
#define LEFT_CN_PIN_113 PA13
#define LEFT_CN_PIN_114 PD2
#define LEFT_CN_PIN_115 PG8
#define LEFT_CN_PIN_116 PG7
#define LEFT_CN_PIN_117 PG6
#define LEFT_CN_PIN_118 PG13
#define LEFT_CN_PIN_119 PD11
#define LEFT_CN_PIN_120 PB12
#define LEFT_CN_PIN_121 PA3
#define LEFT_CN_PIN_122 PA2
#define LEFT_CN_PIN_123 PF5
#define LEFT_CN_PIN_124 PF4
#define LEFT_CN_PIN_125 PA12
#define LEFT_CN_PIN_126 PD1
#define LEFT_CN_PIN_127 PG8
#define LEFT_CN_PIN_128 PG7
#define LEFT_CN_PIN_129 PG6
#define LEFT_CN_PIN_130 PG12
#define LEFT_CN_PIN_131 PD10
#define LEFT_CN_PIN_132 PB11
#define LEFT_CN_PIN_133 PA3
#define LEFT_CN_PIN_134 PA2
#define LEFT_CN_PIN_135 PF5
#define LEFT_CN_PIN_136 PF4
#define LEFT_CN_PIN_137 PF6
#define LEFT_CN_PIN_138 PD0
#define LEFT_CN_PIN_139 PG8
#define LEFT_CN_PIN_140 PG7
#define LEFT_CN_PIN_141 PG6
#define LEFT_CN_PIN_142 PG9
#define LEFT_CN_PIN_143 PD9
#define LEFT_CN_PIN_144 PB10
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
#define LEFT_CN_PIN_167 NC
#define LEFT_CN_PIN_168 NC

// Right connector
#define RIGHT_CN_PIN_001 NC
#define RIGHT_CN_PIN_002 PC1
#define RIGHT_CN_PIN_003 PC2
#define RIGHT_CN_PIN_004 PC3
#define RIGHT_CN_PIN_005 PC4
#define RIGHT_CN_PIN_006 NC
#define RIGHT_CN_PIN_007 NC
#define RIGHT_CN_PIN_008 NC
#define RIGHT_CN_PIN_009 NC
#define RIGHT_CN_PIN_010 NC
#define RIGHT_CN_PIN_011 NC
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
#define RIGHT_CN_PIN_028 PF0
#define RIGHT_CN_PIN_029 PF1
#define RIGHT_CN_PIN_030 PF2
#define RIGHT_CN_PIN_031 PF3
#define RIGHT_CN_PIN_032 PF4
#define RIGHT_CN_PIN_033 PF5
#define RIGHT_CN_PIN_034 PF6
#define RIGHT_CN_PIN_035 PF7
#define RIGHT_CN_PIN_036 NC
#define RIGHT_CN_PIN_037 NC
#define RIGHT_CN_PIN_038 NC
#define RIGHT_CN_PIN_039 NC
#define RIGHT_CN_PIN_040 NC
#define RIGHT_CN_PIN_041 NC
#define RIGHT_CN_PIN_042 NC
#define RIGHT_CN_PIN_043 PG0
#define RIGHT_CN_PIN_044 PG1
#define RIGHT_CN_PIN_045 PG0
#define RIGHT_CN_PIN_046 PG1
#define RIGHT_CN_PIN_047 PG2
#define RIGHT_CN_PIN_048 PG3
#define RIGHT_CN_PIN_049 NC
#define RIGHT_CN_PIN_050 NC
#define RIGHT_CN_PIN_051 PG6
#define RIGHT_CN_PIN_052 PG7
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
#define RIGHT_CN_PIN_117 PG15
#define RIGHT_CN_PIN_118 PG14
#define RIGHT_CN_PIN_119 PG13 
#define RIGHT_CN_PIN_120 PG12
#define RIGHT_CN_PIN_121 NC
#define RIGHT_CN_PIN_122 NC
#define RIGHT_CN_PIN_123 PG9
#define RIGHT_CN_PIN_124 PG8
#define RIGHT_CN_PIN_125 PC4
#define RIGHT_CN_PIN_126 PC3
#define RIGHT_CN_PIN_127 PC2
#define RIGHT_CN_PIN_128 PC1
#define RIGHT_CN_PIN_129 NC
#define RIGHT_CN_PIN_130 NC
#define RIGHT_CN_PIN_131 NC
#define RIGHT_CN_PIN_132 NC
#define RIGHT_CN_PIN_133 NC
#define RIGHT_CN_PIN_134 NC
#define RIGHT_CN_PIN_135 NC
#define RIGHT_CN_PIN_136 PF13
#define RIGHT_CN_PIN_137 PF12
#define RIGHT_CN_PIN_138 NC
#define RIGHT_CN_PIN_139 NC
#define RIGHT_CN_PIN_140 NC
#define RIGHT_CN_PIN_141 PF8
#define RIGHT_CN_PIN_142 NC
#define RIGHT_CN_PIN_143 NC
#define RIGHT_CN_PIN_144 NC
#define RIGHT_CN_PIN_145 NC
#define RIGHT_CN_PIN_146 NC
#define RIGHT_CN_PIN_147 NC
#define RIGHT_CN_PIN_148 NC
#define RIGHT_CN_PIN_149 NC
#define RIGHT_CN_PIN_150 PD15
#define RIGHT_CN_PIN_151 PD14
#define RIGHT_CN_PIN_152 PD13
#define RIGHT_CN_PIN_153 PD12
#define RIGHT_CN_PIN_154 PD11
#define RIGHT_CN_PIN_155 PD10
#define RIGHT_CN_PIN_156 PD9
#define RIGHT_CN_PIN_157 PD8
#define RIGHT_CN_PIN_158 NC
#define RIGHT_CN_PIN_159 PF4
#define RIGHT_CN_PIN_160 PF5
#define RIGHT_CN_PIN_161 NC
#define RIGHT_CN_PIN_162 NC
#define RIGHT_CN_PIN_163 NC
#define RIGHT_CN_PIN_164 NC
#define RIGHT_CN_PIN_165 NC
#define RIGHT_CN_PIN_166 NC
#define RIGHT_CN_PIN_167 NC
#define RIGHT_CN_PIN_168 NC

#define LCD_TFT_8BIT_CH0 PORT_E
#define LCD_TFT_CH0_8BIT_MASK 0xFF

#define LCD_TFT_16BIT_CH0 PORT_E
#define LCD_TFT_16BIT_CH0_MASK 0xFF

#define LCD_TFT_16BIT_CH1 NC
#define LCD_TFT_16BIT_CH1_MASK 0xFF00

#ifdef __cplusplus
}
#endif

#endif // _MCU_CARD_H_
// ------------------------------------------------------------------------- END
