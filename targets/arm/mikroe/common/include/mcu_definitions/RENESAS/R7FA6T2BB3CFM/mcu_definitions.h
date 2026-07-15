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
#define __P201_CN
#define __P212_CN
#define __P213_CN
#define __PA00_CN
#define __PA01_CN
#define __PA02_CN
#define __PA03_CN
#define __PA04_CN
#define __PA05_CN
#define __PA06_CN
#define __PA07_CN
#define __PA08_CN
#define __PA09_CN
#define __PA10_CN
#define __PA11_CN
#define __PA12_CN
#define __PA13_CN
#define __PA14_CN
#define __PA15_CN
#define __PB00_CN
#define __PB01_CN
#define __PB02_CN
#define __PB03_CN
#define __PB04_CN
#define __PB05_CN
#define __PB06_CN
#define __PB07_CN
#define __PB08_CN
#define __PB09_CN
#define __PB12_CN
#define __PB13_CN
#define __PB14_CN
#define __PB15_CN
#define __PC00_CN
#define __PC01_CN
#define __PC02_CN
#define __PC03_CN
#define __PC04_CN
#define __PC05_CN
#define __PC06_CN
#define __PC07_CN
#define __PC08_CN
#define __PC09_CN
#define __PC10_CN
#define __PC11_CN
#define __PC12_CN
#define __PC13_CN
#define __PC14_CN
#define __PC15_CN
#define __PD02_CN

#define __PORT_0_CN
#define __PORT_2_CN
#define __PORT_A_CN
#define __PORT_B_CN
#define __PORT_C_CN
#define __PORT_D_CN

#define PORT_SIZE (16)
#define PORT_COUNT (6)
//EOF GPIO

//ADC
#ifdef __P002_CN
#define ADC0_P002_AN019
#endif
#ifdef __PA00_CN
#define ADC0_PA00_AN000
#endif
#ifdef __PA01_CN
#define ADC0_PA01_AN001
#endif
#ifdef __PA02_CN
#define ADC0_PA02_AN002
#endif
#ifdef __PA03_CN
#define ADC0_PA03_AN003
#endif
#ifdef __PA04_CN
#define ADC0_PA04_AN004
#endif
#ifdef __PA05_CN
#define ADC0_PA05_AN005
#endif
#ifdef __PA06_CN
#define ADC0_PA06_AN006
#endif
#ifdef __PA07_CN
#define ADC0_PA07_AN007
#endif
#ifdef __PB00_CN
#define ADC0_PB00_AN008
#endif
#ifdef __PB01_CN
#define ADC0_PB01_AN009
#endif
#ifdef __PB02_CN
#define ADC0_PB02_AN018
#endif
#ifdef __PC00_CN
#define ADC0_PC00_AN012
#endif
#ifdef __PC01_CN
#define ADC0_PC01_AN013
#endif
#ifdef __PC02_CN
#define ADC0_PC02_AN014
#endif
#ifdef __PC03_CN
#define ADC0_PC03_AN015
#endif
#ifdef __PC04_CN
#define ADC0_PC04_AN010
#endif
#ifdef __PC05_CN
#define ADC0_PC05_AN011
#endif

#define ADC_MODULE_0 1

#define ADC_MODULE_COUNT 1
//EOF ADC

