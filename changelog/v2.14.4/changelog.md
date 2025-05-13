<p align="center">
  <img src="http://www.mikroe.com/img/designs/beta/logo_small.png?raw=true" alt="MikroElektronika"/>
</p>

---

**[BACK TO MAIN FILE](../../changelog.md)**

---

# `v2.14.4`

+ released: 2025-04-16

## Changes

+ [`v2.14.4`](#v2144)
  + [Changes](#changes)
    + [Fixes](#fixes)
      + [mikroSDK](#mikrosdk)
      + [CORE](#core)
    + [NEW HARDWARE](#new-hardware)

### Fixes

#### mikroSDK

+ Fixed the TFT_BPWM pin for boards EasyPIC PRO v8 and EasyAVR PRO v8
+ Fixes for PIC18FxxQ8x MCUs
  + Corrected certain register addresses, resolving I2C communication issues
  + Updated relevant regex patterns to ensure compatibility with *mikroC AI for PIC*
+ Fixed clock setting for USB in tinyUSB implementation for STM32L4
    + For STM32L47x/L48x clock source for USB should be set to PLLQ

#### CORE

+ Fixed USB clock schemes for STM32L47x/L48x

### NEW HARDWARE

> NOTE:
>> If any new hardware was added to current version, it will be listed here.

Support added for following hardware:

---

**[BACK TO MAIN FILE](../../changelog.md)**

---
