# TFT8 DMA flush engine — design and maintenance

This document is for whoever maintains or extends `MikroSDK.Tft8.DmaFlush` and the SDK changes it depends on. For how to *use* the component see [README.md](README.md); for the list of changes see [the changelog](../../../changelog/unreleased/changelog.md).

## 1. What this is

`MikroSDK.Tft8.DmaFlush` sends RGB565 pixels to an SSD1963 (or any 16-bit 8080-bus controller) without the CPU touching each pixel. A timer generates three DMA requests per pixel:

```
            ┌─────────── one pixel = WR low + WR high ───────────┐
TIM1 count  0 ── CCR1 ──────────── CCR3 ─────────────────── ARR │ 0 …
            │      │                 │                          │
            │      └ DMA: data word → GPIO ODR (data port)      │
            │                        └ DMA: WR low  → GPIO BSRR  │
            └ DMA: WR high → GPIO BSRR (latches the previous pixel)
```

The CPU only opens the write window (`frame_start()`), starts a run and gets a callback when the last pixel is latched. While the DMA sends one buffer, LVGL renders the next one.

Three SDK changes were needed to move this from a project into mikroSDK:

| Change | Location | Why it was needed |
|---|---|---|
| DMA interrupt / status / FIFO API | `drv_dma`, `hal_dma`, STM32 `hal_ll_dma` (`implementation_1`) | The engine needs a transfer-complete interrupt, flag clearing and direct mode. Without an API it had to write DMA registers directly. |
| Shared `lvgl_common.h` state | `components/tft8/common/ssd1963` | The header declared the display pins as `static`, so a second source file (the engine's caller) got its own uninitialized copies. |
| The engine itself | `components/tft8/dma_flush` | Reusable, LVGL-independent, with a stub on MCUs without a backend so display drivers can always link it. |

Four DMA bugs found along the way were fixed in the same change (see the changelog, *Fixes*).

## 2. Why it is built this way

These decisions are deliberate. Changing one usually breaks something that is not obvious from the code.

### DMA API

| Decision | Reason |
|---|---|
| **Interrupt/FIFO settings are stored per stream in `hal_ll_dma` and re-applied on every reconfiguration.** | `dma_set_transfer_config()` aborts the stream and re-runs mode/direction/priority init. That cleared the interrupt enables and turned the FIFO back on **on every transfer**. A user who enabled direct mode once silently ran in FIFO mode from the second transfer on. |
| **`*_register_irq_handler()` lives in its own source file at every layer** (`drv_dma_irq.c`, `hal_dma_irq.c`, `hal_ll_dma_irq.c`). | The SDK defines the `DMAx_StreamY_IRQHandler` functions. Static-library linking pulls in a whole object file when any symbol in it is referenced. In separate files, the handlers are linked only into firmware that registers a callback; firmware that defines its own DMA handlers keeps working. |
| **No change to `dma_t` / `hal_dma_t` / `hal_ll_dma_t` or their config structures.** | The three layers cast these objects into each other. New state lives in arrays inside `hal_ll_dma.c`. |
| **`HAL_LL_DMA_EXT_SUPPORTED`** in the target's `hal_ll_dma.h`; drv/hal return `DMA_ERROR` without it. | Other targets (`implementation_2`, Tiva, NXP, PIC32, GD32, PIC18) keep building without any change to their code. |
| **NVIC via `hal_ll_core_enable_irq()`** with vector numbers (IRQn + 16), same convention as the UART handlers. | `mcu.h` has the CMSIS core header disabled, so `NVIC_EnableIRQ()` does not exist. |

### Engine

| Decision | Reason |
|---|---|
| **LVGL-independent; completion is a callback.** | mikroSDK does not depend on LVGL. The caller calls `lv_display_flush_ready()`. |
| **Built for every MCU/toolchain that has `MikroSDK.LVGL.Common`; stub backend where there is no real one.** | Display drivers can always link it and fall back to the CPU path at run time instead of failing to build. |
| **Direct mode (`dma_set_fifo(false)`).** | One timer request must move exactly one item. With the FIFO, data and WR writes can drift apart. |
| **Latch-first priorities: WR high `VERY_HIGH`, data and WR low `HIGH`.** | When requests are pending together, the previous pixel must be latched before the next word reaches the bus. WR low may land before or after the data — the SSD1963 samples on the rising edge. |
| **WR timing defaults per family, measured on hardware** (F2/F4 60/60/15 ns, F7 32/32/9 ns). | At 32 ns an STM32F407ZG drew smeared, ghosted pixels; an STM32F429NI did too once LVGL was compiled `-O2`. The CPU rendering into the same SRAM delays the DMA, and the data word lands after the latch. **No DMA error flag is raised in that case** — only slowing the clock reveals it. |
| **Timings in nanoseconds, converted with the real timer clock** (`OSC_KHZ` + RCC APB2 prescaler/TIMPRE). | The same defaults work across clock configurations. |
| **`TFT8_DMA_FLUSH_BUFFER_ATTR`: NOBITS `.dma_buffer` section on STM32F7.** | F7 RAM starts with DTCM, which the DMA cannot reliably read (corrupt panel). The section is placed in SRAM1 by the application's linker option. A plain named section would be PROGBITS: 64 KB of zeros with a RAM load address in the `.hex`. |
| **`tft8_dma_flush_init()` refuses to start if its own DMA data is unreachable** (F7 DTCM, F4 CCM). | A missing linker option otherwise shows up as a garbage screen instead of a slower but correct one. |
| **WR words assigned at run time, never via initializers.** | The NOBITS section is not initialized at startup; an initializer there is silently lost (WR never toggles, blank panel). |
| **Links `MikroSDK.Driver` always, `MikroSDK.Driver.DMA` only with the real backend.** | `MikroSDK.Driver` provides `drv_name.h` (`err_t`) on every target; the DMA driver does not exist everywhere. |

### `lvgl_common`

| Decision | Reason |
|---|---|
| **State declared `extern` in the header, defined once in `src/lvgl_common.c`; library instead of header-only.** | Every source file including the header now uses the same pins. The inline API is unchanged, so existing display drivers need no edits. |

## 3. Invariants — check these in every change

1. **The CMake backend condition and `TFT8_DMA_FLUSH_SUPPORTED` must agree.**
   `dma_flush/CMakeLists.txt` (`TOOLCHAIN_LANGUAGE`/`MCU_NAME` → backend source + DMA dependency) and `include/tft8_dma_flush.h` (`__GNUC__` + family macros) express the same rule twice. If they drift you get either an unused backend or undefined references.
2. **Interrupt registration stays in separate source files** at drv, hal and hal_ll level. Never move `*_register_irq_handler()` into `drv_dma.c`, `hal_dma.c` or `hal_ll_dma.c`.
3. **New `hal_ll_dma_*` functions only behind `HAL_LL_DMA_EXT_SUPPORTED`**, and the drv/hal wrappers must still compile and return an error when it is not defined.
4. **No layout changes to the DMA object/config structures** without changing all three layers together.
5. **Anything that reconfigures a stream must re-apply the stored interrupt and FIFO settings** (`hal_ll_dma_apply_interrupts()`, FIFO handling in `hal_ll_dma_init_hw()`).
6. **DMA source data (pixel buffers, WR words) must be DMA-reachable** and must not rely on initializers in a NOBITS section.
7. **Timing defaults change only with a hardware test** that includes a busy CPU (LVGL animations with optimized LVGL), not a static image.
8. **`lvgl_common.h` must not get `static` variables again.** New shared state goes into `lvgl_common.c`.

## 4. Adding an MCU family

A new part of an already-supported family (STM32F2/F4/F7) needs nothing, provided its MCU card maps the TFT data bus to one full 16-bit port and `dma_definitions.h` exists for it. For a new family:

1. **DMA driver support** — in that target's `hal_ll_dma`: implement `hal_ll_dma_set_interrupts`, `hal_ll_dma_get_status`, `hal_ll_dma_clear_status`, `hal_ll_dma_set_fifo` (on a DMA without a FIFO every transfer is already one item per request, so `false` can simply succeed), add an `*_irq.c` with the stream/channel handlers and `hal_ll_dma_register_irq_handler()`, keep settings across reconfiguration, and define `HAL_LL_DMA_EXT_SUPPORTED`.
2. **Backend** — `src/tft8_dma_flush_<family>.c`, guarded by `#if TFT8_DMA_FLUSH_SUPPORTED` and the family, implementing the contract in `src/tft8_dma_flush_backend.h`:
   - `tft8_dma_flush_backend_max_px` — the DMA transfer-count limit in pixels,
   - `tft8_dma_flush_backend_default_timing()`,
   - `tft8_dma_flush_backend_init()` — timer, request routing, interrupt; return non-zero on any failure,
   - `tft8_dma_flush_backend_start()` — one run; call `tft8_dma_flush_backend_done(error)` from the interrupt when the last pixel is latched (also after an error, or the caller hangs).
   On families with a parallel-bus peripheral (PIC32 PMP, NXP FlexIO/FlexBus, Tiva EPI, FMC/FSMC wiring) one DMA stream into the peripheral replaces the timer and the three streams.
3. **Header** — extend `TFT8_DMA_FLUSH_SUPPORTED`; add a `TFT8_DMA_FLUSH_BUFFER_ATTR` variant if the family has RAM the DMA cannot read.
4. **Core** — add the family's unreachable ranges to `tft8_dma_flush_is_reachable()` in `src/tft8_dma_flush.c`. D-cache cleaning already covers every Cortex-M7.
5. **CMake** — select the new backend source and `MikroSDK.Driver.DMA` in `dma_flush/CMakeLists.txt` (invariant 1).
6. **Linker** — if the family needs a dedicated DMA RAM section, add it to the linker scripts in `core_packages` (`ARM/gcc_clang/linker_scripts/…`); until then document the application linker option.
7. **Timing** — measure on hardware (section 6) and set the defaults.

The display drivers (`display_lvgl.c` in the LVGL templates/projects) need no change: once `TFT8_DMA_FLUSH_SUPPORTED` is 1 for the family, the same code uses DMA.

## 5. Testing checklist

**Build** (GCC, NECTO toolchain):

- [ ] A supported family (e.g. STM32F429NI, UNI-DS v8, TFT board 5/7): `lib_hal_ll_dma`, `lib_hal_dma`, `lib_drv_dma`, `lib_lvgl_common`, `lib_tft8_dma_flush` build; the dma_flush library references `dma_*` functions.
- [ ] An unsupported family on the same board (e.g. STM32F302VC, MCU card 11): `lib_tft8_dma_flush` builds with only `tft8_dma_flush_none.c` and has no `dma_*` references.
- [ ] Changed sources are clean with `-Wall -Wextra` (pre-existing header warnings aside).

**Link** (against the built libraries, the core library and the generated linker script):

- [ ] Firmware using the engine: `DMAx_StreamY_IRQHandler` of the WR-high stream is a strong symbol from `hal_ll_dma_irq.c`, and its vector-table entry points to it.
- [ ] Firmware using DMA without a callback: all DMA stream handlers stay the startup file's weak defaults.

**Hardware** (LVGL project, double-buffered partial rendering, LVGL compiled `-O2`):

- [ ] Static screen, animations, screen switches and scrolling are clean.
- [ ] `tft8_dma_flush_get_error_count()` stays 0.
- [ ] A/B against the CPU path (`DISP_USE_DMA=0`) and a slower timing — if the slower timing fixes artifacts, the default is too fast for that family.
- [ ] On new families: WR waveform on a scope against the controller's WR-cycle spec.

## 6. Troubleshooting

| Symptom | Likely cause | Check |
|---|---|---|
| Screen layout correct, pixels smeared/ghosted, `error_count` 0 | DMA throughput: data word lands after the latch (bus contention with CPU rendering) | Slower timing fixes it → raise the family default |
| Whole screen garbage (STM32F7) | Buffers in DTCM: `.dma_buffer` linker option missing | Linker map: `.dma_buffer` at `0x20020000`, not `0x2000xxxx`; init should have refused — check the caller ignores the return value |
| Blank panel, flush never completes | WR words zero (initializer in NOBITS section) or interrupt not firing | WR words assigned in init; `dma_set_interrupts()` called after `dma_register_irq_handler()` |
| Only the first flush works | Stream flags left pending; a stream cannot start while any flag is set | `dma_clear_status()` before `dma_transfer_start()` |
| `multiple definition of DMAx_StreamY_IRQHandler` | Application defines the handler and also registers a callback for that stream | Use one or the other |
| `undefined reference to dma_*` / `drv_name.h` not found | CMake backend condition and `TFT8_DMA_FLUSH_SUPPORTED` disagree, or `MikroSDK.Driver` dependency missing | Invariant 1 |
| `error_count` climbing | DMA transfer or direct-mode error (request arrived before the previous one was served) | Slower timing; check DMA priorities and other DMA users on the same controller |

## 7. Known limitations and follow-ups

- **Timer has no SDK API.** Backends program the timer directly and compute its clock from RCC. A `hal_ll_tim` extension for DMA-request generation (period/compare in ns, UDE/CCxDE) and the timer kernel clock would remove most per-family code.
- **CMSIS core header disabled in `mcu.h`.** The engine writes `SCB->DCCMVAC` directly for D-cache cleaning; LVGL's DMA2D driver and tinyusb (`__NOP`) also need the core header.
- **No `.dma_buffer` in the generated linker scripts** (they live in `core_packages`); STM32F7 applications must add `LINKER:--section-start=.dma_buffer=0x20020000`.
- **The support rule is written twice** (CMake + header, invariant 1). Better: CMake passes `TFT8_DMA_FLUSH_BACKEND=<name>` and the header derives `TFT8_DMA_FLUSH_SUPPORTED` from it.
- **Per-family constants are literals in the backend** (request routing, IRQ vectors, timer instance). A per-family table would make sibling families (F1 → GD32) mostly data.
- **`implementation_2` (DMAMUX/channel STM32) has no interrupt/status/FIFO API**, and its DMA2 DMAMUX slot offset is hard-coded (`0x20`) because `DMA_NUM_OF_STREAMS` is not a reliable per-part channel count.
- **GCC only.** mikroC builds get the stub; supporting it needs replacements for the GCC attributes and inline asm.
- **ILI9341 `lvgl_common.h`** (`components/tft7/common/ili9341`) still has the `static` state problem.
- **Hardware coverage:** the engine ran on STM32F767BI, F429NI and F407ZG (UNI-DS v8, SSD1963). `implementation_2` fixes were reviewed but not compiled.

## 8. File map

```
components/tft8/dma_flush/
├── CMakeLists.txt                       backend selection (invariant 1), dependencies
├── README.md                            usage
├── MAINTENANCE.md                       this file
├── include/tft8_dma_flush.h             public API, TFT8_DMA_FLUSH_SUPPORTED, TFT8_DMA_FLUSH_BUFFER_ATTR
└── src/
    ├── tft8_dma_flush.c                 core: chunking, D-cache clean, reachability, completion
    ├── tft8_dma_flush_backend.h         core ↔ backend contract
    ├── tft8_dma_flush_stm32_stream.c    STM32F2/F4/F7 backend (TIM1 + DMA2 S1/S5/S6, ch 6)
    └── tft8_dma_flush_none.c            stub backend (init fails → CPU path)

components/tft8/common/ssd1963/
├── include/lvgl_common.h                shared state now extern
└── src/lvgl_common.c                    the single definition of that state

drv/lib/include/drv_dma.h                DMA_EVENT_*, dma_set_interrupts/… API
drv/lib/src/lib_drv_dma/drv_dma_irq.c    dma_register_irq_handler (separate on purpose)
hal/lib/src/lib_hal_dma/hal_dma_irq.c    hal_dma_register_irq_handler (separate on purpose)
targets/arm/mikroe/stm32/include/dma/hal_ll_dma.h                    HAL_LL_DMA_EXT_SUPPORTED + API (F2/F4/F7)
targets/arm/mikroe/stm32/src/dma/implementation_1/hal_ll_dma.c       per-stream state, status/clear/fifo/interrupts
targets/arm/mikroe/stm32/src/dma/implementation_1/hal_ll_dma_irq.c   stream IRQ handlers + registration
```
