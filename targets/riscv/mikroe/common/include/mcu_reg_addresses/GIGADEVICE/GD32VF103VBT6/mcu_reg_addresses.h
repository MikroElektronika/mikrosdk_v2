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
* @brief MCU specific RTC module required definitions.
* @details GD32VF103 RTC module definitions needed for proper
*          RTC functionality.
*/

#ifndef _RTC_DEFINITIONS_H_
#define _RTC_DEFINITIONS_H_

// GD32VF103 REGISTER DEFINITIONS
#define PMU_CTL_REG_ADDRESS (0x40007000UL)
#define RTC_CTL_REG_ADDRESS (0x40002804UL)
#define RTC_CNTL_REG_ADDRESS (0x4000281CUL)
#define RTC_CNTH_REG_ADDRESS (0x40002818UL)
#define RTC_INTEN_REG_ADDRESS (0x40002800UL)
#define RCU_APB1EN_REG_ADDRESS (0x4002101CUL)
#define RCU_BDCTL_REG_ADDRESS (0x40021020UL)
#define FWDGT_CTL_REG_ADDRESS (0x40003000UL)
#define FWDGT_PSC_REG_ADDRESS (0x40003004UL)
// EOF REGISTER DEFINITIONS

#endif // _RTC_DEFINITIONS_H_
// ------------------------------------------------------------------------- END
