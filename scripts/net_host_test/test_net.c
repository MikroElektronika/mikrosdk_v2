/*
 * Host test of the mikroSDK network layer (middleware/net + lwIP) on a Linux TAP
 * device. Run by harness.py inside a private network namespace, which provides
 * the peer (Linux TCP/IP), DHCP/DNS (dnsmasq) and test servers on 192.168.77.1:
 *   7007/tcp echo, 7008/udp echo, 8000/tcp HTTP, 123/udp SNTP, 1883/tcp MQTT,
 *   5353/udp mDNS peer, nothing on 7999/tcp.
 *
 *   test_net dhcp     DHCP, random numbers from the built-in PRNG
 *   test_net static   static address 192.168.77.20, random numbers from a hook
 *
 * Prints "OK <name>" / "FAIL <name>: <detail>" per check and exits 1 on any failure.
 * The protocol with harness.py: "READY <ip>" and "LISTEN <port>" lines; the
 * harness answers "GO" on stdin when it has finished its part.
 */

#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <unistd.h>
#include <sys/random.h>

#include "net_api.h"
#include "net_http.h"
#include "net_http_server.h"
#include "net_mdns.h"
#include "net_mqtt.h"
#include "net_sntp.h"
#include "tap_driver.h"

static int failures;
static tap_driver_t tap;
static const net_ip4_t HOST = { { 192, 168, 77, 1 } };

#define CHECK( name, cond, ... ) do { \
        if ( cond ) { printf( "OK %s\n", name ); } \
        else { failures++; printf( "FAIL %s: ", name ); printf( __VA_ARGS__ ); printf( "\n" ); } \
        fflush( stdout ); } while ( 0 )

static uint32_t now_ms( void )
{
    struct timespec ts;
    clock_gettime( CLOCK_MONOTONIC, &ts );
    return ( uint32_t )( ts.tv_sec * 1000u + ts.tv_nsec / 1000000u );
}

static uint32_t hw_random( void )
{
    uint32_t r = 0;
    if ( getrandom( &r, sizeof( r ), 0 ) != sizeof( r ) )
    {
        abort();
    }
    return r;
}

static void on_assert( const char *message, const char *file, int line )
{
    fprintf( stderr, "lwIP assertion: %s (%s:%d)\n", message, file, line );
    abort();
}

/* Keep the stack (and an HTTP server, if given) running until the harness writes
 * "GO" (it pings us or connects meanwhile). */
static void wait_for_go_serving( uint32_t timeout_ms, net_http_server_t *srv );
static void wait_for_go( uint32_t timeout_ms )
{
    wait_for_go_serving( timeout_ms, NULL );
}

static void wait_for_go_serving( uint32_t timeout_ms, net_http_server_t *srv )
{
    char line[ 16 ];
    size_t len = 0;
    uint32_t start = net_now_ms();
    fcntl( 0, F_SETFL, fcntl( 0, F_GETFL ) | O_NONBLOCK );
    while ( net_now_ms() - start < timeout_ms )
    {
        net_poll();
        if ( srv )
        {
            net_http_server_poll( srv );
        }
        char c;
        while ( read( 0, &c, 1 ) == 1 )
        {
            if ( c == '\n' )
            {
                line[ len ] = '\0';
                if ( 0 == strcmp( line, "GO" ) )
                {
                    return;
                }
                len = 0;
            }
            else if ( len < sizeof( line ) - 1 )
            {
                line[ len++ ] = c;
            }
        }
        usleep( 1000 );
    }
    CHECK( "harness-go", false, "no GO from the harness" );
}

static void test_addresses( bool dhcp )
{
    net_ip4_t ip, mask, gw;
    char a[ 16 ], b[ 16 ], c[ 16 ];
    net_err_t err = net_get_address( &ip, &mask, &gw );
    net_ip4_to_string( &ip, a );
    net_ip4_to_string( &mask, b );
    net_ip4_to_string( &gw, c );
    if ( dhcp )
    {
        CHECK( "dhcp-address", NET_OK == err && ip.addr[ 0 ] == 192 && ip.addr[ 2 ] == 77 &&
               ip.addr[ 3 ] >= 50 && ip.addr[ 3 ] <= 60, "%s", a );
    }
    else
    {
        CHECK( "static-address", NET_OK == err && 0 == strcmp( a, "192.168.77.20" ), "%s", a );
    }
    CHECK( "netmask", 0 == strcmp( b, "255.255.255.0" ), "%s", b );
    CHECK( "gateway", 0 == strcmp( c, "192.168.77.1" ), "%s", c );
    printf( "READY %s\n", a );
    fflush( stdout );
    wait_for_go( 15000 );    /* the harness pings us meanwhile */
}

static void test_helpers( void )
{
    net_ip4_t ip;
    char s[ 16 ];
    CHECK( "ip-parse", NET_OK == net_ip4_from_string( "10.0.255.7", &ip ) &&
           0 == strcmp( net_ip4_to_string( &ip, s ), "10.0.255.7" ), "%s", s );
    CHECK( "ip-parse-reject", NET_INVALID == net_ip4_from_string( "256.1.1.1", &ip ) &&
           NET_INVALID == net_ip4_from_string( "1.2.3", &ip ) &&
           NET_INVALID == net_ip4_from_string( "1.2.3.4.5", &ip ) &&
           NET_INVALID == net_ip4_from_string( "1..2.3", &ip ) &&
           NET_INVALID == net_ip4_from_string( "1.2.3.4 ", &ip ), "accepted an invalid address" );
}

