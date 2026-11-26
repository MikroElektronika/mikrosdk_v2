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
 * @file net_driver_kinetis.c
 * @brief NXP Kinetis ENET driver for the mikroSDK network layer.
 * @details Written from the reference manuals of the K60, K64, K66 and KV58
 * (chapter "10/100-Mbps Ethernet MAC (ENET)"). Legacy (8-byte) buffer
 * descriptors in little-endian order (ECR[DBSWP]); the MAC strips the FCS
 * (RCR[CRCFWD]). The register map below is checked against NXP's device
 * headers by scripts/net_host_test (test_kinetis_regmap).
 *
 * MKV58 (Cortex-M7): when the application has the data cache on, buffers and
 * descriptors (32-byte aligned whole cache lines) are cleaned before the DMA
 * reads them and invalidated before the CPU does. K65/K66: the LMEM cache is
 * off after reset and mikroSDK does not switch it on.
 */

#include <string.h>

#include "net_driver_kinetis.h"
#include "delays.h"
#if defined( __arm__ )
#include "core_header.h"
#endif

#if !defined( NET_KINETIS_K60_K64 ) && !defined( NET_KINETIS_K65_K66 ) && !defined( NET_KINETIS_KV58 )
#error "net_driver_kinetis: define the variant (NET_KINETIS_K60_K64/K65_K66/KV58), set by middleware/net/CMakeLists.txt"
#endif

#ifndef FOSC_KHZ_VALUE
#error "net_driver_kinetis: the setup gives no core clock (FOSC_KHZ_VALUE)"
#endif

/* ----------------------------------------------------------- Peripherals --- */

#ifndef NET_KINETIS_ENET_BASE
#define NET_KINETIS_ENET_BASE   0x400C0000UL
#endif
#ifndef NET_KINETIS_SIM_BASE
#define NET_KINETIS_SIM_BASE    0x40047000UL
#endif
#ifndef NET_KINETIS_PORTA_BASE
#define NET_KINETIS_PORTA_BASE  0x40049000UL
#endif
#ifndef NET_KINETIS_PORTB_BASE
#define NET_KINETIS_PORTB_BASE  0x4004A000UL
#endif
#ifndef NET_KINETIS_PORTE_BASE
#define NET_KINETIS_PORTE_BASE  0x4004D000UL
#endif
#ifndef NET_KINETIS_MPU_BASE
#define NET_KINETIS_MPU_BASE    0x4000D000UL
#endif
#ifndef NET_KINETIS_SCB_BASE
#define NET_KINETIS_SCB_BASE    0xE000E000UL
#endif

#define REG( base, offset )     ( *( volatile uint32_t * )( ( uintptr_t )( base ) + ( offset ) ) )

/* ENET registers (offsets as in ENET_Type) */
#define ENET_EIR                REG( NET_KINETIS_ENET_BASE, 0x004 )
#define ENET_EIMR               REG( NET_KINETIS_ENET_BASE, 0x008 )
#define ENET_RDAR               REG( NET_KINETIS_ENET_BASE, 0x010 )
#define ENET_TDAR               REG( NET_KINETIS_ENET_BASE, 0x014 )
#define ENET_ECR                REG( NET_KINETIS_ENET_BASE, 0x024 )
#define ENET_MMFR               REG( NET_KINETIS_ENET_BASE, 0x040 )
#define ENET_MSCR               REG( NET_KINETIS_ENET_BASE, 0x044 )
#define ENET_RCR                REG( NET_KINETIS_ENET_BASE, 0x084 )
#define ENET_TCR                REG( NET_KINETIS_ENET_BASE, 0x0C4 )
#define ENET_PALR               REG( NET_KINETIS_ENET_BASE, 0x0E4 )
#define ENET_PAUR               REG( NET_KINETIS_ENET_BASE, 0x0E8 )
#define ENET_IAUR               REG( NET_KINETIS_ENET_BASE, 0x118 )
#define ENET_IALR               REG( NET_KINETIS_ENET_BASE, 0x11C )
#define ENET_GAUR               REG( NET_KINETIS_ENET_BASE, 0x120 )
#define ENET_GALR               REG( NET_KINETIS_ENET_BASE, 0x124 )
#define ENET_TFWR               REG( NET_KINETIS_ENET_BASE, 0x144 )
#define ENET_RDSR               REG( NET_KINETIS_ENET_BASE, 0x180 )
#define ENET_TDSR               REG( NET_KINETIS_ENET_BASE, 0x184 )
#define ENET_MRBR               REG( NET_KINETIS_ENET_BASE, 0x188 )
#define ENET_RSFL               REG( NET_KINETIS_ENET_BASE, 0x190 )

