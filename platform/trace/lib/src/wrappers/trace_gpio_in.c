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
 * @file  trace_gpio_in.c
 * @brief Firmware trace wrappers of the GPIO In driver.
 *
 * @details See trace_i2c.c. With FLATTEN_ME_LEVEL_HIGH digital_in_read() is a macro
 * (drv_digital_in.h), which calls the hook itself: only digital_in_init() is wrapped.
 */

#include "drv_digital_in.h"
#include "../trace_hooks.h"

err_t __real_digital_in_init( digital_in_t *in, pin_name_t name );

err_t __wrap_digital_in_init( digital_in_t *in, pin_name_t name )
{
    err_t result = __real_digital_in_init( in, name );
    if ( DIGITAL_IN_SUCCESS == result )
    {
        trace_hook_gpio_init( in, name, 0 );
    }
    return result;
}

#if (FLATTEN_ME_LEVEL < FLATTEN_ME_LEVEL_HIGH)
uint8_t __real_digital_in_read( digital_in_t *in );

uint8_t __wrap_digital_in_read( digital_in_t *in )
{
    uint8_t level = __real_digital_in_read( in );
    // The hook gives the level back, or the level of a fault holding the pin.
    return in->pin.base ? trace_hook_gpio_in( in, level ) : level;
}
#endif

// ------------------------------------------------------------------------- END
