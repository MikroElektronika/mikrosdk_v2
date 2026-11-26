/* TI side of the TM4C129 register map check (see tm4c_regmap.h). */
#include <stdint.h>
#include <stdbool.h>
#include "inc/hw_memmap.h"
#include "inc/hw_emac.h"
#include "inc/hw_sysctl.h"
#include "inc/hw_gpio.h"
#include "driverlib/pin_map.h"
#include "tm4c_regmap.h"

#define TI( name, ours, ti ) ( uint32_t )( ti ),
const uint32_t regmap_st[] = { REGMAP( TI ) };    /* same symbol as the STM32 check: shared main */
