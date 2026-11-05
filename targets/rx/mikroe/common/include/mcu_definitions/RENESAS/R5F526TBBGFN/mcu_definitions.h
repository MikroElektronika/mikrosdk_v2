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
#define __P100_CN
#define __P101_CN
#define __P200_CN
#define __P201_CN
#define __P202_CN
#define __P207_CN
#define __P300_CN
#define __P301_CN
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
#define __P500_CN
#define __P501_CN
#define __P502_CN
#define __P503_CN
#define __P504_CN
#define __P505_CN
#define __P600_CN
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
#define __PA03_CN
#define __PA05_CN
#define __PB00_CN
#define __PB01_CN
#define __PB02_CN
#define __PB03_CN
#define __PB04_CN
#define __PB05_CN
#define __PB06_CN
#define __PD02_CN
#define __PD03_CN
#define __PD04_CN
#define __PD05_CN
#define __PD06_CN
#define __PD07_CN
#define __PE02_CN
#define __PE03_CN
#define __PE04_CN
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
#define __PORT_A_CN
#define __PORT_B_CN
#define __PORT_D_CN
#define __PORT_E_CN
#define __PORT_N_CN

#define PORT_SIZE (8)
#define PORT_COUNT (14)
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
#define ADC1_P404_AN100
#endif
#ifdef __P405_CN
#define ADC1_P405_AN101
#endif
#ifdef __P406_CN
#define ADC1_P406_AN102
#endif
#ifdef __P407_CN
#define ADC1_P407_AN103
#endif
#ifdef __P500_CN
#define ADC2_P500_AN204
#endif
#ifdef __P501_CN
#define ADC2_P501_AN205
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
#ifdef __P505_CN
#define ADC2_P505_AN203
#endif
#ifdef __P600_CN
#define ADC2_P600_AN206
#endif
#ifdef __P604_CN
#define ADC2_P604_AN210
#endif
#ifdef __P605_CN
#define ADC2_P605_AN211
#endif

#define ADC_MODULE_0 1
#define ADC_MODULE_1 2
#define ADC_MODULE_2 3

#define ADC_MODULE_COUNT 3
//EOF ADC

