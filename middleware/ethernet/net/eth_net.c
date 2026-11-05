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
 * @file eth_net.c
 * @brief Minimal IPv4 protocol helpers (ARP, ICMP echo, TCP, UDP, DHCP client).
 */

#include "eth_net.h"
#include <string.h>

// Offsets in an Ethernet/IPv4 frame without IP options
#define IP_OFFSET           ETH_NET_ETH_HEADER_SIZE                             // 14
#define L4_OFFSET           ( IP_OFFSET + ETH_NET_IP_HEADER_SIZE )             // 34
#define TCP_DATA_OFFSET     ( L4_OFFSET + ETH_NET_TCP_HEADER_SIZE )            // 54
#define UDP_DATA_OFFSET     ( L4_OFFSET + ETH_NET_UDP_HEADER_SIZE )            // 42

#define ARP_PACKET_SIZE     28
#define ARP_FRAME_SIZE      ( ETH_NET_ETH_HEADER_SIZE + ARP_PACKET_SIZE )      // 42
#define ICMP_HEADER_SIZE    8
#define ICMP_ECHO_REQUEST   8
#define ICMP_ECHO_REPLY     0

#define DHCP_FIXED_SIZE     240                                                 // Fixed fields + magic cookie
#define DHCP_OPTIONS_SIZE   29                                                  // Options 53, 61, 50, 54, 55, 255
#define DHCP_FRAME_SIZE     ( UDP_DATA_OFFSET + DHCP_FIXED_SIZE + DHCP_OPTIONS_SIZE )
#define DHCP_OP_REQUEST     1
#define DHCP_HTYPE_ETH      1
#define DHCP_HLEN_ETH       6

#if ETH_NET_TX_BUF_SIZE < DHCP_FRAME_SIZE
    #error "ETH_NET_TX_BUF_SIZE is too small for a DHCP message"
#endif

static const uint8_t dhcp_magic_cookie[ 4 ] = { 0x63, 0x82, 0x53, 0x63 };

// Shared TX buffer, every frame is built here and sent right away
static uint8_t tx_pkt[ ETH_NET_TX_BUF_SIZE ];

// Byte order helpers (network order = big-endian)
static void put_be16( uint8_t *buf, uint16_t val ) {
    buf[ 0 ] = ( uint8_t )( val >> 8 );
    buf[ 1 ] = ( uint8_t )( val & 0xFF );
}

static void put_be32( uint8_t *buf, uint32_t val ) {
    buf[ 0 ] = ( uint8_t )( val >> 24 );
    buf[ 1 ] = ( uint8_t )( val >> 16 );
    buf[ 2 ] = ( uint8_t )( val >> 8 );
    buf[ 3 ] = ( uint8_t )( val & 0xFF );
}

static uint16_t get_be16( uint8_t *buf ) {
    return ( ( uint16_t )buf[ 0 ] << 8 ) | buf[ 1 ];
}

// Checksums (RFC 1071)
static uint32_t checksum_add( uint32_t sum, uint8_t *buf, uint16_t len ) {
    uint16_t i;

    for ( i = 0; i + 1 < len; i += 2 )
        sum += ( ( uint32_t )buf[ i ] << 8 ) | buf[ i + 1 ];    // 16-bit big-endian words
    if ( len & 1 )
        sum += ( uint32_t )buf[ len - 1 ] << 8;                 // odd length: last byte is the MSB, LSB = 0
    return sum;
}

static uint16_t checksum_fold( uint32_t sum ) {
    while ( sum >> 16 )                                         // 16-bit carry rollback
        sum = ( sum & 0xFFFF ) + ( sum >> 16 );
    return ( uint16_t )( ~sum );
}

static uint16_t ip_checksum( uint8_t *buf, uint16_t len ) {
    return checksum_fold( checksum_add( 0, buf, len ) );
}

// TCP/UDP checksum, covers the pseudo-header and the whole segment
static uint16_t l4_checksum( uint8_t *src_ip, uint8_t *dst_ip, uint8_t proto, uint8_t *seg, uint16_t len ) {
    uint8_t pseudo[ 12 ];

    memcpy( &pseudo[ 0 ], src_ip, 4 );
    memcpy( &pseudo[ 4 ], dst_ip, 4 );
    pseudo[ 8 ] = 0;
    pseudo[ 9 ] = proto;
    put_be16( &pseudo[ 10 ], len );

    return checksum_fold( checksum_add( checksum_add( 0, pseudo, 12 ), seg, len ) );
}

