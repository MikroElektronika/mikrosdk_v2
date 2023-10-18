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
** a written agreement between you and The mikroElektronika Company.
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
#define MCU_CARD_REV_MINOR (80)

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
#define LEFT_CN_PIN_009 NC
#define LEFT_CN_PIN_010 NC
#define LEFT_CN_PIN_011 NC
#define LEFT_CN_PIN_012 PB0
#define LEFT_CN_PIN_013 PB1
#define LEFT_CN_PIN_014 PB2
#define LEFT_CN_PIN_015 PB3
#define LEFT_CN_PIN_016 PB4
#define LEFT_CN_PIN_017 PB5
#define LEFT_CN_PIN_018 NC
#define LEFT_CN_PIN_019 NC
#define LEFT_CN_PIN_020 NC
#define LEFT_CN_PIN_021 NC
#define LEFT_CN_PIN_022 NC
#define LEFT_CN_PIN_023 NC
#define LEFT_CN_PIN_024 NC
#define LEFT_CN_PIN_025 PN0
#define LEFT_CN_PIN_026 PN1
#define LEFT_CN_PIN_027 PN2
#define LEFT_CN_PIN_028 PN3
#define LEFT_CN_PIN_029 PN4
#define LEFT_CN_PIN_030 PM0
#define LEFT_CN_PIN_031 PM1
#define LEFT_CN_PIN_032 PM2
#define LEFT_CN_PIN_033 PM3
#define LEFT_CN_PIN_034 PM4
#define LEFT_CN_PIN_035 PM5
#define LEFT_CN_PIN_036 PM6
#define LEFT_CN_PIN_037 PM7
#define LEFT_CN_PIN_038 PA0
#define LEFT_CN_PIN_039 PA1
#define LEFT_CN_PIN_040 PA2
#define LEFT_CN_PIN_041 PA3
#define LEFT_CN_PIN_042 PA4
#define LEFT_CN_PIN_043 PA5
#define LEFT_CN_PIN_044 PA6
#define LEFT_CN_PIN_045 PA7
#define LEFT_CN_PIN_046 NC
#define LEFT_CN_PIN_047 NC
#define LEFT_CN_PIN_048 NC
#define LEFT_CN_PIN_049 NC
#define LEFT_CN_PIN_050 NC
#define LEFT_CN_PIN_051 NC
#define LEFT_CN_PIN_052 NC
#define LEFT_CN_PIN_053 NC
#define LEFT_CN_PIN_054 PJ0
#define LEFT_CN_PIN_055 PJ1
#define LEFT_CN_PIN_056 PD7
#define LEFT_CN_PIN_057 PG0
#define LEFT_CN_PIN_058 PL1
#define LEFT_CN_PIN_059 PL0
#define LEFT_CN_PIN_060 PG1
#define LEFT_CN_PIN_061 PQ1
#define LEFT_CN_PIN_062 PN5
#define LEFT_CN_PIN_063 PE1
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
#define LEFT_CN_PIN_085 PL0
#define LEFT_CN_PIN_086 PL1
#define LEFT_CN_PIN_087 PD5
#define LEFT_CN_PIN_088 PD4
#define LEFT_CN_PIN_089 PP5
#define LEFT_CN_PIN_090 PD6
#define LEFT_CN_PIN_091 PE4
#define LEFT_CN_PIN_092 PE5
#define LEFT_CN_PIN_093 PB5
#define LEFT_CN_PIN_094 PK2
#define LEFT_CN_PIN_095 PL3
#define LEFT_CN_PIN_096 PE1
#define LEFT_CN_PIN_097 PL0
#define LEFT_CN_PIN_098 PL1
#define LEFT_CN_PIN_099 PP1
#define LEFT_CN_PIN_100 PP0
#define LEFT_CN_PIN_101 PP4
#define LEFT_CN_PIN_102 PB3
#define LEFT_CN_PIN_103 PE4
#define LEFT_CN_PIN_104 PE5
#define LEFT_CN_PIN_105 PB5
#define LEFT_CN_PIN_106 PH3
#define LEFT_CN_PIN_107 PL2
#define LEFT_CN_PIN_108 PE2
#define LEFT_CN_PIN_109 PD3
#define LEFT_CN_PIN_110 PD2
#define LEFT_CN_PIN_111 PC5
#define LEFT_CN_PIN_112 PC4
#define LEFT_CN_PIN_113 PP3
#define LEFT_CN_PIN_114 PB2
#define LEFT_CN_PIN_115 PQ2
#define LEFT_CN_PIN_116 PQ3
#define LEFT_CN_PIN_117 PQ0
#define LEFT_CN_PIN_118 PH2
#define LEFT_CN_PIN_119 PK7
#define LEFT_CN_PIN_120 PE3
#define LEFT_CN_PIN_121 PD3
#define LEFT_CN_PIN_122 PD2
#define LEFT_CN_PIN_123 PC7
#define LEFT_CN_PIN_124 PC6
#define LEFT_CN_PIN_125 PP2
#define LEFT_CN_PIN_126 PL5
#define LEFT_CN_PIN_127 PQ2
#define LEFT_CN_PIN_128 PQ3
#define LEFT_CN_PIN_129 PQ0
#define LEFT_CN_PIN_130 PH1
#define LEFT_CN_PIN_131 PE0
#define LEFT_CN_PIN_132 PD1
#define LEFT_CN_PIN_133 PD3
#define LEFT_CN_PIN_134 PD2
#define LEFT_CN_PIN_135 PK1
#define LEFT_CN_PIN_136 PK0
#define LEFT_CN_PIN_137 PQ4
#define LEFT_CN_PIN_138 PL4
#define LEFT_CN_PIN_139 PQ2
#define LEFT_CN_PIN_140 PQ3
#define LEFT_CN_PIN_141 PQ0
#define LEFT_CN_PIN_142 PH0
#define LEFT_CN_PIN_143 PK3
#define LEFT_CN_PIN_144 PD0
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
#define RIGHT_CN_PIN_001 PE0
#define RIGHT_CN_PIN_002 PE1
#define RIGHT_CN_PIN_003 PE2
#define RIGHT_CN_PIN_004 PE3
#define RIGHT_CN_PIN_005 PE4
#define RIGHT_CN_PIN_006 PE5
#define RIGHT_CN_PIN_007 NC
#define RIGHT_CN_PIN_008 NC
#define RIGHT_CN_PIN_009 NC
#define RIGHT_CN_PIN_010 NC
#define RIGHT_CN_PIN_011 NC
#define RIGHT_CN_PIN_012 PG0
#define RIGHT_CN_PIN_013 PG1
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
#define RIGHT_CN_PIN_028 PK0
#define RIGHT_CN_PIN_029 PK1
#define RIGHT_CN_PIN_030 PK2
#define RIGHT_CN_PIN_031 PK3
#define RIGHT_CN_PIN_032 PK4
#define RIGHT_CN_PIN_033 PK5
#define RIGHT_CN_PIN_034 PK6
#define RIGHT_CN_PIN_035 PK7
#define RIGHT_CN_PIN_036 PK5
#define RIGHT_CN_PIN_037 NC
#define RIGHT_CN_PIN_038 PK6
#define RIGHT_CN_PIN_039 NC
#define RIGHT_CN_PIN_040 NC
#define RIGHT_CN_PIN_041 NC
#define RIGHT_CN_PIN_042 NC
#define RIGHT_CN_PIN_043 NC
#define RIGHT_CN_PIN_044 NC
#define RIGHT_CN_PIN_045 PM0
#define RIGHT_CN_PIN_046 PM1
#define RIGHT_CN_PIN_047 PM2
#define RIGHT_CN_PIN_048 PM3
#define RIGHT_CN_PIN_049 PM4
#define RIGHT_CN_PIN_050 PM5
#define RIGHT_CN_PIN_051 PM6
#define RIGHT_CN_PIN_052 PM7
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
#define RIGHT_CN_PIN_069 PQ0
#define RIGHT_CN_PIN_070 PQ1
#define RIGHT_CN_PIN_071 PQ2
#define RIGHT_CN_PIN_072 PQ3
#define RIGHT_CN_PIN_073 PQ4
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
#define RIGHT_CN_PIN_111 PP5
#define RIGHT_CN_PIN_112 PP4
#define RIGHT_CN_PIN_113 PP3
#define RIGHT_CN_PIN_114 PP2
#define RIGHT_CN_PIN_115 PP1
#define RIGHT_CN_PIN_116 PP0
#define RIGHT_CN_PIN_117 NC
#define RIGHT_CN_PIN_118 NC
#define RIGHT_CN_PIN_119 PN5
#define RIGHT_CN_PIN_120 PN4
#define RIGHT_CN_PIN_121 PN3
#define RIGHT_CN_PIN_122 PN2
#define RIGHT_CN_PIN_123 PN1
#define RIGHT_CN_PIN_124 PN0
#define RIGHT_CN_PIN_125 PE2
#define RIGHT_CN_PIN_126 PE3
#define RIGHT_CN_PIN_127 PD1
#define RIGHT_CN_PIN_128 PD0
#define RIGHT_CN_PIN_129 PB4
#define RIGHT_CN_PIN_130 PB0
#define RIGHT_CN_PIN_131 NC
#define RIGHT_CN_PIN_132 NC
#define RIGHT_CN_PIN_133 PB1
#define RIGHT_CN_PIN_134 NC
#define RIGHT_CN_PIN_135 NC
#define RIGHT_CN_PIN_136 PL5
#define RIGHT_CN_PIN_137 PL4
#define RIGHT_CN_PIN_138 PL3
#define RIGHT_CN_PIN_139 PL2
#define RIGHT_CN_PIN_140 PL1
#define RIGHT_CN_PIN_141 PL0
#define RIGHT_CN_PIN_142 NC
#define RIGHT_CN_PIN_143 NC
#define RIGHT_CN_PIN_144 NC
#define RIGHT_CN_PIN_145 NC
#define RIGHT_CN_PIN_146 NC
#define RIGHT_CN_PIN_147 NC
#define RIGHT_CN_PIN_148 PJ1
#define RIGHT_CN_PIN_149 PJ0
#define RIGHT_CN_PIN_150 NC
#define RIGHT_CN_PIN_151 NC
#define RIGHT_CN_PIN_152 NC
#define RIGHT_CN_PIN_153 NC
#define RIGHT_CN_PIN_154 PH3
#define RIGHT_CN_PIN_155 PH2
#define RIGHT_CN_PIN_156 PH1
#define RIGHT_CN_PIN_157 PH0
#define RIGHT_CN_PIN_158 NC
#define RIGHT_CN_PIN_159 PD4
#define RIGHT_CN_PIN_160 PD5
#define RIGHT_CN_PIN_161 NC
#define RIGHT_CN_PIN_162 NC
#define RIGHT_CN_PIN_163 NC
#define RIGHT_CN_PIN_164 PF4
#define RIGHT_CN_PIN_165 PF3
#define RIGHT_CN_PIN_166 PF2
#define RIGHT_CN_PIN_167 PF1
#define RIGHT_CN_PIN_168 PF0

#define LCD_TFT_8BIT_CH0 PORT_M
#define LCD_TFT_CH0_8BIT_MASK 0x00FF

#define LCD_TFT_16BIT_CH0 PORT_M
#define LCD_TFT_16BIT_CH0_MASK 0x00FF

#define LCD_TFT_16BIT_CH1 PORT_A
#define LCD_TFT_16BIT_CH1_MASK 0x00FF

#ifdef __cplusplus
}
#endif

#endif // _MCU_CARD_H_
// ------------------------------------------------------------------------- END
