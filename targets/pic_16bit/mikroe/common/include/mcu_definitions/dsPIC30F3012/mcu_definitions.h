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
* @brief dsPIC30F3012 MCU specific pin and module definitions.
*/

#ifndef _MCU_DEFINITIONS_H_
#define _MCU_DEFINITIONS_H_

#include "mcu_reg_addresses.h"

// ADC
#define ADC_RB0 (0)
#define ADC_RB0_AN0 (0)
#define ADC_RB1 (1)
#define ADC_RB1_AN1 (1)
#define ADC_RB2 (2)
#define ADC_RB2_AN2 (2)
#define ADC_RB3 (3)
#define ADC_RB3_AN3 (3)
#define ADC_RB4 (4)
#define ADC_RB4_AN4 (4)
#define ADC_RB5 (5)
#define ADC_RB5_AN5 (5)
#define ADC_RB6 (6)
#define ADC_RB6_AN6 (6)
#define ADC_RB7 (7)
#define ADC_RB7_AN7 (7)

#define ADC_MODULE 1
#define ADC_MODULE_COUNT 1
#define HAL_LL_AN_COUNT 8

#define SUPPORTED_ADC_RES_12_BIT

// ADC Register addresses and offsets
#define HAL_LL_IFS0_REG_ADDRESS (0x84)
#define HAL_LL_IFS1_REG_ADDRESS (0x86)
#define HAL_LL_IFS2_REG_ADDRESS (0x88)
#define HAL_LL_IEC0_REG_ADDRESS (0x8C)
#define HAL_LL_IEC1_REG_ADDRESS (0x8E)
#define HAL_LL_IEC2_REG_ADDRESS (0x90)
#define HAL_LL_IPC0_REG_ADDRESS (0x94)
#define HAL_LL_IPC1_REG_ADDRESS (0x96)
#define HAL_LL_IPC2_REG_ADDRESS (0x98)
#define HAL_LL_IPC3_REG_ADDRESS (0x9A)
#define HAL_LL_IPC4_REG_ADDRESS (0x9C)
#define HAL_LL_IPC5_REG_ADDRESS (0x9E)
#define HAL_LL_IPC10_REG_ADDRESS (0xA8)
#define HAL_LL_ADCBUF0_REG_ADDRESS (0x280)
#define HAL_LL_ADCBUF1_REG_ADDRESS (0x282)
#define HAL_LL_ADCBUF2_REG_ADDRESS (0x284)
#define HAL_LL_ADCBUF3_REG_ADDRESS (0x286)
#define HAL_LL_ADCBUF4_REG_ADDRESS (0x288)
#define HAL_LL_ADCBUF5_REG_ADDRESS (0x28A)
#define HAL_LL_ADCBUF6_REG_ADDRESS (0x28C)
#define HAL_LL_ADCBUF7_REG_ADDRESS (0x28E)
#define HAL_LL_ADCBUF8_REG_ADDRESS (0x290)
#define HAL_LL_ADCBUF9_REG_ADDRESS (0x292)
#define HAL_LL_ADCBUFA_REG_ADDRESS (0x294)
#define HAL_LL_ADCBUFB_REG_ADDRESS (0x296)
#define HAL_LL_ADCBUFC_REG_ADDRESS (0x298)
#define HAL_LL_ADCBUFD_REG_ADDRESS (0x29A)
#define HAL_LL_ADCBUFE_REG_ADDRESS (0x29C)
#define HAL_LL_ADCBUFF_REG_ADDRESS (0x29E)
#define HAL_LL_ADCON1_REG_ADDRESS (0x2A0)
#define HAL_LL_ADCON2_REG_ADDRESS (0x2A2)
#define HAL_LL_ADCON3_REG_ADDRESS (0x2A4)
#define HAL_LL_ADCHS_REG_ADDRESS (0x2A6)
#define HAL_LL_ADPCFG_REG_ADDRESS (0x2A8)
#define HAL_LL_ADCSSL_REG_ADDRESS (0x2AA)
#define _ADC_ADPCFG_
// EOF ADC Register addresses and offsets
// EOF ADC