static void test_dns( void )
{
    net_ip4_t ip;
    char s[ 16 ] = "";
    net_err_t err = net_resolve( "test.mikroe.local", &ip, 5000 );
    CHECK( "dns-resolve", NET_OK == err && 0 == memcmp( &ip, &HOST, 4 ), "err %d ip %s", err, net_ip4_to_string( &ip, s ) );
    err = net_resolve( "missing.mikroe.local", &ip, 5000 );
    CHECK( "dns-not-found", NET_NOT_FOUND == err, "err %d", err );
    err = net_resolve( "192.168.77.1", &ip, 0 );
    CHECK( "dns-literal", NET_OK == err && 0 == memcmp( &ip, &HOST, 4 ), "err %d", err );
}

static void test_tcp_echo( uint32_t total )
{
    net_socket_t s;
    net_err_t err = net_tcp_connect( &s, &HOST, 7007, 5000 );
    CHECK( "tcp-connect", NET_OK == err, "err %d", err );
    if ( NET_OK != err )
    {
        return;
    }
    static uint8_t tx[ 1024 ], rx[ 2048 ];
    uint32_t seed = 12345, sent = 0, got = 0, rx_hash = 2166136261u, tx_hash = 2166136261u;
    bool ok = true;
    while ( got < total && ok )
    {
        if ( sent < total )
        {
            uint32_t n = ( total - sent < sizeof( tx ) ) ? total - sent : sizeof( tx );
            for ( uint32_t i = 0; i < n; i++ )
            {
                seed = seed * 1103515245u + 12345u;
                tx[ i ] = ( uint8_t )( seed >> 16 );
                tx_hash = ( tx_hash ^ tx[ i ] ) * 16777619u;
            }
            int32_t r = net_tcp_send( s, tx, n, 5000 );
            if ( r != ( int32_t )n )
            {
                ok = false;
                CHECK( "tcp-send", false, "sent %d of %u", r, n );
                break;
            }
            sent += n;
        }
        /* Read what is there (wait a bit when everything is sent). */
        int32_t r = net_tcp_receive( s, rx, sizeof( rx ), ( sent < total ) ? 0 : 5000 );
        if ( r > 0 )
        {
            for ( int32_t i = 0; i < r; i++ )
            {
                rx_hash = ( rx_hash ^ rx[ i ] ) * 16777619u;
            }
            got += ( uint32_t )r;
        }
        else if ( r != NET_TIMEOUT || sent >= total )
        {
            ok = false;
            CHECK( "tcp-receive", false, "receive %d after %u bytes", r, got );
        }
    }
    CHECK( "tcp-echo", ok && got == total && rx_hash == tx_hash, "%u of %u bytes, hash %s", got, total,
           rx_hash == tx_hash ? "ok" : "differs" );
    CHECK( "tcp-close", NET_OK == net_close( s ), "close failed" );
    CHECK( "tcp-closed-socket", NET_INVALID == net_tcp_send( s, tx, 1, 0 ), "send on a closed socket accepted" );
}

static void test_tcp_errors( void )
{
    net_socket_t s;
    net_err_t err = net_tcp_connect( &s, &HOST, 7999, 5000 );
    CHECK( "tcp-refused", NET_REFUSED == err && NET_SOCKET_INVALID == s, "err %d", err );
    net_ip4_t nobody = net_ip4( 192, 168, 77, 99 );
    uint32_t t0 = net_now_ms();
    err = net_tcp_connect( &s, &nobody, 80, 1500 );
    uint32_t took = net_now_ms() - t0;
    CHECK( "tcp-timeout", NET_TIMEOUT == err && took >= 1500 && took < 2500, "err %d after %u ms", err, took );
}

static void test_tcp_server( void )
{
    net_socket_t l, c;
    net_err_t err = net_tcp_listen( &l, 8080 );
    CHECK( "tcp-listen", NET_OK == err, "err %d", err );
    if ( NET_OK != err )
    {
        return;
    }
    printf( "LISTEN 8080\n" );
    fflush( stdout );
    err = net_tcp_accept( l, &c, 10000 );
    CHECK( "tcp-accept", NET_OK == err, "err %d", err );
    if ( NET_OK == err )
    {
        net_ip4_t peer;
        uint16_t port = 0;
        CHECK( "tcp-peer", NET_OK == net_tcp_peer( c, &peer, &port ) && 0 == memcmp( &peer, &HOST, 4 ) && port,
               "peer port %u", port );
        char buf[ 64 ];
        uint32_t len = 0;
        while ( len < 12 )
        {
            int32_t r = net_tcp_receive( c, buf + len, sizeof( buf ) - 1 - len, 5000 );
            if ( r <= 0 )
            {
                break;
            }
            len += ( uint32_t )r;
        }
        buf[ len ] = '\0';
        CHECK( "tcp-server-receive", 0 == strcmp( buf, "hello server" ), "got \"%s\"", buf );
        for ( uint32_t i = 0; i < len; i++ )
        {
            if ( buf[ i ] >= 'a' && buf[ i ] <= 'z' )
            {
                buf[ i ] = ( char )( buf[ i ] - 32 );
            }
        }
        CHECK( "tcp-server-send", net_tcp_send( c, buf, len, 5000 ) == ( int32_t )len, "send failed" );
        int32_t r = net_tcp_receive( c, buf, sizeof( buf ), 5000 );
        CHECK( "tcp-peer-close", NET_CLOSED == r, "receive after peer close returned %d", r );
        net_close( c );
    }
    net_close( l );
    wait_for_go( 10000 );    /* harness confirms it got the reply */
}

