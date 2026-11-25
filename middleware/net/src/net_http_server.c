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
 * @file net_http_server.c
 * @brief HTTP/1.1 server built only on net_api.h (see net_http_server.h).
 */

#include <string.h>

#include "net_http_server.h"

#define METHOD_MAX 8

static uint32_t remaining_ms( uint32_t start, uint32_t timeout_ms )
{
    uint32_t used = net_now_ms() - start;
    return ( used < timeout_ms ) ? ( timeout_ms - used ) : 0;
}

static char lower( char c )
{
    return ( c >= 'A' && c <= 'Z' ) ? ( char )( c - 'A' + 'a' ) : c;
}

static bool has_crlf( const char *s )
{
    return s && ( strchr( s, '\r' ) || strchr( s, '\n' ) );
}

static void u32_to_dec( uint32_t v, char *buf )
{
    char tmp[ 11 ];
    uint8_t n = 0;
    do
    {
        tmp[ n++ ] = ( char )( '0' + v % 10 );
        v /= 10;
    } while ( v );
    while ( n )
    {
        *buf++ = tmp[ --n ];
    }
    *buf = '\0';
}

static const char *reason( uint16_t status )
{
    switch ( status )
    {
        case 100: return "Continue";
        case 200: return "OK";
        case 201: return "Created";
        case 202: return "Accepted";
        case 204: return "No Content";
        case 301: return "Moved Permanently";
        case 302: return "Found";
        case 304: return "Not Modified";
        case 400: return "Bad Request";
        case 401: return "Unauthorized";
        case 403: return "Forbidden";
        case 404: return "Not Found";
        case 405: return "Method Not Allowed";
        case 408: return "Request Timeout";
        case 411: return "Length Required";
        case 413: return "Content Too Large";
        case 415: return "Unsupported Media Type";
        case 431: return "Request Header Fields Too Large";
        case 500: return "Internal Server Error";
        case 501: return "Not Implemented";
        case 503: return "Service Unavailable";
        default:  return "Status";
    }
}

static net_err_t send_str( net_http_server_conn_t *conn, const char *s )
{
    uint32_t len = ( uint32_t )strlen( s );
    int32_t sent = net_tcp_send( conn->sock, s, len, NET_HTTP_SERVER_TIMEOUT_MS );
    if ( sent < 0 )
    {
        return ( net_err_t )sent;
    }
    return ( ( uint32_t )sent == len ) ? NET_OK : NET_TIMEOUT;
}

/* ------------------------------------------------------------ Responses --- */

net_err_t net_http_server_respond_begin( net_http_server_conn_t *conn, uint16_t status, const char *content_type,
                                         const char *extra_headers, uint32_t body_len )
{
    if ( !conn || conn->responded || status < 100 || status > 999 || has_crlf( content_type ) )
    {
        return NET_INVALID;
    }
    conn->responded = true;
    char num[ 11 ];
    net_err_t err;
#define SEND( s ) do { err = send_str( conn, ( s ) ); if ( NET_OK != err ) { conn->error = err; return err; } } while ( 0 )
    u32_to_dec( status, num );
    SEND( "HTTP/1.1 " );
    SEND( num );
    SEND( " " );
    SEND( reason( status ) );
    SEND( "\r\n" );
    if ( content_type )
    {
        SEND( "Content-Type: " );
        SEND( content_type );
        SEND( "\r\n" );
    }
    u32_to_dec( body_len, num );
    SEND( "Content-Length: " );
    SEND( num );
    SEND( "\r\n" );
    if ( extra_headers )
    {
        SEND( extra_headers );
    }
    SEND( "Connection: close\r\n\r\n" );
#undef SEND
    return NET_OK;
}

net_err_t net_http_server_send( net_http_server_conn_t *conn, const void *data, uint32_t len )
{
    if ( !conn || !conn->responded || ( !data && len ) )
    {
        return NET_INVALID;
    }
    if ( !len )
    {
        return NET_OK;
    }
    int32_t sent = net_tcp_send( conn->sock, data, len, NET_HTTP_SERVER_TIMEOUT_MS );
    net_err_t err = ( sent < 0 ) ? ( net_err_t )sent : ( ( uint32_t )sent == len ? NET_OK : NET_TIMEOUT );
    if ( NET_OK != err )
    {
        conn->error = err;
    }
    return err;
}

net_err_t net_http_server_respond( net_http_server_conn_t *conn, uint16_t status, const char *content_type,
                                   const void *body, uint32_t body_len )
{
    net_err_t err = net_http_server_respond_begin( conn, status, content_type, NULL, body_len );
    return ( NET_OK == err ) ? net_http_server_send( conn, body, body_len ) : err;
}

static void respond_text( net_http_server_conn_t *conn, uint16_t status )
{
    const char *text = reason( status );
    net_http_server_respond( conn, status, "text/plain", text, ( uint32_t )strlen( text ) );
}

