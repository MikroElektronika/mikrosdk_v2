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
#define __P003_CN
#define __P004_CN
#define __P005_CN
#define __P006_CN
#define __P007_CN
#define __P008_CN
#define __P009_CN
#define __P010_CN
#define __P011_CN
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
#define __P509_CN
#define __P510_CN
#define __P511_CN
#define __P512_CN
#define __P513_CN
#define __P514_CN
#define __P515_CN
#define __P600_CN
#define __P601_CN
#define __P602_CN
#define __P603_CN
#define __P604_CN
#define __P605_CN
#define __P606_CN
#define __P607_CN
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
#define __P709_CN
#define __P710_CN
#define __P711_CN
#define __P712_CN
#define __P713_CN
#define __P714_CN
#define __P715_CN
#define __P800_CN
#define __P801_CN
#define __P802_CN
#define __P803_CN
#define __P804_CN
#define __P805_CN
#define __P806_CN
#define __P807_CN
#define __P808_CN
#define __P809_CN
#define __P810_CN
#define __P811_CN
#define __P812_CN
#define __P813_CN
#define __P814_CN
#define __P815_CN
#define __P900_CN
#define __P901_CN
#define __P902_CN
#define __P903_CN
#define __P904_CN
#define __P905_CN
#define __P906_CN
#define __P907_CN
#define __P908_CN
#define __P909_CN
#define __P910_CN
#define __P911_CN
#define __P912_CN
#define __P913_CN
#define __P914_CN
#define __P915_CN
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
#define __PORT_A_CN
#define __PORT_B_CN

#define PORT_SIZE (16)
#define PORT_COUNT (12)
//EOF GPIO

//ADC
#ifdef __P004_CN
#define ADC0_P004_AN000
#endif
#ifdef __P005_CN
#define ADC0_P005_AN001
#endif
#ifdef __P006_CN
#define ADC0_P006_AN002
#endif
#ifdef __P007_CN
#define ADC0_P007_AN004
#endif
#ifdef __P008_CN
#define ADC0_P008_AN008
#endif
#ifdef __P009_CN
#define ADC0_P009_AN006
#endif
#ifdef __P010_CN
#define ADC0_P010_AN005
#endif
#ifdef __P014_CN
#define ADC0_P014_AN007
#endif
#ifdef __P502_CN
#define ADC0_P502_AN019
#endif
#ifdef __P513_CN
#define ADC0_P513_AN016
#endif
#ifdef __P805_CN
#define ADC0_P805_AN017
#endif
#ifdef __P806_CN
#define ADC0_P806_AN018
#endif
#ifdef __P000_CN
#define ADC1_P000_AN100
#endif
#ifdef __P001_CN
#define ADC1_P001_AN101
#endif
#ifdef __P002_CN
#define ADC1_P002_AN102
#endif
#ifdef __P003_CN
#define ADC1_P003_AN104
#endif
#ifdef __P011_CN
#define ADC1_P011_AN106
#endif
#ifdef __P015_CN
#define ADC1_P015_AN105
#endif
#ifdef __P500_CN
#define ADC1_P500_AN121
#endif
#ifdef __P501_CN
#define ADC1_P501_AN120
#endif
#ifdef __P502_CN
#define ADC1_P502_AN119
#endif
#ifdef __P513_CN
#define ADC1_P513_AN116
#endif
#ifdef __P805_CN
#define ADC1_P805_AN117
#endif
#ifdef __P806_CN
#define ADC1_P806_AN118
#endif
#ifdef __P812_CN
#define ADC1_P812_AN122
#endif

#define ADC_MODULE_0 1
#define ADC_MODULE_1 2

#define ADC_MODULE_COUNT 2
//EOF ADC

//I2C
#ifdef __P407_CN
#define I2C0_SDA_P407_AF7
#endif
#ifdef __P408_CN
#define I2C0_SCL_P408_AF7
#endif
#ifdef __P409_CN
#define I2C0_SDA_P409_AF7
#endif
#ifdef __P410_CN
#define I2C0_SCL_P410_AF7
#endif
#ifdef __P205_CN
#define I2C1_SCL_P205_AF7
#endif
#ifdef __P206_CN
#define I2C1_SDA_P206_AF7
#endif
#ifdef __P511_CN
#define I2C1_SDA_P511_AF7
#endif
#ifdef __P512_CN
#define I2C1_SCL_P512_AF7
#endif
#ifdef __P401_CN
#define I2C1_SDA_P401_AF5
#endif
#ifdef __P400_CN
#define I2C1_SCL_P400_AF5
#endif

