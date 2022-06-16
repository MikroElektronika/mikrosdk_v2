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
 * @file  conversions.h
 * @brief Conversion function prototypes.
 */

#ifndef _CONVERSIONS_H_
#define _CONVERSIONS_H_

#ifdef __cplusplus
extern "C"{
#endif

#include <stdint.h>
#include <stdbool.h>
#ifdef __GNUC__
#include <me_built_in.h>
#endif


/**
 * @brief Converts int8_t to hex value
 *
 * @param input in int8_t
 * @param output in hex
 */
void int8_to_hex(int8_t input, char * output);

/**
 * @brief Converts uint8_t to hex value
 *
 * @param input in uint8_t
 * @param output in hex
 */
void uint8_to_hex(uint8_t input, char * output);

/**
 * @brief Converts uint16_t to hex value
 *
 * @param input in uint16_t
 * @param output in hex
 */
void uint16_to_hex(uint16_t input, char * output);

/**
 * @brief Converts int16_t to hex value
 *
 * @param input in int16_t
 * @param output in hex
 */
void int16_to_hex(int16_t input, char * output);

/**
 * @brief Converts uint32_t to hex value
 *
 * @param input in uint32_t
 * @param output in hex
 */
void uint32_to_hex(uint32_t input, char * output);

/**
 * @brief Converts int32_t to hex value
 *
 * @param input in int32_t
 * @param output in hex
 */
void int32_to_hex(int32_t input, char * output);

#ifdef __CONVERSIONS_SET__
/**
 * @brief Converts uint64_t to hex value
 *
 * @param input in uint64_t
 * @param output in hex
 */
void uint64_to_hex(uint64_t input, char * output);

/**
 * @brief Converts int64_t to hex value
 *
 * @param input in int64_t
 * @param output in hex
 */
void int64_to_hex(int64_t input, char * output);
#endif

/**
 * @brief Converts uint8_t to string
 *
 * @param input in uint8_t
 * @param output in string
 */
void uint8_to_str( uint8_t input, char * output );

/**
 * @brief Converts uint8_t to string
 *                 with zeros
 *
 * @param input in uint8_t
 * @param output in string
 */
void uint8_to_str_with_zeros( uint8_t input, char * output );

/**
 * @brief Converts uint16_t to string
 *
 * @param input in uint16_t
 * @param output in string
 */
void uint16_to_str( uint16_t input, char * output );

/**
 * @brief Converts uint16_t to string
 *                 with zeros
 *
 * @param input in uint16_t
 * @param output in string
 */
void uint16_to_str_with_zeros(uint16_t input, char * output);

/**
 * @brief Converts int8_t to string
 *
 * @param input in int8_t
 * @param output in string
 */
void int8_to_str(int8_t input, char * output);

/**
 * @brief Converts int8_t to string
 *                 with zeros
 *
 * @param input in int8_t
 * @param output in string
 */
void int8_to_str_with_zeros(int8_t input, char * output);

/**
 * @brief Converts int16_t to string
 *
 * @param input in int16_t
 * @param output in string
 */
void int16_to_str(int16_t input, char * output);

/**
 * @brief Converts int16_t to string
 *                 with zeros
 *
 * @param input in int16_t
 * @param output in string
 */
void int16_to_str_with_zeros( int16_t input, char * output );

/**
 * @brief Converts uint32_t to string
 *
 * @param input in uint32_t
 * @param output in string
 */
void uint32_to_str( uint32_t input, char * output );

/**
 * @brief Converts uint32_t to string
 *                 with zeros
 *
 * @param input in uint32_t
 * @param output in string
 */
void uint32_to_str_with_zeros( uint32_t input, char * output );

/**
 * @brief Converts int32_t to string
 *
 * @param input in int32_t
 * @param output in string
 */
void int32_to_str( int32_t input, char * output );

/**
 * @brief Converts int32_t to string
 *                 with zeros
 *
 * @param input in int32_t
 * @param output in string
 */
void int32_to_str_with_zeros( int32_t input, char * output );

#ifdef __CONVERSIONS_SET__
/**
 * @brief Converts uint64_t to string
 *                 with zeros
 *
 * @param input in uint64_t
 * @param output in string
 */
void uint64_to_str_with_zeros(uint64_t input, char * output);

/**
 * @brief Converts int64_t to string
 *                 with zeros
 *
 * @param input in int64_t
 * @param output in string
 */
void int64_to_str_with_zeros( int64_t input, char * output );

/**
 * @brief Converts uint64_t to string
 *
 * @param input in uint64_t
 * @param output in string
 */
void uint64_to_str( uint64_t input, char * output );

/**
 * @brief Converts int64_t to string
 *
 * @param input in int64_t
 * @param output in string
 */
void int64_to_str( int64_t input, char * output );
#endif

/**
 * @brief Converts decimal number
 *                 to bcd value
 *
 * @param input
 * @param output in uint8_t
 */
uint8_t dec_to_bcd(uint8_t decnum);

/**
 * @brief Converts bcd value
 *                 to decimal number
 *
 * @param input
 * @param output in uint8_t
 */
uint8_t bcd_to_dec( uint8_t bcdnum );

/**
 * @brief Converts bcd value
 *                 to decimal number
 *
 * @param input
 * @param output in uint16_t
 */
uint16_t bcd_to_dec16(uint16_t bcdnum);

/**
 * @brief Converts bcd value
 *                 to decimal number
 *
 * @param input
 * @param output in uint16_t
 */
uint16_t dec_to_bcd16( uint16_t decnum );

/**
 * @brief Trims the trailing spaces from
 *        array given with *string
 *
 * @param string
 * @return char*
 */
char * r_trim( char * string );

/**
 * @brief Trims the leading spaces from
 *        array given with *string
 *
 * @param string
 * @return char*
 */
char * l_trim( char * string );

/**
 * @brief Converts floating point number into string
 *
 * @param f_num           - floating point number to be converted
 * @param string          - pointer to a string where converted number is stored
 * @return uint8_t : 0    - conversion ok (fnum is not +INF, -INF or NaN)
 *                   1    - if fnum is +INF
 *                   2    - if fnum is -INF
 *                   3    - if fnum is NaN
 */
uint8_t float_to_str( float f_num, char * string);

/**
 * @brief Converts string into uint8
 *
 * @param byte_in
 * @return uint8_in
 */
uint8_t str_to_uint8( char uint8_in[3] );

/**
 * @brief Converts string into int8
 *
 * @param int8_in
 * @return int8_t
 */
int8_t str_to_int8( char int8_in[4] );

/**
 * @brief Converts string into int16
 *
 * @param int16_in
 * @return int16_t
 */
int16_t str_to_int16( char int16_in[6] );

/**
 * @brief Converts string into uint16
 *
 * @param uint16_in
 * @return uint16_t
 */
uint16_t str_to_uint16( char uint16_in[5] );

/**
 * @brief Converts string into uint32
 *
 * @param uint32_in
 * @return uint32_t
 */
uint32_t str_to_uint32( char uint32_in[10] );

/**
 * @brief Converts string into int32
 *
 * @param int32_in
 * @return long
 */
int32_t str_to_int32( char int32_in[11] );

#ifdef __CONVERSIONS_SET__
/**
 * @brief Converts string into int64
 *
 * @param int64_in
 * @return int64_t
 */
int64_t str_to_int64( char int64_in[20] );

/**
 * @brief Converts string into uint64
 *
 * @param uint64_in
 * @return uint64_t
 */
uint64_t str_to_uint64( char uint64_in[20] );
#endif

/**
 * @brief Converts string into float
 *
 * @param data_str
 * @return float
 */
float str_to_float( char data_str[20] );

/**
 * @brief Converts hex into uint8
 *
 * @param hex_in
 * @return uint8_t
 */
uint8_t hex_to_uint8( char hex_in[2] );

/**
 * @brief Converts hex into uint16
 *
 * @param hex_in
 * @return uint16_t
 */
uint16_t hex_to_uint16( char hex_in[4] );

/**
 * @brief Converts hex into uint32
 *
 * @param hex_in
 * @return uint32_t
 */
uint32_t hex_to_uint32( char hex_in[8] );

#ifdef __CONVERSIONS_SET__
/**
 * @brief Converts hex into uint64
 *
 * @param hex_in
 * @return uint64_t
 */
uint64_t hex_to_uint64( char hex_in[16] );
#endif

/**
 * @brief Converts hex into int8
 *
 * @param hex_in
 * @return int8_t
 */
int8_t hex_to_int8( char hex_in[2] );

/**
 * @brief Converts hex into int16
 *
 * @param hex_in
 * @return int16_t
 */
int16_t hex_to_int16( char hex_in[4] );

/**
 * @brief Converts hex into int32
 *
 * @param hex_in
 * @return int32_t
 */
int32_t hex_to_int32( char hex_in[8] );

#ifdef __CONVERSIONS_SET__
/**
 * @brief Converts hex into int64
 *
 * @param hex_in
 * @return int64_t
 */
int64_t hex_to_int64( char hex_in[16] );

/**
 * @brief Converts long double to string
 *
 * @param dnum
 * @param str
 * @return uint8_t:  0    - conversion ok (fnum is not +INF, -INF or NaN)
 *                   1    - if fnum is +INF
 *                   2    - if fnum is -INF
 *                   3    - if fnum is NaN
 */
uint8_t long_double_to_str(long double dnum, char * str);
#endif

#ifdef __cplusplus
}
#endif

#endif  // _CONVERSIONS_H_
// ------------------------------------------------------------------------- END
