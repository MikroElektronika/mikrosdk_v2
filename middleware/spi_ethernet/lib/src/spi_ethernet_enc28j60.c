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
 * @file spi_ethernet_enc28j60.c
 * @brief SPI Ethernet ENC28J60 Driver.
 */

#include "spi_ethernet_enc28j60.h"
#include "drv_spi_master.h"
#include <delays.h>

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

#define SPI_ETH_OK           0x00
#define SPI_ETH_INIT_ERROR   0xFF

pin_name_t enc28j60_cs_pin;

static uint8_t current_bank = 0;
static uint16_t nextPtr = RECEIVE_START;
static spi_ethernet_t *current_eth = NULL;

static uint8_t enc28j60_read_reg( uint8_t reg );
static uint8_t * enc28j60_read_mem( uint8_t *buf, uint16_t len );
static void enc28j60_write_reg( uint8_t reg, uint16_t value );
uint8_t enc28j60_packet_available( spi_ethernet_t *eth );
static void enc28j60_write_mem( const uint8_t *buf, uint16_t len );
static void enc28j60_set_bit_reg( uint8_t reg, uint8_t mask );
static void enc28j60_clear_bit_reg( uint8_t reg, uint8_t mask );
static void enc28j60_hw_reset( spi_ethernet_t *eth );
static void enc28j60_sw_reset( void );
static void enc28j60_wait_clk_ready( void );
static void enc28j60_init_rx_buffer( void );
static void enc28j60_init_tx_buffer( void );
static void enc28j60_init_rx_filter( void );
static void enc28j60_init_mac( spi_ethernet_t *eth );
static void enc28j60_init_mac_address( void );
static void enc28j60_init_clock_output( void );
static void enc28j60_read_revision( void );
static void enc28j60_set_write_ptr( uint16_t addr );
void enc28j60_phy_write( uint8_t reg, uint16_t value );
void enc28j60_phy_read( uint8_t reg, uint8_t *low, uint8_t *high );

void enc28j60_select_bank( uint8_t bank ) {
    uint8_t cmd[ 2 ];

    if ( bank > 3 ) return;

    if ( bank == current_bank )
        return;

    cmd[ 0 ] = ( uint8_t )( ENC28J60_BFC_CMD | ( ECON1 & 0x1F ) );
    cmd[ 1 ] = 0x03;

    spi_master_select_device( enc28j60_cs_pin );
    spi_master_write( current_eth->spi, cmd, 2 );
    spi_master_deselect_device( enc28j60_cs_pin );

    cmd[ 0 ] = ( uint8_t )( ENC28J60_BFS_CMD | ( ECON1 & 0x1F ) );
    cmd[ 1 ] = ( uint8_t )( bank & 0x03 );

    spi_master_select_device( enc28j60_cs_pin );
    spi_master_write( current_eth->spi, cmd, 2 );
    spi_master_deselect_device( enc28j60_cs_pin );

    current_bank = bank;
}

uint8_t enc28j60_mac_addr[ 6 ];
uint8_t enc28j60_ipaddr[ 4 ];

static uint16_t enc_hwRev;

#ifndef NULL
#endif
#define ARPCACHESIZE     3

enc28j60_arp_cache_t enc28j60_arp_cache[ ARPCACHESIZE ];

spi_ethernet_driver_t enc28j60_driver = {
    .init            = enc28j60_init,
    .send_packet     = enc28j60_send_packet,
    .read_packet     = enc28j60_read_packet,
    .available       = enc28j60_packet_available,
    .get_link_status = enc28j60_get_link_status,
    .set_mac         = enc28j60_set_mac,
    .get_mac         = enc28j60_get_mac,
    .set_ip          = enc28j60_set_ip,
    .get_ip          = enc28j60_get_ip
};

