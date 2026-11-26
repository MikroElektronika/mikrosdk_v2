/*
 * Host unit test of middleware/net/drivers/stm32 for one family (NET_STM32_F1,
 * F2, F4 or F7, set by CMakeLists.txt). The registers are fake memory, and a
 * small hardware model (NET_STM32_POLL_HOOK) completes the DMA reset when a
 * reference clock is "present", runs MDIO transfers against a simulated
 * LAN8720 and finishes FIFO flushes; the test plays the DMA engines. Tests the
 * driver's logic and its use of the register and descriptor formats (which
 * stm32_regmap checks against ST's headers), not the silicon.
 */

#include <stdio.h>
#include <string.h>
#include <stdint.h>

/* Fake peripherals; the driver uses them instead of the real addresses. */
static uint32_t fake_eth[ 0x1020 / 4 ];
static uint32_t fake_rcc[ 0x100 / 4 ];
static uint32_t fake_syscfg[ 0x40 / 4 ];
static uint32_t fake_afio[ 0x40 / 4 ];
static uint32_t fake_scb[ 0x1000 / 4 ];
#define NET_STM32_ETH_BASE      ( ( uintptr_t )fake_eth )
#define NET_STM32_RCC_BASE      ( ( uintptr_t )fake_rcc )
#define NET_STM32_SYSCFG_BASE   ( ( uintptr_t )fake_syscfg )
#define NET_STM32_AFIO_BASE     ( ( uintptr_t )fake_afio )
#define NET_STM32_SCB_BASE      ( ( uintptr_t )fake_scb )
static void hardware_model( void );
#define NET_STM32_POLL_HOOK()   hardware_model()

/* White box: the driver's descriptors, buffers and state are visible here. */
#include "../../middleware/net/drivers/stm32/net_driver_stm32.c"

static int failures;
#define CHECK( name, cond ) do { if ( cond ) printf( "OK %s\n", name ); \
        else { failures++; printf( "FAIL %s (line %d)\n", name, __LINE__ ); } } while ( 0 )

/* ---------------------------------------------------- Hardware model --- */

static bool ref_clock_present = true;
static uint8_t phy_addr = 1;
static uint16_t phy_reg[ 32 ];
static uint32_t mdio_ops, mdio_bad_range;

