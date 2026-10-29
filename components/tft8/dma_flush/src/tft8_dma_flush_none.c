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
 * @file  tft8_dma_flush_none.c
 * @brief TFT8 DMA flush backend for MCU families without one: init fails so
 *        the caller uses the CPU path.
 */

#include "tft8_dma_flush_backend.h"

#if !TFT8_DMA_FLUSH_SUPPORTED

const uint32_t tft8_dma_flush_backend_max_px = 0u;

void tft8_dma_flush_backend_default_timing( tft8_dma_flush_timing_t *timing ) {
    timing->wr_low_ns = 60;
    timing->wr_high_ns = 60;
    timing->data_hold_ns = 15;
}

err_t tft8_dma_flush_backend_init( const tft8_dma_flush_hw_t *hw, const tft8_dma_flush_timing_t *timing ) {
    (void)hw;
    (void)timing;
    return -1;
}

void tft8_dma_flush_backend_start( const uint16_t *pixels, uint32_t num_px ) {
    (void)pixels;
    (void)num_px;
}

#endif // !TFT8_DMA_FLUSH_SUPPORTED

// ------------------------------------------------------------------------- END
