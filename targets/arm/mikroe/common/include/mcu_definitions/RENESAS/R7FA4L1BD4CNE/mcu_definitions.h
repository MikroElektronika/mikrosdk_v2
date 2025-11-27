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
#define __P002_CN
#define __P003_CN
#define __P004_CN
#define __P010_CN
#define __P011_CN
#define __P100_CN
#define __P101_CN
#define __P102_CN
#define __P103_CN
#define __P108_CN
#define __P109_CN
#define __P110_CN
#define __P111_CN
#define __P112_CN
#define __P200_CN
#define __P201_CN
#define __P206_CN
#define __P207_CN
#define __P212_CN
#define __P213_CN
#define __P214_CN
#define __P215_CN
#define __P300_CN
#define __P301_CN
#define __P302_CN
#define __P400_CN
#define __P401_CN
#define __P407_CN
#define __P408_CN
#define __P409_CN
#define __P500_CN
#define __P506_CN
#define __P507_CN
#define __P508_CN
#define __P509_CN
#define __P814_CN
#define __P815_CN

#define __PORT_0_CN
#define __PORT_1_CN
#define __PORT_2_CN
#define __PORT_3_CN
#define __PORT_4_CN
#define __PORT_5_CN
#define __PORT_8_CN

#define PORT_SIZE (16)
#define PORT_COUNT (7)
//EOF GPIO

//ADC
#ifdef __P002_CN
#define ADC0_P002_AN000
#endif
#ifdef __P003_CN
#define ADC0_P003_AN001
#endif
#ifdef __P004_CN
#define ADC0_P004_AN002
#endif
#ifdef __P010_CN
#define ADC0_P010_AN003
#endif
#ifdef __P011_CN
#define ADC0_P011_AN004
#endif
#ifdef __P500_CN
#define ADC0_P500_AN021
#endif
#ifdef __P506_CN
#define ADC0_P506_AN020
#endif
#ifdef __P507_CN
#define ADC0_P507_AN019
#endif
#ifdef __P508_CN
#define ADC0_P508_AN018
#endif
#ifdef __P509_CN
#define ADC0_P509_AN017
#endif

#define ADC_MODULE_0 1

#define ADC_MODULE_COUNT 1
//EOF ADC

//I2C
#ifdef __P100_CN
#define I2C0_SDA0_P100_AF7
#endif
#ifdef __P101_CN
#define I2C0_SCL0_P101_AF7
#endif
#ifdef __P301_CN
#define I2C0_SDA0_P301_AF7
#endif
#ifdef __P302_CN
#define I2C0_SCL0_P302_AF7
#endif

#define I2C_MODULE_0 1

#define I2C_MODULE_COUNT 1
//EOF I2C

//UART
#ifdef __P100_CN
#define UART0_RX0_P100_AF4
#endif
#ifdef __P101_CN
#define UART0_TX0_P101_AF4
#endif
#ifdef __P212_CN
#define UART0_RX0_P212_AF4
#endif
#ifdef __P213_CN
#define UART0_TX0_P213_AF4
#endif
#ifdef __P400_CN
#define UART1_TX1_P400_AF5
#endif
#ifdef __P401_CN
#define UART1_RX1_P401_AF5
#endif
#ifdef __P102_CN
#define UART3_RX3_P102_AF5
#endif
#ifdef __P103_CN
#define UART3_TX3_P103_AF5
#endif
#ifdef __P408_CN
#define UART3_RX3_P408_AF5
#endif
#ifdef __P409_CN
#define UART3_TX3_P409_AF5
#endif
#ifdef __P206_CN
#define UART4_RX4_P206_AF4
#endif
#ifdef __P207_CN
#define UART4_TX4_P207_AF4
#endif
#ifdef __P301_CN
#define UART5_RX5_P301_AF5
#endif
#ifdef __P302_CN
#define UART5_TX5_P302_AF5
#endif
#ifdef __P506_CN
#define UART5_TX5_P506_AF5
#endif
#ifdef __P507_CN
#define UART5_RX5_P507_AF5
#endif
#ifdef __P109_CN
#define UART9_TX9_P109_AF5
#endif
#ifdef __P110_CN
#define UART9_RX9_P110_AF5
#endif

#define UART_MODULE_0 1
#define UART_MODULE_1 2
#define UART_MODULE_3 3
#define UART_MODULE_4 4
#define UART_MODULE_5 5
#define UART_MODULE_9 6

#define UART_MODULE_COUNT 6
//EOF UART

//SPI
#ifdef __P109_CN
#define SPI0_MOSI0_P109_AF6
#endif
#ifdef __P110_CN
#define SPI0_MISO0_P110_AF6
#endif
#ifdef __P111_CN
#define SPI0_SCK0_P111_AF6
#endif

#define SPI_MODULE_0 1

#define SPI_MODULE_COUNT 1
//EOF SPI