#define ECR_RESET               ( 1UL << 0 )
#define ECR_ETHEREN             ( 1UL << 1 )
#define ECR_DBSWP               ( 1UL << 8 )
#define EIR_MII                 ( 1UL << 23 )
#define MMFR_ST                 ( 1UL << 30 )
#define MMFR_OP_WRITE           ( 1UL << 28 )
#define MMFR_OP_READ            ( 2UL << 28 )
#define MMFR_PA_POS             23
#define MMFR_RA_POS             18
#define MMFR_TA                 ( 2UL << 16 )
#define MSCR_MII_SPEED_POS      1
#define MSCR_HOLDTIME_POS       8
#define RCR_DRT                 ( 1UL << 1 )
#define RCR_MII_MODE            ( 1UL << 2 )
#define RCR_RMII_MODE           ( 1UL << 8 )
#define RCR_RMII_10T            ( 1UL << 9 )
#define RCR_CRCFWD              ( 1UL << 14 )
#define RCR_MAX_FL_POS          16
#define TCR_FDEN                ( 1UL << 2 )
#define TFWR_STRFWD             ( 1UL << 8 )
#define DAR_ACTIVE              ( 1UL << 24 )   /* RDAR / TDAR: descriptors ready */

/* SIM */
#define SIM_SOPT2               REG( NET_KINETIS_SIM_BASE, 0x1004 )
#define SIM_SCGC2               REG( NET_KINETIS_SIM_BASE, 0x102C )
#define SIM_SCGC5               REG( NET_KINETIS_SIM_BASE, 0x1038 )
#define SIM_SOPT2_TIMESRC       ( 3UL << 20 )   /* 1588 timer clock: ENET_1588_CLKIN */
#define SIM_SOPT2_RMIISRC       ( 1UL << 19 )   /* RMII clock: ENET_1588_CLKIN */
#define SIM_SCGC2_ENET          ( 1UL << 0 )
#define SIM_SCGC5_PORTA         ( 1UL << 9 )
#define SIM_SCGC5_PORTB         ( 1UL << 10 )
#define SIM_SCGC5_PORTE         ( 1UL << 13 )

/* PORT pin control */
#define PCR( port_base, pin )   REG( port_base, 4u * ( pin ) )
#define PCR_PS                  ( 1UL << 0 )    /* pull-up (with PE) */
#define PCR_PE                  ( 1UL << 1 )
#define PCR_MUX( n )            ( ( uint32_t )( n ) << 8 )

/* System MPU */
#define MPU_CESR                REG( NET_KINETIS_MPU_BASE, 0x000 )
#define MPU_CESR_VLD            ( 1UL << 0 )

/* Cortex-M7 data cache (KV58) */
#define SCB_CCR                 REG( NET_KINETIS_SCB_BASE, 0xD14 )
#define SCB_CCR_DC              ( 1UL << 16 )
#define SCB_DCIMVAC             REG( NET_KINETIS_SCB_BASE, 0xF5C )
#define SCB_DCCMVAC             REG( NET_KINETIS_SCB_BASE, 0xF68 )

/* --------------------------------------------------------- Descriptors --- */

/* RX control */
#define RXBD_E                  0x8000u         /* empty: owned by the ENET */
#define RXBD_W                  0x2000u         /* wrap: last descriptor of the ring */
#define RXBD_L                  0x0800u         /* last buffer of the frame */
#define RXBD_ERRORS             ( 0x0020u | 0x0010u | 0x0004u | 0x0002u | 0x0001u )   /* LG, NO, CR, OV, TR */
/* TX control */
#define TXBD_R                  0x8000u         /* ready: owned by the ENET */
#define TXBD_W                  0x2000u
#define TXBD_L                  0x0800u
#define TXBD_TC                 0x0400u         /* append the CRC */

