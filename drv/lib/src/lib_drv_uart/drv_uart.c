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
 * @file  drv_uart.c
 * @brief UART driver implementation.
 */

#include "drv_uart.h"

static uart_t *_owner = NULL;

#if !DRV_TO_HAL
extern hal_uart_handle_register_t DRV_TO_HAL_PREFIXED(uart, hal_module_state)[ UART_MODULE_COUNT ];

extern const uint8_t DRV_TO_HAL_PREFIXED(uart, module_state_count);

static handle_t hal_is_handle_null( handle_t *hal_module_handle )
{
    uint8_t hal_module_state_count = DRV_TO_HAL_PREFIXED(uart, module_state_count);

    #ifdef __XC8__
    uint32_t tmp_addr;
    #endif

    while( hal_module_state_count-- )
    {
        #ifdef __XC8__
        tmp_addr = ( handle_t )&DRV_TO_HAL_PREFIXED(uart, hal_module_state)[ hal_module_state_count ].hal_uart_handle;
        if ( *hal_module_handle == tmp_addr )
        {
            return tmp_addr;
        }
        #else
        if ( *hal_module_handle == ( handle_t )&DRV_TO_HAL_PREFIXED(uart, hal_module_state)[ hal_module_state_count ].hal_uart_handle )
        {
            return ( handle_t )&DRV_TO_HAL_PREFIXED(uart, hal_module_state)[ hal_module_state_count ].hal_uart_handle;
        }
        #endif
    }

    return ACQUIRE_SUCCESS;
}
#endif

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
    if ( config )
    {
        config->tx_pin = (pin_name_t)0xFFFFFFFF;
        config->rx_pin = (pin_name_t)0xFFFFFFFF;

        config->baud = 115200;
        config->data_bits = UART_DATA_BITS_DEFAULT;
        config->parity = UART_PARITY_DEFAULT;
        config->stop_bits = UART_STOP_BITS_DEFAULT;

        memset( &config->tx_buf, 0x00, sizeof( ring_buf8_t ) );
        memset( &config->rx_buf, 0x00, sizeof( ring_buf8_t ) );

        config->tx_ring_size = 0;
        config->rx_ring_size = 0;
    }
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
        #if DRV_TO_HAL
        return hal_uart_set_baud( &obj->handle, &obj->config );
        #else
        hal_uart_handle_register_t *hal_handle = ( hal_uart_handle_register_t * )hal_is_handle_null( (handle_t *)&obj->handle );
        err_t hal_status;

        if ( !hal_handle )
            return HAL_UART_ERROR;

        if ( !obj->config.baud )
            return HAL_UART_ERROR;

        hal_handle->init_state = false;

        hal_status = hal_ll_uart_set_baud( (handle_t *)&hal_handle, obj->config.baud );

        if ( hal_status == HAL_UART_WRONG_PINS || hal_status == HAL_UART_MODULE_ERROR )
        {
            return HAL_UART_ERROR;
        } else {
            hal_handle->init_state = true;
            return HAL_UART_SUCCESS;
        }
        #endif
    } else {
        return UART_ERROR;
    }
}

err_t uart_set_parity( uart_t *obj, uart_parity_t parity )
{
    if ( _acquire( obj, false ) != ACQUIRE_FAIL )
    {
        obj->config.parity = parity;
        #if DRV_TO_HAL
        return hal_uart_set_parity( &obj->handle, &obj->config );
        #else
        hal_uart_handle_register_t *hal_handle = ( hal_uart_handle_register_t * )hal_is_handle_null( (handle_t *)&obj->handle );
        err_t hal_status;

        if ( !hal_handle )
            return HAL_UART_ERROR;

        if ( (obj->config.parity < HAL_UART_PARITY_NONE) || (obj->config.parity > HAL_UART_PARITY_ODD) )
            return HAL_UART_ERROR;

        hal_handle->init_state = false;

        hal_status = hal_ll_uart_set_parity( (handle_t *)&hal_handle, (hal_ll_uart_parity_t)obj->config.parity );

        if ( hal_status == HAL_UART_WRONG_PINS || hal_status == HAL_UART_MODULE_ERROR )
        {
            return HAL_UART_ERROR;
        } else {
            hal_handle->init_state = true;
            return HAL_UART_SUCCESS;
        }
        #endif
    } else {
        return UART_ERROR;
    }
}

