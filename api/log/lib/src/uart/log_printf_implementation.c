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

#include <stdarg.h>

#ifdef __MIKROC__
#include "ctype.h"
#endif

#include "drv_uart.h"
#include "log_printf_implementation.h"


#define SELECT_FLOAT 1
#define SELECT_DOUBLE 0

#define DBL_MAX_EXP 128
#define DBL_MAX_10_EXP 38

#define _div_to_l_(a, b) ((unsigned long)((a)/(b)))

#if defined( SELECT_FLOAT ) && !defined( SELECT_LONG )
    #define SELECT_LONG 1
#endif

#define frexp(val, ptr) (*(ptr) = ((*(unsigned long *)&val >> __mantis_value__) & 255) - 126)

#ifdef SELECT_LONG
    #define value long
// max number of digits to be printed
#define NDIG 12
#else
    #define value int
// max number of digits to be printed
    #define NDIG 6
#endif



#if SELECT_DOUBLE

union { unsigned long ul[ 40 ]; float db[ 20 ]; }
_fdp = {
    0x00000001,0x00000000,
    0x0000000A,0x00000000,
    0x00000064,0x00000000,
    0x000003E8,0x00000000,
    0x00002710,0x00000000,
    0x000186A0,0x00000000,
    0x000F4240,0x00000000,
    0x00989680,0x00000000,
    0x05F5E100,0x00000000,
    0x3B9ACA00,0x00000000,
    0x540BE400,0x00000002,
    0x4876E800,0x00000017,
    0xD4A51000,0x000000E8,
    0x4E72A000,0x00000918,
    0x107A4000,0x00005AF3,
    0xA4C68000,0x00038D7E,
    0x6FC10000,0x002386F2,
    0x5D8A0000,0x01634578,
    0xA7640000,0x0DE0B6B3,
    0x89E80000,0x8AC72304,
};

#define fdpowers _fdp.db

#else
    #define fdpowers dpowers
#endif


// Tables of powers of 10, for use in atof and doprnt.

static const code float _powers_[] =
{
    1e0,
    1e1,
    1e2,
    1e3,
    1e4,
    1e5,
    1e6,
    1e7,
    1e8,
    1e9,
    1e10,
    1e20,
    1e30,
};

static const code float _npowers_[] =
{
    1e-0,
    1e-1,
    1e-2,
    1e-3,
    1e-4,
    1e-5,
    1e-6,
    1e-7,
    1e-8,
    1e-9,
    1e-10,
    1e-20,
    1e-30,
};

static const code char  hexb[] = "0123456789ABCDEF";
static const code char  hexs[] = "0123456789abcdef";


const code static unsigned value dpowers[ ] =
{
    1, 10, 100, 1000, 10000,
#ifdef SELECT_LONG
    100000, 1000000, 10000000, 100000000,
    1000000000
#endif
};


const code static unsigned value hexpowers[ ] =
{
    1, 0x10, 0x100, 0x1000,
#if SELECT_LONG
    0x10000, 0x100000, 0x1000000, 0x10000000
#endif
};

const code static unsigned value octpowers[ ] =
{
    1, 010, 0100, 01000, 010000, 0100000,
#ifdef SELECT_LONG
    01000000, 010000000, 0100000000, 01000000000, 010000000000,
    0000000000000
#endif
};

//-----------------------------------------------------------------------------
//----------------------------------------------------------------------- FLOAT

#ifdef SELECT_FLOAT

#define NDDIG ( sizeof fdpowers/sizeof fdpowers[0] )
#define expon signed char

// this routine returns a value to round to the
// number of decimal places specified

static float fround ( unsigned char prec )
{
    // prec is guaranteed to be less than NDIG
    if ( prec >= 110 )
    {
        return 0.5 * _npowers_[ prec / 100 + 18 ] * _npowers_[ ( prec % 100 ) / 10 + 9 ] * _npowers_[ prec % 10 ];
    }
    else if ( prec > 10 )
    {
        return 0.5 * _npowers_[ prec / 10 + 9 ] * _npowers_[ prec % 10 ];
    }
    return 0.5 * _npowers_[ prec ];
}

