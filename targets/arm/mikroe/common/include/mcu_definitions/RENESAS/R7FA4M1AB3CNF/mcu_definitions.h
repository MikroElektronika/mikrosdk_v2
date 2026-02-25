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
#define __P010_CN
#define __P011_CN
#define __P012_CN
#define __P013_CN
#define __P014_CN
#define __P015_CN
#define __P100_CN
#define __P101_CN
#define __P102_CN
#define __P108_CN
#define __P109_CN
#define __P110_CN
#define __P111_CN
#define __P112_CN
#define __P200_CN
#define __P201_CN
#define __P212_CN
#define __P213_CN
#define __P214_CN
#define __P215_CN
#define __P300_CN
#define __P301_CN
#define __P407_CN
#define __P408_CN
#define __P914_CN
#define __P915_CN

#define __PORT_0_CN
#define __PORT_1_CN
#define __PORT_2_CN
#define __PORT_3_CN
#define __PORT_4_CN
#define __PORT_9_CN

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
#ifdef __P010_CN
#define ADC0_P010_AN005
#endif
#ifdef __P011_CN
#define ADC0_P011_AN006
#endif
#ifdef __P012_CN
#define ADC0_P012_AN007
#endif
#ifdef __P013_CN
#define ADC0_P013_AN008
#endif
#ifdef __P014_CN
#define ADC0_P014_AN009
#endif
#ifdef __P015_CN
#define ADC0_P015_AN010
#endif
#ifdef __P100_CN
#define ADC0_P100_AN022
#endif
#ifdef __P101_CN
#define ADC0_P101_AN021
#endif
#ifdef __P102_CN
#define ADC0_P102_AN020
#endif

#define ADC_MODULE_0 1

#define ADC_MODULE_COUNT 1
//EOF ADC

//SCI
#ifdef __P100_CN
#define SCI0_SCL_P100_AF4
#define SCI0_MISO_P100_AF4
#endif
#ifdef __P101_CN
#define SCI0_SDA_P101_AF4
#define SCI0_MOSI_P101_AF4
#endif
#ifdef __P102_CN
#define SCI0_SCK_P102_AF4
#endif
#ifdef __P100_CN
#define SCI1_SCK_P100_AF5
#endif
#ifdef __P109_CN
#define SCI1_SCK_P109_AF5
#endif
#ifdef __P112_CN
#define SCI1_SCK_P112_AF5
#endif
#ifdef __P212_CN
#define SCI1_SCL_P212_AF5
#define SCI1_MISO_P212_AF5
#endif
#ifdef __P213_CN
#define SCI1_SDA_P213_AF5
#define SCI1_MOSI_P213_AF5
#endif
#ifdef __P102_CN
#define SCI2_SDA_P102_AF4
#define SCI2_MOSI_P102_AF4
#endif
#ifdef __P111_CN
#define SCI2_SCK_P111_AF4
#endif
#ifdef __P112_CN
#define SCI2_SDA_P112_AF4
#define SCI2_MOSI_P112_AF4
#endif
#ifdef __P301_CN
#define SCI2_SCL_P301_AF4
#define SCI2_MISO_P301_AF4
#endif
#ifdef __P109_CN
#define SCI9_SDA_P109_AF5
#define SCI9_MOSI_P109_AF5
#endif
#ifdef __P110_CN
#define SCI9_SCL_P110_AF5
#define SCI9_MISO_P110_AF5
#endif
#ifdef __P111_CN
#define SCI9_SCK_P111_AF5
#endif
#ifdef __P408_CN
#define SCI9_SCL_P408_AF5
#define SCI9_MISO_P408_AF5
#endif

#define SCI_MODULE_0 1
#define SCI_MODULE_1 2
#define SCI_MODULE_2 3
#define SCI_MODULE_9 10

#define SCI_MODULE_COUNT 4
//EOF SCI

//I2C
#ifdef __P407_CN
#define I2C0_SDA_P407_AF7
#endif
#ifdef __P408_CN
#define I2C0_SCL_P408_AF7
#endif
#ifdef __P100_CN
#define I2C1_SCL_P100_AF7
#endif
#ifdef __P101_CN
#define I2C1_SDA_P101_AF7
#endif

