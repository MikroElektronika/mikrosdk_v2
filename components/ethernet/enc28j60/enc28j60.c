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

// Control registers and memory layout, private to the driver: the plain names
// (MACON1, ECON1, EIR, ...) are also SFRs of the PIC18F97J60 family
#define ENC28J60_MICMD_MIIRD    0x01

#define ENC28J60_EIE              0x1B
#define ENC28J60_EIR              0x1C
#define ENC28J60_ESTAT            0x1D
#define ENC28J60_ECON2            0x1E
#define ENC28J60_ECON1            0x1F
// Bank 0 registers
#define ENC28J60_ERDPTL           ( 0x00 )
#define ENC28J60_ERDPTH           ( 0x01 )
#define ENC28J60_EWRPTL           ( 0x02 )
#define ENC28J60_EWRPTH           ( 0x03 )
#define ENC28J60_ETXSTL           ( 0x04 )
#define ENC28J60_ETXSTH           ( 0x05 )
#define ENC28J60_ETXNDL           ( 0x06 )
#define ENC28J60_ETXNDH           ( 0x07 )
#define ENC28J60_ERXSTL           ( 0x08 )
#define ENC28J60_ERXSTH           ( 0x09 )
#define ENC28J60_ERXNDL           ( 0x0A )
#define ENC28J60_ERXNDH           ( 0x0B )
#define ENC28J60_ERXRDPTL         ( 0x0C )
#define ENC28J60_ERXRDPTH         ( 0x0D )
#define ENC28J60_ERXWRPTL         ( 0x0E )
#define ENC28J60_ERXWRPTH         ( 0x0F )
#define ENC28J60_EDMASTL          ( 0x10 )
#define ENC28J60_EDMASTH          ( 0x11 )
#define ENC28J60_EDMANDL          ( 0x12 )
#define ENC28J60_EDMANDH          ( 0x13 )
#define ENC28J60_EDMADSTL         ( 0x14 )
#define ENC28J60_EDMADSTH         ( 0x15 )
#define ENC28J60_EDMACSL          ( 0x16 )
#define ENC28J60_EDMACSH          ( 0x17 )
// Bank 1 registers
#define ENC28J60_EHT0             ( 0x00 )
#define ENC28J60_EHT1             ( 0x01 )
#define ENC28J60_EHT2             ( 0x02 )
#define ENC28J60_EHT3             ( 0x03 )
#define ENC28J60_EHT4             ( 0x04 )
#define ENC28J60_EHT5             ( 0x05 )
#define ENC28J60_EHT6             ( 0x06 )
#define ENC28J60_EHT7             ( 0x07 )
#define ENC28J60_EPMM0            ( 0x08 )
#define ENC28J60_EPMM1            ( 0x09 )
#define ENC28J60_EPMM2            ( 0x0A )
#define ENC28J60_EPMM3            ( 0x0B )
#define ENC28J60_EPMM4            ( 0x0C )
#define ENC28J60_EPMM5            ( 0x0D )
#define ENC28J60_EPMM6            ( 0x0E )
#define ENC28J60_EPMM7            ( 0x0F )
#define ENC28J60_EPMCSL           ( 0x10 )
#define ENC28J60_EPMCSH           ( 0x11 )
#define ENC28J60_EPMOL            ( 0x14 )
#define ENC28J60_EPMOH            ( 0x15 )
#define ENC28J60_EWOLIE           ( 0x16 )
#define ENC28J60_EWOLIR           ( 0x17 )
#define ENC28J60_ERXFCON          ( 0x18 )
#define ENC28J60_EPKTCNT          ( 0x19 )
// Bank 2 registers
#define ENC28J60_MACON1           ( 0x00|0x80 )
#define ENC28J60_MACON2           ( 0x01|0x80 )
#define ENC28J60_MACON3           ( 0x02|0x80 )
#define ENC28J60_MACON4           ( 0x03|0x80 )
#define ENC28J60_MABBIPG          ( 0x04|0x80 )
#define ENC28J60_MAIPGL           ( 0x06|0x80 )
#define ENC28J60_MAIPGH           ( 0x07|0x80 )
#define ENC28J60_MACLCON1         ( 0x08|0x80 )
#define ENC28J60_MACLCON2         ( 0x09|0x80 )
#define ENC28J60_MAMXFLL          ( 0x0A|0x80 )
#define ENC28J60_MAMXFLH          ( 0x0B|0x80 )
#define ENC28J60_MAPHSUP          ( 0x0D|0x80 )
#define ENC28J60_MICON            ( 0x11|0x80 )
#define ENC28J60_MICMD            ( 0x12|0x80 )
#define ENC28J60_MIREGADR         ( 0x14|0x80 )
#define ENC28J60_MIWRL            ( 0x16|0x80 )
#define ENC28J60_MIWRH            ( 0x17|0x80 )
#define ENC28J60_MIRDL            ( 0x18|0x80 )
#define ENC28J60_MIRDH            ( 0x19|0x80 )
// Bank 3 registers
#define ENC28J60_MAADR5           ( 0x00|0x80 )
#define ENC28J60_MAADR6           ( 0x01|0x80 )
#define ENC28J60_MAADR3           ( 0x02|0x80 )
#define ENC28J60_MAADR4           ( 0x03|0x80 )
#define ENC28J60_MAADR1           ( 0x04|0x80 )
#define ENC28J60_MAADR2           ( 0x05|0x80 )
#define ENC28J60_EBSTSD           ( 0x06 )
#define ENC28J60_EBSTCON          ( 0x07 )
#define ENC28J60_EBSTCSL          ( 0x08 )
#define ENC28J60_EBSTCSH          ( 0x09 )
#define ENC28J60_MISTAT           ( 0x0A|0x80 )
#define ENC28J60_EREVID           ( 0x12 )
#define ENC28J60_ECOCON           ( 0x15 )
#define ENC28J60_EFLOCON          ( 0x17 )
#define ENC28J60_EPAUSL           ( 0x18 )
#define ENC28J60_EPAUSH           ( 0x19 )