// Ethernet + IPv4 header (20 bytes, no options) at the start of tx_pkt
static void build_eth_ipv4( uint8_t *dst_mac, uint8_t *src_mac, uint8_t *src_ip, uint8_t *dst_ip,
                            uint8_t proto, uint16_t ip_len ) {
    uint8_t *ip = &tx_pkt[ IP_OFFSET ];

    memcpy( &tx_pkt[ 0 ], dst_mac, 6 );
    memcpy( &tx_pkt[ 6 ], src_mac, 6 );
    put_be16( &tx_pkt[ 12 ], ETH_NET_ETHERTYPE_IPV4 );

    ip[ 0 ] = 0x45;                     // Version = 4, IHL = 5 (20 bytes)
    ip[ 1 ] = 0x00;                     // ToS
    put_be16( &ip[ 2 ], ip_len );       // Total length
    put_be16( &ip[ 4 ], 1 );            // ID = 1 (fixed, no fragmentation)
    ip[ 6 ] = 0x40; ip[ 7 ] = 0x00;     // Don't Fragment, offset 0
    ip[ 8 ] = 64;                       // TTL
    ip[ 9 ] = proto;
    ip[ 10 ] = 0; ip[ 11 ] = 0;         // Checksum, computed below
    memcpy( &ip[ 12 ], src_ip, 4 );
    memcpy( &ip[ 16 ], dst_ip, 4 );
    put_be16( &ip[ 10 ], ip_checksum( ip, ETH_NET_IP_HEADER_SIZE ) );
}

// UDP header + checksum and send, the payload must already be at tx_pkt[ UDP_DATA_OFFSET ]
static uint16_t send_udp_frame( eth_transport_t *eth, uint8_t *local_mac,
                                uint8_t *dst_mac, uint8_t *dst_ip, uint8_t *src_ip,
                                uint16_t src_port, uint16_t dst_port, uint16_t payload_len ) {
    uint8_t *udp = &tx_pkt[ L4_OFFSET ];
    uint16_t udp_len = ETH_NET_UDP_HEADER_SIZE + payload_len;
    uint16_t ck;

    build_eth_ipv4( dst_mac, local_mac, src_ip, dst_ip, ETH_NET_IP_PROTO_UDP,
                    ETH_NET_IP_HEADER_SIZE + udp_len );

    put_be16( &udp[ 0 ], src_port );
    put_be16( &udp[ 2 ], dst_port );
    put_be16( &udp[ 4 ], udp_len );
    udp[ 6 ] = 0; udp[ 7 ] = 0;

    ck = l4_checksum( &tx_pkt[ IP_OFFSET + 12 ], &tx_pkt[ IP_OFFSET + 16 ], ETH_NET_IP_PROTO_UDP, udp, udp_len );
    if ( !ck )
        ck = 0xFFFF;                    // RFC 768: 0 means "no checksum", send all ones instead
    put_be16( &udp[ 6 ], ck );

    return eth_transport_send( eth, tx_pkt, UDP_DATA_OFFSET + payload_len );
}

// Returns the value of a DHCP option and its length, NULL if missing or truncated
static uint8_t *dhcp_find_option( uint8_t *options, uint16_t options_len, uint8_t opt_code, uint8_t *out_len ) {
    uint16_t i = 0;

    while ( i < options_len ) {
        if ( options[ i ] == 255 )              // end of options
            break;
        if ( options[ i ] == 0 ) {              // padding
            i++;
            continue;
        }
        if ( i + 1 >= options_len || i + 2 + options[ i + 1 ] > options_len )
            break;                              // option runs past the end of the packet
        if ( options[ i ] == opt_code ) {
            *out_len = options[ i + 1 ];
            return &options[ i + 2 ];
        }
        i += 2 + options[ i + 1 ];              // skip code(1) + len(1) + data(len)
    }
    return NULL;
}

