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
 * @file w6100.c
 * @brief SPI Ethernet WIZnet W6100 Driver.
 */

#include "w6100.h"
#include <delays.h>

#define W6100_IR_SENDOK      0x10

#define W6100_CTX( eth )     ( ( w6100_ctx_t * )( eth )->driver_ctx )

static w6100_ctx_t w6100_default_ctx;

static uint8_t   w6100_read_reg( eth_transport_t *eth, uint16_t addr, uint8_t bsb );
static void      w6100_write_reg( eth_transport_t *eth, uint16_t addr, uint8_t bsb, uint8_t val_in );
static uint16_t  w6100_read_reg16( eth_transport_t *eth, uint16_t addr, uint8_t bsb );
static void      w6100_write_reg16( eth_transport_t *eth, uint16_t addr, uint8_t bsb, uint16_t value );
static void      w6100_read_burst( eth_transport_t *eth, uint16_t addr, uint8_t bsb, uint8_t *buf, uint16_t len );
static void      w6100_write_burst( eth_transport_t *eth, uint16_t addr, uint8_t bsb, uint8_t *buf, uint16_t len );
static void      w6100_hw_reset( eth_transport_t *eth );
static void      w6100_wait_socket_cmd( eth_transport_t *eth );
static uint8_t   w6100_wait_sn_sr_macraw( eth_transport_t *eth );
static void      w6100_open_socket0_macraw( eth_transport_t *eth );

eth_transport_driver_t w6100_driver = {
    .init            = w6100_init,
    .send_packet     = w6100_send_packet,
    .read_packet     = w6100_read_packet,
    .available       = w6100_packet_available,
    .get_link_status = w6100_get_link_status,
    .set_mac         = w6100_set_mac,
    .set_ip          = w6100_set_ip
};

// Low-Level SPI Access
static uint8_t w6100_read_reg( eth_transport_t *eth, uint16_t addr, uint8_t bsb ) {
    uint8_t header[ 3 ];
    uint8_t val = 0;

    header[ 0 ] = ( uint8_t )( addr >> 8 );
    header[ 1 ] = ( uint8_t )( addr & 0xFF );
    header[ 2 ] = ( uint8_t )( bsb | W6100_RWB_READ | W6100_OM_VDM );

    ( void )eth_transport_bus_read( eth, header, 3, &val, 1 );

    return val;
}

static void w6100_write_reg( eth_transport_t *eth, uint16_t addr, uint8_t bsb, uint8_t val_in ) {
    uint8_t frame[ 4 ];

    frame[ 0 ] = ( uint8_t )( addr >> 8 );
    frame[ 1 ] = ( uint8_t )( addr & 0xFF );
    frame[ 2 ] = ( uint8_t )( bsb | W6100_RWB_WRITE | W6100_OM_VDM );
    frame[ 3 ] = val_in;

    ( void )eth_transport_bus_write( eth, frame, 4, NULL, 0 );
}

static uint16_t w6100_read_reg16( eth_transport_t *eth, uint16_t addr, uint8_t bsb ) {
    uint8_t buf[ 2 ];
    w6100_read_burst( eth, addr, bsb, buf, 2 );
    return ( uint16_t )( ( ( uint16_t )buf[ 0 ] << 8 ) | buf[ 1 ] );
}

static void w6100_write_reg16( eth_transport_t *eth, uint16_t addr, uint8_t bsb, uint16_t value ) {
    uint8_t buf[ 2 ];
    buf[ 0 ] = ( uint8_t )( value >> 8 );
    buf[ 1 ] = ( uint8_t )( value & 0xFF );
    w6100_write_burst( eth, addr, bsb, buf, 2 );
}

static void w6100_read_burst( eth_transport_t *eth, uint16_t addr, uint8_t bsb, uint8_t *buf, uint16_t len ) {
    uint8_t header[ 3 ];

    header[ 0 ] = ( uint8_t )( addr >> 8 );
    header[ 1 ] = ( uint8_t )( addr & 0xFF );
    header[ 2 ] = ( uint8_t )( bsb | W6100_RWB_READ | W6100_OM_VDM );

    ( void )eth_transport_bus_read( eth, header, 3, buf, len );
}

