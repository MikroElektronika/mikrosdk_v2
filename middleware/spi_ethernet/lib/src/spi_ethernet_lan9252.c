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
 * @file spi_ethernet_lan9252.c
 * @brief SPI EtherCAT LAN9252 Driver.
 */

#include "spi_ethernet.h"
#include "spi_ethernet_lan9252.h"
#include "drv_spi_master.h"
#include <delays.h>
#include <string.h>

pin_name_t lan9252_cs_pin;

static spi_ethernet_t *current_eth = NULL;
static uint32_t lan9252_id_rev_cache = 0;

spi_ethernet_driver_t lan9252_driver = {
    .init            = lan9252_init,
    .send_packet     = lan9252_send_packet,
    .read_packet     = lan9252_read_packet,
    .available       = lan9252_packet_available,
    .get_link_status = lan9252_get_link_status,
    .set_mac         = lan9252_set_mac,
    .get_mac         = lan9252_get_mac,
    .set_ip          = lan9252_set_ip,
    .get_ip          = lan9252_get_ip
};

// Low-Level SPI Primitives
uint32_t lan9252_read_reg32( uint16_t addr ) {
    uint8_t header[ 3 ];
    uint8_t rxbuf[ 4 ];
    uint32_t val;

    header[ 0 ] = LAN9252_SPI_READ;
    header[ 1 ] = ( uint8_t )( addr >> 8 );
    header[ 2 ] = ( uint8_t )( addr & 0xFF );

    spi_master_select_device( lan9252_cs_pin );
    spi_master_write_then_read( current_eth->spi, header, 3, rxbuf, 4 );
    spi_master_deselect_device( lan9252_cs_pin );

    // rxbuf[0] = LSB first
    val = ( ( uint32_t )rxbuf[ 3 ] << 24 ) |
          ( ( uint32_t )rxbuf[ 2 ] << 16 ) |
          ( ( uint32_t )rxbuf[ 1 ] << 8 )  |
            ( uint32_t )rxbuf[ 0 ];

    return val;
}

void lan9252_write_reg32( uint16_t addr, uint32_t value ) {
    uint8_t frame[ 7 ];

    frame[ 0 ] = LAN9252_SPI_WRITE;
    frame[ 1 ] = ( uint8_t )( addr >> 8 );
    frame[ 2 ] = ( uint8_t )( addr & 0xFF );
    frame[ 3 ] = ( uint8_t )( value & 0xFF );          // LSB first
    frame[ 4 ] = ( uint8_t )( ( value >> 8 )  & 0xFF );
    frame[ 5 ] = ( uint8_t )( ( value >> 16 ) & 0xFF );
    frame[ 6 ] = ( uint8_t )( ( value >> 24 ) & 0xFF );

    spi_master_select_device( lan9252_cs_pin );
    spi_master_write( current_eth->spi, frame, 7 );
    spi_master_deselect_device( lan9252_cs_pin );
}

// Identification
uint8_t lan9252_byte_test_ok( void ) {
    uint32_t val = lan9252_read_reg32( LAN9252_BYTE_TEST );
    return ( val == LAN9252_BYTE_TEST_PATTERN ) ? 1 : 0;
}

uint8_t lan9252_wait_ready( void ) {
    uint16_t tries = 0;

    // Step 1 : waiting for SPI link to be functional
    while ( !lan9252_byte_test_ok( ) ) {
        Delay_ms( 1 );
        if ( ++tries > 500 ) return 0;      // ~500ms timeout
    }

    // Step 2 : waiting for the device to be ready (HW_CFG.READY)
    tries = 0;
    while ( !( lan9252_read_reg32( LAN9252_HW_CFG ) & LAN9252_HW_CFG_READY_MASK ) ) {
        Delay_ms( 1 );
        if ( ++tries > 500 ) return 0;
    }

    return 1;
}

uint32_t lan9252_get_id_rev( void ) {
    return lan9252_id_rev_cache;
}

uint8_t lan9252_get_rev( void ) {
    return ( uint8_t )( lan9252_id_rev_cache & 0xFF );
}

// Init
static void lan9252_hw_reset( spi_ethernet_t *eth ) {
    digital_out_high( &eth->reset ); Delay_ms( 10 );
    digital_out_low( &eth->reset );  Delay_ms( 1 );
    digital_out_high( &eth->reset ); Delay_ms( 100 );
}

void lan9252_init( spi_ethernet_t *eth, spi_ethernet_driver_t *drv ) {
    current_eth = eth;

    lan9252_hw_reset( eth );

    if ( !lan9252_wait_ready( ) ) {
        lan9252_id_rev_cache = 0;
        return;
    }

    lan9252_id_rev_cache = lan9252_read_reg32( LAN9252_ID_REV );
}

// Stubs for the generic interface `spi_ethernet_driver_t`
int lan9252_reset( void ) {
    return -1;
}

uint16_t lan9252_send_packet( spi_ethernet_t *eth, uint8_t *buf, uint16_t len ) {
    ( void )eth; ( void )buf; ( void )len;
    return 0;
}

uint16_t lan9252_read_packet( spi_ethernet_t *eth, uint8_t *buf, uint16_t max_len ) {
    ( void )eth; ( void )buf; ( void )max_len;
    return 0;
}

uint8_t lan9252_packet_available( spi_ethernet_t *eth ) {
    ( void )eth;
    return 0;
}

uint8_t lan9252_get_link_status( void ) {
    return 0;
}

int lan9252_set_mac( uint8_t mac[ 6 ] ) {
    ( void )mac;
    return -1;
}

int lan9252_get_mac( uint8_t mac[ 6 ] ) {
    ( void )mac;
    return -1;
}

int lan9252_set_ip( uint8_t ip[ 4 ] ) {
    ( void )ip;
    return -1;
}

int lan9252_get_ip( uint8_t ip[ 4 ] ) {
    ( void )ip;
    return -1;
}

// Config / Setup
void lan9252_cfg_setup( lan9252_cfg_t *cfg ) {
    cfg->miso = HAL_PIN_NC;
    cfg->mosi = HAL_PIN_NC;
    cfg->sck  = HAL_PIN_NC;
    cfg->cs   = HAL_PIN_NC;
    cfg->rst  = HAL_PIN_NC;

    cfg->spi_speed = 1000000;
    cfg->spi_mode  = SPI_MASTER_MODE_0;

    cfg->full_duplex = 0;
}

uint8_t lan9252_configure( spi_ethernet_t *eth, spi_master_t *spi, lan9252_cfg_t *cfg ) {
    spi_master_config_t spi_cfg;
    spi_master_configure_default( &spi_cfg );

    spi_cfg.sck   = cfg->sck;
    spi_cfg.miso  = cfg->miso;
    spi_cfg.mosi  = cfg->mosi;
    spi_cfg.speed = cfg->spi_speed;
    spi_cfg.mode  = cfg->spi_mode;

    spi_master_open( spi, &spi_cfg );

    digital_out_init( &eth->cs, cfg->cs );
    digital_out_init( &eth->reset, cfg->rst );

    lan9252_cs_pin = cfg->cs;
    spi_master_deselect_device( lan9252_cs_pin );

    eth->spi = spi;
    memcpy( eth->mac, cfg->mac, 6 );
    memcpy( &eth->ip, cfg->ip, 4 );
    eth->fullDuplex = cfg->full_duplex;

    return 0;
}

// ----------------------------------------------------------------------- END
