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

### Fixes

#### mikroSDK

- Defined previously missing I2C register addresses for PIC18FxxK42 MCUs
  - Without these definitions, I2C-related code fails to compile on all 18 supported variants
  - Projects attempting I2C communication on these MCUs would encounter build errors
  - This update ensures proper recognition of all I2C registers by the compiler
  - I2C examples and user projects now build successfully on PIC18FxxK42 devices

---

**[BACK TO MAIN FILE](../../changelog.md)**

---