static void w6100_write_burst( eth_transport_t *eth, uint16_t addr, uint8_t bsb, uint8_t *buf, uint16_t len ) {
    uint8_t header[ 3 ];

    header[ 0 ] = ( uint8_t )( addr >> 8 );
    header[ 1 ] = ( uint8_t )( addr & 0xFF );
    header[ 2 ] = ( uint8_t )( bsb | W6100_RWB_WRITE | W6100_OM_VDM );

    ( void )eth_transport_bus_write( eth, header, 3, buf, len );
}

// Init
static void w6100_hw_reset( eth_transport_t *eth ) {
    digital_out_high( &eth->reset ); Delay_ms( 10 );
    digital_out_low( &eth->reset );  Delay_ms( 1 );
    digital_out_high( &eth->reset ); Delay_ms( 100 );
}

static void w6100_wait_socket_cmd( eth_transport_t *eth ) {
    uint16_t tries = 0;
    while ( w6100_read_reg( eth, W6100_Sn_CR, W6100_BSB_SOCKET0_REG( 0 ) ) ) {
        Delay_ms( 1 );
        if ( ++tries > 200 ) break;
    }
}

static uint8_t w6100_wait_sn_sr_macraw( eth_transport_t *eth ) {
    uint16_t tries = 0;

    do {
        if ( w6100_read_reg( eth, W6100_Sn_SR, W6100_BSB_SOCKET0_REG( 0 ) ) == W6100_SOCK_MACRAW )
            return 1;
        Delay_ms( 1 );
    } while ( ++tries < 500 );
    return 0;
}

static void w6100_open_socket0_macraw( eth_transport_t *eth ) {
    w6100_write_reg( eth, W6100_Sn_MR, W6100_BSB_SOCKET0_REG( 0 ), W6100_Sn_MR_MACRAW );
    w6100_write_reg( eth, W6100_Sn_CR, W6100_BSB_SOCKET0_REG( 0 ), W6100_Sn_CR_OPEN );
    ( void )w6100_wait_sn_sr_macraw( eth );
}

uint8_t w6100_reopen_socket0_macraw( eth_transport_t *eth ) {
    w6100_open_socket0_macraw( eth );
    return w6100_read_reg( eth, W6100_Sn_SR, W6100_BSB_SOCKET0_REG( 0 ) );
}

err_t w6100_init( eth_transport_t *eth ) {
    if ( !eth || !eth->driver_ctx ) return ETH_TRANSPORT_ERROR;

    w6100_hw_reset( eth );

    W6100_CTX( eth )->hw_rev = w6100_read_reg( eth, W6100_VERSIONR, W6100_BSB_COMMON_REG );

    w6100_write_reg( eth, W6100_NETLCKR, W6100_BSB_COMMON_REG, 0x3A );     // Unlock network registers
    w6100_set_mac( eth, eth->mac );
    w6100_set_ip( eth, eth->ip );

    w6100_write_reg( eth, W6100_NET4MR, W6100_BSB_COMMON_REG,
                     W6100_NET4MR_PB | W6100_NET4MR_RSTB );

    w6100_open_socket0_macraw( eth );

    w6100_write_reg( eth, W6100_NETLCKR, W6100_BSB_COMMON_REG, 0x00 );

    return ETH_TRANSPORT_SUCCESS;
}

// Data transfer (MACRAW, socket 0)
uint16_t w6100_send_packet( eth_transport_t *eth, uint8_t *buf, uint16_t len ) {
    uint16_t wr_ptr;

    if ( len > W6100_FRAME_SIZE ) return 0;

    wr_ptr = w6100_read_reg16( eth, W6100_Sn_TX_WR, W6100_BSB_SOCKET0_REG( 0 ) );
    w6100_write_burst( eth, wr_ptr, W6100_BSB_SOCKET0_TX( 0 ), buf, len );
    w6100_write_reg16( eth, W6100_Sn_TX_WR, W6100_BSB_SOCKET0_REG( 0 ), ( uint16_t )( wr_ptr + len ) );

    w6100_write_reg( eth, W6100_Sn_CR, W6100_BSB_SOCKET0_REG( 0 ), W6100_Sn_CR_SEND );
    w6100_wait_socket_cmd( eth );

    w6100_write_reg( eth, W6100_Sn_IR, W6100_BSB_SOCKET0_REG( 0 ), W6100_IR_SENDOK );

    return len;
}

