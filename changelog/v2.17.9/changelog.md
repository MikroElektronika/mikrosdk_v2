<p align="center">
  <img src="http://www.mikroe.com/img/designs/beta/logo_small.png?raw=true" alt="MikroElektronika"/>
</p>

---

**[BACK TO MAIN FILE](../../changelog.md)**

---

# `v2.17.9`

+ released: 2026-03-03

## Changes

- [`v2.17.9`](#v2179)
  - [Changes](#changes)
    - [RENESAS](#renesas)
    - [Improvements](#improvements)
      - [mikroSDK](#mikrosdk)
    - [Fixes](#fixes)
      - [mikroSDK](#mikrosdk-1)
    - [NEW HARDWARE](#new-hardware)

### <font color=red>RENESAS</font>

**RA4M2 MCUs supported!**

|            |
| :-----------: |
| R7FA4M2AB3CFL |
| R7FA4M2AB3CFM |
| R7FA4M2AB3CFP |
| R7FA4M2AB3CNE |
| R7FA4M2AC3CFL |
| R7FA4M2AC3CFM |
| R7FA4M2AC3CFP |
| R7FA4M2AC3CNE |
| R7FA4M2AD3CFL |
| R7FA4M2AD3CFM |
| R7FA4M2AD3CFP |
| R7FA4M2AD3CNE |
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

+ Improved the way module numeration for Renesas MCUs is handled in low-level
  + This change affects modules SCI, PWM, I2C and UART
  + The module numeration is now handled in a more consistent way across all Renesas MCUs, which should improve the stability and make it easier to add support for new Renesas MCUs in the future

### Fixes

#### mikroSDK

+ Fixed enabling on the timer modules for Renesas MCUs
  + The previous approach did not cover all modules on all Renesas MCUs
  + The new approach is more consistent and should work for all modules on all Renesas MCUs
+ Fixed IIC Simple mode of SCI module for RA8M1
  + Previously only transmit operation worked correctly

### NEW HARDWARE

> NOTE:
>> If any new hardware was added to current version, it will be listed here.

---

**[BACK TO MAIN FILE](../../changelog.md)**

---
