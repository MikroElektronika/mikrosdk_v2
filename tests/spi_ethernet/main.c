#ifdef PREINIT_SUPPORTED
#include "preinit.h"
#endif

#define SPI_ETH_CHIP    SPI_ETH_CHIP_LAN9250   // Define your chip (SPI_ETH_CHIP_* in transport_select.h)
#define USE_DHCP        1                       // Define your mode (1 = DHCP; 0 = local static ip)

#include "transport_select.h"
#include "eth_net.h"
#include "log.h"
#include <delays.h>
#include "board.h"
#include <string.h>
#include <stdint.h>

#ifndef MIKROBUS_POSITION_SPI_ETH
    #define MIKROBUS_POSITION_SPI_ETH 1 // Define your mikrobus position
#endif

static eth_transport_t eth;
static eth_bus_spi_t   bus;
static log_t logger;

static uint8_t local_mac[ 6 ] = { 0x02, 0xDE, 0xAD, 0xBE, 0xEF, 0x01 };
static uint8_t local_ip[ 4 ]  = { 172, 20, 22, 200 };   // Define your local static ip
#if USE_DHCP
static uint8_t dhcp_offered_ip[ 4 ] = { 0, 0, 0, 0 };
static uint8_t dhcp_server_ip[ 4 ]  = { 0, 0, 0, 0 };
static uint8_t dhcp_src_ip[ 4 ]     = { 0, 0, 0, 0 };
static uint32_t dhcp_xid = 0x39017623;
#endif
static char hex_digits[ ] = "0123456789ABCDEF";
static uint8_t rx_buf[ 700 ];

// Print an IP address in dotted decimal format
static void log_print_ip( log_t *logger, uint8_t *ip ) {
    uint8_t k, val, digit;
    for ( k = 0; k < 4; k++ ) {
        val = ip[ k ];
        if ( val >= 100 ) {
            digit = val / 100; log_printf( logger, "%c", hex_digits[ digit ] );
            val -= digit * 100;
            digit = val / 10; log_printf( logger, "%c", hex_digits[ digit ] );
            val -= digit * 10;
        } else if ( val >= 10 ) {
            digit = val / 10; log_printf( logger, "%c", hex_digits[ digit ] );
            val -= digit * 10;
        }
        log_printf( logger, "%c", hex_digits[ val ] );
        if ( k < 3 ) log_printf( logger, "." );
    }
}

// Print the HTTP server ready message
static void print_server_ready( void ) {
    log_printf( &logger, "\r\n=== HTTP SERVER READY - open http://" );
    log_print_ip( &logger, local_ip );
    log_printf( &logger, " ===\r\n" );
}

// Web server response (HTTP 200 OK)
static char http_response[ ] =
    "HTTP/1.1 200 OK\r\n"
    "Content-Type: text/html\r\n"
    "Connection: close\r\n"
    "\r\n"
    "<!DOCTYPE html><html><body>"
    "<h1>Hello from " SPI_ETH_CHIP_NAME " chip!</h1>"
    "<p>MikroE SPI-ETHERNET library test works!</p>"
    "</body></html>\r\n";