void enc28j60_init( spi_ethernet_t *eth, spi_ethernet_driver_t *drv ) {
    current_eth = eth;
    current_bank = 0;

    spi_master_deselect_device( enc28j60_cs_pin );
    
    enc28j60_hw_reset( eth );                 // HW RESET
    enc28j60_sw_reset( );                    // SW RESET
    enc28j60_wait_clk_ready( );              // WAIT CLK READY AFTER RESET

    memcpy( enc28j60_mac_addr, eth->mac, 6 );
    memcpy( enc28j60_ipaddr, eth->ip, 4 );

    enc28j60_init_rx_buffer( );              // INIT RX 
    enc28j60_init_tx_buffer( );              // INIT TX 
    enc28j60_init_rx_filter( );              // Conditions (ex: broadcast, multicast, MAC frames)
    enc28j60_init_mac( eth );                 // MAC Activation
    enc28j60_init_mac_address( );            // MAC init
    enc28j60_init_clock_output( );           // Deactivation of configurable clock output
    enc28j60_read_revision( );               // HW VERSION
    enc28j60_phy_init( );                    // Physical Link
    
    enc28j60_select_bank( 0 );
    enc28j60_set_bit_reg( ECON1, ECON1_RXEN );                    // Set ACTIVE Ethernet reception

    memset( &enc28j60_arp_cache, 0, sizeof( enc28j60_arp_cache ) ); // Init ARP cache 
    enc28j60_select_bank( 0 );
}

void enc28j60_phy_init( void ) {
    enc28j60_phy_write( PHCON1, 0x8000 );     /* Reset PHY */
    Delay_ms( 100 );
    enc28j60_phy_write( PHCON1, 0x0000 );     /* Normal mode */
    Delay_ms( 50 );
    enc28j60_phy_write( PHCON2, 0x0100 );     /* Disable loopback (so physical cable only)*/
    Delay_ms( 50 );
}

uint8_t enc28j60_get_link_status( void ) {
    uint8_t low = 0, high = 0;

    if ( !current_eth ) return 0;

    enc28j60_phy_read( PHSTAT2, &low, &high );
    enc28j60_phy_read( PHSTAT2, &low, &high );

    return ( high & PHSTAT2_LSTAT_HIGH_MASK ) ? 1 : 0;
}

int enc28j60_set_mac( const uint8_t mac[ 6 ] ) {
    memcpy( enc28j60_mac_addr, mac, 6 );

    enc28j60_select_bank( 3 );

    enc28j60_write_reg( MAADR1, mac[ 0 ] );
    enc28j60_write_reg( MAADR2, mac[ 1 ] );
    enc28j60_write_reg( MAADR3, mac[ 2 ] );
    enc28j60_write_reg( MAADR4, mac[ 3 ] );
    enc28j60_write_reg( MAADR5, mac[ 4 ] );
    enc28j60_write_reg( MAADR6, mac[ 5 ] );

    return 1;
}

int enc28j60_get_mac( uint8_t mac[ 6 ] ) {
    memcpy( mac, enc28j60_mac_addr, 6 );
    return 1;
}

int enc28j60_set_ip( const uint8_t ip[ 4 ] ) {
    memcpy( enc28j60_ipaddr, ip, 4 );
    return 1;
}

int enc28j60_get_ip( uint8_t ip[ 4 ] ) {
    memcpy( ip, enc28j60_ipaddr, 4 );
    return 1;
}

uint16_t enc28j60_read_packet( spi_ethernet_t *eth, uint8_t *buf, uint16_t max_len ) {
    uint8_t header[ 6 ];
    uint16_t length, status;

    current_eth = eth;
    if ( !enc28j60_packet_available( eth ) ) return 0;

    enc28j60_select_bank( 0 );
    enc28j60_write_reg( ERDPTL, nextPtr & 0xFF );
    enc28j60_write_reg( ERDPTH, nextPtr >> 8 );

    enc28j60_read_mem( header, sizeof( header ) );

    nextPtr = header[ 0 ] | ( header[ 1 ] << 8 );
    length  = header[ 2 ] | ( header[ 3 ] << 8 );
    status  = header[ 4 ] | ( header[ 5 ] << 8 );

    if ( ( status & ENC28J60_RSV_RECEIVED_OK ) == 0 ) {
        enc28j60_set_bit_reg( ECON2, PKTDEC );
        return 0;
    }

    if ( length > 4 ) length -= 4;
    if ( length > max_len ) length = max_len;
    enc28j60_read_mem( buf, length );

    uint16_t newPtr = ( nextPtr == RECEIVE_START ) ? RECEIVE_END : nextPtr - 1;
    enc28j60_write_reg( ERXRDPTL, newPtr & 0xFF );
    enc28j60_write_reg( ERXRDPTH, newPtr >> 8 );

    enc28j60_set_bit_reg( ECON2, PKTDEC );
    return length;
}

