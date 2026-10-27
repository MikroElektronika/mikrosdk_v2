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
 * @file eth_transport.h
 * @brief Ethernet transport core: device instance, controller driver
 * interface and bus interface.
 * @details The Ethernet stack is split in independent layers, each one only
 * knows the layer below it through an interface defined in this file:
 *
 *     application, eth_net (ARP, ICMP, TCP, UDP, DHCP)
 *         |  eth_transport_* API
 *     controller driver (components/ethernet/<chip>)   implements eth_transport_driver_t
 *         |  eth_transport_bus_write/read/transfer()
 *     bus binding (middleware/ethernet/<bus>)          implements eth_bus_ops_t
 *         |  mikroSDK peripheral drivers (SPI, I2C, UART, ...)
 *
 * Nothing above a layer depends on how that layer is implemented:
 * - Adding a bus (I2C, UART, ...): create middleware/ethernet/<bus> with an
 *   eth_bus_ops_t implementation and a configure function that opens the
 *   peripheral and calls eth_transport_configure(), see eth_bus_spi.h.
 * - Adding a controller: implement eth_transport_driver_t, do all register
 *   access through eth_transport_bus_*() and keep per-device state in
 *   eth->driver_ctx, see components/ethernet/enc28j60.
 * - Switching controller or bus in an application only changes its
 *   configure call and the driver passed to eth_transport_init().
 */

#ifndef _ETH_TRANSPORT_H
#define _ETH_TRANSPORT_H

