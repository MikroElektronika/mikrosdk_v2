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
 * @brief MCU specific pin and module definitions for STM32C011D6_WLCSP12.
 */

#ifndef _MCU_DEFINITIONS_H_
#define _MCU_DEFINITIONS_H_

#ifdef __cplusplus
extern "C"{
#endif

#include "mcu_reg_addresses.h"

// Defined only the pins used for testing
#define __P212_CN
#define __P211_CN
#define __P113_CN
#define __P229_CN
#define __P227_CN
#define __P228_CN
#define __P208_CN
#define __P207_CN
#define __P300_CN
// ADC
#define ADC0_P300_AN000

#define ADC_MODULE_0 (1)

#define ADC_MODULE_COUNT (1)
// EOF ADC

// I2C
#define I2C0_SDA_P207_AF7
#define I2C0_SCL_P208_AF7

#define I2C_MODULE_0 (1)

#define I2C_MODULE_COUNT (1)
// EOF I2C

// U(S)ART
#define UART0_TX_P212_AF1
#define UART0_RX_P211_AF1

#define UART_MODULE_0 (1)

#define UART_MODULE_COUNT (1)
// EOF U(S)ART

// SPI
#define SPI0_SCK_P229_AF2
#define SPI0_MISO_P227_AF2
#define SPI0_MOSI_P228_AF2

#define SPI_MODULE_0 (1)

#define SPI_MODULE_COUNT (1)
// EOF SPI

// TIM
#define TIM0_P113_CHA_AF1

#define TIM_MODULE_0 (1)

#define TIM_MODULE_COUNT (1)

// EOF TIM

// GPIO
#define __P000_CN_

#define PORT_COUNT (6)
#define PORT_SIZE  (16)
// EOF GPIO

// IVT_TABLE
#define UART1_IVT (27)
#define UART1_NVIC (43)
#define UART2_IVT (28)
#define UART2_NVIC (44)
// EOF IVT_TABLE

#ifdef __cplusplus
}
#endif

#endif // _MCU_DEFINITIONS_H_
// ------------------------------------------------------------------------- END
