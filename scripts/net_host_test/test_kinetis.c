/*
 * Host unit test of middleware/net/drivers/kinetis for one variant
 * (NET_KINETIS_K60_K64, K65_K66 or KV58, set by CMakeLists.txt). The registers
 * are fake memory; a small hardware model (NET_KINETIS_POLL_HOOK) finishes the
 * reset and runs MDIO frames against a simulated LAN8720; the test plays the
 * DMA. Tests the driver's logic and its use of the register and descriptor
 * formats (kinetis_regmap checks the registers against NXP's headers).
 */

#include <stdio.h>
#include <string.h>
#include <stdint.h>

static uint32_t fake_enet[ 0x200 / 4 ];
static uint32_t fake_sim[ 0x1100 / 4 ];
static uint32_t fake_porta[ 32 ], fake_portb[ 32 ], fake_porte[ 32 ];
static uint32_t fake_mpu[ 4 ];
static uint32_t fake_scb[ 0x1000 / 4 ];
#define NET_KINETIS_ENET_BASE   ( ( uintptr_t )fake_enet )
#define NET_KINETIS_SIM_BASE    ( ( uintptr_t )fake_sim )
#define NET_KINETIS_PORTA_BASE  ( ( uintptr_t )fake_porta )
#define NET_KINETIS_PORTB_BASE  ( ( uintptr_t )fake_portb )
#define NET_KINETIS_PORTE_BASE  ( ( uintptr_t )fake_porte )
#define NET_KINETIS_MPU_BASE    ( ( uintptr_t )fake_mpu )
#define NET_KINETIS_SCB_BASE    ( ( uintptr_t )fake_scb )
static void hardware_model( void );
#define NET_KINETIS_POLL_HOOK() hardware_model()

#include "../../middleware/net/drivers/kinetis/net_driver_kinetis.c"

static int failures;
#define CHECK( name, cond ) do { if ( cond ) printf( "OK %s\n", name ); \
        else { failures++; printf( "FAIL %s (line %d)\n", name, __LINE__ ); } } while ( 0 )

/* ---------------------------------------------------- Hardware model --- */

static uint8_t phy_addr = 1;
static uint16_t phy_reg[ 32 ];
static uint32_t mdio_ops, mdio_bad_frames;

static void hardware_model( void )
{
    ENET_ECR &= ~ECR_RESET;
    uint32_t f = ENET_MMFR;
    if ( f & MMFR_ST )          /* a frame was written and not run yet */
    {
        uint8_t addr = ( uint8_t )( ( f >> MMFR_PA_POS ) & 0x1F );
        uint8_t reg = ( uint8_t )( ( f >> MMFR_RA_POS ) & 0x1F );
        uint32_t op = f & ( 3UL << 28 );
        if ( ( f & ( 3UL << 16 ) ) != MMFR_TA || ( op != MMFR_OP_READ && op != MMFR_OP_WRITE ) )
        {
            mdio_bad_frames++;
        }
        uint16_t data = 0xFFFF;
        if ( addr == phy_addr )
        {
            if ( op == MMFR_OP_WRITE )
            {
                phy_reg[ reg ] = ( uint16_t )( f & 0xFFFF );
                phy_reg[ 0 ] &= 0x7FFF;
            }
            data = phy_reg[ reg ];
        }
        ENET_MMFR = data;           /* frame done: start bits gone, data in the low half */
        ENET_EIR |= EIR_MII;
        mdio_ops++;
    }
}

static void lan8720( void )
{
    memset( phy_reg, 0, sizeof( phy_reg ) );
    phy_reg[ 2 ] = 0x0007;
    phy_reg[ 3 ] = 0xC0F1;
    phy_reg[ 1 ] = 0x7809;
}

