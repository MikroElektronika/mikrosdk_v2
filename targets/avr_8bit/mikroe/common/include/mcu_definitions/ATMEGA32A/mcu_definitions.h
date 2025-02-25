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

// ADC
#define ADC0_PA0_CH0
#define ADC0_PA1_CH1
#define ADC0_PA2_CH2
#define ADC0_PA3_CH3
#define ADC0_PA4_CH4
#define ADC0_PA5_CH5
#define ADC0_PA6_CH6
#define ADC0_PA7_CH7

#define ADC_MODULE_0 (1)

#define HAL_LL_AN_COUNT (8)
#define ADC_MODULE_COUNT (1)

// ADC Register addresses and offsets
#define HAL_LL_ADC0_ADCL_REG_ADDRESS (0x24)
#define HAL_LL_ADC0_ADCH_REG_ADDRESS (0x25)
#define HAL_LL_ADC0_ADC_REG_ADDRESS (0x24)
#define HAL_LL_ADC0_BASE_ADDRESS (HAL_LL_ADC0_ADC_REG_ADDRESS)
#define HAL_LL_ADC0_ADCSRA_REG_ADDRESS (0x26)
#define HAL_LL_ADC0_ADMUX_REG_ADDRESS (0x27)
#define HAL_LL_ADC0_ACSR_REG_ADDRESS (0x28)
#define HAL_LL_ADC0_ADCSRB_REG_ADDRESS (HAL_LL_ADC0_ACSR_REG_ADDRESS)
// EOF ADC Register addresses and offsets
// EOF ADC

// I2C
#define TWI0_SCL_PC0
#define TWI0_SDA_PC1

#define TWI_MODULE_0 (1)
#define I2C_MODULE_0 (TWI_MODULE_0)
#define TWI_MODULE_COUNT (1)
#define I2C_MODULE_COUNT (TWI_MODULE_COUNT)

// I2C Register addresses and offsets
#define HAL_LL_TWI_TWBR_REG_ADDRESS (0x20)
#define HAL_LL_I2C0_BASE_ADDRESS (HAL_LL_TWI_TWBR_REG_ADDRESS)
#define HAL_LL_TWI_TWSR_REG_ADDRESS (0x21)
#define HAL_LL_TWI_TWAR_REG_ADDRESS (0x22)
#define HAL_LL_TWI_TWDR_REG_ADDRESS (0x23)
#define HAL_LL_TWI_TWCR_REG_ADDRESS (0x56)
// EOF I2C Register addresses and offsets
// EOF I2C

// U(S)ART
#define USART_RXD_PD0
#define USART_TXD_PD1

#define UART_MODULE_0 (1)
#define UART_MODULE_COUNT (1)

// U(S)ART Register addresses and offsets
#define HAL_LL_USART0_UBRR0L_REG_ADDRESS (0x29)
#define HAL_LL_USART0_UCSR0B_REG_ADDRESS (0x2A)
#define HAL_LL_USART0_UCSR0A_REG_ADDRESS (0x2B)
#define HAL_LL_USART0_UDR0_REG_ADDRESS (0x2C)
// Shared register addresses
#define REGISTERS_WITH_SHARED_IO_LOCATION
#define HAL_LL_USART0_UCSR0C_REG_ADDRESS (0x40)
#define HAL_LL_USART0_UBRR0H_REG_ADDRESS (0x40)
// EOF U(S)ART Register addresses and offsets
// EOF U(S)ART

// SPI
#define SPI0_MISO_PB6
#define SPI0_MOSI_PB5
#define SPI0_SCK_PB7
#define SPI0_SS_PB4

#define SPI_MODULE_0 (1)
#define SPI_MODULE_COUNT (1)

// SPI Register addresses and offsets
#define HAL_LL_SPI0_SPCR_REG_ADDRESS (0x2D)
#define HAL_LL_SPI0_SPSR_REG_ADDRESS (0x2E)
#define HAL_LL_SPI0_SPDR_REG_ADDRESS (0x2F)
// EOF SPI Register addresses and offsets
// EOF SPI

// TIM
#define TIM0_PB3_CH_NONE
#define TIM1_PD4_CH_B
#define TIM1_PD5_CH_A
#define TIM2_PD7_CH_NONE

#define TIM_MODULE_0 (1)
#define TIM_MODULE_1 (2)
#define TIM_MODULE_2 (3)
#define TIM_MODULE_COUNT (3)

// TIM Register addresses and offsets
#define HAL_LL_TIM2_ASSR_REG_ADDRESS (0x42)
#define HAL_LL_TIM2_OCR2A_REG_ADDRESS (0x43)
#define HAL_LL_TIM2_TCNT2_REG_ADDRESS (0x44)
#define HAL_LL_TIM2_TCCR2A_REG_ADDRESS (0x45)
#define HAL_LL_TIM1_ICR1_REG_ADDRESS (0x46)
#define HAL_LL_TIM1_OCR1BH_REG_ADDRESS (0x49)
#define HAL_LL_TIM1_OCR1BL_REG_ADDRESS (0x48)
#define HAL_LL_TIM1_OCR1AH_REG_ADDRESS (0x4b)
#define HAL_LL_TIM1_OCR1AL_REG_ADDRESS (0x4A)
#define HAL_LL_TIM1_TCNT1H_REG_ADDRESS (0x4d)
#define HAL_LL_TIM1_TCNT1L_REG_ADDRESS (0x4C)
#define HAL_LL_TIM1_TCCR1B_REG_ADDRESS (0x4E)
#define HAL_LL_TIM1_TCCR1A_REG_ADDRESS (0x4F)
#define HAL_LL_TIM0_TCNT0_REG_ADDRESS (0x52)
#define HAL_LL_TIM0_TCCR0A_REG_ADDRESS (0x53)
#define HAL_LL_TIM0_OCR0A_REG_ADDRESS (0x5C)
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

#define __PORT_A_CN
#define __PORT_B_CN
#define __PORT_C_CN
#define __PORT_D_CN

#define PORT_SIZE  (8)
#define PORT_COUNT (4)

// GPIO Register addresses and offsets
#define PIND_REG_ADDRESS (0x30)
#define DDRD_REG_ADDRESS (0x31)
#define PORTD_REG_ADDRESS (0x32)
#define PINC_REG_ADDRESS (0x33)
#define DDRC_REG_ADDRESS (0x34)
#define PORTC_REG_ADDRESS (0x35)
#define PINB_REG_ADDRESS (0x36)
#define DDRB_REG_ADDRESS (0x37)
#define PORTB_REG_ADDRESS (0x38)
#define PINA_REG_ADDRESS (0x39)
#define DDRA_REG_ADDRESS (0x3A)
#define PORTA_REG_ADDRESS (0x3B)
// REMAP Register addresses
#define HAL_LL_MODULE_REMAP (false)
// EOF GPIO Register addresses and offsets
// EOF GPIO

// POWER REDUCTION REGISTER
#define HAL_LL_POWER_REDUCTION (false)
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
