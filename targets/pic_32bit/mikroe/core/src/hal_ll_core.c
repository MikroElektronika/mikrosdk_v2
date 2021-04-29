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

void hal_ll_core_enable_interrupts( void ) {
    hal_ll_core_enable_int_asm;
}

void hal_ll_core_disable_interrupts( void ) {
    hal_ll_core_disable_int_asm;
}

void hal_ll_core_enable_irq( uint8_t IRQn ) {
    if( 38 == IRQn ) {
        set_reg_bit( HAL_LL_IEC1_ADDRESS, 9 );
    } else if( 39 == IRQn ) {
        set_reg_bit( HAL_LL_IEC1_ADDRESS, 10 );
    } else if( 41 == IRQn ) {
        set_reg_bit( HAL_LL_IEC1_ADDRESS, 6 );
    } else if( 42 == IRQn ) {
        set_reg_bit( HAL_LL_IEC1_ADDRESS, 7 );
    #ifdef HAL_LL_IEC2_ADDRESS
    } else if ( IRQn <= 75 && IRQn >= 64 ) {
        set_reg_bit( HAL_LL_IEC2_ADDRESS, IRQn - 64 );
    #endif
    } else if ( IRQn <= 63 && IRQn >= 32 ) {
        set_reg_bit( HAL_LL_IEC1_ADDRESS, IRQn - 32 );
    } else if ( IRQn <= 31 && IRQn >= 0 ) {
        set_reg_bit( HAL_LL_IEC0_ADDRESS, IRQn );
    }
}

void hal_ll_core_disable_irq( uint8_t IRQn ) {
    if( 38 == IRQn ) {
        clear_reg_bit( HAL_LL_IEC1_ADDRESS, 9 );
    } else if( 39 == IRQn ) {
        clear_reg_bit( HAL_LL_IEC1_ADDRESS, 10 );
    } else if( 41 == IRQn ) {
        clear_reg_bit( HAL_LL_IEC1_ADDRESS, 6 );
    } else if( 42 == IRQn ) {
        clear_reg_bit( HAL_LL_IEC1_ADDRESS, 7 );
    #ifdef HAL_LL_IEC2_ADDRESS
    } else if ( IRQn <= 75 && IRQn >= 64 ) {
        clear_reg_bit( HAL_LL_IEC2_ADDRESS, IRQn - 64 );
    #endif
    } else if ( IRQn <= 63 && IRQn >= 32 ) {
        clear_reg_bit( HAL_LL_IEC1_ADDRESS, IRQn - 32 );
    } else if ( IRQn <= 31 && IRQn >= 0 ) {
        clear_reg_bit( HAL_LL_IEC0_ADDRESS, IRQn );
    }
}

