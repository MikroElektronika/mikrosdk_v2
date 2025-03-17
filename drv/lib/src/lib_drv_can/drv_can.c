/****************************************************************************
**
** Copyright (C) ${COPYRIGHT_YEAR} MikroElektronika d.o.o.
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
** EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES
** OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT.
** IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM,
** DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT
** OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE
** OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
**
****************************************************************************/
/*!
 * @file  drv_can.c
 * @brief CAN driver implementation.
 */

#include "drv_can.h"

static can_t *_owner = NULL;

#if !DRV_TO_HAL
extern hal_can_handle_register_t DRV_TO_HAL_PREFIXED(can, hal_module_state)[ CAN_MODULE_COUNT ];

extern const uint8_t DRV_TO_HAL_PREFIXED(can, module_state_count);

static handle_t hal_is_handle_null( handle_t *hal_module_handle )
{
    uint8_t hal_module_state_count = DRV_TO_HAL_PREFIXED(can, module_state_count);

    #ifdef __XC8__
    uint32_t tmp_addr;
    #endif

    while( hal_module_state_count-- )
    {
        #ifdef __XC8__
        tmp_addr = ( handle_t )&DRV_TO_HAL_PREFIXED(can, hal_module_state)[ hal_module_state_count ].hal_can_handle;
        if ( *hal_module_handle == tmp_addr )
        {
            return tmp_addr;
        }
        #else
        if ( *hal_module_handle == ( handle_t )&DRV_TO_HAL_PREFIXED(can, hal_module_state)[ hal_module_state_count ].hal_can_handle )
        {
            return ( handle_t )&DRV_TO_HAL_PREFIXED(can, hal_module_state)[ hal_module_state_count ].hal_can_handle;
        }
        #endif
    }

    return ACQUIRE_SUCCESS;
}
#endif

static err_t _acquire( can_t *obj, bool obj_open_state )
{
    err_t status = ACQUIRE_SUCCESS;

    if ( obj_open_state == true && _owner == obj )
    {
        return ACQUIRE_FAIL;
    }

    if ( _owner != obj )
    {
        status = hal_can_open( &obj->handle, obj_open_state );

        if ( status != ACQUIRE_FAIL )
            _owner = obj;
    }

    return status;
}

void can_configure_default( can_config_t *config )
{
    if ( config )
    {
        config->tx_pin = (pin_name_t) 0xFFFFFFFF;
        config->rx_pin = (pin_name_t) 0xFFFFFFFF;

        config->mode = CAN_MODE_NORMAL;
        config->frequency = 500000;
    }
}

void can_filter_configure_default( can_filter_config_t *filter_config )
{
    if ( filter_config )
    {
        filter_config->can_filter_id_high = 0x0000;
        filter_config->can_filter_id_low = 0x0000;
        filter_config->can_filter_mask_id_high = 0x0000;
        filter_config->can_filter_mask_id_low = 0x0000;
        filter_config->can_filter_mode = CAN_FILTER_MODE_IDMASK;
        filter_config->can_filter_scale = CAN_FILTER_SCALE_16BIT;
        filter_config->can_filter_enable = CAN_FILTER_DISABLE;
        filter_config->can_filter_fifo = CAN_FILTER_FIFO0;
        filter_config->can_filter_bank = 0;
    }
}

err_t can_open( can_t *obj, can_config_t *config )
{
    can_config_t *p_config = &obj->config;
    memcpy( p_config, config, sizeof( can_config_t ) );

    return _acquire( obj, true );
}

err_t can_init( can_t *obj ) {
    if ( _acquire( obj, false ) != ACQUIRE_FAIL )
    {
        #if DRV_TO_HAL
        return hal_can_init( &obj->handle, (hal_can_config_t *) &obj->config, (hal_can_filter_config_t *) &obj->filter_config );
        #else
        hal_can_handle_register_t *hal_handle = ( hal_can_handle_register_t * )hal_is_handle_null( (handle_t *)&obj->handle );
        err_t hal_status;

        if ( !hal_handle )
            return HAL_CAN_ERROR;

        hal_handle->init_state = false;

        hal_status = hal_ll_can_init( (handle_t *)&hal_handle, (hal_ll_can_config_t *)&obj->config, (hal_ll_can_filter_config_t *)&obj->filter_config );

        if ( HAL_CAN_SUCCESS != hal_status )
        {
            return HAL_CAN_ERROR;
        } else {
            hal_handle->init_state = true;
            return HAL_CAN_SUCCESS;
        }
        #endif
    } else {
        return CAN_ERROR;
    }
}