//TIM
#ifdef __P108_CN
#define TIM0_P108_CH0B_AF3
#endif
#ifdef __P212_CN
#define TIM0_P212_CH0B_AF3
#endif
#ifdef __P213_CN
#define TIM0_P213_CH0A_AF3
#endif
#ifdef __P300_CN
#define TIM0_P300_CH0A_AF3
#endif
#ifdef __P109_CN
#define TIM1_P109_CH1A_AF3
#endif
#ifdef __P110_CN
#define TIM1_P110_CH1B_AF3
#endif
#ifdef __P400_CN
#define TIM2_P400_CH2A_AF3
#endif
#ifdef __P401_CN
#define TIM2_P401_CH2B_AF3
#endif
#ifdef __P407_CN
#define TIM2_P407_CH2A_AF3
#endif
#ifdef __P408_CN
#define TIM2_P408_CH2B_AF3
#endif
#ifdef __P206_CN
#define TIM3_P206_CH3B_AF3
#endif
#ifdef __P207_CN
#define TIM3_P207_CH3A_AF3
#endif
#ifdef __P301_CN
#define TIM4_P301_CH4B_AF3
#endif
#ifdef __P302_CN
#define TIM4_P302_CH4A_AF3
#endif
#ifdef __P506_CN
#define TIM4_P506_CH4A_AF3
#endif
#ifdef __P507_CN
#define TIM4_P507_CH4B_AF3
#endif
#ifdef __P100_CN
#define TIM5_P100_CH5B_AF3
#endif
#ifdef __P101_CN
#define TIM5_P101_CH5A_AF3
#endif

#define TIM_MODULE_0 1
#define TIM_MODULE_1 2
#define TIM_MODULE_2 3
#define TIM_MODULE_3 4
#define TIM_MODULE_4 5
#define TIM_MODULE_5 6

#define TIM_MODULE_COUNT 6
//EOF TIM

//IVT_TABLE
#define UART0_ERI_EVENT 0x177
#define UART0_ERI_NVIC 2
#define UART0_RXI_EVENT 0x174
#define UART0_RXI_NVIC 1
#define UART0_TXI_EVENT 0x175
#define UART0_TXI_NVIC 0
#define UART1_ERI_EVENT 0x17D
#define UART1_ERI_NVIC 5
#define UART1_RXI_EVENT 0x17A
#define UART1_RXI_NVIC 4
#define UART1_TXI_EVENT 0x17B
#define UART1_TXI_NVIC 3
#define UART2_ERI_EVENT 0x183
#define UART2_ERI_NVIC 8
#define UART2_RXI_EVENT 0x180
#define UART2_RXI_NVIC 7
#define UART2_TXI_EVENT 0x181
#define UART2_TXI_NVIC 6
#define UART3_ERI_EVENT 0x189
#define UART3_ERI_NVIC 11
#define UART3_RXI_EVENT 0x186
#define UART3_RXI_NVIC 10
#define UART3_TXI_EVENT 0x187
#define UART3_TXI_NVIC 9
#define UART4_ERI_EVENT 0x18F
#define UART4_ERI_NVIC 14
#define UART4_RXI_EVENT 0x18C
#define UART4_RXI_NVIC 13
#define UART4_TXI_EVENT 0x18D
#define UART4_TXI_NVIC 12
#define UART5_ERI_EVENT 0x195
#define UART5_ERI_NVIC 17
#define UART5_RXI_EVENT 0x192
#define UART5_RXI_NVIC 16
#define UART5_TXI_EVENT 0x193
#define UART5_TXI_NVIC 15
#define UART6_ERI_EVENT 0x19B
#define UART6_ERI_NVIC 20
#define UART6_RXI_EVENT 0x198
#define UART6_RXI_NVIC 19
#define UART6_TXI_EVENT 0x199
#define UART6_TXI_NVIC 18
#define UART7_ERI_EVENT 0x1A1
#define UART7_ERI_NVIC 23
#define UART7_RXI_EVENT 0x19E
#define UART7_RXI_NVIC 22
#define UART7_TXI_EVENT 0x19F
#define UART7_TXI_NVIC 21
#define UART8_ERI_EVENT 0x1A7
#define UART8_ERI_NVIC 26
#define UART8_RXI_EVENT 0x1A4
#define UART8_RXI_NVIC 25
#define UART8_TXI_EVENT 0x1A5
#define UART8_TXI_NVIC 24
#define UART9_ERI_EVENT 0x1AD
#define UART9_ERI_NVIC 29
#define UART9_RXI_EVENT 0x1AA
#define UART9_RXI_NVIC 28
#define UART9_TXI_EVENT 0x1AB
#define UART9_TXI_NVIC 27
//EOF IVT_TABLE


#endif // _MCU_DEFINITIONS_H_
// ------------------------------------------------------------------------- END