//SCI
#ifdef __PA08_CN
#define SCI0_SCK_PA08_AF4
#define SCI1_SCK_PA08_AF5
#endif
#ifdef __PA09_CN
#define SCI0_MOSI_PA09_AF4
#define SCI0_SDA_PA09_AF4
#define SCI0_TX_PA09_AF4
#endif
#ifdef __PA10_CN
#define SCI0_MISO_PA10_AF4
#define SCI0_SCL_PA10_AF4
#define SCI0_RX_PA10_AF4
#endif
#ifdef __PA13_CN
#define SCI0_SCK_PA13_AF4
#endif
#ifdef __PA14_CN
#define SCI0_MOSI_PA14_AF4
#define SCI9_SCK_PA14_AF5
#define SCI0_SDA_PA14_AF4
#define SCI0_TX_PA14_AF4
#endif
#ifdef __PA15_CN
#define SCI0_MISO_PA15_AF4
#define SCI9_MISO_PA15_AF5
#define SCI0_SCL_PA15_AF4
#define SCI9_SCL_PA15_AF5
#define SCI0_RX_PA15_AF4
#define SCI9_RX_PA15_AF5
#endif
#ifdef __PB06_CN
#define SCI0_MOSI_PB06_AF4
#define SCI0_SDA_PB06_AF4
#define SCI0_TX_PB06_AF4
#endif
#ifdef __PB07_CN
#define SCI0_MISO_PB07_AF4
#define SCI0_SCL_PB07_AF4
#define SCI0_RX_PB07_AF4
#endif
#ifdef __PA11_CN
#define SCI1_MISO_PA11_AF5
#define SCI1_SCL_PA11_AF5
#define SCI1_RX_PA11_AF5
#endif
#ifdef __PA12_CN
#define SCI1_MOSI_PA12_AF5
#define SCI1_SDA_PA12_AF5
#define SCI1_TX_PA12_AF5
#endif
#ifdef __PB08_CN
#define SCI1_MISO_PB08_AF5
#define SCI4_MISO_PB08_AF4
#define SCI1_SCL_PB08_AF5
#define SCI4_SCL_PB08_AF4
#define SCI1_RX_PB08_AF5
#define SCI4_RX_PB08_AF4
#endif
#ifdef __PB09_CN
#define SCI1_MOSI_PB09_AF5
#define SCI4_MOSI_PB09_AF4
#define SCI1_SDA_PB09_AF5
#define SCI4_SDA_PB09_AF4
#define SCI1_TX_PB09_AF5
#define SCI4_TX_PB09_AF4
#endif
#ifdef __PC10_CN
#define SCI1_MOSI_PC10_AF5
#define SCI1_SDA_PC10_AF5
#define SCI1_TX_PC10_AF5
#endif
#ifdef __PC11_CN
#define SCI1_MISO_PC11_AF5
#define SCI1_SCL_PC11_AF5
#define SCI1_RX_PC11_AF5
#endif
#ifdef __PC12_CN
#define SCI1_SCK_PC12_AF5
#define SCI4_MOSI_PC12_AF4
#define SCI4_SDA_PC12_AF4
#define SCI4_TX_PC12_AF4
#endif
#ifdef __PB03_CN
#define SCI2_MOSI_PB03_AF4
#define SCI9_MOSI_PB03_AF5
#define SCI2_SDA_PB03_AF4
#define SCI9_SDA_PB03_AF5
#define SCI2_TX_PB03_AF4
#define SCI9_TX_PB03_AF5
#endif
#ifdef __PB04_CN
#define SCI2_MISO_PB04_AF4
#define SCI3_MISO_PB04_AF5
#define SCI2_SCL_PB04_AF4
#define SCI3_SCL_PB04_AF5
#define SCI2_RX_PB04_AF4
#define SCI3_RX_PB04_AF5
#endif
#ifdef __PB05_CN
#define SCI2_SCK_PB05_AF4
#define SCI3_MOSI_PB05_AF5
#define SCI3_SDA_PB05_AF5
#define SCI3_TX_PB05_AF5
#endif
#ifdef __PC06_CN
#define SCI2_MOSI_PC06_AF4
#define SCI2_SDA_PC06_AF4
#define SCI2_TX_PC06_AF4
#endif
#ifdef __PC07_CN
#define SCI2_MISO_PC07_AF4
#define SCI2_SCL_PC07_AF4
#define SCI2_RX_PC07_AF4
#endif
#ifdef __PC08_CN
#define SCI2_SCK_PC08_AF4
#endif
#ifdef __PB12_CN
#define SCI3_MISO_PB12_AF5
#define SCI4_SCK_PB12_AF4
#define SCI3_SCL_PB12_AF5
#define SCI3_RX_PB12_AF5
#endif
#ifdef __PB13_CN
#define SCI3_MOSI_PB13_AF5
#define SCI3_SDA_PB13_AF5
#define SCI3_TX_PB13_AF5
#endif
#ifdef __PB14_CN
#define SCI3_SCK_PB14_AF5
#endif
#ifdef __PD02_CN
#define SCI3_SCK_PD02_AF5
#define SCI4_MISO_PD02_AF4
#define SCI4_SCL_PD02_AF4
#define SCI4_RX_PD02_AF4
#endif
#ifdef __PB15_CN
#define SCI4_MISO_PB15_AF4
#define SCI4_SCL_PB15_AF4
#define SCI4_RX_PB15_AF4
#endif

#define SCI_MODULE_0 1
#define SCI_MODULE_1 2
#define SCI_MODULE_2 3
#define SCI_MODULE_3 4
#define SCI_MODULE_4 5
#define SCI_MODULE_9 10

#define SCI_MODULE_COUNT 6
//EOF SCI

//I3C
#define I3C_MODULE_COUNT (0)
//EOF I3C

