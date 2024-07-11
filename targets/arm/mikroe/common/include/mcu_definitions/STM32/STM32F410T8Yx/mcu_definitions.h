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
 * @brief MCU specific pin and module definitions.
 */

#ifndef _MCU_DEFINITIONS_H_
#define _MCU_DEFINITIONS_H_

#include "mcu_reg_addresses.h"
#include "dma_definitions.h"
#include "can_definitions.h"

//ADC
#define ADC1_PA0_CH0
#define ADC1_PA2_CH2
#define ADC1_PA3_CH3
#define ADC1_PA5_CH5

#define ADC_MODULE_1 1

#define ADC_MODULE_COUNT 1
//EOF ADC

//I2C
#define I2C1_SCL_PB6_AF4
#define I2C1_SCL_PB8_AF4
#define I2C1_SDA_PB7_AF4
#define I2C2_SCL_PB10_AF4
#define I2C2_SDA_PB3_AF9

#define I2C_MODULE_1 1
#define I2C_MODULE_2 2

#define I2C_MODULE_COUNT 2
//EOF I2C

//UART

//EOF UART

//USART
#define UART1_RX_PB3_AF7
#define UART1_RX_PB7_AF7
#define UART1_TX_PA15_AF7
#define UART1_TX_PB6_AF7
#define UART2_RX_PA3_AF7
#define UART2_TX_PA2_AF7

#define UART_MODULE_1 1
#define UART_MODULE_2 2

#define UART_MODULE_COUNT 2
//EOF USART

//SPI
#define SPI1_MISO_PB4_AF5
#define SPI1_MOSI_PB5_AF5
#define SPI1_SCK_PA5_AF5
#define SPI1_SCK_PB3_AF5

#define SPI_MODULE_1 1

#define SPI_MODULE_COUNT 1
//EOF SPI

//TIM
#define TIM1_BKIN_PB12_AF1
#define TIM1_CH1_PA8_AF1
#define TIM1_ETR_PA12_AF1
#define TIM5_CH1_PA0_AF2
#define TIM5_CH1_PB12_AF2
#define TIM5_CH3_PA2_AF2
#define TIM5_CH4_PA3_AF2
#define TIM9_CH1_PA2_AF3
#define TIM9_CH2_PA3_AF3

#define TIM1_BUS 2
#define TIM5_BUS 1
#define TIM9_BUS 2

#define TIM_MODULE_1 1
#define TIM_MODULE_5 2
#define TIM_MODULE_9 3

#define TIM_MODULE_COUNT 3
//EOF TIM

//GPIO
#define __PH1_CN
#define __PH0_CN
#define __PC15_CN
#define __PC14_CN
#define __PC13_CN
#define __PB8_CN
#define __PB7_CN
#define __PB6_CN
#define __PB5_CN
#define __PB4_CN
#define __PB3_CN
#define __PB2_CN
#define __PB12_CN
#define __PB10_CN
#define __PA8_CN
#define __PA5_CN
#define __PA3_CN
#define __PA2_CN
#define __PA15_CN
#define __PA14_CN
#define __PA13_CN
#define __PA12_CN
#define __PA0_CN

#define __PORT_A_CN
#define __PORT_B_CN
#define __PORT_C_CN
#define __PORT_H_CN

#define PORT_SIZE (16)
#define PORT_COUNT (4)
//EOF GPIO

//IVT_TABLE
#define UART1_NVIC  53
#define UART2_NVIC  54
//EOF IVT_TABLE


#endif // _MCU_DEFINITIONS_H_
// ------------------------------------------------------------------------- END
