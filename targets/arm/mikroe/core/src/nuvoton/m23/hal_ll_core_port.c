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
 * @file  hal_ll_core_port.c
 * @brief This file contains all low level function definitions for chip specific core functionality.
 * @note  Refers to all M23 cortex chips.
 */

#include "hal_ll_core_defines.h"
#include "hal_ll_bit_control.h"

void hal_ll_core_port_nvic_enable_irq( uint8_t IRQn )
{
    if ( IRQn < 0 )
        return;

    uint8_t iser_number = (((uint32_t)IRQn) >> 5UL);

    switch ( iser_number ) {
    case 0:
        set_reg_bit( HAL_LL_CORE_NVIC_ISER_0, ( IRQn & HAL_LL_CORE_IRQ_MASK ) );
        break;
    case 1:
        set_reg_bit( HAL_LL_CORE_NVIC_ISER_1, ( IRQn & HAL_LL_CORE_IRQ_MASK ) );
        break;
    case 2:
        set_reg_bit( HAL_LL_CORE_NVIC_ISER_2, ( IRQn & HAL_LL_CORE_IRQ_MASK ) );
        break;
    case 3:
        set_reg_bit( HAL_LL_CORE_NVIC_ISER_3, ( IRQn & HAL_LL_CORE_IRQ_MASK ) );
        break;

    default:
        break;
    }
}

void hal_ll_core_port_nvic_disable_irq( uint8_t IRQn )
{
    if ( IRQn < 0 )
        return;

    uint8_t icer_number = (((uint32_t)IRQn) >> 5UL);

    switch ( icer_number ) {
    case 0:
        set_reg_bit( HAL_LL_CORE_NVIC_ICER_0, ( IRQn & HAL_LL_CORE_IRQ_MASK ) );
        break;
    case 1:
        set_reg_bit( HAL_LL_CORE_NVIC_ICER_1, ( IRQn & HAL_LL_CORE_IRQ_MASK ) );
        break;
    case 2:
        set_reg_bit( HAL_LL_CORE_NVIC_ICER_2, ( IRQn & HAL_LL_CORE_IRQ_MASK ) );
        break;
    case 3:
        set_reg_bit( HAL_LL_CORE_NVIC_ICER_3, ( IRQn & HAL_LL_CORE_IRQ_MASK ) );
        break;

    default:
        break;
    }
}

void hal_ll_core_port_nvic_set_priority_irq( uint8_t IRQn, uint8_t IRQn_priority )
{
    if ( IRQn < 0 )
        return;

    uint8_t ipr_index = IRQn >> 2;
    uint8_t ipr_shift = ( IRQn & 0x3 ) * 8;

    volatile uint32_t* ipr_register = HAL_LL_CORE_NVIC_IPR_0 + ipr_index;

    uint32_t register_value = *ipr_register;
    register_value &= ~( HAL_LL_CORE_NVIC_IPR_MASK << ipr_shift );
    register_value |= ( ( IRQn_priority << ( 8U - HAL_LL_NVIC_PRIO_BTIS ) ) & HAL_LL_CORE_NVIC_IPR_MASK ) << ipr_shift;

    *ipr_register = register_value;
}
// ------------------------------------------------------------------------- END
