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
 * @brief MCU specific pin and module definitions for PIC32MX220F032D.
 */

#ifndef _MCU_DEFINITIONS_H_
#define _MCU_DEFINITIONS_H_

#include "mcu_reg_addresses.h"
#include "can_definitions.h"

//DMA
#define DMA_NUM_OF_MODULES 1
#define DMA_NUM_OF_STREAMS 4
#define DMA_NUM_OF_STREAMS_FAMILY 4
#define DMA_NUM_OF_CHANNELS 255
#define DMA_NUM_OF_CHANNELS_FAMILY 255
//EOF DMA

//ADC
#define HAL_LL_RA0_AN0 0
#define HAL_LL_RA1_AN1 1
#define HAL_LL_RB0_AN2 2
#define HAL_LL_RB1_AN3 3
#define HAL_LL_RB13_AN11 11
#define HAL_LL_RB14_AN10 10
#define HAL_LL_RB15_AN9 9
#define HAL_LL_RB2_AN4 4
#define HAL_LL_RB3_AN5 5
#define HAL_LL_RC0_AN6 6
#define HAL_LL_RC1_AN7 7
#define HAL_LL_RC2_AN8 8
#define HAL_LL_RC3_AN12 12

#define ADC_MODULE 1
#define ADC_MODULE_COUNT 1
#define HAL_LL_AN_COUNT 13

#define HAL_LL_ANSELC_ADDRESS 0xBF886200UL
#define HAL_LL_ANSELB_ADDRESS 0xBF886100UL
#define HAL_LL_ANSELA_ADDRESS 0xBF886000UL
#define HAL_LL_ADC1BUFF_ADDRESS 0xBF809160UL
#define HAL_LL_ADC1BUFE_ADDRESS 0xBF809150UL
#define HAL_LL_ADC1BUFD_ADDRESS 0xBF809140UL
#define HAL_LL_ADC1BUFC_ADDRESS 0xBF809130UL
#define HAL_LL_ADC1BUFB_ADDRESS 0xBF809120UL
#define HAL_LL_ADC1BUFA_ADDRESS 0xBF809110UL
#define HAL_LL_ADC1BUF9_ADDRESS 0xBF809100UL
#define HAL_LL_ADC1BUF8_ADDRESS 0xBF8090F0UL
#define HAL_LL_ADC1BUF7_ADDRESS 0xBF8090E0UL
#define HAL_LL_ADC1BUF6_ADDRESS 0xBF8090D0UL
#define HAL_LL_ADC1BUF5_ADDRESS 0xBF8090C0UL
#define HAL_LL_ADC1BUF4_ADDRESS 0xBF8090B0UL
#define HAL_LL_ADC1BUF3_ADDRESS 0xBF8090A0UL
#define HAL_LL_ADC1BUF2_ADDRESS 0xBF809090UL
#define HAL_LL_ADC1BUF1_ADDRESS 0xBF809080UL
#define HAL_LL_ADC1BUF0_ADDRESS 0xBF809070UL
#define HAL_LL_AD1CSSL_ADDRESS 0xBF809050UL
#define HAL_LL_AD1CON3_ADDRESS 0xBF809020UL
#define HAL_LL_AD1CON2_ADDRESS 0xBF809010UL
#define HAL_LL_AD1CON1_ADDRESS 0xBF809000UL
#define HAL_LL_AD1CHS_ADDRESS 0xBF809040UL

