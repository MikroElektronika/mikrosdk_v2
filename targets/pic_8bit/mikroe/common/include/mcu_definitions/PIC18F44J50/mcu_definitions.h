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
 * @brief MCU specific pin and module definitions.
 */

#ifndef _MCU_DEFINITIONS_H_
#define _MCU_DEFINITIONS_H_

#include "mcu_reg_addresses.h"
#include "can_definitions.h"

//ADC
#define HAL_LL_RA0_AN0_ANCON0_BIT 0
#define HAL_LL_RA0_AN0_ANCON0 0
#define HAL_LL_RA1_AN1_ANCON0_BIT 1
#define HAL_LL_RA1_AN1_ANCON0 1
#define HAL_LL_RA2_AN2_ANCON0_BIT 2
#define HAL_LL_RA2_AN2_ANCON0 2
#define HAL_LL_RA3_AN3_ANCON0_BIT 3
#define HAL_LL_RA3_AN3_ANCON0 3
#define HAL_LL_RA5_AN4_ANCON0_BIT 4
#define HAL_LL_RA5_AN4_ANCON0 4
#define HAL_LL_RB0_AN12_ANCON1_BIT 4
#define HAL_LL_RB0_AN12_ANCON1 12
#define HAL_LL_RB1_AN10_ANCON1_BIT 2
#define HAL_LL_RB1_AN10_ANCON1 10
#define HAL_LL_RB2_AN8_ANCON1_BIT 0
#define HAL_LL_RB2_AN8_ANCON1 8
#define HAL_LL_RB3_AN9_ANCON1_BIT 1
#define HAL_LL_RB3_AN9_ANCON1 9
#define HAL_LL_RC2_AN11_ANCON1_BIT 3
#define HAL_LL_RC2_AN11_ANCON1 11
#define HAL_LL_RE0_AN5_ANCON0_BIT 5
#define HAL_LL_RE0_AN5_ANCON0 5
#define HAL_LL_RE1_AN6_ANCON0_BIT 6
#define HAL_LL_RE1_AN6_ANCON0 6
#define HAL_LL_RE2_AN7_ANCON0_BIT 7
#define HAL_LL_RE2_AN7_ANCON0 7


#define HAL_LL_ADRESL_ADDRESS 0xFC3U
#define HAL_LL_ANCON1_ADDRESS 0xF49U
#define HAL_LL_ANCON0_ADDRESS 0xF48U
#define HAL_LL_ADCON1_ADDRESS 0xFC1U
#define HAL_LL_ADCON0_ADDRESS 0xFC2U

#define HAL_LL_AN_COUNT 13
#define ADC_MODULE 1
#define ADC_MODULE_COUNT 1
//EOF ADC

//I2C
#define I2C1_SCL_RB4
#define I2C1_SDA_RB5
#define I2C2_SCL_RD0
#define I2C2_SDA_RD1


#define I2C_MODULE_1 1
#define I2C_MODULE_2 2

#define I2C_MODULE_COUNT 2

#define HAL_LL_I2C_PPS_ENABLED false
//EOF I2C

//UART
#define UART1_TX_RC6
#define UART2_TX_RA0
#define UART2_TX_RA1
#define UART2_TX_RA5
#define UART2_TX_RB0
#define UART2_TX_RB1
#define UART2_TX_RB2
#define UART2_TX_RB3
#define UART2_TX_RB4
#define UART2_TX_RB5
#define UART2_TX_RB6
#define UART2_TX_RB7
#define UART2_TX_RC0
#define UART2_TX_RC1
#define UART2_TX_RC2
#define UART2_TX_RC6
#define UART2_TX_RC7
#define UART2_TX_RD2
#define UART2_TX_RD3
#define UART2_TX_RD4
#define UART2_TX_RD5
#define UART2_TX_RD6
#define UART2_TX_RD7

#define UART1_RX_RC7
#define UART2_RX_RA0
#define UART2_RX_RA1
#define UART2_RX_RA5
#define UART2_RX_RB0
#define UART2_RX_RB1
#define UART2_RX_RB2
#define UART2_RX_RB3
#define UART2_RX_RB4
#define UART2_RX_RB5
#define UART2_RX_RB6
#define UART2_RX_RB7
#define UART2_RX_RC0
#define UART2_RX_RC1
#define UART2_RX_RC2
#define UART2_RX_RC6
#define UART2_RX_RC7
#define UART2_RX_RD2
#define UART2_RX_RD3
#define UART2_RX_RD4
#define UART2_RX_RD5
#define UART2_RX_RD6
#define UART2_RX_RD7


