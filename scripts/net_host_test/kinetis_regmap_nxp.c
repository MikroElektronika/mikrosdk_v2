/* NXP side of the Kinetis register map check (see kinetis_regmap.h): NXP's
 * device header, given as NXP_DEVICE_HEADER by CMakeLists.txt. */
#include <stdint.h>
#include NXP_DEVICE_HEADER
#include "kinetis_regmap.h"

#define NXP( name, ours, nxp ) ( uint32_t )( nxp ),
const uint32_t regmap_st[] = { REGMAP( NXP ) };    /* same symbol as the STM32 check: shared main */
