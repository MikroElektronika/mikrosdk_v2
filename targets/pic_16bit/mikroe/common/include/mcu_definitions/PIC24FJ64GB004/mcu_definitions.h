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
* @file  mcu_definitions.h
* @brief PIC24FJ64GB004 MCU specific pin and module definitions.
*/

#ifndef _MCU_DEFINITIONS_H_
#define _MCU_DEFINITIONS_H_

// ADC
#define ADC1_RA0 (0)
#define ADC1_RA0_AN0 (0)
#define ADC1_RA1 (1)
#define ADC1_RA1_AN1 (1)
#define ADC1_RB0 (0)
#define ADC1_RB0_AN2 (2)
#define ADC1_RB1 (1)
#define ADC1_RB1_AN3 (3)
#define ADC1_RB13 (13)
#define ADC1_RB13_AN11 (11)
#define ADC1_RB14 (14)
#define ADC1_RB14_AN10 (10)
#define ADC1_RB15 (15)
#define ADC1_RB15_AN9 (9)
#define ADC1_RB2 (2)
#define ADC1_RB2_AN4 (4)
#define ADC1_RB3 (3)
#define ADC1_RB3_AN5 (5)
#define ADC1_RC0 (0)
#define ADC1_RC0_AN6 (6)
#define ADC1_RC1 (1)
#define ADC1_RC1_AN7 (7)
#define ADC1_RC2 (2)
#define ADC1_RC2_AN8 (8)
#define ADC1_RC3 (3)
#define ADC1_RC3_AN12 (12)

#define ADC_MODULE_1 1
#define ADC_MODULE_COUNT 1
#define HAL_LL_AN_COUNT 13

#define SUPPORTED_ADC_RES_10_BIT

// ADC Register addresses and offsets
#define HAL_LL_IFS0_REG_ADDRESS (0x84)
#define HAL_LL_IFS1_REG_ADDRESS (0x86)
#define HAL_LL_IFS2_REG_ADDRESS (0x88)
#define HAL_LL_IFS3_REG_ADDRESS (0x8A)
#define HAL_LL_IFS4_REG_ADDRESS (0x8C)
#define HAL_LL_IFS5_REG_ADDRESS (0x8E)
#define HAL_LL_IEC0_REG_ADDRESS (0x94)
#define HAL_LL_IEC1_REG_ADDRESS (0x96)
#define HAL_LL_IEC2_REG_ADDRESS (0x98)
#define HAL_LL_IEC3_REG_ADDRESS (0x9A)
#define HAL_LL_IEC4_REG_ADDRESS (0x9C)
#define HAL_LL_IEC5_REG_ADDRESS (0x9E)
#define HAL_LL_IPC0_REG_ADDRESS (0xA4)
#define HAL_LL_IPC1_REG_ADDRESS (0xA6)
#define HAL_LL_IPC2_REG_ADDRESS (0xA8)
#define HAL_LL_IPC3_REG_ADDRESS (0xAA)
#define HAL_LL_IPC4_REG_ADDRESS (0xAC)
#define HAL_LL_IPC5_REG_ADDRESS (0xAE)
#define HAL_LL_IPC6_REG_ADDRESS (0xB0)
#define HAL_LL_IPC7_REG_ADDRESS (0xB2)
#define HAL_LL_IPC8_REG_ADDRESS (0xB4)
#define HAL_LL_IPC9_REG_ADDRESS (0xB6)
#define HAL_LL_IPC10_REG_ADDRESS (0xB8)
#define HAL_LL_IPC11_REG_ADDRESS (0xBA)
#define HAL_LL_IPC12_REG_ADDRESS (0xBC)
#define HAL_LL_IPC15_REG_ADDRESS (0xC2)
#define HAL_LL_IPC16_REG_ADDRESS (0xC4)
#define HAL_LL_IPC18_REG_ADDRESS (0xC8)
#define HAL_LL_IPC19_REG_ADDRESS (0xCA)
#define HAL_LL_IPC21_REG_ADDRESS (0xCE)
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
#define HAL_LL_AD1CHS_REG_ADDRESS (0x328)
#define HAL_LL_AD1PCFG_REG_ADDRESS (0x32C)
#define HAL_LL_AD1CSSL_REG_ADDRESS (0x330)
#define _ADC_AD1PCFG_
// EOF ADC Register addresses and offsets
// EOF ADC

