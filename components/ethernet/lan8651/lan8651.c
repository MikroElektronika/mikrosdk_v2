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
 * @file lan8651.c
 * @brief SPI Ethernet Microchip LAN8651 10BASE-T1S MAC-PHY Driver.
 */

#include "lan8651.h"
#include <delays.h>
#include <string.h>

#define LAN8651_RESET_TIMEOUT_MS    1000
#define LAN8651_TX_CREDIT_TRIES     1000
#define LAN8651_RX_MAX_CHUNKS       ( 2 * ( ( LAN8651_FRAME_SIZE + LAN8651_FCS_SIZE ) / LAN8651_CHUNK_PAYLOAD_SIZE + 1 ) )

#define LAN8651_CTX( eth )          ( ( lan8651_ctx_t * )( eth )->driver_ctx )

static lan8651_ctx_t lan8651_default_ctx;

// TC6 data chunk buffers, only used within a single call so shared by all devices
static uint8_t lan8651_chunk_tx[ LAN8651_CHUNK_SIZE ];
static uint8_t lan8651_chunk_rx[ LAN8651_CHUNK_SIZE ];

// LAN865x Rev.B0/B1 configuration from AN1760 (written to MMS 4)
static const uint16_t lan8651_fixup_regs[ 17 ] = {
    0x00D0, 0x00E0, 0x00E9, 0x00F5, 0x00F4, 0x00F8, 0x00F9, 0x0081,
    0x0091, 0x0043, 0x0044, 0x0045, 0x0053, 0x0054, 0x0055, 0x0040,
    0x0050
};
static const uint16_t lan8651_fixup_vals[ 17 ] = {
    0x3F31, 0xC000, 0x9E50, 0x1CF8, 0xC020, 0xB900, 0x4E53, 0x0080,
    0x9660, 0x00FF, 0xFFFF, 0x0000, 0x00FF, 0xFFFF, 0x0000, 0x0002,
    0x0002
};
static const uint16_t lan8651_sqi_regs[ 12 ] = {
    0x00B0, 0x00B1, 0x00B2, 0x00B3, 0x00B4, 0x00B5,
    0x00B6, 0x00B7, 0x00B8, 0x00B9, 0x00BA, 0x00BB
};
static const uint16_t lan8651_sqi_vals[ 12 ] = {
    0x0103, 0x0910, 0x1D26, 0x002A, 0x0103, 0x070D,
    0x1720, 0x0027, 0x0509, 0x0E13, 0x1C25, 0x002B
};

static uint32_t lan8651_add_parity( uint32_t word );
static void     lan8651_put_be32( uint8_t *buf, uint32_t val );
static uint32_t lan8651_get_be32( uint8_t *buf );
static uint8_t  lan8651_ctrl( eth_transport_t *eth, uint8_t write, uint8_t mms, uint16_t addr, uint32_t *val );
static uint32_t lan8651_read_reg( eth_transport_t *eth, uint8_t mms, uint16_t addr );
static void     lan8651_write_reg( eth_transport_t *eth, uint8_t mms, uint16_t addr, uint32_t val );
static void     lan8651_modify_reg( eth_transport_t *eth, uint8_t mms, uint16_t addr, uint32_t mask, uint32_t val );
static int8_t   lan8651_indirect_read( eth_transport_t *eth, uint16_t addr );
static void     lan8651_apply_config_fixups( eth_transport_t *eth );
static void     lan8651_clear_status( eth_transport_t *eth );
static uint8_t  lan8651_wait_reset_complete( eth_transport_t *eth );
static void     lan8651_hw_reset( eth_transport_t *eth );
static uint8_t  lan8651_rx_append( lan8651_ctx_t *ctx, uint8_t *data_buf, uint16_t len );
static void     lan8651_rx_finish( lan8651_ctx_t *ctx );
static void     lan8651_process_rx_chunk( lan8651_ctx_t *ctx, uint32_t footer );
static uint8_t  lan8651_data_chunk( eth_transport_t *eth, uint8_t *tx_data, uint8_t tx_len, uint8_t start, uint8_t end );

