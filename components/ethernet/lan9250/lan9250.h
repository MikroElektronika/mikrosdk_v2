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
 * @file lan9250.h
 * @brief SPI Ethernet Microchip LAN9250 Driver.
 * @details Several devices can be used at the same time: give each
 * eth_transport_t its own lan9250_ctx_t through driver_ctx before calling
 * lan9250_configure(). Without it, a built-in context is used.
 */

#ifndef SPI_ETHERNET_LAN9250_H
#define SPI_ETHERNET_LAN9250_H

#include "eth_bus_spi.h"
#include <stdint.h>

#define LAN9250_MAP_MIKROBUS( cfg, mikrobus ) \
    ETH_BUS_SPI_MAP_MIKROBUS( cfg.bus, mikrobus ) \
    ETH_TRANSPORT_MAP_MIKROBUS( cfg.eth, mikrobus )

/**
 * @brief LAN9250 configuration: SPI bus and device settings.
 */
typedef struct {
    eth_bus_spi_cfg_t   bus;    // SPI pins, speed and mode
    eth_transport_cfg_t eth;    // Reset pin, MAC, IP, duplex
} lan9250_cfg_t;

/**
 * @brief Per-device driver state, referenced through eth_transport_t.driver_ctx.
 */
typedef struct {
    uint32_t id_rev;            // ID_REV read during initialization
} lan9250_ctx_t;

/**
 * @brief Initialize the LAN9250 configuration structure with default values.
 * @param[out] cfg LAN9250 configuration structure.
 * @return Nothing.
 */
void     lan9250_cfg_setup( lan9250_cfg_t *cfg );

/**
 * @brief Configure the SPI interface and the control pins for the LAN9250.
 * @param[in,out] eth Ethernet transport instance. If eth->driver_ctx is NULL
 *                    the built-in context is used, otherwise it must point to
 *                    a lan9250_ctx_t owned by the caller (one per device).
 * @param[out] bus SPI bus object for this device, must stay valid while it is used.
 * @param[in] cfg LAN9250 configuration structure.
 * @return ETH_TRANSPORT_SUCCESS on success, ETH_TRANSPORT_ERROR otherwise.
 */
err_t    lan9250_configure( eth_transport_t *eth, eth_bus_spi_t *bus, lan9250_cfg_t *cfg );

/**
 * @brief Initialize the LAN9250.
 * @details Resets the LAN9250, waits for the device to become ready, performs
 * the digital reset, reads the chip identification, configures the TX FIFO,
 * programs the MAC address and enables transmission and reception.
 * @param[in] eth Ethernet transport instance.
 * @return ETH_TRANSPORT_SUCCESS on success, ETH_TRANSPORT_ERROR otherwise.
 * @pre lan9250_configure() must have been called beforehand.
 */
err_t    lan9250_init( eth_transport_t *eth );

/**
 * @brief Send an Ethernet frame through the TX data FIFO.
 * @param[in] eth Ethernet transport instance.
 * @param[in] buf Ethernet frame (without FCS).
 * @param[in] len Frame length in bytes, at most LAN9250_FRAME_SIZE.
 * @return Number of bytes sent, 0 if the frame is too long or the TX FIFO is full.
 */
uint16_t lan9250_send_packet( eth_transport_t *eth, uint8_t *buf, uint16_t len );

/**
 * @brief Read the next Ethernet frame from the RX data FIFO.
 * @param[in] eth Ethernet transport instance.
 * @param[out] buf Buffer receiving the frame.
 * @param[in] len Size of @p buf in bytes, longer frames are truncated.
 * @return Number of bytes read, 0 if no valid frame is available.
 */
uint16_t lan9250_read_packet( eth_transport_t *eth, uint8_t *buf, uint16_t len );

/**
 * @brief Get the number of frames waiting in the RX FIFO.
 * @param[in] eth Ethernet transport instance.
 * @return Number of frames waiting, limited to 255.
 */
uint8_t  lan9250_packet_available( eth_transport_t *eth );

/**
 * @brief Get the current Ethernet link status.
 * @param[in] eth Ethernet transport instance.
 * @return 1 if the link is up, otherwise 0.
 */
uint8_t  lan9250_get_link_status( eth_transport_t *eth );

/**
 * @brief Get the LAN9250 revision (low byte of ID_REV).
 * @param[in] eth Ethernet transport instance.
 * @return Revision value.
 */
uint8_t  lan9250_get_rev( eth_transport_t *eth );

/**
 * @brief Get the complete ID_REV value read during initialization.
 * @param[in] eth Ethernet transport instance.
 * @return ID_REV value, 0x9250 expected in bits 31:16.
 */
uint32_t lan9250_get_id_rev( eth_transport_t *eth );

/**
 * @brief Program the host MAC address registers.
 * @param[in] eth Ethernet transport instance.
 * @param[in] mac 6-byte MAC address.
 * @return ETH_TRANSPORT_SUCCESS.
 */
err_t    lan9250_set_mac( eth_transport_t *eth, uint8_t *mac );

extern eth_transport_driver_t lan9250_driver;

// SPI instructions (datasheet DS00001913, System CSR interface)
#define LAN9250_SPI_INSTR_READ       0x03   // byte/word/dword read,  no dummy, up to 80 MHz in FASTREAD mode
#define LAN9250_SPI_INSTR_WRITE      0x02   // byte/word/dword write, no dummy
#define LAN9250_SPI_INSTR_FASTREAD   0x0B   // 1 dummy byte, not used here

