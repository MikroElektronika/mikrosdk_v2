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
* @file  mcu_definitions.h
* @brief dsPIC33EP128MC502 MCU specific pin and module definitions.
*/

#ifndef _MCU_DEFINITIONS_H_
#define _MCU_DEFINITIONS_H_

#include "mcu_reg_addresses.h"

// ADC
#define ADC1_RA0 (0)
#define ADC1_RA0_AN0 (0)
#define ADC1_RA1 (1)
#define ADC1_RA1_AN1 (1)
#define ADC1_RB0 (0)
#define ADC1_RB0_AN2 (2)
#define ADC1_RB1 (1)
#define ADC1_RB1_AN3 (3)
#define ADC1_RB2 (2)
#define ADC1_RB2_AN4 (4)
#define ADC1_RB3 (3)
#define ADC1_RB3_AN5 (5)
// Rest of ANSELx/ANSx bits
#define HAL_LL_ANSELA_ANSA4 (4)
#define HAL_LL_ANSELB_ANSB8 (8)
// EOF Rest of ANSELx/ANSx bits


#define ADC_MODULE_1 1
#define ADC_MODULE_COUNT 1
#define HAL_LL_AN_COUNT 6

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
#define HAL_LL_IPC12_REG_ADDRESS (0x858)
#define HAL_LL_IPC14_REG_ADDRESS (0x85C)
#define HAL_LL_IPC16_REG_ADDRESS (0x860)
#define HAL_LL_IPC17_REG_ADDRESS (0x862)
#define HAL_LL_IPC19_REG_ADDRESS (0x866)
#define HAL_LL_IPC23_REG_ADDRESS (0x86E)
#define HAL_LL_IPC24_REG_ADDRESS (0x870)
#define HAL_LL_IPC35_REG_ADDRESS (0x886)
#define HAL_LL_IPC36_REG_ADDRESS (0x888)
#define HAL_LL_IPC37_REG_ADDRESS (0x88A)
#define HAL_LL_ANSELA_REG_ADDRESS (0xE0E)
#define HAL_LL_ANSELB_REG_ADDRESS (0xE1E)
#define _ADC_ANSEL_
// EOF ADC Register addresses and offsets
// EOF ADC

// I2C
#define I2C1_RB8_SCL1_ALT
#define I2C1_RB9_SDA1_ALT
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
// EOF I2C Register addresses and offsets
// EOF I2C

// U(S)ART
#define UART1_RX_RA4_RP20 (20)
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
#define UART2_RX_RA4_RP20 (20)
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
#define SPI1_MISO_RB9
#define SPI1_MOSI_RB8
#define SPI1_SCK_RB7
#define SPI1_SS_RB0
#define SPI2_MISO_RA4_RP20 (20)
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
#define SPI2_SCK_RA4_RP20 (20)
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
#define PWM_CCP1_OC1_RA4_RP20 (20)
#define PWM_CCP2_OC1_RB11_RP43 (43)
#define PWM_CCP2_OC1_RB7_RP39 (39)
#define PWM_CCP2_OC2_RB10_RP42 (42)
#define PWM_CCP2_OC2_RB6_RP38 (38)
#define PWM_CCP2_OC2_RB9_RP41 (41)
#define PWM_CCP2_OC3_RB5_RP37 (37)
#define PWM_CCP2_OC4_RB3_RP35 (35)
#define PWM_CCP2_OC4_RB4_RP36 (36)
#define PWM_CCP2_OC4_RB8_RP40 (40)
#define PWM_CCP3_OC4_RA4_RP20 (20)
#define PWM_CCP4_OC1_RB10_RP42 (42)
#define PWM_CCP4_OC1_RB6_RP38 (38)
#define PWM_CCP4_OC1_RB9_RP41 (41)
#define PWM_CCP4_OC2_RB5_RP37 (37)
#define PWM_CCP4_OC3_RB3_RP35 (35)
#define PWM_CCP4_OC3_RB4_RP36 (36)
#define PWM_CCP4_OC3_RB8_RP40 (40)
#define PWM_CCP4_OC4_RB11_RP43 (43)
#define PWM_CCP4_OC4_RB7_RP39 (39)
#define PWM_CCP5_OC3_RA4_RP20 (20)

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
#define HAL_LL_PTCON_REG_ADDRESS (0xC00)
#define HAL_LL_PTPER_REG_ADDRESS (0xC04)
#define HAL_LL_MDC_REG_ADDRESS (0xC0A)
#define HAL_LL_PWMCON1_REG_ADDRESS (0xC20)
#define HAL_LL_IOCON1_REG_ADDRESS (0xC22)
#define HAL_LL_PDC1_REG_ADDRESS (0xC26)
#define HAL_LL_PWMCON2_REG_ADDRESS (0xC40)
#define HAL_LL_IOCON2_REG_ADDRESS (0xC42)
#define HAL_LL_PDC2_REG_ADDRESS (0xC46)
#define HAL_LL_PWMCON3_REG_ADDRESS (0xC60)
#define HAL_LL_IOCON3_REG_ADDRESS (0xC62)
#define HAL_LL_PDC3_REG_ADDRESS (0xC66)
// EOF TIM Register addresses and offsets
// EOF TIM

// GPIO
#define __RA0_CN
#define __RA1_CN
#define __RA2_CN
#define __RA3_CN
#define __RA4_CN
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

#define __PORT_A_CN
#define __PORT_B_CN

#define PORT_SIZE  (16)
#define PORT_COUNT (2)

#define TRISA_REG_ADDRESS (0xE00)
#define PORTA_REG_ADDRESS (0xE02)
#define LATA_REG_ADDRESS (0xE04)
#define TRISB_REG_ADDRESS (0xE10)
#define PORTB_REG_ADDRESS (0xE12)
#define LATB_REG_ADDRESS (0xE14)
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
#define HAL_LL_RPINR0_REG_ADDRESS (0x6A0)
#define HAL_LL_RPINR1_REG_ADDRESS (0x6A2)
#define HAL_LL_RPINR3_REG_ADDRESS (0x6A6)
#define HAL_LL_RPINR7_REG_ADDRESS (0x6AE)
#define HAL_LL_RPINR8_REG_ADDRESS (0x6B0)
#define HAL_LL_RPINR11_REG_ADDRESS (0x6B6)
#define HAL_LL_RPINR12_REG_ADDRESS (0x6B8)
#define HAL_LL_RPINR14_REG_ADDRESS (0x6BC)
#define HAL_LL_RPINR15_REG_ADDRESS (0x6BE)
#define HAL_LL_RPINR18_REG_ADDRESS (0x6C4)
#define HAL_LL_RPINR19_REG_ADDRESS (0x6C6)
#define HAL_LL_RPINR22_REG_ADDRESS (0x6CC)
#define HAL_LL_RPINR23_REG_ADDRESS (0x6CE)
#define HAL_LL_RPINR26_REG_ADDRESS (0x6D4)
#define HAL_LL_RPINR37_REG_ADDRESS (0x6EA)
#define HAL_LL_RPINR38_REG_ADDRESS (0x6EC)
#define HAL_LL_RPINR39_REG_ADDRESS (0x6EE)
// EOF PPS Register addresses and offsets
// EOF PPS

// IVT
#define USART1_RX_IVT_ADDRESS (0x002A)
#define USART1_TX_IVT_ADDRESS (0x002C)
#define USART2_RX_IVT_ADDRESS (0x0050)
#define USART2_TX_IVT_ADDRESS (0x0052)
// EOF IVT

#define _HAS_GIE_BIT_

#endif // _MCU_DEFINITIONS_H_
// ------------------------------------------------------------------------- END