//SCI
#ifdef __P000_CN
#define SCI12_MISO_P000_AF12
#define SCI12_RX_P000_AF12
#define SCI12_SCL_P000_AF12
#define SCI9_MISO_P000_AF44
#define SCI9_RX_P000_AF44
#define SCI9_SCL_P000_AF44
#endif
#ifdef __P001_CN
#define SCI12_MOSI_P001_AF12
#define SCI12_SDA_P001_AF12
#define SCI12_TX_P001_AF12
#define SCI9_MOSI_P001_AF44
#define SCI9_SDA_P001_AF44
#define SCI9_TX_P001_AF44
#endif
#ifdef __P100_CN
#define SCI9_MOSI_P100_AF44
#define SCI9_SDA_P100_AF44
#define SCI9_TX_P100_AF44
#endif
#ifdef __P101_CN
#define SCI8_SCK_P101_AF45
#define SCI9_SCK_P101_AF44
#endif
#ifdef __P200_CN
#define SCI8_MISO_P200_AF45
#define SCI8_RX_P200_AF45
#define SCI8_SCL_P200_AF45
#endif
#ifdef __P201_CN
#define SCI12_MOSI_P201_AF12
#define SCI12_SDA_P201_AF12
#define SCI12_TX_P201_AF12
#define SCI8_MOSI_P201_AF44
#define SCI8_SDA_P201_AF44
#define SCI8_TX_P201_AF44
#endif
#ifdef __P202_CN
#define SCI12_MISO_P202_AF12
#define SCI12_RX_P202_AF12
#define SCI12_SCL_P202_AF12
#define SCI8_MISO_P202_AF44
#define SCI8_RX_P202_AF44
#define SCI8_SCK_P202_AF45
#define SCI8_SCL_P202_AF44
#endif
#ifdef __P300_CN
#define SCI8_SCK_P300_AF44
#endif
#ifdef __P306_CN
#define SCI5_MOSI_P306_AF10
#define SCI5_SDA_P306_AF10
#define SCI5_TX_P306_AF10
#endif
#ifdef __P307_CN
#define SCI5_MISO_P307_AF10
#define SCI5_RX_P307_AF10
#define SCI5_SCL_P307_AF10
#endif
#ifdef __P700_CN
#define SCI5_SCK_P700_AF10
#endif
#ifdef __P900_CN
#define SCI5_MOSI_P900_AF10
#define SCI5_SDA_P900_AF10
#define SCI5_TX_P900_AF10
#endif
#ifdef __P901_CN
#define SCI5_MISO_P901_AF10
#define SCI5_RX_P901_AF10
#define SCI5_SCL_P901_AF10
#endif
#ifdef __P902_CN
#define SCI11_MOSI_P902_AF45
#define SCI11_SDA_P902_AF45
#define SCI11_TX_P902_AF45
#define SCI9_SCK_P902_AF44
#endif
#ifdef __P903_CN
#define SCI11_MISO_P903_AF45
#define SCI11_RX_P903_AF45
#define SCI11_SCL_P903_AF45
#define SCI9_MOSI_P903_AF44
#define SCI9_SDA_P903_AF44
#define SCI9_TX_P903_AF44
#endif
#ifdef __P904_CN
#define SCI8_SCK_P904_AF45
#define SCI9_MOSI_P904_AF44
#define SCI9_SDA_P904_AF44
#define SCI9_TX_P904_AF44
#endif
#ifdef __P905_CN
#define SCI6_MISO_P905_AF10
#define SCI6_RX_P905_AF10
#define SCI6_SCL_P905_AF10
#define SCI8_MISO_P905_AF45
#define SCI8_RX_P905_AF45
#define SCI8_SCL_P905_AF45
#endif
#ifdef __PA03_CN
#define SCI8_SCK_PA03_AF45
#define SCI9_MOSI_PA03_AF44
#define SCI9_SDA_PA03_AF44
#define SCI9_TX_PA03_AF44
#endif
#ifdef __PA05_CN
#define SCI6_MISO_PA05_AF10
#define SCI6_RX_PA05_AF10
#define SCI6_SCL_PA05_AF10
#define SCI8_MISO_PA05_AF45
#define SCI8_RX_PA05_AF45
#define SCI8_SCL_PA05_AF45
#endif
#ifdef __PB00_CN
#define SCI6_MOSI_PB00_AF10
#define SCI6_SDA_PB00_AF10
#define SCI6_TX_PB00_AF10
#define SCI8_MOSI_PB00_AF44
#define SCI8_SDA_PB00_AF44
#define SCI8_TX_PB00_AF44
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
#define SCI11_SCK_PB04_AF45
#define SCI12_MISO_PB04_AF12
#define SCI12_RX_PB04_AF12
#define SCI12_SCL_PB04_AF12
#endif
#ifdef __PB05_CN
#define SCI11_MOSI_PB05_AF45
#define SCI11_SDA_PB05_AF45
#define SCI11_TX_PB05_AF45
#define SCI12_MOSI_PB05_AF12
#define SCI12_SDA_PB05_AF12
#define SCI12_TX_PB05_AF12
#define SCI5_MOSI_PB05_AF10
#define SCI5_SDA_PB05_AF10
#define SCI5_TX_PB05_AF10
#endif
#ifdef __PB06_CN
#define SCI11_MISO_PB06_AF45
#define SCI11_RX_PB06_AF45
#define SCI11_SCL_PB06_AF45
#define SCI12_MISO_PB06_AF12
#define SCI12_RX_PB06_AF12
#define SCI12_SCL_PB06_AF12
#define SCI5_MISO_PB06_AF10
#define SCI5_RX_PB06_AF10
#define SCI5_SCL_PB06_AF10
#endif
#ifdef __PD02_CN
#define SCI5_SCK_PD02_AF10
#define SCI8_SCK_PD02_AF45
#endif
#ifdef __PD03_CN
#define SCI11_MOSI_PD03_AF45
#define SCI11_SDA_PD03_AF45
#define SCI11_TX_PD03_AF45
#define SCI1_MOSI_PD03_AF10
#define SCI1_SDA_PD03_AF10
#define SCI1_TX_PD03_AF10
#endif
#ifdef __PD04_CN
#define SCI11_SCK_PD04_AF45
#define SCI12_MOSI_PD04_AF12
#define SCI12_SDA_PD04_AF12
#define SCI12_TX_PD04_AF12
#define SCI1_SCK_PD04_AF10
#endif
#ifdef __PD05_CN
#define SCI11_MISO_PD05_AF45
#define SCI11_RX_PD05_AF45
#define SCI11_SCL_PD05_AF45
#define SCI1_MISO_PD05_AF10
#define SCI1_RX_PD05_AF10
#define SCI1_SCL_PD05_AF10
#endif
#ifdef __PD06_CN
#define SCI12_MISO_PD06_AF12
#define SCI12_RX_PD06_AF12
#define SCI12_SCL_PD06_AF12
#endif
#ifdef __PD07_CN
#define SCI5_MOSI_PD07_AF10
#define SCI5_SDA_PD07_AF10
#define SCI5_TX_PD07_AF10
#define SCI8_MOSI_PD07_AF45
#define SCI8_SDA_PD07_AF45
#define SCI8_TX_PD07_AF45
#define SCI9_SCK_PD07_AF44
#endif
#ifdef __PE04_CN
#define SCI9_SCK_PE04_AF44
#endif

