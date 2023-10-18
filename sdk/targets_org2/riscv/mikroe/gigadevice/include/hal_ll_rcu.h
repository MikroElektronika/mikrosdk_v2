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
 * @file  hal_ll_rcu.h
 * @brief Reset and Clock control unit defines necessary for HAL.
 */

#ifndef _HAL_LL_RCU_H_
#define _HAL_LL_RCU_H_

#ifdef __cplusplus
extern "C"{
#endif

#include <stdint.h>
#include "rcu_typedef.h"

/**
 *  Core register addresses used in source
 */

/* Clock enable registers. */
#define RCU_APB2EN  (( uint32_t * )0x40021018)
#define RCU_APB1EN  (( uint32_t * )0x4002101C)
#define RCU_AHBEN   (( uint32_t * )0x40021014)

/* Clock reset registers. */
#define RCU_APB1RST (( uint32_t * )0x40021010)
#define RCU_APB2RST (( uint32_t * )0x4002100C)
#define RCU_AHBRST  (( uint32_t * )0x40021028)

#ifdef __cplusplus
}
#endif

#endif // _HAL_LL_RCU_H_
// ------------------------------------------------------------------------- END
