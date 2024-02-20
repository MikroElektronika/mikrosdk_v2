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
#define ADC_PA0_CH0
#define ADC_PA1_CH1
#define ADC_PA2_CH2
#define ADC_PA3_CH3
#define ADC_PA4_CH4
#define ADC_PA5_CH5
#define ADC_PA6_CH6
#define ADC_PA7_CH7
#define ADC_PB0_CH8
#define ADC_PB1_CH9
#define ADC_PB12_CH18
#define ADC_PB13_CH19
#define ADC_PB14_CH20
#define ADC_PC0_CH10
#define ADC_PC1_CH11
#define ADC_PC2_CH12
#define ADC_PC3_CH13
#define ADC_PC4_CH14
#define ADC_PC5_CH15

#define ADC_MODULE 1

#define ADC_MODULE_COUNT 1
//EOF ADC

//I2C
#define I2C1_SCL_PB6_AF4
#define I2C1_SCL_PB8_AF4
#define I2C1_SDA_PB7_AF4
#define I2C1_SDA_PB9_AF4
#define I2C2_SCL_PB10_AF4
#define I2C2_SDA_PB11_AF4

#define I2C_MODULE_1 1
#define I2C_MODULE_2 2

#define I2C_MODULE_COUNT 2
//EOF I2C

//UART

//EOF UART

//USART
#define UART1_RX_PA10_AF7
#define UART1_RX_PB7_AF7
#define UART1_TX_PA9_AF7
#define UART1_TX_PB6_AF7
#define UART2_RX_PA3_AF7
#define UART2_TX_PA2_AF7
#define UART3_RX_PB11_AF7
#define UART3_RX_PC11_AF7
#define UART3_TX_PB10_AF7
#define UART3_TX_PC10_AF7

#define UART_MODULE_1 1
#define UART_MODULE_2 2
#define UART_MODULE_3 3

#define UART_MODULE_COUNT 3
//EOF USART

//SPI
#define SPI1_MISO_PA11_AF5
#define SPI1_MISO_PA6_AF5
#define SPI1_MISO_PB4_AF5
#define SPI1_MOSI_PA12_AF5
#define SPI1_MOSI_PA7_AF5
#define SPI1_MOSI_PB5_AF5
#define SPI1_SCK_PA5_AF5
#define SPI1_SCK_PB3_AF5
#define SPI2_MISO_PB14_AF5
#define SPI2_MOSI_PB15_AF5
#define SPI2_SCK_PB13_AF5

#define SPI_MODULE_1 1
#define SPI_MODULE_2 2

#define SPI_MODULE_COUNT 2
//EOF SPI

