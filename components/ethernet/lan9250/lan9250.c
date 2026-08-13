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
 * @file spi_ethernet_lan9250.c
 * @brief SPI Ethernet Microchip LAN9250 Driver.
 */

#include "transport.h"
#include "lan9250.h"
#include "drv_spi_master.h"
#include <delays.h>
#include <string.h>

#define SPI_ETH_OK           0x00
#define SPI_ETH_INIT_ERROR   0xFF

#define LAN9250_WAIT_TIMEOUT_MS   500
#define LAN9250_BUSY_TIMEOUT_MS   50

pin_name_t lan9250_cs_pin;

static spi_ethernet_t *current_eth = NULL;
static uint8_t  lan9250_mac_addr[ 6 ];
static uint8_t  lan9250_ipaddr[ 4 ];
static uint32_t lan9250_id_rev;

// Scratch buffer shared by FIFO read/write helpers (avoids large stack usage)
static uint8_t lan9250_fifo_scratch[ LAN9250_FRAME_SIZE + 4 ];

static uint32_t lan9250_read_sys_reg( uint16_t addr );
static void     lan9250_write_sys_reg( uint16_t addr, uint32_t val );
static uint32_t lan9250_read_mac_reg( uint8_t addr );
static void     lan9250_write_mac_reg( uint8_t addr, uint32_t val );
static uint16_t lan9250_read_phy_reg( uint8_t addr );
static void     lan9250_write_phy_reg( uint8_t addr, uint16_t val );
static void     lan9250_write_fifo( uint16_t addr, uint8_t *buf, uint16_t len );
static void     lan9250_read_fifo( uint16_t addr, uint8_t *buf, uint16_t copy_len, uint16_t total_len );
static void     lan9250_hw_reset( spi_ethernet_t *eth );
static uint8_t  lan9250_wait_ready( void );
static void     lan9250_drop_packet( uint16_t length );

uint16_t lan9250_send_packet( spi_ethernet_t *eth, uint8_t *buf, uint16_t len );
uint16_t lan9250_read_packet( spi_ethernet_t *eth, uint8_t *buf, uint16_t len );
uint8_t  lan9250_packet_available( spi_ethernet_t *eth );

spi_ethernet_driver_t lan9250_driver = {
    .init            = lan9250_init,
    .send_packet     = lan9250_send_packet,
    .read_packet     = lan9250_read_packet,
    .available       = lan9250_packet_available,
    .get_link_status = lan9250_get_link_status,
    .set_mac         = lan9250_set_mac,
    .get_mac         = lan9250_get_mac,
    .set_ip          = lan9250_set_ip,
    .get_ip          = lan9250_get_ip
};

// Low-level SPI access (System CSR, 32-bit registers, LSB first)
static uint32_t lan9250_read_sys_reg( uint16_t addr ) {
    uint8_t hdr[ 3 ];
    uint8_t buf4[ 4 ] = { 0, 0, 0, 0 };

    hdr[ 0 ] = LAN9250_SPI_INSTR_READ;
    hdr[ 1 ] = ( uint8_t )( addr >> 8 );
    hdr[ 2 ] = ( uint8_t )( addr & 0xFF );

    spi_master_select_device( lan9250_cs_pin );
    spi_master_write_then_read( current_eth->spi, hdr, 3, buf4, 4 );
    spi_master_deselect_device( lan9250_cs_pin );

    return ( uint32_t )buf4[ 0 ] |
           ( ( uint32_t )buf4[ 1 ] << 8 ) |
           ( ( uint32_t )buf4[ 2 ] << 16 ) |
           ( ( uint32_t )buf4[ 3 ] << 24 );
}

