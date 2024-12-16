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
 * @file  drv_i2c_master.c
 * @brief I2C master driver implementation.
 */

#include "drv_i2c_master.h"

static i2c_master_t *_owner = NULL;

#if !DRV_TO_HAL
extern hal_i2c_master_handle_register_t DRV_TO_HAL_PREFIXED(i2c, hal_module_state)[ I2C_MODULE_COUNT ];

extern const uint8_t DRV_TO_HAL_PREFIXED(i2c, module_state_count);

static handle_t hal_is_handle_null( handle_t *hal_module_handle )
{
    uint8_t hal_module_state_count = DRV_TO_HAL_PREFIXED(i2c, module_state_count);

    #ifdef __XC8__
    uint32_t tmp_addr;
    #endif

    while( hal_module_state_count-- )
    {
        #ifdef __XC8__
        tmp_addr = ( handle_t )&DRV_TO_HAL_PREFIXED(i2c, hal_module_state)[ hal_module_state_count ].hal_i2c_master_handle;
        if ( *hal_module_handle == tmp_addr )
        {
            return tmp_addr;
        }
        #else
        if ( *hal_module_handle == ( handle_t )&DRV_TO_HAL_PREFIXED(i2c, hal_module_state)[ hal_module_state_count ].hal_i2c_master_handle )
        {
            return ( handle_t )&DRV_TO_HAL_PREFIXED(i2c, hal_module_state)[ hal_module_state_count ].hal_i2c_master_handle;
        }
        #endif
    }

    return ACQUIRE_SUCCESS;
}
#endif

static err_t _acquire( i2c_master_t *obj, bool obj_open_state )
{
    err_t status = ACQUIRE_SUCCESS;

    if ( obj_open_state == true && _owner == obj )
    {
        return ACQUIRE_FAIL;
    }

    if ( _owner != obj )
    {
        status = hal_i2c_master_open( &obj->handle,obj_open_state );

        if ( status != ACQUIRE_FAIL )
        {
            _owner = obj;
        }
    }

    return status;
}

void i2c_master_configure_default( i2c_master_config_t *config )
{
    if ( config )
    {
        config->addr = 0;

        config->sda = (pin_name_t)0xFFFFFFFF;
        config->scl = (pin_name_t)0xFFFFFFFF;

        config->speed = I2C_MASTER_SPEED_STANDARD;
        config->timeout_pass_count = 10000;
    }
}

err_t i2c_master_open( i2c_master_t *obj, i2c_master_config_t *config )
{
    i2c_master_config_t *p_config = &obj->config;
    memcpy( p_config, config, sizeof( i2c_master_config_t ) );

    return _acquire( obj, true );
}

err_t i2c_master_set_speed( i2c_master_t *obj, uint32_t speed )
{
    if( _acquire( obj, false ) != ACQUIRE_FAIL )
    {
        obj->config.speed = speed;
        #if DRV_TO_HAL
        return hal_i2c_master_set_speed( &obj->handle, &obj->config );
        #else
        hal_i2c_master_handle_register_t *hal_handle = ( hal_i2c_master_handle_register_t * )hal_is_handle_null( (handle_t *)&obj->handle );
        err_t hal_status = HAL_I2C_MASTER_SUCCESS;

        if ( !hal_handle )
        {
            return HAL_I2C_MASTER_ERROR;
        }

        hal_handle->init_state = false;

        hal_status = hal_ll_i2c_master_set_speed( (handle_t *)&hal_handle, obj->config.speed );

        if( ( hal_status == HAL_I2C_MASTER_MODULE_ERROR ) || ( hal_status == HAL_I2C_MASTER_TIMEOUT_INIT ) )
        {
            return HAL_I2C_MASTER_ERROR;
        } else {
            hal_handle->init_state = true;
            return HAL_I2C_MASTER_SUCCESS;
        }
        #endif
    } else {
        return I2C_MASTER_ERROR;
    }
}

err_t i2c_master_set_timeout( i2c_master_t *obj, uint16_t timeout_pass_count )
{
    if( _acquire( obj, false ) != ACQUIRE_FAIL )
    {
        obj->config.timeout_pass_count = timeout_pass_count;
        #if DRV_TO_HAL
        hal_i2c_master_set_timeout( &obj->handle, &obj->config );
        #else
        handle_t hal_handle = hal_is_handle_null( &obj->handle );

        if ( hal_handle )
        {
            hal_ll_i2c_master_set_timeout( &hal_handle, obj->config.timeout_pass_count );
        }
        #endif
        return I2C_MASTER_SUCCESS;
    } else {
        return I2C_MASTER_ERROR;
    }
}

err_t i2c_master_set_slave_address( i2c_master_t *obj, uint8_t address )
{
    if( _acquire( obj, false ) != ACQUIRE_FAIL )
    {
        obj->config.addr = address;
        #if DRV_TO_HAL
        hal_i2c_master_set_slave_address( &obj->handle, &obj->config );
        #else
        handle_t hal_handle = hal_is_handle_null( &obj->handle );

        if ( hal_handle )
        {
            hal_ll_i2c_master_set_slave_address( &hal_handle, obj->config.addr );
        }
        #endif
        return I2C_MASTER_SUCCESS;
    } else {
        return I2C_MASTER_ERROR;
    }
}