static void hardware_model( void )
{
    if ( ref_clock_present )
    {
        ETH->DMABMR &= ~DMABMR_SR;
    }
    ETH->DMAOMR &= ~DMAOMR_FTF;
    uint32_t ar = ETH->MACMIIAR;
    if ( ar & MACMIIAR_MB )
    {
        uint8_t addr = ( uint8_t )( ( ar >> MACMIIAR_PA_POS ) & 0x1F );
        uint8_t reg = ( uint8_t )( ( ar >> MACMIIAR_MR_POS ) & 0x1F );
        if ( ( ( ar >> MACMIIAR_CR_POS ) & 0x7 ) != eth.mdc_range )
        {
            mdio_bad_range++;
        }
        if ( addr != phy_addr )
        {
            ETH->MACMIIDR = 0xFFFF;
        }
        else if ( ar & MACMIIAR_MW )
        {
            phy_reg[ reg ] = ( uint16_t )ETH->MACMIIDR;
            phy_reg[ 0 ] &= 0x7FFF;     /* BMCR reset finishes at once */
        }
        else
        {
            ETH->MACMIIDR = phy_reg[ reg ];
        }
        ETH->MACMIIAR = ar & ~MACMIIAR_MB;
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

/* Receive DMA: put a frame (plus 4 CRC bytes) into the next descriptor. */
static uint8_t dma_rx_next;
static bool dma_receive( const uint8_t *frame, uint32_t len, uint32_t extra_flags )
{
    dcpt_t *d = &rx_dcpt[ dma_rx_next ];
    if ( !( d->des0 & DES0_OWN ) )
    {
        return false;   /* ring full: the frame is lost */
    }
    memcpy( rx_buf[ dma_rx_next ], frame, len );
    memset( rx_buf[ dma_rx_next ] + len, 0xCC, CRC_SIZE );
    d->des0 = RDES0_FS | RDES0_LS | ( ( len + CRC_SIZE ) << 16 ) | extra_flags;
    dma_rx_next = ( uint8_t )( ( dma_rx_next + 1 ) % NET_STM32_RX_BUFFERS );
    return true;
}

/* Transmit DMA: take every descriptor the driver handed over, in order. */
static uint8_t dma_tx_next;
static uint8_t sent_frame[ BUF_SIZE ];
static uint32_t sent_len, sent_count;
static void dma_transmit( void )
{
    for ( ; ; )
    {
        dcpt_t *d = &tx_dcpt[ dma_tx_next ];
        if ( !( d->des0 & DES0_OWN ) )
        {
            return;
        }
        sent_len = d->des1 & 0x1FFF;
        memcpy( sent_frame, tx_buf[ dma_tx_next ], sent_len );
        sent_count++;
        d->des0 &= ~DES0_OWN;
        dma_tx_next = ( uint8_t )( ( dma_tx_next + 1 ) % NET_STM32_TX_BUFFERS );
    }
}

/* ------------------------------------------------------ GPIO layer fake --- */

static module_struct pins_seen;
static int pins_calls;
void hal_ll_gpio_module_struct_init( module_struct const *module, bool state )
{
    if ( state )
    {
        pins_seen = *module;
        pins_calls++;
    }
}

static bool pin_has( uint32_t name, uint32_t af, uint32_t config )
{
    for ( int i = 0; i < 13 && pins_seen.pins[ i ] != ( uint32_t )GPIO_MODULE_STRUCT_END; i++ )
    {
        if ( pins_seen.pins[ i ] == ( uint32_t )VALUE( name, af ) && pins_seen.configs[ i ] == config )
        {
            return true;
        }
    }
    return false;
}

static int pin_count( void )
{
    int n = 0;
    while ( n < 13 && pins_seen.pins[ n ] != ( uint32_t )GPIO_MODULE_STRUCT_END )
    {
        n++;
    }
    return n;
}

static int reset_low;
err_t digital_out_init( digital_out_t *out, pin_name_t name ) { out->pin = name; return DIGITAL_OUT_SUCCESS; }
err_t digital_out_low( digital_out_t *out ) { ( void )out; reset_low++; return 0; }
err_t digital_out_high( digital_out_t *out ) { ( void )out; return 0; }
void Delay_ms( uint32_t ms ) { ( void )ms; }

/* ------------------------------------------------------------- Helpers --- */

static void make_frame( uint8_t *f, uint32_t len, uint8_t tag )
{
    for ( uint32_t i = 0; i < len; i++ )
    {
        f[ i ] = ( uint8_t )( tag + i * 13 );
    }
}

static void clear_hardware( void )
{
    memset( fake_eth, 0, sizeof( fake_eth ) );
    memset( fake_rcc, 0, sizeof( fake_rcc ) );
    memset( fake_syscfg, 0, sizeof( fake_syscfg ) );
    memset( fake_afio, 0, sizeof( fake_afio ) );
    memset( fake_scb, 0, sizeof( fake_scb ) );
    memset( &pins_seen, 0, sizeof( pins_seen ) );
    dma_rx_next = dma_tx_next = 0;
    ref_clock_present = true;
    phy_addr = 1;
    lan8720();
}

#if defined( NET_STM32_F1 )
#define FAMILY "F1"
#define EXPECTED_MDC 0          /* 72 MHz: HCLK/42 */
#elif defined( NET_STM32_F2 )
#define FAMILY "F2"
#define EXPECTED_MDC 1          /* 120 MHz: HCLK/62 */
#elif defined( NET_STM32_F4 )
#define FAMILY "F4"
#define EXPECTED_MDC 4          /* 168 MHz: HCLK/102 */
#else
#define FAMILY "F7"
#define EXPECTED_MDC 4          /* 216 MHz: HCLK/102 */
#endif

int main( void )
{
    static const uint8_t mac[ 6 ] = { 0x02, 0x11, 0x22, 0x33, 0x44, 0x55 };
    static uint8_t frame[ 2048 ], out[ 2048 ];
    net_driver_t drv;
    net_stm32_cfg_t cfg;
    printf( "family %s\n", FAMILY );

    /* ---- defaults and init ---- */
    clear_hardware();
    net_stm32_cfg_setup( &cfg );
    CHECK( "cfg-defaults", NET_STM32_TX_PINS_PB11_PB12_PB13 == cfg.tx_pins && NET_STM32_REF_CLOCK_MCO == cfg.ref_clock &&
           HAL_PIN_NC == cfg.phy_reset && NET_PHY_ADDR_AUTO == cfg.phy_addr );
    cfg.phy_reset = 77;
    net_driver_stm32( &drv, &cfg );
    CHECK( "init", 0 == drv.init( drv.ctx, mac ) );
    CHECK( "init-phy-found-and-reset", 1 == net_driver_stm32_phy()->addr && 0x0007C0F1u == net_driver_stm32_phy()->id &&
           1 == reset_low );
    CHECK( "init-mdc-range", EXPECTED_MDC == eth.mdc_range && mdio_ops > 0 && 0 == mdio_bad_range );

#if defined( NET_STM32_F1 )
    CHECK( "pins-rmii-f1", 10 == pin_count() && pin_has( GPIO_PA1, 0, CFG_IN ) && pin_has( GPIO_PA2, 0, CFG_OUT ) &&
           pin_has( GPIO_PA7, 0, CFG_IN ) && pin_has( GPIO_PC1, 0, CFG_OUT ) && pin_has( GPIO_PC4, 0, CFG_IN ) &&
           pin_has( GPIO_PC5, 0, CFG_IN ) && pin_has( GPIO_PB11, 0, CFG_OUT ) && pin_has( GPIO_PB12, 0, CFG_OUT ) &&
           pin_has( GPIO_PB13, 0, CFG_OUT ) && pin_has( GPIO_PA8, 0, CFG_OUT ) && 0 == pins_seen.gpio_remap );
    CHECK( "rmii-selected-afio", AFIO_MAPR & AFIO_MAPR_MII_RMII_SEL );
    CHECK( "mco-sysclk", RCC_CFGR_MCO_SYSCLK == ( RCC_CFGR & RCC_CFGR_MCO_MASK ) );
    CHECK( "mac-clocks-on-reset-released", RCC_ETH_CLOCKS == ( RCC_AHBENR & RCC_ETH_CLOCKS ) && !( RCC_AHBRSTR & RCC_ETH_RESET ) );
#else
    CHECK( "pins-rmii-af11", 10 == pin_count() && pin_has( GPIO_PA1, 11, CFG_IN ) && pin_has( GPIO_PA2, 11, CFG_OUT ) &&
           pin_has( GPIO_PA7, 11, CFG_IN ) && pin_has( GPIO_PC1, 11, CFG_OUT ) && pin_has( GPIO_PC4, 11, CFG_IN ) &&
           pin_has( GPIO_PC5, 11, CFG_IN ) && pin_has( GPIO_PB11, 11, CFG_OUT ) && pin_has( GPIO_PB12, 11, CFG_OUT ) &&
           pin_has( GPIO_PB13, 11, CFG_OUT ) && pin_has( GPIO_PA8, 0, CFG_OUT ) );
    CHECK( "rmii-selected-syscfg", ( SYSCFG_PMC & SYSCFG_PMC_MII_RMII_SEL ) && ( RCC_APB2ENR & RCC_APB2ENR_SYSCFGEN ) );
    CHECK( "mco1-pll-div", ( RCC_CFGR_MCO1_PLL | RCC_CFGR_MCO1PRE_DIV( cfg.mco_div ) ) == ( RCC_CFGR & RCC_CFGR_MCO1_MASK ) );
    CHECK( "mac-clocks-on-reset-released", RCC_ETH_CLOCKS == ( RCC_AHB1ENR & RCC_ETH_CLOCKS ) && !( RCC_AHB1RSTR & RCC_ETH_RESET ) );
#endif
    CHECK( "mac-address", 0x5544u == ETH->MACA0HR && 0x33221102u == ETH->MACA0LR );
    CHECK( "mac-filter-multicast", MACFFR_PAM == ETH->MACFFR );
    CHECK( "mac-started", ( MACCR_TE | MACCR_RE | MACCR_FES | MACCR_DM ) == ETH->MACCR );
    CHECK( "dma-started", ( DMAOMR_ST | DMAOMR_SR | DMAOMR_TSF | DMAOMR_RSF ) == ETH->DMAOMR &&
           ( DMABMR_AAB | DMABMR_USP | DMABMR_RDP_32 | DMABMR_FB | DMABMR_PBL_32 ) == ETH->DMABMR );
    CHECK( "dma-rings", ADDR( &tx_dcpt[ 0 ] ) == ETH->DMATDLAR && ADDR( &rx_dcpt[ 0 ] ) == ETH->DMARDLAR );
    bool rings = true;
    for ( int i = 0; i < NET_STM32_RX_BUFFERS; i++ )
    {
        rings = rings && DES0_OWN == rx_dcpt[ i ].des0 && ( RDES1_RCH | BUF_SIZE ) == rx_dcpt[ i ].des1 &&
                ADDR( rx_buf[ i ] ) == rx_dcpt[ i ].des2 && ADDR( &rx_dcpt[ ( i + 1 ) % NET_STM32_RX_BUFFERS ] ) == rx_dcpt[ i ].des3;
    }
    for ( int i = 0; i < NET_STM32_TX_BUFFERS; i++ )
    {
        rings = rings && TDES0_TCH == tx_dcpt[ i ].des0 && ADDR( tx_buf[ i ] ) == tx_dcpt[ i ].des2 &&
                ADDR( &tx_dcpt[ ( i + 1 ) % NET_STM32_TX_BUFFERS ] ) == tx_dcpt[ i ].des3;
    }
    CHECK( "descriptor-rings", rings );
    CHECK( "descriptor-cache-lines", 32 == sizeof( dcpt_t ) && 0 == ( ( uintptr_t )rx_dcpt % 32 ) &&
           0 == ( ( uintptr_t )rx_buf % 32 ) && 0 == ( ( uintptr_t )tx_buf % 32 ) );

    /* ---- receive ---- */
    CHECK( "rx-nothing", 0 == drv.receive( drv.ctx, out, sizeof( out ) ) );
    make_frame( frame, 60, 1 );
    dma_receive( frame, 60, 0 );
    int32_t n = drv.receive( drv.ctx, out, sizeof( out ) );
    CHECK( "rx-frame-without-crc", 60 == n && 0 == memcmp( out, frame, 60 ) );
    CHECK( "rx-descriptor-returned", DES0_OWN == rx_dcpt[ 0 ].des0 );

    bool order = true;
    for ( int r = 0; r < 3 * NET_STM32_RX_BUFFERS; r++ )
    {
        uint32_t len = 64 + ( uint32_t )r * 55;
        make_frame( frame, len, ( uint8_t )r );
        dma_receive( frame, len, 0 );
        n = drv.receive( drv.ctx, out, sizeof( out ) );
        order = order && ( int32_t )len == n && 0 == memcmp( out, frame, len );
    }
    CHECK( "rx-ring-wraps-in-order", order );

    make_frame( frame, 1514, 9 );
    dma_receive( frame, 1514, 0 );
    memset( out, 0xEE, sizeof( out ) );
    n = drv.receive( drv.ctx, out, 1000 );
    CHECK( "rx-clamped-to-buffer", 1000 == n && 0 == memcmp( out, frame, 1000 ) && 0xEE == out[ 1000 ] );

    make_frame( frame, 80, 5 );
    dma_receive( frame, 80, RDES0_ES );     /* errored */
    dma_receive( frame, 8, 0 );             /* runt */
    make_frame( frame, 70, 6 );
    dma_receive( frame, 70, 0 );
    n = drv.receive( drv.ctx, out, sizeof( out ) );
    CHECK( "rx-drops-errors-and-runts", 70 == n && 0 == memcmp( out, frame, 70 ) );
    CHECK( "rx-all-returned", 0 == drv.receive( drv.ctx, out, sizeof( out ) ) );

    for ( int i = 0; i < NET_STM32_RX_BUFFERS; i++ )
    {
        make_frame( frame, 100, ( uint8_t )i );
        dma_receive( frame, 100, 0 );
    }
    CHECK( "rx-ring-full", !dma_receive( frame, 100, 0 ) );
    ETH->DMASR = DMASR_RBUS | DMASR_TBUS;
    ETH->DMARPDR = 0xFFFFFFFFu;
    int got = 0;
    while ( drv.receive( drv.ctx, out, sizeof( out ) ) > 0 )
    {
        got++;
    }
    CHECK( "rx-backlog-and-resume", NET_STM32_RX_BUFFERS == got && DMASR_RBUS == ETH->DMASR && 0 == ETH->DMARPDR );

    /* ---- transmit ---- */
    ETH->DMASR = DMASR_TBUS | DMASR_RBUS;
    ETH->DMATPDR = 0xFFFFFFFFu;
    make_frame( frame, 342, 7 );
    CHECK( "tx-send", 0 == drv.send( drv.ctx, frame, 342 ) );
    CHECK( "tx-descriptor", ( DES0_OWN | TDES0_FS | TDES0_LS | TDES0_TCH ) == tx_dcpt[ 0 ].des0 && 342 == tx_dcpt[ 0 ].des1 );
    CHECK( "tx-dma-resumed", DMASR_TBUS == ETH->DMASR && 0 == ETH->DMATPDR );
    dma_transmit();
    CHECK( "tx-frame-on-wire", 1 == sent_count && 342 == sent_len && 0 == memcmp( sent_frame, frame, 342 ) );

    bool tx_ok = true;
    for ( int r = 0; r < 3 * NET_STM32_TX_BUFFERS; r++ )
    {
        uint32_t len = 60 + ( uint32_t )r * 99;
        make_frame( frame, len, ( uint8_t )( 40 + r ) );
        tx_ok = tx_ok && 0 == drv.send( drv.ctx, frame, ( uint16_t )len );
        dma_transmit();
        tx_ok = tx_ok && len == sent_len && 0 == memcmp( sent_frame, frame, len );
    }
    CHECK( "tx-ring-wraps", tx_ok );
    for ( int i = 0; i < NET_STM32_TX_BUFFERS; i++ )
    {
        drv.send( drv.ctx, frame, 60 );     /* the DMA takes nothing: ring fills up */
    }
    CHECK( "tx-full-ring-times-out", -1 == drv.send( drv.ctx, frame, 60 ) );
    dma_transmit();
    CHECK( "tx-rejects-empty-and-oversize", -1 == drv.send( drv.ctx, frame, 0 ) && -1 == drv.send( drv.ctx, frame, 1537 ) );

    /* ---- link and MAC mode ---- */
    CHECK( "link-down", !drv.link_up( drv.ctx ) );
    phy_reg[ 1 ] = 0x782D;
    phy_reg[ 5 ] = 0x41E1;      /* partner 100 full */
    CHECK( "link-100-full", drv.link_up( drv.ctx ) && ( ETH->MACCR & MACCR_FES ) && ( ETH->MACCR & MACCR_DM ) &&
           ( ETH->MACCR & MACCR_TE ) && ( ETH->MACCR & MACCR_RE ) );
    phy_reg[ 1 ] = 0x7809;
    CHECK( "link-lost", !drv.link_up( drv.ctx ) );
    phy_reg[ 1 ] = 0x782D;
    phy_reg[ 5 ] = 0x0021;      /* partner 10 half */
    CHECK( "link-10-half", drv.link_up( drv.ctx ) && !( ETH->MACCR & ( MACCR_FES | MACCR_DM ) ) &&
           ( ETH->MACCR & ( MACCR_TE | MACCR_RE ) ) == ( MACCR_TE | MACCR_RE ) );

#if defined( NET_STM32_F7 )
    /* ---- data cache on: buffers and descriptors cleaned / invalidated ---- */
    SCB_CCR |= SCB_CCR_DC;
    SCB_DCCMVAC = 0;
    SCB_DCIMVAC = 0;
    uint8_t slot = eth.tx_next;
    drv.send( drv.ctx, frame, 100 );
    CHECK( "cache-clean-before-dma", ADDR( &tx_dcpt[ slot ] ) == SCB_DCCMVAC );
    dma_transmit();
    make_frame( frame, 100, 3 );
    slot = eth.rx_next;
    dma_receive( frame, 100, 0 );
    drv.receive( drv.ctx, out, sizeof( out ) );
    CHECK( "cache-invalidate-before-cpu", ( SCB_DCIMVAC >= ADDR( rx_buf[ slot ] ) && SCB_DCIMVAC < ADDR( rx_buf[ slot ] ) + 100 ) ||
           SCB_DCIMVAC == ADDR( &rx_dcpt[ ( slot + 1 ) % NET_STM32_RX_BUFFERS ] ) );
    SCB_CCR = 0;
#endif

    /* ---- board variants and failures ---- */
    clear_hardware();
    net_stm32_cfg_setup( &cfg );
    cfg.tx_pins = NET_STM32_TX_PINS_PG11_PG13_PG14;
    cfg.ref_clock = NET_STM32_REF_CLOCK_BOARD;
    net_driver_stm32( &drv, &cfg );
    CHECK( "init-pg-pins-board-clock", 0 == drv.init( drv.ctx, mac ) && 9 == pin_count() &&
           pin_has( GPIO_PG11, AF_ETH, CFG_OUT ) && pin_has( GPIO_PG13, AF_ETH, CFG_OUT ) && pin_has( GPIO_PG14, AF_ETH, CFG_OUT ) &&
           !pin_has( GPIO_PB11, AF_ETH, CFG_OUT ) && 0 == RCC_CFGR );

    clear_hardware();
    ref_clock_present = false;
    net_stm32_cfg_setup( &cfg );
    net_driver_stm32( &drv, &cfg );
    CHECK( "init-without-reference-clock-fails", -2 == drv.init( drv.ctx, mac ) );

    clear_hardware();
    phy_addr = 40;              /* nobody answers on MDIO */
    net_driver_stm32( &drv, &cfg );
    CHECK( "init-without-phy-fails", -1 == drv.init( drv.ctx, mac ) );

    printf( "RESULT %s (%d failed)\n", failures ? "FAIL" : "PASS", failures );
    return failures ? 1 : 0;
}
