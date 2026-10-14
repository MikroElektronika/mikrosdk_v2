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
#define __P00_CN
#define __P01_CN
#define __P11_CN
#define __P20_CN
#define __P21_CN
#define __P22_CN
#define __P36_CN
#define __P37_CN
#define __P40_CN
#define __P41_CN
#define __P42_CN
#define __P43_CN
#define __P44_CN
#define __P45_CN
#define __P46_CN
#define __P47_CN
#define __P52_CN
#define __P53_CN
#define __P54_CN
#define __P64_CN
#define __P65_CN
#define __P70_CN
#define __P71_CN
#define __P72_CN
#define __P73_CN
#define __P74_CN
#define __P75_CN
#define __P76_CN
#define __P90_CN
#define __P91_CN
#define __P92_CN
#define __P93_CN
#define __P94_CN
#define __P95_CN
#define __P96_CN
#define __PB0_CN
#define __PB1_CN
#define __PB2_CN
#define __PB3_CN
#define __PB4_CN
#define __PB5_CN
#define __PB6_CN
#define __PD3_CN
#define __PD4_CN
#define __PD5_CN
#define __PD6_CN
#define __PD7_CN
#define __PE2_CN
#define __PN6_CN
#define __PN7_CN

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
#ifdef __P20_CN
#define ADC2_P20_AN216
#endif
#ifdef __P21_CN
#define ADC2_P21_AN217
#endif
#ifdef __P40_CN
#define ADC0_P40_AN000
#endif
#ifdef __P41_CN
#define ADC0_P41_AN001
#endif
#ifdef __P42_CN
#define ADC0_P42_AN002
#endif
#ifdef __P43_CN
#define ADC0_P43_AN003
#endif
#ifdef __P44_CN
#define ADC1_P44_AN100
#endif
#ifdef __P45_CN
#define ADC1_P45_AN101
#endif
#ifdef __P46_CN
#define ADC1_P46_AN102
#endif
#ifdef __P47_CN
#define ADC1_P47_AN103
#endif
#ifdef __P52_CN
#define ADC2_P52_AN200
#endif
#ifdef __P53_CN
#define ADC2_P53_AN201
#endif
#ifdef __P54_CN
#define ADC2_P54_AN202
#endif
#ifdef __P64_CN
#define ADC2_P64_AN210
#endif
#ifdef __P65_CN
#define ADC2_P65_AN211
#endif

#define ADC_MODULE_0 1
#define ADC_MODULE_1 2
#define ADC_MODULE_2 3

#define ADC_MODULE_COUNT 3
//EOF ADC

