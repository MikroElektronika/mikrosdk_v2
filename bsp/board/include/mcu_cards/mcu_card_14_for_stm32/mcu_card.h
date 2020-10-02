/****************************************************************************
**
** Copyright (C) 2020 MikroElektronika d.o.o.
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
#define MCU_CARD_REV_MINOR (85)

#define NC HAL_PIN_NC

// Left connector
#define LEFT_CN_PIN_001 PA0
#define LEFT_CN_PIN_002 NC
#define LEFT_CN_PIN_003 NC
#define LEFT_CN_PIN_004 PA3
#define LEFT_CN_PIN_005 PA4
#define LEFT_CN_PIN_006 PA5
#define LEFT_CN_PIN_007 PA6
#define LEFT_CN_PIN_008 NC
#define LEFT_CN_PIN_009 NC
#define LEFT_CN_PIN_010 NC
#define LEFT_CN_PIN_011 NC
#define LEFT_CN_PIN_012 NC
#define LEFT_CN_PIN_013 PA9
#define LEFT_CN_PIN_014 PA10
#define LEFT_CN_PIN_015 NC
#define LEFT_CN_PIN_016 NC
#define LEFT_CN_PIN_017 PA13
#define LEFT_CN_PIN_018 PA14
#define LEFT_CN_PIN_019 PA15
#define LEFT_CN_PIN_020 NC
#define LEFT_CN_PIN_021 PE3
#define LEFT_CN_PIN_022 PE4
#define LEFT_CN_PIN_023 PE5
#define LEFT_CN_PIN_024 PE6
#define LEFT_CN_PIN_025 PF10
#define LEFT_CN_PIN_026 PE7
#define LEFT_CN_PIN_027 PG8
#define LEFT_CN_PIN_028 PB6
#define LEFT_CN_PIN_029 PB7
#define LEFT_CN_PIN_030 PE8
#define LEFT_CN_PIN_031 PE9
#define LEFT_CN_PIN_032 PE10
#define LEFT_CN_PIN_033 PE11
#define LEFT_CN_PIN_034 PE12
#define LEFT_CN_PIN_035 PE13
#define LEFT_CN_PIN_036 PE14
#define LEFT_CN_PIN_037 PE15
#define LEFT_CN_PIN_038 PG0
#define LEFT_CN_PIN_039 PG1
#define LEFT_CN_PIN_040 PG2
#define LEFT_CN_PIN_041 PG3
#define LEFT_CN_PIN_042 PG4
#define LEFT_CN_PIN_043 PG5
#define LEFT_CN_PIN_044 PG6
#define LEFT_CN_PIN_045 PG7
#define LEFT_CN_PIN_046 NC
#define LEFT_CN_PIN_047 NC
#define LEFT_CN_PIN_048 NC
#define LEFT_CN_PIN_049 NC
#define LEFT_CN_PIN_050 NC
#define LEFT_CN_PIN_051 NC
#define LEFT_CN_PIN_052 NC
#define LEFT_CN_PIN_053 NC
#define LEFT_CN_PIN_054 PC12
#define LEFT_CN_PIN_055 PD2
#define LEFT_CN_PIN_056 PD14
#define LEFT_CN_PIN_057 PD4
#define LEFT_CN_PIN_058 PB8
#define LEFT_CN_PIN_059 PB9
#define LEFT_CN_PIN_060 PD5
#define LEFT_CN_PIN_061 PD6
#define LEFT_CN_PIN_062 PG9
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
#define LEFT_CN_PIN_079 NC
#define LEFT_CN_PIN_080 NC
#define LEFT_CN_PIN_081 NC
#define LEFT_CN_PIN_082 NC
#define LEFT_CN_PIN_083 PB14
#define LEFT_CN_PIN_084 PB15
#define LEFT_CN_PIN_085 PB9
#define LEFT_CN_PIN_086 PB8
#define LEFT_CN_PIN_087 PD8
#define LEFT_CN_PIN_088 PD9
#define LEFT_CN_PIN_089 PF15
#define LEFT_CN_PIN_090 PD15
#define LEFT_CN_PIN_091 PB15
#define LEFT_CN_PIN_092 PB14
#define LEFT_CN_PIN_093 PD3
#define LEFT_CN_PIN_094 PF12
#define LEFT_CN_PIN_095 PF5
#define LEFT_CN_PIN_096 PC3
#define LEFT_CN_PIN_097 PB9
#define LEFT_CN_PIN_098 PB8
#define LEFT_CN_PIN_099 PD8
#define LEFT_CN_PIN_100 PD9
#define LEFT_CN_PIN_101 PF14
#define LEFT_CN_PIN_102 PC9
#define LEFT_CN_PIN_103 PB15
#define LEFT_CN_PIN_104 PB14
#define LEFT_CN_PIN_105 PD3
#define LEFT_CN_PIN_106 PF11
#define LEFT_CN_PIN_107 PF4
#define LEFT_CN_PIN_108 PA3
#define LEFT_CN_PIN_109 PB9
#define LEFT_CN_PIN_110 PB8
#define LEFT_CN_PIN_111 PD8
#define LEFT_CN_PIN_112 PD9
#define LEFT_CN_PIN_113 PF13
#define LEFT_CN_PIN_114 PC8
#define LEFT_CN_PIN_115 PB15
#define LEFT_CN_PIN_116 PB14
#define LEFT_CN_PIN_117 PD3
#define LEFT_CN_PIN_118 PB2
#define LEFT_CN_PIN_119 PF3
#define LEFT_CN_PIN_120 PA6
#define LEFT_CN_PIN_121 PB9
#define LEFT_CN_PIN_122 PB8
#define LEFT_CN_PIN_123 PC10
#define LEFT_CN_PIN_124 PC11
#define LEFT_CN_PIN_125 PC2
#define LEFT_CN_PIN_126 PC7
#define LEFT_CN_PIN_127 PB15
#define LEFT_CN_PIN_128 PB14
#define LEFT_CN_PIN_129 PD3
#define LEFT_CN_PIN_130 PD12
#define LEFT_CN_PIN_131 PF2
#define LEFT_CN_PIN_132 PA5
#define LEFT_CN_PIN_133 PB9
#define LEFT_CN_PIN_134 PB8
#define LEFT_CN_PIN_135 PC10
#define LEFT_CN_PIN_136 PC11
#define LEFT_CN_PIN_137 PC0
#define LEFT_CN_PIN_138 PC6
#define LEFT_CN_PIN_139 PB15
#define LEFT_CN_PIN_140 PB14
#define LEFT_CN_PIN_141 PD3
#define LEFT_CN_PIN_142 PD11
#define LEFT_CN_PIN_143 PC13
#define LEFT_CN_PIN_144 PA4
#define LEFT_CN_PIN_145 PB5
#define LEFT_CN_PIN_146 PB4
#define LEFT_CN_PIN_147 PB3
#define LEFT_CN_PIN_148 PG12
#define LEFT_CN_PIN_149 PG11
#define LEFT_CN_PIN_150 PG10
#define LEFT_CN_PIN_151 PA15
#define LEFT_CN_PIN_152 PA14
#define LEFT_CN_PIN_153 PA13
#define LEFT_CN_PIN_154 PA0
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
#define RIGHT_CN_PIN_001 PC0
#define RIGHT_CN_PIN_002 NC
#define RIGHT_CN_PIN_003 PC2
#define RIGHT_CN_PIN_004 PC3
#define RIGHT_CN_PIN_005 NC
#define RIGHT_CN_PIN_006 NC
#define RIGHT_CN_PIN_007 PC6
#define RIGHT_CN_PIN_008 PC7
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
#define RIGHT_CN_PIN_019 NC
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
#define RIGHT_CN_PIN_043 PD0
#define RIGHT_CN_PIN_044 PD1
#define RIGHT_CN_PIN_045 PG0
#define RIGHT_CN_PIN_046 PG1
#define RIGHT_CN_PIN_047 PG2
#define RIGHT_CN_PIN_048 PG3
#define RIGHT_CN_PIN_049 PG4
#define RIGHT_CN_PIN_050 PG5
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
#define RIGHT_CN_PIN_102 PD4
#define RIGHT_CN_PIN_103 PD14
#define RIGHT_CN_PIN_104 PF1
#define RIGHT_CN_PIN_105 PF0
#define RIGHT_CN_PIN_106 PE2
#define RIGHT_CN_PIN_107 PE1
#define RIGHT_CN_PIN_108 PE0
#define RIGHT_CN_PIN_109 NC
#define RIGHT_CN_PIN_110 NC
#define RIGHT_CN_PIN_111 NC
#define RIGHT_CN_PIN_112 NC
#define RIGHT_CN_PIN_113 NC
#define RIGHT_CN_PIN_114 NC
#define RIGHT_CN_PIN_115 NC
#define RIGHT_CN_PIN_116 NC
#define RIGHT_CN_PIN_117 PG15
#define RIGHT_CN_PIN_118 NC
#define RIGHT_CN_PIN_119 NC
#define RIGHT_CN_PIN_120 PG12
#define RIGHT_CN_PIN_121 PG11
#define RIGHT_CN_PIN_122 PG10
#define RIGHT_CN_PIN_123 PG9
#define RIGHT_CN_PIN_124 PG8
#define RIGHT_CN_PIN_125 PA3
#define RIGHT_CN_PIN_126 PA6
#define RIGHT_CN_PIN_127 PB1
#define RIGHT_CN_PIN_128 PB0
#define RIGHT_CN_PIN_129 PG15
#define RIGHT_CN_PIN_130 PA10
#define RIGHT_CN_PIN_131 NC
#define RIGHT_CN_PIN_132 NC
#define RIGHT_CN_PIN_133 PA9
#define RIGHT_CN_PIN_134 PF15
#define RIGHT_CN_PIN_135 PF14
#define RIGHT_CN_PIN_136 PF13
#define RIGHT_CN_PIN_137 PF12
#define RIGHT_CN_PIN_138 PF11
#define RIGHT_CN_PIN_139 PF10
#define RIGHT_CN_PIN_140 NC
#define RIGHT_CN_PIN_141 NC
#define RIGHT_CN_PIN_142 PE15
#define RIGHT_CN_PIN_143 PE14
#define RIGHT_CN_PIN_144 PE13
#define RIGHT_CN_PIN_145 PE12
#define RIGHT_CN_PIN_146 PE11
#define RIGHT_CN_PIN_147 PE10
#define RIGHT_CN_PIN_148 PE9
#define RIGHT_CN_PIN_149 PE8
#define RIGHT_CN_PIN_150 PD15
#define RIGHT_CN_PIN_151 PD14
#define RIGHT_CN_PIN_152 NC
#define RIGHT_CN_PIN_153 PD12
#define RIGHT_CN_PIN_154 PD11
#define RIGHT_CN_PIN_155 NC
#define RIGHT_CN_PIN_156 PD9
#define RIGHT_CN_PIN_157 PD8
#define RIGHT_CN_PIN_158 NC
#define RIGHT_CN_PIN_159 PD9
#define RIGHT_CN_PIN_160 PD8
#define RIGHT_CN_PIN_161 NC
#define RIGHT_CN_PIN_162 NC
#define RIGHT_CN_PIN_163 PC13
#define RIGHT_CN_PIN_164 PC12
#define RIGHT_CN_PIN_165 PC11
#define RIGHT_CN_PIN_166 PC10
#define RIGHT_CN_PIN_167 PC9
#define RIGHT_CN_PIN_168 PC8

#define LCD_TFT_8BIT_CH0 PORT_E
#define LCD_TFT_CH0_8BIT_MASK 0x00FF

#define LCD_TFT_16BIT_CH0 PORT_E
#define LCD_TFT_16BIT_CH0_MASK 0x00FF

#define LCD_TFT_16BIT_CH1 PORT_G
#define LCD_TFT_16BIT_CH1_MASK 0x00FF

// Ethernet
#define ETH_RXD0   PC4
#define ETH_RXD1   PC5
#define ETH_TXD0   PB12
#define ETH_TXD1   PB13
#define ETH_TXEN   PB11
#define ETH_CRS_DV PA7
#define ETH_RXER   PB10
#define ETH_MDIO   PA2
#define ETH_MDC    PC1
#define ETH_NINT   PB14
#define ETH_CLK    PA8
#define ETH_RST    NC

#ifdef __cplusplus
}
#endif

#endif // _MCU_CARD_H_
// ------------------------------------------------------------------------- END
