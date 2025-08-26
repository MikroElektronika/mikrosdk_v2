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
#define HAL_LL_CG_BASE_ADDR              0x40083000UL
#define HAL_LL_CG_BASE_PROTECT_ADDR      0x40083000UL
#define HAL_LL_CG_BASE_OSCCR_ADDR        0x40083004UL
#define HAL_LL_CG_BASE_SYSCR_ADDR        0x40083008UL
#define HAL_LL_CG_BASE_STBYCR_ADDR       0x4008300CUL
#define HAL_LL_CG_BASE_PLL0SEL_ADDR      0x40083020UL
#define HAL_LL_CG_BASE_WUPHCR_ADDR       0x40083030UL
#define HAL_LL_CG_BASE_FSYSMENA_ADDR     0x40083048UL
#define HAL_LL_CG_BASE_FSYSMENB_ADDR     0x4008304CUL
#define HAL_LL_CG_BASE_FSYSENA_ADDR      0x40083050UL
#define HAL_LL_CG_BASE_FCEN_ADDR         0x40083058UL
#define HAL_LL_CG_BASE_SPCLKEN_ADDR      0x4008305CUL

/*!< @brief Clock Generator register structure. */
typedef struct {
    volatile uint32_t PROTECT;   // 0x40083000 - Write Protection Register
    volatile uint32_t OSCCR;     // 0x40083004 - Oscillation Control Register
    volatile uint32_t SYSCR;     // 0x40083008 - System Clock Control Register
    volatile uint32_t STBYCR;    // 0x4008300C - Standby Control Register
             uint32_t RESERVED0[4];  // 0x40083010-0x4008301C
    volatile uint32_t PLL0SEL;   // 0x40083020 - PLL Selection Register for fsys
             uint32_t RESERVED1[3];  // 0x40083024-0x4008302C
    volatile uint32_t WUPHCR;    // 0x40083030 - High-speed Oscillation Warming-up Register
             uint32_t RESERVED2[5];  // 0x40083034-0x40083044
    volatile uint32_t FSYSMENA;  // 0x40083048 - Supply and Stop Register A for fsysm
    volatile uint32_t FSYSMENB;  // 0x4008304C - Supply and Stop Register B for fsysm
    volatile uint32_t FSYSENA;   // 0x40083050 - Supply and Stop Register A for fsysh
             uint32_t RESERVED3[1];  // 0x40083054
    volatile uint32_t FCEN;      // 0x40083058 - Clock Supply and Stop Register for fc
    volatile uint32_t SPCLKEN;   // 0x4008305C - Clock Supply and Stop Register for ADC and Debug Circuit
} hal_ll_cg_base_handle_t;

#ifdef __cplusplus
}
#endif

#endif // _HAL_LL_CG_H_
// ------------------------------------------------------------------------- END
