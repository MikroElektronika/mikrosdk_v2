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
 * @file  mcu_definitions.h
 * @brief MCU specific pin and module definitions.
 */

#ifndef _MCU_DEFINITIONS_H_
#define _MCU_DEFINITIONS_H_

#include "mcu_reg_addresses.h"
#include "can_definitions.h"

//ADC
#define HAL_LL_RA0_AN0_ANSELA_BIT 0
#define HAL_LL_RA0_AN0_ANSELA 0
#define HAL_LL_RA1_AN1_ANSELA_BIT 1
#define HAL_LL_RA1_AN1_ANSELA 1
#define HAL_LL_RA2_AN2_ANSELA_BIT 2
#define HAL_LL_RA2_AN2_ANSELA 2
#define HAL_LL_RA3_AN3_ANSELA_BIT 3
#define HAL_LL_RA3_AN3_ANSELA 3
#define HAL_LL_RA5_AN4_ANSELA_BIT 5
#define HAL_LL_RA5_AN4_ANSELA 4
#define HAL_LL_RB0_AN12_ANSELB_BIT 0
#define HAL_LL_RB0_AN12_ANSELB 12
#define HAL_LL_RB1_AN10_ANSELB_BIT 1
#define HAL_LL_RB1_AN10_ANSELB 10
#define HAL_LL_RB2_AN8_ANSELB_BIT 2
#define HAL_LL_RB2_AN8_ANSELB 8
#define HAL_LL_RB3_AN9_ANSELB_BIT 3
#define HAL_LL_RB3_AN9_ANSELB 9
#define HAL_LL_RB4_AN11_ANSELB_BIT 4
#define HAL_LL_RB4_AN11_ANSELB 11
#define HAL_LL_RB5_AN13_ANSELB_BIT 5
#define HAL_LL_RB5_AN13_ANSELB 13
#define HAL_LL_RC2_AN14_ANSELC_BIT 2
#define HAL_LL_RC2_AN14_ANSELC 14
#define HAL_LL_RC6_AN18_ANSELC_BIT 6
#define HAL_LL_RC6_AN18_ANSELC 18
#define HAL_LL_RC7_AN19_ANSELC_BIT 7
#define HAL_LL_RC7_AN19_ANSELC 19
#define HAL_LL_RD0_AN20_ANSELD_BIT 0
#define HAL_LL_RD0_AN20_ANSELD 20
#define HAL_LL_RD1_AN21_ANSELD_BIT 1
#define HAL_LL_RD1_AN21_ANSELD 21
#define HAL_LL_RD2_AN22_ANSELD_BIT 2
#define HAL_LL_RD2_AN22_ANSELD 22
#define HAL_LL_RD3_AN23_ANSELD_BIT 3
#define HAL_LL_RD3_AN23_ANSELD 23
#define HAL_LL_RD4_AN24_ANSELD_BIT 4
#define HAL_LL_RD4_AN24_ANSELD 24
#define HAL_LL_RD5_AN25_ANSELD_BIT 5
#define HAL_LL_RD5_AN25_ANSELD 25
#define HAL_LL_RD6_AN26_ANSELD_BIT 6
#define HAL_LL_RD6_AN26_ANSELD 26
#define HAL_LL_RD7_AN27_ANSELD_BIT 7
#define HAL_LL_RD7_AN27_ANSELD 27
#define HAL_LL_RE0_AN5_ANSELE_BIT 0
#define HAL_LL_RE0_AN5_ANSELE 5
#define HAL_LL_RE1_AN6_ANSELE_BIT 1
#define HAL_LL_RE1_AN6_ANSELE 6
#define HAL_LL_RE2_AN7_ANSELE_BIT 2
#define HAL_LL_RE2_AN7_ANSELE 7


