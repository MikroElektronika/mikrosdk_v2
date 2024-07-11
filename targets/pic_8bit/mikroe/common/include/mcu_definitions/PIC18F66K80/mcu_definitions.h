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
#define HAL_LL_RB0_AN10_ANCON1_BIT 2
#define HAL_LL_RB0_AN10_ANCON1 10
#define HAL_LL_RB1_AN8_ANCON1_BIT 0
#define HAL_LL_RB1_AN8_ANCON1 8
#define HAL_LL_RB4_AN9_ANCON1_BIT 1
#define HAL_LL_RB4_AN9_ANCON1 9
#define HAL_LL_RE0_AN5_ANCON0_BIT 5
#define HAL_LL_RE0_AN5_ANCON0 5
#define HAL_LL_RE1_AN6_ANCON0_BIT 6
#define HAL_LL_RE1_AN6_ANCON0 6
#define HAL_LL_RE2_AN7_ANCON0_BIT 7
#define HAL_LL_RE2_AN7_ANCON0 7


#define HAL_LL_ADRESL_ADDRESS 0xFC3U
#define HAL_LL_ANCON1_ADDRESS 0xF5CU
#define HAL_LL_ANCON0_ADDRESS 0xF5DU
#define HAL_LL_ADCON2_ADDRESS 0xFC0U
#define HAL_LL_ADCON1_ADDRESS 0xFC1U
#define HAL_LL_ADCON0_ADDRESS 0xFC2U

#define HAL_LL_AN_COUNT 11
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
#define UART1_RX_RG0
#define UART1_TX_RG3
#define UART2_RX_RE6
#define UART2_TX_RE7


#define UART_MODULE_1 1
#define UART_MODULE_2 2

#define UART_MODULE_COUNT 2

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
#define PWM_CCP1_RD4
#define PWM_CCP2_RC2
#define PWM_CCP3_RC6
#define PWM_CCP4_RC7
#define PWM_CCP5_RB5

#define EPWM_CCP1_RD4_P1A
#define EPWM_CCP1_RD5_P1B
#define EPWM_CCP1_RD6_P1C
#define EPWM_CCP1_RD7_P1D

#define CCP_MODULE_1 1
#define CCP_MODULE_2 2
#define CCP_MODULE_3 3
#define CCP_MODULE_4 4
#define CCP_MODULE_5 5

#define CCP_MODULE_COUNT 5

#define TIM_MODULE_COUNT CCP_MODULE_COUNT

#define HAL_LL_TIM_PPS_ENABLED false
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
#define __RC3_CN
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
#define __RE4_CN
#define __RE5_CN
#define __RE6_CN
#define __RE7_CN
#define __RF0_CN
#define __RF1_CN
#define __RF2_CN
#define __RF3_CN
#define __RF4_CN
#define __RF5_CN
#define __RF6_CN
#define __RF7_CN
#define __RG0_CN
#define __RG1_CN
#define __RG2_CN
#define __RG3_CN
#define __RG4_CN

#define __PORT_A_CN
#define __PORT_B_CN
#define __PORT_C_CN
#define __PORT_D_CN
#define __PORT_E_CN
#define __PORT_F_CN
#define __PORT_G_CN
#define PORT_COUNT (7)
#define PORT_SIZE (8)
//EOF IO

// GPIO Register addresses and offsets
#define LATA_BASE_ADDRESS 0xF89U
#define LATB_BASE_ADDRESS 0xF8AU
#define LATC_BASE_ADDRESS 0xF8BU
#define LATD_BASE_ADDRESS 0xF8CU
#define LATE_BASE_ADDRESS 0xF8DU
#define LATF_BASE_ADDRESS 0xF8EU
#define LATG_BASE_ADDRESS 0xF8FU
#define PORTA_BASE_ADDRESS 0xF80U
#define PORTB_BASE_ADDRESS 0xF81U
#define PORTC_BASE_ADDRESS 0xF82U
#define PORTD_BASE_ADDRESS 0xF83U
#define PORTE_BASE_ADDRESS 0xF84U
#define PORTF_BASE_ADDRESS 0xF85U
#define PORTG_BASE_ADDRESS 0xF86U
#define TRISA_BASE_ADDRESS 0xF92U
#define TRISB_BASE_ADDRESS 0xF93U
#define TRISC_BASE_ADDRESS 0xF94U
#define TRISD_BASE_ADDRESS 0xF95U
#define TRISE_BASE_ADDRESS 0xF96U
#define TRISF_BASE_ADDRESS 0xF97U
#define TRISG_BASE_ADDRESS 0xF98U
// EOF GPIO Register addresses and offsets

