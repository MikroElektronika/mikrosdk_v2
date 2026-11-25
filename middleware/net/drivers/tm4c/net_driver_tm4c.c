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
 * @file net_driver_tm4c.c
 * @brief TI TM4C129 Ethernet driver for the mikroSDK network layer.
 * @details Written from the TM4C129 data sheets (chapter "Ethernet
 * Controller"). The MAC and DMA are the same design as in STM32 (normal 4-word
 * descriptors, chained); the register offsets, the clock / power / reset
 * control and the integrated PHY are TI's. The register map below is checked
 * against TI's headers (hw_emac.h, hw_sysctl.h, hw_gpio.h, hw_memmap.h) by
 * scripts/net_host_test (test_tm4c_regmap). Cortex-M4F: no data cache.
 */

#include <string.h>

#include "net_driver_tm4c.h"
#if defined( __arm__ )
#include "core_header.h"
#endif

#ifndef FOSC_KHZ_VALUE
#error "net_driver_tm4c: the setup gives no core clock (FOSC_KHZ_VALUE)"
#endif

/* ----------------------------------------------------------- Peripherals --- */

#ifndef NET_TM4C_EMAC_BASE
#define NET_TM4C_EMAC_BASE      0x400EC000UL
#endif
#ifndef NET_TM4C_SYSCTL_BASE
#define NET_TM4C_SYSCTL_BASE    0x400FE000UL
#endif
#ifndef NET_TM4C_GPIOK_BASE
#define NET_TM4C_GPIOK_BASE     0x40061000UL
#endif

#define REG( base, offset )     ( *( volatile uint32_t * )( ( uintptr_t )( base ) + ( offset ) ) )

/* EMAC */
#define EMAC_CFG                REG( NET_TM4C_EMAC_BASE, 0x000 )
#define EMAC_FRAMEFLTR          REG( NET_TM4C_EMAC_BASE, 0x004 )
#define EMAC_MIIADDR            REG( NET_TM4C_EMAC_BASE, 0x010 )
#define EMAC_MIIDATA            REG( NET_TM4C_EMAC_BASE, 0x014 )
#define EMAC_FLOWCTL            REG( NET_TM4C_EMAC_BASE, 0x018 )
#define EMAC_ADDR0H             REG( NET_TM4C_EMAC_BASE, 0x040 )
#define EMAC_ADDR0L             REG( NET_TM4C_EMAC_BASE, 0x044 )
#define EMAC_DMABUSMOD          REG( NET_TM4C_EMAC_BASE, 0xC00 )
#define EMAC_TXPOLLD            REG( NET_TM4C_EMAC_BASE, 0xC04 )
#define EMAC_RXPOLLD            REG( NET_TM4C_EMAC_BASE, 0xC08 )
#define EMAC_RXDLADDR           REG( NET_TM4C_EMAC_BASE, 0xC0C )
#define EMAC_TXDLADDR           REG( NET_TM4C_EMAC_BASE, 0xC10 )
#define EMAC_DMARIS             REG( NET_TM4C_EMAC_BASE, 0xC14 )
#define EMAC_DMAOPMODE          REG( NET_TM4C_EMAC_BASE, 0xC18 )
#define EMAC_DMAIM              REG( NET_TM4C_EMAC_BASE, 0xC1C )
#define EMAC_PC                 REG( NET_TM4C_EMAC_BASE, 0xFC4 )

#define CFG_RE                  ( 1UL << 2 )
#define CFG_TE                  ( 1UL << 3 )
#define CFG_DUPM                ( 1UL << 11 )
#define CFG_FES                 ( 1UL << 14 )
#define CFG_PS                  ( 1UL << 15 )   /* port select: MII (10/100) */
#define FRAMEFLTR_PM            ( 1UL << 4 )    /* pass all multicast (mDNS, IPv6) */
#define MIIADDR_MIIB            ( 1UL << 0 )
#define MIIADDR_MIIW            ( 1UL << 1 )
#define MIIADDR_CR_POS          2
#define MIIADDR_MII_POS         6
#define MIIADDR_PLA_POS         11
#define DMABUSMOD_SWR           ( 1UL << 0 )
#define DMABUSMOD_PBL_32        ( 32UL << 8 )
#define DMABUSMOD_FB            ( 1UL << 16 )
#define DMABUSMOD_RPBL_32       ( 32UL << 17 )
#define DMABUSMOD_USP           ( 1UL << 23 )
#define DMABUSMOD_AAL           ( 1UL << 25 )
#define DMARIS_TU               ( 1UL << 2 )    /* write 1 to clear */
#define DMARIS_RU               ( 1UL << 7 )
#define DMAOPMODE_SR            ( 1UL << 1 )
#define DMAOPMODE_ST            ( 1UL << 13 )
#define DMAOPMODE_FTF           ( 1UL << 20 )
#define DMAOPMODE_TSF           ( 1UL << 21 )
#define DMAOPMODE_RSF           ( 1UL << 25 )
#define PC_ANEN                 ( 1UL << 3 )
#define PC_ANMODE_ALL           ( 3UL << 1 )    /* advertise 10/100, half/full */
#define PC_MDIXEN               ( 1UL << 10 )

