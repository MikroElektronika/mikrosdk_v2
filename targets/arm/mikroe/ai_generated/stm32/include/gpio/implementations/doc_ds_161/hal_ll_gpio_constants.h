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

// Define any specific macros here
// REPLACE_MACROS //

// Predefined macros if missing
#ifndef GPIO_OSPEEDER_OSPEEDR0
#define GPIO_OSPEEDER_OSPEEDR0             ( uint32_t )0x03
#endif
#ifndef GPIO_MODER_MODER0
#define GPIO_MODER_MODER0                  ( uint32_t )0x03
#endif
#ifndef GPIO_OTYPER_OT_0
#define GPIO_OTYPER_OT_0                   ( uint32_t )0x01
#endif
#ifndef GPIO_PUPDR_PUPDR0
#define GPIO_PUPDR_PUPDR0                  ( uint32_t )0x03
#endif

#ifndef GPIO_PIN_MASK_LOW
#define GPIO_PIN_MASK_LOW                  ( uint32_t )0x00FF
#endif
#ifndef GPIO_PIN_MASK_HIGH
#define GPIO_PIN_MASK_HIGH                 ( uint32_t )0xFF00
#endif
#ifndef GPIO_PIN_MASK_ALL
#define GPIO_PIN_MASK_ALL                  ( uint32_t )0xFFFF
#endif

#ifndef GPIO_AF_CONFIG_OFFSET
#define GPIO_AF_CONFIG_OFFSET              ( uint32_t )20
#endif
#ifndef GPIO_AF_MASK
#define GPIO_AF_MASK                       ( 0x0F )
#endif
#ifndef GPIO_PIN_NAME_MASK
#define GPIO_PIN_NAME_MASK                 ( ( uint32_t )0xFF )
#endif
#ifndef GPIO_AF_CONFIG_MASK
#define GPIO_AF_CONFIG_MASK                ( ( uint32_t )0x0F << GPIO_AF_CONFIG_OFFSET )
#endif

#ifndef GPIO_CFG_MODE_ANALOG
#define GPIO_CFG_MODE_ANALOG               ( uint32_t )0x1
#endif
#ifndef GPIO_CFG_MODE_INPUT
#define GPIO_CFG_MODE_INPUT                ( uint32_t )0x2
#endif
#ifndef GPIO_CFG_MODE_OUTPUT
#define GPIO_CFG_MODE_OUTPUT               ( uint32_t )0x4
#endif
#ifndef GPIO_CFG_MODE_ALT_FUNCTION
#define GPIO_CFG_MODE_ALT_FUNCTION         ( uint32_t )0x8
#endif
#ifndef GPIO_CFG_OTYPE_PP
#define GPIO_CFG_OTYPE_PP                  ( uint32_t )0x10
#endif
#ifndef GPIO_CFG_OTYPE_OD
#define GPIO_CFG_OTYPE_OD                  ( uint32_t )0x20
#endif
#ifndef GPIO_CFG_PULL_NO
#define GPIO_CFG_PULL_NO                   ( uint32_t )0x40
#endif
#ifndef GPIO_CFG_PULL_UP
#define GPIO_CFG_PULL_UP                   ( uint32_t )0x80
#endif
#ifndef GPIO_CFG_PULL_DOWN
#define GPIO_CFG_PULL_DOWN                 ( uint32_t )0x100
#endif
#ifndef GPIO_CFG_SPEED_LOW
#define GPIO_CFG_SPEED_LOW                 ( uint32_t )0x0
#endif
#ifndef GPIO_CFG_SPEED_MEDIUM
#define GPIO_CFG_SPEED_MEDIUM              ( uint32_t )0x200
#endif
#ifndef GPIO_CFG_SPEED_HIGH
#define GPIO_CFG_SPEED_HIGH                ( uint32_t )0x400
#endif
#ifndef GPIO_CFG_SPEED_VERY_HIGH
#define GPIO_CFG_SPEED_VERY_HIGH           ( uint32_t )0x800
#endif
#ifndef GPIO_CFG_SPEED_MAX
#define GPIO_CFG_SPEED_MAX                 ( uint32_t )0x80000
#endif

#ifndef GPIO_AHB_SHIFT
#define GPIO_AHB_SHIFT                     17
#endif

#ifndef GPIO_CFG_DIGITAL_OUTPUT
#define GPIO_CFG_DIGITAL_OUTPUT            ( GPIO_CFG_MODE_OUTPUT | GPIO_CFG_SPEED_MAX | GPIO_CFG_OTYPE_PP )
#endif
#ifndef GPIO_CFG_DIGITAL_INPUT
#define GPIO_CFG_DIGITAL_INPUT             ( GPIO_CFG_MODE_INPUT | GPIO_CFG_PULL_NO )
#endif
#ifndef GPIO_CFG_ANALOG_INPUT
#define GPIO_CFG_ANALOG_INPUT              ( GPIO_CFG_MODE_ANALOG | GPIO_CFG_PULL_NO )
#endif

#ifdef __cplusplus
}
#endif

#endif  // _HAL_LL_GPIO_CONSTANTS_H_
// ------------------------------------------------------------------------- END
