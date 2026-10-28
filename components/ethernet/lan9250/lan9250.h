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
 * @file spi_ethernet_lan9250.h
 * @brief SPI Ethernet Microchip LAN9250 Driver.
 */

#ifndef SPI_ETHERNET_LAN9250_H
#define SPI_ETHERNET_LAN9250_H

#include "drv_digital_out.h"
#include "drv_spi_master.h"
#include <stdint.h>
#include <stdbool.h>

#define LAN9250_MAP_MIKROBUS( cfg, mikrobus ) \
    cfg.miso  = MIKROBUS( mikrobus, MIKROBUS_MISO ); \
    cfg.mosi  = MIKROBUS( mikrobus, MIKROBUS_MOSI ); \
    cfg.sck   = MIKROBUS( mikrobus, MIKROBUS_SCK );  \
    cfg.cs    = MIKROBUS( mikrobus, MIKROBUS_CS );   \
    cfg.rst   = MIKROBUS( mikrobus, MIKROBUS_RST );

typedef struct {
    pin_name_t miso;
    pin_name_t mosi;
    pin_name_t sck;
    pin_name_t cs;
    pin_name_t rst;

    uint32_t spi_speed;
    spi_master_mode_t spi_mode;

    uint8_t mac[ 6 ];
    uint8_t ip[ 4 ];
    uint8_t full_duplex;
} lan9250_cfg_t;

/**
 * @brief Initialize the LAN9250 SPI Ethernet driver.
 *
 * @details Resets the LAN9250, waits for the device to become ready,
 * performs the required digital reset, reads the chip identification,
 * configures the TX FIFO, initializes the MAC address and enables
 * Ethernet transmission and reception.
 *
 * @param eth Pointer to the SPI Ethernet instance.
 * @param drv Pointer to the SPI Ethernet driver structure.
 *
 * @pre lan9250_configure() must have been called beforehand.
 *
 * @return void
 */
void     lan9250_init( spi_ethernet_t *eth, spi_ethernet_driver_t *drv );

/**
 * @brief Initialize the LAN9250 configuration structure with default values.
 *
 * @details Sets all GPIO pins to HAL_PIN_NC, configures SPI mode 0,
 * sets the default SPI speed to 1 MHz and disables full-duplex mode.
 *
 * @param cfg Pointer to the LAN9250 configuration structure.
 *
 * @return void
 */
void     lan9250_cfg_setup( lan9250_cfg_t *cfg );

/**
 * @brief Configure the SPI interface and GPIO pins for the LAN9250.
 *
 * @details Configures the SPI peripheral, initializes the chip select and
 * reset pins, and copies the MAC address, IP address and duplex setting
 * into the SPI Ethernet instance.
 *
 * @param eth Pointer to the SPI Ethernet instance.
 * @param spi Pointer to the SPI master instance.
 * @param cfg Pointer to the LAN9250 configuration structure.
 *
 * @pre lan9250_cfg_setup() should be called before this function.
 *
 * @return 0 if the configuration is successful.
 */
uint8_t  lan9250_configure( spi_ethernet_t *eth, spi_master_t *spi, lan9250_cfg_t *cfg );


/**
 * @brief Send an Ethernet frame through the LAN9250.
 *
 * @details Checks the available TX FIFO space, writes the LAN9250 TX
 * command words and copies the Ethernet frame into the TX data FIFO.
 *
 * @param eth Pointer to the SPI Ethernet instance.
 * @param buf Pointer to the Ethernet frame buffer.
 * @param len Length of the Ethernet frame in bytes.
 *
 * @pre lan9250_init() must have been called beforehand.
 * @pre @p buf must point to a buffer containing at least @p len bytes.
 *
 * @return Number of bytes written to the TX FIFO, or 0 if there is not
 * enough available FIFO space.
 */
uint16_t lan9250_send_packet( spi_ethernet_t *eth, uint8_t *buf, uint16_t len );

