/****************************************************************************
**
** Copyright (C) 2023 MikroElektronika d.o.o.
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
 * @file  conversions.c
 * @brief Conversion function definitions.
 */

#include "conversions.h"
#include <string.h>

#ifdef __MIKROC__
#include "built_in.h"
#endif
// ------------------------------------------------------------- PRIVATE MACROS

#define F32_ZERO        0x00000000
#define F32_NAN         0xFFFFFFFF
#ifdef __CONVERSIONS_CHIPS_32BIT__
#define F32_PLUS_INF    0x7F800000
#elif defined(__CONVERSIONS_CHIPS_PIC__)
#define F32_PLUS_INF    0xFF000000
#endif
#define F32_MINUS_INF   0xFF800000
#define F32_NDIG        7   // Maximum number of decimal digits of the mantissa
#define F32_BO          3   // Byte ordering: 0 = Big endian; 3 = Little endian

#define F64_ZERO        0x0000000000000000
#define F64_NAN         0xFFFFFFFFFFFFFFFF
#define F64_PLUS_INF    0x7FF0000000000000
#define F64_MINUS_INF   0xFFF0000000000000
#define F64_NDIG        16  // Maximum number of decimal digits of the mantissa
#define F64_BO          7   // Byte ordering: 0 = Big endian; 7 = Little endian


// -------------------------------------------------------------- PRIVATE TYPES

union f32_ul
{
    float fl;
    uint32_t ul;
    uint8_t uc[4];
};

#ifdef __CONVERSIONS_SET__
union f64_ul
{
    long double ld;
    uint64_t ull;
    uint8_t uc[8];
    struct
    {
        uint64_t fraction : 52;
        unsigned exponent : 11;
        unsigned sign : 1;
    };
};
#endif

// ------------------------------------------------------------------ CONSTANTS

static const char digits[] =
{
    '0','1','2','3','4','5','6','7','8','9','A','B','C','D','E','F'
};

// ------------------------------------------------------------------ VARIABLES


// ---------------------------------------------- PRIVATE FUNCTION DECLARATIONS

/**
 * @brief copies input for editing and checks for garbage input
 *
 * @param byte_in
 * @param buf_str2
 * @param counter
 * @return uint64_t
 */
#ifdef __CONVERSIONS_SUBSET__
static uint32_t forward_input( char * byte_in, char * buf_str2, uint8_t * counter );
#else
static uint64_t forward_input( char * byte_in, char * buf_str2, uint8_t * counter );
#endif

/**
 * @brief checks input for numbers and letters
 *
 * @param byte_in
 * @param result
 * @return char
 */
static char adjust_hex( char * byte_in, char * result );

/**
 * @brief checks input for numbers and letters
 *
 * @param hex_in
 * @return char
 */
static char check_input( char * hex_in );

// ------------------------------------------------ PUBLIC FUNCTION DEFINITIONS

void uint8_to_hex( uint8_t input, char * output )
{
  output[0] = digits[input >> 4];
  output[1] = digits[input & 0xF];
  output[2] = 0;
}

void int8_to_hex( int8_t input, char * output )
{
  output[0] = digits[( char )input >> 4];
  output[1] = digits[input & 0xF];
  output[2] = 0;
}

void uint16_to_hex( uint16_t input, char * output )
{
  output[0] = digits[Hi( input ) >> 4];
  output[1] = digits[Hi( input ) & 0xF];
  output[2] = digits[Lo( input ) >> 4];
  output[3] = digits[Lo( input ) & 0xF];
  output[4] = 0;
}

void int16_to_hex( int16_t input, char * output )
{
  output[0] = digits[Hi( input ) >> 4];
  output[1] = digits[Hi( input ) & 0xF];
  output[2] = digits[Lo( input ) >> 4];
  output[3] = digits[Lo( input ) & 0xF];
  output[4] = 0;
}

void uint32_to_hex( uint32_t input, char * output )
{
  uint16_t input_half;

  input_half = HiWord( input );
  output[0]  = digits[Hi( input_half ) >> 4];
  output[1]  = digits[Hi( input_half ) & 0xF];
  output[2]  = digits[Lo( input_half ) >> 4];
  output[3]  = digits[Lo( input_half ) & 0xF];
  input_half = LoWord( input );
  output[4]  = digits[Hi( input_half ) >> 4];
  output[5]  = digits[Hi( input_half ) & 0xF];
  output[6]  = digits[Lo( input_half ) >> 4];
  output[7]  = digits[Lo( input_half ) & 0xF];
  output[8]  = 0;
}

void int32_to_hex( int32_t input, char * output )
{
  uint16_t input_half;

  input_half = HiWord( input );
  output[0]  = digits[Hi( input_half ) >> 4];
  output[1]  = digits[Hi( input_half ) & 0xF];
  output[2]  = digits[Lo( input_half ) >> 4];
  output[3]  = digits[Lo( input_half ) & 0xF];
  input_half = LoWord( input );
  output[4]  = digits[Hi( input_half ) >> 4];
  output[5]  = digits[Hi( input_half ) & 0xF];
  output[6]  = digits[Lo( input_half ) >> 4];
  output[7]  = digits[Lo( input_half ) & 0xF];
  output[8]  = 0;
}

#ifdef __CONVERSIONS_SET__
void uint64_to_hex( uint64_t input, char * output )
{
  uint32_t half;
  half = ( uint64_t )input >> 32;
  uint32_to_hex( half, output );
  half = input;
  uint32_to_hex( half, output + 8 );
}

