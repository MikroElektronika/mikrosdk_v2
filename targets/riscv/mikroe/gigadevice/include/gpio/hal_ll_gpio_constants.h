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
 * @file  hal_ll_gpio_constants.h
 * @brief GPIO HAL LL macros.
 */

#ifndef _HAL_LL_GPIO_CONSTANTS_H_
#define _HAL_LL_GPIO_CONSTANTS_H_

#ifdef __cplusplus
extern "C"{
#endif

/* GPIO pin masks. */
#define GPIO_PIN_MASK_LOW                  (0x00FFUL)
#define GPIO_PIN_MASK_HIGH                 (0xFF00UL)
#define GPIO_PIN_MASK_ALL                  (0xFFFFUL)
#define GPIO_PIN_NAME_MASK                 (0xFFUL)
#define GPIO_AFIO_PCF0_MASK                (0x3741FFFFUL)

/* GPIOx_CTL register macros. */
#define GPIO_CTL_MODE_INPUT                (0x0UL)
#define GPIO_CTL_MODE_OUTPUT_SPEED_M2      (0x2UL)
#define GPIO_CTL_MODE_OUTPUT_SPEED_M10     (0x1UL)
#define GPIO_CTL_MODE_OUTPUT_SPEED_M50     (0x3UL)

#define GPIO_CTL_CFG_INPUT_ANALOG          (0x0UL)
#define GPIO_CTL_CFG_INPUT_FLOATING        (0x4UL)
#define GPIO_CTL_CFG_INPUT_PUPD            (0x8UL)

#define GPIO_CTL_CFG_OUTPUT_GPIO_PP        (0x0UL)
#define GPIO_CTL_CFG_OUTPUT_GPIO_OD        (0x4UL)
#define GPIO_CTL_CFG_OUTPUT_AFIO_PP        (0x8UL)
#define GPIO_CTL_CFG_OUTPUT_AFIO_OD        (0xCUL)

#define GPIO_MASK_BITS_CTL                 (0xCUL)
#define GPIO_MASK_BITS_MD                  (0x3UL)

/* GPIOx_LOCK register macros. */
#define GPIO_LOCK_KEY_BIT_POS              (16)
#define GPIO_LOCK_KEY_BIT_MASK             (1UL << GPIO_LOCK_KEY_BIT_POS)

/* GPIO general setting macros. */
#define GPIO_CFG_ANALOG_INPUT              (GPIO_CTL_MODE_INPUT | GPIO_CTL_CFG_INPUT_ANALOG)
#define GPIO_CFG_DIGITAL_INPUT             (GPIO_CTL_MODE_INPUT | GPIO_CTL_CFG_INPUT_FLOATING)
#define GPIO_CFG_DIGITAL_OUTPUT            (GPIO_CTL_MODE_OUTPUT_SPEED_M50 | GPIO_CTL_CFG_OUTPUT_GPIO_PP)

#ifdef __cplusplus
}
#endif

#endif  // _HAL_LL_GPIO_CONSTANTS_H_
// ------------------------------------------------------------------------- END
