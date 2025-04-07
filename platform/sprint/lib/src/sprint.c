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

#include <stdarg.h>
#include <stdbool.h>

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

/* Helper to convert an unsigned int to string with base (10 for decimal, 16 for hex, etc.) */
static int utoa(unsigned long value, char *str, int base, bool uppercase);

/* Helper to convert signed int to string */
static int itoa(int value, char *str);

// ------------------------------------------------ PUBLIC FUNCTION DEFINITIONS

int sprintf_me(char *str, const char *format, ...) {
    va_list args;
    va_start(args, format);

    char *orig = str;
    char temp[32];
    int precision = -1; // Default precision

    while (*format) {
        if (*format == '%') {
            format++;
            bool long_flag = false;

            if (*format == 'l') {
                long_flag = true;
                format++;
            }

            if (*format == 'h') {
                format++;
            }

            // Parse optional precision (e.g., "%.2f")
            if (*format == '.') {
                format++;
                precision = 0;
                while (*format >= '0' && *format <= '9') {
                    precision = precision * 10 + (*format - '0');
                    format++;
                }
            }

            switch (*format) {
                case 'd': {
                    if (long_flag) {
                        long value = va_arg(args, long);
                        itoa((int)value, temp);
                    } else {
                        int value = va_arg(args, int);
                        itoa(value, temp);
                    }
                    for (char *p = temp; *p; p++) *str++ = *p;
                    break;
                }
                case 'f': { // <-- Added Float
                    double value = va_arg(args, double);

                    // Default precision if not specified
                    if (precision < 0) precision = 6;

                    // Handle negative numbers
                    if (value < 0) {
                        *str++ = '-';
                        value = -value;
                    }

                    // Integer part
                    unsigned long integer_part = (unsigned long)value;
                    utoa(integer_part, temp, 10, false);
                    for (char *p = temp; *p; p++) *str++ = *p;

                    *str++ = '.';

                    // Fractional part
                    double fractional = value - (double)integer_part;
                    for (int i = 0; i < precision; i++) {
                        fractional *= 10;
                    }
                    unsigned long frac_part = (unsigned long)(fractional + 0.5); // rounding
                    utoa(frac_part, temp, 10, false);

                    // Add leading zeros if necessary
                    int frac_len = 0;
                    for (unsigned long temp_frac = frac_part; temp_frac > 0; temp_frac /= 10) frac_len++;
                    while (frac_len++ < precision) *str++ = '0';

                    for (char *p = temp; *p; p++) *str++ = *p;
                    break;
                }
                case 'u': {
                    unsigned long value;
                    if (long_flag) {
                        value = va_arg(args, unsigned long);
                    } else {
                        value = va_arg(args, unsigned int);
                    }
                    utoa(value, temp, 10, false);
                    for (char *p = temp; *p; p++) *str++ = *p;
                    break;
                }
                case 'x':
                case 'X': {
                    unsigned long value;
                    if (long_flag) {
                        value = va_arg(args, unsigned long);
                    } else {
                        value = va_arg(args, unsigned int);
                    }
                    utoa(value, temp, 16, *format == 'X');
                    for (char *p = temp; *p; p++) *str++ = *p;
                    break;
                }
                case 'h': {
                    // Handle short specifiers (%hd, %hu, %hx, %ho)
                    if (*format == 'd') {
                        short value = va_arg(args, int);  // short gets promoted to int in variadic functions
                        itoa((int)value, temp);
                    } else if (*format == 'u') {
                        unsigned short value = va_arg(args, int);  // unsigned short gets promoted to int
                        utoa(value, temp, 10, false);
                    } else if (*format == 'x') {
                        unsigned short value = va_arg(args, int);
                        utoa(value, temp, 16, false);
                    } else if (*format == 'o') {
                        unsigned short value = va_arg(args, int);
                        utoa(value, temp, 8, false);
                    }
                    for (char *p = temp; *p; p++) *str++ = *p;
                    break;
                }
                case 'o': {
                    unsigned long value;
                    if (long_flag) {
                        value = va_arg(args, unsigned long);
                    } else {
                        value = va_arg(args, unsigned int);
                    }
                    utoa(value, temp, 8, false);
                    for (char *p = temp; *p; p++) *str++ = *p;
                    break;
                }
                case 'c': {
                    char ch = (char)va_arg(args, int);
                    *str++ = ch;
                    break;
                }
                case 's': {
                    const char *s = va_arg(args, char *);
                    while (*s) *str++ = *s++;
                    break;
                }
                case '%': {
                    *str++ = '%';
                    break;
                }
                default: {
                    // Unsupported format; copy as-is
                    *str++ = '%';
                    *str++ = *format;
                    break;
                }
            }
        } else {
            *str++ = *format;
        }
        format++;
    }

    *str = '\0';
    va_end(args);
    return str - orig;
}

