<p align="center">
  <img src="http://www.mikroe.com/img/designs/beta/logo_small.png?raw=true" alt="MikroElektronika"/>
</p>

---

**[BACK TO MAIN FILE](../../changelog.md)**

---

# `v2.21.0`

+ released: 2026-12-01

## Changes

- [`v2.21.0`](#v2210)
  - [Changes](#changes)
    - [RENESAS](#renesas)
    - [NEW HARDWARE](#new-hardware)

### <font color=red>RENESAS</font>

**RX architecture supported!**

mikroSDK now supports Renesas RX MCUs, starting with the RX26T family.

**RX26T MCUs supported!**

**About the MCU:**

The RX26T is a 32-bit MCU family built around the RXv3 core, aimed at motor control and power conversion applications such as inverters, pumps, fans and industrial drives.

+ RXv3 CPU with single and double precision FPU, up to 120MHz
+ Trigonometric Function Unit (TFU) for accelerated motor control calculations
+ Up to 512KB Flash, 64KB SRAM and 16KB Data Flash
+ 2.7V to 5.5V operating voltage
+ Available in 48-pin, 64-pin, 80-pin and 100-pin packages

| **R5F526T8ADFL** | **R5F526TACDFM** | **R5F526TBCGFL** | **R5F526TFBDFP** |
| :-----------: | :-----------: | :-----------: | :-----------: |
| **R5F526T8ADFM** | **R5F526TACGFL** | **R5F526TBCGFM** | **R5F526TFBDND** |
| **R5F526T8AGFL** | **R5F526TACGFM** | **R5F526TBCGFN** | **R5F526TFBDNE** |
| **R5F526T8AGFM** | **R5F526TBADFL** | **R5F526TBCGFP** | **R5F526TFBGFL** |
| **R5F526T9ADFL** | **R5F526TBADFM** | **R5F526TBCGND** | **R5F526TFBGFM** |
| **R5F526T9ADFM** | **R5F526TBADFN** | **R5F526TBCGNE** | **R5F526TFBGFN** |
| **R5F526T9ADFN** | **R5F526TBADFP** | **R5F526TBDDFL** | **R5F526TFBGFP** |
| **R5F526T9ADFP** | **R5F526TBADND** | **R5F526TBDDFM** | **R5F526TFBGND** |
| **R5F526T9ADND** | **R5F526TBADNE** | **R5F526TBDDFN** | **R5F526TFBGNE** |
| **R5F526T9ADNE** | **R5F526TBAGFL** | **R5F526TBDDFP** | **R5F526TFCDFL** |
| **R5F526T9AGFL** | **R5F526TBAGFM** | **R5F526TBDDND** | **R5F526TFCDFM** |
| **R5F526T9AGFM** | **R5F526TBAGFN** | **R5F526TBDDNE** | **R5F526TFCDFN** |
| **R5F526T9AGFN** | **R5F526TBAGFP** | **R5F526TBDGFL** | **R5F526TFCDFP** |
| **R5F526T9AGFP** | **R5F526TBAGND** | **R5F526TBDGFM** | **R5F526TFCDND** |
| **R5F526T9AGND** | **R5F526TBAGNE** | **R5F526TBDGFN** | **R5F526TFCDNE** |
| **R5F526T9AGNE** | **R5F526TBBDFL** | **R5F526TBDGFP** | **R5F526TFCGFL** |
| **R5F526T9BDFL** | **R5F526TBBDFM** | **R5F526TBDGND** | **R5F526TFCGFM** |
| **R5F526T9BDFM** | **R5F526TBBDFN** | **R5F526TBDGNE** | **R5F526TFCGFN** |
| **R5F526T9BDFN** | **R5F526TBBDFP** | **R5F526TFADFL** | **R5F526TFCGFP** |
| **R5F526T9BDFP** | **R5F526TBBDND** | **R5F526TFADFM** | **R5F526TFCGND** |
| **R5F526T9BDND** | **R5F526TBBDNE** | **R5F526TFADFN** | **R5F526TFCGNE** |
| **R5F526T9BDNE** | **R5F526TBBGFL** | **R5F526TFADFP** | **R5F526TFDDFL** |
| **R5F526T9BGFL** | **R5F526TBBGFM** | **R5F526TFADND** | **R5F526TFDDFM** |
| **R5F526T9BGFM** | **R5F526TBBGFN** | **R5F526TFADNE** | **R5F526TFDDFN** |
| **R5F526T9BGFN** | **R5F526TBBGFP** | **R5F526TFAGFL** | **R5F526TFDDFP** |
| **R5F526T9BGFP** | **R5F526TBBGND** | **R5F526TFAGFM** | **R5F526TFDDND** |
| **R5F526T9BGND** | **R5F526TBBGNE** | **R5F526TFAGFN** | **R5F526TFDDNE** |
| **R5F526T9BGNE** | **R5F526TBCDFL** | **R5F526TFAGFP** | **R5F526TFDGFL** |
| **R5F526TAADFL** | **R5F526TBCDFM** | **R5F526TFAGND** | **R5F526TFDGFM** |
| **R5F526TAADFM** | **R5F526TBCDFN** | **R5F526TFAGNE** | **R5F526TFDGFN** |
| **R5F526TAAGFL** | **R5F526TBCDFP** | **R5F526TFBDFL** | **R5F526TFDGFP** |
| **R5F526TAAGFM** | **R5F526TBCDND** | **R5F526TFBDFM** | **R5F526TFDGND** |
| **R5F526TACDFL** | **R5F526TBCDNE** | **R5F526TFBDFN** | **R5F526TFDGNE** |

**Supported modules:**

+ ADC (Full module support)
+ SPI (Full module support)
+ UART (Full module support)
+ I2C (Full module support)
+ PWM (Full module support)
+ GPIO (Full module support)
+ 1-Wire (Full module support)

### NEW HARDWARE

> NOTE:
>> If any new hardware was added to current version, it will be listed here.

Support added for following hardware:

+ **[2026-11-03](./new_hw/2026-11-03.md)**
+ **[2026-11-04](./new_hw/2026-11-04.md)**
+ **[2026-11-05](./new_hw/2026-11-05.md)**
+ **[2026-11-06](./new_hw/2026-11-06.md)**
+ **[2026-11-09](./new_hw/2026-11-09.md)**
+ **[2026-11-10](./new_hw/2026-11-10.md)**
+ **[2026-11-11](./new_hw/2026-11-11.md)**
+ **[2026-11-12](./new_hw/2026-11-12.md)**
+ **[2026-11-13](./new_hw/2026-11-13.md)**
+ **[2026-11-16](./new_hw/2026-11-16.md)**
+ **[2026-11-17](./new_hw/2026-11-17.md)**
+ **[2026-11-18](./new_hw/2026-11-18.md)**
+ **[2026-11-19](./new_hw/2026-11-19.md)**
+ **[2026-11-20](./new_hw/2026-11-20.md)**
+ **[2026-11-23](./new_hw/2026-11-23.md)**
+ **[2026-11-24](./new_hw/2026-11-24.md)**
+ **[2026-11-25](./new_hw/2026-11-25.md)**
+ **[2026-11-26](./new_hw/2026-11-26.md)**
+ **[2026-11-27](./new_hw/2026-11-27.md)**
+ **[2026-11-30](./new_hw/2026-11-30.md)**
+ **[2026-12-01](./new_hw/2026-12-01.md)**
+ **[2026-12-02](./new_hw/2026-12-02.md)**
+ **[2026-12-03](./new_hw/2026-12-03.md)**
+ **[2026-12-04](./new_hw/2026-12-04.md)**
+ **[2026-12-07](./new_hw/2026-12-07.md)**
+ **[2026-12-08](./new_hw/2026-12-08.md)**
+ **[2026-12-09](./new_hw/2026-12-09.md)**
+ **[2026-12-10](./new_hw/2026-12-10.md)**
+ **[2026-12-11](./new_hw/2026-12-11.md)**
+ **[2026-12-14](./new_hw/2026-12-14.md)**
+ **[2026-12-15](./new_hw/2026-12-15.md)**
+ **[2026-12-16](./new_hw/2026-12-16.md)**
+ **[2026-12-17](./new_hw/2026-12-17.md)**
+ **[2026-12-18](./new_hw/2026-12-18.md)**
+ **[2026-12-21](./new_hw/2026-12-21.md)**
+ **[2026-12-22](./new_hw/2026-12-22.md)**
+ **[2026-12-23](./new_hw/2026-12-23.md)**
+ **[2026-12-24](./new_hw/2026-12-24.md)**
+ **[2026-12-25](./new_hw/2026-12-25.md)**
+ **[2026-12-28](./new_hw/2026-12-28.md)**
+ **[2026-12-29](./new_hw/2026-12-29.md)**
+ **[2026-12-30](./new_hw/2026-12-30.md)**
+ **[2026-12-31](./new_hw/2026-12-31.md)**
+ **[2027-01-01](./new_hw/2027-01-01.md)**
+ **[2027-01-04](./new_hw/2027-01-04.md)**
+ **[2027-01-05](./new_hw/2027-01-05.md)**
+ **[2027-01-06](./new_hw/2027-01-06.md)**
+ **[2027-01-07](./new_hw/2027-01-07.md)**
+ **[2027-01-08](./new_hw/2027-01-08.md)**
+ **[2027-01-11](./new_hw/2027-01-11.md)**
+ **[2027-01-12](./new_hw/2027-01-12.md)**
+ **[2027-01-13](./new_hw/2027-01-13.md)**
+ **[2027-01-14](./new_hw/2027-01-14.md)**
+ **[2027-01-15](./new_hw/2027-01-15.md)**
+ **[2027-01-18](./new_hw/2027-01-18.md)**
+ **[2027-01-19](./new_hw/2027-01-19.md)**
+ **[2027-01-20](./new_hw/2027-01-20.md)**
+ **[2027-01-21](./new_hw/2027-01-21.md)**
+ **[2027-01-22](./new_hw/2027-01-22.md)**
+ **[2027-01-25](./new_hw/2027-01-25.md)**
+ **[2027-01-26](./new_hw/2027-01-26.md)**
+ **[2027-01-27](./new_hw/2027-01-27.md)**
+ **[2027-01-28](./new_hw/2027-01-28.md)**
+ **[2027-01-29](./new_hw/2027-01-29.md)**
+ **[2027-02-01](./new_hw/2027-02-01.md)**
+ **[2027-02-02](./new_hw/2027-02-02.md)**
+ **[2027-02-03](./new_hw/2027-02-03.md)**
+ **[2027-02-04](./new_hw/2027-02-04.md)**
+ **[2027-02-05](./new_hw/2027-02-05.md)**
+ **[2027-02-08](./new_hw/2027-02-08.md)**
+ **[2027-02-09](./new_hw/2027-02-09.md)**
+ **[2027-02-10](./new_hw/2027-02-10.md)**
+ **[2027-02-11](./new_hw/2027-02-11.md)**
+ **[2027-02-12](./new_hw/2027-02-12.md)**
+ **[2027-02-15](./new_hw/2027-02-15.md)**
+ **[2027-02-16](./new_hw/2027-02-16.md)**
+ **[2027-02-17](./new_hw/2027-02-17.md)**
+ **[2027-02-18](./new_hw/2027-02-18.md)**
+ **[2027-02-19](./new_hw/2027-02-19.md)**
+ **[2027-02-22](./new_hw/2027-02-22.md)**
+ **[2027-02-23](./new_hw/2027-02-23.md)**
+ **[2027-02-24](./new_hw/2027-02-24.md)**
+ **[2027-02-25](./new_hw/2027-02-25.md)**
+ **[2027-02-26](./new_hw/2027-02-26.md)**
+ **[2027-03-01](./new_hw/2027-03-01.md)**
+ **[2027-03-02](./new_hw/2027-03-02.md)**

---

**[BACK TO MAIN FILE](../../changelog.md)**

---
