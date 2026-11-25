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
#define __PD0_CN
#define __PD1_CN
#define __PD2_CN
#define __PD3_CN
#define __PD4_CN
#define __PD5_CN
#define __PE0_CN
#define __PE1_CN
#define __PE2_CN
#define __PE3_CN
#define __PE4_CN
#define __PE5_CN
#define __PE6_CN
#define __PE7_CN
#define __PF0_CN
#define __PF1_CN
#define __PF2_CN
#define __PF3_CN
#define __PF4_CN
#define __PF5_CN
#define __PG0_CN
#define __PG1_CN
#define __PG2_CN
#define __PG3_CN
#define __PH0_CN
#define __PH1_CN
#define __PJ0_CN
#define __PJ1_CN
#define __PJ2_CN

#define __PORT_A_CN
#define __PORT_B_CN
#define __PORT_C_CN
#define __PORT_D_CN
#define __PORT_E_CN
#define __PORT_F_CN
#define __PORT_G_CN
#define __PORT_H_CN
#define __PORT_J_CN

#define PORT_SIZE (8)
#define PORT_COUNT (9)
//EOF GPIO

//ADC
#ifdef __PE0_CN
#define ADC0_PE0_CH0
#endif
#ifdef __PE0_CN
#define ADC1_PE0_CH0
#endif
#ifdef __PE1_CN
#define ADC0_PE1_CH1
#endif
#ifdef __PE1_CN
#define ADC1_PE1_CH1
#endif
#ifdef __PE2_CN
#define ADC0_PE2_CH2
#endif
#ifdef __PE2_CN
#define ADC1_PE2_CH2
#endif
#ifdef __PE3_CN
#define ADC0_PE3_CH3
#endif
#ifdef __PE3_CN
#define ADC1_PE3_CH3
#endif
#ifdef __PE4_CN
#define ADC0_PE4_CH4
#endif
#ifdef __PE4_CN
#define ADC1_PE4_CH4
#endif
#ifdef __PE5_CN
#define ADC0_PE5_CH5
#endif
#ifdef __PE5_CN
#define ADC1_PE5_CH5
#endif
#ifdef __PE6_CN
#define ADC0_PE6_CH6
#endif
#ifdef __PE6_CN
#define ADC1_PE6_CH6
#endif
#ifdef __PE7_CN
#define ADC0_PE7_CH7
#endif
#ifdef __PE7_CN
#define ADC1_PE7_CH7
#endif
#ifdef __PF0_CN
#define ADC0_PF0_CH8
#endif
#ifdef __PF0_CN
#define ADC1_PF0_CH8
#endif
#ifdef __PF1_CN
#define ADC0_PF1_CH9
#endif
#ifdef __PF1_CN
#define ADC1_PF1_CH9
#endif
#ifdef __PF2_CN
#define ADC0_PF2_CH10
#endif
#ifdef __PF2_CN
#define ADC1_PF2_CH10
#endif
#ifdef __PF3_CN
#define ADC0_PF3_CH11
#endif
#ifdef __PF3_CN
#define ADC1_PF3_CH11
#endif
#ifdef __PF4_CN
#define ADC0_PF4_CH12
#endif
#ifdef __PF4_CN
#define ADC1_PF4_CH12
#endif
#ifdef __PF5_CN
#define ADC0_PF5_CH13
#endif
#ifdef __PF5_CN
#define ADC1_PF5_CH13
#endif

#define ADC_MODULE_0 1
#define ADC_MODULE_1 2

#define ADC_MODULE_COUNT 2
//EOF ADC

//I2C
#ifdef __PA3_CN
#define I2C0_SCL_PA3_AF5
#endif
#ifdef __PA4_CN
#define I2C0_SDA_PA4_AF5
#endif
#ifdef __PA5_CN
#ifdef HAL_LL_I2C1_BASE_ADDR
#define I2C1_SCL_PA5_AF5
#endif
#endif
#ifdef __PA6_CN
#ifdef HAL_LL_I2C1_BASE_ADDR
#define I2C1_SDA_PA6_AF5
#endif
#endif

