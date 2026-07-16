#ifdef PREINIT_SUPPORTED
#include "preinit.h"
#endif

#include "spi_ethernet.h"
#include "drv_spi_master.h"
#include "log.h"
#include <delays.h>
#include "board.h"
#include <string.h>
#include <stdint.h>

#define SPI_ETH_CHIP    ENC28J60        // Define your chip

#ifndef MIKROBUS_POSITION_SPI_ETH
    #define MIKROBUS_POSITION_SPI_ETH 1
#endif

#if SPI_ETH_CHIP == ENC28J60
    #include "spi_ethernet_enc28j60.h"
    extern spi_ethernet_driver_t                        enc28j60_driver;
    extern pin_name_t                                   enc28j60_cs_pin;
    #define SPI_ETH_DRIVER                              enc28j60_driver
    #define SPI_ETH_MAP_MIKROBUS( eth, mikrobus )       ENC28J60_MAP_MIKROBUS( eth, mikrobus )
    #define spi_eth_cfg_setup                           enc28j60_cfg_setup
    #define spi_eth_configure                           enc28j60_configure
    #define spi_eth_get_rev                             enc28j60_get_rev
    #define spi_eth_phy_read                            enc28j60_phy_read
    typedef enc28j60_cfg_t                              spi_eth_cfg_t;
#endif

#define TCP_FLAG_FIN 0x01
#define TCP_FLAG_SYN 0x02
#define TCP_FLAG_ACK 0x10

static spi_ethernet_t eth;
static spi_master_t   spi;
static log_t logger;

static const uint8_t local_mac[ 6 ] = { 0x02, 0xDE, 0xAD, 0xBE, 0xEF, 0x01 };
static const uint8_t local_ip[ 4 ]  = { 172, 20, 22, 200 };

// Checksums
static uint16_t ip_checksum( const uint8_t *buf, uint16_t len ) {
    uint32_t sum = 0;
    uint16_t i;

    for ( i = 0; i + 1 < len; i += 2 )
        sum += ( ( uint32_t )buf[ i ] << 8 ) | buf[ i+1 ];  // reconstructs a 16-bit big-endian word (MSB, LSB)

    if ( len & 1 )                                          // odd length -> one byte remains
        sum += ( uint32_t )buf[ len-1 ] << 8;               // Last byte treated as MSB, LSB = 0

    while ( sum >> 16 )                                     // 16-bit carry rollback
        sum = ( sum & 0xFFFF ) + ( sum >> 16 );         

    return ( uint16_t )( ~sum );                            // complement to a final value = checksum
}

static uint16_t tcp_checksum( const uint8_t *src_ip, const uint8_t *dst_ip,
                             const uint8_t *tcp_seg, uint16_t tcp_len ) {
    uint8_t pseudo[ 12 ];
    uint32_t sum = 0;

    memcpy( &pseudo[ 0 ], src_ip, 4 );      // Bytes 0-3  : IP source
    memcpy( &pseudo[ 4 ], dst_ip, 4 );      // Bytes 4-7  : IP dest.
    pseudo[ 8 ]  = 0;                       // Byte 8     : reserve (always 0)
    pseudo[ 9 ]  = 6;                       // Byte 9     : protocol = 6 (TCP)
    pseudo[ 10 ] = tcp_len >> 8;            // Bytes 10-11: TCP segment length (big-endian)
    pseudo[ 11 ] = tcp_len & 0xFF;

    for ( uint8_t i = 0; i + 1 < 12; i += 2 )
        sum += ( ( uint32_t )pseudo[i] << 8 ) | pseudo[ i+1 ];      // 16-bit words of the pseudo-header

    for ( uint16_t i = 0; i + 1 < tcp_len; i += 2 )
        sum += ( ( uint32_t )tcp_seg[i] << 8 ) | tcp_seg[ i+1 ];    // 16-bit words in the TCP segment (header + payload)
        
    if ( tcp_len & 1 ) 
        sum += ( uint32_t )tcp_seg[ tcp_len-1 ] << 8;               // final byte only if the length is odd

    while ( sum >> 16 ) 
        sum = ( sum & 0xFFFF ) + ( sum >> 16 );                     // repli des retenues

    return ( uint16_t )( ~sum );
}