#define HAL_LL_RA0_AN0_ADDRESS HAL_LL_ANSELA_ADDRESS
#define HAL_LL_RA1_AN1_ADDRESS HAL_LL_ANSELA_ADDRESS
#define HAL_LL_RB0_AN2_ADDRESS HAL_LL_ANSELB_ADDRESS
#define HAL_LL_RB1_AN3_ADDRESS HAL_LL_ANSELB_ADDRESS
#define HAL_LL_RB13_AN11_ADDRESS HAL_LL_ANSELB_ADDRESS
#define HAL_LL_RB14_AN10_ADDRESS HAL_LL_ANSELB_ADDRESS
#define HAL_LL_RB15_AN9_ADDRESS HAL_LL_ANSELB_ADDRESS
#define HAL_LL_RB2_AN4_ADDRESS HAL_LL_ANSELB_ADDRESS
#define HAL_LL_RB3_AN5_ADDRESS HAL_LL_ANSELB_ADDRESS
#define HAL_LL_RC0_AN6_ADDRESS HAL_LL_ANSELC_ADDRESS
#define HAL_LL_RC1_AN7_ADDRESS HAL_LL_ANSELC_ADDRESS
#define HAL_LL_RC2_AN8_ADDRESS HAL_LL_ANSELC_ADDRESS
#define HAL_LL_RC3_AN12_ADDRESS HAL_LL_ANSELC_ADDRESS
//EOF ADC

//I2C
#define I2C1_SCL_RB8
#define I2C1_SDA_RB9
#define I2C2_SCL_RB3
#define I2C2_SDA_RB2

#define I2C_MODULE_1 1
#define I2C_MODULE_2 2

#define I2C_MODULE_COUNT 2

#define HAL_LL_I2C_PPS_ENABLED false
//EOF I2C

//UART
#define UART1_RX_RA2
#define UART1_RX_RA4
#define UART1_RX_RB13
#define UART1_RX_RB2
#define UART1_RX_RC6
#define UART1_RX_RC1
#define UART1_RX_RC3

#define UART2_RX_RA1
#define UART2_RX_RB5
#define UART2_RX_RB1
#define UART2_RX_RB11
#define UART2_RX_RB8
#define UART2_RX_RA8
#define UART2_RX_RC8
#define UART2_RX_RA9

//Output
#define UART1_TX_RA0
#define UART1_TX_RB3
#define UART1_TX_RB4
#define UART1_TX_RB15
#define UART1_TX_RB7
#define UART1_TX_RC7
#define UART1_TX_RC0
#define UART1_TX_RC5

#define UART2_TX_RA3
#define UART2_TX_RB14
#define UART2_TX_RB0
#define UART2_TX_RB10
#define UART2_TX_RB9
#define UART2_TX_RC9
#define UART2_TX_RC2
#define UART2_TX_RC4

#define UART_MODULE_1 1
#define UART_MODULE_2 2

#define UART_MODULE_COUNT 2

#define HAL_LL_UART_PPS_ENABLED true
//EOF UART

//SPI
#define SPI1_SCK_RB14
#define SPI2_SCK_RB15

#define SPI1_MISO_RA1
#define SPI1_MISO_RB5
#define SPI1_MISO_RB1
#define SPI1_MISO_RB11
#define SPI1_MISO_RB8
#define SPI1_MISO_RA8
#define SPI1_MISO_RC8
#define SPI1_MISO_RA9

#define SPI2_MISO_RA2
#define SPI2_MISO_RA4
#define SPI2_MISO_RB13
#define SPI2_MISO_RB2
#define SPI2_MISO_RC6
#define SPI2_MISO_RC1
#define SPI2_MISO_RC3

//Output
#define SPI1_MOSI_RA1
#define SPI1_MOSI_RB5
#define SPI1_MOSI_RB1
#define SPI1_MOSI_RB11
#define SPI1_MOSI_RB8
#define SPI1_MOSI_RA8
#define SPI1_MOSI_RC8
#define SPI1_MOSI_RA9

#define SPI1_MOSI_RA2
#define SPI1_MOSI_RA4
#define SPI1_MOSI_RB13
#define SPI1_MOSI_RB2
#define SPI1_MOSI_RC6
#define SPI1_MOSI_RC1
#define SPI1_MOSI_RC3

#define SPI2_MOSI_RA2
#define SPI2_MOSI_RA4
#define SPI2_MOSI_RB13
#define SPI2_MOSI_RB2
#define SPI2_MOSI_RC6
#define SPI2_MOSI_RC1
#define SPI2_MOSI_RC3

#define SPI2_MOSI_RA1
#define SPI2_MOSI_RB5
#define SPI2_MOSI_RB1
#define SPI2_MOSI_RB11
#define SPI2_MOSI_RB8
#define SPI2_MOSI_RA8
#define SPI2_MOSI_RC8
#define SPI2_MOSI_RA9