// Memory allocation
#define ENC28J60_RAM_SIZE       ( 8192 )                                            // 8kb RAM available
#define ENC28J60_TRANSMIT_START ( ENC28J60_RAM_SIZE - ( ENC28J60_FRAME_SIZE + 100 ) )   // Transmit buffer start address, a few more bytes for padding pseudo header + transmit status : Even memory address
#define ENC28J60_RECEIVE_START  ( 0 )                                               // Receive buffer start address : Should be an even memory address; must be 0 for errata
#define ENC28J60_RECEIVE_END    ( ENC28J60_TRANSMIT_START - 1 )                     // Receive buffer end address : Odd for errata workaround

#define PKTDEC      0x40
#define CSUMEN      0x10
#define DMAST       0x20

#define MARXEN      0x01
#define ECON1_RXEN  0x04
#define ECON1_RXRST 0x40
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
#define ENC28J60_EREVID_UNUSED   0xE0   // ENC28J60_EREVID bits 7:5 always read 0

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
static uint8_t enc28j60_wait_clk_ready( eth_transport_t *eth );
static void    enc28j60_init_rx_buffer( eth_transport_t *eth );
static void    enc28j60_init_tx_buffer( eth_transport_t *eth );
static void    enc28j60_init_rx_filter( eth_transport_t *eth );
static void    enc28j60_init_mac( eth_transport_t *eth );
static void    enc28j60_init_clock_output( eth_transport_t *eth );
static void    enc28j60_set_write_ptr( eth_transport_t *eth, uint16_t addr );
static void    enc28j60_write_mac( eth_transport_t *eth, uint8_t *mac );
static void    enc28j60_rx_recover( eth_transport_t *eth );

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

    cmd[ 0 ] = ( uint8_t )( ENC28J60_BFC_CMD | ( ENC28J60_ECON1 & 0x1F ) );
    cmd[ 1 ] = 0x03;

    ( void )eth_transport_bus_write( eth, cmd, 2, NULL, 0 );

    cmd[ 0 ] = ( uint8_t )( ENC28J60_BFS_CMD | ( ENC28J60_ECON1 & 0x1F ) );
    cmd[ 1 ] = ( uint8_t )( bank & 0x03 );

    ( void )eth_transport_bus_write( eth, cmd, 2, NULL, 0 );

    // On a failed write the selected bank is unknown, force a reselect next time
    ctx->current_bank = eth->bus_error ? 0xFF : bank;
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
    enc28j60_write_reg( eth, ENC28J60_EWRPTL, addr & 0xFF );
    enc28j60_write_reg( eth, ENC28J60_EWRPTH, addr >> 8 );
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

