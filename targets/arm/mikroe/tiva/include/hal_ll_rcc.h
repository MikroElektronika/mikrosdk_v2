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
 * @file  hal_ll_rcc.h
 * @brief Reset and Clock control defines necessary for HAL.
 */

#ifndef _HAL_LL_RCC_H_
#define _HAL_LL_RCC_H_

#ifdef __cplusplus
extern "C"{
#endif

#include <stdint.h>

/**
 *  Core register addresses used in source.
 */
#define _SYSCTL_RCGCGPIO    ( uint32_t * )0x400FE608
#define _SYSCTL_GPIOHBCTL   ( uint32_t * )0x400FE06C
#define _SYSCTL_RCGCSSI     ( uint32_t * )0x400FE61C
#define _SYSCTL_RCGCTIMER   ( uint32_t * )0x400FE604
#define _SYSCTL_RCGCUART    ( uint32_t * )0x400FE618
#define _SYSCTL_RCGCI2C     ( uint32_t * )0x400FE620
#define _SYSCTL_RCGCADC     ( uint32_t * )0x400FE638
#define _SYSCTL_RCGCCAN     ( uint32_t * )0x400FE634

#ifdef __cplusplus
}
#endif

#endif // _HAL_LL_RCC_H_
// ------------------------------------------------------------------------- END