//I2C
#ifdef __PA08_CN
#define I2C0_SCL_PA08_AF7
#endif
#ifdef __PB06_CN
#define I2C0_SCL_PB06_AF7
#endif
#ifdef __PB07_CN
#define I2C0_SDA_PB07_AF7
#endif
#ifdef __PB14_CN
#define I2C0_SDA_PB14_AF7
#endif
#ifdef __PB15_CN
#define I2C0_SCL_PB15_AF7
#endif
#ifdef __PC08_CN
#define I2C0_SCL_PC08_AF7
#endif
#ifdef __PC09_CN
#define I2C0_SDA_PC09_AF7
#endif
#ifdef __PC10_CN
#define I2C0_SCL_PC10_AF7
#endif
#ifdef __PC11_CN
#define I2C0_SDA_PC11_AF7
#endif
#ifdef __PA09_CN
#define I2C1_SCL_PA09_AF7
#endif
#ifdef __PA10_CN
#define I2C1_SDA_PA10_AF7
#endif
#ifdef __PB08_CN
#define I2C1_SCL_PB08_AF7
#endif
#ifdef __PB09_CN
#define I2C1_SDA_PB09_AF7
#endif
#ifdef __PC06_CN
#define I2C1_SCL_PC06_AF7
#endif
#ifdef __PC07_CN
#define I2C1_SDA_PC07_AF7
#endif

#define I2C_MODULE_0 11
#define I2C_MODULE_1 12

#define I2C_MODULE_COUNT (SCI_MODULE_COUNT + I3C_MODULE_COUNT + 2)
//EOF I2C

//UART
#define UART_MODULE_COUNT (SCI_MODULE_COUNT + 0)
//EOF UART

//SPI
#ifdef __PA10_CN
#define SPI0_SCK_PA10_AF6
#endif
#ifdef __PA11_CN
#define SPI0_MOSI_PA11_AF6
#endif
#ifdef __PA12_CN
#define SPI0_MISO_PA12_AF6
#endif
#ifdef __PB03_CN
#define SPI0_SCK_PB03_AF6
#endif
#ifdef __PB04_CN
#define SPI0_MISO_PB04_AF6
#endif
#ifdef __PB05_CN
#define SPI0_MOSI_PB05_AF6
#endif
#ifdef __PB13_CN
#define SPI1_SCK_PB13_AF6
#endif
#ifdef __PB14_CN
#define SPI1_MISO_PB14_AF6
#endif
#ifdef __PB15_CN
#define SPI1_MOSI_PB15_AF6
#endif
#ifdef __PC10_CN
#define SPI1_SCK_PC10_AF6
#endif
#ifdef __PC11_CN
#define SPI1_MISO_PC11_AF6
#endif
#ifdef __PC12_CN
#define SPI1_MOSI_PC12_AF6
#endif

#define SPI_MODULE_0 11
#define SPI_MODULE_1 12

#define SPI_MODULE_COUNT (SCI_MODULE_COUNT + 2)
//EOF SPI