/* SYSCTL (bit 0: EMAC0 / EPHY0; RCGCGPIO bit 9: port K) */
#define SYSCTL_SREPHY           REG( NET_TM4C_SYSCTL_BASE, 0x530 )
#define SYSCTL_SREMAC           REG( NET_TM4C_SYSCTL_BASE, 0x59C )
#define SYSCTL_RCGCGPIO         REG( NET_TM4C_SYSCTL_BASE, 0x608 )
#define SYSCTL_RCGCEPHY         REG( NET_TM4C_SYSCTL_BASE, 0x630 )
#define SYSCTL_RCGCEMAC         REG( NET_TM4C_SYSCTL_BASE, 0x69C )
#define SYSCTL_PCEPHY           REG( NET_TM4C_SYSCTL_BASE, 0x930 )
#define SYSCTL_PCEMAC           REG( NET_TM4C_SYSCTL_BASE, 0x99C )
#define SYSCTL_PRGPIO           REG( NET_TM4C_SYSCTL_BASE, 0xA08 )
#define SYSCTL_PREPHY           REG( NET_TM4C_SYSCTL_BASE, 0xA30 )
#define SYSCTL_PREMAC           REG( NET_TM4C_SYSCTL_BASE, 0xA9C )
#define SYSCTL_EMAC0            ( 1UL << 0 )
#define SYSCTL_GPIOK            ( 1UL << 9 )

/* GPIO port K */
#define GPIOK_AFSEL             REG( NET_TM4C_GPIOK_BASE, 0x420 )
#define GPIOK_DEN               REG( NET_TM4C_GPIOK_BASE, 0x51C )
#define GPIOK_PCTL              REG( NET_TM4C_GPIOK_BASE, 0x52C )
#define PCTL_EN0LED             5u              /* PK4 EN0LED0, PK5 EN0LED2, PK6 EN0LED1 */

/* --------------------------------------------------------- Descriptors --- */

#define DES0_OWN                ( 1UL << 31 )
#define TDES0_LS                ( 1UL << 29 )
#define TDES0_FS                ( 1UL << 28 )
#define TDES0_TCH               ( 1UL << 20 )
#define RDES0_FL( d )           ( ( ( d ) >> 16 ) & 0x3FFFUL )   /* frame length, CRC included */
#define RDES0_ES                ( 1UL << 15 )
#define RDES0_FS                ( 1UL << 9 )
#define RDES0_LS                ( 1UL << 8 )
#define RDES1_RCH               ( 1UL << 14 )

#define BUF_SIZE                1536u
#define CRC_SIZE                4u

typedef struct
{
    volatile uint32_t des0;
    volatile uint32_t des1;
    volatile uint32_t des2;     /* buffer */
    volatile uint32_t des3;     /* next descriptor (chained) */
} dcpt_t;

static dcpt_t rx_dcpt[ NET_TM4C_RX_BUFFERS ] __attribute__(( aligned( 16 ) ));
static dcpt_t tx_dcpt[ NET_TM4C_TX_BUFFERS ] __attribute__(( aligned( 16 ) ));
static uint8_t rx_buf[ NET_TM4C_RX_BUFFERS ][ BUF_SIZE ] __attribute__(( aligned( 16 ) ));
static uint8_t tx_buf[ NET_TM4C_TX_BUFFERS ][ BUF_SIZE ] __attribute__(( aligned( 16 ) ));

#define ADDR( p )               ( ( uint32_t )( uintptr_t )( p ) )

