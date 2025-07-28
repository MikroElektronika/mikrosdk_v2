<p align="center">
  <img src="http://www.mikroe.com/img/designs/beta/logo_small.png?raw=true" alt="MikroElektronika"/>
</p>

---

**[BACK TO MAIN FILE](../../changelog.md)**

---

# `v2.14.6`

+ released: 2025-07-17

## Changes

- [`v2.14.6`](#v2146)
  - [Changes](#changes)
    - [New Features](#new-features)
      - [mikroSDK](#mikrosdk)
    - [Fixes](#fixes)
      - [FT800](#ft800)
    - [NEW HARDWARE](#new-hardware)

### New Features

#### mikroSDK

+ Introduced SPI transfer API
  + Full-duplex SPI support available across all architectures in mikroSDK
  + This addition enables simultaneous data transmission and reception via a single call

### Fixes

#### FT800

+ Refactored code to eliminate redundancy by encapsulating repeated logic into reusable functions
+ Enhanced compatibility with compilers through conditional adjustments and code alignment:
  + All MikroC compilers
  + XC8 compiler
+ Disabled FT800 support for AVR architectures due to insufficient performance for reliable display operation

### NEW HARDWARE

> NOTE:
>> If any new hardware was added to current version, it will be listed here.

Support added for following hardware:

+ **[2025-07-17](./new_hw/2025-07-17.md)**
+ **[2025-07-21](./new_hw/2025-07-21.md)**
+ **[2025-07-22](./new_hw/2025-07-22.md)**
+ **[2025-07-23](./new_hw/2025-07-23.md)**
+ **[2025-07-24](./new_hw/2025-07-24.md)**
+ **[2025-07-29](./new_hw/2025-07-29.md)**
+ **[2025-07-30](./new_hw/2025-07-30.md)**
+ **[2025-07-31](./new_hw/2025-07-31.md)**
+ **[2025-08-04](./new_hw/2025-08-04.md)**
+ **[2025-08-05](./new_hw/2025-08-05.md)**
+ **[2025-08-06](./new_hw/2025-08-06.md)**
+ **[2025-08-14](./new_hw/2025-08-14.md)**

---

**[BACK TO MAIN FILE](../../changelog.md)**

---
