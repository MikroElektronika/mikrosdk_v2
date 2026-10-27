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
 * @file enc28j60.c
 * @brief SPI Ethernet Microchip ENC28J60 Driver.
 */

#include "enc28j60.h"
#include <delays.h>
#include <string.h>

#define PKTDEC      0x40
#define CSUMEN      0x10
#define DMAST       0x20

#define MARXEN      0x01
#define ECON1_RXEN  0x04
#define AUTOINC     0x80
#define TXRTS       0x08
#define TXRST       0x80
#define TXERIF      0x02
#define TXIF        0x08

#define MACON1_MARXEN ( 0x1 )
#define MACON1_RXPAUS ( 0x4 )
#define MACON1_TXPAUS ( 0x8 )
#define MACON3_PADCFG_MASK ( 0xE0 )
#define MACON3_PADCFG_SET ( 0x20 )
#define MACON3_TXCRCEN ( 0x10 )
#define MACON3_FULDPX ( 0x1 )
#define MACON4_DEFER ( 0x40 )

#define PHSTAT2_LSTAT_HIGH_MASK 0x04
#define MISTAT_BUSY 0x01
#define ENC28J60_MIIM_TIMEOUT_MS 100

#define ENC28J60_CTX( eth )     ( ( enc28j60_ctx_t * )( eth )->driver_ctx )

static enc28j60_ctx_t enc28j60_default_ctx;

static void    enc28j60_select_bank( eth_transport_t *eth, uint8_t bank );
static uint8_t enc28j60_read_reg( eth_transport_t *eth, uint8_t reg );
static void    enc28j60_read_mem( eth_transport_t *eth, uint8_t *buf, uint16_t len );
static void    enc28j60_write_reg( eth_transport_t *eth, uint8_t reg, uint8_t value );
static void    enc28j60_write_mem( eth_transport_t *eth, uint8_t *buf, uint16_t len );
static void    enc28j60_set_bit_reg( eth_transport_t *eth, uint8_t reg, uint8_t mask );
static void    enc28j60_clear_bit_reg( eth_transport_t *eth, uint8_t reg, uint8_t mask );
static void    enc28j60_hw_reset( eth_transport_t *eth );
static void    enc28j60_sw_reset( eth_transport_t *eth );
static void    enc28j60_wait_clk_ready( eth_transport_t *eth );
static void    enc28j60_init_rx_buffer( eth_transport_t *eth );
static void    enc28j60_init_tx_buffer( eth_transport_t *eth );
static void    enc28j60_init_rx_filter( eth_transport_t *eth );
static void    enc28j60_init_mac( eth_transport_t *eth );
static void    enc28j60_init_clock_output( eth_transport_t *eth );
static void    enc28j60_set_write_ptr( eth_transport_t *eth, uint16_t addr );

eth_transport_driver_t enc28j60_driver = {
    .init            = enc28j60_init,
    .send_packet     = enc28j60_send_packet,
    .read_packet     = enc28j60_read_packet,
    .available       = enc28j60_packet_available,
    .get_link_status = enc28j60_get_link_status,
    .set_mac         = enc28j60_set_mac
};

// Low-level SPI access
static void enc28j60_select_bank( eth_transport_t *eth, uint8_t bank ) {
    enc28j60_ctx_t *ctx = ENC28J60_CTX( eth );
    uint8_t cmd[ 2 ];

    if ( bank > 3 || bank == ctx->current_bank )
        return;

    cmd[ 0 ] = ( uint8_t )( ENC28J60_BFC_CMD | ( ECON1 & 0x1F ) );
    cmd[ 1 ] = 0x03;

    ( void )eth_transport_bus_write( eth, cmd, 2, NULL, 0 );

    cmd[ 0 ] = ( uint8_t )( ENC28J60_BFS_CMD | ( ECON1 & 0x1F ) );
    cmd[ 1 ] = ( uint8_t )( bank & 0x03 );

    ( void )eth_transport_bus_write( eth, cmd, 2, NULL, 0 );

    ctx->current_bank = bank;
}

