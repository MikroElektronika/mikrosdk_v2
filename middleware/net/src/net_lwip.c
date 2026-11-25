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
 * @file net_lwip.c
 * @brief net_api.h implemented with lwIP (raw API, NO_SYS = 1).
 * @details lwIP calls back into this file (received data, connection events);
 * the blocking net_* functions wait for those events by calling net_poll()
 * until they happen or the timeout expires. Everything runs in the caller's
 * context, so no locking is needed.
 *
 * This file must not include mikroSDK headers: lwIP and mikroSDK both define
 * err_t (s8_t and int32_t).
 */

#include <string.h>

#include "net_api.h"

#include "lwip/init.h"
#include "lwip/netif.h"
#include "lwip/pbuf.h"
#include "lwip/timeouts.h"
#include "lwip/dhcp.h"
#include "lwip/dns.h"
#include "lwip/tcp.h"
#include "lwip/udp.h"
#include "lwip/etharp.h"
#include "netif/ethernet.h"

/* ----------------------------------------------------------- State --- */

typedef enum
{
    SOCK_FREE = 0,
    SOCK_TCP,
    SOCK_LISTEN,
    SOCK_UDP
} sock_type_t;

typedef enum
{
    TCP_IDLE = 0,
    TCP_CONNECTING,
    TCP_CONNECTED,
    TCP_PEER_CLOSED,   /* FIN received: remaining data can still be read */
    TCP_FAILED         /* reset, aborted or refused; pcb already freed by lwIP */
} tcp_state_t;

typedef struct
{
    struct pbuf *p;
    ip_addr_t addr;
    u16_t port;
} udp_dgram_t;

typedef struct
{
    sock_type_t type;
    tcp_state_t state;
    net_err_t failure;          /* reason when state == TCP_FAILED */
    struct tcp_pcb *tpcb;
    struct udp_pcb *upcb;
    struct pbuf *rx;            /* TCP: received data not read yet */
    net_socket_t pending[ NET_TCP_BACKLOG ];  /* listener: accepted sockets */
    uint8_t pending_count;
    udp_dgram_t dgram[ NET_UDP_QUEUE_LEN ];   /* UDP: received datagrams */
    uint8_t dgram_head;
    uint8_t dgram_count;
} net_sock_t;

static struct
{
    bool started;
    net_config_t cfg;
    struct netif netif;
    uint32_t last_link_poll;
    bool link;
    uint32_t rand_state;
    uint8_t frame[ NET_DRIVER_FRAME_MAX ];
    net_sock_t socks[ NET_MAX_SOCKETS ];
    /* DNS: one lookup at a time; a late answer to an old lookup is ignored. */
    uint32_t dns_id;
    bool dns_done;
    bool dns_found;
    ip_addr_t dns_result;
} net;

/* ------------------------------------------------- Port for lwIP --- */

u32_t sys_now( void )
{
    return net.cfg.now_ms ? net.cfg.now_ms() : 0;
}

uint32_t net_now_ms( void )
{
    return sys_now();
}

uint32_t net_port_rand( void )
{
    if ( net.cfg.random )
    {
        return net.cfg.random();
    }
    if ( 0 == net.rand_state )
    {
        /* Seed from the MAC address and the time of the first use. */
        uint32_t seed = sys_now() ^ 0x9E3779B9u;
        for ( uint8_t i = 0; i < 6; i++ )
        {
            seed = ( seed << 5 ) ^ ( seed >> 27 ) ^ net.cfg.mac[ i ];
        }
        net.rand_state = seed ? seed : 0x2545F491u;
    }
    /* xorshift32 */
    uint32_t x = net.rand_state;
    x ^= x << 13;
    x ^= x >> 17;
    x ^= x << 5;
    net.rand_state = x;
    return x;
}

void net_port_assert( const char *message, const char *file, int line )
{
    if ( net.cfg.assert_hook )
    {
        net.cfg.assert_hook( message, file, line );
    }
}

/* ----------------------------------------------------------- Helpers --- */

static void to_lwip( const net_ip4_t *in, ip_addr_t *out )
{
    IP_ADDR4( out, in->addr[ 0 ], in->addr[ 1 ], in->addr[ 2 ], in->addr[ 3 ] );
}

