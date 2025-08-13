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
#define ADC0_P003_AN007
#define ADC0_P008_AN003
#define ADC0_P009_AN004
#define ADC0_P014_AN005
#define ADC0_P015_AN006
#define ADC0_P500_AN016
#define ADC0_P502_AN017
#define ADC0_P504_AN018
#define ADC0_P506_AN019
#define ADC0_P508_AN020
#define ADC1_P004_AN100
#define ADC1_P005_AN101
#define ADC1_P006_AN102
#define ADC1_P007_AN107
#define ADC1_P010_AN103
#define ADC1_P014_AN105
#define ADC1_P015_AN106
#define ADC1_P501_AN116
#define ADC1_P503_AN117
#define ADC1_P505_AN118
#define ADC1_P507_AN119

#define ADC_MODULE_0 1
#define ADC_MODULE_1 2

#define ADC_MODULE_COUNT 2
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
#define I2C2_SCL_P512_AF7
#define I2C2_SDA_P511_AF7

#define I2C_MODULE_0 1
#define I2C_MODULE_1 2
#define I2C_MODULE_2 3

#define I2C_MODULE_COUNT 3
//EOF I2C

//UART
#define UART0_RX_P100_AF4
#define UART0_RX_P410_AF4
#define UART0_TX_P101_AF4
#define UART0_TX_P411_AF4
#define UART1_RX_P212_AF5
#define UART1_RX_P708_AF5
#define UART1_TX_P213_AF5
#define UART2_RX_P113_AF4
#define UART2_RX_P301_AF4
#define UART2_TX_P112_AF4
#define UART2_TX_P302_AF4
#define UART3_RX_P309_AF5
#define UART3_RX_P408_AF5
#define UART3_RX_P706_AF5
#define UART3_TX_P310_AF5
#define UART3_TX_P409_AF5
#define UART3_TX_P707_AF5
#define UART4_RX_P206_AF4
#define UART4_RX_P315_AF4
#define UART4_RX_P511_AF4
#define UART4_TX_P205_AF4
#define UART4_TX_P512_AF4
#define UART4_TX_P900_AF4
#define UART5_RX_P502_AF5
#define UART5_RX_P513_AF5
#define UART5_TX_P501_AF5
#define UART5_TX_P805_AF5
#define UART6_RX_P304_AF4
#define UART6_RX_P505_AF4
#define UART6_TX_P305_AF4
#define UART6_TX_P506_AF4
#define UART7_RX_P402_AF5
#define UART7_RX_P614_AF5
#define UART7_TX_P401_AF5
#define UART7_TX_P613_AF5
#define UART8_RX_P104_AF4
#define UART8_RX_P607_AF4
#define UART8_TX_P105_AF4
#define UART8_TX_PA00_AF4
#define UART9_RX_P110_AF5
#define UART9_RX_P202_AF5
#define UART9_RX_P601_AF5
#define UART9_TX_P109_AF5
#define UART9_TX_P203_AF5
#define UART9_TX_P602_AF5

#define UART_MODULE_0 1
#define UART_MODULE_1 2
#define UART_MODULE_2 3
#define UART_MODULE_3 4
#define UART_MODULE_4 5
#define UART_MODULE_5 6
#define UART_MODULE_6 7
#define UART_MODULE_7 8
#define UART_MODULE_8 9
#define UART_MODULE_9 10

#define UART_MODULE_COUNT 10
//EOF UART

//SPI
#define SPI0_MISO_P100_AF6
#define SPI0_MISO_P410_AF6
#define SPI0_MOSI_P101_AF6
#define SPI0_MOSI_P411_AF6
#define SPI0_SCK_P102_AF6
#define SPI0_SCK_P412_AF6
#define SPI1_MISO_P110_AF6
#define SPI1_MISO_P202_AF6
#define SPI1_MISO_P700_AF6
#define SPI1_MOSI_P109_AF6
#define SPI1_MOSI_P203_AF6
#define SPI1_MOSI_P701_AF6
#define SPI1_SCK_P111_AF6
#define SPI1_SCK_P204_AF6
#define SPI1_SCK_P702_AF6

#define SPI_MODULE_0 1
#define SPI_MODULE_1 2