#define UART_MODULE_1 1
#define UART_MODULE_2 2

#define UART_MODULE_COUNT 2

#define HAL_LL_UART_PPS_ENABLED true
//EOF UART

//SPI
#define SPI1_MISO_RB5
#define SPI1_MOSI_RC7
#define SPI1_SCK_RB4
#define SPI2_MISO_RA0
#define SPI2_MISO_RA1
#define SPI2_MISO_RA5
#define SPI2_MISO_RB0
#define SPI2_MISO_RB1
#define SPI2_MISO_RB2
#define SPI2_MISO_RB3
#define SPI2_MISO_RB4
#define SPI2_MISO_RB5
#define SPI2_MISO_RB6
#define SPI2_MISO_RB7
#define SPI2_MISO_RC0
#define SPI2_MISO_RC1
#define SPI2_MISO_RC2
#define SPI2_MISO_RC6
#define SPI2_MISO_RC7
#define SPI2_MISO_RD2
#define SPI2_MISO_RD3
#define SPI2_MISO_RD4
#define SPI2_MISO_RD5
#define SPI2_MISO_RD6
#define SPI2_MISO_RD7
#define SPI2_MOSI_RA0
#define SPI2_MOSI_RA1
#define SPI2_MOSI_RA5
#define SPI2_MOSI_RB0
#define SPI2_MOSI_RB1
#define SPI2_MOSI_RB2
#define SPI2_MOSI_RB3
#define SPI2_MOSI_RB4
#define SPI2_MOSI_RB5
#define SPI2_MOSI_RB6
#define SPI2_MOSI_RB7
#define SPI2_MOSI_RC0
#define SPI2_MOSI_RC1
#define SPI2_MOSI_RC2
#define SPI2_MOSI_RC6
#define SPI2_MOSI_RC7
#define SPI2_MOSI_RD2
#define SPI2_MOSI_RD3
#define SPI2_MOSI_RD4
#define SPI2_MOSI_RD5
#define SPI2_MOSI_RD6
#define SPI2_MOSI_RD7
#define SPI2_SCK_RA0
#define SPI2_SCK_RA1
#define SPI2_SCK_RA5
#define SPI2_SCK_RB0
#define SPI2_SCK_RB1
#define SPI2_SCK_RB2
#define SPI2_SCK_RB3
#define SPI2_SCK_RB4
#define SPI2_SCK_RB5
#define SPI2_SCK_RB6
#define SPI2_SCK_RB7
#define SPI2_SCK_RC0
#define SPI2_SCK_RC1
#define SPI2_SCK_RC2
#define SPI2_SCK_RC6
#define SPI2_SCK_RC7
#define SPI2_SCK_RD2
#define SPI2_SCK_RD3
#define SPI2_SCK_RD4
#define SPI2_SCK_RD5
#define SPI2_SCK_RD6
#define SPI2_SCK_RD7


#define SPI_MODULE_1 1
#define SPI_MODULE_2 2

#define SPI_MODULE_COUNT 2

#define HAL_LL_SPI_PPS_ENABLED true
//EOF SPI

