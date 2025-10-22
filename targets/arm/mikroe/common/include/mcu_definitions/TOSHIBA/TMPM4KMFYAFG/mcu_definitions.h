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

/* ========================================== M4K(2) LQFP80
 ========================================== */

//ADC
/* ==== ADC0 ==== */
#define ADC0_PL7_CH8
#define ADC0_PL6_CH9
#define ADC0_PL5_CH13
#define ADC0_PL3_CH14
#define ADC0_PL1_CH15
#define ADC0_PL0_CH16
#define ADC0_PL2_CH17
#define ADC0_PL4_CH18
/* ==== ADC1 ==== */
#define ADC1_PK0_CH0
#define ADC1_PK1_CH1
#define ADC1_PK2_CH2
#define ADC1_PK3_CH3
#define ADC1_PK4_CH4
/* ==== ADC2 ==== */
#define ADC2_PJ0_CH0
#define ADC2_PJ1_CH1
#define ADC2_PJ2_CH2
#define ADC2_PJ3_CH3

#define ADC_MODULE_0 1
#define ADC_MODULE_1 2
#define ADC_MODULE_2 3

#define ADC_MODULE_COUNT 3
//EOF ADC

//I2C
/* ======= I2C0 ======= */
#define I2C0_SCL_PC1_AF4
#define I2C0_SDA_PC0_AF4
/* ======= I2C1 ======= */
#define I2C1_SCL_PU1_AF3
#define I2C1_SDA_PU0_AF3

#define I2C_MODULE_0 1
#define I2C_MODULE_1 2

#define I2C_MODULE_COUNT 2
//EOF I2C
//UART
//UART
/* ====== UART0 ====== */
/* RX */
#define UART0_RX_PC0_FR2
#define UART0_RX_PC1_FR1
#define UART0_RX_PN0_FR2
#define UART0_RX_PN1_FR1
/* TX */
#define UART0_TX_PC1_FR2
#define UART0_TX_PC0_FR1
#define UART0_TX_PN1_FR2
#define UART0_TX_PN0_FR1
/* ====== UART1 ====== */
/* RX */
#define UART1_RX_PC4_FR2
#define UART1_RX_PC5_FR1
#define UART1_RX_PU5_FR2
#define UART1_RX_PU6_FR1
/* TX */
#define UART1_TX_PC5_FR2
#define UART1_TX_PC4_FR1
#define UART1_TX_PU6_FR2
#define UART1_TX_PU5_FR1
/* ====== UART2 ====== */
/* RX */
#define UART2_RX_PF0_FR2
#define UART2_RX_PF1_FR1
#define UART2_RX_PU0_FR2
#define UART2_RX_PU1_FR1
/* TX */
#define UART2_TX_PF1_FR2
#define UART2_TX_PF0_FR1
#define UART2_TX_PU1_FR2
#define UART2_TX_PU0_FR1
/* ====== UART3 ====== */
/* RX */
#define UART3_RX_PF3_FR2
#define UART3_RX_PF4_FR1
#define UART3_RX_PF6_FR2
#define UART3_RX_PF7_FR1
/* TX */
#define UART3_TX_PF4_FR2
#define UART3_TX_PF3_FR1
#define UART3_TX_PF7_FR2
#define UART3_TX_PF6_FR1

#define UART_MODULE_COUNT 4

#define UART_MODULE_0 0
#define UART_MODULE_1 1
#define UART_MODULE_2 2
#define UART_MODULE_3 3
//EOF UART

//SPI
/* ======== SPI0 ======== */
#define SPI0_SCK_PA4_AF1
#define SPI0_SCK_PC5_AF3
#define SPI0_MOSI_PA3_AF1
#define SPI0_MOSI_PC4_AF3
#define SPI0_MISO_PA2_AF1
#define SPI0_MISO_PC3_AF3
/* ======== SPI1 ======== */
#define SPI1_SCK_PG6_AF1
#define SPI1_MOSI_PG5_AF1
#define SPI1_MISO_PG4_AF1

#define SPI_MODULE_0 1
#define SPI_MODULE_1 2

#define SPI_MODULE_COUNT 2
//EOF SPI