// PMD Register addresses
#define HAL_LL_PIE1_ADDRESS 0xF9DU
#define HAL_LL_PIE2_ADDRESS 0xFA0U
#define HAL_LL_PIE3_ADDRESS 0xFA3U
#define HAL_LL_PIE4_ADDRESS 0xFB6U
#define HAL_LL_PIE5_ADDRESS 0xF76U
#define HAL_LL_PIR1_ADDRESS 0xF9EU
#define HAL_LL_PIR2_ADDRESS 0xFA1U
#define HAL_LL_PIR3_ADDRESS 0xFA4U
#define HAL_LL_PIR4_ADDRESS 0xFB7U
#define HAL_LL_PIR5_ADDRESS 0xF77U
#define HAL_LL_PMD0_ADDRESS 0xF59U
#define HAL_LL_PMD1_ADDRESS 0xF58U
#define HAL_LL_PMD2_ADDRESS 0xF57U
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
#define HAL_LL_PIE_MODULE_UART2_ADDRESS HAL_LL_PIE3_ADDRESS
#define HAL_LL_PIR_MODULE_I2C1_ADDRESS HAL_LL_PIR1_ADDRESS
#define HAL_LL_PIR_MODULE_UART1_ADDRESS HAL_LL_PIR1_ADDRESS
#define HAL_LL_PIR_MODULE_UART2_ADDRESS HAL_LL_PIR3_ADDRESS
#define HAL_LL_PIR_SSPIF_MODULE_1_BIT 3
#define HAL_LL_PMD_I2C_ADDRESS HAL_LL_PMD0_ADDRESS
#define HAL_LL_PMD_SPI_ADDRESS HAL_LL_PMD0_ADDRESS
#define HAL_LL_PMD_UART1_ADDRESS HAL_LL_PMD0_ADDRESS
#define HAL_LL_PMD_UART2_ADDRESS HAL_LL_PMD0_ADDRESS
#define HAL_LL_SSP_MODULE_BIT 0
#define HAL_LL_UART1_MODULE_BIT 1
#define HAL_LL_UART1_RCIF_BIT 5
#define HAL_LL_UART1_TXIF_BIT 4
#define HAL_LL_UART2_MODULE_BIT 2
#define HAL_LL_UART2_RCIF_BIT 5
#define HAL_LL_UART2_TXIF_BIT 4
// EOF PMD & PIR Register defines

// TMR Register addresses
#define HAL_LL_PSTR1CON_ADDRESS 0xF9CU
#define HAL_LL_CCP1CON_ADDRESS 0xFBBU
#define HAL_LL_CCP2CON_ADDRESS 0xF50U
#define HAL_LL_CCP3CON_ADDRESS 0xF4DU
#define HAL_LL_CCP4CON_ADDRESS 0xF4AU
#define HAL_LL_CCP5CON_ADDRESS 0xF47U
#define HAL_LL_CCPTMRS_ADDRESS 0xF99U
#define HAL_LL_CCPTMRS_CCP_MODULE_1 HAL_LL_CCPTMRS_ADDRESS
#define HAL_LL_CCP_MODULE_1_TIM2_ENABLE_BIT 0x00
#define HAL_LL_CCPTMRS_CCP_MODULE_2 HAL_LL_CCPTMRS_ADDRESS
#define HAL_LL_CCP_MODULE_2_TIM2_ENABLE_BIT 0x00
#define HAL_LL_CCPTMRS_CCP_MODULE_3 HAL_LL_CCPTMRS_ADDRESS
#define HAL_LL_CCP_MODULE_3_TIM2_ENABLE_BIT 0x00
#define HAL_LL_CCPTMRS_CCP_MODULE_4 HAL_LL_CCPTMRS_ADDRESS
#define HAL_LL_CCP_MODULE_4_TIM2_ENABLE_BIT 0x00
#define HAL_LL_CCPTMRS_CCP_MODULE_5 HAL_LL_CCPTMRS_ADDRESS
#define HAL_LL_CCP_MODULE_5_TIM2_ENABLE_BIT 0x00
#define HAL_LL_PMD_CCP_MODULE_1 HAL_LL_PMD0_ADDRESS
#define HAL_LL_PMD_CCP_MODULE_1_ENABLE_BIT 3
#define HAL_LL_PMD_CCP_MODULE_2 HAL_LL_PMD0_ADDRESS
#define HAL_LL_PMD_CCP_MODULE_2_ENABLE_BIT 4
#define HAL_LL_PMD_CCP_MODULE_3 HAL_LL_PMD0_ADDRESS
#define HAL_LL_PMD_CCP_MODULE_3_ENABLE_BIT 5
#define HAL_LL_PMD_CCP_MODULE_4 HAL_LL_PMD0_ADDRESS
#define HAL_LL_PMD_CCP_MODULE_4_ENABLE_BIT 6
#define HAL_LL_PMD_CCP_MODULE_5 HAL_LL_PMD0_ADDRESS
#define HAL_LL_PMD_CCP_MODULE_5_ENABLE_BIT 7
#define HAL_LL_PR2_ADDRESS 0xFCBU
#define HAL_LL_PR4_ADDRESS 0xFA9U
#define HAL_LL_T0CON_ADDRESS 0xFD5U
#define HAL_LL_T1CON_ADDRESS 0xFCDU
#define HAL_LL_T2CON_ADDRESS 0xFCAU
#define HAL_LL_T3CON_ADDRESS 0xFB1U
#define HAL_LL_T4CON_ADDRESS 0xF88U
#define HAL_LL_CCPR1L_ADDRESS 0xFBCU
#define HAL_LL_CCPR2L_ADDRESS 0xF51U
#define HAL_LL_CCPR3L_ADDRESS 0xF4EU
#define HAL_LL_CCPR4L_ADDRESS 0xF4BU
#define HAL_LL_CCPR5L_ADDRESS 0xF48U
// EOF TMR Register addresses

