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
 * @file spi_ethernet_w6100.c
 * @brief SPI Ethernet WIZnet W6100 Driver.
 */

#include "spi_ethernet.h"
#include "spi_ethernet_w6100.h"
#include "drv_spi_master.h"
#include <delays.h>
#include <string.h>

#define SPI_ETH_OK           0x00
#define SPI_ETH_INIT_ERROR   0xFF

#define W6100_IR_SENDOK      0x10

pin_name_t w6100_cs_pin;

static spi_ethernet_t *current_eth = NULL;
static uint8_t w6100_mac_addr[ 6 ];
static uint8_t w6100_ipaddr[ 4 ];
static uint8_t w6100_hwRev;
uint8_t dbg_sock_sr;
uint16_t dbg_send_len;
uint8_t dbg_send_ir;
uint8_t dbg_cr_after_open;
uint8_t dbg_cr_stuck;

static uint8_t   w6100_read_reg( uint16_t addr, uint8_t bsb );
static void      w6100_write_reg( uint16_t addr, uint8_t bsb, uint8_t val_in );
static uint16_t  w6100_read_reg16( uint16_t addr, uint8_t bsb );
static void      w6100_write_reg16( uint16_t addr, uint8_t bsb, uint16_t value );
static void      w6100_read_burst( uint16_t addr, uint8_t bsb, uint8_t *buf, uint16_t len );
static void      w6100_write_burst( uint16_t addr, uint8_t bsb, uint8_t *buf, uint16_t len );
static void      w6100_hw_reset( spi_ethernet_t *eth );
static void      w6100_wait_socket_cmd( void );
static void      w6100_open_socket0_macraw( void );

uint16_t w6100_send_packet( spi_ethernet_t *eth, uint8_t *buf, uint16_t len );
uint16_t w6100_read_packet( spi_ethernet_t *eth, uint8_t *buf, uint16_t len );
uint8_t  w6100_packet_available( spi_ethernet_t *eth );

spi_ethernet_driver_t w6100_driver = {
    .init            = w6100_init,
    .send_packet     = w6100_send_packet,
    .read_packet     = w6100_read_packet,
    .available       = w6100_packet_available,
    .get_link_status = w6100_get_link_status,
    .set_mac         = w6100_set_mac,
    .get_mac         = w6100_get_mac,
    .set_ip          = w6100_set_ip,
    .get_ip          = w6100_get_ip
};

// Low-Level SPI Access
static uint8_t w6100_read_reg( uint16_t addr, uint8_t bsb ) {
    uint8_t header[ 3 ];
    uint8_t val;

    header[ 0 ] = ( uint8_t )( addr >> 8 );
    header[ 1 ] = ( uint8_t )( addr & 0xFF );
    header[ 2 ] = ( uint8_t )( bsb | W6100_RWB_READ | W6100_OM_VDM );
    val = 0;

    spi_master_select_device( w6100_cs_pin );
    spi_master_write_then_read( current_eth->spi, header, 3, &val, 1 );
    spi_master_deselect_device( w6100_cs_pin );

    return val;
}

static void w6100_write_reg( uint16_t addr, uint8_t bsb, uint8_t val_in ) {
    uint8_t frame[ 4 ];

    frame[ 0 ] = ( uint8_t )( addr >> 8 );
    frame[ 1 ] = ( uint8_t )( addr & 0xFF );
    frame[ 2 ] = ( uint8_t )( bsb | W6100_RWB_WRITE | W6100_OM_VDM );
    frame[ 3 ] = val_in;

    spi_master_select_device( w6100_cs_pin );
    spi_master_write( current_eth->spi, frame, 4 );
    spi_master_deselect_device( w6100_cs_pin );
}

static uint16_t w6100_read_reg16( uint16_t addr, uint8_t bsb ) {
    uint8_t buf[ 2 ];
    w6100_read_burst( addr, bsb, buf, 2 );
    return ( uint16_t )( ( ( uint16_t )buf[ 0 ] << 8 ) | buf[ 1 ] );
}

static void w6100_write_reg16( uint16_t addr, uint8_t bsb, uint16_t value ) {
    uint8_t buf[ 2 ];
    buf[ 0 ] = ( uint8_t )( value >> 8 );
    buf[ 1 ] = ( uint8_t )( value & 0xFF );
    w6100_write_burst( addr, bsb, buf, 2 );
}

static void w6100_read_burst( uint16_t addr, uint8_t bsb, uint8_t *buf, uint16_t len ) {
    uint8_t header[ 3 ];

    header[ 0 ] = ( uint8_t )( addr >> 8 );
    header[ 1 ] = ( uint8_t )( addr & 0xFF );
    header[ 2 ] = ( uint8_t )( bsb | W6100_RWB_READ | W6100_OM_VDM );

    spi_master_select_device( w6100_cs_pin );
    spi_master_write_then_read( current_eth->spi, header, 3, buf, len );
    spi_master_deselect_device( w6100_cs_pin );
}