static uint8_t enc28j60_wait_clk_ready( eth_transport_t *eth ) {
    uint16_t tries = 0;

    ENC28J60_CTX( eth )->current_bank = 0;      // Bank 0 is selected after reset

    while ( !( enc28j60_read_reg( eth, ENC28J60_ESTAT ) & 0x01 ) ) {
        if ( eth->bus_error || ++tries > 200 ) return 0;
        Delay_ms( 1 );
    }
    Delay_ms( 10 );
    return eth->bus_error ? 0 : 1;
}

static void enc28j60_init_rx_buffer( eth_transport_t *eth ) {
    enc28j60_select_bank( eth, 0 );
    enc28j60_write_reg( eth, ENC28J60_ERXSTL, ENC28J60_RECEIVE_START & 0xFF );
    enc28j60_write_reg( eth, ENC28J60_ERXSTH, ENC28J60_RECEIVE_START >> 8 );

    enc28j60_write_reg( eth, ENC28J60_ERXNDL, ENC28J60_RECEIVE_END & 0xFF );
    enc28j60_write_reg( eth, ENC28J60_ERXNDH, ENC28J60_RECEIVE_END >> 8 );

    enc28j60_write_reg( eth, ENC28J60_ERXRDPTL, ENC28J60_RECEIVE_END & 0xFF );
    enc28j60_write_reg( eth, ENC28J60_ERXRDPTH, ENC28J60_RECEIVE_END >> 8 );

    enc28j60_write_reg( eth, ENC28J60_ERDPTL, ENC28J60_RECEIVE_START & 0xFF );
    enc28j60_write_reg( eth, ENC28J60_ERDPTH, ENC28J60_RECEIVE_START >> 8 );

    ENC28J60_CTX( eth )->next_ptr = ENC28J60_RECEIVE_START;
}

static void enc28j60_init_tx_buffer( eth_transport_t *eth ) {
    enc28j60_select_bank( eth, 0 );
    enc28j60_write_reg( eth, ENC28J60_ETXSTL, ENC28J60_TRANSMIT_START & 0xFF );
    enc28j60_write_reg( eth, ENC28J60_ETXSTH, ENC28J60_TRANSMIT_START >> 8 );
}

static void enc28j60_init_rx_filter( eth_transport_t *eth ) {
    enc28j60_select_bank( eth, 1 );
    enc28j60_write_reg( eth, ENC28J60_ERXFCON, 0xA1 );
}

static void enc28j60_init_mac( eth_transport_t *eth ) {
    enc28j60_select_bank( eth, 2 );
    enc28j60_write_reg( eth, ENC28J60_MACON1, eth->full_duplex ?
        ( MACON1_MARXEN | MACON1_TXPAUS | MACON1_RXPAUS ) :
        MACON1_MARXEN );

    enc28j60_write_reg( eth, ENC28J60_MACON3, eth->full_duplex ?
        ( MACON3_PADCFG_SET | MACON3_TXCRCEN | MACON3_FULDPX ) :
        ( MACON3_PADCFG_SET | MACON3_TXCRCEN ) );

    enc28j60_write_reg( eth, ENC28J60_MACON4, eth->full_duplex ? 0 : MACON4_DEFER );

    enc28j60_write_reg( eth, ENC28J60_MAMXFLL, ENC28J60_FRAME_SIZE & 0xFF );
    enc28j60_write_reg( eth, ENC28J60_MAMXFLH, ENC28J60_FRAME_SIZE >> 8 );

    enc28j60_write_reg( eth, ENC28J60_MABBIPG, eth->full_duplex ? 0x15 : 0x12 );
    enc28j60_write_reg( eth, ENC28J60_MAIPGL, 0x12 );

    if ( !eth->full_duplex )
        enc28j60_write_reg( eth, ENC28J60_MAIPGH, 0x0C );
}