eth_transport_driver_t lan8651_driver = {
    .init            = lan8651_init,
    .send_packet     = lan8651_send_packet,
    .read_packet     = lan8651_read_packet,
    .available       = lan8651_packet_available,
    .get_link_status = lan8651_get_link_status,
    .set_mac         = lan8651_set_mac
};

// Helpers (TC6 headers are 32-bit big-endian words with odd parity in bit 0)
static uint32_t lan8651_add_parity( uint32_t word ) {
    uint32_t p = word;
    p ^= p >> 16;
    p ^= p >> 8;
    p ^= p >> 4;
    p ^= p >> 2;
    p ^= p >> 1;
    if ( !( p & 1 ) )       // even number of ones -> set P to make it odd
        word |= 1;
    return word;
}

static void lan8651_put_be32( uint8_t *buf, uint32_t val ) {
    buf[ 0 ] = ( uint8_t )( val >> 24 );
    buf[ 1 ] = ( uint8_t )( val >> 16 );
    buf[ 2 ] = ( uint8_t )( val >> 8 );
    buf[ 3 ] = ( uint8_t )( val & 0xFF );
}

static uint32_t lan8651_get_be32( uint8_t *buf ) {
    return ( ( uint32_t )buf[ 0 ] << 24 ) | ( ( uint32_t )buf[ 1 ] << 16 ) |
           ( ( uint32_t )buf[ 2 ] << 8 )  | buf[ 3 ];
}

// Low-level SPI access (TC6 control transaction, one register)
static uint8_t lan8651_ctrl( eth_transport_t *eth, uint8_t write, uint8_t mms, uint16_t addr, uint32_t *val ) {
    uint8_t tx_buf[ 12 ];
    uint8_t rx_buf[ 12 ];
    uint32_t header;

    header = ( write ? LAN8651_CTRL_HDR_WNR : 0 ) |
             ( ( uint32_t )( mms & 0x0F ) << LAN8651_CTRL_HDR_MMS_SHIFT ) |
             ( ( uint32_t )addr << LAN8651_CTRL_HDR_ADDR_SHIFT );   // LEN = 0 -> one register
    header = lan8651_add_parity( header );

    memset( tx_buf, 0, sizeof( tx_buf ) );
    lan8651_put_be32( &tx_buf[ 0 ], header );
    if ( write )
        lan8651_put_be32( &tx_buf[ 4 ], *val );

    if ( eth_transport_bus_transfer( eth, tx_buf, rx_buf, sizeof( tx_buf ) ) != ETH_TRANSPORT_SUCCESS )
        return 0;                       // bus error or bus without full duplex support

    // Reply is delayed by one word: [ ignored ][ echoed header ][ register value ]
    if ( lan8651_get_be32( &rx_buf[ 4 ] ) != header )
        return 0;
    if ( !write )
        *val = lan8651_get_be32( &rx_buf[ 8 ] );
    return 1;
}

static uint32_t lan8651_read_reg( eth_transport_t *eth, uint8_t mms, uint16_t addr ) {
    uint32_t val = 0;
    ( void )lan8651_ctrl( eth, 0, mms, addr, &val );
    return val;
}

static void lan8651_write_reg( eth_transport_t *eth, uint8_t mms, uint16_t addr, uint32_t val ) {
    ( void )lan8651_ctrl( eth, 1, mms, addr, &val );
}

static void lan8651_modify_reg( eth_transport_t *eth, uint8_t mms, uint16_t addr, uint32_t mask, uint32_t val ) {
    uint32_t reg = lan8651_read_reg( eth, mms, addr );
    lan8651_write_reg( eth, mms, addr, ( reg & ~mask ) | ( val & mask ) );
}

