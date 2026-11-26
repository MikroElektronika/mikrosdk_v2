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
 * @file net_mqtt.c
 * @brief MQTT 3.1.1 client (see net_mqtt.h), built only on net_api.h.
 * @details Written from the OASIS MQTT 3.1.1 standard. Every packet from the
 * broker is parsed as untrusted input: lengths are checked against the packet
 * and the buffer, the remaining length is limited to 4 bytes.
 */

#include <string.h>

#include "net_mqtt.h"

/* Control packet types (high nibble of the first byte). */
#define T_CONNECT       1u
#define T_CONNACK       2u
#define T_PUBLISH       3u
#define T_PUBACK        4u
#define T_SUBSCRIBE     8u
#define T_SUBACK        9u
#define T_UNSUBSCRIBE   10u
#define T_UNSUBACK      11u
#define T_PINGREQ       12u
#define T_PINGRESP      13u
#define T_DISCONNECT    14u

#define SEND_TIMEOUT_MS 5000u
#define MAX_REMAINING   268435455ul     /* 4-byte remaining length */
#define SUBACK_FAILURE  0x80u

enum { RX_HEADER = 0, RX_LENGTH, RX_BODY };

/* ------------------------------------------------------------- Helpers --- */

static net_err_t lost( net_mqtt_t *m, net_err_t why )
{
    if ( m->connected )
    {
        net_close( m->sock );
        m->connected = false;
        m->sock = NET_SOCKET_INVALID;
    }
    return why;
}

static net_err_t send_raw( net_mqtt_t *m, const void *data, uint32_t len )
{
    if ( !m->connected )
    {
        return NET_CLOSED;
    }
    if ( 0 == len )
    {
        return NET_OK;
    }
    int32_t n = net_tcp_send( m->sock, data, len, SEND_TIMEOUT_MS );
    if ( n == ( int32_t )len )
    {
        m->last_tx = net_now_ms();
        return NET_OK;
    }
    return lost( m, ( n < 0 ) ? ( net_err_t )n : NET_TIMEOUT );
}

static net_err_t send_header( net_mqtt_t *m, uint8_t first, uint32_t remaining )
{
    uint8_t h[ 5 ];
    uint8_t n = 0;
    h[ n++ ] = first;
    do
    {
        uint8_t digit = ( uint8_t )( remaining % 128u );
        remaining /= 128u;
        if ( remaining )
        {
            digit |= 0x80u;
        }
        h[ n++ ] = digit;
    } while ( remaining && ( n < sizeof( h ) ) );
    return send_raw( m, h, n );
}

static net_err_t send_u16( net_mqtt_t *m, uint16_t v )
{
    uint8_t b[ 2 ] = { ( uint8_t )( v >> 8 ), ( uint8_t )v };
    return send_raw( m, b, 2 );
}

static net_err_t send_string( net_mqtt_t *m, const char *s )
{
    uint16_t len = ( uint16_t )strlen( s );
    net_err_t err = send_u16( m, len );
    return ( NET_OK == err ) ? send_raw( m, s, len ) : err;
}

static bool string_ok( const char *s )
{
    return s && ( strlen( s ) <= 0xFFFFu );
}

static uint16_t next_id( net_mqtt_t *m )
{
    if ( 0 == ++m->next_id )
    {
        m->next_id = 1;
    }
    return m->next_id;
}

static uint32_t remaining_ms( uint32_t start, uint32_t timeout_ms )
{
    uint32_t used = net_now_ms() - start;
    return ( used < timeout_ms ) ? ( timeout_ms - used ) : 0;
}

/* Wait for the acknowledgement of type `type` (and packet id `id`, 0 = any),
 * handling everything else the broker sends meanwhile. */
static net_err_t wait_ack( net_mqtt_t *m, uint8_t type, uint16_t id, uint32_t timeout_ms )
{
    uint32_t start = net_now_ms();
    for ( ; ; )
    {
        net_poll();
        net_err_t err = net_mqtt_poll( m );
        if ( NET_OK != err )
        {
            return err;
        }
        if ( m->ack_seen && ( m->ack_type == type ) && ( ( 0 == id ) || ( m->ack_id == id ) ) )
        {
            m->ack_seen = false;
            return NET_OK;
        }
        if ( 0 == remaining_ms( start, timeout_ms ) )
        {
            return NET_TIMEOUT;
        }
    }
}

/* ------------------------------------------------------------ Receive --- */

static void record_ack( net_mqtt_t *m, uint8_t type, uint16_t id, uint8_t rc )
{
    m->ack_type = type;
    m->ack_id = id;
    m->ack_code = rc;
    m->ack_seen = true;
}

