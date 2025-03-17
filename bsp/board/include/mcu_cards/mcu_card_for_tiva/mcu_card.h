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
** EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES
** OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT.
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
#define LEFT_CN_PIN_001 GPIO_PA0
#define LEFT_CN_PIN_002 GPIO_PA1
#define LEFT_CN_PIN_003 GPIO_PA2
#define LEFT_CN_PIN_004 GPIO_PA3
#define LEFT_CN_PIN_005 GPIO_PA4
#define LEFT_CN_PIN_006 GPIO_PA5
#define LEFT_CN_PIN_007 GPIO_PA6
#define LEFT_CN_PIN_008 GPIO_PA7
#define LEFT_CN_PIN_009     // Pin not routed.
#define LEFT_CN_PIN_010     // Pin not routed.
#define LEFT_CN_PIN_011     // Pin not routed.
#define LEFT_CN_PIN_012 GPIO_PB0
#define LEFT_CN_PIN_013 GPIO_PB1
#define LEFT_CN_PIN_014 GPIO_PB2
#define LEFT_CN_PIN_015 GPIO_PB3
#define LEFT_CN_PIN_016 GPIO_PB4
#define LEFT_CN_PIN_017 GPIO_PB5
#define LEFT_CN_PIN_018 GPIO_PB6
#define LEFT_CN_PIN_019 GPIO_PB7
#define LEFT_CN_PIN_020     // Pin not routed.
#define LEFT_CN_PIN_021 GPIO_PL0
#define LEFT_CN_PIN_022 GPIO_PL1
#define LEFT_CN_PIN_023 GPIO_PL2
#define LEFT_CN_PIN_024 GPIO_PL3
#define LEFT_CN_PIN_025 GPIO_PC4
#define LEFT_CN_PIN_026 GPIO_PC5
#define LEFT_CN_PIN_027 GPIO_PC6
#define LEFT_CN_PIN_028 GPIO_PC7
#define LEFT_CN_PIN_029 GPIO_PE6
#define LEFT_CN_PIN_030 GPIO_PH0
#define LEFT_CN_PIN_031 GPIO_PH1
#define LEFT_CN_PIN_032 GPIO_PH2
#define LEFT_CN_PIN_033 GPIO_PH3
#define LEFT_CN_PIN_034 GPIO_PH4
#define LEFT_CN_PIN_035 GPIO_PH5
#define LEFT_CN_PIN_036 GPIO_PH6
#define LEFT_CN_PIN_037 GPIO_PH7
#define LEFT_CN_PIN_038 GPIO_PQ0
#define LEFT_CN_PIN_039 GPIO_PQ1
#define LEFT_CN_PIN_040 GPIO_PQ2
#define LEFT_CN_PIN_041 GPIO_PQ3
#define LEFT_CN_PIN_042 GPIO_PQ4
#define LEFT_CN_PIN_043 GPIO_PQ5
#define LEFT_CN_PIN_044 GPIO_PQ6
#define LEFT_CN_PIN_045 GPIO_PQ7
#define LEFT_CN_PIN_046 GPIO_PS0
#define LEFT_CN_PIN_047 GPIO_PS1
#define LEFT_CN_PIN_048 GPIO_PS2
#define LEFT_CN_PIN_049 GPIO_PS3
#define LEFT_CN_PIN_050 GPIO_PS4
#define LEFT_CN_PIN_051 GPIO_PS5
#define LEFT_CN_PIN_052 GPIO_PS6
#define LEFT_CN_PIN_053 GPIO_PS7
#define LEFT_CN_PIN_054 GPIO_PG7
#define LEFT_CN_PIN_055 GPIO_PK3
#define LEFT_CN_PIN_056 GPIO_PM6
#define LEFT_CN_PIN_057 GPIO_PK4
#define LEFT_CN_PIN_058 GPIO_PG2
#define LEFT_CN_PIN_059 GPIO_PG3
#define LEFT_CN_PIN_060 GPIO_PG4
#define LEFT_CN_PIN_061 GPIO_PG5
#define LEFT_CN_PIN_062 GPIO_PG6
#define LEFT_CN_PIN_063 GPIO_PK2
#define LEFT_CN_PIN_064 GPIO_PP6
#define LEFT_CN_PIN_065 GPIO_PP7
#define LEFT_CN_PIN_066     // Pin not routed.
#define LEFT_CN_PIN_067     // Pin not routed.
#define LEFT_CN_PIN_068     // Pin not routed.
#define LEFT_CN_PIN_069 GPIO_PC0
#define LEFT_CN_PIN_070 GPIO_PC1
#define LEFT_CN_PIN_071 GPIO_PC2
#define LEFT_CN_PIN_072 GPIO_PC3
#define LEFT_CN_PIN_073 GPIO_PC4
#define LEFT_CN_PIN_074 GPIO_PC5
#define LEFT_CN_PIN_075 GPIO_PC6
#define LEFT_CN_PIN_076 GPIO_PC7
#define LEFT_CN_PIN_077 GPIO_PD0
#define LEFT_CN_PIN_078 GPIO_PD1
#define LEFT_CN_PIN_079 GPIO_PD2
#define LEFT_CN_PIN_080 GPIO_PD3
#define LEFT_CN_PIN_081 GPIO_PD4
#define LEFT_CN_PIN_082 GPIO_PD5
#define LEFT_CN_PIN_083 GPIO_PD6
#define LEFT_CN_PIN_084 GPIO_PD7
#define LEFT_CN_PIN_085 GPIO_PG1
#define LEFT_CN_PIN_086 GPIO_PG0
#define LEFT_CN_PIN_087 GPIO_PA3
#define LEFT_CN_PIN_088 GPIO_PK0
#define LEFT_CN_PIN_089 GPIO_PJ7
#define LEFT_CN_PIN_090 GPIO_PM4
#define LEFT_CN_PIN_091 GPIO_PE4
#define LEFT_CN_PIN_092 GPIO_PE5
#define LEFT_CN_PIN_093 GPIO_PB5
#define LEFT_CN_PIN_094 GPIO_PJ6
#define LEFT_CN_PIN_095 GPIO_PF7
#define LEFT_CN_PIN_096 GPIO_PD4
#define LEFT_CN_PIN_097 GPIO_PG1
#define LEFT_CN_PIN_098 GPIO_PG0
#define LEFT_CN_PIN_099 GPIO_PJ1
#define LEFT_CN_PIN_100 GPIO_PJ0
#define LEFT_CN_PIN_101 GPIO_PJ5
#define LEFT_CN_PIN_102 GPIO_PM2
#define LEFT_CN_PIN_103 GPIO_PE4
#define LEFT_CN_PIN_104 GPIO_PE5
#define LEFT_CN_PIN_105 GPIO_PB5
#define LEFT_CN_PIN_106 GPIO_PJ4
#define LEFT_CN_PIN_107 GPIO_PF6
#define LEFT_CN_PIN_108 GPIO_PD5
#define LEFT_CN_PIN_109 GPIO_PG1
#define LEFT_CN_PIN_110 GPIO_PG0
#define LEFT_CN_PIN_111 GPIO_PA7
#define LEFT_CN_PIN_112 GPIO_PA6
#define LEFT_CN_PIN_113 GPIO_PD7
#define LEFT_CN_PIN_114 GPIO_PM0
#define LEFT_CN_PIN_115 GPIO_PE4
#define LEFT_CN_PIN_116 GPIO_PE5
#define LEFT_CN_PIN_117 GPIO_PB5
#define LEFT_CN_PIN_118 GPIO_PJ2
#define LEFT_CN_PIN_119 GPIO_PF5
#define LEFT_CN_PIN_120 GPIO_PE1
#define LEFT_CN_PIN_121 GPIO_PB3
#define LEFT_CN_PIN_122 GPIO_PB2
#define LEFT_CN_PIN_123 GPIO_PR6
#define LEFT_CN_PIN_124 GPIO_PR5
#define LEFT_CN_PIN_125 GPIO_PN1
#define LEFT_CN_PIN_126 GPIO_PR7
#define LEFT_CN_PIN_127 GPIO_PA4
#define LEFT_CN_PIN_128 GPIO_PA5
#define LEFT_CN_PIN_129 GPIO_PA2
#define LEFT_CN_PIN_130 GPIO_PE0
#define LEFT_CN_PIN_131 GPIO_PB7
#define LEFT_CN_PIN_132 GPIO_PE2
#define LEFT_CN_PIN_133 GPIO_PB3
#define LEFT_CN_PIN_134 GPIO_PB2
#define LEFT_CN_PIN_135 GPIO_PA1
#define LEFT_CN_PIN_136 GPIO_PA0
#define LEFT_CN_PIN_137 GPIO_PB4
#define LEFT_CN_PIN_138 GPIO_PD0
#define LEFT_CN_PIN_139 GPIO_PA4
#define LEFT_CN_PIN_140 GPIO_PA5
#define LEFT_CN_PIN_141 GPIO_PA2
#define LEFT_CN_PIN_142 GPIO_PE7
#define LEFT_CN_PIN_143 GPIO_PB6
#define LEFT_CN_PIN_144 GPIO_PE3
#define LEFT_CN_PIN_145 GPIO_PK7
#define LEFT_CN_PIN_146 GPIO_PM7
#define LEFT_CN_PIN_147 GPIO_PM5
#define LEFT_CN_PIN_148 GPIO_PM3
#define LEFT_CN_PIN_149 GPIO_PM1
#define LEFT_CN_PIN_150 GPIO_PN7
#define LEFT_CN_PIN_151 GPIO_PN6
#define LEFT_CN_PIN_152 GPIO_PN5
#define LEFT_CN_PIN_153 GPIO_PN4
#define LEFT_CN_PIN_154 GPIO_PN3
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
#define RIGHT_CN_PIN_001 GPIO_PE0
#define RIGHT_CN_PIN_002 GPIO_PE1
#define RIGHT_CN_PIN_003 GPIO_PE2
#define RIGHT_CN_PIN_004 GPIO_PE3
#define RIGHT_CN_PIN_005 GPIO_PE4
#define RIGHT_CN_PIN_006 GPIO_PE5
#define RIGHT_CN_PIN_007 GPIO_PE6
#define RIGHT_CN_PIN_008 GPIO_PE7
#define RIGHT_CN_PIN_009     // Pin not routed.
#define RIGHT_CN_PIN_010     // Pin not routed.
#define RIGHT_CN_PIN_011     // Pin not routed.
#define RIGHT_CN_PIN_012 GPIO_PG0
#define RIGHT_CN_PIN_013 GPIO_PG1
#define RIGHT_CN_PIN_014 GPIO_PG2
#define RIGHT_CN_PIN_015 GPIO_PG3
#define RIGHT_CN_PIN_016 GPIO_PG4
#define RIGHT_CN_PIN_017 GPIO_PG5
#define RIGHT_CN_PIN_018 GPIO_PG6
#define RIGHT_CN_PIN_019 GPIO_PG7
#define RIGHT_CN_PIN_020     // Pin not routed.
#define RIGHT_CN_PIN_021     // Pin not routed.
#define RIGHT_CN_PIN_022     // Pin not routed.
#define RIGHT_CN_PIN_023     // Pin not routed.
#define RIGHT_CN_PIN_024     // Pin not routed.
#define RIGHT_CN_PIN_025     // Pin not routed.
#define RIGHT_CN_PIN_026     // Pin not routed.
#define RIGHT_CN_PIN_027     // Pin not routed.
#define RIGHT_CN_PIN_028 GPIO_PK0
#define RIGHT_CN_PIN_029 GPIO_PK1
#define RIGHT_CN_PIN_030 GPIO_PK2
#define RIGHT_CN_PIN_031 GPIO_PK3
#define RIGHT_CN_PIN_032 GPIO_PK4
#define RIGHT_CN_PIN_033 GPIO_PK5
#define RIGHT_CN_PIN_034 GPIO_PK6
#define RIGHT_CN_PIN_035 GPIO_PK7
#define RIGHT_CN_PIN_036 GPIO_PK5
#define RIGHT_CN_PIN_037     // Pin not routed.
#define RIGHT_CN_PIN_038 GPIO_PK6
#define RIGHT_CN_PIN_039     // Pin not routed.
#define RIGHT_CN_PIN_040     // Pin not routed.
#define RIGHT_CN_PIN_041     // Pin not routed.
#define RIGHT_CN_PIN_042     // Pin not routed.
#define RIGHT_CN_PIN_043 GPIO_PT2
#define RIGHT_CN_PIN_044 GPIO_PT3
#define RIGHT_CN_PIN_045 GPIO_PM0
#define RIGHT_CN_PIN_046 GPIO_PM1
#define RIGHT_CN_PIN_047 GPIO_PM2
#define RIGHT_CN_PIN_048 GPIO_PM3
#define RIGHT_CN_PIN_049 GPIO_PM4
#define RIGHT_CN_PIN_050 GPIO_PM5
#define RIGHT_CN_PIN_051 GPIO_PM6
#define RIGHT_CN_PIN_052 GPIO_PM7
#define RIGHT_CN_PIN_053     // Pin not routed.
#define RIGHT_CN_PIN_054     // Pin not routed.
#define RIGHT_CN_PIN_055     // Pin not routed.
#define RIGHT_CN_PIN_056     // Pin not routed.
#define RIGHT_CN_PIN_057     // Pin not routed.
#define RIGHT_CN_PIN_058     // Pin not routed.
#define RIGHT_CN_PIN_059     // Pin not routed.
#define RIGHT_CN_PIN_060     // Pin not routed.
#define RIGHT_CN_PIN_061 GPIO_PR0
#define RIGHT_CN_PIN_062 GPIO_PR1
#define RIGHT_CN_PIN_063 GPIO_PR2
#define RIGHT_CN_PIN_064 GPIO_PR3
#define RIGHT_CN_PIN_065 GPIO_PR4
#define RIGHT_CN_PIN_066     // Pin not routed.
#define RIGHT_CN_PIN_067     // Pin not routed.
#define RIGHT_CN_PIN_068     // Pin not routed.
#define RIGHT_CN_PIN_069 GPIO_PQ0
#define RIGHT_CN_PIN_070 GPIO_PQ1
#define RIGHT_CN_PIN_071 GPIO_PQ2
#define RIGHT_CN_PIN_072 GPIO_PQ3
#define RIGHT_CN_PIN_073 GPIO_PQ4
#define RIGHT_CN_PIN_074 GPIO_PQ5
#define RIGHT_CN_PIN_075 GPIO_PQ6
#define RIGHT_CN_PIN_076 GPIO_PQ7
#define RIGHT_CN_PIN_077 GPIO_PS0
#define RIGHT_CN_PIN_078 GPIO_PS1
#define RIGHT_CN_PIN_079 GPIO_PS2
#define RIGHT_CN_PIN_080 GPIO_PS3
#define RIGHT_CN_PIN_081 GPIO_PS4
#define RIGHT_CN_PIN_082 GPIO_PS5
#define RIGHT_CN_PIN_083 GPIO_PS6
#define RIGHT_CN_PIN_084 GPIO_PS7
#define RIGHT_CN_PIN_085     // Pin not routed.
#define RIGHT_CN_PIN_086     // Pin not routed.
#define RIGHT_CN_PIN_087     // Pin not routed.
#define RIGHT_CN_PIN_088     // Pin not routed.
#define RIGHT_CN_PIN_089 GPIO_PT3
#define RIGHT_CN_PIN_090 GPIO_PT2
#define RIGHT_CN_PIN_091 GPIO_PT1
#define RIGHT_CN_PIN_092 GPIO_PT0
#define RIGHT_CN_PIN_093 GPIO_PR7
#define RIGHT_CN_PIN_094 GPIO_PR6
#define RIGHT_CN_PIN_095 GPIO_PR5
#define RIGHT_CN_PIN_096 GPIO_PR4
#define RIGHT_CN_PIN_097 GPIO_PR3
#define RIGHT_CN_PIN_098 GPIO_PR2
#define RIGHT_CN_PIN_099 GPIO_PR1
#define RIGHT_CN_PIN_100 GPIO_PR0
#define RIGHT_CN_PIN_101 GPIO_PL5
#define RIGHT_CN_PIN_102 GPIO_PL4
#define RIGHT_CN_PIN_103 GPIO_PT1
#define RIGHT_CN_PIN_104 GPIO_PT0
#define RIGHT_CN_PIN_105 GPIO_PP5
#define RIGHT_CN_PIN_106 GPIO_PP4
#define RIGHT_CN_PIN_107 GPIO_PP3
#define RIGHT_CN_PIN_108 GPIO_PP2
#define RIGHT_CN_PIN_109 GPIO_PP7
#define RIGHT_CN_PIN_110 GPIO_PP6
#define RIGHT_CN_PIN_111 GPIO_PP5
#define RIGHT_CN_PIN_112 GPIO_PP4
#define RIGHT_CN_PIN_113 GPIO_PP3
#define RIGHT_CN_PIN_114 GPIO_PP2
#define RIGHT_CN_PIN_115 GPIO_PP1
#define RIGHT_CN_PIN_116 GPIO_PP0
#define RIGHT_CN_PIN_117 GPIO_PN7
#define RIGHT_CN_PIN_118 GPIO_PN6
#define RIGHT_CN_PIN_119 GPIO_PN5
#define RIGHT_CN_PIN_120 GPIO_PN4
#define RIGHT_CN_PIN_121 GPIO_PN3
#define RIGHT_CN_PIN_122 GPIO_PN2
#define RIGHT_CN_PIN_123 GPIO_PN1
#define RIGHT_CN_PIN_124 GPIO_PN0
#define RIGHT_CN_PIN_125 GPIO_PD2
#define RIGHT_CN_PIN_126 GPIO_PD3
#define RIGHT_CN_PIN_127 GPIO_PK1
#define RIGHT_CN_PIN_128 GPIO_PD1
#define RIGHT_CN_PIN_129 GPIO_PD6
#define RIGHT_CN_PIN_130 GPIO_PB0
#define RIGHT_CN_PIN_131     // Pin not routed.
#define RIGHT_CN_PIN_132     // Pin not routed.
#define RIGHT_CN_PIN_133 GPIO_PB1
#define RIGHT_CN_PIN_134     // Pin not routed.
#define RIGHT_CN_PIN_135     // Pin not routed.
#define RIGHT_CN_PIN_136 GPIO_PL5
#define RIGHT_CN_PIN_137 GPIO_PL4
#define RIGHT_CN_PIN_138 GPIO_PL3
#define RIGHT_CN_PIN_139 GPIO_PL2
#define RIGHT_CN_PIN_140 GPIO_PL1
#define RIGHT_CN_PIN_141 GPIO_PL0
#define RIGHT_CN_PIN_142 GPIO_PJ7
#define RIGHT_CN_PIN_143 GPIO_PJ6
#define RIGHT_CN_PIN_144 GPIO_PJ5
#define RIGHT_CN_PIN_145 GPIO_PJ4
#define RIGHT_CN_PIN_146 GPIO_PJ3
#define RIGHT_CN_PIN_147 GPIO_PJ2
#define RIGHT_CN_PIN_148 GPIO_PJ1
#define RIGHT_CN_PIN_149 GPIO_PJ0
#define RIGHT_CN_PIN_150 GPIO_PH7
#define RIGHT_CN_PIN_151 GPIO_PH6
#define RIGHT_CN_PIN_152 GPIO_PH5
#define RIGHT_CN_PIN_153 GPIO_PH4
#define RIGHT_CN_PIN_154 GPIO_PH3
#define RIGHT_CN_PIN_155 GPIO_PH2
#define RIGHT_CN_PIN_156 GPIO_PH1
#define RIGHT_CN_PIN_157 GPIO_PH0
#define RIGHT_CN_PIN_158     // Pin not routed.
#define RIGHT_CN_PIN_159 GPIO_PP0
#define RIGHT_CN_PIN_160 GPIO_PP1
#define RIGHT_CN_PIN_161 GPIO_PF7
#define RIGHT_CN_PIN_162 GPIO_PF6
#define RIGHT_CN_PIN_163 GPIO_PF5
#define RIGHT_CN_PIN_164 GPIO_PF4
#define RIGHT_CN_PIN_165 GPIO_PF3
#define RIGHT_CN_PIN_166 GPIO_PF2
#define RIGHT_CN_PIN_167 GPIO_PF1
#define RIGHT_CN_PIN_168 GPIO_PF0

#define LCD_TFT_8BIT_CH0 GPIO_PORT_H
#define LCD_TFT_CH0_8BIT_MASK 0x00FF

#define LCD_TFT_16BIT_CH0 GPIO_PORT_H
#define LCD_TFT_16BIT_CH0_MASK 0x00FF

#define LCD_TFT_16BIT_CH1 GPIO_PORT_Q
#define LCD_TFT_16BIT_CH1_MASK 0x00FF

#ifdef __cplusplus
}
#endif

#endif // _MCU_CARD_H_
// ------------------------------------------------------------------------- END
