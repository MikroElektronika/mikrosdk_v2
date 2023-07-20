/****************************************************************************
**
** Copyright (C) 2023 MikroElektronika d.o.o.
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

#define GPIO_MUX_OFFSET                    0x8UL
#define GPIO_PIN_NAME_MASK                 0x1FUL
// Pull Select
#define GPIO_CFG_PULL_UP                   0x1UL
#define GPIO_CFG_PULL_DOWN                 0x0
// Pull Enable
#define GPIO_CFG_PULL_ENABLE               0x2UL
#define GPIO_CFG_PULL_DISABLE              0x0
// Slew Rate Enable
#define GPIO_CFG_SLEW_RATE_SLOW            0x4UL
#define GPIO_CFG_SLEW_RATE_FAST            0x0
// Passive Filter Enable
#define GPIO_CFG_PASSIVE_FILT_ENABLE       0x10UL
#define GPIO_CFG_PASSIVE_FILT_DISABLE      0x0
// Open Drain Enable
#define GPIO_CFG_TYPE_OD_ENABLED           0x20UL
#define GPIO_CFG_TYPE_OD_DISABLED          0x0
// Drive Strength Enable
#define GPIO_CFG_DRIVE_STRENGTH_HIGH       0x40UL
#define GPIO_CFG_DRIVE_STRENGTH_LOW        0x0

#define GPIO_CFG_MODE_ANALOG               0x10000UL
#define GPIO_CFG_MODE_INPUT                0x20000UL
#define GPIO_CFG_MODE_OUTPUT               0x40000UL
#define GPIO_CFG_MODE_ALT_FUNCTION         0x80000UL

// Pin Mux Alternate Function
#define GPIO_CFG_MUX_ALT0                  0x0UL
#define GPIO_CFG_MUX_ALT1                  0x100UL
#define GPIO_CFG_MUX_ALT2                  0x200UL
#define GPIO_CFG_MUX_ALT3                  0x300UL
#define GPIO_CFG_MUX_ALT4                  0x400UL
#define GPIO_CFG_MUX_ALT5                  0x500UL
#define GPIO_CFG_MUX_ALT6                  0x600UL
#define GPIO_CFG_MUX_ALT7                  0x700UL

#define GPIO_CFG_ANALOG_INPUT              ( GPIO_CFG_MODE_ANALOG | GPIO_CFG_MUX_ALT0 )
#define GPIO_CFG_DIGITAL_INPUT             ( GPIO_CFG_MODE_INPUT | GPIO_CFG_PULL_ENABLE | GPIO_CFG_SLEW_RATE_SLOW | \
                                             GPIO_CFG_PASSIVE_FILT_DISABLE | GPIO_CFG_DRIVE_STRENGTH_LOW | GPIO_CFG_MUX_ALT1 )
#define GPIO_CFG_DIGITAL_OUTPUT            ( GPIO_CFG_MODE_OUTPUT | GPIO_CFG_PULL_DISABLE | GPIO_CFG_SLEW_RATE_SLOW | \
                                             GPIO_CFG_PASSIVE_FILT_DISABLE | GPIO_CFG_TYPE_OD_DISABLED | GPIO_CFG_DRIVE_STRENGTH_LOW | \
                                             GPIO_CFG_MUX_ALT1 )

#ifdef __cplusplus
}
#endif

#endif  // _HAL_LL_GPIO_CONSTANTS_H_
// ------------------------------------------------------------------------- END
