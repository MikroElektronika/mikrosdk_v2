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
 * @file net_http.c
 * @brief HTTP/1.1 client built only on net_api.h (see net_http.h).
 * @details The response is parsed as untrusted input: the header block is
 * limited to NET_HTTP_HEADER_MAX bytes, numbers are checked for overflow and the
 * body never goes past the caller's buffer.
 */

#include <string.h>

#include "net_http.h"

typedef enum
{
    BODY_NONE,
    BODY_LENGTH,
    BODY_CHUNKED,
    BODY_CLOSE
} body_mode_t;

typedef enum
{
    CHUNK_SIZE,         /* hex size */
    CHUNK_EXT,          /* ";extension" up to CRLF */
    CHUNK_SIZE_LF,
    CHUNK_DATA,
    CHUNK_DATA_CR,
    CHUNK_DATA_LF,
    CHUNK_TRAILER,      /* trailer lines until an empty one */
    CHUNK_TRAILER_LF,
    CHUNK_DONE
} chunk_state_t;

typedef struct
{
    net_http_response_t *resp;
    body_mode_t mode;
    uint32_t remaining;         /* BODY_LENGTH: bytes left; CHUNKED: bytes left in chunk */
    chunk_state_t chunk;
    uint8_t size_digits;
    bool line_empty;            /* trailer: current line has no characters yet */
    bool complete;
} body_t;

static uint32_t remaining_ms( uint32_t start, uint32_t timeout_ms )
{
    uint32_t used = net_now_ms() - start;
    return ( used < timeout_ms ) ? ( timeout_ms - used ) : 0;
}

static bool has_crlf( const char *s )
{
    return s && ( strchr( s, '\r' ) || strchr( s, '\n' ) );
}

