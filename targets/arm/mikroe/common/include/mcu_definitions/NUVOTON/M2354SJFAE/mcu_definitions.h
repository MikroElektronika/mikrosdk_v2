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

//ADC
#define ADC0_PB0_CH0
#define ADC0_PB1_CH1
#define ADC0_PB2_CH2
#define ADC0_PB3_CH3
#define ADC0_PB4_CH4
#define ADC0_PB5_CH5
#define ADC0_PB6_CH6
#define ADC0_PB7_CH7
#define ADC0_PB8_CH8
#define ADC0_PB9_CH9
#define ADC0_PB10_CH10
#define ADC0_PB11_CH11
#define ADC0_PB12_CH12
#define ADC0_PB13_CH13
#define ADC0_PB14_CH14
#define ADC0_PB15_CH15

#define ADC_MODULE_0            0

#define ADC_MODULE_COUNT        1
//EOF ADC

//I2C
#define I2C0_SCL_PF3_AF4
#define I2C0_SCL_PB5_AF6
#define I2C0_SCL_PA5_AF9
#define I2C0_SCL_PC1_AF9

#define I2C0_SDA_PF2_AF4
#define I2C0_SDA_PB4_AF6
#define I2C0_SDA_PA4_AF9
#define I2C0_SDA_PC0_AF9

#define I2C1_SCL_PF0_AF3
#define I2C1_SCL_PA12_AF4
#define I2C1_SCL_PB11_AF7
#define I2C1_SCL_PA7_AF8
#define I2C1_SCL_PA3_AF9
#define I2C1_SCL_PB1_AF9
#define I2C1_SCL_PC5_AF9

#define I2C1_SDA_PF1_AF3
#define I2C1_SDA_PA13_AF4
#define I2C1_SDA_PB10_AF7
#define I2C1_SDA_PA6_AF8
#define I2C1_SDA_PA2_AF9
#define I2C1_SDA_PB0_AF9
#define I2C1_SDA_PC4_AF9

#define I2C2_SCL_PA14_AF6
#define I2C2_SCL_PD1_AF6
#define I2C2_SCL_PA11_AF7
#define I2C2_SCL_PB13_AF8
#define I2C2_SCL_PA1_AF9

#define I2C2_SDA_PA15_AF6
#define I2C2_SDA_PA10_AF7
#define I2C2_SDA_PB12_AF8
#define I2C2_SDA_PA0_AF9

#define I2C_MODULE_0            0
#define I2C_MODULE_1            1
#define I2C_MODULE_2            2

#define I2C_MODULE_COUNT        3
//EOF I2C

//UART
#define UART0_RX_PA15_AF3
#define UART0_RX_PF2_AF3
#define UART0_RX_PF1_AF4
#define UART0_RX_PB8_AF5
#define UART0_RX_PB12_AF6
#define UART0_RX_PA0_AF7
#define UART0_RX_PA6_AF7
#define UART0_RX_PD2_AF9
#define UART0_RX_PA4_AF11

#define UART0_TX_PA14_AF3
#define UART0_TX_PF3_AF3
#define UART0_TX_PF0_AF4
#define UART0_TX_PB9_AF5
#define UART0_TX_PB13_AF6
#define UART0_TX_PA1_AF7
#define UART0_TX_PA7_AF7
#define UART0_TX_PD3_AF9
#define UART0_TX_PA5_AF11

#define UART1_RX_PF1_AF2
#define UART1_RX_PB2_AF6
#define UART1_RX_PB6_AF6
#define UART1_RX_PA8_AF7
#define UART1_RX_PA2_AF8

#define UART1_TX_PF0_AF2
#define UART1_TX_PB3_AF6
#define UART1_TX_PB7_AF6
#define UART1_TX_PA9_AF7
#define UART1_TX_PA3_AF8

#define UART2_RX_PF5_AF2
#define UART2_RX_PB0_AF7
#define UART2_RX_PC0_AF8
#define UART2_RX_PC4_AF8
#define UART2_RX_PB4_AF12

#define UART2_TX_PF4_AF2
#define UART2_TX_PB1_AF7
#define UART2_TX_PC1_AF8
#define UART2_TX_PC5_AF8
#define UART2_TX_PB5_AF12

#define UART3_RX_PB14_AF7
#define UART3_RX_PC2_AF11

#define UART3_TX_PD1_AF5
#define UART3_TX_PB15_AF7
#define UART3_TX_PC3_AF11

#define UART4_RX_PA13_AF3
#define UART4_RX_PC6_AF5
#define UART4_RX_PB10_AF6
#define UART4_RX_PF6_AF6
#define UART4_RX_PA2_AF7
#define UART4_RX_PC4_AF11

