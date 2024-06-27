/****************************************************************************
**
** Copyright (C) 2024 MikroElektronika d.o.o.
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
** OF MERCHANTABILITY, EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED
** TO THE WARRANTIES FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT.
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
#include "dma_definitions.h"
#include "can_definitions.h"

//ADC
#define ADC0_IN10_PC0
#define ADC1_IN10_PC0
#define ADC0_IN11_PC1
#define ADC1_IN11_PC1
#define ADC0_IN12_PC2
#define ADC1_IN12_PC2
#define ADC0_IN13_PC3
#define ADC1_IN13_PC3
#define ADC0_IN0_PA0
#define ADC1_IN0_PA0
#define ADC0_IN1_PA1
#define ADC1_IN1_PA1
#define ADC0_IN2_PA2
#define ADC1_IN2_PA2
#define ADC0_IN3_PA3
#define ADC1_IN3_PA3
#define ADC0_IN4_PA4
#define ADC1_IN4_PA4
#define ADC0_IN5_PA5
#define ADC1_IN5_PA5
#define ADC0_IN6_PA6
#define ADC1_IN6_PA6
#define ADC0_IN7_PA7
#define ADC1_IN7_PA7
#define ADC0_IN14_PC4
#define ADC1_IN14_PC4
#define ADC0_IN15_PC5
#define ADC1_IN15_PC5
#define ADC0_IN8_PB0
#define ADC1_IN8_PB0
#define ADC0_IN9_PB1
#define ADC1_IN9_PB1

#define ADC_MODULE_0 (1)
#define ADC_MODULE_1 (2)

#define ADC_MODULE_COUNT (2)
//EOF ADC

//I2C
#define I2C0_SCL_PB6_REMAP_NONE
#define I2C0_SDA_PB7_REMAP_NONE
#define I2C0_SCL_PB8_REMAP_FULL
#define I2C0_SDA_PB9_REMAP_FULL

#define I2C_MODULE_0 (1)

#define I2C_MODULE_COUNT (1)
//EOF I2C

//U(S)ART
#define UART1_TX_PA2_REMAP_NONE
#define UART1_RX_PA3_REMAP_NONE
#define UART0_TX_PA9_REMAP_NONE
#define UART0_RX_PA10_REMAP_NONE
#define UART0_TX_PB6_REMAP_FULL
#define UART0_RX_PB7_REMAP_FULL

#define UART_MODULE_1 (2)
#define UART_MODULE_0 (1)

#define UART_MODULE_COUNT (2)
//EOF U(S)ART

//SPI
#define SPI0_SCK_PA5_REMAP_NONE
#define SPI0_MISO_PA6_REMAP_NONE
#define SPI0_MOSI_PA7_REMAP_NONE
#define SPI0_SCK_PB3_REMAP_FULL
#define SPI0_MISO_PB4_REMAP_FULL
#define SPI0_MOSI_PB5_REMAP_FULL

#define SPI_MODULE_0 (1)

#define SPI_MODULE_COUNT (1)
//EOF SPI

//TIM
#define TIMER1_CH0_PA0_REMAP_NONE
#define TIMER1_CH1_PA1_REMAP_NONE
#define TIMER1_CH2_PA2_REMAP_NONE
#define TIMER1_CH3_PA3_REMAP_NONE
#define TIMER2_CH0_PA6_REMAP_NONE
#define TIMER2_CH1_PA7_REMAP_NONE
#define TIMER0_CH0_PA7_REMAP_PARTIAL
#define TIMER0_CH0_ON_PA7_INVERTED_REMAP_NONE
#define TIMER2_CH2_PB0_REMAP_NONE
#define TIMER0_CH1_PB0_REMAP_PARTIAL
#define TIMER0_CH1_ON_PB0_INVERTED_REMAP_NONE
#define TIMER2_CH3_PB1_REMAP_NONE
#define TIMER0_CH2_PB1_REMAP_PARTIAL
#define TIMER0_CH2_ON_PB1_INVERTED_REMAP_NONE
#define TIMER1_CH2_PB10_REMAP_FULL
#define TIMER1_CH3_PB11_REMAP_FULL
#define TIMER0_CH0_PB13_REMAP_NONE
#define TIMER0_CH0_ON_PB13_INVERTED_REMAP_NONE
#define TIMER0_CH1_PB14_REMAP_NONE
#define TIMER0_CH1_ON_PB14_INVERTED_REMAP_NONE
#define TIMER0_CH2_PB15_REMAP_NONE
#define TIMER0_CH2_ON_PB15_INVERTED_REMAP_NONE
#define TIMER2_CH0_PC6_REMAP_FULL
#define TIMER2_CH1_PC7_REMAP_FULL
#define TIMER2_CH2_PC8_REMAP_FULL
#define TIMER2_CH3_PC9_REMAP_FULL
#define TIMER0_CH0_PA8_REMAP_NONE
#define TIMER0_CH1_PA9_REMAP_NONE
#define TIMER0_CH2_PA10_REMAP_NONE
#define TIMER0_CH3_PA11_REMAP_NONE
#define TIMER1_CH0_PA15_REMAP_NONE
#define TIMER1_CH1_PB3_REMAP_PARTIAL
#define TIMER2_CH0_PB4_REMAP_PARTIAL
#define TIMER2_CH1_PB5_REMAP_PARTIAL

#define TIM_MODULE_1 (2)
#define TIM_MODULE_2 (3)
#define TIM_MODULE_0 (1)

#define TIM_MODULE_COUNT (3)
//EOF TIM

//GPIO
#define __PC13_CN
#define __PC14_CN
#define __PC15_CN
#define __PC0_CN
#define __PC1_CN
#define __PC2_CN
#define __PC3_CN
#define __PA0_CN
#define __PA1_CN
#define __PA2_CN
#define __PA3_CN
#define __PA4_CN
#define __PA5_CN
#define __PA6_CN
#define __PA7_CN
#define __PC4_CN
#define __PC5_CN
#define __PB0_CN
#define __PB1_CN
#define __PB2_CN
#define __PB10_CN
#define __PB11_CN
#define __PB12_CN
#define __PB13_CN
#define __PB14_CN
#define __PB15_CN
#define __PC6_CN
#define __PC7_CN
#define __PC8_CN
#define __PC9_CN
#define __PA8_CN
#define __PA9_CN
#define __PA10_CN
#define __PA11_CN
#define __PA12_CN
#define __PA13_CN
#define __PA14_CN
#define __PA15_CN
#define __PC10_CN
#define __PC11_CN
#define __PC12_CN
#define __PD0_CN
#define __PD1_CN
#define __PD2_CN
#define __PB3_CN
#define __PB4_CN
#define __PB5_CN
#define __PB6_CN
#define __PB7_CN
#define __PB8_CN
#define __PB9_CN

#define __PORT_C_CN
#define __PORT_A_CN
#define __PORT_B_CN
#define __PORT_D_CN

#define PORT_SIZE  (16)
#define PORT_COUNT (4)
//EOF GPIO

//IVT_TABLE
#define ECLIC_VECTOR_NUMBER_UART1 (57)
#define ECLIC_VECTOR_ADDRESS_UART1 (0x000000E4)
#define ECLIC_VECTOR_NUMBER_UART0 (56)
#define ECLIC_VECTOR_ADDRESS_UART0 (0x000000E0)
//EOF IVT_TABLE

#endif // _MCU_DEFINITIONS_H_
// ------------------------------------------------------------------------- END