uint16_t eth_net_send_tcp( eth_transport_t *eth, uint8_t *local_mac, uint8_t *local_ip,
                           uint8_t *dst_mac, uint8_t *dst_ip,
                           uint16_t src_port, uint16_t dst_port,
                           uint32_t seq, uint32_t ack_num, uint8_t flags,
                           uint8_t *payload, uint16_t payload_len ) {
    uint8_t *tcp = &tx_pkt[ L4_OFFSET ];
    uint16_t tcp_len;

    if ( !payload )
        payload_len = 0;
    if ( payload_len > ETH_NET_TX_BUF_SIZE - TCP_DATA_OFFSET )
        return 0;
    tcp_len = ETH_NET_TCP_HEADER_SIZE + payload_len;

    build_eth_ipv4( dst_mac, local_mac, local_ip, dst_ip, ETH_NET_IP_PROTO_TCP,
                    ETH_NET_IP_HEADER_SIZE + tcp_len );

    put_be16( &tcp[ 0 ], src_port );
    put_be16( &tcp[ 2 ], dst_port );
    put_be32( &tcp[ 4 ], seq );
    put_be32( &tcp[ 8 ], ack_num );
    tcp[ 12 ] = 0x50;                   // Data offset = 5 (20 bytes, no options)
    tcp[ 13 ] = flags;
    put_be16( &tcp[ 14 ], 0x2000 );     // Window = 8192 bytes
    tcp[ 16 ] = 0; tcp[ 17 ] = 0;       // Checksum, computed below
    tcp[ 18 ] = 0; tcp[ 19 ] = 0;       // Urgent pointer

    if ( payload_len )
        memcpy( &tx_pkt[ TCP_DATA_OFFSET ], payload, payload_len );

    put_be16( &tcp[ 16 ], l4_checksum( &tx_pkt[ IP_OFFSET + 12 ], &tx_pkt[ IP_OFFSET + 16 ],
                                       ETH_NET_IP_PROTO_TCP, tcp, tcp_len ) );

    return eth_transport_send( eth, tx_pkt, TCP_DATA_OFFSET + payload_len );
}

uint16_t eth_net_send_udp( eth_transport_t *eth, uint8_t *local_mac,
                           uint8_t *dst_mac, uint8_t *dst_ip, uint8_t *src_ip,
                           uint16_t src_port, uint16_t dst_port,
                           uint8_t *payload, uint16_t payload_len ) {
    if ( !payload )
        payload_len = 0;
    if ( payload_len > ETH_NET_TX_BUF_SIZE - UDP_DATA_OFFSET )
        return 0;

    if ( payload_len )
        memcpy( &tx_pkt[ UDP_DATA_OFFSET ], payload, payload_len );

    return send_udp_frame( eth, local_mac, dst_mac, dst_ip, src_ip, src_port, dst_port, payload_len );
}

uint16_t eth_net_handle_arp( eth_transport_t *eth, uint8_t *local_mac, uint8_t *local_ip,
                             uint8_t *pkt, uint16_t len ) {
    uint8_t *arp = &pkt[ ETH_NET_ETH_HEADER_SIZE ];
    uint8_t *reply = &tx_pkt[ ETH_NET_ETH_HEADER_SIZE ];

    if ( len < ARP_FRAME_SIZE || get_be16( &pkt[ 12 ] ) != ETH_NET_ETHERTYPE_ARP )
        return 0;
    if ( get_be16( &arp[ 0 ] ) != 1 || get_be16( &arp[ 2 ] ) != ETH_NET_ETHERTYPE_IPV4 )
        return 0;                               // Ethernet / IPv4 only
    if ( get_be16( &arp[ 6 ] ) != 1 )           // Opcode 1 = request
        return 0;
    if ( memcmp( &arp[ 24 ], local_ip, 4 ) != 0 )   // Target protocol address
        return 0;

    memcpy( &tx_pkt[ 0 ], &pkt[ 6 ], 6 );       // dst = sender MAC
    memcpy( &tx_pkt[ 6 ], local_mac, 6 );       // src = us
    put_be16( &tx_pkt[ 12 ], ETH_NET_ETHERTYPE_ARP );

    put_be16( &reply[ 0 ], 1 );                 // HW type Ethernet
    put_be16( &reply[ 2 ], ETH_NET_ETHERTYPE_IPV4 );
    reply[ 4 ] = 6; reply[ 5 ] = 4;             // HW / protocol address sizes
    put_be16( &reply[ 6 ], 2 );                 // Opcode 2 = reply
    memcpy( &reply[ 8 ], local_mac, 6 );        // sender MAC = us
    memcpy( &reply[ 14 ], local_ip, 4 );        // sender IP  = us
    memcpy( &reply[ 18 ], &arp[ 8 ], 6 );       // target MAC = requester
    memcpy( &reply[ 24 ], &arp[ 14 ], 4 );      // target IP  = requester

    return eth_transport_send( eth, tx_pkt, ARP_FRAME_SIZE );
}

