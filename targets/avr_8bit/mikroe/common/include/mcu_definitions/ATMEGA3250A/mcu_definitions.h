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

// ADC
#define ADC0_PF0_CH0
#define ADC0_PF1_CH1
#define ADC0_PF2_CH2
#define ADC0_PF3_CH3
#define ADC0_PF4_CH4
#define ADC0_PF5_CH5
#define ADC0_PF6_CH6
#define ADC0_PF7_CH7

#define ADC_MODULE_0 (1)

#define HAL_LL_AN_COUNT (8)
#define ADC_MODULE_COUNT (1)

// ADC Register addresses and offsets
#define HAL_LL_ADC0_ADMUX_REG_ADDRESS (0x7C)
#define HAL_LL_ADC0_ADCSRA_REG_ADDRESS (0x7A)
#define HAL_LL_ADC0_ADCSRB_REG_ADDRESS (0x7B)
#define HAL_LL_ADC0_ADC_REG_ADDRESS (0x78)
#define HAL_LL_ADC0_ADCL_REG_ADDRESS (0x78)
#define HAL_LL_ADC0_ADCH_REG_ADDRESS (0x79)
#define HAL_LL_ADC0_BASE_ADDRESS (HAL_LL_ADC0_ADCL_REG_ADDRESS)
// EOF ADC Register addresses and offsets
// EOF ADC

// I2C
// ATmega3250A does not have hardware I2C/TWI module
// Number of modules equals number of available ports
#define TWI_MODULE_HW (false)
#define TWI_MODULE_COUNT (9)
#define I2C_MODULE_COUNT (TWI_MODULE_COUNT)
// EOF I2C

// U(S)ART
#define USART0_RXD_PE0
#define USART0_TXD_PE1

#define UART_MODULE_0 (1)
#define UART_MODULE_COUNT (1)

// U(S)ART Register addresses and offsets
#define HAL_LL_USART0_UCSR0A_REG_ADDRESS (0xC0)
#define HAL_LL_USART0_UCSR0B_REG_ADDRESS (0xC1)
#define HAL_LL_USART0_UCSR0C_REG_ADDRESS (0xC2)
#define HAL_LL_USART0_UBRR0L_REG_ADDRESS (0xC4)
#define HAL_LL_USART0_UBRR0H_REG_ADDRESS (0xC5)
#define HAL_LL_USART0_UBRR0_REG_ADDRESS (0xC4)
#define HAL_LL_USART0_UDR0_REG_ADDRESS (0xC6)
// EOF U(S)ART Register addresses and offsets
// EOF U(S)ART

// SPI
#define SPI0_SS_PB0
#define SPI0_SCK_PB1
#define SPI0_MOSI_PB2
#define SPI0_MISO_PB3

#define SPI_MODULE_0 (1)
#define SPI_MODULE_COUNT (1)

// SPI Register addresses and offsets
#define HAL_LL_SPI0_SPCR_REG_ADDRESS (0x4C)
#define HAL_LL_SPI0_SPSR_REG_ADDRESS (0x4D)
#define HAL_LL_SPI0_SPDR_REG_ADDRESS (0x4E)
// EOF SPI Register addresses and offsets
// EOF SPI

// TIM
// 8-bit Timer/Counter2
#define TIM2_PB7_CH_A
// 16-bit Timer/Counter1
#define TIM1_PB6_CH_B
// 16-bit Timer/Counter1
#define TIM1_PB5_CH_A
// 8-bit Timer/Counter0
#define TIM0_PB4_CH_A

#define TIM_MODULE_0 (1)
#define TIM_MODULE_1 (2)
#define TIM_MODULE_2 (3)

#define TIM_MODULE_COUNT (3)

// TIM Register addresses and offsets
#define HAL_LL_TIM0_TCCR0A_REG_ADDRESS (0x44)
#define HAL_LL_TIM0_TCNT0_REG_ADDRESS (0x46)
#define HAL_LL_TIM0_OCR0A_REG_ADDRESS (0x47)
#define HAL_LL_TIM1_TCCR1A_REG_ADDRESS (0x80)
#define HAL_LL_TIM1_TCCR1B_REG_ADDRESS (0x81)
#define HAL_LL_TIM1_TCCR1C_REG_ADDRESS (0x82)
#define HAL_LL_TIM1_TCNT1H_REG_ADDRESS (0x85)
#define HAL_LL_TIM1_TCNT1L_REG_ADDRESS (0x84)
#define HAL_LL_TIM1_OCR1AH_REG_ADDRESS (0x89)
#define HAL_LL_TIM1_OCR1AL_REG_ADDRESS (0x88)
#define HAL_LL_TIM1_OCR1BH_REG_ADDRESS (0x8B)
#define HAL_LL_TIM1_OCR1BL_REG_ADDRESS (0x8A)
#define HAL_LL_TIM2_TCCR2A_REG_ADDRESS (0xB0)
#define HAL_LL_TIM2_TCNT2_REG_ADDRESS (0xB2)
#define HAL_LL_TIM2_OCR2A_REG_ADDRESS (0xB3)
// EOF TIM Register addresses and offsets
// EOF TIM