static uint8_t enc28j60_read_reg( eth_transport_t *eth, uint8_t reg ) {     // RCR - Read Control Register
    uint8_t cmd = ENC28J60_RCR_CMD | ( reg & 0x1F );
    uint8_t buf[ 2 ] = { 0, 0 };
    uint8_t len = ( reg & 0x80 ) ? 2 : 1;       // MAC/MII registers return a dummy byte first

    ( void )eth_transport_bus_read( eth, &cmd, 1, buf, len );

    return buf[ len - 1 ];
}

static void enc28j60_read_mem( eth_transport_t *eth, uint8_t *buf, uint16_t len ) {     // RBM - Read Buffer Memory
    uint8_t cmd = ENC28J60_RBM_CMD;

    ( void )eth_transport_bus_read( eth, &cmd, 1, buf, len );
}

static void enc28j60_write_reg( eth_transport_t *eth, uint8_t reg, uint8_t value ) {    // WCR - Write Control Register
    uint8_t cmd[ 2 ];

    cmd[ 0 ] = ( uint8_t )( ENC28J60_WCR_CMD | ( reg & 0x1F ) );
    cmd[ 1 ] = value;

    ( void )eth_transport_bus_write( eth, cmd, 2, NULL, 0 );
}

static void enc28j60_write_mem( eth_transport_t *eth, uint8_t *buf, uint16_t len ) {    // WBM - Write Buffer Memory
    uint8_t cmd = ENC28J60_WBM_CMD;

    ( void )eth_transport_bus_write( eth, &cmd, 1, buf, len );
}

static void enc28j60_set_bit_reg( eth_transport_t *eth, uint8_t reg, uint8_t mask ) {   // BFS - Bit Field Set
    uint8_t cmd[ 2 ];

    cmd[ 0 ] = ( uint8_t )( ENC28J60_BFS_CMD | ( reg & 0x1F ) );
    cmd[ 1 ] = mask;

    ( void )eth_transport_bus_write( eth, cmd, 2, NULL, 0 );
}

static void enc28j60_clear_bit_reg( eth_transport_t *eth, uint8_t reg, uint8_t mask ) { // BFC - Bit Field Clear
    uint8_t cmd[ 2 ];

    cmd[ 0 ] = ( uint8_t )( ENC28J60_BFC_CMD | ( reg & 0x1F ) );
    cmd[ 1 ] = mask;

    ( void )eth_transport_bus_write( eth, cmd, 2, NULL, 0 );
}

static void enc28j60_set_write_ptr( eth_transport_t *eth, uint16_t addr ) {
    enc28j60_write_reg( eth, EWRPTL, addr & 0xFF );
    enc28j60_write_reg( eth, EWRPTH, addr >> 8 );
}

// Init
static void enc28j60_hw_reset( eth_transport_t *eth ) {
    digital_out_high( &eth->reset ); Delay_ms( 10 );
    digital_out_low( &eth->reset );  Delay_ms( 10 );
    digital_out_high( &eth->reset ); Delay_ms( 100 );
}

static void enc28j60_sw_reset( eth_transport_t *eth ) {
    uint8_t cmd = ENC28J60_SRC_CMD;

    ( void )eth_transport_bus_write( eth, &cmd, 1, NULL, 0 );
    Delay_ms( 2 );
}

static void enc28j60_wait_clk_ready( eth_transport_t *eth ) {
    uint16_t tries = 0;

    ENC28J60_CTX( eth )->current_bank = 0;      // Bank 0 is selected after reset

    while ( !( enc28j60_read_reg( eth, ESTAT ) & 0x01 ) ) {
        Delay_ms( 1 );
        if ( ++tries > 200 ) break;
    }
    Delay_ms( 10 );
}

