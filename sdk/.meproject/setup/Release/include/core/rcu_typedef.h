/****************************************************************************
**
** Copyright (C) 2022 MikroElektronika d.o.o.
** Contact: https://www.mikroe.com/contact
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
 * @file  rcu_typedef.h
 * @brief Mikroe `reset and clock unit` configuration.
 */

#ifndef __RCU_TYPEDEF_H__
#define __RCU_TYPEDEF_H__

#include <stdint.h>

#ifdef __cplusplus
extern "C" {
#endif

/**
 * @brief Timer clock structure.
 * @note Timer module 0 is clocked from APB2.
 * All other timer modules are clocked from APB1.
 */
typedef struct {
    uint32_t rcu_clocks_timer_0;
    uint32_t rcu_clocks_timer_others;
} rcu_clocks_timer_t;

/**
 * @brief Clock branches structure.
 * @note Can be utilised with the
 * `system_rcu_get_clocks` function.
 */
typedef struct {
    uint32_t rcu_clocks_system;            /* System clock frequency in Hz. */
    uint32_t rcu_clocks_ahb;               /* AHB clock frequency in Hz. */
    uint32_t rcu_clocks_exmc;              /* EXMC clock frequency in Hz. */
    uint32_t rcu_clocks_hclk;              /* HCLK clock frequency in Hz. */
    uint32_t rcu_clocks_sys_tick;          /* SysTick clock frequency in Hz. */
    uint32_t rcu_clocks_fclk;              /* FCLK clock frequency in Hz. */
    uint32_t rcu_clocks_apb1;              /* APB1(PCLK1) clock frequency in Hz. */
    uint32_t rcu_clocks_apb2;              /* APB2(PCLK2) clock frequency in Hz. */
    rcu_clocks_timer_t rcu_clocks_timer;   /* Timer clock frequency in Hz. */
    uint32_t rcu_clocks_adc;               /* ADC clock frequency in Hz. */
} rcu_clocks_t;

/* -----PUBLIC FUNCTION DECLARATIONS------ */

/**
 * @brief Returns branch clock values based on system clock.
 * @param[out] rcu_clocks Structure containing all values.
 * @details Param type is @li @ref rcu_clocks_t.
 * @retval Nothing.
 *
 * @note Structure contains following information:
 *   System clock frequency in Hz.
 *   AHB clock frequency in Hz.
 *   EXMC clock frequency in Hz.
 *   HCLK clock frequency in Hz.
 *   SysTick clock frequency in Hz.
 *   FCLK clock frequency in Hz.
 *   APB1(PCLK1) clock frequency in Hz.
 *   APB2(PCLK2) clock frequency in Hz.
 *   Timer clock frequency in Hz.
 *     Timer0 clock frequency in Hz.
 *     Other timer modules frequency in Hz.
 *   ADC clock frequency in Hz.
 */
void system_rcu_get_clocks( rcu_clocks_t* rcu_clocks );

#ifdef __cplusplus
}
#endif

#endif // __RCU_TYPEDEF_H__