// I2C
#define I2C1_RA0_SDA1
#define I2C1_RA1_SCL1
#define I2C1_RB8_SCL1
#define I2C1_RB9_SDA1
#define I2C2_RB2_SDA2
#define I2C2_RB3_SCL2

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
#define HAL_LL_PADCFG1_REG_ADDRESS (0x2FC)
// EOF I2C Register addresses and offsets
// EOF I2C

// U(S)ART
#define UART1_RX_RA0_RP5 (5)
#define UART1_RX_RA1_RP6 (6)
#define UART1_RX_RB0_RP0 (0)
#define UART1_RX_RB1_RP1 (1)
#define UART1_RX_RB10_RP10 (10)
#define UART1_RX_RB11_RP11 (11)
#define UART1_RX_RB13_RP13 (13)
#define UART1_RX_RB14_RP14 (14)
#define UART1_RX_RB15_RP15 (15)
#define UART1_RX_RB2_RP2 (2)
#define UART1_RX_RB3_RP3 (3)
#define UART1_RX_RB4_RP4 (4)
#define UART1_RX_RB7_RP7 (7)
#define UART1_RX_RB8_RP8 (8)
#define UART1_RX_RB9_RP9 (9)
#define UART1_RX_RC0_RP16 (16)
#define UART1_RX_RC1_RP17 (17)
#define UART1_RX_RC2_RP18 (18)
#define UART1_RX_RC3_RP19 (19)
#define UART1_RX_RC4_RP20 (20)
#define UART1_RX_RC5_RP21 (21)
#define UART1_RX_RC6_RP22 (22)
#define UART1_RX_RC7_RP23 (23)
#define UART1_RX_RC8_RP24 (24)
#define UART1_RX_RC9_RP25 (25)
#define UART1_TX_RA0_RP5 (5)
#define UART1_TX_RA1_RP6 (6)
#define UART1_TX_RB0_RP0 (0)
#define UART1_TX_RB1_RP1 (1)
#define UART1_TX_RB10_RP10 (10)
#define UART1_TX_RB11_RP11 (11)
#define UART1_TX_RB13_RP13 (13)
#define UART1_TX_RB14_RP14 (14)
#define UART1_TX_RB15_RP15 (15)
#define UART1_TX_RB2_RP2 (2)
#define UART1_TX_RB3_RP3 (3)
#define UART1_TX_RB4_RP4 (4)
#define UART1_TX_RB7_RP7 (7)
#define UART1_TX_RB8_RP8 (8)
#define UART1_TX_RB9_RP9 (9)
#define UART1_TX_RC0_RP16 (16)
#define UART1_TX_RC1_RP17 (17)
#define UART1_TX_RC2_RP18 (18)
#define UART1_TX_RC3_RP19 (19)
#define UART1_TX_RC4_RP20 (20)
#define UART1_TX_RC5_RP21 (21)
#define UART1_TX_RC6_RP22 (22)
#define UART1_TX_RC7_RP23 (23)
#define UART1_TX_RC8_RP24 (24)
#define UART1_TX_RC9_RP25 (25)
#define UART2_RX_RA0_RP5 (5)
#define UART2_RX_RA1_RP6 (6)
#define UART2_RX_RB0_RP0 (0)
#define UART2_RX_RB1_RP1 (1)
#define UART2_RX_RB10_RP10 (10)
#define UART2_RX_RB11_RP11 (11)
#define UART2_RX_RB13_RP13 (13)
#define UART2_RX_RB14_RP14 (14)
#define UART2_RX_RB15_RP15 (15)
#define UART2_RX_RB2_RP2 (2)
#define UART2_RX_RB3_RP3 (3)
#define UART2_RX_RB4_RP4 (4)
#define UART2_RX_RB7_RP7 (7)
#define UART2_RX_RB8_RP8 (8)
#define UART2_RX_RB9_RP9 (9)
#define UART2_RX_RC0_RP16 (16)
#define UART2_RX_RC1_RP17 (17)
#define UART2_RX_RC2_RP18 (18)
#define UART2_RX_RC3_RP19 (19)
#define UART2_RX_RC4_RP20 (20)
#define UART2_RX_RC5_RP21 (21)
#define UART2_RX_RC6_RP22 (22)
#define UART2_RX_RC7_RP23 (23)
#define UART2_RX_RC8_RP24 (24)
#define UART2_RX_RC9_RP25 (25)
#define UART2_TX_RA0_RP5 (5)
#define UART2_TX_RA1_RP6 (6)
#define UART2_TX_RB0_RP0 (0)
#define UART2_TX_RB1_RP1 (1)
#define UART2_TX_RB10_RP10 (10)
#define UART2_TX_RB11_RP11 (11)
#define UART2_TX_RB13_RP13 (13)
#define UART2_TX_RB14_RP14 (14)
#define UART2_TX_RB15_RP15 (15)
#define UART2_TX_RB2_RP2 (2)
#define UART2_TX_RB3_RP3 (3)
#define UART2_TX_RB4_RP4 (4)
#define UART2_TX_RB7_RP7 (7)
#define UART2_TX_RB8_RP8 (8)
#define UART2_TX_RB9_RP9 (9)
#define UART2_TX_RC0_RP16 (16)
#define UART2_TX_RC1_RP17 (17)
#define UART2_TX_RC2_RP18 (18)
#define UART2_TX_RC3_RP19 (19)
#define UART2_TX_RC4_RP20 (20)
#define UART2_TX_RC5_RP21 (21)
#define UART2_TX_RC6_RP22 (22)
#define UART2_TX_RC7_RP23 (23)
#define UART2_TX_RC8_RP24 (24)
#define UART2_TX_RC9_RP25 (25)

