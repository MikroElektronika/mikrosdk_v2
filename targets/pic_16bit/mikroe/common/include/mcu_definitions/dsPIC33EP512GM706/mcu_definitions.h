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
* @file  mcu_definitions.h
* @brief dsPIC33EP512GM706 MCU specific pin and module definitions.
*/

#ifndef _MCU_DEFINITIONS_H_
#define _MCU_DEFINITIONS_H_

#include "mcu_reg_addresses.h"

// ADC
#define ADC1_RA0 (0)
#define ADC1_RA0_AN0 (0)
#define ADC1_RA1 (1)
#define ADC1_RA1_AN1 (1)
#define ADC1_RA11 (11)
#define ADC1_RA11_AN9 (9)
#define ADC1_RA12 (12)
#define ADC1_RA12_AN10 (10)
#define ADC1_RA4 (4)
#define ADC1_RA4_AN24 (24)
#define ADC1_RA9 (9)
#define ADC1_RA9_AN28 (28)
#define ADC1_RB0 (0)
#define ADC1_RB0_AN2 (2)
#define ADC1_RB1 (1)
#define ADC1_RB1_AN3 (3)
#define ADC1_RB2 (2)
#define ADC1_RB2_AN4 (4)
#define ADC1_RB3 (3)
#define ADC1_RB3_AN5 (5)
#define ADC1_RB7 (7)
#define ADC1_RB7_AN25 (25)
#define ADC1_RB8 (8)
#define ADC1_RB8_AN26 (26)
#define ADC1_RB9 (9)
#define ADC1_RB9_AN27 (27)
#define ADC1_RC0 (0)
#define ADC1_RC0_AN6 (6)
#define ADC1_RC1 (1)
#define ADC1_RC1_AN7 (7)
#define ADC1_RC10 (10)
#define ADC1_RC10_AN48 (48)
#define ADC1_RC11 (11)
#define ADC1_RC11_AN11 (11)
#define ADC1_RC12 (12)
#define ADC1_RC12_AN49 (49)
#define ADC1_RC2 (2)
#define ADC1_RC2_AN8 (8)
#define ADC1_RC3 (3)
#define ADC1_RC3_AN29 (29)
#define ADC1_RC4 (4)
#define ADC1_RC4_AN30 (30)
#define ADC1_RC5 (5)
#define ADC1_RC5_AN31 (31)
#define ADC1_RE12 (12)
#define ADC1_RE12_AN12 (12)
#define ADC1_RE13 (13)
#define ADC1_RE13_AN13 (13)
#define ADC1_RE14 (14)
#define ADC1_RE14_AN14 (14)
#define ADC1_RE15 (15)
#define ADC1_RE15_AN15 (15)
#define ADC1_RG6 (6)
#define ADC1_RG6_AN19 (19)
#define ADC1_RG7 (7)
#define ADC1_RG7_AN18 (18)
#define ADC1_RG8 (8)
#define ADC1_RG8_AN17 (17)
#define ADC1_RG9 (9)
#define ADC1_RG9_AN16 (16)
#define ADC2_RA0 (0)
#define ADC2_RA0_AN0 (0)
#define ADC2_RA1 (1)
#define ADC2_RA1_AN1 (1)
#define ADC2_RA11 (11)
#define ADC2_RA11_AN9 (9)
#define ADC2_RA12 (12)
#define ADC2_RA12_AN10 (10)
#define ADC2_RA4 (4)
#define ADC2_RA4_AN24 (24)
#define ADC2_RA9 (9)
#define ADC2_RA9_AN28 (28)
#define ADC2_RB0 (0)
#define ADC2_RB0_AN2 (2)
#define ADC2_RB1 (1)
#define ADC2_RB1_AN3 (3)
#define ADC2_RB2 (2)
#define ADC2_RB2_AN4 (4)
#define ADC2_RB3 (3)
#define ADC2_RB3_AN5 (5)
#define ADC2_RB7 (7)
#define ADC2_RB7_AN25 (25)
#define ADC2_RB8 (8)
#define ADC2_RB8_AN26 (26)
#define ADC2_RB9 (9)
#define ADC2_RB9_AN27 (27)
#define ADC2_RC0 (0)
#define ADC2_RC0_AN6 (6)
#define ADC2_RC1 (1)
#define ADC2_RC1_AN7 (7)
#define ADC2_RC11 (11)
#define ADC2_RC11_AN11 (11)
#define ADC2_RC2 (2)
#define ADC2_RC2_AN8 (8)
#define ADC2_RC3 (3)
#define ADC2_RC3_AN29 (29)
#define ADC2_RC4 (4)
#define ADC2_RC4_AN30 (30)
#define ADC2_RC5 (5)
#define ADC2_RC5_AN31 (31)
#define ADC2_RE12 (12)
#define ADC2_RE12_AN12 (12)
#define ADC2_RE13 (13)
#define ADC2_RE13_AN13 (13)
#define ADC2_RE14 (14)
#define ADC2_RE14_AN14 (14)
#define ADC2_RE15 (15)
#define ADC2_RE15_AN15 (15)
#define ADC2_RG6 (6)
#define ADC2_RG6_AN19 (19)
#define ADC2_RG7 (7)
#define ADC2_RG7_AN18 (18)
#define ADC2_RG8 (8)
#define ADC2_RG8_AN17 (17)
#define ADC2_RG9 (9)
#define ADC2_RG9_AN16 (16)

#define ADC_MODULE_1 1
#define ADC_MODULE_2 2
#define ADC_MODULE_COUNT 2
#define HAL_LL_AN_COUNT 58

#define SUPPORTED_ADC_RES_10_BIT
#define SUPPORTED_ADC_RES_12_BIT