//TIM
/* ======= TIM0 =======*/
#define TIM0_CHA_PA3_FR4
#define TIM0_CHB_PA4_FR4
#define TIM0_CHC_PA3_FR5
/* ======= TIM1 =======*/
#define TIM1_CHA_PF4_FR4
#define TIM1_CHC_PF4_FR5
/* ======= TIM2 =======*/
#define TIM2_CHA_PC1_FR5
#define TIM2_CHA_PU2_FR4
#define TIM2_CHB_PU4_FR4
#define TIM2_CHC_PC1_FR6
#define TIM2_CHC_PU2_FR5
/* ======= TIM3 =======*/
#define TIM3_CHA_PC2_FR5
#define TIM3_CHA_PE2_FR4
#define TIM3_CHB_PC3_FR5
#define TIM3_CHB_PE6_FR4
#define TIM3_CHC_PC2_FR6
#define TIM3_CHC_PE2_FR5
/* ======= TIM4 =======*/
#define TIM4_CHA_PG2_FR4
#define TIM4_CHB_PG3_FR4
#define TIM4_CHC_PG2_FR5
/* ======= TIM5 =======*/
#define TIM5_CHA_PF1_FR4
#define TIM5_CHA_PN1_FR4
#define TIM5_CHC_PF1_FR5
#define TIM5_CHC_PN1_FR5

#define TIM_MODULE_0 1
#define TIM_MODULE_1 2
#define TIM_MODULE_2 3
#define TIM_MODULE_3 4
#define TIM_MODULE_4 5
#define TIM_MODULE_5 6

#define TIM_MODULE_COUNT 6
//EOF TIM

//GPIO
/* === PA ==== */
#define __PA0_CN
#define __PA1_CN
#define __PA2_CN
#define __PA3_CN
#define __PA4_CN
/* === PB ==== */
#define __PB0_CN
#define __PB1_CN
#define __PB2_CN
#define __PB3_CN
#define __PB4_CN
#define __PB5_CN
#define __PB6_CN
#define __PB7_CN
/* === PC ==== */
#define __PC0_CN
#define __PC1_CN
#define __PC2_CN
#define __PC3_CN
#define __PC4_CN
#define __PC5_CN
#define __PC6_CN
#define __PC7_CN
/* === PD ==== */
#define __PD0_CN
#define __PD1_CN
#define __PD2_CN
#define __PD3_CN
#define __PD4_CN
#define __PD5_CN
/* === PE ==== */
#define __PE0_CN
#define __PE1_CN
#define __PE2_CN
#define __PE3_CN
#define __PE4_CN
#define __PE5_CN
#define __PE6_CN
#define __PE7_CN
/* === PF ==== */
#define __PF0_CN
#define __PF1_CN
#define __PF2_CN
#define __PF3_CN
#define __PF4_CN
#define __PF5_CN
#define __PF6_CN
#define __PF7_CN
/* === PG ==== */
#define __PG0_CN
#define __PG1_CN
#define __PG2_CN
#define __PG3_CN
#define __PG4_CN
#define __PG5_CN
#define __PG6_CN
/* === PH ==== */
#define __PH0_CN
#define __PH1_CN
/* === PJ ==== */
#define __PJ0_CN
#define __PJ1_CN
#define __PJ2_CN
#define __PJ3_CN
#define __PJ4_CN
#define __PJ5_CN
/* === PK ==== */
#define __PK0_CN
#define __PK1_CN
#define __PK2_CN
#define __PK3_CN
#define __PK4_CN
/* === PL ==== */
#define __PL0_CN
#define __PL1_CN
#define __PL2_CN
#define __PL3_CN
#define __PL4_CN
#define __PL5_CN
#define __PL6_CN
#define __PL7_CN
/* === PM ==== */
#define __PM0_CN
#define __PM1_CN
#define __PM2_CN
/* === PN ==== */
#define __PN0_CN
#define __PN1_CN
#define __PN2_CN
/* === PU ==== */
#define __PU0_CN
#define __PU1_CN
#define __PU2_CN
#define __PU3_CN
#define __PU4_CN
#define __PU5_CN
#define __PU6_CN
#define __PU7_CN
/* === PV ==== */
#define __PV0_CN
#define __PV1_CN

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
#define __PORT_U_CN
#define __PORT_V_CN

#define PORT_COUNT (15)
#define PORT_SIZE (8)
//EOF GPIO

//IVT_TABLE
#define UART0_RX_NVIC   60  /* INTSC0RX */
#define UART0_TX_NVIC   61  /* INTSC0TX */

#define UART1_RX_NVIC   63  /* INTSC1RX */
#define UART1_TX_NVIC   64  /* INTSC1TX */

#define UART2_RX_NVIC   66  /* INTSC2RX */
#define UART2_TX_NVIC   67  /* INTSC2TX */

#define UART3_RX_NVIC   69  /* INTSC3RX */
#define UART3_TX_NVIC   70  /* INTSC3TX */

//EOF IVT_TABLE

#endif // _MCU_DEFINITIONS_H_
// ------------------------------------------------------------------------- END
