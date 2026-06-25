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
#define __P214_CN
#define __P215_CN
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
#define __P608_CN
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
#define __PD00_CN
#define __PD01_CN
#define __PD02_CN
#define __PD03_CN
#define __PD04_CN
#define __PD05_CN
#define __PD06_CN
#define __PD07_CN

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
#define __PORT_C_CN
#define __PORT_D_CN

#define PORT_SIZE (16)
#define PORT_COUNT (14)
//EOF GPIO

//ADC
#define ADC_MODULE_COUNT 0
//EOF ADC

//SCI
#ifdef __P112_CN
#define SCI0_MOSI_P112_AF4
#define SCI0_SDA_P112_AF4
#define SCI0_TX_P112_AF4
#endif
#ifdef __P113_CN
#define SCI0_MISO_P113_AF4
#define SCI0_SCL_P113_AF4
#define SCI0_RX_P113_AF4
#endif
#ifdef __P300_CN
#define SCI0_SCK_P300_AF4
#endif
#ifdef __P601_CN
#define SCI0_SCK_P601_AF4
#endif
#ifdef __P602_CN
#define SCI0_MISO_P602_AF4
#define SCI0_SCL_P602_AF4
#define SCI0_RX_P602_AF4
#endif
#ifdef __P603_CN
#define SCI0_MOSI_P603_AF4
#define SCI0_SDA_P603_AF4
#define SCI0_TX_P603_AF4
#endif
#ifdef __P609_CN
#define SCI0_MOSI_P609_AF4
#define SCI0_SDA_P609_AF4
#define SCI0_TX_P609_AF4
#endif
#ifdef __P610_CN
#define SCI0_MISO_P610_AF4
#define SCI0_SCL_P610_AF4
#define SCI0_RX_P610_AF4
#endif
#ifdef __P611_CN
#define SCI0_SCK_P611_AF4
#endif
#ifdef __P212_CN
#define SCI1_MISO_P212_AF5
#define SCI1_SCL_P212_AF5
#define SCI1_RX_P212_AF5
#endif
#ifdef __P213_CN
#define SCI1_MOSI_P213_AF5
#define SCI1_SDA_P213_AF5
#define SCI1_TX_P213_AF5
#endif
#ifdef __P400_CN
#define SCI1_MOSI_P400_AF5
#define SCI1_SDA_P400_AF5
#define SCI1_TX_P400_AF5
#endif
#ifdef __P401_CN
#define SCI1_MISO_P401_AF5
#define SCI1_SCL_P401_AF5
#define SCI1_RX_P401_AF5
#endif
#ifdef __P402_CN
#define SCI1_SCK_P402_AF5
#endif
#ifdef __P407_CN
#define SCI1_SCK_P407_AF5
#endif
#ifdef __P706_CN
#define SCI1_MISO_P706_AF5
#define SCI1_SCL_P706_AF5
#define SCI1_RX_P706_AF5
#endif
#ifdef __P707_CN
#define SCI1_MOSI_P707_AF5
#define SCI1_SDA_P707_AF5
#define SCI1_TX_P707_AF5
#endif
#ifdef __PB00_CN
#define SCI1_SCK_PB00_AF5
#endif
#ifdef __P405_CN
#define SCI2_SCK_P405_AF4
#endif
#ifdef __P406_CN
#define SCI2_MOSI_P406_AF4
#define SCI2_SDA_P406_AF4
#define SCI2_TX_P406_AF4
#endif
#ifdef __P700_CN
#define SCI2_MISO_P700_AF4
#define SCI2_SCL_P700_AF4
#define SCI2_RX_P700_AF4
#endif
#ifdef __P801_CN
#define SCI2_MOSI_P801_AF4
#define SCI2_SDA_P801_AF4
#define SCI2_TX_P801_AF4
#endif
#ifdef __P802_CN
#define SCI2_MISO_P802_AF4
#define SCI2_SCL_P802_AF4
#define SCI2_RX_P802_AF4
#endif
#ifdef __P803_CN
#define SCI2_SCK_P803_AF4
#endif
#ifdef __PA02_CN
#define SCI2_MISO_PA02_AF4
#define SCI2_SCL_PA02_AF4
#define SCI2_RX_PA02_AF4
#endif
#ifdef __PA03_CN
#define SCI2_MOSI_PA03_AF4
#define SCI2_SDA_PA03_AF4
#define SCI2_TX_PA03_AF4
#endif
#ifdef __PA04_CN
#define SCI2_SCK_PA04_AF4
#endif
#ifdef __P310_CN
#define SCI3_MOSI_P310_AF5
#define SCI3_SDA_P310_AF5
#define SCI3_TX_P310_AF5
#endif
#ifdef __P311_CN
#define SCI3_SCK_P311_AF5
#endif
#ifdef __P313_CN
#define SCI3_MOSI_P313_AF5
#define SCI3_SDA_P313_AF5
#define SCI3_TX_P313_AF5
#endif
#ifdef __P314_CN
#define SCI3_MISO_P314_AF5
#define SCI3_SCL_P314_AF5
#define SCI3_RX_P314_AF5
#endif
#ifdef __P315_CN
#define SCI3_SCK_P315_AF5
#endif
#ifdef __P408_CN
#define SCI3_MISO_P408_AF5
#define SCI3_SCL_P408_AF5
#define SCI3_RX_P408_AF5
#endif
#ifdef __P409_CN
#define SCI3_MOSI_P409_AF5
#define SCI3_SDA_P409_AF5
#define SCI3_TX_P409_AF5
#endif
#ifdef __P410_CN
#define SCI3_SCK_P410_AF5
#endif
#ifdef __P905_CN
#define SCI3_MISO_P905_AF5
#define SCI3_SCL_P905_AF5
#define SCI3_RX_P905_AF5
#endif
#ifdef __P203_CN
#define SCI4_MISO_P203_AF4
#define SCI4_SCL_P203_AF4
#define SCI4_RX_P203_AF4
#endif
#ifdef __P204_CN
#define SCI4_SCK_P204_AF4
#endif
#ifdef __P205_CN
#define SCI4_MOSI_P205_AF4
#define SCI4_SDA_P205_AF4
#define SCI4_TX_P205_AF4
#endif
#ifdef __P414_CN
#define SCI4_MISO_P414_AF4
#define SCI4_SCL_P414_AF4
#define SCI4_RX_P414_AF4
#endif
#ifdef __P415_CN
#define SCI4_MOSI_P415_AF4
#define SCI4_SDA_P415_AF4
#define SCI4_TX_P415_AF4
#endif
#ifdef __P514_CN
#define SCI4_SCK_P514_AF4
#endif
#ifdef __P708_CN
#define SCI4_SCK_P708_AF4
#endif
#ifdef __P714_CN
#define SCI4_MOSI_P714_AF4
#define SCI4_SDA_P714_AF4
#define SCI4_TX_P714_AF4
#endif
#ifdef __P715_CN
#define SCI4_MISO_P715_AF4
#define SCI4_SCL_P715_AF4
#define SCI4_RX_P715_AF4
#endif
#ifdef __P510_CN
#define SCI5_MISO_P510_AF5
#define SCI5_SCL_P510_AF5
#define SCI5_RX_P510_AF5
#endif
#ifdef __P608_CN
#define SCI5_MOSI_P608_AF5
#define SCI5_SDA_P608_AF5
#define SCI5_TX_P608_AF5
#endif
#ifdef __PA08_CN
#define SCI5_MISO_PA08_AF5
#define SCI5_SCL_PA08_AF5
#define SCI5_RX_PA08_AF5
#endif
#ifdef __PA09_CN
#define SCI5_MOSI_PA09_AF5
#define SCI5_SDA_PA09_AF5
#define SCI5_TX_PA09_AF5
#endif
#ifdef __PA10_CN
#define SCI5_SCK_PA10_AF5
#endif
#ifdef __PB02_CN
#define SCI5_MISO_PB02_AF5
#define SCI5_SCL_PB02_AF5
#define SCI5_RX_PB02_AF5
#endif
#ifdef __PB03_CN
#define SCI5_MOSI_PB03_AF5
#define SCI5_SDA_PB03_AF5
#define SCI5_TX_PB03_AF5
#endif
#ifdef __PB04_CN
#define SCI5_SCK_PB04_AF5
#endif
#ifdef __PD00_CN
#define SCI5_SCK_PD00_AF5
#endif
#ifdef __P301_CN
#define SCI6_MOSI_P301_AF4
#define SCI6_SDA_P301_AF4
#define SCI6_TX_P301_AF4
#endif
#ifdef __P302_CN
#define SCI6_MISO_P302_AF4
#define SCI6_SCL_P302_AF4
#define SCI6_RX_P302_AF4
#endif
#ifdef __P303_CN
#define SCI6_SCK_P303_AF4
#endif
#ifdef __P907_CN
#define SCI6_SCK_P907_AF4
#endif
#ifdef __P908_CN
#define SCI6_MOSI_P908_AF4
#define SCI6_SDA_P908_AF4
#define SCI6_TX_P908_AF4
#endif
#ifdef __P909_CN
#define SCI6_MISO_P909_AF4
#define SCI6_SCL_P909_AF4
#define SCI6_RX_P909_AF4
#endif
#ifdef __PC12_CN
#define SCI6_SCK_PC12_AF4
#endif
#ifdef __PC13_CN
#define SCI6_MISO_PC13_AF4
#define SCI6_SCL_PC13_AF4
#define SCI6_RX_PC13_AF4
#endif
#ifdef __PC14_CN
#define SCI6_MOSI_PC14_AF4
#define SCI6_SDA_PC14_AF4
#define SCI6_TX_PC14_AF4
#endif
#ifdef __P614_CN
#define SCI7_MISO_P614_AF5
#define SCI7_SCL_P614_AF5
#define SCI7_RX_P614_AF5
#endif
#ifdef __P615_CN
#define SCI7_MOSI_P615_AF5
#define SCI7_SDA_P615_AF5
#define SCI7_TX_P615_AF5
#endif
#ifdef __P808_CN
#define SCI7_MISO_P808_AF5
#define SCI7_SCL_P808_AF5
#define SCI7_RX_P808_AF5
#endif
#ifdef __P809_CN
#define SCI7_MOSI_P809_AF5
#define SCI7_SDA_P809_AF5
#define SCI7_TX_P809_AF5
#endif
#ifdef __P810_CN
#define SCI7_SCK_P810_AF5
#endif
#ifdef __P813_CN
#define SCI7_SCK_P813_AF5
#endif
#ifdef __PC02_CN
#define SCI7_SCK_PC02_AF5
#endif
#ifdef __PC03_CN
#define SCI7_MOSI_PC03_AF5
#define SCI7_SDA_PC03_AF5
#define SCI7_TX_PC03_AF5
#endif
#ifdef __PC04_CN
#define SCI7_MISO_PC04_AF5
#define SCI7_SCL_PC04_AF5
#define SCI7_RX_PC04_AF5
#endif
#ifdef __P500_CN
#define SCI8_MISO_P500_AF4
#define SCI8_SCL_P500_AF4
#define SCI8_RX_P500_AF4
#endif
#ifdef __P501_CN
#define SCI8_MOSI_P501_AF4
#define SCI8_SDA_P501_AF4
#define SCI8_TX_P501_AF4
#endif
#ifdef __P502_CN
#define SCI8_SCK_P502_AF4
#endif
#ifdef __P513_CN
#define SCI8_SCK_P513_AF4
#endif
#ifdef __P805_CN
#define SCI8_MOSI_P805_AF4
#define SCI8_SDA_P805_AF4
#define SCI8_TX_P805_AF4
#endif
#ifdef __P806_CN
#define SCI8_MISO_P806_AF4
#define SCI8_SCL_P806_AF4
#define SCI8_RX_P806_AF4
#endif
#ifdef __PD01_CN
#define SCI8_SCK_PD01_AF4
#endif
#ifdef __PD02_CN
#define SCI8_MOSI_PD02_AF4
#define SCI8_SDA_PD02_AF4
#define SCI8_TX_PD02_AF4
#endif
#ifdef __PD03_CN
#define SCI8_MISO_PD03_AF4
#define SCI8_SCL_PD03_AF4
#define SCI8_RX_PD03_AF4
#endif
#ifdef __P100_CN
#define SCI9_SCK_P100_AF5
#endif
#ifdef __P101_CN
#define SCI9_MISO_P101_AF5
#define SCI9_SCL_P101_AF5
#define SCI9_RX_P101_AF5
#endif
#ifdef __P102_CN
#define SCI9_MOSI_P102_AF5
#define SCI9_SDA_P102_AF5
#define SCI9_TX_P102_AF5
#endif
#ifdef __P208_CN
#define SCI9_MISO_P208_AF5
#define SCI9_SCL_P208_AF5
#define SCI9_RX_P208_AF5
#endif
#ifdef __P209_CN
#define SCI9_MOSI_P209_AF5
#define SCI9_SDA_P209_AF5
#define SCI9_TX_P209_AF5
#endif
#ifdef __P211_CN
#define SCI9_SCK_P211_AF5
#endif
#ifdef __PA11_CN
#define SCI9_SCK_PA11_AF5
#endif
#ifdef __PA12_CN
#define SCI9_MISO_PA12_AF5
#define SCI9_SCL_PA12_AF5
#define SCI9_RX_PA12_AF5
#endif
#ifdef __PA14_CN
#define SCI9_MOSI_PA14_AF5
#define SCI9_SDA_PA14_AF5
#define SCI9_TX_PA14_AF5
#endif

