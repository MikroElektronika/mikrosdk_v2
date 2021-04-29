/****************************************************************************
**
** Copyright (C) 2021 MikroElektronika d.o.o.
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
 * @file hal_ll_core.c
 * @brief CORE HAL LOW LEVEL layer implementation.
 */

#include "mcu_definitions.h"
#include "hal_ll_core_defines.h"
#include "hal_ll_bit_control.h"

void hal_ll_core_enable_interrupts( void )
{
    hal_ll_core_enable_int_asm;
}

void hal_ll_core_disable_interrupts( void )
{
    hal_ll_core_disable_int_asm;
}

void hal_ll_core_enable_irq( uint8_t IRQn )
{
    #ifdef IRQLOCK_REG
    hal_ll_core_mirq_lock_unlock_reg( IRQLOCK_REG, HAL_LL_CORE_MIRQ_UNLOCK );
    #ifdef IRQ_BASE_ADDRESS_CUSTOM
    hal_ll_core_write_reg( IRQBASEL_REG, IRQ_BASE_ADDRESS_CUSTOM );  // Custom address is defined in `mcu_definitions.h` file
    #else
    hal_ll_core_write_reg( IRQBASEL_REG, IRQ_BASE_ADDR_DEFAULT );  // Default adress if custom is undefined
    #endif
    hal_ll_core_mirq_lock_unlock_reg( IRQLOCK_REG, HAL_LL_CORE_MIRQ_LOCK );
    #endif

    hal_ll_core_interrupt_priority_disable_asm;
    hal_ll_core_enable_peripheral_int_asm;

    if( IRQn >= HAL_LL_CORE_IRQ_NOT_SUPPORTED ) {
        return;
    #ifdef HAL_LL_PIE15_ADDRESS
    } else if( IRQn >= HAL_LL_CORE_REG15 ) {
        set_reg_bit( HAL_LL_PIE15_ADDRESS, IRQn - HAL_LL_CORE_REG15 );
    #endif
    #ifdef HAL_LL_PIE14_ADDRESS
    } else if( IRQn >= HAL_LL_CORE_REG14 ) {
        set_reg_bit( HAL_LL_PIE14_ADDRESS, IRQn - HAL_LL_CORE_REG14 );
    #endif
    #ifdef HAL_LL_PIE13_ADDRESS
    } else if( IRQn >= HAL_LL_CORE_REG13 ) {
        set_reg_bit( HAL_LL_PIE13_ADDRESS, IRQn - HAL_LL_CORE_REG13 );
    #endif
    #ifdef HAL_LL_PIE12_ADDRESS
    } else if( IRQn >= HAL_LL_CORE_REG12 ) {
        set_reg_bit( HAL_LL_PIE12_ADDRESS, IRQn - HAL_LL_CORE_REG12 );
    #endif
    #ifdef HAL_LL_PIE11_ADDRESS
    } else if( IRQn >= HAL_LL_CORE_REG11 ) {
        set_reg_bit( HAL_LL_PIE11_ADDRESS, IRQn - HAL_LL_CORE_REG11 );
    #endif
    #ifdef HAL_LL_PIE10_ADDRESS
    } else if( IRQn >= HAL_LL_CORE_REG10 ) {
        set_reg_bit( HAL_LL_PIE10_ADDRESS, IRQn - HAL_LL_CORE_REG10 );
    #endif
    #ifdef HAL_LL_PIE9_ADDRESS
    } else if( IRQn >= HAL_LL_CORE_REG9 ) {
        set_reg_bit( HAL_LL_PIE9_ADDRESS, IRQn - HAL_LL_CORE_REG9 );
    #endif
    #ifdef HAL_LL_PIE8_ADDRESS
    } else if( IRQn >= HAL_LL_CORE_REG8 ) {
        set_reg_bit( HAL_LL_PIE8_ADDRESS, IRQn - HAL_LL_CORE_REG8 );
    #endif
    #ifdef HAL_LL_PIE7_ADDRESS
    } else if( IRQn >= HAL_LL_CORE_REG7 ) {
        set_reg_bit( HAL_LL_PIE7_ADDRESS, IRQn - HAL_LL_CORE_REG7 );
    #endif
    #ifdef HAL_LL_PIE6_ADDRESS
    } else if( IRQn >= HAL_LL_CORE_REG6 ) {
        set_reg_bit( HAL_LL_PIE6_ADDRESS, IRQn - HAL_LL_CORE_REG6 );
    #endif
    #ifdef HAL_LL_PIE5_ADDRESS
    } else if( IRQn >= HAL_LL_CORE_REG5 ) {
        set_reg_bit( HAL_LL_PIE5_ADDRESS, IRQn - HAL_LL_CORE_REG5 );
    #endif
    #ifdef HAL_LL_PIE4_ADDRESS
    } else if( IRQn >= HAL_LL_CORE_REG4 ) {
        set_reg_bit( HAL_LL_PIE4_ADDRESS, IRQn - HAL_LL_CORE_REG4 );
    #endif
    #ifdef HAL_LL_PIE3_ADDRESS
    } else if( IRQn >= HAL_LL_CORE_REG3 ) {
        set_reg_bit( HAL_LL_PIE3_ADDRESS, IRQn - HAL_LL_CORE_REG3 );
    #endif
    #ifdef HAL_LL_PIE2_ADDRESS
    } else if( IRQn >= HAL_LL_CORE_REG2 ) {
        set_reg_bit( HAL_LL_PIE2_ADDRESS, IRQn - HAL_LL_CORE_REG2 );
    #endif
    #ifdef HAL_LL_PIE1_ADDRESS
    } else {
        set_reg_bit( HAL_LL_PIE1_ADDRESS,  IRQn );
    #endif
    }

    hal_ll_core_interrupt_priority_enable_asm;
}

