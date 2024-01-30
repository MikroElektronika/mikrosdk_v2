/****************************************************************************
**
** Copyright (C) 2024 MikroElektronika d.o.o.
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
 * @file  hal_can.c
 * @brief This file contains all the functions prototypes for the CAN library.
 */

#include "hal_can.h"
#include "hal_ll_can.h"

static handle_t *hal_owner = NULL;

static volatile hal_can_handle_register_t hal_module_state[ CAN_MODULE_COUNT ];

static const uint8_t module_state_count = sizeof( hal_module_state ) / ( sizeof( hal_can_handle_register_t ) );

static handle_t hal_is_handle_null( handle_t *hal_module_handle )
{
    uint8_t hal_module_state_count = module_state_count;

    while( hal_module_state_count-- )
    {
        if ( *hal_module_handle == ( handle_t )&hal_module_state[ hal_module_state_count ].hal_can_handle )
        {
            return ( handle_t )&hal_module_state[ hal_module_state_count ].hal_can_handle;
        }
    }

    return ACQUIRE_SUCCESS;
}

void hal_can_configure_default( hal_can_config_t *config )
{
    if ( config )
    {
        config->tx_pin = (hal_pin_name_t) 0xFFFFFFFF;
        config->rx_pin = (hal_pin_name_t) 0xFFFFFFFF;

        config->mode = HAL_CAN_MODE_NORMAL;
        config->frequency = 500000;
    }
}

void hal_can_filter_configure_default( hal_can_filter_config_t *filter_config )
{
    if ( filter_config )
    {
        filter_config->can_filter_id_high = 0x0000;
        filter_config->can_filter_id_low = 0x0000;
        filter_config->can_filter_mask_id_high = 0x0000;
        filter_config->can_filter_mask_id_low = 0x0000;
        filter_config->can_filter_mode = HAL_CAN_FILTER_MODE_IDMASK;
        filter_config->can_filter_scale = HAL_CAN_FILTER_SCALE_32BIT;
        filter_config->can_filter_enable = HAL_CAN_FILTER_DISABLE;
        filter_config->can_filter_fifo = HAL_CAN_FILTER_FIFO0;
        filter_config->can_filter_bank = 0;
    }
}

err_t hal_can_open( handle_t *handle, bool hal_obj_open_state )
{
    uint8_t hal_module_id;
    err_t hal_status = sizeof( hal_can_config_t );
    hal_can_t *hal_obj = ( hal_can_t * ) handle;
    uint8_t hal_module_state_count = module_state_count;

    if ( !handle )
    {
        return ACQUIRE_FAIL;
    }

    if ( hal_obj_open_state == true )
    {
        if( hal_is_handle_null( handle ) != ACQUIRE_SUCCESS )
        {
            return ACQUIRE_FAIL;
        }
    }

    if( hal_owner != handle )
    {
        while ( hal_module_state_count-- ) {
            if ( hal_module_state[ hal_module_state_count ].drv_can_handle == handle ) {
                hal_owner = handle;
                return ACQUIRE_SUCCESS;
            }
        }

        hal_status = hal_ll_can_register_handle( hal_obj->config.tx_pin, hal_obj->config.rx_pin,
                                                        &hal_module_state, &hal_module_id );

        if( hal_status == ACQUIRE_SUCCESS )
        {
            hal_module_state[ hal_module_id ].drv_can_handle = handle;
            *handle = ( handle_t )&hal_module_state[ hal_module_id ].hal_can_handle;
            hal_owner = handle;
            return ACQUIRE_INIT;
        } else {
            *handle = 0;
            return ACQUIRE_FAIL;
        }
    } else {
        return ACQUIRE_SUCCESS;
    }
}

err_t hal_can_init( handle_t *handle, hal_can_config_t *config, hal_can_filter_config_t *filter_config ) {
    hal_can_handle_register_t *hal_handle = ( hal_can_handle_register_t * )hal_is_handle_null( handle );
    err_t hal_status;

    if ( !hal_handle )
        return HAL_CAN_ERROR;

    hal_handle->init_state = false;

    hal_status = hal_ll_can_init( &hal_handle, config, filter_config );

    if ( HAL_CAN_SUCCESS != hal_status )
    {
        return HAL_CAN_ERROR;
    } else {
        hal_handle->init_state = true;
        return HAL_CAN_SUCCESS;
    }
}

err_t hal_can_set_filter( handle_t *handle, hal_can_config_t *config, hal_can_filter_config_t *filter_config ) {
    hal_can_handle_register_t *hal_handle = ( hal_can_handle_register_t * )hal_is_handle_null( handle );
    err_t hal_status;

    if ( !hal_handle )
        return HAL_CAN_ERROR;

    hal_handle->init_state = false;

    hal_status = hal_ll_can_set_filter( &hal_handle, config, filter_config );

    if ( HAL_CAN_SUCCESS != hal_status )
    {
        return HAL_CAN_ERROR;
    } else {
        hal_handle->init_state = true;
        return HAL_CAN_SUCCESS;
    }
}

