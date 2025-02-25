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
 * @file hal_ll_core.c
 * @brief CORE HAL LOW LEVEL layer implementation.
 */

#include "hal_ll_core_defines.h"
#include "hal_ll_core_macros.h"
#include "hal_ll_bit_control.h"

/*!< @brief Global variable to get module number from UART hal low level layer. */
extern uint8_t hal_ll_module_num;

void hal_ll_core_enable_interrupts( void )
{
    hal_ll_core_enable_int_asm();
}

void hal_ll_core_disable_interrupts( void )
{
    hal_ll_core_disable_int_asm();
}

void hal_ll_core_enable_irq( uint8_t IRQn )
{
    switch ( hal_ll_module_num )
    {
        #ifdef UART_MODULE_1
        case hal_ll_module_num(UART_MODULE_1):
            if (HAL_LL_CORE_IRQ_RX == IRQn) {
                set_reg_bit(UART1_INTERRUPT_CONTROL_REG_IEC_RX, UART1_INTERRUPT_CONTROL_BIT_RX);
            } else if (HAL_LL_CORE_IRQ_TX == IRQn) {
                set_reg_bit(UART1_INTERRUPT_CONTROL_REG_IEC_TX, UART1_INTERRUPT_CONTROL_BIT_TX);
            }
            break;
        #endif
        #ifdef UART_MODULE_2
        case hal_ll_module_num(UART_MODULE_2):
            if (HAL_LL_CORE_IRQ_RX == IRQn) {
                set_reg_bit(UART2_INTERRUPT_CONTROL_REG_IEC_RX, UART2_INTERRUPT_CONTROL_BIT_RX);
            } else if (HAL_LL_CORE_IRQ_TX == IRQn) {
                set_reg_bit(UART2_INTERRUPT_CONTROL_REG_IEC_TX, UART2_INTERRUPT_CONTROL_BIT_TX);
            }
            break;
        #endif
        #ifdef UART_MODULE_3
        case hal_ll_module_num(UART_MODULE_3):
            if (HAL_LL_CORE_IRQ_RX == IRQn) {
                set_reg_bit(UART3_INTERRUPT_CONTROL_REG_IEC_RX, UART3_INTERRUPT_CONTROL_BIT_RX);
            } else if (HAL_LL_CORE_IRQ_TX == IRQn) {
                set_reg_bit(UART3_INTERRUPT_CONTROL_REG_IEC_TX, UART3_INTERRUPT_CONTROL_BIT_TX);
            }
            break;
        #endif
        #ifdef UART_MODULE_4
        case hal_ll_module_num(UART_MODULE_4):
            if (HAL_LL_CORE_IRQ_RX == IRQn) {
                set_reg_bit(UART4_INTERRUPT_CONTROL_REG_IEC_RX, UART4_INTERRUPT_CONTROL_BIT_RX);
            } else if (HAL_LL_CORE_IRQ_TX == IRQn) {
                set_reg_bit(UART4_INTERRUPT_CONTROL_REG_IEC_TX, UART4_INTERRUPT_CONTROL_BIT_TX);
            }
            break;
        #endif
        #ifdef UART_MODULE_5
        case hal_ll_module_num(UART_MODULE_5):
            if (HAL_LL_CORE_IRQ_RX == IRQn) {
                set_reg_bit(UART5_INTERRUPT_CONTROL_REG_IEC_RX, UART5_INTERRUPT_CONTROL_BIT_RX);
            } else if (HAL_LL_CORE_IRQ_TX == IRQn) {
                set_reg_bit(UART5_INTERRUPT_CONTROL_REG_IEC_TX, UART5_INTERRUPT_CONTROL_BIT_TX);
            }
            break;
        #endif
        #ifdef UART_MODULE_6
        case hal_ll_module_num(UART_MODULE_6):
            if (HAL_LL_CORE_IRQ_RX == IRQn) {
                set_reg_bit(UART6_INTERRUPT_CONTROL_REG_IEC_RX, UART6_INTERRUPT_CONTROL_BIT_RX);
            } else if (HAL_LL_CORE_IRQ_TX == IRQn) {
                set_reg_bit(UART6_INTERRUPT_CONTROL_REG_IEC_TX, UART6_INTERRUPT_CONTROL_BIT_TX);
            }
            break;
        #endif

        default:
            break;
    }
}

