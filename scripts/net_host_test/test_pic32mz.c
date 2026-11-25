/*
 * Host unit test of middleware/net/drivers/pic32mz with fake registers
 * (fakes/pic32mz/mcu.h) and a simulated LAN8720. The test plays the DMA
 * controller: it fills receive descriptors and checks what the driver writes.
 * It tests the driver's logic and its use of the descriptor format, not the
 * silicon. Exit status 0 when every check passed.
 */

#include <stdio.h>
#include <string.h>

/* White box: the driver's static descriptors and buffers are visible here. */
#include "../../middleware/net/drivers/pic32mz/net_driver_pic32mz.c"

static int failures;
#define CHECK( name, cond ) do { if ( cond ) printf( "OK %s\n", name ); \
        else { failures++; printf( "FAIL %s (line %d)\n", name, __LINE__ ); } } while ( 0 )

/* ------------------------------------------------------------- Fakes --- */

#define FAKE_DEFINE( name ) volatile uint32_t name;
FAKE_REGS( FAKE_DEFINE )

uint8_t fake_phy_addr;
uint16_t fake_phy_reg[ 32 ];

uint32_t fake_mdio_read_data( void )
{
    uint8_t addr = ( uint8_t )( ( EMAC1MADR >> 8 ) & 0x1F );
    return ( addr == fake_phy_addr ) ? fake_phy_reg[ EMAC1MADR & 0x1F ] : 0xFFFF;
}

static int reset_low, reset_high, pins_calls;
err_t digital_out_init( digital_out_t *out, pin_name_t name ) { out->pin = name; return DIGITAL_OUT_SUCCESS; }
err_t digital_out_low( digital_out_t *out ) { ( void )out; reset_low++; return 0; }
err_t digital_out_high( digital_out_t *out ) { ( void )out; reset_high = reset_low; return 0; }
void Delay_ms( uint32_t ms ) { ( void )ms; }
static void pins( void ) { pins_calls++; }

static void lan8720_at( uint8_t addr )
{
    memset( fake_phy_reg, 0, sizeof( fake_phy_reg ) );
    fake_phy_addr = addr;
    fake_phy_reg[ 2 ] = 0x0007;
    fake_phy_reg[ 3 ] = 0xC0F1;
    fake_phy_reg[ 1 ] = 0x7809;     /* no link */
}

/* The "controller" puts a received frame into the next descriptor. */
static uint8_t dma_next;
static void dma_receive( const uint8_t *frame, uint32_t len, uint32_t flags )
{
    memcpy( rx_buf[ dma_next ], frame, len );
    rx_dcpt[ dma_next ].hdr = flags | DCPT_NPV | ( len << 16 );   /* EOWN cleared */
    dma_next = ( uint8_t )( ( dma_next + 1 ) % NET_PIC32MZ_RX_BUFFERS );
}

static void make_frame( uint8_t *f, uint32_t len, uint8_t tag )
{
    for ( uint32_t i = 0; i < len; i++ )
    {
        f[ i ] = ( uint8_t )( tag + i * 7 );
    }
}