/**
 * @brief Read an Ethernet frame received by the LAN9250.
 *
 * @details Reads the next packet status from the RX status FIFO, checks
 * the packet status and length, and copies the received frame from the
 * RX data FIFO into the provided buffer.
 *
 * @param eth Pointer to the SPI Ethernet instance.
 * @param buf Pointer to the destination buffer.
 * @param len Maximum number of bytes that can be copied into @p buf.
 *
 * @pre lan9250_init() must have been called beforehand.
 * @pre @p buf must point to a buffer large enough to hold @p len bytes.
 *
 * @return Number of bytes copied into @p buf, or 0 if no valid packet
 * is available.
 */
uint16_t lan9250_read_packet( spi_ethernet_t *eth, uint8_t *buf, uint16_t len );

/**
 * @brief Check whether an Ethernet packet is available.
 *
 * @details Reads the LAN9250 RX FIFO information register and returns
 * the number of received packets waiting in the RX FIFO.
 *
 * @param eth Pointer to the SPI Ethernet instance.
 *
 * @return Number of packets available, limited to 255.
 */
uint8_t  lan9250_packet_available( spi_ethernet_t *eth );

/**
 * @brief Get the current Ethernet link status.
 *
 * @details Reads the internal PHY basic status register and checks
 * the link status bit.
 *
 * @pre lan9250_init() must have been called beforehand.
 *
 * @return 1 if the Ethernet link is active, otherwise 0.
 */
uint8_t  lan9250_get_link_status( void );


/**
 * @brief Get the LAN9250 revision number.
 *
 * @details Returns the least significant byte of the LAN9250 ID_REV
 * register.
 *
 * @pre lan9250_init() must have been called beforehand.
 *
 * @return LAN9250 revision value.
 *
 * @note This function returns only the low byte of ID_REV for compatibility
 * with the generic SPI Ethernet interface.
 */
uint8_t  lan9250_get_rev( void );               // low byte of ID_REV (compat spi_eth_get_rev)

/**
 * @brief Get the complete LAN9250 chip identification and revision value.
 *
 * @details Returns the complete 32-bit ID_REV register value read during
 * driver initialization.
 *
 * @pre lan9250_init() must have been called beforehand.
 *
 * @return 32-bit LAN9250 ID_REV value.
 *
 * @note The expected chip identification is 0x9250 in bits 31:16.
 */
uint32_t lan9250_get_id_rev( void );            // full 32-bit ID_REV : 0x9250xxxx expected

/**
 * @brief Set the Ethernet MAC address.
 *
 * @details Stores the MAC address locally and programs it into the
 * LAN9250 host MAC address registers.
 *
 * @param mac Pointer to the 6-byte MAC address.
 *
 * @pre lan9250_init() must have been called beforehand.
 *
 * @return 1 if the MAC address was set successfully.
 */
int      lan9250_set_mac( uint8_t mac[ 6 ] );

/**
 * @brief Get the configured Ethernet MAC address.
 *
 * @details Copies the currently configured MAC address into the
 * provided buffer.
 *
 * @param mac Pointer to the destination buffer for the 6-byte MAC address.
 *
 * @return 1 if the MAC address was copied successfully.
 */
int      lan9250_get_mac( uint8_t mac[ 6 ] );

/**
 * @brief Set the IPv4 address.
 *
 * @details Stores the IPv4 address in the LAN9250 driver configuration.
 *
 * @param ip Pointer to the 4-byte IPv4 address.
 *
 * @return 1 if the IP address was set successfully.
 */
int      lan9250_set_ip( uint8_t ip[ 4 ] );

/**
 * @brief Get the configured IPv4 address.
 *
 * @details Copies the currently configured IPv4 address into the
 * provided buffer.
 *
 * @param ip Pointer to the destination buffer for the 4-byte IPv4 address.
 *
 * @return 1 if the IP address was copied successfully.
 */
int      lan9250_get_ip( uint8_t ip[ 4 ] );

extern spi_ethernet_driver_t lan9250_driver;
extern pin_name_t            lan9250_cs_pin;

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
