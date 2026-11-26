/****************************************************************************
**
** Copyright ( C ) ${COPYRIGHT_YEAR} MikroElektronika d.o.o.
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
 * @file net_common.c
 * @brief Stack independent helpers of net_api.h (IPv4 address text).
 */

#include "net_api.h"

net_ip4_t net_ip4( uint8_t a, uint8_t b, uint8_t c, uint8_t d )
{
    net_ip4_t ip;
    ip.addr[ 0 ] = a;
    ip.addr[ 1 ] = b;
    ip.addr[ 2 ] = c;
    ip.addr[ 3 ] = d;
    return ip;
}

char *net_ip4_to_string( const net_ip4_t *ip, char *buf )
{
    char *out = buf;
    for ( uint8_t i = 0; i < 4; i++ )
    {
        uint8_t v = ip->addr[ i ];
        if ( v >= 100 )
        {
            *out++ = ( char )( '0' + v / 100 );
        }
        if ( v >= 10 )
        {
            *out++ = ( char )( '0' + ( v / 10 ) % 10 );
        }
        *out++ = ( char )( '0' + v % 10 );
        if ( i < 3 )
        {
            *out++ = '.';
        }
    }
    *out = '\0';
    return buf;
}

net_err_t net_ip4_from_string( const char *str, net_ip4_t *ip )
{
    if ( !str || !ip )
    {
        return NET_INVALID;
    }
    net_ip4_t result;
    for ( uint8_t i = 0; i < 4; i++ )
    {
        uint16_t value = 0;
        uint8_t digits = 0;
        while ( ( *str >= '0' ) && ( *str <= '9' ) )
        {
            value = ( uint16_t )( value * 10 + ( uint16_t )( *str - '0' ) );
            if ( ( ++digits > 3 ) || ( value > 255 ) )
            {
                return NET_INVALID;
            }
            str++;
        }
        if ( 0 == digits )
        {
            return NET_INVALID;
        }
        result.addr[ i ] = ( uint8_t )value;
        if ( i < 3 )
        {
            if ( '.' != *str )
            {
                return NET_INVALID;
            }
            str++;
        }
    }
    if ( '\0' != *str )
    {
        return NET_INVALID;
    }
    *ip = result;
    return NET_OK;
}

// ------------------------------------------------------------------------- END
