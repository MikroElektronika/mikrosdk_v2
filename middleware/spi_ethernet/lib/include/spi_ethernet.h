/****************************************************************************
**
** Copyright (C) ${COPYRIGHT_YEAR} MikroElektronika d.o.o.
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
 * @file spi_ethernet.h
 * @brief SPI Ethernet Driver.
 */

#ifndef SPI_ETHERNET_H
#define SPI_ETHERNET_H

#ifdef __cplusplus
extern "C"{
#endif

#include "drv_spi_master.h"

#include <stdint.h>
// #include "spi_ethernet_enc28j60.h"

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
    uint8_t mac[6];             // MAC address
    uint32_t ip;                // IP address (optional if library handles DHCP externally)

    uint8_t fullDuplex;

    spi_ethernet_driver_t *drv;
};

/* Driver interface */
struct spi_ethernet_driver{
    void     (*init)(spi_ethernet_t *eth, spi_ethernet_driver_t *drv);
    int      (*reset)(void);
    // int      (*send)(const uint8_t *data, uint16_t len);
    uint16_t (*send_packet)(spi_ethernet_t *eth, uint8_t *data, uint16_t len);

    // int      (*receive)(uint8_t *data, uint16_t max_len);
    uint16_t (*read_packet)(spi_ethernet_t *eth, uint8_t *data, uint16_t len);
    uint8_t (*available)(spi_ethernet_t *eth);
    // int      (*flush)(void);
    uint8_t  (*get_link_status)(void);
    int      (*set_mac)(const uint8_t mac[6]);
    int      (*get_mac)(uint8_t mac[6]);
    int      (*set_ip)(const uint8_t ip[4]);
    int      (*get_ip)(uint8_t ip[4]);
    // int      (*set_gateway)(const uint8_t gw[4]);
    // int      (*get_gateway)(uint8_t gw[4]);
    // int      (*set_phy_mode)(uint8_t mode);
    // int      (*ping)(const uint8_t ip[4], uint16_t timeout_ms);
    // int      (*dhcp_start)(void);
    // int      (*dhcp_stop)(void);
    // int      (*ioctl)(uint8_t cmd, void *param);
};

/* Library context */
// typedef struct {
//     spi_ethernet_driver_t *drv;
//     spi_master_t spi_eth;
// } spi_ethernet_t;

typedef enum {
    SPI_ETH_IOCTL_PACKET_START = 0,
    SPI_ETH_IOCTL_PACKET_WRITE,
    SPI_ETH_IOCTL_PACKET_END,
    SPI_ETH_IOCTL_PACKET_AVAILABLE,
    SPI_ETH_IOCTL_PACKET_READ,
    SPI_ETH_IOCTL_MODULE_SPECIFIC = 0xF0  // reserved for module-specific commands
} spi_ethernet_ioctl_cmd_t;

/* Library API */
void spi_ethernet_init(spi_ethernet_t *eth, spi_ethernet_driver_t *drv);
int  spi_ethernet_reset(spi_ethernet_t *eth);
int  spi_ethernet_send(spi_ethernet_t *eth, const uint8_t *data, uint16_t len);
int  spi_ethernet_recv(spi_ethernet_t *eth, uint8_t *data, uint16_t max_len);
uint16_t spi_ethernet_available(spi_ethernet_t *eth);
int  spi_ethernet_flush(spi_ethernet_t *eth);
uint8_t spi_ethernet_get_link_status(spi_ethernet_t *eth);
int  spi_ethernet_set_mac(spi_ethernet_t *eth, const uint8_t mac[6]);
int  spi_ethernet_get_mac(spi_ethernet_t *eth, uint8_t mac[6]);
int  spi_ethernet_set_ip(spi_ethernet_t *eth, const uint8_t ip[4]);
int  spi_ethernet_get_ip(spi_ethernet_t *eth, uint8_t ip[4]);
int  spi_ethernet_set_gateway(spi_ethernet_t *eth, const uint8_t gw[4]);
int  spi_ethernet_get_gateway(spi_ethernet_t *eth, uint8_t gw[4]);
int  spi_ethernet_set_phy_mode(spi_ethernet_t *eth, uint8_t mode);
int  spi_ethernet_ping(spi_ethernet_t *eth, const uint8_t ip[4], uint16_t timeout_ms);
int  spi_ethernet_dhcp_start(spi_ethernet_t *eth);
int  spi_ethernet_dhcp_stop(spi_ethernet_t *eth);
int spi_ethernet_ioctl(spi_ethernet_t *eth, spi_ethernet_ioctl_cmd_t cmd, void *param);

// ARP cache structure
typedef struct {
    bool valid;                   // valid/invalid entry flag
    unsigned long time;           // timestamp
    uint8_t ip[4];          // IP address
    uint8_t mac[6];         // MAC address behind the IP address
} spi_ethernet_arp_cache_t;

