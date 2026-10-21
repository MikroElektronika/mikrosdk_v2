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
#define __PD0_CN
#define __PD1_CN
#define __PD2_CN
#define __PD3_CN
#define __PE0_CN
#define __PE1_CN
#define __PE2_CN
#define __PE3_CN
#define __PE4_CN
#define __PE5_CN
#define __PE6_CN
#define __PF0_CN
#define __PF1_CN
#define __PF2_CN
#define __PF3_CN
#define __PF4_CN
#define __PF5_CN
#define __PG0_CN
#define __PG1_CN
#define __PH0_CN
#define __PH1_CN
#define __PH2_CN
#define __PH3_CN
#define __PJ0_CN
#define __PJ1_CN
#define __PJ2_CN
#define __PJ3_CN
#define __PJ4_CN
#define __PJ5_CN
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
#define __PM0_CN
#define __PM1_CN
#define __PM2_CN
#define __PM3_CN
#define __PM4_CN
#define __PM5_CN
#define __PM6_CN
#define __PN0_CN
#define __PN1_CN
#define __PN2_CN
#define __PN3_CN
#define __PN4_CN
#define __PN5_CN
#define __PP0_CN
#define __PP1_CN
#define __PP2_CN
#define __PP3_CN
#define __PP4_CN
#define __PP5_CN
#define __PP6_CN
#define __PP7_CN
#define __PR0_CN
#define __PR1_CN
#define __PR2_CN
#define __PR3_CN
#define __PW0_CN

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
#define __PORT_R_CN
#define __PORT_W_CN

#define PORT_SIZE (8)
#define PORT_COUNT (16)
//EOF GPIO

//ADC
#ifdef __PD0_CN
#define ADC0_PD0_CH0
#endif
#ifdef __PD1_CN
#define ADC0_PD1_CH1
#endif
#ifdef __PD2_CN
#define ADC0_PD2_CH2
#endif
#ifdef __PD3_CN
#define ADC0_PD3_CH3
#endif
#ifdef __PD4_CN
#define ADC0_PD4_CH19
#endif
#ifdef __PD5_CN
#define ADC0_PD5_CH20
#endif
#ifdef __PE0_CN
#define ADC0_PE0_CH4
#endif
#ifdef __PE1_CN
#define ADC0_PE1_CH5
#endif
#ifdef __PE2_CN
#define ADC0_PE2_CH6
#endif
#ifdef __PE3_CN
#define ADC0_PE3_CH7
#endif
#ifdef __PE4_CN
#define ADC0_PE4_CH8
#endif
#ifdef __PE5_CN
#define ADC0_PE5_CH9
#endif
#ifdef __PE6_CN
#define ADC0_PE6_CH10
#endif
#ifdef __PF0_CN
#define ADC0_PF0_CH11
#endif
#ifdef __PF1_CN
#define ADC0_PF1_CH12
#endif
#ifdef __PF2_CN
#define ADC0_PF2_CH13
#endif
#ifdef __PF3_CN
#define ADC0_PF3_CH14
#endif
#ifdef __PF4_CN
#define ADC0_PF4_CH15
#endif
#ifdef __PF5_CN
#define ADC0_PF5_CH16
#endif
#ifdef __PF6_CN
#define ADC0_PF6_CH17
#endif
#ifdef __PF7_CN
#define ADC0_PF7_CH18
#endif

#define ADC_MODULE_0 1

#define ADC_MODULE_COUNT 1
//EOF ADC

//I2C
#ifdef __PA4_CN
#define I2C1_SCL_PA4_AF2
#endif
#ifdef __PA5_CN
#define I2C1_SDA_PA5_AF2
#endif
#ifdef __PC0_CN
#define I2C0_SCL_PC0_AF2
#endif
#ifdef __PC1_CN
#define I2C0_SDA_PC1_AF2
#endif
#ifdef __PL0_CN
#define I2C2_SCL_PL0_AF4
#endif
#ifdef __PL1_CN
#define I2C2_SDA_PL1_AF4
#endif
#ifdef __PT0_CN
#define I2C3_SDA_PT0_AF4
#endif
#ifdef __PT1_CN
#define I2C3_SCL_PT1_AF4
#endif