static void test_udp( void )
{
    net_socket_t s;
    net_err_t err = net_udp_open( &s, 0 );
    CHECK( "udp-open", NET_OK == err, "err %d", err );
    if ( NET_OK != err )
    {
        return;
    }
    const char msg[] = "ping-udp";
    err = net_udp_send_to( s, &HOST, 7008, msg, sizeof( msg ) - 1 );
    CHECK( "udp-send", NET_OK == err, "err %d", err );
    char buf[ 32 ];
    net_ip4_t from;
    uint16_t port = 0;
    int32_t r = net_udp_receive_from( s, buf, sizeof( buf ), &from, &port, 3000 );
    CHECK( "udp-echo", r == ( int32_t )sizeof( msg ) - 1 && 0 == memcmp( buf, msg, sizeof( msg ) - 1 ) &&
           0 == memcmp( &from, &HOST, 4 ) && 7008 == port, "r %d port %u", r, port );
    r = net_udp_receive_from( s, buf, sizeof( buf ), NULL, NULL, 200 );
    CHECK( "udp-timeout", NET_TIMEOUT == r, "r %d", r );
    net_close( s );
}

static void test_socket_limit( void )
{
    net_socket_t s[ NET_MAX_SOCKETS + 1 ];
    int opened = 0;
    for ( int i = 0; i < NET_MAX_SOCKETS; i++ )
    {
        if ( NET_OK == net_udp_open( &s[ i ], 0 ) )
        {
            opened++;
        }
    }
    net_err_t extra = net_udp_open( &s[ NET_MAX_SOCKETS ], 0 );
    CHECK( "socket-limit", NET_MAX_SOCKETS == opened && NET_NO_MEMORY == extra, "opened %d, extra %d", opened, extra );
    for ( int i = 0; i < opened; i++ )
    {
        net_close( s[ i ] );
    }
    net_err_t again = net_udp_open( &s[ 0 ], 0 );
    CHECK( "socket-reuse", NET_OK == again, "err %d", again );
    net_close( s[ 0 ] );
    CHECK( "socket-invalid", NET_INVALID == net_close( 99 ) && NET_INVALID == net_close( -1 ), "bad handle accepted" );
}

static void test_http( void )
{
    static char body[ 4096 ];
    net_http_response_t resp = { 0 };
    net_http_request_t req = { 0 };
    resp.body = body;
    resp.body_size = sizeof( body );

    req.host = "test.mikroe.local";
    req.port = 8000;
    req.path = "/hello";
    net_err_t err = net_http_request( &req, &resp, 5000 );
    CHECK( "http-get", NET_OK == err && 200 == resp.status && 0 == strcmp( body, "Hello from the host" ),
           "err %d status %u body \"%s\"", err, resp.status, body );

    static const char payload[] = "{\"sensor\":\"temp\",\"value\":23.5}";
    req.method = "POST";
    req.path = "/echo";
    req.content_type = "application/json";
    req.headers = "X-Test: 1\r\n";
    req.body = payload;
    req.body_len = sizeof( payload ) - 1;
    err = net_http_request( &req, &resp, 5000 );
    CHECK( "http-post", NET_OK == err && 200 == resp.status && resp.body_len == req.body_len &&
           0 == memcmp( body, payload, req.body_len ), "err %d status %u body \"%s\"", err, resp.status, body );

    memset( &req, 0, sizeof( req ) );
    req.host = "192.168.77.1";
    req.port = 8000;
    req.path = "/chunked";
    err = net_http_request( &req, &resp, 5000 );
    CHECK( "http-chunked", NET_OK == err && 200 == resp.status && 0 == strcmp( body, "chunk one|chunk two|end" ),
           "err %d status %u body \"%s\"", err, resp.status, body );

    req.path = "/missing";
    err = net_http_request( &req, &resp, 5000 );
    CHECK( "http-404", NET_OK == err && 404 == resp.status, "err %d status %u", err, resp.status );

    static char small[ 100 ];
    net_http_response_t r2 = { 0 };
    r2.body = small;
    r2.body_size = sizeof( small );
    req.path = "/big";
    err = net_http_request( &req, &r2, 10000 );
    CHECK( "http-big-truncated", NET_OK == err && 200 == r2.status && r2.truncated && 100 == r2.body_len,
           "err %d status %u len %u truncated %d", err, r2.status, r2.body_len, r2.truncated );

    req.path = "/close-delimited";
    err = net_http_request( &req, &resp, 5000 );
    CHECK( "http-close-delimited", NET_OK == err && 0 == strcmp( body, "until the connection closes" ),
           "err %d body \"%s\"", err, body );

    req.path = "/bad\r\nInjected: 1";
    CHECK( "http-reject-injection", NET_INVALID == net_http_request( &req, &resp, 1000 ), "accepted CR/LF in the path" );
    req.path = "/malformed";
    err = net_http_request( &req, &resp, 5000 );
    CHECK( "http-malformed", NET_ERROR == err, "err %d", err );
}

/* ------------------------------------------------------- HTTP server --- */

static int handler_calls;

static void on_index( const net_http_server_request_t *req, net_http_server_conn_t *conn )
{
    ( void )req;
    handler_calls++;
    net_http_server_respond( conn, 200, "text/html", "index page", 10 );
}

