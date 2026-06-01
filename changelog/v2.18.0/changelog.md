<p align="center">
  <img src="http://www.mikroe.com/img/designs/beta/logo_small.png?raw=true" alt="MikroElektronika"/>
</p>

---

**[BACK TO MAIN FILE](../../changelog.md)**

---

# `v2.18.0`

+ released: 2026-06-04

## Changes

- [`v2.18.0`](#v2180)
  - [Changes](#changes)
    - [RENESAS](#renesas)
    - [Fixes](#fixes)
    - [Improvements](#improvements)
    - [NEW HARDWARE](#new-hardware)

### <font color=red>RENESAS</font>

**RA2L2 MCUs supported!**

| **R7FA2L2073CFJ** | **R7FA2L2093CFJ** |
| :-----------: | :-----------: |
| **R7FA2L2073CFL** | **R7FA2L2093CFL** |
| **R7FA2L2073CFM** | **R7FA2L2093CFM** |
| **R7FA2L2073CNE** | **R7FA2L2093CNE** |
| **R7FA2L2073CNH** | **R7FA2L2093CNH** |
| **R7FA2L2074CFJ** | **R7FA2L2094CFJ** |
| **R7FA2L2074CFL** | **R7FA2L2094CFL** |
| **R7FA2L2074CFM** | **R7FA2L2094CFM** |
| **R7FA2L2074CNE** | **R7FA2L2094CNE** |
| **R7FA2L2074CNH** | **R7FA2L2094CNH** |
|           |            |

**RA0E2 MCUs supported!**

| **R7FA0E2073CFJ** | **R7FA0E2093CFJ** |
| :-----------: | :-----------: |
| **R7FA0E2073CFL** | **R7FA0E2093CFL** |
| **R7FA0E2073CFM** | **R7FA0E2093CFM** |
| **R7FA0E2073CNE** | **R7FA0E2093CNE** |
| **R7FA0E2073CNH** | **R7FA0E2093CNH** |
| **R7FA0E2074CFJ** | **R7FA0E2094CFJ** |
| **R7FA0E2074CFL** | **R7FA0E2094CFL** |
| **R7FA0E2074CFM** | **R7FA0E2094CFM** |
| **R7FA0E2074CNE** | **R7FA0E2094CNE** |
| **R7FA0E2074CNH** | **R7FA0E2094CNH** |
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
+ Fixed implicit function declaration error raising for multiple implementations:
  + Included `delays.h` header for Nuvoton low-level ADC implementation.
  + Included `math.h` header for Toshiba low-level UART implementation.
  + Declared `SYSTEM_GetClocksFrequency()` function for Renesas devices.


### Improvements
+ Added a memory usage report to the compile output for MCUs using XC compilers.
+ Added UARTA module support for RA2L2, RA4C1 and RA4L1 MCU families.
+ Refactored the UART implementation for RA8 families
  + Now it better aligns with the architecture where SCI is handled as a UART sub-implementation.


### NEW HARDWARE

> NOTE:
>> If any new hardware was added to current version, it will be listed here.

Support added for following hardware:

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
+ **[2026-09-02](./new_hw/2026-09-02.md)**
+ **[2026-09-03](./new_hw/2026-09-03.md)**
+ **[2026-09-04](./new_hw/2026-09-04.md)**
+ **[2026-09-07](./new_hw/2026-09-07.md)**

---

**[BACK TO MAIN FILE](../../changelog.md)**

---
