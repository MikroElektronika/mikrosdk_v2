<p align="center">
  <img src="http://www.mikroe.com/img/designs/beta/logo_small.png?raw=true" alt="MikroElektronika"/>
</p>

---

**[BACK TO MAIN FILE](../../changelog.md)**

---

# `v2.19.0`

+ released: 2026-08-13

## Changes

- [`v2.19.0`](#v2190)
  - [Changes](#changes)
    - [RENESAS](#renesas)
    - [Fixes](#fixes)
    - [NEW HARDWARE](#new-hardware)

### <font color=red>RENESAS</font>

**RA6M1 MCUs supported!**

| **R7FA6M1AD2CLJ** | **R7FA6M1AD3CLJ** |
| :-----------: | :-----------: |
| **R7FA6M1AD3CFM** | **R7FA6M1AD3CNB** |
| **R7FA6M1AD3CFP** |  |
|           |            |

**RA6M2 MCUs supported!**

| **R7FA6M2AD2CLK** | **R7FA6M2AF2CLK** |
| :-----------: | :-----------: |
| **R7FA6M2AD3CFB** | **R7FA6M2AF3CFB** |
| **R7FA6M2AD3CFP** | **R7FA6M2AF3CFP** |
| **R7FA6M2AD3CLK** | **R7FA6M2AF3CLK** |
|           |            |

**RA8M2 MCUs supported!**

| **R7KA8M2ADLCAB** | **R7KA8M2AFECHC** |
| :-----------: | :-----------: |
| **R7KA8M2ADLCAC** | **R7KA8M2JFLCAB** |
| **R7KA8M2ADDCAB** | **R7KA8M2JFLCAC** |
| **R7KA8M2ADDCAC** | **R7KA8M2JFDCAB** |
| **R7KA8M2ADECAB** | **R7KA8M2JFDCAC** |
| **R7KA8M2ADECAC** | **R7KA8M2JFECAB** |
| **R7KA8M2AFLCAB** | **R7KA8M2JFECAC** |
| **R7KA8M2AFLCAC** | **R7KA8M2JFECHC** |
| **R7KA8M2AFDCAB** | **R7JA8M2JRLSAJ** |
| **R7KA8M2AFDCAC** | **R7JA8M2JSLSAJ** |
| **R7KA8M2AFECAB** | **R7JA8M2JRDSAJ** |
| **R7KA8M2AFECAC** | **R7JA8M2JSDSAJ** |
| **R7KA8M2ADECHC** |  |
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

* Fixed SPI and SCI clock selection for Renesas RA6T2 MCUs.
  * Previously SPI and SCI peripherals were using Peripheral clocks instead of specific SCISPICLK.
  * This was causing incorrect baudrate settings which led to the wrong module behavior.

### NEW HARDWARE

> NOTE:
>> If any new hardware was added to current version, it will be listed here.

Support added for following hardware:

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

---

**[BACK TO MAIN FILE](../../changelog.md)**

---
