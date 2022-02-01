/****************************************************************************
**
** Copyright (C) 2022 MikroElektronika d.o.o.
** Contact: https://www.mikroe.com/contact
**
** This file is part of the mikroSDK package
**
** Commercial License Usage
**
** Licensees holding valid commercial NECTO compilers AI licenses may use this
** file in accordance with the commercial license agreement provided with the
** Software or, alternatively, in accordance with the terms contained in
** a written agreement between you and The MikroElektronika Company.
** For licensing terms and conditions see
** https://www.mikroe.com/legal/software-license-agreement.
** For further information use the contact form at
** https://www.mikroe.com/contact.
**
**
** GNU Lesser General Public License Usage
**
** Alternatively, this file may be used for
** non-commercial projects under the terms of the GNU Lesser
** General Public License version 3 as published by the Free Software
** Foundation: https://www.gnu.org/licenses/lgpl-3.0.html.
**
** The above copyright notice and this permission notice shall be
** included in all copies or substantial portions of the Software.
**
** THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND,
** OF MERCHANTABILITY, EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED
** TO THE WARRANTIES FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT.
** IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM,
** DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT
** OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE
** OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
**
****************************************************************************/
/*!
 *
 * @file  hal_ll_pps_port.c
 * @brief This file contains low level HAL PPS LOW LAYER PORTED function definitions.
 */

#include "hal_ll_pps_connection_defs.h"

/**
 * @brief Checks selected pin with available functions.
 *
 * @param map_index Index of map.
 * @param hal_ll_pps_cfg Local map.
 *
 * @return hal_ll_pps_err_t Error handling
 * Returns one of pre-defined values:
 * HAL_LL_PPS_SUCCESS -- init success
 * HAL_LL_PPS_DIRECTION_ERROR -- direction non-existent
 * HAL_LL_PPS_PIN_ERROR -- pin non-existent
 * HAL_LL_PPS_MODULE_ERROR -- init failed
 *
 * @note PIC ONLY
 */
static hal_ll_pps_err_t hal_ll_pps_check_pin_to_function( uint16_t *map_index, hal_ll_pps_hw_specifics_map_t *hal_ll_pps_cfg );

// ---------------------------------------------- PUBLIC FUNCTION DEFINTIONS
hal_ll_pps_err_t hal_ll_pps_map_input( hal_ll_port_name_t port_name, hal_ll_pin_name_t pin_num, hal_ll_pps_functionality_t pps_func, hal_ll_pps_module_index_t module_num, bool hal_ll_state ) {
    hal_ll_pps_hw_specifics_map_t hal_ll_pps_cfg;
    hal_ll_pin_name_t map_index_num = 0;

    hal_ll_pps_cfg.pin_num = pin_num;
    hal_ll_pps_cfg.port_num = port_name;
    hal_ll_pps_cfg.pin_direction = HAL_LL_GPIO_DIGITAL_INPUT;
    hal_ll_pps_cfg.pps_function = pps_func;
    hal_ll_pps_cfg.pps_module_num = module_num;

    if ( hal_ll_pps_check_pin_to_function( &map_index_num, &hal_ll_pps_cfg ) != HAL_LL_PPS_SUCCESS ) {
        return HAL_LL_PPS_PIN_ERROR;
    }

    switch ( hal_ll_state )
    {
        case true:
            write_reg_ptr(hal_ll_pps_input_map[ map_index_num ].pps_reg_addr, hal_ll_pps_input_map[ map_index_num ].pps_reg_value);
            break;

        case false:
            clear_reg_ptr(hal_ll_pps_input_map[ map_index_num ].pps_reg_addr, hal_ll_pps_input_map[ map_index_num ].pps_reg_value);
            break;
    }

    return HAL_LL_PPS_SUCCESS;
}

hal_ll_pps_err_t hal_ll_pps_map_output( hal_ll_port_name_t port_name, hal_ll_pin_name_t pin_num, hal_ll_pps_functionality_t pps_func, hal_ll_pps_module_index_t module_num, bool hal_ll_state ) {
    hal_ll_pps_hw_specifics_map_t hal_ll_pps_cfg;
    uint16_t map_index_num = 0;

    hal_ll_pps_cfg.pin_num = pin_num;
    hal_ll_pps_cfg.port_num = port_name;
    hal_ll_pps_cfg.pin_direction = HAL_LL_GPIO_DIGITAL_OUTPUT;
    hal_ll_pps_cfg.pps_function = pps_func;
    hal_ll_pps_cfg.pps_module_num = module_num;

    if ( hal_ll_pps_check_pin_to_function( &map_index_num, &hal_ll_pps_cfg ) != HAL_LL_PPS_SUCCESS ) {
        return HAL_LL_PPS_PIN_ERROR;
    }

    switch ( hal_ll_state )
    {
        case true:
            write_reg_ptr(hal_ll_pps_output_map[ map_index_num ].pps_reg_addr, hal_ll_pps_output_map[ map_index_num ].pps_reg_value);
            break;

        case false:
            clear_reg_ptr(hal_ll_pps_output_map[ map_index_num ].pps_reg_addr, hal_ll_pps_output_map[ map_index_num ].pps_reg_value);
            break;
    }

    return HAL_LL_PPS_SUCCESS;
}

// ---------------------------------------------- PRIVATE FUNCTION DEFINITONS
static hal_ll_pps_err_t hal_ll_pps_check_pin_to_function( uint16_t *map_index, hal_ll_pps_hw_specifics_map_t *hal_ll_pps_cfg ) {
    uint16_t pps_map_size;
    uint16_t hal_ll_pps_index;
    hal_ll_pps_pin_map_t map_index_ll;

    switch ( hal_ll_pps_cfg->pin_direction )
    {
        case HAL_LL_GPIO_DIGITAL_INPUT:
            map_index_ll = *hal_ll_pps_input_map;
            pps_map_size = (sizeof(hal_ll_pps_input_map) / sizeof(hal_ll_pps_pin_map_t));
            break;

        case HAL_LL_GPIO_DIGITAL_OUTPUT:
            map_index_ll = *hal_ll_pps_output_map;
            pps_map_size  = (sizeof(hal_ll_pps_output_map)  / sizeof(hal_ll_pps_pin_map_t));
            break;

        default:
            return HAL_LL_PPS_DIRECTION_ERROR;
    }

    for ( hal_ll_pps_index = 0; hal_ll_pps_index < pps_map_size; hal_ll_pps_index ) {
        if ( map_index_ll.pin_num == hal_ll_pps_cfg->pin_num ) {
            if ( map_index_ll.port_num == hal_ll_pps_cfg->port_num ) {
                if ( map_index_ll.pin_direction == hal_ll_pps_cfg->pin_direction ) {
                    if ( map_index_ll.pps_function == hal_ll_pps_cfg->pps_function ) {
                        if ( map_index_ll.pps_module_num == hal_ll_pps_cfg->pps_module_num ) {
                            *map_index = hal_ll_pps_index;
                            return HAL_LL_PPS_SUCCESS;
                        }
                    }
                }
            }
        }

        // Increment pointer to next structure element
        if( hal_ll_pps_cfg->pin_direction == HAL_LL_GPIO_DIGITAL_INPUT ) {
            map_index_ll = hal_ll_pps_input_map[ ++hal_ll_pps_index ];
        } else {
            map_index_ll = hal_ll_pps_output_map[ ++hal_ll_pps_index ];
        }
    }

    // If it gets to here, check pin maps for error
    return HAL_LL_PPS_MODULE_ERROR;
}
// ------------------------------------------------------------------------- END
