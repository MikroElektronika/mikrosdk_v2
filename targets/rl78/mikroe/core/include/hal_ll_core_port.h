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
 * @file  hal_ll_core_port.h
 * @brief This file contains all function prototypes for the low level ported CORE library functions.
 *        These functions are chip specific.
 */

#ifndef _HAL_LL_CORE_PORT_H_
#define _HAL_LL_CORE_PORT_H_

#ifdef __cplusplus
extern "C"
{
#endif

#include "stdint.h"
#include <stdbool.h>

/**
 * @brief  Sets or clears the interrupt mask flag (MKxx) of an interrupt source.
 *
 * @param[in] IRQn Vector table address of the interrupt source.
 * @param[in] mask True masks (disables) the source, false unmasks it.
 *
 * @return void None.
 */
void hal_ll_core_port_irq_mask( uint8_t IRQn, bool mask );

/**
 * @brief  Sets or clears the interrupt request flag (IFxx) of an interrupt source.
 *
 * Setting the flag from software requests the interrupt
 * the same way the peripheral would.
 *
 * @param[in] IRQn Vector table address of the interrupt source.
 * @param[in] state True sets the request flag, false clears it.
 *
 * @return void None.
 */
void hal_ll_core_port_irq_flag( uint8_t IRQn, bool state );

/**
 * @brief  Sets the priority level (PR1xx:PR0xx) of an interrupt source.
 *
 * @param[in] IRQn Vector table address of the interrupt source.
 * @param[in] IRQn_priority One of hal_ll_core_irq_priority_levels, 0 is the highest.
 *
 * @return void None.
 */
void hal_ll_core_port_irq_priority( uint8_t IRQn, uint8_t IRQn_priority );

#ifdef __cplusplus
}
#endif

#endif // _HAL_LL_CORE_PORT_H_
// ------------------------------------------------------------------------- END