/* Bounded waits on hardware flags. NET_TM4C_POLL_HOOK() runs in every wait:
 * empty here, the host unit test uses it to play the hardware. */
#define WAIT_LOOPS              200000ul
#ifndef NET_TM4C_POLL_HOOK
#define NET_TM4C_POLL_HOOK()    ( ( void )0 )
#endif

/* ---------------------------------------------------------------- State --- */

static struct
{
    net_tm4c_cfg_t cfg;
    net_phy_t phy;
    uint32_t mdc_range;
    uint8_t rx_next;
    uint8_t tx_next;
    bool link;
} eth;

/* ------------------------------------------------------------- Helpers --- */

static int32_t wait_set( volatile uint32_t *reg, uint32_t mask )
{
    for ( uint32_t i = 0; i < WAIT_LOOPS; i++ )
    {
        NET_TM4C_POLL_HOOK();
        if ( ( *reg & mask ) == mask )
        {
            return 0;
        }
    }
    return -1;
}

static int32_t wait_clear( volatile uint32_t *reg, uint32_t mask )
{
    for ( uint32_t i = 0; i < WAIT_LOOPS; i++ )
    {
        NET_TM4C_POLL_HOOK();
        if ( !( *reg & mask ) )
        {
            return 0;
        }
    }
    return -1;
}

/* MDC clock range (MIIADDR.CR) from the system clock: MDC <= 2.5 MHz. */
static uint32_t mdc_range( uint32_t sysclk_khz )
{
    if ( sysclk_khz >= 100000u )
    {
        return 1;   /* /62 */
    }
    if ( sysclk_khz >= 60000u )
    {
        return 0;   /* /42 */
    }
    if ( sysclk_khz >= 35000u )
    {
        return 3;   /* /26 */
    }
    return 2;       /* /16 */
}

/* ----------------------------------------------------------------- MDIO --- */

static uint32_t mdio_command( uint8_t addr, uint8_t reg )
{
    return ( ( uint32_t )( addr & 0x1F ) << MIIADDR_PLA_POS ) | ( ( uint32_t )( reg & 0x1F ) << MIIADDR_MII_POS ) |
           ( eth.mdc_range << MIIADDR_CR_POS ) | MIIADDR_MIIB;
}

static int32_t mdio_read( void *ctx, uint8_t addr, uint8_t reg, uint16_t *value )
{
    ( void )ctx;
    if ( wait_clear( &EMAC_MIIADDR, MIIADDR_MIIB ) )
    {
        return -1;
    }
    EMAC_MIIADDR = mdio_command( addr, reg );
    int32_t err = wait_clear( &EMAC_MIIADDR, MIIADDR_MIIB );
    *value = ( uint16_t )EMAC_MIIDATA;
    return err;
}

static int32_t mdio_write( void *ctx, uint8_t addr, uint8_t reg, uint16_t value )
{
    ( void )ctx;
    if ( wait_clear( &EMAC_MIIADDR, MIIADDR_MIIB ) )
    {
        return -1;
    }
    EMAC_MIIDATA = value;
    EMAC_MIIADDR = mdio_command( addr, reg ) | MIIADDR_MIIW;
    return wait_clear( &EMAC_MIIADDR, MIIADDR_MIIB );
}

/* ------------------------------------------------------------- Driver --- */

static void leds_init( void )
{
    SYSCTL_RCGCGPIO |= SYSCTL_GPIOK;
    wait_set( &SYSCTL_PRGPIO, SYSCTL_GPIOK );
    /* PCTL of PK4/PK5/PK6 to the Ethernet LEDs; PK5 and PK6 switched to it
     * (as TivaWare's GPIOPinConfigure / GPIOPinTypeEthernetLED in hw_eth). */
    GPIOK_PCTL = ( GPIOK_PCTL & ~( 0xFFFUL << 16 ) ) |
                 ( PCTL_EN0LED << 16 ) | ( PCTL_EN0LED << 20 ) | ( PCTL_EN0LED << 24 );
    GPIOK_AFSEL |= ( 1UL << 5 ) | ( 1UL << 6 );
    GPIOK_DEN |= ( 1UL << 5 ) | ( 1UL << 6 );
}