// AN1760 'indirect read', returns the 5-bit signed trim value
static int8_t lan8651_indirect_read( eth_transport_t *eth, uint16_t addr ) {
    uint8_t val;

    lan8651_write_reg( eth, LAN8651_MMS_PHY_VS_PLCA, LAN8651_VS_CFGPARAM_ADDR, addr );
    lan8651_write_reg( eth, LAN8651_MMS_PHY_VS_PLCA, LAN8651_VS_CFGPARAM_CTRL, LAN8651_VS_CFGPARAM_READ );
    val = ( uint8_t )( lan8651_read_reg( eth, LAN8651_MMS_PHY_VS_PLCA, LAN8651_VS_CFGPARAM_DATA ) & 0x1F );

    if ( val & 0x10 )       // sign extend
        val |= 0xE0;
    return ( int8_t )val;
}

static void lan8651_apply_config_fixups( eth_transport_t *eth ) {
    int8_t offset1 = lan8651_indirect_read( eth, 0x0004 );
    int8_t offset2 = lan8651_indirect_read( eth, 0x0008 );
    uint8_t i;

    for ( i = 0; i < 17; i++ ) {
        lan8651_write_reg( eth, LAN8651_MMS_PHY_VS_PLCA, lan8651_fixup_regs[ i ], lan8651_fixup_vals[ i ] );
        if ( i == 1 ) {     // trimmed parameters go right after 0x00E0
            lan8651_write_reg( eth, LAN8651_MMS_PHY_VS_PLCA, 0x0084,
                               ( ( uint32_t )( ( 9 + offset1 ) & 0x3F ) << 10 ) |
                               ( ( uint32_t )( ( 14 + offset1 ) & 0x3F ) << 4 ) | 0x03 );
            lan8651_write_reg( eth, LAN8651_MMS_PHY_VS_PLCA, 0x008A,
                               ( uint32_t )( ( 40 + offset2 ) & 0x3F ) << 10 );
        }
    }

    lan8651_write_reg( eth, LAN8651_MMS_PHY_VS_PLCA, 0x00AD,
                       ( ( uint32_t )( ( 5 + offset1 ) & 0x3F ) << 8 ) | ( ( 9 + offset1 ) & 0x3F ) );
    lan8651_write_reg( eth, LAN8651_MMS_PHY_VS_PLCA, 0x00AE,
                       ( ( uint32_t )( ( 9 + offset1 ) & 0x3F ) << 8 ) | ( ( 14 + offset1 ) & 0x3F ) );
    lan8651_write_reg( eth, LAN8651_MMS_PHY_VS_PLCA, 0x00AF,
                       ( ( uint32_t )( ( 17 + offset1 ) & 0x3F ) << 8 ) | ( ( 22 + offset1 ) & 0x3F ) );

    for ( i = 0; i < 12; i++ )
        lan8651_write_reg( eth, LAN8651_MMS_PHY_VS_PLCA, lan8651_sqi_regs[ i ], lan8651_sqi_vals[ i ] );
}

static void lan8651_clear_status( eth_transport_t *eth ) {
    uint32_t status = lan8651_read_reg( eth, LAN8651_MMS_OA, LAN8651_OA_STATUS0 );

    if ( !status )
        return;
    lan8651_write_reg( eth, LAN8651_MMS_OA, LAN8651_OA_STATUS0, status );   // write 1 to clear

    if ( status & LAN8651_OA_STATUS0_RXBOE )        // RX overflow, partial frame is lost
        LAN8651_CTX( eth )->rx_in_progress = 0;
}

// Init
static uint8_t lan8651_wait_reset_complete( eth_transport_t *eth ) {
    uint16_t tries = 0;
    uint32_t status = 0;

    while ( !lan8651_ctrl( eth, 0, LAN8651_MMS_OA, LAN8651_OA_STATUS0, &status ) ||
            !( status & LAN8651_OA_STATUS0_RESETC ) ) {
        Delay_ms( 1 );
        if ( ++tries > LAN8651_RESET_TIMEOUT_MS ) return 0;
    }

    lan8651_write_reg( eth, LAN8651_MMS_OA, LAN8651_OA_STATUS0, status );
    return 1;
}