#define SPI_MODULE_1 1
#define SPI_MODULE_2 2

#define SPI_MODULE_COUNT 2

#define HAL_LL_SPI_PPS_ENABLED true
//EOF SPI

//PWM
#define PWM1_OC_RA0
#define PWM1_OC_RB3
#define PWM1_OC_RB4
#define PWM1_OC_RB15
#define PWM1_OC_RB7
#define PWM1_OC_RC7
#define PWM1_OC_RC0
#define PWM1_OC_RC5

#define PWM2_OC_RA1
#define PWM2_OC_RB5
#define PWM2_OC_RB1
#define PWM2_OC_RB11
#define PWM2_OC_RB8
#define PWM2_OC_RA8
#define PWM2_OC_RC8
#define PWM2_OC_RA9

#define PWM3_OC_RA3
#define PWM3_OC_RB14
#define PWM3_OC_RB0
#define PWM3_OC_RB10
#define PWM3_OC_RB9
#define PWM3_OC_RC9
#define PWM3_OC_RC2
#define PWM3_OC_RC4

#define PWM4_OC_RA2
#define PWM4_OC_RA4
#define PWM4_OC_RB13
#define PWM4_OC_RB2
#define PWM4_OC_RC6
#define PWM4_OC_RC1
#define PWM4_OC_RC3

#define PWM5_OC_RA2
#define PWM5_OC_RA4
#define PWM5_OC_RB13
#define PWM5_OC_RB2
#define PWM5_OC_RC6
#define PWM5_OC_RC1
#define PWM5_OC_RC3

#define OCR_MODULE_1 1
#define OCR_MODULE_2 2
#define OCR_MODULE_3 3
#define OCR_MODULE_4 4
#define OCR_MODULE_5 5

#define OCR_MODULE_COUNT 5

#define TIM_MODULE_COUNT OCR_MODULE_COUNT

#define HAL_LL_TIM_PPS_ENABLED true
//EOF PWM

//IO
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
#define PORT_COUNT (3)
#define PORT_SIZE (16)
//EOF IO

// GPIO Register addresses and offsets
#define LATA_BASE_ADDRESS 0xBF886030UL
#define LATB_BASE_ADDRESS 0xBF886130UL
#define LATC_BASE_ADDRESS 0xBF886230UL
#define PORTA_BASE_ADDRESS 0xBF886020UL
#define PORTB_BASE_ADDRESS 0xBF886120UL
#define PORTC_BASE_ADDRESS 0xBF886220UL
#define TRISA_BASE_ADDRESS 0xBF886010UL
#define TRISB_BASE_ADDRESS 0xBF886110UL
#define TRISC_BASE_ADDRESS 0xBF886210UL
// EOF GPIO Register addresses and offsets

// PMD Register addresses
#define HAL_LL_I2C1MD_ENABLE_BIT 16
#define HAL_LL_I2C2MD_ENABLE_BIT 17
#define HAL_LL_OC1MD_ENABLE_BIT 16
#define HAL_LL_OC2MD_ENABLE_BIT 17
#define HAL_LL_OC3MD_ENABLE_BIT 18
#define HAL_LL_OC4MD_ENABLE_BIT 19
#define HAL_LL_OC5MD_ENABLE_BIT 20
#define HAL_LL_PMD1_ADDRESS 0xBF80F240UL
#define HAL_LL_PMD2_ADDRESS 0xBF80F250UL
#define HAL_LL_PMD3_ADDRESS 0xBF80F260UL
#define HAL_LL_PMD4_ADDRESS 0xBF80F270UL
#define HAL_LL_PMD5_ADDRESS 0xBF80F280UL
#define HAL_LL_PMD6_ADDRESS 0xBF80F290UL
#define HAL_LL_SPI1MD_ENABLE_BIT 8
#define HAL_LL_SPI2MD_ENABLE_BIT 9
#define HAL_LL_U1MD_ENABLE_BIT 0
#define HAL_LL_U2MD_ENABLE_BIT 1
// EOF PMD Register addresses

