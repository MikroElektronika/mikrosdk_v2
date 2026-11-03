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
    + Recorded events: I2C Master and SPI Master transfers, SPI chip select changes, UART writes and reads, GPIO output writes and GPIO input level changes, plus named values through `trace_value()`.
    + Records are kept in a RAM buffer (512 bytes by default, `TRACE_BUFFER( size )` to change it) and handed to the debugger when the buffer is full, on `trace_flush()`, or every 500 ms of program time (`trace_set_flush_interval()`).
    + Fast GPIO writes (a display strobe, a bit-banged bus) are coalesced into bursts, so they do not stop the program over and over.
    + Time base: the DWT cycle counter on Cortex-M3 and newer; other cores keep the order of events but not the timing. Applications can supply their own timer through the weak `trace_ticks()` and `trace_tick_hz()`.
    + Added trace hooks to the GPIO Out, GPIO In, I2C Master, SPI Master and UART drivers (`drv_trace.h`). Without the trace library the hooks cost one load and a branch per call.
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