#define SCI_MODULE_0 1
#define SCI_MODULE_1 2
#define SCI_MODULE_2 3
#define SCI_MODULE_3 4
#define SCI_MODULE_4 5
#define SCI_MODULE_5 6
#define SCI_MODULE_6 7
#define SCI_MODULE_7 8
#define SCI_MODULE_8 9
#define SCI_MODULE_9 10

#define SCI_MODULE_COUNT 10
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
#ifdef __P204_CN
#define I2C1_SDA_P204_AF7
#endif
#ifdef __P205_CN
#define I2C1_SCL_P205_AF7
#endif
#ifdef __P511_CN
#define I2C1_SDA_P511_AF7
#endif
#ifdef __P512_CN
#define I2C1_SCL_P512_AF7
#endif
#ifdef __P514_CN
#define I2C2_SDA_P514_AF7
#endif
#ifdef __P515_CN
#define I2C2_SCL_P515_AF7
#endif
#ifdef __P708_CN
#define I2C2_SDA_P708_AF7
#endif
#ifdef __P709_CN
#define I2C2_SCL_P709_AF7
#endif

#define I2C_MODULE_0 12
#define I2C_MODULE_1 13
#define I2C_MODULE_2 14

#define I2C_MODULE_COUNT (SCI_MODULE_COUNT + I3C_MODULE_COUNT + 3)
//EOF I2C

