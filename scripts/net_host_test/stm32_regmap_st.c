/* ST side of the STM32 register map check (see stm32_regmap.h): ST's CMSIS
 * device header, given as ST_DEVICE_HEADER by CMakeLists.txt. */
#include <stdint.h>
#include ST_DEVICE_HEADER
#include "stm32_regmap.h"

#define ST( name, ours, st ) ( uint32_t )( st ),
const uint32_t regmap_st[] = { REGMAP( ST ) };