err_t hal_can_set_frequency( handle_t *handle, hal_can_config_t *config, hal_can_filter_config_t *filter_config ) {
    hal_can_handle_register_t *hal_handle = ( hal_can_handle_register_t * )hal_is_handle_null( handle );
    err_t hal_status;

    if ( !hal_handle )
        return HAL_CAN_ERROR;

    hal_handle->init_state = false;

    hal_status = hal_ll_can_set_frequency( &hal_handle, config, filter_config );

    if ( HAL_CAN_SUCCESS != hal_status )
    {
        return HAL_CAN_ERROR;
    } else {
        hal_handle->init_state = true;
        return HAL_CAN_SUCCESS;
    }
}

err_t hal_can_get_frequency( handle_t *handle ) {
    hal_can_handle_register_t *hal_handle = ( hal_can_handle_register_t * )hal_is_handle_null( handle );

    if ( !hal_handle )
        return HAL_CAN_ERROR;

    return hal_ll_can_get_frequency( &hal_handle );
}

err_t hal_can_set_mode( handle_t *handle, hal_can_config_t *config, hal_can_filter_config_t *filter_config ) {
    hal_can_handle_register_t *hal_handle = ( hal_can_handle_register_t * )hal_is_handle_null( handle );
    err_t hal_status;

    if ( !hal_handle )
        return HAL_CAN_ERROR;

    hal_handle->init_state = false;

    hal_status = hal_ll_can_set_mode( &hal_handle, config, filter_config );

    if ( HAL_CAN_SUCCESS != hal_status )
    {
        return HAL_CAN_ERROR;
    } else {
        hal_handle->init_state = true;
        return HAL_CAN_SUCCESS;
    }
}

err_t hal_can_get_mode( handle_t *handle ) {
    hal_can_handle_register_t *hal_handle = ( hal_can_handle_register_t * )hal_is_handle_null( handle );

    if ( !hal_handle )
        return HAL_CAN_ERROR;

    return hal_ll_can_get_mode( &hal_handle );
}

err_t hal_can_transmit( handle_t *handle, hal_can_transmit_message_struct *transmit_message ) {
    hal_can_handle_register_t *hal_handle = ( hal_can_handle_register_t * )hal_is_handle_null( handle );
    err_t hal_status = HAL_CAN_SUCCESS;

    if ( !handle )
    {
        return HAL_CAN_ERROR;
    }

    if ( !transmit_message )
    {
        return HAL_CAN_ERROR;
    }

    if( !hal_handle->init_state ) {
        hal_status = hal_can_init( handle,
                                   &(*(hal_can_t *)hal_handle->drv_can_handle).config,
                                   &(*(hal_can_t *)hal_handle->drv_can_handle).filter_config );
    }

    if( HAL_CAN_SUCCESS != hal_status ) {
        return HAL_CAN_ERROR;
    }

    return hal_ll_can_transmit( &hal_handle, (hal_ll_can_transmit_message_struct *)transmit_message );
}

void hal_can_transmission_stop( handle_t *handle ) {
    hal_can_handle_register_t *hal_handle = ( hal_can_handle_register_t * )hal_is_handle_null( handle );

    if ( handle && hal_handle->init_state ) {
        hal_ll_can_transmission_stop( &hal_handle );
    }
}

err_t hal_can_receive( handle_t *handle, hal_can_receive_message_struct *receive_message ) {
    hal_can_handle_register_t *hal_handle = ( hal_can_handle_register_t * )hal_is_handle_null( handle );
    err_t hal_status = HAL_CAN_SUCCESS;

    if ( !handle )
    {
        return HAL_CAN_ERROR;
    }

    if ( !receive_message )
    {
        return HAL_CAN_ERROR;
    }

    if( !hal_handle->init_state ) {
        hal_status = hal_can_init( handle,
                                   &(*(hal_can_t *)hal_handle->drv_can_handle).config,
                                   &(*(hal_can_t *)hal_handle->drv_can_handle).filter_config );
    }

    if( HAL_CAN_SUCCESS != hal_status ) {
        return HAL_CAN_ERROR;
    }

    hal_status = hal_ll_can_receive( &hal_handle, (hal_ll_can_receive_message_struct *)receive_message );

    if( hal_status != HAL_CAN_SUCCESS )
    {
        return HAL_CAN_ERROR;
    } else {
        return hal_status;
    }

}

err_t hal_can_close( handle_t *handle )
{
    hal_can_handle_register_t *hal_handle = ( hal_can_handle_register_t * )hal_is_handle_null( handle );

    if( hal_handle )
    {
        if ( hal_handle->hal_can_handle )
        {
            hal_can_t *hal_obj = ( hal_can_t * )handle;

            hal_ll_can_close( &hal_handle );

            memset( &hal_obj->config, 0xFF, sizeof( hal_can_config_t ) );

            hal_handle->hal_can_handle = NULL;
            hal_handle->drv_can_handle = NULL;

            hal_handle->init_state = false;

            hal_owner = NULL;

            return HAL_CAN_SUCCESS;
        }
    }

    return HAL_CAN_ERROR;
}

// ------------------------------------------------------------------------- END
