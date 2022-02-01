/****************************************************************************
**
** Copyright (C) 2022 MikroElektronika d.o.o.
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
 * @file  ring.h
 * @brief mikroSDK ring buffer.
 */

#ifndef _RING_H_
#define _RING_H_

#ifdef __cplusplus
extern "C"{
#endif

#include <stdint.h>
#include <stdbool.h>
#include <stddef.h>

/*!
 * @addtogroup platform Platform
 * @{
 */

/*!
 * @addtogroup ringbuf Ring buffer.
 * @brief Ring buffer library.
 *
 * Detailed description here.
 * @{
 */

typedef struct
{
    uint8_t *buffer;
    size_t capacity;
    volatile size_t size;
    volatile size_t head;
    volatile size_t tail;
} ring_buf8_t;

/**
 * @brief Initializes ring buffer with preallocated memory.
 *
 * @param ring The ring buffer isntance.
 * @param buf Preallocated memory address.
 * @param capacity Preallocated memory size.
 *
 */
void ring_buf8_init(ring_buf8_t *ring, uint8_t *buf, size_t capacity);


/**
 * @brief Pushes data to the ring buffer.
 *
 * @param ring The ring buffer isntance.
 * @param data_ Data to be pushed to the buffer.
 *
 * @return Retruns true if data is pushed successfuly, otherwise returns false.
 */
bool ring_buf8_push(ring_buf8_t *buf, uint8_t data_);

/**
 * @brief Pops data from the ring buffer. The caller needs to ensure that the
 * ring buffer is not empty.
 *
 * @param ring The ring buffer isntance.
 *
 * @return Returns data.
 */
uint8_t ring_buf8_pop(ring_buf8_t *buf);


/**
 * @brief Returns true if the ring buffer is empty, otherwise returns false.
 */
bool ring_buf8_is_empty(ring_buf8_t *buf);

/**
 * @brief Returns true if the ring buffer is full, otherwise returns false.
 */
bool ring_buf8_is_full(ring_buf8_t *buf);


/**
 * @brief Returns number of bytes in the ring buffer.
 */
size_t ring_buf8_size(ring_buf8_t *buf);

/**
 * @brief Clears the ring buffer.
 */
void ring_buf8_clear(ring_buf8_t *buf);

/*! @} */ // ringbuf
/*! @} */ // platform

#ifdef __cplusplus
}
#endif

/*! @} */

#endif // _RING_H_
// ------------------------------------------------------------------------- END
