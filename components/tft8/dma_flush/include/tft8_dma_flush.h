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
 * @file  tft8_dma_flush.h
 * @brief DMA flush engine for 16-bit parallel (8080) TFT boards.
 *
 * Sends RGB565 pixel runs to a TFT controller (e.g. SSD1963) on a 16-bit
 * parallel bus without CPU involvement: a timer paces DMA requests that put
 * each pixel word on the data port and toggle the WR strobe. The caller opens
 * the controller's write window first (e.g. frame_start() from lvgl_common.h)
 * and gets a callback when the last pixel has been latched.
 *
 * Requirements:
 *  - the 16 data lines are one whole GPIO port (port_16bit_single in
 *    lvgl_common.h); other layouts must use the CPU (write_array_data()),
 *  - WR is a GPIO pin; CS/DC are left to the caller,
 *  - pixel buffers and the engine's internal data must be readable by the
 *    DMA - see TFT8_DMA_FLUSH_BUFFER_ATTR.
 *
 * Supported: STM32F2/F4/F7 with GCC (TIM1 + DMA2 Stream1/5/6, channel 6).
 * The library is built for every MCU and toolchain that has the SSD1963 TFT
 * boards; elsewhere TFT8_DMA_FLUSH_SUPPORTED is 0 and tft8_dma_flush_init()
 * fails, so the caller falls back to the CPU path.
 *
 * The engine does not depend on LVGL. With LVGL, call lv_display_flush_ready()
 * from the done callback.
 */

#ifndef _TFT8_DMA_FLUSH_H_
#define _TFT8_DMA_FLUSH_H_

