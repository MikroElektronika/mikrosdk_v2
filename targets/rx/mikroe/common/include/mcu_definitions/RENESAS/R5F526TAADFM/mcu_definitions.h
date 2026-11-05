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
#define __P101_CN
#define __P200_CN
#define __P201_CN
#define __P202_CN
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
#define __P502_CN
#define __P503_CN
#define __P504_CN
#define __P604_CN
#define __P605_CN
#define __P700_CN
#define __P701_CN
#define __P702_CN
#define __P703_CN
#define __P704_CN
#define __P705_CN
#define __P706_CN
#define __P900_CN
#define __P901_CN
#define __P902_CN
#define __P903_CN
#define __P904_CN
#define __P905_CN
#define __P906_CN
#define __PB00_CN
#define __PB01_CN
#define __PB02_CN
#define __PB03_CN
#define __PB04_CN
#define __PB05_CN
#define __PB06_CN
#define __PD03_CN
#define __PD04_CN
#define __PD05_CN
#define __PD06_CN
#define __PD07_CN
#define __PE02_CN
#define __PN06_CN
#define __PN07_CN

#define __PORT_0_CN
#define __PORT_1_CN
#define __PORT_2_CN
#define __PORT_3_CN
#define __PORT_4_CN
#define __PORT_5_CN
#define __PORT_6_CN
#define __PORT_7_CN
#define __PORT_9_CN
#define __PORT_B_CN
#define __PORT_D_CN
#define __PORT_E_CN
#define __PORT_N_CN

#define PORT_SIZE (8)
#define PORT_COUNT (13)
//EOF GPIO

//ADC
#ifdef __P200_CN
#define ADC2_P200_AN216
#endif
#ifdef __P201_CN
#define ADC2_P201_AN217
#endif
#ifdef __P400_CN
#define ADC0_P400_AN000
#endif
#ifdef __P401_CN
#define ADC0_P401_AN001
#endif
#ifdef __P402_CN
#define ADC0_P402_AN002
#endif
#ifdef __P403_CN
#define ADC0_P403_AN003
#endif
#ifdef __P404_CN
#define ADC0_P404_AN004
#endif
#ifdef __P405_CN
#define ADC0_P405_AN005
#endif
#ifdef __P406_CN
#define ADC0_P406_AN006
#endif
#ifdef __P407_CN
#define ADC2_P407_AN206
#endif
#ifdef __P502_CN
#define ADC2_P502_AN200
#endif
#ifdef __P503_CN
#define ADC2_P503_AN201
#endif
#ifdef __P504_CN
#define ADC2_P504_AN202
#endif
#ifdef __P604_CN
#define ADC2_P604_AN210
#endif
#ifdef __P605_CN
#define ADC2_P605_AN211
#endif

#define ADC_MODULE_0 1
#define ADC_MODULE_2 2

#define ADC_MODULE_COUNT 2
//EOF ADC

//SCI
#ifdef __P000_CN
#define SCI12_MISO_P000_AF12
#define SCI12_RX_P000_AF12
#define SCI12_SCL_P000_AF12
#endif
#ifdef __P001_CN
#define SCI12_MOSI_P001_AF12
#define SCI12_SDA_P001_AF12
#define SCI12_TX_P001_AF12
#endif
#ifdef __P201_CN
#define SCI12_MOSI_P201_AF12
#define SCI12_SDA_P201_AF12
#define SCI12_TX_P201_AF12
#endif
#ifdef __P202_CN
#define SCI12_MISO_P202_AF12
#define SCI12_RX_P202_AF12
#define SCI12_SCL_P202_AF12
#endif
#ifdef __P905_CN
#define SCI6_MISO_P905_AF10
#define SCI6_RX_P905_AF10
#define SCI6_SCL_P905_AF10
#endif
#ifdef __PB00_CN
#define SCI6_MOSI_PB00_AF10
#define SCI6_SDA_PB00_AF10
#define SCI6_TX_PB00_AF10
#endif
#ifdef __PB01_CN
#define SCI6_MISO_PB01_AF10
#define SCI6_RX_PB01_AF10
#define SCI6_SCL_PB01_AF10
#endif
#ifdef __PB02_CN
#define SCI6_MOSI_PB02_AF10
#define SCI6_SDA_PB02_AF10
#define SCI6_TX_PB02_AF10
#endif
#ifdef __PB03_CN
#define SCI12_MOSI_PB03_AF12
#define SCI12_SDA_PB03_AF12
#define SCI12_TX_PB03_AF12
#define SCI6_SCK_PB03_AF10
#endif
#ifdef __PB04_CN
#define SCI12_MISO_PB04_AF12
#define SCI12_RX_PB04_AF12
#define SCI12_SCL_PB04_AF12
#endif
#ifdef __PB05_CN
#define SCI12_MOSI_PB05_AF12
#define SCI12_SDA_PB05_AF12
#define SCI12_TX_PB05_AF12
#endif
#ifdef __PB06_CN
#define SCI12_MISO_PB06_AF12
#define SCI12_RX_PB06_AF12
#define SCI12_SCL_PB06_AF12
#endif
#ifdef __PD03_CN
#define SCI1_MOSI_PD03_AF10
#define SCI1_SDA_PD03_AF10
#define SCI1_TX_PD03_AF10
#endif
#ifdef __PD04_CN
#define SCI12_MOSI_PD04_AF12
#define SCI12_SDA_PD04_AF12
#define SCI12_TX_PD04_AF12
#define SCI1_SCK_PD04_AF10
#endif
#ifdef __PD05_CN
#define SCI1_MISO_PD05_AF10
#define SCI1_RX_PD05_AF10
#define SCI1_SCL_PD05_AF10
#endif
#ifdef __PD06_CN
#define SCI12_MISO_PD06_AF12
#define SCI12_RX_PD06_AF12
#define SCI12_SCL_PD06_AF12
#endif

