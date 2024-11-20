<p align="center">
  <img src="http://www.mikroe.com/img/designs/beta/logo_small.png?raw=true" alt="MikroElektronika"/>
</p>

---

**[BACK TO MAIN FILE](../../changelog.md)**

---

# `v2.12.0`

+ released: 2024-11-08

## Changes

+ [`v2.12.0`](#v2120)
  + [Changes](#changes)
    + [Improvements](#improvements)
      + [mikroSDK](#mikrosdk)
    + [Fixes](#fixes)
    + [NEW HARDWARE](#new-hardware)

### Improvements

#### mikroSDK

**mikroSDK** now has the option to skip `DRV` to `HAL` layer jumps completely.

> Note that this feature is enabled by default in NECTO.

### Fixes

+ Fixed PIC XC8 SPI module so the code can be generated
  + Previous code was too complex for XC8 compiler, so it has been simplified
+ Fixed all timer module number definitions for all STM32L1x MCUs
  + Previously, timer/pwm was not working correctly as these values were incorrect

### NEW HARDWARE

> NOTE:
>> If any new hardware was added to current version, it will be listed here.

Support added for following hardware:

+ **[2024-11-08](./new_hw/2024-11-08.md)**
+ **[2024-11-12](./new_hw/2024-11-12.md)**
+ **[2024-11-13](./new_hw/2024-11-13.md)**
+ **[2024-11-14](./new_hw/2024-11-14.md)**
+ **[2024-11-15](./new_hw/2024-11-15.md)**
+ **[2024-11-18](./new_hw/2024-11-18.md)**
+ **[2024-11-19](./new_hw/2024-11-19.md)**

---

**[BACK TO MAIN FILE](../../changelog.md)**

---