static void enc28j60_init_clock_output( eth_transport_t *eth ) {
    enc28j60_select_bank( eth, 3 );
    enc28j60_write_reg( eth, ENC28J60_ECOCON, 0x00 );
}

err_t enc28j60_init( eth_transport_t *eth ) {
    enc28j60_ctx_t *ctx;

    if ( !eth || !eth->driver_ctx ) return ETH_TRANSPORT_ERROR;
    ctx = ENC28J60_CTX( eth );
    ctx->current_bank = 0;
    eth->bus_error = 0;

    enc28j60_hw_reset( eth );                   // HW RESET
    enc28j60_sw_reset( eth );                   // SW RESET
    if ( !enc28j60_wait_clk_ready( eth ) )      // WAIT CLK READY AFTER RESET
        return ETH_TRANSPORT_ERROR;

    enc28j60_init_rx_buffer( eth );             // INIT RX
    enc28j60_init_tx_buffer( eth );             // INIT TX
    enc28j60_init_rx_filter( eth );             // Conditions (ex: broadcast, multicast, MAC frames)
    enc28j60_init_mac( eth );                   // MAC Activation
    enc28j60_write_mac( eth, eth->mac );        // MAC address
    enc28j60_init_clock_output( eth );          // Deactivation of configurable clock output

    enc28j60_select_bank( eth, 3 );             // HW VERSION
    ctx->hw_rev = enc28j60_read_reg( eth, ENC28J60_EREVID );
    if ( !ctx->hw_rev || ( ctx->hw_rev & ENC28J60_EREVID_UNUSED ) )
        return ETH_TRANSPORT_ERROR;             // No ENC28J60 responding

    enc28j60_phy_init( eth );                   // Physical Link

    enc28j60_select_bank( eth, 0 );
    enc28j60_set_bit_reg( eth, ENC28J60_ECON1, ECON1_RXEN );     // Set ACTIVE Ethernet reception

    return eth->bus_error ? ETH_TRANSPORT_ERROR : ETH_TRANSPORT_SUCCESS;
}

// PHY access
void enc28j60_phy_init( eth_transport_t *eth ) {
    enc28j60_phy_write( eth, PHCON1, PHCON1_PRST );     // Reset PHY
    Delay_ms( 100 );
    // Normal mode, PHY duplex must match ENC28J60_MACON3.FULDPX
    enc28j60_phy_write( eth, PHCON1, eth->full_duplex ? PHCON1_PDPXMD : 0x0000 );
    Delay_ms( 50 );
    enc28j60_phy_write( eth, PHCON2, 0x0100 );  // Disable loopback (so physical cable only)
    Delay_ms( 50 );
}

void enc28j60_phy_write( eth_transport_t *eth, uint8_t phy_reg, uint16_t value ) {
    uint16_t tries = 0;

    enc28j60_select_bank( eth, 2 );
    enc28j60_write_reg( eth, ENC28J60_MIREGADR & 0x1F, phy_reg );
    enc28j60_write_reg( eth, ENC28J60_MIWRL    & 0x1F, ( uint8_t )( value & 0xFF ) );
    enc28j60_write_reg( eth, ENC28J60_MIWRH    & 0x1F, ( uint8_t )( value >> 8 ) );
    Delay_ms( 15 );
    enc28j60_select_bank( eth, 3 );             // MISTAT is in bank 3
    while ( enc28j60_read_reg( eth, ENC28J60_MISTAT ) & MISTAT_BUSY ) {
        if ( eth->bus_error ) break;
        if ( ++tries > ENC28J60_MIIM_TIMEOUT_MS ) {
            eth->bus_error = 1;                 // PHY not responding
            break;
        }
        Delay_ms( 1 );
    }
}

