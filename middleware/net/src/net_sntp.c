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
 * @file net_sntp.c
 * @brief SNTP client (RFC 4330, see net_sntp.h), built only on net_api.h.
 */

#include <string.h>

#include "net_sntp.h"

#define PACKET_SIZE         48u
#define NTP_UNIX_OFFSET     2208988800ul    /* seconds from 1900-01-01 to 1970-01-01 */
#define LI_ALARM            3u              /* leap indicator: server not synchronised */
#define MODE_CLIENT         3u
#define MODE_SERVER         4u
#define VERSION             4u

static struct
{
    bool synced;
    uint64_t unix_ms;       /* UTC at the moment below */
    uint32_t local_ms;      /* net_now_ms() at that moment */
} clock;

static uint32_t get_be32( const uint8_t *p )
{
    return ( ( uint32_t )p[ 0 ] << 24 ) | ( ( uint32_t )p[ 1 ] << 16 ) | ( ( uint32_t )p[ 2 ] << 8 ) | p[ 3 ];
}

static void put_be32( uint8_t *p, uint32_t v )
{
    p[ 0 ] = ( uint8_t )( v >> 24 );
    p[ 1 ] = ( uint8_t )( v >> 16 );
    p[ 2 ] = ( uint8_t )( v >> 8 );
    p[ 3 ] = ( uint8_t )v;
}

/* NTP timestamp (seconds since 1900, 32-bit fraction) to Unix milliseconds.
 * Seconds below 2^31 belong to the era starting in 2036 (RFC 4330, section 3). */
static uint64_t ntp_to_unix_ms( const uint8_t *p )
{
    uint64_t seconds = get_be32( p );
    uint32_t fraction = get_be32( p + 4 );
    if ( !( seconds & 0x80000000ul ) )
    {
        seconds += 0x100000000ull;
    }
    return ( seconds - NTP_UNIX_OFFSET ) * 1000u + ( ( ( uint64_t )fraction * 1000u ) >> 32 );
}

net_err_t net_sntp_sync( const char *server, uint32_t timeout_ms )
{
    if ( !server )
    {
        return NET_INVALID;
    }
    uint32_t start = net_now_ms();
    net_ip4_t ip;
    net_err_t err = net_resolve( server, &ip, timeout_ms );
    if ( NET_OK != err )
    {
        return err;
    }

    net_socket_t sock;
    err = net_udp_open( &sock, 0 );     /* random local port */
    if ( NET_OK != err )
    {
        return err;
    }

    /* Request: client mode, version 4; the transmit timestamp is a random nonce
     * the server must echo in the originate field (RFC 4330, section 5). */
    uint8_t packet[ PACKET_SIZE ];
    uint8_t nonce[ 8 ];
    memset( packet, 0, sizeof( packet ) );
    packet[ 0 ] = ( uint8_t )( ( VERSION << 3 ) | MODE_CLIENT );
    put_be32( nonce, net_random() );
    put_be32( nonce + 4, net_random() );
    memcpy( packet + 40, nonce, 8 );

    uint32_t sent_at = net_now_ms();
    err = net_udp_send_to( sock, &ip, NET_SNTP_PORT, packet, sizeof( packet ) );
    if ( NET_OK != err )
    {
        net_close( sock );
        return err;
    }

    err = NET_TIMEOUT;
    for ( ; ; )
    {
        uint32_t used = net_now_ms() - start;
        if ( used >= timeout_ms )
        {
            break;
        }
        net_ip4_t from;
        uint16_t port = 0;
        uint8_t reply[ PACKET_SIZE + 4 ];
        int32_t n = net_udp_receive_from( sock, reply, sizeof( reply ), &from, &port, timeout_ms - used );
        uint32_t received_at = net_now_ms();
        if ( n < 0 )
        {
            break;
        }
        /* Ignore anything that is not the answer to this request. */
        if ( n < ( int32_t )PACKET_SIZE || 0 != memcmp( &from, &ip, sizeof( ip ) ) || NET_SNTP_PORT != port ||
             ( reply[ 0 ] & 0x7u ) != MODE_SERVER || 0 != memcmp( reply + 24, nonce, 8 ) )
        {
            continue;
        }
        uint8_t version = ( uint8_t )( ( reply[ 0 ] >> 3 ) & 0x7u );
        uint8_t stratum = reply[ 1 ];
        if ( 0 == stratum )
        {
            err = NET_REFUSED;          /* kiss-of-death: the server asks us to go away */
            break;
        }
        if ( ( reply[ 0 ] >> 6 ) == LI_ALARM || stratum > 15u || version < 3u || version > 4u ||
             0 == get_be32( reply + 40 ) )
        {
            continue;                   /* unsynchronised or malformed server answer */
        }

        /* Server receive (T2) and transmit (T3) times; the local round trip
         * minus the server's processing time gives the network delay. */
        uint64_t t2 = ntp_to_unix_ms( reply + 32 );
        uint64_t t3 = ntp_to_unix_ms( reply + 40 );
        uint32_t round_trip = received_at - sent_at;
        uint64_t server_time = ( t3 >= t2 ) ? ( t3 - t2 ) : 0;
        uint32_t delay = ( round_trip > server_time ) ? ( uint32_t )( round_trip - server_time ) : 0;
        clock.unix_ms = t3 + delay / 2u;
        clock.local_ms = received_at;
        clock.synced = true;
        err = NET_OK;
        break;
    }
    net_close( sock );
    return err;
}

bool net_sntp_synced( void )
{
    return clock.synced;
}

net_err_t net_sntp_now( uint32_t *unix_seconds, uint16_t *milliseconds )
{
    if ( !clock.synced )
    {
        return NET_NOT_READY;
    }
    uint64_t now = clock.unix_ms + ( uint32_t )( net_now_ms() - clock.local_ms );
    if ( unix_seconds )
    {
        *unix_seconds = ( uint32_t )( now / 1000u );
    }
    if ( milliseconds )
    {
        *milliseconds = ( uint16_t )( now % 1000u );
    }
    return NET_OK;
}

// ------------------------------------------------------------------------- END
