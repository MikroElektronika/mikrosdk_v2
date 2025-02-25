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
* @details PIC32MZ2048EFH124 register address definitions.
*/

#ifndef _MCU_REG_ADDRESSES_H_
#define _MCU_REG_ADDRESSES_H_

// PIC32MZ2048EFH124 REGISTER DEFINITIONS
#define SYSKEY_REG_ADDRESS (0xBF800030UL)
#define OSCCON_REG_ADDRESS (0xBF801200UL)
#define RTCCON_REG_ADDRESS (0xBF800C00UL)
#define RTCCONSET_REG_ADDRESS (0xBF800C08UL)
#define RTCCONCLR_REG_ADDRESS (0xBF800C04UL)
#define RTCDATE_REG_ADDRESS (0xBF800C30UL)
#define RTCTIME_REG_ADDRESS (0xBF800C20UL)
#define RTCALRMCLR_REG_ADDRESS (0xBF800C14UL)
#define RSWRSTSET_REG_ADDRESS (0xBF801258UL)
#define RSWRST_REG_ADDRESS (0xBF801250UL)
#define IEC1CLR_REG_ADDRESS (0xBF8100D4UL)
#define IFS1CLR_REG_ADDRESS (0xBF810054UL)
#define IPC8CLR_REG_ADDRESS (0xBF8101C4UL)
#define INTCON_REG_ADDRESS (0xBF810000UL)
#define PRISS_REG_ADDRESS (0xBF810010UL)
// EOF REGISTER DEFINITIONS

#endif // _MCU_REG_ADDRESSES_H_
// ------------------------------------------------------------------------- END
