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
 * @brief MCU specific pin and module definitions for STM32C031F6_TSSOP20.
 */

#ifndef _MCU_DEFINITIONS_H_
#define _MCU_DEFINITIONS_H_

#ifdef __cplusplus
extern "C"{
#endif

// ADC
#define ADC1_PA0_CH0
#define ADC1_PA11_CH11
#define ADC1_PA12_CH12
#define ADC1_PA13_CH13
#define ADC1_PA14_CH14
#define ADC1_PA1_CH1
#define ADC1_PA2_CH2
#define ADC1_PA3_CH3
#define ADC1_PA4_CH4
#define ADC1_PA5_CH5
#define ADC1_PA6_CH6
#define ADC1_PA7_CH7
#define ADC1_PA8_CH8

#define ADC_MODULE_1 (1)

#define ADC_MODULE_COUNT (1)
// EOF ADC

// CAN

// EOF CAN

// DMA
#define DMA_NUM_OF_CHANNELS (54)
#define DMA_NUM_OF_CHANNELS_FAMILY (54)
#define DMA_NUM_OF_MODULES (1)
#define DMA_NUM_OF_STREAMS (3)
#define DMA_NUM_OF_STREAMS_FAMILY (3)
// EOF DMA

// I2C
#define I2C1_SCL_PA9_AF6
#define I2C1_SCL_PB6_AF6
#define I2C1_SCL_PB7_AF14
#define I2C1_SDA_PA10_AF6
#define I2C1_SDA_PB7_AF6
#define I2C1_SDA_PC14_AF14

#define I2C_MODULE_1 (1)

#define I2C_MODULE_COUNT (1)
// EOF I2C

// U(S)ART
#define USART1_RX_PA10_AF1
#define USART1_RX_PA1_AF4
#define USART1_RX_PA8_AF14
#define USART1_RX_PB7_AF0
#define USART1_TX_PA0_AF4
#define USART1_TX_PA9_AF1
#define USART1_TX_PB6_AF0
#define USART1_TX_PC14_AF0
#define USART2_RX_PA13_AF4
#define USART2_RX_PA14_AF9
#define USART2_RX_PA3_AF1
#define USART2_RX_PA5_AF1
#define USART2_TX_PA14_AF1
#define USART2_TX_PA2_AF1
#define USART2_TX_PA4_AF1
#define USART2_TX_PA8_AF1

#define UART_MODULE_1 (1)
#define UART_MODULE_2 (2)

#define UART_MODULE_COUNT (2)
// EOF U(S)ART

// SPI
#define SPI1_MISO_PA11_AF0
#define SPI1_MISO_PA6_AF0
#define SPI1_MISO_PB6_AF9
#define SPI1_MOSI_PA12_AF0
#define SPI1_MOSI_PA2_AF0
#define SPI1_MOSI_PA7_AF0
#define SPI1_MOSI_PB6_AF8
#define SPI1_SCK_PA1_AF0
#define SPI1_SCK_PA5_AF0
#define SPI1_SCK_PB6_AF10

#define SPI_MODULE_1 (1)

#define SPI_MODULE_COUNT (1)
// EOF SPI

// TIM
#define TIM14_CH1_PA4_AF4
#define TIM14_CH1_PA7_AF4
#define TIM14_CH1_PA8_AF13
#define TIM16_BKIN_PB6_AF14
#define TIM16_CH1N_PA2_AF2
#define TIM16_CH1N_PB6_AF2
#define TIM16_CH1_PA0_AF2
#define TIM16_CH1_PA6_AF5
#define TIM16_CH1_PB7_AF10
#define TIM17_BKIN_PA10_AF5
#define TIM17_BKIN_PB6_AF15
#define TIM17_CH1N_PA4_AF5
#define TIM17_CH1N_PB7_AF2
#define TIM17_CH1_PA1_AF2
#define TIM17_CH1_PA7_AF5
#define TIM17_CH1_PC14_AF10
#define TIM1_BKIN2_PA11_AF5
#define TIM1_BKIN2_PC14_AF2
#define TIM1_BKIN_PA6_AF2
#define TIM1_CH1N_PA3_AF2
#define TIM1_CH1N_PA7_AF2
#define TIM1_CH1_PA0_AF5
#define TIM1_CH1_PA14_AF10
#define TIM1_CH1_PA5_AF5
#define TIM1_CH1_PA8_AF2
#define TIM1_CH2N_PA4_AF2
#define TIM1_CH2N_PA8_AF9
#define TIM1_CH2_PA1_AF5
#define TIM1_CH2_PA9_AF2
#define TIM1_CH2_PB6_AF11
#define TIM1_CH3N_PA5_AF2
#define TIM1_CH3N_PA8_AF10
#define TIM1_CH3_PA10_AF2
#define TIM1_CH3_PA2_AF5
#define TIM1_CH3_PB6_AF1
#define TIM1_CH4_PA11_AF2
#define TIM1_CH4_PA3_AF5
#define TIM1_CH4_PB7_AF1
#define TIM1_CH4_PF2_AF1
#define TIM1_ETR_PA12_AF2
#define TIM1_ETR_PC14_AF1
#define TIM1_ETR_PC15_AF2
#define TIM3_CH1_PA6_AF1
#define TIM3_CH1_PB6_AF12
#define TIM3_CH1_PB7_AF11
#define TIM3_CH2_PA7_AF1
#define TIM3_CH2_PB6_AF13
#define TIM3_CH2_PC14_AF11
#define TIM3_CH3_PA8_AF11
#define TIM3_CH3_PB6_AF3
#define TIM3_CH3_PC15_AF3
#define TIM3_CH4_PA8_AF12
#define TIM3_CH4_PB7_AF3
#define TIM3_ETR_PA13_AF3
#define TIM3_ETR_PA2_AF3
#define TIM3_ETR_PA9_AF3

#define TIM_MODULE_1 (1)
#define TIM_MODULE_3 (2)
#define TIM_MODULE_14 (3)
#define TIM_MODULE_16 (4)
#define TIM_MODULE_17 (5)

#define TIM_MODULE_COUNT (5)

#define TIM1_BUS (1)
#define TIM3_BUS (1)
#define TIM14_BUS (1)
#define TIM16_BUS (1)
#define TIM17_BUS (1)
// EOF TIM

// GPIO
#define __PA0_CN
#define __PA1_CN
#define __PA10_CN
#define __PA11_CN
#define __PA12_CN
#define __PA13_CN
#define __PA14_CN
#define __PA2_CN
#define __PA3_CN
#define __PA4_CN
#define __PA5_CN
#define __PA6_CN
#define __PA7_CN
#define __PA8_CN
#define __PA9_CN
#define __PB6_CN
#define __PB7_CN
#define __PC14_CN
#define __PC15_CN
#define __PF2_CN

#define __PORT_A_CN
#define __PORT_B_CN
#define __PORT_C_CN
#define __PORT_F_CN

#define PORT_COUNT (4)
#define PORT_SIZE (16)
// EOF GPIO

// IVT_TABLE
#define UART1_IVT (27)
#define UART1_NVIC (43)
#define UART2_IVT (28)
#define UART2_NVIC (44)
// EOF IVT_TABLE

#ifdef __cplusplus
}
#endif

#endif // _MCU_DEFINITIONS_H_
// ------------------------------------------------------------------------- END