typedef struct {
    uint8_t can_close_tcp;
    uint8_t is_broadcast;
} spi_ethernet_pkt_flags_t;

// TODO Esma From ethenc28j60private.h
// #pragma setintsize mE

// My functions (maybe set as static?)
uint8_t spi_ethernet_read_reg(uint8_t reg);
uint8_t * spi_ethernet_read_mem( uint8_t *buf, uint16_t len );
void spi_ethernet_write_reg(uint8_t reg, unsigned short value);
void spi_ethernet_write_mem(const uint8_t *buf, uint16_t len);
void spi_ethernet_set_bit_reg( uint8_t reg, uint8_t mask );
void spi_ethernet_clear_bit_reg( uint8_t reg, uint8_t mask );
void spi_ethernet_soft_reset();

// TODO Esma
// void spi_ethernet_init(uint8_t *mac, uint8_t *ip, uint8_t fullDuplex);
void spi_ethernet_init(spi_ethernet_t *eth, spi_ethernet_driver_t *drv);

/**
 * @brief Process the next Ethernet packet available in the ENC RAM buffer.
 *
 * Reads and handles the next available packet from the ENC controller's receive
 * buffer starting at the current ERDPT (read pointer) position. This function
 * consumes the packet data and advances internal buffer pointers accordingly.
 *
 * @pre spi_ethernet_init() must have been called to initialize the controller and buffers.
 * @pre ERDPT must be correctly set either by spi_ethernet_init() or by a previous
 *      call to spi_ethernet_read_packet().
 *
 * @return uint8_t Status code:
 *         @retval 0 Success — packet processed
 *         @retval non-zero Failure — error condition (e.g. no packet available, SPI error, buffer overrun)
 *
 * @note Calling this function modifies the ENC RAM read pointer (ERDPT) and internal
 *       state used for subsequent reads.
 * @note Ensure the SPI bus and any required interrupts are configured appropriately
 *       before invoking this routine.
 *
 * @see spi_ethernet_init()
 */
uint16_t spi_ethernet_read_packet();

/**
 * @brief Handle a single, unfragmented TCP/IP request found in the ENC buffer.
 *
 * This routine processes a TCP segment contained entirely within one ENC receive
 * buffer entry. It parses the IP/TCP headers, verifies basic header assumptions
 * and prepares any reply payload into the ENC transmit buffer at the provided
 * address. It does not perform IP fragmentation reassembly or multi-packet
 * TCP stream handling.
 *
 * @param start Address (offset) of the incoming packet in the ENC receive buffer.
 * @param ipHeaderLen Length of the IP header in bytes (used to locate the TCP header).
 * @param payloadAddr Address (offset) in the ENC transmit buffer where the response
 *                    payload should be written.
 *
 * @pre The packet at @p start is a complete, unfragmented IPv4 packet containing a
 *      TCP segment and fits within the ENC receive buffer.
 * @pre Caller must ensure exclusive access to ENC buffers and that the ENC device
 *      is in the expected state.
 *
 * @post TCP processing is performed and any response payload is placed at @p payloadAddr
 *       in the ENC transmit buffer; appropriate ENC transmit bookkeeping is updated.
 *
 * @note This function is intended to be invoked only from spi_ethernet_read_packet().
 *
 * @warning Does not handle fragmented IP packets, TCP stream reassembly, or
 *          advanced TCP features (window scaling, selective ACKs). Caller is
 *          responsible for higher-level protocol state and retransmission logic.
 *
 * @return void
 *
 * @see spi_ethernet_read_packet
 */
void spi_ethernet_process_tcp(uint16_t start, uint16_t ipHeaderLen, uint16_t payloadAddr);

/**
 * @brief Reply to an incoming UDP/IP request.
 *
 * @details Constructs and sends a UDP/IP reply using data from the ENC receive buffer
 * and places the response payload into the ENC transmit buffer. Intended to be invoked
 * from spi_ethernet_read_packet() to form a proper UDP response to an incoming datagram.
 *
 * @param start Address (offset) of the incoming packet within the ENC receive buffer.
 * @param ipHeaderLen Length in bytes of the IP header in the received packet.
 * @param payloadAddr Address (offset) in the ENC transmit buffer where the reply payload should be written.
 *
 * @note The caller must ensure the receive buffer at @p start contains a valid packet
 *       and that @p payloadAddr refers to a writable region in the transmit buffer.
 * @warning This function assumes a well-formed UDP/IP datagram and does limited validation.
 * @return void
 */
void spi_ethernet_process_udp(uint16_t start, uint8_t ipHeaderLen, uint16_t payloadAddr);