static void from_lwip( const ip_addr_t *in, net_ip4_t *out )
{
    const ip4_addr_t *a = ip_2_ip4( in );
    out->addr[ 0 ] = ip4_addr1( a );
    out->addr[ 1 ] = ip4_addr2( a );
    out->addr[ 2 ] = ip4_addr3( a );
    out->addr[ 3 ] = ip4_addr4( a );
}

static bool time_left( uint32_t start, uint32_t timeout_ms )
{
    return ( uint32_t )( sys_now() - start ) < timeout_ms;
}

static net_sock_t *sock_get( net_socket_t s, sock_type_t type )
{
    if ( !net.started || ( s < 0 ) || ( s >= NET_MAX_SOCKETS ) || ( net.socks[ s ].type != type ) )
    {
        return NULL;
    }
    return &net.socks[ s ];
}

static net_socket_t sock_alloc( sock_type_t type )
{
    for ( net_socket_t i = 0; i < NET_MAX_SOCKETS; i++ )
    {
        if ( SOCK_FREE == net.socks[ i ].type )
        {
            memset( &net.socks[ i ], 0, sizeof( net.socks[ i ] ) );
            net.socks[ i ].type = type;
            return i;
        }
    }
    return NET_SOCKET_INVALID;
}

static net_err_t from_lwip_err( err_t err )
{
    switch ( err )
    {
        case ERR_OK:    return NET_OK;
        case ERR_MEM:
        case ERR_BUF:   return NET_NO_MEMORY;
        case ERR_TIMEOUT: return NET_TIMEOUT;
        case ERR_RST:
        case ERR_ABRT:  return NET_RESET;
        case ERR_CLSD:  return NET_CLOSED;
        case ERR_RTE:
        case ERR_IF:    return NET_NOT_READY;
        case ERR_USE:   return NET_ERROR;
        case ERR_ARG:
        case ERR_VAL:   return NET_INVALID;
        default:        return NET_ERROR;
    }
}

/* ------------------------------------------------------ Interface --- */

static err_t netif_output( struct netif *netif, struct pbuf *p )
{
    (void)netif;
    if ( p->tot_len > sizeof( net.frame ) )
    {
        return ERR_BUF;
    }
    u16_t len = pbuf_copy_partial( p, net.frame, p->tot_len, 0 );
    return ( 0 == net.cfg.driver->send( net.cfg.driver->ctx, net.frame, len ) ) ? ERR_OK : ERR_IF;
}

static err_t netif_setup( struct netif *netif )
{
    netif->name[ 0 ] = 'e';
    netif->name[ 1 ] = 'n';
    netif->output = etharp_output;
    netif->linkoutput = netif_output;
    netif->mtu = 1500;
    netif->hwaddr_len = ETH_HWADDR_LEN;
    memcpy( netif->hwaddr, net.cfg.mac, ETH_HWADDR_LEN );
    netif->flags = NETIF_FLAG_BROADCAST | NETIF_FLAG_ETHARP | NETIF_FLAG_ETHERNET;
#if LWIP_NETIF_HOSTNAME
    netif->hostname = net.cfg.hostname;
#endif
    return ERR_OK;
}

void net_config_default( net_config_t *cfg )
{
    if ( cfg )
    {
        memset( cfg, 0, sizeof( *cfg ) );
        cfg->use_dhcp = true;
    }
}