uint8_t w6100_packet_available( eth_transport_t *eth ) {
    uint16_t rsr;

    if ( !eth ) return 0;

    rsr = w6100_read_reg16( eth, W6100_Sn_RX_RSR, W6100_BSB_SOCKET0_REG( 0 ) );
    return ( rsr > 0 ) ? 1 : 0;
}

uint16_t w6100_read_packet( eth_transport_t *eth, uint8_t *buf, uint16_t max_len ) {
    uint16_t rd_ptr, frame_len, data_len, copy_len;
    uint8_t hdr[ 2 ];

    if ( !w6100_packet_available( eth ) ) return 0;

    rd_ptr = w6100_read_reg16( eth, W6100_Sn_RX_RD, W6100_BSB_SOCKET0_REG( 0 ) );

    // MACRAW frames are prefixed with a 2-byte length (including itself)
    w6100_read_burst( eth, rd_ptr, W6100_BSB_SOCKET0_RX( 0 ), hdr, 2 );
    frame_len = ( uint16_t )( ( ( uint16_t )hdr[ 0 ] << 8 ) | hdr[ 1 ] );

    if ( frame_len < 2 ) {
        w6100_write_reg16( eth, W6100_Sn_RX_RD, W6100_BSB_SOCKET0_REG( 0 ), ( uint16_t )( rd_ptr + 2 ) );
        w6100_write_reg( eth, W6100_Sn_CR, W6100_BSB_SOCKET0_REG( 0 ), W6100_Sn_CR_RECV );
        return 0;
    }

    data_len = ( uint16_t )( frame_len - 2 );
    copy_len = ( data_len > max_len ) ? max_len : data_len;
    w6100_read_burst( eth, ( uint16_t )( rd_ptr + 2 ), W6100_BSB_SOCKET0_RX( 0 ), buf, copy_len );

    w6100_write_reg16( eth, W6100_Sn_RX_RD, W6100_BSB_SOCKET0_REG( 0 ), ( uint16_t )( rd_ptr + frame_len ) );
    w6100_write_reg( eth, W6100_Sn_CR, W6100_BSB_SOCKET0_REG( 0 ), W6100_Sn_CR_RECV );

    return copy_len;
}

// Link / identification
uint8_t w6100_get_link_status( eth_transport_t *eth ) {
    if ( !eth ) return 0;
    return ( w6100_read_reg( eth, W6100_PHYSR, W6100_BSB_COMMON_REG ) & W6100_PHYSR_LNK_MASK ) ? 1 : 0;
}

uint8_t w6100_get_rev( eth_transport_t *eth ) {
    if ( !eth || !eth->driver_ctx ) return 0;
    return W6100_CTX( eth )->hw_rev;
}

// Addressing
err_t w6100_set_mac( eth_transport_t *eth, uint8_t *mac ) {
    w6100_write_burst( eth, W6100_SHAR, W6100_BSB_COMMON_REG, mac, 6 );
    return ETH_TRANSPORT_SUCCESS;
}

err_t w6100_set_ip( eth_transport_t *eth, uint8_t *ip ) {
    w6100_write_burst( eth, W6100_SIPR, W6100_BSB_COMMON_REG, ip, 4 );
    return ETH_TRANSPORT_SUCCESS;
}

// Config / setup
void w6100_cfg_setup( w6100_cfg_t *cfg ) {
    eth_bus_spi_cfg_setup( &cfg->bus );
    eth_transport_cfg_setup( &cfg->eth );
}

err_t w6100_configure( eth_transport_t *eth, eth_bus_spi_t *bus, w6100_cfg_t *cfg ) {
    if ( !eth || !cfg ) return ETH_TRANSPORT_ERROR;
    if ( !eth->driver_ctx )
        eth->driver_ctx = &w6100_default_ctx;
    return eth_bus_spi_configure( eth, bus, &cfg->bus, &cfg->eth );
}

// ----------------------------------------------------------------------- END
