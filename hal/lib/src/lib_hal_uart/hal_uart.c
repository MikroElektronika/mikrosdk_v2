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
 * @file  hal_uart.c
 * @brief This file contains all the functions prototypes for the UART library.
 */

#include "hal_uart.h"
#include "hal_ll_uart.h"
#include "hal_ll_core.h"
#include "delays.h"

#ifdef __XC8__
#include <assert.h>
#endif

static handle_t *hal_owner = NULL;

void hal_uart_irq_handler( handle_t obj, hal_uart_irq_t event );

DRV_TO_HAL_STATIC hal_uart_handle_register_t DRV_TO_HAL_PREFIXED(uart, hal_module_state)[ UART_MODULE_COUNT ];

DRV_TO_HAL_STATIC const uint8_t DRV_TO_HAL_PREFIXED(uart, module_state_count) = sizeof( DRV_TO_HAL_PREFIXED(uart, hal_module_state) ) / ( sizeof( hal_uart_handle_register_t ) );

#ifdef __XC8__
static uint8_t **rx_ring_address[ UART_MODULE_COUNT ], **tx_ring_address[ UART_MODULE_COUNT ];

static handle_t hal_fetch_module_id( handle_t *hal_module_handle )
{
    uint8_t hal_module_state_count = DRV_TO_HAL_PREFIXED(uart, module_state_count);
    uint32_t tmp_addr;

    while( hal_module_state_count-- )
    {
        tmp_addr = ( handle_t )&(DRV_TO_HAL_PREFIXED(uart, hal_module_state)[ hal_module_state_count ].hal_uart_handle);
        if ( *hal_module_handle == tmp_addr )
        {
            return hal_module_state_count;
        }
    }

    return ACQUIRE_FAIL;
}
#endif

