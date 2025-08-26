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
 * @file  hal_ll_gpio_constants.h
 * @brief GPIO HAL LL macros.
 */

#ifndef _HAL_LL_GPIO_CONSTANTS_H_
#define _HAL_LL_GPIO_CONSTANTS_H_

#ifdef __cplusplus
extern "C"{
#endif

// ===============================
// GPIO bit masks for TMPM4K
// ===============================

#define GPIO_PIN_MASK_LOW        (uint32_t)0x00FF
#define GPIO_PIN_MASK_HIGH       (uint32_t)0xFF00
#define GPIO_PIN_MASK_ALL        (uint32_t)0xFFFF

// ===============================
// GPIO configuration bits (PxCR, PxFR, PxOD, PxPUP, PxPDN)
// ===============================

// PxCR - direction
#define GPIO_CFG_PORT_DIRECTION_INPUT     (0x0UL)   // PxCR = 0 -> Input
#define GPIO_CFG_PORT_DIRECTION_OUTPUT    (0x1UL)   // PxCR = 1 -> Output

// PxFR - function selection
#define GPIO_CFG_GPIO_FUNCTION            (0x0UL)   // GPIO mode
#define GPIO_CFG_ALT_FUNCTION             (0x1UL)   // Peripheral function

// PxOD - output type
#define GPIO_CFG_OTYPE_PP                 (0x0UL)   // Push-pull
#define GPIO_CFG_OTYPE_OD                 (0x1UL)   // Open-drain

// PxPUP - pull-up enable
#define GPIO_CFG_PULL_NO                  (0x0UL)   // No pull-up/down
#define GPIO_CFG_PULL_UP                  (0x1UL)   // Pull-up enabled

// PxPDN - pull-down enable
#define GPIO_CFG_PULL_DOWN                (0x1UL)   // Pull-down enabled

// PxDATA - output value
#define GPIO_CFG_PORT_OUTPUT_LOW          (0x0UL)
#define GPIO_CFG_PORT_OUTPUT_HIGH         (0x1UL)

// PxIE - interrupt enable
#define GPIO_CFG_IRQ_DISABLE              (0x0UL)
#define GPIO_CFG_IRQ_ENABLE               (0x1UL)

// Configuration bit field positions
#define GPIO_CFG_DIRECTION_POS            (0)
#define GPIO_CFG_PULL_UP_POS              (1)
#define GPIO_CFG_PULL_DOWN_POS            (2)
#define GPIO_CFG_OTYPE_POS                (3)
#define GPIO_CFG_ALT_FUNC_POS             (4)

// Combined configuration masks for common pin modes
#define GPIO_CFG_MODE_INPUT               (GPIO_CFG_PORT_DIRECTION_INPUT)
#define GPIO_CFG_MODE_INPUT_PULLUP        (GPIO_CFG_PORT_DIRECTION_INPUT | (GPIO_CFG_PULL_UP << GPIO_CFG_PULL_UP_POS))
#define GPIO_CFG_MODE_INPUT_PULLDOWN      (GPIO_CFG_PORT_DIRECTION_INPUT | (GPIO_CFG_PULL_DOWN << GPIO_CFG_PULL_DOWN_POS))
#define GPIO_CFG_MODE_OUTPUT_PP           (GPIO_CFG_PORT_DIRECTION_OUTPUT | (GPIO_CFG_OTYPE_PP << GPIO_CFG_OTYPE_POS))
#define GPIO_CFG_MODE_OUTPUT_OD           (GPIO_CFG_PORT_DIRECTION_OUTPUT | (GPIO_CFG_OTYPE_OD << GPIO_CFG_OTYPE_POS))

#ifdef __cplusplus
}
#endif

#endif  // _HAL_LL_GPIO_CONSTANTS_H_
// ------------------------------------------------------------------------- END