static void on_api( const net_http_server_request_t *req, net_http_server_conn_t *conn )
{
    char name[ 32 ], x[ 8 ], out[ 64 ];
    handler_calls++;
    if ( net_http_server_param( req->query, "name", name, sizeof( name ) ) < 0 ||
         net_http_server_param( req->query, "x", x, sizeof( x ) ) < 0 )
    {
        net_http_server_respond( conn, 400, "text/plain", "missing", 7 );
        return;
    }
    snprintf( out, sizeof( out ), "name=%s;x=%s", name, x );
    net_http_server_respond( conn, 200, "text/plain", out, ( uint32_t )strlen( out ) );
}

static void on_echo( const net_http_server_request_t *req, net_http_server_conn_t *conn )
{
    handler_calls++;
    net_http_server_respond( conn, 200, "application/octet-stream", req->body, req->body_len );
}

static void on_any( const net_http_server_request_t *req, net_http_server_conn_t *conn )
{
    handler_calls++;
    net_http_server_respond( conn, 200, "text/plain", req->method, ( uint32_t )strlen( req->method ) );
}

static void on_big( const net_http_server_request_t *req, net_http_server_conn_t *conn )
{
    static uint8_t piece[ 1000 ];
    ( void )req;
    handler_calls++;
    net_http_server_respond_begin( conn, 200, "application/octet-stream", "X-Pieces: 30\r\n", 30000 );
    for ( int i = 0; i < 30; i++ )
    {
        for ( int j = 0; j < 1000; j++ )
        {
            piece[ j ] = ( uint8_t )( ( i * 1000 + j ) % 251 );
        }
        net_http_server_send( conn, piece, sizeof( piece ) );
    }
}

static void on_forgot( const net_http_server_request_t *req, net_http_server_conn_t *conn )
{
    ( void )req;
    ( void )conn;
    handler_calls++;        /* answers nothing: the server must send 500 */
}

static void test_http_server( void )
{
    static const net_http_route_t routes[] = {
        { "GET", "/", on_index },
        { "GET", "/api", on_api },
        { "POST", "/echo", on_echo },
        { NULL, "/any", on_any },
        { "GET", "/big", on_big },
        { "GET", "/forgot", on_forgot },
    };
    static char buffer[ 512 ];
    static net_http_server_t srv;

    char v[ 16 ];
    CHECK( "param-decode", 5 == net_http_server_param( "a=1&b=x%20y%2Bz&c", "b", v, sizeof( v ) ) &&
           0 == strcmp( v, "x y+z" ), "value \"%s\"", v );
    CHECK( "param-plus-and-empty", 3 == net_http_server_param( "q=a+b&e=", "q", v, sizeof( v ) ) &&
           0 == strcmp( v, "a b" ) && 0 == net_http_server_param( "q=a+b&e=", "e", v, sizeof( v ) ), "value \"%s\"", v );
    CHECK( "param-missing-and-prefix", -1 == net_http_server_param( "ab=1&c", "a", v, sizeof( v ) ) &&
           -1 == net_http_server_param( "ab=1&c", "c", v, sizeof( v ) ), "value \"%s\"", v );
    CHECK( "param-too-long-and-nul", -1 == net_http_server_param( "k=0123456789abcdef", "k", v, sizeof( v ) ) &&
           -1 == net_http_server_param( "k=a%00b", "k", v, sizeof( v ) ), "value \"%s\"", v );
    CHECK( "param-bad-escape-kept", 3 == net_http_server_param( "k=%zz", "k", v, sizeof( v ) ) &&
           0 == strcmp( v, "%zz" ), "value \"%s\"", v );

    net_err_t err = net_http_server_start( &srv, 8081, routes, sizeof( routes ) / sizeof( routes[ 0 ] ),
                                           buffer, sizeof( buffer ) );
    CHECK( "http-server-start", NET_OK == err, "err %d", err );
    if ( NET_OK != err )
    {
        return;
    }
    printf( "HTTPSERVER 8081\n" );
    fflush( stdout );
    wait_for_go_serving( 60000, &srv );     /* the harness sends its requests meanwhile */
    CHECK( "http-server-handlers", 8 == handler_calls, "%d handler calls", handler_calls );
    CHECK( "http-server-requests", srv.requests >= 15, "%u requests", srv.requests );
    net_http_server_stop( &srv );
}

/* ------------------------------------------------------------- SNTP --- */

static void test_sntp( void )
{
    uint32_t seconds = 0;
    uint16_t ms = 0;
    CHECK( "sntp-not-synced-yet", !net_sntp_synced() && NET_NOT_READY == net_sntp_now( &seconds, &ms ), "synced too early" );
    net_err_t err = net_sntp_sync( "192.168.77.1", 3000 );
    struct timespec host;
    clock_gettime( CLOCK_REALTIME, &host );
    CHECK( "sntp-sync", NET_OK == err && net_sntp_synced(), "err %d", err );
    net_sntp_now( &seconds, &ms );
    double diff = ( ( double )seconds + ms / 1000.0 ) - ( ( double )host.tv_sec + host.tv_nsec / 1e9 );
    CHECK( "sntp-time-matches-host", diff > -2.0 && diff < 2.0, "off by %.3f s", diff );
    usleep( 300000 );
    uint32_t later = 0;
    uint16_t later_ms = 0;
    net_sntp_now( &later, &later_ms );
    double step = ( ( double )later + later_ms / 1000.0 ) - ( ( double )seconds + ms / 1000.0 );
    CHECK( "sntp-clock-runs", step > 0.2 && step < 0.6, "advanced %.3f s in 0.3 s", step );
    err = net_sntp_sync( "ntp.mikroe.local", 3000 );
    CHECK( "sntp-by-name", NET_OK == err, "err %d", err );
    err = net_sntp_sync( "192.168.77.2", 3000 );
    CHECK( "sntp-kiss-of-death-refused", NET_REFUSED == err, "err %d", err );
    uint32_t t0 = net_now_ms();
    err = net_sntp_sync( "192.168.77.3", 1500 );
    uint32_t took = net_now_ms() - t0;
    CHECK( "sntp-invalid-answers-ignored", NET_TIMEOUT == err && took >= 1500, "err %d after %u ms", err, took );
    CHECK( "sntp-keeps-last-good-time", net_sntp_synced(), "lost the time" );
}

