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
// R7F100LPL (RL78/L23, 100-pin), R01UH1082 2.1.6
#define __P000_CN
#define __P001_CN
#define __P002_CN
#define __P003_CN
#define __P004_CN
#define __P005_CN
#define __P006_CN
#define __P007_CN
#define __P010_CN
#define __P011_CN
#define __P012_CN
#define __P013_CN
#define __P014_CN
#define __P015_CN
#define __P016_CN
#define __P017_CN
#define __P020_CN
#define __P021_CN
#define __P022_CN
#define __P023_CN
#define __P024_CN
#define __P025_CN
#define __P026_CN
#define __P027_CN
#define __P030_CN
#define __P031_CN
#define __P032_CN
#define __P033_CN
#define __P034_CN
#define __P035_CN
#define __P040_CN
#define __P041_CN
#define __P042_CN
#define __P043_CN
#define __P044_CN
#define __P045_CN
#define __P046_CN
#define __P047_CN
#define __P050_CN
#define __P051_CN
#define __P052_CN
#define __P053_CN
#define __P054_CN
#define __P055_CN
#define __P056_CN
#define __P057_CN
#define __P060_CN
#define __P061_CN
#define __P062_CN
#define __P063_CN
#define __P064_CN
#define __P065_CN
#define __P066_CN
#define __P067_CN
#define __P070_CN
#define __P071_CN
#define __P072_CN
#define __P073_CN
#define __P074_CN
#define __P075_CN
#define __P076_CN
#define __P077_CN
#define __P080_CN
#define __P081_CN
#define __P082_CN
#define __P083_CN
#define __P084_CN
#define __P085_CN
#define __P086_CN
#define __P087_CN
#define __P090_CN
#define __P091_CN
#define __P092_CN
#define __P093_CN
#define __P094_CN
#define __P095_CN
#define __P096_CN
#define __P097_CN
#define __P121_CN
#define __P122_CN
#define __P123_CN
#define __P124_CN
#define __P125_CN
#define __P126_CN
#define __P127_CN
#define __P130_CN
#define __P137_CN
#define __P140_CN
#define __P141_CN
#define __P142_CN
#define __P143_CN
#define __P144_CN
#define __P145_CN
#define __P146_CN
#define __P147_CN

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
#define __PORT_12_CN
#define __PORT_13_CN
#define __PORT_14_CN

#define PORT_SIZE (8)
#define PORT_COUNT (13)
//EOF GPIO

//ADC
#ifdef __P027_CN
#define ADC0_P027_AN021
#endif

#define ADC_MODULE_0 1

#define ADC_MODULE_COUNT 1
//EOF ADC

//I2C
#ifdef __P060_CN
#define I2C0_SCL_P060_AF0
#endif
#ifdef __P061_CN
#define I2C0_SDA_P061_AF0
#endif

#define I2C_MODULE_0 1

#define I2C_MODULE_COUNT 1
//EOF I2C

//UART
// SAU UARTs only, AF = PIOR10 (UART0/1) / PIOR11 (UART2/3) field value. TX and RX
// of one UART must share the AF value since a single PIOR field routes both.
#ifdef __P077_CN
#define UART2_TX_P077_AF0
#endif
#ifdef __P076_CN
#define UART2_RX_P076_AF0
#endif

#define UART_MODULE_0 1
#define UART_MODULE_1 2
#define UART_MODULE_2 3
#define UART_MODULE_3 4

#define UART_MODULE_COUNT 4
//EOF UART

//SPI
// SAU simplified SPI (CSI) only, SPI0-7 = CSI00, CSI01, CSI10, CSI11, CSI20, CSI21, CSI30, CSI31.
// AF = PIOR10 (SPI0-3) / PIOR11 (SPI4-7) field value. SCK, MISO and MOSI of one CSI must
// share the AF value since a single PIOR field routes all three (R01UH1082 Figure 4-10).
#ifdef __P140_CN
#define SPI7_SCK_P140_AF0
#endif
#ifdef __P046_CN
#define SPI7_MISO_P046_AF0
#endif
#ifdef __P047_CN
#define SPI7_MOSI_P047_AF0
#endif

#define SPI_MODULE_0 1
#define SPI_MODULE_1 2
#define SPI_MODULE_2 3
#define SPI_MODULE_3 4
#define SPI_MODULE_4 5
#define SPI_MODULE_5 6
#define SPI_MODULE_6 7
#define SPI_MODULE_7 8

#define SPI_MODULE_COUNT 8
//EOF SPI

//TIM
// TAU0 PWM, TIMn = master channel 2n + slave channel 2n + 1, output TO0(2n+1).
// AF = PIOR0 (TO01) / PIOR1 (TO03, TO05) / PIOR2 (TO07) field value (R01UH1082 Figure 4-10).
#ifdef __P064_CN
#define TIM1_P064_CH3_AF4
#endif
#ifdef __P065_CN
#define TIM2_P065_CH5_AF5
#endif
#ifdef __P077_CN
#define TIM3_P077_CH7_AF3
#endif

#define TIM_MODULE_0 1
#define TIM_MODULE_1 2
#define TIM_MODULE_2 3
#define TIM_MODULE_3 4

#define TIM_MODULE_COUNT 4
//EOF TIM

#endif // _MCU_DEFINITIONS_H_
// ------------------------------------------------------------------------- END
