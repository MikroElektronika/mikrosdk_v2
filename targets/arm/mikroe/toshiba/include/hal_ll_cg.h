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
 * @file  hal_ll_cg.h
 * @brief Reset and Clock control defines necessary for HAL.
 */

#ifndef _HAL_LL_CG_H_
#define _HAL_LL_CG_H_

#include "hal_ll_target_names.h"
#ifdef __cplusplus
extern "C"{
#endif

#include <stdint.h>

/*!< @brief Base address for clock control registers */
#define HAL_LL_CG_BASE_ADDR              0x40083048UL
#define HAL_LL_CG_BASE_FSYSMENA_ADDR     0x40083048UL
#define HAL_LL_CG_BASE_FSYSMENB_ADDR     0x4008304CUL
#define HAL_LL_CG_BASE_FSYSENA_ADDR      0x40083050UL

/*!< @brief Clock Generator register structure. */
typedef struct {
    volatile uint32_t FSYSMENA;   // 0x40083048 - Function System Module Enable A
    volatile uint32_t FSYSMENB;   // 0x4008304C - Function System Module Enable B
    volatile uint32_t FSYSENA;    // 0x40083050 - Function System Enable A
} hal_ll_cg_base_handle_t;

#ifdef __cplusplus
}
#endif

#endif // _HAL_LL_MSTPCR_H_
// ------------------------------------------------------------------------- END