#define I2C_MODULE_0 1
#define I2C_MODULE_1 2
#define I2C_MODULE_2 3

#define I2C_MODULE_COUNT 3
//EOF I2C

//UART
#ifdef __PA1_CN
#define UART0_RX_PA1_AF2
#endif
#ifdef __PA1_CN
#define UART0_TX_PA1_AF1
#endif
#ifdef __PA2_CN
#define UART0_RX_PA2_AF1
#endif
#ifdef __PA2_CN
#define UART0_TX_PA2_AF2
#endif
#ifdef __PA6_CN
#define UART3_RX_PA6_AF1
#endif
#ifdef __PA6_CN
#define UART3_TX_PA6_AF2
#endif
#ifdef __PA7_CN
#define UART3_RX_PA7_AF2
#endif
#ifdef __PA7_CN
#define UART3_TX_PA7_AF1
#endif
#ifdef __PB2_CN
#define UART2_RX_PB2_AF2
#endif
#ifdef __PB2_CN
#define UART2_TX_PB2_AF1
#endif
#ifdef __PB3_CN
#define UART2_RX_PB3_AF1
#endif
#ifdef __PB3_CN
#define UART2_TX_PB3_AF2
#endif
#ifdef __PC3_CN
#define UART4_RX_PC3_AF2
#endif
#ifdef __PC3_CN
#define UART4_TX_PC3_AF1
#endif
#ifdef __PC4_CN
#define UART4_RX_PC4_AF1
#endif
#ifdef __PC4_CN
#define UART4_TX_PC4_AF2
#endif
#ifdef __PG2_CN
#define UART3_RX_PG2_AF1
#endif
#ifdef __PG2_CN
#define UART3_TX_PG2_AF2
#endif
#ifdef __PG3_CN
#define UART3_RX_PG3_AF2
#endif
#ifdef __PG3_CN
#define UART3_TX_PG3_AF1
#endif
#ifdef __PJ1_CN
#define UART1_RX_PJ1_AF2
#endif
#ifdef __PJ1_CN
#define UART1_TX_PJ1_AF1
#endif
#ifdef __PJ2_CN
#define UART1_RX_PJ2_AF1
#endif
#ifdef __PJ2_CN
#define UART1_TX_PJ2_AF2
#endif
#ifdef __PK1_CN
#define UART1_RX_PK1_AF2
#endif
#ifdef __PK1_CN
#define UART1_TX_PK1_AF1
#endif
#ifdef __PK2_CN
#define UART1_RX_PK2_AF1
#endif
#ifdef __PK2_CN
#define UART1_TX_PK2_AF2
#endif
#ifdef __PK5_CN
#define UART6_RX_PK5_AF1
#endif
#ifdef __PK5_CN
#define UART6_TX_PK5_AF2
#endif
#ifdef __PK6_CN
#define UART6_RX_PK6_AF2
#endif
#ifdef __PK6_CN
#define UART6_TX_PK6_AF1
#endif
#ifdef __PL0_CN
#define UART2_RX_PL0_AF2
#endif
#ifdef __PL0_CN
#define UART2_TX_PL0_AF1
#endif
#ifdef __PL1_CN
#define UART2_RX_PL1_AF1
#endif
#ifdef __PL1_CN
#define UART2_TX_PL1_AF2
#endif
#ifdef __PM1_CN
#define UART0_RX_PM1_AF2
#endif
#ifdef __PM1_CN
#define UART0_TX_PM1_AF1
#endif
#ifdef __PM2_CN
#define UART0_RX_PM2_AF1
#endif
#ifdef __PM2_CN
#define UART0_TX_PM2_AF2
#endif
#ifdef __PN2_CN
#define UART5_RX_PN2_AF1
#endif
#ifdef __PN2_CN
#define UART5_TX_PN2_AF2
#endif
#ifdef __PN3_CN
#define UART5_RX_PN3_AF2
#endif
#ifdef __PN3_CN
#define UART5_TX_PN3_AF1
#endif
#ifdef __PR0_CN
#define UART7_RX_PR0_AF1
#endif
#ifdef __PR0_CN
#define UART7_TX_PR0_AF2
#endif
#ifdef __PR1_CN
#define UART7_RX_PR1_AF2
#endif
#ifdef __PR1_CN
#define UART7_TX_PR1_AF1
#endif
#ifdef __PV6_CN
#define UART4_RX_PV6_AF2
#endif
#ifdef __PV6_CN
#define UART4_TX_PV6_AF1
#endif
#ifdef __PV7_CN
#define UART4_RX_PV7_AF1
#endif
#ifdef __PV7_CN
#define UART4_TX_PV7_AF2
#endif

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
#ifdef __PA0_CN
#define SPI0_SCK_PA0_AF3
#endif
#ifdef __PA1_CN
#define SPI0_MOSI_PA1_AF3
#endif
#ifdef __PA2_CN
#define SPI0_MISO_PA2_AF3
#endif
#ifdef __PB2_CN
#ifdef HAL_LL_SPI1_MASTER_BASE_ADDR
#define SPI1_SCK_PB2_AF3
#endif
#endif
#ifdef __PB3_CN
#ifdef HAL_LL_SPI1_MASTER_BASE_ADDR
#define SPI1_MOSI_PB3_AF3
#endif
#endif
#ifdef __PB4_CN
#define SPI1_MISO_PB4_AF3
#endif
#ifdef __PH4_CN
#define SPI4_SCK_PH4_AF1
#endif
#ifdef __PH5_CN
#define SPI4_MOSI_PH5_AF1
#endif
#ifdef __PH6_CN
#define SPI4_MISO_PH6_AF1
#endif
#ifdef __PM0_CN
#define SPI0_SCK_PM0_AF3
#endif
#ifdef __PM1_CN
#define SPI0_MOSI_PM1_AF3
#endif
#ifdef __PM2_CN
#define SPI0_MISO_PM2_AF3
#endif
#ifdef __PP0_CN
#define SPI2_SCK_PP0_AF2
#endif
#ifdef __PP1_CN
#define SPI2_MOSI_PP1_AF2
#endif
#ifdef __PP2_CN
#define SPI2_MISO_PP2_AF2
#endif
#ifdef __PP3_CN
#ifdef HAL_LL_SPI3_MASTER_BASE_ADDR
#define SPI3_MISO_PP3_AF1
#endif
#endif
#ifdef __PP4_CN
#define SPI3_MOSI_PP4_AF1
#endif
#ifdef __PP5_CN
#define SPI3_SCK_PP5_AF1
#endif
#ifdef __PT2_CN
#define SPI2_SCK_PT2_AF1
#endif
#ifdef __PT3_CN
#define SPI2_MOSI_PT3_AF1
#endif
#ifdef __PT4_CN
#define SPI2_MISO_PT4_AF1
#endif

