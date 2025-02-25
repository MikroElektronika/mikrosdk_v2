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
 * @file  hal_ll_core.h
 * @brief This file contains all function prototypes for the low level CORE library functions.
 *        These functions are chip specific.
 */

#ifndef _HAL_LL_CORE_H_
#define _HAL_LL_CORE_H_

#ifdef __cplusplus
extern "C"
{
#endif

#include "hal_ll_core_defines.h"

/**
 * @brief  Checks if core functionality is implemented.
 *
 * Verifies the availability of core functionality.
 *
 * @return bool True if implemented, false otherwise.
 */
bool hal_ll_core_implemented( void );

/**
 * @brief  Enables interrupts.
 *
 * Enables interrupts on global level.
 *
 * @return void None.
 */
void hal_ll_core_enable_interrupts(void);

/**
 * @brief  Disables interrupts.
 *
 * Disables interrupts on global level.
 *
 * @return void None.
 */
void hal_ll_core_disable_interrupts(void);

/**
 * @brief  Enables selected IRQ.
 *
 * Registers interrupt on hardware level and enables
 * it.
 *
 * @param[in] IRQn Chip specific IRQ number.
 * @return void None.
 */
void hal_ll_core_enable_irq(uint8_t IRQn);

/**
 * @brief  Disables selected IRQ.
 *
 * Disables previously registered interrupt
 * handler..
 *
 * @param[in] IRQn Chip specific IRQ number.
 * @return void None.
 */
void hal_ll_core_disable_irq(uint8_t IRQn);

#ifdef __cplusplus
}
#endif

#endif // _HAL_LL_CORE_H_
// ------------------------------------------------------------------------- END
