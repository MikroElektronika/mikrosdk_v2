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
 * @file enc28j60.h
 * @brief SPI Ethernet Microchip ENC28J60 Driver.
 * @details Several devices can be used at the same time: give each
 * eth_transport_t its own enc28j60_ctx_t through driver_ctx before calling
 * enc28j60_configure(). Without it, a built-in context is used.
 */

#ifndef SPI_ETHERNET_ENC28J60_H
#define SPI_ETHERNET_ENC28J60_H

#include "eth_bus_spi.h"
#include <stdint.h>

#define ENC28J60_MAP_MIKROBUS( cfg, mikrobus ) \
    ETH_BUS_SPI_MAP_MIKROBUS( cfg.bus, mikrobus ) \
    ETH_TRANSPORT_MAP_MIKROBUS( cfg.eth, mikrobus )

/**
 * @brief ENC28J60 configuration: SPI bus and device settings.
 */
typedef struct {
    eth_bus_spi_cfg_t   bus;    // SPI pins, speed and mode
    eth_transport_cfg_t eth;    // Reset pin, MAC, IP, duplex
} enc28j60_cfg_t;

/**
 * @brief Per-device driver state, referenced through eth_transport_t.driver_ctx.
 */
typedef struct {
    uint8_t  current_bank;      // Currently selected register bank
    uint16_t next_ptr;          // Start of the next packet in the RX buffer
    uint8_t  hw_rev;            // EREVID read during initialization
} enc28j60_ctx_t;

/**
 * @brief Initialize the ENC28J60 configuration structure with default values.
 * @param[out] cfg ENC28J60 configuration structure.
 * @return Nothing.
 */
void     enc28j60_cfg_setup( enc28j60_cfg_t *cfg );

/**
 * @brief Configure the SPI interface and the control pins for the ENC28J60.
 * @param[in,out] eth Ethernet transport instance. If eth->driver_ctx is NULL
 *                    the built-in context is used, otherwise it must point to
 *                    an enc28j60_ctx_t owned by the caller (one per device).
 * @param[out] bus SPI bus object for this device, must stay valid while it is used.
 * @param[in] cfg ENC28J60 configuration structure.
 * @return ETH_TRANSPORT_SUCCESS on success, ETH_TRANSPORT_ERROR otherwise.
 */
err_t    enc28j60_configure( eth_transport_t *eth, eth_bus_spi_t *bus, enc28j60_cfg_t *cfg );

/**
 * @brief Initialize the ENC28J60 Ethernet controller.
 * @details Performs hardware and software reset, initializes the receive and
 * transmit buffers, the receive filter, the MAC and the PHY, reads the chip
 * revision and enables reception.
 * @param[in] eth Ethernet transport instance.
 * @return ETH_TRANSPORT_SUCCESS on success, ETH_TRANSPORT_ERROR otherwise.
 * @pre enc28j60_configure() must have been called beforehand.
 */
err_t    enc28j60_init( eth_transport_t *eth );

/**
 * @brief Send an Ethernet frame through the ENC28J60.
 * @param[in] eth Ethernet transport instance.
 * @param[in] buf Ethernet frame (without FCS).
 * @param[in] len Frame length in bytes, at most ENC28J60_FRAME_SIZE.
 * @return Number of bytes sent, 0 if the frame is too long.
 */
uint16_t enc28j60_send_packet( eth_transport_t *eth, uint8_t *buf, uint16_t len );

/**
 * @brief Read the next Ethernet frame from the ENC28J60 receive buffer.
 * @param[in] eth Ethernet transport instance.
 * @param[out] buf Buffer receiving the frame (without FCS).
 * @param[in] len Size of @p buf in bytes, longer frames are truncated.
 * @return Number of bytes read, 0 if no valid frame is available.
 */
uint16_t enc28j60_read_packet( eth_transport_t *eth, uint8_t *buf, uint16_t len );

/**
 * @brief Get the number of frames waiting in the receive buffer.
 * @param[in] eth Ethernet transport instance.
 * @return Number of frames waiting.
 */
uint8_t  enc28j60_packet_available( eth_transport_t *eth );

