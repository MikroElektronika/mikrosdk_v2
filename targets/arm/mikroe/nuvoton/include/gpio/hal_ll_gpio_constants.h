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

#define GPIO_MODER_MODER0                   0x3UL               // Reset Mode

#define GPIO_MODE_INPUT                     0x0UL               // Input Mode
#define GPIO_MODE_OUTPUT                    0x1UL               // Output Mode
#define GPIO_MODE_OPEN_DRAIN                0x2UL               // Open-Drain Mode
#define GPIO_MODE_QUASI                     0x3UL               // Quasi-bidirectional Mode

#define GPIO_INT_RISING                     0x00010000UL        // Interrupt enable by Input Rising Edge
#define GPIO_INT_FALLING                    0x00000001UL        // Interrupt enable by Input Falling Edge
#define GPIO_INT_BOTH_EDGE                  0x00010001UL        // Interrupt enable by both Rising Edge and Falling Edge
#define GPIO_INT_HIGH                       0x01010000UL        // Interrupt enable by Level-High 
#define GPIO_INT_LOW                        0x01000001UL        // Interrupt enable by Level-Level

#define GPIO_INTTYPE_EDGE                   0x0UL               // GPIO_INTTYPE Setting for Edge Trigger Mode
#define GPIO_INTTYPE_LEVEL                  0x1UL               // GPIO_INTTYPE Setting for Edge Level Mode

#define GPIO_SLEWCTL_NORMAL                 0x0UL               // GPIO slew setting for normal Mode 
#define GPIO_SLEWCTL_HIGH                   0x1UL               // GPIO slew setting for high Mode 
#define GPIO_SLEWCTL_FAST                   0x2UL               // GPIO slew setting for fast Mode 

#define GPIO_PUSEL_DISABLE0                 0x0UL               // GPIO PUSEL setting for Disable Mode 
#define GPIO_PUSEL_PULL_UP                  0x1UL               // GPIO PUSEL setting for Pull-up Mode 
#define GPIO_PUSEL_PULL_DOWN                0x2UL               // GPIO PUSEL setting for Pull-down Mode
#define GPIO_PUSEL_DISABLE3                 0x3UL               // GPIO PUSEL setting for Disable Mode

#define GPIO_PIN_MASK_LOW                   0x00FFUL
#define GPIO_PIN_MASK_HIGH                  0xFF00UL
#define GPIO_PIN_MASK_ALL                   0xFFFFUL

#define GPIO_PORT_LOW_MODE_OUTPUT           0x00005555UL
#define GPIO_PORT_HIGH_MODE_OUTPUT          0x55550000UL
#define GPIO_PORT_ALL_MODE_OUTPUT           0x55555555UL

#define GPIO_PORT_LOW_PUSEL_PULL_DOWN       0x0000AAAA
#define GPIO_PORT_HIGH_PUSEL_PULL_DOWN      0xAAAA0000
#define GPIO_PORT_ALL_PUSEL_PULL_DOWN       0xAAAAAAAA

#define GPIO_MODE_PIN_WIDTH                 (2)

#define GPIO_MFP_ADDR                       0x40000030UL
#define _GPIO_MFP_ADDR_P                    (uint32_t*)GPIO_MFP_ADDR

#define GPIO_MFP_PIN_WITH                   (4)
#define GPIO_MFP_RESET                      0xFUL

#ifdef __cplusplus
}
#endif

#endif  // _HAL_LL_GPIO_CONSTANTS_H_
// ------------------------------------------------------------------------- END