net_err_t net_init( const net_config_t *cfg )
{
    if ( net.started || !cfg || !cfg->driver || !cfg->driver->send || !cfg->driver->receive || !cfg->now_ms )
    {
        return NET_INVALID;
    }
    memset( &net, 0, sizeof( net ) );
    net.cfg = *cfg;

    if ( net.cfg.driver->init && ( net.cfg.driver->init( net.cfg.driver->ctx, net.cfg.mac ) < 0 ) )
    {
        return NET_ERROR;
    }

    lwip_init();

    ip4_addr_t ip, mask, gw;
    if ( net.cfg.use_dhcp )
    {
        ip4_addr_set_zero( &ip );
        ip4_addr_set_zero( &mask );
        ip4_addr_set_zero( &gw );
    }
    else
    {
        IP4_ADDR( &ip, cfg->ip.addr[ 0 ], cfg->ip.addr[ 1 ], cfg->ip.addr[ 2 ], cfg->ip.addr[ 3 ] );
        IP4_ADDR( &mask, cfg->netmask.addr[ 0 ], cfg->netmask.addr[ 1 ], cfg->netmask.addr[ 2 ], cfg->netmask.addr[ 3 ] );
        IP4_ADDR( &gw, cfg->gateway.addr[ 0 ], cfg->gateway.addr[ 1 ], cfg->gateway.addr[ 2 ], cfg->gateway.addr[ 3 ] );
    }
    if ( !netif_add( &net.netif, &ip, &mask, &gw, NULL, netif_setup, ethernet_input ) )
    {
        return NET_ERROR;
    }
    netif_set_default( &net.netif );
    netif_set_up( &net.netif );

    if ( cfg->dns.addr[ 0 ] | cfg->dns.addr[ 1 ] | cfg->dns.addr[ 2 ] | cfg->dns.addr[ 3 ] )
    {
        ip_addr_t dns;
        to_lwip( &cfg->dns, &dns );
        dns_setserver( 0, &dns );
    }
    if ( net.cfg.use_dhcp && ( ERR_OK != dhcp_start( &net.netif ) ) )
    {
        return NET_NO_MEMORY;
    }

    net.started = true;
    net.last_link_poll = sys_now() - NET_LINK_POLL_MS;
    net_poll();
    return NET_OK;
}

void net_poll( void )
{
    if ( !net.started )
    {
        return;
    }
    const net_driver_t *drv = net.cfg.driver;

    if ( ( uint32_t )( sys_now() - net.last_link_poll ) >= NET_LINK_POLL_MS )
    {
        net.last_link_poll = sys_now();
        bool up = drv->link_up ? drv->link_up( drv->ctx ) : true;
        if ( up != net.link )
        {
            net.link = up;
            if ( up )
            {
                netif_set_link_up( &net.netif );    /* restarts DHCP, sends gratuitous ARP */
            }
            else
            {
                netif_set_link_down( &net.netif );
            }
        }
    }

    for ( uint8_t i = 0; i < NET_POLL_RX_BURST; i++ )
    {
        int32_t len = drv->receive( drv->ctx, net.frame, sizeof( net.frame ) );
        if ( len <= 0 )
        {
            break;
        }
        if ( len > ( int32_t )sizeof( net.frame ) )
        {
            continue;   /* driver bug: ignore */
        }
        struct pbuf *p = pbuf_alloc( PBUF_RAW, ( u16_t )len, PBUF_POOL );
        if ( !p )
        {
            continue;   /* out of buffers: drop, TCP retransmits */
        }
        pbuf_take( p, net.frame, ( u16_t )len );
        if ( ERR_OK != net.netif.input( p, &net.netif ) )
        {
            pbuf_free( p );
        }
    }

    sys_check_timeouts();
}

bool net_link_up( void )
{
    return net.started && net.link;
}

bool net_is_ready( void )
{
    if ( !net.started || !net.link || !netif_is_up( &net.netif ) || ip4_addr_isany_val( *netif_ip4_addr( &net.netif ) ) )
    {
        return false;
    }
    return !net.cfg.use_dhcp || dhcp_supplied_address( &net.netif );
}

net_err_t net_wait_ready( uint32_t timeout_ms )
{
    uint32_t start = sys_now();
    for ( ; ; )
    {
        net_poll();
        if ( net_is_ready() )
        {
            return NET_OK;
        }
        if ( !net.started || !time_left( start, timeout_ms ) )
        {
            return NET_TIMEOUT;
        }
    }
}

net_err_t net_get_address( net_ip4_t *ip, net_ip4_t *netmask, net_ip4_t *gateway )
{
    if ( !net_is_ready() )
    {
        return NET_NOT_READY;
    }
    ip_addr_t a;
    if ( ip )
    {
        ip_addr_copy_from_ip4( a, *netif_ip4_addr( &net.netif ) );
        from_lwip( &a, ip );
    }
    if ( netmask )
    {
        ip_addr_copy_from_ip4( a, *netif_ip4_netmask( &net.netif ) );
        from_lwip( &a, netmask );
    }
    if ( gateway )
    {
        ip_addr_copy_from_ip4( a, *netif_ip4_gw( &net.netif ) );
        from_lwip( &a, gateway );
    }
    return NET_OK;
}

/* ------------------------------------------------------------- DNS --- */

