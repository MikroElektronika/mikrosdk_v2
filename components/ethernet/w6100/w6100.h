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
 * @file w6100.h
 * @brief SPI Ethernet WIZnet W6100 Driver.
 * @details The W6100 is used in MACRAW mode on socket 0. Several devices can
 * be used at the same time: give each eth_transport_t its own w6100_ctx_t
 * through driver_ctx before calling w6100_configure(). Without it, a built-in
 * context is used.
 */

#ifndef SPI_ETHERNET_W6100_H
#define SPI_ETHERNET_W6100_H

#include "eth_bus_spi.h"
#include <stdint.h>

#define W6100_MAP_MIKROBUS( cfg, mikrobus ) \
    ETH_BUS_SPI_MAP_MIKROBUS( cfg.bus, mikrobus ) \
    ETH_TRANSPORT_MAP_MIKROBUS( cfg.eth, mikrobus )

/**
 * @brief W6100 configuration: SPI bus and device settings.
 */
typedef struct {
    eth_bus_spi_cfg_t   bus;    // SPI pins, speed and mode
    eth_transport_cfg_t eth;    // Reset pin, MAC, IP, duplex
} w6100_cfg_t;

/**
 * @brief Per-device driver state, referenced through eth_transport_t.driver_ctx.
 */
typedef struct {
    uint8_t hw_rev;             // VERSIONR read during initialization
} w6100_ctx_t;

/**
 * @brief Initialize the W6100 configuration structure with default values.
 * @param[out] cfg W6100 configuration structure.
 * @return Nothing.
 */
void     w6100_cfg_setup( w6100_cfg_t *cfg );

/**
 * @brief Configure the SPI interface and the control pins for the W6100.
 * @param[in,out] eth Ethernet transport instance. If eth->driver_ctx is NULL
 *                    the built-in context is used, otherwise it must point to
 *                    a w6100_ctx_t owned by the caller (one per device).
 * @param[out] bus SPI bus object for this device, must stay valid while it is used.
 * @param[in] cfg W6100 configuration structure.
 * @return ETH_TRANSPORT_SUCCESS on success, ETH_TRANSPORT_ERROR otherwise.
 */
err_t    w6100_configure( eth_transport_t *eth, eth_bus_spi_t *bus, w6100_cfg_t *cfg );

/**
 * @brief Initialize the W6100.
 * @details Performs a hardware reset, programs the MAC and IP addresses and
 * opens socket 0 in MACRAW mode.
 * @param[in] eth Ethernet transport instance.
 * @return ETH_TRANSPORT_SUCCESS on success, ETH_TRANSPORT_ERROR otherwise.
 * @pre w6100_configure() must have been called beforehand.
 */
err_t    w6100_init( eth_transport_t *eth );

/**
 * @brief Send an Ethernet frame through socket 0.
 * @param[in] eth Ethernet transport instance.
 * @param[in] buf Ethernet frame (without FCS).
 * @param[in] len Frame length in bytes, at most W6100_FRAME_SIZE.
 * @return Number of bytes sent, 0 if the frame is too long.
 */
uint16_t w6100_send_packet( eth_transport_t *eth, uint8_t *buf, uint16_t len );

/**
 * @brief Read the next Ethernet frame from socket 0.
 * @param[in] eth Ethernet transport instance.
 * @param[out] buf Buffer receiving the frame.
 * @param[in] len Size of @p buf in bytes, longer frames are truncated.
 * @return Number of bytes read, 0 if no valid frame is available.
 */
uint16_t w6100_read_packet( eth_transport_t *eth, uint8_t *buf, uint16_t len );

/**
 * @brief Check whether a frame is waiting in the socket 0 RX buffer.
 * @param[in] eth Ethernet transport instance.
 * @return 1 if a frame is available, otherwise 0.
 */
uint8_t  w6100_packet_available( eth_transport_t *eth );

/**
 * @brief Get the current Ethernet link status.
 * @param[in] eth Ethernet transport instance.
 * @return 1 if the link is up, otherwise 0.
 */
uint8_t  w6100_get_link_status( eth_transport_t *eth );

/**
 * @brief Get the W6100 revision read during initialization.
 * @param[in] eth Ethernet transport instance.
 * @return VERSIONR value.
 */
uint8_t  w6100_get_rev( eth_transport_t *eth );

/**
 * @brief Reopen socket 0 in MACRAW mode.
 * @param[in] eth Ethernet transport instance.
 * @return Socket 0 status (Sn_SR) after the attempt, W6100_SOCK_MACRAW on success.
 */
