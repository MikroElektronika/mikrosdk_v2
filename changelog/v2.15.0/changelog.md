<p align="center">
  <img src="http://www.mikroe.com/img/designs/beta/logo_small.png?raw=true" alt="MikroElektronika"/>
</p>

---

**[BACK TO MAIN FILE](../../changelog.md)**

---

# `v2.15.0`

+ released: 2025-08-07

## Changes

- [`v2.15.0`](#v2150)
  - [Changes](#changes)
    - [RENESAS](#renesas)
    - [Fixes](#fixes)
      - [mikroSDK](#mikrosdk)
    - [NEW HARDWARE](#new-hardware)

### <font color=red>RENESAS</font>

**RA4M1 MCUs supported!**

|       MCU       |
|  :------------: |
|  R7FA4M1AB3CFP  |
|  R7FA4M1AB2CLJ  |
|  R7FA4M1AB3CFM  |
|  R7FA4M1AB3CNB  |
|  R7FA4M1AB3CFL  |
|  R7FA4M1AB3CNE  |
|  R7FA4M1AB3CNF  |

**Supported modules:**

+ ADC (Full module support)
+ SPI (Full module support)
+ UART (Full module support)
+ I2C (Full module support)
+ PWM (Full module support)
+ GPIO (Full module support)
+ 1-Wire (Full module support)

### Fixes

#### mikroSDK

- Fixed the build issue for MCUs STM32C011J6 and STM32C011J4
  - Now setups with these MCUs can be successfully created
- SPI transfer API is now also available for the 157 MCUs with AI generated SDK support
- Minor fixes and improvements regarding the SPI transfer API implementation

### NEW HARDWARE

> NOTE:
>> If any new hardware was added to current version, it will be listed here.

Support added for following hardware:

---

**[BACK TO MAIN FILE](../../changelog.md)**

---
