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
#define LEFT_CN_PIN_015     // Pin not routed.
#define LEFT_CN_PIN_016     // Pin not routed.
#define LEFT_CN_PIN_017 PA13
#define LEFT_CN_PIN_018 PA14
#define LEFT_CN_PIN_019 PA15
#define LEFT_CN_PIN_020     // Pin not routed.
#define LEFT_CN_PIN_021     // Pin not routed.
#define LEFT_CN_PIN_022     // Pin not routed.
#define LEFT_CN_PIN_023     // Pin not routed.
#define LEFT_CN_PIN_024     // Pin not routed.
#define LEFT_CN_PIN_025 PC3
#define LEFT_CN_PIN_026 PA4
#define LEFT_CN_PIN_027 PC9
#define LEFT_CN_PIN_028 PA8
#define LEFT_CN_PIN_029 PC12
#define LEFT_CN_PIN_030 PB0
#define LEFT_CN_PIN_031 PB1
#define LEFT_CN_PIN_032 PB2
#define LEFT_CN_PIN_033 PB3
#define LEFT_CN_PIN_034 PB4
#define LEFT_CN_PIN_035 PB5
#define LEFT_CN_PIN_036 PB6
#define LEFT_CN_PIN_037 PB7
#define LEFT_CN_PIN_038     // Pin not routed.
#define LEFT_CN_PIN_039     // Pin not routed.
#define LEFT_CN_PIN_040     // Pin not routed.
#define LEFT_CN_PIN_041     // Pin not routed.
#define LEFT_CN_PIN_042     // Pin not routed.
#define LEFT_CN_PIN_043     // Pin not routed.
#define LEFT_CN_PIN_044     // Pin not routed.
#define LEFT_CN_PIN_045     // Pin not routed.
#define LEFT_CN_PIN_046     // Pin not routed.
#define LEFT_CN_PIN_047     // Pin not routed.
#define LEFT_CN_PIN_048     // Pin not routed.
#define LEFT_CN_PIN_049     // Pin not routed.
#define LEFT_CN_PIN_050     // Pin not routed.
#define LEFT_CN_PIN_051     // Pin not routed.
#define LEFT_CN_PIN_052     // Pin not routed.
#define LEFT_CN_PIN_053     // Pin not routed.
#define LEFT_CN_PIN_054 PA0
#define LEFT_CN_PIN_055 PC4
#define LEFT_CN_PIN_056 PB14
#define LEFT_CN_PIN_057 PD2
#define LEFT_CN_PIN_058 PF6
#define LEFT_CN_PIN_059 PF7
#define LEFT_CN_PIN_060 PA3
#define LEFT_CN_PIN_061 PC6
#define LEFT_CN_PIN_062 PC7
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
#define LEFT_CN_PIN_079     // Pin not routed.
#define LEFT_CN_PIN_080     // Pin not routed.
#define LEFT_CN_PIN_081     // Pin not routed.
#define LEFT_CN_PIN_082     // Pin not routed.
#define LEFT_CN_PIN_083 PB14
#define LEFT_CN_PIN_084 PB15
#define LEFT_CN_PIN_085 PF7
#define LEFT_CN_PIN_086 PF6
#define LEFT_CN_PIN_087 PC10
#define LEFT_CN_PIN_088 PC11
#define LEFT_CN_PIN_089 PB1
#define LEFT_CN_PIN_090 PC4
#define LEFT_CN_PIN_091 PA7
#define LEFT_CN_PIN_092 PA6
#define LEFT_CN_PIN_093 PA5
#define LEFT_CN_PIN_094 PB0
#define LEFT_CN_PIN_095 PD2
#define LEFT_CN_PIN_096 PA0
#define LEFT_CN_PIN_097 PF7
#define LEFT_CN_PIN_098 PF6
#define LEFT_CN_PIN_099 PC10
#define LEFT_CN_PIN_100 PC11
#define LEFT_CN_PIN_101 PC12
#define LEFT_CN_PIN_102 PA4
#define LEFT_CN_PIN_103 PA7
#define LEFT_CN_PIN_104 PA6
#define LEFT_CN_PIN_105 PA5
#define LEFT_CN_PIN_106 PA8
#define LEFT_CN_PIN_107 PC9
#define LEFT_CN_PIN_108 PC3
#define LEFT_CN_PIN_109 PF7
#define LEFT_CN_PIN_110 PF6
#define LEFT_CN_PIN_111 PC10
#define LEFT_CN_PIN_112 PC11
#define LEFT_CN_PIN_113 PC8
#define LEFT_CN_PIN_114 PA3
#define LEFT_CN_PIN_115 PA7
#define LEFT_CN_PIN_116 PA6
#define LEFT_CN_PIN_117 PA5
#define LEFT_CN_PIN_118 PC7
#define LEFT_CN_PIN_119 PC6
#define LEFT_CN_PIN_120 PC2
#define LEFT_CN_PIN_121 PF7
#define LEFT_CN_PIN_122 PF6
#define LEFT_CN_PIN_123 PA9
#define LEFT_CN_PIN_124 PA10
#define LEFT_CN_PIN_125 PD8
#define LEFT_CN_PIN_126 PA2
#define LEFT_CN_PIN_127 PA7
#define LEFT_CN_PIN_128 PA6
#define LEFT_CN_PIN_129 PA5
#define LEFT_CN_PIN_130 PB15
#define LEFT_CN_PIN_131 PE9
#define LEFT_CN_PIN_132 PC1
#define LEFT_CN_PIN_133 PF7
#define LEFT_CN_PIN_134 PF6
#define LEFT_CN_PIN_135 PA9
#define LEFT_CN_PIN_136 PA10
#define LEFT_CN_PIN_137 PE8
#define LEFT_CN_PIN_138 PA1
#define LEFT_CN_PIN_139 PA7
#define LEFT_CN_PIN_140 PA6
#define LEFT_CN_PIN_141 PA5
#define LEFT_CN_PIN_142 PC5
#define LEFT_CN_PIN_143 PC13
#define LEFT_CN_PIN_144 PC0
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
#define RIGHT_CN_PIN_012     // Pin not routed.
#define RIGHT_CN_PIN_013     // Pin not routed.
#define RIGHT_CN_PIN_014 PD2
#define RIGHT_CN_PIN_015     // Pin not routed.
#define RIGHT_CN_PIN_016     // Pin not routed.
#define RIGHT_CN_PIN_017     // Pin not routed.
#define RIGHT_CN_PIN_018     // Pin not routed.
#define RIGHT_CN_PIN_019     // Pin not routed.
#define RIGHT_CN_PIN_020     // Pin not routed.
#define RIGHT_CN_PIN_021     // Pin not routed.
#define RIGHT_CN_PIN_022     // Pin not routed.
#define RIGHT_CN_PIN_023     // Pin not routed.
#define RIGHT_CN_PIN_024     // Pin not routed.
#define RIGHT_CN_PIN_025     // Pin not routed.
#define RIGHT_CN_PIN_026     // Pin not routed.
#define RIGHT_CN_PIN_027     // Pin not routed.
#define RIGHT_CN_PIN_028     // Pin not routed.
#define RIGHT_CN_PIN_029     // Pin not routed.
#define RIGHT_CN_PIN_030     // Pin not routed.
#define RIGHT_CN_PIN_031     // Pin not routed.
#define RIGHT_CN_PIN_032     // Pin not routed.
#define RIGHT_CN_PIN_033     // Pin not routed.
#define RIGHT_CN_PIN_034 PF6
#define RIGHT_CN_PIN_035 PF7
#define RIGHT_CN_PIN_036     // Pin not routed.
#define RIGHT_CN_PIN_037     // Pin not routed.
#define RIGHT_CN_PIN_038     // Pin not routed.
#define RIGHT_CN_PIN_039     // Pin not routed.
#define RIGHT_CN_PIN_040     // Pin not routed.
#define RIGHT_CN_PIN_041     // Pin not routed.
#define RIGHT_CN_PIN_042     // Pin not routed.
#define RIGHT_CN_PIN_043 PB8
#define RIGHT_CN_PIN_044 PB9
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
#define RIGHT_CN_PIN_125 PC3
#define RIGHT_CN_PIN_126 PC2
#define RIGHT_CN_PIN_127 PC1
#define RIGHT_CN_PIN_128 PC0
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
#define RIGHT_CN_PIN_145     // Pin not routed.
#define RIGHT_CN_PIN_146     // Pin not routed.
#define RIGHT_CN_PIN_147     // Pin not routed.
#define RIGHT_CN_PIN_148 PE9
#define RIGHT_CN_PIN_149 PE8
#define RIGHT_CN_PIN_150     // Pin not routed.
#define RIGHT_CN_PIN_151     // Pin not routed.
#define RIGHT_CN_PIN_152     // Pin not routed.
#define RIGHT_CN_PIN_153     // Pin not routed.
#define RIGHT_CN_PIN_154     // Pin not routed.
#define RIGHT_CN_PIN_155     // Pin not routed.
#define RIGHT_CN_PIN_156     // Pin not routed.
#define RIGHT_CN_PIN_157 PD8
#define RIGHT_CN_PIN_158     // Pin not routed.
#define RIGHT_CN_PIN_159 PC11
#define RIGHT_CN_PIN_160 PC10
#define RIGHT_CN_PIN_161     // Pin not routed.
#define RIGHT_CN_PIN_162     // Pin not routed.
#define RIGHT_CN_PIN_163 PC13
#define RIGHT_CN_PIN_164 PC12
#define RIGHT_CN_PIN_165 PC11
#define RIGHT_CN_PIN_166 PC10
#define RIGHT_CN_PIN_167 PC9
#define RIGHT_CN_PIN_168 PC8

#define LCD_TFT_8BIT_CH0 PORT_B
#define LCD_TFT_CH0_8BIT_MASK 0x00FF

#define LCD_TFT_16BIT_CH0 HAL_PORT_NC
#define LCD_TFT_16BIT_CH0_MASK 0x0000

#define LCD_TFT_16BIT_CH1 HAL_PORT_NC
#define LCD_TFT_16BIT_CH1_MASK 0x0000

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
#define ETH_RST    HAL_PIN_NC

#ifdef __cplusplus
}
#endif

#endif // _MCU_CARD_H_
// ------------------------------------------------------------------------- END
