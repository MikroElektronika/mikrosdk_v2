/*
 * Host test only: the PIC32MZ Ethernet registers used by net_driver_pic32.c,
 * as plain variables. SET/CLR registers keep the last value written; the MDIO
 * read data register answers from a simulated PHY (fake_phy_reg[], address
 * fake_phy_addr). See test_pic32.c.
 */
#ifndef FAKE_PIC32MZ_MCU_H
#define FAKE_PIC32MZ_MCU_H

#include <stdint.h>

#define FAKE_REGS( X ) \
    X( ETHCON1 ) X( ETHCON1SET ) X( ETHCON1CLR ) X( ETHCON2 ) X( ETHSTAT ) X( ETHIEN ) \
    X( ETHIRQ ) X( ETHIRQCLR ) X( ETHTXST ) X( ETHRXST ) X( ETHRXFC ) \
    X( EMAC1CFG1 ) X( EMAC1CFG2 ) X( EMAC1IPGT ) X( EMAC1IPGR ) X( EMAC1MAXF ) \
    X( EMAC1SUPPSET ) X( EMAC1SUPPCLR ) X( EMAC1MCFG ) X( EMAC1MCMD ) X( EMAC1MADR ) \
    X( EMAC1MWTD ) X( EMAC1MIND ) X( EMAC1SA0 ) X( EMAC1SA1 ) X( EMAC1SA2 )

#define FAKE_DECLARE( name ) extern volatile uint32_t name;
FAKE_REGS( FAKE_DECLARE )

extern uint8_t fake_phy_addr;
extern uint16_t fake_phy_reg[ 32 ];
uint32_t fake_mdio_read_data( void );
#define EMAC1MRDD ( fake_mdio_read_data() )

#endif
