/****************************************************************************
**
** Copyright (C) 2021 MikroElektronika d.o.o.
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

//ADC
#define ADC1_PA0_CH0
#define ADC1_PA1_CH1
#define ADC1_PA12_CH16
#define ADC1_PA13_CH17
#define ADC1_PA14_CH18
#define ADC1_PA2_CH2
#define ADC1_PB0_CH8
#define ADC1_PB1_CH9
#define ADC1_PB7_CH11

#define ADC_MODULE_1 1

#define ADC_MODULE_COUNT 1
//EOF ADC

//I2C
#define I2C1_SCL_PB6_AF6
#define I2C1_SCL_PB8_AF6
#define I2C1_SDA_PB7_AF6
#define I2C1_SDA_PB9_AF6

#define I2C_MODULE_1 1

#define I2C_MODULE_COUNT 1
//EOF I2C

//UART

//EOF UART

//USART
#define UART1_RX_PB7_AF0
#define UART1_TX_PB6_AF0

#define UART_MODULE_1 1

#define UART_MODULE_COUNT 1
//EOF USART

//SPI
#define SPI1_MOSI_PA2_AF0
#define SPI1_MOSI_PB5_AF0
#define SPI1_SCK_PA1_AF0
#define SPI2_MISO_PB6_AF4
#define SPI2_MOSI_PB7_AF1
#define SPI2_SCK_PA0_AF0
#define SPI2_SCK_PB8_AF1

#define SPI_MODULE_1 1
#define SPI_MODULE_2 2

#define SPI_MODULE_COUNT 2
//EOF SPI

//TIM
#define TIM1_BK2_PC14_AF2
#define TIM1_CH1_PA8_AF2
#define TIM1_CH2N_PB0_AF2
#define TIM1_CH3_PB6_AF1
#define TIM1_CH3N_PB1_AF2
#define TIM14_CH1_PB1_AF0
#define TIM16_BK_PB5_AF2
#define TIM16_CH1_PB8_AF2
#define TIM16_CH1N_PB6_AF2
#define TIM17_CH1_PB9_AF2
#define TIM17_CH1N_PB7_AF2
#define TIM3_CH2_PB5_AF1
#define TIM3_CH3_PB0_AF1
#define TIM3_CH4_PB1_AF1

#define TIM1_BUS 2
#define TIM14_BUS 2
#define TIM16_BUS 2
#define TIM17_BUS 2
#define TIM3_BUS 1

#define TIM_MODULE_1 1
#define TIM_MODULE_14 3
#define TIM_MODULE_16 4
#define TIM_MODULE_17 5
#define TIM_MODULE_3 2

#define TIM_MODULE_COUNT 5
//EOF TIM

//GPIO
#define __PC14_CN
#define __PB9_CN
#define __PB8_CN
#define __PB7_CN
#define __PB6_CN
#define __PB5_CN
#define __PB1_CN
#define __PB0_CN
#define __PA9_CN
#define __PA8_CN
#define __PA2_CN
#define __PA15_CN
#define __PA14_CN
#define __PA13_CN
#define __PA12_CN
#define __PA11_CN
#define __PA10_CN
#define __PA1_CN
#define __PA0_CN

#define __PORT_A_CN
#define __PORT_B_CN
#define __PORT_C_CN

#define PORT_SIZE (16)
#define PORT_COUNT (3)
//EOF GPIO

//IVT_TABLE
#define UART1_NVIC  43
#define UART2_NVIC  44
//EOF IVT_TABLE


#endif // _MCU_DEFINITIONS_H_
// ------------------------------------------------------------------------- END