uint16_t eth_net_handle_icmp( eth_transport_t *eth, uint8_t *local_mac, uint8_t *local_ip,
                              uint8_t *pkt, uint16_t len ) {
    uint8_t *ip = &pkt[ IP_OFFSET ];
    uint8_t *icmp;
    uint8_t *reply = &tx_pkt[ L4_OFFSET ];
    uint8_t ihl;
    uint16_t ip_total;
    uint16_t icmp_len;

    if ( len < L4_OFFSET + ICMP_HEADER_SIZE || get_be16( &pkt[ 12 ] ) != ETH_NET_ETHERTYPE_IPV4 )
        return 0;
    if ( ip[ 9 ] != ETH_NET_IP_PROTO_ICMP || memcmp( &ip[ 16 ], local_ip, 4 ) != 0 )
        return 0;

    ihl = ( ip[ 0 ] & 0x0F ) * 4;
    ip_total = get_be16( &ip[ 2 ] );
    if ( ihl < ETH_NET_IP_HEADER_SIZE || ip_total < ihl + ICMP_HEADER_SIZE || ip_total > len - IP_OFFSET )
        return 0;                               // Malformed or truncated packet

    icmp = &ip[ ihl ];
    icmp_len = ip_total - ihl;
    if ( icmp[ 0 ] != ICMP_ECHO_REQUEST )
        return 0;
    if ( icmp_len > ETH_NET_TX_BUF_SIZE - L4_OFFSET )
        return 0;                               // Reply does not fit the TX buffer

    // Reply always uses a 20-byte IP header, request IP options are not echoed
    build_eth_ipv4( &pkt[ 6 ], local_mac, local_ip, &ip[ 12 ], ETH_NET_IP_PROTO_ICMP,
                    ETH_NET_IP_HEADER_SIZE + icmp_len );

    memcpy( reply, icmp, icmp_len );            // Same identifier, sequence and data
    reply[ 0 ] = ICMP_ECHO_REPLY;
    reply[ 1 ] = 0;
    reply[ 2 ] = 0; reply[ 3 ] = 0;
    put_be16( &reply[ 2 ], ip_checksum( reply, icmp_len ) );

    return eth_transport_send( eth, tx_pkt, L4_OFFSET + icmp_len );
}

uint16_t eth_net_dhcp_send( eth_transport_t *eth, uint8_t msg_type, uint8_t *local_mac,
                            uint8_t *dhcp_src_ip, uint8_t *dhcp_offered_ip,
                            uint8_t *dhcp_server_ip, uint32_t dhcp_xid ) {
    uint8_t bcast_mac[ 6 ] = { 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF };
    uint8_t bcast_ip[ 4 ]  = { 255, 255, 255, 255 };
    uint8_t *dhcp = &tx_pkt[ UDP_DATA_OFFSET ];     // Built in place, no extra buffer
    uint16_t opt = DHCP_FIXED_SIZE;

    memset( dhcp, 0, DHCP_FIXED_SIZE );

    // Fixed fields (RFC 2131), sname and file are left at 0
    dhcp[ 0 ] = DHCP_OP_REQUEST;
    dhcp[ 1 ] = DHCP_HTYPE_ETH;
    dhcp[ 2 ] = DHCP_HLEN_ETH;
    dhcp[ 3 ] = 0;                              // hops
    put_be32( &dhcp[ 4 ], dhcp_xid );
    put_be16( &dhcp[ 10 ], 0x8000 );            // flags: BROADCAST, ask for a broadcast reply
    memcpy( &dhcp[ 28 ], local_mac, 6 );        // chaddr
    memcpy( &dhcp[ 236 ], dhcp_magic_cookie, 4 );

    // Option 53: DHCP message type
    dhcp[ opt++ ] = 53; dhcp[ opt++ ] = 1; dhcp[ opt++ ] = msg_type;

    // Option 61: client identifier (type 1 = Ethernet + MAC)
    dhcp[ opt++ ] = 61; dhcp[ opt++ ] = 7; dhcp[ opt++ ] = 1;
    memcpy( &dhcp[ opt ], local_mac, 6 ); opt += 6;

    if ( msg_type == ETH_NET_DHCP_MSG_REQUEST ) {
        // Option 50: requested IP address (the offered one)
        dhcp[ opt++ ] = 50; dhcp[ opt++ ] = 4;
        memcpy( &dhcp[ opt ], dhcp_offered_ip, 4 ); opt += 4;

        // Option 54: server identifier (mandatory in a REQUEST)
        dhcp[ opt++ ] = 54; dhcp[ opt++ ] = 4;
        memcpy( &dhcp[ opt ], dhcp_server_ip, 4 ); opt += 4;
    }

    // Option 55: parameter request list (subnet mask, router)
    dhcp[ opt++ ] = 55; dhcp[ opt++ ] = 2; dhcp[ opt++ ] = 1; dhcp[ opt++ ] = 3;

    // Option 255: end
    dhcp[ opt++ ] = 255;

    return send_udp_frame( eth, local_mac, bcast_mac, bcast_ip, dhcp_src_ip,
                           ETH_NET_DHCP_CLIENT_PORT, ETH_NET_DHCP_SERVER_PORT, opt );
}