void enc28j60_phy_read( eth_transport_t *eth, uint8_t reg, uint8_t *low, uint8_t *high ) {
    uint16_t tries = 0;

    enc28j60_select_bank( eth, 2 );
    enc28j60_write_reg( eth, ENC28J60_MIREGADR & 0x1F, reg );
    enc28j60_write_reg( eth, ENC28J60_MICMD & 0x1F, ENC28J60_MICMD_MIIRD );
    Delay_ms( 15 );
    enc28j60_select_bank( eth, 3 );             // MISTAT is in bank 3
    while ( enc28j60_read_reg( eth, ENC28J60_MISTAT ) & MISTAT_BUSY ) {
        if ( eth->bus_error ) break;
        if ( ++tries > ENC28J60_MIIM_TIMEOUT_MS ) {
            eth->bus_error = 1;                 // PHY not responding
            break;
        }
        Delay_ms( 1 );
    }
    enc28j60_select_bank( eth, 2 );
    enc28j60_write_reg( eth, ENC28J60_MICMD & 0x1F, 0x00 );
    // MII registers return a dummy byte first, keep the 0x80 marker
    *low  = enc28j60_read_reg( eth, ENC28J60_MIRDL );
    *high = enc28j60_read_reg( eth, ENC28J60_MIRDH );
}

// Data transfer
uint8_t enc28j60_packet_available( eth_transport_t *eth ) {
    uint8_t count;

    if ( !eth ) return 0;
    eth->bus_error = 0;

    enc28j60_select_bank( eth, 0 );
    enc28j60_set_bit_reg( eth, ENC28J60_ECON1, ECON1_RXEN );

    enc28j60_select_bank( eth, 1 );
    count = enc28j60_read_reg( eth, ENC28J60_EPKTCNT );
    return eth->bus_error ? 0 : count;
}

// Recovery from a corrupt RX header: reset the receive logic and start with an empty ring
static void enc28j60_rx_recover( eth_transport_t *eth ) {
    uint8_t tries = 0;

    enc28j60_clear_bit_reg( eth, ENC28J60_ECON1, ECON1_RXEN );
    enc28j60_set_bit_reg( eth, ENC28J60_ECON1, ECON1_RXRST );
    enc28j60_clear_bit_reg( eth, ENC28J60_ECON1, ECON1_RXRST );
    enc28j60_init_rx_buffer( eth );

    enc28j60_select_bank( eth, 1 );
    while ( enc28j60_read_reg( eth, ENC28J60_EPKTCNT ) && !eth->bus_error && ++tries )
        enc28j60_set_bit_reg( eth, ENC28J60_ECON2, PKTDEC );

    enc28j60_select_bank( eth, 0 );
    enc28j60_set_bit_reg( eth, ENC28J60_ECON1, ECON1_RXEN );
}

uint16_t enc28j60_read_packet( eth_transport_t *eth, uint8_t *buf, uint16_t max_len ) {
    enc28j60_ctx_t *ctx;
    uint8_t header[ 6 ] = { 0, 0, 0, 0, 0, 0 };
    uint16_t next_ptr;
    uint16_t length;
    uint16_t status;
    uint16_t new_ptr;

    if ( !eth || !eth->driver_ctx ) return 0;
    ctx = ENC28J60_CTX( eth );

    if ( !enc28j60_packet_available( eth ) ) return 0;

    enc28j60_select_bank( eth, 0 );
    enc28j60_write_reg( eth, ENC28J60_ERDPTL, ctx->next_ptr & 0xFF );
    enc28j60_write_reg( eth, ENC28J60_ERDPTH, ctx->next_ptr >> 8 );

    enc28j60_read_mem( eth, header, sizeof( header ) );
    if ( eth->bus_error ) return 0;             // Nothing consumed, retried on the next call

    next_ptr = header[ 0 ] | ( ( uint16_t )header[ 1 ] << 8 );
    length   = header[ 2 ] | ( ( uint16_t )header[ 3 ] << 8 );
    status   = header[ 4 ] | ( ( uint16_t )header[ 5 ] << 8 );

    // Packets start on even addresses inside the RX ring, anything else means the read position is lost
    if ( next_ptr > ENC28J60_RECEIVE_END || ( next_ptr & 1 ) || length > ENC28J60_FRAME_SIZE ) {
        enc28j60_rx_recover( eth );
        return 0;
    }

    if ( ( status & ENC28J60_RSV_RECEIVED_OK ) == 0 ) {
        length = 0;                             // Drop, but still release its ring space
    } else {
        if ( length > 4 ) length -= 4;          // Strip FCS
        if ( length > max_len ) length = max_len;
        enc28j60_read_mem( eth, buf, length );
        if ( eth->bus_error ) return 0;         // Packet stays in the ring, retried on the next call
    }

    // ERXRDPT must be odd (errata), so it is set just before the next packet
    ctx->next_ptr = next_ptr;
    new_ptr = ( next_ptr == ENC28J60_RECEIVE_START ) ? ENC28J60_RECEIVE_END : next_ptr - 1;
    enc28j60_write_reg( eth, ENC28J60_ERXRDPTL, new_ptr & 0xFF );
    enc28j60_write_reg( eth, ENC28J60_ERXRDPTH, new_ptr >> 8 );

    enc28j60_set_bit_reg( eth, ENC28J60_ECON2, PKTDEC );
    return eth->bus_error ? 0 : length;
}