// Sending a TCP segment
static void send_tcp( spi_ethernet_t *eth,
                     const uint8_t *dst_mac, const uint8_t *dst_ip,
                     uint16_t src_port, uint16_t dst_port,
                     uint32_t seq, uint32_t ack_num, uint8_t flags,
                     const uint8_t *payload, uint16_t payload_len ) {

    uint16_t tcp_len   = 20 + payload_len;      // TCP header (20 bytes, no options) + payload
    uint16_t ip_len    = 20 + tcp_len;          // IP header (20 bytes) + TCP segment
    uint16_t total_len = 14 + ip_len;           // Ethernet header (14 bytes) + IP packet
    uint16_t ip_ck;
    uint16_t tcp_ck;
    static uint8_t pkt[ 700 ];
    
    memset( pkt, 0, total_len );

    // Ethernet Header (14 bytes)
    memcpy( &pkt[ 0 ], dst_mac,   6 );          // octets 0-5   : MAC destination
    memcpy( &pkt[ 6 ], local_mac, 6 );          // octets 6-11  : MAC source (nous)
    pkt[ 12 ] = 0x08; pkt[ 13 ] = 0x00;         // octets 12-13 : EtherType = 0x0800 (IPv4)

    // IP Header (20 bytes, offset 14)
    pkt[ 14 ] = 0x45; pkt[ 15 ] = 0x00;                 // Version=4, IHL=5 (20 octets) ; ToS=0
    pkt[ 16 ] = ip_len >> 8; pkt[ 17 ] = ip_len & 0xFF; // Total Length (big-endian)
    pkt[ 18 ] = 0x00; pkt[ 19 ] = 0x01;                 // ID = 1 (fixed, no fragmentation managed)
    pkt[ 20 ] = 0x40; pkt[ 21 ] = 0x00;                 // Flags: Don't Fragment (MSB bit 0x40) ; Fragment Offset = 0
    pkt[ 22 ] = 64;                                     // TTL = 64
    pkt[ 23 ] = 6;                                      // Protocol = 6 (TCP)
    
    ip_ck = ip_checksum(&pkt[ 14 ], 20 );   // IP header checksum (20 bytes) before final filling
    pkt[ 24 ] = 0; pkt[25] = 0;             // Header Checksum : set to 0 before recalculating below
    memcpy(&pkt[ 26 ], local_ip, 4 );       // Bytes 26-29 : IP source (us)
    memcpy(&pkt[ 30 ], dst_ip,   4 );       // Bytes 30-33 : IP dest.
    pkt[ 24 ] = ip_ck >> 8; pkt[ 25 ] = ip_ck & 0xFF;       // Write the IP checksum (big-endian)
    
    // En-tete TCP (20 octets, offset 34)
    pkt[ 34 ] = src_port >> 8;  pkt[ 35 ] = src_port & 0xFF;        // Src port (big-endian)
    pkt[ 36 ] = dst_port >> 8;  pkt[ 37 ] = dst_port & 0xFF;        // Dest. port (big-endian)
    pkt[ 38 ] = seq >> 24; pkt[ 39 ] = seq >> 16;                   // Sequence Number, MSB bytes 
    pkt[ 40 ] = seq >> 8;  pkt[ 41 ] = seq & 0xFF;                  // LSB (big-endian, 4 bytes)
    pkt[ 42 ] = ack_num >> 24; pkt[ 43 ] = ack_num >> 16;           // Acknowledgment Number
    pkt[ 44 ] = ack_num >> 8;  pkt[ 45 ] = ack_num & 0xFF;
    pkt[ 46 ] = 0x50;       // Data Offset = 5 (20 bytes, no options) on the upper 4 bits
    pkt[ 47 ] = flags;      // TCP Flags (SYN/ACK/FIN...)
    pkt[ 48 ] = 0x20; pkt[ 49 ] = 0x00;     // Window Size = 0x2000 = 8192 bytes

    if ( payload && payload_len )
        memcpy( &pkt[ 54 ], payload, payload_len );     // application data following the TCP header (offset 54 = 34+20)

    tcp_ck = tcp_checksum( &pkt[ 26 ], &pkt[ 30 ], &pkt[ 34 ], tcp_len );     // Checksum calculated based on the pseudo-header and the entire segment
    pkt[ 50 ] = tcp_ck >> 8;        // Checksum TCP (big-endian)
    pkt[ 51 ] = tcp_ck & 0xFF;

    spi_ethernet_send( eth, pkt, total_len );
}

