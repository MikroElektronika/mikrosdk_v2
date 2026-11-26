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
 * @brief Network clients on the mikroSDK network layer (net_api.h, lwIP):
 * HTTP (replaces the CycloneTCP test tests/ethernet/test_http_client), SNTP
 * and MQTT against public servers.
 * @details Runs on the same interfaces as net_web_server (NET_INTERFACE below,
 * see ../net_common/net_test_interface.h). Gets an address by DHCP, then checks
 *   DNS     httpbin.org resolves
 *   HTTP    GET and POST to http://httpbin.org/anything (it echoes the
 *           request as JSON), 404 from /status/404
 *   SNTP    time from pool.ntp.org
 *   MQTT    test.mosquitto.org: subscribe to a topic of this board, publish
 *           to it with QoS 1 and receive the message back
 * and prints "PASS <check>" / "FAIL <check>: <why>" and a summary on the USB
 * UART. Needs a network with Internet access.
 */

#ifdef PREINIT_SUPPORTED
#include "preinit.h"
#endif

// ----------------------------------------------------------------- Settings

// NET_IF_SPI (Click), NET_IF_PIC32, NET_IF_STM32, NET_IF_KINETIS or NET_IF_TM4C (on-chip)
#define NET_INTERFACE   NET_IF_SPI              // Define your interface

#define SPI_ETH_CHIP    SPI_ETH_CHIP_LAN9250    // NET_IF_SPI: your chip (SPI_ETH_CHIP_* in transport_select.h)

#ifndef MIKROBUS_POSITION_SPI_ETH
    #define MIKROBUS_POSITION_SPI_ETH 1         // NET_IF_SPI: your mikroBUS position
#endif

#define LOCAL_MAC       { 0x02, 0xDE, 0xAD, 0xBE, 0xEF, 0x03 }   // Define your MAC address

#define HTTP_HOST       "httpbin.org"
#define NTP_HOST        "pool.ntp.org"
#define MQTT_HOST       "test.mosquitto.org"
#define TIMEOUT_MS      10000

// ------------------------------------------------------------------ Includes

#include <string.h>
#include <stdint.h>
#include "board.h"
#include "log.h"
#include "net_api.h"
#include "net_http.h"
#include "net_sntp.h"
#include "net_mqtt.h"

#include "net_test_interface.h"       // tests/net_common: interface selected above

// --------------------------------------------------------------------- State

static const uint8_t local_mac[ 6 ] = LOCAL_MAC;
static log_t logger;
static net_driver_t driver;
static char body[ 1024 ];
static uint8_t mqtt_buffer[ 256 ];
static net_mqtt_t mqtt;
static char topic[ 40 ];
static uint8_t passed, failed;

typedef struct
{
    uint8_t count;
    char payload[ 32 ];
} inbox_t;

// ------------------------------------------------------------------- Helpers

static void check( const char *name, bool ok, const char *why, int32_t detail )
{
    if ( ok )
    {
        passed++;
        log_printf( &logger, "PASS %s\r\n", name );
    }
    else
    {
        failed++;
        log_printf( &logger, "FAIL %s: %s (%ld)\r\n", name, why, ( long )detail );
    }
}

static net_err_t http( const char *method, const char *path, const char *data, net_http_response_t *resp )
{
    net_http_request_t req;
    memset( &req, 0, sizeof( req ) );
    req.method = method;
    req.host = HTTP_HOST;
    req.path = path;
    if ( data )
    {
        req.content_type = "text/plain";
        req.body = data;
        req.body_len = ( uint32_t )strlen( data );
    }
    memset( resp, 0, sizeof( *resp ) );
    resp->body = body;
    resp->body_size = sizeof( body );
    return net_http_request( &req, resp, TIMEOUT_MS );
}

static void on_message( void *ctx, const char *t, const uint8_t *payload, uint32_t len )
{
    inbox_t *in = ctx;
    ( void )t;
    in->count++;
    if ( len >= sizeof( in->payload ) )
    {
        len = sizeof( in->payload ) - 1;
    }
    memcpy( in->payload, payload, len );
    in->payload[ len ] = '\0';
}

// --------------------------------------------------------------------- Tests

static void test_dns( void )
{
    net_ip4_t ip;
    char text[ 16 ];
    net_err_t err = net_resolve( HTTP_HOST, &ip, TIMEOUT_MS );
    check( "dns " HTTP_HOST, NET_OK == err, "not resolved", err );
    if ( NET_OK == err )
    {
        log_printf( &logger, "     %s = %s\r\n", HTTP_HOST, net_ip4_to_string( &ip, text ) );
    }
}

