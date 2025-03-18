/****************************************************************************
**
** Copyright (C) 2025 MikroElektronika d.o.o.
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

#include "log.h"

static void api_log ( log_t *log, char * prefix, const code char * __generic_ptr f, va_list ap )
{
    printf_me( prefix );
    vfprintf_me( &debugStdOut, f, ap );
    printf_me( "\n" );
}

log_err_t log_init ( log_t *log, log_cfg_t *cfg )
{
    log->log_level = cfg->level;

    return LOG_SUCCESS;
}

void log_printf ( log_t *log, const code char * __generic_ptr f,... )
{
    va_list  ap;

    va_start( ap, f );
    vfprintf_me( &debugStdOut, f, ap );
    printf_me( "\n" );
}

void log_clear ( log_t *log )
{
    printf_me( "log_clear not implemented for MikroE std_out.\n" );
}

int8_t log_read ( log_t *log, uint8_t *rx_data_buf, uint8_t max_len )
{
    printf_me( "log_read not implemented for MikroE std_out.\n" );
    return 0;
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
