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
 * @file  drv_spi_master.c
 * @brief SPI master driver implementation.
 */

#include "drv_spi_master.h"

static spi_master_t *_owner = NULL;

#if !DRV_TO_HAL
extern hal_spi_master_handle_register_t DRV_TO_HAL_PREFIXED(spi, hal_module_state)[ SPI_MODULE_COUNT ];

extern const uint8_t DRV_TO_HAL_PREFIXED(spi, module_state_count);

extern hal_spi_master_chip_select_polarity_t hal_spi_master_chip_select_polarity;

static handle_t hal_is_handle_null( handle_t *hal_module_handle )
{
    uint8_t hal_module_state_count = DRV_TO_HAL_PREFIXED(spi, module_state_count);

    #ifdef __XC8__
    uint32_t tmp_addr;
    #endif

    while ( hal_module_state_count-- )
    {
        #ifdef __XC8__
        tmp_addr = ( handle_t )&DRV_TO_HAL_PREFIXED(spi, hal_module_state)[ hal_module_state_count ].hal_spi_master_handle;
        if ( *hal_module_handle == tmp_addr )
        {
            return tmp_addr;
        }
        #else
        if ( *hal_module_handle == ( handle_t )&DRV_TO_HAL_PREFIXED(spi, hal_module_state)[ hal_module_state_count ].hal_spi_master_handle )
        {
            return ( handle_t )&DRV_TO_HAL_PREFIXED(spi, hal_module_state)[ hal_module_state_count ].hal_spi_master_handle;
        }
        #endif
    }

    return ACQUIRE_SUCCESS;
}
#endif

static err_t _acquire( spi_master_t *obj, bool obj_open_state )
{
    err_t status = ACQUIRE_SUCCESS;

    if ( obj_open_state == true && _owner == obj )
    {
        return ACQUIRE_FAIL;
    }

    if ( _owner !=  obj )
    {
        status = hal_spi_master_open( &obj->handle, obj_open_state );

        if( status != ACQUIRE_FAIL )
        {
            _owner = obj;
        }
    }
    return status;
}

void spi_master_configure_default( spi_master_config_t *config )
{
    if ( config )
    {
        config->default_write_data = 0;
        config->sck = (pin_name_t)0xFFFFFFFF;
        config->miso = (pin_name_t)0xFFFFFFFF;
        config->mosi = (pin_name_t)0xFFFFFFFF;
        config->speed = 100000;
        config->mode = SPI_MASTER_MODE_DEFAULT;
    }
}

err_t spi_master_open( spi_master_t *obj, spi_master_config_t *config )
{
    spi_master_config_t *p_config = &obj->config;
    memcpy( p_config, config, sizeof( spi_master_config_t ) );
    return _acquire( obj, true );
}

void spi_master_select_device( pin_name_t chip_select )
{
    #if DRV_TO_HAL
    hal_spi_master_select_device( chip_select );
    #else
    hal_gpio_pin_t struct_cs;
    hal_gpio_configure_pin( &struct_cs, chip_select, HAL_GPIO_DIGITAL_OUTPUT );

    if ( chip_select != HAL_PIN_NC )
    {
        if ( hal_spi_master_chip_select_polarity == HAL_SPI_MASTER_CHIP_SELECT_POLARITY_ACTIVE_HIGH )
        {
            hal_gpio_set_pin_output( &struct_cs );
        } else {
            hal_gpio_clear_pin_output( &struct_cs );
        }
    }
    #endif
}

void spi_master_deselect_device( pin_name_t chip_select )
{
    #if DRV_TO_HAL
    hal_spi_master_deselect_device( chip_select );
    #else
    hal_gpio_pin_t struct_cs;
    hal_gpio_configure_pin( &struct_cs, chip_select, HAL_GPIO_DIGITAL_OUTPUT );

    if ( chip_select != HAL_PIN_NC )
    {
        if ( hal_spi_master_chip_select_polarity == HAL_SPI_MASTER_CHIP_SELECT_POLARITY_ACTIVE_HIGH )
        {
            hal_gpio_clear_pin_output( &struct_cs );
        } else {
            hal_gpio_set_pin_output( &struct_cs );
        }
    }
    #endif
}