//UART
#define UART_MODULE_COUNT (SCI_MODULE_COUNT + 0)
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
#ifdef __P415_CN
#define SPI1_SCK_P415_AF6
#endif
#ifdef __P708_CN
#define SPI1_MOSI_P708_AF6
#endif
#ifdef __P709_CN
#define SPI1_MISO_P709_AF6
#endif

#define SPI_MODULE_0 11
#define SPI_MODULE_1 12

#define SPI_MODULE_COUNT (SCI_MODULE_COUNT + 2)
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
#ifdef __P507_CN
#define TIM0_P507_CHA_AF3
#endif
#ifdef __P508_CN
#define TIM0_P508_CHB_AF3
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
#ifdef __P509_CN
#define TIM1_P509_CHA_AF3
#endif
#ifdef __P510_CN
#define TIM1_P510_CHB_AF3
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
#ifdef __PD05_CN
#define TIM2_PD05_CHB_AF3
#endif
#ifdef __PD06_CN
#define TIM2_PD06_CHA_AF3
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
#ifdef __PD03_CN
#define TIM3_PD03_CHB_AF3
#endif
#ifdef __PD04_CN
#define TIM3_PD04_CHA_AF3
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
#ifdef __PA04_CN
#define TIM4_PA04_CHB_AF3
#endif
#ifdef __PA05_CN
#define TIM4_PA05_CHA_AF3
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
#ifdef __P813_CN
#define TIM7_P813_CHB_AF3
#endif
#ifdef __PA06_CN
#define TIM7_PA06_CHB_AF3
#endif
#ifdef __PA07_CN
#define TIM7_PA07_CHA_AF3
#endif
#ifdef __PA15_CN
#define TIM7_PA15_CHA_AF3
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
#ifdef __P110_CN
#define TIM9_P110_CHB_AF3
#endif
#ifdef __P111_CN
#define TIM9_P111_CHA_AF3
#endif
#ifdef __P410_CN
#define TIM9_P410_CHB_AF3
#endif
#ifdef __P411_CN
#define TIM9_P411_CHA_AF3
#endif
#ifdef __P612_CN
#define TIM9_P612_CHA_AF3
#endif
#ifdef __P613_CN
#define TIM9_P613_CHB_AF3
#endif
#ifdef __PB06_CN
#define TIM9_PB06_CHA_AF3
#endif
#ifdef __PB07_CN
#define TIM9_PB07_CHB_AF3
#endif
#ifdef __P108_CN
#define TIM10_P108_CHB_AF3
#endif
#ifdef __P109_CN
#define TIM10_P109_CHA_AF3
#endif
#ifdef __P407_CN
#define TIM10_P407_CHB_AF3
#endif
#ifdef __P408_CN
#define TIM10_P408_CHA_AF3
#endif
#ifdef __P810_CN
#define TIM10_P810_CHA_AF3
#endif
#ifdef __P811_CN
#define TIM10_P811_CHB_AF3
#endif
#ifdef __PA13_CN
#define TIM10_PA13_CHA_AF3
#endif
#ifdef __PA14_CN
#define TIM10_PA14_CHB_AF3
#endif
#ifdef __P500_CN
#define TIM11_P500_CHB_AF3
#endif
#ifdef __P710_CN
#define TIM11_P710_CHB_AF3
#endif
#ifdef __P711_CN
#define TIM11_P711_CHA_AF3
#endif
#ifdef __P800_CN
#define TIM11_P800_CHA_AF3
#endif
#ifdef __P801_CN
#define TIM11_P801_CHB_AF3
#endif
#ifdef __P812_CN
#define TIM11_P812_CHA_AF3
#endif
#ifdef __P903_CN
#define TIM11_P903_CHA_AF3
#endif
#ifdef __P904_CN
#define TIM11_P904_CHB_AF3
#endif
#ifdef __P501_CN
#define TIM12_P501_CHA_AF3
#endif
#ifdef __P502_CN
#define TIM12_P502_CHB_AF3
#endif
#ifdef __P714_CN
#define TIM12_P714_CHB_AF3
#endif
#ifdef __P715_CN
#define TIM12_P715_CHA_AF3
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
#ifdef __P513_CN
#define TIM13_P513_CHB_AF3
#endif
#ifdef __P514_CN
#define TIM13_P514_CHB_AF3
#endif
#ifdef __P515_CN
#define TIM13_P515_CHA_AF3
#endif
#ifdef __P804_CN
#define TIM13_P804_CHA_AF3
#endif
#ifdef __P807_CN
#define TIM13_P807_CHA_AF3
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
#ifdef __P102_CN
#define AGT0_P102_CH_AF1
#endif
#ifdef __P106_CN
#define AGT0_P106_CHB_AF1
#endif
#ifdef __P107_CN
#define AGT0_P107_CHA_AF1
#endif
#ifdef __P614_CN
#define AGT0_P614_CH_AF1
#endif
#ifdef __P704_CN
#define AGT0_P704_CH_AF1
#endif
#ifdef __P712_CN
#define AGT0_P712_CHB_AF1
#endif
#ifdef __P713_CN
#define AGT0_P713_CHA_AF1
#endif
#ifdef __P800_CN
#define AGT0_P800_CHA_AF1
#endif
#ifdef __P801_CN
#define AGT0_P801_CHB_AF1
#endif
#ifdef __P205_CN
#define AGT1_P205_CH_AF1
#endif
#ifdef __P311_CN
#define AGT1_P311_CHB_AF1
#endif
#ifdef __P312_CN
#define AGT1_P312_CHA_AF1
#endif
#ifdef __P410_CN
#define AGT1_P410_CHB_AF1
#endif
#ifdef __P411_CN
#define AGT1_P411_CHA_AF1
#endif
#ifdef __P613_CN
#define AGT1_P613_CH_AF1
#endif
#ifdef __P703_CN
#define AGT1_P703_CH_AF1
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
#define AGT_MODULE_0 15
#define AGT_MODULE_1 16