uint8_t enc28j60_packet_available( spi_ethernet_t *eth ) {
    if ( !eth ) return 0;

    enc28j60_select_bank( 0 );
    enc28j60_set_bit_reg( ECON1, ECON1_RXEN );

    enc28j60_select_bank( 1 );
    uint8_t num_of_packages = enc28j60_read_reg( EPKTCNT );

    return num_of_packages;
}

uint16_t enc28j60_send_packet( spi_ethernet_t *eth, uint8_t *buf, uint16_t len ) {
    current_eth = eth;
    enc28j60_select_bank( 0 );

    enc28j60_write_reg( ETXSTL, ENC28J60_TX_BUFFER_START & 0xFF );
    enc28j60_write_reg( ETXSTH, ENC28J60_TX_BUFFER_START >> 8 );
    uint16_t txnd = ENC28J60_TX_BUFFER_START + len;
    enc28j60_write_reg( ETXNDL, txnd & 0xFF );
    enc28j60_write_reg( ETXNDH, txnd >> 8 );

    enc28j60_set_bit_reg( ECON1, TXRST );
    enc28j60_clear_bit_reg( ECON1, TXRST );
    enc28j60_clear_bit_reg( EIR, TXERIF | TXIF );

    enc28j60_set_write_ptr( ENC28J60_TX_BUFFER_START );
    uint8_t ctrl = 0x00;
    enc28j60_write_mem( &ctrl, 1 );
    enc28j60_write_mem( buf, len );

    enc28j60_set_bit_reg( ECON1, TXRTS );
    uint16_t tries = 0;
    while ( enc28j60_read_reg( ECON1 ) & TXRTS ) {
        Delay_ms( 1 );
        if ( ++tries > 200 ) break;
    }
    if ( enc28j60_read_reg( EIR ) & TXERIF )
        enc28j60_clear_bit_reg( ECON1, TXRTS );
    return len;
}

uint8_t enc28j60_get_rev( void ) {
    return enc_hwRev;
}

static uint8_t enc28j60_read_reg( uint8_t reg ) {                         // RCR - Read Control Register
    uint8_t cmd = ENC28J60_RCR_CMD | ( reg & 0x1F );
    uint8_t buf[ 2 ] = {0, 0};
    uint8_t len = ( reg & 0x80 ) ? 2 : 1;

    spi_master_select_device( enc28j60_cs_pin ); 
    spi_master_write_then_read( current_eth->spi, &cmd, 1, buf, len );
    spi_master_deselect_device( enc28j60_cs_pin );

    return buf[ len - 1 ];
}

static uint8_t * enc28j60_read_mem( uint8_t *buf, uint16_t len ) {      // RBM - Read Buffer Memory
    uint8_t cmd = ENC28J60_RBM_CMD;

    spi_master_select_device( enc28j60_cs_pin );
    spi_master_write_then_read( current_eth->spi, &cmd, 1, buf, len );
    spi_master_deselect_device( enc28j60_cs_pin );

    return buf;
}

static void enc28j60_write_reg( uint8_t reg, uint16_t value ) {           // WCR - Write Control Register
    uint8_t cmd[ 2 ] = {
        ( uint8_t )( ENC28J60_WCR_CMD | ( reg & 0x1F ) ),
        ( uint8_t )value
    };

    spi_master_select_device( enc28j60_cs_pin );
    spi_master_write( current_eth->spi, cmd, 2 );
    spi_master_deselect_device( enc28j60_cs_pin );
}

static void enc28j60_write_mem( const uint8_t *buf, uint16_t len ) {      // WBM - Write Buffer Memory
    uint8_t cmd = ENC28J60_WBM_CMD;

    spi_master_select_device( enc28j60_cs_pin );
    spi_master_write( current_eth->spi, &cmd, 1 );
    spi_master_write( current_eth->spi, ( uint8_t * )buf, len );
    spi_master_deselect_device( enc28j60_cs_pin );
}

