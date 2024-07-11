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
 * @file  hal_ll_core_defines.h
 * @brief Core specific defines and enums used for PIC chips.
 */

#ifndef _HAL_LL_CORE_DEFINES_H_
#define _HAL_LL_CORE_DEFINES_H_

#ifdef __cplusplus
extern "C"{
#endif

#include <stdint.h>
#include "assembly.h"
#ifdef __XC32__
#include <sys/attribs.h>
#endif

#if defined(__MIKROC_AI_FOR_PIC32__)
#define MIKROC_IV(x) iv x ilevel 7
#define MARK_AS_IRQ_HANDLER(vec_num)
#else
#define MIKROC_IV(x)
#define MARK_AS_IRQ_HANDLER(vec_num) __ISR(vec_num, IPL7SRS)
#endif

#define __weak __attribute__((weak))

typedef enum
{
    HAL_LL_IRQ_PRIORITY_LEVEL_0 = 0,
    HAL_LL_IRQ_PRIORITY_LEVEL_1,
    HAL_LL_IRQ_PRIORITY_LEVEL_2,
    HAL_LL_IRQ_PRIORITY_LEVEL_3,
    HAL_LL_IRQ_PRIORITY_LEVEL_4,
    HAL_LL_IRQ_PRIORITY_LEVEL_5,
    HAL_LL_IRQ_PRIORITY_LEVEL_6,
    HAL_LL_IRQ_PRIORITY_LEVEL_7
} hal_ll_core_irq_priority_levels;

#define hal_ll_core_enable_int_asm assembly(nop); \
                                   assembly(ei); \
                                   assembly(nop)

#define hal_ll_core_disable_int_asm assembly(nop); \
                                    assembly(di); \
                                    assembly(nop)

#define HAL_LL_INTCON_MVEC_BIT (12)
#define HAL_LL_INT_PRI_SHADOW_SET (0x76543210UL)

#ifdef __cplusplus
}
#endif

#endif // _HAL_LL_CORE_DEFINES_H_
// ------------------------------------------------------------------------- END