void hal_ll_core_disable_irq( uint8_t IRQn )
{
    hal_ll_core_interrupt_priority_disable_asm;
    hal_ll_core_disable_peripheral_int_asm;

    if( IRQn >= HAL_LL_CORE_IRQ_NOT_SUPPORTED ) {
        return;
    #ifdef HAL_LL_PIE15_ADDRESS
    } else if( IRQn >= HAL_LL_CORE_REG15 ) {
        clear_reg_bit( HAL_LL_PIE15_ADDRESS, IRQn - HAL_LL_CORE_REG15 );
    #endif
    #ifdef HAL_LL_PIE14_ADDRESS
    } else if( IRQn >= HAL_LL_CORE_REG14 ) {
        clear_reg_bit( HAL_LL_PIE14_ADDRESS, IRQn - HAL_LL_CORE_REG14 );
    #endif
    #ifdef HAL_LL_PIE13_ADDRESS
    } else if( IRQn >= HAL_LL_CORE_REG13 ) {
        clear_reg_bit( HAL_LL_PIE13_ADDRESS, IRQn - HAL_LL_CORE_REG13 );
    #endif
    #ifdef HAL_LL_PIE12_ADDRESS
    } else if( IRQn >= HAL_LL_CORE_REG12 ) {
        clear_reg_bit( HAL_LL_PIE12_ADDRESS, IRQn - HAL_LL_CORE_REG12 );
    #endif
    #ifdef HAL_LL_PIE11_ADDRESS
    } else if( IRQn >= HAL_LL_CORE_REG11 ) {
        clear_reg_bit( HAL_LL_PIE11_ADDRESS, IRQn - HAL_LL_CORE_REG11 );
    #endif
    #ifdef HAL_LL_PIE10_ADDRESS
    } else if( IRQn >= HAL_LL_CORE_REG10 ) {
        clear_reg_bit( HAL_LL_PIE10_ADDRESS, IRQn - HAL_LL_CORE_REG10 );
    #endif
    #ifdef HAL_LL_PIE9_ADDRESS
    } else if( IRQn >= HAL_LL_CORE_REG9 ) {
        clear_reg_bit( HAL_LL_PIE9_ADDRESS, IRQn - HAL_LL_CORE_REG9 );
    #endif
    #ifdef HAL_LL_PIE8_ADDRESS
    } else if( IRQn >= HAL_LL_CORE_REG8 ) {
        clear_reg_bit( HAL_LL_PIE8_ADDRESS, IRQn - HAL_LL_CORE_REG8 );
    #endif
    #ifdef HAL_LL_PIE7_ADDRESS
    } else if( IRQn >= HAL_LL_CORE_REG7 ) {
        clear_reg_bit( HAL_LL_PIE7_ADDRESS, IRQn - HAL_LL_CORE_REG7 );
    #endif
    #ifdef HAL_LL_PIE6_ADDRESS
    } else if( IRQn >= HAL_LL_CORE_REG6 ) {
        clear_reg_bit( HAL_LL_PIE6_ADDRESS, IRQn - HAL_LL_CORE_REG6 );
    #endif
    #ifdef HAL_LL_PIE5_ADDRESS
    } else if( IRQn >= HAL_LL_CORE_REG5 ) {
        clear_reg_bit( HAL_LL_PIE5_ADDRESS, IRQn - HAL_LL_CORE_REG5 );
    #endif
    #ifdef HAL_LL_PIE4_ADDRESS
    } else if( IRQn >= HAL_LL_CORE_REG4 ) {
        clear_reg_bit( HAL_LL_PIE4_ADDRESS, IRQn - HAL_LL_CORE_REG4 );
    #endif
    #ifdef HAL_LL_PIE3_ADDRESS
    } else if( IRQn >= HAL_LL_CORE_REG3 ) {
        clear_reg_bit( HAL_LL_PIE3_ADDRESS, IRQn - HAL_LL_CORE_REG3 );
    #endif
    #ifdef HAL_LL_PIE2_ADDRESS
    } else if( IRQn >= HAL_LL_CORE_REG2 ) {
        clear_reg_bit( HAL_LL_PIE2_ADDRESS, IRQn - HAL_LL_CORE_REG2 );
    #endif
    #ifdef HAL_LL_PIE1_ADDRESS
    } else {
        clear_reg_bit( HAL_LL_PIE1_ADDRESS,  IRQn );
    #endif
    }

    #ifdef IRQLOCK_REG
    hal_ll_core_mirq_lock_unlock_reg( IRQLOCK_REG, HAL_LL_CORE_MIRQ_UNLOCK );
    hal_ll_core_write_reg( IRQBASEL_REG, IRQ_BASE_ADDR_DEFAULT );
    hal_ll_core_mirq_lock_unlock_reg( IRQLOCK_REG, HAL_LL_CORE_MIRQ_LOCK );
    #endif
}

