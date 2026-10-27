#ifdef PREINIT_SUPPORTED
#include "preinit.h"
#endif

#include "lan8651.h"
#include "eth_net.h"
#include "log.h"
#include <delays.h>
#include "board.h"
#include <string.h>
#include <stdint.h>

#define USE_PLCA            0       // Define your mode (1 = PLCA, node A is coordinator; 0 = CSMA/CD)
#define PING_COUNT          10      // Number of A -> B pings in the test sequence
#define RX_TIMEOUT_MS       500     // Max wait for an expected frame
#define ETHERTYPE_TEST      0x88B5  // Local experimental EtherType for raw frames

#define MIKROBUS_POSITION_NODE_A MIKROBUS_1 // Define your mikrobus position
#define MIKROBUS_POSITION_NODE_B MIKROBUS_5 // Different SPI module than mikroBUS 1

typedef struct {
    char tag;
    eth_transport_t eth;
    eth_bus_spi_t  bus;
    lan8651_ctx_t  ctx;
    uint8_t mac[ 6 ];
    uint8_t ip[ 4 ];
} node_t;

static node_t node_a;
static node_t node_b;
static log_t logger;

static uint8_t rx_buf[ LAN8651_FRAME_SIZE ];
static uint8_t tx_buf[ LAN8651_FRAME_SIZE ];
static char hex_digits[ ] = "0123456789ABCDEF";
static uint8_t tests_run = 0;
static uint8_t tests_passed = 0;

// Print a byte as two hex digits
static void log_hex8( uint8_t val ) {
    log_printf( &logger, "%c%c", hex_digits[ val >> 4 ], hex_digits[ val & 0x0F ] );
}

static void log_mac( uint8_t *mac ) {
    uint8_t k;
    for ( k = 0; k < 6; k++ ) {
        log_hex8( mac[ k ] );
        if ( k < 5 ) log_printf( &logger, ":" );
    }
}

static void log_result( uint8_t ok ) {
    tests_run++;
    if ( ok ) tests_passed++;
    log_printf( &logger, " -> %s\r\n", ok ? "OK" : "FAIL" );
}

// Internet checksum (IP header / ICMP)
static uint16_t inet_checksum( uint8_t *buf, uint16_t len ) {
    uint32_t sum = 0;
    uint16_t i;

    for ( i = 0; i + 1 < len; i += 2 )
        sum += ( ( uint32_t )buf[ i ] << 8 ) | buf[ i + 1 ];
    if ( len & 1 )
        sum += ( uint32_t )buf[ len - 1 ] << 8;
    while ( sum >> 16 )
        sum = ( sum & 0xFFFF ) + ( sum >> 16 );

    return ( uint16_t )( ~sum );
}

// Ethernet header: dst, src, EtherType
static void build_eth_header( uint8_t *buf, uint8_t *dst, uint8_t *src, uint16_t etype ) {
    memcpy( &buf[ 0 ], dst, 6 );
    memcpy( &buf[ 6 ], src, 6 );
    buf[ 12 ] = ( uint8_t )( etype >> 8 );
    buf[ 13 ] = ( uint8_t )( etype & 0xFF );
}

// Wait for a frame with the given EtherType on a node, other frames are discarded
static uint16_t wait_frame( node_t *node, uint16_t etype ) {
    uint16_t t, len;

    for ( t = 0; t < RX_TIMEOUT_MS; t++ ) {
        len = eth_transport_receive( &node->eth, rx_buf, sizeof( rx_buf ) );
        if ( len >= 14 && ( ( ( uint16_t )rx_buf[ 12 ] << 8 ) | rx_buf[ 13 ] ) == etype )
            return len;
        Delay_ms( 1 );
    }
    return 0;
}