void spi_master_set_chip_select_polarity( spi_master_chip_select_polarity_t polarity )
{
    #if DRV_TO_HAL
    hal_spi_master_set_chip_select_polarity( polarity );
    #else
    if ( polarity == HAL_SPI_MASTER_CHIP_SELECT_POLARITY_ACTIVE_HIGH )
    {
        hal_spi_master_chip_select_polarity = HAL_SPI_MASTER_CHIP_SELECT_POLARITY_ACTIVE_HIGH;
    } else {
        hal_spi_master_chip_select_polarity = HAL_SPI_MASTER_CHIP_SELECT_POLARITY_ACTIVE_LOW;
    }
    #endif
}

err_t spi_master_set_speed( spi_master_t *obj, uint32_t speed )
{
    if ( _acquire( obj, false ) != ACQUIRE_FAIL )
    {
        obj->config.speed = speed;
        #if DRV_TO_HAL
        return hal_spi_master_set_speed( &obj->handle, &obj->config );
        #else
        hal_spi_master_handle_register_t *hal_handle = ( hal_spi_master_handle_register_t * )hal_is_handle_null( (handle_t *)&obj->handle );
        volatile err_t hal_status;

        if ( !hal_handle || !obj->config.speed )
        {
            return HAL_SPI_MASTER_ERROR;
        }

        hal_handle->init_state = false;

        hal_status = hal_ll_spi_master_set_speed( (handle_t *)&hal_handle, obj->config.speed );

        if ( hal_status == HAL_SPI_MASTER_MODULE_ERROR )
        {
            return HAL_SPI_MASTER_ERROR;
        } else {
            hal_handle->init_state = true;
            return HAL_SPI_MASTER_SUCCESS;
        }
        #endif
    } else {
        return SPI_MASTER_ERROR;
    }
}

err_t spi_master_set_mode( spi_master_t *obj, spi_master_mode_t mode )
{
    if ( _acquire( obj, false ) != ACQUIRE_FAIL )
    {
        obj->config.mode = mode;
        #if DRV_TO_HAL
        return hal_spi_master_set_mode( &obj->handle, &obj->config );
        #else
        hal_spi_master_handle_register_t *hal_handle = ( hal_spi_master_handle_register_t* )hal_is_handle_null( (handle_t *)&obj->handle );
        volatile err_t hal_status;

        if ( !hal_handle )
        {
            return HAL_SPI_MASTER_ERROR;
        }

        if ( ( HAL_SPI_MASTER_MODE_3 < obj->config.mode ) || ( obj->config.mode < HAL_SPI_MASTER_MODE_0 ) )
        {
            return HAL_SPI_MASTER_ERROR;
        }

        hal_handle->init_state = false;

        hal_status = hal_ll_spi_master_set_mode( (handle_t *)&hal_handle, (hal_ll_spi_master_mode_t)obj->config.mode );

        if ( hal_status == HAL_SPI_MASTER_MODULE_ERROR )
        {
            return HAL_SPI_MASTER_ERROR;
        } else {
            hal_handle->init_state = true;
            return HAL_SPI_MASTER_SUCCESS;
        }
        #endif
    } else {
        return SPI_MASTER_ERROR;
    }
}

err_t spi_master_set_default_write_data( spi_master_t *obj, uint8_t default_write_data )
{
    if ( _acquire( obj, false ) != ACQUIRE_FAIL )
    {
        obj->config.default_write_data = default_write_data;
        #if DRV_TO_HAL
        hal_spi_master_set_default_write_data( &obj->handle, &obj->config );
        #else
        handle_t hal_handle = hal_is_handle_null( (handle_t *)&obj->handle );

        if ( hal_handle )
        {
            hal_ll_spi_master_set_default_write_data( &hal_handle, obj->config.default_write_data );
        }
        #endif
        return SPI_MASTER_SUCCESS;
    } else {
        return SPI_MASTER_ERROR;
    }
}