static void enc28j60_set_bit_reg( uint8_t reg, uint8_t mask ) {         // BSF - Bit Field Set
    uint8_t cmd[ 2 ] = {
        ( uint8_t )( ENC28J60_BFS_CMD | ( reg & 0x1F ) ),
        mask
    };

    spi_master_select_device( enc28j60_cs_pin );
    spi_master_write( current_eth->spi, cmd, 2 );
    spi_master_deselect_device( enc28j60_cs_pin );
}

static void enc28j60_clear_bit_reg( uint8_t reg, uint8_t mask ) {       // BFC - Bit Field Clear
    uint8_t cmd[ 2 ] = {
        ( uint8_t )( ENC28J60_BFC_CMD | ( reg & 0x1F ) ),
        mask
    };

    spi_master_select_device( enc28j60_cs_pin );
    spi_master_write( current_eth->spi, cmd, 2 );
    spi_master_deselect_device( enc28j60_cs_pin );
}

static void enc28j60_hw_reset( spi_ethernet_t *eth ) {
    digital_out_high( &eth->reset ); Delay_ms( 10 );
    digital_out_low( &eth->reset );  Delay_ms( 10 );
    digital_out_high( &eth->reset ); Delay_ms( 100 );
}

static void enc28j60_sw_reset( ) {
    uint8_t cmd = ENC28J60_SRC_CMD;

    spi_master_select_device( enc28j60_cs_pin );
    spi_master_write( current_eth->spi, &cmd, 1 );
    spi_master_deselect_device( enc28j60_cs_pin );
    Delay_ms( 2 );
}

static void enc28j60_wait_clk_ready( void ) {
    uint16_t tries = 0;

    current_bank = 0;

    enc28j60_select_bank( 0 );
    while ( !( enc28j60_read_reg( ESTAT ) & 0x01 ) ) {
        Delay_ms( 1 );
        if ( ++tries > 200 ) {
            break;
        }
    }
    Delay_ms( 10 );
}

static void enc28j60_init_rx_buffer( void ) {
    enc28j60_select_bank( 0 );
    enc28j60_write_reg( ERXSTL, RECEIVE_START & 0xFF );
    enc28j60_write_reg( ERXSTH, RECEIVE_START >> 8 );

    enc28j60_write_reg( ERXNDL, RECEIVE_END & 0xFF );
    enc28j60_write_reg( ERXNDH, RECEIVE_END >> 8 );

    enc28j60_write_reg( ERXRDPTL, RECEIVE_END & 0xFF );
    enc28j60_write_reg( ERXRDPTH, RECEIVE_END >> 8 );

    enc28j60_write_reg( ERDPTL, RECEIVE_START & 0xFF );
    enc28j60_write_reg( ERDPTH, RECEIVE_START >> 8 );
}

static void enc28j60_init_tx_buffer( void ) {
    enc28j60_select_bank( 0 );
    enc28j60_write_reg( ETXSTL, TRANSMIT_START & 0xFF );
    enc28j60_write_reg( ETXSTH, TRANSMIT_START >> 8 );
}

static void enc28j60_init_rx_filter( void ) {
    enc28j60_select_bank( 1 );
    enc28j60_write_reg( ERXFCON, 0xA1 );
}

static void enc28j60_init_mac( spi_ethernet_t *eth ) {
    enc28j60_select_bank( 2 );
    enc28j60_write_reg( MACON1, eth->fullDuplex ?
        ( MACON1_MARXEN | MACON1_TXPAUS | MACON1_RXPAUS ) :
        MACON1_MARXEN );

    enc28j60_write_reg( MACON3, eth->fullDuplex ?
        ( MACON3_PADCFG_SET | MACON3_TXCRCEN | MACON3_FULDPX ) :
        ( MACON3_PADCFG_SET | MACON3_TXCRCEN ) );

    enc28j60_write_reg( MACON4, eth->fullDuplex ? 0 : MACON4_DEFER );

    enc28j60_write_reg( MAMXFLL, ENC28J60_FRAME_SIZE & 0xFF );
    enc28j60_write_reg( MAMXFLH, ENC28J60_FRAME_SIZE >> 8 );

    enc28j60_write_reg( MABBIPG, eth->fullDuplex ? 0x15 : 0x12 );
    enc28j60_write_reg( MAIPGL, 0x12 );

    if ( !eth->fullDuplex )
        enc28j60_write_reg( MAIPGH, 0x0C );
}