// Initialize one click, cfg must already be mapped to its mikroBUS
static uint8_t node_init( node_t *node, lan8651_cfg_t *cfg, uint8_t plca_id ) {
    uint32_t phy_id;
    int8_t k;

    memcpy( cfg->eth.mac, node->mac, 6 );
    memcpy( cfg->eth.ip, node->ip, 4 );
    cfg->plca_enable     = USE_PLCA;
    cfg->plca_node_id    = plca_id;
    cfg->plca_node_count = 2;

    node->eth.driver_ctx = &node->ctx;      // own driver state for each click
    log_printf( &logger, "NODE %c: SPI INIT...", node->tag );
    if ( lan8651_configure( &node->eth, &node->bus, cfg ) != ETH_TRANSPORT_SUCCESS ||
         eth_transport_init( &node->eth, &lan8651_driver ) != ETH_TRANSPORT_SUCCESS ) {
        log_printf( &logger, " FAILED\r\n" );
        return 0;
    }

    phy_id = lan8651_get_phy_id( &node->eth );
    log_printf( &logger, " OA_PHYID = 0x" );
    for ( k = 3; k >= 0; k-- )
        log_hex8( ( uint8_t )( phy_id >> ( 8 * k ) ) );
    log_printf( &logger, ", MAC = " );
    log_mac( node->mac );

    if ( phy_id == 0 || phy_id == 0xFFFFFFFF ) {
        log_printf( &logger, " -> CHIP NOT DETECTED\r\n" );
        return 0;
    }
    log_printf( &logger, " -> OK\r\n" );
    return 1;
}

static uint8_t node_link( node_t *node ) {
    return eth_transport_get_link_status( &node->eth );
}

// Raw frame with custom EtherType from one node to the other
static uint8_t test_raw( node_t *src, node_t *dst, uint16_t payload_len ) {
    uint16_t i, len;

    build_eth_header( tx_buf, dst->mac, src->mac, ETHERTYPE_TEST );
    for ( i = 0; i < payload_len; i++ )
        tx_buf[ 14 + i ] = ( uint8_t )( i * 7 + src->tag );

    log_printf( &logger, "RAW %c -> %c, %u bytes", src->tag, dst->tag, ( uint16_t )( 14 + payload_len ) );
    if ( !eth_transport_send( &src->eth, tx_buf, 14 + payload_len ) ) {
        log_printf( &logger, " (send failed)" );
        return 0;
    }

    len = wait_frame( dst, ETHERTYPE_TEST );
    if ( !len ) {
        log_printf( &logger, " (timeout)" );
        return 0;
    }
    // Short frames are padded to 60 bytes on the wire
    if ( len < 14 + payload_len || memcmp( rx_buf, tx_buf, 14 + payload_len ) != 0 ) {
        log_printf( &logger, " (data mismatch, got %u bytes)", len );
        return 0;
    }
    return 1;
}

// Broadcast ARP request from src, dst answers through the eth_net helper
static uint8_t test_arp( node_t *src, node_t *dst ) {
    static uint8_t broadcast[ 6 ] = { 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF };
    uint16_t len;

    build_eth_header( tx_buf, broadcast, src->mac, 0x0806 );
    tx_buf[ 14 ] = 0x00; tx_buf[ 15 ] = 0x01;       // HW type Ethernet
    tx_buf[ 16 ] = 0x08; tx_buf[ 17 ] = 0x00;       // IPv4
    tx_buf[ 18 ] = 6;    tx_buf[ 19 ] = 4;
    tx_buf[ 20 ] = 0x00; tx_buf[ 21 ] = 0x01;       // request
    memcpy( &tx_buf[ 22 ], src->mac, 6 );
    memcpy( &tx_buf[ 28 ], src->ip, 4 );
    memset( &tx_buf[ 32 ], 0, 6 );
    memcpy( &tx_buf[ 38 ], dst->ip, 4 );

    log_printf( &logger, "ARP %c who-has %u.%u.%u.%u", src->tag, dst->ip[ 0 ], dst->ip[ 1 ], dst->ip[ 2 ], dst->ip[ 3 ] );
    eth_transport_send( &src->eth, tx_buf, 42 );

    len = wait_frame( dst, 0x0806 );
    if ( !len ) {
        log_printf( &logger, " (request not received)" );
        return 0;
    }
    eth_net_handle_arp( &dst->eth, dst->mac, dst->ip, rx_buf, len );

    // Skip any ARP frame that is not the reply (e.g. own broadcast)
    do {
        len = wait_frame( src, 0x0806 );
    } while ( len && rx_buf[ 21 ] != 0x02 );
    if ( !len || memcmp( &rx_buf[ 22 ], dst->mac, 6 ) != 0 ) {
        log_printf( &logger, " (no valid reply)" );
        return 0;
    }
    log_printf( &logger, " is-at " );
    log_mac( &rx_buf[ 22 ] );
    return 1;
}

