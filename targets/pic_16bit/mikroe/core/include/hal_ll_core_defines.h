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
 * @file  hal_ll_core_defines.h
 * @brief Core specific defines and enums used for dsPIC chips.
 */

#ifndef _HAL_LL_CORE_DEFINES_H_
#define _HAL_LL_CORE_DEFINES_H_

#ifdef __cplusplus
extern "C"{
#endif

#include "mcu_definitions.h"

#if defined(__MIKROC__)
#define MIKROC_IV(x) __INTERRUPT__ x
#define MARK_AS_IRQ_HANDLER
#else
#define MIKROC_IV(x)
#define MARK_AS_IRQ_HANDLER __attribute__((interrupt, auto_psv))
#endif

/*!< @brief Helper macro for getting adequate module index number */
#define hal_ll_module_num(_module_num) (_module_num - 1)

typedef enum
{
    HAL_LL_CORE_IRQ_RX, /* RX INT   */
    HAL_LL_CORE_IRQ_TX  /* TX INT   */
} hal_ll_core_irq_t;

/**
 * @note MCUs that have GIE (global interrupt enable) bit shall
 * use that bit in order to enable/disable interrupts.
 * MCUs that do not have this bit shall enable/disable all
 * user interrupts with priority levels 7 and lower effectively
 * emulating the GIE bit functionality.
 */
#ifdef _HAS_GIE_BIT_
    #ifdef __XC16__
        static inline void hal_ll_core_enable_int_asm(void) {
            __builtin_enable_interrupts();
        }

        static inline void hal_ll_core_disable_int_asm(void) {
            __builtin_disable_interrupts();
        }
    #else
        static inline void hal_ll_core_enable_int_asm(void) {
            // bit set flag of INTCON2 register
            asm {
                BSET INTCON2,#15
                nop
            }
        }

        static inline void hal_ll_core_disable_int_asm(void) {
            // bit clear flag of INTCON2 register
            asm {
                BCLR INTCON2,#15
                nop
            }
        }
    #endif
#else
    #ifdef __XC16__
    static inline void hal_ll_core_enable_int_asm(void) {
        __builtin_enable_interrupts();
    }

    static inline void hal_ll_core_disable_int_asm(void) {
        __builtin_disable_interrupts();
    }
    #else
    static inline void hal_ll_core_enable_int_asm(void) {
        asm {
            MOV #0xFF1F, W1
            MOV #lo_addr(SR), W0
            AND W1, [W0], [W0]
            nop
        }
    }

    static inline void hal_ll_core_disable_int_asm(void) {
        asm {
            MOV #lo_addr(SR), W0
            MOV #0xE0, W1
            IOR W1, [W0], [W0]
            nop
        }
    }
    #endif
#endif

#ifdef __cplusplus
}
#endif

#endif // _HAL_LL_CORE_DEFINES_H_
// ------------------------------------------------------------------------- END
