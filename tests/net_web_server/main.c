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
 * @file main.c
 * @brief Web server on the mikroSDK network layer (net_api.h, lwIP).
 * @details The same application on two kinds of Ethernet:
 *   NET_IF_SPI     an SPI Ethernet controller on mikroBUS (ENC28J60, W5500,
 *                  LAN9250, W6100, LAN8651, see ../spi_ethernet/transport_select.h)
 *   NET_IF_PIC32   the on-chip Ethernet of PIC32MX 6xx/7xx or PIC32MZ with its PHY
 *                  (MCU card for PIC32MX795F512L, mikromedia 4/5 for PIC32MZ)
 *   NET_IF_STM32   the on-chip Ethernet of STM32F107/F2/F4/F7 with its PHY (MCU
 *                  cards and boards with an Ethernet connector)
 *   NET_IF_KINETIS the on-chip ENET of NXP Kinetis MK6x / MKV58 with its PHY
 *   NET_IF_TM4C    the on-chip Ethernet of TI TM4C129 with its integrated PHY
 * Gets an address by DHCP (or uses a static one), then serves
 *   /             an HTML page (interface, address, uptime, requests)
 *   /api/status   the same as JSON
 * Needs MIKROSDK_NET_STACK=LWIP (the default).
 */

#ifdef PREINIT_SUPPORTED
#include "preinit.h"
#endif

// ----------------------------------------------------------------- Settings

// NET_IF_SPI (Click), NET_IF_PIC32, NET_IF_STM32, NET_IF_KINETIS or NET_IF_TM4C (on-chip)
#define NET_INTERFACE   NET_IF_SPI              // Define your interface

#define SPI_ETH_CHIP    SPI_ETH_CHIP_LAN9250    // NET_IF_SPI: your chip (SPI_ETH_CHIP_* in transport_select.h)
#define USE_DHCP        1                       // 1 = DHCP, 0 = the static address below

#ifndef MIKROBUS_POSITION_SPI_ETH
    #define MIKROBUS_POSITION_SPI_ETH 1         // NET_IF_SPI: your mikroBUS position
#endif

#define LOCAL_MAC       { 0x02, 0xDE, 0xAD, 0xBE, 0xEF, 0x02 }   // Define your MAC address
#define STATIC_IP       net_ip4( 192, 168, 1, 200 )
#define STATIC_NETMASK  net_ip4( 255, 255, 255, 0 )
#define STATIC_GATEWAY  net_ip4( 192, 168, 1, 1 )

// ------------------------------------------------------------------ Includes

#include <string.h>
#include <stdint.h>
#include "board.h"
#include "log.h"
#include "net_api.h"
#include "net_http_server.h"
#include "net_mdns.h"

#include "net_test_interface.h"       // tests/net_common: interface selected above

// --------------------------------------------------------------------- State

static const uint8_t local_mac[ 6 ] = LOCAL_MAC;
static log_t logger;
static net_driver_t driver;
static net_http_server_t server;
static char addr_text[ 16 ];

// ------------------------------------------------------------------- Helpers

static char *u32_to_text( uint32_t v, char *buf )
{
    char tmp[ 11 ];
    uint8_t n = 0;
    char *out = buf;
    do
    {
        tmp[ n++ ] = ( char )( '0' + v % 10 );
        v /= 10;
    } while ( v );
    while ( n )
    {
        *out++ = tmp[ --n ];
    }
    *out = '\0';
    return buf;
}

// Append src to dst (size bytes), always terminated.
static void append( char *dst, uint32_t size, const char *src )
{
    uint32_t len = ( uint32_t )strlen( dst );
    while ( *src && ( len + 1 < size ) )
    {
        dst[ len++ ] = *src++;
    }
    dst[ len ] = '\0';
}

// --------------------------------------------------------------- Web server

// Refresh the address text: DHCP may give a new one after a link loss.
static void update_address( void )
{
    net_ip4_t ip;
    if ( NET_OK == net_get_address( &ip, NULL, NULL ) )
    {
        net_ip4_to_string( &ip, addr_text );
    }
}

static void on_index( const net_http_server_request_t *req, net_http_server_conn_t *conn )
{
    static char body[ 640 ];
    char num[ 11 ];
    ( void )req;
    update_address();
    body[ 0 ] = '\0';
    append( body, sizeof( body ), "<!DOCTYPE html><html><head><title>mikroSDK</title></head><body>"
                                  "<h1>Hello from mikroSDK</h1><p>Network layer: lwIP over " INTERFACE_NAME
                                  "</p><ul><li>Address: " );
    append( body, sizeof( body ), addr_text );
    append( body, sizeof( body ), "</li><li>Uptime: " );
    append( body, sizeof( body ), u32_to_text( net_now_ms() / 1000u, num ) );
    append( body, sizeof( body ), " s</li><li>Requests: " );
    append( body, sizeof( body ), u32_to_text( server.requests + 1, num ) );
    append( body, sizeof( body ), "</li></ul></body></html>" );
    net_http_server_respond( conn, 200, "text/html", body, ( uint32_t )strlen( body ) );
    log_printf( &logger, "GET / -> 200\r\n" );
}

