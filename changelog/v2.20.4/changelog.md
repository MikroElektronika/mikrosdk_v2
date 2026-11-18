<p align="center">
  <img src="http://www.mikroe.com/img/designs/beta/logo_small.png?raw=true" alt="MikroElektronika"/>
</p>

---

**[BACK TO MAIN FILE](../../changelog.md)**

---

# `v2.20.4`

+ released: 2026-11-24

## Changes

- [`v2.20.4`](#v2204)
  - [Changes](#changes)
    - [New features](#new-features)
      - [mikroSDK](#mikrosdk)
    - [Fixes](#fixes)
    - [NEW HARDWARE](#new-hardware)

### New features

#### mikroSDK

+ **Firmware trace library (`MikroSDK.Trace`)**
  + Records driver activity on the device and hands it to the debugger, so NECTO Studio can show it on a timeline.
  + Key changes:
    + Added the `MikroSDK.Trace` platform library (`trace.h`); linking it is all an application needs, the trace starts with the first recorded event.
    + Recorded events: I2C Master and SPI Master transfers, SPI chip select changes, UART writes and reads, 1-Wire operations (reset, ROM commands, byte writes and reads), ADC reads (raw and voltage), GPIO output writes and GPIO input level changes, plus named values through `trace_value()`.
    + Trace format version 4 (1-Wire records, injected events, bus bursts); NECTO Studio needs a trace decoder that reads version 4.
    + Fault injection while debugging: NECTO Studio can make an I2C device stop answering, hold SPI MISO at a byte, hold a GPIO input at a level, force an ADC value, and take the devices off a 1-Wire bus. The debugger writes the faults to the trace library (`__traceFaults`); the trace's driver wrappers apply them before or after each call, and the trace marks the calls a fault changed.
    + Records are kept in a RAM buffer (512 bytes by default, `TRACE_BUFFER( size )` to change it) and handed to the debugger when the buffer is full, on `trace_flush()`, or every 500 ms of program time (`trace_set_flush_interval()`).
    + Fast GPIO writes (a display strobe, a bit-banged bus) and fast bus transfers (a display filled pixel by pixel over SPI) are coalesced into bursts, so they do not stop the program over and over.
    + Time base: the core cycle counter (DWT CYCCNT on Cortex-M3 and newer, `mcycle` on RISC-V, CP0 Count on PIC32); Cortex-M0/M0+ keep the order of events but not the timing. Applications can supply their own timer through the weak `trace_ticks()` and `trace_tick_hz()`.
    + The GPIO Out, GPIO In, I2C Master, SPI Master, UART, ADC and 1-Wire drivers are traced through linker wrapping (`--wrap`): linking `MikroSDK.Trace` sends their calls through the trace, and the drivers themselves are unchanged. Projects without the trace library build exactly as before, and outside NECTO Studio (no `NECTO_APPLICATION_DIR`) the library is not built at all. Flattened GPIO macros (`FLATTEN_ME_LEVEL_HIGH`) report to the trace only when `MIKROSDK_TRACE` is defined, which the library does for the application.
    + The library is built for ARM (GCC and Clang), RISC-V (GCC) and PIC32 (XC32); the architecture-specific code (interrupt lock, cycle counter) is in `trace_port.h`. mikroC is not supported (its linker cannot wrap symbols), nor are dsPIC/PIC24 (XC16) and XC8.
    + Added validation test under `tests/trace`.
+ **Timestamped plot**
  + Added `plot_ts()` to `plot.h`: like `plot()`, with the time the value was taken on the device, so NECTO Studio keeps the real spacing of the values.

### Fixes

+ Fixed mikroBUS 1 and mikroBUS 2 I2C pins in `board.h` for Curiosity PIC32MZ EF 2.0 Development Board
  + SCL/SDA moved from `PA2`/`PA3` (I2C2) to `PA14`/`PA15` (I2C1), where both sockets are wired; Click boards on I2C got no answer before

### NEW HARDWARE

> NOTE:
>> If any new hardware was added to current version, it will be listed here.

---

**[BACK TO MAIN FILE](../../changelog.md)**

---
