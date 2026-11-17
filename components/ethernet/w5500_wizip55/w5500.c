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
 * @file w5500.c
 * @brief SPI Ethernet WIZnet W5500 Driver.
 */

#include "w5500.h"
#include <delays.h>

#define W5500_IR_SENDOK      0x10
#define W5500_VERSION        0x04

#define W5500_RX_HDR_SIZE    2                          // MACRAW length prefix
#define W5500_RX_FRAME_MAX   ( 1518 + W5500_RX_HDR_SIZE )   // VLAN tagged frames included
#define W5500_RX_FRAME_MIN   ( 14 + W5500_RX_HDR_SIZE )     // Ethernet header
#define W5500_SEND_TRIES     10000                      // x 10 us, >= 100 ms

#define W5500_CTX( eth )     ( ( w5500_ctx_t * )( eth )->driver_ctx )

static w5500_ctx_t w5500_default_ctx;

static uint8_t   w5500_read_reg( eth_transport_t *eth, uint16_t addr, uint8_t bsb );
static void      w5500_write_reg( eth_transport_t *eth, uint16_t addr, uint8_t bsb, uint8_t val_in );
static uint16_t  w5500_read_reg16( eth_transport_t *eth, uint16_t addr, uint8_t bsb );
static uint16_t  w5500_read_reg16_stable( eth_transport_t *eth, uint16_t addr );
static void      w5500_write_reg16( eth_transport_t *eth, uint16_t addr, uint8_t bsb, uint16_t value );
static void      w5500_read_burst( eth_transport_t *eth, uint16_t addr, uint8_t bsb, uint8_t *buf, uint16_t len );
static void      w5500_write_burst( eth_transport_t *eth, uint16_t addr, uint8_t bsb, uint8_t *buf, uint16_t len );
static void      w5500_hw_reset( eth_transport_t *eth );
static uint8_t   w5500_wait_socket_cmd( eth_transport_t *eth );
static uint8_t   w5500_open_socket0_macraw( eth_transport_t *eth );
static void      w5500_reopen_socket0( eth_transport_t *eth );

eth_transport_driver_t w5500_driver = {
    .init            = w5500_init,
    .send_packet     = w5500_send_packet,
    .read_packet     = w5500_read_packet,
    .available       = w5500_packet_available,
    .get_link_status = w5500_get_link_status,
    .set_mac         = w5500_set_mac,
    .set_ip          = w5500_set_ip
};

// Low-Level SPI Access
static uint8_t w5500_read_reg( eth_transport_t *eth, uint16_t addr, uint8_t bsb ) {
    uint8_t header[ 3 ];
    uint8_t val = 0;

    header[ 0 ] = ( uint8_t )( addr >> 8 );
    header[ 1 ] = ( uint8_t )( addr & 0xFF );
    header[ 2 ] = ( uint8_t )( bsb | W5500_RWB_READ | W5500_OM_FDM1 );

    ( void )eth_transport_bus_read( eth, header, 3, &val, 1 );

    return val;
}

static void w5500_write_reg( eth_transport_t *eth, uint16_t addr, uint8_t bsb, uint8_t val_in ) {
    uint8_t frame[ 4 ];

    frame[ 0 ] = ( uint8_t )( addr >> 8 );
    frame[ 1 ] = ( uint8_t )( addr & 0xFF );
    frame[ 2 ] = ( uint8_t )( bsb | W5500_RWB_WRITE | W5500_OM_FDM1 );
    frame[ 3 ] = val_in;

    ( void )eth_transport_bus_write( eth, frame, 4, NULL, 0 );
}

static uint16_t w5500_read_reg16( eth_transport_t *eth, uint16_t addr, uint8_t bsb ) {
    uint8_t buf[ 2 ] = { 0, 0 };
    w5500_read_burst( eth, addr, bsb, buf, 2 );
    return ( uint16_t )( ( ( uint16_t )buf[ 0 ] << 8 ) | buf[ 1 ] );
}

