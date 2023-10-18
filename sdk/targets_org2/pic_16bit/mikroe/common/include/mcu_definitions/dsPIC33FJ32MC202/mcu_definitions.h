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
* @brief dsPIC33FJ32MC202 MCU specific pin and module definitions.
*/

#ifndef _MCU_DEFINITIONS_H_
#define _MCU_DEFINITIONS_H_

// ADC
#define ADC_RA0 (0)
#define ADC_RA0_AN0 (0)
#define ADC_RA1 (1)
#define ADC_RA1_AN1 (1)
#define ADC_RB0 (0)
#define ADC_RB0_AN2 (2)
#define ADC_RB1 (1)
#define ADC_RB1_AN3 (3)
#define ADC_RB2 (2)
#define ADC_RB2_AN4 (4)
#define ADC_RB3 (3)
#define ADC_RB3_AN5 (5)

#define ADC_MODULE 1
#define ADC_MODULE_COUNT 1
#define HAL_LL_AN_COUNT 6

#define SUPPORTED_ADC_RES_10_BIT
#define SUPPORTED_ADC_RES_12_BIT

// ADC Register addresses and offsets
#define HAL_LL_IFS0_REG_ADDRESS (0x84)
#define HAL_LL_IFS1_REG_ADDRESS (0x86)
#define HAL_LL_IFS3_REG_ADDRESS (0x8A)
#define HAL_LL_IFS4_REG_ADDRESS (0x8C)
#define HAL_LL_IEC0_REG_ADDRESS (0x94)
#define HAL_LL_IEC1_REG_ADDRESS (0x96)
#define HAL_LL_IEC3_REG_ADDRESS (0x9A)
#define HAL_LL_IEC4_REG_ADDRESS (0x9C)
#define HAL_LL_IPC0_REG_ADDRESS (0xA4)
#define HAL_LL_IPC1_REG_ADDRESS (0xA6)
#define HAL_LL_IPC2_REG_ADDRESS (0xA8)
#define HAL_LL_IPC3_REG_ADDRESS (0xAA)
#define HAL_LL_IPC4_REG_ADDRESS (0xAC)
#define HAL_LL_IPC5_REG_ADDRESS (0xAE)
#define HAL_LL_IPC7_REG_ADDRESS (0xB2)
#define HAL_LL_IPC14_REG_ADDRESS (0xC0)
#define HAL_LL_IPC15_REG_ADDRESS (0xC2)
#define HAL_LL_IPC16_REG_ADDRESS (0xC4)
#define HAL_LL_IPC18_REG_ADDRESS (0xC8)
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
#define HAL_LL_AD1PCFGL_REG_ADDRESS (0x32C)
#define HAL_LL_AD1CSSL_REG_ADDRESS (0x330)
#define _ADC_ADPCFGLH_
// EOF ADC Register addresses and offsets
// EOF ADC

// I2C
#define I2C1_SCL_RB6_ALT
#define I2C1_SCL_RB8
#define I2C1_SDA_RB5_ALT
#define I2C1_SDA_RB9

#define I2C_MODULE_1 1
#define I2C_MODULE_COUNT 1

// I2C Register addresses and offsets
#define HAL_LL_I2C1RCV_REG_ADDRESS (0x200)
#define HAL_LL_I2C1TRN_REG_ADDRESS (0x202)
#define HAL_LL_I2C1BRG_REG_ADDRESS (0x204)
#define HAL_LL_I2C1CON_REG_ADDRESS (0x206)
#define HAL_LL_I2C1STAT_REG_ADDRESS (0x208)
#define HAL_LL_FPOR_REG_ADDRESS (0xF8000C)
// EOF I2C Register addresses and offsets
// EOF I2C

