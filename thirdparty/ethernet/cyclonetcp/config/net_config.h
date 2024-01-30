/**
 * @file net_config.h
 * @brief CycloneTCP configuration file
 *
 * @section License
 *
 * SPDX-License-Identifier: GPL-2.0-or-later
 *
 * Copyright (C) 2010-2023 Oryx Embedded SARL. All rights reserved.
 *
 * This file is part of CycloneTCP Open.
 *
 * This program is free software; you can redistribute it and/or
 * modify it under the terms of the GNU General Public License
 * as published by the Free Software Foundation; either version 2
 * of the License, or (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software Foundation,
 * Inc., 51 Franklin Street, Fifth Floor, Boston, MA  02110-1301, USA.
 *
 * @author Oryx Embedded SARL (www.oryx-embedded.com)
 * @version 2.3.0
 **/

#ifndef _NET_CONFIG_H
#define _NET_CONFIG_H

//Trace level for TCP/IP stack debugging
#define MEM_TRACE_LEVEL          TRACE_LEVEL_INFO
#define NIC_TRACE_LEVEL          TRACE_LEVEL_INFO
#define ETH_TRACE_LEVEL          TRACE_LEVEL_OFF
#define LLDP_TRACE_LEVEL         TRACE_LEVEL_OFF
#define ARP_TRACE_LEVEL          TRACE_LEVEL_OFF
#define IP_TRACE_LEVEL           TRACE_LEVEL_OFF
#define IPV4_TRACE_LEVEL         TRACE_LEVEL_OFF
#define IPV6_TRACE_LEVEL         TRACE_LEVEL_OFF
#define ICMP_TRACE_LEVEL         TRACE_LEVEL_OFF
#define IGMP_TRACE_LEVEL         TRACE_LEVEL_OFF
#define ICMPV6_TRACE_LEVEL       TRACE_LEVEL_OFF
#define MLD_TRACE_LEVEL          TRACE_LEVEL_OFF
#define NDP_TRACE_LEVEL          TRACE_LEVEL_OFF
#define UDP_TRACE_LEVEL          TRACE_LEVEL_OFF
#define TCP_TRACE_LEVEL          TRACE_LEVEL_OFF
#define SOCKET_TRACE_LEVEL       TRACE_LEVEL_OFF
#define RAW_SOCKET_TRACE_LEVEL   TRACE_LEVEL_OFF
#define BSD_SOCKET_TRACE_LEVEL   TRACE_LEVEL_OFF
#define WEB_SOCKET_TRACE_LEVEL   TRACE_LEVEL_OFF
#define AUTO_IP_TRACE_LEVEL      TRACE_LEVEL_INFO
#define SLAAC_TRACE_LEVEL        TRACE_LEVEL_INFO
#define DHCP_TRACE_LEVEL         TRACE_LEVEL_INFO
#define DHCPV6_TRACE_LEVEL       TRACE_LEVEL_INFO
#define DNS_TRACE_LEVEL          TRACE_LEVEL_INFO
#define MDNS_TRACE_LEVEL         TRACE_LEVEL_OFF
#define NBNS_TRACE_LEVEL         TRACE_LEVEL_OFF
#define LLMNR_TRACE_LEVEL        TRACE_LEVEL_OFF
#define ECHO_TRACE_LEVEL         TRACE_LEVEL_INFO
#define COAP_TRACE_LEVEL         TRACE_LEVEL_INFO
#define FTP_TRACE_LEVEL          TRACE_LEVEL_DEBUG
#define HTTP_TRACE_LEVEL         TRACE_LEVEL_INFO
#define MQTT_TRACE_LEVEL         TRACE_LEVEL_INFO
#define MQTT_SN_TRACE_LEVEL      TRACE_LEVEL_INFO
#define SMTP_TRACE_LEVEL         TRACE_LEVEL_INFO
#define SNMP_TRACE_LEVEL         TRACE_LEVEL_INFO
#define SNTP_TRACE_LEVEL         TRACE_LEVEL_INFO
#define TFTP_TRACE_LEVEL         TRACE_LEVEL_INFO
#define MODBUS_TRACE_LEVEL       TRACE_LEVEL_INFO

//Number of network adapters
#define NET_INTERFACE_COUNT 1

//Size of the MAC address filter
#define MAC_ADDR_FILTER_SIZE 12

//IPv4 support
#define IPV4_SUPPORT ENABLED
//Size of the IPv4 multicast filter
#define IPV4_MULTICAST_FILTER_SIZE 4

//IPv4 fragmentation support
#define IPV4_FRAG_SUPPORT ENABLED
//Maximum number of fragmented packets the host will accept
//and hold in the reassembly queue simultaneously
#define IPV4_MAX_FRAG_DATAGRAMS 4
//Maximum datagram size the host will accept when reassembling fragments
#define IPV4_MAX_FRAG_DATAGRAM_SIZE 8192

//Size of ARP cache
#define ARP_CACHE_SIZE 8
//Maximum number of packets waiting for address resolution to complete
#define ARP_MAX_PENDING_PACKETS 2

//IGMP host support
#define IGMP_HOST_SUPPORT ENABLED

//IPv6 support
#define IPV6_SUPPORT ENABLED
//Size of the IPv6 multicast filter
#define IPV6_MULTICAST_FILTER_SIZE 8

//IPv6 fragmentation support
#define IPV6_FRAG_SUPPORT ENABLED
//Maximum number of fragmented packets the host will accept
//and hold in the reassembly queue simultaneously
#define IPV6_MAX_FRAG_DATAGRAMS 4
//Maximum datagram size the host will accept when reassembling fragments
#define IPV6_MAX_FRAG_DATAGRAM_SIZE 8192

//MLD support
#define MLD_SUPPORT ENABLED

//Neighbor cache size
#define NDP_NEIGHBOR_CACHE_SIZE 8
//Destination cache size
#define NDP_DEST_CACHE_SIZE 8
//Maximum number of packets waiting for address resolution to complete
#define NDP_MAX_PENDING_PACKETS 2

//TCP support
#define TCP_SUPPORT ENABLED
//Default buffer size for transmission
#define TCP_DEFAULT_TX_BUFFER_SIZE (1430*2)
//Default buffer size for reception
#define TCP_DEFAULT_RX_BUFFER_SIZE (1430*2)
//Default SYN queue size for listening sockets
#define TCP_DEFAULT_SYN_QUEUE_SIZE 4
//Maximum number of retransmissions
#define TCP_MAX_RETRIES 5
//Selective acknowledgment support
#define TCP_SACK_SUPPORT DISABLED
//TCP keep-alive support
#define TCP_KEEP_ALIVE_SUPPORT DISABLED

//UDP support
#define UDP_SUPPORT ENABLED
//Receive queue depth for connectionless sockets
#define UDP_RX_QUEUE_SIZE 4

//Raw socket support
#define RAW_SOCKET_SUPPORT DISABLED
//Receive queue depth for raw sockets
#define RAW_SOCKET_RX_QUEUE_SIZE 4

//Number of sockets that can be opened simultaneously
#define SOCKET_MAX_COUNT 16

//LLMNR responder support
#define LLMNR_RESPONDER_SUPPORT ENABLED

//FTP server support
#define FTP_SERVER_SUPPORT ENABLED
//Priority at which the FTP server should run
#define FTP_SERVER_PRIORITY OS_TASK_PRIORITY_HIGH

//Echo server support
#define ECHO_SERVER_SUPPORT ENABLED

#endif
