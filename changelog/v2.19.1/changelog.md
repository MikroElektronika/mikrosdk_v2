<p align="center">
  <img src="http://www.mikroe.com/img/designs/beta/logo_small.png?raw=true" alt="MikroElektronika"/>
</p>

---

**[BACK TO MAIN FILE](../../changelog.md)**

---

# `v2.19.1`

+ released: 2026-08-27

## Changes

- [`v2.19.1`](#v2191)
  - [Changes](#changes)
    - [RENESAS](#renesas)
    - [Fixes](#fixes)
    - [NEW HARDWARE](#new-hardware)

### RENESAS

**RA8P1 MCUs supported!**

| **R7KA8P1ADLCAB** | **R7KA8P1JFLCAB** |
| :-----------: | :-----------: |
| **R7KA8P1ADLCAC** | **R7KA8P1JFLCAC** |
| **R7KA8P1ADDCAB** | **R7KA8P1JFDCAB** |
| **R7KA8P1ADDCAC** | **R7KA8P1JFDCAC** |
| **R7KA8P1AFLCAB** | **R7KA8P1KFLCAB** |
| **R7KA8P1AFLCAC** | **R7KA8P1KFLCAC** |
| **R7KA8P1AFDCAB** | **R7KA8P1KFDCAB** |
| **R7KA8P1AFDCAC** | **R7KA8P1KFDCAC** |
| **R7KA8P1BDLCAB** | **R7JA8P1JRLSAJ** |
| **R7KA8P1BDLCAC** | **R7JA8P1JSLSAJ** |
| **R7KA8P1BDDCAB** | **R7JA8P1JRDSAJ** |
| **R7KA8P1BDDCAC** | **R7JA8P1JSDSAJ** |
| **R7KA8P1BFLCAB** | **R7JA8P1KRLSAJ**|
| **R7KA8P1BFLCAC** | **R7JA8P1KSLSAJ**|
| **R7KA8P1BFDCAB** | **R7JA8P1KRDSAJ**|
| **R7KA8P1BFDCAC** | **R7JA8P1KSDSAJ**|
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

* Declared missing NVIC types and functions for tinyUSB implementation for TM4C123 devices.
  * The issue became visible after `-Wno-implicit-function-declaration` was removed from the default build flags for NECTO configurations.
* Fixed tinyUSB implementation for STM32F373x8 and STM373xB MCUs.
  * Previously for these MCUs there was no tinyUSB implementation defined which caused build errors.
* Defined HSE_VALUE for STM32F7xx MCUs in tinyUSB implementation.
  * Previously HSE_VALUE was not defined for these MCUs which caused build errors.

### NEW HARDWARE

> NOTE:
>> If any new hardware was added to current version, it will be listed here.

Support added for following hardware:

+ **[2026-08-27](./new_hw/2026-08-27.md)**
+ **[2026-08-28](./new_hw/2026-08-28.md)**
+ **[2026-08-31](./new_hw/2026-08-31.md)**
+ **[2026-09-01](./new_hw/2026-09-01.md)**
+ **[2026-09-02](./new_hw/2026-09-02.md)**
+ **[2026-09-03](./new_hw/2026-09-03.md)**
+ **[2026-09-04](./new_hw/2026-09-04.md)**
+ **[2026-09-07](./new_hw/2026-09-07.md)**
+ **[2026-09-08](./new_hw/2026-09-08.md)**
+ **[2026-09-09](./new_hw/2026-09-09.md)**

---

**[BACK TO MAIN FILE](../../changelog.md)**

---
