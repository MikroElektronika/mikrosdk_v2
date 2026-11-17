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

Support added for following hardware:

+ **[2026-10-20](./new_hw/2026-10-20.md)**
+ **[2026-10-21](./new_hw/2026-10-21.md)**
+ **[2026-10-22](./new_hw/2026-10-22.md)**
+ **[2026-10-23](./new_hw/2026-10-23.md)**
+ **[2026-10-26](./new_hw/2026-10-26.md)**
+ **[2026-10-27](./new_hw/2026-10-27.md)**
+ **[2026-10-28](./new_hw/2026-10-28.md)**
+ **[2026-10-29](./new_hw/2026-10-29.md)**
+ **[2026-10-30](./new_hw/2026-10-30.md)**
+ **[2026-11-02](./new_hw/2026-11-02.md)**

---

**[BACK TO MAIN FILE](../../changelog.md)**

---