// ADC Register addresses and offsets
#define HAL_LL_ADC1BUF0_REG_ADDRESS (0x300)
#define HAL_LL_ADC1BUF1_REG_ADDRESS (0x302)
#define HAL_LL_ADC1BUF2_REG_ADDRESS (0x304)
#define HAL_LL_ADC1BUF3_REG_ADDRESS (0x306)
#define HAL_LL_ADC1BUF4_REG_ADDRESS (0x308)
#define HAL_LL_ADC1BUF5_REG_ADDRESS (0x30A)
#define HAL_LL_ADC1BUF6_REG_ADDRESS (0x30C)
#define HAL_LL_ADC1BUF7_REG_ADDRESS (0x30E)
#define HAL_LL_ADC1BUF8_REG_ADDRESS (0x310)
#define HAL_LL_ADC1BUF9_REG_ADDRESS (0x312)
#define HAL_LL_ADC1BUFA_REG_ADDRESS (0x314)
#define HAL_LL_ADC1BUFB_REG_ADDRESS (0x316)
#define HAL_LL_ADC1BUFC_REG_ADDRESS (0x318)
#define HAL_LL_ADC1BUFD_REG_ADDRESS (0x31A)
#define HAL_LL_ADC1BUFE_REG_ADDRESS (0x31C)
#define HAL_LL_ADC1BUFF_REG_ADDRESS (0x31E)
#define HAL_LL_AD1CON1_REG_ADDRESS (0x320)
#define HAL_LL_AD1CON2_REG_ADDRESS (0x322)
#define HAL_LL_AD1CON3_REG_ADDRESS (0x324)
#define HAL_LL_AD1CHS123_REG_ADDRESS (0x326)
#define HAL_LL_AD1CHS0_REG_ADDRESS (0x328)
#define HAL_LL_AD1CSSH_REG_ADDRESS (0x32E)
#define HAL_LL_AD1CSSL_REG_ADDRESS (0x330)
#define HAL_LL_AD1CON4_REG_ADDRESS (0x332)
#define HAL_LL_ADC2BUF0_REG_ADDRESS (0x340)
#define HAL_LL_ADC2BUF1_REG_ADDRESS (0x342)
#define HAL_LL_ADC2BUF2_REG_ADDRESS (0x344)
#define HAL_LL_ADC2BUF3_REG_ADDRESS (0x346)
#define HAL_LL_ADC2BUF4_REG_ADDRESS (0x348)
#define HAL_LL_ADC2BUF5_REG_ADDRESS (0x34A)
#define HAL_LL_ADC2BUF6_REG_ADDRESS (0x34C)
#define HAL_LL_ADC2BUF7_REG_ADDRESS (0x34E)
#define HAL_LL_ADC2BUF8_REG_ADDRESS (0x350)
#define HAL_LL_ADC2BUF9_REG_ADDRESS (0x352)
#define HAL_LL_ADC2BUFA_REG_ADDRESS (0x354)
#define HAL_LL_ADC2BUFB_REG_ADDRESS (0x356)
#define HAL_LL_ADC2BUFC_REG_ADDRESS (0x358)
#define HAL_LL_ADC2BUFD_REG_ADDRESS (0x35A)
#define HAL_LL_ADC2BUFE_REG_ADDRESS (0x35C)
#define HAL_LL_ADC2BUFF_REG_ADDRESS (0x35E)
#define HAL_LL_AD2CON1_REG_ADDRESS (0x360)
#define HAL_LL_AD2CON2_REG_ADDRESS (0x362)
#define HAL_LL_AD2CON3_REG_ADDRESS (0x364)
#define HAL_LL_AD2CHS123_REG_ADDRESS (0x366)
#define HAL_LL_AD2CHS0_REG_ADDRESS (0x368)
#define HAL_LL_AD2CSSH_REG_ADDRESS (0x36E)
#define HAL_LL_AD2CSSL_REG_ADDRESS (0x370)
#define HAL_LL_AD2CON4_REG_ADDRESS (0x372)
#define HAL_LL_IFS0_REG_ADDRESS (0x800)
#define HAL_LL_IFS1_REG_ADDRESS (0x802)
#define HAL_LL_IFS2_REG_ADDRESS (0x804)
#define HAL_LL_IFS3_REG_ADDRESS (0x806)
#define HAL_LL_IFS4_REG_ADDRESS (0x808)
#define HAL_LL_IFS5_REG_ADDRESS (0x80A)
#define HAL_LL_IFS6_REG_ADDRESS (0x80C)
#define HAL_LL_IFS8_REG_ADDRESS (0x810)
#define HAL_LL_IFS9_REG_ADDRESS (0x812)
#define HAL_LL_IEC0_REG_ADDRESS (0x820)
#define HAL_LL_IEC1_REG_ADDRESS (0x822)
#define HAL_LL_IEC2_REG_ADDRESS (0x824)
#define HAL_LL_IEC3_REG_ADDRESS (0x826)
#define HAL_LL_IEC4_REG_ADDRESS (0x828)
#define HAL_LL_IEC5_REG_ADDRESS (0x82A)
#define HAL_LL_IEC6_REG_ADDRESS (0x82C)
#define HAL_LL_IEC8_REG_ADDRESS (0x830)
#define HAL_LL_IEC9_REG_ADDRESS (0x832)
#define HAL_LL_IPC0_REG_ADDRESS (0x840)
#define HAL_LL_IPC1_REG_ADDRESS (0x842)
#define HAL_LL_IPC2_REG_ADDRESS (0x844)
#define HAL_LL_IPC3_REG_ADDRESS (0x846)
#define HAL_LL_IPC4_REG_ADDRESS (0x848)
#define HAL_LL_IPC5_REG_ADDRESS (0x84A)
#define HAL_LL_IPC6_REG_ADDRESS (0x84C)
#define HAL_LL_IPC7_REG_ADDRESS (0x84E)
#define HAL_LL_IPC8_REG_ADDRESS (0x850)
#define HAL_LL_IPC9_REG_ADDRESS (0x852)
#define HAL_LL_IPC10_REG_ADDRESS (0x854)
#define HAL_LL_IPC11_REG_ADDRESS (0x856)
#define HAL_LL_IPC12_REG_ADDRESS (0x858)
#define HAL_LL_IPC13_REG_ADDRESS (0x85A)
#define HAL_LL_IPC14_REG_ADDRESS (0x85C)
#define HAL_LL_IPC15_REG_ADDRESS (0x85E)
#define HAL_LL_IPC16_REG_ADDRESS (0x860)
#define HAL_LL_IPC17_REG_ADDRESS (0x862)
#define HAL_LL_IPC18_REG_ADDRESS (0x864)
#define HAL_LL_IPC19_REG_ADDRESS (0x866)
#define HAL_LL_IPC20_REG_ADDRESS (0x868)
#define HAL_LL_IPC21_REG_ADDRESS (0x86A)
#define HAL_LL_IPC22_REG_ADDRESS (0x86C)
#define HAL_LL_IPC23_REG_ADDRESS (0x86E)
#define HAL_LL_IPC24_REG_ADDRESS (0x870)
#define HAL_LL_IPC35_REG_ADDRESS (0x886)
#define HAL_LL_IPC36_REG_ADDRESS (0x888)
#define HAL_LL_IPC37_REG_ADDRESS (0x88A)
#define HAL_LL_ANSELA_REG_ADDRESS (0xE0E)
#define HAL_LL_ANSELB_REG_ADDRESS (0xE1E)
#define HAL_LL_ANSELC_REG_ADDRESS (0xE2E)
#define HAL_LL_ANSELD_REG_ADDRESS (0xE3E)
#define HAL_LL_ANSELE_REG_ADDRESS (0xE4E)
#define HAL_LL_ANSELF_REG_ADDRESS (0xE5E)
#define HAL_LL_ANSELG_REG_ADDRESS (0xE6E)
#define _ADC_ANSEL_
// EOF ADC Register addresses and offsets
// EOF ADC

// I2C
#define I2C1_RC4_SDA1
#define I2C1_RC5_SCL1
#define I2C1_RG7_SCL1_ALT
#define I2C1_RG8_SDA1_ALT
#define I2C2_RA8_SDA2
#define I2C2_RB4_SCL2
#define I2C2_RB5_SDA2_ALT
#define I2C2_RB6_SCL2_ALT

#define I2C_MODULE_1 1
#define I2C_MODULE_2 2
#define I2C_MODULE_COUNT 2

// I2C Register addresses and offsets
#define HAL_LL_I2C1RCV_REG_ADDRESS (0x200)
#define HAL_LL_I2C1TRN_REG_ADDRESS (0x202)
#define HAL_LL_I2C1BRG_REG_ADDRESS (0x204)
#define HAL_LL_I2C1CON_REG_ADDRESS (0x206)
#define HAL_LL_I2C1STAT_REG_ADDRESS (0x208)
#define HAL_LL_I2C2RCV_REG_ADDRESS (0x210)
#define HAL_LL_I2C2TRN_REG_ADDRESS (0x212)
#define HAL_LL_I2C2BRG_REG_ADDRESS (0x214)
#define HAL_LL_I2C2CON_REG_ADDRESS (0x216)
#define HAL_LL_I2C2STAT_REG_ADDRESS (0x218)
#define HAL_LL_PADCFG1_REG_ADDRESS (0xEFE)
// EOF I2C Register addresses and offsets
// EOF I2C

