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
 * @note  Refers to all RL78 chips.
 */

#include "hal_ll_core_defines.h"
#include "hal_ll_core_port.h"
#include "hal_ll_bit_control.h"

/**
 * @brief  Read-modify-write of an interrupt control register bit.
 *
 * The MKxx/IFxx/PRxx registers are shared by eight interrupt sources and
 * may also be changed from interrupt handlers, so the update runs with
 * interrupts disabled. The previous IE state is restored afterwards.
 *
 * @param[in] reg Register address.
 * @param[in] bit Bit position.
 * @param[in] state True sets the bit, false clears it.
 *
 * @return void None.
 */
static void hal_ll_core_port_write_bit( volatile uint8_t *reg, uint8_t bit, bool state ) {
    uint8_t ie = *( volatile uint8_t * )HAL_LL_CORE_PSW_ADDR & HAL_LL_CORE_PSW_IE;

    hal_ll_core_disable_int_asm;

    if ( state ) {
        set_reg_bit( reg, bit );
    } else {
        clear_reg_bit( reg, bit );
    }

    if ( ie ) {
        hal_ll_core_enable_int_asm;
    }
}

void hal_ll_core_port_irq_mask( uint8_t IRQn, bool mask ) {
    if ( ( IRQn < HAL_LL_CORE_IRQ_VECTOR_FIRST ) || ( IRQn > HAL_LL_CORE_IRQ_VECTOR_LAST ) ) {
        return;
    }

    hal_ll_core_port_write_bit( hal_ll_core_irq_reg( IRQn, HAL_LL_CORE_IRQ_MK_OFFSET ),
                                hal_ll_core_irq_bit( IRQn ), mask );
}

void hal_ll_core_port_irq_flag( uint8_t IRQn, bool state ) {
    if ( ( IRQn < HAL_LL_CORE_IRQ_VECTOR_FIRST ) || ( IRQn > HAL_LL_CORE_IRQ_VECTOR_LAST ) ) {
        return;
    }

    hal_ll_core_port_write_bit( hal_ll_core_irq_reg( IRQn, 0 ),
                                hal_ll_core_irq_bit( IRQn ), state );
}

void hal_ll_core_port_irq_priority( uint8_t IRQn, uint8_t IRQn_priority ) {
    if ( ( IRQn < HAL_LL_CORE_IRQ_VECTOR_FIRST ) || ( IRQn > HAL_LL_CORE_IRQ_VECTOR_LAST ) ||
         ( IRQn_priority > HAL_LL_IVT_PRIORITY_LEVEL_3 ) ) {
        return;
    }

    // Level = PR1xx:PR0xx.
    hal_ll_core_port_write_bit( hal_ll_core_irq_reg( IRQn, HAL_LL_CORE_IRQ_PR0_OFFSET ),
                                hal_ll_core_irq_bit( IRQn ), IRQn_priority & 0x01 );
    hal_ll_core_port_write_bit( hal_ll_core_irq_reg( IRQn, HAL_LL_CORE_IRQ_PR1_OFFSET ),
                                hal_ll_core_irq_bit( IRQn ), IRQn_priority & 0x02 );
}

// ------------------------------------------------------------------------- END