/**
 * @brief Get the current Ethernet link status.
 * @param[in] eth Ethernet transport instance.
 * @return 1 if the link is up, otherwise 0.
 */
uint8_t  enc28j60_get_link_status( eth_transport_t *eth );

/**
 * @brief Program the MAC address registers.
 * @param[in] eth Ethernet transport instance.
 * @param[in] mac 6-byte MAC address.
 * @return ETH_TRANSPORT_SUCCESS.
 */
err_t    enc28j60_set_mac( eth_transport_t *eth, uint8_t *mac );

/**
 * @brief Get the ENC28J60 silicon revision read during initialization.
 * @param[in] eth Ethernet transport instance.
 * @return EREVID value.
 */
uint8_t  enc28j60_get_rev( eth_transport_t *eth );

/**
 * @brief Initialize the ENC28J60 PHY (reset, normal mode, no loopback).
 * @param[in] eth Ethernet transport instance.
 * @return Nothing.
 */
void     enc28j60_phy_init( eth_transport_t *eth );

/**
 * @brief Write a 16-bit value to a PHY register.
 * @param[in] eth Ethernet transport instance.
 * @param[in] phy_reg PHY register address.
 * @param[in] value Value to write.
 * @return Nothing.
 */
void     enc28j60_phy_write( eth_transport_t *eth, uint8_t phy_reg, uint16_t value );

/**
 * @brief Read a 16-bit value from a PHY register.
 * @param[in] eth Ethernet transport instance.
 * @param[in] reg PHY register address.
 * @param[out] low Low byte of the register value.
 * @param[out] high High byte of the register value.
 * @return Nothing.
 */
void     enc28j60_phy_read( eth_transport_t *eth, uint8_t reg, uint8_t *low, uint8_t *high );

extern eth_transport_driver_t enc28j60_driver;

// ENC28J60 register addresses and bit positions
#define MICMD_MIIRD    0x01