void int64_to_hex( int64_t input, char * output )
{
  signed long half;
  half = input >> 32;
  uint32_to_hex( half,output );
  half = input;
  uint32_to_hex( half,output + 8 );
}
#endif

void uint8_to_str( uint8_t input, char * output )
{
    uint8_t digit_pos;

    for ( digit_pos = 0; digit_pos < 3; digit_pos++ )
    {
        output[digit_pos] = ' ';
    }

    output[digit_pos--] = 0;

    while ( 1 )
    {
        output[digit_pos] = ( input % 10u ) + 48;
        input = input / 10u;
        if ( input == 0 )
        {
            break;
        }

        digit_pos--;
    }
}

void uint8_to_str_with_zeros( uint8_t input, char * output )
{
    uint8_t len;

    for ( len = 0; len < 3; len++ )
    {
        output[len] = '0';
    }

    output[len--] = 0;

    while ( input != 0 )
    {
        output[len--] = ( uint8_t )( input % 10 ) + 48;
        input = input / 10;
    }
}

void uint16_to_str( uint16_t input, char * output )
{
    uint8_t len;

    //--- the result is right justified - so we go from bottom to top
    for ( len = 0 ; len < 5 ; len++ )
    {
        output[len] = ' ';
    }

    output[len--] = 0;

    while ( 1 )
    {
        output[len] = input % 10u + 48;
        input = input / 10u;

        if ( input == 0 )
        {
            break;
        }

        len--;
    }
}

void uint16_to_str_with_zeros( uint16_t input, char * output )
{
    uint16_t len;

    for ( len = 0; len < 5; len++ )
    {
        output[len] = '0';
    }

    output[len--] = 0;

    while ( input != 0 )
    {
        output[len--] = ( uint16_t )( input % 10 ) + 48;
        input = input / 10;
    }
}


void int8_to_str( int8_t input, char * output )
{
    bool negative;
    uint16_t i;
    uint16_t tmp;

    negative = false;
    tmp = ( int16_t )input;

    if ( input < 0 )
    {
        negative = true;
        tmp = ( 0 - input );
    }

    uint8_to_str( tmp, output );

    i = 4;

    while ( i > 0 )
    {
        output[i] = output[i - 1];
        i--;
    }

    output[0] = ' ';

    if ( negative )
    {
        i = 0;

        while ( output[ i ] == ' ' )
        {
            i++;
        }

        i--;
        output[ i ] = '-';
    }
}

void int8_to_str_with_zeros( int8_t input, char * output )
{
    bool negative;
    uint8_t len;
    uint16_t tmp;

    for ( len = 0; len < 4; len++ )
    {
        output[len] = '0';
    }

    output[len] = 0;

    if ( input == 0 )
    {
        return;
    }

    negative = false;

    if ( input < 0 )
    {
        negative = true;
        tmp = ( uint16_t )( 0 - input );
    }
    else
    {
        tmp = ( uint16_t )input;
    }

    len = 3;
    while ( tmp != 0 )
    {
        output[len--] = ( uint16_t )( tmp % 10 ) + 48;
        tmp = tmp / 10;
    }

    if ( negative )
    {
        output[0] = '-';
    }
}

void int16_to_str( int16_t input, char * output )
{
    bool negative;
    uint16_t i;
    uint16_t tmp;

    negative = false;
    tmp = ( uint16_t )input;

    if ( input < 0 )
    {
        negative = true;
        tmp = ( uint16_t )( 0 - input );
    }

    uint16_to_str( tmp, output );
    i = 6;

    while ( i > 0 )
    {
        output[i] = output[i - 1];
        i--;
    }

    output[0] = ' ';

    if ( negative )
    {
        i = 0;

        while ( output[ i ] == ' ' )
        {
            i++;
        }

        i--;
        output[ i ] = '-';
    }
}

void int16_to_str_with_zeros( int16_t input, char * output )
{
    bool negative;
    uint8_t len;
    uint16_t tmp;

    for ( len = 0; len < 6; len++ )
    {
        output[len] = '0';
    }

    output[len] = 0;

    if ( input == 0 )
    {
        return;
    }

    negative = 0;

    if ( input < 0 )
    {
        negative = 1;
        tmp = ( uint16_t )( 0 - input );
    }
    else
    {
        tmp = ( uint16_t )input;
    }

    len = 5;

    while ( tmp != 0 )
    {
        output[len--] = ( uint16_t )( tmp % 10 ) + 48;
        tmp = tmp / 10;
    }

    if ( negative )
    {
        output[0] = '-';
    }
}

void uint32_to_str( uint32_t input, char * output )
{
    uint16_t len;
    //--- the result is right justified - so we go from bottom to top
    for ( len = 0; len < 10; len++ )
    {
        output[len] = ' ';
    }

    output[len--] = 0;

    while ( 1 )
    {
        output[len] = input % 10u + 48;
        input = input / 10u;

        if ( input == 0 )
        {
            break;
        }

        len--;
    }
}

void uint32_to_str_with_zeros( uint32_t input, char * output )
{
    uint16_t len;
    //--- the result is right justified - so we go from bottom to top
    for ( len = 0; len < 10; len++ )
    {
        output[len] = '0';
    }

    output[len--] = 0;

    while ( input != 0 )
    {
        output[len--] = ( uint16_t )( input % 10 ) + 48;
        input = input / 10;
    }
}