static const char http_response[ ] =
    "HTTP/1.1 200 OK\r\n"
    "Content-Type: text/html\r\n"
    "Connection: close\r\n"
    "\r\n"
    "<!DOCTYPE html><html><body>"
    "<h1>Hello from ETH Click chip!</h1>"
    "<p>MikroE SPI-ETHERNET library test works!</p>"
    "<p>IP: 172.20.22.200</p>"
    "</body></html>\r\n";

// Handler ARP
static void handle_arp( spi_ethernet_t *eth, uint8_t *pkt, uint16_t len ) {
    uint8_t *arp = &pkt[ 14 ];
    uint8_t reply[ 42 ];

    if ( len < 14 + 28 ) 
        return;
    if ( arp[ 6 ] != 0x00 || arp[ 7 ] != 0x01 )     // Bytes 6-7 = Opcode ARP ; 0x0001 = request
        return;
    if ( memcmp( &arp[ 24 ], local_ip, 4 ) != 0 )   // Bytes 24-27 = Target Protocol Address (IP dest.)
        return;

    memcpy( &reply[ 0 ], &pkt[ 6 ], 6 );        // dst = sender MAC
    memcpy( &reply[ 6 ], local_mac, 6 );        // src = your MAC
    reply[ 12 ] = 0x08; reply[ 13 ] = 0x06;     // ARP

    reply[ 14 ] = 0x00; reply[ 15 ] = 0x01;     // HW type Ethernet
    reply[ 16 ] = 0x08; reply[ 17 ] = 0x00;     // IPv4
    reply[ 18 ] = 6;    reply[ 19 ] = 4;        // sizes and addresses
    reply[ 20 ] = 0x00; reply[ 21 ] = 0x02;     // opcode = reply

    memcpy( &reply[ 22 ], local_mac, 6 );       // sender MAC = you
    memcpy( &reply[ 28 ], local_ip, 4 );        // sender IP  = you
    memcpy( &reply[ 32 ], &arp[ 8 ], 6 );       // target MAC = sender
    memcpy( &reply[ 36 ], &arp[ 14 ], 4 );      // target IP  = sender

    spi_ethernet_send( eth, reply, 42 );
    log_printf( &logger, "ARP reply sent\r\n" );
}

// Handler ICMP (ping)
static void handle_icmp( spi_ethernet_t *eth, uint8_t *pkt, uint16_t len ) {
    uint8_t *ip = &pkt[ 14 ];
    uint8_t ihl = ( ip[ 0 ] & 0x0F ) * 4;
    uint8_t *icmp = &ip[ ihl ];
    uint16_t ip_total = ( ( uint16_t )ip[ 2 ] << 8 ) | ip[ 3 ];     // Total Length IP (Bytes 2-3, big-endian)
    uint16_t icmp_len = ip_total - ihl;
    uint16_t total = 14 + 20 + icmp_len;        // Ethernet + IP (20 bytes, without options) + ICMP
    uint16_t ip_ck;
    uint16_t icmp_ck;
    static uint8_t reply[ 600 ];

    // Echo request (type 8) ?
    if ( icmp[ 0 ] != 8 )       // ICMP Byte 0 = Type ; 8 = Echo Request
        return;

    // Ethernet header
    memcpy( &reply[ 0 ], &pkt[ 6 ], 6 );
    memcpy( &reply[ 6 ], local_mac, 6 );
    reply[ 12 ] = 0x08; reply[ 13 ] = 0x00;

    // IP header
    memcpy( &reply[ 14 ], ip, 20 );
    reply[ 14+8 ] = 64;     // Byte 8 = TTL
    reply[ 14+9 ] = 1;      // Byte 9 = Protocol = 1 (ICMP)
    memcpy( &reply[ 14+12 ], local_ip, 4 );     // src = you
    memcpy( &reply[ 14+16 ], &ip[ 12 ], 4 );    // dst = sender
    reply[ 14+10 ] = 0; reply[ 14+11 ] = 0;     // Header checksum reset to 0 before recalculation

    ip_ck = ip_checksum( &reply[ 14 ], 20 );
    reply[ 14+10 ] = ip_ck >> 8;                // Write IP checksum (big-endian)
    reply[ 14+11 ] = ip_ck & 0xFF;

    // ICMP echo reply
    memcpy( &reply[ 14+ihl ], icmp, icmp_len );     // Copy the received ICMP message
    reply[ 14+ihl+0 ] = 0;      // type = Echo Reply
    reply[ 14+ihl+1 ] = 0;      // code = 0
    reply[ 14+ihl+2 ] = 0; reply[ 14+ihl+3 ] = 0;   // ICMP checksum reset to 0 before recalculation
    
    icmp_ck = ip_checksum( &reply[ 14+ihl ], icmp_len );
    reply[ 14+ihl+2 ] = icmp_ck >> 8;
    reply[ 14+ihl+3 ] = icmp_ck & 0xFF;

    spi_ethernet_send( eth, reply, total );
    log_printf( &logger, "ICMP Echo Reply sent\r\n" );
}

