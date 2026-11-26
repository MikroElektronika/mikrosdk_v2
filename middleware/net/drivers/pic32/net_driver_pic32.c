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
 * @file net_driver_pic32.c
 * @brief PIC32MX / PIC32MZ Ethernet controller driver for the mikroSDK network layer.
 * @details Written from the PIC32MZ EF (DS60001320) and PIC32MX5XX/6XX/7XX
 * (DS60001156) data sheets and the PIC32
 * Family Reference Manual, Section 35 "Ethernet Controller". Register and bit
 * names are those of the device header (mcu.h).
 *
 * DMA: the controller reads and writes descriptors and buffers in RAM, and the
 * PIC32MZ has a data cache (PIC32MX has none). Both therefore live in uncached memory (XC32's
 * "coherent" attribute, KSEG1); the controller is given physical addresses.
 *
 * Descriptor format (5 words, linked with NPV):
 *   word 0  bit 7 EOWN (1: owned by the controller), bit 8 NPV (word 4 valid),
 *           bits 26:16 byte count, bit 30 EOP, bit 31 SOP
 *   word 1  physical address of the buffer
 *   word 2,3 status (TSV / RSV), not used: the receive filter only accepts
 *           frames with a correct CRC
 *   word 4  physical address of the next descriptor
 */

#include <string.h>

#include "net_driver_pic32.h"
#include "mcu.h"
#include "delays.h"

/* ------------------------------------------------------------ Registers --- */

/* ETHCON1 */
#define ETHCON1_ON          ( 1ul << 15 )
#define ETHCON1_TXRTS       ( 1ul << 9 )
#define ETHCON1_RXEN        ( 1ul << 8 )
#define ETHCON1_BUFCDEC     ( 1ul << 0 )
/* ETHSTAT */
#define ETHSTAT_BUSY        ( 1ul << 7 )
#define ETHSTAT_BUFCNT_MASK ( 0xFFul << 16 )
/* ETHIRQ */
#define ETHIRQ_RXOVFLW      ( 1ul << 0 )
#define ETHIRQ_RXBUFNA      ( 1ul << 1 )
/* ETHRXFC */
#define ETHRXFC_BCEN        ( 1ul << 0 )
#define ETHRXFC_MCEN        ( 1ul << 1 )
#define ETHRXFC_UCEN        ( 1ul << 3 )
#define ETHRXFC_CRCOKEN     ( 1ul << 6 )
/* EMAC1CFG1 */
#define EMAC1CFG1_RXENABLE  ( 1ul << 0 )
#define EMAC1CFG1_SOFTRESET ( 1ul << 15 )
/* EMAC1CFG2 */
#define EMAC1CFG2_FULLDPLX  ( 1ul << 0 )
#define EMAC1CFG2_CRCENABLE ( 1ul << 4 )
#define EMAC1CFG2_PADENABLE ( 1ul << 5 )
#define EMAC1CFG2_EXCESSDFR ( 1ul << 14 )
/* EMAC1SUPP */
#define EMAC1SUPP_SPEEDRMII ( 1ul << 8 )
#define EMAC1SUPP_RESETRMII ( 1ul << 11 )
/* EMAC1MCFG */
#define EMAC1MCFG_RESETMGMT ( 1ul << 15 )
#define EMAC1MCFG_CLKSEL_50 ( 0xAul << 2 )  /* MDC = TPBCLK5 / 50: 2 MHz at 100 MHz, MDIO allows 2.5 MHz */
/* EMAC1MCMD */
#define EMAC1MCMD_READ      ( 1ul << 0 )
/* EMAC1MIND */
#define EMAC1MIND_MIIMBUSY  ( 1ul << 0 )

/* Inter-packet gaps (data sheet recommendations). */
#define IPGT_FULL_DUPLEX    0x15u
#define IPGT_HALF_DUPLEX    0x12u
#define IPGR_DEFAULT        0x0C12u
#define MAX_FRAME           1518u

/* --------------------------------------------------------- Descriptors --- */

#define DCPT_EOWN           ( 1ul << 7 )
#define DCPT_NPV            ( 1ul << 8 )
#define DCPT_EOP            ( 1ul << 30 )
#define DCPT_SOP            ( 1ul << 31 )
#define DCPT_COUNT( hdr )   ( ( ( hdr ) >> 16 ) & 0x7FFul )

