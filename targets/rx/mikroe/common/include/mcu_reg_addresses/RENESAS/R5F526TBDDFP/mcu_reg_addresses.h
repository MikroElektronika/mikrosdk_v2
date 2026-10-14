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
* @details R5F526TBDDFP register address definitions.
*/

#ifndef _MCU_REG_ADDRESSES_H_
#define _MCU_REG_ADDRESSES_H_

// R5F526TBDDFP REGISTER DEFINITIONS
#define GPIO_PORT0_BASE (0x8C000UL)
#define GPIO_PORT1_BASE (0x8C001UL)
#define GPIO_PORT2_BASE (0x8C002UL)
#define GPIO_PORT3_BASE (0x8C003UL)
#define GPIO_PORT4_BASE (0x8C004UL)
#define GPIO_PORT5_BASE (0x8C005UL)
#define GPIO_PORT6_BASE (0x8C006UL)
#define GPIO_PORT7_BASE (0x8C007UL)
#define GPIO_PORT8_BASE (0x8C008UL)
#define GPIO_PORT9_BASE (0x8C009UL)
#define GPIO_PORTA_BASE (0x8C00AUL)
#define GPIO_PORTB_BASE (0x8C00BUL)
#define GPIO_PORTD_BASE (0x8C00DUL)
#define GPIO_PORTE_BASE (0x8C00EUL)
#define GPIO_PORTN_BASE (0x8C016UL)
static const hal_ll_base_addr_t HAL_LL_ADC0_BASE_ADDR = ( hal_ll_base_addr_t ) (0x89000UL);
static const hal_ll_base_addr_t HAL_LL_ADC1_BASE_ADDR = ( hal_ll_base_addr_t ) (0x89200UL);
static const hal_ll_base_addr_t HAL_LL_ADC2_BASE_ADDR = ( hal_ll_base_addr_t ) (0x89400UL);
static const hal_ll_base_addr_t HAL_LL_SCI1_BASE_ADDR = ( hal_ll_base_addr_t ) (0x8A020UL);
static const hal_ll_base_addr_t HAL_LL_SCI5_BASE_ADDR = ( hal_ll_base_addr_t ) (0x8A0A0UL);
static const hal_ll_base_addr_t HAL_LL_SCI6_BASE_ADDR = ( hal_ll_base_addr_t ) (0x8A0C0UL);
static const hal_ll_base_addr_t HAL_LL_SCI8_BASE_ADDR = ( hal_ll_base_addr_t ) (0xA1400UL);
static const hal_ll_base_addr_t HAL_LL_SCI9_BASE_ADDR = ( hal_ll_base_addr_t ) (0xA1480UL);
static const hal_ll_base_addr_t HAL_LL_SCI11_BASE_ADDR = ( hal_ll_base_addr_t ) (0xE2080UL);
static const hal_ll_base_addr_t HAL_LL_SCI12_BASE_ADDR = ( hal_ll_base_addr_t ) (0x8B300UL);
static const hal_ll_base_addr_t HAL_LL_TIM0_BASE_ADDR = ( hal_ll_base_addr_t ) (0xC2000UL);
static const hal_ll_base_addr_t HAL_LL_TIM1_BASE_ADDR = ( hal_ll_base_addr_t ) (0xC2100UL);
static const hal_ll_base_addr_t HAL_LL_TIM2_BASE_ADDR = ( hal_ll_base_addr_t ) (0xC2200UL);
static const hal_ll_base_addr_t HAL_LL_TIM3_BASE_ADDR = ( hal_ll_base_addr_t ) (0xC2300UL);
static const hal_ll_base_addr_t HAL_LL_TIM4_BASE_ADDR = ( hal_ll_base_addr_t ) (0xC2400UL);
static const hal_ll_base_addr_t HAL_LL_TIM5_BASE_ADDR = ( hal_ll_base_addr_t ) (0xC2500UL);
static const hal_ll_base_addr_t HAL_LL_TIM6_BASE_ADDR = ( hal_ll_base_addr_t ) (0xC2600UL);
static const hal_ll_base_addr_t HAL_LL_TIM7_BASE_ADDR = ( hal_ll_base_addr_t ) (0xC2700UL);
static const hal_ll_base_addr_t HAL_LL_I2C0_BASE_ADDR = ( hal_ll_base_addr_t ) (0x88300UL);
static const hal_ll_base_addr_t HAL_LL_I3C0_BASE_ADDR = ( hal_ll_base_addr_t ) (0xEC000UL);
static const hal_ll_base_addr_t HAL_LL_SPI0_MASTER_BASE_ADDR = ( hal_ll_base_addr_t ) (0xD0100UL);
static const hal_ll_base_addr_t HAL_LL_SPI1_MASTER_BASE_ADDR = ( hal_ll_base_addr_t ) (0xE2800UL);
// EOF REGISTER DEFINITIONS

#endif // _MCU_REG_ADDRESSES_H_
// ------------------------------------------------------------------------- END