// I2C
#define I2C_SCL_RB4
#define I2C_SDA_RB5

#define I2C_MODULE 1
#define I2C_MODULE_COUNT 1

// I2C Register addresses and offsets
#define HAL_LL_I2CRCV_REG_ADDRESS (0x200)
#define HAL_LL_I2CTRN_REG_ADDRESS (0x202)
#define HAL_LL_I2CBRG_REG_ADDRESS (0x204)
#define HAL_LL_I2CCON_REG_ADDRESS (0x206)
#define HAL_LL_I2CSTAT_REG_ADDRESS (0x208)
// EOF I2C Register addresses and offsets
// EOF I2C

// U(S)ART
#define UART1_RX_RB5
#define UART1_RX_RC14_ALT
#define UART1_TX_RB4
#define UART1_TX_RC13_ALT

#define UART_MODULE_1 1
#define UART_MODULE_COUNT 1

// U(S)ART Register addresses and offsets
#define HAL_LL_U1MODE_REG_ADDRESS (0x20C)
#define HAL_LL_U1STA_REG_ADDRESS (0x20E)
#define HAL_LL_U1TXREG_REG_ADDRESS (0x210)
#define HAL_LL_U1RXREG_REG_ADDRESS (0x212)
#define HAL_LL_U1BRG_REG_ADDRESS (0x214)
// EOF U(S)ART Register addresses and offsets
// EOF U(S)ART

// SPI
#define SPI1_MISO_RB5
#define SPI1_MOSI_RB4
#define SPI1_SCK_RB6

#define SPI_MODULE_1 1
#define SPI_MODULE_COUNT 1

// SPI Register addresses and offsets
#define HAL_LL_SPI1STAT_REG_ADDRESS (0x220)
#define HAL_LL_SPI1CON_REG_ADDRESS (0x222)
#define HAL_LL_SPI1_CONTROL_REG_ADDRESS HAL_LL_SPI1CON_REG_ADDRESS
#define HAL_LL_SPI1BUF_REG_ADDRESS (0x224)
// EOF SPI Register addresses and offsets
// EOF SPI

// TIM
#define PWM_CCP1_RB7
#define PWM_CCP1_RD0
#define PWM_CCP2_RB7
#define PWM_CCP2_RD0
#define PWM_CCP3_RB7
#define PWM_CCP3_RD0

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
// EOF TIM Register addresses and offsets
// EOF TIM

// GPIO
#define __RB0_CN
#define __RB1_CN
#define __RB2_CN
#define __RB3_CN
#define __RB4_CN
#define __RB5_CN
#define __RB6_CN
#define __RB7_CN
#define __RC13_CN
#define __RC14_CN
#define __RC15_CN
#define __RD0_CN

#define __PORT_B_CN
#define __PORT_C_CN
#define __PORT_D_CN

#define PORT_SIZE  (16)
#define PORT_COUNT (3)

#define TRISB_REG_ADDRESS (0x2C6)
#define PORTB_REG_ADDRESS (0x2C8)
#define LATB_REG_ADDRESS (0x2CA)
#define TRISC_REG_ADDRESS (0x2CC)
#define PORTC_REG_ADDRESS (0x2CE)
#define LATC_REG_ADDRESS (0x2D0)
#define TRISD_REG_ADDRESS (0x2D2)
#define PORTD_REG_ADDRESS (0x2D4)
#define LATD_REG_ADDRESS (0x2D6)
// EOF GPIO

// PPS
// PPS Register addresses and offsets
// No PPS for dsPIC30F3012
// EOF PPS Register addresses and offsets
// EOF PPS

// IVT
#define USART1_RX_IVT_ADDRESS (0x0026)
#define USART1_TX_IVT_ADDRESS (0x0028)
// EOF IVT

#endif // _MCU_DEFINITIONS_H_
// ------------------------------------------------------------------------- END
