/****************************************************************************
**
** Copyright (C) 2023 MikroElektronika d.o.o.
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
/*!
 * @file  drv_one_wire.c
 * @brief One Wire driver implementation.
 */

#include "drv_one_wire.h"

err_t one_wire_open( one_wire_t *obj ) {
    if ( HAL_PIN_NC == obj->data_pin || obj->state ) {
        return ONE_WIRE_ERROR;
    }

    if ( ONE_WIRE_SUCCESS != hal_one_wire_open( obj ) ) {
        return ONE_WIRE_ERROR;
    } else {
        return ONE_WIRE_SUCCESS;
    }
}

void one_wire_configure_default( one_wire_t *obj ) {
    obj->data_pin = 0xFFFFFFFF;
    obj->state = false;
}

err_t one_wire_reset( one_wire_t *obj ) {
    if ( hal_one_wire_reset( obj ) ) {
        return ONE_WIRE_ERROR;
    }

    return ONE_WIRE_SUCCESS;
}

err_t one_wire_read_rom( one_wire_t *obj, one_wire_rom_address_t *device_rom_address ) {
    if ( hal_one_wire_read_rom( obj, device_rom_address ) ) {
        return ONE_WIRE_ERROR;
    }

    return ONE_WIRE_SUCCESS;
}

err_t one_wire_skip_rom( one_wire_t *obj ) {
    if ( hal_one_wire_skip_rom( obj ) ) {
        return ONE_WIRE_ERROR;
    }

    return ONE_WIRE_SUCCESS;
}

err_t one_wire_match_rom( one_wire_t *obj, one_wire_rom_address_t *device_rom_address ) {
    if ( hal_one_wire_match_rom( obj, device_rom_address ) ) {
        return ONE_WIRE_ERROR;
    }

    return ONE_WIRE_SUCCESS;
}

err_t one_wire_search_first_device( one_wire_t *obj, one_wire_rom_address_t *one_wire_device_list ) {
    if ( hal_one_wire_search_first_device( obj, one_wire_device_list ) ) {
        return ONE_WIRE_ERROR;
    }

    return ONE_WIRE_SUCCESS;
}

err_t one_wire_search_next_device( one_wire_t *obj, one_wire_rom_address_t *one_wire_device_list ) {
    if ( hal_one_wire_search_next_device( obj, one_wire_device_list ) ) {
        return ONE_WIRE_ERROR;
    }

    return ONE_WIRE_SUCCESS;
}

err_t one_wire_write_byte( one_wire_t *obj, uint8_t *write_data_buffer, size_t write_data_length ) {
    if ( hal_one_wire_write_byte( obj, write_data_buffer, write_data_length ) ) {
        return ONE_WIRE_ERROR;
    }

    return ONE_WIRE_SUCCESS;
}

err_t one_wire_read_byte( one_wire_t *obj, uint8_t *read_data_buffer, size_t read_data_length ) {
    if ( hal_one_wire_read_byte( obj, read_data_buffer, read_data_length ) ) {
        return ONE_WIRE_ERROR;
    }

    return ONE_WIRE_SUCCESS;
}

// ------------------------------------------------------------------------- END