static void w6100_write_burst( uint16_t addr, uint8_t bsb, uint8_t *buf, uint16_t len ) {
    uint8_t header[ 3 ];

    header[ 0 ] = ( uint8_t )( addr >> 8 );
    header[ 1 ] = ( uint8_t )( addr & 0xFF );
    header[ 2 ] = ( uint8_t )( bsb | W6100_RWB_WRITE | W6100_OM_VDM );

    spi_master_select_device( w6100_cs_pin );
    spi_master_write( current_eth->spi, header, 3 );
    spi_master_write( current_eth->spi, buf, len );
    spi_master_deselect_device( w6100_cs_pin );
}

// Init
static void w6100_hw_reset( spi_ethernet_t *eth ) {
    digital_out_high( &eth->reset ); Delay_ms( 10 );
    digital_out_low( &eth->reset );  Delay_ms( 1 );
    digital_out_high( &eth->reset ); Delay_ms( 100 );
}

static void w6100_wait_socket_cmd( void ) {
    uint16_t tries = 0;
    while ( w6100_read_reg( W6100_Sn_CR, W6100_BSB_SOCKET0_REG( 0 ) ) ) {
        Delay_ms( 1 );
        if ( ++tries > 200 ) break;
    }
}

static uint8_t w6100_wait_sn_sr_macraw( void ) {
    uint16_t tries = 0;
    uint8_t sr;
    do {
        sr = w6100_read_reg( W6100_Sn_SR, W6100_BSB_SOCKET0_REG( 0 ) );
        if ( sr == W6100_SOCK_MACRAW ) return 1;
        Delay_ms( 1 );
    } while ( ++tries < 500 );
    return 0;
}

static void w6100_open_socket0_macraw( void ) {
    w6100_write_reg( W6100_Sn_MR, W6100_BSB_SOCKET0_REG( 0 ), W6100_Sn_MR_MACRAW );
    w6100_write_reg( W6100_Sn_CR, W6100_BSB_SOCKET0_REG( 0 ), W6100_Sn_CR_OPEN );

    dbg_cr_after_open = w6100_read_reg( W6100_Sn_CR, W6100_BSB_SOCKET0_REG( 0 ) );
    dbg_sock_sr = w6100_wait_sn_sr_macraw( ) ? W6100_SOCK_MACRAW
                                              : w6100_read_reg( W6100_Sn_SR, W6100_BSB_SOCKET0_REG( 0 ) );
}

uint8_t w6100_reopen_socket0_macraw( void ) {
    w6100_open_socket0_macraw();
    return w6100_read_reg( W6100_Sn_SR, W6100_BSB_SOCKET0_REG( 0 ) );
}

void w6100_init( spi_ethernet_t *eth, spi_ethernet_driver_t *drv ) {
    current_eth = eth;

    w6100_hw_reset( eth );

    memcpy( w6100_mac_addr, eth->mac, 6 );
    memcpy( w6100_ipaddr, &eth->ip, 4 );

    w6100_hwRev = w6100_read_reg( W6100_VERSIONR, W6100_BSB_COMMON_REG );

    w6100_write_reg( W6100_NETLCKR, W6100_BSB_COMMON_REG, 0x3A );
    w6100_set_mac( w6100_mac_addr );
    w6100_set_ip( w6100_ipaddr );

    w6100_open_socket0_macraw( );   // <-- déplacé ICI, avant le relock

    w6100_write_reg( W6100_NETLCKR, W6100_BSB_COMMON_REG, 0x00 );   // relock à la fin
}

// Data Tranfert (MACRAW, socket 0)
uint16_t w6100_send_packet( spi_ethernet_t *eth, uint8_t *buf, uint16_t len ) {
    uint16_t wr_ptr;
    current_eth = eth;

    wr_ptr = w6100_read_reg16( W6100_Sn_TX_WR, W6100_BSB_SOCKET0_REG( 0 ) );
    w6100_write_burst( wr_ptr, W6100_BSB_SOCKET0_TX( 0 ), buf, len );
    w6100_write_reg16( W6100_Sn_TX_WR, W6100_BSB_SOCKET0_REG( 0 ), ( uint16_t )( wr_ptr + len ) );

    w6100_write_reg( W6100_Sn_CR, W6100_BSB_SOCKET0_REG( 0 ), W6100_Sn_CR_SEND );
    w6100_wait_socket_cmd( );

    dbg_send_len = len;
    dbg_send_ir = w6100_read_reg( W6100_Sn_IR, W6100_BSB_SOCKET0_REG( 0 ) );

    w6100_write_reg( W6100_Sn_IR, W6100_BSB_SOCKET0_REG( 0 ), W6100_IR_SENDOK );

    return len;
}