// U(S)ART
// #define UART1_BCLK1_RC2
// #define UART1_U1CTS_RC11
// #define UART1_U1RTS_RC2
// #define UART2_BCLK2_RE12
// #define UART2_U2CTS_RE13
// #define UART2_U2RTS_RE12
#define UART1_RX_RA0_RPI16 (16)
#define UART1_RX_RA1_RPI17 (17)
#define UART1_RX_RA11_RPI27 (27)
#define UART1_RX_RA12_RPI28 (28)
#define UART1_RX_RA4_RP20 (20)
#define UART1_RX_RA8_RPI24 (24)
#define UART1_RX_RA9_RPI25 (25)
#define UART1_RX_RB0_RPI32 (32)
#define UART1_RX_RB1_RPI33 (33)
#define UART1_RX_RB10_RP42 (42)
#define UART1_RX_RB11_RP43 (43)
#define UART1_RX_RB12_RPI44 (44)
#define UART1_RX_RB13_RPI45 (45)
#define UART1_RX_RB14_RPI46 (46)
#define UART1_RX_RB15_RPI47 (47)
#define UART1_RX_RB2_RPI34 (34)
#define UART1_RX_RB3_RP35 (35)
#define UART1_RX_RB4_RP36 (36)
#define UART1_RX_RB5_RP37 (37)
#define UART1_RX_RB6_RP38 (38)
#define UART1_RX_RB7_RP39 (39)
#define UART1_RX_RB8_RP40 (40)
#define UART1_RX_RB9_RP41 (41)
#define UART1_RX_RC0_RP48 (48)
#define UART1_RX_RC1_RP49 (49)
#define UART1_RX_RC10_RPI58 (58)
#define UART1_RX_RC12_RPI60 (60)
#define UART1_RX_RC13_RPI61 (61)
#define UART1_RX_RC15_RPI63 (63)
#define UART1_RX_RC2_RPI50 (50)
#define UART1_RX_RC3_RPI51 (51)
#define UART1_RX_RC4_RPI52 (52)
#define UART1_RX_RC5_RPI53 (53)
#define UART1_RX_RC6_RP54 (54)
#define UART1_RX_RC7_RP55 (55)
#define UART1_RX_RC8_RP56 (56)
#define UART1_RX_RC9_RP57 (57)
#define UART1_RX_RD5_RP69 (69)
#define UART1_RX_RD6_RP70 (70)
#define UART1_RX_RD8_RPI72 (72)
#define UART1_RX_RE14_RPI94 (94)
#define UART1_RX_RE15_RPI95 (95)
#define UART1_RX_RF0_RPI96 (96)
#define UART1_RX_RF1_RP97 (97)
#define UART1_RX_RG6_RP118 (118)
#define UART1_RX_RG7_RPI119 (119)
#define UART1_RX_RG8_RP120 (120)
#define UART1_RX_RG9_RPI121 (121)
#define UART1_TX_RA4_RP20 (20)
#define UART1_TX_RB10_RP42 (42)
#define UART1_TX_RB11_RP43 (43)
#define UART1_TX_RB3_RP35 (35)
#define UART1_TX_RB4_RP36 (36)
#define UART1_TX_RB5_RP37 (37)
#define UART1_TX_RB6_RP38 (38)
#define UART1_TX_RB7_RP39 (39)
#define UART1_TX_RB8_RP40 (40)
#define UART1_TX_RB9_RP41 (41)
#define UART1_TX_RC0_RP48 (48)
#define UART1_TX_RC1_RP49 (49)
#define UART1_TX_RC6_RP54 (54)
#define UART1_TX_RC7_RP55 (55)
#define UART1_TX_RC8_RP56 (56)
#define UART1_TX_RC9_RP57 (57)
#define UART1_TX_RD5_RP69 (69)
#define UART1_TX_RD6_RP70 (70)
#define UART1_TX_RF1_RP97 (97)
#define UART1_TX_RG6_RP118 (118)
#define UART1_TX_RG8_RP120 (120)
#define UART2_RX_RA0_RPI16 (16)
#define UART2_RX_RA1_RPI17 (17)
#define UART2_RX_RA11_RPI27 (27)
#define UART2_RX_RA12_RPI28 (28)
#define UART2_RX_RA4_RP20 (20)
#define UART2_RX_RA8_RPI24 (24)
#define UART2_RX_RA9_RPI25 (25)
#define UART2_RX_RB0_RPI32 (32)
#define UART2_RX_RB1_RPI33 (33)
#define UART2_RX_RB10_RP42 (42)
#define UART2_RX_RB11_RP43 (43)
#define UART2_RX_RB12_RPI44 (44)
#define UART2_RX_RB13_RPI45 (45)
#define UART2_RX_RB14_RPI46 (46)
#define UART2_RX_RB15_RPI47 (47)
#define UART2_RX_RB2_RPI34 (34)
#define UART2_RX_RB3_RP35 (35)
#define UART2_RX_RB4_RP36 (36)
#define UART2_RX_RB5_RP37 (37)
#define UART2_RX_RB6_RP38 (38)
#define UART2_RX_RB7_RP39 (39)
#define UART2_RX_RB8_RP40 (40)
#define UART2_RX_RB9_RP41 (41)
#define UART2_RX_RC0_RP48 (48)
#define UART2_RX_RC1_RP49 (49)
#define UART2_RX_RC10_RPI58 (58)
#define UART2_RX_RC12_RPI60 (60)
#define UART2_RX_RC13_RPI61 (61)
#define UART2_RX_RC15_RPI63 (63)
#define UART2_RX_RC2_RPI50 (50)
#define UART2_RX_RC3_RPI51 (51)
#define UART2_RX_RC4_RPI52 (52)
#define UART2_RX_RC5_RPI53 (53)
#define UART2_RX_RC6_RP54 (54)
#define UART2_RX_RC7_RP55 (55)
#define UART2_RX_RC8_RP56 (56)
#define UART2_RX_RC9_RP57 (57)
#define UART2_RX_RD5_RP69 (69)
#define UART2_RX_RD6_RP70 (70)
#define UART2_RX_RD8_RPI72 (72)
#define UART2_RX_RE14_RPI94 (94)
#define UART2_RX_RE15_RPI95 (95)
#define UART2_RX_RF0_RPI96 (96)
#define UART2_RX_RF1_RP97 (97)
#define UART2_RX_RG6_RP118 (118)
#define UART2_RX_RG7_RPI119 (119)
#define UART2_RX_RG8_RP120 (120)
#define UART2_RX_RG9_RPI121 (121)
#define UART2_TX_RA4_RP20 (20)
#define UART2_TX_RB10_RP42 (42)
#define UART2_TX_RB11_RP43 (43)
#define UART2_TX_RB3_RP35 (35)
#define UART2_TX_RB4_RP36 (36)
#define UART2_TX_RB5_RP37 (37)
#define UART2_TX_RB6_RP38 (38)
#define UART2_TX_RB7_RP39 (39)
#define UART2_TX_RB8_RP40 (40)
#define UART2_TX_RB9_RP41 (41)
#define UART2_TX_RC0_RP48 (48)
#define UART2_TX_RC1_RP49 (49)
#define UART2_TX_RC6_RP54 (54)
#define UART2_TX_RC7_RP55 (55)
#define UART2_TX_RC8_RP56 (56)
#define UART2_TX_RC9_RP57 (57)
#define UART2_TX_RD5_RP69 (69)
#define UART2_TX_RD6_RP70 (70)
#define UART2_TX_RF1_RP97 (97)
#define UART2_TX_RG6_RP118 (118)
#define UART2_TX_RG8_RP120 (120)
#define UART3_RX_RA0_RPI16 (16)
#define UART3_RX_RA1_RPI17 (17)
#define UART3_RX_RA11_RPI27 (27)
#define UART3_RX_RA12_RPI28 (28)
#define UART3_RX_RA4_RP20 (20)
#define UART3_RX_RA8_RPI24 (24)
#define UART3_RX_RA9_RPI25 (25)
#define UART3_RX_RB0_RPI32 (32)
#define UART3_RX_RB1_RPI33 (33)
#define UART3_RX_RB10_RP42 (42)
#define UART3_RX_RB11_RP43 (43)
#define UART3_RX_RB12_RPI44 (44)
#define UART3_RX_RB13_RPI45 (45)
#define UART3_RX_RB14_RPI46 (46)
#define UART3_RX_RB15_RPI47 (47)
#define UART3_RX_RB2_RPI34 (34)
#define UART3_RX_RB3_RP35 (35)
#define UART3_RX_RB4_RP36 (36)
#define UART3_RX_RB5_RP37 (37)
#define UART3_RX_RB6_RP38 (38)
#define UART3_RX_RB7_RP39 (39)
#define UART3_RX_RB8_RP40 (40)
#define UART3_RX_RB9_RP41 (41)
#define UART3_RX_RC0_RP48 (48)
#define UART3_RX_RC1_RP49 (49)
#define UART3_RX_RC10_RPI58 (58)
#define UART3_RX_RC12_RPI60 (60)
#define UART3_RX_RC13_RPI61 (61)
#define UART3_RX_RC15_RPI63 (63)
#define UART3_RX_RC2_RPI50 (50)
#define UART3_RX_RC3_RPI51 (51)
#define UART3_RX_RC4_RPI52 (52)
#define UART3_RX_RC5_RPI53 (53)
#define UART3_RX_RC6_RP54 (54)
#define UART3_RX_RC7_RP55 (55)
#define UART3_RX_RC8_RP56 (56)
#define UART3_RX_RC9_RP57 (57)
#define UART3_RX_RD5_RP69 (69)
#define UART3_RX_RD6_RP70 (70)
#define UART3_RX_RD8_RPI72 (72)
#define UART3_RX_RE14_RPI94 (94)
#define UART3_RX_RE15_RPI95 (95)
#define UART3_RX_RF0_RPI96 (96)
#define UART3_RX_RF1_RP97 (97)
#define UART3_RX_RG6_RP118 (118)
#define UART3_RX_RG7_RPI119 (119)
#define UART3_RX_RG8_RP120 (120)
#define UART3_RX_RG9_RPI121 (121)
#define UART3_TX_RA4_RP20 (20)
#define UART3_TX_RB10_RP42 (42)
#define UART3_TX_RB11_RP43 (43)
#define UART3_TX_RB3_RP35 (35)
#define UART3_TX_RB4_RP36 (36)
#define UART3_TX_RB5_RP37 (37)
#define UART3_TX_RB6_RP38 (38)
#define UART3_TX_RB7_RP39 (39)
#define UART3_TX_RB8_RP40 (40)
#define UART3_TX_RB9_RP41 (41)
#define UART3_TX_RC0_RP48 (48)
#define UART3_TX_RC1_RP49 (49)
#define UART3_TX_RC6_RP54 (54)
#define UART3_TX_RC7_RP55 (55)
#define UART3_TX_RC8_RP56 (56)
#define UART3_TX_RC9_RP57 (57)
#define UART3_TX_RD5_RP69 (69)
#define UART3_TX_RD6_RP70 (70)
#define UART3_TX_RF1_RP97 (97)
#define UART3_TX_RG6_RP118 (118)
#define UART3_TX_RG8_RP120 (120)
#define UART4_RX_RA0_RPI16 (16)
#define UART4_RX_RA1_RPI17 (17)
#define UART4_RX_RA11_RPI27 (27)
#define UART4_RX_RA12_RPI28 (28)
#define UART4_RX_RA4_RP20 (20)
#define UART4_RX_RA8_RPI24 (24)
#define UART4_RX_RA9_RPI25 (25)
#define UART4_RX_RB0_RPI32 (32)
#define UART4_RX_RB1_RPI33 (33)
#define UART4_RX_RB10_RP42 (42)
#define UART4_RX_RB11_RP43 (43)
#define UART4_RX_RB12_RPI44 (44)
#define UART4_RX_RB13_RPI45 (45)
#define UART4_RX_RB14_RPI46 (46)
#define UART4_RX_RB15_RPI47 (47)
#define UART4_RX_RB2_RPI34 (34)
#define UART4_RX_RB3_RP35 (35)
#define UART4_RX_RB4_RP36 (36)
#define UART4_RX_RB5_RP37 (37)
#define UART4_RX_RB6_RP38 (38)
#define UART4_RX_RB7_RP39 (39)
#define UART4_RX_RB8_RP40 (40)
#define UART4_RX_RB9_RP41 (41)
#define UART4_RX_RC0_RP48 (48)
#define UART4_RX_RC1_RP49 (49)
#define UART4_RX_RC10_RPI58 (58)
#define UART4_RX_RC12_RPI60 (60)
#define UART4_RX_RC13_RPI61 (61)
#define UART4_RX_RC15_RPI63 (63)
#define UART4_RX_RC2_RPI50 (50)
#define UART4_RX_RC3_RPI51 (51)
#define UART4_RX_RC4_RPI52 (52)
#define UART4_RX_RC5_RPI53 (53)
#define UART4_RX_RC6_RP54 (54)
#define UART4_RX_RC7_RP55 (55)
#define UART4_RX_RC8_RP56 (56)
#define UART4_RX_RC9_RP57 (57)
#define UART4_RX_RD5_RP69 (69)
#define UART4_RX_RD6_RP70 (70)
#define UART4_RX_RD8_RPI72 (72)
#define UART4_RX_RE14_RPI94 (94)
#define UART4_RX_RE15_RPI95 (95)
#define UART4_RX_RF0_RPI96 (96)
#define UART4_RX_RF1_RP97 (97)
#define UART4_RX_RG6_RP118 (118)
#define UART4_RX_RG7_RPI119 (119)
#define UART4_RX_RG8_RP120 (120)
#define UART4_RX_RG9_RPI121 (121)
#define UART4_TX_RA4_RP20 (20)
#define UART4_TX_RB10_RP42 (42)
#define UART4_TX_RB11_RP43 (43)
#define UART4_TX_RB3_RP35 (35)
#define UART4_TX_RB4_RP36 (36)
#define UART4_TX_RB5_RP37 (37)
#define UART4_TX_RB6_RP38 (38)
#define UART4_TX_RB7_RP39 (39)
#define UART4_TX_RB8_RP40 (40)
#define UART4_TX_RB9_RP41 (41)
#define UART4_TX_RC0_RP48 (48)
#define UART4_TX_RC1_RP49 (49)
#define UART4_TX_RC6_RP54 (54)
#define UART4_TX_RC7_RP55 (55)
#define UART4_TX_RC8_RP56 (56)
#define UART4_TX_RC9_RP57 (57)
#define UART4_TX_RD5_RP69 (69)
#define UART4_TX_RD6_RP70 (70)
#define UART4_TX_RF1_RP97 (97)
#define UART4_TX_RG6_RP118 (118)
#define UART4_TX_RG8_RP120 (120)