// I2C and SPI Register addresses
#define HAL_LL_I2C1ADD_ADDRESS 0xBF805020UL
#define HAL_LL_I2C1BRG_ADDRESS 0xBF805040UL
#define HAL_LL_I2C1CON_ADDRESS 0xBF805000UL
#define HAL_LL_I2C1MSK_ADDRESS 0xBF805030UL
#define HAL_LL_I2C1RCV_ADDRESS 0xBF805060UL
#define HAL_LL_I2C1STAT_ADDRESS 0xBF805010UL
#define HAL_LL_I2C1TRN_ADDRESS 0xBF805050UL
#define HAL_LL_I2C2ADD_ADDRESS 0xBF805120UL
#define HAL_LL_I2C2BRG_ADDRESS 0xBF805140UL
#define HAL_LL_I2C2CON_ADDRESS 0xBF805100UL
#define HAL_LL_I2C2MSK_ADDRESS 0xBF805130UL
#define HAL_LL_I2C2RCV_ADDRESS 0xBF805160UL
#define HAL_LL_I2C2STAT_ADDRESS 0xBF805110UL
#define HAL_LL_I2C2TRN_ADDRESS 0xBF805150UL
#define HAL_LL_SPI1BRG_ADDRESS 0xBF805830UL
#define HAL_LL_SPI1BUF_ADDRESS 0xBF805820UL
#define HAL_LL_SPI1CON_ADDRESS 0xBF805800UL
#define HAL_LL_SPI1CON2_ADDRESS 0xBF805840UL
#define HAL_LL_SPI1STAT_ADDRESS 0xBF805810UL
#define HAL_LL_SPI2BRG_ADDRESS 0xBF805A30UL
#define HAL_LL_SPI2BUF_ADDRESS 0xBF805A20UL
#define HAL_LL_SPI2CON_ADDRESS 0xBF805A00UL
#define HAL_LL_SPI2CON2_ADDRESS 0xBF805A40UL
#define HAL_LL_SPI2STAT_ADDRESS 0xBF805A10UL
// EOF I2C and SPI Register addresses

// TMR Register addresses
#define HAL_LL_CM1CON_ADDRESS 0xBF80A000UL
#define HAL_LL_CM2CON_ADDRESS 0xBF80A010UL
#define HAL_LL_CM3CON_ADDRESS 0xBF80A020UL
#define HAL_LL_CMSTAT_ADDRESS 0xBF80A060UL
#define HAL_LL_OC1CON_ADDRESS 0xBF803000UL
#define HAL_LL_OC1R_ADDRESS 0xBF803010UL
#define HAL_LL_OC1RS_ADDRESS 0xBF803020UL
#define HAL_LL_OC2CON_ADDRESS 0xBF803200UL
#define HAL_LL_OC2R_ADDRESS 0xBF803210UL
#define HAL_LL_OC2RS_ADDRESS 0xBF803220UL
#define HAL_LL_OC3CON_ADDRESS 0xBF803400UL
#define HAL_LL_OC3R_ADDRESS 0xBF803410UL
#define HAL_LL_OC3RS_ADDRESS 0xBF803420UL
#define HAL_LL_OC4CON_ADDRESS 0xBF803600UL
#define HAL_LL_OC4R_ADDRESS 0xBF803610UL
#define HAL_LL_OC4RS_ADDRESS 0xBF803620UL
#define HAL_LL_OC5CON_ADDRESS 0xBF803800UL
#define HAL_LL_OC5R_ADDRESS 0xBF803810UL
#define HAL_LL_OC5RS_ADDRESS 0xBF803820UL
#define HAL_LL_PR1_ADDRESS 0xBF800620UL
#define HAL_LL_PR2_ADDRESS 0xBF800820UL
#define HAL_LL_PR3_ADDRESS 0xBF800A20UL
#define HAL_LL_PR4_ADDRESS 0xBF800C20UL
#define HAL_LL_PR5_ADDRESS 0xBF800E20UL
#define HAL_LL_T1CON_ADDRESS 0xBF800600UL
#define HAL_LL_T2CON_ADDRESS 0xBF800800UL
#define HAL_LL_T3CON_ADDRESS 0xBF800A00UL
#define HAL_LL_T4CON_ADDRESS 0xBF800C00UL
#define HAL_LL_T5CON_ADDRESS 0xBF800E00UL
#define HAL_LL_TMR1_ADDRESS 0xBF800610UL
#define HAL_LL_TMR2_ADDRESS 0xBF800810UL
#define HAL_LL_TMR3_ADDRESS 0xBF800A10UL
#define HAL_LL_TMR4_ADDRESS 0xBF800C10UL
#define HAL_LL_TMR5_ADDRESS 0xBF800E10UL
// EOF TMR Register addresses

