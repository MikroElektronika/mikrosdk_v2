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
 * @file  drv_analog_in.c
 * @brief Analog input driver implementation.
 */

#include "drv_analog_in.h"

static analog_in_t *_owner = NULL;

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
    config->input_pin = 0xFFFFFFFF;
    config->resolution = ANALOG_IN_RESOLUTION_DEFAULT;
    config->vref_input = ANALOG_IN_VREF_EXTERNAL;
    config->vref_value = -1.0;
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
        return hal_adc_set_resolution( &obj->handle, &obj->config );
    } else {
        return ADC_ERROR;
    }
}

err_t analog_in_set_vref_input( analog_in_t *obj, analog_in_vref_t vref )
{
    if ( _acquire( obj, false ) != ACQUIRE_FAIL )
    {
        obj->config.vref_input = vref;
        return hal_adc_set_vref_input( &obj->handle, &obj->config );
    } else {
        return ADC_ERROR;
    }
}

err_t analog_in_set_vref_value( analog_in_t *obj, float vref_value )
{
    if ( _acquire( obj, false ) != ACQUIRE_FAIL )
    {
        obj->config.vref_value = vref_value;
        hal_adc_set_vref_value( &obj->handle, &obj->config );
        return ADC_SUCCESS;
    } else {
        return ADC_ERROR;
    }
}

err_t analog_in_read( analog_in_t *obj, uint16_t *readDatabuf )
{
    if ( _acquire( obj, false ) != ACQUIRE_FAIL )
    {
        return hal_adc_read( &obj->handle, readDatabuf );
    } else {
        return ADC_ERROR;
    }
}

err_t analog_in_read_voltage( analog_in_t *obj, float *readDatabuf )
{
    if ( _acquire( obj, false ) != ACQUIRE_FAIL )
    {
        return hal_adc_read_voltage( &obj->handle, readDatabuf );
    } else {
        return ADC_ERROR;
    }
}

void analog_in_close( analog_in_t *obj )
{
    err_t drv_status;

    drv_status = hal_adc_close( &obj->handle );

    if ( drv_status == ADC_SUCCESS )
    {
        obj->handle = NULL;
        _owner = NULL;
    }
}

// ------------------------------------------------------------------------- END