#define RX_BUF_SIZE         1536u           /* multiple of 16, holds a full frame */
#define TX_BUF_SIZE         1536u

typedef struct
{
    volatile uint32_t hdr;
    volatile uint32_t buffer;
    volatile uint32_t status[ 2 ];
    volatile uint32_t next;
} dcpt_t;

#if defined( __XC32 )
#define DMA_MEMORY __attribute__(( coherent, aligned( 16 ) ))
#else
#define DMA_MEMORY __attribute__(( aligned( 16 ) ))     /* syntax checks on other compilers */
#endif

static DMA_MEMORY dcpt_t rx_dcpt[ NET_PIC32_RX_BUFFERS ];
static DMA_MEMORY dcpt_t tx_dcpt[ 2 ];      /* one frame, then a stop descriptor */
static DMA_MEMORY uint8_t rx_buf[ NET_PIC32_RX_BUFFERS ][ RX_BUF_SIZE ];
static DMA_MEMORY uint8_t tx_buf[ TX_BUF_SIZE ];

/* Physical address of a kernel virtual address (KSEG0 or KSEG1). */
#define PHYS( p )           ( ( uint32_t )( p ) & 0x1FFFFFFFul )

/* Bounded waits on hardware flags. */
#define WAIT_LOOPS          100000ul

/* ---------------------------------------------------------------- State --- */

static struct
{
    net_pic32_cfg_t cfg;
    net_phy_t phy;
    uint8_t rx_next;
    bool link;
} eth;

/* ----------------------------------------------------------------- MDIO --- */

static int32_t mdio_wait( void )
{
    for ( uint32_t i = 0; i < WAIT_LOOPS; i++ )
    {
        if ( !( EMAC1MIND & EMAC1MIND_MIIMBUSY ) )
        {
            return 0;
        }
    }
    return -1;
}

static int32_t mdio_read( void *ctx, uint8_t addr, uint8_t reg, uint16_t *value )
{
    ( void )ctx;
    if ( mdio_wait() )
    {
        return -1;
    }
    EMAC1MADR = ( ( uint32_t )( addr & 0x1F ) << 8 ) | ( reg & 0x1F );
    EMAC1MCMD = EMAC1MCMD_READ;
    /* MIIMBUSY is set a few clocks after the command: do not test it at once. */
    __asm__ volatile ( "nop\n\tnop\n\tnop\n\tnop\n\tnop\n\tnop\n\tnop\n\tnop" );
    int32_t err = mdio_wait();
    EMAC1MCMD = 0;
    *value = ( uint16_t )EMAC1MRDD;
    return err;
}

static int32_t mdio_write( void *ctx, uint8_t addr, uint8_t reg, uint16_t value )
{
    ( void )ctx;
    if ( mdio_wait() )
    {
        return -1;
    }
    EMAC1MADR = ( ( uint32_t )( addr & 0x1F ) << 8 ) | ( reg & 0x1F );
    EMAC1MWTD = value;      /* writing the data starts the transfer */
    __asm__ volatile ( "nop\n\tnop\n\tnop\n\tnop\n\tnop\n\tnop\n\tnop\n\tnop" );
    return mdio_wait();
}

/* ----------------------------------------------------------- Controller --- */

static void descriptors_init( void )
{
    for ( uint8_t i = 0; i < NET_PIC32_RX_BUFFERS; i++ )
    {
        rx_dcpt[ i ].buffer = PHYS( rx_buf[ i ] );
        rx_dcpt[ i ].status[ 0 ] = 0;
        rx_dcpt[ i ].status[ 1 ] = 0;
        rx_dcpt[ i ].next = PHYS( &rx_dcpt[ ( i + 1 ) % NET_PIC32_RX_BUFFERS ] );
        rx_dcpt[ i ].hdr = DCPT_EOWN | DCPT_NPV;
    }
    eth.rx_next = 0;

    tx_dcpt[ 0 ].buffer = PHYS( tx_buf );
    tx_dcpt[ 0 ].next = PHYS( &tx_dcpt[ 1 ] );
    tx_dcpt[ 0 ].hdr = 0;
    tx_dcpt[ 1 ].buffer = PHYS( tx_buf );
    tx_dcpt[ 1 ].next = PHYS( &tx_dcpt[ 0 ] );
    tx_dcpt[ 1 ].hdr = 0;   /* not owned: the controller stops here */
}