static void descriptors_init( void )
{
    for ( uint8_t i = 0; i < NET_TM4C_RX_BUFFERS; i++ )
    {
        rx_dcpt[ i ].des1 = RDES1_RCH | BUF_SIZE;
        rx_dcpt[ i ].des2 = ADDR( rx_buf[ i ] );
        rx_dcpt[ i ].des3 = ADDR( &rx_dcpt[ ( i + 1 ) % NET_TM4C_RX_BUFFERS ] );
        rx_dcpt[ i ].des0 = DES0_OWN;
    }
    for ( uint8_t i = 0; i < NET_TM4C_TX_BUFFERS; i++ )
    {
        tx_dcpt[ i ].des0 = TDES0_TCH;
        tx_dcpt[ i ].des1 = 0;
        tx_dcpt[ i ].des2 = ADDR( tx_buf[ i ] );
        tx_dcpt[ i ].des3 = ADDR( &tx_dcpt[ ( i + 1 ) % NET_TM4C_TX_BUFFERS ] );
    }
    eth.rx_next = 0;
    eth.tx_next = 0;
}

static void mac_set_mode( const net_phy_mode_t *mode )
{
    uint32_t cfg = EMAC_CFG & ~( CFG_FES | CFG_DUPM );
    if ( mode->speed_100 )
    {
        cfg |= CFG_FES;
    }
    if ( mode->full_duplex )
    {
        cfg |= CFG_DUPM;
    }
    EMAC_CFG = cfg;
}

static int32_t tm4c_init( void *ctx, const uint8_t *mac )
{
    ( void )ctx;

    if ( eth.cfg.leds )
    {
        leds_init();
    }

    /* 1. Clocks and power of the MAC and the integrated PHY. */
    SYSCTL_RCGCEMAC |= SYSCTL_EMAC0;
    SYSCTL_RCGCEPHY |= SYSCTL_EMAC0;
    SYSCTL_PCEMAC |= SYSCTL_EMAC0;
    SYSCTL_PCEPHY |= SYSCTL_EMAC0;
    if ( wait_set( &SYSCTL_PREMAC, SYSCTL_EMAC0 ) || wait_set( &SYSCTL_PREPHY, SYSCTL_EMAC0 ) )
    {
        return -2;
    }

    /* 2. Integrated PHY with auto-negotiation and auto-MDIX; the setting takes
     *    effect when MAC and PHY are reset. */
    EMAC_PC = PC_MDIXEN | PC_ANEN | PC_ANMODE_ALL;      /* PHYEXT = 0: integrated PHY */
    SYSCTL_SREMAC |= SYSCTL_EMAC0;
    SYSCTL_SREPHY |= SYSCTL_EMAC0;
    for ( volatile uint8_t hold = 0; hold < 16; hold++ )
    {
        NET_TM4C_POLL_HOOK();       /* keep the reset asserted a moment, as TivaWare does */
    }
    SYSCTL_SREMAC &= ~SYSCTL_EMAC0;
    SYSCTL_SREPHY &= ~SYSCTL_EMAC0;
    if ( wait_set( &SYSCTL_PREMAC, SYSCTL_EMAC0 ) || wait_set( &SYSCTL_PREPHY, SYSCTL_EMAC0 ) )
    {
        return -2;
    }

    /* 3. DMA software reset. */
    EMAC_DMABUSMOD |= DMABUSMOD_SWR;
    if ( wait_clear( &EMAC_DMABUSMOD, DMABUSMOD_SWR ) )
    {
        return -2;
    }

    /* 4. PHY over MDIO. */
    eth.mdc_range = mdc_range( FOSC_KHZ_VALUE );
    eth.phy.ctx = NULL;
    eth.phy.addr = eth.cfg.phy_addr;
    eth.phy.read = mdio_read;
    eth.phy.write = mdio_write;
    if ( net_phy_init( &eth.phy ) )
    {
        return -1;
    }

    /* 5. MAC: MII port, 100 Mbit/s full duplex until the PHY reports the mode. */
    EMAC_CFG = CFG_PS | CFG_FES | CFG_DUPM;
    EMAC_FRAMEFLTR = FRAMEFLTR_PM;
    EMAC_FLOWCTL = 0;
    EMAC_ADDR0H = ( uint32_t )mac[ 4 ] | ( ( uint32_t )mac[ 5 ] << 8 );
    EMAC_ADDR0L = ( uint32_t )mac[ 0 ] | ( ( uint32_t )mac[ 1 ] << 8 ) | ( ( uint32_t )mac[ 2 ] << 16 ) |
                  ( ( uint32_t )mac[ 3 ] << 24 );

    /* 6. DMA: rings, bursts, store and forward. */
    descriptors_init();
    EMAC_TXDLADDR = ADDR( &tx_dcpt[ 0 ] );
    EMAC_RXDLADDR = ADDR( &rx_dcpt[ 0 ] );
    EMAC_DMABUSMOD = DMABUSMOD_AAL | DMABUSMOD_USP | DMABUSMOD_RPBL_32 | DMABUSMOD_FB | DMABUSMOD_PBL_32;
    EMAC_DMAIM = 0;
    EMAC_DMAOPMODE = DMAOPMODE_RSF | DMAOPMODE_TSF;

    /* 7. Start: transmitter, flush its FIFO, DMA transmit, receiver, DMA receive. */
    EMAC_CFG |= CFG_TE;
    EMAC_DMAOPMODE |= DMAOPMODE_FTF;
    wait_clear( &EMAC_DMAOPMODE, DMAOPMODE_FTF );
    EMAC_DMAOPMODE |= DMAOPMODE_ST;
    EMAC_CFG |= CFG_RE;
    EMAC_DMAOPMODE |= DMAOPMODE_SR;
    eth.link = false;
    return 0;
}

