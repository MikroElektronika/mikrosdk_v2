/* Driver side of the STM32 register map check (see stm32_regmap.h): the driver
 * with its default addresses, never run, only its definitions are used. */
#include <stdint.h>
#include "../../middleware/net/drivers/stm32/net_driver_stm32.c"
#include "stm32_regmap.h"

#define OURS( name, ours, st ) ( uint32_t )( ours ),
#define NAME( name, ours, st ) #name,
const uint32_t regmap_ours[] = { REGMAP( OURS ) };
const char *const regmap_names[] = { REGMAP( NAME ) };
const size_t regmap_count = sizeof( regmap_ours ) / sizeof( regmap_ours[ 0 ] );

/* Symbols the driver refers to; never called here. */
void hal_ll_gpio_module_struct_init( module_struct const *module, bool state ) { ( void )module; ( void )state; }
void Delay_ms( uint32_t ms ) { ( void )ms; }
err_t digital_out_init( digital_out_t *out, pin_name_t name ) { ( void )out; ( void )name; return 0; }
err_t digital_out_high( digital_out_t *out ) { ( void )out; return 0; }
err_t digital_out_low( digital_out_t *out ) { ( void )out; return 0; }
int32_t net_phy_init( net_phy_t *phy ) { ( void )phy; return 0; }
bool net_phy_link( net_phy_t *phy, net_phy_mode_t *mode ) { ( void )phy; ( void )mode; return false; }