// ICMP echo request from src, dst answers through the eth_net helper
static uint8_t ping( node_t *src, node_t *dst, uint16_t seq ) {
    uint8_t *ip = &tx_buf[ 14 ];
    uint8_t *icmp = &tx_buf[ 34 ];
    uint16_t ck, len, i;

    build_eth_header( tx_buf, dst->mac, src->mac, 0x0800 );
    memset( ip, 0, 20 );
    ip[ 0 ] = 0x45;                                 // IPv4, 20 byte header
    ip[ 2 ] = 0; ip[ 3 ] = 20 + 8 + 32;             // total length
    ip[ 4 ] = ( uint8_t )( seq >> 8 ); ip[ 5 ] = ( uint8_t )seq;
    ip[ 8 ] = 64;                                   // TTL
    ip[ 9 ] = 1;                                    // ICMP
    memcpy( &ip[ 12 ], src->ip, 4 );
    memcpy( &ip[ 16 ], dst->ip, 4 );
    ck = inet_checksum( ip, 20 );
    ip[ 10 ] = ( uint8_t )( ck >> 8 ); ip[ 11 ] = ( uint8_t )ck;

    icmp[ 0 ] = 8; icmp[ 1 ] = 0;                   // echo request
    icmp[ 2 ] = 0; icmp[ 3 ] = 0;
    icmp[ 4 ] = 'M'; icmp[ 5 ] = 'E';               // identifier
    icmp[ 6 ] = ( uint8_t )( seq >> 8 ); icmp[ 7 ] = ( uint8_t )seq;
    for ( i = 0; i < 32; i++ )
        icmp[ 8 + i ] = ( uint8_t )( 'a' + ( i % 23 ) );
    ck = inet_checksum( icmp, 8 + 32 );
    icmp[ 2 ] = ( uint8_t )( ck >> 8 ); icmp[ 3 ] = ( uint8_t )ck;

    eth_transport_send( &src->eth, tx_buf, 14 + 20 + 8 + 32 );

    len = wait_frame( dst, 0x0800 );
    if ( !len )
        return 0;
    eth_net_handle_icmp( &dst->eth, dst->mac, dst->ip, rx_buf, len );

    len = wait_frame( src, 0x0800 );
    if ( len < 14 + 20 + 8 + 32 )
        return 0;
    // Echo reply (type 0) with the same identifier, sequence and payload
    return ( rx_buf[ 34 ] == 0 && memcmp( &rx_buf[ 38 ], &icmp[ 4 ], 4 + 32 ) == 0 &&
             memcmp( &rx_buf[ 26 ], dst->ip, 4 ) == 0 ) ? 1 : 0;
}

static uint8_t test_ping( node_t *src, node_t *dst, uint8_t count ) {
    uint8_t n, ok = 0;

    log_printf( &logger, "PING %c -> %c x%u: ", src->tag, dst->tag, ( uint16_t )count );
    for ( n = 0; n < count; n++ ) {
        if ( ping( src, dst, n ) ) {
            ok++;
            log_printf( &logger, "!" );
        } else {
            log_printf( &logger, "." );
        }
    }
    log_printf( &logger, " %u/%u", ( uint16_t )ok, ( uint16_t )count );
    return ok == count;
}

