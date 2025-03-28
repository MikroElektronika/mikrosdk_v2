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
 * @file  drv_analog_in.c
 * @brief Analog input driver implementation.
 */

#include "drv_analog_in.h"

static analog_in_t *_owner = NULL;

#if !DRV_TO_HAL
extern hal_adc_handle_register_t DRV_TO_HAL_PREFIXED(adc, hal_module_state)[ADC_MODULE_COUNT];

extern const uint8_t DRV_TO_HAL_PREFIXED(adc, module_state_count);

static handle_t hal_is_handle_null( handle_t *hal_module_handle )
{
    uint8_t hal_module_state_count = DRV_TO_HAL_PREFIXED(adc, module_state_count);

    #ifdef __XC8__
    uint32_t tmp_addr;
    #endif

    while ( hal_module_state_count-- )
    {
        #ifdef __XC8__
        tmp_addr = ( handle_t )&DRV_TO_HAL_PREFIXED(adc, hal_module_state)[ hal_module_state_count ].hal_adc_handle;
        if ( *hal_module_handle == tmp_addr )
        {
            return tmp_addr;
        }
        #else
        if ( *hal_module_handle == ( handle_t )&DRV_TO_HAL_PREFIXED(adc, hal_module_state)[ hal_module_state_count ].hal_adc_handle )
        {
            return ( handle_t )&DRV_TO_HAL_PREFIXED(adc, hal_module_state)[ hal_module_state_count ].hal_adc_handle;
        }
        #endif
    }
    return ACQUIRE_SUCCESS;
}
#endif

static err_t _acquire( analog_in_t *obj, bool obj_open_state )
{
    err_t status = ACQUIRE_SUCCESS;

    if ( obj_open_state == true && _owner == obj )
    {
        return ACQUIRE_FAIL;
    }
    if ( _owner != obj )
    {
        status = hal_adc_open( &obj->handle, obj_open_state );

        if ( status != ACQUIRE_FAIL )
            _owner = obj;
    }

    return status;
}

void analog_in_configure_default( analog_in_config_t *config )
{
    if ( config )
    {
        config->input_pin = (pin_name_t)0xFFFFFFFF;
        config->resolution = ANALOG_IN_RESOLUTION_DEFAULT;
        config->vref_input = ANALOG_IN_VREF_EXTERNAL;
        config->vref_value = -1.0;
    }
}

err_t analog_in_open( analog_in_t *obj, analog_in_config_t *config )
{
    analog_in_config_t *p_config = &obj->config;
    memcpy( p_config, config, sizeof( analog_in_config_t ) );

    return _acquire( obj, true );
}

err_t analog_in_set_resolution( analog_in_t *obj, analog_in_resolution_t resolution )
{
    if ( _acquire(obj, false) != ACQUIRE_FAIL )
    {
        obj->config.resolution = resolution;
        #if DRV_TO_HAL
        return hal_adc_set_resolution( &obj->handle, &obj->config );
        #else
        hal_adc_handle_register_t *hal_handle = ( hal_adc_handle_register_t * )hal_is_handle_null((handle_t *)&obj->handle);
        err_t hal_status = HAL_ADC_SUCCESS;

        if ( !hal_handle )
        {
            return HAL_ADC_ERROR;
        }

        hal_handle->init_state = false;

        hal_status = hal_ll_adc_set_resolution( (handle_t *)&hal_handle, (hal_ll_adc_resolution_t)obj->config.resolution );

        if ( hal_status != HAL_ADC_SUCCESS )
        {
            return HAL_ADC_ERROR;
        } else {
            hal_handle->init_state = true;
            return hal_status;
        }
        #endif
    } else {
        return ADC_ERROR;
    }
}

err_t analog_in_set_vref_input( analog_in_t *obj, analog_in_vref_t vref )
{
    if ( _acquire( obj, false ) != ACQUIRE_FAIL )
    {
        obj->config.vref_input = vref;
        #if DRV_TO_HAL
        return hal_adc_set_vref_input( &obj->handle, &obj->config );
        #else
        hal_adc_handle_register_t *hal_handle = ( hal_adc_handle_register_t * )hal_is_handle_null((handle_t *)&obj->handle);
        err_t hal_status = HAL_ADC_SUCCESS;

        if ( !hal_handle )
        {
            return HAL_ADC_ERROR;
        }

        hal_handle->init_state = false;

        hal_status = hal_ll_adc_set_vref_input( (handle_t *)&hal_handle, (hal_ll_adc_voltage_reference_t)obj->config.vref_input );

        if ( hal_status != HAL_ADC_SUCCESS )
        {
            return HAL_ADC_ERROR;
        } else {
            hal_handle->init_state = true;
            return hal_status;
        }
        #endif
    } else {
        return ADC_ERROR;
    }
}