#define TIM_MODULE_COUNT 16
//EOF TIM

//IVT_TABLE
#define SCI0_ERI_EVENT 0x2C7
#define SCI0_ERI_NVIC 2
#define SCI0_RXI_EVENT 0x2C4
#define SCI0_RXI_NVIC 1
#define SCI0_TXI_EVENT 0x2C5
#define SCI0_TXI_NVIC 0
#define SCI1_ERI_EVENT 0x2CE
#define SCI1_ERI_NVIC 5
#define SCI1_RXI_EVENT 0x2CB
#define SCI1_RXI_NVIC 4
#define SCI1_TXI_EVENT 0x2CC
#define SCI1_TXI_NVIC 3
#define SCI2_ERI_EVENT 0x2D5
#define SCI2_ERI_NVIC 8
#define SCI2_RXI_EVENT 0x2D2
#define SCI2_RXI_NVIC 7
#define SCI2_TXI_EVENT 0x2D3
#define SCI2_TXI_NVIC 6
#define SCI3_ERI_EVENT 0x2DC
#define SCI3_ERI_NVIC 11
#define SCI3_RXI_EVENT 0x2D9
#define SCI3_RXI_NVIC 10
#define SCI3_TXI_EVENT 0x2DA
#define SCI3_TXI_NVIC 9
#define SCI4_ERI_EVENT 0x2E3
#define SCI4_ERI_NVIC 14
#define SCI4_RXI_EVENT 0x2E0
#define SCI4_RXI_NVIC 13
#define SCI4_TXI_EVENT 0x2E1
#define SCI4_TXI_NVIC 12
#define SCI5_ERI_EVENT 0x2EA
#define SCI5_ERI_NVIC 17
#define SCI5_RXI_EVENT 0x2E7
#define SCI5_RXI_NVIC 16
#define SCI5_TXI_EVENT 0x2E8
#define SCI5_TXI_NVIC 15
#define SCI6_ERI_EVENT 0x2F1
#define SCI6_ERI_NVIC 20
#define SCI6_RXI_EVENT 0x2EE
#define SCI6_RXI_NVIC 19
#define SCI6_TXI_EVENT 0x2EF
#define SCI6_TXI_NVIC 18
#define SCI7_ERI_EVENT 0x2F8
#define SCI7_ERI_NVIC 23
#define SCI7_RXI_EVENT 0x2F5
#define SCI7_RXI_NVIC 22
#define SCI7_TXI_EVENT 0x2F6
#define SCI7_TXI_NVIC 21
#define SCI8_ERI_EVENT 0x2FF
#define SCI8_ERI_NVIC 14
#define SCI8_RXI_EVENT 0x2FC
#define SCI8_RXI_NVIC 13
#define SCI8_TXI_EVENT 0x2FD
#define SCI8_TXI_NVIC 12
#define SCI9_ERI_EVENT 0x306
#define SCI9_ERI_NVIC 29
#define SCI9_RXI_EVENT 0x303
#define SCI9_RXI_NVIC 28
#define SCI9_TXI_EVENT 0x304
#define SCI9_TXI_NVIC 27
//EOF IVT_TABLE

#endif // _MCU_DEFINITIONS_H_
// ------------------------------------------------------------------------- END
