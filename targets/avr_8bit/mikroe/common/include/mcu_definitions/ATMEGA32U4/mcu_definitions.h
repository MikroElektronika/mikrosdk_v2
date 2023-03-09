/****************************************************************************
**
** Copyright (C) 2023 MikroElektronika d.o.o.
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

// ADC
#define ADC0_PB4_CH11
#define ADC0_PB5_CH12
#define ADC0_PB6_CH13
#define ADC0_PD4_CH8
#define ADC0_PD6_CH9
#define ADC0_PD7_CH10
#define ADC0_PF0_CH0
#define ADC0_PF1_CH1
#define ADC0_PF4_CH4
#define ADC0_PF5_CH5
#define ADC0_PF6_CH6
#define ADC0_PF7_CH7

#define ADC_MODULE_0 (1)

#define HAL_LL_AN_COUNT (12)
#define ADC_MODULE_COUNT (1)

// ADC Register addresses and offsets
#define HAL_LL_ADC0_ADCL_REG_ADDRESS (0x78)
#define HAL_LL_ADC0_ADCH_REG_ADDRESS (0x79)
#define HAL_LL_ADC0_ADC_REG_ADDRESS (0x78)
#define HAL_LL_ADC0_BASE_ADDRESS (HAL_LL_ADC0_ADC_REG_ADDRESS)
#define HAL_LL_ADC0_ADCSRA_REG_ADDRESS (0x7A)
#define HAL_LL_ADC0_ADMUX_REG_ADDRESS (0x7C)
// EOF ADC Register addresses and offsets
// EOF ADC

// I2C
#define TWI0_SCL_PD0
#define TWI0_SDA_PD1

#define TWI_MODULE_0 (1)
#define I2C_MODULE_0 (TWI_MODULE_0)
#define TWI_MODULE_COUNT (1)
#define I2C_MODULE_COUNT (TWI_MODULE_COUNT)

// I2C Register addresses and offsets
#define HAL_LL_TWI_TWBR_REG_ADDRESS (0xB8)
#define HAL_LL_I2C0_BASE_ADDRESS (HAL_LL_TWI_TWBR_REG_ADDRESS)
#define HAL_LL_TWI_TWSR_REG_ADDRESS (0xB9)
#define HAL_LL_TWI_TWAR_REG_ADDRESS (0xBA)
#define HAL_LL_TWI_TWDR_REG_ADDRESS (0xBB)
#define HAL_LL_TWI_TWCR_REG_ADDRESS (0xBC)
#define HAL_LL_TWI_TWAMR_REG_ADDRESS (0xBD)
// EOF I2C Register addresses and offsets
// EOF I2C

// U(S)ART
#define USART1_RXD_PD2
#define USART1_TXD_PD3

#define UART_MODULE_1 (1)
#define UART_MODULE_COUNT (1)

// U(S)ART Register addresses and offsets
#define HAL_LL_USART1_UCSR1A_REG_ADDRESS (0xC8)
#define HAL_LL_USART1_UCSR1B_REG_ADDRESS (0xC9)
#define HAL_LL_USART1_UCSR1C_REG_ADDRESS (0xCA)
#define HAL_LL_USART1_UCSR1D_REG_ADDRESS (0xCB)
#define HAL_LL_USART1_UBRR1L_REG_ADDRESS (0xCC)
#define HAL_LL_USART1_UBRR1H_REG_ADDRESS (0xCD)
#define HAL_LL_USART1_UBRR1_REG_ADDRESS (0xCC)
#define HAL_LL_USART1_UDR1_REG_ADDRESS (0xCE)
// EOF U(S)ART Register addresses and offsets
// EOF U(S)ART

// SPI
#define SPI0_MISO_PB3
#define SPI0_MOSI_PB2
#define SPI0_SCK_PB1
#define SPI0_SS_PB0

#define SPI_MODULE_0 (1)
#define SPI_MODULE_COUNT (1)

// SPI Register addresses and offsets
#define HAL_LL_SPI0_SPCR_REG_ADDRESS (0x4C)
#define HAL_LL_SPI0_SPSR_REG_ADDRESS (0x4D)
#define HAL_LL_SPI0_SPDR_REG_ADDRESS (0x4E)
// EOF SPI Register addresses and offsets
// EOF SPI

// TIM
#define TIM0_PB7_CH_A
#define TIM0_PD0_CH_B
#define TIM1_PB5_CH_A
#define TIM1_PB6_CH_B
#define TIM1_PB7_CH_C
#define TIM3_PC6_CH_A
#define TIM4_PB6_CH_B
#define TIM4_PC7_CH_A
#define TIM4_PD7_CH_D

#define TIM_MODULE_0 (1)
#define TIM_MODULE_1 (2)
#define TIM_MODULE_3 (3)
#define TIM_MODULE_4 (4)
#define TIM_MODULE_COUNT (4)

// TIM Register addresses and offsets
#define HAL_LL_TIM0_TIFR0_REG_ADDRESS (0x35)
#define HAL_LL_TIM1_TIFR1_REG_ADDRESS (0x36)
#define HAL_LL_TIM3_TIFR3_REG_ADDRESS (0x38)
#define HAL_LL_TIM4_TIFR4_REG_ADDRESS (0x39)
#define HAL_LL_TIM0_GTCCR_REG_ADDRESS (0x43)
#define HAL_LL_TIM0_TCCR0A_REG_ADDRESS (0x44)
#define HAL_LL_TIM0_TCCR0B_REG_ADDRESS (0x45)
#define HAL_LL_TIM0_TCNT0_REG_ADDRESS (0x46)
#define HAL_LL_TIM0_OCR0A_REG_ADDRESS (0x47)
#define HAL_LL_TIM0_OCR0B_REG_ADDRESS (0x48)
#define HAL_LL_TIM0_TIMSK0_REG_ADDRESS (0x6E)
#define HAL_LL_TIM1_TIMSK1_REG_ADDRESS (0x6F)
#define HAL_LL_TIM3_TIMSK3_REG_ADDRESS (0x71)
#define HAL_LL_TIM4_TIMSK4_REG_ADDRESS (0x72)
#define HAL_LL_TIM1_TCCR1A_REG_ADDRESS (0x80)
#define HAL_LL_TIM1_TCCR1B_REG_ADDRESS (0x81)
#define HAL_LL_TIM1_TCCR1C_REG_ADDRESS (0x82)
#define HAL_LL_TIM1_TCNT1H_REG_ADDRESS (0x85)
#define HAL_LL_TIM1_TCNT1L_REG_ADDRESS (0x84)
#define HAL_LL_TIM1_ICR1_REG_ADDRESS (0x86)
#define HAL_LL_TIM1_OCR1AH_REG_ADDRESS (0x89)
#define HAL_LL_TIM1_OCR1AL_REG_ADDRESS (0x88)
#define HAL_LL_TIM1_OCR1BH_REG_ADDRESS (0x8b)
#define HAL_LL_TIM1_OCR1BL_REG_ADDRESS (0x8A)
#define HAL_LL_TIM1_OCR1CH_REG_ADDRESS (0x8d)
#define HAL_LL_TIM1_OCR1CL_REG_ADDRESS (0x8C)
#define HAL_LL_TIM3_TCCR3A_REG_ADDRESS (0x90)
#define HAL_LL_TIM3_TCCR3B_REG_ADDRESS (0x91)
#define HAL_LL_TIM3_TCCR3C_REG_ADDRESS (0x92)
#define HAL_LL_TIM3_TCNT3H_REG_ADDRESS (0x95)
#define HAL_LL_TIM3_TCNT3L_REG_ADDRESS (0x94)
#define HAL_LL_TIM3_ICR3_REG_ADDRESS (0x96)
#define HAL_LL_TIM3_OCR3AH_REG_ADDRESS (0x99)
#define HAL_LL_TIM3_OCR3AL_REG_ADDRESS (0x98)
#define HAL_LL_TIM3_OCR3BH_REG_ADDRESS (0x9b)
#define HAL_LL_TIM3_OCR3BL_REG_ADDRESS (0x9A)
#define HAL_LL_TIM3_OCR3CH_REG_ADDRESS (0x9d)
#define HAL_LL_TIM3_OCR3CL_REG_ADDRESS (0x9C)
#define HAL_LL_TIM4_TCNT4H_REG_ADDRESS (0xbf)
#define HAL_LL_TIM4_TCNT4L_REG_ADDRESS (0xBE)
#define HAL_LL_TIM4_TC4H_REG_ADDRESS (0xBF)
#define HAL_LL_TIM4_TCCR4A_REG_ADDRESS (0xC0)
#define HAL_LL_TIM4_TCCR4B_REG_ADDRESS (0xC1)
#define HAL_LL_TIM4_TCCR4C_REG_ADDRESS (0xC2)
#define HAL_LL_TIM4_TCCR4D_REG_ADDRESS (0xC3)
#define HAL_LL_TIM4_TCCR4E_REG_ADDRESS (0xC4)
#define HAL_LL_TIM4_OCR4AH_REG_ADDRESS (0xd0)
#define HAL_LL_TIM4_OCR4AL_REG_ADDRESS (0xCF)
#define HAL_LL_TIM4_OCR4BH_REG_ADDRESS (0xd1)
#define HAL_LL_TIM4_OCR4BL_REG_ADDRESS (0xD0)
#define HAL_LL_TIM4_OCR4CH_REG_ADDRESS (0xd2)
#define HAL_LL_TIM4_OCR4CL_REG_ADDRESS (0xD1)
#define HAL_LL_TIM4_OCR4D_REG_ADDRESS (0xD2)
#define HAL_LL_TIM4_DT4_REG_ADDRESS (0xD4)
// EOF TIM Register addresses and offsets
// EOF TIM

// GPIO
#define __PB0_CN
#define __PB1_CN
#define __PB2_CN
#define __PB3_CN
#define __PB4_CN
#define __PB5_CN
#define __PB6_CN
#define __PB7_CN
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
#define __PE2_CN
#define __PE6_CN
#define __PF0_CN
#define __PF1_CN
#define __PF4_CN
#define __PF5_CN
#define __PF6_CN
#define __PF7_CN

#define __PORT_B_CN
#define __PORT_C_CN
#define __PORT_D_CN
#define __PORT_E_CN
#define __PORT_F_CN

#define PORT_SIZE  (8)
#define PORT_COUNT (5)

// GPIO Register addresses and offsets
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
// REMAP Register addresses
#define HAL_LL_MODULE_REMAP (false)
// EOF GPIO Register addresses and offsets
// EOF GPIO

// POWER REDUCTION REGISTER
#define HAL_LL_PRR0_REG_ADDRESS (0x64)
#define HAL_LL_PRR1_REG_ADDRESS (0x65)
#define HAL_LL_POWER_REDUCTION (true)
// EOF POWER REDUCTION REGISTER

// IVT
#define HAL_LL_USART1_RX_IVT (25)
#define HAL_LL_USART1_UDRE_IVT (26)
#define HAL_LL_USART1_TX_IVT (27)
// IVT ADDRESSES
#define HAL_LL_USART1_RX_IVT_ADDRESS (0x32)
#define HAL_LL_USART1_UDRE_IVT_ADDRESS (0x34)
#define HAL_LL_USART1_TX_IVT_ADDRESS (0x36)
// EOF IVT

#endif // _MCU_DEFINITIONS_H_
// ------------------------------------------------------------------------- END