#define SPI_MODULE_COUNT 2
//EOF SPI

//TIM
#define TIM0_P108_CHB_AF3
#define TIM0_P212_CHB_AF3
#define TIM0_P213_CHA_AF3
#define TIM0_P300_CHA_AF3
#define TIM0_P414_CHB_AF3
#define TIM0_P415_CHA_AF3
#define TIM0_P511_CHB_AF3
#define TIM0_P512_CHA_AF3
#define TIM1_P104_CHB_AF3
#define TIM1_P105_CHA_AF3
#define TIM1_P109_CHA_AF3
#define TIM1_P110_CHB_AF3
#define TIM1_P405_CHA_AF3
#define TIM1_P406_CHB_AF3
#define TIM2_P102_CHB_AF3
#define TIM2_P103_CHA_AF3
#define TIM2_P113_CHA_AF3
#define TIM2_P114_CHB_AF3
#define TIM3_P111_CHA_AF3
#define TIM3_P112_CHB_AF3
#define TIM3_P403_CHA_AF3
#define TIM3_P404_CHB_AF3
#define TIM4_P115_CHA_AF3
#define TIM4_P204_CHB_AF3
#define TIM4_P205_CHA_AF3
#define TIM4_P301_CHB_AF3
#define TIM4_P302_CHA_AF3
#define TIM4_P608_CHB_AF3
#define TIM5_P100_CHB_AF3
#define TIM5_P101_CHA_AF3
#define TIM5_P202_CHB_AF3
#define TIM5_P203_CHA_AF3
#define TIM5_P609_CHA_AF3
#define TIM5_P610_CHB_AF3
#define TIM5_P700_CHA_AF3
#define TIM5_P701_CHB_AF3
#define TIM6_P400_CHA_AF3
#define TIM6_P401_CHB_AF3
#define TIM6_P600_CHB_AF3
#define TIM6_P601_CHA_AF3
#define TIM6_P702_CHA_AF3
#define TIM6_P703_CHB_AF3
#define TIM7_P303_CHB_AF3
#define TIM7_P304_CHA_AF3
#define TIM7_P602_CHB_AF3
#define TIM7_P603_CHA_AF3
#define TIM8_P106_CHB_AF3
#define TIM8_P107_CHA_AF3
#define TIM8_P604_CHB_AF3
#define TIM8_P605_CHA_AF3
#define TIM9_P410_CHB_AF3
#define TIM9_P411_CHA_AF3

#define TIM_MODULE_0 1
#define TIM_MODULE_1 2
#define TIM_MODULE_2 3
#define TIM_MODULE_3 4
#define TIM_MODULE_4 5
#define TIM_MODULE_5 6
#define TIM_MODULE_6 7
#define TIM_MODULE_7 8
#define TIM_MODULE_8 9
#define TIM_MODULE_9 10

#define TIM_MODULE_COUNT 10
//EOF TIM

//GPIO
#define __P000_CN
#define __P001_CN
#define __P002_CN
#define __P003_CN
#define __P004_CN
#define __P005_CN
#define __P006_CN
#define __P007_CN
#define __P008_CN
#define __P009_CN
#define __P010_CN
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
#define __P114_CN
#define __P115_CN
#define __P200_CN
#define __P201_CN
#define __P202_CN
#define __P203_CN
#define __P204_CN
#define __P205_CN
#define __P206_CN
#define __P207_CN
#define __P208_CN
#define __P209_CN
#define __P210_CN
#define __P211_CN
#define __P212_CN
#define __P213_CN
#define __P214_CN
#define __P300_CN
#define __P301_CN
#define __P302_CN
#define __P303_CN
#define __P304_CN
#define __P305_CN
#define __P306_CN
#define __P307_CN
#define __P308_CN
#define __P309_CN
#define __P310_CN
#define __P311_CN
#define __P312_CN
#define __P313_CN
#define __P314_CN
#define __P315_CN
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
#define __P412_CN
#define __P413_CN
#define __P414_CN
#define __P415_CN
#define __P500_CN
#define __P501_CN
#define __P502_CN
#define __P503_CN
#define __P504_CN
#define __P505_CN
#define __P506_CN
#define __P507_CN
#define __P508_CN
#define __P511_CN
#define __P512_CN
#define __P513_CN
#define __P600_CN
#define __P601_CN
#define __P602_CN
#define __P603_CN
#define __P604_CN
#define __P605_CN
#define __P606_CN
#define __P607_CN
#define __P608_CN
#define __P609_CN
#define __P610_CN
#define __P611_CN
#define __P612_CN
#define __P613_CN
#define __P614_CN
#define __P615_CN
#define __P700_CN
#define __P701_CN
#define __P702_CN
#define __P703_CN
#define __P704_CN
#define __P705_CN
#define __P706_CN
#define __P707_CN
#define __P708_CN
#define __P800_CN
#define __P801_CN
#define __P802_CN
#define __P803_CN
#define __P804_CN
#define __P805_CN
#define __P806_CN
#define __P900_CN
#define __P901_CN
#define __P905_CN
#define __P906_CN
#define __P907_CN
#define __P908_CN