static void on_status( const net_http_server_request_t *req, net_http_server_conn_t *conn )
{
    static char body[ 160 ];
    char num[ 11 ];
    ( void )req;
    update_address();
    body[ 0 ] = '\0';
    append( body, sizeof( body ), "{\"interface\":\"" INTERFACE_NAME "\",\"address\":\"" );
    append( body, sizeof( body ), addr_text );
    append( body, sizeof( body ), "\",\"uptime_s\":" );
    append( body, sizeof( body ), u32_to_text( net_now_ms() / 1000u, num ) );
    append( body, sizeof( body ), ",\"requests\":" );
    append( body, sizeof( body ), u32_to_text( server.requests + 1, num ) );
    append( body, sizeof( body ), "}" );
    net_http_server_respond( conn, 200, "application/json", body, ( uint32_t )strlen( body ) );
    log_printf( &logger, "GET /api/status -> 200\r\n" );
}

// Other paths get 404 and other methods 405 from the server.
static const net_http_route_t routes[ ] = {
    { "GET", "/", on_index },
    { "GET", "/api/status", on_status },
};

// ---------------------------------------------------------------------- Main

int main( void )
{
    #ifdef PREINIT_SUPPORTED
    preinit();
    #endif

    log_cfg_t log_cfg;
    LOG_MAP_USB_UART( log_cfg );
    log_init( &logger, &log_cfg );
    log_printf( &logger, "\r\n=== mikroSDK network layer: web server over %s ===\r\n", INTERFACE_NAME );

    net_test_interface_init( &driver, local_mac, &logger );

    net_config_t cfg;
    net_config_default( &cfg );      // time source: systime_ms (core cycle counter)
    cfg.driver = &driver;
    cfg.hostname = "mikrosdk";
    memcpy( cfg.mac, local_mac, 6 );
    #if !USE_DHCP
    cfg.use_dhcp = false;
    cfg.ip = STATIC_IP;
    cfg.netmask = STATIC_NETMASK;
    cfg.gateway = STATIC_GATEWAY;
    #endif

    if ( NET_OK != net_init( &cfg ) )
    {
        log_printf( &logger, "net_init FAILED (driver, PHY or its reference clock)\r\n" );
        for ( ; ; );
    }

    log_printf( &logger, "Waiting for link and address" );
    while ( NET_OK != net_wait_ready( 1000 ) )
    {
        log_printf( &logger, net_link_up() ? "." : " (no link)" );
    }
    net_ip4_t ip;
    net_get_address( &ip, NULL, NULL );
    net_ip4_to_string( &ip, addr_text );
    log_printf( &logger, "\r\nReady: open http://%s/\r\n", addr_text );

    static char request_buffer[ 1024 ];
    if ( NET_OK != net_http_server_start( &server, 80, routes, sizeof( routes ) / sizeof( routes[ 0 ] ),
                                          request_buffer, sizeof( request_buffer ) ) )
    {
        log_printf( &logger, "Cannot listen on port 80\r\n" );
        for ( ; ; );
    }

    // mDNS: http://mikrosdk.local/ and "mikroSDK web server" in service browsers
    // (the controller must pass multicast; the SPI Click chips' filters may not).
    if ( NET_OK == net_mdns_start( NULL ) &&
         NET_OK == net_mdns_add_service( "mikroSDK web server", "_http", NET_MDNS_TCP, 80, "path=/", NULL ) )
    {
        log_printf( &logger, "mDNS: http://%s.local/\r\n", cfg.hostname );
    }

    bool link = true;
    net_err_t mdns = NET_NOT_READY;
    for ( ; ; )
    {
        if ( net_mdns_status() != mdns )
        {
            mdns = net_mdns_status();
            if ( NET_REFUSED == mdns )
            {
                log_printf( &logger, "mDNS: %s.local is used by another device, renaming\r\n", cfg.hostname );
                net_mdns_rename( "mikrosdk-2" );
            }
        }
        net_poll();
        net_http_server_poll( &server );

        if ( net_link_up() != link )
        {
            link = !link;
            log_printf( &logger, link ? ">>> LINK UP\r\n" : ">>> LINK DOWN\r\n" );
        }
    }

    return 0;
}

// ----------------------------------------------------------------------- END