// Sn_TX_FSR / Sn_RX_RSR change while the chip works, read until two values agree
static uint16_t w5500_read_reg16_stable( eth_transport_t *eth, uint16_t addr ) {
    uint16_t prev;
    uint16_t val = w5500_read_reg16( eth, addr, W5500_BSB_SOCKET0_REG( 0 ) );
    uint8_t tries = 0;

    do {
        prev = val;
        val = w5500_read_reg16( eth, addr, W5500_BSB_SOCKET0_REG( 0 ) );
    } while ( val != prev && ++tries < 8 );

    return val;
}

static void w5500_write_reg16( eth_transport_t *eth, uint16_t addr, uint8_t bsb, uint16_t value ) {
    uint8_t buf[ 2 ];
    buf[ 0 ] = ( uint8_t )( value >> 8 );
    buf[ 1 ] = ( uint8_t )( value & 0xFF );
    w5500_write_burst( eth, addr, bsb, buf, 2 );
}

static void w5500_read_burst( eth_transport_t *eth, uint16_t addr, uint8_t bsb, uint8_t *buf, uint16_t len ) {
    uint8_t header[ 3 ];

    header[ 0 ] = ( uint8_t )( addr >> 8 );
    header[ 1 ] = ( uint8_t )( addr & 0xFF );
    header[ 2 ] = ( uint8_t )( bsb | W5500_RWB_READ | W5500_OM_VDM );

    ( void )eth_transport_bus_read( eth, header, 3, buf, len );
}

static void w5500_write_burst( eth_transport_t *eth, uint16_t addr, uint8_t bsb, uint8_t *buf, uint16_t len ) {
    uint8_t header[ 3 ];

    header[ 0 ] = ( uint8_t )( addr >> 8 );
    header[ 1 ] = ( uint8_t )( addr & 0xFF );
    header[ 2 ] = ( uint8_t )( bsb | W5500_RWB_WRITE | W5500_OM_VDM );

    ( void )eth_transport_bus_write( eth, header, 3, buf, len );
}

// Init
static void w5500_hw_reset( eth_transport_t *eth ) {
    digital_out_high( &eth->reset ); Delay_ms( 10 );
    digital_out_low( &eth->reset );  Delay_ms( 1 );
    digital_out_high( &eth->reset ); Delay_ms( 100 );
}

static uint8_t w5500_wait_socket_cmd( eth_transport_t *eth ) {
    uint16_t tries = 0;
    while ( w5500_read_reg( eth, W5500_Sn_CR, W5500_BSB_SOCKET0_REG( 0 ) ) ) {
        if ( eth->bus_error || ++tries > 200 ) return 0;
        Delay_ms( 1 );
    }
    return eth->bus_error ? 0 : 1;
}

static uint8_t w5500_open_socket0_macraw( eth_transport_t *eth ) {
    uint16_t tries = 0;

    w5500_write_reg( eth, W5500_Sn_MR, W5500_BSB_SOCKET0_REG( 0 ), W5500_Sn_MR_MACRAW | W5500_Sn_MR_MF );
    w5500_write_reg( eth, W5500_Sn_CR, W5500_BSB_SOCKET0_REG( 0 ), W5500_Sn_CR_OPEN );
    if ( !w5500_wait_socket_cmd( eth ) )
        return 0;

    while ( w5500_read_reg( eth, W5500_Sn_SR, W5500_BSB_SOCKET0_REG( 0 ) ) != W5500_SOCK_MACRAW ) {
        if ( eth->bus_error || ++tries > 500 ) return 0;
        Delay_ms( 1 );
    }
    return 1;
}

// Recovery from a corrupt RX header: closing the socket discards its buffers
static void w5500_reopen_socket0( eth_transport_t *eth ) {
    w5500_write_reg( eth, W5500_Sn_CR, W5500_BSB_SOCKET0_REG( 0 ), W5500_Sn_CR_CLOSE );
    ( void )w5500_wait_socket_cmd( eth );
    ( void )w5500_open_socket0_macraw( eth );
}