#define I2C_MODULE_0 (SCI_MODULE_COUNT + 1)
#define I2C_MODULE_1 (SCI_MODULE_COUNT + 2)

#define I2C_MODULE_COUNT (SCI_MODULE_COUNT + 2)
//EOF I2C

//UART
#ifdef __P100_CN
#define UART0_RX_P100_AF4
#endif
#ifdef __P101_CN
#define UART0_TX_P101_AF4
#endif
#ifdef __P212_CN
#define UART1_RX_P212_AF5
#endif
#ifdef __P213_CN
#define UART1_TX_P213_AF5
#endif
#ifdef __P102_CN
#define UART2_TX_P102_AF4
#endif
#ifdef __P112_CN
#define UART2_TX_P112_AF4
#endif
#ifdef __P301_CN
#define UART2_RX_P301_AF4
#endif
#ifdef __P109_CN
#define UART9_TX_P109_AF5
#endif
#ifdef __P110_CN
#define UART9_RX_P110_AF5
#endif
#ifdef __P408_CN
#define UART9_RX_P408_AF5
#endif

#define UART_MODULE_0 1
#define UART_MODULE_1 2
#define UART_MODULE_2 3
#define UART_MODULE_9 10

#define UART_MODULE_COUNT 4
//EOF UART

//SPI
#ifdef __P100_CN
#define SPI0_MISO_P100_AF6
#endif
#ifdef __P101_CN
#define SPI0_MOSI_P101_AF6
#endif
#ifdef __P102_CN
#define SPI0_SCK_P102_AF6
#endif
#ifdef __P109_CN
#define SPI1_MOSI_P109_AF6
#endif
#ifdef __P110_CN
#define SPI1_MISO_P110_AF6
#endif
#ifdef __P111_CN
#define SPI1_SCK_P111_AF6
#endif

#define SPI_MODULE_0 (SCI_MODULE_COUNT + 1)
#define SPI_MODULE_1 (SCI_MODULE_COUNT + 2)

#define SPI_MODULE_COUNT (SCI_MODULE_COUNT + 2)
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
#ifdef __P109_CN
#define TIM1_P109_CHA_AF3
#endif
#ifdef __P110_CN
#define TIM1_P110_CHB_AF3
#endif
#ifdef __P102_CN
#define TIM2_P102_CHB_AF3
#endif
#ifdef __P111_CN
#define TIM3_P111_CHA_AF3
#endif
#ifdef __P112_CN
#define TIM3_P112_CHB_AF3
#endif
#ifdef __P301_CN
#define TIM4_P301_CHB_AF3
#endif
#ifdef __P100_CN
#define TIM5_P100_CHB_AF3
#endif
#ifdef __P101_CN
#define TIM5_P101_CHA_AF3
#endif
#ifdef __P408_CN
#define TIM5_P408_CHB_AF3
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
#define UART0_ERI_EVENT 0x9B
#define UART0_ERI_NVIC 2
#define UART0_RXI_EVENT 0x98
#define UART0_RXI_NVIC 1
#define UART0_TXI_EVENT 0x99
#define UART0_TXI_NVIC 0
#define UART1_ERI_EVENT 0xA1
#define UART1_ERI_NVIC 5
#define UART1_RXI_EVENT 0x9E
#define UART1_RXI_NVIC 4
#define UART1_TXI_EVENT 0x9F
#define UART1_TXI_NVIC 3
#define UART2_ERI_EVENT 0xA6
#define UART2_ERI_NVIC 8
#define UART2_RXI_EVENT 0xA3
#define UART2_RXI_NVIC 7
#define UART2_TXI_EVENT 0xA4
#define UART2_TXI_NVIC 6
#define UART9_ERI_EVENT 0xAB
#define UART9_ERI_NVIC 29
#define UART9_RXI_EVENT 0xA8
#define UART9_RXI_NVIC 28
#define UART9_TXI_EVENT 0xA9
#define UART9_TXI_NVIC 27
//EOF IVT_TABLE

#endif // _MCU_DEFINITIONS_H_
// ------------------------------------------------------------------------- END