#define UART_MODULE_1 1
#define UART_MODULE_2 2
#define UART_MODULE_COUNT 2

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
// EOF U(S)ART Register addresses and offsets
// EOF U(S)ART

// SPI
#define SPI1_MISO_RA0_RP5 (5)
#define SPI1_MISO_RA1_RP6 (6)
#define SPI1_MISO_RB0_RP0 (0)
#define SPI1_MISO_RB1_RP1 (1)
#define SPI1_MISO_RB10_RP10 (10)
#define SPI1_MISO_RB11_RP11 (11)
#define SPI1_MISO_RB13_RP13 (13)
#define SPI1_MISO_RB14_RP14 (14)
#define SPI1_MISO_RB15_RP15 (15)
#define SPI1_MISO_RB2_RP2 (2)
#define SPI1_MISO_RB3_RP3 (3)
#define SPI1_MISO_RB4_RP4 (4)
#define SPI1_MISO_RB7_RP7 (7)
#define SPI1_MISO_RB8_RP8 (8)
#define SPI1_MISO_RB9_RP9 (9)
#define SPI1_MISO_RC0_RP16 (16)
#define SPI1_MISO_RC1_RP17 (17)
#define SPI1_MISO_RC2_RP18 (18)
#define SPI1_MISO_RC3_RP19 (19)
#define SPI1_MISO_RC4_RP20 (20)
#define SPI1_MISO_RC5_RP21 (21)
#define SPI1_MISO_RC6_RP22 (22)
#define SPI1_MISO_RC7_RP23 (23)
#define SPI1_MISO_RC8_RP24 (24)
#define SPI1_MISO_RC9_RP25 (25)
#define SPI1_MOSI_RA0_RP5 (5)
#define SPI1_MOSI_RA1_RP6 (6)
#define SPI1_MOSI_RB0_RP0 (0)
#define SPI1_MOSI_RB1_RP1 (1)
#define SPI1_MOSI_RB10_RP10 (10)
#define SPI1_MOSI_RB11_RP11 (11)
#define SPI1_MOSI_RB13_RP13 (13)
#define SPI1_MOSI_RB14_RP14 (14)
#define SPI1_MOSI_RB15_RP15 (15)
#define SPI1_MOSI_RB2_RP2 (2)
#define SPI1_MOSI_RB3_RP3 (3)
#define SPI1_MOSI_RB4_RP4 (4)
#define SPI1_MOSI_RB7_RP7 (7)
#define SPI1_MOSI_RB8_RP8 (8)
#define SPI1_MOSI_RB9_RP9 (9)
#define SPI1_MOSI_RC0_RP16 (16)
#define SPI1_MOSI_RC1_RP17 (17)
#define SPI1_MOSI_RC2_RP18 (18)
#define SPI1_MOSI_RC3_RP19 (19)
#define SPI1_MOSI_RC4_RP20 (20)
#define SPI1_MOSI_RC5_RP21 (21)
#define SPI1_MOSI_RC6_RP22 (22)
#define SPI1_MOSI_RC7_RP23 (23)
#define SPI1_MOSI_RC8_RP24 (24)
#define SPI1_MOSI_RC9_RP25 (25)
#define SPI1_SCK_RA0_RP5 (5)
#define SPI1_SCK_RA1_RP6 (6)
#define SPI1_SCK_RB0_RP0 (0)
#define SPI1_SCK_RB1_RP1 (1)
#define SPI1_SCK_RB10_RP10 (10)
#define SPI1_SCK_RB11_RP11 (11)
#define SPI1_SCK_RB13_RP13 (13)
#define SPI1_SCK_RB14_RP14 (14)
#define SPI1_SCK_RB15_RP15 (15)
#define SPI1_SCK_RB2_RP2 (2)
#define SPI1_SCK_RB3_RP3 (3)
#define SPI1_SCK_RB4_RP4 (4)
#define SPI1_SCK_RB7_RP7 (7)
#define SPI1_SCK_RB8_RP8 (8)
#define SPI1_SCK_RB9_RP9 (9)
#define SPI1_SCK_RC0_RP16 (16)
#define SPI1_SCK_RC1_RP17 (17)
#define SPI1_SCK_RC2_RP18 (18)
#define SPI1_SCK_RC3_RP19 (19)
#define SPI1_SCK_RC4_RP20 (20)
#define SPI1_SCK_RC5_RP21 (21)
#define SPI1_SCK_RC6_RP22 (22)
#define SPI1_SCK_RC7_RP23 (23)
#define SPI1_SCK_RC8_RP24 (24)
#define SPI1_SCK_RC9_RP25 (25)
#define SPI2_MISO_RA0_RP5 (5)
#define SPI2_MISO_RA1_RP6 (6)
#define SPI2_MISO_RB0_RP0 (0)
#define SPI2_MISO_RB1_RP1 (1)
#define SPI2_MISO_RB10_RP10 (10)
#define SPI2_MISO_RB11_RP11 (11)
#define SPI2_MISO_RB13_RP13 (13)
#define SPI2_MISO_RB14_RP14 (14)
#define SPI2_MISO_RB15_RP15 (15)
#define SPI2_MISO_RB2_RP2 (2)
#define SPI2_MISO_RB3_RP3 (3)
#define SPI2_MISO_RB4_RP4 (4)
#define SPI2_MISO_RB7_RP7 (7)
#define SPI2_MISO_RB8_RP8 (8)
#define SPI2_MISO_RB9_RP9 (9)
#define SPI2_MISO_RC0_RP16 (16)
#define SPI2_MISO_RC1_RP17 (17)
#define SPI2_MISO_RC2_RP18 (18)
#define SPI2_MISO_RC3_RP19 (19)
#define SPI2_MISO_RC4_RP20 (20)
#define SPI2_MISO_RC5_RP21 (21)
#define SPI2_MISO_RC6_RP22 (22)
#define SPI2_MISO_RC7_RP23 (23)
#define SPI2_MISO_RC8_RP24 (24)
#define SPI2_MISO_RC9_RP25 (25)
#define SPI2_MOSI_RA0_RP5 (5)
#define SPI2_MOSI_RA1_RP6 (6)
#define SPI2_MOSI_RB0_RP0 (0)
#define SPI2_MOSI_RB1_RP1 (1)
#define SPI2_MOSI_RB10_RP10 (10)
#define SPI2_MOSI_RB11_RP11 (11)
#define SPI2_MOSI_RB13_RP13 (13)
#define SPI2_MOSI_RB14_RP14 (14)
#define SPI2_MOSI_RB15_RP15 (15)
#define SPI2_MOSI_RB2_RP2 (2)
#define SPI2_MOSI_RB3_RP3 (3)
#define SPI2_MOSI_RB4_RP4 (4)
#define SPI2_MOSI_RB7_RP7 (7)
#define SPI2_MOSI_RB8_RP8 (8)
#define SPI2_MOSI_RB9_RP9 (9)
#define SPI2_MOSI_RC0_RP16 (16)
#define SPI2_MOSI_RC1_RP17 (17)
#define SPI2_MOSI_RC2_RP18 (18)
#define SPI2_MOSI_RC3_RP19 (19)
#define SPI2_MOSI_RC4_RP20 (20)
#define SPI2_MOSI_RC5_RP21 (21)
#define SPI2_MOSI_RC6_RP22 (22)
#define SPI2_MOSI_RC7_RP23 (23)
#define SPI2_MOSI_RC8_RP24 (24)
#define SPI2_MOSI_RC9_RP25 (25)
#define SPI2_SCK_RA0_RP5 (5)
#define SPI2_SCK_RA1_RP6 (6)
#define SPI2_SCK_RB0_RP0 (0)
#define SPI2_SCK_RB1_RP1 (1)
#define SPI2_SCK_RB10_RP10 (10)
#define SPI2_SCK_RB11_RP11 (11)
#define SPI2_SCK_RB13_RP13 (13)
#define SPI2_SCK_RB14_RP14 (14)
#define SPI2_SCK_RB15_RP15 (15)
#define SPI2_SCK_RB2_RP2 (2)
#define SPI2_SCK_RB3_RP3 (3)
#define SPI2_SCK_RB4_RP4 (4)
#define SPI2_SCK_RB7_RP7 (7)
#define SPI2_SCK_RB8_RP8 (8)
#define SPI2_SCK_RB9_RP9 (9)
#define SPI2_SCK_RC0_RP16 (16)
#define SPI2_SCK_RC1_RP17 (17)
#define SPI2_SCK_RC2_RP18 (18)
#define SPI2_SCK_RC3_RP19 (19)
#define SPI2_SCK_RC4_RP20 (20)
#define SPI2_SCK_RC5_RP21 (21)
#define SPI2_SCK_RC6_RP22 (22)
#define SPI2_SCK_RC7_RP23 (23)
#define SPI2_SCK_RC8_RP24 (24)
#define SPI2_SCK_RC9_RP25 (25)