static void lan9250_write_sys_reg( uint16_t addr, uint32_t val ) {
    uint8_t hdr[ 3 ];
    uint8_t buf4[ 4 ];

    hdr[ 0 ] = LAN9250_SPI_INSTR_WRITE;
    hdr[ 1 ] = ( uint8_t )( addr >> 8 );
    hdr[ 2 ] = ( uint8_t )( addr & 0xFF );

    buf4[ 0 ] = ( uint8_t )( val & 0xFF );
    buf4[ 1 ] = ( uint8_t )( ( val >> 8 ) & 0xFF );
    buf4[ 2 ] = ( uint8_t )( ( val >> 16 ) & 0xFF );
    buf4[ 3 ] = ( uint8_t )( ( val >> 24 ) & 0xFF );

    spi_master_select_device( lan9250_cs_pin );
    spi_master_write( current_eth->spi, hdr, 3 );
    spi_master_write( current_eth->spi, buf4, 4 );
    spi_master_deselect_device( lan9250_cs_pin );
}

// Host MAC CSR indirect access (through MAC_CSR_CMD / MAC_CSR_DATA)
static void lan9250_write_mac_reg( uint8_t addr, uint32_t val ) {
    uint32_t cmd;
    uint16_t tries = 0;

    lan9250_write_sys_reg( LAN9250_MAC_CSR_DATA, val );

    cmd = LAN9250_MAC_CSR_CMD_BUSY | LAN9250_MAC_CSR_CMD_WRITE |
          ( addr & LAN9250_MAC_CSR_CMD_ADDR );
    lan9250_write_sys_reg( LAN9250_MAC_CSR_CMD, cmd );

    while ( lan9250_read_sys_reg( LAN9250_MAC_CSR_CMD ) & LAN9250_MAC_CSR_CMD_BUSY ) {
        Delay_ms( 1 );
        if ( ++tries > LAN9250_BUSY_TIMEOUT_MS ) break;
    }
}

static uint32_t lan9250_read_mac_reg( uint8_t addr ) {
    uint32_t cmd;
    uint16_t tries = 0;

    cmd = LAN9250_MAC_CSR_CMD_BUSY | LAN9250_MAC_CSR_CMD_READ |
          ( addr & LAN9250_MAC_CSR_CMD_ADDR );
    lan9250_write_sys_reg( LAN9250_MAC_CSR_CMD, cmd );

    while ( lan9250_read_sys_reg( LAN9250_MAC_CSR_CMD ) & LAN9250_MAC_CSR_CMD_BUSY ) {
        Delay_ms( 1 );
        if ( ++tries > LAN9250_BUSY_TIMEOUT_MS ) break;
    }

    return lan9250_read_sys_reg( LAN9250_MAC_CSR_DATA );
}

// PHY register indirect access (through HMAC_MII_ACC / HMAC_MII_DATA)
static void lan9250_write_phy_reg( uint8_t addr, uint16_t val ) {
    uint32_t acc;
    uint16_t tries = 0;

    lan9250_write_mac_reg( LAN9250_HMAC_MII_DATA, val );

    acc = LAN9250_HMAC_MII_ACC_MIIBZY | LAN9250_HMAC_MII_ACC_MIIW_R |
          LAN9250_HMAC_MII_ACC_PHY_ADDR_DEFAULT |
          ( ( ( uint32_t )addr << LAN9250_HMAC_MII_ACC_MIIRINDA_SHIFT ) & 0x000007C0UL );
    lan9250_write_mac_reg( LAN9250_HMAC_MII_ACC, acc );

    while ( lan9250_read_mac_reg( LAN9250_HMAC_MII_ACC ) & LAN9250_HMAC_MII_ACC_MIIBZY ) {
        Delay_ms( 1 );
        if ( ++tries > LAN9250_BUSY_TIMEOUT_MS ) break;
    }
}

static uint16_t lan9250_read_phy_reg( uint8_t addr ) {
    uint32_t acc;
    uint16_t tries = 0;

    acc = LAN9250_HMAC_MII_ACC_MIIBZY | LAN9250_HMAC_MII_ACC_PHY_ADDR_DEFAULT |
          ( ( ( uint32_t )addr << LAN9250_HMAC_MII_ACC_MIIRINDA_SHIFT ) & 0x000007C0UL );
    lan9250_write_mac_reg( LAN9250_HMAC_MII_ACC, acc );

    while ( lan9250_read_mac_reg( LAN9250_HMAC_MII_ACC ) & LAN9250_HMAC_MII_ACC_MIIBZY ) {
        Delay_ms( 1 );
        if ( ++tries > LAN9250_BUSY_TIMEOUT_MS ) break;
    }

    return ( uint16_t )( lan9250_read_mac_reg( LAN9250_HMAC_MII_DATA ) & 0xFFFF );
}

