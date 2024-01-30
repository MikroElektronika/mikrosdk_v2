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
#include "dma_definitions.h"
#include "can_definitions.h"

//ADC
#define ADC1_SE4_PE0_AF0
#define ADC1_SE5_PE1_AF0
#define ADC1_SE6_PE2_AF0
#define ADC1_SE7_PE3_AF0
#define ADC1_SE17_PA17_AF0
#define ADC0_SE8_PB0_AF0
#define ADC1_SE8_PB0_AF0
#define ADC0_SE9_PB1_AF0
#define ADC1_SE9_PB1_AF0
#define ADC0_SE12_PB2_AF0
#define ADC0_SE13_PB3_AF0
#define ADC1_SE14_PB10_AF0
#define ADC1_SE15_PB11_AF0
#define ADC0_SE14_PC0_AF0
#define ADC0_SE15_PC1_AF0
#define ADC0_SE4_PC2_AF0_SUB_B
#define ADC1_SE4_PC8_AF0_SUB_B
#define ADC1_SE5_PC9_AF0_SUB_B
#define ADC1_SE6_PC10_AF0_SUB_B
#define ADC1_SE7_PC11_AF0_SUB_B
#define ADC0_SE5_PD1_AF0_SUB_B
#define ADC0_SE6_PD5_AF0_SUB_B
#define ADC0_SE7_PD6_AF0_SUB_B

#define ADC_MODULE_0 1
#define ADC_MODULE_1 2

#define ADC_MODULE_COUNT 2
//EOF ADC

//I2C
#define I2C1_SDA_PE0_AF6
#define I2C1_SCL_PE1_AF6
#define I2C2_SCL_PA12_AF5
#define I2C2_SDA_PA13_AF5
#define I2C2_SCL_PA14_AF5
#define I2C0_SCL_PB0_AF2
#define I2C0_SDA_PB1_AF2
#define I2C0_SCL_PB2_AF2
#define I2C0_SDA_PB3_AF2
#define I2C1_SCL_PC10_AF2
#define I2C1_SDA_PC11_AF2
#define I2C0_SCL_PD2_AF7
#define I2C0_SDA_PD3_AF7

#define I2C_MODULE_0 1
#define I2C_MODULE_1 2
#define I2C_MODULE_2 3

#define I2C_MODULE_COUNT 3
//EOF I2C

//UART
#define UART1_TX_PE0_AF3
#define UART1_RX_PE1_AF3
#define UART3_TX_PE4_AF3
#define UART3_RX_PE5_AF3
#define UART0_RX_PA1_AF2
#define UART0_TX_PA2_AF2
#define UART0_TX_PA14_AF3
#define UART0_RX_PA15_AF3
#define UART3_RX_PB10_AF3
#define UART3_TX_PB11_AF3
#define UART0_RX_PB16_AF3
#define UART0_TX_PB17_AF3
#define UART1_RX_PC3_AF3
#define UART1_TX_PC4_AF3
#define UART3_RX_PC16_AF3
#define UART3_TX_PC17_AF3
#define UART2_RX_PD2_AF3
#define UART2_TX_PD3_AF3
#define UART0_RX_PD6_AF3
#define UART0_TX_PD7_AF3

#define UART_MODULE_0 1
#define UART_MODULE_1 2
#define UART_MODULE_2 3
#define UART_MODULE_3 4

#define UART_MODULE_COUNT 4
//EOF UART

//SPI
#define SPI1_MOSI_PE1_AF2
#define SPI1_MISO_PE1_AF7
#define SPI1_SCK_PE2_AF2
#define SPI1_MISO_PE3_AF2
#define SPI1_MOSI_PE3_AF7
#define SPI0_SCK_PA15_AF2
#define SPI0_MOSI_PA16_AF2
#define SPI0_MISO_PA17_AF2
#define SPI1_SCK_PB11_AF2
#define SPI1_MOSI_PB16_AF2
#define SPI1_MISO_PB17_AF2
#define SPI0_SCK_PC5_AF2
#define SPI0_MOSI_PC6_AF2
#define SPI0_MISO_PC7_AF2
#define SPI0_SCK_PD1_AF2
#define SPI0_MOSI_PD2_AF2
#define SPI0_MISO_PD3_AF2