/* ------------------------------------------------------------- MQTT --- */

typedef struct
{
    int count;
    char topic[ 64 ];
    uint8_t payload[ 512 ];
    uint32_t len;
} mqtt_inbox_t;

static void on_mqtt( void *ctx, const char *topic, const uint8_t *payload, uint32_t len )
{
    mqtt_inbox_t *in = ctx;
    in->count++;
    snprintf( in->topic, sizeof( in->topic ), "%s", topic );
    in->len = len;
    memcpy( in->payload, payload, ( len < sizeof( in->payload ) ) ? len : sizeof( in->payload ) );
}

/* Poll until `in` has `want` messages, the time is up or the connection ends. */
static net_err_t mqtt_pump( net_mqtt_t *m, mqtt_inbox_t *in, int want, uint32_t ms )
{
    uint32_t t0 = net_now_ms();
    net_err_t err = NET_OK;
    while ( net_now_ms() - t0 < ms && ( !in || in->count < want ) )
    {
        net_poll();
        err = net_mqtt_poll( m );
        if ( NET_OK != err )
        {
            break;
        }
        usleep( 1000 );
    }
    return err;
}

static void test_mqtt( void )
{
    static uint8_t buf_a[ 512 ], buf_b[ 256 ], buf_c[ 128 ];
    static net_mqtt_t a, b, c;
    static mqtt_inbox_t in_a, in_b;
    net_mqtt_cfg_t cfg;
    net_err_t err;

    net_mqtt_cfg_setup( &cfg );
    CHECK( "mqtt-cfg-defaults", 1883 == cfg.port && 60 == cfg.keepalive_s && cfg.clean_session && !cfg.client_id,
           "port %u keepalive %u", cfg.port, cfg.keepalive_s );
    CHECK( "mqtt-needs-host", NET_INVALID == net_mqtt_connect( &a, &cfg, buf_a, sizeof( buf_a ), NULL, NULL, 1000 ),
           "accepted no host" );
    cfg.host = "192.168.77.1";
    CHECK( "mqtt-needs-buffer", NET_INVALID == net_mqtt_connect( &a, &cfg, buf_a, 32, NULL, NULL, 1000 ),
           "accepted a 32-byte buffer" );
    cfg.password = "secret";
    CHECK( "mqtt-password-needs-user", NET_INVALID == net_mqtt_connect( &a, &cfg, buf_a, sizeof( buf_a ), NULL, NULL,
           1000 ), "accepted a password without user" );

    cfg.username = "bad";
    err = net_mqtt_connect( &a, &cfg, buf_a, sizeof( buf_a ), NULL, NULL, 3000 );
    CHECK( "mqtt-connect-refused", NET_REFUSED == err && 5 == a.connack_code && !net_mqtt_connected( &a ),
           "err %d code %u", err, a.connack_code );
    cfg.port = 7999;
    err = net_mqtt_connect( &a, &cfg, buf_a, sizeof( buf_a ), NULL, NULL, 3000 );
    CHECK( "mqtt-no-broker", NET_REFUSED == err && 0 == a.connack_code, "err %d", err );
    net_mqtt_cfg_setup( &cfg );
    cfg.host = "192.168.77.1";
    cfg.client_id = "silent";
    uint32_t t0 = net_now_ms();
    err = net_mqtt_connect( &a, &cfg, buf_a, sizeof( buf_a ), NULL, NULL, 1000 );
    uint32_t took = net_now_ms() - t0;
    CHECK( "mqtt-no-connack-timeout", NET_TIMEOUT == err && took >= 1000 && took < 3000 && !net_mqtt_connected( &a ),
           "err %d after %u ms", err, took );

    /* Main client: by name, credentials, generated client id, 2 s keep-alive. */
    net_mqtt_cfg_setup( &cfg );
    cfg.host = "broker.mikroe.local";
    cfg.username = "user";
    cfg.password = "secret";
    cfg.keepalive_s = 2;
    err = net_mqtt_connect( &a, &cfg, buf_a, sizeof( buf_a ), on_mqtt, &in_a, 3000 );
    CHECK( "mqtt-connect", NET_OK == err && net_mqtt_connected( &a ), "err %d", err );
    if ( NET_OK != err )
    {
        return;
    }
    err = net_mqtt_subscribe( &a, "echo/#", 1, 3000 );
    CHECK( "mqtt-subscribe", NET_OK == err, "err %d", err );
    CHECK( "mqtt-subscribe-refused", NET_REFUSED == net_mqtt_subscribe( &a, "forbidden/x", 1, 3000 ), "accepted" );
    CHECK( "mqtt-subscribe-qos2-invalid", NET_INVALID == net_mqtt_subscribe( &a, "x", 2, 3000 ), "accepted" );

    err = net_mqtt_publish( &a, "echo/a", "hello", 5, 0, false, 0 );
    CHECK( "mqtt-publish-qos0", NET_OK == err, "err %d", err );
    mqtt_pump( &a, &in_a, 1, 3000 );
    CHECK( "mqtt-receive-qos0", 1 == in_a.count && 0 == strcmp( in_a.topic, "echo/a" ) && 5 == in_a.len &&
           0 == memcmp( in_a.payload, "hello", 5 ), "%d messages, topic \"%s\" len %u", in_a.count, in_a.topic,
           in_a.len );

    uint8_t data[ 300 ];
    for ( uint32_t i = 0; i < sizeof( data ); i++ )
    {
        data[ i ] = ( uint8_t )( i * 7 + 3 );
    }
    err = net_mqtt_publish( &a, "echo/b", data, sizeof( data ), 1, false, 3000 );
    CHECK( "mqtt-publish-qos1-acked", NET_OK == err, "err %d", err );
    mqtt_pump( &a, &in_a, 2, 3000 );
    CHECK( "mqtt-receive-qos1", 2 == in_a.count && 0 == strcmp( in_a.topic, "echo/b" ) &&
           sizeof( data ) == in_a.len && 0 == memcmp( in_a.payload, data, sizeof( data ) ),
           "%d messages, topic \"%s\" len %u", in_a.count, in_a.topic, in_a.len );
    CHECK( "mqtt-publish-empty", NET_OK == net_mqtt_publish( &a, "echo/empty", NULL, 0, 1, false, 3000 ) &&
           NET_OK == mqtt_pump( &a, &in_a, 3, 3000 ) && 0 == in_a.len && 0 == strcmp( in_a.topic, "echo/empty" ),
           "topic \"%s\" len %u", in_a.topic, in_a.len );
    CHECK( "mqtt-publish-retain", NET_OK == net_mqtt_publish( &a, "echo/retained", "r", 1, 0, true, 0 ) &&
           NET_OK == mqtt_pump( &a, &in_a, 4, 3000 ) && 4 == in_a.count, "%d messages", in_a.count );
    CHECK( "mqtt-publish-wildcard-invalid", NET_INVALID == net_mqtt_publish( &a, "echo/+", "x", 1, 0, false, 0 ) &&
           NET_INVALID == net_mqtt_publish( &a, "echo/#", "x", 1, 0, false, 0 ) &&
           NET_INVALID == net_mqtt_publish( &a, "", "x", 1, 0, false, 0 ), "accepted" );
    t0 = net_now_ms();
    err = net_mqtt_publish( &a, "cmd/wrongack", "x", 1, 1, false, 800 );
    took = net_now_ms() - t0;
    CHECK( "mqtt-puback-id-checked", NET_TIMEOUT == err && took >= 800 && net_mqtt_connected( &a ),
           "err %d after %u ms", err, took );
    CHECK( "mqtt-publish-qos2-invalid", NET_INVALID == net_mqtt_publish( &a, "echo/q", "x", 1, 2, false, 0 ),
           "accepted" );

    /* 2000 bytes do not fit the 512-byte buffer: dropped, acknowledged, the stream stays in step. */
    in_a.count = 0;
    err = net_mqtt_publish( &a, "cmd/big", "", 0, 1, false, 3000 );
    mqtt_pump( &a, &in_a, 1, 3000 );
    CHECK( "mqtt-too-large-dropped", NET_OK == err && 1 == a.dropped && 1 == in_a.count &&
           0 == strcmp( in_a.topic, "echo/small" ) && 9 == in_a.len && net_mqtt_connected( &a ),
           "err %d dropped %u, %d messages, topic \"%s\"", err, a.dropped, in_a.count, in_a.topic );

    /* Keep-alive: idle longer than 2 s, the client pings and the broker answers. */
    in_a.count = 0;
    err = mqtt_pump( &a, NULL, 0, 2600 );
    CHECK( "mqtt-keepalive", NET_OK == err && 0 != a.ping_sent && !a.ping_pending && net_mqtt_connected( &a ),
           "err %d ping_sent %u pending %d", err, a.ping_sent, a.ping_pending );

    /* Last will: a second client with a will "crashes" (closes without DISCONNECT). */
    err = net_mqtt_subscribe( &a, "status/#", 1, 3000 );
    net_mqtt_cfg_setup( &cfg );
    cfg.host = "192.168.77.1";
    cfg.client_id = "crash";
    cfg.will_topic = "status/crash";
    cfg.will_message = "offline";
    cfg.will_len = 7;
    cfg.will_qos = 1;
    cfg.will_retain = true;
    net_err_t err_b = net_mqtt_connect( &b, &cfg, buf_b, sizeof( buf_b ), on_mqtt, &in_b, 3000 );
    CHECK( "mqtt-second-client", NET_OK == err && NET_OK == err_b, "subscribe %d connect %d", err, err_b );
    net_mqtt_publish( &b, "echo/from-b", "b", 1, 1, false, 3000 );
    mqtt_pump( &a, &in_a, 1, 3000 );
    CHECK( "mqtt-between-clients", 1 == in_a.count && 0 == strcmp( in_a.topic, "echo/from-b" ), "topic \"%s\"",
           in_a.topic );
    net_close( b.sock );
    b.connected = false;
    mqtt_pump( &a, &in_a, 2, 3000 );
    CHECK( "mqtt-last-will", 2 == in_a.count && 0 == strcmp( in_a.topic, "status/crash" ) && 7 == in_a.len &&
           0 == memcmp( in_a.payload, "offline", 7 ), "%d messages, topic \"%s\"", in_a.count, in_a.topic );
    CHECK( "mqtt-closed-client", NET_CLOSED == net_mqtt_poll( &b ) &&
           NET_CLOSED == net_mqtt_publish( &b, "x", "x", 1, 0, false, 0 ), "still usable" );

    /* Unsubscribe: messages stop. */
    err = net_mqtt_unsubscribe( &a, "echo/#", 3000 );
    in_a.count = 0;
    net_err_t pub = net_mqtt_publish( &a, "echo/c", "c", 1, 1, false, 3000 );
    mqtt_pump( &a, &in_a, 1, 500 );
    CHECK( "mqtt-unsubscribe", NET_OK == err && NET_OK == pub && 0 == in_a.count, "err %d/%d, %d messages", err, pub,
           in_a.count );

    /* Clean disconnect: no will (a will would reach a subscriber). */
    net_mqtt_disconnect( &a );
    CHECK( "mqtt-disconnect", !net_mqtt_connected( &a ) && NET_CLOSED == net_mqtt_poll( &a ), "still connected" );
    printf( "MQTTCHECK\n" );
    fflush( stdout );
    wait_for_go( 10000 );

    /* Unanswered ping: the connection is given up after another keep-alive period. */
    net_mqtt_cfg_setup( &cfg );
    cfg.host = "192.168.77.1";
    cfg.client_id = "noping";
    cfg.keepalive_s = 1;
    err = net_mqtt_connect( &c, &cfg, buf_c, sizeof( buf_c ), NULL, NULL, 3000 );
    t0 = net_now_ms();
    net_err_t end = mqtt_pump( &c, NULL, 0, 5000 );
    took = net_now_ms() - t0;
    CHECK( "mqtt-ping-unanswered", NET_OK == err && NET_TIMEOUT == end && took >= 1900 && took < 3000 &&
           !net_mqtt_connected( &c ), "connect %d end %d after %u ms", err, end, took );

    /* Broker errors: a malformed remaining length, the broker closing. */
    cfg.client_id = "garbage";
    cfg.keepalive_s = 0;
    err = net_mqtt_connect( &c, &cfg, buf_c, sizeof( buf_c ), NULL, NULL, 3000 );
    if ( NET_OK == err )
    {
        net_mqtt_publish( &c, "cmd/garbage", "", 0, 0, false, 0 );
    }
    end = mqtt_pump( &c, NULL, 0, 3000 );
    CHECK( "mqtt-malformed-length", NET_OK == err && NET_ERROR == end && !net_mqtt_connected( &c ),
           "connect %d end %d", err, end );
    cfg.client_id = "closer";
    err = net_mqtt_connect( &c, &cfg, buf_c, sizeof( buf_c ), NULL, NULL, 3000 );
    if ( NET_OK == err )
    {
        net_mqtt_publish( &c, "cmd/close", "", 0, 0, false, 0 );
    }
    end = mqtt_pump( &c, NULL, 0, 3000 );
    CHECK( "mqtt-broker-closed", NET_OK == err && ( NET_CLOSED == end || NET_RESET == end ) &&
           !net_mqtt_connected( &c ), "connect %d end %d", err, end );
}