err_t spi_master_write( spi_master_t *obj, uint8_t * __generic_ptr write_data_buffer, size_t write_data_length )
{
    if ( _acquire( obj, false ) != ACQUIRE_FAIL )
    {
        #if DRV_TO_HAL
        return  hal_spi_master_write( &obj->handle, write_data_buffer, write_data_length );
        #else
        hal_spi_master_handle_register_t *hal_handle = ( hal_spi_master_handle_register_t* )hal_is_handle_null( (handle_t *)&obj->handle );
        err_t hal_status = HAL_SPI_MASTER_SUCCESS;

        if ( !hal_handle )
        {
            return HAL_SPI_MASTER_ERROR;
        }

        if ( !write_data_buffer )
        {
            return HAL_SPI_MASTER_ERROR;
        }

        if ( write_data_length <= 0 )
        {
            return HAL_SPI_MASTER_ERROR;
        }

        if ( hal_handle->init_state == false )
        {
            hal_status = hal_ll_module_configure_spi( (handle_t *)&hal_handle );
        }

        if ( hal_status != HAL_SPI_MASTER_SUCCESS )
        {
            return HAL_SPI_MASTER_ERROR;
        } else {
            hal_handle->init_state = true;
        }

        hal_status = hal_ll_spi_master_write( (handle_t *)&hal_handle, write_data_buffer, write_data_length );

        if ( hal_status == HAL_SPI_MASTER_MODULE_ERROR )
        {
            return HAL_SPI_MASTER_ERROR;
        } else {
            return HAL_SPI_MASTER_SUCCESS;
        }
        #endif
    } else {
        return SPI_MASTER_ERROR;
    }
}

err_t spi_master_read( spi_master_t *obj, uint8_t *read_data_buffer, size_t read_data_length )
{
    if ( _acquire( obj, false ) != ACQUIRE_FAIL )
    {
        #if DRV_TO_HAL
        return hal_spi_master_read( &obj->handle, read_data_buffer, read_data_length );
        #else
        hal_spi_master_handle_register_t *hal_handle = ( hal_spi_master_handle_register_t* )hal_is_handle_null( (handle_t *)&obj->handle );
        err_t hal_status = HAL_SPI_MASTER_SUCCESS;

        if ( !hal_handle )
        {
            return HAL_SPI_MASTER_ERROR;
        }

        if ( !read_data_buffer )
        {
            return HAL_SPI_MASTER_ERROR;
        }

        if ( read_data_length <= 0 )
        {
            return HAL_SPI_MASTER_ERROR;
        }

        if ( hal_handle->init_state == false )
        {
            hal_status = hal_ll_module_configure_spi( (handle_t *)&hal_handle );
        }

        if( hal_status != HAL_SPI_MASTER_SUCCESS )
        {
            return HAL_SPI_MASTER_ERROR;
        } else {
            hal_handle->init_state = true;
        }

        hal_status = hal_ll_spi_master_read( (handle_t *)&hal_handle, read_data_buffer, read_data_length );

        if ( hal_status == HAL_SPI_MASTER_MODULE_ERROR )
        {
            return HAL_SPI_MASTER_ERROR;
        } else {
            return HAL_SPI_MASTER_SUCCESS;
        }
        #endif
    } else {
        return SPI_MASTER_ERROR;
    }
}

