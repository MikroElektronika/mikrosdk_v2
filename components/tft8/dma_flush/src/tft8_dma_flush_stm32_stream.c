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
 * @file  tft8_dma_flush_stm32_stream.c
 * @brief TFT8 DMA flush backend for STM32F2/F4/F7 (stream DMA, fixed request
 *        table). TIM1 clocks three DMA2 streams that push pixels and toggle WR:
 *
 *   TIM1_CH1 -> DMA2 Stream1 Ch6 : pixel word -> <data>->ODR  (CCR1)
 *   TIM1_CH3 -> DMA2 Stream6 Ch6 : WR low     -> <WR>->BSRR   (CCR3)
 *   TIM1_UP  -> DMA2 Stream5 Ch6 : WR high    -> <WR>->BSRR   (overflow = latch)
 *
 * Per timer period: WR high (latch previous pixel) -> data -> WR low; the
 * SSD1963 latches on the rising edge. The WR-high stream's transfer-complete
 * interrupt marks the last latch. The request table is identical on F2/F4/F7,
 * and only DMA2 can write GPIO there. The timer itself is programmed directly:
 * mikroSDK has no API for timer-generated DMA requests.
 */

#include "tft8_dma_flush_backend.h"

#if TFT8_DMA_FLUSH_SUPPORTED

#include "mcu.h"
#include "drv_dma.h"

// ------------------------------------------------------------- PRIVATE MACROS

#define TFT8_DMA_MODULE       1u  /*!< mikroSDK index of DMA2. */
#define TFT8_DMA_CHANNEL      6u  /*!< CHSEL of every TIM1 request below. */
#define TFT8_DMA_STREAM_DATA  1u  /*!< TIM1_CH1. */
#define TFT8_DMA_STREAM_WRLO  6u  /*!< TIM1_CH3. */
#define TFT8_DMA_STREAM_WRHI  5u  /*!< TIM1_UP. */

#define TFT8_DMA_ALL_EVENTS   ( DMA_EVENT_TRANSFER_COMPLETE | DMA_EVENT_HALF_TRANSFER | \
                                DMA_EVENT_TRANSFER_ERROR | DMA_EVENT_DIRECT_MODE_ERROR | \
                                DMA_EVENT_FIFO_ERROR )
#define TFT8_DMA_ERROR_EVENTS ( DMA_EVENT_TRANSFER_ERROR | DMA_EVENT_DIRECT_MODE_ERROR )

// ------------------------------------------------------------------ VARIABLES

/*!< NDTR is 16 bits: one item per pixel on every stream. */
const uint32_t tft8_dma_flush_backend_max_px = 65535u;

/*!< BSRR values fed to the WR streams (one write replicated per pixel). DMA
     sources, so DMA-reachable; that section may be NOBITS (no initializer
     copied at startup), so they are assigned in init. */
static TFT8_DMA_FLUSH_BUFFER_ATTR uint32_t tft8_dma_wr_low_word;
static TFT8_DMA_FLUSH_BUFFER_ATTR uint32_t tft8_dma_wr_high_word;

static uint32_t tft8_dma_data_odr;  /*!< &<data port>->ODR. */
static uint32_t tft8_dma_wr_bsrr;   /*!< &<WR port>->BSRR. */

static dma_t tft8_dma_data;  /*!< Pixels -> data port ODR. */
static dma_t tft8_dma_wrlo;  /*!< WR low -> WR port BSRR. */
static dma_t tft8_dma_wrhi;  /*!< WR high -> WR port BSRR. */

// ---------------------------------------------- PRIVATE FUNCTION DECLARATIONS

/*!< TIM1 kernel clock from the core clock (OSC_KHZ) and RCC APB2 prescaler/TIMPRE. */
static uint32_t tft8_dma_tim1_clock_hz( void );

/*!< Smallest number of timer ticks lasting at least @p ns. */
static uint32_t tft8_dma_ns_to_ticks( uint32_t ns, uint32_t clk_hz );

/*!< Opens one stream in direct mode; false on failure. */
static bool tft8_dma_open_stream( dma_t *obj, uint8_t stream, dma_data_align_t align,
                                  bool src_inc, dma_priority_t priority );

/*!< WR-high stream interrupt: end of the run (or a DMA error). */
static void tft8_dma_on_wrhi( void *context, uint8_t events );

// ------------------------------------------------ PUBLIC FUNCTION DEFINITIONS

void tft8_dma_flush_backend_default_timing( tft8_dma_flush_timing_t *timing ) {
#if defined(STM32F7xx)
    timing->wr_low_ns = 32;
    timing->wr_high_ns = 32;
    timing->data_hold_ns = 9;
#else
    // F2/F4: CPU rendering into the same SRAM delays the DMA; 32 ns smears.
    timing->wr_low_ns = 60;
    timing->wr_high_ns = 60;
    timing->data_hold_ns = 15;
#endif
}

