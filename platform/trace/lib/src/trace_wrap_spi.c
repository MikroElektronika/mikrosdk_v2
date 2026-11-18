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
 * @file  trace_wrap_spi.c
 * @brief Firmware trace wrappers of the SPI Master driver.
 *
 * @details See trace_wrap_i2c.c.
 */

#include "drv_spi_master.h"
#include "trace_hooks.h"

// Defined by the HAL in both driver modes.
extern hal_spi_master_chip_select_polarity_t hal_spi_master_chip_select_polarity;

void __real_spi_master_select_device( pin_name_t chip_select );
void __real_spi_master_deselect_device( pin_name_t chip_select );
err_t __real_spi_master_write( spi_master_t *obj, uint8_t * __generic_ptr write_data_buffer, size_t write_data_length );
err_t __real_spi_master_read( spi_master_t *obj, uint8_t *read_data_buffer, size_t read_data_length );
err_t __real_spi_master_write_then_read( spi_master_t *obj, uint8_t *write_data_buffer, size_t length_write_data,
                                         uint8_t *read_data_buffer, size_t length_read_data );
err_t __real_spi_master_transfer( spi_master_t *obj, uint8_t *write_data_buffer,
                                  uint8_t *read_data_buffer, size_t data_length );

static void trace_chip_select( pin_name_t chip_select, uint8_t selected )
{
    uint8_t active_high =
        ( hal_spi_master_chip_select_polarity == HAL_SPI_MASTER_CHIP_SELECT_POLARITY_ACTIVE_HIGH );
    trace_hook_spi_cs( chip_select, selected, ( selected == active_high ) ? 1 : 0 );
}

void __wrap_spi_master_select_device( pin_name_t chip_select )
{
    __real_spi_master_select_device( chip_select );
    trace_chip_select( chip_select, 1 );
}

void __wrap_spi_master_deselect_device( pin_name_t chip_select )
{
    __real_spi_master_deselect_device( chip_select );
    trace_chip_select( chip_select, 0 );
}

err_t __wrap_spi_master_write( spi_master_t *obj, uint8_t * __generic_ptr write_data_buffer, size_t write_data_length )
{
    uint32_t start = trace_hook_now();
    err_t result = __real_spi_master_write( obj, write_data_buffer, write_data_length );
    trace_hook_spi( obj, TRACE_OP_WRITE, write_data_buffer, write_data_length, NULL, 0, result, start );
    return result;
}

err_t __wrap_spi_master_read( spi_master_t *obj, uint8_t *read_data_buffer, size_t read_data_length )
{
    uint32_t start = trace_hook_now();
    err_t result = __real_spi_master_read( obj, read_data_buffer, read_data_length );
    // MISO held stuck (fault injection): the bytes read are replaced.
    trace_hook_fault_spi( obj, read_data_buffer, read_data_length );
    trace_hook_spi( obj, TRACE_OP_READ, NULL, 0, read_data_buffer, read_data_length, result, start );
    return result;
}

err_t __wrap_spi_master_write_then_read( spi_master_t *obj, uint8_t *write_data_buffer, size_t length_write_data,
                                         uint8_t *read_data_buffer, size_t length_read_data )
{
    uint32_t start = trace_hook_now();
    err_t result = __real_spi_master_write_then_read( obj, write_data_buffer, length_write_data,
                                                      read_data_buffer, length_read_data );
    trace_hook_fault_spi( obj, read_data_buffer, length_read_data );
    trace_hook_spi( obj, TRACE_OP_WRITE_THEN_READ, write_data_buffer, length_write_data,
                    read_data_buffer, length_read_data, result, start );
    return result;
}

err_t __wrap_spi_master_transfer( spi_master_t *obj, uint8_t *write_data_buffer,
                                  uint8_t *read_data_buffer, size_t data_length )
{
    uint32_t start = trace_hook_now();
    err_t result = __real_spi_master_transfer( obj, write_data_buffer, read_data_buffer, data_length );
    trace_hook_fault_spi( obj, read_data_buffer, data_length );
    trace_hook_spi( obj, TRACE_OP_TRANSFER, write_data_buffer, data_length,
                    read_data_buffer, data_length, result, start );
    return result;
}

// ------------------------------------------------------------------------- END
