/****************************************************************************
**
** Copyright (C) 2023 MikroElektronika d.o.o.
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
 * @file  hal_ll_core_port.c
 * @brief This file contains all low level function definitions for chip specific core functionality.
 * @note  Refers to all M0 cortex chips.
 */

#include "hal_ll_core_defines.h"
#include "hal_ll_bit_control.h"

void hal_ll_core_port_nvic_enable_irq( uint8_t IRQn )
{
    if( IRQn == HAL_LL_CORE_IVT_INT_SYS_TICK )
    {
        set_reg_bit( HAL_LL_CORE_STK_CTRL, HAL_LL_CORE_IVT_TICKINT_BIT );
    } else if ( IRQn >= 16 ) {
        set_reg_bit( HAL_LL_CORE_NVIC_ISER, ( ( hal_ll_core_irq( IRQn ) ) & HAL_LL_CORE_IRQ_MASK ) );
    }
}

void hal_ll_core_port_nvic_disable_irq( uint8_t IRQn )
{
    if( IRQn == HAL_LL_CORE_IVT_INT_SYS_TICK )
    {
        clear_reg_bit( HAL_LL_CORE_STK_CTRL, HAL_LL_CORE_IVT_TICKINT_BIT );
    } else if ( IRQn >= 16 ) {
        set_reg_bit( HAL_LL_CORE_NVIC_ICER, ( ( hal_ll_core_irq( IRQn ) ) & HAL_LL_CORE_IRQ_MASK ) );
    }
}

void hal_ll_core_port_nvic_set_priority_irq( uint8_t IRQn, uint8_t IRQn_priority )
{
    uintptr_t *reg;
    uint8_t    tmp_shift;

    if ( IRQn > 15 )
    {
        reg = HAL_LL_CORE_NVIC_IPR_0 + ( ( hal_ll_core_irq( IRQn ) ) >> 2 );
        tmp_shift = ( ( ( hal_ll_core_irq( IRQn ) ) % 4 ) << 3 ) + 6;
    } else {
        if ( IRQn == 11 ) {
            reg = HAL_LL_CORE_NVIC_SCB_SHPR2;
        } else if ( IRQn > 11 ) {
            reg = HAL_LL_CORE_NVIC_SCB_SHPR3;
        }
        tmp_shift = ( ( IRQn % 4 ) << 3 ) + 6;
    }

    if ( IRQn_priority & HAL_LL_CORE_LOW_NIBBLE ) {
        *reg &= ~( HAL_LL_CORE_LOW_NIBBLE << tmp_shift );
        *reg |= ( uint32_t )IRQn_priority << tmp_shift;
    } else {
        *reg &= ~( HAL_LL_CORE_LOW_NIBBLE << tmp_shift );
        *reg |= ( uint32_t )IRQn_priority << ( tmp_shift - 6 );
    }
}
// ------------------------------------------------------------------------- END
