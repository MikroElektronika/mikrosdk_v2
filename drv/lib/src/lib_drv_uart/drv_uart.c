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
 * @file  drv_uart.c
 * @brief UART driver implementation.
 */

#include "drv_uart.h"

static uart_t *_owner = NULL;

static err_t _acquire( uart_t *obj, bool obj_open_state )
{
    err_t status = ACQUIRE_SUCCESS;

    if ( obj_open_state == true && _owner == obj )
    {
        return ACQUIRE_FAIL;
    }

    if ( _owner != obj )
    {
        status = hal_uart_open( &obj->handle, obj_open_state );

        if ( status != ACQUIRE_FAIL )
            _owner = obj;
    }

    return status;
}

void uart_configure_default( uart_config_t *config )
{
    config->tx_pin = 0xFFFFFFFF;
    config->rx_pin = 0xFFFFFFFF;

    config->baud = 115200;
    config->data_bits = UART_DATA_BITS_DEFAULT;
    config->parity = UART_PARITY_DEFAULT;
    config->stop_bits = UART_STOP_BITS_DEFAULT;

    memset( &config->tx_buf, 0x00, sizeof( ring_buf8_t ) );
    memset( &config->rx_buf, 0x00, sizeof( ring_buf8_t ) );

    config->tx_ring_size = 0;
    config->rx_ring_size = 0;
}

err_t uart_open( uart_t *obj, uart_config_t *config )
{
    uart_config_t *p_config = &obj->config;
    memcpy( p_config, config, sizeof( uart_config_t ) );

    return _acquire( obj, true );
}

err_t uart_set_baud( uart_t *obj, uint32_t baud )
{
    if ( _acquire( obj, false ) != ACQUIRE_FAIL )
    {
        obj->config.baud = baud;
        return hal_uart_set_baud( &obj->handle, &obj->config );
    } else {
        return UART_ERROR;
    }
}

err_t uart_set_parity( uart_t *obj, uart_parity_t parity )
{
    if ( _acquire( obj, false ) != ACQUIRE_FAIL )
    {
        obj->config.parity = parity;
        return hal_uart_set_parity( &obj->handle, &obj->config );
    } else {
        return UART_ERROR;
    }
}

err_t uart_set_stop_bits( uart_t *obj, uart_stop_bits_t stop )
{
    if ( _acquire( obj, false ) != ACQUIRE_FAIL )
    {
        obj->config.stop_bits = stop;
        return hal_uart_set_stop_bits( &obj->handle, &obj->config );
    } else {
        return UART_ERROR;
    }
}

err_t uart_set_data_bits( uart_t *obj, uart_data_bits_t bits )
{
    if ( _acquire( obj, false ) != ACQUIRE_FAIL )
    {
        obj->config.data_bits = bits;
        return hal_uart_set_data_bits( &obj->handle, &obj->config );
    } else {
        return UART_ERROR;
    }
}

void uart_set_blocking( uart_t *obj, bool blocking )
{
    hal_uart_set_blocking( &obj->handle, blocking );
}

err_t uart_write( uart_t *obj, uint8_t *buffer, size_t size )
{
    size_t data_written = 0;

    if ( _acquire( obj, false ) != ACQUIRE_FAIL )
    {
        data_written = hal_uart_write( &obj->handle, buffer, size );
        return data_written;
    } else {
        return UART_ERROR;
    }
}

err_t uart_read( uart_t *obj, uint8_t *buffer, size_t size )
{
    size_t data_read = 0;

    if ( _acquire( obj, false ) != ACQUIRE_FAIL )
    {
        data_read = hal_uart_read( &obj->handle, buffer, size );
        return data_read;
    } else {
        return UART_ERROR;
    }
}

err_t uart_print( uart_t *obj, char *text )
{
    size_t data_written = 0;

    if ( _acquire( obj, false ) != ACQUIRE_FAIL )
    {
        data_written = hal_uart_print( &obj->handle, text );
        return data_written;
    } else {
        return UART_ERROR;
    }
}

err_t uart_println( uart_t *obj, char *text )
{
    size_t data_written = 0;

    if ( _acquire( obj, false ) != ACQUIRE_FAIL )
    {
        data_written = hal_uart_println( &obj->handle, text );
        return data_written;
    } else {
        return UART_ERROR;
    }
}

size_t uart_bytes_available( uart_t *obj )
{
    return hal_uart_bytes_available( obj );
}

void uart_clear( uart_t *obj )
{
    hal_uart_clear( obj );
}

void uart_close( uart_t *obj )
{
    err_t drv_status;

    drv_status = hal_uart_close( &obj->handle );

    if ( drv_status == UART_SUCCESS )
    {
        obj->handle = NULL;
        _owner = NULL;
    }
}

// ------------------------------------------------------------------------- END
