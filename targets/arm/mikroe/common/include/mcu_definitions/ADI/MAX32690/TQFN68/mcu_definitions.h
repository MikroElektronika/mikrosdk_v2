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
 * @brief MCU specific pin and module definitions for STM32C011D6_WLCSP12.
 */

#ifndef _MCU_DEFINITIONS_H_
#define _MCU_DEFINITIONS_H_

#ifdef __cplusplus
extern "C"{
#endif

#include "mcu_reg_addresses.h"

// GPIO
#define __P007_CN
#define __P008_CN
#define __P009_CN
#define __P010_CN
#define __P014_CN
#define __P023_CN
#define __P028_CN
#define __P029_CN
#define __P107_CN
#define __P108_CN
#define __P109_CN
#define __P110_CN
#define __P111_CN
#define __P112_CN
#define __P113_CN
#define __P114_CN
#define __P115_CN
#define __P116_CN
#define __P118_CN
#define __P119_CN
#define __P120_CN
#define __P121_CN
#define __P207_CN
#define __P208_CN
#define __P211_CN
#define __P212_CN
#define __P222_CN
#define __P223_CN
#define __P224_CN
#define __P225_CN
#define __P226_CN
#define __P227_CN
#define __P228_CN
#define __P229_CN
#define __P300_CN
#define __P301_CN
#define __P304_CN
#define __P400_CN

#define __PORT_0_CN
#define __PORT_1_CN
#define __PORT_2_CN
#define __PORT_3_CN
#define __PORT_4_CN

#define PORT_COUNT (5)
#define PORT_SIZE  (32)
// EOF GPIO

// ADC
#ifdef __P300_CN
#define ADC0_P300_AN000
#endif
#ifdef __P301_CN
#define ADC0_P301_AN001
#endif
#ifdef __P302_CN
#define ADC0_P302_AN102
#endif
#ifdef __P303_CN
#define ADC0_P303_AN103
#endif
#ifdef __P304_CN
#define ADC0_P304_AN204
#endif
#ifdef __P305_CN
#define ADC0_P305_AN205
#endif
#ifdef __P306_CN
#define ADC0_P306_AN306
#endif
#ifdef __P307_CN
#define ADC0_P307_AN307
#endif

#define ADC_MODULE_0 (1)

#define ADC_MODULE_COUNT (1)
// EOF ADC

// I2C
#ifdef __P207_CN
#define I2C0_SDA_P207_AF1
#endif
#ifdef __P208_CN
#define I2C0_SCL_P208_AF1
#endif
#ifdef __P030_CN
#define I2C0_SDA_P030_AF1
#endif
#ifdef __P031_CN
#define I2C0_SCL_P031_AF1
#endif
#ifdef __P011_CN
#define I2C1_SDA_P011_AF1
#endif
#ifdef __P012_CN
#define I2C1_SCL_P012_AF1
#endif
#ifdef __P217_CN
#define I2C1_SDA_P217_AF1
#endif
#ifdef __P218_CN
#define I2C1_SCL_P218_AF1
#endif
#ifdef __P013_CN
#define I2C2_SDA_P013_AF3
#endif
#ifdef __P014_CN
#define I2C2_SCL_P014_AF3
#endif
#ifdef __P107_CN
#define I2C2_SDA_P107_AF3
#endif
#ifdef __P108_CN
#define I2C2_SCL_P108_AF3
#endif

#define I2C_MODULE_0 (1)
#define I2C_MODULE_1 (2)
#define I2C_MODULE_2 (3)

#define I2C_MODULE_COUNT (3)
// EOF I2C

// U(S)ART
#ifdef __P212_CN
#define UART0_TX_P212_AF1
#endif
#ifdef __P211_CN
#define UART0_RX_P211_AF1
#endif
#ifdef __P216_CN
#define UART1_TX_P216_AF1
#endif
#ifdef __P214_CN
#define UART1_RX_P214_AF1
#endif
#ifdef __P001_CN
#define UART2_TX_P001_AF3
#endif
#ifdef __P006_CN
#define UART2_RX_P006_AF3
#endif
#ifdef __P110_CN
#define UART2_TX_P110_AF1
#endif
#ifdef __P109_CN
#define UART2_RX_P109_AF1
#endif
#ifdef __P301_CN
#define UART3_TX_P301_AF2
#endif
#ifdef __P300_CN
#define UART3_RX_P300_AF2
#endif

#define UART_MODULE_0 (1)
#define UART_MODULE_1 (2)
#define UART_MODULE_2 (3)
#define UART_MODULE_3 (3)

#define UART_MODULE_COUNT (4)
// EOF U(S)ART

// SPI
#ifdef __P229_CN
#define SPI0_SCK_P229_AF2
#endif
#ifdef __P227_CN
#define SPI0_MISO_P227_AF2
#endif
#ifdef __P228_CN
#define SPI0_MOSI_P228_AF2
#endif
#ifdef __P126_CN
#define SPI1_SCK_P126_AF1
#endif
#ifdef __P128_CN
#define SPI1_MISO_P128_AF1
#endif
#ifdef __P129_CN
#define SPI1_MOSI_P129_AF1
#endif
#ifdef __P202_CN
#define SPI2_SCK_P202_AF1
#endif
#ifdef __P203_CN
#define SPI2_MISO_P203_AF1
#endif
#ifdef __P204_CN
#define SPI2_MOSI_P204_AF1
#endif
#ifdef __P016_CN
#define SPI3_SCK_P016_AF1
#endif
#ifdef __P020_CN
#define SPI3_MISO_P020_AF1
#endif
#ifdef __P021_CN
#define SPI3_MOSI_P021_AF1
#endif
#ifdef __P103_CN
#define SPI4_SCK_P103_AF1
#endif
#ifdef __P102_CN
#define SPI4_MISO_P102_AF1
#endif
#ifdef __P101_CN
#define SPI4_MOSI_P101_AF1
#endif

#define SPI_MODULE_0 (1)
#define SPI_MODULE_1 (2)
#define SPI_MODULE_2 (3)
#define SPI_MODULE_3 (4)
#define SPI_MODULE_4 (5)

#define SPI_MODULE_COUNT (5)
// EOF SPI

// TIM
#ifdef __P004_CN
#define TIM0_P004_CHA_AF3
#endif
#ifdef __P009_CN
#define TIM0_P009_CHAN_AF3
#endif
#ifdef __P010_CN
#define TIM0_P010_CHBN_AF3
#endif
#ifdef __P011_CN
#define TIM0_P011_CHAN_AF3
#endif
#ifdef __P012_CN
#define TIM0_P012_CHBN_AF3
#endif
#ifdef __P013_CN
#define TIM0_P013_CHA_AF2
#endif
#ifdef __P014_CN
#define TIM0_P014_CHB_AF2
#endif
#ifdef __P007_CN
#define TIM1_P007_CHA_AF2
#endif
#ifdef __P008_CN
#define TIM1_P008_CHB_AF2
#endif
#ifdef __P015_CN
#define TIM1_P015_CHA_AF3
#endif
#ifdef __P017_CN
#define TIM1_P017_CHB_AF3
#endif
#ifdef __P006_CN
#define TIM2_P006_CHB_AF3
#endif
#ifdef __P104_CN
#define TIM2_P104_CHA_AF2
#endif
#ifdef __P105_CN
#define TIM2_P105_CHB_AF2
#endif
#ifdef __P220_CN
#define TIM2_P220_CHA_AF3
#endif
#ifdef __P221_CN
#define TIM2_P221_CHB_AF3
#endif
#ifdef __P113_CN
#define TIM3_P113_CHA_AF1
#endif
#ifdef __P114_CN
#define TIM3_P114_CHB_AF1
#endif
#ifdef __P230_CN
#define TIM3_P230_CHA_AF3
#endif
#ifdef __P231_CN
#define TIM3_P231_CHB_AF3
#endif

#define TIM_MODULE_0 (1)
#define TIM_MODULE_1 (2)
#define TIM_MODULE_2 (3)
#define TIM_MODULE_3 (4)

#define TIM_MODULE_COUNT (4)

// EOF TIM

// IVT_TABLE
#define UART0_NVIC  (30)
#define UART1_NVIC  (31)
#define UART2_NVIC  (50)
#define UART3_NVIC  (104)
// EOF IVT_TABLE

#ifdef __cplusplus
}
#endif

#endif // _MCU_DEFINITIONS_H_
// ------------------------------------------------------------------------- END