err_t i2c_master_write( i2c_master_t *obj, uint8_t *write_data_buf, size_t len_write_data )
{
    if(_acquire( obj, false ) != ACQUIRE_FAIL )
    {
        #if DRV_TO_HAL
        return hal_i2c_master_write( &obj->handle, write_data_buf, len_write_data );
        #else
        hal_i2c_master_handle_register_t *hal_handle = ( hal_i2c_master_handle_register_t * )hal_is_handle_null( (handle_t *)&obj->handle );
        err_t hal_status = HAL_I2C_MASTER_SUCCESS;

        if ( !hal_handle )
        {
            return HAL_I2C_MASTER_ERROR;
        }

        if ( len_write_data <= 0 )
        {
            return HAL_I2C_MASTER_ERROR;
        }

        if ( !write_data_buf )
        {
            return HAL_I2C_MASTER_ERROR;
        }

        if ( hal_handle->init_state == false )
        {
            hal_status = hal_ll_module_configure_i2c( (handle_t *)&hal_handle );
        }

        if( hal_status != HAL_I2C_MASTER_SUCCESS )
        {
            return HAL_I2C_MASTER_ERROR;
        } else {
            hal_handle->init_state = true;
        }

        hal_status = hal_ll_i2c_master_write( (handle_t *)&hal_handle, write_data_buf, len_write_data );

        if( hal_status != HAL_I2C_MASTER_SUCCESS )
        {
            return HAL_I2C_MASTER_ERROR;
        } else {
            return hal_status;
        }
        #endif
    } else {
        return I2C_MASTER_ERROR;
    }
}

err_t i2c_master_read(i2c_master_t *obj, uint8_t *read_data_buf, size_t len_read_data )
{
    if( _acquire( obj, false ) != ACQUIRE_FAIL )
    {
        #if DRV_TO_HAL
        return hal_i2c_master_read( &obj->handle, read_data_buf, len_read_data );
        #else
        hal_i2c_master_handle_register_t *hal_handle = ( hal_i2c_master_handle_register_t * )hal_is_handle_null( (handle_t *)&obj->handle );
        err_t hal_status = HAL_I2C_MASTER_SUCCESS;

        if ( !hal_handle )
        {
            return HAL_I2C_MASTER_ERROR;
        }

        if ( len_read_data <= 0 )
        {
            return HAL_I2C_MASTER_ERROR;
        }

        if ( !read_data_buf )
        {
            return HAL_I2C_MASTER_ERROR;
        }

        if ( hal_handle->init_state == false )
        {
            hal_status = hal_ll_module_configure_i2c( (handle_t *)&hal_handle );
        }

        if( hal_status != HAL_I2C_MASTER_SUCCESS )
        {
            return HAL_I2C_MASTER_ERROR;
        } else {
            hal_handle->init_state = true;
        }

        hal_status = hal_ll_i2c_master_read( (handle_t *)&hal_handle, read_data_buf, len_read_data );

        if( hal_status != HAL_I2C_MASTER_SUCCESS )
        {
            return HAL_I2C_MASTER_ERROR;
        } else {
            return hal_status;
        }
        #endif
    } else {
        return I2C_MASTER_ERROR;
    }
}

err_t i2c_master_write_then_read( i2c_master_t *obj, uint8_t *write_data_buf, size_t len_write_data,
                                                     uint8_t *read_data_buf, size_t len_read_data )
{
    if( _acquire( obj, false ) != ACQUIRE_FAIL )
    {
        #if DRV_TO_HAL
        return hal_i2c_master_write_then_read( &obj->handle, write_data_buf, len_write_data,
                                               read_data_buf, len_read_data );
        #else
        hal_i2c_master_handle_register_t *hal_handle = ( hal_i2c_master_handle_register_t * )hal_is_handle_null( (handle_t *)&obj->handle );
        err_t hal_status = HAL_I2C_MASTER_SUCCESS;

        if ( !hal_handle )
        {
            return HAL_I2C_MASTER_ERROR;
        }

        if ( (len_read_data <= 0 ) || (len_write_data <= 0) )
        {
            return HAL_I2C_MASTER_ERROR;
        }

        if ( !read_data_buf || !write_data_buf )
        {
            return HAL_I2C_MASTER_ERROR;
        }

        if ( hal_handle->init_state == false )
        {
            hal_status = hal_ll_module_configure_i2c( (handle_t *)&hal_handle );
        }

        if( hal_status != HAL_I2C_MASTER_SUCCESS )
        {
            return HAL_I2C_MASTER_ERROR;
        } else {
            hal_handle->init_state = true;
        }

        hal_status = hal_ll_i2c_master_write_then_read( (handle_t *)&hal_handle, write_data_buf, len_write_data,
                                                        read_data_buf, len_read_data );

        if( hal_status != HAL_I2C_MASTER_SUCCESS )
        {
            return HAL_I2C_MASTER_ERROR;
        } else {
            return hal_status;
        }
        #endif
    } else {
        return I2C_MASTER_ERROR;
    }
}

err_t i2c_master_close( i2c_master_t *obj )
{
    if( I2C_MASTER_SUCCESS == hal_i2c_master_close( &obj->handle ) )
    {
        obj->handle = NULL;
        _owner = NULL;
        return I2C_MASTER_SUCCESS;
    } else {
        return I2C_MASTER_ERROR;
    }
}

// ------------------------------------------------------------------------- END
