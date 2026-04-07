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
* @details R7FA8M1AHECFB register address definitions.
*/

#ifndef _MCU_REG_ADDRESSES_H_
#define _MCU_REG_ADDRESSES_H_

// R7FA8M1AHECFB REGISTER DEFINITIONS
#define GPIO_PORT0_BASE (0x40400000UL)
#define GPIO_PORT10_BASE (0x40400140UL)
#define GPIO_PORT11_BASE (0x40400160UL)
#define GPIO_PORT12_BASE (0x40400180UL)
#define GPIO_PORT13_BASE (0x404001A0UL)
#define GPIO_PORT14_BASE (0x404001C0UL)
#define GPIO_PORT1_BASE (0x40400020UL)
#define GPIO_PORT2_BASE (0x40400040UL)
#define GPIO_PORT3_BASE (0x40400060UL)
#define GPIO_PORT4_BASE (0x40400080UL)
#define GPIO_PORT5_BASE (0x404000A0UL)
#define GPIO_PORT6_BASE (0x404000C0UL)
#define GPIO_PORT7_BASE (0x404000E0UL)
#define GPIO_PORT8_BASE (0x40400100UL)
#define GPIO_PORT9_BASE (0x40400120UL)
#define HAL_LL_ADC0_ADPGACR_REG_ADDR ((uint16_t *) 0x403321A0UL)
#define HAL_LL_ADC0_ADPGADCR0_REG_ADDR ((uint16_t *) 0x403321B0UL)
#define HAL_LL_ADC0_ADPGAGS0_REG_ADDR ((uint16_t *) 0x403321A2UL)
#define HAL_LL_ADC1_ADPGACR_REG_ADDR ((uint16_t *) 0x403323A0UL)
#define HAL_LL_ADC1_ADPGADCR0_REG_ADDR ((uint16_t *) 0x403323B0UL)
#define HAL_LL_ADC1_ADPGAGS0_REG_ADDR ((uint16_t *) 0x403323A2UL)
#define HAL_LL_ICU_IELSR_BASE_ADDRESS (0x4000C300UL)
#define PFS_REGISTER_ADDR (GPIO_PORT0_BASE + 0x00000800UL)
#define PWPR_REGISTER_BASE (* ( volatile uint8_t * )(GPIO_PORT0_BASE + 0x00000D14UL))
static const hal_ll_base_addr_t HAL_LL_ADC0_BASE_ADDR = ( hal_ll_base_addr_t ) (0x40332000UL);
static const hal_ll_base_addr_t HAL_LL_ADC1_BASE_ADDR = ( hal_ll_base_addr_t ) (0x40332200UL);
static const hal_ll_base_addr_t HAL_LL_I2C0_BASE_ADDR = ( hal_ll_base_addr_t ) (0x4025E000UL);
static const hal_ll_base_addr_t HAL_LL_I2C1_BASE_ADDR = ( hal_ll_base_addr_t ) (0x4025E100UL);
static const hal_ll_base_addr_t HAL_LL_I2C2_BASE_ADDR = ( hal_ll_base_addr_t ) (0x4025E200UL);
static const hal_ll_base_addr_t HAL_LL_ICU_BASE_ADDR = ( hal_ll_base_addr_t ) (0x40006000UL);
static const hal_ll_base_addr_t HAL_LL_SCI0_BASE_ADDR = ( hal_ll_base_addr_t ) (0x40358000UL);
static const hal_ll_base_addr_t HAL_LL_SCI1_BASE_ADDR = ( hal_ll_base_addr_t ) (0x40358100UL);
static const hal_ll_base_addr_t HAL_LL_SCI2_BASE_ADDR = ( hal_ll_base_addr_t ) (0x40358200UL);
static const hal_ll_base_addr_t HAL_LL_SCI3_BASE_ADDR = ( hal_ll_base_addr_t ) (0x40358300UL);
static const hal_ll_base_addr_t HAL_LL_SCI4_BASE_ADDR = ( hal_ll_base_addr_t ) (0x40358400UL);
static const hal_ll_base_addr_t HAL_LL_SCI5_BASE_ADDR = ( hal_ll_base_addr_t ) (0x40358500UL);
static const hal_ll_base_addr_t HAL_LL_SCI6_BASE_ADDR = ( hal_ll_base_addr_t ) (0x40358600UL);
static const hal_ll_base_addr_t HAL_LL_SCI7_BASE_ADDR = ( hal_ll_base_addr_t ) (0x40358700UL);
static const hal_ll_base_addr_t HAL_LL_SCI8_BASE_ADDR = ( hal_ll_base_addr_t ) (0x40358800UL);
static const hal_ll_base_addr_t HAL_LL_SCI9_BASE_ADDR = ( hal_ll_base_addr_t ) (0x40358900UL);
static const hal_ll_base_addr_t HAL_LL_SPI0_MASTER_BASE_ADDR = ( hal_ll_base_addr_t ) (0x4035C000UL);
static const hal_ll_base_addr_t HAL_LL_SPI1_MASTER_BASE_ADDR = ( hal_ll_base_addr_t ) (0x4035C100UL);
static const hal_ll_base_addr_t HAL_LL_SPI2_MASTER_BASE_ADDR = ( hal_ll_base_addr_t ) (0x4035C200UL);
static const hal_ll_base_addr_t HAL_LL_TIM0_BASE_ADDR = ( hal_ll_base_addr_t ) (0x40322000UL);
static const hal_ll_base_addr_t HAL_LL_TIM10_BASE_ADDR = ( hal_ll_base_addr_t ) (0x40322A00UL);
static const hal_ll_base_addr_t HAL_LL_TIM11_BASE_ADDR = ( hal_ll_base_addr_t ) (0x40322B00UL);
static const hal_ll_base_addr_t HAL_LL_TIM12_BASE_ADDR = ( hal_ll_base_addr_t ) (0x40322C00UL);
static const hal_ll_base_addr_t HAL_LL_TIM13_BASE_ADDR = ( hal_ll_base_addr_t ) (0x40322D00UL);
static const hal_ll_base_addr_t HAL_LL_TIM1_BASE_ADDR = ( hal_ll_base_addr_t ) (0x40322100UL);
static const hal_ll_base_addr_t HAL_LL_TIM2_BASE_ADDR = ( hal_ll_base_addr_t ) (0x40322200UL);
static const hal_ll_base_addr_t HAL_LL_TIM3_BASE_ADDR = ( hal_ll_base_addr_t ) (0x40322300UL);
static const hal_ll_base_addr_t HAL_LL_TIM4_BASE_ADDR = ( hal_ll_base_addr_t ) (0x40322400UL);
static const hal_ll_base_addr_t HAL_LL_TIM5_BASE_ADDR = ( hal_ll_base_addr_t ) (0x40322500UL);
static const hal_ll_base_addr_t HAL_LL_TIM6_BASE_ADDR = ( hal_ll_base_addr_t ) (0x40322600UL);
static const hal_ll_base_addr_t HAL_LL_TIM7_BASE_ADDR = ( hal_ll_base_addr_t ) (0x40322700UL);
static const hal_ll_base_addr_t HAL_LL_TIM8_BASE_ADDR = ( hal_ll_base_addr_t ) (0x40322800UL);
static const hal_ll_base_addr_t HAL_LL_TIM9_BASE_ADDR = ( hal_ll_base_addr_t ) (0x40322900UL);
// EOF REGISTER DEFINITIONS

#endif // _MCU_REG_ADDRESSES_H_
// ------------------------------------------------------------------------- END