#define UART4_TX_PA12_AF3
#define UART4_TX_PC7_AF5
#define UART4_TX_PB11_AF6
#define UART4_TX_PA3_AF7
#define UART4_TX_PC5_AF11

#define UART5_RX_PB4_AF7
#define UART5_RX_PA4_AF8

#define UART5_TX_PB5_AF7
#define UART5_TX_PA5_AF8

#define UART_MODULE_0           0
#define UART_MODULE_1           1
#define UART_MODULE_2           2
#define UART_MODULE_3           3
#define UART_MODULE_4           4
#define UART_MODULE_5           5

#define UART_MODULE_COUNT       6
//EOF UART

//SPI
#define SPI0_SCK_PA2_AF4
#define SPI0_SCK_PB14_AF4
#define SPI0_SCK_PD2_AF4

#define SPI0_MISO_PA1_AF4
#define SPI0_MISO_PB13_AF4
#define SPI0_MISO_PD1_AF4

#define SPI0_MOSI_PA0_AF4
#define SPI0_MOSI_PB12_AF4
#define SPI0_MOSI_PF6_AF5

#define SPI1_SCK_PA7_AF4
#define SPI1_SCK_PB3_AF5
#define SPI1_SCK_PC1_AF7

#define SPI1_MISO_PC7_AF4
#define SPI1_MISO_PB5_AF5
#define SPI1_MISO_PC3_AF7

#define SPI1_MOSI_PC6_AF4
#define SPI1_MOSI_PB4_AF5
#define SPI1_MOSI_PC2_AF7

#define SPI2_SCK_PA10_AF4
#define SPI2_SCK_PA13_AF5

#define SPI2_MISO_PA9_AF4
#define SPI2_MISO_PA14_AF5

#define SPI2_MOSI_PA8_AF4
#define SPI2_MOSI_PA15_AF5

#define SPI3_SCK_PB11_AF11

#define SPI3_MISO_PB9_AF11

#define SPI3_MOSI_PB8_AF11

#define SPI_MODULE_0            0
#define SPI_MODULE_1            1
#define SPI_MODULE_2            2
#define SPI_MODULE_3            3

#define SPI_MODULE_COUNT        4
//EOF SPI

//TIM
#define TIM0_PB5_AF14
#define TIM0_PC7_AF14

#define TIM1_PB4_AF14
#define TIM1_PC6_AF14

#define TIM2_PA7_AF14
#define TIM2_PB3_AF14

#define TIM3_PA6_AF14
#define TIM3_PB2_AF14

#define TIM4_PA7_AF10
#define TIM4_PB3_AF13

#define TIM5_PA6_AF10
#define TIM5_PB2_AF13

#define TIM_MODULE_0            0
#define TIM_MODULE_1            1
#define TIM_MODULE_2            2
#define TIM_MODULE_3            3
#define TIM_MODULE_4            4
#define TIM_MODULE_5            5

#define TIM_MODULE_COUNT        6
//EOF TIM

//GPIO
#define __PF6_CN
#define __PF5_CN
#define __PF4_CN
#define __PF3_CN
#define __PF2_CN
#define __PF1_CN
#define __PF0_CN

#define __PD3_CN
#define __PD2_CN
#define __PD1_CN

#define __PC7_CN
#define __PC6_CN
#define __PC5_CN
#define __PC4_CN
#define __PC3_CN
#define __PC2_CN
#define __PC1_CN
#define __PC0_CN

#define __PB15_CN
#define __PB14_CN
#define __PB13_CN
#define __PB12_CN
#define __PB11_CN
#define __PB10_CN
#define __PB9_CN
#define __PB8_CN
#define __PB7_CN
#define __PB6_CN
#define __PB5_CN
#define __PB4_CN
#define __PB3_CN
#define __PB2_CN
#define __PB1_CN
#define __PB0_CN

#define __PA15_CN
#define __PA14_CN
#define __PA13_CN
#define __PA12_CN
#define __PA11_CN
#define __PA10_CN
#define __PA9_CN
#define __PA8_CN
#define __PA7_CN
#define __PA6_CN
#define __PA5_CN
#define __PA4_CN
#define __PA3_CN
#define __PA2_CN
#define __PA1_CN
#define __PA0_CN

#define __PORT_A_CN
#define __PORT_B_CN
#define __PORT_C_CN
#define __PORT_D_CN
#define __PORT_F_CN

#define PORT_SIZE               (16)
#define PORT_COUNT              (5)
//EOF GPIO

//IVT_TABLE
#define UART0_NVIC              36
#define UART1_NVIC              37
#define UART2_NVIC              48
#define UART3_NVIC              49
#define UART4_NVIC              74
#define UART5_NVIC              75
//EOF IVT_TABLE


#endif // _MCU_DEFINITIONS_H_
// ------------------------------------------------------------------------- END