err_t w5500_init( eth_transport_t *eth ) {
    if ( !eth || !eth->driver_ctx ) return ETH_TRANSPORT_ERROR;

    eth->bus_error = 0;
    w5500_hw_reset( eth );

    W5500_CTX( eth )->hw_rev = w5500_read_reg( eth, W5500_VERSIONR, W5500_BSB_COMMON_REG );
    if ( W5500_CTX( eth )->hw_rev != W5500_VERSION )
        return ETH_TRANSPORT_ERROR;             // No W5500 responding

    w5500_write_reg( eth, W5500_MR, W5500_BSB_COMMON_REG, W5500_MR_PB );

    w5500_write_burst( eth, W5500_SHAR, W5500_BSB_COMMON_REG, eth->mac, 6 );
    w5500_write_burst( eth, W5500_SIPR, W5500_BSB_COMMON_REG, eth->ip, 4 );

    if ( !w5500_open_socket0_macraw( eth ) || eth->bus_error )
        return ETH_TRANSPORT_ERROR;

    return ETH_TRANSPORT_SUCCESS;
}

// Data transfer (MACRAW, socket 0)
uint16_t w5500_send_packet( eth_transport_t *eth, uint8_t *buf, uint16_t len ) {
    uint16_t wr_ptr;

    uint16_t tries = 0;

    if ( len > W5500_FRAME_SIZE ) return 0;
    eth->bus_error = 0;

    // Wait for enough TX buffer space, a previous frame may still be pending
    while ( w5500_read_reg16_stable( eth, W5500_Sn_TX_FSR ) < len ) {
        if ( eth->bus_error || ++tries > W5500_SEND_TRIES ) return 0;
        Delay_10us( );
    }

    wr_ptr = w5500_read_reg16( eth, W5500_Sn_TX_WR, W5500_BSB_SOCKET0_REG( 0 ) );
    w5500_write_burst( eth, wr_ptr, W5500_BSB_SOCKET0_TX( 0 ), buf, len );
    w5500_write_reg16( eth, W5500_Sn_TX_WR, W5500_BSB_SOCKET0_REG( 0 ), ( uint16_t )( wr_ptr + len ) );
    if ( eth->bus_error ) return 0;

    // Clear a stale SENDOK, then send and wait for this frame's SENDOK
    w5500_write_reg( eth, W5500_Sn_IR, W5500_BSB_SOCKET0_REG( 0 ), W5500_IR_SENDOK );
    w5500_write_reg( eth, W5500_Sn_CR, W5500_BSB_SOCKET0_REG( 0 ), W5500_Sn_CR_SEND );
    if ( !w5500_wait_socket_cmd( eth ) ) return 0;

    tries = 0;
    while ( !( w5500_read_reg( eth, W5500_Sn_IR, W5500_BSB_SOCKET0_REG( 0 ) ) & W5500_IR_SENDOK ) ) {
        if ( eth->bus_error || ++tries > W5500_SEND_TRIES ) return 0;
        Delay_10us( );
    }
    w5500_write_reg( eth, W5500_Sn_IR, W5500_BSB_SOCKET0_REG( 0 ), W5500_IR_SENDOK );

    return eth->bus_error ? 0 : len;
}

uint8_t w5500_packet_available( eth_transport_t *eth ) {
    uint16_t rsr;

    if ( !eth ) return 0;
    eth->bus_error = 0;

    rsr = w5500_read_reg16_stable( eth, W5500_Sn_RX_RSR );
    return ( rsr > 0 && !eth->bus_error ) ? 1 : 0;
}

