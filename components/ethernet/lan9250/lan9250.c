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
 * @file lan9250.c
 * @brief SPI Ethernet Microchip LAN9250 Driver.
 */

#include "lan9250.h"
#include <delays.h>
#include <string.h>

#define LAN9250_WAIT_TIMEOUT_MS   500
#define LAN9250_BUSY_TIMEOUT_MS   50

#define LAN9250_CTX( eth )        ( ( lan9250_ctx_t * )( eth )->driver_ctx )

static lan9250_ctx_t lan9250_default_ctx;

// FIFO scratch buffer, only used within a single call so shared by all devices
static uint8_t lan9250_fifo_scratch[ LAN9250_FRAME_SIZE + 4 ];

static uint32_t lan9250_read_sys_reg( eth_transport_t *eth, uint16_t addr );
static void     lan9250_write_sys_reg( eth_transport_t *eth, uint16_t addr, uint32_t val );
static uint32_t lan9250_read_mac_reg( eth_transport_t *eth, uint8_t addr );
static void     lan9250_write_mac_reg( eth_transport_t *eth, uint8_t addr, uint32_t val );
static uint16_t lan9250_read_phy_reg( eth_transport_t *eth, uint8_t addr );
static void     lan9250_write_fifo( eth_transport_t *eth, uint16_t addr, uint8_t *buf, uint16_t len );
static void     lan9250_read_fifo( eth_transport_t *eth, uint16_t addr, uint8_t *buf, uint16_t copy_len, uint16_t total_len );
static void     lan9250_hw_reset( eth_transport_t *eth );
static uint8_t  lan9250_wait_ready( eth_transport_t *eth );
static void     lan9250_drop_packet( eth_transport_t *eth, uint16_t length );

eth_transport_driver_t lan9250_driver = {
    .init            = lan9250_init,
    .send_packet     = lan9250_send_packet,
    .read_packet     = lan9250_read_packet,
    .available       = lan9250_packet_available,
    .get_link_status = lan9250_get_link_status,
    .set_mac         = lan9250_set_mac
};

// Low-level SPI access (System CSR, 32-bit registers, LSB first)
static uint32_t lan9250_read_sys_reg( eth_transport_t *eth, uint16_t addr ) {
    uint8_t hdr[ 3 ];
    uint8_t buf4[ 4 ] = { 0, 0, 0, 0 };

    hdr[ 0 ] = LAN9250_SPI_INSTR_READ;
    hdr[ 1 ] = ( uint8_t )( addr >> 8 );
    hdr[ 2 ] = ( uint8_t )( addr & 0xFF );

    ( void )eth_transport_bus_read( eth, hdr, 3, buf4, 4 );

    return ( uint32_t )buf4[ 0 ] |
           ( ( uint32_t )buf4[ 1 ] << 8 ) |
           ( ( uint32_t )buf4[ 2 ] << 16 ) |
           ( ( uint32_t )buf4[ 3 ] << 24 );
}

static void lan9250_write_sys_reg( eth_transport_t *eth, uint16_t addr, uint32_t val ) {
    uint8_t hdr[ 3 ];
    uint8_t buf4[ 4 ];

    hdr[ 0 ] = LAN9250_SPI_INSTR_WRITE;
    hdr[ 1 ] = ( uint8_t )( addr >> 8 );
    hdr[ 2 ] = ( uint8_t )( addr & 0xFF );

    buf4[ 0 ] = ( uint8_t )( val & 0xFF );
    buf4[ 1 ] = ( uint8_t )( ( val >> 8 ) & 0xFF );
    buf4[ 2 ] = ( uint8_t )( ( val >> 16 ) & 0xFF );
    buf4[ 3 ] = ( uint8_t )( ( val >> 24 ) & 0xFF );

    ( void )eth_transport_bus_write( eth, hdr, 3, buf4, 4 );
}

// Host MAC CSR indirect access (through MAC_CSR_CMD / MAC_CSR_DATA)
static void lan9250_write_mac_reg( eth_transport_t *eth, uint8_t addr, uint32_t val ) {
    uint32_t cmd;
    uint16_t tries = 0;

    lan9250_write_sys_reg( eth, LAN9250_MAC_CSR_DATA, val );

    cmd = LAN9250_MAC_CSR_CMD_BUSY | LAN9250_MAC_CSR_CMD_WRITE |
          ( addr & LAN9250_MAC_CSR_CMD_ADDR );
    lan9250_write_sys_reg( eth, LAN9250_MAC_CSR_CMD, cmd );

    while ( lan9250_read_sys_reg( eth, LAN9250_MAC_CSR_CMD ) & LAN9250_MAC_CSR_CMD_BUSY ) {
        Delay_ms( 1 );
        if ( ++tries > LAN9250_BUSY_TIMEOUT_MS ) break;
    }
}

