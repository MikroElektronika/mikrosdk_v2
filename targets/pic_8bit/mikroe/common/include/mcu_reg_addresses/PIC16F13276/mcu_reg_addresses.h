/****************************************************************************
**
** Copyright (C) 2026 MikroElektronika d.o.o.
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
* @file  mcu_reg_addresses.h
* @brief MCU specific register address definitions.
* @details PIC18F24J11 register address definitions.
*/

#ifndef _MCU_REG_ADDRESSES_H_
#define _MCU_REG_ADDRESSES_H_
#ifndef MCU_DEFINITIONS_H
#define MCU_DEFINITIONS_H

#include <xc.h>

// ============================================================
// OSNOVNE DEFINICIJE - OBAVEZNO PROVERITI U DATASHEET-U
// ============================================================

// ----- BROJ MODULA -----
#define PORT_COUNT              5   // PORTA, PORTB, PORTC, PORTD, PORTE
#define PORT_SIZE               8   // 8 pinova po portu
#define I2C_MODULE_COUNT        2   // 2 MSSP modula
#define SPI_MODULE_COUNT        2   // 2 MSSP modula
#define UART_MODULE_COUNT       2   // 2 EUSART modula
#define ADC_MODULE_COUNT        1   // 1 ADC modul
#define TIM_MODULE_COUNT        3   // Broj tajmera (proveri u datasheet-u)
#define HAL_LL_AN_COUNT         35  // Broj ADC kanala

// ----- OSNOVNE ADRESE PORTOVA -----
// Ove adrese su primer - MORAJU SE PROVERITI U DATASHEET-U!
#define PORTA_BASE_ADDRESS      0x0C
#define PORTB_BASE_ADDRESS      0x0D
#define PORTC_BASE_ADDRESS      0x0E
#define PORTD_BASE_ADDRESS      0x0F
#define PORTE_BASE_ADDRESS      0x10

#define TRISA_BASE_ADDRESS      0x12
#define TRISB_BASE_ADDRESS      0x13
#define TRISC_BASE_ADDRESS      0x14
#define TRISD_BASE_ADDRESS      0x15
#define TRISE_BASE_ADDRESS      0x16

#define LATA_BASE_ADDRESS       0x18
#define LATB_BASE_ADDRESS       0x19
#define LATC_BASE_ADDRESS       0x1A
#define LATD_BASE_ADDRESS       0x1B
#define LATE_BASE_ADDRESS       0x1C

#define ANSELA_BASE_ADDRESS     0x1E8C
#define ANSELB_BASE_ADDRESS     0x1E96
#define ANSELC_BASE_ADDRESS     0x1EA0
#define ANSELD_BASE_ADDRESS     0x1EAA
#define ANSELE_BASE_ADDRESS     0x1EB4

#define ODCONA_BASE_ADDRESS     0x1E8E
#define ODCONB_BASE_ADDRESS     0x1E98
#define ODCONC_BASE_ADDRESS     0x1EA3
#define ODCOND_BASE_ADDRESS     0x1EAD
#define ODCONE_BASE_ADDRESS     0x1EB6




// ============================================================
// REGISTRI KOJI SE POMINJU U GREŠKAMA
// ============================================================

// ----- WDTCON registar (Watchdog Timer Control) -----
#define HAL_LL_WDTCON_ADDRESS           0xFFF  // Adresa WDTCON registra
#define HAL_LL_WDTCON_ADSHR_BIT         7      // Bit za ADSHR (proveri u datasheet-u)

// ----- ADC registri -----
#define HAL_LL_ADCON0_ADDRESS           0x1D26  // Adresa ADCON0 registra
#define HAL_LL_ADCON1_ADDRESS           0x1D27  // Adresa ADCON1 registra
#define HAL_LL_ADCON2_ADDRESS           0x1D28  // Adresa ADCON2 registra
#define HAL_LL_ADCON3_ADDRESS           0x1D29  // Adresa ADCON3 registra
#define HAL_LL_ADRESL_ADDRESS           0x1D1D  // Adresa ADRESL registra
#define HAL_LL_ADRESH_ADDRESS           0x1D1E  // Adresa ADRESH registra
#define HAL_LL_ADPCH_ADDRESS            0x1D1F
#define HAL_LL_ADREF_ADDRESS            0x1D2B
#define HAL_LL_FVRCON_ADDRESS           0x020C


// ----- ADC bitovi -----
#define HAL_LL_ADC_TURN_ON_BIT           7      // Bit za uključivanje ADC (ADON)
#define HAL_LL_ADC_START_CONVERSION_BIT  0      // Bit za start konverzije (GO/DONE)
#define HAL_LL_ADC_CLEAR_CHANNEL_BITS    0x3F//0x3C   // Maska za brisanje kanala (proveri)
#define HAL_LL_ADC_CONVERSION_CLOCK      0x10//0x30   // Vrednost za takt konverzije (proveri)
#define HAL_LL_ADC_RESULT_FORMAT_BIT     7      // Bit za format rezultata (ADFM)
#define HAL_LL_ADC_VREF_MASK             0xC0   // Maska za referentni napon (proveri)
#define HAL_LL_ADREF                     0x03 // vrednost u ADREF registar (koji je karakteristican za PIC16F13)