void int32_to_str( int32_t input, char * output )
{
    bool negative;
    uint16_t i;
    uint32_t tmp;

    negative = false;
    tmp = ( uint32_t )input;

    if ( input < 0 )
    {
        negative = true;
        tmp = ( uint32_t )( 0 - input );
    }

    uint32_to_str( tmp, output );
    i = 11;

    while ( i > 0 )
    {
        output[i] = output[i - 1];
        i--;
    }

    output[0] = ' ';
    if ( negative )
    {
        i = 0;

        while ( output[ i ] == ' ' )
        {
            i++;
        }

        i--;
        output[ i ] = '-';
    }
}

void int32_to_str_with_zeros( int32_t input, char * output )
{
    bool negative;
    uint8_t len;
    uint32_t tmp;

    for ( len = 0; len < 11; len++ )
    {
        output[len] = '0';
    }

    output[len] = 0;

    if ( input == 0 )
    {
        return;
    }

    negative = false;

    if ( input < 0 )
    {
        negative = true;
        tmp = ( uint32_t )( 0 - input );
    }
    else
    {
        tmp = ( uint32_t )input;
    }

    len = 10;
    while ( tmp != 0 )
    {
        output[len--] = ( uint32_t )( tmp % 10 ) + 48;
        tmp = tmp / 10;
    }

    if ( negative )
    {
        output[0] = '-';
    }
}

#ifdef __CONVERSIONS_SET__
void uint64_to_str_with_zeros( uint64_t input, char * output )
{
    uint16_t len;
    //--- the result is right justified - so we go from bottom to top
    for ( len = 0; len < 20; len++ )
    {
        output[len] = '0';
    }

    output[len--] = 0;

    while ( input != 0 )
    {
        output[len--] = ( uint16_t )( input % 10 ) + 48;
        input = input / 10;
    }
}

void int64_to_str_with_zeros( int64_t input, char * output )
{
    bool negative;
    uint16_t len;
    uint64_t tmp;

    for ( len = 0; len < 20; len++ )
    {
        output[len] = '0';
    }

    output[len] = 0;

    negative = false;

    if ( input == 0l )
    {
        return;
    }

    tmp = ( uint64_t )input;
    if ( input < 0 )
    {
        negative = true;
        tmp = ( uint64_t )( 0 - input );
    }

    len = 19;

    while ( tmp != 0 )
    {
        output[len--] = ( uint64_t )( tmp % 10 ) + 48;
        tmp = tmp / 10;
    }

    if ( negative )
    {
        output[0] = '-';
    }
}

void uint64_to_str( uint64_t input, char * output )
{
    uint16_t len;
    //--- the result is right justified - so we go from bottom to top
    for ( len = 0; len < 20; len++ )
    {
        output[len] = ' ';
    }

    output[len--] = 0;

    if ( input == 0l )
    {
        output[19] = 48;
        return;
    }

    while ( input != 0 )
    {
        output[len--] = ( uint16_t )( input % 10 ) + 48;
        input = input / 10;
    }
}

void int64_to_str( int64_t input, char * output )
{
    bool negative;
    uint16_t len;
    uint64_t tmp;

    for ( len = 0; len < 20; len++ )
    {
        output[len] = ' ';
    }

    output[len] = 0;
    negative = false;

    if ( input == 0l )
    {
        output[19] = 48;
        return;
    }

    tmp = ( uint64_t ) input;
    if ( input < 0 )
    {
        negative = true;
        tmp = ( uint64_t )( 0 - input );
    }

    len = 19;

    while ( tmp != 0 )
    {
        output[len--] = ( uint64_t )( tmp % 10 ) + 48;
        tmp = tmp / 10;
    }

    if ( negative )
    {
        output[len] = '-';
    }
}
#endif

uint8_t dec_to_bcd( uint8_t decnum )
{
    uint8_t tmp;

    tmp = 0;

    if ( decnum > 9 )
    {
        tmp = decnum / 10;
        tmp <<= 4;
        tmp |= ( decnum % 10 );
    }
    else
    {
        tmp = decnum;
    }

    return tmp;
}

uint8_t bcd_to_dec( uint8_t bcdnum )
{
    uint8_t tmp = 0;

    tmp = ( bcdnum >> 4 ) * 10;
    tmp += ( bcdnum & 0x0F );

    return tmp;
}

uint16_t bcd_to_dec16( uint16_t bcdnum )
{
    uint16_t tmp = 0;

    tmp = ( bcdnum >> 12 ) * 1000;
    tmp += ( ( ( bcdnum & 0x0F00 ) >> 8 ) * 100 );
    tmp += ( ( ( bcdnum & 0x00F0 ) >> 4 )  * 10 );
    tmp += ( bcdnum & 0x000F );

    return tmp;
}

uint16_t dec_to_bcd16( uint16_t decnum )
{
    uint16_t d;
    uint16_t tmp;

    tmp = 0;

    d = decnum / 1000;
    tmp |= ( d << 12 );
    decnum -= ( d * 1000 );

    d = decnum / 100;
    tmp |= ( d << 8 );
    decnum -= ( d * 100 );

    d = decnum / 10;
    tmp |= ( d << 4 );
    decnum -= ( d * 10 );

    tmp |= decnum;
    return tmp;
}

