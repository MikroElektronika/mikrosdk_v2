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
 * @brief Core specific defines and enums used for RL78 chips.
 */

#ifndef _HAL_LL_CORE_DEFINES_H_
#define _HAL_LL_CORE_DEFINES_H_

#ifdef __cplusplus
extern "C"{
#endif

#include <stdint.h>

/*!< @brief Vector table addresses usable as IRQn.
 *          Vector address 0x04 (INTWDTI) is interrupt source 0, every
 *          following vector adds one source. BRK (0x7E) can't be masked. */
#define HAL_LL_CORE_IRQ_VECTOR_FIRST        ( 0x04 )
#define HAL_LL_CORE_IRQ_VECTOR_LAST         ( 0x7C )

/*!< @brief Interrupt source number and bit position within the 8-bit flag registers. */
#define hal_ll_core_irq_source(_irqn)       ( ( uint8_t )( ( ( _irqn ) - HAL_LL_CORE_IRQ_VECTOR_FIRST ) >> 1 ) )
#define hal_ll_core_irq_bit(_irqn)          ( hal_ll_core_irq_source( _irqn ) & 0x07 )

/*!< @brief Request flag registers: IF0L-IF1H at FFFE0H-FFFE3H, IF2L-IF3H at FFFD0H-FFFD3H.
 *          Mask (MKxx), priority 0 (PR0xx) and priority 1 (PR1xx) registers
 *          follow at +4, +8 and +12 from the matching IFxx. */
#define HAL_LL_CORE_IF0L_ADDR               ( 0xFFFE0UL )
#define HAL_LL_CORE_IF2L_ADDR               ( 0xFFFD0UL )
#define HAL_LL_CORE_IRQ_MK_OFFSET           ( 0x04UL )
#define HAL_LL_CORE_IRQ_PR0_OFFSET          ( 0x08UL )
#define HAL_LL_CORE_IRQ_PR1_OFFSET          ( 0x0CUL )
#define hal_ll_core_irq_if_addr(_irqn)      ( ( hal_ll_core_irq_source( _irqn ) < 32 ) ? \
                                              ( HAL_LL_CORE_IF0L_ADDR + ( hal_ll_core_irq_source( _irqn ) >> 3 ) ) : \
                                              ( HAL_LL_CORE_IF2L_ADDR + ( ( hal_ll_core_irq_source( _irqn ) - 32 ) >> 3 ) ) )
#define hal_ll_core_irq_reg(_irqn,_offset)  ( ( volatile uint8_t * )( hal_ll_core_irq_if_addr( _irqn ) + ( _offset ) ) )

/*!< @brief Program status word, IE is bit 7. */
#define HAL_LL_CORE_PSW_ADDR                ( 0xFFFFAUL )
#define HAL_LL_CORE_PSW_IE                  ( 0x80U )

/*!< @brief Global interrupt enable/disable (EI/DI instructions). */
#define hal_ll_core_enable_int_asm          __builtin_rl78_ei()
#define hal_ll_core_disable_int_asm         __builtin_rl78_di()

/*!< @brief Interrupt priority levels, level 0 is the highest. Out of reset all sources are level 3. */
typedef enum
{
    HAL_LL_IVT_PRIORITY_LEVEL_0 = 0,
    HAL_LL_IVT_PRIORITY_LEVEL_1,
    HAL_LL_IVT_PRIORITY_LEVEL_2,
    HAL_LL_IVT_PRIORITY_LEVEL_3
} hal_ll_core_irq_priority_levels;

#ifdef __cplusplus
}
#endif

#endif // _HAL_LL_CORE_DEFINES_H_
// ------------------------------------------------------------------------- END