// Handler TCP/HTTP
static void handle_tcp( spi_ethernet_t *eth, uint8_t *pkt, uint16_t len ) {
    uint8_t *ip = &pkt[ 14 ];
    uint8_t ihl = ( ip[ 0 ] & 0x0F ) * 4;       // IHL in 32-bit words and x4 for the IP header size in bytes (only take the 4 bits on the right for IHL)
    uint8_t *tcp = &ip[ ihl ];                  // TCP header immediately after the IP header
    uint16_t dst_port = ( ( uint16_t )tcp[ 2 ] << 8 ) | tcp[ 3 ];       // TCP bytes 2-3 = dest. port (big-endian)

    if ( dst_port != 80 ) 
        return;
    if ( memcmp( &ip[ 16 ], local_ip, 4 ) != 0 )        // IP bytes 16-19 = dest. address
        return;

    uint16_t src_port = ( ( uint16_t )tcp[ 0 ] << 8 ) | tcp[ 1 ];       // TCP bytes 0-1 = src port
    uint32_t seq = ( ( uint32_t )tcp[ 4 ] << 24) | ( ( uint32_t )tcp[ 5 ] << 16 ) |
                   ( ( uint32_t )tcp[ 6 ] << 8)  | tcp[ 7 ];            // bytes 4-7 = sequence number (big-endian, 32 bits)
    uint8_t  tcp_hlen = ( tcp[ 12 ] >> 4 ) * 4;     // Data offset = the upper 4 bits of byte 12, x4 bytes size
    uint8_t  flags = tcp[ 13 ];                     // byte 13 = flags TCP (SYN/ACK/FIN/...)
    uint16_t ip_total = ( ( uint16_t )ip[ 2 ] << 8 ) | ip[ 3 ];         // Total length IP
    uint16_t tcp_payload_len = ip_total - ihl - tcp_hlen;               // Data size

    uint8_t *src_ip_addr  = &ip[ 12 ];      // IP bytes 12-15 = src address 
    uint8_t *src_mac_addr = &pkt[ 6 ];      // Ethernet bytes 6-11 = MAC source 

    static uint32_t our_seq = 0x12345678;

    if ( flags & TCP_FLAG_SYN ) {           // bit SYN pose -> ask open connection
        log_printf( &logger, "TCP SYN recu -> SYN-ACK\r\n" );
        send_tcp( eth, src_mac_addr, src_ip_addr, 80, src_port,
                 our_seq, seq + 1, TCP_FLAG_SYN | TCP_FLAG_ACK, NULL, 0 );      // ack_num = seq client + 1 (SYN acknowledgment of receipt)
        our_seq++;
        return;
    }

    if (( flags & TCP_FLAG_ACK ) && tcp_payload_len > 0 ) {     // ACK with data = HTTP request received
        uint32_t new_ack = seq + tcp_payload_len;               // All received data bytes are acknowledged.
        uint16_t resp_len = ( uint16_t )( sizeof( http_response ) - 1 );        // -1 to exclude the final '\0'
        log_printf( &logger, "TCP DATA recu -> HTTP 200\r\n" );

        send_tcp( eth, src_mac_addr, src_ip_addr, 80, src_port,
                 our_seq, new_ack, TCP_FLAG_ACK, NULL, 0 );     // ACK for received data

        send_tcp( eth, src_mac_addr, src_ip_addr, 80, src_port,
                 our_seq, new_ack, TCP_FLAG_ACK | TCP_FLAG_FIN,
                 ( const uint8_t* )http_response, resp_len );   // HTTP response + close connection (END)
        our_seq += resp_len + 1;                                // +1 because consumes a sequence number
        return;
    }

    if ( flags & TCP_FLAG_FIN ) {       // FIN bit set -> the client closes the connection
        send_tcp( eth, src_mac_addr, src_ip_addr, 80, src_port,
                 our_seq, seq + 1, TCP_FLAG_ACK, NULL, 0 );     // +1 because END also uses a client-side sequence number
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
        handle_icmp( eth, pkt, len ); 
        return; 
    }

    if ( ip[ 9 ] == 6) {    // byte 9 = protocol field ; 6 = TCP
        handle_tcp( eth, pkt, len );  
        return; 
    }
}

