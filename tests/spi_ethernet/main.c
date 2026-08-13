#ifdef PREINIT_SUPPORTED
#include "preinit.h"
#endif

#include "transport.h"

#define SPI_ETH_CHIP    LAN9250        // Define your chip

#include "transport_select.h"
#include "drv_spi_master.h"
#include "log.h"
#include <delays.h>
#include "board.h"
#include <string.h>
#include <stdint.h>

#ifndef MIKROBUS_POSITION_SPI_ETH
    #define MIKROBUS_POSITION_SPI_ETH 3
#endif

static spi_ethernet_t eth;
static spi_master_t   spi;
static log_t logger;

static uint8_t local_mac[ 6 ] = { 0x02, 0xDE, 0xAD, 0xBE, 0xEF, 0x01 };
static uint8_t local_ip[ 4 ]  = { 172, 20, 22, 200 };
static char hex_digits[ ] = "0123456789ABCDEF";

static char http_response[ ] =
    "HTTP/1.1 200 OK\r\n"
    "Content-Type: text/html\r\n"
    "Connection: close\r\n"
    "\r\n"
    "<!DOCTYPE html><html><body>"
    "<h1>Hello from ETH Click chip!</h1>"
    "<p>MikroE SPI-ETHERNET library test works!</p>"
    "<p>IP: 172.20.22.200</p>"
    "</body></html>\r\n";

// Handler TCP/HTTP
static void handle_tcp( spi_ethernet_t *eth, uint8_t *pkt, uint16_t len ) {
    uint8_t *ip = &pkt[ 14 ];
    uint8_t ihl = ( ip[ 0 ] & 0x0F ) * 4;       // IHL in 32-bit words and x4 for the IP header size in bytes (only take the 4 bits on the right for IHL)
    uint8_t *tcp = &ip[ ihl ];                  // TCP header immediately after the IP header
    uint16_t dst_port = ( ( uint16_t )tcp[ 2 ] << 8 ) | tcp[ 3 ];       // TCP bytes 2-3 = dest. port (big-endian)
    uint16_t src_port = ( ( uint16_t )tcp[ 0 ] << 8 ) | tcp[ 1 ];       // TCP bytes 0-1 = src port
    uint32_t seq = ( ( uint32_t )tcp[ 4 ] << 24 ) | ( ( uint32_t )tcp[ 5 ] << 16 ) |
                ( ( uint32_t )tcp[ 6 ] << 8 )  | tcp[ 7 ];              // bytes 4-7 = sequence number (big-endian, 32 bits)
    uint8_t  tcp_hlen = ( tcp[ 12 ] >> 4 ) * 4;     // Data offset = the upper 4 bits of byte 12, x4 bytes size
    uint8_t  flags = tcp[ 13 ];                     // byte 13 = flags TCP (SYN/ACK/FIN/...)
    uint16_t ip_total = ( ( uint16_t )ip[ 2 ] << 8 ) | ip[ 3 ];         // Total length IP
    uint16_t tcp_payload_len = ip_total - ihl - tcp_hlen;               // Data size
    uint8_t *src_ip_addr  = &ip[ 12 ];      // IP bytes 12-15 = src address
    uint8_t *src_mac_addr = &pkt[ 6 ];      // Ethernet bytes 6-11 = MAC source

    static uint32_t our_seq = 0x12345678;

    if ( dst_port != 80 )
        return;
    if ( memcmp( &ip[ 16 ], local_ip, 4 ) != 0 )        // IP bytes 16-19 = dest. address
        return;

    if ( flags & TCP_FLAG_SYN ) {           // bit SYN pose -> ask open connection
        log_printf( &logger, "TCP SYN recu -> SYN-ACK\r\n" );
        spi_ethernet_send_tcp( eth, local_mac, local_ip, src_mac_addr, src_ip_addr, 80, src_port,
                our_seq, seq + 1, TCP_FLAG_SYN | TCP_FLAG_ACK, NULL, 0 );      // ack_num = seq client + 1 (SYN acknowledgment of receipt)
        our_seq++;
        return;
    }

    if ( ( flags & TCP_FLAG_ACK ) && tcp_payload_len > 0 ) {    // ACK with data = HTTP request received
        uint32_t new_ack = seq + tcp_payload_len;               // All received data bytes are acknowledged.
        uint16_t resp_len = ( uint16_t )( sizeof( http_response ) - 1 );        // -1 to exclude the final '\0'
        log_printf( &logger, "TCP DATA recu -> HTTP 200\r\n" );

        spi_ethernet_send_tcp( eth, local_mac, local_ip, src_mac_addr, src_ip_addr, 80, src_port,
                our_seq, new_ack, TCP_FLAG_ACK, NULL, 0 );      // ACK for received data

        spi_ethernet_send_tcp( eth, local_mac, local_ip, src_mac_addr, src_ip_addr, 80, src_port,
                our_seq, new_ack, TCP_FLAG_ACK | TCP_FLAG_FIN,
                ( uint8_t* )http_response, resp_len );          // HTTP response + close connection (END)
        our_seq += resp_len + 1;                                // +1 because consumes a sequence number
        return;
    }

    if ( flags & TCP_FLAG_FIN ) {       // FIN bit set -> the client closes the connection
        spi_ethernet_send_tcp( eth, local_mac, local_ip, src_mac_addr, src_ip_addr, 80, src_port,
                our_seq, seq + 1, TCP_FLAG_ACK, NULL, 0 );      // +1 because END also uses a client-side sequence number
        log_printf( &logger, "TCP FIN -> ACK\r\n" );
    }
}