#define SPI_MODULE_1 1
#define SPI_MODULE_2 2
#define SPI_MODULE_COUNT 2

// SPI Register addresses and offsets
#define HAL_LL_SPI1STAT_REG_ADDRESS (0x240)
#define HAL_LL_SPI1CON1_REG_ADDRESS (0x242)
#define HAL_LL_SPI1_CONTROL_REG_ADDRESS HAL_LL_SPI1CON1_REG_ADDRESS
#define HAL_LL_SPI1BUF_REG_ADDRESS (0x248)
#define HAL_LL_SPI2STAT_REG_ADDRESS (0x260)
#define HAL_LL_SPI2CON1_REG_ADDRESS (0x262)
#define HAL_LL_SPI2_CONTROL_REG_ADDRESS HAL_LL_SPI2CON1_REG_ADDRESS
#define HAL_LL_SPI2BUF_REG_ADDRESS (0x268)
// EOF SPI Register addresses and offsets
// EOF SPI

// TIM
#define PWM_CCP1_OC1_RA0_RP5 (5)
#define PWM_CCP1_OC1_RA1_RP6 (6)
#define PWM_CCP2_OC1_RB1_RP1 (1)
#define PWM_CCP2_OC1_RB8_RP8 (8)
#define PWM_CCP2_OC1_RB9_RP9 (9)
#define PWM_CCP2_OC2_RB2_RP2 (2)
#define PWM_CCP2_OC3_RB13_RP13 (13)
#define PWM_CCP2_OC3_RB3_RP3 (3)
#define PWM_CCP2_OC3_RB7_RP7 (7)
#define PWM_CCP2_OC4_RB11_RP11 (11)
#define PWM_CCP2_OC4_RB14_RP14 (14)
#define PWM_CCP2_OC5_RB0_RP0 (0)
#define PWM_CCP2_OC5_RB10_RP10 (10)
#define PWM_CCP2_OC5_RB15_RP15 (15)
#define PWM_CCP2_OC5_RB4_RP4 (4)
#define PWM_CCP3_OC1_RC9_RP25 (25)
#define PWM_CCP3_OC2_RC2_RP18 (18)
#define PWM_CCP3_OC2_RC7_RP23 (23)
#define PWM_CCP3_OC3_RC0_RP16 (16)
#define PWM_CCP3_OC3_RC4_RP20 (20)
#define PWM_CCP3_OC4_RC8_RP24 (24)
#define PWM_CCP3_OC5_RC1_RP17 (17)
#define PWM_CCP3_OC5_RC3_RP19 (19)
#define PWM_CCP3_OC5_RC5_RP21 (21)
#define PWM_CCP3_OC5_RC6_RP22 (22)
#define PWM_CCP4_OC2_RA0_RP5 (5)
#define PWM_CCP4_OC2_RA1_RP6 (6)
#define PWM_CCP5_OC1_RB0_RP0 (0)
#define PWM_CCP5_OC1_RB10_RP10 (10)
#define PWM_CCP5_OC1_RB15_RP15 (15)
#define PWM_CCP5_OC1_RB4_RP4 (4)
#define PWM_CCP5_OC2_RB1_RP1 (1)
#define PWM_CCP5_OC2_RB8_RP8 (8)
#define PWM_CCP5_OC2_RB9_RP9 (9)
#define PWM_CCP5_OC3_RB2_RP2 (2)
#define PWM_CCP5_OC4_RB13_RP13 (13)
#define PWM_CCP5_OC4_RB3_RP3 (3)
#define PWM_CCP5_OC4_RB7_RP7 (7)
#define PWM_CCP5_OC5_RB11_RP11 (11)
#define PWM_CCP5_OC5_RB14_RP14 (14)