#define SPI_MODULE_0 1
#define SPI_MODULE_1 2

#define SPI_MODULE_COUNT 2
//EOF SPI

//SPI PCS
#define SPI1_PCS1_PE0_AF2
#define SPI1_PCS0_PE4_AF2
#define SPI1_PCS2_PE5_AF2
#define SPI0_PCS0_PA14_AF2
#define SPI1_PCS0_PB10_AF2
#define SPI0_PCS4_PC0_AF2
#define SPI0_PCS3_PC1_AF2
#define SPI0_PCS2_PC2_AF2
#define SPI0_PCS1_PC3_AF2
#define SPI0_PCS0_PC4_AF2
#define SPI0_PCS0_PD0_AF2
#define SPI0_PCS1_PD4_AF2
#define SPI0_PCS2_PD5_AF2
#define SPI0_PCS3_PD6_AF2
//EOF SPI PCS

//TIM
#define TIM3_CH0_PE5_AF6
#define TIM0_CH5_PA0_AF3
#define TIM0_CH6_PA1_AF3
#define TIM0_CH7_PA2_AF3
#define TIM0_CH0_PA3_AF3
#define TIM0_CH1_PA4_AF3
#define TIM0_CH2_PA5_AF3
#define TIM1_CH0_PA12_AF3
#define TIM1_CH1_PA13_AF3
#define TIM1_CH0_PB0_AF3
#define TIM1_CH1_PB1_AF3
#define TIM2_CH0_PB18_AF3
#define TIM2_CH1_PB19_AF3
#define TIM0_CH0_PC1_AF4
#define TIM0_CH1_PC2_AF4
#define TIM0_CH2_PC3_AF4
#define TIM0_CH3_PC4_AF4
#define TIM0_CH2_PC5_AF7
#define TIM3_CH4_PC8_AF3
#define TIM3_CH5_PC9_AF3
#define TIM3_CH6_PC10_AF3
#define TIM3_CH7_PC11_AF3
#define TIM3_CH0_PD0_AF4
#define TIM3_CH1_PD1_AF4
#define TIM3_CH2_PD2_AF4
#define TIM3_CH3_PD3_AF4
#define TIM0_CH4_PD4_AF4
#define TIM0_CH5_PD5_AF4
#define TIM0_CH6_PD6_AF4
#define TIM0_CH7_PD7_AF4

#define TIM_MODULE_0 1
#define TIM_MODULE_1 2
#define TIM_MODULE_2 3
#define TIM_MODULE_3 4

#define TIM_MODULE_COUNT 4
//EOF TIM

//GPIO
#define __PE0_CN
#define __PE1_CN
#define __PE2_CN
#define __PE3_CN
#define __PE4_CN
#define __PE5_CN
#define __PA0_CN
#define __PA1_CN
#define __PA2_CN
#define __PA3_CN
#define __PA4_CN
#define __PA5_CN
#define __PA12_CN
#define __PA13_CN
#define __PA14_CN
#define __PA15_CN
#define __PA16_CN
#define __PA17_CN
#define __PA18_CN
#define __PA19_CN
#define __PB0_CN
#define __PB1_CN
#define __PB2_CN
#define __PB3_CN
#define __PB10_CN
#define __PB11_CN
#define __PB16_CN
#define __PB17_CN
#define __PB18_CN
#define __PB19_CN
#define __PC0_CN
#define __PC1_CN
#define __PC2_CN
#define __PC3_CN
#define __PC4_CN
#define __PC5_CN
#define __PC6_CN
#define __PC7_CN
#define __PC8_CN
#define __PC9_CN
#define __PC10_CN
#define __PC11_CN
#define __PC16_CN
#define __PC17_CN
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
#define __PORT_E_CN

#define PORT_SIZE (32)
#define PORT_COUNT (5)
//EOF GPIO

//IVT_TABLE
#define UART0_NVIC 47
#define UART1_NVIC 49
#define UART2_NVIC 51
#define UART3_NVIC 53
//EOF IVT_TABLE

#endif // _MCU_DEFINITIONS_H_
// ------------------------------------------------------------------------- END
