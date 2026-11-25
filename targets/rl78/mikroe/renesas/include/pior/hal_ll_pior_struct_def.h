/*!
 * @file  hal_ll_pior_struct_def.h
 * @brief Struct definition for the per-chip PIOR routing table. Shared -
 *        only hal_ll_pior_connection_defs.h (one array of these) is per-MCU.
 */

#ifndef _HAL_LL_PIOR_STRUCT_DEF_H_
#define _HAL_LL_PIOR_STRUCT_DEF_H_

#ifdef __cplusplus
extern "C"{
#endif

#include "hal_ll_gpio_port.h"
#include "hal_ll_pior_defines.h"

/*!< @brief One row per (pin, function) combination.
 * direction mirrors the manual's own Input/Output/Input-output column -
 * it's informational here (hal_ll_gpio_config() already does the real
 * PM/PDIDIS work), not a register to write.
 * pior_mask selects the PIORn bits routing the function and pior_value
 * holds those bits in position. pior_mask == 0 means "not redirectable,
 * skip the PIOR write entirely". */
typedef struct
{
    hal_ll_pin_name_t            pin;
    hal_ll_port_name_t           port;
    hal_ll_gpio_direction_t      direction;
    hal_ll_pior_functionality_t  pior_func;
    hal_ll_pior_module_index_t   module_index;
    uint8_t                      pior_reg;
    uint8_t                      pior_mask;
    uint8_t                      pior_value;
    bool                         open_drain;   // true for every SDA row
} hal_ll_pior_pin_map_t;

#ifdef __cplusplus
}
#endif

#endif // _HAL_LL_PIOR_STRUCT_DEF_H_