#ifdef __cplusplus
extern "C"{
#endif

#include <stdbool.h>
#include <stdint.h>
#include "drv_name.h"

/*!
 * \addtogroup compgroup Components
 * @{
 */

/*!
 * \addtogroup tft8dmaflushgroup TFT8 DMA flush engine.
 * \brief Timer-paced DMA writes of pixel data to a 16-bit 8080 TFT bus.
 * @{
 */

/*!< 1 when this MCU family and compiler have an engine backend (GCC on
     STM32F2/F4/F7). 0 elsewhere: the library still links, but
     tft8_dma_flush_init() fails and callers use the CPU path. */
#if defined(__GNUC__) && ( defined(STM32F2xx) || defined(STM32F4xx) || defined(STM32F7xx) )
#define TFT8_DMA_FLUSH_SUPPORTED 1
#else
#define TFT8_DMA_FLUSH_SUPPORTED 0
#endif

/**
 * @brief Placement for pixel buffers handed to tft8_dma_flush_write().
 * @details On STM32F7, RAM at 0x20000000-0x2001FFFF is DTCM, which the DMA
 *          cannot reliably read: buffers go to the NOBITS ".dma_buffer"
 *          section, which the application must place in SRAM1 - with GCC:
 *          @code
 *          target_link_options(<app> PRIVATE LINKER:--section-start=.dma_buffer=0x20020000)
 *          @endcode
 *          ("aw",%nobits keeps 0x20020000 out of the flash image; the trailing
 *          '@' comments out the flags GCC appends.) Elsewhere ordinary RAM is
 *          used. tft8_dma_flush_init() fails if a buffer is not DMA-reachable.
 */
#if defined(__GNUC__) && defined(STM32F7xx)
#define TFT8_DMA_FLUSH_BUFFER_ATTR __attribute__((section(".dma_buffer,\"aw\",%nobits@"), aligned(32)))
#elif defined(__GNUC__)
#define TFT8_DMA_FLUSH_BUFFER_ATTR __attribute__((aligned(32)))
#else
#define TFT8_DMA_FLUSH_BUFFER_ATTR
#endif

/**
 * @brief Bus hardware, taken from the display driver's pin/port objects.
 * @details With lvgl_common.h: wr_base = pin_wr.pin.base, wr_mask =
 *          pin_wr.pin.mask, data_base = port_low.port.base (after
 *          display_configure()).
 */
typedef struct
{
    void     *wr_base;    /*!< WR pin GPIO register base. */
    uint32_t  wr_mask;    /*!< WR pin mask within its port. */
    void     *data_base;  /*!< Data port GPIO register base (16 data lines, whole port). */
} tft8_dma_flush_hw_t;

/**
 * @brief 8080 WR-cycle timing in nanoseconds.
 * @details One pixel = WR low + WR high. The next data word goes on the bus
 *          data_hold_ns after WR rises; setup before WR falls is
 *          wr_high_ns - data_hold_ns. Converted to timer ticks at the actual
 *          timer clock (rounded up). Verify on a scope for new boards.
 */
typedef struct
{
    uint16_t wr_low_ns;     /*!< WR low phase. */
    uint16_t wr_high_ns;    /*!< WR high phase. */
    uint16_t data_hold_ns;  /*!< Data change after the WR rising edge. */
} tft8_dma_flush_timing_t;

/**
 * @brief Called (from the DMA interrupt) when a whole write has been latched.
 * @param[in] context Context given to tft8_dma_flush_init().
 */
typedef void ( *tft8_dma_flush_done_t )( void *context );

/**
 * @brief Fills @p timing with the measured-safe defaults for this MCU family.
 * @details STM32F2/F4: 60/60/15 ns (~7 MHz pixel rate). At 32 ns the CPU
 *          rendering into the same SRAM delays the DMA and the data word lands
 *          after the latch (smeared pixels, no DMA error flag) - seen on
 *          STM32F407ZG, and on STM32F429NI once LVGL ran at -O2.
 *          STM32F7: 32/32/9 ns (~15 MHz), verified on STM32F767BI.
 * @param[out] timing Timing structure.
 * @return Nothing.
 */
void tft8_dma_flush_default_timing( tft8_dma_flush_timing_t *timing );

/**
 * @brief Sets up the engine (timer, three DMA streams, interrupt).
 * @details Call once, after the display driver configured its pins.
 * @param[in] hw Bus hardware.
 * @param[in] timing WR timing, NULL for tft8_dma_flush_default_timing().
 * @param[in] done Completion callback (called from interrupt context).
 * @param[in] context Passed to @p done.
 * @return 0 on success; -1 if the MCU has no backend, a DMA stream cannot be
 *         opened, or the engine's DMA data is not DMA-reachable. Then use the
 *         CPU path for every write.
 */
err_t tft8_dma_flush_init( const tft8_dma_flush_hw_t *hw, const tft8_dma_flush_timing_t *timing,
                           tft8_dma_flush_done_t done, void *context );

/**
 * @brief Starts sending @p num_px RGB565 pixels; returns immediately.
 * @details The display window must already be open with CS low. Runs longer
 *          than one DMA transfer are split internally; the done callback runs
 *          once, after the last pixel. Not reentrant: wait for the callback
 *          before the next call. The pixels must stay unchanged until then and
 *          must be DMA-reachable (tft8_dma_flush_is_reachable()).
 * @param[in] pixels RGB565 pixels.
 * @param[in] num_px Number of pixels.
 * @return Nothing.
 */
void tft8_dma_flush_write( const uint16_t *pixels, uint32_t num_px );

/**
 * @brief Checks that [@p addr, @p addr + @p size) can be read by the DMA.
 * @details False if it overlaps memory the DMA cannot read on this family
 *          (STM32F7 DTCM, STM32F4 CCM RAM).
 * @param[in] addr Start address.
 * @param[in] size Size in bytes.
 * @return true if DMA-reachable.
 */
bool tft8_dma_flush_is_reachable( const void *addr, uint32_t size );

/**
 * @brief Number of writes that ended with a DMA error (transfer or
 *        direct-mode error on any of the engine's streams). For diagnostics.
 * @return Error count since init.
 */
uint32_t tft8_dma_flush_get_error_count( void );

/*! @} */ // tft8dmaflushgroup
/*! @} */ // compgroup

#ifdef __cplusplus
}
#endif

#endif // _TFT8_DMA_FLUSH_H_
// ------------------------------------------------------------------------- END