// U(S)ART
#define UART1_RX_RB0_RP0
#define UART1_RX_RB1_RP1
#define UART1_RX_RB10_RP10
#define UART1_RX_RB11_RP11
#define UART1_RX_RB12_RP12
#define UART1_RX_RB13_RP13
#define UART1_RX_RB14_RP14
#define UART1_RX_RB15_RP15
#define UART1_RX_RB2_RP2
#define UART1_RX_RB3_RP3
#define UART1_RX_RB4_RP4
#define UART1_RX_RB5_RP5
#define UART1_RX_RB6_RP6
#define UART1_RX_RB7_RP7
#define UART1_RX_RB8_RP8
#define UART1_RX_RB9_RP9
#define UART1_TX_RB0_RP0
#define UART1_TX_RB1_RP1
#define UART1_TX_RB10_RP10
#define UART1_TX_RB11_RP11
#define UART1_TX_RB12_RP12
#define UART1_TX_RB13_RP13
#define UART1_TX_RB14_RP14
#define UART1_TX_RB15_RP15
#define UART1_TX_RB2_RP2
#define UART1_TX_RB3_RP3
#define UART1_TX_RB4_RP4
#define UART1_TX_RB5_RP5
#define UART1_TX_RB6_RP6
#define UART1_TX_RB7_RP7
#define UART1_TX_RB8_RP8
#define UART1_TX_RB9_RP9

#define UART_MODULE_1 1
#define UART_MODULE_COUNT 1

// U(S)ART Register addresses and offsets
#define HAL_LL_U1MODE_REG_ADDRESS (0x220)
#define HAL_LL_U1STA_REG_ADDRESS (0x222)
#define HAL_LL_U1TXREG_REG_ADDRESS (0x224)
#define HAL_LL_U1RXREG_REG_ADDRESS (0x226)
#define HAL_LL_U1BRG_REG_ADDRESS (0x228)
// EOF U(S)ART Register addresses and offsets
// EOF U(S)ART

// SPI
#define SPI1_MISO_RB0_RP0
#define SPI1_MISO_RB1_RP1
#define SPI1_MISO_RB10_RP10
#define SPI1_MISO_RB11_RP11
#define SPI1_MISO_RB12_RP12
#define SPI1_MISO_RB13_RP13
#define SPI1_MISO_RB14_RP14
#define SPI1_MISO_RB15_RP15
#define SPI1_MISO_RB2_RP2
#define SPI1_MISO_RB3_RP3
#define SPI1_MISO_RB4_RP4
#define SPI1_MISO_RB5_RP5
#define SPI1_MISO_RB6_RP6
#define SPI1_MISO_RB7_RP7
#define SPI1_MISO_RB8_RP8
#define SPI1_MISO_RB9_RP9
#define SPI1_MOSI_RB0_RP0
#define SPI1_MOSI_RB1_RP1
#define SPI1_MOSI_RB10_RP10
#define SPI1_MOSI_RB11_RP11
#define SPI1_MOSI_RB12_RP12
#define SPI1_MOSI_RB13_RP13
#define SPI1_MOSI_RB14_RP14
#define SPI1_MOSI_RB15_RP15
#define SPI1_MOSI_RB2_RP2
#define SPI1_MOSI_RB3_RP3
#define SPI1_MOSI_RB4_RP4
#define SPI1_MOSI_RB5_RP5
#define SPI1_MOSI_RB6_RP6
#define SPI1_MOSI_RB7_RP7
#define SPI1_MOSI_RB8_RP8
#define SPI1_MOSI_RB9_RP9
#define SPI1_SCK_RB0_RP0
#define SPI1_SCK_RB1_RP1
#define SPI1_SCK_RB10_RP10
#define SPI1_SCK_RB11_RP11
#define SPI1_SCK_RB12_RP12
#define SPI1_SCK_RB13_RP13
#define SPI1_SCK_RB14_RP14
#define SPI1_SCK_RB15_RP15
#define SPI1_SCK_RB2_RP2
#define SPI1_SCK_RB3_RP3
#define SPI1_SCK_RB4_RP4
#define SPI1_SCK_RB5_RP5
#define SPI1_SCK_RB6_RP6
#define SPI1_SCK_RB7_RP7
#define SPI1_SCK_RB8_RP8
#define SPI1_SCK_RB9_RP9

#define SPI_MODULE_1 1
#define SPI_MODULE_COUNT 1

// SPI Register addresses and offsets
#define HAL_LL_SPI1STAT_REG_ADDRESS (0x240)
#define HAL_LL_SPI1CON1_REG_ADDRESS (0x242)
#define HAL_LL_SPI1_CONTROL_REG_ADDRESS HAL_LL_SPI1CON1_REG_ADDRESS
#define HAL_LL_SPI1BUF_REG_ADDRESS (0x248)
// EOF SPI Register addresses and offsets
// EOF SPI

