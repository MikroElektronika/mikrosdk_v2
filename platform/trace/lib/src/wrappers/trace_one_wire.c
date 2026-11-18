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
 * @file  trace_one_wire.c
 * @brief Firmware trace wrappers of the 1-Wire driver.
 *
 * @details See trace_i2c.c.
 */

#include "drv_one_wire.h"
#include "../trace_hooks.h"

err_t __real_one_wire_reset( one_wire_t *obj );
err_t __real_one_wire_read_rom( one_wire_t *obj, one_wire_rom_address_t *device_rom_address );
err_t __real_one_wire_skip_rom( one_wire_t *obj );
err_t __real_one_wire_match_rom( one_wire_t *obj, one_wire_rom_address_t *device_rom_address );
err_t __real_one_wire_search_first_device( one_wire_t *obj, one_wire_rom_address_t *one_wire_device_list );
err_t __real_one_wire_search_next_device( one_wire_t *obj, one_wire_rom_address_t *one_wire_device_list );
err_t __real_one_wire_write_byte( one_wire_t *obj, uint8_t *write_data_buffer, size_t write_data_length );
err_t __real_one_wire_read_byte( one_wire_t *obj, uint8_t *read_data_buffer, size_t read_data_length );

static void trace_one_wire( one_wire_t *obj, uint8_t op, const uint8_t *buf, size_t len,
                            err_t result, uint32_t start ) {
    if ( obj ) {
        trace_hook_one_wire( obj, obj->data_pin, op, buf, len, result, start );
    }
}

static void trace_one_wire_rom( one_wire_t *obj, uint8_t op, one_wire_rom_address_t *rom,
                                err_t result, uint32_t start ) {
    trace_one_wire( obj, op, rom ? rom->address : NULL, rom ? sizeof( rom->address ) : 0, result, start );
}

// No device answers while fault injection says so, and the operation is skipped as on an empty
// bus: what starts with a reset fails for the missing presence pulse, reads see the idle bus
// (0xFF), writes go nowhere. True when the operation is skipped; *result is then its result.
static bool trace_one_wire_fault( one_wire_t *obj, uint8_t op, uint8_t *buf, size_t len,
                                  err_t *result ) {
    if ( !obj || !trace_hook_fault_one_wire( obj, obj->data_pin ) ) {
        return false;
    }
    if ( TRACE_ONE_WIRE_READ == op ) {
        for ( size_t i = 0; buf && ( i < len ); i++ ) {
            buf[ i ] = 0xFF;
        }
        *result = ONE_WIRE_SUCCESS;
    } else if ( TRACE_ONE_WIRE_WRITE == op ) {
        *result = ONE_WIRE_SUCCESS;
    } else {
        *result = ONE_WIRE_ERROR;
    }
    return true;
}

err_t __wrap_one_wire_reset( one_wire_t *obj ) {
    uint32_t start = trace_hook_now();
    err_t result;
    if ( !trace_one_wire_fault( obj, TRACE_ONE_WIRE_RESET, NULL, 0, &result ) ) {
        result = __real_one_wire_reset( obj );
    }
    trace_one_wire( obj, TRACE_ONE_WIRE_RESET, NULL, 0, result, start );
    return result;
}

err_t __wrap_one_wire_read_rom( one_wire_t *obj, one_wire_rom_address_t *device_rom_address ) {
    uint32_t start = trace_hook_now();
    err_t result;
    if ( !trace_one_wire_fault( obj, TRACE_ONE_WIRE_READ_ROM, NULL, 0, &result ) ) {
        result = __real_one_wire_read_rom( obj, device_rom_address );
    }
    trace_one_wire_rom( obj, TRACE_ONE_WIRE_READ_ROM, device_rom_address, result, start );
    return result;
}

err_t __wrap_one_wire_skip_rom( one_wire_t *obj ) {
    uint32_t start = trace_hook_now();
    err_t result;
    if ( !trace_one_wire_fault( obj, TRACE_ONE_WIRE_SKIP_ROM, NULL, 0, &result ) ) {
        result = __real_one_wire_skip_rom( obj );
    }
    trace_one_wire( obj, TRACE_ONE_WIRE_SKIP_ROM, NULL, 0, result, start );
    return result;
}

err_t __wrap_one_wire_match_rom( one_wire_t *obj, one_wire_rom_address_t *device_rom_address ) {
    uint32_t start = trace_hook_now();
    err_t result;
    if ( !trace_one_wire_fault( obj, TRACE_ONE_WIRE_MATCH_ROM, NULL, 0, &result ) ) {
        result = __real_one_wire_match_rom( obj, device_rom_address );
    }
    trace_one_wire_rom( obj, TRACE_ONE_WIRE_MATCH_ROM, device_rom_address, result, start );
    return result;
}

err_t __wrap_one_wire_search_first_device( one_wire_t *obj, one_wire_rom_address_t *one_wire_device_list ) {
    uint32_t start = trace_hook_now();
    err_t result;
    if ( !trace_one_wire_fault( obj, TRACE_ONE_WIRE_SEARCH_FIRST, NULL, 0, &result ) ) {
        result = __real_one_wire_search_first_device( obj, one_wire_device_list );
    }
    trace_one_wire_rom( obj, TRACE_ONE_WIRE_SEARCH_FIRST, one_wire_device_list, result, start );
    return result;
}

err_t __wrap_one_wire_search_next_device( one_wire_t *obj, one_wire_rom_address_t *one_wire_device_list ) {
    uint32_t start = trace_hook_now();
    err_t result;
    if ( !trace_one_wire_fault( obj, TRACE_ONE_WIRE_SEARCH_NEXT, NULL, 0, &result ) ) {
        result = __real_one_wire_search_next_device( obj, one_wire_device_list );
    }
    trace_one_wire_rom( obj, TRACE_ONE_WIRE_SEARCH_NEXT, one_wire_device_list, result, start );
    return result;
}

err_t __wrap_one_wire_write_byte( one_wire_t *obj, uint8_t *write_data_buffer, size_t write_data_length ) {
    uint32_t start = trace_hook_now();
    err_t result;
    if ( !trace_one_wire_fault( obj, TRACE_ONE_WIRE_WRITE, NULL, 0, &result ) ) {
        result = __real_one_wire_write_byte( obj, write_data_buffer, write_data_length );
    }
    trace_one_wire( obj, TRACE_ONE_WIRE_WRITE, write_data_buffer, write_data_length, result, start );
    return result;
}

err_t __wrap_one_wire_read_byte( one_wire_t *obj, uint8_t *read_data_buffer, size_t read_data_length ) {
    uint32_t start = trace_hook_now();
    err_t result;
    if ( !trace_one_wire_fault( obj, TRACE_ONE_WIRE_READ, read_data_buffer, read_data_length, &result ) ) {
        result = __real_one_wire_read_byte( obj, read_data_buffer, read_data_length );
    }
    trace_one_wire( obj, TRACE_ONE_WIRE_READ, read_data_buffer, read_data_length, result, start );
    return result;
}

// ------------------------------------------------------------------------- END