#define CCP_MODULE_1 1
#define CCP_MODULE_2 2
#define CCP_MODULE_3 3
#define CCP_MODULE_4 4
#define CCP_MODULE_5 5

#define CCP_MODULE_COUNT 5
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
#define HAL_LL_OC1CON1_REG_ADDRESS (0x190)
#define HAL_LL_OC1CON2_REG_ADDRESS (0x192)
#define HAL_LL_OC1RS_REG_ADDRESS (0x194)
#define HAL_LL_OC1R_REG_ADDRESS (0x196)
#define HAL_LL_OC2CON1_REG_ADDRESS (0x19A)
#define HAL_LL_OC2CON2_REG_ADDRESS (0x19C)
#define HAL_LL_OC2RS_REG_ADDRESS (0x19E)
#define HAL_LL_OC2R_REG_ADDRESS (0x1A0)
#define HAL_LL_OC2TMR_REG_ADDRESS (0x1A2)
#define HAL_LL_OC3CON1_REG_ADDRESS (0x1A4)
#define HAL_LL_OC3CON2_REG_ADDRESS (0x1A6)
#define HAL_LL_OC3RS_REG_ADDRESS (0x1A8)
#define HAL_LL_OC3R_REG_ADDRESS (0x1AA)
#define HAL_LL_OC3TMR_REG_ADDRESS (0x1AC)
#define HAL_LL_OC4CON1_REG_ADDRESS (0x1AE)
#define HAL_LL_OC4CON2_REG_ADDRESS (0x1B0)
#define HAL_LL_OC4RS_REG_ADDRESS (0x1B2)
#define HAL_LL_OC4R_REG_ADDRESS (0x1B4)
#define HAL_LL_OC4TMR_REG_ADDRESS (0x1B6)
#define HAL_LL_OC5CON1_REG_ADDRESS (0x1B8)
#define HAL_LL_OC5CON2_REG_ADDRESS (0x1BA)
#define HAL_LL_OC5RS_REG_ADDRESS (0x1BC)
#define HAL_LL_OC5R_REG_ADDRESS (0x1BE)
#define HAL_LL_OC5TMR_REG_ADDRESS (0x1C0)
// EOF TIM Register addresses and offsets
// EOF TIM