// Handler IPv4 (dispatch ICMP/TCP)
static void handle_ip( spi_ethernet_t *eth, uint8_t *pkt, uint16_t len ) {
    uint8_t *ip = &pkt[ 14 ];
    if ( len < 34 )
        return;

    if ( memcmp( &ip[ 16 ], local_ip, 4 ) != 0 )    // bytes 16-19 = IP address dest.
        return;

    if ( ip[ 9 ] == 1 ) {   // byte 9 = protocol field ; 1 = ICMP
        spi_ethernet_handle_icmp( eth, local_mac, local_ip, pkt, len );
        return;
    }

    if ( ip[ 9 ] == 6 ) {   // byte 9 = protocol field ; 6 = TCP
        handle_tcp( eth, pkt, len );
        return;
    }
}

int main( void ) {
    #ifdef PREINIT_SUPPORTED
        preinit( );
    #endif

    // Declarations
    log_cfg_t log_cfg;
    spi_eth_cfg_t eth_cfg;
    const char msg[ ] = "HELLO_FROM_MCU";
    static uint8_t rx_buf[ 700 ];
    uint8_t tx_buf[ 60 ];
    uint8_t rev;
    uint8_t low, high;
    uint8_t link_ok = 0;
    uint8_t i;
    uint8_t last_link;
    uint8_t current_link;
    uint16_t phhid1;
    uint16_t rx_len;
    uint16_t etype;

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

    memcpy( eth_cfg.mac, local_mac, 6 );
    memcpy( eth_cfg.ip, local_ip, 4 );

    if ( spi_eth_configure( &eth, &spi, &eth_cfg ) != 0 ) {
        log_printf( &logger, "SPI/GPIO INIT FAILED\r\n" );
        for( ;; );
    }
    log_printf( &logger, " OK\r\n" );

    // Init Chip
    log_printf( &logger, "NIC INIT..." );
    spi_ethernet_init( &eth, &SPI_ETH_DRIVER );
    log_printf( &logger, " OK\r\n" );

    // SPI
    rev = spi_eth_get_rev( );
    log_printf( &logger, "EREVID = 0x" );
    log_printf( &logger, "%c", hex_digits[ ( rev >> 4 ) & 0x0F ] );
    log_printf( &logger, "%c", hex_digits[ rev & 0x0F ] );
    if ( rev == 0x00 || rev == 0xFF )
        log_printf( &logger, " NOT OK" );
    log_printf( &logger, "\r\n" );

    // PHY ID
    #if SPI_ETH_CHIP == ENC28J60
    spi_eth_phy_read( PHHID1, &low, &high );
    phhid1 = ( uint16_t )high << 8 | low;       // 16-bit word reconstruction
    log_printf( &logger, "PHHID1 = 0x%X%X%X%X (expected 0x0083)%s\r\n",
                ( phhid1 >> 12 ) & 0x0F, ( phhid1 >> 8 ) & 0x0F,
                ( phhid1 >> 4 ) & 0x0F, phhid1 & 0x0F,
                ( high == 0x00 && low == 0x83 ) ? "" : " NOT OK" );   // 0x0083 = expected value for the ENC28J60 PHY
    #endif

    // Waiting link
    log_printf( &logger, "\r\nWAIT LINK (10s max)...\r\n" );
    for ( i = 0; i < 100; i++ ) {       // 100ms x 100 = max 10s timeout
        if ( spi_ethernet_get_link_status( &eth ) ) {
            link_ok = 1;
            log_printf( &logger, ">>> LINK UP\r\n" );
            log_printf( &logger, "\r\n=== HTTP SERVER READY - open http://172.20.22.200 ===\r\n" );
            break;
        }
        log_printf( &logger, "." );
        if ( ( i + 1 ) % 10 == 0 )      // Waiting messages for cable connection
            log_printf( &logger, "\r\n" );
        Delay_ms( 100 );
    }
    if ( !link_ok ) {
        if ( rev == 0x00 || rev == 0xFF )
            log_printf( &logger, "\r\n>>> CHIP NOT DETECTED (SPI/EREVID fail)\r\n" );
        else
            log_printf( &logger, "\r\n>>> LINK DOWN (no Ethernet cable)\r\n" );
    }
    last_link = spi_ethernet_get_link_status( &eth );

    // Frame test EtherType custom 0x88B5
    memset( tx_buf, 0, sizeof( tx_buf ) );
    memset( &tx_buf[ 0 ], 0xFF, 6 );                // MAC dest. = broadcast
    memcpy( &tx_buf[ 6 ], local_mac, 6 );           // MAC source = us
    tx_buf[ 12 ] = 0x88; tx_buf[ 13 ] = 0xB5;       // EtherType = 0x88B5 for testing
    memcpy( &tx_buf[ 14 ], msg, sizeof( msg )-1 );  // Payload following Ethernet 14 bytes header

    while ( 1 ) {
        current_link = spi_ethernet_get_link_status( &eth );
        if ( current_link != last_link ) {
            if ( current_link ) {
                log_printf( &logger, ">>> LINK UP\r\n" );
                log_printf( &logger, "\r\n=== HTTP SERVER READY - open http://172.20.22.200 ===\r\n" );
            }
            else {
                log_printf( &logger, ">>> LINK DOWN\r\n" );
            }
            last_link = current_link;
        }

        rx_len = spi_ethernet_receive( &eth, rx_buf, sizeof( rx_buf ) );
        if ( rx_len < 14 ) {
            Delay_ms( 1 );
            continue;
        }

        etype = ( ( uint16_t )rx_buf[ 12 ] << 8 ) | rx_buf[ 13 ];   // Ethernet bytes 12&13 = EtherType (big-endian)
        if ( etype == 0x0806 )          // 0x0806 = ARP
            spi_ethernet_handle_arp( &eth, local_mac, local_ip, rx_buf, rx_len );
        else if ( etype == 0x0800 )     // 0x0800 = IPv4
            handle_ip( &eth, rx_buf, rx_len );

        Delay_ms( 1 );
    }

    return 0;
}

// ----------------------------------------------------------------------- END
