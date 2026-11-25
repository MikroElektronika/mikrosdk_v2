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
 * @file lwipopts.h
 * @brief lwIP configuration for the mikroSDK network layer (middleware/net).
 * @details No RTOS (NO_SYS = 1, raw API only), one network interface, IPv4 with
 * DHCP and DNS. Every size below can be overridden with a compile definition of
 * the same NET_LWIP_* name (e.g. from CMake) to fit smaller or larger MCUs.
 * Default RAM use is roughly MEM_SIZE + PBUF_POOL_SIZE * 1.5 KB + the PCB pools,
 * about 30 KB.
 */

#ifndef LWIP_LWIPOPTS_H
#define LWIP_LWIPOPTS_H

/* ---- System: no RTOS, raw API, single-threaded --------------------------- */
#define NO_SYS                          1
#define SYS_LIGHTWEIGHT_PROT            0   /* lwIP is only called from net_poll() and the net_* API, never from interrupts */
#define LWIP_NETCONN                    0
#define LWIP_SOCKET                     0
#define LWIP_SINGLE_NETIF               1
#define LWIP_TIMERS                     1

/* ---- Memory -------------------------------------------------------------- */
/* Pointer size: 4 on the 32-bit MCUs (ARM, PIC32), 8 for 64-bit host tests. */
#if defined(__SIZEOF_POINTER__) && (__SIZEOF_POINTER__ > 4)
#define MEM_ALIGNMENT                   8
#else
#define MEM_ALIGNMENT                   4
#endif
#ifndef NET_LWIP_MEM_SIZE
#define NET_LWIP_MEM_SIZE               (10 * 1024)
#endif
#define MEM_SIZE                        NET_LWIP_MEM_SIZE

#ifndef NET_LWIP_PBUF_POOL_SIZE
#define NET_LWIP_PBUF_POOL_SIZE         10
#endif
#define PBUF_POOL_SIZE                  NET_LWIP_PBUF_POOL_SIZE
#define MEMP_NUM_PBUF                   16

/* ---- Protocols ----------------------------------------------------------- */
#define LWIP_IPV4                       1
#ifndef NET_LWIP_IPV6
#define NET_LWIP_IPV6                   0
#endif
#define LWIP_IPV6                       NET_LWIP_IPV6
#define LWIP_ARP                        1
#define LWIP_ETHERNET                   1
#define LWIP_ICMP                       1
#define LWIP_RAW                        0
#define LWIP_UDP                        1
#define LWIP_TCP                        1
#define LWIP_DHCP                       1
#define LWIP_DNS                        1
#define LWIP_IGMP                       0
#define LWIP_NETIF_HOSTNAME             1
#define DNS_MAX_SERVERS                 2
#define IP_REASSEMBLY                   1
#define IP_FRAG                         1

/* ---- TCP ----------------------------------------------------------------- */
#ifndef NET_LWIP_TCP_MSS
#define NET_LWIP_TCP_MSS                1460
#endif
#define TCP_MSS                         NET_LWIP_TCP_MSS
#ifndef NET_LWIP_TCP_WND
#define NET_LWIP_TCP_WND                (2 * TCP_MSS)
#endif
#define TCP_WND                         NET_LWIP_TCP_WND
#ifndef NET_LWIP_TCP_SND_BUF
#define NET_LWIP_TCP_SND_BUF            (2 * TCP_MSS)
#endif
#define TCP_SND_BUF                     NET_LWIP_TCP_SND_BUF
#define TCP_SND_QUEUELEN                ((4 * (TCP_SND_BUF) + (TCP_MSS - 1)) / (TCP_MSS))
#define MEMP_NUM_TCP_SEG                (2 * TCP_SND_QUEUELEN)
#define TCP_LISTEN_BACKLOG              1
#define LWIP_TCP_KEEPALIVE              1

/* PCB pools: sockets of the network layer (NET_MAX_SOCKETS in net_api.h) plus
 * the UDP PCBs DHCP and DNS use internally. */
#ifndef NET_MAX_SOCKETS
#define NET_MAX_SOCKETS                 4
#endif
#define MEMP_NUM_TCP_PCB                NET_MAX_SOCKETS
#define MEMP_NUM_TCP_PCB_LISTEN         2
#define MEMP_NUM_UDP_PCB                (NET_MAX_SOCKETS + 2)

/* ---- Checksums: computed in software (drivers may enable offload later) -- */
#define CHECKSUM_GEN_IP                 1
#define CHECKSUM_GEN_UDP                1
#define CHECKSUM_GEN_TCP                1
#define CHECKSUM_GEN_ICMP               1
#define CHECKSUM_CHECK_IP               1
#define CHECKSUM_CHECK_UDP              1
#define CHECKSUM_CHECK_TCP              1
#define CHECKSUM_CHECK_ICMP             1

/* ---- Statistics and debugging off ---------------------------------------- */
#define LWIP_STATS                      0
/* LWIP_DEBUG is tested with #ifdef: leave it undefined. */

#endif /* LWIP_LWIPOPTS_H */