// GPIO
#define __RA0_CN
#define __RA1_CN
#define __RA10_CN
#define __RA2_CN
#define __RA3_CN
#define __RA4_CN
#define __RA7_CN
#define __RA8_CN
#define __RA9_CN
#define __RB0_CN
#define __RB1_CN
#define __RB10_CN
#define __RB11_CN
#define __RB13_CN
#define __RB14_CN
#define __RB15_CN
#define __RB2_CN
#define __RB3_CN
#define __RB4_CN
#define __RB5_CN
#define __RB7_CN
#define __RB8_CN
#define __RB9_CN
#define __RC0_CN
#define __RC1_CN
#define __RC2_CN
#define __RC3_CN
#define __RC4_CN
#define __RC5_CN
#define __RC6_CN
#define __RC7_CN
#define __RC8_CN
#define __RC9_CN

#define __PORT_A_CN
#define __PORT_B_CN
#define __PORT_C_CN

#define PORT_SIZE  (16)
#define PORT_COUNT (3)

#define TRISA_REG_ADDRESS (0x2C0)
#define PORTA_REG_ADDRESS (0x2C2)
#define LATA_REG_ADDRESS (0x2C4)
#define TRISB_REG_ADDRESS (0x2C8)
#define PORTB_REG_ADDRESS (0x2CA)
#define LATB_REG_ADDRESS (0x2CC)
#define TRISC_REG_ADDRESS (0x2D0)
#define PORTC_REG_ADDRESS (0x2D2)
#define LATC_REG_ADDRESS (0x2D4)
// EOF GPIO