// GPIO
#define __PA0_CN
#define __PA1_CN
#define __PA2_CN
#define __PA3_CN
#define __PA4_CN
#define __PA5_CN
#define __PA6_CN
#define __PA7_CN
#define __PB0_CN
#define __PB1_CN
#define __PB2_CN
#define __PB3_CN
#define __PB4_CN
#define __PB5_CN
#define __PB6_CN
#define __PB7_CN
#define __PC0_CN
#define __PC1_CN
#define __PC2_CN
#define __PC3_CN
#define __PC4_CN
#define __PC5_CN
#define __PC6_CN
#define __PC7_CN
#define __PD0_CN
#define __PD1_CN
#define __PD2_CN
#define __PD3_CN
#define __PD4_CN
#define __PD5_CN
#define __PD6_CN
#define __PD7_CN
#define __PE0_CN
#define __PE1_CN
#define __PE2_CN
#define __PE3_CN
#define __PE4_CN
#define __PE5_CN
#define __PE6_CN
#define __PE7_CN
#define __PF0_CN
#define __PF1_CN
#define __PF2_CN
#define __PF3_CN
#define __PF4_CN
#define __PF5_CN
#define __PF6_CN
#define __PF7_CN
#define __PG0_CN
#define __PG1_CN
#define __PG2_CN
#define __PG3_CN
#define __PG4_CN
#define __PG5_CN
#define __PG6_CN
#define __PG7_CN
#define __PH0_CN
#define __PH1_CN
#define __PH2_CN
#define __PH3_CN
#define __PH4_CN
#define __PH5_CN
#define __PH6_CN
#define __PH7_CN
#define __PJ0_CN
#define __PJ1_CN
#define __PJ2_CN
#define __PJ3_CN
#define __PJ4_CN
#define __PJ5_CN
#define __PJ6_CN
#define __PJ7_CN

#define __PORT_A_CN
#define __PORT_B_CN
#define __PORT_C_CN
#define __PORT_D_CN
#define __PORT_E_CN
#define __PORT_F_CN
#define __PORT_G_CN
#define __PORT_H_CN
#define __PORT_J_CN

#define PORT_SIZE  (8)
#define PORT_COUNT (9)

// GPIO Register addresses and offsets
#define PINA_REG_ADDRESS (0x20)
#define DDRA_REG_ADDRESS (0x21)
#define PORTA_REG_ADDRESS (0x22)
#define PINB_REG_ADDRESS (0x23)
#define DDRB_REG_ADDRESS (0x24)
#define PORTB_REG_ADDRESS (0x25)
#define PINC_REG_ADDRESS (0x26)
#define DDRC_REG_ADDRESS (0x27)
#define PORTC_REG_ADDRESS (0x28)
#define PIND_REG_ADDRESS (0x29)
#define DDRD_REG_ADDRESS (0x2A)
#define PORTD_REG_ADDRESS (0x2B)
#define PINE_REG_ADDRESS (0x2C)
#define DDRE_REG_ADDRESS (0x2D)
#define PORTE_REG_ADDRESS (0x2E)
#define PINF_REG_ADDRESS (0x2F)
#define DDRF_REG_ADDRESS (0x30)
#define PORTF_REG_ADDRESS (0x31)
#define PING_REG_ADDRESS (0x32)
#define DDRG_REG_ADDRESS (0x33)
#define PORTG_REG_ADDRESS (0x34)
#define PINH_REG_ADDRESS (0xD8)
#define DDRH_REG_ADDRESS (0xD9)
#define PORTH_REG_ADDRESS (0xDA)
#define PINJ_REG_ADDRESS (0xDB)
#define DDRJ_REG_ADDRESS (0xDC)
#define PORTJ_REG_ADDRESS (0xDD)
// REMAP Register addresses
#define HAL_LL_MODULE_REMAP (false)
// EOF GPIO Register addresses and offsets
// EOF GPIO

// POWER REDUCTION REGISTER
#define HAL_LL_PRR0_REG_ADDRESS (0x64)
#define HAL_LL_POWER_REDUCTION (true)
// EOF POWER REDUCTION REGISTER

// IVT
#define HAL_LL_USART0_RX_IVT (13)
#define HAL_LL_USART0_UDRE_IVT (14)
#define HAL_LL_USART0_TX_IVT (15)
// IVT ADDRESSES
#define HAL_LL_USART0_RX_IVT_ADDRESS (0x1A)
#define HAL_LL_USART0_UDRE_IVT_ADDRESS (0x1C)
#define HAL_LL_USART0_TX_IVT_ADDRESS (0x1E)
// EOF IVT

#endif // _MCU_DEFINITIONS_H_
// ------------------------------------------------------------------------- END
