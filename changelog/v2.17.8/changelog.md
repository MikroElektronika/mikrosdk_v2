<p align="center">
  <img src="http://www.mikroe.com/img/designs/beta/logo_small.png?raw=true" alt="MikroElektronika"/>
</p>

---

**[BACK TO MAIN FILE](../../changelog.md)**

---

# `v2.17.8`

+ released: 2026-02-19

## Changes

- [`v2.17.8`](#v2178)
  - [Changes](#changes)
    - [RENESAS](#renesas)
    - [Improvements](#improvements)
      - [mikroSDK](#mikrosdk)
    - [Fixes](#fixes)
      - [mikroSDK](#mikrosdk-1)
    - [NEW HARDWARE](#new-hardware)

### <font color=red>RENESAS</font>

**RA8M1 MCUs supported!**

|            |
| :-----------: |
| R7FA8M1AFECBD |
| R7FA8M1AFECFB |
| R7FA8M1AFECFC |
| R7FA8M1AFECFP |
| R7FA8M1AHECBD |
| R7FA8M1AHECFB |
| R7FA8M1AHECFC |
| R7FA8M1AHECFP |
|            |

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

+ Added SCI-based SPI and I2C sub-implementations for all supported Renesas devices
  + Full SCI pin support in Simple SPI mode
  + Full SCI pin support in Simple I2C mode

### Fixes

#### mikroSDK

+ Added conditional compilation guards for PGA-capable GPIO pins (P000/P001/P002) to prevent build issues when pins are undefined across different MCUs

### NEW HARDWARE

> NOTE:
>> If any new hardware was added to current version, it will be listed here.

Support added for following hardware:

+ **[2026-02-19](./new_hw/2026-02-19.md)**
+ **[2026-02-20](./new_hw/2026-02-20.md)**
+ **[2026-02-23](./new_hw/2026-02-23.md)**
+ **[2026-02-24](./new_hw/2026-02-24.md)**
+ **[2026-02-25](./new_hw/2026-02-25.md)**
+ **[2026-02-26](./new_hw/2026-02-26.md)**
+ **[2026-02-27](./new_hw/2026-02-27.md)**
+ **[2026-03-02](./new_hw/2026-03-02.md)**

---

**[BACK TO MAIN FILE](../../changelog.md)**

---