// UART Register addresses
#define HAL_LL_U1BRG_ADDRESS 0xBF806040UL
#define HAL_LL_U1MODE_ADDRESS 0xBF806000UL
#define HAL_LL_U1RXREG_ADDRESS 0xBF806030UL
#define HAL_LL_U1STA_ADDRESS 0xBF806010UL
#define HAL_LL_U1TXREG_ADDRESS 0xBF806020UL
#define HAL_LL_U2BRG_ADDRESS 0xBF806240UL
#define HAL_LL_U2MODE_ADDRESS 0xBF806200UL
#define HAL_LL_U2RXREG_ADDRESS 0xBF806230UL
#define HAL_LL_U2STA_ADDRESS 0xBF806210UL
#define HAL_LL_U2TXREG_ADDRESS 0xBF806220UL
// EOF UART Register addresses

// IVT Register addresses
#define HAL_LL_UART_1 32
#define HAL_LL_UART_2 37
#define HAL_LL_UART1_ERR 39
#define HAL_LL_UART1_RX 40
#define HAL_LL_UART1_TX 41
#define HAL_LL_UART2_ERR 53
#define HAL_LL_UART2_RX 54
#define HAL_LL_UART2_TX 55
#define HAL_LL_IEC0_ADDRESS 0xBF881060UL
#define HAL_LL_IEC1_ADDRESS 0xBF881070UL
#define HAL_LL_IFS0_ADDRESS 0xBF881030UL
#define HAL_LL_IFS1_ADDRESS 0xBF881040UL
#define HAL_LL_INTSTAT_ADDRESS 0xBF881010UL
#define HAL_LL_IPC0_ADDRESS 0xBF881090UL
#define HAL_LL_IPC1_ADDRESS 0xBF8810A0UL
#define HAL_LL_IPC10_ADDRESS 0xBF881130UL
#define HAL_LL_IPC2_ADDRESS 0xBF8810B0UL
#define HAL_LL_IPC3_ADDRESS 0xBF8810C0UL
#define HAL_LL_IPC4_ADDRESS 0xBF8810D0UL
#define HAL_LL_IPC5_ADDRESS 0xBF8810E0UL
#define HAL_LL_IPC6_ADDRESS 0xBF8810F0UL
#define HAL_LL_IPC7_ADDRESS 0xBF881100UL
#define HAL_LL_IPC8_ADDRESS 0xBF881110UL
#define HAL_LL_IPC9_ADDRESS 0xBF881120UL
#define HAL_LL_IPTMR_ADDRESS 0xBF881020UL
// EOF IVT Register addresses