//PWM
#define PWM_CCP1_RA0
#define PWM_CCP1_RA1
#define PWM_CCP1_RA5
#define PWM_CCP1_RB0
#define PWM_CCP1_RB1
#define PWM_CCP1_RB2
#define PWM_CCP1_RB3
#define PWM_CCP1_RB4
#define PWM_CCP1_RB5
#define PWM_CCP1_RB6
#define PWM_CCP1_RB7
#define PWM_CCP1_RC0
#define PWM_CCP1_RC1
#define PWM_CCP1_RC2
#define PWM_CCP1_RC6
#define PWM_CCP1_RC7
#define PWM_CCP1_RD2
#define PWM_CCP1_RD3
#define PWM_CCP1_RD4
#define PWM_CCP1_RD5
#define PWM_CCP1_RD6
#define PWM_CCP1_RD7
#define PWM_CCP2_RA0
#define PWM_CCP2_RA1
#define PWM_CCP2_RA5
#define PWM_CCP2_RB0
#define PWM_CCP2_RB1
#define PWM_CCP2_RB2
#define PWM_CCP2_RB3
#define PWM_CCP2_RB4
#define PWM_CCP2_RB5
#define PWM_CCP2_RB6
#define PWM_CCP2_RB7
#define PWM_CCP2_RC0
#define PWM_CCP2_RC1
#define PWM_CCP2_RC2
#define PWM_CCP2_RC6
#define PWM_CCP2_RC7
#define PWM_CCP2_RD2
#define PWM_CCP2_RD3
#define PWM_CCP2_RD4
#define PWM_CCP2_RD5
#define PWM_CCP2_RD6
#define PWM_CCP2_RD7

#define CCP_MODULE_1 1
#define CCP_MODULE_2 2

#define CCP_MODULE_COUNT 2

#define TIM_MODULE_COUNT CCP_MODULE_COUNT

#define HAL_LL_TIM_PPS_ENABLED true
//EOF PWM

//IO
#define __RA0_CN
#define __RA1_CN
#define __RA2_CN
#define __RA3_CN
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
#define __RC4_CN
#define __RC5_CN
#define __RC6_CN
#define __RC7_CN
#define __RD0_CN
#define __RD1_CN
#define __RD2_CN
#define __RD3_CN
#define __RD4_CN
#define __RD5_CN
#define __RD6_CN
#define __RD7_CN
#define __RE0_CN
#define __RE1_CN
#define __RE2_CN

#define __PORT_A_CN
#define __PORT_B_CN
#define __PORT_C_CN
#define __PORT_D_CN
#define __PORT_E_CN
#define PORT_COUNT (5)
#define PORT_SIZE (8)
//EOF IO

// GPIO Register addresses and offsets
#define LATA_BASE_ADDRESS 0xF89U
#define LATB_BASE_ADDRESS 0xF8AU
#define LATC_BASE_ADDRESS 0xF8BU
#define LATD_BASE_ADDRESS 0xF8CU
#define LATE_BASE_ADDRESS 0xF8DU
#define PORTA_BASE_ADDRESS 0xF80U
#define PORTB_BASE_ADDRESS 0xF81U
#define PORTC_BASE_ADDRESS 0xF82U
#define PORTD_BASE_ADDRESS 0xF83U
#define PORTE_BASE_ADDRESS 0xF84U
#define TRISA_BASE_ADDRESS 0xF92U
#define TRISB_BASE_ADDRESS 0xF93U
#define TRISC_BASE_ADDRESS 0xF94U
#define TRISD_BASE_ADDRESS 0xF95U
#define TRISE_BASE_ADDRESS 0xF96U
// EOF GPIO Register addresses and offsets

// PMD Register addresses
#define HAL_LL_PIE1_ADDRESS 0xF9DU
#define HAL_LL_PIE2_ADDRESS 0xFA0U
#define HAL_LL_PIE3_ADDRESS 0xFA3U
#define HAL_LL_PIR1_ADDRESS 0xF9EU
#define HAL_LL_PIR2_ADDRESS 0xFA1U
#define HAL_LL_PIR3_ADDRESS 0xFA4U
// EOF PMD Register addresses

// I2C and SPI Register addresses
#define HAL_LL_SSP1ADD_ADDRESS 0xFC8U
#define HAL_LL_SSP1BUF_ADDRESS 0xFC9U
#define HAL_LL_SSP1CON1_ADDRESS 0xFC6U
#define HAL_LL_SSP1CON2_ADDRESS 0xFC5U
#define HAL_LL_SSP1STAT_ADDRESS 0xFC7U
#define HAL_LL_SSP2ADD_ADDRESS 0xF74U
#define HAL_LL_SSP2BUF_ADDRESS 0xF75U
#define HAL_LL_SSP2CON1_ADDRESS 0xF72U
#define HAL_LL_SSP2CON2_ADDRESS 0xF71U
#define HAL_LL_SSP2STAT_ADDRESS 0xF73U
#define HAL_LL_SSPBUF_SPI_MASTER_MODULE_1 HAL_LL_SSP1BUF_ADDRESS
#define HAL_LL_SSPBUF_SPI_MASTER_MODULE_2 HAL_LL_SSP2BUF_ADDRESS
#define HAL_LL_SSPCON1_SPI_MASTER_MODULE_1 HAL_LL_SSP1CON1_ADDRESS
#define HAL_LL_SSPCON1_SPI_MASTER_MODULE_2 HAL_LL_SSP2CON1_ADDRESS
#define HAL_LL_SSPSTAT_SPI_MASTER_MODULE_1 HAL_LL_SSP1STAT_ADDRESS
#define HAL_LL_SSPSTAT_SPI_MASTER_MODULE_2 HAL_LL_SSP2STAT_ADDRESS
// EOF I2C and SPI Register addresses