/* A complete packet is in m->buf (rx_len bytes, of which min(rx_len, size) stored). */
static net_err_t dispatch( net_mqtt_t *m )
{
    uint8_t type = ( uint8_t )( m->rx_type >> 4 );
    uint8_t flags = ( uint8_t )( m->rx_type & 0x0Fu );
    uint32_t stored = ( m->rx_len < m->size ) ? m->rx_len : m->size;
    uint8_t *b = m->buf;

    switch ( type )
    {
        case T_CONNACK:
            if ( 2 != m->rx_len )
            {
                return lost( m, NET_ERROR );
            }
            record_ack( m, T_CONNACK, 0, b[ 1 ] );
            return NET_OK;

        case T_PUBACK:
        case T_UNSUBACK:
            if ( 2 != m->rx_len )
            {
                return lost( m, NET_ERROR );
            }
            record_ack( m, type, ( uint16_t )( ( b[ 0 ] << 8 ) | b[ 1 ] ), 0 );
            return NET_OK;

        case T_SUBACK:
            if ( m->rx_len < 3 )
            {
                return lost( m, NET_ERROR );
            }
            record_ack( m, T_SUBACK, ( uint16_t )( ( b[ 0 ] << 8 ) | b[ 1 ] ), b[ 2 ] );
            return NET_OK;

        case T_PINGRESP:
            if ( 0 != m->rx_len )
            {
                return lost( m, NET_ERROR );
            }
            m->ping_pending = false;
            return NET_OK;

        case T_PUBLISH:
        {
            uint8_t qos = ( uint8_t )( ( flags >> 1 ) & 0x3u );
            if ( qos > 1 || m->rx_len < 2 )
            {
                return lost( m, NET_ERROR );    /* QoS 2 never subscribed for, or malformed */
            }
            uint32_t topic_len = ( ( uint32_t )b[ 0 ] << 8 ) | b[ 1 ];
            uint32_t head = 2u + topic_len + ( qos ? 2u : 0u );
            if ( head > m->rx_len || 0 == topic_len )
            {
                return lost( m, NET_ERROR );
            }
            if ( head > stored )
            {
                m->dropped++;                   /* not even the topic fits: cannot acknowledge */
                return NET_OK;
            }
            uint16_t id = ( uint16_t )( qos ? ( ( b[ 2 + topic_len ] << 8 ) | b[ 3 + topic_len ] ) : 0 );
            if ( m->rx_len <= m->size )
            {
                /* Topic to the front, '\0'-terminated; the payload stays where it is. */
                memmove( b, b + 2, topic_len );
                b[ topic_len ] = '\0';
                if ( m->on_message )
                {
                    m->on_message( m->ctx, ( const char * )b, b + head, m->rx_len - head );
                }
            }
            else
            {
                m->dropped++;
            }
            if ( qos )
            {
                net_err_t err = send_header( m, T_PUBACK << 4, 2 );
                return ( NET_OK == err ) ? send_u16( m, id ) : err;
            }
            return NET_OK;
        }

        default:
            return lost( m, NET_ERROR );        /* nothing else may come from a broker */
    }
}

net_err_t net_mqtt_poll( net_mqtt_t *m )
{
    if ( !m || !m->connected )
    {
        return NET_CLOSED;
    }

    for ( ; ; )
    {
        uint8_t byte;
        int32_t n;
        if ( RX_BODY == m->rx_state )
        {
            uint32_t want = m->rx_len - m->rx_got;
            if ( m->rx_got < m->size )
            {
                uint32_t room = m->size - m->rx_got;
                n = net_tcp_receive( m->sock, m->buf + m->rx_got, ( want < room ) ? want : room, 0 );
            }
            else
            {
                uint8_t discard[ 64 ];
                n = net_tcp_receive( m->sock, discard, ( want < sizeof( discard ) ) ? want : sizeof( discard ), 0 );
            }
        }
        else
        {
            n = net_tcp_receive( m->sock, &byte, 1, 0 );
        }
        if ( NET_TIMEOUT == n )
        {
            break;                              /* nothing more waiting */
        }
        if ( n <= 0 )
        {
            return lost( m, ( n < 0 ) ? ( net_err_t )n : NET_CLOSED );
        }

        bool complete = false;
        switch ( m->rx_state )
        {
            case RX_HEADER:
                m->rx_type = byte;
                m->rx_len = 0;
                m->rx_multiplier = 1;
                m->rx_len_bytes = 0;
                m->rx_state = RX_LENGTH;
                break;
            case RX_LENGTH:
                m->rx_len += ( uint32_t )( byte & 0x7Fu ) * m->rx_multiplier;
                m->rx_multiplier *= 128u;
                if ( ++m->rx_len_bytes > 4 )
                {
                    return lost( m, NET_ERROR );
                }
                if ( !( byte & 0x80u ) )
                {
                    m->rx_got = 0;
                    m->rx_state = RX_BODY;
                    complete = ( 0 == m->rx_len );
                }
                break;
            default:
                m->rx_got += ( uint32_t )n;
                complete = ( m->rx_got == m->rx_len );
                break;
        }
        if ( complete )
        {
            m->rx_state = RX_HEADER;
            net_err_t err = dispatch( m );
            if ( NET_OK != err )
            {
                return err;
            }
        }
    }

    /* Keep-alive: ping when idle, give up when the ping is not answered. */
    if ( m->keepalive_s )
    {
        uint32_t period = ( uint32_t )m->keepalive_s * 1000u;
        uint32_t now = net_now_ms();
        if ( m->ping_pending && ( now - m->ping_sent ) >= period )
        {
            return lost( m, NET_TIMEOUT );
        }
        if ( !m->ping_pending && ( now - m->last_tx ) >= period )
        {
            net_err_t err = send_header( m, T_PINGREQ << 4, 0 );
            if ( NET_OK != err )
            {
                return err;
            }
            m->ping_pending = true;
            m->ping_sent = now;
        }
    }
    return m->connected ? NET_OK : NET_CLOSED;
}