// TIM
#define PWM_CCP1_OC1_RB0_RP0
#define PWM_CCP1_OC1_RB1_RP1
#define PWM_CCP1_OC1_RB10_RP10
#define PWM_CCP1_OC1_RB11_RP11
#define PWM_CCP1_OC1_RB12_RP12
#define PWM_CCP1_OC1_RB13_RP13
#define PWM_CCP1_OC1_RB14_RP14
#define PWM_CCP1_OC1_RB15_RP15
#define PWM_CCP1_OC1_RB2_RP2
#define PWM_CCP1_OC1_RB3_RP3
#define PWM_CCP1_OC1_RB4_RP4
#define PWM_CCP1_OC1_RB5_RP5
#define PWM_CCP1_OC1_RB6_RP6
#define PWM_CCP1_OC1_RB7_RP7
#define PWM_CCP1_OC1_RB8_RP8
#define PWM_CCP1_OC1_RB9_RP9
#define PWM_CCP1_OC2_RB0_RP0
#define PWM_CCP1_OC2_RB1_RP1
#define PWM_CCP1_OC2_RB10_RP10
#define PWM_CCP1_OC2_RB11_RP11
#define PWM_CCP1_OC2_RB12_RP12
#define PWM_CCP1_OC2_RB13_RP13
#define PWM_CCP1_OC2_RB14_RP14
#define PWM_CCP1_OC2_RB15_RP15
#define PWM_CCP1_OC2_RB2_RP2
#define PWM_CCP1_OC2_RB3_RP3
#define PWM_CCP1_OC2_RB4_RP4
#define PWM_CCP1_OC2_RB5_RP5
#define PWM_CCP1_OC2_RB6_RP6
#define PWM_CCP1_OC2_RB7_RP7
#define PWM_CCP1_OC2_RB8_RP8
#define PWM_CCP1_OC2_RB9_RP9
#define PWM_CCP2_OC1_RB0_RP0
#define PWM_CCP2_OC1_RB1_RP1
#define PWM_CCP2_OC1_RB10_RP10
#define PWM_CCP2_OC1_RB11_RP11
#define PWM_CCP2_OC1_RB12_RP12
#define PWM_CCP2_OC1_RB13_RP13
#define PWM_CCP2_OC1_RB14_RP14
#define PWM_CCP2_OC1_RB15_RP15
#define PWM_CCP2_OC1_RB2_RP2
#define PWM_CCP2_OC1_RB3_RP3
#define PWM_CCP2_OC1_RB4_RP4
#define PWM_CCP2_OC1_RB5_RP5
#define PWM_CCP2_OC1_RB6_RP6
#define PWM_CCP2_OC1_RB7_RP7
#define PWM_CCP2_OC1_RB8_RP8
#define PWM_CCP2_OC1_RB9_RP9
#define PWM_CCP2_OC2_RB0_RP0
#define PWM_CCP2_OC2_RB1_RP1
#define PWM_CCP2_OC2_RB10_RP10
#define PWM_CCP2_OC2_RB11_RP11
#define PWM_CCP2_OC2_RB12_RP12
#define PWM_CCP2_OC2_RB13_RP13
#define PWM_CCP2_OC2_RB14_RP14
#define PWM_CCP2_OC2_RB15_RP15
#define PWM_CCP2_OC2_RB2_RP2
#define PWM_CCP2_OC2_RB3_RP3
#define PWM_CCP2_OC2_RB4_RP4
#define PWM_CCP2_OC2_RB5_RP5
#define PWM_CCP2_OC2_RB6_RP6
#define PWM_CCP2_OC2_RB7_RP7
#define PWM_CCP2_OC2_RB8_RP8
#define PWM_CCP2_OC2_RB9_RP9
#define PWM_CCP3_OC1_RB0_RP0
#define PWM_CCP3_OC1_RB1_RP1
#define PWM_CCP3_OC1_RB10_RP10
#define PWM_CCP3_OC1_RB11_RP11
#define PWM_CCP3_OC1_RB12_RP12
#define PWM_CCP3_OC1_RB13_RP13
#define PWM_CCP3_OC1_RB14_RP14
#define PWM_CCP3_OC1_RB15_RP15
#define PWM_CCP3_OC1_RB2_RP2
#define PWM_CCP3_OC1_RB3_RP3
#define PWM_CCP3_OC1_RB4_RP4
#define PWM_CCP3_OC1_RB5_RP5
#define PWM_CCP3_OC1_RB6_RP6
#define PWM_CCP3_OC1_RB7_RP7
#define PWM_CCP3_OC1_RB8_RP8
#define PWM_CCP3_OC1_RB9_RP9
#define PWM_CCP3_OC2_RB0_RP0
#define PWM_CCP3_OC2_RB1_RP1
#define PWM_CCP3_OC2_RB10_RP10
#define PWM_CCP3_OC2_RB11_RP11
#define PWM_CCP3_OC2_RB12_RP12
#define PWM_CCP3_OC2_RB13_RP13
#define PWM_CCP3_OC2_RB14_RP14
#define PWM_CCP3_OC2_RB15_RP15
#define PWM_CCP3_OC2_RB2_RP2
#define PWM_CCP3_OC2_RB3_RP3
#define PWM_CCP3_OC2_RB4_RP4
#define PWM_CCP3_OC2_RB5_RP5
#define PWM_CCP3_OC2_RB6_RP6
#define PWM_CCP3_OC2_RB7_RP7
#define PWM_CCP3_OC2_RB8_RP8
#define PWM_CCP3_OC2_RB9_RP9

