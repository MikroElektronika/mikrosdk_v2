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

//ADC
#define ADC1_CH6_PE0_AF0_MUX0_F
#define ADC1_CH7_PE1_AF0_MUX1_F
#define ADC0_CH0_PE16_AF0
#define ADC0_CH1_PE17_AF0
#define ADC1_CH0_PE18_AF0
#define ADC1_CH1_PE19_AF0
#define ADC0_CH4_PE29_AF0
#define ADC0_CH5_PE30_AF0
#define ADC1_CH4_PE24_AF0
#define ADC1_CH5_PE25_AF0
#define ADC1_CH2_PB0_AF0
#define ADC1_CH3_PB1_AF0
#define ADC0_CH6_PB2_AF0_MUX0_E
#define ADC1_CH7_PB3_AF0_MUX1_E
#define ADC1_CH6_PC0_AF0_MUX0_B
#define ADC1_CH7_PC1_AF0_MUX1_B
#define ADC1_CH6_PC2_AF0_MUX0_C
#define ADC1_CH7_PC8_AF0_MUX1_C
#define ADC1_CH6_PC9_AF0_MUX0_D
#define ADC1_CH7_PC10_AF0_MUX1_D
#define ADC1_CH6_PC11_AF0_MUX0_E
#define ADC0_CH7_PD1_AF0_MUX1_F
#define ADC0_CH6_PD5_AF0_MUX0_G
#define ADC0_CH7_PD6_AF0_MUX1_G

#define ADC_MODULE_0 1
#define ADC_MODULE_1 2

#define ADC_MODULE_COUNT 2
//EOF ADC

//I2C
#define I2C0_SDA_PE18_AF4
#define I2C0_SCL_PE19_AF4
#define I2C0_SCL_PE24_AF5
#define I2C0_SDA_PE25_AF5
#define I2C0_SCL_PB0_AF2
#define I2C0_SDA_PB1_AF2
#define I2C0_SCL_PB2_AF2
#define I2C0_SDA_PB3_AF2
#define I2C0_SCL_PC6_AF7
#define I2C0_SDA_PC7_AF7
#define I2C0_SCL_PD2_AF7
#define I2C0_SDA_PD3_AF7

#define I2C_MODULE_0 1

#define I2C_MODULE_COUNT 1
//EOF I2C

//UART
#define UART1_TX_PE0_AF3
#define UART1_RX_PE1_AF3
#define UART1_TX_PE16_AF3
#define UART1_RX_PE17_AF3
#define UART0_RX_PA1_AF2
#define UART0_TX_PA2_AF2
#define UART0_RX_PB0_AF7
#define UART0_TX_PB1_AF7
#define UART0_RX_PB16_AF3
#define UART0_TX_PB17_AF3
#define UART1_RX_PC3_AF3
#define UART1_TX_PC4_AF3
#define UART0_RX_PC6_AF5
#define UART0_TX_PC7_AF5
#define UART0_RX_PD6_AF3
#define UART0_TX_PD7_AF3

#define UART_MODULE_0 1
#define UART_MODULE_1 2

#define UART_MODULE_COUNT 2
//EOF UART

//SPI
#define SPI0_SCK_PE17_AF2
#define SPI0_MOSI_PE18_AF2
#define SPI0_MISO_PE19_AF2
#define SPI0_SCK_PC5_AF2
#define SPI0_MOSI_PC6_AF2
#define SPI0_MISO_PC7_AF2
#define SPI0_SCK_PD1_AF2
#define SPI0_MOSI_PD2_AF2
#define SPI0_MISO_PD3_AF2
#define SPI0_SCK_PD5_AF7
#define SPI0_MOSI_PD6_AF7
#define SPI0_MISO_PD7_AF7

#define SPI_MODULE_0 1

#define SPI_MODULE_COUNT 1
//EOF SPI

//SPI PCS
#define SPI0_PCS0_PE16_AF2
#define SPI0_PCS4_PC0_AF2
#define SPI0_PCS0_PC0_AF7
#define SPI0_PCS3_PC1_AF2
#define SPI0_PCS2_PC2_AF2
#define SPI0_PCS1_PC3_AF2
#define SPI0_PCS0_PC4_AF2
#define SPI0_PCS0_PD0_AF2
#define SPI0_PCS1_PD4_AF2
#define SPI0_PCS0_PD4_AF7
#define SPI0_PCS2_PD5_AF2
#define SPI0_PCS3_PD6_AF2
//EOF SPI PCS

//TIM
#define TIM0_CH2_PE29_AF3
#define TIM0_CH3_PE30_AF3
#define TIM0_CH0_PE24_AF3
#define TIM0_CH1_PE25_AF3
#define TIM0_CH5_PA0_AF3
#define TIM0_CH6_PA1_AF3
#define TIM1_CH1_PA1_AF6
#define TIM0_CH7_PA2_AF3
#define TIM1_CH0_PA2_AF6
#define TIM0_CH0_PA3_AF3
#define TIM0_CH1_PA4_AF3
#define TIM0_CH2_PA5_AF3
#define TIM1_CH0_PA12_AF3
#define TIM1_CH1_PA13_AF3
#define TIM3_CH2_PA18_AF6
#define TIM1_CH0_PB0_AF3
#define TIM1_CH1_PB1_AF3
#define TIM3_CH2_PB18_AF4
#define TIM3_CH3_PB19_AF4
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
#define TIM0_CH0_PD0_AF5
#define TIM3_CH1_PD1_AF4
#define TIM0_CH1_PD1_AF5
#define TIM3_CH2_PD2_AF4
#define TIM0_CH2_PD2_AF5
#define TIM3_CH3_PD3_AF4
#define TIM0_CH3_PD3_AF5
#define TIM0_CH4_PD4_AF4
#define TIM0_CH5_PD5_AF4
#define TIM0_CH6_PD6_AF4
#define TIM1_CH0_PD6_AF5
#define TIM0_CH7_PD7_AF4
#define TIM1_CH1_PD7_AF5

#define TIM_MODULE_0 1
#define TIM_MODULE_1 2
#define TIM_MODULE_3 3

#define TIM_MODULE_COUNT 3
//EOF TIM

//GPIO
#define __PE0_CN
#define __PE1_CN
#define __PE16_CN
#define __PE17_CN
#define __PE18_CN
#define __PE19_CN
#define __PE29_CN
#define __PE30_CN
#define __PE24_CN
#define __PE25_CN
#define __PA0_CN
#define __PA1_CN
#define __PA2_CN
#define __PA3_CN
#define __PA4_CN
#define __PA5_CN
#define __PA12_CN
#define __PA13_CN
#define __PA18_CN
#define __PA19_CN
#define __PB0_CN
#define __PB1_CN
#define __PB2_CN
#define __PB3_CN
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
//EOF IVT_TABLE

#endif // _MCU_DEFINITIONS_H_
// ------------------------------------------------------------------------- END
