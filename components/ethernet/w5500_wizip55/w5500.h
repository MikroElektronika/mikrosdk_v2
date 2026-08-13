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
 * @file spi_ethernet_w5500.h
 * @brief SPI Ethernet WIZnet W5500 Driver.
 */

#ifndef SPI_ETHERNET_W5500_H
#define SPI_ETHERNET_W5500_H

#include "drv_digital_out.h"
#include "drv_spi_master.h"
#include <stdint.h>
#include <stdbool.h>

#define W5500_MAP_MIKROBUS( cfg, mikrobus ) \
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
} w5500_cfg_t;

/**
 * @brief Initialize the W5500 SPI Ethernet driver.
 *
 * @details Resets the W5500, reads its hardware revision, configures
 * the MAC and IP addresses, and opens socket 0 in MACRAW mode for
 * raw Ethernet frame transmission and reception.
 *
 * @param eth Pointer to the SPI Ethernet instance.
 * @param drv Pointer to the SPI Ethernet driver structure.
 *
 * @pre w5500_configure() must have been called beforehand.
 *
 * @return void
 */
void     w5500_init( spi_ethernet_t *eth, spi_ethernet_driver_t *drv );

/**
 * @brief Initialize the W5500 configuration structure with default values.
 *
 * @details Sets all GPIO pins to HAL_PIN_NC, configures SPI mode 0,
 * sets the default SPI speed to 1 MHz and disables full-duplex mode.
 *
 * @param cfg Pointer to the W5500 configuration structure.
 *
 * @return void
 */
void     w5500_cfg_setup( w5500_cfg_t *cfg );

/**
 * @brief Configure the SPI interface and GPIO pins for the W5500.
 *
 * @details Configures the SPI peripheral, initializes the chip select
 * and reset pins, and copies the MAC address, IP address and duplex
 * configuration into the SPI Ethernet instance.
 *
 * @param eth Pointer to the SPI Ethernet instance.
 * @param spi Pointer to the SPI master instance.
 * @param cfg Pointer to the W5500 configuration structure.
 *
 * @pre w5500_cfg_setup() should be called before this function.
 *
 * @return 0 if the configuration is successful.
 */
uint8_t  w5500_configure( spi_ethernet_t *eth, spi_master_t *spi, w5500_cfg_t *cfg );

/**
 * @brief Send an Ethernet frame through the W5500.
 *
 * @details Writes the Ethernet frame to the socket 0 TX buffer,
 * updates the TX write pointer and issues the SEND command.
 * Socket 0 operates in MACRAW mode.
 *
 * @param eth Pointer to the SPI Ethernet instance.
 * @param buf Pointer to the Ethernet frame buffer.
 * @param len Length of the Ethernet frame in bytes.
 *
 * @pre w5500_init() must have been called beforehand.
 * @pre @p buf must point to a buffer containing at least @p len bytes.
 *
 * @return Number of bytes sent.
 */
uint16_t w5500_send_packet( spi_ethernet_t *eth, uint8_t *buf, uint16_t len );

/**
 * @brief Read an Ethernet frame received by the W5500.
 *
 * @details Reads the next frame from the socket 0 RX buffer in MACRAW
 * mode, removes the two-byte frame length header and copies the frame
 * into the provided buffer.
 *
 * @param eth Pointer to the SPI Ethernet instance.
 * @param buf Pointer to the destination buffer.
 * @param len Maximum number of bytes that can be copied into @p buf.
 *
 * @pre w5500_init() must have been called beforehand.
 * @pre @p buf must point to a buffer large enough to hold @p len bytes.
 *
 * @return Number of bytes copied into @p buf, or 0 if no valid packet
 * is available.
 */
uint16_t w5500_read_packet( spi_ethernet_t *eth, uint8_t *buf, uint16_t len );


/**
 * @brief Check whether an Ethernet packet is available.
 *
 * @details Reads the socket 0 RX Received Size Register and checks
 * whether at least one Ethernet frame is waiting in the RX buffer.
 *
 * @param eth Pointer to the SPI Ethernet instance.
 *
 * @return 1 if a packet is available, otherwise 0.
 */
uint8_t  w5500_packet_available( spi_ethernet_t *eth );


/**
 * @brief Get the current Ethernet link status.
 *
 * @details Verifies the W5500 hardware revision and reads the PHY
 * configuration register to determine whether the Ethernet link is active.
 *
 * @pre w5500_init() must have been called beforehand.
 *
 * @return 1 if the Ethernet link is active, otherwise 0.
 */
uint8_t  w5500_get_link_status( void );

/**
 * @brief Get the W5500 hardware revision.
 *
 * @details Returns the hardware revision value read from the W5500
 * VERSIONR register during initialization.
 *
 * @pre w5500_init() must have been called beforehand.
 *
 * @return W5500 hardware revision value.
 */
uint8_t  w5500_get_rev( void );

/**
 * @brief Set the Ethernet MAC address.
 *
 * @details Stores the MAC address locally and writes it to the W5500
 * Source Hardware Address Register.
 *
 * @param mac Pointer to the 6-byte MAC address.
 *
 * @pre w5500_init() must have been called beforehand.
 *
 * @return 1 if the MAC address was set successfully.
 */
int      w5500_set_mac( uint8_t mac[ 6 ] );

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
int      w5500_get_mac( uint8_t mac[ 6 ] );

/**
 * @brief Set the IPv4 address.
 *
 * @details Stores the IPv4 address locally and writes it to the W5500
 * Source IP Address Register.
 *
 * @param ip Pointer to the 4-byte IPv4 address.
 *
 * @pre w5500_init() must have been called beforehand.
 *
 * @return 1 if the IP address was set successfully.
 */
int      w5500_set_ip( uint8_t ip[ 4 ] );

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
int      w5500_get_ip( uint8_t ip[ 4 ] );

extern spi_ethernet_driver_t w5500_driver;
extern pin_name_t            w5500_cs_pin;

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
#define W5500_MR              0x0000
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