err_t uart_set_stop_bits( uart_t *obj, uart_stop_bits_t stop )
{
    if ( _acquire( obj, false ) != ACQUIRE_FAIL )
    {
        obj->config.stop_bits = stop;
        #if DRV_TO_HAL
        return hal_uart_set_stop_bits( &obj->handle, &obj->config );
        #else
        hal_uart_handle_register_t *hal_handle = ( hal_uart_handle_register_t * )hal_is_handle_null( (handle_t *)&obj->handle );
        err_t hal_status;

        if ( !hal_handle )
            return HAL_UART_ERROR;

        if ( (obj->config.stop_bits < HAL_UART_STOP_BITS_HALF) || (obj->config.stop_bits > HAL_UART_STOP_BITS_TWO) )
            return HAL_UART_ERROR;

        hal_handle->init_state = false;

        hal_status = hal_ll_uart_set_stop_bits( (handle_t *)&hal_handle, (hal_ll_uart_stop_bits_t)obj->config.stop_bits );

        if ( hal_status == HAL_UART_WRONG_PINS || hal_status == HAL_UART_MODULE_ERROR )
        {
            return HAL_UART_ERROR;
        } else {
            hal_handle->init_state = true;
            return HAL_UART_SUCCESS;
        }
        #endif
    } else {
        return UART_ERROR;
    }
}

err_t uart_set_data_bits( uart_t *obj, uart_data_bits_t bits )
{
    if ( _acquire( obj, false ) != ACQUIRE_FAIL )
    {
        obj->config.data_bits = bits;
        #if DRV_TO_HAL
        return hal_uart_set_data_bits( &obj->handle, &obj->config );
        #else
        hal_uart_handle_register_t *hal_handle = ( hal_uart_handle_register_t * )hal_is_handle_null( (handle_t *)&obj->handle );
        err_t hal_status;

        if ( !hal_handle )
            return HAL_UART_ERROR;

        if ( (obj->config.data_bits < HAL_UART_DATA_BITS_7) || (obj->config.data_bits > HAL_UART_DATA_BITS_9) )
            return HAL_UART_ERROR;

        hal_handle->init_state = false;

        hal_status = hal_ll_uart_set_data_bits( (handle_t *)&hal_handle, (hal_ll_uart_data_bits_t)obj->config.data_bits );

        if ( hal_status == HAL_UART_WRONG_PINS || hal_status == HAL_UART_MODULE_ERROR )
        {
            return HAL_UART_ERROR;
        } else {
            hal_handle->init_state = true;
            return HAL_UART_SUCCESS;
        }
        #endif
    } else {
        return UART_ERROR;
    }
}

void uart_set_blocking( uart_t *obj, bool blocking )
{
    if( obj )
    {
        if ( obj->handle )
        {
            #if DRV_TO_HAL
            hal_uart_set_blocking( &obj->handle, blocking );
            #else
            hal_uart_t *hal_obj = ( hal_uart_t * ) &obj->handle;

            if ( hal_obj )
            {
                hal_obj->is_blocking = blocking;
            }
            #endif
        }
    }
}

err_t uart_write( uart_t *obj, uint8_t *buffer, size_t size )
{
    size_t data_written = 0;

    if ( _acquire( obj, false ) != ACQUIRE_FAIL )
    {
        #if DRV_TO_HAL
        data_written = hal_uart_write( &obj->handle, buffer, size );
        return data_written;
        #else
        hal_uart_handle_register_t *hal_handle = ( hal_uart_handle_register_t * )hal_is_handle_null( (handle_t *)&obj->handle );
        hal_uart_t *hal_obj = ( hal_uart_t * ) &obj->handle;
        ring_buf8_t *ring = &hal_obj->config.tx_buf;
        size_t data_written = 0;

        if ( !hal_handle )
        {
            return 0;
        }

        if ( size <= 0 )
            return 0;

        if ( !buffer )
        {
            return 0;
        }

        if ( hal_handle->init_state == false )
            hal_ll_module_configure_uart( (handle_t *)&hal_handle );

        while ( data_written < size )
        {
            if ( ring_buf8_is_full( ring ) )
            {
                if ( !hal_obj->is_blocking )
                {
                    break;
                }
                // Waits for interrupt handler to free some space up in tx buffer.
                do
                {
                    Delay_1ms();
                } while ( ring_buf8_is_full( ring ) );
            }

            hal_ll_core_disable_interrupts();
            ring_buf8_push( ring, buffer[ data_written++ ] );

            // Enable interrupt if there is any data to write from buffer.
            if ( !hal_obj->is_tx_irq_enabled && !ring_buf8_is_empty( ring ) )
            {
                hal_ll_uart_irq_enable( (handle_t *)&hal_handle, (hal_ll_uart_irq_t)HAL_UART_IRQ_TX );
                hal_obj->is_tx_irq_enabled = true;
            }
            hal_ll_core_enable_interrupts();
        }

        return data_written;
        #endif
    } else {
        return UART_ERROR;
    }
}