#define BUF_SIZE                1536u           /* full frame, multiple of 16 (MRBR) and of 32 (cache line) */

/* Legacy 8-byte descriptors, back to back as the ENET reads them; four share a
 * 32-byte cache line (KV58). That is safe because every write to a descriptor
 * is cleaned at once, so an invalidate never drops a pending CPU write. */
typedef struct
{
    volatile uint16_t length;
    volatile uint16_t control;
    volatile uint32_t buffer;
} bd_t;

static bd_t rx_bd[ NET_KINETIS_RX_BUFFERS ] __attribute__(( aligned( 32 ) ));
static bd_t tx_bd[ NET_KINETIS_TX_BUFFERS ] __attribute__(( aligned( 32 ) ));
static uint8_t rx_buf[ NET_KINETIS_RX_BUFFERS ][ BUF_SIZE ] __attribute__(( aligned( 32 ) ));
static uint8_t tx_buf[ NET_KINETIS_TX_BUFFERS ][ BUF_SIZE ] __attribute__(( aligned( 32 ) ));

#define ADDR( p )               ( ( uint32_t )( uintptr_t )( p ) )

/* Bounded waits on hardware flags. NET_KINETIS_POLL_HOOK() runs in every wait:
 * empty here, the host unit test uses it to play the hardware. */
#define WAIT_LOOPS              200000ul
#ifndef NET_KINETIS_POLL_HOOK
#define NET_KINETIS_POLL_HOOK() ( ( void )0 )
#endif

/* ---------------------------------------------------------------- State --- */

static struct
{
    net_kinetis_cfg_t cfg;
    net_phy_t phy;
    uint8_t rx_next;
    uint8_t tx_next;
    bool link;
} eth;

/* ---------------------------------------------------------------- Cache --- */

#if defined( NET_KINETIS_KV58 )
static bool dcache_on( void )
{
    return 0 != ( SCB_CCR & SCB_CCR_DC );
}

static void barrier( void )
{
#if defined( __arm__ )
    __asm__ volatile ( "dsb 0xF\n\tisb 0xF" ::: "memory" );
#endif
}

static void dcache_clean( const volatile void *p, uint32_t len )
{
    if ( dcache_on() )
    {
        for ( uintptr_t a = ( uintptr_t )p & ~( uintptr_t )31; a < ( uintptr_t )p + len; a += 32 )
        {
            SCB_DCCMVAC = ( uint32_t )a;
        }
        barrier();
    }
}

static void dcache_invalidate( const volatile void *p, uint32_t len )
{
    if ( dcache_on() )
    {
        for ( uintptr_t a = ( uintptr_t )p & ~( uintptr_t )31; a < ( uintptr_t )p + len; a += 32 )
        {
            SCB_DCIMVAC = ( uint32_t )a;
        }
        barrier();
    }
}
#else
#define dcache_clean( p, len )      ( ( void )( p ), ( void )( len ) )
#define dcache_invalidate( p, len ) ( ( void )( p ), ( void )( len ) )
#endif

/* ----------------------------------------------------------------- MDIO --- */

static int32_t mdio_transfer( uint32_t frame, uint16_t *value )
{
    ENET_EIR = EIR_MII;             /* write 1 to clear */
    ENET_MMFR = frame;
    for ( uint32_t i = 0; i < WAIT_LOOPS; i++ )
    {
        NET_KINETIS_POLL_HOOK();
        if ( ENET_EIR & EIR_MII )
        {
            ENET_EIR = EIR_MII;
            if ( value )
            {
                *value = ( uint16_t )( ENET_MMFR & 0xFFFFu );
            }
            return 0;
        }
    }
    return -1;
}

static uint32_t mdio_frame( uint32_t op, uint8_t addr, uint8_t reg )
{
    return MMFR_ST | op | ( ( uint32_t )( addr & 0x1F ) << MMFR_PA_POS ) | ( ( uint32_t )( reg & 0x1F ) << MMFR_RA_POS ) |
           MMFR_TA;
}

static int32_t mdio_read( void *ctx, uint8_t addr, uint8_t reg, uint16_t *value )
{
    ( void )ctx;
    return mdio_transfer( mdio_frame( MMFR_OP_READ, addr, reg ), value );
}

