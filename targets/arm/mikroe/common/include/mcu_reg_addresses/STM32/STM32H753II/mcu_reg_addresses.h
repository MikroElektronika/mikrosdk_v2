/****************************************************************************
**
** Copyright (C) 2024 MikroElektronika d.o.o.
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
** OF MERCHANTABILITY, EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED
** TO THE WARRANTIES FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT.
** IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM,
** DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT
** OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE
** OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
**
****************************************************************************/
/*!
* @file  mcu_reg_addresses.h
* @brief MCU specific register address definitions.
* @details STM32H753II register address definitions.
*/

#ifndef _MCU_REG_ADDRESSES_H_
#define _MCU_REG_ADDRESSES_H_

// STM32H753II REGISTER DEFINITIONS
#define RTC_WPR_REG_ADDRESS (0x58004024UL) 
#define RTC_ISR_REG_ADDRESS (0x5800400CUL) 
#define RTC_PRER_REG_ADDRESS (0x58004010UL) 
#define RTC_TR_REG_ADDRESS (0x58004000UL) 
#define RTC_DR_REG_ADDRESS (0x58004004UL) 
#define RTC_CR_REG_ADDRESS (0x58004008UL) 
#define RCC_APB4ENR_REG_ADDRESS (0x580244F4UL) 
#define RTC_BKP0R_REG_ADDRESS (0x58004050UL) 
#define RCC_BDCR_REG_ADDRESS (0x58024470UL) 
#define RCC_CSR_REG_ADDRESS (0x58024474UL) 
#define PWR_CR1_REG_ADDRESS (0x58024800UL) 
#define WWDG_CR_REG_ADDRESS (0x50003000UL)
#define IWDG_KR_REG_ADDRESS (0x58004800UL)
// EOF REGISTER DEFINITIONS

#endif // _MCU_REG_ADDRESSES_H_
// ------------------------------------------------------------------------- END
