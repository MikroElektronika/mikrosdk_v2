/*!
 * @file  hal_ll_pior_port.h
 * @brief Function prototype for the LOW LEVEL HAL PORTED PIOR implementation
 *        (the swappable part - see implementation_1/hal_ll_pior_port.c and
 *        the CMakeLists' pior_subimplementation variable).
 */

#ifndef _HAL_LL_PIOR_PORT_H_
#define _HAL_LL_PIOR_PORT_H_

#ifdef __cplusplus
extern "C"
{
#endif

#include "hal_ll_target.h"
#include "hal_ll_gpio_port.h"
#include "hal_ll_pior_defines.h"

/**
 * @brief  Find and apply (or no-op, per hal_ll_state) the PIOR routing for
 *         one pin. Single function, not split by direction the way PIC32
 *         splits map_input/map_output - RL78's PIOR field is the same
 *         register regardless of which way the signal flows.
 *
 * @note RL78 ONLY
 */
hal_ll_pior_err_t hal_ll_pior_port_map( hal_ll_port_name_t port_name, hal_ll_pin_name_t pin_num,
                                         hal_ll_gpio_direction_t direction,
                                         hal_ll_pior_functionality_t pior_func,
                                         hal_ll_pior_module_index_t module_num,
                                         bool hal_ll_state );

#ifdef __cplusplus
}
#endif

#endif // _HAL_LL_PIOR_PORT_H_
