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
+ **[2026-06-04](./new_hw/2026-06-04.md)**
+ **[2026-06-05](./new_hw/2026-06-05.md)**
+ **[2026-06-08](./new_hw/2026-06-08.md)**
+ **[2026-06-09](./new_hw/2026-06-09.md)**
+ **[2026-06-10](./new_hw/2026-06-10.md)**
+ **[2026-06-11](./new_hw/2026-06-11.md)**
+ **[2026-06-12](./new_hw/2026-06-12.md)**
+ **[2026-06-15](./new_hw/2026-06-15.md)**
+ **[2026-06-16](./new_hw/2026-06-16.md)**
+ **[2026-06-17](./new_hw/2026-06-17.md)**
+ **[2026-06-18](./new_hw/2026-06-18.md)**
+ **[2026-06-19](./new_hw/2026-06-19.md)**
+ **[2026-06-22](./new_hw/2026-06-22.md)**
+ **[2026-06-23](./new_hw/2026-06-23.md)**
+ **[2026-06-24](./new_hw/2026-06-24.md)**
+ **[2026-06-25](./new_hw/2026-06-25.md)**
+ **[2026-06-26](./new_hw/2026-06-26.md)**
+ **[2026-06-29](./new_hw/2026-06-29.md)**
+ **[2026-06-30](./new_hw/2026-06-30.md)**
+ **[2026-07-01](./new_hw/2026-07-01.md)**
+ **[2026-07-02](./new_hw/2026-07-02.md)**
+ **[2026-07-03](./new_hw/2026-07-03.md)**
+ **[2026-07-06](./new_hw/2026-07-06.md)**
+ **[2026-07-07](./new_hw/2026-07-07.md)**
+ **[2026-07-08](./new_hw/2026-07-08.md)**
+ **[2026-07-09](./new_hw/2026-07-09.md)**
+ **[2026-07-10](./new_hw/2026-07-10.md)**
+ **[2026-07-13](./new_hw/2026-07-13.md)**
+ **[2026-07-14](./new_hw/2026-07-14.md)**
+ **[2026-07-15](./new_hw/2026-07-15.md)**
+ **[2026-07-16](./new_hw/2026-07-16.md)**
+ **[2026-07-17](./new_hw/2026-07-17.md)**
+ **[2026-07-20](./new_hw/2026-07-20.md)**
+ **[2026-07-21](./new_hw/2026-07-21.md)**
+ **[2026-07-22](./new_hw/2026-07-22.md)**
+ **[2026-07-23](./new_hw/2026-07-23.md)**
+ **[2026-07-24](./new_hw/2026-07-24.md)**
+ **[2026-07-27](./new_hw/2026-07-27.md)**
+ **[2026-07-28](./new_hw/2026-07-28.md)**
+ **[2026-07-29](./new_hw/2026-07-29.md)**
+ **[2026-07-30](./new_hw/2026-07-30.md)**
+ **[2026-07-31](./new_hw/2026-07-31.md)**
+ **[2026-08-03](./new_hw/2026-08-03.md)**
+ **[2026-08-04](./new_hw/2026-08-04.md)**
+ **[2026-08-05](./new_hw/2026-08-05.md)**
+ **[2026-08-06](./new_hw/2026-08-06.md)**
+ **[2026-08-07](./new_hw/2026-08-07.md)**
+ **[2026-08-10](./new_hw/2026-08-10.md)**
+ **[2026-08-11](./new_hw/2026-08-11.md)**
+ **[2026-08-12](./new_hw/2026-08-12.md)**
+ **[2026-08-13](./new_hw/2026-08-13.md)**
+ **[2026-08-14](./new_hw/2026-08-14.md)**
+ **[2026-08-17](./new_hw/2026-08-17.md)**
+ **[2026-08-18](./new_hw/2026-08-18.md)**
+ **[2026-08-19](./new_hw/2026-08-19.md)**
+ **[2026-08-20](./new_hw/2026-08-20.md)**
+ **[2026-08-21](./new_hw/2026-08-21.md)**
+ **[2026-08-24](./new_hw/2026-08-24.md)**
+ **[2026-08-25](./new_hw/2026-08-25.md)**
+ **[2026-08-26](./new_hw/2026-08-26.md)**
+ **[2026-08-27](./new_hw/2026-08-27.md)**
+ **[2026-08-28](./new_hw/2026-08-28.md)**
+ **[2026-08-31](./new_hw/2026-08-31.md)**
+ **[2026-09-01](./new_hw/2026-09-01.md)**

---

**[BACK TO MAIN FILE](../../changelog.md)**

---