/**
 * @brief Build and send a UDP packet to a specified MAC/IP destination and ports.
 *
 * @details Prepares UDP and IP headers and transmits a packet via the ENC transmit buffer.
 * Destination hardware (MAC) and network (IP) addresses are taken from the provided pointers.
 * Source and destination UDP ports are set according to the parameters. The function returns
 * a value that indicates the result as defined by the lower-level ENC driver/implementation
 * (e.g., transmit buffer address, number of bytes sent, or status code).
 *
 * @param destMAC Pointer to a 6-byte destination MAC address.
 * @param destIP Pointer to a 4-byte destination IPv4 address.
 * @param sourcePort UDP source port (host byte order).
 * @param destPort UDP destination port (host byte order).
 * @param pktLen Length in bytes of the UDP payload to send.
 *
 * @return uint16_t Implementation-dependent result (e.g., transmit buffer pointer, number of bytes sent, or error/status code).
 * @note Ensure @p destMAC and @p destIP point to valid memory and that @p pktLen does not exceed the transmit buffer capacity.
 * @warning Caller is responsible for any required checksum calculations or for relying on the driver to compute them.
 */
uint16_t spi_ethernet_send_udp2( uint8_t *destMAC, uint8_t *destIP,
                                     uint16_t sourcePort, uint16_t destPort,
                                     uint16_t pktLen );

/**
 * @brief Service the DHCP state machine and manage lease negotiation.
 *
 * @details Executes the DHCP handler responsible for maintaining the device’s network
 * configuration. This includes processing offer/acknowledge states, handling lease
 * expiration, updating assigned IP/netmask/gateway values, and preparing outgoing
 * DHCP messages when required. The function does not perform any packet reception
 * itself—rather, it operates only on DHCP data previously extracted from incoming
 * Ethernet frames.
 *
 * This routine must be called from within @ref spi_ethernet_read_packet() so that DHCP
 * processing remains synchronized with packet reception and the internal ENC buffer
 * handling. Calling it from any other context may break timing assumptions or cause
 * incomplete DHCP state transitions.
 *
 * @note Does not send packets directly; it only advances DHCP logic and schedules
 * outgoing messages when appropriate.
 * @warning Must be invoked regularly to avoid lease timeout or stalled DHCP negotiation.
 */
void spi_ethernet_dhcp_service( void );

/**
 * @brief Receive, parse, and validate incoming DHCP packets.
 *
 * @details Extracts DHCP payloads from processed Ethernet frames and evaluates whether
 * they match the current DHCP transaction (e.g., correct transaction ID, expected
 * message type, and proper addressing). If valid, the function updates DHCP context
 * fields such as offered IP address, lease time, renewal/rebinding intervals, and
 * server identifier.
 *
 * The function returns an implementation-specific value indicating the number of bytes
 * handled or a driver-dependent status code. This return value is typically used by
 * higher-layer DHCP logic to determine whether the incoming message should cause a
 * state transition (e.g., OFFER → REQUEST, REQUEST → BOUND).
 *
 * @return uint16_t Number of DHCP payload bytes processed, or a status/result code
 * depending on the underlying ENC driver behavior.
 *
 * @note Caller must ensure packet boundaries have already been validated by the
 * Ethernet/ENC layer before invoking this routine.
 */
uint16_t spi_ethernet_dhcp_receive(void); // TODO OPIS

/**
 * @brief Construct and transmit a DHCP protocol message.
 *
 * @details Builds a DHCP message of the specified type (DISCOVER, REQUEST, DECLINE,
 * RELEASE, or RENEW) and pushes it to the ENC transmit buffer for dispatch. The
 * routine prepares all standard DHCP fields, inserts the correct transaction ID,
 * embeds client hardware address information, applies renewal logic when
 * @p renew_flag is set, and appends mandatory DHCP options.
 *
 * Returned value indicates the underlying driver's result (e.g., number of bytes
 * written, transmit buffer address, or a status/error flag). The actual format of
 * this return value depends on the ENC driver implementation.
 *
 * @param message_type The DHCP message type to transmit, according to DHCP spec
 *                     (e.g., 1 = DISCOVER, 3 = REQUEST, 5 = ACK, 7 = RELEASE).
 * @param renew_flag Non-zero to send a renewal-style message using existing lease
 *                     parameters rather than initiating a fresh negotiation.
 *
 * @return uint16_t Implementation-dependent result, usually representing number of
 * bytes queued for transmission or a status code.
 *
 * @note Caller must ensure network layer (IP/UDP) configuration is valid before
 * transmission. Incorrect or expired lease values may cause servers to ignore the
 * message.
 * @warning This function does not verify lease validity; it assumes the DHCP state
 * machine enforces correctness.
 */