//SCI
#ifdef __P00_CN
#define SCI12_MISO_P00_AF12
#define SCI12_RX_P00_AF12
#define SCI12_SCL_P00_AF12
#define SCI9_MISO_P00_AF44
#define SCI9_RX_P00_AF44
#define SCI9_SCL_P00_AF44
#endif
#ifdef __P01_CN
#define SCI12_MOSI_P01_AF12
#define SCI12_SDA_P01_AF12
#define SCI12_TX_P01_AF12
#define SCI9_MOSI_P01_AF44
#define SCI9_SDA_P01_AF44
#define SCI9_TX_P01_AF44
#endif
#ifdef __P11_CN
#define SCI8_SCK_P11_AF45
#define SCI9_SCK_P11_AF44
#endif
#ifdef __P20_CN
#define SCI8_MISO_P20_AF45
#define SCI8_RX_P20_AF45
#define SCI8_SCL_P20_AF45
#endif
#ifdef __P21_CN
#define SCI12_MOSI_P21_AF12
#define SCI12_SDA_P21_AF12
#define SCI12_TX_P21_AF12
#define SCI8_MOSI_P21_AF44
#define SCI8_SDA_P21_AF44
#define SCI8_TX_P21_AF44
#endif
#ifdef __P22_CN
#define SCI12_MISO_P22_AF12
#define SCI12_RX_P22_AF12
#define SCI12_SCL_P22_AF12
#define SCI8_MISO_P22_AF44
#define SCI8_RX_P22_AF44
#define SCI8_SCK_P22_AF45
#define SCI8_SCL_P22_AF44
#endif
#ifdef __P36_CN
#define SCI5_MOSI_P36_AF10
#define SCI5_SDA_P36_AF10
#define SCI5_TX_P36_AF10
#endif
#ifdef __P37_CN
#define SCI5_MISO_P37_AF10
#define SCI5_RX_P37_AF10
#define SCI5_SCL_P37_AF10
#endif
#ifdef __P70_CN
#define SCI5_SCK_P70_AF10
#endif
#ifdef __P90_CN
#define SCI5_MOSI_P90_AF10
#define SCI5_SDA_P90_AF10
#define SCI5_TX_P90_AF10
#endif
#ifdef __P91_CN
#define SCI5_MISO_P91_AF10
#define SCI5_RX_P91_AF10
#define SCI5_SCL_P91_AF10
#endif
#ifdef __P92_CN
#define SCI11_MOSI_P92_AF45
#define SCI11_SDA_P92_AF45
#define SCI11_TX_P92_AF45
#define SCI9_SCK_P92_AF44
#endif
#ifdef __P93_CN
#define SCI11_MISO_P93_AF45
#define SCI11_RX_P93_AF45
#define SCI11_SCL_P93_AF45
#define SCI9_MOSI_P93_AF44
#define SCI9_SDA_P93_AF44
#define SCI9_TX_P93_AF44
#endif
#ifdef __P94_CN
#define SCI8_SCK_P94_AF45
#define SCI9_MOSI_P94_AF44
#define SCI9_SDA_P94_AF44
#define SCI9_TX_P94_AF44
#endif
#ifdef __P95_CN
#define SCI6_MISO_P95_AF10
#define SCI6_RX_P95_AF10
#define SCI6_SCL_P95_AF10
#define SCI8_MISO_P95_AF45
#define SCI8_RX_P95_AF45
#define SCI8_SCL_P95_AF45
#endif
#ifdef __PB0_CN
#define SCI6_MOSI_PB0_AF10
#define SCI6_SDA_PB0_AF10
#define SCI6_TX_PB0_AF10
#define SCI8_MOSI_PB0_AF44
#define SCI8_SDA_PB0_AF44
#define SCI8_TX_PB0_AF44
#endif
#ifdef __PB1_CN
#define SCI6_MISO_PB1_AF10
#define SCI6_RX_PB1_AF10
#define SCI6_SCL_PB1_AF10
#endif
#ifdef __PB2_CN
#define SCI6_MOSI_PB2_AF10
#define SCI6_SDA_PB2_AF10
#define SCI6_TX_PB2_AF10
#endif
#ifdef __PB3_CN
#define SCI12_MOSI_PB3_AF12
#define SCI12_SDA_PB3_AF12
#define SCI12_TX_PB3_AF12
#define SCI6_SCK_PB3_AF10
#endif
#ifdef __PB4_CN
#define SCI11_SCK_PB4_AF45
#define SCI12_MISO_PB4_AF12
#define SCI12_RX_PB4_AF12
#define SCI12_SCL_PB4_AF12
#endif
#ifdef __PB5_CN
#define SCI11_MOSI_PB5_AF45
#define SCI11_SDA_PB5_AF45
#define SCI11_TX_PB5_AF45
#define SCI12_MOSI_PB5_AF12
#define SCI12_SDA_PB5_AF12
#define SCI12_TX_PB5_AF12
#define SCI5_MOSI_PB5_AF10
#define SCI5_SDA_PB5_AF10
#define SCI5_TX_PB5_AF10
#endif
#ifdef __PB6_CN
#define SCI11_MISO_PB6_AF45
#define SCI11_RX_PB6_AF45
#define SCI11_SCL_PB6_AF45
#define SCI12_MISO_PB6_AF12
#define SCI12_RX_PB6_AF12
#define SCI12_SCL_PB6_AF12
#define SCI5_MISO_PB6_AF10
#define SCI5_RX_PB6_AF10
#define SCI5_SCL_PB6_AF10
#endif
#ifdef __PD3_CN
#define SCI11_MOSI_PD3_AF45
#define SCI11_SDA_PD3_AF45
#define SCI11_TX_PD3_AF45
#define SCI1_MOSI_PD3_AF10
#define SCI1_SDA_PD3_AF10
#define SCI1_TX_PD3_AF10
#endif
#ifdef __PD4_CN
#define SCI11_SCK_PD4_AF45
#define SCI12_MOSI_PD4_AF12
#define SCI12_SDA_PD4_AF12
#define SCI12_TX_PD4_AF12
#define SCI1_SCK_PD4_AF10
#endif
#ifdef __PD5_CN
#define SCI11_MISO_PD5_AF45
#define SCI11_RX_PD5_AF45
#define SCI11_SCL_PD5_AF45
#define SCI1_MISO_PD5_AF10
#define SCI1_RX_PD5_AF10
#define SCI1_SCL_PD5_AF10
#endif
#ifdef __PD6_CN
#define SCI12_MISO_PD6_AF12
#define SCI12_RX_PD6_AF12
#define SCI12_SCL_PD6_AF12
#endif
#ifdef __PD7_CN
#define SCI5_MOSI_PD7_AF10
#define SCI5_SDA_PD7_AF10
#define SCI5_TX_PD7_AF10
#define SCI8_MOSI_PD7_AF45
#define SCI8_SDA_PD7_AF45
#define SCI8_TX_PD7_AF45
#define SCI9_SCK_PD7_AF44
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
#ifdef __PB1_CN
#define I3C0_SCL_PB1_AF50
#endif
#ifdef __PB2_CN
#define I3C0_SDA_PB2_AF50
#endif