// this routine returns a scaling factor
// equal to 1 to the decimal power supplied

static float scale ( expon scl )
{
    if ( scl < 0 )
    {
        scl = -scl;
        if ( scl >= 110 )
        {
            return _npowers_[scl/100+18] * _npowers_[(scl%100)/10+9] * _npowers_[scl%10];
        }
        else if ( scl > 10 )
        {
            return _npowers_[scl/10+9] * _npowers_[scl%10];
        }
        return _npowers_[scl];
    }
    if ( scl >= 110 )
    {
        return _powers_[scl/100+18] * _powers_[(scl%100)/10+9] * _powers_[scl%10];
    }
    else if ( scl > 10 )
    {
        return _powers_[scl/10+9] * _powers_[scl%10];
    }
    return _powers_[scl];
}

#endif    // SELECT_FLOAT
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------

#define OPTSIGN    0x00
#define SPCSIGN    0x01
#define MANSIGN    0x02
#define NEGSIGN    0x03
#define FILL       0x04
#define LEFT       0x08
#define LONG       0x10
#define UPCASE     0x20
#define TEN        0x00
#define EIGHT      0x40
#define SIXTEEN    0x80
#define UNSIGN     0xC0
#define BASEM      0xC0
#define EFMT       0x100
#define GFMT       0x200
#define FFMT       0x400
#define ALTERN     0x800
#define DEFPREC    0x1000
#define POINTER    0x2000

#define pputc(log, c) do{uint8_t buf = c; uart_write(&log->uart, &buf, 1); } while(0)