uint16_t spi_ethernet_dhcp_message(uint8_t messageType, uint8_t renewFlag); // TODO OPIS

/**
 * @brief Service the DNS resolver logic.
 *
 * @details Executes the internal DNS handler responsible for processing
 * outstanding name-resolution operations. This includes examining DNS
 * response packets previously extracted by the Ethernet receive routine,
 * validating query IDs, checking response types (A records, error codes,
 * etc.), and updating the resolver context with resolved IPv4 addresses.
 *
 * The function does not access the ENC hardware directly. It operates only
 * on DNS payloads already obtained through spi_ethernet_read_packet(), which
 * is why it must be invoked strictly from within that routine. This keeps
 * DNS state progression synchronized with packet reception, prevents missed
 * responses, and ensures proper handling of packet boundaries.
 *
 * @note Does not initiate DNS queries; it only processes responses to queries
 * issued elsewhere.
 * @warning Calling this function outside spi_ethernet_read_packet() may lead
 * to dropped DNS replies or incomplete resolver state updates.
 */
void spi_ethernet_dns_service( void );

/**
 * @brief Service the ARP handler and maintain address-resolution state.
 *
 * @details Processes ARP requests and replies extracted from incoming Ethernet
 * frames. This includes validating sender/target IP and MAC fields, updating the
 * internal ARP cache, refreshing entry lifetimes, and preparing outgoing ARP
 * responses when required. The function does not read directly from the ENC
 * hardware; it only works on ARP payloads already provided by the Ethernet
 * receive routine.
 *
 * This function must be called from within spi_ethernet_read_packet() so that
 * ARP processing stays aligned with packet reception and the internal buffer
 * flow. Calling it from anywhere else can result in outdated ARP cache entries
 * or missed ARP replies.
 *
 * @note Does not initiate ARP scans on its own; it only reacts to packets the
 * driver has already received.
 * @warning Incorrect call ordering may leave the ARP cache stale, which can
 * break IP communication until entries expire naturally.
 */
void spi_ethernet_arp_service( void );

/**
 * @brief Trigger a hardware checksum calculation on ENC memory.
 *
 * @details Instructs the ENC controller to perform a DMA-based checksum over a
 * block of memory starting at the ENC RAM address specified by @p start and
 * spanning @p length bytes. The calculation is executed entirely by the ENC
 * hardware, and the result is written into the EDMACS[H:L] checksum registers
 * upon completion.
 *
 * The function itself does not return the checksum value. Callers must read the
 * ENC EDMACS registers directly after the operation to obtain the computed
 * result. This hardware-assisted checksum is typically used to accelerate IP,
 * UDP, or TCP checksum generation when assembling outgoing packets.
 *
 * @param start ENC RAM start address of the region to be checksummed.
 * @param length Number of bytes to include in the checksum operation.
 *
 * @note Requires spi_ethernet_init() to be successfully executed beforehand.
 * @warning Caller is responsible for ensuring that the provided address range
 *          is valid within ENC memory; out-of-range values may result in
 *          undefined hardware behavior.
 */
void spi_ethernet_checksum(uint16_t start, uint16_t l); // TODO OPIS

/**
 * @brief Perform an ENC hardware-assisted RAM copy operation.
 *
 * @details Commands the ENC controller to copy a block of memory from ENC RAM
 * beginning at @p start and ending at @p stop (exclusive) into another ENC RAM
 * location specified by @p dest. The transfer is handled via the ENC’s internal
 * DMA engine, allowing fast movement of packet data without CPU-driven reads and
 * writes.
 *
 * When @p wrap is non-zero, the function enables buffer-wrapping behavior used
 * when copying data from the receive buffer, which is implemented as a circular
 * FIFO. In wrap mode, the ENC performs the necessary boundary checks to prevent
 * buffer overrun or hardware lockup while crossing the RX buffer end boundary.
 *
 * This routine does not validate the address ranges; the caller must ensure all
 * addresses fall within valid ENC memory regions and that no overlap or ordering
 * errors occur that could corrupt in-use transmit or receive buffers.
 *
 * @param start ENC RAM address of the first source byte (inclusive).
 * @param stop ENC RAM address of the last source byte (exclusive).
 * @param dest ENC RAM address of the first destination byte.
 * @param wrap Copy mode:
 *               - 0 → no wrap (copying from TX buffer)
 *               - 1 → wrap enabled (copying from RX circular buffer)
 *
 * @note Requires a successful call to spi_ethernet_init() before use.
 * @warning Invalid address ranges or incorrect wrap mode may cause undefined
 *          ENC behavior or corrupted packet data.
 */
void spi_ethernet_ram_copy(uint16_t start, uint16_t stop, uint16_t dest, uint8_t w); // TODO OPIS