err_t can_set_filter( can_t *obj, can_filter_config_t *filter_config ) {
    can_filter_config_t *p_config = &obj->filter_config;
    memcpy( p_config, filter_config, sizeof( can_filter_config_t ) );

    if ( _acquire( obj, false ) != ACQUIRE_FAIL )
    {
        #if DRV_TO_HAL
        return hal_can_set_filter( &obj->handle, (hal_can_config_t *) &obj->config, (hal_can_filter_config_t *) &obj->filter_config );
        #else
        hal_can_handle_register_t *hal_handle = ( hal_can_handle_register_t * )hal_is_handle_null( (handle_t *)&obj->handle );
        err_t hal_status;

        if ( !hal_handle )
            return HAL_CAN_ERROR;

        hal_handle->init_state = false;

        hal_status = hal_ll_can_set_filter( (handle_t *)&hal_handle, (hal_ll_can_config_t *)&obj->config, (hal_ll_can_filter_config_t *)&obj->filter_config );

        if ( HAL_CAN_SUCCESS != hal_status )
        {
            return HAL_CAN_ERROR;
        } else {
            hal_handle->init_state = true;
            return HAL_CAN_SUCCESS;
        }
        #endif
    } else {
        return CAN_ERROR;
    }
}

err_t can_set_frequency( can_t *obj, uint32_t frequency ) {
    if ( _acquire( obj, false ) != ACQUIRE_FAIL )
    {
        uint32_t original_value = obj->config.frequency;
        obj->config.frequency = frequency;

        #if DRV_TO_HAL
        err_t result = hal_can_set_frequency( &obj->handle, &obj->config, &obj->filter_config );
        #else
        hal_can_handle_register_t *hal_handle = ( hal_can_handle_register_t * )hal_is_handle_null( (handle_t *)&obj->handle );
        err_t result;

        if ( !hal_handle )
            return HAL_CAN_ERROR;

        hal_handle->init_state = false;

        result = hal_ll_can_set_frequency( (handle_t *)&hal_handle, (hal_ll_can_config_t *)&obj->config, (hal_ll_can_filter_config_t *)&obj->filter_config );

        if ( HAL_CAN_SUCCESS == result )
        {
            hal_handle->init_state = true;
        }
        #endif
        if( HAL_CAN_ERROR == result ) {
            obj->config.frequency = original_value;
        }

        return result;
    } else {
        return CAN_ERROR;
    }
}

err_t can_get_frequency( can_t *obj ) {
    if ( _acquire( obj, false ) != ACQUIRE_FAIL )
    {
        #if DRV_TO_HAL
        return hal_can_get_frequency( &obj->handle );
        #else
        hal_can_handle_register_t *hal_handle = ( hal_can_handle_register_t * )hal_is_handle_null( (handle_t *)&obj->handle );

        if ( !hal_handle )
            return HAL_CAN_ERROR;

        return hal_ll_can_get_frequency( (handle_t *)&hal_handle );
        #endif
    } else {
        return CAN_ERROR;
    }
}

err_t can_get_mode( can_t *obj ) {
    if ( _acquire( obj, false ) != ACQUIRE_FAIL )
    {
        #if DRV_TO_HAL
        return hal_can_get_mode( &obj->handle );
        #else
        hal_can_handle_register_t *hal_handle = ( hal_can_handle_register_t * )hal_is_handle_null( (handle_t *)&obj->handle );

        if ( !hal_handle )
            return HAL_CAN_ERROR;

        return hal_ll_can_get_mode( (handle_t *)&hal_handle );
        #endif
    } else {
        return CAN_ERROR;
    }
}

