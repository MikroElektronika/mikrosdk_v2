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
 * @file  sprint.c
 * @brief Sprint function definitions.
 */

#include "conversions.h"
#include "sprint.h"
#include <string.h>

#ifdef __MIKROC__
#include "built_in.h"
#endif
// ------------------------------------------------------------- PRIVATE MACROS

#define TODO Esma

// -------------------------------------------------------------- PRIVATE TYPES

// TODO Esma

// ------------------------------------------------------------------ CONSTANTS

// TODO Esma

// ------------------------------------------------------------------ VARIABLES


// ---------------------------------------------- PRIVATE FUNCTION DECLARATIONS

// TODO Esma
static int int_to_str(int num, char *str);

static int long_to_str(long num, char *str);

// ------------------------------------------------ PUBLIC FUNCTION DEFINITIONS

// int sprintf(char *str, const char *format, ...);

int sprinti(char *str, const char *format, ...) {
    va_list args;
    va_start(args, format);
    char *s;
    int d, count = 0;
    // char temp[20];
    char *temp;

    while (*format) {
        if (*format == '%') {
            format++;
            switch (*format) {
                case 'd':
                    d = va_arg(args, int);
                    count += int_to_str(d, temp);
                    while (*temp) {
                        *str++ = *temp++;
                    //     char *p = temp;  // Create a pointer to iterate through temp
                    //     while (*p) {
                    //         *str++ = *p++;
                    //     }
                    }
                    break;
                case 'c':
                    *str++ = (char)va_arg(args, int);
                    count++;
                    break;
                case 's':
                    s = va_arg(args, char *);
                    while (*s) {
                        *str++ = *s++;
                        count++;
                    }
                    break;
                default:
                    *str++ = '%';
                    *str++ = *format;
                    count += 2;
                    break;
            }
        } else {
            *str++ = *format;
            count++;
        }
        format++;
    }

    *str = '\0';
    va_end(args);
    return count;
}

int sprintl(char *str, const char *format, ...) {
    va_list args;
    va_start(args, format);
    char *s;
    int d;
    long ld;
    int count = 0;
    // char temp[20];
    char *temp;

    while (*format) {
        if (*format == '%') {
            format++;
            switch (*format) {
                case 'd':
                    d = va_arg(args, int);
                    count += int_to_str(d, temp);
                    while (*temp) {
                        *str++ = *temp++;
                    //     char *p = temp;  // Create a pointer to iterate through temp
                    //     while (*p) {
                    //         *str++ = *p++;
                    //     }
                    }
                    break;
                case 'l':
                    format++;
                    if (*format == 'd') {
                        ld = va_arg(args, long);
                        count += long_to_str(ld, temp);
                        while (*temp) {
                            *str++ = *temp++;
                        //     char *p = temp;  // Create a pointer to iterate through temp
                        //     while (*p) {
                        //         *str++ = *p++;
                        //     }
                        }
                    } else {
                        *str++ = '%';
                        *str++ = 'l';
                        *str++ = *format;
                        count += 3;
                    }
                    break;
                case 'c':
                    *str++ = (char)va_arg(args, int);
                    count++;
                    break;
                case 's':
                    s = va_arg(args, char *);
                    while (*s) {
                        *str++ = *s++;
                        count++;
                    }
                    break;
                default:
                    *str++ = '%';
                    *str++ = *format;
                    count += 2;
                    break;
            }
        } else {
            *str++ = *format;
            count++;
        }
        format++;
    }

    *str = '\0';
    va_end(args);
    return count;
}

// ----------------------------------------------- PRIVATE FUNCTION DEFINITIONS

// TODO Esma
/* Helper function: Convert integer to string */
static int int_to_str(int num, char *str) {
    char temp[12];
    int i = 0, j;
    bool is_negative = false;

    if (num < 0) {
        is_negative = true;
        num = -num;
    }

    do {
        temp[i++] = (num % 10) + '0';
        num /= 10;
    } while (num > 0);

    if (is_negative) {
        temp[i++] = '-';
    }

    for (j = 0; j < i; j++) {
        str[j] = temp[i - j - 1];
    }
    str[i] = '\0';

    return i;
}

/* Helper function: Convert long integer to string */
static int long_to_str(long num, char *str) {
    char temp[20];
    int i = 0, j;
    bool is_negative = false;

    if (num < 0) {
        is_negative = true;
        num = -num;
    }

    do {
        temp[i++] = (num % 10) + '0';
        num /= 10;
    } while (num > 0);

    if (is_negative) {
        temp[i++] = '-';
    }

    for (j = 0; j < i; j++) {
        str[j] = temp[i - j - 1];
    }
    str[i] = '\0';

    return i;
}

// ------------------------------------------------------------------------- END
