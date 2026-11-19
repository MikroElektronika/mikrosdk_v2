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
#define __P202_CN
#define __P203_CN
#define __P400_CN
#define __P404_CN
#define __P502_CN
#define __P701_CN
#define __P704_CN
#define __P800_CN
#define __P801_CN
#define __P802_CN
#define __P903_CN
#define __PA00_CN
#define __PA01_CN
#define __PB01_CN
#define __PB02_CN
#define __PD00_CN
#define __PD01_CN
#define __PD02_CN
#define __PD03_CN
#define __PD05_CN
#define __PD07_CN
#define __PE00_CN

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
#define __PORT_D_CN
#define __PORT_E_CN
#define __PORT_H_CN

#define PORT_SIZE (8)
#define PORT_COUNT (15)
//EOF GPIO

//ADC
#ifdef __P400_CN
#define ADC0_P400_AN000
#endif
#ifdef __P404_CN
#define ADC1_P404_AN100
#endif
#ifdef __P502_CN
#define ADC2_P502_AN200
#endif

#define ADC_MODULE_0 1
#define ADC_MODULE_1 2
#define ADC_MODULE_2 3

#define ADC_MODULE_COUNT 3
//EOF ADC

//SCI
#ifdef __PD03_CN
#define SCI1_TX_PD03_AF10
#endif
#ifdef __PD05_CN
#define SCI1_RX_PD05_AF10
#endif
#ifdef __PD07_CN
#define SCI5_SDA_PD07_AF10
#endif
#ifdef __PE00_CN
#define SCI5_SCL_PE00_AF10
#endif
#ifdef __P802_CN
#define SCI6_SCK_P802_AF10
#endif
#ifdef __P801_CN
#define SCI6_MOSI_P801_AF10
#endif
#ifdef __P800_CN
#define SCI6_MISO_P800_AF10
#endif
#ifdef __P203_CN
#define SCI8_TX_P203_AF10
#endif
#ifdef __P202_CN
#define SCI8_RX_P202_AF10
#endif
#ifdef __PA00_CN
#define SCI11_TX_PA00_AF11
#endif
#ifdef __PA01_CN
#define SCI11_RX_PA01_AF11
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

//I2C
#ifdef __PB01_CN
#define I2C0_SCL_PB01_AF15
#endif
#ifdef __PB02_CN
#define I2C0_SDA_PB02_AF15
#endif

#define I2C_MODULE_0 (SCI_MODULE_COUNT + 1)

#define I2C_MODULE_COUNT (SCI_MODULE_COUNT + 1)
//EOF I2C

//UART
#define UART_MODULE_COUNT (SCI_MODULE_COUNT + 0)
//EOF UART

//SPI
#ifdef __PD00_CN
#define SPI0_SCK_PD00_AF13
#endif
#ifdef __PD01_CN
#define SPI0_MISO_PD01_AF13
#endif
#ifdef __PD02_CN
#define SPI0_MOSI_PD02_AF13
#endif

#define SPI_MODULE_0 (SCI_MODULE_COUNT + 1)

#define SPI_MODULE_COUNT (SCI_MODULE_COUNT + 1)
//EOF SPI

//TIM
#ifdef __P701_CN
#define TIM0_P701_CHA_AF20
#endif
#ifdef __P704_CN
#define TIM0_P704_CHB_AF20
#endif
#ifdef __P903_CN
#define TIM9_P903_CHA_AF21
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

#define TIM_MODULE_COUNT 10
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
#define SCI1_ERI_GROUP_VECTOR                    ICU_GROUPBL0_VECTOR
#define SCI1_ERI_GROUP_ENABLE_REG                HAL_LL_ICU_GENBL0
#define SCI1_ERI_GROUP_STATUS_REG                HAL_LL_ICU_GRPBL0
#define SCI1_ERI_GROUP_BIT                       (3)
#define SCI5_ERI_GROUP_VECTOR                    ICU_GROUPBL0_VECTOR
#define SCI5_ERI_GROUP_ENABLE_REG                HAL_LL_ICU_GENBL0
#define SCI5_ERI_GROUP_STATUS_REG                HAL_LL_ICU_GRPBL0
#define SCI5_ERI_GROUP_BIT                       (11)
#define SCI6_ERI_GROUP_VECTOR                    ICU_GROUPBL0_VECTOR
#define SCI6_ERI_GROUP_ENABLE_REG                HAL_LL_ICU_GENBL0
#define SCI6_ERI_GROUP_STATUS_REG                HAL_LL_ICU_GRPBL0
#define SCI6_ERI_GROUP_BIT                       (13)
#define SCI8_ERI_GROUP_VECTOR                    ICU_GROUPBL1_VECTOR
#define SCI8_ERI_GROUP_ENABLE_REG                HAL_LL_ICU_GENBL1
#define SCI8_ERI_GROUP_STATUS_REG                HAL_LL_ICU_GRPBL1
#define SCI8_ERI_GROUP_BIT                       (25)
#define SCI9_ERI_GROUP_VECTOR                    ICU_GROUPBL1_VECTOR
#define SCI9_ERI_GROUP_ENABLE_REG                HAL_LL_ICU_GENBL1
#define SCI9_ERI_GROUP_STATUS_REG                HAL_LL_ICU_GRPBL1
#define SCI9_ERI_GROUP_BIT                       (27)
#define SCI11_ERI_GROUP_VECTOR                   ICU_GROUPAL0_VECTOR
#define SCI11_ERI_GROUP_ENABLE_REG               HAL_LL_ICU_GENAL0
#define SCI11_ERI_GROUP_STATUS_REG               HAL_LL_ICU_GRPAL0
#define SCI11_ERI_GROUP_BIT                      (13)
#define SCI12_ERI_GROUP_VECTOR                   ICU_GROUPBL0_VECTOR
#define SCI12_ERI_GROUP_ENABLE_REG               HAL_LL_ICU_GENBL0
#define SCI12_ERI_GROUP_STATUS_REG               HAL_LL_ICU_GRPBL0
#define SCI12_ERI_GROUP_BIT                      (17)
//EOF IVT_TABLE

#endif // _MCU_DEFINITIONS_H_
// ------------------------------------------------------------------------- END