static void test_http( void )
{
    net_http_response_t resp;
    net_err_t err = http( "GET", "/anything?board=mikrosdk", NULL, &resp );
    check( "http get", NET_OK == err && 200 == resp.status && strstr( body, "\"board\": \"mikrosdk\"" ),
           "status or echo wrong", NET_OK == err ? resp.status : err );

    err = http( "POST", "/anything", "hello from mikroSDK", &resp );
    check( "http post", NET_OK == err && 200 == resp.status && strstr( body, "hello from mikroSDK" ),
           "status or echo wrong", NET_OK == err ? resp.status : err );

    err = http( "GET", "/status/404", NULL, &resp );
    check( "http 404", NET_OK == err && 404 == resp.status, "expected 404", NET_OK == err ? resp.status : err );
}

static void test_sntp( void )
{
    net_err_t err = net_sntp_sync( NTP_HOST, TIMEOUT_MS );
    uint32_t seconds = 0;
    uint16_t ms = 0;
    if ( NET_OK == err )
    {
        net_sntp_now( &seconds, &ms );
    }
    // After 2026-01-01 00:00:00 UTC and before 2100: a plausible clock.
    check( "sntp " NTP_HOST, NET_OK == err && seconds > 1767225600UL && seconds < 4102444800UL, "no time", err );
    if ( NET_OK == err )
    {
        log_printf( &logger, "     UNIX time %lu.%03u\r\n", ( unsigned long )seconds, ms );
    }
}

static void test_mqtt( void )
{
    static inbox_t inbox;
    net_mqtt_cfg_t cfg;
    net_mqtt_cfg_setup( &cfg );
    cfg.host = MQTT_HOST;
    cfg.keepalive_s = 30;

    net_err_t err = net_mqtt_connect( &mqtt, &cfg, mqtt_buffer, sizeof( mqtt_buffer ), on_message, &inbox,
                                      TIMEOUT_MS );
    check( "mqtt connect " MQTT_HOST, NET_OK == err, "connect failed", err );
    if ( NET_OK != err )
    {
        return;
    }
    err = net_mqtt_subscribe( &mqtt, topic, 1, TIMEOUT_MS );
    check( "mqtt subscribe", NET_OK == err, "subscribe failed", err );
    err = net_mqtt_publish( &mqtt, topic, "ping", 4, 1, false, TIMEOUT_MS );
    check( "mqtt publish qos1", NET_OK == err, "no PUBACK", err );

    uint32_t start = net_now_ms();
    while ( 0 == inbox.count && ( net_now_ms() - start ) < TIMEOUT_MS && NET_OK == err )
    {
        net_poll();
        err = net_mqtt_poll( &mqtt );
    }
    check( "mqtt receive", 1 <= inbox.count && 0 == strcmp( inbox.payload, "ping" ), "message not back", err );
    net_mqtt_disconnect( &mqtt );
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
    log_printf( &logger, "\r\n=== mikroSDK network layer: clients over %s ===\r\n", INTERFACE_NAME );

    net_test_interface_init( &driver, local_mac, &logger );

    net_config_t cfg;
    net_config_default( &cfg );      // time source: systime_ms (core cycle counter)
    cfg.driver = &driver;
    cfg.hostname = "mikrosdk-client";
    memcpy( cfg.mac, local_mac, 6 );
    if ( NET_OK != net_init( &cfg ) )
    {
        log_printf( &logger, "net_init FAILED (driver, PHY or its reference clock)\r\n" );
        for ( ; ; );
    }

    log_printf( &logger, "Waiting for link and address" );
    net_err_t err = net_wait_ready( 30000 );
    log_printf( &logger, "\r\n" );
    check( "dhcp", NET_OK == err, net_link_up() ? "no address" : "no link", err );
    if ( NET_OK == err )
    {
        net_ip4_t ip;
        char text[ 16 ];
        net_get_address( &ip, NULL, NULL );
        log_printf( &logger, "     address %s\r\n", net_ip4_to_string( &ip, text ) );

        // A topic of this board: mikrosdk/test/<MAC>.
        static const char hex[] = "0123456789abcdef";
        strcpy( topic, "mikrosdk/test/" );
        char *p = topic + strlen( topic );
        for ( uint8_t i = 0; i < 6; i++ )
        {
            *p++ = hex[ local_mac[ i ] >> 4 ];
            *p++ = hex[ local_mac[ i ] & 0xF ];
        }
        *p = '\0';

        test_dns();
        test_http();
        test_sntp();
        test_mqtt();
    }

    log_printf( &logger, "RESULT %s: %u passed, %u failed\r\n", failed ? "FAIL" : "PASS", passed, failed );
    for ( ; ; )
    {
        net_poll();                  // keeps answering pings
    }
    return 0;
}

// ------------------------------------------------------------------------- END