#define I2C_MODULE_0 1
#define I2C_MODULE_1 2

#define I2C_MODULE_COUNT 2
//EOF I2C

//UART
#ifdef __P112_CN
#define UART0_TX_P112_AF4
#endif
#ifdef __P113_CN
#define UART0_RX_P113_AF4
#endif
#ifdef __P602_CN
#define UART0_RX_P602_AF4
#endif
#ifdef __P603_CN
#define UART0_TX_P603_AF4
#endif
#ifdef __P609_CN
#define UART0_TX_P609_AF4
#endif
#ifdef __P610_CN
#define UART0_RX_P610_AF4
#endif
#ifdef __P212_CN
#define UART1_RX_P212_AF5
#endif
#ifdef __P213_CN
#define UART1_TX_P213_AF5
#endif
#ifdef __P400_CN
#define UART1_TX_P400_AF5
#endif
#ifdef __P401_CN
#define UART1_RX_P401_AF5
#endif
#ifdef __P706_CN
#define UART1_RX_P706_AF5
#endif
#ifdef __P707_CN
#define UART1_TX_P707_AF5
#endif
#ifdef __P406_CN
#define UART2_TX_P406_AF4
#endif
#ifdef __P700_CN
#define UART2_RX_P700_AF4
#endif
#ifdef __P801_CN
#define UART2_TX_P801_AF4
#endif
#ifdef __P802_CN
#define UART2_RX_P802_AF4
#endif
#ifdef __PA02_CN
#define UART2_RX_PA02_AF4
#endif
#ifdef __PA03_CN
#define UART2_TX_PA03_AF4
#endif
#ifdef __P309_CN
#define UART3_RX_P309_AF5
#endif
#ifdef __P310_CN
#define UART3_TX_P310_AF5
#endif
#ifdef __P408_CN
#define UART3_RX_P408_AF5
#endif
#ifdef __P409_CN
#define UART3_TX_P409_AF5
#endif
#ifdef __P900_CN
#define UART3_TX_P900_AF5
#endif
#ifdef __P901_CN
#define UART3_RX_P901_AF5
#endif
#ifdef __P205_CN
#define UART4_TX_P205_AF4
#endif
#ifdef __P206_CN
#define UART4_RX_P206_AF4
#endif
#ifdef __P414_CN
#define UART4_RX_P414_AF4
#endif
#ifdef __P415_CN
#define UART4_TX_P415_AF4
#endif
#ifdef __P714_CN
#define UART4_TX_P714_AF4
#endif
#ifdef __P715_CN
#define UART4_RX_P715_AF4
#endif
#ifdef __P101_CN
#define UART9_RX_P101_AF5
#endif
#ifdef __P102_CN
#define UART9_TX_P102_AF5
#endif
#ifdef __P208_CN
#define UART9_RX_P208_AF5
#endif
#ifdef __P209_CN
#define UART9_TX_P209_AF5
#endif
#ifdef __PA14_CN
#define UART9_TX_PA14_AF5
#endif
#ifdef __PA15_CN
#define UART9_RX_PA15_AF5
#endif

#define UART_MODULE_0 1
#define UART_MODULE_1 2
#define UART_MODULE_2 3
#define UART_MODULE_3 4
#define UART_MODULE_4 5
#define UART_MODULE_9 6

#define UART_MODULE_COUNT 6
//EOF UART

//SPI
#ifdef __P115_CN
#define SPI0_MOSI_P115_AF6
#endif
#ifdef __P202_CN
#define SPI0_MOSI_P202_AF6
#endif
#ifdef __P203_CN
#define SPI0_SCK_P203_AF6
#endif
#ifdef __P313_CN
#define SPI0_MISO_P313_AF6
#endif
#ifdef __P609_CN
#define SPI0_MISO_P609_AF6
#endif
#ifdef __P610_CN
#define SPI0_SCK_P610_AF6
#endif
#ifdef __P611_CN
#define SPI0_MOSI_P611_AF6
#endif
#ifdef __P700_CN
#define SPI0_MISO_P700_AF6
#endif
#ifdef __P701_CN
#define SPI0_MOSI_P701_AF6
#endif
#ifdef __P702_CN
#define SPI0_SCK_P702_AF6
#endif
#ifdef __P100_CN
#define SPI1_MISO_P100_AF6
#endif
#ifdef __P101_CN
#define SPI1_MOSI_P101_AF6
#endif
#ifdef __P102_CN
#define SPI1_SCK_P102_AF6
#endif
#ifdef __P410_CN
#define SPI1_MISO_P410_AF6
#endif
#ifdef __P411_CN
#define SPI1_MOSI_P411_AF6
#endif
#ifdef __P412_CN
#define SPI1_SCK_P412_AF6
#endif