#define HAL_LL_VREFCON0_ADDRESS 0xF7DU
#define HAL_LL_ANSELE_ADDRESS 0xF5FU
#define HAL_LL_ANSELD_ADDRESS 0xF5EU
#define HAL_LL_ANSELC_ADDRESS 0xF5DU
#define HAL_LL_ANSELB_ADDRESS 0xF5CU
#define HAL_LL_ANSELA_ADDRESS 0xF5BU
#define HAL_LL_ADRESL_ADDRESS 0xFC3U
#define HAL_LL_ADCON2_ADDRESS 0xFC0U
#define HAL_LL_ADCON1_ADDRESS 0xFC1U
#define HAL_LL_ADCON0_ADDRESS 0xFC2U

#define HAL_LL_AN_COUNT 25
#define ADC_MODULE 1
#define ADC_MODULE_COUNT 1
//EOF ADC

//I2C
#define I2C_SCL_RB1
#define I2C_SDA_RB0


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
#define SPI_MISO_RB0
#define SPI_MOSI_RB3
#define SPI_MOSI_RC7
#define SPI_SCK_RB1


#define SPI_MODULE 1

#define SPI_MODULE_COUNT 1

#define HAL_LL_SPI_PPS_ENABLED false
//EOF SPI

//PWM
#define PWM_CCP1_RC2
#define PWM_CCP2_RB3
#define PWM_CCP2_RC1

#define EPWM_CCP1_RC2_P1A
#define EPWM_CCP1_RD5_P1B
#define EPWM_CCP1_RD6_P1C
#define EPWM_CCP1_RD7_P1D

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
#define __RE3_CN

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
#define HAL_LL_PMD0_ADDRESS 0xF7EU
#define HAL_LL_PMD1_ADDRESS 0xF7FU
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
#define HAL_LL_PMD_I2C_ADDRESS HAL_LL_PMD1_ADDRESS
#define HAL_LL_PMD_SPI_ADDRESS HAL_LL_PMD1_ADDRESS
#define HAL_LL_PMD_UART1_ADDRESS HAL_LL_PMD0_ADDRESS
#define HAL_LL_SSP_MODULE_BIT 6
#define HAL_LL_UART1_MODULE_BIT 6
#define HAL_LL_UART1_RCIF_BIT 5
#define HAL_LL_UART1_TXIF_BIT 4
// EOF PMD & PIR Register defines

// TMR Register addresses
#define HAL_LL_PSTR1CON_ADDRESS 0xFB9U
#define HAL_LL_CCP1CON_ADDRESS 0xFBDU
#define HAL_LL_CCP2CON_ADDRESS 0xF97U
#define HAL_LL_CCPTMRS_ADDRESS 0xF59U
#define HAL_LL_CCPTMRS_CCP_MODULE_1 HAL_LL_CCPTMRS_ADDRESS
#define HAL_LL_CCP_MODULE_1_TIM2_ENABLE_BIT 0x00
#define HAL_LL_CCPTMRS_CCP_MODULE_2 HAL_LL_CCPTMRS_ADDRESS
#define HAL_LL_CCP_MODULE_2_TIM2_ENABLE_BIT 0x00
#define HAL_LL_PMD_CCP_MODULE_1 HAL_LL_PMD1_ADDRESS
#define HAL_LL_PMD_CCP_MODULE_1_ENABLE_BIT 0
#define HAL_LL_PMD_CCP_MODULE_2 HAL_LL_PMD1_ADDRESS
#define HAL_LL_PMD_CCP_MODULE_2_ENABLE_BIT 1
#define HAL_LL_PR2_ADDRESS 0xFBBU
#define HAL_LL_T0CON_ADDRESS 0xFD5U
#define HAL_LL_T1CON_ADDRESS 0xFCDU
#define HAL_LL_T2CON_ADDRESS 0xFBAU
#define HAL_LL_T3CON_ADDRESS 0xFB1U
#define HAL_LL_CCPR1L_ADDRESS 0xFBEU
#define HAL_LL_CCPR2L_ADDRESS 0xF90U
// EOF TMR Register addresses

