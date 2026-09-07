/*!
 * @file  hal_ll_pior_port.c
 * @brief Low level HAL PORTED PIOR function definitions - the swappable
 *        implementation (implementation_1). Table search + register write
 *        live here; hal_ll_pior.c (one directory up) is the thin public
 *        entry point that calls into this.
 */

#include "hal_ll_pior_connection_defs.h"

// ---------------------------------------------- PRIVATE FUNCTION DEFINITIONS

static hal_ll_pior_err_t hal_ll_pior_check_pin_to_function( uint16_t *map_index,
                                                              hal_ll_port_name_t port_name,
                                                              hal_ll_pin_name_t pin_num,
                                                              hal_ll_gpio_direction_t direction,
                                                              hal_ll_pior_functionality_t pior_func,
                                                              hal_ll_pior_module_index_t module_num ) {
    uint16_t map_size = ( sizeof( hal_ll_pior_map ) / sizeof( hal_ll_pior_pin_map_t ) );
    uint16_t index;

    for ( index = 0; index < map_size; index++ ) {
        if ( ( hal_ll_pior_map[ index ].pin == pin_num ) &&
             ( hal_ll_pior_map[ index ].port == port_name ) &&
             ( hal_ll_pior_map[ index ].direction == direction ) &&
             ( hal_ll_pior_map[ index ].pior_func == pior_func ) &&
             ( hal_ll_pior_map[ index ].module_index == module_num ) ) {
            *map_index = index;
            return HAL_LL_PIOR_SUCCESS;
        }
    }

    return HAL_LL_PIOR_PIN_ERROR;
}

// ---------------------------------------------- PUBLIC FUNCTION DEFINITIONS

hal_ll_pior_err_t hal_ll_pior_port_map( hal_ll_port_name_t port_name, hal_ll_pin_name_t pin_num,
                                         hal_ll_gpio_direction_t direction,
                                         hal_ll_pior_functionality_t pior_func,
                                         hal_ll_pior_module_index_t module_num,
                                         bool hal_ll_state ) {
    uint16_t map_index_num = 0;

    if ( hal_ll_pior_check_pin_to_function( &map_index_num, port_name, pin_num, direction,
                                             pior_func, module_num ) != HAL_LL_PIOR_SUCCESS ) {
        return HAL_LL_PIOR_PIN_ERROR;
    }

    if ( true == hal_ll_state ) {
        if ( 0 != hal_ll_pior_map[ map_index_num ].pior_width ) {
            hal_ll_pior_set_field( hal_ll_pior_map[ map_index_num ].pior_reg,
                                    hal_ll_pior_map[ map_index_num ].pior_shift,
                                    hal_ll_pior_map[ map_index_num ].pior_width,
                                    hal_ll_pior_map[ map_index_num ].pior_value );
        }
    }
    // hal_ll_state == false: intentionally a no-op, same reasoning as before -
    // RL78 has no "unroute" bit; writing 0 into a PIOR field just routes to
    // a different pin, it doesn't disconnect anything.

    return HAL_LL_PIOR_SUCCESS;
}
