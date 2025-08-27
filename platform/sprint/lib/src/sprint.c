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

// ------------------------------------------------------------------- INCLUDES

#include "conversions.h"
#include "sprint.h"
#include <string.h>

#include <stdarg.h>
#include <stdbool.h>

#ifdef __MIKROC__
#include "built_in.h"
#endif

// ------------------------------------------------------------- PRIVATE MACROS

#ifndef va_end
#define va_end(ap) ;
#endif

// ---------------------------------------------- PRIVATE FUNCTION DECLARATIONS

/**
 * @brief Converts an unsigned long integer to a string with the specified base.
 *
 * @param value The unsigned long integer to convert.
 * @param str The buffer to store the resulting string.
 * @param base The base for conversion (e.g., 10 for decimal, 16 for hex).
 * @param uppercase Whether to use uppercase for hex digits (true/false).
 *
 * @return The number of characters written to the string (excluding null terminator).
 */
static int utoa_me( unsigned long value, char *str, int base, bool uppercase );

/**
 * @brief Converts a signed integer to a string.
 *
 * @param value The signed integer to convert.
 * @param str The buffer to store the resulting string.
 *
 * @return The number of characters written to the string (excluding null terminator).
 */
static int itoa_me( int value, char *str );

/**
 * @brief Converts a signed long integer to a string.
 *
 * @param value The signed long integer to convert.
 * @param str The buffer to store the resulting string.
 *
 * @return The number of characters written to the string (excluding null terminator).
 */
static int ltoa_me( long value, char *str );

// ------------------------------------------------ PUBLIC FUNCTION DEFINITIONS

int sprintf_me( char *str, const char *format, ... ) {
    va_list args;
    va_start( args, format );

    char *orig = str;
    char temp[32];
    int count = 0;
    int precision = -1; // Default precision

    while ( *format ) {
        if ( *format == '%' ) {
            format++;
            bool long_flag = false;

            if ( *format == 'l' ) {
                long_flag = true;
                format++;
            }

            if ( *format == 'h' ) {
                format++;
            }

            // Parse optional precision (e.g., "%.2f")
            if ( *format == '.' ) {
                format++;
                precision = 0;
                while ( *format >= '0' && *format <= '9' ) {
                    precision = precision * 10 + ( *format - '0' );
                    format++;
                }
            }

            switch ( *format ) {
                case 'd': {
                    if ( long_flag ) {
                        long value = va_arg( args, long );
                        ltoa_me( value, temp );
                    } else {
                        int value = va_arg( args, int );
                        itoa_me( value, temp );
                    }
                    for ( char *p = temp; *p; p++ ) {
                        *str++ = *p;
                        count++;
                    }
                    break;
                }
                case 'f': {
                    double value = va_arg( args, double );

                    if ( precision < 0 ) precision = 6;

                    // Handle negative numbers
                    if ( value < 0 ) {
                        *str++ = '-';
                        value = -value;
                    }

                    // Scale factor for precision
                    unsigned long scale = 1;
                    for ( int i = 0; i < precision; i++ ) scale *= 10;

                    // Multiply first, then round, then split
                    unsigned long long scaled = ( unsigned long long )( value * scale + 0.5 );
                    unsigned long integer_part = scaled / scale;
                    unsigned long frac_part = scaled % scale;

                    // Integer part
                    utoa_me( integer_part, temp, 10, false );
                    for ( char *p = temp; *p; p++ ) {
                        *str++ = *p;
                        count++;
                    }

                    *str++ = '.';

                    // Fractional part: pad with leading zeros
                    char frac_str[32];
                    int frac_len = utoa_me( frac_part, frac_str, 10, false );
                    for ( int i = frac_len; i < precision; ++i ) {
                        *str++ = '0';
                    }
                    for ( int i = 0; i < frac_len; ++i ) {
                        *str++ = frac_str[i];
                    }

                    break;
                }
                case 'u': {
                    unsigned long value;
                    if ( long_flag ) {
                        value = va_arg( args, unsigned long );
                    } else {
                        value = va_arg( args, unsigned int );
                    }
                    utoa_me( value, temp, 10, false );
                    for ( char *p = temp; *p; p++ ) {
                        *str++ = *p;
                        count++;
                    }
                    break;
                }
                case 'x':
                case 'X': {
                    unsigned long value;
                    if ( long_flag ) {
                        value = va_arg( args, unsigned long );
                    } else {
                        value = va_arg( args, unsigned int );
                    }
                    utoa_me( value, temp, 16, *format == 'X' );
                    for ( char *p = temp; *p; p++ ) {
                        *str++ = *p;
                        count++;
                    }
                    break;
                }
                case 'o': {
                    unsigned long value;
                    if ( long_flag ) {
                        value = va_arg( args, unsigned long );
                    } else {
                        value = va_arg( args, unsigned int );
                    }
                    utoa_me( value, temp, 8, false );
                    for ( char *p = temp; *p; p++ ) {
                        *str++ = *p;
                        count++;
                    }
                    break;
                }
                case 'c': {
                    char ch = ( char )va_arg( args, int );
                    *str++ = ch;
                    count++;
                    break;
                }
                case 's': {
                    char *s = va_arg( args, char * );
                    while ( *s ) {
                        *str++ = *s++;
                        count++;
                    }
                    break;
                }
                case '%': {
                    *str++ = '%';
                    count++;
                    break;
                }
                default: {
                    // Unsupported format; copy as-is
                    *str++ = '%';
                    *str++ = *format;
                    count++;
                    break;
                }
            }
        } else {
            *str++ = *format;
            count++;
        }
        format++;
    }

    *str = '\0';
    va_end( args );
    return str - orig;
}

