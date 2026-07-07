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

/* --- Data Transfer --- */
int spi_ethernet_send(spi_ethernet_t *eth, const uint8_t *data, uint16_t len) {
    if (!eth || !eth->drv || !eth->drv->send_packet) return -1;
    return eth->drv->send_packet(eth, data, len);
}

int spi_ethernet_receive(spi_ethernet_t *eth, uint8_t *data, uint16_t len) {
    if (!eth || !eth->drv || !eth->drv->read_packet) return -1;
    return eth->drv->read_packet(eth, data, len);
}

uint16_t spi_ethernet_available(spi_ethernet_t *eth) {
    if (!eth || !eth->drv || !eth->drv->available) return 0;
    return eth->drv->available(eth);
}

int ethernet_send_frame(spi_ethernet_t *eth, ethernet_frame_t *frame) {
    uint8_t buffer[ETH_MAX_FRAME];
    uint16_t pos = 0;

    // Destination MAC
    for(int i = 0; i < 6; i++)
        buffer[pos++] = frame->dest[i];

    // Source MAC
    for(int i = 0; i < 6; i++)
        buffer[pos++] = frame->src[i];

    // EtherType (big endian)
    buffer[pos++] = (frame->type >> 8);
    buffer[pos++] = (frame->type & 0xFF);

    // Payload
    for(int i = 0; i < frame->payload_len; i++)
        buffer[pos++] = frame->payload[i];

    return spi_ethernet_send(eth, buffer, pos);
}

int ethernet_receive_frame(spi_ethernet_t *eth, ethernet_frame_t *frame) {
    uint8_t buffer[ETH_MAX_FRAME];

    int len = spi_ethernet_receive(eth, buffer, sizeof(buffer));
    if(len <= ETH_HEADER_SIZE)
        return 0;

    uint16_t pos = 0;

    for(int i = 0; i < 6; i++)
        frame->dest[i] = buffer[pos++];

    for(int i = 0; i < 6; i++)
        frame->src[i] = buffer[pos++];

    frame->type = (buffer[pos++] << 8);
    frame->type |= buffer[pos++];

    frame->payload_len = len - ETH_HEADER_SIZE;

    for(int i = 0; i < frame->payload_len; i++)
        frame->payload[i] = buffer[pos++];

    return frame->payload_len;
}

// ------------------------------------------------------------------------ END