static uint8_t dma_rx_next;
static bool dma_receive( const uint8_t *frame, uint16_t len, uint16_t extra )
{
    bd_t *d = &rx_bd[ dma_rx_next ];
    if ( !( d->control & RXBD_E ) )
    {
        return false;
    }
    memcpy( rx_buf[ dma_rx_next ], frame, len );
    d->length = len;
    d->control = ( uint16_t )( ( d->control & RXBD_W ) | RXBD_L | extra );
    dma_rx_next = ( uint8_t )( ( dma_rx_next + 1 ) % NET_KINETIS_RX_BUFFERS );
    return true;
}

static uint8_t dma_tx_next;
static uint8_t sent_frame[ BUF_SIZE ];
static uint32_t sent_len, sent_count;
static void dma_transmit( void )
{
    for ( ; ; )
    {
        bd_t *d = &tx_bd[ dma_tx_next ];
        if ( !( d->control & TXBD_R ) )
        {
            return;
        }
        sent_len = d->length;
        memcpy( sent_frame, tx_buf[ dma_tx_next ], sent_len );
        sent_count++;
        d->control &= ( uint16_t )~TXBD_R;
        dma_tx_next = ( uint8_t )( ( dma_tx_next + 1 ) % NET_KINETIS_TX_BUFFERS );
    }
}

static int reset_low;
err_t digital_out_init( digital_out_t *out, pin_name_t name ) { out->pin = name; return DIGITAL_OUT_SUCCESS; }
err_t digital_out_low( digital_out_t *out ) { ( void )out; reset_low++; return 0; }
err_t digital_out_high( digital_out_t *out ) { ( void )out; return 0; }
void Delay_ms( uint32_t ms ) { ( void )ms; }

static void make_frame( uint8_t *f, uint32_t len, uint8_t tag )
{
    for ( uint32_t i = 0; i < len; i++ )
    {
        f[ i ] = ( uint8_t )( tag + i * 11 );
    }
}

static void clear_hardware( void )
{
    memset( fake_enet, 0, sizeof( fake_enet ) );
    memset( fake_sim, 0, sizeof( fake_sim ) );
    memset( fake_porta, 0, sizeof( fake_porta ) );
    memset( fake_portb, 0, sizeof( fake_portb ) );
    memset( fake_porte, 0, sizeof( fake_porte ) );
    fake_mpu[ 0 ] = MPU_CESR_VLD;       /* MPU on after reset */
    memset( fake_scb, 0, sizeof( fake_scb ) );
    dma_rx_next = dma_tx_next = 0;
    phy_addr = 1;
    lan8720();
}

#define PORTA( n ) PCR( NET_KINETIS_PORTA_BASE, n )
#define PORTB( n ) PCR( NET_KINETIS_PORTB_BASE, n )
#define PORTE( n ) PCR( NET_KINETIS_PORTE_BASE, n )