int main( void ) {
    #ifdef PREINIT_SUPPORTED
        preinit( );
    #endif

    log_cfg_t log_cfg;
    lan8651_cfg_t cfg_a, cfg_b;
    uint8_t ok_a, ok_b;
    uint8_t i;
    uint16_t seq = 0;

    // Init UART
    LOG_MAP_USB_UART( log_cfg );
    log_init( &logger, &log_cfg );

    Delay_ms( 100 );
    log_printf( &logger, "\r\n\n=== TWO-WIRE ETH (10BASE-T1S) A <-> B TEST ===\r\n" );
    log_printf( &logger, "Mode: %s\r\n", USE_PLCA ? "PLCA (A = coordinator)" : "CSMA/CD" );

    node_a.tag = 'A';
    node_a.mac[ 0 ] = 0x02; node_a.mac[ 1 ] = 0x4D; node_a.mac[ 2 ] = 0x45;
    node_a.mac[ 3 ] = 0x00; node_a.mac[ 4 ] = 0x00; node_a.mac[ 5 ] = 0x0A;
    node_a.ip[ 0 ] = 192; node_a.ip[ 1 ] = 168; node_a.ip[ 2 ] = 50; node_a.ip[ 3 ] = 1;

    node_b.tag = 'B';
    memcpy( node_b.mac, node_a.mac, 6 ); node_b.mac[ 5 ] = 0x0B;
    memcpy( node_b.ip, node_a.ip, 4 );   node_b.ip[ 3 ] = 2;

    // MIKROBUS() pastes tokens, so the position must be mapped with the macro itself
    lan8651_cfg_setup( &cfg_a );
    LAN8651_MAP_MIKROBUS( cfg_a, MIKROBUS_POSITION_NODE_A );
    lan8651_cfg_setup( &cfg_b );
    LAN8651_MAP_MIKROBUS( cfg_b, MIKROBUS_POSITION_NODE_B );

    ok_a = node_init( &node_a, &cfg_a, 0 );
    ok_b = node_init( &node_b, &cfg_b, 1 );
    if ( !ok_a || !ok_b ) {
        log_printf( &logger, "\r\n>>> INIT FAILED - check click placement, RST/CS and SPI wiring\r\n" );
        for ( ; ; );
    }

    // In PLCA mode node B reports link once it receives beacons from node A
    log_printf( &logger, "WAIT LINK..." );
    for ( i = 0; i < 50; i++ ) {
        if ( node_link( &node_a ) && node_link( &node_b ) )
            break;
        Delay_ms( 100 );
    }
    log_printf( &logger, " A:%s B:%s\r\n\r\n", node_link( &node_a ) ? "UP" : "DOWN",
                node_link( &node_b ) ? "UP" : "DOWN" );

    log_result( test_raw( &node_a, &node_b, 32 ) );
    log_result( test_raw( &node_b, &node_a, 32 ) );
    log_result( test_raw( &node_a, &node_b, 1000 ) );
    log_result( test_raw( &node_b, &node_a, 1500 ) );
    log_result( test_arp( &node_a, &node_b ) );
    log_result( test_arp( &node_b, &node_a ) );
    log_result( test_ping( &node_a, &node_b, PING_COUNT ) );
    log_result( test_ping( &node_b, &node_a, PING_COUNT ) );

    log_printf( &logger, "\r\n=== RESULT: %u/%u PASSED -> %s ===\r\n\r\n", ( uint16_t )tests_passed,
                ( uint16_t )tests_run, ( tests_passed == tests_run ) ? "TEST PASSED" : "TEST FAILED" );

    // Keep pinging A -> B once per second (unplug/replug the pair to watch it recover)
    log_printf( &logger, "Continuous ping A -> B:\r\n" );
    while ( 1 ) {
        log_printf( &logger, "ping #%u %s\r\n", seq, ping( &node_a, &node_b, seq ) ? "OK" : "TIMEOUT" );
        seq++;
        Delay_ms( 1000 );
    }

    return 0;
}

// ----------------------------------------------------------------------- END
