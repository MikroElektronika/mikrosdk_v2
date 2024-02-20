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
#define MCU_CARD_REV_MINOR (89)

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
#define LEFT_CN_PIN_021 PL0
#define LEFT_CN_PIN_022 PL1
#define LEFT_CN_PIN_023 PL2
#define LEFT_CN_PIN_024 PL3
#define LEFT_CN_PIN_025 PC4
#define LEFT_CN_PIN_026 PC5
#define LEFT_CN_PIN_027 PC6
#define LEFT_CN_PIN_028 PC7
#define LEFT_CN_PIN_029 PE6
#define LEFT_CN_PIN_030 PH0
#define LEFT_CN_PIN_031 PH1
#define LEFT_CN_PIN_032 PH2
#define LEFT_CN_PIN_033 PH3
#define LEFT_CN_PIN_034 PH4
#define LEFT_CN_PIN_035 PH5
#define LEFT_CN_PIN_036 PH6
#define LEFT_CN_PIN_037 PH7
#define LEFT_CN_PIN_038 PQ0
#define LEFT_CN_PIN_039 PQ1
#define LEFT_CN_PIN_040 PQ2
#define LEFT_CN_PIN_041 PQ3
#define LEFT_CN_PIN_042 PQ4
#define LEFT_CN_PIN_043 PQ5
#define LEFT_CN_PIN_044 PQ6
#define LEFT_CN_PIN_045 PQ7
#define LEFT_CN_PIN_046 PS0
#define LEFT_CN_PIN_047 PS1
#define LEFT_CN_PIN_048 PS2
#define LEFT_CN_PIN_049 PS3
#define LEFT_CN_PIN_050 PS4
#define LEFT_CN_PIN_051 PS5
#define LEFT_CN_PIN_052 PS6
#define LEFT_CN_PIN_053 PS7
#define LEFT_CN_PIN_054 PG7
#define LEFT_CN_PIN_055 PK3
#define LEFT_CN_PIN_056 PM6
#define LEFT_CN_PIN_057 PK4
#define LEFT_CN_PIN_058 PG2
#define LEFT_CN_PIN_059 PG3
#define LEFT_CN_PIN_060 PG4
#define LEFT_CN_PIN_061 PG5
#define LEFT_CN_PIN_062 PG6
#define LEFT_CN_PIN_063 PK2
#define LEFT_CN_PIN_064 PP6
#define LEFT_CN_PIN_065 PP7
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
#define LEFT_CN_PIN_085 PG1
#define LEFT_CN_PIN_086 PG0
#define LEFT_CN_PIN_087 PA3
#define LEFT_CN_PIN_088 PK0
#define LEFT_CN_PIN_089 PJ7
#define LEFT_CN_PIN_090 PM4
#define LEFT_CN_PIN_091 PE4
#define LEFT_CN_PIN_092 PE5
#define LEFT_CN_PIN_093 PB5
#define LEFT_CN_PIN_094 PJ6
#define LEFT_CN_PIN_095 PF7
#define LEFT_CN_PIN_096 PD4
#define LEFT_CN_PIN_097 PG1
#define LEFT_CN_PIN_098 PG0
#define LEFT_CN_PIN_099 PJ1
#define LEFT_CN_PIN_100 PJ0
#define LEFT_CN_PIN_101 PJ5
#define LEFT_CN_PIN_102 PM2
#define LEFT_CN_PIN_103 PE4
#define LEFT_CN_PIN_104 PE5
#define LEFT_CN_PIN_105 PB5
#define LEFT_CN_PIN_106 PJ4
#define LEFT_CN_PIN_107 PF6
#define LEFT_CN_PIN_108 PD5
#define LEFT_CN_PIN_109 PG1
#define LEFT_CN_PIN_110 PG0
#define LEFT_CN_PIN_111 PA7
#define LEFT_CN_PIN_112 PA6
#define LEFT_CN_PIN_113 PD7
#define LEFT_CN_PIN_114 PM0
#define LEFT_CN_PIN_115 PE4
#define LEFT_CN_PIN_116 PE5
#define LEFT_CN_PIN_117 PB5
#define LEFT_CN_PIN_118 PJ2
#define LEFT_CN_PIN_119 PF5
#define LEFT_CN_PIN_120 PE1
#define LEFT_CN_PIN_121 PB3
#define LEFT_CN_PIN_122 PB2
#define LEFT_CN_PIN_123 PR6
#define LEFT_CN_PIN_124 PR5
#define LEFT_CN_PIN_125 PN1
#define LEFT_CN_PIN_126 PR7
#define LEFT_CN_PIN_127 PA4
#define LEFT_CN_PIN_128 PA5
#define LEFT_CN_PIN_129 PA2
#define LEFT_CN_PIN_130 PE0
#define LEFT_CN_PIN_131 PB7
#define LEFT_CN_PIN_132 PE2
#define LEFT_CN_PIN_133 PB3
#define LEFT_CN_PIN_134 PB2
#define LEFT_CN_PIN_135 PA1
#define LEFT_CN_PIN_136 PA0
#define LEFT_CN_PIN_137 PB4
#define LEFT_CN_PIN_138 PD0
#define LEFT_CN_PIN_139 PA4
#define LEFT_CN_PIN_140 PA5
#define LEFT_CN_PIN_141 PA2
#define LEFT_CN_PIN_142 PE7
#define LEFT_CN_PIN_143 PB6
#define LEFT_CN_PIN_144 PE3
#define LEFT_CN_PIN_145 PK7
#define LEFT_CN_PIN_146 PM7
#define LEFT_CN_PIN_147 PM5
#define LEFT_CN_PIN_148 PM3
#define LEFT_CN_PIN_149 PM1
#define LEFT_CN_PIN_150 PN7
#define LEFT_CN_PIN_151 PN6
#define LEFT_CN_PIN_152 PN5
#define LEFT_CN_PIN_153 PN4
#define LEFT_CN_PIN_154 PN3
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
#define RIGHT_CN_PIN_017 PG5
#define RIGHT_CN_PIN_018 PG6
#define RIGHT_CN_PIN_019 PG7
#define RIGHT_CN_PIN_020     // Pin not routed.
#define RIGHT_CN_PIN_021     // Pin not routed.
#define RIGHT_CN_PIN_022     // Pin not routed.
#define RIGHT_CN_PIN_023     // Pin not routed.
#define RIGHT_CN_PIN_024     // Pin not routed.
#define RIGHT_CN_PIN_025     // Pin not routed.
#define RIGHT_CN_PIN_026     // Pin not routed.
#define RIGHT_CN_PIN_027     // Pin not routed.
#define RIGHT_CN_PIN_028 PK0
#define RIGHT_CN_PIN_029 PK1
#define RIGHT_CN_PIN_030 PK2
#define RIGHT_CN_PIN_031 PK3
#define RIGHT_CN_PIN_032 PK4
#define RIGHT_CN_PIN_033 PK5
#define RIGHT_CN_PIN_034 PK6
#define RIGHT_CN_PIN_035 PK7
#define RIGHT_CN_PIN_036 PK5
#define RIGHT_CN_PIN_037     // Pin not routed.
#define RIGHT_CN_PIN_038 PK6
#define RIGHT_CN_PIN_039     // Pin not routed.
#define RIGHT_CN_PIN_040     // Pin not routed.
#define RIGHT_CN_PIN_041     // Pin not routed.
#define RIGHT_CN_PIN_042     // Pin not routed.
#define RIGHT_CN_PIN_043 PT2
#define RIGHT_CN_PIN_044 PT3
#define RIGHT_CN_PIN_045 PM0
#define RIGHT_CN_PIN_046 PM1
#define RIGHT_CN_PIN_047 PM2
#define RIGHT_CN_PIN_048 PM3
#define RIGHT_CN_PIN_049 PM4
#define RIGHT_CN_PIN_050 PM5
#define RIGHT_CN_PIN_051 PM6
#define RIGHT_CN_PIN_052 PM7
#define RIGHT_CN_PIN_053     // Pin not routed.
#define RIGHT_CN_PIN_054     // Pin not routed.
#define RIGHT_CN_PIN_055     // Pin not routed.
#define RIGHT_CN_PIN_056     // Pin not routed.
#define RIGHT_CN_PIN_057     // Pin not routed.
#define RIGHT_CN_PIN_058     // Pin not routed.
#define RIGHT_CN_PIN_059     // Pin not routed.
#define RIGHT_CN_PIN_060     // Pin not routed.
#define RIGHT_CN_PIN_061 PR0
#define RIGHT_CN_PIN_062 PR1
#define RIGHT_CN_PIN_063 PR2
#define RIGHT_CN_PIN_064 PR3
#define RIGHT_CN_PIN_065 PR4
#define RIGHT_CN_PIN_066     // Pin not routed.
#define RIGHT_CN_PIN_067     // Pin not routed.
#define RIGHT_CN_PIN_068     // Pin not routed.
#define RIGHT_CN_PIN_069 PQ0
#define RIGHT_CN_PIN_070 PQ1
#define RIGHT_CN_PIN_071 PQ2
#define RIGHT_CN_PIN_072 PQ3
#define RIGHT_CN_PIN_073 PQ4
#define RIGHT_CN_PIN_074 PQ5
#define RIGHT_CN_PIN_075 PQ6
#define RIGHT_CN_PIN_076 PQ7
#define RIGHT_CN_PIN_077 PS0
#define RIGHT_CN_PIN_078 PS1
#define RIGHT_CN_PIN_079 PS2
#define RIGHT_CN_PIN_080 PS3
#define RIGHT_CN_PIN_081 PS4
#define RIGHT_CN_PIN_082 PS5
#define RIGHT_CN_PIN_083 PS6
#define RIGHT_CN_PIN_084 PS7
#define RIGHT_CN_PIN_085     // Pin not routed.
#define RIGHT_CN_PIN_086     // Pin not routed.
#define RIGHT_CN_PIN_087     // Pin not routed.
#define RIGHT_CN_PIN_088     // Pin not routed.
#define RIGHT_CN_PIN_089 PT3
#define RIGHT_CN_PIN_090 PT2
#define RIGHT_CN_PIN_091 PT1
#define RIGHT_CN_PIN_092 PT0
#define RIGHT_CN_PIN_093 PR7
#define RIGHT_CN_PIN_094 PR6
#define RIGHT_CN_PIN_095 PR5
#define RIGHT_CN_PIN_096 PR4
#define RIGHT_CN_PIN_097 PR3
#define RIGHT_CN_PIN_098 PR2
#define RIGHT_CN_PIN_099 PR1
#define RIGHT_CN_PIN_100 PR0
#define RIGHT_CN_PIN_101 PL5
#define RIGHT_CN_PIN_102 PL4
#define RIGHT_CN_PIN_103 PT1
#define RIGHT_CN_PIN_104 PT0
#define RIGHT_CN_PIN_105 PP5
#define RIGHT_CN_PIN_106 PP4
#define RIGHT_CN_PIN_107 PP3
#define RIGHT_CN_PIN_108 PP2
#define RIGHT_CN_PIN_109 PP7
#define RIGHT_CN_PIN_110 PP6
#define RIGHT_CN_PIN_111 PP5
#define RIGHT_CN_PIN_112 PP4
#define RIGHT_CN_PIN_113 PP3
#define RIGHT_CN_PIN_114 PP2
#define RIGHT_CN_PIN_115 PP1
#define RIGHT_CN_PIN_116 PP0
#define RIGHT_CN_PIN_117 PN7
#define RIGHT_CN_PIN_118 PN6
#define RIGHT_CN_PIN_119 PN5
#define RIGHT_CN_PIN_120 PN4
#define RIGHT_CN_PIN_121 PN3
#define RIGHT_CN_PIN_122 PN2
#define RIGHT_CN_PIN_123 PN1
#define RIGHT_CN_PIN_124 PN0
#define RIGHT_CN_PIN_125 PD2
#define RIGHT_CN_PIN_126 PD3
#define RIGHT_CN_PIN_127 PK1
#define RIGHT_CN_PIN_128 PD1
#define RIGHT_CN_PIN_129 PD6
#define RIGHT_CN_PIN_130 PB0
#define RIGHT_CN_PIN_131     // Pin not routed.
#define RIGHT_CN_PIN_132     // Pin not routed.
#define RIGHT_CN_PIN_133 PB1
#define RIGHT_CN_PIN_134     // Pin not routed.
#define RIGHT_CN_PIN_135     // Pin not routed.
#define RIGHT_CN_PIN_136 PL5
#define RIGHT_CN_PIN_137 PL4
#define RIGHT_CN_PIN_138 PL3
#define RIGHT_CN_PIN_139 PL2
#define RIGHT_CN_PIN_140 PL1
#define RIGHT_CN_PIN_141 PL0
#define RIGHT_CN_PIN_142 PJ7
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
#define RIGHT_CN_PIN_159 PP0
#define RIGHT_CN_PIN_160 PP1
#define RIGHT_CN_PIN_161 PF7
#define RIGHT_CN_PIN_162 PF6
#define RIGHT_CN_PIN_163 PF5
#define RIGHT_CN_PIN_164 PF4
#define RIGHT_CN_PIN_165 PF3
#define RIGHT_CN_PIN_166 PF2
#define RIGHT_CN_PIN_167 PF1
#define RIGHT_CN_PIN_168 PF0

#define LCD_TFT_8BIT_CH0 PORT_H
#define LCD_TFT_CH0_8BIT_MASK 0x00FF

#define LCD_TFT_16BIT_CH0 PORT_H
#define LCD_TFT_16BIT_CH0_MASK 0x00FF

#define LCD_TFT_16BIT_CH1 PORT_Q
#define LCD_TFT_16BIT_CH1_MASK 0x00FF

#ifdef __cplusplus
}
#endif

#endif // _MCU_CARD_H_
// ------------------------------------------------------------------------- END