#define SPI_MODULE_0 1
#define SPI_MODULE_1 2
#define SPI_MODULE_2 3
#define SPI_MODULE_3 4

#define SPI_MODULE_COUNT 4
//EOF SPI

//TIM
#ifdef __PA0_CN
#define TIM0_CH0_PA0_AF4
#endif
#ifdef __PA0_CN
#define TIM0_CH2_PA0_AF5
#endif
#ifdef __PA3_CN
#define TIM0_CH1_PA3_AF4
#endif
#ifdef __PB0_CN
#define TIM1_CH0_PB0_AF4
#endif
#ifdef __PB0_CN
#define TIM1_CH2_PB0_AF5
#endif
#ifdef __PB3_CN
#define TIM1_CH1_PB3_AF4
#endif
#ifdef __PC0_CN
#define TIM2_CH0_PC0_AF3
#endif
#ifdef __PC0_CN
#define TIM2_CH2_PC0_AF4
#endif
#ifdef __PC3_CN
#define TIM2_CH1_PC3_AF3
#endif
#ifdef __PG2_CN
#define TIM7_CH0_PG2_AF3
#endif
#ifdef __PG2_CN
#define TIM7_CH2_PG2_AF4
#endif
#ifdef __PG5_CN
#define TIM7_CH1_PG5_AF3
#endif
#ifdef __PJ0_CN
#define TIM3_CH0_PJ0_AF3
#endif
#ifdef __PJ0_CN
#define TIM3_CH2_PJ0_AF4
#endif
#ifdef __PJ3_CN
#define TIM3_CH1_PJ3_AF3
#endif
#ifdef __PK2_CN
#define TIM4_CH0_PK2_AF3
#endif
#ifdef __PK2_CN
#define TIM4_CH2_PK2_AF4
#endif
#ifdef __PK5_CN
#define TIM4_CH1_PK5_AF3
#endif
#ifdef __PL2_CN
#define TIM6_CH1_PL2_AF3
#endif
#ifdef __PL5_CN
#define TIM6_CH0_PL5_AF3
#endif
#ifdef __PL5_CN
#define TIM6_CH2_PL5_AF4
#endif
#ifdef __PM0_CN
#define TIM0_CH0_PM0_AF4
#endif
#ifdef __PM0_CN
#define TIM0_CH2_PM0_AF5
#endif
#ifdef __PM3_CN
#define TIM0_CH1_PM3_AF4
#endif
#ifdef __PN0_CN
#define TIM5_CH0_PN0_AF3
#endif
#ifdef __PN0_CN
#define TIM5_CH2_PN0_AF4
#endif
#ifdef __PN3_CN
#define TIM5_CH1_PN3_AF3
#endif
#ifdef __PP0_CN
#define TIM1_CH0_PP0_AF3
#endif
#ifdef __PP0_CN
#define TIM1_CH2_PP0_AF4
#endif
#ifdef __PR0_CN
#define TIM2_CH0_PR0_AF3
#endif
#ifdef __PR0_CN
#define TIM2_CH2_PR0_AF4
#endif
#ifdef __PT2_CN
#define TIM6_CH1_PT2_AF3
#endif
#ifdef __PT5_CN
#define TIM6_CH0_PT5_AF3
#endif
#ifdef __PT5_CN
#define TIM6_CH2_PT5_AF4
#endif