/* -------------------------------------------------------------- Server --- */

net_err_t net_http_server_start( net_http_server_t *srv, uint16_t port, const net_http_route_t *routes,
                                 uint8_t route_count, char *buffer, uint32_t buffer_size )
{
    if ( !srv || ( route_count && !routes ) || !buffer || ( buffer_size < 64 ) )
    {
        return NET_INVALID;
    }
    memset( srv, 0, sizeof( *srv ) );
    srv->routes = routes;
    srv->route_count = route_count;
    srv->buffer = buffer;
    srv->buffer_size = buffer_size;
    return net_tcp_listen( &srv->listener, port );
}

void net_http_server_stop( net_http_server_t *srv )
{
    if ( srv && NET_SOCKET_INVALID != srv->listener )
    {
        net_close( srv->listener );
        srv->listener = NET_SOCKET_INVALID;
    }
}

/* Header line value of @p name (case-insensitive), or NULL. */
static const char *header_value( const char *line, const char *end, const char *name )
{
    size_t n = strlen( name );
    if ( ( size_t )( end - line ) <= n || line[ n ] != ':' )
    {
        return NULL;
    }
    for ( size_t i = 0; i < n; i++ )
    {
        if ( lower( line[ i ] ) != name[ i ] )
        {
            return NULL;
        }
    }
    const char *v = line + n + 1;
    while ( v < end && ( *v == ' ' || *v == '\t' ) )
    {
        v++;
    }
    return v;
}

/* Read, check and route one request; returns the status sent by the server
 * itself (0 when a handler answered). */
static uint16_t handle( net_http_server_t *srv, net_http_server_conn_t *conn, uint32_t start )
{
    char *buf = srv->buffer;
    uint32_t cap = srv->buffer_size - 1;    /* room for a '\0' */
    uint32_t len = 0;
    uint32_t header_end = 0;

    /* Header block. */
    while ( !header_end )
    {
        if ( len >= cap )
        {
            return 431;
        }
        int32_t got = net_tcp_receive( conn->sock, buf + len, cap - len, remaining_ms( start, NET_HTTP_SERVER_TIMEOUT_MS ) );
        if ( got <= 0 )
        {
            return ( NET_TIMEOUT == got ) ? 408 : 1;   /* 1: client gone, nothing to send */
        }
        uint32_t from = ( len >= 3 ) ? len - 3 : 0;
        len += ( uint32_t )got;
        for ( uint32_t i = from; i + 3 < len; i++ )
        {
            if ( buf[ i ] == '\r' && buf[ i + 1 ] == '\n' && buf[ i + 2 ] == '\r' && buf[ i + 3 ] == '\n' )
            {
                header_end = i + 4;
                break;
            }
        }
    }

    /* Request line: METHOD SP target SP HTTP/1.x CRLF */
    char *line_end = memchr( buf, '\r', header_end );
    char *sp1 = memchr( buf, ' ', ( size_t )( line_end - buf ) );
    if ( !sp1 || sp1 == buf || ( sp1 - buf ) > METHOD_MAX )
    {
        return 400;
    }
    for ( char *p = buf; p < sp1; p++ )
    {
        if ( *p < 'A' || *p > 'Z' )
        {
            return 400;
        }
    }
    char *target = sp1 + 1;
    char *sp2 = memchr( target, ' ', ( size_t )( line_end - target ) );
    if ( !sp2 || target[ 0 ] != '/' || ( line_end - sp2 ) != 9 ||
         0 != memcmp( sp2 + 1, "HTTP/1.", 7 ) || ( sp2[ 8 ] != '0' && sp2[ 8 ] != '1' ) )
    {
        return 400;
    }
    for ( char *p = target; p < sp2; p++ )
    {
        if ( ( unsigned char )*p <= ' ' || *p == 0x7F )
        {
            return 400;
        }
    }

    /* Headers. */
    bool have_length = false, expect_continue = false;
    uint32_t content_length = 0;
    char *line = line_end + 2;
    while ( line < buf + header_end - 2 )
    {
        char *le = memchr( line, '\r', ( size_t )( buf + header_end - line ) );
        if ( !le || le == line )
        {
            break;
        }
        const char *v;
        if ( ( v = header_value( line, le, "content-length" ) ) )
        {
            if ( have_length || v >= le )
            {
                return 400;     /* duplicate or empty: ambiguous */
            }
            for ( ; v < le; v++ )
            {
                if ( *v < '0' || *v > '9' || content_length > 429496728u )
                {
                    return 400;
                }
                content_length = content_length * 10 + ( uint32_t )( *v - '0' );
            }
            have_length = true;
        }
        else if ( header_value( line, le, "transfer-encoding" ) )
        {
            return 501;         /* chunked request bodies are not supported */
        }
        else if ( ( v = header_value( line, le, "expect" ) ) )
        {
            expect_continue = ( ( le - v ) >= 12 ) && 0 == memcmp( v, "100-continue", 12 );
        }
        line = le + 2;
    }

    /* Body. */
    if ( content_length > cap - header_end )
    {
        return 413;
    }
    if ( expect_continue && content_length && ( len - header_end ) < content_length )
    {
        send_str( conn, "HTTP/1.1 100 Continue\r\n\r\n" );
    }
    while ( len - header_end < content_length )
    {
        int32_t got = net_tcp_receive( conn->sock, buf + len, header_end + content_length - len,
                                       remaining_ms( start, NET_HTTP_SERVER_TIMEOUT_MS ) );
        if ( got <= 0 )
        {
            return ( NET_TIMEOUT == got ) ? 408 : 1;
        }
        len += ( uint32_t )got;
    }

    /* Split into strings (the header block is not needed any more). */
    net_http_server_request_t req;
    *sp1 = '\0';
    *sp2 = '\0';
    req.method = buf;
    char *q = strchr( target, '?' );
    if ( q )
    {
        *q = '\0';
        req.query = q + 1;
    }
    else
    {
        req.query = "";
    }
    req.path = target;
    buf[ header_end + content_length ] = '\0';
    req.body = buf + header_end;
    req.body_len = content_length;
    net_tcp_peer( conn->sock, &req.peer, NULL );

    /* Route. */
    bool path_known = false;
    for ( uint8_t i = 0; i < srv->route_count; i++ )
    {
        const net_http_route_t *r = &srv->routes[ i ];
        if ( !r->path || 0 != strcmp( r->path, req.path ) )
        {
            continue;
        }
        path_known = true;
        if ( !r->method || 0 == strcmp( r->method, req.method ) )
        {
            r->handler( &req, conn );
            return conn->responded ? 0 : 500;
        }
    }
    return path_known ? 405 : 404;
}