#define I2C_MODULE_0 1
#define I2C_MODULE_1 2

#define I2C_MODULE_COUNT 2
//EOF I2C

//UART
#ifdef __PA1_CN
#define UART2_RX_PA1_AF2
#endif
#ifdef __PA1_CN
#define UART2_TX_PA1_AF1
#endif
#ifdef __PA2_CN
#define UART2_RX_PA2_AF1
#endif
#ifdef __PA2_CN
#define UART2_TX_PA2_AF2
#endif
#ifdef __PA3_CN
#define UART1_RX_PA3_AF2
#endif
#ifdef __PA3_CN
#define UART1_TX_PA3_AF1
#endif
#ifdef __PA4_CN
#define UART1_RX_PA4_AF1
#endif
#ifdef __PA4_CN
#define UART1_TX_PA4_AF2
#endif
#ifdef __PA5_CN
#define UART1_RX_PA5_AF2
#endif
#ifdef __PA5_CN
#define UART1_TX_PA5_AF1
#endif
#ifdef __PA6_CN
#define UART1_RX_PA6_AF1
#endif
#ifdef __PA6_CN
#define UART1_TX_PA6_AF2
#endif
#ifdef __PA7_CN
#define UART4_RX_PA7_AF2
#endif
#ifdef __PA7_CN
#define UART4_TX_PA7_AF1
#endif
#ifdef __PC0_CN
#define UART3_RX_PC0_AF2
#endif
#ifdef __PC0_CN
#define UART3_TX_PC0_AF1
#endif
#ifdef __PC1_CN
#define UART3_RX_PC1_AF1
#endif
#ifdef __PC1_CN
#define UART3_TX_PC1_AF2
#endif
#ifdef __PC2_CN
#define UART2_RX_PC2_AF2
#endif
#ifdef __PC2_CN
#define UART2_TX_PC2_AF1
#endif
#ifdef __PC3_CN
#define UART2_RX_PC3_AF1
#endif
#ifdef __PC3_CN
#define UART2_TX_PC3_AF2
#endif
#ifdef __PD2_CN
#define UART0_RX_PD2_AF1
#endif
#ifdef __PD2_CN
#define UART0_TX_PD2_AF2
#endif
#ifdef __PD3_CN
#define UART0_RX_PD3_AF2
#endif
#ifdef __PD3_CN
#define UART0_TX_PD3_AF1
#endif
#ifdef __PD4_CN
#define UART3_RX_PD4_AF1
#endif
#ifdef __PD4_CN
#define UART3_TX_PD4_AF2
#endif
#ifdef __PD5_CN
#define UART3_RX_PD5_AF2
#endif
#ifdef __PD5_CN
#define UART3_TX_PD5_AF1
#endif
#ifdef __PG0_CN
#ifdef HAL_LL_UART5_BASE_ADDRESS
#define UART5_TX_PG0_AF1
#endif
#endif
#ifdef __PG1_CN
#define UART5_RX_PG1_AF1
#endif
#ifdef __PJ2_CN
#define UART4_RX_PJ2_AF1
#endif
#ifdef __PJ2_CN
#define UART4_TX_PJ2_AF2
#endif

#define UART_MODULE_0 1
#define UART_MODULE_1 2
#define UART_MODULE_2 3
#define UART_MODULE_3 4
#define UART_MODULE_4 5
#define UART_MODULE_5 6

#define UART_MODULE_COUNT 6
//EOF UART

//SPI
#ifdef __PA0_CN
#define SPI2_SCK_PA0_AF3
#endif
#ifdef __PA1_CN
#define SPI2_MOSI_PA1_AF3
#endif
#ifdef __PA2_CN
#define SPI2_MISO_PA2_AF3
#endif
#ifdef __PC1_CN
#define SPI1_SCK_PC1_AF3
#endif
#ifdef __PC2_CN
#define SPI1_MOSI_PC2_AF3
#endif
#ifdef __PC3_CN
#define SPI1_MISO_PC3_AF3
#endif
#ifdef __PG0_CN
#ifdef HAL_LL_SPI0_MASTER_BASE_ADDR
#define SPI0_MOSI_PG0_AF3
#endif
#endif
#ifdef __PG1_CN
#ifdef HAL_LL_SPI0_MASTER_BASE_ADDR
#define SPI0_MISO_PG1_AF3
#endif
#endif
#ifdef __PG2_CN
#define SPI0_SCK_PG2_AF3
#endif

