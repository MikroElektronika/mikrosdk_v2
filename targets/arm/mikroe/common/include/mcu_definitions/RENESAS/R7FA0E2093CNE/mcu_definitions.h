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
#define __P008_CN
#define __P009_CN
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
#define ADC0_P000_AN008
#endif
#ifdef __P001_CN
#define ADC0_P001_AN009
#endif
#ifdef __P002_CN
#define ADC0_P002_AN010
#endif
#ifdef __P008_CN
#define ADC0_P008_AN002
#endif
#ifdef __P009_CN
#define ADC0_P009_AN003
#endif
#ifdef __P010_CN
#define ADC0_P010_AN000
#endif
#ifdef __P011_CN
#define ADC0_P011_AN001
#endif
#ifdef __P012_CN
#define ADC0_P012_AN004
#endif
#ifdef __P013_CN
#define ADC0_P013_AN005
#endif
#ifdef __P014_CN
#define ADC0_P014_AN006
#endif
#ifdef __P015_CN
#define ADC0_P015_AN007
#endif
#ifdef __P100_CN
#define ADC0_P100_AN022
#endif
#ifdef __P101_CN
#define ADC0_P101_AN021
#endif

#define ADC_MODULE_0 1

#define ADC_MODULE_COUNT 1
//EOF ADC

//SAU_I2C
#ifdef __P100_CN
#define SAU_I2C00_SDA_P100_AF3
#endif
#ifdef __P102_CN
#define SAU_I2C00_SCL_P102_AF3
#endif
#ifdef __P500_CN
#define SAU_I2C00_SCL_P500_AF2
#endif
#ifdef __P207_CN
#define SAU_I2C01_SDA_P207_AF3
#endif
#ifdef __P208_CN
#define SAU_I2C01_SCL_P208_AF3
#endif
#ifdef __P104_CN
#define SAU_I2C10_SCL_P104_AF3
#endif
#ifdef __P105_CN
#define SAU_I2C10_SDA_P105_AF3
#endif
#ifdef __P201_CN
#define SAU_I2C11_SCL_P201_AF3
#endif
#ifdef __P212_CN
#define SAU_I2C11_SDA_P212_AF4
#endif
#ifdef __P407_CN
#define SAU_I2C11_SCL_P407_AF1
#endif
#ifdef __P409_CN
#define SAU_I2C11_SCL_P409_AF1
#endif
#ifdef __P110_CN
#define SAU_I2C20_SDA_P110_AF2
#endif
#ifdef __P112_CN
#define SAU_I2C20_SCL_P112_AF2
#endif
#ifdef __P301_CN
#define SAU_I2C21_SDA_P301_AF2
#endif
#ifdef __P302_CN
#define SAU_I2C21_SCL_P302_AF2
#endif

#define SAU_I2C_MODULE_0 1
#define SAU_I2C_MODULE_1 2

 #define SAU_I2C_MODULE_COUNT 2
//EOF SAU_I2C

//SAU_SPI
#ifdef __P100_CN
#define SAU_SPI00_MISO_P100_AF3
#endif
#ifdef __P101_CN
#define SAU_SPI00_MOSI_P101_AF3
#endif
#ifdef __P102_CN
#define SAU_SPI00_SCK_P102_AF3
#endif
#ifdef __P500_CN
#define SAU_SPI00_SCK_P500_AF2
#endif
#ifdef __P206_CN
#define SAU_SPI01_MOSI_P206_AF1
#endif
#ifdef __P207_CN
#define SAU_SPI01_MISO_P207_AF3
#endif
#ifdef __P208_CN
#define SAU_SPI01_SCK_P208_AF3
#endif
#ifdef __P915_CN
#define SAU_SPI01_MOSI_P915_AF3
#endif
#ifdef __P104_CN
#define SAU_SPI10_SCK_P104_AF3
#endif
#ifdef __P105_CN
#define SAU_SPI10_MISO_P105_AF3
#endif
#ifdef __P106_CN
#define SAU_SPI10_MOSI_P106_AF3
#endif
#ifdef __P201_CN
#define SAU_SPI11_SCK_P201_AF3
#endif
#ifdef __P212_CN
#define SAU_SPI11_MISO_P212_AF4
#endif
#ifdef __P213_CN
#define SAU_SPI11_MOSI_P213_AF4
#endif
#ifdef __P407_CN
#define SAU_SPI11_SCK_P407_AF1
#endif
#ifdef __P409_CN
#define SAU_SPI11_SCK_P409_AF1
#endif
#ifdef __P109_CN
#define SAU_SPI20_MOSI_P109_AF2
#endif
#ifdef __P110_CN
#define SAU_SPI20_MISO_P110_AF2
#endif
#ifdef __P112_CN
#define SAU_SPI20_SCK_P112_AF2
#endif