#define SCI_MODULE_1 1
#define SCI_MODULE_5 2
#define SCI_MODULE_6 3
#define SCI_MODULE_8 4
#define SCI_MODULE_9 5
#define SCI_MODULE_11 6
#define SCI_MODULE_12 7

#define SCI_MODULE_COUNT 7
//EOF SCI

//I3C
#ifdef __PB01_CN
#define I3C0_SCL_PB01_AF50
#endif
#ifdef __PB02_CN
#define I3C0_SDA_PB02_AF50
#endif

#define I3C_MODULE_0 (SCI_MODULE_COUNT + 1)

#define I3C_MODULE_COUNT 1
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
#define SPI1_SCK_P200_AF14
#endif
#ifdef __P201_CN
#define SPI0_MOSI_P201_AF13
#define SPI1_MOSI_P201_AF14
#endif
#ifdef __P202_CN
#define SPI0_MISO_P202_AF13
#define SPI1_MISO_P202_AF14
#endif
#ifdef __P207_CN
#define SPI0_SCK_P207_AF13
#define SPI1_SCK_P207_AF14
#endif
#ifdef __P700_CN
#define SPI1_SCK_P700_AF14
#endif
#ifdef __P701_CN
#define SPI1_MISO_P701_AF14
#endif
#ifdef __P702_CN
#define SPI1_MOSI_P702_AF14
#endif
#ifdef __P901_CN
#define SPI1_SCK_P901_AF14
#endif
#ifdef __P902_CN
#define SPI1_MISO_P902_AF14
#endif
#ifdef __P903_CN
#define SPI1_MOSI_P903_AF14
#endif
#ifdef __P905_CN
#define SPI0_MISO_P905_AF13
#define SPI1_MISO_P905_AF51
#endif
#ifdef __P906_CN
#define SPI1_SCK_P906_AF51
#endif
#ifdef __PA05_CN
#define SPI0_MISO_PA05_AF13
#define SPI1_MISO_PA05_AF14
#endif
#ifdef __PB00_CN
#define SPI0_MOSI_PB00_AF13
#define SPI1_MOSI_PB00_AF14
#endif
#ifdef __PB03_CN
#define SPI0_SCK_PB03_AF13
#endif
#ifdef __PB04_CN
#define SPI0_MISO_PB04_AF13
#endif
#ifdef __PB05_CN
#define SPI1_SCK_PB05_AF14
#endif
#ifdef __PB06_CN
#define SPI1_MISO_PB06_AF14
#endif
#ifdef __PD02_CN
#define SPI0_MOSI_PD02_AF13
#define SPI1_MOSI_PD02_AF14
#endif
#ifdef __PD03_CN
#define SPI1_MOSI_PD03_AF14
#endif

#define SPI_MODULE_0 (SCI_MODULE_COUNT + 1)
#define SPI_MODULE_1 (SCI_MODULE_COUNT + 2)

#define SPI_MODULE_COUNT (SCI_MODULE_COUNT + 2)
//EOF SPI

//TIM
#ifdef __P100_CN
#define TIM3_P100_CHA_AF20
#endif
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
#ifdef __PD02_CN
#define TIM0_PD02_CHA_AF21
#define TIM2_PD02_CHB_AF20
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
#define SCI5_RXI_VECTOR                          (84)
#define SCI5_TXI_VECTOR                          (85)
#define SCI6_RXI_VECTOR                          (86)
#define SCI6_TXI_VECTOR                          (87)
#define SCI8_RXI_VECTOR                          (100)
#define SCI8_TXI_VECTOR                          (101)
#define SCI9_RXI_VECTOR                          (102)
#define SCI9_TXI_VECTOR                          (103)
#define SCI11_RXI_VECTOR                         (114)
#define SCI11_TXI_VECTOR                         (115)
#define SCI12_RXI_VECTOR                         (116)
#define SCI12_TXI_VECTOR                         (117)
#define ICU_GROUPBL0_VECTOR                      (110)
#define ICU_GROUPBL1_VECTOR                      (111)
#define ICU_GROUPAL0_VECTOR                      (112)
#define SCI1_ERI_GROUP_BIT                       (3)
#define SCI5_ERI_GROUP_BIT                       (11)
#define SCI6_ERI_GROUP_BIT                       (13)
#define SCI8_ERI_GROUP_BIT                       (25)
#define SCI9_ERI_GROUP_BIT                       (27)
#define SCI11_ERI_GROUP_BIT                      (13)
#define SCI12_ERI_GROUP_BIT                      (17)
//EOF IVT_TABLE

#endif // _MCU_DEFINITIONS_H_
// ------------------------------------------------------------------------- END