err_t spi_master_write_then_read( spi_master_t *obj, uint8_t *write_data_buffer,
                                                      size_t length_write_data,
                                                     uint8_t *read_data_buffer,
                                                      size_t length_read_data )
{
    if ( _acquire( obj, false ) != ACQUIRE_FAIL )
    {
        #if DRV_TO_HAL
        return hal_spi_master_write_then_read( &obj->handle, write_data_buffer,
                                                             length_write_data,
                                                             read_data_buffer,
                                                             length_read_data );
        #else
        hal_spi_master_handle_register_t *hal_handle = ( hal_spi_master_handle_register_t* )hal_is_handle_null( (handle_t *)&obj->handle );
        err_t hal_status = HAL_SPI_MASTER_SUCCESS;

        if ( !hal_handle )
        {
            return HAL_SPI_MASTER_ERROR;
        }

        if ( !write_data_buffer || !read_data_buffer )
        {
            return HAL_SPI_MASTER_ERROR;
        }

        if ( (length_write_data <= 0) || (length_read_data <= 0) )
        {
            return HAL_SPI_MASTER_ERROR;
        }

        if ( hal_handle->init_state == false )
        {
            hal_status = hal_ll_module_configure_spi( (handle_t *)&hal_handle );
        }

        if( hal_status != HAL_SPI_MASTER_SUCCESS )
        {
            return HAL_SPI_MASTER_ERROR;
        } else {
            hal_handle->init_state = true;
        }

        hal_status =  hal_ll_spi_master_write_then_read( (handle_t *)&hal_handle, write_data_buffer,
                                                                    length_write_data,
                                                                    read_data_buffer,
                                                                    length_read_data );

        if (hal_status == HAL_SPI_MASTER_MODULE_ERROR)
        {
            return HAL_SPI_MASTER_ERROR;
        } else {
            return HAL_SPI_MASTER_SUCCESS;
        }
        #endif
    } else {
        return SPI_MASTER_ERROR;
    }
}

err_t spi_master_transfer( spi_master_t *obj, uint8_t *write_data_buffer,
                                              uint8_t *read_data_buffer,
                                              size_t data_length ) {
    if ( _acquire( obj, false ) != ACQUIRE_FAIL )
        {
            #if DRV_TO_HAL
            return hal_spi_master_transfer( &obj->handle, write_data_buffer,
                                                          read_data_buffer,
                                                          data_length );
        #else
        hal_spi_master_handle_register_t *hal_handle = ( hal_spi_master_handle_register_t* )hal_is_handle_null( (handle_t *)&obj->handle );
        err_t hal_status = HAL_SPI_MASTER_SUCCESS;

        if ( !hal_handle )
        {
            return HAL_SPI_MASTER_ERROR;
        }

        if ( !write_data_buffer || !read_data_buffer )
        {
            return HAL_SPI_MASTER_ERROR;
        }

        if ( data_length <= 0 )
        {
            return HAL_SPI_MASTER_ERROR;
        }

        if ( hal_handle->init_state == false )
        {
            hal_status = hal_ll_module_configure_spi( (handle_t *)&hal_handle );
        }

        if( hal_status != HAL_SPI_MASTER_SUCCESS )
        {
            return HAL_SPI_MASTER_ERROR;
        } else {
            hal_handle->init_state = true;
        }

        hal_status =  hal_ll_spi_master_transfer( (handle_t *)&hal_handle, write_data_buffer,
                                                                           read_data_buffer,
                                                                           data_length );

        if (hal_status == HAL_SPI_MASTER_MODULE_ERROR)
        {
            return HAL_SPI_MASTER_ERROR;
        } else {
            return HAL_SPI_MASTER_SUCCESS;
        }
        #endif
    } else {
        return SPI_MASTER_ERROR;
    }
}

err_t spi_master_close( spi_master_t *obj )
{
    if ( SPI_MASTER_SUCCESS == hal_spi_master_close( &obj->handle ) )
    {
        obj->handle = NULL;
        _owner = NULL;
        return SPI_MASTER_SUCCESS;
    } else {
        return SPI_MASTER_ERROR;
    }
}

// ------------------------------------------------------------------------- END
