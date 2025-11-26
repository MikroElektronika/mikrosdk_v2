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
#define __P000_CN
#define __P001_CN
#define __P002_CN
#define __P003_CN
#define __P004_CN
#define __P014_CN
#define __P015_CN
#define __P100_CN
#define __P101_CN
#define __P102_CN
#define __P103_CN
#define __P104_CN
#define __P105_CN
#define __P106_CN
#define __P108_CN
#define __P109_CN
#define __P110_CN
#define __P111_CN
#define __P112_CN
#define __P113_CN
#define __P200_CN
#define __P201_CN
#define __P205_CN
#define __P206_CN
#define __P207_CN
#define __P208_CN
#define __P212_CN
#define __P213_CN
#define __P300_CN
#define __P301_CN
#define __P302_CN
#define __P303_CN
#define __P304_CN
#define __P400_CN
#define __P401_CN
#define __P402_CN
#define __P403_CN
#define __P404_CN
#define __P405_CN
#define __P406_CN
#define __P407_CN
#define __P408_CN
#define __P409_CN
#define __P410_CN
#define __P411_CN
#define __P500_CN

#define __PORT_0_CN
#define __PORT_1_CN
#define __PORT_2_CN
#define __PORT_3_CN
#define __PORT_4_CN
#define __PORT_5_CN

#define PORT_SIZE (16)
#define PORT_COUNT (6)
//EOF GPIO

//ADC
#ifdef __P000_CN
#define ADC0_P000_AN000
#endif
#ifdef __P001_CN
#define ADC0_P001_AN001
#endif
#ifdef __P002_CN
#define ADC0_P002_AN002
#endif
#ifdef __P003_CN
#define ADC0_P003_AN003
#endif
#ifdef __P004_CN
#define ADC0_P004_AN004
#endif
#ifdef __P014_CN
#define ADC0_P014_AN012
#endif
#ifdef __P015_CN
#define ADC0_P015_AN013
#endif
#ifdef __P000_CN
#define ADC1_P000_AN100
#endif
#ifdef __P001_CN
#define ADC1_P001_AN101
#endif
#ifdef __P002_CN
#define ADC1_P002_AN102
#endif
#ifdef __P500_CN
#define ADC1_P500_AN116
#endif

#define ADC_MODULE_0 1
#define ADC_MODULE_1 2

#define ADC_MODULE_COUNT 2
//EOF ADC

//I2C
#ifdef __P400_CN
#define I2C0_SCL_P400_AF7
#endif
#ifdef __P401_CN
#define I2C0_SDA_P401_AF7
#endif
#ifdef __P407_CN
#define I2C0_SDA_P407_AF7
#endif
#ifdef __P408_CN
#define I2C0_SCL_P408_AF7
#endif
#ifdef __P205_CN
#define I2C1_SCL_P205_AF7
#endif
#ifdef __P206_CN
#define I2C1_SDA_P206_AF7
#endif

#define I2C_MODULE_0 1
#define I2C_MODULE_1 2

#define I2C_MODULE_COUNT 2
//EOF I2C

//UART
#ifdef __P100_CN
#define UART0_RX_P100_AF4
#endif
#ifdef __P101_CN
#define UART0_TX_P101_AF4
#endif
#ifdef __P410_CN
#define UART0_RX_P410_AF4
#endif
#ifdef __P411_CN
#define UART0_TX_P411_AF4
#endif
#ifdef __P212_CN
#define UART1_RX_P212_AF5
#endif
#ifdef __P213_CN
#define UART1_TX_P213_AF5
#endif
#ifdef __P112_CN
#define UART2_TX_P112_AF4
#endif
#ifdef __P113_CN
#define UART2_RX_P113_AF4
#endif
#ifdef __P301_CN
#define UART2_RX_P301_AF4
#endif
#ifdef __P302_CN
#define UART2_TX_P302_AF4
#endif
#ifdef __P408_CN
#define UART3_RX_P408_AF5
#endif
#ifdef __P409_CN
#define UART3_TX_P409_AF5
#endif
#ifdef __P205_CN
#define UART4_TX_P205_AF4
#endif
#ifdef __P206_CN
#define UART4_RX_P206_AF4
#endif
#ifdef __P207_CN
#define UART4_TX_P207_AF4
#endif
#ifdef __P109_CN
#define UART9_TX_P109_AF5
#endif
#ifdef __P110_CN
#define UART9_RX_P110_AF5
#endif

#define UART_MODULE_0 1
#define UART_MODULE_1 2
#define UART_MODULE_2 3
#define UART_MODULE_3 4
#define UART_MODULE_4 5
#define UART_MODULE_9 6

#define UART_MODULE_COUNT 6
//EOF UART

