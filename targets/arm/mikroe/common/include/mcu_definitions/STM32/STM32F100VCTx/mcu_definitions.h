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
#include "dma_definitions.h"
#include "can_definitions.h"

//ADC
#define ADC1_PC5_CH15
#define ADC1_PC4_CH14
#define ADC1_PC3_CH13
#define ADC1_PC2_CH12
#define ADC1_PC1_CH11
#define ADC1_PC0_CH10
#define ADC1_PB1_CH9
#define ADC1_PB0_CH8
#define ADC1_PA7_CH7
#define ADC1_PA6_CH6
#define ADC1_PA5_CH5
#define ADC1_PA4_CH4
#define ADC1_PA3_CH3
#define ADC1_PA2_CH2
#define ADC1_PA1_CH1
#define ADC1_PA0_CH0

#define ADC_MODULE_1 1

#define ADC_MODULE_COUNT 1
//EOF ADC

//I2C
#define I2C1_SCL_PB6
#define I2C1_SCL_PB8_REMAP
#define I2C1_SDA_PB7
#define I2C1_SDA_PB9_REMAP
#define I2C2_SCL_PB10
#define I2C2_SDA_PB11

#define I2C_MODULE_1 1
#define I2C_MODULE_2 2

#define I2C_MODULE_COUNT 2
//EOF I2C

//UART
#define UART4_RX_PC11
#define UART4_TX_PC10
#define UART5_RX_PD2
#define UART5_TX_PC12

#define UART_MODULE_4 4
#define UART_MODULE_5 5
//EOF UART

//USART
#define UART1_RX_PA10
#define UART1_RX_PB7_REMAP
#define UART1_TX_PA9
#define UART1_TX_PB6_REMAP
#define UART2_RX_PA3
#define UART2_RX_PD6_REMAP
#define UART2_TX_PA2
#define UART2_TX_PD5_REMAP
#define UART3_RX_PB11
#define UART3_RX_PC11_REMAP
#define UART3_RX_PD9_REMAP
#define UART3_TX_PB10
#define UART3_TX_PC10_REMAP
#define UART3_TX_PD8_REMAP

#define UART_MODULE_1 1
#define UART_MODULE_2 2
#define UART_MODULE_3 3

#define UART_MODULE_COUNT 5
//EOF USART

//SPI
#define SPI1_MISO_PA6
#define SPI1_MISO_PB4_REMAP
#define SPI1_MOSI_PA7
#define SPI1_MOSI_PB5_REMAP
#define SPI1_SCK_PA5
#define SPI1_SCK_PB3_REMAP
#define SPI2_MISO_PB14
#define SPI2_MOSI_PB15
#define SPI2_SCK_PB13

#define SPI_MODULE_1 1
#define SPI_MODULE_2 2

#define SPI_MODULE_COUNT 2
//EOF SPI

