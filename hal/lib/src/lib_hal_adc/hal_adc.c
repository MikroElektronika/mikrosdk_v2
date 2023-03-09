/****************************************************************************
**
** Copyright (C) 2023 MikroElektronika d.o.o.
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
 * @file  hal_adc.c
 * @brief This file contains all the functions prototypes for the ADC library.
 */

#include "hal_adc.h"
#include "hal_ll_adc.h"

static handle_t *hal_owner = NULL;

static hal_adc_handle_register_t hal_module_state[ADC_MODULE_COUNT];

static const uint8_t module_state_count = sizeof( hal_module_state ) / ( sizeof( hal_adc_handle_register_t ) );

static handle_t hal_is_handle_null( handle_t *hal_module_handle )
{
    uint8_t hal_module_state_count = module_state_count;

    while ( hal_module_state_count-- )
    {
        if ( *hal_module_handle == ( handle_t )&hal_module_state[ hal_module_state_count ].hal_adc_handle )
        {
            return ( handle_t )&hal_module_state[ hal_module_state_count ].hal_adc_handle;
        }
    }
    return ACQUIRE_SUCCESS;
}

err_t hal_adc_open( handle_t *handle, bool hal_obj_open_state )
{
    uint8_t hal_module_id;
    hal_adc_t *hal_obj = ( hal_adc_t * ) handle;
    err_t hal_status = sizeof( hal_adc_config_t );
    uint8_t hal_module_state_count = module_state_count;

    if ( hal_obj_open_state == true )
    {
        if( hal_is_handle_null( handle ) != ACQUIRE_SUCCESS )
            return ACQUIRE_FAIL;
    }

    if ( hal_owner != handle )
    {
        while ( hal_module_state_count-- ) {
            if ( hal_module_state[ hal_module_state_count ].drv_adc_handle == handle ) {
                hal_owner = handle;
                return ACQUIRE_SUCCESS;
            }
        }

        hal_status = hal_ll_adc_register_handle( hal_obj->config.pin, hal_obj->config.vref_input,
                                                 hal_obj->config.resolution, &hal_module_state, &hal_module_id );

        if ( hal_status == ACQUIRE_SUCCESS )
        {
            hal_module_state[ hal_module_id ].drv_adc_handle = handle;
            *handle = ( handle_t )&hal_module_state[ hal_module_id ].hal_adc_handle;
            hal_owner = handle;
            return ACQUIRE_INIT;
        } else {
            *handle = HAL_MODULE_ERROR;
            return ACQUIRE_FAIL;
        }
    } else {
        return ACQUIRE_SUCCESS;
    }
}

void hal_adc_configure_default( hal_adc_config_t *config )
{
    config->pin        = HAL_PIN_NC;
    config->resolution = HAL_ADC_RESOLUTION_DEFAULT;
    config->vref_input = HAL_ADC_VREF_DEFAULT;
    config->vref_value = -1.0;
}

err_t hal_adc_set_resolution( handle_t *handle, hal_adc_config_t *config )
{
    hal_adc_handle_register_t *hal_handle = ( hal_adc_handle_register_t * )hal_is_handle_null(handle);
    err_t hal_status = HAL_ADC_SUCCESS;

    if ( hal_handle == NULL )
    {
        return HAL_ADC_ERROR;
    }

    hal_handle->init_state = false;

    hal_status = hal_ll_adc_set_resolution( &hal_handle, config->resolution );

    if ( hal_status != HAL_ADC_SUCCESS )
    {
        return HAL_ADC_ERROR;
    } else {
        hal_handle->init_state = true;
        return hal_status;
    }
}

err_t hal_adc_set_vref_input( handle_t *handle, hal_adc_config_t *config )
{
    hal_adc_handle_register_t *hal_handle = ( hal_adc_handle_register_t * )hal_is_handle_null(handle);
    err_t hal_status = HAL_ADC_SUCCESS;

    if ( hal_handle == NULL )
    {
        return HAL_ADC_ERROR;
    }

    hal_handle->init_state = false;

    hal_status = hal_ll_adc_set_vref_input( &hal_handle, config->vref_input );

    if ( hal_status != HAL_ADC_SUCCESS )
    {
        return HAL_ADC_ERROR;
    } else {
        hal_handle->init_state = true;
        return hal_status;
    }
}

void hal_adc_set_vref_value( handle_t *handle, hal_adc_config_t *config )
{
    hal_adc_handle_register_t *hal_handle = ( hal_adc_handle_register_t * )hal_is_handle_null( handle );

    if ( hal_handle != NULL )
    {
        hal_ll_adc_set_vref_value( &hal_handle, config->vref_value );
    }
}

err_t hal_adc_read( handle_t *handle, uint16_t *readDatabuf )
{
    hal_adc_handle_register_t *hal_handle = ( hal_adc_handle_register_t * )hal_is_handle_null( handle );
    err_t hal_status = HAL_ADC_SUCCESS;

    if ( hal_handle == NULL )
    {
        return HAL_ADC_ERROR;
    }

    if ( readDatabuf == NULL )
    {
        return HAL_ADC_ERROR;
    }

    if ( hal_handle->init_state == false )
    {
        hal_status = hal_ll_module_configure_adc( &hal_handle );
    }

    if ( hal_status != HAL_ADC_SUCCESS )
    {
        return HAL_ADC_ERROR;
    } else {
        hal_handle->init_state = true;
    }

    return hal_ll_adc_read( &hal_handle, readDatabuf );
}

err_t hal_adc_read_voltage( handle_t *handle, float *readDatabuf )
{
    uint16_t adc_value;
    uint16_t local_resolution;

    hal_adc_t *hal_obj = ( hal_adc_t * ) handle;

    hal_adc_handle_register_t *hal_handle = ( hal_adc_handle_register_t * )hal_is_handle_null( handle );
    err_t hal_status = HAL_ADC_SUCCESS;

    if ( hal_handle == NULL )
    {
        return HAL_ADC_ERROR;
    }

    if ( readDatabuf == NULL )
    {
        return HAL_ADC_ERROR;
    }

    if ( hal_handle->init_state == false )
    {
        hal_status = hal_ll_module_configure_adc( &hal_handle );
    }

    if ( hal_status != HAL_ADC_SUCCESS )
    {
        return HAL_ADC_ERROR;
    } else {
        hal_handle->init_state = true;
    }

    if ( hal_ll_adc_read( &hal_handle, &adc_value ) == HAL_ADC_SUCCESS )
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
        }
        *readDatabuf = ( adc_value * ( hal_obj->config.vref_value ) ) / ( local_resolution );
        return HAL_ADC_SUCCESS;
    } else {
        return HAL_ADC_ERROR;
    }
}

err_t hal_adc_close( handle_t *handle )
{
    hal_adc_handle_register_t *hal_handle = ( hal_adc_handle_register_t * )hal_is_handle_null( handle );

    if ( hal_handle->hal_adc_handle != NULL )
    {
        hal_adc_t *hal_obj = ( hal_adc_t * )handle;

        hal_ll_adc_close( &hal_handle );

        memset( &hal_obj->config, 0xFF, sizeof( hal_adc_config_t ) );

        hal_handle->hal_adc_handle = NULL;
        hal_handle->drv_adc_handle = NULL;
        hal_handle->init_state = false;

        hal_owner = NULL;

        return HAL_ADC_SUCCESS;
    }

    return HAL_ADC_ERROR;
}

// ------------------------------------------------------------------------- END