char * r_trim( char * string )
{
    char * original;
    original = string + strlen( string );

    while ( ( *--original == ' ' ) && ( original >= string ) )
    {
        ;
    }

    *( original + 1 ) = 0;

    return string;
}


char * l_trim( char * string )
{
    char * original;
    char * p;
    int16_t trimmed;

    trimmed = 0;
    original = string;
    p = original;

    do
    {
        if  (*original != ' ' || trimmed )
        {
            trimmed = 1;
            *p++ = *original;
        }
    } while ( *original++ != 0 );

    return string;
}

uint8_t float_to_str( float f_num, char * string )
{
    int8_t  bpoint;
    uint8_t i;
    uint8_t d;
    int8_t dexpon;   // Decimal exponent
    union f32_ul un;

    dexpon = 0;
    bpoint = 0;
    un.fl = f_num;

    if ( un.ul == F32_NAN )
    {
        strcpy( string, "NaN" );
        return 3;                   // return 3 if not a number (NaN)
    }

    i = 1;                          // The function returns 1 if +INF or 2 if -INF

    #ifdef __CONVERSIONS_CHIPS_32BIT__
    if ( un.uc[F32_BO] & 0x80 )
    {                               // Byte ordering. 3 = Little endian.
        un.uc[F32_BO] ^= 0x80;      // If fnum < 0 then fnum = -fnum
        i++;
        *string++ = '-';
    }
    #elif defined(__CONVERSIONS_CHIPS_PIC__)
    if ( un.uc[F32_BO-1] & 0x80 )
    {                               // Byte ordering. 3 = Little endian.
        un.uc[F32_BO-1] ^= 0x80;      // If fnum < 0 then fnum = -fnum
        i++;
        *string++ = '-';
    }
    #endif

    if ( un.ul == F32_ZERO )
    {
        strcpy( string, "0" );
        return 0;
    }

    if ( un.ul == F32_PLUS_INF )
    {
        strcpy( string, "INF" );
        return i;                   // i = 1 if +INF, 2 if -INF
    }

    while (un.fl < 1e-6)
    {
        un.fl *= 1e6;
        dexpon -= 6;
    }

    while ( un.fl < 1.0 )           // Convert float to a value in the range
    {
        un.fl *= 10.0;              // 1.0 to 9.999999 and adjust decimal exponent
        dexpon--;
    }

    while (un.fl >= 1e6)
    {
        un.fl *= 1e-6;
        dexpon += 6;
    }

    while ( un.fl >= 10.0 )
    {
        un.fl *= 0.1;
        dexpon++;
    }

    // From here on, we'll treat it as a fixed-point fraction with byte
    // 1 = integer part, and bytes 2, 3 and 4 = fractional part
    #ifdef __CONVERSIONS_CHIPS_32BIT__
    un.ul <<= 1;                              // move exponent into most significant byte
    #elif defined(__CONVERSIONS_CHIPS_PIC__)
    {
        uint32_t aux;
        aux = un.ul & 0x007FFFFF;
        aux <<= 1;
        un.ul &= 0xFF000000;
        un.ul |= aux;
    }
    #endif

    d = un.uc[F32_BO] - 127;                  // d = exponent unbiased. As (1.0 < un.fl < 10.0)
                                              // d can be: 0, 1, 2 or 3.
                                              // (1 = 1.0*2^0 and 9 = 1.001*2^3)
    un.uc[F32_BO] = 1;                        // clear exponent, re-insert the hidden bit
    un.ul <<= d;                              // (integer part) and adjust the binary exponent to zero
    *string++ = '0' + un.uc[F32_BO];          // write first decimal digit and

    if ( ( dexpon < 1 ) || ( dexpon > 6 ) )   // if dexp < 1 or dexp > 6
    {
        *string++ = '.';                      // write decimal point after first digit
        bpoint = 1;
    }

    for ( d = F32_NDIG - 1; d != 0; d-- )
    {
        un.uc[F32_BO] = 0;                    // Integer part = 0
        un.ul += ( un.ul << 2 );              // un.ul = 5*(un.ul). Multiply by 10 (5*2)
        un.ul <<= 1;                          // un.ul = 2*(un.ul)
        *string++ = '0' + un.uc[F32_BO];      // Write next decimal digit

        if ( bpoint == 0 )                    // If decimal point yet no written
        {
            if ( --dexpon == 0 )
            {
                *string++ = '.';              // Write decimal point when dexpon == 0
                bpoint = 1;
            }
        }
    }

    while ( string[-1] == '0' )               // Delete final zeros after the decimal point
    {
        string--;
    }

    if ( string[-1] == '.' )                  // Delete decimal point if it is the last character
    {
        string--;
    }

    if ( dexpon != 0 )
    {
        *string++ = 'e';                      // Write the exponent with maximum 2 digits
        if ( dexpon < 0 )
        {
            *string++ = '-';
            dexpon = -dexpon;
        }

        d = ( uint8_t )dexpon;

        if ( d > 9 )
        {
            *string++ = '0' + d / 10;
        }

        *string++ = '0' + d % 10;
    }
    *string = 0;

    return 0;
}