#define I3C_MODULE_0 1

#define I3C_MODULE_COUNT 1
//EOF I3C

//I2C
#ifdef __PB1_CN
#define I2C0_SCL_PB1_AF15
#endif
#ifdef __PB2_CN
#define I2C0_SDA_PB2_AF15
#endif

#define I2C_MODULE_0 1

#define I2C_MODULE_COUNT (SCI_MODULE_COUNT + I3C_MODULE_COUNT + 1)
//EOF I2C

//UART
#define UART_MODULE_COUNT (SCI_MODULE_COUNT + 0)
//EOF UART

//SPI
#ifdef __P20_CN
#define SPI0_SCK_P20_AF13
#define SPI1_SCK_P20_AF14
#endif
#ifdef __P21_CN
#define SPI0_MOSI_P21_AF13
#define SPI1_MOSI_P21_AF14
#endif
#ifdef __P22_CN
#define SPI0_MISO_P22_AF13
#define SPI1_MISO_P22_AF14
#endif
#ifdef __P70_CN
#define SPI1_SCK_P70_AF14
#endif
#ifdef __P71_CN
#define SPI1_MISO_P71_AF14
#endif
#ifdef __P72_CN
#define SPI1_MOSI_P72_AF14
#endif
#ifdef __P91_CN
#define SPI1_SCK_P91_AF14
#endif
#ifdef __P92_CN
#define SPI1_MISO_P92_AF14
#endif
#ifdef __P93_CN
#define SPI1_MOSI_P93_AF14
#endif
#ifdef __P95_CN
#define SPI0_MISO_P95_AF13
#define SPI1_MISO_P95_AF51
#endif
#ifdef __P96_CN
#define SPI1_SCK_P96_AF51
#endif
#ifdef __PB0_CN
#define SPI0_MOSI_PB0_AF13
#define SPI1_MOSI_PB0_AF14
#endif
#ifdef __PB3_CN
#define SPI0_SCK_PB3_AF13
#endif
#ifdef __PB4_CN
#define SPI0_MISO_PB4_AF13
#endif
#ifdef __PB5_CN
#define SPI1_SCK_PB5_AF14
#endif
#ifdef __PB6_CN
#define SPI1_MISO_PB6_AF14
#endif
#ifdef __PD3_CN
#define SPI1_MOSI_PD3_AF14
#endif

