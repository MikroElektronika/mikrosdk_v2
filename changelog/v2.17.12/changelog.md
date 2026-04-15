<p align="center">
  <img src="http://www.mikroe.com/img/designs/beta/logo_small.png?raw=true" alt="MikroElektronika"/>
</p>

---

**[BACK TO MAIN FILE](../../changelog.md)**

---

# `v2.17.12`

+ released: 2026-04-23

## Changes

- [`v2.17.12`](#v21712)
  - [Changes](#changes)
    - [RENESAS](#renesas)
    - [Improvements](#improvements)
    - [New Features](#new-features)
    - [NEW HARDWARE](#new-hardware)

### <font color=red>RENESAS</font>

**RA2E1 MCUs supported!**

| MCU | MCU | MCU | MCU |
| :-----------: | :-----------: | :-----------: | :-----------: |
| R7FA2E1A52DBV | R7FA2E1A52DDA | R7FA2E1A52DFJ | R7FA2E1A52DFL |
| R7FA2E1A52DLM | R7FA2E1A52DNE | R7FA2E1A52DNH | R7FA2E1A53CBV |
| R7FA2E1A53CDA | R7FA2E1A53CFJ | R7FA2E1A53CFL | R7FA2E1A53CLM |
| R7FA2E1A53CNE | R7FA2E1A53CNH | R7FA2E1A72DBU | R7FA2E1A72DBV |
| R7FA2E1A72DDA | R7FA2E1A72DFJ | R7FA2E1A72DFK | R7FA2E1A72DFL |
| R7FA2E1A72DFM | R7FA2E1A72DLM | R7FA2E1A72DNB | R7FA2E1A72DNE |
| R7FA2E1A72DNH | R7FA2E1A73CBU | R7FA2E1A73CBV | R7FA2E1A73CDA |
| R7FA2E1A73CFJ | R7FA2E1A73CFK | R7FA2E1A73CFL | R7FA2E1A73CFM |
| R7FA2E1A73CLM | R7FA2E1A73CNB | R7FA2E1A73CNE | R7FA2E1A73CNH |
| R7FA2E1A82DBU | R7FA2E1A82DBV | R7FA2E1A82DFJ | R7FA2E1A82DFK |
| R7FA2E1A82DFL | R7FA2E1A82DFM | R7FA2E1A82DLM | R7FA2E1A82DNE |
| R7FA2E1A82DNH | R7FA2E1A83CBU | R7FA2E1A83CBV | R7FA2E1A83CFJ |
| R7FA2E1A83CFK | R7FA2E1A83CFL | R7FA2E1A83CFM | R7FA2E1A83CLM |
| R7FA2E1A83CNE | R7FA2E1A83CNH | R7FA2E1A92DBU | R7FA2E1A92DBV |
| R7FA2E1A92DDA | R7FA2E1A92DFJ | R7FA2E1A92DFK | R7FA2E1A92DFL |
| R7FA2E1A92DFM | R7FA2E1A92DLM | R7FA2E1A92DNB | R7FA2E1A92DNE |
| R7FA2E1A92DNH | R7FA2E1A93CBU | R7FA2E1A93CBV | R7FA2E1A93CDA |
| R7FA2E1A93CFJ | R7FA2E1A93CFK | R7FA2E1A93CFL | R7FA2E1A93CFM |
| R7FA2E1A93CLM | R7FA2E1A93CNB | R7FA2E1A93CNE | R7FA2E1A93CNH |
|                   |

**Supported modules:**

+ ADC (Full module support)
+ SPI (Full module support)
+ UART (Full module support)
+ I2C (Full module support)
+ PWM (Full module support)
+ GPIO (Full module support)
+ 1-Wire (Full module support)

### Improvements

+ Reduced the amount of `#ifdef` conditionals and regular expressions in various low-level implementations for Renesas MCUs
  + Simplified conditional compilation and regex usage
  + Improved readability and maintainability across affected modules

### New Features

+ AGT module support for Renesas devices
  + Implemented PWM mode for the AGT module
  + Expands available PWM output pins (previously only GPT module was supported)
  + Automatic module selection based on pin configuration is transparent to users

### NEW HARDWARE

> NOTE:
>> If any new hardware was added to current version, it will be listed here.

---

**[BACK TO MAIN FILE](../../changelog.md)**

---
