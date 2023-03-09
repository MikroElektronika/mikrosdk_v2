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
 * @file hal_pwm.c
 * @brief PWM HAL layer implementation.
 */

#include "hal_pwm.h"

static handle_t *hal_owner = NULL;

static volatile hal_pwm_handle_register_t hal_module_state[ TIM_MODULE_COUNT ];

static const uint8_t module_state_count = sizeof( hal_module_state ) / ( sizeof( hal_pwm_handle_register_t ) );

static handle_t hal_is_handle_null( handle_t *hal_module_handle )
{
    uint8_t hal_module_state_count = module_state_count;

    while( hal_module_state_count-- )
    {
        if ( *hal_module_handle == ( handle_t )&hal_module_state[ hal_module_state_count ].hal_pwm_handle )
        {
            return ( handle_t )&hal_module_state[ hal_module_state_count ].hal_pwm_handle;
        }
    }
    return ACQUIRE_SUCCESS;
}

err_t hal_pwm_open( handle_t *handle, bool hal_obj_open_state )
{
    err_t hal_status = sizeof( hal_pwm_config_t );
    uint8_t hal_module_id;
    hal_pwm_t *hal_obj = ( hal_pwm_t * ) handle;
    uint8_t hal_module_state_count = module_state_count;

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
            if ( hal_module_state[ hal_module_state_count ].drv_pwm_handle == handle ) {
                hal_owner = handle;
                return ACQUIRE_SUCCESS;
            }
        }

        hal_status = hal_ll_tim_register_handle( hal_obj->config.pin, &hal_module_state, &hal_module_id );

        if( hal_status == ACQUIRE_SUCCESS )
        {
            hal_module_state[ hal_module_id ].drv_pwm_handle = handle;
            *handle = ( handle_t )&hal_module_state[ hal_module_id ].hal_pwm_handle;

            // Set HAL layer owner
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

void hal_pwm_configure_default( hal_pwm_config_t *config )
{
    config->pin = HAL_PIN_NC;
    config->freq_hz = 0;
}

err_t hal_pwm_start( handle_t *handle )
{
    hal_pwm_handle_register_t *hal_handle = ( hal_pwm_handle_register_t * )hal_is_handle_null( handle );
    err_t hal_status = HAL_PWM_SUCCESS;

    if ( hal_handle == NULL )
    {
        return HAL_PWM_ERROR;
    }

    if ( hal_handle->init_state == false )
    {
        hal_status = hal_ll_module_configure_tim( &hal_handle );
    }

    if( hal_status != HAL_PWM_SUCCESS )
    {
        return HAL_PWM_ERROR;
    } else {
        hal_handle->init_state = true;
    }

    hal_status = hal_ll_tim_start( &hal_handle );

    if( hal_status != HAL_PWM_SUCCESS )
    {
        return HAL_PWM_ERROR;
    } else {
        return hal_status;
    }
}

err_t hal_pwm_stop( handle_t *handle )
{
    hal_pwm_handle_register_t *hal_handle = ( hal_pwm_handle_register_t * )hal_is_handle_null( handle );
    err_t hal_status = HAL_PWM_SUCCESS;

    if ( hal_handle == NULL )
    {
        return HAL_PWM_ERROR;
    }

    if ( hal_handle->init_state == false )
    {
        hal_status = hal_ll_module_configure_tim( &hal_handle );
    }

    if( hal_status != HAL_PWM_SUCCESS )
    {
        return HAL_PWM_ERROR;
    } else {
        hal_handle->init_state = true;
    }

    hal_status = hal_ll_tim_stop( &hal_handle );

    if( hal_status != HAL_PWM_SUCCESS )
    {
        return HAL_PWM_ERROR;
    } else {
        return hal_status;
    }
}

err_t hal_pwm_set_duty( handle_t *handle, float duty_ratio )
{
    hal_pwm_handle_register_t *hal_handle = ( hal_pwm_handle_register_t * )hal_is_handle_null( handle );
    err_t hal_status = HAL_PWM_SUCCESS;

    if ( hal_handle == NULL )
    {
        return HAL_PWM_ERROR;
    }

    if ( hal_handle->init_state == false )
    {
        hal_status = hal_ll_module_configure_tim( &hal_handle );
    }

    if( hal_status != HAL_PWM_SUCCESS )
    {
        return HAL_PWM_ERROR;
    } else {
        hal_handle->init_state = true;
    }

    if ( duty_ratio > 1 )
    {
        return hal_ll_tim_set_duty( &hal_handle, HAL_PWM_MAX_DUTY_RATIO );
    } else if ( duty_ratio < 0 ) {
        return hal_ll_tim_set_duty( &hal_handle, HAL_PWM_MIN_DUTY_RATIO );
    } else {
        return hal_ll_tim_set_duty( &hal_handle, duty_ratio );
    }
}

err_t hal_pwm_set_freq( handle_t *handle, hal_pwm_config_t *config )
{
    hal_pwm_handle_register_t *hal_handle = ( hal_pwm_handle_register_t * )hal_is_handle_null( handle );
    err_t hal_status = HAL_PWM_SUCCESS;

    if ( hal_handle == NULL )
    {
        return HAL_PWM_ERROR;
    }

    if ( config->freq_hz <= 0 )
    {
        return HAL_PWM_ERROR;
    }

    hal_handle->init_state = false;

    hal_status = hal_ll_tim_set_freq( &hal_handle, config->freq_hz );

    if( hal_status == HAL_PWM_MODULE_ERROR )
    {
        return HAL_PWM_ERROR;
    } else {
        hal_handle->init_state = true;
        return HAL_PWM_SUCCESS;
    }
}

err_t hal_pwm_close( handle_t *handle )
{
    hal_pwm_handle_register_t *hal_handle = ( hal_pwm_handle_register_t * )hal_is_handle_null( handle );

    if( hal_handle->hal_pwm_handle != NULL )
    {
        hal_pwm_t *hal_obj = ( hal_pwm_t* )handle;
        hal_ll_tim_close( &hal_handle );

        memset( &hal_obj->config, 0xFF, sizeof( hal_pwm_config_t ) );

        hal_handle->hal_pwm_handle = NULL;
        hal_handle->drv_pwm_handle = NULL;

        hal_handle->init_state = false;

        hal_owner = NULL;

        return HAL_PWM_SUCCESS;
    }

    return HAL_PWM_ERROR;
}

// ------------------------------------------------------------------------- END