#define SPI_MODULE_0 1
#define SPI_MODULE_1 2

#define SPI_MODULE_COUNT (SCI_MODULE_COUNT + 2)
//EOF SPI

//TIM
#ifdef __P11_CN
#define TIM3_P11_CHB_AF20
#endif
#ifdef __P71_CN
#define TIM0_P71_CHA_AF20
#define TIM4_P71_CHA_AF21
#endif
#ifdef __P72_CN
#define TIM1_P72_CHA_AF20
#define TIM5_P72_CHA_AF21
#endif
#ifdef __P73_CN
#define TIM2_P73_CHA_AF20
#define TIM6_P73_CHA_AF21
#endif
#ifdef __P74_CN
#define TIM0_P74_CHB_AF20
#define TIM4_P74_CHB_AF21
#endif
#ifdef __P75_CN
#define TIM1_P75_CHB_AF20
#define TIM5_P75_CHB_AF21
#endif
#ifdef __P76_CN
#define TIM2_P76_CHB_AF20
#define TIM6_P76_CHB_AF21
#endif
#ifdef __P90_CN
#define TIM6_P90_CHB_AF20
#endif
#ifdef __P91_CN
#define TIM5_P91_CHB_AF20
#endif
#ifdef __P92_CN
#define TIM4_P92_CHB_AF20
#define TIM7_P92_CHB_AF21
#endif
#ifdef __P93_CN
#define TIM6_P93_CHA_AF20
#endif
#ifdef __P94_CN
#define TIM5_P94_CHA_AF20
#endif
#ifdef __P95_CN
#define TIM4_P95_CHA_AF20
#define TIM7_P95_CHA_AF21
#endif
#ifdef __PB1_CN
#define TIM7_PB1_CHB_AF21
#endif
#ifdef __PB2_CN
#define TIM7_PB2_CHA_AF21
#endif
#ifdef __PB5_CN
#define TIM2_PB5_CHB_AF20
#define TIM3_PB5_CHB_AF21
#endif
#ifdef __PB6_CN
#define TIM2_PB6_CHA_AF20
#define TIM3_PB6_CHA_AF21
#endif
#ifdef __PD3_CN
#define TIM2_PD3_CHA_AF20
#define TIM7_PD3_CHB_AF23
#endif
#ifdef __PD4_CN
#define TIM1_PD4_CHB_AF20
#endif
#ifdef __PD5_CN
#define TIM1_PD5_CHA_AF20
#define TIM7_PD5_CHA_AF23
#endif
#ifdef __PD6_CN
#define TIM0_PD6_CHB_AF20
#define TIM3_PD6_CHB_AF21
#endif
#ifdef __PD7_CN
#define TIM0_PD7_CHA_AF20
#define TIM3_PD7_CHA_AF21
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
#define SCI1_RXI_VECTOR                      (60)
#define SCI1_TXI_VECTOR                      (61)
#define SCI5_RXI_VECTOR                      (84)
#define SCI5_TXI_VECTOR                      (85)
#define SCI6_RXI_VECTOR                      (86)
#define SCI6_TXI_VECTOR                      (87)
#define SCI8_RXI_VECTOR                      (100)
#define SCI8_TXI_VECTOR                      (101)
#define SCI9_RXI_VECTOR                      (102)
#define SCI9_TXI_VECTOR                      (103)
#define SCI11_RXI_VECTOR                      (114)
#define SCI11_TXI_VECTOR                      (115)
#define SCI12_RXI_VECTOR                      (116)
#define SCI12_TXI_VECTOR                      (117)
#define ICU_GROUPBL0_VECTOR                      (110)
#define ICU_GROUPBL1_VECTOR                      (111)
#define ICU_GROUPAL0_VECTOR                      (112)
//EOF IVT_TABLE

#endif // _MCU_DEFINITIONS_H_
// ------------------------------------------------------------------------- END
