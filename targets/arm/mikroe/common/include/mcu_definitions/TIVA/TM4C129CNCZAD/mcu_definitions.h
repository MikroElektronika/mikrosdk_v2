/****************************************************************************
**
** Copyright (C) 2021 MikroElektronika d.o.o.
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
#define ADC0_PE3_AIN0
#define ADC1_PE3_AIN0
#define ADC0_PE2_AIN1
#define ADC1_PE2_AIN1
#define ADC0_PE1_AIN2
#define ADC1_PE1_AIN2
#define ADC0_PE0_AIN3
#define ADC1_PE0_AIN3
#define ADC0_PD7_AIN4
#define ADC1_PD7_AIN4
#define ADC0_PD6_AIN5
#define ADC1_PD6_AIN5
#define ADC0_PD5_AIN6
#define ADC1_PD5_AIN6
#define ADC0_PD4_AIN7
#define ADC1_PD4_AIN7
#define ADC0_PE5_AIN8
#define ADC1_PE5_AIN8
#define ADC0_PE4_AIN9
#define ADC1_PE4_AIN9
#define ADC0_PB4_AIN10
#define ADC1_PB4_AIN10
#define ADC0_PB5_AIN11
#define ADC1_PB5_AIN11
#define ADC0_PD3_AIN12
#define ADC1_PD3_AIN12
#define ADC0_PD2_AIN13
#define ADC1_PD2_AIN13
#define ADC0_PD1_AIN14
#define ADC1_PD1_AIN14
#define ADC0_PD0_AIN15
#define ADC1_PD0_AIN15
#define ADC0_PK0_AIN16
#define ADC1_PK0_AIN16
#define ADC0_PK1_AIN17
#define ADC1_PK1_AIN17
#define ADC0_PK2_AIN18
#define ADC1_PK2_AIN18
#define ADC0_PK3_AIN19
#define ADC1_PK3_AIN19
#define ADC0_PE6_AIN20
#define ADC1_PE6_AIN20
#define ADC0_PE7_AIN21
#define ADC1_PE7_AIN21
#define ADC0_PP7_AIN22
#define ADC1_PP7_AIN22
#define ADC0_PP6_AIN23
#define ADC1_PP6_AIN23

#define ADC_MODULE_0 1
#define ADC_MODULE_1 2

#define ADC_MODULE_COUNT 2
//EOF ADC

//I2C
#define I2C0_SCL_PB2_AF2
#define I2C0_SDA_PB3_AF2
#define I2C1_SCL_PG0_AF2
#define I2C1_SCL_PR0_AF2
#define I2C1_SDA_PG1_AF2
#define I2C1_SDA_PR1_AF2
#define I2C2_SCL_PG2_AF2
#define I2C2_SCL_PL1_AF2
#define I2C2_SCL_PN5_AF3
#define I2C2_SCL_PP5_AF2
#define I2C2_SCL_PR2_AF2
#define I2C2_SDA_PG3_AF2
#define I2C2_SDA_PL0_AF2
#define I2C2_SDA_PN4_AF3
#define I2C2_SDA_PP6_AF2
#define I2C2_SDA_PR3_AF2
#define I2C3_SCL_PG4_AF2
#define I2C3_SCL_PK4_AF2
#define I2C3_SCL_PR4_AF2
#define I2C3_SDA_PG5_AF2
#define I2C3_SDA_PK5_AF2
#define I2C3_SDA_PR5_AF2
#define I2C4_SCL_PG6_AF2
#define I2C4_SCL_PK6_AF2
#define I2C4_SCL_PR6_AF2
#define I2C4_SDA_PG7_AF2
#define I2C4_SDA_PK7_AF2
#define I2C4_SDA_PR7_AF2
#define I2C5_SCL_PB0_AF2
#define I2C5_SCL_PB4_AF2
#define I2C5_SDA_PB1_AF2
#define I2C5_SDA_PB5_AF2
#define I2C6_SCL_PA6_AF2
#define I2C6_SCL_PB6_AF2
#define I2C6_SDA_PA7_AF2
#define I2C6_SDA_PB7_AF2
#define I2C7_SCL_PA4_AF2
#define I2C7_SCL_PD0_AF2
#define I2C7_SDA_PA5_AF2
#define I2C7_SDA_PD1_AF2
#define I2C8_SCL_PA2_AF2
#define I2C8_SCL_PD2_AF2
#define I2C8_SDA_PA3_AF2
#define I2C8_SDA_PD3_AF2
#define I2C9_SCL_PA0_AF2
#define I2C9_SCL_PE6_AF2
#define I2C9_SDA_PA1_AF2
#define I2C9_SDA_PE7_AF2

#define I2C_MODULE_0 1
#define I2C_MODULE_1 2
#define I2C_MODULE_2 3
#define I2C_MODULE_3 4
#define I2C_MODULE_4 5
#define I2C_MODULE_5 6
#define I2C_MODULE_6 7
#define I2C_MODULE_7 8
#define I2C_MODULE_8 9
#define I2C_MODULE_9 10

#define I2C_MODULE_COUNT 10
//EOF I2C

//UART
#define UART0_RX_PA0_AF1
#define UART0_TX_PA1_AF1
#define UART1_RX_PB0_AF1
#define UART1_RX_PQ4_AF1
#define UART1_RX_PR5_AF1
#define UART1_TX_PB1_AF1
#define UART1_TX_PQ5_AF1
#define UART1_TX_PR6_AF1
#define UART2_RX_PA6_AF1
#define UART2_RX_PD4_AF1
#define UART2_TX_PA7_AF1
#define UART2_TX_PD5_AF1
#define UART3_RX_PA4_AF1
#define UART3_RX_PJ0_AF1
#define UART3_TX_PA5_AF1
#define UART3_TX_PJ1_AF1
#define UART4_RX_PA2_AF1
#define UART4_RX_PK0_AF1
#define UART4_RX_PR1_AF1
#define UART4_TX_PA3_AF1
#define UART4_TX_PK1_AF1
#define UART4_TX_PR0_AF1
#define UART5_RX_PC6_AF1
#define UART5_RX_PH6_AF1
#define UART5_TX_PC7_AF1
#define UART5_TX_PH7_AF1
#define UART6_RX_PP0_AF1
#define UART6_TX_PP1_AF1
#define UART7_RX_PC4_AF1
#define UART7_RX_PH6_AF2
#define UART7_TX_PC5_AF1
#define UART7_TX_PH7_AF2

#define UART_MODULE_0 1
#define UART_MODULE_1 2
#define UART_MODULE_2 3
#define UART_MODULE_3 4
#define UART_MODULE_4 5
#define UART_MODULE_5 6
#define UART_MODULE_6 7
#define UART_MODULE_7 8

#define UART_MODULE_COUNT 8
//EOF UART

//SPI
#define SPI0_MISO_PA5_AF15
#define SPI0_MOSI_PA4_AF15
#define SPI0_SCK_PA2_AF15
#define SPI1_MISO_PE5_AF15
#define SPI1_MOSI_PE4_AF15
#define SPI1_SCK_PB5_AF15
#define SPI2_MISO_PD0_AF15
#define SPI2_MISO_PG4_AF15
#define SPI2_MOSI_PD1_AF15
#define SPI2_MOSI_PG5_AF15
#define SPI2_SCK_PD3_AF15
#define SPI2_SCK_PG7_AF15
#define SPI3_MISO_PF0_AF14
#define SPI3_MISO_PQ3_AF14
#define SPI3_MOSI_PF1_AF14
#define SPI3_MOSI_PQ2_AF14
#define SPI3_SCK_PF2_AF14
#define SPI3_SCK_PF3_AF14
#define SPI3_SCK_PQ0_AF14

#define SPI_MODULE_0 1
#define SPI_MODULE_1 2
#define SPI_MODULE_2 3
#define SPI_MODULE_3 4

#define SPI_MODULE_COUNT 4
//EOF SPI

//TIM
#define TIM0_CCP0_PA0_AF3
#define TIM0_CCP0_PD0_AF3
#define TIM0_CCP0_PL4_AF3
#define TIM0_CCP0_PR4_AF3
#define TIM0_CCP1_PA1_AF3
#define TIM0_CCP1_PD1_AF3
#define TIM0_CCP1_PL5_AF3
#define TIM0_CCP1_PR5_AF3
#define TIM1_CCP0_PA2_AF3
#define TIM1_CCP0_PD2_AF3
#define TIM1_CCP0_PL6_AF3
#define TIM1_CCP0_PR6_AF3
#define TIM1_CCP1_PA3_AF3
#define TIM1_CCP1_PD3_AF3
#define TIM1_CCP1_PL7_AF3
#define TIM1_CCP1_PR7_AF3
#define TIM2_CCP0_PA4_AF3
#define TIM2_CCP0_PM0_AF3
#define TIM2_CCP0_PS0_AF3
#define TIM2_CCP1_PA5_AF3
#define TIM2_CCP1_PM1_AF3
#define TIM2_CCP1_PS1_AF3
#define TIM3_CCP0_PA6_AF3
#define TIM3_CCP0_PD4_AF3
#define TIM3_CCP0_PM2_AF3
#define TIM3_CCP0_PS2_AF3
#define TIM3_CCP1_PA7_AF3
#define TIM3_CCP1_PD5_AF3
#define TIM3_CCP1_PM3_AF3
#define TIM3_CCP1_PS3_AF3
#define TIM4_CCP0_PB0_AF3
#define TIM4_CCP0_PD6_AF3
#define TIM4_CCP0_PM4_AF3
#define TIM4_CCP0_PS4_AF3
#define TIM4_CCP1_PB1_AF3
#define TIM4_CCP1_PD7_AF3
#define TIM4_CCP1_PM5_AF3
#define TIM4_CCP1_PS5_AF3
#define TIM5_CCP0_PB2_AF3
#define TIM5_CCP0_PM6_AF3
#define TIM5_CCP0_PS6_AF3
#define TIM5_CCP1_PB3_AF3
#define TIM5_CCP1_PM7_AF3
#define TIM5_CCP1_PS7_AF3
#define TIM6_CCP0_PB6_AF3
#define TIM6_CCP0_PP0_AF5
#define TIM6_CCP0_PQ0_AF3
#define TIM6_CCP0_PT0_AF3
#define TIM6_CCP1_PB7_AF3
#define TIM6_CCP1_PP1_AF5
#define TIM6_CCP1_PQ1_AF3
#define TIM6_CCP1_PT1_AF3
#define TIM7_CCP0_PC4_AF3
#define TIM7_CCP0_PQ2_AF3
#define TIM7_CCP0_PT2_AF3
#define TIM7_CCP1_PC5_AF3
#define TIM7_CCP1_PQ3_AF3
#define TIM7_CCP1_PT3_AF3

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

//GPIO
#define __PA0_CN
#define __PA1_CN
#define __PA2_CN
#define __PA3_CN
#define __PA4_CN
#define __PA5_CN
#define __PA6_CN
#define __PA7_CN
#define __PB0_CN
#define __PB1_CN
#define __PB2_CN
#define __PB3_CN
#define __PB4_CN
#define __PB5_CN
#define __PB6_CN
#define __PB7_CN
#define __PC0_CN
#define __PC1_CN
#define __PC2_CN
#define __PC3_CN
#define __PC4_CN
#define __PC5_CN
#define __PC6_CN
#define __PC7_CN
#define __PD0_CN
#define __PD1_CN
#define __PD2_CN
#define __PD3_CN
#define __PD4_CN
#define __PD5_CN
#define __PD6_CN
#define __PD7_CN
#define __PE0_CN
#define __PE1_CN
#define __PE2_CN
#define __PE3_CN
#define __PE4_CN
#define __PE5_CN
#define __PE6_CN
#define __PE7_CN
#define __PF0_CN
#define __PF1_CN
#define __PF2_CN
#define __PF3_CN
#define __PF4_CN
#define __PF5_CN
#define __PF6_CN
#define __PF7_CN
#define __PG0_CN
#define __PG1_CN
#define __PG2_CN
#define __PG3_CN
#define __PG4_CN
#define __PG5_CN
#define __PG6_CN
#define __PG7_CN
#define __PH0_CN
#define __PH1_CN
#define __PH2_CN
#define __PH3_CN
#define __PH4_CN
#define __PH5_CN
#define __PH6_CN
#define __PH7_CN
#define __PJ0_CN
#define __PJ1_CN
#define __PJ2_CN
#define __PJ3_CN
#define __PJ4_CN
#define __PJ5_CN
#define __PJ6_CN
#define __PJ7_CN
#define __PK0_CN
#define __PK1_CN
#define __PK2_CN
#define __PK3_CN
#define __PK4_CN
#define __PK5_CN
#define __PK6_CN
#define __PK7_CN
#define __PL0_CN
#define __PL1_CN
#define __PL2_CN
#define __PL3_CN
#define __PL4_CN
#define __PL5_CN
#define __PL6_CN
#define __PL7_CN
#define __PM0_CN
#define __PM1_CN
#define __PM2_CN
#define __PM3_CN
#define __PM4_CN
#define __PM5_CN
#define __PM6_CN
#define __PM7_CN
#define __PN0_CN
#define __PN1_CN
#define __PN2_CN
#define __PN3_CN
#define __PN4_CN
#define __PN5_CN
#define __PN6_CN
#define __PN7_CN
#define __PP0_CN
#define __PP1_CN
#define __PP2_CN
#define __PP3_CN
#define __PP4_CN
#define __PP5_CN
#define __PP6_CN
#define __PP7_CN
#define __PQ0_CN
#define __PQ1_CN
#define __PQ2_CN
#define __PQ3_CN
#define __PQ4_CN
#define __PQ5_CN
#define __PQ6_CN
#define __PQ7_CN
#define __PR0_CN
#define __PR1_CN
#define __PR2_CN
#define __PR3_CN
#define __PR4_CN
#define __PR5_CN
#define __PR6_CN
#define __PR7_CN
#define __PS0_CN
#define __PS1_CN
#define __PS2_CN
#define __PS3_CN
#define __PS4_CN
#define __PS5_CN
#define __PS6_CN
#define __PS7_CN
#define __PT0_CN
#define __PT1_CN
#define __PT2_CN
#define __PT3_CN

#define __PORT_A_CN
#define __PORT_B_CN
#define __PORT_C_CN
#define __PORT_D_CN
#define __PORT_E_CN
#define __PORT_F_CN
#define __PORT_G_CN
#define __PORT_H_CN
#define __PORT_J_CN
#define __PORT_K_CN
#define __PORT_L_CN
#define __PORT_M_CN
#define __PORT_N_CN
#define __PORT_P_CN
#define __PORT_Q_CN
#define __PORT_R_CN
#define __PORT_S_CN
#define __PORT_T_CN

#define PORT_SIZE (8)
#define PORT_COUNT (18)
//EOF GPIO

//IVT_TABLE
#define UART0_NVIC 21
#define UART1_NVIC 22
#define UART2_NVIC 49
#define UART3_NVIC 72
#define UART4_NVIC 73
#define UART5_NVIC 74
#define UART6_NVIC 75
#define UART7_NVIC 76
//EOF IVT_TABLE

#endif // _MCU_DEFINITIONS_H_
// ------------------------------------------------------------------------- END