// PMD & PIR Register defines
#define HAL_LL_PIE_MODULE_UART1_ADDRESS HAL_LL_PIE1_ADDRESS
#define HAL_LL_PIE_MODULE_UART2_ADDRESS HAL_LL_PIE3_ADDRESS
#define HAL_LL_PIR_MODULE_I2C1_ADDRESS HAL_LL_PIR1_ADDRESS
#define HAL_LL_PIR_MODULE_I2C2_ADDRESS HAL_LL_PIR3_ADDRESS
#define HAL_LL_PIR_MODULE_UART1_ADDRESS HAL_LL_PIR1_ADDRESS
#define HAL_LL_PIR_MODULE_UART2_ADDRESS HAL_LL_PIR3_ADDRESS
#define HAL_LL_PIR_SSPIF_MODULE_1_BIT 3
#define HAL_LL_PIR_SSPIF_MODULE_2_BIT 7
#define HAL_LL_UART1_RCIF_BIT 5
#define HAL_LL_UART1_TXIF_BIT 4
#define HAL_LL_UART2_RCIF_BIT 5
#define HAL_LL_UART2_TXIF_BIT 4
// EOF PMD & PIR Register defines

// TMR Register addresses
#define HAL_LL_PSTR2CON_ADDRESS 0xFB9U
#define HAL_LL_PSTR1CON_ADDRESS 0xFBFU
#define HAL_LL_CCP1CON_ADDRESS 0xFBAU
#define HAL_LL_CCP2CON_ADDRESS 0xFB4U
#define HAL_LL_PR2_ADDRESS 0xFCBU
#define HAL_LL_PR4_ADDRESS 0xF77U
#define HAL_LL_T0CON_ADDRESS 0xFD5U
#define HAL_LL_T1CON_ADDRESS 0xFCDU
#define HAL_LL_T2CON_ADDRESS 0xFCAU
#define HAL_LL_T3CON_ADDRESS 0xF79U
#define HAL_LL_T4CON_ADDRESS 0xF76U
#define HAL_LL_CCPR1L_ADDRESS 0xFBBU
#define HAL_LL_CCPR2L_ADDRESS 0xFB5U
// EOF TMR Register addresses

// ODCON Register addresses and bit defines
#define HAL_LL_ODCON_NUMERIC
#define HAL_LL_ODCON1_ADDRESS 0xF42U
#define HAL_LL_ODCON1_ECCP1OD_BIT 0
#define HAL_LL_ODCON1_ECCP2OD_BIT 1
#define HAL_LL_ODCON2_ADDRESS 0xF41U
#define HAL_LL_ODCON3_ADDRESS 0xF40U
#define HAL_LL_ODCON_BIT_COUNT 2

// EOF ODCON Register addresses and bit defines

// UART Register addresses
#define HAL_LL_BAUDCON1_ADDRESS 0xF7EU
#define HAL_LL_BAUDCON2_ADDRESS 0xF7CU
#define HAL_LL_RCREG1_ADDRESS 0xFAFU
#define HAL_LL_RCREG2_ADDRESS 0xFAAU
#define HAL_LL_RCSTA1_ADDRESS 0xFACU
#define HAL_LL_RCSTA2_ADDRESS 0xF9CU
#define HAL_LL_SPBRG1_ADDRESS 0xFB0U
#define HAL_LL_SPBRG2_ADDRESS 0xFABU
#define HAL_LL_SPBRGH1_ADDRESS 0xF7FU
#define HAL_LL_SPBRGH2_ADDRESS 0xF7DU
#define HAL_LL_TXREG1_ADDRESS 0xFAEU
#define HAL_LL_TXREG2_ADDRESS 0xFA9U
#define HAL_LL_TXSTA1_ADDRESS 0xFADU
#define HAL_LL_TXSTA2_ADDRESS 0xFA8U
// EOF UART Register addresses