static void enc28j60_init_rx_buffer( eth_transport_t *eth ) {
    enc28j60_select_bank( eth, 0 );
    enc28j60_write_reg( eth, ERXSTL, RECEIVE_START & 0xFF );
    enc28j60_write_reg( eth, ERXSTH, RECEIVE_START >> 8 );

    enc28j60_write_reg( eth, ERXNDL, RECEIVE_END & 0xFF );
    enc28j60_write_reg( eth, ERXNDH, RECEIVE_END >> 8 );

    enc28j60_write_reg( eth, ERXRDPTL, RECEIVE_END & 0xFF );
    enc28j60_write_reg( eth, ERXRDPTH, RECEIVE_END >> 8 );

    enc28j60_write_reg( eth, ERDPTL, RECEIVE_START & 0xFF );
    enc28j60_write_reg( eth, ERDPTH, RECEIVE_START >> 8 );

    ENC28J60_CTX( eth )->next_ptr = RECEIVE_START;
}

static void enc28j60_init_tx_buffer( eth_transport_t *eth ) {
    enc28j60_select_bank( eth, 0 );
    enc28j60_write_reg( eth, ETXSTL, TRANSMIT_START & 0xFF );
    enc28j60_write_reg( eth, ETXSTH, TRANSMIT_START >> 8 );
}

static void enc28j60_init_rx_filter( eth_transport_t *eth ) {
    enc28j60_select_bank( eth, 1 );
    enc28j60_write_reg( eth, ERXFCON, 0xA1 );
}

static void enc28j60_init_mac( eth_transport_t *eth ) {
    enc28j60_select_bank( eth, 2 );
    enc28j60_write_reg( eth, MACON1, eth->full_duplex ?
        ( MACON1_MARXEN | MACON1_TXPAUS | MACON1_RXPAUS ) :
        MACON1_MARXEN );

    enc28j60_write_reg( eth, MACON3, eth->full_duplex ?
        ( MACON3_PADCFG_SET | MACON3_TXCRCEN | MACON3_FULDPX ) :
        ( MACON3_PADCFG_SET | MACON3_TXCRCEN ) );

    enc28j60_write_reg( eth, MACON4, eth->full_duplex ? 0 : MACON4_DEFER );

    enc28j60_write_reg( eth, MAMXFLL, ENC28J60_FRAME_SIZE & 0xFF );
    enc28j60_write_reg( eth, MAMXFLH, ENC28J60_FRAME_SIZE >> 8 );

    enc28j60_write_reg( eth, MABBIPG, eth->full_duplex ? 0x15 : 0x12 );
    enc28j60_write_reg( eth, MAIPGL, 0x12 );

    if ( !eth->full_duplex )
        enc28j60_write_reg( eth, MAIPGH, 0x0C );
}

static void enc28j60_init_clock_output( eth_transport_t *eth ) {
    enc28j60_select_bank( eth, 3 );
    enc28j60_write_reg( eth, ECOCON, 0x00 );
}

err_t enc28j60_init( eth_transport_t *eth ) {
    enc28j60_ctx_t *ctx;

    if ( !eth || !eth->driver_ctx ) return ETH_TRANSPORT_ERROR;
    ctx = ENC28J60_CTX( eth );
    ctx->current_bank = 0;

    enc28j60_hw_reset( eth );                   // HW RESET
    enc28j60_sw_reset( eth );                   // SW RESET
    enc28j60_wait_clk_ready( eth );             // WAIT CLK READY AFTER RESET

    enc28j60_init_rx_buffer( eth );             // INIT RX
    enc28j60_init_tx_buffer( eth );             // INIT TX
    enc28j60_init_rx_filter( eth );             // Conditions (ex: broadcast, multicast, MAC frames)
    enc28j60_init_mac( eth );                   // MAC Activation
    enc28j60_set_mac( eth, eth->mac );          // MAC address
    enc28j60_init_clock_output( eth );          // Deactivation of configurable clock output

    enc28j60_select_bank( eth, 3 );             // HW VERSION
    ctx->hw_rev = enc28j60_read_reg( eth, EREVID );

    enc28j60_phy_init( eth );                   // Physical Link

    enc28j60_select_bank( eth, 0 );
    enc28j60_set_bit_reg( eth, ECON1, ECON1_RXEN );     // Set ACTIVE Ethernet reception

    return ETH_TRANSPORT_SUCCESS;
}

