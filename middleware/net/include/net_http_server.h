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
 * @file net_http_server.h
 * @brief Small HTTP/1.1 server on the mikroSDK network API (plain HTTP).
 * @details Routes map a method and a path to a handler. One request is served
 * at a time, from net_http_server_poll() in the main loop; every connection is
 * closed after its response ("Connection: close"). Requests are parsed as
 * untrusted input: everything must fit into the buffer given to the server,
 * else the client gets 413 / 431, and malformed requests get 400.
 *
 * @code
 * static void on_status( const net_http_server_request_t *req, net_http_server_conn_t *conn )
 * {
 *     net_http_server_respond( conn, 200, "application/json", "{\"ok\":true}", 11 );
 * }
 * static const net_http_route_t routes[] = { { "GET", "/api/status", on_status } };
 * static char buffer[ 1024 ];
 * static net_http_server_t server;
 *
 * net_http_server_start( &server, 80, routes, 1, buffer, sizeof( buffer ) );
 * for ( ; ; ) { net_poll(); net_http_server_poll( &server ); }
 * @endcode
 */

#ifndef _NET_HTTP_SERVER_H
#define _NET_HTTP_SERVER_H

#ifdef __cplusplus
extern "C"{
#endif

#include "net_api.h"

/*! Time a client gets to send its request, in ms. */
#ifndef NET_HTTP_SERVER_TIMEOUT_MS
#define NET_HTTP_SERVER_TIMEOUT_MS 3000
#endif

/*! @brief A parsed request. Strings point into the server buffer, valid during the handler. */
typedef struct
{
    const char *method;     /*!< "GET", "POST", ... */
    const char *path;       /*!< Path without the query, e.g. "/api/led". */
    const char *query;      /*!< Text after '?', "" if none (see net_http_server_param()). */
    const char *body;       /*!< Request body (Content-Length bytes), "" if none; '\0'-terminated. */
    uint32_t body_len;      /*!< Body length. */
    net_ip4_t peer;         /*!< Client address. */
} net_http_server_request_t;

/*! @brief Connection being answered; pass it to the respond functions. */
typedef struct
{
    net_socket_t sock;
    bool responded;
    net_err_t error;
} net_http_server_conn_t;

/*! @brief Request handler: must answer with net_http_server_respond() (or _begin / _send). */
typedef void ( *net_http_handler_t )( const net_http_server_request_t *req, net_http_server_conn_t *conn );

/*! @brief Route: method (NULL = any) and exact path. */
typedef struct
{
    const char *method;
    const char *path;
    net_http_handler_t handler;
} net_http_route_t;

/*! @brief Server state; the routes and the buffer must stay valid while it runs. */
typedef struct
{
    net_socket_t listener;
    const net_http_route_t *routes;
    uint8_t route_count;
    char *buffer;
    uint32_t buffer_size;
    uint32_t requests;      /*!< Requests answered (any status). */
} net_http_server_t;

/*!
 * @brief Listen on @p port.
 * @param buffer Holds one request (header and body); 1 KB is enough for small APIs.
 * @return NET_OK, NET_INVALID or the net_tcp_listen() error.
 */
net_err_t net_http_server_start( net_http_server_t *srv, uint16_t port, const net_http_route_t *routes,
                                 uint8_t route_count, char *buffer, uint32_t buffer_size );

/*!
 * @brief Serve one waiting connection, if any (returns at once otherwise).
 * Call it from the main loop next to net_poll().
 * @return true when a request was handled.
 */
bool net_http_server_poll( net_http_server_t *srv );

/*! @brief Stop listening. */
void net_http_server_stop( net_http_server_t *srv );

/*!
 * @brief Send a complete response (status line, Content-Type, Content-Length, body).
 * @param content_type NULL for none (e.g. with 204).
 * @return NET_OK or the send error.
 */
net_err_t net_http_server_respond( net_http_server_conn_t *conn, uint16_t status, const char *content_type,
                                   const void *body, uint32_t body_len );

/*!
 * @brief Start a response whose body follows in pieces with net_http_server_send();
 * exactly @p body_len bytes must follow.
 * @param extra_headers Additional header lines, each ending in "\r\n", or NULL.
 */
net_err_t net_http_server_respond_begin( net_http_server_conn_t *conn, uint16_t status, const char *content_type,
                                         const char *extra_headers, uint32_t body_len );

/*! @brief Send a piece of the body started with net_http_server_respond_begin(). */
net_err_t net_http_server_send( net_http_server_conn_t *conn, const void *data, uint32_t len );

/*!
 * @brief Get a parameter from a query ("a=1&b=x%20y") or a form body
 * (application/x-www-form-urlencoded), decoding "%XX" and '+'.
 * @return value length, or -1 when the parameter is missing or does not fit
 * into @p size (including the terminating '\0').
 */
int32_t net_http_server_param( const char *query, const char *name, char *value, uint32_t size );

#ifdef __cplusplus
}
#endif

#endif // _NET_HTTP_SERVER_H
// ------------------------------------------------------------------------- END
