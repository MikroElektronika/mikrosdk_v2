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
 * @file w5500.h
 * @brief SPI Ethernet WIZnet W5500 Driver (also used on WIZ_IP55).
 * @details The W5500 is used in MACRAW mode on socket 0, so frames go through
 * the eth_net helpers like on any other controller. Several devices can be
 * used at the same time: give each eth_transport_t its own w5500_ctx_t
 * through driver_ctx before calling w5500_configure(). Without it, a built-in
 * context is used.
 */

#ifndef SPI_ETHERNET_W5500_H
#define SPI_ETHERNET_W5500_H

#include "eth_bus_spi.h"
#include <stdint.h>

#define W5500_MAP_MIKROBUS( cfg, mikrobus ) \
    ETH_BUS_SPI_MAP_MIKROBUS( cfg.bus, mikrobus ) \
    ETH_TRANSPORT_MAP_MIKROBUS( cfg.eth, mikrobus )

/**
 * @brief W5500 configuration: SPI bus and device settings.
 */
typedef struct {
    eth_bus_spi_cfg_t   bus;    // SPI pins, speed and mode
    eth_transport_cfg_t eth;    // Reset pin, MAC, IP, duplex
} w5500_cfg_t;

/**
 * @brief Per-device driver state, referenced through eth_transport_t.driver_ctx.
 */
typedef struct {
    uint8_t hw_rev;             // VERSIONR read during initialization
} w5500_ctx_t;

/**
 * @brief Initialize the W5500 configuration structure with default values.
 * @param[out] cfg W5500 configuration structure.
 * @return Nothing.
 */
void     w5500_cfg_setup( w5500_cfg_t *cfg );

/**
 * @brief Configure the SPI interface and the control pins for the W5500.
 * @param[in,out] eth Ethernet transport instance. If eth->driver_ctx is NULL
 *                    the built-in context is used, otherwise it must point to
 *                    a w5500_ctx_t owned by the caller (one per device).
 * @param[out] bus SPI bus object for this device, must stay valid while it is used.
 * @param[in] cfg W5500 configuration structure.
 * @return ETH_TRANSPORT_SUCCESS on success, ETH_TRANSPORT_ERROR otherwise.
 */
err_t    w5500_configure( eth_transport_t *eth, eth_bus_spi_t *bus, w5500_cfg_t *cfg );

/**
 * @brief Initialize the W5500.
 * @details Resets the W5500, reads its revision, programs the MAC and IP
 * addresses and opens socket 0 in MACRAW mode.
 * @param[in] eth Ethernet transport instance.
 * @return ETH_TRANSPORT_SUCCESS on success, ETH_TRANSPORT_ERROR otherwise.
 * @pre w5500_configure() must have been called beforehand.
 */
err_t    w5500_init( eth_transport_t *eth );

/**
 * @brief Send an Ethernet frame through socket 0.
 * @param[in] eth Ethernet transport instance.
 * @param[in] buf Ethernet frame (without FCS).
 * @param[in] len Frame length in bytes, at most W5500_FRAME_SIZE.
 * @return Number of bytes sent, 0 if the frame is too long.
 */
uint16_t w5500_send_packet( eth_transport_t *eth, uint8_t *buf, uint16_t len );

/**
 * @brief Read the next Ethernet frame from socket 0.
 * @param[in] eth Ethernet transport instance.
 * @param[out] buf Buffer receiving the frame.
 * @param[in] len Size of @p buf in bytes, longer frames are truncated.
 * @return Number of bytes read, 0 if no valid frame is available.
 */
uint16_t w5500_read_packet( eth_transport_t *eth, uint8_t *buf, uint16_t len );

/**
 * @brief Check whether a frame is waiting in the socket 0 RX buffer.
 * @param[in] eth Ethernet transport instance.
 * @return 1 if a frame is available, otherwise 0.
 */
uint8_t  w5500_packet_available( eth_transport_t *eth );

/**
 * @brief Get the current Ethernet link status.
 * @param[in] eth Ethernet transport instance.
 * @return 1 if the link is up, 0 if it is down or the chip does not respond.
 */
uint8_t  w5500_get_link_status( eth_transport_t *eth );

/**
 * @brief Get the W5500 revision read during initialization.
 * @param[in] eth Ethernet transport instance.
 * @return VERSIONR value (0x04 for W5500).
 */
