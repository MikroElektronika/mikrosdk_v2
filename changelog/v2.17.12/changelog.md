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
    - [New Features](#new-features)
    - [Improvements](#improvements)
    - [Fixes](#fixes)
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

### New Features

+ AGT module support for Renesas devices
  + Implemented PWM mode for the AGT module
  + Expands available PWM output pins (previously only GPT module was supported)
  + Automatic module selection based on pin configuration is transparent to users

### Improvements

+ Reduced the amount of `#ifdef` conditionals and regular expressions in various low-level implementations for Renesas MCUs
  + Simplified conditional compilation and regex usage
  + Improved readability and maintainability across affected modules

### Fixes

+ Fixed setting of interrupt priority for the M23 core
  + Manifested as UART receive interrupt issues on Renesas RA2 devices
  + Incorrect interrupt priority register index and bit-shift calculation corrected in `hal_ll_core_port_nvic_set_priority_irq`

### NEW HARDWARE

> NOTE:
>> If any new hardware was added to current version, it will be listed here.

+ **[2026-04-23](./new_hw/2026-04-23.md)**
+ **[2026-04-24](./new_hw/2026-04-24.md)**
+ **[2026-04-27](./new_hw/2026-04-27.md)**
+ **[2026-04-28](./new_hw/2026-04-28.md)**
+ **[2026-04-29](./new_hw/2026-04-29.md)**
+ **[2026-04-30](./new_hw/2026-04-30.md)**
+ **[2026-05-01](./new_hw/2026-05-01.md)**
+ **[2026-05-04](./new_hw/2026-05-04.md)**
+ **[2026-05-05](./new_hw/2026-05-05.md)**
+ **[2026-05-06](./new_hw/2026-05-06.md)**
+ **[2026-05-07](./new_hw/2026-05-07.md)**
+ **[2026-05-08](./new_hw/2026-05-08.md)**
+ **[2026-05-11](./new_hw/2026-05-11.md)**
+ **[2026-05-12](./new_hw/2026-05-12.md)**
+ **[2026-05-13](./new_hw/2026-05-13.md)**
+ **[2026-05-14](./new_hw/2026-05-14.md)**
+ **[2026-05-15](./new_hw/2026-05-15.md)**
+ **[2026-05-18](./new_hw/2026-05-18.md)**
+ **[2026-05-19](./new_hw/2026-05-19.md)**
+ **[2026-05-20](./new_hw/2026-05-20.md)**
+ **[2026-05-21](./new_hw/2026-05-21.md)**
+ **[2026-05-22](./new_hw/2026-05-22.md)**
+ **[2026-05-25](./new_hw/2026-05-25.md)**
+ **[2026-05-26](./new_hw/2026-05-26.md)**
+ **[2026-05-27](./new_hw/2026-05-27.md)**
+ **[2026-05-28](./new_hw/2026-05-28.md)**
+ **[2026-05-29](./new_hw/2026-05-29.md)**
+ **[2026-06-01](./new_hw/2026-06-01.md)**
+ **[2026-06-02](./new_hw/2026-06-02.md)**
+ **[2026-06-03](./new_hw/2026-06-03.md)**
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

---

**[BACK TO MAIN FILE](../../changelog.md)**

---