// RPOR Register addresses
#define HAL_LL_RPOR0_ADDRESS 0xEC6U
#define HAL_LL_RPOR1_ADDRESS 0xEC7U
#define HAL_LL_RPOR2_ADDRESS 0xEC8U
#define HAL_LL_RPOR3_ADDRESS 0xEC9U
#define HAL_LL_RPOR4_ADDRESS 0xECAU
#define HAL_LL_RPOR5_ADDRESS 0xECBU
#define HAL_LL_RPOR6_ADDRESS 0xECCU
#define HAL_LL_RPOR7_ADDRESS 0xECDU
#define HAL_LL_RPOR8_ADDRESS 0xECEU
#define HAL_LL_RPOR9_ADDRESS 0xECFU
#define HAL_LL_RPOR10_ADDRESS 0xED0U
#define HAL_LL_RPOR11_ADDRESS 0xED1U
#define HAL_LL_RPOR12_ADDRESS 0xED2U
#define HAL_LL_RPOR13_ADDRESS 0xED3U
#define HAL_LL_RPOR17_ADDRESS 0xED7U
#define HAL_LL_RPOR18_ADDRESS 0xED8U
#define HAL_LL_RPOR19_ADDRESS 0xED9U
#define HAL_LL_RPOR20_ADDRESS 0xEDAU
#define HAL_LL_RPOR21_ADDRESS 0xEDBU
#define HAL_LL_RPOR22_ADDRESS 0xEDCU
#define HAL_LL_RPOR23_ADDRESS 0xEDDU
#define HAL_LL_RPOR24_ADDRESS 0xEDEU
// EOF RPOR Register addresses

// RPINR Register addresses
#define HAL_LL_RPINR1_ADDRESS 0xEE7U
#define HAL_LL_RPINR2_ADDRESS 0xEE8U
#define HAL_LL_RPINR3_ADDRESS 0xEE9U
#define HAL_LL_RPINR4_ADDRESS 0xEEAU
#define HAL_LL_RPINR6_ADDRESS 0xEECU
#define HAL_LL_RPINR7_ADDRESS 0xEEDU
#define HAL_LL_RPINR8_ADDRESS 0xEEEU
#define HAL_LL_RPINR12_ADDRESS 0xEF2U
#define HAL_LL_RPINR13_ADDRESS 0xEF3U
#define HAL_LL_RPINR16_ADDRESS 0xEF6U
#define HAL_LL_RPINR17_ADDRESS 0xEF7U
#define HAL_LL_RPINR21_ADDRESS 0xEFBU
#define HAL_LL_RPINR22_ADDRESS 0xEFCU
#define HAL_LL_RPINR23_ADDRESS 0xEFDU
#define HAL_LL_RPINR24_ADDRESS 0xEFEU
// EOF RPINR Register addresses

// Unlock Register addresses
#define HAL_LL_PPSCON_ADDRESS 0xEFFU
#define HAL_LL_EECON2_ADDRESS 0xFA7U
// EOF Unlock Register addresses

#define HAL_LL_SLRCON_BIT_COUNT 0

// IRQ defines
#define HAL_LL_INTERRUPT_PRIORITY_LOW 0x0018
#define HAL_LL_INTERRUPT_PRIORITY_HIGH 0x0008
#define HAL_LL_INTERRUPT_PRIORITY HAL_LL_INTERRUPT_PRIORITY_HIGH
#define HAL_LL_IRQ_TX1IE_BIT 4
#define HAL_LL_IRQ_RC1IE_BIT 5
#define HAL_LL_IRQ_TX2IE_BIT 20
#define HAL_LL_IRQ_RC2IE_BIT 21
// EOF IRQ defines

#endif // _MCU_DEFINITIONS_H_
// ------------------------------------------------------------------------- END
