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
 * @file net_api.h
 * @brief mikroSDK network API: IPv4 interface, DNS, TCP and UDP sockets.
 * @details Independent of the TCP/IP stack behind it (lwIP, see
 * thirdparty/ethernet/lwip), so applications never include stack headers.
 *
 * Runs without an RTOS: call net_poll() regularly (every few milliseconds) from
 * the main loop. Functions with a @p timeout_ms parameter keep calling
 * net_poll() themselves while they wait; a timeout of 0 returns at once.
 * None of the functions may be called from an interrupt.
 *
 * @code
 * net_config_t cfg;
 * net_config_default( &cfg );
 * cfg.driver = &my_driver;          // see net_driver.h
 * cfg.now_ms = my_millis;           // millisecond counter, e.g. from SysTick
 * memcpy( cfg.mac, my_mac, 6 );
 * net_init( &cfg );                 // DHCP by default
 * if ( NET_OK == net_wait_ready( 10000 ) ) { ... }
 * @endcode
 */

#ifndef _NET_API_H
#define _NET_API_H

#ifdef __cplusplus
extern "C"{
#endif

#include <stdint.h>
#include <stdbool.h>
#include "net_driver.h"

/*! Maximum number of sockets (TCP, UDP and listening sockets together). */
#ifndef NET_MAX_SOCKETS
#define NET_MAX_SOCKETS 4
#endif

/*! Datagrams queued per UDP socket before new ones are dropped. */
#ifndef NET_UDP_QUEUE_LEN
#define NET_UDP_QUEUE_LEN 4
#endif

/*! Connections a listening TCP socket keeps waiting for net_tcp_accept(). */
#ifndef NET_TCP_BACKLOG
#define NET_TCP_BACKLOG 2
#endif

/*! How often the link state is read from the driver, in milliseconds. */
#ifndef NET_LINK_POLL_MS
#define NET_LINK_POLL_MS 100
#endif

/*! Frames taken from the driver per net_poll() call. */
#ifndef NET_POLL_RX_BURST
#define NET_POLL_RX_BURST 8
#endif

/*!
 * @brief Result of the network functions. Functions returning a length return
 * it as a non-negative value and one of these (negative) on failure.
 */
typedef enum
{
    NET_OK = 0,              /*!< Success. */
    NET_ERROR = -1,          /*!< General or driver error. */
    NET_TIMEOUT = -2,        /*!< Nothing happened within the timeout. */
    NET_NO_MEMORY = -3,      /*!< Out of sockets or stack memory. */
    NET_NOT_READY = -4,      /*!< Not initialised, no link or no address yet. */
    NET_CLOSED = -5,         /*!< The peer closed the connection (no more data). */
    NET_RESET = -6,          /*!< The connection was reset or aborted. */
    NET_INVALID = -7,        /*!< Invalid argument or socket. */
    NET_NOT_FOUND = -8,      /*!< Host name not found. */
    NET_REFUSED = -9         /*!< Connection refused by the peer. */
} net_err_t;

/*! @brief IPv4 address in network order: 192.168.1.10 is { 192, 168, 1, 10 }. */
typedef struct
{
    uint8_t addr[ 4 ];
} net_ip4_t;

/*! @brief Socket handle; NET_SOCKET_INVALID if not open. */
typedef int8_t net_socket_t;
#define NET_SOCKET_INVALID ( ( net_socket_t )-1 )

/*! @brief Interface configuration, see net_config_default(). */
typedef struct
{
    const net_driver_t *driver;          /*!< Frame driver (mandatory). */
    uint32_t ( *now_ms )( void );        /*!< Millisecond counter (mandatory), may wrap. */
    uint8_t mac[ 6 ];                    /*!< MAC address of the interface. */
    bool use_dhcp;                       /*!< true: get the address by DHCP (default). */
    net_ip4_t ip;                        /*!< Static address (use_dhcp == false). */
    net_ip4_t netmask;                   /*!< Static netmask. */
    net_ip4_t gateway;                   /*!< Static gateway. */
    net_ip4_t dns;                       /*!< DNS server for static configuration
                                              (with DHCP: used only if 0.0.0.0 is not given). */
    const char *hostname;                /*!< Host name sent with DHCP, may be NULL. */
    uint32_t ( *random )( void );        /*!< Random numbers (e.g. hardware RNG). Strongly
                                              recommended: used for TCP sequence numbers and
                                              DNS/DHCP IDs. NULL uses a PRNG seeded from the
                                              MAC address and the time of the first use. */
    void ( *assert_hook )( const char *message, const char *file, int line ); /*!< Called
                                              when the stack detects an internal error. May be NULL. */
} net_config_t;

/*!
 * @brief Fill @p cfg with defaults: DHCP, no driver, no time source, MAC
 * 00:00:00:00:00:00 (set a real one).
 */
void net_config_default( net_config_t *cfg );

/*!
 * @brief Start the network interface.
 * @return NET_OK, NET_INVALID (missing driver or time source, already started)
 * or NET_ERROR (driver init failed).
 */
net_err_t net_init( const net_config_t *cfg );

/*!
 * @brief Process received frames, the link state and the stack's timers.
 * Call it every few milliseconds from the main loop.
 */
void net_poll( void );

/*! @brief Milliseconds of the configured time source (net_config_t.now_ms), 0 before net_init(). */
uint32_t net_now_ms( void );

/*! @brief true when the driver reports the link up. */
bool net_link_up( void );

/*! @brief true when the link is up and the interface has an IPv4 address. */
bool net_is_ready( void );

/*!
 * @brief Wait until net_is_ready() (link up and address assigned).
 * @return NET_OK or NET_TIMEOUT.
 */
net_err_t net_wait_ready( uint32_t timeout_ms );

/*!
 * @brief Current address, netmask and gateway (any pointer may be NULL).
 * @return NET_OK, or NET_NOT_READY without an address.
 */
net_err_t net_get_address( net_ip4_t *ip, net_ip4_t *netmask, net_ip4_t *gateway );

/*!
 * @brief Resolve @p host (a name or a dotted IPv4 address) with DNS.
 * @return NET_OK, NET_NOT_FOUND, NET_TIMEOUT or NET_NOT_READY.
 */
net_err_t net_resolve( const char *host, net_ip4_t *ip, uint32_t timeout_ms );

/*!
 * @brief Write @p ip as "a.b.c.d" into @p buf (at least 16 bytes).
 * @return @p buf.
 */
char *net_ip4_to_string( const net_ip4_t *ip, char *buf );

/*!
 * @brief Parse a dotted IPv4 address ("192.168.1.10").
 * @return NET_OK or NET_INVALID.
 */
net_err_t net_ip4_from_string( const char *str, net_ip4_t *ip );

/*! @brief Build an address from four numbers: net_ip4( 192, 168, 1, 10 ). */
net_ip4_t net_ip4( uint8_t a, uint8_t b, uint8_t c, uint8_t d );

/* ------------------------------------------------------------------ TCP --- */

/*!
 * @brief Connect to @p ip : @p port.
 * @param[out] sock Socket of the connection, valid when NET_OK is returned.
 * @return NET_OK, NET_TIMEOUT, NET_REFUSED, NET_RESET, NET_NO_MEMORY or NET_NOT_READY.
 */
net_err_t net_tcp_connect( net_socket_t *sock, const net_ip4_t *ip, uint16_t port, uint32_t timeout_ms );

/*!
 * @brief Send @p len bytes. Waits up to @p timeout_ms for room in the send buffer.
 * @return bytes queued for sending (may be fewer than @p len on timeout), or a
 * net_err_t (NET_TIMEOUT if nothing could be queued, NET_RESET, NET_CLOSED, ...).
 */
int32_t net_tcp_send( net_socket_t sock, const void *data, uint32_t len, uint32_t timeout_ms );

/*!
 * @brief Receive up to @p size bytes. Returns as soon as any data is available.
 * @return bytes received (> 0), NET_TIMEOUT, NET_CLOSED once the peer closed the
 * connection and all data was read, or NET_RESET.
 */
int32_t net_tcp_receive( net_socket_t sock, void *buf, uint32_t size, uint32_t timeout_ms );

/*!
 * @brief Listen for connections on @p port (all local addresses).
 * @return NET_OK, NET_NO_MEMORY or NET_ERROR (port in use).
 */
net_err_t net_tcp_listen( net_socket_t *sock, uint16_t port );

/*!
 * @brief Take the next connection from a listening socket.
 * @param[out] client Socket of the new connection.
 * @return NET_OK, NET_TIMEOUT or NET_INVALID.
 */
net_err_t net_tcp_accept( net_socket_t listener, net_socket_t *client, uint32_t timeout_ms );

/*!
 * @brief Peer address of a connected socket (any pointer may be NULL).
 * @return NET_OK or NET_INVALID.
 */
net_err_t net_tcp_peer( net_socket_t sock, net_ip4_t *ip, uint16_t *port );

/* ------------------------------------------------------------------ UDP --- */

/*!
 * @brief Open a UDP socket on @p local_port (0 = any free port).
 * @return NET_OK, NET_NO_MEMORY or NET_ERROR (port in use).
 */
net_err_t net_udp_open( net_socket_t *sock, uint16_t local_port );

/*!
 * @brief Send one datagram of @p len bytes to @p ip : @p port.
 * @return NET_OK, NET_NO_MEMORY, NET_NOT_READY or NET_ERROR.
 */
net_err_t net_udp_send_to( net_socket_t sock, const net_ip4_t *ip, uint16_t port, const void *data, uint16_t len );

/*!
 * @brief Receive one datagram; a datagram longer than @p size is truncated.
 * @param[out] ip, port Sender (may be NULL).
 * @return datagram length copied (>= 0), NET_TIMEOUT or NET_INVALID.
 */
int32_t net_udp_receive_from( net_socket_t sock, void *buf, uint16_t size, net_ip4_t *ip, uint16_t *port,
                              uint32_t timeout_ms );

/* ------------------------------------------------------------ Any socket -- */

/*!
 * @brief Close a socket of any kind and free it. Unread data is discarded.
 * @return NET_OK or NET_INVALID.
 */
net_err_t net_close( net_socket_t sock );

#ifdef __cplusplus
}
#endif

#endif // _NET_API_H
// ------------------------------------------------------------------------- END