bool net_http_server_poll( net_http_server_t *srv )
{
    net_http_server_conn_t conn;
    if ( !srv || NET_OK != net_tcp_accept( srv->listener, &conn.sock, 0 ) )
    {
        return false;
    }
    conn.responded = false;
    conn.error = NET_OK;
    uint16_t status = handle( srv, &conn, net_now_ms() );
    if ( status >= 100 && !conn.responded )
    {
        respond_text( &conn, status );
        /* Refused before the whole request was read: read and drop the rest for
         * a moment ("lingering close"), so the close is not a reset that could
         * make the client lose the response. */
        uint32_t start = net_now_ms();
        while ( ( 408 != status ) && ( net_now_ms() - start < 200 ) )
        {
            if ( net_tcp_receive( conn.sock, srv->buffer, srv->buffer_size, 50 ) <= 0 )
            {
                break;      /* nothing more for 50 ms, or the client closed */
            }
        }
    }
    net_close( conn.sock );
    srv->requests++;
    return true;
}

/* -------------------------------------------------------------- Params --- */

static int hex_value( char c )
{
    if ( c >= '0' && c <= '9' ) return c - '0';
    if ( c >= 'a' && c <= 'f' ) return c - 'a' + 10;
    if ( c >= 'A' && c <= 'F' ) return c - 'A' + 10;
    return -1;
}

int32_t net_http_server_param( const char *query, const char *name, char *value, uint32_t size )
{
    if ( !query || !name || !name[ 0 ] || !value || !size )
    {
        return -1;
    }
    size_t name_len = strlen( name );
    const char *p = query;
    while ( *p )
    {
        const char *end = strchr( p, '&' );
        if ( !end )
        {
            end = p + strlen( p );
        }
        if ( ( size_t )( end - p ) > name_len && 0 == memcmp( p, name, name_len ) && p[ name_len ] == '=' )
        {
            uint32_t n = 0;
            for ( const char *s = p + name_len + 1; s < end; s++ )
            {
                char c = *s;
                if ( c == '+' )
                {
                    c = ' ';
                }
                else if ( c == '%' && ( end - s ) > 2 && hex_value( s[ 1 ] ) >= 0 && hex_value( s[ 2 ] ) >= 0 )
                {
                    c = ( char )( hex_value( s[ 1 ] ) * 16 + hex_value( s[ 2 ] ) );
                    s += 2;
                    if ( c == '\0' )
                    {
                        return -1;      /* %00 would cut the string */
                    }
                }
                if ( n + 1 >= size )
                {
                    return -1;
                }
                value[ n++ ] = c;
            }
            value[ n ] = '\0';
            return ( int32_t )n;
        }
        p = *end ? end + 1 : end;
    }
    /* "name" without "=value" or missing. */
    return -1;
}

// ------------------------------------------------------------------------- END
