/*!
 * @file  hal_ll_pior.c
 * @brief Low level HAL PIOR function definitions - thin top-level entry
 *        point, mirrors hal_ll_pps.c's role. No lock/unlock step and no
 *        direction-based dispatch to do here (see hal_ll_pior_port_map's
 *        own doc comment for why), so this just forwards straight through.
 */

#include "hal_ll_pior_port.h"

hal_ll_pior_err_t hal_ll_pior_map( hal_ll_port_name_t port_name, hal_ll_pin_name_t pin_num,
                                    hal_ll_gpio_direction_t direction,
                                    hal_ll_pior_functionality_t pior_func,
                                    hal_ll_pior_module_index_t module_num,
                                    bool hal_ll_state ) {
    return hal_ll_pior_port_map( port_name, pin_num, direction, pior_func, module_num, hal_ll_state );
}