err_t tft8_dma_flush_backend_init( const tft8_dma_flush_hw_t *hw, const tft8_dma_flush_timing_t *timing ) {
    // The mikroSDK GPIO objects keep the CMSIS port register base.
    GPIO_TypeDef *wr_gpio = (GPIO_TypeDef *)hw->wr_base;
    GPIO_TypeDef *data_gpio = (GPIO_TypeDef *)hw->data_base;
    uint32_t clk, wr_low, wr_high, hold;

    if ( !tft8_dma_flush_is_reachable( &tft8_dma_wr_low_word, sizeof( tft8_dma_wr_low_word ) ) ||
         !tft8_dma_flush_is_reachable( &tft8_dma_wr_high_word, sizeof( tft8_dma_wr_high_word ) ) ) {
        return -1;
    }

    // TIM1 clock. (GPIO and DMA2 clocks: display driver / dma_open.)
    RCC->APB2ENR |= RCC_APB2ENR_TIM1EN;

    tft8_dma_wr_bsrr = (uint32_t)&wr_gpio->BSRR;
    tft8_dma_data_odr = (uint32_t)&data_gpio->ODR;

    // BSRR: mask => WR high, mask << 16 (reset half) => WR low.
    tft8_dma_wr_high_word = hw->wr_mask;
    tft8_dma_wr_low_word = hw->wr_mask << 16;
    tft8_dma_flush_cache_clean( &tft8_dma_wr_low_word, sizeof( tft8_dma_wr_low_word ) );
    tft8_dma_flush_cache_clean( &tft8_dma_wr_high_word, sizeof( tft8_dma_wr_high_word ) );

    // When requests are pending together, the latch (WR high) must win over the
    // next data word; WR low may land before or after the data.
    if ( !tft8_dma_open_stream( &tft8_dma_data, TFT8_DMA_STREAM_DATA, DMA_DATA_ALIGN_BYTES_2, true,
                                DMA_PRIORITY_HIGH ) ||
         !tft8_dma_open_stream( &tft8_dma_wrlo, TFT8_DMA_STREAM_WRLO, DMA_DATA_ALIGN_BYTES_4, false,
                                DMA_PRIORITY_HIGH ) ||
         !tft8_dma_open_stream( &tft8_dma_wrhi, TFT8_DMA_STREAM_WRHI, DMA_DATA_ALIGN_BYTES_4, false,
                                DMA_PRIORITY_VERY_HIGH ) ) {
        return -1;
    }

    if ( DMA_SUCCESS != dma_register_irq_handler( &tft8_dma_wrhi, tft8_dma_on_wrhi, NULL ) ||
         DMA_SUCCESS != dma_set_interrupts( &tft8_dma_wrhi, DMA_EVENT_TRANSFER_COMPLETE | TFT8_DMA_ERROR_EVENTS ) ) {
        return -1;
    }

    // Pacing: counter 0..ARR; overflow = WR high, CCR1 = next data word, CCR3 = WR low.
    clk = tft8_dma_tim1_clock_hz();
    wr_low = tft8_dma_ns_to_ticks( timing->wr_low_ns, clk );
    wr_high = tft8_dma_ns_to_ticks( timing->wr_high_ns, clk );
    hold = tft8_dma_ns_to_ticks( timing->data_hold_ns, clk );
    if ( wr_low < 1u ) wr_low = 1u;
    if ( wr_high < 2u ) wr_high = 2u;
    if ( hold < 1u ) hold = 1u;
    if ( hold >= wr_high ) hold = wr_high - 1u;

    // CH1/CH3 in PWM mode 1 so compare matches raise CC DMA requests (frozen
    // mode raises none). CC1E/CC3E + MOE activate them; the TIM1_CH1/CH3 pins
    // are not in AF mode, so no pin is driven.
    TIM1->CR1 = 0u;
    TIM1->PSC = 0u;
    TIM1->ARR = wr_low + wr_high - 1u;
    TIM1->CCR1 = hold;
    TIM1->CCR3 = wr_high;
    TIM1->CCMR1 = ( TIM1->CCMR1 & ~TIM_CCMR1_OC1M ) | ( 6u << TIM_CCMR1_OC1M_Pos );
    TIM1->CCMR2 = ( TIM1->CCMR2 & ~TIM_CCMR2_OC3M ) | ( 6u << TIM_CCMR2_OC3M_Pos );
    TIM1->CCER |= TIM_CCER_CC1E | TIM_CCER_CC3E;
    TIM1->BDTR |= TIM_BDTR_MOE;

    return 0;
}