// ADC Register addresses and bit defines
#define HAL_LL_ADC_PMD_ADDRESS HAL_LL_PMD1_ADDRESS
#define HAL_LL_ADCMD_BIT 5
// EOF ADC Register addresses and bit defines

// SLRCON Register addresses and bit defines
#define HAL_LL_SLRCON_ADDRESS 0xF90U
#define HAL_LL_SLRCON_PA0_BIT 0
#define HAL_LL_SLRCON_PA1_BIT 0
#define HAL_LL_SLRCON_PA2_BIT 0
#define HAL_LL_SLRCON_PA3_BIT 0
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
#define HAL_LL_SLRCON_PC3_BIT 2
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
#define HAL_LL_SLRCON_PE4_BIT 4
#define HAL_LL_SLRCON_PE5_BIT 4
#define HAL_LL_SLRCON_PE6_BIT 4
#define HAL_LL_SLRCON_PE7_BIT 4
#define HAL_LL_SLRCON_PF0_BIT 5
#define HAL_LL_SLRCON_PF1_BIT 5
#define HAL_LL_SLRCON_PF2_BIT 5
#define HAL_LL_SLRCON_PF3_BIT 5
#define HAL_LL_SLRCON_PF4_BIT 5
#define HAL_LL_SLRCON_PF5_BIT 5
#define HAL_LL_SLRCON_PF6_BIT 5
#define HAL_LL_SLRCON_PF7_BIT 5
#define HAL_LL_SLRCON_PG0_BIT 6
#define HAL_LL_SLRCON_PG1_BIT 6
#define HAL_LL_SLRCON_PG2_BIT 6
#define HAL_LL_SLRCON_PG3_BIT 6
#define HAL_LL_SLRCON_PG4_BIT 6
#define HAL_LL_SLRCONA_ADDRESS HAL_LL_SLRCON_ADDRESS
#define HAL_LL_SLRCONB_ADDRESS HAL_LL_SLRCON_ADDRESS
#define HAL_LL_SLRCONC_ADDRESS HAL_LL_SLRCON_ADDRESS
#define HAL_LL_SLRCOND_ADDRESS HAL_LL_SLRCON_ADDRESS
#define HAL_LL_SLRCONE_ADDRESS HAL_LL_SLRCON_ADDRESS
#define HAL_LL_SLRCONF_ADDRESS HAL_LL_SLRCON_ADDRESS
#define HAL_LL_SLRCONG_ADDRESS HAL_LL_SLRCON_ADDRESS
#define HAL_LL_SLRCON_BIT_COUNT 52

// EOF SLRCON Register addresses and bit defines

// UART Register addresses
#define HAL_LL_BAUDCON1_ADDRESS 0xFA7U
#define HAL_LL_BAUDCON2_ADDRESS 0xFB9U
#define HAL_LL_RCREG1_ADDRESS 0xFAEU
#define HAL_LL_RCREG2_ADDRESS 0xF7AU
#define HAL_LL_RCSTA1_ADDRESS 0xFABU
#define HAL_LL_RCSTA2_ADDRESS 0xFA6U
#define HAL_LL_SPBRG1_ADDRESS 0xFAFU
#define HAL_LL_SPBRG2_ADDRESS 0xF7BU
#define HAL_LL_SPBRGH1_ADDRESS 0xF7DU
#define HAL_LL_SPBRGH2_ADDRESS 0xF7CU
#define HAL_LL_TXREG1_ADDRESS 0xFADU
#define HAL_LL_TXREG2_ADDRESS 0xF79U
#define HAL_LL_TXSTA1_ADDRESS 0xFACU
#define HAL_LL_TXSTA2_ADDRESS 0xFBAU
// EOF UART Register addresses

// Unlock Register addresses
#define HAL_LL_EECON2_ADDRESS 0xF7EU
#define HAL_LL_OSCCON2_ADDRESS 0xFD2U
// EOF Unlock Register addresses

#define HAL_LL_ODCON_BIT_COUNT 0

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
