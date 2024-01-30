/****************************************************************************
**
** Copyright (C) 2024 MikroElektronika d.o.o.
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

void hal_ll_core_enable_interrupts(void) {
    hal_ll_core_enable_int_asm;
}

void hal_ll_core_disable_interrupts(void) {
    hal_ll_core_disable_int_asm;
}

void hal_ll_core_enable_irq(uint8_t IRQn) {
    if ( IRQn >= HAL_LL_CORE_IRQ_NOT_SUPPORTED ) {
        return;
    #ifdef HAL_LL_USART0_UCSR0B_REG_ADDRESS
    } else if ( IRQn >= HAL_LL_USART0_TX_IVT_ADDRESS ) {
        set_reg_bit(HAL_LL_USART0_UCSR0B_REG_ADDRESS, 6);
    } else if ( IRQn >= HAL_LL_USART0_UDRE_IVT_ADDRESS ) {
        set_reg_bit(HAL_LL_USART0_UCSR0B_REG_ADDRESS, 5);
    } else if ( IRQn >= HAL_LL_USART0_RX_IVT_ADDRESS ) {
        set_reg_bit(HAL_LL_USART0_UCSR0B_REG_ADDRESS, 7);
    #endif
    #ifdef HAL_LL_USART1_UCSR1B_REG_ADDRESS
    } else if ( IRQn >= HAL_LL_USART1_TX_IVT_ADDRESS ) {
        set_reg_bit(HAL_LL_USART1_UCSR1B_REG_ADDRESS, 6);
    } else if ( IRQn >= HAL_LL_USART1_UDRE_IVT_ADDRESS ) {
        set_reg_bit(HAL_LL_USART1_UCSR1B_REG_ADDRESS, 5);
    } else if ( IRQn >= HAL_LL_USART1_RX_IVT_ADDRESS ) {
        set_reg_bit(HAL_LL_USART1_UCSR1B_REG_ADDRESS, 7);
    #endif
    #ifdef HAL_LL_USART2_UCSR2B_REG_ADDRESS
    } else if ( IRQn >= HAL_LL_USART2_TX_IVT_ADDRESS ) {
        set_reg_bit(HAL_LL_USART2_UCSR2B_REG_ADDRESS, 6);
    } else if ( IRQn >= HAL_LL_USART2_UDRE_IVT_ADDRESS ) {
        set_reg_bit(HAL_LL_USART2_UCSR2B_REG_ADDRESS, 5);
    } else if ( IRQn >= HAL_LL_USART2_RX_IVT_ADDRESS ) {
        set_reg_bit(HAL_LL_USART2_UCSR2B_REG_ADDRESS, 7);
    #endif
    #ifdef HAL_LL_USART3_UCSR3B_REG_ADDRESS
    } else if ( IRQn >= HAL_LL_USART3_TX_IVT_ADDRESS ) {
        set_reg_bit(HAL_LL_USART3_UCSR3B_REG_ADDRESS, 6);
    } else if ( IRQn >= HAL_LL_USART3_UDRE_IVT_ADDRESS ) {
        set_reg_bit(HAL_LL_USART3_UCSR3B_REG_ADDRESS, 5);
    } else if ( IRQn >= HAL_LL_USART3_RX_IVT_ADDRESS ) {
        set_reg_bit(HAL_LL_USART3_UCSR3B_REG_ADDRESS, 7);
    #endif
    }
}

void hal_ll_core_disable_irq(uint8_t IRQn) {
    if ( IRQn >= HAL_LL_CORE_IRQ_NOT_SUPPORTED ) {
        return;
    #ifdef HAL_LL_USART0_UCSR0B_REG_ADDRESS
    } else if ( IRQn >= HAL_LL_USART0_TX_IVT_ADDRESS ) {
        clear_reg_bit(HAL_LL_USART0_UCSR0B_REG_ADDRESS, 6);
    } else if ( IRQn >= HAL_LL_USART0_UDRE_IVT_ADDRESS ) {
        clear_reg_bit(HAL_LL_USART0_UCSR0B_REG_ADDRESS, 5);
    } else if ( IRQn >= HAL_LL_USART0_RX_IVT_ADDRESS ) {
        clear_reg_bit(HAL_LL_USART0_UCSR0B_REG_ADDRESS, 7);
    #endif
    #ifdef HAL_LL_USART1_UCSR1B_REG_ADDRESS
    } else if ( IRQn >= HAL_LL_USART1_TX_IVT_ADDRESS ) {
        clear_reg_bit(HAL_LL_USART1_UCSR1B_REG_ADDRESS, 6);
    } else if ( IRQn >= HAL_LL_USART1_UDRE_IVT_ADDRESS ) {
        clear_reg_bit(HAL_LL_USART1_UCSR1B_REG_ADDRESS, 5);
    } else if ( IRQn >= HAL_LL_USART1_RX_IVT_ADDRESS ) {
        clear_reg_bit(HAL_LL_USART1_UCSR1B_REG_ADDRESS, 7);
    #endif
    #ifdef HAL_LL_USART2_UCSR2B_REG_ADDRESS
    } else if ( IRQn >= HAL_LL_USART2_TX_IVT_ADDRESS ) {
        clear_reg_bit(HAL_LL_USART2_UCSR2B_REG_ADDRESS, 6);
    } else if ( IRQn >= HAL_LL_USART2_UDRE_IVT_ADDRESS ) {
        clear_reg_bit(HAL_LL_USART2_UCSR2B_REG_ADDRESS, 5);
    } else if ( IRQn >= HAL_LL_USART2_RX_IVT_ADDRESS ) {
        clear_reg_bit(HAL_LL_USART2_UCSR2B_REG_ADDRESS, 7);
    #endif
    #ifdef HAL_LL_USART3_UCSR3B_REG_ADDRESS
    } else if ( IRQn >= HAL_LL_USART3_TX_IVT_ADDRESS ) {
        clear_reg_bit(HAL_LL_USART3_UCSR3B_REG_ADDRESS, 6);
    } else if ( IRQn >= HAL_LL_USART3_UDRE_IVT_ADDRESS ) {
        clear_reg_bit(HAL_LL_USART3_UCSR3B_REG_ADDRESS, 5);
    } else if ( IRQn >= HAL_LL_USART3_RX_IVT_ADDRESS ) {
        clear_reg_bit(HAL_LL_USART3_UCSR3B_REG_ADDRESS, 7);
    #endif
    }
}

// ------------------------------------------------------------------------- END