// Handler TCP/HTTP (dispatch SYN/ACK/FIN)
static void handle_tcp( eth_transport_t *eth, uint8_t *pkt, uint16_t len ) {
    uint8_t *ip = &pkt[ 14 ];
    uint8_t ihl = ( ip[ 0 ] & 0x0F ) * 4;       // IHL: lower 4 bits, converted from 32-bit words to bytes
    uint8_t *tcp = &ip[ ihl ];                  // TCP header starts after the IP header
    uint16_t dst_port = ( ( uint16_t )tcp[ 2 ] << 8 ) | tcp[ 3 ];       // TCP bytes 2-3 = dest. port (big-endian)
    uint16_t src_port = ( ( uint16_t )tcp[ 0 ] << 8 ) | tcp[ 1 ];       // TCP bytes 0-1 = src port
    uint32_t seq = ( ( uint32_t )tcp[ 4 ] << 24 ) | ( ( uint32_t )tcp[ 5 ] << 16 ) |
                ( ( uint32_t )tcp[ 6 ] << 8 )  | tcp[ 7 ];              // bytes 4-7 = sequence number (big-endian)
    uint32_t our_seq = ( ( uint32_t )tcp[ 8 ] << 24 ) | ( ( uint32_t )tcp[ 9 ] << 16 ) |
                ( ( uint32_t )tcp[ 10 ] << 8 ) | tcp[ 11 ];             // bytes 8-11 = ack number = our next seq for this connection
    uint8_t  tcp_hlen = ( tcp[ 12 ] >> 4 ) * 4;     // Data offset: upper 4 bits, converted to bytes
    uint8_t  flags = tcp[ 13 ];                     // TCP flags
    uint16_t ip_total = ( ( uint16_t )ip[ 2 ] << 8 ) | ip[ 3 ];         // Total IP packet length
    uint16_t tcp_payload_len;
    uint8_t *src_ip_addr  = &ip[ 12 ];      // IP bytes 12-15 = src address
    uint8_t *src_mac_addr = &pkt[ 6 ];      // Ethernet bytes 6-11 = MAC source

    if ( len < 14 + ihl + 20 || ip_total < ihl + tcp_hlen || ip_total > len - 14 )
        return;                                         // Truncated or malformed segment
    tcp_payload_len = ip_total - ihl - tcp_hlen;

    if ( dst_port != 80 )
        return;

    if ( flags & ETH_NET_TCP_FLAG_SYN ) {               // SYN: request to establish a connection
        log_printf( &logger, "TCP SYN received -> SYN-ACK\r\n" );
        eth_net_send_tcp( eth, local_mac, local_ip, src_mac_addr, src_ip_addr, 80, src_port,
                0x12345678, seq + 1, ETH_NET_TCP_FLAG_SYN | ETH_NET_TCP_FLAG_ACK, NULL, 0 );    // ACK the client's SYN
        return;
    }

    if ( ( flags & ETH_NET_TCP_FLAG_ACK ) && tcp_payload_len > 0 ) {    // ACK with data = HTTP request received
        uint32_t new_ack = seq + tcp_payload_len;               // Acknowledge all received data bytes
        uint16_t resp_len = ( uint16_t )( sizeof( http_response ) - 1 );        // Exclude the terminating '\0'
        log_printf( &logger, "TCP DATA received -> HTTP 200\r\n" );

        eth_net_send_tcp( eth, local_mac, local_ip, src_mac_addr, src_ip_addr, 80, src_port,
                our_seq, new_ack, ETH_NET_TCP_FLAG_ACK, NULL, 0 );      // ACK for received data

        eth_net_send_tcp( eth, local_mac, local_ip, src_mac_addr, src_ip_addr, 80, src_port,
                our_seq, new_ack, ETH_NET_TCP_FLAG_ACK | ETH_NET_TCP_FLAG_FIN,
                ( uint8_t* )http_response, resp_len );          // HTTP response + close connection (END)
        return;
    }

    if ( flags & ETH_NET_TCP_FLAG_FIN ) {                       // FIN: client requests connection closure
        eth_net_send_tcp( eth, local_mac, local_ip, src_mac_addr, src_ip_addr, 80, src_port,
                our_seq, seq + 1, ETH_NET_TCP_FLAG_ACK, NULL, 0 );      // Acknowledge the client's FIN
        log_printf( &logger, "TCP FIN -> ACK\r\n" );
    }
}

// Handler IPv4 (dispatch ICMP/TCP)
static void handle_ip( eth_transport_t *eth, uint8_t *pkt, uint16_t len ) {
    uint8_t *ip = &pkt[ 14 ];
    if ( len < 34 )
        return;

    if ( memcmp( &ip[ 16 ], local_ip, 4 ) != 0 )    // bytes 16-19 = IP address dest.
        return;

    if ( ip[ 9 ] == ETH_NET_IP_PROTO_ICMP ) {
        eth_net_handle_icmp( eth, local_mac, local_ip, pkt, len );
        return;
    }

    if ( ip[ 9 ] == ETH_NET_IP_PROTO_TCP ) {
        handle_tcp( eth, pkt, len );
        return;
    }
}

