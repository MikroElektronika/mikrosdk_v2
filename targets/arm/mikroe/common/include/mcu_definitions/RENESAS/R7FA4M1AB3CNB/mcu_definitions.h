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

//ADC
#define ADC0_P000_AN000
#define ADC0_P001_AN001
#define ADC0_P002_AN002
#define ADC0_P003_AN003
#define ADC0_P004_AN004
#define ADC0_P010_AN005
#define ADC0_P011_AN006
#define ADC0_P012_AN007
#define ADC0_P013_AN008
#define ADC0_P014_AN009
#define ADC0_P015_AN010
#define ADC0_P100_AN022
#define ADC0_P101_AN021
#define ADC0_P102_AN020
#define ADC0_P103_AN019
#define ADC0_P500_AN016
#define ADC0_P501_AN017
#define ADC0_P502_AN018

#define ADC_MODULE_0 1

#define ADC_MODULE_COUNT 1
//EOF ADC

//I2C
#define I2C0_SCL_P204_AF7
#define I2C0_SCL_P400_AF7
#define I2C0_SCL_P408_AF7
#define I2C0_SDA_P401_AF7
#define I2C0_SDA_P407_AF7
#define I2C1_SCL_P100_AF7
#define I2C1_SCL_P205_AF7
#define I2C1_SDA_P101_AF7
#define I2C1_SDA_P206_AF7

#define I2C_MODULE_0 1
#define I2C_MODULE_1 2

#define I2C_MODULE_COUNT 2
//EOF I2C

//UART
#define UART0_RX_P100_AF4
#define UART0_RX_P104_AF4
#define UART0_RX_P206_AF4
#define UART0_RX_P410_AF4
#define UART0_TX_P101_AF4
#define UART0_TX_P205_AF4
#define UART0_TX_P411_AF4
#define UART1_RX_P212_AF5
#define UART1_RX_P402_AF5
#define UART1_RX_P502_AF5
#define UART1_TX_P213_AF5
#define UART1_TX_P401_AF5
#define UART1_TX_P501_AF5
#define UART2_RX_P301_AF4
#define UART2_TX_P102_AF4
#define UART2_TX_P112_AF4
#define UART2_TX_P302_AF4
#define UART9_RX_P110_AF5
#define UART9_RX_P408_AF5
#define UART9_TX_P109_AF5
#define UART9_TX_P409_AF5

#define UART_MODULE_0 1
#define UART_MODULE_1 2
#define UART_MODULE_2 3
#define UART_MODULE_9 10

#define UART_MODULE_COUNT 4
//EOF UART

//SPI
#define SPI0_MISO_P100_AF6
#define SPI0_MISO_P410_AF6
#define SPI0_MOSI_P101_AF6
#define SPI0_MOSI_P411_AF6
#define SPI0_SCK_P102_AF6
#define SPI1_MISO_P110_AF6
#define SPI1_MOSI_P109_AF6
#define SPI1_SCK_P111_AF6
#define SPI1_SCK_P204_AF6

#define SPI_MODULE_0 1
#define SPI_MODULE_1 2

#define SPI_MODULE_COUNT 2
//EOF SPI

//TIM
#define TIM0_P106_CHB_AF3
#define TIM0_P107_CHA_AF3
#define TIM0_P108_CHB_AF3
#define TIM0_P212_CHB_AF3
#define TIM0_P213_CHA_AF3
#define TIM0_P300_CHA_AF3
#define TIM1_P104_CHB_AF3
#define TIM1_P105_CHA_AF3
#define TIM1_P109_CHA_AF3
#define TIM1_P110_CHB_AF3
#define TIM2_P102_CHB_AF3
#define TIM2_P103_CHA_AF3
#define TIM2_P113_CHA_AF3
#define TIM2_P500_CHA_AF3
#define TIM2_P501_CHB_AF3
#define TIM3_P111_CHA_AF3
#define TIM3_P112_CHB_AF3
#define TIM3_P502_CHB_AF3
#define TIM4_P204_CHB_AF3
#define TIM4_P205_CHA_AF3
#define TIM4_P301_CHB_AF3
#define TIM4_P302_CHA_AF3
#define TIM5_P100_CHB_AF3
#define TIM5_P101_CHA_AF3
#define TIM5_P408_CHB_AF3
#define TIM5_P409_CHA_AF3
#define TIM6_P400_CHA_AF3
#define TIM6_P401_CHB_AF3
#define TIM6_P410_CHB_AF3
#define TIM6_P411_CHA_AF3
#define TIM7_P303_CHB_AF3
#define TIM7_P304_CHA_AF3

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

