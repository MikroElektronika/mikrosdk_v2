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
 * @file eth_net.h
 * @brief Minimal IPv4 protocol helpers (ARP, ICMP echo, TCP, UDP, DHCP client).
 * @details Transport independent: frames are sent through the eth_transport_*
 * API, independently of the controller and of the bus (SPI, I2C, UART, ...).
 * All frames are built in one internal TX buffer of ETH_NET_TX_BUF_SIZE bytes,
 * so the functions are not reentrant. IPv4 options and fragmentation are not
 * supported on transmit, TCP connection state is left to the caller.
 */

#ifndef _ETH_NET_H
#define _ETH_NET_H

#ifdef __cplusplus
extern "C"{
#endif

#include "eth_transport.h"
#include <stdint.h>

/**
 * @addtogroup middlewaregroup Middleware Libraries
 * @{
 */

/**
 * @defgroup eth_net Ethernet Network Helpers
 * @brief Transport independent ARP/ICMP/TCP/UDP/DHCP helpers.
 * @{
 */

/**
 * @brief Size of the internal TX buffer, the largest frame the helpers can build.
 * @details Must hold a DHCP message (311 bytes). TCP/UDP payloads are limited
 * to ETH_NET_TX_BUF_SIZE - 54 / ETH_NET_TX_BUF_SIZE - 42 bytes.
 */
#ifndef ETH_NET_TX_BUF_SIZE
#define ETH_NET_TX_BUF_SIZE         400
#endif

/**
 * @brief Frame layout.
 */
#define ETH_NET_ETH_HEADER_SIZE     14
#define ETH_NET_IP_HEADER_SIZE      20
#define ETH_NET_TCP_HEADER_SIZE     20
#define ETH_NET_UDP_HEADER_SIZE     8

/**
 * @brief EtherType and IPv4 protocol numbers.
 */
#define ETH_NET_ETHERTYPE_IPV4      0x0800
#define ETH_NET_ETHERTYPE_ARP       0x0806
#define ETH_NET_IP_PROTO_ICMP       1
#define ETH_NET_IP_PROTO_TCP        6
#define ETH_NET_IP_PROTO_UDP        17

/**
 * @brief TCP flags.
 */
#define ETH_NET_TCP_FLAG_FIN        0x01
#define ETH_NET_TCP_FLAG_SYN        0x02
#define ETH_NET_TCP_FLAG_RST        0x04
#define ETH_NET_TCP_FLAG_PSH        0x08
#define ETH_NET_TCP_FLAG_ACK        0x10

/**
 * @brief DHCP client.
 */
#define ETH_NET_DHCP_SERVER_PORT    67
#define ETH_NET_DHCP_CLIENT_PORT    68
#define ETH_NET_DHCP_MSG_DISCOVER   1
#define ETH_NET_DHCP_MSG_OFFER      2
#define ETH_NET_DHCP_MSG_REQUEST    3
#define ETH_NET_DHCP_MSG_ACK        5
#define ETH_NET_DHCP_MSG_NAK        6

/**
 * @brief eth_net_handle_dhcp() results.
 */
#define ETH_NET_DHCP_NONE           0   // Not a DHCP reply for this transaction
#define ETH_NET_DHCP_OFFER          1
#define ETH_NET_DHCP_ACK            2
#define ETH_NET_DHCP_NAK            3

/**
 * @brief Send a TCP segment over Ethernet/IPv4.
 * @details Builds the Ethernet, IPv4 and TCP headers (no options, window
 * 8192), computes the checksums and sends the frame.
 * @param[in] eth Ethernet transport instance.
 * @param[in] local_mac This device's MAC address (6 bytes).
 * @param[in] local_ip This device's IPv4 address (4 bytes), used as source.
 * @param[in] dst_mac Destination MAC address (6 bytes).
 * @param[in] dst_ip Destination IPv4 address (4 bytes).
 * @param[in] src_port Source TCP port.
 * @param[in] dst_port Destination TCP port.
 * @param[in] seq Sequence number.
 * @param[in] ack_num Acknowledgment number.
 * @param[in] flags TCP flags (ETH_NET_TCP_FLAG_*).
 * @param[in] payload Payload, NULL if none.
 * @param[in] payload_len Payload length in bytes, at most ETH_NET_TX_BUF_SIZE - 54.
 * @return Number of bytes sent, 0 if the payload does not fit or on error.
 * @note No retransmission or connection state is handled.
 */
uint16_t eth_net_send_tcp( eth_transport_t *eth, uint8_t *local_mac, uint8_t *local_ip,
                           uint8_t *dst_mac, uint8_t *dst_ip,
                           uint16_t src_port, uint16_t dst_port,
                           uint32_t seq, uint32_t ack_num, uint8_t flags,
                           uint8_t *payload, uint16_t payload_len );

/**
 * @brief Send a UDP datagram over Ethernet/IPv4.
 * @param[in] eth Ethernet transport instance.
 * @param[in] local_mac This device's MAC address (6 bytes).
 * @param[in] dst_mac Destination MAC address (6 bytes).
 * @param[in] dst_ip Destination IPv4 address (4 bytes).
 * @param[in] src_ip Source IPv4 address (4 bytes), may be 0.0.0.0 (e.g. DHCP).
 * @param[in] src_port Source UDP port.
 * @param[in] dst_port Destination UDP port.
 * @param[in] payload Payload, NULL if none.
 * @param[in] payload_len Payload length in bytes, at most ETH_NET_TX_BUF_SIZE - 42.
 * @return Number of bytes sent, 0 if the payload does not fit or on error.
 */
uint16_t eth_net_send_udp( eth_transport_t *eth, uint8_t *local_mac,
                           uint8_t *dst_mac, uint8_t *dst_ip, uint8_t *src_ip,
                           uint16_t src_port, uint16_t dst_port,
                           uint8_t *payload, uint16_t payload_len );

/**
 * @brief Answer an ARP request for this device.
 * @details Replies with @p local_mac if @p pkt is an Ethernet/IPv4 ARP
 * request for @p local_ip, other frames are ignored.
 * @param[in] eth Ethernet transport instance.
 * @param[in] local_mac This device's MAC address (6 bytes).
 * @param[in] local_ip This device's IPv4 address (4 bytes).
 * @param[in] pkt Received Ethernet frame.
 * @param[in] len Length of @p pkt in bytes.
 * @return Number of bytes sent, 0 if the frame was ignored or on error.
 */
uint16_t eth_net_handle_arp( eth_transport_t *eth, uint8_t *local_mac, uint8_t *local_ip,
                             uint8_t *pkt, uint16_t len );

/**
 * @brief Answer an ICMP echo request (ping) for this device.
 * @details Replies with an echo reply carrying the same identifier, sequence
 * and data if @p pkt is an echo request addressed to @p local_ip.
 * @param[in] eth Ethernet transport instance.
 * @param[in] local_mac This device's MAC address (6 bytes).
 * @param[in] local_ip This device's IPv4 address (4 bytes).
 * @param[in] pkt Received Ethernet frame.
 * @param[in] len Length of @p pkt in bytes.
 * @return Number of bytes sent, 0 if the frame was ignored, malformed, the
 * reply does not fit the TX buffer, or on error.
 */
uint16_t eth_net_handle_icmp( eth_transport_t *eth, uint8_t *local_mac, uint8_t *local_ip,
                              uint8_t *pkt, uint16_t len );

/**
 * @brief Broadcast a DHCP DISCOVER or REQUEST.
 * @details Builds the DHCP message (RFC 2131 fixed fields, magic cookie and
 * options 53, 61, 50, 54, 55) and broadcasts it from port 68 to port 67.
 * @param[in] eth Ethernet transport instance.
 * @param[in] msg_type ETH_NET_DHCP_MSG_DISCOVER or ETH_NET_DHCP_MSG_REQUEST.
 * @param[in] local_mac This device's MAC address (6 bytes).
 * @param[in] dhcp_src_ip Source IPv4 address, 0.0.0.0 until a lease is obtained.
 * @param[in] dhcp_offered_ip Offered address (option 50), REQUEST only.
 * @param[in] dhcp_server_ip Server identifier (option 54), REQUEST only.
 * @param[in] dhcp_xid Transaction ID.
 * @return Number of bytes sent, 0 on error.
 */
uint16_t eth_net_dhcp_send( eth_transport_t *eth, uint8_t msg_type, uint8_t *local_mac,
                            uint8_t *dhcp_src_ip, uint8_t *dhcp_offered_ip,
                            uint8_t *dhcp_server_ip, uint32_t dhcp_xid );

/**
 * @brief Parse a received frame as a DHCP server reply.
 * @details Accepts only well-formed IPv4/UDP frames for port 68 with the
 * DHCP magic cookie and a matching transaction ID. On OFFER the offered and
 * server addresses are stored, on ACK the confirmed address is written to
 * @p local_ip.
 * @param[in] pkt Received Ethernet frame.
 * @param[in] len Length of @p pkt in bytes.
 * @param[in] dhcp_xid Expected transaction ID.
 * @param[out] dhcp_offered_ip Updated on OFFER (4 bytes).
 * @param[out] dhcp_server_ip Updated on OFFER if the server sent option 54 (4 bytes).
 * @param[out] local_ip Updated on ACK (4 bytes).
 * @return ETH_NET_DHCP_NONE, ETH_NET_DHCP_OFFER, ETH_NET_DHCP_ACK or ETH_NET_DHCP_NAK.
 */
uint8_t eth_net_handle_dhcp( uint8_t *pkt, uint16_t len, uint32_t dhcp_xid,
                             uint8_t *dhcp_offered_ip, uint8_t *dhcp_server_ip,
                             uint8_t *local_ip );

/*! @} */ // eth_net
/*! @} */ // middlewaregroup

#ifdef __cplusplus
}
#endif
#endif // _ETH_NET_H

// ------------------------------------------------------------------------ END