void hal_ll_core_set_priority_irq( uint8_t IRQn, uint8_t IRQn_priority ) {
    switch ( IRQn ) {
        #ifdef PIC32MXxx
        #ifdef HAL_LL_IVT_UART_1
        case HAL_LL_IVT_UART_1:
            set_reg_bits( HAL_LL_IVT_UART_1_ADDRESS, (uint32_t)IRQn_priority << HAL_LL_IVT_UART_1_SHIFT );
            break;
        #endif
        #ifdef HAL_LL_IVT_UART_2
        case HAL_LL_IVT_UART_2:
            set_reg_bits( HAL_LL_IVT_UART_2_ADDRESS, (uint32_t)IRQn_priority << HAL_LL_IVT_UART_2_SHIFT );
            break;
        #endif
        #ifdef HAL_LL_IVT_UART_3
        case HAL_LL_IVT_UART_3:
            set_reg_bits( HAL_LL_IVT_UART_3_ADDRESS, (uint32_t)IRQn_priority << HAL_LL_IVT_UART_3_SHIFT );
            break;
        #endif
        #ifdef HAL_LL_IVT_UART_4
        case HAL_LL_IVT_UART_4:
            set_reg_bits( HAL_LL_IVT_UART_4_ADDRESS, (uint32_t)IRQn_priority << HAL_LL_IVT_UART_4_SHIFT );
            break;
        #endif
        #ifdef HAL_LL_IVT_UART_5
        case HAL_LL_IVT_UART_5:
            set_reg_bits( HAL_LL_IVT_UART_5_ADDRESS, (uint32_t)IRQn_priority << HAL_LL_IVT_UART_5_SHIFT );
            break;
        #endif
        #ifdef HAL_LL_IVT_UART_6
        case HAL_LL_IVT_UART_6:
            set_reg_bits( HAL_LL_IVT_UART_6_ADDRESS, (uint32_t)IRQn_priority << HAL_LL_IVT_UART_6_SHIFT );
            break;
        #endif
        #elif defined(PIC32MZxx)
        #ifdef UART_MODULE_1
        case HAL_LL_IVT_UART_1_RX:
            set_reg_bits( HAL_LL_IVT_UART_1_ADDRESS_RX, (uint32_t)IRQn_priority << HAL_LL_IVT_UART_1_SHIFT_RX );
            break;
        case HAL_LL_IVT_UART_1_TX:
            set_reg_bits( HAL_LL_IVT_UART_1_ADDRESS_TX, (uint32_t)IRQn_priority << HAL_LL_IVT_UART_1_SHIFT_TX );
            break;
        #endif
        #ifdef UART_MODULE_2
        case HAL_LL_IVT_UART_2_RX:
            set_reg_bits( HAL_LL_IVT_UART_2_ADDRESS_RX, (uint32_t)IRQn_priority << HAL_LL_IVT_UART_2_SHIFT_RX );
            break;
        case HAL_LL_IVT_UART_2_TX:
            set_reg_bits( HAL_LL_IVT_UART_2_ADDRESS_TX, (uint32_t)IRQn_priority << HAL_LL_IVT_UART_2_SHIFT_TX );
            break;
        #endif
        #ifdef UART_MODULE_3
        case HAL_LL_IVT_UART_3_RX:
            set_reg_bits( HAL_LL_IVT_UART_3_ADDRESS_RX, (uint32_t)IRQn_priority << HAL_LL_IVT_UART_3_SHIFT_RX );
            break;
        case HAL_LL_IVT_UART_3_TX:
            set_reg_bits( HAL_LL_IVT_UART_3_ADDRESS_TX, (uint32_t)IRQn_priority << HAL_LL_IVT_UART_3_SHIFT_TX );
            break;
        #endif
        #ifdef UART_MODULE_4
        case HAL_LL_IVT_UART_4_RX:
            set_reg_bits( HAL_LL_IVT_UART_4_ADDRESS_RX, (uint32_t)IRQn_priority << HAL_LL_IVT_UART_4_SHIFT_RX );
            break;
        case HAL_LL_IVT_UART_4_TX:
            set_reg_bits( HAL_LL_IVT_UART_4_ADDRESS_TX, (uint32_t)IRQn_priority << HAL_LL_IVT_UART_4_SHIFT_TX );
            break;
        #endif
        #ifdef UART_MODULE_5
        case HAL_LL_IVT_UART_5_RX:
            set_reg_bits( HAL_LL_IVT_UART_5_ADDRESS_RX, (uint32_t)IRQn_priority << HAL_LL_IVT_UART_5_SHIFT_RX );
            break;
        case HAL_LL_IVT_UART_5_TX:
            set_reg_bits( HAL_LL_IVT_UART_5_ADDRESS_TX, (uint32_t)IRQn_priority << HAL_LL_IVT_UART_5_SHIFT_TX );
            break;
        #endif
        #ifdef UART_MODULE_6
        case HAL_LL_IVT_UART_6_RX:
            set_reg_bits( HAL_LL_IVT_UART_6_ADDRESS_RX, (uint32_t)IRQn_priority << HAL_LL_IVT_UART_6_SHIFT_RX );
            break;
        case HAL_LL_IVT_UART_6_TX:
            set_reg_bits( HAL_LL_IVT_UART_6_ADDRESS_TX, (uint32_t)IRQn_priority << HAL_LL_IVT_UART_6_SHIFT_TX );
            break;
        #endif
        #endif

        default:
            break;
    }
}
// ------------------------------------------------------------------------- END