#define CCP_MODULE_1 1
#define CCP_MODULE_2 2
#define CCP_MODULE_3 3

#define CCP_MODULE_COUNT 3
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
#define HAL_LL_OC1RS_REG_ADDRESS (0x180)
#define HAL_LL_OC1R_REG_ADDRESS (0x182)
#define HAL_LL_OC1CON_REG_ADDRESS (0x184)
#define HAL_LL_OC2RS_REG_ADDRESS (0x186)
#define HAL_LL_OC2R_REG_ADDRESS (0x188)
#define HAL_LL_OC2CON_REG_ADDRESS (0x18A)
#define HAL_LL_P1TCON_REG_ADDRESS (0x1C0)
#define HAL_LL_P1TPER_REG_ADDRESS (0x1C4)
#define HAL_LL_PWM1CON1_REG_ADDRESS (0x1C8)
#define HAL_LL_P1DC1_REG_ADDRESS (0x1D6)
#define HAL_LL_P2TCON_REG_ADDRESS (0x5C0)
#define HAL_LL_P2TPER_REG_ADDRESS (0x5C4)
#define HAL_LL_PWM2CON1_REG_ADDRESS (0x5C8)
#define HAL_LL_P2DC1_REG_ADDRESS (0x5D6)
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

#define TRISA_REG_ADDRESS (0x2C0)
#define PORTA_REG_ADDRESS (0x2C2)
#define LATA_REG_ADDRESS (0x2C4)
#define TRISB_REG_ADDRESS (0x2C8)
#define PORTB_REG_ADDRESS (0x2CA)
#define LATB_REG_ADDRESS (0x2CC)
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
#define HAL_LL_RPINR7_REG_ADDRESS (0x68E)
#define HAL_LL_RPINR10_REG_ADDRESS (0x694)
#define HAL_LL_RPINR11_REG_ADDRESS (0x696)
#define HAL_LL_RPINR12_REG_ADDRESS (0x698)
#define HAL_LL_RPINR13_REG_ADDRESS (0x69A)
#define HAL_LL_RPINR14_REG_ADDRESS (0x69C)
#define HAL_LL_RPINR15_REG_ADDRESS (0x69E)
#define HAL_LL_RPINR18_REG_ADDRESS (0x6A4)
#define HAL_LL_RPINR20_REG_ADDRESS (0x6A8)
#define HAL_LL_RPINR21_REG_ADDRESS (0x6AA)
#define HAL_LL_RPOR0_REG_ADDRESS (0x6C0)
#define HAL_LL_RPOR1_REG_ADDRESS (0x6C2)
#define HAL_LL_RPOR2_REG_ADDRESS (0x6C4)
#define HAL_LL_RPOR3_REG_ADDRESS (0x6C6)
#define HAL_LL_RPOR4_REG_ADDRESS (0x6C8)
#define HAL_LL_RPOR5_REG_ADDRESS (0x6CA)
#define HAL_LL_RPOR6_REG_ADDRESS (0x6CC)
#define HAL_LL_RPOR7_REG_ADDRESS (0x6CE)
// EOF PPS Register addresses and offsets
// EOF PPS

// IVT
#define USART1_RX_IVT_ADDRESS (0x002A)
#define USART1_TX_IVT_ADDRESS (0x002C)
// EOF IVT

#endif // _MCU_DEFINITIONS_H_
// ------------------------------------------------------------------------- END