uint16_t enc28j60_send_packet( eth_transport_t *eth, uint8_t *buf, uint16_t len ) {
    uint8_t ctrl = 0x00;                        // Per packet control byte: use ENC28J60_MACON3 settings
    uint16_t txnd;
    uint16_t tries = 0;

    if ( len > ENC28J60_TX_FRAME_SIZE ) return 0;
    eth->bus_error = 0;

    enc28j60_select_bank( eth, 0 );

    // TX buffer lives above the RX ring (ENC28J60_TRANSMIT_START .. end of RAM)
    enc28j60_write_reg( eth, ENC28J60_ETXSTL, ENC28J60_TRANSMIT_START & 0xFF );
    enc28j60_write_reg( eth, ENC28J60_ETXSTH, ENC28J60_TRANSMIT_START >> 8 );
    txnd = ENC28J60_TRANSMIT_START + len;
    enc28j60_write_reg( eth, ENC28J60_ETXNDL, txnd & 0xFF );
    enc28j60_write_reg( eth, ENC28J60_ETXNDH, txnd >> 8 );

    enc28j60_set_bit_reg( eth, ENC28J60_ECON1, TXRST );
    enc28j60_clear_bit_reg( eth, ENC28J60_ECON1, TXRST );
    enc28j60_clear_bit_reg( eth, ENC28J60_EIR, TXERIF | TXIF );

    enc28j60_set_write_ptr( eth, ENC28J60_TRANSMIT_START );
    enc28j60_write_mem( eth, &ctrl, 1 );
    enc28j60_write_mem( eth, buf, len );
    if ( eth->bus_error ) return 0;

    enc28j60_set_bit_reg( eth, ENC28J60_ECON1, TXRTS );
    while ( enc28j60_read_reg( eth, ENC28J60_ECON1 ) & TXRTS ) {
        if ( eth->bus_error || ++tries > 200 ) break;
        Delay_ms( 1 );
    }
    if ( eth->bus_error || ( tries > 200 ) || ( enc28j60_read_reg( eth, ENC28J60_EIR ) & TXERIF ) ) {
        enc28j60_clear_bit_reg( eth, ENC28J60_ECON1, TXRTS );    // Abort, TXRST at the next send recovers the TX logic
        return 0;
    }
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
static void enc28j60_write_mac( eth_transport_t *eth, uint8_t *mac ) {
    enc28j60_select_bank( eth, 3 );
    enc28j60_write_reg( eth, ENC28J60_MAADR1, mac[ 0 ] );
    enc28j60_write_reg( eth, ENC28J60_MAADR2, mac[ 1 ] );
    enc28j60_write_reg( eth, ENC28J60_MAADR3, mac[ 2 ] );
    enc28j60_write_reg( eth, ENC28J60_MAADR4, mac[ 3 ] );
    enc28j60_write_reg( eth, ENC28J60_MAADR5, mac[ 4 ] );
    enc28j60_write_reg( eth, ENC28J60_MAADR6, mac[ 5 ] );
}

err_t enc28j60_set_mac( eth_transport_t *eth, uint8_t *mac ) {
    eth->bus_error = 0;
    enc28j60_write_mac( eth, mac );
    return eth->bus_error ? ETH_TRANSPORT_ERROR : ETH_TRANSPORT_SUCCESS;
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
