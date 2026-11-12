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
 * @file  drv_trace.c
 * @brief Empty firmware trace hooks of the driver layer.
 *
 * @details The MikroSDK.Trace library replaces all of them when it is linked (trace.h). They
 * are defined here once, for every driver: mikroC rejects a weak symbol defined in two
 * libraries, so each driver cannot carry its own.
 */

#include "drv_trace.h"

#if DRV_TRACE_ENABLED

#if defined(__MIKROC_AI__)
// Starts at 0: see DRV_TRACE_PRESENT_TYPE.
DRV_TRACE_WEAK DRV_TRACE_PRESENT_TYPE drv_trace_present;
#else
DRV_TRACE_WEAK DRV_TRACE_PRESENT_TYPE drv_trace_present = 0;
#endif

DRV_TRACE_WEAK uint32_t drv_trace_now( void )
{
    return 0;
}

DRV_TRACE_WEAK void drv_trace_i2c( const void *obj, uint8_t op, const uint8_t *write_buf, size_t write_len,
                                   const uint8_t *read_buf, size_t read_len, err_t result, uint32_t start )
{
}

DRV_TRACE_WEAK void drv_trace_spi( const void *obj, uint8_t op, const uint8_t *write_buf, size_t write_len,
                                   const uint8_t *read_buf, size_t read_len, err_t result, uint32_t start )
{
}

DRV_TRACE_WEAK void drv_trace_spi_cs( pin_name_t chip_select, uint8_t selected, uint8_t level )
{
}

DRV_TRACE_WEAK void drv_trace_uart( const void *obj, uint8_t is_tx, const uint8_t *buf, size_t len, uint32_t start )
{
}

DRV_TRACE_WEAK void drv_trace_gpio_init( const void *obj, pin_name_t pin, uint8_t is_output )
{
}

DRV_TRACE_WEAK void drv_trace_gpio_out( const void *obj, uint8_t level )
{
}

DRV_TRACE_WEAK uint8_t drv_trace_gpio_in( const void *obj, uint8_t level )
{
    return level;
}

DRV_TRACE_WEAK void drv_trace_adc( const void *obj, pin_name_t pin, uint8_t is_voltage, float value )
{
}

DRV_TRACE_WEAK void drv_trace_one_wire( const void *obj, pin_name_t pin, uint8_t op, const uint8_t *buf, size_t len,
                                        err_t result, uint32_t start )
{
}

DRV_TRACE_WEAK uint8_t drv_trace_fault_i2c( const void *obj )
{
    return 0;
}

DRV_TRACE_WEAK void drv_trace_fault_spi( const void *obj, uint8_t *read_buf, size_t read_len )
{
}

DRV_TRACE_WEAK uint8_t drv_trace_fault_adc( const void *obj, pin_name_t pin, uint8_t is_voltage, float *value )
{
    return 0;
}

DRV_TRACE_WEAK uint8_t drv_trace_fault_one_wire( const void *obj, pin_name_t pin )
{
    return 0;
}

#else
// Some compilers reject a file with no declaration.
typedef int drv_trace_unused_t;
#endif

// ------------------------------------------------------------------------- END