#define TIM_MODULE_0 1
#define TIM_MODULE_1 2
#define TIM_MODULE_2 3
#define TIM_MODULE_3 4
#define TIM_MODULE_4 5
#define TIM_MODULE_5 6
#define TIM_MODULE_6 7

#define TIM_MODULE_COUNT 7
//EOF TIM

//IVT_TABLE
#define UART0_RX_NVIC   67  /* INTUART0RX */
#define UART0_TX_NVIC   68  /* INTUART0TX */
#define UART1_RX_NVIC   70  /* INTUART1RX */
#define UART1_TX_NVIC   71  /* INTUART1TX */
#define UART2_RX_NVIC   73  /* INTUART2RX */
#define UART2_TX_NVIC   74  /* INTUART2TX */
#define UART3_RX_NVIC   76  /* INTUART3RX */
#define UART3_TX_NVIC   77  /* INTUART3TX */
#define UART4_RX_NVIC   79  /* INTUART4RX */
#define UART4_TX_NVIC   80  /* INTUART4TX */
#define UART5_RX_NVIC   82  /* INTUART5RX */
#define UART5_TX_NVIC   83  /* INTUART5TX */
#define UART6_RX_NVIC   168  /* INTUART6RX */
#define UART6_TX_NVIC   169  /* INTUART6TX */
#define UART7_RX_NVIC   171  /* INTUART7RX */
#define UART7_TX_NVIC   172  /* INTUART7TX */
//EOF IVT_TABLE

#endif // _MCU_DEFINITIONS_H_
// ------------------------------------------------------------------------- END