#define EIE              0x1B
#define EIR              0x1C
#define ESTAT            0x1D
#define ECON2            0x1E
#define ECON1            0x1F
// Bank 0 registers
#define ERDPTL           ( 0x00 )
#define ERDPTH           ( 0x01 )
#define EWRPTL           ( 0x02 )
#define EWRPTH           ( 0x03 )
#define ETXSTL           ( 0x04 )
#define ETXSTH           ( 0x05 )
#define ETXNDL           ( 0x06 )
#define ETXNDH           ( 0x07 )
#define ERXSTL           ( 0x08 )
#define ERXSTH           ( 0x09 )
#define ERXNDL           ( 0x0A )
#define ERXNDH           ( 0x0B )
#define ERXRDPTL         ( 0x0C )
#define ERXRDPTH         ( 0x0D )
#define ERXWRPTL         ( 0x0E )
#define ERXWRPTH         ( 0x0F )
#define EDMASTL          ( 0x10 )
#define EDMASTH          ( 0x11 )
#define EDMANDL          ( 0x12 )
#define EDMANDH          ( 0x13 )
#define EDMADSTL         ( 0x14 )
#define EDMADSTH         ( 0x15 )
#define EDMACSL          ( 0x16 )
#define EDMACSH          ( 0x17 )
// Bank 1 registers
#define EHT0             ( 0x00 )
#define EHT1             ( 0x01 )
#define EHT2             ( 0x02 )
#define EHT3             ( 0x03 )
#define EHT4             ( 0x04 )
#define EHT5             ( 0x05 )
#define EHT6             ( 0x06 )
#define EHT7             ( 0x07 )
#define EPMM0            ( 0x08 )
#define EPMM1            ( 0x09 )
#define EPMM2            ( 0x0A )
#define EPMM3            ( 0x0B )
#define EPMM4            ( 0x0C )
#define EPMM5            ( 0x0D )
#define EPMM6            ( 0x0E )
#define EPMM7            ( 0x0F )
#define EPMCSL           ( 0x10 )
#define EPMCSH           ( 0x11 )
#define EPMOL            ( 0x14 )
#define EPMOH            ( 0x15 )
#define EWOLIE           ( 0x16 )
#define EWOLIR           ( 0x17 )
#define ERXFCON          ( 0x18 )
#define EPKTCNT          ( 0x19 )
// Bank 2 registers
#define MACON1           ( 0x00|0x80 )
#define MACON2           ( 0x01|0x80 )
#define MACON3           ( 0x02|0x80 )
#define MACON4           ( 0x03|0x80 )
#define MABBIPG          ( 0x04|0x80 )
#define MAIPGL           ( 0x06|0x80 )
#define MAIPGH           ( 0x07|0x80 )
#define MACLCON1         ( 0x08|0x80 )
#define MACLCON2         ( 0x09|0x80 )
#define MAMXFLL          ( 0x0A|0x80 )
#define MAMXFLH          ( 0x0B|0x80 )
#define MAPHSUP          ( 0x0D|0x80 )
#define MICON            ( 0x11|0x80 )
#define MICMD            ( 0x12|0x80 )
#define MIREGADR         ( 0x14|0x80 )
#define MIWRL            ( 0x16|0x80 )
#define MIWRH            ( 0x17|0x80 )
#define MIRDL            ( 0x18|0x80 )
#define MIRDH            ( 0x19|0x80 )
// Bank 3 registers
#define MAADR5           ( 0x00|0x80 )
#define MAADR6           ( 0x01|0x80 )
#define MAADR3           ( 0x02|0x80 )
#define MAADR4           ( 0x03|0x80 )
#define MAADR1           ( 0x04|0x80 )
#define MAADR2           ( 0x05|0x80 )
#define EBSTSD           ( 0x06 )
#define EBSTCON          ( 0x07 )
#define EBSTCSL          ( 0x08 )
#define EBSTCSH          ( 0x09 )
#define MISTAT           ( 0x0A|0x80 )
#define EREVID           ( 0x12 )
#define ECOCON           ( 0x15 )
#define EFLOCON          ( 0x17 )
#define EPAUSL           ( 0x18 )
#define EPAUSH           ( 0x19 )
// PHY registers
#define PHCON1           0x00
#define PHSTAT1          0x01
#define PHHID1           0x02
#define PHHID2           0x03
#define PHCON2           0x10
#define PHSTAT2          0x11
#define PHIE             0x12
#define PHIR             0x13
#define PHLCON           0x14

// SPI instruction set for the ENC28J60
#define ENC28J60_RCR_CMD 0x00       // Read Control Register
#define ENC28J60_WCR_CMD 0x40       // Write Control Register
#define ENC28J60_BFS_CMD 0x80       // Bit Field Set
#define ENC28J60_BFC_CMD 0xA0       // Bit Field Clear
#define ENC28J60_SRC_CMD 0xFF       // System Reset Command
#define ENC28J60_RBM_CMD 0x3A       // Read Buffer Memory
#define ENC28J60_WBM_CMD 0x7A       // Write Buffer Memory

// Maximum packet length (Ethernet frames are between 64 and 1518 bytes long)
#define ENC28J60_FRAME_SIZE 1518

// Receive status vector bit definitions
// Bits 0 to 15 are assigned for Received Byte Count
#define ENC28J60_RSV_RECEIVED_OK       0x80    // Frame received OK (bit 23 out of 31)

// Memory allocation
#define RAM_SIZE ( 8192 )                                             // 8kb RAM available
#define TRANSMIT_START ( RAM_SIZE - ( ENC28J60_FRAME_SIZE + 100 ) )   // Transmit buffer start address, a few more bytes for padding pseudo header + transmit status : Even memory address
#define RECEIVE_START ( 0 )                                           // Receive buffer start address : Should be an even memory address; must be 0 for errata
#define RECEIVE_END ( TRANSMIT_START - 1 )                            // Receive buffer end address : Odd for errata workaround
#define REPLY_START ( TRANSMIT_START + 1 )                            // Reply buffer starts after per packet control byte
#define RECEIVE_SIZE ( RECEIVE_END - RECEIVE_START + 1 )              // Receive buffer size
#define NO_ADDR ( 0xFFFF )

#endif

// ----------------------------------------------------------------------- END