#define UART_MODULE_1 1
#define UART_MODULE_2 2
#define UART_MODULE_3 3
#define UART_MODULE_4 4
#define UART_MODULE_COUNT 4

// U(S)ART Register addresses and offsets
#define HAL_LL_U1MODE_REG_ADDRESS (0x220)
#define HAL_LL_U1STA_REG_ADDRESS (0x222)
#define HAL_LL_U1TXREG_REG_ADDRESS (0x224)
#define HAL_LL_U1RXREG_REG_ADDRESS (0x226)
#define HAL_LL_U1BRG_REG_ADDRESS (0x228)
#define HAL_LL_U2MODE_REG_ADDRESS (0x230)
#define HAL_LL_U2STA_REG_ADDRESS (0x232)
#define HAL_LL_U2TXREG_REG_ADDRESS (0x234)
#define HAL_LL_U2RXREG_REG_ADDRESS (0x236)
#define HAL_LL_U2BRG_REG_ADDRESS (0x238)
#define HAL_LL_U3MODE_REG_ADDRESS (0x250)
#define HAL_LL_U3STA_REG_ADDRESS (0x252)
#define HAL_LL_U3TXREG_REG_ADDRESS (0x254)
#define HAL_LL_U3RXREG_REG_ADDRESS (0x256)
#define HAL_LL_U3BRG_REG_ADDRESS (0x258)
#define HAL_LL_U4MODE_REG_ADDRESS (0x2B0)
#define HAL_LL_U4STA_REG_ADDRESS (0x2B2)
#define HAL_LL_U4TXREG_REG_ADDRESS (0x2B4)
#define HAL_LL_U4RXREG_REG_ADDRESS (0x2B6)
#define HAL_LL_U4BRG_REG_ADDRESS (0x2B8)
// EOF U(S)ART Register addresses and offsets
// EOF U(S)ART