static void lan8651_hw_reset( eth_transport_t *eth ) {
    // RST also drives the click CS multiplexer, it must stay high for SPI access
    digital_out_high( &eth->reset ); Delay_ms( 10 );
    digital_out_low( &eth->reset );  Delay_ms( 10 );
    digital_out_high( &eth->reset ); Delay_ms( 50 );
}

err_t lan8651_init( eth_transport_t *eth ) {
    lan8651_ctx_t *ctx;
    uint32_t bufsts;

    if ( !eth || !eth->driver_ctx ) return ETH_TRANSPORT_ERROR;
    if ( !eth->bus_ops || !eth->bus_ops->transfer )
        return ETH_TRANSPORT_ERROR;     // TC6 needs a full duplex bus
    ctx = LAN8651_CTX( eth );

    ctx->rx_len = 0;
    ctx->rx_in_progress = 0;
    ctx->rx_ready = 0;

    lan8651_hw_reset( eth );
    lan8651_wait_reset_complete( eth );

    lan8651_write_reg( eth, LAN8651_MMS_OA, LAN8651_OA_RESET, LAN8651_OA_RESET_SWRESET );
    lan8651_wait_reset_complete( eth );

    ctx->phy_id = lan8651_read_reg( eth, LAN8651_MMS_OA, LAN8651_OA_PHYID );

    lan8651_apply_config_fixups( eth );

    // Errata s3: only one receive frame per chunk, starting at the first payload word
    lan8651_modify_reg( eth, LAN8651_MMS_OA, LAN8651_OA_CONFIG0,
                        LAN8651_OA_CONFIG0_ZARFE, LAN8651_OA_CONFIG0_ZARFE );

    // 25 MHz internal clock -> 40 ns timer increment (AN1760)
    lan8651_write_reg( eth, LAN8651_MMS_MAC, LAN8651_MAC_TISUBN, LAN8651_MAC_TI_40NS );

    if ( ctx->plca_enable ) {
        lan8651_write_reg( eth, LAN8651_MMS_PHY_VS_PLCA, LAN8651_PLCA_CTRL1,
                           ( ( uint32_t )ctx->plca_node_count << 8 ) | ctx->plca_node_id );
        lan8651_write_reg( eth, LAN8651_MMS_PHY_VS_PLCA, LAN8651_PLCA_CTRL0, LAN8651_PLCA_CTRL0_EN );
        // Collision detection is recommended off in PLCA mode (AN1760)
        lan8651_modify_reg( eth, LAN8651_MMS_PHY_VS_PLCA, LAN8651_VS_CDCTL0, LAN8651_VS_CDCTL0_CDEN, 0 );
    }

    lan8651_set_mac( eth, eth->mac );

    lan8651_modify_reg( eth, LAN8651_MMS_MAC, LAN8651_MAC_NCR,
                        LAN8651_MAC_NCR_TXEN | LAN8651_MAC_NCR_RXEN,
                        LAN8651_MAC_NCR_TXEN | LAN8651_MAC_NCR_RXEN );

    // Configuration done, enable data transfers
    lan8651_modify_reg( eth, LAN8651_MMS_OA, LAN8651_OA_CONFIG0,
                        LAN8651_OA_CONFIG0_SYNC, LAN8651_OA_CONFIG0_SYNC );
    lan8651_clear_status( eth );

    bufsts = lan8651_read_reg( eth, LAN8651_MMS_OA, LAN8651_OA_BUFSTS );
    ctx->tx_credits = ( uint8_t )( ( bufsts >> 8 ) & 0xFF );
    ctx->rx_chunks  = ( uint8_t )( bufsts & 0xFF );

    // IRQ_N stays asserted after reset until the first data chunk is exchanged
    ( void )lan8651_data_chunk( eth, NULL, 0, 0, 0 );

    return ETH_TRANSPORT_SUCCESS;
}