// FIFO burst access (data FIFOs are always accessed in 4-byte words)
static void lan9250_write_fifo( uint16_t addr, uint8_t *buf, uint16_t len ) {
    uint8_t hdr[ 3 ];
    uint16_t aligned_len = ( uint16_t )( ( len + 3 ) & ~( ( uint16_t )3 ) );

    memset( lan9250_fifo_scratch, 0, aligned_len );
    memcpy( lan9250_fifo_scratch, buf, len );

    hdr[ 0 ] = LAN9250_SPI_INSTR_WRITE;
    hdr[ 1 ] = ( uint8_t )( addr >> 8 );
    hdr[ 2 ] = ( uint8_t )( addr & 0xFF );

    spi_master_select_device( lan9250_cs_pin );
    spi_master_write( current_eth->spi, hdr, 3 );
    spi_master_write( current_eth->spi, lan9250_fifo_scratch, aligned_len );
    spi_master_deselect_device( lan9250_cs_pin );
}

static void lan9250_read_fifo( uint16_t addr, uint8_t *buf, uint16_t copy_len, uint16_t total_len ) {
    uint8_t hdr[ 3 ];
    uint16_t aligned_len = ( uint16_t )( ( total_len + 3 ) & ~( ( uint16_t )3 ) );

    hdr[ 0 ] = LAN9250_SPI_INSTR_READ;
    hdr[ 1 ] = ( uint8_t )( addr >> 8 );
    hdr[ 2 ] = ( uint8_t )( addr & 0xFF );

    spi_master_select_device( lan9250_cs_pin );
    spi_master_write_then_read( current_eth->spi, hdr, 3, lan9250_fifo_scratch, aligned_len );
    spi_master_deselect_device( lan9250_cs_pin );

    memcpy( buf, lan9250_fifo_scratch, copy_len );
}

// Init
static void lan9250_hw_reset( spi_ethernet_t *eth ) {
    digital_out_high( &eth->reset ); Delay_ms( 10 );
    digital_out_low( &eth->reset );  Delay_ms( 10 );
    digital_out_high( &eth->reset ); Delay_ms( 50 );
}
static uint8_t lan9250_wait_ready( void ) {
    uint16_t tries = 0;

    while ( lan9250_read_sys_reg( LAN9250_BYTE_TEST ) != LAN9250_BYTE_TEST_DEFAULT ) {
        Delay_ms( 1 );
        if ( ++tries > LAN9250_WAIT_TIMEOUT_MS ) return 0;
    }

    tries = 0;
    while ( !( lan9250_read_sys_reg( LAN9250_HW_CFG ) & LAN9250_HW_CFG_DEVICE_READY ) ) {
        Delay_ms( 1 );
        if ( ++tries > LAN9250_WAIT_TIMEOUT_MS ) return 0;
    }

    return 1;
}