uint8_t eth_net_handle_dhcp( uint8_t *pkt, uint16_t len, uint32_t dhcp_xid,
                             uint8_t *dhcp_offered_ip, uint8_t *dhcp_server_ip,
                             uint8_t *local_ip ) {
    uint8_t *ip = &pkt[ IP_OFFSET ];
    uint8_t *udp;
    uint8_t *dhcp;
    uint8_t *options;
    uint8_t *opt_val;
    uint8_t opt_len;
    uint8_t ihl;
    uint16_t udp_len;
    uint16_t options_len;

    if ( len < L4_OFFSET || get_be16( &pkt[ 12 ] ) != ETH_NET_ETHERTYPE_IPV4 || ip[ 9 ] != ETH_NET_IP_PROTO_UDP )
        return ETH_NET_DHCP_NONE;

    ihl = ( ip[ 0 ] & 0x0F ) * 4;
    if ( ihl < ETH_NET_IP_HEADER_SIZE || len < IP_OFFSET + ihl + ETH_NET_UDP_HEADER_SIZE + DHCP_FIXED_SIZE )
        return ETH_NET_DHCP_NONE;

    udp = &ip[ ihl ];
    if ( get_be16( &udp[ 2 ] ) != ETH_NET_DHCP_CLIENT_PORT )
        return ETH_NET_DHCP_NONE;

    udp_len = get_be16( &udp[ 4 ] );
    if ( udp_len < ETH_NET_UDP_HEADER_SIZE + DHCP_FIXED_SIZE || udp_len > len - IP_OFFSET - ihl )
        return ETH_NET_DHCP_NONE;

    dhcp = &udp[ ETH_NET_UDP_HEADER_SIZE ];
    if ( memcmp( &dhcp[ 236 ], dhcp_magic_cookie, 4 ) != 0 )
        return ETH_NET_DHCP_NONE;

    // Check this reply matches our transaction (xid)
    if ( dhcp[ 4 ] != ( uint8_t )( dhcp_xid >> 24 ) || dhcp[ 5 ] != ( uint8_t )( dhcp_xid >> 16 ) ||
         dhcp[ 6 ] != ( uint8_t )( dhcp_xid >> 8 )  || dhcp[ 7 ] != ( uint8_t )( dhcp_xid & 0xFF ) )
        return ETH_NET_DHCP_NONE;

    options = &dhcp[ DHCP_FIXED_SIZE ];
    options_len = udp_len - ETH_NET_UDP_HEADER_SIZE - DHCP_FIXED_SIZE;

    opt_val = dhcp_find_option( options, options_len, 53, &opt_len );
    if ( !opt_val || opt_len < 1 )
        return ETH_NET_DHCP_NONE;

    if ( *opt_val == ETH_NET_DHCP_MSG_OFFER ) {
        memcpy( dhcp_offered_ip, &dhcp[ 16 ], 4 );      // yiaddr = offered IP

        opt_val = dhcp_find_option( options, options_len, 54, &opt_len );     // Server identifier
        if ( opt_val && opt_len >= 4 )
            memcpy( dhcp_server_ip, opt_val, 4 );
        return ETH_NET_DHCP_OFFER;
    }

    if ( *opt_val == ETH_NET_DHCP_MSG_ACK ) {
        memcpy( local_ip, &dhcp[ 16 ], 4 );             // yiaddr = confirmed IP
        return ETH_NET_DHCP_ACK;
    }

    if ( *opt_val == ETH_NET_DHCP_MSG_NAK )
        return ETH_NET_DHCP_NAK;

    return ETH_NET_DHCP_NONE;
}

// ------------------------------------------------------------------------ END