static uint32_t lan9250_read_mac_reg( eth_transport_t *eth, uint8_t addr ) {
    uint32_t cmd;
    uint16_t tries = 0;

    cmd = LAN9250_MAC_CSR_CMD_BUSY | LAN9250_MAC_CSR_CMD_READ |
          ( addr & LAN9250_MAC_CSR_CMD_ADDR );
    lan9250_write_sys_reg( eth, LAN9250_MAC_CSR_CMD, cmd );

    while ( lan9250_read_sys_reg( eth, LAN9250_MAC_CSR_CMD ) & LAN9250_MAC_CSR_CMD_BUSY ) {
        Delay_ms( 1 );
        if ( ++tries > LAN9250_BUSY_TIMEOUT_MS ) break;
    }

    return lan9250_read_sys_reg( eth, LAN9250_MAC_CSR_DATA );
}

// PHY register indirect access (through HMAC_MII_ACC / HMAC_MII_DATA)
static uint16_t lan9250_read_phy_reg( eth_transport_t *eth, uint8_t addr ) {
    uint32_t acc;
    uint16_t tries = 0;

    acc = LAN9250_HMAC_MII_ACC_MIIBZY | LAN9250_HMAC_MII_ACC_PHY_ADDR_DEFAULT |
          ( ( ( uint32_t )addr << LAN9250_HMAC_MII_ACC_MIIRINDA_SHIFT ) & 0x000007C0UL );
    lan9250_write_mac_reg( eth, LAN9250_HMAC_MII_ACC, acc );

    while ( lan9250_read_mac_reg( eth, LAN9250_HMAC_MII_ACC ) & LAN9250_HMAC_MII_ACC_MIIBZY ) {
        Delay_ms( 1 );
        if ( ++tries > LAN9250_BUSY_TIMEOUT_MS ) break;
    }

    return ( uint16_t )( lan9250_read_mac_reg( eth, LAN9250_HMAC_MII_DATA ) & 0xFFFF );
}

// FIFO burst access (data FIFOs are always accessed in 4-byte words)
static void lan9250_write_fifo( eth_transport_t *eth, uint16_t addr, uint8_t *buf, uint16_t len ) {
    uint8_t hdr[ 3 ];
    uint16_t aligned_len = ( uint16_t )( ( len + 3 ) & ~( ( uint16_t )3 ) );

    memset( lan9250_fifo_scratch, 0, aligned_len );
    memcpy( lan9250_fifo_scratch, buf, len );

    hdr[ 0 ] = LAN9250_SPI_INSTR_WRITE;
    hdr[ 1 ] = ( uint8_t )( addr >> 8 );
    hdr[ 2 ] = ( uint8_t )( addr & 0xFF );

    ( void )eth_transport_bus_write( eth, hdr, 3, lan9250_fifo_scratch, aligned_len );
}

static void lan9250_read_fifo( eth_transport_t *eth, uint16_t addr, uint8_t *buf, uint16_t copy_len, uint16_t total_len ) {
    uint8_t hdr[ 3 ];
    uint16_t aligned_len = ( uint16_t )( ( total_len + 3 ) & ~( ( uint16_t )3 ) );

    hdr[ 0 ] = LAN9250_SPI_INSTR_READ;
    hdr[ 1 ] = ( uint8_t )( addr >> 8 );
    hdr[ 2 ] = ( uint8_t )( addr & 0xFF );

    ( void )eth_transport_bus_read( eth, hdr, 3, lan9250_fifo_scratch, aligned_len );

    memcpy( buf, lan9250_fifo_scratch, copy_len );
}

// Init
static void lan9250_hw_reset( eth_transport_t *eth ) {
    digital_out_high( &eth->reset ); Delay_ms( 10 );
    digital_out_low( &eth->reset );  Delay_ms( 10 );
    digital_out_high( &eth->reset ); Delay_ms( 50 );
}