int main(void) {
    #ifdef PREINIT_SUPPORTED
        preinit();
    #endif

    // Declarations
    log_cfg_t log_cfg;
    spi_eth_cfg_t eth_cfg;
    uint8_t rev;
    uint8_t low, high;
    uint16_t phhid1;
    const char *pad;
    uint8_t link_ok = 0;
    uint8_t i;
    uint8_t last_link;
    uint8_t tx_buf[ 60 ];
    const char msg[ ] = "HELLO_FROM_MCU";
    static uint8_t rx_buf[ 1518 ];
    uint8_t current_link;
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
        for(;;);
    }
    log_printf( &logger, " OK\r\n" );

    // Init Chip
    log_printf( &logger, "NIC INIT..." );
    spi_ethernet_init( &eth, &SPI_ETH_DRIVER );
    log_printf( &logger, " OK\r\n" );

    // SPI
    rev = spi_eth_get_rev( );
    log_printf( &logger, "EREVID = 0x%s%X%s\r\n",
            ( rev < 0x10 ) ? "0" : "",      // No padding if value fits into a single hexa digit
            rev,
            ( rev == 0x00 || rev == 0xFF ) ? " NOT OK" : "" );  // 0x00/0xFF = failed SPI reading

    // PHY ID
    spi_eth_phy_read( PHHID1, &low, &high );
    phhid1 = ( uint16_t )high << 8 | low;       // 16-bit word reconstruction
    pad = ( phhid1 < 0x10 ) ? "000" :           // Adding padding depending on the size of the hex value
            ( phhid1 < 0x100 ) ? "00" :
            ( phhid1 < 0x1000 ) ? "0" : "";
    log_printf( &logger, "PHHID1 = 0x%s%X (expected 0x0083)%s\r\n", pad, phhid1,
                (high == 0x00 && low == 0x83) ? "" : " NOT OK" );   // 0x0083 = expected value for the ENC28J60 PHY

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
    if ( !link_ok ) 
        log_printf( &logger, "\r\n>>> LINK DOWN (no Ethernet cable)\r\n" );
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

        rx_len = spi_ethernet_receive( &eth, rx_buf, sizeof( rx_buf ));
        if ( rx_len < 14 ) { 
            Delay_ms( 1 ); 
            continue; 
        }

        etype = ( ( uint16_t )rx_buf[ 12 ] << 8 ) | rx_buf[ 13 ];   // Ethernet bytes 12&13 = EtherType (big-endian)
        if ( etype == 0x0806 )          // 0x0806 = ARP
            handle_arp( &eth, rx_buf, rx_len );
        else if ( etype == 0x0800 )     // 0x0800 = IPv4
            handle_ip( &eth, rx_buf, rx_len );

        Delay_ms( 1 );
    }

    return 0;
}

// ----------------------------------------------------------------------- END