static void enc28j60_init_mac_address( void ) {
    enc28j60_select_bank( 3 );
    enc28j60_write_reg( MAADR1, enc28j60_mac_addr[ 0 ] );
    enc28j60_write_reg( MAADR2, enc28j60_mac_addr[ 1 ] );
    enc28j60_write_reg( MAADR3, enc28j60_mac_addr[ 2 ] );
    enc28j60_write_reg( MAADR4, enc28j60_mac_addr[ 3 ] );
    enc28j60_write_reg( MAADR5, enc28j60_mac_addr[ 4 ] );
    enc28j60_write_reg( MAADR6, enc28j60_mac_addr[ 5 ] );
}

static void enc28j60_init_clock_output( void ) {
    enc28j60_select_bank( 3 );
    enc28j60_write_reg( ECOCON, 0x00 );
}

static void enc28j60_read_revision( void ) {
    enc28j60_select_bank( 3 );
    enc_hwRev = enc28j60_read_reg( EREVID );
}

void enc28j60_cfg_setup( enc28j60_cfg_t *cfg ) {
    cfg->miso = HAL_PIN_NC;
    cfg->mosi = HAL_PIN_NC;
    cfg->sck  = HAL_PIN_NC;
    cfg->cs   = HAL_PIN_NC;
    cfg->rst  = HAL_PIN_NC;

    cfg->spi_speed  = 1000000;
    cfg->spi_mode   = SPI_MASTER_MODE_0;

    cfg->full_duplex = 0;
}

uint8_t enc28j60_configure( spi_ethernet_t *eth, spi_master_t *spi, enc28j60_cfg_t *cfg ) {
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

    enc28j60_cs_pin = cfg->cs;
    spi_master_deselect_device( enc28j60_cs_pin );

    eth->spi = spi;
    memcpy( eth->mac, cfg->mac, 6 );
    memcpy( eth->ip, cfg->ip, 4 );
    eth->fullDuplex = cfg->full_duplex;

    return 0;
}

static void enc28j60_set_write_ptr( uint16_t addr ) {
    enc28j60_write_reg( EWRPTL, addr & 0xFF );
    enc28j60_write_reg( EWRPTH, addr >> 8 );
}

void enc28j60_phy_write( uint8_t phy_reg, uint16_t value ) {
    enc28j60_select_bank( 2 );
    enc28j60_write_reg( MIREGADR & 0x1F, phy_reg );
    enc28j60_write_reg( MIWRL    & 0x1F, ( uint8_t )( value & 0xFF ) );
    enc28j60_write_reg( MIWRH    & 0x1F, ( uint8_t )( value >> 8 ) );
    Delay_ms( 15 );
    enc28j60_select_bank( 2 ); 
    uint16_t tries = 0;
    while ( enc28j60_read_reg( MISTAT & 0x1F ) & MISTAT_BUSY ) {
        Delay_ms( 1 );
        if ( ++tries > ENC28J60_MIIM_TIMEOUT_MS ) break;
    }
}

void enc28j60_phy_read( uint8_t reg, uint8_t *low, uint8_t *high ) {
    enc28j60_select_bank( 2 );
    enc28j60_write_reg( MIREGADR & 0x1F, reg );
    enc28j60_write_reg( MICMD & 0x1F, 0x01 ); 
    Delay_ms( 15 );
    enc28j60_select_bank( 2 );
    uint16_t tries = 0;
    while ( enc28j60_read_reg( MISTAT& 0x1F ) & MISTAT_BUSY ) {
        Delay_ms( 1 );
        if ( ++tries > ENC28J60_MIIM_TIMEOUT_MS ) break;
    }
    enc28j60_write_reg( MICMD & 0x1F, 0x00 );
    *low  = enc28j60_read_reg( MIRDL & 0x1F );
    *high = enc28j60_read_reg( MIRDH & 0x1F );
}
