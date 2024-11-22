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
 * @brief MCU specific pin and module definitions for ATSAME70N21B_LQFP100.
 */

#ifndef _MCU_DEFINITIONS_H_
#define _MCU_DEFINITIONS_H_

#ifdef __cplusplus
extern "C"{
#endif

// ADC
#define ADC0_PD30_CH0
#define ADC0_PA21_CH1
#define ADC0_PB3_CH2
#define ADC0_PB2_CH5
#define ADC0_PA17_CH6
#define ADC0_PA18_CH7
#define ADC0_PA19_CH8
#define ADC0_PA20_CH9
#define ADC0_PB0_CH10
#define ADC1_PB1_CH0

#define ADC_MODULE_0 (0)
#define ADC_MODULE_1 (1)

#define ADC_MODULE_COUNT (2)
// EOF ADC

// I2C
#define I2C0_SCL_PA4_AFA
#define I2C0_SDA_PA3_AFA
#define I2C1_SCL_PB5_AFA
#define I2C1_SDA_PB4_AFA
#define I2C2_SCL_PD28_AFC
#define I2C2_SDA_PD27_AFC

#define I2C_MODULE_0 (0)
#define I2C_MODULE_1 (1)
#define I2C_MODULE_2 (2)

#define I2C_MODULE_COUNT (3)
// EOF I2C

// TIM
#define TIM0_CH0_A_PA0_AFB
#define TIM0_CH1_A_PA15_AFB
#define TIM0_CH2_A_PA26_AFB
#define TIM0_CH0_B_PA1_AFB
#define TIM0_CH1_B_PA16_AFB
#define TIM0_CH2_B_PA27_AFB
#define TIM3_CH2_A_PD21_AFC
#define TIM3_CH2_B_PD22_AFC

#define TIM_MODULE_0 (0)
#define TIM_MODULE_3 (3)

#define TIM_CHANNEL_NUMBER (3)
#define TIM_MODULE_COUNT   (2)
// EOF TIM

// USART
#define USART0_RX_PB0_AFC
#define USART0_TX_PB1_AFC
#define USART1_RX_PA21_AFA
#define USART1_TX_PB4_AFD
#define USART2_RX_PD15_AFB
#define USART2_TX_PD16_AFB

#define USART_MODULE_0 (0)
#define USART_MODULE_1 (1)
#define USART_MODULE_2 (2)

#define USART_MODULE_COUNT (3)
// EOF USART

// UART
#define UART0_RX_PA9_AFA
#define UART0_TX_PA10_AFA
#define UART1_RX_PA5_AFC
#define UART1_TX_PA4_AFC
#define UART1_TX_PA6_AFC
#define UART1_TX_PD26_AFD
#define UART2_RX_PD25_AFC
#define UART2_TX_PD26_AFC
#define UART3_RX_PD28_AFA
#define UART3_TX_PD30_AFA
#define UART3_TX_PD31_AFB
#define UART4_RX_PD18_AFC
#define UART4_TX_PD3_AFC
#define UART4_TX_PD19_AFC

#define UART_MODULE_0 (0)
#define UART_MODULE_1 (1)
#define UART_MODULE_2 (2)
#define UART_MODULE_3 (3)
#define UART_MODULE_4 (4)

#define UART_MODULE_COUNT (5)
// EOF UART

// SPI
#define SPI0_MISO_PD20_AFB
#define SPI0_MOSI_PD21_AFB
#define SPI0_SCK_PD22_AFB

#define SPI_MODULE_0 (0)

#define SPI_MODULE_COUNT (1)
// EOF SPI

// GPIO
#define __PA0_CN
#define __PA1_CN
#define __PA2_CN
#define __PA3_CN
#define __PA4_CN
#define __PA5_CN
#define __PA6_CN
#define __PA7_CN
#define __PA8_CN
#define __PA9_CN
#define __PA10_CN
#define __PA11_CN
#define __PA12_CN
#define __PA13_CN
#define __PA14_CN
#define __PA15_CN
#define __PA16_CN
#define __PA17_CN
#define __PA18_CN
#define __PA19_CN
#define __PA20_CN
#define __PA21_CN
#define __PA22_CN
#define __PA23_CN
#define __PA24_CN
#define __PA25_CN
#define __PA26_CN
#define __PA27_CN
#define __PA28_CN
#define __PA29_CN
#define __PA30_CN
#define __PA31_CN
#define __PB0_CN
#define __PB1_CN
#define __PB2_CN
#define __PB3_CN
#define __PB4_CN
#define __PB5_CN
#define __PB6_CN
#define __PB7_CN
#define __PB8_CN
#define __PB9_CN
#define __PB12_CN
#define __PB13_CN
#define __PD0_CN
#define __PD1_CN
#define __PD2_CN
#define __PD3_CN
#define __PD4_CN
#define __PD5_CN
#define __PD6_CN
#define __PD7_CN
#define __PD8_CN
#define __PD9_CN
#define __PD10_CN
#define __PD11_CN
#define __PD12_CN
#define __PD13_CN
#define __PD14_CN
#define __PD15_CN
#define __PD16_CN
#define __PD17_CN
#define __PD18_CN
#define __PD19_CN
#define __PD20_CN
#define __PD21_CN
#define __PD22_CN
#define __PD23_CN
#define __PD24_CN
#define __PD25_CN
#define __PD26_CN
#define __PD27_CN
#define __PD28_CN
#define __PD29_CN
#define __PD30_CN
#define __PD31_CN

#define __PORT_A_CN
#define __PORT_B_CN
#define __PORT_D_CN

#define PORT_COUNT (3)
#define PORT_SIZE  (32)
// EOF GPIO

// IVT Table
#define UART0_NVIC (7)
#define UART1_NVIC (8)
#define USART0_NVIC (13)
#define USART1_NVIC (14)
#define USART2_NVIC (15)
#define UART2_NVIC (44)
#define UART3_NVIC (45)
#define UART4_NVIC (46)
// EOF IVT Table

#ifdef __cplusplus
}
#endif

#endif // _MCU_DEFINITIONS_H_
// ------------------------------------------------------------------------- END