/* ------------------------------------------------------------- mDNS --- */

static net_err_t mdns_wait( net_err_t want, uint32_t ms )
{
    uint32_t t0 = net_now_ms();
    while ( net_mdns_status() != want && net_now_ms() - t0 < ms )
    {
        net_poll();
        usleep( 1000 );
    }
    return net_mdns_status();
}

static void test_mdns( void )
{
    static const char long_label[] = "a123456789b123456789c123456789d123456789e123456789f123456789xyzw";   /* 64 */
    static char long_txt[ 80 ];
    memset( long_txt, 'x', 64 );
    uint8_t web = 0xFF, mqtt = 0xFF, again = 0xFF;

    CHECK( "mdns-not-started", NET_NOT_READY == net_mdns_status() &&
           NET_NOT_READY == net_mdns_add_service( "x", "_http", NET_MDNS_TCP, 80, NULL, NULL ) &&
           NET_NOT_READY == net_mdns_rename( "x" ) && NET_INVALID == net_mdns_remove_service( 0 ), "status %d",
           net_mdns_status() );
    CHECK( "mdns-bad-hostname", NET_INVALID == net_mdns_start( "bad name" ) && NET_INVALID == net_mdns_start( "" ) &&
           NET_INVALID == net_mdns_start( long_label ), "accepted" );
    net_err_t err = net_mdns_start( NULL );     /* net_config_t.hostname: mikrosdk-test */
    CHECK( "mdns-start", NET_OK == err && NET_INVALID == net_mdns_start( "again" ), "err %d", err );
    CHECK( "mdns-bad-service", NET_INVALID == net_mdns_add_service( "x", "http", NET_MDNS_TCP, 80, NULL, NULL ) &&
           NET_INVALID == net_mdns_add_service( long_label, "_http", NET_MDNS_TCP, 80, NULL, NULL ) &&
           NET_INVALID == net_mdns_add_service( "x", "_http", ( net_mdns_proto_t )7, 80, NULL, NULL ) &&
           NET_INVALID == net_mdns_add_service( "x", "_http", NET_MDNS_TCP, 80, long_txt, NULL ), "accepted" );
    err = net_mdns_add_service( "mikrosdk web", "_http", NET_MDNS_TCP, 80, "path=/;;board=test;", &web );
    net_err_t err2 = net_mdns_add_service( "mikrosdk mqtt", "_mqtt", NET_MDNS_TCP, 1883, NULL, &mqtt );
    CHECK( "mdns-add-services", NET_OK == err && NET_OK == err2 && 0 == web && 1 == mqtt, "err %d %d ids %u %u",
           err, err2, web, mqtt );
    CHECK( "mdns-services-full", NET_NO_MEMORY == net_mdns_add_service( "x", "_ftp", NET_MDNS_TCP, 21, NULL, NULL ),
           "third service accepted" );
    err = mdns_wait( NET_OK, 5000 );
    CHECK( "mdns-probing-done", NET_OK == err, "status %d", err );
    printf( "MDNS mikrosdk-test\n" );
    fflush( stdout );
    wait_for_go( 30000 );                       /* the harness queries meanwhile */

    err = net_mdns_remove_service( web );
    CHECK( "mdns-remove-service", NET_OK == err && NET_INVALID == net_mdns_remove_service( web ) &&
           NET_INVALID == net_mdns_remove_service( 9 ), "err %d", err );
    printf( "MDNSGONE mikrosdk-test\n" );       /* the harness checks _http is gone, _mqtt is not */
    fflush( stdout );
    wait_for_go( 30000 );
    err = net_mdns_add_service( "mikrosdk web", "_http", NET_MDNS_TCP, 8080, NULL, &again );
    CHECK( "mdns-slot-reused", NET_OK == err && web == again, "err %d id %u", err, again );

    /* Another device (the harness) owns taken.local. */
    err = net_mdns_rename( "taken" );
    net_err_t end = mdns_wait( NET_REFUSED, 5000 );
    CHECK( "mdns-name-conflict", NET_OK == err && NET_REFUSED == end, "rename %d status %d", err, end );
    CHECK( "mdns-bad-rename", NET_INVALID == net_mdns_rename( "a.b" ) && NET_INVALID == net_mdns_rename( NULL ),
           "accepted" );
    err = net_mdns_rename( "mikrosdk-test" );
    end = mdns_wait( NET_OK, 5000 );
    CHECK( "mdns-rename-after-conflict", NET_OK == err && NET_OK == end, "rename %d status %d", err, end );
}