void hal_ll_core_disable_irq( uint8_t IRQn )
{
    switch ( hal_ll_module_num )
    {
        #ifdef UART_MODULE_1
        case hal_ll_module_num(UART_MODULE_1):
            if (HAL_LL_CORE_IRQ_RX == IRQn) {
                clear_reg_bit(UART1_INTERRUPT_CONTROL_REG_IEC_RX, UART1_INTERRUPT_CONTROL_BIT_RX);
            } else if (HAL_LL_CORE_IRQ_TX == IRQn) {
                clear_reg_bit(UART1_INTERRUPT_CONTROL_REG_IEC_TX, UART1_INTERRUPT_CONTROL_BIT_TX);
            }
            break;
        #endif
        #ifdef UART_MODULE_2
        case hal_ll_module_num(UART_MODULE_2):
            if (HAL_LL_CORE_IRQ_RX == IRQn) {
                clear_reg_bit(UART2_INTERRUPT_CONTROL_REG_IEC_RX, UART2_INTERRUPT_CONTROL_BIT_RX);
            } else if (HAL_LL_CORE_IRQ_TX == IRQn) {
                clear_reg_bit(UART2_INTERRUPT_CONTROL_REG_IEC_TX, UART2_INTERRUPT_CONTROL_BIT_TX);
            }
            break;
        #endif
        #ifdef UART_MODULE_3
        case hal_ll_module_num(UART_MODULE_3):
            if (HAL_LL_CORE_IRQ_RX == IRQn) {
                clear_reg_bit(UART3_INTERRUPT_CONTROL_REG_IEC_RX, UART3_INTERRUPT_CONTROL_BIT_RX);
            } else if (HAL_LL_CORE_IRQ_TX == IRQn) {
                clear_reg_bit(UART3_INTERRUPT_CONTROL_REG_IEC_TX, UART3_INTERRUPT_CONTROL_BIT_TX);
            }
            break;
        #endif
        #ifdef UART_MODULE_4
        case hal_ll_module_num(UART_MODULE_4):
            if (HAL_LL_CORE_IRQ_RX == IRQn) {
                clear_reg_bit(UART4_INTERRUPT_CONTROL_REG_IEC_RX, UART4_INTERRUPT_CONTROL_BIT_RX);
            } else if (HAL_LL_CORE_IRQ_TX == IRQn) {
                clear_reg_bit(UART4_INTERRUPT_CONTROL_REG_IEC_TX, UART4_INTERRUPT_CONTROL_BIT_TX);
            }
            break;
        #endif
        #ifdef UART_MODULE_5
        case hal_ll_module_num(UART_MODULE_5):
            if (HAL_LL_CORE_IRQ_RX == IRQn) {
                clear_reg_bit(UART5_INTERRUPT_CONTROL_REG_IEC_RX, UART5_INTERRUPT_CONTROL_BIT_RX);
            } else if (HAL_LL_CORE_IRQ_TX == IRQn) {
                clear_reg_bit(UART5_INTERRUPT_CONTROL_REG_IEC_TX, UART5_INTERRUPT_CONTROL_BIT_TX);
            }
            break;
        #endif
        #ifdef UART_MODULE_6
        case hal_ll_module_num(UART_MODULE_6):
            if (HAL_LL_CORE_IRQ_RX == IRQn) {
                clear_reg_bit(UART6_INTERRUPT_CONTROL_REG_IEC_RX, UART6_INTERRUPT_CONTROL_BIT_RX);
            } else if (HAL_LL_CORE_IRQ_TX == IRQn) {
                clear_reg_bit(UART6_INTERRUPT_CONTROL_REG_IEC_TX, UART6_INTERRUPT_CONTROL_BIT_TX);
            }
            break;
        #endif

        default:
            break;
    }
}

void hal_ll_core_set_priority_irq( uint8_t IRQn, uint8_t IRQn_priority ) {
    // Not used in this implementation.
}