/**
 * @brief Swap source and destination MAC addresses in the ENC transmit buffer.
 *
 * @details Modifies the Ethernet frame currently assembled in the ENC transmit
 * buffer by exchanging the six-byte destination MAC field with the six-byte
 * source MAC field. This is typically used when generating automatic replies
 * (e.g., ARP responses or certain service frames) where the incoming packet’s
 * source MAC becomes the destination for the outgoing frame.
 *
 * The function operates directly on the transmit buffer region without inspecting
 * payload contents. It assumes that a valid Ethernet header is already present
 * at the expected offset and that the transmit buffer has been prepared using
 * the appropriate ENC pointer registers.
 *
 * @note Does not validate header contents; incorrect buffer pointer setup may
 *       result in unintended memory modification.
 * @warning Requires spi_ethernet_init() to have completed successfully.
 */
void spi_ethernet_mac_swap( void );

/**
 * @brief Swap source and destination IPv4 addresses in the ENC transmit buffer.
 *
 * @details Updates the IP header of the packet currently staged in the ENC
 * transmit buffer by exchanging the 4-byte source IP field with the 4-byte
 * destination IP field. This is commonly used when generating immediate
 * responses to incoming packets (e.g., ICMP echo replies) where the incoming
 * packet’s source IP must become the destination of the outgoing one.
 *
 * The function assumes the transmit buffer already contains a valid IPv4 header
 * at the expected location and that buffer write pointers have been positioned
 * correctly. No validation of header fields is performed; the operation is a
 * direct in-place swap of the two IP address fields.
 *
 * @note Only the IP header fields are modified; checksums must be updated by
 *       the caller or by subsequent header-building functions.
 * @warning Requires spi_ethernet_init() to have completed successfully.
 */
void spi_ethernet_ip_swap( void );

/**
 * @brief Transmit the packet currently assembled in the ENC transmit buffer.
 *
 * @details Finalizes and sends an Ethernet frame of @p length bytes using the
 * ENC hardware transmit logic. The function assumes that the transmit buffer
 * has already been populated with a complete and valid Ethernet frame, including
 * MAC, IP, and protocol headers (if applicable). Upon invocation, the ENC’s
 * transmit pointer registers are updated and the transmission process is
 * initiated on the physical interface.
 *
 * The return value indicates basic success or failure: a non-zero value means
 * the transmit command was accepted by the ENC hardware, while zero indicates
 * an error such as an invalid buffer pointer, incorrect state, or failure to
 * arm the transmitter.
 *
 * @param length Total number of bytes to transmit from the ENC transmit buffer.
 *
 * @return uint16_t 1 on success, 0 on error.
 *
 * @note Caller is responsible for ensuring the frame length meets Ethernet
 *       minimum requirements (typically 60 bytes without CRC).
 * @warning Requires spi_ethernet_init() to have completed successfully before
 *          any transmission attempts.
 */
uint16_t spi_ethernet_transmit_packet(uint16_t l); // TODO OPIS

/**
 * @brief Compare a block of ENC RAM with a block of MCU RAM.
 *
 * @details Reads @p length bytes starting at ENC RAM address @p addr and compares
 * them byte-for-byte with the MCU memory region pointed to by @p s. The function
 * performs a straightforward sequential comparison without interpreting the data
 * or performing any alignment adjustments. It is typically used when validating
 * protocol headers, checking received data against expected patterns, or
 * confirming buffer contents before transmission.
 *
 * A return value of 0 indicates an exact match across all bytes. Any non-zero
 * return value indicates a mismatch, with the exact value depending on the first
 * differing byte (implementation-defined). The function does not distinguish
 * between different mismatch causes — any difference results in a >0 value.
 *
 * @param addr ENC RAM start address of the region to compare.
 * @param s Pointer to the MCU RAM buffer to compare against.
 * @param length Number of bytes to compare.
 *
 * @return uint8_t 0 if the memory regions match, non-zero otherwise.
 *
 * @note Caller must ensure that @p addr and @p length form a valid region within
 *       ENC RAM; invalid addresses may cause incorrect reads.
 * @warning Requires spi_ethernet_init() to have been executed beforehand.
 */
uint16_t spi_ethernet_memcmp(uint16_t addr, uint8_t *s, uint8_t l); // TODO OPIS

