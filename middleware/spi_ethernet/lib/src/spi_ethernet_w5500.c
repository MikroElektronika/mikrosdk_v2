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
 * @file spi_ethernet_w5500.c
 * @brief SPI Ethernet WIZnet W5500 Driver.
 *
 * @note Socket 0 est ouvert en mode MACRAW pour exposer la meme API
 * trame-Ethernet-brute que le driver ENC28J60, afin que le parsing
 * ARP/ICMP/TCP de main.c reste independant de la puce.
 */

#include "spi_ethernet.h"
#include "spi_ethernet_w5500.h"
#include "drv_spi_master.h"
#include <delays.h>
#include <string.h>

#define SPI_ETH_OK           0x00
#define SPI_ETH_INIT_ERROR   0xFF

#define W5500_IR_SENDOK      0x10

pin_name_t w5500_cs_pin;

static spi_ethernet_t *current_eth = NULL;
static uint8_t w5500_mac_addr[ 6 ];
static uint8_t w5500_ipaddr[ 4 ];
static uint8_t w5500_hwRev;

static uint8_t   w5500_read_reg( uint16_t addr, uint8_t bsb );
static void      w5500_write_reg( uint16_t addr, uint8_t bsb, uint8_t val_in );
static uint16_t  w5500_read_reg16( uint16_t addr, uint8_t bsb );
static void      w5500_write_reg16( uint16_t addr, uint8_t bsb, uint16_t value );
static void      w5500_read_burst( uint16_t addr, uint8_t bsb, uint8_t *buf, uint16_t len );
static void      w5500_write_burst( uint16_t addr, uint8_t bsb, uint8_t *buf, uint16_t len );
static void      w5500_hw_reset( spi_ethernet_t *eth );
static void      w5500_wait_socket_cmd( void );
static void      w5500_open_socket0_macraw( void );

uint16_t w5500_send_packet( spi_ethernet_t *eth, uint8_t *buf, uint16_t len );
uint16_t w5500_read_packet( spi_ethernet_t *eth, uint8_t *buf, uint16_t len );
uint8_t  w5500_packet_available( spi_ethernet_t *eth );

spi_ethernet_driver_t w5500_driver = {
    .init            = w5500_init,
    .send_packet     = w5500_send_packet,
    .read_packet     = w5500_read_packet,
    .available       = w5500_packet_available,
    .get_link_status = w5500_get_link_status,
    .set_mac         = w5500_set_mac,
    .get_mac         = w5500_get_mac,
    .set_ip          = w5500_set_ip,
    .get_ip          = w5500_get_ip
};

/* --------------------------------------------------------------------
 * Acces SPI bas niveau
 * Chaque transaction : [ addr high ][ addr low ][ control byte ][ data... ]
 * -------------------------------------------------------------------- */
static uint8_t w5500_read_reg( uint16_t addr, uint8_t bsb ) {
    uint8_t header[ 3 ];
    uint8_t val;

    header[ 0 ] = ( uint8_t )( addr >> 8 );
    header[ 1 ] = ( uint8_t )( addr & 0xFF );
    header[ 2 ] = ( uint8_t )( bsb | W5500_RWB_READ | W5500_OM_FDM1 );
    val = 0;

    spi_master_select_device( w5500_cs_pin );
    spi_master_write_then_read( current_eth->spi, header, 3, &val, 1 );
    spi_master_deselect_device( w5500_cs_pin );

    return val;
}

static void w5500_write_reg( uint16_t addr, uint8_t bsb, uint8_t val_in ) {
    uint8_t frame[ 4 ];

    frame[ 0 ] = ( uint8_t )( addr >> 8 );
    frame[ 1 ] = ( uint8_t )( addr & 0xFF );
    frame[ 2 ] = ( uint8_t )( bsb | W5500_RWB_WRITE | W5500_OM_FDM1 );
    frame[ 3 ] = val_in;

    spi_master_select_device( w5500_cs_pin );
    spi_master_write( current_eth->spi, frame, 4 );
    spi_master_deselect_device( w5500_cs_pin );
}

static uint16_t w5500_read_reg16( uint16_t addr, uint8_t bsb ) {
    uint8_t buf[ 2 ];
    w5500_read_burst( addr, bsb, buf, 2 );
    return ( uint16_t )( ( ( uint16_t )buf[ 0 ] << 8 ) | buf[ 1 ] );
}

