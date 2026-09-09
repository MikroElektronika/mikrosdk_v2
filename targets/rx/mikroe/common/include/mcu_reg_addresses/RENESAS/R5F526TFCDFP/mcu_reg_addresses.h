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
* @details R5F526TFCDFP register address definitions.
*/

#ifndef _MCU_REG_ADDRESSES_H_
#define _MCU_REG_ADDRESSES_H_

// R5F526TFCDFP REGISTER DEFINITIONS
#define GPIO_PORT0_BASE (0x0008C000UL)
#define GPIO_PORT1_BASE (0x0008C001UL)
#define GPIO_PORT2_BASE (0x0008C002UL)
#define GPIO_PORT3_BASE (0x0008C003UL)
#define GPIO_PORT4_BASE (0x0008C004UL)
#define GPIO_PORT5_BASE (0x0008C005UL)
#define GPIO_PORT6_BASE (0x0008C006UL)
#define GPIO_PORT7_BASE (0x0008C007UL)
#define GPIO_PORT8_BASE (0x0008C008UL)
#define GPIO_PORT9_BASE (0x0008C009UL)
#define GPIO_PORTA_BASE (0x0008C00AUL)
#define GPIO_PORTB_BASE (0x0008C00BUL)
#define GPIO_PORTD_BASE (0x0008C00DUL)
#define GPIO_PORTE_BASE (0x0008C00EUL)
#define GPIO_PORTN_BASE (0x0008C016UL)
// TODO: the following addresses are not valid for RX26T, they are just placeholders for now
static const hal_ll_base_addr_t HAL_LL_ADC0_BASE_ADDR = ( hal_ll_base_addr_t ) (0x400A1800UL);
static const hal_ll_base_addr_t HAL_LL_I2C0_BASE_ADDR = ( hal_ll_base_addr_t ) (0x400A3000UL);
static const hal_ll_base_addr_t HAL_LL_ICU_BASE_ADDR = ( hal_ll_base_addr_t ) (0x40006000UL);
static const hal_ll_base_addr_t HAL_LL_SAU0_BASE_ADDR = ( hal_ll_base_addr_t ) (0x400A2000UL);
static const hal_ll_base_addr_t HAL_LL_SAU1_BASE_ADDR = ( hal_ll_base_addr_t ) (0x400A2200UL);
static const hal_ll_base_addr_t HAL_LL_TIM0_BASE_ADDR = ( hal_ll_base_addr_t ) (0x400A2600UL);
static const hal_ll_base_addr_t HAL_LL_UARTA0_BASE_ADDR = ( hal_ll_base_addr_t ) (0x400A3400UL);
// EOF REGISTER DEFINITIONS

#endif // _MCU_REG_ADDRESSES_H_
// ------------------------------------------------------------------------- END