static int32_t mdio_write( void *ctx, uint8_t addr, uint8_t reg, uint16_t value )
{
    ( void )ctx;
    return mdio_transfer( mdio_frame( MMFR_OP_WRITE, addr, reg ) | value, NULL );
}

/* MSCR: MDC = clock / ((MII_SPEED + 1) * 2) <= 2.5 MHz, MDIO hold time >= 10 ns
 * (the computation of NXP's SDK, ENET_SetSMI). */
static uint32_t mscr_value( uint32_t clock_hz )
{
    uint32_t speed = ( clock_hz + 5000000u - 1u ) / 5000000u - 1u;
    uint32_t ns_per_clock = 1000000000u / clock_hz;
    uint32_t hold = ( 10u + ns_per_clock - 1u ) / ns_per_clock - 1u;
    return ( ( speed & 0x3Fu ) << MSCR_MII_SPEED_POS ) | ( ( hold & 0x7u ) << MSCR_HOLDTIME_POS );
}

/* --------------------------------------------------- Pins and clocks --- */

static void pins_init( void )
{
    uint32_t data_mux = ( NET_KINETIS_PINS_KV58 == eth.cfg.pins ) ? 5u : 4u;

    SIM_SCGC5 |= SIM_SCGC5_PORTA | SIM_SCGC5_PORTB | SIM_SCGC5_PORTE;
    PCR( NET_KINETIS_PORTA_BASE, 5 ) = PCR_MUX( 4 ) | PCR_PE;            /* RXER (pulled down) */
    PCR( NET_KINETIS_PORTA_BASE, 12 ) = PCR_MUX( data_mux );            /* RXD1 */
    PCR( NET_KINETIS_PORTA_BASE, 13 ) = PCR_MUX( data_mux );            /* RXD0 */
    PCR( NET_KINETIS_PORTA_BASE, 14 ) = PCR_MUX( data_mux );            /* CRS_DV */
    PCR( NET_KINETIS_PORTA_BASE, 15 ) = PCR_MUX( data_mux );            /* TXEN */
    PCR( NET_KINETIS_PORTA_BASE, 16 ) = PCR_MUX( data_mux );            /* TXD0 */
    PCR( NET_KINETIS_PORTA_BASE, 17 ) = PCR_MUX( data_mux );            /* TXD1 */
    if ( NET_KINETIS_PINS_K60_K64 == eth.cfg.pins )
    {
        PCR( NET_KINETIS_PORTB_BASE, 0 ) = PCR_MUX( 4 ) | PCR_PE | PCR_PS;  /* MDIO (pulled up) */
        PCR( NET_KINETIS_PORTB_BASE, 1 ) = PCR_MUX( 4 );                    /* MDC */
    }
    else
    {
        PCR( NET_KINETIS_PORTA_BASE, 7 ) = PCR_MUX( 5 ) | PCR_PE | PCR_PS;  /* MDIO (pulled up) */
        PCR( NET_KINETIS_PORTA_BASE, 8 ) = PCR_MUX( 5 );                    /* MDC */
    }
    if ( NET_KINETIS_REF_CLOCK_CLKIN == eth.cfg.ref_clock )
    {
        PCR( NET_KINETIS_PORTE_BASE, 26 ) = PCR_MUX( 2 );                   /* ENET_1588_CLKIN */
        SIM_SOPT2 |= SIM_SOPT2_RMIISRC | SIM_SOPT2_TIMESRC;
    }
    else
    {
        SIM_SOPT2 &= ~SIM_SOPT2_RMIISRC;                                    /* RMII clock from EXTAL */
    }
}

/* ------------------------------------------------------------- Driver --- */

static void descriptors_init( void )
{
    for ( uint8_t i = 0; i < NET_KINETIS_RX_BUFFERS; i++ )
    {
        rx_bd[ i ].length = 0;
        rx_bd[ i ].buffer = ADDR( rx_buf[ i ] );
        rx_bd[ i ].control = RXBD_E | ( ( i == NET_KINETIS_RX_BUFFERS - 1 ) ? RXBD_W : 0u );
    }
    for ( uint8_t i = 0; i < NET_KINETIS_TX_BUFFERS; i++ )
    {
        tx_bd[ i ].length = 0;
        tx_bd[ i ].buffer = ADDR( tx_buf[ i ] );
        tx_bd[ i ].control = ( i == NET_KINETIS_TX_BUFFERS - 1 ) ? TXBD_W : 0u;
    }
    dcache_clean( rx_bd, sizeof( rx_bd ) );
    dcache_clean( tx_bd, sizeof( tx_bd ) );
    eth.rx_next = 0;
    eth.tx_next = 0;
}

