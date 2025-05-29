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
 * @brief GPIO low-level register map structure.
 *
 * @details
 * This structure represents the memory layout of the GPIO peripheral registers
 * at the hardware abstraction layer (HAL) low-level (LL) interface.
 * It contains all the essential registers required to configure and control
 * GPIO pins, including mode, output type, speed, pull-up/pull-down, input/output data,
 * bit set/reset, lock, and alternate function registers.
 */
typedef struct hal_ll_gpio_base_handle
{
    uint32_t moder;    /**< GPIO port mode register */
    uint32_t otyper;   /**< GPIO port output type register */
    uint32_t ospeedr;  /**< GPIO port output speed register */
    uint32_t pupdr;    /**< GPIO port pull-up/pull-down register */
    uint32_t idr;      /**< GPIO port input data register */
    uint32_t odr;      /**< GPIO port output data register */
    uint32_t bsrr;     /**< GPIO port bit set/reset register */
    uint32_t lckr;     /**< GPIO port configuration lock register */
    uint32_t afrl;     /**< GPIO alternate function low register */
    uint32_t afrh;     /**< GPIO alternate function high register */
    uint32_t brr;      /**< GPIO port bit reset register */
} hal_ll_gpio_base_handle_t;

#ifdef __cplusplus
}
#endif

#endif  // _HAL_LL_GPIO_STRUCT_TYPE_H_
// ------------------------------------------------------------------------- END