/**
 * @brief Copy a block of MCU RAM into ENC RAM.
 *
 * @details Writes @p length bytes from the MCU memory buffer pointed to by
 * @p src into the ENC RAM starting at address @p addr. The operation is a
 * direct byte-wise transfer and does not perform alignment adjustments,
 * protocol-specific formatting, or boundary checking. This routine is
 * typically used when assembling Ethernet, IP, or transport-layer headers
 * directly inside the ENC transmit buffer, or when injecting payload data
 * into the ENC RAM before transmission.
 *
 * The function assumes that the ENC write pointer and addressing rules are
 * respected by the caller. It does not validate whether the destination
 * range overlaps internal control structures, reserved memory, or areas
 * concurrently used by RX or TX buffers.
 *
 * @param addr ENC RAM destination address.
 * @param src Pointer to the MCU buffer containing the data to copy.
 * @param length Number of bytes to copy into ENC RAM.
 *
 * @note This function does not return a status value; callers must ensure
 *       all parameters are valid and that @p length fits entirely within
 *       the intended ENC RAM region.
 * @warning Requires spi_ethernet_init() to have been executed before use.
 */
void spi_ethernet_memcpy(uint16_t addr, uint8_t *s, uint16_t l); // TODO OPIS

/**
 * @brief Write two bytes into ENC RAM.
 *
 * @details Copies the values @p v1 and @p v2 into ENC RAM starting at
 * address @p addr. The first byte is written to @p addr, and the second
 * is written to @p addr + 1. This helper is primarily used when assembling
 * protocol headers or small multi-byte fields directly inside the ENC
 * transmit buffer. Typical use cases include writing protocol type fields,
 * identifier values, port numbers, checksums, and similar two-byte
 * structures.
 *
 * The function does not perform bounds checking or verify whether the
 * destination lies in the transmit region, receive region, or a reserved
 * area. The caller is responsible for ensuring that the target memory
 * region is valid and that the write does not overlap active buffers.
 *
 * @param addr ENC RAM destination address.
 * @param v1    Value to store at @p addr.
 * @param v2    Value to store at @p addr + 1.
 *
 * @note This function does not return a status code. It assumes that the
 *       caller has verified that the write is safe.
 *
 * @warning Requires spi_ethernet_init() to have been executed before use.
 */
void spi_ethernet_write_memory(uint16_t addr, uint8_t v1, uint8_t v2); // TODO OPIS

/**
 * @brief Write a 16-bit value into ENC RAM at the current write pointer.
 *
 * @details Stores the 16-bit value @p v into ENC RAM locations pointed to by
 * the current write pointer (WRPTL). The high byte of @p v is written first
 * to the lower address, followed by the low byte at the next address. This
 * function is useful for writing multi-byte fields, such as protocol headers
 * or length/type identifiers, directly into the ENC transmit or control buffers.
 *
 * The function performs direct writes and does not perform bounds checking.
 * The caller must ensure that writing at the current write pointer does not
 * overwrite active transmit or receive buffers or reserved ENC memory regions.
 *
 * @param v 16-bit value to write into ENC RAM (high byte first, low byte second).
 *
 * @note The function does not return a status code; any errors must be managed externally.
 * @warning spi_ethernet_init() must have been called before using this function.
 */
void spi_ethernet_write_memory2(uint16_t v); // TODO OPIS

/**
 * @brief Write a single byte into ENC RAM.
 *
 * @details Stores the byte @p v1 into ENC RAM at the specified address @p addr.
 * This function is commonly used for writing individual control bytes, flags,
 * or small protocol fields directly into the ENC memory, such as configuration
 * registers or temporary header values.
 *
 * The function performs a direct memory write and does not perform bounds
 * checking. The caller is responsible for ensuring that the target address
 * is valid and does not overwrite active transmit/receive buffers or reserved
 * ENC memory regions.
 *
 * @param addr ENC RAM destination address for the byte.
 * @param v1   Value to write at @p addr.
 *
 * @note The function does not return a status code; any errors must be managed externally.
 * @warning spi_ethernet_init() must have been called before using this function.
 */
// void spi_ethernet_write_mem(uint16_t addr, uint8_t v1); // TODO OPIS
void spi_ethernet_write_mem(const uint8_t *buf, uint16_t len);

/**
 * @brief Read a single byte from ENC RAM.
 *
 * @details Retrieves the value stored at the ENC RAM address specified by
 * @p addr. This function is typically used for reading control registers,
 * status bytes, or small fields from transmit/receive buffers within the ENC
 * memory.
 *
 * The function performs a direct memory read and does not perform bounds
 * checking. The caller is responsible for ensuring that the address is valid
 * and does not point into reserved or undefined ENC memory regions.
 *
 * @param addr ENC RAM address to read from.
 *
 * @return uint8_t Value stored at @p addr in ENC RAM.
 *
 * @note The function does not indicate errors; the caller must ensure the
 *       memory read is valid.
 * @warning spi_ethernet_init() must have been called before using this function.
 */
// uint8_t spi_ethernet_read_mem(uint16_t addr);
uint8_t * spi_ethernet_read_mem( uint8_t *buf, uint16_t len );

