# TFT8 DMA flush engine (`MikroSDK.Tft8.DmaFlush`)

Design decisions, invariants, adding MCU families and testing: see [MAINTENANCE.md](MAINTENANCE.md).

Sends RGB565 pixels to a 16-bit parallel (8080) TFT controller such as the SSD1963 without CPU involvement. A timer paces three DMA streams: one puts each pixel word on the data port, two drive the WR strobe low and high. The CPU is free to render the next buffer while the current one is sent.

## Requirements

- The 16 data lines are one whole GPIO port (`port_16bit_single` in `lvgl_common.h`). Other bus layouts must use the CPU (`write_array_data()`).
- WR is a GPIO pin. CS/DC and the write window (`frame_start()`) are handled by the caller.
- Supported: STM32F2/F4/F7 with GCC (TIM1 + DMA2 Stream1/5/6, channel 6). `TFT8_DMA_FLUSH_SUPPORTED` is 1 there.
- Everywhere else (other MCUs, mikroC) the library is still built - wherever `MikroSDK.LVGL.Common` is - with a stub backend: `TFT8_DMA_FLUSH_SUPPORTED` is 0 and `tft8_dma_flush_init()` fails. A display driver can therefore always link it and fall back to the CPU path (see the example).
- Pixel buffers must be DMA-reachable: declare them with `TFT8_DMA_FLUSH_BUFFER_ATTR`. On STM32F7 also link with `LINKER:--section-start=.dma_buffer=0x20020000` (the default RAM start is DTCM, which the DMA cannot reliably read).
- The engine uses TIM1 and DMA2 streams 1, 5 and 6, and provides `DMA2_Stream5_IRQHandler` — don't use those elsewhere.

## API

```c
void     tft8_dma_flush_default_timing( tft8_dma_flush_timing_t *timing );
err_t    tft8_dma_flush_init( const tft8_dma_flush_hw_t *hw, const tft8_dma_flush_timing_t *timing,
                              tft8_dma_flush_done_t done, void *context );
void     tft8_dma_flush_write( const uint16_t *pixels, uint32_t num_px );   // async, done() at the end
bool     tft8_dma_flush_is_reachable( const void *addr, uint32_t size );
uint32_t tft8_dma_flush_get_error_count( void );
```

`done` is called from the DMA interrupt once all pixels are latched. Writes longer than one DMA transfer (65535 pixels) are split internally.

## WR timing

| Family | WR low / WR high / data hold | Pixel rate |
|---|---|---|
| STM32F2, STM32F4 | 60 / 60 / 15 ns | ~7 MHz |
| STM32F7 | 32 / 32 / 9 ns | ~15 MHz |

Converted to timer ticks from the real TIM1 clock (`OSC_KHZ` and the RCC APB2 prescaler/TIMPRE). On F2/F4 the CPU rendering into the same SRAM delays the DMA; at 32 ns the data word lands after the latch (smeared pixels, no DMA error flag). Pass your own `tft8_dma_flush_timing_t` to tune a board, and check it on a scope.

## Example with LVGL 9 and `lvgl_common.h`

```c
#include "lvgl.h"
#include "lvgl_common.h"
#include "tft8_dma_flush.h"

#define BUF_LINES 20
static TFT8_DMA_FLUSH_BUFFER_ATTR uint16_t buf_1[ _TFT_WIDTH_ * BUF_LINES ];
static TFT8_DMA_FLUSH_BUFFER_ATTR uint16_t buf_2[ _TFT_WIDTH_ * BUF_LINES ];
static bool dma_ready;

static void flush_done( void *context ) {
    display_deselect();                                  // CS high
    lv_display_flush_ready( (lv_display_t *)context );
}

static void disp_flush( lv_display_t *display, const lv_area_t *area, uint8_t *px_map ) {
    /* ... clip to the screen, compute act_x1/act_y1/act_y2/act_w as before ... */
    set_column();
    set_page();
    frame_start( start_column, end_column, start_page, end_page );

    if ( dma_ready && port_16bit_single && act_w == full_w &&
         act_x1 == area->x1 && act_y1 == area->y1 && act_y2 == area->y2 ) {
        tft8_dma_flush_write( (uint16_t *)px_map, (uint32_t)act_w * ( act_y2 - act_y1 + 1 ) );
        return;                                          // flush_done() finishes it
    }
    /* CPU path: write_array_data() per line, display_deselect(), lv_display_flush_ready() */
}

void lv_port_disp_init( void ) {
    display_configure();
    lv_display_t *display = lv_display_create( _TFT_WIDTH_, _TFT_HEIGHT_ );
    lv_display_set_flush_cb( display, disp_flush );

    tft8_dma_flush_hw_t hw = {
        .wr_base   = pin_wr.pin.base,
        .wr_mask   = pin_wr.pin.mask,
        .data_base = port_low.port.base,
    };
    dma_ready = ( 0 == tft8_dma_flush_init( &hw, NULL, flush_done, display ) );

    lv_display_set_buffers( display, buf_1, buf_2, sizeof( buf_1 ), LV_DISPLAY_RENDER_MODE_PARTIAL );
}
```

Link `MikroSDK.Tft8.DmaFlush` (on supported families it pulls in `MikroSDK.Driver.DMA`).

To also build against SDKs that do not ship the component at all, find it optionally and tell the code whether it is there:

```cmake
find_package_me(MikroSDK.Tft8.DmaFlush)            # optional: no error if missing
if(TARGET MikroSDK.Tft8.DmaFlush)                  # find_package_me is a function: test the target, not _FOUND
    target_link_libraries(<app> PUBLIC MikroSDK.Tft8.DmaFlush)
    target_compile_definitions(<app> PRIVATE DISP_HAS_TFT8_DMA_FLUSH=1)
endif()
```

and include `tft8_dma_flush.h` only under `#if DISP_HAS_TFT8_DMA_FLUSH`.

## Migrating a project-local copy

Projects that carried this engine in their own sources (`display_dma.c`, `display_dma_stm32_stream.c`, `display_dma_port.h`, `display_dma_backend.h`) can drop them:

- remove the project's `DMA2_Stream5_IRQHandler` (the SDK now provides it),
- replace `disp_dma_init()` / `disp_dma_flush()` / `disp_dma_get_buffers()` with `tft8_dma_flush_init()` / `tft8_dma_flush_write()` and buffers declared with `TFT8_DMA_FLUSH_BUFFER_ATTR`,
- the deselect callback is no longer needed: `lvgl_common.h` state is now shared, so call `display_deselect()` directly in the done callback,
- `DISP_WR_*_NS` overrides become a `tft8_dma_flush_timing_t` passed to init; `disp_dma_error_count` becomes `tft8_dma_flush_get_error_count()`,
- keep the F7 `--section-start=.dma_buffer=0x20020000` link option.
