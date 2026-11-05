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
 * @file eth_transport.c
 * @brief Ethernet transport core.
 */

#include "eth_transport.h"
#include <string.h>

/* --- Configuration --- */
void eth_transport_cfg_setup( eth_transport_cfg_t *cfg ) {
    if ( !cfg ) return;

    cfg->rst = HAL_PIN_NC;
    memset( cfg->mac, 0, sizeof( cfg->mac ) );
    memset( cfg->ip, 0, sizeof( cfg->ip ) );
    cfg->full_duplex = 0;
}

err_t eth_transport_configure( eth_transport_t *eth, void *bus, eth_bus_ops_t *bus_ops,
                               eth_transport_cfg_t *cfg ) {
    if ( !eth || !bus || !bus_ops || !cfg ) return ETH_TRANSPORT_ERROR;

    eth->bus = bus;
    eth->bus_ops = bus_ops;

    digital_out_init( &eth->reset, cfg->rst );

    memcpy( eth->mac, cfg->mac, 6 );
    memcpy( eth->ip, cfg->ip, 4 );
    eth->full_duplex = cfg->full_duplex;

    return ETH_TRANSPORT_SUCCESS;
}

/* --- Bus access (used by controller drivers) --- */
err_t eth_transport_bus_write( eth_transport_t *eth, uint8_t *hdr, uint16_t hdr_len,
                               uint8_t *data_buf, uint16_t data_len ) {
    if ( !eth || !eth->bus_ops || !eth->bus_ops->write ) return ETH_TRANSPORT_ERROR;
    return eth->bus_ops->write( eth->bus, hdr, hdr_len, data_buf, data_len );
}

err_t eth_transport_bus_read( eth_transport_t *eth, uint8_t *hdr, uint16_t hdr_len,
                              uint8_t *data_buf, uint16_t data_len ) {
    if ( !eth || !eth->bus_ops || !eth->bus_ops->read ) return ETH_TRANSPORT_ERROR;
    return eth->bus_ops->read( eth->bus, hdr, hdr_len, data_buf, data_len );
}

err_t eth_transport_bus_transfer( eth_transport_t *eth, uint8_t *tx_buf, uint8_t *rx_buf, uint16_t len ) {
    if ( !eth || !eth->bus_ops || !eth->bus_ops->transfer ) return ETH_TRANSPORT_ERROR;
    return eth->bus_ops->transfer( eth->bus, tx_buf, rx_buf, len );
}

/* --- Initialization --- */
err_t eth_transport_init( eth_transport_t *eth, eth_transport_driver_t *drv ) {
    if ( !eth || !drv ) return ETH_TRANSPORT_ERROR;
    eth->drv = drv;
    if ( !drv->init ) return ETH_TRANSPORT_SUCCESS;
    return drv->init( eth );
}

err_t eth_transport_reset( eth_transport_t *eth ) {
    if ( !eth || !eth->drv ) return ETH_TRANSPORT_ERROR;
    if ( eth->drv->reset ) return eth->drv->reset( eth );
    if ( eth->drv->init ) return eth->drv->init( eth );
    return ETH_TRANSPORT_ERROR;
}

/* --- Data transfer --- */
uint16_t eth_transport_send( eth_transport_t *eth, uint8_t *buf, uint16_t len ) {
    if ( !eth || !eth->drv || !eth->drv->send_packet || !buf || !len ) return 0;
    return eth->drv->send_packet( eth, buf, len );
}

uint16_t eth_transport_receive( eth_transport_t *eth, uint8_t *buf, uint16_t max_len ) {
    if ( !eth || !eth->drv || !eth->drv->read_packet || !buf || !max_len ) return 0;
    return eth->drv->read_packet( eth, buf, max_len );
}

uint8_t eth_transport_available( eth_transport_t *eth ) {
    if ( !eth || !eth->drv || !eth->drv->available ) return 0;
    return eth->drv->available( eth );
}

uint8_t eth_transport_get_link_status( eth_transport_t *eth ) {
    if ( !eth || !eth->drv || !eth->drv->get_link_status ) return 0;
    return eth->drv->get_link_status( eth );
}

/* --- Addressing --- */
err_t eth_transport_set_mac( eth_transport_t *eth, uint8_t *mac ) {
    if ( !eth || !mac ) return ETH_TRANSPORT_ERROR;
    if ( mac != eth->mac )
        memcpy( eth->mac, mac, 6 );
    if ( eth->drv && eth->drv->set_mac )
        return eth->drv->set_mac( eth, eth->mac );
    return ETH_TRANSPORT_SUCCESS;
}

err_t eth_transport_get_mac( eth_transport_t *eth, uint8_t *mac ) {
    if ( !eth || !mac ) return ETH_TRANSPORT_ERROR;
    memcpy( mac, eth->mac, 6 );
    return ETH_TRANSPORT_SUCCESS;
}

err_t eth_transport_set_ip( eth_transport_t *eth, uint8_t *ip ) {
    if ( !eth || !ip ) return ETH_TRANSPORT_ERROR;
    if ( ip != eth->ip )
        memcpy( eth->ip, ip, 4 );
    if ( eth->drv && eth->drv->set_ip )
        return eth->drv->set_ip( eth, eth->ip );
    return ETH_TRANSPORT_SUCCESS;
}

err_t eth_transport_get_ip( eth_transport_t *eth, uint8_t *ip ) {
    if ( !eth || !ip ) return ETH_TRANSPORT_ERROR;
    memcpy( ip, eth->ip, 4 );
    return ETH_TRANSPORT_SUCCESS;
}

// ------------------------------------------------------------------------ END