/**
 * @brief Read a byte from an ENC register.
 *
 * @details Retrieves the value stored in the ENC register specified by @p addr
 * within the currently selected bank. This function is commonly used to read
 * status registers, configuration registers, or other control registers in the
 * ENC hardware. Bank selection must already be configured prior to calling
 * this function.
 *
 * The function performs a direct register read and does not check whether
 * the register is valid for the current bank; the caller must ensure correct
 * bank selection.
 *
 * @param addr ENC register address within the current bank.
 *
 * @return uint8_t Value of the ENC register at @p addr.
 *
 * @note The function does not return an error code; ensure bank selection is correct.
 * @warning spi_ethernet_init() must have been called before using this function.
 */
uint8_t spi_ethernet_read_reg(uint8_t addr);

/**
 * @brief Write a 16-bit value to an ENC register.
 *
 * @details Stores the value @p v into the ENC register specified by @p addr
 * within the currently selected bank. This function is typically used for
 * configuring ENC control registers, setting flags, or updating multi-byte
 * fields directly in the hardware. Bank selection must already be configured
 * before calling this function.
 *
 * The function performs a direct register write and does not verify the
 * validity of the address or bank. The caller is responsible for ensuring that
 * the target register exists in the current bank and that the write does not
 * interfere with ongoing operations.
 *
 * @param addr ENC register address within the current bank.
 * @param v    16-bit value to write into the register.
 *
 * @note The function does not return a status code; any errors must be managed externally.
 * @warning spi_ethernet_init() must have been called prior to using this function.
 */
void spi_ethernet_write_reg(uint8_t addr, uint16_t v);

/**
 * @brief Set specific bits in an ENC register.
 *
 * @details Performs a bitwise OR of the current value in the ENC register
 * specified by @p addr with the provided @p mask. This function is commonly
 * used to enable features, set flags, or modify configuration bits without
 * altering other bits in the register. Bank selection must already be configured
 * before calling this function.
 *
 * The function performs a direct register read-modify-write operation and does
 * not verify the validity of the address or mask. The caller is responsible
 * for ensuring that only appropriate bits are set and that the operation does
 * not interfere with ongoing ENC operations.
 *
 * @param addr ENC register address within the current bank.
 * @param mask Bitmask indicating which bits to set (1 → set, 0 → leave unchanged).
 *
 * @note This function does not return a status code; ensure that the register
 *       and bank selection are valid.
 * @warning spi_ethernet_init() must have been called prior to using this function.
 */
void spi_ethernet_set_bit_reg(uint8_t addr, uint8_t mask);

/**
 * @brief Clear specific bits in an ENC register.
 *
 * @details Performs a bitwise AND of the current value in the ENC register
 * specified by @p addr with the complement of the provided @p mask. This
 * effectively clears the bits corresponding to 1s in the mask while leaving
 * other bits unchanged. Bank selection must already be configured before
 * calling this function.
 *
 * This function is useful for disabling features, clearing flags, or resetting
 * configuration bits without affecting other bits in the register. The caller
 * is responsible for ensuring that only valid bits are cleared and that the
 * operation does not interfere with ongoing ENC operations.
 *
 * @param addr ENC register address within the current bank.
 * @param mask Bitmask indicating which bits to clear (1 → clear, 0 → leave unchanged).
 *
 * @note The function does not return a status code; ensure that the register
 *       and bank selection are valid.
 * @warning spi_ethernet_init() must have been called prior to using this function.
 */
void spi_ethernet_clear_bit_reg(uint8_t addr, uint8_t mask);

/**
 * @brief Set the ENC receive buffer read pointer.
 *
 * @details Adjusts the provided absolute address @p addr to account for
 * circular wrapping of the ENC receive buffer and writes the resulting
 * value into the receive buffer read pointer (ERDPT). This function is
 * used to control from which location the ENC will next read received
 * packet data.
 *
 * The function automatically handles buffer wrapping to prevent invalid
 * memory accesses within the ENC receive buffer. The caller must ensure
 * that @p addr points to a valid location within the buffer and that the
 * receive pointer adjustment does not interfere with ongoing packet reception.
 *
 * @param addr Absolute ENC receive buffer address to set as the read pointer.
 *
 * @note Does not return a status code; the caller must ensure the address is valid.
 * @warning spi_ethernet_init() must have been called and the correct bank selected
 *          prior to calling this function.
 */
void spi_ethernet_set_rx_read_address(unsigned addr); // TODO OPIS

