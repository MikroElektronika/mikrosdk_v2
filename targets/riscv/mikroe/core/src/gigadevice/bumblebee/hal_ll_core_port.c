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
 * @file  hal_ll_core_port.c
 * @brief This file contains all low level function definitions for chip specific core functionality.
 * @note  Refers to all BumbleBee RISC-V core chips.
 */

#include "hal_ll_core_defines.h"
#include "hal_ll_bit_control.h"

static eclic *eclic_regs = (eclic *)ECLIC_ADDR_BASE;

void hal_ll_core_port_clic_mode_enable() {
    uint32_t mtvec_value = read_csr( mtvec );
    mtvec_value = mtvec_value & MTVEC_CLIC_INTERRUPT_MODE_MASK;
    mtvec_value = mtvec_value | MTVEC_CLIC_INTERRUPT_MODE;
    write_csr( mtvec, mtvec_value );
}

void hal_ll_core_port_eclic_set_vectored_mode( uint32_t IRQn ) {
    uint8_t old_clicint_attr = GET_ECLIC_CLICINT_ATTR( IRQn );
    uint8_t new_clicint_attr = ( old_clicint_attr | CLICINT_ATTR_VECTORED_INTERRUPT );
    SET_ECLIC_CLICINT_ATTR( IRQn, new_clicint_attr );
}

void hal_ll_core_port_eclic_init ( uint32_t IRQn ) {
    hal_ll_core_port_clic_mode_enable();
    hal_ll_core_port_eclic_set_vectored_mode( IRQn );
}

void hal_ll_core_port_eclic_enable_irq( uint8_t IRQn ) {
    hal_ll_core_port_eclic_init( IRQn );
    SET_ECLIC_CLICINT_IE( IRQn, 1 );
}

void hal_ll_core_port_eclic_disable_irq( uint8_t IRQn ) {
    SET_ECLIC_CLICINT_IE( IRQn, 0 );
}

uint8_t hal_ll_core_port_eclic_get_cfg_nlbits() {
    uint8_t nlbits = eclic_regs->cfg;
    nlbits = ( nlbits & CLIC_CFG_NLBITS_MASK ) >> CLIC_CFG_NLBITS_SHIFT;
    return nlbits;
}

uint8_t hal_ll_core_port_eclic_get_info_clicintctlbits() {
    uint8_t clicintctlbits = eclic_regs->info;
    clicintctlbits = ( clicintctlbits & CLIC_INFO_CLICINTCTLBITS_MASK ) >> CLIC_INFO_CLICINTCTLBITS_SHIFT;
    return clicintctlbits;
}

void hal_ll_core_port_eclic_set_irq_lvl_abs( uint32_t IRQn, uint8_t IRQn_level ) {
    uint8_t nlbits = hal_ll_core_port_eclic_get_cfg_nlbits();
    uint8_t clicintctlbits = hal_ll_core_port_eclic_get_info_clicintctlbits();

    if ( nlbits > clicintctlbits ) {
        nlbits = clicintctlbits;
    }
    // Shift level into correct bit position
    uint8_t lvl = IRQn_level << ( 8 - nlbits );
    // Read from clicint_ctl
    uint8_t current_clicint_ctl = GET_ECLIC_CLICINT_CTL( IRQn );
    // Shift clicint_ctl left to mask off unused bits
    current_clicint_ctl = current_clicint_ctl << nlbits;
    // Shift clicint_ctl into correct bit position
    current_clicint_ctl = current_clicint_ctl >> nlbits;

    SET_ECLIC_CLICINT_CTL( IRQn, ( current_clicint_ctl | lvl ));
}

void hal_ll_core_port_eclic_set_priority_irq( uint8_t IRQn, uint8_t IRQn_priority ) {
    uint8_t nlbits = hal_ll_core_port_eclic_get_cfg_nlbits();
    uint8_t clicintctlbits = hal_ll_core_port_eclic_get_info_clicintctlbits();

    if ( nlbits >= clicintctlbits ) {
        nlbits = clicintctlbits;
    }
    // Shift priority into correct bit position
    IRQn_priority = IRQn_priority << ( 8 - clicintctlbits );
    // Read from clicint_ctl
    uint8_t current_clicint_ctl = GET_ECLIC_CLICINT_CTL( IRQn );
    // Shift clicint_ctl right to mask off unused bits
    current_clicint_ctl = current_clicint_ctl >> ( 8 - nlbits );
    // Shift clicint_ctl into correct bit position
    current_clicint_ctl = current_clicint_ctl << ( 8 - nlbits );

    SET_ECLIC_CLICINT_CTL( IRQn, ( current_clicint_ctl | IRQn_priority ));
}

void hal_ll_core_port_eclic_set_priority_level( uint32_t IRQn, uint8_t IRQn_level, uint8_t IRQn_priority ) {
    hal_ll_core_port_eclic_set_irq_lvl_abs( IRQn, IRQn_level );
    hal_ll_core_port_eclic_set_priority_irq( IRQn, IRQn_priority );
}

void hal_ll_core_port_eclic_priority_group_set( uint32_t prigroup ) {
    // Shift nlbits to correct position
    uint8_t nlbits_shifted = prigroup << CLIC_CFG_NLBITS_SHIFT;

    // Read the current cliccfg
    uint8_t old_cfg = eclic_regs->cfg;
    uint8_t new_cfg = ( old_cfg & ( ~CLIC_CFG_NLBITS_MASK )) | ( CLIC_CFG_NLBITS_MASK & nlbits_shifted );

    eclic_regs->cfg = new_cfg;
}

// ------------------------------------------------------------------------- END
