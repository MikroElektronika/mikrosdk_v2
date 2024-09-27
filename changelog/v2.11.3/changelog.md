<p align="center">
  <img src="http://www.mikroe.com/img/designs/beta/logo_small.png?raw=true" alt="MikroElektronika"/>
</p>

---

**[BACK TO MAIN FILE](../../changelog.md)**

---

# `v2.11.3`

+ released: 2024-10-01

## Changes

- [`v2.11.3`](#v2113)
  - [Changes](#changes)
    - [Fixes](#fixes)
    - [Improvements](#improvements)
    - [NEW HARDWARE](#new-hardware)

### Fixes

+ Fixed touch panel implementation and TSC2003 library to recognize touch on TSC2003 RESISTIVE Displays while using LVGL projects
+ Fixed TP_ROTATION value to be "180" for all 4" CAPACITIVE Mikromedia Boards with PIC32MZ so touch position can be detected correctly

### Improvements

+ Updated [CMakeLists.txt](../../bsp/board/CMakeLists.txt) to include MCU Cards headers differently
  + Headers are now included with new path with `MCU_NAME`

### NEW HARDWARE

> NOTE:
>> If any new hardware was added to current version, it will be listed here.

---

**[BACK TO MAIN FILE](../../changelog.md)**

---
