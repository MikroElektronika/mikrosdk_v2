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
 * @file  trace_wrap_uart.c
 * @brief Firmware trace wrappers of the UART driver.
 *
 * @details See trace_wrap_i2c.c.
 */

#include "drv_uart.h"
#include "trace_hooks.h"

err_t __real_uart_write( uart_t *obj, uint8_t *buffer, size_t size );
err_t __real_uart_print( uart_t *obj, char *text );
err_t __real_uart_println( uart_t *obj, char *text );
err_t __real_uart_read( uart_t *obj, uint8_t *buffer, size_t size );

// The UART functions return the number of bytes, or a negative error.
static void trace_uart( const uart_t *obj, uint8_t is_tx, const void *buf, err_t result, uint32_t start )
{
    if ( result > 0 )
    {
        trace_hook_uart( obj, is_tx, (const uint8_t *)buf, (size_t)result, start );
    }
}

err_t __wrap_uart_write( uart_t *obj, uint8_t *buffer, size_t size )
{
    uint32_t start = trace_hook_now();
    err_t result = __real_uart_write( obj, buffer, size );
    trace_uart( obj, 1, buffer, result, start );
    return result;
}

err_t __wrap_uart_print( uart_t *obj, char *text )
{
    uint32_t start = trace_hook_now();
    err_t result = __real_uart_print( obj, text );
    trace_uart( obj, 1, text, result, start );
    return result;
}

err_t __wrap_uart_println( uart_t *obj, char *text )
{
    uint32_t start = trace_hook_now();
    err_t result = __real_uart_println( obj, text );
    // The result counts the "\r\n" too, which is not in the text: the trace gets what was
    // sent, put together here, and never reads past the end of the text. 16 bytes is the
    // most the trace keeps of a transfer.
    uint8_t sent[ 16 ];
    size_t count = 0;
    while ( ( count < sizeof( sent ) ) && text[ count ] )
    {
        sent[ count ] = (uint8_t)text[ count ];
        count++;
    }
    if ( count < sizeof( sent ) )
    {
        sent[ count++ ] = '\r';
    }
    if ( count < sizeof( sent ) )
    {
        sent[ count++ ] = '\n';
    }
    trace_uart( obj, 1, sent, result, start );
    return result;
}

err_t __wrap_uart_read( uart_t *obj, uint8_t *buffer, size_t size )
{
    uint32_t start = trace_hook_now();
    err_t result = __real_uart_read( obj, buffer, size );
    trace_uart( obj, 0, buffer, result, start );
    return result;
}

// ------------------------------------------------------------------------- END