/* MAC speed and duplex after auto-negotiation. */
static void mac_set_mode( const net_phy_mode_t *mode )
{
    uint32_t cfg2 = EMAC1CFG2_PADENABLE | EMAC1CFG2_CRCENABLE | EMAC1CFG2_EXCESSDFR;
    if ( mode->full_duplex )
    {
        cfg2 |= EMAC1CFG2_FULLDPLX;
    }
    EMAC1CFG2 = cfg2;
    EMAC1IPGT = mode->full_duplex ? IPGT_FULL_DUPLEX : IPGT_HALF_DUPLEX;
    if ( mode->speed_100 )
    {
        EMAC1SUPPSET = EMAC1SUPP_SPEEDRMII;
    }
    else
    {
        EMAC1SUPPCLR = EMAC1SUPP_SPEEDRMII;
    }
}

static int32_t pic32_init( void *ctx, const uint8_t *mac )
{
    ( void )ctx;

    if ( eth.cfg.pins_init )
    {
        eth.cfg.pins_init();
    }

    /* Hardware reset of the PHY (LAN8720: at least 100 us low; 1 ms used). */
    if ( HAL_PIN_NC != eth.cfg.phy_reset )
    {
        digital_out_t rst;
        if ( digital_out_init( &rst, eth.cfg.phy_reset ) == DIGITAL_OUT_SUCCESS )
        {
            digital_out_low( &rst );
            Delay_ms( 1 );
            digital_out_high( &rst );
            Delay_ms( 10 );     /* PHY ready after reset */
        }
    }

    /* 1. Stop the controller and clear its state. */
    ETHCON1CLR = ETHCON1_ON | ETHCON1_TXRTS | ETHCON1_RXEN;
    for ( uint32_t i = 0; ( i < WAIT_LOOPS ) && ( ETHSTAT & ETHSTAT_BUSY ); i++ )
    {
    }
    ETHIEN = 0;
    ETHIRQ = 0;
    ETHTXST = 0;
    ETHRXST = 0;

    /* 2. Switch it on (the MAC registers need the module on), reset the MAC. */
    ETHCON1SET = ETHCON1_ON;
    EMAC1CFG1 = EMAC1CFG1_SOFTRESET;
    EMAC1CFG1 = 0;
    EMAC1SUPPSET = EMAC1SUPP_RESETRMII;
    EMAC1SUPPCLR = EMAC1SUPP_RESETRMII;
    EMAC1MCFG = EMAC1MCFG_RESETMGMT;
    EMAC1MCFG = EMAC1MCFG_CLKSEL_50;

    /* 3. MAC: receive on, pad and CRC on transmit, full duplex 100 Mbit/s until
     *    the PHY reports the negotiated mode. */
    EMAC1CFG1 = EMAC1CFG1_RXENABLE;
    net_phy_mode_t initial = { true, true };
    mac_set_mode( &initial );
    EMAC1IPGR = IPGR_DEFAULT;
    EMAC1MAXF = MAX_FRAME;

    /* Station address: STNADDR1 (first byte on the wire) is the low byte of SA2. */
    EMAC1SA2 = ( uint32_t )mac[ 0 ] | ( ( uint32_t )mac[ 1 ] << 8 );
    EMAC1SA1 = ( uint32_t )mac[ 2 ] | ( ( uint32_t )mac[ 3 ] << 8 );
    EMAC1SA0 = ( uint32_t )mac[ 4 ] | ( ( uint32_t )mac[ 5 ] << 8 );

    /* 4. PHY: reset and start auto-negotiation. */
    eth.phy.ctx = NULL;
    eth.phy.addr = eth.cfg.phy_addr;
    eth.phy.read = mdio_read;
    eth.phy.write = mdio_write;
    if ( net_phy_init( &eth.phy ) )
    {
        ETHCON1CLR = ETHCON1_ON;
        return -1;
    }

    /* 5. DMA: descriptor rings, buffer size, receive filter, then receive on. */
    descriptors_init();
    ETHCON2 = ( RX_BUF_SIZE / 16u ) << 4;
    ETHRXFC = ETHRXFC_CRCOKEN | ETHRXFC_UCEN | ETHRXFC_BCEN | ETHRXFC_MCEN;
    ETHRXST = PHYS( &rx_dcpt[ 0 ] );
    ETHCON1SET = ETHCON1_RXEN;
    eth.link = false;
    return 0;
}

