/*
 * Host unit test of middleware/net/drivers/tm4c with fake registers and a
 * hardware model (NET_TM4C_POLL_HOOK): peripherals become ready when clocked,
 * resets finish, MDIO transfers go to a simulated integrated PHY; the test
 * plays the DMA. tm4c_regmap checks the registers against TI's headers.
 */

#include <stdio.h>
#include <string.h>
#include <stdint.h>

static uint32_t fake_emac[ 0x1000 / 4 ];
static uint32_t fake_sysctl[ 0xB00 / 4 ];
static uint32_t fake_gpiok[ 0x600 / 4 ];
#define NET_TM4C_EMAC_BASE      ( ( uintptr_t )fake_emac )
#define NET_TM4C_SYSCTL_BASE    ( ( uintptr_t )fake_sysctl )
#define NET_TM4C_GPIOK_BASE     ( ( uintptr_t )fake_gpiok )
static void hardware_model( void );
#define NET_TM4C_POLL_HOOK()    hardware_model()

#include "../../middleware/net/drivers/tm4c/net_driver_tm4c.c"

static int failures;
#define CHECK( name, cond ) do { if ( cond ) printf( "OK %s\n", name ); \
        else { failures++; printf( "FAIL %s (line %d)\n", name, __LINE__ ); } } while ( 0 )

static bool emac_powers_up = true;
static uint8_t phy_addr = 0;            /* the integrated PHY answers at 0 */
static uint16_t phy_reg[ 32 ];
static uint32_t mdio_ops, mdio_bad_range, mac_resets;
static uint32_t pc_at_reset;

static void hardware_model( void )
{
    if ( emac_powers_up )
    {
        SYSCTL_PREMAC = SYSCTL_RCGCEMAC & SYSCTL_PCEMAC & ~SYSCTL_SREMAC;
        SYSCTL_PREPHY = SYSCTL_RCGCEPHY & SYSCTL_PCEPHY & ~SYSCTL_SREPHY;
    }
    SYSCTL_PRGPIO = SYSCTL_RCGCGPIO;
    if ( SYSCTL_SREMAC & SYSCTL_EMAC0 )
    {
        mac_resets++;
        pc_at_reset = EMAC_PC;
    }
    EMAC_DMABUSMOD &= ~DMABUSMOD_SWR;
    EMAC_DMAOPMODE &= ~DMAOPMODE_FTF;
    uint32_t a = EMAC_MIIADDR;
    if ( a & MIIADDR_MIIB )
    {
        uint8_t addr = ( uint8_t )( ( a >> MIIADDR_PLA_POS ) & 0x1F );
        uint8_t reg = ( uint8_t )( ( a >> MIIADDR_MII_POS ) & 0x1F );
        if ( ( ( a >> MIIADDR_CR_POS ) & 0xF ) != eth.mdc_range )
        {
            mdio_bad_range++;
        }
        if ( addr != phy_addr )
        {
            EMAC_MIIDATA = 0xFFFF;
        }
        else if ( a & MIIADDR_MIIW )
        {
            phy_reg[ reg ] = ( uint16_t )EMAC_MIIDATA;
            phy_reg[ 0 ] &= 0x7FFF;
        }
        else
        {
            EMAC_MIIDATA = phy_reg[ reg ];
        }
        EMAC_MIIADDR = a & ~MIIADDR_MIIB;
        mdio_ops++;
    }
}

static void integrated_phy( void )
{
    memset( phy_reg, 0, sizeof( phy_reg ) );
    phy_reg[ 2 ] = 0x2000;      /* TI */
    phy_reg[ 3 ] = 0xA221;
    phy_reg[ 1 ] = 0x7809;
}

static uint8_t dma_rx_next;
static bool dma_receive( const uint8_t *frame, uint32_t len, uint32_t extra )
{
    dcpt_t *d = &rx_dcpt[ dma_rx_next ];
    if ( !( d->des0 & DES0_OWN ) )
    {
        return false;
    }
    memcpy( rx_buf[ dma_rx_next ], frame, len );
    d->des0 = RDES0_FS | RDES0_LS | ( ( len + CRC_SIZE ) << 16 ) | extra;
    dma_rx_next = ( uint8_t )( ( dma_rx_next + 1 ) % NET_TM4C_RX_BUFFERS );
    return true;
}

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
        dma_tx_next = ( uint8_t )( ( dma_tx_next + 1 ) % NET_TM4C_TX_BUFFERS );
    }
}

