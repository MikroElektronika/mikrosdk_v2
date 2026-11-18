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
 * @file  trace_gpio_out.c
 * @brief Firmware trace wrappers of the GPIO Out driver.
 *
 * @details See trace_i2c.c. With FLATTEN_ME_LEVEL_HIGH the pin functions are macros
 * (drv_digital_out.h), which call the hook themselves: only digital_out_init() is wrapped.
 */

#include "drv_digital_out.h"
#include "../trace_hooks.h"

err_t __real_digital_out_init( digital_out_t *out, pin_name_t name );

err_t __wrap_digital_out_init( digital_out_t *out, pin_name_t name )
{
    err_t result = __real_digital_out_init( out, name );
    if ( DIGITAL_OUT_SUCCESS == result )
    {
        trace_hook_gpio_init( out, name, 1 );
    }
    return result;
}

#if (FLATTEN_ME_LEVEL < FLATTEN_ME_LEVEL_HIGH)
err_t __real_digital_out_high( digital_out_t *out );
err_t __real_digital_out_low( digital_out_t *out );
err_t __real_digital_out_toggle( digital_out_t *out );
err_t __real_digital_out_write( digital_out_t *out, uint8_t value );

// The hook comes before the write, as in the flattened macros. Pins the driver does not
// support are not written, nor traced.
err_t __wrap_digital_out_high( digital_out_t *out )
{
    if ( out->pin.base )
    {
        trace_hook_gpio_out( out, 1 );
    }
    return __real_digital_out_high( out );
}

err_t __wrap_digital_out_low( digital_out_t *out )
{
    if ( out->pin.base )
    {
        trace_hook_gpio_out( out, 0 );
    }
    return __real_digital_out_low( out );
}

err_t __wrap_digital_out_toggle( digital_out_t *out )
{
    if ( out->pin.base )
    {
        trace_hook_gpio_out( out, !hal_gpio_read_pin_output( &out->pin ) );
    }
    return __real_digital_out_toggle( out );
}

err_t __wrap_digital_out_write( digital_out_t *out, uint8_t value )
{
    if ( out->pin.base )
    {
        trace_hook_gpio_out( out, value );
    }
    return __real_digital_out_write( out, value );
}
#endif

// ------------------------------------------------------------------------- END