#ifdef __cplusplus
extern "C"{
#endif

#include "drv_digital_out.h"
#include <stdint.h>

/**
 * @addtogroup middlewaregroup Middleware Libraries
 * @{
 */

/**
 * @defgroup eth_transport Ethernet Transport
 * @brief Bus and controller independent Ethernet device layer.
 * @{
 */

/**
 * @brief Return values.
 */
#define ETH_TRANSPORT_SUCCESS   ( 0 )
#define ETH_TRANSPORT_ERROR     ( -1 )

/**
 * @brief Map the bus independent pins (reset) to a mikroBUS position.
 */
#define ETH_TRANSPORT_MAP_MIKROBUS( cfg, mikrobus ) \
    cfg.rst = MIKROBUS( mikrobus, MIKROBUS_RST );

typedef struct eth_transport eth_transport_t;
typedef struct eth_transport_driver eth_transport_driver_t;
typedef struct eth_bus_ops eth_bus_ops_t;

/**
 * @brief Bus interface, implemented once per bus type (SPI, I2C, UART, ...).
 * @details Each callback is one complete bus transaction on the device
 * @p bus was opened for. @p bus is the binding's own object (e.g.
 * eth_bus_spi_t), the core never looks inside it.
 */
struct eth_bus_ops {
    /**
     * Send @p hdr then @p data (may be NULL / 0) in one transaction.
     * SPI: one chip select assertion. I2C: one write to the device address.
     * UART: the bytes back to back.
     */
    err_t ( *write )( void *bus, uint8_t *hdr, uint16_t hdr_len, uint8_t *data, uint16_t data_len );
    /**
     * Send @p hdr, then receive @p data_len bytes into @p data, in one transaction.
     * SPI: write then read under one chip select. I2C: write, repeated start, read.
     * UART: send, then wait for the reply bytes.
     */
    err_t ( *read )( void *bus, uint8_t *hdr, uint16_t hdr_len, uint8_t *data, uint16_t data_len );
    /**
     * Optional full duplex exchange of @p len bytes (SPI only), NULL if the
     * bus cannot do it. Only controllers that need it (e.g. LAN8651) use it.
     */
    err_t ( *transfer )( void *bus, uint8_t *tx, uint8_t *rx, uint16_t len );
};

/**
 * @brief Bus independent device configuration.
 */
typedef struct {
    pin_name_t rst;             // Reset pin, HAL_PIN_NC if not connected
    uint8_t mac[ 6 ];           // MAC address
    uint8_t ip[ 4 ];            // IPv4 address
    uint8_t full_duplex;        // 1 = full duplex, 0 = half duplex
} eth_transport_cfg_t;

/**
 * @brief Ethernet device instance (one per Ethernet controller).
 */
struct eth_transport {
    void *bus;                  // Bus binding object (e.g. eth_bus_spi_t)
    eth_bus_ops_t *bus_ops;     // Bus binding operations (e.g. eth_bus_spi_ops)
    digital_out_t reset;        // Reset pin

    uint8_t mac[ 6 ];           // MAC address
    uint8_t ip[ 4 ];            // IPv4 address
    uint8_t full_duplex;        // 1 = full duplex, 0 = half duplex

    void *driver_ctx;           // Controller driver state (e.g. enc28j60_ctx_t), one per device
    eth_transport_driver_t *drv;
};

/**
 * @brief Ethernet controller driver interface.
 * @details All callbacks receive the device instance, drivers keep their
 * state in eth->driver_ctx so several devices can be used at the same time.
 * MAC and IP addresses are kept in the instance; set_mac and set_ip are
 * only needed when the controller has to be programmed with them.
 */
struct eth_transport_driver {
    err_t    ( *init )( eth_transport_t *eth );                                     // Mandatory
    err_t    ( *reset )( eth_transport_t *eth );                                    // Optional, init is used if NULL
    uint16_t ( *send_packet )( eth_transport_t *eth, uint8_t *buf, uint16_t len );  // Mandatory
    uint16_t ( *read_packet )( eth_transport_t *eth, uint8_t *buf, uint16_t len );  // Mandatory
    uint8_t  ( *available )( eth_transport_t *eth );                                // Mandatory
    uint8_t  ( *get_link_status )( eth_transport_t *eth );                          // Mandatory
    err_t    ( *set_mac )( eth_transport_t *eth, uint8_t *mac );                    // Optional
    err_t    ( *set_ip )( eth_transport_t *eth, uint8_t *ip );                      // Optional
};

/**
 * @brief Initialize the device configuration structure.
 * @details Reset pin not connected, MAC and IP cleared, half duplex.
 * @param[out] cfg Device configuration.
 * @return Nothing.
 */
void eth_transport_cfg_setup( eth_transport_cfg_t *cfg );

/**
 * @brief Attach an opened bus to the instance and apply the device configuration.
 * @details Called by bus bindings (e.g. eth_bus_spi_configure()) once the
 * peripheral is open. Initializes the reset pin and stores the MAC address,
 * IP address and duplex setting. eth->driver_ctx is not modified.
 * @param[in,out] eth Ethernet transport instance.
 * @param[in] bus Bus binding object.
 * @param[in] bus_ops Bus binding operations.
 * @param[in] cfg Device configuration.
 * @return ETH_TRANSPORT_SUCCESS on success, ETH_TRANSPORT_ERROR otherwise.
 */
err_t eth_transport_configure( eth_transport_t *eth, void *bus, eth_bus_ops_t *bus_ops,
                               eth_transport_cfg_t *cfg );

/**
 * @brief Bus access for controller drivers: one write transaction.
 * @param[in] eth Ethernet transport instance.
 * @param[in] hdr Bytes sent first (command / address).
 * @param[in] hdr_len Number of header bytes.
 * @param[in] data Bytes sent after the header, NULL if none.
 * @param[in] data_len Number of data bytes.
 * @return Bus result, ETH_TRANSPORT_ERROR if no bus is attached.
 */
err_t eth_transport_bus_write( eth_transport_t *eth, uint8_t *hdr, uint16_t hdr_len,
                               uint8_t *data, uint16_t data_len );

/**
 * @brief Bus access for controller drivers: one write-then-read transaction.
 * @param[in] eth Ethernet transport instance.
 * @param[in] hdr Bytes sent first (command / address).
 * @param[in] hdr_len Number of header bytes.
 * @param[out] data Buffer receiving the reply.
 * @param[in] data_len Number of bytes to read.
 * @return Bus result, ETH_TRANSPORT_ERROR if no bus is attached.
 */
err_t eth_transport_bus_read( eth_transport_t *eth, uint8_t *hdr, uint16_t hdr_len,
                              uint8_t *data, uint16_t data_len );

/**
 * @brief Bus access for controller drivers: one full duplex exchange.
 * @param[in] eth Ethernet transport instance.
 * @param[in] tx Bytes to send.
 * @param[out] rx Buffer receiving the same number of bytes.
 * @param[in] len Number of bytes.
 * @return Bus result, ETH_TRANSPORT_ERROR if no bus is attached or the bus
 * does not support full duplex transfers.
 */
err_t eth_transport_bus_transfer( eth_transport_t *eth, uint8_t *tx, uint8_t *rx, uint16_t len );

/**
 * @brief Initialize the Ethernet controller.
 * @details Associates @p eth with @p drv and runs the driver initialization.
 * @param[in,out] eth Ethernet transport instance, already configured.
 * @param[in] drv Ethernet controller driver.
 * @return ETH_TRANSPORT_SUCCESS on success, ETH_TRANSPORT_ERROR otherwise.
 * @pre The controller configure function (e.g. enc28j60_configure()) must
 * have been called beforehand.
 */
err_t eth_transport_init( eth_transport_t *eth, eth_transport_driver_t *drv );

/**
 * @brief Reset the Ethernet controller.
 * @details Calls the driver reset routine, or reinitializes the controller
 * if the driver does not provide one. Link and session state is lost.
 * @param[in,out] eth Ethernet transport instance.
 * @return ETH_TRANSPORT_SUCCESS on success, ETH_TRANSPORT_ERROR otherwise.
 */
err_t eth_transport_reset( eth_transport_t *eth );

/**
 * @brief Send a raw Ethernet frame.
 * @details The frame must be complete (header and payload, without FCS).
 * @param[in] eth Ethernet transport instance.
 * @param[in] buf Frame to send.
 * @param[in] len Frame length in bytes.
 * @return Number of bytes sent, 0 on error.
 */
uint16_t eth_transport_send( eth_transport_t *eth, uint8_t *buf, uint16_t len );

/**
 * @brief Receive a raw Ethernet frame, if one is available.
 * @details Frames longer than @p max_len are truncated.
 * @param[in] eth Ethernet transport instance.
 * @param[out] buf Buffer receiving the frame.
 * @param[in] max_len Size of @p buf in bytes.
 * @return Number of bytes received, 0 if no frame is available or on error.
 */
uint16_t eth_transport_receive( eth_transport_t *eth, uint8_t *buf, uint16_t max_len );

/**
 * @brief Check whether received frames are waiting.
 * @param[in] eth Ethernet transport instance.
 * @return Number of frames waiting (driver dependent, may be capped at 1),
 * 0 if none or on error.
 */
uint8_t eth_transport_available( eth_transport_t *eth );

/**
 * @brief Get the physical link status.
 * @param[in] eth Ethernet transport instance.
 * @return 1 if the link is up, 0 if it is down or on error.
 */
uint8_t eth_transport_get_link_status( eth_transport_t *eth );

/**
 * @brief Set the MAC address.
 * @details Stores the address in @p eth and programs the controller.
 * @param[in,out] eth Ethernet transport instance.
 * @param[in] mac 6-byte MAC address.
 * @return ETH_TRANSPORT_SUCCESS on success, ETH_TRANSPORT_ERROR otherwise.
 */
err_t eth_transport_set_mac( eth_transport_t *eth, uint8_t *mac );

/**
 * @brief Get the MAC address.
 * @param[in] eth Ethernet transport instance.
 * @param[out] mac 6-byte buffer receiving the MAC address.
 * @return ETH_TRANSPORT_SUCCESS on success, ETH_TRANSPORT_ERROR otherwise.
 */
err_t eth_transport_get_mac( eth_transport_t *eth, uint8_t *mac );

/**
 * @brief Set the IPv4 address.
 * @details Stores the address in @p eth and programs the controller if it
 * uses it (e.g. W5500/W6100), it is not validated in any way.
 * @param[in,out] eth Ethernet transport instance.
 * @param[in] ip 4-byte IPv4 address.
 * @return ETH_TRANSPORT_SUCCESS on success, ETH_TRANSPORT_ERROR otherwise.
 */
err_t eth_transport_set_ip( eth_transport_t *eth, uint8_t *ip );

/**
 * @brief Get the IPv4 address.
 * @param[in] eth Ethernet transport instance.
 * @param[out] ip 4-byte buffer receiving the IPv4 address.
 * @return ETH_TRANSPORT_SUCCESS on success, ETH_TRANSPORT_ERROR otherwise.
 */
err_t eth_transport_get_ip( eth_transport_t *eth, uint8_t *ip );

/*! @} */ // eth_transport
/*! @} */ // middlewaregroup

#ifdef __cplusplus
}
#endif
#endif // _ETH_TRANSPORT_H

// ------------------------------------------------------------------------ END