uint8_t str_to_uint8( char uint8_in[3] )
{
    uint8_t i;
    uint8_t counter = 0;
    char buf_str2[3] = {0};
    uint8_t result;
    uint8_t multiplier;

    result = 0;
    multiplier = 1;

    i = strlen( uint8_in );

    if ( i <= 3 )
    {
        multiplier = forward_input( uint8_in, &buf_str2, &counter );

        if ( counter == 0 )
        {
            if( multiplier == 1 ) {
                  result = (buf_str2[0] - '0') * 1;
                } else if( multiplier == 10 ) {
                  result = (buf_str2[1] - '0') * 1;
                  result = result + (buf_str2[0] - '0') * 10;
                } else if( multiplier == 100 ) {
                  result = (buf_str2[2] - '0') * 1;
                  result = result + (buf_str2[1] - '0') * 10;
                  result = result + (buf_str2[0] - '0') * 100;
                }
        }
        else
        {
            result = 0;
        }
    }
    else
    {
        result = 0;
    }

    return result;
}

int8_t str_to_int8( char int8_in[4] )
{
    uint8_t i;
    uint8_t i1;
    uint8_t counter;
    char buf_str2[4] = {0};
    uint16_t multiplier;
    int8_t result;

    counter = 0;
    result = 0;
    multiplier = 1;
    i = i1 = strlen( int8_in );

    if ( i <= 4 )
    {
        multiplier = forward_input( int8_in, &buf_str2, &counter );

        if ( counter <= 1 )
        {
            if ( int8_in[0] != '-' )
            {
                for ( i = 0; i < i1; i++ )
                {
                    result += ( buf_str2[i] - '0' ) * multiplier;
                    multiplier /= 10;
                }

                if ( result == -128 )
                {
                    result = 0;
                }
            }
            else if ( ( int8_in[0] = '-' ) && ( counter == 1 ) )
            {
                for ( i = 1; i < i1; i++ )
                {
                    result += ( buf_str2[i] - '0' ) * multiplier;
                    multiplier /= 10;
                }

                result = 0 - result;

                if ( result == 127 )
                {
                    result = 0;
                }
            }
        }
        else
        {
            result = 0;
        }
    }
    else
    {
        result = 0;
    }

    return result;
}

int16_t str_to_int16( char int16_in[6] )
{
    uint8_t i;
    uint8_t i1;
    uint8_t counter;
    char buf_str2[6] = {0};
    int16_t result;
    uint32_t multiplier;

    counter = 0;
    result = 0;
    multiplier = 1;
    i = i1 = strlen( int16_in );

    if ( i <= 6 )
    {
        multiplier = forward_input( int16_in, &buf_str2, &counter );

        if ( counter <= 1 )
        {
            if ( int16_in[0] != '-' )
            {
                for ( i = 0; i < i1; i++ )
                {
                    result += ( buf_str2[i] - '0' ) * multiplier;
                    multiplier /= 10;
                }
                if ( result == -32768 )
                {
                    result = 0;
                }
            }
            else if ( ( int16_in[0] = '-' ) && ( counter == 1 ) )
            {
                for ( i = 1; i < i1; i++ )
                {
                    result += ( buf_str2[i] - '0' ) * multiplier;
                    multiplier /= 10;
                }
                result = 0 - result;
                if ( result == 32767 )
                {
                    result = 0;
                }
            }
        }
        else
        {
            result = 0;
        }
    }
    else
    {
        result = 0;
    }

    return result;
}

uint16_t str_to_uint16( char uint16_in[5] )
{
    uint8_t i;
    uint8_t i1;
    uint8_t counter;
    char buf_str2[5] = {0};
    uint16_t result;
    uint32_t multiplier;

    counter = 0;
    result = 0;
    multiplier = 1;
    i = i1 = strlen( uint16_in );

    if ( i <= 5 )
    {
        multiplier = forward_input( uint16_in, &buf_str2, &counter );

        if ( counter == 0 )
        {
            for ( i = 0; i < i1; i++ )
            {
                result = result + ( buf_str2[i] - '0' ) * multiplier;
                multiplier = multiplier / 10;
            }
        }
        else
        {
            result = 0;
        }
    }
    else
    {
        result = 0;
    }

    return result;
}

uint32_t str_to_uint32( char uint32_in[10] )
{
    uint8_t i;
    uint8_t i1;
    uint8_t counter;
    char buf_str[10] = {0};
    uint32_t result;
#ifdef __CONVERSIONS_SUBSET__
    uint32_t multiplier;
#else
    uint64_t multiplier;
#endif

    counter = 0;
    result = 0;
    multiplier = 1;

    i = i1 = strlen( uint32_in );

    if ( i <= 10 )
    {
        multiplier = forward_input( uint32_in, &buf_str, &counter );

        if ( counter == 0 )
        {
            for ( i = 0; i < i1; i++ )
            {
                result = result + ( buf_str[i] - '0' ) * multiplier;
                multiplier = multiplier/10;
            }
        }
        else
        {
            result = 0;
        }
    }
    else
    {
        result = 0;
    }
    return result;
}