/* ---------------------------------------------------------------- API --- */

void net_mqtt_cfg_setup( net_mqtt_cfg_t *cfg )
{
    memset( cfg, 0, sizeof( *cfg ) );
    cfg->port = 1883;
    cfg->keepalive_s = 60;
    cfg->clean_session = true;
}

net_err_t net_mqtt_connect( net_mqtt_t *m, const net_mqtt_cfg_t *cfg, uint8_t *buffer, uint32_t size,
                            net_mqtt_on_message_t on_message, void *ctx, uint32_t timeout_ms )
{
    if ( !m || !cfg || !cfg->host || !buffer || size < 64 || cfg->will_qos > 1 ||
         ( cfg->client_id && !string_ok( cfg->client_id ) ) || ( cfg->username && !string_ok( cfg->username ) ) ||
         ( cfg->password && ( !cfg->username || !string_ok( cfg->password ) ) ) ||
         ( cfg->will_topic && ( !string_ok( cfg->will_topic ) || ( cfg->will_len && !cfg->will_message ) ) ) )
    {
        return NET_INVALID;
    }
    memset( m, 0, sizeof( *m ) );
    m->sock = NET_SOCKET_INVALID;
    m->buf = buffer;
    m->size = size;
    m->on_message = on_message;
    m->ctx = ctx;
    m->keepalive_s = cfg->keepalive_s;
    m->next_id = ( uint16_t )net_random();

    uint32_t start = net_now_ms();
    net_ip4_t ip;
    net_err_t err = net_resolve( cfg->host, &ip, timeout_ms );
    if ( NET_OK != err )
    {
        return err;
    }
    err = net_tcp_connect( &m->sock, &ip, cfg->port ? cfg->port : 1883, remaining_ms( start, timeout_ms ) );
    if ( NET_OK != err )
    {
        return err;
    }
    m->connected = true;

    char generated[ 18 ];
    const char *client_id = cfg->client_id;
    if ( !client_id )
    {
        static const char hex[] = "0123456789abcdef";
        uint32_t r = net_random();
        memcpy( generated, "mikrosdk-", 9 );
        for ( uint8_t i = 0; i < 8; i++ )
        {
            generated[ 9 + i ] = hex[ ( r >> ( 28 - 4 * i ) ) & 0xFu ];
        }
        generated[ 17 ] = '\0';
        client_id = generated;
    }

    uint8_t flags = cfg->clean_session ? 0x02u : 0x00u;
    uint32_t remaining = 10u + 2u + ( uint32_t )strlen( client_id );
    if ( cfg->will_topic )
    {
        flags |= ( uint8_t )( 0x04u | ( cfg->will_qos << 3 ) | ( cfg->will_retain ? 0x20u : 0u ) );
        remaining += 2u + ( uint32_t )strlen( cfg->will_topic ) + 2u + cfg->will_len;
    }
    if ( cfg->username )
    {
        flags |= 0x80u;
        remaining += 2u + ( uint32_t )strlen( cfg->username );
    }
    if ( cfg->password )
    {
        flags |= 0x40u;
        remaining += 2u + ( uint32_t )strlen( cfg->password );
    }

    static const uint8_t protocol[] = { 0x00, 0x04, 'M', 'Q', 'T', 'T', 0x04 };
#define TRY( call ) do { err = ( call ); if ( NET_OK != err ) return err; } while ( 0 )
    TRY( send_header( m, T_CONNECT << 4, remaining ) );
    TRY( send_raw( m, protocol, sizeof( protocol ) ) );
    TRY( send_raw( m, &flags, 1 ) );
    TRY( send_u16( m, cfg->keepalive_s ) );
    TRY( send_string( m, client_id ) );
    if ( cfg->will_topic )
    {
        TRY( send_string( m, cfg->will_topic ) );
        TRY( send_u16( m, cfg->will_len ) );
        TRY( send_raw( m, cfg->will_message, cfg->will_len ) );
    }
    if ( cfg->username )
    {
        TRY( send_string( m, cfg->username ) );
    }
    if ( cfg->password )
    {
        TRY( send_string( m, cfg->password ) );
    }
#undef TRY

    err = wait_ack( m, T_CONNACK, 0, remaining_ms( start, timeout_ms ) );
    if ( NET_OK != err )
    {
        return lost( m, err );
    }
    if ( 0 != m->ack_code )
    {
        m->connack_code = m->ack_code;
        return lost( m, NET_REFUSED );
    }
    return NET_OK;
}

