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
 * @file net_mdns.c
 * @brief net_mdns.h on the lwIP mDNS responder (apps/mdns).
 */

#include <string.h>

#include "net_mdns.h"

#include "lwip/netif.h"
#include "lwip/apps/mdns.h"

#if LWIP_MDNS_RESPONDER

#define TXT_SIZE 128

static struct
{
    bool initialised;
    bool started;
    int8_t state;                           /* NET_OK, NET_NOT_READY or NET_REFUSED */
    bool used[ MDNS_MAX_SERVICES ];
    char txt[ MDNS_MAX_SERVICES ][ TXT_SIZE ];
} mdns;

static void on_result( struct netif *netif, u8_t result, s8_t slot )
{
    ( void )netif;
    ( void )slot;                           /* host name (-1) and services alike */
    mdns.state = ( int8_t )( ( MDNS_PROBING_SUCCESSFUL == result ) ? NET_OK : NET_REFUSED );
}

static void add_txt( struct mdns_service *service, void *userdata )
{
    const char *item = userdata;
    while ( *item )
    {
        const char *end = strchr( item, ';' );
        size_t len = end ? ( size_t )( end - item ) : strlen( item );
        if ( len )
        {
            mdns_resp_add_service_txtitem( service, item, ( u8_t )len );
        }
        item += len + ( end ? 1u : 0u );
    }
}

static bool label_ok( const char *s, bool hostname )
{
    size_t len = s ? strlen( s ) : 0;
    if ( 0 == len || len > NET_MDNS_LABEL_MAX )
    {
        return false;
    }
    for ( size_t i = 0; hostname && i < len; i++ )
    {
        char c = s[ i ];
        if ( !( ( c >= 'a' && c <= 'z' ) || ( c >= 'A' && c <= 'Z' ) || ( c >= '0' && c <= '9' ) || '-' == c ) )
        {
            return false;
        }
    }
    return true;
}

/* TXT items: each 1..63 bytes; the whole record must fit lwIP's 256-byte domain buffer. */
static bool txt_ok( const char *txt )
{
    if ( !txt )
    {
        return true;
    }
    size_t total = strlen( txt );
    if ( total >= TXT_SIZE )
    {
        return false;
    }
    size_t item = 0;
    for ( size_t i = 0; i <= total; i++ )
    {
        if ( ';' == txt[ i ] || '\0' == txt[ i ] )
        {
            item = 0;
        }
        else if ( ++item > NET_MDNS_LABEL_MAX )
        {
            return false;
        }
    }
    return true;
}

net_err_t net_mdns_start( const char *hostname )
{
    struct netif *netif = netif_default;
    if ( !netif )
    {
        return NET_NOT_READY;
    }
#if LWIP_NETIF_HOSTNAME
    if ( !hostname )
    {
        hostname = netif->hostname;
    }
#endif
    if ( mdns.started || !label_ok( hostname, true ) )
    {
        return NET_INVALID;
    }
    if ( !mdns.initialised )
    {
        mdns_resp_init();
        mdns_resp_register_name_result_cb( on_result );
        mdns.initialised = true;
    }
    mdns.state = NET_NOT_READY;
    err_t err = mdns_resp_add_netif( netif, hostname );
    if ( ERR_OK != err )
    {
        return ( ERR_MEM == err ) ? NET_NO_MEMORY : NET_ERROR;
    }
    mdns.started = true;
    return NET_OK;
}

net_err_t net_mdns_rename( const char *hostname )
{
    if ( !mdns.started )
    {
        return NET_NOT_READY;
    }
    if ( !label_ok( hostname, true ) )
    {
        return NET_INVALID;
    }
    mdns.state = NET_NOT_READY;
    return ( ERR_OK == mdns_resp_rename_netif( netif_default, hostname ) ) ? NET_OK : NET_ERROR;
}

net_err_t net_mdns_add_service( const char *instance, const char *service, net_mdns_proto_t proto, uint16_t port,
                                const char *txt, uint8_t *id )
{
    if ( !mdns.started )
    {
        return NET_NOT_READY;
    }
    if ( !label_ok( instance, false ) || !label_ok( service, false ) || '_' != service[ 0 ] ||
         ( NET_MDNS_TCP != proto && NET_MDNS_UDP != proto ) || !txt_ok( txt ) )
    {
        return NET_INVALID;
    }
    /* The TXT copy goes to the first free slot; lwIP takes its own first free slot and
     * frees the same slots as we do, so the two stay in step (checked below). */
    uint8_t slot = 0;
    while ( slot < MDNS_MAX_SERVICES && mdns.used[ slot ] )
    {
        slot++;
    }
    if ( slot >= MDNS_MAX_SERVICES )
    {
        return NET_NO_MEMORY;
    }
    char *copy = mdns.txt[ slot ];
    strcpy( copy, txt ? txt : "" );
    s8_t r = mdns_resp_add_service( netif_default, instance, service,
                                    ( NET_MDNS_TCP == proto ) ? DNSSD_PROTO_TCP : DNSSD_PROTO_UDP, port,
                                    add_txt, copy );
    if ( r < 0 )
    {
        return ( ERR_MEM == r ) ? NET_NO_MEMORY : NET_ERROR;
    }
    if ( r != ( s8_t )slot )
    {
        mdns_resp_del_service( netif_default, ( u8_t )r );
        return NET_ERROR;
    }
    mdns.used[ slot ] = true;
    if ( id )
    {
        *id = slot;
    }
    mdns.state = NET_NOT_READY;             /* lwIP probes again with the new service */
    return NET_OK;
}

net_err_t net_mdns_status( void )
{
    return mdns.started ? ( net_err_t )mdns.state : NET_NOT_READY;
}

net_err_t net_mdns_remove_service( uint8_t id )
{
    if ( !mdns.started || id >= MDNS_MAX_SERVICES || !mdns.used[ id ] )
    {
        return NET_INVALID;
    }
    if ( ERR_OK != mdns_resp_del_service( netif_default, id ) )
    {
        return NET_ERROR;
    }
    mdns.used[ id ] = false;
    return NET_OK;
}

#else   /* mDNS left out (NET_LWIP_MDNS=0) */

net_err_t net_mdns_start( const char *hostname )
{
    ( void )hostname;
    return NET_ERROR;
}

net_err_t net_mdns_rename( const char *hostname )
{
    ( void )hostname;
    return NET_ERROR;
}

net_err_t net_mdns_add_service( const char *instance, const char *service, net_mdns_proto_t proto, uint16_t port,
                                const char *txt, uint8_t *id )
{
    ( void )instance;
    ( void )service;
    ( void )proto;
    ( void )port;
    ( void )txt;
    ( void )id;
    return NET_ERROR;
}

net_err_t net_mdns_remove_service( uint8_t id )
{
    ( void )id;
    return NET_ERROR;
}

net_err_t net_mdns_status( void )
{
    return NET_ERROR;
}

#endif

// ------------------------------------------------------------------------- END