int log_implementation_do_prntf ( log_t *log, const code char * __generic_ptr f, va_list ap )
{
    int        prec;
    char       c;
    int        width;
    unsigned   flag;
    int        ccnt = 0;

#ifdef SELECT_FLOAT
    float      fval;
    int        exp;
#if SELECT_DOUBLE
    float      ival;
#endif
    union
    {
        unsigned value  _val;
        struct
        {
            char        *_cp;
            unsigned    _len;
        }_str;

        float  _integ;
    }_val;
#else
    union
    {
        unsigned value  _val;
        struct
        {
            char *      _cp;
            unsigned    _len;
        }_str;
    }_val;
#endif

#define val   _val._val
#define cp    _val._str._cp
#define len   _val._str._len
#define integ _val._integ

    flag = 0;
    while ( c = *f++ )
    {
        if ( c != '%' )
        {
            pputc( log, c );
            continue;
        }
        width = 0;
        flag = 0;
        for ( ; ; )
        {
            switch( *f )
            {
                case '-':
                {
                    flag |= LEFT;
                    f++;
                    continue;
                }
                case ' ':
                {
                    flag |= SPCSIGN;
                    f++;
                    continue;
                }
                case '+':
                {
                    flag |= MANSIGN;
                    f++;
                    continue;
                }
                case '#':
                {
                    flag |= ALTERN;
                    f++;
                    continue;
                }
                case '0':
                {
                    flag |= FILL;
                    f++;
                    continue;
                }
            }
            break;
        }
        if ( flag & MANSIGN )
        {
            flag &= ~SPCSIGN;
        }
        if ( flag & LEFT )
        {
            flag &= ~FILL;
        }
        if ( isdigit( ( unsigned )*f ) )
        {
            width = 0;
            do
            {
                width = width * 10 + *f++ - '0';
            } while ( isdigit ( ( unsigned ) *f ) );
        }
        else
        {
            if ( *f == '*' )
            {
                width = va_arg(ap, int);
                f++;
            }
            if ( *f == '.' )
            {
                if( *++f == '*' )
                {
                    prec = va_arg(ap, int);
                    f++;
                }
                else
                {
                    prec = 0;
                    while ( isdigit( ( unsigned )*f ) )
                    {
                        prec = prec*10 + *f++ - '0';
                    }
                }
            }
            else
            {
                prec = 0;
#ifdef SELECT_FLOAT
                flag |= DEFPREC;
#endif
            }
        }
#ifdef SELECT_LONG
loop:
#endif
        switch ( c = *f++ )
        {
            case 0:
            {
                return ccnt;
            }
            case 'l':
            case 'L':
            {
#ifdef SELECT_LONG
                flag |= LONG;
                goto loop;
#else
                cp = "(non-long printf)";
                goto strings;
#endif
            }
#ifndef SELECT_FLOAT
            case 'E':
            case 'f':
            case 'e':
            case 'g':
            {
                cp = "(non-float printf)";
                goto strings;
            }
#else
            case 'f':
            {
                flag |= FFMT;
                break;
            }
            case 'E':
            {
                flag |= UPCASE;
            }
            case 'e':
            {
                flag |= EFMT;
                break;
            }
            case 'g':
            {
                flag |= GFMT;
                break;
            }
#endif
            case 'o':
            {
                flag |= EIGHT;
                break;
            }
            case 'd':
            case 'i':
            {
                break;
            }
            case 'p':
            case 'X':
            {
                flag |= UPCASE;
            }
            case 'x':
            {
                flag |= SIXTEEN;
                break;
            }
            case 's':
            {
                cp = va_arg( ap, char* );
            }

#if !defined( SELECT_FLOAT )
strings:
#endif
            if ( cp == 0 )
            {
                cp = "(null)";
            }
            len = 0;
            while ( cp[ len ] )
            {
                len++;
            }

dostring:

            if ( prec && ( prec < len ) )
            {
                len = prec;
            }

            if ( width > len )
            {
                width -= len;
            }
            else
            {
                width = 0;
            }

            if ( !( flag & LEFT ) )
            {
                while ( width-- ) pputc( log, ' ' );
                while( len-- ) pputc( log, *cp++ );

                if ( flag & LEFT )
                {
                    while ( width-- ) pputc(log, ' ');
                }
                continue;
            }

            case 'c':
            {
                c = va_arg( ap, int );
            }
            default:
            {
                cp = &c;
                len = 1;
                goto dostring;
            }
            case 'u':
            {
                flag |= UNSIGN;
                break;
            }
        }
#ifdef SELECT_FLOAT
        if ( flag & ( EFMT | GFMT | FFMT ) )
        {
            if ( flag & DEFPREC ) prec = 6;
            fval = va_arg( ap, double ); // double
            if ( fval < 0.0 )
            {
                fval = -fval;
                flag |= NEGSIGN;
            }
            // If the number is zero, the exponent is zero.
            exp = 0;
            if ( fval!=0 )
            {
                // If the number is non-zero, find the exponent.
                frexp( fval, &exp ); // get binary exponent
                exp--;   // adjust 0.5 -> 1.0
                exp *= 3;
                exp /= 10; // estimate decimal exponent
                if ( exp < 0 ) exp--;
                integ = fval * scale(-exp);
                if ( integ < 1.0 ) exp--;
                else if ( integ >= 10.0 ) exp++;
            }
            if ( exp <= 0 ) c = 1;
            else c = exp;
            if ( flag & EFMT || flag & GFMT && ( exp < -4 || exp >= (int)prec ) )
            {
                // use e format
                if ( prec && flag & GFMT ) prec--; // g format precision includes integer digit
                if ( ( unsigned )prec > NDDIG - 2 ) c = NDDIG - 2;
                else c = prec;

                if( fval != 0 )
                {
                    // Normalise only if the number is non-zero.
                    fval /= scale(exp);
                    fval /= scale(-c);
                    if ( fval - (float)(unsigned long)fval >= 0.5 ) fval += 0.5;
                    if ( ( unsigned long )fval >= fdpowers[c+1] )
                    {
                        fval *= 1e-1;
                        exp++;
                    }
                    else if ( ( unsigned long )fval < fdpowers[c] )
                    {
                        fval *= 10.0;
                        exp--;
                    }
                }
                if ( flag & GFMT && !( flag & ALTERN ) )
                {   // g format, precision means something different */
                    if ( prec > (int)( NDDIG ) ) prec = NDDIG;
                    val = ( unsigned long )fval;
                    while ( val && val % 10 == 0 )
                    {
                        prec--;
                        val /= 10;
                    }
                    if ( prec < c )
                    {
                        fval /= scale( c-prec );
                        c = prec;
                    }
                }
                width -= prec + 5;
                if ( prec || flag & ALTERN ) width--;
                if ( flag & ( MANSIGN|SPCSIGN ) ) width--;
                if ( flag & FILL )
                {
                    if ( flag & MANSIGN ) pputc( log, flag & SPCSIGN ? '-' : '+' );
                    else if ( flag & SPCSIGN ) pputc(log, ' ');
                    while ( width > 0 )
                    {
                        pputc(log, '0');
                        width--;
                    }
                }
                else
                {
                    if( !(flag & LEFT ) )
                        while ( width > 0 )
                        {
                            pputc(log, ' ');
                            width--;
                        }
                    if ( flag & MANSIGN ) pputc( log, flag & SPCSIGN ? '-' : '+' );
                    else if( flag & SPCSIGN ) pputc(log, ' ');
                }
                val = (unsigned long)fval;
                pputc( log, val/fdpowers[c] + '0' );
                if ( prec || flag & ALTERN )
                {
                    pputc(log, '.');
                    prec -= c;
                    while( c )
                    {
                        pputc(log, '0' + (val/fdpowers[--c]) % 10);
                    }
                    while( prec )
                    {
                        pputc( log, '0' );
                        prec--;
                    }
                }
                if ( flag & UPCASE ) pputc(log, 'E');
                else pputc(log, 'e');
                if ( exp < 0 )
                {
                    exp = -exp;
                    pputc(log, '-');
                }
                else pputc(log, '+');
                pputc(log, exp / 10 + '0');
                pputc(log, exp % 10 + '0');
                if((flag & LEFT) && width > 0)
                    do
                        pputc(log, ' ');
                    while(--width);
                continue;
            }
            // here for f format

            if( flag & GFMT )
            {
                if ( exp < 0 ) prec -= exp-1;
                val = (unsigned long)fval;
                for ( c = 1; c != NDDIG; c++ )
                    if ( val < fdpowers[c] )
                        break;
                prec -= c;
                val = (unsigned long)((fval-(float)val) * scale(prec)+0.5);
                while ( prec && val % 10 == 0 )
                {
                    val /= 10;
                    prec--;
                }
            }
            if ( prec <= NDIG ) fval += fround(prec);
            // ~4.2e9 is the largest float that will with into a 32-bit long
            if ( fval != 0 && (unsigned long)fval == 0 && exp > 1 )
            {
                // fval is > 4.2e9
                // new exp must be such that div_to_l() is < 4.2e9
                if ( fval / scale(exp) < 4.294967296 ) exp -= NDDIG-1;
                else exp -= NDDIG-2;
                val = _div_to_l_( fval, scale ( exp ) );
                fval = 0.0;
            }
            else
            {
                val = (unsigned long)fval;
                fval -= (float)val;
                exp = 0;
            }
            for ( c = 1; c != NDDIG; c++ )
                if ( val < fdpowers[c] )
                    break;
            width -= prec + c + exp;
            if ( flag & ALTERN || prec ) width--;
            if ( flag & (MANSIGN|SPCSIGN ) ) width--;
            if ( flag & FILL )
            {
                if ( flag & MANSIGN ) pputc(log, flag & SPCSIGN ? '-' : '+');
                else if ( flag & SPCSIGN ) pputc(log, ' ');
                while ( width > 0 )
                {
                    pputc(log, '0');
                    width--;
                }
            }
            else
            {
                if ( !(flag & LEFT ) )
                    while(width > 0)
                    {
                        pputc(log, ' ');
                        width--;
                    }
                if ( flag & MANSIGN ) pputc( log, flag & SPCSIGN ? '-' : '+' );
                else if ( flag & SPCSIGN ) pputc(log, ' ');
            }
            while ( c-- ) pputc(log, '0' + (val/fdpowers[c]) % 10);
            while( exp > 0 )
            {
                pputc(log, '0');
                exp--;
            }
            if ( prec > (int)(NDDIG-2) ) c = NDDIG-2;
            else c = prec;
            prec -= c;
            if ( c || flag & ALTERN ) pputc(log, '.');

            val = (long)(fval * scale(c));
            while( c )  pputc(log, '0' + (val/fdpowers[--c]) % 10);

            while( prec )
            {
                pputc(log, '0');
                prec--;
            }
            if ( ( flag & LEFT ) && width > 0 )
                do
                    pputc(log, ' ');
                while(--width);
            continue;
    }
    #endif     // SELECT_FLOAT
        if ( ( flag & BASEM ) == TEN )
        {
    #ifdef SELECT_LONG
            if ( flag & LONG ) val = va_arg(ap, long);
            else
    #endif
            val = (value)va_arg(ap, int);
            if ( ( value )val < 0 )
            {
                flag |= NEGSIGN;
                val = -val;
            }
    }
    else
    {
    #ifdef        SELECT_LONG
            if ( flag & LONG ) val = va_arg(ap, unsigned long);
            else val = va_arg(ap, unsigned);
    #endif
        }
        if  ( prec == 0 && val == 0) prec++;
        switch((unsigned char)(flag & BASEM))
        {
            case TEN:
            case UNSIGN:
                for( c = 1; c != sizeof dpowers/sizeof dpowers[0]; c++)
                    if(val < dpowers[c])
                        break;
                    break;

            case SIXTEEN:
                for( c = 1; c != sizeof hexpowers/sizeof hexpowers[0]; c++)
                    if( val < hexpowers[c])
                        break;
                    break;

            case EIGHT:
                for( c = 1; c != sizeof octpowers/sizeof octpowers[0]; c++)
                    if( val < octpowers[c])
                        break;
                    break;
        }
        if ( c < prec ) c = prec;
        else if( prec < c ) prec = c;
        if( width && flag & NEGSIGN ) width--;
        if( width > prec ) width -= prec;
        else width = 0;
        if ( ( flag & ( FILL|BASEM|ALTERN ) ) == ( EIGHT|ALTERN ) )
        {
            if ( width ) width--;
        }
        else if ( ( flag & (BASEM|ALTERN ) ) == ( SIXTEEN|ALTERN ) )
        {
            if ( width > 2 ) width -= 2;
            else width = 0;
        }
        if ( flag & FILL )
        {
            if ( flag & MANSIGN ) pputc(log, flag & SPCSIGN ? '-' : '+');
            else if ( flag & SPCSIGN ) pputc(log, ' ');
            else if ( ( flag & (BASEM|ALTERN ) ) == ( SIXTEEN|ALTERN ) )
            {
                pputc(log, '0');
                pputc(log, flag & UPCASE ? 'X' : 'x');
            }
            if ( width )
                do
                    pputc(log, '0');
                while ( --width );
        }
        else
        {
            if ( width && !(flag & LEFT ) )
                do
                    pputc(log, ' ');
                    while( --width );
                    if ( flag & MANSIGN ) pputc(log, flag & SPCSIGN ? '-' : '+');
                    else if ( flag & SPCSIGN ) pputc(log, ' ');
                    if ( ( flag & (BASEM|ALTERN) ) == (EIGHT|ALTERN)) pputc(log, '0');
                    else if ( ( flag & (BASEM|ALTERN ) ) == (SIXTEEN|ALTERN))
                    {
                        pputc(log, '0');
                        pputc(log, flag & UPCASE ? 'X' : 'x');
                    }
        }
        while( prec > c ) pputc(log, '0');
        while( prec-- )
        {
            switch((unsigned char)(flag & BASEM))
            {
                case TEN:
                case UNSIGN:
                    c = (val / dpowers[prec]) % 10 + '0';
                    break;

                case SIXTEEN:
                    if (flag & UPCASE)
                        c = hexb[(val / hexpowers[prec]) & 0xF];
                    else
                        c =  hexs[(val / hexpowers[prec]) & 0xF];
                    break;

                case EIGHT:
                    c = ((val / octpowers[prec]) & 07) + '0';
                    break;
            }
            pputc(log, c);
        }
        if (  ( flag & LEFT ) && width > 0 )
            do
                pputc(log, ' ');
            while(--width);
    }
    return ccnt;
}