int sprintl_me( char *str, const char *format, ... ) {
    va_list args;
    va_start( args, format );
    char *s;
    int d;
    long ld;
    int count = 0;
    char temp[20];

    while ( *format ) {
        if ( *format == '%' ) {
            format++;
            bool long_flag = false;

            if ( *format == 'l' ) {
                long_flag = true;
                format++;
            }

            if ( *format == 'h' ) {
                format++;
            }

            switch ( *format ) {
                case 'd':{
                    if ( long_flag ) {
                        long value = va_arg( args, long );
                        ltoa_me( value, temp );
                    } else {
                        int value = va_arg( args, int );
                        itoa_me( value, temp );
                    }
                    for ( char *p = temp; *p; p++ ) {
                        *str++ = *p;
                        count++;
                    }
                    break;
                }
                case 'u': {
                    unsigned long value = long_flag ? va_arg( args, unsigned long ) : va_arg( args, unsigned int );
                    utoa_me( value, temp, 10, false );
                    for ( char *p = temp; *p; p++ ) {
                        *str++ = *p;
                        count++;
                    }
                    break;
                }
                case 'x':
                case 'X': {
                    unsigned long value = long_flag ? va_arg( args, unsigned long ) : va_arg( args, unsigned int );
                    utoa_me( value, temp, 16, *format == 'X' );
                    for ( char *p = temp; *p; p++ ) {
                        *str++ = *p;
                        count++;
                    }
                    break;
                }
                case 'o': {
                    unsigned long value = long_flag ? va_arg( args, unsigned long ) : va_arg( args, unsigned int );
                    utoa_me( value, temp, 8, false );
                    for ( char *p = temp; *p; p++ ) {
                        *str++ = *p;
                        count++;
                    }
                    break;
                }
                case 'c': {
                    *str++ = ( char )va_arg( args, int );
                    count++;
                    break;
                }
                case 's': {
                    s = va_arg( args, char * );
                    while ( *s ) {
                        *str++ = *s++;
                        count++;
                    }
                    break;
                }
                default: {
                    *str++ = '%';
                    *str++ = *format;
                    count += 2;
                    break;
                }
            }
        } else {
            *str++ = *format;
            count++;
        }
        format++;
    }

    *str = '\0';
    va_end( args );
    return count;
}

int sprinti_me( char *str, const char *format, ... ) {
    va_list args;
    va_start( args, format );
    char *s;
    int d, count = 0;
    char temp[20];
    while ( *format ) {
        if ( *format == '%' ) {
            format++;

            if ( *format == 'h' ) {
                format++;
            }

            switch ( *format ) {
                case 'd': {
                    int value = va_arg( args, int );
                    itoa_me( value, temp );
                    for ( char *p = temp; *p; p++ ) {
                        *str++ = *p;
                        count++;
                    }
                    break;
                }
                case 'u': {
                    unsigned value = va_arg( args, unsigned int );
                    utoa_me( value, temp, 10, false );
                    for ( char *p = temp; *p; p++ ) {
                        *str++ = *p;
                        count++;
                    }
                    break;
                }
                case 'x':
                case 'X': {
                    unsigned long value = va_arg( args, unsigned int );
                    utoa_me( value, temp, 16, *format == 'X' );
                    for ( char *p = temp; *p; p++ ) {
                        *str++ = *p;
                        count++;
                    }
                    break;
                }
                case 'o': {
                    unsigned long value = va_arg( args, unsigned int );
                    utoa_me( value, temp, 8, false );
                    for ( char *p = temp; *p; p++ ) {
                        *str++ = *p;
                        count++;
                    }
                    break;
                }
                case 'c': {
                    *str++ = ( char )va_arg( args, int );
                    count++;
                    break;
                }
                case 's': {
                    s = va_arg( args, char * );
                    while ( *s ) {
                        *str++ = *s++;
                        count++;
                    }
                    break;
                }
                default: {
                    *str++ = '%';
                    *str++ = *format;
                    count += 2;
                    break;
                }
            }
        } else {
            *str++ = *format;
            count++;
        }
        format++;
    }
    *str = '\0';
    va_end( args );

    return count;
}

// ----------------------------------------------- PRIVATE FUNCTION DEFINITIONS

/* Convert unsigned long to string with base (supports base 10, 16, etc.) */
static int utoa_me( unsigned long value, char *str, int base, bool uppercase ) {
    const char *digits = uppercase ? "0123456789ABCDEF" : "0123456789abcdef";
    char temp[32]; // Enough for 64-bit numbers
    int i = 0, len = 0;

    if ( value == 0 ) {
        str[0] = '0';
        str[1] = '\0';
        return 1;
    }

    while ( value > 0 ) {
        temp[i++] = digits[value % base];
        value /= base;
    }

    // Reverse the string into the output buffer
    for ( int j = i - 1; j >= 0; j-- ) {
        str[len++] = temp[j];
    }

    str[len] = '\0';
    return len;
}

/* Convert signed integer to string (base 10 only) */
static int itoa_me( int value, char *str ) {
    unsigned int abs_value = ( value < 0 ) ? -( unsigned int )value : ( unsigned int )value;
    int len = 0;

    if ( value < 0 ) {
        str[len++] = '-';
    }
    char *new_str = str+len;

    len += utoa_me( abs_value, new_str, 10, false );
    return len;
}

/* Convert long to string (base 10 only) */
static int ltoa_me( long value, char *str ) {
    unsigned long abs_value = ( value < 0 ) ? -( unsigned long )value : ( unsigned long )value;
    int len = 0;

    if ( value < 0 ) {
        str[len++] = '-';
    }

    char *new_str = str+len;
    len += utoa_me( abs_value, new_str, 10, false );
    return len;
}

// ------------------------------------------------------------------------- END
