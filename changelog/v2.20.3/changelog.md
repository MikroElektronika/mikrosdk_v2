<p align="center">
  <img src="http://www.mikroe.com/img/designs/beta/logo_small.png?raw=true" alt="MikroElektronika"/>
</p>

---

**[BACK TO MAIN FILE](../../changelog.md)**

---

# `v2.20.3`

+ released: TBD

## Changes

- [`v2.20.3`](#v2203)
  - [Changes](#changes)
    - [New features](#new-features)
      - [mikroSDK](#mikrosdk)
    - [NEW HARDWARE](#new-hardware)

### New features

#### mikroSDK

+ **Firmware trace library (`MikroSDK.Trace`)**
  + Records driver activity on the device and hands it to the debugger, so NECTO Studio can show it on a timeline.
  + Key changes:
    + Added the `MikroSDK.Trace` platform library (`trace.h`); linking it is all an application needs, the trace starts with the first recorded event.
    + Recorded events: I2C Master and SPI Master transfers, SPI chip select changes, UART writes and reads, 1-Wire operations (reset, ROM commands, byte writes and reads), ADC reads (raw and voltage), GPIO output writes and GPIO input level changes, plus named values through `trace_value()`.
    + Trace format version 3 (1-Wire records, injected events); NECTO Studio needs a trace decoder that reads version 3.
    + Fault injection while debugging: NECTO Studio can make an I2C device stop answering, hold SPI MISO at a byte, hold a GPIO input at a level, force an ADC value, and take the devices off a 1-Wire bus. The debugger writes the faults to the trace library (`__traceFaults`); the drivers ask fault hooks (`drv_trace_fault_*()`) before or after each call, and the trace marks the calls a fault changed.
    + Records are kept in a RAM buffer (512 bytes by default, `TRACE_BUFFER( size )` to change it) and handed to the debugger when the buffer is full, on `trace_flush()`, or every 500 ms of program time (`trace_set_flush_interval()`).
    + Fast GPIO writes (a display strobe, a bit-banged bus) are coalesced into bursts, so they do not stop the program over and over.
    + Time base: the DWT cycle counter on Cortex-M3 and newer; other cores keep the order of events but not the timing. Applications can supply their own timer through the weak `trace_ticks()` and `trace_tick_hz()`.
    + Added trace hooks to the GPIO Out, GPIO In, I2C Master, SPI Master, UART, ADC and 1-Wire drivers (`drv_trace.h`). Without the trace library the hooks cost one load and a branch per call.
    + The library is built for ARM with GCC and Clang. With mikroC and XC8 the drivers are built without hooks.
    + Added validation test under `tests/trace`.
+ **Timestamped plot**
  + Added `plot_ts()` to `plot.h`: like `plot()`, with the time the value was taken on the device, so NECTO Studio keeps the real spacing of the values.

### NEW HARDWARE

> NOTE:
>> If any new hardware was added to current version, it will be listed here.

Support added for following hardware:

---

**[BACK TO MAIN FILE](../../changelog.md)**

---
