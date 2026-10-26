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
* @file  mcu_reg_addresses.h
* @brief MCU specific register address definitions.
* @details R7F100LPL register address definitions.
*/

#ifndef _MCU_REG_ADDRESSES_H_
#define _MCU_REG_ADDRESSES_H_

// R7F100LPL REGISTER DEFINITIONS
#define GPIO_PORT0_BASE (0xFFF00UL)
#define GPIO_PORT1_BASE (0xFFF01UL)
#define GPIO_PORT2_BASE (0xFFF02UL)
#define GPIO_PORT3_BASE (0xFFF03UL)
#define GPIO_PORT4_BASE (0xFFF04UL)
#define GPIO_PORT5_BASE (0xFFF05UL)
#define GPIO_PORT6_BASE (0xFFF06UL)
#define GPIO_PORT7_BASE (0xFFF07UL)
#define GPIO_PORT8_BASE (0xFFF08UL)
#define GPIO_PORT9_BASE (0xFFF09UL)
#define GPIO_PORT12_BASE (0xFFF0CUL)
#define GPIO_PORT13_BASE (0xFFF0DUL)
#define GPIO_PORT14_BASE (0xFFF0EUL)
static const hal_ll_base_addr_t HAL_LL_ADC0_BASE_ADDR = ( hal_ll_base_addr_t ) (0xFFF30UL); // ADM0
static const hal_ll_base_addr_t HAL_LL_I2C0_BASE_ADDR = ( hal_ll_base_addr_t ) (0xFFF50UL); // IICA0
static const hal_ll_base_addr_t HAL_LL_SAU0_BASE_ADDR = ( hal_ll_base_addr_t ) (0xF0100UL); // SSR00
static const hal_ll_base_addr_t HAL_LL_SAU1_BASE_ADDR = ( hal_ll_base_addr_t ) (0xF0140UL); // SSR10
static const hal_ll_base_addr_t HAL_LL_SPI0_BASE_ADDR = ( hal_ll_base_addr_t ) (0xFFF10UL); // SDR00 (CSI00)
static const hal_ll_base_addr_t HAL_LL_SPI1_BASE_ADDR = ( hal_ll_base_addr_t ) (0xFFF12UL); // SDR01 (CSI01)
static const hal_ll_base_addr_t HAL_LL_SPI2_BASE_ADDR = ( hal_ll_base_addr_t ) (0xFFF44UL); // SDR02 (CSI10)
static const hal_ll_base_addr_t HAL_LL_SPI3_BASE_ADDR = ( hal_ll_base_addr_t ) (0xFFF46UL); // SDR03 (CSI11)
static const hal_ll_base_addr_t HAL_LL_SPI4_BASE_ADDR = ( hal_ll_base_addr_t ) (0xFFF48UL); // SDR10 (CSI20)
static const hal_ll_base_addr_t HAL_LL_SPI5_BASE_ADDR = ( hal_ll_base_addr_t ) (0xFFF4AUL); // SDR11 (CSI21)
static const hal_ll_base_addr_t HAL_LL_SPI6_BASE_ADDR = ( hal_ll_base_addr_t ) (0xFFF14UL); // SDR12 (CSI30)
static const hal_ll_base_addr_t HAL_LL_SPI7_BASE_ADDR = ( hal_ll_base_addr_t ) (0xFFF16UL); // SDR13 (CSI31)
static const hal_ll_base_addr_t HAL_LL_TAU0_BASE_ADDR = ( hal_ll_base_addr_t ) (0xF0190UL); // TMR00
static const hal_ll_base_addr_t HAL_LL_TIM0_BASE_ADDR = ( hal_ll_base_addr_t ) (0xFFF1AUL); // TDR01 (TO01 slave)
static const hal_ll_base_addr_t HAL_LL_TIM1_BASE_ADDR = ( hal_ll_base_addr_t ) (0xFFF66UL); // TDR03 (TO03 slave)
static const hal_ll_base_addr_t HAL_LL_TIM2_BASE_ADDR = ( hal_ll_base_addr_t ) (0xFFF6AUL); // TDR05 (TO05 slave)
static const hal_ll_base_addr_t HAL_LL_TIM3_BASE_ADDR = ( hal_ll_base_addr_t ) (0xFFF6EUL); // TDR07 (TO07 slave)
static const hal_ll_base_addr_t HAL_LL_UART0_BASE_ADDR = ( hal_ll_base_addr_t ) (0xFFF10UL); // SDR00 (TXD0)
static const hal_ll_base_addr_t HAL_LL_UART1_BASE_ADDR = ( hal_ll_base_addr_t ) (0xFFF44UL); // SDR02 (TXD1)
static const hal_ll_base_addr_t HAL_LL_UART2_BASE_ADDR = ( hal_ll_base_addr_t ) (0xFFF48UL); // SDR10 (TXD2)
static const hal_ll_base_addr_t HAL_LL_UART3_BASE_ADDR = ( hal_ll_base_addr_t ) (0xFFF14UL); // SDR12 (TXD3)
// EOF REGISTER DEFINITIONS

#endif // _MCU_REG_ADDRESSES_H_
// ------------------------------------------------------------------------- END
