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
* @details PIC32MX360F256L register address definitions.
*/

#ifndef _MCU_REG_ADDRESSES_H_
#define _MCU_REG_ADDRESSES_H_

// PIC32MX360F256L REGISTER DEFINITIONS
#define SYSKEY_REG_ADDRESS (0xBF80F230UL)
#define OSCCON_REG_ADDRESS (0xBF80F000UL)
#define RTCCON_REG_ADDRESS (0xBF800200UL)
#define RTCCONSET_REG_ADDRESS (0xBF800208UL)
#define RTCCONCLR_REG_ADDRESS (0xBF800204UL)
#define RTCDATE_REG_ADDRESS (0xBF800230UL)
#define RTCTIME_REG_ADDRESS (0xBF800220UL)
#define RTCALRMCLR_REG_ADDRESS (0xBF800214UL)
#define RSWRSTSET_REG_ADDRESS (0xBF80F618UL)
#define RSWRST_REG_ADDRESS (0xBF80F610UL)
#define IEC1CLR_REG_ADDRESS (0xBF881074UL)
#define IFS1CLR_REG_ADDRESS (0xBF881044UL)
#define IPC8CLR_REG_ADDRESS (0xBF881114UL)
#define INTCON_REG_ADDRESS (0xBF881000UL)
// EOF REGISTER DEFINITIONS

#endif // _MCU_REG_ADDRESSES_H_
// ------------------------------------------------------------------------- END