void tft8_dma_flush_backend_start( const uint16_t *pixels, uint32_t num_px ) {
    // Sizes in bytes: 16-bit pixel words, 32-bit BSRR writes.
    dma_set_transfer_config( &tft8_dma_data, (uint32_t)pixels, tft8_dma_data_odr,
                             num_px * 2u, DMA_SOURCE_MEMORY_REGION_RAM );
    dma_set_transfer_config( &tft8_dma_wrlo, (uint32_t)&tft8_dma_wr_low_word, tft8_dma_wr_bsrr,
                             num_px * 4u, DMA_SOURCE_MEMORY_REGION_RAM );
    dma_set_transfer_config( &tft8_dma_wrhi, (uint32_t)&tft8_dma_wr_high_word, tft8_dma_wr_bsrr,
                             num_px * 4u, DMA_SOURCE_MEMORY_REGION_RAM );

    // A stream will not start while any of its flags is pending.
    dma_clear_status( &tft8_dma_data, TFT8_DMA_ALL_EVENTS );
    dma_clear_status( &tft8_dma_wrlo, TFT8_DMA_ALL_EVENTS );
    dma_clear_status( &tft8_dma_wrhi, TFT8_DMA_ALL_EVENTS );

    // Arm the streams; each waits for its TIM1 request.
    dma_transfer_start( &tft8_dma_data );
    dma_transfer_start( &tft8_dma_wrlo );
    dma_transfer_start( &tft8_dma_wrhi );

    TIM1->CR1 = 0u;
    TIM1->EGR = TIM_EGR_UG;  // Reload PSC/ARR/CCR shadows, reset CNT.
    TIM1->SR = 0u;           // Drop UG-generated flags.
    TIM1->DIER = TIM_DIER_UDE | TIM_DIER_CC1DE | TIM_DIER_CC3DE;
    TIM1->CR1 = TIM_CR1_CEN;
}

// ----------------------------------------------- PRIVATE FUNCTION DEFINITIONS

static void tft8_dma_on_wrhi( void *context, uint8_t events ) {
    uint8_t errors;

    (void)context;

    // Stop the timebase so no further DMA requests are generated.
    TIM1->CR1 = 0u;
    TIM1->DIER = 0u;

    errors = ( events | dma_get_status( &tft8_dma_data ) | dma_get_status( &tft8_dma_wrlo ) ) &
             TFT8_DMA_ERROR_EVENTS;

    // Disable the streams (also after an error, which leaves them mid-transfer).
    dma_transfer_abort( &tft8_dma_data );
    dma_transfer_abort( &tft8_dma_wrlo );
    dma_transfer_abort( &tft8_dma_wrhi );

    tft8_dma_flush_backend_done( 0 != errors );
}

static bool tft8_dma_open_stream( dma_t *obj, uint8_t stream, dma_data_align_t align,
                                  bool src_inc, dma_priority_t priority ) {
    dma_config_t cfg;

    dma_configure_default( &cfg );
    cfg.module = TFT8_DMA_MODULE;
    cfg.stream = stream;
    cfg.channel = TFT8_DMA_CHANNEL;
    cfg.direction = DMA_DIRECTION_MEMORY_TO_PERIPH;
    cfg.mode = DMA_MODE_NORMAL;
    cfg.priority = priority;
    cfg.src_inc = src_inc;
    cfg.dst_inc = false;
    cfg.data_align_source = align;
    cfg.data_align_destination = align;
    if ( DMA_SUCCESS != dma_open( obj, &cfg ) ) {
        return false;
    }

    // Exactly one item per timer request; kept across reconfiguration.
    return DMA_SUCCESS == dma_set_fifo( obj, false );
}

static uint32_t tft8_dma_tim1_clock_hz( void ) {
    static const uint8_t apb_div[ 8 ] = { 1u, 1u, 1u, 1u, 2u, 4u, 8u, 16u };
    const uint32_t hclk = (uint32_t)( OSC_KHZ ) * 1000u;
    const uint32_t div = apb_div[ ( RCC->CFGR & RCC_CFGR_PPRE2 ) >> RCC_CFGR_PPRE2_Pos ];
    const uint32_t pclk2 = hclk / div;

#if defined(RCC_DCKCFGR1_TIMPRE)
    if ( RCC->DCKCFGR1 & RCC_DCKCFGR1_TIMPRE ) return ( div <= 4u ) ? hclk : 4u * pclk2;
#elif defined(RCC_DCKCFGR_TIMPRE)
    if ( RCC->DCKCFGR & RCC_DCKCFGR_TIMPRE ) return ( div <= 4u ) ? hclk : 4u * pclk2;
#endif
    return ( 1u == div ) ? pclk2 : 2u * pclk2;
}

static uint32_t tft8_dma_ns_to_ticks( uint32_t ns, uint32_t clk_hz ) {
    const uint32_t clk_khz = clk_hz / 1000u;
    return ( ns * clk_khz + 999999u ) / 1000000u;
}

#endif // TFT8_DMA_FLUSH_SUPPORTED

// ------------------------------------------------------------------------- END
