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
 * @file net_ftp.c
 * @brief FTP client (see net_ftp.h), built only on net_api.h.
 * @details Written from RFC 959 (FTP) and RFC 3659 (SIZE). Replies are parsed
 * as untrusted input: codes must be 100-599, line length and the number of
 * lines are bounded by the timeout, only the first line is kept (truncated).
 */

#include <string.h>

#include "net_ftp.h"

#define CMD_MAX 256                     /* longest command line, CRLF included */

/* ------------------------------------------------------------- Helpers --- */

static void close_data( net_ftp_t *f )
{
    if ( f->transfer )
    {
        net_close( f->data );
        f->data = NET_SOCKET_INVALID;
        f->transfer = false;
    }
}

static net_err_t lost( net_ftp_t *f, net_err_t why )
{
    close_data( f );
    if ( f->connected )
    {
        net_close( f->ctrl );
        f->ctrl = NET_SOCKET_INVALID;
        f->connected = false;
    }
    return why;
}

static uint32_t remaining( const net_ftp_t *f, uint32_t start )
{
    uint32_t used = net_now_ms() - start;
    return ( used < f->timeout_ms ) ? ( f->timeout_ms - used ) : 0;
}

static bool arg_ok( const char *s )
{
    return s && !strpbrk( s, "\r\n" );
}

static bool is_digit( char c )
{
    return c >= '0' && c <= '9';
}

/* Read one reply (single or multi-line) into f->status / f->reply. */
static net_err_t read_reply( net_ftp_t *f )
{
    uint32_t start = net_now_ms();
    char head[ 4 ];                     /* first 4 characters of the current line */
    uint32_t col = 0;                   /* position in the current line */
    uint32_t kept = 0;                  /* characters of the first line kept */
    bool first = true, multi = false;
    uint16_t rc = 0;

    f->reply[ 0 ] = '\0';
    for ( ; ; )
    {
        char c;
        uint32_t left = remaining( f, start );
        if ( 0 == left )
        {
            return lost( f, NET_TIMEOUT );
        }
        int32_t n = net_tcp_receive( f->ctrl, &c, 1, left );
        if ( n <= 0 )
        {
            return lost( f, ( 0 == n ) ? NET_CLOSED : ( net_err_t )n );
        }
        if ( '\n' != c )
        {
            if ( col < sizeof( head ) )
            {
                head[ col ] = c;
            }
            if ( first && '\r' != c && kept < sizeof( f->reply ) - 1 )
            {
                f->reply[ kept++ ] = c;
                f->reply[ kept ] = '\0';
            }
            col++;
            continue;
        }
        /* End of a line: head holds its first characters (col of them, '\r' included). */
        bool has_code = col >= 3 && is_digit( head[ 0 ] ) && is_digit( head[ 1 ] ) && is_digit( head[ 2 ] );
        char sep = ( col >= 4 ) ? head[ 3 ] : ' ';
        if ( first )
        {
            if ( !has_code || ( '-' != sep && ' ' != sep && '\r' != sep ) )
            {
                return lost( f, NET_ERROR );
            }
            rc = ( uint16_t )( ( head[ 0 ] - '0' ) * 100 + ( head[ 1 ] - '0' ) * 10 + ( head[ 2 ] - '0' ) );
            if ( rc < 100 || rc > 599 )
            {
                return lost( f, NET_ERROR );
            }
            multi = ( '-' == sep );
            first = false;
        }
        else if ( has_code && ' ' == sep &&
                  ( uint16_t )( ( head[ 0 ] - '0' ) * 100 + ( head[ 1 ] - '0' ) * 10 + ( head[ 2 ] - '0' ) ) == rc )
        {
            multi = false;              /* "123 text" ends a multi-line reply */
        }
        col = 0;
        if ( !multi )
        {
            f->status = rc;
            return NET_OK;
        }
    }
}

static net_err_t send_cmd( net_ftp_t *f, const char *cmd, const char *arg )
{
    char line[ CMD_MAX ];
    size_t len = strlen( cmd );
    size_t alen = arg ? strlen( arg ) : 0;
    if ( !f->connected )
    {
        return NET_CLOSED;
    }
    if ( ( arg && !arg_ok( arg ) ) || len + 1 + alen + 2 > sizeof( line ) )
    {
        return NET_INVALID;
    }
    memcpy( line, cmd, len );
    if ( arg )
    {
        line[ len++ ] = ' ';
        memcpy( line + len, arg, alen );
        len += alen;
    }
    line[ len++ ] = '\r';
    line[ len++ ] = '\n';
    int32_t n = net_tcp_send( f->ctrl, line, ( uint32_t )len, f->timeout_ms );
    if ( n != ( int32_t )len )
    {
        return lost( f, ( n < 0 ) ? ( net_err_t )n : NET_TIMEOUT );
    }
    return NET_OK;
}

