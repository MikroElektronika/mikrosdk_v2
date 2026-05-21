<p align="center">
  <img src="http://www.mikroe.com/img/designs/beta/logo_small.png?raw=true" alt="MikroElektronika"/>
</p>

---

**[BACK TO MAIN FILE](../../changelog.md)**

---

# `v2.17.14`

+ released: 2026-05-21

## Changes

- [`v2.17.14`](#v21714)
  - [Changes](#changes)
    - [RENESAS](#renesas)
    - [Fixes](#fixes)
    - [Improvements](#improvements)
    - [NEW HARDWARE](#new-hardware)

### <font color=red>RENESAS</font>

**RA4C1 MCUs supported!**

| **R7FA4C1BD3CFP** | **R7FA4C1BD3CFM** |
| :-----------: | :-----------: |
| **R7FA4C1BB3CFP** | **R7FA4C1BB3CFM** |
|           |            |

**RA4E1 MCUs supported!**

| **R7FA4E10B2CFM** | **R7FA4E10B2CNE** |
| :-----------: | :-----------: |
| **R7FA4E10D2CFM** | **R7FA4E10D2CNE** |
|           |            |

**RA4E2 MCUs supported!**

| **R7FA4E2B92CBB** | **R7FA4E2B92CBC** |
| :-----------: | :-----------: |
| **R7FA4E2B93CBB** | **R7FA4E2B93CBC** |
| **R7FA4E2B93CFM** | **R7FA4E2B93CNE** |
| **R7FA4E2B93CNH** |  |
|           |            |

**RA6E1 MCUs supported!**

| **R7FA6E10D2CFM** | **R7FA6E10D2CFP** |
| :-----------: | :-----------: |
| **R7FA6E10D2CNE** | **R7FA6E10F2CFM** |
| **R7FA6E10F2CFP** | **R7FA6E10F2CNE** |
|           |            |

**Supported modules:**

+ ADC (Full module support)
+ SPI (Full module support)
+ UART (Full module support)
+ I2C (Full module support)
+ PWM (Full module support)
+ GPIO (Full module support)
+ 1-Wire (Full module support)

### Fixes

+ Added missing header guard `#define` directives to template header files
  + Fixed LVGL and Simple Designer header templates that were missing header guard definitions
  + Previously it could cause errors when header files were included in multiple source files
+ Improved implicit function declaration handling
  + Removed full suppression of implicit function declaration diagnostics previously done with `-Wno-implicit-function-declaration`
  + Runtime builds now report implicit function declaration issues correctly
  + Added missing `ctype.h` inclusion for non-mikroC compilers to provide required function declarations and avoid related diagnostics

### Improvements

+ Added SPI2 module support for Renesas devices that have it
+ Added touchpanel gesture ID dynamical setting based on controller firmware
  + Will fix use of `FT5x06` devices with new firmware while keeping compatibility with old firmware devices
+ Added shield definitions for mikroBUS
  + [Click Shield for Arduino UNO](https://www.mikroe.com/blog/click-shield-for-arduino-uno?srsltid=AfmBOooS_jZsvsznf0MEEYbqES2dFaePjwe-2YLAXnhrnIwnBr0CH7YA)

### NEW HARDWARE

> NOTE:
>> If any new hardware was added to current version, it will be listed here.

Support added for following hardware:

+ **[2026-05-21](./new_hw/2026-05-21.md)**
+ **[2026-05-22](./new_hw/2026-05-22.md)**
+ **[2026-05-25](./new_hw/2026-05-25.md)**
+ **[2026-05-26](./new_hw/2026-05-26.md)**
+ **[2026-05-27](./new_hw/2026-05-27.md)**
+ **[2026-05-28](./new_hw/2026-05-28.md)**
+ **[2026-05-29](./new_hw/2026-05-29.md)**
+ **[2026-06-01](./new_hw/2026-06-01.md)**
+ **[2026-06-02](./new_hw/2026-06-02.md)**
+ **[2026-06-03](./new_hw/2026-06-03.md)**

---

**[BACK TO MAIN FILE](../../changelog.md)**

---