#define SCI_MODULE_1 1
#define SCI_MODULE_6 2
#define SCI_MODULE_12 3

#define SCI_MODULE_COUNT 3
//EOF SCI

//I3C
#define I3C_MODULE_COUNT 0
//EOF I3C

//I2C
#ifdef __PB01_CN
#define I2C0_SCL_PB01_AF15
#endif
#ifdef __PB02_CN
#define I2C0_SDA_PB02_AF15
#endif

#define I2C_MODULE_0 (SCI_MODULE_COUNT + I3C_MODULE_COUNT + 1)

#define I2C_MODULE_COUNT (SCI_MODULE_COUNT + I3C_MODULE_COUNT + 1)
//EOF I2C

//UART
#define UART_MODULE_COUNT (SCI_MODULE_COUNT + 0)
//EOF UART

//SPI
#ifdef __P200_CN
#define SPI0_SCK_P200_AF13
#endif
#ifdef __P201_CN
#define SPI0_MOSI_P201_AF13
#endif
#ifdef __P202_CN
#define SPI0_MISO_P202_AF13
#endif
#ifdef __P905_CN
#define SPI0_MISO_P905_AF13
#endif
#ifdef __PB00_CN
#define SPI0_MOSI_PB00_AF13
#endif
#ifdef __PB03_CN
#define SPI0_SCK_PB03_AF13
#endif
#ifdef __PB04_CN
#define SPI0_MISO_PB04_AF13
#endif

#define SPI_MODULE_0 (SCI_MODULE_COUNT + 1)

#define SPI_MODULE_COUNT (SCI_MODULE_COUNT + 1)
//EOF SPI

//TIM
#ifdef __P101_CN
#define TIM3_P101_CHB_AF20
#endif
#ifdef __P701_CN
#define TIM0_P701_CHA_AF20
#define TIM4_P701_CHA_AF21
#endif
#ifdef __P702_CN
#define TIM1_P702_CHA_AF20
#define TIM5_P702_CHA_AF21
#endif
#ifdef __P703_CN
#define TIM2_P703_CHA_AF20
#define TIM6_P703_CHA_AF21
#endif
#ifdef __P704_CN
#define TIM0_P704_CHB_AF20
#define TIM4_P704_CHB_AF21
#endif
#ifdef __P705_CN
#define TIM1_P705_CHB_AF20
#define TIM5_P705_CHB_AF21
#endif
#ifdef __P706_CN
#define TIM2_P706_CHB_AF20
#define TIM6_P706_CHB_AF21
#endif
#ifdef __P900_CN
#define TIM6_P900_CHB_AF20
#endif
#ifdef __P901_CN
#define TIM5_P901_CHB_AF20
#endif
#ifdef __P902_CN
#define TIM4_P902_CHB_AF20
#define TIM7_P902_CHB_AF21
#endif
#ifdef __P903_CN
#define TIM6_P903_CHA_AF20
#endif
#ifdef __P904_CN
#define TIM5_P904_CHA_AF20
#endif
#ifdef __P905_CN
#define TIM4_P905_CHA_AF20
#define TIM7_P905_CHA_AF21
#endif
#ifdef __PB01_CN
#define TIM7_PB01_CHB_AF21
#endif
#ifdef __PB02_CN
#define TIM7_PB02_CHA_AF21
#endif
#ifdef __PB05_CN
#define TIM2_PB05_CHB_AF20
#define TIM3_PB05_CHB_AF21
#endif
#ifdef __PB06_CN
#define TIM2_PB06_CHA_AF20
#define TIM3_PB06_CHA_AF21
#endif
#ifdef __PD03_CN
#define TIM2_PD03_CHA_AF20
#define TIM7_PD03_CHB_AF23
#endif
#ifdef __PD04_CN
#define TIM1_PD04_CHB_AF20
#endif
#ifdef __PD05_CN
#define TIM1_PD05_CHA_AF20
#define TIM7_PD05_CHA_AF23
#endif
#ifdef __PD06_CN
#define TIM0_PD06_CHB_AF20
#define TIM3_PD06_CHB_AF21
#endif
#ifdef __PD07_CN
#define TIM0_PD07_CHA_AF20
#define TIM3_PD07_CHA_AF21
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
#define SCI1_RXI_VECTOR                          (60)
#define SCI1_TXI_VECTOR                          (61)
#define SCI6_RXI_VECTOR                          (86)
#define SCI6_TXI_VECTOR                          (87)
#define SCI12_RXI_VECTOR                         (116)
#define SCI12_TXI_VECTOR                         (117)
#define ICU_GROUPBL0_VECTOR                      (110)
#define ICU_GROUPBL1_VECTOR                      (111)
#define ICU_GROUPAL0_VECTOR                      (112)
#define SCI1_ERI_GROUP_BIT                       (3)
#define SCI6_ERI_GROUP_BIT                       (13)
#define SCI12_ERI_GROUP_BIT                      (17)
//EOF IVT_TABLE

#endif // _MCU_DEFINITIONS_H_
// ------------------------------------------------------------------------- END
