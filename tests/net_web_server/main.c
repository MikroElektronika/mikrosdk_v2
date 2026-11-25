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
 *   NET_IF_PIC32MZ the on-chip Ethernet of PIC32MZ with its PHY (mikromedia 4/5
 *                  for PIC32MZ)
 * Gets an address by DHCP (or uses a static one), then serves
 *   /             an HTML page (interface, address, uptime, requests)
 *   /api/status   the same as JSON
 * Needs MIKROSDK_NET_STACK=LWIP.
 */

#ifdef PREINIT_SUPPORTED
#include "preinit.h"
#endif

// ----------------------------------------------------------------- Settings

#define NET_IF_SPI      0
#define NET_IF_PIC32MZ  1
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
#include "net_clock.h"

#if NET_INTERFACE == NET_IF_SPI
    #include "transport_select.h"
    #include "net_driver_eth_transport.h"
    #define INTERFACE_NAME SPI_ETH_CHIP_NAME " (SPI)"
#elif NET_INTERFACE == NET_IF_PIC32MZ
    #include "mcu.h"
    #include "net_driver_pic32mz.h"
    #define INTERFACE_NAME "PIC32MZ Ethernet"
#else
    #error "Unknown NET_INTERFACE"
#endif

// --------------------------------------------------------------------- State

static const uint8_t local_mac[ 6 ] = LOCAL_MAC;
static log_t logger;
static net_driver_t driver;
static uint32_t requests;
static char addr_text[ 16 ];

#if NET_INTERFACE == NET_IF_SPI
static eth_transport_t eth;
static eth_bus_spi_t bus;
#endif

// --------------------------------------------------------------- Interfaces

#if NET_INTERFACE == NET_IF_SPI
static void interface_init( void )
{
    spi_eth_cfg_t eth_cfg;
    spi_eth_cfg_setup( &eth_cfg );
    SPI_ETH_MAP_MIKROBUS( eth_cfg, MIKROBUS_POSITION_SPI_ETH );
    memcpy( eth_cfg.eth.mac, local_mac, 6 );

    if ( spi_eth_configure( &eth, &bus, &eth_cfg ) != ETH_TRANSPORT_SUCCESS ||
         eth_transport_init( &eth, &SPI_ETH_DRIVER ) != ETH_TRANSPORT_SUCCESS )
    {
        log_printf( &logger, "%s init FAILED\r\n", SPI_ETH_CHIP_NAME );
        for ( ; ; );
    }
    net_driver_eth_transport( &driver, &eth );
}
#else
// mikromedia 4/5 for PIC32MZ (144 pins): the RMII pins that share an analog input.
static void board_eth_pins( void )
{
    ANSELJCLR = ( 1UL << 8 ) | ( 1UL << 9 ) | ( 1UL << 11 );   // ETXD0, ETXD1, EREFCLK
    ANSELHCLR = ( 1UL << 4 ) | ( 1UL << 5 );                    // ERXERR, ERXD1
}

static void interface_init( void )
{
    net_pic32mz_cfg_t eth_cfg;
    net_pic32mz_cfg_setup( &eth_cfg );
    #ifdef ETH_RST
    eth_cfg.phy_reset = ETH_RST;
    #endif
    eth_cfg.pins_init = board_eth_pins;
    net_driver_pic32mz( &driver, &eth_cfg );
}
#endif

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

static int32_t send_text( net_socket_t client, const char *text )
{
    return net_tcp_send( client, text, ( uint32_t )strlen( text ), 3000 );
}

// --------------------------------------------------------------- Web server

static void serve( net_socket_t client )
{
    static char request[ 512 ];
    static char body[ 640 ];
    char num[ 11 ];
    uint32_t len = 0;

    // Read the request header (the body of a GET is empty).
    while ( len < sizeof( request ) - 1 )
    {
        int32_t got = net_tcp_receive( client, request + len, sizeof( request ) - 1 - len, 3000 );
        if ( got <= 0 )
        {
            break;
        }
        len += ( uint32_t )got;
        request[ len ] = '\0';
        if ( strstr( request, "\r\n\r\n" ) )
        {
            break;
        }
    }
    request[ len ] = '\0';
    requests++;

    net_ip4_t ip;
    if ( NET_OK == net_get_address( &ip, NULL, NULL ) )
    {
        net_ip4_to_string( &ip, addr_text );   // DHCP may give a new one after a link loss
    }

    const char *status = "200 OK";
    const char *type = "text/html";
    uint32_t uptime_s = net_now_ms() / 1000u;
    body[ 0 ] = '\0';

    if ( 0 == strncmp( request, "GET / ", 6 ) )
    {
        append( body, sizeof( body ), "<!DOCTYPE html><html><head><title>mikroSDK</title></head><body>"
                                      "<h1>Hello from mikroSDK</h1><p>Network layer: lwIP over " INTERFACE_NAME
                                      "</p><ul><li>Address: " );
        append( body, sizeof( body ), addr_text );
        append( body, sizeof( body ), "</li><li>Uptime: " );
        append( body, sizeof( body ), u32_to_text( uptime_s, num ) );
        append( body, sizeof( body ), " s</li><li>Requests: " );
        append( body, sizeof( body ), u32_to_text( requests, num ) );
        append( body, sizeof( body ), "</li></ul></body></html>" );
    }
    else if ( 0 == strncmp( request, "GET /api/status ", 16 ) )
    {
        type = "application/json";
        append( body, sizeof( body ), "{\"interface\":\"" INTERFACE_NAME "\",\"address\":\"" );
        append( body, sizeof( body ), addr_text );
        append( body, sizeof( body ), "\",\"uptime_s\":" );
        append( body, sizeof( body ), u32_to_text( uptime_s, num ) );
        append( body, sizeof( body ), ",\"requests\":" );
        append( body, sizeof( body ), u32_to_text( requests, num ) );
        append( body, sizeof( body ), "}" );
    }
    else
    {
        status = "404 Not Found";
        type = "text/plain";
        append( body, sizeof( body ), "Not found" );
    }

    send_text( client, "HTTP/1.1 " );
    send_text( client, status );
    send_text( client, "\r\nContent-Type: " );
    send_text( client, type );
    send_text( client, "\r\nContent-Length: " );
    send_text( client, u32_to_text( ( uint32_t )strlen( body ), num ) );
    send_text( client, "\r\nConnection: close\r\n\r\n" );
    send_text( client, body );
    net_close( client );

    log_printf( &logger, "%s -> %s\r\n", ( len > 6 && request[ 0 ] == 'G' ) ? "GET" : "request", status );
}

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

    net_clock_init();
    interface_init();

    net_config_t cfg;
    net_config_default( &cfg );
    cfg.driver = &driver;
    cfg.now_ms = net_clock_ms;
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
        log_printf( &logger, "net_init FAILED (driver / PHY)\r\n" );
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

    net_socket_t listener;
    if ( NET_OK != net_tcp_listen( &listener, 80 ) )
    {
        log_printf( &logger, "Cannot listen on port 80\r\n" );
        for ( ; ; );
    }

    bool link = true;
    for ( ; ; )
    {
        net_poll();

        if ( net_link_up() != link )
        {
            link = !link;
            log_printf( &logger, link ? ">>> LINK UP\r\n" : ">>> LINK DOWN\r\n" );
        }

        net_socket_t client;
        if ( NET_OK == net_tcp_accept( listener, &client, 0 ) )
        {
            serve( client );
        }
    }

    return 0;
}

// ----------------------------------------------------------------------- END
