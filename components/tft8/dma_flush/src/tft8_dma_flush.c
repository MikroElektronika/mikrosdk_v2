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
 * @file  tft8_dma_flush.c
 * @brief Portable core of the TFT8 DMA flush engine: D-cache maintenance,
 *        splitting long writes into backend-sized runs, completion callback.
 */

#include "tft8_dma_flush_backend.h"

// ------------------------------------------------------------------ VARIABLES

static tft8_dma_flush_done_t tft8_dma_flush_done;
static void *tft8_dma_flush_context;
static bool tft8_dma_flush_ready = false;

static const uint16_t *tft8_dma_flush_next_px;     /*!< First pixel of the next run. */
static volatile uint32_t tft8_dma_flush_remaining; /*!< Pixels not yet handed to the backend. */
static volatile uint32_t tft8_dma_flush_error_count;

#if defined(__cortex_m7__) && defined(__GNUC__)
/*!< SCB->DCCMVAC: clean D-cache line by address (architectural, Cortex-M7). */
#define TFT8_DMA_FLUSH_SCB_DCCMVAC (*(volatile uint32_t *)0xE000EF68u)
#endif

// ---------------------------------------------- PRIVATE FUNCTION DECLARATIONS

/*!< Hands the backend the next run, at most one DMA transfer long. */
static void tft8_dma_flush_start_next( void );

// ------------------------------------------------ PUBLIC FUNCTION DEFINITIONS

void tft8_dma_flush_cache_clean( const void *addr, uint32_t size ) {
#if defined(__cortex_m7__) && defined(__GNUC__)
    uint32_t line = (uint32_t)addr & ~31u;
    uint32_t end = (uint32_t)addr + size;

    __asm volatile( "dsb 0xF" ::: "memory" );
    while ( line < end ) {
        TFT8_DMA_FLUSH_SCB_DCCMVAC = line;
        line += 32u;
    }
    __asm volatile( "dsb 0xF" ::: "memory" );
    __asm volatile( "isb 0xF" ::: "memory" );
#else
    (void)addr;
    (void)size;
#endif
}

bool tft8_dma_flush_is_reachable( const void *addr, uint32_t size ) {
    const uint32_t start = (uint32_t)addr;
    const uint32_t end = start + size;

#if defined(STM32F7xx)
    // DTCM.
    return ( end <= 0x20000000u ) || ( start >= 0x20020000u );
#elif defined(STM32F2xx) || defined(STM32F4xx)
    // CCM RAM (F4; absent on F2, harmless).
    return ( end <= 0x10000000u ) || ( start >= 0x10010000u );
#else
    (void)start;
    (void)end;
    return true;
#endif
}

void tft8_dma_flush_default_timing( tft8_dma_flush_timing_t *timing ) {
    if ( timing ) {
        tft8_dma_flush_backend_default_timing( timing );
    }
}

err_t tft8_dma_flush_init( const tft8_dma_flush_hw_t *hw, const tft8_dma_flush_timing_t *timing,
                           tft8_dma_flush_done_t done, void *context ) {
    tft8_dma_flush_timing_t defaults;

    tft8_dma_flush_ready = false;
    if ( !hw || !hw->wr_base || !hw->data_base || !done ) {
        return -1;
    }
    if ( !timing ) {
        tft8_dma_flush_backend_default_timing( &defaults );
        timing = &defaults;
    }

    tft8_dma_flush_done = done;
    tft8_dma_flush_context = context;
    tft8_dma_flush_error_count = 0;

    if ( tft8_dma_flush_backend_init( hw, timing ) ) {
        return -1;
    }
    tft8_dma_flush_ready = true;
    return 0;
}

void tft8_dma_flush_write( const uint16_t *pixels, uint32_t num_px ) {
    if ( !tft8_dma_flush_ready || !num_px ) {
        if ( tft8_dma_flush_done ) {
            tft8_dma_flush_done( tft8_dma_flush_context );
        }
        return;
    }

    // The CPU wrote the pixels through the D-cache; the DMA reads RAM.
    tft8_dma_flush_cache_clean( pixels, num_px * 2u );

    // The display window is open for the whole run, so consecutive backend
    // runs just continue the pixel stream.
    tft8_dma_flush_next_px = pixels;
    tft8_dma_flush_remaining = num_px;
    tft8_dma_flush_start_next();
}

uint32_t tft8_dma_flush_get_error_count( void ) {
    return tft8_dma_flush_error_count;
}

void tft8_dma_flush_backend_done( bool error ) {
    if ( error ) {
        tft8_dma_flush_error_count++;
    }
    if ( tft8_dma_flush_remaining ) {
        tft8_dma_flush_start_next();
        return;
    }
    tft8_dma_flush_done( tft8_dma_flush_context );
}

// ----------------------------------------------- PRIVATE FUNCTION DEFINITIONS

static void tft8_dma_flush_start_next( void ) {
    uint32_t num_px = tft8_dma_flush_remaining;
    const uint16_t *pixels = tft8_dma_flush_next_px;

    if ( num_px > tft8_dma_flush_backend_max_px ) {
        num_px = tft8_dma_flush_backend_max_px;
    }
    tft8_dma_flush_next_px += num_px;
    tft8_dma_flush_remaining -= num_px;
    tft8_dma_flush_backend_start( pixels, num_px );
}

// ------------------------------------------------------------------------- END
