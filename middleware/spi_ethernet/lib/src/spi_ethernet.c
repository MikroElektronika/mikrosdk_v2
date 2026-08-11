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
 * @file spi_ethernet.c
 * @brief SPI Ethernet Driver.
 */

#include "spi_ethernet.h"
#include <string.h>
static uint8_t tx_pkt[ 400 ];

/* --- Library Initialization --- */
void spi_ethernet_init( spi_ethernet_t *eth, spi_ethernet_driver_t *drv ) {
    if ( !eth || !drv ) return;
    eth->drv = drv;
    if ( eth->drv->init ) eth->drv->init( eth, drv );
}

/* --- Basic Control --- */
int spi_ethernet_reset( spi_ethernet_t *eth ) {
    if ( !eth || !eth->drv || !eth->drv->reset ) return -1;
    return eth->drv->reset( );
}

uint8_t spi_ethernet_get_link_status( spi_ethernet_t *eth ) {
    if ( !eth || !eth->drv || !eth->drv->get_link_status ) return 0;
    return eth->drv->get_link_status( );
}

// /* --- Addressing --- */
int spi_ethernet_set_mac( spi_ethernet_t *eth, uint8_t mac[ 6 ] ) {
    if ( !eth || !eth->drv || !eth->drv->set_mac ) return -1;
    return eth->drv->set_mac( mac );
}

int spi_ethernet_get_mac( spi_ethernet_t *eth, uint8_t mac[ 6 ] ) {
    if ( !eth || !eth->drv || !eth->drv->get_mac ) return -1;
    return eth->drv->get_mac( mac );
}

int spi_ethernet_set_ip( spi_ethernet_t *eth, uint8_t ip[ 4 ] ) {
    if ( !eth || !eth->drv || !eth->drv->set_ip ) return -1;
    return eth->drv->set_ip( ip );
}

int spi_ethernet_get_ip( spi_ethernet_t *eth, uint8_t ip[ 4 ] ) {
    if ( !eth || !eth->drv || !eth->drv->get_ip ) return -1;
    return eth->drv->get_ip( ip );
}

/* --- Data Transfer --- */
int spi_ethernet_send( spi_ethernet_t *eth, uint8_t *buf, uint16_t len ) {
    if ( !eth || !eth->drv || !eth->drv->send_packet ) return -1;
    return eth->drv->send_packet( eth, buf, len );
}

int spi_ethernet_receive( spi_ethernet_t *eth, uint8_t *buf, uint16_t len ) {
    if ( !eth || !eth->drv || !eth->drv->read_packet ) return -1;
    return eth->drv->read_packet( eth, buf, len );
}

uint16_t spi_ethernet_available( spi_ethernet_t *eth ) {
    if ( !eth || !eth->drv || !eth->drv->available ) return 0;
    return eth->drv->available( eth );
}