static void dns_found_cb( const char *name, const ip_addr_t *addr, void *arg )
{
    (void)name;
    if ( ( uint32_t )( uintptr_t )arg != net.dns_id )
    {
        return;     /* answer to a lookup that already timed out */
    }
    net.dns_done = true;
    net.dns_found = ( NULL != addr );
    if ( addr )
    {
        ip_addr_copy( net.dns_result, *addr );
    }
}

net_err_t net_resolve( const char *host, net_ip4_t *ip, uint32_t timeout_ms )
{
    if ( !host || !ip )
    {
        return NET_INVALID;
    }
    if ( NET_OK == net_ip4_from_string( host, ip ) )
    {
        return NET_OK;
    }
    if ( !net_is_ready() )
    {
        return NET_NOT_READY;
    }

    net.dns_id++;
    net.dns_done = false;
    net.dns_found = false;
    ip_addr_t addr;
    err_t err = dns_gethostbyname( host, &addr, dns_found_cb, ( void * )( uintptr_t )net.dns_id );
    if ( ERR_OK == err )
    {
        from_lwip( &addr, ip );
        return NET_OK;
    }
    if ( ERR_INPROGRESS != err )
    {
        return ( ERR_ARG == err ) ? NET_INVALID : NET_ERROR;
    }

    uint32_t start = sys_now();
    while ( !net.dns_done )
    {
        if ( !time_left( start, timeout_ms ) )
        {
            net.dns_id++;   /* ignore a late answer */
            return NET_TIMEOUT;
        }
        net_poll();
    }
    if ( !net.dns_found )
    {
        return NET_NOT_FOUND;
    }
    from_lwip( &net.dns_result, ip );
    return NET_OK;
}

/* ------------------------------------------------------------- TCP --- */

static err_t tcp_recv_cb( void *arg, struct tcp_pcb *tpcb, struct pbuf *p, err_t err )
{
    net_sock_t *s = ( net_sock_t * )arg;
    (void)tpcb;
    if ( !p )
    {
        s->state = TCP_PEER_CLOSED;
        return ERR_OK;
    }
    if ( ERR_OK != err )
    {
        pbuf_free( p );
        return ERR_OK;
    }
    /* Keep the data; the window is opened again (tcp_recved) when it is read. */
    if ( s->rx )
    {
        pbuf_cat( s->rx, p );
    }
    else
    {
        s->rx = p;
    }
    return ERR_OK;
}

static void tcp_err_cb( void *arg, err_t err )
{
    net_sock_t *s = ( net_sock_t * )arg;
    if ( !s )
    {
        return;
    }
    /* lwIP has already freed the pcb. */
    s->tpcb = NULL;
    s->failure = ( TCP_CONNECTING == s->state && ERR_RST == err ) ? NET_REFUSED : from_lwip_err( err );
    s->state = TCP_FAILED;
}

static err_t tcp_connected_cb( void *arg, struct tcp_pcb *tpcb, err_t err )
{
    net_sock_t *s = ( net_sock_t * )arg;
    (void)tpcb;
    (void)err;      /* always ERR_OK in lwIP 2.x; failures arrive through tcp_err_cb */
    s->state = TCP_CONNECTED;
    return ERR_OK;
}

static void tcp_attach( net_sock_t *s, struct tcp_pcb *pcb )
{
    s->tpcb = pcb;
    tcp_arg( pcb, s );
    tcp_recv( pcb, tcp_recv_cb );
    tcp_err( pcb, tcp_err_cb );
}

/* Detach a pcb from its socket and close it (abort if closing is not possible). */
static void tcp_release( net_sock_t *s )
{
    if ( s->tpcb )
    {
        struct tcp_pcb *pcb = s->tpcb;
        s->tpcb = NULL;
        tcp_arg( pcb, NULL );
        if ( LISTEN != pcb->state )
        {
            tcp_recv( pcb, NULL );
            tcp_err( pcb, NULL );
            tcp_sent( pcb, NULL );
        }
        else
        {
            tcp_accept( pcb, NULL );
        }
        if ( ERR_OK != tcp_close( pcb ) )
        {
            tcp_abort( pcb );
        }
    }
    if ( s->rx )
    {
        pbuf_free( s->rx );
        s->rx = NULL;
    }
}

