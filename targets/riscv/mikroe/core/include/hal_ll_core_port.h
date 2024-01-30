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

/**
 * @brief Enables selected IRQ.
 *
 * Registers interrupt on hardware level and enables
 * it.
 *
 * @param[in] IRQn Chip specific IRQ number.
 * @return void None.
 */
void hal_ll_core_port_eclic_enable_irq( uint8_t IRQn );

/**
 * @brief Disables selected IRQ.
 *
 * Disables previously registered interrupt
 * handler.
 *
 * @param[in] IRQn Chip specific IRQ number.
 * @return void None.
 */
void hal_ll_core_port_eclic_disable_irq( uint8_t IRQn );

/**
 * @brief Sets interrupt priority.
 *
 * Sets specified IRQ priority on
 * hardware level.
 *
 * @param[in] IRQn Chip specific IRQ number.
 * @param[in] IRQn_priority Interrupt priority.
 *
 * @return void None.
 */
void hal_ll_core_port_eclic_set_priority_irq( uint8_t IRQn, uint8_t IRQn_priority );

/**
 * @brief Sets interrupt level.
 *
 * Sets specified IRQ level on
 * hardware level.
 *
 * @param[in] IRQn Chip specific IRQ number.
 * @param[in] IRQn_level Interrupt level.
 *
 * @return void None.
 */
void hal_ll_core_port_eclic_set_irq_lvl_abs( uint32_t IRQn, uint8_t IRQn_level );

/**
 * @brief Sets IRQ priority and level.
 *
 * Sets specified IRQ priority and priority on
 * hardware level.
 *
 * @param[in] IRQn Chip specific IRQ number.
 * @param[in] IRQn_level Interrupt level.
 * @param[in] IRQn_priority Interrupt priority.
 *
 * @return void None.
 */
void hal_ll_core_port_eclic_set_priority_level( uint32_t IRQn, uint8_t IRQn_level, uint8_t IRQn_priority );

/**
 * @brief Sets nlbits.
 *
 * Sets cliccgf[nlbits] used to specify bit-width of
 * level and priority.
 *
 * @param[in] prigroup Desired value.
 * @return void None.
 */
void hal_ll_core_port_eclic_priority_group_set( uint32_t prigroup );

/**
 * @brief Initializes the ECLIC unit.
 *
 * Sets the CLIC interrupt mode and vectored interrupt mode.
 *
 * @param[in] IRQn Chip specific IRQ number.
 * @return void None.
 */
void hal_ll_core_port_eclic_init( uint32_t IRQn );

/**
 * @brief Sets the mtvec register.
 *
 * Selects the CLIC interrupt mode.
 *
 * @param[in] void None.
 * @return void None.
 */
void hal_ll_core_port_clic_mode_enable();

/**
 * @brief Vectored interrupt mode.
 *
 * Sets vectored interrupt mode.
 *
 * @param[in] IRQn Chip specific IRQ number.
 * @return void None.
 */
void hal_ll_core_port_eclic_set_vectored_mode( uint32_t IRQn );

/**
 * @brief Gets nlbits.
 *
 * Gets nlbits from the cfg register.
 *
 * @param[in] void None.
 * @return void None.
 */
uint8_t hal_ll_core_port_eclic_get_cfg_nlbits();

/**
 * @brief Gets clicintctlbits.
 *
 * Gets clicintctlbits from the info register.
 *
 * @param[in] void None.
 * @return void None.
 */
uint8_t hal_ll_core_port_eclic_get_info_clicintctlbits();

#ifdef __cplusplus
}
#endif

#endif // _HAL_LL_CORE_PORT_H_
// ------------------------------------------------------------------------- END
