/*
 * Host test of the mikroSDK network layer (middleware/net + lwIP) on a Linux TAP
 * device. Run by harness.py inside a private network namespace, which provides
 * the peer (Linux TCP/IP), DHCP/DNS (dnsmasq) and test servers on 192.168.77.1:
 *   7007/tcp echo, 7008/udp echo, 8000/tcp HTTP, nothing on 7999/tcp.
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

/* Keep the stack running until the harness writes "GO" (it pings us or connects meanwhile). */
static void wait_for_go( uint32_t timeout_ms )
{
    char line[ 16 ];
    size_t len = 0;
    uint32_t start = net_now_ms();
    fcntl( 0, F_SETFL, fcntl( 0, F_GETFL ) | O_NONBLOCK );
    while ( net_now_ms() - start < timeout_ms )
    {
        net_poll();
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
    if ( dhcp )
    {
        test_link();
    }

    printf( "RESULT %s (%d failed, tx %u rx %u frames)\n", failures ? "FAIL" : "PASS", failures,
            tap.tx_frames, tap.rx_frames );
    return failures ? 1 : 0;
}