static void w5500_write_reg16( uint16_t addr, uint8_t bsb, uint16_t value ) {
    uint8_t buf[ 2 ];
    buf[ 0 ] = ( uint8_t )( value >> 8 );
    buf[ 1 ] = ( uint8_t )( value & 0xFF );
    w5500_write_burst( addr, bsb, buf, 2 );
}

static void w5500_read_burst( uint16_t addr, uint8_t bsb, uint8_t *buf, uint16_t len ) {
    uint8_t header[ 3 ];

    header[ 0 ] = ( uint8_t )( addr >> 8 );
    header[ 1 ] = ( uint8_t )( addr & 0xFF );
    header[ 2 ] = ( uint8_t )( bsb | W5500_RWB_READ | W5500_OM_VDM );

    spi_master_select_device( w5500_cs_pin );
    spi_master_write_then_read( current_eth->spi, header, 3, buf, len );
    spi_master_deselect_device( w5500_cs_pin );
}

static void w5500_write_burst( uint16_t addr, uint8_t bsb, uint8_t *buf, uint16_t len ) {
    uint8_t header[ 3 ];

    header[ 0 ] = ( uint8_t )( addr >> 8 );
    header[ 1 ] = ( uint8_t )( addr & 0xFF );
    header[ 2 ] = ( uint8_t )( bsb | W5500_RWB_WRITE | W5500_OM_VDM );

    spi_master_select_device( w5500_cs_pin );
    spi_master_write( current_eth->spi, header, 3 );
    spi_master_write( current_eth->spi, buf, len );
    spi_master_deselect_device( w5500_cs_pin );
}

// Init
static void w5500_hw_reset( spi_ethernet_t *eth ) {
    digital_out_high( &eth->reset ); Delay_ms( 10 );
    digital_out_low( &eth->reset );  Delay_ms( 1 );
    digital_out_high( &eth->reset ); Delay_ms( 100 );
}

static void w5500_wait_socket_cmd( void ) {
    uint16_t tries = 0;
    while ( w5500_read_reg( W5500_Sn_CR, W5500_BSB_SOCKET0_REG( 0 ) ) ) {
        Delay_ms( 1 );
        if ( ++tries > 200 ) break;
    }
}

static void w5500_open_socket0_macraw( void ) {
    w5500_write_reg( W5500_Sn_MR, W5500_BSB_SOCKET0_REG( 0 ), W5500_Sn_MR_MACRAW | W5500_Sn_MR_MF );
    w5500_write_reg( W5500_Sn_CR, W5500_BSB_SOCKET0_REG( 0 ), W5500_Sn_CR_OPEN );
    w5500_wait_socket_cmd( );
}

void w5500_init( spi_ethernet_t *eth, spi_ethernet_driver_t *drv ) {
    current_eth = eth;

    w5500_hw_reset( eth );

    memcpy( w5500_mac_addr, eth->mac, 6 );
    memcpy( w5500_ipaddr, &eth->ip, 4 );

    w5500_hwRev = w5500_read_reg( W5500_VERSIONR, W5500_BSB_COMMON_REG );

    w5500_set_mac( w5500_mac_addr );
    w5500_set_ip( w5500_ipaddr );

    w5500_open_socket0_macraw( );
}

// Data Tranfert (MACRAW, socket 0)
uint16_t w5500_send_packet( spi_ethernet_t *eth, uint8_t *buf, uint16_t len ) {
    uint16_t wr_ptr;
    current_eth = eth;

    wr_ptr = w5500_read_reg16( W5500_Sn_TX_WR, W5500_BSB_SOCKET0_REG( 0 ) );
    w5500_write_burst( wr_ptr, W5500_BSB_SOCKET0_TX( 0 ), buf, len );
    w5500_write_reg16( W5500_Sn_TX_WR, W5500_BSB_SOCKET0_REG( 0 ), ( uint16_t )( wr_ptr + len ) );

    w5500_write_reg( W5500_Sn_CR, W5500_BSB_SOCKET0_REG( 0 ), W5500_Sn_CR_SEND );
    w5500_wait_socket_cmd( );

    w5500_write_reg( W5500_Sn_IR, W5500_BSB_SOCKET0_REG( 0 ), W5500_IR_SENDOK );

    return len;
}