//TIM
#define TIM1_BKIN_PA6_REMAP
#define TIM1_BKIN_PB12
#define TIM1_BKIN_PE15_REMAP
#define TIM1_CH1_PA8
#define TIM1_CH1_PE9_REMAP
#define TIM1_CH1N_PA7_REMAP
#define TIM1_CH1N_PB13
#define TIM1_CH1N_PE8_REMAP
#define TIM1_CH2_PE11_REMAP
#define TIM1_CH2N_PB0_REMAP
#define TIM1_CH2N_PB14
#define TIM1_CH2N_PE10_REMAP
#define TIM1_CH3_PE13_REMAP
#define TIM1_CH3N_PB1_REMAP
#define TIM1_CH3N_PE12_REMAP
#define TIM1_CH4_PA11
#define TIM1_CH4_PE14_REMAP
#define TIM1_ETR_PA12
#define TIM1_ETR_PE7_REMAP
#define TIM12_CH1_PB12_REMAP
#define TIM12_CH1_PC4
#define TIM12_CH2_PB13_REMAP
#define TIM12_CH2_PC5
#define TIM13_CH1_PB0_REMAP
#define TIM13_CH1_PC8
#define TIM14_CH1_PB1_REMAP
#define TIM14_CH1_PC9
#define TIM15_BKIN_PA9
#define TIM15_CH1_PA2
#define TIM15_CH1_PB14_REMAP
#define TIM15_CH1N_PB15
#define TIM15_CH2_PA3
#define TIM16_BKIN_PB5
#define TIM16_CH1_PA6_REMAP
#define TIM16_CH1_PB8
#define TIM16_CH1N_PB6
#define TIM17_BKIN_PA10
#define TIM17_CH1_PA7_REMAP
#define TIM17_CH1_PB9
#define TIM17_CH1N_PB7
#define TIM2_CH1_PA0
#define TIM2_CH1_PA15
#define TIM2_CH2_PA1
#define TIM2_CH2_PB3
#define TIM2_CH3_PA2
#define TIM2_CH3_PB10
#define TIM2_CH4_PA3
#define TIM2_CH4_PB11
#define TIM2_ETR_PA15
#define TIM3_CH1_PA6
#define TIM3_CH1_PB4_REMAP
#define TIM3_CH1_PC6_REMAP
#define TIM3_CH2_PA7
#define TIM3_CH2_PC7_REMAP
#define TIM3_CH3_PB0
#define TIM3_CH3_PC8_REMAP
#define TIM3_CH4_PB1
#define TIM3_CH4_PC9_REMAP
#define TIM3_ETR_PD2
#define TIM4_CH1_PD12_REMAP
#define TIM4_CH2_PD13_REMAP
#define TIM4_CH3_PB8
#define TIM4_CH3_PD14_REMAP
#define TIM4_CH4_PB9
#define TIM4_CH4_PD15_REMAP
#define TIM4_ETR_PE0

#define TIM1_BUS 2
#define TIM12_BUS 1
#define TIM13_BUS 1
#define TIM14_BUS 1
#define TIM15_BUS 2
#define TIM16_BUS 2
#define TIM17_BUS 2
#define TIM2_BUS 1
#define TIM3_BUS 1
#define TIM4_BUS 1

#define TIM_MODULE_1 1
#define TIM_MODULE_12 5
#define TIM_MODULE_13 6
#define TIM_MODULE_14 7
#define TIM_MODULE_15 8
#define TIM_MODULE_16 9
#define TIM_MODULE_17 10
#define TIM_MODULE_2 2
#define TIM_MODULE_3 3
#define TIM_MODULE_4 4

#define TIM_MODULE_COUNT 10
//EOF TIM

//GPIO
#define __PE9_CN
#define __PE8_CN
#define __PE7_CN
#define __PE6_CN
#define __PE5_CN
#define __PE4_CN
#define __PE3_CN
#define __PE2_CN
#define __PE15_CN
#define __PE14_CN
#define __PE13_CN
#define __PE12_CN
#define __PE11_CN
#define __PE10_CN
#define __PE1_CN
#define __PE0_CN
#define __PD9_CN
#define __PD8_CN
#define __PD7_CN
#define __PD6_CN
#define __PD5_CN
#define __PD4_CN
#define __PD3_CN
#define __PD2_CN
#define __PD15_CN
#define __PD14_CN
#define __PD13_CN
#define __PD12_CN
#define __PD11_CN
#define __PD10_CN
#define __PD1_CN
#define __PD0_CN
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
#define __PORT_E_CN

#define PORT_SIZE (16)
#define PORT_COUNT (5)
//EOF GPIO

//IVT_TABLE
#define UART1_NVIC  53
#define UART2_NVIC  54
#define UART3_NVIC  55
#define UART4_NVIC  68
#define UART5_NVIC  69
//EOF IVT_TABLE


#endif // _MCU_DEFINITIONS_H_
// ------------------------------------------------------------------------- END