int32_t str_to_int32( char int32_in[11] )
{
    uint8_t i;
    uint8_t i1;
    uint8_t counter;
    char buf_str[11] = {0};
    int32_t result;
#ifdef __CONVERSIONS_SUBSET__
    uint32_t multiplier;
#else
    uint64_t multiplier;
#endif

    counter = 0;
    result = 0;
    multiplier = 1;

    i = i1 = strlen( int32_in );

    if ( i <= 11 )
    {
        multiplier = forward_input( int32_in, &buf_str, &counter );

        if ( counter <= 1 )
        {
            if ( int32_in[0] != '-' )
            {
                for ( i = 0; i < i1; i++ )
                {
                    result += ( buf_str[i] - '0' ) * multiplier;
                    multiplier /= 10;
                }
                if ( result == -2147483648 )
                {
                    result = 0;
                }

            }
            else if ( ( int32_in[0] = '-' ) && ( counter == 1 ) )
            {
                for ( i = 1; i < i1; i++ )
                {
                    result += ( buf_str[i] - '0' ) * multiplier;
                    multiplier /= 10;
                }

                result = 0 - result;

                if ( result == 2147483647 )
                {
                    result = 0;
                }
            }
        }
        else
        {
            result = 0;
        }
    }
    else
    {
        result = 0;
    }

    return result;
}

#ifdef __CONVERSIONS_SET__
int64_t str_to_int64( char int64_in[20] )
{
    uint8_t i;
    uint8_t i1;
    uint8_t counter;
    char buf_str[20] = {0};
    int64_t result;
    uint64_t multiplier;

    counter = 0;
    result = 0;
    multiplier = 1;

    i = i1 = strlen( int64_in );

    if ( i <= 20 )
    {
        multiplier = forward_input( int64_in, &buf_str, &counter );

        if ( counter <= 1 )
        {
            if ( int64_in[0] != '-' )
            {
                for ( i = 0; i < i1; i++ )
                {
                    result += ( buf_str[i] - '0' ) * multiplier;
                    multiplier /= 10;
                }
                if ( result < 0 )
                {
                    result = 0;
                }
            }
            else if ( ( int64_in[0] = '-' ) && ( counter == 1 ) )
            {
                for ( i = 1; i < i1; i++ )
                {
                    result += ( buf_str[i] - '0' ) * multiplier;
                    multiplier /= 10;
                }
                result = 0 - result;
                if ( result > 0 )
                {
                    result = 0;
                }
            }
        }
        else
        {
            result = 0;
        }
    }
    else
    {
        result = 0;
    }

    return result;
}

uint64_t str_to_uint64( char uint64_in[20] )
{
    uint8_t i;
    uint8_t i1;
    uint8_t counter;
    char buf_str[20] = {0};
    uint64_t result;
    uint64_t multiplier;

    counter = 0;
    result = 0;
    multiplier = 1;

    i = i1 = strlen( uint64_in ) ;

    if ( i <= 20 )
    {
        multiplier = forward_input( uint64_in, &buf_str, &counter );

        if ( counter == 0 )
        {
            for ( i = 0; i < i1; i++ )
            {
                result = result + ( buf_str[i] - '0' ) * multiplier;
                multiplier = multiplier / 10;
            }
        }
        else
        {
            result = 0;
        }
    }
    else
    {
        result = 0;
    }

    return result;
}
#endif

float str_to_float( char data_str[20] )
{
    int16_t i;
    int16_t cnt;
    int16_t point_pos;
    int16_t divider;
    int16_t point_check;
    bool negative_sign;
    uint8_t counter;
    float result;
#ifdef __CONVERSIONS_SUBSET__
    uint32_t multiplier;
#else
    uint64_t multiplier;
#endif

    divider = 10;
    negative_sign = false;
    point_check = 0;
    counter = 0;
    result = 0.;
    multiplier = 1;

    cnt = strlen( data_str );

    for ( i = 0; i < cnt; i++ )
    {
        if ( data_str[i] == '.' )
        {
            point_check++;
        }
    }
    if ( ( point_check <= 1 ) && ( cnt <=20 ) )                 // check if there are more than one '.' and
    {                                                           // if there are less than 20 characters alltogether
        for ( i = 0; i < cnt; i++ )
        {
            if ( data_str[i] == '.' )
            {
                point_pos = i;
                break;
            }
            multiplier *= 10;
        }

        if ( ( point_pos < 10 ) && ( cnt - point_pos <= 10 ) )  // make sure there are 10 or less characters
        {                                                       // on both sides of the '.'
            multiplier /= 10;

            if ( data_str[0] == '-' )
            {
                negative_sign = true;
                multiplier /= 10;
            }

            for ( i = negative_sign; i < point_pos; i++ )
            {
                result += ( ( float )( data_str[i] - '0' ) ) * ( ( float )multiplier );
                multiplier /= 10;
                if ( ( data_str[i] < '0' ) || ( data_str[i] > '9' ) )
                {
                    counter++;
                }
            }

            for ( i = ( point_pos + 1 ); i < cnt; i++ )
            {
                result += ( ( float )( data_str[i] - '0' ) ) / ( ( float )divider );
                divider *= 10;

                if ( ( data_str[i] < '0' ) || ( data_str[i] > '9' ) )
                {
                    counter++;
                }
            }

            if ( negative_sign )
            {
                result = 0 - result;
            }

            if ( counter )
            {
                result = 0.;
            }
        }
    }
    else
    {
        result = 0.;
    }

    return result;
}

