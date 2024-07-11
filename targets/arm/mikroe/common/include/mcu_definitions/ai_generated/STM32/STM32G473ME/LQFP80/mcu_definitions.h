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
 * @brief MCU specific pin and module definitions for STM32G473ME_LQFP80.
 */

#ifndef _MCU_DEFINITIONS_H_
#define _MCU_DEFINITIONS_H_

#ifdef __cplusplus
extern "C"{
#endif

// ADC
#define ADC1_PA0_CH1
#define ADC1_PA1_CH2
#define ADC1_PA2_CH3
#define ADC1_PA3_CH4
#define ADC1_PB0_CH15
#define ADC1_PB11_CH14
#define ADC1_PB12_CH11
#define ADC1_PB14_CH5
#define ADC1_PB1_CH12
#define ADC1_PC0_CH6
#define ADC1_PC1_CH7
#define ADC1_PC2_CH8
#define ADC1_PC3_CH9
#define ADC1_PF0_CH10
#define ADC2_PA0_CH1
#define ADC2_PA1_CH2
#define ADC2_PA4_CH17
#define ADC2_PA5_CH13
#define ADC2_PA6_CH3
#define ADC2_PA7_CH4
#define ADC2_PB11_CH14
#define ADC2_PB15_CH15
#define ADC2_PB2_CH12
#define ADC2_PC0_CH6
#define ADC2_PC1_CH7
#define ADC2_PC2_CH8
#define ADC2_PC3_CH9
#define ADC2_PC4_CH5
#define ADC2_PC5_CH11
#define ADC2_PF1_CH10
#define ADC3_PB0_CH12
#define ADC3_PB13_CH5
#define ADC3_PB1_CH1
#define ADC3_PD10_CH7
#define ADC3_PE10_CH14
#define ADC3_PE11_CH15
#define ADC3_PE12_CH16
#define ADC3_PE13_CH3
#define ADC3_PE7_CH4
#define ADC3_PE8_CH6
#define ADC3_PE9_CH2
#define ADC4_PB12_CH3
#define ADC4_PB14_CH4
#define ADC4_PB15_CH5
#define ADC4_PD10_CH7
#define ADC4_PD8_CH12
#define ADC4_PD9_CH13
#define ADC4_PE10_CH14
#define ADC4_PE11_CH15
#define ADC4_PE12_CH16
#define ADC4_PE14_CH1
#define ADC4_PE15_CH2
#define ADC4_PE8_CH6
#define ADC5_PA8_CH1
#define ADC5_PA9_CH2
#define ADC5_PD10_CH7
#define ADC5_PD8_CH12
#define ADC5_PD9_CH13
#define ADC5_PE10_CH14
#define ADC5_PE11_CH15
#define ADC5_PE12_CH16
#define ADC5_PE8_CH6

#define ADC_MODULE_1 (1)
#define ADC_MODULE_2 (2)
#define ADC_MODULE_3 (3)
#define ADC_MODULE_4 (4)
#define ADC_MODULE_5 (5)

#define ADC_MODULE_COUNT (5)
// EOF ADC

// CAN
#define FDCAN1_RX_PA11_AF9
#define FDCAN1_RX_PB8_AF9
#define FDCAN1_RX_PD0_AF9
#define FDCAN1_TX_PA12_AF9
#define FDCAN1_TX_PB9_AF9
#define FDCAN1_TX_PD1_AF9
#define FDCAN2_RX_PB12_AF9
#define FDCAN2_RX_PB5_AF9
#define FDCAN2_TX_PB13_AF9
#define FDCAN2_TX_PB6_AF9
#define FDCAN3_RX_PA8_AF11
#define FDCAN3_RX_PB3_AF11
#define FDCAN3_TX_PA15_AF11
#define FDCAN3_TX_PB4_AF11

#define CAN_MODULE_1 (1)
#define CAN_MODULE_2 (2)
#define CAN_MODULE_3 (3)

#define CAN_MODULE_COUNT (3)

#define HAL_LL_FDCAN1_GPIO_AF9 (9)
#define HAL_LL_FDCAN2_GPIO_AF9 (9)
#define HAL_LL_FDCAN3_GPIO_AF11 (11)
// EOF CAN

// DMA
#define DMA_NUM_OF_CHANNELS (116)
#define DMA_NUM_OF_CHANNELS_FAMILY (116)
#define DMA_NUM_OF_MODULES (2)
#define DMA_NUM_OF_STREAMS (8)
#define DMA_NUM_OF_STREAMS_FAMILY (8)
// EOF DMA

// I2C
#define I2C1_SCL_PA13_AF4
#define I2C1_SCL_PA15_AF4
#define I2C1_SCL_PB8_AF4
#define I2C1_SDA_PA14_AF4
#define I2C1_SDA_PB7_AF4
#define I2C1_SDA_PB9_AF4
#define I2C2_SCL_PA9_AF4
#define I2C2_SCL_PC4_AF4
#define I2C2_SDA_PA8_AF4
#define I2C2_SDA_PF0_AF4
#define I2C3_SCL_PA8_AF2
#define I2C3_SCL_PC8_AF8
#define I2C3_SDA_PB5_AF8
#define I2C3_SDA_PC11_AF8
#define I2C3_SDA_PC9_AF8
#define I2C4_SCL_PA13_AF3
#define I2C4_SCL_PC6_AF8
#define I2C4_SDA_PB7_AF3
#define I2C4_SDA_PC7_AF8

#define I2C_MODULE_1 (1)
#define I2C_MODULE_2 (2)
#define I2C_MODULE_3 (3)
#define I2C_MODULE_4 (4)

#define I2C_MODULE_COUNT (4)
// EOF I2C

// U(S)ART
#define LPUART1_RX_PA3_AF12
#define LPUART1_RX_PB10_AF8
#define LPUART1_RX_PC0_AF8
#define LPUART1_TX_PA2_AF12
#define LPUART1_TX_PB11_AF8
#define LPUART1_TX_PC1_AF8
#define UART4_RX_PC11_AF5
#define UART4_TX_PC10_AF5
#define UART5_RX_PD2_AF5
#define UART5_TX_PC12_AF5
#define USART1_RX_PA10_AF7
#define USART1_RX_PB7_AF7
#define USART1_RX_PC5_AF7
#define USART1_TX_PA9_AF7
#define USART1_TX_PB6_AF7
#define USART1_TX_PC4_AF7
#define USART2_RX_PA15_AF7
#define USART2_RX_PA3_AF7
#define USART2_RX_PB4_AF7
#define USART2_TX_PA14_AF7
#define USART2_TX_PA2_AF7
#define USART2_TX_PB3_AF7
#define USART3_RX_PB11_AF7
#define USART3_RX_PB8_AF7
#define USART3_RX_PC11_AF7
#define USART3_RX_PD9_AF7
#define USART3_RX_PE15_AF7
#define USART3_TX_PB10_AF7
#define USART3_TX_PB9_AF7
#define USART3_TX_PC10_AF7
#define USART3_TX_PD8_AF7

#define UART_MODULE_1 (1)
#define UART_MODULE_2 (2)
#define UART_MODULE_3 (3)
#define UART_MODULE_4 (4)
#define UART_MODULE_5 (5)

#define UART_MODULE_COUNT (5)
// EOF U(S)ART

// SPI
#define SPI1_MISO_PA6_AF5
#define SPI1_MISO_PB4_AF5
#define SPI1_MOSI_PA7_AF5
#define SPI1_MOSI_PB5_AF5
#define SPI1_SCK_PA5_AF5
#define SPI1_SCK_PB3_AF5
#define SPI2_MISO_PA10_AF5
#define SPI2_MISO_PB14_AF5
#define SPI2_MOSI_PA11_AF5
#define SPI2_MOSI_PB15_AF5
#define SPI2_SCK_PB13_AF5
#define SPI2_SCK_PF1_AF5
#define SPI3_MISO_PB4_AF6
#define SPI3_MISO_PC11_AF6
#define SPI3_MOSI_PB5_AF6
#define SPI3_MOSI_PC12_AF6
#define SPI3_SCK_PB3_AF6
#define SPI3_SCK_PC10_AF6
#define SPI4_MISO_PE13_AF5
#define SPI4_MOSI_PE14_AF5
#define SPI4_SCK_PE12_AF5

#define SPI_MODULE_1 (1)
#define SPI_MODULE_2 (2)
#define SPI_MODULE_3 (3)
#define SPI_MODULE_4 (4)

#define SPI_MODULE_COUNT (4)
// EOF SPI

// TIM
#define LPTIM1_ETR_PB6_AF11
#define LPTIM1_ETR_PC3_AF1
#define TIM15_BKIN_PA9_AF9
#define TIM15_BKIN_PC5_AF2
#define TIM15_CH1N_PA1_AF9
#define TIM15_CH1N_PB15_AF2
#define TIM15_CH1_PA2_AF9
#define TIM15_CH1_PB14_AF1
#define TIM15_CH2_PA3_AF9
#define TIM15_CH2_PB15_AF1
#define TIM16_BKIN_PB5_AF1
#define TIM16_CH1N_PA13_AF1
#define TIM16_CH1N_PB6_AF1
#define TIM16_CH1_PA12_AF1
#define TIM16_CH1_PA6_AF1
#define TIM16_CH1_PB4_AF1
#define TIM16_CH1_PB8_AF1
#define TIM17_BKIN_PA10_AF1
#define TIM17_BKIN_PB4_AF10
#define TIM17_CH1N_PB7_AF1
#define TIM17_CH1_PA7_AF1
#define TIM17_CH1_PB5_AF10
#define TIM17_CH1_PB9_AF1
#define TIM1_BKIN2_PA11_AF12
#define TIM1_BKIN2_PC3_AF6
#define TIM1_BKIN2_PE14_AF6
#define TIM1_BKIN_PA14_AF6
#define TIM1_BKIN_PA15_AF9
#define TIM1_BKIN_PA6_AF6
#define TIM1_BKIN_PB10_AF12
#define TIM1_BKIN_PB12_AF6
#define TIM1_BKIN_PB8_AF12
#define TIM1_BKIN_PC13_AF2
#define TIM1_BKIN_PE15_AF2
#define TIM1_CH1N_PA11_AF6
#define TIM1_CH1N_PA7_AF6
#define TIM1_CH1N_PB13_AF6
#define TIM1_CH1N_PC13_AF4
#define TIM1_CH1N_PE8_AF2
#define TIM1_CH1_PA8_AF6
#define TIM1_CH1_PC0_AF2
#define TIM1_CH1_PE9_AF2
#define TIM1_CH2N_PA12_AF6
#define TIM1_CH2N_PB0_AF6
#define TIM1_CH2N_PB14_AF6
#define TIM1_CH2N_PE10_AF2
#define TIM1_CH2_PA9_AF6
#define TIM1_CH2_PC1_AF2
#define TIM1_CH2_PE11_AF2
#define TIM1_CH3N_PB15_AF4
#define TIM1_CH3N_PB1_AF6
#define TIM1_CH3N_PB9_AF12
#define TIM1_CH3N_PE12_AF2
#define TIM1_CH3N_PF0_AF6
#define TIM1_CH3_PA10_AF6
#define TIM1_CH3_PC2_AF2
#define TIM1_CH3_PE13_AF2
#define TIM1_CH4N_PC5_AF6
#define TIM1_CH4N_PE15_AF6
#define TIM1_CH4_PA11_AF11
#define TIM1_CH4_PC3_AF2
#define TIM1_CH4_PE14_AF2
#define TIM1_ETR_PA12_AF11
#define TIM1_ETR_PC4_AF2
#define TIM1_ETR_PE7_AF2
#define TIM20_CH1_PB2_AF3
#define TIM20_CH2_PC2_AF6
#define TIM20_CH3_PC8_AF6
#define TIM2_CH1_PA0_AF1
#define TIM2_CH1_PA15_AF1
#define TIM2_CH1_PA5_AF1
#define TIM2_CH2_PA1_AF1
#define TIM2_CH2_PB3_AF1
#define TIM2_CH3_PA2_AF1
#define TIM2_CH3_PA9_AF10
#define TIM2_CH3_PB10_AF1
#define TIM2_CH4_PA10_AF10
#define TIM2_CH4_PA3_AF1
#define TIM2_CH4_PB11_AF1
#define TIM2_ETR_PA0_AF14
#define TIM2_ETR_PA15_AF14
#define TIM2_ETR_PA5_AF2
#define TIM3_CH1_PA6_AF2
#define TIM3_CH1_PB4_AF2
#define TIM3_CH1_PC6_AF2
#define TIM3_CH2_PA4_AF2
#define TIM3_CH2_PA7_AF2
#define TIM3_CH2_PB5_AF2
#define TIM3_CH2_PC7_AF2
#define TIM3_CH3_PB0_AF2
#define TIM3_CH3_PC8_AF2
#define TIM3_CH4_PB1_AF2
#define TIM3_CH4_PB7_AF10
#define TIM3_CH4_PC9_AF2
#define TIM3_ETR_PB3_AF10
#define TIM3_ETR_PD2_AF2
#define TIM4_CH1_PA11_AF10
#define TIM4_CH1_PB6_AF2
#define TIM4_CH2_PA12_AF10
#define TIM4_CH2_PB7_AF2
#define TIM4_CH3_PA13_AF10
#define TIM4_CH3_PB8_AF2
#define TIM4_CH4_PB9_AF2
#define TIM4_ETR_PA8_AF10
#define TIM4_ETR_PB3_AF2
#define TIM5_CH1_PA0_AF2
#define TIM5_CH1_PB2_AF2
#define TIM5_CH2_PA1_AF2
#define TIM5_CH2_PC12_AF1
#define TIM5_CH3_PA2_AF2
#define TIM5_CH3_PE8_AF1
#define TIM5_CH4_PA3_AF2
#define TIM5_CH4_PE9_AF1
#define TIM5_ETR_PB12_AF2
#define TIM8_BKIN2_PB6_AF10
#define TIM8_BKIN2_PC9_AF6
#define TIM8_BKIN2_PD1_AF6
#define TIM8_BKIN_PA0_AF9
#define TIM8_BKIN_PA10_AF11
#define TIM8_BKIN_PA6_AF4
#define TIM8_BKIN_PB7_AF5
#define TIM8_BKIN_PD2_AF4
#define TIM8_CH1N_PA7_AF4
#define TIM8_CH1N_PB3_AF4
#define TIM8_CH1N_PC10_AF4
#define TIM8_CH1_PA15_AF2
#define TIM8_CH1_PB6_AF5
#define TIM8_CH1_PC6_AF4
#define TIM8_CH2N_PB0_AF4
#define TIM8_CH2N_PB4_AF4
#define TIM8_CH2N_PC11_AF4
#define TIM8_CH2_PA14_AF5
#define TIM8_CH2_PB8_AF10
#define TIM8_CH2_PC7_AF4
#define TIM8_CH3N_PB1_AF4
#define TIM8_CH3N_PB5_AF3
#define TIM8_CH3N_PC12_AF4
#define TIM8_CH3_PB9_AF10
#define TIM8_CH3_PC8_AF4
#define TIM8_CH4N_PC13_AF6
#define TIM8_CH4N_PD0_AF6
#define TIM8_CH4_PC9_AF4
#define TIM8_CH4_PD1_AF4
#define TIM8_ETR_PA0_AF10
#define TIM8_ETR_PB6_AF6

#define TIM_MODULE_1 (1)
#define TIM_MODULE_2 (2)
#define TIM_MODULE_3 (3)
#define TIM_MODULE_4 (4)
#define TIM_MODULE_5 (5)
#define TIM_MODULE_8 (6)
#define TIM_MODULE_15 (7)
#define TIM_MODULE_16 (8)
#define TIM_MODULE_17 (9)
#define TIM_MODULE_20 (10)

#define TIM_MODULE_COUNT (10)

#define TIM2_BUS (1)
#define TIM3_BUS (1)
#define TIM4_BUS (1)
#define TIM5_BUS (1)
#define TIM1_BUS (2)
#define TIM8_BUS (2)
#define TIM20_BUS (2)
#define TIM15_BUS (2)
#define TIM16_BUS (2)
#define TIM17_BUS (2)
// EOF TIM

// GPIO
#define __PA0_CN
#define __PA1_CN
#define __PA10_CN
#define __PA11_CN
#define __PA12_CN
#define __PA13_CN
#define __PA14_CN
#define __PA15_CN
#define __PA2_CN
#define __PA3_CN
#define __PA4_CN
#define __PA5_CN
#define __PA6_CN
#define __PA7_CN
#define __PA8_CN
#define __PA9_CN
#define __PB0_CN
#define __PB1_CN
#define __PB10_CN
#define __PB11_CN
#define __PB12_CN
#define __PB13_CN
#define __PB14_CN
#define __PB15_CN
#define __PB2_CN
#define __PB3_CN
#define __PB4_CN
#define __PB5_CN
#define __PB6_CN
#define __PB7_CN
#define __PB8_CN
#define __PB9_CN
#define __PC0_CN
#define __PC1_CN
#define __PC10_CN
#define __PC11_CN
#define __PC12_CN
#define __PC13_CN
#define __PC14_CN
#define __PC15_CN
#define __PC2_CN
#define __PC3_CN
#define __PC4_CN
#define __PC5_CN
#define __PC6_CN
#define __PC7_CN
#define __PC8_CN
#define __PC9_CN
#define __PD0_CN
#define __PD1_CN
#define __PD10_CN
#define __PD2_CN
#define __PD8_CN
#define __PD9_CN
#define __PE10_CN
#define __PE11_CN
#define __PE12_CN
#define __PE13_CN
#define __PE14_CN
#define __PE15_CN
#define __PE7_CN
#define __PE8_CN
#define __PE9_CN
#define __PF0_CN
#define __PF1_CN
#define __PG10_CN

#define __PORT_A_CN
#define __PORT_B_CN
#define __PORT_C_CN
#define __PORT_D_CN
#define __PORT_E_CN
#define __PORT_F_CN
#define __PORT_G_CN

#define PORT_COUNT (7)
#define PORT_SIZE (16)
// EOF GPIO

// IVT_TABLE
#define UART1_IVT (37)
#define UART1_NVIC (53)
#define UART2_IVT (38)
#define UART2_NVIC (54)
#define UART3_IVT (39)
#define UART3_NVIC (55)
#define UART4_IVT (52)
#define UART4_NVIC (68)
#define UART5_IVT (53)
#define UART5_NVIC (69)
// EOF IVT_TABLE

#ifdef __cplusplus
}
#endif

#endif // _MCU_DEFINITIONS_H_
// ------------------------------------------------------------------------- END
