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
** EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES
** OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT.
** IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM,
** DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT
** OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE
** OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
**
****************************************************************************/
/*!
 * @file  hal_ll_pin_names.h
 * @brief Header file containing symbolic pin name definitions.
 */

#ifndef _HAL_LL_PIN_NAMES_H_
#define _HAL_LL_PIN_NAMES_H_

#ifdef __cplusplus
extern "C"{
#endif

#include "mcu_definitions.h"
#include "hal_ll_target_names.h"

#define GPIO_FEATURE_8BIT_PORT

// PORT 0
#ifdef __P000_CN
#define GPIO_P000 (0x00)
#endif
#ifdef __P001_CN
#define GPIO_P001 (0x01)
#endif
#ifdef __P002_CN
#define GPIO_P002 (0x02)
#endif
#ifdef __P003_CN
#define GPIO_P003 (0x03)
#endif
#ifdef __P004_CN
#define GPIO_P004 (0x04)
#endif
#ifdef __P005_CN
#define GPIO_P005 (0x05)
#endif
#ifdef __P006_CN
#define GPIO_P006 (0x06)
#endif
#ifdef __P007_CN
#define GPIO_P007 (0x07)
#endif

// PORT 1
#ifdef __P010_CN
#define GPIO_P010 (0x10)
#endif
#ifdef __P011_CN
#define GPIO_P011 (0x11)
#endif
#ifdef __P012_CN
#define GPIO_P012 (0x12)
#endif
#ifdef __P013_CN
#define GPIO_P013 (0x13)
#endif
#ifdef __P014_CN
#define GPIO_P014 (0x14)
#endif
#ifdef __P015_CN
#define GPIO_P015 (0x15)
#endif
#ifdef __P016_CN
#define GPIO_P016 (0x16)
#endif
#ifdef __P017_CN
#define GPIO_P017 (0x17)
#endif

// PORT 2
#ifdef __P020_CN
#define GPIO_P020 (0x20)
#endif
#ifdef __P021_CN
#define GPIO_P021 (0x21)
#endif
#ifdef __P022_CN
#define GPIO_P022 (0x22)
#endif
#ifdef __P023_CN
#define GPIO_P023 (0x23)
#endif
#ifdef __P024_CN
#define GPIO_P024 (0x24)
#endif
#ifdef __P025_CN
#define GPIO_P025 (0x25)
#endif
#ifdef __P026_CN
#define GPIO_P026 (0x26)
#endif
#ifdef __P027_CN
#define GPIO_P027 (0x27)
#endif

// PORT 3
#ifdef __P030_CN
#define GPIO_P030 (0x30)
#endif
#ifdef __P031_CN
#define GPIO_P031 (0x31)
#endif
#ifdef __P032_CN
#define GPIO_P032 (0x32)
#endif
#ifdef __P033_CN
#define GPIO_P033 (0x33)
#endif
#ifdef __P034_CN
#define GPIO_P034 (0x34)
#endif
#ifdef __P035_CN
#define GPIO_P035 (0x35)
#endif
#ifdef __P036_CN
#define GPIO_P036 (0x36)
#endif
#ifdef __P037_CN
#define GPIO_P037 (0x37)
#endif

// PORT 4
#ifdef __P040_CN
#define GPIO_P040 (0x40)
#endif
#ifdef __P041_CN
#define GPIO_P041 (0x41)
#endif
#ifdef __P042_CN
#define GPIO_P042 (0x42)
#endif
#ifdef __P043_CN
#define GPIO_P043 (0x43)
#endif
#ifdef __P044_CN
#define GPIO_P044 (0x44)
#endif
#ifdef __P045_CN
#define GPIO_P045 (0x45)
#endif
#ifdef __P046_CN
#define GPIO_P046 (0x46)
#endif
#ifdef __P047_CN
#define GPIO_P047 (0x47)
#endif

// PORT 5
#ifdef __P050_CN
#define GPIO_P050 (0x50)
#endif
#ifdef __P051_CN
#define GPIO_P051 (0x51)
#endif
#ifdef __P052_CN
#define GPIO_P052 (0x52)
#endif
#ifdef __P053_CN
#define GPIO_P053 (0x53)
#endif
#ifdef __P054_CN
#define GPIO_P054 (0x54)
#endif
#ifdef __P055_CN
#define GPIO_P055 (0x55)
#endif
#ifdef __P056_CN
#define GPIO_P056 (0x56)
#endif
#ifdef __P057_CN
#define GPIO_P057 (0x57)
#endif

// PORT 6
#ifdef __P060_CN
#define GPIO_P060 (0x60)
#endif
#ifdef __P061_CN
#define GPIO_P061 (0x61)
#endif
#ifdef __P062_CN
#define GPIO_P062 (0x62)
#endif
#ifdef __P063_CN
#define GPIO_P063 (0x63)
#endif
#ifdef __P064_CN
#define GPIO_P064 (0x64)
#endif
#ifdef __P065_CN
#define GPIO_P065 (0x65)
#endif
#ifdef __P066_CN
#define GPIO_P066 (0x66)
#endif
#ifdef __P067_CN
#define GPIO_P067 (0x67)
#endif

// PORT 7
#ifdef __P070_CN
#define GPIO_P070 (0x70)
#endif
#ifdef __P071_CN
#define GPIO_P071 (0x71)
#endif
#ifdef __P072_CN
#define GPIO_P072 (0x72)
#endif
#ifdef __P073_CN
#define GPIO_P073 (0x73)
#endif
#ifdef __P074_CN
#define GPIO_P074 (0x74)
#endif
#ifdef __P075_CN
#define GPIO_P075 (0x75)
#endif
#ifdef __P076_CN
#define GPIO_P076 (0x76)
#endif
#ifdef __P077_CN
#define GPIO_P077 (0x77)
#endif

// PORT 8
#ifdef __P080_CN
#define GPIO_P080 (0x80)
#endif
#ifdef __P081_CN
#define GPIO_P081 (0x81)
#endif
#ifdef __P082_CN
#define GPIO_P082 (0x82)
#endif
#ifdef __P083_CN
#define GPIO_P083 (0x83)
#endif
#ifdef __P084_CN
#define GPIO_P084 (0x84)
#endif
#ifdef __P085_CN
#define GPIO_P085 (0x85)
#endif
#ifdef __P086_CN
#define GPIO_P086 (0x86)
#endif
#ifdef __P087_CN
#define GPIO_P087 (0x87)
#endif

// PORT 9
#ifdef __P090_CN
#define GPIO_P090 (0x90)
#endif
#ifdef __P091_CN
#define GPIO_P091 (0x91)
#endif
#ifdef __P092_CN
#define GPIO_P092 (0x92)
#endif
#ifdef __P093_CN
#define GPIO_P093 (0x93)
#endif
#ifdef __P094_CN
#define GPIO_P094 (0x94)
#endif
#ifdef __P095_CN
#define GPIO_P095 (0x95)
#endif
#ifdef __P096_CN
#define GPIO_P096 (0x96)
#endif
#ifdef __P097_CN
#define GPIO_P097 (0x97)
#endif

// PORT 10
#ifdef __P100_CN
#define GPIO_P100 (0xA0)
#endif
#ifdef __P101_CN
#define GPIO_P101 (0xA1)
#endif
#ifdef __P102_CN
#define GPIO_P102 (0xA2)
#endif
#ifdef __P103_CN
#define GPIO_P103 (0xA3)
#endif
#ifdef __P104_CN
#define GPIO_P104 (0xA4)
#endif
#ifdef __P105_CN
#define GPIO_P105 (0xA5)
#endif
#ifdef __P106_CN
#define GPIO_P106 (0xA6)
#endif
#ifdef __P107_CN
#define GPIO_P107 (0xA7)
#endif

// PORT 11
#ifdef __P110_CN
#define GPIO_P110 (0xB0)
#endif
#ifdef __P111_CN
#define GPIO_P111 (0xB1)
#endif
#ifdef __P112_CN
#define GPIO_P112 (0xB2)
#endif
#ifdef __P113_CN
#define GPIO_P113 (0xB3)
#endif
#ifdef __P114_CN
#define GPIO_P114 (0xB4)
#endif
#ifdef __P115_CN
#define GPIO_P115 (0xB5)
#endif
#ifdef __P116_CN
#define GPIO_P116 (0xB6)
#endif
#ifdef __P117_CN
#define GPIO_P117 (0xB7)
#endif

// PORT 12
#ifdef __P120_CN
#define GPIO_P120 (0xC0)
#endif
#ifdef __P121_CN
#define GPIO_P121 (0xC1)
#endif
#ifdef __P122_CN
#define GPIO_P122 (0xC2)
#endif
#ifdef __P123_CN
#define GPIO_P123 (0xC3)
#endif
#ifdef __P124_CN
#define GPIO_P124 (0xC4)
#endif
#ifdef __P125_CN
#define GPIO_P125 (0xC5)
#endif
#ifdef __P126_CN
#define GPIO_P126 (0xC6)
#endif
#ifdef __P127_CN
#define GPIO_P127 (0xC7)
#endif

// PORT 13
#ifdef __P130_CN
#define GPIO_P130 (0xD0)
#endif
#ifdef __P131_CN
#define GPIO_P131 (0xD1)
#endif
#ifdef __P132_CN
#define GPIO_P132 (0xD2)
#endif
#ifdef __P133_CN
#define GPIO_P133 (0xD3)
#endif
#ifdef __P134_CN
#define GPIO_P134 (0xD4)
#endif
#ifdef __P135_CN
#define GPIO_P135 (0xD5)
#endif
#ifdef __P136_CN
#define GPIO_P136 (0xD6)
#endif
#ifdef __P137_CN
#define GPIO_P137 (0xD7)
#endif

// PORT 14
#ifdef __P140_CN
#define GPIO_P140 (0xE0)
#endif
#ifdef __P141_CN
#define GPIO_P141 (0xE1)
#endif
#ifdef __P142_CN
#define GPIO_P142 (0xE2)
#endif
#ifdef __P143_CN
#define GPIO_P143 (0xE3)
#endif
#ifdef __P144_CN
#define GPIO_P144 (0xE4)
#endif
#ifdef __P145_CN
#define GPIO_P145 (0xE5)
#endif
#ifdef __P146_CN
#define GPIO_P146 (0xE6)
#endif
#ifdef __P147_CN
#define GPIO_P147 (0xE7)
#endif

// PORT 15
#ifdef __P150_CN
#define GPIO_P150 (0xF0)
#endif
#ifdef __P151_CN
#define GPIO_P151 (0xF1)
#endif
#ifdef __P152_CN
#define GPIO_P152 (0xF2)
#endif
#ifdef __P153_CN
#define GPIO_P153 (0xF3)
#endif
#ifdef __P154_CN
#define GPIO_P154 (0xF4)
#endif
#ifdef __P155_CN
#define GPIO_P155 (0xF5)
#endif
#ifdef __P156_CN
#define GPIO_P156 (0xF6)
#endif
#ifdef __P157_CN
#define GPIO_P157 (0xF7)
#endif

#define GPIO_PIN_0 (0x00)
#define PIN_0 GPIO_PIN_0 // Notice: Will be removed in one of the upcoming releases. Use GPIO_PIN_0!
#define GPIO_PIN_1 (0x01)
#define PIN_1 GPIO_PIN_1 // Notice: Will be removed in one of the upcoming releases. Use GPIO_PIN_1!
#define GPIO_PIN_2 (0x02)
#define PIN_2 GPIO_PIN_2 // Notice: Will be removed in one of the upcoming releases. Use GPIO_PIN_2!
#define GPIO_PIN_3 (0x03)
#define PIN_3 GPIO_PIN_3 // Notice: Will be removed in one of the upcoming releases. Use GPIO_PIN_3!
#define GPIO_PIN_4 (0x04)
#define PIN_4 GPIO_PIN_4 // Notice: Will be removed in one of the upcoming releases. Use GPIO_PIN_4!
#define GPIO_PIN_5 (0x05)
#define PIN_5 GPIO_PIN_5 // Notice: Will be removed in one of the upcoming releases. Use GPIO_PIN_5!
#define GPIO_PIN_6 (0x06)
#define PIN_6 GPIO_PIN_6 // Notice: Will be removed in one of the upcoming releases. Use GPIO_PIN_6!
#define GPIO_PIN_7 (0x07)
#define PIN_7 GPIO_PIN_7 // Notice: Will be removed in one of the upcoming releases. Use GPIO_PIN_7!

#ifdef __PORT_0_CN
#define GPIO_PORT_0 (0x00)
#define PORT_0 GPIO_PORT_0 // Notice: Will be removed in one of the upcoming releases. Use GPIO_PORT_0!
#endif
#ifdef __PORT_1_CN
#define GPIO_PORT_1 (0x01)
#define PORT_1 GPIO_PORT_1 // Notice: Will be removed in one of the upcoming releases. Use GPIO_PORT_1!
#endif
#ifdef __PORT_2_CN
#define GPIO_PORT_2 (0x02)
#define PORT_2 GPIO_PORT_2 // Notice: Will be removed in one of the upcoming releases. Use GPIO_PORT_2!
#endif
#ifdef __PORT_3_CN
#define GPIO_PORT_3 (0x03)
#define PORT_3 GPIO_PORT_3 // Notice: Will be removed in one of the upcoming releases. Use GPIO_PORT_3!
#endif
#ifdef __PORT_4_CN
#define GPIO_PORT_4 (0x04)
#define PORT_4 GPIO_PORT_4 // Notice: Will be removed in one of the upcoming releases. Use GPIO_PORT_4!
#endif
#ifdef __PORT_5_CN
#define GPIO_PORT_5 (0x05)
#define PORT_5 GPIO_PORT_5 // Notice: Will be removed in one of the upcoming releases. Use GPIO_PORT_5!
#endif
#ifdef __PORT_6_CN
#define GPIO_PORT_6 (0x06)
#define PORT_6 GPIO_PORT_6 // Notice: Will be removed in one of the upcoming releases. Use GPIO_PORT_6!
#endif
#ifdef __PORT_7_CN
#define GPIO_PORT_7 (0x07)
#define PORT_7 GPIO_PORT_7 // Notice: Will be removed in one of the upcoming releases. Use GPIO_PORT_7!
#endif
#ifdef __PORT_8_CN
#define GPIO_PORT_8 (0x08)
#define PORT_8 GPIO_PORT_8 // Notice: Will be removed in one of the upcoming releases. Use GPIO_PORT_8!
#endif
#ifdef __PORT_9_CN
#define GPIO_PORT_9 (0x09)
#define PORT_9 GPIO_PORT_9 // Notice: Will be removed in one of the upcoming releases. Use GPIO_PORT_9!
#endif
#ifdef __PORT_10_CN
#define GPIO_PORT_10 (0x0A)
#define PORT_10 GPIO_PORT_10 // Notice: Will be removed in one of the upcoming releases. Use GPIO_PORT_10!
#endif
#ifdef __PORT_11_CN
#define GPIO_PORT_11 (0x0B)
#define PORT_11 GPIO_PORT_11 // Notice: Will be removed in one of the upcoming releases. Use GPIO_PORT_11!
#endif
#ifdef __PORT_12_CN
#define GPIO_PORT_12 (0x0C)
#define PORT_12 GPIO_PORT_12 // Notice: Will be removed in one of the upcoming releases. Use GPIO_PORT_12!
#endif
#ifdef __PORT_13_CN
#define GPIO_PORT_13 (0x0D)
#define PORT_13 GPIO_PORT_13 // Notice: Will be removed in one of the upcoming releases. Use GPIO_PORT_13!
#endif
#ifdef __PORT_14_CN
#define GPIO_PORT_14 (0x0E)
#define PORT_14 GPIO_PORT_14 // Notice: Will be removed in one of the upcoming releases. Use GPIO_PORT_14!
#endif
#ifdef __PORT_15_CN
#define GPIO_PORT_15 (0x0F)
#define PORT_15 GPIO_PORT_15 // Notice: Will be removed in one of the upcoming releases. Use GPIO_PORT_15!
#endif

#ifdef __cplusplus
}
#endif

#endif // _HAL_PIN_NAMES_H_
// ------------------------------------------------------------------------- END
