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
** OF MERCHANTABILITY, EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED
** TO THE WARRANTIES FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT.
** IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM,
** DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT
** OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE
** OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
**
****************************************************************************/
/*!
 * @file  drv_pwm.c
 * @brief PWM driver implementation.
 */

#include "drv_pwm.h"

static pwm_t *_owner = NULL;

#if !DRV_TO_HAL
extern hal_pwm_handle_register_t DRV_TO_HAL_PREFIXED(pwm, hal_module_state)[ TIM_MODULE_COUNT ];

extern const uint8_t DRV_TO_HAL_PREFIXED(pwm, module_state_count);

static handle_t hal_is_handle_null( handle_t *hal_module_handle )
{
    uint8_t hal_module_state_count = DRV_TO_HAL_PREFIXED(pwm, module_state_count);

    while( hal_module_state_count-- )
    {
        if ( *hal_module_handle == ( handle_t )&DRV_TO_HAL_PREFIXED(pwm, hal_module_state)[ hal_module_state_count ].hal_pwm_handle )
        {
            return ( handle_t )&DRV_TO_HAL_PREFIXED(pwm, hal_module_state)[ hal_module_state_count ].hal_pwm_handle;
        }
    }
    return ACQUIRE_SUCCESS;
}
#endif

static err_t _acquire( pwm_t *obj, bool obj_open_state )
{
    err_t status = ACQUIRE_SUCCESS;

    if ( obj_open_state == true && _owner == obj )
    {
        return ACQUIRE_FAIL;
    }

    if ( _owner != obj )
    {
        status = hal_pwm_open( &obj->handle, obj_open_state );

        if ( status != ACQUIRE_FAIL )
        {
            _owner = obj;
        }
    }

    return status;
}

void pwm_configure_default( pwm_config_t *config )
{
    if ( config )
    {
        config->pin = (pin_name_t)0xFFFFFFFF;
        config->freq_hz = 0;
    }
}

err_t pwm_open( pwm_t *obj, pwm_config_t *config )
{
    pwm_config_t *p_config = &obj->config;
    memcpy( p_config, config, sizeof( pwm_config_t ) );

    return _acquire( obj, true );
}

err_t pwm_start( pwm_t *obj )
{
    if( _acquire( obj, false ) != ACQUIRE_FAIL )
    {
        #if DRV_TO_HAL
        return hal_pwm_start( &obj->handle );
        #else
        hal_pwm_handle_register_t *hal_handle = ( hal_pwm_handle_register_t * )hal_is_handle_null( (handle_t *)&obj->handle );
        err_t hal_status = HAL_PWM_SUCCESS;

        if ( !hal_handle )
        {
            return HAL_PWM_ERROR;
        }

        if ( hal_handle->init_state == false )
        {
            hal_status = hal_ll_module_configure_tim( (handle_t *)&hal_handle );
        }

        if( hal_status != HAL_PWM_SUCCESS )
        {
            return HAL_PWM_ERROR;
        } else {
            hal_handle->init_state = true;
        }

        hal_status = hal_ll_tim_start( (handle_t *)&hal_handle );

        if( hal_status != HAL_PWM_SUCCESS )
        {
            return HAL_PWM_ERROR;
        } else {
            return hal_status;
        }
        #endif
    } else {
        return PWM_ERROR;
    }
}

err_t pwm_stop( pwm_t *obj )
{
    if( _acquire( obj, false ) != ACQUIRE_FAIL )
    {
        #if DRV_TO_HAL
        return hal_pwm_stop( &obj->handle );
        #else
        hal_pwm_handle_register_t *hal_handle = ( hal_pwm_handle_register_t * )hal_is_handle_null( (handle_t *)&obj->handle );
        err_t hal_status = HAL_PWM_SUCCESS;

        if ( !hal_handle )
        {
            return HAL_PWM_ERROR;
        }

        if ( hal_handle->init_state == false )
        {
            hal_status = hal_ll_module_configure_tim( (handle_t *)&hal_handle );
        }

        if( hal_status != HAL_PWM_SUCCESS )
        {
            return HAL_PWM_ERROR;
        } else {
            hal_handle->init_state = true;
        }

        hal_status = hal_ll_tim_stop( (handle_t *)&hal_handle );

        if( hal_status != HAL_PWM_SUCCESS )
        {
            return HAL_PWM_ERROR;
        } else {
            return hal_status;
        }
        #endif
    } else {
        return PWM_ERROR;
    }
}

err_t pwm_set_duty( pwm_t *obj, float duty_ratio )
{
    if( _acquire( obj, false ) != ACQUIRE_FAIL )
    {
        #if DRV_TO_HAL
        return hal_pwm_set_duty( &obj->handle, duty_ratio );
        #else
        hal_pwm_handle_register_t *hal_handle = ( hal_pwm_handle_register_t * )hal_is_handle_null( (handle_t *)&obj->handle );
        err_t hal_status = HAL_PWM_SUCCESS;

        if ( !hal_handle )
        {
            return HAL_PWM_ERROR;
        }

        if ( hal_handle->init_state == false )
        {
            hal_status = hal_ll_module_configure_tim( (handle_t *)&hal_handle );
        }

        if( hal_status != HAL_PWM_SUCCESS )
        {
            return HAL_PWM_ERROR;
        } else {
            hal_handle->init_state = true;
        }

        if ( duty_ratio > 1 )
        {
            return hal_ll_tim_set_duty( (handle_t *)&hal_handle, HAL_PWM_MAX_DUTY_RATIO );
        } else if ( duty_ratio < 0 ) {
            return hal_ll_tim_set_duty( (handle_t *)&hal_handle, HAL_PWM_MIN_DUTY_RATIO );
        } else {
            return hal_ll_tim_set_duty( (handle_t *)&hal_handle, duty_ratio );
        }
        #endif
    } else {
        return PWM_ERROR;
    }
}

err_t pwm_set_freq( pwm_t *obj, uint32_t freq_hz )
{
    err_t drv_freq_status;

    if( _acquire( obj, false ) != ACQUIRE_FAIL )
    {
        obj->config.freq_hz = freq_hz;

        #if DRV_TO_HAL
        drv_freq_status = hal_pwm_set_freq( &obj->handle, &obj->config );
        #else
        hal_pwm_handle_register_t *hal_handle = ( hal_pwm_handle_register_t * )hal_is_handle_null( (handle_t *)&obj->handle );
        err_t hal_status = HAL_PWM_SUCCESS;

        if ( !hal_handle )
        {
            return HAL_PWM_ERROR;
        }

        if ( obj->config.freq_hz <= 0 )
        {
            return HAL_PWM_ERROR;
        }

        hal_handle->init_state = false;

        hal_status = hal_ll_tim_set_freq( (handle_t *)&hal_handle, obj->config.freq_hz );

        if( hal_status == HAL_PWM_MODULE_ERROR )
        {
            drv_freq_status = HAL_PWM_ERROR;
        } else {
            hal_handle->init_state = true;
            drv_freq_status = HAL_PWM_SUCCESS;
        }
        #endif

        if ( drv_freq_status == PWM_ERROR )
        {
            return PWM_ERROR;
        } else {
            return PWM_SUCCESS;
        }
    } else {
        return PWM_ERROR;
    }
}

err_t pwm_close( pwm_t *obj )
{
    if( PWM_SUCCESS == hal_pwm_close( &obj->handle ) )
    {
        obj->handle = NULL;
        _owner = NULL;
        return PWM_SUCCESS;
    } else {
        return PWM_ERROR;
    }
}

// ------------------------------------------------------------------------- END