// Data transfer (TC6 data chunks)
static uint8_t lan8651_rx_append( lan8651_ctx_t *ctx, uint8_t *data_buf, uint16_t len ) {
    if ( ctx->rx_len + len > sizeof( ctx->rx_frame ) ) {
        ctx->rx_in_progress = 0;        // oversized frame, drop it
        return 0;
    }
    memcpy( &ctx->rx_frame[ ctx->rx_len ], data_buf, len );
    ctx->rx_len += len;
    return 1;
}

static void lan8651_rx_finish( lan8651_ctx_t *ctx ) {
    ctx->rx_in_progress = 0;
    if ( ctx->rx_len <= LAN8651_FCS_SIZE )
        return;
    ctx->rx_len -= LAN8651_FCS_SIZE;    // MAC-PHY delivers frames with FCS attached
    ctx->rx_ready = 1;
}

static void lan8651_process_rx_chunk( lan8651_ctx_t *ctx, uint32_t footer ) {
    uint8_t sv  = ( footer & LAN8651_DATA_FTR_SV ) ? 1 : 0;
    uint8_t ev  = ( footer & LAN8651_DATA_FTR_EV ) ? 1 : 0;
    uint8_t swo = ( uint8_t )( ( ( footer >> LAN8651_DATA_FTR_SWO_SHIFT ) & 0x0F ) * 4 );
    uint8_t ebo = ( uint8_t )( ( footer >> LAN8651_DATA_FTR_EBO_SHIFT ) & 0x3F );

    if ( !( footer & LAN8651_DATA_FTR_DV ) || ctx->rx_ready )
        return;

    // End of a frame started in an earlier chunk (possibly followed by a new start)
    if ( ev && ( !sv || swo > ebo ) ) {
        if ( ctx->rx_in_progress && lan8651_rx_append( ctx, lan8651_chunk_rx, ( uint16_t )ebo + 1 ) )
            lan8651_rx_finish( ctx );
        ctx->rx_in_progress = 0;
        if ( !sv || ctx->rx_ready )
            return;
        ev = 0;
    }

    if ( sv ) {
        ctx->rx_len = 0;
        ctx->rx_in_progress = 1;
        if ( ev ) {
            if ( lan8651_rx_append( ctx, &lan8651_chunk_rx[ swo ], ( uint16_t )( ebo + 1 - swo ) ) )
                lan8651_rx_finish( ctx );
        } else {
            lan8651_rx_append( ctx, &lan8651_chunk_rx[ swo ], ( uint16_t )( LAN8651_CHUNK_PAYLOAD_SIZE - swo ) );
        }
    } else if ( ctx->rx_in_progress ) {
        lan8651_rx_append( ctx, lan8651_chunk_rx, LAN8651_CHUNK_PAYLOAD_SIZE );
    }
}

