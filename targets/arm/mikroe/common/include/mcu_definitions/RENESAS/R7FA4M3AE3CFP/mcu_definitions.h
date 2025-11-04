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
#define ADC0_P001_AN000
#define ADC0_P002_AN000
#define ADC0_P003_AN000
#define ADC0_P004_AN000
#define ADC0_P005_AN000
#define ADC0_P006_AN000
#define ADC0_P007_AN000
#define ADC0_P008_AN000
#define ADC0_P014_AN001
#define ADC0_P015_AN001
#define ADC1_P000_AN110
#define ADC1_P001_AN110
#define ADC1_P002_AN110
#define ADC1_P500_AN111
#define ADC1_P501_AN111
#define ADC1_P502_AN111
#define ADC1_P503_AN111
#define ADC1_P504_AN112
#define ADC1_P505_AN112

#define ADC_MODULE_0 1
#define ADC_MODULE_1 2

#define ADC_MODULE_COUNT 2
//EOF ADC

//I2C
#define I2C0_SCL_P400_AF7
#define I2C0_SCL_P408_AF7
#define I2C0_SDA_P401_AF7
#define I2C0_SDA_P407_AF7
#define I2C1_SCL_P205_AF7
#define I2C1_SDA_P206_AF7

#define I2C_MODULE_0 1
#define I2C_MODULE_1 2

#define I2C_MODULE_COUNT 2
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
#define UART3_RX_P408_AF5
#define UART3_TX_P409_AF5
#define UART4_RX_P206_AF4
#define UART4_TX_P205_AF4
#define UART4_TX_P207_AF4
#define UART9_RX_P110_AF5
#define UART9_RX_P601_AF5
#define UART9_TX_P109_AF5
#define UART9_TX_P602_AF5

#define UART_MODULE_0 1
#define UART_MODULE_1 2
#define UART_MODULE_2 3
#define UART_MODULE_3 4
#define UART_MODULE_4 5
#define UART_MODULE_9 10

#define UART_MODULE_COUNT 6
//EOF UART

//SPI
#define SPI0_MISO_P110_AF6
#define SPI0_MOSI_P109_AF6
#define SPI0_SCK_P111_AF6

#define SPI_MODULE_0 1

#define SPI_MODULE_COUNT 1
//EOF SPI

//TIM




#define TIM_MODULE_COUNT 0
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
#define __P600_CN
#define __P601_CN
#define __P602_CN
#define __P608_CN
#define __P609_CN
#define __P610_CN
#define __P708_CN

#define __PORT_0_CN
#define __PORT_1_CN
#define __PORT_2_CN
#define __PORT_3_CN
#define __PORT_4_CN
#define __PORT_5_CN
#define __PORT_6_CN
#define __PORT_7_CN

#define PORT_SIZE (16)
#define PORT_COUNT (8)
//EOF GPIO

//IVT_TABLE
#define UART0_TXI_NVIC 0
#define UART0_TXI_EVENT 0x181
#define UART0_RXI_NVIC 1
#define UART0_RXI_EVENT 0x180
#define UART0_ERI_NVIC 2
#define UART0_ERI_EVENT 0x183
#define UART1_TXI_NVIC 3
#define UART1_TXI_EVENT 0x187
#define UART1_RXI_NVIC 4
#define UART1_RXI_EVENT 0x186
#define UART1_ERI_NVIC 5
#define UART1_ERI_EVENT 0x189
#define UART2_TXI_NVIC 6
#define UART2_TXI_EVENT 0x18D
#define UART2_RXI_NVIC 7
#define UART2_RXI_EVENT 0x18C
#define UART2_ERI_NVIC 8
#define UART2_ERI_EVENT 0x18F
#define UART3_TXI_NVIC 9
#define UART3_TXI_EVENT 0x193
#define UART3_RXI_NVIC 10
#define UART3_RXI_EVENT 0x192
#define UART3_ERI_NVIC 11
#define UART3_ERI_EVENT 0x195
#define UART4_TXI_NVIC 12
#define UART4_TXI_EVENT 0x199
#define UART4_RXI_NVIC 13
#define UART4_RXI_EVENT 0x198
#define UART4_ERI_NVIC 14
#define UART4_ERI_EVENT 0x19B
#define UART9_TXI_NVIC 27
#define UART9_TXI_EVENT 0x1B7
#define UART9_RXI_NVIC 28
#define UART9_RXI_EVENT 0x1B6
#define UART9_ERI_NVIC 29
#define UART9_ERI_EVENT 0x1B9
//EOF IVT_TABLE


#endif // _MCU_DEFINITIONS_H_
// ------------------------------------------------------------------------- END