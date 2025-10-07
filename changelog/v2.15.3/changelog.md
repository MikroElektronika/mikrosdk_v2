<p align="center">
  <img src="http://www.mikroe.com/img/designs/beta/logo_small.png?raw=true" alt="MikroElektronika"/>
</p>

---

**[BACK TO MAIN FILE](../../changelog.md)**

---

# `v2.15.3`

+ released: 2025-09-09

## Changes

- [`v2.15.3`](#v2153)
  - [Changes](#changes)
    - [Fixes](#fixes)
      - [mikroSDK](#mikrosdk)
    - [NEW HARDWARE](#new-hardware)

### Fixes

#### mikroSDK

- Defined previously missing I2C register addresses for PIC18FxxK42 MCUs
  - Without these definitions, I2C-related code fails to compile on all 18 supported variants
  - Projects attempting I2C communication on these MCUs would encounter build errors
  - This update ensures proper recognition of all I2C registers by the compiler
  - I2C examples and user projects now build successfully on PIC18FxxK42 devices

### NEW HARDWARE

> NOTE:
>> If any new hardware was added to current version, it will be listed here.

Support added for following hardware:

+ **[2025-09-10](./new_hw/2025-09-10.md)**
+ **[2025-09-11](./new_hw/2025-09-11.md)**
+ **[2025-09-12](./new_hw/2025-09-12.md)**
+ **[2025-09-15](./new_hw/2025-09-15.md)**
+ **[2025-09-16](./new_hw/2025-09-16.md)**
+ **[2025-09-17](./new_hw/2025-09-17.md)**
+ **[2025-09-18](./new_hw/2025-09-18.md)**

---

**[BACK TO MAIN FILE](../../changelog.md)**

---