// Exchanges one data chunk; tx_data == NULL sends an empty chunk (RX/status poll)
static uint8_t lan8651_data_chunk( eth_transport_t *eth, uint8_t *tx_data, uint8_t tx_len, uint8_t start, uint8_t end ) {
    lan8651_ctx_t *ctx = LAN8651_CTX( eth );
    uint32_t header = LAN8651_DATA_HDR_DNC;
    uint32_t footer;

    memset( lan8651_chunk_tx, 0, sizeof( lan8651_chunk_tx ) );
    if ( tx_data ) {
        header |= LAN8651_DATA_HDR_DV;
        if ( start )
            header |= LAN8651_DATA_HDR_SV;
        if ( end )
            header |= LAN8651_DATA_HDR_EV | ( ( uint32_t )( tx_len - 1 ) << LAN8651_DATA_HDR_EBO_SHIFT );
        memcpy( &lan8651_chunk_tx[ 4 ], tx_data, tx_len );
    }
    if ( ctx->rx_ready )        // keep RX data in the MAC-PHY until the pending frame is read
        header |= LAN8651_DATA_HDR_NORX;
    lan8651_put_be32( lan8651_chunk_tx, lan8651_add_parity( header ) );

    if ( eth_transport_bus_transfer( eth, lan8651_chunk_tx, lan8651_chunk_rx, LAN8651_CHUNK_SIZE ) != ETH_TRANSPORT_SUCCESS ) {
        ctx->rx_in_progress = 0;
        return 0;
    }

    // TX header goes first, RX footer comes last: [ 64 B payload ][ footer ]
    footer = lan8651_get_be32( &lan8651_chunk_rx[ LAN8651_CHUNK_PAYLOAD_SIZE ] );
    if ( !( footer & LAN8651_DATA_FTR_SYNC ) || ( footer & LAN8651_DATA_FTR_HDRB ) ) {
        ctx->rx_in_progress = 0;
        return 0;
    }

    ctx->tx_credits = ( uint8_t )( ( footer >> LAN8651_DATA_FTR_TXC_SHIFT ) & 0x1F );
    ctx->rx_chunks  = ( uint8_t )( ( footer >> LAN8651_DATA_FTR_RCA_SHIFT ) & 0x1F );

    if ( footer & LAN8651_DATA_FTR_EXST )
        lan8651_clear_status( eth );

    lan8651_process_rx_chunk( ctx, footer );
    return 1;
}

uint16_t lan8651_send_packet( eth_transport_t *eth, uint8_t *buf, uint16_t len ) {
    uint8_t  pad[ LAN8651_MIN_FRAME_SIZE ];
    uint16_t offset = 0;
    uint16_t tries;
    uint8_t  chunk_len;

    if ( !buf || !len || len > LAN8651_FRAME_SIZE )
        return 0;

    // Pad runt frames to the Ethernet minimum (FCS is appended by the MAC)
    if ( len < LAN8651_MIN_FRAME_SIZE ) {
        memset( pad, 0, sizeof( pad ) );
        memcpy( pad, buf, len );
        buf = pad;
        len = LAN8651_MIN_FRAME_SIZE;
    }

    while ( offset < len ) {
        tries = 0;
        while ( !LAN8651_CTX( eth )->tx_credits ) {
            if ( !lan8651_data_chunk( eth, NULL, 0, 0, 0 ) || ++tries > LAN8651_TX_CREDIT_TRIES )
                return 0;
        }

        chunk_len = ( len - offset > LAN8651_CHUNK_PAYLOAD_SIZE ) ? LAN8651_CHUNK_PAYLOAD_SIZE
                                                                  : ( uint8_t )( len - offset );
        if ( !lan8651_data_chunk( eth, &buf[ offset ], chunk_len, offset == 0, offset + chunk_len >= len ) )
            return 0;
        offset += chunk_len;
    }

    return len;
}

uint8_t lan8651_packet_available( eth_transport_t *eth ) {
    lan8651_ctx_t *ctx;

    if ( !eth ) return 0;
    ctx = LAN8651_CTX( eth );

    if ( ctx->rx_ready )
        return 1;

    ctx->rx_chunks = ( uint8_t )( lan8651_read_reg( eth, LAN8651_MMS_OA, LAN8651_OA_BUFSTS ) & 0xFF );
    return ( ctx->rx_chunks > 0 ) ? 1 : 0;
}

uint16_t lan8651_read_packet( eth_transport_t *eth, uint8_t *buf, uint16_t max_len ) {
    lan8651_ctx_t *ctx = LAN8651_CTX( eth );
    uint16_t chunks = 0;
    uint16_t copy_len;

    if ( !ctx->rx_ready ) {
        if ( !lan8651_packet_available( eth ) )
            return 0;

        while ( !ctx->rx_ready && chunks++ < LAN8651_RX_MAX_CHUNKS ) {
            if ( !lan8651_data_chunk( eth, NULL, 0, 0, 0 ) )
                break;
            if ( !ctx->rx_chunks && !ctx->rx_in_progress )
                break;
        }

        if ( !ctx->rx_ready )
            return 0;
    }

    copy_len = ( ctx->rx_len > max_len ) ? max_len : ctx->rx_len;
    memcpy( buf, ctx->rx_frame, copy_len );
    ctx->rx_ready = 0;

    return copy_len;
}

