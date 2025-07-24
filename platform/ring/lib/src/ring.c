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
 * @file  ring.c
 * @brief mikroSDK ring buffer library source file.
 */

#include "ring.h"

#include <assert.h>
#include <string.h>

void ring_buf8_init( ring_buf8_t *ring, uint8_t *buf, size_t capacity )
{
    memset( buf, 0x00, capacity );

    ring->buffer = buf;
    ring->capacity = capacity;
}

bool ring_buf8_push( ring_buf8_t *ring, uint8_t data_ )
{
    if ( ring->size == ring->capacity ) {
        return false;
    }

    ring->buffer[ ring->head ] = data_;
    ring->head = ( ring->head + 1 ) % ring->capacity;
    ring->size++;

    return true;
}

uint8_t ring_buf8_pop( ring_buf8_t *ring )
{
    uint8_t result;

    // GCC & Clang compiler files for Renesas are not included into the project.
    #if ( vendor != renesas )
    assert( ring->size > 0 );
    #endif

    result = ring->buffer[ ring->tail ];
    ring->tail = ( ring->tail + 1 ) % ring->capacity;
    ring->size--;

    return result;
}

bool ring_buf8_is_empty( ring_buf8_t *ring )
{
    return ring->size == 0;
}

bool ring_buf8_is_full( ring_buf8_t *ring )
{
    return ring->size == ring->capacity;
}

size_t ring_buf8_size( ring_buf8_t *ring )
{
    return ring->size;
}

void ring_buf8_clear( ring_buf8_t *ring )
{
    ring->size = 0;
    ring->head = 0;
    ring->tail = 0;
}

#ifdef __MIKROC_AI_FOR_PIC__
#pragma ReentrancyCheck OFF ring_buf8_is_empty, ring_buf8_is_full, ring_buf8_pop, ring_buf8_push
#endif

// ------------------------------------------------------------------------- END
