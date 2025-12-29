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
+ **[2026-01-22](./new_hw/2026-01-22.md)**
+ **[2026-01-23](./new_hw/2026-01-23.md)**
+ **[2026-01-26](./new_hw/2026-01-26.md)**
+ **[2026-01-27](./new_hw/2026-01-27.md)**
+ **[2026-01-28](./new_hw/2026-01-28.md)**
+ **[2026-01-29](./new_hw/2026-01-29.md)**
+ **[2026-01-30](./new_hw/2026-01-30.md)**
+ **[2026-02-02](./new_hw/2026-02-02.md)**
+ **[2026-02-03](./new_hw/2026-02-03.md)**
+ **[2026-02-04](./new_hw/2026-02-04.md)**
+ **[2026-02-05](./new_hw/2026-02-05.md)**
+ **[2026-02-06](./new_hw/2026-02-06.md)**
+ **[2026-02-09](./new_hw/2026-02-09.md)**
+ **[2026-02-10](./new_hw/2026-02-10.md)**
+ **[2026-02-11](./new_hw/2026-02-11.md)**
+ **[2026-02-12](./new_hw/2026-02-12.md)**
+ **[2026-02-13](./new_hw/2026-02-13.md)**
+ **[2026-02-16](./new_hw/2026-02-16.md)**
+ **[2026-02-17](./new_hw/2026-02-17.md)**
+ **[2026-02-18](./new_hw/2026-02-18.md)**
+ **[2026-02-19](./new_hw/2026-02-19.md)**
+ **[2026-02-20](./new_hw/2026-02-20.md)**
+ **[2026-02-23](./new_hw/2026-02-23.md)**
+ **[2026-02-24](./new_hw/2026-02-24.md)**

---

**[BACK TO MAIN FILE](../../changelog.md)**

---