err_t analog_in_set_vref_value( analog_in_t *obj, float vref_value )
{
    if ( _acquire( obj, false ) != ACQUIRE_FAIL )
    {
        obj->config.vref_value = vref_value;
        #if DRV_TO_HAL
        hal_adc_set_vref_value( &obj->handle, &obj->config );
        #else
        hal_adc_handle_register_t *hal_handle = ( hal_adc_handle_register_t * )hal_is_handle_null( (handle_t *)&obj->handle );

        if ( hal_handle )
        {
            hal_ll_adc_set_vref_value( (handle_t *)&hal_handle, obj->config.vref_value );
        }
        #endif
        return ADC_SUCCESS;
    } else {
        return ADC_ERROR;
    }
}

err_t analog_in_read( analog_in_t *obj, uint16_t *readDatabuf )
{
    if ( _acquire( obj, false ) != ACQUIRE_FAIL )
    {
        #if DRV_TO_HAL
        return hal_adc_read( &obj->handle, readDatabuf );
        #else
        hal_adc_handle_register_t *hal_handle = ( hal_adc_handle_register_t * )hal_is_handle_null( (handle_t *)&obj->handle );
        err_t hal_status = HAL_ADC_SUCCESS;

        if ( !hal_handle )
        {
            return HAL_ADC_ERROR;
        }

        if ( !readDatabuf )
        {
            return HAL_ADC_ERROR;
        }

        if ( hal_handle->init_state == false )
        {
            hal_status = hal_ll_module_configure_adc( (handle_t *)&hal_handle );
        }

        if ( hal_status != HAL_ADC_SUCCESS )
        {
            return HAL_ADC_ERROR;
        } else {
            hal_handle->init_state = true;
        }

        return hal_ll_adc_read( (handle_t *)&hal_handle, readDatabuf );
        #endif
    } else {
        return ADC_ERROR;
    }
}

err_t analog_in_read_voltage( analog_in_t *obj, float *readDatabuf )
{
    if ( _acquire( obj, false ) != ACQUIRE_FAIL )
    {
        #if DRV_TO_HAL
        return hal_adc_read_voltage( &obj->handle, readDatabuf );
        #else
        uint16_t adc_value;
        uint16_t local_resolution;

        hal_adc_t *hal_obj = ( hal_adc_t * ) obj;

        hal_adc_handle_register_t *hal_handle = ( hal_adc_handle_register_t * )hal_is_handle_null( (handle_t *)&obj->handle );
        err_t hal_status = HAL_ADC_SUCCESS;

        if ( !hal_handle )
        {
            return HAL_ADC_ERROR;
        }

        if ( !readDatabuf )
        {
            return HAL_ADC_ERROR;
        }

        if ( hal_handle->init_state == false )
        {
            hal_status = hal_ll_module_configure_adc( (handle_t *)&hal_handle );
        }

        if ( hal_status != HAL_ADC_SUCCESS )
        {
            return HAL_ADC_ERROR;
        } else {
            hal_handle->init_state = true;
        }

        if ( hal_ll_adc_read( (handle_t *)&hal_handle, &adc_value ) == HAL_ADC_SUCCESS )
        {
            switch( hal_obj->config.resolution ) {
                case HAL_ADC_RESOLUTION_6_BIT:
                    local_resolution = HAL_ADC_6BIT_RES_VAL;
                break;
                case HAL_ADC_RESOLUTION_8_BIT:
                    local_resolution = HAL_ADC_8BIT_RES_VAL;
                break;
                case HAL_ADC_RESOLUTION_10_BIT:
                    local_resolution = HAL_ADC_10BIT_RES_VAL;
                break;
                case HAL_ADC_RESOLUTION_12_BIT:
                    local_resolution = HAL_ADC_12BIT_RES_VAL;
                break;
                case HAL_ADC_RESOLUTION_14_BIT:
                    local_resolution = HAL_ADC_14BIT_RES_VAL;
                break;
                case HAL_ADC_RESOLUTION_16_BIT:
                    local_resolution = HAL_ADC_16BIT_RES_VAL;
                break;

                default:
                    return HAL_ADC_ERROR;
            }
            *readDatabuf = ( adc_value * ( hal_obj->config.vref_value ) ) / ( local_resolution );
            return HAL_ADC_SUCCESS;
        } else {
            return HAL_ADC_ERROR;
        }
        #endif
    } else {
        return ADC_ERROR;
    }
}

err_t analog_in_close( analog_in_t *obj )
{
    if ( ADC_SUCCESS == hal_adc_close( &obj->handle ) )
    {
        obj->handle = NULL;
        _owner = NULL;
        return ADC_SUCCESS;
    } else {
        return ADC_ERROR;
    }
}

// ------------------------------------------------------------------------- END
