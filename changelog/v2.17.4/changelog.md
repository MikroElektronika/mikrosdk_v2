<p align="center">
  <img src="http://www.mikroe.com/img/designs/beta/logo_small.png?raw=true" alt="MikroElektronika"/>
</p>

---

**[BACK TO MAIN FILE](../../changelog.md)**

---

# `v2.17.4`

+ released: 2026-01-08

## Changes

- [`v2.17.4`](#v2174)
  - [Changes](#changes)
    - [RENESAS](#renesas)
    - [Improvements](#improvements)
      - [mikroSDK](#mikrosdk)
    - [NEW HARDWARE](#new-hardware)

### <font color=red>RENESAS</font>

**RA6M4 MCUs supported!**

|            |            |            |
| :-----------: | :-----------: | :-----------: |
| R7FA6M4AD2CBM | R7FA6M4AD2CBQ | R7FA6M4AD3CBM |
| R7FA6M4AD3CBQ | R7FA6M4AD3CFB | R7FA6M4AD3CFM |
| R7FA6M4AD3CFP | R7FA6M4AE2CBM | R7FA6M4AE2CBQ |
| R7FA6M4AE3CBM | R7FA6M4AE3CBQ | R7FA6M4AE3CFB |
| R7FA6M4AE3CFM | R7FA6M4AE3CFP | R7FA6M4AF2CBM |
| R7FA6M4AF2CBQ | R7FA6M4AF3CBM | R7FA6M4AF3CBQ |
| R7FA6M4AF3CFB | R7FA6M4AF3CFM | R7FA6M4AF3CFP |
|            |            |            |

**Supported modules:**

+ ADC (Full module support)
+ SPI (Full module support)
+ UART (Full module support)
+ I2C (Full module support)
+ PWM (Full module support)
+ GPIO (Full module support)
+ 1-Wire (Full module support)

### Improvements

#### mikroSDK

+ Fixed PWM frequency calculation for STM32 timers by correcting timer clock source handling across MCU families.
  + Resolved incorrect prescaler/auto-reload computation that caused mismatched PWM frequencies.
  + Unified timer frequency setup logic for both low level implementations.
  + Improved robustness of timer initialization for following STM32 series:
    + `F0/F1/F2/F3/F4/F7`
    + `L0/L1/L4/L4+`
    + `G0`
    + `H7`
+ Upgraded the `sprintf_me`, `sprintl_me` and `sprinti_me` functions to support a wider range of formatting styles.
  + In addition to that, implemented `snprintf_me`, `snprintl_me` and `snprinti_me` as a counterparts to C's `snprintf` function.
+ Configuration and Git handling improvements
  + Added a pre-config CMake step to locally ignore changes to configuration files using Git index flags.
  + Fixed template processing by applying `@ONLY` where required to prevent unintended substitutions.
  + Updated `.gitignore` to exclude specific generated files.

### NEW HARDWARE

> NOTE:
>> If any new hardware was added to current version, it will be listed here.

Support added for following hardware:

+ **[2026-01-08](./new_hw/2026-01-08.md)**
+ **[2026-01-09](./new_hw/2026-01-09.md)**
+ **[2026-01-12](./new_hw/2026-01-12.md)**
+ **[2026-01-13](./new_hw/2026-01-13.md)**
+ **[2026-01-14](./new_hw/2026-01-14.md)**
+ **[2026-01-15](./new_hw/2026-01-15.md)**
+ **[2026-01-16](./new_hw/2026-01-16.md)**
+ **[2026-01-19](./new_hw/2026-01-19.md)**
+ **[2026-01-20](./new_hw/2026-01-20.md)**
+ **[2026-01-21](./new_hw/2026-01-21.md)**

---

**[BACK TO MAIN FILE](../../changelog.md)**

---