void hal_ll_core_set_priority_irq( uint8_t IRQn, uint8_t IRQn_priority )
{
    hal_ll_core_interrupt_priority_enable_asm;

    if( IRQn >= HAL_LL_CORE_IRQ_NOT_SUPPORTED ) {
        return;
    #ifdef HAL_LL_IPR15_ADDRESS
    } else if( IRQn >= HAL_LL_CORE_REG15 ) {
        hal_ll_core_priority_set( HAL_LL_IPR15_ADDRESS, IRQn - HAL_LL_CORE_REG15, IRQn_priority );
    #endif
    #ifdef HAL_LL_IPR14_ADDRESS
    } else if( IRQn >= HAL_LL_CORE_REG14 ) {
        hal_ll_core_priority_set( HAL_LL_IPR14_ADDRESS, IRQn - HAL_LL_CORE_REG14, IRQn_priority );
    #endif
    #ifdef HAL_LL_IPR13_ADDRESS
    } else if( IRQn >= HAL_LL_CORE_REG13 ) {
        hal_ll_core_priority_set( HAL_LL_IPR13_ADDRESS, IRQn - HAL_LL_CORE_REG13, IRQn_priority );
    #endif
    #ifdef HAL_LL_IPR12_ADDRESS
    } else if( IRQn >= HAL_LL_CORE_REG12 ) {
        hal_ll_core_priority_set( HAL_LL_IPR12_ADDRESS, IRQn - HAL_LL_CORE_REG12, IRQn_priority );
    #endif
    #ifdef HAL_LL_IPR10_ADDRESS
    } else if( IRQn >= HAL_LL_CORE_REG11 ) {
        hal_ll_core_priority_set( HAL_LL_IPR11_ADDRESS, IRQn - HAL_LL_CORE_REG11, IRQn_priority );
    #endif
    #ifdef HAL_LL_IPR10_ADDRESS
    } else if( IRQn >= HAL_LL_CORE_REG10 ) {
        hal_ll_core_priority_set( HAL_LL_IPR10_ADDRESS, IRQn - HAL_LL_CORE_REG10, IRQn_priority );
    #endif
    #ifdef HAL_LL_IPR9_ADDRESS
    } else if( IRQn >= HAL_LL_CORE_REG9 ) {
        hal_ll_core_priority_set( HAL_LL_CORE_IRQ_IPR9, IRQn - HAL_LL_CORE_REG9, IRQn_priority );
    #endif
    #ifdef HAL_LL_IPR8_ADDRESS
    } else if( IRQn >= HAL_LL_CORE_REG8 ) {
        hal_ll_core_priority_set( HAL_LL_IPR8_ADDRESS, IRQn - HAL_LL_CORE_REG8, IRQn_priority );
    #endif
    #ifdef HAL_LL_IPR7_ADDRESS
    } else if( IRQn >= HAL_LL_CORE_REG7 ) {
        hal_ll_core_priority_set( HAL_LL_IPR7_ADDRESS, IRQn - HAL_LL_CORE_REG7, IRQn_priority );
    #endif
    #ifdef HAL_LL_IPR6_ADDRESS
    } else if( IRQn >= HAL_LL_CORE_REG6 ) {
        hal_ll_core_priority_set( HAL_LL_IPR6_ADDRESS, IRQn - HAL_LL_CORE_REG6, IRQn_priority );
    #endif
    #ifdef HAL_LL_IPR5_ADDRESS
    } else if( IRQn >= HAL_LL_CORE_REG5 ) {
        hal_ll_core_priority_set( HAL_LL_IPR5_ADDRESS, IRQn - HAL_LL_CORE_REG5, IRQn_priority );
    #endif
    #ifdef HAL_LL_IPR4_ADDRESS
    } else if( IRQn >= HAL_LL_CORE_REG4 ) {
        hal_ll_core_priority_set( HAL_LL_IPR4_ADDRESS, IRQn - HAL_LL_CORE_REG4, IRQn_priority );
    #endif
    #ifdef HAL_LL_IPR3_ADDRESS
    } else if( IRQn >= HAL_LL_CORE_REG3 ) {
        hal_ll_core_priority_set( HAL_LL_IPR3_ADDRESS, IRQn - HAL_LL_CORE_REG3, IRQn_priority );
    #endif
    #ifdef HAL_LL_IPR2_ADDRESS
    } else if( IRQn >= HAL_LL_CORE_REG2 ) {
        hal_ll_core_priority_set( HAL_LL_IPR2_ADDRESS, IRQn - HAL_LL_CORE_REG2, IRQn_priority );
    #endif
    #ifdef HAL_LL_IPR1_ADDRESS
    } else {
        hal_ll_core_priority_set( HAL_LL_IPR1_ADDRESS, IRQn, IRQn_priority );
    #endif
    }
}
// ------------------------------------------------------------------------- END