net_err_t net_tcp_connect( net_socket_t *sock, const net_ip4_t *ip, uint16_t port, uint32_t timeout_ms )
{
    if ( !sock || !ip )
    {
        return NET_INVALID;
    }
    *sock = NET_SOCKET_INVALID;
    if ( !net_is_ready() )
    {
        return NET_NOT_READY;
    }
    net_socket_t id = sock_alloc( SOCK_TCP );
    if ( NET_SOCKET_INVALID == id )
    {
        return NET_NO_MEMORY;
    }
    net_sock_t *s = &net.socks[ id ];
    struct tcp_pcb *pcb = tcp_new_ip_type( IPADDR_TYPE_V4 );
    if ( !pcb )
    {
        s->type = SOCK_FREE;
        return NET_NO_MEMORY;
    }
    tcp_attach( s, pcb );
    s->state = TCP_CONNECTING;

    ip_addr_t addr;
    to_lwip( ip, &addr );
    err_t err = tcp_connect( pcb, &addr, port, tcp_connected_cb );
    if ( ERR_OK != err )
    {
        tcp_release( s );
        s->type = SOCK_FREE;
        return from_lwip_err( err );
    }

    uint32_t start = sys_now();
    while ( TCP_CONNECTING == s->state )
    {
        if ( !time_left( start, timeout_ms ) )
        {
            tcp_release( s );
            s->type = SOCK_FREE;
            return NET_TIMEOUT;
        }
        net_poll();
    }
    if ( TCP_CONNECTED != s->state )
    {
        net_err_t failure = ( TCP_FAILED == s->state ) ? s->failure : NET_CLOSED;
        tcp_release( s );
        s->type = SOCK_FREE;
        return failure;
    }
    *sock = id;
    return NET_OK;
}

int32_t net_tcp_send( net_socket_t sock, const void *data, uint32_t len, uint32_t timeout_ms )
{
    net_sock_t *s = sock_get( sock, SOCK_TCP );
    if ( !s || ( !data && len ) )
    {
        return NET_INVALID;
    }
    const uint8_t *src = ( const uint8_t * )data;
    uint32_t sent = 0;
    uint32_t start = sys_now();

    while ( sent < len )
    {
        if ( TCP_FAILED == s->state )
        {
            return sent ? ( int32_t )sent : s->failure;
        }
        if ( !s->tpcb || ( TCP_CONNECTED != s->state && TCP_PEER_CLOSED != s->state ) )
        {
            return sent ? ( int32_t )sent : NET_CLOSED;
        }
        u16_t room = tcp_sndbuf( s->tpcb );
        if ( room && ( tcp_sndqueuelen( s->tpcb ) < TCP_SND_QUEUELEN ) )
        {
            uint32_t chunk = len - sent;
            if ( chunk > room )
            {
                chunk = room;
            }
            err_t err = tcp_write( s->tpcb, src + sent, ( u16_t )chunk,
                                   TCP_WRITE_FLAG_COPY | ( ( sent + chunk < len ) ? TCP_WRITE_FLAG_MORE : 0 ) );
            if ( ERR_OK == err )
            {
                sent += chunk;
                tcp_output( s->tpcb );
                continue;
            }
            if ( ERR_MEM != err )
            {
                return sent ? ( int32_t )sent : from_lwip_err( err );
            }
        }
        /* Send buffer full: let ACKs come in. */
        tcp_output( s->tpcb );
        if ( !time_left( start, timeout_ms ) )
        {
            return sent ? ( int32_t )sent : NET_TIMEOUT;
        }
        net_poll();
    }
    return ( int32_t )sent;
}

int32_t net_tcp_receive( net_socket_t sock, void *buf, uint32_t size, uint32_t timeout_ms )
{
    net_sock_t *s = sock_get( sock, SOCK_TCP );
    if ( !s || !buf || !size )
    {
        return NET_INVALID;
    }
    uint32_t start = sys_now();
    for ( ; ; )
    {
        if ( s->rx )
        {
            uint32_t want = s->rx->tot_len;
            if ( want > size )
            {
                want = size;
            }
            if ( want > 0xFFFFu )
            {
                want = 0xFFFFu;
            }
            u16_t got = pbuf_copy_partial( s->rx, buf, ( u16_t )want, 0 );
            s->rx = pbuf_free_header( s->rx, got );
            if ( s->tpcb )
            {
                tcp_recved( s->tpcb, got );
            }
            return got;
        }
        if ( TCP_FAILED == s->state )
        {
            return s->failure;
        }
        if ( TCP_PEER_CLOSED == s->state || !s->tpcb )
        {
            return NET_CLOSED;
        }
        if ( !time_left( start, timeout_ms ) )
        {
            return NET_TIMEOUT;
        }
        net_poll();
    }
}