/**
 * @brief Write a 16-bit value to an ENC register.
 *
 * @details Stores the 16-bit value @p v into the ENC register specified by
 * @p addr within the currently selected bank. The high byte is written first
 * to the lower address, followed by the low byte. This function is typically
 * used for writing multi-byte control registers or pointer values in the ENC
 * hardware, such as transmit/receive buffer addresses or length registers.
 *
 * The function performs a direct register write and does not validate the
 * address or bank selection. The caller must ensure that the target register
 * exists in the current bank and that the write does not interfere with ongoing
 * ENC operations.
 *
 * @param addr ENC register address within the current bank.
 * @param v    16-bit value to write into the register (high byte first).
 *
 * @note The function does not return a status code; ensure the register and
 *       bank selection are valid.
 * @warning spi_ethernet_init() must have been called prior to using this function.
 */
void spi_ethernet_write_addr(uint8_t addr, uint16_t v); // TODO OPIS

/**
 * @brief Write a 16-bit value to an ENC PHY register.
 *
 * @details Writes the high byte @p h and low byte @p l sequentially into the
 * PHY register specified by @p reg. The high byte is written first, followed
 * by the low byte. This function is commonly used to configure PHY control
 * registers, set link parameters, or adjust PHY-specific settings such as
 * duplex mode, speed, or reset operations.
 *
 * The function performs direct writes to the ENC PHY and does not perform
 * address validation. The caller must ensure that the register exists and
 * that writing these values does not disrupt ongoing PHY operations.
 *
 * @param reg ENC PHY register address.
 * @param h High byte to write to the PHY register.
 * @param l Low byte to write to the PHY register.
 *
 * @note The function does not return a status code; the caller must ensure
 *       the register is valid.
 * @warning spi_ethernet_init() must have been called prior to using this function.
 */
void spi_ethernet_write_phy(uint8_t reg, uint16_t h, uint16_t l);

/**
 * @brief Read a 16-bit value from an ENC PHY register.
 *
 * @details Retrieves the high and low bytes from the PHY register specified
 * by @p reg. The high byte is stored at the memory location pointed to by
 * @p h, and the low byte is stored at the location pointed to by @p l.
 * This function is typically used to read PHY status, link parameters, or
 * configuration registers such as speed, duplex mode, or link status.
 *
 * The function performs direct reads from the ENC PHY and does not validate
 * the pointers; the caller must ensure that @p h and @p l point to valid
 * memory locations. Bank selection and PHY initialization must be handled
 * prior to calling this function.
 *
 * @param reg ENC PHY register address to read from.
 * @param h Pointer to store the high byte of the register value.
 * @param l Pointer to store the low byte of the register value.
 *
 * @note Does not return a status code; the caller must ensure pointers are valid.
 * @warning spi_ethernet_init() must have been called before using this function.
 */
void spi_ethernet_read_phy(uint8_t reg, uint8_t *h, uint8_t *l);

/**
 * @brief Introduce a short delay for ENC operations.
 *
 * @details Provides an approximate 200 ms delay used primarily when accessing
 * ENC PHY-level registers during initialization or configuration. Certain
 * PHY operations, such as resets or register updates, require small delays
 * to ensure the hardware has time to complete internal state changes.
 *
 * This function blocks execution for the duration of the delay and does not
 * perform any hardware checks. It is intended for use only during setup
 * or in situations where precise timing is not critical.
 *
 * @note Duration is fixed at roughly 200 ms; do not rely on this function
 *       for precise timing in production applications.
 * @warning No return status; ensure that calling this function does not
 *          interfere with time-critical tasks.
 */
void spi_ethernet_delay(void);

/**
 * @brief Continue ENC initialization sequence (phases 2–10).
 *
 * @details This function is the second part of the SPI Ethernet initialization
 * routine, split to accommodate flash paging limitations on PIC16 devices.
 * It performs the subsequent initialization steps (phases 2 through 10) as
 * defined in the ENC datasheet, including PHY configuration, buffer setup,
 * and control register initialization.
 *
 * The @p fullDuplex parameter determines whether the ENC PHY is configured
 * for full-duplex or half-duplex operation. This affects link negotiation,
 * MAC control settings, and duplex-specific timing behavior.
 *
 * The function assumes that the first part of the initialization has already
 * been executed (phase 1) and that SPI communication with the ENC is ready.
 * It does not return a status code; the caller is responsible for verifying
 * proper initialization if needed.
 *
 * @param fullDuplex 0 → half-duplex, non-zero → full-duplex.
 *
 * @note Intended for internal use as part of spi_ethernet_init(); splitting
 *       the initialization routine avoids issues with PIC16 flash paging.
 * @warning Ensure SPI and ENC hardware are ready before calling this function.
 */
void spi_ethernet_init2(uint8_t fullDuplex);

#ifdef __cplusplus
}
#endif
#endif // SPI_ETHERNET_H

/*! @} */ // spi_ethernet
/*! @} */ // middlewaregroup

// ------------------------------------------------------------------------ END
