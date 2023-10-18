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
* @details MK20DX128VLF5 RTC module definitions needed for proper
*          RTC functionality.
*/

#ifndef _RTC_DEFINITIONS_H_
#define _RTC_DEFINITIONS_H_

// RTC
#define SIM_SCGC6_REG_ADDRESS (0x4004803C) 
#define RTC_TSR_REG_ADDRESS (0x4003D000) 
#define RTC_CR_REG_ADDRESS (0x4003D010) 
#define RTC_SR_REG_ADDRESS (0x4003D014) 
#define RTC_IER_REG_ADDRESS (0x4003D01C) 
#define RTC_TAR_REG_ADDRESS (0x4003D008) 
#define WDOG_REFRESH_REG_ADDRESS (0x4005200C) 
#define WDOG_STCTRLH_REG_ADDRESS (0x40052000) 
#define WDOG_UNLOCK_REG_ADDRESS (0x4005200E) 
#define WDOG_TOVALH_REG_ADDRESS (0x40052004) 
#define WDOG_TOVALL_REG_ADDRESS (0x40052006)
// EOF RTC

#endif // _RTC_DEFINITIONS_H_
// ------------------------------------------------------------------------- END
