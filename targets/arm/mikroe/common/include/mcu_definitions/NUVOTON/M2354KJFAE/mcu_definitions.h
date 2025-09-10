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

#define ADC_MODULE_0 1

#define ADC_MODULE_COUNT 1
//EOF ADC

//I2C
#define I2C_MODULE_COUNT 3
//EOF I2C

//UART
#define UART_MODULE_COUNT 6
//EOF UART

//SPI
#define SPI_MODULE_COUNT 4
//EOF SPI

//TIM
#define TIM_MODULE_COUNT 6
//EOF TIM

//GPIO

// #define __PH15_CN
// #define __PH14_CN
// #define __PH13_CN
// #define __PH12_CN
#define __PH11_CN
#define __PH10_CN
#define __PH9_CN
#define __PH8_CN
#define __PH7_CN
#define __PH6_CN
#define __PH5_CN
#define __PH4_CN
// #define __PH3_CN
// #define __PH2_CN
// #define __PH1_CN
// #define __PH0_CN

#define __PG15_CN
#define __PG14_CN
#define __PG13_CN
#define __PG12_CN
#define __PG11_CN
#define __PG10_CN
#define __PG9_CN
// #define __PG8_CN
// #define __PG7_CN
// #define __PG6_CN
// #define __PG5_CN
#define __PG4_CN
#define __PG3_CN
#define __PG2_CN
// #define __PG1_CN
// #define __PG0_CN

// #define __PF15_CN
// #define __PF14_CN
// #define __PF13_CN
// #define __PF12_CN
#define __PF11_CN
#define __PF10_CN
#define __PF9_CN
#define __PF8_CN
#define __PF7_CN
#define __PF6_CN
#define __PF5_CN
#define __PF4_CN
#define __PF3_CN
#define __PF2_CN
#define __PF1_CN
#define __PF0_CN

#define __PE15_CN
#define __PE14_CN
#define __PE13_CN
#define __PE12_CN
#define __PE11_CN
#define __PE10_CN
#define __PE9_CN
#define __PE8_CN
#define __PE7_CN
#define __PE6_CN
#define __PE5_CN
#define __PE4_CN
#define __PE3_CN
#define __PE2_CN
#define __PE1_CN
#define __PE0_CN

// #define __PD15_CN
#define __PD14_CN
// #define __PD13_CN
#define __PD12_CN
#define __PD11_CN
#define __PD10_CN
#define __PD9_CN
#define __PD8_CN
#define __PD7_CN
#define __PD6_CN
#define __PD5_CN
#define __PD4_CN
#define __PD3_CN
#define __PD2_CN
#define __PD1_CN
#define __PD0_CN

// #define __PC15_CN
// #define __PC14_CN
#define __PC13_CN
#define __PC12_CN
#define __PC11_CN
#define __PC10_CN
#define __PC9_CN
#define __PC8_CN
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
#define __PORT_E_CN
#define __PORT_F_CN
#define __PORT_G_CN
#define __PORT_H_CN

#define PORT_SIZE (16)
#define PORT_COUNT (8)
//EOF GPIO

//IVT_TABLE

//EOF IVT_TABLE


#endif // _MCU_DEFINITIONS_H_
// ------------------------------------------------------------------------- END