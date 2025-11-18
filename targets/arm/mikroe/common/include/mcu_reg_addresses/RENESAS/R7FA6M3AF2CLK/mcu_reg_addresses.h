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
* @details R7FA6M3AF2CLK register address definitions.
*/

#ifndef _MCU_REG_ADDRESSES_H_
#define _MCU_REG_ADDRESSES_H_

// R7FA6M3AF2CLK REGISTER DEFINITIONS
#define HAL_LL_ADC0_ADPGACR_REG_ADDR ((uint16_t *) 0x4005C1A0UL)
#define HAL_LL_ADC1_ADPGACR_REG_ADDR ((uint16_t *) 0x4005C3A0UL)
#define HAL_LL_ADC0_ADPGAGS0_REG_ADDR ((uint16_t *) 0x4005C1A2UL)
#define HAL_LL_ADC1_ADPGAGS0_REG_ADDR ((uint16_t *) 0x4005C3A2UL)
#define HAL_LL_ADC0_ADPGADCR0_REG_ADDR ((uint16_t *) 0x4005C1B0UL)
#define HAL_LL_ADC1_ADPGADCR0_REG_ADDR ((uint16_t *) 0x4005C3B0UL)
#define HAL_LL_ICU_IELSR_BASE_ADDRESS (0x4005C300UL)
static const hal_ll_base_addr_t HAL_LL_ADC0_BASE_ADDR = ( hal_ll_base_addr_t ) (0x4005C000UL);
static const hal_ll_base_addr_t HAL_LL_ADC1_BASE_ADDR = ( hal_ll_base_addr_t ) (0x4005C200UL);
static const hal_ll_base_addr_t HAL_LL_TIM0_BASE_ADDR = ( hal_ll_base_addr_t ) (0x40078000UL);
static const hal_ll_base_addr_t HAL_LL_TIM1_BASE_ADDR = ( hal_ll_base_addr_t ) (0x40078100UL);
static const hal_ll_base_addr_t HAL_LL_TIM2_BASE_ADDR = ( hal_ll_base_addr_t ) (0x40078200UL);
static const hal_ll_base_addr_t HAL_LL_TIM3_BASE_ADDR = ( hal_ll_base_addr_t ) (0x40078300UL);
static const hal_ll_base_addr_t HAL_LL_TIM4_BASE_ADDR = ( hal_ll_base_addr_t ) (0x40078400UL);
static const hal_ll_base_addr_t HAL_LL_TIM5_BASE_ADDR = ( hal_ll_base_addr_t ) (0x40078500UL);
static const hal_ll_base_addr_t HAL_LL_TIM6_BASE_ADDR = ( hal_ll_base_addr_t ) (0x40078600UL);
static const hal_ll_base_addr_t HAL_LL_TIM7_BASE_ADDR = ( hal_ll_base_addr_t ) (0x40078700UL);
static const hal_ll_base_addr_t HAL_LL_TIM8_BASE_ADDR = ( hal_ll_base_addr_t ) (0x40078800UL);
static const hal_ll_base_addr_t HAL_LL_TIM9_BASE_ADDR = ( hal_ll_base_addr_t ) (0x40078900UL);
static const hal_ll_base_addr_t HAL_LL_TIM10_BASE_ADDR = ( hal_ll_base_addr_t ) (0x40078A00UL);
static const hal_ll_base_addr_t HAL_LL_TIM11_BASE_ADDR = ( hal_ll_base_addr_t ) (0x40078B00UL);
static const hal_ll_base_addr_t HAL_LL_TIM12_BASE_ADDR = ( hal_ll_base_addr_t ) (0x40078C00UL);
static const hal_ll_base_addr_t HAL_LL_TIM13_BASE_ADDR = ( hal_ll_base_addr_t ) (0x40078D00UL);
static const hal_ll_base_addr_t HAL_LL_I2C0_BASE_ADDR = ( hal_ll_base_addr_t ) (0x40053000UL);
static const hal_ll_base_addr_t HAL_LL_I2C1_BASE_ADDR = ( hal_ll_base_addr_t ) (0x40053100UL);
static const hal_ll_base_addr_t HAL_LL_I2C2_BASE_ADDR = ( hal_ll_base_addr_t ) (0x40053200UL);
#define GPIO_PORT0_BASE (0x40040000UL)
#define GPIO_PORT1_BASE (0x40040020UL)
#define GPIO_PORT2_BASE (0x40040040UL)
#define GPIO_PORT3_BASE (0x40040060UL)
#define GPIO_PORT4_BASE (0x40040080UL)
#define GPIO_PORT5_BASE (0x400400A0UL)
#define GPIO_PORT6_BASE (0x400400C0UL)
#define GPIO_PORT7_BASE (0x400400E0UL)
#define GPIO_PORT8_BASE (0x40040100UL)
#define GPIO_PORT9_BASE (0x40040120UL)
#define GPIO_PORT10_BASE (0x40040140UL)
#define GPIO_PORT11_BASE (0x40040160UL)
#define GPIO_PORT12_BASE (0x40040180UL)
#define GPIO_PORT13_BASE (0x400401A0UL)
#define GPIO_PORT14_BASE (0x400401C0UL)
static const hal_ll_base_addr_t HAL_LL_UART0_BASE_ADDRESS = ( hal_ll_base_addr_t ) (0x40070000UL);
static const hal_ll_base_addr_t HAL_LL_UART1_BASE_ADDRESS = ( hal_ll_base_addr_t ) (0x40070020UL);
static const hal_ll_base_addr_t HAL_LL_UART2_BASE_ADDRESS = ( hal_ll_base_addr_t ) (0x40070040UL);
static const hal_ll_base_addr_t HAL_LL_UART3_BASE_ADDRESS = ( hal_ll_base_addr_t ) (0x40070060UL);
static const hal_ll_base_addr_t HAL_LL_UART4_BASE_ADDRESS = ( hal_ll_base_addr_t ) (0x40070080UL);
static const hal_ll_base_addr_t HAL_LL_UART5_BASE_ADDRESS = ( hal_ll_base_addr_t ) (0x400700A0UL);
static const hal_ll_base_addr_t HAL_LL_UART6_BASE_ADDRESS = ( hal_ll_base_addr_t ) (0x400700C0UL);
static const hal_ll_base_addr_t HAL_LL_UART7_BASE_ADDRESS = ( hal_ll_base_addr_t ) (0x400700E0UL);
static const hal_ll_base_addr_t HAL_LL_UART8_BASE_ADDRESS = ( hal_ll_base_addr_t ) (0x40070100UL);
static const hal_ll_base_addr_t HAL_LL_UART9_BASE_ADDRESS = ( hal_ll_base_addr_t ) (0x40070120UL);
static const hal_ll_base_addr_t HAL_LL_SPI0_MASTER_BASE_ADDR = ( hal_ll_base_addr_t ) (0x40072000UL);
static const hal_ll_base_addr_t HAL_LL_SPI1_MASTER_BASE_ADDR = ( hal_ll_base_addr_t ) (0x40072100UL);
static const hal_ll_base_addr_t HAL_LL_SPI2_MASTER_BASE_ADDR = ( hal_ll_base_addr_t ) (0x40072200UL);
// EOF REGISTER DEFINITIONS

#endif // _MCU_REG_ADDRESSES_H_
// ------------------------------------------------------------------------- END
