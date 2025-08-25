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
#define ADC_MODULE_COUNT 1
//EOF ADC

//I2C
#define I2C_MODULE_COUNT 2
//EOF I2C

//UART
#define UART_MODULE_COUNT 4
//EOF UART

//SPI
#define SPI_MODULE_COUNT 2
//EOF SPI

//TIM
#define TIM_MODULE_COUNT 8
//EOF TIM

//GPIO
#define __PA0_CN
#define __PA1_CN
#define __PA2_CN
#define __PA3_CN
#define __PA4_CN
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
#define __PH0_CN
#define __PH1_CN
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
#define __PN0_CN
#define __PN1_CN
#define __PN2_CN
#define __PU0_CN
#define __PU1_CN
#define __PU2_CN
#define __PU3_CN
#define __PU4_CN
#define __PU5_CN
#define __PU6_CN
#define __PU7_CN
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

#define SPI_MODULE_0 1
#define SPI_MODULE_1 2

#define SPI0_SCK_PA4_AF1 1
#define SPI0_SCK_PC5_AF3 1
#define SPI0_MISO_PA3_AF1 1
#define SPI0_MISO_PC4_AF3 1
#define SPI0_MOSI_PA2_AF1 1
#define SPI0_MOSI_PC3_AF3 1

#define SPI1_SCK_PG6_AF1 1
#define SPI1_MISO_PG4_AF1 1
#define SPI1_MOSI_PG5_AF1 1
#define SPI1_MOSI_PV1_AF2 1

#define PORT_COUNT (15)
#define PORT_SIZE (8)
//EOF GPIO

//IVT_TABLE

//EOF IVT_TABLE


#endif // _MCU_DEFINITIONS_H_
// ------------------------------------------------------------------------- END
