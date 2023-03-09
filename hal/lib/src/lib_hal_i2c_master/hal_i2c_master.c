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
 * @file hal_i2c_master.c
 * @brief I2C master HAL layer implementation.
 */

#include "hal_i2c_master.h"
#include "hal_ll_i2c_master.h"

static handle_t *hal_owner = NULL;

static volatile hal_i2c_master_handle_register_t hal_module_state[ I2C_MODULE_COUNT ];

static const uint8_t module_state_count = sizeof( hal_module_state ) / ( sizeof( hal_i2c_master_handle_register_t ) );

static handle_t hal_is_handle_null( handle_t *hal_module_handle )
{
    uint8_t hal_module_state_count = module_state_count;

    while( hal_module_state_count-- )
    {
        if ( *hal_module_handle == ( handle_t )&hal_module_state[ hal_module_state_count ].hal_i2c_master_handle )
        {
            return ( handle_t )&hal_module_state[ hal_module_state_count ].hal_i2c_master_handle;
        }
    }

    return ACQUIRE_SUCCESS;
}

err_t hal_i2c_master_open( handle_t *handle, bool hal_obj_open_state )
{
    uint8_t hal_module_id;
    err_t hal_status = sizeof( hal_i2c_master_config_t );
    hal_i2c_master_t *hal_obj = ( hal_i2c_master_t * ) handle;
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
            if ( hal_module_state[ hal_module_state_count ].drv_i2c_master_handle == handle ) {
                hal_owner = handle;
                return ACQUIRE_SUCCESS;
            }
        }

        hal_status = hal_ll_i2c_master_register_handle( hal_obj->config.scl, hal_obj->config.sda,
                                                        &hal_module_state, &hal_module_id );

        if( hal_status == ACQUIRE_SUCCESS )
        {
            hal_module_state[ hal_module_id ].drv_i2c_master_handle = handle;
            *handle = ( handle_t )&hal_module_state[ hal_module_id ].hal_i2c_master_handle;
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

void hal_i2c_master_configure_default( hal_i2c_master_config_t *config )
{
    config->addr = 0;

    config->scl = HAL_PIN_NC;
    config->sda = HAL_PIN_NC;

    config->speed = HAL_I2C_MASTER_SPEED_STANDARD;
    config->timeout_pass_count = 10000;
}

void hal_i2c_master_set_slave_address( handle_t *handle, hal_i2c_master_config_t *config )
{
    handle_t hal_handle = hal_is_handle_null( handle );

    if ( hal_handle != NULL )
    {
        hal_ll_i2c_master_set_slave_address( &hal_handle, config->addr );
    }
}

err_t hal_i2c_master_set_speed( handle_t *handle, hal_i2c_master_config_t *config )
{
    hal_i2c_master_handle_register_t *hal_handle = ( hal_i2c_master_handle_register_t * )hal_is_handle_null( handle );
    err_t hal_status = HAL_I2C_MASTER_SUCCESS;

    if ( hal_handle == NULL )
    {
        return HAL_I2C_MASTER_ERROR;
    }

    hal_handle->init_state = false;

    hal_status = hal_ll_i2c_master_set_speed( &hal_handle, config->speed );

    if( ( hal_status == HAL_I2C_MASTER_MODULE_ERROR ) || ( hal_status == HAL_I2C_MASTER_TIMEOUT_INIT ) )
    {
        return HAL_I2C_MASTER_ERROR;
    } else {
        hal_handle->init_state = true;
        return HAL_I2C_MASTER_SUCCESS;
    }
}

void hal_i2c_master_set_timeout( handle_t *handle,  hal_i2c_master_config_t *config )
{
    handle_t hal_handle = hal_is_handle_null( handle );

    if ( hal_handle != NULL )
    {
        hal_ll_i2c_master_set_timeout( &hal_handle, config->timeout_pass_count );
    }
}

err_t hal_i2c_master_read( handle_t handle, uint8_t *read_data_buf, size_t len_read_data )
{
    hal_i2c_master_handle_register_t *hal_handle = ( hal_i2c_master_handle_register_t * )hal_is_handle_null( handle );
    err_t hal_status = HAL_I2C_MASTER_SUCCESS;

    if ( hal_handle == NULL )
    {
        return HAL_I2C_MASTER_ERROR;
    }

    if ( !len_read_data )
    {
        return HAL_I2C_MASTER_ERROR;
    }

    if ( hal_handle->init_state == false )
    {
        hal_status = hal_ll_module_configure_i2c( &hal_handle );
    }

    if( hal_status != HAL_I2C_MASTER_SUCCESS )
    {
        return HAL_I2C_MASTER_ERROR;
    } else {
        hal_handle->init_state = true;
    }

    hal_status = hal_ll_i2c_master_read( &hal_handle, read_data_buf, len_read_data );

    if( hal_status != HAL_I2C_MASTER_SUCCESS )
    {
        return HAL_I2C_MASTER_ERROR;
    } else {
        return hal_status;
    }
}

err_t hal_i2c_master_write( handle_t handle, uint8_t *write_data_buf, size_t len_write_data )
{
    hal_i2c_master_handle_register_t *hal_handle = ( hal_i2c_master_handle_register_t * )hal_is_handle_null( handle );
    err_t hal_status = HAL_I2C_MASTER_SUCCESS;

    if ( hal_handle == NULL )
    {
        return HAL_I2C_MASTER_ERROR;
    }

    if ( !len_write_data )
    {
        return HAL_I2C_MASTER_ERROR;
    }

    if ( hal_handle->init_state == false )
    {
        hal_status = hal_ll_module_configure_i2c( &hal_handle );
    }

    if( hal_status != HAL_I2C_MASTER_SUCCESS )
    {
        return HAL_I2C_MASTER_ERROR;
    } else {
        hal_handle->init_state = true;
    }

    hal_status = hal_ll_i2c_master_write( &hal_handle, write_data_buf, len_write_data );

    if( hal_status != HAL_I2C_MASTER_SUCCESS )
    {
        return HAL_I2C_MASTER_ERROR;
    } else {
        return hal_status;
    }
}

err_t hal_i2c_master_write_then_read( handle_t handle, uint8_t *write_data_buf, size_t len_write_data,
                                                       uint8_t *read_data_buf, size_t len_read_data )
{
    hal_i2c_master_handle_register_t *hal_handle = ( hal_i2c_master_handle_register_t * )hal_is_handle_null( handle );
    err_t hal_status = HAL_I2C_MASTER_SUCCESS;

    if ( hal_handle == NULL )
    {
        return HAL_I2C_MASTER_ERROR;
    }

    if ( !len_read_data || !len_write_data )
    {
        return HAL_I2C_MASTER_ERROR;
    }

    if ( hal_handle->init_state == false )
    {
        hal_status = hal_ll_module_configure_i2c( &hal_handle );
    }

    if( hal_status != HAL_I2C_MASTER_SUCCESS )
    {
        return HAL_I2C_MASTER_ERROR;
    } else {
        hal_handle->init_state = true;
    }

    hal_status = hal_ll_i2c_master_write_then_read( &hal_handle, write_data_buf, len_write_data,
                                                    read_data_buf, len_read_data );

    if( hal_status != HAL_I2C_MASTER_SUCCESS )
    {
        return HAL_I2C_MASTER_ERROR;
    } else {
        return hal_status;
    }
}

err_t hal_i2c_master_close( handle_t *handle )
{
    hal_i2c_master_handle_register_t *hal_handle = ( hal_i2c_master_handle_register_t * )hal_is_handle_null( handle );

    if( hal_handle->hal_i2c_master_handle != NULL )
    {
        hal_i2c_master_t *hal_obj = ( hal_i2c_master_t * )handle;

        hal_ll_i2c_master_close( &hal_handle );

        memset( &hal_obj->config, 0xFF, sizeof( hal_i2c_master_config_t ) );

        hal_handle->hal_i2c_master_handle = NULL;
        hal_handle->drv_i2c_master_handle = NULL;

        hal_handle->init_state = false;

        hal_owner = NULL;

        return HAL_I2C_MASTER_SUCCESS;
    }

    return HAL_I2C_MASTER_ERROR;
}

// ------------------------------------------------------------------------- END
