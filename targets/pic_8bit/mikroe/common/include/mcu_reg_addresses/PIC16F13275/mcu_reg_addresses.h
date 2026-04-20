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

// PIC18F24J11 REGISTER DEFINITIONS
// EOF REGISTER DEFINITIONS
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
#define PORTA_BASE_ADDRESS      0xF80
#define PORTB_BASE_ADDRESS      0xF81
#define PORTC_BASE_ADDRESS      0xF82
#define PORTD_BASE_ADDRESS      0xF83
#define PORTE_BASE_ADDRESS      0xF84

#define TRISA_BASE_ADDRESS      0xF92
#define TRISB_BASE_ADDRESS      0xF93
#define TRISC_BASE_ADDRESS      0xF94
#define TRISD_BASE_ADDRESS      0xF95
#define TRISE_BASE_ADDRESS      0xF96

#define LATA_BASE_ADDRESS       0xF89
#define LATB_BASE_ADDRESS       0xF8A
#define LATC_BASE_ADDRESS       0xF8B
#define LATD_BASE_ADDRESS       0xF8C
#define LATE_BASE_ADDRESS       0xF8D

#define ANSELA_BASE_ADDRESS     0xF38
#define ANSELB_BASE_ADDRESS     0xF39
#define ANSELC_BASE_ADDRESS     0xF3A
#define ANSELD_BASE_ADDRESS     0xF3B
#define ANSELE_BASE_ADDRESS     0xF3C

// ============================================================
// REGISTRI KOJI SE POMINJU U GREŠKAMA
// ============================================================

// ----- WDTCON registar (Watchdog Timer Control) -----
#define HAL_LL_WDTCON_ADDRESS           0xFFF  // Adresa WDTCON registra
#define HAL_LL_WDTCON_ADSHR_BIT         7      // Bit za ADSHR (proveri u datasheet-u)

// ----- ADC registri -----
#define HAL_LL_ADCON0_ADDRESS           0xFC0  // Adresa ADCON0 registra
#define HAL_LL_ADCON1_ADDRESS           0xFC1  // Adresa ADCON1 registra
#define HAL_LL_ADCON2_ADDRESS           0xFC2  // Adresa ADCON2 registra
#define HAL_LL_ADRESL_ADDRESS           0xFC3  // Adresa ADRESL registra
#define HAL_LL_ADRESH_ADDRESS           0xFC4  // Adresa ADRESH registra

// ----- ADC bitovi -----
#define HAL_LL_ADC_TURN_ON_BIT           0      // Bit za uključivanje ADC (ADON)
#define HAL_LL_ADC_START_CONVERSION_BIT  1      // Bit za start konverzije (GO/DONE)
#define HAL_LL_ADC_CLEAR_CHANNEL_BITS    0x3C   // Maska za brisanje kanala (proveri)
#define HAL_LL_ADC_CONVERSION_CLOCK      0x30   // Vrednost za takt konverzije (proveri)
#define HAL_LL_ADC_RESULT_FORMAT_BIT     7      // Bit za format rezultata (ADFM)
#define HAL_LL_ADC_VREF_MASK             0xC0   // Maska za referentni napon (proveri)

// ----- I2C specifično -----
#define HAL_LL_SSPxADD_ADDRESS           0xFC8  // Adresa SSPxADD registra (proveri)
#define HAL_LL_SSPxCON1_ADDRESS          0xFC5  // Adresa SSPxCON1 registra (proveri)
#define HAL_LL_SSPxSTAT_ADDRESS          0xFC6  // Adresa SSPxSTAT registra (proveri)
#define HAL_LL_SSPxBUF_ADDRESS           0xFC9  // Adresa SSPxBUF registra (proveri)

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
#define HAL_LL_TMR0_ADDRESS                0xFD6  // Adresa TMR0 registra (proveri)
#define HAL_LL_TMR1L_ADDRESS               0xFCE  // Adresa TMR1L registra (proveri)
#define HAL_LL_TMR1H_ADDRESS               0xFCF  // Adresa TMR1H registra (proveri)
#define HAL_LL_TMR2_ADDRESS                0xFCC  // Adresa TMR2 registra (proveri)
#define HAL_LL_PR2_ADDRESS                  0xFCB  // Adresa PR2 registra (proveri)

// ----- PPS (Peripheral Pin Select) -----
#define HAL_LL_PPS_LOCK_ADDRESS            0xF0F  // Adresa PPSLOCK registra (proveri)
#define HAL_LL_PPS_UNLOCK_SEQUENCE         0x55AA // Sekvenca za otključavanje PPS

// ----- BROJ BITOVA -----
#define HAL_LL_ODCON_BIT_COUNT             8
#define HAL_LL_SLRCON_BIT_COUNT            8
#define HAL_LL_INLVL_BIT_COUNT              8
#define HAL_LL_WPU_BIT_COUNT                8

#endif

#endif // _MCU_REG_ADDRESSES_H_
// ------------------------------------------------------------------------- END
