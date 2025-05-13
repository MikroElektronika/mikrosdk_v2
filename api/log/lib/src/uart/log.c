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

#include "log.h"
#include "log_printf_implementation.h"

static uint8_t uart_tx_buf[ 256 ];
static uint8_t uart_rx_buf[ 256 ];

#define LOG_ASSERT_EQUAL(actual, expected) if (expected != actual) { return LOG_ERROR; } else { }

static void api_log ( log_t *log, char * prefix, const code char * __generic_ptr f, va_list ap )
{
    uart_print( &log->uart, prefix );
    log_implementation_do_prntf( log, f, ap );
    uart_print( &log->uart, "\r\n" );
}

log_err_t log_init ( log_t *log, log_cfg_t *cfg )
{
    uart_config_t uart_cfg;
    log_err_t status = LOG_SUCCESS;

    // Default config
    uart_configure_default( &uart_cfg );

    // Ring buffer mapping
    log->uart.tx_ring_buffer = uart_tx_buf;
    log->uart.rx_ring_buffer = uart_rx_buf;

    // UART module config
    uart_cfg.rx_pin = cfg->rx_pin;  // UART RX pin.
    uart_cfg.tx_pin = cfg->tx_pin;  // UART TX pin.
    uart_cfg.is_interrupt = cfg->is_interrupt;
    uart_cfg.tx_ring_size = sizeof( uart_tx_buf );
    uart_cfg.rx_ring_size = sizeof( uart_rx_buf );

    status = uart_open( &log->uart, &uart_cfg );
    if ( ACQUIRE_SUCCESS != status && ACQUIRE_INIT != status )
        return LOG_ERROR;
    status = uart_set_baud( &log->uart, cfg->baud );
    LOG_ASSERT_EQUAL( status, LOG_SUCCESS );
    status = uart_set_parity( &log->uart, UART_PARITY_DEFAULT );
    LOG_ASSERT_EQUAL( status, LOG_SUCCESS );
    status = uart_set_stop_bits( &log->uart, UART_STOP_BITS_DEFAULT );
    LOG_ASSERT_EQUAL( status, LOG_SUCCESS );
    status = uart_set_data_bits( &log->uart, UART_DATA_BITS_DEFAULT );
    LOG_ASSERT_EQUAL( status, LOG_SUCCESS );
    uart_set_blocking( &log->uart, true );

    log->log_level = cfg->level;

    return status;
}

void log_printf ( log_t *log, const code char * __generic_ptr f,... )
{
    int cnt;
    va_list  ap;

    va_start( ap, f );
    cnt = log_implementation_do_prntf( log, f, ap );
}

void log_clear ( log_t *log )
{
    uart_clear( &log->uart );
}

int8_t log_read ( log_t *log, uint8_t *rx_data_buf, uint8_t max_len )
{
    int8_t rx_size;

    rx_size = uart_read( &log->uart, rx_data_buf, max_len );
    return rx_size;
}

void log_info ( log_t *log, const code char * __generic_ptr f,... )
{
    va_list  ap;
    va_start( ap, f );

    if ( log->log_level <= LOG_LEVEL_INFO )
    {
        api_log( log, "[INFO]: ", f, ap );
    }
}

void log_error ( log_t *log, const code char * __generic_ptr f,... )
{
    va_list  ap;
    va_start( ap, f );

    if ( log->log_level <= LOG_LEVEL_ERROR )
    {
        api_log( log, "[ERROR]: ", f, ap );
    }
}

void log_fatal ( log_t *log, const code char * __generic_ptr f,... )
{
    va_list  ap;
    va_start( ap, f );

    if ( log->log_level <= LOG_LEVEL_FATAL )
    {
        api_log( log, "[FATAL]: ", f, ap );
    }
}

void log_debug ( log_t *log, const code char * __generic_ptr f,... )
{
    va_list  ap;
    va_start( ap, f );

    if ( log->log_level <= LOG_LEVEL_DEBUG )
    {
        api_log( log, "[DEBUG]: ", f, ap );
    }
}

void log_warning ( log_t *log, const code char * __generic_ptr f,... )
{
    va_list  ap;
    va_start( ap, f );

    if ( log->log_level <= LOG_LEVEL_WARNING )
    {
        api_log( log, "[WARNING]: ", f, ap );
    }
}

void log_log ( log_t *log, char * prefix, const code char * __generic_ptr f,... )
{
    va_list  ap;
    va_start( ap, f );

    api_log( log, prefix, f, ap );
}