static err_t tcp_accept_cb( void *arg, struct tcp_pcb *newpcb, err_t err )
{
    net_sock_t *listener = ( net_sock_t * )arg;
    if ( ( ERR_OK != err ) || !newpcb || !listener || ( listener->pending_count >= NET_TCP_BACKLOG ) )
    {
        return ERR_MEM;     /* lwIP aborts the new connection */
    }
    net_socket_t id = sock_alloc( SOCK_TCP );
    if ( NET_SOCKET_INVALID == id )
    {
        return ERR_MEM;
    }
    net_sock_t *s = &net.socks[ id ];
    tcp_attach( s, newpcb );
    s->state = TCP_CONNECTED;
    listener->pending[ listener->pending_count++ ] = id;
    return ERR_OK;
}

net_err_t net_tcp_listen( net_socket_t *sock, uint16_t port )
{
    if ( !sock )
    {
        return NET_INVALID;
    }
    *sock = NET_SOCKET_INVALID;
    if ( !net.started )
    {
        return NET_NOT_READY;
    }
    net_socket_t id = sock_alloc( SOCK_LISTEN );
    if ( NET_SOCKET_INVALID == id )
    {
        return NET_NO_MEMORY;
    }
    net_sock_t *s = &net.socks[ id ];
    struct tcp_pcb *pcb = tcp_new_ip_type( IPADDR_TYPE_V4 );
    if ( !pcb )
    {
        s->type = SOCK_FREE;
        return NET_NO_MEMORY;
    }
    err_t err = tcp_bind( pcb, IP4_ADDR_ANY, port );
    if ( ERR_OK != err )
    {
        tcp_abort( pcb );
        s->type = SOCK_FREE;
        return from_lwip_err( err );
    }
    struct tcp_pcb *lpcb = tcp_listen_with_backlog( pcb, NET_TCP_BACKLOG );
    if ( !lpcb )
    {
        tcp_abort( pcb );
        s->type = SOCK_FREE;
        return NET_NO_MEMORY;
    }
    s->tpcb = lpcb;
    tcp_arg( lpcb, s );
    tcp_accept( lpcb, tcp_accept_cb );
    *sock = id;
    return NET_OK;
}

net_err_t net_tcp_accept( net_socket_t listener, net_socket_t *client, uint32_t timeout_ms )
{
    net_sock_t *s = sock_get( listener, SOCK_LISTEN );
    if ( !s || !client )
    {
        return NET_INVALID;
    }
    uint32_t start = sys_now();
    while ( 0 == s->pending_count )
    {
        if ( !time_left( start, timeout_ms ) )
        {
            return NET_TIMEOUT;
        }
        net_poll();
    }
    *client = s->pending[ 0 ];
    s->pending_count--;
    memmove( &s->pending[ 0 ], &s->pending[ 1 ], s->pending_count * sizeof( s->pending[ 0 ] ) );
    return NET_OK;
}

net_err_t net_tcp_peer( net_socket_t sock, net_ip4_t *ip, uint16_t *port )
{
    net_sock_t *s = sock_get( sock, SOCK_TCP );
    if ( !s || !s->tpcb )
    {
        return NET_INVALID;
    }
    if ( ip )
    {
        from_lwip( &s->tpcb->remote_ip, ip );
    }
    if ( port )
    {
        *port = s->tpcb->remote_port;
    }
    return NET_OK;
}

/* ------------------------------------------------------------- UDP --- */

static void udp_recv_cb( void *arg, struct udp_pcb *pcb, struct pbuf *p, const ip_addr_t *addr, u16_t port )
{
    net_sock_t *s = ( net_sock_t * )arg;
    (void)pcb;
    if ( !s || ( s->dgram_count >= NET_UDP_QUEUE_LEN ) )
    {
        pbuf_free( p );     /* queue full: drop, like a full socket buffer */
        return;
    }
    udp_dgram_t *d = &s->dgram[ ( s->dgram_head + s->dgram_count ) % NET_UDP_QUEUE_LEN ];
    d->p = p;
    ip_addr_copy( d->addr, *addr );
    d->port = port;
    s->dgram_count++;
}