int main( void )
{
    static const uint8_t mac[ 6 ] = { 0x02, 0x11, 0x22, 0x33, 0x44, 0x55 };
    static uint8_t frame[ 2048 ], out[ 2048 ];
    net_driver_t drv;
    net_kinetis_cfg_t cfg;

    clear_hardware();
    net_kinetis_cfg_setup( &cfg );
    CHECK( "cfg-defaults", NET_KINETIS_REF_CLOCK_CLKIN == cfg.ref_clock && cfg.disable_mpu &&
           HAL_PIN_NC == cfg.phy_reset && NET_PHY_ADDR_AUTO == cfg.phy_addr );
    cfg.phy_reset = 77;
    net_driver_kinetis( &drv, &cfg );
    CHECK( "init", 0 == drv.init( drv.ctx, mac ) );
    CHECK( "init-phy-found-and-reset", 1 == net_driver_kinetis_phy()->addr && 0x0007C0F1u == net_driver_kinetis_phy()->id &&
           1 == reset_low && mdio_ops > 0 && 0 == mdio_bad_frames );

    /* Pins as in hw_eth for the variant. */
    uint32_t data_mux = ( NET_KINETIS_PINS_KV58 == cfg.pins ) ? 5u : 4u;
    bool data_pins = PORTA( 5 ) == ( PCR_MUX( 4 ) | PCR_PE );
    for ( int p = 12; p <= 17; p++ )
    {
        data_pins = data_pins && PORTA( p ) == PCR_MUX( data_mux );
    }
    CHECK( "pins-rmii-data", data_pins );
    if ( NET_KINETIS_PINS_K60_K64 == cfg.pins )
    {
        CHECK( "pins-mdio-ptb0-ptb1", ( PCR_MUX( 4 ) | PCR_PE | PCR_PS ) == PORTB( 0 ) && PCR_MUX( 4 ) == PORTB( 1 ) );
    }
    else
    {
        CHECK( "pins-mdio-pta7-pta8", ( PCR_MUX( 5 ) | PCR_PE | PCR_PS ) == PORTA( 7 ) && PCR_MUX( 5 ) == PORTA( 8 ) );
    }
    CHECK( "rmii-clock-clkin", PCR_MUX( 2 ) == PORTE( 26 ) &&
           ( SIM_SOPT2_RMIISRC | SIM_SOPT2_TIMESRC ) == ( SIM_SOPT2 & ( SIM_SOPT2_RMIISRC | SIM_SOPT2_TIMESRC ) ) );
    CHECK( "clocks-on", ( SIM_SCGC2 & SIM_SCGC2_ENET ) &&
           ( SIM_SCGC5_PORTA | SIM_SCGC5_PORTB | SIM_SCGC5_PORTE ) == ( SIM_SCGC5 & ( SIM_SCGC5_PORTA | SIM_SCGC5_PORTB | SIM_SCGC5_PORTE ) ) );
    CHECK( "mpu-off-for-dma", !( MPU_CESR & MPU_CESR_VLD ) );

    uint32_t clock = ( uint32_t )FOSC_KHZ_VALUE * 1000u;
    uint32_t speed = ( ENET_MSCR >> MSCR_MII_SPEED_POS ) & 0x3F;
    uint32_t hold = ( ENET_MSCR >> MSCR_HOLDTIME_POS ) & 0x7;
    CHECK( "mdc-at-most-2.5MHz-hold-10ns", clock / ( ( speed + 1 ) * 2 ) <= 2500000u &&
           clock / ( ( speed + 2 ) * 2 ) < 2500000u &&       /* and not slower than needed */
           ( hold + 1 ) * ( 1000000000u / clock ) >= 10u );
    CHECK( "mac-address", 0x02112233u == ENET_PALR && 0x44550000u == ENET_PAUR );
    CHECK( "rx-config", ( ( 1518UL << RCR_MAX_FL_POS ) | RCR_CRCFWD | RCR_RMII_MODE | RCR_MII_MODE ) == ENET_RCR &&
           TCR_FDEN == ENET_TCR );
    CHECK( "multicast-and-store-forward", 0xFFFFFFFFu == ENET_GAUR && 0xFFFFFFFFu == ENET_GALR && 0 == ENET_IAUR &&
           TFWR_STRFWD == ENET_TFWR && 0 == ENET_RSFL );
    CHECK( "enabled-little-endian", ( ECR_ETHEREN | ECR_DBSWP ) == ENET_ECR && DAR_ACTIVE == ENET_RDAR );
    CHECK( "rings", ADDR( rx_bd ) == ENET_RDSR && ADDR( tx_bd ) == ENET_TDSR && BUF_SIZE == ENET_MRBR &&
           8 == sizeof( bd_t ) && 0 == ADDR( rx_bd ) % 16 && 0 == ADDR( rx_buf ) % 16 && 0 == ADDR( tx_buf ) % 16 );
    bool rings = true;
    for ( int i = 0; i < NET_KINETIS_RX_BUFFERS; i++ )
    {
        rings = rings && rx_bd[ i ].buffer == ADDR( rx_buf[ i ] ) &&
                rx_bd[ i ].control == ( RXBD_E | ( i == NET_KINETIS_RX_BUFFERS - 1 ? RXBD_W : 0 ) );
    }
    for ( int i = 0; i < NET_KINETIS_TX_BUFFERS; i++ )
    {
        rings = rings && tx_bd[ i ].buffer == ADDR( tx_buf[ i ] ) &&
                tx_bd[ i ].control == ( i == NET_KINETIS_TX_BUFFERS - 1 ? TXBD_W : 0 );
    }
    CHECK( "descriptor-rings-wrap-bits", rings );

    /* ---- receive ---- */
    CHECK( "rx-nothing", 0 == drv.receive( drv.ctx, out, sizeof( out ) ) );
    make_frame( frame, 60, 1 );
    dma_receive( frame, 60, 0 );
    ENET_RDAR = 0;
    int32_t n = drv.receive( drv.ctx, out, sizeof( out ) );
    CHECK( "rx-frame", 60 == n && 0 == memcmp( out, frame, 60 ) );
    CHECK( "rx-descriptor-returned", RXBD_E == rx_bd[ 0 ].control && DAR_ACTIVE == ENET_RDAR );
    bool order = true;
    for ( int r = 0; r < 3 * NET_KINETIS_RX_BUFFERS; r++ )
    {
        uint16_t len = ( uint16_t )( 64 + r * 57 );
        make_frame( frame, len, ( uint8_t )r );
        dma_receive( frame, len, 0 );
        n = drv.receive( drv.ctx, out, sizeof( out ) );
        order = order && len == n && 0 == memcmp( out, frame, len );
    }
    CHECK( "rx-ring-wraps-in-order-keeps-wrap-bit", order &&
           ( rx_bd[ NET_KINETIS_RX_BUFFERS - 1 ].control & RXBD_W ) && !( rx_bd[ 0 ].control & RXBD_W ) );
    make_frame( frame, 1514, 9 );
    dma_receive( frame, 1514, 0 );
    memset( out, 0xEE, sizeof( out ) );
    n = drv.receive( drv.ctx, out, 1000 );
    CHECK( "rx-clamped-to-buffer", 1000 == n && 0 == memcmp( out, frame, 1000 ) && 0xEE == out[ 1000 ] );
    make_frame( frame, 80, 5 );
    dma_receive( frame, 80, 0x0004 );       /* CRC error */
    dma_receive( frame, 80, 0x0001 );       /* truncated */
    dma_receive( frame, 8, 0 );             /* runt */
    make_frame( frame, 70, 6 );
    dma_receive( frame, 70, 0 );
    n = drv.receive( drv.ctx, out, sizeof( out ) );
    CHECK( "rx-drops-errors-and-runts", 70 == n && 0 == memcmp( out, frame, 70 ) );
    CHECK( "rx-all-returned", 0 == drv.receive( drv.ctx, out, sizeof( out ) ) );

    /* ---- transmit ---- */
    make_frame( frame, 342, 7 );
    ENET_TDAR = 0;
    CHECK( "tx-send", 0 == drv.send( drv.ctx, frame, 342 ) );
    CHECK( "tx-descriptor", ( TXBD_R | TXBD_L | TXBD_TC ) == tx_bd[ 0 ].control && 342 == tx_bd[ 0 ].length &&
           DAR_ACTIVE == ENET_TDAR );
    dma_transmit();
    CHECK( "tx-frame-on-wire", 1 == sent_count && 342 == sent_len && 0 == memcmp( sent_frame, frame, 342 ) );
    bool tx_ok = true;
    for ( int r = 0; r < 3 * NET_KINETIS_TX_BUFFERS; r++ )
    {
        uint16_t len = ( uint16_t )( 60 + r * 101 );
        make_frame( frame, len, ( uint8_t )( 40 + r ) );
        tx_ok = tx_ok && 0 == drv.send( drv.ctx, frame, len );
        dma_transmit();
        tx_ok = tx_ok && len == sent_len && 0 == memcmp( sent_frame, frame, len );
    }
    CHECK( "tx-ring-wraps-keeps-wrap-bit", tx_ok && ( tx_bd[ NET_KINETIS_TX_BUFFERS - 1 ].control & TXBD_W ) );
    for ( int i = 0; i < NET_KINETIS_TX_BUFFERS; i++ )
    {
        drv.send( drv.ctx, frame, 60 );
    }
    CHECK( "tx-full-ring-times-out", -1 == drv.send( drv.ctx, frame, 60 ) );
    dma_transmit();
    CHECK( "tx-rejects-empty-and-oversize", -1 == drv.send( drv.ctx, frame, 0 ) && -1 == drv.send( drv.ctx, frame, 1537 ) );

    /* ---- link ---- */
    CHECK( "link-down", !drv.link_up( drv.ctx ) );
    phy_reg[ 1 ] = 0x782D;
    phy_reg[ 5 ] = 0x41E1;
    CHECK( "link-100-full", drv.link_up( drv.ctx ) && ( ENET_TCR & TCR_FDEN ) && !( ENET_RCR & ( RCR_RMII_10T | RCR_DRT ) ) &&
           ( ENET_RCR & RCR_RMII_MODE ) && ( ENET_ECR & ECR_ETHEREN ) );
    phy_reg[ 1 ] = 0x7809;
    CHECK( "link-lost", !drv.link_up( drv.ctx ) );
    phy_reg[ 1 ] = 0x782D;
    phy_reg[ 5 ] = 0x0021;
    CHECK( "link-10-half", drv.link_up( drv.ctx ) && !( ENET_TCR & TCR_FDEN ) &&
           ( RCR_RMII_10T | RCR_DRT ) == ( ENET_RCR & ( RCR_RMII_10T | RCR_DRT ) ) && ( ENET_RCR & RCR_CRCFWD ) );

#if defined( NET_KINETIS_KV58 )
    SCB_CCR |= SCB_CCR_DC;
    SCB_DCCMVAC = 0;
    SCB_DCIMVAC = 0;
    uint8_t slot = eth.tx_next;
    drv.send( drv.ctx, frame, 100 );
    CHECK( "cache-clean-before-dma", ( SCB_DCCMVAC & ~31u ) == ( ADDR( &tx_bd[ slot ] ) & ~31u ) );
    dma_transmit();
    slot = eth.rx_next;
    make_frame( frame, 100, 3 );
    dma_receive( frame, 100, 0 );
    drv.receive( drv.ctx, out, sizeof( out ) );
    CHECK( "cache-invalidate-before-cpu", 0 != SCB_DCIMVAC );
    SCB_CCR = 0;
#endif

    /* ---- options and failures ---- */
    clear_hardware();
    net_kinetis_cfg_setup( &cfg );
    cfg.ref_clock = NET_KINETIS_REF_CLOCK_EXTAL;
    cfg.disable_mpu = false;
    SIM_SOPT2 = SIM_SOPT2_RMIISRC;
    net_driver_kinetis( &drv, &cfg );
    CHECK( "extal-clock-and-mpu-kept", 0 == drv.init( drv.ctx, mac ) && !( SIM_SOPT2 & SIM_SOPT2_RMIISRC ) &&
           0 == PORTE( 26 ) && ( MPU_CESR & MPU_CESR_VLD ) );

    clear_hardware();
    phy_addr = 40;
    net_kinetis_cfg_setup( &cfg );
    net_driver_kinetis( &drv, &cfg );
    CHECK( "init-without-phy-fails", -1 == drv.init( drv.ctx, mac ) );

    printf( "RESULT %s (%d failed)\n", failures ? "FAIL" : "PASS", failures );
    return failures ? 1 : 0;
}