/* Send a command, read the reply; NET_OK when its first digit is `want`. */
static net_err_t command( net_ftp_t *f, const char *cmd, const char *arg, uint8_t want )
{
    net_err_t err = send_cmd( f, cmd, arg );
    if ( NET_OK == err )
    {
        err = read_reply( f );
    }
    if ( NET_OK == err && ( f->status / 100 ) != want )
    {
        err = NET_REFUSED;
    }
    return err;
}

/* "227 Entering Passive Mode (h1,h2,h3,h4,p1,p2)": the port. 0 when malformed. */
static uint16_t pasv_port( const char *text )
{
    uint32_t v[ 6 ];
    const char *p = text + 3;           /* after the reply code */
    while ( *p && !is_digit( *p ) )
    {
        p++;
    }
    for ( uint8_t i = 0; i < 6; i++ )
    {
        if ( !is_digit( *p ) )
        {
            return 0;
        }
        v[ i ] = 0;
        for ( uint8_t d = 0; is_digit( *p ); d++, p++ )
        {
            if ( d >= 3 )
            {
                return 0;
            }
            v[ i ] = v[ i ] * 10 + ( uint32_t )( *p - '0' );
        }
        if ( v[ i ] > 255 || ( i < 5 && ',' != *p++ ) )
        {
            return 0;
        }
    }
    return ( uint16_t )( v[ 4 ] * 256 + v[ 5 ] );
}

/* ---------------------------------------------------------------- API --- */

net_err_t net_ftp_connect( net_ftp_t *f, const char *host, uint16_t port, uint32_t timeout_ms )
{
    if ( !f || !host || !timeout_ms )
    {
        return NET_INVALID;
    }
    memset( f, 0, sizeof( *f ) );
    f->ctrl = NET_SOCKET_INVALID;
    f->data = NET_SOCKET_INVALID;
    f->timeout_ms = timeout_ms;

    net_err_t err = net_resolve( host, &f->server, timeout_ms );
    if ( NET_OK != err )
    {
        return err;
    }
    err = net_tcp_connect( &f->ctrl, &f->server, port ? port : NET_FTP_PORT, timeout_ms );
    if ( NET_OK != err )
    {
        return err;
    }
    f->connected = true;
    do
    {
        err = read_reply( f );          /* 120 "ready in n minutes" comes before the 220 */
    } while ( NET_OK == err && 120 == f->status );
    if ( NET_OK == err && 2 != f->status / 100 )
    {
        return lost( f, NET_REFUSED );
    }
    return err;
}

net_err_t net_ftp_login( net_ftp_t *f, const char *user, const char *password )
{
    if ( !f || !arg_ok( user ) || !user[ 0 ] || ( password && !arg_ok( password ) ) )
    {
        return NET_INVALID;
    }
    net_err_t err = send_cmd( f, "USER", user );
    if ( NET_OK == err )
    {
        err = read_reply( f );
    }
    if ( NET_OK == err && 331 == f->status )
    {
        err = send_cmd( f, "PASS", password ? password : "" );
        if ( NET_OK == err )
        {
            err = read_reply( f );
        }
    }
    if ( NET_OK != err )
    {
        return err;
    }
    if ( 230 != f->status && 202 != f->status )     /* 202: no login needed */
    {
        return NET_REFUSED;
    }
    return command( f, "TYPE", "I", 2 );
}

net_err_t net_ftp_open( net_ftp_t *f, const char *path, net_ftp_mode_t mode )
{
    static const char *const verbs[] = { "RETR", "STOR", "APPE", "LIST", "NLST" };
    if ( !f || f->transfer || ( unsigned )mode > NET_FTP_NAMES || ( path && !arg_ok( path ) ) ||
         ( !path && mode < NET_FTP_LIST ) || ( path && !path[ 0 ] ) )
    {
        return NET_INVALID;
    }
    net_err_t err = command( f, "PASV", NULL, 2 );
    if ( NET_OK != err )
    {
        return err;
    }
    uint16_t port = ( 227 == f->status ) ? pasv_port( f->reply ) : 0;
    if ( 0 == port )
    {
        return lost( f, NET_ERROR );
    }
    /* The server's own address, not the one in the reply (see net_ftp.h). */
    err = net_tcp_connect( &f->data, &f->server, port, f->timeout_ms );
    if ( NET_OK != err )
    {
        return err;
    }
    f->transfer = true;
    f->data_done = false;
    f->replied = false;
    f->reading = ( NET_FTP_READ == mode || NET_FTP_LIST == mode || NET_FTP_NAMES == mode );

    err = send_cmd( f, verbs[ mode ], path );
    if ( NET_OK == err )
    {
        err = read_reply( f );
    }
    if ( NET_OK != err )
    {
        close_data( f );
        return err;
    }
    if ( 1 == f->status / 100 )
    {
        return NET_OK;                  /* 125 / 150: transfer starting */
    }
    if ( 2 == f->status / 100 )
    {
        f->replied = true;              /* already complete (e.g. an empty listing) */
        return NET_OK;
    }
    close_data( f );
    return NET_REFUSED;
}