#define SPI_MODULE_0 1
#define SPI_MODULE_1 2

#define SPI_MODULE_COUNT 2
//EOF SPI

//TIM
#ifdef __P210_CN
#define TIM0_P210_CHB_AF3
#endif
#ifdef __P211_CN
#define TIM0_P211_CHA_AF3
#endif
#ifdef __P212_CN
#define TIM0_P212_CHB_AF3
#endif
#ifdef __P213_CN
#define TIM0_P213_CHA_AF3
#endif
#ifdef __P414_CN
#define TIM0_P414_CHB_AF3
#endif
#ifdef __P415_CN
#define TIM0_P415_CHA_AF3
#endif
#ifdef __P511_CN
#define TIM0_P511_CHB_AF3
#endif
#ifdef __P512_CN
#define TIM0_P512_CHA_AF3
#endif
#ifdef __P104_CN
#define TIM1_P104_CHB_AF3
#endif
#ifdef __P105_CN
#define TIM1_P105_CHA_AF3
#endif
#ifdef __P208_CN
#define TIM1_P208_CHB_AF3
#endif
#ifdef __P209_CN
#define TIM1_P209_CHA_AF3
#endif
#ifdef __P405_CN
#define TIM1_P405_CHA_AF3
#endif
#ifdef __P406_CN
#define TIM1_P406_CHB_AF3
#endif
#ifdef __P102_CN
#define TIM2_P102_CHB_AF3
#endif
#ifdef __P103_CN
#define TIM2_P103_CHA_AF3
#endif
#ifdef __P113_CN
#define TIM2_P113_CHA_AF3
#endif
#ifdef __P114_CN
#define TIM2_P114_CHB_AF3
#endif
#ifdef __P712_CN
#define TIM2_P712_CHB_AF3
#endif
#ifdef __P713_CN
#define TIM2_P713_CHA_AF3
#endif
#ifdef __P112_CN
#define TIM3_P112_CHB_AF3
#endif
#ifdef __P300_CN
#define TIM3_P300_CHA_AF3
#endif
#ifdef __P403_CN
#define TIM3_P403_CHA_AF3
#endif
#ifdef __P404_CN
#define TIM3_P404_CHB_AF3
#endif
#ifdef __P911_CN
#define TIM3_P911_CHB_AF3
#endif
#ifdef __P912_CN
#define TIM3_P912_CHA_AF3
#endif
#ifdef __P204_CN
#define TIM4_P204_CHB_AF3
#endif
#ifdef __P205_CN
#define TIM4_P205_CHA_AF3
#endif
#ifdef __P301_CN
#define TIM4_P301_CHB_AF3
#endif
#ifdef __P302_CN
#define TIM4_P302_CHA_AF3
#endif
#ifdef __P610_CN
#define TIM4_P610_CHA_AF3
#endif
#ifdef __P611_CN
#define TIM4_P611_CHB_AF3
#endif
#ifdef __P115_CN
#define TIM5_P115_CHA_AF3
#endif
#ifdef __P202_CN
#define TIM5_P202_CHB_AF3
#endif
#ifdef __P203_CN
#define TIM5_P203_CHA_AF3
#endif
#ifdef __P609_CN
#define TIM5_P609_CHB_AF3
#endif
#ifdef __P700_CN
#define TIM5_P700_CHA_AF3
#endif
#ifdef __P701_CN
#define TIM5_P701_CHB_AF3
#endif
#ifdef __P914_CN
#define TIM5_P914_CHB_AF3
#endif
#ifdef __P915_CN
#define TIM5_P915_CHA_AF3
#endif
#ifdef __P400_CN
#define TIM6_P400_CHA_AF3
#endif
#ifdef __P401_CN
#define TIM6_P401_CHB_AF3
#endif
#ifdef __P600_CN
#define TIM6_P600_CHB_AF3
#endif
#ifdef __P601_CN
#define TIM6_P601_CHA_AF3
#endif
#ifdef __P702_CN
#define TIM6_P702_CHA_AF3
#endif
#ifdef __P703_CN
#define TIM6_P703_CHB_AF3
#endif
#ifdef __PA11_CN
#define TIM6_PA11_CHA_AF3
#endif
#ifdef __PA12_CN
#define TIM6_PA12_CHB_AF3
#endif
#ifdef __P303_CN
#define TIM7_P303_CHB_AF3
#endif
#ifdef __P304_CN
#define TIM7_P304_CHA_AF3
#endif
#ifdef __P602_CN
#define TIM7_P602_CHB_AF3
#endif
#ifdef __P603_CN
#define TIM7_P603_CHA_AF3
#endif
#ifdef __PA06_CN
#define TIM7_PA06_CHB_AF3
#endif
#ifdef __PA07_CN
#define TIM7_PA07_CHA_AF3
#endif
#ifdef __P100_CN
#define TIM8_P100_CHB_AF3
#endif
#ifdef __P101_CN
#define TIM8_P101_CHA_AF3
#endif
#ifdef __P106_CN
#define TIM8_P106_CHB_AF3
#endif
#ifdef __P107_CN
#define TIM8_P107_CHA_AF3
#endif
#ifdef __P604_CN
#define TIM8_P604_CHB_AF3
#endif
#ifdef __P605_CN
#define TIM8_P605_CHA_AF3
#endif
#ifdef __P814_CN
#define TIM8_P814_CHB_AF3
#endif
#ifdef __P815_CN
#define TIM8_P815_CHA_AF3
#endif
#ifdef __P410_CN
#define TIM9_P410_CHB_AF3
#endif
#ifdef __P411_CN
#define TIM9_P411_CHA_AF3
#endif
#ifdef __PB06_CN
#define TIM9_PB06_CHA_AF3
#endif
#ifdef __PB07_CN
#define TIM9_PB07_CHB_AF3
#endif
#ifdef __P407_CN
#define TIM10_P407_CHB_AF3
#endif
#ifdef __P408_CN
#define TIM10_P408_CHA_AF3
#endif
#ifdef __P800_CN
#define TIM11_P800_CHA_AF3
#endif
#ifdef __P801_CN
#define TIM11_P801_CHB_AF3
#endif
#ifdef __P903_CN
#define TIM11_P903_CHA_AF3
#endif
#ifdef __P904_CN
#define TIM11_P904_CHB_AF3
#endif
#ifdef __P802_CN
#define TIM12_P802_CHA_AF3
#endif
#ifdef __P803_CN
#define TIM12_P803_CHB_AF3
#endif
#ifdef __P908_CN
#define TIM12_P908_CHB_AF3
#endif
#ifdef __P909_CN
#define TIM12_P909_CHA_AF3
#endif
#ifdef __P804_CN
#define TIM13_P804_CHA_AF3
#endif
#ifdef __P808_CN
#define TIM13_P808_CHB_AF3
#endif
#ifdef __P906_CN
#define TIM13_P906_CHB_AF3
#endif
#ifdef __P907_CN
#define TIM13_P907_CHA_AF3
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
#define TIM_MODULE_10 11
#define TIM_MODULE_11 12
#define TIM_MODULE_12 13
#define TIM_MODULE_13 14