int sprintl_me(char *str, const char *format, ...) {
    va_list args;
    va_start(args, format);
    char *s;
    int d;
    long ld;
    int count = 0;
    char *temp;

    while (*format) {
        if (*format == '%') {
            format++;
            bool long_flag = false;

            if (*format == 'l') {
                long_flag = true;
                format++;
            }

            if (*format == 'h') {
                format++;
            }

            switch (*format) {
                case 'd':
                    d = va_arg(args, int);
                    count += int_to_str(d, temp);
                    while (*temp) {
                        *str++ = *temp++;
                    }
                    break;
                case 'l':
                    format++;
                    if (*format == 'd') {
                        ld = va_arg(args, long);
                        count += long_to_str(ld, temp);
                        while (*temp) {
                            *str++ = *temp++;
                        }
                    } else {
                        *str++ = '%';
                        *str++ = *format;
                        count += 3;
                    }
                    break;
                case 'u': {
                    unsigned long value = long_flag ? va_arg(args, unsigned long) : va_arg(args, unsigned int);
                    utoa(value, temp, 10, false);
                    for (char *p = temp; *p; p++) *str++ = *p;
                    break;
                }
                case 'x':
                case 'X': {
                    unsigned long value = long_flag ? va_arg(args, unsigned long) : va_arg(args, unsigned int);
                    utoa(value, temp, 16, *format == 'X');
                    for (char *p = temp; *p; p++) *str++ = *p;
                    break;
                }
                case 'o': {
                    unsigned long value = long_flag ? va_arg(args, unsigned long) : va_arg(args, unsigned int);
                    utoa(value, temp, 8, false);
                    for (char *p = temp; *p; p++) *str++ = *p;
                    break;
                }
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

int sprinti_me(char *str, const char *format, ...) {
    va_list args;
    va_start(args, format);
    char *s;
    int d, count = 0;
    char *temp;
    while (*format) {
        if (*format == '%') {
            format++;

            if (*format == 'h') {
                format++;
            }

            switch (*format) {
                case 'd':
                    d = va_arg(args, int);
                    count += int_to_str(d, temp);
                    while (*temp) {
                        *str++ = *temp++;
                    }
                    break;
                case 'u': {
                    unsigned value = va_arg(args, unsigned int);
                    utoa(value, temp, 10, false);
                    for (char *p = temp; *p; p++) *str++ = *p;
                    break;
                }
                case 'x':
                case 'X': {
                    unsigned long value = va_arg(args, unsigned int);
                    utoa(value, temp, 16, *format == 'X');
                    for (char *p = temp; *p; p++) *str++ = *p;
                    break;
                }
                case 'o': {
                    unsigned long value = va_arg(args, unsigned int);
                    utoa(value, temp, 8, false);
                    for (char *p = temp; *p; p++) *str++ = *p;
                    break;
                }
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

/* Helper to convert an unsigned int to string with base (10 for decimal, 16 for hex, etc.) */
static int utoa(unsigned long value, char *str, int base, bool uppercase) {
    const char *digits = uppercase ? "0123456789ABCDEF" : "0123456789abcdef";
    char temp[32];
    int i = 0, len = 0;

    if (value == 0) {
        str[0] = '0';
        str[1] = '\0';
        return 1;
    }

    while (value) {
        temp[i++] = digits[value % base];
        value /= base;
    }

    for (int j = i - 1; j >= 0; j--) {
        str[len++] = temp[j];
    }
    str[len] = '\0';
    return len;
}

/* Helper to convert signed int to string */
static int itoa(int value, char *str) {
    if (value < 0) {
        *str++ = '-';
        return 1 + utoa((unsigned)-value, str, 10, false);
    } else {
        return utoa((unsigned)value, str, 10, false);
    }
}

// ------------------------------------------------------------------------- END
