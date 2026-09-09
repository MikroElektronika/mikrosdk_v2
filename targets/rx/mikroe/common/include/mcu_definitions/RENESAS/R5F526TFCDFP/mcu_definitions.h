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

// TODO: Invalid content of this file, only GPIO was tested.
//GPIO
#define __P200_CN
#define __P201_CN
#define __P501_CN
#define __PB1_CN
#define __PE2_CN

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
#define __PORT_A_CN
#define __PORT_B_CN
#define __PORT_D_CN
#define __PORT_E_CN
#define __PORT_N_CN

#define PORT_SIZE (16)
#define PORT_COUNT (14)
//EOF GPIO

//ADC

#define ADC_MODULE_0 1

#define ADC_MODULE_COUNT 1
//EOF ADC

//SAU_I2C
#define SAU_I2C_MODULE_0 1
#define SAU_I2C_MODULE_1 2

 #define SAU_I2C_MODULE_COUNT 2
//EOF SAU_I2C

//SAU_SPI

#define SAU_SPI_MODULE_0 1
#define SAU_SPI_MODULE_1 2

 #define SAU_SPI_MODULE_COUNT 2
//EOF SAU_SPI

//SAU_UART
#define SAU_UART_CHANNEL_0
#define SAU_UART_CHANNEL_1
#define SAU_UART_CHANNEL_2
#define SAU_UART_MODULE_0 1
#define SAU_UART_MODULE_1 2

 #define SAU_UART_MODULE_COUNT 2
//EOF SAU_UART

//I2C

#define I2C_MODULE_0 3

#define I2C_MODULE_COUNT (SAU_I2C_MODULE_COUNT + 1)
//EOF I2C

//UART

#define UART_MODULE_0 3

#define UART_MODULE_COUNT (SAU_UART_MODULE_COUNT + 1)
//EOF UART

//SPI
#define SPI_MODULE_COUNT (SAU_SPI_MODULE_COUNT + 0)
//EOF SPI

//TIM

#define TIM_MODULE_0 1

#define TIM_MODULE_COUNT 1
//EOF TIM

//IVT_TABLE
#define SAU1_UART_TXI2_NVIC    12
#define SAU1_UART_RXI2_NVIC    13
#define SAU0_UART_TXI0_NVIC    18
#define SAU0_UART_TXI1_NVIC    22
#define SAU0_UART_RXI1_NVIC    23
#define SAU0_UART_RXI0_NVIC    27
#define UARTA0_ERRI_NVIC       39
#define UARTA0_TXI_NVIC        40
#define UARTA0_RXI_NVIC        41
#define UARTA1_ERRI_NVIC       43
#define UARTA1_TXI_NVIC        44
#define UARTA1_RXI_NVIC        45
//EOF IVT_TABLE

#endif // _MCU_DEFINITIONS_H_
// ------------------------------------------------------------------------- END
