/****************************************************************************
**
** Copyright (C)  MikroElektronika d.o.o.
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
** EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES
** OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT.
** IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM,
** DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT
** OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE
** OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
**
****************************************************************************/
/*!
 * @file  flatten_me.h
 * @brief mikroSDK code flattener level selection.
 */

#ifndef __FLATTEN_ME_H__
#define __FLATTEN_ME_H__

#ifdef __cplusplus
extern "C" {
#endif

/**
 * @brief Flattening levels.
 *   @ref FLATTEN_ME_LEVEL_NONE - no code flattening done.
 *   @ref FLATTEN_ME_LEVEL_LOW  - flatten only HAL_LL APIs.
 *   @ref FLATTEN_ME_LEVEL_MID  - flatten only HAL_LL and HAL APIs.
 *   @ref FLATTEN_ME_LEVEL_HIGH - flatten all layered APIs (HAL_LL, HAL and DRV).
 */
#define FLATTEN_ME_LEVEL_NONE (0)
#define FLATTEN_ME_LEVEL_LOW  (1)
#define FLATTEN_ME_LEVEL_MID  (2)
#define FLATTEN_ME_LEVEL_HIGH (3)

// Flatten code or not?
#define FLATTEN_ME

// Flatten level selection.
#define FLATTEN_ME_LEVEL FLATTEN_ME_LEVEL_HIGH

#ifdef __cplusplus
}
#endif

#endif // __FLATTEN_ME_H__