// SPI
#define SPI1_MISO_RA9
#define SPI1_MOSI_RA4
#define SPI1_SCK_RC3
#define SPI1_SS_RB0
#define SPI2_MISO_RA0_RPI16 (16)
#define SPI2_MISO_RA1_RPI17 (17)
#define SPI2_MISO_RA11_RPI27 (27)
#define SPI2_MISO_RA12_RPI28 (28)
#define SPI2_MISO_RA4_RP20 (20)
#define SPI2_MISO_RA8_RPI24 (24)
#define SPI2_MISO_RA9_RPI25 (25)
#define SPI2_MISO_RB0_RPI32 (32)
#define SPI2_MISO_RB1_RPI33 (33)
#define SPI2_MISO_RB10_RP42 (42)
#define SPI2_MISO_RB11_RP43 (43)
#define SPI2_MISO_RB12_RPI44 (44)
#define SPI2_MISO_RB13_RPI45 (45)
#define SPI2_MISO_RB14_RPI46 (46)
#define SPI2_MISO_RB15_RPI47 (47)
#define SPI2_MISO_RB2_RPI34 (34)
#define SPI2_MISO_RB3_RP35 (35)
#define SPI2_MISO_RB4_RP36 (36)
#define SPI2_MISO_RB5_RP37 (37)
#define SPI2_MISO_RB6_RP38 (38)
#define SPI2_MISO_RB7_RP39 (39)
#define SPI2_MISO_RB8_RP40 (40)
#define SPI2_MISO_RB9_RP41 (41)
#define SPI2_MISO_RC0_RP48 (48)
#define SPI2_MISO_RC1_RP49 (49)
#define SPI2_MISO_RC10_RPI58 (58)
#define SPI2_MISO_RC12_RPI60 (60)
#define SPI2_MISO_RC13_RPI61 (61)
#define SPI2_MISO_RC15_RPI63 (63)
#define SPI2_MISO_RC2_RPI50 (50)
#define SPI2_MISO_RC3_RPI51 (51)
#define SPI2_MISO_RC4_RPI52 (52)
#define SPI2_MISO_RC5_RPI53 (53)
#define SPI2_MISO_RC6_RP54 (54)
#define SPI2_MISO_RC7_RP55 (55)
#define SPI2_MISO_RC8_RP56 (56)
#define SPI2_MISO_RC9_RP57 (57)
#define SPI2_MISO_RD5_RP69 (69)
#define SPI2_MISO_RD6_RP70 (70)
#define SPI2_MISO_RD8_RPI72 (72)
#define SPI2_MISO_RE14_RPI94 (94)
#define SPI2_MISO_RE15_RPI95 (95)
#define SPI2_MISO_RF0_RPI96 (96)
#define SPI2_MISO_RF1_RP97 (97)
#define SPI2_MISO_RG6_RP118 (118)
#define SPI2_MISO_RG7_RPI119 (119)
#define SPI2_MISO_RG8_RP120 (120)
#define SPI2_MISO_RG9_RPI121 (121)
#define SPI2_MOSI_RA4_RP20 (20)
#define SPI2_MOSI_RB10_RP42 (42)
#define SPI2_MOSI_RB11_RP43 (43)
#define SPI2_MOSI_RB3_RP35 (35)
#define SPI2_MOSI_RB4_RP36 (36)
#define SPI2_MOSI_RB5_RP37 (37)
#define SPI2_MOSI_RB6_RP38 (38)
#define SPI2_MOSI_RB7_RP39 (39)
#define SPI2_MOSI_RB8_RP40 (40)
#define SPI2_MOSI_RB9_RP41 (41)
#define SPI2_MOSI_RC0_RP48 (48)
#define SPI2_MOSI_RC1_RP49 (49)
#define SPI2_MOSI_RC6_RP54 (54)
#define SPI2_MOSI_RC7_RP55 (55)
#define SPI2_MOSI_RC8_RP56 (56)
#define SPI2_MOSI_RC9_RP57 (57)
#define SPI2_MOSI_RD5_RP69 (69)
#define SPI2_MOSI_RD6_RP70 (70)
#define SPI2_MOSI_RF1_RP97 (97)
#define SPI2_MOSI_RG6_RP118 (118)
#define SPI2_MOSI_RG8_RP120 (120)
#define SPI2_SCK_RA0_RPI16 (16)
#define SPI2_SCK_RA1_RPI17 (17)
#define SPI2_SCK_RA11_RPI27 (27)
#define SPI2_SCK_RA12_RPI28 (28)
#define SPI2_SCK_RA4_RP20 (20)
#define SPI2_SCK_RA8_RPI24 (24)
#define SPI2_SCK_RA9_RPI25 (25)
#define SPI2_SCK_RB0_RPI32 (32)
#define SPI2_SCK_RB1_RPI33 (33)
#define SPI2_SCK_RB10_RP42 (42)
#define SPI2_SCK_RB11_RP43 (43)
#define SPI2_SCK_RB12_RPI44 (44)
#define SPI2_SCK_RB13_RPI45 (45)
#define SPI2_SCK_RB14_RPI46 (46)
#define SPI2_SCK_RB15_RPI47 (47)
#define SPI2_SCK_RB2_RPI34 (34)
#define SPI2_SCK_RB3_RP35 (35)
#define SPI2_SCK_RB4_RP36 (36)
#define SPI2_SCK_RB5_RP37 (37)
#define SPI2_SCK_RB6_RP38 (38)
#define SPI2_SCK_RB7_RP39 (39)
#define SPI2_SCK_RB8_RP40 (40)
#define SPI2_SCK_RB9_RP41 (41)
#define SPI2_SCK_RC0_RP48 (48)
#define SPI2_SCK_RC1_RP49 (49)
#define SPI2_SCK_RC10_RPI58 (58)
#define SPI2_SCK_RC12_RPI60 (60)
#define SPI2_SCK_RC13_RPI61 (61)
#define SPI2_SCK_RC15_RPI63 (63)
#define SPI2_SCK_RC2_RPI50 (50)
#define SPI2_SCK_RC3_RPI51 (51)
#define SPI2_SCK_RC4_RPI52 (52)
#define SPI2_SCK_RC5_RPI53 (53)
#define SPI2_SCK_RC6_RP54 (54)
#define SPI2_SCK_RC7_RP55 (55)
#define SPI2_SCK_RC8_RP56 (56)
#define SPI2_SCK_RC9_RP57 (57)
#define SPI2_SCK_RD5_RP69 (69)
#define SPI2_SCK_RD6_RP70 (70)
#define SPI2_SCK_RD8_RPI72 (72)
#define SPI2_SCK_RE14_RPI94 (94)
#define SPI2_SCK_RE15_RPI95 (95)
#define SPI2_SCK_RF0_RPI96 (96)
#define SPI2_SCK_RF1_RP97 (97)
#define SPI2_SCK_RG6_RP118 (118)
#define SPI2_SCK_RG7_RPI119 (119)
#define SPI2_SCK_RG8_RP120 (120)
#define SPI2_SCK_RG9_RPI121 (121)
#define SPI3_MISO_RA0_RPI16 (16)
#define SPI3_MISO_RA1_RPI17 (17)
#define SPI3_MISO_RA11_RPI27 (27)
#define SPI3_MISO_RA12_RPI28 (28)
#define SPI3_MISO_RA4_RP20 (20)
#define SPI3_MISO_RA8_RPI24 (24)
#define SPI3_MISO_RA9_RPI25 (25)
#define SPI3_MISO_RB0_RPI32 (32)
#define SPI3_MISO_RB1_RPI33 (33)
#define SPI3_MISO_RB10_RP42 (42)
#define SPI3_MISO_RB11_RP43 (43)
#define SPI3_MISO_RB12_RPI44 (44)
#define SPI3_MISO_RB13_RPI45 (45)
#define SPI3_MISO_RB14_RPI46 (46)
#define SPI3_MISO_RB15_RPI47 (47)
#define SPI3_MISO_RB2_RPI34 (34)
#define SPI3_MISO_RB3_RP35 (35)
#define SPI3_MISO_RB4_RP36 (36)
#define SPI3_MISO_RB5_RP37 (37)
#define SPI3_MISO_RB6_RP38 (38)
#define SPI3_MISO_RB7_RP39 (39)
#define SPI3_MISO_RB8_RP40 (40)
#define SPI3_MISO_RB9_RP41 (41)
#define SPI3_MISO_RC0_RP48 (48)
#define SPI3_MISO_RC1_RP49 (49)
#define SPI3_MISO_RC10_RPI58 (58)
#define SPI3_MISO_RC12_RPI60 (60)
#define SPI3_MISO_RC13_RPI61 (61)
#define SPI3_MISO_RC15_RPI63 (63)
#define SPI3_MISO_RC2_RPI50 (50)
#define SPI3_MISO_RC3_RPI51 (51)
#define SPI3_MISO_RC4_RPI52 (52)
#define SPI3_MISO_RC5_RPI53 (53)
#define SPI3_MISO_RC6_RP54 (54)
#define SPI3_MISO_RC7_RP55 (55)
#define SPI3_MISO_RC8_RP56 (56)
#define SPI3_MISO_RC9_RP57 (57)
#define SPI3_MISO_RD5_RP69 (69)
#define SPI3_MISO_RD6_RP70 (70)
#define SPI3_MISO_RD8_RPI72 (72)
#define SPI3_MISO_RE14_RPI94 (94)
#define SPI3_MISO_RE15_RPI95 (95)
#define SPI3_MISO_RF0_RPI96 (96)
#define SPI3_MISO_RF1_RP97 (97)
#define SPI3_MISO_RG6_RP118 (118)
#define SPI3_MISO_RG7_RPI119 (119)
#define SPI3_MISO_RG8_RP120 (120)
#define SPI3_MISO_RG9_RPI121 (121)
#define SPI3_MOSI_RA4_RP20 (20)
#define SPI3_MOSI_RB10_RP42 (42)
#define SPI3_MOSI_RB11_RP43 (43)
#define SPI3_MOSI_RB3_RP35 (35)
#define SPI3_MOSI_RB4_RP36 (36)
#define SPI3_MOSI_RB5_RP37 (37)
#define SPI3_MOSI_RB6_RP38 (38)
#define SPI3_MOSI_RB7_RP39 (39)
#define SPI3_MOSI_RB8_RP40 (40)
#define SPI3_MOSI_RB9_RP41 (41)
#define SPI3_MOSI_RC0_RP48 (48)
#define SPI3_MOSI_RC1_RP49 (49)
#define SPI3_MOSI_RC6_RP54 (54)
#define SPI3_MOSI_RC7_RP55 (55)
#define SPI3_MOSI_RC8_RP56 (56)
#define SPI3_MOSI_RC9_RP57 (57)
#define SPI3_MOSI_RD5_RP69 (69)
#define SPI3_MOSI_RD6_RP70 (70)
#define SPI3_MOSI_RF1_RP97 (97)
#define SPI3_MOSI_RG6_RP118 (118)
#define SPI3_MOSI_RG8_RP120 (120)
#define SPI3_SCK_RA0_RPI16 (16)
#define SPI3_SCK_RA1_RPI17 (17)
#define SPI3_SCK_RA11_RPI27 (27)
#define SPI3_SCK_RA12_RPI28 (28)
#define SPI3_SCK_RA4_RP20 (20)
#define SPI3_SCK_RA8_RPI24 (24)
#define SPI3_SCK_RA9_RPI25 (25)
#define SPI3_SCK_RB0_RPI32 (32)
#define SPI3_SCK_RB1_RPI33 (33)
#define SPI3_SCK_RB10_RP42 (42)
#define SPI3_SCK_RB11_RP43 (43)
#define SPI3_SCK_RB12_RPI44 (44)
#define SPI3_SCK_RB13_RPI45 (45)
#define SPI3_SCK_RB14_RPI46 (46)
#define SPI3_SCK_RB15_RPI47 (47)
#define SPI3_SCK_RB2_RPI34 (34)
#define SPI3_SCK_RB3_RP35 (35)
#define SPI3_SCK_RB4_RP36 (36)
#define SPI3_SCK_RB5_RP37 (37)
#define SPI3_SCK_RB6_RP38 (38)
#define SPI3_SCK_RB7_RP39 (39)
#define SPI3_SCK_RB8_RP40 (40)
#define SPI3_SCK_RB9_RP41 (41)
#define SPI3_SCK_RC0_RP48 (48)
#define SPI3_SCK_RC1_RP49 (49)
#define SPI3_SCK_RC10_RPI58 (58)
#define SPI3_SCK_RC12_RPI60 (60)
#define SPI3_SCK_RC13_RPI61 (61)
#define SPI3_SCK_RC15_RPI63 (63)
#define SPI3_SCK_RC2_RPI50 (50)
#define SPI3_SCK_RC3_RPI51 (51)
#define SPI3_SCK_RC4_RPI52 (52)
#define SPI3_SCK_RC5_RPI53 (53)
#define SPI3_SCK_RC6_RP54 (54)
#define SPI3_SCK_RC7_RP55 (55)
#define SPI3_SCK_RC8_RP56 (56)
#define SPI3_SCK_RC9_RP57 (57)
#define SPI3_SCK_RD5_RP69 (69)
#define SPI3_SCK_RD6_RP70 (70)
#define SPI3_SCK_RD8_RPI72 (72)
#define SPI3_SCK_RE14_RPI94 (94)
#define SPI3_SCK_RE15_RPI95 (95)
#define SPI3_SCK_RF0_RPI96 (96)
#define SPI3_SCK_RF1_RP97 (97)
#define SPI3_SCK_RG6_RP118 (118)
#define SPI3_SCK_RG7_RPI119 (119)
#define SPI3_SCK_RG8_RP120 (120)
#define SPI3_SCK_RG9_RPI121 (121)