int32_t net_ftp_read( net_ftp_t *f, void *buf, uint32_t size )
{
    if ( !f || !f->transfer || !f->reading || !buf || !size )
    {
        return NET_INVALID;
    }
    if ( f->data_done )
    {
        return 0;
    }
    int32_t n = net_tcp_receive( f->data, buf, size, f->timeout_ms );
    if ( NET_CLOSED == n )
    {
        f->data_done = true;
        return 0;
    }
    return n;
}

int32_t net_ftp_write( net_ftp_t *f, const void *data, uint32_t len )
{
    if ( !f || !f->transfer || f->reading || ( len && !data ) )
    {
        return NET_INVALID;
    }
    return len ? net_tcp_send( f->data, data, len, f->timeout_ms ) : 0;
}

net_err_t net_ftp_close( net_ftp_t *f )
{
    if ( !f || !f->transfer )
    {
        return NET_INVALID;
    }
    bool early = f->reading && !f->data_done;
    close_data( f );                    /* for an upload, the end of the file */
    if ( f->replied )
    {
        return NET_OK;
    }
    net_err_t err = read_reply( f );
    if ( NET_OK != err )
    {
        return err;
    }
    if ( 2 == f->status / 100 || ( early && ( 426 == f->status || 451 == f->status ) ) )
    {
        return NET_OK;
    }
    return NET_ERROR;
}

net_err_t net_ftp_cwd( net_ftp_t *f, const char *path )
{
    return ( f && arg_ok( path ) && path[ 0 ] ) ? command( f, "CWD", path, 2 ) : NET_INVALID;
}

net_err_t net_ftp_pwd( net_ftp_t *f, char *buf, uint32_t size )
{
    if ( !f || !buf || !size )
    {
        return NET_INVALID;
    }
    net_err_t err = command( f, "PWD", NULL, 2 );
    if ( NET_OK != err )
    {
        return err;
    }
    /* 257 "<path>" comment; a '"' in the path is doubled. */
    const char *p = strchr( f->reply, '"' );
    if ( 257 != f->status || !p )
    {
        return NET_ERROR;
    }
    uint32_t n = 0;
    for ( p++; *p; p++ )
    {
        if ( '"' == *p )
        {
            if ( '"' != p[ 1 ] )
            {
                break;
            }
            p++;
        }
        if ( n + 1 < size )
        {
            buf[ n++ ] = *p;
        }
    }
    buf[ n ] = '\0';
    return ( '"' == *p ) ? NET_OK : NET_ERROR;   /* no closing quote: truncated reply */
}

net_err_t net_ftp_mkdir( net_ftp_t *f, const char *path )
{
    return ( f && arg_ok( path ) && path[ 0 ] ) ? command( f, "MKD", path, 2 ) : NET_INVALID;
}

net_err_t net_ftp_rmdir( net_ftp_t *f, const char *path )
{
    return ( f && arg_ok( path ) && path[ 0 ] ) ? command( f, "RMD", path, 2 ) : NET_INVALID;
}

net_err_t net_ftp_delete( net_ftp_t *f, const char *path )
{
    return ( f && arg_ok( path ) && path[ 0 ] ) ? command( f, "DELE", path, 2 ) : NET_INVALID;
}

net_err_t net_ftp_rename( net_ftp_t *f, const char *from, const char *to )
{
    if ( !f || !arg_ok( from ) || !from[ 0 ] || !arg_ok( to ) || !to[ 0 ] )
    {
        return NET_INVALID;
    }
    net_err_t err = command( f, "RNFR", from, 3 );
    return ( NET_OK == err ) ? command( f, "RNTO", to, 2 ) : err;
}

net_err_t net_ftp_size( net_ftp_t *f, const char *path, uint32_t *size )
{
    if ( !f || !arg_ok( path ) || !path[ 0 ] || !size )
    {
        return NET_INVALID;
    }
    net_err_t err = command( f, "SIZE", path, 2 );
    if ( NET_OK != err )
    {
        return err;
    }
    const char *p = f->reply + 3;
    while ( ' ' == *p )
    {
        p++;
    }
    if ( 213 != f->status || !is_digit( *p ) )
    {
        return NET_ERROR;
    }
    uint32_t v = 0;
    for ( ; is_digit( *p ); p++ )
    {
        uint32_t d = ( uint32_t )( *p - '0' );
        if ( v > ( 0xFFFFFFFFu - d ) / 10u )
        {
            return NET_ERROR;           /* larger than 4 GB */
        }
        v = v * 10u + d;
    }
    *size = v;
    return NET_OK;
}

void net_ftp_quit( net_ftp_t *f )
{
    if ( !f )
    {
        return;
    }
    close_data( f );
    if ( f->connected )
    {
        if ( NET_OK == send_cmd( f, "QUIT", NULL ) )
        {
            read_reply( f );            /* 221; whatever comes, the connection ends */
        }
        lost( f, NET_CLOSED );
    }
}

// ------------------------------------------------------------------------- END
