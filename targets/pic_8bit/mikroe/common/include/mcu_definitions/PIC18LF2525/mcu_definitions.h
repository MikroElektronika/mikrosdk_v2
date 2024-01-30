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
 * @brief MCU specific pin and module definitions.
 */

#ifndef _MCU_DEFINITIONS_H_
#define _MCU_DEFINITIONS_H_

#include "mcu_reg_addresses.h"
#include "can_definitions.h"

//ADC
#define HAL_LL_RA0_AN0_ADCON1 0
#define HAL_LL_RA1_AN1_ADCON1 1
#define HAL_LL_RA2_AN2_ADCON1 2
#define HAL_LL_RA3_AN3_ADCON1 3
#define HAL_LL_RA5_AN4_ADCON1 4
#define HAL_LL_RB0_AN12_ADCON1 12
#define HAL_LL_RB1_AN10_ADCON1 10
#define HAL_LL_RB2_AN8_ADCON1 8
#define HAL_LL_RB3_AN9_ADCON1 9
#define HAL_LL_RB4_AN11_ADCON1 11


#define HAL_LL_ADRESL_ADDRESS 0xFC3U
#define HAL_LL_ADCON2_ADDRESS 0xFC0U
#define HAL_LL_ADCON1_ADDRESS 0xFC1U
#define HAL_LL_ADCON0_ADDRESS 0xFC2U

#define HAL_LL_AN_COUNT 10
#define ADC_MODULE 1
#define ADC_MODULE_COUNT 1
//EOF ADC

//I2C
#define I2C_SCL_RC3
#define I2C_SDA_RC4


#define I2C_MODULE 1

#define I2C_MODULE_COUNT 1

#define HAL_LL_I2C_PPS_ENABLED false
//EOF I2C

//UART
#define UART_RX_RC7
#define UART_TX_RC6


#define UART_MODULE 1

#define UART_MODULE_COUNT 1

#define HAL_LL_UART_PPS_ENABLED false
//EOF UART

//SPI
#define SPI_MISO_RC4
#define SPI_MOSI_RC5
#define SPI_SCK_RC3


#define SPI_MODULE 1

#define SPI_MODULE_COUNT 1

#define HAL_LL_SPI_PPS_ENABLED false
//EOF SPI

//PWM
#define PWM_CCP1_RC2
#define PWM_CCP2_RB3
#define PWM_CCP2_RC1


#define CCP_MODULE_1 1
#define CCP_MODULE_2 2

#define CCP_MODULE_COUNT 2

#define TIM_MODULE_COUNT CCP_MODULE_COUNT

#define HAL_LL_TIM_PPS_ENABLED false
//EOF PWM

//IO
#define __RA0_CN
#define __RA1_CN
#define __RA2_CN
#define __RA3_CN
#define __RA4_CN
#define __RA5_CN
#define __RA6_CN
#define __RA7_CN
#define __RB0_CN
#define __RB1_CN
#define __RB2_CN
#define __RB3_CN
#define __RB4_CN
#define __RB5_CN
#define __RB6_CN
#define __RB7_CN
#define __RC0_CN
#define __RC1_CN
#define __RC2_CN
#define __RC3_CN
#define __RC4_CN
#define __RC5_CN
#define __RC6_CN
#define __RC7_CN
#define __RE3_CN

#define __PORT_A_CN
#define __PORT_B_CN
#define __PORT_C_CN
#define __PORT_E_CN
#define PORT_COUNT (5)
#define PORT_SIZE (8)
//EOF IO

// GPIO Register addresses and offsets
#define LATA_BASE_ADDRESS 0xF89U
#define LATB_BASE_ADDRESS 0xF8AU
#define LATC_BASE_ADDRESS 0xF8BU
#define LATE_BASE_ADDRESS 0x00U
#define PORTA_BASE_ADDRESS 0xF80U
#define PORTB_BASE_ADDRESS 0xF81U
#define PORTC_BASE_ADDRESS 0xF82U
#define PORTE_BASE_ADDRESS 0xF84U
#define TRISA_BASE_ADDRESS 0xF92U
#define TRISB_BASE_ADDRESS 0xF93U
#define TRISC_BASE_ADDRESS 0xF94U
#define TRISE_BASE_ADDRESS 0x00U
// EOF GPIO Register addresses and offsets