// ADC Register addresses and bit defines
#define HAL_LL_ADC_PMD_ADDRESS HAL_LL_PMD1_ADDRESS
#define HAL_LL_ADCMD_BIT 2
// EOF ADC Register addresses and bit defines

// SLRCON Register addresses and bit defines
#define HAL_LL_SLRCON_ADDRESS 0xF7AU
#define HAL_LL_SLRCON_PA0_BIT 0
#define HAL_LL_SLRCON_PA1_BIT 0
#define HAL_LL_SLRCON_PA2_BIT 0
#define HAL_LL_SLRCON_PA3_BIT 0
#define HAL_LL_SLRCON_PA4_BIT 0
#define HAL_LL_SLRCON_PA5_BIT 0
#define HAL_LL_SLRCON_PA6_BIT 0
#define HAL_LL_SLRCON_PA7_BIT 0
#define HAL_LL_SLRCON_PB0_BIT 1
#define HAL_LL_SLRCON_PB1_BIT 1
#define HAL_LL_SLRCON_PB2_BIT 1
#define HAL_LL_SLRCON_PB3_BIT 1
#define HAL_LL_SLRCON_PB4_BIT 1
#define HAL_LL_SLRCON_PB5_BIT 1
#define HAL_LL_SLRCON_PB6_BIT 1
#define HAL_LL_SLRCON_PB7_BIT 1
#define HAL_LL_SLRCON_PC0_BIT 2
#define HAL_LL_SLRCON_PC1_BIT 2
#define HAL_LL_SLRCON_PC2_BIT 2
#define HAL_LL_SLRCON_PC4_BIT 2
#define HAL_LL_SLRCON_PC5_BIT 2
#define HAL_LL_SLRCON_PC6_BIT 2
#define HAL_LL_SLRCON_PC7_BIT 2
#define HAL_LL_SLRCON_PD0_BIT 3
#define HAL_LL_SLRCON_PD1_BIT 3
#define HAL_LL_SLRCON_PD2_BIT 3
#define HAL_LL_SLRCON_PD3_BIT 3
#define HAL_LL_SLRCON_PD4_BIT 3
#define HAL_LL_SLRCON_PD5_BIT 3
#define HAL_LL_SLRCON_PD6_BIT 3
#define HAL_LL_SLRCON_PD7_BIT 3
#define HAL_LL_SLRCON_PE0_BIT 4
#define HAL_LL_SLRCON_PE1_BIT 4
#define HAL_LL_SLRCON_PE2_BIT 4
#define HAL_LL_SLRCON_PE3_BIT 4
#define HAL_LL_SLRCONA_ADDRESS HAL_LL_SLRCON_ADDRESS
#define HAL_LL_SLRCONB_ADDRESS HAL_LL_SLRCON_ADDRESS
#define HAL_LL_SLRCONC_ADDRESS HAL_LL_SLRCON_ADDRESS
#define HAL_LL_SLRCOND_ADDRESS HAL_LL_SLRCON_ADDRESS
#define HAL_LL_SLRCONE_ADDRESS HAL_LL_SLRCON_ADDRESS
#define HAL_LL_SLRCON_BIT_COUNT 35

// EOF SLRCON Register addresses and bit defines

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
#define HAL_LL_OSCCON2_ADDRESS 0xFD2U
// EOF Unlock Register addresses

#define HAL_LL_ODCON_BIT_COUNT 0

// IRQ defines
#define HAL_LL_INTERRUPT_PRIORITY_LOW 0x0018
#define HAL_LL_INTERRUPT_PRIORITY_HIGH 0x0008
#define HAL_LL_INTERRUPT_PRIORITY HAL_LL_INTERRUPT_PRIORITY_HIGH
#define HAL_LL_IRQ_TXIE_BIT 4
#define HAL_LL_IRQ_RCIE_BIT 5
// EOF IRQ defines

#endif // _MCU_DEFINITIONS_H_
// ------------------------------------------------------------------------- END
