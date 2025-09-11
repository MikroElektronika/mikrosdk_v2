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
// GPIO configuration bits (PxCR, PxFR, PxOD, PxPUP, PxPDN, PxIE)
// ===============================

// Individual GPIO control flags (bit flags for flexible configuration)
#define GPIO_CFG_CR                         (0x01)   // Control Register (direction) flag
#define GPIO_CFG_OD                         (0x02)   // Open Drain flag
#define GPIO_CFG_PULL_UP                    (0x04)   // Pull-up flag
#define GPIO_CFG_PULL_DOWN                  (0x08)   // Pull-down flag
#define GPIO_CFG_IE                         (0x10)   // Input Enable flag

#define GPIO_CFG_PORT_DIRECTION_OUTPUT      (GPIO_CFG_CR)
#define GPIO_CFG_MODE_DIGITAL_INPUT         (GPIO_CFG_IE)
#define GPIO_CFG_MODE_ANALOG_INPUT          (0x00)

#ifdef __cplusplus
}
#endif

#endif  // _HAL_LL_GPIO_CONSTANTS_H_
// ------------------------------------------------------------------------- END