err_t uart_print( uart_t *obj, char *text )
{
    size_t data_written = 0;

    if ( _acquire( obj, false ) != ACQUIRE_FAIL )
    {
        #if DRV_TO_HAL
        data_written = hal_uart_print( &obj->handle, text );
        return data_written;
        #else
        size_t data_written = 0;

        if ( !obj )
        {
            return 0;
        }

        if ( !text )
        {
            return 0;
        }

        while ( text[ data_written ] != '\0' )
        {
            if ( hal_uart_write( (handle_t *)obj, (uint8_t *)&text[ data_written ], 1 ) != 1 )
                return data_written;
            data_written++;
        }

        return data_written;
        #endif
    } else {
        return UART_ERROR;
    }
}

err_t uart_println( uart_t *obj, char *text )
{
    size_t data_written = 0;

    if ( _acquire( obj, false ) != ACQUIRE_FAIL )
    {
        #if DRV_TO_HAL
        data_written = hal_uart_println( &obj->handle, text );
        return data_written;
        #else
        if ( !obj )
        {
            return 0;
        }

        size_t data_written = hal_uart_print( (handle_t *)obj, text );

        if ( data_written < 0 )
            return 0;

        return data_written + hal_uart_print( (handle_t *)obj, "\r\n" );
        #endif
    } else {
        return UART_ERROR;
    }
}

err_t uart_read( uart_t *obj, uint8_t *buffer, size_t size )
{
    size_t data_read = 0;

    if ( _acquire( obj, false ) != ACQUIRE_FAIL )
    {
        #if DRV_TO_HAL
        data_read = hal_uart_read( &obj->handle, buffer, size );
        return data_read;
        #else
        hal_uart_handle_register_t *hal_handle = ( hal_uart_handle_register_t * )hal_is_handle_null( (handle_t *)&obj->handle );
        hal_uart_t *hal_obj = ( hal_uart_t * ) &obj->handle;
        ring_buf8_t *ring = &hal_obj->config.rx_buf;
        size_t data_read = 0;

        if ( !hal_handle )
        {
            return 0;
        }

        if ( size <= 0 )
        {
            return 0;
        }

        if ( !buffer )
        {
            return 0;
        }

        if ( hal_handle->init_state == false )
            hal_ll_module_configure_uart( (handle_t *)&hal_handle );

        // Enable module interrupt, if it's disabled
        if ( !hal_obj->is_rx_irq_enabled )
        {
            hal_ll_uart_irq_enable( (handle_t *)&hal_handle, (hal_ll_uart_irq_t)HAL_UART_IRQ_RX );
            hal_obj->is_rx_irq_enabled = true;
        }
        // Wait for some data to be received to the buffer if in blocking mode.
        while ( ring_buf8_is_empty( ring ) )
        {
            if ( !hal_obj->is_blocking )
            {
                return 0;
            }
            Delay_1ms();
        }

        while ( ( size > 0 ) && !ring_buf8_is_empty( ring ) )
        {
            uint8_t data_byte;

            hal_ll_core_disable_interrupts();
            data_byte = ring_buf8_pop( ring );

            if ( !hal_obj->is_rx_irq_enabled && !ring_buf8_is_full( ring ) )
            {
                hal_ll_uart_irq_enable( (handle_t *)&hal_handle, (hal_ll_uart_irq_t)HAL_UART_IRQ_RX );
                hal_obj->is_rx_irq_enabled = true;
            }
            hal_ll_core_enable_interrupts();

            buffer[ data_read++ ] = data_byte;
            size--;
        }

        return data_read;
        #endif
    } else {
        return UART_ERROR;
    }
}

size_t uart_bytes_available( uart_t *obj )
{
    return hal_uart_bytes_available( (hal_uart_t *)obj );
}

void uart_clear( uart_t *obj )
{
    hal_uart_clear( (hal_uart_t *)obj );
}

err_t uart_close( uart_t *obj )
{
    if ( UART_SUCCESS == hal_uart_close( &obj->handle ) )
    {
        obj->handle = 0;
        _owner = NULL;
        return UART_SUCCESS;
    } else {
        return UART_ERROR;
    }
}

// ------------------------------------------------------------------------- END