uint8_t hex_to_uint8( char hex_in[2] )
{
    uint8_t counter;
    uint8_t counter1;
    uint8_t counter2;
    uint8_t result1;
    uint8_t result2;
    uint8_t result;

    counter  = 0;
    counter1 = 0;
    counter2 = 0;
    result = 0;

    // Check if one ( or both ) elements of argument does( do ) not have hexadecimal symbols

    counter = check_input( hex_in );

        if ( !counter )
        {
            // Adjust 1st hexadecimal symbol

            counter1 = adjust_hex( &hex_in[0], &result1 );
            result1 = result1 << 4;

            // Adjust 2nd hexadecimal symbol

            counter2 = adjust_hex( &hex_in[1], &result2 );
            result = result1 + result2;

                if ( ( counter1 + counter2 ) > 4 )
                {
                    result = 0;
                }
        }
        else
        {
            result = 0;
        }

    return result;
}

uint16_t hex_to_uint16( char hex_in[4] )
{
    char buf_str[3];
    uint8_t counter;
    uint16_t result;

    counter  = 0;

    // Check if element( s ) of argument does( do ) not have hexadecimal symbols

    counter = check_input( hex_in );

        if ( !counter )
        {
            // Adjust 1st and 2nd hexadecimal symbol

            buf_str[0] = hex_in[0];
            buf_str[1] = hex_in[1];
            buf_str[2] = 0;

            result = ( uint16_t )hex_to_uint8( buf_str ) << 8;

            // Adjust 3rd and 4th hexadecimal symbol

            buf_str[0] = hex_in[2];
            buf_str[1] = hex_in[3];
            buf_str[2] = 0;

            result = result + ( uint16_t )hex_to_uint8( buf_str );
        }
        else
        {
            result = 0;
        }

    return result;
}

uint32_t hex_to_uint32( char hex_in[8] )
{
    char buf_str[5];
    uint8_t counter;
    uint32_t result;

    // Check if element( s ) of argument does( do ) not have hexadecimal symbols

    counter = check_input( hex_in );

       if ( !counter )
       {
           // Adjust 1st, 2nd, 3rd and 4th hexadecimal symbol

           buf_str[0] = hex_in[0];
           buf_str[1] = hex_in[1];
           buf_str[2] = hex_in[2];
           buf_str[3] = hex_in[3];
           buf_str[4] = 0;

           result = ( uint32_t )hex_to_uint16( buf_str ) << 16;

           // Adjust 5th, 6th, 7th and 8th hexadecimal symbol

           buf_str[0] = hex_in[4];
           buf_str[1] = hex_in[5];
           buf_str[2] = hex_in[6];
           buf_str[3] = hex_in[7];
           buf_str[4] = 0;

           result = result + ( uint32_t )hex_to_uint16( buf_str );
       }
       else
       {
           result = 0;
       }

    return result;
}

#ifdef __CONVERSIONS_SET__
uint64_t hex_to_uint64( char hex_in[16] )
{
    char buf_str[9];
    uint8_t counter = 0;
    uint64_t result;
    uint8_t i;

    // Check if element( s ) of argument does( do ) not have hexadecimal symbols

    counter = check_input( hex_in );

        if ( !counter )
        {

            // Adjust 1st - 8th hexadecimal symbol

            buf_str[0] = hex_in[0];
            buf_str[1] = hex_in[1];
            buf_str[2] = hex_in[2];
            buf_str[3] = hex_in[3];
            buf_str[4] = hex_in[4];
            buf_str[5] = hex_in[5];
            buf_str[6] = hex_in[6];
            buf_str[7] = hex_in[7];
            buf_str[8] = 0;

            result = ( uint64_t )hex_to_uint32( buf_str ) << 32;

            // Adjust 8th - 16th hexadecimal symbol

            buf_str[0] = hex_in[8];
            buf_str[1] = hex_in[9];
            buf_str[2] = hex_in[10];
            buf_str[3] = hex_in[11];
            buf_str[4] = hex_in[12];
            buf_str[5] = hex_in[13];
            buf_str[6] = hex_in[14];
            buf_str[7] = hex_in[15];
            buf_str[8] = 0;

            result = result + ( uint64_t )hex_to_uint32( buf_str );
        }
        else
        {
            result = 0;
        }

    return result;
}
#endif

int8_t hex_to_int8( char hex_in[2] )
{
    return (int8_t) hex_to_uint8(hex_in);
}

int16_t hex_to_int16( char hex_in[4] )
{
    return (int16_t) hex_to_uint16(hex_in);
}

int32_t hex_to_int32( char hex_in[8] )
{
    return (int32_t) hex_to_uint32(hex_in);
}

#ifdef __CONVERSIONS_SET__
int64_t hex_to_int64( char hex_in[16] )
{
    return (int64_t) hex_to_uint64(hex_in);
}

