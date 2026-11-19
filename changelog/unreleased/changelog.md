<p align="center">
  <img src="http://www.mikroe.com/img/designs/beta/logo_small.png?raw=true" alt="MikroElektronika"/>
</p>

---

**[BACK TO MAIN FILE](../../changelog.md)**

---

# `unreleased` — DMA interrupts/status/FIFO, STM32 DMA fixes, LVGL common state, TFT8 DMA flush engine

+ branch: `wip/marko.lukic/tft_dma_flush` (based on master after the 2.20.2 release)
+ origin: a timer-paced DMA display driver for SSD1963 TFT boards (UNI-DS v8, STM32F767BI / F429NI / F407ZG) that had to bypass mikroSDK for most of its DMA handling. These changes move that support into the SDK.

## Changes

+ [New Features](#new-features)
  + [DMA: interrupts, status and FIFO control](#dma-interrupts-status-and-fifo-control)
  + [TFT8 DMA flush engine (`MikroSDK.Tft8.DmaFlush`)](#tft8-dma-flush-engine-mikrosdktft8dmaflush)
+ [Improvements](#improvements)
  + [`MikroSDK.LVGL.Common`: one shared display/touch state](#mikrosdklvglcommon-one-shared-displaytouch-state)
+ [Fixes](#fixes)
+ [Compatibility](#compatibility)
+ [Verification](#verification)
+ [Not done / follow-ups](#not-done--follow-ups)

### New Features

#### DMA: interrupts, status and FIFO control

New driver API (`drv_dma.h`), forwarded through `hal_dma` to `hal_ll_dma`:

| Function | Purpose |
|---|---|
| `err_t dma_set_interrupts( dma_t *obj, uint8_t events )` | Enable stream interrupts (`DMA_EVENT_*`) and the stream's NVIC line; `0` disables. |
| `err_t dma_register_irq_handler( dma_t *obj, dma_isr_t handler, void *context )` | Register a callback; the SDK then provides the stream's `DMAx_StreamY_IRQHandler`, clears the reported flags and calls `handler( context, events )`. |
| `uint8_t dma_get_status( dma_t *obj )` | Pending `DMA_EVENT_*` flags. |
| `err_t dma_clear_status( dma_t *obj, uint8_t events )` | Clear flags (a stream cannot start while any is pending). |
| `err_t dma_set_fifo( dma_t *obj, bool enable )` | FIFO mode or direct mode (one item per peripheral request, needed for timer-paced transfers). |

Events: `DMA_EVENT_TRANSFER_COMPLETE`, `DMA_EVENT_HALF_TRANSFER`, `DMA_EVENT_TRANSFER_ERROR`, `DMA_EVENT_DIRECT_MODE_ERROR`, `DMA_EVENT_FIFO_ERROR` (same values at the `HAL_DMA_EVENT_*` / `HAL_LL_DMA_EVENT_*` levels).

+ **Settings persist across reconfiguration.** `dma_set_transfer_config()` aborts the stream and re-runs mode/direction/priority initialization, which cleared the stream's interrupt enables and reset FIFO mode on every call. Interrupt and FIFO settings are now kept per stream in `hal_ll_dma` and re-applied by `init_hw` and `set_parameters`.
+ **Interrupt handlers are linked only when used.** `dma_register_irq_handler()` lives in its own source file at each layer (`drv_dma_irq.c`, `hal_dma_irq.c`, `hal_ll_dma_irq.c`). A firmware that never registers a callback does not pull the SDK's DMA handlers in, so existing applications that define their own `DMAx_StreamY_IRQHandler` are unaffected. Applications that do register a callback must not define that stream's handler themselves.
+ **NVIC through `hal_ll_core_enable_irq()`**, using the stream vector numbers (identical on STM32F2/F4/F7: DMA1 27–33, 63; DMA2 72–76, 84–86).
+ **Availability:** implemented for STM32F2/F4/F7 (`implementation_1`), signalled by `HAL_LL_DMA_EXT_SUPPORTED` in the STM32 `hal_ll_dma.h`. On every other target the new functions compile and return `DMA_ERROR` (`dma_get_status()` returns 0); no other target implementation was modified.

New / changed files:

```
drv/lib/include/drv_dma.h                                   API + DMA_EVENT_* + dma_isr_t
drv/lib/src/lib_drv_dma/drv_dma.c                           set_interrupts/get_status/clear_status/set_fifo
drv/lib/src/lib_drv_dma/drv_dma_irq.c              (new)    dma_register_irq_handler
hal/lib/include/hal_dma.h                                   API + HAL_DMA_EVENT_* + hal_dma_isr_t
hal/lib/src/lib_hal_dma/hal_dma.c                           forwarding (#ifdef HAL_LL_DMA_EXT_SUPPORTED)
hal/lib/src/lib_hal_dma/hal_dma_irq.c              (new)    hal_dma_register_irq_handler
targets/arm/mikroe/stm32/include/dma/hal_ll_dma.h           F2/F4/F7 API + HAL_LL_DMA_EXT_SUPPORTED
targets/arm/mikroe/stm32/src/dma/implementation_1/hal_ll_dma.c       per-stream state, status/clear/fifo/interrupts
targets/arm/mikroe/stm32/src/dma/implementation_1/hal_ll_dma_irq.c   (new) stream IRQ handlers + registration
targets/arm/mikroe/stm32/src/dma/CMakeLists.txt             adds hal_ll_dma_irq.c for implementation_1
```

Example:

```c
static void on_dma( void *context, uint8_t events ) {
    if ( events & DMA_EVENT_TRANSFER_COMPLETE ) { /* ... */ }
}

dma_open( &dma, &cfg );
dma_set_fifo( &dma, false );                      // direct mode
dma_register_irq_handler( &dma, on_dma, NULL );
dma_set_interrupts( &dma, DMA_EVENT_TRANSFER_COMPLETE | DMA_EVENT_TRANSFER_ERROR );
```

#### TFT8 DMA flush engine (`MikroSDK.Tft8.DmaFlush`)

New component `components/tft8/dma_flush` (library `lib_tft8_dma_flush`, header installed to `include/components/tft8_dma_flush`). It sends RGB565 pixel runs to an SSD1963 (or any 8080 16-bit controller) with no CPU involvement: TIM1 paces three DMA2 streams that write the data port and toggle WR. See [its README](../../components/tft8/dma_flush/README.md) for usage and [MAINTENANCE.md](../../components/tft8/dma_flush/MAINTENANCE.md) for design rationale, invariants and how to add MCU families.

+ LVGL-independent: completion is a callback; with LVGL call `lv_display_flush_ready()` there.
+ Uses only the driver API above for DMA (open, direct mode, interrupts, status). The timer is still programmed directly — there is no timer API for DMA request generation.
+ Per-family WR timing defaults, measured on hardware: **STM32F2/F4 60/60/15 ns**, **STM32F7 32/32/9 ns** (WR low / WR high / data hold). At 32 ns an STM32F407ZG — and an STM32F429NI once LVGL was compiled `-O2` — showed smeared pixels with no DMA error flag: CPU rendering into the same SRAM delays the DMA so the data word lands after the latch.
+ Stream priorities latch-first (WR high `VERY_HIGH`, data / WR low `HIGH`).
+ `TFT8_DMA_FLUSH_BUFFER_ATTR` places buffers where the DMA can read them (STM32F7: NOBITS `.dma_buffer`, see follow-ups); `tft8_dma_flush_init()` refuses to start if the engine's own DMA data is not reachable (F7 DTCM / F4 CCM), so the caller falls back to the CPU path instead of drawing garbage.
+ `tft8_dma_flush_get_error_count()`: writes that ended with a transfer or direct-mode error.
+ Built wherever `MikroSDK.LVGL.Common` is (SSD1963 TFT boards), for every MCU and toolchain. GCC on STM32F2/F4/F7 compiles the DMA backend and links `MikroSDK.Driver.DMA`; everything else compiles only `tft8_dma_flush_none.c` (no DMA dependency, no GCC attributes or ARM asm): `TFT8_DMA_FLUSH_SUPPORTED` is 0, init fails, callers use `write_array_data()`.

### Improvements

#### `MikroSDK.LVGL.Common`: one shared display/touch state

`components/tft8/common/ssd1963/include/lvgl_common.h` declared its state as `static` in the header (`pin_cs`, `pin_wr`, `pin_dc`, `port_high`, `port_low`, `display_driver`, `tp_interface`, `tp`, `port_16bit_single`, `port_16bit_dual`, `shift_data_port_low/high`). Every `.c` file that included it got its own, uninitialized copy, so only the file that called `display_configure()` had working pins — a second module (e.g. a DMA flush driver) could not use them.

+ The header now declares them `extern`; they are defined once in the new `src/lvgl_common.c`.
+ `MikroSDK.LVGL.Common` is now a static library (`mikrosdk_add_library`) instead of an interface library; links `PUBLIC` to `MikroC.Core`, `MikroSDK.TouchController`, `MikroSDK.Ssd1963` as before.
+ The inline API (`display_configure()`, `frame_start()`, `write_array_data()`, the `CS_*`/`WR_*`/`DC_*` macros, `check_touchpad()` …) is unchanged; existing code including the header needs no change.

### Fixes

+ **STM32F2/F4/F7 `hal_ll_dma_transfer_abort()` cleared the wrong flags.** It selected LISR/LIFCR vs HISR/HIFCR with `channel / 4` instead of `stream / 4`, and shifted the clear mask by the stream number instead of the flag-group offset (0, 6, 16, 22). Aborting a stream could leave its own flags set (so it would not restart) and clear another stream's. The clear mask also no longer writes the reserved bit 1 of each group (`0x3F` → `0x3D`).
+ **STM32 `implementation_2` CR rebuild did not clear the old configuration.** The clear mask OR-ed the bit *positions* (`HAL_LL_DMA_CCR_*_BIT`, e.g. 0, 2, 6) instead of `1 << position`, so DIR/CIRC/PINC/MINC/M2M and the interrupt enables survived a reconfiguration. (Side effect of the fix: reconfiguring an `implementation_2` channel now really clears its interrupt enables, as `implementation_1` already did through `abort`.)
+ **STM32 DMAMUX request selection OR-ed into the previous request** (`dmamux_cr |= channel`). `DMAREQ_ID` is a field; it is now replaced (mask `0xFF`; 7 bits on G0/G4/L4+, 8 on H7).
+ **STM32F0/L0 CSELR selection OR-ed into the previous one** (`cselr |= channel << ...`). The 4-bit `CxS` field is now replaced.

### Compatibility

+ No structure layout changes (`dma_t` / `hal_dma_t` / `hal_ll_dma_t` and their configs are unchanged; the drv/hal/hal_ll objects are still cast into each other).
+ Existing DMA users see one behaviour change on `implementation_2` targets (interrupt enables cleared on reconfigure, see Fixes) and corrected flag clearing on F2/F4/F7 abort.
+ `MikroSDK.LVGL.Common` becomes a library to link (CMake consumers already link the target, so nothing changes for them). Code that relied on per-file copies of its state — none known — would now share one.

### Verification

Built with the NECTO GCC toolchain (arm-none-eabi 14.2.1) for STM32F429NI / UNI-DS v8 / TFT board 5, Debug:

+ `lib_hal_ll_dma`, `lib_hal_dma`, `lib_drv_dma`, `lib_lvgl_common`, `lib_tft8_dma_flush` build; changed/new sources are clean with `-Wall -Wextra` (remaining warnings are pre-existing ones from SDK headers, e.g. `__weak` redefined, and the `interrupt` attribute FP-register note that the existing UART handlers produce as well).
+ Link test 1 (uses `MikroSDK.Tft8.DmaFlush`): links; `DMA2_Stream5_IRQHandler` is the SDK's handler (vector 84 → `0x08001F32`).
+ Link test 2 (plain `dma_open` / `dma_transfer_start`, no callback): links; all DMA stream handlers remain the startup file's weak defaults — the SDK handlers are not pulled in.
+ **Not verified:** `implementation_2` was not compiled (no G0/G4/L4/H7/F0/L0 configuration available); its changes were reviewed only. Nothing was run on hardware from this SDK build — the engine's behaviour (timing defaults, priorities) comes from the same code running in a project on STM32F767BI, F429NI and F407ZG.

### Not done / follow-ups

| Item | Why | Suggested follow-up |
|---|---|---|
| Timer API for DMA request generation (period/compare in ns, UDE/CCxDE, timer kernel clock) | No existing timer abstraction to extend; engine programs TIM1 directly | `hal_ll_tim` extension; also expose the APB timer clock instead of each user reading RCC |
| CMSIS core header in `mcu.h` (`core_cm4.h`/`core_cm7.h` is commented out) | Touches every MCU header | Enable it (or add `hal_ll_core` cache-maintenance functions); the engine's D-cache clean still writes `SCB->DCCMVAC` directly; LVGL's DMA2D driver also needs these headers |
| `.dma_buffer` section in generated linker scripts | Scripts live in `core_packages` (`ARM/gcc_clang/linker_scripts/stm/`), not in this repository | Add a NOBITS `.dma_buffer` in DMA-reachable RAM per family (F7: SRAM1 0x20020000; H7: AXI/D2); until then F7 applications pass `LINKER:--section-start=.dma_buffer=0x20020000` |
| DMAMUX slot for DMA2 on `implementation_2` | Offset hard-coded `0x20` (8 DMA1 channels); `DMA_NUM_OF_STREAMS` per part is not a reliable channel count (e.g. 94 on STM32L4R5) | Per-part DMA1 channel count in `dma_definitions.h` |
| `implementation_2` interrupt/status/FIFO support | Different register layout (CCR/ISR per channel, no FIFO) | Implement `hal_ll_dma_set_interrupts/get_status/clear_status` there and define `HAL_LL_DMA_EXT_SUPPORTED` |
| Same `static` state in `components/tft7/common/ili9341/include/lvgl_common.h` | Not used by the originating project | Apply the same `extern` + `lvgl_common.c` change |
| Engine backends for other families (DMAMUX STM32, PIC32 PMP, NXP FlexIO, FMC/FSMC boards) | Out of scope | Implement `tft8_dma_flush_backend_*` per family |