// Link / identification
uint8_t lan8651_get_link_status( eth_transport_t *eth ) {
    uint32_t val = 0;

    if ( !eth || !eth->driver_ctx ) return 0;

    if ( LAN8651_CTX( eth )->plca_enable )
        return ( lan8651_read_reg( eth, LAN8651_MMS_PHY_VS_PLCA, LAN8651_PLCA_STS ) &
                 LAN8651_PLCA_STS_PST ) ? 1 : 0;

    // CSMA/CD: no link indication on 10BASE-T1S, report whether the MAC-PHY is alive and configured
    if ( !lan8651_ctrl( eth, 0, LAN8651_MMS_OA, LAN8651_OA_CONFIG0, &val ) )
        return 0;
    return ( val & LAN8651_OA_CONFIG0_SYNC ) ? 1 : 0;
}

uint8_t lan8651_get_rev( eth_transport_t *eth ) {
    return ( uint8_t )( lan8651_get_phy_id( eth ) & 0xFF );
}

uint32_t lan8651_get_phy_id( eth_transport_t *eth ) {
    if ( !eth || !eth->driver_ctx ) return 0;
    return LAN8651_CTX( eth )->phy_id;
}

// Addressing
err_t lan8651_set_mac( eth_transport_t *eth, uint8_t *mac ) {
    // Bottom half first: writing it disables the filter until the top half is written
    lan8651_write_reg( eth, LAN8651_MMS_MAC, LAN8651_MAC_SAB1,
                       ( uint32_t )mac[ 0 ] | ( ( uint32_t )mac[ 1 ] << 8 ) |
                       ( ( uint32_t )mac[ 2 ] << 16 ) | ( ( uint32_t )mac[ 3 ] << 24 ) );
    lan8651_write_reg( eth, LAN8651_MMS_MAC, LAN8651_MAC_SAT1,
                       ( uint32_t )mac[ 4 ] | ( ( uint32_t )mac[ 5 ] << 8 ) );
    return ETH_TRANSPORT_SUCCESS;
}

// Config / setup
void lan8651_cfg_setup( lan8651_cfg_t *cfg ) {
    eth_bus_spi_cfg_setup( &cfg->bus );
    eth_transport_cfg_setup( &cfg->eth );

    cfg->plca_enable     = 0;
    cfg->plca_node_id    = 0;
    cfg->plca_node_count = 8;
}

err_t lan8651_configure( eth_transport_t *eth, eth_bus_spi_t *bus, lan8651_cfg_t *cfg ) {
    lan8651_ctx_t *ctx;

    if ( !eth || !cfg ) return ETH_TRANSPORT_ERROR;

    cfg->eth.full_duplex = 0;   // 10BASE-T1S is half duplex only

    if ( !eth->driver_ctx )
        eth->driver_ctx = &lan8651_default_ctx;

    if ( eth_bus_spi_configure( eth, bus, &cfg->bus, &cfg->eth ) != ETH_TRANSPORT_SUCCESS )
        return ETH_TRANSPORT_ERROR;

    // RST also drives the click CS multiplexer, it must stay high for SPI access
    digital_out_high( &eth->reset );

    ctx = LAN8651_CTX( eth );
    ctx->plca_enable     = cfg->plca_enable;
    ctx->plca_node_id    = cfg->plca_node_id;
    ctx->plca_node_count = cfg->plca_node_count;

    return ETH_TRANSPORT_SUCCESS;
}

// ----------------------------------------------------------------------- END