static uint8_t lan9250_wait_ready( eth_transport_t *eth ) {
    uint16_t tries = 0;

    while ( lan9250_read_sys_reg( eth, LAN9250_BYTE_TEST ) != LAN9250_BYTE_TEST_DEFAULT ) {
        Delay_ms( 1 );
        if ( ++tries > LAN9250_WAIT_TIMEOUT_MS ) return 0;
    }

    tries = 0;
    while ( !( lan9250_read_sys_reg( eth, LAN9250_HW_CFG ) & LAN9250_HW_CFG_DEVICE_READY ) ) {
        Delay_ms( 1 );
        if ( ++tries > LAN9250_WAIT_TIMEOUT_MS ) return 0;
    }

    return 1;
}

err_t lan9250_init( eth_transport_t *eth ) {
    uint32_t hmac_cr;
    uint32_t tx_cfg;

    if ( !eth || !eth->driver_ctx ) return ETH_TRANSPORT_ERROR;

    lan9250_hw_reset( eth );

    // Wait for the SPI interface to become functional
    lan9250_wait_ready( eth );

    // Perform a digital (multi-module) reset, then wait again
    lan9250_write_sys_reg( eth, LAN9250_RESET_CTL, LAN9250_RESET_CTL_DIGITAL_RST );
    lan9250_wait_ready( eth );

    // Read chip ID / revision for diagnostics (expected 0x9250xxxx)
    LAN9250_CTX( eth )->id_rev = lan9250_read_sys_reg( eth, LAN9250_ID_REV );

    // Configure TX FIFO size (mandatory MBO bit set)
    lan9250_write_sys_reg( eth, LAN9250_HW_CFG, LAN9250_HW_CFG_MBO | LAN9250_HW_CFG_TX_FIF_SZ_5KB );

    // Ignore TX status words (we poll TX_FIFO_INF instead)
    lan9250_write_sys_reg( eth, LAN9250_TX_CFG, LAN9250_TX_CFG_TXSAO );

    // Program the MAC address into the hardware filter
    lan9250_set_mac( eth, eth->mac );

    // Configure the host MAC (duplex mode)
    hmac_cr = eth->full_duplex ? LAN9250_HMAC_CR_FDPX : 0;
    lan9250_write_mac_reg( eth, LAN9250_HMAC_CR, hmac_cr );

    // Enable the transmitter at the system level
    tx_cfg = lan9250_read_sys_reg( eth, LAN9250_TX_CFG );
    tx_cfg |= LAN9250_TX_CFG_TX_ON;
    lan9250_write_sys_reg( eth, LAN9250_TX_CFG, tx_cfg );

    // Enable the host MAC transmitter and receiver
    hmac_cr = lan9250_read_mac_reg( eth, LAN9250_HMAC_CR );
    hmac_cr |= LAN9250_HMAC_CR_TXEN | LAN9250_HMAC_CR_RXEN;
    lan9250_write_mac_reg( eth, LAN9250_HMAC_CR, hmac_cr );

    return ETH_TRANSPORT_SUCCESS;
}

// Data transfer
uint16_t lan9250_send_packet( eth_transport_t *eth, uint8_t *buf, uint16_t len ) {
    uint32_t free_space;
    uint32_t cmd_a;
    uint32_t cmd_b;

    if ( len > LAN9250_FRAME_SIZE ) return 0;

    free_space = lan9250_read_sys_reg( eth, LAN9250_TX_FIFO_INF ) & LAN9250_TX_FIFO_INF_TXFREE;
    if ( free_space < ( uint32_t )( len + LAN9250_TX_CMD_SIZE ) )
        return 0;

    cmd_a = LAN9250_TX_CMD_A_BUFFER_ALIGN_4B | LAN9250_TX_CMD_A_START_OFFSET_0B |
            LAN9250_TX_CMD_A_FIRST_SEG | LAN9250_TX_CMD_A_LAST_SEG | ( len & 0x000007FFUL );
    lan9250_write_sys_reg( eth, LAN9250_TX_DATA_FIFO, cmd_a );

    cmd_b = ( ( uint32_t )0 << LAN9250_TX_CMD_B_PACKET_TAG_SHIFT ) | ( len & 0x000007FFUL );
    lan9250_write_sys_reg( eth, LAN9250_TX_DATA_FIFO, cmd_b );

    lan9250_write_fifo( eth, LAN9250_TX_DATA_FIFO, buf, len );

    return len;
}