// Checksums
static uint16_t ip_checksum( uint8_t *buf, uint16_t len ) {
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

static uint16_t tcp_checksum( uint8_t *src_ip, uint8_t *dst_ip,
                            uint8_t *tcp_seg, uint16_t tcp_len ) {
    uint8_t pseudo[ 12 ];
    uint32_t sum = 0;
    uint8_t i8;
    uint16_t i16;

    memcpy( &pseudo[ 0 ], src_ip, 4 );      // Bytes 0-3  : IP source
    memcpy( &pseudo[ 4 ], dst_ip, 4 );      // Bytes 4-7  : IP dest.
    pseudo[ 8 ]  = 0;                       // Byte 8     : reserve (always 0)
    pseudo[ 9 ]  = 6;                       // Byte 9     : protocol = 6 (TCP)
    pseudo[ 10 ] = tcp_len >> 8;            // Bytes 10-11: TCP segment length (big-endian)
    pseudo[ 11 ] = tcp_len & 0xFF;

    for ( i8 = 0; i8 + 1 < 12; i8 += 2 )
        sum += ( ( uint32_t )pseudo[ i8 ] << 8 ) | pseudo[ i8+1 ];      // 16-bit words of the pseudo-header

    for ( i16 = 0; i16 + 1 < tcp_len; i16 += 2 )
        sum += ( ( uint32_t )tcp_seg[ i16 ] << 8 ) | tcp_seg[ i16+1 ];    // 16-bit words in the TCP segment (header + payload)

    if ( tcp_len & 1 )
        sum += ( uint32_t )tcp_seg[ tcp_len-1 ] << 8;               // final byte only if the length is odd

    while ( sum >> 16 )
        sum = ( sum & 0xFFFF ) + ( sum >> 16 );

    return ( uint16_t )( ~sum );
}

static uint16_t udp_checksum( uint8_t *src_ip, uint8_t *dst_ip,
                            uint8_t *udp_seg, uint16_t udp_len ) {
    uint8_t pseudo[ 12 ];
    uint32_t sum = 0;
    uint8_t i8;
    uint16_t i16;

    memcpy( &pseudo[ 0 ], src_ip, 4 );
    memcpy( &pseudo[ 4 ], dst_ip, 4 );
    pseudo[ 8 ]  = 0;
    pseudo[ 9 ]  = 17;                      // Protocol = 17 (UDP)
    pseudo[ 10 ] = udp_len >> 8;
    pseudo[ 11 ] = udp_len & 0xFF;

    for ( i8 = 0; i8 + 1 < 12; i8 += 2 )
        sum += ( ( uint32_t )pseudo[ i8 ] << 8 ) | pseudo[ i8+1 ];

    for ( i16 = 0; i16 + 1 < udp_len; i16 += 2 )
        sum += ( ( uint32_t )udp_seg[ i16 ] << 8 ) | udp_seg[ i16+1 ];

    if ( udp_len & 1 )
        sum += ( uint32_t )udp_seg[ udp_len-1 ] << 8;

    while ( sum >> 16 )
        sum = ( sum & 0xFFFF ) + ( sum >> 16 );

    return ( uint16_t )( ~sum );
}

// Sending a TCP segment
void spi_ethernet_send_tcp( spi_ethernet_t *eth, uint8_t *local_mac, uint8_t *local_ip,
                    uint8_t *dst_mac, uint8_t *dst_ip,
                    uint16_t src_port, uint16_t dst_port,
                    uint32_t seq, uint32_t ack_num, uint8_t flags,
                    uint8_t *payload, uint16_t payload_len ) {

    uint16_t tcp_len   = 20 + payload_len;      // TCP header (20 bytes, no options) + payload
    uint16_t ip_len    = 20 + tcp_len;          // IP header (20 bytes) + TCP segment
    uint16_t total_len = 14 + ip_len;           // Ethernet header (14 bytes) + IP packet
    uint16_t ip_ck;
    uint16_t tcp_ck;

    memset( tx_pkt, 0, total_len );

    // Ethernet Header (14 bytes)
    memcpy( &tx_pkt[ 0 ], dst_mac,   6 );        // octets 0-5   : MAC destination
    memcpy( &tx_pkt[ 6 ], local_mac, 6 );        // octets 6-11  : MAC source (nous)
    tx_pkt[ 12 ] = 0x08; tx_pkt[ 13 ] = 0x00;    // octets 12-13 : EtherType = 0x0800 (IPv4)

    // IP Header (20 bytes, offset 14)
    tx_pkt[ 14 ] = 0x45; tx_pkt[ 15 ] = 0x00;                   // Version=4, IHL=5 (20 octets) ; ToS=0
    tx_pkt[ 16 ] = ip_len >> 8; tx_pkt[ 17 ] = ip_len & 0xFF;   // Total Length (big-endian)
    tx_pkt[ 18 ] = 0x00; tx_pkt[ 19 ] = 0x01;                   // ID = 1 (fixed, no fragmentation managed)
    tx_pkt[ 20 ] = 0x40; tx_pkt[ 21 ] = 0x00;                   // Flags: Don't Fragment (MSB bit 0x40) ; Fragment Offset = 0
    tx_pkt[ 22 ] = 64;                                          // TTL = 64
    tx_pkt[ 23 ] = 6;                                           // Protocol = 6 (TCP)

    tx_pkt[ 24 ] = 0; tx_pkt[ 25 ] = 0;              // Header Checksum : set to 0 before recalculating below
    memcpy( &tx_pkt[ 26 ], local_ip, 4 );            // Bytes 26-29 : IP source (us)
    memcpy( &tx_pkt[ 30 ], dst_ip,   4 );            // Bytes 30-33 : IP dest.
    ip_ck = ip_checksum( &tx_pkt[ 14 ], 20 );        // IP header checksum (20 bytes) before final filling
    tx_pkt[ 24 ] = ip_ck >> 8; tx_pkt[ 25 ] = ip_ck & 0xFF;       // Write the IP checksum (big-endian)

    // En-tete TCP (20 octets, offset 34)
    tx_pkt[ 34 ] = src_port >> 8;  tx_pkt[ 35 ] = src_port & 0xFF;        // Src port (big-endian)
    tx_pkt[ 36 ] = dst_port >> 8;  tx_pkt[ 37 ] = dst_port & 0xFF;        // Dest. port (big-endian)
    tx_pkt[ 38 ] = seq >> 24; tx_pkt[ 39 ] = seq >> 16;                   // Sequence Number, MSB bytes
    tx_pkt[ 40 ] = seq >> 8;  tx_pkt[ 41 ] = seq & 0xFF;                  // LSB (big-endian, 4 bytes)
    tx_pkt[ 42 ] = ack_num >> 24; tx_pkt[ 43 ] = ack_num >> 16;           // Acknowledgment Number
    tx_pkt[ 44 ] = ack_num >> 8;  tx_pkt[ 45 ] = ack_num & 0xFF;
    tx_pkt[ 46 ] = 0x50;                            // Data Offset = 5 (20 bytes, no options) on the upper 4 bits
    tx_pkt[ 47 ] = flags;                           // TCP Flags (SYN/ACK/FIN...)
    tx_pkt[ 48 ] = 0x20; tx_pkt[ 49 ] = 0x00;       // Window Size = 0x2000 = 8192 bytes

    if ( payload && payload_len )
        memcpy( &tx_pkt[ 54 ], payload, payload_len );     // Application data following the TCP header (offset 54 = 34+20)

    tx_pkt[ 50 ] = 0;
    tx_pkt[ 51 ] = 0;

    tcp_ck = tcp_checksum( &tx_pkt[ 26 ], &tx_pkt[ 30 ], &tx_pkt[ 34 ], tcp_len );     // Checksum calculated based on the pseudo-header and the entire segment
    tx_pkt[ 50 ] = tcp_ck >> 8;        // Checksum TCP (big-endian)
    tx_pkt[ 51 ] = tcp_ck & 0xFF;

    spi_ethernet_send( eth, tx_pkt, total_len );
}

void spi_ethernet_send_udp( spi_ethernet_t *eth, uint8_t *local_mac,
                    uint8_t *dst_mac, uint8_t *dst_ip, uint8_t *src_ip,
                    uint16_t src_port, uint16_t dst_port,
                    uint8_t *payload, uint16_t payload_len ) {

    uint16_t udp_len   = 8 + payload_len;       // UDP header (8 bytes) + payload
    uint16_t ip_len    = 20 + udp_len;          // IP header (20 bytes) + UDP segment
    uint16_t total_len = 14 + ip_len;           // Ethernet header (14 bytes) + IP packet
    uint16_t ip_ck;
    uint16_t udp_ck;

    memset( tx_pkt, 0, total_len );

    // Ethernet Header (14 bytes)
    memcpy( &tx_pkt[ 0 ], dst_mac,   6 );
    memcpy( &tx_pkt[ 6 ], local_mac, 6 );
    tx_pkt[ 12 ] = 0x08; tx_pkt[ 13 ] = 0x00;

    // IP Header (20 bytes, offset 14)
    tx_pkt[ 14 ] = 0x45; tx_pkt[ 15 ] = 0x00;
    tx_pkt[ 16 ] = ip_len >> 8; tx_pkt[ 17 ] = ip_len & 0xFF;
    tx_pkt[ 18 ] = 0x00; tx_pkt[ 19 ] = 0x01;
    tx_pkt[ 20 ] = 0x40; tx_pkt[ 21 ] = 0x00;
    tx_pkt[ 22 ] = 64;
    tx_pkt[ 23 ] = 17;                          // Protocole = 17 (UDP)

    tx_pkt[ 24 ] = 0; tx_pkt[ 25 ] = 0;
    memcpy( &tx_pkt[ 26 ], src_ip, 4 );
    memcpy( &tx_pkt[ 30 ], dst_ip,   4 );
    ip_ck = ip_checksum( &tx_pkt[ 14 ], 20 );
    tx_pkt[ 24 ] = ip_ck >> 8; tx_pkt[ 25 ] = ip_ck & 0xFF;

    // UDP Header (8 bytes, offset 34)
    tx_pkt[ 34 ] = src_port >> 8;  tx_pkt[ 35 ] = src_port & 0xFF;
    tx_pkt[ 36 ] = dst_port >> 8;  tx_pkt[ 37 ] = dst_port & 0xFF;
    tx_pkt[ 38 ] = udp_len >> 8;   tx_pkt[ 39 ] = udp_len & 0xFF;   // UDP Length (header+data)
    tx_pkt[ 40 ] = 0; tx_pkt[ 41 ] = 0;                             // Checksum reset avant calcul

    if ( payload && payload_len )
        memcpy( &tx_pkt[ 42 ], payload, payload_len );              // offset 42 = 34+8

    udp_ck = udp_checksum( &tx_pkt[ 26 ], &tx_pkt[ 30 ], &tx_pkt[ 34 ], udp_len );
    tx_pkt[ 40 ] = udp_ck >> 8;
    tx_pkt[ 41 ] = udp_ck & 0xFF;

    spi_ethernet_send( eth, tx_pkt, total_len );
}

// Handler ARP
void spi_ethernet_handle_arp( spi_ethernet_t *eth, uint8_t *local_mac, uint8_t *local_ip,
                          uint8_t *pkt, uint16_t len ) {
    uint8_t *arp = &pkt[ 14 ];
    uint8_t tx_pkt[ 42 ];

    if ( len < 14 + 28 )
        return;
    if ( arp[ 6 ] != 0x00 || arp[ 7 ] != 0x01 )     // Bytes 6-7 = Opcode ARP ; 0x0001 = request
        return;
    if ( memcmp( &arp[ 24 ], local_ip, 4 ) != 0 )   // Bytes 24-27 = Target Protocol Address (IP dest.)
        return;

    memcpy( &tx_pkt[ 0 ], &pkt[ 6 ], 6 );       // dst = sender MAC
    memcpy( &tx_pkt[ 6 ], local_mac, 6 );       // src = your MAC
    tx_pkt[ 12 ] = 0x08; tx_pkt[ 13 ] = 0x06;   // ARP

    tx_pkt[ 14 ] = 0x00; tx_pkt[ 15 ] = 0x01;   // HW type Ethernet
    tx_pkt[ 16 ] = 0x08; tx_pkt[ 17 ] = 0x00;   // IPv4
    tx_pkt[ 18 ] = 6;    tx_pkt[ 19 ] = 4;      // sizes and addresses
    tx_pkt[ 20 ] = 0x00; tx_pkt[ 21 ] = 0x02;   // opcode = tx_pkt

    memcpy( &tx_pkt[ 22 ], local_mac, 6 );      // sender MAC = you
    memcpy( &tx_pkt[ 28 ], local_ip, 4 );       // sender IP  = you
    memcpy( &tx_pkt[ 32 ], &arp[ 8 ], 6 );      // target MAC = sender
    memcpy( &tx_pkt[ 36 ], &arp[ 14 ], 4 );     // target IP  = sender

    spi_ethernet_send( eth, tx_pkt, 42 );
}

// Handler ICMP (ping)
void spi_ethernet_handle_icmp( spi_ethernet_t *eth, uint8_t *local_mac, uint8_t *local_ip,
                           uint8_t *pkt, uint16_t len ) {
    uint8_t *ip = &pkt[ 14 ];
    uint8_t ihl = ( ip[ 0 ] & 0x0F ) * 4;
    uint8_t *icmp = &ip[ ihl ];
    uint16_t ip_total = ( ( uint16_t )ip[ 2 ] << 8 ) | ip[ 3 ];     // Total Length IP (Bytes 2-3, big-endian)
    uint16_t icmp_len = ip_total - ihl;
    uint16_t total = 14 + 20 + icmp_len;        // Ethernet + IP (20 bytes, without options) + ICMP
    uint16_t ip_ck;
    uint16_t icmp_ck;

    // Echo request (type 8) ?
    if ( icmp[ 0 ] != 8 )       // ICMP Byte 0 = Type ; 8 = Echo Request
        return;

    // Ethernet header
    memcpy( &tx_pkt[ 0 ], &pkt[ 6 ], 6 );
    memcpy( &tx_pkt[ 6 ], local_mac, 6 );
    tx_pkt[ 12 ] = 0x08; tx_pkt[ 13 ] = 0x00;

    // IP header
    memcpy( &tx_pkt[ 14 ], ip, 20 );
    tx_pkt[ 14+8 ] = 64;     // Byte 8 = TTL
    tx_pkt[ 14+9 ] = 1;      // Byte 9 = Protocol = 1 (ICMP)
    memcpy( &tx_pkt[ 14+12 ], local_ip, 4 );        // src = you
    memcpy( &tx_pkt[ 14+16 ], &ip[ 12 ], 4 );       // dst = sender
    tx_pkt[ 14+10 ] = 0; tx_pkt[ 14+11 ] = 0;       // Header checksum reset to 0 before recalculation

    ip_ck = ip_checksum( &tx_pkt[ 14 ], 20 );
    tx_pkt[ 14+10 ] = ip_ck >> 8;                   // Write IP checksum (big-endian)
    tx_pkt[ 14+11 ] = ip_ck & 0xFF;

    // ICMP echo tx_pkt
    memcpy( &tx_pkt[ 14+ihl ], icmp, icmp_len );    // Copy the received ICMP message
    tx_pkt[ 14+ihl+0 ] = 0;      // type = Echo tx_pkt
    tx_pkt[ 14+ihl+1 ] = 0;      // code = 0
    tx_pkt[ 14+ihl+2 ] = 0; tx_pkt[ 14+ihl+3 ] = 0; // ICMP checksum reset to 0 before recalculation

    icmp_ck = ip_checksum( &tx_pkt[ 14+ihl ], icmp_len );
    tx_pkt[ 14+ihl+2 ] = icmp_ck >> 8;
    tx_pkt[ 14+ihl+3 ] = icmp_ck & 0xFF;

    spi_ethernet_send( eth, tx_pkt, total );
}

void spi_ethernet_dhcp_send( spi_ethernet_t *eth, uint8_t msg_type, uint8_t *local_mac,
                         uint8_t *dhcp_src_ip, uint8_t *dhcp_offered_ip,
                         uint8_t *dhcp_server_ip, uint32_t dhcp_xid ) {
    uint8_t bcast_mac[ 6 ] = { 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF };
    uint8_t bcast_ip[ 4 ]  = { 255, 255, 255, 255 };
    uint8_t dhcp_pkt[ 300 ];
    uint16_t opt = 240;   // options offset, right after the 240 fixed DHCP bytes

    memset( dhcp_pkt, 0, sizeof( dhcp_pkt ) );

    // Fixed DHCP fields (RFC 2131)
    dhcp_pkt[ 0 ] = DHCP_OP_REQUEST;         // op = 1 (client -> server request)
    dhcp_pkt[ 1 ] = DHCP_HTYPE_ETH;          // htype = 1 (Ethernet)
    dhcp_pkt[ 2 ] = DHCP_HLEN_ETH;           // hlen = 6 (MAC address size)
    dhcp_pkt[ 3 ] = 0;                       // hops = 0

    dhcp_pkt[ 4 ]  = dhcp_xid >> 24;         // xid (4 bytes, big-endian)
    dhcp_pkt[ 5 ]  = dhcp_xid >> 16;
    dhcp_pkt[ 6 ]  = dhcp_xid >> 8;
    dhcp_pkt[ 7 ]  = dhcp_xid & 0xFF;

    dhcp_pkt[ 8 ] = 0; dhcp_pkt[ 9 ] = 0;    // secs = 0
    dhcp_pkt[ 10 ] = 0x80; dhcp_pkt[ 11 ] = 0x00;   // flags: BROADCAST bit set (0x8000) -> ask for a broadcast reply

    memcpy( &dhcp_pkt[ 28 ], local_mac, 6 ); // chaddr (28-43) = our MAC (16 bytes total, only first 6 used)

    // sname (44-107) and file (108-235) left at 0

    // Magic cookie (236-239)
    dhcp_pkt[ 236 ] = DHCP_MAGIC_COOKIE_0;
    dhcp_pkt[ 237 ] = DHCP_MAGIC_COOKIE_1;
    dhcp_pkt[ 238 ] = DHCP_MAGIC_COOKIE_2;
    dhcp_pkt[ 239 ] = DHCP_MAGIC_COOKIE_3;

    // DHCP Option
    // Option 53: DHCP Message Type
    dhcp_pkt[ opt++ ] = 53; dhcp_pkt[ opt++ ] = 1; dhcp_pkt[ opt++ ] = msg_type;

    // Option 61: Client identifier (type 1 = Ethernet + MAC)
    dhcp_pkt[ opt++ ] = 61; dhcp_pkt[ opt++ ] = 7; dhcp_pkt[ opt++ ] = 1;
    memcpy( &dhcp_pkt[ opt ], local_mac, 6 ); opt += 6;

    if ( msg_type == DHCP_MSG_REQUEST ) {
        // Option 50: Requested IP Address (the IP offered by the server)
        dhcp_pkt[ opt++ ] = 50; dhcp_pkt[ opt++ ] = 4;
        memcpy( &dhcp_pkt[ opt ], dhcp_offered_ip, 4 ); opt += 4;

        // Option 54: DHCP Server Identifier (mandatory in a REQUEST)
        dhcp_pkt[ opt++ ] = 54; dhcp_pkt[ opt++ ] = 4;
        memcpy( &dhcp_pkt[ opt ], dhcp_server_ip, 4 ); opt += 4;
    }

    // Option 55: Parameter Request List (asking for subnet mask + router, common practice)
    dhcp_pkt[ opt++ ] = 55; dhcp_pkt[ opt++ ] = 2; dhcp_pkt[ opt++ ] = 1; dhcp_pkt[ opt++ ] = 3;

    // Option 255: End
    dhcp_pkt[ opt++ ] = 255;

    spi_ethernet_send_udp( eth, local_mac, bcast_mac, bcast_ip, dhcp_src_ip, DHCP_CLIENT_PORT, DHCP_SERVER_PORT, dhcp_pkt, opt );
}

static uint8_t *dhcp_find_option( uint8_t *options, uint16_t options_len, uint8_t opt_code, uint8_t *out_len ) {
    uint16_t i = 0;
    while ( i < options_len ) {
        if ( options[ i ] == 255 )              // end of options
            break;
        if ( options[ i ] == 0 ) {              // padding
            i++;
            continue;
        }
        if ( options[ i ] == opt_code ) {
            *out_len = options[ i + 1 ];
            return &options[ i + 2 ];
        }
        i += 2 + options[ i + 1 ];              // skip code(1) + len(1) + data(len)
    }
    return NULL;
}

uint8_t spi_ethernet_handle_dhcp( uint8_t *pkt, uint16_t len, uint32_t dhcp_xid,
                              uint8_t *dhcp_offered_ip, uint8_t *dhcp_server_ip,
                              uint8_t *local_ip ) {
    uint8_t *ip  = &pkt[ 14 ];
    uint8_t ihl  = ( ip[ 0 ] & 0x0F ) * 4;
    uint8_t *udp = &ip[ ihl ];
    uint8_t *dhcp = &udp[ 8 ];                  // DHCP payload right after the UDP header (8 bytes)
    uint16_t udp_len = ( ( uint16_t )udp[ 4 ] << 8 ) | udp[ 5 ];
    uint16_t dhcp_len = udp_len - 8;
    uint8_t *options = &dhcp[ 240 ];                    // options right after the magic cookie
    uint16_t options_len = dhcp_len - 240;
    uint8_t *msg_type_ptr;
    uint8_t opt_len;
    uint16_t dst_port_check = ( ( uint16_t )udp[ 2 ] << 8 ) | udp[ 3 ];
    if ( dst_port_check != DHCP_CLIENT_PORT )
        return 0;

    if ( dhcp_len < 240 )
        return 0;

    // Check this reply matches our transaction (xid)
    if ( dhcp[ 4 ] != ( uint8_t )( dhcp_xid >> 24 ) || dhcp[ 5 ] != ( uint8_t )( dhcp_xid >> 16 ) ||
         dhcp[ 6 ] != ( uint8_t )( dhcp_xid >> 8 )  || dhcp[ 7 ] != ( uint8_t )( dhcp_xid & 0xFF ) )
        return 0;

    msg_type_ptr = dhcp_find_option( options, options_len, 53, &opt_len );
    if ( !msg_type_ptr )
        return 0;

    if ( *msg_type_ptr == DHCP_MSG_OFFER ) {
        memcpy( dhcp_offered_ip, &dhcp[ 16 ], 4 );      // yiaddr = offered IP (offset 16-19)

        // Option 54 = DHCP Server Identifier
        {
            uint8_t *srv = dhcp_find_option( options, options_len, 54, &opt_len );
            if ( srv )
                memcpy( dhcp_server_ip, srv, 4 );
        }
        return 1;
    }

    if ( *msg_type_ptr == DHCP_MSG_ACK ) {
        memcpy( local_ip, &dhcp[ 16 ], 4 );             // yiaddr = confirmed IP -> becomes our IP
        return 2;
    }

    if ( *msg_type_ptr == DHCP_MSG_NAK )
        return 3;

    return 0;
}

// ------------------------------------------------------------------------ END