#define TIM_MODULE_COUNT 14
//EOF TIM

//IVT_TABLE
#define UART0_ERI_EVENT 0x127
#define UART0_ERI_NVIC 2
#define UART0_RXI_EVENT 0x124
#define UART0_RXI_NVIC 1
#define UART0_TXI_EVENT 0x125
#define UART0_TXI_NVIC 0
#define UART1_ERI_EVENT 0x12E
#define UART1_ERI_NVIC 5
#define UART1_RXI_EVENT 0x12B
#define UART1_RXI_NVIC 4
#define UART1_TXI_EVENT 0x12C
#define UART1_TXI_NVIC 3
#define UART2_ERI_EVENT 0x135
#define UART2_ERI_NVIC 8
#define UART2_RXI_EVENT 0x132
#define UART2_RXI_NVIC 7
#define UART2_TXI_EVENT 0x133
#define UART2_TXI_NVIC 6
#define UART3_ERI_EVENT 0x13C
#define UART3_ERI_NVIC 11
#define UART3_RXI_EVENT 0x139
#define UART3_RXI_NVIC 10
#define UART3_TXI_EVENT 0x13A
#define UART3_TXI_NVIC 9
#define UART4_ERI_EVENT 0x143
#define UART4_ERI_NVIC 14
#define UART4_RXI_EVENT 0x140
#define UART4_RXI_NVIC 13
#define UART4_TXI_EVENT 0x141
#define UART4_TXI_NVIC 12
#define UART9_ERI_EVENT 0x166
#define UART9_ERI_NVIC 29
#define UART9_RXI_EVENT 0x163
#define UART9_RXI_NVIC 28
#define UART9_TXI_EVENT 0x164
#define UART9_TXI_NVIC 27
//EOF IVT_TABLE

#endif // _MCU_DEFINITIONS_H_
// ------------------------------------------------------------------------- END