#define SPI_MODULE_1 1
#define SPI_MODULE_2 2
#define SPI_MODULE_3 3
#define SPI_MODULE_COUNT 3

// SPI Register addresses and offsets
#define HAL_LL_SPI1STAT_REG_ADDRESS (0x240)
#define HAL_LL_SPI1CON1_REG_ADDRESS (0x242)
#define HAL_LL_SPI1_CONTROL_REG_ADDRESS HAL_LL_SPI1CON1_REG_ADDRESS
#define HAL_LL_SPI1BUF_REG_ADDRESS (0x248)
#define HAL_LL_SPI2STAT_REG_ADDRESS (0x260)
#define HAL_LL_SPI2CON1_REG_ADDRESS (0x262)
#define HAL_LL_SPI2_CONTROL_REG_ADDRESS HAL_LL_SPI2CON1_REG_ADDRESS
#define HAL_LL_SPI2BUF_REG_ADDRESS (0x268)
#define HAL_LL_SPI3STAT_REG_ADDRESS (0x2A0)
#define HAL_LL_SPI3CON1_REG_ADDRESS (0x2A2)
#define HAL_LL_SPI3_CONTROL_REG_ADDRESS HAL_LL_SPI3CON1_REG_ADDRESS
#define HAL_LL_SPI3BUF_REG_ADDRESS (0x2A8)
// EOF SPI Register addresses and offsets
// EOF SPI

