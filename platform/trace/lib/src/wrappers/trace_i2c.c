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
 * @file  trace_i2c.c
 * @brief Firmware trace wrappers of the I2C Master driver.
 *
 * @details The linker sends every call of the wrapped functions here (--wrap, see
 * CMakeLists.txt); __real_ names the driver function itself.
 */

#include "drv_i2c_master.h"
#include "../trace_hooks.h"

err_t __real_i2c_master_write( i2c_master_t *obj, uint8_t *write_data_buf, size_t len_write_data );
err_t __real_i2c_master_read( i2c_master_t *obj, uint8_t *read_data_buf, size_t len_read_data );
err_t __real_i2c_master_write_then_read( i2c_master_t *obj, uint8_t *write_data_buf, size_t len_write_data,
                                                            uint8_t *read_data_buf, size_t len_read_data );

err_t __wrap_i2c_master_write( i2c_master_t *obj, uint8_t *write_data_buf, size_t len_write_data )
{
    uint32_t start = trace_hook_now();
    // A device made not to answer (fault injection) fails the transfer before it starts.
    err_t result = trace_hook_fault_i2c( obj ) ? I2C_MASTER_ERROR :
                   __real_i2c_master_write( obj, write_data_buf, len_write_data );
    trace_hook_i2c( obj, TRACE_OP_WRITE, write_data_buf, len_write_data, NULL, 0, result, start );
    return result;
}

err_t __wrap_i2c_master_read( i2c_master_t *obj, uint8_t *read_data_buf, size_t len_read_data )
{
    uint32_t start = trace_hook_now();
    err_t result = trace_hook_fault_i2c( obj ) ? I2C_MASTER_ERROR :
                   __real_i2c_master_read( obj, read_data_buf, len_read_data );
    trace_hook_i2c( obj, TRACE_OP_READ, NULL, 0, read_data_buf, len_read_data, result, start );
    return result;
}

err_t __wrap_i2c_master_write_then_read( i2c_master_t *obj, uint8_t *write_data_buf, size_t len_write_data,
                                                            uint8_t *read_data_buf, size_t len_read_data )
{
    uint32_t start = trace_hook_now();
    err_t result = trace_hook_fault_i2c( obj ) ? I2C_MASTER_ERROR :
                   __real_i2c_master_write_then_read( obj, write_data_buf, len_write_data,
                                                      read_data_buf, len_read_data );
    trace_hook_i2c( obj, TRACE_OP_WRITE_THEN_READ, write_data_buf, len_write_data,
                    read_data_buf, len_read_data, result, start );
    return result;
}

// ------------------------------------------------------------------------- END