#define SAU_SPI_MODULE_0 1
#define SAU_SPI_MODULE_1 2

 #define SAU_SPI_MODULE_COUNT 2
//EOF SAU_SPI

//SAU_UART
#ifdef __P100_CN
#define SAU_UART0_RX_P100_AF3
#endif
#ifdef __P101_CN
#define SAU_UART0_TX_P101_AF3
#endif
#ifdef __P212_CN
#define SAU_UART1_RX_P212_AF3
#endif
#ifdef __P213_CN
#define SAU_UART1_TX_P213_AF3
#endif
#ifdef __P109_CN
#define SAU_UART2_TX_P109_AF2
#endif
#ifdef __P110_CN
#define SAU_UART2_RX_P110_AF2
#endif

#define SAU_UART_CHANNEL_0
#define SAU_UART_CHANNEL_1
#define SAU_UART_CHANNEL_2
#define SAU_UART_MODULE_0 1
#define SAU_UART_MODULE_1 2

 #define SAU_UART_MODULE_COUNT 2
//EOF SAU_UART

//I2C
#ifdef __P100_CN
#define I2C0_SCL_P100_AF4
#endif
#ifdef __P101_CN
#define I2C0_SDA_P101_AF4
#endif
#ifdef __P109_CN
#define I2C0_SDA_P109_AF3
#endif
#ifdef __P110_CN
#define I2C0_SCL_P110_AF3
#endif
#ifdef __P212_CN
#define I2C0_SCL_P212_AF5
#endif
#ifdef __P213_CN
#define I2C0_SDA_P213_AF5
#endif
#ifdef __P913_CN
#define I2C0_SDA_P913_AF1
#endif
#ifdef __P914_CN
#define I2C0_SCL_P914_AF1
#endif
#ifdef __P102_CN
#define I2C1_SCL_P102_AF6
#endif
#ifdef __P103_CN
#define I2C1_SDA_P103_AF6
#endif
#ifdef __P206_CN
#define I2C1_SDA_P206_AF2
#endif
#ifdef __P207_CN
#define I2C1_SCL_P207_AF4
#endif
#ifdef __P208_CN
#define I2C1_SDA_P208_AF4
#endif
#ifdef __P301_CN
#define I2C1_SCL_P301_AF3
#endif
#ifdef __P302_CN
#define I2C1_SDA_P302_AF3
#endif
#ifdef __P400_CN
#define I2C1_SCL_P400_AF1
#endif
#ifdef __P401_CN
#define I2C1_SDA_P401_AF1
#endif
#ifdef __P407_CN
#define I2C1_SDA_P407_AF4
#endif
#ifdef __P408_CN
#define I2C1_SCL_P408_AF4
#endif

#define I2C_MODULE_0 3
#define I2C_MODULE_1 4

#define I2C_MODULE_COUNT (SAU_I2C_MODULE_COUNT + 2)
//EOF I2C

