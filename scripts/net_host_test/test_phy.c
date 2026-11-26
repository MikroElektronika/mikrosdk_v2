/*
 * Host unit test of middleware/net/drivers/phy (generic clause 22 PHY) with a
 * simulated PHY behind a fake MDIO bus. Exit status 0 when every check passed.
 */

#include <stdio.h>
#include <string.h>

#include "net_phy.h"

static int failures;
#define CHECK( name, cond ) do { if ( cond ) printf( "OK %s\n", name ); \
        else { failures++; printf( "FAIL %s (line %d)\n", name, __LINE__ ); } } while ( 0 )

/* Simulated PHY */
static struct
{
    uint8_t addr;               /* bus address it answers on */
    uint16_t reg[ 32 ];
    int reset_reads;            /* reads of BMCR until the reset bit clears (-1: never) */
    int bmsr_link_latched_low;  /* first BMSR read reports the old link failure */
    bool mdio_error;
} sim;

static int32_t sim_read( void *ctx, uint8_t addr, uint8_t reg, uint16_t *value )
{
    ( void )ctx;
    if ( sim.mdio_error )
    {
        return -1;
    }
    if ( addr != sim.addr )
    {
        *value = 0xFFFF;        /* nobody drives MDIO: pulled up */
        return 0;
    }
    if ( NET_PHY_REG_BMCR == reg && ( sim.reg[ 0 ] & 0x8000 ) && sim.reset_reads >= 0 )
    {
        if ( 0 == sim.reset_reads-- )
        {
            sim.reg[ 0 ] &= ( uint16_t )~0x8000;
        }
    }
    *value = sim.reg[ reg ];
    if ( NET_PHY_REG_BMSR == reg && sim.bmsr_link_latched_low )
    {
        sim.bmsr_link_latched_low = 0;
        *value &= ( uint16_t )~0x0004;
    }
    return 0;
}

static int32_t sim_write( void *ctx, uint8_t addr, uint8_t reg, uint16_t value )
{
    ( void )ctx;
    if ( sim.mdio_error )
    {
        return -1;
    }
    if ( addr == sim.addr )
    {
        sim.reg[ reg ] = value;
    }
    return 0;
}

static void sim_lan8720( uint8_t addr )
{
    memset( &sim, 0, sizeof( sim ) );
    sim.addr = addr;
    sim.reg[ NET_PHY_REG_ID1 ] = 0x0007;
    sim.reg[ NET_PHY_REG_ID2 ] = 0xC0F1;
    sim.reg[ NET_PHY_REG_BMSR ] = 0x7809;      /* abilities, no link yet */
    sim.reset_reads = 3;
}

static net_phy_t phy_at( uint8_t addr )
{
    net_phy_t p = { NULL, addr, sim_read, sim_write, 0 };
    return p;
}

int main( void )
{
    net_phy_t p;

    sim_lan8720( 1 );
    p = phy_at( NET_PHY_ADDR_AUTO );
    CHECK( "scan-finds-phy", 0 == net_phy_init( &p ) && 1 == p.addr && 0x0007C0F1u == p.id );
    CHECK( "advertises-10-100-half-full", 0x01E1 == sim.reg[ NET_PHY_REG_ANAR ] );
    CHECK( "autoneg-restarted", 0x1200 == ( sim.reg[ NET_PHY_REG_BMCR ] & 0x1200 ) );

    sim_lan8720( 0 );
    p = phy_at( 0 );
    CHECK( "fixed-address", 0 == net_phy_init( &p ) && 0 == p.addr );

    sim_lan8720( 5 );
    p = phy_at( 3 );
    CHECK( "wrong-fixed-address-fails", 0 != net_phy_init( &p ) );

    sim_lan8720( 31 );
    sim.addr = 40;      /* nobody on the bus */
    p = phy_at( NET_PHY_ADDR_AUTO );
    CHECK( "no-phy-fails", 0 != net_phy_init( &p ) && NET_PHY_ADDR_AUTO == p.addr );

    sim_lan8720( 2 );
    sim.reset_reads = -1;   /* reset never finishes */
    p = phy_at( 2 );
    CHECK( "stuck-reset-fails", 0 != net_phy_init( &p ) );

    sim_lan8720( 2 );
    sim.mdio_error = true;
    p = phy_at( 2 );
    CHECK( "mdio-error-fails", 0 != net_phy_init( &p ) );

    /* Link and negotiated mode. */
    sim_lan8720( 1 );
    p = phy_at( 1 );
    net_phy_init( &p );
    net_phy_mode_t mode;
    CHECK( "no-link", !net_phy_link( &p, &mode ) );

    struct { uint16_t partner; bool s100, fd; const char *name; } cases[] = {
        { 0x01E1, true,  true,  "mode-100-full" },
        { 0x00A1, true,  false, "mode-100-half" },
        { 0x0061, false, true,  "mode-10-full" },
        { 0x0021, false, false, "mode-10-half" },
    };
    for ( unsigned i = 0; i < sizeof( cases ) / sizeof( cases[ 0 ] ); i++ )
    {
        sim.reg[ NET_PHY_REG_BMSR ] = 0x782D;   /* link up, auto-negotiation complete */
        sim.reg[ NET_PHY_REG_ANLPAR ] = cases[ i ].partner;
        bool up = net_phy_link( &p, &mode );
        CHECK( cases[ i ].name, up && mode.speed_100 == cases[ i ].s100 && mode.full_duplex == cases[ i ].fd );
    }

    /* We advertise only 10 Mbit/s: the common mode must not be 100. */
    sim.reg[ NET_PHY_REG_ANAR ] = 0x0061;
    sim.reg[ NET_PHY_REG_ANLPAR ] = 0x01E1;
    CHECK( "mode-uses-common-abilities", net_phy_link( &p, &mode ) && !mode.speed_100 && mode.full_duplex );
    sim.reg[ NET_PHY_REG_ANAR ] = 0x01E1;

    sim.bmsr_link_latched_low = 1;      /* old failure latched: second read is current */
    CHECK( "latched-low-read-twice", net_phy_link( &p, &mode ) );

    sim.reg[ NET_PHY_REG_BMSR ] = 0x780D;   /* link, but auto-negotiation not complete */
    CHECK( "link-waits-for-autoneg", !net_phy_link( &p, &mode ) );

    sim.reg[ NET_PHY_REG_BMSR ] = 0x782D;
    CHECK( "mode-pointer-optional", net_phy_link( &p, NULL ) );

    printf( "RESULT %s (%d failed)\n", failures ? "FAIL" : "PASS", failures );
    return failures ? 1 : 0;
}
