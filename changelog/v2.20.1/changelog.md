<p align="center">
  <img src="http://www.mikroe.com/img/designs/beta/logo_small.png?raw=true" alt="MikroElektronika"/>
</p>

---

**[BACK TO MAIN FILE](../../changelog.md)**

---

# `v2.20.1`

+ released: 2026-10-20

## Changes

- [`v2.20.1`](#v2201)
  - [Changes](#changes)
    - [New features](#new-features)
      - [mikroSDK](#mikrosdk)
    - [NEW HARDWARE](#new-hardware)

### New features

#### mikroSDK

+ **LVGL IPS display support**
  + This PR adds IPS display support for mikroBUS-based boards using the ST7789 driver, enabling LVGL-based designs on boards that do not have a built-in display.
  + Key changes:
    + Added a new ST7789 middleware display driver.
    + Added a stub tp_st7789 touch-controller implementation for ST7789 boards.
    + Implemented the IPS display component on top of ST7789, so Complex Designer projects can target external IPS displays connected through a mikroBUS socket.
    + Added LVGL validation tests for display colors and orientation on different aspect ratios.

### NEW HARDWARE

> NOTE:
>> If any new hardware was added to current version, it will be listed here.

---

**[BACK TO MAIN FILE](../../changelog.md)**

---
