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
 * @file spi_ethernet.c
 * @brief SPI Ethernet Driver.
 */

#include "spi_ethernet.h"

/* --- Library Initialization --- */
void spi_ethernet_init(spi_ethernet_t *eth, spi_ethernet_driver_t *drv) {
    if (!eth || !drv) return;
    eth->drv = drv;
    if (eth->drv->init) eth->drv->init(eth, drv);
}

/* --- Basic Control --- */
int spi_ethernet_reset(spi_ethernet_t *eth) {
    if (!eth || !eth->drv || !eth->drv->reset) return -1;
    return eth->drv->reset();
}

uint8_t spi_ethernet_get_link_status(spi_ethernet_t *eth) {
    if (!eth || !eth->drv || !eth->drv->get_link_status) return 0;
    return eth->drv->get_link_status();
}

// /* --- Addressing --- */
int spi_ethernet_set_mac(spi_ethernet_t *eth, const uint8_t mac[6]) {
    if (!eth || !eth->drv || !eth->drv->set_mac) return -1;
    return eth->drv->set_mac(mac);
}

int spi_ethernet_get_mac(spi_ethernet_t *eth, uint8_t mac[6]) {
    if (!eth || !eth->drv || !eth->drv->get_mac) return -1;
    return eth->drv->get_mac(mac);
}

int spi_ethernet_set_ip(spi_ethernet_t *eth, const uint8_t ip[4]) {
    if (!eth || !eth->drv || !eth->drv->set_ip) return -1;
    return eth->drv->set_ip(ip);
}

int spi_ethernet_get_ip(spi_ethernet_t *eth, uint8_t ip[4]) {
    if (!eth || !eth->drv || !eth->drv->get_ip) return -1;
    return eth->drv->get_ip(ip);
}

// int spi_ethernet_set_gateway(spi_ethernet_t *eth, const uint8_t gw[4]) {
//     if (!eth || !eth->drv || !eth->drv->set_gateway) return -1;
//     return eth->drv->set_gateway(gw);
// }

// int spi_ethernet_get_gateway(spi_ethernet_t *eth, uint8_t gw[4]) {
//     if (!eth || !eth->drv || !eth->drv->get_gateway) return -1;
//     return eth->drv->get_gateway(gw);
// }

/* --- Data Transfer --- */
int spi_ethernet_send(spi_ethernet_t *eth, const uint8_t *data, uint16_t len) {
    if (!eth || !eth->drv || !eth->drv->send_packet) return -1;
    return eth->drv->send_packet(eth, data, len);
}

int spi_ethernet_receive(spi_ethernet_t *eth, uint8_t *data, uint16_t len) {
    if (!eth || !eth->drv || !eth->drv->read_packet) return -1;
    // return eth->drv->receive(data, max_len);
    return eth->drv->read_packet(eth, data, len);
}

uint16_t spi_ethernet_available(spi_ethernet_t *eth) {
    if (!eth || !eth->drv || !eth->drv->available) return 0;
    return eth->drv->available(eth);
}

// int spi_ethernet_flush(spi_ethernet_t *eth) {
//     if (!eth || !eth->drv || !eth->drv->flush) return -1;
//     return eth->drv->flush();
// }

// /* --- Optional Control --- */
// int spi_ethernet_set_phy_mode(spi_ethernet_t *eth, uint8_t mode) {
//     if (!eth || !eth->drv || !eth->drv->set_phy_mode) return -1;
//     return eth->drv->set_phy_mode(mode);
// }

// int spi_ethernet_ping(spi_ethernet_t *eth, const uint8_t ip[4], uint16_t timeout_ms) {
//     if (!eth || !eth->drv || !eth->drv->ping) return -1;
//     return eth->drv->ping(ip, timeout_ms);
// }

// int spi_ethernet_dhcp_start(spi_ethernet_t *eth) {
//     if (!eth || !eth->drv || !eth->drv->dhcp_start) return -1;
//     return eth->drv->dhcp_start();
// }

// int spi_ethernet_dhcp_stop(spi_ethernet_t *eth) {
//     if (!eth || !eth->drv || !eth->drv->dhcp_stop) return -1;
//     return eth->drv->dhcp_stop();
// }

// /* --- Module-Specific Commands --- */
// int spi_ethernet_ioctl(spi_ethernet_t *eth, spi_ethernet_ioctl_cmd_t cmd, void *param) {
//     if (!eth || !eth->drv || !eth->drv->ioctl) return -1;
//     return eth->drv->ioctl(cmd, param);
// }

// /* --- Packet Handling --- */
// int spi_ethernet_packet_start(spi_ethernet_t *eth, uint16_t len) {
//     if (!eth || !eth->drv || !eth->drv->ioctl) return -1;
//     /* Command reserved for starting TX buffer */
//     return eth->drv->ioctl(SPI_ETH_IOCTL_PACKET_START, &len);
// }

// int spi_ethernet_packet_write(spi_ethernet_t *eth, const uint8_t *data, uint16_t len) {
//     if (!eth || !eth->drv || !eth->drv->ioctl) return -1;
//     /* Write data to packet buffer */
//     return eth->drv->ioctl(SPI_ETH_IOCTL_PACKET_WRITE, (void*)data);
// }

// int spi_ethernet_packet_end(spi_ethernet_t *eth) {
//     if (!eth || !eth->drv || !eth->drv->ioctl) return -1;
//     /* Finalize and send packet */
//     return eth->drv->ioctl(SPI_ETH_IOCTL_PACKET_END, NULL);
// }

// uint16_t spi_ethernet_packet_available(spi_ethernet_t *eth) {
//     if (!eth || !eth->drv || !eth->drv->ioctl) return 0;
//     uint16_t avail = 0;
//     eth->drv->ioctl(SPI_ETH_IOCTL_PACKET_AVAILABLE, &avail);
//     return avail;
// }

// int spi_ethernet_packet_read(spi_ethernet_t *eth, uint8_t *data, uint16_t max_len) {
//     if (!eth || !eth->drv || !eth->drv->ioctl) return -1;
//     return eth->drv->ioctl(SPI_ETH_IOCTL_PACKET_READ, data);
// }

// ------------------------------------------------------------------------ END
