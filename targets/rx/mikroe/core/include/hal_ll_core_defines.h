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
 * @file  hal_ll_core_defines.h
 * @brief Core specific defines and enums used for RX chips.
 */

#ifndef _HAL_LL_CORE_DEFINES_H_
#define _HAL_LL_CORE_DEFINES_H_

#ifdef __cplusplus
extern "C"{
#endif

#include <stdint.h>

#define hal_ll_core_enable_int_asm   __asm__ volatile ( "setpsw i" )
#define hal_ll_core_disable_int_asm  __asm__ volatile ( "clrpsw i" )

#define HAL_LL_CORE_ICU_BASE         ( 0x00087000UL )
#define HAL_LL_CORE_ICU_IER_BASE     ( HAL_LL_CORE_ICU_BASE + 0x200UL )
#define HAL_LL_CORE_ICU_IPR_BASE     ( HAL_LL_CORE_ICU_BASE + 0x300UL )

#define HAL_LL_CORE_ICU_VECTOR_MIN   ( 16 )
#define HAL_LL_CORE_PRIORITY_MASK    ( 0x0F )

#define HAL_LL_CORE_ICU_IER( vector ) \
( *( volatile uint8_t * )( HAL_LL_CORE_ICU_IER_BASE + (( vector ) >> 3 )))

#define HAL_LL_CORE_ICU_IPR( vector ) \
( *( volatile uint8_t * )( HAL_LL_CORE_ICU_IPR_BASE + ( vector )))

#define hal_ll_core_irq( vector )    ( uint8_t )( 1U << (( vector ) & 0x07 ))

#ifdef __cplusplus
}
#endif

#endif // _HAL_LL_CORE_DEFINES_H_
// ------------------------------------------------------------------------- END
