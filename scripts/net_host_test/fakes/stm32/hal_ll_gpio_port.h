/*
 * Host test only: the parts of mikroSDK's STM32 hal_ll_gpio_port.h the STM32
 * Ethernet driver uses (same layout and macros). hal_ll_gpio_module_struct_init()
 * is provided by the test, which records the module it gets.
 */
#ifndef FAKE_HAL_LL_GPIO_PORT_H
#define FAKE_HAL_LL_GPIO_PORT_H

#include <stdbool.h>
#include <stdint.h>
#include "hal_ll_gpio_constants.h"

#define GPIO_MODULE_STRUCT_END -1
#define GPIO_AF_OFFSET 8
#define VALUE(pin, func) (pin | (func << GPIO_AF_OFFSET))

typedef struct
{
  uint32_t pins[13];
  uint32_t configs[13];
  uint32_t gpio_remap;
} module_struct;

void hal_ll_gpio_module_struct_init( module_struct const *module, bool state );

#endif
