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
#include "can_definitions.h"

//DMA
#define DMA_NUM_OF_MODULES 1
#define DMA_NUM_OF_STREAMS 32
#define DMA_NUM_OF_STREAMS_FAMILY 32
#define DMA_NUM_OF_CHANNELS 5
#define DMA_NUM_OF_CHANNELS_FAMILY 5
//EOF DMA

//ADC
#define ADC0_PE3_AIN0
#define ADC1_PE3_AIN0
#define ADC0_PE2_AIN1
#define ADC1_PE2_AIN1
#define ADC0_PE1_AIN2
#define ADC1_PE1_AIN2
#define ADC0_PE0_AIN3
#define ADC1_PE0_AIN3
#define ADC0_PD3_AIN4
#define ADC1_PD3_AIN4
#define ADC0_PD2_AIN5
#define ADC1_PD2_AIN5
#define ADC0_PD1_AIN6
#define ADC1_PD1_AIN6
#define ADC0_PD0_AIN7
#define ADC1_PD0_AIN7
#define ADC0_PE5_AIN8
#define ADC1_PE5_AIN8
#define ADC0_PE4_AIN9
#define ADC1_PE4_AIN9
#define ADC0_PB4_AIN10
#define ADC1_PB4_AIN10
#define ADC0_PB5_AIN11
#define ADC1_PB5_AIN11

#define ADC_MODULE_0 1
#define ADC_MODULE_1 2

#define ADC_MODULE_COUNT 2
//EOF ADC

//I2C
#define I2C0_SCL_PB2_AF3
#define I2C0_SDA_PB3_AF3
#define I2C1_SCL_PA6_AF3
#define I2C1_SCL_PG4_AF3
#define I2C1_SDA_PA7_AF3
#define I2C1_SDA_PG5_AF3
#define I2C2_SCL_PE4_AF3
#define I2C2_SDA_PE5_AF3
#define I2C3_SCL_PD0_AF3
#define I2C3_SCL_PG0_AF3
#define I2C3_SDA_PD1_AF3
#define I2C3_SDA_PG1_AF3
#define I2C4_SCL_PG2_AF3
#define I2C4_SDA_PG3_AF3
#define I2C5_SCL_PB6_AF3
#define I2C5_SDA_PB7_AF3

#define I2C_MODULE_0 1
#define I2C_MODULE_1 2
#define I2C_MODULE_2 3
#define I2C_MODULE_3 4
#define I2C_MODULE_4 5
#define I2C_MODULE_5 6

#define I2C_MODULE_COUNT 6
//EOF I2C

//UART
#define UART0_RX_PA0_AF1
#define UART0_TX_PA1_AF1
#define UART1_RX_PB0_AF1
#define UART1_RX_PC4_AF2
#define UART1_TX_PB1_AF1
#define UART1_TX_PC5_AF2
#define UART2_RX_PD6_AF1
#define UART2_RX_PG4_AF1
#define UART2_TX_PD7_AF1
#define UART2_TX_PG5_AF1
#define UART3_RX_PC6_AF1
#define UART3_TX_PC7_AF1
#define UART4_RX_PC4_AF1
#define UART4_TX_PC5_AF1
#define UART5_RX_PE4_AF1
#define UART5_TX_PE5_AF1
#define UART6_RX_PD4_AF1
#define UART6_TX_PD5_AF1
#define UART7_RX_PE0_AF1
#define UART7_TX_PE1_AF1

#define UART_MODULE_0 1
#define UART_MODULE_1 2
#define UART_MODULE_2 3
#define UART_MODULE_3 4
#define UART_MODULE_4 5
#define UART_MODULE_5 6
#define UART_MODULE_6 7
#define UART_MODULE_7 8

#define UART_MODULE_COUNT 8
//EOF UART

//SPI
#define SPI0_MISO_PA4_AF2
#define SPI0_MOSI_PA5_AF2
#define SPI0_SCK_PA2_AF2
#define SPI1_MISO_PD2_AF2
#define SPI1_MISO_PF0_AF2
#define SPI1_MOSI_PD3_AF2
#define SPI1_MOSI_PF1_AF2
#define SPI1_SCK_PD0_AF2
#define SPI1_SCK_PF2_AF2
#define SPI2_MISO_PB6_AF2
#define SPI2_MOSI_PB7_AF2
#define SPI2_SCK_PB4_AF2
#define SPI3_MISO_PD2_AF1
#define SPI3_MOSI_PD3_AF1
#define SPI3_SCK_PD0_AF1

#define SPI_MODULE_0 1
#define SPI_MODULE_1 2
#define SPI_MODULE_2 3
#define SPI_MODULE_3 4

#define SPI_MODULE_COUNT 4
//EOF SPI

//TIM
#define TIM0_CCP0_PB6_AF7
#define TIM0_CCP0_PF0_AF7
#define TIM0_CCP1_PB7_AF7
#define TIM0_CCP1_PF1_AF7
#define TIM1_CCP0_PB4_AF7
#define TIM1_CCP0_PF2_AF7
#define TIM1_CCP1_PB5_AF7
#define TIM1_CCP1_PF3_AF7
#define TIM2_CCP0_PB0_AF7
#define TIM2_CCP0_PF4_AF7
#define TIM2_CCP1_PB1_AF7
#define TIM3_CCP0_PB2_AF7
#define TIM3_CCP1_PB3_AF7
#define TIM4_CCP0_PC0_AF7
#define TIM4_CCP0_PG0_AF7
#define TIM4_CCP1_PC1_AF7
#define TIM4_CCP1_PG1_AF7
#define TIM5_CCP0_PC2_AF7
#define TIM5_CCP0_PG2_AF7
#define TIM5_CCP1_PC3_AF7
#define TIM5_CCP1_PG3_AF7

#define TIM_MODULE_0 1
#define TIM_MODULE_1 2
#define TIM_MODULE_2 3
#define TIM_MODULE_3 4
#define TIM_MODULE_4 5
#define TIM_MODULE_5 6

#define TIM_MODULE_COUNT 6
//EOF TIM

//GPIO
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
#define __PF0_CN
#define __PF1_CN
#define __PF2_CN
#define __PF3_CN
#define __PF4_CN
#define __PG0_CN
#define __PG1_CN
#define __PG2_CN
#define __PG3_CN
#define __PG4_CN
#define __PG5_CN

#define __PORT_A_CN
#define __PORT_B_CN
#define __PORT_C_CN
#define __PORT_D_CN
#define __PORT_E_CN
#define __PORT_F_CN
#define __PORT_G_CN

#define PORT_SIZE (8)
#define PORT_COUNT (7)
//EOF GPIO

//IVT_TABLE
#define UART0_NVIC 21
#define UART1_NVIC 22
#define UART2_NVIC 49
#define UART3_NVIC 75
#define UART4_NVIC 76
#define UART5_NVIC 77
#define UART6_NVIC 78
#define UART7_NVIC 79
//EOF IVT_TABLE

#endif // _MCU_DEFINITIONS_H_
// ------------------------------------------------------------------------- END