static handle_t hal_is_handle_null( handle_t *hal_module_handle )
{
    uint8_t hal_module_state_count = DRV_TO_HAL_PREFIXED(uart, module_state_count);

    #ifdef __XC8__
    uint32_t tmp_addr;
    #endif

    while( hal_module_state_count-- )
    {
        #ifdef __XC8__
        tmp_addr = ( handle_t )&(DRV_TO_HAL_PREFIXED(uart, hal_module_state)[ hal_module_state_count ].hal_uart_handle);
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

void hal_uart_configure_default( hal_uart_config_t *config )
{
    if ( config )
    {
        config->tx_pin = HAL_PIN_NC;
        config->rx_pin = HAL_PIN_NC;

        config->baud = 115200;
        config->data_bits = HAL_UART_DATA_BITS_DEFAULT;
        config->parity = HAL_UART_PARITY_DEFAULT;
        config->stop_bits = HAL_UART_STOP_BITS_DEFAULT;

        memset( &config->tx_buf, 0x00, sizeof( ring_buf8_t ) );
        memset( &config->rx_buf, 0x00, sizeof( ring_buf8_t ) );

        config->tx_ring_size = 0;
        config->rx_ring_size = 0;
    }
}

err_t hal_uart_open( handle_t *handle, bool hal_obj_open_state )
{
    handle_t handle_ll;
    uint8_t hal_module_id;
    hal_uart_t *hal_obj = ( hal_uart_t * )handle;
    err_t hal_status = sizeof( hal_uart_config_t );
    uint8_t hal_module_state_count = DRV_TO_HAL_PREFIXED(uart, module_state_count);

    #ifdef __XC8__
    uint32_t tmp_addr;
    #endif

    if ( !handle )
    {
        return ACQUIRE_FAIL;
    }

    if ( !hal_obj->rx_ring_buffer || !hal_obj->tx_ring_buffer )
    {
        return ACQUIRE_FAIL;
    }

    if ( !hal_obj->config.rx_ring_size || !hal_obj->config.rx_ring_size )
    {
        return ACQUIRE_FAIL;
    }

    if ( hal_obj_open_state == true )
    {
        if ( hal_is_handle_null( handle ) != ACQUIRE_SUCCESS )
            return ACQUIRE_FAIL;
    }

    if ( hal_obj->is_interrupt )
        if ( !hal_ll_core_implemented() )
            return ACQUIRE_FAIL;

    if ( hal_owner != handle )
    {
        while ( hal_module_state_count-- ) {
            if ( DRV_TO_HAL_PREFIXED(uart, hal_module_state)[ hal_module_state_count ].drv_uart_handle == handle ) {
                if ( hal_obj->is_interrupt ) {
                    hal_obj->is_tx_irq_enabled = false;
                    hal_obj->is_rx_irq_enabled = false;
                }
                hal_owner = handle;
                return ACQUIRE_SUCCESS;
            }
        }

        hal_status = hal_ll_uart_register_handle( hal_obj->config.tx_pin, hal_obj->config.rx_pin,
                                                  &DRV_TO_HAL_PREFIXED(uart, hal_module_state), &hal_module_id );

        #ifdef __XC8__
        rx_ring_address[hal_module_id] = &hal_obj->rx_ring_buffer;
        tx_ring_address[hal_module_id] = &hal_obj->tx_ring_buffer;
        #endif

        if ( hal_status == ACQUIRE_SUCCESS )
        {
            DRV_TO_HAL_PREFIXED(uart, hal_module_state)[ hal_module_id ].drv_uart_handle = handle;

            hal_obj->is_tx_irq_enabled = false;
            hal_obj->is_rx_irq_enabled = false;

            #ifdef __XC8__
            tmp_addr = ( handle_t )&(DRV_TO_HAL_PREFIXED(uart, hal_module_state)[ hal_module_id ].hal_uart_handle);
            *handle = tmp_addr;
            #else
            handle_t handle_address = &DRV_TO_HAL_PREFIXED(uart, hal_module_state)[hal_module_id].hal_uart_handle;
            *handle = handle_address;
            #endif

            handle_ll = hal_is_handle_null( handle );

            while( !ring_buf8_is_empty(&hal_obj->config.tx_buf) );
            while( !ring_buf8_is_empty(&hal_obj->config.rx_buf) );

            ring_buf8_init( &hal_obj->config.rx_buf, hal_obj->rx_ring_buffer,
                            hal_obj->config.rx_ring_size );
            ring_buf8_init( &hal_obj->config.tx_buf, hal_obj->tx_ring_buffer,
                            hal_obj->config.tx_ring_size );

            if ( hal_obj->is_interrupt ) {
                hal_ll_uart_register_irq_handler( &handle_ll, hal_uart_irq_handler, ( handle_t )hal_obj );
                hal_ll_core_enable_interrupts();
            }

            // Set HAL layer owner
            hal_owner = handle;
            return ACQUIRE_INIT;
        } else {
            *handle = 0;
            return ACQUIRE_FAIL;
        }
    } else {
        return ACQUIRE_SUCCESS;
    }
}

err_t hal_uart_set_baud( handle_t *handle, hal_uart_config_t *config )
{
    hal_uart_handle_register_t *hal_handle = ( hal_uart_handle_register_t * )hal_is_handle_null( handle );
    err_t hal_status;

    if ( !hal_handle )
        return HAL_UART_ERROR;

    if ( !config->baud )
        return HAL_UART_ERROR;

    hal_handle->init_state = false;

    hal_status = hal_ll_uart_set_baud( &hal_handle, config->baud );

    if ( hal_status == HAL_UART_WRONG_PINS || hal_status == HAL_UART_MODULE_ERROR )
    {
        return HAL_UART_ERROR;
    } else {
        hal_handle->init_state = true;
        return HAL_UART_SUCCESS;
    }
}

err_t hal_uart_set_parity( handle_t *handle, hal_uart_config_t *config )
{
    hal_uart_handle_register_t *hal_handle = ( hal_uart_handle_register_t * )hal_is_handle_null( handle );
    err_t hal_status;

    if ( !hal_handle )
        return HAL_UART_ERROR;

    if ( (config->parity < HAL_UART_PARITY_NONE) || (config->parity > HAL_UART_PARITY_ODD) )
        return HAL_UART_ERROR;

    hal_handle->init_state = false;

    hal_status = hal_ll_uart_set_parity( &hal_handle, config->parity );

    if ( hal_status == HAL_UART_WRONG_PINS || hal_status == HAL_UART_MODULE_ERROR )
    {
        return HAL_UART_ERROR;
    } else {
        hal_handle->init_state = true;
        return HAL_UART_SUCCESS;
    }
}

err_t hal_uart_set_stop_bits( handle_t *handle, hal_uart_config_t *config )
{
    hal_uart_handle_register_t *hal_handle = ( hal_uart_handle_register_t * )hal_is_handle_null( handle );
    err_t hal_status;

    if ( !hal_handle )
        return HAL_UART_ERROR;

    if ( (config->stop_bits < HAL_UART_STOP_BITS_HALF) || (config->stop_bits > HAL_UART_STOP_BITS_TWO) )
        return HAL_UART_ERROR;

    hal_handle->init_state = false;

    hal_status = hal_ll_uart_set_stop_bits( &hal_handle, config->stop_bits );

    if ( hal_status == HAL_UART_WRONG_PINS || hal_status == HAL_UART_MODULE_ERROR )
    {
        return HAL_UART_ERROR;
    } else {
        hal_handle->init_state = true;
        return HAL_UART_SUCCESS;
    }
}

err_t hal_uart_set_data_bits( handle_t *handle, hal_uart_config_t *config )
{
    hal_uart_handle_register_t *hal_handle = ( hal_uart_handle_register_t * )hal_is_handle_null( handle );
    err_t hal_status;

    if ( !hal_handle )
        return HAL_UART_ERROR;

    if ( (config->data_bits < HAL_UART_DATA_BITS_7) || (config->data_bits > HAL_UART_DATA_BITS_9) )
        return HAL_UART_ERROR;

    hal_handle->init_state = false;

    hal_status = hal_ll_uart_set_data_bits( &hal_handle, config->data_bits );

    if ( hal_status == HAL_UART_WRONG_PINS || hal_status == HAL_UART_MODULE_ERROR )
    {
        return HAL_UART_ERROR;
    } else {
        hal_handle->init_state = true;
        return HAL_UART_SUCCESS;
    }
}

void hal_uart_set_blocking( handle_t *handle, bool blocking )
{
    hal_uart_t *hal_obj = ( hal_uart_t * ) handle;

    if ( hal_obj )
    {
        hal_obj->is_blocking = blocking;
    }
}

size_t hal_uart_write( handle_t *handle, uint8_t *buffer, size_t size )
{
    hal_uart_handle_register_t *hal_handle = ( hal_uart_handle_register_t * )hal_is_handle_null( handle );
    hal_uart_t *hal_obj = ( hal_uart_t * ) handle;
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
        hal_ll_module_configure_uart( &hal_handle );

    #ifdef __XC8__
    uint8_t module_id = hal_fetch_module_id(handle);
    assert(ACQUIRE_FAIL != module_id);
    #endif

    while ( data_written < size ) {
        if ( hal_obj->is_interrupt ) {
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
            #ifdef __XC8__
            if ( ring->size != ring->capacity ) {
                write_reg(*tx_ring_address[module_id] + ring->head, buffer[ data_written++ ]);
                ring->head = ( ring->head + 1 ) % ring->capacity;
                ring->size++;
            }
            #else
            ring_buf8_push( ring, buffer[ data_written++ ] );
            #endif

            // Enable interrupt if there is any data to write from buffer.
            if ( !hal_obj->is_tx_irq_enabled && !ring_buf8_is_empty( ring ) )
            {
                hal_ll_uart_irq_enable( &hal_handle, HAL_UART_IRQ_TX );
                hal_obj->is_tx_irq_enabled = true;
            }
            hal_ll_core_enable_interrupts();
        } else
            hal_ll_uart_write_polling( &hal_obj->handle, buffer[ data_written++ ] );
    }

    return data_written;
}

size_t hal_uart_read( handle_t *handle, uint8_t *buffer, size_t size )
{
    hal_uart_handle_register_t *hal_handle = ( hal_uart_handle_register_t * )hal_is_handle_null( handle );
    hal_uart_t *hal_obj = ( hal_uart_t * ) handle;
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
        hal_ll_module_configure_uart( &hal_handle );

    if ( hal_obj->is_interrupt ) {
        // Enable module interrupt, if it's disabled
        if ( !hal_obj->is_rx_irq_enabled )
        {
            hal_ll_uart_irq_enable( &hal_handle, HAL_UART_IRQ_RX );
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

        #ifdef __XC8__
        uint8_t module_id = hal_fetch_module_id(handle);
        assert(ACQUIRE_FAIL != module_id);
        #endif

        while ( ( size > 0 ) && !ring_buf8_is_empty( ring ) )
        {
            uint8_t data_byte;

            hal_ll_core_disable_interrupts();
            #ifdef __XC8__
            data_byte = read_reg(*rx_ring_address[module_id] + ring->tail);
            ring->tail = ( ring->tail + 1 ) % ring->capacity;
            ring->size--;
            #else
            data_byte = ring_buf8_pop( ring );
            #endif

            if ( !hal_obj->is_rx_irq_enabled && !ring_buf8_is_full( ring ) )
            {
                hal_ll_uart_irq_enable( &hal_handle, HAL_UART_IRQ_RX );
                hal_obj->is_rx_irq_enabled = true;
            }
            hal_ll_core_enable_interrupts();

            buffer[ data_read++ ] = data_byte;
            size--;
        }
    } else {
        uint8_t volatile rd_data;
  
        rd_data = hal_ll_uart_read_polling( &hal_obj->handle );   
        ring_buf8_push( &hal_obj->config.rx_buf, rd_data );
        while ( ( size > 0 ) && !ring_buf8_is_empty( ring ) )
        {
            uint8_t data_byte;

            data_byte = ring_buf8_pop( ring );

            buffer[ data_read++ ] = data_byte;
            size--;
        }
    }

    return data_read;
}

size_t hal_uart_print( handle_t *handle, char *text )
{
    size_t data_written = 0;

    if ( !handle )
    {
        return 0;
    }

    if ( !text )
    {
        return 0;
    }

    while ( text[ data_written ] != '\0' )
    {
        if ( hal_uart_write( handle, &text[ data_written ], 1 ) != 1 )
            return data_written;
        data_written++;
    }

    return data_written;
}

size_t hal_uart_println( handle_t *handle, char *text )
{
    if ( !handle )
    {
        return 0;
    }

    size_t data_written = hal_uart_print( handle, text );

    if ( data_written < 0 )
        return 0;

    return data_written + hal_uart_print( handle, "\r\n" );
}

#ifdef __XC8__
#pragma optimize none
#define volatile volatile
#else
#define volatile
#endif

void hal_uart_irq_handler( handle_t obj, hal_uart_irq_t event )
{
    hal_uart_t *hal_obj = ( hal_uart_t* )obj;
    #ifdef __XC8__
    ring_buf8_t * volatile ring;
    #endif

    // If RX interrupt triggered
    if ( event == HAL_UART_IRQ_RX )
    {
        uint8_t volatile rd_data;
        #ifdef __XC8__
        ring = &hal_obj->config.rx_buf;
        if ( ring_buf8_is_full( ring ) )
        #else
        if ( ring_buf8_is_full( &hal_obj->config.rx_buf ) )
        #endif
        {
            hal_ll_uart_irq_disable( &hal_obj->handle, HAL_UART_IRQ_RX );
            hal_obj->is_rx_irq_enabled = false;
            return;
        }

        rd_data = hal_ll_uart_read( &hal_obj->handle );
        #ifdef __XC8__
        uint8_t module_id_rx = hal_fetch_module_id(hal_obj);
        assert(ACQUIRE_FAIL != module_id_rx);
        if ( ring->size != ring->capacity ) {
            write_reg(*rx_ring_address[module_id_rx] + ring->head, rd_data);
            ring->head = ( ring->head + 1 ) % ring->capacity;
            ring->size++;
        }
        #else
        ring_buf8_push( &hal_obj->config.rx_buf, rd_data );
        #endif
    }

    // If TX interrupt triggered
    if ( event == HAL_UART_IRQ_TX )
    {
        uint8_t volatile wr_data;
        #ifdef __XC8__
        uint8_t module_id_tx = hal_fetch_module_id(hal_obj);
        assert(ACQUIRE_FAIL != module_id_tx);
        ring = &hal_obj->config.tx_buf;
        wr_data = read_reg(*tx_ring_address[module_id_tx] + ring->tail);
        ring->tail = ( ring->tail + 1 ) % ring->capacity;
        ring->size--;
        #else
        wr_data = ring_buf8_pop( &hal_obj->config.tx_buf );
        #endif

        hal_ll_uart_write( &hal_obj->handle, wr_data );

        #ifdef __XC8__
        if ( hal_obj->is_tx_irq_enabled && ring_buf8_is_empty( ring ) )
        #else
        if ( hal_obj->is_tx_irq_enabled && ring_buf8_is_empty( &hal_obj->config.tx_buf ) )
        #endif
        {
            hal_ll_uart_irq_disable( &hal_obj->handle, HAL_UART_IRQ_TX );
            hal_obj->is_tx_irq_enabled = false;
            return;
        }
    }
}

#ifdef __XC8__
#pragma optimize default
#endif

size_t hal_uart_bytes_available( hal_uart_t *hal_obj )
{
    if ( !hal_obj )
    {
        return 0;
    }

    if ( !hal_obj->handle )
    {
        return 0;
    }

    return ring_buf8_size( &hal_obj->config.rx_buf );
}

void hal_uart_clear( hal_uart_t *hal_obj )
{
    if ( hal_obj )
    {
        if ( hal_obj->handle )
        {
            ring_buf8_clear( &hal_obj->config.rx_buf );
            ring_buf8_clear( &hal_obj->config.tx_buf );
        }
    }
}

err_t hal_uart_close( handle_t *handle )
{
    hal_uart_handle_register_t *hal_handle = ( hal_uart_handle_register_t * )hal_is_handle_null( handle );

    if( hal_handle )
    {
        if ( hal_handle->hal_uart_handle )
        {
            hal_uart_t *hal_obj = ( hal_uart_t * )handle;

            hal_ll_uart_close( &hal_handle );

            memset( &hal_obj->config, 0xFF, sizeof( hal_uart_config_t ) );

            hal_handle->hal_uart_handle = NULL;
            hal_handle->drv_uart_handle = NULL;

            hal_handle->init_state = false;

            hal_owner = NULL;

            return HAL_UART_SUCCESS;
        }
    }

    return HAL_UART_ERROR;
}

// ------------------------------------------------------------------------- END