uint16_t w5500_read_packet( eth_transport_t *eth, uint8_t *buf, uint16_t max_len ) {
    uint16_t rsr, rd_ptr, frame_len, data_len, copy_len;
    uint8_t hdr[ 2 ] = { 0, 0 };

    if ( !eth ) return 0;
    eth->bus_error = 0;

    rsr = w5500_read_reg16_stable( eth, W5500_Sn_RX_RSR );
    if ( !rsr || eth->bus_error ) return 0;

    rd_ptr = w5500_read_reg16( eth, W5500_Sn_RX_RD, W5500_BSB_SOCKET0_REG( 0 ) );

    // MACRAW frames are prefixed with a 2-byte length (including itself)
    w5500_read_burst( eth, rd_ptr, W5500_BSB_SOCKET0_RX( 0 ), hdr, W5500_RX_HDR_SIZE );
    if ( eth->bus_error ) return 0;             // Nothing consumed, retried on the next call
    frame_len = ( uint16_t )( ( ( uint16_t )hdr[ 0 ] << 8 ) | hdr[ 1 ] );

    // A corrupt length means the read position is lost, start over with empty buffers
    if ( frame_len < W5500_RX_FRAME_MIN || frame_len > W5500_RX_FRAME_MAX || frame_len > rsr ) {
        w5500_reopen_socket0( eth );
        return 0;
    }

    data_len = ( uint16_t )( frame_len - W5500_RX_HDR_SIZE );
    copy_len = ( data_len > max_len ) ? max_len : data_len;
    w5500_read_burst( eth, ( uint16_t )( rd_ptr + W5500_RX_HDR_SIZE ), W5500_BSB_SOCKET0_RX( 0 ), buf, copy_len );
    if ( eth->bus_error ) return 0;

    w5500_write_reg16( eth, W5500_Sn_RX_RD, W5500_BSB_SOCKET0_REG( 0 ), ( uint16_t )( rd_ptr + frame_len ) );
    w5500_write_reg( eth, W5500_Sn_CR, W5500_BSB_SOCKET0_REG( 0 ), W5500_Sn_CR_RECV );
    if ( !w5500_wait_socket_cmd( eth ) ) return 0;

    return copy_len;
}

// Link / identification
uint8_t w5500_get_link_status( eth_transport_t *eth ) {
    uint8_t phycfgr;

    if ( !eth ) return 0;

    if ( w5500_read_reg( eth, W5500_VERSIONR, W5500_BSB_COMMON_REG ) != 0x04 )
        return 0;                               // Chip not responding

    phycfgr = w5500_read_reg( eth, W5500_PHYCFGR, W5500_BSB_COMMON_REG );
    return ( phycfgr & W5500_PHYCFGR_LNK_MASK ) ? 1 : 0;
}

uint8_t w5500_get_rev( eth_transport_t *eth ) {
    if ( !eth || !eth->driver_ctx ) return 0;
    return W5500_CTX( eth )->hw_rev;
}

// Addressing
err_t w5500_set_mac( eth_transport_t *eth, uint8_t *mac ) {
    eth->bus_error = 0;
    w5500_write_burst( eth, W5500_SHAR, W5500_BSB_COMMON_REG, mac, 6 );
    return eth->bus_error ? ETH_TRANSPORT_ERROR : ETH_TRANSPORT_SUCCESS;
}

err_t w5500_set_ip( eth_transport_t *eth, uint8_t *ip ) {
    eth->bus_error = 0;
    w5500_write_burst( eth, W5500_SIPR, W5500_BSB_COMMON_REG, ip, 4 );
    return eth->bus_error ? ETH_TRANSPORT_ERROR : ETH_TRANSPORT_SUCCESS;
}

// Config / setup
void w5500_cfg_setup( w5500_cfg_t *cfg ) {
    eth_bus_spi_cfg_setup( &cfg->bus );
    eth_transport_cfg_setup( &cfg->eth );
}

err_t w5500_configure( eth_transport_t *eth, eth_bus_spi_t *bus, w5500_cfg_t *cfg ) {
    if ( !eth || !cfg ) return ETH_TRANSPORT_ERROR;
    if ( !eth->driver_ctx )
        eth->driver_ctx = &w5500_default_ctx;
    return eth_bus_spi_configure( eth, bus, &cfg->bus, &cfg->eth );
}

// ----------------------------------------------------------------------- END
