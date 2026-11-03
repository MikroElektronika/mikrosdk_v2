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
 * @file  drv_digital_in.c
 * @brief Digital input driver implementation.
 */

#include "drv_digital_in.h"

#if DRV_TRACE_ENABLED
// Empty unless the MikroSDK.Trace library is linked.
DRV_TRACE_WEAK const volatile uint8_t drv_trace_present = 0;

DRV_TRACE_WEAK void drv_trace_gpio_init( const void *obj, pin_name_t pin, uint8_t is_output )
{
}

DRV_TRACE_WEAK uint8_t drv_trace_gpio_in( const void *obj, uint8_t level )
{
    return level;
}
#endif

err_t digital_in_init( digital_in_t *in, pin_name_t name )
{
    if ( HAL_PIN_NC == name )
    {
        return DIGITAL_IN_UNSUPPORTED_PIN;
    }

    hal_gpio_configure_pin( &in->pin, name, (hal_gpio_direction_t)GPIO_DIGITAL_INPUT );
    #if DRV_TRACE_ENABLED
    DRV_TRACE( drv_trace_gpio_init( in, name, 0 ) );
    #endif
    return DIGITAL_IN_SUCCESS;
}

#if (FLATTEN_ME_LEVEL < FLATTEN_ME_LEVEL_HIGH)
uint8_t digital_in_read( digital_in_t *in )
{
    if ( in->pin.base )
    {
        #if DRV_TRACE_ENABLED
        // The hook gives the level back, or the level of a fault holding the pin.
        uint8_t level = hal_gpio_read_pin_input( &in->pin );
        return drv_trace_present ? drv_trace_gpio_in( in, level ) : level;
        #else
        return hal_gpio_read_pin_input( &in->pin );
        #endif
    } else {
        return 0;
    }
}
#endif

// ------------------------------------------------------------------------- END