uint8_t long_double_to_str( long double dnum, char * str )
{
    uint8_t bpoint;
    uint16_t i;
    uint16_t d;
    int16_t dexpon;           // Decimal exponent
    union f64_ul un;

    bpoint = 0;
    dexpon = 0;
    un.ld = dnum;

    if ( un.ull == F64_NAN )
    {
        strcpy( str, "NaN" );
        return 3;             // return 3 if not a number (NaN)
    }

    i = 1;                    // The function returns 1 if +INF or 2 if -INF

    if ( un.sign == 1 )        // Byte ordering. 3 = Little endian.
    {
        un.sign = 0;          // If fnum < 0 then fnum = -fnum
        i++;
        *str++ = '-';
    }

    if ( un.ull == F64_ZERO )
    {
        strcpy( str, "0" );
        return 0;
    }
    if ( un.ull == F64_PLUS_INF )
    {
        strcpy( str, "INF" );
        return i;             // i = 1 if +INF, 2 if -INF
    }

    while ( un.ld < 1e-6 )
    {
        un.ld *= 1e6;
        dexpon -= 6;
    }

    while ( un.ld < 1.0l )    // Convert float to a value in the range
    {
        un.ld *= 10.0l;       // 1.0 to 9.999999 and adjust decimal exponent
        dexpon--;
    }

    while ( un.ld >= 1e6 )
    {
        un.ld *= 1e-6;
        dexpon += 6;
    }

    while ( un.ld >= 10.0l )
    {
        un.ld *= 0.1l;
        dexpon++;
    }

    // From here on, we'll treat it as a fixed-point fraction with byte
    // 1 = integer part, and bytes 2, 3 and 4 = fractional part

    d = un.exponent - 1023;             // d = exponent unbiased. As (1.0 < un.fl < 10.0)
                                        // d can be: 0, 1, 2 or 3.
                                        // (1 = 1.0*2^0 and 9 = 1.001*2^3)
    un.uc[F64_BO] = 1;                  // clear exponent, re-insert the hidden bit
    un.exponent = 1;

    un.ull <<= 4;

    un.ull <<= d;                            // (integer part) and adjust the binary exponent to zero

    *str++ = '0' + un.uc[F64_BO];            // write first decimal digit and

    if ( ( dexpon < 1 ) || ( dexpon > 6 ) )  // if dexp < 1 or dexp > 6
    {
        *str++ = '.';                        // write decimal point after first digit
        bpoint = 1;
    }

    for ( d = F64_NDIG -1; d != 0; d-- )
    {
        un.uc[F64_BO] = 0;                   // Integer part = 0
        un.ull += ( un.ull << 2 );           // un.ul = 5*(un.ul). Multiply by 10 (5*2)
        un.ull <<= 1;                        // un.ul = 2*(un.ul)
        *str++ = '0' + un.uc[F64_BO];        // Write next decimal digit
        if ( bpoint == 0 )                   // If decimal point yet no written
        {
            if ( --dexpon == 0 )
            {
                *str++ = '.';                // Write decimal point when dexpon == 0
                bpoint = 1;
            }
        }
    }

    while ( str[-1] == '0' )                 // Delete final zeros after the decimal point
    {
        str--;
    }

    if ( str[-1] == '.' )                    // Delete decimal point if it is the last character
    {
        str--;
    }

    if ( dexpon != 0 )
    {
        *str++ = 'e';                        // Write the exponent with maximum 2 digits
        if ( dexpon < 0 )
        {
            *str++ = '-';
            dexpon = -dexpon;
        }

        d = ( uint32_t )dexpon;

        if ( d > 99 )
        {
            *str++ = '0' + ( uint32_t )d / 100;
            *str++ = '0' + ( ( ( uint32_t )d / 10 ) % 10 );
        }
        if ( ( d > 9 ) && ( d < 99 ) )
        {
            *str++ = '0' + ( uint32_t ) d / 10;
            *str++ = '0' + ( uint32_t ) d % 10;
        }
    }

    *str = 0;

    return 0;
}
#endif

// ----------------------------------------------- PRIVATE FUNCTION DEFINITIONS
#ifdef __CONVERSIONS_SUBSET__
static uint32_t forward_input( char * byte_in, char * buf_str2, uint8_t * counter )
#else
static uint64_t forward_input( char * byte_in, char * buf_str2, uint8_t * counter )
#endif
{
    uint8_t i;
    char tmp;
#ifdef __CONVERSIONS_SUBSET__
    uint32_t multiplier;
#else
    uint64_t multiplier;
#endif

    i = strlen( byte_in );
    multiplier = 1;

    while ( i > 0 )
    {
        tmp = *( byte_in + i - 1 );

        if ( ( tmp >= '0' ) && ( tmp <= '9' ) )
        {
            *( buf_str2 + i - 1 ) = *( byte_in + i - 1 );
            multiplier *= 10;
        }
        else
        {
            *( counter ) += 1;
        }

        i--;
    }

    multiplier /= 10;

    return multiplier;
}

static char adjust_hex( char * byte_in, char * result )
{
    char tmp;
    uint8_t counter;

    tmp = *byte_in;
    counter = 0;

    if ( ( tmp >= '0' ) && ( tmp <= '9' ) )
    {
        *result = ( tmp - 48 );
    }
    else
    {
        counter++;
    }

    if ( ( tmp >= 'A' ) && ( tmp <= 'F' ) )
    {
        *result = ( tmp - 55 );
    }
    else
    {
        counter++;
    }

    if ( ( tmp >= 'a' ) && ( tmp <= 'f' ) )
    {
        *result = ( tmp - 87 );
    }
    else
    {
        counter++;
    }

    return counter;
}

static char check_input( char * hex_in )
{
    uint8_t i;
    uint8_t counter;

    counter = 0;

    for ( i = 0; i < strlen( hex_in ); i++ )
    {
        if ( ( hex_in[i] < '0' ) || ( hex_in[i] > 'f' ) )
        {
            counter++;
        }
        if ( ( hex_in[i] > '9' ) && ( hex_in[i] < 'A' ) )
        {
            counter++;
        }
        if ( ( hex_in[i] > 'F' ) && ( hex_in[i] < 'a' ) )
        {
            counter++;
        }
    }

    return counter;
}

// ------------------------------------------------------------------------- END
