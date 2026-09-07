/*!
 * @file  hal_ll_pior.h
 * @brief Function prototype for LOW LEVEL HAL PIOR implementation - the
 *        single entry point a peripheral driver (SPI/UART/I2C/TAU) calls
 *        to route one pin, mirroring hal_ll_pps_map()'s role for PIC32.
 */

#ifndef _HAL_LL_PIOR_H_
#define _HAL_LL_PIOR_H_

#ifdef __cplusplus
extern "C"
{
#endif

#include "hal_ll_gpio_port.h"
#include "hal_ll_pior_defines.h"

/**
 * @brief  Route one pin's alternate function through PIOR.
 *
 * Looks up (port_name, pin_num, pior_func, module_num) in
 * hal_ll_pior_connection_defs.h's table and, if found, writes pior_value
 * into the matching PIOR register field. Unlike PIC32's PPS (separate
 * input/output register sets), RL78 has one routing table for both
 * directions - direction is only used to disambiguate identically-named
 * candidates if that's ever needed, not to pick which register to hit.
 *
 * @param[in]  port_name    - desired port
 * @param[in]  pin_num      - desired pin
 * @param[in]  direction    - HAL_LL_GPIO_DIGITAL_INPUT / _OUTPUT
 * @param[in]  pior_func    - desired function, see hal_ll_pior_functionality_t
 * @param[in]  module_num   - channel index, see hal_ll_pior_module_index_t
 * @param[in]  hal_ll_state - true to route it, false to release it back to
 *                            plain GPIO (this is a no-op for PIOR itself -
 *                            RL78 has no "unroute" bit; it just means the
 *                            caller has stopped relying on the routing,
 *                            included for API symmetry with hal_ll_pps_map)
 *
 * @return hal_ll_pior_err_t - HAL_LL_PIOR_SUCCESS, _PIN_ERROR (no matching
 *         row), or _MODULE_ERROR
 *
 * @note RL78 ONLY
 */
hal_ll_pior_err_t hal_ll_pior_map( hal_ll_port_name_t port_name, hal_ll_pin_name_t pin_num,
                                    hal_ll_gpio_direction_t direction,
                                    hal_ll_pior_functionality_t pior_func,
                                    hal_ll_pior_module_index_t module_num,
                                    bool hal_ll_state );

#ifdef __cplusplus
}
#endif

#endif // _HAL_LL_PIOR_H_