/* Speed and duplex after auto-negotiation (written while running, as NXP's SDK does). */
static void mac_set_mode( const net_phy_mode_t *mode )
{
    uint32_t rcr = ENET_RCR & ~( RCR_RMII_10T | RCR_DRT );
    uint32_t tcr = ENET_TCR & ~TCR_FDEN;
    if ( !mode->speed_100 )
    {
        rcr |= RCR_RMII_10T;
    }
    if ( mode->full_duplex )
    {
        tcr |= TCR_FDEN;
    }
    else
    {
        rcr |= RCR_DRT;
    }
    ENET_RCR = rcr;
    ENET_TCR = tcr;
}

static int32_t kinetis_init( void *ctx, const uint8_t *mac )
{
    ( void )ctx;

    /* 1. Pins, RMII clock, ENET clock; the MPU would block the ENET DMA. */
    pins_init();
    SIM_SCGC2 |= SIM_SCGC2_ENET;
    if ( eth.cfg.disable_mpu )
    {
        MPU_CESR &= ~MPU_CESR_VLD;
    }
    if ( HAL_PIN_NC != eth.cfg.phy_reset )
    {
        digital_out_t rst;
        if ( DIGITAL_OUT_SUCCESS == digital_out_init( &rst, eth.cfg.phy_reset ) )
        {
            digital_out_low( &rst );
            Delay_ms( 1 );
            digital_out_high( &rst );
            Delay_ms( 10 );
        }
    }

    /* 2. Reset the controller. */
    ENET_ECR = ECR_RESET;
    uint32_t i = 0;
    while ( NET_KINETIS_POLL_HOOK(), ENET_ECR & ECR_RESET )
    {
        if ( ++i >= WAIT_LOOPS )
        {
            return -2;
        }
    }
    ENET_EIMR = 0;
    ENET_EIR = 0xFFFFFFFFu;

    /* 3. PHY over MDIO. */
    ENET_MSCR = mscr_value( ( uint32_t )FOSC_KHZ_VALUE * 1000u );
    eth.phy.ctx = NULL;
    eth.phy.addr = eth.cfg.phy_addr;
    eth.phy.read = mdio_read;
    eth.phy.write = mdio_write;
    if ( net_phy_init( &eth.phy ) )
    {
        return -1;
    }

    /* 4. MAC: RMII, FCS stripped, 1518-byte frames, 100 Mbit/s full duplex until
     *    the PHY reports the negotiated mode; all multicast accepted (mDNS, IPv6). */
    ENET_RCR = ( 1518UL << RCR_MAX_FL_POS ) | RCR_CRCFWD | RCR_RMII_MODE | RCR_MII_MODE;
    ENET_TCR = TCR_FDEN;
    ENET_PALR = ( ( uint32_t )mac[ 0 ] << 24 ) | ( ( uint32_t )mac[ 1 ] << 16 ) | ( ( uint32_t )mac[ 2 ] << 8 ) | mac[ 3 ];
    ENET_PAUR = ( ( uint32_t )mac[ 4 ] << 24 ) | ( ( uint32_t )mac[ 5 ] << 16 );
    ENET_IAUR = 0;
    ENET_IALR = 0;
    ENET_GAUR = 0xFFFFFFFFu;
    ENET_GALR = 0xFFFFFFFFu;
    ENET_TFWR = TFWR_STRFWD;
    ENET_RSFL = 0;          /* receive store and forward */

    /* 5. Descriptor rings, then enable (little-endian descriptors). */
    descriptors_init();
    ENET_MRBR = BUF_SIZE;
    ENET_RDSR = ADDR( rx_bd );
    ENET_TDSR = ADDR( tx_bd );
    ENET_ECR = ECR_ETHEREN | ECR_DBSWP;
    ENET_RDAR = DAR_ACTIVE;
    eth.link = false;
    return 0;
}