#define __PORT_0_CN
#define __PORT_1_CN
#define __PORT_2_CN
#define __PORT_3_CN
#define __PORT_4_CN
#define __PORT_5_CN
#define __PORT_6_CN
#define __PORT_7_CN
#define __PORT_8_CN
#define __PORT_9_CN

#define PORT_SIZE (16)
#define PORT_COUNT (10)
//EOF GPIO

//IVT_TABLE
#define UART0_TXI_NVIC 0
#define UART0_TXI_EVENT 0x175
#define UART0_RXI_NVIC 1
#define UART0_RXI_EVENT 0x174
#define UART0_ERI_NVIC 2
#define UART0_ERI_EVENT 0x177
#define UART1_TXI_NVIC 3
#define UART1_TXI_EVENT 0x17B
#define UART1_RXI_NVIC 4
#define UART1_RXI_EVENT 0x17A
#define UART1_ERI_NVIC 5
#define UART1_ERI_EVENT 0x17D
#define UART2_TXI_NVIC 6
#define UART2_TXI_EVENT 0x181
#define UART2_RXI_NVIC 7
#define UART2_RXI_EVENT 0x180
#define UART2_ERI_NVIC 8
#define UART2_ERI_EVENT 0x183
#define UART3_TXI_NVIC 9
#define UART3_TXI_EVENT 0x187
#define UART3_RXI_NVIC 10
#define UART3_RXI_EVENT 0x186
#define UART3_ERI_NVIC 11
#define UART3_ERI_EVENT 0x189
#define UART4_TXI_NVIC 12
#define UART4_TXI_EVENT 0x18D
#define UART4_RXI_NVIC 13
#define UART4_RXI_EVENT 0x18C
#define UART4_ERI_NVIC 14
#define UART4_ERI_EVENT 0x18F
#define UART5_TXI_NVIC 15
#define UART5_TXI_EVENT 0x193
#define UART5_RXI_NVIC 16
#define UART5_RXI_EVENT 0x192
#define UART5_ERI_NVIC 17
#define UART5_ERI_EVENT 0x195
#define UART6_TXI_NVIC 18
#define UART6_TXI_EVENT 0x199
#define UART6_RXI_NVIC 19
#define UART6_RXI_EVENT 0x198
#define UART6_ERI_NVIC 20
#define UART6_ERI_EVENT 0x19B
#define UART7_TXI_NVIC 21
#define UART7_TXI_EVENT 0x19F
#define UART7_RXI_NVIC 22
#define UART7_RXI_EVENT 0x19E
#define UART7_ERI_NVIC 23
#define UART7_ERI_EVENT 0x1A1
#define UART8_TXI_NVIC 24
#define UART8_TXI_EVENT 0x1A5
#define UART8_RXI_NVIC 25
#define UART8_RXI_EVENT 0x1A4
#define UART8_ERI_NVIC 26
#define UART8_ERI_EVENT 0x1A7
#define UART9_TXI_NVIC 27
#define UART9_TXI_EVENT 0x1AB
#define UART9_RXI_NVIC 28
#define UART9_RXI_EVENT 0x1AA
#define UART9_ERI_NVIC 29
#define UART9_ERI_EVENT 0x1AD
//EOF IVT_TABLE


#endif // _MCU_DEFINITIONS_H_
// ------------------------------------------------------------------------- END