// ---- PWM -----
/*#define HALL_LL_PWM_PWM1CON              0x0495
#define HALL_LL_PWM_PWM1ERS                0x048C
#define HALL_LL_PWM_PWM1S1P1             0x0497
#define HALL_LL_PWM_PWM2CON              0x0595
#define HALL_LL_PWM_PWM2ERS                0x058C
#define HALL_LL_PWM_PWM2S1P1             0x0597*/


// ----- I2C specifično -----
#define HAL_LL_SSP1ADD_ADDRESS           0x078D  // Adresa SSPxADD registra (proveri)
#define HAL_LL_SSP1CON1_ADDRESS          0x0790  // Adresa SSPxCON1 registra (proveri)
#define HAL_LL_SSP1CON2_ADDRESS          0x0791
#define HAL_LL_SSP1CON3_ADDRESS          0x0792
#define HAL_LL_SSP1STAT_ADDRESS          0x078F  // Adresa SSPxSTAT registra (proveri)
#define HAL_LL_SSP1BUF_ADDRESS           0x078C  // Adresa SSPxBUF registra (proveri)
//#define HAL_LL_SSP1MSK_ADDRESS           0x078E

#define HAL_LL_SSP2ADD_ADDRESS           0x0797  // Adresa SSPxADD registra (proveri)
#define HAL_LL_SSP2CON1_ADDRESS          0x079A  // Adresa SSPxCON1 registra (proveri)
#define HAL_LL_SSP2CON2_ADDRESS          0x079B
#define HAL_LL_SSP2CON3_ADDRESS          0x079C
#define HAL_LL_SSP2STAT_ADDRESS          0x0799  // Adresa SSPxSTAT registra (proveri)
#define HAL_LL_SSP2BUF_ADDRESS           0x0796  // Adresa SSPxBUF registra (proveri)
//#define HAL_LL_SSP2MSK_ADDRESS           0x0798
#define HAL_LL_PIR5_ADDRESS              0x0091

// ----- SPI specifično -----
#define HAL_LL_SSPxCON1_SPI_ADDRESS      0xFC5  // Ista kao I2C, drugačija konfiguracija
#define HAL_LL_SSPxSTAT_SPI_ADDRESS      0xFC6  // Ista kao I2C, drugačija konfiguracija

// ----- UART specifično -----
#define HAL_LL_TXSTA_ADDRESS              0xFAC  // Adresa TXSTA registra (proveri)
#define HAL_LL_RCSTA_ADDRESS              0xFAB  // Adresa RCSTA registra (proveri)
#define HAL_LL_SPBRG_ADDRESS               0xFAF  // Adresa SPBRG registra (proveri)
#define HAL_LL_SPBRGH_ADDRESS              0xFB0  // Adresa SPBRGH registra (proveri)
#define HAL_LL_TXREG_ADDRESS               0xFAD  // Adresa TXREG registra (proveri)
#define HAL_LL_RCREG_ADDRESS               0xFAE  // Adresa RCREG registra (proveri)

// ----- TIMER specifično -----
#define HAL_LL_TMR0_ADDRESS                0x019C  // Adresa TMR0 registra (proveri)
#define HAL_LL_TMR1L_ADDRESS               0x030C  // Adresa TMR1L registra (proveri)
#define HAL_LL_TMR1H_ADDRESS               0x030D  // Adresa TMR1H registra (proveri)
#define HAL_LL_TMR2_ADDRESS                0xFCC  // Adresa TMR2 registra (proveri)
#define HAL_LL_PR2_ADDRESS                  0xFCB  // Adresa PR2 registra (proveri)

// ----- PPS (Peripheral Pin Select) -----
#define HAL_LL_PPS_LOCK_ADDRESS            0x1E0C  // Adresa PPSLOCK registra (proveri)
#define HAL_LL_PPS_UNLOCK_SEQUENCE         0x55AA // Sekvenca za otključavanje PPS
#define HAL_LL_RC3_PPS                     0x1D9F
#define HAL_LL_RC4_PPS                     0x1DA0
#define HAL_LL_RB1_PPS                     0x1D95
#define HAL_LL_RB2_PPS                     0x1D96

// ----- BROJ BITOVA -----
#define HAL_LL_ODCON_BIT_COUNT             8
#define HAL_LL_SLRCON_BIT_COUNT            8
#define HAL_LL_INLVL_BIT_COUNT              8
#define HAL_LL_WPU_BIT_COUNT                8

#define HAL_LL_PMD_SPI1_ADDRESS
#define HAL_LL_PMD_SPI2_ADDRESS

#endif

#endif // _MCU_REG_ADDRESSES_H_
// ------------------------------------------------------------------------- END