static int32_t kinetis_send( void *ctx, const uint8_t *frame, uint16_t len )
{
    ( void )ctx;
    if ( ( len == 0 ) || ( len > BUF_SIZE ) )
    {
        return -1;
    }
    bd_t *d = &tx_bd[ eth.tx_next ];
    for ( uint32_t i = 0; ; i++ )
    {
        NET_KINETIS_POLL_HOOK();
        dcache_invalidate( d, sizeof( *d ) );
        if ( !( d->control & TXBD_R ) )
        {
            break;
        }
        if ( i >= WAIT_LOOPS )
        {
            return -1;      /* the ENET still owns the descriptor: transmitter stuck */
        }
    }
    memcpy( tx_buf[ eth.tx_next ], frame, len );
    dcache_clean( tx_buf[ eth.tx_next ], len );
    d->length = len;
    d->control = ( uint16_t )( TXBD_R | TXBD_L | TXBD_TC | ( d->control & TXBD_W ) );
    dcache_clean( d, sizeof( *d ) );
    ENET_TDAR = DAR_ACTIVE;
    eth.tx_next = ( uint8_t )( ( eth.tx_next + 1 ) % NET_KINETIS_TX_BUFFERS );
    return 0;
}

static int32_t kinetis_receive( void *ctx, uint8_t *buf, uint16_t size )
{
    ( void )ctx;
    int32_t result = 0;
    bool returned = false;

    /* At most one pass over the ring per call. */
    for ( uint8_t pass = 0; ( pass < NET_KINETIS_RX_BUFFERS ) && ( result <= 0 ); pass++ )
    {
        bd_t *d = &rx_bd[ eth.rx_next ];
        dcache_invalidate( d, sizeof( *d ) );
        uint16_t control = d->control;
        if ( control & RXBD_E )
        {
            break;          /* nothing (more) received */
        }

        uint32_t len = d->length;   /* without FCS (RCR[CRCFWD]) */
        if ( ( control & RXBD_L ) && !( control & RXBD_ERRORS ) && ( len >= 14u ) )
        {
            if ( len > size )
            {
                len = size;
            }
            dcache_invalidate( rx_buf[ eth.rx_next ], len );
            memcpy( buf, rx_buf[ eth.rx_next ], len );
            result = ( int32_t )len;
        }
        /* Errored, runt or over several buffers (cannot happen with 1536-byte
         * buffers): dropped. Give the descriptor back. */
        d->control = ( uint16_t )( RXBD_E | ( control & RXBD_W ) );
        dcache_clean( d, sizeof( *d ) );
        eth.rx_next = ( uint8_t )( ( eth.rx_next + 1 ) % NET_KINETIS_RX_BUFFERS );
        returned = true;
    }

    /* Descriptors given back: tell the ENET (it stops when it finds none empty). */
    if ( returned )
    {
        ENET_RDAR = DAR_ACTIVE;
    }
    return result;
}

static bool kinetis_link_up( void *ctx )
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

void net_kinetis_cfg_setup( net_kinetis_cfg_t *cfg )
{
#if defined( NET_KINETIS_KV58 )
    cfg->pins = NET_KINETIS_PINS_KV58;
#elif defined( NET_KINETIS_K65_K66 )
    cfg->pins = NET_KINETIS_PINS_K65_K66;
#else
    cfg->pins = NET_KINETIS_PINS_K60_K64;
#endif
    cfg->ref_clock = NET_KINETIS_REF_CLOCK_CLKIN;
    cfg->disable_mpu = true;
    cfg->phy_reset = HAL_PIN_NC;
    cfg->phy_addr = NET_PHY_ADDR_AUTO;
}

void net_driver_kinetis( net_driver_t *drv, const net_kinetis_cfg_t *cfg )
{
    eth.cfg = *cfg;
    drv->ctx = NULL;
    drv->init = kinetis_init;
    drv->send = kinetis_send;
    drv->receive = kinetis_receive;
    drv->link_up = kinetis_link_up;
}

const net_phy_t *net_driver_kinetis_phy( void )
{
    return &eth.phy;
}

// ------------------------------------------------------------------------- END