net_err_t net_udp_open( net_socket_t *sock, uint16_t local_port )
{
    if ( !sock )
    {
        return NET_INVALID;
    }
    *sock = NET_SOCKET_INVALID;
    if ( !net.started )
    {
        return NET_NOT_READY;
    }
    net_socket_t id = sock_alloc( SOCK_UDP );
    if ( NET_SOCKET_INVALID == id )
    {
        return NET_NO_MEMORY;
    }
    net_sock_t *s = &net.socks[ id ];
    s->upcb = udp_new_ip_type( IPADDR_TYPE_V4 );
    if ( !s->upcb )
    {
        s->type = SOCK_FREE;
        return NET_NO_MEMORY;
    }
    err_t err = udp_bind( s->upcb, IP4_ADDR_ANY, local_port );
    if ( ERR_OK != err )
    {
        udp_remove( s->upcb );
        s->type = SOCK_FREE;
        return from_lwip_err( err );
    }
    udp_recv( s->upcb, udp_recv_cb, s );
    *sock = id;
    return NET_OK;
}

net_err_t net_udp_send_to( net_socket_t sock, const net_ip4_t *ip, uint16_t port, const void *data, uint16_t len )
{
    net_sock_t *s = sock_get( sock, SOCK_UDP );
    if ( !s || !ip || ( !data && len ) )
    {
        return NET_INVALID;
    }
    if ( !net_is_ready() )
    {
        return NET_NOT_READY;
    }
    struct pbuf *p = pbuf_alloc( PBUF_TRANSPORT, len, PBUF_RAM );
    if ( !p )
    {
        return NET_NO_MEMORY;
    }
    if ( len )
    {
        pbuf_take( p, data, len );
    }
    ip_addr_t addr;
    to_lwip( ip, &addr );
    err_t err = udp_sendto( s->upcb, p, &addr, port );
    pbuf_free( p );
    return from_lwip_err( err );
}

int32_t net_udp_receive_from( net_socket_t sock, void *buf, uint16_t size, net_ip4_t *ip, uint16_t *port,
                              uint32_t timeout_ms )
{
    net_sock_t *s = sock_get( sock, SOCK_UDP );
    if ( !s || ( !buf && size ) )
    {
        return NET_INVALID;
    }
    uint32_t start = sys_now();
    while ( 0 == s->dgram_count )
    {
        if ( !time_left( start, timeout_ms ) )
        {
            return NET_TIMEOUT;
        }
        net_poll();
    }
    udp_dgram_t *d = &s->dgram[ s->dgram_head ];
    u16_t got = size ? pbuf_copy_partial( d->p, buf, size, 0 ) : 0;
    if ( ip )
    {
        from_lwip( &d->addr, ip );
    }
    if ( port )
    {
        *port = d->port;
    }
    pbuf_free( d->p );
    d->p = NULL;
    s->dgram_head = ( uint8_t )( ( s->dgram_head + 1 ) % NET_UDP_QUEUE_LEN );
    s->dgram_count--;
    return got;
}

/* ------------------------------------------------------------ Close --- */

net_err_t net_close( net_socket_t sock )
{
    if ( !net.started || ( sock < 0 ) || ( sock >= NET_MAX_SOCKETS ) )
    {
        return NET_INVALID;
    }
    net_sock_t *s = &net.socks[ sock ];
    switch ( s->type )
    {
        case SOCK_TCP:
            tcp_release( s );
            break;
        case SOCK_LISTEN:
            /* Connections accepted but never taken are closed too. */
            for ( uint8_t i = 0; i < s->pending_count; i++ )
            {
                net_close( s->pending[ i ] );
            }
            tcp_release( s );
            break;
        case SOCK_UDP:
            while ( s->dgram_count )
            {
                pbuf_free( s->dgram[ s->dgram_head ].p );
                s->dgram_head = ( uint8_t )( ( s->dgram_head + 1 ) % NET_UDP_QUEUE_LEN );
                s->dgram_count--;
            }
            if ( s->upcb )
            {
                udp_remove( s->upcb );
            }
            break;
        default:
            return NET_INVALID;
    }
    memset( s, 0, sizeof( *s ) );
    return NET_OK;
}

// ------------------------------------------------------------------------- END