// TIM
#define PWM_CCP1_OC1_RA4_RP20 (20)
#define PWM_CCP2_OC2_RB10_RP42 (42)
#define PWM_CCP2_OC2_RB7_RP39 (39)
#define PWM_CCP2_OC3_RB5_RP37 (37)
#define PWM_CCP2_OC5_RB11_RP43 (43)
#define PWM_CCP2_OC5_RB9_RP41 (41)
#define PWM_CCP2_OC6_RB6_RP38 (38)
#define PWM_CCP2_OC7_RB4_RP36 (36)
#define PWM_CCP2_OC7_RB8_RP40 (40)
#define PWM_CCP2_OC8_RB3_RP35 (35)
#define PWM_CCP3_OC3_RC6_RP54 (54)
#define PWM_CCP3_OC3_RC9_RP57 (57)
#define PWM_CCP3_OC5_RC7_RP55 (55)
#define PWM_CCP3_OC6_RC1_RP49 (49)
#define PWM_CCP3_OC8_RC0_RP48 (48)
#define PWM_CCP3_OC8_RC8_RP56 (56)
#define PWM_CCP4_OC5_RD5_RP69 (69)
#define PWM_CCP4_OC7_RD6_RP70 (70)
#define PWM_CCP5_OC8_RF1_RP97 (97)
#define PWM_CCP6_OC1_RG6_RP118 (118)
#define PWM_CCP6_OC4_RG8_RP120 (120)
#define PWM_CCP7_OC8_RA4_RP20 (20)
#define PWM_CCP8_OC1_RB10_RP42 (42)
#define PWM_CCP8_OC1_RB7_RP39 (39)
#define PWM_CCP8_OC2_RB5_RP37 (37)
#define PWM_CCP8_OC4_RB11_RP43 (43)
#define PWM_CCP8_OC4_RB9_RP41 (41)
#define PWM_CCP8_OC5_RB6_RP38 (38)
#define PWM_CCP8_OC6_RB4_RP36 (36)
#define PWM_CCP8_OC6_RB8_RP40 (40)
#define PWM_CCP8_OC7_RB3_RP35 (35)
#define PWM_CCP9_OC2_RC6_RP54 (54)
#define PWM_CCP9_OC2_RC9_RP57 (57)
#define PWM_CCP9_OC4_RC7_RP55 (55)
#define PWM_CCP9_OC5_RC1_RP49 (49)
#define PWM_CCP9_OC7_RC0_RP48 (48)
#define PWM_CCP9_OC7_RC8_RP56 (56)

#define CCP_MODULE_1 1
#define CCP_MODULE_2 2
#define CCP_MODULE_3 3
#define CCP_MODULE_4 4
#define CCP_MODULE_5 5
#define CCP_MODULE_6 6
#define CCP_MODULE_7 7
#define CCP_MODULE_8 8
#define CCP_MODULE_9 9

#define CCP_MODULE_COUNT 9
#define TIM_MODULE_COUNT CCP_MODULE_COUNT

// TIM Register addresses and offsets
#define HAL_LL_TMR1_REG_ADDRESS (0x100)
#define HAL_LL_PR1_REG_ADDRESS (0x102)
#define HAL_LL_T1CON_REG_ADDRESS (0x104)
#define HAL_LL_TMR2_REG_ADDRESS (0x106)
#define HAL_LL_TMR3_REG_ADDRESS (0x10A)
#define HAL_LL_PR2_REG_ADDRESS (0x10C)
#define HAL_LL_PR3_REG_ADDRESS (0x10E)
#define HAL_LL_T2CON_REG_ADDRESS (0x110)
#define HAL_LL_T3CON_REG_ADDRESS (0x112)
#define HAL_LL_TMR4_REG_ADDRESS (0x114)
#define HAL_LL_TMR5_REG_ADDRESS (0x118)
#define HAL_LL_PR4_REG_ADDRESS (0x11A)
#define HAL_LL_PR5_REG_ADDRESS (0x11C)
#define HAL_LL_T4CON_REG_ADDRESS (0x11E)
#define HAL_LL_T5CON_REG_ADDRESS (0x120)
#define HAL_LL_TMR6_REG_ADDRESS (0x122)
#define HAL_LL_TMR7_REG_ADDRESS (0x126)
#define HAL_LL_PR6_REG_ADDRESS (0x128)
#define HAL_LL_PR7_REG_ADDRESS (0x12A)
#define HAL_LL_T6CON_REG_ADDRESS (0x12C)
#define HAL_LL_T7CON_REG_ADDRESS (0x12E)
#define HAL_LL_TMR8_REG_ADDRESS (0x130)
#define HAL_LL_TMR9_REG_ADDRESS (0x134)
#define HAL_LL_PR8_REG_ADDRESS (0x136)
#define HAL_LL_PR9_REG_ADDRESS (0x138)
#define HAL_LL_T8CON_REG_ADDRESS (0x13A)
#define HAL_LL_T9CON_REG_ADDRESS (0x13C)
#define HAL_LL_OC1CON1_REG_ADDRESS (0x900)
#define HAL_LL_OC1CON2_REG_ADDRESS (0x902)
#define HAL_LL_OC1RS_REG_ADDRESS (0x904)
#define HAL_LL_OC1R_REG_ADDRESS (0x906)
#define HAL_LL_OC2CON1_REG_ADDRESS (0x90A)
#define HAL_LL_OC2CON2_REG_ADDRESS (0x90C)
#define HAL_LL_OC2RS_REG_ADDRESS (0x90E)
#define HAL_LL_OC2R_REG_ADDRESS (0x910)
#define HAL_LL_OC2TMR_REG_ADDRESS (0x912)
#define HAL_LL_OC3CON1_REG_ADDRESS (0x914)
#define HAL_LL_OC3CON2_REG_ADDRESS (0x916)
#define HAL_LL_OC3RS_REG_ADDRESS (0x918)
#define HAL_LL_OC3R_REG_ADDRESS (0x91A)
#define HAL_LL_OC3TMR_REG_ADDRESS (0x91C)
#define HAL_LL_OC4CON1_REG_ADDRESS (0x91E)
#define HAL_LL_OC4CON2_REG_ADDRESS (0x920)
#define HAL_LL_OC4RS_REG_ADDRESS (0x922)
#define HAL_LL_OC4R_REG_ADDRESS (0x924)
#define HAL_LL_OC4TMR_REG_ADDRESS (0x926)
#define HAL_LL_OC5CON1_REG_ADDRESS (0x928)
#define HAL_LL_OC5CON2_REG_ADDRESS (0x92A)
#define HAL_LL_OC5RS_REG_ADDRESS (0x92C)
#define HAL_LL_OC5R_REG_ADDRESS (0x92E)
#define HAL_LL_OC5TMR_REG_ADDRESS (0x930)
#define HAL_LL_OC6CON1_REG_ADDRESS (0x932)
#define HAL_LL_OC6CON2_REG_ADDRESS (0x934)
#define HAL_LL_OC6RS_REG_ADDRESS (0x936)
#define HAL_LL_OC6R_REG_ADDRESS (0x938)
#define HAL_LL_OC6TMR_REG_ADDRESS (0x93A)
#define HAL_LL_OC7CON1_REG_ADDRESS (0x93C)
#define HAL_LL_OC7CON2_REG_ADDRESS (0x93E)
#define HAL_LL_OC7RS_REG_ADDRESS (0x940)
#define HAL_LL_OC7R_REG_ADDRESS (0x942)
#define HAL_LL_OC7TMR_REG_ADDRESS (0x944)
#define HAL_LL_OC8CON1_REG_ADDRESS (0x946)
#define HAL_LL_OC8CON2_REG_ADDRESS (0x948)
#define HAL_LL_OC8RS_REG_ADDRESS (0x94A)
#define HAL_LL_OC8R_REG_ADDRESS (0x94C)
#define HAL_LL_OC8TMR_REG_ADDRESS (0x94E)
#define HAL_LL_PTCON_REG_ADDRESS (0xC00)
#define HAL_LL_PTPER_REG_ADDRESS (0xC04)
#define HAL_LL_MDC_REG_ADDRESS (0xC0A)
#define HAL_LL_STCON_REG_ADDRESS (0xC0E)
#define HAL_LL_PWMCON1_REG_ADDRESS (0xC20)
#define HAL_LL_IOCON1_REG_ADDRESS (0xC22)
#define HAL_LL_PDC1_REG_ADDRESS (0xC26)
#define HAL_LL_SDC1_REG_ADDRESS (0xC2E)
#define HAL_LL_PWMCON2_REG_ADDRESS (0xC40)
#define HAL_LL_IOCON2_REG_ADDRESS (0xC42)
#define HAL_LL_PDC2_REG_ADDRESS (0xC46)
#define HAL_LL_SDC2_REG_ADDRESS (0xC4E)
#define HAL_LL_PWMCON3_REG_ADDRESS (0xC60)
#define HAL_LL_IOCON3_REG_ADDRESS (0xC62)
#define HAL_LL_PDC3_REG_ADDRESS (0xC66)
#define HAL_LL_SDC3_REG_ADDRESS (0xC6E)
#define HAL_LL_PWMCON4_REG_ADDRESS (0xC80)
#define HAL_LL_IOCON4_REG_ADDRESS (0xC82)
#define HAL_LL_PDC4_REG_ADDRESS (0xC86)
#define HAL_LL_SDC4_REG_ADDRESS (0xC8E)
#define HAL_LL_PWMCON5_REG_ADDRESS (0xCA0)
#define HAL_LL_IOCON5_REG_ADDRESS (0xCA2)
#define HAL_LL_PDC5_REG_ADDRESS (0xCA6)
#define HAL_LL_SDC5_REG_ADDRESS (0xCAE)
#define HAL_LL_PWMCON6_REG_ADDRESS (0xCC0)
#define HAL_LL_IOCON6_REG_ADDRESS (0xCC2)
#define HAL_LL_PDC6_REG_ADDRESS (0xCC6)
#define HAL_LL_SDC6_REG_ADDRESS (0xCCE)
// EOF TIM Register addresses and offsets
// EOF TIM

