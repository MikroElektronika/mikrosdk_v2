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
#define __P100_CN
#define __P101_CN
#define __P102_CN
#define __P103_CN
#define __P108_CN
#define __P109_CN
#define __P110_CN
#define __P200_CN
#define __P201_CN
#define __P300_CN
#define __P400_CN
#define __P401_CN

#define __PORT_1_CN
#define __PORT_2_CN
#define __PORT_3_CN
#define __PORT_4_CN

#define PORT_SIZE (16)
#define PORT_COUNT (4)
//EOF GPIO

//ADC
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

//SCI
#ifdef __P100_CN
#define SCI9_MISO_P100_AF4
#define SCI9_SCK_P100_AF5
#define SCI9_SCL_P100_AF4
#define SCI9_RX_P100_AF4
#endif
#ifdef __P101_CN
#define SCI9_MOSI_P101_AF4
#define SCI9_SDA_P101_AF4
#define SCI9_TX_P101_AF4
#endif
#ifdef __P102_CN
#define SCI9_SCK_P102_AF4
#define SCI9_MOSI_P102_AF5
#define SCI9_SDA_P102_AF5
#define SCI9_TX_P102_AF5
#endif
#ifdef __P103_CN
#define SCI9_MISO_P103_AF5
#define SCI9_SCL_P103_AF5
#define SCI9_RX_P103_AF5
#endif
#ifdef __P108_CN
#define SCI9_MOSI_P108_AF4
#define SCI9_SDA_P108_AF4
#define SCI9_TX_P108_AF4
#endif
#ifdef __P109_CN
#define SCI9_SCK_P109_AF4
#define SCI9_MOSI_P109_AF5
#define SCI9_SDA_P109_AF5
#define SCI9_TX_P109_AF5
#endif
#ifdef __P110_CN
#define SCI9_MISO_P110_AF5
#define SCI9_SCL_P110_AF5
#define SCI9_RX_P110_AF5
#endif
#ifdef __P300_CN
#define SCI9_MISO_P300_AF4
#define SCI9_SCK_P300_AF5
#define SCI9_SCL_P300_AF4
#define SCI9_RX_P300_AF4
#endif
#ifdef __P400_CN
#define SCI9_SCK_P400_AF4
#define SCI9_MOSI_P400_AF5
#define SCI9_SDA_P400_AF5
#define SCI9_TX_P400_AF5
#endif
#ifdef __P401_CN
#define SCI9_MISO_P401_AF5
#define SCI9_SCL_P401_AF5
#define SCI9_RX_P401_AF5
#endif

#define SCI_MODULE_9 10

#define SCI_MODULE_COUNT 1
//EOF SCI

//I3C
#ifdef __P400_CN
#define I3C0_SCL_P400_AF7
#endif
#ifdef __P401_CN
#define I3C0_SDA_P401_AF7
#endif

#define I3C_MODULE_0 11

#define I3C_MODULE_COUNT (1)
//EOF I3C

//I2C
#define I2C_MODULE_COUNT (SCI_MODULE_COUNT + I3C_MODULE_COUNT + 0)
//EOF I2C

//UART
#define UART_MODULE_COUNT (SCI_MODULE_COUNT + 0)
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
#ifdef __P108_CN
#define SPI0_MOSI_P108_AF6
#endif
#ifdef __P109_CN
#define SPI0_MISO_P109_AF6
#endif
#ifdef __P300_CN
#define SPI0_SCK_P300_AF6
#endif

#define SPI_MODULE_0 11

#define SPI_MODULE_COUNT (SCI_MODULE_COUNT + 1)
//EOF SPI

//TIM
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
#ifdef __P108_CN
#define TIM7_P108_CHB_AF3
#endif
#ifdef __P300_CN
#define TIM7_P300_CHA_AF3
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
#ifdef __P102_CN
#define AGT0_P102_CH_AF1
#endif
#ifdef __P103_CN
#define AGT0_P103_CHB_AF1
#endif
#ifdef __P110_CN
#define AGT0_P110_CHA_AF1
#endif
#ifdef __P108_CN
#define AGT1_P108_CHA_AF1
#endif
#ifdef __P109_CN
#define AGT1_P109_CH_AF1
#endif
#ifdef __P300_CN
#define AGT1_P300_CHB_AF1
#endif

#define TIM_MODULE_4 5
#define TIM_MODULE_5 6
#define TIM_MODULE_7 8
#define TIM_MODULE_8 9
#define TIM_MODULE_9 10
#define AGT_MODULE_0 11
#define AGT_MODULE_1 12

#define TIM_MODULE_COUNT 7
//EOF TIM

//IVT_TABLE
#define SCI0_RXI_EVENT 0x12
#define SCI0_RXI_NVIC 0
#define SCI0_TXI_EVENT 0x10
#define SCI0_TXI_NVIC 1
#define SCI0_ERI_EVENT 0x0F
#define SCI0_ERI_NVIC 3
#define SCI1_RXI_EVENT 0x1E
#define SCI1_RXI_NVIC 8
#define SCI1_TXI_EVENT 0x1B
#define SCI1_TXI_NVIC 9
#define SCI1_ERI_EVENT 0x19
#define SCI1_ERI_NVIC 11
#define SCI2_RXI_EVENT 0x1D
#define SCI2_RXI_NVIC 12
#define SCI2_TXI_EVENT 0x1B
#define SCI2_TXI_NVIC 13
#define SCI2_ERI_EVENT 0x19
#define SCI2_ERI_NVIC 15
#define SCI3_RXI_EVENT 0x1F
#define SCI3_RXI_NVIC 16
#define SCI3_TXI_EVENT 0x1D
#define SCI3_TXI_NVIC 17
#define SCI3_ERI_EVENT 0x1A
#define SCI3_ERI_NVIC 19
#define SCI9_RXI_EVENT 0x1E
#define SCI9_RXI_NVIC 28
#define SCI9_TXI_EVENT 0x1C
#define SCI9_TXI_NVIC 29
#define SCI9_ERI_EVENT 0x1A
#define SCI9_ERI_NVIC 31
#define UARTA0_TXI_EVENT 0x0D
#define UARTA0_TXI_NVIC 10
#define UARTA0_RXI_EVENT 0x10
#define UARTA0_RXI_NVIC 16
#define UARTA0_ERI_EVENT 0x0D
#define UARTA0_ERI_NVIC 7
#define UARTA1_TXI_EVENT 0x0F
#define UARTA1_TXI_NVIC 17
#define UARTA1_RXI_EVENT 0x1F
#define UARTA1_RXI_NVIC 18
#define UARTA1_ERI_EVENT 0x0E
#define UARTA1_ERI_NVIC 23
//EOF IVT_TABLE

#endif // _MCU_DEFINITIONS_H_
// ------------------------------------------------------------------------- END