static void test_link( void )
{
    tap.link = false;
    uint32_t t0 = net_now_ms();
    while ( net_now_ms() - t0 < 3 * NET_LINK_POLL_MS )
    {
        net_poll();
        usleep( 1000 );
    }
    CHECK( "link-down", !net_link_up() && !net_is_ready(), "still up" );
    tap.link = true;
    net_err_t err = net_wait_ready( 15000 );
    CHECK( "link-up-again", NET_OK == err, "err %d", err );
}

int main( int argc, char **argv )
{
    bool dhcp = !( argc > 1 && 0 == strcmp( argv[ 1 ], "static" ) );
    net_driver_t drv;
    if ( tap_driver_open( &tap, &drv, "tap0" ) )
    {
        perror( "tap0" );
        return 2;
    }

    net_config_t cfg;
    net_config_default( &cfg );
    CHECK( "init-needs-driver", NET_INVALID == net_init( &cfg ), "accepted a config without a driver" );
    cfg.driver = &drv;
    cfg.now_ms = now_ms;
    cfg.assert_hook = on_assert;
    cfg.hostname = "mikrosdk-test";
    static const uint8_t mac[ 6 ] = { 0x02, 0x4D, 0x49, 0x4B, 0x52, 0x01 };
    memcpy( cfg.mac, mac, 6 );
    if ( !dhcp )
    {
        cfg.use_dhcp = false;
        cfg.ip = net_ip4( 192, 168, 77, 20 );
        cfg.netmask = net_ip4( 255, 255, 255, 0 );
        cfg.gateway = HOST;
        cfg.dns = HOST;
        cfg.random = hw_random;
    }
    net_err_t err = net_init( &cfg );
    CHECK( "init", NET_OK == err, "err %d", err );
    CHECK( "init-twice", NET_INVALID == net_init( &cfg ), "second net_init accepted" );
    err = net_wait_ready( 15000 );
    CHECK( "ready", NET_OK == err, "err %d", err );
    if ( NET_OK != err )
    {
        return 1;
    }

    test_addresses( dhcp );
    test_helpers();
    test_dns();
    test_tcp_echo( dhcp ? 300000 : 20000 );
    test_tcp_errors();
    test_udp();
    test_socket_limit();
    test_http();
    test_tcp_server();
    test_http_server();
    test_sntp();
    test_mqtt();
    test_mdns();
    if ( dhcp )
    {
        printf( "MDNSMARK\n" );                        /* the harness forgets what it heard so far */
        fflush( stdout );
        wait_for_go( 10000 );
        test_link();
        uint32_t t0 = net_now_ms();
        while ( net_now_ms() - t0 < 3000 )              /* probing (3 x 250 ms) and announcing */
        {
            net_poll();
            usleep( 1000 );
        }
        printf( "MDNSAGAIN mikrosdk-test\n" );         /* the harness checks it probed and announced again */
        fflush( stdout );
        wait_for_go( 10000 );
    }

    printf( "RESULT %s (%d failed, tx %u rx %u frames)\n", failures ? "FAIL" : "PASS", failures,
            tap.tx_frames, tap.rx_frames );
    return failures ? 1 : 0;
}