//TIM
#ifdef __PB04_CN
#define TIM0_PB04_CHA_AF3
#define TIM4_PB04_CHA_AF3
#define TIM5_PB04_CHA_AF3
#endif
#ifdef __PB05_CN
#define TIM0_PB05_CHB_AF3
#define TIM4_PB05_CHB_AF3
#define TIM6_PB05_CHA_AF3
#endif
#ifdef __PB12_CN
#define TIM0_PB12_CHA_AF3
#define TIM4_PB12_CHA_AF3
#endif
#ifdef __PB13_CN
#define TIM0_PB13_CHB_AF3
#define TIM5_PB13_CHA_AF3
#define TIM7_PB13_CHA_AF3
#endif
#ifdef __PB06_CN
#define TIM1_PB06_CHA_AF3
#define TIM4_PB06_CHB_AF3
#define TIM5_PB06_CHA_AF3
#endif
#ifdef __PB07_CN
#define TIM1_PB07_CHB_AF3
#define TIM5_PB07_CHB_AF3
#endif
#ifdef __PB14_CN
#define TIM1_PB14_CHA_AF3
#define TIM6_PB14_CHA_AF3
#define TIM8_PB14_CHA_AF3
#endif
#ifdef __PB15_CN
#define TIM1_PB15_CHB_AF3
#define TIM4_PB15_CHB_AF3
#define TIM9_PB15_CHA_AF3
#endif
#ifdef __PA08_CN
#define TIM2_PA08_CHA_AF3
#define TIM7_PA08_CHB_AF3
#define TIM8_PA08_CHA_AF3
#define TIM9_PA08_CHA_AF3
#endif
#ifdef __PA09_CN
#define TIM2_PA09_CHB_AF3
#define TIM7_PA09_CHB_AF3
#endif
#ifdef __PB08_CN
#define TIM2_PB08_CHA_AF3
#define TIM5_PB08_CHB_AF3
#define TIM6_PB08_CHA_AF3
#endif
#ifdef __PB09_CN
#define TIM2_PB09_CHB_AF3
#define TIM6_PB09_CHB_AF3
#endif
#ifdef __PA10_CN
#define TIM3_PA10_CHA_AF3
#define TIM8_PA10_CHB_AF3
#define TIM9_PA10_CHA_AF3
#define TIM9_PA10_CHB_AF3
#endif
#ifdef __PA11_CN
#define TIM3_PA11_CHB_AF3
#define TIM9_PA11_CHB_AF3
#endif
#ifdef __PC14_CN
#define TIM3_PC14_CHA_AF3
#endif
#ifdef __PC15_CN
#define TIM3_PC15_CHB_AF3
#endif
#ifdef __PB03_CN
#define TIM4_PB03_CHA_AF3
#endif
#ifdef __PC06_CN
#define TIM5_PC06_CHB_AF3
#define TIM6_PC06_CHA_AF3
#endif
#ifdef __PC07_CN
#define TIM6_PC07_CHB_AF3
#endif
#ifdef __PC08_CN
#define TIM7_PC08_CHA_AF3
#endif
#ifdef __PC09_CN
#define TIM7_PC09_CHB_AF3
#define TIM8_PC09_CHA_AF3
#endif
#ifdef __PA09 (A)_CN
#define TIM8_PA09 (A)_CHB_AF3
#endif
#ifdef __PA09 (C)_CN
#define TIM8_PA09 (C)_CHB_AF3
#endif
#ifdef __PA13_CN
#define AGT0_PA13_CH_AF1
#endif
#ifdef __PB04_CN
#define AGT0_PB04_CHA_AF1
#endif
#ifdef __PB05_CN
#define AGT0_PB05_CHB_AF1
#endif
#ifdef __PC06_CN
#define AGT0_PC06_CH_AF1
#endif
#ifdef __PC08_CN
#define AGT0_PC08_CHA_AF1
#endif
#ifdef __PC09_CN
#define AGT0_PC09_CHB_AF1
#endif
#ifdef __PA14_CN
#define AGT1_PA14_CH_AF1
#endif
#ifdef __PB03_CN
#define AGT1_PB03_CH_AF1
#endif
#ifdef __PB06_CN
#define AGT1_PB06_CHA_AF1
#endif
#ifdef __PB07_CN
#define AGT1_PB07_CHB_AF1
#endif
#ifdef __PC11_CN
#define AGT1_PC11_CHA_AF1
#endif
#ifdef __PC12_CN
#define AGT1_PC12_CHB_AF1
#endif

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
#define AGT_MODULE_0 11
#define AGT_MODULE_1 12

#define TIM_MODULE_COUNT 12
//EOF TIM

//IVT_TABLE
#define SCI0_ERI_EVENT 0x190
#define SCI0_ERI_NVIC 2
#define SCI0_RXI_EVENT 0x18D
#define SCI0_RXI_NVIC 1
#define SCI0_TXI_EVENT 0x18E
#define SCI0_TXI_NVIC 0
#define SCI1_ERI_EVENT 0x198
#define SCI1_ERI_NVIC 5
#define SCI1_RXI_EVENT 0x195
#define SCI1_RXI_NVIC 4
#define SCI1_TXI_EVENT 0x196
#define SCI1_TXI_NVIC 3
#define SCI2_ERI_EVENT 0x19F
#define SCI2_ERI_NVIC 8
#define SCI2_RXI_EVENT 0x19C
#define SCI2_RXI_NVIC 7
#define SCI2_TXI_EVENT 0x19D
#define SCI2_TXI_NVIC 6
#define SCI3_ERI_EVENT 0x1A6
#define SCI3_ERI_NVIC 11
#define SCI3_RXI_EVENT 0x1A3
#define SCI3_RXI_NVIC 10
#define SCI3_TXI_EVENT 0x1A4
#define SCI3_TXI_NVIC 9
#define SCI4_ERI_EVENT 0x1AD
#define SCI4_ERI_NVIC 14
#define SCI4_RXI_EVENT 0x1AA
#define SCI4_RXI_NVIC 13
#define SCI4_TXI_EVENT 0x1AB
#define SCI4_TXI_NVIC 12
#define SCI9_ERI_EVENT 0x1B4
#define SCI9_ERI_NVIC 29
#define SCI9_RXI_EVENT 0x1B1
#define SCI9_RXI_NVIC 28
#define SCI9_TXI_EVENT 0x1B2
#define SCI9_TXI_NVIC 27
//EOF IVT_TABLE

#endif // _MCU_DEFINITIONS_H_
// ------------------------------------------------------------------------- END