// System CSR registers (byte offsets)
#define LAN9250_RX_DATA_FIFO   0x0000
#define LAN9250_TX_DATA_FIFO   0x0020
#define LAN9250_RX_STATUS_FIFO 0x0040
#define LAN9250_TX_STATUS_FIFO 0x0048
#define LAN9250_ID_REV         0x0050
#define LAN9250_IRQ_CFG        0x0054
#define LAN9250_INT_STS        0x0058
#define LAN9250_INT_EN         0x005C
#define LAN9250_BYTE_TEST      0x0064
#define LAN9250_RX_CFG         0x006C
#define LAN9250_TX_CFG         0x0070
#define LAN9250_HW_CFG         0x0074
#define LAN9250_RX_DP_CTRL     0x0078
#define LAN9250_RX_FIFO_INF    0x007C
#define LAN9250_TX_FIFO_INF    0x0080
#define LAN9250_MAC_CSR_CMD    0x00A4
#define LAN9250_MAC_CSR_DATA   0x00A8
#define LAN9250_RESET_CTL      0x01F8

// BYTE_TEST expected fixed pattern
#define LAN9250_BYTE_TEST_DEFAULT  0x87654321UL

// HW_CFG bits
#define LAN9250_HW_CFG_DEVICE_READY  0x08000000UL
#define LAN9250_HW_CFG_MBO           0x00100000UL   // must-be-one
#define LAN9250_HW_CFG_TX_FIF_SZ_5KB 0x00050000UL

// TX_CFG bits
#define LAN9250_TX_CFG_TXSAO  0x00000004UL          // TX status all-ones (host ignores TX status)
#define LAN9250_TX_CFG_TX_ON  0x00000002UL

// RX_DP_CTRL bits
#define LAN9250_RX_DP_CTRL_RX_FFWD 0x80000000UL

// RX/TX FIFO information registers
#define LAN9250_RX_FIFO_INF_RXSUSED 0x00FF0000UL   // number of RX status words available (bits 23:16)
#define LAN9250_TX_FIFO_INF_TXFREE  0x0000FFFFUL   // free space in TX data FIFO, in bytes

// RESET_CTL bits
#define LAN9250_RESET_CTL_DIGITAL_RST 0x00000001UL

// ID_REV fields
#define LAN9250_ID_REV_CHIP_ID_MASK    0xFFFF0000UL
#define LAN9250_ID_REV_CHIP_ID_LAN9250 0x92500000UL

// TX command 'A' (first DWORD written to TX_DATA_FIFO for a new frame)
#define LAN9250_TX_CMD_A_BUFFER_ALIGN_4B  0x00000000UL
#define LAN9250_TX_CMD_A_START_OFFSET_0B  0x00000000UL
#define LAN9250_TX_CMD_A_FIRST_SEG        0x00002000UL
#define LAN9250_TX_CMD_A_LAST_SEG         0x00001000UL

// TX command 'B' (second DWORD written to TX_DATA_FIFO)
#define LAN9250_TX_CMD_B_PACKET_TAG_SHIFT 16

// Number of extra bytes (2 command DWORDs) needed ahead of frame data in TX FIFO
#define LAN9250_TX_CMD_SIZE  8

// RX status word fields (read from RX_STATUS_FIFO)
#define LAN9250_RX_STS_ERROR_STATUS  0x00008000UL
#define LAN9250_RX_STS_PACKET_LEN    0x3FFF0000UL   // bits 29:16

// Host MAC CSR indirect registers (accessed through MAC_CSR_CMD / MAC_CSR_DATA)
#define LAN9250_HMAC_CR       0x01
#define LAN9250_HMAC_ADDRH    0x02
#define LAN9250_HMAC_ADDRL    0x03
#define LAN9250_HMAC_MII_ACC  0x06
#define LAN9250_HMAC_MII_DATA 0x07

// MAC_CSR_CMD bits
#define LAN9250_MAC_CSR_CMD_BUSY  0x80000000UL
#define LAN9250_MAC_CSR_CMD_READ  0x40000000UL
#define LAN9250_MAC_CSR_CMD_WRITE 0x00000000UL
#define LAN9250_MAC_CSR_CMD_ADDR  0x000000FFUL

// HMAC_CR bits
#define LAN9250_HMAC_CR_RCVOWN 0x00800000UL
#define LAN9250_HMAC_CR_FDPX   0x00100000UL
#define LAN9250_HMAC_CR_TXEN   0x00000008UL
#define LAN9250_HMAC_CR_RXEN   0x00000004UL

// HMAC_MII_ACC bits (PHY register indirect access)
#define LAN9250_HMAC_MII_ACC_PHY_ADDR_DEFAULT 0x00000800UL   // internal PHY address = 1
#define LAN9250_HMAC_MII_ACC_MIIRINDA_SHIFT   6
#define LAN9250_HMAC_MII_ACC_MIIW_R           0x00000002UL   // 1 = write, 0 = read
#define LAN9250_HMAC_MII_ACC_MIIBZY           0x00000001UL

// PHY registers (through HMAC_MII_ACC/HMAC_MII_DATA)
#define LAN9250_PHY_BASIC_STATUS 0x01

// PHY_BASIC_STATUS bits
#define LAN9250_PHY_BASIC_STATUS_LINK_STATUS 0x0004

// Maximum Ethernet frame size handled
#define LAN9250_FRAME_SIZE 1518

#endif

// ------------------------------------------------------------------------ END
