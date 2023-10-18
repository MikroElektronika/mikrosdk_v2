/*
    cstdio.h

 ------------------------------------------------------------------------------

  This file is part of mikroSDK.

  Copyright (c) 2023, MikroElektonika - www.mikroe.com

  All rights reserved.

----------------------------------------------------------------------------- */

/**
    \file   cstdio.h
    \brief  Standard input output functions.
    \{

- Version : **1.0.0**
- Date : **02.03.2023**
- Developer : **MikroE Team**

*/
// ----------------------------------------------------------------------------

#ifndef _CSTDIO_H_
#define _CSTDIO_H_

#ifdef __cplusplus
extern "C"{
#endif

#include <stdint.h>
#include <stdarg.h>

/**
 * @brief MikroE standard output breakpoint.
 * @details This routine is used by built-in terminal.
 * @param / None
 * @return None
 */
static inline void stdBuffFullBreak() {
    asm ("nop");
}

/**
 * @brief Writes a character to stdout.
 * @details The C library function int putchar(int char) writes a character (an unsigned char)
 *          specified by the argument char to stdout.
 * @param[in] character This is the character to be written.
 * @note @b character is passed as its int promotion.
 * @note MikroE standard output implementation.
 * @return This function returns the character written as an unsigned
 *         char cast to an int or EOF on error.
 */
int putchar_me( int character );

/**
 * @brief Writes a string to stdout.
 * @details The C library function int puts(const char *str) writes a string to stdout up to
 *          but not including the null character. A newline character is appended to the output.
 * @param[in] str This is the C string to be written.
 * @note MikroE standard output implementation.
 * @return None
 */
int puts_me( const char *str );

/**
 * @brief Writes a string to specified stream.
 * @details The C library function int fputs(const char *str, FILE *stream) writes a string
 *          to the specified stream up to but not including the null character.
 * @param[in] str This is the C string to be written.
 * @param[out] stream This is the pointer to a FILE object that identifies the stream
 *                    where the string is to be written.
 * @note MikroE standard output implementation.
 * @return None
 */
int fputs_me( const char *str, void (*stream)(char ch) );

/**
 * @brief MikroE standard output API.
 * @details This routine is used by NECTO Studio
 *          to send log output to the built-in terminal.
 * @param[in] ch String to be written.
 * @return None
 */
void debugStdOut( char ch );

/**
 * @brief Sends formatted output to stdout.
 * @param[in] format This is the string that contains the text to be written to stdout.
 *            It can optionally contain embedded format tags that are replaced by the values
 *            specified in subsequent additional arguments and formatted as requested.
 *            Format tags prototype is @b %[flags][width][.precision][length]specifier
 * @note Depending on the format string, the function may expect a sequence of additional arguments,
 *       each containing one value to be inserted instead of each @b %-tag specified in
 *       the format parameter (if any).
 *       There should be the same number of these arguments as the number of @b %-tags that expect a value.
 * @return If successful, the total number of characters written is returned.
 *         On failure, a negative number is returned.
 */
int printf_me( const char *format, ... );

/**
 * @brief Sends formatted output to a stream.
 * @param[out] stream This is the pointer to an object that identifies the stream.
 * @param[in] format This is the string that contains the text to be written to stdout.
 *            It can optionally contain embedded format tags that are replaced by the values
 *            specified in subsequent additional arguments and formatted as requested.
 *            Format tags prototype is @b %[flags][width][.precision][length]specifier
 * @note Depending on the format string, the function may expect a sequence of additional arguments,
 *       each containing one value to be inserted instead of each @b %-tag specified in
 *       the format parameter (if any).
 *       There should be the same number of these arguments as the number of @b %-tags that expect a value.
 * @return If successful, the total number of characters written is returned.
 *         On failure, a negative number is returned.
 */
int fprintf_me( void (*stream)(char ch), const char *format, ... );

/**
 * @brief Sends formatted output to a stream using an argument list passed to it.
 * @param[out] stream This is the pointer to an object that identifies the stream.
 * @param[in] format This is the string that contains the text to be written to stdout.
 *            It can optionally contain embedded format tags that are replaced by the values
 *            specified in subsequent additional arguments and formatted as requested.
 *            Format tags prototype is @b %[flags][width][.precision][length]specifier
 * @param[in] arg An object representing the variable arguments list.
 *            This should be initialized by the @ref va_start macro defined in @b <stdarg>
 * @note Depending on the format string, the function may expect a sequence of additional arguments,
 *       each containing one value to be inserted instead of each @b %-tag specified in
 *       the format parameter (if any).
 *       There should be the same number of these arguments as the number of @b %-tags that expect a value.
 * @return If successful, the total number of characters written is returned.
 *         On failure, a negative number is returned.
 */
int vfprintf_me( void (*stream)(char ch), const char *format, register va_list arg );

#ifdef __cplusplus
}
#endif

#endif  // _CSTDIO_H_

/// \}
// ----------------------------------------------------------------------------
/*
    cstdio.h

    Copyright (c) 2023, MikroElektronika - www.mikroe.com

Permission is hereby granted, free of charge, to any person obtaining a copy of
this software and associated documentation files (the "Software"), to deal in
the Software without restriction, including without limitation the rights to
use, copy, modify, merge, publish, distribute, sublicense, and/or sell copies
of the Software, and to permit persons to whom the Software is furnished to do
so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in all
copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
SOFTWARE.

*/
// ----------------------------------------------------------------------------
