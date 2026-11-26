/* Driver side of the TM4C129 register map check (see tm4c_regmap.h). */
#include <stdint.h>
#include "../../middleware/net/drivers/tm4c/net_driver_tm4c.c"
#include "tm4c_regmap.h"

#define OURS( name, ours, ti ) ( uint32_t )( ours ),
#define NAME( name, ours, ti ) #name,
const uint32_t regmap_ours[] = { REGMAP( OURS ) };
const char *const regmap_names[] = { REGMAP( NAME ) };
const size_t regmap_count = sizeof( regmap_ours ) / sizeof( regmap_ours[ 0 ] );

int32_t net_phy_init( net_phy_t *phy ) { ( void )phy; return 0; }
bool net_phy_link( net_phy_t *phy, net_phy_mode_t *mode ) { ( void )phy; ( void )mode; return false; }
