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
 * @file lan8651.h
 * @brief SPI Ethernet Microchip LAN8651 10BASE-T1S MAC-PHY Driver.
 * @details Used on Two-Wire ETH Click and Two-Wire ETH 3 Click.
 * The device is accessed over the OPEN Alliance TC6 (10BASE-T1x MAC-PHY
 * Serial Interface) protocol: register access through control transactions
 * and Ethernet frames through 64-byte data chunks.
 *
 * Several devices can be used at the same time (e.g. one click per mikroBUS):
 * give each spi_ethernet_t its own lan8651_ctx_t through driver_ctx before
 * calling lan8651_configure(). Without it, a built-in context is used.
 */

#ifndef SPI_ETHERNET_LAN8651_H
#define SPI_ETHERNET_LAN8651_H

#include "drv_digital_out.h"
#include "drv_spi_master.h"
#include <stdint.h>
#include <stdbool.h>

#define LAN8651_MAP_MIKROBUS( cfg, mikrobus ) \
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

    uint8_t plca_enable;        // 0 = CSMA/CD (default), 1 = PLCA
    uint8_t plca_node_id;       // PLCA local node ID (0 = coordinator)
    uint8_t plca_node_count;    // PLCA node count (used by the coordinator only)
} lan8651_cfg_t;

/**
 * @brief Initializes the LAN8651 Ethernet controller.
 *
 * Performs hardware and software reset, applies the AN1760 configuration
 * fixups, configures PLCA/CSMA-CD, programs the MAC address and enables
 * the MAC transmitter and receiver.
 *
 * @param[in] eth SPI Ethernet instance.
 * @param[in] drv LAN8651 driver instance.
 */
void     lan8651_init( spi_ethernet_t *eth, spi_ethernet_driver_t *drv );

/**
 * @brief Initializes the LAN8651 configuration structure with default values.
 *
 * @param[out] cfg LAN8651 configuration structure.
 */
void     lan8651_cfg_setup( lan8651_cfg_t *cfg );

/**
 * @brief Configures the SPI interface and LAN8651 control pins.
 *
 * @param[in] eth SPI Ethernet instance. If eth->driver_ctx is NULL the
 *                built-in context is used, otherwise it must point to a
 *                lan8651_ctx_t owned by the caller (one per device).
 * @param[in] spi SPI master instance.
 * @param[in] cfg LAN8651 configuration structure.
 *
 * @return Configuration status.
 */
uint8_t  lan8651_configure( spi_ethernet_t *eth, spi_master_t *spi, lan8651_cfg_t *cfg );

/**
 * @brief Selects the device used by driver functions without an instance argument.
 *
 * @details get_link_status, set_mac, get_mac, set_ip, get_ip, get_rev and
 * get_phy_id act on the active device. It is updated automatically by
 * init/send/read/available; call this before the others when more than
 * one LAN8651 is used.
 *
 * @param[in] eth SPI Ethernet instance to make active.
 */
void     lan8651_set_active( spi_ethernet_t *eth );

/**
 * @brief Sends an Ethernet frame as a sequence of TC6 data chunks.
 *
 * @param[in] eth SPI Ethernet instance.
 * @param[in] buf Ethernet frame buffer (without FCS).
 * @param[in] len Ethernet frame length in bytes.
 *
 * @return Number of bytes sent, 0 on failure.
 */
uint16_t lan8651_send_packet( spi_ethernet_t *eth, uint8_t *buf, uint16_t len );

/**
 * @brief Reads an Ethernet frame from the LAN8651 receive buffer.
 *
 * @param[in] eth SPI Ethernet instance.
 * @param[out] buf Buffer receiving the Ethernet frame (without FCS).
 * @param[in] len Maximum number of bytes to read.
 *
 * @return Number of bytes read, 0 if no frame is available.
 */
uint16_t lan8651_read_packet( spi_ethernet_t *eth, uint8_t *buf, uint16_t len );

/**
 * @brief Checks whether an Ethernet frame is available.
 *
 * @param[in] eth SPI Ethernet instance.
 *
 * @return 1 if a packet is available, otherwise 0.
 */
uint8_t  lan8651_packet_available( spi_ethernet_t *eth );

/**
 * @brief Gets the Ethernet link status.
 *
 * @details 10BASE-T1S has no link pulses in CSMA/CD mode, so the link is
 * reported up while the MAC-PHY responds and its configuration is
 * synchronized. In PLCA mode the PLCA status (beacons seen) is reported.
 *
 * @return 1 if the Ethernet link is up, otherwise 0.
 */
uint8_t  lan8651_get_link_status( void );

/**
 * @brief Gets the LAN8651 model/revision byte (lowest byte of OA PHYID).
 *
 * @return LAN8651 model/revision byte.
 */
uint8_t  lan8651_get_rev( void );

/**
 * @brief Gets the full OPEN Alliance PHY identification register.
 *
 * @return OA_PHYID register value.
 */
uint32_t lan8651_get_phy_id( void );

/**
 * @brief Sets the Ethernet MAC address.
 *
 * @param[in] mac MAC address to configure.
 *
 * @return 1 on success.
 */
int      lan8651_set_mac( uint8_t mac[ 6 ] );

/**
 * @brief Gets the configured Ethernet MAC address.
 *
 * @param[out] mac Buffer receiving the MAC address.
 *
 * @return 1 on success.
 */
int      lan8651_get_mac( uint8_t mac[ 6 ] );