//UART
#ifdef __P100_CN
#define SAU_UART0_RX_P100_AF3
#endif
#ifdef __P101_CN
#define SAU_UART0_TX_P101_AF3
#endif
#ifdef __P109_CN
#define SAU_UART0_TX_P109_AF2
#endif
#ifdef __P110_CN
#define SAU_UART0_RX_P110_AF2
#endif
#ifdef __P207_CN
#define UART0_RX_P207_AF2
#endif
#ifdef __P208_CN
#define UART0_TX_P208_AF2
#endif
#ifdef __P212_CN
#define UART0_RX_P212_AF6
#endif
#ifdef __P213_CN
#define UART0_TX_P213_AF6
#endif
#ifdef __P102_CN
#define UART1_RX_P102_AF7
#endif
#ifdef __P103_CN
#define UART1_TX_P103_AF7
#endif
#ifdef __P105_CN
#define UART1_RX_P105_AF4
#endif
#ifdef __P106_CN
#define UART1_TX_P106_AF4
#endif
#ifdef __P206_CN
#define UART1_TX_P206_AF3
#endif
#ifdef __P301_CN
#define UART1_RX_P301_AF4
#endif
#ifdef __P302_CN
#define UART1_TX_P302_AF4
#endif

#define UART_MODULE_0 3
#define UART_MODULE_1 4

#define UART_MODULE_COUNT (SAU_UART_MODULE_COUNT + 2)
//EOF UART

//SPI
#define SPI_MODULE_COUNT (SAU_SPI_MODULE_COUNT + 0)
//EOF SPI

//TIM
#ifdef __P100_CN
#define TIM0_P100_CH1_AF2
#endif
#ifdef __P105_CN
#define TIM0_P105_CH1_AF1
#endif
#ifdef __P110_CN
#define TIM0_P110_CH1_AF1
#endif
#ifdef __P104_CN
#define TIM0_P104_CH2_AF1
#endif
#ifdef __P109_CN
#define TIM0_P109_CH2_AF1
#endif
#ifdef __P213_CN
#define TIM0_P213_CH2_AF2
#endif
#ifdef __P108_CN
#define TIM0_P108_CH3_AF2
#endif
#ifdef __P112_CN
#define TIM0_P112_CH3_AF1
#endif
#ifdef __P212_CN
#define TIM0_P212_CH3_AF2
#endif
#ifdef __P409_CN
#define TIM0_P409_CH3_AF2
#endif
#ifdef __P500_CN
#define TIM0_P500_CH3_AF1
#endif
#ifdef __P100_CN
#define TIM0_P100_CH4_AF1
#endif
#ifdef __P300_CN
#define TIM0_P300_CH4_AF2
#endif
#ifdef __P408_CN
#define TIM0_P408_CH4_AF2
#endif
#ifdef __P103_CN
#define TIM0_P103_CH5_AF1
#endif
#ifdef __P201_CN
#define TIM0_P201_CH5_AF1
#endif
#ifdef __P302_CN
#define TIM0_P302_CH5_AF1
#endif
#ifdef __P102_CN
#define TIM0_P102_CH6_AF1
#endif
#ifdef __P301_CN
#define TIM0_P301_CH6_AF1
#endif
#ifdef __P101_CN
#define TIM0_P101_CH7_AF1
#endif
#ifdef __P111_CN
#define TIM0_P111_CH7_AF1
#endif

#define TIM_MODULE_0 1

#define TIM_MODULE_COUNT 1
//EOF TIM

//IVT_TABLE
#define SAU1_UART_TXI2_NVIC    12
#define SAU1_UART_RXI2_NVIC    13
#define SAU0_UART_TXI0_NVIC    18
#define SAU0_UART_TXI1_NVIC    22
#define SAU0_UART_RXI1_NVIC    23
#define SAU0_UART_RXI0_NVIC    27
#define UARTA0_ERRI_NVIC       39
#define UARTA0_TXI_NVIC        40
#define UARTA0_RXI_NVIC        41
#define UARTA1_ERRI_NVIC       43
#define UARTA1_TXI_NVIC        44
#define UARTA1_RXI_NVIC        45
//EOF IVT_TABLE

#endif // _MCU_DEFINITIONS_H_
// ------------------------------------------------------------------------- END
