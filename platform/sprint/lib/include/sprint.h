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
 * @file  sprint.h
 * @brief Sprint function prototypes.
 */

#ifndef _SPRINT_H_
#define _SPRINT_H_

#ifdef __cplusplus
extern "C"{
#endif

#include <stdint.h>
#include <stdbool.h>
#include <stdarg.h>
#ifdef __GNUC__
#include <me_built_in.h>
#endif

/**
 * @brief Formats and stores a series of characters and values into the given buffer.
 *
 * This is a standard implementation of the C `sprintf` function, which supports a wide range of format specifiers
 * including integers, floating point numbers, characters, and strings. The formatted output is written to the
 * buffer pointed to by `str`.
 *
 * @param str Pointer to the destination buffer where the resulting string is stored.
 * @param format Format string that specifies how subsequent arguments are converted for output.
 * @param ... Additional arguments to be formatted and inserted into the resulting string.
 * @return The number of characters written, excluding the null terminator.
 */
int sprintf_me( char *str, const char *format, ... );

/**
 * @brief Formats and stores long and basic types (%ld, %d, %c, %s) into a string buffer.
 *
 * This extended version of `sprinti` adds support for long decimal values using the %ld specifier,
 * in addition to supporting %d (int), %c (char), and %s (string). It is designed for use in
 * embedded systems that require formatting of long integers without full `sprintf` support.
 *
 * @param str Pointer to the destination buffer where the resulting string is stored.
 * @param format Format string specifying the output format. Supports %ld, %d, %c, and %s.
 * @param ... Additional arguments to be formatted according to the format string.
 * @return The number of characters written, excluding the null terminator.
 */
int sprintl_me( char *str, const char *format, ... );

/**
 * @brief Formats and stores basic types (%d, %c, %s) into a string buffer.
 *
 * This lightweight implementation of `sprintf` supports a limited subset of format specifiers,
 * specifically: %d for integers, %c for characters, and %s for strings. It is optimized for use
 * in embedded systems where minimal code size is important.
 *
 * @param str Pointer to the destination buffer where the resulting string is stored.
 * @param format Format string specifying the output format. Supports %d, %c, and %s.
 * @param ... Additional arguments to be formatted according to the format string.
 * @return The number of characters written, excluding the null terminator.
 */
int sprinti_me( char *str, const char *format, ... );

#ifdef __cplusplus
}
#endif

#endif  // _SPRINT_H_
// ------------------------------------------------------------------------- END