//SPI
#ifdef __P109_CN
#define SPI0_MOSI_P109_AF6
#endif
#ifdef __P110_CN
#define SPI0_MISO_P110_AF6
#endif
#ifdef __P111_CN
#define SPI0_SCK_P111_AF6
#endif

#define SPI_MODULE_0 1

#define SPI_MODULE_COUNT 1
//EOF SPI

//TIM
#ifdef __P108_CN
#define TIM0_P108_CHB_AF3
#endif
#ifdef __P212_CN
#define TIM0_P212_CHB_AF3
#endif
#ifdef __P213_CN
#define TIM0_P213_CHA_AF3
#endif
#ifdef __P300_CN
#define TIM0_P300_CHA_AF3
#endif
#ifdef __P104_CN
#define TIM1_P104_CHB_AF3
#endif
#ifdef __P105_CN
#define TIM1_P105_CHA_AF3
#endif
#ifdef __P109_CN
#define TIM1_P109_CHA_AF3
#endif
#ifdef __P110_CN
#define TIM1_P110_CHB_AF3
#endif
#ifdef __P405_CN
#define TIM1_P405_CHA_AF3
#endif
#ifdef __P406_CN
#define TIM1_P406_CHB_AF3
#endif
#ifdef __P102_CN
#define TIM2_P102_CHB_AF3
#endif
#ifdef __P103_CN
#define TIM2_P103_CHA_AF3
#endif
#ifdef __P113_CN
#define TIM2_P113_CHA_AF3
#endif
#ifdef __P111_CN
#define TIM3_P111_CHA_AF3
#endif
#ifdef __P112_CN
#define TIM3_P112_CHB_AF3
#endif
#ifdef __P403_CN
#define TIM3_P403_CHA_AF3
#endif
#ifdef __P404_CN
#define TIM3_P404_CHB_AF3
#endif
#ifdef __P205_CN
#define TIM4_P205_CHA_AF3
#endif
#ifdef __P301_CN
#define TIM4_P301_CHB_AF3
#endif
#ifdef __P302_CN
#define TIM4_P302_CHA_AF3
#endif
#ifdef __P100_CN
#define TIM5_P100_CHB_AF3
#endif
#ifdef __P101_CN
#define TIM5_P101_CHA_AF3
#endif
#ifdef __P400_CN
#define TIM6_P400_CHA_AF3
#endif
#ifdef __P401_CN
#define TIM6_P401_CHB_AF3
#endif
#ifdef __P407_CN
#define TIM6_P407_CHA_AF3
#endif
#ifdef __P408_CN
#define TIM6_P408_CHB_AF3
#endif
#ifdef __P303_CN
#define TIM7_P303_CHB_AF3
#endif
#ifdef __P304_CN
#define TIM7_P304_CHA_AF3
#endif

#define TIM_MODULE_0 1
#define TIM_MODULE_1 2
#define TIM_MODULE_2 3
#define TIM_MODULE_3 4
#define TIM_MODULE_4 5
#define TIM_MODULE_5 6
#define TIM_MODULE_6 7
#define TIM_MODULE_7 8

#define TIM_MODULE_COUNT 8
//EOF TIM

//IVT_TABLE
#define UART0_ERI_EVENT 0x183
#define UART0_ERI_NVIC 2
#define UART0_RXI_EVENT 0x180
#define UART0_RXI_NVIC 1
#define UART0_TXI_EVENT 0x181
#define UART0_TXI_NVIC 0
#define UART1_ERI_EVENT 0x189
#define UART1_ERI_NVIC 5
#define UART1_RXI_EVENT 0x186
#define UART1_RXI_NVIC 4
#define UART1_TXI_EVENT 0x187
#define UART1_TXI_NVIC 3
#define UART2_ERI_EVENT 0x18F
#define UART2_ERI_NVIC 8
#define UART2_RXI_EVENT 0x18C
#define UART2_RXI_NVIC 7
#define UART2_TXI_EVENT 0x18D
#define UART2_TXI_NVIC 6
#define UART3_ERI_EVENT 0x195
#define UART3_ERI_NVIC 11
#define UART3_RXI_EVENT 0x192
#define UART3_RXI_NVIC 10
#define UART3_TXI_EVENT 0x193
#define UART3_TXI_NVIC 9
#define UART4_ERI_EVENT 0x19B
#define UART4_ERI_NVIC 14
#define UART4_RXI_EVENT 0x198
#define UART4_RXI_NVIC 13
#define UART4_TXI_EVENT 0x199
#define UART4_TXI_NVIC 12
#define UART9_ERI_EVENT 0x1B9
#define UART9_ERI_NVIC 29
#define UART9_RXI_EVENT 0x1B6
#define UART9_RXI_NVIC 28
#define UART9_TXI_EVENT 0x1B7
#define UART9_TXI_NVIC 27
//EOF IVT_TABLE

#endif // _MCU_DEFINITIONS_H_
// ------------------------------------------------------------------------- END
