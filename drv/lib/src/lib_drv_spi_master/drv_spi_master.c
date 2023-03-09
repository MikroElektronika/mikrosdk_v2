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
 * @file  drv_spi_master.c
 * @brief SPI master driver implementation.
 */

#include "drv_spi_master.h"

static spi_master_t *_owner = NULL;

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
    config->default_write_data = 0;
    config->sck = 0xFFFFFFFF;
    config->miso = 0xFFFFFFFF;
    config->mosi = 0xFFFFFFFF;
    config->speed = 100000;
    config->mode = SPI_MASTER_MODE_DEFAULT;
}

err_t spi_master_open( spi_master_t *obj, spi_master_config_t *config )
{
    spi_master_config_t *p_config = &obj->config;
    memcpy( p_config, config, sizeof( spi_master_config_t ) );
    return _acquire( obj, true );
}

void spi_master_select_device( pin_name_t chip_select )
{
    hal_spi_master_select_device( chip_select );
}

void spi_master_deselect_device( pin_name_t chip_select )
{
    hal_spi_master_deselect_device( chip_select );
}

void spi_master_set_chip_select_polarity( spi_master_chip_select_polarity_t polarity )
{
    hal_spi_master_set_chip_select_polarity( polarity );
}

err_t spi_master_set_speed( spi_master_t *obj, uint32_t speed )
{
    if ( _acquire( obj, false ) != ACQUIRE_FAIL )
    {
        obj->config.speed = speed;
        return hal_spi_master_set_speed( &obj->handle, &obj->config );
    } else {
        return SPI_MASTER_ERROR;
    }
}

err_t spi_master_set_mode( spi_master_t *obj, spi_master_mode_t mode )
{
    if ( _acquire( obj, false ) != ACQUIRE_FAIL )
    {
        obj->config.mode = mode;
        return hal_spi_master_set_mode( &obj->handle, &obj->config );
    } else {
        return SPI_MASTER_ERROR;
    }
}

err_t spi_master_set_default_write_data( spi_master_t *obj, uint8_t default_write_data )
{
    if ( _acquire( obj, false ) != ACQUIRE_FAIL )
    {
        obj->config.default_write_data = default_write_data;
        hal_spi_master_set_default_write_data( &obj->handle, &obj->config );
        return SPI_MASTER_SUCCESS;
    } else {
        return SPI_MASTER_ERROR;
    }
}

err_t spi_master_write( spi_master_t *obj, uint8_t *write_data_buffer, size_t write_data_length )
{
    if ( _acquire( obj, false ) != ACQUIRE_FAIL )
    {
        return  hal_spi_master_write( &obj->handle, write_data_buffer, write_data_length );
    } else {
        return SPI_MASTER_ERROR;
    }
}

err_t spi_master_read( spi_master_t *obj, uint8_t *read_data_buffer, size_t read_data_length )
{
    if ( _acquire( obj, false ) != ACQUIRE_FAIL )
    {
        return hal_spi_master_read( &obj->handle, read_data_buffer, read_data_length );
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
        return hal_spi_master_write_then_read( &obj->handle, write_data_buffer,
                                                             length_write_data,
                                                             read_data_buffer,
                                                             length_read_data );
     } else {
        return SPI_MASTER_ERROR;
    }
}

void spi_master_close( spi_master_t *obj )
{
    err_t status;

    status = hal_spi_master_close( &obj->handle );

    if ( status == SPI_MASTER_SUCCESS )
    {
        obj->handle = NULL;
        _owner = NULL;
    }
}

// ------------------------------------------------------------------------- END