void lan9250_init( spi_ethernet_t *eth, spi_ethernet_driver_t *drv ) {
    uint32_t hmac_cr;
    uint32_t tx_cfg;

    current_eth = eth;

    lan9250_hw_reset( eth );

    // Wait for the SPI interface to become functional
    lan9250_wait_ready( );

    // Perform a digital (multi-module) reset, then wait again
    lan9250_write_sys_reg( LAN9250_RESET_CTL, LAN9250_RESET_CTL_DIGITAL_RST );
    lan9250_wait_ready( );

    // Read chip ID / revision for diagnostics (expected 0x9250xxxx)
    lan9250_id_rev = lan9250_read_sys_reg( LAN9250_ID_REV );

    memcpy( lan9250_mac_addr, eth->mac, 6 );
    memcpy( lan9250_ipaddr, &eth->ip, 4 );

    // Configure TX FIFO size (mandatory MBO bit set)
    lan9250_write_sys_reg( LAN9250_HW_CFG, LAN9250_HW_CFG_MBO | LAN9250_HW_CFG_TX_FIF_SZ_5KB );

    // Ignore TX status words (we poll TX_FIFO_INF instead)
    lan9250_write_sys_reg( LAN9250_TX_CFG, LAN9250_TX_CFG_TXSAO );

    // Program the MAC address into the hardware filter
    lan9250_set_mac( lan9250_mac_addr );

    // Configure the host MAC (duplex mode)
    hmac_cr = eth->fullDuplex ? LAN9250_HMAC_CR_FDPX : 0;
    lan9250_write_mac_reg( LAN9250_HMAC_CR, hmac_cr );

    // Enable the transmitter at the system level
    tx_cfg = lan9250_read_sys_reg( LAN9250_TX_CFG );
    tx_cfg |= LAN9250_TX_CFG_TX_ON;
    lan9250_write_sys_reg( LAN9250_TX_CFG, tx_cfg );

    // Enable the host MAC transmitter and receiver
    hmac_cr = lan9250_read_mac_reg( LAN9250_HMAC_CR );
    hmac_cr |= LAN9250_HMAC_CR_TXEN | LAN9250_HMAC_CR_RXEN;
    lan9250_write_mac_reg( LAN9250_HMAC_CR, hmac_cr );
}

// Data transfer
uint16_t lan9250_send_packet( spi_ethernet_t *eth, uint8_t *buf, uint16_t len ) {
    uint32_t free_space;
    uint32_t cmd_a;
    uint32_t cmd_b;

    current_eth = eth;

    free_space = lan9250_read_sys_reg( LAN9250_TX_FIFO_INF ) & LAN9250_TX_FIFO_INF_TXFREE;
    if ( free_space < ( uint32_t )( len + LAN9250_TX_CMD_SIZE ) )
        return 0;

    cmd_a = LAN9250_TX_CMD_A_BUFFER_ALIGN_4B | LAN9250_TX_CMD_A_START_OFFSET_0B |
            LAN9250_TX_CMD_A_FIRST_SEG | LAN9250_TX_CMD_A_LAST_SEG | ( len & 0x000007FFUL );
    lan9250_write_sys_reg( LAN9250_TX_DATA_FIFO, cmd_a );

    cmd_b = ( ( uint32_t )0 << LAN9250_TX_CMD_B_PACKET_TAG_SHIFT ) | ( len & 0x000007FFUL );
    lan9250_write_sys_reg( LAN9250_TX_DATA_FIFO, cmd_b );

    lan9250_write_fifo( LAN9250_TX_DATA_FIFO, buf, len );

    return len;
}

uint8_t lan9250_packet_available( spi_ethernet_t *eth ) {
    uint32_t rxsused;

    if ( !eth ) return 0;

    rxsused = ( lan9250_read_sys_reg( LAN9250_RX_FIFO_INF ) & LAN9250_RX_FIFO_INF_RXSUSED ) >> 16;
    return ( uint8_t )( ( rxsused > 0xFF ) ? 0xFF : rxsused );
}

static void lan9250_drop_packet( uint16_t length ) {
    uint16_t i;
    uint16_t tries = 0;

    if ( length >= 16 ) {
        lan9250_write_sys_reg( LAN9250_RX_DP_CTRL, LAN9250_RX_DP_CTRL_RX_FFWD );
        while ( lan9250_read_sys_reg( LAN9250_RX_DP_CTRL ) & LAN9250_RX_DP_CTRL_RX_FFWD ) {
            Delay_ms( 1 );
            if ( ++tries > LAN9250_BUSY_TIMEOUT_MS ) break;
        }
    }
    else {
        for ( i = 0; i < length; i += 4 )
            lan9250_read_sys_reg( LAN9250_RX_DATA_FIFO );
    }
}

