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
#define LEFT_CN_PIN_016 NC
#define LEFT_CN_PIN_017 NC
#define LEFT_CN_PIN_018 PA14
#define LEFT_CN_PIN_019 PA15
#define LEFT_CN_PIN_020 NC
#define LEFT_CN_PIN_021 PJ13
#define LEFT_CN_PIN_022 PJ14
#define LEFT_CN_PIN_023 PJ15
#define LEFT_CN_PIN_024 PJ6
#define LEFT_CN_PIN_025 PB10
#define LEFT_CN_PIN_026 PK11
#define LEFT_CN_PIN_027 PB9
#define LEFT_CN_PIN_028 PK15
#define LEFT_CN_PIN_029 PK14
#define LEFT_CN_PIN_030 PH0
#define LEFT_CN_PIN_031 PH1
#define LEFT_CN_PIN_032 PH2
#define LEFT_CN_PIN_033 PH3
#define LEFT_CN_PIN_034 PH4
#define LEFT_CN_PIN_035 PH5
#define LEFT_CN_PIN_036 PH6
#define LEFT_CN_PIN_037 PH7
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
#define LEFT_CN_PIN_054 PD15
#define LEFT_CN_PIN_055 PD14
#define LEFT_CN_PIN_056 PF12
#define LEFT_CN_PIN_057 PF4
#define LEFT_CN_PIN_058 PA2
#define LEFT_CN_PIN_059 PA3
#define LEFT_CN_PIN_060 PB8
#define LEFT_CN_PIN_061 PB4
#define LEFT_CN_PIN_062 PB3
#define LEFT_CN_PIN_063 PB2
#define LEFT_CN_PIN_064 PB1
#define LEFT_CN_PIN_065 PB0
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
#define LEFT_CN_PIN_085 PD9
#define LEFT_CN_PIN_086 PD10
#define LEFT_CN_PIN_087 PG13
#define LEFT_CN_PIN_088 PG12
#define LEFT_CN_PIN_089 PD11
#define LEFT_CN_PIN_090 PD7
#define LEFT_CN_PIN_091 PG8
#define LEFT_CN_PIN_092 PG7
#define LEFT_CN_PIN_093 PG6
#define LEFT_CN_PIN_094 PH15
#define LEFT_CN_PIN_095 PH14
#define LEFT_CN_PIN_096 PB15
#define LEFT_CN_PIN_097 PD9
#define LEFT_CN_PIN_098 PD10
#define LEFT_CN_PIN_099 PF8
#define LEFT_CN_PIN_100 PD12
#define LEFT_CN_PIN_101 PG1
#define LEFT_CN_PIN_102 PD1
#define LEFT_CN_PIN_103 PG8
#define LEFT_CN_PIN_104 PG7
#define LEFT_CN_PIN_105 PG6
#define LEFT_CN_PIN_106 PH11
#define LEFT_CN_PIN_107 PH10
#define LEFT_CN_PIN_108 PB14
#define LEFT_CN_PIN_109 PD9
#define LEFT_CN_PIN_110 PD10
#define LEFT_CN_PIN_111 PF2
#define LEFT_CN_PIN_112 PE2
#define LEFT_CN_PIN_113 PG9
#define LEFT_CN_PIN_114 PG0
#define LEFT_CN_PIN_115 PG8
#define LEFT_CN_PIN_116 PG7
#define LEFT_CN_PIN_117 PG6
#define LEFT_CN_PIN_118 PH9
#define LEFT_CN_PIN_119 PH8
#define LEFT_CN_PIN_120 PB13
#define LEFT_CN_PIN_121 PA3
#define LEFT_CN_PIN_122 PA2
#define LEFT_CN_PIN_123 PF13
#define LEFT_CN_PIN_124 PE4
#define LEFT_CN_PIN_125 PE3
#define LEFT_CN_PIN_126 PG14
#define LEFT_CN_PIN_127 PG8
#define LEFT_CN_PIN_128 PG7
#define LEFT_CN_PIN_129 PG6
#define LEFT_CN_PIN_130 PK1
#define LEFT_CN_PIN_131 PK0
#define LEFT_CN_PIN_132 PA7
#define LEFT_CN_PIN_133 PA3
#define LEFT_CN_PIN_134 PA2
#define LEFT_CN_PIN_135 PF1
#define LEFT_CN_PIN_136 PA15
#define LEFT_CN_PIN_137 PA14
#define LEFT_CN_PIN_138 PF0
#define LEFT_CN_PIN_139 PG8
#define LEFT_CN_PIN_140 PG7
#define LEFT_CN_PIN_141 PG6
#define LEFT_CN_PIN_142 PJ4
#define LEFT_CN_PIN_143 PJ5
#define LEFT_CN_PIN_144 PA6
#define LEFT_CN_PIN_145 PJ7
#define LEFT_CN_PIN_146 PC4
#define LEFT_CN_PIN_147 PC3
#define LEFT_CN_PIN_148 PC2
#define LEFT_CN_PIN_149 PC1
#define LEFT_CN_PIN_150 PJ12
#define LEFT_CN_PIN_151 PJ11
#define LEFT_CN_PIN_152 PJ10
#define LEFT_CN_PIN_153 PJ9
#define LEFT_CN_PIN_154 PJ8
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
#define RIGHT_CN_PIN_034 NC
#define RIGHT_CN_PIN_035 NC
#define RIGHT_CN_PIN_036 NC
#define RIGHT_CN_PIN_037 NC
#define RIGHT_CN_PIN_038 NC
#define RIGHT_CN_PIN_039 NC
#define RIGHT_CN_PIN_040 NC
#define RIGHT_CN_PIN_041 NC
#define RIGHT_CN_PIN_042 NC
#define RIGHT_CN_PIN_043 PE6
#define RIGHT_CN_PIN_044 PE5
#define RIGHT_CN_PIN_045 PG0
#define RIGHT_CN_PIN_046 PG1
#define RIGHT_CN_PIN_047 NC
#define RIGHT_CN_PIN_048 NC
#define RIGHT_CN_PIN_049 NC
#define RIGHT_CN_PIN_050 NC
#define RIGHT_CN_PIN_051 PG6
#define RIGHT_CN_PIN_052 PG7
#define RIGHT_CN_PIN_053 PH0
#define RIGHT_CN_PIN_054 PH1
#define RIGHT_CN_PIN_055 PH2
#define RIGHT_CN_PIN_056 PH3
#define RIGHT_CN_PIN_057 PH4
#define RIGHT_CN_PIN_058 PH5
#define RIGHT_CN_PIN_059 PH6
#define RIGHT_CN_PIN_060 PH7
#define RIGHT_CN_PIN_061 PK1
#define RIGHT_CN_PIN_062 PK0
#define RIGHT_CN_PIN_063 PK13
#define RIGHT_CN_PIN_064 PK12
#define RIGHT_CN_PIN_065 NC
#define RIGHT_CN_PIN_066 NC
#define RIGHT_CN_PIN_067 NC
#define RIGHT_CN_PIN_068 NC
#define RIGHT_CN_PIN_069 PK0
#define RIGHT_CN_PIN_070 PK1
#define RIGHT_CN_PIN_071 NC
#define RIGHT_CN_PIN_072 NC
#define RIGHT_CN_PIN_073 NC
#define RIGHT_CN_PIN_074 NC
#define RIGHT_CN_PIN_075 NC
#define RIGHT_CN_PIN_076 NC
#define RIGHT_CN_PIN_077 PJ0
#define RIGHT_CN_PIN_078 PJ1
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
#define RIGHT_CN_PIN_089 PJ11
#define RIGHT_CN_PIN_090 PJ10
#define RIGHT_CN_PIN_091 PJ9
#define RIGHT_CN_PIN_092 PJ8
#define RIGHT_CN_PIN_093 PK15
#define RIGHT_CN_PIN_094 PK14
#define RIGHT_CN_PIN_095 PK13
#define RIGHT_CN_PIN_096 PK12
#define RIGHT_CN_PIN_097 PK11
#define RIGHT_CN_PIN_098 NC
#define RIGHT_CN_PIN_099 NC
#define RIGHT_CN_PIN_100 NC
#define RIGHT_CN_PIN_101 PJ0
#define RIGHT_CN_PIN_102 PJ1
#define RIGHT_CN_PIN_103 PJ2
#define RIGHT_CN_PIN_104 PE1
#define RIGHT_CN_PIN_105 PJ4
#define RIGHT_CN_PIN_106 PG15
#define RIGHT_CN_PIN_107 PH12
#define RIGHT_CN_PIN_108 PH13
#define RIGHT_CN_PIN_109 PH15
#define RIGHT_CN_PIN_110 PH14
#define RIGHT_CN_PIN_111 PH13
#define RIGHT_CN_PIN_112 PH12
#define RIGHT_CN_PIN_113 PH11
#define RIGHT_CN_PIN_114 PH10
#define RIGHT_CN_PIN_115 PH9
#define RIGHT_CN_PIN_116 PH8
#define RIGHT_CN_PIN_117 PG15
#define RIGHT_CN_PIN_118 PG14
#define RIGHT_CN_PIN_119 PG13
#define RIGHT_CN_PIN_120 PG12
#define RIGHT_CN_PIN_121 NC
#define RIGHT_CN_PIN_122 NC
#define RIGHT_CN_PIN_123 PG9
#define RIGHT_CN_PIN_124 PG8
#define RIGHT_CN_PIN_125 PC4
#define RIGHT_CN_PIN_126 PE7
#define RIGHT_CN_PIN_127 PE8
#define RIGHT_CN_PIN_128 PE9
#define RIGHT_CN_PIN_129 PB5
#define RIGHT_CN_PIN_130 PF3
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
#define RIGHT_CN_PIN_148 PE9
#define RIGHT_CN_PIN_149 PE8
#define RIGHT_CN_PIN_150 PD15
#define RIGHT_CN_PIN_151 PD14
#define RIGHT_CN_PIN_152 PD13
#define RIGHT_CN_PIN_153 PD12
#define RIGHT_CN_PIN_154 PD11
#define RIGHT_CN_PIN_155 PD10
#define RIGHT_CN_PIN_156 PD9
#define RIGHT_CN_PIN_157 PD8
#define RIGHT_CN_PIN_158 NC
#define RIGHT_CN_PIN_159 PG12
#define RIGHT_CN_PIN_160 PG13
#define RIGHT_CN_PIN_161 NC
#define RIGHT_CN_PIN_162 NC
#define RIGHT_CN_PIN_163 NC
#define RIGHT_CN_PIN_164 NC
#define RIGHT_CN_PIN_165 NC
#define RIGHT_CN_PIN_166 NC
#define RIGHT_CN_PIN_167 NC
#define RIGHT_CN_PIN_168 NC

#define LCD_TFT_8BIT_CH0 PORT_H
#define LCD_TFT_CH0_8BIT_MASK 0xFF

#define LCD_TFT_16BIT_CH0 PORT_H
#define LCD_TFT_16BIT_CH0_MASK 0xFF

#define LCD_TFT_16BIT_CH1 NC
#define LCD_TFT_16BIT_CH1_MASK 0xFF00

#ifdef __cplusplus
}
#endif

#endif // _MCU_CARD_H_
// ------------------------------------------------------------------------- END
