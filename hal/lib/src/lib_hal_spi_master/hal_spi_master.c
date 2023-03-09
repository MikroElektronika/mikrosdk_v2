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
 * @file  hal_spi_master.c
 * @brief SPI Master HAL layer implementation.
 */

#include "hal_spi_master.h"
#include "hal_ll_spi_master.h"

hal_spi_master_chip_select_polarity_t hal_spi_master_chip_select_polarity = HAL_SPI_MASTER_CHIP_SELECT_DEFAULT_POLARITY;

static handle_t *hal_owner = NULL;

static volatile hal_spi_master_handle_register_t hal_module_state[ SPI_MODULE_COUNT ];

static const uint8_t module_state_count = sizeof( hal_module_state ) / ( sizeof( hal_spi_master_handle_register_t ) );

static handle_t hal_is_handle_null( handle_t *hal_module_handle )
{
    uint8_t hal_module_state_count = module_state_count;

    while ( hal_module_state_count-- )
    {
        if ( *hal_module_handle == ( handle_t )&hal_module_state[ hal_module_state_count ].hal_spi_master_handle )
        {
            return ( handle_t )&hal_module_state[ hal_module_state_count ].hal_spi_master_handle;
        }
    }
    return ACQUIRE_SUCCESS;
}

err_t hal_spi_master_open( handle_t *handle, bool hal_obj_open_state )
{
    uint8_t hal_module_id;
    err_t hal_status = sizeof( hal_spi_master_config_t );
    hal_spi_master_t *hal_obj = ( hal_spi_master_t* )handle;
    uint8_t hal_module_state_count = module_state_count;

    if ( hal_obj_open_state == true )
    {
        if( hal_is_handle_null( handle ) != ACQUIRE_SUCCESS )
        {
            return ACQUIRE_FAIL;
        }
    }

    if ( hal_owner != handle ) {
        while ( hal_module_state_count-- ) {
            if ( hal_module_state[ hal_module_state_count ].drv_spi_master_handle == handle ) {
                hal_owner = handle;
                return ACQUIRE_SUCCESS;
            }
        }

        hal_status = hal_ll_spi_master_register_handle( hal_obj->config.sck,
                                                        hal_obj->config.miso,
                                                        hal_obj->config.mosi,
                                                        &hal_module_state,
                                                        &hal_module_id );

        if ( hal_status == ACQUIRE_SUCCESS )
        {
            hal_module_state[ hal_module_id ].drv_spi_master_handle = handle;
            *handle = ( handle_t )&hal_module_state[ hal_module_id ].hal_spi_master_handle;
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

void hal_spi_master_configure_default( hal_spi_master_config_t *config )
{
    config->default_write_data = 0;
    config->sck   = HAL_PIN_NC;
    config->miso  = HAL_PIN_NC;
    config->mosi  = HAL_PIN_NC;
    config->speed = 100000;
    config->mode  = HAL_SPI_MASTER_MODE_DEFAULT;
}

void hal_spi_master_select_device( hal_pin_name_t chip_select )
{
    hal_gpio_pin_t struct_cs;
    hal_gpio_configure_pin( &struct_cs, chip_select, HAL_GPIO_DIGITAL_OUTPUT );

    if ( chip_select != 0xFFFF )
    {
        if ( hal_spi_master_chip_select_polarity == HAL_SPI_MASTER_CHIP_SELECT_POLARITY_ACTIVE_HIGH )
        {
            hal_gpio_set_pin_output( &struct_cs );
        } else {
            hal_gpio_clear_pin_output( &struct_cs );
        }
    }
}

void hal_spi_master_deselect_device( hal_pin_name_t chip_select )
{
    hal_gpio_pin_t struct_cs;
    hal_gpio_configure_pin( &struct_cs, chip_select, HAL_GPIO_DIGITAL_OUTPUT );

    if ( chip_select != 0xFFFF )
    {
        if ( hal_spi_master_chip_select_polarity == HAL_SPI_MASTER_CHIP_SELECT_POLARITY_ACTIVE_HIGH )
        {
            hal_gpio_clear_pin_output( &struct_cs );
        } else {
            hal_gpio_set_pin_output( &struct_cs );
        }
    }
}

void hal_spi_master_set_chip_select_polarity( hal_spi_master_chip_select_polarity_t polarity )
{
    if ( polarity == HAL_SPI_MASTER_CHIP_SELECT_POLARITY_ACTIVE_HIGH )
    {
        hal_spi_master_chip_select_polarity = HAL_SPI_MASTER_CHIP_SELECT_POLARITY_ACTIVE_HIGH;
    } else {
        hal_spi_master_chip_select_polarity = HAL_SPI_MASTER_CHIP_SELECT_POLARITY_ACTIVE_LOW;
    }
}

err_t hal_spi_master_set_speed( handle_t *handle, hal_spi_master_config_t *config )
{
    hal_spi_master_handle_register_t *hal_handle = ( hal_spi_master_handle_register_t * )hal_is_handle_null( handle );
    volatile err_t hal_status;

    if ( hal_handle == NULL )
    {
        return HAL_SPI_MASTER_ERROR;
    }

    hal_handle->init_state = false;

    hal_status = hal_ll_spi_master_set_speed( &hal_handle, config->speed );

    if ( hal_status == HAL_SPI_MASTER_MODULE_ERROR )
    {
        return HAL_SPI_MASTER_ERROR;
    } else {
        hal_handle->init_state = true;
        return HAL_SPI_MASTER_SUCCESS;
    }
}

err_t hal_spi_master_set_mode( handle_t *handle, hal_spi_master_config_t *config )
{
    hal_spi_master_handle_register_t *hal_handle = ( hal_spi_master_handle_register_t* )hal_is_handle_null( handle );
    volatile err_t hal_status;

    if ( hal_handle == NULL )
    {
        return HAL_SPI_MASTER_ERROR;
    }

    if ( ( HAL_SPI_MASTER_MODE_3 < config->mode ) || ( config->mode < HAL_SPI_MASTER_MODE_0 ) )
    {
        return HAL_SPI_MASTER_ERROR;
    }

    hal_handle->init_state = false;

    hal_status = hal_ll_spi_master_set_mode( &hal_handle, config->mode );

    if ( hal_status == HAL_SPI_MASTER_MODULE_ERROR )
    {
        return HAL_SPI_MASTER_ERROR;
    } else {
        hal_handle->init_state = true;
        return HAL_SPI_MASTER_SUCCESS;
    }
}

void hal_spi_master_set_default_write_data( handle_t *handle, hal_spi_master_config_t *config )
{
    handle_t hal_handle = hal_is_handle_null( handle );

    if ( hal_handle != NULL )
    {
        hal_ll_spi_master_set_default_write_data( &hal_handle, config->default_write_data );
    }
}

err_t hal_spi_master_write( handle_t handle, uint8_t *write_data_buffer, size_t write_data_length )
{
    hal_spi_master_handle_register_t *hal_handle = ( hal_spi_master_handle_register_t* )hal_is_handle_null( handle );
    err_t hal_status = HAL_SPI_MASTER_SUCCESS;

    if ( hal_handle == NULL )
    {
        return HAL_SPI_MASTER_ERROR;
    }

    if ( !write_data_length )
    {
        return HAL_SPI_MASTER_ERROR;
    }

    if ( hal_handle->init_state == false )
    {
        hal_status = hal_ll_module_configure_spi( &hal_handle );
    }

    if ( hal_status != HAL_SPI_MASTER_SUCCESS )
    {
        return HAL_SPI_MASTER_ERROR;
    } else {
        hal_handle->init_state = true;
    }

    hal_status = hal_ll_spi_master_write( &hal_handle, write_data_buffer, write_data_length );

    if ( hal_status == HAL_SPI_MASTER_MODULE_ERROR )
    {
        return HAL_SPI_MASTER_ERROR;
    } else {
        return HAL_SPI_MASTER_SUCCESS;
    }
}

err_t hal_spi_master_read( handle_t handle, uint8_t *read_data_buffer, size_t read_data_length )
{
    hal_spi_master_handle_register_t *hal_handle = ( hal_spi_master_handle_register_t* )hal_is_handle_null( handle );
    err_t hal_status = HAL_SPI_MASTER_SUCCESS;

    if ( hal_handle == NULL )
    {
        return HAL_SPI_MASTER_ERROR;
    }

    if ( !read_data_length )
    {
        return HAL_SPI_MASTER_ERROR;
    }

    if ( hal_handle->init_state == false )
    {
        hal_status = hal_ll_module_configure_spi( &hal_handle );
    }

    if( hal_status != HAL_SPI_MASTER_SUCCESS )
    {
        return HAL_SPI_MASTER_ERROR;
    } else {
        hal_handle->init_state = true;
    }

    hal_status = hal_ll_spi_master_read( &hal_handle, read_data_buffer, read_data_length );

    if ( hal_status == HAL_SPI_MASTER_MODULE_ERROR )
    {
        return HAL_SPI_MASTER_ERROR;
    } else {
        return HAL_SPI_MASTER_SUCCESS;
    }
}

err_t hal_spi_master_write_then_read( handle_t handle, uint8_t *write_data_buffer,
                                                        size_t length_write_data,
                                                       uint8_t *read_data_buffer,
                                                        size_t length_read_data )
{
    hal_spi_master_handle_register_t *hal_handle = ( hal_spi_master_handle_register_t* )hal_is_handle_null( handle );
    err_t hal_status = HAL_SPI_MASTER_SUCCESS;

    if ( hal_handle == NULL )
    {
        return HAL_SPI_MASTER_ERROR;
    }

    if ( !length_write_data || !length_read_data )
    {
        return HAL_SPI_MASTER_ERROR;
    }

    if ( hal_handle->init_state == false )
    {
        hal_status = hal_ll_module_configure_spi( &hal_handle );
    }

    if( hal_status != HAL_SPI_MASTER_SUCCESS )
    {
        return HAL_SPI_MASTER_ERROR;
    } else {
        hal_handle->init_state = true;
    }

    hal_status =  hal_ll_spi_master_write_then_read( &hal_handle, write_data_buffer,
                                                                  length_write_data,
                                                                  read_data_buffer,
                                                                  length_read_data );

    if (hal_status == HAL_SPI_MASTER_MODULE_ERROR)
    {
        return HAL_SPI_MASTER_ERROR;
    } else {
        return HAL_SPI_MASTER_SUCCESS;
    }
}

err_t hal_spi_master_close( handle_t *handle )
{
    hal_spi_master_handle_register_t *hal_handle = ( hal_spi_master_handle_register_t * )hal_is_handle_null( handle );

    if ( hal_handle->hal_spi_master_handle != NULL )
    {
        hal_spi_master_t *hal_obj = ( hal_spi_master_t * )handle;

        hal_ll_spi_master_close( &hal_handle );

        memset( &hal_obj->config, 0xFF, sizeof( hal_spi_master_config_t ) );

        hal_handle->hal_spi_master_handle = NULL;
        hal_handle->drv_spi_master_handle = NULL;

        hal_handle->init_state = false;

        hal_owner = NULL;

        return HAL_SPI_MASTER_SUCCESS;
    }
    return HAL_SPI_MASTER_ERROR;
}

// ------------------------------------------------------------------------- END
