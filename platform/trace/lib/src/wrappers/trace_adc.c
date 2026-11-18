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
 * @file  trace_adc.c
 * @brief Firmware trace wrappers of the ADC driver.
 *
 * @details See trace_i2c.c.
 */

#include "drv_analog_in.h"
#include "../trace_hooks.h"

err_t __real_analog_in_read( analog_in_t *obj, uint16_t *readDatabuf );
err_t __real_analog_in_read_voltage( analog_in_t *obj, float *readDatabuf );

err_t __wrap_analog_in_read( analog_in_t *obj, uint16_t *readDatabuf )
{
    // A value forced by fault injection is given without reading the input.
    float forced;
    err_t result;
    if ( readDatabuf && trace_hook_fault_adc( obj, obj->config.input_pin, 0, &forced ) )
    {
        *readDatabuf = (uint16_t)forced;
        result = ADC_SUCCESS;
    } else {
        result = __real_analog_in_read( obj, readDatabuf );
    }
    if ( ADC_SUCCESS == result )
    {
        trace_hook_adc( obj, obj->config.input_pin, 0, (float)*readDatabuf );
    }
    return result;
}

err_t __wrap_analog_in_read_voltage( analog_in_t *obj, float *readDatabuf )
{
    err_t result;
    if ( readDatabuf && trace_hook_fault_adc( obj, obj->config.input_pin, 1, readDatabuf ) )
    {
        result = ADC_SUCCESS;
    } else {
        result = __real_analog_in_read_voltage( obj, readDatabuf );
    }
    if ( ADC_SUCCESS == result )
    {
        trace_hook_adc( obj, obj->config.input_pin, 1, *readDatabuf );
    }
    return result;
}

// ------------------------------------------------------------------------- END
