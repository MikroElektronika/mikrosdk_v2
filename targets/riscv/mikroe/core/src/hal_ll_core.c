/****************************************************************************
**
** Copyright (C) 2022 MikroElektronika d.o.o.
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
 * @file  hal_ll_core.c
 * @brief This file contains all CORE functionalities for RISC-V chips.
 */

#include "hal_ll_core_defines.h"
#include "hal_ll_core_port.h"
#include "hal_ll_bit_control.h"

void hal_ll_core_enable_interrupts( void )
{
    set_csr(mstatus, MSTATUS_MIE);
}

void hal_ll_core_disable_interrupts( void )
{
    clear_csr(mstatus, MSTATUS_MIE);
}

void hal_ll_core_enable_irq( uint8_t IRQn )
{
    hal_ll_core_port_eclic_enable_irq( IRQn );
}

void hal_ll_core_disable_irq( uint8_t IRQn )
{
    hal_ll_core_port_eclic_disable_irq( IRQn );
}

void hal_ll_core_set_priority_irq( uint8_t IRQn, uint8_t IRQn_priority )
{
    hal_ll_core_port_eclic_set_priority_irq( IRQn, IRQn_priority );
}
// ------------------------------------------------------------------------- END