uint8_t  w6100_reopen_socket0_macraw( eth_transport_t *eth );

/**
 * @brief Program the source hardware address register (SHAR).
 * @param[in] eth Ethernet transport instance.
 * @param[in] mac 6-byte MAC address.
 * @return ETH_TRANSPORT_SUCCESS.
 * @note The network registers must be unlocked (NETLCKR), this is done
 * during w6100_init().
 */
err_t    w6100_set_mac( eth_transport_t *eth, uint8_t *mac );

/**
 * @brief Program the source IP address register (SIPR).
 * @param[in] eth Ethernet transport instance.
 * @param[in] ip 4-byte IPv4 address.
 * @return ETH_TRANSPORT_SUCCESS.
 * @note The network registers must be unlocked (NETLCKR), this is done
 * during w6100_init().
 */
err_t    w6100_set_ip( eth_transport_t *eth, uint8_t *ip );

extern eth_transport_driver_t w6100_driver;

// Control byte: OM (operation mode) bits [1:0]
#define W6100_OM_VDM        0x00
#define W6100_OM_FDM1       0x01
#define W6100_OM_FDM2       0x02
#define W6100_OM_FDM4       0x03
// Control byte: R/W bit [2]
#define W6100_RWB_READ      0x00
#define W6100_RWB_WRITE     0x04
// Control byte: Block Select Bits [7:3]
#define W6100_BSB_COMMON_REG        ( 0x00 << 3 )
#define W6100_BSB_SOCKET0_REG( n )  ( ( ( 1 + ( 4 * ( n ) ) ) & 0x1F ) << 3 )
#define W6100_BSB_SOCKET0_TX( n )   ( ( ( 2 + ( 4 * ( n ) ) ) & 0x1F ) << 3 )
#define W6100_BSB_SOCKET0_RX( n )   ( ( ( 3 + ( 4 * ( n ) ) ) & 0x1F ) << 3 )

// Common register block
#define W6100_CIDR          0x0000
#define W6100_VERSIONR      0x0002
#define W6100_NET4MR        0x4000
#define W6100_NET4MR_PB     0x01
#define W6100_NET4MR_RSTB   0x02
#define W6100_NETMR         0x4008
#define W6100_SHAR          0x4120
#define W6100_SUBR          0x4134
#define W6100_SIPR          0x4138
#define W6100_PHYSR         0x3000
#define W6100_NETLCKR       0x41F5

// Socket n register block
#define W6100_Sn_MR           0x0000
#define W6100_Sn_CR           0x0010
#define W6100_Sn_IR           0x0020
#define W6100_Sn_SR           0x0030
#define W6100_Sn_PORTR        0x0114
#define W6100_Sn_DHAR         0x0118
#define W6100_Sn_DIPR         0x0120
#define W6100_Sn_DPORT        0x0140
#define W6100_Sn_MSSR         0x0110
#define W6100_Sn_TOSR         0x0104
#define W6100_Sn_TTLR         0x0108
#define W6100_Sn_TX_BSR       0x0200
#define W6100_Sn_TX_FSR       0x0204
#define W6100_Sn_TX_RD        0x0208
#define W6100_Sn_TX_WR        0x020C
#define W6100_Sn_RX_BSR       0x0220
#define W6100_Sn_RX_RSR       0x0224
#define W6100_Sn_RX_RD        0x0228
#define W6100_Sn_RX_WR        0x022C

/* Sn_MR protocol bits [3:0] */
#define W6100_Sn_MR_CLOSED    0x00
#define W6100_Sn_MR_TCP       0x01
#define W6100_Sn_MR_UDP       0x02
#define W6100_Sn_MR_MACRAW    0x07
#define W6100_Sn_MR_MF        0x40
/* Sn_CR commands */
#define W6100_Sn_CR_OPEN      0x01
#define W6100_Sn_CR_CLOSE     0x10
#define W6100_Sn_CR_SEND      0x20
#define W6100_Sn_CR_RECV      0x40
/* Sn_SR values of interest */
#define W6100_SOCK_CLOSED     0x00
#define W6100_SOCK_MACRAW     0x42

/* PHYCFGR bits */
#define W6100_PHYSR_LNK_MASK  0x01
#define W6100_PHYSR_RST       0x80

#define W6100_FRAME_SIZE 1518

#endif

// ------------------------------------------------------------------------ END