uint8_t w6100_packet_available( spi_ethernet_t *eth ) {
    uint16_t rsr;
    if ( !eth ) return 0;

    rsr = w6100_read_reg16( W6100_Sn_RX_RSR, W6100_BSB_SOCKET0_REG( 0 ) );
    return ( rsr > 0 ) ? 1 : 0;
}

uint16_t w6100_read_packet( spi_ethernet_t *eth, uint8_t *buf, uint16_t max_len ) {
    uint16_t rd_ptr, frame_len, data_len, copy_len;
    uint8_t hdr[ 2 ];
    current_eth = eth;

    if ( !w6100_packet_available( eth ) ) return 0;

    rd_ptr = w6100_read_reg16( W6100_Sn_RX_RD, W6100_BSB_SOCKET0_REG( 0 ) );

    w6100_read_burst( rd_ptr, W6100_BSB_SOCKET0_RX( 0 ), hdr, 2 );
    frame_len = ( uint16_t )( ( ( uint16_t )hdr[ 0 ] << 8 ) | hdr[ 1 ] );

    if ( frame_len < 2 ) {
        w6100_write_reg16( W6100_Sn_RX_RD, W6100_BSB_SOCKET0_REG( 0 ), ( uint16_t )( rd_ptr + 2 ) );
        w6100_write_reg( W6100_Sn_CR, W6100_BSB_SOCKET0_REG( 0 ), W6100_Sn_CR_RECV );
        return 0;
    }

    data_len = ( uint16_t )( frame_len - 2 );
    copy_len = ( data_len > max_len ) ? max_len : data_len;
    w6100_read_burst( ( uint16_t )( rd_ptr + 2 ), W6100_BSB_SOCKET0_RX( 0 ), buf, copy_len );

    w6100_write_reg16( W6100_Sn_RX_RD, W6100_BSB_SOCKET0_REG( 0 ), ( uint16_t )( rd_ptr + frame_len ) );
    w6100_write_reg( W6100_Sn_CR, W6100_BSB_SOCKET0_REG( 0 ), W6100_Sn_CR_RECV );

    return copy_len;
}

// Link / Identification
uint8_t w6100_get_link_status( void ) {
    uint8_t phycfgr;
    if ( !current_eth ) return 0;

    phycfgr = w6100_read_reg( W6100_PHYSR, W6100_BSB_COMMON_REG );
    return ( phycfgr & W6100_PHYSR_LNK_MASK ) ? 1 : 0;
}

uint8_t w6100_get_rev( void ) {
    return w6100_hwRev;
}

// Addressing
int w6100_set_mac( uint8_t mac[ 6 ] ) {
    memcpy( w6100_mac_addr, mac, 6 );
    w6100_write_burst( W6100_SHAR, W6100_BSB_COMMON_REG, mac, 6 );
    return 1;
}

int w6100_get_mac( uint8_t mac[ 6 ] ) {
    memcpy( mac, w6100_mac_addr, 6 );
    return 1;
}

int w6100_set_ip( uint8_t ip[ 4 ] ) {
    memcpy( w6100_ipaddr, ip, 4 );
    w6100_write_burst( W6100_SIPR, W6100_BSB_COMMON_REG, ip, 4 );
    return 1;
}

int w6100_get_ip( uint8_t ip[ 4 ] ) {
    memcpy( ip, w6100_ipaddr, 4 );
    return 1;
}

// Config / Setup
void w6100_cfg_setup( w6100_cfg_t *cfg ) {
    cfg->miso = HAL_PIN_NC;
    cfg->mosi = HAL_PIN_NC;
    cfg->sck  = HAL_PIN_NC;
    cfg->cs   = HAL_PIN_NC;
    cfg->rst  = HAL_PIN_NC;

    cfg->spi_speed = 1000000;
    cfg->spi_mode  = SPI_MASTER_MODE_0;

    cfg->full_duplex = 0;
}

uint8_t w6100_configure( spi_ethernet_t *eth, spi_master_t *spi, w6100_cfg_t *cfg ) {
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

    w6100_cs_pin = cfg->cs;
    spi_master_deselect_device( w6100_cs_pin );

    eth->spi = spi;
    memcpy( eth->mac, cfg->mac, 6 );
    memcpy( &eth->ip, cfg->ip, 4 );
    eth->fullDuplex = cfg->full_duplex;

    return 0;
}

// ----------------------------------------------------------------------- END