uint8_t  w5500_get_rev( eth_transport_t *eth );

/**
 * @brief Program the source hardware address register (SHAR).
 * @param[in] eth Ethernet transport instance.
 * @param[in] mac 6-byte MAC address.
 * @return ETH_TRANSPORT_SUCCESS.
 */
err_t    w5500_set_mac( eth_transport_t *eth, uint8_t *mac );

/**
 * @brief Program the source IP address register (SIPR).
 * @param[in] eth Ethernet transport instance.
 * @param[in] ip 4-byte IPv4 address.
 * @return ETH_TRANSPORT_SUCCESS.
 */
err_t    w5500_set_ip( eth_transport_t *eth, uint8_t *ip );

extern eth_transport_driver_t w5500_driver;

// Control byte: OM (operation mode) bits [1:0]
#define W5500_OM_VDM        0x00
#define W5500_OM_FDM1       0x01
#define W5500_OM_FDM2       0x02
#define W5500_OM_FDM4       0x03
// Control byte: R/W bit [2]
#define W5500_RWB_READ      0x00
#define W5500_RWB_WRITE     0x04
// Control byte: Block Select Bits [7:3]
#define W5500_BSB_COMMON_REG        ( 0x00 << 3 )
#define W5500_BSB_SOCKET0_REG( n )  ( ( ( 1 + ( 4 * ( n ) ) ) & 0x1F ) << 3 )
#define W5500_BSB_SOCKET0_TX( n )   ( ( ( 2 + ( 4 * ( n ) ) ) & 0x1F ) << 3 )
#define W5500_BSB_SOCKET0_RX( n )   ( ( ( 3 + ( 4 * ( n ) ) ) & 0x1F ) << 3 )
// Common register block (BSB = 0x00)
#define W5500_MR             0x0000
#define W5500_GAR            0x0001
#define W5500_SUBR           0x0005
#define W5500_SHAR           0x0009
#define W5500_SIPR           0x000F
#define W5500_INTLEVEL       0x0013
#define W5500_IR             0x0015
#define W5500_IMR            0x0016
#define W5500_SIR            0x0017
#define W5500_SIMR           0x0018
#define W5500_RTR            0x0019
#define W5500_RCR            0x001B
#define W5500_PHYCFGR        0x002E
#define W5500_VERSIONR       0x0039
/* Socket n register block */
#define W5500_Sn_MR           0x0000
#define W5500_Sn_CR           0x0001
#define W5500_Sn_IR           0x0002
#define W5500_Sn_SR           0x0003
#define W5500_Sn_PORT         0x0004
#define W5500_Sn_DHAR         0x0006
#define W5500_Sn_DIPR         0x000C
#define W5500_Sn_DPORT        0x0010
#define W5500_Sn_MSSR         0x0012
#define W5500_Sn_TOS          0x0015
#define W5500_Sn_TTL          0x0016
#define W5500_Sn_RXBUF_SIZE   0x001E
#define W5500_Sn_TXBUF_SIZE   0x001F
#define W5500_Sn_TX_FSR       0x0020
#define W5500_Sn_TX_RD        0x0022
#define W5500_Sn_TX_WR        0x0024
#define W5500_Sn_RX_RSR       0x0026
#define W5500_Sn_RX_RD        0x0028
#define W5500_Sn_RX_WR        0x002A
/* Sn_MR protocol bits [3:0] */
#define W5500_Sn_MR_CLOSED    0x00
#define W5500_Sn_MR_TCP       0x01
#define W5500_Sn_MR_UDP       0x02
#define W5500_Sn_MR_MACRAW    0x04
#define W5500_MR_PB           0x10
#define W5500_Sn_MR_MF        0x40
/* Sn_CR commands */
#define W5500_Sn_CR_OPEN      0x01
#define W5500_Sn_CR_CLOSE     0x10
#define W5500_Sn_CR_SEND      0x20
#define W5500_Sn_CR_RECV      0x40
/* Sn_SR values of interest */
#define W5500_SOCK_CLOSED     0x00
#define W5500_SOCK_MACRAW     0x42

/* PHYCFGR bits */
#define W5500_PHYCFGR_LNK_MASK  0x01
#define W5500_PHYCFGR_RST       0x80

#define W5500_FRAME_SIZE 1518

#endif

// ------------------------------------------------------------------------ END
