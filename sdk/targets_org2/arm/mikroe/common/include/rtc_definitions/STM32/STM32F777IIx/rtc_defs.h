/****************************************************************************
**
** Copyright (C) 2023 MikroElektronika d.o.o.
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
* @file  rtc_definitions.h
* @brief MCU specific RTC module required definitions.
* @details STM32F777II RTC module definitions needed for proper
*          RTC functionality.
*/

#ifndef _RTC_DEFINITIONS_H_
#define _RTC_DEFINITIONS_H_

// RTC
#define RTC_WPR_REG_ADDRESS (0x40002824) 
#define RTC_ISR_REG_ADDRESS (0x4000280C) 
#define RTC_PRER_REG_ADDRESS (0x40002810) 
#define RTC_TR_REG_ADDRESS (0x40002800) 
#define RTC_DR_REG_ADDRESS (0x40002804) 
#define RTC_CR_REG_ADDRESS (0x40002808) 
#define RCC_APB1ENR_REG_ADDRESS (0x40023840) 
#define PWR_CR1_REG_ADDRESS (0x40007000) 
#define RCC_BDCR_REG_ADDRESS (0x40023870) 
#define IWDG_KR_REG_ADDRESS (0x40003000) 
#define IWDG_PR_REG_ADDRESS (0x40003004) 
#define IWDG_RLR_REG_ADDRESS (0x40003008) 
#define IWDG_SR_REG_ADDRESS (0x4000300C) 
#define RTC_BKP0R_REG_ADDRESS (0x40002850) 
#define RTC_BKP1R_REG_ADDRESS (0x40002854)
// EOF RTC

#endif // _RTC_DEFINITIONS_H_
// ------------------------------------------------------------------------- END