// PHY access
void enc28j60_phy_init( eth_transport_t *eth ) {
    enc28j60_phy_write( eth, PHCON1, 0x8000 );  // Reset PHY
    Delay_ms( 100 );
    enc28j60_phy_write( eth, PHCON1, 0x0000 );  // Normal mode
    Delay_ms( 50 );
    enc28j60_phy_write( eth, PHCON2, 0x0100 );  // Disable loopback (so physical cable only)
    Delay_ms( 50 );
}

void enc28j60_phy_write( eth_transport_t *eth, uint8_t phy_reg, uint16_t value ) {
    uint16_t tries = 0;

    enc28j60_select_bank( eth, 2 );
    enc28j60_write_reg( eth, MIREGADR & 0x1F, phy_reg );
    enc28j60_write_reg( eth, MIWRL    & 0x1F, ( uint8_t )( value & 0xFF ) );
    enc28j60_write_reg( eth, MIWRH    & 0x1F, ( uint8_t )( value >> 8 ) );
    Delay_ms( 15 );
    enc28j60_select_bank( eth, 2 );
    while ( enc28j60_read_reg( eth, MISTAT & 0x1F ) & MISTAT_BUSY ) {
        Delay_ms( 1 );
        if ( ++tries > ENC28J60_MIIM_TIMEOUT_MS ) break;
    }
}

void enc28j60_phy_read( eth_transport_t *eth, uint8_t reg, uint8_t *low, uint8_t *high ) {
    uint16_t tries = 0;

    enc28j60_select_bank( eth, 2 );
    enc28j60_write_reg( eth, MIREGADR & 0x1F, reg );
    enc28j60_write_reg( eth, MICMD & 0x1F, MICMD_MIIRD );
    Delay_ms( 15 );
    enc28j60_select_bank( eth, 2 );
    while ( enc28j60_read_reg( eth, MISTAT & 0x1F ) & MISTAT_BUSY ) {
        Delay_ms( 1 );
        if ( ++tries > ENC28J60_MIIM_TIMEOUT_MS ) break;
    }
    enc28j60_write_reg( eth, MICMD & 0x1F, 0x00 );
    *low  = enc28j60_read_reg( eth, MIRDL & 0x1F );
    *high = enc28j60_read_reg( eth, MIRDH & 0x1F );
}

// Data transfer
uint8_t enc28j60_packet_available( eth_transport_t *eth ) {
    if ( !eth ) return 0;

    enc28j60_select_bank( eth, 0 );
    enc28j60_set_bit_reg( eth, ECON1, ECON1_RXEN );

    enc28j60_select_bank( eth, 1 );
    return enc28j60_read_reg( eth, EPKTCNT );
}

uint16_t enc28j60_read_packet( eth_transport_t *eth, uint8_t *buf, uint16_t max_len ) {
    enc28j60_ctx_t *ctx = ENC28J60_CTX( eth );
    uint8_t header[ 6 ];
    uint16_t length;
    uint16_t status;
    uint16_t new_ptr;

    if ( !enc28j60_packet_available( eth ) ) return 0;

    enc28j60_select_bank( eth, 0 );
    enc28j60_write_reg( eth, ERDPTL, ctx->next_ptr & 0xFF );
    enc28j60_write_reg( eth, ERDPTH, ctx->next_ptr >> 8 );

    enc28j60_read_mem( eth, header, sizeof( header ) );

    ctx->next_ptr = header[ 0 ] | ( ( uint16_t )header[ 1 ] << 8 );
    length        = header[ 2 ] | ( ( uint16_t )header[ 3 ] << 8 );
    status        = header[ 4 ] | ( ( uint16_t )header[ 5 ] << 8 );

    if ( ( status & ENC28J60_RSV_RECEIVED_OK ) == 0 ) {
        enc28j60_set_bit_reg( eth, ECON2, PKTDEC );
        return 0;
    }

    if ( length > 4 ) length -= 4;              // Strip FCS
    if ( length > max_len ) length = max_len;
    enc28j60_read_mem( eth, buf, length );

    // ERXRDPT must be odd (errata), so it is set just before the next packet
    new_ptr = ( ctx->next_ptr == RECEIVE_START ) ? RECEIVE_END : ctx->next_ptr - 1;
    enc28j60_write_reg( eth, ERXRDPTL, new_ptr & 0xFF );
    enc28j60_write_reg( eth, ERXRDPTH, new_ptr >> 8 );

    enc28j60_set_bit_reg( eth, ECON2, PKTDEC );
    return length;
}

