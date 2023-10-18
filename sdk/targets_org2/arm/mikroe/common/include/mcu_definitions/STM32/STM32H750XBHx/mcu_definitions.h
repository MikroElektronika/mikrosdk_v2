/****************************************************************************
**
** Copyright (C) 2023 MikroElektronika d.o.o.
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

//ADC
#define ADC1_PA0_CH0
#define ADC1_PA0_CH1
#define ADC1_PA0_CH16
#define ADC1_PA1_CH1
#define ADC1_PA1_CH16
#define ADC1_PA1_CH17
#define ADC1_PA2_CH14
#define ADC1_PA3_CH15
#define ADC1_PA4_CH18
#define ADC1_PA5_CH18
#define ADC1_PA5_CH19
#define ADC1_PA6_CH3
#define ADC1_PA7_CH3
#define ADC1_PA7_CH7
#define ADC1_PB0_CH5
#define ADC1_PB0_CH9
#define ADC1_PB1_CH5
#define ADC1_PC0_CH10
#define ADC1_PC1_CH10
#define ADC1_PC1_CH11
#define ADC1_PC2_CH11
#define ADC1_PC2_CH12
#define ADC1_PC3_CH12
#define ADC1_PC3_CH13
#define ADC1_PC4_CH4
#define ADC1_PC5_CH4
#define ADC1_PC5_CH8
#define ADC1_PF12_CH2
#define ADC1_PF12_CH6
#define ADC2_PA0_CH0
#define ADC2_PA0_CH1
#define ADC2_PA1_CH1
#define ADC2_PA2_CH14
#define ADC2_PA3_CH15
#define ADC2_PA4_CH18
#define ADC2_PA5_CH18
#define ADC2_PA5_CH19
#define ADC2_PA6_CH3
#define ADC2_PA7_CH3
#define ADC2_PA7_CH7
#define ADC2_PB0_CH5
#define ADC2_PB0_CH9
#define ADC2_PB1_CH5
#define ADC2_PC0_CH10
#define ADC2_PC1_CH10
#define ADC2_PC1_CH11
#define ADC2_PC2_CH11
#define ADC2_PC2_CH12
#define ADC2_PC3_CH12
#define ADC2_PC3_CH13
#define ADC2_PC4_CH4
#define ADC2_PC5_CH4
#define ADC2_PC5_CH8
#define ADC2_PF13_CH2
#define ADC2_PF14_CH2
#define ADC2_PF14_CH6
#define ADC3_PC0_CH10
#define ADC3_PC1_CH10
#define ADC3_PC1_CH11
#define ADC3_PC2_CH0
#define ADC3_PC2_CH1
#define ADC3_PC2_CH11
#define ADC3_PC2_CH12
#define ADC3_PC3_CH1
#define ADC3_PF10_CH2
#define ADC3_PF10_CH6
#define ADC3_PF3_CH5
#define ADC3_PF4_CH5
#define ADC3_PF4_CH9
#define ADC3_PF5_CH4
#define ADC3_PF6_CH4
#define ADC3_PF6_CH8
#define ADC3_PF7_CH3
#define ADC3_PF8_CH3
#define ADC3_PF8_CH7
#define ADC3_PF9_CH2
#define ADC3_PH2_CH13
#define ADC3_PH3_CH13
#define ADC3_PH3_CH14
#define ADC3_PH4_CH14
#define ADC3_PH4_CH15
#define ADC3_PH5_CH15
#define ADC3_PH5_CH16

#define ADC_MODULE_1 1
#define ADC_MODULE_2 2
#define ADC_MODULE_3 3

#define ADC_MODULE_COUNT 3
//EOF ADC

//I2C
#define I2C1_SCL_PB6_AF4
#define I2C1_SCL_PB8_AF4
#define I2C1_SDA_PB7_AF4
#define I2C1_SDA_PB9_AF4
#define I2C2_SCL_PB10_AF4
#define I2C2_SCL_PF1_AF4
#define I2C2_SCL_PH4_AF4
#define I2C2_SDA_PB11_AF4
#define I2C2_SDA_PF0_AF4
#define I2C2_SDA_PH5_AF4
#define I2C3_SCL_PA8_AF4
#define I2C3_SCL_PH7_AF4
#define I2C3_SDA_PC9_AF4
#define I2C3_SDA_PH8_AF4
#define I2C4_SCL_PB6_AF6
#define I2C4_SCL_PB8_AF6
#define I2C4_SCL_PD12_AF4
#define I2C4_SCL_PF14_AF4
#define I2C4_SCL_PH11_AF4
#define I2C4_SDA_PB7_AF6
#define I2C4_SDA_PB9_AF6
#define I2C4_SDA_PD13_AF4
#define I2C4_SDA_PF15_AF4
#define I2C4_SDA_PH12_AF4

#define I2C_MODULE_1 1
#define I2C_MODULE_2 2
#define I2C_MODULE_3 3
#define I2C_MODULE_4 4

#define I2C_MODULE_COUNT 4
//EOF I2C

//UART
#define UART4_RX_PA1_AF8
#define UART4_RX_PA11_AF6
#define UART4_RX_PB8_AF8
#define UART4_RX_PC11_AF8
#define UART4_RX_PD0_AF8
#define UART4_RX_PH14_AF8
#define UART4_RX_PI9_AF8
#define UART4_TX_PA0_AF8
#define UART4_TX_PA12_AF6
#define UART4_TX_PB9_AF8
#define UART4_TX_PC10_AF8
#define UART4_TX_PD1_AF8
#define UART4_TX_PH13_AF8
#define UART5_RX_PB12_AF14
#define UART5_RX_PB5_AF14
#define UART5_RX_PD2_AF8
#define UART5_TX_PB13_AF14
#define UART5_TX_PB6_AF14
#define UART5_TX_PC12_AF8
#define UART7_RX_PA8_AF11
#define UART7_RX_PB3_AF11
#define UART7_RX_PE7_AF7
#define UART7_RX_PF6_AF7
#define UART7_TX_PA15_AF11
#define UART7_TX_PB4_AF11
#define UART7_TX_PE8_AF7
#define UART7_TX_PF7_AF7
#define UART8_RX_PE0_AF8
#define UART8_RX_PJ9_AF8
#define UART8_TX_PE1_AF8
#define UART8_TX_PJ8_AF8

#define UART_MODULE_4 4
#define UART_MODULE_5 5
#define UART_MODULE_7 7
#define UART_MODULE_8 8
//EOF UART

//USART
#define UART1_RX_PA10_AF7
#define UART1_RX_PB15_AF4
#define UART1_RX_PB7_AF7
#define UART1_TX_PA9_AF7
#define UART1_TX_PB14_AF4
#define UART1_TX_PB6_AF7
#define UART2_RX_PA3_AF7
#define UART2_RX_PD6_AF7
#define UART2_TX_PA2_AF7
#define UART2_TX_PD5_AF7
#define UART3_RX_PB11_AF7
#define UART3_RX_PC11_AF7
#define UART3_RX_PD9_AF7
#define UART3_TX_PB10_AF7
#define UART3_TX_PC10_AF7
#define UART3_TX_PD8_AF7
#define UART6_RX_PC7_AF7
#define UART6_RX_PG9_AF7
#define UART6_TX_PC6_AF7
#define UART6_TX_PG14_AF7

#define UART_MODULE_1 1
#define UART_MODULE_2 2
#define UART_MODULE_3 3
#define UART_MODULE_6 6

#define UART_MODULE_COUNT 8
//EOF USART

//SPI
#define SPI1_MISO_PA6_AF5
#define SPI1_MISO_PB4_AF5
#define SPI1_MISO_PG9_AF5
#define SPI1_MOSI_PA7_AF5
#define SPI1_MOSI_PB5_AF5
#define SPI1_MOSI_PD7_AF5
#define SPI1_SCK_PA5_AF5
#define SPI1_SCK_PB3_AF5
#define SPI1_SCK_PG11_AF5
#define SPI2_MISO_PB14_AF5
#define SPI2_MISO_PC2_AF5
#define SPI2_MISO_PI2_AF5
#define SPI2_MOSI_PB15_AF5
#define SPI2_MOSI_PC1_AF5
#define SPI2_MOSI_PC3_AF5
#define SPI2_MOSI_PI3_AF5
#define SPI2_SCK_PA12_AF5
#define SPI2_SCK_PA9_AF5
#define SPI2_SCK_PB10_AF5
#define SPI2_SCK_PB13_AF5
#define SPI2_SCK_PD3_AF5
#define SPI2_SCK_PI1_AF5
#define SPI3_MISO_PB4_AF6
#define SPI3_MISO_PC11_AF6
#define SPI3_MOSI_PB2_AF7
#define SPI3_MOSI_PB5_AF7
#define SPI3_MOSI_PC12_AF6
#define SPI3_MOSI_PD6_AF5
#define SPI3_SCK_PB3_AF6
#define SPI3_SCK_PC10_AF6
#define SPI4_MISO_PE13_AF5
#define SPI4_MISO_PE5_AF5
#define SPI4_MOSI_PE14_AF5
#define SPI4_MOSI_PE6_AF5
#define SPI4_SCK_PE12_AF5
#define SPI4_SCK_PE2_AF5
#define SPI5_MISO_PF8_AF5
#define SPI5_MISO_PH7_AF5
#define SPI5_MISO_PJ11_AF5
#define SPI5_MOSI_PF11_AF5
#define SPI5_MOSI_PF9_AF5
#define SPI5_MOSI_PJ10_AF5
#define SPI5_SCK_PF7_AF5
#define SPI5_SCK_PH6_AF5
#define SPI5_SCK_PK0_AF5
#define SPI6_MISO_PA6_AF8
#define SPI6_MISO_PB4_AF8
#define SPI6_MISO_PG12_AF5
#define SPI6_MOSI_PA7_AF8
#define SPI6_MOSI_PB5_AF8
#define SPI6_MOSI_PG14_AF5
#define SPI6_SCK_PA5_AF8
#define SPI6_SCK_PB3_AF8
#define SPI6_SCK_PG13_AF5

#define SPI_MODULE_1 1
#define SPI_MODULE_2 2
#define SPI_MODULE_3 3
#define SPI_MODULE_4 4
#define SPI_MODULE_5 5
#define SPI_MODULE_6 6

#define SPI_MODULE_COUNT 6
//EOF SPI

//TIM
#define TIM1_BKIN_COMP1_PA6_AF12
#define TIM1_BKIN_COMP1_PB12_AF13
#define TIM1_BKIN_COMP1_PE15_AF13
#define TIM1_BKIN_COMP1_PK2_AF11
#define TIM1_BKIN_COMP2_PA6_AF12
#define TIM1_BKIN_COMP2_PB12_AF13
#define TIM1_BKIN_COMP2_PE15_AF13
#define TIM1_BKIN_COMP2_PK2_AF11
#define TIM1_BKIN_PA6_AF1
#define TIM1_BKIN_PB12_AF1
#define TIM1_BKIN_PE15_AF1
#define TIM1_BKIN_PK2_AF1
#define TIM1_BKIN2_COMP1_PE6_AF11
#define TIM1_BKIN2_COMP1_PG4_AF11
#define TIM1_BKIN2_COMP2_PE6_AF11
#define TIM1_BKIN2_COMP2_PG4_AF11
#define TIM1_BKIN2_PE6_AF1
#define TIM1_BKIN2_PG4_AF1
#define TIM1_CH1_PA8_AF1
#define TIM1_CH1_PE9_AF1
#define TIM1_CH1_PK1_AF1
#define TIM1_CH1N_PA7_AF1
#define TIM1_CH1N_PB13_AF1
#define TIM1_CH1N_PE8_AF1
#define TIM1_CH1N_PK0_AF1
#define TIM1_CH2_PA9_AF1
#define TIM1_CH2_PE11_AF1
#define TIM1_CH2_PJ11_AF1
#define TIM1_CH2N_PB0_AF1
#define TIM1_CH2N_PB14_AF1
#define TIM1_CH2N_PE10_AF1
#define TIM1_CH2N_PJ10_AF1
#define TIM1_CH3_PA10_AF1
#define TIM1_CH3_PE13_AF1
#define TIM1_CH3_PJ9_AF1
#define TIM1_CH3N_PB1_AF1
#define TIM1_CH3N_PB15_AF1
#define TIM1_CH3N_PE12_AF1
#define TIM1_CH3N_PJ8_AF1
#define TIM1_CH4_PA11_AF1
#define TIM1_CH4_PE14_AF1
#define TIM1_ETR_PA12_AF1
#define TIM1_ETR_PE7_AF1
#define TIM1_ETR_PG5_AF1
#define TIM12_CH1_PB14_AF2
#define TIM12_CH1_PH6_AF2
#define TIM12_CH2_PB15_AF2
#define TIM12_CH2_PH9_AF2
#define TIM13_CH1_PA6_AF9
#define TIM13_CH1_PF8_AF9
#define TIM14_CH1_PA7_AF9
#define TIM14_CH1_PF9_AF9
#define TIM15_BKIN_PA0_AF4
#define TIM15_BKIN_PE3_AF4
#define TIM15_CH1_PA2_AF4
#define TIM15_CH1_PE5_AF4
#define TIM15_CH1N_PA1_AF4
#define TIM15_CH1N_PE4_AF4
#define TIM15_CH2_PA3_AF4
#define TIM15_CH2_PE6_AF4
#define TIM16_BKIN_PB4_AF1
#define TIM16_BKIN_PF10_AF1
#define TIM16_CH1_PB8_AF1
#define TIM16_CH1_PF6_AF1
#define TIM16_CH1N_PB6_AF1
#define TIM16_CH1N_PF8_AF1
#define TIM17_BKIN_PB5_AF1
#define TIM17_BKIN_PG6_AF1
#define TIM17_CH1_PB9_AF1
#define TIM17_CH1_PF7_AF1
#define TIM17_CH1N_PB7_AF1
#define TIM17_CH1N_PF9_AF1
#define TIM2_CH1_PA0_AF1
#define TIM2_CH1_PA15_AF1
#define TIM2_CH1_PA5_AF1
#define TIM2_CH2_PA1_AF1
#define TIM2_CH2_PB3_AF1
#define TIM2_CH3_PA2_AF1
#define TIM2_CH3_PB10_AF1
#define TIM2_CH4_PA3_AF1
#define TIM2_CH4_PB11_AF1
#define TIM2_ETR_PA0_AF1
#define TIM2_ETR_PA15_AF1
#define TIM2_ETR_PA5_AF1
#define TIM3_CH1_PA6_AF2
#define TIM3_CH1_PB4_AF2
#define TIM3_CH1_PC6_AF2
#define TIM3_CH2_PA7_AF2
#define TIM3_CH2_PB5_AF2
#define TIM3_CH2_PC7_AF2
#define TIM3_CH3_PB0_AF2
#define TIM3_CH3_PC8_AF2
#define TIM3_CH4_PB1_AF2
#define TIM3_CH4_PC9_AF2
#define TIM3_ETR_PD2_AF2
#define TIM4_CH1_PB6_AF2
#define TIM4_CH1_PD12_AF2
#define TIM4_CH2_PB7_AF2
#define TIM4_CH2_PD13_AF2
#define TIM4_CH3_PB8_AF2
#define TIM4_CH3_PD14_AF2
#define TIM4_CH4_PB9_AF2
#define TIM4_CH4_PD15_AF2
#define TIM4_ETR_PE0_AF2
#define TIM5_CH1_PA0_AF2
#define TIM5_CH1_PH10_AF2
#define TIM5_CH2_PA1_AF2
#define TIM5_CH2_PH11_AF2
#define TIM5_CH3_PA2_AF2
#define TIM5_CH3_PH12_AF2
#define TIM5_CH4_PA3_AF2
#define TIM5_CH4_PI0_AF2
#define TIM5_ETR_PA4_AF2
#define TIM5_ETR_PH8_AF2
#define TIM8_BKIN_COMP1_PA6_AF10
#define TIM8_BKIN_COMP1_PG2_AF11
#define TIM8_BKIN_COMP1_PI4_AF11
#define TIM8_BKIN_COMP1_PK2_AF10
#define TIM8_BKIN_COMP2_PA6_AF10
#define TIM8_BKIN_COMP2_PG2_AF11
#define TIM8_BKIN_COMP2_PI4_AF11
#define TIM8_BKIN_COMP2_PK2_AF10
#define TIM8_BKIN_PA6_AF3
#define TIM8_BKIN_PG2_AF3
#define TIM8_BKIN_PI4_AF3
#define TIM8_BKIN_PK2_AF3
#define TIM8_BKIN2_COMP1_PA8_AF12
#define TIM8_BKIN2_COMP1_PG3_AF11
#define TIM8_BKIN2_COMP1_PI1_AF11
#define TIM8_BKIN2_COMP2_PA8_AF12
#define TIM8_BKIN2_COMP2_PG3_AF11
#define TIM8_BKIN2_COMP2_PI1_AF11
#define TIM8_BKIN2_PA8_AF3
#define TIM8_BKIN2_PG3_AF3
#define TIM8_BKIN2_PI1_AF3
#define TIM8_CH1_PC6_AF3
#define TIM8_CH1_PI5_AF3
#define TIM8_CH1_PJ8_AF3
#define TIM8_CH1N_PA5_AF3
#define TIM8_CH1N_PA7_AF3
#define TIM8_CH1N_PH13_AF3
#define TIM8_CH1N_PJ9_AF3
#define TIM8_CH2_PC7_AF3
#define TIM8_CH2_PI6_AF3
#define TIM8_CH2_PJ10_AF3
#define TIM8_CH2_PJ6_AF3
#define TIM8_CH2N_PB0_AF3
#define TIM8_CH2N_PB14_AF3
#define TIM8_CH2N_PH14_AF3
#define TIM8_CH2N_PJ11_AF3
#define TIM8_CH2N_PJ7_AF3
#define TIM8_CH3_PC8_AF3
#define TIM8_CH3_PI7_AF3
#define TIM8_CH3_PK0_AF3
#define TIM8_CH3N_PB1_AF3
#define TIM8_CH3N_PB15_AF3
#define TIM8_CH3N_PH15_AF3
#define TIM8_CH3N_PK1_AF3
#define TIM8_CH4_PC9_AF3
#define TIM8_CH4_PI2_AF3
#define TIM8_ETR_PA0_AF3
#define TIM8_ETR_PG8_AF3
#define TIM8_ETR_PI3_AF3

#define TIM1_BUS 2
#define TIM12_BUS 1
#define TIM13_BUS 1
#define TIM14_BUS 1
#define TIM15_BUS 2
#define TIM16_BUS 2
#define TIM17_BUS 2
#define TIM2_BUS 1
#define TIM3_BUS 1
#define TIM4_BUS 1
#define TIM5_BUS 1
#define TIM8_BUS 2

#define TIM_MODULE_1 1
#define TIM_MODULE_12 7
#define TIM_MODULE_13 8
#define TIM_MODULE_14 9
#define TIM_MODULE_15 10
#define TIM_MODULE_16 11
#define TIM_MODULE_17 12
#define TIM_MODULE_2 2
#define TIM_MODULE_3 3
#define TIM_MODULE_4 4
#define TIM_MODULE_5 5
#define TIM_MODULE_8 6

#define TIM_MODULE_COUNT 12
//EOF TIM

//GPIO
#define __PK7_CN
#define __PK6_CN
#define __PK5_CN
#define __PK4_CN
#define __PK3_CN
#define __PK2_CN
#define __PK1_CN
#define __PK0_CN
#define __PJ9_CN
#define __PJ8_CN
#define __PJ7_CN
#define __PJ6_CN
#define __PJ5_CN
#define __PJ4_CN
#define __PJ3_CN
#define __PJ2_CN
#define __PJ15_CN
#define __PJ14_CN
#define __PJ13_CN
#define __PJ12_CN
#define __PJ11_CN
#define __PJ10_CN
#define __PJ1_CN
#define __PJ0_CN
#define __PI9_CN
#define __PI8_CN
#define __PI7_CN
#define __PI6_CN
#define __PI5_CN
#define __PI4_CN
#define __PI3_CN
#define __PI2_CN
#define __PI15_CN
#define __PI14_CN
#define __PI13_CN
#define __PI12_CN
#define __PI11_CN
#define __PI10_CN
#define __PI1_CN
#define __PI0_CN
#define __PH9_CN
#define __PH8_CN
#define __PH7_CN
#define __PH6_CN
#define __PH5_CN
#define __PH4_CN
#define __PH3_CN
#define __PH2_CN
#define __PH1_CN
#define __PH15_CN
#define __PH14_CN
#define __PH13_CN
#define __PH12_CN
#define __PH11_CN
#define __PH10_CN
#define __PH0_CN
#define __PG9_CN
#define __PG8_CN
#define __PG7_CN
#define __PG6_CN
#define __PG5_CN
#define __PG4_CN
#define __PG3_CN
#define __PG2_CN
#define __PG15_CN
#define __PG14_CN
#define __PG13_CN
#define __PG12_CN
#define __PG11_CN
#define __PG10_CN
#define __PG1_CN
#define __PG0_CN
#define __PF9_CN
#define __PF8_CN
#define __PF7_CN
#define __PF6_CN
#define __PF5_CN
#define __PF4_CN
#define __PF3_CN
#define __PF2_CN
#define __PF15_CN
#define __PF14_CN
#define __PF13_CN
#define __PF12_CN
#define __PF11_CN
#define __PF10_CN
#define __PF1_CN
#define __PF0_CN
#define __PE9_CN
#define __PE8_CN
#define __PE7_CN
#define __PE6_CN
#define __PE5_CN
#define __PE4_CN
#define __PE3_CN
#define __PE2_CN
#define __PE15_CN
#define __PE14_CN
#define __PE13_CN
#define __PE12_CN
#define __PE11_CN
#define __PE10_CN
#define __PE1_CN
#define __PE0_CN
#define __PD9_CN
#define __PD8_CN
#define __PD7_CN
#define __PD6_CN
#define __PD5_CN
#define __PD4_CN
#define __PD3_CN
#define __PD2_CN
#define __PD15_CN
#define __PD14_CN
#define __PD13_CN
#define __PD12_CN
#define __PD11_CN
#define __PD10_CN
#define __PD1_CN
#define __PD0_CN
#define __PC9_CN
#define __PC8_CN
#define __PC7_CN
#define __PC6_CN
#define __PC5_CN
#define __PC4_CN
#define __PC3_CN
#define __PC3_CN
#define __PC2_CN
#define __PC2_CN
#define __PC15_CN
#define __PC14_CN
#define __PC13_CN
#define __PC12_CN
#define __PC11_CN
#define __PC10_CN
#define __PC1_CN
#define __PC0_CN
#define __PB9_CN
#define __PB8_CN
#define __PB7_CN
#define __PB6_CN
#define __PB5_CN
#define __PB4_CN
#define __PB3_CN
#define __PB2_CN
#define __PB15_CN
#define __PB14_CN
#define __PB13_CN
#define __PB12_CN
#define __PB11_CN
#define __PB10_CN
#define __PB1_CN
#define __PB0_CN
#define __PA9_CN
#define __PA8_CN
#define __PA7_CN
#define __PA6_CN
#define __PA5_CN
#define __PA4_CN
#define __PA3_CN
#define __PA2_CN
#define __PA15_CN
#define __PA14_CN
#define __PA13_CN
#define __PA12_CN
#define __PA11_CN
#define __PA10_CN
#define __PA1_CN
#define __PA1_CN
#define __PA0_CN
#define __PA0_CN

#define __PORT_A_CN
#define __PORT_B_CN
#define __PORT_C_CN
#define __PORT_D_CN
#define __PORT_E_CN
#define __PORT_F_CN
#define __PORT_G_CN
#define __PORT_H_CN
#define __PORT_I_CN
#define __PORT_J_CN
#define __PORT_K_CN

#define PORT_SIZE (16)
#define PORT_COUNT (11)
//EOF GPIO

//IVT_TABLE
#define UART1_NVIC   53
#define UART2_NVIC   54
#define UART3_NVIC   55
#define UART4_NVIC   68
#define UART5_NVIC   69
#define UART6_NVIC   87
#define UART7_NVIC   98
#define UART8_NVIC   99
#define LPUART1_NVIC  158
//EOF IVT_TABLE


#endif // _MCU_DEFINITIONS_H_
// ------------------------------------------------------------------------- END