int main( void )
{
    static const uint8_t mac[ 6 ] = { 0x02, 0x11, 0x22, 0x33, 0x44, 0x55 };
    net_driver_t drv;
    net_pic32mz_cfg_t cfg;
    static uint8_t frame[ 2048 ], out[ 2048 ];

    /* ---- init ---- */
    net_pic32mz_cfg_setup( &cfg );
    CHECK( "cfg-defaults", HAL_PIN_NC == cfg.phy_reset && NET_PHY_ADDR_AUTO == cfg.phy_addr && !cfg.pins_init );
    cfg.phy_reset = 42;
    cfg.pins_init = pins;
    net_driver_pic32mz( &drv, &cfg );
    lan8720_at( 1 );
    CHECK( "init", 0 == drv.init( drv.ctx, mac ) );
    CHECK( "init-pins-and-phy-reset", 1 == pins_calls && 1 == reset_low && 1 == reset_high );
    CHECK( "init-phy-found", 1 == net_driver_pic32mz_phy()->addr && 0x0007C0F1u == net_driver_pic32mz_phy()->id );
    CHECK( "init-station-address", 0x1102 == EMAC1SA2 && 0x3322 == EMAC1SA1 && 0x5544 == EMAC1SA0 );
    CHECK( "init-rx-buffer-size", ( 1536u / 16u ) << 4 == ETHCON2 );
    CHECK( "init-rx-filter", ( ETHRXFC_CRCOKEN | ETHRXFC_UCEN | ETHRXFC_BCEN | ETHRXFC_MCEN ) == ETHRXFC );
    CHECK( "init-rx-start", PHYS( &rx_dcpt[ 0 ] ) == ETHRXST && ETHCON1_RXEN == ETHCON1SET );
    CHECK( "init-mdc-and-frame", EMAC1MCFG_CLKSEL_50 == EMAC1MCFG && 1518 == EMAC1MAXF && EMAC1CFG1_RXENABLE == EMAC1CFG1 );
    bool ring_ok = true;
    for ( int i = 0; i < NET_PIC32MZ_RX_BUFFERS; i++ )
    {
        ring_ok = ring_ok && ( DCPT_EOWN | DCPT_NPV ) == rx_dcpt[ i ].hdr &&
                  PHYS( rx_buf[ i ] ) == rx_dcpt[ i ].buffer &&
                  PHYS( &rx_dcpt[ ( i + 1 ) % NET_PIC32MZ_RX_BUFFERS ] ) == rx_dcpt[ i ].next;
    }
    CHECK( "init-rx-ring", ring_ok );
    CHECK( "init-autoneg-started", 0x1200 == EMAC1MWTD );   /* last MDIO write: BMCR auto-negotiation enable + restart */

    /* ---- receive ---- */
    CHECK( "rx-nothing", 0 == drv.receive( drv.ctx, out, sizeof( out ) ) );

    make_frame( frame, 60, 1 );
    dma_receive( frame, 60, DCPT_SOP | DCPT_EOP );
    ETHCON1SET = 0;
    int32_t n = drv.receive( drv.ctx, out, sizeof( out ) );
    CHECK( "rx-frame", 60 == n && 0 == memcmp( out, frame, 60 ) );
    CHECK( "rx-descriptor-returned", ( DCPT_EOWN | DCPT_NPV ) == rx_dcpt[ 0 ].hdr && ETHCON1_BUFCDEC == ETHCON1SET );
    CHECK( "rx-nothing-after", 0 == drv.receive( drv.ctx, out, sizeof( out ) ) );

    /* Ring wrap-around: 3 rounds of the ring, frames come out in order. */
    bool order_ok = true;
    for ( int round = 0; round < 3 * NET_PIC32MZ_RX_BUFFERS; round++ )
    {
        uint32_t len = 64 + ( uint32_t )round * 50;
        make_frame( frame, len, ( uint8_t )round );
        dma_receive( frame, len, DCPT_SOP | DCPT_EOP );
        n = drv.receive( drv.ctx, out, sizeof( out ) );
        order_ok = order_ok && ( int32_t )len == n && 0 == memcmp( out, frame, len );
    }
    CHECK( "rx-ring-wraps-in-order", order_ok );

    /* Several frames waiting: one per call. */
    for ( int i = 0; i < 3; i++ )
    {
        make_frame( frame, 100, ( uint8_t )( 50 + i ) );
        dma_receive( frame, 100, DCPT_SOP | DCPT_EOP );
    }
    int got = 0;
    while ( drv.receive( drv.ctx, out, sizeof( out ) ) > 0 )
    {
        got++;
    }
    CHECK( "rx-backlog", 3 == got );

    /* Full-size frame with CRC (1518) into a small buffer: clamped, not overrun. */
    make_frame( frame, 1518, 9 );
    dma_receive( frame, 1518, DCPT_SOP | DCPT_EOP );
    memset( out, 0xEE, sizeof( out ) );
    n = drv.receive( drv.ctx, out, 1000 );
    CHECK( "rx-clamped-to-buffer", 1000 == n && 0 == memcmp( out, frame, 1000 ) && 0xEE == out[ 1000 ] );

    /* A frame over two buffers (SOP, then EOP) and a runt are dropped; the next
     * whole frame is returned in the same call. */
    make_frame( frame, 100, 3 );
    dma_receive( frame, 100, DCPT_SOP );
    dma_receive( frame, 100, DCPT_EOP );
    dma_receive( frame, 10, DCPT_SOP | DCPT_EOP );
    make_frame( frame, 70, 4 );
    dma_receive( frame, 70, DCPT_SOP | DCPT_EOP );
    n = drv.receive( drv.ctx, out, sizeof( out ) );
    CHECK( "rx-drops-partial-and-runt", 70 == n && 0 == memcmp( out, frame, 70 ) );
    CHECK( "rx-all-descriptors-returned", 0 == drv.receive( drv.ctx, out, sizeof( out ) ) );

    ETHIRQ = ETHIRQ_RXBUFNA | ETHIRQ_RXOVFLW;
    ETHIRQCLR = 0;
    drv.receive( drv.ctx, out, sizeof( out ) );
    CHECK( "rx-clears-overflow-flags", ( ETHIRQ_RXBUFNA | ETHIRQ_RXOVFLW ) == ETHIRQCLR );
    ETHIRQ = 0;

    /* ---- transmit ---- */
    make_frame( frame, 342, 7 );
    ETHCON1 = 0;
    CHECK( "tx-send", 0 == drv.send( drv.ctx, frame, 342 ) );
    CHECK( "tx-buffer", 0 == memcmp( tx_buf, frame, 342 ) );
    CHECK( "tx-descriptor", ( DCPT_SOP | DCPT_EOP | DCPT_NPV | DCPT_EOWN | ( 342u << 16 ) ) == tx_dcpt[ 0 ].hdr &&
           0 == tx_dcpt[ 1 ].hdr && PHYS( &tx_dcpt[ 1 ] ) == tx_dcpt[ 0 ].next );
    CHECK( "tx-started", PHYS( &tx_dcpt[ 0 ] ) == ETHTXST && ETHCON1_TXRTS == ETHCON1SET );
    CHECK( "tx-rejects-empty-and-oversize", -1 == drv.send( drv.ctx, frame, 0 ) && -1 == drv.send( drv.ctx, frame, 1537 ) );
    ETHCON1 = ETHCON1_TXRTS;    /* previous frame never finishes */
    CHECK( "tx-busy-times-out", -1 == drv.send( drv.ctx, frame, 60 ) );
    ETHCON1 = 0;

    /* ---- link and MAC mode ---- */
    CHECK( "link-down", !drv.link_up( drv.ctx ) );
    fake_phy_reg[ 1 ] = 0x782D;
    fake_phy_reg[ 4 ] = 0x01E1;
    fake_phy_reg[ 5 ] = 0x41E1;     /* partner: 100 full */
    EMAC1SUPPSET = EMAC1SUPPCLR = 0;
    CHECK( "link-up-100-full", drv.link_up( drv.ctx ) && ( EMAC1CFG2 & EMAC1CFG2_FULLDPLX ) &&
           0x15 == EMAC1IPGT && EMAC1SUPP_SPEEDRMII == EMAC1SUPPSET );
    fake_phy_reg[ 1 ] = 0x7809;
    CHECK( "link-lost", !drv.link_up( drv.ctx ) );
    fake_phy_reg[ 1 ] = 0x782D;
    fake_phy_reg[ 5 ] = 0x0021;     /* partner: 10 half */
    EMAC1SUPPSET = EMAC1SUPPCLR = 0;
    CHECK( "link-up-10-half", drv.link_up( drv.ctx ) && !( EMAC1CFG2 & EMAC1CFG2_FULLDPLX ) &&
           0x12 == EMAC1IPGT && EMAC1SUPP_SPEEDRMII == EMAC1SUPPCLR );
    CHECK( "mac-pads-and-crc", ( EMAC1CFG2_PADENABLE | EMAC1CFG2_CRCENABLE ) == ( EMAC1CFG2 & ( EMAC1CFG2_PADENABLE | EMAC1CFG2_CRCENABLE ) ) );

    /* ---- no PHY: init fails and switches the controller off ---- */
    lan8720_at( 40 );   /* no PHY on the bus */
    net_pic32mz_cfg_setup( &cfg );
    net_driver_pic32mz( &drv, &cfg );
    ETHCON1CLR = 0;
    CHECK( "init-without-phy-fails", 0 != drv.init( drv.ctx, mac ) && ETHCON1_ON == ETHCON1CLR );

    printf( "RESULT %s (%d failed)\n", failures ? "FAIL" : "PASS", failures );
    return failures ? 1 : 0;
}