uint8_t lan9250_packet_available( eth_transport_t *eth ) {
    uint32_t rxsused;

    if ( !eth ) return 0;

    rxsused = ( lan9250_read_sys_reg( eth, LAN9250_RX_FIFO_INF ) & LAN9250_RX_FIFO_INF_RXSUSED ) >> 16;
    return ( uint8_t )( ( rxsused > 0xFF ) ? 0xFF : rxsused );
}

static void lan9250_drop_packet( eth_transport_t *eth, uint16_t length ) {
    uint16_t i;
    uint16_t tries = 0;

    if ( length >= 16 ) {
        lan9250_write_sys_reg( eth, LAN9250_RX_DP_CTRL, LAN9250_RX_DP_CTRL_RX_FFWD );
        while ( lan9250_read_sys_reg( eth, LAN9250_RX_DP_CTRL ) & LAN9250_RX_DP_CTRL_RX_FFWD ) {
            Delay_ms( 1 );
            if ( ++tries > LAN9250_BUSY_TIMEOUT_MS ) break;
        }
    }
    else {
        for ( i = 0; i < length; i += 4 )
            lan9250_read_sys_reg( eth, LAN9250_RX_DATA_FIFO );
    }
}

uint16_t lan9250_read_packet( eth_transport_t *eth, uint8_t *buf, uint16_t max_len ) {
    uint32_t status;
    uint16_t length;
    uint16_t copy_len;

    if ( !lan9250_packet_available( eth ) ) return 0;

    status = lan9250_read_sys_reg( eth, LAN9250_RX_STATUS_FIFO );
    length = ( uint16_t )( ( status & LAN9250_RX_STS_PACKET_LEN ) >> 16 );

    if ( status & LAN9250_RX_STS_ERROR_STATUS ) {
        lan9250_drop_packet( eth, length );
        return 0;
    }

    if ( length == 0 || length > LAN9250_FRAME_SIZE ) {
        lan9250_drop_packet( eth, length );
        return 0;
    }

    copy_len = ( length > max_len ) ? max_len : length;
    lan9250_read_fifo( eth, LAN9250_RX_DATA_FIFO, buf, copy_len, length );

    return copy_len;
}

// Link / identification
uint8_t lan9250_get_link_status( eth_transport_t *eth ) {
    uint16_t status;

    if ( !eth ) return 0;

    // Any link failure is latched; reading twice returns the actual status
    status = lan9250_read_phy_reg( eth, LAN9250_PHY_BASIC_STATUS );
    status = lan9250_read_phy_reg( eth, LAN9250_PHY_BASIC_STATUS );

    return ( status & LAN9250_PHY_BASIC_STATUS_LINK_STATUS ) ? 1 : 0;
}

uint8_t lan9250_get_rev( eth_transport_t *eth ) {
    return ( uint8_t )( lan9250_get_id_rev( eth ) & 0xFF );
}

uint32_t lan9250_get_id_rev( eth_transport_t *eth ) {
    if ( !eth || !eth->driver_ctx ) return 0;
    return LAN9250_CTX( eth )->id_rev;
}

// Addressing
err_t lan9250_set_mac( eth_transport_t *eth, uint8_t *mac ) {
    uint32_t addrl;
    uint32_t addrh;

    addrl = ( uint32_t )mac[ 0 ] | ( ( uint32_t )mac[ 1 ] << 8 ) |
            ( ( uint32_t )mac[ 2 ] << 16 ) | ( ( uint32_t )mac[ 3 ] << 24 );
    addrh = ( uint32_t )mac[ 4 ] | ( ( uint32_t )mac[ 5 ] << 8 );

    lan9250_write_mac_reg( eth, LAN9250_HMAC_ADDRL, addrl );
    lan9250_write_mac_reg( eth, LAN9250_HMAC_ADDRH, addrh );

    return ETH_TRANSPORT_SUCCESS;
}

// Config / setup
void lan9250_cfg_setup( lan9250_cfg_t *cfg ) {
    eth_bus_spi_cfg_setup( &cfg->bus );
    eth_transport_cfg_setup( &cfg->eth );
}

err_t lan9250_configure( eth_transport_t *eth, eth_bus_spi_t *bus, lan9250_cfg_t *cfg ) {
    if ( !eth || !cfg ) return ETH_TRANSPORT_ERROR;
    if ( !eth->driver_ctx )
        eth->driver_ctx = &lan9250_default_ctx;
    return eth_bus_spi_configure( eth, bus, &cfg->bus, &cfg->eth );
}

// ----------------------------------------------------------------------- END
