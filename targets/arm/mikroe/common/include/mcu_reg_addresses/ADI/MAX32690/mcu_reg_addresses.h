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
* @details MAX32690 register address definitions.
*/

#ifndef _MCU_REG_ADDRESSES_H_
#define _MCU_REG_ADDRESSES_H_

// MAX32690 REGISTER DEFINITIONS
static const hal_ll_base_addr_t GPIO_PORT0_BASE = ( hal_ll_base_addr_t ) (0x40008000UL);
static const hal_ll_base_addr_t GPIO_PORT1_BASE = ( hal_ll_base_addr_t ) (0x40009000UL);
static const hal_ll_base_addr_t GPIO_PORT2_BASE = ( hal_ll_base_addr_t ) (0x4000A000UL);
static const hal_ll_base_addr_t GPIO_PORT3_BASE = ( hal_ll_base_addr_t ) (0x40080400UL);
static const hal_ll_base_addr_t GPIO_PORT4_BASE = ( hal_ll_base_addr_t ) (0x40006C20UL);
static const hal_ll_base_addr_t HAL_LL_ADC0_BASE_ADDR = ( hal_ll_base_addr_t ) (0x40034000UL);
static const hal_ll_base_addr_t HAL_LL_I2C0_BASE_ADDR = ( hal_ll_base_addr_t ) (0x4001D000UL);
static const hal_ll_base_addr_t HAL_LL_I2C1_BASE_ADDR = ( hal_ll_base_addr_t ) (0x4001E000UL);
static const hal_ll_base_addr_t HAL_LL_I2C2_BASE_ADDR = ( hal_ll_base_addr_t ) (0x4001F000UL);
static const hal_ll_base_addr_t HAL_LL_SPI0_BASE_ADDR = ( hal_ll_base_addr_t ) (0x40046000UL);
static const hal_ll_base_addr_t HAL_LL_SPI1_BASE_ADDR = ( hal_ll_base_addr_t ) (0x40047000UL);
static const hal_ll_base_addr_t HAL_LL_SPI2_BASE_ADDR = ( hal_ll_base_addr_t ) (0x40048000UL);
static const hal_ll_base_addr_t HAL_LL_SPI3_BASE_ADDR = ( hal_ll_base_addr_t ) (0x400BE000UL);
static const hal_ll_base_addr_t HAL_LL_SPI4_BASE_ADDR = ( hal_ll_base_addr_t ) (0x400BE400UL);
static const hal_ll_base_addr_t HAL_LL_TIM0_BASE_ADDR = ( hal_ll_base_addr_t ) (0x40010000UL);
static const hal_ll_base_addr_t HAL_LL_TIM1_BASE_ADDR = ( hal_ll_base_addr_t ) (0x40011000UL);
static const hal_ll_base_addr_t HAL_LL_TIM2_BASE_ADDR = ( hal_ll_base_addr_t ) (0x40012000UL);
static const hal_ll_base_addr_t HAL_LL_TIM3_BASE_ADDR = ( hal_ll_base_addr_t ) (0x40013000UL);
static const hal_ll_base_addr_t HAL_LL_TIM4_BASE_ADDR = ( hal_ll_base_addr_t ) (0x40080C00UL);
static const hal_ll_base_addr_t HAL_LL_TIM5_BASE_ADDR = ( hal_ll_base_addr_t ) (0x40081000UL);
static const hal_ll_base_addr_t HAL_LL_UART0_BASE_ADDR = ( hal_ll_base_addr_t ) (0x40042000UL);
static const hal_ll_base_addr_t HAL_LL_UART1_BASE_ADDR = ( hal_ll_base_addr_t ) (0x40043000UL);
static const hal_ll_base_addr_t HAL_LL_UART2_BASE_ADDR = ( hal_ll_base_addr_t ) (0x40044000UL);
static const hal_ll_base_addr_t HAL_LL_UART3_BASE_ADDR = ( hal_ll_base_addr_t ) (0x40081400UL);

// EOF REGISTER DEFINITIONS

#endif // _MCU_REG_ADDRESSES_H_
// ------------------------------------------------------------------------- END
