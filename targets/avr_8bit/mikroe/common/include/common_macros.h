/****************************************************************************
**
** Copyright (C) 2022 MikroElektronika d.o.o.
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
 * @file  common_macros.h
 * @brief Macros (common per architecture type).
 */

#ifndef _COMMON_MACROS_H_
#define _COMMON_MACROS_H_

#ifdef __cplusplus
extern "C"{
#endif

#ifdef __MIKROC_AI__
    #define __weak __attribute__((weak))
#else
    #define __weak
#endif

// One Wire
#ifdef MACRO_USAGE_ONE_WIRE
#define ONE_WIRE_CMD_ROM_READ (0x33)
#define ONE_WIRE_CMD_ROM_SKIP (0xCC)
#define ONE_WIRE_CMD_ROM_MATCH (0x55)
#define ONE_WIRE_CMD_ROM_SEARCH (0xF0)
#define ONE_WIRE_CMD_ROM_READ_LEGACY (0x0F)
#endif
// EOF One Wire

#ifdef __cplusplus
}
#endif

#endif // _COMMON_MACROS_H_
// ------------------------------------------------------------------------- END