static int32_t tm4c_send( void *ctx, const uint8_t *frame, uint16_t len )
{
    ( void )ctx;
    if ( ( len == 0 ) || ( len > BUF_SIZE ) )
    {
        return -1;
    }
    dcpt_t *d = &tx_dcpt[ eth.tx_next ];
    if ( wait_clear( &d->des0, DES0_OWN ) )
    {
        return -1;      /* the DMA still owns the descriptor: transmitter stuck */
    }
    memcpy( tx_buf[ eth.tx_next ], frame, len );
    d->des1 = len;
    d->des0 = DES0_OWN | TDES0_FS | TDES0_LS | TDES0_TCH;
    if ( EMAC_DMARIS & DMARIS_TU )
    {
        EMAC_DMARIS = DMARIS_TU;
    }
    EMAC_TXPOLLD = 0;
    eth.tx_next = ( uint8_t )( ( eth.tx_next + 1 ) % NET_TM4C_TX_BUFFERS );
    return 0;
}

static int32_t tm4c_receive( void *ctx, uint8_t *buf, uint16_t size )
{
    ( void )ctx;
    int32_t result = 0;

    for ( uint8_t pass = 0; ( pass < NET_TM4C_RX_BUFFERS ) && ( result <= 0 ); pass++ )
    {
        dcpt_t *d = &rx_dcpt[ eth.rx_next ];
        uint32_t des0 = d->des0;
        if ( des0 & DES0_OWN )
        {
            break;
        }
        uint32_t len = RDES0_FL( des0 );
        bool whole = ( des0 & RDES0_FS ) && ( des0 & RDES0_LS ) && !( des0 & RDES0_ES );
        if ( whole && ( len >= 14u + CRC_SIZE ) )
        {
            len -= CRC_SIZE;
            if ( len > size )
            {
                len = size;
            }
            memcpy( buf, rx_buf[ eth.rx_next ], len );
            result = ( int32_t )len;
        }
        d->des0 = DES0_OWN;
        eth.rx_next = ( uint8_t )( ( eth.rx_next + 1 ) % NET_TM4C_RX_BUFFERS );
    }

    if ( EMAC_DMARIS & DMARIS_RU )
    {
        EMAC_DMARIS = DMARIS_RU;
        EMAC_RXPOLLD = 0;
    }
    return result;
}

static bool tm4c_link_up( void *ctx )
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

void net_tm4c_cfg_setup( net_tm4c_cfg_t *cfg )
{
    cfg->leds = true;
    cfg->phy_addr = NET_PHY_ADDR_AUTO;
}

void net_driver_tm4c( net_driver_t *drv, const net_tm4c_cfg_t *cfg )
{
    eth.cfg = *cfg;
    drv->ctx = NULL;
    drv->init = tm4c_init;
    drv->send = tm4c_send;
    drv->receive = tm4c_receive;
    drv->link_up = tm4c_link_up;
}

const net_phy_t *net_driver_tm4c_phy( void )
{
    return &eth.phy;
}

// ------------------------------------------------------------------------- END