//TIM
#define TIM10_CH1_PA6_AF3
#define TIM10_CH1_PB12_AF3
#define TIM10_CH1_PB8_AF3
#define TIM11_CH1_PA7_AF3
#define TIM11_CH1_PB15_AF3
#define TIM11_CH1_PB9_AF3
#define TIM2_CH1_PA0_AF1
#define TIM2_CH1_PA15_AF1
#define TIM2_CH1_PA5_AF1
#define TIM2_CH2_PA1_AF1
#define TIM2_CH2_PB3_AF1
#define TIM2_CH3_PA2_AF1
#define TIM2_CH3_PB10_AF1
#define TIM2_CH4_PA3_AF1
#define TIM2_CH4_PB11_AF1
#define TIM2_ETR_PA0_AF1
#define TIM3_CH1_PA6_AF2
#define TIM3_CH1_PB4_AF2
#define TIM3_CH1_PC6_AF2
#define TIM3_CH2_PA7_AF2
#define TIM3_CH2_PB5_AF2
#define TIM3_CH2_PC7_AF2
#define TIM3_CH3_PB0_AF2
#define TIM3_CH3_PC8_AF2
#define TIM3_CH4_PB1_AF2
#define TIM3_CH4_PC9_AF2
#define TIM3_ETR_PD2_AF2
#define TIM4_CH1_PB6_AF2
#define TIM4_CH2_PB7_AF2
#define TIM4_CH3_PB8_AF2
#define TIM4_CH4_PB9_AF2
#define TIM9_CH1_PA2_AF3
#define TIM9_CH1_PB13_AF3
#define TIM9_CH2_PA3_AF3
#define TIM9_CH2_PB14_AF3
#define TIMX_IC1_PA0_AF14
#define TIMX_IC1_PA12_AF14
#define TIMX_IC1_PA4_AF14
#define TIMX_IC1_PA8_AF14
#define TIMX_IC1_PC0_AF14
#define TIMX_IC1_PC12_AF14
#define TIMX_IC1_PC4_AF14
#define TIMX_IC1_PC8_AF14
#define TIMX_IC2_PA1_AF14
#define TIMX_IC2_PA13_AF14
#define TIMX_IC2_PA5_AF14
#define TIMX_IC2_PA9_AF14
#define TIMX_IC2_PC1_AF14
#define TIMX_IC2_PC13_AF14
#define TIMX_IC2_PC5_AF14
#define TIMX_IC2_PC9_AF14
#define TIMX_IC3_PA10_AF14
#define TIMX_IC3_PA14_AF14
#define TIMX_IC3_PA2_AF14
#define TIMX_IC3_PA6_AF14
#define TIMX_IC3_PC10_AF14
#define TIMX_IC3_PC14_AF14
#define TIMX_IC3_PC2_AF14
#define TIMX_IC3_PC6_AF14
#define TIMX_IC3_PD2_AF14
#define TIMX_IC4_PA11_AF14
#define TIMX_IC4_PA15_AF14
#define TIMX_IC4_PA3_AF14
#define TIMX_IC4_PA7_AF14
#define TIMX_IC4_PC11_AF14
#define TIMX_IC4_PC15_AF14
#define TIMX_IC4_PC3_AF14
#define TIMX_IC4_PC7_AF14

#define TIM10_BUS 2
#define TIM11_BUS 2
#define TIM2_BUS 1
#define TIM3_BUS 1
#define TIM4_BUS 1
#define TIM9_BUS 2

#define TIM_MODULE_10 9
#define TIM_MODULE_11 10
#define TIM_MODULE_2 2
#define TIM_MODULE_3 4
#define TIM_MODULE_4 6
#define TIM_MODULE_9 8
#define TIM_MODULE_TIMX_IC1 1
#define TIM_MODULE_TIMX_IC2 3
#define TIM_MODULE_TIMX_IC3 5
#define TIM_MODULE_TIMX_IC4 7

#define TIM_MODULE_COUNT 10
//EOF TIM

//GPIO
#define __PH1_CN
#define __PH0_CN
#define __PD2_CN
#define __PC9_CN
#define __PC8_CN
#define __PC7_CN
#define __PC6_CN
#define __PC5_CN
#define __PC4_CN
#define __PC3_CN
#define __PC2_CN
#define __PC15_CN
#define __PC14_CN
#define __PC13_CN
#define __PC12_CN
#define __PC11_CN
#define __PC10_CN
#define __PC1_CN
#define __PC0_CN
#define __PB9_CN
#define __PB8_CN
#define __PB7_CN
#define __PB6_CN
#define __PB5_CN
#define __PB4_CN
#define __PB3_CN
#define __PB2_CN
#define __PB15_CN
#define __PB14_CN
#define __PB13_CN
#define __PB12_CN
#define __PB11_CN
#define __PB10_CN
#define __PB1_CN
#define __PB0_CN
#define __PA9_CN
#define __PA8_CN
#define __PA7_CN
#define __PA6_CN
#define __PA5_CN
#define __PA4_CN
#define __PA3_CN
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
#define __PORT_D_CN
#define __PORT_H_CN

#define PORT_SIZE (16)
#define PORT_COUNT (5)
//EOF GPIO

//IVT_TABLE
#define UART1_NVIC  53
#define UART2_NVIC  54
#define UART3_NVIC  55
//EOF IVT_TABLE


#endif // _MCU_DEFINITIONS_H_
// ------------------------------------------------------------------------- END
