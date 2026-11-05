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
 * @file eth_bus_spi.c
 * @brief Ethernet transport SPI bus binding.
 */

#include "eth_bus_spi.h"

static err_t eth_bus_spi_write( void *bus, uint8_t *hdr, uint16_t hdr_len, uint8_t *data_buf, uint16_t data_len );
static err_t eth_bus_spi_read( void *bus, uint8_t *hdr, uint16_t hdr_len, uint8_t *data_buf, uint16_t data_len );
static err_t eth_bus_spi_transfer( void *bus, uint8_t *tx_buf, uint8_t *rx_buf, uint16_t len );

eth_bus_ops_t eth_bus_spi_ops = {
    .write    = eth_bus_spi_write,
    .read     = eth_bus_spi_read,
    .transfer = eth_bus_spi_transfer
};

// Bus operations, each one is a single chip select assertion
static err_t eth_bus_spi_write( void *bus, uint8_t *hdr, uint16_t hdr_len, uint8_t *data_buf, uint16_t data_len ) {
    eth_bus_spi_t *spi_bus = ( eth_bus_spi_t * )bus;
    err_t err;

    spi_master_select_device( spi_bus->cs );
    err = spi_master_write( &spi_bus->spi, hdr, hdr_len );
    if ( err == SPI_MASTER_SUCCESS && data_buf && data_len )
        err = spi_master_write( &spi_bus->spi, data_buf, data_len );
    spi_master_deselect_device( spi_bus->cs );

    return ( err == SPI_MASTER_SUCCESS ) ? ETH_TRANSPORT_SUCCESS : ETH_TRANSPORT_ERROR;
}

static err_t eth_bus_spi_read( void *bus, uint8_t *hdr, uint16_t hdr_len, uint8_t *data_buf, uint16_t data_len ) {
    eth_bus_spi_t *spi_bus = ( eth_bus_spi_t * )bus;
    err_t err;

    spi_master_select_device( spi_bus->cs );
    err = spi_master_write_then_read( &spi_bus->spi, hdr, hdr_len, data_buf, data_len );
    spi_master_deselect_device( spi_bus->cs );

    return ( err == SPI_MASTER_SUCCESS ) ? ETH_TRANSPORT_SUCCESS : ETH_TRANSPORT_ERROR;
}

static err_t eth_bus_spi_transfer( void *bus, uint8_t *tx_buf, uint8_t *rx_buf, uint16_t len ) {
    eth_bus_spi_t *spi_bus = ( eth_bus_spi_t * )bus;
    err_t err;

    spi_master_select_device( spi_bus->cs );
    err = spi_master_transfer( &spi_bus->spi, tx_buf, rx_buf, len );
    spi_master_deselect_device( spi_bus->cs );

    return ( err == SPI_MASTER_SUCCESS ) ? ETH_TRANSPORT_SUCCESS : ETH_TRANSPORT_ERROR;
}

// Setup
void eth_bus_spi_cfg_setup( eth_bus_spi_cfg_t *cfg ) {
    if ( !cfg ) return;

    cfg->miso = HAL_PIN_NC;
    cfg->mosi = HAL_PIN_NC;
    cfg->sck  = HAL_PIN_NC;
    cfg->cs   = HAL_PIN_NC;

    cfg->speed = 1000000;
    cfg->mode  = SPI_MASTER_MODE_0;
}

err_t eth_bus_spi_configure( eth_transport_t *eth, eth_bus_spi_t *bus,
                             eth_bus_spi_cfg_t *bus_cfg, eth_transport_cfg_t *eth_cfg ) {
    spi_master_config_t spi_cfg;

    if ( !eth || !bus || !bus_cfg || !eth_cfg ) return ETH_TRANSPORT_ERROR;

    spi_master_configure_default( &spi_cfg );
    spi_cfg.sck   = bus_cfg->sck;
    spi_cfg.miso  = bus_cfg->miso;
    spi_cfg.mosi  = bus_cfg->mosi;
    spi_cfg.speed = bus_cfg->speed;
    spi_cfg.mode  = bus_cfg->mode;

    if ( spi_master_open( &bus->spi, &spi_cfg ) == SPI_MASTER_ERROR )
        return ETH_TRANSPORT_ERROR;

    digital_out_init( &bus->cs_out, bus_cfg->cs );
    bus->cs = bus_cfg->cs;
    spi_master_deselect_device( bus->cs );

    return eth_transport_configure( eth, bus, &eth_bus_spi_ops, eth_cfg );
}

// ------------------------------------------------------------------------ END