uint8_t w5500_packet_available( spi_ethernet_t *eth ) {
    uint16_t rsr;
    if ( !eth ) return 0;

    rsr = w5500_read_reg16( W5500_Sn_RX_RSR, W5500_BSB_SOCKET0_REG( 0 ) );
    return ( rsr > 0 ) ? 1 : 0;
}

uint16_t w5500_read_packet( spi_ethernet_t *eth, uint8_t *buf, uint16_t max_len ) {
    uint16_t rd_ptr, frame_len, data_len, copy_len;
    uint8_t hdr[ 2 ];
    current_eth = eth;

    if ( !w5500_packet_available( eth ) ) return 0;

    rd_ptr = w5500_read_reg16( W5500_Sn_RX_RD, W5500_BSB_SOCKET0_REG( 0 ) );

    w5500_read_burst( rd_ptr, W5500_BSB_SOCKET0_RX( 0 ), hdr, 2 );
    frame_len = ( uint16_t )( ( ( uint16_t )hdr[ 0 ] << 8 ) | hdr[ 1 ] );

    if ( frame_len < 2 ) {
        w5500_write_reg16( W5500_Sn_RX_RD, W5500_BSB_SOCKET0_REG( 0 ), ( uint16_t )( rd_ptr + 2 ) );
        w5500_write_reg( W5500_Sn_CR, W5500_BSB_SOCKET0_REG( 0 ), W5500_Sn_CR_RECV );
        return 0;
    }

    data_len = ( uint16_t )( frame_len - 2 );
    copy_len = ( data_len > max_len ) ? max_len : data_len;
    w5500_read_burst( ( uint16_t )( rd_ptr + 2 ), W5500_BSB_SOCKET0_RX( 0 ), buf, copy_len );

    w5500_write_reg16( W5500_Sn_RX_RD, W5500_BSB_SOCKET0_REG( 0 ), ( uint16_t )( rd_ptr + frame_len ) );
    w5500_write_reg( W5500_Sn_CR, W5500_BSB_SOCKET0_REG( 0 ), W5500_Sn_CR_RECV );

    return copy_len;
}

// Link / Identification
uint8_t w5500_get_link_status( void ) {
    uint8_t phycfgr;
    if ( !current_eth ) return 0;

    phycfgr = w5500_read_reg( W5500_PHYCFGR, W5500_BSB_COMMON_REG );
    return ( phycfgr & W5500_PHYCFGR_LNK_MASK ) ? 1 : 0;
}

uint8_t w5500_get_rev( void ) {
    return w5500_hwRev;
}

// Addressage
int w5500_set_mac( uint8_t mac[ 6 ] ) {
    memcpy( w5500_mac_addr, mac, 6 );
    w5500_write_burst( W5500_SHAR, W5500_BSB_COMMON_REG, mac, 6 );
    return 1;
}

int w5500_get_mac( uint8_t mac[ 6 ] ) {
    memcpy( mac, w5500_mac_addr, 6 );
    return 1;
}

int w5500_set_ip( uint8_t ip[ 4 ] ) {
    memcpy( w5500_ipaddr, ip, 4 );
    w5500_write_burst( W5500_SIPR, W5500_BSB_COMMON_REG, ip, 4 );
    return 1;
}

int w5500_get_ip( uint8_t ip[ 4 ] ) {
    memcpy( ip, w5500_ipaddr, 4 );
    return 1;
}

// Config / Setup
void w5500_cfg_setup( w5500_cfg_t *cfg ) {
    cfg->miso = HAL_PIN_NC;
    cfg->mosi = HAL_PIN_NC;
    cfg->sck  = HAL_PIN_NC;
    cfg->cs   = HAL_PIN_NC;
    cfg->rst  = HAL_PIN_NC;

    cfg->spi_speed = 1000000;
    cfg->spi_mode  = SPI_MASTER_MODE_0;

    cfg->full_duplex = 0;
}

uint8_t w5500_configure( spi_ethernet_t *eth, spi_master_t *spi, w5500_cfg_t *cfg ) {
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

    w5500_cs_pin = cfg->cs;
    spi_master_deselect_device( w5500_cs_pin );

    eth->spi = spi;
    memcpy( eth->mac, cfg->mac, 6 );
    memcpy( &eth->ip, cfg->ip, 4 );
    eth->fullDuplex = cfg->full_duplex;

    return 0;
}

// ----------------------------------------------------------------------- END
