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
 * @file  tft8_dma_flush_backend.h
 * @brief Contract between the portable TFT8 DMA flush core and the MCU-family
 *        backend that paces pixels onto the bus. Exactly one backend is built;
 *        each guards itself with its family macros.
 */

#ifndef _TFT8_DMA_FLUSH_BACKEND_H_
#define _TFT8_DMA_FLUSH_BACKEND_H_

#include "tft8_dma_flush.h"

// ---- Implemented by the backend ------------------------------------------

/*!< Most pixels one tft8_dma_flush_backend_start() may send (DMA count limit). */
extern const uint32_t tft8_dma_flush_backend_max_px;

/*!< One-time setup; non-zero on failure. Timing is already defaulted. */
err_t tft8_dma_flush_backend_init( const tft8_dma_flush_hw_t *hw, const tft8_dma_flush_timing_t *timing );

/*!< Send 1..tft8_dma_flush_backend_max_px pixels; D-cache already cleaned. */
void tft8_dma_flush_backend_start( const uint16_t *pixels, uint32_t num_px );

/*!< Family default WR timing. */
void tft8_dma_flush_backend_default_timing( tft8_dma_flush_timing_t *timing );

// ---- Implemented by the core, for the backend -----------------------------

/*!< Called by the backend (interrupt context) when the run is on the panel;
     @p error is true if a DMA error flag was raised during the run. */
void tft8_dma_flush_backend_done( bool error );

/*!< Write back D-cache lines covering [addr, addr + size) so the DMA reads RAM. */
void tft8_dma_flush_cache_clean( const void *addr, uint32_t size );

#endif // _TFT8_DMA_FLUSH_BACKEND_H_
// ------------------------------------------------------------------------- END