#if USE_DHCP
// DISCOVER -> OFFER -> REQUEST -> ACK, returns 1 once an address is leased
static uint8_t dhcp_obtain_ip( eth_transport_t *eth ) {
    uint8_t dhcp_state = 0;     // 0 = discovering, 1 = requesting
    uint8_t retry;
    uint8_t i;
    uint8_t result;
    uint16_t rx_len;

    for ( retry = 0; retry < 5; retry++ ) {
        eth_net_dhcp_send( eth, dhcp_state ? ETH_NET_DHCP_MSG_REQUEST : ETH_NET_DHCP_MSG_DISCOVER,
                           local_mac, dhcp_src_ip, dhcp_offered_ip, dhcp_server_ip, dhcp_xid );

        // Wait ~2s for a reply (20 x 100ms)
        for ( i = 0; i < 20; i++ ) {
            rx_len = eth_transport_receive( eth, rx_buf, sizeof( rx_buf ) );
            result = eth_net_handle_dhcp( rx_buf, rx_len, dhcp_xid, dhcp_offered_ip, dhcp_server_ip, local_ip );
            if ( result == ETH_NET_DHCP_OFFER && dhcp_state == 0 ) {
                log_printf( &logger, "DHCPOFFER received\r\n" );
                dhcp_state = 1;
                break;
            }
            if ( result == ETH_NET_DHCP_ACK && dhcp_state == 1 ) {
                log_printf( &logger, "DHCPACK received -> IP obtained\r\n" );
                return 1;
            }
            Delay_ms( 100 );
        }
    }
    return 0;
}
#endif