// PMD Register addresses
#define HAL_LL_PIE1_ADDRESS 0xF9DU
#define HAL_LL_PIE2_ADDRESS 0xFA0U
#define HAL_LL_PIR1_ADDRESS 0xF9EU
#define HAL_LL_PIR2_ADDRESS 0xFA1U
// EOF PMD Register addresses

// I2C and SPI Register addresses
#define HAL_LL_SSP1ADD_ADDRESS 0xFC8U
#define HAL_LL_SSP1BUF_ADDRESS 0xFC9U
#define HAL_LL_SSP1CON1_ADDRESS 0xFC6U
#define HAL_LL_SSP1CON2_ADDRESS 0xFC5U
#define HAL_LL_SSP1STAT_ADDRESS 0xFC7U
#define HAL_LL_SSPBUF_SPI_MASTER_MODULE_1 HAL_LL_SSP1BUF_ADDRESS
#define HAL_LL_SSPCON1_SPI_MASTER_MODULE_1 HAL_LL_SSP1CON1_ADDRESS
#define HAL_LL_SSPSTAT_SPI_MASTER_MODULE_1 HAL_LL_SSP1STAT_ADDRESS
// EOF I2C and SPI Register addresses

// PMD & PIR Register defines
#define HAL_LL_PIE_MODULE_UART1_ADDRESS HAL_LL_PIE1_ADDRESS
#define HAL_LL_PIR_MODULE_I2C1_ADDRESS HAL_LL_PIR1_ADDRESS
#define HAL_LL_PIR_MODULE_UART1_ADDRESS HAL_LL_PIR1_ADDRESS
#define HAL_LL_PIR_SSPIF_MODULE_1_BIT 3
#define HAL_LL_UART1_RCIF_BIT 5
#define HAL_LL_UART1_TXIF_BIT 4
// EOF PMD & PIR Register defines

// TMR Register addresses
#define HAL_LL_CCP1CON_ADDRESS 0xFBDU
#define HAL_LL_CCP2CON_ADDRESS 0xFBAU
#define HAL_LL_PR2_ADDRESS 0xFCBU
#define HAL_LL_T0CON_ADDRESS 0xFD5U
#define HAL_LL_T1CON_ADDRESS 0xFCDU
#define HAL_LL_T2CON_ADDRESS 0xFCAU
#define HAL_LL_T3CON_ADDRESS 0xFB1U
#define HAL_LL_CCPR1L_ADDRESS 0xFBEU
#define HAL_LL_CCPR2L_ADDRESS 0xFBBU
// EOF TMR Register addresses

// UART Register addresses
#define HAL_LL_BAUDCON1_ADDRESS 0xFB8U
#define HAL_LL_RCREG1_ADDRESS 0xFAEU
#define HAL_LL_RCSTA1_ADDRESS 0xFABU
#define HAL_LL_SPBRG1_ADDRESS 0xFAFU
#define HAL_LL_SPBRGH1_ADDRESS 0xFB0U
#define HAL_LL_TXREG1_ADDRESS 0xFADU
#define HAL_LL_TXSTA1_ADDRESS 0xFACU
// EOF UART Register addresses

// Unlock Register addresses
#define HAL_LL_EECON2_ADDRESS 0xFA7U
// EOF Unlock Register addresses

#define HAL_LL_ODCON_BIT_COUNT 0
#define HAL_LL_SLRCON_BIT_COUNT 0

// IRQ defines
#define HAL_LL_INTERRUPT_PRIORITY_LOW 0x0018
#define HAL_LL_INTERRUPT_PRIORITY_HIGH 0x0008
#define HAL_LL_INTERRUPT_PRIORITY HAL_LL_INTERRUPT_PRIORITY_HIGH
#define HAL_LL_IRQ_TXIE_BIT 4
#define HAL_LL_IRQ_RCIE_BIT 5
// EOF IRQ defines

#endif // _MCU_DEFINITIONS_H_
// ------------------------------------------------------------------------- END
