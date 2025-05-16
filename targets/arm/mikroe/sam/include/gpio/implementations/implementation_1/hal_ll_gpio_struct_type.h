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
/**
 * @file  hal_ll_gpio_struct_type.h
 * @brief GPIO HAL LL register structure typedef.
 */

#ifndef _HAL_LL_GPIO_STRUCT_TYPE_H_
#define _HAL_LL_GPIO_STRUCT_TYPE_H_

#ifdef __cplusplus
extern "C"{
#endif

#include <stdint.h>

/**
 * @brief GPIO base handle structure.
 *
 * @details
 * This structure represents the base handle for GPIO registers in the HAL LL (Hardware Abstraction Layer Low Level).
 * It contains pointers and values corresponding to various GPIO control registers such as input-output controller,
 * output configuration, input filter, output signal, interrupt controller, multi-driver controller, pull-up resistor disabling,
 * and peripheral ABCD select registers.
 */
typedef struct hal_ll_gpio_base_handle
{
    hal_ll_gpio_register_handle_t pio;                  /* Parallel input-output controller */
    hal_ll_gpio_register_handle_t output;               /* Output configuration controller */
    hal_ll_gpio_register_handle_t filter;               /* Input filter controller */
    hal_ll_gpio_signal_register_handle_t signal;        /* Output signal controller */
    hal_ll_gpio_interrupt_register_handle_t interrupt;  /* IO interrupt controller */
    hal_ll_gpio_register_handle_t multi_driver;         /* Multi-driver controller */
    hal_ll_gpio_register_handle_t pullup_off;           /* Pull-up resistor disabling controller */
    uint32_t abcdsr0;                                   /* Peripheral ABCD Select Register 0 */
    uint32_t abcdsr1;                                   /* Peripheral ABCD Select Register 1 */
} hal_ll_gpio_base_handle_t;

#ifdef __cplusplus
}
#endif

#endif  // _HAL_LL_GPIO_STRUCT_TYPE_H_
// ------------------------------------------------------------------------- END