uint16_t lan9250_read_packet( spi_ethernet_t *eth, uint8_t *buf, uint16_t max_len ) {
    uint32_t rxsused;
    uint32_t status;
    uint16_t length;
    uint16_t copy_len;

    current_eth = eth;

    rxsused = ( lan9250_read_sys_reg( LAN9250_RX_FIFO_INF ) & LAN9250_RX_FIFO_INF_RXSUSED ) >> 16;
    if ( rxsused == 0 ) return 0;

    status = lan9250_read_sys_reg( LAN9250_RX_STATUS_FIFO );
    length = ( uint16_t )( ( status & LAN9250_RX_STS_PACKET_LEN ) >> 16 );

    if ( status & LAN9250_RX_STS_ERROR_STATUS ) {
        lan9250_drop_packet( length );
        return 0;
    }

    if ( length == 0 || length > LAN9250_FRAME_SIZE ) {
        lan9250_drop_packet( length );
        return 0;
    }

    copy_len = ( length > max_len ) ? max_len : length;
    lan9250_read_fifo( LAN9250_RX_DATA_FIFO, buf, copy_len, length );

    return copy_len;
}

// Link / identification
uint8_t lan9250_get_link_status( void ) {
    uint16_t status;

    if ( !current_eth ) return 0;

    /* Any link failure is latched; reading twice returns the actual status */
    status = lan9250_read_phy_reg( LAN9250_PHY_BASIC_STATUS );
    status = lan9250_read_phy_reg( LAN9250_PHY_BASIC_STATUS );

    return ( status & LAN9250_PHY_BASIC_STATUS_LINK_STATUS ) ? 1 : 0;
}

uint8_t lan9250_get_rev( void ) {
    return ( uint8_t )( lan9250_id_rev & 0xFF );
}

uint32_t lan9250_get_id_rev( void ) {
    return lan9250_id_rev;
}

// Addressing
int lan9250_set_mac( uint8_t mac[ 6 ] ) {
    uint32_t addrl;
    uint32_t addrh;

    memcpy( lan9250_mac_addr, mac, 6 );

    addrl = ( uint32_t )mac[ 0 ] | ( ( uint32_t )mac[ 1 ] << 8 ) |
            ( ( uint32_t )mac[ 2 ] << 16 ) | ( ( uint32_t )mac[ 3 ] << 24 );
    addrh = ( uint32_t )mac[ 4 ] | ( ( uint32_t )mac[ 5 ] << 8 );

    lan9250_write_mac_reg( LAN9250_HMAC_ADDRL, addrl );
    lan9250_write_mac_reg( LAN9250_HMAC_ADDRH, addrh );

    return 1;
}

int lan9250_get_mac( uint8_t mac[ 6 ] ) {
    memcpy( mac, lan9250_mac_addr, 6 );
    return 1;
}

int lan9250_set_ip( uint8_t ip[ 4 ] ) {
    memcpy( lan9250_ipaddr, ip, 4 );
    return 1;
}

int lan9250_get_ip( uint8_t ip[ 4 ] ) {
    memcpy( ip, lan9250_ipaddr, 4 );
    return 1;
}

// Config / setup
void lan9250_cfg_setup( lan9250_cfg_t *cfg ) {
    cfg->miso = HAL_PIN_NC;
    cfg->mosi = HAL_PIN_NC;
    cfg->sck  = HAL_PIN_NC;
    cfg->cs   = HAL_PIN_NC;
    cfg->rst  = HAL_PIN_NC;

    cfg->spi_speed = 1000000;
    cfg->spi_mode  = SPI_MASTER_MODE_0;

    cfg->full_duplex = 0;
}

uint8_t lan9250_configure( spi_ethernet_t *eth, spi_master_t *spi, lan9250_cfg_t *cfg ) {
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

    lan9250_cs_pin = cfg->cs;
    spi_master_deselect_device( lan9250_cs_pin );

    eth->spi = spi;
    memcpy( eth->mac, cfg->mac, 6 );
    memcpy( &eth->ip, cfg->ip, 4 );
    eth->fullDuplex = cfg->full_duplex;

    return 0;
}

// ----------------------------------------------------------------------- END
