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
#ifdef __XC8__
#include "mcu.h"
#endif

#if defined(__MIKROC_AI_FOR_PIC__)
#define MIKROC_IV(x) iv x
#define MARK_AS_IRQ_HANDLER
#else
#define MIKROC_IV(x)
// Legacy support - should work for all PIC MCUs in XC8 toolchain
#define MARK_AS_IRQ_HANDLER __interrupt()
// Previous approach left for future reference
// #define MARK_AS_IRQ_HANDLER __interrupt(irq(default))
#endif

#define __weak __attribute__((weak))

typedef enum
{
    HAL_LL_IRQ_PRIORITY_LEVEL_LOW = 0,
    HAL_LL_IRQ_PRIORITY_LEVEL_HIGH
} hal_ll_core_irq_priority_levels;

#ifdef __XC8__
    #define _INTCON_BIT_POS(INTCON_REG_SEL, BIT_NAME) _##INTCON_REG_SEL##_##BIT_NAME##_POSN
    #define INTCON_BIT_POS(INTCON_REG,BIT_NAME) _INTCON_BIT_POS(INTCON_REG, BIT_NAME)
#else
    #define INTCON_BIT_POS(INTCON_REG,BIT_NAME) BIT_NAME
#endif

#define hal_ll_core_enable_int_asm assembly(BSF INTCON_REG,INTCON_BIT_POS(INTCON_REG,GIE))  // bit set flag of INTCON register
#define hal_ll_core_disable_int_asm assembly(BCF INTCON_REG,INTCON_BIT_POS(INTCON_REG,GIE))  // bit clear flag of INTCON register

#if defined __hal_ll_core_subimplementation_1__
    #define hal_ll_core_enable_peripheral_int_asm assembly(nop)
    #define hal_ll_core_disable_peripheral_int_asm assembly(nop)
    #define hal_ll_core_interrupt_priority_enable_asm assembly(BSF INTCON_REG,INTCON_BIT_POS(INTCON_REG,IPEN)) // bit set IPEN flag of INTCON register
    #define hal_ll_core_interrupt_priority_disable_asm assembly(BCF INTCON_REG,INTCON_BIT_POS(INTCON_REG,IPEN)) // bit clear IPEN flag of INTCON register
#elif defined __hal_ll_core_subimplementation_2__
    #define hal_ll_core_enable_peripheral_int_asm assembly(BSF INTCON_REG,INTCON_BIT_POS(INTCON_REG,PEIE)) // bit set flag of INTCON register
    #define hal_ll_core_disable_peripheral_int_asm assembly(BCF INTCON_REG,INTCON_BIT_POS(INTCON_REG,PEIE)) // bit clear flag of INTCON register
    #define hal_ll_core_interrupt_priority_enable_asm assembly(nop)
    #define hal_ll_core_interrupt_priority_disable_asm assembly(nop)
#endif

#define hal_ll_core_write_reg(reg_addr,write_val) ((*(uint8_t *)reg_addr)=write_val)

#if defined(IRQLOCK_REG)
    #define HAL_LL_CORE_MIRQ_LOCK 0
    #define HAL_LL_CORE_MIRQ_UNLOCK 1

    #define HAL_LL_CORE_LOCK_UNLOCK_SEQUENCE_KEY_FIRST 0x55
    #define HAL_LL_CORE_LOCK_UNLOCK_SEQUENCE_KEY_SECOND 0xAA

    #define IRQ_BASE_START_ADDR 0x20

    #define hal_ll_core_mirq_lock_unlock_sequence(irq_reg) hal_ll_core_write_reg(irq_reg,HAL_LL_CORE_LOCK_UNLOCK_SEQUENCE_KEY_FIRST); \
                                                           hal_ll_core_write_reg(irq_reg, HAL_LL_CORE_LOCK_UNLOCK_SEQUENCE_KEY_SECOND);

    #define hal_ll_core_mirq_lock_unlock_reg(irq_reg,lock_val) hal_ll_core_mirq_lock_unlock_sequence(irq_reg); \
                                                               ( lock_val == HAL_LL_CORE_MIRQ_LOCK ) ? \
                                                               ( clear_reg_bit(irq_reg,HAL_LL_CORE_MIRQ_UNLOCK) ) : \
                                                               ( set_reg_bit(irq_reg,HAL_LL_CORE_MIRQ_UNLOCK) )
#endif

#define hal_ll_core_priority_set(irq_reg,bit_num,irq_priority) ( irq_priority == HAL_LL_IRQ_PRIORITY_LEVEL_LOW ) ? \
                                                               ( clear_reg_bit(irq_reg,bit_num) ) : \
                                                               ( set_reg_bit(irq_reg,bit_num) )

#define HAL_LL_CORE_REG2 8
#define HAL_LL_CORE_REG3 16
#define HAL_LL_CORE_REG4 24
#define HAL_LL_CORE_REG5 32
#define HAL_LL_CORE_REG6 40
#define HAL_LL_CORE_REG7 48
#define HAL_LL_CORE_REG8 56
#define HAL_LL_CORE_REG9 64
#define HAL_LL_CORE_REG10 72
#define HAL_LL_CORE_REG11 80
#define HAL_LL_CORE_REG12 88
#define HAL_LL_CORE_REG13 96
#define HAL_LL_CORE_REG14 104
#define HAL_LL_CORE_REG15 112
#define HAL_LL_CORE_IRQ_NOT_SUPPORTED 120

#ifdef __cplusplus
}
#endif

#endif // _HAL_LL_CORE_DEFINES_H_
// ------------------------------------------------------------------------- END
