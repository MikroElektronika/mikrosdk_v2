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

    char temp[32];
    int count = 0;

    while ( *format ) {
        if ( *format == '%' ) {
            format++;

            bool long_flag = false;
            bool left_align = false;
            bool zero_pad = false;
            bool plus_sign = false;
            bool space_sign = false;
            bool alt_form = false;

            int width = 0;
            int precision = -1;

            /* ---- FLAGS ---- */
            bool parsing = true;
            while ( parsing ) {
                switch ( *format ) {
                    case '-': left_align = true; format++; break;
                    case '0': zero_pad = true; format++; break;
                    case '+': plus_sign = true; format++; break;
                    case ' ': space_sign = true; format++; break;
                    case '#': alt_form = true; format++; break;
                    default: parsing = false; break;
                }
            }

            if ( left_align ) zero_pad = false;

            /* ---- LENGTH ---- */
            if ( *format == 'l' ) {
                long_flag = true;
                format++;
            }
            if ( *format == 'h' ) {
                format++;
            }

            /* ---- WIDTH ---- */
            while ( *format >= '0' && *format <= '9' ) {
                width = width * 10 + ( *format - '0' );
                format++;
            }

            /* ---- PRECISION ---- */
            if ( *format == '.' ) {
                format++;
                precision = 0;
                while ( *format >= '0' && *format <= '9' ) {
                    precision = precision * 10 + ( *format - '0' );
                    format++;
                }
            }

            switch ( *format ) {
            /* ---------- SIGNED INT ---------- */
            case 'd': {
                long value = long_flag ? va_arg( args, long ) : va_arg( args, int );
                bool negative = value < 0;
                if ( negative ) value = -value;

                ltoa_me( value, temp );

                int len = 0;
                for ( char *p = temp; *p; p++ ) len++;

                int sign_len = ( negative || plus_sign || space_sign ) ? 1 : 0;
                int total = len + sign_len;
                int pad = width > total ? width - total : 0;
                char padc = zero_pad ? '0' : ' ';

                if ( !left_align ) {
                    if ( padc == ' ' ) {
                        while ( pad-- ) {
                            *str++ = ' ';
                            count++;
                        }
                    }
                }

                if ( negative ) {
                    *str++ = '-';
                    count++;
                }
                else if ( plus_sign ) {
                    *str++ = '+';
                    count++;
                }
                else if ( space_sign ) {
                    *str++ = ' ';
                    count++;
                }

                if ( !left_align && padc == '0' ) {
                    while ( pad-- ) {
                        *str++ = '0';
                        count++;
                    }
                }

                for ( char *p = temp; *p; p++ ) {
                    *str++ = *p;
                    count++;
                }

                if ( left_align ) {
                    while ( pad-- ) {
                        *str++ = ' ';
                        count++;
                    }
                }
                break;
            }

            /* ---------- UNSIGNED / HEX / OCT ---------- */
            case 'u':
            case 'x':
            case 'X':
            case 'o': {
                unsigned long value =
                    long_flag ? va_arg( args, unsigned long ) : va_arg( args, unsigned int );

                int base = ( *format == 'o' ) ? 8 : ( *format == 'u' ) ? 10 : 16;
                bool upper = ( *format == 'X' );

                int len = utoa_me( value, temp, base, upper );

                int prefix_len = 0;
                if ( alt_form && value ) {
                    if ( *format == 'x' || *format == 'X' ) prefix_len = 2;
                    if ( *format == 'o' ) prefix_len = 1;
                }

                int total = len + prefix_len;
                int pad = width > total ? width - total : 0;
                char padc = zero_pad ? '0' : ' ';

                if ( !left_align && padc == ' ' ) {
                    while ( pad-- ) {
                        *str++ = ' ';
                        count++;
                    }
                }

                if ( prefix_len ) {
                    if ( *format == 'o' ) { *str++ = '0'; count++; }
                    else {
                        *str++ = '0';
                        *str++ = upper ? 'X' : 'x';
                        count += 2;
                    }
                }

                if ( !left_align && padc == '0' ) {
                    while ( pad-- ) {
                        *str++ = '0';
                        count++;
                    }
                }

                for ( int i = 0; i < len; i++ ) {
                    *str++ = temp[i];
                    count++;
                }

                if ( left_align ) {
                    while ( pad-- ) {
                        *str++ = ' ';
                        count++;
                    }
                }
                break;
            }

            /* ---------- FLOAT ---------- */
            case 'f': {
                double value = va_arg( args, double );
                if ( precision < 0 ) precision = 6;

                bool negative = value < 0;
                if ( negative ) value = -value;

                unsigned long scale = 1;
                for ( int i = 0; i < precision; i++ ) scale *= 10;

                unsigned long long scaled = ( unsigned long long )( value * scale + 0.5 );
                unsigned long ip = scaled / scale;
                unsigned long fp = scaled % scale;

                int ilen = utoa_me( ip, temp, 10, false );

                char frac[32];
                int flen = utoa_me( fp, frac, 10, false );

                int sign_len = ( negative || plus_sign || space_sign ) ? 1 : 0;
                int total = ilen + 1 + precision + sign_len;
                int pad = width > total ? width - total : 0;
                char padc = zero_pad ? '0' : ' ';

                if ( !left_align && padc == ' ' ) {
                    while ( pad-- ) {
                        *str++ = ' ';
                        count++;
                    }
                }

                if ( negative ) {
                    *str++ = '-';
                    count++;
                }
                else if ( plus_sign ) {
                    *str++ = '+';
                    count++;
                }
                else if ( space_sign ) {
                    *str++ = ' ';
                    count++;
                }

                if ( !left_align && padc == '0' ) {
                    while ( pad-- ) {
                        *str++ = '0';
                        count++;
                    }
                }

                for ( int i = 0; i < ilen; i++ ) {
                    *str++ = temp[i];
                    count++;
                }

                *str++ = '.';
                count++;

                for ( int i = flen; i < precision; i++ ) {
                    *str++ = '0';
                    count++;
                }
                for ( int i = 0; i < flen; i++ ) {
                    *str++ = frac[i];
                    count++;
                }

                if ( left_align ) {
                    while ( pad-- ) {
                        *str++ = ' ';
                        count++;
                    }
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
                char *s = va_arg( args, char* );
                while ( *s ) {
                    *str++ = *s++;
                    count++;
                }
                break;
            }

            case '%': {
                *str++ = '%'; count++;
                break;
            }

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
    va_end( args );
    return count;
}

int snprintf_me( char *str, size_t size, const char *format, ... ) {
    va_list args;
    va_start( args, format );

    char temp[32];
    int count = 0;
    size_t written = 0;

    while ( *format ) {
        if ( *format == '%' ) {
            format++;

            bool long_flag = false;
            bool left_align = false;
            bool zero_pad = false;
            bool plus_sign = false;
            bool space_sign = false;
            bool alt_form = false;

            int width = 0;
            int precision = -1;

            /* ---- FLAGS ---- */
            bool parsing = true;
            while ( parsing ) {
                switch ( *format ) {
                    case '-': left_align = true; format++; break;
                    case '0': zero_pad = true; format++; break;
                    case '+': plus_sign = true; format++; break;
                    case ' ': space_sign = true; format++; break;
                    case '#': alt_form = true; format++; break;
                    default: parsing = false; break;
                }
            }

            if ( left_align ) zero_pad = false;

            /* ---- LENGTH ---- */
            if ( *format == 'l' ) {
                long_flag = true;
                format++;
            }
            if ( *format == 'h' ) {
                format++;
            }

            /* ---- WIDTH ---- */
            while ( *format >= '0' && *format <= '9' ) {
                width = width * 10 + ( *format - '0' );
                format++;
            }

            /* ---- PRECISION ---- */
            if ( *format == '.' ) {
                format++;
                precision = 0;
                while ( *format >= '0' && *format <= '9' ) {
                    precision = precision * 10 + ( *format - '0' );
                    format++;
                }
            }

            switch ( *format ) {
            /* ---------- SIGNED INT ---------- */
            case 'd': {
                long value = long_flag ? va_arg( args, long ) : va_arg( args, int );
                bool negative = value < 0;
                if ( negative ) value = -value;

                ltoa_me( value, temp );

                int len = 0;
                for ( char *p = temp; *p; p++ ) len++;

                int sign_len = ( negative || plus_sign || space_sign ) ? 1 : 0;
                int total = len + sign_len;
                int pad = width > total ? width - total : 0;
                char padc = zero_pad ? '0' : ' ';

                if ( !left_align ) {
                    if ( padc == ' ' ) {
                        while ( pad-- ) {
                            if ( written + 1 < size ) {
                                *str++ = ' ';
                            }
                            written++;
                            count++;
                        }
                    }
                }

                if ( negative ) {
                    if ( written + 1 < size ) {
                        *str++ = '-';
                    }
                    written++;
                    count++;
                }
                else if ( plus_sign ) {
                    if ( written + 1 < size ) {
                        *str++ = '+';
                    }
                    written++;
                    count++;
                }
                else if ( space_sign ) {
                    if ( written + 1 < size ) {
                        *str++ = ' ';
                    }
                    written++;
                    count++;
                }

                if ( !left_align && padc == '0' ) {
                    while ( pad-- ) {
                        if ( written + 1 < size ) {
                            *str++ = '0';
                        }
                        written++;
                        count++;
                    }
                }

                for ( char *p = temp; *p; p++ ) {
                    if ( written + 1 < size ) {
                        *str++ = *p;
                    }
                    written++;
                    count++;
                }

                if ( left_align ) {
                    while ( pad-- ) {
                        if ( written + 1 < size ) {
                            *str++ = ' ';
                        }
                        written++;
                        count++;
                    }
                }
                break;
            }

            /* ---------- UNSIGNED / HEX / OCT ---------- */
            case 'u':
            case 'x':
            case 'X':
            case 'o': {
                unsigned long value =
                    long_flag ? va_arg( args, unsigned long ) : va_arg( args, unsigned int );

                int base = ( *format == 'o' ) ? 8 : ( *format == 'u' ) ? 10 : 16;
                bool upper = ( *format == 'X' );

                int len = utoa_me( value, temp, base, upper );

                int prefix_len = 0;
                if ( alt_form && value ) {
                    if ( *format == 'x' || *format == 'X' ) prefix_len = 2;
                    if ( *format == 'o' ) prefix_len = 1;
                }

                int total = len + prefix_len;
                int pad = width > total ? width - total : 0;
                char padc = zero_pad ? '0' : ' ';

                if ( !left_align && padc == ' ' ) {
                    while ( pad-- ) {
                        if ( written + 1 < size ) {
                            *str++ = ' ';
                        }
                        written++;
                        count++;
                    }
                }

                if ( prefix_len ) {
                    if ( *format == 'o' ) {
                        if ( written + 1 < size ) {
                            *str++ = '0';
                        }
                        written++;
                        count++;
                    } else {
                        if ( written + 1 < size ) {
                            *str++ = '0';
                        }
                        written++;
                        count++;

                        if ( written + 1 < size ) {
                            *str++ = upper ? 'X' : 'x';
                        }
                        written++;
                        count++;
                    }
                }

                if ( !left_align && padc == '0' ) {
                    while ( pad-- ) {
                        if( written + 1 < size ) {
                            *str++ = '0';
                        }
                        written++;
                        count++;
                    }
                }

                for ( int i = 0; i < len; i++ ) {
                    if ( written + 1 < size ) {
                        *str++ = temp[i];
                    }
                    written++;
                    count++;
                }

                if ( left_align ) {
                    while ( pad-- ) {
                        if ( written + 1 < size ) {
                            *str++ = ' ';
                        }
                        written++;
                        count++;
                    }
                }
                break;
            }

            /* ---------- FLOAT ---------- */
            case 'f': {
                double value = va_arg( args, double );
                if ( precision < 0 ) precision = 6;

                bool negative = value < 0;
                if ( negative ) value = -value;

                unsigned long scale = 1;
                for ( int i = 0; i < precision; i++ ) scale *= 10;

                unsigned long long scaled = ( unsigned long long )( value * scale + 0.5 );
                unsigned long ip = scaled / scale;
                unsigned long fp = scaled % scale;

                int ilen = utoa_me( ip, temp, 10, false );

                char frac[32];
                int flen = utoa_me( fp, frac, 10, false );

                int sign_len = ( negative || plus_sign || space_sign ) ? 1 : 0;
                int total = ilen + 1 + precision + sign_len;
                int pad = width > total ? width - total : 0;
                char padc = zero_pad ? '0' : ' ';

                if ( !left_align && padc == ' ' ) {
                    while ( pad-- ) {
                        if ( written + 1 < size ) {
                            *str++ = ' ';
                        }
                        written++;
                        count++;
                    }
                }

                if ( negative ) {
                    if( written + 1 < size ) {
                        *str++ = '-';
                    }
                    written++;
                    count++;
                }
                else if ( plus_sign ) {
                    if( written + 1 < size ) {
                        *str++ = '+';
                    }
                    written++;
                    count++;
                }
                else if ( space_sign ) {
                    if( written + 1 < size ) {
                        *str++ = ' ';
                    }
                    written++;
                    count++;
                }

                if ( !left_align && padc == '0' ) {
                    while ( pad-- ) {
                        if ( written + 1 < size ) {
                            *str++ = '0';
                        }
                        written++;
                        count++;
                    }
                }

                for ( int i = 0; i < ilen; i++ ) {
                    if ( written + 1 < size ) {
                        *str++ = temp[i];
                    }
                    written++;
                    count++;
                }

                if( written + 1 < size ) {
                    *str++ = '.';
                }
                written++;
                count++;

                for ( int i = flen; i < precision; i++ ) {
                    if ( written + 1 < size ) {
                        *str++ = '0';
                    }
                    written++;
                    count++;
                }
                for ( int i = 0; i < flen; i++ ) {
                    if ( written + 1 < size ) {
                        *str++ = frac[i];
                    }
                    written++;
                    count++;
                }

                if ( left_align ) {
                    while ( pad-- ) {
                        if ( written + 1 < size ) {
                            *str++ = ' ';
                        }
                        written++;
                        count++;
                    }
                }
                break;
            }

            case 'c': {
                char ch = ( char )va_arg( args, int );
                if ( written + 1 < size ) {
                    *str++ = ch;
                }
                written++;
                count++;
                break;
            }

            case 's': {
                char *s = va_arg( args, char* );
                while ( *s ) {
                    if ( written + 1 < size ) {
                        *str++ = *s++;
                    }
                    written++;
                    count++;
                }
                break;
            }

            case '%': {
                if ( written + 1 < size ) {
                    *str++ = '%';
                }
                written++;
                count++;
                break;
            }

            default:
                if ( written + 2 < size ) {
                    *str++ = '%';
                    *str++ = *format;
                }
                written += 2;
                count += 2;
                break;
            }
        } else {
            if ( written + 1 < size ) {
                *str++ = *format;
            }
            written++;
            count++;
        }
        format++;
    }

    if ( size > 0 ) {
        if ( written >= size )
            str[size - 1] = '\0';
        else
            *str = '\0';
    }

    va_end( args );
    return count;
}

int sprintl_me( char *str, const char *format, ... ) {
    va_list args;
    va_start( args, format );

    char temp[20];
    int count = 0;

    while ( *format ) {
        if ( *format == '%' ) {
            format++;

            bool long_flag = false;
            bool left_align = false;
            bool zero_pad = false;
            bool plus_sign = false;
            bool space_sign = false;
            bool alt_form = false;

            int width = 0;
            int precision = -1;

            /* ---- FLAGS ---- */
            bool parsing = true;
            while ( parsing ) {
                switch ( *format ) {
                    case '-': left_align = true; format++; break;
                    case '0': zero_pad = true; format++; break;
                    case '+': plus_sign = true; format++; break;
                    case ' ': space_sign = true; format++; break;
                    case '#': alt_form = true; format++; break;
                    default: parsing = false; break;
                }
            }

            if ( left_align ) zero_pad = false;

            if ( *format == 'l' ) {
                long_flag = true;
                format++;
            }

            if ( *format == 'h' ) {
                format++;
            }

            /* ---- WIDTH ---- */
            while ( *format >= '0' && *format <= '9' ) {
                width = width * 10 + ( *format - '0' );
                format++;
            }

            switch ( *format ) {
                case 'd':{
                    long value = long_flag ? va_arg( args, long ) : va_arg( args, int );
                    bool negative = value < 0;
                    if ( negative ) value = -value;

                    ltoa_me( value, temp );

                    int len = 0;
                    for ( char *p = temp; *p; p++ ) len++;

                    int sign_len = ( negative || plus_sign || space_sign ) ? 1 : 0;
                    int total = len + sign_len;
                    int pad = width > total ? width - total : 0;
                    char padc = zero_pad ? '0' : ' ';

                    if ( !left_align ) {
                        if ( padc == ' ' ) {
                            while ( pad-- ) {
                                *str++ = ' ';
                                count++;
                            }
                        }
                    }

                    if ( negative ) {
                        *str++ = '-';
                        count++;
                    }
                    else if ( plus_sign ) {
                        *str++ = '+';
                        count++;
                    }
                    else if ( space_sign ) {
                        *str++ = ' ';
                        count++;
                    }

                    if ( !left_align && padc == '0' ) {
                        while ( pad-- ) {
                            *str++ = '0';
                            count++;
                        }
                    }

                    for ( char *p = temp; *p; p++ ) {
                        *str++ = *p;
                        count++;
                    }

                    if ( left_align ) {
                        while ( pad-- ) {
                            *str++ = ' ';
                            count++;
                        }
                    }
                    break;
                }
                case 'u':
                case 'x':
                case 'X':
                case 'o': {
                    unsigned long value =
                        long_flag ? va_arg( args, unsigned long ) : va_arg( args, unsigned int );

                    int base = ( *format == 'o' ) ? 8 : ( *format == 'u' ) ? 10 : 16;
                    bool upper = ( *format == 'X' );

                    int len = utoa_me( value, temp, base, upper );

                    int prefix_len = 0;
                    if ( alt_form && value ) {
                        if ( *format == 'x' || *format == 'X' ) prefix_len = 2;
                        if ( *format == 'o' ) prefix_len = 1;
                    }

                    int total = len + prefix_len;
                    int pad = width > total ? width - total : 0;
                    char padc = zero_pad ? '0' : ' ';

                    if ( !left_align && padc == ' ' ) {
                        while ( pad-- ) {
                            *str++ = ' ';
                            count++;
                        }
                    }

                    if ( prefix_len ) {
                        if ( *format == 'o' ) { *str++ = '0'; count++; }
                        else {
                            *str++ = '0';
                            *str++ = upper ? 'X' : 'x';
                            count += 2;
                        }
                    }

                    if ( !left_align && padc == '0' ) {
                        while ( pad-- ) {
                            *str++ = '0';
                            count++;
                        }
                    }

                    for ( int i = 0; i < len; i++ ) {
                        *str++ = temp[i];
                        count++;
                    }

                    if ( left_align ) {
                        while ( pad-- ) {
                            *str++ = ' ';
                            count++;
                        }
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
                    char *s = va_arg( args, char* );
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

    int count = 0;
    char temp[20];

    while ( *format ) {
        if ( *format == '%' ) {
            format++;

            bool long_flag = false;
            bool left_align = false;
            bool zero_pad = false;
            bool plus_sign = false;
            bool space_sign = false;
            bool alt_form = false;

            int width = 0;
            int precision = -1;

            /* ---- FLAGS ---- */
            bool parsing = true;
            while ( parsing ) {
                switch ( *format ) {
                    case '-': left_align = true; format++; break;
                    case '0': zero_pad = true; format++; break;
                    case '+': plus_sign = true; format++; break;
                    case ' ': space_sign = true; format++; break;
                    case '#': alt_form = true; format++; break;
                    default: parsing = false; break;
                }
            }

            if ( left_align ) zero_pad = false;

            if ( *format == 'h' ) {
                format++;
            }

            /* ---- WIDTH ---- */
            while ( *format >= '0' && *format <= '9' ) {
                width = width * 10 + ( *format - '0' );
                format++;
            }

            switch ( *format ) {
                case 'd': {
                    int value = va_arg( args, int );
                    itoa_me( value, temp );
                    int len = 0;
                    for ( char *p = temp; *p; p++ ) len++;
                    for ( int i = len; i < width; i++ ) {
                        *str++ = ' ';
                        count++;
                    }
                    for ( char *p = temp; *p; p++ ) {
                        *str++ = *p;
                        count++;
                    }
                    break;
                }
                case 'u': {
                    unsigned value = va_arg( args, unsigned int );
                    utoa_me( value, temp, 10, false );
                    int len = 0;
                    for ( char *p = temp; *p; p++ ) len++;
                    for ( int i = len; i < width; i++ ) {
                        *str++ = ' ';
                        count++;
                    }
                    for ( char *p = temp; *p; p++ ) {
                        *str++ = *p;
                        count++;
                    }
                    break;
                }
                case 'x':
                case 'X': {
                    unsigned value = va_arg( args, unsigned int );
                    utoa_me( value, temp, 16, *format == 'X' );
                    int len = 0;
                    for ( char *p = temp; *p; p++ ) len++;
                    for ( int i = len; i < width; i++ ) {
                        *str++ = ' ';
                        count++;
                    }
                    for ( char *p = temp; *p; p++ ) {
                        *str++ = *p;
                        count++;
                    }
                    break;
                }
                case 'o': {
                    unsigned value = va_arg( args, unsigned int );
                    utoa_me( value, temp, 8, false );
                    int len = 0;
                    for ( char *p = temp; *p; p++ ) len++;
                    for ( int i = len; i < width; i++ ) {
                        *str++ = ' ';
                        count++;
                    }
                    for ( char *p = temp; *p; p++ ) {
                        *str++ = *p;
                        count++;
                    }
                    break;
                }
                case 'c': {
                    char ch = ( char )va_arg( args, int );
                    for ( int i = 1; i < width; i++ ) {
                        *str++ = ' ';
                        count++;
                    }
                    *str++ = ch;
                    count++;
                    break;
                }
                case 's': {
                    char *s = va_arg( args, char * );
                    int len = 0;
                    for ( char *p = s; *p; p++ ) len++;
                    for ( int i = len; i < width; i++ ) {
                        *str++ = ' ';
                        count++;
                    }
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