err_t can_set_mode( can_t *obj, can_mode_t mode ) {
    if ( _acquire( obj, false ) != ACQUIRE_FAIL )
    {
        can_mode_t original_value = obj->config.mode;
        obj->config.mode = mode;

        #if DRV_TO_HAL
        err_t result = hal_can_set_mode( &obj->handle, &obj->config, &obj->filter_config );
        #else
        hal_can_handle_register_t *hal_handle = ( hal_can_handle_register_t * )hal_is_handle_null( (handle_t *)&obj->handle );
        err_t result;

        if ( !hal_handle )
            return HAL_CAN_ERROR;

        hal_handle->init_state = false;

        result = hal_ll_can_set_mode( (handle_t *)&hal_handle, (hal_ll_can_config_t *)&obj->config, (hal_ll_can_filter_config_t *)&obj->filter_config );

        if ( HAL_CAN_SUCCESS == result )
        {
            hal_handle->init_state = true;
        }
        #endif

        if( HAL_CAN_ERROR == result ) {
            obj->config.mode = original_value;
        }

        return result;
    } else {
        return CAN_ERROR;
    }
}

err_t can_transmit( can_t *obj, can_transmit_message_struct *transmit_message ) {
    if ( _acquire( obj, false ) != ACQUIRE_FAIL )
    {
        #if DRV_TO_HAL
        return hal_can_transmit( &obj->handle, (hal_can_transmit_message_struct *)transmit_message );
        #else
        hal_can_handle_register_t *hal_handle = ( hal_can_handle_register_t * )hal_is_handle_null( (handle_t *)&obj->handle );
        err_t hal_status = HAL_CAN_SUCCESS;

        if ( !obj )
        {
            return HAL_CAN_ERROR;
        }

        if ( !transmit_message )
        {
            return HAL_CAN_ERROR;
        }

        if( !hal_handle->init_state ) {
            hal_status = hal_can_init( (handle_t *)obj,
                                       &(*(hal_can_t *)hal_handle->drv_can_handle).config,
                                       &(*(hal_can_t *)hal_handle->drv_can_handle).filter_config
                                     );
        }

        if( HAL_CAN_SUCCESS != hal_status ) {
            return HAL_CAN_ERROR;
        }

        return hal_ll_can_transmit( (handle_t *)&hal_handle, (hal_ll_can_transmit_message_struct *)transmit_message );
        #endif
    } else {
        return CAN_ERROR;
    }
}

void can_transmission_stop( can_t *obj ) {
    if ( _acquire( obj, false ) != ACQUIRE_FAIL ) {
        #if DRV_TO_HAL
        hal_can_transmission_stop( &obj->handle );
        #else
        hal_can_handle_register_t *hal_handle = ( hal_can_handle_register_t * )hal_is_handle_null( (handle_t *)&obj->handle );

        if ( obj && hal_handle->init_state ) {
            hal_ll_can_transmission_stop( (handle_t *)&hal_handle );
        }
        #endif
    }
}

err_t can_receive( can_t *obj, can_receive_message_struct *receive_message ) {
    if ( _acquire( obj, false ) != ACQUIRE_FAIL )
    {
        #if DRV_TO_HAL
        return hal_can_receive( &obj->handle, (hal_can_receive_message_struct *)receive_message );
        #else
        hal_can_handle_register_t *hal_handle = ( hal_can_handle_register_t * )hal_is_handle_null( (handle_t *)&obj->handle );
        err_t hal_status = HAL_CAN_SUCCESS;

        if ( !obj )
        {
            return HAL_CAN_ERROR;
        }

        if ( !receive_message )
        {
            return HAL_CAN_ERROR;
        }

        if( !hal_handle->init_state ) {
            hal_status = hal_can_init( (handle_t *)obj,
                                       &(*(hal_can_t *)hal_handle->drv_can_handle).config,
                                       &(*(hal_can_t *)hal_handle->drv_can_handle).filter_config
                                     );
        }

        if( HAL_CAN_SUCCESS != hal_status ) {
            return HAL_CAN_ERROR;
        }

        hal_status = hal_ll_can_receive( (handle_t *)&hal_handle, (hal_ll_can_receive_message_struct *)receive_message );

        if( hal_status != HAL_CAN_SUCCESS )
        {
            return HAL_CAN_ERROR;
        } else {
            return hal_status;
        }
        #endif
    } else {
        return CAN_ERROR;
    }
}

err_t can_close( can_t *obj )
{
    if ( CAN_SUCCESS == hal_can_close( &obj->handle ) )
    {
        obj->handle = NULL;
        _owner = NULL;
        return CAN_SUCCESS;
    } else {
        return CAN_ERROR;
    }
}

// ------------------------------------------------------------------------- END