net_err_t net_mqtt_publish( net_mqtt_t *m, const char *topic, const void *payload, uint32_t len, uint8_t qos,
                            bool retain, uint32_t timeout_ms )
{
    if ( !m || !string_ok( topic ) || !topic[ 0 ] || strpbrk( topic, "+#" ) || qos > 1 || ( len && !payload ) )
    {
        return NET_INVALID;
    }
    uint32_t topic_len = ( uint32_t )strlen( topic );
    uint32_t remaining = 2u + topic_len + ( qos ? 2u : 0u ) + len;
    if ( remaining > MAX_REMAINING || remaining < len )
    {
        return NET_INVALID;
    }
    if ( !m->connected )
    {
        return NET_CLOSED;
    }
    uint16_t id = qos ? next_id( m ) : 0;
    m->ack_seen = false;
    net_err_t err = send_header( m, ( uint8_t )( ( T_PUBLISH << 4 ) | ( qos << 1 ) | ( retain ? 1u : 0u ) ), remaining );
    if ( NET_OK == err )
    {
        err = send_string( m, topic );
    }
    if ( NET_OK == err && qos )
    {
        err = send_u16( m, id );
    }
    if ( NET_OK == err )
    {
        err = send_raw( m, payload, len );
    }
    if ( NET_OK != err || 0 == qos )
    {
        return err;
    }
    return wait_ack( m, T_PUBACK, id, timeout_ms );
}

static net_err_t subscription( net_mqtt_t *m, uint8_t type, const char *filter, uint8_t qos, uint32_t timeout_ms )
{
    if ( !m || !string_ok( filter ) || !filter[ 0 ] || qos > 1 )
    {
        return NET_INVALID;
    }
    if ( !m->connected )
    {
        return NET_CLOSED;
    }
    bool subscribe = ( T_SUBSCRIBE == type );
    uint16_t id = next_id( m );
    m->ack_seen = false;
    net_err_t err = send_header( m, ( uint8_t )( ( type << 4 ) | 0x02u ),
                                 2u + 2u + ( uint32_t )strlen( filter ) + ( subscribe ? 1u : 0u ) );
    if ( NET_OK == err )
    {
        err = send_u16( m, id );
    }
    if ( NET_OK == err )
    {
        err = send_string( m, filter );
    }
    if ( NET_OK == err && subscribe )
    {
        err = send_raw( m, &qos, 1 );
    }
    if ( NET_OK != err )
    {
        return err;
    }
    err = wait_ack( m, subscribe ? T_SUBACK : T_UNSUBACK, id, timeout_ms );
    if ( NET_OK == err && subscribe && SUBACK_FAILURE == m->ack_code )
    {
        return NET_REFUSED;
    }
    return err;
}

net_err_t net_mqtt_subscribe( net_mqtt_t *m, const char *filter, uint8_t qos, uint32_t timeout_ms )
{
    return subscription( m, T_SUBSCRIBE, filter, qos, timeout_ms );
}

net_err_t net_mqtt_unsubscribe( net_mqtt_t *m, const char *filter, uint32_t timeout_ms )
{
    return subscription( m, T_UNSUBSCRIBE, filter, 0, timeout_ms );
}

bool net_mqtt_connected( const net_mqtt_t *m )
{
    return m && m->connected;
}

void net_mqtt_disconnect( net_mqtt_t *m )
{
    if ( m && m->connected )
    {
        send_header( m, T_DISCONNECT << 4, 0 );
        lost( m, NET_CLOSED );
    }
}

// ------------------------------------------------------------------------- END