// PPS Register addresses
#define HAL_LL_RPA0R_ADDRESS 0xBF80FB00UL
#define HAL_LL_RPA1R_ADDRESS 0xBF80FB04UL
#define HAL_LL_RPA2R_ADDRESS 0xBF80FB08UL
#define HAL_LL_RPA3R_ADDRESS 0xBF80FB0CUL
#define HAL_LL_RPA4R_ADDRESS 0xBF80FB10UL
#define HAL_LL_RPA8R_ADDRESS 0xBF80FB20UL
#define HAL_LL_RPA9R_ADDRESS 0xBF80FB24UL
#define HAL_LL_RPB0R_ADDRESS 0xBF80FB2CUL
#define HAL_LL_RPB10R_ADDRESS 0xBF80FB54UL
#define HAL_LL_RPB11R_ADDRESS 0xBF80FB58UL
#define HAL_LL_RPB13R_ADDRESS 0xBF80FB60UL
#define HAL_LL_RPB14R_ADDRESS 0xBF80FB64UL
#define HAL_LL_RPB15R_ADDRESS 0xBF80FB68UL
#define HAL_LL_RPB1R_ADDRESS 0xBF80FB30UL
#define HAL_LL_RPB2R_ADDRESS 0xBF80FB34UL
#define HAL_LL_RPB3R_ADDRESS 0xBF80FB38UL
#define HAL_LL_RPB4R_ADDRESS 0xBF80FB3CUL
#define HAL_LL_RPB5R_ADDRESS 0xBF80FB40UL
#define HAL_LL_RPB7R_ADDRESS 0xBF80FB48UL
#define HAL_LL_RPB8R_ADDRESS 0xBF80FB4CUL
#define HAL_LL_RPB9R_ADDRESS 0xBF80FB50UL
#define HAL_LL_RPC0R_ADDRESS 0xBF80FB6CUL
#define HAL_LL_RPC1R_ADDRESS 0xBF80FB70UL
#define HAL_LL_RPC2R_ADDRESS 0xBF80FB74UL
#define HAL_LL_RPC3R_ADDRESS 0xBF80FB78UL
#define HAL_LL_RPC4R_ADDRESS 0xBF80FB7CUL
#define HAL_LL_RPC5R_ADDRESS 0xBF80FB80UL
#define HAL_LL_RPC6R_ADDRESS 0xBF80FB84UL
#define HAL_LL_RPC7R_ADDRESS 0xBF80FB88UL
#define HAL_LL_RPC8R_ADDRESS 0xBF80FB8CUL
#define HAL_LL_RPC9R_ADDRESS 0xBF80FB90UL
#define HAL_LL_SDI1R_ADDRESS 0xBF80FA84UL
#define HAL_LL_SDI2R_ADDRESS 0xBF80FA90UL
#define HAL_LL_U1RXR_ADDRESS 0xBF80FA50UL
#define HAL_LL_U2RXR_ADDRESS 0xBF80FA58UL
// EOF PPS Register addresses

// Unlock Register addresses
#define HAL_LL_OSCCON_ADDRESS 0xBF80F000UL
// EOF Unlock Register addresses

// UART Interrupt necessities
#define HAL_LL_IVT_UART_1_SHIFT 2
#define HAL_LL_IVT_UART_1 HAL_LL_UART_1
#define HAL_LL_IVT_UART_1_ADDRESS HAL_LL_IPC8_ADDRESS
#define HAL_LL_UART_1_IFS_RX_ADDRESS HAL_LL_IFS1_ADDRESS
#define HAL_LL_UART_1_IEC_RX_ADDRESS HAL_LL_IEC1_ADDRESS
#define HAL_LL_UART_1_IFS_TX_ADDRESS HAL_LL_IFS1_ADDRESS
#define HAL_LL_UART_1_IEC_TX_ADDRESS HAL_LL_IEC1_ADDRESS
#define HAL_LL_UART_1_TX_FLAG 9
#define HAL_LL_UART_1_RX_FLAG 8

#define HAL_LL_IVT_UART_2_SHIFT 10
#define HAL_LL_IVT_UART_2 HAL_LL_UART_2
#define HAL_LL_IVT_UART_2_ADDRESS HAL_LL_IPC9_ADDRESS
#define HAL_LL_UART_2_IFS_RX_ADDRESS HAL_LL_IFS1_ADDRESS
#define HAL_LL_UART_2_IEC_RX_ADDRESS HAL_LL_IEC1_ADDRESS
#define HAL_LL_UART_2_IFS_TX_ADDRESS HAL_LL_IFS1_ADDRESS
#define HAL_LL_UART_2_IEC_TX_ADDRESS HAL_LL_IEC1_ADDRESS
#define HAL_LL_UART_2_TX_FLAG 23
#define HAL_LL_UART_2_RX_FLAG 22
// EOF UART Interrupt necessities

#endif // _MCU_DEFINITIONS_H_
