<p align="center">
  <img src="http://www.mikroe.com/img/designs/beta/logo_small.png?raw=true" alt="MikroElektronika"/>
</p>

---

**[BACK TO MAIN FILE](../../changelog.md)**

---

# `v2.18.2`

+ released: 2026-07-09

## Changes

- [`v2.18.2`](#v2182)
  - [Changes](#changes)
    - [RENESAS](#renesas)
    - [Fixes](#fixes)
    - [Improvements](#improvements)
    - [NEW HARDWARE](#new-hardware)

### <font color=red>RENESAS</font>

**RA0L1 MCUs supported!**

| **R7FA0L1053CFJ** | **R7FA0L1073CFJ** |
| :-----------: | :-----------: |
| **R7FA0L1053CFL** | **R7FA0L1073CFL** |
| **R7FA0L1053CNE** | **R7FA0L1073CNE** |
| **R7FA0L1053CNH** | **R7FA0L1073CNH** |
| **R7FA0L1053CNK** | **R7FA0L1073CNK** |
| **R7FA0L1053CSC** | **R7FA0L1073CSC** |
| **R7FA0L1054CFJ** | **R7FA0L1074CFJ** |
| **R7FA0L1054CFL** | **R7FA0L1074CFL** |
| **R7FA0L1054CNE** | **R7FA0L1074CNE** |
| **R7FA0L1054CNH** | **R7FA0L1074CNH** |
| **R7FA0L1054CNK** | **R7FA0L1074CNK** |
| **R7FA0L1054CSC** | **R7FA0L1074CSC** |
|           |            |

**RA2T1 MCUs supported!**

| **R7FA2T1073CFL** | **R7FA2T1074CFJ** |
| :-----------: | :-----------: |
| **R7FA2T1073CFJ** | **R7FA2T1074CNH** |
| **R7FA2T1073CNH** | **R7FA2T1074CNE** |
| **R7FA2T1073CNE** | **R7FA2T1073CNK** |
| **R7FA2T1074CFL** | **R7FA2T1074CNK** |
|           |            |

**RA4T1 MCUs supported!**

| **R7FA4T1B93CFJ** | **R7FA4T1BB3CFJ** |
| :-----------: | :-----------: |
| **R7FA4T1B93CFL** | **R7FA4T1BB3CFL** |
| **R7FA4T1B93CFM** | **R7FA4T1BB3CFM** |
| **R7FA4T1B93CNE** | **R7FA4T1BB3CNE** |
| **R7FA4T1B93CNH** | **R7FA4T1BB3CNH** |
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

+ Fixed a bug which caused incorrect AGT behavior on certain Renesas MCU families.
  + All Renesas MCU families now work correctly with AGT pins which are used as PWM channels.

### Improvements

+ Improvements and fixes in `conversions.c`
  + Fixed comparison bugs and an uninitialized variable in the string-to-number conversion functions
  + Added a new fixed-precision float-to-string conversion function - `float_to_str_prec()`
  + Renamed variables for clarity and applied consistent comparison style throughout

### NEW HARDWARE

> NOTE:
>> If any new hardware was added to current version, it will be listed here.

Support added for following hardware:

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

---

**[BACK TO MAIN FILE](../../changelog.md)**

---
