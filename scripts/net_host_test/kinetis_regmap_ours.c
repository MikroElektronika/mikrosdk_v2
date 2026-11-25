/* Driver side of the Kinetis register map check (see kinetis_regmap.h): the
 * driver with its default addresses, never run, only its definitions are used. */
#include <stdint.h>
#include "../../middleware/net/drivers/kinetis/net_driver_kinetis.c"
#include "kinetis_regmap.h"

#define OURS( name, ours, nxp ) ( uint32_t )( ours ),
#define NAME( name, ours, nxp ) #name,
const uint32_t regmap_ours[] = { REGMAP( OURS ) };
const char *const regmap_names[] = { REGMAP( NAME ) };
const size_t regmap_count = sizeof( regmap_ours ) / sizeof( regmap_ours[ 0 ] );

/* Symbols the driver refers to; never called here. */
void Delay_ms( uint32_t ms ) { ( void )ms; }
err_t digital_out_init( digital_out_t *out, pin_name_t name ) { ( void )out; ( void )name; return 0; }
err_t digital_out_high( digital_out_t *out ) { ( void )out; return 0; }
err_t digital_out_low( digital_out_t *out ) { ( void )out; return 0; }
int32_t net_phy_init( net_phy_t *phy ) { ( void )phy; return 0; }
bool net_phy_link( net_phy_t *phy, net_phy_mode_t *mode ) { ( void )phy; ( void )mode; return false; }