// PPS
#define HAL_LL_OSCCON_REG_ADDRESS 0x742
#define HAL_LL_UART_PPS_ENABLED true
#define HAL_LL_SPI_PPS_ENABLED true
#define HAL_LL_PWM_PPS_ENABLED true
// PPS Register addresses and offsets
#define HAL_LL_RPINR0_REG_ADDRESS (0x680)
#define HAL_LL_RPINR1_REG_ADDRESS (0x682)
#define HAL_LL_RPINR3_REG_ADDRESS (0x686)
#define HAL_LL_RPINR4_REG_ADDRESS (0x688)
#define HAL_LL_RPINR7_REG_ADDRESS (0x68E)
#define HAL_LL_RPINR8_REG_ADDRESS (0x690)
#define HAL_LL_RPINR9_REG_ADDRESS (0x692)
#define HAL_LL_RPINR11_REG_ADDRESS (0x696)
#define HAL_LL_RPINR18_REG_ADDRESS (0x6A4)
#define HAL_LL_RPINR19_REG_ADDRESS (0x6A6)
#define HAL_LL_RPINR20_REG_ADDRESS (0x6A8)
#define HAL_LL_RPINR21_REG_ADDRESS (0x6AA)
#define HAL_LL_RPINR22_REG_ADDRESS (0x6AC)
#define HAL_LL_RPINR23_REG_ADDRESS (0x6AE)
#define HAL_LL_RPOR0_REG_ADDRESS (0x6C0)
#define HAL_LL_RPOR1_REG_ADDRESS (0x6C2)
#define HAL_LL_RPOR2_REG_ADDRESS (0x6C4)
#define HAL_LL_RPOR3_REG_ADDRESS (0x6C6)
#define HAL_LL_RPOR4_REG_ADDRESS (0x6C8)
#define HAL_LL_RPOR5_REG_ADDRESS (0x6CA)
#define HAL_LL_RPOR6_REG_ADDRESS (0x6CC)
#define HAL_LL_RPOR7_REG_ADDRESS (0x6CE)
#define HAL_LL_RPOR8_REG_ADDRESS (0x6D0)
#define HAL_LL_RPOR9_REG_ADDRESS (0x6D2)
#define HAL_LL_RPOR10_REG_ADDRESS (0x6D4)
#define HAL_LL_RPOR11_REG_ADDRESS (0x6D6)
#define HAL_LL_RPOR12_REG_ADDRESS (0x6D8)
// EOF PPS Register addresses and offsets
// EOF PPS

// IVT
#define USART1_RX_IVT_ADDRESS (0x002A)
#define USART1_TX_IVT_ADDRESS (0x002C)
#define USART2_RX_IVT_ADDRESS (0x0050)
#define USART2_TX_IVT_ADDRESS (0x0052)
// EOF IVT

#endif // _MCU_DEFINITIONS_H_
// ------------------------------------------------------------------------- END