/**
 * @brief Sets the IPv4 address.
 *
 * @param[in] ip IPv4 address to configure.
 *
 * @return 1 on success.
 */
int      lan8651_set_ip( uint8_t ip[ 4 ] );

/**
 * @brief Gets the configured IPv4 address.
 *
 * @param[out] ip Buffer receiving the IPv4 address.
 *
 * @return 1 on success.
 */
int      lan8651_get_ip( uint8_t ip[ 4 ] );

extern spi_ethernet_driver_t    lan8651_driver;

// Memory map selectors
#define LAN8651_MMS_OA              0x00    // OPEN Alliance standard registers
#define LAN8651_MMS_MAC             0x01    // MAC registers
#define LAN8651_MMS_PHY_VS_PLCA     0x04    // PHY vendor specific / PLCA registers

// Control transaction header
#define LAN8651_CTRL_HDR_WNR        0x20000000UL
#define LAN8651_CTRL_HDR_MMS_SHIFT  24
#define LAN8651_CTRL_HDR_ADDR_SHIFT 8

// Data chunk header (host -> MAC-PHY)
#define LAN8651_DATA_HDR_DNC        0x80000000UL
#define LAN8651_DATA_HDR_NORX       0x20000000UL
#define LAN8651_DATA_HDR_DV         0x00200000UL
#define LAN8651_DATA_HDR_SV         0x00100000UL
#define LAN8651_DATA_HDR_EV         0x00004000UL
#define LAN8651_DATA_HDR_EBO_SHIFT  8

// Data chunk footer (MAC-PHY -> host)
#define LAN8651_DATA_FTR_EXST       0x80000000UL
#define LAN8651_DATA_FTR_HDRB       0x40000000UL
#define LAN8651_DATA_FTR_SYNC       0x20000000UL
#define LAN8651_DATA_FTR_RCA_SHIFT  24
#define LAN8651_DATA_FTR_DV         0x00200000UL
#define LAN8651_DATA_FTR_SV         0x00100000UL
#define LAN8651_DATA_FTR_SWO_SHIFT  16
#define LAN8651_DATA_FTR_EV         0x00004000UL
#define LAN8651_DATA_FTR_EBO_SHIFT  8
#define LAN8651_DATA_FTR_TXC_SHIFT  1

// OPEN Alliance standard registers (MMS 0)
#define LAN8651_OA_PHYID            0x0001
#define LAN8651_OA_RESET            0x0003
#define LAN8651_OA_RESET_SWRESET    0x00000001UL
#define LAN8651_OA_CONFIG0          0x0004
#define LAN8651_OA_CONFIG0_SYNC     0x00008000UL
#define LAN8651_OA_CONFIG0_ZARFE    0x00001000UL
#define LAN8651_OA_STATUS0          0x0008
#define LAN8651_OA_STATUS0_RESETC   0x00000040UL
#define LAN8651_OA_STATUS0_RXBOE    0x00000008UL
#define LAN8651_OA_BUFSTS           0x000B

// MAC registers (MMS 1)
#define LAN8651_MAC_NCR             0x0000
#define LAN8651_MAC_NCR_TXEN        0x00000008UL
#define LAN8651_MAC_NCR_RXEN        0x00000004UL
#define LAN8651_MAC_SAB1            0x0022
#define LAN8651_MAC_SAT1            0x0023
#define LAN8651_MAC_TISUBN          0x0077
#define LAN8651_MAC_TI_40NS         0x00000028UL

// PHY vendor specific / PLCA registers (MMS 4)
#define LAN8651_VS_CFGPARAM_ADDR    0x00D8
#define LAN8651_VS_CFGPARAM_DATA    0x00D9
#define LAN8651_VS_CFGPARAM_CTRL    0x00DA
#define LAN8651_VS_CFGPARAM_READ    0x0002
#define LAN8651_VS_CDCTL0           0x0087
#define LAN8651_VS_CDCTL0_CDEN      0x00008000UL
#define LAN8651_PLCA_CTRL0          0xCA01
#define LAN8651_PLCA_CTRL0_EN       0x00008000UL
#define LAN8651_PLCA_CTRL1          0xCA02
#define LAN8651_PLCA_STS            0xCA03
#define LAN8651_PLCA_STS_PST        0x00008000UL

#define LAN8651_CHUNK_PAYLOAD_SIZE  64
#define LAN8651_CHUNK_SIZE          ( LAN8651_CHUNK_PAYLOAD_SIZE + 4 )
#define LAN8651_FCS_SIZE            4
#define LAN8651_MIN_FRAME_SIZE      60
#define LAN8651_FRAME_SIZE          1518

// Per-device driver state, referenced through spi_ethernet_t.driver_ctx
typedef struct {
    pin_name_t cs_pin;
    uint8_t  mac[ 6 ];
    uint8_t  ip[ 4 ];
    uint32_t phy_id;
    uint8_t  plca_enable;
    uint8_t  plca_node_id;
    uint8_t  plca_node_count;

    uint8_t  rx_frame[ LAN8651_FRAME_SIZE + LAN8651_FCS_SIZE ];
    uint16_t rx_len;
    uint8_t  rx_in_progress;    // frame start received, end not yet
    uint8_t  rx_ready;          // complete frame waiting in rx_frame
    uint8_t  tx_credits;
    uint8_t  rx_chunks;
} lan8651_ctx_t;

#endif

// ------------------------------------------------------------------------ END