static int32_t pic32_send( void *ctx, const uint8_t *frame, uint16_t len )
{
    ( void )ctx;
    if ( ( len == 0 ) || ( len > TX_BUF_SIZE ) )
    {
        return -1;
    }
    /* The previous frame must be out: the controller clears TXRTS when done. */
    for ( uint32_t i = 0; ETHCON1 & ETHCON1_TXRTS; i++ )
    {
        if ( i >= WAIT_LOOPS )
        {
            return -1;
        }
    }
    memcpy( tx_buf, frame, len );
    tx_dcpt[ 1 ].hdr = 0;
    tx_dcpt[ 0 ].hdr = DCPT_SOP | DCPT_EOP | DCPT_NPV | DCPT_EOWN | ( ( uint32_t )len << 16 );
    ETHTXST = PHYS( &tx_dcpt[ 0 ] );
    ETHCON1SET = ETHCON1_TXRTS;
    return 0;
}

static int32_t pic32_receive( void *ctx, uint8_t *buf, uint16_t size )
{
    ( void )ctx;

    /* No free descriptor or FIFO overflow: frames were dropped, clear the flags
     * so the controller goes on once descriptors are returned. */
    if ( ETHIRQ & ( ETHIRQ_RXBUFNA | ETHIRQ_RXOVFLW ) )
    {
        ETHIRQCLR = ETHIRQ_RXBUFNA | ETHIRQ_RXOVFLW;
    }

    /* At most one pass over the ring per call: bounded even if the descriptors
     * are in an unexpected state. */
    for ( uint8_t pass = 0; pass < NET_PIC32_RX_BUFFERS; pass++ )
    {
        dcpt_t *d = &rx_dcpt[ eth.rx_next ];
        uint32_t hdr = d->hdr;
        if ( hdr & DCPT_EOWN )
        {
            return 0;       /* nothing received */
        }

        int32_t result = -1;
        bool whole = ( hdr & DCPT_SOP ) && ( hdr & DCPT_EOP );
        uint32_t len = DCPT_COUNT( hdr );
        if ( whole && ( len >= 14 ) )
        {
            /* The count may include the 4 CRC bytes: lwIP trims frames to the IP
             * length, so passing them on is harmless, cutting them would not be. */
            if ( len > size )
            {
                len = size;
            }
            memcpy( buf, rx_buf[ eth.rx_next ], len );
            result = ( int32_t )len;
        }

        /* Give the descriptor back and count the buffer as free. */
        d->hdr = DCPT_EOWN | DCPT_NPV;
        ETHCON1SET = ETHCON1_BUFCDEC;
        eth.rx_next = ( uint8_t )( ( eth.rx_next + 1 ) % NET_PIC32_RX_BUFFERS );

        if ( result > 0 )
        {
            return result;
        }
        /* A frame spread over several buffers (cannot happen with 1536-byte
         * buffers) or a runt: dropped, look at the next descriptor. */
    }
    return 0;
}

static bool pic32_link_up( void *ctx )
{
    ( void )ctx;
    net_phy_mode_t mode;
    bool up = net_phy_link( &eth.phy, &mode );
    if ( up && !eth.link )
    {
        mac_set_mode( &mode );
    }
    eth.link = up;
    return up;
}

/* ---------------------------------------------------------------- API --- */

void net_pic32_cfg_setup( net_pic32_cfg_t *cfg )
{
    cfg->phy_reset = HAL_PIN_NC;
    cfg->phy_addr = NET_PHY_ADDR_AUTO;
    cfg->pins_init = NULL;
}

void net_driver_pic32( net_driver_t *drv, const net_pic32_cfg_t *cfg )
{
    eth.cfg = *cfg;
    drv->ctx = NULL;
    drv->init = pic32_init;
    drv->send = pic32_send;
    drv->receive = pic32_receive;
    drv->link_up = pic32_link_up;
}

const net_phy_t *net_driver_pic32_phy( void )
{
    return &eth.phy;
}

// ------------------------------------------------------------------------- END