static net_err_t send_str( net_socket_t sock, const char *s, uint32_t start, uint32_t timeout_ms )
{
    uint32_t len = ( uint32_t )strlen( s );
    int32_t sent = net_tcp_send( sock, s, len, remaining_ms( start, timeout_ms ) );
    if ( sent < 0 )
    {
        return ( net_err_t )sent;
    }
    return ( ( uint32_t )sent == len ) ? NET_OK : NET_TIMEOUT;
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

static char lower( char c )
{
    return ( c >= 'A' && c <= 'Z' ) ? ( char )( c - 'A' + 'a' ) : c;
}

/* Case-insensitive match of a header name at the start of a line, followed by ':'. */
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

static bool contains_token( const char *v, const char *end, const char *token )
{
    size_t n = strlen( token );
    for ( ; v + n <= end; v++ )
    {
        size_t i = 0;
        while ( i < n && lower( v[ i ] ) == token[ i ] )
        {
            i++;
        }
        if ( i == n )
        {
            return true;
        }
    }
    return false;
}

static void store( body_t *b, const uint8_t *data, uint32_t len )
{
    net_http_response_t *r = b->resp;
    if ( !r->body )
    {
        r->truncated = r->truncated || ( len > 0 );
        return;
    }
    uint32_t room = ( r->body_size > r->body_len ) ? ( r->body_size - r->body_len ) : 0;
    uint32_t n = ( len < room ) ? len : room;
    memcpy( r->body + r->body_len, data, n );
    r->body_len += n;
    if ( r->body_len < r->body_size )
    {
        r->body[ r->body_len ] = '\0';   /* always a valid string, also after an error */
    }
    if ( n < len )
    {
        r->truncated = true;
    }
}

static int hex_value( uint8_t c )
{
    if ( c >= '0' && c <= '9' ) return c - '0';
    if ( c >= 'a' && c <= 'f' ) return c - 'a' + 10;
    if ( c >= 'A' && c <= 'F' ) return c - 'A' + 10;
    return -1;
}

/* Feed received body bytes. Returns false on a malformed chunked body. */
static bool body_feed( body_t *b, const uint8_t *data, uint32_t len )
{
    if ( BODY_LENGTH == b->mode )
    {
        uint32_t n = ( len < b->remaining ) ? len : b->remaining;
        store( b, data, n );
        b->remaining -= n;
        b->complete = ( 0 == b->remaining );
        return true;
    }
    if ( BODY_CLOSE == b->mode )
    {
        store( b, data, len );
        return true;
    }
    if ( BODY_CHUNKED != b->mode )
    {
        return true;
    }

    for ( uint32_t i = 0; i < len && !b->complete; i++ )
    {
        uint8_t c = data[ i ];
        switch ( b->chunk )
        {
            case CHUNK_SIZE:
            {
                int h = hex_value( c );
                if ( h >= 0 )
                {
                    if ( ( b->remaining > 0x0FFFFFFFu ) || ( ++b->size_digits > 8 ) )
                    {
                        return false;   /* chunk size too large */
                    }
                    b->remaining = ( b->remaining << 4 ) | ( uint32_t )h;
                }
                else if ( 0 == b->size_digits )
                {
                    return false;
                }
                else if ( ';' == c || ' ' == c || '\t' == c )
                {
                    b->chunk = CHUNK_EXT;
                }
                else if ( '\r' == c )
                {
                    b->chunk = CHUNK_SIZE_LF;
                }
                else
                {
                    return false;
                }
                break;
            }
            case CHUNK_EXT:
                if ( '\r' == c )
                {
                    b->chunk = CHUNK_SIZE_LF;
                }
                break;
            case CHUNK_SIZE_LF:
                if ( '\n' != c )
                {
                    return false;
                }
                if ( 0 == b->remaining )
                {
                    b->chunk = CHUNK_TRAILER;
                    b->line_empty = true;
                }
                else
                {
                    b->chunk = CHUNK_DATA;
                }
                break;
            case CHUNK_DATA:
            {
                uint32_t n = len - i;
                if ( n > b->remaining )
                {
                    n = b->remaining;
                }
                store( b, &data[ i ], n );
                b->remaining -= n;
                i += n - 1;
                if ( 0 == b->remaining )
                {
                    b->chunk = CHUNK_DATA_CR;
                }
                break;
            }
            case CHUNK_DATA_CR:
                if ( '\r' != c )
                {
                    return false;
                }
                b->chunk = CHUNK_DATA_LF;
                break;
            case CHUNK_DATA_LF:
                if ( '\n' != c )
                {
                    return false;
                }
                b->chunk = CHUNK_SIZE;
                b->size_digits = 0;
                b->remaining = 0;
                break;
            case CHUNK_TRAILER:
                if ( '\r' == c )
                {
                    b->chunk = CHUNK_TRAILER_LF;
                }
                else
                {
                    b->line_empty = false;
                }
                break;
            case CHUNK_TRAILER_LF:
                if ( '\n' != c )
                {
                    return false;
                }
                if ( b->line_empty )
                {
                    b->chunk = CHUNK_DONE;
                    b->complete = true;
                }
                else
                {
                    b->chunk = CHUNK_TRAILER;
                    b->line_empty = true;
                }
                break;
            default:
                break;
        }
    }
    return true;
}

static net_err_t send_request( net_socket_t sock, const net_http_request_t *req, uint32_t start, uint32_t timeout_ms )
{
    char num[ 12 ];
    net_err_t err;
#define SEND( s ) do { err = send_str( sock, ( s ), start, timeout_ms ); if ( NET_OK != err ) return err; } while ( 0 )
    SEND( req->method ? req->method : "GET" );
    SEND( " " );
    SEND( req->path ? req->path : "/" );
    SEND( " HTTP/1.1\r\nHost: " );
    SEND( req->host );
    if ( req->port && ( 80 != req->port ) )
    {
        u32_to_dec( req->port, num );
        SEND( ":" );
        SEND( num );
    }
    SEND( "\r\nConnection: close\r\nUser-Agent: mikroSDK\r\n" );
    if ( req->body || req->body_len )
    {
        if ( req->content_type )
        {
            SEND( "Content-Type: " );
            SEND( req->content_type );
            SEND( "\r\n" );
        }
        u32_to_dec( req->body_len, num );
        SEND( "Content-Length: " );
        SEND( num );
        SEND( "\r\n" );
    }
    if ( req->headers )
    {
        SEND( req->headers );
    }
    SEND( "\r\n" );
#undef SEND
    if ( req->body_len )
    {
        int32_t sent = net_tcp_send( sock, req->body, req->body_len, remaining_ms( start, timeout_ms ) );
        if ( sent < 0 )
        {
            return ( net_err_t )sent;
        }
        if ( ( uint32_t )sent != req->body_len )
        {
            return NET_TIMEOUT;
        }
    }
    return NET_OK;
}

/* Parse the header block hdr[0..len) (ends with the empty line). */
static net_err_t parse_header( const char *hdr, uint32_t len, const net_http_request_t *req, body_t *b )
{
    const char *end = hdr + len;
    const char *line_end = memchr( hdr, '\r', len );
    if ( !line_end || ( line_end - hdr ) < 12 || 0 != memcmp( hdr, "HTTP/1.", 7 ) || hdr[ 8 ] != ' ' )
    {
        return NET_ERROR;
    }
    uint16_t status = 0;
    for ( uint8_t i = 9; i < 12; i++ )
    {
        if ( hdr[ i ] < '0' || hdr[ i ] > '9' )
        {
            return NET_ERROR;
        }
        status = ( uint16_t )( status * 10 + ( uint16_t )( hdr[ i ] - '0' ) );
    }
    b->resp->status = status;

    bool chunked = false;
    bool have_length = false;
    uint32_t length = 0;
    const char *line = line_end + 2;
    while ( line < end )
    {
        const char *le = memchr( line, '\r', ( size_t )( end - line ) );
        if ( !le || le == line )
        {
            break;      /* empty line: end of the header block */
        }
        const char *v;
        if ( ( v = header_value( line, le, "content-length" ) ) )
        {
            if ( v >= le )
            {
                return NET_ERROR;
            }
            length = 0;
            for ( ; v < le && *v >= '0' && *v <= '9'; v++ )
            {
                if ( length > 429496728u )
                {
                    return NET_ERROR;   /* would overflow */
                }
                length = length * 10 + ( uint32_t )( *v - '0' );
            }
            have_length = true;
        }
        else if ( ( v = header_value( line, le, "transfer-encoding" ) ) )
        {
            chunked = contains_token( v, le, "chunked" );
        }
        line = le + 2;
    }

    bool no_body = ( req->method && 0 == strcmp( req->method, "HEAD" ) ) ||
                   ( status >= 100 && status < 200 ) || 204 == status || 304 == status;
    if ( no_body )
    {
        b->mode = BODY_NONE;
        b->complete = true;
    }
    else if ( chunked )
    {
        b->mode = BODY_CHUNKED;
        b->chunk = CHUNK_SIZE;
    }
    else if ( have_length )
    {
        b->mode = BODY_LENGTH;
        b->remaining = length;
        b->complete = ( 0 == length );
    }
    else
    {
        b->mode = BODY_CLOSE;
    }
    return NET_OK;
}

net_err_t net_http_request( const net_http_request_t *req, net_http_response_t *resp, uint32_t timeout_ms )
{
    if ( !req || !resp || !req->host || !req->host[ 0 ] || ( req->body_len && !req->body ) ||
         has_crlf( req->method ) || has_crlf( req->host ) || has_crlf( req->path ) || has_crlf( req->content_type ) ||
         ( req->path && req->path[ 0 ] != '/' ) )
    {
        return NET_INVALID;     /* also refuses header injection through method, host or path */
    }
    resp->status = 0;
    resp->body_len = 0;
    resp->truncated = false;
    if ( resp->body && resp->body_size )
    {
        resp->body[ 0 ] = '\0';
    }

    uint32_t start = net_now_ms();
    net_ip4_t ip;
    net_err_t err = net_resolve( req->host, &ip, timeout_ms );
    if ( NET_OK != err )
    {
        return err;
    }
    net_socket_t sock;
    err = net_tcp_connect( &sock, &ip, req->port ? req->port : 80, remaining_ms( start, timeout_ms ) );
    if ( NET_OK != err )
    {
        return err;
    }
    err = send_request( sock, req, start, timeout_ms );
    if ( NET_OK != err )
    {
        net_close( sock );
        return err;
    }

    /* Header block (static: keeps it off the stack of small MCUs; the client is not reentrant). */
    static char hdr[ NET_HTTP_HEADER_MAX ];
    uint32_t hdr_len = 0;
    uint32_t header_end = 0;
    while ( 0 == header_end )
    {
        if ( hdr_len >= sizeof( hdr ) )
        {
            net_close( sock );
            return NET_ERROR;   /* header block too large */
        }
        int32_t got = net_tcp_receive( sock, hdr + hdr_len, sizeof( hdr ) - hdr_len, remaining_ms( start, timeout_ms ) );
        if ( got < 0 )
        {
            net_close( sock );
            return ( NET_CLOSED == got ) ? NET_ERROR : ( net_err_t )got;
        }
        uint32_t from = ( hdr_len >= 3 ) ? hdr_len - 3 : 0;
        hdr_len += ( uint32_t )got;
        for ( uint32_t i = from; i + 3 < hdr_len; i++ )
        {
            if ( hdr[ i ] == '\r' && hdr[ i + 1 ] == '\n' && hdr[ i + 2 ] == '\r' && hdr[ i + 3 ] == '\n' )
            {
                header_end = i + 4;
                break;
            }
        }
    }

    body_t b;
    memset( &b, 0, sizeof( b ) );
    b.resp = resp;
    err = parse_header( hdr, header_end, req, &b );
    if ( NET_OK != err )
    {
        net_close( sock );
        return err;
    }

    /* Body bytes that arrived together with the header. */
    if ( !b.complete && !body_feed( &b, ( const uint8_t * )hdr + header_end, hdr_len - header_end ) )
    {
        net_close( sock );
        return NET_ERROR;
    }

    static uint8_t buf[ 256 ];
    while ( !b.complete )
    {
        int32_t got = net_tcp_receive( sock, buf, sizeof( buf ), remaining_ms( start, timeout_ms ) );
        if ( NET_CLOSED == got )
        {
            if ( BODY_CLOSE == b.mode )
            {
                b.complete = true;
                break;
            }
            net_close( sock );
            return NET_ERROR;   /* connection closed before the end of the body */
        }
        if ( got < 0 )
        {
            net_close( sock );
            return ( net_err_t )got;
        }
        if ( !body_feed( &b, buf, ( uint32_t )got ) )
        {
            net_close( sock );
            return NET_ERROR;
        }
    }
    net_close( sock );
    return NET_OK;
}

// ------------------------------------------------------------------------- END