#define SPI_MODULE_0 1
#define SPI_MODULE_1 2
#define SPI_MODULE_2 3

#define SPI_MODULE_COUNT 3
//EOF SPI

//TIM
#ifdef __PA1_CN
#define TIM4_CH1_PA1_AF7
#endif
#ifdef __PA2_CN
#define TIM4_CH0_PA2_AF7
#endif
#ifdef __PA2_CN
#define TIM4_CH2_PA2_AF8
#endif
#ifdef __PA3_CN
#define TIM2_CH1_PA3_AF7
#endif
#ifdef __PA4_CN
#define TIM2_CH0_PA4_AF7
#endif
#ifdef __PA7_CN
#define TIM2_CH1_PA7_AF7
#endif
#ifdef __PB7_CN
#define TIM0_CH1_PB7_AF8
#endif
#ifdef __PC1_CN
#define TIM0_CH0_PC1_AF8
#endif
#ifdef __PC2_CN
#define TIM1_CH1_PC2_AF7
#endif
#ifdef __PC3_CN
#define TIM1_CH0_PC3_AF7
#endif
#ifdef __PC3_CN
#define TIM1_CH2_PC3_AF8
#endif
#ifdef __PD2_CN
#define TIM3_CH0_PD2_AF7
#endif
#ifdef __PD2_CN
#define TIM3_CH2_PD2_AF8
#endif
#ifdef __PD3_CN
#define TIM3_CH1_PD3_AF7
#endif
#ifdef __PD4_CN
#define TIM1_CH0_PD4_AF6
#endif
#ifdef __PD4_CN
#define TIM1_CH2_PD4_AF7
#endif
#ifdef __PD5_CN
#define TIM1_CH1_PD5_AF6
#endif
#ifdef __PG1_CN
#define TIM3_CH0_PG1_AF7
#endif
#ifdef __PG1_CN
#define TIM3_CH2_PG1_AF8
#endif
#ifdef __PG3_CN
#define TIM0_CH1_PG3_AF6
#endif
#ifdef __PJ0_CN
#define TIM4_CH1_PJ0_AF7
#endif
#ifdef __PJ1_CN
#define TIM0_CH0_PJ1_AF7
#endif
#ifdef __PJ1_CN
#define TIM0_CH2_PJ1_AF8
#endif
#ifdef __PJ2_CN
#define TIM2_CH0_PJ2_AF7
#endif
#ifdef __PJ2_CN
#define TIM2_CH2_PJ2_AF8
#endif

#define TIM_MODULE_0 1
#define TIM_MODULE_1 2
#define TIM_MODULE_2 3
#define TIM_MODULE_3 4
#define TIM_MODULE_4 5

#define TIM_MODULE_COUNT 5
//EOF TIM

//IVT_TABLE
#define UART0_RX_NVIC   68  /* INTUART0RX */
#define UART0_TX_NVIC   69  /* INTUART0TX */
#define UART1_RX_NVIC   71  /* INTUART1RX */
#define UART1_TX_NVIC   72  /* INTUART1TX */
#define UART2_RX_NVIC   74  /* INTUART2RX */
#define UART2_TX_NVIC   75  /* INTUART2TX */
#define UART3_RX_NVIC   77  /* INTUART3RX */
#define UART3_TX_NVIC   78  /* INTUART3TX */
#define UART4_RX_NVIC   80  /* INTUART4RX */
#define UART4_TX_NVIC   81  /* INTUART4TX */
#define UART5_RX_NVIC   83  /* INTUART5RX */
#define UART5_TX_NVIC   84  /* INTUART5TX */
//EOF IVT_TABLE

#endif // _MCU_DEFINITIONS_H_
// ------------------------------------------------------------------------- END
