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
#define __P108_CN
#define __P109_CN
#define __P110_CN
#define __P111_CN
#define __P112_CN
#define __P200_CN
#define __P201_CN
#define __P206_CN
#define __P207_CN
#define __P208_CN
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
#define __P913_CN
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
#ifdef __P103_CN
#define ADC0_P103_AN019
#endif

#define ADC_MODULE_0 1

#define ADC_MODULE_COUNT 1
//EOF ADC

//I2C
#ifdef __P100_CN
#define I2C0_SCL0_P100_AF7
#endif
#ifdef __P101_CN
#define I2C0_SDA0_P101_AF7
#endif
#ifdef __P400_CN
#define I2C0_SCL0_P400_AF7
#endif
#ifdef __P401_CN
#define I2C0_SDA0_P401_AF7
#endif
#ifdef __P407_CN
#define I2C0_SDA0_P407_AF7
#endif
#ifdef __P408_CN
#define I2C0_SCL0_P408_AF7
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
#ifdef __P104_CN
#define UART0_RX0_P104_AF4
#endif
#ifdef __P206_CN
#define UART0_RX0_P206_AF4
#endif
#ifdef __P212_CN
#define UART1_RX1_P212_AF5
#endif
#ifdef __P213_CN
#define UART1_TX1_P213_AF5
#endif
#ifdef __P401_CN
#define UART1_TX1_P401_AF5
#endif
#ifdef __P102_CN
#define UART2_TX2_P102_AF4
#endif
#ifdef __P112_CN
#define UART2_TX2_P112_AF4
#endif
#ifdef __P301_CN
#define UART2_RX2_P301_AF4
#endif
#ifdef __P302_CN
#define UART2_TX2_P302_AF4
#endif
#ifdef __P109_CN
#define UART9_TX9_P109_AF5
#endif
#ifdef __P110_CN
#define UART9_RX9_P110_AF5
#endif

#define UART_MODULE_0 1
#define UART_MODULE_1 2
#define UART_MODULE_2 3
#define UART_MODULE_9 4

#define UART_MODULE_COUNT 4
//EOF UART

//SPI
#ifdef __P100_CN
#define SPI0_MISO0_P100_AF6
#endif
#ifdef __P101_CN
#define SPI0_MOSI0_P101_AF6
#endif
#ifdef __P102_CN
#define SPI0_SCK0_P102_AF6
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
#define TIM4_P104_CHB_AF3
#endif
#ifdef __P109_CN
#define TIM4_P109_CHA_AF3
#endif
#ifdef __P110_CN
#define TIM4_P110_CHB_AF3
#endif
#ifdef __P102_CN
#define TIM5_P102_CHB_AF3
#endif
#ifdef __P103_CN
#define TIM5_P103_CHA_AF3
#endif
#ifdef __P500_CN
#define TIM5_P500_CHA_AF3
#endif
#ifdef __P111_CN
#define TIM6_P111_CHA_AF3
#endif
#ifdef __P112_CN
#define TIM6_P112_CHB_AF3
#endif
#ifdef __P301_CN
#define TIM7_P301_CHB_AF3
#endif
#ifdef __P302_CN
#define TIM7_P302_CHA_AF3
#endif
#ifdef __P100_CN
#define TIM8_P100_CHB_AF3
#endif
#ifdef __P101_CN
#define TIM8_P101_CHA_AF3
#endif
#ifdef __P400_CN
#define TIM9_P400_CHA_AF3
#endif
#ifdef __P401_CN
#define TIM9_P401_CHB_AF3
#endif

#define TIM_MODULE_0 1
#define TIM_MODULE_4 2
#define TIM_MODULE_5 3
#define TIM_MODULE_6 4
#define TIM_MODULE_7 5
#define TIM_MODULE_8 6
#define TIM_MODULE_9 7

#define TIM_MODULE_COUNT 7
//EOF TIM

//IVT_TABLE
#define UART0_ERI_EVENT 0x74
#define UART0_ERI_NVIC 2
#define UART0_RXI_EVENT 0x71
#define UART0_RXI_NVIC 1
#define UART0_TXI_EVENT 0x72
#define UART0_TXI_NVIC 0
#define UART1_ERI_EVENT 0x7A
#define UART1_ERI_NVIC 5
#define UART1_RXI_EVENT 0x77
#define UART1_RXI_NVIC 4
#define UART1_TXI_EVENT 0x78
#define UART1_TXI_NVIC 3
#define UART2_ERI_EVENT 0x91
#define UART2_ERI_NVIC 8
#define UART2_RXI_EVENT 0x8E
#define UART2_RXI_NVIC 7
#define UART2_TXI_EVENT 0x8F
#define UART2_TXI_NVIC 6
#define UART9_ERI_EVENT 0x7F
#define UART9_ERI_NVIC 29
#define UART9_RXI_EVENT 0x7C
#define UART9_RXI_NVIC 28
#define UART9_TXI_EVENT 0x7D
#define UART9_TXI_NVIC 27
//EOF IVT_TABLE


#endif // _MCU_DEFINITIONS_H_
// ------------------------------------------------------------------------- END