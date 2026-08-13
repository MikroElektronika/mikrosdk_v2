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
 * @file transport.h
 * @brief SPI Ethernet Driver.
 */

#ifndef SPI_ETHERNET_H
#define SPI_ETHERNET_H

#ifdef __cplusplus
extern "C"{
#endif

#include "drv_spi_master.h"
#include <stdint.h>

#define ETH_HEADER_SIZE 14
#define ETH_MAX_PAYLOAD 1500
#define ETH_MAX_FRAME   ( ETH_HEADER_SIZE + ETH_MAX_PAYLOAD )
#define ENC28J60        0
#define W5500           1
#define WIZ_IP55        W5500
#define LAN9250         2
#define W6100           3

#define TCP_FLAG_FIN    0x01
#define TCP_FLAG_SYN    0x02
#define TCP_FLAG_ACK    0x10

typedef struct
{
    uint8_t mac[ 6 ];
} ethernet_device_t;

typedef struct
{
    uint8_t dest[ 6 ];
    uint8_t src[ 6 ];
    uint16_t type;
    uint8_t payload[ ETH_MAX_PAYLOAD ];
    uint16_t payload_len;
} ethernet_frame_t;

typedef struct spi_ethernet spi_ethernet_t;
typedef struct spi_ethernet_driver spi_ethernet_driver_t;

struct spi_ethernet {
    // SPI interface handle/pointer
    spi_master_t *spi;                 // Pointer to already initialized SPI object
    digital_out_t cs;                  // Chip select pin for this device
    digital_out_t reset;               // Optional reset pin
    digital_out_t int_pin;             // Optional interrupt pin

    // Device/driver-specific context
    void *driver_ctx;           // Pointer to driver-specific structure (e.g., enc28j60 state)

    // Status flags
    uint8_t link_up;            // 1 if link is active, 0 if down
    uint8_t initialized;        // 1 if device has been initialized

    // Optional: network configuration
    uint8_t mac[ 6 ];           // MAC address
    uint32_t ip;                // IP address (optional if library handles DHCP externally)

    uint8_t fullDuplex;

    spi_ethernet_driver_t *drv;
};

/* Driver interface */
struct spi_ethernet_driver{
    void     ( *init )( spi_ethernet_t *eth, spi_ethernet_driver_t *drv );
    int      ( *reset )( void );
    uint16_t ( *send_packet )( spi_ethernet_t *eth, uint8_t *buf, uint16_t len );
    uint16_t ( *read_packet )( spi_ethernet_t *eth, uint8_t *buf, uint16_t len );
    uint8_t ( *available )( spi_ethernet_t *eth );
    uint8_t  ( *get_link_status )( void );
    int      ( *set_mac )( uint8_t mac[ 6 ] );
    int      ( *get_mac )( uint8_t mac[ 6 ] );
    int      ( *set_ip )( uint8_t ip[ 4 ] );
    int      ( *get_ip )( uint8_t ip[ 4 ] );
};

typedef enum {
    SPI_ETH_IOCTL_PACKET_START = 0,
    SPI_ETH_IOCTL_PACKET_WRITE,
    SPI_ETH_IOCTL_PACKET_END,
    SPI_ETH_IOCTL_PACKET_AVAILABLE,
    SPI_ETH_IOCTL_PACKET_READ,
    SPI_ETH_IOCTL_MODULE_SPECIFIC = 0xF0  // reserved for module-specific commands
} spi_ethernet_ioctl_cmd_t;

/* Library API */
/**
 * @brief Initialize the SPI Ethernet interface.
 *
 * @details Associates an Ethernet device instance with its low-level driver
 * and calls the driver-specific initialization routine if available.
 * This function must be called before using any other SPI Ethernet API
 * functions. The driver structure provides the hardware-dependent operations
 * required to communicate with the Ethernet controller.
 *
 * @param eth Pointer to the SPI Ethernet instance to initialize.
 * @param drv Pointer to the SPI Ethernet driver implementation containing
 *            hardware-specific callbacks.
 *
 * @pre @p eth and @p drv must point to valid allocated structures.
 * @pre The driver structure must be properly configured before initialization.
 *
 * @post The Ethernet instance is linked to the provided driver and the
 *       driver initialization routine is executed if defined.
 *
 * @note This function does not configure network parameters such as MAC or IP
 *       addresses. Use the corresponding address configuration functions
 *       after initialization.
 *
 * @warning Passing NULL pointers has no effect and the initialization is aborted.
 *          The caller is responsible for ensuring that the driver instance
 *          remains valid during the lifetime of the Ethernet object.
 *
 * @return void
 *
 * @see spi_ethernet_reset
 * @see spi_ethernet_set_mac
 * @see spi_ethernet_set_ip
 */
void spi_ethernet_init( spi_ethernet_t *eth, spi_ethernet_driver_t *drv );

/**
 * @brief Reset the Ethernet controller.
 *
 * @details Calls the driver-specific reset routine to reinitialize the
 * underlying Ethernet controller hardware. This is typically used to
 * recover from an error state or to reinitialize the device without
 * a full power cycle.
 *
 * @param eth Pointer to the SPI Ethernet instance.
 *
 * @pre spi_ethernet_init() must have been called beforehand, and @p eth
 *      must be associated with a valid driver exposing a reset callback.
 *
 * @return int 0 (or driver-defined success code) on success, -1 if
 *         @p eth, its driver, or the reset callback is NULL/undefined.
 *
 * @note The exact return value on success depends on the underlying driver
 *       implementation.
 * @warning Resetting the controller may drop any ongoing link/session state.
 *
 * @see spi_ethernet_init
 */
int  spi_ethernet_reset( spi_ethernet_t *eth );

/**
 * @brief Send a raw Ethernet frame.
 *
 * @details Forwards the given buffer to the driver-specific packet
 * transmission routine. The buffer must already contain a fully formed
 * Ethernet frame (headers and payload); this function does not build or
 * validate any protocol headers.
 *
 * @param eth Pointer to the SPI Ethernet instance.
 * @param buf Pointer to the buffer containing the frame to send.
 * @param len Length in bytes of the frame to send.
 *
 * @pre spi_ethernet_init() must have been called beforehand.
 * @pre @p buf must point to a valid, fully constructed Ethernet frame of
 *      at least @p len bytes.
 *
 * @return int Number of bytes sent (driver-dependent) on success, -1 if
 *         @p eth, its driver, or the send_packet callback is NULL/undefined.
 *
 * @note This function does not compute or verify checksums; the caller is
 *       responsible for providing a complete, valid frame.
 * @warning Requires spi_ethernet_init() to have completed successfully.
 *
 * @see spi_ethernet_receive
 */
int  spi_ethernet_send( spi_ethernet_t *eth, uint8_t *buf, uint16_t len );

/**
 * @brief Receive a raw Ethernet frame, if one is available.
 *
 * @details Forwards the request to the driver-specific packet reception
 * routine, which reads the next available frame from the controller's
 * receive buffer into @p buf. If no frame is currently available, the
 * underlying driver returns 0.
 *
 * @param eth Pointer to the SPI Ethernet instance.
 * @param buf Pointer to the buffer where the received frame will be stored.
 * @param max_len Maximum number of bytes that @p buf can hold.
 *
 * @pre spi_ethernet_init() must have been called beforehand.
 * @pre @p buf must point to a buffer of at least @p max_len bytes.
 *
 * @return int Number of bytes actually received (0 if no frame is
 *         available) on success, -1 if @p eth, its driver, or the
 *         read_packet callback is NULL/undefined.
 *
 * @note Frames larger than @p max_len may be truncated depending on the
 *       underlying driver implementation.
 * @warning Requires spi_ethernet_init() to have completed successfully.
 *
 * @see spi_ethernet_send
 * @see spi_ethernet_available
 */
int  spi_ethernet_receive( spi_ethernet_t *eth, uint8_t *buf, uint16_t max_len );

/**
 * @brief Set the MAC address used by the Ethernet controller.
 *
 * @details Forwards the given MAC address to the driver-specific set_mac
 * routine, which typically writes it into the controller's hardware
 * address registers.
 *
 * @param eth Pointer to the SPI Ethernet instance.
 * @param mac 6-byte array containing the new MAC address to apply.
 *
 * @pre spi_ethernet_init() must have been called beforehand.
 *
 * @return int Driver-defined success code (typically non-zero) on success,
 *         -1 if @p eth, its driver, or the set_mac callback is
 *         NULL/undefined.
 *
 * @note Changing the MAC address after the link is already established may
 *       require reinitializing the controller depending on the driver.
 * @warning Requires spi_ethernet_init() to have completed successfully.
 *
 * @see spi_ethernet_get_mac
 */
int  spi_ethernet_set_mac( spi_ethernet_t *eth, uint8_t mac[ 6 ] );

/**
 * @brief Retrieve the MAC address currently used by the Ethernet controller.
 *
 * @details Forwards the request to the driver-specific get_mac routine,
 * which copies the controller's current hardware address into @p mac.
 *
 * @param eth Pointer to the SPI Ethernet instance.
 * @param mac 6-byte array to receive the current MAC address.
 *
 * @pre spi_ethernet_init() must have been called beforehand.
 * @pre @p mac must point to a writable buffer of at least 6 bytes.
 *
 * @return int Driver-defined success code (typically non-zero) on success,
 *         -1 if @p eth, its driver, or the get_mac callback is
 *         NULL/undefined.
 *
 * @warning Requires spi_ethernet_init() to have completed successfully.
 *
 * @see spi_ethernet_set_mac
 */
int  spi_ethernet_get_mac( spi_ethernet_t *eth, uint8_t mac[ 6 ] );

/**
 * @brief Set the IPv4 address used by the Ethernet controller/stack.
 *
 * @details Forwards the given IPv4 address to the driver-specific set_ip
 * routine. Depending on the driver, this may only update an internal
 * software field (used by higher-level protocol handling) rather than any
 * hardware register, since IP addressing is typically not hardware-enforced
 * at the Ethernet controller level.
 *
 * @param eth Pointer to the SPI Ethernet instance.
 * @param ip 4-byte array containing the new IPv4 address to apply.
 *
 * @pre spi_ethernet_init() must have been called beforehand.
 *
 * @return int Driver-defined success code (typically non-zero) on success,
 *         -1 if @p eth, its driver, or the set_ip callback is
 *         NULL/undefined.
 *
 * @note This function does not perform any network-level validation
 *       (e.g. subnet consistency, address conflicts).
 * @warning Requires spi_ethernet_init() to have completed successfully.
 *
 * @see spi_ethernet_get_ip
 */
int  spi_ethernet_set_ip( spi_ethernet_t *eth, uint8_t ip[ 4 ] );

/**
 * @brief Retrieve the IPv4 address currently used by the Ethernet controller/stack.
 *
 * @details Forwards the request to the driver-specific get_ip routine,
 * which copies the currently configured IPv4 address into @p ip.
 *
 * @param eth Pointer to the SPI Ethernet instance.
 * @param ip 4-byte array to receive the current IPv4 address.
 *
 * @pre spi_ethernet_init() must have been called beforehand.
 * @pre @p ip must point to a writable buffer of at least 4 bytes.
 *
 * @return int Driver-defined success code (typically non-zero) on success,
 *         -1 if @p eth, its driver, or the get_ip callback is
 *         NULL/undefined.
 *
 * @warning Requires spi_ethernet_init() to have completed successfully.
 *
 * @see spi_ethernet_set_ip
 */
int  spi_ethernet_get_ip( spi_ethernet_t *eth, uint8_t ip[ 4 ] );

/**
 * @brief Check how many received frames are currently available.
 *
 * @details Forwards the request to the driver-specific available routine,
 * which typically queries the controller's packet counter register to
 * determine how many frames are waiting to be read from the receive buffer.
 *
 * @param eth Pointer to the SPI Ethernet instance.
 *
 * @pre spi_ethernet_init() must have been called beforehand.
 *
 * @return uint16_t Number of frames currently available for reading, or 0
 *         if @p eth, its driver, or the available callback is
 *         NULL/undefined (or if no frames are pending).
 *
 * @note A return value of 0 does not necessarily indicate an error; it may
 *       simply mean no frame has been received yet.
 * @warning Requires spi_ethernet_init() to have completed successfully.
 *
 * @see spi_ethernet_receive
 */
uint16_t spi_ethernet_available( spi_ethernet_t *eth );

/**
 * @brief Get the current physical link status.
 *
 * @details Forwards the request to the driver-specific get_link_status
 * routine, which typically reads the PHY status register to determine
 * whether a valid Ethernet link (cable connection with a functioning
 * remote link partner) is currently established.
 *
 * @param eth Pointer to the SPI Ethernet instance.
 *
 * @pre spi_ethernet_init() must have been called beforehand.
 *
 * @return uint8_t 1 if the link is up, 0 if the link is down or if @p eth,
 *         its driver, or the get_link_status callback is NULL/undefined.
 *
 * @note Depending on the PHY, this status may take a short time to update
 *       after a physical cable connection/disconnection.
 * @warning Requires spi_ethernet_init() to have completed successfully.
 */
uint8_t spi_ethernet_get_link_status( spi_ethernet_t *eth );

/**
 * @brief Send a TCP segment over Ethernet/IP.
 *
 * @details Builds a complete Ethernet + IPv4 + TCP frame (headers and
 * optional payload), computes the IP and TCP checksums, and transmits it
 * through the underlying SPI Ethernet driver.
 *
 * @param eth Pointer to the SPI Ethernet instance.
 * @param local_mac This device's MAC address (6 bytes).
 * @param local_ip This device's IPv4 address (4 bytes), used as source.
 * @param dst_mac Destination MAC address (6 bytes).
 * @param dst_ip Destination IPv4 address (4 bytes).
 * @param src_port Source TCP port.
 * @param dst_port Destination TCP port.
 * @param seq TCP sequence number.
 * @param ack_num TCP acknowledgment number.
 * @param flags TCP flags (SYN/ACK/FIN, see TCP_FLAG_* defines).
 * @param payload Optional pointer to application payload (NULL if none).
 * @param payload_len Length of the payload in bytes (0 if none).
 *
 * @pre spi_ethernet_init() must have been called beforehand.
 *
 * @return void
 *
 * @note This function does not manage TCP retransmission or connection
 *       state; it only builds and sends a single segment.
 * @warning The internal transmit buffer supports frames up to 400 bytes;
 *          larger payloads will overflow it.
 */
void spi_ethernet_send_tcp( spi_ethernet_t *eth, uint8_t *local_mac, uint8_t *local_ip,
                        uint8_t *dst_mac, uint8_t *dst_ip,
                        uint16_t src_port, uint16_t dst_port,
                        uint32_t seq, uint32_t ack_num, uint8_t flags,
                        uint8_t *payload, uint16_t payload_len );

/**
 * @brief Handle an incoming ARP request and reply if it targets us.
 *
 * @details Parses a received Ethernet frame carrying an ARP packet. If it
 * is an ARP request targeting @p local_ip, builds and sends an ARP reply
 * containing @p local_mac.
 *
 * @param eth Pointer to the SPI Ethernet instance.
 * @param local_mac This device's MAC address (6 bytes).
 * @param local_ip This device's IPv4 address (4 bytes).
 * @param pkt Pointer to the received raw Ethernet frame.
 * @param len Length of the received frame in bytes.
 *
 * @pre spi_ethernet_init() must have been called beforehand.
 * @pre @p pkt must point to a buffer of at least @p len bytes.
 *
 * @return void
 *
 * @note Frames that are not ARP requests, or that do not target
 *       @p local_ip, are silently ignored.
 */
void spi_ethernet_handle_arp( spi_ethernet_t *eth, uint8_t *local_mac, uint8_t *local_ip,
                          uint8_t *pkt, uint16_t len );

/**
 * @brief Handle an incoming ICMP Echo Request (ping) and reply.
 *
 * @details Parses a received Ethernet/IPv4 frame carrying an ICMP packet.
 * If it is an Echo Request (type 8), builds and sends an Echo Reply with
 * the same payload, recalculating the IP and ICMP checksums.
 *
 * @param eth Pointer to the SPI Ethernet instance.
 * @param local_mac This device's MAC address (6 bytes).
 * @param local_ip This device's IPv4 address (4 bytes), used as source.
 * @param pkt Pointer to the received raw Ethernet frame.
 * @param len Length of the received frame in bytes.
 *
 * @pre spi_ethernet_init() must have been called beforehand.
 * @pre @p pkt must point to a buffer of at least @p len bytes.
 *
 * @return void
 *
 * @note ICMP messages other than Echo Request are silently ignored.
 */
void spi_ethernet_handle_icmp( spi_ethernet_t *eth, uint8_t *local_mac, uint8_t *local_ip,
                           uint8_t *pkt, uint16_t len );

// ARP cache structure
typedef struct {
    bool valid;               // valid/invalid entry flag
    unsigned long time;       // timestamp
    uint8_t ip[ 4 ];          // IP address
    uint8_t mac[ 6 ];         // MAC address behind the IP address
} spi_ethernet_arp_cache_t;

typedef struct {
    uint8_t can_close_tcp;
    uint8_t is_broadcast;
} spi_ethernet_pkt_flags_t;

#ifdef __cplusplus
}
#endif
#endif // SPI_ETHERNET_H

/*! @} */ // spi_ethernet
/*! @} */ // middlewaregroup

// ------------------------------------------------------------------------ END