// GPIO
#define __RA0_CN
#define __RA1_CN
#define __RA10_CN
#define __RA11_CN
#define __RA12_CN
#define __RA4_CN
#define __RA7_CN
#define __RA8_CN
#define __RA9_CN
#define __RB0_CN
#define __RB1_CN
#define __RB10_CN
#define __RB11_CN
#define __RB12_CN
#define __RB13_CN
#define __RB14_CN
#define __RB15_CN
#define __RB2_CN
#define __RB3_CN
#define __RB4_CN
#define __RB5_CN
#define __RB6_CN
#define __RB7_CN
#define __RB8_CN
#define __RB9_CN
#define __RC0_CN
#define __RC1_CN
#define __RC10_CN
#define __RC11_CN
#define __RC12_CN
#define __RC13_CN
#define __RC15_CN
#define __RC2_CN
#define __RC3_CN
#define __RC4_CN
#define __RC5_CN
#define __RC6_CN
#define __RC7_CN
#define __RC8_CN
#define __RC9_CN
#define __RD5_CN
#define __RD6_CN
#define __RD8_CN
#define __RE12_CN
#define __RE13_CN
#define __RE14_CN
#define __RE15_CN
#define __RF0_CN
#define __RF1_CN
#define __RG6_CN
#define __RG7_CN
#define __RG8_CN
#define __RG9_CN

#define __PORT_A_CN
#define __PORT_B_CN
#define __PORT_C_CN
#define __PORT_D_CN
#define __PORT_E_CN
#define __PORT_F_CN
#define __PORT_G_CN

#define PORT_SIZE  (16)
#define PORT_COUNT (7)

#define TRISA_REG_ADDRESS (0xE00)
#define PORTA_REG_ADDRESS (0xE02)
#define LATA_REG_ADDRESS (0xE04)
#define TRISB_REG_ADDRESS (0xE10)
#define PORTB_REG_ADDRESS (0xE12)
#define LATB_REG_ADDRESS (0xE14)
#define TRISC_REG_ADDRESS (0xE20)
#define PORTC_REG_ADDRESS (0xE22)
#define LATC_REG_ADDRESS (0xE24)
#define TRISD_REG_ADDRESS (0xE30)
#define PORTD_REG_ADDRESS (0xE32)
#define LATD_REG_ADDRESS (0xE34)
#define TRISE_REG_ADDRESS (0xE40)
#define PORTE_REG_ADDRESS (0xE42)
#define LATE_REG_ADDRESS (0xE44)
#define TRISF_REG_ADDRESS (0xE50)
#define PORTF_REG_ADDRESS (0xE52)
#define LATF_REG_ADDRESS (0xE54)
#define TRISG_REG_ADDRESS (0xE60)
#define PORTG_REG_ADDRESS (0xE62)
#define LATG_REG_ADDRESS (0xE64)
// EOF GPIO

// PPS
#define HAL_LL_OSCCON_REG_ADDRESS 0x742
#define HAL_LL_UART_PPS_ENABLED true
#define HAL_LL_SPI_PPS_ENABLED true
#define HAL_LL_PWM_PPS_ENABLED true
// PPS Register addresses and offsets
#define HAL_LL_RPOR0_REG_ADDRESS (0x680)
#define HAL_LL_RPOR1_REG_ADDRESS (0x682)
#define HAL_LL_RPOR2_REG_ADDRESS (0x684)
#define HAL_LL_RPOR3_REG_ADDRESS (0x686)
#define HAL_LL_RPOR4_REG_ADDRESS (0x688)
#define HAL_LL_RPOR5_REG_ADDRESS (0x68A)
#define HAL_LL_RPOR6_REG_ADDRESS (0x68C)
#define HAL_LL_RPOR7_REG_ADDRESS (0x68E)
#define HAL_LL_RPOR8_REG_ADDRESS (0x690)
#define HAL_LL_RPOR9_REG_ADDRESS (0x692)
#define HAL_LL_RPOR10_REG_ADDRESS (0x694)
#define HAL_LL_RPOR11_REG_ADDRESS (0x696)
#define HAL_LL_RPOR12_REG_ADDRESS (0x698)
#define HAL_LL_RPINR0_REG_ADDRESS (0x6A0)
#define HAL_LL_RPINR1_REG_ADDRESS (0x6A2)
#define HAL_LL_RPINR3_REG_ADDRESS (0x6A6)
#define HAL_LL_RPINR7_REG_ADDRESS (0x6AE)
#define HAL_LL_RPINR8_REG_ADDRESS (0x6B0)
#define HAL_LL_RPINR9_REG_ADDRESS (0x6B2)
#define HAL_LL_RPINR10_REG_ADDRESS (0x6B4)
#define HAL_LL_RPINR11_REG_ADDRESS (0x6B6)
#define HAL_LL_RPINR12_REG_ADDRESS (0x6B8)
#define HAL_LL_RPINR14_REG_ADDRESS (0x6BC)
#define HAL_LL_RPINR15_REG_ADDRESS (0x6BE)
#define HAL_LL_RPINR16_REG_ADDRESS (0x6C0)
#define HAL_LL_RPINR17_REG_ADDRESS (0x6C2)
#define HAL_LL_RPINR18_REG_ADDRESS (0x6C4)
#define HAL_LL_RPINR19_REG_ADDRESS (0x6C6)
#define HAL_LL_RPINR22_REG_ADDRESS (0x6CC)
#define HAL_LL_RPINR23_REG_ADDRESS (0x6CE)
#define HAL_LL_RPINR24_REG_ADDRESS (0x6D0)
#define HAL_LL_RPINR25_REG_ADDRESS (0x6D2)
#define HAL_LL_RPINR26_REG_ADDRESS (0x6D4)
#define HAL_LL_RPINR27_REG_ADDRESS (0x6D6)
#define HAL_LL_RPINR28_REG_ADDRESS (0x6D8)
#define HAL_LL_RPINR29_REG_ADDRESS (0x6DA)
#define HAL_LL_RPINR30_REG_ADDRESS (0x6DC)
#define HAL_LL_RPINR37_REG_ADDRESS (0x6EA)
#define HAL_LL_RPINR38_REG_ADDRESS (0x6EC)
#define HAL_LL_RPINR39_REG_ADDRESS (0x6EE)
#define HAL_LL_RPINR40_REG_ADDRESS (0x6F0)
#define HAL_LL_RPINR41_REG_ADDRESS (0x6F2)
// EOF PPS Register addresses and offsets
// EOF PPS

// IVT
#define USART1_RX_IVT_ADDRESS (0x002A)
#define USART1_TX_IVT_ADDRESS (0x002C)
#define USART2_RX_IVT_ADDRESS (0x0050)
#define USART2_TX_IVT_ADDRESS (0x0052)
#define USART3_RX_IVT_ADDRESS (0x00B8)
#define USART3_TX_IVT_ADDRESS (0x00BA)
#define USART4_RX_IVT_ADDRESS (0x00C4)
#define USART4_TX_IVT_ADDRESS (0x00C6)
// EOF IVT

#define _HAS_GIE_BIT_

#endif // _MCU_DEFINITIONS_H_
// ------------------------------------------------------------------------- END