uint16_t enc28j60_send_packet( eth_transport_t *eth, uint8_t *buf, uint16_t len ) {
    uint8_t ctrl = 0x00;                        // Per packet control byte: use MACON3 settings
    uint16_t txnd;
    uint16_t tries = 0;

    if ( len > ENC28J60_FRAME_SIZE ) return 0;

    enc28j60_select_bank( eth, 0 );

    // TX buffer lives above the RX ring (TRANSMIT_START .. end of RAM)
    enc28j60_write_reg( eth, ETXSTL, TRANSMIT_START & 0xFF );
    enc28j60_write_reg( eth, ETXSTH, TRANSMIT_START >> 8 );
    txnd = TRANSMIT_START + len;
    enc28j60_write_reg( eth, ETXNDL, txnd & 0xFF );
    enc28j60_write_reg( eth, ETXNDH, txnd >> 8 );

    enc28j60_set_bit_reg( eth, ECON1, TXRST );
    enc28j60_clear_bit_reg( eth, ECON1, TXRST );
    enc28j60_clear_bit_reg( eth, EIR, TXERIF | TXIF );

    enc28j60_set_write_ptr( eth, TRANSMIT_START );
    enc28j60_write_mem( eth, &ctrl, 1 );
    enc28j60_write_mem( eth, buf, len );

    enc28j60_set_bit_reg( eth, ECON1, TXRTS );
    while ( enc28j60_read_reg( eth, ECON1 ) & TXRTS ) {
        Delay_ms( 1 );
        if ( ++tries > 200 ) break;
    }
    if ( enc28j60_read_reg( eth, EIR ) & TXERIF )
        enc28j60_clear_bit_reg( eth, ECON1, TXRTS );
    return len;
}

// Link / identification
uint8_t enc28j60_get_link_status( eth_transport_t *eth ) {
    uint8_t low = 0, high = 0;

    if ( !eth ) return 0;

    // Link failure is latched, the second read returns the current state
    enc28j60_phy_read( eth, PHSTAT2, &low, &high );
    enc28j60_phy_read( eth, PHSTAT2, &low, &high );

    return ( high & PHSTAT2_LSTAT_HIGH_MASK ) ? 1 : 0;
}

uint8_t enc28j60_get_rev( eth_transport_t *eth ) {
    if ( !eth || !eth->driver_ctx ) return 0;
    return ENC28J60_CTX( eth )->hw_rev;
}

// Addressing
err_t enc28j60_set_mac( eth_transport_t *eth, uint8_t *mac ) {
    enc28j60_select_bank( eth, 3 );
    enc28j60_write_reg( eth, MAADR1, mac[ 0 ] );
    enc28j60_write_reg( eth, MAADR2, mac[ 1 ] );
    enc28j60_write_reg( eth, MAADR3, mac[ 2 ] );
    enc28j60_write_reg( eth, MAADR4, mac[ 3 ] );
    enc28j60_write_reg( eth, MAADR5, mac[ 4 ] );
    enc28j60_write_reg( eth, MAADR6, mac[ 5 ] );
    return ETH_TRANSPORT_SUCCESS;
}

// Config / setup
void enc28j60_cfg_setup( enc28j60_cfg_t *cfg ) {
    eth_bus_spi_cfg_setup( &cfg->bus );
    eth_transport_cfg_setup( &cfg->eth );
}

err_t enc28j60_configure( eth_transport_t *eth, eth_bus_spi_t *bus, enc28j60_cfg_t *cfg ) {
    if ( !eth || !cfg ) return ETH_TRANSPORT_ERROR;
    if ( !eth->driver_ctx )
        eth->driver_ctx = &enc28j60_default_ctx;
    return eth_bus_spi_configure( eth, bus, &cfg->bus, &cfg->eth );
}

// ----------------------------------------------------------------------- END