static void make_frame( uint8_t *f, uint32_t len, uint8_t tag )
{
    for ( uint32_t i = 0; i < len; i++ )
    {
        f[ i ] = ( uint8_t )( tag + i * 17 );
    }
}

static void clear_hardware( void )
{
    memset( fake_emac, 0, sizeof( fake_emac ) );
    memset( fake_sysctl, 0, sizeof( fake_sysctl ) );
    memset( fake_gpiok, 0, sizeof( fake_gpiok ) );
    fake_gpiok[ 0x52C / 4 ] = 0x0000000Fu;      /* PCTL of PK0 in use by something else */
    dma_rx_next = dma_tx_next = 0;
    emac_powers_up = true;
    phy_addr = 0;
    mac_resets = 0;
    integrated_phy();
}

int main( void )
{
    static const uint8_t mac[ 6 ] = { 0x02, 0x11, 0x22, 0x33, 0x44, 0x55 };
    static uint8_t frame[ 2048 ], out[ 2048 ];
    net_driver_t drv;
    net_tm4c_cfg_t cfg;

    clear_hardware();
    net_tm4c_cfg_setup( &cfg );
    CHECK( "cfg-defaults", cfg.leds && NET_PHY_ADDR_AUTO == cfg.phy_addr );
    net_driver_tm4c( &drv, &cfg );
    CHECK( "init", 0 == drv.init( drv.ctx, mac ) );
    CHECK( "init-integrated-phy", 0 == net_driver_tm4c_phy()->addr && 0x2000A221u == net_driver_tm4c_phy()->id &&
           mdio_ops > 0 && 0 == mdio_bad_range && 1 == eth.mdc_range );
    CHECK( "clocks-power-on", ( SYSCTL_RCGCEMAC & SYSCTL_RCGCEPHY & SYSCTL_PCEMAC & SYSCTL_PCEPHY & SYSCTL_EMAC0 ) &&
           !( SYSCTL_SREMAC & SYSCTL_EMAC0 ) && !( SYSCTL_SREPHY & SYSCTL_EMAC0 ) );
    CHECK( "phy-config-then-reset", mac_resets > 0 && ( PC_MDIXEN | PC_ANEN | PC_ANMODE_ALL ) == pc_at_reset &&
           !( EMAC_PC & ( 1UL << 31 ) ) );
    CHECK( "leds-pk5-pk6", ( ( PCTL_EN0LED << 16 ) | ( PCTL_EN0LED << 20 ) | ( PCTL_EN0LED << 24 ) | 0xFu ) == GPIOK_PCTL &&
           ( ( 1UL << 5 ) | ( 1UL << 6 ) ) == GPIOK_AFSEL && ( ( 1UL << 5 ) | ( 1UL << 6 ) ) == GPIOK_DEN &&
           ( SYSCTL_RCGCGPIO & SYSCTL_GPIOK ) );
    CHECK( "mac-address", 0x5544u == EMAC_ADDR0H && 0x33221102u == EMAC_ADDR0L );
    CHECK( "mac-started", ( CFG_PS | CFG_FES | CFG_DUPM | CFG_TE | CFG_RE ) == EMAC_CFG && FRAMEFLTR_PM == EMAC_FRAMEFLTR );
    CHECK( "dma-started", ( DMAOPMODE_ST | DMAOPMODE_SR | DMAOPMODE_TSF | DMAOPMODE_RSF ) == EMAC_DMAOPMODE &&
           ( DMABUSMOD_AAL | DMABUSMOD_USP | DMABUSMOD_RPBL_32 | DMABUSMOD_FB | DMABUSMOD_PBL_32 ) == EMAC_DMABUSMOD &&
           ADDR( &tx_dcpt[ 0 ] ) == EMAC_TXDLADDR && ADDR( &rx_dcpt[ 0 ] ) == EMAC_RXDLADDR );

    /* receive */
    CHECK( "rx-nothing", 0 == drv.receive( drv.ctx, out, sizeof( out ) ) );
    bool order = true;
    for ( int r = 0; r < 3 * NET_TM4C_RX_BUFFERS; r++ )
    {
        uint32_t len = 60 + ( uint32_t )r * 61;
        make_frame( frame, len, ( uint8_t )r );
        dma_receive( frame, len, 0 );
        int32_t n = drv.receive( drv.ctx, out, sizeof( out ) );
        order = order && ( int32_t )len == n && 0 == memcmp( out, frame, len );
    }
    CHECK( "rx-frames-without-crc-ring-wraps", order );
    make_frame( frame, 80, 5 );
    dma_receive( frame, 80, RDES0_ES );
    dma_receive( frame, 8, 0 );
    make_frame( frame, 70, 6 );
    dma_receive( frame, 70, 0 );
    EMAC_DMARIS = DMARIS_RU | DMARIS_TU;
    EMAC_RXPOLLD = 0xFFFFFFFFu;
    int32_t n = drv.receive( drv.ctx, out, 1000 );
    CHECK( "rx-drops-errors-runts-resumes", 70 == n && 0 == memcmp( out, frame, 70 ) && DMARIS_RU == EMAC_DMARIS &&
           0 == EMAC_RXPOLLD );

    /* transmit */
    EMAC_DMARIS = DMARIS_TU;
    EMAC_TXPOLLD = 0xFFFFFFFFu;
    make_frame( frame, 342, 7 );
    CHECK( "tx-send", 0 == drv.send( drv.ctx, frame, 342 ) &&
           ( DES0_OWN | TDES0_FS | TDES0_LS | TDES0_TCH ) == tx_dcpt[ 0 ].des0 && 342 == tx_dcpt[ 0 ].des1 &&
           DMARIS_TU == EMAC_DMARIS && 0 == EMAC_TXPOLLD );
    dma_transmit();
    CHECK( "tx-frame-on-wire", 1 == sent_count && 342 == sent_len && 0 == memcmp( sent_frame, frame, 342 ) );
    for ( int i = 0; i < NET_TM4C_TX_BUFFERS; i++ )
    {
        drv.send( drv.ctx, frame, 60 );
    }
    CHECK( "tx-full-ring-times-out", -1 == drv.send( drv.ctx, frame, 60 ) );
    dma_transmit();

    /* link */
    CHECK( "link-down", !drv.link_up( drv.ctx ) );
    phy_reg[ 1 ] = 0x782D;
    phy_reg[ 5 ] = 0x41E1;
    CHECK( "link-100-full", drv.link_up( drv.ctx ) && ( EMAC_CFG & CFG_FES ) && ( EMAC_CFG & CFG_DUPM ) && ( EMAC_CFG & CFG_PS ) );
    phy_reg[ 1 ] = 0x7809;
    drv.link_up( drv.ctx );
    phy_reg[ 1 ] = 0x782D;
    phy_reg[ 5 ] = 0x0021;
    CHECK( "link-10-half", drv.link_up( drv.ctx ) && !( EMAC_CFG & ( CFG_FES | CFG_DUPM ) ) &&
           ( EMAC_CFG & ( CFG_TE | CFG_RE ) ) == ( CFG_TE | CFG_RE ) );

    /* options and failures */
    clear_hardware();
    net_tm4c_cfg_setup( &cfg );
    cfg.leds = false;
    net_driver_tm4c( &drv, &cfg );
    CHECK( "no-leds", 0 == drv.init( drv.ctx, mac ) && 0x0000000Fu == GPIOK_PCTL && 0 == GPIOK_AFSEL );

    clear_hardware();
    emac_powers_up = false;
    net_tm4c_cfg_setup( &cfg );
    net_driver_tm4c( &drv, &cfg );
    CHECK( "init-mac-not-ready-fails", -2 == drv.init( drv.ctx, mac ) );

    clear_hardware();
    phy_addr = 40;
    net_driver_tm4c( &drv, &cfg );
    CHECK( "init-without-phy-fails", -1 == drv.init( drv.ctx, mac ) );

    printf( "RESULT %s (%d failed)\n", failures ? "FAIL" : "PASS", failures );
    return failures ? 1 : 0;
}