//GPIO
#define __P000_CN
#define __P001_CN
#define __P002_CN
#define __P003_CN
#define __P004_CN
#define __P010_CN
#define __P011_CN
#define __P012_CN
#define __P013_CN
#define __P014_CN
#define __P015_CN
#define __P100_CN
#define __P101_CN
#define __P102_CN
#define __P103_CN
#define __P104_CN
#define __P105_CN
#define __P106_CN
#define __P107_CN
#define __P108_CN
#define __P109_CN
#define __P110_CN
#define __P111_CN
#define __P112_CN
#define __P113_CN
#define __P200_CN
#define __P201_CN
#define __P204_CN
#define __P205_CN
#define __P206_CN
#define __P212_CN
#define __P213_CN
#define __P214_CN
#define __P215_CN
#define __P300_CN
#define __P301_CN
#define __P302_CN
#define __P303_CN
#define __P304_CN
#define __P400_CN
#define __P401_CN
#define __P402_CN
#define __P407_CN
#define __P408_CN
#define __P409_CN
#define __P410_CN
#define __P411_CN
#define __P500_CN
#define __P501_CN
#define __P502_CN
#define __P914_CN
#define __P915_CN

#define __PORT_0_CN
#define __PORT_1_CN
#define __PORT_2_CN
#define __PORT_3_CN
#define __PORT_4_CN
#define __PORT_5_CN
#define __PORT_9_CN

#define PORT_SIZE (16)
#define PORT_COUNT (7)
//EOF GPIO

//IVT_TABLE
#define UART0_TXI_NVIC 0
#define UART0_TXI_EVENT 0x99
#define UART0_RXI_NVIC 1
#define UART0_RXI_EVENT 0x98
<<<<<<< HEAD
#define UART0_ERI_NVIC 2
#define UART0_ERI_EVENT 0x9B
#define UART1_TXI_NVIC 3
#define UART1_TXI_EVENT 0x9F
#define UART1_RXI_NVIC 4
#define UART1_RXI_EVENT 0x9E
#define UART1_ERI_NVIC 5
#define UART1_ERI_EVENT 0xA1
#define UART2_TXI_NVIC 6
#define UART2_TXI_EVENT 0xA4
#define UART2_RXI_NVIC 7
#define UART2_RXI_EVENT 0xA3
#define UART2_ERI_NVIC 8
#define UART2_ERI_EVENT 0xA6
#define UART9_TXI_NVIC 27
#define UART9_TXI_EVENT 0xA9
#define UART9_RXI_NVIC 28
#define UART9_RXI_EVENT 0xA8
#define UART9_ERI_NVIC 29
#define UART9_ERI_EVENT 0xAB
=======
#define UART1_TXI_NVIC 2
#define UART1_TXI_EVENT 0x9F
#define UART1_RXI_NVIC 3
#define UART1_RXI_EVENT 0x9E
#define UART2_TXI_NVIC 4
#define UART2_TXI_EVENT 0xA4
#define UART2_RXI_NVIC 5
#define UART2_RXI_EVENT 0xA3
#define UART9_TXI_NVIC 18
#define UART9_TXI_EVENT 0xA9
#define UART9_RXI_NVIC 19
#define UART9_RXI_EVENT 0xA8
>>>>>>> origin/mikrosdk-2.15.0
//EOF IVT_TABLE


#endif // _MCU_DEFINITIONS_H_
<<<<<<< HEAD
// ------------------------------------------------------------------------- END
=======
// ------------------------------------------------------------------------- END
>>>>>>> origin/mikrosdk-2.15.0