int main( void ) {
    #ifdef PREINIT_SUPPORTED
        preinit( );
    #endif

    // Declarations
    log_cfg_t log_cfg;
    spi_eth_cfg_t eth_cfg;
    uint8_t rev;
    uint8_t link_ok = 0;
    uint8_t i;
    uint8_t last_link;
    uint8_t current_link;
    uint16_t rx_len;
    uint16_t etype;
    #if SPI_ETH_CHIP == SPI_ETH_CHIP_ENC28J60
    uint8_t low, high;
    uint16_t phhid1;
    #endif

    // Init UART
    LOG_MAP_USB_UART( log_cfg );
    log_init( &logger, &log_cfg );

    Delay_ms( 100 );
    log_printf( &logger, "\r\n\n" );
    log_printf( &logger, "=== CHIP INIT TEST ===\r\n" );

    // Init SPI
    log_printf( &logger, "SPI INIT..." );
    spi_eth_cfg_setup( &eth_cfg );
    SPI_ETH_MAP_MIKROBUS( eth_cfg, MIKROBUS_POSITION_SPI_ETH );

    memcpy( eth_cfg.eth.mac, local_mac, 6 );
    memcpy( eth_cfg.eth.ip, local_ip, 4 );

    if ( spi_eth_configure( &eth, &bus, &eth_cfg ) != ETH_TRANSPORT_SUCCESS ) {
        log_printf( &logger, " FAILED\r\n" );
        for ( ; ; );
    }
    log_printf( &logger, " OK\r\n" );

    // Init Chip
    log_printf( &logger, "NIC INIT..." );
    if ( eth_transport_init( &eth, &SPI_ETH_DRIVER ) != ETH_TRANSPORT_SUCCESS ) {
        log_printf( &logger, " FAILED\r\n" );
        for ( ; ; );
    }
    log_printf( &logger, " OK\r\n" );

    // SPI
    rev = spi_eth_get_rev( &eth );
    log_printf( &logger, "EREVID = 0x" );
    log_printf( &logger, "%c", hex_digits[ ( rev >> 4 ) & 0x0F ] );
    log_printf( &logger, "%c", hex_digits[ rev & 0x0F ] );
    if ( rev == 0x00 || rev == 0xFF )
        log_printf( &logger, " NOT OK" );
    log_printf( &logger, "\r\n" );

    // PHY ID
    #if SPI_ETH_CHIP == SPI_ETH_CHIP_ENC28J60
    spi_eth_phy_read( &eth, PHHID1, &low, &high );
    phhid1 = ( uint16_t )high << 8 | low;       // 16-bit word reconstruction
    log_printf( &logger, "PHHID1 = 0x%X%X%X%X (expected 0x0083)%s\r\n",
                ( phhid1 >> 12 ) & 0x0F, ( phhid1 >> 8 ) & 0x0F,
                ( phhid1 >> 4 ) & 0x0F, phhid1 & 0x0F,
                ( high == 0x00 && low == 0x83 ) ? "" : " NOT OK" );   // 0x0083 = expected value for the ENC28J60 PHY
    #elif SPI_ETH_CHIP == SPI_ETH_CHIP_LAN8651
    {
        uint32_t phy_id = spi_eth_get_phy_id( &eth );
        log_printf( &logger, "OA_PHYID = 0x" );
        for ( i = 0; i < 8; i++ )
            log_printf( &logger, "%c", hex_digits[ ( phy_id >> ( 28 - 4 * i ) ) & 0x0F ] );
        log_printf( &logger, "\r\n" );
    }
    #endif

    // Waiting link
    log_printf( &logger, "\r\nWAIT LINK (10s max)...\r\n" );
    for ( i = 0; i < 100; i++ ) {               // 100ms x 100 = max 10s timeout
        if ( eth_transport_get_link_status( &eth ) ) {
            link_ok = 1;
            log_printf( &logger, ">>> LINK UP\r\n" );
            log_printf( &logger, "\r\n" );
            break;
        }
        log_printf( &logger, "." );
        if ( ( i + 1 ) % 10 == 0 )              // Waiting messages for cable connection
            log_printf( &logger, "\r\n" );
        Delay_ms( 100 );
    }
    if ( !link_ok ) {
        if ( rev == 0x00 || rev == 0xFF )
            log_printf( &logger, "\r\n>>> CHIP NOT DETECTED (SPI/EREVID fail)\r\n" );
        else
            log_printf( &logger, "\r\n>>> LINK DOWN (no Ethernet cable)\r\n" );
    }
    last_link = eth_transport_get_link_status( &eth );

    #if USE_DHCP
        if ( link_ok && dhcp_obtain_ip( &eth ) ) {
            memcpy( dhcp_src_ip, local_ip, 4 );
            eth_transport_set_ip( &eth, local_ip );
            log_printf( &logger, "IP (DHCP) = " );
            log_print_ip( &logger, local_ip );
            log_printf( &logger, "\r\n" );
            print_server_ready( );
        } else if ( link_ok ) {
            log_printf( &logger, "DHCP DOWN (timeout) -> static local IP\r\n" );
        } else {
            log_printf( &logger, "DHCP DOWN (no link) -> static local IP\r\n" );
        }
    #else
        log_printf( &logger, "Static IP mode -> " );
        log_print_ip( &logger, local_ip );
        log_printf( &logger, "\r\n" );
        print_server_ready( );
    #endif

    while ( 1 ) {
        current_link = eth_transport_get_link_status( &eth );
        if ( current_link != last_link ) {
            if ( current_link ) {
                log_printf( &logger, ">>> LINK UP\r\n" );
                print_server_ready( );
            }
            else {
                log_printf( &logger, ">>> LINK DOWN\r\n" );
            }
            last_link = current_link;
        }

        rx_len = eth_transport_receive( &eth, rx_buf, sizeof( rx_buf ) );
        if ( rx_len < 14 ) {
            Delay_ms( 1 );
            continue;
        }

        etype = ( ( uint16_t )rx_buf[ 12 ] << 8 ) | rx_buf[ 13 ];   // Ethernet bytes 12&13 = EtherType (big-endian)
        if ( etype == ETH_NET_ETHERTYPE_ARP )
            eth_net_handle_arp( &eth, local_mac, local_ip, rx_buf, rx_len );
        else if ( etype == ETH_NET_ETHERTYPE_IPV4 )
            handle_ip( &eth, rx_buf, rx_len );

        Delay_ms( 1 );
    }

    return 0;
}

// ----------------------------------------------------------------------- END
