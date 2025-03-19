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
#include "systick.h"
#include "log_printf_implementation.h"

static uint8_t uart_tx_buf[ 256 ];
static uint8_t uart_rx_buf[ 256 ];

#define LOG_ASSERT_EQUAL(expected, actual) if (expected != actual) { return LOG_ERROR; } else { }

/**
 * @note Using the stack without an OS requires @ref systemTicks
 * to be incremented every 1ms.
 */
TIMER_SYSTICK_HANDLER() {
    tud_task(); // Tinyusb device task.
}

static void api_log ( log_t *log, char * prefix, const code char * __generic_ptr f, va_list ap )
{
    static uint8_t hid_tx_buffer[HID_BUFFER_SIZE] = { 0 };

    while (!tud_hid_ready()) tud_task(); // Ensure HID is ready
    memcpy(hid_tx_buffer, prefix, strlen(prefix));
    tud_hid_report(0, hid_tx_buffer, HID_BUFFER_SIZE);
    log_implementation_do_prntf( log, f, ap );
}

log_err_t log_init ( log_t *log, log_cfg_t *cfg )
{
    log_err_t status = LOG_SUCCESS;

    // Configure SYSTICK to 1ms interrupt.
    if ( !sysTickConfig( GET_TICK_NUMBER_PER_CLOCK ) ) {
        sysTickInit( 15 ); // Maximum priority - level 15.
    } else {
        return -1;
    }

    // Init device stack on configured roothub port
    if ( false == tusb_init() )
        while(1);

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
